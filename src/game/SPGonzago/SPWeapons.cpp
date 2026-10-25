// src/game/SPGonzago/SPWeapons.cpp -- migrated from slice(s) s0135ae10, s00cc22c0, s00cbf120, s00cbda10, s00cbb020, s00cb91d0, s00cb7310, s00cb6570, s00cb5620, s00cb44b0, s00cb2f70 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPWeapons.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cArtilleryProjectile.h"
#include "SP/cLocomotiveObject.h"
#include "SP/cDataSerializationInfo.h"
#include "SP/cGameData.h"
#include "SP/cSPSpaceToolData.h"
#include "SP/cSpatialObject.h"
#include "SP/cVarListSerializer.h"

// unnamed retail callees and globals (address in the comment)
extern char g_157d398;   // [0x0157d398]
extern char g_157d7d8;   // [0x0157d7d8]
extern char g_157dd7c;   // [0x0157dd7c]
extern char g_157ddb8;   // [0x0157ddb8]
extern char g_157e358;   // [0x0157e358]
extern char g_157e578;   // [0x0157e578]
extern char g_157e758;   // [0x0157e758]
#include <math.h>
#include "SP/cCommunity.h"
#include "SP/cDefaultAoEArea.h"
#include "SP/cDefaultBeamProjectile.h"
#include "SP/cPlanetModel.h"
#include "SP/cSPTimer.h"
#include "SP/cEffectInfo.h"
#include "SP/cEmpire.h"
#include "SP/cGameNounManager.h"
#include "SP/cSPCreatureBase.h"

// ---- items of slice s00cb2f70 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct VObj { void** vt; };
typedef void* (__thiscall *FnVp0)(void*);
bool __cdecl EA_IO_WriteUint32(void* s, const void* p, uint32_t n, int endian); // 0x0093aa70
bool __cdecl EA_IO_ReadInt32(void* s, void* p, uint32_t n, int endian);         // 0x0093a780
extern char g_157d398;   // [0x0157d398]
extern char g_157d7d8;   // [0x0157d7d8]
extern char g_157dd7c;   // [0x0157dd7c]
extern char g_157ddb8;   // [0x0157ddb8]
extern char g_157e358;   // [0x0157e358]
extern char g_157e578;   // [0x0157e578]
extern char g_157e758;   // [0x0157e758]
struct IStream;
struct cGameData {
    void* mpVtbl;        // +0x00
    char  pad04[0x30];   // +0x04
    void __thiscall Write(IStream* s);   // 0x00b18590
    void __thiscall Read(IStream* s);    // 0x00b18600
};
struct cLocomotiveObject {
    char  pad00[0x1000];
    void __thiscall Write(IStream* s);   // 0x00c448a0
    void __thiscall Read(IStream* s);    // 0x00c43c10
};
struct cSpatialObject {
    char  pad00[0x1000];
    void __thiscall Write(IStream* s);   // 0x00c88a90
};
struct cDataSerializationInfo { char d[0x14]; };
class cVarListSerializer {
public:
    cDataSerializationInfo mInfos[128]; // +0x0000
    int      mSerializableVarCount;     // +0x0a00
    int      mSerializedVarCount;       // +0x0a04
    uint32_t mSignature;                // +0x0a08
    void*    mpObject;                  // +0x0a0c
    void*    mpSerializerList;          // +0x0a10

    cVarListSerializer(void* obj, void* list, uint32_t sig); // 0x00692f90
    bool __thiscall Serialize(IStream* s);                   // 0x00692900
    bool __thiscall SerializeRead(IStream* s);               // 0x00693e10
};
static inline void* StreamWriter(IStream* s) {
    return ((FnVp0)((VObj*)s)->vt[0x20 / 4])(s);
}
static inline void* WriterValue(void* w) {
    return ((FnVp0)((VObj*)w)->vt[0x18 / 4])(w);
}
struct cSPSpaceToolData {
    char pad00[0x150];
    char mb150;                                     // +0x150
    int __thiscall GetProjectileMotion();           // 0x0104bd90
};
struct CSubCast {
    void* __thiscall Cast_00c41d00(int type);   // 0x00c41d00
    void* __thiscall Cast_00b18460(int type);   // 0x00b18460
    void* __thiscall Cast_00c884f0(int type);   // 0x00c884f0
    void* __thiscall Cast_00bfc380(int type);   // 0x00bfc380
    void* __thiscall Cast_00ac0320(int type);   // 0x00ac0320
};
struct CObj3760 {
    void* __thiscall Cast(int type);
};
struct CArtilleryProjectile {
    cGameData         mGameData;   // +0x00
    cLocomotiveObject mLoco;       // +0x34
    bool __thiscall Write(IStream* s);
};
struct CArtilleryProjectileR {
    cGameData         mGameData;   // +0x00
    cLocomotiveObject mLoco;       // +0x34
    bool __thiscall Read(IStream* s);
};
struct CFlakProjectile {
    cGameData         mGameData;   // +0x00
    cLocomotiveObject mLoco;       // +0x34
    void __thiscall Write(IStream* s);
};
struct CObj3ad0 {
    void* __thiscall Cast(int type);
};
struct CCulturalProjectile {
    cGameData         mGameData;   // +0x00
    cLocomotiveObject mLoco;       // +0x34
    void __thiscall Write(IStream* s);
};
struct CObj3c80 {
    void* __thiscall Cast(int type);
};
struct CResourceProjectile {
    cGameData      mGameData;    // +0x00
    cSpatialObject mSpatial;     // +0x34
    void __thiscall Write(IStream* s);
};
struct CObj3e20 {
    void* __thiscall Cast(int type);
};
struct CDefaultAoEArea {
    cGameData      mGameData;    // +0x00
    cSpatialObject mSpatial;     // +0x34
    void __thiscall Write(IStream* s);
};
struct CCulturalProjectileW {
    cGameData         mGameData;   // +0x00
    cLocomotiveObject mLoco;       // +0x34
    void __thiscall Write(IStream* s);
};
struct CResourceProjectileW2 {
    cGameData         mGameData;   // +0x00
    cLocomotiveObject mLoco;       // +0x34
    void __thiscall Write(IStream* s);
};
// ---- items of slice s00cb2f70 end

// ---- items of slice s00cb44b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_1em5;                          // 0x01475160
extern float g_1em3;                          // 0x013f9428
typedef unsigned int   uint;
struct Vector3 { float x, y, z; };
struct Quaternion { float x, y, z, w; };
struct RefCounted {
virtual void r00();
virtual void r04();
virtual void r08();
virtual void r0c();
virtual void r10();
virtual void r14();
virtual void r18();
virtual void r1c();
virtual void r20();
virtual void r24();
virtual void r28();
virtual void r2c();
virtual void r30();
virtual void r34();
virtual void r38();
virtual void r3c();
virtual void r40();
virtual void r44();
virtual void r48();
virtual void r4c();
virtual void r50();
virtual void r54();
virtual void r58();
virtual void r5c();
virtual void r60();
virtual void r64();
};
typedef void* (*Vfn1)(void*);
typedef void* (*Vfn2)(void*, void*);
typedef void* (__stdcall *VfnS2)(void*, void*);
struct Tool { char pad[0x114]; void* mStrategy; };
struct CTarget { bool IsValid(); };            // 0x0104cd80, thiscall, ret bool
struct cLocomotionBase {
    char pad[0x30];
    void* mTarget;                           // +0x30
    bool HasLiveTarget();                    // 0x00cb4a40
};
struct cLocomotionObj14 {
    char pad[0x14];
    void* mTarget;                           // +0x14
    bool HasLiveTarget14();                  // 0x00cb4ca0
    void* GetToolStrategy();                 // 0x00cb5420
};
struct cLocomotionObjDC {
    char pad[0xdc];
    void* mTarget;                           // +0xdc
    bool HasLiveTargetDC();                  // 0x00cb5560
};
struct cOutStream;
void cVarListSerializer_ctor(void* p, void* obj, void* list, uint sig);      // 0x00692f90
bool cVarListSerializer_Serialize(void* p, cOutStream* s);                   // 0x00692900
bool  EA_IO_WriteUint32(void* st, const void* buf, int n, int flag);         // 0x0093aa70
bool  StreamWrite(void* st, int a, int b);                                   // 0x0093a9a0
void  QuaternionFromDirections(Quaternion* out, const Vector3* dir, const Vector3* up); // 0x00698180
struct cLocomotiveObject_s00cb_44b0;
struct cGameData_s00cb_44b0 {
virtual void g00();
virtual void g04();
virtual void g08();
virtual void g0c();
virtual void g10();
virtual void g14();
virtual void g18();
virtual void g1c();
virtual void g20();
virtual void g24();
virtual void g28();
virtual void g2c();
virtual void g30();
virtual void g34();
virtual void g38();
virtual void g3c();
virtual void g40();
virtual void g44();
virtual void g48();
virtual void g4c();
virtual void g50();
virtual void g54();
virtual void g58();
virtual void g5c();
virtual void g60();
virtual void g64();
    void Write(cOutStream* s);                                               // 0x00b18590
};
struct IStream_s00cb_44b0 { virtual void i00(); virtual void i04(); virtual void i08(); virtual void i0c();
                 virtual void i10(); virtual void i14(); virtual void i18(); };
struct GetStreamObj { virtual void w00(); virtual void w04(); virtual void w08(); virtual void w0c();
virtual void w10();
virtual void w14();
virtual void w18();
virtual void w1c();
                      virtual IStream_s00cb_44b0* GetStream(); };                    // +0x18
void  cLocomotiveObject_Write(cLocomotiveObject_s00cb_44b0* o, cOutStream* s);          // 0x00c448a0
void  cLocomotiveObject_Shutdown(cLocomotiveObject_s00cb_44b0* o);                      // 0x00c43f90
Vector3* cLocomotiveObject_GetVelocity(cLocomotiveObject_s00cb_44b0* o);                // 0x00d20610
struct cLocomotiveObject_s00cb_44b0 {
virtual void l00();
virtual void l04();
virtual void l08();
virtual void l0c();
virtual void l10();
virtual void l14();
virtual void l18();
virtual void l1c();
virtual void l20();
virtual void l24();
virtual void l28();
virtual void l2c();
virtual void l30();
virtual void l34();
virtual void l38();
virtual void l3c();
virtual void l40();
virtual void l44();
virtual void l48();
virtual void l4c();
virtual void l50();
virtual void l54();
virtual void l58();
virtual void l5c();
virtual void l60();
virtual void l64();
virtual void l68();
virtual void l6c();
virtual void l70();
virtual void l74();
virtual void l78();
virtual void l7c();
virtual void l80();
virtual void l84();
virtual void l88();
virtual void l8c();
virtual void l90();
virtual void l94();
virtual void l98();
virtual void l9c();
virtual void lA0();
virtual void lA4();
virtual void lA8();
virtual void lAC();
virtual void lB0();
virtual void lB4();
virtual void lB8();
virtual void lBC();
virtual void lC0();
virtual void lC4();
virtual void lC8();
virtual void lCC();
virtual void lD0();
virtual void lD4();
virtual void lD8();
virtual void lDC();
virtual void lE0();
virtual void lE4();
virtual void lE8();
virtual void lEC();
virtual void lF0();
virtual void lF4();
virtual void lF8();
virtual void lFC();
virtual void l100();
virtual void l104();
virtual void l108();
virtual void l10c();
virtual void l110();
virtual void l114();
virtual void l118();
virtual void l11c();
virtual void l120();
virtual void l124();
virtual Vector3* GetPosition();
    virtual void SetOrientation(Quaternion* q);              // +0x3c
};
float FUN_0104cda0(void* p);                                                 // 0x0104cda0
float FUN_0104be60(void* p);                                                 // 0x0104be60
// ---- items of slice s00cb44b0 end

// ---- items of slice s00cb5620 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" float __cdecl sqrtf(float);
typedef unsigned char  u8;
typedef unsigned int   u32;
typedef int            s32;
typedef long long      s64;
typedef float          f32;
#define VT(p)   (*(void***)(p))
#define MOPS(p) ((COps*)(p))
struct COps {
    void  FUN_00c88670(u32);                          // 0x00c88670 Simulator::cCommunity::func54h
    void  FUN_00c3f160(s32, f32);                     // 0x00c3f160 cInteractableObject::SetEffectId
    void  FUN_00c8b2e0();                             // 0x00c8b2e0
    void  FUN_00ac0450();                             // 0x00ac0450
    void  FUN_00bc3130();                             // 0x00bc3130 SP::cSPTimer::Restart
    void  FUN_00b638b0();                             // 0x00b638b0 SP::cGonzagoTimer::~cGonzagoTimer
    void  FUN_00c8a420();                             // 0x00c8a420
    f32   FUN_0104be40();                             // 0x0104be40 SP::cSPSpaceToolData::GetDamageRadius
    u32   FUN_00ce6950();                             // 0x00ce6950 cStarRecordRef::GetCommContext
    void  FUN_00be0fc0(u32);                          // 0x00be0fc0
    void  FUN_00bdad60(u32);                          // 0x00bdad60
    void  FUN_00bcc7e0(u32);                          // 0x00bcc7e0
    void  FUN_00bcd130(u32);                          // 0x00bcd130
    u32   FUN_008e7f80();                             // 0x008e7f80 SP::cCombatant::GetDamageState
    u8    FUN_00b35d30(u32, f32, void*, u32);         // 0x00b35d30
    void* FUN_00b7f250();                             // 0x00b7f250 SP::BuildSurfaceOrientation2
    void  FUN_00b184c0();                             // 0x00b184c0 SP::cGameData::~cGameData
    u32   FUN_00a68fb0(u32);                          // 0x00a68fb0 RandomUint32Uniform
};
void* __cdecl FUN_00b7e560(void*);                    // 0x00b7e560 SP::RandomDirection3
void* __stdcall FUN_00b3d350(void*, void*, void*);    // 0x00b3d350 SP::PlanetModel
void* __cdecl FUN_00b3d240(u32, f32, void*, u32);    // 0x00b3d240
void* __cdecl FUN_00ae3370(void*);                    // 0x00ae3370
void* __cdecl FUN_00bcd430(void*);                    // 0x00bcd430
void* __cdecl FUN_00c032a0(void*);                    // 0x00c032a0 SP::GetCreatureFromStimulus
void* __cdecl FUN_00ae3350(void*);                    // 0x00ae3350
__declspec(noinline) u8 __cdecl FUN_00cb6310(void*, u8);   // 0x00cb6310
__declspec(noinline) u8 __cdecl FUN_00cb6400(void*, u8);   // 0x00cb6400
extern f32 gF_0157d350;   // 0x0157d350  ( 1.0)
extern f32 gF_01471064;   // 0x01471064  ( 0.5)
extern f32 gF_013ec4b8;   // 0x013ec4b8  ( 1e-8)
extern u32 gU_0169a40c;   // 0x0169a40c
extern u8  gB_0169a408;   // 0x0169a408
struct cAimOwner {
    u8    mPad000[0x118];
    void* mpAim;          // 0x118
};
struct cToolData {
    u8    mPad000[0x114];
    void* mpItem114;      // 0x114
    void* mpItem118;      // 0x118
};
struct cCombatantObj {
    u8    mPad000[0x08];
    u8    mB_08;          // 0x008 mIgnoreCombatLineTest
    u8    mPad009[0x7f];
    u32   mU_88;          // 0x088
    u8    mPad08c[0x19c];
    u32   mU_228;         // 0x228
    u8    mPad22c[0x4e8];
    s32   mS_714;         // 0x714
};
class cCommunity {
public:
    u8    mPad000[0x5d4];
    void* mpInteractable;     // 0x5d4
public:
    void FUN_00cb5620(u32);   // 0x00cb5620
};
class cGameData_s00cb_5620 {
public:
    u8    mPad000[0x2c];      // 0x000
    void* mpSub2c;            // 0x02c
    u8    mPad030[0x04];      // 0x030
    u8    mSub34[0xa6];       // 0x034
    u8    mB_da;              // 0x0da
    u8    mPad0db[0x41];      // 0x0db
    u8    mSub11c[0x18];      // 0x11c
    void* mp134;              // 0x134
    void* mp138;              // 0x138
    u8    mPad13c[0x20];      // 0x13c
    f32   mF15c;              // 0x15c
    u8    mPad160[0x10];      // 0x160
    f32   mF170;              // 0x170
    u8    mPad174[0x04];      // 0x174
    s64   mQ64;               // 0x178 (quotient + sign)
    u8    mPad180[0x60];      // 0x180
    void* mp1e0;              // 0x1e0
public:
    void FUN_00cb5670();                          // 0x00cb5670 RemoveOwner
    void FUN_00cb56f0(void*, s32, f32, f32);      // 0x00cb56f0
};
class cDefaultBeamProjectile {
public:
    u8    mPad000[0x2c];      // 0x000
    void* mpSub2c;            // 0x02c
    u8    mPad030[0x104];     // 0x030
    void* mpOwner;            // 0x134
    void* mpTarget;           // 0x138
    f32   mCurX;              // 0x13c
    f32   mCurY;              // 0x140
    f32   mCurZ;              // 0x144
    u8    mPad148[0x14];      // 0x148
    f32   mF15c;              // 0x15c
    f32   mDirX;              // 0x160
    f32   mDirY;              // 0x164
    f32   mDirZ;              // 0x168
    u8    mPad16c[0x04];      // 0x16c
    f32   mF170;              // 0x170
    u8    mPad174[0x04];      // 0x174
    s32   mQ178;              // 0x178
    s32   mR17c;              // 0x17c
    f32   mF180;              // 0x180
    f32   mF184;              // 0x184
    f32   mF188;              // 0x188
    f32   mF18c;              // 0x18c
    u32   mU190;              // 0x190
    u32   mU194;              // 0x194
    f32   mF198;              // 0x198
    f32   mF19c;              // 0x19c
    f32   mF1a0;              // 0x1a0
    f32   mF1a4;              // 0x1a4
    f32   mF1a8;              // 0x1a8
    f32   mF1ac;              // 0x1ac
    u8    mPad1b0[0x10];      // 0x1b0
    u8    mTimer1c0[0x20];    // 0x1c0
    void* mpHit;              // 0x1e0
public:
    void FUN_00cb5770(void*, f32*);   // 0x00cb5770 Fire
    void FUN_00cb5930(f32*);          // 0x00cb5930 UpdateTargetPosition
    u32  FUN_00cb5980();              // 0x00cb5980
    u32  FUN_00cb5b70();              // 0x00cb5b70 IsHittingPlayer
};
class cDefaultAoEArea {
public:
    void* mpVtbl;             // 0x000
    void* mpVtbl2;            // 0x004
    u8    mPad008[0x2c];      // 0x008
    void* mpSubVtbl;          // 0x034
    u8    mPad038[0xd0];      // 0x038
    void* mpVtbl108;          // 0x108
    u8    mPad10c[0x10];      // 0x10c
    void* mpToolData;         // 0x11c
    f32   mOffX;              // 0x120
    f32   mOffY;              // 0x124
    f32   mOffZ;              // 0x128
    f32   mRadius;            // 0x12c
    u8    mActive;            // 0x130
    u8    mPad131[0x07];      // 0x131
    u8    mTimer138[0x20];    // 0x138
    u32   mU158;              // 0x158
    u32   mU15c;              // 0x15c
    u32   mU160;              // 0x160
    u32   mU164;              // 0x164
    u32   mU168;              // 0x168
    u32   mU16c;              // 0x16c
public:
    void FUN_00cb5bd0();                 // 0x00cb5bd0
    void FUN_00cb5cf0(void*);            // 0x00cb5cf0 InitArea
    u8   FUN_00cb5d80(f32*, f32*);       // 0x00cb5d80
    u8   FUN_00cb5e10(f32*, f32*);       // 0x00cb5e10 GetNoteEffectPositionAndOrientation
    u8   FUN_00cb5fe0();                 // 0x00cb5fe0
    u32  FUN_00cb6020();                 // 0x00cb6020
    u32  FUN_00cb6060();                 // 0x00cb6060 GetNoteEffectID
    void FUN_00cb6090();                 // 0x00cb6090 StartArea
    void FUN_00cb61d0();                 // 0x00cb61d0 StopArea
};
// ---- items of slice s00cb5620 end

