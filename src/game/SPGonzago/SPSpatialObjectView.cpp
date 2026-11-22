// src/game/SPGonzago/SPSpatialObjectView.cpp -- migrated from slice(s) s00c8aa60, s00c87be0, s00e92ca0, s00e91ce0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPSpatialObjectView.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

// addresses retail relocates here, named so the build relocates them too
extern "C" char g_1455648[];
extern "C" char g_1486c00[];

#include "game/types.h"
#include "SP/cRotationRing.h"
#include "SP/cSpatialObject.h"

// unnamed retail callees and globals (address in the comment)
extern float g_defaultColorR;   // 0x15a89c0
extern float g_defaultColorG;   // 0x15a89c4
extern float g_defaultColorB;   // 0x15a89c8
#include <math.h>
#include <float.h>
#include <string.h>
#include "SP/cGonzagoTimer.h"
#include "SP/cViewer.h"
#include "SP/cCommunity.h"
#include "SP/cGameData.h"
#include "SP/cISerializableObject.h"
#include "SP/cVarListSerializer.h"
#include "EA/Text/Font.h"
#include "SP/cSolarSystem.h"
#include "SP/cStar.h"
#include "EA/ResourceMan/Key.h"

// ---- items of slice s00e91ce0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct V3 { float x, y, z; };
struct Key { uint32_t mInstance, mType, mGroup; };
uint32_t __cdecl FNVHash(const char* s, uint32_t seed, int lowercase);   // 0x00932e80
static inline uint32_t id(const char* s) { return FNVHash(s, 0x811c9dc5, 1); }
void* __cdecl operator_new_sp(unsigned int size, const char* pName,
                              int a, int b, int c, int d);               // 0x00f473a0
void* __cdecl GonzagoModelWorld();                                       // 0x00b3d520
struct cSim_s00b4_8110 { void Fn_00b48770(void* obj, bool b); };       // 0x00b48770
cSim_s00b4_8110* FUN_00b3d310();                                         // 0x00b3d310
void* FUN_00ae66d0(void* p);                                             // 0x00ae66d0
void* FUN_00efe5a0();                                                    // 0x00efe5a0
extern float g_defaultColorR;   // 0x15a89c0
extern float g_defaultColorG;   // 0x15a89c4
extern float g_defaultColorB;   // 0x15a89c8
struct cSpatialObject {
    char pad_00[0x50];
    uint32_t mFlags50;                       // +0x50
    char pad_54[0x70 - 0x54];
    Key mModelKey;                           // +0x70
    char pad_7c[0xc0 - 0x7c];

    void* GetDataRaw(uint32_t id);           // vtable +0xb8
};
class cSpatialObjectView {
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
    virtual void* v28(void*);                // +0x28
    virtual void* GetModel();                // +0x2c
    virtual void* GetTransform();            // +0x30
    virtual float GetScale();                // +0x34
    virtual void  SetRotation(void*);        // +0x38
    virtual void  SetModelMatrix(void*);     // +0x3c
virtual void  v40();
virtual void  v44(void*);
    virtual void  v48(int, int, int);
virtual void  v4c();
virtual void  v50();
virtual void  v54();
virtual void  v58();
virtual void  v5c();
virtual void  v60();
    virtual void  v64(void*, float);
virtual void  v68();
virtual void  v6c();
virtual void  v70();
    virtual void  v74();
    virtual void* v78(void*);                // +0x78

    cSpatialObjectView();                    // 0x00e92af0
    ~cSpatialObjectView();                   // 0x00e92660

    uint32_t mField04;                       // +0x04
    uint32_t mField08;                       // +0x08
    cSpatialObject* mpObject;                // +0x0c
    void*    mpObjectCombatant;              // +0x10
    uint8_t  mField14;                       // +0x14
    char     pad_15[3];
    V3       mColor;                         // +0x18
    uint32_t mField24;                       // +0x24
    uint32_t mField28;                       // +0x28
    uint32_t mField2c;                       // +0x2c
    uint8_t  mbField30;                      // +0x30
    uint8_t  mbField31;                      // +0x31
    uint8_t  mbField32;                      // +0x32

    void  SetIsInWorld(bool b);              // 0x00e92620
    uint8_t GetIsInWorld();                  // 0x00e92c60
    uint8_t GetIsVisible();                  // 0x00e92c80
    void  SetModel_926d0(void* model);       // 0x00e926d0
    void  MakeView_740(void* a, void* b, void* c, void* d);  // 0x00e92740
    void  Init(void* gamedata);              // 0x00e92910
    void* SetModel();                        // 0x00e929b0
    void* GetData();                         // 0x00e929f0
    void  UpdateFadeState();                 // 0x00e92a10
};
#define VF(o, off)  (*(void**)(*(char**)(o) + (off)))
#define VC0(R, o, off)               ((R (__thiscall*)(void*))VF(o, off))((void*)(o))
#define VC1(R, o, off, T1, a1)       ((R (__thiscall*)(void*, T1))VF(o, off))((void*)(o), (a1))
#define VC2(R, o, off, T1, a1, T2, a2) \
    ((R (__thiscall*)(void*, T1, T2))VF(o, off))((void*)(o), (a1), (a2))
// ---- items of slice s00e91ce0 end

// ---- items of slice s00e92ca0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" char g_1486c54[];
#define VS(o, off)              (*(void**)(*(char**)(o) + (off)))
#define VC0_s00e9_2ca0(R, o, off)          ((R (__thiscall*)(void*))VS(o, off))((void*)(o))
#define VC1_s00e9_2ca0(R, o, off, T1, a1)  ((R (__thiscall*)(void*, T1))VS(o, off))((void*)(o), (a1))
#define VC2_s00e9_2ca0(R, o, off, T1, a1, T2, a2) \
    ((R (__thiscall*)(void*, T1, T2))VS(o, off))((void*)(o), (a1), (a2))
#define VC4(R, o, off, T1, a1, T2, a2, T3, a3, T4, a4) \
    ((R (__thiscall*)(void*, T1, T2, T3, T4))VS(o, off))((void*)(o), (a1), (a2), (a3), (a4))
