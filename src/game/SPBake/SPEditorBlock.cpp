// src/game/SPBake/SPEditorBlock.cpp -- migrated from slice(s) s00447150, s00439110, s00451ef0, s00450f70, s0044f7c0, s0044f420, s0044e460, s0044d4f0, s0044bcf0, s0044ae00, s00449ed0, s00448380, s00446ff0, s00441440, s00441080, s00440110, s0043f3a0, s0043e3f0, s0043d690, s0043cad0, s0043bbc0, s0043ac40, s0043a460, s00438440 by tools/migrate/rewrite.py
// Object file: SPBake/SPEditorBlock.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Audio/FactoryBinarySampleData.h"
#include "SP/cSPEditorBlock.h"
#include "SP/cMWModel.h"
#include "SP/cPropertyList.h"
#include "cSPBoundingBox.h"
#include "SP/cSPEditorHandle.h"
#include "SP/cSPEditorHandleDeform.h"
#include "SP/cSPEditorHandleRotationRing.h"
#include "SP/cSPEditorModel.h"
#include "cSPVector3.h"
#include <math.h>
#include <xmmintrin.h>   // also switches /arch:SSE scalar float codegen to SSE at /Od
#include "EA/ArgScript/cIParser.h"
#include "SP/cEffectsRenderer.h"
#include "EA/Variant.h"
#include "SP/cDirectPropertyList.h"
#include "EA/Audio/Sound.h"
#include "SP/cSPEditorHandleBallConnector.h"
#include "SP/cSPEditorHandleRotationBall.h"
#include <stddef.h>
#include <float.h>
#include "SP/cSPEditorSnapVector.h"
#include "EA/Swarm/cIComponent.h"

// ---- items of slice s00438440 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct Triple { uint32_t a, b, c; };
}
namespace SP {
struct TripleVec { Triple* begin; Triple* end; };
}
namespace SP {
struct KeyOwner {
    void GetKey(Triple* out);            // 00440B90
};
}
namespace SP {
struct PropertyList {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6();
    virtual bool HasProperty(uint32_t id);   // vtable +0x1C
};
}
namespace SP {
struct Node {
    bool Check();                        // 004ADC40
};
}
namespace SP {
class cContentValidationSummarizer;
}
namespace SP {
// The object reached through LinkRec::field4 is released through the second
// vtable slot (0x00438C9B loads [old+0x04] before the call at 0x00438C9E);
// cContentValidationSummarizer keeps Release at +0x08, so the field gets its
// own two-slot interface.
struct LinkTarget {
    virtual void AddRef();               // vtable +0x00
    virtual void Release();              // vtable +0x04
};
}
namespace SP {
struct LinkRec {
    void*       field0;                  // +0x00
    LinkTarget* field4;                  // +0x04
    char        pad8[0x3C];
    int32_t     field44;                 // +0x44
};
}
namespace SP {
struct EntityVec {
    cContentValidationSummarizer** begin;
    cContentValidationSummarizer** end;
    void push_back(cContentValidationSummarizer* const& v);  // 004541F0
    void erase(cContentValidationSummarizer** it);           // 00454330
};
}
namespace SP {
struct BitSet60 {
    uint32_t data[2];
    bool Get(int i) {
        if (i < 60) return (data[i >> 5] & (1u << (i % 32))) != 0;
        return false;
    }
    void Set(int i, bool v);             // 00435A10
};
}
namespace SP {
class cContentValidationSummarizer { public:
    virtual void slot0();                // vtable +0x00
    virtual void AddRef();               // vtable +0x04
    virtual void Release();              // vtable +0x08

    char            pad04[8];            // +0x04
    PropertyList*   props;               // +0x0C
    char            pad10[0xC];          // +0x10
    uint32_t        keyA;                // +0x1C
    uint32_t        keyB;                // +0x20
    char            pad24[4];            // +0x24
    Node*           node;                // +0x28
    char            pad2c[0x33C - 0x2C];
    cContentValidationSummarizer* link33c;// +0x33C
    EntityVec       entities;            // +0x340
    char            pad348[0x378 - 0x348];
    LinkRec*        linkRec;             // +0x378
    char            pad37c[0x3E0 - 0x37C];
    cContentValidationSummarizer* link3e0;// +0x3E0
    cContentValidationSummarizer* link3e4;// +0x3E4
    char            pad3e8[0x774 - 0x3E8];
    TripleVec       vec774;              // +0x774 (each vector spans 0x78 bytes)
    char            pad77c[0x7EC - 0x77C];
    TripleVec       vec7ec;              // +0x7EC
    char            pad7f4[0x864 - 0x7F4];
    TripleVec       vec864;              // +0x864
    char            pad86c[0x8DC - 0x86C];
    TripleVec       vec8dc;              // +0x8DC
    char            pad8e4[0x954 - 0x8E4];
    TripleVec       vec954;              // +0x954
    char            pad95c[0x9CC - 0x95C];
    TripleVec       vec9cc;              // +0x9CC
    char            pad9d4[0xABC - 0x9D4];
    TripleVec       vecabc;              // +0xABC
    char            padac4[0xDC8 - 0xAC4];
    BitSet60        bits;                // +0xDC8

    bool FindEntry(KeyOwner* owner, int type);   // 00438440
    bool HasZeroKey(int type);                   // 004385E0
    void RefreshLinks(cContentValidationSummarizer* e);      // 00438700
    void Attach(cContentValidationSummarizer* e);            // 004388B0
    void RefreshLinked(cContentValidationSummarizer* e);     // 00438A40
    void Detach(cContentValidationSummarizer* e);            // 00438B10
    void SetLink3e0(cContentValidationSummarizer* p);        // 00438CC0
    void SetLink3e4(cContentValidationSummarizer* p);        // 00438DF0
    Triple GetKey(int type, int sub);                        // 00438F20
    void SetFlag(int index, bool value);                     // 00435A10
    void SetLink(cContentValidationSummarizer* p);           // 00435FD0
    int  GetCount();                                         // 0044F220
};
}
// ---- items of slice s00438440 end

// ---- items of slice s0043a460 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct Vec3 { float x, y, z; };
}
namespace SP {
struct Vec4 {
    float x, y, z, w;
    Vec4() {}
    Vec4(const Vec4& o) : x(o.x), y(o.y), z(o.z), w(o.w) {}
};
}
namespace SP {
struct BitSet60_s0043_a460 {
    uint32_t data[2];
    bool Get(int i) {
        if (i < 60) return (data[i >> 5] & (1u << (i % 32))) != 0;
        return false;
    }
};
}
namespace SP {
struct KeyVec {
    void* begin;
    void* end;
    bool empty() const;   // 0x00526430
};
}
namespace SP {
struct cSPEditorBlock_s0043_a460 {
    char     pad00[0x10];
    void*    mModel;                 // +0x10
    char     pad14[0x38 - 0x14];
    uint8_t  f38;                    // +0x38
    uint8_t  f39;                    // +0x39
    char     pad3a[2];
    uint32_t f3c;                    // +0x3C
    uint32_t f40;                    // +0x40
    uint32_t f44;                    // +0x44
    char     pad48[0x1C0 - 0x48];
    float    mBaseJointScale;        // +0x1C0
    float    mUniformScale;          // +0x1C4
    char     pad1c8[0x1D8 - 0x1C8];
    float    f1d8;                   // +0x1D8
    char     pad1dc[0x3E0 - 0x1DC];
    void*    p3e0;                   // +0x3E0
    char     pad3e4[0x3F4 - 0x3E4];
    char     tbl3f4[12];             // +0x3F4
    char     tbl400[12];             // +0x400
    char     pad40c[0xA44 - 0x40C];
    KeyVec   keys;                   // +0xA44
    char     padA4c[0xDC8 - 0xA4C];
    BitSet60_s0043_a460 bits;                   // +0xDC8

    bool F3AC40(int type, uint8_t a, uint8_t b);          // 0043AC40
    bool F5a0();                                          // 0043A5A0
    bool F5c0();                                          // 0043A5C0
    float Length1();                                      // 0043A460
    Vec3* GetVec1(Vec3* out);                             // 0043A490
    float Length2();                                      // 0043A500
    Vec3* GetVec2(Vec3* out);                             // 0043A530
    bool F5e0(int type, uint8_t a, uint8_t b, char c);    // 0043A5E0
    void F830(uint8_t p);                                 // 0043A830
    int  GetSkinIdentifierForPicking();                   // 0043A870 0x0043a870
    void F9a0(uint8_t a, uint8_t b);                      // 0043A9A0
    bool F9e0(uint8_t a, uint8_t b);                      // 0043A9E0
    bool Fb90(uint8_t p);                                 // 0043AB90
    void F3cfc0(int a, uint8_t b);                        // 0043CFC0
    void F448a80();                                       // 00448A80
    void F448690(Vec4 v);                                 // 00448690
    void F3cad0();                                        // 0043CAD0
    void F48C790(void* out, int flag);                    // 0048C790
};
}
namespace SP {
bool  ModelKey_HasResourceType(void* modelKey);           // 00526430 (thiscall)
}
namespace SP {
extern const Vec4 g_v4_a;   // 015D21B8
}
namespace SP {
extern const Vec4 g_v4_b;   // 015D21D4
}
// ---- items of slice s0043a460 end

// ---- items of slice s0043ac40 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct Model;
}
namespace SP {
struct BitField {
    uint32_t m;
    bool Get(int i) const {
        if (i < 32) return (m & (1u << (i % 32))) != 0;
        return false;
    }
    void Set(int i, bool v) {
        if (i < 32) {
            if (v) m |= (1u << (i % 32));
            else   m &= ~(1u << (i % 32));
        }
    }
};
}
namespace SP {
struct Model {
    char     pad0[4];
    BitField flags;      // +0x04
    char     pad8[0x5C - 8];
    uint8_t  state;      // +0x5C
};
}
namespace SP {
struct ModelState {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9();
    virtual void SetState(int flag, int state);   // vtbl +0x28
};
}
namespace SP {
struct State {
    uint8_t  a;      // +0
    uint8_t  b;      // +1
    uint16_t pad;    // +2
    int32_t  type;   // +4
};                   // size 8
}
namespace SP {
struct cSPEditorBlock_s0043_ac40 {
    char        pad00[0x10];
    Model*      mModel;      // +0x10
    char        pad14[0x38 - 0x14];
    State       cur;         // +0x38
    State       prev;        // +0x40
    char        pad48[0x3EC - 0x48];
    ModelState* p3ec;        // +0x3EC
    Model*      p3f0;        // +0x3F0

    bool F3AC40(int type, uint8_t a, uint8_t b);
};
}
// ---- items of slice s0043ac40 end

// ---- items of slice s0043bbc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kMinTolerance;         // 0.01f
extern const float kMaxTolerance;         // 0.13f
namespace eastl {
template<class T> struct vector_s0043_bbc0 {
    T* mpBegin; T* mpEnd; T* mpCapacity; int mAllocator;
    int size() const { return (int)(mpEnd - mpBegin); }
    T& operator[](int i) { return mpBegin[i]; }
};
}
namespace eastl {
template<int N> class bitset { public:
    uint32_t mWord[(N + 31) / 32];
    uint32_t& DoGetWord(uint32_t i) { return mWord[i >> 5]; }
    uint32_t DoGetWord(uint32_t i) const { return mWord[i >> 5]; }
    bool test(uint32_t i) const {
        if (i < N) return (DoGetWord(i) & (1u << (i % 32))) != 0;
        return false;
    }
    __forceinline void set(uint32_t i, bool value) {
        if (i < N) {
            if (value) DoGetWord(i) |= 1u << (i % 32);
            else DoGetWord(i) &= ~(1u << (i % 32));
        }
    }
};
}
namespace EA {
template<class T> struct AutoRefCount_s0043_bbc0 {
    T* mpObject;
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
}
using eastl::vector_s0043_bbc0;
using eastl::bitset;
using EA::AutoRefCount_s0043_bbc0;
struct cSPVector3_s0043_bbc0 {
    float x, y, z;
    cSPVector3_s0043_bbc0() {}
    cSPVector3_s0043_bbc0(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    cSPVector3_s0043_bbc0(const cSPVector3_s0043_bbc0& v) : x(v.x), y(v.y), z(v.z) {}
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
cSPVector3_s0043_bbc0 operator-(const cSPVector3_s0043_bbc0& a, const cSPVector3_s0043_bbc0& b);   // 0x41db10
struct cSPMatrix3_s0043_bbc0 {                      // rw::math::fpu::Matrix33Template<float,0>
    cSPVector3_s0043_bbc0 r[3];
    cSPMatrix3_s0043_bbc0() {}
    cSPMatrix3_s0043_bbc0(const cSPMatrix3_s0043_bbc0& o);     // Matrix3::Assign (0x41cb40), out of line
    const cSPVector3_s0043_bbc0& operator[](int i) const { return r[i]; }
};
struct cSPBoundingBox_s0043_bbc0 {
    cSPVector3_s0043_bbc0 mMin, mMax;
    cSPBoundingBox_s0043_bbc0();                                  // BoundingBox_Reset 0x409c00
    cSPBoundingBox_s0043_bbc0(const cSPBoundingBox_s0043_bbc0& o);           // 0x511140
    void Extend(const cSPVector3_s0043_bbc0& p);                  // BoundingBox::Extend 0x41bd50
    bool IsEmpty() const { return mMin[0] > mMax[0]; }
    void Add(const cSPBoundingBox_s0043_bbc0& o);                 // 0x43f050
    cSPVector3_s0043_bbc0 GetCorner(uint32_t mask) const;         // 0x43f290
};
namespace SP {
struct cPropertyList_s0043_bbc0 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6();
    virtual bool HasProperty(uint32_t id);  // 0x006a2470 (SP::cPropertyList::HasProperty)
};
}
namespace SP {
bool GetPropertyAsKey(cPropertyList_s0043_bbc0* p, uint32_t id, uint32_t out);
}
namespace SP {
struct cMWModel_s0043_bbc0 { char pad[0x44]; bitset<64> mGroups; };
}
namespace SP {
struct cSPEditorModel_s0043_bbc0 {
    float GetScale();       // 0x4adaa0
    bool Func4adb80();      // 0x4adb80
    bool Func4adbc0();      // 0x4adbc0
    bool Func4adc40();      // 0x4adc40 (symmetry enabled?)
};
}
namespace SP {
struct cSPEditorHandle_s0043_bbc0 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
    virtual void Update();                 // vtable +0x2c
};
}
namespace SP {
struct cSPEditorHandleRotationRing_s0043_bbc0 : cSPEditorHandle_s0043_bbc0 {
    char pad[0x92 - 4]; bool mbHidden;     // +0x92
    bool IsHidden() const { return mbHidden; }
};
}
namespace SP {
struct cSPEditorHandleRotationBall_s0043_bbc0 : cSPEditorHandle_s0043_bbc0 {};
}
namespace SP {
struct cSPEditorHandleDeform_s0043_bbc0 : cSPEditorHandle_s0043_bbc0 {
    char pad04[0x8c - 4];
    uint32_t mAnimationID;                 // +0x8c  (mData.mAnimationID)
    cSPVector3_s0043_bbc0 mStartPt;                   // +0x90
    cSPVector3_s0043_bbc0 mEndPt;                     // +0x9c
    char padA8[0x180 - 0xa8];
    float mDelta;                          // +0x180
    char pad184[0x1d4 - 0x184];
    bool mIsHiddenHandle;                  // +0x1d4
    bool mDoNotPlaceHandle;                // +0x1d5
    float GetDelta() const { return mDelta; }
};
}
namespace SP {
struct cSPEditorBlock_s0043_bbc0;
}
namespace SP {
struct BlockList : vector_s0043_bbc0<AutoRefCount_s0043_bbc0<cSPEditorBlock_s0043_bbc0> > { bool Func526430(); };  // SP::GetResourceTypeFromModelType (folded)
}
namespace SP {
struct cSPFadeController {               // at +0xdd0
    bool IsActive();                     // FadeController::IsActive 0x4340c0
    void Stop();                         // FadeController::Stop 0x434120
    void Start(uint32_t a, float t);     // 0x4342f0
};
}
void* GetCurrentThing();                  // 0x401060
void PostMessageId(uint32_t id);          // 0x4a88d0
cSPMatrix3_s0043_bbc0 MatA(SP::cSPEditorBlock_s0043_bbc0* o, cSPMatrix3_s0043_bbc0 m);   // 0x49e880
cSPMatrix3_s0043_bbc0 MatB(SP::cSPEditorBlock_s0043_bbc0* o);                 // 0x494270
float Vec3Dist(const cSPVector3_s0043_bbc0& a, const cSPVector3_s0043_bbc0& b);   // 0x454aa0
namespace SP {
struct cSPEditorBlock_s0043_bbc0 {
    char pad00[0x0c];
    AutoRefCount_s0043_bbc0<cPropertyList_s0043_bbc0> mPropList;                     // +0x0c
    AutoRefCount_s0043_bbc0<cMWModel_s0043_bbc0> mModel;                             // +0x10
    char pad14[0x28 - 0x14];
    cSPEditorModel_s0043_bbc0* mEditorModel;                              // +0x28
    char pad2c[0x48 - 0x2c];
    cSPVector3_s0043_bbc0 mPosition;                                      // +0x48
    char pad54[0x154 - 0x54];
    AutoRefCount_s0043_bbc0<cSPEditorHandleRotationRing_s0043_bbc0> mRotationRingHandles[3];   // +0x154
    AutoRefCount_s0043_bbc0<cSPEditorHandleRotationBall_s0043_bbc0> mRotationBallHandle;       // +0x160
    char pad164[0x1b0 - 0x164];
    int mHandleIndex[4];                                       // +0x1b0
    char pad1c0[0x1d4 - 0x1c0];
    float mField1d4;                                           // +0x1d4
    float mScale;                                              // +0x1d8
    char pad1dc[0x218 - 0x1dc];
    float mRangeMin;                                           // +0x218
    float mRangeMax;                                           // +0x21c
    float mTolA, mTolB, mTol228, mTolC;                        // +0x220
    char pad230[0x340 - 0x230];
    BlockList mChildBlockList;                                 // +0x340
    char pad350[0x3c9 - 0x350];
    bool mField3c9;                                            // +0x3c9
    char pad3ca[0x3e0 - 0x3ca];
    AutoRefCount_s0043_bbc0<cSPEditorBlock_s0043_bbc0> mSymmetricBlock;              // +0x3e0
    char pad3e4[0x3ec - 0x3e4];
    AutoRefCount_s0043_bbc0<cSPEditorBlock_s0043_bbc0> mField3ec;                    // +0x3ec
    char pad3f0[0x448 - 0x3f0];
    float mField448;                                           // +0x448
    float mField44c;                                           // +0x44c
    char pad450[0x604 - 0x450];
    uint32_t mField604;                                        // +0x604
    uint32_t mField608;                                        // +0x608
    char pad60c[0x6cc - 0x60c];
    vector_s0043_bbc0<AutoRefCount_s0043_bbc0<cSPEditorHandleDeform_s0043_bbc0> > mDeformationHandles;   // +0x6cc
    char pad6dc[0x704 - 0x6dc];
    vector_s0043_bbc0<float> mSavedHandleDeltas;                          // +0x704
    char pad714[0x73c - 0x714];
    vector_s0043_bbc0<uint32_t> mSavedHandleAnimIDs;                      // +0x73c
    char pad74c[0xdc8 - 0x74c];
    bitset<60> mFlags;                                         // +0xdc8
    cSPFadeController mFader;                                  // +0xdd0
    char padfade[0xde4 - 0xdd1];
    uint32_t mFadeArg;                                         // +0xde4
    char padde8[0xdf4 - 0xde8];
    int mFadeId;                                               // +0xdf4

    float GetRangeMin() const { return mRangeMin; }
    float GetRangeMax() const { return mRangeMax; }
    cSPEditorModel_s0043_bbc0* GetEditorModel() const { return mEditorModel; }

    // slice s0043bbc0
    bool F_43bbc0(int);
    void F_43bc40(float v);
    bool F_43bc70(float a, float b);
    bool F_43bcf0(float a, float b);
    void F_43bd50(cSPVector3_s0043_bbc0 v, float s);
    bool F_43bd80(cSPMatrix3_s0043_bbc0 m, float s);
    bool F_43bf20(uint32_t out);
    void F_43bf90(uint32_t bit, bool on);
    int F_43c040();
    int F_43c0a0();
    int F_43c120(uint32_t id);
    cSPEditorHandleDeform_s0043_bbc0* F_43c1a0();
    cSPEditorHandleDeform_s0043_bbc0* F_43c1e0();
    cSPEditorHandleDeform_s0043_bbc0* F_43c210();
    cSPEditorHandleDeform_s0043_bbc0* F_43c240();
    cSPEditorHandleDeform_s0043_bbc0* F_43c270(int i);
    float F_43c2d0(uint32_t i);
    uint32_t F_43c340(uint32_t i);
    int F_43c3d0(cSPEditorHandleDeform_s0043_bbc0* c);
    bool F_43c450(cSPEditorHandleDeform_s0043_bbc0* c, float f, float* a, bool b);
    bool F_43c510();
    void F_43c710();
    bool F_43ca10();
    void F_43d690(int idx, float f, float* a, bool b, bool one);   // 0x43d690
    // slice s0043e3f0
    void F_43e3f0(float dt, uint32_t index);
    void F_43e760(uint32_t index);
    void F_43e7e0(uint32_t index, bool b);
    bool F_43e8d0(int id);
    bool F_43e920();
    void F_43e940(uint32_t a, uint32_t b, int id);
    void F_43e9c0();
    void F_43ea20();
    void F_43ea40(int id);
    void F_43eaa0(int id);
    void F_43eae0(float v);
    void F_43eb50(float v);
    bool F_43ebc0();
    bool F_43ecb0();
    cSPBoundingBox_s0043_bbc0 F_43eef0();
    float F_43f250();
    float F_43eed0();                      // 0x43eed0
    float F_43f3a0();                      // 0x43f3a0
    void F_440110(float v);                // 0x440110
    void F_440390(float v);                // 0x440390
    void F_449ce0();                       // 0x449ce0
    cSPBoundingBox_s0043_bbc0 GetBBox(bool a, bool b, bool c);   // SP::cSPEditorBlock::GetBBox 0x44ae00
};
}
// ---- items of slice s0043bbc0 end

// ---- items of slice s0043cad0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct Blk {
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
    virtual void SetState(int a, int b);   // vtbl +0x30
};
}
namespace SP {
struct Node_s0043_cad0 {
    bool Check();
    float F3adb80();
    float F3adbc0();
};
}
namespace SP {
struct cSPEditorBlock_s0043_cad0 {
    char        pad00[0x10];
    void*       mModel;      // +0x10
    char        pad14[0x18 - 0x14];
    void*       p18;         // +0x18
    char        pad1c[0x28 - 0x1c];
    Node_s0043_cad0*       node;        // +0x28
    char        pad2c[0x154 - 0x2c];
    Blk*        slots[3];    // +0x154
    Blk*        slot160;     // +0x160
    char        pad164[0x1B0 - 0x164];
    int         f1b0;        // +0x1B0
    char        pad1b4[0x2BC - 0x1B4];
    int         f2bc;        // +0x2BC
    char        pad2c0[0x3EC - 0x2C0];
    void*       p3ec;        // +0x3EC
    char        pad3f0[0x6CC - 0x3F0];
    void**      vec6cc;      // +0x6CC
    void**      vec6d0;      // +0x6D0
    char        pad6d4[0xDC8 - 0x6D4];
    uint32_t    flags0;      // +0xDC8
    uint32_t    flags1;      // +0xDCC

    Blk* GetSlot(int i);                 // 0043CE00
    void F3cad0();                       // 0043CAD0
    void F3ce40();                       // 0043CE40
    void F3cfc0(int p2, char p3);        // 0043CFC0
    Vec3* F3d240(Vec3* out, char p3);    // 0043D240
    void F3d420();                       // 0043D420
};
}
namespace SP {
void* Sub_401060();                       // 00401060 (app/manager singleton)
}
namespace SP {
bool  Sub_4ADB80();                       // 004ADB80
}
namespace SP {
bool  Sub_4ADBC0();                       // 004ADBC0
}
namespace SP {
bool  Sub_4A6120(void* self);             // 004A6120
}
namespace SP {
void  Sub_4A6660(void* self, uint8_t v);  // 004A6660
}
namespace SP {
void  Sub_4A88D0(int id);                 // 004A88D0
}
namespace SP {
void  GetBBox(void* self, void* out, int a, int b, int c);  // 0044AE00
}
namespace SP {
void  BoundingBox_GetCenter(void* box);   // 00409B90
}
namespace SP {
void* Sub_41DCA0(void* out, void* table, const float* key);  // 0041DCA0
}
// ---- items of slice s0043cad0 end

// ---- items of slice s0043d690 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct Blk_s0043_d690 {
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
    virtual void SetState(int a, int b);      // +0x30
    virtual void Refresh();                    // +0x14
};
}
namespace SP {
struct cSPEditorBlockStub {
    char     pad00[0x10];
    void*    mModel;        // +0x10
    char     pad14[0x18 - 0x14];
    void*    p18;           // +0x18
    char     pad1c[0x154 - 0x1c];
    Blk_s0043_d690*     slots[3];      // +0x154
    char     pad160[0x1A8 - 0x160];
    uint8_t  f1a8;          // +0x1A8
    char     pad1a9[0x1B0 - 0x1A9];
    int      f1b0;          // +0x1B0
    char     pad1b4[0x330 - 0x1B4];
    int      f330;          // +0x330
    char     pad334[0x3F0 - 0x334];
    void*    p3f0;          // +0x3F0
    char     pad3f4[0x40C - 0x3F4];
    Vec3     v40c;          // +0x40C
    char     pad418[0x43C - 0x418];
    int      f43c;          // +0x43C
    float    f440;          // +0x440
    float    f444;          // +0x444
    char     pad448[0x6CC - 0x448];
    void**   vec6cc;        // +0x6CC
    void**   vec6d0;        // +0x6D0
    char     pad6d4[0xDC8 - 0x6D4];
    uint32_t flags0;        // +0xDC8
    uint32_t flags1;        // +0xDCC

    int  F3d690(int idx, int a3, int a4, char a5, char a6);  // 0043D690
    Vec3* F3e080(Vec3* out);                                 // 0043E080
    bool F3e0f0(int* out);                                   // 0043E0F0
    void F3e2b0();                                           // 0043E2B0
};
}
namespace SP {
void* Sub_41DAF0(void* out, void* v);
}
namespace SP {
template <int N> inline void ScratchSlots() { uint32_t slots[N]; }
}
namespace SP {
struct Vector3 {
    float x, y, z;
    Vector3& operator=(const Vector3& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
}
namespace SP {
struct Vector3P {
    float x, y, z;
    Vector3P(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};
}
namespace SP {
Vector3 operator*(const float& s, const Vector3& v);           // 0x0041DE40
}
namespace SP {
Vector3 operator-(const Vector3& a, const Vector3& b);         // 0x0041DB10
}
namespace SP {
Vector3 operator+(const Vector3& a, const Vector3& b);         // 0x0041DC10
}
namespace SP {
struct Matrix3 { float m[9]; };
}
namespace SP {
struct Transform {
    uint16_t mFlags;        // +0x00
    uint16_t mChangeCount;  // +0x02
    Vector3P mOffset;       // +0x04
    float mScale;           // +0x10
    Matrix3 mRotation;      // +0x14

    Transform();                                   // 0x00409930
    Transform& operator=(const Transform& other);  // 0x00537DC0
    void Accumulate(const Transform& other);       // 0x0040CCB0
    void AccumulateScaled(const Transform& other); // 0x0040CD80
    void SetOffset(const Vector3P& offset)
    {
        mOffset = offset;
        mFlags |= 4;
        mChangeCount++;
    }
};
}
namespace SP {
struct BoneTransform { float m[12]; };
}
namespace SP {
void BoneTransformToTransform(const BoneTransform* src, Transform* dst);  // 0x00732270
}
namespace SP {
template <int N>
struct bitset_s0043_d690 {
    uint32_t mWord[(N + 31) / 32];
    __forceinline bool test(uint32_t n) const
    {
        if (n < N) {
            const uint32_t word = mWord[n >> 5];
            return (word & (1u << (n % 32))) != 0;
        }
        return false;
    }
};
}
namespace SP {
template <class T, int N>
struct fixed_vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[3];
    uint32_t mBuffer[(N * sizeof(T)) / 4];

    explicit fixed_vector(unsigned int n);  // 0x0041D510
    ~fixed_vector()
    {
        for (T* p = mpBegin; p < mpEnd; ++p)
            p->~T();
        DoFree();
    }
    void DoFree();                          // 0x00428130
    int size() const { return (int)(mpEnd - mpBegin); }
    bool empty() const;                     // 0x00526430 (ICF-shared)
    T& operator[](int i) { return mpBegin[i]; }
    T* data() { return mpBegin; }
};
}
namespace SP {
template <class T>
struct AutoRefCount {
    T* mpObject;
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
}
namespace SP {
class cMWModel_s0043_d690;
}
namespace SP {
class IModelWorld {
public:
virtual int AddRef();
virtual int Release();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
virtual void v70();
    virtual void MoveToTime(cMWModel_s0043_d690* model, uint32_t animID, float time, int animationGroup);   // 0x74
virtual void v78();
virtual void v7c();
    virtual void GetAnimationRange(cMWModel_s0043_d690* model, uint32_t animID, float* start, float* end, int animationGroup);  // 0x80
    virtual int GetNumBones(cMWModel_s0043_d690* model);                              // 0x84
    virtual void v88();
    virtual int GetBoneTransforms(cMWModel_s0043_d690* model, BoneTransform* dst);    // 0x8c
virtual void v90();
virtual void v94();
virtual void v98();
virtual void v9c();
virtual void va0();
virtual void va4();
virtual void va8();
virtual void vac();
virtual void vb0();
virtual void vb4();
virtual void vb8();
virtual void vbc();
virtual void vc0();
virtual void vc4();
virtual void vc8();
virtual void vcc();
virtual void vd0();
virtual void vd4();
virtual void vd8();
virtual void vdc();
virtual void ve0();
virtual void ve4();
virtual void ve8();
virtual void vec();
virtual void vf0();
virtual void vf4();
virtual void vf8();
virtual void vfc();
virtual void v100();
virtual void v104();
    virtual Transform* GetMeshTransform(cMWModel_s0043_d690* model);                  // 0x108
};
}
namespace SP {
class cMWModel_s0043_d690 {
public:
    IModelWorld* mpWorld;   // +0x00
    uint32_t mFlags;        // +0x04
    Transform mTransform;   // +0x08
};
}
namespace SP {
class cSPEditorBlock_s0043_d690;
}
namespace SP {
class cSPEditorHandle_s0043_d690 {
public:
    virtual int AddRef();          // 0x00
    virtual int Release();         // 0x04 0x0051e380
virtual void v08();
virtual void v0c();
virtual void v10();
    virtual void Update();         // 0x14
    void UpdatePosition();         // 0x00485650
};
}
namespace SP {
class cSPEditorHandleDeform_s0043_d690 : public cSPEditorHandle_s0043_d690 {
public:
    uint32_t pad04[(0x8c - 4) / 4];
    uint32_t mAnimID;               // +0x8c
    uint32_t pad90[(0xb4 - 0x90) / 4];
    cSPEditorHandleDeform_s0043_d690* mpSymmetricHandle;  // +0xb4
    uint32_t padb8[(0x180 - 0xb8) / 4];
    float mWeight;                  // +0x180
    void SetWeight(float weight);   // 0x004809A0
};
}
namespace SP {
class cSPEditorBlock_s0043_d690 {
public:
    uint32_t pad00[0x10 / 4];
    AutoRefCount<cMWModel_s0043_d690> mpModel;                  // +0x10
    uint32_t pad14;
    AutoRefCount<IModelWorld> mpModelWorld;          // +0x18
    uint32_t pad1c[(0x48 - 0x1c) / 4];
    Vector3 mPosition;                               // +0x48
    uint32_t pad54[(0x154 - 0x54) / 4];
    AutoRefCount<cSPEditorHandle_s0043_d690> mAxisHandles[3];   // +0x154
    uint32_t pad160[(0x1a8 - 0x160) / 4];
    bool field_1A8;                                  // +0x1a8
    uint8_t pad1a9[3];
    uint32_t pad1ac;
    int mSelectedMorphHandle;                        // +0x1b0
    uint32_t pad1b4[(0x2c0 - 0x1b4) / 4];
    Transform mCSnapBoneTransform1;                  // +0x2c0
    Transform mCSnapBoneTransform2;                  // +0x2f8
    int mCSnapBoneIndex;                             // +0x330
    uint32_t pad334[(0x340 - 0x334) / 4];
    fixed_vector<AutoRefCount<cSPEditorBlock_s0043_d690>, 8> mChildren;  // +0x340
    uint32_t pad378[(0x3f0 - 0x378) / 4];
    AutoRefCount<cMWModel_s0043_d690> mpSocketConnectorModel;   // +0x3f0
    Vector3 mModelMinSocketConnectorOffset;          // +0x3f4
    Vector3 mModelMaxSocketConnectorOffset;          // +0x400
    Vector3 mSocketConnectorOffset;                  // +0x40c
    uint32_t pad418[(0x6cc - 0x418) / 4];
    fixed_vector<AutoRefCount<cSPEditorHandleDeform_s0043_d690>, 8> mMorphHandles;  // +0x6cc
    uint32_t pad704[(0xdc8 - 0x704) / 4];
    bitset_s0043_d690<60> mBooleanAttributes;                   // +0xdc8

