// src/game/SPGonzago/SPCityViews.cpp -- migrated from slice(s) s00e8a510, s00e899b0, s00e88c30, s00e86d40 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCityViews.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cGonzagoTimer.h"

namespace SP { class cSpatialObjectView; }

// unnamed retail callees and globals (address in the comment)
extern const float kOne;           // 0x01485720 (1.0f)
extern const float kOneAndAHalf;   // 0x01485548 (1.5f)
#include <math.h>
#include <string.h>
#include "SP/cBuildingData.h"
#include "SP/cCity.h"
#include "SP/cCityTerritory.h"
#include "SP/cCombatant.h"
#include "SP/cSPTimer.h"
#include "SP/cSpatialObject.h"
#include "SP/cPlanetModel.h"
#include "SP/cVehicle.h"
#include "SP/cBuilding.h"
#include "SP/cGameNounManager.h"

// ---- items of slice s00e86d40 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char      u8;
typedef unsigned int       u32;
#define VS(o, off)              (*(void**)(*(char**)(o) + (off)))
#define VC0(R, o, off)          ((R (__thiscall*)(void*))VS(o, off))((void*)(o))
#define VC1(R, o, off, T1, a1)  ((R (__thiscall*)(void*, T1))VS(o, off))((void*)(o), (a1))
#define VC2(R, o, off, T1, a1, T2, a2) \
    ((R (__thiscall*)(void*, T1, T2))VS(o, off))((void*)(o), (a1), (a2))
#define VC3(R, o, off, T1, a1, T2, a2, T3, a3) \
    ((R (__thiscall*)(void*, T1, T2, T3))VS(o, off))((void*)(o), (a1), (a2), (a3))
extern const float kOne;           // 0x01485720 (1.0f)
extern const float kOneAndAHalf;   // 0x01485548 (1.5f)
struct Vec3 { float x, y, z; };
struct cGonzagoTimer {
    void Construct();                                // 0x00b63890
    void Destruct();                                 // 0x00b638b0
    u32 mData[8];                                    // +0x00 .. +0x1f
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
    virtual void v28(void*);
    virtual void* GetModel();                            // +0x2c
    virtual void* GetTransform();                        // +0x30

    cSpatialObjectView();                                // 0x00e92af0
    ~cSpatialObjectView();                               // 0x00e92660
    void Init(void* gameData);                           // 0x00e92910
    void Init(void* a, void* b, void* c, void* d);       // 0x00e92740

    u32     mField04;                                    // +0x04
    u32     mField08;                                    // +0x08
    void*   mpObject;                                    // +0x0c
    void*   mpObjectCombatant;                           // +0x10
    u8      mField14;                                    // +0x14
    char    pad_15[3];
    Vec3    mColor;                                      // +0x18
    u32     mField24;                                    // +0x24
    u32     mField28;                                    // +0x28
    u32     mField2c;                                    // +0x2c
    u8      mbField30;                                   // +0x30
    u8      mbDamageState;                               // +0x31
    u8      mbField32;                                   // +0x32
    char    pad_33[1];
};
class cBuildingView : public cSpatialObjectView {
public:
    void*   mpEffect_34;                                 // +0x34  refcounted effect
    union {
        int     mState_38;                               // +0x38  visibility/state word
        u8      mbVisible_38;                            // +0x38  low byte (SetVisible)
    };
    float   mScale_3c;                                   // +0x3c
    float   mScale_40;                                   // +0x40
    float   mScale_44;                                   // +0x44
    int     mXformIndices[4];                            // +0x48  sentinel -1 each
    u8      mbFlag_58;                                   // +0x58
    char    pad_59[7];
    cGonzagoTimer mTimer;                                // +0x60  cGonzagoTimer (0x20)
    void*   mpEffect_80;                                 // +0x80  refcounted effect
    void*   mpEffect_84;                                 // +0x84  refcounted effect

    void SetVisible(u8 b);                               // 0x00e875b0
    void ViewInit1(void* gameData);                      // 0x00e87560
    void ViewInit4(void* a, void* b, void* c, void* d);  // 0x00e87580
    cBuildingView();                                     // 0x00e87b70
    ~cBuildingView();                                    // 0x00e87be0
};
void cSpatialObjectView_DestroyAllEffects(void* obj, int flag);                 // 0x00c8b0a0
void  FUN_00c8b220(u32 key, u32 id, int flag, float* out);                      // 0x00c8b220
void  FUN_00bd9480(void* self, float* out);                                     // 0x00bd9480
bool  FUN_00bd8240(void* self);                                                 // 0x00bd8240
bool  FUN_00bfc600(void* self);                                                 // 0x00bfc600
void* FUN_00bce5c0(void* self);                                                 // 0x00bce5c0
void* FUN_00fc7e50(void* self);                                                 // 0x00fc7e50
void* FUN_010666a0();                                             // 0x010666a0 (cdecl, no args)
struct MinimapHost { void* GetPanel(); };                         // 0x01067e60 (this=host, +0x31c)
struct cMinimapWin { void RemoveIcon(void* view, int a, int b); };// 0x00e0f9c0 (thiscall on the window)
// ---- items of slice s00e86d40 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern const float kHalf;          // 0x01471064 (0.5f)
extern const float kForty;         // 0x013f08c0 (40.0f)
extern const float kTiny;          // 0x013ec4b8 (1e-08f)
extern const float kTenth;         // 0x01488874 (0.1f)

// ---- items of slice s00e88c30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void operator_delete_array(void*);   // 0x00f47380
extern void* vtbl_cCityTerritory;       // 0x01486208
extern void* vtbl_cCitySoundLoopView;   // 0x0148625c
extern char g_allocTag_013f6b3c;               // 0x013f6b3c (allocation tag)
extern "C" void* GetCurrentGameMode();                    // 0x00b5b800
extern "C" void* FUN_00bd99e0(void* v);                   // 0x00bd99e0
extern "C" void* GonzagoModelWorld();                      // 0x00b3d520
extern "C" void* PropertyManager();                       // 0x0067de30
extern char  g_gameModeCity_1654c10;                      // 0x01654c10
typedef unsigned short u16;
struct cSpatialObjectView_s00e8_8c30 {
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
    virtual void v28(void*);
    virtual void* v2c();
    virtual void* v30();

    void Dtor();                        // 0x00e92660  ??1cSpatialObjectView@@QAE@XZ

    u32   mField04;                     // +0x04
    u32   mField08;                     // +0x08
    void* mpObject;                     // +0x0c
    void* mpObjectCombatant;            // +0x10
    u8    mField14;                     // +0x14
    char  pad_15[3];
    Vec3  mColor;                       // +0x18
    u32   mField24;                     // +0x24
    u32   mField28;                     // +0x28
    u32   mField2c;                     // +0x2c
    u8    mbField30;                    // +0x30
    u8    mbDamageState;                // +0x31
    u8    mbField32;                    // +0x32
    char  pad_33[1];
};
struct cSpatialObject {
    void DestroyAllEffects(int flag);   // 0x00c8b0a0
};
struct cCityTerritory : cSpatialObjectView_s00e8_8c30 {
    void* deleting_dtor(char flag);
};
struct cCitySoundLoopView : cSpatialObjectView_s00e8_8c30 {
    void* mpEffect_34;                  // +0x34
    void* deleting_dtor(char flag);
};
struct cSPUIMeter {
    virtual void AddRef();                    // +0x00
    virtual void Release();                   // +0x04
    virtual void v08();                       // +0x08
    virtual void v0c();                       // +0x0c

    cSPUIMeter* Init(u32 hdr, u32 a, u32 b, const wchar_t* name, u32 d);  // 0x00e06a10
    void Shutdown(int flag);                  // 0x00e06940
    void Func_e06c50(void* obj);              // 0x00e06c50
    void Func_e06cf0(u32 v);                  // 0x00e06cf0
};
template <class T>
struct AutoRef {
    T* mpObj;
    T* operator=(T* p) {
        T* old = mpObj;
        if (p != old) {
            if (p)   p->AddRef();
            mpObj = p;
            if (old) old->Release();
        }
        return p;
    }
};
void* operator_new(u32 size, const char* name, int a, int b, int c, int d);  // 0x00f473a0
struct cCitySub {
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
    virtual bool Func58();                    // +0x58
};
struct cCityHall {
virtual void v00();
virtual void v04();
virtual void v08();
    virtual u32  Func0c(u32 arg);             // +0x0c
};
struct cCity {
    u8       mPre_120[0x120];
    cCitySub mSub;                            // +0x120
    u8       mPad_124[0x748 - 0x124];
    float    mField748;                       // +0x748  progress 0..100
    int      mField74c;                       // +0x74c  state id
    int      mField750;                       // +0x750
    int      mField754;                       // +0x754  state id
    int      mField758;                       // +0x758
    int      mField75c;                       // +0x75c  state id