#define FU32(p, off)  (*(uint32_t*)((char*)(p) + (off)))
class Key_s00e9_2ca0 {                                  // EA::ResourceMan::Key  (0xc)
public:
    uint32_t mInstance;                      // +0x0
    uint32_t mType;                          // +0x4
    uint32_t mGroup;                         // +0x8
};
struct Vec3 { float x, y, z; };
struct Matrix33 { float m[9]; };
struct XformMsg_s00e9_2ca0 {
    uint16_t mFlags;                         // +0x00  bit 2 translation, bit 1 rotation
    uint16_t mModCount;                      // +0x02
    Vec3     mTranslation;                   // +0x04
    float    mScale;                         // +0x10
    Matrix33 mRotation;                      // +0x14
    XformMsg_s00e9_2ca0();                              // 0x00434040
    void SetPosition(const Vec3* p);         // 0x00571d40
};
struct cIVisualEffect {
    virtual int  AddRef();
    virtual int  Release();
    virtual void Start(int);
    virtual void Stop(int);
    virtual bool IsRunning();
    virtual void SetTransform(XformMsg_s00e9_2ca0*);
    virtual void Move(XformMsg_s00e9_2ca0*);
    virtual void Method20(XformMsg_s00e9_2ca0*);
    virtual bool Method24(int, void*);
    virtual void Method2c();
    virtual int  Method58();
    virtual int  Method5c();
    virtual int  Method60();
    virtual int  Method64(void*);
    virtual void* Method68(void*, int);
    virtual void Method6c(void*, int, int);
    virtual void Method70(void*, void*, int, float, int);
    virtual void Method74();
    virtual void Method7c(void*, float);
};
struct XformMsg {
    uint16_t mFlags;                         // +0x00  bit 2 translation, bit 1 rotation
    uint16_t mModCount;                      // +0x02
    Vec3     mTranslation;                   // +0x04
    float    mScale;                         // +0x10
    Matrix33 mRotation;                      // +0x14
    XformMsg();                              // 0x00434040
    void SetPosition(const Vec3* p);         // 0x00571d40
};
struct EffectInfo {
    int32_t mId;                             // +0x00
    int32_t mOwner;                          // +0x04
    uint8_t mFlag8;                          // +0x08
    char    pad_09[3];
    float   mF0c;                            // +0x0c
    uint8_t mFlag10;                         // +0x10
    char    pad_11[3];
    float   mF14;                            // +0x14
    float   mF18;                            // +0x18
    int32_t mI1c, mI20, mI24;
    uint8_t mFlag28;                         // +0x28
    char    pad_29[0x38 - 0x29];
    cIVisualEffect* mpEffect;                // +0x38
};
struct cSpatialObject_s00e9_2ca0 {
    char pad_00[0x38];
    uint32_t mFlags;                         // +0x38
    uint32_t mMaterialType;                  // +0x3c
    char pad_40[0x50 - 0x40];
    uint8_t mIsSelected;                     // +0x50
    uint8_t mIsRolledOver;                   // +0x51
    uint8_t mIsInvalid;                      // +0x52
    uint8_t mbPickable;                      // +0x53
    char pad_54[0x5c - 0x54];
    uint8_t mbKeepPinnedToPlanet;            // +0x5c
    char pad_5d[0x70 - 0x5d];
    Key_s00e9_2ca0 mModelKey;                           // +0x70
    char pad_7c[0xc0 - 0x7c];
    EffectInfo* mEffectsBegin;               // +0xc0
    EffectInfo* mEffectsEnd;                 // +0xc4

    // effect-list helpers (retail methods on cSpatialObject).
    void* FindEffectRaw(uint32_t id);        // 0x00c888e0
    bool  GetEffect(uint32_t id);            // 0x00c88910
    void  KillEffect(uint32_t id, int flag); // 0x00c8ad30
    void  CreateEffect2(uint32_t id, int a, int b); // 0x00c8b130
    void* CreateEffect3(uint32_t a, uint32_t b, uint32_t c); // 0x00c8b060
    void  sub_b1a0(int id);                  // 0x00c8b1a0
    void  sub_b210(int id);                  // 0x00c8b210
    void  c88550_f(float dt);                // 0x00c88550
    void  c8aa60_f();                        // 0x00c8aa60
    bool  c888c0_f();                        // 0x00c888c0
    void  c89d60_f(void* msg);               // 0x00c89d60
};
struct cGonzagoTimer {
    void*    mField00;                       // +0x00 (vptr)
    uint32_t mRefCount;                      // +0x04
    uint64_t mElapsedTime;                   // +0x08
    uint64_t mBaseTime;                      // +0x10
    uint8_t  mRunning;                       // +0x18
    char     pad_19[3];
    void*    mGetTime;                       // +0x1c
    cGonzagoTimer();
    ~cGonzagoTimer() throw();
    void Restart();
    uint64_t GetElapsedTime();
    void Cancel();
};
class cSpatialObjectView_s00e9_2ca0 {
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
    virtual void* v28(void*);                            // +0x28
    virtual void* GetModel();                            // +0x2c
    virtual void* GetTransform();                        // +0x30
    virtual float GetScale();                            // +0x34
    virtual void  SetRotation(XformMsg_s00e9_2ca0*);                // +0x38
    virtual void  SetModelMatrix(void*);                 // +0x3c
    virtual void  v40();
    virtual void  UpdateShadow(XformMsg_s00e9_2ca0*);               // +0x44
    virtual void  SetEffectRange(int, int, int);         // +0x48
    virtual void  v4c();
    virtual void  v50();
    virtual void  v54();
    virtual void  v58();
    virtual void  v5c();
    virtual void  v60();
    virtual void  v64();
    virtual void  v68();
    virtual void  v6c();
    virtual void  v70();
    virtual void  v74();
    virtual void* v78(void*);                            // +0x78

    cSpatialObjectView_s00e9_2ca0();                                // 0x00e92af0
    __declspec(noinline) ~cSpatialObjectView_s00e9_2ca0();          // 0x00e92660

    uint32_t mField04;                                   // +0x04
    uint32_t mField08;                                   // +0x08
    cSpatialObject_s00e9_2ca0* mpObject;                            // +0x0c
    void*           mpObjectCombatant;                   // +0x10
    uint8_t mField14;                                    // +0x14
    char    pad_15[3];
    Vec3    mColor;                                      // +0x18
    uint32_t mField24;                                   // +0x24
    uint32_t mField28;                                   // +0x28
    uint32_t mField2c;                                   // +0x2c
    uint8_t mbField30;                                   // +0x30
    uint8_t mbDamageState;                               // +0x31
    uint8_t mbField32;                                   // +0x32
    char    pad_33[1];

    void HandleSimulationUpdate(int deltaTimeMS, int deltaTime);  // 0x00e92ca0
    void OnDamageStateChanged(int state, Key_s00e9_2ca0* key);               // 0x00e93160
    void v926d0(void* model);                                     // 0x00e926d0
};
class cTribeToolView : public cSpatialObjectView_s00e9_2ca0 {
public:
    cTribeToolView();                                    // 0x00e932a0
    ~cTribeToolView();                                   // 0x00e932d0
    cSpatialObjectView_s00e9_2ca0* MakeView(void* gameData);        // 0x00e93380
    void UpdateDamageState();                            // 0x00e934f0

    uint8_t  mbDrawPerimeter;                            // +0x34
    uint8_t  mbTransition;                               // +0x35
    char     pad_36[2];
    int32_t  mDamageState;                               // +0x38
    cGonzagoTimer mTransitionTimer;                      // +0x40
    uint32_t mTransitionEnd;                             // +0x60
    uint32_t mTransitionTime;                            // +0x64
    cIVisualEffect* mDamageEffect;                       // +0x68
};
void*    b767760(void* a);                            // 0x00767760 (ecx = &local)
cSpatialObjectView_s00e9_2ca0::~cSpatialObjectView_s00e9_2ca0()
{
}
// ---- items of slice s00e92ca0 end

// ---- items of slice s00c87be0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct SpatialA {
    char    pad00[0x64];
    float   f64;   // 0x64
    char    pad68[0x76 - 0x68];
    uint8_t b76;   // 0x76
    char    pad77[0x7c - 0x77];
    float   f7c;   // 0x7c
    char    pad80[0x88 - 0x80];
    float   f88;   // 0x88
    char    pad8c[0xa6 - 0x8c];
    uint8_t bA6;   // 0xa6
    uint8_t bA7;   // 0xa7
    void SetValue(float v);
    void Sync(int v);
    void MaybeCall();
};
struct GameData {
    char    pad00[0x68];
    float   f68;    // 0x68
    char    pad6c;
    uint8_t m6d;    // 0x6d
    char    pad6e[0x76 - 0x6e];
    uint8_t b76;    // 0x76
    char    pad77[0x9c - 0x77];
    char*   mp9c;   // 0x9c
    void*   mpA0;   // 0xa0
    char    padA4[0xc0 - 0xa4];
    char*   mpBegin; // 0xc0
    char*   mpEnd;   // 0xc4