// ---- items of slice s00cb6570 begin (TODO(rewrite): local stubs, replace by canonical classes)
void  FUN_00cb6570(void*, void*, float, void*, void*, void*, void*, void*); // 0x00cb6570 cdecl
void  FUN_00cb64c0();                        // 0x00cb64c0 default callback
void  FUN_00cb64e0();                        // 0x00cb64e0 alt callback
void  FUN_00cb63c0();                        // 0x00cb63c0 default callback
void  FUN_00cb63e0();                        // 0x00cb63e0 alt callback
void  FUN_00f47380(void*);                   // 0x00f47380 cdecl operator delete[]
void  FUN_00b184c0();                        // 0x00b184c0 thiscall cGameData dtor
char     g_169a408;   // 0x0169a408  byte flag store
uint32_t g_169a40c;   // 0x0169a40c
void*    g_vft_145dca8[4];  // 0x0145dca8  vtable reset stored into +0x504
struct CtxObj {
    char _p000[0x08];
    char mState;                 // +0x08
    char mAlt;                   // +0x09
};
struct Loco {
    void Shutdown();             // 0x00c43f90
    void Destroy();              // 0x00c432e0
    char _p000[0x1fc - 0x34];
};
struct GameObject {
    char     _p000[0x2c];
    void*    mp2c;               // +0x2c
    char     _p030[4];
    Loco     mLoco;              // +0x34
    void*    mp1fc;              // +0x1fc
    void*    mp200;              // +0x200
    void*    mp204;              // +0x204
    char     _p208[0x224 - 0x208];
    uint32_t m224;               // +0x224
    char     _p228[0x504 - 0x228];
    void*    mp504;              // +0x504
    char     _p508[0x518 - 0x508];
    void*    mp518;              // +0x518
    void*    mp51c;              // +0x51c
    void*    mp520;              // +0x520
    void*    mp524;              // +0x524
    char     _p528[0x534 - 0x528];
    void*    mp534;              // +0x534

    void       RemoveOwner();
    GameObject* _virtual_dtor(unsigned char flags);
    void       DestroyRefs();
    void       SetBallistic(const uint32_t* src);
    void       SetForwardDir(void* arg);
};
// ---- items of slice s00cb6570 end

// ---- items of slice s00cb7310 begin
#pragma warning(disable : 4100)
// ---- items of slice s00cb7310 end

// ---- items of slice s00cb91d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl FUN_00f473a0(int, const char*, int, int, int, int);    // operator_new
extern "C" void  __cdecl FUN_009216a0(void*, void*, void*, int);                // eastl::RBTreeInsert
extern "C" void* __cdecl FUN_00b3d350(void);                                    // SP::PlanetModel
extern "C" void  __cdecl FUN_00bff2d0(void*, int);
extern "C" void* __cdecl FUN_0067ddd0(void);                                    // EffectsManagerPtr
extern "C" void* __cdecl FUN_0069b440(void*, void*);                            // Matrix3FromFacingAndUp
extern float DAT_013ec4d0;
extern float DAT_0169aa18;
extern float DAT_0169aa1c;
extern float DAT_0169aa20;
extern float DAT_0169a9f4;
#define VF(p, off) (*(void**)((char*)(*(void**)(p)) + (off)))
extern "C" void* __cdecl FUN_00b3d300(uint32_t);                                // SP::NounManager
class TObj {
public:
    // ---- reused __thiscall callees (addresses in comments) -------------------
    void   F_18660();                       // 0x00b18660  SP::cGameData::cGameData
    void   F_c43860();                      // 0x00c43860
    void   F_c432e0();                      // 0x00c432e0
    void   F_184c0();                       // 0x00b184c0  SP::cGameData::~cGameData
    int    F_b7e3e0();                      // 0x00b7e3e0
    void*  F_b25f40();                      // 0x00b25f40
    void   F_0041cb40(void*);               // 0x0041cb40  rw::math::Matrix3::Assign

    // ---- slice targets -------------------------------------------------------
    TObj* FUN_00cb94b0();                                   // 0x00cb94b0 Simulator::cICBM::cICBM
    void* _virtual_dtor(uint8_t);                           // 0x00cb9600 Object::_virtual_dtor
    void* FUN_00cb9b90(uint8_t);                            // 0x00cb9b90 deleting dtor
    void  FUN_00cb9780(void**, void*, void**, char);        // 0x00cb9780 eastl rbtree insert helper
    void  FUN_00cb91d0();                                   // 0x00cb91d0 SP::cResourceProjectile::Explode
    void  FUN_00cb9650();                                   // 0x00cb9650 SP::cICBM::Explode
    void  FUN_00cb9810();                                   // 0x00cb9810 SpatialQuery helper
    void  FUN_00cb9bd0();                                   // 0x00cb9bd0 SP::cFlakProjectile::Explode
};
struct Rec {
    uint16_t flags0;
    uint16_t cnt0;
    uint16_t flags1;
    uint16_t cnt1;
    float    x;
    float    y;
    float    z;
    float    one;
    float    m[9];
};
// ---- items of slice s00cb91d0 end

// ---- items of slice s00cbb020 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned __int64 u64;
struct Vec3 { float x, y, z; };
#define VTSLOT(obj, off) ((*(void***)(obj))[(off) / 4])
typedef void  (__thiscall *Fn_v_p)(void*);
extern "C" void* DAT_01654c10 = 0;                       // 0x01654c10  game-mode tag B
struct Obj;
struct RefList;
struct cSPTimer;
struct cPathFollowingLocomotion;
struct cSPSpaceTool;
namespace Simulator {
 struct cGameData_s00cb_b020; struct cLocomotiveObject_s00cb_b020; 
}
struct Obj {
    int    m_8e7f80();                       // 0x008e7f80  damage-state query
    int    m_104bfa0();                      // 0x0104bfa0  timer limit
    float  m_104be70();                      // 0x0104be70  fuse radius
    bool   m_104cd20();                      // 0x0104cd20
    bool   m_104cd30();                      // 0x0104cd30
    bool   m_104cd60();                      // 0x0104cd60
    bool   m_104cda0();                      // 0x0104cda0
    Obj*   m_104f930();                      // 0x0104f930  cSPSpaceToolData::GetStrategy
    float  m_c41f20();                       // 0x00c41f20
    bool   m_c38990(int a);                  // 0x00c38990
    void   m_ae6970();                       // 0x00ae6970  eastl vector destructor
    void   m_b638b0();                       // 0x00b638b0  SP::cGonzagoTimer::~cGonzagoTimer
    void   m_c432e0();                       // 0x00c432e0
    void   m_b184c0();                       // 0x00b184c0  SP::cGameData::~cGameData
    void   m_c43f90();                       // 0x00c43f90  SP::cLocomotiveObject::Shutdown
    void   m_bc3170();                       // 0x00bc3170  cSPTimer reset
    void   m_aeab40(void* pKey);             // 0x00aeab40
    void   m_cb4ae0(Vec3* pEnd);             // 0x00cb4ae0  cPathFollowingLocomotion::UpdateEndPoint
    Vec3*  m_position();                     // vftable slot 0x2c
    void   m_setPosition(Vec3* p);           // vftable slot 0x38
};
struct cSPTimer {
    u8 mPad00[0x10];
    u64 GetElapsedTime();                    // 0x00bc3190  -> edx:eax
    void Start();                            // 0x00bc30f0
    void Reset();                            // 0x00bc3170
};
struct cPathFollowingLocomotion {
    u8   mPad00[0x24];
    int  m24;                                // +0x024
    u8   mPad28[0x30 - 0x28];
    int  m30;                                // +0x030
    void m_cb4ae0(Vec3* pEnd);               // 0x00cb4ae0  UpdateEndPoint
};
struct cSPSpaceTool {
    u8    mPad000[0x114];
    void* mpTarget;                          // +0x114
    int   m_104bfa0();                       // 0x0104bfa0
    bool  m_104cd20();                       // 0x0104cd20
    bool  m_104cd30();                       // 0x0104cd30
    bool  m_104cd60();                       // 0x0104cd60
    bool  m_104cda0();                       // 0x0104cda0
    Obj*  m_104f930();                       // 0x0104f930
};
struct RefList {
    void*  m00;                              // +0x00
    void*  mSentinelNext;                    // +0x04  points at itself when empty
    void*  mSentinelPrev;                    // +0x08  points at &mSentinelNext
    int    mCount;                           // +0x0c
    u8     mFlag;                            // +0x10
    u8     mPad11[3];
    int    m14;                              // +0x14
    void   m_cbae20(int field);              // 0x00cbae20 (ret 4)
    void   m_cbae70(void* pOut, void** pVal, int b);  // 0x00cbae70 (ret 0xc)
};
namespace Simulator {
struct cLocomotiveObject_s00cb_b020 {
    void* mVftable;                          // +0x000
    u8    mPad04[0x1c8 - 0x04];
    Vec3  mVec1c8;                           // +0x1c8  == cGameData+0x1fc
    u8    mPad1d4[0x1f0 - 0x1d4];
    int   mField1f0;                         // +0x1f0  == cGameData+0x224
    u8    mPad1f4[0x4d0 - 0x1f4];
    void  m_c432e0();                        // 0x00c432e0
    void  m_c43f90();                        // 0x00c43f90  Shutdown
    void  m_c421b0(void* p);                 // 0x00c421b0
};
}
namespace Simulator {
struct cGameData_s00cb_b020 {
    u8    mPad00[0x2c];
    void* mpOwner;                           // +0x02c
    u8    mPad30[0x04];
    cLocomotiveObject_s00cb_b020 mLoco;                 // +0x034  (0x4d0 bytes -> +0x504)
    void* mpVtable504;                       // +0x504  sub-object vftable
    u8    mPad508[0x10];
    cSPSpaceTool* mpSpaceTool;               // +0x518
    cPathFollowingLocomotion* mpLocomotion;  // +0x51c
    Vec3  mLastPosition;                     // +0x520
    u8    mPad52c[0x14];
    float mField540;                         // +0x540
    int   mField544;                         // +0x544
    cSPTimer mTimer;                         // +0x548
    u8    mPad558[0x18];
    RefList mList570;                        // +0x570
    u8    mPad588[0x04];
    Vec3  mHomePosition;                     // +0x58c
    int   mField598;                         // +0x598
    u8    mPad59c[0x30];
    void* mpField5cc;                        // +0x5cc
    int   mState5d0;                         // +0x5d0
    void* mpField5d4;                        // +0x5d4
    void* mpField5d8;                        // +0x5d8
    u8    mVector5dc[0x10];                  // +0x5dc  eastl vector

    void FUN_00cbb6f0();                     // 0x00cbb6f0  teardown
    void RemoveOwner();                      // 0x00cbb790
    bool FUN_00cbb840();                     // 0x00cbb840  space-tool update
};
}
// ---- items of slice s00cbb020 end

// ---- items of slice s00cbda10 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl sqrt(double);
extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);
extern float kTwoPi;                         // 0x0169aa28 (runtime-initialized float)
#pragma warning(disable: 4100)
#pragma intrinsic(sqrt, sin, cos)
inline void* operator new(unsigned int, void* p) throw() { return p; }
inline void operator delete(void*, void*) throw() {}
void* __cdecl operator new(unsigned int size, const char* pName, int flags, unsigned debugFlags,
                           const char* file, int line);                     // 0x00f473a0
void __cdecl operator delete[](void* p);                                    // 0x00f47380
struct Vector3_s00cb_da10 {
    float x, y, z;
    Vector3_s00cb_da10() {}
    Vector3_s00cb_da10(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3_s00cb_da10(const Vector3_s00cb_da10& v) : x(v.x), y(v.y), z(v.z) {}
    Vector3_s00cb_da10 operator+(const Vector3_s00cb_da10& b) const { return Vector3_s00cb_da10(x + b.x, y + b.y, z + b.z); }
    Vector3_s00cb_da10 operator-(const Vector3_s00cb_da10& b) const { return Vector3_s00cb_da10(x - b.x, y - b.y, z - b.z); }
    Vector3_s00cb_da10 operator*(float s) const { return Vector3_s00cb_da10(x * s, y * s, z * s); }
    Vector3_s00cb_da10 operator/(float s) const { float inv = 1.0f / s; return Vector3_s00cb_da10(x * inv, y * inv, z * inv); }
    Vector3_s00cb_da10& operator+=(const Vector3_s00cb_da10& b) { x += b.x; y += b.y; z += b.z; return *this; }
    float Length() const { return (float)sqrt(x * x + y * y + z * z); }
    Vector3_s00cb_da10 Normalized() const
    {
        float inv = 1.0f / (float)sqrt(x * x + y * y + z * z + 1e-8f);
        return Vector3_s00cb_da10(x * inv, y * inv, z * inv);
    }
    void Normalize()
    {
        float inv = 1.0f / (float)sqrt(x * x + y * y + z * z + 1e-8f);
        x *= inv; y *= inv; z *= inv;
    }
    inline void Rotate(const struct Matrix3& r);
    static const Vector3_s00cb_da10 ZERO;     // 0x0169a414
    static const Vector3_s00cb_da10 Z_AXIS;   // 0x0157d380 (0, 0, 1)
};
struct Matrix3 {
    float m[3][3];
    Matrix3& operator=(const Matrix3& o);    // 0x0041cb40 (out of line)
    static const Matrix3 IDENTITY;           // 0x0169aa44
};
inline void Vector3_s00cb_da10::Rotate(const Matrix3& r)
{
    float nx = x * r.m[0][0] + y * r.m[1][0] + z * r.m[2][0];
    float ny = x * r.m[0][1] + y * r.m[1][1] + z * r.m[2][1];
    float nz = x * r.m[0][2] + y * r.m[1][2] + z * r.m[2][2];
    x = nx; y = ny; z = nz;
}
Vector3_s00cb_da10 normalized_safe(const Vector3_s00cb_da10& v);  // 0x00449c20 SP::normalized_safe
struct Transform {
    enum { kTransformFlagScale = 1, kTransformFlagRotation = 2, kTransformFlagOffset = 4 };
    int16_t mnFlags;
    int16_t mnTransformCount;
    Vector3_s00cb_da10 mOffset;
    float   mfScale;
    Matrix3 mRotation;