    cCityHall* GetCityHall();                 // 0x00bd9b40
};
struct cCityFeedbackView {
    void*    mField00;
    void*    mField04;
    void*    mField08;
    cCity*   mpObject;                        // +0x0c
    AutoRef<cSPUIMeter> mMeter1;              // +0x10
    AutoRef<cSPUIMeter> mMeter2;              // +0x14
    AutoRef<cSPUIMeter> mMeter3;              // +0x18

    cSPUIMeter* UpdateLoyaltyBar(cSPUIMeter* p, char bShow, u32 hdr);
    void        HandleSimulationUpdate(int, int);
};
#define VC4(R, o, off, T1, a1, T2, a2, T3, a3, T4, a4) \
    ((R (__thiscall*)(void*, T1, T2, T3, T4))VS(o, off))((void*)(o), (a1), (a2), (a3), (a4))
struct cSPTimer {                        // 0x00bc3130 Restart
    u32 mData[8];                        // +0x00..+0x1f
    void Restart();                      // 0x00bc3130
};
struct cBuildingSub {                    // embedded sub-object at cBuildingData +0x34
    virtual void s00();
};
struct cBuildingData {                   // argument of ConfigureBuildingView
    u8          mPad_34[0x34];
    cBuildingSub mSub;                   // +0x34
};
struct cXform {                          // object returned by cBuildingView vtable[0x2c]
    u8    mPad_4c[0x4c];
    float mField4c;                      // +0x4c
    float mField50;                      // +0x50
    float mField54;                      // +0x54
};
struct cCombatant {                      // 0x008e7f80 GetDamageState
    int GetDamageState();                // 0x008e7f80
};
struct PropRef {                         // 0x0041ea70 GetFloat
    u8    mPad_12[0x12];
    u16   mKind;                         // +0x12
    float* GetFloat();                   // 0x0041ea70
};
class cBuildingView_s00e8_8c30 : public cSpatialObjectView_s00e8_8c30 {
public:
    void*    mpEffect_34;                // +0x34
    int      mState_38;                  // +0x38
    float    mScale_3c;                  // +0x3c
    float    mScale_40;                  // +0x40
    float    mScale_44;                  // +0x44
    int      mXformIndices[4];           // +0x48
    u8       mbFlag_58;                  // +0x58
    u8       mPad_59[7];
    cSPTimer mTimer;                     // +0x60
    void*    mpEffect_80;                // +0x80
    void*    mpEffect_84;                // +0x84

    void ConfigureBuildingView(cBuildingData* p2);        // 0x00e88e10
    void UpdateSpaceCaptureEffects();                     // 0x00e89060
    void SpawnAndPlaceDamageEffects();                    // 0x00e89530
};
extern "C" void  SetKeyKind(void* v, u32 kind, int flag);  // 0x0068c6d0
extern "C" void  GetPropertyT_int(void* obj, u32 tag, int* out);  // 0x0040cf10
extern Vec3  g_cityColor_15a87b4;                         // 0x015a87b4 (RGB vec)
// ---- items of slice s00e88c30 end

// ---- items of slice s00e899b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float   g_1485720;        // 0x01485720  1.0f
extern float   g_1470f1c;        // 0x01470f1c  0.4f
extern float   g_1486344;        // 0x01486344  -12.0f (effect offset scale)
extern float   g_14861d0;        // 0x014861d0   1.5258789e-05f (axis epsilon)
extern float   g_f_16c4bbc;      // 0x016c4bbc  unit vector x
extern float   g_f_16c4bc0;      // 0x016c4bc0  unit vector y
extern float   g_f_16c4bc4;      // 0x016c4bc4  unit vector z
extern void* vtbl_citywalls[];   // 0x01486290
extern void* vtbl_turret[];      // 0x014608ec
extern void* vtbl_cultural[];    // 0x01486310
extern void*         EffectsManagerPtr();     // 0x0067ddd0
extern void*         GetSystemAT();           // 0x00a206f0
extern "C" double fabs(double);
extern "C" double ceil(double);
#pragma warning(disable : 4100)
#pragma warning(disable : 4244)
struct Float3 {
    float x, y, z;
    Float3() {}
    Float3(float a, float b, float c) : x(a), y(b), z(c) {}
};
struct Matrix3 {
    float m[9];
    Matrix3() {}
    Matrix3(const Matrix3& o);
};
extern u32     g_bucketSentinel; // 0x0154df28  static empty bucket array
extern Matrix3 g_mtx_16c4b98;    // 0x016c4b98  default orientation
void* operator new(unsigned int, const char*, int, int, int, int);
void  operator delete(void*);
void  operator delete[](void*);
extern void          Start3dSoundByName(u32, u32, float, float, float);  // 0x00571f80
extern void          FUN_00572020(u32, u8);   // 0x00572020  audio effect dispatch thunk
struct IObj {
    virtual void   v00();
    virtual void   v04();
    virtual void   v08(u32);
    virtual void   v0C();
    virtual void   v10(u32);
    virtual void   v14();
    virtual void   v18(void*);
    virtual void   v1C();
    virtual u32    v20();
    virtual void   v24(u32);
    virtual void   v28();
    virtual void   v2C(u32, u32, void*);
    virtual void   v30();
    virtual void   v34();
    virtual void   v38();
    virtual void   v3C();
    virtual void   v40();
    virtual void   v44();
    virtual void   v48();
    virtual void   v4C();
    virtual void   v50();
    virtual void   v54();
    virtual float* v58();
    virtual int    v5C();
    virtual void   v60();
    virtual void   v64();
    virtual void   v68();
    virtual void   v6C();
    virtual void   v70();
    virtual void   v74();
    virtual void   v78();
    virtual void   v7C();
    virtual void   v80();
    virtual void   v84();
    virtual void   v88();
    virtual void   v8C();
    virtual void   v90();
    virtual void   v94();
    virtual void   v98();
    virtual void   v9C();
    virtual void   vA0();
    virtual void   vA4();
    virtual void   vA8();
    virtual void   vAC();
    virtual void   vB0();
    virtual void   vB4();
    virtual void*  vB8(u32);
};
struct ITarget {                    // the object stored in cSpatialObjectView::mpObject
virtual void   a00();
virtual void a04();
virtual void a08();
virtual void a0C();
virtual void   a10();
virtual void a14();
virtual void a18();
virtual void a1C();
virtual void   a20();
virtual void a24();
virtual void a28();
virtual void a2C();
virtual void*  a30();
virtual void a34();
virtual void a38();
virtual void a3C();
virtual void   a40();
virtual void a44();
virtual void a48();
virtual void a4C();
virtual void   a50();
virtual void a54();
virtual void a58();
virtual void a5C();
virtual void   a60();
virtual void a64();
virtual void a68();
virtual void a6C();
virtual void   a70();
virtual void a74();
virtual void a78();
virtual void a7C();
virtual void   a80();
virtual void a84();
virtual void a88();
virtual void a8C();
virtual void   a90();
virtual void a94();
virtual void a98();
virtual void a9C();
virtual void   aA0();
virtual void aA4();
virtual void aA8();
virtual void aAC();
virtual void   aB0();
virtual void aB4();
virtual void* aB8(u32);
};
struct IEmb {                       // embedded object at ITarget + 0x100
virtual void   e00();
virtual void e04();
virtual void e08();
virtual void e0C();
virtual void   e10();
virtual void e14();
virtual void e18();
virtual void e1C();
virtual void   e20();
virtual void e24();
virtual void e28();
virtual Float3* e2C();
virtual void   e30();
virtual void e34();
virtual void e38();
virtual void e3C();
virtual void   e40();
virtual void e44();
virtual void e48();
virtual void e4C();
virtual void   e50();
virtual void e54();
virtual void e58();
virtual Float3* e5C(Float3* out);
};
struct IObj0C {                     // object with a v0C(u32) accessor
virtual void  x00();
virtual void x04();
virtual void x08();
virtual void* x0C(u32);
};
struct IEffect {                    // reference-counted visual effect handle
virtual void b00();
virtual void b04();
virtual void b08();
virtual void b0C();
virtual void b10();
virtual void b14();
virtual void b18(void* msg);
virtual void b1C();
virtual void b20();
virtual void b24();
virtual void b28();
virtual void b2C(u32);
virtual void b30(u32);
};
struct IP70 {                       // vehicle-ish object reached through cCrowdObj::mp70
virtual void   p00();
virtual void p04();
virtual void p08();
virtual void p0C();
virtual void   p10();
virtual void p14();
virtual void p18();
virtual void p1C();
virtual void   p20();
virtual void p24();
virtual void p28();
virtual Float3* p2C();
virtual void   p30();
virtual void p34();
virtual void p38();
virtual void p3C();
virtual void   p40();
virtual void p44();
virtual void p48();
virtual void p4C();
virtual void   p50();
virtual void p54();
virtual void p58();
virtual void p5C();
virtual void   p60();
virtual void p64();
virtual void p68();
virtual void p6C();
virtual void   p70();
virtual void p74();
virtual void p78();
virtual void p7C();
virtual void   p80();
virtual void p84();
virtual void p88();
virtual void p8C();
virtual void   p90();
virtual void p94();
virtual void p98();
virtual void p9C();
virtual void   pA0();
virtual void pA4();
virtual void pA8();
virtual void pAC();
virtual void   pB0();
virtual void pB4();
virtual void* pB8(u32);
};
struct VehicleLike {
    u8  pad00[0xb1c];
    int m1c;                                        // +0xb1c
};
class CWorld {
public:
    void* Get(u32 id);                              // 0x00c888e0
    void  Create(u32 a, u32 b, u32 c);              // 0x00c8b130
    void  Remove(u32 a, u32 b);                     // 0x00c8ad30
    void  Measure(float* outF, int* outN);          // 0x00bd85c0
};
class CCrowdMaker {
public:
    void* Make(u32 flag);                           // 0x00bd9e80
    u8    pad04[0x192 - 0x04];
    u8    m192;                                     // +0x192
};
class cCrowdObj {
public:
    u8     pad00[0x70];
    IP70*  m70;                                     // +0x70
    u8     m74;                                     // +0x74
};
class cVehicle_s00e8_99b0 {
public:
    void ContinueAngryCrowdAttack(u32 v);           // 0x00ca8120
};
class cPlanetModel_s00e8_99b0 {
public:
    void* BuildSurfaceOrientation2();               // 0x00b7f250
};
void* __stdcall PlanetModel(Float3* a, Float3* b, Float3* c);      // 0x00b3d350
Matrix3* __cdecl Matrix3FromQuaternion(Matrix3* dst, void* q);      // 0x0059c190
void __cdecl RecordEvent4(u32 a, u32 b, float c, u32 d);            // 0x00435f40
struct MapIter { void* mpNode; void* mpBucket; };
struct SoundMap {
    u32     m00;              // +0x00
    void**  mpBucketArray;    // +0x04
    u32     mnBucketCount;    // +0x08
    u32     mnElementCount;   // +0x0c