    void RemoveOwner(bool b);
    float GetValue();
    int  HasFlag();
    int  FindEntry(int id);
    bool HasEffect(int id);
};
struct Effects {
    char  pad00[0xc0];
    char* mpBegin;   // 0xc0
    char* mpEnd;     // 0xc4
    int   F40(int id);
    void  StartEffect(int id, int b);
    void  StopEffect(int id, int a);
    void  F00(int id, float v);
    void  F30(int id, int* v);
};
struct VObj174 {
virtual void     v000();
virtual void v004();
virtual void v008();
virtual void v00c();
virtual void     v010();
virtual void v014();
virtual VObj174* v018();
virtual VObj174* v01c();
virtual VObj174* v020();
virtual void v024();
virtual void v028();
virtual float* v02c();
virtual void     v030();
virtual void v034();
virtual void v038();
virtual void v03c();
virtual void     v040();
virtual void v044();
virtual void v048();
virtual void v04c();
virtual VObj174* v050();
virtual void v054();
virtual void v058();
virtual void v05c();
virtual void     v060();
virtual void v064();
virtual void v068();
virtual void v06c();
virtual void     v070();
virtual void v074();
virtual void v078();
virtual void v07c();
virtual void     v080();
virtual void v084();
virtual void v088();
virtual void v08c();
virtual bool     v090(void** out);
virtual void v094();
virtual bool v098(void* r);
virtual void v09c();
virtual void     v0a0();
virtual void v0a4();
virtual void v0a8();
virtual unsigned int v0ac();
virtual void     v0b0();
virtual void v0b4();
virtual VObj174* v0b8(uint32_t id, uint32_t arg);
virtual bool     v0bc();
virtual void v0c0();
virtual void v0c4();
    void GetCameraLocationInfo(void* pos, void* a, void* b, void* c);   // 0x007c3d30
};
VObj174* SP_App();                              // 0x0067dd10
struct ToolSub {
    virtual void AddRef();      // 0x00
    virtual void Release();     // 0x04
};
struct ToolRef {
    ToolSub* mpObject;
    ToolRef& operator=(const ToolRef& src) throw() {
        ToolSub* pNew = src.mpObject;
        ToolSub* pOld = mpObject;
        if (pNew != pOld) {
            if (pNew) pNew->AddRef();
            mpObject = pNew;
            if (pOld) pOld->Release();
        }
        return *this;
    }
};
union ToolF {
    float    f;
    uint32_t i;
};
struct ToolData {
    uint32_t f00;   // 0x00
    uint32_t f04;   // 0x04
    uint8_t  b08;   // 0x08
    uint8_t  b09;   // 0x09
    uint8_t  b0a;   // 0x0a
    float    f0c;   // 0x0c
    uint8_t  b10;   // 0x10
    float    f14;   // 0x14
    float    f18;   // 0x18
    ToolF    f1c;   // 0x1c
    ToolF    f20;   // 0x20
    ToolF    f24;   // 0x24
    uint8_t  b28;   // 0x28
    ToolF    f2c;   // 0x2c
    ToolF    f30;   // 0x30
    ToolF    f34;   // 0x34
    ToolRef  m38;   // 0x38

    ToolData(const ToolData& src);
    ToolData& operator=(const ToolData& src);
};
struct SPVec3 { float x, y, z; };
struct CamInfo {
    char     pad00[4];
    uint32_t mFlags;    // 0x04
    char     pad08[0x88 - 0x08];
    float    mDist;     // 0x88
};
// ---- items of slice s00c87be0 end

// ---- items of slice s00c8aa60 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" char g_1695244[];
extern "C" void __cdecl sub_c88d10(void* first, void* last, void* dst);
extern "C" void __cdecl sub_c8a890(void* self);
extern "C" float __cdecl EffectTime(void* self);            // 0x00c88d90
extern "C" void* __cdecl EffectsManager();                  // 0x0067ddd0
extern "C" float* __cdecl Matrix3FromQuaternion(float* dst, const float* q); // 0x0059c190
#pragma optimize("", off)
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
struct Effect;
struct EffectInfo_s00c8_aa60 {
    int   mId;                   // +0x00
    int   mOwner;                // +0x04
    u8    mFlag8;                // +0x08
    u8    mFlag9;                // +0x09
    u8    mFlagA;                // +0x0a
    u8    mPad0b;                // +0x0b
    float mF0c;                  // +0x0c
    u8    mFlag10;               // +0x10
    u8    mPad11;                // +0x11
    u8    mPad12;                // +0x12
    u8    mPad13;                // +0x13
    float mF14;                  // +0x14
    float mF18;                  // +0x18
    int   mI1c, mI20, mI24;      // +0x1c
    u8    mFlag28;               // +0x28
    u8    mPad29;                // +0x29
    u8    mPad2a;                // +0x2a
    u8    mPad2b;                // +0x2b
    int   mPad2c;                // +0x2c
    int   mPad30;                // +0x30
    int   mPad34;                // +0x34
    Effect* mpEffect;            // +0x38

    EffectInfo_s00c8_aa60& operator=(const EffectInfo_s00c8_aa60& other);  // 0x00c88c30 (retail copy-assign: field copies + mpEffect refcount swap)
};
inline void EffectVecMove(EffectInfo_s00c8_aa60* first, EffectInfo_s00c8_aa60* last, EffectInfo_s00c8_aa60* dest) {
    while (first != last) {
        *dest = *first;
        ++first;
        ++dest;
    }
}
struct XformMsg_s00c8_aa60;
struct Effect {
    virtual void e00();
    virtual void e04();             // +0x04  release
    virtual void e08(int);          // +0x08
    virtual void e0c(int);          // +0x0c
    virtual char e10();             // +0x10  is active
    virtual void e14();
    virtual void e18(XformMsg_s00c8_aa60*);    // +0x18
    virtual void e1c();
    virtual void e20();
    virtual void e24();
    virtual void e28();
    virtual void e2c();
    virtual void e30();
    virtual void e34();
    virtual void e38();
    virtual void e3c();
    virtual void e40();
    virtual void e44(int, void*, int);  // +0x44
};
struct Matrix33_s00c8_aa60 {
    float m0, m1, m2, m3, m4, m5, m6, m7, m8;
    void Assign(const float* src);   // 0x0041cb40
    void CopyFrom(const Matrix33_s00c8_aa60& o) {
        m0 = o.m0; m1 = o.m1; m2 = o.m2;
        m3 = o.m3; m4 = o.m4; m5 = o.m5;
        m6 = o.m6; m7 = o.m7; m8 = o.m8;
    }
};
struct EffectVec {
    EffectInfo_s00c8_aa60* pBegin;      // +0x00
    EffectInfo_s00c8_aa60* pEnd;        // +0x04
    EffectInfo_s00c8_aa60* pCap;        // +0x08
    void DoInsertValue(EffectInfo_s00c8_aa60* pPos, const EffectInfo_s00c8_aa60& value);  // 0x00c8a910
    void push_back_default();                                       // 0x00c8add0