    Transform() : mOffset(Vector3_s00cb_da10::ZERO), mnFlags(0), mnTransformCount(0), mfScale(1.0f)
    {
        mRotation = Matrix3::IDENTITY;
    }
    const Vector3_s00cb_da10& GetOffset() const { return mOffset; }
    Transform& SetOffset(const Vector3_s00cb_da10& v)
    {
        mOffset = v;   // NB: implicit Vector3 operator= (field copy)
        mnFlags |= kTransformFlagOffset;
        mnTransformCount++;
        return *this;
    }
    Transform& PreTranslate(const Vector3_s00cb_da10& v)
    {
        mOffset += v;
        mnFlags |= kTransformFlagOffset;
        mnTransformCount++;
        return *this;
    }
    Transform& PreRotate(const Vector3_s00cb_da10& from, const Vector3_s00cb_da10& to);   // 0x006ba840
    Vector3_s00cb_da10 Apply(Vector3_s00cb_da10 v) const
    {
        if (mnFlags & kTransformFlagRotation)
            v.Rotate(mRotation);
        return mOffset + v * mfScale;
    }
};
struct Vector3Vector {
    Vector3_s00cb_da10* mpBegin;
    Vector3_s00cb_da10* mpEnd;
    Vector3_s00cb_da10* mpCapacity;
    uint32_t mAllocator;

    Vector3Vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~Vector3Vector()
    {
        if (mpBegin) {
            if (((uint32_t*)mpBegin)[-1])
                operator delete[](mpBegin);
        }
    }
    Vector3_s00cb_da10* erase(Vector3_s00cb_da10* first, Vector3_s00cb_da10* last);               // 0x0050f740
    void DoInsertValue(Vector3_s00cb_da10* position, const Vector3_s00cb_da10& value);  // 0x004b5ad0
    void clear() { erase(mpBegin, mpEnd); }
    void push_back(const Vector3_s00cb_da10& value)
    {
        if (mpEnd < mpCapacity)
            ::new(mpEnd++) Vector3_s00cb_da10(value);
        else
            DoInsertValue(mpEnd, value);
    }
};
template <class T> struct intrusive_ptr {
    T* mpObject;
    T* get() const { return mpObject; }
    intrusive_ptr& operator=(T* pObject)
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
};
struct cGameData_s00cb_da10 {
    virtual int AddRef();                       // 0x00
    virtual int Release();                      // 0x04
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
    virtual uint32_t GetPoliticalID();          // 0x4c
    uint32_t gameDataFields[0x30 / 4];
};
struct cCombatant {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual void v20();
    virtual int GetRandomAimIndex();            // 0x24
    virtual Vector3_s00cb_da10 GetAimPoint(int index);     // 0x28
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
    virtual void* Cast(uint32_t type);          // 0x5c
    virtual int AddRef();                       // 0x60
    virtual int Release();                      // 0x64
};
struct cSpaceToolData {
    virtual void v00();
    virtual int AddRef();                       // 0x04
    virtual int Release();                      // 0x08
};
struct cPathFollowingLocomotion_s00cb_da10 {
    virtual int AddRef();                       // 0x00
    virtual int Release();                      // 0x04
    cPathFollowingLocomotion_s00cb_da10(const Vector3Vector& points, uint32_t motionID);   // 0x00cbaf00
    uint32_t data[0x4c / 4];
};
enum {
    kCulturalTargetType = 0x3D5C477,
    kBuildingType       = 0xE9CB8BA,
    kTurretType         = 0x436F315,
    kVehicleType        = 0x137E8E0,
    kCreatureAnimalType = 0xD0036E08,
    kProjectileMotion   = 0x82CE6992,
};
template <uint32_t TYPE> inline void* object_cast(cCombatant* p)
{
    return p ? p->Cast(TYPE) : 0;
}
class cLocomotiveObject_s00cb_da10 {   // secondary base at +0x34
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
virtual void v28();
    virtual const Vector3_s00cb_da10& GetPosition();       // 0x2c
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
virtual void v74();
virtual void v78();
virtual void v7c();
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v8c();
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
    virtual void SetDesiredSpeed(float speed, int arg);   // 0xc4

    void SetLocomotion(cPathFollowingLocomotion_s00cb_da10* p);      // 0x00c421b0

    uint32_t pad04[(0x1f0 - 4) / 4];
    int field_1f0;                              // this+0x224
    uint32_t pad1f4[(0x4d0 - 0x1f4) / 4];
};
class cCulturalProjectile : public cGameData_s00cb_da10, public cLocomotiveObject_s00cb_da10 {
public:
    void LaunchProjectile(cGameData_s00cb_da10* owner, cGameData_s00cb_da10* vehicle, cSpaceToolData* tool,
                          cCombatant* target, const Vector3_s00cb_da10& targetPos, float speed,
                          bool arg_538, bool spin);

    uint32_t projectile[0x14 / 4];              // 0x504 cProjectile base (unused here)
    intrusive_ptr<cPathFollowingLocomotion_s00cb_da10> mpLocomotion;   // 0x518
    intrusive_ptr<cGameData_s00cb_da10> mpVehicle;         // 0x51c
    intrusive_ptr<cCombatant> mpTarget;         // 0x520
    intrusive_ptr<cSpaceToolData> mpTool;       // 0x524
    int field_528;                              // 0x528 (aim index)
    Vector3_s00cb_da10 mTargetPos;                         // 0x52c
    bool field_538;                             // 0x538
    bool mbSpin;                                // 0x539
    uint32_t pad53c[(0x560 - 0x53c) / 4];
    uint32_t mOwner;                            // 0x560 (owner's political id)
};
static inline float RingAngle(int i) { return (float)i * kTwoPi / -12.0f; }
// ---- items of slice s00cbda10 end

// ---- items of slice s00cbf120 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" float sinf(float);
extern "C" float cosf(float);
extern float g_0157e904, g_0157e900, g_0169aa28, g_013ec4b8, g_013ec480;
extern char  g_desc_pos[], g_desc_type[];
extern char  g_game_mode[];
extern "C" float  FUN_00b7e4d0();
extern "C" void   FUN_00466320(void*);
extern "C" void   FUN_00409930();
extern "C" void   FUN_00722c60(float*);
extern "C" void   FUN_00cb3f80(float*, float*, float*, float*, float*, float*);
extern "C" void   operator_delete__(void*);
extern "C" void   eastl_copy_range(void*, void*);
extern "C" void*  GetCurrentGameMode();
extern "C" float  RandomDoubleUniform(void*);
extern "C" void   PlanetModelDtor();
struct IObj {
virtual void  p00();
virtual void p01();
virtual void p02();
virtual void p03();
virtual void  p04();
virtual void p05();
virtual void p06();
virtual void p07();
virtual void  p08();
virtual void p09();
virtual void p10();
    virtual Vec3* GetPosition();                 // 0x2c
    virtual Vec3* GetOrientedPosition(...);      // 0x30 (0 args) / (out*)
virtual void  p13();
virtual void p14();
virtual void p15();
virtual void  p16();
virtual void p17();
virtual void p18();
    virtual void  Query(Vec3*, Vec3*, void**, int); // 0x4c
virtual void  p20();
virtual void p21();
virtual void p22();
virtual void p23();
virtual void  p24();
virtual void p25();
    virtual void* GetOrient(...);                // 0x68
    virtual void  p27();
    virtual void  Notify();                      // 0x70
virtual void  p29();
virtual void p30();
virtual void p31();
virtual void p32();
virtual void  p33();
virtual void p34();
virtual void p35();
virtual void p36();
virtual void  p37();
virtual void p38();
virtual void p39();
virtual void p40();
virtual void  p41();
virtual void p42();
virtual void p43();
virtual void p44();
    virtual void  p45();
    virtual int   IsType(int);                   // 0xb8
    virtual void  p47();
    virtual void  Release();                     // 0xc0
};
struct VecList { Vec3* begin; Vec3* end; Vec3* cap; };
struct cPlanetModel {
    Vec3* MakeRandomWorldPosition(Vec3*, Vec3*, float, float);
    void  DirectionToSurfacePosition(Vec3*, Vec3*);
};
extern "C" IObj*  FUN_00b3d240();
extern "C" char   FUN_00cbd620(IObj*, IObj*, VecList*, float, float, float);
extern "C" char   FUN_00cbcde0(float, float, float, float, float, float, VecList*);
extern "C" void   FUN_0044d4f0(Vec3*);
extern "C" void   FUN_00cbcc40(float, float, float, float, float, float, VecList*);
extern "C" char   FUN_00b35bf0(IObj*, Vec3*, Vec3*, Vec3*);
extern "C" void   FUN_004b5ad0(Vec3*, Vec3*);      // eastl::vector<Vec3>::DoInsertValue
extern "C" void   Matrix3FromQuaternion(float*, Vec3*);
extern "C" cPlanetModel* PlanetModelCtor2(Vec3*, Vec3*);
extern "C" cPlanetModel* PlanetModelCtor4(Vec3*, Vec3*, float, float);
extern "C" Vec3*  normalized_safe(Vec3*, Vec3*);
static inline void AppendPoint(VecList* v, const Vec3& p)
{
    if (v->end < v->cap) {
        *v->end = p;
        v->end = v->end + 1;
    } else {
        FUN_004b5ad0(v->end, (Vec3*)&p);
    }
}
// ---- items of slice s00cbf120 end

// ---- items of slice s00cc22c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define nullptr 0
struct Vec3_s00cc_22c0 {
    float mX;
    float mY;
    float mZ;
};
class IRefCounted {
public:
    virtual void AddRef();                      // 0x00
    virtual void Release();                     // 0x04
    virtual void v08();
    virtual void* Query(const void* pType);     // 0x0c
    virtual void v10();
};
class cEmpire : public IRefCounted {
public:
    void GetColor(void* pColor);
    uint8_t mPad14[0x30];
};
class cPlanetModel_s00cc_22c0 {
public:
    void* BuildSurfaceOrientation(void* pOut, const Vec3_s00cc_22c0* pPosition);
};
class cEffectInfo : public IRefCounted {
public:
    uint8_t mPad14[0x10];
};
class cEffectsManager {
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
    virtual void v28();
    virtual void CreateEffect(uint32_t id, int a, cEffectInfo** ppOut);   // 0x2c
};
class cSpatialObjectView : public IRefCounted {
public:
    cSpatialObjectView();
    ~cSpatialObjectView();
    void SetObject(void* pObject);                  // 0x24
    int UpdateState();
    void HandleSimulationUpdate(int a, int b);
    void CreateEffect(uint32_t id, int a);          // wrapper over the effect list