    MapIter find(const u32& key);       // 0x00645ed0
    u32*    lookup(const u32& key);     // 0x00ad3da0
    MapIter erase(MapIter it);          // 0x01068380
    void    DoFreeNodes(void* p, u32 n);
};
struct XformMsg {
    u16    mFlags;      // +0x00
    u16    mRefs;       // +0x02
    Float3 mPos;        // +0x04
    float  mScale;      // +0x10
    Matrix3 mRot;       // +0x14

    XformMsg();                                     // 0x00434040
    __forceinline XformMsg(const Matrix3& rot)
        : mFlags(0), mRefs(0), mPos(g_f_16c4bbc, g_f_16c4bc0, g_f_16c4bc4), mScale(g_1485720), mRot(rot) {
    }                                               // inlined rotation flavour
};
namespace SP {
struct EAutoRef {
    void* mp;                       // +0x00
    void* AsPPTypeParam();          // 0x00a16f40
};
}
namespace SP {
class cCitySoundLoopView_s00e8_99b0 {
public:
    void**   mpVtbl;                // +0x00
    u8       pad04[0x0c - 0x04];
    void*    mpObject;              // +0x0c
    u8       pad10[0x34 - 0x10];
    EAutoRef mEffectRef;            // +0x34
    u8       pad38[0x44 - 0x38];

    void HandleSimulationUpdate(u32 a, u32 b);   // 0x00e899b0
};
}
namespace SP {
class cCityWallsView {
public:
    void** mpVtbl;                  // +0x00
    u8     pad04[0x34 - 0x04];
    void*  mEffect;                 // +0x34

    cCityWallsView* scalar_deleting_destructor(u8 f);   // 0x00e89c20
    void BaseDtor();
};
}
namespace SP {
class cTurretView {
public:
    void** mpVtbl;                  // +0x00
    u8     pad04[0x34 - 0x04];
    float  m34;                     // +0x34
    float  m38;                     // +0x38
    float  m3c;                     // +0x3c
    float  m40;                     // +0x40
    u32    m44;                     // +0x44
    void*  m48;                     // +0x48
    void*  m4c;                     // +0x4c

    cTurretView();                  // inlined at the allocation site
    void   BaseCtor();              // 0x00e92af0 cSpatialObjectView
};
}
namespace SP {
class CSpatialObject {
public:
    void DestroyAllEffects(u32 flag);
};
}
namespace SP {
class cBuildingView_s00e8_99b0 {
public:
    void** mpVtbl;                  // +0x00
    u8     pad04[0x88 - 0x04];

    cBuildingView_s00e8_99b0();                // 0x00e87b70
    void init(u32 param);           // 0x00e88e10
};
}
namespace SP {
class cCulturalTargetView {
public:
    void**   mpVtbl;                // +0x00
    u8       pad04[0x0c - 0x04];
    void*    mpObject;              // +0x0c
    u8       pad10[0x34 - 0x10];
    SoundMap mSoundMap;             // +0x34
    float    m44;                   // +0x44
    float    m48;                   // +0x48
    u32      m4c;                   // +0x4c
    u8       pad50[0x54 - 0x50];

    cCulturalTargetView();                          // 0x00e89d60
    ~cCulturalTargetView();                         // 0x00e89f20
    u32  FUN_00e89e50(u32 id, u32 key, Float3* p);  // 0x00e89e50
    void FUN_00e89eb0(u32 key, u8 val);             // 0x00e89eb0
    void HandleSimulationUpdate(u32 a, u32 b);      // 0x00e89f80
    void BaseCtor();
    void BaseDtor();
    void BaseUpdate(u32 a, u32 b);                  // 0x00e92ca0
};
}
namespace SP {
struct cSimTargetData {
    u8     pad000[0x100];
    IEmb   mEmb;                                    // +0x100
    u8     pad104[0x1d4 - 0x104];
    u8     m1d4;                                    // +0x1d4
    u8     pad1d5[0x1d8 - 0x1d5];
    int    m1d8;                                    // +0x1d8
    u8     pad1dc[0x20c - 0x1dc];
    float  m20c;                                    // +0x20c
    float  m210;                                    // +0x210
    int    m214;                                    // +0x214
};
}
SP::cTurretView::cTurretView() {
    BaseCtor();
    mpVtbl = vtbl_turret;
    m48 = 0;
    m4c = 0;
}
// ---- items of slice s00e899b0 end

// ---- items of slice s00e8a510 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned long long u64;
#define VC5(R, o, off, T1, a1, T2, a2, T3, a3, T4, a4, T5, a5) \
    ((R (__thiscall*)(void*, T1, T2, T3, T4, T5))VS(o, off))((void*)(o), (a1), (a2), (a3), (a4), (a5))
