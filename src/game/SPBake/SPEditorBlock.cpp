// src/game/SPBake/SPEditorBlock.cpp -- migrated from slice(s) s00451ef0, s00450f70, s0044f7c0, s0044f420, s0044e460, s0044d4f0, s0044bcf0, s0044ae00, s00449ed0, s00448380, s00446ff0, s00441080, s00440110, s0043f3a0, s0043e3f0, s0043d690, s0043cad0, s0043bbc0, s0043ac40, s0043a460, s00438440 by tools/migrate/rewrite.py
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
struct cContentValidationSummarizer;
}
namespace SP {
struct LinkRec {
    void*  field0;                       // +0x00
    cContentValidationSummarizer* field4;// +0x04
    char   pad8[0x3C];
    int32_t field44;                     // +0x44
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
struct cContentValidationSummarizer {
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
struct KeyVec { void* begin; void* end; };
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
    void F3cfc0(uint8_t a, int b);                        // 0043CFC0
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
template<int N> struct bitset {
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
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void SetState(int a, int b);   // vtbl +0x30
};
}
namespace SP {
struct Node_s0043_cad0 { bool Check(); float F3adb80(); float F3adbc0(); };
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
// ---- items of slice s0043cad0 end

// ---- items of slice s0043d690 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
    virtual int AddRef(); virtual int Release();
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual void v3c(); virtual void v40(); virtual void v44();
    virtual void v48(); virtual void v4c(); virtual void v50(); virtual void v54();
    virtual void v58(); virtual void v5c(); virtual void v60(); virtual void v64();
    virtual void v68(); virtual void v6c(); virtual void v70();
    virtual void MoveToTime(cMWModel_s0043_d690* model, uint32_t animID, float time, int animationGroup);   // 0x74
    virtual void v78(); virtual void v7c();
    virtual void GetAnimationRange(cMWModel_s0043_d690* model, uint32_t animID, float* start, float* end, int animationGroup);  // 0x80
    virtual int GetNumBones(cMWModel_s0043_d690* model);                              // 0x84
    virtual void v88();
    virtual int GetBoneTransforms(cMWModel_s0043_d690* model, BoneTransform* dst);    // 0x8c
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4(); virtual void vb8(); virtual void vbc();
    virtual void vc0(); virtual void vc4(); virtual void vc8(); virtual void vcc();
    virtual void vd0(); virtual void vd4(); virtual void vd8(); virtual void vdc();
    virtual void ve0(); virtual void ve4(); virtual void ve8(); virtual void vec();
    virtual void vf0(); virtual void vf4(); virtual void vf8(); virtual void vfc();
    virtual void v100(); virtual void v104();
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
    virtual void v08(); virtual void v0c(); virtual void v10();
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
struct Matrix3_s0043_f3a0 { float m[9]; Matrix3_s0043_f3a0() {} Matrix3_s0043_f3a0(const Matrix3_s0043_f3a0&); };
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
    void  F3eef0(Vec3* out);                   // 0043EEF0
    void* F3f290(Vec3* out, int flag);         // 0043F290
    void  F404f0();                            // 004404F0
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
void  Sub_4A8E10(Matrix3_s0043_f3a0* out, const void* a, int b);
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
    void A85d0();
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
struct M3_s0044_bcf0 { float m[9]; M3_s0044_bcf0& operator=(const M3_s0044_bcf0&); };
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
    int C050();
    void C0e0();
    void C270();
    int C450();
    void C480(int v);
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
inline float Abs(float f) { return fabsf(f); }
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
extern bool FUN_004adc40(void* p);
extern char FUN_004a7e60(void* p);
extern const float g_negOne;   // 0x013eb1bc = -1.0f
struct AutoRefBlockVec { unsigned int w[15]; };   // 0x3c-byte local
struct cSPEditorBlock_s0044_f420;
extern void VecCtor(AutoRefBlockVec* v, const char* name);   // 0x00540470
extern void VecFunc(AutoRefBlockVec* v);                     // 0x00453770
extern void VecDtor(AutoRefBlockVec* v);                     // 0x00453eb0
extern void FUN_0043f230(cSPEditorBlock_s0044_f420* block, cSPEditorBlock_s0044_f420* self);
extern void FUN_004388b0(void* p, cSPEditorBlock_s0044_f420* block);
extern void TrackerGetOffsetA(cSPEditorBlock_s0044_f420* self, float* out, int one);  // 0x00438120
extern void TrackerGetOffsetB(cSPEditorBlock_s0044_f420* self, float* out, int one);  // 0x004381e0
extern void TrackerPlace(cSPEditorBlock_s0044_f420* self, float* a, float* b);        // 0x00437b00
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
    cSPEditorBlock_s0044_f420* BuildBlock(int type, AutoRefBlockVec& a, AutoRefBlockVec& b); // 0x0044f7c0
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
struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
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
    void   SetVec194(int x, int y, int z);// 0x00451330
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
class IUnknown32 {
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
    AutoRefCount_s0045_0f70<IUnknown32> mpOwner;     // +0x64

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
class cSPEditorBlockHelper378 {
public:
    uint32_t mField0;
    AutoRefCount_s0045_0f70<IUnknown32> mpObject;
    uint32_t mData[(0x4c - 8) / 4];

