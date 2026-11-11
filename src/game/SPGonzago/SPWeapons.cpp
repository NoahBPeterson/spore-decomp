// src/game/SPGonzago/SPWeapons.cpp -- migrated from slice(s) s00cc15b0, s00cc0700, s00cbe640, s00cbcde0, s00cbbdc0, s00cba050, s00cb7e50, s0135ae10, s00cc22c0, s00cbf120, s00cbda10, s00cbb020, s00cb91d0, s00cb7310, s00cb6570, s00cb5620, s00cb44b0, s00cb2f70 by tools/migrate/rewrite.py
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
#include "SP/cGonzagoTimer.h"
#include "SP/cInteractableObject.h"
#include <intrin.h>
#include <xmmintrin.h>
#include "SP/cCombatant.h"
#define __PLACEMENT_NEW_INLINE   // the slices' own placement new/delete win over <new>'s (rewrite.py)
#include <new>
#include "SP/cCity.h"
#include "SP/cSPGameDataUFO.h"
#include "SP/cAttachment.h"
#include "SP/cTribe.h"

// ---- items of slice s00cb2f70 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct VObj { void** vt; };
typedef void* (__thiscall *FnVp0)(void*);
bool __cdecl EA_IO_WriteUint32(void* s, const void* p, uint32_t n, int endian); // 0x0093aa70
bool __cdecl EA_IO_ReadInt32(void* s, void* p, uint32_t n, int endian);         // 0x0093a780
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
#define BARYDEN ((((((f7 * f3 - f7 * f2) + f10 * f2) - f10 * f1) + f9 * f1) - f9 * f3))
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
struct IObj_s00cc_0700;
struct Tool {                                  // cSPSpaceToolData
    char pad[0x114];
    EA::AutoRefCount<IObj_s00cc_0700> mpToolOwner;  // +0x114
    bool IsValid();                            // 0x0104cd80
};
struct CTarget { bool IsValid(); };            // 0x0104cd80, thiscall, ret bool
struct cLocomotionBase {
    char pad[0x30];
    void* mTarget;                           // +0x30
    bool HasLiveTarget();                    // 0x00cb4a40
};
struct cLocomotionObj14 {
    char pad[0x14];
    Tool* mpTool;                            // +0x14
    bool HasLiveTarget14();                  // 0x00cb4ca0
    void* GetToolStrategy();                 // 0x00cb5420
};
struct cLocomotionObj518 {
    char pad[0x34];
    char mSub[0x4e4];                        // +0x34 embedded object with its own vptr
    void* mpTool;                            // +0x518
    void GetPositions(Vector3* a, Vector3* b);   // 0x00cb5450
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
struct C_0104be60 { char pad[0x1dc]; float field; float Get(); };            // 0x0104be60
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
extern "C" double __cdecl sqrt(double x);
#pragma intrinsic(sqrt)
int   FUN_00cb6570(void*, void*, float, void*, void*, void*, void*, void*); // 0x00cb6570 cdecl
u8 FUN_00cb64c0(void*);                        // 0x00cb64c0 default callback
void  FUN_00cb64e0();                        // 0x00cb64e0 alt callback
u8 FUN_00cb63c0(void*);                        // 0x00cb63c0 default callback
void  FUN_00cb63e0();                        // 0x00cb63e0 alt callback
void  FUN_00f47380(void*);                   // 0x00f47380 cdecl operator delete[]
void  FUN_00c421b0();                        // 0x00c421b0 thiscall
void  FUN_00b184c0();                        // 0x00b184c0 thiscall cGameData dtor
char     g_169a408;   // 0x0169a408  byte flag store
uint32_t g_169a40c;   // 0x0169a40c
void*    g_vft_145dca8[4];  // 0x0145dca8  vtable reset stored into +0x504
struct CtxObj {
    char _p000[0x08];
    char mState;                 // +0x08
    char mAlt;                   // +0x09
};
struct RefCnt {
    virtual void vf0();          // vtable[0]
    virtual void vf1();          // vtable[1]  Release
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
void* g_vft_13ec458[2];   // 0x013ec458  base vtable written into the new object
void* g_vft_1475164[2];   // 0x01475164
void* g_vft_1475114[2];   // 0x01475114
struct BallisticLocomotion {
    void* mpVt0;              // +0x00
    void* m04;                // +0x04
    void* mpVt8;              // +0x08
    void* m0c;                // +0x0c
};
struct Float3 { float x, y, z; };
Float3 g_waterPoint;                // 0x0169a414  world water-sphere centre
float  g_169a9e8[3];                // 0x0169a9e8  reference up vector
void* g_vft_1475470[2];             // 0x01475470
void* g_vft_147545c[2];             // 0x0147545c
void* g_vft_1475360[2];             // 0x01475360
void* g_vft_1475354[2];             // 0x01475354
void* g_vft_147532c[2];             // 0x0147532c
char g_13f94d4;                             // 0x013f94d4  interface-id descriptor
struct IPlanetProbe {
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0C();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1C();
virtual void s20();
virtual void s24();
virtual void s28();
virtual void s2C();
virtual void s30();
virtual void s34();
virtual void s38();
virtual void s3C();
virtual void s40();
virtual void s44();
virtual void s48();
virtual void s4C();
    virtual bool s50(const float* origin, const Float3* end, void* callback,
                     RefCnt** pHit, Float3* out, void* arg);      // 0x00cb6570
};
struct cPlanetModel_s00cb_6570 {
    void  SampleTerrain(Float3* out, const float* pos, const float* dir); // 0x00b82060
    float GetWaterHeight();                                               // 0x00b7e390
};
IPlanetProbe* __cdecl FUN_00b3d240_s00cb_6570();       // 0x00b3d240
char __cdecl FUN_005a9c40(const float*, const float*, const float*, float, float*); // 0x005a9c40 IntersectRaySphere
void  SP_QuaternionFromDirections(void*, const float*, const float*); // 0x00698180
void  FUN_00b18660();                       // 0x00b18660  SP::cGameData::cGameData
void  FUN_00c43860();                       // 0x00c43860
struct ArtilleryProjectile {
    void*  mpVt0;                    // +0x00
    void*  mpVt1;                    // +0x04
    char   _p008[0x34 - 0x08];
    void*  mpVtLoco;                 // +0x34
    char   _p038[0x108 - 0x38];
    void*  mpVt3;                    // +0x108
    char   _p10c[0x504 - 0x10c];
    void*  mpVt4;                    // +0x504
    float  mTargetOffset[3];         // +0x508
    char   mFlag;                    // +0x514
    char   _p515[0x524 - 0x515];
    void*  mpOwner;                  // +0x524
    int    mMinDamage;               // +0x528
    int    mMaxDamage;               // +0x52c
    int    mDamageType;              // +0x530
    void*  mTool;                    // +0x534

    void   ctor();
};
struct ILoco {
virtual void l00();
virtual void l04();
virtual void l08();
virtual void l0C();
virtual void l10();
virtual void l14();
virtual void l18();
virtual void l1C();
virtual void l20();
virtual void l24();
virtual void l28();
    virtual Float3* GetPosition();                  // slot 0x2c
virtual void l30();
virtual void l34();
    virtual void SetPosition(Float3* pos);          // slot 0x38
};
struct IHit {
    virtual void h00();                             // slot 0x00  AddRef
    virtual void h04();                             // slot 0x04  Release
    virtual void h08();
    virtual void* AsInterface(const void* id);      // slot 0x0c
    virtual uint32_t v10();                         // slot 0x10
};
struct IProjObj {
virtual void p00();
virtual void p04();
virtual void p08();
virtual void p0C();
virtual void p10();
virtual void p14();
virtual void p18();
virtual void p1C();
virtual void p20();
virtual void p24();
virtual void p28();
virtual void p2C();
virtual void p30();
virtual void p34();
virtual void p38();
virtual void p3C();
virtual void p40();
virtual void p44();
virtual void p48();
    virtual uint32_t v4C();                         // slot 0x4c
    virtual void v50();                             // slot 0x50
    virtual void v54();                             // slot 0x54
};
struct IToolData {
    void* GetStrategy();                            // 0x0104f930
};
struct IToolStrategy {
virtual void t00();
virtual void t04();
virtual void t08();
virtual void t0C();
virtual void t10();
virtual void t14();
virtual void t18();
virtual void t1C();
virtual void t20();
virtual void t24();
virtual void t28();
virtual void t2C();
    virtual void Use(void* tool, Float3* pos, uint32_t code, uint32_t unused); // slot 0x30
};
struct ProjSub {                     // view from the +0x504 sub-object
    void*  mpVt;                     // +0x000  (object +0x504)
    char   _p004[0x14 - 0x04];
    Float3 mPos;                     // +0x014  (object +0x518)
    void*  mpCtx;                    // +0x020  (object +0x524)
    char   _p024[0x30 - 0x24];
    void*  mpTool;                   // +0x030  (object +0x534)

    bool Update();                   // 0x00cb7110
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
extern "C" float __fastcall FUN_0104bdc0(void* self);                            // 0x0104bdc0 (this in ecx)
extern "C" unsigned int __fastcall FUN_0104bf10(void* self);                     // 0x0104bf10
extern "C" unsigned int __fastcall FUN_0104bef0(void* self);                     // 0x0104bef0
extern "C" float __stdcall FUN_0104bdb0(void* vec, int a, int b, int c);          // 0x0104bdb0 fill spatial-object vector
extern "C" float __fastcall FUN_00ce6940(void* self);                             // 0x00ce6940 (this in ecx)
extern "C" unsigned int __fastcall RandomUint32Uniform(void* self, unsigned int n);  // 0x00a68fb0
extern "C" void __fastcall FUN_00ad92d0(void* vec);                               // 0x00ad92d0 eastl::vector dtor
extern void* gMathRandom;                                                        // 0x01601760
extern float DAT_01485720;      // _HK_REAL_ONE
extern float DAT_013ec4d0;
extern float DAT_0169aa18;
extern float DAT_0169aa1c;
extern float DAT_0169aa20;
extern float DAT_0169a9f4;
#define VF(p, off) (*(void**)((char*)(*(void**)(p)) + (off)))
extern "C" void* __cdecl FUN_00b3d300(uint32_t);                                // SP::NounManager
extern "C" void* __cdecl FUN_00b3d240_s00cb_91d0(void);
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
struct ObjVec {
    void** mpBegin;   // +0x00
    void** mpEnd;     // +0x04
    void** mpCap;     // +0x08
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
extern const float gDefaultOrientation;
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
class cSPCreatureBase {
public:
    bool PlayIdleAnimation(int nAnimation, int bLoop);
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
class cGameNounManager_s00cc_22c0 {
public:
    void* GetGameDataVector(void* pA, void* pB, void* pC, void* pD, const void* pType);  // 0x00b21340 (cGameNounManager::GetGameDataVector)
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
cGameNounManager_s00cc_22c0* NounManager_s00cc_22c0();
void* NounManager_s00cc_22c0(uint32_t id);
uint8_t* GetGameDataVectorCreatures();
uint32_t GetHitEffectIdA();
uint32_t GetHitEffectIdB();
uint32_t GetHitEffectIdC();
uint32_t GetTrailEffectId();
uint32_t GetProjectileKind();
bool IsWaterSurface();
uint32_t GetAoEKind();
void* CreateHitInstance(uint32_t id);
void SpawnWorldDecal(const Vec3_s00cc_22c0* pPosition);
void* FindObjectAt(void* pVector, const Vec3_s00cc_22c0* pPosition, int a);
void ApplyDamageShake(const Vec3_s00cc_22c0* pPosition);
void CameraShake(const Vec3_s00cc_22c0* pPosition, uint32_t id, uint32_t a, uint32_t b);
void SpawnHitParticles(void* pEffect);
bool IsCinematicMode(int a);
void UpdateMissileEffect(void* pView, void* pEffect, int a);
void UpdateBeamEffect(void* pView, void* pEffect, int a);
void NotifyProjectileHit();
extern uint8_t gGameModeTribe;
// ---- items of slice s00cc22c0 end

// ---- items of slice s00cb7e50 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float g01477fbc;   // 200.0f  (mMaxBeamLength)
extern const float g01485720;   // 1.0f
extern const float g0157d350;   // locomotion speed scale
extern const float g0157d364;   // beam turn rate base
extern const float g013eeda0;   // 8.0f
extern const float g0169a414;   // AoE source offset x
extern const float g0169a418;   // AoE source offset y
extern const float g0169a41c;   // AoE source offset z
extern const float g0169a410;   // effect argument
extern const float g0147515c;   // effect argument
extern "C" void  __cdecl operator_delete(void* p);                                        // 0x00f47380
extern "C" void* __cdecl operator_new(unsigned int size, const char* name,
                                      int a, int b, int c, int d);                        // 0x00f473a0
extern "C" int   __cdecl cSPLivingUniverse_GetUniverseContext();                           // 0x01021080
Vector3*    Vec3Normalize(Vector3* out, const Vector3* in);                           // 0x00436ce0
Vector3*    QuaternionRotate(Vector3* out, const Vector3* v, const Quaternion* q);   // 0x0059aed0
Vector3*    RotateTowards(Vector3* out, const Vector3* from, const Vector3* to, float t); // 0x00b0fd00
Quaternion* QuaternionFromDirections_s00cb_7e50(Quaternion* out, const Vector3* from, const Vector3* to); // 0x00698180
extern const Vector3 kForward;     // 0x0169a9e8
extern const float   kTwoPi_s00cb_7e50;       // 0x0169aa28
inline float MaxSS(float a, float b) { return (a > b) ? a : b; }
inline float MinSS(float a, float b) { return (a < b) ? a : b; }
struct cSpatial {
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
    virtual const Vector3* GetPosition();                      // +0x2c
};
struct cLocomotive : cSpatial {
virtual void v30();
virtual void v34();
virtual void v38();
    virtual void SetOrientation(const Quaternion* q);                       // +0x3c
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
    virtual void GetForward(Vector3* out);                                  // +0x5c
    const Vector3& GetVelocity();                                           // 0x00d20610
};
struct cSPTimer_s00cb_7e50 {  // 0x00bc3190
    uint32_t data[8];
    uint64_t GetElapsedTime();  // 0x00bc3190 (cSPTimer::GetElapsedTime)
};
struct StepArgs {
    Vector3      mVelocity;    // +0x00 out
    uint32_t     pad0c;
    float        mDt;          // +0x10
    cLocomotive* mpLoco;       // +0x14
};
struct Steering {
    uint32_t pad00[4];
    float    mRadius;          // +0x10
    float    mWobbleRate;      // +0x14
    cSpatial* mpTarget;        // +0x18
    uint32_t pad1c;
    cSPTimer_s00cb_7e50 mTimer;           // +0x20
    float    mWobbleAngle;     // +0x40

    void Update(StepArgs* args);   // 0x00cb7e50
};
struct Vtbl {
    void* mSlots[0xc8];
};
typedef void  (__thiscall *VfnV)(void*);
typedef void* (__thiscall *VfnP)(void*);
typedef void* (__thiscall *VfnPU)(void*, unsigned int);
typedef float (__thiscall *VfnF0)(void*);
typedef int   (__thiscall *VfnIF)(void*, float);
enum {
    kVt00 = 0x00 / 4, kVt04 = 0x04 / 4, kVt08 = 0x08 / 4, kVt0C = 0x0c / 4,
    kVt2C = 0x2c / 4, kVt34 = 0x34 / 4, kVt60 = 0x60 / 4, kVt64 = 0x64 / 4,
    kVtC0 = 0xc0 / 4
};
extern Vtbl gVtbl013eb938;  // ??_7ITracerBase@Trace@EA@@6B@
extern Vtbl gVtbl013ec458;  // vtbl_cContentValidationSummarizer
extern Vtbl gVtbl0145dca8;  // PTR_FUN_0145dca8 (cIProjectile common)
extern Vtbl gVtbl014751b4;  // Simulator::cDefaultAoEArea
extern Vtbl gVtbl014751e0;  // Simulator::cDefaultAoEArea +0x34
extern Vtbl gVtbl014752a4;  // Simulator::cDefaultAoEArea +0x04
extern Vtbl gVtbl014752b8;  // Simulator::cDefaultAoEArea +0x00
extern Vtbl gVtbl01475738;  // Simulator::cSpaceDefenseMissile +0x518
extern Vtbl gVtbl014757a0;  // Simulator::cSpaceDefenseMissile +0x504
extern Vtbl gVtbl014757c8;  // Simulator::cSpaceDefenseMissile +0x108
extern Vtbl gVtbl014757d0;  // Simulator::cSpaceDefenseMissile +0x034
extern Vtbl gVtbl014758cc;  // Simulator::cSpaceDefenseMissile +0x004
extern Vtbl gVtbl014758e0;  // Simulator::cSpaceDefenseMissile +0x000
extern Vtbl gVtbl01475990;  // Simulator::cDefaultBeamProjectile +0x11c
extern Vtbl gVtbl014759ac;  // Simulator::cDefaultBeamProjectile +0x108
extern Vtbl gVtbl014759d8;  // Simulator::cDefaultBeamProjectile +0x034
extern Vtbl gVtbl01475a9c;  // Simulator::cDefaultBeamProjectile +0x004
extern Vtbl gVtbl01475ab0;  // Simulator::cDefaultBeamProjectile +0x000
extern Vtbl gVtbl01475b38;  // Simulator::cCulturalProjectile +0x504
extern Vtbl gVtbl01475b60;  // Simulator::cCulturalProjectile +0x108
extern Vtbl gVtbl01475b68;  // Simulator::cCulturalProjectile +0x004
extern Vtbl gVtbl01475b78;  // Simulator::cCulturalProjectile +0x000
extern Vtbl gVtbl01475bd0;  // Simulator::cCulturalProjectile +0x034
extern Vtbl gVtbl01475cf4;  // Simulator::cResourceProjectile +0x504
extern Vtbl gVtbl01475d1c;  // Simulator::cResourceProjectile +0x108
extern Vtbl gVtbl01475d28;  // Simulator::cResourceProjectile +0x034
extern Vtbl gVtbl01475e24;  // Simulator::cResourceProjectile +0x004
extern Vtbl gVtbl01475e38;  // Simulator::cResourceProjectile +0x000
class cGonzagoTimer {
public:
    uint32_t mPad00[8];            // +0x00..+0x1f
    void Construct();              // 0x00b63890
    void Destroy();                // 0x00b638b0
    void Restart();                // 0x00bc3130
};
class IVtblObject {
public:
    Vtbl* mpVtbl;                  // +0x00
};
class cSPSpaceToolData_s00cb_7e50 {
public:
    Vtbl* mpVtbl;                  // +0x00
    float FUN_00c41d40();          // 0x00c41d40  fld [ecx+0x1e0]
    float FUN_0104be50();          // 0x0104be50  fld [ecx+0x1d8]
};
class cInteractableObject : public IVtblObject {
public:
    void SetEffectId(int id);              // 0x00c3f160
    void FUN_00c3f1b0(float a, float b);   // 0x00c3f1b0
    void FUN_00c3f2d0(void* owner);        // 0x00c3f2d0
};
class cGameNounManager {
public:
    IVtblObject* CreateNoun(uint32_t nameHash);   // 0x00b20c60
};
extern "C" cGameNounManager* __cdecl NounManager();    // 0x00b3d300
class cSpaceDefenseMissileLocomotion {
public:
    Vtbl* volatile    mpVtbl;        // +0x00
    uint32_t m04;                    // +0x04
    Vtbl* volatile    mpVtbl8;       // +0x08
    uint32_t volatile m0c;           // +0x0c
    float    volatile mSpeed;        // +0x10
    float    volatile mTurnRate;     // +0x14
    void*    volatile mpTarget;      // +0x18
    uint32_t m1c;                    // +0x1c
    cGonzagoTimer mTimer;            // +0x20 (size 0x20)
    float    m40;                    // +0x40
    uint32_t m44;                    // +0x44
    cSpaceDefenseMissileLocomotion* Construct(float a, float b, void* target);   // 0x00cb54a0
};
class cGameDataBase {
public:
    Vtbl* mpVtbl00;                // +0x000
    Vtbl* mpVtbl04;                // +0x004
    uint32_t mPad08[11];           // +0x008..+0x033
    void Construct();              // 0x00b18660
    void Destroy();                // 0x00b184c0
};
class cLocomotiveBody {
public:
    Vtbl* mpVtbl;                  // +0x000 (+0x034)
    uint32_t mPad04[52];           // +0x004..+0xd3
    void Construct();              // 0x00c43860
    void Destroy();                // 0x00c432e0
    void FUN_00c421b0(void* locomotion);   // 0x00c421b0
};
class cSpatialBody {
public:
    Vtbl* mpVtbl;                  // +0x000 (+0x034)
    uint32_t mPad04[52];           // +0x004..+0xd3
    void Construct();              // 0x00c89630
    void Destroy();                // 0x00c8a420
};
class cProjSuperBody {
public:
    Vtbl* mpVtbl;                  // +0x000 (+0x108)
    uint32_t mPad04[60];           // +0x004..+0x0f3
    float mTargetPosX;             // +0x0f4 (+0x1fc)
    float mTargetPosY;             // +0x0f8 (+0x200)
    float mTargetPosZ;             // +0x0fc (+0x204)
    uint32_t mPad100[7];           // +0x100..+0x11b
    uint32_t mMode;                // +0x11c (+0x224)
    uint32_t mPad120[30];          // +0x120..+0x197
    float mField198;               // +0x198 (+0x2a0)
    uint32_t mPad19c[152];         // +0x19c..+0x3fb
};
class cProjectileBody {
public:
    Vtbl* volatile mpVtbl;         // +0x000
    float mTargetOffsetX;          // +0x004
    float mTargetOffsetY;          // +0x008
    float mTargetOffsetZ;          // +0x00c
    uint8_t mActionTriggered;      // +0x010
    uint8_t mPad11[3];             // +0x011..+0x013
};
inline void InitProjectileBody(cProjectileBody& body, uint32_t zero)
{
    __m128 z = _mm_setzero_ps();
    _ReadWriteBarrier();
    body.mpVtbl = &gVtbl0145dca8;
    _mm_store_ss(&body.mTargetOffsetX, z);
    _mm_store_ss(&body.mTargetOffsetY, z);
    _mm_store_ss(&body.mTargetOffsetZ, z);
    body.mActionTriggered = (uint8_t)zero;
}
class cCombatantBody {
public:
    Vtbl* mpVtbl;                  // +0x000 (+0x518)
    uint32_t mPad04[49];           // +0x004..+0xc7
    void Construct();              // 0x00bfd4e0
    void Destroy();                // 0x00bfcd00
};
class cInteractionBody {
public:
    Vtbl* mpVtbl;                  // +0x000 (+0x11c)
    uint32_t mPad04[5];            // +0x004..+0x017
    void Construct();              // 0x00ac03d0
    void Destroy();                // 0x00ac0520
};
class cSpaceDefenseMissile {
public:
    cGameDataBase     mBase;           // +0x000
    cLocomotiveBody   mLoco;           // +0x034
    cProjSuperBody    mProjSuper;      // +0x108
    cProjectileBody   mProj;           // +0x504
    cCombatantBody    mCombatant;      // +0x518
    cSPSpaceToolData_s00cb_7e50* mpTool;          // +0x5e0
    IVtblObject*      mpTarget;        // +0x5e4
    cGonzagoTimer     mLifeTimer;      // +0x5e8
    cInteractableObject* mpHitSphere;  // +0x608
    uint32_t          mPad60c;         // +0x60c