#define FU8(p, off)   (*(u8*)((char*)(p) + (off)))
#define FI32(p, off)  (*(int*)((char*)(p) + (off)))
#define FU32(p, off)  (*(u32*)((char*)(p) + (off)))
#define FF32(p, off)  (*(float*)((char*)(p) + (off)))
struct XformMsg_s00e8_a510 {
    u16   flags;      // +0x00  |2 = rotation, |4 = position
    u16   count;      // +0x02
    float pos[3];     // +0x04
    float scale;      // +0x10
    float rot[9];     // +0x14
    XformMsg_s00e8_a510();                           // 0x00434040
    void SetPosition(const float* v);     // 0x00571d40 (ecx = msg)
};
struct cSPTimer_s00e8_a510 {
    u64  GetElapsedTime();                // 0x00bc3190
    void Restart();                       // 0x00bc3130
};
struct cCombatant_s00e8_a510 {
    int   GetDamageState();               // 0x008e7f80
    float GetHealthFraction();            // 0x00bfc490
    bool  IsAlive();                      // 0x00bfc600 (name guess)
};
struct cSpatialObject_s00e8_a510 {
    bool  GetEffect(int id);                          // 0x00c88910
    void* FindEffect(int id);                         // 0x00c888e0
    void  SetEffectParam(int id, float f);            // 0x00c88a00
    void  SetEffectPos(int id, void* p);              // 0x00c88a30
    void  KillEffect(int id, int flag);               // 0x00c8ad30
    void  CreateEffect(int effId, int p3, int id);    // 0x00c8b130
    void  sub_b1a0(int id);                           // 0x00c8b1a0
    void  sub_b210(int id);                           // 0x00c8b210
    bool  sub_b220(int id1, int id2, int arg, int z); // 0x00c8b220
    void  sub_a020(int id, float f);                  // 0x00c8a020
};
struct cTribeHolderObj {
    char  pad[0x80];
    struct cOwnerLink* mpLink;                        // +0x80
};
struct cOwnerLink {
    char  pad[0x40];
    void* mpOwner;                                    // +0x40
    bool  Check9660();                                // 0x00d09660
    int   Check9670();                                // 0x00d09670
};
struct cHolder {
    cTribeHolderObj* Get74f0();                       // 0x00cf74f0 (ecx = holder)
};
struct cSpaceGame { char pad[0x20]; cOwnerLink* mpLink; };
struct cGameNounManager_s00e8_a510;
struct cGameDataVec { int pad0; void** mpBegin; void** mpEnd; };
struct cGameNounManager_s00e8_a510 {
    cGameDataVec* GetGameDataVector(int a, int b, int c, int d, int e);  // 0x00b21340
    void*         sub_b25f40(void* id);                                  // 0x00b25f40
    void*         sub_b25f40b(void* id);
};
struct cNounInfo { void* mpOwner; int pad[3]; int mKind; };           // [0], [0x10]
struct cCity_s00e8_a510 {
    void* GetCivilization();                          // 0x00bd9bf0
    bool  sub_bd8f30();                               // 0x00bd8f30
    bool  sub_bd7df0();                               // 0x00bd7df0
    bool  sub_bd7d60();                               // 0x00bd7d60
};
struct cBuilding_s00e8_a510 {                                    // the QI(0x0E9CB8BA) object
    int   sub_bd1080();                               // 0x00bd1080
};
struct cCamera { void GetRight(Vec3* out); };
struct cCombatantQI { bool sub_c3f540(); };      // 0x00c3f540 (ecx = QI(0xE9CB8BA) obj)         // 0x00b13900 (ret 4)
struct cEntityPtr { cNounInfo* GetInfo(); };          // 0x00ca71d0
struct cNounRef { bool sub_ac8d60(); };               // 0x00ac8d60
int            GetCurrentGameMode_s00e8_a510();                  // 0x00b5b800
cHolder*       GetHolder();                           // 0x00cf74c0
cSpaceGame*    SpaceGameGet();                        // 0x01002bd0
void*          EffectsManager();                      // 0x0067ddd0
void**         AsPPTypeParam(void** ref);             // 0x00a16f40 (ecx = ref)
cGameNounManager_s00e8_a510* NounManager();                      // 0x00b3d300
cCamera*       GetCamera();                           // 0x00b3d280
cNounRef*      sub_b3d480(void* p);                   // 0x00b3d480 (cdecl)
void*          sub_b3d240();                          // 0x00b3d240
Vec3*          normalized_safe(Vec3* out, const Vec3* in);   // 0x00449c20
Vec3*          Swarm_Normalize(Vec3* out, const Vec3* in);   // 0x006e6df0
float*         Matrix3FromQuaternion(float* out, void* q);   // 0x0059c190
float*         sub_4a9b40(float* out, void* q);              // 0x004a9b40
u32            FNV1_String8(const char* s, u32 seed, int n); // 0x00932e80
namespace SP {
void UpdateCloudTendril(class cBuildingView_s00e8_a510* v);      // 0x00e87600 (cdecl)
}
namespace SP {
class cSpatialObjectViewBase {
public:
    void HandleSimulationUpdate(int a, int b);        // 0x00e92ca0
    char pad0[0xc];                                   // vtable, ...
    cSpatialObject_s00e8_a510* mpObject;                         // +0x0c
    char pad1[0x34 - 0x10];
    void* mEffect;                                    // +0x34 (swarm effect ref)
    char pad2[0x40 - 0x38];
};
}
namespace SP {
class cBuildingView_s00e8_a510 : public cSpatialObjectViewBase {
public:
    char  pad3[0x48 - 0x40];
    float mDesiredScale;                              // +0x48
    float mCurrentScale;                              // +0x4c
    float mZoomOutScale;                              // +0x50
    int   mDamageEffectXformIndex0;                   // +0x54
    u8    mDamageFlagsSet;                            // +0x58
    char  pad4[0x60 - 0x59];
    cSPTimer_s00e8_a510 mTimer;                                  // +0x60

    void HandleSimulationUpdate(int a, int b);  // 0x00e8a510 (SP::cBuildingView::HandleSimulationUpdate)
    void UpdateSpaceCaptureEffects();                 // 0x00e89060
    void sub_e893a0();                                // 0x00e893a0
    void sub_e87cf0(int id);                          // 0x00e87cf0
    void SpawnAndPlaceDamageEffects(void* c, int a, int b);  // 0x00e89530
};
}
static cOwnerLink* TribeLink()
{
    if (!GetHolder()) return 0;
    cTribeHolderObj* o = GetHolder()->Get74f0();
    if (!o) return 0;
    cTribeHolderObj* o2 = GetHolder()->Get74f0();
    return o2->mpLink;
}
static cOwnerLink* SpaceLink()
{
    if (GetCurrentGameMode_s00e8_a510() != 0x1654c05) return 0;
    if (!SpaceGameGet()) return 0;
    if (!SpaceGameGet()->mpLink) return 0;
    return SpaceGameGet()->mpLink;
}
static bool LinkMatches(void* city, bool needNo9670)
{
    cOwnerLink* x = TribeLink();
    if (x && x->Check9660() && (!needNo9670 || !x->Check9670()) && x->mpOwner == city)
        return true;
    cOwnerLink* y = SpaceLink();
    if (y && y->Check9660() && (!needNo9670 || !y->Check9670()) && y->mpOwner == city)
        return true;
    return false;
}
// ---- items of slice s00e8a510 end

// @ 0x00e87560
void cBuildingView::ViewInit1(void* gameData)
{
    Init(gameData);
    mbFlag_58 = 0;
}

// @ 0x00e87580
void cBuildingView::ViewInit4(void* a, void* b, void* c, void* d)
{
    Init(a, b, c, d);
    mbFlag_58 = 0;
}

// @ 0x00e875b0
void cBuildingView::SetVisible(u8 b)
{
    mbVisible_38 = b;
    void* o = GetModel();
    if (b) {
        if (o) {
            void* p = *(void**)o;
            VC2(void, p, 0x16c, void*, o, int, 1);
        }
    } else {
        if (o) {
            void* p = *(void**)o;
            VC2(void, p, 0x16c, void*, o, int, 0);
        }
    }
}

// @ 0x00e87600
namespace SP {
void UpdateCloudTendril(cSpatialObjectView * view)
{
    void* obj = FUN_00fc7e50(view);
    if (obj == 0)
        return;

    void* building = (void*)VC1(void*, obj, 0xb8, u32, 0xe9cb8ba);
    bool alive;
    void* body;
    if (building != 0) {
        if (VC1(void*, building, 0xc, u32, 0x1a55e4d) == 0)
            return;
        alive = FUN_00bfc600((char*)building + 0x120);
        body = (void*)VC0(void*, building, 0x84);
    } else {
        building = (void*)VC1(void*, obj, 0xb8, u32, 0x436f315);
        if (building == 0)
            return;
        alive = FUN_00bfc600((char*)building + 0x588);
        body = FUN_00bce5c0(building);
    }

    void* span = body;
    bool ok = FUN_00bd8240(span);

    float length = 0.0f;
    int flag;
    if (alive && ok)
        flag = 1;
    else
        flag = 0;
    FUN_00c8b220(0x487eb45b, 0x5de3055, flag, &length);
    if (length == 0.0f)
        return;

    float dir[3];
    FUN_00bd9480(span, dir);

    float inv = 1.0f / sqrtf(dir[0] * dir[0] + (dir[1] * dir[1] + dir[2] * dir[2]) + kTiny);
    dir[0] = dir[0] * inv * kForty + dir[0];
    dir[1] = dir[1] * inv * kForty + dir[1];
    dir[2] = dir[2] * inv * kForty + dir[2];

    float* ext = (float*)VC0(void*, obj, 0x6c);
    float centre[3];
    centre[0] = (ext[3] + ext[0]) * kHalf;
    centre[1] = (ext[1] + ext[4]) * kHalf;
    centre[2] = (ext[2] + ext[5]) * kHalf;

    Vec3 pts[10];
    float stepX = (centre[0] - dir[0]) * kTenth;
    float stepY = (centre[1] - dir[1]) * kTenth;
    float stepZ = (centre[2] - dir[2]) * kTenth;
    for (int i = 0; i < 10; i++) {
        pts[i].x = dir[0] + stepX * (float)i;
        pts[i].y = dir[1] + stepY * (float)i;
        pts[i].z = dir[2] + stepZ * (float)i;
    }
    VC3(void, obj, 0x44, int, 0xd, float*, (float*)pts, int, 0x1e);
}
}  // namespace SP