    // eastl::vector::erase(position): shift the tail down one element, drop the
    // end, and destroy the stale last element (releases its mpEffect). Inlined
    // into 0x00c8ad30; the move loop comes from EffectVecMove above.
    EffectInfo_s00c8_aa60* erase(EffectInfo_s00c8_aa60* position) {
        EffectInfo_s00c8_aa60* destPosition = position;
        if ((position + 1) < pEnd)
            EffectVecMove(destPosition + 1, pEnd, destPosition);
        --pEnd;
        Effect* de = pEnd->mpEffect;
        if (de) de->e04();
        return destPosition;
    }
};
struct XformMsg_s00c8_aa60 {
    u16      mFlags;      // +0x00
    u16      mCount;      // +0x02
    float    mPosX;       // +0x04
    float    mPosY;       // +0x08
    float    mPosZ;       // +0x0c
    float    mScale;      // +0x10
    Matrix33_s00c8_aa60 mMatrix;     // +0x14
    void Init();          // 0x00434040
};
struct EffectsMgr {
virtual void m00();
virtual void m04();
virtual void m08();
virtual void m0c();
virtual void m10();
virtual void m14();
virtual void m18();
virtual void m1c();
virtual void m20();
virtual void m24();
virtual void m28();
    virtual char Resolve(void* id, int a, Effect** out);   // +0x2c
};
struct ViewVirtuals {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
    virtual float* Transform();      // +0x2c  position
    virtual float* Rotation();       // +0x30  quaternion
};
struct cSpatialObjectView_s00c8_aa60 {
    void**  mpVtbl;              // +0x000
    char    pad_04[0xbc];        // +0x004
    EffectVec mEffects;          // +0x0c0

    __declspec(noinline) Effect* CreateEffectInternal(void* p2, int p3, void* p4, int p5);  // 0x00c8ae20 (cSpatialObjectView::CreateEffectInternal)
    void  UpdateEffects();                                     // 0x00c8aa60
    void  CreateEffect4(void* a, void* b, void* c, void* d);   // 0x00c8b040
    void  CreateEffect3(void* a, void* b, void* c);            // 0x00c8b060
    void  CreateEffect1(void* a);                              // 0x00c8b080
    Effect* sub_b130(void* p2, int p3, void* p4);                // 0x00c8b130
    void  sub_b1a0(void* p);                                   // 0x00c8b1a0
    Effect* sub_b1b0(void* p2, int p3, void* p4);                // 0x00c8b1b0
    void  sub_b210(void* p);                                   // 0x00c8b210
    bool  sub_b220(int param2, int id, char create, void** out);// 0x00c8b220
    void  sub_ad30(int param2, int id);                        // 0x00c8ad30
    void  DestroyAllEffects(int param);                        // 0x00c8b0a0
    void  sub_b2e0();                                          // 0x00c8b2e0
};
// ---- items of slice s00c8aa60 end

// ---- items of slice s00c8aa60_bex begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma optimize("", on)          // the slice's TU compiles this function with /Od (see its nonmatching note)
struct XformMsg;
struct Effect_s00c8_aa60__bex {
    virtual void e00();
    virtual void e04();             // +0x04  release
    virtual void e08(int);          // +0x08
    virtual void e0c(int);          // +0x0c
    virtual char e10();             // +0x10  is active
    virtual void e14();
    virtual void e18(XformMsg*);    // +0x18
    virtual void e1c();
    virtual void e20();
    virtual void e24();
    virtual void e28();
    virtual void e2c();
    virtual void e30();
    virtual void e34();
    virtual void e38();
    virtual void e3c();
    virtual void e40();
    virtual void e44(int, void*, int);  // +0x44
};
struct EffectInfo_s00c8_aa60__bex {
    int   mId;                   // +0x00
    int   mOwner;                // +0x04
    u8    mFlag8;                // +0x08
    u8    mFlag9;                // +0x09
    u8    mFlagA;                // +0x0a
    u8    mPad0b;                // +0x0b
    float mF0c;                  // +0x0c
    u8    mFlag10;               // +0x10
    u8    mPad11;                // +0x11
    u8    mPad12;                // +0x12
    u8    mPad13;                // +0x13
    float mF14;                  // +0x14
    float mF18;                  // +0x18
    int   mI1c, mI20, mI24;      // +0x1c
    u8    mFlag28;               // +0x28
    u8    mPad29;                // +0x29
    u8    mPad2a;                // +0x2a
    u8    mPad2b;                // +0x2b
    int   mPad2c;                // +0x2c
    int   mPad30;                // +0x30
    int   mPad34;                // +0x34
    Effect_s00c8_aa60__bex* mpEffect;            // +0x38

    EffectInfo_s00c8_aa60__bex& operator=(const EffectInfo_s00c8_aa60__bex& other);  // 0x00c88c30
};
inline void EffectVecMove_s00c8_aa60__bex(EffectInfo_s00c8_aa60__bex* first, EffectInfo_s00c8_aa60__bex* last, EffectInfo_s00c8_aa60__bex* dest) {
    while (first != last) {
        *dest = *first;
        ++first;
        ++dest;
    }
}
struct EffectVec_s00c8_aa60__bex {
    EffectInfo_s00c8_aa60__bex* pBegin;      // +0x00
    EffectInfo_s00c8_aa60__bex* pEnd;        // +0x04
    EffectInfo_s00c8_aa60__bex* pCap;        // +0x08
    void DoInsertValue(EffectInfo_s00c8_aa60__bex* pPos, const EffectInfo_s00c8_aa60__bex& value);  // 0x00c8a910
    void push_back_default();                                       // 0x00c8add0

    // eastl::vector::erase(position): shift the tail down one element, drop the
    // end, and destroy the stale last element (releases its mpEffect).
    EffectInfo_s00c8_aa60__bex* erase(EffectInfo_s00c8_aa60__bex* position) {
        EffectInfo_s00c8_aa60__bex* destPosition = position;
        if ((position + 1) < pEnd)
            EffectVecMove_s00c8_aa60__bex(destPosition + 1, pEnd, destPosition);
        --pEnd;
        Effect_s00c8_aa60__bex* de = pEnd->mpEffect;
        if (de) de->e04();
        return destPosition;
    }
};
struct cSpatialObjectView_s00c8_aa60__bex {
    void**  mpVtbl;              // +0x000
    char    pad_04[0xbc];        // +0x004
    EffectVec_s00c8_aa60__bex mEffects;          // +0x0c0

    void sub_ad30(int param2, int id);                         // 0x00c8ad30
};
// ---- items of slice s00c8aa60_bex end

// @ 0x00c88550
void SpatialA::Sync(int v)
{ (void)v; if (f64 != f7c) f64 = f7c; }

// @ 0x00c888e0
int GameData::FindEntry(int id)
{
    for (char* p = mpBegin; p != mpEnd; p += 0x3c) {
        if (*(int*)p == id)
            return *(int*)(p + 0x38);
    }
    return 0;
}

// @ 0x00c88910
bool GameData::HasEffect(int id)
{
    char* p = mpBegin;
    char* end = mpEnd;
    while (p != end) {
        if (*(int*)p == id)
            goto found;
        p += 0x3c;
    }
    p = 0;
found:
    return p != 0;
}

// @ 0x00c88940
int Effects::F40(int id)
{
    char* p = mpBegin;
    char* end = mpEnd;
    if (p == end)
        goto none;
    do {
        if (*(int*)p == id) {
            if (p[8] == 0)
                goto none;
            return 1;
        }
        p += 0x3c;
    } while (p != end);
none:
    return 0;
}

// @ 0x00c88980
void Effects::StartEffect(int id, int b)
{
    (void)b;
    char* p = mpBegin;
    char* end = mpEnd;
    if (p == end)
        return;
    do {
        if (*(int*)p == id) {
            if (p[8] == 0) {
                p[8] = 1;
                p[0xa] = 1;
            }
            return;
        }
        p += 0x3c;
    } while (p != end);
}