    void Shutdown();               // 0x004ae250
};
}
namespace SP {
struct cSPEditorBlockOwnerLink {
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
class RefCountVTemplate {
public:
    virtual int AddRef();
    virtual int Release();
    int mnRefCount;
};
}
namespace SP {
class cSPEditorBlock_s0045_0f70 : public RefCountVTemplate, public IUnknown32 {
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
    cSPEditorBlockHelper378* mpHelper378;            // +0x378
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
    cSPEditorBlockOwnerLink mOwnerLink;              // +0xdd0

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
struct Matrix33 { float m[9]; };
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
                cContentValidationSummarizer* old = e->linkRec->field4;
                e->linkRec->field4 = 0;
                old->Release();
            }
            e->linkRec->field44 = -1;
        }
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
        if (!ModelKey_HasResourceType(&keys)) {
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
        F3cfc0(b, 0);
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
    Vec3 base;
    F3eef0(&base);
    if (flag > 0) {
        Vec3* p = (Vec3*)F3f290(&base, 0);
        if (0.0f > a + p->x) {
            Vec3* q = (Vec3*)F3f290(&base, 0);
            a = -q->x;
        }
    } else {
        Vec3* p = (Vec3*)F3f290(&base, 1);
        if (a + p->x >= 0.0f) {
            Vec3* q = (Vec3*)F3f290(&base, 1);
            a = -q->x;
        }
    }
    out->x = a;
    out->y = b;
    out->z = c;
}
}  // namespace SP














// @ 0x0043ffa0
namespace SP {
void cSPEditorBlock_s0043_f3a0::FFa0(Matrix3_s0043_f3a0 m)
{
    Matrix3_s0043_f3a0 tmp;
    Matrix3_Assign(&tmp, &m);
    F404f0();
    if (node != 0 && node->Check() && link3e0 != 0) {
        Matrix3_s0043_f3a0 tmp2;
        Sub_4A8E10(&tmp2, &m, 0);
        link3e0->F404f0();
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
    if (v < lo) v = lo;
    if (v > hi) v = hi;
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
    if (mModel != 0) {
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







// @ 0x0044c480
void Blk_s0044_bcf0::C480(int v)
{
    m1c4 = v;
    if (Child() != 0)
        Child()->m1c4 = v;
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
                    if (Abs(v10[0]) > 0.5f)
                        v10[1] = u[1];
                    else if (Abs(v10[1]) > 0.5f)
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
        cSPEditorBlock* s = mpSocketConnector;
        flag = (((*(unsigned int*)&s->mBaseJointScale) & 0x80000000u) != 0) ? 1 : 0;
        if (!flag) {
            cSPEditorBlock* s2 = mpSocketConnector;
            flag = (((*(unsigned int*)&s2->mBaseJointScale) & 1u) == 0) ? 1 : 0;
        }
    }
    int a = FUN_0044c050();
    int b = FUN_0044c450();
    int result = a;
    if (a == 0 && b == 0) {
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
    VecCtor(&vA, nameA);
    VecFunc(&vA);
    AutoRefBlockVec vB;
    VecCtor(&vB, nameB);
    VecFunc(&vB);

    cSPEditorBlock_s0044_f420* nb = BuildBlock(type, vA, vB);
    if (nb != 0) {
        FUN_0043f230(nb, this);
        if (type == 2 || type == 3) {
            FUN_00448e90((char*)this + 0x48, 0);
            FUN_00449420((char*)this + 0xa8, 0);
            nb->CalculateSymmetrySign();
            if (mModel != 0) {
                cSPEditorBlock_s0044_f420* sc = mSocket;
                if (sc != 0) {
                    cSPEditorBlock_s0044_f420* linked = sc->mLinked;
                    if (linked != 0 && FUN_004adc40(mModel)) {
                        FUN_004388b0(sc->mLinked, nb);
                    } else {
                        if (FUN_004a7e60(mSocket))
                            FUN_004388b0(mSocket, nb);
                        else
                            FUN_004388b0(mSocket, nb);
                    }
                }
            }
            bool f = GetFlag(0xc);
            nb->SetFlag(0xc, f ? 1 : 0);
            if (type == 3) {
                float a[3];
                float b[3];
                TrackerGetOffsetA(this, a, 1);
                a[0] = a[0] * g_negOne;
                TrackerGetOffsetB(this, b, 1);
                b[0] = b[0] * g_negOne;
                TrackerPlace(nb, b, a);
            } else {
                float b[3];
                float a[3];
                TrackerGetOffsetB(this, b, 1);
                TrackerGetOffsetA(this, a, 1);
                TrackerPlace(nb, a, b);
            }
        }
    }
    VecDtor(&vB);
    VecDtor(&vA);
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
void Block2::SetVec194(int x, int y, int z)
{
    *(int*)&mVec194.x = x;
    *(int*)&mVec194.y = y;
    *(int*)&mVec194.z = z;
    mFlag1a0 = true;
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