    bool SetMorphHandleWeight(int index, float weight, int arg3, bool updateChildren, bool updateSymmetric);
    void UpdateMorphs();                                   // 0x0043D420
    Vector3 GetSocketConnectorPosition();                  // 0x0043E080
    void SetBooleanAttribute(int index, bool value);       // 0x00435A10
    void UpdateBoundingBox();                              // 0x0044D570
    void SyncTransform(bool b);                            // 0x00437400 (on a child block)
    void UpdateOthers(int index, bool b);                  // 0x00437310
    int FindMorphHandleIndex(cSPEditorHandleDeform_s0043_d690* handle);   // 0x0043C3D0
};
}
// ---- items of slice s0043d690 end

// ---- items of slice s0043e3f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_15d257c;
namespace eastl {
template<class T> struct vector_s0043_e3f0 {
    T* mpBegin; T* mpEnd; T* mpCapacity; int mAllocator;
    int size() const { return (int)(mpEnd - mpBegin); }
    T& operator[](int i) { return mpBegin[i]; }
};
}
namespace eastl {
template<int N> struct bitset_s0043_e3f0 {
    uint32_t mWord[(N + 31) / 32];
    uint32_t& DoGetWord(uint32_t i) { return mWord[i >> 5]; }
    uint32_t DoGetWord(uint32_t i) const { return mWord[i >> 5]; }
    bool test(uint32_t i) const {
        if (i < N) return (DoGetWord(i) & (1u << (i % 32))) != 0;
        return false;
    }
    __forceinline void set(uint32_t i, bool value) {
        if (i < N) {
            if (value) DoGetWord(i) |= 1u << (i % 32);
            else DoGetWord(i) &= ~(1u << (i % 32));
        }
    }
};
}
namespace EA {
template<class T> struct AutoRefCount_s0043_e3f0 {
    T* mpObject;
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
}
using eastl::vector_s0043_e3f0;
using eastl::bitset_s0043_e3f0;
using EA::AutoRefCount_s0043_e3f0;
struct cSPVector3_s0043_e3f0 {
    float x, y, z;
    cSPVector3_s0043_e3f0() {}
    cSPVector3_s0043_e3f0(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    cSPVector3_s0043_e3f0(const cSPVector3_s0043_e3f0& v) : x(v.x), y(v.y), z(v.z) {}
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
cSPVector3_s0043_e3f0 operator-(const cSPVector3_s0043_e3f0& a, const cSPVector3_s0043_e3f0& b);   // 0x41db10
float Length(const cSPVector3_s0043_e3f0& v);                                // VectorLength 0x40ae50
struct cSPMatrix3_s0043_e3f0 {                      // rw::math::fpu::Matrix33Template<float,0>
    cSPVector3_s0043_e3f0 r[3];
    cSPMatrix3_s0043_e3f0() {}
    cSPMatrix3_s0043_e3f0(const cSPMatrix3_s0043_e3f0& o);     // Matrix3::Assign (0x41cb40), out of line
    const cSPVector3_s0043_e3f0& operator[](int i) const { return r[i]; }
};
struct cSPBoundingBox_s0043_e3f0 {
    cSPVector3_s0043_e3f0 mMin, mMax;
    cSPBoundingBox_s0043_e3f0();                                  // BoundingBox_Reset 0x409c00
    cSPBoundingBox_s0043_e3f0(const cSPBoundingBox_s0043_e3f0& o);           // 0x511140
    void Extend(const cSPVector3_s0043_e3f0& p);                  // BoundingBox::Extend 0x41bd50
    bool IsEmpty() const { return mMin[0] > mMax[0]; }
    void Add(const cSPBoundingBox_s0043_e3f0& o);                 // 0x43f050
    cSPVector3_s0043_e3f0 GetCorner(uint32_t mask) const;         // 0x43f290
};
namespace SP {
struct cPropertyList_s0043_e3f0 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6();
    virtual bool HasProperty(uint32_t id);  // 0x006a2470 (SP::cPropertyList::HasProperty)
};
}
namespace SP {
struct cMWModel_s0043_e3f0 { char pad[0x44]; bitset_s0043_e3f0<64> mGroups; };
}
namespace SP {
struct cSPEditorModel_s0043_e3f0 {
    float GetScale();       // 0x4adaa0
    bool Func4adb80();      // 0x4adb80
    bool Func4adbc0();      // 0x4adbc0
    bool Func4adc40();      // 0x4adc40 (symmetry enabled?)
};
}
namespace SP {
struct cSPEditorHandle_s0043_e3f0 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
    virtual void Update();                 // vtable +0x2c
};
}
namespace SP {
struct cSPEditorHandleRotationRing_s0043_e3f0 : cSPEditorHandle_s0043_e3f0 {
    char pad[0x92 - 4]; bool mbHidden;     // +0x92
    bool IsHidden() const { return mbHidden; }
};
}
namespace SP {
struct cSPEditorHandleRotationBall_s0043_e3f0 : cSPEditorHandle_s0043_e3f0 {};
}
namespace SP {
struct cSPEditorHandleDeform_s0043_e3f0 : cSPEditorHandle_s0043_e3f0 {
    char pad04[0x8c - 4];
    uint32_t mAnimationID;                 // +0x8c  (mData.mAnimationID)
    cSPVector3_s0043_e3f0 mStartPt;                   // +0x90
    cSPVector3_s0043_e3f0 mEndPt;                     // +0x9c
    char padA8[0x180 - 0xa8];
    float mDelta;                          // +0x180
    char pad184[0x1d4 - 0x184];
    bool mIsHiddenHandle;                  // +0x1d4
    bool mDoNotPlaceHandle;                // +0x1d5
    float GetDelta() const { return mDelta; }
};
}
namespace SP {
struct cSPEditorBlock_s0043_e3f0;
}
namespace SP {
struct BlockList_s0043_e3f0 : vector_s0043_e3f0<AutoRefCount_s0043_e3f0<cSPEditorBlock_s0043_e3f0> > { bool Func526430(); };  // SP::GetResourceTypeFromModelType (folded)
}
namespace SP {
struct cSPEditorBlock_s0043_e3f0 {
    char pad00[0x0c];
    AutoRefCount_s0043_e3f0<cPropertyList_s0043_e3f0> mPropList;                     // +0x0c
    AutoRefCount_s0043_e3f0<cMWModel_s0043_e3f0> mModel;                             // +0x10
    char pad14[0x28 - 0x14];
    cSPEditorModel_s0043_e3f0* mEditorModel;                              // +0x28
    char pad2c[0x48 - 0x2c];
    cSPVector3_s0043_e3f0 mPosition;                                      // +0x48
    char pad54[0x154 - 0x54];
    AutoRefCount_s0043_e3f0<cSPEditorHandleRotationRing_s0043_e3f0> mRotationRingHandles[3];   // +0x154
    AutoRefCount_s0043_e3f0<cSPEditorHandleRotationBall_s0043_e3f0> mRotationBallHandle;       // +0x160
    char pad164[0x1b0 - 0x164];
    int mHandleIndex[4];                                       // +0x1b0
    char pad1c0[0x1d4 - 0x1c0];
    float mField1d4;                                           // +0x1d4
    float mScale;                                              // +0x1d8
    char pad1dc[0x218 - 0x1dc];
    float mRangeMin;                                           // +0x218
    float mRangeMax;                                           // +0x21c
    float mTolA, mTolB, mTol228, mTolC;                        // +0x220
    char pad230[0x340 - 0x230];
    BlockList_s0043_e3f0 mChildBlockList;                                 // +0x340
    char pad350[0x3c9 - 0x350];
    bool mField3c9;                                            // +0x3c9
    char pad3ca[0x3e0 - 0x3ca];
    AutoRefCount_s0043_e3f0<cSPEditorBlock_s0043_e3f0> mSymmetricBlock;              // +0x3e0
    char pad3e4[0x3ec - 0x3e4];
    AutoRefCount_s0043_e3f0<cSPEditorBlock_s0043_e3f0> mField3ec;                    // +0x3ec
    char pad3f0[0x448 - 0x3f0];
    float mField448;                                           // +0x448
    float mField44c;                                           // +0x44c
    char pad450[0x604 - 0x450];
    uint32_t mField604;                                        // +0x604
    uint32_t mField608;                                        // +0x608
    char pad60c[0x6cc - 0x60c];
    vector_s0043_e3f0<AutoRefCount_s0043_e3f0<cSPEditorHandleDeform_s0043_e3f0> > mDeformationHandles;   // +0x6cc
    char pad6dc[0x704 - 0x6dc];
    vector_s0043_e3f0<float> mSavedHandleDeltas;                          // +0x704
    char pad714[0x73c - 0x714];
    vector_s0043_e3f0<uint32_t> mSavedHandleAnimIDs;                      // +0x73c
    char pad74c[0xdc8 - 0x74c];
    bitset_s0043_e3f0<60> mFlags;                                         // +0xdc8
    cSPFadeController mFader;                                  // +0xdd0
    char padfade[0xde4 - 0xdd1];
    uint32_t mFadeArg;                                         // +0xde4
    char padde8[0xdf4 - 0xde8];
    int mFadeId;                                               // +0xdf4

    float GetRangeMin() const { return mRangeMin; }
    float GetRangeMax() const { return mRangeMax; }
    cSPEditorModel_s0043_e3f0* GetEditorModel() const { return mEditorModel; }

    // slice s0043bbc0
    bool F_43bbc0(int);  // 0x0043bbc0 (SP::cSPEditorBlock::F_43bbc0)
    void F_43bc40(float v);  // 0x0043bc40 (SP::cSPEditorBlock::F_43bc40)
    bool F_43bc70(float a, float b);  // 0x0043bc70 (SP::cSPEditorBlock::F_43bc70)
    bool F_43bcf0(float a, float b);  // 0x0043bcf0 (SP::cSPEditorBlock::F_43bcf0)
    void F_43bd50(cSPVector3_s0043_e3f0 v, float s);  // 0x0043bd50 (SP::cSPEditorBlock::F_43bd50)
    bool F_43bd80(cSPMatrix3_s0043_e3f0 m, float s);  // 0x0043bd80 (SP::cSPEditorBlock::F_43bd80)
    bool F_43bf20(uint32_t out);  // 0x0043bf20 (SP::cSPEditorBlock::F_43bf20)
    void F_43bf90(uint32_t bit, bool on);  // 0x0043bf90 (SP::cSPEditorBlock::F_43bf90)
    int F_43c040();  // 0x0043c040 (SP::cSPEditorBlock::F_43c040)
    int F_43c0a0();  // 0x0043c0a0 (SP::cSPEditorBlock::F_43c0a0)
    int F_43c120(uint32_t id);  // 0x0043c120 (SP::cSPEditorBlock::F_43c120)
    cSPEditorHandleDeform_s0043_e3f0* F_43c1a0();  // 0x0043c1a0 (SP::cSPEditorBlock::F_43c1a0)
    cSPEditorHandleDeform_s0043_e3f0* F_43c1e0();  // 0x0043c1e0 (SP::cSPEditorBlock::F_43c1e0)
    cSPEditorHandleDeform_s0043_e3f0* F_43c210();  // 0x0043c210 (SP::cSPEditorBlock::F_43c210)
    cSPEditorHandleDeform_s0043_e3f0* F_43c240();  // 0x0043c240 (SP::cSPEditorBlock::F_43c240)
    cSPEditorHandleDeform_s0043_e3f0* F_43c270(int i);  // 0x0043c270 (SP::cSPEditorBlock::F_43c270)
    float F_43c2d0(uint32_t i);  // 0x0043c2d0 (SP::cSPEditorBlock::F_43c2d0)
    uint32_t F_43c340(uint32_t i);  // 0x0043c340 (SP::cSPEditorBlock::F_43c340)
    int F_43c3d0(cSPEditorHandleDeform_s0043_e3f0* c);  // 0x0043c3d0 (SP::cSPEditorBlock::F_43c3d0)
    bool F_43c450(cSPEditorHandleDeform_s0043_e3f0* c, float f, float* a, bool b);  // 0x0043c450 (SP::cSPEditorBlock::F_43c450)
    bool F_43c510();  // 0x0043c510 (SP::cSPEditorBlock::F_43c510)
    void F_43c710();  // 0x0043c710 (SP::cSPEditorBlock::F_43c710)
    bool F_43ca10();  // 0x0043ca10 (SP::cSPEditorBlock::F_43ca10)
    void F_43d690(int idx, float f, float* a, bool b, bool one);   // 0x43d690
    // slice s0043e3f0
    void F_43e3f0(float dt, uint32_t index);
    void F_43e760(uint32_t index);
    void F_43e7e0(uint32_t index, bool b);
    bool F_43e8d0(int id);
    bool F_43e920();
    void F_43e940(uint32_t a, uint32_t b, int id);
    void F_43e9c0();
    void F_43ea20();
    void F_43ea40(int id);
    void F_43eaa0(int id);
    void F_43eae0(float v);
    void F_43eb50(float v);
    bool F_43ebc0();
    bool F_43ecb0();
    cSPBoundingBox_s0043_e3f0 F_43eef0();
    float F_43f250();
    float F_43eed0();                      // 0x43eed0
    float F_43f3a0();                      // 0x43f3a0
    void F_440110(float v);                // 0x440110
    void F_440390(float v);                // 0x440390
    void F_449ce0();                       // 0x449ce0
    cSPBoundingBox_s0043_e3f0 GetBBox(bool a, bool b, bool c);   // SP::cSPEditorBlock::GetBBox 0x44ae00
};
}
inline float Clamp(float x, float lo, float hi)
{
    __asm {
        movss xmm0, x
        maxss xmm0, lo
        minss xmm0, hi
        movss x, xmm0
    }
    return x;
}
// ---- items of slice s0043e3f0 end

// ---- items of slice s0043f3a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct Matrix3_s0043_f3a0 {
    float m[9];
    Matrix3_s0043_f3a0() {}
    Matrix3_s0043_f3a0(const Matrix3_s0043_f3a0&);          // 0041CB40
};
}
namespace SP {
struct DefaultRefCounted { void Release(); };
}
namespace SP {
struct BitSet60_s0043_f3a0 {
    uint32_t data[2];
    bool Get(int i) {
        if (i < 60) return (data[i >> 5] & (1u << (i % 32))) != 0;
        return false;
    }
};
}
namespace SP {
struct cSPEditorBlock_s0043_f3a0 {
    char             pad00[0x28];
    Node*            node;        // +0x28
    char             pad2c[0x33C - 0x2C];
    cSPEditorBlock_s0043_f3a0*  link33c;     // +0x33C
    struct PtrVec {
        cSPEditorBlock_s0043_f3a0** begin;
        cSPEditorBlock_s0043_f3a0** end;
        int size() const { return (int)(end - begin); }
    }                vec340;      // +0x340
    char             pad348[0x3E0 - 0x348];
    cSPEditorBlock_s0043_f3a0*  link3e0;     // +0x3E0
    char             pad3e4[0x3EC - 0x3E4];
    void*            p3ec;        // +0x3EC
    char             pad3f0[0x454 - 0x3F0];
    float            f454;        // +0x454
    char             pad458[0xDC8 - 0x458];
    BitSet60_s0043_f3a0         bits;        // +0xDC8

    float F3eed0();                            // 0043EED0
    float F3f250();                            // 0043F250
    cSPBoundingBox_s0043_e3f0 F3eef0();        // 0043EEF0
    void  F404f0(Matrix3_s0043_f3a0 m);         // 004404F0
    void  F40420(float v, uint8_t b);          // 00440420
    void  F40520(float v, uint8_t b, int c);   // 00440520
    void  F3a5e0(int type, uint8_t a, uint8_t b, char c);  // 0043A5E0
    void  SetValid(char valid, int arg);       // 0043F6B0 0x0043f6b0
    bool  F3fc20(void* pos);                   // 0043FC20

    float F3a0();                              // 0043F3A0
    float F3f0();                              // 0043F3F0
    float F4d0();                              // 0043F4D0
    void  F5b0(Vec3* out, float a, float b, float c, int flag);  // 0043F5B0
    void  FFa0(Matrix3_s0043_f3a0 m);                     // 0043FFA0
    void  F4020(float v, uint8_t b);           // 00440020
    void  F4090(float v, uint8_t b);           // 00440090
    bool  F49b340();                           // 0049B340
};
}
namespace SP {
void  Matrix3_Assign(Matrix3_s0043_f3a0* dst, const Matrix3_s0043_f3a0* src);       // 0041CB40
}
namespace SP {
Matrix3_s0043_f3a0 Sub_4A8E10(const void* a, int b);                                // 004A8E10
}
namespace SP {
int   Sub_493640(void* v, float f);
}
namespace SP {
void  Sub_4ADC20(int v);
}
// ---- items of slice s0043f3a0 end

// ---- items of slice s00440110 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct Matrix3_s0044_0110 { float m[9]; Matrix3_s0044_0110() {} Matrix3_s0044_0110(const Matrix3_s0044_0110&); };
}
namespace SP {
struct Trans {
    uint32_t flag;   // +0x00
    Vec3     a;      // +0x04
    Vec3     b;      // +0x10
    Trans();
    Trans(const Trans& o);
};
}
namespace SP {
struct Transform_s0044_0110 {
    uint16_t mFlags;        // +0x00
    uint16_t mChangeCount;  // +0x02
    Vector3P mOffset;       // +0x04
    float mScale;           // +0x10
    void SetOffset(const Vector3P& offset)
    {
        mOffset = offset;
        mFlags |= 4;
        mChangeCount++;
    }
    void SetScale(float scale)
    {
        mScale = scale;
        mChangeCount++;
    }
};
}
namespace SP {
template <int N>
struct bitset_s0044_0110 {
    uint32_t mWord[(N + 31) / 32];
    __forceinline bool test(uint32_t n) const
    {
        if (n < N) {
            const uint32_t word = mWord[n >> 5];
            return (word & (1u << (n % 32))) != 0;
        }
        return false;
    }
};
}
namespace SP {
__forceinline float Clamp_s0044_0110(float value, float minValue, float maxValue)
{
    __asm {
        movss xmm0, value
        maxss xmm0, minValue
        minss xmm0, maxValue
        movss value, xmm0
    }
    return value;
}
}
namespace SP {
inline float InverseLerp(float value, float lo, float hi) { return (value - lo) / (hi - lo); }
}
namespace SP {
class cMWModel_s0044_0110;
}
namespace SP {
class IModelWorld_s0044_0110 {
public:
    virtual int AddRef(); virtual int Release();
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual void v3c(); virtual void v40(); virtual void v44();
    virtual void v48(); virtual void v4c(); virtual void v50(); virtual void v54();
    virtual void v58(); virtual void v5c(); virtual void v60(); virtual void v64();
    virtual void v68(); virtual void v6c(); virtual void v70();
    virtual void MoveToTime(cMWModel_s0044_0110* model, uint32_t animID, float time, int animationGroup);   // 0x74
    virtual void v78(); virtual void v7c();
    virtual void GetAnimationRange(cMWModel_s0044_0110* model, uint32_t animID, float* start, float* end, int animationGroup);  // 0x80
    virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4(); virtual void vb8(); virtual void vbc();
    virtual void vc0(); virtual void vc4(); virtual void vc8(); virtual void vcc();
    virtual void vd0(); virtual void vd4(); virtual void vd8(); virtual void vdc();
    virtual void ve0(); virtual void ve4(); virtual void ve8(); virtual void vec();
    virtual void vf0(); virtual void vf4(); virtual void vf8(); virtual void vfc();
    virtual void v100(); virtual void v104(); virtual void v108();
    virtual void UpdateModel(cMWModel_s0044_0110* model, int arg);                   // 0x10C
    virtual void ApplyModel(cMWModel_s0044_0110* model, int arg);                    // 0x110
};
}
namespace SP {
class cMWModel_s0044_0110 {
public:
    IModelWorld_s0044_0110* mpWorld;   // +0x00
    uint32_t mFlags;        // +0x04
    Transform_s0044_0110 mTransform;   // +0x08
};
}
namespace SP {
class IPropList {
public:
    virtual int AddRef(); virtual int Release();
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18();
    virtual bool HasKey(uint32_t key);                                    // 0x1C
};
}
namespace SP {
class cSPEditorHandle_s0044_0110 {
public:
    virtual int AddRef();          // 0x00
    virtual int Release();         // 0x04 0x0051e380
    virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void Update();         // 0x14
    bool IsFlagSet();              // 0x0047F290
};
}
namespace SP {
class cSPEditorHandleRotationRing_s0044_0110 : public cSPEditorHandle_s0044_0110 {
public:
    void UpdateAnimTime();         // 0x00485650
    void ApplyAnimTime();          // 0x00485550
};
}
namespace SP {
struct cSPEditorBlock_s0044_0110 {
    char        pad00[0xC];
    AutoRefCount<IPropList> mPropList;  // +0x0C
    union {
        void*       mModel;      // +0x10
        AutoRefCount<cMWModel_s0044_0110> mpModel;
    };
    char        pad14[0x18 - 0x14];
    union {
        void*       p18;         // +0x18
        AutoRefCount<IModelWorld_s0044_0110> mpModelWorld;
    };
    char        pad1c[0x2C - 0x1c];
    bool        mIsFullInit;     // +0x2C
    char        pad2d[0x48 - 0x2D];
    Vector3     mPosition;       // +0x48
    char        pad54[0x154 - 0x54];
    AutoRefCount<cSPEditorHandleRotationRing_s0044_0110> mRotationRingHandles[3]; // +0x154
    AutoRefCount<cSPEditorHandle_s0044_0110> mRotationBallHandle;                 // +0x160
    char        pad164[0x168 - 0x164];
    uint32_t    mVertebraAnimID; // +0x168
    char        pad16c[0x1A8 - 0x16C];
    bool        field_1A8;       // +0x1A8
    char        pad1a9[0x1D4 - 0x1A9];
    float       mDefaultMouseOffset; // +0x1D4
    float       mUniformScale;   // +0x1D8
    char        pad1dc[4];
    float       mMinUniformScale; // +0x1E0
    float       mMaxUniformScale; // +0x1E4
    char        pad1e8[0x33C - 0x1E8];
    cSPEditorBlock_s0044_0110* link33c; // +0x33C
    char        pad340[0x3EC - 0x340];
    void*       p3ec;        // +0x3EC
    AutoRefCount<cMWModel_s0044_0110> mpSocketConnectorModel; // +0x3F0
    char        pad3f4[0x40C - 0x3F4];
    char        pad40c[0x4C8 - 0x40C];
    void*       list4c8;     // +0x4C8
    void*       list4cc;     // +0x4CC
    char        pad4d0[0x5F8 - 0x4D0];
    Vec3        v5f8;        // +0x5F8
    char        pad604[0xDC8 - 0x604];
    bitset_s0044_0110<60>  mBooleanAttributes; // +0xDC8

    Vector3 GetSocketConnectorPosition();       // 0x0043E080
    Vec3* F40b90(Vec3* out);                    // 00440B90
    void  F40bc0(const Vec3* v);                // 00440BC0
    void  F40c00(float f);                      // 00440C00
    void  F40c40(void* item, int flag);         // 00440C40
    bool  F40d80(void* out);                    // 00440D80
    void  F40e00(cSPEditorBlock_s0044_0110* o);            // 00440E00
    void  F40e60(void* key);                    // 00440E60
    void  F40390(float f);                      // 00440390
    void  F40420(float f, char b);              // 00440420
    void  F404f0(Matrix3_s0044_0110 m);                    // 004404F0
    void  F40110(float f);                      // 00440110
    void  SetUniformScale(float scale, bool b, bool force);   // 00440520
    void  SetFlag(int a, int b);                // 00435A10
};
}
namespace SP {
void  Sub_698650(void* m);
}
namespace SP {
extern const Vec3 g_v3_241c;   // 015D241C
}
// ---- items of slice s00440110 end

// ---- items of slice s00441080 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct Elem { void* p; char pad[0x1C]; };   // 0x20-byte element
}
namespace SP {
struct cSPEditorBlock_s0044_1080 {
    char  pad0[0x4C8];
    Elem* begin48;     // +0x4C8
    Elem* end4cc;      // +0x4CC

    void F41080();                                     // 0441080
    void F40e60(void* p);                              // 0440E60
    void F410d0(int idx, int a3, int a4, int a5, int a6, int a7, int a8, int a9,
                int a10, int a11);                      // 04410D0
};
}
// ---- items of slice s00441080 end

// ---- items of slice s00441440 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const bool kDefaultBoolValue;    // 0x015d115d
extern const float kDefaultFloatValue;  // 0x015d1168
extern const uint32_t kEditorModelGroupID;  // 0x015d22e8
#pragma intrinsic(fabs)
void* operator new(unsigned int size, const char* pName, int flags, unsigned debugFlags,
                   const char* file, int line);
struct Vector3_s0044_1440 {
    float x, y, z;
    Vector3_s0044_1440() {}
    Vector3_s0044_1440(float a, float b, float c) : x(a), y(b), z(c) {}
    float& operator[](int i) { return (&x)[i]; }
};
struct Matrix33 {
    float m[9];
};
struct Matrix3_s0044_1440 {
    Vector3_s0044_1440 m[3];
    Matrix3_s0044_1440() {}
    Matrix3_s0044_1440(const Matrix33& other);  // 0x0041cb40
};
struct BoundingBox {
    Vector3_s0044_1440 mMin;
    Vector3_s0044_1440 mMax;
    BoundingBox();  // 0x00409c00
};
Vector3_s0044_1440 operator*(const Vector3_s0044_1440& v, const float& s);           // 0x0041dca0
Vector3_s0044_1440 operator*(const float& s, const Vector3_s0044_1440& v);           // 0x0041de40
Vector3_s0044_1440 operator-(const Vector3_s0044_1440& a, const Vector3_s0044_1440& b);         // 0x0041db10
Vector3_s0044_1440 operator+(const Vector3_s0044_1440& a, const Vector3_s0044_1440& b);         // 0x0041dc10
float VectorLength(const Vector3_s0044_1440& v);                          // 0x0040ae50
Matrix33 Matrix33FromEulerXYZ(const Vector3_s0044_1440& eulerRadians);    // 0x00453920
extern const Vector3_s0044_1440 kVector3Zero;      // 0x015d255c
extern const Matrix3_s0044_1440 kMatrix3Identity;  // 0x015d2428
inline float Abs(float x) { return (float)fabs(x); }
inline float Clamp_s0044_1440(float x, float lo, float hi)
{
    float t = x;
    t = (t > lo) ? t : lo;
    t = (t < hi) ? t : hi;
    return t;
}
struct Transform_s0044_1440 {
    uint16_t mFlags;        // +0x00
    uint16_t mChangeCount;  // +0x02
    Vector3_s0044_1440 mOffset;        // +0x04
    float mScale;           // +0x10
    Matrix3_s0044_1440 mRotation;      // +0x14

    Transform_s0044_1440();                                  // 0x00409930
    Transform_s0044_1440& operator=(const Transform_s0044_1440& other); // 0x00537dc0
    void Accumulate(const Transform_s0044_1440& other);      // 0x0040ccb0
    void AccumulateScaled(const Transform_s0044_1440& other);// 0x0040cd80

    void SetOffset(const Vector3_s0044_1440& offset)
    {
        mOffset = offset;
        mFlags |= 4;
        mChangeCount++;
    }
    void SetRotation(const Matrix3_s0044_1440& rotation)
    {
        mRotation = rotation;
        mFlags |= 2;
        mChangeCount++;
    }
};
struct BoneTransform_s0044_1440 {
    float m[12];
};
void BoneTransformToTransform(const BoneTransform_s0044_1440* src, Transform_s0044_1440* dst);  // 0x00732270
struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};
template <int N>
struct bitset_s0044_1440 {
    uint32_t mWord[(N + 31) / 32];

    __forceinline bool test(uint32_t n) const
    {
        if (n < N)
            return (mWord[n >> 5] & (1u << (n % 32))) != 0;
        return false;
    }
    __forceinline void set(uint32_t n, bool value)
    {
        if (n < N) {
            if (value)
                mWord[n >> 5] |= 1u << (n % 32);
            else
                mWord[n >> 5] &= ~(1u << (n % 32));
        }
    }
};
template <class T, int N>
struct fixed_vector_s0044_1440 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[3];
    uint32_t mBuffer[(N * sizeof(T)) / 4];

    fixed_vector_s0044_1440() {}
    explicit fixed_vector_s0044_1440(unsigned int n);  // out of line (0x0041d0c0 / 0x0041d510)
    ~fixed_vector_s0044_1440()
    {
        for (T* p = mpBegin; p < mpEnd; ++p)
            p->~T();
        DoFree();
    }
    void DoFree();  // out of line (0x004c0b80 / 0x00428130)

    int size() const { return (int)(mpEnd - mpBegin); }
    bool empty() const;               // out of line (0x00526430, ICF-shared)
    T& operator[](int i) { return mpBegin[i]; }
    T* erase(T* first, T* last);      // out of line
    void resize(unsigned int n);      // out of line
    void push_back(const T& value);   // out of line
    void clear() { erase(mpBegin, mpEnd); }
};
template <class T>
struct AutoRefCount_s0044_1440 {
    T* mpObject;