// @ 0x00c88ba0
ToolData::ToolData(const ToolData& src)
{
    f00 = src.f00;
    f04 = src.f04;
    b08 = src.b08;
    b09 = src.b09;
    b0a = src.b0a;
    f0c = src.f0c;
    b10 = src.b10;
    f14 = src.f14;
    f18 = src.f18;
    f1c.f = src.f1c.f;
    f20.f = src.f20.f;
    f24.f = src.f24.f;
    b28 = src.b28;
    f2c.f = src.f2c.f;
    f30.f = src.f30.f;
    f34.f = src.f34.f;
    m38.mpObject = src.m38.mpObject;
    if (m38.mpObject)
        m38.mpObject->AddRef();
}

// @ 0x00c88c30
ToolData& ToolData::operator=(const ToolData& src)
{
    f00 = src.f00;
    f04 = src.f04;
    b08 = src.b08;
    b09 = src.b09;
    b0a = src.b0a;
    f0c = src.f0c;
    b10 = src.b10;
    f14 = src.f14;
    f18 = src.f18;
    f1c.i = src.f1c.i;
    f20.i = src.f20.i;
    f24.i = src.f24.i;
    b28 = src.b28;
    f2c.i = src.f2c.i;
    f30.i = src.f30.i;
    f34.i = src.f34.i;
    m38 = src.m38;
    return *this;
}

// @ 0x00c88d90
long double FUN_00c88d90(VObj174* pObj)
{
    CamInfo* p = (CamInfo*)pObj->v0ac();
    if (p != 0) {
        unsigned char b = (unsigned char)((p->mFlags >> 15) & 1);
        if (b != 0) {
            float d = p->mDist;
            return d;
        }
    }
    VObj174* pViewer = SP_App()->v050()->v01c();
    SPVec3 pos;
    pViewer->GetCameraLocationInfo(&pos, 0, 0, 0);
    float* loc = pObj->v02c();
    long double dx = (long double)loc[0] - (long double)pos.x;
    long double dy = (long double)loc[1] - (long double)pos.y;
    long double dz = (long double)loc[2] - (long double)pos.z;
    return sqrtl(dz * dz + dy * dy + dx * dx);
}

// @ 0x00c8aa60
void cSpatialObjectView_s00c8_aa60::UpdateEffects()
{
    if (mEffects.pBegin == mEffects.pEnd)
        return;

    float t = EffectTime(this);

    if (*(u8*)0x1695244 == 0) {
        for (EffectInfo_s00c8_aa60* it = mEffects.pBegin; it != mEffects.pEnd; ) {
            Effect* e = (Effect*)it->mpEffect;
            if (!e) {
                it = (EffectInfo_s00c8_aa60*)((char*)it + 0x3c);
                continue;
            }
            char active = e->e10();
            bool flag = it->mFlag9 != 0 || it->mFlagA != 0;
            if (active || flag) {
                if (it->mF0c <= t) {
                    if (active)
                        ((Effect*)it->mpEffect)->e0c(0);
                } else if (it->mFlag8 && !active && flag) {
                    ((Effect*)it->mpEffect)->e08(0);
                    it->mFlagA = 0;
                }
                it = (EffectInfo_s00c8_aa60*)((char*)it + 0x3c);
            } else {
                if ((EffectInfo_s00c8_aa60*)((char*)it + 0x3c) < mEffects.pEnd)
                    sub_c88d10((char*)it + 0x3c, mEffects.pEnd, it);
                mEffects.pEnd = (EffectInfo_s00c8_aa60*)((char*)mEffects.pEnd - 0x3c);
                if (mEffects.pEnd->mpEffect)
                    ((Effect*)mEffects.pEnd->mpEffect)->e04();
            }
        }
        return;
    }

    for (EffectInfo_s00c8_aa60* it = mEffects.pBegin; it != mEffects.pEnd; ) {
        char local = 0;
        if (!it->mFlag8) {
            it = (EffectInfo_s00c8_aa60*)((char*)it + 0x3c);
            continue;
        }

        Effect* e = (Effect*)it->mpEffect;
        if (it->mF0c > t) {
            if (e) {
                local = e->e10();
            } else {
                EffectsMgr* mgr = (EffectsMgr*)EffectsManager();
                if (mgr->Resolve((void*)it->mOwner, 0, (Effect**)&it->mpEffect)) {
                    XformMsg_s00c8_aa60 msg;
                    msg.Init();
                    float* pos = ((ViewVirtuals*)this)->Transform();
                    msg.mPosX = pos[0];
                    msg.mPosY = pos[1];
                    msg.mPosZ = pos[2];
                    msg.mFlags |= 4;
                    msg.mCount++;
                    float* quat = ((ViewVirtuals*)this)->Rotation();
                    Matrix33_s00c8_aa60 mat;
                    Matrix3FromQuaternion(&mat.m0, quat);
                    msg.mMatrix.CopyFrom(mat);
                    msg.mFlags |= 2;
                    msg.mCount++;
                    ((Effect*)it->mpEffect)->e18(&msg);
                    if (it->mFlag28)
                        ((Effect*)it->mpEffect)->e44(5, &it->mI1c, 3);
                    ((Effect*)it->mpEffect)->e08(0);
                    local = 1;
                }
            }
        } else {
            if (e) {
                local = e->e10();
                ((Effect*)it->mpEffect)->e0c(0);
                if (it->mpEffect) {
                    it->mpEffect = 0;
                    ((Effect*)e)->e04();
                }
            } else if (!it->mFlag9) {
                local = 0;
            }
        }

        if (it->mFlag8 && !local) {
            Effect* dead = (Effect*)it->mpEffect;
            if (dead) {
                it->mpEffect = 0;
                dead->e04();
            }
            if ((EffectInfo_s00c8_aa60*)((char*)it + 0x3c) < mEffects.pEnd)
                sub_c88d10((char*)it + 0x3c, mEffects.pEnd, it);
            mEffects.pEnd = (EffectInfo_s00c8_aa60*)((char*)mEffects.pEnd - 0x3c);
            if (mEffects.pEnd->mpEffect)
                ((Effect*)mEffects.pEnd->mpEffect)->e04();
        } else {
            it = (EffectInfo_s00c8_aa60*)((char*)it + 0x3c);
        }
    }
}

// @ 0x00c8ad30
void cSpatialObjectView_s00c8_aa60__bex::sub_ad30(int param2, int id)
{
    EffectInfo_s00c8_aa60__bex* end = mEffects.pEnd;
    for (EffectInfo_s00c8_aa60__bex* it = mEffects.pBegin; it != end; it = (EffectInfo_s00c8_aa60__bex*)((char*)it + 0x3c)) {
        if (it->mId != param2) continue;
        Effect_s00c8_aa60__bex* pe = it->mpEffect;
        if (pe) {
            if (pe->e10() || it->mFlag8) {
                it->mpEffect->e0c(id);
            }
        }
        mEffects.erase(it);
        return;
    }
}

// @ 0x00c8add0
void EffectVec::push_back_default()
{
    EffectInfo_s00c8_aa60 tmp;
    tmp.mpEffect = 0;
    if (pEnd < pCap) {
        EffectInfo_s00c8_aa60* slot = pEnd;
        pEnd = slot + 1;
        if (slot)
            slot->mpEffect = 0;
    } else {
        DoInsertValue(pEnd, tmp);
        if (tmp.mpEffect)
            ((Effect*)tmp.mpEffect)->e04();
    }
}