// @ 0x00e87b70
cBuildingView::cBuildingView()
{
    mpEffect_34 = 0;
    float one = kOne;
    mScale_3c = one;
    mScale_40 = one;
    mState_38 = 0;
    mScale_44 = kOneAndAHalf;
    mbFlag_58 = 0;
    mTimer.Construct();
    mXformIndices[0] = mXformIndices[1] = mXformIndices[2] = mXformIndices[3] = -1;
    mpEffect_80 = 0;
    mpEffect_84 = 0;
}

// @ 0x00e87be0
cBuildingView::~cBuildingView()
{
    if (mpEffect_34 != 0) {
        if (mpObject == 0 || VC1(void*, mpObject, 0xb8, u32, 0x70704db) != 0)
            VC1(void, mpEffect_34, 0xc, int, 0);
        if (mpEffect_34 != 0) {
            mpEffect_34 = 0;
            VC0(void, mpEffect_34, 4);
        }
    }

    if (mpEffect_80 != 0) {
        VC1(void, mpEffect_80, 0xc, int, 1);
        if (mpEffect_80 != 0) {
            mpEffect_80 = 0;
            VC0(void, mpEffect_80, 4);
        }
        MinimapHost* host = (MinimapHost*)FUN_010666a0();
        ((cMinimapWin*)host->GetPanel())->RemoveIcon(this, 1, 0);
    }

    if (mpEffect_84 != 0) {
        VC1(void, mpEffect_84, 0xc, int, 0);
        if (mpEffect_84 != 0) {
            mpEffect_84 = 0;
            VC0(void, mpEffect_84, 4);
        }
    }

    cSpatialObjectView_DestroyAllEffects(mpObject, 1);
    if (mpEffect_84 != 0)
        VC0(void, mpEffect_84, 4);
    if (mpEffect_80 != 0)
        VC0(void, mpEffect_80, 4);
    mTimer.Destruct();
    if (mpEffect_34 != 0)
        VC0(void, mpEffect_34, 4);
}

// @ 0x00e88c30
cSPUIMeter* cCityFeedbackView::UpdateLoyaltyBar(cSPUIMeter* p, char bShow, u32 hdr)
{
    if (bShow != 0) {
        if (p != 0)
            return p;

        void* mem = operator_new(0x50, &g_allocTag_013f6b3c, 0, 0, 0, 0);
        cSPUIMeter* np;
        if (mem != 0)
            np = ((cSPUIMeter*)mem)->Init(hdr, 0x3ffb28c, 0x4d428c1, L"CivConversionBar", 0xe9f70df9);
        else
            np = 0;

        np->Func_e06c50(mpObject);
        cCityHall* hall = mpObject->GetCityHall();
        np->Func_e06cf0(hall != 0 ? hall->Func0c(0x1186577) : 0);
        return np;
    }

    if (p != 0) {
        p->Shutdown(1);
        p = 0;
    }
    return p;
}

// @ 0x00e88ce0
void cCityFeedbackView::HandleSimulationUpdate(int, int)
{
    if (mpObject == 0)
        return;

    int state1 = mpObject->mField754;
    mMeter1 = UpdateLoyaltyBar(mMeter1.mpObj, (state1 != -1), 1);
    mMeter2 = UpdateLoyaltyBar(mMeter2.mpObj,
                               (mpObject->mField74c != -1) && (100.0f > mpObject->mField748), 0);
    mMeter3 = UpdateLoyaltyBar(mMeter3.mpObj,
                               (mpObject->mField75c != -1) && !mpObject->mSub.Func58(), 2);
}

// @ 0x00e88e10
void cBuildingView_s00e8_8c30::ConfigureBuildingView(cBuildingData* p2)
{
    cBuildingData* p = 0;
    if (p2 != 0)
        p = (cBuildingData*)VC1(void*, p2, 0xc, u32, 0xe9cb8ba);

    if (GetCurrentGameMode() == &g_gameModeCity_1654c10) {
        mColor = g_cityColor_15a87b4;
    } else {
        Vec3* w = (Vec3*)VC0(void*, p, 0x84);
        Vec3* q = (Vec3*)FUN_00bd99e0(w);
        mColor = *q;
    }

    Vec3  local;
    Vec3* ref;
    if (VC0(char, &p->mSub, 0x90) == 0) {
        ref = (Vec3*)&mField24;
    } else {
        Vec3* w = (Vec3*)VC0(void*, &p->mSub, 0x98);
        local = *w;
        ref = &local;
    }
    VC4(void, this, 0x28, void*, p2, void*, GonzagoModelWorld(), void*, ref, void*, &mColor);

    u32 kind = VC0(u32, p2, 0x38);
    if (mpObject != 0) {
        cCombatant* c = (cCombatant*)VC1(void*, mpObject, 0xb8, u32, 0x13f94d4);
        if (c != 0 && c->GetDamageState() == 2) {
            Vec3* w = (Vec3*)VC0(void*, mpObject, 0x98);
            Vec3  key = *w;
            SetKeyKind(&key, 0x7e, 0);
            VC1(void, mpObject, 0x94, void*, &key);
            cXform* x = (cXform*)VC0(void*, this, 0x2c);
            x->mField4c = 0.4f;
            x->mField50 = 0.4f;
            x->mField54 = 0.4f;
        }
    }

    void* prop = 0;
    void* pm = PropertyManager();
    if (VC2(char, pm, 0x30, u32, 0xb6a5c63d, void**, &prop) != 0) {
        if (kind == 0xecade42 || kind == 0xff10521) {
            if (prop != 0) {
                void* out = 0;
                if (VC2(char, prop, 0x24, u32, 0x1ca5e86, void**, &out) != 0
                    && ((PropRef*)out)->mKind == 0xd)
                    mScale_44 = *((PropRef*)out)->GetFloat();
            }
        } else if (kind == 0x1007ae63) {
            GetPropertyT_int(prop, 0x1c38187, (int*)&mScale_44);
        } else {
            GetPropertyT_int(prop, 0x1ca5e8e, (int*)&mScale_44);
        }
    }
    mScale_40 = 1.0f;
    mScale_3c = 1.0f;
    mTimer.Restart();
    if (prop != 0)
        VC0(void, prop, 4);
}

// @ 0x00e89770
void* cCityTerritory::deleting_dtor(char flag)
{
    *(void**)this = &vtbl_cCityTerritory;
    ((cSpatialObject*)mpObject)->DestroyAllEffects(1);
    ((cSpatialObjectView_s00e8_8c30*)this)->Dtor();
    if (flag & 1)
        operator_delete_array(this);
    return this;
}

// @ 0x00e89950
void* cCitySoundLoopView::deleting_dtor(char flag)
{
    void* p = mpEffect_34;
    *(void**)this = &vtbl_cCitySoundLoopView;
    if (p != 0) {
        VC1(void, p, 0xc, int, 1);
        p = mpEffect_34;
        if (p != 0) {
            mpEffect_34 = 0;
            VC0(void, p, 4);
        }
    }
    if (mpEffect_34 != 0)
        VC0(void, mpEffect_34, 4);
    ((cSpatialObjectView_s00e8_8c30*)this)->Dtor();
    if (flag & 1)
        operator_delete_array(this);
    return this;
}

// @ 0x00e899b0
void SP::cCitySoundLoopView_s00e8_99b0::HandleSimulationUpdate(u32, u32)
{
    void* obj = mpObject;
    if (obj == 0)
        return;

    IObj* fx = (IObj*)((IObj*)obj)->vB8(0x903c3ea3);
    if (fx == 0)
        return;

    fx->v00();

    EAutoRef* ref = &mEffectRef;
    if (ref->mp == 0) {
        switch (fx->v5C()) {
        case 1:
            ((IObj*)EffectsManagerPtr())->v2C(0xf78fa47a, 0, ref->AsPPTypeParam());
            break;
        case 2:
            ((IObj*)EffectsManagerPtr())->v2C(0xced4a9a6, 0, ref->AsPPTypeParam());
            break;
        case 3:
            ((IObj*)EffectsManagerPtr())->v2C(0xf1910322, 0, ref->AsPPTypeParam());
            break;
        case 4:
            ((IObj*)EffectsManagerPtr())->v2C(0xbd61f72b, 0, ref->AsPPTypeParam());
            break;
        case 5:
            ((IObj*)EffectsManagerPtr())->v2C(0xef2700b6, 0, ref->AsPPTypeParam());
            break;
        case 6:
            ((IObj*)EffectsManagerPtr())->v2C(0x62019f3a, 0, ref->AsPPTypeParam());
            break;
        case 7:
            ((IObj*)EffectsManagerPtr())->v2C(0x60d7cad6, 0, ref->AsPPTypeParam());
            break;
        }

        if (ref->mp != 0) {
            XformMsg msg;
            msg.mPos = *(Float3*)fx->v58();
            msg.mFlags |= 4;
            msg.mRefs++;
            ((IObj*)ref->mp)->v18(&msg);
            ((IObj*)ref->mp)->v08(0);
        }
    } else {
        XformMsg msg(g_mtx_16c4b98);
        msg.mPos = *(Float3*)fx->v58();
        msg.mFlags |= 4;
        msg.mRefs++;
        ((IObj*)ref->mp)->v18(&msg);
    }

    fx->v04();
}