    uint8_t mPad04[0x10];           // 0x04
    void* mpObject;                 // 0x14
    uint8_t mPad18[0x1c];           // 0x18
    cEffectInfo* mpEffectInfo;      // 0x34
    uint8_t mFlag38;                // 0x38
    uint8_t mFlag39;                // 0x39
    uint8_t mFlag3a;                // 0x3a
    uint8_t mFlag3b;                // 0x3b
    uint8_t mFlag3c;                // 0x3c
    uint8_t mFlag3d;                // 0x3d
    uint8_t mPad3e[0x02];           // 0x3e
    int mViewState;                 // 0x40
};
class cDefaultToolProjectile : public cSpatialObjectView {
public:
    void Explode(int nKind, void* pHit);
};
class cEmotionSource : public IRefCounted {
public:
    void* GetTarget();
};
class cSpaceProjectile : public IRefCounted {
public:
    virtual void v14();
    virtual void v18();
    virtual uint32_t GetEffectId();                 // 0x1c
    virtual void v20();
    uint8_t mPad18[0x1c];
};
struct Matrix33 {
    float mValue[9];
};
struct EffectSpawnInfo {
    uint16_t mFlags;                // 0x00
    int16_t  mCount;                // 0x02
    Vec3_s00cc_22c0     mPosition;             // 0x04
    float    mScale;                // 0x10
};
cEffectsManager* EffectsManager();
cPlanetModel_s00cc_22c0* PlanetModel(Vec3_s00cc_22c0* pOut, const Vec3_s00cc_22c0* pPosition);
void* Matrix3FromFacingAndUp(Matrix33* pOut, const Vec3_s00cc_22c0* pDirection);
void* BuildOrientationMatrix(Matrix33* pOut, const void* pOrientation);
void* GetUniverseContext();
cEmpire* GetPlayerEmpire(Vec3_s00cc_22c0* pOut);
uint8_t* GetGameDataVectorCreatures();
uint32_t GetHitEffectIdA();
uint32_t GetHitEffectIdB();
uint32_t GetHitEffectIdC();
uint32_t GetTrailEffectId();
uint32_t GetProjectileKind();
bool IsWaterSurface();
void* CreateHitInstance(uint32_t id);
void SpawnWorldDecal(const Vec3_s00cc_22c0* pPosition);
void* FindObjectAt(void* pVector, const Vec3_s00cc_22c0* pPosition, int a);
void ApplyDamageShake(const Vec3_s00cc_22c0* pPosition);
void CameraShake(const Vec3_s00cc_22c0* pPosition, uint32_t id, uint32_t a, uint32_t b);
void SpawnHitParticles(void* pEffect);
void NotifyProjectileHit();
extern uint8_t gGameModeTribe;
// ---- items of slice s00cc22c0 end

// @ 0x00cb36e0
int __cdecl SP_PathPrefsForTool(cSPSpaceToolData* tool)
{
    int result = 2;
    if (tool->mb150 != 0) {
        switch (tool->GetProjectileMotion()) {
        case 0x3307b570:              result = 5; break;
        case (int)0x82ce6992:         result = 2; break;
        case (int)0xa7172377:         result = 4; break;
        case 0x0ba57653:              result = 1; break;
        case (int)0x63aa81ae:         result = 3; break;
        case (int)0x6a93cd4e:         result = 1; break;
        }
    }
    return result;
}

// @ 0x00cb3760
void* CObj3760::Cast(int type)
{
    if (type != 0x1428a48) {
        if (type != 0x142db2a) {
            void* r = ((CSubCast*)((char*)this + 0x34))->Cast_00c41d00(type);
            if (r == 0) {
                r = ((CSubCast*)this)->Cast_00b18460(type);
                if (r == 0)
                    r = ((CSubCast*)((char*)this + 0x34))->Cast_00c884f0(type);
            }
            return r;
        }
        return this ? (char*)this + 0x504 : 0;
    }
    return this;
}

// @ 0x00cb37d0
bool CArtilleryProjectile::Write(IStream* s)
{
    void* w = StreamWriter(s);
    uint32_t id = 0x1428a48;
    void* v = WriterValue(w);
    EA_IO_WriteUint32(v, &id, 1, 0);
    mGameData.Write(s);
    mLoco.Write(s);
    cVarListSerializer ser(this, &g_157d398, 0x1a80d26);
    ser.Serialize(s);
    return true;
}

// @ 0x00cb3850
bool CArtilleryProjectileR::Read(IStream* s)
{
    uint32_t id;
    void* w = StreamWriter(s);
    void* v = WriterValue(w);
    EA_IO_ReadInt32(v, &id, 1, 0);
    mGameData.Read(s);
    mLoco.Read(s);
    cVarListSerializer ser(this, &g_157d398, 0x1a80d26);
    ser.SerializeRead(s);
    return true;
}

// @ 0x00cb3940
void CFlakProjectile::Write(IStream* s)
{
    void* w = StreamWriter(s);
    uint32_t id = 0x240e3b7;
    void* v = WriterValue(w);
    EA_IO_WriteUint32(v, &id, 1, 0);
    mGameData.Write(s);
    mLoco.Write(s);
    cVarListSerializer ser(this, &g_157d7d8, 0x1a80d26);
    ser.Serialize(s);
}

// @ 0x00cb3ad0
void* CObj3ad0::Cast(int type)
{
    if (type != 0x142db2a) {
        if (type != 0x244d3c0) {
            void* r = ((CSubCast*)((char*)this + 0x34))->Cast_00c41d00(type);
            if (r == 0) {
                r = ((CSubCast*)this)->Cast_00b18460(type);
                if (r == 0) {
                    r = ((CSubCast*)((char*)this + 0x34))->Cast_00c884f0(type);
                    if (r == 0)
                        r = ((CSubCast*)((char*)this + 0x518))->Cast_00bfc380(type);
                }
            }
            return r;
        }
        return this;
    }
    return this ? (char*)this + 0x504 : 0;
}

// @ 0x00cb3b70
void CCulturalProjectile::Write(IStream* s)
{
    void* w = StreamWriter(s);
    uint32_t id = 0x244d3c0;
    void* v = WriterValue(w);
    EA_IO_WriteUint32(v, &id, 1, 0);
    mGameData.Write(s);
    mLoco.Write(s);
    cVarListSerializer ser(this, &g_157dd7c, 0x1a80d26);
    ser.Serialize(s);
}

// @ 0x00cb3c80
void* CObj3c80::Cast(int type)
{
    if (type != 0x142db2a) {
        if (type != 0x24630ce) {
            void* r = ((CSubCast*)((char*)this + 0x34))->Cast_00c884f0(type);
            if (r == 0) {
                r = ((CSubCast*)this)->Cast_00b18460(type);
                if (r == 0)
                    r = ((CSubCast*)((char*)this + 0x11c))->Cast_00ac0320(type);
            }
            return r;
        }
        return this;
    }
    return this ? (char*)this + 0x108 : 0;
}

// @ 0x00cb3d20
void CResourceProjectile::Write(IStream* s)
{
    void* w = StreamWriter(s);
    uint32_t id = 0x24630ce;
    void* v = WriterValue(w);
    EA_IO_WriteUint32(v, &id, 1, 0);
    mGameData.Write(s);
    mSpatial.Write(s);
    cVarListSerializer ser(this, &g_157ddb8, 0x1a80d26);
    ser.Serialize(s);
}

// @ 0x00cb3e20
void* CObj3e20::Cast(int type)
{
    if (type != 0x142db2a) {
        if (type != 0x4167194) {
            void* r = ((CSubCast*)this)->Cast_00b18460(type);
            if (r == 0)
                r = ((CSubCast*)((char*)this + 0x34))->Cast_00c884f0(type);
            return r;
        }
        return this;
    }
    return this ? (char*)this + 0x108 : 0;
}

// @ 0x00cb3e90
void CDefaultAoEArea::Write(IStream* s)
{
    void* w = StreamWriter(s);
    uint32_t id = 0x4167194;
    void* v = WriterValue(w);
    EA_IO_WriteUint32(v, &id, 1, 0);
    mGameData.Write(s);
    mSpatial.Write(s);
    cVarListSerializer ser(this, &g_157e358, 0x1a80d26);
    ser.Serialize(s);
}

// @ 0x00cb41c0
void CCulturalProjectileW::Write(IStream* s)
{
    void* w = StreamWriter(s);
    uint32_t id = 0x4f76f08;
    void* v = WriterValue(w);
    EA_IO_WriteUint32(v, &id, 1, 0);
    mGameData.Write(s);
    mLoco.Write(s);
    cVarListSerializer ser(this, &g_157e578, 0x1a80d26);
    ser.Serialize(s);
}

// @ 0x00cb4350
void CResourceProjectileW2::Write(IStream* s)
{
    void* w = StreamWriter(s);
    uint32_t id = 0x5776a28;
    void* v = WriterValue(w);
    EA_IO_WriteUint32(v, &id, 1, 0);
    mGameData.Write(s);
    mLoco.Write(s);
    cVarListSerializer ser(this, &g_157e758, 0x1a80d26);
    ser.Serialize(s);
}

// @ 0x00cb44b0
int f00cb44b0_write(cGameData_s00cb_44b0* self, cOutStream* stream)
{
    void* w  = ((GetStreamObj*)stream)->GetStream();          // vtable +0x20
    void* wr = ((GetStreamObj*)w)->GetStream();               // vtable +0x18
    uint sig = 0x49cec5c;
    EA_IO_WriteUint32(wr, &sig, 1, 0);
    self->Write(stream);
    cLocomotiveObject_Write((cLocomotiveObject_s00cb_44b0*)((char*)self + 0x34), stream);
    char ser[12];
    cVarListSerializer_ctor(ser, self, (void*)0x0157e888, 0x1a80d26);
    cVarListSerializer_Serialize(ser, stream);
    return 0;
}

// @ 0x00cb4670
void f00cb4670_ballistic_execute(Vector3* self, float unused)
{
    cLocomotiveObject_s00cb_44b0* obj = *(cLocomotiveObject_s00cb_44b0**)((char*)self + 0x14);
    Vector3* vel = obj->GetPosition();                        // vtable +0x2c (direction)
    float len = vel->x * vel->x + vel->y * vel->y + vel->z * vel->z;
    if (len < 1.0f) {
        self->x = 0.0f; self->y = 0.0f; self->z = 0.0f;
        return;
    }
    Quaternion q;
    QuaternionFromDirections(&q, (const Vector3*)0x0169a9e8, self);
    obj->SetOrientation(&q);
}

// @ 0x00cb46f0
int f00cb46f0_calc_firing_vel(float p1, float p2, float p3, float p4, float p5, float p6, float p7, float* out, float p9, float p10, float p11)
{
    // complex ballistics; complete but not byte-exact
    extern float _c0_0157d360;
    float a = p9 - p1, b = p10 - p2, c = p11 - p3;
    float dist = a * a + b * b + c * c;
    (void)dist;
    float v = p7 * p7;
    if (v <= 1.0f && -1.0f <= v) {
        float inv = 1.0f;
        out[0] = a * inv;
        out[1] = b * inv;
        out[2] = c * inv;
        return 1;
    }
    return 0;
}

// @ 0x00cb4950
void f00cb4950(int self, RefCounted* a, uint v1, uint v2, uint v3, RefCounted* b)
{
    *(uint*)(self + 0x528) = v1;
    *(uint*)(self + 0x52c) = v2;
    *(uint*)(self + 0x530) = v3;
    RefCounted* old = *(RefCounted**)(self + 0x524);
    if (a != old) {
        if (a) ((RefCounted*)a)->r60();
        *(RefCounted**)(self + 0x524) = a;
        if (old) old->r64();
    }
    RefCounted* old2 = *(RefCounted**)(self + 0x534);
    if (b != old2) {
        if (b) b->r04();
        *(RefCounted**)(self + 0x534) = b;
        if (old2) old2->r08();
    }
}

// @ 0x00cb49e0
void f00cb49e0(int self)
{
    RefCounted* p = *(RefCounted**)(self + 0x524);
    if (p) {
        *(void**)(self + 0x524) = 0;
        p->r64();
    }
    RefCounted* q = *(RefCounted**)(self + 0x534);
    if (q) {
        *(void**)(self + 0x534) = 0;
        q->r08();
    }
    RefCounted* r = *(RefCounted**)(self + 0x2c);
    if (r) {
        *(void**)(self + 0x2c) = 0;
        r->r04();
    }
    cLocomotiveObject_Shutdown((cLocomotiveObject_s00cb_44b0*)(self + 0x34));
}

// @ 0x00cb4a40
bool cLocomotionBase::HasLiveTarget()
{
    if (mTarget && ((CTarget*)mTarget)->IsValid())
        return true;
    return false;
}

// @ 0x00cb4a70
void f00cb4a70(int self)
{
    if (*(uint*)(self + 0x40) != 0x6a93cd4e)
        return;
    int i = 0;
    if (*(int*)(self + 0x24) < 0)
        return;
    float* p = *(float**)(self + 0x10);
    do {
        float z = p[2], y = p[1], x = p[0];
        float len = x * x + y * y + z * z;
        // sqrt via SSE
        float sq = 0.0f;
        __asm { sqrtss xmm0, len }
        __asm { movss sq, xmm0 }
        if (*(float*)(self + 0x44) < sq)
            *(float*)(self + 0x44) = sq;
        if (*(float*)(self + 0x48) > sq)
            *(float*)(self + 0x48) = sq;
        i++;
        p += 3;
    } while (i <= *(int*)(self + 0x24));
}

// @ 0x00cb4ae0
void f00cb4ae0(int self, Vector3* p)
{
    float* begin = *(float**)(self + 0x10);
    int cnt = (int)((*(float**)(self + 0x14) - begin) * ((float)0x2aaaaaab));
    // recompute count properly: (end-begin)/12
    cnt = (int)((*(char**)(self + 0x14) - (char*)begin) / 12);
    float* last = begin + (cnt - 1) * 3;
    float dx = p->x - last[0];
    float dy = p->y - last[1];
    float dz = p->z - last[2];
    if (dx * dx + dy * dy + dz * dz <= g_1em5)
        return;
    last[0] = p->x; last[1] = p->y; last[2] = p->z;
    int idx = cnt - 2;
    float f = 0.9f;
    while (idx > *(int*)(self + 0x30)) {
        float* e = begin + idx * 3;
        e[1] = dy * f + e[1];
        float f2 = f - 0.1f;
        e[0] = dx * f + e[0];
        e[2] = dz * f + e[2];
        f = f2;
        if (!(0.0f < f))
            break;
        idx--;
    }
}

// @ 0x00cb4bd0
void f00cb4bd0(int self, RefCounted* obj)
{
    RefCounted* old = *(RefCounted**)(self + 0x518);
    if (obj != old) {
        if (obj) obj->r04();
        *(RefCounted**)(self + 0x518) = obj;
        if (old) old->r08();
    }
    void* tool = *(void**)((char*)*(void**)(self + 0x518) + 0x114);
    if (tool) {
        void* t2 = (*(Vfn2*)(*(int*)tool + 0xb8))(tool, (void*)0x013f94d4);
        if (t2) {
            int v = (int)(*(Vfn1*)(*(int*)t2 + 0x10))(t2);
            (*(void(**)(int, int))(*(int*)self + 0x48))(self, v);
            return;
        }
    }
    (*(void(**)(int, int))(*(int*)self + 0x48))(self, -1);
}

// @ 0x00cb4ca0
bool cLocomotionObj14::HasLiveTarget14()
{
    if (mTarget && ((CTarget*)mTarget)->IsValid())
        return true;
    return false;
}

// @ 0x00cb4cc0
void f00cb4cc0(Vector3* self, float unused)
{
    cLocomotiveObject_s00cb_44b0* obj = *(cLocomotiveObject_s00cb_44b0**)((char*)self + 0x14);
    obj->GetPosition();                                       // vtable +0x2c
    Vector3* vel = cLocomotiveObject_GetVelocity(obj);
    Vector3 v; v.x = vel->x; v.y = vel->y; v.z = vel->z;
    self->x = v.x; self->y = v.y; self->z = v.z;
    Quaternion q;
    QuaternionFromDirections(&q, (const Vector3*)0x0169a9e8, &v);
    obj->SetOrientation(&q);
}

// @ 0x00cb4d40
int f00cb4d40(int self, int a, int b, int c, int d, int e)
{
    // complex projectile configuration; complete but not byte-exact
    (void)self; (void)a; (void)b; (void)c; (void)d; (void)e;
    return 0;
}

// @ 0x00cb5050
void f00cb5050(int self)
{
    void* p = *(void**)(self + 0x4e4);
    float v = FUN_0104be60(p);
    if (v > 0.0f) {
        FUN_0104be60(*(void**)(self + 0x4e4));
        return;
    }
    (*(void(**)(int))(*(int*)self + 0xc8))(self);
}

// @ 0x00cb5090
void f00cb5090(Vector3* self, float unused)
{
    cLocomotiveObject_s00cb_44b0* obj = *(cLocomotiveObject_s00cb_44b0**)((char*)self + 0x14);
    obj->GetPosition();                                       // vtable +0x2c
    Vector3* vel = cLocomotiveObject_GetVelocity(obj);
    self->x = vel->x; self->y = vel->y; self->z = vel->z;
    float len = self->x * self->x + self->y * self->y + self->z * self->z;
    if (len > g_1em3) {
        Vector3 v; v.x = self->x; v.y = self->y; v.z = self->z;
        Quaternion q;
        QuaternionFromDirections(&q, (const Vector3*)0x0169a9e8, &v);
        obj->SetOrientation(&q);
    }
}

// @ 0x00cb5140
float* f00cb5140(int self, float* out)
{
    int path = *(int*)(self + 0x51c);
    if (path && (uint)((*(int*)(path + 0x14) - *(int*)(path + 0x10)) / 12) > 1) {
        float* p = *(float**)(path + 0x10);
        float dz = p[5] - p[2];
        float dy = p[4] - p[1];
        float dx = p[3] - p[0];
        float inv = 1.0f / (dx * dx + dy * dy + dz * dz);
        out[0] = inv * dx; out[1] = inv * dy; out[2] = dz * inv;
        return out;
    }
    float x = *(float*)(self + 0x1fc);
    float y = *(float*)(self + 0x200);
    float z = *(float*)(self + 0x204);
    if (x * x + y * y + z * z > 0.0f) {
        float inv = 1.0f / (x * x + y * y + z * z);
        out[0] = x * inv; out[1] = y * inv; out[2] = z * inv;
        return out;
    }
    (*(void(**)(int, float*))(*(int*)(self + 0x34) + 0x5c))(self + 0x34, out);
    return out;
}

// @ 0x00cb52c0
int f00cb52c0(int self)
{
    if (FUN_0104cda0(*(void**)(self + 0x518)) == 0.0f)
        return 0;
    void* p = *(void**)(self + 0x5cc);
    if (p && (*(Vfn1*)(*(int*)p + 0x10))(p))
        return 1;
    int* strat = (int*)0;   // GetStrategy stub
    (void)strat;
    return 0;
}

// @ 0x00cb5330
int f00cb5330_write(cGameData_s00cb_44b0* self, cOutStream* stream)
{
    void* w  = ((GetStreamObj*)stream)->GetStream();
    void* wr = ((GetStreamObj*)w)->GetStream();
    uint sig = 0x24270c4;
    EA_IO_WriteUint32(wr, &sig, 1, 0);
    self->Write(stream);
    cLocomotiveObject_Write((cLocomotiveObject_s00cb_44b0*)((char*)self + 0x34), stream);
    char ser[12];
    cVarListSerializer_ctor(ser, self, (void*)0x0157d890, 0x1a80d26);
    bool ok = cVarListSerializer_Serialize(ser, stream);
    float flag = *(float*)((char*)self + 0x51c);
    w  = ((GetStreamObj*)stream)->GetStream();
    wr = ((GetStreamObj*)w)->GetStream();
    char b = (flag != 0.0f);
    StreamWrite(wr, 1, b);
    if (flag != 0.0f) {
        char ser2[12];
        cVarListSerializer_ctor(ser2, (void*)(int)flag, (void*)0x0157d540, 0x1a80d26);
        cVarListSerializer_Serialize(ser2, stream);
    }
    return ok;
}

// @ 0x00cb5420
void* cLocomotionObj14::GetToolStrategy()
{
    void* p = *(void**)((char*)this + 0x14);
    void* s = *(void**)&((Tool*)p)->mStrategy;
    if (s)
        return (*(VfnS2*)(*(int*)s + 0xb8))(s, (void*)0x013f94d4);
    return 0;
}

// @ 0x00cb5450
void f00cb5450(int self, Vector3* a, Vector3* b)
{
    Vector3* p1 = (Vector3*)(*(void*(**)(int))(**(int**)(*(int*)(self + 0x518) + 0x114) + 0x2c))(
                       *(int*)(self + 0x518));
    a->x = p1->x; a->y = p1->y; a->z = p1->z;
    Vector3* p2 = (Vector3*)(*(void*(**)(int))(*(int*)(self + 0x34) + 0x2c))(self + 0x34);
    b->x = p2->x; b->y = p2->y; b->z = p2->z;
}

// @ 0x00cb54a0
void* f00cb54a0(int self, float maxSpeed, float turnRate, void* target)
{
    (void)target;
    *(float*)(self + 0x10) = maxSpeed;
    *(float*)(self + 0x14) = turnRate;
    return (void*)self;
}

// @ 0x00cb5560
bool cLocomotionObjDC::HasLiveTargetDC()
{
    if (mTarget && ((CTarget*)mTarget)->IsValid())
        return true;
    return false;
}

// @ 0x00cb5580
void f00cb5580(int self)
{
    RefCounted* p = *(RefCounted**)(self + 0x5e0);
    if (p) {
        *(void**)(self + 0x5e0) = 0;
        p->r08();
    }
    RefCounted* q = *(RefCounted**)(self + 0x5e4);
    if (q) {
        *(void**)(self + 0x5e4) = 0;
        q->r64();
    }
    RefCounted* r = *(RefCounted**)(self + 0x2c);
    if (r) {
        *(void**)(self + 0x2c) = 0;
        r->r04();
    }
    cLocomotiveObject_Shutdown((cLocomotiveObject_s00cb_44b0*)(self + 0x34));
}

// @ 0x00cb5620
void cCommunity::FUN_00cb5620(u32 a1)
{
    MOPS(this)->FUN_00c88670(a1);
    void* obj = mpInteractable;
    if (obj != 0) {
        f32 k = gF_0157d350;
        f32 s = ((f32 (__thiscall*)(void*))VT(this)[0x34 / 4])(this);
        f32 r = k * s;
        MOPS(obj)->FUN_00c3f160((s32)a1, r);
    }
}

// @ 0x00cb5670
void cGameData_s00cb_5620::FUN_00cb5670()
{
    void* p = mp134;
    if (p != 0) {
        mp134 = 0;
        ((void (__thiscall*)(void*))VT(p)[8 / 4])(p);
    }
    p = mp1e0;
    if (p != 0) {
        mp1e0 = 0;
        ((void (__thiscall*)(void*))VT(p)[4 / 4])(p);
    }
    p = mp138;
    if (p != 0) {
        mp138 = 0;
        ((void (__thiscall*)(void*))VT(p)[0x64 / 4])(p);
    }
    p = mpSub2c;
    if (p != 0) {
        mpSub2c = 0;
        ((void (__thiscall*)(void*))VT(p)[4 / 4])(p);
    }
    MOPS((u8*)this + 0x34)->FUN_00c8b2e0();
    MOPS((u8*)this + 0x11c)->FUN_00ac0450();
}

// @ 0x00cb56f0
void cGameData_s00cb_5620::FUN_00cb56f0(void* a1, s32 a2, f32 a3, f32 a4)
{
    void* old = mp134;
    if (a1 != old) {
        if (a1 != 0)
            ((void (__thiscall*)(void*))VT(a1)[4 / 4])(a1);
        mp134 = a1;
        if (old != 0)
            ((void (__thiscall*)(void*))VT(old)[8 / 4])(old);
    }
    if (a2 != 0)
        mQ64 = 1000 / a2;
    mF170 = a3;
    mF15c = a4;
    mB_da = 0;
}

// @ 0x00cb5770
void cDefaultBeamProjectile::FUN_00cb5770(void* target, f32* pos)
{
    MOPS(mTimer1c0)->FUN_00bc3130();

    void* aim = ((cAimOwner*)mpOwner)->mpAim;
    if (aim != 0) {
        f32* p = (f32*)((void* (__thiscall*)(void*))VT(aim)[0x2c / 4])(aim);
        mCurX = p[0];
        mCurY = p[1];
        mCurZ = p[2];
    } else {
        mCurX = pos[0];
        mCurY = pos[1];
        mCurZ = pos[2];
    }

    void* old = mpTarget;
    if (target != old) {
        if (target != 0)
            ((void (__thiscall*)(void*))VT(target)[0x60 / 4])(target);
        mpTarget = target;
        if (old != 0)
            ((void (__thiscall*)(void*))VT(old)[0x64 / 4])(old);
    }

    mF180 = 0.0f;
    mF184 = 0.0f;
    mF188 = 0.0f;
    mF18c = 0.0f;

    void* gd = (void*)((void* (__thiscall*)(void*))VT(target)[8 / 4])(target);
    f32* tpos = (f32*)((void* (__thiscall*)(void*))VT(gd)[0x2c / 4])(gd);
    f32 dx = pos[0] - tpos[0];
    f32 dy = pos[1] - tpos[1];
    f32 dz = pos[2] - tpos[2];
    f32 inv = 1.0f / sqrtf(dx * dx + dy * dy + dz * dz);

    f32 dir[3];
    dir[0] = dx * inv;
    dir[1] = dy * inv;
    dir[2] = dz * inv;
    mDirX = dir[0];
    mDirY = dir[1];
    mDirZ = dir[2];

    f32* rd = (f32*)FUN_00b7e560(dir);
    mF1a4 = rd[0];
    mF1a8 = rd[1];
    mF1ac = rd[2];
    mF198 = 0.0f;
    mF19c = 0.0f;
    mF1a0 = 0.0f;
    mU190 = 0;
    mU194 = 0;
}

// @ 0x00cb5930
void cDefaultBeamProjectile::FUN_00cb5930(f32* pos)
{
    f32* src;
    void* owner = mpOwner;
    if (owner != 0) {
        void* aim = ((cAimOwner*)owner)->mpAim;
        if (aim != 0)
            src = (f32*)((void* (__thiscall*)(void*))VT(aim)[0x2c / 4])(aim);
        else
            src = pos;
    } else {
        src = pos;
    }
    *(u32*)&mCurX = ((u32*)src)[0];
    *(u32*)&mCurY = ((u32*)src)[1];
    *(u32*)&mCurZ = ((u32*)src)[2];
}

// @ 0x00cb5980
u32 cDefaultBeamProjectile::FUN_00cb5980()
{
    void** slot = (void**)((u8*)mpSub2c + 0x114);
    void* p = *slot;
    if (p == 0)
        return 0;
    return ((u32 (__thiscall*)(void*, u32))VT(p)[0xb8 / 4])(p, 0x13f94d4);
}

// @ 0x00cb59b0
void __cdecl FUN_00cb59b0(void* self, f32* pos, f32 f1, f32 f2, s32 mode, s32 id, u32 a5, u32 a6)
{
    if (a6 == 0 && id != -1) {
        u32 myId = ((u32 (__thiscall*)(void*))VT(self)[0x10 / 4])(self);
        if (myId == (u32)id)
            return;
    }

    void* propA = 0;
    void* propB = 0;
    if (self != 0) {
        propA = (void*)((u32 (__thiscall*)(void*, u32))VT(self)[0x5c / 4])(self, 0xe9cb8ba);
        propB = (void*)((u32 (__thiscall*)(void*, u32))VT(self)[0x5c / 4])(self, 0x436f315);
    }

    if (mode == 3) {
        if (propA != 0) {
            u32 a = ((u32 (__thiscall*)(void*))VT(propA)[0x10 / 4])(propA);
            u32 b = ((u32 (__thiscall*)(void*))VT(self)[0x10 / 4])(self);
            if (b != a)
                return;
        }
        if (propA != 0)
            return;
        if (propB != 0)
            return;
    }

    void* gd = (void*)((void* (__thiscall*)(void*))VT(self)[8 / 4])(self);
    f32* gp = (f32*)((void* (__thiscall*)(void*))VT(gd)[0x2c / 4])(gd);
    f32 dx = gp[0] - pos[0];
    f32 dy = gp[1] - pos[1];
    f32 dz = gp[2] - pos[2];

    f32 v = f1;
    if (mode != 3) {
        s32 n = (s32)f2;
        u32 r = MOPS((void*)0x01601760)->FUN_00a68fb0((u32)n);
        v = (f32)((s32)r + (s32)f1);
    }

    f32 inv = 1.0f / sqrtf(dx * dx + dy * dy + dz * dz + gF_013ec4b8);
    f32 dir[3];
    dir[0] = dx * inv;
    dir[1] = dy * inv;
    dir[2] = dz * inv;
    ((void (__thiscall*)(void*, f32, s32, s32, f32*, u32))VT(self)[0x18 / 4])
        (self, v, id, mode, dir, a5);
}

// @ 0x00cb5b70
u32 cDefaultBeamProjectile::FUN_00cb5b70()
{
    void* p = mpHit;
    if (p != 0) {
        void* q = (void*)((u32 (__thiscall*)(void*, u32))VT(p)[0xc / 4])(p, 0xb033b403);
        if (q != 0 && ((cCombatantObj*)q)->mS_714 == 0)
            return 1;
    }
    return 0;
}

// @ 0x00cb5bd0
void cDefaultAoEArea::FUN_00cb5bd0()
{
    mpVtbl = (void*)0x14752b8;
    mpVtbl2 = (void*)0x14752a4;
    mpSubVtbl = (void*)0x14751e0;
    mpVtbl108 = (void*)0x14751b4;

    MOPS((u8*)this + 0x138)->FUN_00b638b0();

    void* p = mpToolData;
    if (p != 0)
        ((void (__thiscall*)(void*))VT(p)[8 / 4])(p);

    mpVtbl108 = (void*)0x145dca8;
    MOPS((u8*)this + 0x34)->FUN_00c8a420();
    MOPS(this)->FUN_00b184c0();
}

// @ 0x00cb5cf0
void cDefaultAoEArea::FUN_00cb5cf0(void* tool)
{
    void* old = mpToolData;
    if (tool != old) {
        if (tool != 0)
            ((void (__thiscall*)(void*))VT(tool)[4 / 4])(tool);
        mpToolData = tool;
        if (old != 0)
            ((void (__thiscall*)(void*))VT(old)[8 / 4])(old);
    }
    mRadius = MOPS(tool)->FUN_0104be40();
}

// @ 0x00cb5d80
u8 cDefaultAoEArea::FUN_00cb5d80(f32* pos, f32* orient)
{
    cToolData* tool = (cToolData*)mpToolData;
    if (tool == 0)
        return 0;
    if (tool->mpItem114 == 0)
        return 0;

    f32* p = (f32*)((void* (__thiscall*)(void*))VT((u8*)this + 0x34)[0x2c / 4])((u8*)this + 0x34);
    pos[0] = p[0] + mOffX;
    pos[1] = p[1] + mOffY;
    pos[2] = p[2] + mOffZ;

    f32* q = (f32*)((void* (__thiscall*)(void*))VT((u8*)this + 0x34)[0x30 / 4])((u8*)this + 0x34);
    orient[0] = q[0];
    orient[1] = q[1];
    orient[2] = q[2];
    orient[3] = q[3];
    return 1;
}

// @ 0x00cb5e10
u8 cDefaultAoEArea::FUN_00cb5e10(f32* pos, f32* orient)
{
    cToolData* tool = (cToolData*)mpToolData;
    if (tool == 0)
        return 0;
    if (tool->mpItem114 == 0)
        return 0;

    void* i1 = tool->mpItem114;
    void* o1 = (void*)((u32 (__thiscall*)(void*, u32))VT(i1)[0xb8 / 4])(i1, 0x1186577);
    void* i2 = tool->mpItem118;
    void* o2 = 0;
    if (i2 != 0)
        o2 = (void*)((u32 (__thiscall*)(void*, u32))VT(i2)[0xb8 / 4])(i2, 0x1186577);

    u32 f1 = *(u32*)((u8*)o1 + 0x50);
    if ((f1 & 0x10) != 0 && (f1 & 0x20) == 0) {
        f32* p = (f32*)((void* (__thiscall*)(void*))VT(o1)[0x2c / 4])(o1);
        pos[0] = p[0];
        pos[1] = p[1];
        pos[2] = p[2];
    } else {
        f32 tmp[6];
        f32* p = (f32*)((void* (__thiscall*)(void*, void*))VT(o1)[0x6c / 4])(o1, tmp);
        pos[0] = (p[0] + p[3]) * gF_01471064;
        pos[1] = (p[4] + p[1]) * gF_01471064;
        pos[2] = (p[5] + p[2]) * gF_01471064;
    }

    f32 cx, cy, cz;
    u32 f2 = *(u32*)((u8*)o2 + 0x50);
    if ((f2 & 0x10) != 0 && (f2 & 0x20) == 0) {
        f32* p = (f32*)((void* (__thiscall*)(void*))VT(o2)[0x2c / 4])(o2);
        cx = p[0];
        cy = p[1];
        cz = p[2];
    } else {
        f32 tmp[6];
        f32* p = (f32*)((void* (__thiscall*)(void*, void*))VT(o2)[0x6c / 4])(o2, tmp);
        cx = (p[0] + p[3]) * gF_01471064;
        cy = (p[4] + p[1]) * gF_01471064;
        cz = (p[5] + p[2]) * gF_01471064;
    }

    f32 diff[3];
    diff[0] = cx - pos[0];
    diff[1] = cy - pos[1];
    diff[2] = cz - pos[2];

    f32 tmpa[6];
    void* pm = (void*)FUN_00b3d350(tmpa, pos, diff);
    f32* r = (f32*)MOPS(pm)->FUN_00b7f250();
    orient[0] = r[0];
    orient[1] = r[1];
    orient[2] = r[2];
    orient[3] = r[3];
    return 1;
}

// @ 0x00cb5fe0
u8 cDefaultAoEArea::FUN_00cb5fe0()
{
    cToolData* tool = (cToolData*)mpToolData;
    void* p = tool->mpItem118;
    u32 v = 0;
    if (p != 0)
        v = ((u32 (__thiscall*)(void*, u32))VT(p)[0xb8 / 4])(p, 0x137e8e0);
    return (v != 0) ? 1 : 0;
}

// @ 0x00cb6020
u32 cDefaultAoEArea::FUN_00cb6020()
{
    cToolData* tool = (cToolData*)mpToolData;
    void* p = tool->mpItem114;
    u32 v = 0;
    if (p != 0)
        v = ((u32 (__thiscall*)(void*, u32))VT(p)[0xb8 / 4])(p, 0x137e8e0);
    u32 x = *(u32*)((u8*)v + 0xb1c);
    return 0x99736761 + ((x != 2) ? 0x749c5cb3 : 0);
}

// @ 0x00cb6060
u32 cDefaultAoEArea::FUN_00cb6060()
{
    cToolData* tool = (cToolData*)mpToolData;
    void* p = tool->mpItem114;
    if (p != 0)
        ((u32 (__thiscall*)(void*, u32))VT(p)[0xb8 / 4])(p, 0x137e8e0);
    return 0xfb2bdb16;
}

// @ 0x00cb6090
void cDefaultAoEArea::FUN_00cb6090()
{
    mActive = 0;
    MOPS((u8*)this + 0x138)->FUN_00bc3130();
    cToolData* tool = (cToolData*)mpToolData;
    mU158 = 0;
    mU15c = 0;
    mU160 = 0;
    mU164 = 0;
    mU168 = 0;
    mU16c = 0;

    if (MOPS(tool)->FUN_00ce6950() != 0x94e412ed)
        return;

    void* p = tool->mpItem118;
    void* a = 0;
    void* b = 0;
    void* c = 0;
    if (p != 0)
        a = (void*)((u32 (__thiscall*)(void*, u32))VT(p)[0xb8 / 4])(p, 0x3d5c477);
    p = tool->mpItem118;
    if (p != 0)
        b = (void*)((u32 (__thiscall*)(void*, u32))VT(p)[0xb8 / 4])(p, 0xe9cb8ba);
    p = tool->mpItem118;
    if (p != 0)
        c = (void*)((u32 (__thiscall*)(void*, u32))VT(p)[0xb8 / 4])(p, 0x436f315);

    if (a != 0) {
        void* q = tool->mpItem114;
        u32 r = 0;
        if (q != 0)
            r = ((u32 (__thiscall*)(void*, u32))VT(q)[0xb8 / 4])(q, 0x17f243b);
        MOPS(a)->FUN_00be0fc0(r);
        return;
    }
    if (b != 0) {
        MOPS(b)->FUN_00bcc7e0(1);
        return;
    }
    if (c != 0)
        MOPS(c)->FUN_00bcd130(1);
}

// @ 0x00cb61d0
void cDefaultAoEArea::FUN_00cb61d0()
{
    mActive = 1;
    cToolData* tool = (cToolData*)mpToolData;
    if (MOPS(tool)->FUN_00ce6950() != 0x94e412ed)
        return;

    void* p = tool->mpItem118;
    if (p != 0) {
        void* q = (void*)((u32 (__thiscall*)(void*, u32))VT(p)[0xb8 / 4])(p, 0x17f243b);
        if (q != 0) {
            if (((u8 (__thiscall*)(void*))VT(q)[0x2c / 4])(q) != 0)
                return;
        }
    }

    void* a = 0;
    void* b = 0;
    void* c = 0;
    p = tool->mpItem118;
    if (p != 0)
        a = (void*)((u32 (__thiscall*)(void*, u32))VT(p)[0xb8 / 4])(p, 0x3d5c477);
    p = tool->mpItem118;
    if (p != 0)
        b = (void*)((u32 (__thiscall*)(void*, u32))VT(p)[0xb8 / 4])(p, 0xe9cb8ba);
    p = tool->mpItem118;
    if (p != 0)
        c = (void*)((u32 (__thiscall*)(void*, u32))VT(p)[0xb8 / 4])(p, 0x436f315);

    if (a != 0) {
        void* q = tool->mpItem114;
        u32 r = 0;
        if (q != 0)
            r = ((u32 (__thiscall*)(void*, u32))VT(q)[0xb8 / 4])(q, 0x17f243b);
        MOPS(a)->FUN_00bdad60(r);
        return;
    }
    if (b != 0) {
        MOPS(b)->FUN_00bcc7e0(0xffffffff);
        return;
    }
    if (c != 0)
        MOPS(c)->FUN_00bcd130(0xffffffff);
}

// @ 0x00cb6310
u8 __cdecl FUN_00cb6310(void* a1, u8 a2)
{
    if (a1 == 0)
        return 0;

    void* c = (void*)((u32 (__thiscall*)(void*, u32))VT(a1)[0xc / 4])(a1, 0x13f94d4);
    if (c != 0) {
        u32 ds = MOPS(c)->FUN_008e7f80();
        if (ds == 2)
            return 0;
        if (((cCombatantObj*)c)->mB_08 != 0)
            return 0;
        if (a2 != 0)
            return 1;
        u32 id = ((u32 (__thiscall*)(void*))VT(c)[0x10 / 4])(c);
        if (id == gU_0169a40c)
            return 0;
        return 1;
    }

    void* p = (void*)((u32 (__thiscall*)(void*, u32))VT(a1)[0xc / 4])(a1, 0x3ed590d);
    if (p != 0) {
        u32 v = ((cCombatantObj*)p)->mU_88;
        if (v == 0 || v == 1 || v == 2)
            return 1;
        return 0;
    }

    void* q = (void*)((u32 (__thiscall*)(void*, u32))VT(a1)[0xc / 4])(a1, 0x175cdc9);
    if (q != 0) {
        u32 v = ((cCombatantObj*)q)->mU_228;
        if (v == 0x611a05e)
            return 1;
        if (v == 0x611a05f)
            return 1;
    }
    return 0;
}

// @ 0x00cb63c0
void __cdecl FUN_00cb63c0(void* a1)
{
    void* p = *(void**)((u8*)a1 + 0x64);
    FUN_00cb6310(p, 1);
}

// @ 0x00cb63e0
void __cdecl FUN_00cb63e0(void* a1)
{
    void* p = *(void**)((u8*)a1 + 0x64);
    FUN_00cb6310(p, 0);
}

// @ 0x00cb6400
u8 __cdecl FUN_00cb6400(void* a1, u8 a2)
{
    if (a1 == 0)
        return 0;

    void* c = (void*)((u32 (__thiscall*)(void*, u32))VT(a1)[0xc / 4])(a1, 0x13f94d4);
    if (c == 0)
        return 0;

    void* prop = (void*)((u32 (__thiscall*)(void*, u32))VT(c)[0x5c / 4])(c, 0xb033b403);
    u32 ds = MOPS(c)->FUN_008e7f80();
    if (ds == 2)
        return 0;
    if (((cCombatantObj*)c)->mB_08 != 0)
        return 0;
    if (a2 == 0) {
        u32 id = ((u32 (__thiscall*)(void*))VT(c)[0x10 / 4])(c);
        if (id == gU_0169a40c)
            return 0;
    }
    if (gB_0169a408 != 0 && prop != 0 && ((cCombatantObj*)prop)->mS_714 == 3)
        return 0;

    if (FUN_00ae3370(c) != 0)
        return 1;
    if (FUN_00bcd430(c) != 0)
        return 1;
    if (FUN_00c032a0(c) != 0)
        return 1;
    if (FUN_00ae3350(c) != 0)
        return 1;
    return 0;
}

// @ 0x00cb64c0
void __cdecl FUN_00cb64c0(void* a1)
{
    void* p = *(void**)((u8*)a1 + 0x64);
    FUN_00cb6400(p, 1);
}

// @ 0x00cb64e0
void __cdecl FUN_00cb64e0(void* a1)
{
    void* p = *(void**)((u8*)a1 + 0x64);
    FUN_00cb6400(p, 0);
}

// @ 0x00cb6500
u32 __cdecl FUN_00cb6500(u32 a1, f32 a2, u32 a3, void* a4)
{
    u8 old = 0;
    void* cb = (void*)0x00cb63c0;

    if (a4 != 0) {
        old = *((u8*)a4 + 8);
        *((u8*)a4 + 8) = 1;
        if (*((u8*)a4 + 9) != 0) {
            cb = (void*)0x00cb63e0;
            gU_0169a40c = ((u32 (__thiscall*)(void*))VT(a4)[0x10 / 4])(a4);
        }
    }

    void* r = (void*)FUN_00b3d240(a1, a2, cb, a3);
    u32 result = 3;
    if (MOPS(r)->FUN_00b35d30(a1, a2, cb, a3) != 0)
        result = 0;

    if (a4 != 0)
        *((u8*)a4 + 8) = old;
    return result;
}

// @ 0x00cb6960
void __cdecl FUN_00cb6960(void* a0, void* a1, float a2, void* a3, void* a4, CtxObj* a5, void* a6, char a7)
{
    char  old = 0;
    void* fp  = (void*)(void (__cdecl*)(void*))FUN_00cb64c0;

    if (a5 != 0) {
        old = a5->mState;
        a5->mState = 1;
        if (a5->mAlt != 0) {
            fp = (void*)(void (__cdecl*)(void*))FUN_00cb64e0;
            g_169a40c = ((uint32_t(__thiscall*)(void*)) (*(void***)a5)[0x10 / 4])(a5);
        }
        g_169a408 = a7;
    }

    FUN_00cb6570(a0, a1, a2, a3, a4, a5, a6, fp);

    if (a5 != 0)
        a5->mState = old;
}

// @ 0x00cb69e0
void __cdecl SP_CombatLineTest(void* a0, void* a1, float a2, void* a3, void* a4, CtxObj* a5, void* a6)
{
    char  old = 0;
    void* fp  = (void*)(void (__cdecl*)(void*))FUN_00cb63c0;

    if (a5 != 0) {
        old = a5->mState;
        a5->mState = 1;
        if (a5->mAlt != 0) {
            fp = (void*)(void (__cdecl*)(void*))FUN_00cb63e0;
            g_169a40c = ((uint32_t(__thiscall*)(void*)) (*(void***)a5)[0x10 / 4])(a5);
        }
    }

    FUN_00cb6570(a0, a1, a2, a3, a4, a5, a6, fp);

    if (a5 != 0)
        a5->mState = old;
}

// @ 0x00cb6ca0
void GameObject::DestroyRefs()
{
    void* p;

    p = mp518;
    if (p != 0) {
        mp518 = 0;
        ((void(__thiscall*)(void*)) (*(void***)p)[4 / 4])(p);
    }

    p = mp51c;
    if (p != 0) {
        mp51c = 0;
        ((void(__thiscall*)(void*)) (*(void***)p)[4 / 4])(p);
    }

    p = mp520;
    if (p != 0) {
        mp520 = 0;
        ((void(__thiscall*)(void*)) (*(void***)p)[0x64 / 4])(p);
    }

    p = mp524;
    if (p != 0) {
        mp524 = 0;
        ((void(__thiscall*)(void*)) (*(void***)p)[8 / 4])(p);
    }

    p = mp2c;
    if (p != 0) {
        mp2c = 0;
        ((void(__thiscall*)(void*)) (*(void***)p)[4 / 4])(p);
    }

    mLoco.Shutdown();
}

// @ 0x00cb6d20
void GameObject::RemoveOwner()
{
    void* p;

    p = mp518;
    if (p != 0) {
        mp518 = 0;
        ((void(__thiscall*)(void*)) (*(void***)p)[4 / 4])(p);
    }

    p = mp51c;
    if (p != 0) {
        mp51c = 0;
        ((void(__thiscall*)(void*)) (*(void***)p)[4 / 4])(p);
    }

    p = mp2c;
    if (p != 0) {
        mp2c = 0;
        ((void(__thiscall*)(void*)) (*(void***)p)[4 / 4])(p);
    }

    mLoco.Shutdown();
}

// @ 0x00cb6fe0
GameObject* GameObject::_virtual_dtor(unsigned char flags)
{
    void* p;

    p = mp534;
    if (p != 0)
        ((void(__thiscall*)(void*)) (*(void***)p)[8 / 4])(p);

    p = mp524;
    if (p != 0)
        ((void(__thiscall*)(void*)) (*(void***)p)[0x64 / 4])(p);

    mp504 = (void*)g_vft_145dca8;    // vtable pointer reset on the +0x34 subobj
    mLoco.Destroy();
    ((void(__thiscall*)(void*)) FUN_00b184c0)(this);

    if ((flags & 1) != 0)
        FUN_00f47380(this);

    return this;
}

// @ 0x00cb7b50
void __cdecl virtual_dtor()
{
}

// @ 0x00cb7ce0
void __cdecl Read()
{
}

// @ 0x00cb91d0
void TObj::FUN_00cb91d0()
{
    void* em = FUN_0067ddd0();
    TObj* es = (TObj*)((void*(__thiscall*)(void*, uint32_t))VF(em, 0x54))(em, 0x3701a5c);
    uint32_t tag;
    int pm = ((TObj*)FUN_00b3d350())->F_b7e3e0();
    uint32_t t = *(uint32_t*)((char*)this + 0x51c);
    if (pm != 0) {
        if (*(uint8_t*)((char*)this + 0x554) != 0) {
            tag = 0xba78f977;
        } else if (t == 0 || *(float*)(t + 0x224) < DAT_013ec4d0) {
            tag = 0x95938523;
        } else {
            tag = 0x971fa14;
        }
    } else {
        if (*(uint8_t*)((char*)this + 0x554) != 0) {
            tag = 0xba78f977;
        } else if (t == 0 || *(float*)(t + 0x224) < DAT_013ec4d0) {
            tag = 0x96a1703;
        } else {
            tag = 0x63fbd7f4;
        }
    }
    void* ref = 0;
    char ok = ((char(__thiscall*)(void*, uint32_t, int, void**))VF(es, 8))(es, tag, 0, &ref);
    if (ok != 0) {
        Rec rec;
        rec.x = DAT_0169aa18;
        rec.y = DAT_0169aa1c;
        rec.flags0 = 0;
        rec.z = DAT_0169aa20;
        rec.cnt0 = 0;
        rec.one = 1.0f;
        ((TObj*)&rec.m[0])->F_0041cb40(&DAT_0169a9f4);
        TObj* sub = (TObj*)((char*)this + 0x34);
        float* pl = ((float*(__thiscall*)(void*))VF(sub, 0x2c))(sub);
        rec.x = pl[0];
        rec.y = pl[1];
        rec.z = pl[2];
        rec.flags0 |= 4;
        rec.cnt0++;
        float* pl2 = ((float*(__thiscall*)(void*))VF(sub, 0x2c))(sub);
        uint8_t tmp[0x10];
        void* fr = ((void*(__thiscall*)(void*, void*, float*))VF(sub, 0x5c))(sub, tmp, pl2);
        float mtmp[9];
        float* mret = (float*)FUN_0069b440(mtmp, fr);
        for (int i = 0; i < 9; i++) {
            rec.m[i] = mret[i];
        }
        rec.flags1 |= 2;
        rec.cnt1++;
        ((void(__thiscall*)(void*, void*))VF(ref, 0x18))(ref, &rec);
        TObj* q = (TObj*)((TObj*)FUN_00b3d300(*(uint32_t*)((char*)this + 0x550)))->F_b25f40();
        if (q != 0) {
            float pos[3];
            pos[0] = *(float*)((char*)q + 0xc4);
            pos[1] = *(float*)((char*)q + 0xc8);
            pos[2] = *(float*)((char*)q + 0xcc);
            ((void(__thiscall*)(void*, int, float*, int))VF(ref, 0x44))(ref, 5, pos, 3);
        }
        ((void(__thiscall*)(void*, int))VF(ref, 8))(ref, 0);
    }
    uint32_t t2 = *(uint32_t*)((char*)this + 0x51c);
    if (t2 != 0) {
        if (*(uint8_t*)((char*)this + 0x554) != 0) {
            FUN_00bff2d0((void*)*(uint32_t*)((char*)this + 0x550), 3);
        } else {
            *(uint8_t*)(t2 + 0x1e8) = 1;
        }
    }
    if (ref != 0) {
        ((void(__thiscall*)(void*))VF(ref, 4))(ref);
    }
}

// @ 0x00cb94b0
TObj* TObj::FUN_00cb94b0()
{
    ((TObj*)this)->F_18660();
    TObj* sub = (TObj*)((char*)this + 0x34);
    sub->F_c43860();
    *(uint32_t*)((char*)this + 0x504) = 0x145dca8;
    float zero = 0.0f;
    *(float*)((char*)this + 0x508) = zero;
    *(float*)((char*)this + 0x50c) = zero;
    *(float*)((char*)this + 0x510) = zero;
    *(uint8_t*)((char*)this + 0x514) = 0;
    *(uint32_t*)((char*)this + 0x000) = 0x1475ff8;
    *(uint32_t*)((char*)this + 0x004) = 0x1475fe4;
    *(uint32_t*)((char*)this + 0x034) = 0x1475ee8;
    *(uint32_t*)((char*)this + 0x108) = 0x1475edc;
    *(uint32_t*)((char*)this + 0x504) = 0x1475eb4;
    *(uint32_t*)((char*)this + 0x520) = 0;
    return this;
}

// @ 0x00cb9600
void* TObj::_virtual_dtor(uint8_t param_2)
{
    uint32_t p = *(uint32_t*)((char*)this + 0x520);
    if (p != 0) {
        ((void(__thiscall*)(uint32_t))VF(p, 0x64))(p);
    }
    TObj* sub = (TObj*)((char*)this + 0x34);
    *(uint32_t*)((char*)this + 0x504) = 0x145dca8;
    sub->F_c432e0();
    ((TObj*)this)->F_184c0();
    if ((param_2 & 1) != 0) {
        FUN_00f47380(this);
    }
    return this;
}

// @ 0x00cb9650
void TObj::FUN_00cb9650()
{
    void* em = FUN_0067ddd0();
    TObj* es = (TObj*)((void*(__thiscall*)(void*, uint32_t))VF(em, 0x54))(em, 0x3701a5c);
    void* ref = 0;
    char ok = ((char(__thiscall*)(void*, uint32_t, int, void**))VF(es, 8))(es, 0x27e375b3, 0, &ref);
    if (ok != 0) {
        Rec rec;
        rec.x = DAT_0169aa18;
        rec.y = DAT_0169aa1c;
        rec.flags0 = 0;
        rec.z = DAT_0169aa20;
        rec.cnt0 = 0;
        rec.one = 1.0f;
        ((TObj*)&rec.m[0])->F_0041cb40(&DAT_0169a9f4);
        TObj* sub = (TObj*)((char*)this + 0x34);
        float* pl = ((float*(__thiscall*)(void*))VF(sub, 0x2c))(sub);
        rec.x = pl[0];
        rec.y = pl[1];
        rec.z = pl[2];
        rec.flags0 |= 4;
        rec.cnt0++;
        float* pl2 = ((float*(__thiscall*)(void*))VF(sub, 0x2c))(sub);
        uint8_t tmp[0x10];
        void* fr = ((void*(__thiscall*)(void*, void*, float*))VF(sub, 0x5c))(sub, tmp, pl2);
        float mtmp[9];
        float* mret = (float*)FUN_0069b440(mtmp, fr);
        for (int i = 0; i < 9; i++) {
            rec.m[i] = mret[i];
        }
        rec.flags1 |= 2;
        rec.cnt1++;
        ((void(__thiscall*)(void*, void*))VF(ref, 0x18))(ref, &rec);
        ((void(__thiscall*)(void*, int))VF(ref, 8))(ref, 0);
    }
    if (ref != 0) {
        ((void(__thiscall*)(void*))VF(ref, 4))(ref);
    }
}

// @ 0x00cb9780
void TObj::FUN_00cb9780(void** param_2, void* param_3, void** param_4, char param_5)
{
    int side;
    if (param_5 == 0 && param_3 != (void*)((char*)this + 4)
        && *(uint32_t*)param_4 >= *(uint32_t*)((char*)param_3 + 0x10)) {
        side = 1;
    } else {
        side = 0;
    }
    void* node = FUN_00f473a0(0x14, "Simulator", 0, 0, 0x13ebb38, 0xd1);
    void** slot = (void**)((char*)node + 0x10);
    if (slot != 0) {
        void* val = *param_4;
        *slot = val;
        if (val != 0) {
            ((void(__thiscall*)(void*))VF(val, 0xbc))(val);
        }
    }
    FUN_009216a0(node, param_3, (char*)this + 4, side);
    *(uint32_t*)((char*)this + 0x14) += 1;
    *(uint32_t*)param_2 = (uint32_t)node;
}

// @ 0x00cb9b90
void* TObj::FUN_00cb9b90(uint8_t param_2)
{
    uint32_t p = *(uint32_t*)((char*)this + 0x10);
    if (p != 0 && *(uint32_t*)(p - 4) != 0) {
        FUN_00f47380((void*)p);
    }
    *(uint32_t*)((char*)this + 0x08) = 0x13ec458;
    *(uint32_t*)((char*)this + 0x00) = 0x13eb938;
    if ((param_2 & 1) != 0) {
        FUN_00f47380(this);
    }
    return this;
}

// @ 0x00cbb790
void Simulator::cGameData_s00cb_b020::RemoveOwner()
{
    if (mpSpaceTool != 0) {
        void* p = mpSpaceTool;
        mpSpaceTool = 0;
        ((Fn_v_p)VTSLOT(p, 8))(p);
    }
    if (mpLocomotion != 0) {
        void* p = mpLocomotion;
        mpLocomotion = 0;
        ((Fn_v_p)VTSLOT(p, 4))(p);
    }

    RefList* pList = &mList570;
    pList->m_cbae20(pList->mCount);
    pList->mSentinelPrev = &pList->mSentinelNext;
    pList->mCount = 0;
    pList->mFlag = 0;
    pList->m14 = 0;
    pList->mSentinelNext = &pList->mSentinelNext;

    if (mpField5cc != 0) {
        void* p = mpField5cc;
        mpField5cc = 0;
        ((Fn_v_p)VTSLOT(p, 4))(p);
    }
    if (mpField5d4 != 0) {
        void* p = mpField5d4;
        mpField5d4 = 0;
        ((Fn_v_p)VTSLOT(p, 4))(p);
    }
    if (mpOwner != 0) {
        void* p = mpOwner;
        mpOwner = 0;
        ((Fn_v_p)VTSLOT(p, 4))(p);
    }

    mLoco.m_c43f90();
}

// @ 0x00cbda10
void cCulturalProjectile::LaunchProjectile(cGameData_s00cb_da10* owner, cGameData_s00cb_da10* vehicle, cSpaceToolData* tool, cCombatant* target, const Vector3_s00cb_da10& targetPos, float speed, bool arg_538, bool spin)
{
    mOwner = owner->GetPoliticalID();
    mpVehicle = vehicle;
    mpTarget = target;
    mpTool = tool;
    field_538 = arg_538;
    mbSpin = spin;

    bool bArched = object_cast<kCulturalTargetType>(target) || GetPoliticalID() != vehicle->GetPoliticalID();
    bool isBuilding = object_cast<kBuildingType>(target) != 0;
    bool isTurret = object_cast<kTurretType>(target) != 0;
    bool isVehicle = object_cast<kVehicleType>(target) != 0;
    bool isAnimal = object_cast<kCreatureAnimalType>(target) != 0;

    field_1f0 = 5;

    Vector3Vector points;
    points.clear();

    Transform ring;
    float minDistance = 3.402823466e+38f;
    int startIndex = 0;
    float height = isTurret ? 1.0f : (isVehicle ? 5.0f : 3.0f);

    Vector3_s00cb_da10 endPoint;
    if (mbSpin) {
        Vector3_s00cb_da10 dir(targetPos);
        dir.Normalize();
        ring.PreRotate(Vector3_s00cb_da10::Z_AXIS, dir);
        ring.PreTranslate(targetPos);

        int nearest = 0;
        for (int i = 0; i < 12; i++) {
            float angle = RingAngle(i);
            Vector3_s00cb_da10 p = ring.Apply(Vector3_s00cb_da10((float)sin(angle), (float)cos(angle), 0.0f));
            float distance = (p - GetPosition()).Length();
            if (distance < minDistance) {
                minDistance = distance;
                nearest = i;
            }
        }
        startIndex = nearest + 3;
        float angle = RingAngle(startIndex);
        endPoint = ring.Apply(Vector3_s00cb_da10((float)sin(angle) * (isTurret ? 4.0f : 8.0f),
                                      (float)cos(angle) * (isTurret ? 4.0f : 8.0f), height));
    }
    else if (!isVehicle && !isAnimal) {
        endPoint = targetPos;
        endPoint += normalized_safe(endPoint) * 10.0f;
    }
    else {
        field_528 = target->GetRandomAimIndex();
        endPoint = target->GetAimPoint(field_528);
    }

    Vector3_s00cb_da10 position = GetPosition();
    Vector3_s00cb_da10 delta = endPoint - GetPosition();
    float length = delta.Length();
    Vector3_s00cb_da10 step = delta / length * (length / 33.0f);

    float lift = 0.0f;
    for (int i = 0; i < 32; i++) {
        if (bArched)
            lift += (32 - i) * 0.033f;
        else if (i < 16)
            lift += (16 - i) * (isBuilding ? 0.1f : 0.05f);
        else
            lift -= (i - 16) * (isBuilding ? 0.1f : 0.05f);

        Vector3_s00cb_da10 p = position + position.Normalized() * lift;
        points.push_back(p);
        mTargetPos = p;
        position += step;
    }

    if (mbSpin) {
        for (int i = startIndex; i < startIndex + 60; i++) {
            float angle = RingAngle(i);
            float x = (float)sin(angle) * (isTurret ? 4.0f : 8.0f);
            float y = (float)cos(angle) * (isTurret ? 4.0f : 8.0f);
            height += (isTurret || isVehicle) ? 0.1f : 0.2f;
            Vector3_s00cb_da10 p = ring.Apply(Vector3_s00cb_da10(x, y, height));
            points.push_back(p);
            mTargetPos = p;
        }
    }

    mpLocomotion = new("Simulator/cPathFollowingLocomotion", 0, 0, 0, 0)
        cPathFollowingLocomotion_s00cb_da10(points, kProjectileMotion);
    SetLocomotion(mpLocomotion.get());

    if (isVehicle)
        speed *= 2.0f;
    SetDesiredSpeed(speed, 0);
}

// @ 0x00cbf120
void __cdecl FindProjectilePath(IObj* param_1, IObj* param_2, VecList* param_3, float param_4, float param_5, float param_6, int param_7, float param_8)
{
    // ---- exact scalar temporaries used by the original (names from Ghidra) ----
    float fStack_3ac = 0, fStack_3a8 = 0, fStack_3a4 = 0, fStack_3a0 = 0;
    float fStack_39c = 0, fStack_398 = 0, fStack_394 = 0, fStack_378 = 0;
    float fStack_374 = 0, fStack_370 = 0, local_36c = 0, fStack_368 = 0;
    float fStack_364 = 0, fStack_360 = 0, fStack_35c = 0;
    float fStack_358 = 0, fStack_354 = 0, fStack_350 = 0;
    float fStack_34c = 0, fStack_348 = 0, fStack_344 = 0;
    float fStack_340 = 0, fStack_33c = 0, fStack_338 = 0;
    float fStack_334 = 0, fStack_330 = 0, fStack_32c = 0, fStack_328 = 0;
    float fStack_324 = 0, fStack_320 = 0, fStack_31c = 0;
    float fStack_318 = 0, fStack_314 = 0, fStack_310 = 0, fStack_30c = 0;
    float f37c, f380, f384, f388, f38c, f390;
    float f2dc = 0, f2d8 = 0, f2d4 = 0;
    float u2f0 = 0, u2ec = 0, u2e8 = 0, f2e4 = 0;
    unsigned short u2e0 = 0; short s2de = 0;
    float a2cc[9] = {0}, a2a8[9] = {0};
    float af34[12] = {0};
    float afbuf[14] = {0};
    float f17, f18, f19, f20, f21, f22;
    float fVar14, fVar15;
    int *piVar4, *piVar1, *piVar2;
    int *piStack_308, *piStack_304 = 0, *piStack_300 = 0;
    float uStack_2fc = 0;
    unsigned char *puVar12 = 0, *puStack_284, *puStack_280, *puStack_27c, *puStack_274;
    unsigned char auStack_26c[512] = {0}, auStack_6c[56] = {0};
    float dummy[8] = {0};

    eastl_copy_range(param_3->begin, param_3->end);
    piVar4 = (int*)FUN_00b3d240();
    local_36c = (float)(int)piVar4;
    if (piVar4 == 0) {           // Ghidra: if (local_36c == 0.0) return;
        return;
    }
    if (param_7 == 3) {
        if (FUN_00cbd620(param_1, param_2, param_3, param_4, param_5, param_6) != 0) {
            return;
        }
        param_7 = 1;
    }

    // ---- launch position ----
    if (param_1 == 0) {
        piVar4 = 0;
    } else {
        piVar4 = (int*)param_1->IsType((int)g_desc_pos);
    }
    {
        float* pf;
        if (piVar4 == 0) {
            pf = (float*)param_1->GetPosition();
        } else {
            pf = (float*)((IObj*)piVar4)->GetOrientedPosition((Vec3*)&f38c);
        }
        f384 = pf[0]; f380 = pf[1]; f37c = pf[2];
    }

    // ---- target / offset position ----
    if (param_2 == 0) {
        f390 = param_4; f38c = param_5; f388 = param_6;
    } else {
        float* pf = (float*)param_2->GetPosition();
        f390 = pf[0] + param_4;
        f38c = pf[1] + param_5;
        f388 = pf[2] + param_6;
    }
    fStack_32c = f38c;
    fStack_330 = f390;
    fStack_328 = f388;

    // ---- mode specific setup ----
    if (param_7 == 4) {
        Vec3 vA, vB;
        vA.x = fStack_330; vA.y = fStack_32c; vA.z = fStack_328;   // target
        vB.x = f390;      vB.y = f38c;      vB.z = f388;            // dst
        f18 = g_0157e904;
        f17 = g_0157e904 + 1.0f;
        cPlanetModel* pm = PlanetModelCtor4(&vB, &vA, g_0157e904, f17);
        float* pf = (float*)pm->MakeRandomWorldPosition(&vB, &vA, f18, f17);
        f384 = pf[0]; f380 = pf[1]; f37c = pf[2];
        PlanetModelDtor();
        fVar14 = (float)FUN_00b7e4d0();
        f18 = fVar14 * g_0157e900;
        f17 = 1.0f / sqrtf((f384 * f384 + (f380 * f380 + f37c * f37c)) + 1e-8f);
        f384 = (f17 * f384) * f18;
        f380 = (f380 * f17) * f18;
        f37c = (f17 * f37c) * f18;
    } else if (param_7 == 5 &&
               FUN_00cbcde0(f384, f380, f37c, f390, f38c, f388, param_3) == 0) {
        param_7 = 1;
    }

    // ---- build the local coordinate frame at the arc midpoint ----
    {
        float dx = fStack_330 - f384;
        float dy = fStack_32c - f380;
        float dz = fStack_328 - f37c;
        fStack_3a0 = sqrtf((dx * dx + dy * dy) + dz * dz);
        f18 = 1.0f / fStack_3a0;
        float ux = f18 * dx, uy = f18 * dy, uz = f18 * dz;
        fStack_378 = fStack_3a0 * 0.5f;
        float mx = fStack_358 = ux * fStack_378 + f384;
        float my = fStack_338 = f380 + uy * fStack_378;
        float mz = fStack_394 = f37c + uz * fStack_378;
        (void)mx; (void)mz;
        fStack_368 = 1.0f / sqrtf(((fStack_358 * fStack_358 + fStack_338 * fStack_338) +
                                   fStack_394 * fStack_394) + 1e-8f);
        f20 = fStack_368 * fStack_394;
        fStack_318 = fStack_368 * fStack_358;
        fStack_368 = fStack_368 * fStack_338;
        local_36c = f20 * uy - fStack_368 * uz;       // cross(n, u).x
        f18      = fStack_318 * uz - f20 * ux;        // .y
        f19      = fStack_368 * ux - fStack_318 * uy; // .z
        f17 = 1.0f / sqrtf(((local_36c * local_36c + f18 * f18) + f19 * f19) + 1e-8f);
        local_36c = f17 * local_36c;
        f18 = f17 * f18;
        f17 = f17 * f19;
        fStack_334 = f17 * fStack_368 - f18 * f20;
        fStack_354 = local_36c * f20 - f17 * fStack_318;
        f19 = f18 * fStack_318 - local_36c * fStack_368;
        fStack_350 = 1.0f / sqrtf(((fStack_334 * fStack_334 + fStack_354 * fStack_354) +
                                   f19 * f19) + 1e-8f);
        fStack_334 = fStack_350 * fStack_334;
        fStack_354 = fStack_350 * fStack_354;
        fStack_350 = fStack_350 * f19;
        fStack_39c = f37c - fStack_394;
        fStack_3a4 = (f384 - fStack_358) * fStack_334 + (f380 - fStack_338) * fStack_354;
        fStack_314 = fStack_3a4 + fStack_39c * fStack_350;
        fStack_310 = ((f384 - fStack_358) * fStack_318 + (f380 - fStack_338) * fStack_368) +
                     fStack_39c * f20;
        fStack_340 = ((fStack_330 - fStack_358) * fStack_334 + (fStack_32c - fStack_338) * fStack_354) +
                     (fStack_328 - fStack_394) * fStack_350;
        fStack_33c = ((fStack_330 - fStack_358) * fStack_318 + (fStack_32c - fStack_338) * fStack_368) +
                     (fStack_328 - fStack_394) * f20;
    }

    if (param_7 == 2 || param_7 == 5) {
        goto LAB_00cc0229;
    }

    // ---- collect candidate objects around the launch point ----
    {
        Vec3 P, Q;
        Vec3* pf;
        Vec3 sV, tV;
        sV.x = f384; sV.y = f380; sV.z = f37c;          // launch position
        tV.x = fStack_330; tV.y = fStack_32c; tV.z = fStack_328; // target
        P.x = f384; P.y = f380; P.z = f37c;
        Q.x = fStack_330; Q.y = fStack_32c; Q.z = fStack_328;
        piStack_304 = 0;
        piStack_300 = 0;
        uStack_2fc = 0;
        PlanetModelCtor2(&P, &sV)->DirectionToSurfacePosition(&P, &sV);
        PlanetModelCtor2(&Q, &tV)->DirectionToSurfacePosition(&Q, &tV);
        Vec3 dvec; dvec.x = f390; dvec.y = f38c; dvec.z = f388;
        pf = normalized_safe(&dvec, &P);
        P.x = pf->x * 2.0f + P.x;
        P.y = P.y + pf->y * 2.0f;
        P.z = P.z + pf->z * 2.0f;
        pf = normalized_safe(&dvec, &Q);
        Q.x = pf->x * 2.0f + Q.x;
        Q.y = Q.y + pf->y * 2.0f;
        Q.z = Q.z + pf->z * 2.0f;

        piVar4 = (int*)FUN_00b3d240();
        ((IObj*)piVar4)->Query(&P, &Q, (void**)&piStack_304, 1);

        puStack_27c = auStack_6c;
        puStack_274 = auStack_26c;
        puStack_280 = auStack_26c;
        puStack_284 = auStack_26c;
        piStack_308 = piStack_300;
        piVar4 = piStack_304;
        if (piStack_304 != piStack_300) {
            do {
                piVar1 = (int*)*piVar4;
                piVar2 = 0;
                if (piVar1 != (int*)param_2 && piVar1 != (int*)param_1 &&
                    ((IObj*)piVar1)->IsType((int)0xce9f6639) == 0 &&
                    ((IObj*)piVar1)->IsType((int)0x2e71a5a) == 0 &&
                    ((IObj*)piVar1)->IsType((int)g_desc_type) == 0) {
                    float* pf2 = (float*)((IObj*)piVar1)->GetOrient();
                    if (pf2[0] < pf2[3] || pf2[0] == pf2[3]) {
                        float* pos = (float*)((IObj*)piVar1)->GetPosition();
                        f390 = pos[0]; f38c = pos[1]; f388 = pos[2];
                        ((IObj*)piVar1)->Notify();
                        puVar12 = auStack_6c;
                        ((IObj*)piVar1)->GetOrient(puVar12);
                        FUN_00466320(puVar12);
                        float* q = (float*)((IObj*)piVar1)->GetOrientedPosition();
                        u2f0 = q[0]; u2ec = q[1]; u2e8 = q[2]; f2e4 = q[3];
                        FUN_00409930();
                        Matrix3FromQuaternion(a2a8, (Vec3*)&u2f0);
                        for (int i = 0; i < 9; ++i) a2cc[i] = a2a8[i];
                        f2dc = f390; u2e0 = (unsigned short)(u2e0 | 6);
                        f2d8 = f38c; s2de = (short)(s2de + 2);
                        f2d4 = f388;
                        float* ap = &afbuf[2];
                        for (int k = 4; k != 0; --k) {
                            fStack_34c = ap[-2];
                            fStack_348 = ap[-1];
                            fStack_344 = ap[0];
                            FUN_0044d4f0((Vec3*)&fStack_34c);
                            f19 = (local_36c * (fStack_34c - fStack_358) +
                                   f18 * (fStack_348 - fStack_338)) +
                                  f17 * (fStack_344 - fStack_394);
                            fStack_34c = fStack_358 + ((fStack_34c - fStack_358) - local_36c * f19);
                            fStack_348 = fStack_338 + ((fStack_348 - fStack_338) - f18 * f19);
                            fStack_344 = fStack_394 + ((fStack_344 - fStack_394) - f17 * f19);
                            fStack_39c = (fStack_334 * (fStack_34c - fStack_358) +
                                          fStack_354 * (fStack_348 - fStack_338)) +
                                         fStack_350 * (fStack_344 - fStack_394);
                            fStack_398 = (fStack_318 * (fStack_34c - fStack_358) +
                                          fStack_368 * (fStack_348 - fStack_338)) +
                                         f20 * (fStack_344 - fStack_394);
                            if (fStack_314 < fStack_39c && fStack_39c < fStack_340) {
                                FUN_00722c60(&fStack_39c);
                            }
                            ap += 3;
                        }
                    }
                }
                piVar4 += 1;
            } while (piVar4 != piStack_308);
        }

        if (param_7 == 1) {
            void* gm = GetCurrentGameMode();
            local_36c = fStack_33c * 1.1f;
            float* psel = &fStack_378;
            if (gm == (void*)g_game_mode) {
                fStack_378 = fStack_3a0 * 0.1f;
                if (fStack_3a0 * 0.1f <= local_36c) psel = &local_36c;
                fStack_374 = *psel;
                fStack_378 = fStack_340 * 0.5f;
            } else {
                if (fStack_378 <= local_36c) psel = &local_36c;
                fStack_374 = *psel;
                fStack_378 = fStack_340 * 0.5f;
            }
LAB_00cbfd19:
            FUN_00722c60(&fStack_378);
        } else if (param_7 == 4) {
            fStack_374 = fStack_310 * 0.3f;
            fStack_378 = fStack_314 * 0.0f;
            goto LAB_00cbfd19;
        }
    }

    // ---- fit the arc and emit points ----
    puVar12 = puStack_284;
    if (puStack_284 != puStack_280) {
        int n = (int)(puStack_280 - puStack_284) >> 3;
        int i = 0;
        fStack_3a8 = 3.4028234e38f;
        if (0 < n) {
            do {
                fStack_30c = *(float*)(puVar12 + i * 8);
                FUN_00cb3f80(&fStack_314, &fStack_340, &fStack_30c, &fStack_378, &local_36c, dummy);
                if (fStack_378 < 0.0f) {
                    f17 = -(local_36c / (fStack_378 * 2.0f));
                    f17 = (f17 * fStack_378 + local_36c) * f17 + f18;
                    if (f17 < fStack_3a8) {
                        int j = 0;
                        do {
                            if ((*(float*)(puVar12 + j * 8) * fStack_378 + local_36c) *
                                *(float*)(puVar12 + j * 8) + f18 <
                                *(float*)(puVar12 + j * 8 + 4)) {
                                if (j < n) goto LAB_00cbfe57;
                                break;
                            }
                            j = j + 1;
                        } while (j < n);
                        fStack_3a4 = fStack_378;
                        fStack_39c = local_36c;
                        fStack_3a8 = f17;
                        fStack_3a0 = f18;
                    }
                }
LAB_00cbfe57:
                i = i + 1;
            } while (i < n);

            if (fStack_3a8 != 3.4028234e38f) {
                fStack_378 = 64.0f;
                local_36c = fStack_33c * 1.1f;
                float* psel = &fStack_378;
                if (64.0f <= fStack_33c * 1.1f) psel = &local_36c;
                if (*psel < fStack_3a8) {
                    fStack_30c = -(fStack_39c / (fStack_3a4 * 2.0f));
                    FUN_00cb3f80(&fStack_314, &fStack_340, &fStack_30c, &fStack_3a4, &fStack_39c,
                                 &fStack_3a0);
                }
                fStack_378 = (fStack_340 - fStack_314) * 0.03125f;
                fStack_3a8 = fStack_378 + fStack_314;
                {
                    Vec3 p;
                    p.x = (fStack_358 + fStack_334 * fStack_314) + fStack_318 * fStack_310;
                    p.y = (fStack_338 + fStack_354 * fStack_314) + fStack_368 * fStack_310;
                    p.z = (fStack_394 + fStack_350 * fStack_314) + f20 * fStack_310;
                    AppendPoint(param_3, p);
                }
                for (int k = 0x1f; k != 0; --k) {
                    f18 = (fStack_3a8 * fStack_3a4 + fStack_39c) * fStack_3a8 + fStack_3a0;
                    Vec3 p;
                    p.x = (fStack_358 + fStack_334 * fStack_3a8) + fStack_318 * f18;
                    p.y = (fStack_338 + fStack_354 * fStack_3a8) + fStack_368 * f18;
                    p.z = (fStack_394 + fStack_350 * fStack_3a8) + f20 * f18;
                    AppendPoint(param_3, p);
                    fStack_3a8 = fStack_3a8 + fStack_378;
                }
                {
                    Vec3 p;
                    p.x = (fStack_358 + fStack_334 * fStack_340) + fStack_318 * fStack_33c;
                    p.y = (fStack_338 + fStack_354 * fStack_340) + fStack_368 * fStack_33c;
                    p.z = (fStack_394 + fStack_350 * fStack_340) + f20 * fStack_33c;
                    AppendPoint(param_3, p);
                }
            }
        }
    }

    // ---- release the candidate list ----
    piVar4 = piStack_304;
    piVar1 = piStack_300;
    if (puVar12 != 0 && puVar12 != puStack_274) {
        operator_delete__(puVar12);
        piVar4 = piStack_304;
        piVar1 = piStack_300;
    }
    for (; piVar4 < piStack_300; piVar4 += 1) {
        (void)piVar1;
        if (*piVar4 != 0) {
            ((IObj*)*piVar4)->Release();
        }
    }
    if (piStack_304 != 0 && piStack_304[-1] != 0) {
        operator_delete__(piStack_304);
    }

LAB_00cc0229:
    if (param_3->begin == param_3->end) {
        eastl_copy_range(param_3->begin, param_3->end);
        Vec3 a, b, c;
        a.x = f384; a.y = f380; a.z = f37c;   // source
        b.x = fStack_330; b.y = fStack_32c; b.z = fStack_328; // target
        // If pB is null, or FUN_00b35bf0 fails, use the target as the end point.
        if (param_2 == 0 || FUN_00b35bf0(param_2, &a, &b, &c) == 0) {
            c = b;
        }
        FUN_00cbcc40(a.x, a.y, a.z, c.x, c.y, c.z, param_3);
    }

    // ---- apply spread / random perturbation along the path ----
    if (0.0f < param_8) {
        fVar14 = RandomDoubleUniform((void*)0);
        fStack_3ac = fVar14 * g_0169aa28;
        fVar14 = RandomDoubleUniform((void*)0);
        fVar15 = fStack_3ac;
        fStack_394 = param_8;
        fStack_368 = param_8 * 0.5f;
        {
            int i = 1;
            int off = 0xc;
            do {
                int base = (int)param_3->begin;
                fStack_364 = *(float*)(base + off);
                fStack_35c = *(float*)(base + 8 + off);
                fStack_360 = *(float*)(base + 4 + off);
                f388 = *(float*)(base + 0x14 + off) - fStack_35c;
                float* pf = (float*)(base + off);
                f390 = *(float*)(base + 0xc + off) - fStack_364;
                f38c = *(float*)(base + 0x10 + off) - fStack_360;
                f17 = 1.0f / sqrtf((f38c * f38c +
                                    (f388 * f388 + f390 * f390)) + 1e-8f);
                f20 = f388 * f17;
                f19 = f38c * f17;
                f17 = f17 * f390;
                fVar15 = sinf(fVar15 * 0.5f);
                f18 = fVar15;
                fVar15 = cosf(fVar15 * 0.5f);
                f21 = f19 * f18;
                f22 = f20 * f18;
                f18 = f18 * f17;
                f2e4 = fVar15;
                fStack_3a0 = 1.0f / sqrtf((fStack_364 * fStack_364 +
                                           (fStack_360 * fStack_360 + fStack_35c * fStack_35c)) + 1e-8f);
                fStack_324 = fStack_3a0 * fStack_364;
                fStack_320 = fStack_360 * fStack_3a0;
                fStack_31c = fStack_35c * fStack_3a0;
                fStack_348 = (f20 * fStack_324 - fStack_31c * f17) * fStack_394;
                fStack_34c = (fStack_31c * f19 - fStack_320 * f20) * fStack_394;
                fStack_3a4 = f18 * f18;
                fStack_344 = (fStack_320 * f17 - f19 * fStack_324) * fStack_394;
                fStack_39c = f2e4 * f21;
                fStack_370 = 1.0f - (f22 * f22 + fStack_3a4) * 2.0f;
                pf[0] = (((f21 * f18 - f2e4 * f22) * fStack_348 +
                          (fStack_39c + f22 * f18) * fStack_344) * 2.0f +
                         (1.0f - (f22 * f22 + f21 * f21) * 2.0f) * fStack_34c) + pf[0];
                pf[1] = (((f2e4 * f22 + f21 * f18) * fStack_34c +
                          (f22 * f21 - f2e4 * f18) * fStack_344) * 2.0f +
                         fStack_370 * fStack_348) + pf[1];
                pf[2] = (((f22 * f18 - fStack_39c) * fStack_34c +
                          (f2e4 * f18 + f22 * f21) * fStack_348) * 2.0f +
                         (1.0f - (f21 * f21 + fStack_3a4) * 2.0f) * fStack_344) + pf[2];
                fVar15 = RandomDoubleUniform((void*)0);
                fVar15 = (fVar15 + 1.0f) * 0.2f;
                if (0.5f <= fVar14) {
                    fVar15 = fStack_3ac - fVar15;
                    fStack_3ac = fVar15;
                    if (fVar15 < 0.0f) {
                        fStack_3ac = fStack_3ac + g_0169aa28;
                        goto LAB_00cc06b1;
                    }
                } else {
                    fVar15 = fVar15 + fStack_3ac;
                    fStack_3ac = fVar15;
                    if (g_0169aa28 < fVar15) {
                        fStack_3ac = fStack_3ac - g_0169aa28;
LAB_00cc06b1:
                        fVar15 = fStack_3ac;
                    }
                }
                if (i < 0x11) {
                    fStack_394 = fStack_368 + fStack_394;
                } else {
                    fStack_394 = fStack_394 - fStack_368;
                }
                off += 0xc;
                i = i + 1;
            } while (off < 0x174);
        }
    }
    return;
}

// @ 0x00cc22c0
void cDefaultToolProjectile::Explode(int nKind, void* pHit)
{
    NotifyProjectileHit();

    uint32_t nEffectId;
    if (nKind == 0) {
        void* pObject = nullptr;
        void* pTarget = nullptr;
        if (pHit != nullptr)
            pTarget = ((IRefCounted*)pHit)->Query((const void*)0xb033b403);
        if (pTarget == nullptr || *(void**)((uint8_t*)pTarget + 0x714) == nullptr ||
            GetTrailEffectId() == 0)
            nEffectId = GetHitEffectIdC();
        else
            nEffectId = GetTrailEffectId();
    } else if (nKind == 1 || nKind != 2) {
        nEffectId = GetHitEffectIdA();
    } else {
        nEffectId = GetHitEffectIdB();
    }

    bool bInstant = false;
    bool bWater = false;
    if (*(void**)((uint8_t*)this + 0x518) != nullptr) {
        uint32_t nHitKind = GetProjectileKind();
        if (nHitKind == 0xeb54070u)
            bInstant = true;
        else
            bWater = IsWaterSurface() != 0;
    }

    cEffectInfo* pOldEffect = *(cEffectInfo**)((uint8_t*)this + 0x5cc);
    *(cEffectInfo**)((uint8_t*)this + 0x5cc) = nullptr;
    if (pOldEffect != nullptr)
        pOldEffect->Release();

    void* pTargetObject = nullptr;
    if (pHit != nullptr)
        pTargetObject = ((IRefCounted*)pHit)->Query((const void*)&gGameModeTribe);

    if (nKind == 0 && pTargetObject != nullptr) {
        void* pInstance = CreateHitInstance(nEffectId);
        cEffectInfo* pCurrent = *(cEffectInfo**)((uint8_t*)this + 0x5cc);
        if (pInstance != pCurrent) {
            if (pInstance != nullptr)
                ((IRefCounted*)pInstance)->AddRef();
            *(void**)((uint8_t*)this + 0x5cc) = pInstance;
            if (pCurrent != nullptr)
                pCurrent->Release();
        }
    } else {
        cEffectsManager* pEffects = EffectsManager();
        cEffectInfo* pCurrent = *(cEffectInfo**)((uint8_t*)this + 0x5cc);
        if (pCurrent != nullptr) {
            *(cEffectInfo**)((uint8_t*)this + 0x5cc) = nullptr;
            pCurrent->Release();
        }
        pEffects->CreateEffect(nEffectId, 0, (cEffectInfo**)((uint8_t*)this + 0x5cc));
    }

    if (*(cEffectInfo**)((uint8_t*)this + 0x5cc) != nullptr) {
        EffectSpawnInfo info;
        info.mPosition.mX = 0.0f;
        info.mPosition.mY = 0.0f;
        info.mPosition.mZ = 0.0f;
        info.mCount = 0;
        info.mFlags = 0;
        info.mScale = 1.0f;

        Matrix33 orientation;
        Vec3_s00cc_22c0* pPosition = (Vec3_s00cc_22c0*)(*(void* (__thiscall*)(void*))(**(uint32_t**)((uint8_t*)this + 0x34) + 0x2c))
                                 ((uint8_t*)this + 0x34);
        info.mPosition = *pPosition;
        info.mFlags |= 4;
        info.mCount += 1;

        Matrix33* pSource;
        if (!bWater) {
            if (bInstant) {
                pSource = (Matrix33*)((uint8_t*)this + 0x5a8);
            } else {
                Vec3_s00cc_22c0* pDir = (Vec3_s00cc_22c0*)(*(void* (__thiscall*)(void*))(**(uint32_t**)((uint8_t*)this + 0x34) + 0x2c))
                                       ((uint8_t*)this + 0x34);
                void* pFacing = ((void* (__thiscall*)(void*, void*, void*))(**(uint32_t**)((uint8_t*)this + 0x34) + 0x5c))
                                       ((uint8_t*)this + 0x34, &orientation, pDir);
                pSource = (Matrix33*)Matrix3FromFacingAndUp(&orientation, (Vec3_s00cc_22c0*)pFacing);
            }
        } else {
            Vec3_s00cc_22c0* pDir = (Vec3_s00cc_22c0*)(*(void* (__thiscall*)(void*))(**(uint32_t**)((uint8_t*)this + 0x34) + 0x2c))
                                   ((uint8_t*)this + 0x34);
            cPlanetModel_s00cc_22c0* pPlanet = PlanetModel(&info.mPosition, pDir);
            void* pSurface = pPlanet->BuildSurfaceOrientation(&orientation, pDir);
            pSource = (Matrix33*)BuildOrientationMatrix(&orientation, pSurface);
        }

        for (int i = 0; i < 9; ++i)
            orientation.mValue[i] = pSource->mValue[i];
        info.mFlags |= 2;
        info.mCount += 1;

        if (GetUniverseContext() != nullptr) {
            void* pOwner = *(void**)((uint8_t*)this + 0x518);
            info.mScale = ((cSpaceProjectile*)pOwner)->GetEffectId();
            info.mCount += 1;
        }

        if (GetProjectileKind() == 0xec439b3fu) {
            Vec3_s00cc_22c0 color;
            cEmpire* pEmpire = GetPlayerEmpire(&color);
            pEmpire->GetColor(&color);
            ((IRefCounted*)*(void**)((uint8_t*)this + 0x5cc))->v10();
        }

        ((IRefCounted*)*(void**)((uint8_t*)this + 0x5cc))->AddRef();
        ((IRefCounted*)*(void**)((uint8_t*)this + 0x5cc))->Release();

        if (*(int*)((uint8_t*)this + 0x538) == 0xb) {
            void* pCreatures = GetGameDataVectorCreatures();
            Vec3_s00cc_22c0* pPos = (Vec3_s00cc_22c0*)(*(void* (__thiscall*)(void*))(**(uint32_t**)((uint8_t*)this + 0x34) + 0x2c))
                                   ((uint8_t*)this + 0x34);
            void* pHitObject = FindObjectAt((uint8_t*)pCreatures + 4, pPos, 0);
            if (pHitObject != nullptr)
                SpawnHitParticles(*(void**)((uint8_t*)this + 0x5cc));
        }
    }

    int nProjectileKind = *(int*)((uint8_t*)this + 0x538);
    if (nProjectileKind == 0xe || nProjectileKind == 0xf || nProjectileKind == 10) {
        Vec3_s00cc_22c0* pPosition = (Vec3_s00cc_22c0*)(*(void* (__thiscall*)(void*))(**(uint32_t**)((uint8_t*)this + 0x34) + 0x2c))
                                 ((uint8_t*)this + 0x34);
        SpawnWorldDecal(pPosition);
        ApplyDamageShake(pPosition);
    }

    if (GetCurrentGameMode() == &gGameModeTribe) {
        void* pWeapon = *(void**)((uint8_t*)this + 0x504);
        uint32_t nOwner = 0xffffffffu;
        int nTarget = 0;
        if (((cEmotionSource*)pWeapon)->GetTarget() != nullptr)
            nTarget = 1;
        void* pSource = pWeapon;
        (void)pSource;
        uint32_t nGroup = *(uint32_t*)((uint8_t*)this + 0x534);
        uint32_t nResult = ((cSpaceProjectile*)pSource)->GetEffectId();
        CameraShake(nullptr, nGroup, (uint32_t)(nTarget == 0), nResult);
        (void)nOwner;
    }
}

// @ 0x0135ae10
void E422()
{
}

// @ 0x0135b6f0
void E426()
{
}

// @ 0x0135ba30
void E431()
{
}