// @ 0x00c8ae20
Effect* cSpatialObjectView_s00c8_aa60::CreateEffectInternal(void* p2, int p3, void* p4, int p5)
{
    Effect* local = 0;
    if (*(u8*)0x1695244 == 0) {
        EffectsMgr* mgr = (EffectsMgr*)EffectsManager();
        if (local) {
            Effect* old = local;
            local = 0;
            old->e04();
        }
        if (!mgr->Resolve(p2, p3, &local))
            goto done;
    }

    {
        EffectInfo_s00c8_aa60* it = mEffects.pBegin;
        EffectInfo_s00c8_aa60* end = mEffects.pEnd;
        while (it != end && it->mId != (int)p4)
            it = (EffectInfo_s00c8_aa60*)((char*)it + 0x3c);

        if (it == end) {
            mEffects.push_back_default();
            it = (EffectInfo_s00c8_aa60*)((char*)mEffects.pEnd - 0x3c);
        } else {
            Effect* cur = (Effect*)it->mpEffect;
            if (cur) {
                cur->e0c(1);
                it->mpEffect = 0;
                cur->e04();
            }
        }

        it->mId    = (int)p4;
        it->mOwner = (int)p2;

        Effect* oldEffect = (Effect*)it->mpEffect;
        if (local != oldEffect) {
            if (local)
                local->e00();
            it->mpEffect = local;
            if (oldEffect)
                oldEffect->e04();
        }

        it->mF0c    = *(float*)0x13f1160;
        it->mFlag8  = 0;
        it->mFlag9  = (u8)p5;
        it->mFlagA  = 0;
        it->mFlag10 = 0;
        it->mF14    = *(float*)0x1485720;
        it->mF18    = 0.0f;
        it->mI1c    = *(int*)0x1695248;
        it->mI20    = *(int*)0x169524c;
        it->mI24    = *(int*)0x1695250;
        it->mFlag28 = 0;

        if (local) {
            XformMsg_s00c8_aa60 msg;
            msg.mFlags = 0;
            msg.mCount = 0;
            msg.mPosX  = *(float*)0x16952f4;
            msg.mPosY  = *(float*)0x16952f8;
            msg.mPosZ  = *(float*)0x16952fc;
            msg.mScale = *(float*)0x1485720;
            msg.mMatrix.Assign((const float*)0x16952d0);

            float* pos = ((ViewVirtuals*)this)->Transform();
            msg.mPosX = pos[0];
            msg.mPosY = pos[1];
            msg.mPosZ = pos[2];
            msg.mFlags |= 4;
            msg.mCount++;

            float* quat = ((ViewVirtuals*)this)->Rotation();
            Matrix33_s00c8_aa60 mat;
            Matrix3FromQuaternion(&mat.m0, quat);
                msg.mMatrix.CopyFrom(mat);
            msg.mFlags |= 2;
            msg.mCount++;

            local->e18(&msg);
            if (it->mFlag28)
                local->e44(5, &it->mI1c, 3);
            local->e08(0);
        }
    }

done:
    Effect* result = local;
    if (local)
        local->e04();
    return result;
}

// @ 0x00c8b040
void cSpatialObjectView_s00c8_aa60::CreateEffect4(void* a, void* b, void* c, void* d)
{
    CreateEffectInternal(a, (int)b, c, (int)d);
}
#pragma optimize("", on)

// @ 0x00c8b060
void cSpatialObjectView_s00c8_aa60::CreateEffect3(void* a, void* b, void* c)
{
    CreateEffectInternal(a, (int)b, c, 1);
}

// @ 0x00c8b080
void cSpatialObjectView_s00c8_aa60::CreateEffect1(void* a)
{
    CreateEffectInternal(a, 0, a, 1);
}

// @ 0x00c8b0a0
void cSpatialObjectView_s00c8_aa60::DestroyAllEffects(int param)
{
    int force = param;
    for (EffectInfo_s00c8_aa60* it = mEffects.pBegin; it != mEffects.pEnd; it = (EffectInfo_s00c8_aa60*)((char*)it + 0x3c)) {
        if (!it->mpEffect) continue;
        char c = ((char(__thiscall*)(void*))(*(void***)it->mpEffect)[0x10 / 4])(it->mpEffect);
        if (!c && !it->mFlag8) continue;
        unsigned long long id = ((unsigned long long(__thiscall*)(void*))(*(void***)it->mpEffect)[0x60 / 4])(it->mpEffect);
        if (id == 0x2abf6155ULL) {
            force = 1;
        } else {
            id = ((unsigned long long(__thiscall*)(void*))(*(void***)it->mpEffect)[0x60 / 4])(it->mpEffect);
            if (id == 0x2241f9c6ULL) force = 1;
        }
        ((void(__thiscall*)(void*, int))(*(void***)it->mpEffect)[0xc / 4])(it->mpEffect, force);
    }
    ((void(__thiscall*)(void*, EffectInfo_s00c8_aa60*, EffectInfo_s00c8_aa60*))sub_c8a890)(&mEffects.pBegin, mEffects.pBegin, mEffects.pEnd);
}

// @ 0x00c8b130
Effect* cSpatialObjectView_s00c8_aa60::sub_b130(void* p2, int p3, void* p4)
{
    Effect* e = CreateEffectInternal(p2, p3, p4, 1);
    if (g_1695244[0] || e) {
        for (EffectInfo_s00c8_aa60* it = mEffects.pBegin; it != mEffects.pEnd; ++it) {
            if (it->mId == (int)p4) {
                if (!it->mFlag8) { it->mFlag8 = 1; it->mFlagA = 1; }
                return e;
            }
        }
    }
    return e;
}

// @ 0x00c8b1b0
Effect* cSpatialObjectView_s00c8_aa60::sub_b1b0(void* p2, int p3, void* p4)
{
    Effect* e = CreateEffectInternal(p2, p3, p4, 0);
    if (e) {
        for (EffectInfo_s00c8_aa60* it = mEffects.pBegin; it != mEffects.pEnd; ++it) {
            if (it->mId == (int)p4) {
                if (!it->mFlag8) { it->mFlag8 = 1; it->mFlagA = 1; }
                return e;
            }
        }
    }
    return e;
}

// @ 0x00c8b220
bool cSpatialObjectView_s00c8_aa60::sub_b220(int param2, int id, char create, void** out)
{
    EffectInfo_s00c8_aa60* it = mEffects.pBegin;
    EffectInfo_s00c8_aa60* end = mEffects.pEnd;
    while (it != end && it->mId != id) it = (EffectInfo_s00c8_aa60*)((char*)it + 0x3c);

    bool created = false;
    void* found = 0;
    if (create) {
        if (it == end) {
            found = CreateEffectInternal((void*)param2, 0, (void*)id, 1);
            created = found != 0;
        } else {
            found = it->mpEffect;
        }
    } else if (it != end) {
        if (it->mpEffect) {
            char c = ((char(__thiscall*)(void*))(*(void***)it->mpEffect)[0x10 / 4])(it->mpEffect);
            if (c || it->mFlag8) {
                ((void(__thiscall*)(void*, int))(*(void***)it->mpEffect)[0xc / 4])(it->mpEffect, 0);
            }
        }
        if ((EffectInfo_s00c8_aa60*)((char*)it + 0x3c) < mEffects.pEnd) {
            sub_c88d10((char*)it + 0x3c, mEffects.pEnd, it);
        }
        mEffects.pEnd = (EffectInfo_s00c8_aa60*)((char*)mEffects.pEnd - 0x3c);
        if (mEffects.pEnd->mpEffect) {
            ((void(__thiscall*)(void*))(*(void***)mEffects.pEnd->mpEffect)[4 / 4])(mEffects.pEnd->mpEffect);
        }
    }
    if (out) *out = found;
    return created;
}