    AutoRefCount_s0044_1440& operator=(T* pObject)
    {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
struct FixedString32 {
    uint32_t mData[13];
    FixedString32& operator=(const char* p);  // 0x00453690
};
struct Property {
    void* mpData;        // +0x00 (array data, or the inline value itself)
    uint32_t pad04;
    int mnItemCount;     // +0x08
    uint32_t pad0c;
    uint16_t mnFlags;    // +0x10 (0x30 = array)
    uint16_t mnType;     // +0x12

    void* GetValuePtr();     // 0x00446ff0
    int* GetValueInt32();    // 0x0041e990

    int GetItemCount()
    {
        if (mnFlags & 0x30)
            return mnItemCount;
        else if (mnType != 0)
            return 1;
        return 0;
    }
    void* GetItems()
    {
        if (mnFlags & 0x30)
            return mpData;
        else if (mnType != 0)
            return this;
        return 0;
    }
};
const ResourceKey* GetDefaultKeyValue();   // 0x006bb640
const Vector3_s0044_1440* GetDefaultVector3Value();   // 0x006bb5e0
__forceinline const bool* GetValueBool(Property* p)
{
    return (p->mnType == 1 || p->mnType == 0x10) ? (const bool*)p->GetValuePtr() : &kDefaultBoolValue;
}
__forceinline const float* GetValueFloat(Property* p)
{
    return (p->mnType == 0xd || p->mnType == 0x10) ? (const float*)p->GetValuePtr() : &kDefaultFloatValue;
}
__forceinline const ResourceKey* GetValueKey(Property* p)
{
    return (p->mnType == 0x20 || p->mnType == 0x10) ? (const ResourceKey*)p->GetValuePtr() : GetDefaultKeyValue();
}
__forceinline const Vector3_s0044_1440* GetValueVector3(Property* p)
{
    return (p->mnType == 0x31 || p->mnType == 0x10) ? (const Vector3_s0044_1440*)p->GetValuePtr() : GetDefaultVector3Value();
}
class cPropertyList_s0044_1440 {
public:
    virtual int AddRef();
    virtual int Release();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void SetProperty(uint32_t id, const Property* p);  // 0x006a2e20 (cPropertyList::SetProperty)
    virtual int RemoveProperty(uint32_t id);  // 0x006a2ef0 (cPropertyList::RemoveProperty)
    virtual bool HasProperty(uint32_t id);                       // 0x1c 0x006a2470
    virtual bool GetPropertyAlt(uint32_t id, Property*& result); // 0x20
    virtual bool GetProperty(uint32_t id, Property*& result);    // 0x24
    virtual Property* GetPropertyObject(uint32_t id);            // 0x28
};
bool GetBoolProperty(cPropertyList_s0044_1440* list, uint32_t id, bool& value);              // 0x00407190
bool GetFloatProperty(cPropertyList_s0044_1440* list, uint32_t id, float& value);            // 0x0040cf10
bool TryGetUIntProperty(cPropertyList_s0044_1440* list, uint32_t id, uint32_t& value);       // 0x00410370
bool GetPropertyAsKey(cPropertyList_s0044_1440* list, uint32_t id, ResourceKey& value);      // 0x006a1250
bool GetPropertyAsKeyInstance(cPropertyList_s0044_1440* list, uint32_t id, uint32_t& value); // 0x006a12a0
bool GetPropertyAsVector3(cPropertyList_s0044_1440* list, uint32_t id, Vector3_s0044_1440& value);      // 0x006a1110
bool GetPropertyAsChar8Ptr(cPropertyList_s0044_1440* list, uint32_t id, const char*& value); // 0x006a1450
inline bool GetIntProperty(cPropertyList_s0044_1440* list, uint32_t id, int& value)
{
    Property* prop;
    if (list && list->GetProperty(id, prop) && prop->mnType == 9) {
        value = *prop->GetValueInt32();
        return true;
    }
    return false;
}
template <int N>
inline void CopyKeys(fixed_vector_s0044_1440<ResourceKey, N>& dst, int count, const ResourceKey* keys)
{
    dst.resize(count);
    for (int i = 0; i < count; i++)
        dst[i] = keys[i];
}
class IUnknown32 {
public:
    virtual int AddRef();
    virtual int Release();
};
class IModelWorld_s0044_1440;
struct cMWModel_s0044_1440 {
    IModelWorld_s0044_1440* mpWorld;                 // +0x00
    bitset_s0044_1440<32> mFlags;                    // +0x04
    Transform_s0044_1440 mTransform;                 // +0x08
    int mnRefCount;                       // +0x40
    bitset_s0044_1440<64> mGroupFlags;               // +0x44
    float mColor[4];                      // +0x4c
    bool field_5C;                        // +0x5c
    uint8_t mCollisionMode;               // +0x5d
    uint8_t pad5e[2];
    int field_60;                         // +0x60
    AutoRefCount_s0044_1440<IUnknown32> mpOwner;     // +0x64
    uint32_t pad68[2];
    BoundingBox mDefaultBBox;             // +0x70
    uint32_t pad88[2];
    cPropertyList_s0044_1440* mpPropList;            // +0x90

    int AddRef() { return ++mnRefCount; }
    int Release();                        // 0x0040f360
    void SetVisible(bool visible);        // 0x00437f70
};
class IModelWorld_s0044_1440 {
public:
    virtual int AddRef();                                                     // 0x00
    virtual int Release();                                                    // 0x04
    virtual void v08();
    virtual cMWModel_s0044_1440* CreateModel(uint32_t instanceID, uint32_t groupID, int flags);  // 0x0c
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54();
    virtual void StallUntilLoaded(cMWModel_s0044_1440* model);                           // 0x58
    virtual void v5c(); virtual void v60(); virtual void v64();
    virtual int GetNumAnimations(cMWModel_s0044_1440* model, int animationGroup);        // 0x68
    virtual int GetAnimationIDs(cMWModel_s0044_1440* model, uint32_t* dst, int animationGroup);  // 0x6c
    virtual void AnimAction(cMWModel_s0044_1440* model, uint32_t animID, int arg3, float arg4, int animationGroup);  // 0x70
    virtual void v74(); virtual void v78(); virtual void v7c(); virtual void v80();
    virtual int GetNumBones(cMWModel_s0044_1440* model);                                 // 0x84
    virtual int GetPoseTransforms(cMWModel_s0044_1440* model, BoneTransform_s0044_1440* dst, bool original);  // 0x88
    virtual int GetBoneTransforms(cMWModel_s0044_1440* model, BoneTransform_s0044_1440* dst);       // 0x8c
    virtual int GetBoneIDs(cMWModel_s0044_1440* model, uint32_t* dst);                   // 0x90
    virtual void v94(); virtual void v98(); virtual void v9c(); virtual void va0();
    virtual void va4(); virtual void va8(); virtual void vac(); virtual void vb0();
    virtual void vb4(); virtual void vb8(); virtual void vbc(); virtual void vc0();
    virtual void vc4(); virtual void vc8(); virtual void vcc(); virtual void vd0();
    virtual void SetExternalEffectsTransform(cMWModel_s0044_1440* model, const Transform_s0044_1440* t, uint32_t instanceID);  // 0xd4
    virtual void vd8(); virtual void vdc();
    virtual void ReleaseTransformedHull(int* hull);                           // 0xe0
    virtual void ve4();
    virtual int GetDeformationHandles(cMWModel_s0044_1440* model, void* dst, int count); // 0xe8
    virtual void vec(); virtual void vf0(); virtual void vf4(); virtual void vf8();
    virtual void vfc(); virtual void v100(); virtual void v104();
    virtual Transform_s0044_1440* GetMeshTransform(cMWModel_s0044_1440* model);                     // 0x108
    virtual void v10c(); virtual void v110(); virtual void v114(); virtual void v118();
    virtual void v11c(); virtual void v120(); virtual void v124(); virtual void v128();
    virtual void v12c(); virtual void v130(); virtual void v134(); virtual void v138();
    virtual void v13c(); virtual void v140(); virtual void v144(); virtual void v148();
    virtual void v14c(); virtual void v150(); virtual void v154(); virtual void v158();
    virtual void v15c(); virtual void v160(); virtual void v164(); virtual void v168();
    virtual bool SetInWorld(cMWModel_s0044_1440* model, bool inWorld);                   // 0x16c
};
class IModelManager {
public:
    virtual int AddRef();
    virtual int Release();
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual int GetGroupFlag(uint32_t groupID, int arg);  // 0x28
};
namespace SP {
 IModelManager* ModelManager();   // 0x0067dd80
}
class IBlockPropertySource {
public:
    virtual int AddRef();
    virtual int Release();
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual void v3c(); virtual void v40(); virtual void v44();
    virtual void v48(); virtual void v4c(); virtual void v50(); virtual void v54();
    virtual cPropertyList_s0044_1440* GetPropertyList(uint32_t instanceID, uint32_t groupID);  // 0x58
    virtual void v5c(); virtual void v60(); virtual void v64(); virtual void v68();
    virtual float GetPropertyListFloat(cPropertyList_s0044_1440* list);                      // 0x6c
};
IBlockPropertySource* BlockPropertySource();  // 0x00401010
namespace SP {
class cSPEditorBlock_s0044_1440;
}
namespace SP {
class cSPEditorHandle_s0044_1440 {
public:
    virtual int AddRef();          // 0x00
    virtual int Release();         // 0x04 0x0051e380
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18();
    virtual void Dispose();        // 0x1c
    virtual void SetScale(float scale);  // 0x20
};
}
namespace SP {
class cSPEditorHandleBallConnector_s0044_1440 : public cSPEditorHandle_s0044_1440 {
public:
    uint32_t mData[(0x50 - 4) / 4];
    cSPEditorHandleBallConnector_s0044_1440();   // 0x0047f4b0
    void Init(cSPEditorBlock_s0044_1440* block); // 0x0047f720
};
}
namespace SP {
class cSPEditorHandleRotationBall_s0044_1440 : public cSPEditorHandle_s0044_1440 {
public:
    uint32_t pad04[(0x5d - 4) / 4];
    uint8_t pad58[5];
    bool mIsHidden;                   // +0x5d
    uint8_t pad5e[6];
    cSPEditorHandleRotationBall_s0044_1440();    // 0x00482f90
    void Init(IModelManager* modelMgr, cSPEditorBlock_s0044_1440* block, Vector3_s0044_1440 offset, bool fullInit);  // 0x00483350
};
}
namespace SP {
struct MorphHandleInfo {
    uint32_t mAnimID;
    Transform_s0044_1440 mTransform;
    uint32_t mData[8];
};
}
namespace SP {
class cSPEditorHandleDeform_s0044_1440 : public cSPEditorHandle_s0044_1440 {
public:
    uint32_t pad04[(0x180 - 4) / 4];
    float mDefaultWeight;             // +0x180
    uint32_t pad184[(0x1d8 - 0x184) / 4];
    cSPEditorHandleDeform_s0044_1440();          // 0x0047fa30
    void Init(IModelManager* modelMgr, cSPEditorBlock_s0044_1440* block, MorphHandleInfo* info, bool fullInit);  // 0x00480030
};
}
namespace SP {
class cSPEditorBlockHelper378 {
public:
    uint32_t mField0;
    IUnknown32* mpObject;
    uint32_t mData[(0x4c - 8) / 4];

    cSPEditorBlockHelper378();  // 0x004e8f70
    ~cSPEditorBlockHelper378()
    {
        if (mpObject)
            mpObject->Release();
    }
    void Shutdown();            // 0x004ae250
};
}
namespace SP {
struct cSPEditorBlockOwnerLink {
    uint32_t mData[0x38 / 4];
    void SetOwner(cSPEditorBlock_s0044_1440* block);  // 0x00433a80
};
}
namespace SP {
struct CapabilityLevel {
    bool mIsVariableLevel;
    int mMinLevel;
    int mMaxLevel;
    int mDefaultLevel;
};
}
namespace SP {
struct Capability {
    uint32_t mPropertyID;
    CapabilityLevel mLevel;
    Capability() : mPropertyID(0), mLevel() {}
};
}
namespace SP {
struct CapabilityPropertyDesc {
    uint32_t mPropertyID;
    uint32_t mUnk4;
    bool mIsVariableLevel;
};
}
namespace SP {
extern const CapabilityPropertyDesc kCapabilityProperties[0x5b];
}
namespace SP {
class RefCountVTemplate {
public:
    virtual int AddRef();
    virtual int Release();
    int mnRefCount;
};
}
namespace SP {
enum {
    kAttrOrientToSurfaces = 0x00,
    kAttrOrientWhenSnapped = 0x04,
    kAttrUseDummyBlocks = 0x05,
    kAttrIsVertebra = 0x07,
    kAttrIsPlantRoot = 0x08,
    kAttr09 = 0x09,
    kAttrUseSkin = 0x0a,
    kAttrHasBallAndSocket = 0x0b,
    kAttr0C = 0x0c,
    kAttrHasLeftFile = 0x0d,
    kAttrOnSymmetryPlane = 0x0f,
    kAttrRemainUpright = 0x11,
    kAttrMoveBottomEdgeToSurface = 0x12,
    kAttrPointForward = 0x13,
    kAttrIsNullBlock = 0x14,
    kAttrUseHullForBBox = 0x15,
    kAttrStayAboveGround = 0x16,
    kAttrHasSnapDownTo = 0x17,
    kAttrHideDeformHandles = 0x18,
    kAttrHideRotationHandles = 0x19,
    kAttrHasAlignLateralWith = 0x1a,
    kAttrHasAlignHeightWith = 0x1b,
    kAttrSnapToParentCenter = 0x1c,
    kAttrSnapToParentSnapVectors = 0x1d,
    kAttrSnapToCenterOfEditor = 0x1e,
    kAttrHasBallConnector = 0x1f,
    kAttrHasSocketConnector = 0x20,
    kAttrCellAllowOnTopOfBody = 0x21,
    kAttrPreferToBeOnPlaneOfSymmetry = 0x22,
    kAttrCanBeParentless = 0x23,
    kAttrBoundsCheckOnlyForDelete = 0x24,
    kAttrHasRotationBallHandle = 0x26,
    kAttrHasEffectBone = 0x27,
    kAttrActLikeFinOnPlaneOfSymmetry = 0x28,
    kAttrWarpCursorToPinPoint = 0x29,
    kAttrActsLikeGrasper = 0x2c,
    kAttrActsLikeFoot = 0x2d,
    kAttrUseHullForPicking = 0x2e,
    kAttrForcePinningAgainstType = 0x2f,
    kAttrAllowAsymmetricalRotationOnPlaneOfSymmetry = 0x30,
    kAttrCircularTopAlignment = 0x31,
    kAttrRemainUprightOnTop = 0x32,
    kAttrIsAllowedOutOfBounds = 0x33,
    kAttrDoNotFlipOnPlaneOfSymmetry = 0x34,
    kAttrHasAlignXYWith = 0x35,
    kAttrHasCSnapBone = 0x36,
    kAttrAllowTopBehaviors = 0x37,
    kAttrCellApplyBehaviorToUserRotation = 0x38,
    kAttrStartAsymmetric = 0x3b
};
}
namespace SP {
class cSPEditorBlock_s0044_1440 : public RefCountVTemplate, public IUnknown32 {
public:
    AutoRefCount_s0044_1440<cPropertyList_s0044_1440> mpPropList;          // +0x0c
    AutoRefCount_s0044_1440<cMWModel_s0044_1440> mpModel;                  // +0x10
    AutoRefCount_s0044_1440<cMWModel_s0044_1440> mpEffectsMaskModel;       // +0x14
    AutoRefCount_s0044_1440<IModelWorld_s0044_1440> mpModelWorld;          // +0x18
    uint32_t mInstanceID;                            // +0x1c
    uint32_t mGroupID;                               // +0x20
    int mBlockPack;                                  // +0x24
    void* mpEditorModel;                             // +0x28
    bool mIsFullInit;                                // +0x2c
    uint8_t pad2d[3];
    float field_30;                                  // +0x30
    bool mIsVisible;                                 // +0x34
    uint8_t pad35[3];
    uint32_t mUIState[4];                            // +0x38
    Vector3_s0044_1440 mPosition;                               // +0x48
    Vector3_s0044_1440 mHistoryPosition;                        // +0x54
    Matrix3_s0044_1440 mTotalOrientation;                       // +0x60
    Matrix3_s0044_1440 mOtherOrientations[5];                   // +0x84
    Vector3_s0044_1440 mSurfaceNormal;                          // +0x138
    Vector3_s0044_1440 mReplacePartDisplacement;                // +0x144
    int mSnapType;                                   // +0x150
    AutoRefCount_s0044_1440<cSPEditorHandle_s0044_1440> mAxisHandles[3];   // +0x154
    AutoRefCount_s0044_1440<cSPEditorHandleRotationBall_s0044_1440> mpRotationBallHandle;  // +0x160
    uint32_t mRotationRingHandleAnimID;              // +0x164
    uint32_t mVertebraAnimID;                        // +0x168
    float mRotationRingHandleCurrentUnscaledRadius;  // +0x16c
    uint32_t mTimer[6];                              // +0x170
    cSPEditorBlock_s0044_1440* mpClonedFrom;                    // +0x188
    uint32_t pad18c[6];
    int mTransformedHull;                            // +0x1a4
    bool field_1A8;                                  // +0x1a8
    bool field_1A9;                                  // +0x1a9
    uint8_t pad1aa[2];
    int field_1AC;                                   // +0x1ac
    uint32_t pad1b0[4];
    int mSymmetryType;                               // +0x1c0 (PDB setter: SetBaseJointScale)
    int field_1C4;                                   // +0x1c4
    int field_1C8;                                   // +0x1c8
    int mLimbType;                                   // +0x1cc
    float mMuscleScale;                              // +0x1d0
    float mBaseMuscleScale;                          // +0x1d4
    float mSize;                                     // +0x1d8
    float mSize2;                                    // +0x1dc
    float mModelMinScale;                            // +0x1e0
    float mModelMaxScale;                            // +0x1e4
    Vector3_s0044_1440 mModelDefaultMouseOffset;                // +0x1e8
    Matrix3_s0044_1440 mModelEditorInitialRotation;             // +0x1f4
    float mModelMinBallConnectorScale;               // +0x218
    float mModelMaxBallConnectorScale;               // +0x21c
    float mModelSymmetrySnapDelta;                   // +0x220
    float field_224;                                 // +0x224
    float mModelReplaceSnapDelta;                    // +0x228
    float mModelSymmetryRotationSnapAngle;           // +0x22c
    bool field_230;                                  // +0x230
    uint8_t pad231[3];
    uint32_t field_234[5];                           // +0x234
    int mModelNumberOfSnapAxes;                      // +0x248
    Transform_s0044_1440 mEffectsBoneTransform1;                // +0x24c
    Transform_s0044_1440 mEffectsBoneTransform2;                // +0x284
    int mEffectsBoneIndex;                           // +0x2bc
    Transform_s0044_1440 mCSnapBoneTransform1;                  // +0x2c0
    Transform_s0044_1440 mCSnapBoneTransform2;                  // +0x2f8
    int mCSnapBoneIndex;                             // +0x330
    uint32_t pad334[2];
    AutoRefCount_s0044_1440<cSPEditorBlock_s0044_1440> mpParent;           // +0x33c
    uint32_t mChildren[0x38 / 4];                    // +0x340
    cSPEditorBlockHelper378* mpHelper378;            // +0x378
    uint32_t pad37c[9];
    Vector3_s0044_1440 mTriangleDirection;                      // +0x3a0
    Vector3_s0044_1440 mTrianglePickOrigin;                     // +0x3ac
    int mPickingType;                                // +0x3b8
    int mModelForcePinningType;                      // +0x3bc
    uint32_t mModelPinningTypeGroup;                 // +0x3c0
    int field_3C4;                                   // +0x3c4
    bool mModelPinningAntiAliased;                   // +0x3c8
    uint8_t pad3c9[3];
    Vector3_s0044_1440 field_3CC;                               // +0x3cc
    uint32_t pad3d8[4];
    uint8_t pad3e8[4];
    AutoRefCount_s0044_1440<cSPEditorHandleBallConnector_s0044_1440> mpBallConnectorHandle;  // +0x3ec
    AutoRefCount_s0044_1440<cMWModel_s0044_1440> mpSocketConnectorModel;   // +0x3f0
    Vector3_s0044_1440 mModelMinSocketConnectorOffset;          // +0x3f4
    Vector3_s0044_1440 mModelMaxSocketConnectorOffset;          // +0x400
    Vector3_s0044_1440 mSocketConnectorOffset;                  // +0x40c
    Vector3_s0044_1440 mModelRotationBallHandleOffset;          // +0x418
    Vector3_s0044_1440 mModelPaletteRotation;                   // +0x424
    int mDeformAnimIndex;                            // +0x430
    uint32_t mDeformAnimID;                          // +0x434
    uint32_t pad438[6];
    float mModelBottomEdgeDistanceAdjustment;        // +0x450
    float mModelScale;                               // +0x454
    uint32_t mModelMinMuscleFile;                    // +0x458
    uint32_t mModelMaxMuscleFile;                    // +0x45c
    FixedString32 mModelSoundScale;                  // +0x460
    FixedString32 mModelSoundRotation;               // +0x494
    uint32_t mPaints[(0x5e4 - 0x4c8) / 4];           // +0x4c8
    uint32_t mModelPrice;                            // +0x5e4
    uint32_t mModelComplexityScore;                  // +0x5e8
    uint32_t mModelRunTimeBoneCount;                 // +0x5ec
    uint32_t mModelBakeLevel;                        // +0x5f0
    float field_5F4;                                 // +0x5f4
    ResourceKey mModelRigBlockType;                  // +0x5f8
    uint32_t mModelShowoffAnimation;                 // +0x604
    uint32_t mModelShowoffEffect;                    // +0x608
    uint32_t pad60c[(0x6cc - 0x60c) / 4];
    fixed_vector_s0044_1440<AutoRefCount_s0044_1440<cSPEditorHandleDeform_s0044_1440>, 8> mMorphHandles;  // +0x6cc
    fixed_vector_s0044_1440<float, 8> mMorphHandleWeights;      // +0x704
    fixed_vector_s0044_1440<uint32_t, 8> mMorphHandleChannels;  // +0x73c
    fixed_vector_s0044_1440<ResourceKey, 8> mModelSnapDownTo;   // +0x774
    fixed_vector_s0044_1440<ResourceKey, 8> mModelSnapToParentTypes;  // +0x7ec
    fixed_vector_s0044_1440<ResourceKey, 8> mModelStayAbove;    // +0x864
    fixed_vector_s0044_1440<ResourceKey, 8> mModelAlignLateralWith;   // +0x8dc
    fixed_vector_s0044_1440<ResourceKey, 8> mModelAlignHeightWith;    // +0x954
    fixed_vector_s0044_1440<ResourceKey, 8> mModelAlignXYWith;  // +0x9cc
    fixed_vector_s0044_1440<ResourceKey, 8> mModelTypesToInteractWith;  // +0xa44
    fixed_vector_s0044_1440<ResourceKey, 8> mModelTypesToSnapReplace;   // +0xabc
    fixed_vector_s0044_1440<ResourceKey, 16> mModelTypesNotToInteractWith;  // +0xb34
    fixed_vector_s0044_1440<Capability, 20> mCapabilities;      // +0xc0c
    uint32_t mFootType;                              // +0xdb4
    uint32_t mMouthType;                             // +0xdb8
    uint32_t mWeaponType;                            // +0xdbc
    uint32_t padDC0[2];
    bitset_s0044_1440<60> mBooleanAttributes;                   // +0xdc8
    cSPEditorBlockOwnerLink mOwnerLink;              // +0xdd0

    bool GetBooleanAttribute(int index) { return mBooleanAttributes.test(index); }

    bool BuildBlock(uint32_t instanceID, uint32_t groupID, IModelWorld_s0044_1440* pWorld,
                    cSPEditorBlock_s0044_1440* pParent, float field30, bool bInteractive,
                    bool bCreateModel, bool bModelFlag);

    // out-of-line callees (thiscall)
    void SetBooleanAttribute(int index, bool value);     // 0x00435a10
    void SetBaseJointScale(int value);                   // 0x0044e980 (writes +0x1c0)
    int GetBlockType(uint32_t instanceID);               // 0x0044e830
    bool Sub_44c5a0(int symmetryType);                   // 0x0044c5a0
    void SetScaleType(int limbType);                     // 0x0044f130 (writes +0x1cc)
    float GetDefaultScale();                             // 0x0044b5c0
    void ReleasePhysics();                               // 0x00451fe0
    void RebuildPhysics();                               // 0x00452040
    Vector3_s0044_1440 Sub_4364a0();                                // 0x004364a0
    void SetPosition(Vector3_s0044_1440 position, bool absolute);   // 0x004380a0
    void Sub_43ac40(int a, int b, int c);                // 0x0043ac40
    BoundingBox GetBBox(int mode, bool a, bool b);       // 0x0044ae00
    void CreateRotationRingHandle(int axis, uint32_t name, uint32_t allowHiddenProp,
                                  uint32_t axisProp, uint32_t rotationProp,
                                  uint32_t offsetProp, uint32_t scaleProp,
                                  uint32_t actLikeBallProp, uint32_t isHiddenProp,
                                  uint32_t unk);         // 0x004410d0
    void Sub_451e20(cSPEditorBlock_s0044_1440* parent);             // 0x00451e20
    void SetMorphHandleWeight(int index, float weight, int a, int b, int c);  // 0x0043d690
    void Sub_43e2b0();                                   // 0x0043e2b0
    void InitializeHandleData(cPropertyList_s0044_1440* propList);  // 0x00447150
    void Sub_43e0f0(int* animIndex);                     // 0x0043e0f0
    void Sub_448b80(int a);                              // 0x00448b80
    void Sub_449d40(BoundingBox* bbox);                  // 0x00449d40
    void CalculateSnapAxes();                            // 0x0044c690
    void Sub_4484f0();                                   // 0x004484f0
    void Sub_44b640(BoundingBox* bbox);                  // 0x0044b640
    void Sub_44b6b0();                                   // 0x0044b6b0
    void Sub_4485d0();                                   // 0x004485d0
    void Sub_44e7c0(int index);                          // 0x0044e7c0
};
}
bool Sub_492de0(SP::cSPEditorBlock_s0044_1440* block);  // 0x00492de0
float Sub_492e70(SP::cSPEditorBlock_s0044_1440* block, Vector3_s0044_1440* a, Vector3_s0044_1440* b, int* index, float scale,
                 bool flag);                  // 0x00492e70
    void operator delete(void*); // 0x00f47380
// ---- items of slice s00441440 end

// ---- items of slice s00446ff0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cSPTransform_s0044_6ff0 {
    unsigned short mFlags;
    unsigned short mModificationCount;
    float mTranslation[3];
    float mScale;
    float mRotation[9];
    void Init();
};
struct Elem_s0044_6ff0 {                          // stride 0x5c
    unsigned int mPad0;
    cSPTransform_s0044_6ff0 mTransform;
    char mPad1[0x5c - 4 - 0x38];
};
struct Target {
    void Apply(void* block, unsigned char param2);
};
struct Binder {
    char pad0[0x10];
    int mArg;                          // +0x10
    char pad1[4];
    void* mWorld;                      // +0x18
    char pad2[0x6cc - 0x1c];
    Target** mTargets;                 // +0x6cc
    void Method(unsigned char param2);
};
// ---- items of slice s00446ff0 end

// ---- items of slice s00448380 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Item;
struct Blk_s0044_8380 {
    char pad0[0x10];
    int m10;                 // +0x10
    int m14;                 // +0x14
    int m18;                 // +0x18
    int m1c;                 // +0x1c
    int m20;                 // +0x20
    char pad1[0x6cc - 0x24];
    Item** mItems;           // +0x6cc
    Item** mItemsEnd;        // +0x6d0
    char pad2[0xdc8 - 0x6d4];
    unsigned mBits;          // +0xdc8