    void* FUN_00cb84f0();                                      // ctor
    void FUN_00cb86a0();                                       // dtor
    void FUN_00cb8760(const Vector3* pos, IVtblObject* target);
};
class cDefaultBeamProjectile_s00cb_7e50 {
public:
    cGameDataBase       mBase;                // +0x000
    cSpatialBody        mSpatial;             // +0x034
    cProjectileBody     mProj;                // +0x108
    cInteractionBody    mInteraction;         // +0x11c
    cSPSpaceToolData_s00cb_7e50*   mpTool;               // +0x134
    IVtblObject*        mpSource;             // +0x138
    float               mTargetPositionX;     // +0x13c
    float               mTargetPositionY;     // +0x140
    float               mTargetPositionZ;     // +0x144
    float               mHitPositionX;        // +0x148
    float               mHitPositionY;        // +0x14c
    float               mHitPositionZ;        // +0x150
    uint8_t             mActionTriggered;     // +0x154
    uint8_t             mbStopBeam;           // +0x155
    uint8_t             mPad156[2];           // +0x156..+0x157
    float               mMaxBeamLength;       // +0x158
    float               mProjectileScale;     // +0x15c
    float               mBeamDirectionX;      // +0x160
    float               mBeamDirectionY;      // +0x164
    float               mBeamDirectionZ;      // +0x168
    uint8_t             mbHittingGround;      // +0x16c
    uint8_t             mbHittingWater;       // +0x16d
    uint8_t             mOrientsToTerrain;    // +0x16e
    uint8_t             mbPassesThroughToTerrain;  // +0x16f
    float               mDamageRadius;        // +0x170
    float               mBeamTurnRate;        // +0x174
    uint32_t            mMsPerDamagePointLo;  // +0x178
    uint32_t            mMsPerDamagePointHi;  // +0x17c
    uint32_t            mPad180[16];          // +0x180..+0x1bf
    cGonzagoTimer       mLifeTimer;           // +0x1c0
    IVtblObject*        mTargetedCombatant;   // +0x1e0
    Vector3*            mPathBegin;           // +0x1e4
    Vector3*            mPathEnd;             // +0x1e8
    Vector3*            mPathCapacity;        // +0x1ec

    void* FUN_00cb88e0();                                    // ctor
    void FUN_00cb8b20();                                     // dtor
    void FUN_00cb8ba0(Vector3* start, Vector3* end);         // GetEndPoints
};
class cDefaultAoEArea_s00cb_7e50 {
public:
    cGameDataBase       mBase;                // +0x000
    cSpatialBody        mSpatial;             // +0x034
    cProjectileBody     mProj;                // +0x108
    cSPSpaceToolData_s00cb_7e50*   mpTool;               // +0x11c
    float               mSourceOffsetX;       // +0x120
    float               mSourceOffsetY;       // +0x124
    float               mSourceOffsetZ;       // +0x128
    float               mDamageRadius;        // +0x12c
    uint8_t             mbStopArea;           // +0x130
    uint8_t             mPad131[7];           // +0x131..+0x137
    cGonzagoTimer       mLifeTimer;           // +0x138
    uint32_t            mAccumulatedTimeLo;   // +0x158
    uint32_t            mAccumulatedTimeHi;   // +0x15c
    uint32_t            mCulturalTimeLo;      // +0x160
    uint32_t            mCulturalTimeHi;      // +0x164
    uint32_t            mLastUpdateLo;        // +0x168
    uint32_t            mLastUpdateHi;        // +0x16c
    void* FUN_00cb8cd0();                                    // ctor
};
class cCulturalProjectile_s00cb_7e50 {
public:
    cGameDataBase       mBase;                // +0x000
    cLocomotiveBody     mLoco;                // +0x034
    cProjSuperBody      mProjSuper;           // +0x108
    cProjectileBody     mProj;                // +0x504
    IVtblObject*        mPathLocomotion;      // +0x518
    IVtblObject*        mpVehicle;            // +0x51c
    IVtblObject*        mpTarget;             // +0x520
    cSPSpaceToolData_s00cb_7e50*   mpTool;               // +0x524
    uint32_t            mField528;            // +0x528
    uint32_t            mPad52c[3];           // +0x52c..+0x537
    uint8_t             mbExplode;            // +0x538
    uint8_t             mbSpin;               // +0x539
    uint8_t             mPad53a[6];           // +0x53a..+0x53f
    cGonzagoTimer       mLifeTimer;           // +0x540
    uint32_t            mOwner;               // +0x560
    uint32_t            mPad564;              // +0x564
    cGonzagoTimer       mField568;            // +0x568
    void* FUN_00cb8dd0();                                    // ctor
    void FUN_00cb8f50();                                     // dtor
};
class cResourceProjectile {
public:
    cGameDataBase       mBase;                // +0x000
    cLocomotiveBody     mLoco;                // +0x034
    cProjSuperBody      mProjSuper;           // +0x108
    cProjectileBody     mProj;                // +0x504
    IVtblObject*        mPathLocomotion;      // +0x518
    IVtblObject*        mpNode;               // +0x51c
    uint32_t            mPad520[4];           // +0x520..+0x52f
    cGonzagoTimer       mLifeTimer;           // +0x530
    uint32_t            mOwner;               // +0x550
    void* FUN_00cb9010();                                    // ctor
    void* FUN_00cb9170(int flags);                           // deleting dtor
};
class cContentValidationSummarizer {
public:
    Vtbl*         mpVtblTracer;        // +0x00  ??_7ITracerBase@Trace@EA@@6B@
    uint32_t      mPad04;              // +0x04
    Vtbl*         mpVtblSelf;          // +0x08  vtbl_cContentValidationSummarizer
    uint32_t      mPad0c[3];           // +0x0c..+0x17
    IVtblObject*  mpField18;           // +0x18
    uint32_t      mPad1c;              // +0x1c
    cGonzagoTimer mTimer;              // +0x20
    void* FUN_00cb84b0(int flags);     // deleting dtor
};
// ---- items of slice s00cb7e50 end

// ---- items of slice s00cba050 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float DAT_01470f1c;                     // 0x01470f1c  2.0f   guide arrival radius
extern float DAT_01486110;                     // 0x01486110  5.0f   ICBM ground clearance
extern float DAT_01471064;                     // 0x01471064  0.5f   radius half
extern float DAT_013eeda0;                     // 0x013eeda0  8.0f   radius scale
extern float DAT_0147515c;                     // 0x0147515c  FLT_MAX
struct Matrix3Rows { float m[3][3]; };
typedef void  (__thiscall *Fn_v_pp)(void*, void*);
typedef void  (__thiscall *Fn_v_pf)(void*, float);
typedef void  (__thiscall *Fn_v_pi)(void*, int);
typedef void* (__thiscall *Fn_p_p)(void*);
typedef void* (__thiscall *Fn_p_pi)(void*, int);
extern "C" void* DAT_013f94d4 = 0;             // 0x013f94d4  space-tool interface key
extern "C" void* gRandom = 0;                  // 0x01601760  EA::Random global (this)
struct Obj_s00cb_a050;
void*   __cdecl SP_PlanetModel(Vector3* pPos);                  // 0x00b3d350
void*   __cdecl SP_RelationshipManager();                       // 0x00b3d2c0
void*   __cdecl SP_EffectsManagerPtr();                         // 0x0067ddd0
void*   __cdecl SP_NounManager();                               // 0x00b3d300
void*   __cdecl SP_ToolManager();                               // 0x00b3d240
void*   __cdecl eastl_RBTreeIncrement(void* pNode);             // 0x00921580
void    __cdecl EA_IO_WriteUint32(int a, void* p, int n, int f); // 0x0093aa70
Vector3* __cdecl SP_NormalizedSafe(Vector3* pOut, Vector3* pV); // 0x00449c20
Matrix3Rows* __cdecl Matrix3FromFacingAndUp(Matrix3Rows* pOut, Vector3* pFacing,
                                            Vector3* pUp);      // 0x0069b440
int     __cdecl GetPlayerEmpireOrMinus1();                      // 0x00b1f9d0
unsigned __cdecl RandomUint32Uniform(unsigned range);           // 0x00a68fb0 (this=gRandom)
struct Obj_s00cb_a050 {
    int      m_8e7f80();                     // 0x008e7f80  damage state (this+0x34)
    void     m_b225d0(void* pNoun);          // 0x00b225d0  cGameNounManager::RemoveNoun
    void*    m_b25f40(void* pOwner);         // 0x00b25f40  noun lookup by owner
    bool     m_b81f90(Vector3* p);           // 0x00b81f90  IsPositionBelowSurface
    void     m_bfc460(int a);                // 0x00bfc460  store a at this+0x34
    Vector3* m_position();                   // vftable slot 0x2c
    void     m_setPosition(Vector3* p);      // vftable slot 0x38
};
struct cWorldXform {
    void*    mpVtable;                       // +0x00
};
struct cHitObject {
    uint32_t  mPad000[0x34 / 4];
    cWorldXform mLoco;                       // +0x034 (ends at +0x38)
    uint32_t  mPad038[(0xc4 - 0x38) / 4];
    Vector3   mPosition;                     // +0x0c4
    uint32_t  mPad0d0[(0x508 - 0xd0) / 4];
    uint32_t  m508;                          // +0x508
    uint32_t  mPad50c[(0x714 - 0x50c) / 4];
    int       mLiveHits;                     // +0x714
};
struct cSPSpaceToolData_s00cb_a050 {
    uint32_t mPad000[0x114 / 4];
    void*    mpTarget_114;                   // +0x114
    uint32_t mPad118[(0x1ac - 0x118) / 4];
    float    m1ac;                           // +0x1ac
    float    m1b0;                           // +0x1b0
    float    m1b4;                           // +0x1b4
    float    m1b8;                           // +0x1b8
    uint32_t mPad1bc[(0x1d0 - 0x1bc) / 4];
    float    m1d0;                           // +0x1d0
    uint32_t mPad1d4[(0x218 - 0x1d4) / 4];
    int      m218;                           // +0x218
    int      m21c;                           // +0x21c
    int      m220;                           // +0x220
    int      m224;                           // +0x224
    void     m_bfc460(int a);                // 0x00bfc460  store a at this+0x34
    float    GetDamageRadius(float a, float b, int c, int d, int e, int f);  // 0x0104be40
};
struct cSPObjectList {
    Obj_s00cb_a050**  mpBegin;
    Obj_s00cb_a050**  mpEnd;
    Obj_s00cb_a050**  mpCapacity;
    uint32_t mAllocator;
};
struct Vector3Vector_s00cb_a050 {
    Vector3* mpBegin;
    Vector3* mpEnd;
    Vector3* mpCapacity;
    uint32_t mAllocator;
    Vector3Vector_s00cb_a050() {}                        // (retail constructs in place at 0x00473460)
    void CopyFrom(const Vector3Vector_s00cb_a050& src);  // 0x00473460
};
struct cCulturalLocomotion {
    uint32_t mPad000[0x10 / 4];
    Vector3Vector_s00cb_a050 mPath;                     // +0x010
    uint32_t mPad020[(0x508 - 0x20) / 4];
    uint32_t mBlock508;                      // +0x508
    uint32_t mPad50c[(0xc50 - 0x50c) / 4];
    float    mRadius;                        // +0xc50
};
struct cSPTimer_s00cb_a050 {
    uint32_t mPad00[0x18 / 4];
    bool     mRunning;                       // +0x18
    uint64_t GetElapsedTime();               // 0x00bc3190  -> edx:eax
    void     Start();                        // 0x00bc30f0
    bool     IsRunning();                    // 0x00feba90  -> +0x18
};
namespace SP {
struct cSpaceDefenseMissile_s00cb_a050 {
    uint32_t          mPad000[0x34 / 4];
    cWorldXform       mLoco;                 // +0x034 (4 bytes, ends at +0x38)
    uint32_t          mPad038[(0x508 - 0x38) / 4];
    void*             mpVtable508;           // +0x508
    void*             mpField50c;            // +0x50c
    uint32_t          mPad510[(0x518 - 0x510) / 4];
    cSPSpaceToolData_s00cb_a050* mpTool518;             // +0x518
    cSPSpaceToolData_s00cb_a050* mpGuidance51c;         // +0x51c
    uint32_t          mPad520[(0x550 - 0x520) / 4];
    float             m550;                  // +0x550
    uint32_t          mPad554[(0x5e0 - 0x554) / 4];
    cSPSpaceToolData_s00cb_a050* mpDamageTool;          // +0x5e0
    void Explode();  // 0x00cba050 (SP::cSpaceDefenseMissile::Explode)
};
}
namespace SP {
struct cCombatant_s00cb_a050 {
    uint32_t mPad000[0x518 / 4];
    int  m_8e7f80();                                     // 0x008e7f80  damage state
    void m_bfcdd0(float f, int a, int b, int c, int d);  // 0x00bfcdd0  base TakeHit
    void TakeHit(float f, int a, int b, int c, int d);   // ret 0x14 0x00bfcdd0
};
}
namespace SP {
struct cCulturalProjectile_s00cb_a050 {
    uint32_t mPad000[0x34 / 4];
    cWorldXform mLoco;                       // +0x034  embedded locomotion/transform (ends +0x38)
    uint32_t mPad038[(0x518 - 0x38) / 4];
    void*    mpLocomotion;                   // +0x518
    void*    mpVehicle;                      // +0x51c
    void*    mpTarget;                       // +0x520
    void*    mpTool;                         // +0x524
    int      mAimIndex;                      // +0x528
    Vector3  mTargetPos;                     // +0x52c
    uint8_t  mbFlag538;                      // +0x538
    uint8_t  mbSpin539;                      // +0x539
    uint32_t mPad53c[(0x560 - 0x53c) / 4];
    uint32_t mOwner;                         // +0x560
    uint32_t mPad564[(0x568 - 0x564) / 4];
    cSPTimer_s00cb_a050 mTimer;                         // +0x568
    void Explode();  // 0x00cba690 (SP::cCulturalProjectile::Explode)
};
}
namespace SP {
struct cResourceProjectile_s00cb_a050 {
    uint32_t mPad000[0x1c / 4];
    Vector3  mEndPoint;                      // +0x01c
    uint32_t mPad028[(0x2c - 0x28) / 4];
    cSPTimer_s00cb_a050 mTimer;                         // +0x02c
    bool Update();
};
}
namespace SP {
struct cICBM {
    uint32_t mPad000[0x1c / 4];
    Obj_s00cb_a050*     mpGuidance_1c;                  // +0x01c
    bool Update();
};
}
struct cProjectileBase {
    void ExplodeResource();                  // 0x00cb91d0
    void ExplodeICBM();                      // 0x00cb9650
};
struct PropertyList {
    void*    mpNode0;                        // +0x00
    uint32_t m4;                             // +0x04  end sentinel marker
    void*    mpRoot;                         // +0x08
    uint32_t m0c[2];
    int      mCount;                         // +0x14
};
namespace Simulator {
struct cPathFollowingLocomotion_s00cb_a050 {
    void*    mpVftable0;                     // +0x00
    uint32_t mRefCount;                      // +0x04
    void*    mpVftable8;                     // +0x08
    uint32_t mField0c;                       // +0x0c
    Vector3Vector_s00cb_a050 mPath;                     // +0x10
    int      m20;                            // +0x20
    int      mDistanceFromLastPoint;         // +0x24
    float    mCurrentSegmentLength;          // +0x28
    float    mLastPointReached;              // +0x2c
    int      m30;                            // +0x30
    Vector3  mToNextPoint;                   // +0x34
    int      m40;                            // +0x40
    float    mLowestAltitude;                // +0x44
    float    mLastSpeed;                     // +0x48
    uint32_t m4c;                            // +0x4c