// @ 0x00c8b2e0
void cSpatialObjectView_s00c8_aa60::sub_b2e0()
{
    char* self = (char*)this;
    // [self+0x9c] holds a pointer to a handle whose first field is the real object;
    // the original loads ecx = *(void**)(self+0x9c) then edx = *ecx (the vtable) and
    // passes the handle, not the object, as the first stack argument.
    void* h1 = *(void**)(self + 0x9c);
    if (h1) {
        void* o1 = *(void**)h1;
        ((void(__thiscall*)(void*, void*, int))(*(void***)o1)[0x16c / 4])(o1, h1, 0);
    }
    void* h2 = *(void**)(self + 0x9c);
    if (h2) {
        *(void**)(self + 0x9c) = 0;
        if (*(int*)((char*)h2 + 0x40) > 1) --*(int*)((char*)h2 + 0x40);
        else {
            void* o2 = *(void**)h2;
            ((void(__thiscall*)(void*, void*, bool))(*(void***)o2)[0x170 / 4])(
                o2, h2, (bool)(((*(u32*)((char*)h2 + 4)) >> 31) & 1));
        }
    }
    void* c = *(void**)(self + 0xa0);
    if (c) {
        *(void**)(self + 0xa0) = 0;
        ((void(__thiscall*)(void*))(*(void***)c)[4 / 4])(c);
    }
    DestroyAllEffects(1);
}

// @ 0x00e92620
void cSpatialObjectView::SetIsInWorld(bool b)
{
    void* p = (void*)VC0(void*, this, 0x2c);
    if (p == 0)
        return;
    if (b) {
        void** slot0 = *(void***)*(void**)p;
        ((void (__stdcall*)(void*, int))slot0[0x16c / 4])(p, 1);
    } else {
        void** slot0 = *(void***)*(void**)p;
        ((void (__stdcall*)(void*, int))slot0[0x16c / 4])(p, 0);
    }
}

// @ 0x00e92660
cSpatialObjectView::~cSpatialObjectView()
{
    cSpatialObject* o = mpObject;
    *(void**)this = (void*)g_1486c00;
    if (o != 0)
        VC0(void, o, 0xa4);

    o = mpObject;
    if (o != 0) {
        mpObject = 0;
        VC0(void, o, 0xc0);
    }
    void* c = mpObjectCombatant;
    mpObjectCombatant = 0;
    if (c != 0)
        VC0(void, c, 0x64);

    c = mpObjectCombatant;
    if (c != 0)
        VC0(void, c, 0x64);

    o = mpObject;
    if (o != 0)
        VC0(void, o, 0xc0);

    *(void**)this = (void*)g_1455648;
}

// @ 0x00e926d0
extern "C" char g_17f243b[];
struct ISpatialObj_926d0 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30();
    virtual float GetScale();                         // +0x34
    virtual void v38(); virtual void v3c(); virtual void v40(); virtual void v44();
    virtual void v48(); virtual void v4c(); virtual void v50(); virtual void v54();
    virtual void v58(); virtual void v5c(); virtual void v60();
    virtual void SetModel(void* key, float scale);    // +0x64
};
void cSpatialObjectView::SetModel_926d0(void* model)
{
    *(uint32_t*)((char*)mpObject + 0x50) &= 0xffffffefu;
    ISpatialObj_926d0* o = (ISpatialObj_926d0*)mpObject;
    o->SetModel((char*)model + 0x70, o->GetScale());
    cSpatialObject* obj = mpObject;
    void* go = obj ? (void*)VC1(void*, obj, 0xb8, uint32_t, (uint32_t)g_17f243b) : 0;
    FUN_00b3d310()->Fn_00b48770(go, true);
}

// @ 0x00e92740
void cSpatialObjectView::MakeView_740(void* a, void* b, void* c, void* d)
{
    void* newObj = 0;
    if (a != 0)
        newObj = (void*)VC1(void*, a, 0xc, uint32_t, 0x1186577);

    if (newObj != mpObject) {
        if (newObj != 0)
            VC0(void, newObj, 0xbc);
        cSpatialObject* old = mpObject;
        mpObject = (cSpatialObject*)newObj;
        if (old != 0)
            VC0(void, old, 0xc0);
    }
    if (mpObject == 0)
        return;

    void* sub = (void*)VC0(void*, mpObject, 0xac);
    bool doSet = false;
    if (sub != 0) {
        void* have = (void*)VC0(void*, mpObject, 0x98);
        bool same = (*(uint32_t*)have == *(uint32_t*)d)
                 && (*(uint32_t*)((char*)have + 4) == *(uint32_t*)((char*)d + 4))
                 && (*(uint32_t*)((char*)have + 8) == *(uint32_t*)((char*)d + 8));
        if (!same || VC0(bool, mpObject, 0x88)) {
            VC1(void, mpObject, 0x94, void*, d);
            if (VC1(bool, mpObject, 0xa0, void*, a)) {
                void* s2 = (void*)VC0(void*, mpObject, 0xac);
                if (s2 != 0) {
                    bool vis = VC0(bool, mpObject, 0x9c);
                    mbField30 = !vis;
                    if (vis)
                        SetModel_926d0(s2);
                }
            }
            doSet = true;
        }
    }

    if (doSet) {
        if (mField14) {
            *(V3*)((char*)this + 0x18) = *(V3*)((char*)sub + 0x4c);
        }
        else {
            *(V3*)((char*)this + 0x18) = *(V3*)c;
            *(V3*)((char*)sub + 0x4c) = *(V3*)c;
        }
        void* oldc = *(void**)((char*)sub + 0x64);
        if (a != oldc) {
            if (a != 0)
                (*(void(__thiscall**)(void*))a)(a);
            *(void**)((char*)sub + 0x64) = a;
            if (oldc != 0)
                (*(void(__thiscall**)(void*, int))(*(void**)oldc))(oldc, 0);
        }
        *(uint32_t*)((char*)sub + 0x60) = VC0(uint32_t, a, 0x20);
        VC1(void, mpObject, 0x8c, int, 0);
        mbField31 = 0;
    }

    {
        void* v = 0;
        if (mpObject != 0)
            v = (void*)VC1(void*, mpObject, 0xb8, uint32_t, 0x13f94d4);
        void* oldv = mpObjectCombatant;
        if (v != oldv) {
            if (v != 0)
                VC0(void, v, 0x60);
            mpObjectCombatant = v;
            if (oldv != 0)
                VC0(void, oldv, 0x64);
        }
    }
}

// @ 0x00e92910
void cSpatialObjectView::Init(void* gamedata)
{
    void* newObj = 0;
    if (gamedata != 0)
        newObj = (void*)VC1(void*, gamedata, 0xc, uint32_t, 0x1186577);

    if (newObj != mpObject) {
        if (newObj != 0)
            VC0(void, newObj, 0xbc);
        cSpatialObject* old = mpObject;
        mpObject = (cSpatialObject*)newObj;
        if (old != 0)
            VC0(void, old, 0xc0);
    }
    if (mpObject == 0)
        return;
    void* sub = (void*)VC0(void*, mpObject, 0xac);
    if (sub == 0)
        return;

    void* oldc = *(void**)((char*)sub + 0x64);
    if (gamedata != oldc) {
        if (gamedata != 0)
            (*(void(__thiscall**)(void*))gamedata)(gamedata);
        *(void**)((char*)sub + 0x64) = gamedata;
        if (oldc != 0)
            (*(void(__thiscall**)(void*, int))(*(void**)oldc))(oldc, 0);
    }
    *(uint32_t*)((char*)sub + 0x60) = VC0(uint32_t, gamedata, 0x20);
}