// @ 0x00e89c20
SP::cCityWallsView* SP::cCityWallsView::scalar_deleting_destructor(u8 f)
{
    *(void* volatile*)&mpVtbl = (void*)vtbl_citywalls;
    void* eff = *(void* volatile*)&mEffect;
    if (eff != 0)
        ((IObj*)eff)->v04();
    BaseDtor();
    if (f & 1)
        operator delete(this);
    return this;
}

// @ 0x00e89c60
SP::cTurretView* __stdcall FUN_00e89c60(u32 param)
{
    SP::cTurretView* v = new ("Simulator/cTurretView", 0, 0, 0, 0) SP::cTurretView();
    ((IObj*)v)->v24(param);
    v->m44 = 0;
    v->m34 = 0.0f;
    v->m38 = 0.0f;
    v->m3c = 0.0f;
    *(volatile float*)&v->m40 = g_1485720;
    void* o48 = *(void* volatile*)&v->m48;
    if (o48 != 0) {
        v->m48 = 0;
        ((IObj*)o48)->v04();
    }
    if (v->m4c != 0) {
        void* o = v->m4c;
        v->m4c = 0;
        ((IObj*)o)->v04();
    }
    return v;
}

// @ 0x00e89d10
SP::cBuildingView_s00e8_99b0* __stdcall FUN_00e89d10(u32 param)
{
    SP::cBuildingView_s00e8_99b0* v = new ("Simulator/cBuildingView", 0, 0, 0, 0) SP::cBuildingView_s00e8_99b0();
    v->init(param);
    return v;
}

// @ 0x00e89d60
SP::cCulturalTargetView::cCulturalTargetView()
{
    BaseCtor();
    float f44 = g_1485720;
    *(void* volatile*)&mpVtbl = (void*)vtbl_cultural;
    *(volatile float*)&m44 = f44;
    *(volatile float*)&m48 = g_1470f1c;
    u32 zero = 0;
    *(volatile u32*)&mSoundMap.mnElementCount = zero;
    *(volatile u32*)&m4c = zero;
    *(volatile u32*)&mSoundMap.mnBucketCount = 1;
    *(void* volatile*)&mSoundMap.mpBucketArray = (void*)&g_bucketSentinel;
}

// @ 0x00e89db0
SP::cCulturalTargetView* __stdcall FUN_00e89db0(u32 param)
{
    SP::cCulturalTargetView* v = new ("Simulator/cCulturalTargetView", 0, 0, 0, 0) SP::cCulturalTargetView();
    ((IObj*)v)->v24(param);
    return v;
}

// @ 0x00e89e50
u32 SP::cCulturalTargetView::FUN_00e89e50(u32 id, u32 key, Float3* p)
{
    IObj* sys = (IObj*)GetSystemAT();
    u32 snd;
    if (sys != 0)
        snd = sys->v20();
    else
        snd = 0;
    *mSoundMap.lookup(key) = snd;
    Start3dSoundByName(id, snd, p->x, p->y, p->z);
    return snd;
}

// @ 0x00e89eb0
void SP::cCulturalTargetView::FUN_00e89eb0(u32 key, u8 val)
{
    SoundMap* map = &mSoundMap;
    MapIter it = map->find(key);
    if (it.mpNode != map->mpBucketArray[map->mnBucketCount]) {
        u32* slot = map->lookup(key);
        FUN_00572020(*slot, val);
        it = map->erase(it);
    }
}

// @ 0x00e89f20
SP::cCulturalTargetView::~cCulturalTargetView()
{
    mpVtbl = vtbl_cultural;
    ((CSpatialObject*)mpObject)->DestroyAllEffects(1);
    FUN_00e89eb0(0x3f69195, 1);
    SoundMap* map = &mSoundMap;
    map->DoFreeNodes(map->mpBucketArray, map->mnBucketCount);
    map->mnElementCount = 0;
    if (map->mnBucketCount > 1)
        operator delete[](map->mpBucketArray);
    BaseDtor();
}

// @ 0x00e89f80
void SP::cCulturalTargetView::HandleSimulationUpdate(u32 a, u32 b)
{
    void* obj = mpObject;
    ITarget* target = 0;
    if (obj != 0)
        target = (ITarget*)((IObj*)obj)->vB8(0x3d5c477);

    BaseUpdate(a, b);
    ((CWorld*)obj)->Get(0x3df43f4);
    ((CWorld*)obj)->Get(0x3df43f5);

    cSimTargetData* td = (cSimTargetData*)target;
    int flag = 2;
    if (td->m1d8 == 2) {
        if (fabs((double)td->m20c) < (double)g_14861d0) {
            flag = !(fabs((double)td->m20c) > fabs((double)td->m210));
            target->a4C();
        }

        MapIter it = mSoundMap.find(0x3f69195);
        if (it.mpNode == mSoundMap.mpBucketArray[mSoundMap.mnBucketCount]) {
            Float3* p = td->mEmb.e2C();
            FUN_00e89e50(0x2873c7ee, 0x3f69195, p);
        }

        it = mSoundMap.find(0x3f69195);
        if (it.mpNode != mSoundMap.mpBucketArray[mSoundMap.mnBucketCount]) {
            float fv = 0.0f;
            int   n = 0;
            ((CWorld*)obj)->Measure(&fv, &n);
            float v;
            if (n > 0)
                v = (float)ceil((double)((fv * 3.0f) / (float)n));
            else
                v = 1.0f;
            if (v < 1.0f)
                v = 1.0f;
            if (v > 3.0f)
                v = 3.0f;
            float dmg = (flag == 2) ? 1.0f : g_1470f1c;
            u32 key = 0x3f69195;
            RecordEvent4(*mSoundMap.lookup(key), 0x187ffedd, v, 0);
            RecordEvent4(*mSoundMap.lookup(key), 0xffb10599, dmg, 0);
        }
    } else {
        FUN_00e89eb0(0x3f69195, 0);
    }

    u32 b1d4 = td->m1d4;
    void* w = target->a30();
    void* w2 = (w != 0) ? ((IObj0C*)w)->x0C(0xee9b2232) : 0;
    cCrowdObj* crowd = (cCrowdObj*)((CCrowdMaker*)w2)->Make(b1d4);
    IP70* p70 = crowd->m70;
    void* veh = (p70 != 0) ? p70->pB8(0x137e8e0) : 0;
    u8 proceed = crowd->m74;
    bool active = (td->m214 > 0) && (p70 != 0);

    void* eff = ((CWorld*)obj)->Get(0x4af5ae2);
    if (!active) {
        if (eff != 0)
            ((CWorld*)obj)->Remove(0x4af5ae2, 1);
        return;
    }
    if (eff == 0) {
        u32 id = 0x251bc7a8;
        int t = ((VehicleLike*)veh)->m1c;
        if (t == 1)
            id = 0xa1185324;
        else if (t == 2)
            id = 0xa8eb404d;
        ((CWorld*)obj)->Create(id, 0, 0x4af5ae2);
        eff = ((CWorld*)obj)->Get(0x4af5ae2);
        if (eff == 0)
            return;
        proceed = 1;
    }

    void* w3 = target->a30();
    void* w4 = (w3 != 0) ? ((IObj0C*)w3)->x0C(0xee9b2232) : 0;
    u32 on = (((CCrowdMaker*)w4)->m192 != 0) ? 1 : 0;
    ((IEffect*)eff)->b2C(on);
    ((IEffect*)eff)->b30(on);

    if (proceed == 0)
        return;

    ((cVehicle_s00e8_99b0*)veh)->ContinueAngryCrowdAttack(1);

    Float3* pa = p70->p2C();
    Float3 dir;
    td->mEmb.e5C(&dir);
    float ox = dir.x * g_1486344;
    float oy = dir.y * g_1486344;
    float oz = dir.z * g_1486344;
    Float3* pb = td->mEmb.e2C();
    Float3 pos(pb->x + ox, pb->y + oy, pb->z + oz);

    XformMsg msg(g_mtx_16c4b98);
    msg.mFlags |= 4;
    msg.mPos = pos;
    msg.mRefs++;

    Float3 d(pa->x - pos.x, pa->y - pos.y, pa->z - pos.z);
    cPlanetModel_s00e8_99b0* pm = (cPlanetModel_s00e8_99b0*)PlanetModel(&dir, &pos, &d);
    void* quat = pm->BuildSurfaceOrientation2();
    Matrix3 mtx;
    Matrix3FromQuaternion(&mtx, quat);
    msg.mRot = mtx;
    msg.mFlags |= 2;
    msg.mRefs++;
    ((IEffect*)eff)->b18(&msg);
}