    cPathFollowingLocomotion_s00cb_a050(const Vector3Vector_s00cb_a050& points, int motionID);
    void PathUpdated();                      // 0x00cb4a70
};  // namespace Simulator
}
// ---- items of slice s00cba050 end

// ---- items of slice s00cbbdc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int vtbl_01476188[];   // 0x01476188
extern "C" int vtbl_0147633c[];   // 0x0147633c
extern "C" int vtbl_01476088[];   // 0x01476088
extern "C" int vtbl_01476080[];   // 0x01476080
extern "C" int vtbl_01476058[];   // 0x01476058
extern "C" int vtbl_0145dca8[];   // 0x0145dca8
extern "C" int vtbl_01476350[];   // 0x01476350
extern "C" int vtbl_01476240[];   // 0x01476240
extern "C" int vtbl_01476214[];   // 0x01476214
extern "C" float DAT_01485720;    // 0x01485720  (1.0f)
extern "C" float DAT_0169a414;    // 0x0169a414
extern "C" float DAT_0169a418;    // 0x0169a418
extern "C" float DAT_0169a41c;    // 0x0169a41c
extern "C" int PTR_FUN_013f94d4[];                                   // 0x013f94d4
void __fastcall SP_cGameData_ctor(void* self);            // 0x00b18660
void __fastcall FUN_00c43860(void* self);                 // 0x00c43860
void __fastcall cGonzagoTimer_ctor(void* self);           // 0x00b63890
int  __fastcall FUN_01021300_ret();                       // 0x01021300
int  __fastcall FUN_00c30c80(void* self);                 // 0x00c30c80
void __fastcall FUN_00bdbc20(void* self, int dummy, int a); // 0x00bdbc20
void* __cdecl do_copy(void* first, void* last, void* dst); // 0x006782c0
void* __cdecl eastl_vector_insert(void* dst, void* pos, unsigned int bytes); // 0x011e0744
void* __cdecl EAAllocate(unsigned int size, const char* file, int a, int b, int c, int line); // 0x00f473a0
int   __fastcall FUN_00829110(void* self, int dummy, int a, int b, int c); // 0x00829110
int   __fastcall FUN_00ac97a0(void* self, int dummy, void* a, void* b);    // 0x00ac97a0
int   __fastcall FUN_00ea0350(void* self, int dummy, void* a, void* b, void* c); // 0x00ea0350
int   __fastcall FUN_00b2ac90(void* self, int dummy, int count, void* src, void* dst); // 0x00b2ac90
void* __fastcall SpVector_erase(void* self, int dummy, void* first, void* last); // 0x0050f740
void  __fastcall SpVector_DoInsertValue(void* self, int dummy, void* pos, const Vector3* val); // 0x004b5ad0
int       __fastcall cSPTimer_IsRunning(void* self);                 // 0x00feba90
void      __fastcall cSPTimer_Restart(void* self);                   // 0x00bc3130
long long __fastcall cSPTimer_GetElapsedTime(void* self);            // 0x00bc3190
float     __fastcall FUN_0104bf60(void* self);                       // 0x0104bf60
void*     __cdecl    FUN_00b3d240_s00cb_bdc0();                                 // 0x00b3d240
void*     __cdecl    SP_EffectsManager();                            // 0x0067ddd0
char      __cdecl    FUN_0104cd70();                                 // 0x0104cd70
char      __cdecl    FUN_0104cd40();                                 // 0x0104cd40
void      __fastcall FUN_00bbec40(int a, int b);                     // 0x00bbec40
unsigned int __fastcall RandomUint32Uniform(void* self, int dummy, int range); // 0x00a1c530-style EA random
// ---- items of slice s00cbbdc0 end

// ---- items of slice s00cbcde0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kPiOver4;                                            // 0x0157d35c
extern float g_flightArcPiOver8;                                        // 0x0169aa6c
extern unsigned int g_flightArcPiOver8Guard;                            // 0x0169aa70
struct Vector3_s00cb_cde0 {
    float x, y, z;
    Vector3_s00cb_cde0() {}
    Vector3_s00cb_cde0(float a, float b, float c) : x(a), y(b), z(c) {}
    Vector3_s00cb_cde0(const Vector3_s00cb_cde0& o) : x(o.x), y(o.y), z(o.z) {}
};
static inline Vector3_s00cb_cde0 operator-(const Vector3_s00cb_cde0& a, const Vector3_s00cb_cde0& b) { return Vector3_s00cb_cde0(a.x - b.x, a.y - b.y, a.z - b.z); }
static inline Vector3_s00cb_cde0 operator+(const Vector3_s00cb_cde0& a, const Vector3_s00cb_cde0& b) { return Vector3_s00cb_cde0(a.x + b.x, a.y + b.y, a.z + b.z); }
static inline Vector3_s00cb_cde0 operator*(const Vector3_s00cb_cde0& a, float s) { return Vector3_s00cb_cde0(a.x * s, a.y * s, a.z * s); }
static inline Vector3_s00cb_cde0 operator*(float s, const Vector3_s00cb_cde0& a) { return Vector3_s00cb_cde0(s * a.x, s * a.y, s * a.z); }
static inline float Dot(const Vector3_s00cb_cde0& a, const Vector3_s00cb_cde0& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
static inline float Length(const Vector3_s00cb_cde0& a) { return sqrtf(a.x * a.x + a.z * a.z + a.y * a.y); }
static inline Vector3_s00cb_cde0 NormalizedSafe(const Vector3_s00cb_cde0& a) {
    float inv = 1.0f / sqrtf(a.x * a.x + a.y * a.y + a.z * a.z + 1e-8f);
    return inv * a;
}
static inline Vector3_s00cb_cde0 NormalizedSafeArc(const Vector3_s00cb_cde0& a) {
    float zz = a.z * a.z;
    float yy = a.y * a.y;
    float rr = zz + yy;
    float inv = 1.0f / sqrtf(rr + a.x * a.x + 1e-8f);
    return inv * a;
}
static const float kPi = 3.1415927f;                                    // 0x0157d364
static const float kTwoPi_s00cb_cde0 = 6.2831855f;                                 // 0x0169aa28
static inline float LengthXZY(const Vector3_s00cb_cde0& a) {
    return sqrtf(a.x * a.x + a.z * a.z + a.y * a.y);
}
static inline Vector3_s00cb_cde0 NormalizedXZY(const Vector3_s00cb_cde0& a) {
    float inv = 1.0f / sqrtf(a.x * a.x + a.z * a.z + a.y * a.y + 1e-8f);
    return inv * a;
}
struct sp_alloc { unsigned int d[2]; };
struct SpVectorV3 {                    // eastl::vector<Vector3, sp_vector_allocator>
    Vector3_s00cb_cde0* mpBegin;
    Vector3_s00cb_cde0* mpEnd;
    Vector3_s00cb_cde0* mpCapacity;
    sp_alloc mAllocator;
    void DoInsertValue(Vector3_s00cb_cde0* pos, const Vector3_s00cb_cde0& v);                 // 0x004b5ad0
    void push_back(const Vector3_s00cb_cde0& v) {
        if (mpEnd < mpCapacity) ::new((void*)mpEnd++) Vector3_s00cb_cde0(v);
        else DoInsertValue(mpEnd, v);
    }
};
struct PlanetModel_s00cb_cde0 {
    float GetRadius();                                                  // 0x00b7e4d0 (thiscall, float in st0)
    float DistanceBetweenPoints(const Vector3_s00cb_cde0* pA, const Vector3_s00cb_cde0* pB);  // 0x00b81470
};
PlanetModel_s00cb_cde0* __cdecl GetPlanetModel();                                  // 0x00b3d350 (SP::PlanetModel)
struct IPositioned {
virtual void p00();
virtual void p04();
virtual void p08();
virtual void p0c();
virtual void p10();
virtual void p14();
virtual void p18();
virtual void p1c();
virtual void p20();
virtual void p24();
virtual void p28();
    virtual Vector3_s00cb_cde0* GetPosition();                                     // +0x2c
};
// ---- items of slice s00cbcde0 end

// ---- items of slice s00cbe640 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const int kTypeA;                              // 0x013f94d4
struct Vector3_s00cb_e640 {
    float x, y, z;
    Vector3_s00cb_e640() {}
    Vector3_s00cb_e640(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3_s00cb_e640(const Vector3_s00cb_e640& v) : x(v.x), y(v.y), z(v.z) {}
};
class Obj_s00cb_e640 {
public:
virtual void v00();
virtual void v04();
    virtual Obj_s00cb_e640* GetObject();                        // 0x08
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
    virtual const Vector3_s00cb_e640* GetPosition();            // 0x2c
    virtual const Vector3_s00cb_e640* GetRotation();            // 0x30
    virtual void v34();
    virtual void SetPosition(const Vector3_s00cb_e640* p);      // 0x38 (on the projectile's embedded interface)
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
    virtual const float* GetBounds(float* tmp);      // 0x6c
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
    virtual Obj_s00cb_e640* Cast(const void* typeId);           // 0xb8
};
class Owner {
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
virtual void v2c();
virtual void v30();
virtual void v34();
    virtual void SetPosition(const Vector3_s00cb_e640* p);      // 0x38
    virtual void SetRotation(const Vector3_s00cb_e640* r);      // 0x3c
};
struct Ref { Obj_s00cb_e640* p; };   // intrusive smart pointer (just the raw pointer)
class TribeIface {
public:
virtual void v00();
virtual void v04();
    virtual Obj_s00cb_e640* v08();                              // 0x08
    virtual void v0c();
    virtual void* v10();                             // 0x10
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
    virtual void* GetTarget();                       // 0x54
};
class Tribe {
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
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
    virtual void* GetOwnerId();                      // 0x4c
    uint32_t pad04[(0x508 - 0x50) / 4];
    TribeIface iface508;                             // 0x508 (vptr)
};
class Ctx {
public:
    uint32_t pad[0x114 / 4];
    Ref r114;
    Ref r118;
    int GetCommContext();                            // 0x00ce6950 ([this+0x184])
    float GetSpeed();                                // 0x0104be50 ([this+0x1d8])
};
class RandomLC { public: unsigned RandomUint32Uniform(unsigned n); };   // 0x00a68fb0 (thiscall)
extern RandomLC sMathRandom;                                          // 0x01601760
struct Member {                                       // tribe member (type 0x1a55e4d)
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
    virtual int GetTypeId();                          // 0x38
    uint32_t pad04[(0x34 - 4) / 4];
    Obj_s00cb_e640 sub34;                                        // 0x34
    uint32_t pad38[(0x288 - 0x38) / 4];
    uint8_t b288;
    uint8_t flag289;                                  // 0x289
};
struct MemberVec { Member** mpBegin; Member** mpEnd; };
class Slot { public: uint32_t pad[0x70 / 4]; Ref r70; };
class Projectile;
class City;
class Caster {
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
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
    uint32_t pad04[(0x1d4 - 0x3c) / 4];
    uint8_t slotIndex;                                // 0x1d4
    City* GetCity();                                  // 0x00bd84e0 (thiscall, via slot 0x30)
};
class CityHall { public: uint32_t pad04[0x34 / 4]; Obj_s00cb_e640 sub34; };
class City {
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
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
    virtual void* GetOwnerId();                       // 0x4c
    CityHall* GetCityHall();                          // 0x00bd9b40 ([this+0x320])
    MemberVec* GetMembers();                          // 0x00c8e810 (&this[+0x340])
    void* GetCivilization();                          // 0x00bd9bf0 ([this+0x590])
    Slot* GetSlot(int index);                         // 0x00bd9e80
    uint32_t pad04[(0x750 - 0x50) / 4];
    float scale;                                      // 0x750
};
class Projectile {
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
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
    virtual void SetOwnerId(void* id);                // 0x48
    uint32_t pad04[(0x34 - 4) / 4];
    Obj_s00cb_e640 sub34;                                        // 0x34
    void Launch(void* owner, void* vehicle, void* tool, void* target, const Vector3_s00cb_e640* targetPos,
                float speed, bool arg538, bool spin);  // 0x00cbda10 (thiscall, ret 0x20)
};
class NounManager_s00cb_e640 {
public:
    Projectile* GetProjectile();                      // 0x00cb6ea0
    void* GetOwner(void* tribeOwner);                 // 0x00b25f40 (thiscall, ret 4)
};
NounManager_s00cb_e640* GetNounManager();                        // 0x00b3d300 (cdecl, returns a global)
struct GameTime { uint32_t pad[0x48 / 4]; uint32_t flags; };
GameTime* GetGameTimeManager();                       // 0x00b3d380
Tribe* CastTribe(const Ref* ref);                     // 0x00bd8440
void* CastCommodityNode(const Ref* ref);              // 0x00c9f020
void* CastSpatial(const Ref* ref);                    // 0x00ad2690
Caster* CastCaster(const Ref* ref);                   // 0x00cb45f0
class cSPTimer_s00cb_e640 { public: int64_t GetElapsedTime(); }; // 0x00bc3190 (thiscall, edx:eax)
class cAttackTick {
public:
    uint32_t pad00[0x14 / 4];
    Ctx* mpCtx;                 // 0x14
    uint32_t pad18[(0x28 - 0x18) / 4];
    bool mbGuard;               // 0x28
    uint8_t pad29[7];
    cSPTimer_s00cb_e640 mTimer;            // 0x30
    uint32_t pad34[(0x50 - 0x34) / 4];
    int64_t mTotal;             // 0x50
    uint64_t mSinceLaunch;      // 0x58
    int64_t mLast;              // 0x60

    bool Update();              // 0x00cbea20
};
// ---- items of slice s00cbe640 end

// ---- items of slice s00cc0700 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char g_013f94d4;   // type-id object passed to the Cast virtuals
struct cSPVector3_s00cc_0700;
struct Vector3_s00cc_0700 {
    float x, y, z;
    Vector3_s00cc_0700() {}
    Vector3_s00cc_0700(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3_s00cc_0700 operator-(const Vector3_s00cc_0700& o) const { return Vector3_s00cc_0700(x - o.x, y - o.y, z - o.z); }
    Vector3_s00cc_0700 operator+(const Vector3_s00cc_0700& o) const { return Vector3_s00cc_0700(x + o.x, y + o.y, z + o.z); }
    Vector3_s00cc_0700 operator*(float s) const { return Vector3_s00cc_0700(x * s, y * s, z * s); }
    float SquaredLength() const { return x * x + y * y + z * z; }
    float Length() const { return (float)sqrt(SquaredLength()); }
    inline cSPVector3_s00cc_0700 Normalized() const;
};
struct cSPVector3_s00cc_0700 : Vector3_s00cc_0700 {
    cSPVector3_s00cc_0700() {}
    cSPVector3_s00cc_0700(float ax, float ay, float az) { x = ax; y = ay; z = az; }
    cSPVector3_s00cc_0700(const Vector3_s00cc_0700& o) { x = o.x; y = o.y; z = o.z; }
    cSPVector3_s00cc_0700(const cSPVector3_s00cc_0700& o) { x = o.x; y = o.y; z = o.z; }
    cSPVector3_s00cc_0700& operator=(const Vector3_s00cc_0700& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
inline cSPVector3_s00cc_0700 Vector3_s00cc_0700::Normalized() const
{
    float len = Length();
    float inv = 1.0f / len;
    return cSPVector3_s00cc_0700(x * inv, y * inv, z * inv);
}
struct IObj_s00cc_0700 {
    virtual void v00();
    virtual void Release();                         // 0x04
    virtual void v08();
    virtual IObj_s00cc_0700* CastC(void* id);                  // 0x0c
    virtual int GetPoliticalID();                   // 0x10
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
    virtual cSPVector3_s00cc_0700 GetAimPoint(int part);          // 0x28
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
    virtual bool IsDestroyed();                     // 0x3c
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
    virtual IObj_s00cc_0700* Cast(void* id);                   // 0xb8
};
struct cSpaceToolData_s00cc_0700;
struct IToolStrategy_s00cc_0700 {
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
    virtual void OnHit(cSpaceToolData_s00cc_0700* tool, Vector3_s00cc_0700* pos, int hitType, int arg);  // 0x30
};
struct cSpaceToolData_s00cc_0700 {
    uint32_t pad0[0x114 / 4];
    IObj_s00cc_0700* mpOwner;        // 0x114
    IObj_s00cc_0700* mpTarget;       // 0x118 (intrusive_ptr<cSpatialObject>)
    int   mTargetPart;    // 0x11c
    bool  HasTargetAim();          // 0x0104cd30
    bool  IsHitScan();             // 0x0104cd60
    bool  DamageFlag();            // 0x0104cd70
    bool  IsReady();               // 0x0104bd50
    IToolStrategy_s00cc_0700* GetStrategy();  // 0x0104f930
};
struct VectorV3 { cSPVector3_s00cc_0700* mpBegin; cSPVector3_s00cc_0700* mpEnd; cSPVector3_s00cc_0700* mpCapacity;
    cSPVector3_s00cc_0700& back() { return *(mpEnd - 1); } };
int  PathPrefsForTool(cSpaceToolData_s00cc_0700* tool);                           // 0x00cb36e0
void FindProjectilePath(IObj_s00cc_0700* owner, IObj_s00cc_0700* target, VectorV3* path, cSPVector3_s00cc_0700 to, int prefs, float spread);  // 0x00cbf120
#define K_DIST_EPS   (*(const float*)0x013EC4B8)   // 1e-8f, ray/sphere epsilon
#define K_FLOAT_ZERO (*(const float*)0x01485378)   // _HK_REAL_ZERO
struct ISimSpatial {                                // sim's spatial data view
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
    virtual const cSPVector3_s00cc_0700& GetPosition();        // 0x2c
};
struct ISimOwner {                                  // sim's empire data view
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
    virtual int GetEmpireID();                      // 0x4c
};
struct cSimGameData {
    uint32_t mPad000[0x714 / 4];                    // +0x000
    int mSpeciesKind;                               // +0x714
};
struct ISim {
    virtual void v00();                             // 0x00
    virtual void v04();                             // 0x04
    virtual ISimSpatial* GetSpatial();              // 0x08
    virtual ISimOwner* GetOwner();                  // 0x0c
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
    virtual cSimGameData* GetGameData(const void* typeId);      // 0x5c
    bool TimedExpired();                            // 0x00bfc600
    void TimedAdd(uint32_t ms);                     // 0x00bfc640
};
struct cSimPtrVector {
    ISim** mpBegin;                                 // +0x00
    ISim** mpEnd;                                   // +0x04
    ISim** mpCapacity;                              // +0x08
};
struct cGameDataList {                              // vector returned by GetGameDataVector
    uint32_t mField000;                             // +0x00
    cSimPtrVector mVec;                             // +0x04
};
struct cGameNounManager_s00cc_0700 {
    cGameDataList* GetGameDataVector(void* collect, void* clear, void* collectSub,
                                     void* filter, const void* typeId);      // 0x00b21340
};
cGameNounManager_s00cc_0700* NounManager_s00cc_0700();                    // 0x00b3d300
int GetPlayerEmpireID();                            // 0x01021090
struct ILocomotion {                                // SmartPtr-managed behaviour (slots 0/4)
    virtual void AddRef();                          // 0x00
    virtual void Release();                         // 0x04
};
struct cLocomotiveView {                            // cLocomotiveObject at this+0x34
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
    virtual const cSPVector3_s00cc_0700& GetPosition();        // 0x2c
virtual void v30();
virtual void v34();
    virtual void SetPosition(const Vector3_s00cc_0700& pos);   // 0x38
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
    virtual void AddRef();                          // 0xbc
    virtual void Release();                         // 0xc0
    virtual void Advance(float deltaTime, int flags);   // 0xc4
    void SetLocomotion(ILocomotion* p);             // 0x00c421b0
};
struct cTargetObj {                                 // the projectile's target object
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
    virtual cSPVector3_s00cc_0700 GetAimPoint(int part);       // 0x28 (hidden return pointer)
    virtual const cSPVector3_s00cc_0700& GetPosition();        // 0x2c
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
    virtual cTargetObj* Cast(const void* typeId);   // 0xb8
    virtual void AddRef();                          // 0xbc
    virtual void Release();                         // 0xc0
};
struct cPathFollowingLocomotion_s00cc_0700 : ILocomotion {
    cPathFollowingLocomotion_s00cc_0700(VectorV3& path, void* motion);     // 0x00cbaf00
};
inline void* operator new(size_t size, const char* tag, int a, int b, int c, int d);
void HeapDelete(void* p);                           // 0x00f47380: operator delete(void*)
struct cToolData_s00cc_0700 {                                  // cSpaceToolData, members used here
    uint32_t mPad000[0x114 / 4];                    // +0x000
    IObj_s00cc_0700*    mpOwner;                               // +0x114
    IObj_s00cc_0700*    mpTarget;                              // +0x118
    int      mTargetPart;                           // +0x11c
    float GetSpread();                              // 0x0104bda0
    void* GetProjectileMotion();                    // 0x0104bd90
};
struct cPhaseTimer { uint32_t mData[8]; void Restart(); };      // 0x00bc3130
struct cDefaultToolProjectile_s00cc_0700 {
    uint32_t mvftable;                              // +0x000
    uint32_t mPad004[0x30 / 4];                     // +0x004
    cLocomotiveView mLocomotive;                    // +0x034
    uint32_t mPad038[(0x224 - 0x038) / 4];          // +0x038
    int      mProjectileState;                      // +0x224
    uint32_t mPad228[(0x518 - 0x228) / 4];          // +0x228
    cToolData_s00cc_0700* mpTool;                              // +0x518
    ILocomotion* mpLocomotion;                      // +0x51c
    cSPVector3_s00cc_0700 mLastPosition;                       // +0x520
    uint32_t mPad52c[(0x544 - 0x52c) / 4];          // +0x52c
    int      mBombPhase;                            // +0x544
    cPhaseTimer mPhaseTimer;                        // +0x548
    uint32_t mPad568[(0x58c - 0x568) / 4];          // +0x568
    cSPVector3_s00cc_0700 mPathEndPoint;                       // +0x58c
    int      mTargetPart;                           // +0x598
    cSPVector3_s00cc_0700 mStartPosition;                      // +0x59c
    uint32_t mPad5a8[(0x5d8 - 0x5a8) / 4];          // +0x5a8
    cTargetObj* mpTarget;                           // +0x5d8
    uint32_t mPad5dc[(0x5f0 - 0x5dc) / 4];          // +0x5dc

    void SetupPathFollowing(float deltaTime, cTargetObj* pTarget, cSPVector3_s00cc_0700* pPos);   // 0x00cc0870
};
template <class T> struct ScopedRef {               // AddRef on entry, Release on exit
    T* mpObject;
    explicit ScopedRef(T* p) : mpObject(p) { if (p) p->AddRef(); }
    ~ScopedRef() { if (mpObject) mpObject->Release(); }
};
// ---- items of slice s00cc0700 end

// ---- items of slice s00cc15b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(sqrt, cos)
struct cSPVector3_s00cc_15b0;
struct Vector3_s00cc_15b0 {
    float x, y, z;
    Vector3_s00cc_15b0() {}
    Vector3_s00cc_15b0(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    __forceinline float SquaredLength() const { return x * x + y * y + z * z; }
    __forceinline float Length() const { return (float)sqrt(SquaredLength()); }
    __forceinline cSPVector3_s00cc_15b0 Normalized_s00cc_15b0() const;
    __forceinline cSPVector3_s00cc_15b0 NormalizedSafe_s00cc_15b0() const;   // inlined SP::normalized_safe (epsilon 1e-8)
};
struct cSPVector3_s00cc_15b0 : Vector3_s00cc_15b0 {
    cSPVector3_s00cc_15b0() {}
    cSPVector3_s00cc_15b0(float ax, float ay, float az) { x = ax; y = ay; z = az; }
    cSPVector3_s00cc_15b0(const Vector3_s00cc_15b0& o) { x = o.x; y = o.y; z = o.z; }
    cSPVector3_s00cc_15b0(const cSPVector3_s00cc_15b0& o) { x = o.x; y = o.y; z = o.z; }
    cSPVector3_s00cc_15b0& operator=(const Vector3_s00cc_15b0& o) { x = o.x; y = o.y; z = o.z; return *this; }
    cSPVector3_s00cc_15b0 operator-() const { return cSPVector3_s00cc_15b0(-x, -y, -z); }
    cSPVector3_s00cc_15b0 operator*(float s) const { return cSPVector3_s00cc_15b0(x * s, y * s, z * s); }
    cSPVector3_s00cc_15b0 operator+(const Vector3_s00cc_15b0& o) const { return cSPVector3_s00cc_15b0(x + o.x, y + o.y, z + o.z); }
};
struct Matrix3_s00cc_15b0 { float m[9]; };
struct XformMsg {
    uint16_t flags;
    uint16_t count;
    Vector3_s00cc_15b0  pos;
    float    scale;
    Matrix3_s00cc_15b0  rot;
    XformMsg();
    void SetPosition(const Vector3_s00cc_15b0& v) { pos = v; flags |= 4; ++count; }
    void SetRotation(const Matrix3_s00cc_15b0& m) { rot = m; flags |= 2; ++count; }
};
#define VSLOT(n) virtual void _v##n();
struct IVisualEffect {
    VSLOT(0)
    virtual int Release();                                    // +0x04
    virtual void Start(int flags);                            // +0x08
    virtual void Stop(int flags);                             // +0x0c
    VSLOT(4) VSLOT(5)
    virtual void SetTransform(const XformMsg& xf);            // +0x18
};
struct cLocomotiveObject_s00cc_15b0 {
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9) VSLOT(10)
    virtual const Vector3_s00cc_15b0& GetPosition();                     // +0x2c
};
struct ResourceKey {
    uint32_t instanceID, typeID, groupID;
    bool operator==(const ResourceKey& o) const
    {
        return instanceID == o.instanceID && typeID == o.typeID && groupID == o.groupID;
    }
};
struct cSpaceToolData_s00cc_15b0 {
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5)
    virtual const ResourceKey* GetToolKey();                  // +0x18
    uint32_t pad04[(0x114 - 4) / 4];
    void* mp114;                                              // +0x114
    uint32_t GetEffectID();                                   // 0x0104bf10
};
struct cSPTimer_s00cc_15b0 {
    uint32_t mData[8];
    bool IsRunning();                                         // 0x00feba90
    void Restart();                                           // 0x00bc3130
    uint64_t GetElapsedTime();                                // 0x00bc3190
};
struct cCity;
struct sp_vector_cities {
    cCity** mpBegin; cCity** mpEnd; cCity** mpCapacity; const char* mAllocName;
    uint32_t pad10[2];                                        // +0x10 (allocator tail, size 0x14)
    sp_vector_cities& operator=(const sp_vector_cities& x);   // 0x01011cc0
    cCity** erase(cCity** first, cCity** last);               // 0x00e25bd0
};
struct GameDataVector { int pad; sp_vector_cities vec; };     // vector at +4
typedef void (__cdecl *GameDataFn)();
struct cAvatar;
struct cGameNounManager_s00cc_15b0 {
    GameDataVector* GetGameDataVector(GameDataFn a, GameDataFn b, GameDataFn c, GameDataFn d, const void* tag);   // 0x00b21340 (ret 0x14)
    void* FUN_00ace2c0();                                     // 0x00ace2c0
    cAvatar* GetAvatar();                                     // 0x00b1fdb0
};
cGameNounManager_s00cc_15b0* NounManager_s00cc_15b0();                              // 0x00b3d300
void __cdecl FUN_00cd7d10();
void __cdecl FUN_00d3d420();
void __cdecl FUN_00acdff0();
void __cdecl FUN_00accbb0();
void __cdecl FUN_00b1e500();
struct cDefaultToolProjectile_s00cc_15b0 {
    uint32_t pad00[0x34 / 4];
    cLocomotiveObject_s00cc_15b0 mLocomotive;                            // 0x34 (vptr only)
    uint32_t pad38[(0x518 - 0x38) / 4];
    cSpaceToolData_s00cc_15b0* mpTool;                                   // 0x518
    uint32_t pad51c[(0x538 - 0x51c) / 4];
    int mDamageType;                                          // 0x538
    uint32_t pad53c[(0x544 - 0x53c) / 4];
    int mBombPhase;                                           // 0x544
    cSPTimer_s00cc_15b0 mPhaseTimer;                                     // 0x548
    uint32_t pad568[(0x5cc - 0x568) / 4];
    IVisualEffect* mpEffect;                                  // 0x5cc
    uint32_t pad5d0[(0x5dc - 0x5d0) / 4];
    sp_vector_cities mWaveFrontTargetCities;                  // 0x5dc

    bool UpdateBombPhase1();
    void FireGravityWave(cSPVector3_s00cc_15b0 pos, cSPVector3_s00cc_15b0 dir);           // 0x00cc1890
    void FirePeaceBomb(cSPVector3_s00cc_15b0 pos, cSPVector3_s00cc_15b0 dir);             // 0x00cc0700
    void FireCashInfusion(cSPVector3_s00cc_15b0 pos, cSPVector3_s00cc_15b0 dir);          // 0x00cbc3c0
    void FirePlanetConversion(cSPVector3_s00cc_15b0 pos, cSPVector3_s00cc_15b0 dir);      // 0x00cbc7f0
};
struct cRefObj {
    virtual void AddRef();                                    // +0x00
    virtual void Release();                                   // +0x04
};
struct cCombatant_s00cc_15b0 : cRefObj {
    VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5)
    virtual void TriggerWave(float strength, int empireID, int a, const void* b, int c);   // +0x18
    VSLOT(7) VSLOT(8) VSLOT(9) VSLOT(10)
    virtual const Vector3_s00cc_15b0& GetPosition();                     // +0x2c
    VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15) VSLOT(16) VSLOT(17)
    VSLOT(18) VSLOT(19) VSLOT(20) VSLOT(21) VSLOT(22)
    virtual void* LookupAttachment(const void* key);          // +0x5c
    int GetState();                                           // 0x008e7f80: [this+0x34]
};
struct cAttachment : cRefObj {
    VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9)
    VSLOT(10) VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15) VSLOT(16) VSLOT(17)
    VSLOT(18) VSLOT(19) VSLOT(20) VSLOT(21) VSLOT(22) VSLOT(23) VSLOT(24) VSLOT(25)
    VSLOT(26) VSLOT(27) VSLOT(28) VSLOT(29) VSLOT(30) VSLOT(31) VSLOT(32)
    virtual void* GetTribe();                                 // +0x84
    void* GetTribeField();                                    // 0x00bce5c0: [this+0x688]
};
struct cCityObj : cRefObj {
    VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9)
    VSLOT(10) VSLOT(11) VSLOT(12) VSLOT(13)
    virtual int GetTag();                                     // +0x38
    VSLOT(15) VSLOT(16) VSLOT(17) VSLOT(18) VSLOT(19) VSLOT(20) VSLOT(21) VSLOT(22)
    VSLOT(23) VSLOT(24) VSLOT(25) VSLOT(26) VSLOT(27) VSLOT(28) VSLOT(29) VSLOT(30)
    VSLOT(31) VSLOT(32) VSLOT(33) VSLOT(34) VSLOT(35) VSLOT(36) VSLOT(37) VSLOT(38)
    VSLOT(39) VSLOT(40) VSLOT(41) VSLOT(42)
    virtual cCityObj* GetOwnerObj();                          // +0xac
    uint32_t pad04[(0x120 - 4) / 4];
    cCombatant_s00cc_15b0 mCombatant;                                    // +0x120
    uint32_t pad124[(0x158 - 0x124) / 4];
    float m158;                                               // +0x158
};
struct cGroundObj : cRefObj {
    uint32_t pad04[(0x588 - 4) / 4];
    cCombatant_s00cc_15b0 mCombatant;                                    // +0x588
};
struct Vec2b {
    cRefObj** mpBegin;                                        // +0x00
    cRefObj** mpEnd;                                          // +0x04
    cRefObj** mpCap;                                          // +0x08
    uint32_t  mPad0c;                                         // +0x0c
    cRefObj** mpInline;                                       // +0x10
    cRefObj*  mpBuf[32];                                      // +0x18
    Vec2b() { mpBegin = mpBuf; mpEnd = mpBuf; mpCap = mpBuf + 32; mpInline = mpBuf; }
    ~Vec2b();                                                 // 0x008e2b20 (Vec2b::Free)
    cRefObj** erase(cRefObj** first, cRefObj** last);         // 0x00e25bd0
};
struct RefVector {
    cRefObj** mpBegin;                                        // +0x00
    cRefObj** mpEnd;                                          // +0x04
    cRefObj** mpCap;                                          // +0x08
    uint32_t  pad0c;                                          // +0x0c
    uint32_t  pad10[2];                                       // +0x10 (size 0x14)
    void Construct(uint32_t count, const void* src);          // 0x00b93c60 (ret 8)
    ~RefVector();                                             // 0x00ae6970
    cRefObj** erase(cRefObj** first, cRefObj** last);         // 0x00e25bd0
};
struct RefVec {
    cRefObj** mpBegin;                                        // +0x00
    cRefObj** mpEnd;                                          // +0x04
    cRefObj** mpCap;                                          // +0x08
    uint32_t  pad0c;                                          // +0x0c
    uint32_t  pad10[2];                                       // +0x10 (size 0x14)
    void Construct(uint32_t count, const void* src);          // 0x00b93c60 (ret 8)
};
struct cTribeMemberList {
    cRefObj**   mpBegin;                                      // +0x00
    cRefObj**   mpEnd;                                        // +0x04
    cRefObj**   mpCap;                                        // +0x08
    const char* mAllocName;                                   // +0x0c
};
struct cCity {
    void* GetCityHall();                                      // 0x00bd9b40: [this+0x320]
};
struct cTribe : cCity {
    cTribeMemberList* GetMembers();                           // 0x00c8e810: this+0x340
    void CopyMembers(Vec2b* out);                             // 0x00be5700 (ret 4)
};
struct RandomLCG { uint32_t RandomUint32Uniform(uint32_t n); };   // 0x00a68fb0
RandomLCG* const gRandomLCG = (RandomLCG*)0x01601760;
struct cAvatar {
    void FUN_00ffa900(cCityObj* city, int id);                // 0x00ffa900 (ret 8)
};
struct cToolExtra {
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8)
    VSLOT(9) VSLOT(10) VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15) VSLOT(16)
    VSLOT(17) VSLOT(18) VSLOT(19) VSLOT(20) VSLOT(21) VSLOT(22) VSLOT(23) VSLOT(24)
    VSLOT(25) VSLOT(26) VSLOT(27) VSLOT(28) VSLOT(29) VSLOT(30) VSLOT(31) VSLOT(32)
    VSLOT(33) VSLOT(34) VSLOT(35) VSLOT(36) VSLOT(37) VSLOT(38) VSLOT(39) VSLOT(40)
    VSLOT(41) VSLOT(42) VSLOT(43) VSLOT(44) VSLOT(45)
    virtual void* Lookup(const void* key);                    // +0xb8
};
struct cToolThing {
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3)
    virtual int GetID();                                      // +0x10
};
cGameNounManager_s00cc_15b0* SpaceGameGet();                             // 0x01002bd0
void* __cdecl EAlloc(uint32_t size, const char* name, int a, int b, const char* file, int line);   // 0x00f473a0
void __cdecl EFree(void* p);                                  // 0x00f47380
cRefObj** __cdecl CopyRefs(cRefObj*** out, cRefObj** first, cRefObj** last, cRefObj** dest, uint32_t dummy);   // 0x00829110
// ---- items of slice s00cc15b0 end

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

// @ 0x00cb3f80
void __cdecl FUN_00cb3f80(float* a, float* b, float* c, float* out1, float* out2, float* out3)
{
    float f1  = c[0];
    float f2  = a[0];
    float f3  = b[0];
    float f4  = a[1];
    float f9  = f2 * f2;
    float f7  = f1 * f1;
    float f5  = b[1];
    float f6  = c[1];
    float f10 = f3 * f3;

    *out1 = (((((f6 * f3 - f5 * f1) - f6 * f2) - f4 * f3) + f4 * f1) + f5 * f2) / BARYDEN;
    *out2 = -((((((f5 - f6) * f9 + f7 * f4) - f10 * f4) + f10 * f6) - f7 * f5) / BARYDEN);
    *out3 = (((((f9 * f1 - f7 * f2) * f5 + (f10 * f6) * f2) - (f10 * f4) * f1)
              - (f9 * f6) * f3) + (f7 * f4) * f3) / BARYDEN;
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

struct ProjRefs {
    char pad[0x524];
    RefCounted* mpOwner; // +0x524, AddRef +0x60 / Release +0x64
    uint m528;
    uint m52c;
    uint m530;
    RefCounted* mpTool;  // +0x534, AddRef +4 / Release +8
    void Set(RefCounted* tool, uint v1, uint v2, uint v3, RefCounted* owner);
};

// @ 0x00cb4950
void ProjRefs::Set(RefCounted* tool, uint v1, uint v2, uint v3, RefCounted* owner)
{
    char* p = (char*)this + 0x528;
    *(uint*)p = v1;
    *(uint*)(p + 4) = v2;
    *(uint*)(p + 8) = v3;
    RefCounted* old = mpOwner;
    if (owner != old) {
        if (owner)
            owner->r60();
        mpOwner = owner;
        if (old)
            old->r64();
    }
    RefCounted* old2 = mpTool;
    if (tool != old2) {
        if (tool)
            tool->r04();
        mpTool = tool;
        if (old2)
            old2->r08();
    }
}

// The sub-object at +0x34 is the projectile's SP::cLocomotiveObject (its vptr is set by ctor 0x00cb6ed0);
// +0x2c, +0x524 and +0x534 are refcounted interface pointers, released in that order before it is shut down.
struct cLocomotiveMember_s00cb_49e0 {
    char pad[0x4f0];
    void Shutdown();                                                 // 0x00c43f90
};
struct cProjectileOwner_s00cb_49e0 {
    char pad[0x2c];
    RefCounted* mpLoco;                                              // +0x2c
    char pad30[4];
    cLocomotiveMember_s00cb_49e0 mLoco;                              // +0x34
    RefCounted* mpOwner;                                             // +0x524
    char pad528[0xc];
    RefCounted* mpTool;                                              // +0x534
    void Shutdown();                                                 // 0x00cb49e0
};

// @ 0x00cb49e0
void cProjectileOwner_s00cb_49e0::Shutdown()
{
    RefCounted* p = mpOwner;
    if (p) {
        mpOwner = 0;
        p->r64();
    }
    RefCounted* q = mpTool;
    if (q) {
        mpTool = 0;
        q->r08();
    }
    RefCounted* r = mpLoco;
    if (r) {
        mpLoco = 0;
        r->r04();
    }
    mLoco.Shutdown();
}

// @ 0x00cb4a40
bool cLocomotionBase::HasLiveTarget()
{
    if (mTarget && ((CTarget*)mTarget)->IsValid())
        return true;
    return false;
}

// @ 0x00cb4a70
void Simulator::cPathFollowingLocomotion_s00cb_a050::PathUpdated()
{
    if (m40 != 0x6a93cd4e)
        return;
    for (int i = 0; i <= mDistanceFromLastPoint; i++) {
        float sq = (float)sqrt((double)(mPath.mpBegin[i].x * mPath.mpBegin[i].x
                                        + mPath.mpBegin[i].y * mPath.mpBegin[i].y
                                        + mPath.mpBegin[i].z * mPath.mpBegin[i].z));
        if (mLowestAltitude < sq)
            mLowestAltitude = sq;
        if (mLastSpeed > sq)
            mLastSpeed = sq;
    }
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
    if (mpTool && mpTool->IsValid())
        return true;
    return false;
}

struct VertLoco {
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
    virtual Vector3* GetPosition();              // +0x2c
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void SetOrientation(Quaternion* q);  // +0x3c
    Vector3* GetVelocity();                      // 0x00d20610
};

extern Vector3 gVertDir; // 0x0169a9e8

// @ 0x00cb4cc0
void __stdcall f00cb4cc0(Vector3* self)
{
    VertLoco* obj = *(VertLoco**)((char*)self + 0x14);
    obj->GetPosition();
    Vector3* vel = (*(VertLoco**)((char*)self + 0x14))->GetVelocity();
    Vector3 v;
    v.x = vel->x;
    v.y = vel->y;
    v.z = vel->z;
    *self = v;
    Quaternion q;
    (*(VertLoco**)((char*)self + 0x14))->SetOrientation(
        QuaternionFromDirections_s00cb_7e50(&q, &gVertDir, &v));
}

// @ 0x00cb4d40
int f00cb4d40(int self, int a, int b, int c, int d, int e)
{
    // complex projectile configuration; complete but not byte-exact
    (void)self; (void)a; (void)b; (void)c; (void)d; (void)e;
    return 0;
}

// @ 0x00cb5050
float __fastcall f00cb5050(int self)
{
    if (((C_0104be60*)*(void**)(self + 0x4e4))->Get() > 0.0f)
        return ((C_0104be60*)*(void**)(self + 0x4e4))->Get();
    return ((float (__fastcall*)(void*))VT(self)[0xc8 / 4])((void*)self);
}

// Closest attempt for 0x00cb5090. Same size as retail. The y store
// `mov [esi+4], ecx` still lands before the z spill; retail spills z first.
struct StraightLoco {
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
    virtual Vector3* GetPosition();              // +0x2c
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void SetOrientation(Quaternion* q);  // +0x3c
    Vector3* GetVelocity();                      // 0x00d20610
};

extern Vector3 gStraightDir; // 0x0169a9e8

// @ 0x00cb5090
void __stdcall f00cb5090(Vector3* self)
{
    StraightLoco* obj = *(StraightLoco**)((char*)self + 0x14);
    obj->GetPosition();
    Vector3* vel = (*(StraightLoco**)((char*)self + 0x14))->GetVelocity();
    Vector3 v;
    v.x = vel->x;
    v.y = vel->y;
    v.z = vel->z;
    *self = v;
    float len = self->x * self->x + self->y * self->y + self->z * self->z;
    if (len > g_1em3) {
        Quaternion q;
        (*(StraightLoco**)((char*)self + 0x14))->SetOrientation(
            QuaternionFromDirections_s00cb_7e50(&q, &gStraightDir, &v));
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
    const EA::AutoRefCount<IObj_s00cc_0700>& owner = mpTool->mpToolOwner;
    if (owner)
        return owner->Cast(&g_013f94d4);
    return 0;
}

// @ 0x00cb5450
void cLocomotionObj518::GetPositions(Vector3* a, Vector3* b)
{
    void* tool = *(void**)(*(int*)((char*)this + 0x518) + 0x114);
    Vector3* p1 = (Vector3*)((void* (__thiscall*)(void*))VT(tool)[0x2c / 4])(tool);
    *a = *p1;
    Vector3* p2 = (Vector3*)((void* (__thiscall*)(void*))VT((char*)this + 0x34)[0x2c / 4])((char*)this + 0x34);
    *b = *p2;
}

// @ 0x00cb54a0
cSpaceDefenseMissileLocomotion* cSpaceDefenseMissileLocomotion::Construct(float maxSpeed,
                                                                         float turnRate,
                                                                         void* target)
{
    mpVtbl8 = (Vtbl*)0x13ec458;
    m0c = 0;
    mSpeed = maxSpeed;
    mpVtbl = (Vtbl*)0x14751a4;
    mpVtbl8 = (Vtbl*)0x1475194;
    mTurnRate = turnRate;
    mpTarget = target;
    if (target != 0)
        ((void (__thiscall*)(void*))VT(target)[0xbc / 4])(target);
    mTimer.Construct();
    m40 = 0.0f;
    mTimer.Restart();
    return this;
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

struct WeaponPredicateContext {
    u32 pad00[0x64 / 4];
    void* mpObject64;
};

// @ 0x00cb63c0
u8 __cdecl FUN_00cb63c0(void* a1)
{
    void* object = ((WeaponPredicateContext*)a1)->mpObject64;
    _ReadWriteBarrier();
    return FUN_00cb6310(object, 1);
}

// @ 0x00cb63e0
void __cdecl FUN_00cb63e0(void* a1)
{
    void* object = ((WeaponPredicateContext*)a1)->mpObject64;
    _ReadWriteBarrier();
    FUN_00cb6310(object, 0);
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
u8 __cdecl FUN_00cb64c0(void* a1)
{
    void* object = ((WeaponPredicateContext*)a1)->mpObject64;
    return FUN_00cb6400(object, 1);
}

// @ 0x00cb64e0
void __cdecl FUN_00cb64e0(void* a1)
{
    void* object = ((WeaponPredicateContext*)a1)->mpObject64;
    _ReadWriteBarrier();
    FUN_00cb6400(object, 0);
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

// @ 0x00cb6570
int __cdecl FUN_00cb6570(void* p1v, void* p2v, float fDist, void* pHitSlot, void* pOutSlot, void* a5, void* a6, void* callback)
{
    const float* p1  = (const float*)p1v;
    const float* p2  = (const float*)p2v;
    void**       ppHit = (void**)pHitSlot;
    float*       pOut  = (float*)pOutSlot;

    Float3 n;
    Float3 end;
    Float3 probe;
    Float3 terrain;
    RefCnt* pHit = 0;
    float fProbeDist;
    float fWaterT;
    float fTerrainDist;
    float fLenPlus = fDist + 1.0f;

    {
        double d2 = (double)p2[0] * (double)p2[0] +
                    ((double)p2[1] * (double)p2[1] + (double)p2[2] * (double)p2[2]);
        float inv = (float)(1.0 / sqrt(d2));
        n.x = p2[0] * inv;
        n.y = p2[1] * inv;
        n.z = p2[2] * inv;
    }

    end.x = p1[0] + n.x * fDist;
    end.y = p1[1] + n.y * fDist;
    end.z = p1[2] + n.z * fDist;

    fProbeDist = fLenPlus;
    if (FUN_00b3d240_s00cb_6570()->s50(p1, &end, callback, &pHit, &probe, a6)) {
        double dx = (double)probe.x - p1[0];
        double dy = (double)probe.y - p1[1];
        double dz = (double)probe.z - p1[2];
        fProbeDist = (float)sqrt((dx * dx + dy * dy) + dz * dz);
    }

    end.x = g_waterPoint.x;
    end.y = g_waterPoint.y;
    end.z = g_waterPoint.z;
    fWaterT = fLenPlus;

    {
        cPlanetModel_s00cb_6570* planet = (cPlanetModel_s00cb_6570*)FUN_00b3d350();
        float water = planet->GetWaterHeight();
        float len2  = (p1[1] * p1[1] + p1[2] * p1[2]) + p1[0] * p1[0];
        if (len2 >= water * water
            && FUN_005a9c40(p1, &n.x, &g_waterPoint.x, water, &fWaterT) != 0) {
            if (fWaterT > fDist) {
                fWaterT = fLenPlus;
            } else {
                end.x = p1[0] + n.x * fWaterT;
                end.y = p1[1] + n.y * fWaterT;
                end.z = p1[2] + n.z * fWaterT;
            }
        }
    }

    {
        cPlanetModel_s00cb_6570* planet = (cPlanetModel_s00cb_6570*)FUN_00b3d350();
        planet->SampleTerrain(&terrain, p1, &n.x);
    }

    fTerrainDist = fLenPlus;
    if (terrain.x != g_waterPoint.x || terrain.y != g_waterPoint.y ||
        terrain.z != g_waterPoint.z) {
        double dx = (double)terrain.x - p1[0];
        double dy = (double)terrain.y - p1[1];
        double dz = (double)terrain.z - p1[2];
        fTerrainDist = (float)sqrt((dx * dx + dy * dy) + dz * dz);
    }

    int   code;
    float fSelected;
    if (fWaterT > fTerrainDist) {
        if (fProbeDist > fTerrainDist) {
            pOut[0] = terrain.x;
            pOut[1] = terrain.y;
            pOut[2] = terrain.z;
            code = 1;
            fSelected = fTerrainDist;
        } else {
            pOut[0] = probe.x;
            pOut[1] = probe.y;
            pOut[2] = probe.z;
            code = 0;
            fSelected = fProbeDist;
        }
    } else {
        if (fProbeDist > fWaterT) {
            pOut[0] = end.x;
            pOut[1] = end.y;
            pOut[2] = end.z;
            code = 2;
            fSelected = fWaterT;
        } else {
            pOut[0] = probe.x;
            pOut[1] = probe.y;
            pOut[2] = probe.z;
            code = 0;
            fSelected = fProbeDist;
        }
    }

    if (fDist < fSelected) {
        pOut[0] = p1[0] + n.x * fDist;
        pOut[1] = p1[1] + n.y * fDist;
        pOut[2] = p1[2] + n.z * fDist;
        if (pHit != 0)
            pHit->vf1();
        return 3;
    }

    if (code == 0) {
        RefCnt* old = (RefCnt*)*ppHit;
        if (pHit != old) {
            if (pHit != 0)
                pHit->vf0();
            *ppHit = pHit;
            if (old != 0)
                old->vf1();
        }
    }
    if (pHit != 0)
        pHit->vf1();
    return code;
}

// @ 0x00cb6960
void __cdecl FUN_00cb6960(void* a0, void* a1, float a2, void* a3, void* a4, CtxObj* a5, void* a6, char a7)
{
    char  old = 0;
    void* fp  = (void*)(u8 (__cdecl*)(void*))FUN_00cb64c0;

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
    void* fp  = (void*)(u8 (__cdecl*)(void*))FUN_00cb63c0;

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

// @ 0x00cb6a50
uint32_t __cdecl FUN_00cb6a50(float* p1, float* p2, float dist, float* out)
{
    float px = g_waterPoint.x;
    float py = g_waterPoint.y;
    float pz = g_waterPoint.z;
    float t  = dist + 1.0f;
    float t0 = t;

    cPlanetModel_s00cb_6570* planet = (cPlanetModel_s00cb_6570*)FUN_00b3d350();
    float water  = planet->GetWaterHeight();
    float x      = p1[0];

    if (water * water <= (x * x + p1[1] * p1[1]) + p1[2] * p1[2]
        && FUN_005a9c40(p1, p2, &g_waterPoint.x, water, &t) != 0) {
        if (t <= dist) {
            px = x + p2[0] * t;
            py = p1[1] + p2[1] * t;
            pz = p1[2] + p2[2] * t;
        } else {
            t = t0;
        }
    }

    Float3 s;
    cPlanetModel_s00cb_6570* planet2 = (cPlanetModel_s00cb_6570*)FUN_00b3d350();
    planet2->SampleTerrain(&s, p1, p2);

    if (s.x != g_waterPoint.x || s.y != g_waterPoint.y || s.z != g_waterPoint.z)
        t0 = (float)sqrt((((double)s.z - p1[2]) * ((double)s.z - p1[2]) +
                          ((double)s.y - p1[1]) * ((double)s.y - p1[1])) +
                         ((double)s.x - x) * ((double)s.x - x));

    uint32_t r;
    if (t <= t0) {
        out[0] = px;
        out[1] = py;
        out[2] = pz;
        r = 2;
    } else {
        out[0] = s.x;
        out[1] = s.y;
        out[2] = s.z;
        r = 1;
        t = t0;
    }

    if (dist < t) {
        out[0] = x + p2[0] * dist;
        out[1] = p1[1] + p2[1] * dist;
        out[2] = p1[2] + p2[2] * dist;
        r = 3;
    }
    return r;
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

// @ 0x00cb6dc0
void GameObject::SetForwardDir(void* arg)
{
    void* loco = (void*)&mLoco;
    float* v = (float*)((void*(__thiscall*)(void*)) (*(void***)loco)[0x2c / 4])(loco);
    float  x = v[0];

    float inv = 1.0f / (float)sqrt((x * x + v[1] * v[1]) + v[2] * v[2] + 1e-08f);

    float n[3];
    n[0] = x * inv;
    n[1] = v[1] * inv;
    n[2] = v[2] * inv;

    char q[16];
    SP_QuaternionFromDirections(q, g_169a9e8, n);
    ((void(__thiscall*)(void*, void*)) (*(void***)loco)[0x3c / 4])(loco, q);

    void* old = mp520;
    if (arg != old) {
        if (arg != 0)
            ((void(__thiscall*)(void*)) (*(void***)arg)[0x60 / 4])(arg);
        mp520 = arg;
        if (old != 0)
            ((void(__thiscall*)(void*)) (*(void***)old)[0x64 / 4])(old);
    }
    m224 = 5;
}

// @ 0x00cb6ed0
void ArtilleryProjectile::ctor()
{
    ((void(__thiscall*)(void*)) FUN_00b18660)(this);
    ((void(__thiscall*)(void*)) FUN_00c43860)(&mpVtLoco);

    float zero = 0.0f;
    mpVt4 = (void*)g_vft_145dca8;
    _ReadWriteBarrier();
    mTargetOffset[0] = zero;
    mTargetOffset[1] = zero;
    mTargetOffset[2] = zero;
    mFlag = 0;
    mpVt0 = (void*)g_vft_1475470;
    mpVt1 = (void*)g_vft_147545c;
    mpVtLoco = (void*)g_vft_1475360;
    mpVt3 = (void*)g_vft_1475354;
    mpVt4 = (void*)g_vft_147532c;
    mpOwner = 0;
    mMinDamage = 0;
    mMaxDamage = 1;
    mDamageType = 0;
    mTool = 0;
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

// @ 0x00cb7040
void GameObject::SetBallistic(const uint32_t* src)
{
    uint32_t* p = (uint32_t*)
        ((void*(__thiscall*)(void*)) (*(void***)((char*)this + 0x34))[0x2c / 4])((char*)this + 0x34);

    mp518 = (void*)p[0];
    mp51c = (void*)p[1];
    mp520 = (void*)p[2];
    m224  = 4;

    BallisticLocomotion* o = (BallisticLocomotion*)
        FUN_00f473a0(0x10, "Simulator/cBallisticLocomotion", 0, 0, 0, 0);
    if (o != 0) {
        o->mpVt8 = (void*)g_vft_13ec458;
        o->m0c   = 0;
        o->mpVt0 = (void*)g_vft_1475164;
        o->mpVt8 = (void*)g_vft_1475114;
    } else {
        o = 0;
    }

    ((void(__thiscall*)(void*, void*)) FUN_00c421b0)((char*)this + 0x34, o);

    mp1fc = (void*)src[0];
    mp200 = (void*)src[1];
    mp204 = (void*)src[2];
}

// @ 0x00cb7110
bool ProjSub::Update()
{
    ILoco*    loco = (ILoco*)((char*)this - 0x4d0);
    IProjObj* obj  = (IProjObj*)this;

    Float3* v = loco->GetPosition();
    float dx = v->x - mPos.x;
    float dy = v->y - mPos.y;
    float dz = v->z - mPos.z;
    float dist = (float)sqrt((dx * dx + dy * dy) + dz * dz);

    if (dist > 0.0f) {
        float inv = 1.0f / dist;

        Float3 delta;
        delta.x = dx * inv;
        delta.y = dy * inv;
        delta.z = dz * inv;

        Float3 out;
        void*  hit = 0;
        int    code = ((int(__cdecl*)(void*, void*, float, void*, void*, CtxObj*, void*))
                       SP_CombatLineTest)(&mPos, &delta, dist, &hit, &out,
                                          (CtxObj*)mpCtx, (void*)4);

        if (hit == 0 || ((IHit*)hit)->AsInterface((const void*)0x0ed7fc07) == 0) {
            if (code != 3) {
                IHit* other = (IHit*)0;
                if (hit != 0) {
                    other = (IHit*)((IHit*)hit)->AsInterface(&g_13f94d4);
                    if (other != 0) {
                        uint32_t a = obj->v4C();
                        uint32_t b = other->v10();
                        if (b == a)
                            goto release;
                    }
                }
                loco->SetPosition(&out);
                obj->v54();
                if (mpTool != 0) {
                    IToolStrategy* strategy =
                        (IToolStrategy*)((IToolData*)mpTool)->GetStrategy();
                    if (strategy != 0)
                        strategy->Use(mpTool, &out, (uint32_t)code, 0);
                }
                ((IHit*)hit)->h04();
                return false;
            }
        }
        if (hit != 0)
            ((IHit*)hit)->h04();
    }
release:
    Float3* v2 = loco->GetPosition();
    mPos = *v2;
    return true;
}

// @ 0x00cb7310
void __cdecl FUN_00cb7310()
{
}

// @ 0x00cb76f0
void __cdecl FUN_00cb76f0()
{
}

void* g_vft_1475650[2];             // 0x01475650  cFlakProjectile vtable 0
void* g_vft_147563c[2];             // 0x0147563c  cFlakProjectile vtable 1
void* g_vft_1475540[2];             // 0x01475540  cFlakProjectile locomotion vtable
void* g_vft_1475538[2];             // 0x01475538  cFlakProjectile vtable 3
void* g_vft_1475510[2];             // 0x01475510  cFlakProjectile vtable 4
void* g_vft_1475174[2];             // 0x01475174  cVerticalRocketLocomotion vtable
void* g_vft_1475184[2];             // 0x01475184  cStraightLineLocomotion vtable
void __fastcall FUN_00bc3130(void* timer);       // 0x00bc3130  SP::cSPTimer::Restart

struct FlakProjectile {
    void*    mpVt0;                      // +0x000
    void*    mpVt1;                      // +0x004
    char     _p008[0x34 - 0x08];
    void*    mpVtLoco;                   // +0x034
    char     _p038[0x108 - 0x38];
    void*    mpVt3;                      // +0x108
    char     _p10c[0x1fc - 0x10c];
    void*    mp1fc;                      // +0x1fc
    void*    mp200;                      // +0x200
    void*    mp204;                      // +0x204
    char     _p208[0x224 - 0x208];
    uint32_t m224;                       // +0x224
    char     _p228[0x504 - 0x228];
    void*    mpVt4;                      // +0x504
    float    mTargetOffset[3];           // +0x508
    char     mFlag514;                   // +0x514
    char     _p515[3];
    void*    mp518;                      // +0x518
    float    m51c;                       // +0x51c
    void*    mp520;                      // +0x520
    void*    mp524;                      // +0x524
    void*    mp528;                      // +0x528
    char     _p52c[0x544 - 0x52c];
    uint32_t m544;                       // +0x544
    char     mTimer[0x1c];               // +0x548

    FlakProjectile* ctor();
    FlakProjectile* _virtual_dtor(unsigned char flags);
    void           SetVerticalRocket(const uint32_t* src, float value);
    void           SetStraightLine(const uint32_t* src, char flag);
};

// @ 0x00cb79f0
FlakProjectile* FlakProjectile::ctor()
{
    ((void(__thiscall*)(void*)) FUN_00b18660)(this);
    ((void(__thiscall*)(void*)) FUN_00c43860)((char*)this + 0x34);

    mpVt4 = (void*)g_vft_145dca8;
    mTargetOffset[0] = 0.0f;
    mTargetOffset[1] = 0.0f;
    mTargetOffset[2] = 0.0f;
    mFlag514 = 0;
    mpVt0 = (void*)g_vft_1475650;
    mpVt1 = (void*)g_vft_147563c;
    mpVtLoco = (void*)g_vft_1475540;
    mpVt3 = (void*)g_vft_1475538;
    mpVt4 = (void*)g_vft_1475510;
    mp518 = 0;
    m51c = 0.0f;
    return this;
}

// @ 0x00cb7b50
FlakProjectile* FlakProjectile::_virtual_dtor(unsigned char flags)
{
    if (mp518 != 0)
        ((void(__thiscall*)(void*)) (*(void***)mp518)[8 / 4])(mp518);

    mpVt4 = (void*)g_vft_145dca8;
    ((Loco*)((char*)this + 0x34))->Destroy();
    ((void(__thiscall*)(void*)) FUN_00b184c0)(this);

    if ((flags & 1) != 0)
        FUN_00f47380(this);

    return this;
}

// @ 0x00cb7ba0
void FlakProjectile::SetVerticalRocket(const uint32_t* src, float value)
{
    m224 = 5;

    BallisticLocomotion* o = (BallisticLocomotion*)
        FUN_00f473a0(0x10, "Simulator/cVerticalRocketLocomotion", 0, 0, 0, 0);
    if (o != 0) {
        o->mpVt8 = (void*)g_vft_13ec458;
        _ReadWriteBarrier();
        o->m0c   = 0;
        o->mpVt0 = (void*)g_vft_1475174;
        o->mpVt8 = (void*)g_vft_1475114;
    } else {
        o = 0;
    }

    ((void(__thiscall*)(void*, void*)) FUN_00c421b0)((char*)this + 0x34, o);

    mp1fc = (void*)src[0];
    mp200 = (void*)src[1];
    mp204 = (void*)src[2];
    m51c  = value;
}

// @ 0x00cb7c20
void FlakProjectile::SetStraightLine(const uint32_t* src, char flag)
{
    m224 = (flag == 0) + 4;

    BallisticLocomotion* o = (BallisticLocomotion*)
        FUN_00f473a0(0x10, "Simulator/cStraightLineLocomotion", 0, 0, 0, 0);
    if (o != 0) {
        o->mpVt8 = (void*)g_vft_13ec458;
        _ReadWriteBarrier();
        o->m0c   = 0;
        o->mpVt0 = (void*)g_vft_1475184;
        o->mpVt8 = (void*)g_vft_1475114;
    } else {
        o = 0;
    }

    ((void(__thiscall*)(void*, void*)) FUN_00c421b0)((char*)this + 0x34, o);

    mp1fc = (void*)src[0];
    mp200 = (void*)src[1];
    mp204 = (void*)src[2];
    m544  = 0;
    FUN_00bc3130((char*)this + 0x548);

    void** v = (void**)
        ((void*(__thiscall*)(void*)) (*(void***)((char*)this + 0x34))[0x2c / 4])((char*)this + 0x34);
    mp520 = v[0];
    mp524 = v[1];
    mp528 = v[2];
}

// @ 0x00cb7ce0
void __cdecl Read()
{
}

// @ 0x00cb7e50
void Steering::Update(StepArgs* args)
{
    Vector3 vel = args->mpLoco->GetVelocity();
    Vector3 heading;

    uint64_t elapsed;
    if (mpTarget != 0 && ((elapsed = mTimer.GetElapsedTime()) > 0x5db)) {
        Vector3 pos = *args->mpLoco->GetPosition();
        Vector3 fwd;
        args->mpLoco->GetForward(&fwd);

        const Vector3* tp = mpTarget->GetPosition();
        Vector3 d;
        d.x = tp->x - pos.x;
        d.y = tp->y - pos.y;
        d.z = tp->z - pos.z;
        float dInv = 1.0f / sqrtf(d.z * d.z + (d.x * d.x + d.y * d.y));
        d.x *= dInv; d.y *= dInv; d.z *= dInv;
        float pInv = 1.0f / sqrtf(pos.x * pos.x + (pos.y * pos.y + pos.z * pos.z));
        Vector3 pn;
        pn.x = pInv * pos.x; pn.y = pos.y * pInv; pn.z = pos.z * pInv;

        // c = pn x d ; tangent = c x pn
        Vector3 c;
        c.x = pn.z * d.y - pn.y * d.z;
        c.y = d.z * pn.x - pn.z * d.x;
        c.z = pn.y * d.x - d.y * pn.x;
        Vector3 t;
        t.x = mRadius * (c.z * pn.y - c.y * pn.z) + pos.x;
        t.y = (pn.z * c.x - c.z * pn.x) * mRadius + pos.y;
        t.z = (c.y * pn.x - pn.y * c.x) * mRadius + pos.z;
        float tInv = 1.0f / sqrtf(t.y * t.y + (t.z * t.z + t.x * t.x));
        t.x *= tInv; t.y *= tInv; t.z *= tInv;

        const Vector3* tp2 = mpTarget->GetPosition();
        float radius = sqrtf((tp2->x * tp2->x + tp2->y * tp2->y) + tp2->z * tp2->z);
        Vector3 w;
        w.x = t.x * radius - pos.x;
        w.y = t.y * radius - pos.y;
        w.z = t.z * radius - pos.z;
        float wInv = 1.0f / sqrtf(w.z * w.z + (w.y * w.y + w.x * w.x));
        Vector3 dir;
        dir.x = wInv * w.x; dir.y = w.y * wInv; dir.z = w.z * wInv;
        Vector3 axis = dir;

        const Vector3* tp3 = mpTarget->GetPosition();
        float dist = sqrtf((tp3->y - pos.y) * (tp3->y - pos.y) +
                           ((tp3->z - pos.z) * (tp3->z - pos.z) + (tp3->x - pos.x) * (tp3->x - pos.x)));
        if (40.0f < dist && dist < 300.0f) {
            Vector3 tmp0, tmp1, tmp2;
            const Vector3* n1 = Vec3Normalize(&tmp0, &pos);
            const Vector3* n2 = Vec3Normalize(&tmp1, &dir);
            axis.x = n1->z * n2->y - n1->y * n2->z;
            axis.z = n2->x * n1->y - n1->x * n2->y;
            float angle = mWobbleAngle;
            float half = angle * 0.5f;
            float s = (float)sin(half);
            axis.y = n1->x * n2->z - n2->x * n1->z;
            Quaternion q;
            float c2 = (float)cos(half);
            q.x = s * t.x; q.y = t.y * s; q.z = t.z * s;
            q.w = c2;
            const Vector3* r = QuaternionRotate(&tmp2, &axis, &q);
            Vector3 mix;
            mix.x = r->x * 0.5f + t.x;
            mix.y = r->y * 0.5f + t.y;
            mix.z = r->z * 0.5f + t.z;
            const Vector3* nm = Vec3Normalize(&tmp2, &mix);
            dir.x = nm->x; dir.y = nm->y; dir.z = nm->z;
            float na = args->mDt * mWobbleRate + angle;
            mWobbleAngle = na;
            if (na > kTwoPi_s00cb_7e50) mWobbleAngle = na - kTwoPi_s00cb_7e50;
        }

        float cs = fwd.x * dir.x + fwd.y * dir.y + fwd.z * dir.z;
        cs = MinSS(MaxSS(cs, -1.0f), 1.0f);
        float ang = (float)acos(cs);
        float step = 1.0f;
        if (ang > 0.0f) {
            float f = (args->mDt * mWobbleRate) / ang;
            step = MinSS(1.0f, f);
        }
        Vector3 out;
        RotateTowards(&out, &fwd, &dir, step);
        args->mVelocity.x = mRadius * out.x;
        args->mVelocity.y = mRadius * out.y;
        args->mVelocity.z = mRadius * out.z;
        Quaternion qo;
        cLocomotive* loco = args->mpLoco;
        loco->SetOrientation(QuaternionFromDirections_s00cb_7e50(&qo, &kForward, &out));
        return;
    }
    args->mVelocity = vel;
    Quaternion qo;
    cLocomotive* loco = args->mpLoco;
    loco->SetOrientation(QuaternionFromDirections_s00cb_7e50(&qo, &kForward, &vel));
}

// @ 0x00cb84b0
void* cContentValidationSummarizer::FUN_00cb84b0(int flags)
{
    mTimer.Destroy();
    if (mpField18)
        ((VfnV)mpField18->mpVtbl->mSlots[kVtC0])(mpField18);
    mpVtblSelf = &gVtbl013ec458;
    mpVtblTracer = &gVtbl013eb938;
    if (flags & 1)
        operator_delete(this);
    return this;
}

// @ 0x00cb84f0
void* cSpaceDefenseMissile::FUN_00cb84f0()
{
    mBase.Construct();
    mLoco.Construct();
    uint32_t zero = 0;
    InitProjectileBody(mProj, zero);
    mCombatant.Construct();
    mBase.mpVtbl00 = &gVtbl014758e0;
    mBase.mpVtbl04 = &gVtbl014758cc;
    mLoco.mpVtbl = &gVtbl014757d0;
    mProjSuper.mpVtbl = &gVtbl014757c8;
    mProj.mpVtbl = &gVtbl014757a0;
    mCombatant.mpVtbl = &gVtbl01475738;
    mpTool = (cSPSpaceToolData_s00cb_7e50*)zero;
    mpTarget = (IVtblObject*)zero;
    mLifeTimer.Construct();
    mpHitSphere = (cInteractableObject*)zero;
    return this;
}

// @ 0x00cb86a0
void cSpaceDefenseMissile::FUN_00cb86a0()
{
    if (mpHitSphere)
        ((VfnV)mpHitSphere->mpVtbl->mSlots[kVt04])(mpHitSphere);
    mLifeTimer.Destroy();
    if (mpTarget)
        ((VfnV)mpTarget->mpVtbl->mSlots[kVt64])(mpTarget);
    if (mpTool)
        ((VfnV)mpTool->mpVtbl->mSlots[kVt08])(mpTool);
    mCombatant.Destroy();
    mProj.mpVtbl = &gVtbl0145dca8;
    mLoco.Destroy();
    mBase.Destroy();
}

// @ 0x00cb8760
void cSpaceDefenseMissile::FUN_00cb8760(const Vector3* pos, IVtblObject* target)
{
    IVtblObject* old = mpTarget;
    if (target != old) {
        if (target)
            ((VfnV)target->mpVtbl->mSlots[kVt60])(target);
        mpTarget = target;
        if (old)
            ((VfnV)old->mpVtbl->mSlots[kVt64])(old);
    }
    mProjSuper.mMode = 4;
    cSpaceDefenseMissileLocomotion* locomotion = 0;
    void* mem = operator_new(0x48, "Simulator/cSpaceDefenseMissileLocomotion", 0, 0, 0, 0);
    if (mem) {
        cSPSpaceToolData_s00cb_7e50* tool = mpTool;
        locomotion = ((cSpaceDefenseMissileLocomotion*)mem)->Construct(
            tool->FUN_0104be50(),
            tool->FUN_00c41d40(),
            (void*)((VfnP)target->mpVtbl->mSlots[kVt08])(target));
    }
    mLoco.FUN_00c421b0(locomotion);
    mProjSuper.mTargetPosX = pos->x;
    mProjSuper.mTargetPosY = pos->y;
    mProjSuper.mTargetPosZ = pos->z;
    mLifeTimer.Restart();
    if (cSPLivingUniverse_GetUniverseContext() == 0) {
        cGameNounManager* manager = NounManager();
        IVtblObject* hitSphere = manager->CreateNoun(0x2e72cae);
        if (hitSphere)
            hitSphere = (IVtblObject*)((VfnPU)hitSphere->mpVtbl->mSlots[kVt0C])(hitSphere, 0x2e71a5a);
        IVtblObject* prev = mpHitSphere;
        if (hitSphere != prev) {
            if (hitSphere)
                ((VfnV)hitSphere->mpVtbl->mSlots[kVt00])(hitSphere);
            mpHitSphere = (cInteractableObject*)hitSphere;
            if (prev)
                ((VfnV)prev->mpVtbl->mSlots[kVt04])(prev);
        }
        float turnRate = ((VfnF0)mLoco.mpVtbl->mSlots[kVt34])(&mLoco) * g0157d350;
        int effect = ((VfnIF)mLoco.mpVtbl->mSlots[kVt2C])(&mLoco, turnRate);
        mpHitSphere->SetEffectId(effect);
        mpHitSphere->FUN_00c3f1b0(g0169a410, g0147515c);
        mpHitSphere->FUN_00c3f2d0(this);
    }
}

// @ 0x00cb88e0
void* cDefaultBeamProjectile_s00cb_7e50::FUN_00cb88e0()
{
    mBase.Construct();
    mSpatial.Construct();
    uint32_t zero = 0;
    InitProjectileBody(mProj, zero);
    mInteraction.Construct();
    mBase.mpVtbl00 = &gVtbl01475ab0;
    mBase.mpVtbl04 = &gVtbl01475a9c;
    mSpatial.mpVtbl = &gVtbl014759d8;
    mProj.mpVtbl = &gVtbl014759ac;
    mInteraction.mpVtbl = &gVtbl01475990;
    mpTool = (cSPSpaceToolData_s00cb_7e50*)zero;
    mpSource = (IVtblObject*)zero;
    mMaxBeamLength = g01477fbc;
    mProjectileScale = g01485720;
    mDamageRadius = g01485720;
    mActionTriggered = (uint8_t)zero;
    mbStopBeam = (uint8_t)zero;
    mbHittingGround = (uint8_t)zero;
    mbHittingWater = (uint8_t)zero;
    mOrientsToTerrain = (uint8_t)zero;
    mbPassesThroughToTerrain = (uint8_t)zero;
    mBeamTurnRate = g0157d364 * g013eeda0;
    mMsPerDamagePointLo = zero;
    mMsPerDamagePointHi = zero;
    mLifeTimer.Construct();
    mTargetedCombatant = (IVtblObject*)zero;
    mPathBegin = (Vector3*)zero;
    mPathEnd = (Vector3*)zero;
    mPathCapacity = (Vector3*)zero;
    return this;
}

// @ 0x00cb8b20
void cDefaultBeamProjectile_s00cb_7e50::FUN_00cb8b20()
{
    Vector3* path = mPathBegin;
    if (path != 0 && ((int*)path)[-1] != 0)
        operator_delete(path);
    if (mTargetedCombatant)
        ((VfnV)mTargetedCombatant->mpVtbl->mSlots[kVt04])(mTargetedCombatant);
    mLifeTimer.Destroy();
    if (mpSource)
        ((VfnV)mpSource->mpVtbl->mSlots[kVt64])(mpSource);
    if (mpTool)
        ((VfnV)mpTool->mpVtbl->mSlots[kVt08])(mpTool);
    mInteraction.Destroy();
    mProj.mpVtbl = &gVtbl0145dca8;
    mSpatial.Destroy();
    mBase.Destroy();
}

// @ 0x00cb8ba0
void cDefaultBeamProjectile_s00cb_7e50::FUN_00cb8ba0(Vector3* start, Vector3* end)
{
    if ((uint32_t)(mPathEnd - mPathBegin) > 1) {
        *start = *mPathBegin;
        *end = mPathEnd[-1];
        return;
    }
    const Vector3* pStart = (const Vector3*)((VfnP)mSpatial.mpVtbl->mSlots[kVt2C])(&mSpatial);
    *start = *pStart;
    float length = mMaxBeamLength;
    if (mTargetedCombatant != 0 || mbHittingGround != 0 || mbHittingWater != 0) {
        float dx = start->x - mHitPositionX;
        float dy = start->y - mHitPositionY;
        float dz = start->z - mHitPositionZ;
        length = (float)sqrt((double)dx * (double)dx + (double)dy * (double)dy +
                             (double)dz * (double)dz);
    }
    end->x = start->x + mBeamDirectionX * length;
    end->y = start->y + mBeamDirectionY * length;
    end->z = start->z + mBeamDirectionZ * length;
}

// @ 0x00cb8cd0
void* cDefaultAoEArea_s00cb_7e50::FUN_00cb8cd0()
{
    mBase.Construct();
    mSpatial.Construct();
    uint32_t zero = 0;
    InitProjectileBody(mProj, zero);
    mBase.mpVtbl00 = &gVtbl014752b8;
    mBase.mpVtbl04 = &gVtbl014752a4;
    mSpatial.mpVtbl = &gVtbl014751e0;
    mProj.mpVtbl = &gVtbl014751b4;
    mpTool = (cSPSpaceToolData_s00cb_7e50*)zero;
    __m128 zed = _mm_setzero_ps();
    mSourceOffsetX = g0169a414;
    mSourceOffsetY = g0169a418;
    mSourceOffsetZ = g0169a41c;
    _mm_store_ss(&mDamageRadius, zed);
    mbStopArea = (uint8_t)zero;
    mLifeTimer.Construct();
    mAccumulatedTimeLo = zero;
    mAccumulatedTimeHi = zero;
    mCulturalTimeLo = zero;
    mCulturalTimeHi = zero;
    mLastUpdateLo = zero;
    mLastUpdateHi = zero;
    return this;
}

// @ 0x00cb8dd0
void* cCulturalProjectile_s00cb_7e50::FUN_00cb8dd0()
{
    mBase.Construct();
    mLoco.Construct();
    uint32_t zero = 0;
    InitProjectileBody(mProj, zero);
    mLoco.mpVtbl = &gVtbl01475bd0;
    mBase.mpVtbl00 = &gVtbl01475b78;
    mBase.mpVtbl04 = &gVtbl01475b68;
    mProjSuper.mpVtbl = &gVtbl01475b60;
    mProj.mpVtbl = &gVtbl01475b38;
    mPathLocomotion = (IVtblObject*)zero;
    mpVehicle = (IVtblObject*)zero;
    mpTarget = (IVtblObject*)zero;
    mpTool = (cSPSpaceToolData_s00cb_7e50*)zero;
    mField528 = 0xffffffff;
    mbExplode = (uint8_t)zero;
    mbSpin = (uint8_t)zero;
    mLifeTimer.Construct();
    mOwner = 0xffffffff;
    mField568.Construct();
    mProjSuper.mField198 = 0.0f;
    return this;
}

// @ 0x00cb8f50
void cCulturalProjectile_s00cb_7e50::FUN_00cb8f50()
{
    mField568.Destroy();
    mLifeTimer.Destroy();
    if (mpTool)
        ((VfnV)mpTool->mpVtbl->mSlots[kVt08])(mpTool);
    if (mpTarget)
        ((VfnV)mpTarget->mpVtbl->mSlots[kVt64])(mpTarget);
    if (mpVehicle)
        ((VfnV)mpVehicle->mpVtbl->mSlots[kVt04])(mpVehicle);
    if (mPathLocomotion)
        ((VfnV)mPathLocomotion->mpVtbl->mSlots[kVt04])(mPathLocomotion);
    mProj.mpVtbl = &gVtbl0145dca8;
    mLoco.Destroy();
    mBase.Destroy();
}

// @ 0x00cb9010
void* cResourceProjectile::FUN_00cb9010()
{
    mBase.Construct();
    mLoco.Construct();
    uint32_t zero = 0;
    InitProjectileBody(mProj, zero);
    mBase.mpVtbl00 = &gVtbl01475e38;
    mBase.mpVtbl04 = &gVtbl01475e24;
    mLoco.mpVtbl = &gVtbl01475d28;
    mProjSuper.mpVtbl = &gVtbl01475d1c;
    mProj.mpVtbl = &gVtbl01475cf4;
    mPathLocomotion = (IVtblObject*)zero;
    mpNode = (IVtblObject*)zero;
    mLifeTimer.Construct();
    mOwner = 0xffffffff;
    return this;
}

// @ 0x00cb9170
void* cResourceProjectile::FUN_00cb9170(int flags)
{
    mLifeTimer.Destroy();
    if (mpNode)
        ((VfnV)mpNode->mpVtbl->mSlots[kVt04])(mpNode);
    if (mPathLocomotion)
        ((VfnV)mPathLocomotion->mpVtbl->mSlots[kVt04])(mPathLocomotion);
    mProj.mpVtbl = &gVtbl0145dca8;
    mLoco.Destroy();
    mBase.Destroy();
    if (flags & 1)
        operator_delete(this);
    return this;
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

// @ 0x00cb9810
void TObj::FUN_00cb9810()
{
    void* mgr = FUN_00b3d240_s00cb_91d0();
    uint32_t state = *(uint32_t*)((char*)this + 0x530);
    TObj* loco = (TObj*)((char*)this + 0x34);
    if (state == 0) {
        float xf[4];
        void* p = ((void*(__thiscall*)(void*, void*))VF(loco, 0x5c))(loco, xf);
        p = ((void*(__thiscall*)(void*, void*))VF(loco, 0x2c))(loco, p);
        ((void(__thiscall*)(void*, uint32_t, void*))VF(mgr, 0x60))(mgr, 0x147e293, p);
    }

    ObjVec vec;
    vec.mpBegin = 0;
    vec.mpEnd = 0;
    vec.mpCap = 0;
    void* hit = ((void*(__thiscall*)(void*, float, ObjVec*, int, int, int))VF(loco, 0x2c))(
        loco, 3.0f, &vec, 0, 0, 0);
    ((void(__thiscall*)(void*, void*))VF(mgr, 0x48))(mgr, hit);

    int count = (int)((char*)vec.mpEnd - (char*)vec.mpBegin) >> 2;
    if (state == 4) {
        for (int i = 0; i < count; i++) {
            void* el = vec.mpBegin[i];
            if (el == 0) {
                continue;
            }
            void* filter = ((void*(__thiscall*)(void*, uint32_t))VF(el, 0xb8))(el, 0x13f94d4);
            if (filter == 0) {
                continue;
            }
            void* owner = ((void*(__thiscall*)(void*))VF((char*)this + 0x504, 0x18))(
                (char*)this + 0x504);
            if (owner == 0) {
                continue;
            }
            void* src = ((void*(__thiscall*)(void*, uint32_t))VF(owner, 0x5c))(owner, 0x137e8e0);
            if (src == 0) {
                continue;
            }
            float height = *(float*)((char*)src + 0xc50);
            void* obj = ((void*(__thiscall*)(void*))VF(filter, 8))(filter);
            float* from = ((float*(__thiscall*)(void*))VF(loco, 0x2c))(loco);
            float* to = ((float*(__thiscall*)(void*))VF(obj, 0x2c))(obj);
            float dx = to[0] - from[0];
            float dy = to[1] - from[1];
            float dz = to[2] - from[2];
            float inv = 1.0f / sqrtf(dx * dx + (dy * dy + dz * dz));
            float dir[3];
            dir[0] = inv * dx;
            dir[1] = dy * inv;
            dir[2] = dz * inv;
            void* effect = ((void*(__thiscall*)(void*, uint32_t, float*, int))VF(this, 0x4c))(
                this, state, dir, 0);
            ((void(__thiscall*)(void*, float, void*))VF(filter, 0x18))(filter, height, effect);
        }
    } else if (state != 3) {
        for (int i = 0; i < count; i++) {
            void* el = vec.mpBegin[i];
            if (el == 0) {
                continue;
            }
            void* filter = ((void*(__thiscall*)(void*, uint32_t))VF(el, 0xb8))(el, 0xb033b403);
            if (filter == 0) {
                continue;
            }
            void* obj = ((void*(__thiscall*)(void*))VF(filter, 8))(filter);
            float* from = ((float*(__thiscall*)(void*))VF(loco, 0x2c))(loco);
            float* to = ((float*(__thiscall*)(void*))VF(obj, 0x2c))(obj);
            float dx = to[0] - from[0];
            float dy = to[1] - from[1];
            float dz = to[2] - from[2];
            float inv = 1.0f / sqrtf(dx * dx + (dy * dy + dz * dz));
            float dir[3];
            dir[0] = inv * dx;
            dir[1] = dy * inv;
            dir[2] = dz * inv;
            unsigned int span = *(uint32_t*)((char*)this + 0x52c)
                              - *(uint32_t*)((char*)this + 0x528);
            unsigned int r = RandomUint32Uniform(&gMathRandom, span);
            int level = (int)(*(uint32_t*)((char*)this + 0x528) + r);
            void* effect = ((void*(__thiscall*)(void*, uint32_t, float*, int))VF(this, 0x4c))(
                this, state, dir, 0);
            ((void(__thiscall*)(void*, float, void*))VF(filter, 0x18))(filter, (float)level, effect);
        }
    }

    for (void** it = vec.mpBegin; it != vec.mpEnd; ++it) {
        void* el = *it;
        if (el != 0) {
            ((void(__thiscall*)(void*))VF(el, 0xc0))(el);
        }
    }
    if (vec.mpBegin != 0 && ((uint32_t*)vec.mpBegin)[-1] != 0) {
        FUN_00f47380(vec.mpBegin);
    }
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

// @ 0x00cb9bd0
void TObj::FUN_00cb9bd0()
{
    void* mgr = FUN_00b3d240_s00cb_91d0();
    ObjVec vec;
    vec.mpBegin = 0;
    vec.mpEnd = 0;
    vec.mpCap = 0;
    void* holder = *(void**)((char*)this + 0x518);
    if (holder == 0) {
        FUN_00ad92d0(&vec);
        return;
    }

    TObj* loco = (TObj*)((char*)this + 0x34);
    float radius = FUN_0104bdb0(&vec, 0, 0, 0);
    void* hit = ((void*(__thiscall*)(void*, float))VF(loco, 0x2c))(loco, radius);
    ((void(__thiscall*)(void*, void*))VF(mgr, 0x48))(mgr, hit);

    int count = (int)((char*)vec.mpEnd - (char*)vec.mpBegin) >> 2;
    char any = 0;
    for (int i = 0; i < count; i++) {
        void* el = vec.mpBegin[i];
        if (el == 0) {
            continue;
        }
        void* filter = ((void*(__thiscall*)(void*, uint32_t))VF(el, 0xb8))(el, 0xb033b403);
        if (filter == 0) {
            continue;
        }
        void* holderObj = *(void**)((char*)holder + 0x114);
        void* tail = 0;
        if (holderObj != 0) {
            tail = ((void*(__thiscall*)(void*, uint32_t))VF(holderObj, 0xb8))(holderObj, 0x13f94d4);
        }
        float* from = ((float*(__thiscall*)(void*))VF(loco, 0x2c))(loco);
        TObj* fself = (TObj*)((char*)filter + 0x34);
        float* to = ((float*(__thiscall*)(void*))VF(fself, 0x2c))(fself);
        float dx = to[0] - from[0];
        float dy = to[1] - from[1];
        float dz = to[2] - from[2];
        float inv = 1.0f / sqrtf(dx * dx + (dy * dy + dz * dz));
        float dir[3];
        dir[0] = inv * dx;
        dir[1] = dy * inv;
        dir[2] = dz * inv;

        float lo = FUN_0104bdc0(holder);
        float hi = FUN_00ce6940(holder);
        double range = (double)(lo - hi);
        double spread = RandomDoubleUniform(&gMathRandom) * range;
        if (spread >= range) {
            spread = range;
        } else if (spread < 0.0) {
            spread = 0.0;
        }

        void* effect = ((void*(__thiscall*)(void*, uint32_t, float*, void*))VF(this, 0x4c))(
            this, 0, dir, tail);
        float offset = (float)((double)FUN_00ce6940(holder) + spread);
        ((void(__thiscall*)(void*, float, void*))VF(filter, 0x18))(filter, offset, effect);
        if (*(uint32_t*)((char*)filter + 0x714) == 0) {
            any = 1;
        }
    }

    unsigned int tag = FUN_0104bf10(holder);
    if (any != 0) {
        tag = FUN_0104bef0(holder);
    }

    void* em = FUN_0067ddd0();
    TObj* es = (TObj*)((void*(__thiscall*)(void*, uint32_t))VF(em, 0x54))(em, 0x3701a5c);
    void* ref = 0;
    char ok = ((char(__thiscall*)(void*, uint32_t, int, void**))VF(es, 8))(es, tag, 0, &ref);
    if (ok != 0) {
        Rec rec;
        rec.x = DAT_0169aa18;
        rec.y = DAT_0169aa1c;
        rec.flags0 = 0;
        rec.z = DAT_0169aa20;
        rec.cnt0 = 0;
        rec.one = DAT_01485720;
        ((TObj*)&rec.m[0])->F_0041cb40(&DAT_0169a9f4);
        float* pl = ((float*(__thiscall*)(void*))VF(loco, 0x2c))(loco);
        rec.x = pl[0];
        rec.y = pl[1];
        rec.z = pl[2];
        rec.flags0 |= 4;
        rec.cnt0++;
        float* pl2 = ((float*(__thiscall*)(void*))VF(loco, 0x2c))(loco);
        uint8_t tmp[0x10];
        void* fr = ((void*(__thiscall*)(void*, void*, float*))VF(loco, 0x5c))(loco, tmp, pl2);
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

    for (void** it = vec.mpBegin; it != vec.mpEnd; ++it) {
        void* el = *it;
        if (el != 0) {
            ((void(__thiscall*)(void*))VF(el, 0xc0))(el);
        }
    }
    if (vec.mpBegin != 0 && ((uint32_t*)vec.mpBegin)[-1] != 0) {
        FUN_00f47380(vec.mpBegin);
    }
}

// @ 0x00cba4e0
void SP::cCombatant_s00cb_a050::TakeHit(float f, int a, int b, int c, int d)
{
    int before = m_8e7f80();
    m_bfcdd0(f, a, b, c, d);    int after = m_8e7f80();
    if (after == 2 && before != 2) {
        SP::cSpaceDefenseMissile_s00cb_a050* pMissile = (SP::cSpaceDefenseMissile_s00cb_a050*)((char*)this - 0x518);
        pMissile->Explode();
        ((Obj_s00cb_a050*)SP_NounManager())->m_b225d0(pMissile);
    }
}

// @ 0x00cba560
void __cdecl FUN_00cba560(void* pTool, void* pOwner1, int pOwner2, int arg3, float f1, float f2, int arg6, int arg7)
{
    cSPObjectList vec;
    vec.mpBegin = 0;
    vec.mpEnd = 0;
    vec.mpCapacity = 0;

    Obj_s00cb_a050* pManager = (Obj_s00cb_a050*)SP_ToolManager();
    ((Fn_v_pf)VTSLOT(pManager, 0x48))(pManager, f1);   // fill the hit list

    int n = (int)(vec.mpEnd - vec.mpBegin);
    for (int i = 0; i < n; ++i) {
        Obj_s00cb_a050* p = vec.mpBegin[i];
        if (!p)
            continue;
        void* pHit = ((Fn_p_pi)VTSLOT(p, 0xb8))(p, (int)&DAT_013f94d4);
        if (!pHit)
            continue;
        // pTool+0x220 interface identity, pOwner, and pOwner2 all skip
        if (pHit == (void*)arg6 || pHit == pOwner1)
            continue;
        // cSPSpaceToolData::DoAreaEffectHit 0x00cb59b0
        ((void (__thiscall*)(void*, int, int, void*, void*, void*, int, float, float))
         0x00cb59b0)(pTool, 0, 0, pHit, pOwner1, (void*)arg6, arg3, f2, f1);
    }
    if (pOwner1) {
        ((void (__thiscall*)(void*, int, int, void*, void*, void*, int, float, float))
         0x00cb59b0)(pTool, 0, 0, pOwner1, (void*)pOwner2, (void*)arg6, arg3, f2, f1);
    }
    // the eastl vector local is released by the caller's tail (operator delete[])
}

// @ 0x00cba690
void SP::cCulturalProjectile_s00cb_a050::Explode()
{
    // --- 0x00cba69a: effect (only when mbFlag538 && !mbSpin539) --------------
    if (mbFlag538 && !mbSpin539) {
        Obj_s00cb_a050* pFx = (Obj_s00cb_a050*)SP_EffectsManagerPtr();
        void* pEffect = ((Fn_p_pi)VTSLOT(pFx, 0x54))(pFx, 0x3701a5c);
        void* pOut = 0;
        bool ok = ((bool (__thiscall*)(void*, int, int, void**))VTSLOT(pEffect, 0x08))(
            pEffect, 0xf88730e6, 0, &pOut);
        if (ok) {
            struct XformMsg { int mData[16]; };
            XformMsg msg;
            Vector3 pos = *((Vector3* (*)(void*))VTSLOT(&mLoco, 0x2c))(&mLoco);
            msg.mData[1] = 0; // (offset slot filled by SetOffset below)
            ((void (__thiscall*)(void*, Vector3*))0x00571d40)(&msg, &pos);
            Vector3* pFacing = ((Vector3* (*)(void*))VTSLOT(&mLoco, 0x5c))(&mLoco);
            Matrix3Rows rot;
            Matrix3FromFacingAndUp(&rot, pFacing, pFacing);
            (void)rot;
            // XformMsg::operator= through the message receiver
            ((Fn_v_pp)VTSLOT(pEffect, 0x18))(pEffect, &msg);

            uint32_t owner = mOwner;
            Obj_s00cb_a050* pNoun = (Obj_s00cb_a050*)((void* (__cdecl*)(uint32_t))0x00b3d300)(owner);
            cHitObject* pHit = 0;
            if (pNoun)
                pHit = (cHitObject*)pNoun->m_b25f40(pNoun);
            if (pHit) {
                Vector3 tp = pHit->mPosition;
                ((Fn_v_pi)VTSLOT(pOut, 0x44))(pOut, 3);
                (void)tp;
            }
            ((Fn_v_pi)VTSLOT(pEffect, 0x08))(pEffect, 0);
        }
    }

    // --- 0x00cba7ea: main branch needs a locomotion and a tool ----------------
    if (!mpVehicle || !mpTool)
        return;

    int aimIndex;
    {
        cCulturalLocomotion* pLoco = (cCulturalLocomotion*)mpVehicle;
        // the +0x508 guidance sub-block slot 0x3c: path exhausted?
        bool bDone = ((bool (__thiscall*)(void*))VTSLOT(&pLoco->mBlock508, 0x3c))(&pLoco->mBlock508);
        if (bDone)
            aimIndex = -1;
        else
            aimIndex = (int)((Fn_p_p)VTSLOT(mpVehicle, 0x4c))(mpVehicle);
    }

    void* pToolKey = 0;
    if (mpTarget)
        pToolKey = ((Fn_p_p)VTSLOT(mpTarget, 0x0c))(mpTarget);
    cCulturalLocomotion* pLoco = (cCulturalLocomotion*)mpVehicle;
    float radius = (pLoco->mRadius + DAT_01471064) * DAT_013eeda0;

    float damage = ((cSPSpaceToolData_s00cb_a050*)mpTool)->GetDamageRadius(radius, radius, 3, aimIndex,
                                                               (int)pToolKey, 0);

    // 0x00cba8cb FUN_00cba560(tool, owner object, ...)
    FUN_00cba560(mpTool, 0, 0, 0, damage, radius, 0, 0);

    void* pTimerOwner = mpTarget;
    if (pTimerOwner) {
        void* pTimerKey = ((Fn_p_p)VTSLOT(pTimerOwner, 0x10))(pTimerOwner);
        ((void (__thiscall*)(void*, void*))0x00bfddc0)(
            &((cCulturalLocomotion*)mpVehicle)->mBlock508, pTimerKey);
    }
    void* pSelfId = 0;
    if (mpTarget)
        pSelfId = ((Fn_p_pi)VTSLOT(mpTarget, 0x5c))(mpTarget, 0x3d5c477);
    void* pBuilding = 0;
    if (mpTarget)
        pBuilding = ((Fn_p_pi)VTSLOT(mpTarget, 0x5c))(mpTarget, (int)0xe9cb8ba);
    void* pTurret = 0;
    if (mpTarget)
        pTurret = ((Fn_p_pi)VTSLOT(mpTarget, 0x5c))(mpTarget, 0x436f315);
    void* pAnimal = 0;
    if (mpTarget)
        pAnimal = ((Fn_p_pi)VTSLOT(mpTarget, 0x5c))(mpTarget, (int)0xd0036e08);

    // relationship bookkeeping (0x00cba952..0x00cba9c3)
    void* pOther = (void*)0;
    if (pTurret) pOther = pTurret;
    else if (pBuilding) pOther = pBuilding;
    else if (pSelfId) pOther = pSelfId;
    else if (pAnimal) pOther = pAnimal;
    if (pOther) {
        if ((void*)((Fn_p_p)VTSLOT(pOther, 0x4c))(pOther) !=
            (void*)((Fn_p_p)VTSLOT(this, 0x4c))(this)) {
            ((Fn_v_p)VTSLOT(pOther, 0x4c))(pOther);
            Obj_s00cb_a050* pRel = (Obj_s00cb_a050*)SP_RelationshipManager();
            ((void (__thiscall*)(void*, float))0x00d06270)(pRel, 1.0f);
            Obj_s00cb_a050* pNoun = (Obj_s00cb_a050*)SP_NounManager();
            if ((int)((Fn_p_p)VTSLOT(this, 0x4c))(this) == GetPlayerEmpireOrMinus1()) {
                if (RandomUint32Uniform(10) == 0) {
                    // 0x00cba9dd secondary effect / fame branch
                    Obj_s00cb_a050* pTool2 = (Obj_s00cb_a050*)((void* (*)(void*))0x00cb4650)(&mpVehicle);
                    int cnt = ((int (__thiscall*)(void*))0x00ca0380)(mpVehicle);
                    if (pTool2 && ((bool (__thiscall*)(void*))VTSLOT(&mLoco, 0x48))(&mLoco)) {
                        cSPTimer_s00cb_a050* pTimer = &mTimer;
                        if (pTimer->IsRunning()) {
                            uint64_t el = pTimer->GetElapsedTime();
                            uint64_t limit = (uint64_t)(uint32_t)(cnt * 5000);
                            if (el < limit)
                                return;
                        }
                        (void)pTool2;
                        ((void (__thiscall*)(void*))0x00bc3130)(pTimer);   // Restart
                    }
                }
            }
        }
    } else {
        // 0x00cbaba7: no target object -- use the locomotion path
        if (mpVehicle) {
            cCulturalLocomotion* pLoco = (cCulturalLocomotion*)mpVehicle;
            Vector3* pPts = pLoco->mPath.mpBegin;
            int cnt = (int)(pLoco->mPath.mpEnd - pLoco->mPath.mpBegin);
            unsigned count = (unsigned)(cnt / (int)sizeof(Vector3));
            if (count > 1) {
                Vector3 a = pPts[count - 1];
                Vector3 b = pPts[count - 2];
                Vector3 d;
                d.x = a.x - b.x; d.y = a.y - b.y; d.z = a.z - b.z;
                Vector3 n;
                SP_NormalizedSafe(&n, &d);
                Obj_s00cb_a050* pToolMan = (Obj_s00cb_a050*)SP_ToolManager();
                ((void (__thiscall*)(void*, int, Vector3*, Vector3*))VTSLOT(pToolMan, 0x60))(
                    pToolMan, 0x65baa81, &a, &n);
            }
        }
    }
}

// @ 0x00cbac80
bool SP::cResourceProjectile_s00cb_a050::Update()
{
    cSPTimer_s00cb_a050* pTimer = &mTimer;

    uint64_t e = pTimer->GetElapsedTime();
    if (e != 0) {
        uint64_t e2 = pTimer->GetElapsedTime();
        if (e2 > 1000u)
            return false;
    } else {
        Obj_s00cb_a050* loco = (Obj_s00cb_a050*)((char*)this - 0x4d0);
        Vector3* p = (Vector3*)((Fn_p_p)VTSLOT(loco, 0x2c))(loco);
        float dx = mEndPoint.x - p->x;
        float dy = mEndPoint.y - p->y;
        float dz = mEndPoint.z - p->z;
        if (sqrtf(dx * dx + (dy * dy + dz * dz)) < DAT_01470f1c) {
            pTimer->Start();
            ((cProjectileBase*)((char*)this - 0x504))->ExplodeResource();
        }
    }
    return true;
}

// @ 0x00cbad00
bool SP::cICBM::Update()
{
    Obj_s00cb_a050* loco = (Obj_s00cb_a050*)((char*)this - 0x4d0);

    Obj_s00cb_a050* pGuide = (Obj_s00cb_a050*)((Fn_p_p)VTSLOT(mpGuidance_1c, 0x08))(mpGuidance_1c);
    Vector3* pa = (Vector3*)((Fn_p_p)VTSLOT(loco, 0x2c))(loco);
    Vector3* pb = (Vector3*)((Fn_p_p)VTSLOT(pGuide, 0x2c))(pGuide);

    float dx = pb->x - pa->x;
    float dy = pb->y - pa->y;
    float dz = pb->z - pa->z;
    float dist = sqrtf(dx * dx + (dy * dy + dz * dz));
    if (dist < DAT_01486110) {
        ((cProjectileBase*)((char*)this - 0x504))->ExplodeICBM();
        return false;
    }
    Vector3* p2 = (Vector3*)((Fn_p_p)VTSLOT(loco, 0x2c))(loco);
    Obj_s00cb_a050* planet = (Obj_s00cb_a050*)SP_PlanetModel(p2);
    if (!planet->m_b81f90(p2))
        return true;
    ((cProjectileBase*)((char*)this - 0x504))->ExplodeICBM();
    return false;
}

// @ 0x00cbad90
void __cdecl FUN_00cbad90(Obj_s00cb_a050* pStream, PropertyList* pList)
{
    PropertyList* pListArg = pList;
    int count = pListArg->mCount;
    void* pWriter = ((Fn_p_p)VTSLOT(pStream, 0x20))(pStream);
    void* pOut = ((Fn_p_p)VTSLOT(pWriter, 0x18))(pWriter);

    EA_IO_WriteUint32((int)pOut, &count, 1, 0);

    void** pSentinel = (void**)((char*)pListArg + 4);
    for (void* it = pListArg->mpRoot; it != pSentinel;
         it = eastl_RBTreeIncrement(it)) {
        int v = 0;
        void* p = *(void**)((char*)it + 0x10);
        if (p)
            v = (int)((Fn_p_pi)VTSLOT(p, 0xb8))(p, 0x179c807);
        ((Fn_v_pi)VTSLOT(pStream, 0x2c))(pStream, v);
        ((Fn_v_p)VTSLOT(pStream, 0x1c))(pStream);
    }
    ((Fn_v_p)VTSLOT(pStream, 0x1c))(pStream);
}

// @ 0x00cbaf00
Simulator::cPathFollowingLocomotion_s00cb_a050::cPathFollowingLocomotion_s00cb_a050(const Vector3Vector_s00cb_a050& points, int motionID)
{
    mpVftable8 = (void*)0x13ec458;
    mField0c = 0;
    mpVftable0 = (void*)0x1475500;
    mpVftable8 = (void*)0x14754f0;

    mPath.CopyFrom(points);

    mCurrentSegmentLength = 0.0f;
    m30 = 0;
    m40 = motionID;
    mLowestAltitude = 0.0f;
    mLastSpeed = DAT_0147515c;
    m4c = 0;

    if (mPath.mpBegin != mPath.mpEnd) {
        int n = (int)(mPath.mpEnd - mPath.mpBegin) - 1;
        mDistanceFromLastPoint = n;
        if (n != 0) {
            Vector3* p = mPath.mpBegin;
            float dx = p[1].x - p[0].x;
            float dy = p[1].y - p[0].y;
            float dz = p[1].z - p[0].z;
            mToNextPoint.x = dx;
            mToNextPoint.y = dy;
            mToNextPoint.z = dz;
            float len = sqrtf(dx * dx + dy * dy + dz * dz);
            mLastPointReached = len;
            float inv = 1.0f / len;
            mToNextPoint.x *= inv;
            mToNextPoint.y *= inv;
            mToNextPoint.z *= inv;
        }
        PathUpdated();
    }
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

// @ 0x00cbbdc0
int __fastcall FUN_00cbbdc0(int s)
{
	int timer = s + 0x548;
	if (!cSPTimer_IsRunning((void*)timer))
	{
		typedef void (__fastcall *TickFn)(void*, int, int, int);
		TickFn tick = (TickFn)(*(int*)(*(int*)s + 0x58));
		tick((void*)s, 0, *(int*)(s + 0x5d0), *(int*)(s + 0x5d4));
		cSPTimer_Restart((void*)timer);
	}

	long long elapsed = cSPTimer_GetElapsedTime((void*)timer);
	float dt = FUN_0104bf60((void*)(*(int*)(s + 0x518)))
	         * (float)(elapsed & 0x7fffffffffffffffLL) * 0.001f;
	*(float*)(s + 0x540) = dt;

	bool clipped = dt < *(float*)(s + 0x534);
	if (!clipped)
	{
		*(float*)(s + 0x540) = *(float*)(s + 0x534);
		*(int*)(s + 0x544) = 2;
	}

	if (!(*(float*)(s + 0x540) > 0.0f))
	{
		if (clipped)
			return 1;
	}
	else
	{
		long long now = cSPTimer_GetElapsedTime((void*)timer);
		if (now - *(long long*)(s + 0x568) < 0xfb)
		{
			if (clipped)
				return 1;
		}
	}

	int ctx = *(int*)(s + 0x518);
	int* tgt = 0;
	int tid = -1;
	if (*(int*)(ctx + 0x114) != 0)
	{
		typedef void* (__fastcall *FindFn)(void*, int, const void*);
		FindFn find = (FindFn)(*(int*)(*(int*)(*(int*)(ctx + 0x114)) + 0xb8));
		tgt = (int*)find((void*)*(int*)(ctx + 0x114), 0, (const void*)PTR_FUN_013f94d4);
		if (tgt != 0)
		{
			typedef int (__fastcall *IdFn)(void*, int);
			typedef char (__fastcall *DeadFn)(void*, int);
			tid = ((IdFn)(*(int*)*tgt + 0x10))((void*)tgt, 0);
			if (!((DeadFn)(*(int*)*tgt + 0x3c))((void*)tgt, 0))
				goto have_target;
		}
	}
	tid = -1;
have_target:
	*(long long*)(s + 0x568) = cSPTimer_GetElapsedTime((void*)timer);

	if (*(float*)(s + 0x540) > 0.0f)
	{
		int* obj = (int*)FUN_00b3d240_s00cb_bdc0();
		typedef int (__fastcall *EmitFn)(void*, int, int, void*, int, int);
		EmitFn emit = (EmitFn)(*(int*)(s + 0x34));
		emit((void*)(s + 0x34), 0, *(int*)(s + 0x540), 0, 1, 0);
		(void)obj;
	}

	if (*(int*)(s + 0x518) != 0 && tgt != 0 && *(int*)(s + 0x518 + 0x50) != 0)
	{
		if (FUN_0104cd70() || tid == -1 || tid != ((int (__fastcall *)(void*, int))(*(int*)*tgt + 0x10))((void*)tgt, 0))
		{
			typedef int* (__fastcall *SubFn)(void*, int);
			int* sub = (int*)((SubFn)(*(int*)*tgt + 8))((void*)tgt, 0);
			typedef float* (__fastcall *PosFn)(void*, int);
			float* a = (float*)((PosFn)(*(int*)(*(int*)(*(int*)(s + 0x34)) + 0x2c)))((void*)(s + 0x34), 0);
			float* b = (float*)((PosFn)(*(int*)(*(int*)*sub + 0x2c)))((void*)sub, 0);
			float dx = b[0] - a[0];
			float dy = b[1] - a[1];
			float dz = b[2] - a[2];
			float inv = 1.0f / sqrtf(dx * dx + (dy * dy + dz * dz));
			float dir[3];
			dir[0] = dx * inv; dir[1] = dy * inv; dir[2] = dz * inv;
			int r = RandomUint32Uniform((void*)0, 0, *(int*)(s + 0x530) - *(int*)(s + 0x52c));
			typedef void (__fastcall *SpawnFn)(void*, int, int, int, int, void*);
			((SpawnFn)(*(int*)*tgt + 0x18))((void*)tgt, 0, *(int*)(s + 0x52c) + r, tid, *(int*)(s + 0x538), dir);
		}
	}

	if (*(int*)(s + 0x518) != 0 && FUN_0104cd40())
		FUN_00bbec40(*(int*)(s + 0x540), *(int*)(s + 0x540));

	return 1;
}

// @ 0x00cbc200
void __fastcall FUN_00cbc200(int* v, int dummy, int pos, int count, int* val)
{
	int obj = *val;
	if (obj != 0)
		(*(void (__fastcall**)(void*, int))(*(int*)obj))((void*)obj, 0);

	unsigned int have = (unsigned int)((v[2] - v[1]) >> 2);
	if ((unsigned int)count <= have)
	{
		if (count == 0)
			return;

		int begin = pos;
		unsigned int tail = (unsigned int)((v[1] - begin) >> 2);
		if ((unsigned int)count < tail)
		{
			int src = v[1] - count * 4;
			FUN_00829110((void*)0, 0, src, v[1], v[1]);
			v[1] += count * 4;
			FUN_00ac97a0((void*)0, 0, (void*)src, (void*)v[1]);
			FUN_00ea0350((void*)0, 0, (void*)begin, (void*)(begin + count * 4), (void*)0);
		}
		else
		{
			FUN_00b2ac90((void*)0, 0, count - tail, (void*)v[1], (void*)val);
			v[1] += (count - tail) * 4;
			FUN_00829110((void*)0, 0, begin, v[1], v[1]);
			v[1] += tail * 4;
			FUN_00ea0350((void*)0, 0, (void*)begin, (void*)v[1], (void*)0);
		}

		if (obj != 0)
			(*(void (__fastcall**)(void*, int))(*(int*)obj + 4))((void*)obj, 0);
		return;
	}

	int used = (v[1] - v[0]) >> 2;
	unsigned int cap2 = used * 2;
	if (used == 0)
		cap2 = 1;
	unsigned int need = used + count;
	if (need > cap2)
		cap2 = need;

	int* mem = 0;
	if (cap2 != 0)
		mem = (int*)EAAllocate(cap2 * 4, "Simulator", 0, 0, 0, 0xd1);

	int* dst = (int*)eastl_vector_insert(mem, (void*)v[0], (unsigned int)((pos - v[0]) & ~3));
	(void)dst;
	FUN_00b2ac90((void*)0, 0, count, (void*)val, (void*)pos);
	FUN_00b2ac90((void*)0, 0, (v[1] - pos) >> 2, (void*)pos, (void*)(pos + count * 4));
	eastl_vector_insert((void*)(pos + count * 4), (void*)pos, (unsigned int)(v[1] - pos));

	if (v[0] != 0 && v[0] != v[4])
		operator_delete((void*)v[0]);

	v[0] = (int)mem;
	v[1] = (int)(mem + used + count);
	v[2] = (int)(mem + cap2);
}

// @ 0x00cbc3c0
void __fastcall FUN_00cbc3c0(int s, int dummy, float p1, float p2, float p3, float p4, float p5, float p6)
{
	int* it = *(int**)(s + 0x5dc);
	int* end = *(int**)(s + 0x5e0);
	for (; it != end; it++)
	{
		int obj = *it;
		if (obj == 0)
			continue;
		typedef float* (__fastcall *PosFn)(void*, int);
		float* pos = (float*)((PosFn)(*(int*)(*(int*)(*(int*)(obj + 0x120)) + 0x2c)))((void*)(obj + 0x120), 0);
		float dx = pos[0] - p1;
		float dy = pos[1] - p2;
		float dz = pos[2] - p3;
		float inv = 1.0f / sqrtf(dx * dx + (dy * dy + dz * dz) + 1e-8f);
		float dot = (dx * inv) * p4 + p5 * (dy * inv) + p6 * (dz * inv);
		if (dot <= 0.0f)
			continue;

		int* fx = (int*)SP_EffectsManager();
		int* handle = 0;
		typedef char (__fastcall *PlayFn)(void*, int, int, const char*, int, void**);
		if (((PlayFn)(*(int*)(*(int*)*fx + 0x2c)))((void*)fx, 0, 0, (const char*)0x4d9a9b0c, 0, (void**)&handle))
		{
			float dirs[16];
			dirs[0] = 1.0f;
			dirs[1] = 0.0f;
			dirs[2] = 0.0f;
			(void)dirs;
		}
	}
}

// @ 0x00cbc7f0
void __fastcall FUN_00cbc7f0(int s, int dummy, float p1, float p2, float p3, float p4, float p5, float p6)
{
	int* it = *(int**)(s + 0x5dc);
	int* end = *(int**)(s + 0x5e0);
	while (it != end)
	{
		int obj = *it;
		typedef float* (__fastcall *PosFn)(void*, int);
		float* pos = (float*)((PosFn)(*(int*)(*(int*)(*(int*)(obj + 0x120)) + 0x2c)))((void*)(obj + 0x120), 0);

		float dx = pos[0] - p1;
		float dy = pos[1] - p2;
		float dz = pos[2] - p3;
		float inv = 1.0f / sqrtf(dx * dx + (dy * dy + dz * dz) + 1e-8f);
		float dot = (dx * inv) * p4 + p5 * (dy * inv) + p6 * (dz * inv);

		if (dot > 0.0f)
		{
			int e = FUN_01021300_ret();
			int r = FUN_00c30c80((void*)e);
			FUN_00bdbc20((void*)obj, 0, r + 0x504);

			if (it + 1 < end)
				do_copy(it + 1, end, it);
			end = (int*)((char*)end - 4);
			*(int**)(s + 0x5e0) = end;

			int ref = *end;
			if (ref != 0)
				(*(void (__fastcall**)(void*, int))(*(int*)ref + 4))((void*)ref, 0);
		}
		else
		{
			it++;
		}
	}
}

// @ 0x00cbc930
int __fastcall FUN_00cbc930(int s)
{
	SP_cGameData_ctor((void*)s);
	FUN_00c43860((void*)(s + 0x34));

	float zero = 0.0f;
	float one = DAT_01485720;

	*(volatile int*)(s+0x504) = (int)vtbl_0145dca8;
	*(float*)(s+0x508) = zero;
	*(float*)(s+0x50c) = zero;
	*(float*)(s+0x510) = zero;
	*(char*)(s+0x514) = 0;
	*(int*)(s+0x0) = (int)vtbl_01476188;
	*(int*)(s+0x4) = (int)vtbl_0147633c;
	*(int*)(s+0x34) = (int)vtbl_01476088;
	*(int*)(s+0x108) = (int)vtbl_01476080;
	*(int*)(s+0x504) = (int)vtbl_01476058;
	*(int*)(s+0x518) = 0;
	*(int*)(s+0x51c) = 0;
	*(int*)(s+0x52c) = 0;
	*(int*)(s+0x530) = 1;
	*(float*)(s+0x534) = one;
	*(int*)(s+0x538) = 0;
	*(float*)(s+0x53c) = one;
	*(float*)(s+0x540) = zero;
	*(int*)(s+0x544) = 0;
	cGonzagoTimer_ctor((void*)(s+0x548));

	int anchor = s+0x574;
	*(int*)(anchor + 4) = 0;
	*(int*)(anchor + 8) = 0;
	*(int*)(anchor + 0xc) = 0;
	*(int*)(s + 0x578) = anchor;
	*(int*)(s + 0x57c) = 0;
	*(char*)(s + 0x580) = 0;
	*(int*)(s + 0x584) = 0;
	*(int*)(anchor) = anchor;

	*(float*)(s + 0x58c) = DAT_0169a414;
	*(float*)(s + 0x590) = DAT_0169a418;
	*(float*)(s + 0x594) = DAT_0169a41c;
	*(int*)(s + 0x598) = -1;
	*(float*)(s + 0x59c) = DAT_0169a414;
	*(float*)(s + 0x5a0) = DAT_0169a418;
	*(float*)(s + 0x5a4) = DAT_0169a41c;
	*(int*)(s + 0x5cc) = 0;
	*(int*)(s + 0x5d4) = 0;
	*(int*)(s + 0x5d8) = 0;
	*(int*)(s + 0x5dc) = 0;
	*(int*)(s + 0x5e0) = 0;
	*(int*)(s + 0x5e4) = 0;
	*(float*)(s + 0x2a0) = 0.0f;
	return s;
}

// @ 0x00cbcb70
__declspec(noinline) int __fastcall FUN_00cbcb70(int s)
{
	FUN_00cbc930(s);
	*(int*)(s + 0x0) = (int)vtbl_01476350;
	*(int*)(s + 0x4) = (int)vtbl_0147633c;
	*(int*)(s + 0x34) = (int)vtbl_01476240;
	*(int*)(s + 0x108) = (int)vtbl_01476080;
	*(int*)(s + 0x504) = (int)vtbl_01476214;
	return s;
}

// @ 0x00cbcc40
void __cdecl FUN_00cbcc40(float p1, float p2, float p3, float p4, float p5, float p6, void* vec)
{
	int* v = (int*)vec;
	SpVector_erase(v, 0, (void*)v[0], (void*)v[1]);

	float dx = p4 - p1;
	float dy = p5 - p2;
	float dz = p6 - p3;
	float len = sqrtf(dx * dx + (dy * dy + dz * dz));
	float inv = 1.0f / len;
	float scale = len * 0.030303031f;
	float sx = (inv * dx) * scale;
	float sy = (inv * dy) * scale;
	float sz = (inv * dz) * scale;

	Vector3 cur;
	cur.x = p1; cur.y = p2; cur.z = p3;

	for (int i = 0x20; i != 0; i--)
	{
		Vector3* e = (Vector3*)v[1];
		if (e < (Vector3*)v[2])
		{
			v[1] = (int)(e + 1);
			if (e != 0)
			{
				e->x = cur.x;
				e->y = cur.y;
				e->z = cur.z;
			}
		}
		else
		{
			SpVector_DoInsertValue(v, 0, e, &cur);
		}
		cur.x = sx + cur.x;
		cur.y = sy + cur.y;
		cur.z = sz + cur.z;
	}

	Vector3* e = (Vector3*)v[1];
	if (e < (Vector3*)v[2])
	{
		v[1] = (int)(e + 1);
		if (e != 0)
		{
			e->x = p4;
			e->y = p5;
			e->z = p6;
		}
	}
	else
	{
		SpVector_DoInsertValue(v, 0, e, (const Vector3*)&p4);
	}
}

// @ 0x00cbcde0
bool BuildFlightArcPath(Vector3_s00cb_cde0 a, Vector3_s00cb_cde0 b, SpVectorV3* out)
{
    if (Length(a - b) < 300.0f)
        return false;

    float R = GetPlanetModel()->GetRadius() + 80.0f;

    // ---- arc leaving A toward B
    Vector3_s00cb_cde0 u = NormalizedSafe(b - a);
    float la = Length(a);
    float k = (R - la) * -4.4444445e-05f;
    Vector3_s00cb_cde0 n = NormalizedSafe(a);
    Vector3_s00cb_cde0 t = NormalizedSafe(u - Dot(n, u) * n);
    for (int i = 0; i < 12; ++i) {
        float s = (float)i * 12.5f;
        Vector3_s00cb_cde0 p = a + t * s;
        float h = ((s - 150.0f) * (s - 150.0f)) * k + R;
        out->push_back(NormalizedSafe(p) * h);
    }

    // ---- arc leaving B toward A, kept in a local array
    Vector3_s00cb_cde0 arr[12];
    {
        Vector3_s00cb_cde0 e = NormalizedSafe(a - b);
        float lb = Length(b);
        float kb = (R - lb) * -4.4444445e-05f;
        Vector3_s00cb_cde0 nb = NormalizedSafe(b);
        Vector3_s00cb_cde0 tb = NormalizedSafe(e - Dot(nb, e) * nb);
        for (int i = 0; i < 12; ++i) {
            float s = (float)i * 12.5f;
            Vector3_s00cb_cde0 p = s * tb + b;
            float h = ((s - 150.0f) * (s - 150.0f)) * kb + R;
            arr[i] = NormalizedSafeArc(p) * h;
        }
    }

    // ---- walk from the end of the first arc to the start of the second
    Vector3_s00cb_cde0 cur = out->mpEnd[-1];
    float len;
    do {
        Vector3_s00cb_cde0 w = arr[11] - cur;
        len = Length(w);
        Vector3_s00cb_cde0 wn = w * (1.0f / len);
        Vector3_s00cb_cde0 cn = NormalizedSafe(cur);
        Vector3_s00cb_cde0 st = NormalizedSafe(wn - Dot(cn, wn) * cn);
        cur = cur + st * 16.0f;
        cur = NormalizedSafe(cur) * R;
        out->push_back(cur);
    } while (33.6f <= len);

    for (int i = 11; i >= 0; --i)
        out->push_back(arr[i]);
    return true;
}

// @ 0x00cbd620
bool BuildFlightArcPathFromObjects(IPositioned* pA, IPositioned* pB, SpVectorV3* out, float ox, float oy, float oz)
{
    if (!(g_flightArcPiOver8Guard & 1)) {   // 0x0169aa70 guard
        g_flightArcPiOver8 = kPiOver4 * 0.5f;
        g_flightArcPiOver8Guard |= 1;
    }
    float s_piOver8 = g_flightArcPiOver8;    // 0x0169aa6c

    Vector3_s00cb_cde0 start = *pA->GetPosition();
    Vector3_s00cb_cde0 end = pB ? *pB->GetPosition() + Vector3_s00cb_cde0(ox, oy, oz)
                     : Vector3_s00cb_cde0(ox, oy, oz);

    if (GetPlanetModel()->DistanceBetweenPoints(&start, &end) < 200.0f)
        return false;

    Vector3_s00cb_cde0 d = end - start;
    Vector3_s00cb_cde0 mid = start + d * 0.5f;
    Vector3_s00cb_cde0 dir = NormalizedXZY(d);
    Vector3_s00cb_cde0 normal = NormalizedXZY(mid);
    float halfDist = LengthXZY(mid - start);

    float arcLen = atan2f(s_piOver8, 1.0f) * halfDist;
    Vector3_s00cb_cde0 center = mid + normal * arcLen;
    float angle = kPi + s_piOver8;
    float step = (kPi + s_piOver8 * 2.0f) * 0.015625f;
    float cosScale = halfDist / cosf(s_piOver8);
    float sinScale = arcLen / sinf(s_piOver8);

    for (int i = 0; i < 64; ++i) {
        float f1 = cosf(angle) * cosScale;
        float f2 = sinf(angle) * sinScale;
        Vector3_s00cb_cde0 p = dir * f1 + center + normal * f2;
        out->push_back(p);
        angle -= step;
        if (angle < 0.0f)
            angle += kTwoPi_s00cb_cde0;
    }
    return true;
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

// @ 0x00cbea20
bool cAttackTick::Update()
{
    bool active = !mbGuard;
    if (active) {
        Owner* owner = (Owner*)((char*)this - 0xd4);
        Obj_s00cb_e640* q = mpCtx->r118.p;
        Obj_s00cb_e640* cast = 0;
        if (q)
            cast = q->Cast(&kTypeA);
        if (q && cast) {
            Obj_s00cb_e640* obj = cast->GetObject();
            owner->SetPosition(obj->GetPosition());
            owner->SetRotation(obj->GetRotation());
        } else {
            owner->SetPosition(mpCtx->r114.p->GetPosition());
            owner->SetRotation(mpCtx->r114.p->GetRotation());
        }
        bool commOk = mpCtx->GetCommContext() == (int)0x94e412ed;
        int64_t now = mTimer.GetElapsedTime();
        if ((GetGameTimeManager()->flags & 1) == 0) {
            mTotal += now - mLast;
            mSinceLaunch += now - mLast;
            if (commOk) {
                if (mSinceLaunch > 3000)
                    mSinceLaunch = 0;
                if (mSinceLaunch == 0) {
                    Tribe* tribe = CastTribe(&mpCtx->r114);
                    if (tribe) {
                        TribeIface* iface = &tribe->iface508;
                        float tmp[6];
                        const float* b = iface->v08()->GetBounds(tmp);
                        Vector3_s00cb_e640 mid;
                        mid.x = (b[0] + b[3]) * 0.5f;
                        mid.y = (b[4] + b[1]) * 0.5f;
                        mid.z = (b[5] + b[2]) * 0.5f;
                        Vector3_s00cb_e640 start = *mpCtx->r118.p->GetPosition();
                        Vector3_s00cb_e640 end = *mpCtx->r118.p->GetPosition();
                        bool arg538 = false;
                        bool spin;
                        if (!CastTribe(&mpCtx->r118) && !CastCommodityNode(&mpCtx->r118))
                            spin = CastSpatial(&mpCtx->r118) == 0;
                        else
                            spin = false;
                        Member* member;
                        Caster* caster = CastCaster(&mpCtx->r118);
                        if (caster) {
                            City* city = caster->GetCity();
                            if (city) {
                                CityHall* hall = city->GetCityHall();
                                if (hall) {
                                    Obj_s00cb_e640* hallSub = &hall->sub34;
                                    start = *hallSub->GetPosition();
                                    Slot* slot = caster->GetCity()->GetSlot(caster->slotIndex);
                                    Tribe* tribe2 = CastTribe(&slot->r70);
                                    if (!tribe2) {
                                        arg538 = true;
                                    } else {
                                        float k = city->scale + 105.0f;
                                        Obj_s00cb_e640* sub2 = (Obj_s00cb_e640*)((char*)tribe2 + 0x34);
                                        const Vector3_s00cb_e640* a = sub2->GetPosition();
                                        const Vector3_s00cb_e640* h = hallSub->GetPosition();
                                        Vector3_s00cb_e640 d((h->x - a->x) * k * 0.004f, (h->y - a->y) * k * 0.004f,
                                                  (h->z - a->z) * k * 0.004f);
                                        const Vector3_s00cb_e640* a2 = sub2->GetPosition();
                                        start = Vector3_s00cb_e640(d.x + a2->x, a2->y + d.y, a2->z + d.z);
                                        k = city->scale + 95.0f;
                                        a = sub2->GetPosition();
                                        h = hallSub->GetPosition();
                                        d = Vector3_s00cb_e640((h->x - a->x) * k * 0.004f, (h->y - a->y) * k * 0.004f,
                                                    (h->z - a->z) * k * 0.004f);
                                        a2 = sub2->GetPosition();
                                        end = Vector3_s00cb_e640(a2->x + d.x, a2->y + d.y, a2->z + d.z);
                                        if (tribe2 == tribe) {
                                            arg538 = true;
                                            MemberVec* members = city->GetMembers();
                                            int n = (int)(members->mpEnd - members->mpBegin);
                                            for (int i = 0; i < n; ++i) {
                                                member = members->mpBegin[i];
                                                if (member->GetTypeId() == 0x1a55e4d && member->flag289 &&
                                                    sMathRandom.RandomUint32Uniform(4) == 0) {
                                                    Projectile* proj = GetNounManager()->GetProjectile();
                                                    proj->SetOwnerId(city->GetOwnerId());
                                                    proj->sub34.SetPosition(member->sub34.GetPosition());
                                                    proj->Launch(city->GetCivilization(), tribe, member,
                                                                 iface->GetTarget(), &end,
                                                                 mpCtx->GetSpeed(), false, false);
                                                }
                                            }
                                            Projectile* proj = GetNounManager()->GetProjectile();
                                            proj->SetOwnerId(city->GetOwnerId());
                                            proj->sub34.SetPosition(hallSub->GetPosition());
                                            proj->Launch(city->GetCivilization(), tribe, member,
                                                         iface->GetTarget(), &end,
                                                         mpCtx->GetSpeed(), true, false);
                                        }
                                    }
                                }
                            }
                            spin = false;
                        }
                        Projectile* proj = GetNounManager()->GetProjectile();
                        proj->SetOwnerId(tribe->GetOwnerId());
                        proj->sub34.SetPosition(&mid);
                        proj->Launch(GetNounManager()->GetOwner(iface->v10()), tribe, member,
                                     iface->GetTarget(), &start, mpCtx->GetSpeed(), arg538, spin);
                    }
                }
            }
        }
        mLast = now;
    }
    return active;
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

// @ 0x00cc0700
void FirePeaceBomb(cSPVector3_s00cc_0700 pos, cSPVector3_s00cc_0700 dir)
{
    cGameNounManager_s00cc_0700* pMgr = NounManager_s00cc_0700();
    cGameDataList* pList = pMgr->GetGameDataVector(
        (void*)0x00cd7d10, (void*)0x00ae7230, (void*)0x00ae7250, (void*)0x00b1e520,
        (const void*)0x013f94d4);
    cSimPtrVector& vec = pList->mVec;
    int count = (int)(vec.mpEnd - vec.mpBegin);
    for (int i = 0; i < count; ++i) {
        ISim* sim = vec.mpBegin[i];
        if (sim->GetOwner()->GetEmpireID() == GetPlayerEmpireID())
            continue;
        if (sim->TimedExpired())
            continue;
        Vector3_s00cc_0700 delta = sim->GetSpatial()->GetPosition() - pos;
        double sq = (double)delta.z * delta.z + (double)delta.y * delta.y
                  + (double)delta.x * delta.x + K_DIST_EPS;
        float inv = (float)(1.0 / sqrt(sq));
        float dot = dir.z * (delta.z * inv) + dir.y * (delta.y * inv)
                  + dir.x * (delta.x * inv);
        if (dot > K_FLOAT_ZERO) {
            cSimGameData* pData = sim->GetGameData((const void*)0x00b033b403);
            if (pData == 0 || pData->mSpeciesKind != 3)
                sim->TimedAdd(120000);
        }
    }
}

// @ 0x00cc0870
void cDefaultToolProjectile_s00cc_0700::SetupPathFollowing(float deltaTime, cTargetObj* pTarget, cSPVector3_s00cc_0700* pPos)
{
    mProjectileState = 5;
    cSPVector3_s00cc_0700 aim;

    if (pTarget) {
        mTargetPart = mpTool->mTargetPart;
        cTargetObj* pOldTarget = mpTarget;
        if (pTarget != pOldTarget) {
            pTarget->AddRef();
            mpTarget = pTarget;
            if (pOldTarget)
                pOldTarget->Release();
        }
        cTargetObj* pAim = pTarget->Cast(&g_013f94d4);
        const cSPVector3_s00cc_0700& targetPos = pTarget->GetPosition();
        aim = pAim->GetAimPoint(mTargetPart) - targetPos;
    } else {
        mStartPosition = *pPos;
        aim = *pPos;
    }

    VectorV3 path;
    path.mpBegin = 0;
    path.mpEnd = 0;
    path.mpCapacity = 0;

    IObj_s00cc_0700* pOwner;
    if (mpTool->mpOwner) {
        pOwner = mpTool->mpOwner;
    } else {
        ScopedRef<cLocomotiveView> held(&mLocomotive);
        pOwner = (IObj_s00cc_0700*)&mLocomotive;
    }

    FindProjectilePath(pOwner, (IObj_s00cc_0700*)pTarget, &path, aim, PathPrefsForTool((cSpaceToolData_s00cc_0700*)mpTool),
                       mpTool->GetSpread());

    mLocomotive.SetPosition(*path.mpBegin);

    cPathFollowingLocomotion_s00cc_0700* pLoco = new ("Simulator/cPathFollowingLocomotion", 0, 0, 0, 0)
        cPathFollowingLocomotion_s00cc_0700(path, mpTool->GetProjectileMotion());
    if (pLoco != mpLocomotion) {
        if (pLoco)
            pLoco->AddRef();
        ILocomotion* pOldLoco = mpLocomotion;
        mpLocomotion = pLoco;
        if (pOldLoco)
            pOldLoco->Release();
    }
    mLocomotive.SetLocomotion(mpLocomotion);

    mPathEndPoint = path.back();
    mLocomotive.Advance(deltaTime, 0);
    mBombPhase = 0;
    mPhaseTimer.Restart();
    mLastPosition = mLocomotive.GetPosition();

    if (path.mpBegin)
        HeapDelete(path.mpBegin);
}

// @ 0x00cc15b0
cCombatant_s00cc_15b0* __cdecl GetBestCityTarget(cTribe* tribe, cCombatant_s00cc_15b0* combatant)
{
    if (combatant != 0 && combatant->GetState() != 2) {
        cAttachment* a = (cAttachment*)combatant->LookupAttachment((const void*)0x0436f315);
        if (a != 0 && a->GetTribeField() == tribe)
            return combatant;
        cAttachment* b = (cAttachment*)combatant->LookupAttachment((const void*)0x0e9cb8ba);
        if (b != 0 && b->GetTribe() == tribe)
            return combatant;
    }

    Vec2b candidates;
    tribe->CopyMembers(&candidates);
    while (candidates.mpBegin != candidates.mpEnd) {
        uint32_t count = (uint32_t)(candidates.mpEnd - candidates.mpBegin);
        uint32_t index = gRandomLCG->RandomUint32Uniform(count);
        cGroundObj* obj = (cGroundObj*)candidates.mpBegin[index];
        cCombatant_s00cc_15b0* cand = obj ? &obj->mCombatant : 0;
        if (cand->GetState() == 0)
            return cand;

        cRefObj* last = candidates.mpEnd[-1];
        cRefObj* old = candidates.mpBegin[index];
        if (last != old) {
            if (last)
                last->AddRef();
            candidates.mpBegin[index] = last;
            if (old)
                old->Release();
        }
        candidates.erase(candidates.mpBegin + (count - 1), candidates.mpEnd);
    }

    cTribeMemberList* members = tribe->GetMembers();
    RefVector list;
    list.Construct((uint32_t)(members->mpEnd - members->mpBegin), &members->mAllocName);
    cRefObj** cursor = list.mpBegin;
    CopyRefs(&cursor, members->mpBegin, members->mpEnd, list.mpBegin, 0.0f);
    list.mpEnd = cursor;

    while (list.mpBegin != list.mpEnd) {
        uint32_t count = (uint32_t)(list.mpEnd - list.mpBegin);
        uint32_t index = gRandomLCG->RandomUint32Uniform(count);
        cCityObj* obj = (cCityObj*)list.mpBegin[index];
        if (obj->GetTag() != 0x1007ae63 && obj->mCombatant.GetState() == 0)
            return &obj->mCombatant;

        cRefObj* old = list.mpBegin[index];
        cRefObj* last = list.mpEnd[-1];
        if (last != old) {
            if (last)
                last->AddRef();
            list.mpBegin[index] = last;
            if (old)
                old->Release();
        }
        list.erase(list.mpBegin + (count - 1), list.mpEnd);
    }

    void* hall = tribe->GetCityHall();
    if (hall != 0)
        return &((cCityObj*)hall)->mCombatant;
    return 0;
}

// @ 0x00cc1890
void cDefaultToolProjectile_s00cc_15b0::FireGravityWave(cSPVector3_s00cc_15b0 pos, cSPVector3_s00cc_15b0 dir)
{
    int id;
    cToolExtra* extra = (cToolExtra*)mpTool->mp114;
    if (extra != 0) {
        cToolThing* thing = (cToolThing*)extra->Lookup((const void*)0x013f94d4);
        if (thing != 0)
            id = thing->GetID();
        else
            id = -1;
    } else {
        id = -1;
    }

    cAvatar* avatar = SpaceGameGet()->GetAvatar();
    cGameNounManager_s00cc_15b0* nm = NounManager_s00cc_15b0();
    sp_vector_cities* cities =
        &nm->GetGameDataVector(FUN_00cd7d10, FUN_00d3d420, FUN_00acdff0, FUN_00b1e500,
                               (const void*)0x018c43e8)->vec;

    RefVec list;
    list.Construct((uint32_t)(cities->mpEnd - cities->mpBegin), &cities->mAllocName);
    cRefObj** cursor = list.mpBegin;
    CopyRefs(&cursor, (cRefObj**)cities->mpBegin, (cRefObj**)cities->mpEnd, list.mpBegin,
             *(const uint32_t*)&pos.x);
    list.mpEnd = cursor;

    int itemCount = (int)(cursor - list.mpBegin);
    for (int i = 0; i < itemCount; ++i) {
        cCityObj* city = (cCityObj*)list.mpBegin[i];
        const Vector3_s00cc_15b0& p = city->mCombatant.GetPosition();
        float dx = p.x - pos.x;
        float dy = p.y - pos.y;
        float dz = p.z - pos.z;
        float inv = 1.0f / (float)sqrt((dx * dx + dz * dz) + dy * dy + 1e-8f);
        float dot = (inv * dx) * dir.x + dir.z * (dz * inv) + dir.y * (dy * inv);
        if (dot > 0.0f)
            avatar->FUN_00ffa900(city, id);
    }

    nm = NounManager_s00cc_15b0();
    cities = &nm->GetGameDataVector(FUN_00cd7d10, FUN_00d3d420, FUN_00accbb0, FUN_00b1e500,
                                    (const void*)0x018c6d19)->vec;

    cRefObj** wave = 0;
    int waveCount = (int)(cities->mpEnd - cities->mpBegin);
    if (waveCount != 0)
        wave = (cRefObj**)EAlloc((uint32_t)waveCount * 4, "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
    cRefObj** wcursor = wave;
    CopyRefs(&wcursor, (cRefObj**)cities->mpBegin, (cRefObj**)cities->mpEnd, wave,
             *(const uint32_t*)&pos.x);

    int waveSize = (int)(wcursor - wave);
    for (int i = 0; i < waveSize; ++i) {
        cCityObj* city = (cCityObj*)wave[i];
        const Vector3_s00cc_15b0& p = city->mCombatant.GetPosition();
        float dx = p.x - pos.x;
        float dy = p.y - pos.y;
        float dz = p.z - pos.z;
        float inv = 1.0f / (float)sqrt((dx * dx + dz * dz) + dy * dy + 1e-8f);
        float dot = (inv * dx) * dir.x + (dy * inv) * dir.y + (dz * inv) * dir.z;
        if (dot > 0.0f) {
            cCityObj* owner = city->GetOwnerObj();
            owner->mCombatant.TriggerWave(owner->m158, GetPlayerEmpireID(), 0,
                                          (const void*)0x0169a414, 0);
        }
    }

    for (cRefObj** p = wave; p < wcursor; ++p) {
        if (*p)
            (*p)->Release();
    }
    if (wave != 0 && ((uint32_t*)wave)[-1] != 0)
        EFree(wave);
    for (cRefObj** p = list.mpBegin; p < list.mpEnd; ++p) {
        if (*p)
            (*p)->Release();
    }
    if (list.mpBegin != 0 && ((uint32_t*)list.mpBegin)[-1] != 0)
        EFree(list.mpBegin);
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

// @ 0x00cc26a0
int FindNearestCreature(float fX, float fY, float fZ, bool bGround, bool bAir)
{
    cGameNounManager_s00cc_22c0* pNouns = NounManager_s00cc_22c0();
    uint8_t* pVector = (uint8_t*)pNouns->GetGameDataVector(nullptr, nullptr, nullptr, nullptr,
                                                          (const void*)&gGameModeTribe);
    int nCount = (*(int*)(pVector + 8) - *(int*)(pVector + 4)) >> 2;

    int pBest = 0;
    float fBestDistance = 0.0f;
    for (int i = 0; i < nCount; ++i) {
        int pCreature = *(int*)(*(int*)(pVector + 4) + i * 4);
        int nKind = *(int*)((uint8_t*)pCreature + 0x714);
        if (IsCinematicMode(1))
            continue;
        void* pAnimated = *(void**)((uint8_t*)pCreature + 0x6c8);
        if (pAnimated != nullptr && ((cSPCreatureBase*)((uint8_t*)pAnimated + 8))->PlayIdleAnimation(8, 0))
            continue;

        int pCandidate = 0;
        if (bAir && (nKind == 2 || nKind == 4 || nKind == 5))
            pCandidate = pCreature;
        if (bGround && (nKind == 0 || nKind == 3))
            pCandidate = pCreature;

        if (pCandidate != 0) {
            Vec3_s00cc_22c0* pPosition = (Vec3_s00cc_22c0*)(*(void* (__thiscall*)(void*))(**(uint32_t**)((uint8_t*)pCandidate + 0x34) + 0x2c))
                                     ((uint8_t*)pCandidate + 0x34);
            float fDistance = (fZ - pPosition->mZ) * (fZ - pPosition->mZ) +
                              (fY - pPosition->mY) * (fY - pPosition->mY) +
                              (fX - pPosition->mX) * (fX - pPosition->mX);
            if (pBest == 0 || fDistance < fBestDistance) {
                pBest = pCandidate;
                fBestDistance = fDistance;
            }
        }
    }
    return pBest;
}

// @ 0x00cc27f0
int cSpatialObjectView::UpdateState()
{
    if (mpObject == nullptr)
        return 0;

    int nState = mViewState;
    if (nState == 0) {
        UpdateMissileEffect(this, mpObject, 0);
    } else if (nState == 1) {
        Vec3_s00cc_22c0* pDirection = (Vec3_s00cc_22c0*)(*(void* (__thiscall*)(void*))(**(uint32_t**)mpObject + 0x18))(mpObject);
        if (pDirection->mX != gDefaultOrientation || pDirection->mY != 0.0f ||
            pDirection->mZ != 0.0f) {
            if (!IsWaterSurface())
                UpdateBeamEffect(this, mpObject, 0);
        }
        UpdateMissileEffect(this, mpObject, 1);
    } else if (nState == 2) {
        return (int)GetAoEKind();
    }
    return 1;
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