// @ 0x00e929b0
void* cSpatialObjectView::SetModel()
{
    cSpatialObject* o = mpObject;
    if (o != 0)
        return (void*)VC0(void*, o, 0xac);
    return 0;
}

// @ 0x00e929f0
void* cSpatialObjectView::GetData()
{
    cSpatialObject* o = mpObject;
    if (o != 0)
        return (void*)VC1(void*, o, 0xb8, uint32_t, 0x17f243b);
    return 0;
}

// @ 0x00e92a10
void cSpatialObjectView::UpdateFadeState()
{
    void* g = *(void**)0x016c7aa4;
    if (g == 0)
        return;
    if (*(int*)((char*)g + 0xcc) != 1)
        return;

    void* self = (void*)VC0(void*, this, 0xac);
    if (self == 0)
        return;
    cSpatialObject* obj = mpObject;
    if (*(char*)((char*)obj + 0x6f) == 0)
        return;
    if (!VC0(bool, this, 0x20))
        return;

    bool b = false;
    void* p = FUN_00ae66d0(this);
    if (p != 0 && p == FUN_00efe5a0())
        b = true;

    if (*(char*)((char*)obj + 0x6e) != 0) {
        *(uint32_t*)((char*)self + 4) |= 8u;
        *(uint8_t*)((char*)self + 0x5c) = 1;
        return;
    }
    if (*(char*)((char*)obj + 0x78) != 0) {
        *(uint32_t*)((char*)self + 4) |= 8u;
        *(uint8_t* const)((char*)self + 0x5c) = 4;
        return;
    }
    if (b) {
        bool r = VC0(bool, this, 0x24);
        *(uint32_t*)((char*)self + 4) |= 8u;
        *(uint8_t*)((char*)self + 0x5c) = r ? 3 : 0;
        return;
    }
    if (VC0(bool, this, 0x24)) {
        *(uint32_t*)((char*)self + 4) |= 8u;
        *(uint8_t*)((char*)self + 0x5c) = 2;
        return;
    }
LAB_off:
    *(uint32_t*)((char*)self + 4) &= 0xfffffff7u;
}

// @ 0x00e92af0
cSpatialObjectView::cSpatialObjectView()
{
    mField08 = 0;
    mField04 = 0;
    *(void**)this = (void*)g_1486c00;
    mpObject = 0;
    mpObjectCombatant = 0;
    mField14 = 0;
    mColor.x = g_defaultColorR;
    mColor.y = g_defaultColorG;
    mColor.z = g_defaultColorB;
    mField24 = 0;
    mField28 = 0;
    mField2c = 0;
    mbField30 = 0;
    mbField31 = 0;
    mbField32 = 0;
}

// @ 0x00e92b50
cSpatialObjectView* MakeView_92b50(void* gamedata)
{
    cSpatialObjectView* v = (cSpatialObjectView*)operator_new_sp(
        0x34, "Simulator/cSpatialObjectView", 0, 0, 0, 0);
    if (v != 0) {
        v->mField08 = 0;
        v->mField04 = 0;
        *(void**)v = (void*)0x1486c00;
        v->mpObject = 0;
        v->mpObjectCombatant = 0;
        v->mField14 = 0;
        v->mColor.x = g_defaultColorR;
        v->mColor.y = g_defaultColorG;
        v->mColor.z = g_defaultColorB;
        v->mField24 = 0;
        v->mField28 = 0;
        v->mField2c = 0;
        v->mbField30 = 0;
        v->mbField31 = 0;
        v->mbField32 = 0;
    }
    else {
        v = 0;
    }
    if (gamedata != 0) {
        void* obj = (void*)VC1(void*, gamedata, 0xc, uint32_t, 0x1186577);
        if (obj != 0) {
            v->mField14 = 1;
            if (VC0(bool, obj, 0x90)) {
                void* pos = (void*)VC0(void*, obj, 0x98);
                V3 p = *(V3*)pos;
                void* world = GonzagoModelWorld();
                VC2(void, v, 0x28, void*, gamedata, void*, world);
                (void)p;
                return v;
            }
            VC1(void, v, 0x24, void*, gamedata);
        }
    }
    return v;
}

// @ 0x00e92c60
unsigned char cSpatialObjectView::GetIsInWorld()
{
    void* p = (void*)VC0(void*, this, 0x2c);
    if (p != 0) {
        unsigned char b = (*(uint32_t*)((char*)p + 4) >> 0xf);
        b &= 1;
        return b;
    }
    return 0;
}

// @ 0x00e92c80
unsigned char cSpatialObjectView::GetIsVisible()
{
    void* p = (void*)VC0(void*, this, 0x2c);
    if (p == 0)
        return 0;
    unsigned char b = *(unsigned char*)((char*)p + 4);
    b &= 1;
    return b;
}

// @ 0x00e93160
void cSpatialObjectView_s00e9_2ca0::OnDamageStateChanged(int state, Key_s00e9_2ca0* key)
{
    void* model = (void*)VC0_s00e9_2ca0(void*, mpObject, 0xac);
    void* model2 = (void*)VC0_s00e9_2ca0(void*, mpObject, 0xb0);
    if (model == 0 || model2 == 0)
        return;
    if (((FU32(model, 4) >> 0xe) & 1) == 0)
        return;
    if (mbDamageState == (uint8_t)state)
        return;
    mbDamageState = (uint8_t)state;

    int n = VC1_s00e9_2ca0(int, model2, 0x64, void*, model);
    for (int i = 0; i < n; ++i) {
        void* elem = VC2_s00e9_2ca0(void*, model2, 0x68, void*, model, int, i);
        uint32_t vec[4];
        b767760(elem);
        int cnt = VC2_s00e9_2ca0(int, model2, 0x6c, void*, model, int, i);
        for (int j = 0; j < cnt; ++j) {
            uint32_t e = *(uint32_t*)&vec[j];
            if (key == 0 || e == key->mInstance)
                VC4(void, model2, 0x70, void*, model, uint32_t, e, void*, vec, int, 0);
        }
    }
}

// @ 0x00e932a0
cTribeToolView::cTribeToolView()
: mbDrawPerimeter(0), mbTransition(0), mDamageState(0), mDamageEffect(0)
{
}

// @ 0x00e932d0
cTribeToolView::~cTribeToolView()
{
    *(void**)this = (void*)g_1486c54;
    cIVisualEffect* e = mDamageEffect;
    if (e) {
        VC1_s00e9_2ca0(void, e, 0xc, int, 1);
        e = mDamageEffect;
        if (e) {
            mDamageEffect = 0;
            VC0_s00e9_2ca0(void, e, 4);
        }
    }
    if (mpObject->FindEffectRaw(0x49b925c))
        mpObject->KillEffect(0x49b925c, 1);
    if (mpObject->FindEffectRaw(0x49b925d))
        mpObject->KillEffect(0x49b925d, 1);
    e = mDamageEffect;
    if (e)
        VC0_s00e9_2ca0(void, e, 4);
}