// @ 0x00e8a510
void SP::cBuildingView_s00e8_a510::HandleSimulationUpdate(int a, int b)
{
    char* R;          // object returned by this->vtbl[0x2c] (rendering-state block)
    char* C;          // QI(0x0E9CB8BA) result on mpObject
    char* H;          // C->vtbl[0x84]() (owning city)
    bool  zFlag;      // [esp+0x1a]
    bool  isSpace;    // [esp+0x1b]
    bool  hasG;       // first tribe chain (bl at 0xa828)

    cSpatialObjectViewBase::HandleSimulationUpdate(a, b);
    R = (char*)VC0(void*, this, 0x2c);
    if (!R) return;

    if (!mDamageFlagsSet && ((FU32(R, 4) >> 0xe) & 1) && !((FU32(R, 4) >> 0x12) & 1)) {
        void* part = *(void**)R;
        int n = VC1(int, part, 0x64, void*, R);
        for (int i = 0; i < n; ++i)
            VC5(void, part, 0x70, void*, R, int, 0xa502dc0b, int, 0, float, 0.0f, int, i);
        mDamageFlagsSet = 1;
    }

    if (mpObject)
        C = (char*)VC1(void*, mpObject, 0xb8, int, 0xe9cb8ba);
    else
        C = 0;

    if (GetCurrentGameMode_s00e8_a510() == 0x1654c05) {
        UpdateSpaceCaptureEffects();
        sub_e893a0();
    }

    zFlag = false;
    if (mpObject) {
        cCombatant_s00e8_a510* cb = (cCombatant_s00e8_a510*)VC1(void*, mpObject, 0xb8, void*, (void*)0x13f94d4);
        if (cb) {
            int ds = cb->GetDamageState();
            if (ds == 0) {
                if (mEffect) {
                    VC1(void, mEffect, 0xc, int, 0);
                    void* e = mEffect;
                    mEffect = 0;
                    if (e) VC0(void, e, 4);
                }
            } else if (ds == 2) {
                zFlag = true;
                u32* pp = (u32*)VC0(void*, mpObject, 0x98);
                u32 key[3];
                key[0] = pp[0]; key[1] = pp[1]; key[2] = pp[2];
                FU32(R, 0x4c) = 0x3ecccccd;
                FU32(R, 0x50) = 0x3ecccccd;
                FU32(R, 0x54) = 0x3ecccccd;
                bool sticky = ((cCombatantQI*)C)->sub_c3f540();
                if (!sticky && mEffect == 0 && key[0] != 0 && (key[2] & 0xff00) != 0x7e00) {
                    void* em = EffectsManager();
                    VC3(void, em, 0x2c, int, 0xee9148d8, int, 0, void**, AsPPTypeParam(&mEffect));
                    if (mEffect) {
                        u32 buf[2];
                        buf[0] = key[0];
                        buf[1] = key[2];
                        VC3(void, mEffect, 0x48, int, 6, void*, buf, int, 2);
                        XformMsg_s00e8_a510 msg;
                        msg.SetPosition((const float*)VC0(void*, mpObject, 0x2c));
                        msg.scale = VC0(float, mpObject, 0x34);
                        msg.count++;
                        float tmp[9];
                        float* m = Matrix3FromQuaternion(tmp, VC0(void*, mpObject, 0x30));
                        for (int i = 0; i < 9; ++i) msg.rot[i] = m[i];
                        msg.flags |= 2;
                        msg.count++;
                        VC1(void, mEffect, 0x18, void*, &msg);
                        VC1(void, mEffect, 8, int, 0);
                    }
                    SetKeyKind(key, 0x7e, 0);
                    VC1(void, mpObject, 0x94, void*, key);
                }
            }
        }
    }

    if (!VC0(u8, this, 0x1c)) return;

    isSpace = (GetCurrentGameMode_s00e8_a510() == 0x1654c05);

    {
        cOwnerLink* l = TribeLink();
        hasG = (l != 0) && l->Check9660();
    }

    if (GetCurrentGameMode_s00e8_a510() != 0x1654c10) {
        if (FU8(mpObject, 0x6e)) {
            FU32(R, 4) |= 8;
            FU8(R, 0x5c) = 1;
        } else if (VC0(u8, mpObject, 0x24)
                   && (!isSpace || VC0(u8, C + 0x34, 0x58))
                   && (!hasG || VC0(u8, C + 0x1e8, 0x10))) {
            FU32(R, 4) |= 8;
            FU8(R, 0x5c) = 2;
        } else {
            FU32(R, 4) &= 0xfffffff7;
        }
    }

    float health = ((cCombatant_s00e8_a510*)(C + 0x120))->GetHealthFraction();
    bool bl = false, fxB = false, fxC = false, fxD = false;
    if (zFlag || health >= 0.8f) {
        bl = true; fxD = true;
    } else if (health < 0.5f) {
        if (health >= 0.0f) { bl = true; fxC = true; }
    } else {
        fxB = true; fxD = true;
    }

    if ((FI32(C, 0x30c) - FI32(C, 0x308)) / 0x38 == 0) {
        if (bl) {
            mpObject->KillEffect(0x49b925c, 0);
            sub_e87cf0(0x4cad362);
        }
        if (fxD) {
            mpObject->KillEffect(0x49b925d, 0);
            sub_e87cf0(0x4cad3a8);
        }
        if (fxB && !mpObject->GetEffect(0x49b925c))
            mpObject->CreateEffect(0x65c15577, 0, 0x49b925c);
        if (fxC && !mpObject->GetEffect(0x49b925d))
            mpObject->CreateEffect(0x97c0b9bf, 0, 0x49b925d);
    } else {
        if (FU8(C, 0x2f0)) {
            fxD = true;
            bl = true;
            FU8(C, 0x2f0) = 0;
        }
        if (bl) sub_e87cf0(0x4cad362);
        if (fxD) sub_e87cf0(0x4cad3a8);
        if (bl && fxD) {
            FU32(this, 0x48) = 0xffffffff;
            FU32(this, 0x4c) = 0xffffffff;
            FU32(this, 0x50) = 0xffffffff;
            mDamageEffectXformIndex0 = -1;
        }
        if (fxB) SpawnAndPlaceDamageEffects(C, 0x4cad362, 0x4cb1631);
        if (fxC) SpawnAndPlaceDamageEffects(C, 0x4cad3a8, 0x4cb1632);
    }

    H = (char*)VC0(void*, C, 0x84);
    bool r1 = false, r2 = false;
    if (GetCurrentGameMode_s00e8_a510() != 0x1654c10) {
        r1 = LinkMatches(H, true);
        // second chain has no Check9670 requirement
        r2 = LinkMatches(H, false);
    }

    if (VC1(int, C, 0xc, int, 0x1007ae63) != 0) {
        int d = FI32(C, 0x298) - FI32(C, 0x29c);
        if (d > 0)
            mpObject->sub_b220(0x20186eab, 0xf40652ad, r1, 0);
        else if (d < 0)
            mpObject->sub_b220(0x6794fedd, 0xf40652ae, r1, 0);
    } else {
        bool v1 = r1 && FU8(C, 0x289) && VC1(int, C, 0xc, int, 0x1a55e4d) != 0;
        mpObject->sub_b220(0x20186eab, 0xf40652ad, v1, 0);
        bool v2 = r1 && FU8(C, 0x289) && VC1(int, C, 0xc, int, 0xecade42) != 0;
        mpObject->sub_b220(0x6794fedd, 0xf40652ae, v2, 0);
    }

    cCombatant_s00e8_a510* cmb = (cCombatant_s00e8_a510*)(C + 0x120);
    if (VC1(int, C, 0xc, int, 0x1a55e4d) != 0) {
        bool v1 = r1 && !FU8(C, 0x289) && cmb->GetDamageState() != 2 && !FU8(C, 0xa6);
        mpObject->sub_b220(0x70f577f7, 0x13b59ba2, v1, 0);
        bool v2 = !r2 && !FU8(C, 0x289) && cmb->GetDamageState() != 2;
        if (mpObject->sub_b220(0xd84031d7, 0x13bdd20b, v2, 0))
            mpObject->SetEffectParam(0x13bdd20b, 512.0f);
    } else if (VC1(int, C, 0xc, int, 0xecade42) != 0) {
        bool v1 = r1 && !FU8(C, 0x289) && cmb->GetDamageState() != 2 && !FU8(C, 0xa6);
        mpObject->sub_b220(0xa65b1464, 0x13b59ba2, v1, 0);
        bool v2 = !r2 && !FU8(C, 0x289) && cmb->GetDamageState() != 2;
        if (mpObject->sub_b220(0x706665c4, 0x13bdd20b, v2, 0))
            mpObject->SetEffectParam(0x13bdd20b, 512.0f);
    } else if (VC1(int, C, 0xc, int, 0xff10521) != 0) {
        bool v1 = r1 && !FU8(C, 0x289) && cmb->GetDamageState() != 2 && !FU8(C, 0xa6);
        mpObject->sub_b220(0xa8b22b41, 0x13b59ba2, v1, 0);
        bool v2 = !r2 && !FU8(C, 0x289) && cmb->GetDamageState() != 2;
        if (mpObject->sub_b220(0xec727821, 0x13bdd20b, v2, 0))
            mpObject->SetEffectParam(0x13bdd20b, 512.0f);
    }

    if (VC1(int, C, 0xc, int, 0x1a55e4d) != 0) {
        cCity_s00e8_a510* city = (cCity_s00e8_a510*)H;
        if (!zFlag && !VC0(u8, C, 0x2c) && FU8(C, 0x289) && !VC0(u8, city, 0x2c)
            && city->sub_bd8f30())
            zFlag = true;
        else
            zFlag = false;
        void* sh = mpObject->FindEffect(0x4acb33b);
        if (zFlag) {
            bool go = true;
            if (!sh) {
                void* civ = city->GetCivilization();
                if (!civ) {
                    go = false;
                } else {
                    float v[3];
                    v[0] = FF32(civ, 0xc4); v[1] = FF32(civ, 0xc8); v[2] = FF32(civ, 0xcc);
                    mpObject->CreateEffect(0xf020ce6, 0, 0x4acb33b);
                    sh = mpObject->FindEffect(0x4acb33b);
                    if (!sh) go = false;
                    else VC3(void, sh, 0x44, int, 5, void*, v, int, 3);
                }
            }
            if (go) {
                u32 fl = FU32(C, 0x84);
                if (!(fl & 0x10) || (fl & 0x20)) {
                    XformMsg_s00e8_a510 msg;
                    float tv[3];
                    float* bb = (float*)VC1(void*, C + 0x34, 0x6c, void*, tv);
                    msg.flags |= 4;
                    msg.count++;
                    float cx = (bb[0] + bb[3]) * 0.5f;
                    float cy = (bb[1] + bb[4]) * 0.5f;
                    float cz = (bb[2] + bb[5]) * 0.5f;
                    msg.pos[0] = cx; msg.pos[1] = cy; msg.pos[2] = cz;
                    float tmp[9];
                    float* m = sub_4a9b40(tmp, VC0(void*, C + 0x34, 0x30));
                    for (int i = 0; i < 9; ++i) msg.rot[i] = m[i];
                    msg.flags |= 2;
                    msg.count++;
                    VC1(void, sh, 0x18, void*, &msg);
                }
            }
        } else if (sh) {
            mpObject->KillEffect(0x4acb33b, 1);
        }
    }

    {
        bool arg = (FI32(C, 0x290) > 0) || ((cCombatant_s00e8_a510*)(C + 0x120))->IsAlive();
        if (mpObject->sub_b220(0x39ff8e9e, 0x4acb33c, arg, 0)) {
            cGameNounManager_s00e8_a510* nm = NounManager();
            cGameDataVec* vec = nm->GetGameDataVector(0xcd7d10, 0xd3d420, 0xae72d0, 0xb1e500, 0x18c6de8);
            int count = (int)(vec->mpEnd - vec->mpBegin);
            for (int i = 0; i < count; ++i) {
                void* p = vec->mpBegin[i];
                cNounInfo* info = ((cEntityPtr*)p)->GetInfo();
                if (info->mKind == 1 && info->mpOwner == (void*)C) {
                    void* id = VC0(void*, p, 0x4c);
                    char* r = (char*)NounManager()->sub_b25f40(id);
                    if (r) {
                        mpObject->SetEffectPos(0x4acb33c, r + 0xc4);
                        break;
                    }
                }
            }
        }
    }

    UpdateCloudTendril(this);

    if (!isSpace) {
        while (((cBuilding_s00e8_a510*)C)->sub_bd1080()) {}
        if (VC0(int, C, 0x20) == 0x18ea1eb && GetCurrentGameMode_s00e8_a510() != 0x1654c10) {
            bool facing = false;
            if (GetCamera()) {
                Vec3 camv;
                GetCamera()->GetRight(&camv);
                Vec3 t;
                Vec3* n = normalized_safe(&t, (const Vec3*)VC0(void*, C + 0x34, 0x2c));
                facing = ((n->y * camv.y + n->z * camv.z) + n->x * camv.x) > 0.0f;
            }
            cCity_s00e8_a510* city = (cCity_s00e8_a510*)H;
            mpObject->sub_b220(0x3e28b6b5, 0x2ca2a9a, city->sub_bd7df0() && !facing, 0);
            mpObject->sub_b220(0xa6e7c82f, 0x2ca38bb, city->sub_bd7d60() && !facing, 0);
        }
    }

    {
        bool arg = (FU32(C, 0x84) & 0x800) == 0x800;
        if (mpObject->sub_b220(0x56192017, 0x30e8811, arg, 0)) {
            mpObject->SetEffectParam(0x30e8811, 512.0f);
            float f = VC0(float, C + 0x34, 0x74);
            mpObject->sub_a020(0x30e8811, f);
        }
    }
    FU32(C, 0x84) &= 0xfffff7ff;
    char* sub34 = C + 0x34;

    if (isSpace && VC1(int, C, 0xc, int, 0x1007ae63) != 0) {
        bool done = false;
        void* eff = 0;
        if (FU8(H, 0x2fc)) {
            if (mpObject->GetEffect(0x47601624)) done = true;
            else {
                mpObject->sub_b1a0(0x47601624);
                mpObject->SetEffectParam(0x47601624, 1000.0f);
                eff = mpObject->FindEffect(0x47601624);
                if (!eff) done = true;
            }
        } else {
            if (!mpObject->GetEffect(0x47601624)) done = true;
            else {
                mpObject->KillEffect(0x47601624, 1);
                mpObject->sub_b210(0x3f056974);
                mpObject->SetEffectParam(0x3f056974, 1000.0f);
                eff = mpObject->FindEffect(0x3f056974);
                if (!eff) done = true;
            }
        }
        if (!done) {
            XformMsg_s00e8_a510 msg;
            const float* pc = (const float*)VC0(void*, sub34, 0x2c);
            char* hs = H + 0x120;
            const float* p2 = (const float*)VC0(void*, hs, 0x2c);
            Vec3 d;
            d.x = p2[0] - pc[0];
            d.y = p2[1] - pc[1];
            d.z = p2[2] - pc[2];
            float r = FF32(H, 0x300);
            Vec3 tmpn;
            Vec3* nn = Swarm_Normalize(&tmpn, (const Vec3*)VC0(void*, hs, 0x2c));
            float x = r * nn->x + d.x;
            float y = nn->y * r + d.y;
            float z = nn->z * r + d.z;
            msg.pos[0] = x; msg.pos[1] = y; msg.pos[2] = z;
            msg.flags |= 4;
            msg.count++;
            VC1(void, eff, 0x14, void*, &msg);
        }
    }

    {
        u32 h = FNV1_String8("SG_ufo_static_cling_stunned_building", 0x811c9dc5, 1);
        bool arg = ((cCombatant_s00e8_a510*)(C + 0x120))->IsAlive();
        mpObject->sub_b220(h, 0x5f8d750, arg, 0);
    }

    if (VC0(int, C, 0x20) == 0x18ea2cc) {
        void* owner = VC0(void*, C, 0x84);
        if (sub_b3d480(owner)->sub_ac8d60()) {
            int v = FI32(C, 0x294);
            int cap = 0x4b0;
            int* sel = (v > 0x4b0) ? &cap : &v;
            u64 elapsed = mTimer.GetElapsedTime();
            long long thresh = (long long)(((0x4b1 - *sel) * 4000) / 0x4b0 + 2000);
            if (elapsed > (u64)thresh) {
                const float* p = (const float*)VC0(void*, sub34, 0x2c);
                Vec3 v1;
                v1.x = p[0]; v1.y = p[1]; v1.z = p[2];
                const float* q = (const float*)VC0(void*, sub34, 0x68);
                float len = q[5] - q[2];
                Vec3 t;
                Vec3* n = normalized_safe(&t, &v1);
                Vec3 pos;
                pos.x = len * n->x + v1.x;
                pos.y = n->y * len + v1.y;
                pos.z = n->z * len + v1.z;
                void* mgr = sub_b3d240();
                Vec3 out;
                void* r5c = VC1(void*, sub34, 0x5c, void*, &out);
                VC3(void, mgr, 0x60, int, 0x6257fd5 + (isSpace ? 1 : 0), void*, &pos, void*, r5c);
                mTimer.Restart();
            }
        }
    }
}