    float A8380();
    bool A8480(int index, char flag);
    bool A84f0();
    void A85d0();  // 0x004485d0 (Blk::A85d0)
    void A8690(int a, int b, int c, int d);
    void A88c0();
    void A8a80();
    void A8b10();
    void A8b80(char flag);
    bool A8c10();
    void A8d60();
    void A8dd0();
    void A8e90(void* v, char flag);
};
struct Item {
    bool Apply(char flag);
    void Method();
    bool Other(char flag);
    void Release();
};
// ---- items of slice s00448380 end

// ---- items of slice s00449ed0 begin (TODO(rewrite): local stubs, replace by canonical classes)
template<int N> inline void ScratchSlots_s0044_9ed0() { uint32_t s[N]; }
struct V3 { float x, y, z; };            // plain POD (SSE copies / integer stores)
struct V3u {                             // cSPVector3-style with user copy ops (fld/fstp copies)
    float x, y, z;
    V3u() {}
    V3u(const V3u& o) { x = o.x; y = o.y; z = o.z; }
    V3u& operator=(const V3u& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
struct M3 { float m[9]; };               // plain POD: copied with rep movsd
struct Mat : M3 {                        // block member matrix (user operator=, still a block copy)
    Mat& operator=(const M3& o) { *(M3*)this = o; return *this; }
};
V3u __cdecl operator-(const V3u& a, const V3u& b);        // 0x0041db10
V3u __cdecl operator+(const V3u& a, const V3u& b);        // 0x0041dc10
V3u __cdecl operator*(const V3u& a, const float& s);      // 0x0041dca0
__declspec(align(16)) struct hkVec4 {
    float v[4];
    hkVec4() {}
    hkVec4(const hkVec4& o) { v[0] = o.v[0]; v[1] = o.v[1]; v[2] = o.v[2]; v[3] = o.v[3]; }
    hkVec4& operator=(const hkVec4& o) { v[0] = o.v[0]; v[1] = o.v[1]; v[2] = o.v[2]; v[3] = o.v[3]; return *this; }
};
struct hkRot {
    hkVec4 c0, c1, c2;
    const hkVec4& row(int i) const { return *(const hkVec4*)((const char*)this + (i << 4)); }
    void Assign(const hkRot& o);                          // 0x0044a8c0
};
struct hkTransformStub {
    hkRot rotation;
    hkVec4 translation;
};
struct hkMotionStub { char pad[0x10]; hkTransformStub transform; };
struct hkRigidBodyStub {
    char pad[0x58];
    hkMotionStub* mMotion;
    void setTransform(const hkTransformStub& t);          // 0x01087890
};
struct BBox {
    V3u mMin, mMax;
    BBox() {}
    BBox(const BBox&);                                     // 0x00511140
    void Reset();                                          // 0x00409c00
    void GetCenter(V3u* out) const;                         // 0x00409b90
    void SetCenterRadius(const V3* c, float r);            // 0x00409ce0
    void TransformBy(const struct Xform* x);               // 0x00409dd0
    void Scale(float s);                                   // 0x0044ad00
    float MinAt(int i) const { return (&mMin.x)[i]; }
    float MaxAt(int i) const { return (&mMax.x)[i]; }
    bool IsInverted() const { return MinAt(0) > MaxAt(0); }
    bool IsUnbounded() const { return MinAt(0) == -FLT_MAX || MaxAt(0) == FLT_MAX; }
};
struct Xform {
    uint16_t flags;
    uint16_t version;
    V3 pos;
    float scale;
    M3 orient;
    Xform();                                               // 0x00409930
};
template <class T>
struct Ref {                              // EA::AutoRefCount-like handle (inline accessors)
    T* mp;
    T* get() const { return mp; }
    T* operator->() const { return mp; }
};
struct ModelStub {
    char pad[8];
    Xform xf;
};
struct HandleStub {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void Refresh();                                // +0x14
    virtual void s6(); virtual void s7();
    virtual void Update(float dt);                         // +0x20
    void* GetModel();                                      // 0x0047e680
    void* GetOther();                                      // 0x0047e6a0
};
struct ModelWorldStub {
    virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47(); virtual void p48(); virtual void p49(); virtual void p50(); virtual void p51(); virtual void p52(); virtual void p53(); virtual void p54(); virtual void p55(); virtual void p56();
    virtual void GetBounds(ModelStub* model, BBox* out);   // +0xe4
};
struct EditorModelStub {
    char pad[0x38];
    float mScale;
    float GetScale();   // 0x004adaa0
};
struct HandleVec {
    HandleStub** mpBegin;
    HandleStub** mpEnd;
    HandleStub** mpCap;
    bool empty() const;                                    // 0x00526430
    int size() const { return (int)(mpEnd - mpBegin); }
    HandleStub*& operator[](int i) { return mpBegin[i]; }
};
struct Bits60 {
    uint32_t w[2];
    bool test(unsigned pos) const {
        if (pos < 0x3c)
            return ((1u << (pos % 32)) & w[pos / 32]) != 0;
        return false;
    }
};
struct Blk_s0044_9ed0 {
    char pad0[0x10];
    Ref<ModelStub> mModel;             // +0x10
    char pad14[4];
    Ref<ModelWorldStub> mModelWorld;   // +0x18
    char pad1c[0x28 - 0x1c];
    EditorModelStub* mEditorModel;     // +0x28
    bool mIsFullInit;                  // +0x2c
    char pad2d[0x48 - 0x2d];
    V3 mPosition;                      // +0x48
    char pad54[0x60 - 0x54];
    Mat mOrientation;                  // +0x60
    char pad84[0xa8 - 0x84];
    M3 mBaseOrientation;               // +0xa8
    char padcc[0xf0 - 0xcc];
    M3 mUserOrientation;               // +0xf0
    char pad114[0x154 - 0x114];
    int mArr[3];                       // +0x154 (HandleStub* x3)
    HandleStub* mBallHandle;           // +0x160
    char pad164[0x18c - 0x164];
    hkRigidBodyStub* mPhysicsBlock;    // +0x18c
    char pad190[0x1d8 - 0x190];
    float mUniformScale;               // +0x1d8
    char pad1dc[0x33c - 0x1dc];
    Blk_s0044_9ed0* mParent;                      // +0x33c
    char pad340[0x3ec - 0x340];
    HandleStub* mChildHandleA;         // +0x3ec
    ModelStub* mChildModelB;           // +0x3f0
    char pad3f4[0x40c - 0x3f4];
    V3 mOffsetVec;                     // +0x40c
    char pad418[0x6cc - 0x418];
    HandleVec mDeformHandles;          // +0x6cc
    char pad6d8[0xdc8 - 0x6d8];
    Bits60 mFlags;                     // +0xdc8

    void A49ed0();
    void A4a070();
    void A4a0e0(M3 orient, bool updatePhysics);
    BBox A4aaa0(int mode);
    bool A4a9a0(Blk_s0044_9ed0* other);
    int A4aa10(int i);
    void SetBooleanAttribute(int a, int b);    // 0x00435a10
    void RebuildPhysics();                      // 0x00452040
    void Sub449d40(BBox* b);                    // 0x00449d40
    void Sub44b640(BBox* b);                    // 0x0044b640
    void Sub44b6b0();                           // 0x0044b6b0
};
// ---- items of slice s00449ed0 end

// ---- items of slice s0044ae00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kFltMax;                         // 0x013ec2a0
struct V3_s0044_ae00 {
    float x, y, z;
    V3_s0044_ae00& operator=(const V3_s0044_ae00& o) { x = o.x; y = o.y; z = o.z; return *this; }
    float& operator[](int i) { return (&x)[i]; }
};
struct M3_s0044_ae00 {
    float m[9];
    M3_s0044_ae00& operator=(const M3_s0044_ae00& o);
};
struct V3Q {
    float x, y, z;
    float& operator[](int i) { return (&x)[i]; }
};
struct F3 {
    float v[3];
    float operator[](int i) const { return v[i]; }
};
struct V3P { float x, y, z; V3P() {} V3P(const V3P& o) : x(o.x), y(o.y), z(o.z) {} };
struct Mat9 { float m[9]; };
template <class T>
struct Sp {
    T* p;
    operator T*() const { return p; }
    T* operator->() const { return p; }
};
struct Prop { char pad[0x12]; unsigned short type; float* GetFloat(); };
struct PropList {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool GetProp(unsigned id, Prop** out);   // slot 9 (+0x24)
};
struct Xf {
    unsigned short flags;
    unsigned short count;
    V3_s0044_ae00 pos;
    float scale;
    Mat9 mat;
    Xf();                                           // 0x00409930
    void SetPosition(const V3_s0044_ae00& p) { pos = p; flags |= 4; ++count; }
    void SetOrientation(const Mat9& m) { mat = m; flags |= 2; ++count; }
    void SetScale(float s) { scale = s; ++count; }
};
struct BBox_s0044_ae00 {
    V3Q mn, mx;
    BBox_s0044_ae00();                                         // 0x00409c00
    BBox_s0044_ae00(const BBox_s0044_ae00& o);                            // 0x00511140
    void SetCenterRadius(const V3Q* c, float r);     // 0x00409ce0
    void Transform(Xf* x);                          // 0x00409dd0
    void Scale(float s);                            // 0x0044ad00
    void Merge(const BBox_s0044_ae00& o);                      // 0x0043f050
    bool IsInverted() { return mn[0] > mx[0]; }
    bool IsInfinite() { return mn[0] == -kFltMax || mx[0] == kFltMax; }
};
extern V3Q g_defaultCenter;                          // 0x015d255c
struct Handle {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void Vfn14();
    void SetBoundingBox(BBox_s0044_ae00* b);                   // 0x00485200
    void F5650();                                   // 0x00485650
    bool IsFlagSet();                               // 0x0047f290
    void F5550();                                   // 0x00485550
};
struct Fade {
    bool IsPlaying();                               // 0x00434100
    void Update(float dt);                          // 0x00433b30
};
struct Bits32 {
    unsigned int w;
    void SetBit(unsigned i) { w |= (1u << (i % 32)); }
    void ClearBit(unsigned i) { w &= ~(1u << (i % 32)); }
    void set(unsigned i, bool v) {
        if (i < 32) {
            if (v)
                SetBit(i);
            else
                ClearBit(i);
        }
    }
};
struct Obj { unsigned int pad0; Bits32 flags; };
struct Link {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11();
    virtual void Vfn30(int a, int b);               // +0x30
};
struct ModelWorld {
    virtual void w00();
    virtual void w01();
    virtual void w02();
    virtual void w03();
    virtual void w04();
    virtual void w05();
    virtual void w06();
    virtual void w07();
    virtual void w08();
    virtual void w09();
    virtual void w0a();
    virtual void w0b();
    virtual void w0c();
    virtual void w0d();
    virtual void w0e();
    virtual void w0f();
    virtual void w10();
    virtual void w11();
    virtual void w12();
    virtual void w13();
    virtual void w14();
    virtual void w15();
    virtual void w16();
    virtual void w17();
    virtual BBox_s0044_ae00* GetBounds(Obj* model);            // +0x60 (6 floats: min, max)
    virtual void w19();
    virtual void w1a();
    virtual void w1b();
    virtual void w1c();
    virtual void w1d();
    virtual void w1e();
    virtual void w1f();
    virtual void w20();
    virtual void w21();
    virtual void w22();
    virtual void w23();
    virtual void w24();
    virtual void w25();
    virtual void w26();
    virtual void w27();
    virtual void w28();
    virtual void w29();
    virtual void w2a();
    virtual void w2b();
    virtual void w2c();
    virtual void w2d();
    virtual void w2e();
    virtual void w2f();
    virtual void w30();
    virtual void w31();
    virtual void w32();
    virtual void w33();
    virtual void w34();
    virtual void Vfnd4(Obj* a, void* b, int c);       // +0xd4
    virtual void w36();
    virtual void w37();
    virtual void w38();
    virtual void Vfne4(Obj* model, BBox_s0044_ae00* out);        // +0xe4
};
struct Sizer {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
    virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
    virtual void v0a(); virtual void v0b(); virtual void v0c(); virtual void v0d(); virtual void v0e();
    virtual void v0f(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14();
    virtual void Vfn54(unsigned inst, unsigned group, float* begin, int count, V3Q* mn, V3Q* mx);   // +0x54
};
Sizer* GetSizer();                                  // 0x00401010
struct Blk_s0044_ae00;
struct BlkVec {
    Sp<Blk_s0044_ae00>* mpBegin;
    Sp<Blk_s0044_ae00>* mpEnd;
    Sp<Blk_s0044_ae00>* mpCap;
    int size() const { return (int)(mpEnd - mpBegin); }
    Sp<Blk_s0044_ae00>& operator[](int i) { return mpBegin[i]; }
};
struct FloatVec {
    float* mpBegin;
    float* mpEnd;
    float* mpCap;
    int size() const { return (int)(mpEnd - mpBegin); }
};
struct Blk_s0044_ae00 {
    char pad00[0xc];
    Sp<PropList> mPropList;     // +0xc
    Sp<Obj> mModel;             // +0x10
    char pad14[4];
    Sp<ModelWorld> mWorld;      // +0x18
    unsigned mInstance;         // +0x1c
    unsigned mGroup;            // +0x20
    char pad24[0x2c - 0x24];
    bool m2c;
    char pad2d[0x34 - 0x2d];
    bool m34;                   // +0x34
    char pad35[0x48 - 0x35];
    V3_s0044_ae00 mPosition;               // +0x48
    char pad54[0x60 - 0x54];
    Mat9 mOrient;               // +0x60
    char pad84[0x14c - 0x84];
    Sp<Handle> mRing[5];        // +0x14c
    char pad160[0x188 - 0x160];
    int m188;                   // +0x188
    char pad18c[0x1a8 - 0x18c];
    bool m1a8;
    bool m1a9;
    char pad1aa[2];
    int m1ac;
    char pad1b0[0x1d8 - 0x1b0];
    float mScaleY;              // +0x1d8
    char pad1dc[0x1e8 - 0x1dc];
    V3_s0044_ae00 mVec;                    // +0x1e8
    M3_s0044_ae00 mMat;                    // +0x1f4
    char pad218[0x230 - 0x218];
    bool m230;
    char pad231[0x284 - 0x231];
    char m284[0x38];            // +0x284
    char pad2bc[0x33c - 0x2bc];
    Sp<Blk_s0044_ae00> mSocket;            // +0x33c
    BlkVec mChildren;           // +0x340
    char pad34c[0x3a0 - 0x34c];
    V3P m3a0;                   // +0x3a0
    char pad3ac[0x3e0 - 0x3ac];
    Sp<Blk_s0044_ae00> m3e0;               // +0x3e0
    char pad3e4[0x3ec - 0x3e4];
    Sp<Link> m3ec;              // +0x3ec
    Sp<Obj> m3f0;               // +0x3f0
    char pad3f4[0x40c - 0x3f4];
    F3 m40c;              // +0x40c
    char pad418[0x434 - 0x418];
    int m434;                   // +0x434
    char pad438[0x604 - 0x438];
    int m604;                   // +0x604
    char pad608[0x704 - 0x608];
    FloatVec m704;              // +0x704
    char pad710[0xdc8 - 0x710];
    unsigned int mFlags[2];     // +0xdc8 (bitset<60>)
    Fade mFade;                 // +0xdd0

    bool GetFlag(unsigned int n) const {
        unsigned int tmp;
        bool t14;
        if (n < 60u) {
            tmp = mFlags[n / 32];
            t14 = (tmp & (1u << (n % 32))) != 0;
        } else {
            t14 = false;
        }
        return t14;
    }

    BBox_s0044_ae00 GetBBox(int type, bool a, bool b);         // 0x0044ae00
    float GetDefaultScale();
    V3_s0044_ae00* B550(V3_s0044_ae00* out);
    M3_s0044_ae00* B590(M3_s0044_ae00* out);
    void B640(int a);
    void B6b0();
    bool B780();
    void B7b0(unsigned ms);
    void Ba20(bool a, bool b);

    float FUN_0043eed0();
    float FUN_0043f3f0();
    bool FUN_0044c030();
    void RebuildPhysics();                          // 0x00452040
    void SetBooleanAttribute(int id, bool v);       // 0x00435a10
    bool IsSymmetryLocked();                        // 0x00435c80
    V3P GetOffsetA(int i);                           // 0x00438120
    V3P GetOffsetB(int i);                           // 0x004381e0
    bool Place(V3P a, V3P b);                         // 0x00437b00
    V3P FUN_004364a0();                              // 0x004364a0
};
bool FUN_004a7e60(Blk_s0044_ae00* b);
// ---- items of slice s0044ae00 end

// ---- items of slice s0044bcf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float g_eps;   // 0.001f
struct Vec1 { float x, y, z; float& operator[](int i) { return (&x)[i]; } };
struct M3_s0044_bcf0 {
    float m[9];
    M3_s0044_bcf0& operator=(const M3_s0044_bcf0&);
};
struct Blk_s0044_bcf0 {
    char pad0[0x48];
    Vec1 mVec;          // +0x48
    char gap1[0xc];
    M3_s0044_bcf0 mMat;            // +0x60
    char pad1[0x1c4 - 0x84];
    int m1c4;           // +0x1c4
    char pad2[0x3e0 - 0x1c8];
    Blk_s0044_bcf0* m3e0;          // +0x3e0

    Blk_s0044_bcf0* Child() { return m3e0; }

    void Abcf0();
    int C050();  // 0x0044c050 (Blk::C050)
    void C0e0();
    void C270();
    int C450();
    void C480(int v);  // 0x0044c480 (Blk::C480)
    void C4d0(int a);
    void C5a0(int a);
};
// ---- items of slice s0044bcf0 end

// ---- items of slice s0044d4f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct V3_s0044_d4f0 { float x, y, z; V3_s0044_d4f0& operator=(const V3_s0044_d4f0& o) { x = o.x; y = o.y; z = o.z; return *this; } };
struct Vec3_s0044_d4f0 {
    float x, y, z;
    float& operator[](int i) { return ((float*)this)[i]; }
    Vec3_s0044_d4f0() {}
    Vec3_s0044_d4f0(float a, float b, float c) { x = a; y = b; z = c; }
    Vec3_s0044_d4f0& operator=(const Vec3_s0044_d4f0& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
struct Mat3 { float m[9]; Mat3() {} };
V3_s0044_d4f0 operator*(const V3_s0044_d4f0& v, const Mat3& m);   // 0x0041daf0
V3_s0044_d4f0& operator*=(V3_s0044_d4f0& v, const float& s);      // 0x0041dba0
struct Raw3 { int a, b, c; };
Vec3_s0044_d4f0 operator*(const Vec3_s0044_d4f0& v, const Mat3& m);   // 0x0041daf0
Vec3_s0044_d4f0 operator-(const Vec3_s0044_d4f0& v);                  // 0x00422020 (Vector3_Negate)
Vec3_s0044_d4f0 operator-(const Vec3_s0044_d4f0& a, const Vec3_s0044_d4f0& b);   // 0x0041db10
Vec3_s0044_d4f0 operator+(const Vec3_s0044_d4f0& a, const Vec3_s0044_d4f0& b);   // 0x0041dc10
Vec3_s0044_d4f0 operator*(const Vec3_s0044_d4f0& v, const float& s);  // 0x0041dca0
Mat3 Transposed(const Mat3& m);                 // 0x0041ded0
Vec3_s0044_d4f0& operator*=(Vec3_s0044_d4f0& v, const float& s);      // 0x0041dba0
inline float Abs_s0044_d4f0(float f) { return fabsf(f); }
struct Holder {
    void* a;    // +0
    void* b;    // +4
    void* GetB() { return b; }
    void Compute(Vec3_s0044_d4f0* pos, Mat3* rot);   // 0x004e95e0
};
struct Bounds {
    V3_s0044_d4f0 mn;      // +0x00
    V3_s0044_d4f0 mx;      // +0x0c
    Holder* m18;    // +0x18
    bool m1c;   // +0x1c
    Bounds();                       // 0x00433960
    Bounds(const Bounds& o);        // same body as operator= (0x0044d960 shape)
    ~Bounds();                      // 0x004ae250
    Bounds& operator=(const Bounds& o);
};
Bounds::Bounds(const Bounds& o)
{
    mn = o.mn;
    mx = o.mx;
    m18 = o.m18;
    m1c = o.m1c;
}
struct BVec {
    Bounds* mBeg;   // +0x234
    Bounds* mEnd;   // +0x238
    int size() { return mEnd - mBeg; }
    Bounds& at(int i) { return mBeg[i]; }
};
struct Pose {
    char pad[0xc];
    Vec3_s0044_d4f0 pos;           // +0x0c
    float pad18;
    Mat3 rot;           // +0x1c
};
struct BBox_s0044_d4f0 { Vec3_s0044_d4f0 mn, mx; };
struct Blk_s0044_d4f0 {
    char pad0[0x10];
    Pose* mXf;          // +0x10
    char pad1[0x48 - 0x14];
    Vec3_s0044_d4f0 mPos;          // +0x48
    char pad2[0x60 - 0x54];
    Mat3 mRot;          // +0x60
    char pad3[0x234 - 0x84];
    BVec mVec;          // +0x234

    Pose* GetXf() { return mXf; }
    Bounds& Elem(int i) { return mVec.mBeg[i]; }
    Vec3_s0044_d4f0& MaxPt(int i) { return *(Vec3_s0044_d4f0*)&mVec.mBeg[i].mx; }
    Vec3_s0044_d4f0& MinPt(int i) { return *(Vec3_s0044_d4f0*)&mVec.mBeg[i].mn; }
    int Count();                                    // 0x0044e800
    void GetBBox(BBox_s0044_d4f0* out, int a, int b, int c);   // 0x0044ae00
    Vec3_s0044_d4f0* Corner(Vec3_s0044_d4f0* out, int i);                 // 0x0043d240
    Vec3_s0044_d4f0 Corner(int i);                             // 0x0043d240 (same function, sret form)

    Bounds GetBounds(int index);
    void D570();
    int D9e0(Vec3_s0044_d4f0 p, float maxDist);
};
// ---- items of slice s0044d4f0 end

// ---- items of slice s0044e460 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern bool PropertyGetBool(void* prop);            // 0x0041e920
struct Vec3_s0044_e460 {
    float x, y, z;
    const float& operator[](int i) const { return ((const float*)this)[i]; }
};
struct cSPEditorBlock;
struct Bounds_s0044_e460;
struct cPropertyList;
extern int  FUN_0044a7e60(cSPEditorBlock* self);    // 0x004a7e60
struct cPropertyList {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6();
    virtual bool HasProperty(unsigned int id);                       // slot 7  (+0x1c)
    virtual void s8();
    virtual bool GetProperty(unsigned int id, void** out);           // slot 9  (+0x24)
};
struct Bounds_s0044_e460 {
    unsigned int mData[8];
    Bounds_s0044_e460();
    ~Bounds_s0044_e460(); // 0x004ae250
    void Set(const void* src);      // 0x0044d960: this = dst, arg = src
};
struct cSPEditorBlock {
    char                pad_00[0xc];
    cPropertyList*      mpPropList;        // +0x0c
    char                pad_10[0x1c0 - 0x10];
    float               mBaseJointScale;   // +0x1c0
    float               mUniformScale;     // +0x1c4
    char                pad_1c8[0x1cc - 0x1c8];
    int                 mScaleType;        // +0x1cc
    char                pad_1d0[0x234 - 0x1d0];
    void*               mpSnapAxesBase;    // +0x234 (eastl::vector mpBegin)
    char                pad_238[0x33c - 0x238];
    cSPEditorBlock*     mpSocketConnector; // +0x33c (AutoRefCount<cMWModel>)
    cSPEditorBlock**    mpChildBegin;      // +0x340
    cSPEditorBlock**    mpChildEnd;        // +0x344
    cSPEditorBlock**    mpChildCap;        // +0x348
    char                pad_34c[0x3e0 - 0x34c];
    cSPEditorBlock*     mpLinked;          // +0x3e0
    cSPEditorBlock*     mpLinkedAlt;       // +0x3e4
    char                pad_3e8[0xdc8 - 0x3e8];
    unsigned int        mFlags[2];         // +0xdc8 (60-bit flag array)

    bool GetFlag(unsigned int n) const {
        unsigned int tmp;
        bool t14;
        if (n < 60u) {
            tmp = mFlags[n / 32];
            t14 = (tmp & (1u << (n % 32))) != 0;
        } else {
            t14 = false;
        }
        return t14;
    }

    void  SetFlag(int id, int value);          // 0x00435a10
    float FUN_0044f220();                      // 0x0044f220 (receiver = socket connector)
    int   CalculateSymmetrySign();             // 0x0044f240
    int   FindSnapAxis(Vec3_s0044_e460 v, float w);       // 0x0044d9e0
    int   FUN_0044c050();                      // 0x0044c050
    int   FUN_0044c450();                      // 0x0044c450
    Bounds_s0044_e460* GetBounds(Bounds_s0044_e460* out, float x, float y, float z, float w); // 0x0044e720
    int   GetBlockType(unsigned int key);      // 0x0044e830
    void  SetBaseJointScale(float scale);      // 0x0044e980
    void  RefreshLinkedFlag();                 // 0x0044ea80
    void  RecursiveFlagA();                    // 0x0044ede0
    void  RecursiveFlagB();                    // 0x0044eea0
    void  RecursiveFlagC();                    // 0x0044efb0
    void  SetScaleType(int type);              // 0x0044f130
};
// ---- items of slice s0044e460 end

// ---- items of slice s0044f420 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float g_negOne;   // 0x013eb1bc = -1.0f
struct Vec3f_s0044_f420 { float v[3]; };
struct AutoRefBlockVec {
    unsigned int w[15];            // 0x3c-byte local
    void Ctor(const char* name);   // 0x00540470
    void Func();                   // 0x00453770
    void Dtor();                   // 0x00453eb0
};
struct cSPEditorBlock_s0044_f420;
struct ModelObj_s0044_f420 {
    bool FUN_004adc40();           // 0x004adc40
};
struct cSPEditorBlock_s0044_f420 {
    char   pad0[0x28];
    void*  mModel;        // +0x28
    char   pad2c[0x33c - 0x2c];
    cSPEditorBlock_s0044_f420* mSocket;  // +0x33c
    char   pad340[0x3e0 - 0x340];
    cSPEditorBlock_s0044_f420* mLinked;  // +0x3e0
    char   pad3e4[0xdc8 - 0x3e4];
    unsigned int mFlags[2];   // +0xdc8

    bool GetFlag(unsigned int n) const {
        unsigned int tmp;
        bool t14;
        if (n < 60u) {
            tmp = mFlags[n / 32];
            t14 = (tmp & (1u << (n % 32))) != 0;
        } else {
            t14 = false;
        }
        return t14;
    }

    int  CalculateSymmetrySign();                 // 0x0044f240
    void SetFlag(int id, int value);              // 0x00435a10
    void FUN_0043f230(cSPEditorBlock_s0044_f420* self);      // 0x0043f230
    void FUN_004388b0(cSPEditorBlock_s0044_f420* block);     // 0x004388b0
    char FUN_004a7e60(cSPEditorBlock_s0044_f420* self);      // 0x004a7e60
    void TrackerGetOffsetA(float* out, int one);  // 0x00438120
    void TrackerGetOffsetB(float* out, int one);  // 0x004381e0
    void TrackerPlace(Vec3f_s0044_f420 a, Vec3f_s0044_f420 b); // 0x00437b00
    cSPEditorBlock_s0044_f420* BuildBlock(int type, void* root, AutoRefBlockVec& a, AutoRefBlockVec& b); // 0x0044f7c0
    void FUN_00448e90(void* p, int a);            // 0x00448e90
    void FUN_00449420(void* p, int a);            // 0x00449420

    cSPEditorBlock_s0044_f420* Split(int type);              // 0x0044f420
};
// ---- items of slice s0044f420 end

// ---- items of slice s0044f7c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3_s0044_f7c0 {
    float x, y, z;
    Vector3_s0044_f7c0() {}
    Vector3_s0044_f7c0(const Vector3_s0044_f7c0& v) : x(v.x), y(v.y), z(v.z) {}
    float& operator[](int i) { return (&x)[i]; }
};
struct Matrix3_s0044_f7c0 {
    float m[9];
    Matrix3_s0044_f7c0() {}
    Matrix3_s0044_f7c0(const Matrix3_s0044_f7c0& other);              // 0x0041cb40 (out of line)
};
Matrix3_s0044_f7c0 MirrorMatrix(const Matrix3_s0044_f7c0& m, int flags);   // 0x004a8e10
Vector3_s0044_f7c0 MirrorVector(const Vector3_s0044_f7c0& v);              // 0x004a8f40
static const float kNegOne = -1.0f;                  // 0x013eb1bc
template <class T>
struct AutoRefCount_s0044_f7c0 {
    T* mpObject;

    AutoRefCount_s0044_f7c0(T* pObject) : mpObject(pObject) {
        if (mpObject)
            mpObject->AddRef();
    }
    ~AutoRefCount_s0044_f7c0() {
        if (mpObject)
            mpObject->Release();
    }
    AutoRefCount_s0044_f7c0& operator=(T* pObject) {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    T* get() const { return mpObject; }
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};
template <unsigned N>
struct bitset_s0044_f7c0 {
    uint32_t mWord[(N + 31) / 32];

    bool test(size_t i) const {
        if (i < N) {
            const uint32_t word = mWord[i / 32];
            return (word & (1u << (i % 32))) != 0;
        }
        return false;
    }
};
struct allocator_tag { allocator_tag() {} };
template <class T>
struct fixed_ref_vector {
    typedef AutoRefCount_s0044_f7c0<T> value_type;
    value_type* mpBegin;
    value_type* mpEnd;
    value_type* mpCapacity;
    char        mAllocator[0xc];
    value_type* mBuffer[8];

    fixed_ref_vector(const allocator_tag& a) { BaseInit(a); FixedInit(); }
    ~fixed_ref_vector();                                       // 0x00453eb0

    void BaseInit(const allocator_tag& a);                     // 0x00540470
    void FixedInit();                                          // 0x00453770
    fixed_ref_vector& operator=(const fixed_ref_vector& x);    // 0x00453f20
    void push_back(const value_type& v);                       // 0x004541f0

    int size() const { return mpEnd - mpBegin; }
    value_type& operator[](int i) { return mpBegin[i]; }
};
struct cIModelWorld;
struct cSPEditorBlock_s0044_f7c0;
struct cSPEditorHandle {                     // morph/deform handle
    char  pad0[0x180];
    float mDelta;                            // +0x180
    void Update();                           // 0x00482670
};
struct cSPEditorPinTarget {                  // refcounted interface: AddRef slot 0, Release slot 1
    virtual int AddRef();
    virtual int Release();
};
struct cSPEditorPinningInfo {                // pointed to by cSPEditorBlock +0x378
    int                              field_0;
    AutoRefCount_s0044_f7c0<cSPEditorPinTarget> mTarget;            // +0x04
    Vector3_s0044_f7c0                          mOffset;            // +0x08
    Vector3_s0044_f7c0                          mNormal;            // +0x14
    Matrix3_s0044_f7c0                          mOrientation;       // +0x20
    int                              mIndex;             // +0x44
    bool                             mFlag;              // +0x48

    void Attach(cSPEditorBlock_s0044_f7c0* parent, int index, bool flag);   // 0x004e9500
};
struct cSPEditorModel {
    void AddBlock(cSPEditorBlock_s0044_f7c0* block, int notify);            // 0x004abaf0
};
typedef fixed_ref_vector<cSPEditorBlock_s0044_f7c0>  BlockRefVector;
typedef fixed_ref_vector<cSPEditorHandle> HandleRefVector;
bool IsBlockMirrorable(cSPEditorBlock_s0044_f7c0* block);                  // 0x004a6270
struct cSPEditorBlock_s0044_f7c0 {
    virtual ~cSPEditorBlock_s0044_f7c0();
    virtual int AddRef();
    virtual int Release();

    char                         pad4[0x18 - 0x4];
    AutoRefCount_s0044_f7c0<cIModelWorld>   mpModelWorld;            // +0x18
    uint32_t                     mInstanceID;             // +0x1c
    uint32_t                     mGroupID;                // +0x20
    int                          mBlockPack;              // +0x24
    cSPEditorModel*              mpEditorModel;           // +0x28
    int                          field_2C;                // +0x2c
    float                        field_30;                // +0x30
    bool                         mIsVisible;              // +0x34
    char                         pad35[0x48 - 0x35];
    Vector3_s0044_f7c0                      mPosition;               // +0x48
    char                         pad54[0xa8 - 0x54];
    Matrix3_s0044_f7c0                      mOrientation;            // +0xa8
    char                         padcc[0xf0 - 0xcc];
    Matrix3_s0044_f7c0                      mUserOrientation;        // +0xf0
    char                         pad114[0x188 - 0x114];
    int                          field_188;               // +0x188
    char                         pad18c[0x1c4 - 0x18c];
    int                          field_1C4;               // +0x1c4
    int                          field_1C8;               // +0x1c8
    int                          mLimbType;               // +0x1cc
    float                        mMuscleScale;            // +0x1d0
    float                        mBaseMuscleScale;        // +0x1d4
    float                        mScale;                  // +0x1d8
    float                        mScale2;                 // +0x1dc
    char                         pad1e0[0x340 - 0x1e0];
    BlockRefVector               mChildren;               // +0x340
    cSPEditorPinningInfo*        mpPinningInfo;           // +0x378
    char                         pad37c[0x3a0 - 0x37c];
    Vector3_s0044_f7c0                      mTriangleDirection;      // +0x3a0
    Vector3_s0044_f7c0                      mTrianglePickOrigin;     // +0x3ac
    char                         pad3b8[0x3e0 - 0x3b8];
    AutoRefCount_s0044_f7c0<cSPEditorBlock_s0044_f7c0> mpSymmetricRigblock;     // +0x3e0
    AutoRefCount_s0044_f7c0<cSPEditorBlock_s0044_f7c0> mpAsymmetricRigblock;    // +0x3e4
    bool                         mIsClone;                // +0x3e8
    char                         pad3e9[0x6cc - 0x3e9];
    HandleRefVector              mMorphHandles;           // +0x6cc
    char                         pad704[0xdc8 - 0x704];
    bitset_s0044_f7c0<60>                   mBooleanAttributes;      // +0xdc8
    char                         padDD0[0xe08 - 0xdd0];

    cSPEditorBlock_s0044_f7c0();                                                   // 0x004346b0
    static void* operator new(size_t n, const char* name, int, int, int, int);

    int  GetLimbType() const { return mLimbType; }

    void SetBooleanAttribute(int index, bool value);                   // 0x00435a10
    bool IsSymmetricChildCandidate();                                   // 0x00435c80
    void SetSymmetricBlock(cSPEditorBlock_s0044_f7c0* block);                      // 0x00438cc0
    void SetAsymmetricBlock(cSPEditorBlock_s0044_f7c0* block);                     // 0x00438df0
    void AddChild(cSPEditorBlock_s0044_f7c0* block);                               // 0x004388b0
    ResourceKey GetMirroredKey(int sign, int flags);                    // 0x00438f20
    void BuildBlock(uint32_t instance, uint32_t group, cIModelWorld* world, int a4,
                    float a5, bool a6, bool a7, bool a8);               // 0x00441440
    void SetModelScaleA(float v, int flag);                             // 0x00440020
    void SetModelScaleB(float v, int flag);                             // 0x00440090
    void SetBaseMuscleScale(float v);                                   // 0x0043eb50
    void Sub_447030(int v);                                             // 0x00447030
    void SetMuscleScale(float v);                                       // 0x0043eae0
    void SetMorphHandleDelta(int index, float delta, bool a, bool b, bool c);  // 0x0043d690
    void UpdateAfterClone();                                            // 0x0044a070
    void RebuildPhysics();                                              // 0x00452040
    void CopyPaintFrom(cSPEditorBlock_s0044_f7c0* src);                            // 0x00440e00
    void SetUserOrientation(Matrix3_s0044_f7c0 m);                                 // 0x0043ffa0
    void SetPosition(const Vector3_s0044_f7c0& pos, bool flag);                    // 0x00448e90
    void SetOrientation(const Matrix3_s0044_f7c0& m, bool flag);                   // 0x00449420
    void SetBaseJointScale(int v);                                      // 0x0044e980
    void SetScaleType(int type);                                        // 0x0044f130
    int  GetSymmetrySign();                                             // 0x0044f220
    int  GetB();                                                        // 0x00451210
    Vector3_s0044_f7c0 GetOffsetA(bool flag);                                      // 0x00438120
    Vector3_s0044_f7c0 GetOffsetB(bool flag);                                      // 0x004381e0
    void Place(Vector3_s0044_f7c0 a, Vector3_s0044_f7c0 b);                                   // 0x00437b00
    void FinishClone();                                                 // 0x00449ed0

    // @ 0x0044f7c0
    cSPEditorBlock_s0044_f7c0* CloneBlock(int type, cSPEditorBlock_s0044_f7c0* root,
                               BlockRefVector& originals, BlockRefVector& copies);
};
// ---- items of slice s0044f7c0 end

// ---- items of slice s00450f70 begin (TODO(rewrite): local stubs, replace by canonical classes)
template <int N> inline void ScratchSlots_s0045_0f70() { uint32_t s[N]; }
struct Vec3_s0045_0f70 {
    float x, y, z;
};
struct RCObj {
    virtual void AddRef();
    virtual void Release();
};
struct SubInner {
    char  pad0[0x1c];
    void* field;        // +0x1c
};
struct Sub {
    char     pad0[0x1c];
    SubInner inner;     // +0x1c
};
struct Tracker {
    char   pad0[4];
    RCObj* field4;      // +4
    char   pad8[0x14 - 8];
    Vec3_s0045_0f70   vec14;       // +0x14
    char   pad20[0x44 - 0x20];
    int    field44;     // +0x44

    void Call(void* tmp, int a, unsigned char b);   // 0x004e9500
};
struct Block2 {
    char     pad0[0x18];
    void*    mp18;        // +0x18
    int      mInstance;   // +0x1c
    int      mGroup;      // +0x20
    char     pad24[0x28 - 0x24];
    int      mField28;    // +0x28
    char     pad2c[0x48 - 0x2c];
    Vec3_s0045_0f70     mVec48;      // +0x48
    char     pad54[0x188 - 0x54];
    void*    mPtr188;     // +0x188
    Sub*     mSub18c;     // +0x18c
    char     pad190[0x194 - 0x190];
    Vec3_s0045_0f70     mVec194;     // +0x194
    bool     mFlag1a0;    // +0x1a0
    char     pad1a1[0x1a4 - 0x1a1];
    int      mField1a4;   // +0x1a4
    char     pad1a8[0x1d8 - 0x1a8];
    float    mField1d8;   // +0x1d8
    float    mField1dc;   // +0x1dc
    char     pad1e0[0x33c - 0x1e0];
    void*    mPtr33c;     // +0x33c
    char     pad340[0x378 - 0x340];
    Tracker* mTracker;    // +0x378
    char     pad37c[0xdc8 - 0x37c];
    unsigned int mFlags[2]; // +0xdc8

    bool GetFlag(unsigned int n) const {
        unsigned int tmp;
        bool t14;
        if (n < 60u) {
            tmp = mFlags[n / 32];
            t14 = (tmp & (1u << (n % 32))) != 0;
        } else {
            t14 = false;
        }
        return t14;
    }
    void SetBit(unsigned int n) { unsigned int w = n / 32; mFlags[w] |= (1u << (n % 32)); }
    void ClearBit(unsigned int n) { unsigned int w = n / 32; mFlags[w] &= ~(1u << (n % 32)); }

    int    GetA();                        // 0x004511f0
    int    GetB();                        // 0x00451210
    void   SetF(void* a, unsigned char b);// 0x00451240
    void   SetRef(RCObj* p);              // 0x00451280
    Vec3_s0045_0f70*  GetVec14(Vec3_s0045_0f70* out);           // 0x004512e0
    Vec3_s0045_0f70*  SetVec194(int x, int y, int z);// 0x00451330
    void   ResetVec194();                 // 0x00451360
    Vec3_s0045_0f70*  GetVec194(Vec3_s0045_0f70* out);          // 0x004513a0
    void   SetPtr188(void* p);            // 0x00451e20
    void   SetSub38(void* p);             // 0x00451e50
    void*  GetSub38();                    // 0x00451e90
    void   Reset188();                    // 0x00451ed0
    unsigned char Rebuild(int a, int b, float c, char d, unsigned char e); // 0x00450f70
    void   FUN_00452040();                // 0x00452040
    void   FUN_00451fe0();                // 0x00451fe0
    void   FUN_00440520(float f, int a, int b);   // 0x00440520
    void   FUN_00449ed0();                // 0x00449ed0
    void   FUN_00448e90(void* p, int a);  // 0x00448e90
    void   FUN_00449420(void* p, int a);  // 0x00449420
    unsigned char BuildBlock(int inst, int grp, int a, int b, float c, char d, unsigned char e, int one); // 0x00441040
};
namespace SP {
class IUnknown32_s0045_0f70 {
public:
    virtual int AddRef();
    virtual int Release();
};
}
namespace SP {
template <class T>
struct AutoRefCount_s0045_0f70 {
    T* mpObject;

    AutoRefCount_s0045_0f70& operator=(T* pObject)
    {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    ~AutoRefCount_s0045_0f70()
    {
        if (mpObject)
            mpObject->Release();
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
}
namespace SP {
template <int N>
struct bitset_s0045_0f70 {
    uint32_t mWord[(N + 31) / 32];

    uint32_t& DoGetWord(uint32_t n) { return mWord[n >> 5]; }
    __forceinline void set(uint32_t n, bool value)
    {
        if (n < N) {
            if (value)
                DoGetWord(n) |= 1u << (n % 32);
            else
                DoGetWord(n) &= ~(1u << (n % 32));
        }
    }
};
}
namespace SP {
class cPropertyList_s0045_0f70 {
public:
    virtual int AddRef();
    virtual int Release();
};
}
namespace SP {
class IModelWorld_s0045_0f70;
}
namespace SP {
struct cMWModel_s0045_0f70 {
    IModelWorld_s0045_0f70* mpWorld;                 // +0x00
    uint32_t pad04[(0x40 - 4) / 4];
    int mnRefCount;                       // +0x40
    uint32_t pad44[(0x64 - 0x44) / 4];
    AutoRefCount_s0045_0f70<IUnknown32_s0045_0f70> mpOwner;     // +0x64

    int AddRef() { mnRefCount = mnRefCount + 1; return mnRefCount; }
    int Release();                        // 0x0040f360
    inline void RemoveFromWorld();
};
}
namespace SP {
class IModelWorld_s0045_0f70 {
public:
    virtual int AddRef();                                                // 0x00
    virtual int Release();                                               // 0x04
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual void v3c(); virtual void v40(); virtual void v44();
    virtual void v48(); virtual void v4c(); virtual void v50(); virtual void v54();
    virtual void v58(); virtual void v5c(); virtual void v60(); virtual void v64();
    virtual void v68(); virtual void v6c(); virtual void v70(); virtual void v74();
    virtual void v78(); virtual void v7c(); virtual void v80(); virtual void v84();
    virtual void v88(); virtual void v8c(); virtual void v90(); virtual void v94();
    virtual void v98(); virtual void v9c(); virtual void va0(); virtual void va4();
    virtual void va8(); virtual void vac(); virtual void vb0(); virtual void vb4();
    virtual void vb8(); virtual void vbc(); virtual void vc0(); virtual void vc4();
    virtual void vc8(); virtual void vcc(); virtual void vd0();
    virtual void SetExternalEffectsTransform(cMWModel_s0045_0f70* model, const void* transform, uint32_t instanceID);  // 0xd4
    virtual void vd8(); virtual void vdc();
    virtual void ReleaseTransformedHull(int* hull);                      // 0xe0
    virtual void ve4(); virtual void ve8(); virtual void vec();
    virtual void vf0(); virtual void vf4(); virtual void vf8(); virtual void vfc();
    virtual void v100(); virtual void v104(); virtual void v108(); virtual void v10c();
    virtual void v110(); virtual void v114(); virtual void v118(); virtual void v11c();
    virtual void v120(); virtual void v124(); virtual void v128(); virtual void v12c();
    virtual void v130(); virtual void v134(); virtual void v138(); virtual void v13c();
    virtual void v140(); virtual void v144(); virtual void v148(); virtual void v14c();
    virtual void v150(); virtual void v154(); virtual void v158(); virtual void v15c();
    virtual void v160(); virtual void v164(); virtual void v168();
    virtual bool SetInWorld(cMWModel_s0045_0f70* model, bool inWorld);              // 0x16c
};
}
namespace SP {
inline void cMWModel_s0045_0f70::RemoveFromWorld() { mpWorld->SetInWorld(this, false); }
}
namespace SP {
class cSPEditorHandle_s0045_0f70 {
public:
    virtual int AddRef();          // 0x00
    virtual int Release();         // 0x04 0x0051e380
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18();
    virtual void Dispose();        // 0x1c
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48();
    virtual void Shutdown();       // 0x4c 0x0047e2c0
};
}
namespace SP {
class cSPEditorBlockHelper378_s0045_0f70 {
public:
    uint32_t mField0;
    AutoRefCount_s0045_0f70<IUnknown32_s0045_0f70> mpObject;
    uint32_t mData[(0x4c - 8) / 4];

    void Shutdown();               // 0x004ae250
};
}
namespace SP {
struct cSPEditorBlockOwnerLink_s0045_0f70 {
    uint32_t mData[0x38 / 4];
    bool IsPlaying();              // 0x00434100
    void Stop();                   // 0x004341c0
    void ReleaseHandle();          // 0x00433aa0
};
}
namespace SP {
class cSPEditorBlock_s0045_0f70;
}
namespace SP {
template <class T>
struct ref_vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[3];
    uint32_t mBuffer[8];
    int size() const { return (int)(mpEnd - mpBegin); }
    bool empty() const;               // 0x00526430 (ICF-shared)
    T& operator[](int i) { return *(mpBegin + i); }
    T* erase(T* first, T* last);      // 0x00533500
    void clear() { erase(mpBegin, mpEnd); }
};
}
namespace SP {
class cSPEditorBlock_s0045_0f70 : public RefCountVTemplate, public IUnknown32_s0045_0f70 {
public:
    AutoRefCount_s0045_0f70<cPropertyList_s0045_0f70> mpPropList;          // +0x0c
    AutoRefCount_s0045_0f70<cMWModel_s0045_0f70> mpModel;                  // +0x10
    AutoRefCount_s0045_0f70<cMWModel_s0045_0f70> mpEffectsMaskModel;       // +0x14
    AutoRefCount_s0045_0f70<IModelWorld_s0045_0f70> mpModelWorld;          // +0x18
    uint32_t mInstanceID;                            // +0x1c
    uint32_t mGroupID;                               // +0x20
    int mBlockPack;                                  // +0x24
    void* mpEditorModel;                             // +0x28
    uint32_t pad2c[(0x154 - 0x2c) / 4];
    AutoRefCount_s0045_0f70<cSPEditorHandle_s0045_0f70> mAxisHandles[3];   // +0x154
    AutoRefCount_s0045_0f70<cSPEditorHandle_s0045_0f70> mpRotationBallHandle;  // +0x160
    uint32_t pad164[(0x1a4 - 0x164) / 4];
    int mTransformedHull;                            // +0x1a4
    uint32_t pad1a8[(0x33c - 0x1a8) / 4];
    AutoRefCount_s0045_0f70<cSPEditorBlock_s0045_0f70> mpParent;           // +0x33c
    ref_vector<AutoRefCount_s0045_0f70<cSPEditorBlock_s0045_0f70> > mChildren;  // +0x340
    cSPEditorBlockHelper378_s0045_0f70* mpHelper378;            // +0x378
    uint32_t pad37c[(0x3e4 - 0x37c) / 4];
    AutoRefCount_s0045_0f70<cSPEditorBlock_s0045_0f70> mpSymmetricBlock;   // +0x3e4
    bool mIsSymmetric;                               // +0x3e8
    uint8_t pad3e9[3];
    AutoRefCount_s0045_0f70<cSPEditorHandle_s0045_0f70> mpBallConnectorHandle;  // +0x3ec
    AutoRefCount_s0045_0f70<cMWModel_s0045_0f70> mpSocketConnectorModel;   // +0x3f0
    uint32_t pad3f4[(0x6cc - 0x3f4) / 4];
    ref_vector<AutoRefCount_s0045_0f70<cSPEditorHandle_s0045_0f70> > mMorphHandles;  // +0x6cc
    uint32_t pad704[(0xdc8 - 0x704) / 4];
    bitset_s0045_0f70<60> mBooleanAttributes;                   // +0xdc8
    cSPEditorBlockOwnerLink_s0045_0f70 mOwnerLink;              // +0xdd0

    bool HasParent() const { return mpParent != 0; }
    void Shutdown2();
    void SetBooleanAttribute(int index, bool value); // 0x00435a10
    void RemoveChild(cSPEditorBlock_s0045_0f70* child);         // 0x00438b10
    void Sub_451ed0();                               // 0x00451ed0 (ReleasePhysics + clear +0x188)
    void Sub_453500(bool b);                         // 0x00453500
    void Sub_438df0(int a);                          // 0x00438df0
    void Sub_438cc0(int a);                          // 0x00438cc0
};
}
// ---- items of slice s00450f70 end

// ---- items of slice s00451ef0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec3_s0045_1ef0 { float x, y, z; };
struct HkWorldObject {
    void removeReference();
};
struct HkEntity {
    void FUN_01083110(void* local, void* arg);   // 0x01083110
};
struct HkWorld {
    HkEntity* addEntity(HkWorldObject* e, int activation); // 0x01082ee0
    void FUN_01084fa0(HkWorldObject* e, int a, int b);     // 0x01084fa0
};
struct cSPEditorBlock_s0045_1ef0 {
    char          pad0[0x48];
    Vec3_s0045_1ef0          mVec48;      // +0x48
    char          pad54[0xa8 - 0x54];
    Matrix33      mMatA8;      // +0xa8
    char          padcc[0x188 - 0xcc];
    HkWorld*      mWorld;      // +0x188
    HkWorldObject* mPhysObj;   // +0x18c
    char          pad190[0x1a8 - 0x190];
    bool          mFlag1a8;    // +0x1a8

    void FUN_00451fe0();       // 0x00451fe0
    void FUN_00451ef0(void* obj); // 0x00451ef0
    void FUN_00452040();       // 0x00452040
    void* BuildNewPhysicsShape(); // 0x00452080
    void FUN_00448fa0(Vec3_s0045_1ef0 v, int one);
    void FUN_0044a0e0();
};
// ---- items of slice s00451ef0 end

// ---- items of slice s00439110 begin (TODO(rewrite): local stubs, replace by canonical classes)
inline void* operator new(size_t, void* p) { return p; }
namespace SP {
struct cSPEditorBlock_s0043_9110;
}
namespace SP {
struct Vector3_s0043_9110 {
    float x, y, z;
    Vector3_s0043_9110() {}
    Vector3_s0043_9110(const Vector3_s0043_9110& v) : x(v.x), y(v.y), z(v.z) {}
    float& operator[](int i) { return (&x)[i]; }
};
}
namespace SP {
struct Matrix3_s0043_9110 {
    float m[9];
    Matrix3_s0043_9110() {}
    Matrix3_s0043_9110(const Matrix3_s0043_9110& other) { Assign(other); }
    void Assign(const Matrix3_s0043_9110& other);             // 0041CB40
};
}
namespace SP {
struct ResourceKey_s0043_9110 {
    uint32_t instanceID, typeID, groupID;
    ResourceKey_s0043_9110() : instanceID(0), typeID(0), groupID(0) {}
};
}
namespace SP {
struct Transform_s0043_9110 {
    uint16_t mFlags;        // +0x00
    uint16_t mChangeCount;  // +0x02
    Vector3_s0043_9110  mOffset;       // +0x04
    float    mScale;        // +0x10
    Matrix3_s0043_9110  mRotation;     // +0x14

    Transform_s0043_9110();                                   // 00409930
    Transform_s0043_9110(const Transform_s0043_9110& other);             // 0040CE80

    void SetOffset(const Vector3_s0043_9110& v) {
        mOffset = v;
        mFlags |= 4;
        mChangeCount++;
    }
    void SetRotation(const Matrix3_s0043_9110& m) {
        mRotation = m;
        mFlags |= 2;
        mChangeCount++;
    }
};
}
namespace SP {
struct cPropertyList_s0043_9110 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual bool HasProperty(uint32_t propertyID) const;   // +0x1C 0x006a2470
};
}
namespace SP {
struct cMorphHandle {
    uint32_t pad0[0x8c / 4];
    uint32_t mChannel;                 // +0x8C
    uint32_t pad90[(0x180 - 0x90) / 4];
    float    mWeight;                  // +0x180
};
}
namespace SP {
struct cSPEditorModel_s0043_9110 {
    bool F4adc40();                    // 004ADC40 (returns byte +0x4f)
};
}
namespace SP {
struct sp_vector_allocator {
    sp_vector_allocator() {}
    sp_vector_allocator(const sp_vector_allocator& x);   // 00429360 (out of line)
};
}
namespace SP {
template <class T> struct SimpleVector {   // vector<T> with out-of-line helpers
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;

    T* erase(T* first, T* last);           // 004769B0
    void DoInsertValue(T* position, const T& value);   // 00455660
    void push_back(const T& value) {       // 004547F0 / 00454860 (declined inline)
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
    void clear() { erase(mpBegin, mpEnd); }
};
}
namespace SP {
template <class T> struct FixedVectorRef {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];
    bool empty() const;                    // 00526430
    int size() const { return (int)(mpEnd - mpBegin); }
    T& operator[](int i) { return mpBegin[i]; }
};
}
namespace SP {
template <int N> inline void ScratchSlots_s0043_9110() { uint32_t s[N]; }
}
namespace SP {
template <int N> struct bitset_s0043_9110 {
    uint32_t mWord[(N + 31) / 32];
    uint32_t DoGetWord(uint32_t i) const { return mWord[i / 32]; }
    bool test(uint32_t i) const {
        if (i < N)
            return (DoGetWord(i) & (1u << (i % 32))) != 0;
        return false;
    }
};
}
namespace SP {
struct HandleState {
    uint32_t data[15];
};
}
namespace SP {
struct alloc_tag { alloc_tag() {} };
}
namespace SP {
struct state_allocator {
    const char* mpName;
    uint32_t mFlags;
    state_allocator(const alloc_tag& tag);       // 00429360 (out of line)
};
}
namespace SP {
struct HandleStateVectorBase {
    HandleState* mpBegin;
    HandleState* mpEnd;
    HandleState* mpCapacity;
    state_allocator mAllocator;

    HandleStateVectorBase(const alloc_tag& a)
        : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(a) {}
    ~HandleStateVectorBase();              // 00455BA0 (frees the buffer)
};
}
namespace SP {
struct HandleStateVector : HandleStateVectorBase {
    HandleStateVector(const alloc_tag& a = alloc_tag())
        : HandleStateVectorBase(a) {}
    __forceinline ~HandleStateVector() {
        for (HandleState* p = mpBegin; p < mpEnd; ++p)
            p->~HandleState();
    }
};
}
namespace SP {
struct empty_allocator {
    const char* mpName;
    uint32_t mFlags;
    empty_allocator() {}
    void deallocate(void* p, size_t n) {
        if (((int*)p)[-1] != 0)
            delete[] (char*)p;
    }
};
}
namespace SP {
struct IRefCounted {
    virtual void v00();
    virtual int AddRef();
    virtual int Release();                  // +0x08
};
}
namespace SP {
struct BlockRef {
    cSPEditorBlock_s0043_9110* mpObject;
    ~BlockRef() {
        if (mpObject)
            ((IRefCounted*)mpObject)->Release();
    }
    operator cSPEditorBlock_s0043_9110*() const { return mpObject; }
};
}
namespace SP {
template <class T> inline void destruct(T* first, T* last) {
    for (; first < last; ++first)
        first->~T();
}
}
namespace SP {
struct BlockVectorBase {
    BlockRef* mpBegin;
    BlockRef* mpEnd;
    BlockRef* mpCapacity;
    empty_allocator mAllocator;
    BlockVectorBase() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~BlockVectorBase() {                    // 00425990 (declined inline)
        if (mpBegin)
            DoFree(mpBegin, mpCapacity - mpBegin);
    }
    void DoFree(BlockRef* p, size_t n) { mAllocator.deallocate(p, n * sizeof(BlockRef)); }
};
}
namespace SP {
struct BlockVector : BlockVectorBase {
    ~BlockVector() { destruct(mpBegin, mpEnd); }   // 00453EB0 (declined inline)
    int size() const { return (int)(mpEnd - mpBegin); }
    BlockRef& operator[](int i) { return mpBegin[i]; }
};
}
namespace SP {
struct cSPEditorBlock_s0043_9110 {
    uint32_t pad0[3];
    AutoRefCount<cPropertyList_s0043_9110> mpPropList;        // +0x00C
    uint32_t pad10[3];
    uint32_t mInstanceID;                          // +0x01C
    uint32_t pad20[2];
    cSPEditorModel_s0043_9110* mpEditorModel;                 // +0x028
    uint32_t pad2c;
    float    field_30;                             // +0x030
    uint32_t pad34;
    uint32_t mUIState;                             // +0x038
    int      mUIStateValue;                        // +0x03C
    uint32_t pad40[2];
    Vector3_s0043_9110  mPosition;                            // +0x048
    uint32_t pad54[3];
    Matrix3_s0043_9110  mTotalOrientation;                    // +0x060
    Matrix3_s0043_9110  mHistoryTotalOrientation;             // +0x084
    Matrix3_s0043_9110  mOrientation;                         // +0x0A8
    Matrix3_s0043_9110  mHistoryBaseOrientation;              // +0x0CC
    Matrix3_s0043_9110  mUserOrientation;                     // +0x0F0
    uint32_t pad114[(0x1c0 - 0x114) / 4];
    int      mSymmetrySign;                        // +0x1C0
    int      mModelSignModifier;                   // +0x1C4
    uint32_t pad1c8[4];
    float    mScale;                               // +0x1D8
    uint32_t pad1dc[(0x340 - 0x1dc) / 4];
    FixedVectorRef<cSPEditorBlock_s0043_9110*> mChildren;     // +0x340
    uint32_t pad354[(0x3a0 - 0x354) / 4];
    Vector3_s0043_9110  mTriangleDirection;                   // +0x3A0
    uint32_t pad3ac[(0x3e0 - 0x3ac) / 4];
    AutoRefCount<cSPEditorBlock_s0043_9110> mpSymmetricRigblock;   // +0x3E0
    uint32_t pad3e4[2];
    AutoRefCount<cSPEditorBlock_s0043_9110> mpBallConnectorHandle; // +0x3EC
    uint32_t pad3f0[(0x6cc - 0x3f0) / 4];
    FixedVectorRef<AutoRefCount<cMorphHandle> > mMorphHandles;   // +0x6CC
    uint32_t pad6e0[(0x704 - 0x6e0) / 4];
    SimpleVector<float> mMorphHandleWeights;       // +0x704
    uint32_t pad714[(0x73c - 0x714) / 4];
    SimpleVector<uint32_t> mMorphHandleChannels;   // +0x73C
    uint32_t pad74c[(0xdc8 - 0x74c) / 4];
    bitset_s0043_9110<60> mBooleanAttributes;                 // +0xDC8

    bool IsFrozen();                                                    // 00435C80
    void SetBooleanAttribute(int index, bool value);                    // 00435A10
    ResourceKey_s0043_9110 GetModelKey(int sign, int flags);                       // 00438F20
    void BuildBlock(uint32_t instanceID, uint32_t groupID, int a, int b,
                    float f, bool c, bool d, bool e);                   // 00441440
    void SetUIState(int state, bool a, bool b, bool c);                 // 0043A5E0
    void ApplyScale(float scale, int flags);                            // 00440090
    void CopyStateFrom(cSPEditorBlock_s0043_9110* other);                          // 00440E00
    void UpdateEffects();                                               // 00449ED0
    void Select(int a, int b);                                          // 0044BCF0
    void Deselect(int a, int b);                                        // 0044BA20
    bool IsSelected();                                                  // 0044C030
    void Invalidate(bool all);                                          // 00447030
    void RebuildPhysics();                                              // 00452040
    void SetUserOrientation(Matrix3_s0043_9110 m);                                 // 0043FFA0
    void SetOrientation(const Matrix3_s0043_9110* m, int flags);                   // 00449420
    void GetOffsetA(Vector3_s0043_9110* out, int flags);                           // 00438120
    void GetOffsetB(Vector3_s0043_9110* out, int flags);                           // 004381E0
    void Place(Vector3_s0043_9110 a, Vector3_s0043_9110 b);                                   // 00437B00
    int  GetBlockType(uint32_t instanceID);                             // 0044E830
    bool CanUseSymmetrySign(int sign);                                  // 0044C5A0
    int  CalculateSymmetrySign();                                       // 0044F240 0x0044f240
    void SetSymmetryFlip(int dir);                                      // 0044C480
    uint32_t GetInstanceID() const { return mInstanceID; }
    cSPEditorBlock_s0043_9110* GetSymmetricBlock() const { return mpSymmetricRigblock; }
    int GetUIStateValue() const { return mUIStateValue; }
    bool GetBooleanAttribute(uint32_t i) const { return mBooleanAttributes.test(i); }

    void SetModelBasedOnSymmetrySign(int sign, bool mirrorOrientation, bool recurse,
                                     bool skipPinned, int depth);
};
}
namespace SP {
bool __cdecl SignsDiffer(int oldSign, int newSign, int flags);                  // 004A7EA0
}
namespace SP {
void __cdecl SaveHandleState(cSPEditorBlock_s0043_9110* block, HandleStateVector* out, bool all); // 0049C8F0
}
namespace SP {
void __cdecl RestoreHandleState(HandleStateVector* state);                     // 0049CB90
}
namespace SP {
Matrix3_s0043_9110 __cdecl MirrorMatrix(const Matrix3_s0043_9110& m, int axis);                      // 004A8E10
}
namespace SP {
void __cdecl BuildPileList(cSPEditorBlock_s0043_9110* block, BlockVector* out, int flags); // 0048C790
}
namespace SP {
void __cdecl MirrorChildTransformA(cSPEditorBlock_s0043_9110* child, Transform_s0043_9110 oldT, Transform_s0043_9110 newT, bool flag); // 0049D390
}
namespace SP {
void __cdecl MirrorChildTransformB(cSPEditorBlock_s0043_9110* child, Transform_s0043_9110 oldT, Transform_s0043_9110 newT, bool flag); // 0049D550
}
// ---- items of slice s00439110 end

// ---- items of slice s00447150 begin (TODO(rewrite): local stubs, replace by canonical classes)
template <class T>
struct AutoRefCount_s0044_7150 {
    T* mpObject;
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
template <int N>
inline void ScratchSlots_s0044_7150()
{
    uint32_t s[N];
}
template <class T>
struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator;

    int size() const { return (int)(mpEnd - mpBegin); }
    T& operator[](int i) { return mpBegin[i]; }
    void push_back(const T& value);     // out of line (0x005402c0)
};
template <class T, int N>
struct fixed_vector_s0044_7150 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[3];
    T mBuffer[N];

    fixed_vector_s0044_7150();  // out of line (0x00533360)
    ~fixed_vector_s0044_7150()
    {
        for (T* p = mpBegin; p < mpEnd; ++p)
            p->~T();
        ScratchSlots_s0044_7150<3>();  // DoFree's frame (declined inline)
        DoFree();
    }
    void DoFree();  // out of line (0x004c0b80): frees mpBegin unless it is the inline buffer

    int size() const { return (int)(mpEnd - mpBegin); }
    T& operator[](int i) { return mpBegin[i]; }
    void resize(unsigned int n);        // out of line (0x00454b80)
};
struct string8 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    uint32_t mAllocator;

    void assign(const char* pBegin, const char* pEnd);  // 0x00454cb0
    string8& operator=(const string8& x)
    {
        if (&x != this)
            assign(x.mpBegin, x.mpEnd);
        return *this;
    }
};
template <class T1, class T2>
struct pair {
    T1 first;
    T2 second;
    pair() : first(), second() {}
};
struct Property_s0044_7150 {
    void* mpData;        // +0x00 (array data, or the inline value itself)
    uint32_t pad04;
    int mnItemCount;     // +0x08
    uint32_t pad0c;
    uint16_t mnFlags;    // +0x10 (0x30 = array)
    uint16_t mnType;     // +0x12

    unsigned int GetItemCount()
    {
        if (mnFlags & 0x30)
            return mnItemCount;
        else if (mnType != 0)
            return 1;
        return 0;
    }
    void* GetItems()
    {
        if (mnFlags & 0x30)
            return mpData;
        else if (mnType != 0)
            return this;
        return 0;
    }
};
class cPropertyList_s0044_7150 {
public:
    virtual int AddRef();
    virtual int Release();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void SetProperty(uint32_t id, const Property_s0044_7150* p);  // 0x006a2e20 (cPropertyList::SetProperty)
    virtual int RemoveProperty(uint32_t id);  // 0x006a2ef0 (cPropertyList::RemoveProperty)
    virtual bool HasProperty(uint32_t id);                       // 0x1c 0x006a2470
    virtual bool GetPropertyAlt(uint32_t id, Property_s0044_7150*& result); // 0x20
    virtual bool GetProperty(uint32_t id, Property_s0044_7150*& result);    // 0x24
    virtual Property_s0044_7150* GetPropertyObject(uint32_t id);            // 0x28
};
bool GetArrayBool(cPropertyList_s0044_7150* list, uint32_t id, int& cnt, bool*& values);  // 0x006a0760
namespace SP {
struct cSPEditorHandleDeform_s0044_7150 {
    uint32_t pad000[0x8c / 4];
    uint32_t mHandleID;                      // +0x8c (cModelDeformationHandle id)
    uint32_t pad090[(0xac - 0x90) / 4];
    uint32_t mPinningType;                   // +0xac
    uint32_t mAxisToIgnore;                  // +0xb0
    cSPEditorHandleDeform_s0044_7150* mSymmetricHandle; // +0xb4
    uint32_t pad0b8[(0x11c - 0xb8) / 4];
    string8 mSoundString;                    // +0x11c
    uint32_t pad12c[(0x1d4 - 0x12c) / 4];
    bool mIsHiddenHandle;                    // +0x1d4
    bool mDoNotPlaceHandle;                  // +0x1d5
};
}
namespace SP {
struct UIntMap {  // eastl::map<uint32_t, uint32_t>
    uint32_t mData[7];
    void Reserve(int n);                      // 0x00454640
    uint32_t& operator[](const uint32_t& key);  // 0x00454750
};
}
namespace SP {
typedef vector<pair<uint32_t, cSPEditorHandleDeform_s0044_7150*> > SoundParamVector;
}
namespace SP {
struct SoundParameterMap {  // eastl::map<uint32_t, vector<pair<uint32_t, cSPEditorHandleDeform*> > >
    uint32_t mData[7];
    SoundParamVector& operator[](const uint32_t& key);  // 0x004544d0
};
}
namespace SP {
extern uint32_t kModelSignModifierHandleID;  // 0x015d25b0
}
namespace SP {
extern uint32_t kLimbTypeHandleID;           // 0x015d2180
}
namespace SP {
extern uint32_t kMuscleScaleHandleID;        // 0x015d22a4
}
namespace SP {
class cSPEditorBlock_s0044_7150 {
public:
    int GetModelSignModifier();              // 0x0043c0a0
    int FindDeformHandleIndex(uint32_t id);  // 0x0043c120
    void InitializeHandleData(cPropertyList_s0044_7150* propList);  // 0x00447150 (SP::cSPEditorBlock::InitializeHandleData)

    uint32_t pad000[3];
    AutoRefCount_s0044_7150<cPropertyList_s0044_7150> mPropList;   // +0x0c
    uint32_t pad010[(0x1b0 - 0x10) / 4];
    int mModelSignModifier;                  // +0x1b0
    int mModelSignModifierHandle;            // +0x1b4
    int mLimbTypeHandle;                     // +0x1b8
    int mMuscleScaleHandle;                  // +0x1bc
    uint32_t pad1c0[(0x614 - 0x1c0) / 4];
    SoundParameterMap mSoundParameterMap;    // +0x614
    UIntMap mAnimationSoundMap;              // +0x630
    uint32_t pad64c[(0x6cc - 0x64c) / 4];
    vector<AutoRefCount_s0044_7150<cSPEditorHandleDeform_s0044_7150> > mDeformationHandles;  // +0x6cc
};
}
// ---- items of slice s00447150 end

// @ 0x004388b0
namespace SP {
void cContentValidationSummarizer::Attach(cContentValidationSummarizer* e)
{
    if (e == 0) return;
    cContentValidationSummarizer** it = entities.begin;
    while (it != entities.end && *it != e) ++it;
    if (it == entities.end) {
        if (e->link33c != 0) e->link33c->RefreshLinked(e);
        cContentValidationSummarizer* p = e;
        if (p != 0) p->AddRef();
        entities.push_back(p);
        if (p != 0) p->Release();
        e->SetLink(this);
        if (e->bits.Get(11)) SetFlag(9, 1);
    }
    int count = entities.end - entities.begin;
    for (int i = 0; i < count; i++) {
    }
}
}  // namespace SP

// @ 0x00438b10
namespace SP {
void cContentValidationSummarizer::Detach(cContentValidationSummarizer* e)
{
    cContentValidationSummarizer** it = entities.begin;
    while (it != entities.end && *it != e) ++it;
    if (it != entities.end) {
        entities.erase(it);
        if (e->bits.Get(11)) {
            SetFlag(9, 1);
            e->SetFlag(9, 1);
        }
        if (e->link33c != 0) {
            cContentValidationSummarizer* old = e->link33c;
            e->link33c = 0;
            old->Release();
        }
        if (e->linkRec != 0) {
            e->linkRec->field0 = 0;
            if (e->linkRec->field4 != 0) {
                LinkTarget* old = e->linkRec->field4;
                e->linkRec->field4 = 0;
                old->Release();
            }
            e->linkRec->field44 = -1;
        }
    }
}
}  // namespace SP

// @ 0x00439110
namespace SP {
void cSPEditorBlock_s0043_9110::SetModelBasedOnSymmetrySign(int symmetrySign, bool flipThisBlockOrientation, bool flipChildren, bool ignoreBallJoints, int depth)
{
    ScratchSlots_s0043_9110<1>();
    if (IsFrozen())
        return;

    HandleStateVector oldHandles;
    HandleStateVector deformState;
    if (depth == 0) {
        SaveHandleState(this, &oldHandles, true);
        SaveHandleState(mpSymmetricRigblock, &deformState, true);
    }

    int desiredModelSign = mModelSignModifier * symmetrySign;
    int oldSymmetrySign = mSymmetrySign;
    if (mpPropList == 0)
        return;
    ScratchSlots_s0043_9110<1>();

    ResourceKey_s0043_9110 key;
    bool needNewModel = false;
    key = GetModelKey(desiredModelSign, 0);
    if (key.instanceID != mInstanceID)
        needNewModel = true;

    Transform_s0043_9110 originalTransform;
    originalTransform.SetOffset(mPosition);
    originalTransform.SetRotation(mTotalOrientation);

    cSPEditorBlock_s0043_9110* symmetricBlock = GetSymmetricBlock();
    bool needFlip = SignsDiffer(mSymmetrySign, symmetrySign, 0);
    mSymmetrySign = symmetrySign;

    if (needNewModel) {
        if (!mMorphHandles.empty()) {
            mMorphHandleWeights.clear();
            mMorphHandleChannels.clear();
            for (int i = 0, listSize = mMorphHandles.size(); i < listSize; ++i) {
                mMorphHandleWeights.push_back(mMorphHandles[i]->mWeight);
                mMorphHandleChannels.push_back(mMorphHandles[i]->mChannel);
            }
        }
        bool isCurrentVisible = IsSelected();
        int uiState = mUIStateValue;
        bool wasFlag23 = GetBooleanAttribute(0x23);
        bool oldFlag33 = GetBooleanAttribute(0x33);
        BuildBlock(key.instanceID, key.groupID, 0, 0, field_30, true, true, true);
        SetBooleanAttribute(0x23, wasFlag23);
        SetBooleanAttribute(0x33, oldFlag33);
        SetUIState(uiState, true, true, true);
        float uniformScale = mScale;
        mScale = 1.0f;
        ApplyScale(uniformScale, 0);
        SetUIState(uiState, true, false, true);
        CopyStateFrom(this);
        UpdateEffects();
        if (isCurrentVisible)
            Select(0, 0);
        else
            Deselect(0, 0);
    }

    bool didFlipMainModel = false;
    if (needFlip && flipThisBlockOrientation) {
        mOrientation = MirrorMatrix(mOrientation, 0);
        mUserOrientation = MirrorMatrix(mUserOrientation, 0);
        didFlipMainModel = true;
    }
    if (needFlip)
        mTriangleDirection[0] *= -1.0f;

    if (mpEditorModel->F4adc40() && symmetricBlock != 0) {
        int symModelSign = -desiredModelSign;
        if (symModelSign == 0) {
            if (!mpPropList->HasProperty(0x3a3b9d21))
                symModelSign = 1;
        }
        key = GetModelKey(symModelSign, 0);
        needNewModel = false;
        symmetricBlock->mSymmetrySign = mSymmetrySign * -1;
        if (key.instanceID != symmetricBlock->mInstanceID)
            needNewModel = true;
        if (needFlip)
            mpSymmetricRigblock->mTriangleDirection[0] *= -1.0f;
        if (needNewModel) {
            bool isCurrentVisible = mpSymmetricRigblock ? mpSymmetricRigblock->IsSelected() : false;
            if (!symmetricBlock->mMorphHandles.empty()) {
                symmetricBlock->mMorphHandleWeights.clear();
                symmetricBlock->mMorphHandleChannels.clear();
                for (int i = 0, listSize = symmetricBlock->mMorphHandles.size(); i < listSize; ++i) {
                    symmetricBlock->mMorphHandleWeights.push_back(symmetricBlock->mMorphHandles[i]->mWeight);
                    symmetricBlock->mMorphHandleChannels.push_back(symmetricBlock->mMorphHandles[i]->mChannel);
                }
            }
            int uiState = symmetricBlock->mUIStateValue;
            bool wasFlag23 = symmetricBlock->GetBooleanAttribute(0x23);
            bool oldFlag33 = symmetricBlock->GetBooleanAttribute(0x33);
            symmetricBlock->BuildBlock(key.instanceID, key.groupID, 0, 0, field_30, true, true, true);
            symmetricBlock->SetBooleanAttribute(0x23, wasFlag23);
            symmetricBlock->SetBooleanAttribute(0x33, oldFlag33);
            symmetricBlock->SetUIState(symmetricBlock->GetUIStateValue(), true, false, true);
            float uniformScale = symmetricBlock->mScale;
            symmetricBlock->mScale = 1.0f;
            symmetricBlock->ApplyScale(uniformScale, 0);
            symmetricBlock->SetUIState(uiState, true, true, true);
            symmetricBlock->CopyStateFrom(this);
            symmetricBlock->UpdateEffects();
            if (isCurrentVisible)
                symmetricBlock->Select(0, 0);
            else
                symmetricBlock->Deselect(0, 0);
        }
    }

    if (needNewModel || oldSymmetrySign != symmetrySign) {
        Invalidate(true);
        RebuildPhysics();
    }

    if (mpSymmetricRigblock != 0) {
        int oldSymSign = mpSymmetricRigblock->mSymmetrySign;
        mpSymmetricRigblock->mSymmetrySign = -symmetrySign;
        if (needNewModel || oldSymSign != -symmetrySign) {
            mpSymmetricRigblock->Invalidate(true);
            mpSymmetricRigblock->RebuildPhysics();
        }
    }

    SetUserOrientation(mUserOrientation);
    ScratchSlots_s0043_9110<2>();
    SetOrientation(&mOrientation, 0);

    Transform_s0043_9110 currentTransform;
    currentTransform.SetOffset(mPosition);
    currentTransform.SetRotation(mTotalOrientation);

    if (!mChildren.empty() && flipChildren) {
        bool keepSymmetric = GetBooleanAttribute(0x13);
        BlockVector pileList;
        BuildPileList(this, &pileList, 0);
        for (int i = 0, pileSize = pileList.size(); i < pileSize; ++i) {
            cSPEditorBlock_s0043_9110* child = pileList[i];
            if (child->IsFrozen()) {
                if (didFlipMainModel || needNewModel || needFlip) {
                    Vector3_s0043_9110 offsetA, offsetB;
                    child->GetOffsetA(&offsetA, 1);
                    child->GetOffsetB(&offsetB, 1);
                    child->Place(offsetA, offsetB);
                }
            } else if (!ignoreBallJoints || !child->GetBooleanAttribute(0x1f)) {
                int childType = child->GetBlockType(child->GetInstanceID());
                ScratchSlots_s0043_9110<12>();
                int signToUse = childType;
                if (needFlip) {
                    MirrorChildTransformA(child, originalTransform, currentTransform, keepSymmetric);
                    MirrorChildTransformB(child, originalTransform, currentTransform, keepSymmetric);
                    signToUse = childType * -1;
                }
                if (!child->CanUseSymmetrySign(signToUse))
                    signToUse = mSymmetrySign;
                int calculatedSign = child->CalculateSymmetrySign();
                if (calculatedSign != 0 && signToUse != 0) {
                    if (calculatedSign != signToUse)
                        child->SetSymmetryFlip(-1);
                    else
                        child->SetSymmetryFlip(1);
                }
                child->SetModelBasedOnSymmetrySign(calculatedSign, false, false, false, depth + 1);
                if (didFlipMainModel || needNewModel || needFlip) {
                    Vector3_s0043_9110 offsetA, offsetB;
                    child->GetOffsetA(&offsetA, 1);
                    child->GetOffsetB(&offsetB, 1);
                    child->Place(offsetA, offsetB);
                    if (child->mpSymmetricRigblock != 0) {
                        Vector3_s0043_9110 offsetA, offsetB;
                        child->mpSymmetricRigblock->GetOffsetA(&offsetA, 1);
                        child->mpSymmetricRigblock->GetOffsetB(&offsetB, 1);
                        child->mpSymmetricRigblock->Place(offsetA, offsetB);
                    }
                }
            }
        }
    }

    if (mpSymmetricRigblock != 0 && needFlip && depth == 0 && mpBallConnectorHandle == 0) {
        RestoreHandleState(&oldHandles);
        RestoreHandleState(&deformState);
    }
}
}  // namespace SP

// @ 0x0043a870
namespace SP {
int cSPEditorBlock_s0043_a460::GetSkinIdentifierForPicking()
{
    int result = 3;
    bool useParent = false;
    if ((char*)&keys == 0) {
        useParent = true;
    } else {
        if (!keys.empty()) {
            int count = (int)(((char*)keys.end - (char*)keys.begin) / 12);
            for (int i = 0; i < count; i++) {
                uint32_t id = *(uint32_t*)((char*)keys.begin + i * 12);
                if (id == 0xE16370D5u) result = 1;
                else if (id == 0x6189D2DEu) result = 0;
            }
        } else {
            useParent = true;
        }
    }
    if (useParent) {
        if (bits.Get(11)) result = 0;
        else result = 1;
    }
    return result;
}
}  // namespace SP

// @ 0x0043a9a0
namespace SP {
void cSPEditorBlock_s0043_a460::F9a0(uint8_t a, uint8_t b)
{
    if (F9e0(a, b)) {
        F5e0((int)f3c, 1, 0, 1);
    }
}
}  // namespace SP

// @ 0x0043a9e0
namespace SP {
bool cSPEditorBlock_s0043_a460::F9e0(uint8_t a, uint8_t b)
{
    if (bits.Get(1)) return false;
    if (f39 == a) return false;
    f40 = *(uint32_t*)&f38;
    f44 = f3c;
    if (f39 != 0) {
        F3cfc0(0, b);
        F448a80();
    } else {
        void* model = mModel;
        if (model != 0) {
            *(uint32_t*)((char*)model + 4) |= 8;
            *(uint8_t*)((char*)model + 0x5C) = 7;
            F448690(g_v4_b);
        }
        F3cad0();
    }
    f39 = a;
    return true;
}
}  // namespace SP

// @ 0x0043ab90
namespace SP {
bool cSPEditorBlock_s0043_a460::Fb90(uint8_t p)
{
    if (f38 == p) return false;
    f40 = *(uint32_t*)&f38;
    f44 = f3c;
    f38 = p;
    if (f3c == 3) {
        if (p == 0) {
            F448a80();
        } else {
            F448690(g_v4_a);
        }
    }
    return true;
}
}  // namespace SP

// @ 0x0043ac40
namespace SP {
bool cSPEditorBlock_s0043_ac40::F3AC40(int type, uint8_t a, uint8_t b)
{
    cur.type = type;
    bool same = prev.a == cur.a && prev.b == cur.b && prev.type == cur.type;
    if (same && b == 0) {
        return false;
    }
    prev = cur;
    switch (cur.type) {
    case 0:
        if (cur.b == 0 || cur.a == 0) {
            if (cur.b == 0) {
                if (cur.a == 0) {
                    if (p3ec != 0) p3ec->SetState(0, 10);
                    if (p3f0 != 0) p3f0->flags.Set(3, false);
                    if (mModel != 0) { mModel->flags.Set(3, true); mModel->state = 10; }
                } else {
                    if (p3ec != 0) p3ec->SetState(1, 5);
                    if (p3f0 != 0) { p3f0->flags.Set(3, true); p3f0->state = 5; }
                    if (mModel != 0) { mModel->flags.Set(3, true); mModel->state = 5; }
                }
            } else {
                if (p3ec != 0) p3ec->SetState(1, 7);
                if (p3f0 != 0) { p3f0->flags.Set(3, true); p3f0->state = 7; }
                if (mModel != 0) { mModel->flags.Set(3, true); mModel->state = 7; }
            }
        } else {
            if (p3ec != 0) p3ec->SetState(1, 8);
            if (mModel != 0) { mModel->flags.Set(3, true); mModel->state = 8; }
        }
        break;
    case 1:
        if (p3ec != 0) p3ec->SetState(1, 6);
        if (p3f0 != 0) { p3f0->flags.Set(3, true); p3f0->state = 6; }
        if (mModel != 0) { mModel->flags.Set(3, true); mModel->state = 6; }
        break;
    case 2:
        if (p3ec != 0) p3ec->SetState(1, 9);
        if (p3f0 != 0) { p3f0->flags.Set(3, true); p3f0->state = 9; }
        if (mModel != 0) { mModel->flags.Set(3, true); mModel->state = 9; }
        break;
    case 4:
        if (p3ec != 0) p3ec->SetState(1, 0xB);
        if (p3f0 != 0) { p3f0->flags.Set(3, true); p3f0->state = 0xB; }
        if (mModel != 0) { mModel->flags.Set(3, true); mModel->state = 0xB; }
        break;
    case 5:
        if (p3ec != 0) p3ec->SetState(1, 0xC);
        if (p3f0 != 0) { p3f0->flags.Set(3, true); p3f0->state = 0xC; }
        if (mModel != 0) { mModel->flags.Set(3, true); mModel->state = 0xC; }
        break;
    }
    return true;
}
}  // namespace SP

// @ 0x0043bbc0
bool SP::cSPEditorBlock_s0043_bbc0::F_43bbc0(int)
{ return mField3c9 || mFlags.test(8); }

// @ 0x0043bc40
void SP::cSPEditorBlock_s0043_bbc0::F_43bc40(float v)
{ F_43bc70(mPosition[0], v); }

// @ 0x0043bc70
bool SP::cSPEditorBlock_s0043_bbc0::F_43bc70(float a, float b)
{
    float x = fabsf(a);
    float tmp = mTolA * mScale;
    __asm {
        movss xmm0, tmp
        maxss xmm0, kMinTolerance
        minss xmm0, kMaxTolerance
        movss tmp, xmm0
    }
    float hi = tmp;
    return x < hi * b;
}

// @ 0x0043bcf0
bool SP::cSPEditorBlock_s0043_bbc0::F_43bcf0(float a, float b)
{ float t = fabsf(a); return mTolB * mScale * b > t; }

// @ 0x0043bd50
void SP::cSPEditorBlock_s0043_bbc0::F_43bd50(cSPVector3_s0043_bbc0 v, float s)
{ F_43bc70(v[0], s); }

// @ 0x0043bd80
bool SP::cSPEditorBlock_s0043_bbc0::F_43bd80(cSPMatrix3_s0043_bbc0 m, float s)
{
    cSPMatrix3_s0043_bbc0 p15(m);
    cSPVector3_s0043_bbc0 tmp(mPosition);
    cSPMatrix3_s0043_bbc0 n25 = MatA(this, m);
    cSPMatrix3_s0043_bbc0 u = MatB(this);
    int v32 = 0;
    if (fabsf(u.r[0][0]) > 0.0) v32 = 0;
    else if (fabsf(u.r[1][0]) > 0.0) v32 = 1;
    else if (fabsf(u.r[2][0]) > 0.0) v32 = 2;
    float chunk = Vec3Dist(m[v32], n25[v32]);
    float v4 = mTolC;
    if (v4 * s > chunk) return true;
    else return false;
}

// @ 0x0043bf20
bool SP::cSPEditorBlock_s0043_bbc0::F_43bf20(uint32_t out)
{
    if (mPropList && mPropList->HasProperty(0xf9efbb))
        return SP::GetPropertyAsKey(mPropList, 0xf9efbb, out);
    return false;
}

// @ 0x0043bf90
void SP::cSPEditorBlock_s0043_bbc0::F_43bf90(uint32_t bit, bool on)
{
    if (mModel) mModel->mGroups.set(bit, on);
}

// @ 0x0043c040
int SP::cSPEditorBlock_s0043_bbc0::F_43c040()
{
    if (mModel) return mDeformationHandles.size();
    return mSavedHandleDeltas.size();
}

// @ 0x0043c0a0
int SP::cSPEditorBlock_s0043_bbc0::F_43c0a0()
{
    for (int i = 0, size = mDeformationHandles.size(); i < size; i++)
        if (mDeformationHandles[i]->mAnimationID == 0x9310d4c0) return i;
    return 0;
}

// @ 0x0043c120
int SP::cSPEditorBlock_s0043_bbc0::F_43c120(uint32_t id)
{
    for (int i = 0, size = mDeformationHandles.size(); i < size; i++)
        if (mDeformationHandles[i]->mAnimationID == id) return i;
    return -1;
}

// @ 0x0043c1a0
SP::cSPEditorHandleDeform_s0043_bbc0* SP::cSPEditorBlock_s0043_bbc0::F_43c1a0()
{ if (mHandleIndex[0] == -1) return F_43c270(0); else return F_43c270(mHandleIndex[0]); }

// @ 0x0043c1e0
SP::cSPEditorHandleDeform_s0043_bbc0* SP::cSPEditorBlock_s0043_bbc0::F_43c1e0()
{ if (mHandleIndex[1] == -1) return 0; else return F_43c270(mHandleIndex[1]); }

// @ 0x0043c210
SP::cSPEditorHandleDeform_s0043_bbc0* SP::cSPEditorBlock_s0043_bbc0::F_43c210()
{ if (mHandleIndex[2] == -1) return 0; else return F_43c270(mHandleIndex[2]); }

// @ 0x0043c240
SP::cSPEditorHandleDeform_s0043_bbc0* SP::cSPEditorBlock_s0043_bbc0::F_43c240()
{ if (mHandleIndex[3] == -1) return 0; else return F_43c270(mHandleIndex[3]); }

// @ 0x0043c270
SP::cSPEditorHandleDeform_s0043_bbc0* SP::cSPEditorBlock_s0043_bbc0::F_43c270(int i)
{ if (i < mDeformationHandles.size() && i >= 0) return mDeformationHandles[i].get(); else return 0; }

// @ 0x0043c2d0
float SP::cSPEditorBlock_s0043_bbc0::F_43c2d0(uint32_t i)
{
    if (i < (uint32_t)F_43c040()) {
        if (mModel) return mDeformationHandles[i]->mDelta;
        return mSavedHandleDeltas[i];
    }
    return 0.0f;
}

// @ 0x0043c340
uint32_t SP::cSPEditorBlock_s0043_bbc0::F_43c340(uint32_t i)
{
    if (i < (uint32_t)F_43c040()) {
        if (mModel) return mDeformationHandles[i]->mAnimationID;
        else if (i < (uint32_t)mSavedHandleAnimIDs.size()) return mSavedHandleAnimIDs.mpBegin[i];
    }
    return 0;
}

// @ 0x0043c3d0
int SP::cSPEditorBlock_s0043_bbc0::F_43c3d0(cSPEditorHandleDeform_s0043_bbc0* c)
{
    if (c) {
        int res = -1;
        for (int i = 0, n = mDeformationHandles.size(); i < n; i++)
            if (mDeformationHandles[i].get() == c) return i;
    }
    return -1;
}

// @ 0x0043c450
bool SP::cSPEditorBlock_s0043_bbc0::F_43c450(cSPEditorHandleDeform_s0043_bbc0* c, float f, float* a, bool b)
{
    if (mModel && c) {
        int idx = F_43c3d0(c);
        if (idx != -1) {
            F_43d690(idx, f, a, b, true);
            if (mEditorModel && mEditorModel->Func4adc40() && mSymmetricBlock)
                mSymmetricBlock->F_43d690(idx, f, a, b, true);
            return true;
        }
    }
    return false;
}

// @ 0x0043c510
bool SP::cSPEditorBlock_s0043_bbc0::F_43c510()
{
    if (mFlags.test(11)) {
        if (!mChildBlockList.Func526430()) {
            for (int i = 0, n = mChildBlockList.size(); i < n; i++)
                if (mChildBlockList[i]->mFlags.test(44)) return mFlags.test(0);
            return false;
        } else return mFlags.test(0);
    } else return mFlags.test(0);
}

// @ 0x0043c710
void SP::cSPEditorBlock_s0043_bbc0::F_43c710()
{
    bool ok = false, value = false, ret = false;
    if (mEditorModel) { ok = mEditorModel->Func4adb80(); value = mEditorModel->Func4adbc0(); }
    void* obj = GetCurrentThing();
    if (obj) {
        if (!mFlags.test(25)) {
            for (int i = 0; i < 3; i++) {
                if (mRotationRingHandles[i] && (!mRotationRingHandles[i]->IsHidden() || ok)) {
                    mRotationRingHandles[i]->Update();
                    ret = true;
                }
            }
            if (mRotationBallHandle) { mRotationBallHandle->Update(); ret = true; }
        }
        if (!mFlags.test(24)) {
            int n = mDeformationHandles.size();
            int idx = (mFlags.test(11) && !value) ? mHandleIndex[0] : -1;
            for (int i = 0, count = mDeformationHandles.size(); i < count; i++) {
                if (i == idx) continue;
                if (mDeformationHandles[i]->mIsHiddenHandle && !ok) continue;
                mDeformationHandles[i]->Update();
                ret = true;
            }
        }
        if (ret) PostMessageId(0xa95d8242);
    }
}

// @ 0x0043ca10
bool SP::cSPEditorBlock_s0043_bbc0::F_43ca10()
{ return !mFlags.test(7) && !mFlags.test(20); }

// @ 0x0043cad0
namespace SP {
void cSPEditorBlock_s0043_cad0::F3cad0()
{
    bool f6 = false, f5 = false;
    if (node != 0) {
        f6 = Sub_4ADB80() ? true : false;
        f5 = Sub_4ADBC0() ? true : false;
    }
    bool changed = false;
    if (!f6) F3ce40();
    if ((flags0 & 0x2000000u) == 0) {
        for (int i = 0; i < 3; i++) {
            Blk* b = slots[i];
            if (b != 0 && (*(uint8_t*)((char*)b + 0x92) == 0 || f6)) {
                b->SetState(3, 1);
                changed = true;
            }
        }
        if (slot160 != 0 && (*(uint8_t*)((char*)slot160 + 0x5D) == 0 || f6)) {
            slot160->SetState(3, 1);
            changed = true;
        }
    }
    if ((flags0 & 0x1000000u) == 0) {
        int skip = -1;
        if ((flags0 & 0x800u) != 0 && !f5) skip = f1b0;
        int count = (int)(vec6d0 - vec6cc);
        for (int i = 0; i < count; i++) {
            Blk* b = *(Blk**)((char*)vec6cc + i * 4);
            if (i != skip && (*(uint8_t*)((char*)b + 0x1D4) == 0 || f6)) {
                b->SetState(3, 1);
                changed = true;
            }
        }
    }
    if (changed) Sub_4A88D0(0xD0A55625);
}
}  // namespace SP

// @ 0x0043ce00
namespace SP {
Blk* cSPEditorBlock_s0043_cad0::GetSlot(int i)
{
    if (i >= 0 && i < 3) {
        Blk* p = slots[i];
        return p;
    }
    return 0;
}
}  // namespace SP

// @ 0x0043ce40
namespace SP {
void cSPEditorBlock_s0043_cad0::F3ce40()
{
    if (Sub_401060() == 0) return;
    for (int i = 0; i < 3; i++) {
        Blk* b = slots[i];
        if (b != 0 && *(uint8_t*)((char*)b + 0x92) != 0) b->SetState(1, 1);
    }
    if (slot160 != 0 && *(uint8_t*)((char*)slot160 + 0x5D) != 0) slot160->SetState(1, 1);
    int count = (int)(vec6d0 - vec6cc);
    for (int i = 0; i < count; i++) {
        Blk* b = *(Blk**)((char*)vec6cc + i * 4);
        if (*(uint8_t*)((char*)b + 0x1D4) != 0) b->SetState(1, 1);
    }
}
}  // namespace SP

// @ 0x0043cfc0
namespace SP {
void cSPEditorBlock_s0043_cad0::F3cfc0(int p2, char p3)
{
    if (Sub_401060() == 0) return;
    if ((flags0 & 0x2000000u) == 0) {
        for (int i = 0; i < 3; i++) {
            Blk* b = slots[i];
            if (b != 0 && (void*)b != (void*)p2) b->SetState(1, 1);
        }
        if (slot160 != 0 && (void*)slot160 != (void*)p2) slot160->SetState(1, 1);
    }
    if (p3 != 0 && Sub_4A6120(this)) {
        uint8_t d = 0;
        if (p2 != 0 && (void*)p2 == p3ec) d = 1;
        Sub_4A6660(this, d);
    }
    if ((flags0 & 0x1000000u) == 0) {
        int count = (int)(vec6d0 - vec6cc);
        for (int i = 0; i < count; i++) {
            void* e = *(void**)((char*)vec6cc + i * 4);
            if ((void*)p2 != e) ((Blk*)e)->SetState(1, 1);
        }
    }
}
}  // namespace SP

// @ 0x0043d240
namespace SP {
Vec3* cSPEditorBlock_s0043_cad0::F3d240(Vec3* out, char p3)
{
    void* mdl = mModel;
    uint8_t large = ((uint32_t)mdl & 0x400000) != 0;
    if (large) {
        if (p3 == 0) {
            float key = *(float*)((char*)mdl + 0x18);
            Vec3* r = (Vec3*)0;
            r = (Vec3*)Sub_41DCA0(out, (char*)this + 0x2FC, &key);
            out->x = r->x; out->y = r->y; out->z = r->z;
        } else {
            out->x = out->y = out->z = 0.0f;
        }
    } else if (p3 == 0) {
        GetBBox(this, out, 1, 0, 0);
        BoundingBox_GetCenter(out);
    } else {
        GetBBox(this, out, 0, 0, 0);
        BoundingBox_GetCenter(out);
    }
    return out;
}
}  // namespace SP

// @ 0x0043d420
namespace SP {
void cSPEditorBlock_s0043_cad0::F3d420()
{
    if (mModel == 0) return;
    if ((flags1 & 0x80u) == 0) return;
    if (f2bc == -1) return;
}
}  // namespace SP

// @ 0x0043d690
namespace SP {
bool cSPEditorBlock_s0043_d690::SetMorphHandleWeight(int index, float weight, int arg3, bool updateChildren, bool updateSymmetric)
{
    int q_p = mMorphHandles.size();
    if (index < q_p) {
        mMorphHandles[index]->SetWeight(weight);
        mMorphHandles[index]->Update();
        float q_p7 = 0.0f;
        float q_t13 = 0.0f;
        mpModelWorld->GetAnimationRange(mpModel, mMorphHandles[index]->mAnimID, &q_p7, &q_t13, 0);
        float q_n23 = (q_t13 - q_p7) * mMorphHandles[index]->mWeight + q_p7;
        mpModelWorld->MoveToTime(mpModel, mMorphHandles[index]->mAnimID, q_n23, 0);
        UpdateMorphs();

        if (mpModel && mBooleanAttributes.test(0x36) && mCSnapBoneIndex != -1) {
            int q_n23 = mpModelWorld->GetNumBones(mpModel);
            Transform q_v36;
            ScratchSlots<3>();
            fixed_vector<BoneTransform, 64> q_t20(q_n23);
            mpModelWorld->GetBoneTransforms(mpModel, q_t20.data());
            BoneTransformToTransform(q_t20.mpBegin + mCSnapBoneIndex, &q_v36);
            ScratchSlots<17>();
            q_v36.Accumulate(mCSnapBoneTransform1);
            q_v36.AccumulateScaled(*mpModelWorld->GetMeshTransform(mpModel));
            ScratchSlots<15>();
            q_v36.mScale = 1.0f;
            q_v36.mChangeCount++;
            mCSnapBoneTransform2 = q_v36;
        }

        if (mBooleanAttributes.test(0xb) && index == mSelectedMorphHandle) {
            mSocketConnectorOffset = mModelMinSocketConnectorOffset +
                weight * (mModelMaxSocketConnectorOffset - mModelMinSocketConnectorOffset);
            if (mpSocketConnectorModel) {
                ScratchSlots<6>();
                Vector3P position = mPosition + GetSocketConnectorPosition();
                ScratchSlots<6>();
                mpSocketConnectorModel->mTransform.SetOffset(mPosition + GetSocketConnectorPosition());
            }
            if (mBooleanAttributes.test(0xa))
                SetBooleanAttribute(9, true);
        }

        UpdateBoundingBox();
        if (updateChildren) {
            if (!mChildren.empty()) {
                for (int i = 0, n = mChildren.size(); i < n; i++)
                    mChildren[i]->SyncTransform(true);
            }
            if (!mMorphHandles.empty())
                UpdateOthers(index, true);
        }
        field_1A8 = true;

        if (updateSymmetric && mMorphHandles[index]->mpSymmetricHandle != 0) {
            int other = FindMorphHandleIndex(mMorphHandles[index]->mpSymmetricHandle);
            if (other != index)
                SetMorphHandleWeight(other, weight, arg3, updateChildren, false);
        }

        for (int j = 0; j < 3; j++) {
            if (mAxisHandles[j]) {
                mAxisHandles[j]->UpdatePosition();
                mAxisHandles[j]->Update();
            }
        }
        return true;
    }
    return false;
}
}  // namespace SP

// @ 0x0043e080
namespace SP {
Vec3* cSPEditorBlockStub::F3e080(Vec3* out)
{
    void* r = Sub_41DCA0(&v40c, (char*)this + 0x1D8, &v40c.x);
    Vec3* p = (Vec3*)Sub_41DAF0(out, r);
    out->x = p->x;
    out->y = p->y;
    out->z = p->z;
    return out;
}
}  // namespace SP

// @ 0x0043e0f0
namespace SP {
bool cSPEditorBlockStub::F3e0f0(int* out)
{
    int n = 0;
    (void)n;
    int count = (int)(vec6d0 - vec6cc);
    if (out == 0 || count <= 0) return false;
    return false;
}
}  // namespace SP

// @ 0x0043e2b0
namespace SP {
void cSPEditorBlockStub::F3e2b0()
{
    int count = (int)(vec6d0 - vec6cc);
    f440 = 0.4f;
    f444 = -0.35f;
    if (count > 0) {
        f43c = 0;
        for (int i = 0; i < count; i++) {
            if ((flags0 & 0x800u) == 0 || i != 0) {
                Blk_s0043_d690* b = *(Blk_s0043_d690**)((char*)vec6cc + i * 4);
                F3d690(i, *(int*)((char*)b + 0xA8), 0, 0, 1);
            }
        }
    }
}
}  // namespace SP

// @ 0x0043e3f0
void SP::cSPEditorBlock_s0043_e3f0::F_43e3f0(float dt, uint32_t index)
{
    if (GetEditorModel()) {
        float scale = GetEditorModel()->GetScale();
        float a = 0.01f * scale;
        float b = 0.2f * scale;
        float c = 3.0f * g_15d257c;
        if (index >= 0 && index < (uint32_t)mDeformationHandles.size()) {
            mField448 += dt;
            SP::cSPEditorHandleDeform_s0043_e3f0* handle = mDeformationHandles[index];
            cSPVector3_s0043_e3f0 d = handle->mEndPt - handle->mStartPt;
            float len = Length(d);
            if (b > len) len = b;
            float amp = a / len;
            float off = 0.0f;
            if (amp > mField44c) off = amp - mField44c;
            else if (amp > 1.0f - mField44c) off = -(amp - (1.0f - mField44c));
            float phase = 0.0f;
            if (off != 0.0f) phase = asinf(-off / amp);
            float v1 = sinf(mField448 * c + phase) * amp + off;
            float v0 = sinf(0.0f * c + phase) * amp + off;
            float v = Clamp(mField44c + v1, 0.0f, 1.0f);
            F_43c450(handle, v, &mField44c, true);
            F_449ce0();
        }
    }
}

// @ 0x0043e760
void SP::cSPEditorBlock_s0043_e3f0::F_43e760(uint32_t index)
{
    if (index < (uint32_t)mDeformationHandles.size() && index >= 0) {
        SP::cSPEditorHandleDeform_s0043_e3f0* handle = mDeformationHandles[index];
        mField44c = handle->mDelta;
        handle->mDoNotPlaceHandle = true;
        mField448 = 0.0f;
    }
}

// @ 0x0043e7e0
void SP::cSPEditorBlock_s0043_e3f0::F_43e7e0(uint32_t index, bool b)
{
    if (index < (uint32_t)mDeformationHandles.size() && index >= 0) {
        SP::cSPEditorHandleDeform_s0043_e3f0* handle = mDeformationHandles[index];
        mField448 = 0.0f;
        handle->mDoNotPlaceHandle = false;
        F_43d690(index, mField44c, 0, b, true);
        if (mEditorModel && mEditorModel->Func4adc40() && mSymmetricBlock)
            mSymmetricBlock->F_43d690(index, handle->mDelta, 0, b, true);
    }
}

// @ 0x0043e8d0
bool SP::cSPEditorBlock_s0043_e3f0::F_43e8d0(int id)
{ return mFadeId == id && mFader.IsActive(); }

// @ 0x0043e920
bool SP::cSPEditorBlock_s0043_e3f0::F_43e920()
{ return mFader.IsActive(); }

// @ 0x0043e940
void SP::cSPEditorBlock_s0043_e3f0::F_43e940(uint32_t a, uint32_t b, int id)
{
    mFadeId = id;
    mFadeArg = b;
    if (mFader.IsActive()) {
        if (id != 1) mFader.Start(a, 0.1f);
    } else {
        mFader.Start(a, 0.1f);
    }
}

// @ 0x0043e9c0
void SP::cSPEditorBlock_s0043_e3f0::F_43e9c0()
{
    F_43ea20();
    if (mEditorModel && mEditorModel->Func4adc40() && mSymmetricBlock)
        mSymmetricBlock->F_43ea20();
}

// @ 0x0043ea20
void SP::cSPEditorBlock_s0043_e3f0::F_43ea20()
{ mFader.Stop(); }

// @ 0x0043ea40
void SP::cSPEditorBlock_s0043_e3f0::F_43ea40(int id)
{
    F_43eaa0(id);
    if (mEditorModel && mEditorModel->Func4adc40() && mSymmetricBlock)
        mSymmetricBlock->F_43eaa0(id);
}

// @ 0x0043eaa0
void SP::cSPEditorBlock_s0043_e3f0::F_43eaa0(int id)
{
    if (mField604) F_43e940(mField604, mField608, id);
}

// @ 0x0043eae0
void SP::cSPEditorBlock_s0043_e3f0::F_43eae0(float v)
{
    F_440390(v);
    if (mEditorModel && mEditorModel->Func4adc40() && mSymmetricBlock)
        mSymmetricBlock->F_440390(v);
}

// @ 0x0043eb50
void SP::cSPEditorBlock_s0043_e3f0::F_43eb50(float v)
{
    F_440110(v);
    if (mEditorModel && mEditorModel->Func4adc40() && mSymmetricBlock)
        mSymmetricBlock->F_440110(v);
}

// @ 0x0043ebc0
bool SP::cSPEditorBlock_s0043_e3f0::F_43ebc0()
{
    bool result = false;
    if (F_43c210()) {
        if (GetRangeMax() > GetRangeMin()) {
            float t = (mField1d4 - GetRangeMin()) / (GetRangeMax() - GetRangeMin());
            float cur = F_43c210()->mDelta;
            if (t != cur) {
                F_43c450(F_43c210(), t, 0, true);
                result = true;
            }
        }
    }
    return result;
}

// @ 0x0043ecb0
bool SP::cSPEditorBlock_s0043_e3f0::F_43ecb0()
{
    bool result = false;
    if (F_43c1e0()) {
        SP::cSPEditorBlock_s0043_e3f0* best = 0;
        for (int i = 0, n = mChildBlockList.size(); i < n; i++) {
            if (mChildBlockList[i]->mField3ec) {
                if (!best || best->F_43eed0() < mChildBlockList[i]->F_43eed0())
                    best = mChildBlockList[i];
            }
        }
        if (best) {
            float v = best->F_43eed0();
            if (GetRangeMin() > v) v = mRangeMin;
            else if (v > GetRangeMax()) v = mRangeMax;
            if (GetRangeMax() > GetRangeMin()) {
                float t = (v - GetRangeMin()) / (GetRangeMax() - GetRangeMin());
                float cur = F_43c1e0()->mDelta;
                if (t != cur) {
                    F_43c450(F_43c1e0(), t, 0, true);
                    result = true;
                }
            }
        }
    }
    return result;
}

// @ 0x0043eef0
cSPBoundingBox_s0043_e3f0 SP::cSPEditorBlock_s0043_e3f0::F_43eef0()
{
    cSPBoundingBox_s0043_e3f0 box;
    float r = F_43f3a0();
    box.Extend(cSPVector3_s0043_e3f0(r, 0.0f, 0.0f));
    box.Extend(cSPVector3_s0043_e3f0(-r, 0.0f, 0.0f));
    if (!mFlags.test(11) && !mFlags.test(20))
        box.Add(GetBBox(true, false, false));
    return box;
}

// @ 0x0043f050
void cSPBoundingBox_s0043_e3f0::Add(const cSPBoundingBox_s0043_e3f0& o)
{
    if (IsEmpty()) {
        mMin = o.mMin;
        mMax = o.mMax;
    } else {
        if (mMin[0] > o.mMin[0]) mMin[0] = o.mMin[0];
        if (mMax[0] < o.mMax[0]) mMax[0] = o.mMax[0];
        if (mMin[1] > o.mMin[1]) mMin[1] = o.mMin[1];
        if (mMax[1] < o.mMax[1]) mMax[1] = o.mMax[1];
        if (mMin[2] > o.mMin[2]) mMin[2] = o.mMin[2];
        if (mMax[2] < o.mMax[2]) mMax[2] = o.mMax[2];
    }
}

// @ 0x0043f250
float SP::cSPEditorBlock_s0043_e3f0::F_43f250()
{
    cSPBoundingBox_s0043_e3f0 box = F_43eef0();
    return Length(box.GetCorner(0)) / 2.0f;
}

// @ 0x0043f290
cSPVector3_s0043_e3f0 cSPBoundingBox_s0043_e3f0::GetCorner(uint32_t mask) const
{
    cSPVector3_s0043_e3f0 v;
    v[0] = (mask & 1) ? mMax[0] : mMin[0];
    v[1] = (mask & 2) ? mMax[1] : mMin[1];
    v[2] = (mask & 4) ? mMax[2] : mMin[2];
    return v;
}

// @ 0x0043f3a0
namespace SP {
float cSPEditorBlock_s0043_f3a0::F3a0()
{
    void* p = p3ec;
    if (p != 0) {
        return F3eed0() * 0.3f * 0.5f * f454;
    }
    return 0.0f;
}
}  // namespace SP

// @ 0x0043f3f0
namespace SP {
float cSPEditorBlock_s0043_f3a0::F3f0()
{
    int count = vec340.size();
    for (int i = 0; i < count; i++) {
        cSPEditorBlock_s0043_f3a0* o = vec340.begin[i];
        if (o->bits.Get(31)) return o->F3eed0();
    }
    return 1.0f;
}
}  // namespace SP

// @ 0x0043f4d0
namespace SP {
float cSPEditorBlock_s0043_f3a0::F4d0()
{
    int count = vec340.size();
    for (int i = 0; i < count; i++) {
        cSPEditorBlock_s0043_f3a0* o = vec340.begin[i];
        if (o->bits.Get(31)) return o->F3f250();
    }
    return 1.0f;
}
}  // namespace SP

// @ 0x0043f5b0
namespace SP {
void cSPEditorBlock_s0043_f3a0::F5b0(Vec3* out, float a, float b, float c, int flag)
{
    cSPBoundingBox_s0043_e3f0 base = F3eef0();
    if (flag > 0) {
        cSPVector3_s0043_e3f0 p = base.GetCorner(0);
        if (0.0f > a + p.x) {
            cSPVector3_s0043_e3f0 q = base.GetCorner(0);
            a = -q.x;
        }
    } else {
        cSPVector3_s0043_e3f0 p = base.GetCorner(1);
        if (a + p.x >= 0.0f) {
            cSPVector3_s0043_e3f0 q = base.GetCorner(1);
            a = -q.x;
        }
    }
    out->x = a;
    out->y = b;
    out->z = c;
}
}  // namespace SP

// @ 0x0043f6b0
namespace SP {
void cSPEditorBlock_s0043_f3a0::SetValid(char valid, int arg)
{
    uint8_t wasLinked = (uint8_t)((bits.data[1] & 2u) != 0);
    F3a5e0(1, (uint8_t)(valid == 0), 1, 0);
    if (valid == 0) {
        F3a5e0(1, 1, 0, 1);
        if (arg != 0 && (bits.data[1] & 0x400u) != 0) { }
        return;
    }
    F3a5e0(0, 1, 0, 0);
    if (arg != 0 && (bits.data[1] & 0x400u) != 0) { }
    (void)wasLinked;
}
}  // namespace SP

// @ 0x0043fc20
namespace SP {
bool cSPEditorBlock_s0043_f3a0::F3fc20(void* pos)
{
    int n = (int)node;
    if (n != 0) *(int*)(n + 8) = *(int*)(n + 8) + 1;
    uint8_t saved = node ? (uint8_t)(node->Check() ? 1 : 0) : 0;
    Sub_4ADC20(0);
    bool flag = (bits.data[1] & 0x80000u) != 0;
    uint8_t result = 0;
    if ((bits.data[0] & 0x80u) == 0) {
        Vec3* src = pos ? (Vec3*)pos : (Vec3*)((char*)this + 0x48);
        Vec3 local = *src;
        float f = F3eed0();
        (void)f;
        int r = Sub_493640(&local, f);
        uint8_t notThree = (uint8_t)(r != 3);
        if (notThree && !flag) result = 1;
        if (link33c == 0 && !F49b340()) result = 1;
        if ((bits.data[0] & 0x100000u) != 0) result = 0;
        if ((bits.data[1] & 0x400u) != 0) result = 1;
        if (link33c != 0 && (link33c->bits.data[0] & 2u) != 0) result = 1;
    }
    Sub_4ADC20((int)saved);
    bool b = result == 0;
    if (n != 0) ((DefaultRefCounted*)(n + 4))->Release();
    return b;
}
}  // namespace SP

// @ 0x0043ffa0
namespace SP {
void cSPEditorBlock_s0043_f3a0::FFa0(Matrix3_s0043_f3a0 m)
{
    F404f0(m);
    if (node != 0 && node->Check() && link3e0 != 0) {
        link3e0->F404f0(Sub_4A8E10(&m, 0));
    }
}
}  // namespace SP

// @ 0x00440020
namespace SP {
void cSPEditorBlock_s0043_f3a0::F4020(float v, uint8_t b)
{
    F40420(v, b);
    if (node != 0) {
        if (node->Check() && link3e0 != 0) {
            link3e0->F40420(v, b);
        }
    }
}
}  // namespace SP

// @ 0x00440090
namespace SP {
void cSPEditorBlock_s0043_f3a0::F4090(float v, uint8_t b)
{
    F40520(v, b, 0);
    if (node != 0) {
        if (node->Check() && link3e0 != 0) {
            link3e0->F40520(v, b, 0);
        }
    }
}
}  // namespace SP

// @ 0x00440390
namespace SP {
void cSPEditorBlock_s0044_0110::F40390(float f)
{
    float lo = 0.0f, hi = 1.0f;
    float v = f;
    v = v > lo ? v : lo;
    v = v < hi ? v : hi;
    if (v != *(float*)((char*)this + 0x1D0)) {
        *(float*)((char*)this + 0x1D0) = v;
        SetFlag(9, 1);
    }
}
}  // namespace SP

// @ 0x00440420
namespace SP {
void cSPEditorBlock_s0044_0110::F40420(float f, char b)
{
    float old = *(float*)((char*)this + 0x1DC);
    *(float*)((char*)this + 0x1DC) = f;
    if (*(float*)((char*)this + 0x1DC) > *(float*)((char*)this + 0x1E4)) {
        *(float*)((char*)this + 0x1DC) = *(float*)((char*)this + 0x1E4);
    } else if (*(float*)((char*)this + 0x1E0) > *(float*)((char*)this + 0x1DC)) {
        *(float*)((char*)this + 0x1DC) = *(float*)((char*)this + 0x1E0);
    }
    if (b != 0 && p3ec != 0) {
        F40110((*(float*)((char*)this + 0x1DC) / old) * *(float*)((char*)this + 0x1D4));
    }
}
}  // namespace SP

// @ 0x004404f0
namespace SP {
void cSPEditorBlock_s0044_0110::F404f0(Matrix3_s0044_0110 m)
{
    Sub_698650(&m);
    uint32_t* dst = (uint32_t*)((char*)this + 0xF0);
    uint32_t* src = (uint32_t*)&m;
    for (int i = 0; i < 9; i++) dst[i] = src[i];
}
}  // namespace SP

// @ 0x00440520
namespace SP {
void cSPEditorBlock_s0044_0110::SetUniformScale(float scale, bool b, bool force)
{
    if (mUniformScale != scale || force) {
        float oldScale = mUniformScale;
        scale = Clamp_s0044_0110(scale, mMinUniformScale, mMaxUniformScale);
        mUniformScale = scale;
        if (mpModel) {
            if (mBooleanAttributes.test(7) && mVertebraAnimID) {
                float end;
                float start;
                mpModelWorld->GetAnimationRange(mpModel, mVertebraAnimID, &start, &end, 0);
                float t = InverseLerp(scale, mMinUniformScale, mMaxUniformScale);
                mpModelWorld->MoveToTime(mpModel, mVertebraAnimID, (end - start) * t + start, 0);
                if (mIsFullInit) {
                    mpModelWorld->UpdateModel(mpModel, 0);
                    if (mPropList && mPropList->HasKey(0xF9EFC0))
                        mpModelWorld->ApplyModel(mpModel, 0);
                }
            } else {
                mpModel->mTransform.SetScale(scale);
            }
        }
        if (b) {
            if (mBooleanAttributes.test(31))
                F40110((mUniformScale / oldScale) * mDefaultMouseOffset);
            if (mpSocketConnectorModel)
                mpSocketConnectorModel->mTransform.SetScale(scale);
        }
        if (mpSocketConnectorModel) {
            ScratchSlots<7>();
            mpSocketConnectorModel->mTransform.SetOffset(mPosition + GetSocketConnectorPosition());
        }
        for (int i = 0; i < 3; i++) {
            if (mRotationRingHandles[i]) {
                mRotationRingHandles[i]->UpdateAnimTime();
                mRotationRingHandles[i]->Update();
                if (mRotationRingHandles[i]->IsFlagSet())
                    mRotationRingHandles[i]->ApplyAnimTime();
            }
        }
        if (mRotationBallHandle)
            mRotationBallHandle->Update();
        field_1A8 = true;
        SetFlag(9, 1);
    }
}
}  // namespace SP

// @ 0x00440b90
namespace SP {
Vec3* cSPEditorBlock_s0044_0110::F40b90(Vec3* out)
{
    *out = v5f8;
    return out;
}
}  // namespace SP

// @ 0x00440bc0
namespace SP {
void cSPEditorBlock_s0044_0110::F40bc0(const Vec3* v)
{
    void* model = mModel;
    if (model != 0) {
        void* m = mModel;
        *(Vec3*)((char*)m + 0x4C) = *v;
    }
}
}  // namespace SP

// @ 0x00440c00
namespace SP {
void cSPEditorBlock_s0044_0110::F40c00(float f)
{
    if (mModel != 0) {
        void* m = mModel;
        *(float*)((char*)m + 0x58) = f;
    }
}
}  // namespace SP

// @ 0x00440e00
namespace SP {
void cSPEditorBlock_s0044_0110::F40e00(cSPEditorBlock_s0044_0110* o)
{
    char* it = (char*)o->list4c8;
    char* end = (char*)o->list4cc;
    for (; it != end; it += 0x20) {
        F40c40(it + 4, *(int*)it);
    }
}
}  // namespace SP

// @ 0x00440f60
namespace SP {
Trans::Trans()
{
    flag = 0;
    a = g_v3_241c;
    b = g_v3_241c;
}
}  // namespace SP

// @ 0x00440ff0
namespace SP {
Trans::Trans(const Trans& o)
{
    flag = o.flag;
    a = o.a;
    b = o.b;
}
}  // namespace SP

// @ 0x00441080
namespace SP {
void cSPEditorBlock_s0044_1080::F41080()
{
    Elem* it = begin48;
    Elem* end = end4cc;
    for (; it != end; it++) {
        F40e60(it->p);
    }
}
}  // namespace SP

// @ 0x00441440
bool SP::cSPEditorBlock_s0044_1440::BuildBlock(uint32_t instanceID, uint32_t groupID, IModelWorld_s0044_1440* pWorld, cSPEditorBlock_s0044_1440* pParent, float field30, bool bInteractive, bool bCreateModel, bool bModelFlag)
{
    bool result = true;
    IModelManager* modelMgr = ModelManager();

    field_30 = field30;
    mIsFullInit = (bInteractive && bCreateModel) ? true : false;
    field_230 = true;
    mInstanceID = instanceID;
    mGroupID = groupID;
    mIsVisible = true;

    if (mpHelper378) {
        mpHelper378->Shutdown();
        delete mpHelper378;
        mpHelper378 = 0;
    }
    if (bCreateModel)
        mpHelper378 = new ("Editor", 0, 0, 0, 0) cSPEditorBlockHelper378();

    if (pWorld) {
        mpModelWorld = pWorld;
    } else {
        if (mpModel) {
            mpModelWorld->SetExternalEffectsTransform(mpModel, 0, 0);
            mpModel->mpWorld->SetInWorld(mpModel, false);
        }
        if (mpEffectsMaskModel)
            mpEffectsMaskModel->mpWorld->SetInWorld(mpEffectsMaskModel, false);
    }

    if (!pParent) {
        if (mpClonedFrom)
            pParent = mpClonedFrom;
        else
            mIsFullInit = false;
    }

    if (mTransformedHull) {
        mpModelWorld->ReleaseTransformedHull(&mTransformedHull);
        mTransformedHull = 0;
    }

    ReleasePhysics();
    if (mpPropList)
        mpPropList = 0;

    if (!bCreateModel) {
        mpPropList = BlockPropertySource()->GetPropertyList(instanceID, groupID);
    } else {
        int flags = bModelFlag ? 0 : 4;
        mpModel = mpModelWorld->CreateModel(instanceID, groupID, flags | 2);
        if (mpModel) {
            mpModelWorld->StallUntilLoaded(mpModel);
            mpPropList = mpModel->mpPropList;
        }
    }

    if (!mpPropList)
        result = false;
    cPropertyList_s0044_1440* propList = mpPropList;

    if (propList->HasProperty(0x9069c7c8))  // modelUseSkin
        SetBooleanAttribute(kAttrUseSkin, *GetValueBool(propList->GetPropertyObject(0x9069c7c8)));
    if (propList->HasProperty(0xafff3a14))  // modelIsVertebra
        SetBooleanAttribute(kAttrIsVertebra, *GetValueBool(propList->GetPropertyObject(0xafff3a14)));

    if (mSymmetryType == -2)
        SetBaseJointScale(-2);

    int unused = 0;
    int blockType = GetBlockType(mInstanceID);
    if (blockType == -2)
        blockType = mSymmetryType;
    if (blockType != mSymmetryType && blockType != 0 && mSymmetryType != 0) {
        if (mSymmetryType == 1 && !mpPropList->HasProperty(0x0f48eb09))  // modelLeftFile
            blockType = mSymmetryType;
        else if (mSymmetryType == -1 && !mpPropList->HasProperty(0x18c1dbe0))  // modelRightFile
            blockType = mSymmetryType;
    }
    if (blockType != 0 && mSymmetryType != 0 && blockType != mSymmetryType &&
        Sub_44c5a0(mSymmetryType)) {
        field_1C4 = -1;
        field_1C8 = -1;
    } else {
        field_1C4 = 1;
        field_1C8 = 1;
    }
    SetBooleanAttribute(kAttr09, true);
    if (mSymmetryType == 0 || Abs(mPosition[0]) < 0.001f)
        SetBooleanAttribute(kAttrOnSymmetryPlane, true);

    if (propList->HasProperty(0x8ffc9e66))  // modelSymmetrySnapDelta
        mModelSymmetrySnapDelta = *GetValueFloat(propList->GetPropertyObject(0x8ffc9e66));
    mModelReplaceSnapDelta = 0.4f;
    if (propList->HasProperty(0x049218c6))  // modelReplaceSnapDelta
        mModelReplaceSnapDelta = *GetValueFloat(propList->GetPropertyObject(0x049218c6));
    mModelSymmetryRotationSnapAngle = 0.5f;
    GetFloatProperty(propList, 0x046b02c5, mModelSymmetryRotationSnapAngle);  // modelSymmetryRotationSnapAngle

    if (propList->HasProperty(0x0f48eb09))  // modelLeftFile
        SetBooleanAttribute(kAttrHasLeftFile, true);
    if (!TryGetUIntProperty(propList, 0xe305aafb, (uint32_t&)mBlockPack))  // blockPack
        mBlockPack = 0;

    if (propList->HasProperty(0x105f54ff))  // modelMinMuscleFile
        mModelMinMuscleFile = GetValueKey(propList->GetPropertyObject(0x105f54ff))->instanceID;
    if (propList->HasProperty(0xf061e767))  // modelMaxMuscleFile
        mModelMaxMuscleFile = GetValueKey(propList->GetPropertyObject(0xf061e767))->instanceID;

    const char* soundScale = "creature_size";
    GetPropertyAsChar8Ptr(propList, 0x02784061, soundScale);  // modelSoundScale
    mModelSoundScale = soundScale;
    const char* soundRotation = "creature_rotate";
    GetPropertyAsChar8Ptr(propList, 0x027c3d61, soundRotation);  // modelSoundRotation
    mModelSoundRotation = soundRotation;

    bool modelHasBallConnector = false;
    GetBoolProperty(propList, 0x4ff31eec, modelHasBallConnector);
    SetBooleanAttribute(kAttrHasBallConnector, modelHasBallConnector);
    bool modelHasSocketConnector = false;
    GetBoolProperty(propList, 0x6ff31f12, modelHasSocketConnector);
    SetBooleanAttribute(kAttrHasSocketConnector, modelHasSocketConnector);
    if (modelHasSocketConnector && modelHasBallConnector)
        SetBooleanAttribute(kAttrHasBallAndSocket, true);

    bool modelOrientToSurfaces = false;
    GetBoolProperty(propList, 0x2ff325cd, modelOrientToSurfaces);
    SetBooleanAttribute(kAttrOrientToSurfaces, modelOrientToSurfaces);
    bool modelStayAboveGround = false;
    GetBoolProperty(propList, 0xec611fc7, modelStayAboveGround);
    SetBooleanAttribute(kAttrStayAboveGround, modelStayAboveGround);
    bool modelRemainUpright = false;
    GetBoolProperty(propList, 0x0201636b, modelRemainUpright);
    SetBooleanAttribute(kAttrRemainUpright, modelRemainUpright);
    bool modelMoveBottomEdgeToSurface = false;
    GetBoolProperty(propList, 0x657a035c, modelMoveBottomEdgeToSurface);
    SetBooleanAttribute(kAttrMoveBottomEdgeToSurface, modelMoveBottomEdgeToSurface);
    bool modelPointForward = false;
    GetBoolProperty(propList, 0x31b7b15b, modelPointForward);
    SetBooleanAttribute(kAttrPointForward, modelPointForward);
    bool modelOrientWhenSnapped = false;
    GetBoolProperty(propList, 0xb0032aed, modelOrientWhenSnapped);
    SetBooleanAttribute(kAttrOrientWhenSnapped, modelOrientWhenSnapped);
    bool modelIsNullBlock = false;
    GetBoolProperty(propList, 0x02437197, modelIsNullBlock);
    SetBooleanAttribute(kAttrIsNullBlock, modelIsNullBlock);
    bool modelUseHullForBBox = false;
    GetBoolProperty(propList, 0x51365d07, modelUseHullForBBox);
    SetBooleanAttribute(kAttrUseHullForBBox, modelUseHullForBBox);
    bool modelUseDummyBlocks = false;
    GetBoolProperty(propList, 0x023fa66c, modelUseDummyBlocks);
    SetBooleanAttribute(kAttrUseDummyBlocks, modelUseDummyBlocks);
    bool modelHasRotationBallHandle = false;
    GetBoolProperty(propList, 0xb07b21bd, modelHasRotationBallHandle);
    SetBooleanAttribute(kAttrHasRotationBallHandle, modelHasRotationBallHandle);
    bool modelIsPlantRoot = false;
    GetBoolProperty(propList, 0x0d8800eb, modelIsPlantRoot);
    SetBooleanAttribute(kAttrIsPlantRoot, modelIsPlantRoot);
    bool modelHideDeformHandles = false;
    GetBoolProperty(propList, 0x9416cea1, modelHideDeformHandles);
    SetBooleanAttribute(kAttrHideDeformHandles, modelHideDeformHandles);
    bool modelHideRotationHandles = false;
    GetBoolProperty(propList, 0x0493691f, modelHideRotationHandles);
    SetBooleanAttribute(kAttrHideRotationHandles, modelHideRotationHandles);
    bool modelCellApplyBehaviorToUserRotation = false;
    GetBoolProperty(propList, 0x0655296a, modelCellApplyBehaviorToUserRotation);
    SetBooleanAttribute(kAttrCellApplyBehaviorToUserRotation, modelCellApplyBehaviorToUserRotation);

    // modelPinningType: instance = pinning mode, group = pinning type group.
    ResourceKey pinningType;
    pinningType.instanceID = 0;
    pinningType.typeID = 0;
    pinningType.groupID = 0;
    if (propList->HasProperty(0x2e853adb)) {  // modelPinningType
        GetPropertyAsKey(propList, 0x2e853adb, pinningType);
    } else {
        pinningType.groupID = 0xb6f87eb0;     // PinningGeometry
        pinningType.instanceID = 0x5ef161f1;  // PinningNormal
    }
    if (pinningType.groupID == 0x9183dc9b &&  // PinningPhysics
        !propList->HasProperty(0x00f9efc0))   // modelMeshHull
        pinningType.groupID = 0xb6f87eb0;     // PinningGeometry
    mModelPinningTypeGroup = pinningType.groupID;
    mModelPinningAntiAliased = pinningType.instanceID == 0x17cfd48f;  // PinningAntiAliased

    uint32_t pinningAgainstType = 0;
    if (propList->HasProperty(0x04e2bf28)) {  // modelForcePinningAgainstType
        GetPropertyAsKeyInstance(propList, 0x04e2bf28, pinningAgainstType);
        if (pinningAgainstType != 0x2ca33bdb) {  // None
            SetBooleanAttribute(kAttrForcePinningAgainstType, true);
            switch (pinningAgainstType) {
            case 0x9183dc9b:  // PinningPhysics
                mModelForcePinningType = 2;
                break;
            case 0xb6f87eb0:  // PinningGeometry
                mModelForcePinningType = 4;
                break;
            default:
                SetBooleanAttribute(kAttrForcePinningAgainstType, false);
                break;
            }
        }
    }

    mModelScale = 1.0f;
    GetFloatProperty(propList, 0x00fba611, mModelScale);  // modelScale
    mModelShowoffAnimation = 0;
    GetPropertyAsKeyInstance(propList, 0x4f2f2a48, mModelShowoffAnimation);  // modelShowoffAnimation
    mModelShowoffEffect = 0;
    GetPropertyAsKeyInstance(propList, 0x06514c0b, mModelShowoffEffect);  // modelShowoffEffect
    mOwnerLink.SetOwner(this);

    mModelRigBlockType.instanceID = 0;
    mModelRigBlockType.groupID = 0;
    mModelRigBlockType.typeID = 0;
    if (propList->HasProperty(0x0186609d)) {  // modelRigBlockType
        GetPropertyAsKey(propList, 0x0186609d, mModelRigBlockType);
        if (mModelRigBlockType.groupID == 0xffffffff || mModelRigBlockType.groupID == 0x2ca33bdb)
            mModelRigBlockType.groupID = 0;
        if (mModelRigBlockType.instanceID == 0xffffffff || mModelRigBlockType.instanceID == 0x2ca33bdb)
            mModelRigBlockType.instanceID = 0;
        if (mModelRigBlockType.typeID == 0xffffffff || mModelRigBlockType.typeID == 0x2ca33bdb)
            mModelRigBlockType.typeID = 0;
    }

    bool modelSnapToParentCenter = false;
    GetBoolProperty(propList, 0x0213a120, modelSnapToParentCenter);
    SetBooleanAttribute(kAttrSnapToParentCenter, modelSnapToParentCenter);
    bool modelSnapToParentSnapVectors = false;
    GetBoolProperty(propList, 0xf87abea3, modelSnapToParentSnapVectors);
    SetBooleanAttribute(kAttrSnapToParentSnapVectors, modelSnapToParentSnapVectors);
    bool modelSnapToCenterOfEditor = false;
    GetBoolProperty(propList, 0xdafbe434, modelSnapToCenterOfEditor);
    SetBooleanAttribute(kAttrSnapToCenterOfEditor, modelSnapToCenterOfEditor);
    bool modelCellAllowOnTopOfBody = false;
    GetBoolProperty(propList, 0xd11cbf2e, modelCellAllowOnTopOfBody);
    SetBooleanAttribute(kAttrCellAllowOnTopOfBody, modelCellAllowOnTopOfBody);
    bool modelPreferToBeOnPlaneOfSymmetry = false;
    GetBoolProperty(propList, 0x5c5e51ec, modelPreferToBeOnPlaneOfSymmetry);
    SetBooleanAttribute(kAttrPreferToBeOnPlaneOfSymmetry, modelPreferToBeOnPlaneOfSymmetry);
    bool modelActLikeFinOnPlaneOfSymmetry = false;
    GetBoolProperty(propList, 0xfb23b7d1, modelActLikeFinOnPlaneOfSymmetry);
    SetBooleanAttribute(kAttrActLikeFinOnPlaneOfSymmetry, modelActLikeFinOnPlaneOfSymmetry);
    bool modelStartAsymmetric = false;
    GetBoolProperty(propList, 0x0750dcd1, modelStartAsymmetric);
    SetBooleanAttribute(kAttrStartAsymmetric, modelStartAsymmetric);
    bool modelCanBeParentless = false;
    GetBoolProperty(propList, 0x8e31d974, modelCanBeParentless);
    SetBooleanAttribute(kAttrCanBeParentless, modelCanBeParentless);
    bool modelWarpCursorToPinPoint = false;
    GetBoolProperty(propList, 0x0489164a, modelWarpCursorToPinPoint);
    SetBooleanAttribute(kAttrWarpCursorToPinPoint, modelWarpCursorToPinPoint);
    bool modelActsLikeFoot = false;
    GetBoolProperty(propList, 0x04a33896, modelActsLikeFoot);
    SetBooleanAttribute(kAttrActsLikeFoot, modelActsLikeFoot);
    bool modelAllowAsymmetricalRotationOnPlaneOfSymmetry = false;
    GetBoolProperty(propList, 0x04eb8e7a, modelAllowAsymmetricalRotationOnPlaneOfSymmetry);
    SetBooleanAttribute(kAttrAllowAsymmetricalRotationOnPlaneOfSymmetry,
                        modelAllowAsymmetricalRotationOnPlaneOfSymmetry);
    bool modelDoNotFlipBasedOnSurfaceNormalOnPlaneOfSymmetry = false;
    GetBoolProperty(propList, 0x05c08c60, modelDoNotFlipBasedOnSurfaceNormalOnPlaneOfSymmetry);
    SetBooleanAttribute(kAttrDoNotFlipOnPlaneOfSymmetry,
                        modelDoNotFlipBasedOnSurfaceNormalOnPlaneOfSymmetry);

    mModelNumberOfSnapAxes = -1;
    TryGetUIntProperty(propList, 0x04ece315, (uint32_t&)mModelNumberOfSnapAxes);  // modelNumberOfSnapAxes

    bool modelRemainUprightOnTop = false;
    GetBoolProperty(propList, 0x04ed8506, modelRemainUprightOnTop);
    SetBooleanAttribute(kAttrRemainUprightOnTop, modelRemainUprightOnTop);
    bool modelAllowTopBehaviors = false;
    GetBoolProperty(propList, 0x05f98a72, modelAllowTopBehaviors);
    SetBooleanAttribute(kAttrAllowTopBehaviors, modelAllowTopBehaviors);
    bool modelIsAllowedOutOfBounds = false;
    GetBoolProperty(propList, 0x0538a895, modelIsAllowedOutOfBounds);
    SetBooleanAttribute(kAttrIsAllowedOutOfBounds, modelIsAllowedOutOfBounds);
    bool modelCircularTopAlignment = false;
    GetBoolProperty(propList, 0x04ed4c40, modelCircularTopAlignment);
    SetBooleanAttribute(kAttrCircularTopAlignment, modelCircularTopAlignment);
    bool modelActsLikeGrasper = false;
    GetBoolProperty(propList, 0x04a3386d, modelActsLikeGrasper);
    SetBooleanAttribute(kAttrActsLikeGrasper, modelActsLikeGrasper);

    mModelDefaultMouseOffset = kVector3Zero;
    GetPropertyAsVector3(propList, 0x0520f199, mModelDefaultMouseOffset);  // modelDefaultMouseOffset
    mModelEditorInitialRotation = kMatrix3Identity;
    if (propList->HasProperty(0x05aee941)) {  // modelEditorInitialRotation
        Vector3_s0044_1440 initialRotation;
        GetPropertyAsVector3(propList, 0x05aee941, initialRotation);
        float degToRad = 0.017453292f;
        initialRotation = initialRotation * degToRad;
        Matrix3_s0044_1440 rotation(Matrix33FromEulerXYZ(initialRotation));
        mModelEditorInitialRotation = rotation;
    }

    mModelBottomEdgeDistanceAdjustment = 0.0f;
    if (propList->HasProperty(0x165f0e1e))  // modelBottomEdgeDistanceAdjustment
        GetFloatProperty(propList, 0x165f0e1e, mModelBottomEdgeDistanceAdjustment);

    bool modelBoundsCheckOnlyForDelete = false;
    GetBoolProperty(propList, 0x3701d675, modelBoundsCheckOnlyForDelete);
    SetBooleanAttribute(kAttrBoundsCheckOnlyForDelete, modelBoundsCheckOnlyForDelete);

    mModelMinScale = 0.2f;
    GetFloatProperty(propList, 0xf023ed73, mModelMinScale);  // modelMinScale
    mModelMaxScale = 3.0f;
    GetFloatProperty(propList, 0xf023ed79, mModelMaxScale);  // modelMaxScale
    float defaultScale = GetDefaultScale();
    mModelMinBallConnectorScale = 0.5f;
    GetFloatProperty(propList, 0xfe0926f6, mModelMinBallConnectorScale);  // modelMinBallConnectorScale
    mModelMaxBallConnectorScale = 2.0f;
    GetFloatProperty(propList, 0x21d55d8c, mModelMaxBallConnectorScale);  // modelMaxBallConnectorScale

    if (propList->HasProperty(0x0224fea2)) {  // modelPaletteRotation
        Vector3_s0044_1440 paletteRotation = *GetValueVector3(propList->GetPropertyObject(0x0224fea2));
        mModelPaletteRotation = paletteRotation;
    }

    uint32_t modelPrice = 0;
    TryGetUIntProperty(propList, 0x02166464, modelPrice);  // modelPrice
    mModelPrice = modelPrice;
    mModelComplexityScore = 0;
    mModelRunTimeBoneCount = 0;
    mModelBakeLevel = 0;
    TryGetUIntProperty(propList, 0x3c652302, mModelComplexityScore);   // modelComplexityScore
    TryGetUIntProperty(propList, 0x51fa9dfa, mModelRunTimeBoneCount);  // modelRunTimeBoneCount
    TryGetUIntProperty(propList, 0x04460b63, mModelBakeLevel);         // modelBakeLevel
    field_5F4 = BlockPropertySource()->GetPropertyListFloat(propList);

    GetPropertyAsKeyInstance(propList, 0xdd94fb65, mFootType);    // foottype
    GetPropertyAsKeyInstance(propList, 0x0e40c402, mMouthType);   // mouthtype
    GetPropertyAsKeyInstance(propList, 0x2dc2a89d, mWeaponType);  // weapontype

    // ResourceKey lists
    mModelSnapDownTo.clear();
    {
        Property* prop = propList->GetPropertyObject(0x86e4091f);  // modelSnapDownTo
        int count = prop->GetItemCount();
        if (count > 0)
            SetBooleanAttribute(kAttrHasSnapDownTo, true);
        const ResourceKey* keys = (const ResourceKey*)prop->GetItems();
        CopyKeys(mModelSnapDownTo, count, keys);
    }
    mModelSnapToParentTypes.clear();
    if (propList->HasProperty(0xe3803d2a)) {  // modelSnapToParentTypes
        Property* prop = propList->GetPropertyObject(0xe3803d2a);
        int count = prop->GetItemCount();
        const ResourceKey* keys = (const ResourceKey*)prop->GetItems();
        CopyKeys(mModelSnapToParentTypes, count, keys);
    }
    mModelTypesToInteractWith.clear();
    if (propList->HasProperty(0x6ffded92)) {  // modelTypesToInteractWith
        Property* prop = propList->GetPropertyObject(0x6ffded92);
        int count = prop->GetItemCount();
        const ResourceKey* keys = (const ResourceKey*)prop->GetItems();
        CopyKeys(mModelTypesToInteractWith, count, keys);
    }
    mModelTypesNotToInteractWith.clear();
    if (propList->HasProperty(0x044dcd0a)) {  // modelTypesNotToInteractWith
        Property* prop = propList->GetPropertyObject(0x044dcd0a);
        int count = prop->GetItemCount();
        const ResourceKey* keys = (const ResourceKey*)prop->GetItems();
        CopyKeys(mModelTypesNotToInteractWith, count, keys);
    }
    mModelTypesToSnapReplace.clear();
    if (propList->HasProperty(0x048e2a2e)) {  // modelTypesToSnapReplace
        Property* prop = propList->GetPropertyObject(0x048e2a2e);
        int count = prop->GetItemCount();
        const ResourceKey* keys = (const ResourceKey*)prop->GetItems();
        CopyKeys(mModelTypesToSnapReplace, count, keys);
    }
    mModelAlignHeightWith.clear();
    if (propList->HasProperty(0xa3db17be)) {  // modelAlignHeightWith
        Property* prop = propList->GetPropertyObject(0xa3db17be);
        int count = prop->GetItemCount();
        if (count > 0)
            SetBooleanAttribute(kAttrHasAlignHeightWith, true);
        const ResourceKey* keys = (const ResourceKey*)prop->GetItems();
        CopyKeys(mModelAlignHeightWith, count, keys);
    }
    mModelAlignXYWith.clear();
    if (propList->HasProperty(0x05f57a28)) {  // modelAlignXYWith
        Property* prop = propList->GetPropertyObject(0x05f57a28);
        int count = prop->GetItemCount();
        if (count > 0)
            SetBooleanAttribute(kAttrHasAlignXYWith, true);
        const ResourceKey* keys = (const ResourceKey*)prop->GetItems();
        CopyKeys(mModelAlignXYWith, count, keys);
    }
    mModelAlignLateralWith.clear();
    if (propList->HasProperty(0x467ef4e0)) {  // modelAlignLateralWith
        Property* prop = propList->GetPropertyObject(0x467ef4e0);
        int count = prop->GetItemCount();
        if (count > 0)
            SetBooleanAttribute(kAttrHasAlignLateralWith, true);
        const ResourceKey* keys = (const ResourceKey*)prop->GetItems();
        CopyKeys(mModelAlignLateralWith, count, keys);
    }
    mModelStayAbove.clear();
    if (propList->HasProperty(0xee0fa2ce)) {  // modelStayAbove
        Property* prop = propList->GetPropertyObject(0xee0fa2ce);
        int count = prop->GetItemCount();
        if (count > 0)
            SetBooleanAttribute(kAttrStayAboveGround, true);
        const ResourceKey* keys = (const ResourceKey*)prop->GetItems();
        CopyKeys(mModelStayAbove, count, keys);
    }

    // Capabilities
    mCapabilities.clear();
    for (unsigned int i = 0; i < 0x5b; i++) {
        const CapabilityPropertyDesc* desc = &kCapabilityProperties[i];
        if (!propList->HasProperty(kCapabilityProperties[i].mPropertyID))
            continue;
        if (!desc->mIsVariableLevel) {
            Capability capability;
            capability.mPropertyID = kCapabilityProperties[i].mPropertyID;
            int level;  // left uninitialised when the property is missing or not an int
            GetIntProperty(propList, desc->mPropertyID, level);
            CapabilityLevel fixedLevel;
            fixedLevel.mIsVariableLevel = false;
            fixedLevel.mMinLevel = level;
            fixedLevel.mMaxLevel = level;
            fixedLevel.mDefaultLevel = -1;
            capability.mLevel = fixedLevel;
            mCapabilities.push_back(capability);
        } else {
            Capability capability;
            capability.mPropertyID = kCapabilityProperties[i].mPropertyID;
            Vector3_s0044_1440 range;
            GetPropertyAsVector3(propList, desc->mPropertyID, range);
            CapabilityLevel variableLevel;
            variableLevel.mIsVariableLevel = true;
            variableLevel.mDefaultLevel = (int)range.x;
            variableLevel.mMinLevel = (int)range.y;
            variableLevel.mMaxLevel = (int)range.z;
            capability.mLevel = variableLevel;
            mCapabilities.push_back(capability);
        }
    }

    Vector3_s0044_1440 rotationBallOffset(0.0f, -0.5f, 0.0f);
    if (propList->HasProperty(0xb07b21be)) {  // modelRotationBallHandleOffset
        Vector3_s0044_1440 offset = *GetValueVector3(propList->GetPropertyObject(0xb07b21be));
        rotationBallOffset = offset;
    }
    mModelRotationBallHandleOffset = rotationBallOffset;

    Vector3_s0044_1440 minSocketOffset(0.0f, 0.0f, 0.0f);
    Vector3_s0044_1440 maxSocketOffset(0.0f, 0.0f, 0.0f);
    mBooleanAttributes.test(kAttrHasSocketConnector);  // result unused
    if (propList->HasProperty(0x3061e2b3)) {  // modelMinSocketConnectorOffset
        Vector3_s0044_1440 offset = *GetValueVector3(propList->GetPropertyObject(0x3061e2b3));
        minSocketOffset = offset;
    }
    if (propList->HasProperty(0x3061e2b8)) {  // modelMaxSocketConnectorOffset
        Vector3_s0044_1440 offset = *GetValueVector3(propList->GetPropertyObject(0x3061e2b8));
        maxSocketOffset = offset;
    } else {
        maxSocketOffset = minSocketOffset;
    }
    mModelMinSocketConnectorOffset = minSocketOffset;
    mModelMaxSocketConnectorOffset = maxSocketOffset;

    if (mLimbType == 3)
        SetScaleType(0);

    // Ball connector
    if (GetBooleanAttribute(kAttrHasBallConnector)) {
        if (mpBallConnectorHandle) {
            mpBallConnectorHandle->Dispose();
            mpBallConnectorHandle = 0;
        }
        if (bInteractive) {
            mpBallConnectorHandle = new ("Editor", 0, 0, 0, 0) cSPEditorHandleBallConnector_s0044_1440();
            mpBallConnectorHandle->Init(this);
        }
        if (mpBallConnectorHandle)
            mpBallConnectorHandle->SetScale(mBaseMuscleScale);
    } else {
        mBooleanAttributes.set(kAttr0C, false);
    }

    // Socket connector
    if (GetBooleanAttribute(kAttrHasSocketConnector)) {
        if (mpSocketConnectorModel) {
            mpSocketConnectorModel->mpWorld->SetInWorld(mpSocketConnectorModel, false);
            mpSocketConnectorModel = 0;
        }
        mSocketConnectorOffset = mModelMinSocketConnectorOffset * mModelScale;
        mModelMinSocketConnectorOffset = mModelMinSocketConnectorOffset * mModelScale;
        mModelMaxSocketConnectorOffset = mModelMaxSocketConnectorOffset * mModelScale;
        if (bInteractive)
            mpSocketConnectorModel = mpModelWorld->CreateModel(0xcd09fa6a, kEditorModelGroupID, 0);  // ce_basic_socket
        if (mpSocketConnectorModel) {
            mpSocketConnectorModel->mpOwner = static_cast<IUnknown32*>(this);
            mpSocketConnectorModel->mGroupFlags.set(modelMgr->GetGroupFlag(0x4ff4af74, 0), true);
            mpSocketConnectorModel->SetVisible(false);
        }
    }

    if (GetBooleanAttribute(kAttrStayAboveGround) && mModelStayAbove.empty()) {
        mModelStayAbove.resize(1);
        mModelStayAbove[0].instanceID = 0x96b84350;  // ground
    }
    if (GetBooleanAttribute(kAttrUseDummyBlocks) && mpSocketConnectorModel)
        mpSocketConnectorModel->SetVisible(false);
    if (GetBooleanAttribute(kAttrHasBallAndSocket) && GetBooleanAttribute(kAttrUseSkin) && mpModel)
        mpModel->SetVisible(false);

    if (bInteractive && mpParent && !GetBooleanAttribute(kAttrIsVertebra) &&
        !GetBooleanAttribute(kAttrHasBallConnector)) {
        if (0.5f > VectorLength(mTriangleDirection))
            mTriangleDirection = Sub_4364a0();
    } else {
        mTriangleDirection = mTotalOrientation.m[1];
    }

    SetPosition(mPosition, false);
    field_3CC = mTotalOrientation.m[1];
    mEffectsBoneIndex = -1;
    mCSnapBoneIndex = -1;

    if (mpModel) {
        mpModel->mpOwner = static_cast<IUnknown32*>(this);
        mpModel->mTransform.SetOffset(mPosition);
        mpModel->mTransform.SetRotation(mTotalOrientation);
        mpModel->mGroupFlags.set(modelMgr->GetGroupFlag(0x9138fd8d, 0), true);
        mpModel->mFlags.set(1, false);

        bool modelOverrideBounds = false;
        GetBoolProperty(mpPropList, 0xd2435f2d, modelOverrideBounds);
        mpModel->mFlags.set(9, modelOverrideBounds);

        bool modelUseHullForPicking = false;
        GetBoolProperty(mpPropList, 0x350f8605, modelUseHullForPicking);
        if (modelUseHullForPicking) {
            SetBooleanAttribute(kAttrUseHullForPicking, true);
            mpModel->mFlags.set(8, true);
            mpModel->mCollisionMode = 2;
            mPickingType = 2;
        } else {
            mPickingType = 4;
        }

        if (GetBooleanAttribute(kAttrIsVertebra)) {
            mpModelWorld->StallUntilLoaded(mpModel);
            if (mpModelWorld && mpModelWorld->GetNumAnimations(mpModel, 0) == 1) {
                mpModelWorld->GetAnimationIDs(mpModel, &mVertebraAnimID, 0);
                if (mVertebraAnimID)
                    mpModelWorld->AnimAction(mpModel, mVertebraAnimID, 3, 0.0f, 0);
            }
            mpModel->mGroupFlags.set(modelMgr->GetGroupFlag(0x022fff11, 0), true);
            mpModel->mGroupFlags.set(modelMgr->GetGroupFlag(0x513cdfc1, 0), true);
            mpModel->mFlags.set(1, true);
            mpModel->mColor[3] = 0.0f;
        } else if (GetBooleanAttribute(kAttrHasBallAndSocket) && GetBooleanAttribute(kAttrUseSkin)) {
            mpModel->mFlags.set(1, true);
            mpModel->mColor[3] = 0.0f;
        }
        Sub_43ac40(0, 1, 1);
    }

    if (!mpPropList->HasProperty(0x8ffc9e66)) {  // modelSymmetrySnapDelta
        BoundingBox bbox = GetBBox(2, false, false);
        float delta = Clamp_s0044_1440((bbox.mMax[0] - bbox.mMin[0]) * 0.3f, 0.01f, 0.13f);
        mModelSymmetrySnapDelta = delta;
    }
    BoundingBox bbox = GetBBox(2, false, false);
    float replaceDelta = Clamp_s0044_1440((bbox.mMax[0] - bbox.mMin[0]) * mModelReplaceSnapDelta, 0.01f, 0.3f);
    field_224 = replaceDelta;

    // Rotation handles
    for (int i = 0; i < 3; i++) {
        if (mAxisHandles[i]) {
            mAxisHandles[i]->Dispose();
            mAxisHandles[i] = 0;
        }
    }
    bool createRotationHandles =
        (!GetBooleanAttribute(kAttrHideRotationHandles) && bInteractive) ? true : false;
    if (createRotationHandles) {
        CreateRotationRingHandle(0, 0x067489dc,  // xaxis
                                 0x04617bf6, 0x98d0ea44, 0x98d0ea45, 0x040cbd94, 0x041295c9,
                                 0x0420dc18, 0x04604b00, 0x04617d3d);
        CreateRotationRingHandle(1, 0x3bc16bcd,  // yaxis
                                 0x04617bf7, 0x98d0ea46, 0x98d0ea47, 0x040cbd95, 0x041295ca,
                                 0x0420dc19, 0x04604b01, 0x04617d3e);
        CreateRotationRingHandle(2, 0x01d369ee,  // zaxis
                                 0x04617bf8, 0x98d0ea48, 0x98d0ea49, 0x040cbd96, 0x041295cb,
                                 0x0420dc1a, 0x04604b02, 0x04617d3f);
    }
    if (createRotationHandles && GetBooleanAttribute(kAttrHasRotationBallHandle)) {
        if (mpRotationBallHandle) {
            mpRotationBallHandle->Dispose();
            mpRotationBallHandle = 0;
        }
        mpRotationBallHandle = new ("Editor", 0, 0, 0, 0) cSPEditorHandleRotationBall_s0044_1440();
        mpRotationBallHandle->Init(modelMgr, this, mModelRotationBallHandleOffset, bInteractive);
        bool modelRotationBallHandleIsHidden = false;
        GetBoolProperty(mpPropList, 0x04604b03, modelRotationBallHandleIsHidden);
        mpRotationBallHandle->mIsHidden = modelRotationBallHandleIsHidden;
    }

    if (pParent)
        Sub_451e20(pParent);

    // Deform handles
    bool showDeformHandles = !GetBooleanAttribute(kAttrHideDeformHandles);
    MorphHandleInfo morphHandles[0x20];
    int numWeights = mMorphHandleWeights.size();
    int numMorphHandles = 0;
    if (mpModel)
        numMorphHandles = mpModelWorld->GetDeformationHandles(mpModel, morphHandles, 0x20);

    if (numWeights >= 1 && GetBooleanAttribute(kAttrHasBallAndSocket)) {
        int boneLengthIndex = 0;
        int numChannels = mMorphHandleChannels.size();
        for (int i = 0; i < numChannels; i++) {
            if (mMorphHandleChannels[i] == 0x9310d4c0) {  // DeformBoneLength
                boneLengthIndex = i;
                break;
            }
        }
        float& weight = mMorphHandleWeights[boneLengthIndex];
        mSocketConnectorOffset = mModelMinSocketConnectorOffset +
            weight * (mModelMaxSocketConnectorOffset - mModelMinSocketConnectorOffset);
    }

    int i = 0;
    int numHandles = mMorphHandles.size();
    for (; i < numHandles; i++) {
        if (mMorphHandles[i])
            mMorphHandles[i]->Dispose();
    }
    mMorphHandles.clear();
    mMorphHandles.resize(numMorphHandles);
    for (int h = 0; h < numMorphHandles; h++) {
        mMorphHandles[h] = new ("Editor", 0, 0, 0, 0) cSPEditorHandleDeform_s0044_1440();
        cSPEditorHandleDeform_s0044_1440* handle = mMorphHandles[h];
        handle->Init(modelMgr, this, &morphHandles[h], bInteractive);
        cSPEditorHandleDeform_s0044_1440* created = mMorphHandles[h];
        SetMorphHandleWeight(h, created->mDefaultWeight, 0, 0, 1);
    }
    if (mMorphHandleWeights.empty())
        Sub_43e2b0();

    if (numMorphHandles > 0) {
        InitializeHandleData(propList);
        if (mpModelWorld && mpModel) {
            Sub_43e0f0(&mDeformAnimIndex);
            if (mDeformAnimIndex != -1) {
                uint32_t animIDs[0x20];
                mpModelWorld->GetAnimationIDs(mpModel, animIDs, 0);
                mDeformAnimID = animIDs[mDeformAnimIndex];
            }
        }
    }

    if (bInteractive) {
        Sub_448b80(0);
        BoundingBox modelBBox;
        Sub_449d40(&modelBBox);
        if (mpModel && mpModelWorld && mModelNumberOfSnapAxes > 0) {
            mpPropList->HasProperty(0x00f9efc0);  // modelMeshHull (result unused)
            RebuildPhysics();
            CalculateSnapAxes();
        }
        Sub_4484f0();
    }

    for (int w = 0; w < numMorphHandles; w++) {
        if (w < numWeights)
            SetMorphHandleWeight(w, mMorphHandleWeights[w], 0, 0, 1);
    }

    if (bInteractive && mpModel && mpModelWorld) {
        BoundingBox modelBBox2;
        Sub_449d40(&modelBBox2);
        RebuildPhysics();
        Sub_44b640(&mpModel->mDefaultBBox);
        Sub_44b6b0();
        Sub_4485d0();
    }

    field_1A9 = true;
    field_1AC = 0;

    int snapIndex = -2;
    if (bInteractive) {
        Vector3_s0044_1440 snapA;
        Vector3_s0044_1440 snapB;
        bool flag = Sub_492de0(this);
        float score = Sub_492e70(this, &snapA, &snapB, &snapIndex, 1.0f, flag);
        if (score > -1.0f)
            Sub_44e7c0(snapIndex);
    }

    // "effect" and "csnap" bones
    if (mpModel) {
        int numBones = mpModelWorld->GetNumBones(mpModel);
        fixed_vector_s0044_1440<uint32_t, 64> boneIDs(numBones);
        fixed_vector_s0044_1440<BoneTransform_s0044_1440, 64> boneTransforms(numBones);
        const uint32_t kEffectBone = 0x80d91e9e;  // effect
        const uint32_t kCSnapBone = 0x2002c980;   // csnap
        mpModelWorld->GetBoneIDs(mpModel, boneIDs.mpBegin);
        for (int bone = 0; bone < numBones; bone++) {
            if (boneIDs[bone] == 0x80d91e9e || boneIDs[bone] == 0x2002c980) {
                Transform_s0044_1440 worldTransform;
                Transform_s0044_1440 poseTransform;
                fixed_vector_s0044_1440<BoneTransform_s0044_1440, 64> transforms(numBones);
                mpModelWorld->GetBoneTransforms(mpModel, transforms.mpBegin);
                BoneTransformToTransform(&transforms[bone], &worldTransform);
                mpModelWorld->GetPoseTransforms(mpModel, transforms.mpBegin, false);
                BoneTransformToTransform(&transforms[bone], &poseTransform);
                worldTransform.Accumulate(poseTransform);
                worldTransform.AccumulateScaled(*mpModelWorld->GetMeshTransform(mpModel));
                worldTransform.mScale = 1.0f;
                worldTransform.mChangeCount++;
                if (boneIDs[bone] == 0x80d91e9e) {
                    SetBooleanAttribute(kAttrHasEffectBone, true);
                    mEffectsBoneTransform1 = poseTransform;
                    mEffectsBoneTransform2 = worldTransform;
                    mEffectsBoneIndex = bone;
                } else if (boneIDs[bone] == 0x2002c980) {
                    SetBooleanAttribute(kAttrHasCSnapBone, true);
                    mCSnapBoneTransform1 = poseTransform;
                    mCSnapBoneTransform2 = worldTransform;
                    mCSnapBoneIndex = bone;
                }
            }
        }
    }

    return result;
}

// @ 0x00446ff0
int* __fastcall Sub_446ff0(int* p)
{
    if ((*(unsigned short*)((char*)p + 0x10) & 0x30) != 0) {
        return (int*)*p;
    } else {
        if (*(unsigned short*)((char*)p + 0x12) != 0)
            return p;
    }
    return 0;
}

// @ 0x00447030
void Binder::Method(unsigned char param2)
{
    Elem_s0044_6ff0 scratch[0x20];
    int n = 0x20;
    Elem_s0044_6ff0* p = scratch;
    while (n = n - 1, -1 < n) {
        p->mTransform.Init();
        p = (Elem_s0044_6ff0*)((char*)p + 0x5c);
    }
    void* obj = mWorld;
    int count = ((int(__thiscall*)(void*, int, void*, int))(
        *(void**)(*(char**)obj + 0xe8)))(obj, mArg, scratch, 0x20);
    for (int i = 0; i < count; i++)
        mTargets[i]->Apply(&scratch[i], param2);
}

// @ 0x00447150
namespace SP {
void cSPEditorBlock_s0044_7150::InitializeHandleData(cPropertyList_s0044_7150* propList)
{
    fixed_vector_s0044_7150<cSPEditorHandleDeform_s0044_7150*, 8> handles;
    ScratchSlots_s0044_7150<2>();

    mModelSignModifier = GetModelSignModifier();

    mModelSignModifierHandle = FindDeformHandleIndex(kModelSignModifierHandleID);
    if (mModelSignModifierHandle != -1)
        mDeformationHandles[mModelSignModifierHandle]->mDoNotPlaceHandle = true;
    mLimbTypeHandle = FindDeformHandleIndex(kLimbTypeHandleID);
    if (mLimbTypeHandle != -1)
        mDeformationHandles[mLimbTypeHandle]->mDoNotPlaceHandle = true;
    mMuscleScaleHandle = FindDeformHandleIndex(kMuscleScaleHandleID);
    if (mMuscleScaleHandle != -1)
        mDeformationHandles[mMuscleScaleHandle]->mDoNotPlaceHandle = true;

    int nNumHandles = mDeformationHandles.size();

    if (propList->HasProperty(0x8ecb344a)) {  // modelHandleKeys
        Property_s0044_7150* prop = propList->GetPropertyObject(0x8ecb344a);
        int cnt = prop->GetItemCount();
        ResourceKey* keyArray = (ResourceKey*)prop->GetItems();
        ScratchSlots_s0044_7150<3>();
        handles.resize(cnt);
        for (int i = 0; i < cnt; i++) {
            uint32_t id = keyArray[i].instanceID;
            handles[i] = 0;
            for (int j = 0; j < nNumHandles; j++) {
                if (mDeformationHandles[j]->mHandleID == id)
                    handles[i] = mDeformationHandles[j];
            }
        }
    }

    if (propList->HasProperty(0x3644a2c5)) {  // modelHandleStretchSounds
        Property_s0044_7150* prop = propList->GetPropertyObject(0x3644a2c5);
        if (prop->mnType == 0x12) {
            int cnt = prop->GetItemCount();
            string8* sounds = (string8*)prop->GetItems();
            for (int i = 0; i < cnt; i++) {
                if (i < handles.size() && handles[i] != 0)
                    handles[i]->mSoundString = sounds[i];
            }
        }
    }

    if (propList->HasProperty(0x04604b04)) {  // modelHandleIsHidden
        int cnt = 0;
        bool* hidden;
        GetArrayBool(mPropList, 0x04604b04, cnt, hidden);
        for (int i = 0; i < cnt; i++) {
            if (i < handles.size() && handles[i] != 0)
                handles[i]->mIsHiddenHandle = hidden[i];
        }
    }

    if (propList->HasProperty(0x87fe8a14)) {  // modelHandleLinkedHandlesTemplate
        Property_s0044_7150* prop = propList->GetPropertyObject(0x87fe8a14);
        int cnt = prop->GetItemCount();
        ResourceKey* keyArray = (ResourceKey*)prop->GetItems();
        for (int i = 0; i < cnt; i++) {
            uint32_t idA = keyArray[i].groupID;
            uint32_t idB = keyArray[i].instanceID;
            cSPEditorHandleDeform_s0044_7150* handleA = 0;
            cSPEditorHandleDeform_s0044_7150* handleB = 0;
            for (int j = 0; j < nNumHandles; j++) {
                if (mDeformationHandles[j]->mHandleID == idA)
                    handleA = mDeformationHandles[j];
                if (mDeformationHandles[j]->mHandleID == idB)
                    handleB = mDeformationHandles[j];
            }
            if (handleB != 0 && handleA != 0) {
                handleA->mSymmetricHandle = handleB;
                handleB->mSymmetricHandle = handleA;
            }
        }
    }

    if (propList->HasProperty(0x45101f3e)) {  // modelHandleLinkedHandles
        Property_s0044_7150* prop = propList->GetPropertyObject(0x45101f3e);
        int cnt = prop->GetItemCount();
        ResourceKey* keyArray = (ResourceKey*)prop->GetItems();
        for (int i = 0; i < cnt; i++) {
            uint32_t idA = keyArray[i].groupID;
            uint32_t idB = keyArray[i].instanceID;
            cSPEditorHandleDeform_s0044_7150* handleA = 0;
            cSPEditorHandleDeform_s0044_7150* handleB = 0;
            bool bClear = idB == 0x2ca33bdb;  // "None"
            for (int j = 0; j < nNumHandles; j++) {
                if (mDeformationHandles[j]->mHandleID == idA)
                    handleA = mDeformationHandles[j];
                if (!bClear && mDeformationHandles[j]->mHandleID == idB)
                    handleB = mDeformationHandles[j];
            }
            if (handleB != 0 && handleA != 0) {
                handleA->mSymmetricHandle = handleB;
                handleB->mSymmetricHandle = handleA;
            } else if (bClear && handleA != 0) {
                if (handleA->mSymmetricHandle != 0)
                    handleA->mSymmetricHandle->mSymmetricHandle = 0;
                handleA->mSymmetricHandle = 0;
            }
        }
    }

    if (propList->HasProperty(0x3b58c554)) {  // modelHandlePlacementTypesTemplate
        Property_s0044_7150* prop = propList->GetPropertyObject(0x3b58c554);
        int cnt = prop->GetItemCount();
        ResourceKey* keyArray = (ResourceKey*)prop->GetItems();
        for (int i = 0; i < cnt; i++) {
            uint32_t placementType = keyArray[i].instanceID;
            uint32_t id = keyArray[i].groupID;
            for (int j = 0; j < nNumHandles; j++) {
                if (mDeformationHandles[j]->mHandleID == id) {
                    mDeformationHandles[j]->mPinningType = placementType;
                    if (placementType == 0x9e6e561c)  // IgnoreAxis
                        mDeformationHandles[j]->mAxisToIgnore = keyArray[i].typeID;
                }
            }
        }
    }

    if (propList->HasProperty(0x23fc767e)) {  // modelHandlePlacementTypes
        Property_s0044_7150* prop = propList->GetPropertyObject(0x23fc767e);
        int cnt = prop->GetItemCount();
        ResourceKey* keyArray = (ResourceKey*)prop->GetItems();
        for (int i = 0; i < cnt; i++) {
            uint32_t placementType = keyArray[i].instanceID;
            uint32_t id = keyArray[i].groupID;
            for (int j = 0; j < nNumHandles; j++) {
                if (mDeformationHandles[j]->mHandleID == id) {
                    mDeformationHandles[j]->mPinningType = placementType;
                    if (placementType == 0x9e6e561c)  // IgnoreAxis
                        mDeformationHandles[j]->mAxisToIgnore = keyArray[i].typeID;
                }
            }
        }
    }

    if (propList->HasProperty(0xb75fd502)) {  // modelAnimationSoundLinks
        Property_s0044_7150* prop = propList->GetPropertyObject(0xb75fd502);
        int cnt = prop->GetItemCount();
        ResourceKey* keyArray = (ResourceKey*)prop->GetItems();
        ScratchSlots_s0044_7150<8>();
        mAnimationSoundMap.Reserve(cnt);
        for (int i = 0; i < cnt; i++) {
            uint32_t sound = keyArray[i].instanceID;
            uint32_t anim = keyArray[i].groupID;
            mAnimationSoundMap[anim] = sound;
        }
    }

    if (propList->HasProperty(0x41f72519)) {  // modelSoundParameters
        Property_s0044_7150* prop = propList->GetPropertyObject(0x41f72519);
        int cnt = prop->GetItemCount();
        ResourceKey* keyArray = (ResourceKey*)prop->GetItems();
        for (int i = 0; i < cnt; i++) {
            uint32_t group = keyArray[i].groupID;
            uint32_t handleId = keyArray[i].typeID;
            uint32_t parameterID = keyArray[i].instanceID;
            cSPEditorHandleDeform_s0044_7150* foundHandle = 0;
            for (int j = 0; j < nNumHandles; j++) {
                if (mDeformationHandles[j]->mHandleID == handleId)
                    foundHandle = mDeformationHandles[j];
            }
            pair<uint32_t, cSPEditorHandleDeform_s0044_7150*> entry;
            entry.first = parameterID;
            entry.second = foundHandle;
            ScratchSlots_s0044_7150<63>();
            mSoundParameterMap[group].push_back(entry);
        }
    }
}
}  // namespace SP

// @ 0x004484f0
bool Blk_s0044_8380::A84f0()
{
    bool result = true;
    if ((mBits & 0x800) == 0) {
        for (int i = 0; i < (int)(mItemsEnd - mItems); i++) {
            bool r = A8480(i, 1);
            result = (result && r);
        }
    }
    return result;
}

// @ 0x004485d0
void Blk_s0044_8380::A85d0()
{
    if ((mBits & 0x800) == 0) {
        for (int i = 0; i < (int)(mItemsEnd - mItems); i++)
            mItems[i]->Method();
    }
}

// @ 0x00449ed0
void Blk_s0044_9ed0::A49ed0()
{
    if (mEditorModel) {
        float dt = (mEditorModel->GetScale() != 0.0f) ? mEditorModel->GetScale() * 0.5f : 1.0f;
        int n = mDeformHandles.size();
        for (int i = 0; i < n; ++i) {
            HandleStub* h = mDeformHandles[i];
            if (h)
                h->Update(dt);
        }
        if (mBallHandle)
            mBallHandle->Update(dt * 0.16666f);
        for (int j = 0; j < 3; ++j) {
            HandleStub* h = (HandleStub*)mArr[j];
            if (h)
                h->Update(dt * 0.5f);
        }
    }
}

// @ 0x0044a070
void Blk_s0044_9ed0::A4a070()
{
    if (mIsFullInit && mModel.get() && mModelWorld.get()) {
        BBox box;
        box.Reset();
        ScratchSlots_s0044_9ed0<12>();
        Sub449d40(&box);
        RebuildPhysics();
        Sub44b640(&box);
        Sub44b6b0();
    }
}

// @ 0x0044ae00
BBox_s0044_ae00 Blk_s0044_ae00::GetBBox(int type, bool a, bool b)
{
    BBox_s0044_ae00 box;
    if (a && GetFlag(10) && (GetFlag(11) || GetFlag(7))) {
        if (GetFlag(11)) {
            float h0 = FUN_0043eed0();
            float h1 = FUN_0043f3f0();
            float avg = (h0 + h1) * 0.5f;
            float depth = (float)fabs(m40c[1]);
            float e = avg * 0.06f;
            box.mn.x = -e;
            box.mn.y = -depth;
            box.mn.z = -e;
            box.mx.x = e;
            box.mx.y = 0.0f;
            box.mx.z = e;
        } else {
            box.mn.x = -0.19f;
            box.mn.y = -0.07f;
            box.mn.z = -0.35f;
            box.mx.x = 0.19f;
            box.mx.y = 0.07f;
            box.mx.z = 0.03f;
        }
    } else if (mModel && mWorld) {
        if (GetFlag(21)) {
            mWorld->Vfne4(mModel, &box);
        } else {
            BBox_s0044_ae00* r = mWorld->GetBounds(mModel);
            box.mx = r->mx;
            box.mn = r->mn;
        }
    } else {
        Sizer* s = GetSizer();
        int cnt = m704.size();
        float* beg = m704.mpBegin;
        s->Vfn54(mInstance, mGroup, beg, cnt, &box.mn, &box.mx);
    }
    if (box.IsInverted() || box.IsInfinite())
        box.SetCenterRadius(&g_defaultCenter, 0.01f);
    switch (type) {
    case 0: {
        Xf xf;
        xf.SetPosition(mPosition);
        xf.SetOrientation(mOrient);
        xf.SetScale(mScaleY);
        box.Transform(&xf);
        break;
    }
    case 1:
        box.Scale(mScaleY);
        break;
    }
    float scale = (type == 2) ? 1.0f : mScaleY;
    if (b) {
        int n = mChildren.size();
        int i;
        for (i = 0; i < n; i++)
            box.Merge(mChildren[i]->GetBBox(type, a, b));
    }
    return box;
}

// @ 0x0044b550
V3_s0044_ae00* Blk_s0044_ae00::B550(V3_s0044_ae00* out)
{
    *out = mVec;
    return out;
}

// @ 0x0044b590
M3_s0044_ae00* Blk_s0044_ae00::B590(M3_s0044_ae00* out)
{
    *out = mMat;
    return out;
}

// @ 0x0044b5c0
float Blk_s0044_ae00::GetDefaultScale()
{
    if (mPropList) {
        float r = 1.0f;
        PropList* pl = mPropList.p;
        if (pl) {
            Prop* p;
            if (pl->GetProp(0x536c50c, &p) && p->type == 0xd)
                r = *p->GetFloat();
        }
        return r;
    }
    return 1.0f;
}

// @ 0x0044b640
void Blk_s0044_ae00::B640(int)
{
    BBox_s0044_ae00 box = GetBBox(2, false, false);
    for (int i = 0; i < 3; i++) {
        if (mRing[2 + i]) {
            mRing[2 + i]->SetBoundingBox(&box);
        }
    }
}

// @ 0x0044b6b0
void Blk_s0044_ae00::B6b0()
{
    if (m2c) {
        for (int i = 0; i < 3; i++) {
            if (mRing[2 + i]) {
                mRing[2 + i]->F5650();
                mRing[2 + i]->Vfn14();
                if (mRing[2 + i]->IsFlagSet()) {
                    mRing[2 + i]->F5550();
                }
            }
        }
    }
}

// @ 0x0044b780
bool Blk_s0044_ae00::B780()
{
    if (m604 != 0)
        return true;
    if (m434 != 0)
        return true;
    return false;
}

// @ 0x0044b7b0
void Blk_s0044_ae00::B7b0(unsigned ms)
{
    if (mFade.IsPlaying()) {
        float dt = (float)ms * 0.001f;
        mFade.Update(dt);
    }
    if (FUN_0044c030() || m230) {
        m230 = false;
        if (m1a8 && m188 != 0)
            RebuildPhysics();
        if (m1a9) {
            if (m1ac > 5) {
                m1a9 = false;
            } else if (mSocket) {
                if (!mSocket->GetFlag(10)) {
                    if (Place(GetOffsetA(1), GetOffsetB(1))) {
                        m1a9 = false;
                    } else {
                        m1ac = m1ac + 1;
                        if (m1ac == 5)
                            m3a0 = FUN_004364a0();
                    }
                } else {
                    m1a9 = false;
                }
            }
        }
        if (GetFlag(39) && mModel) {
            mWorld->Vfnd4(mModel, &m284, 0);
        }
    }
}

// @ 0x0044ba20
void Blk_s0044_ae00::Ba20(bool a, bool b)
{
    int n;
    int i;
    if (mModel) {
        if (FUN_0044c030()) {
            SetBooleanAttribute(9, true);
            Obj* o = mModel.p;
            o->flags.set(0, false);
            if (m3ec)
                m3ec->Vfn30(1, 0);
            if (m3f0 && !GetFlag(5)) {
                Obj* o2 = m3f0.p;
                o2->flags.set(0, false);
            }
            m34 = false;
        }
        n = mChildren.size();
        for (i = 0; i < n; i++) {
            if (!FUN_004a7e60(this) && mChildren[i]->IsSymmetryLocked()) {
                mChildren[i]->Ba20(a, true);
            } else if (b) {
                mChildren[i]->Ba20(a, b);
            }
        }
        if (a && m3e0)
            m3e0->Ba20(false, false);
    }
}

// @ 0x0044bcf0
void Blk_s0044_bcf0::Abcf0()
{
}

// @ 0x0044c050
int Blk_s0044_bcf0::C050()
{
    float f = mVec[0];
    float r;
    if (f < -g_eps) {
        r = -1.0f;
    } else {
        r = (f > g_eps) ? 1.0f : 0.0f;
    }
    int n = (int)r;
    return n;
}

// @ 0x0044c0e0
void Blk_s0044_bcf0::C0e0()
{
}

// @ 0x0044c270
void Blk_s0044_bcf0::C270()
{
}

// @ 0x0044c450
int Blk_s0044_bcf0::C450()
{
    return 0;
}

// @ 0x0044c480
void Blk_s0044_bcf0::C480(int v)
{
    m1c4 = v;
    if (Child() != 0)
        Child()->m1c4 = v;
}

// @ 0x0044c4d0
void Blk_s0044_bcf0::C4d0(int)
{
}

// @ 0x0044c5a0
void Blk_s0044_bcf0::C5a0(int)
{
}

// @ 0x0044d570
void Blk_s0044_d4f0::D570()
{
    BBox_s0044_d4f0 box;
    GetBBox(&box, 1, 0, 0);
    for (int i = 0, size = mVec.size(); i < size; i++) {
        if (mVec.mBeg[i].m18 && mVec.mBeg[i].m18->a) {
            if (mVec.at(i).m18->GetB()) {
                Vec3_s0044_d4f0 last;
                Vec3_s0044_d4f0 u;
                Mat3 v18;
                Vec3_s0044_d4f0 v10;
                Vec3_s0044_d4f0 t8;
                mVec.at(i).m18->Compute(&last, &v18);
                v10 = last - GetXf()->pos;
                v10 = v10 * Transposed(GetXf()->rot);
                Corner(&t8, 1);
                u = (t8 - GetXf()->pos) * Transposed(GetXf()->rot);
                v10[2] = 0.0f;
                if (mVec.mBeg[i].m1c) {
                    if (Abs_s0044_d4f0(v10[0]) > 0.5f)
                        v10[1] = u[1];
                    else if (Abs_s0044_d4f0(v10[1]) > 0.5f)
                        v10[0] = u[0];
                }
                *(Raw3*)&mVec.mBeg[i].mx = *(Raw3*)&v10;
            }
        }
    }
}

// @ 0x0044f130
void cSPEditorBlock::SetScaleType(int type)
{
    if (GetFlag(0xb)) {
        if (GetFlag(0xa)) {
            mScaleType = type;
            SetFlag(9, 1);
        } else {
            mScaleType = 2;
        }
    } else {
        mScaleType = 3;
    }
}

// @ 0x0044f240
int cSPEditorBlock::CalculateSymmetrySign()
{
    FUN_0044a7e60(this);
    if (GetFlag(7))
        return 0;
    char flag = 0;
    if (mpSocketConnector != 0) {
        flag = mpSocketConnector->GetFlag(7) ? 1 : 0;
        if (!flag) {
            flag = mpSocketConnector->GetFlag(0) ? 0 : 1;
        }
    }
    int a = FUN_0044c050();
    int b = FUN_0044c450();
    int result = a;
    if (result == 0) {
        result = b;
        if (result == 0) {
            char pb = 0;
            cPropertyList* p = mpPropList;
            if (p != 0) {
                void* prop = 0;
                if (p->GetProperty(0x7bd0ca3e, &prop)) {
                    if (*(unsigned short*)((char*)prop + 0x12) == 1)
                        pb = *(char*)PropertyGetBool(prop);
                }
            }
            if (pb)
                result = -1;
        }
    }
    (void)flag;
    (void)*(void**)((char*)this + 0x33c);
    return result;
}

// @ 0x0044f420
cSPEditorBlock_s0044_f420* cSPEditorBlock_s0044_f420::Split(int type)
{
    char nameA[8];
    char nameB[8];
    nameA[0] = 0;
    nameB[0] = 0;

    AutoRefBlockVec vA;
    vA.Ctor(nameA);
    vA.Func();
    AutoRefBlockVec vB;
    vB.Ctor(nameB);
    vB.Func();

    cSPEditorBlock_s0044_f420* nb = BuildBlock(type, this, vA, vB);
    if (nb != 0) {
        nb->FUN_0043f230(this);
        if (type == 2 || type == 3) {
            FUN_00448e90((char*)this + 0x48, 0);
            FUN_00449420((char*)this + 0xa8, 0);
            nb->CalculateSymmetrySign();
            if (mModel != 0) {
                cSPEditorBlock_s0044_f420* sc = mSocket;
                if (sc != 0) {
                    cSPEditorBlock_s0044_f420* linked = sc->mLinked;
                    if (linked != 0 && ((ModelObj_s0044_f420*)mModel)->FUN_004adc40()) {
                        sc->mLinked->FUN_004388b0(nb);
                    } else {
                        if (mSocket->FUN_004a7e60(mSocket))
                            mSocket->FUN_004388b0(nb);
                        else
                            mSocket->FUN_004388b0(nb);
                    }
                }
            }
            bool f = GetFlag(0xc);
            nb->SetFlag(0xc, f ? 1 : 0);
            if (type == 3) {
                Vec3f_s0044_f420 a;
                Vec3f_s0044_f420 b;
                this->TrackerGetOffsetA(a.v, 1);
                a.v[0] = a.v[0] * g_negOne;
                this->TrackerGetOffsetB(b.v, 1);
                b.v[0] = b.v[0] * g_negOne;
                nb->TrackerPlace(b, a);
            } else {
                Vec3f_s0044_f420 b;
                Vec3f_s0044_f420 a;
                this->TrackerGetOffsetB(b.v, 1);
                this->TrackerGetOffsetA(a.v, 1);
                nb->TrackerPlace(a, b);
            }
        }
    }
    vB.Dtor();
    vA.Dtor();
    return nb;
}

// @ 0x0044f7c0
cSPEditorBlock_s0044_f7c0* cSPEditorBlock_s0044_f7c0::CloneBlock(int type, cSPEditorBlock_s0044_f7c0* root, BlockRefVector& originals, BlockRefVector& copies)
{
    if (type == 0 || type == 1) {
        cSPEditorBlock_s0044_f7c0* block = new("Editor", 0, 0, 0, 0) cSPEditorBlock_s0044_f7c0();

        block->SetBooleanAttribute(0xb, mBooleanAttributes.test(0xb));
        block->SetBooleanAttribute(0xa, mBooleanAttributes.test(0xa));
        if (mBooleanAttributes.test(0x39) && !mpAsymmetricRigblock.get()) {
            SetAsymmetricBlock(block);
            block->SetAsymmetricBlock(this);
        }
        block->SetBooleanAttribute(0x39, mBooleanAttributes.test(0x39));
        block->SetBooleanAttribute(0x3a, mBooleanAttributes.test(0x3a));

        if (type == 1) {
            block->SetUserOrientation(MirrorMatrix(mUserOrientation, 0));
            block->SetOrientation(MirrorMatrix(mOrientation, 0), 0);
            block->SetPosition(MirrorVector(mPosition), 0);
        } else {
            block->SetUserOrientation(mUserOrientation);
            block->SetOrientation(mOrientation, 0);
            block->SetPosition(mPosition, 0);
        }
        block->SetBaseJointScale(-2);

        if (type == 1 && mBooleanAttributes.test(0xd)) {
            int sign = GetSymmetrySign() * -1;
            block->SetBaseJointScale(sign);
            const ResourceKey& key = GetMirroredKey(sign, 0);
            block->BuildBlock(key.instanceID, key.groupID, mpModelWorld.get(), field_188,
                              field_30, 1, 1, 1);
        } else {
            block->BuildBlock(mInstanceID, mGroupID, mpModelWorld.get(), field_188,
                              field_30, 1, 1, 1);
        }
        block->mIsClone = 1;

        block->SetBooleanAttribute(0x33, mBooleanAttributes.test(0x33));
        block->SetBooleanAttribute(0x23, mBooleanAttributes.test(0x23));
        block->mIsVisible = mIsVisible;
        block->SetPosition(mPosition, 0);
        block->mTriangleDirection = mTriangleDirection;
        block->mTrianglePickOrigin = mTrianglePickOrigin;
        if (type == 1) {
            block->mTriangleDirection[0] *= kNegOne;
            block->mTrianglePickOrigin[0] *= kNegOne;
        }
        block->field_1C4 = field_1C4;
        block->field_1C8 = field_1C8;

        block->mpPinningInfo->mNormal = mpPinningInfo->mNormal;
        block->mpPinningInfo->mOrientation = mpPinningInfo->mOrientation;
        block->mpPinningInfo->mOffset = mpPinningInfo->mOffset;
        if (type == 0) {
            block->mpPinningInfo->mIndex = mpPinningInfo->mIndex;
            block->mpPinningInfo->mFlag = mpPinningInfo->mFlag;
        } else {
            block->mpPinningInfo->mIndex = -1;
            block->mpPinningInfo->mFlag = 0;
        }
        block->mpPinningInfo->mTarget = 0;

        if (!mBooleanAttributes.test(3) || IsBlockMirrorable(this)) {
            block->SetModelScaleA(mScale2, 1);
            block->SetModelScaleB(mScale, 0);
            block->SetBaseMuscleScale(mBaseMuscleScale);
        }
        block->Sub_447030(1);
        block->SetMuscleScale(mMuscleScale);

        block->SetBooleanAttribute(0, mBooleanAttributes.test(0));
        block->SetBooleanAttribute(5, mBooleanAttributes.test(5));
        block->SetBooleanAttribute(0xf, mBooleanAttributes.test(0xf));
        block->SetBooleanAttribute(0x14, mBooleanAttributes.test(0x14));
        block->SetBooleanAttribute(0x15, mBooleanAttributes.test(0x15));
        block->SetBooleanAttribute(0xc, mBooleanAttributes.test(0xc));
        block->SetScaleType(GetLimbType());
        block->SetBooleanAttribute(1, mBooleanAttributes.test(1));
        if (mBooleanAttributes.test(0xd)) {
            block->SetBooleanAttribute(0xd, 1);
            block->SetBooleanAttribute(0xe, !mBooleanAttributes.test(0xe));
        }

        int numHandles = block->mMorphHandles.size();
        if (numHandles == mMorphHandles.size()) {
            for (int i = 0; i < numHandles; ++i)
                block->SetMorphHandleDelta(i, mMorphHandles[i]->mDelta, 0, 0, 1);
        }
        for (int j = 0; j < numHandles; ++j)
            block->mMorphHandles[j]->Update();

        block->UpdateAfterClone();
        block->RebuildPhysics();
        block->SetBooleanAttribute(9, 1);
        block->CopyPaintFrom(this);
        return block;
    } else if (mpEditorModel) {
        cSPEditorBlock_s0044_f7c0* result = 0;
        if (type == 3) {
            result = CloneBlock(1, root, originals, copies);
            mpEditorModel->AddBlock(result, 1);
            result->SetSymmetricBlock(this);
            result->SetAsymmetricBlock(this);
        } else {
            result = CloneBlock(0, root, originals, copies);
            mpEditorModel->AddBlock(result, 1);
        }
        originals.push_back(AutoRefCount_s0044_f7c0<cSPEditorBlock_s0044_f7c0>(this));
        copies.push_back(AutoRefCount_s0044_f7c0<cSPEditorBlock_s0044_f7c0>(result));

        BlockRefVector children((allocator_tag()));
        children = mChildren;
        if (root->mpSymmetricRigblock.get() && mpSymmetricRigblock.get()) {
            cSPEditorBlock_s0044_f7c0* symmetric = mpSymmetricRigblock.get();
            BlockRefVector symChildren((allocator_tag()));
            symChildren = symmetric->mChildren;
            for (size_t i = 0, n = symChildren.size(); i < n; ++i) {
                if (symChildren[i]->IsSymmetricChildCandidate())
                    children.push_back(symChildren[i]);
            }
        }

        int numChildren = children.size();
        for (int i = 0; i < numChildren; ++i) {
            cSPEditorBlock_s0044_f7c0* copy = children[i]->CloneBlock(type, root, originals, copies);
            originals.push_back(children[i]);
            copies.push_back(AutoRefCount_s0044_f7c0<cSPEditorBlock_s0044_f7c0>(copy));
            result->AddChild(copy);
            copy->SetBooleanAttribute(0xc, children[i]->mBooleanAttributes.test(0xc));
            children[i]->SetPosition(children[i]->mPosition, 1);
            children[i]->SetUserOrientation(children[i]->mUserOrientation);
            children[i]->SetOrientation(children[i]->mOrientation, 1);
            copy->SetBaseJointScale(-2);
            if (copy->GetB() == -1) {
                if (type == 3) {
                    Vector3_s0044_f7c0 offsetA = children[i]->GetOffsetA(1);
                    offsetA[0] *= kNegOne;
                    Vector3_s0044_f7c0 offsetB = children[i]->GetOffsetB(1);
                    offsetB[0] *= kNegOne;
                    copy->Place(offsetA, offsetB);
                } else {
                    copy->Place(copy->GetOffsetA(1), copy->GetOffsetB(1));
                }
            } else {
                copy->mpPinningInfo->Attach(result, copy->mpPinningInfo->mIndex,
                                            copy->mpPinningInfo->mFlag);
            }
        }

        int numOriginals = originals.size();
        int numCopies = copies.size();
        for (int k = 0; k < numOriginals; ++k) {
            cSPEditorBlock_s0044_f7c0* original = originals[k];
            cSPEditorBlock_s0044_f7c0* clone = copies[k];
            if (!clone->mpSymmetricRigblock.get() && original->mpSymmetricRigblock.get()) {
                int found = -1;
                for (int m = 0; m < numOriginals; ++m) {
                    if (originals[m].get() == original->mpSymmetricRigblock.get()) {
                        found = m;
                        break;
                    }
                }
                if (found != -1)
                    clone->SetSymmetricBlock(copies[found]);
            }
            if (!clone->mpAsymmetricRigblock.get() && original->mpAsymmetricRigblock.get()) {
                int found = -1;
                for (int m = 0; m < numOriginals; ++m) {
                    if (originals[m].get() == original->mpAsymmetricRigblock.get()) {
                        found = m;
                        break;
                    }
                }
                if (found != -1)
                    clone->SetAsymmetricBlock(copies[found]);
            }
        }
        result->FinishClone();
        return result;
    }
    return 0;
}

// @ 0x00450f70
unsigned char Block2::Rebuild(int a, int b, float c, char d, unsigned char e)
{
    bool f12 = GetFlag(0xc);
    bool f39 = GetFlag(0x39);
    mFlags[0] = 0;
    mFlags[1] = 0;
    if (f12) SetBit(0xc); else ClearBit(0xc);
    if (f39) SetBit(0x39); else ClearBit(0x39);
    unsigned char r = BuildBlock(mInstance, mGroup, a, b, c, d, e, 1);
    FUN_00440520(mField1d8, 0, 1);
    mField1dc = mField1d8;
    if (d != 0)
        FUN_00449ed0();
    FUN_00448e90((char*)this + 0x48, 0);
    FUN_00449420((char*)this + 0xa8, 0);
    return r;
}

// @ 0x004511f0
int Block2::GetA()
{
    int result = (int)mTracker->field4;
    return result;
}

// @ 0x00451210
int Block2::GetB()
{
    if (mTracker != 0) {
        return mTracker->field44;
    } else {
        return -1;
    }
}

// @ 0x00451240
void Block2::SetF(void* a, unsigned char b)
{
    void* tmp = mPtr33c;
    mTracker->Call(tmp, (int)a, b);
}

// @ 0x00451280
void Block2::SetRef(RCObj* p)
{
    RCObj** slot = &mTracker->field4;
    RCObj* old;
    if (p != *slot) {
        old = *slot;
        if (p != 0) p->AddRef();
        *slot = p;
        if (old != 0) old->Release();
    }
}

// @ 0x004512e0
Vec3_s0045_0f70* Block2::GetVec14(Vec3_s0045_0f70* out)
{
    Vec3_s0045_0f70* p = &mTracker->vec14;
    out->x = p->x;
    out->y = p->y;
    out->z = p->z;
    return out;
}

// @ 0x00451330
// The original leaves eax = &mVec194: it materialises the address once
// (mov eax,[ebp-4]; add eax,0x194), stores all three words through it and never
// overwrites eax again, so the setter returns the vector (its result is unused by
// the callers).  The integer stores keep the compiler from using SSE moves.
Vec3_s0045_0f70* Block2::SetVec194(int x, int y, int z)
{
    Vec3_s0045_0f70* p = &mVec194;
    *(int*)&p->x = x;
    *(int*)&p->y = y;
    *(int*)&p->z = z;
    mFlag1a0 = true;
    return p;
}

// @ 0x00451360
void Block2::ResetVec194()
{
    mVec194 = mVec48;
    mFlag1a0 = false;
}

// @ 0x004513a0
Vec3_s0045_0f70* Block2::GetVec194(Vec3_s0045_0f70* out)
{
    Vec3_s0045_0f70* p = &mVec194;
    out->x = p->x;
    out->y = p->y;
    out->z = p->z;
    return out;
}

// @ 0x00451400
namespace SP {
void cSPEditorBlock_s0045_0f70::Shutdown2()
{
    if (mTransformedHull) {
        mpModelWorld->ReleaseTransformedHull(&mTransformedHull);
        mTransformedHull = 0;
    }
    Sub_451ed0();
    if (mOwnerLink.IsPlaying())
        mOwnerLink.Stop();
    mOwnerLink.ReleaseHandle();
    mBooleanAttributes.set(1, true);
    void* pEditorModel = mpEditorModel;
    mpEditorModel = 0;

    mpPropList = 0;
    if (mpModel) {
        mpModelWorld->SetExternalEffectsTransform(mpModel, 0, 0);
        mpModel->RemoveFromWorld();
        mpModel = 0;
    }
    if (mpEffectsMaskModel) {
        mpEffectsMaskModel->RemoveFromWorld();
        mpEffectsMaskModel = 0;
    }
    mpModelWorld = 0;

    while (!mChildren.empty()) {
        if (mChildren[0]->mpHelper378) {
            mChildren[0]->mpHelper378->mField0 = 0;
            mChildren[0]->mpHelper378->mpObject = 0;
        }
        mChildren[0]->SetBooleanAttribute(0xc, false);
        RemoveChild(mChildren[0]);
    }
    if (HasParent())
        mpParent->RemoveChild(this);

    if (mpBallConnectorHandle) {
        mpBallConnectorHandle->Dispose();
        mpBallConnectorHandle = 0;
    }
    if (mpSocketConnectorModel) {
        mpSocketConnectorModel->mpOwner = 0;
        mpSocketConnectorModel->RemoveFromWorld();
        ScratchSlots_s0045_0f70<2>();
        mpSocketConnectorModel = 0;
    }

    int n = mMorphHandles.size();
    for (int i = 0; i < n; i++) {
        if (mMorphHandles[i])
            mMorphHandles[i]->Dispose();
    }
    ScratchSlots_s0045_0f70<3>();
    mMorphHandles.clear();

    if (mpRotationBallHandle) {
        mpRotationBallHandle->Shutdown();
        mpRotationBallHandle = 0;
    }
    for (int j = 0; j < 3; j++) {
        if (mAxisHandles[j]) {
            mAxisHandles[j]->Dispose();
            mAxisHandles[j] = 0;
        }
    }
    if (mpHelper378) {
        mpHelper378->Shutdown();
        delete mpHelper378;
    }
    if (mpSymmetricBlock && mIsSymmetric) {
        mpSymmetricBlock->Sub_453500(true);
        Sub_453500(false);
    }
    Sub_438df0(0);
    Sub_438cc0(0);
}
}  // namespace SP

// @ 0x00451e20
void Block2::SetPtr188(void* p)
{
    mPtr188 = p;
    FUN_00452040();
}

// @ 0x00451e50
void Block2::SetSub38(void* p)
{
    if (mSub18c != 0) {
        SubInner* q = &mSub18c->inner;
        q->field = p;
    }
}

// @ 0x00451e90
void* Block2::GetSub38()
{
    if (mSub18c != 0) {
        SubInner* q = &mSub18c->inner;
        void* result = q->field;
        return result;
    } else {
        return 0;
    }
}

// @ 0x00451ed0
void Block2::Reset188()
{
    FUN_00451fe0();
    mPtr188 = 0;
}

// @ 0x00451ef0
void cSPEditorBlock_s0045_1ef0::FUN_00451ef0(void* obj)
{
    FUN_00451fe0();
    int n = 6;
    (void)n;
    if (mPhysObj != 0)
        FUN_00451fe0();
    mPhysObj = (HkWorldObject*)obj;
    if (mPhysObj != 0) {
        mWorld->addEntity(mPhysObj, 1);
        mWorld->FUN_01084fa0(mPhysObj, 0, 1);
        Vec3_s0045_1ef0 v = mVec48;
        FUN_00448fa0(v, 1);
        Matrix33 tmp = mMatA8;
        FUN_0044a0e0();
        (void)tmp;
        mFlag1a8 = false;
    }
}

// @ 0x00451fe0
void cSPEditorBlock_s0045_1ef0::FUN_00451fe0()
{
    if (mPhysObj != 0) {
        HkEntity* e = *(HkEntity**)((char*)mPhysObj + 8);
        char c;
        e->FUN_01083110(&c, mPhysObj);
        mPhysObj->removeReference();
    }
    mPhysObj = 0;
}

// @ 0x00452040
void cSPEditorBlock_s0045_1ef0::FUN_00452040()
{
    mFlag1a8 = true;
    if (mWorld != 0)
        FUN_00451ef0(BuildNewPhysicsShape());
}
