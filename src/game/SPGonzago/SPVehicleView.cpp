// src/game/SPGonzago/SPVehicleView.cpp -- migrated from slice(s) s00e956f0, s00e94b60, s00e93c60 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPVehicleView.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "SP/cSPTimer.h"
#include "SP/cTribe.h"

// unnamed retail callees and globals (address in the comment)
extern uint8_t  gShowVehiclePaths;                           // 0x016c5c88
extern const float    kZeroPoint1;                           // 0x01488874  (0.1f)
extern const float    kExactlyOne;                           // 0x01485720  (1.0f)
extern const float    kEmitterDivisor;                       // 0x015a8aac
extern uint32_t kEffectId3c;                                 // 0x015a8a3c
extern uint32_t kEffectId40;                                 // 0x015a8a40
extern uint32_t kEffectId44;                                 // 0x015a8a44
#include <math.h>
#include <new>
#include "SP/cCityTerritory.h"
#include "SP/cCombatant.h"
#include "SP/cGameData.h"
#include "SP/cLocomotiveObject.h"
#include "SP/cPlanetModel.h"
#include "SP/cPropertyManager.h"
#include "SP/cSpatialObject.h"
#include "SP/cVehicle.h"

// ---- items of slice s00e93c60 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void pv##n();
struct Vec3 { float x, y, z; };
namespace EA {
namespace Random {
class RandomLinearCongruential_s00e9_3c60 {
 public:
    uint32_t RandomUint32Uniform(uint32_t range);            // 0x00a68fb0
};
}
}
extern EA::Random::RandomLinearCongruential_s00e9_3c60 sMathRandom;     // 0x01601760
extern uint8_t  gShowVehiclePaths;                           // 0x016c5c88
extern const float    kZeroPoint1;                           // 0x01488874  (0.1f)
extern const float    kExactlyOne;                           // 0x01485720  (1.0f)
extern const float    kEmitterDivisor;                       // 0x015a8aac
extern uint32_t kEffectId3c;                                 // 0x015a8a3c
extern uint32_t kEffectId40;                                 // 0x015a8a40
extern uint32_t kEffectId44;                                 // 0x015a8a44
namespace SP {
class cSpatialObjectView;
}
namespace SP {
class cTribe_s00e9_3c60;
}
namespace SP {
class cTribeView;
}
namespace SP {
class cVehicleView;
}
namespace SP {
class cEmitter;
}
namespace SP {
class cEffectTarget;
}
namespace SP {
class cEffectsView;
}
namespace SP {
class cSPTimer_s00e9_3c60 {
 public:
    void               Start();                              // 0x00bc30f0
    void               Restart();                            // 0x00bc3130
    unsigned long long GetElapsedTime();                     // 0x00bc3190
    void               FUN_00bc3170();                       // 0x00bc3170
    uint8_t pad[0x20];
};
}
namespace SP {
class cSpatial {
 public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual const Vec3* GetPosition();                       // +0x2c
    PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25)
    virtual float* GetBounds();                              // +0x68
    PV(27) PV(28) PV(29) PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36)
    virtual void  SetPos(const Vec3* p);                     // +0x94
    virtual Vec3* GetVec3();                                 // +0x98
    PV(39) PV(40) PV(41) PV(42)
    virtual cEffectsView* GetEffectsView();                  // +0xac
    virtual void* SlotB0();                                  // +0xb0
    uint8_t pad[0x1c];
};
}
namespace SP {
class cEffectsView {
 public:
    uint8_t  pad00[0x04];
    uint32_t mFlags_4;                                       // +0x04
    uint8_t  pad08[0x4c - 0x08];
    Vec3     mColor_4c;                                      // +0x4c
    float    mFloat_58;                                      // +0x58
    uint8_t  mState_5c;                                      // +0x5c
};
}
namespace SP {
class cEmitter {
 public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
    PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24)
    virtual int  EmitterCount(void* target);                 // +0x64
    PV(26) PV(27)
    virtual void EmitterAdd(void* target, uint32_t id, int mode, float f, int i);   // +0x70
    virtual void EmitterAdd2(void* target, uint32_t id, float f, int i);            // +0x74
    PV(30)
    virtual void EmitterScale(void* target, float f);        // +0x7c
};
}
namespace SP {
struct cEffectFlags {
    uint32_t mBit0_13  : 14;
    uint32_t mBit14    : 1;                                  // visibility / hold flag
    uint32_t mBit15_17 : 3;
    uint32_t mBit18    : 1;                                  // "hidden" flag
    uint32_t mBit19_31 : 13;
};
}
namespace SP {
class cEffectTarget {
 public:
    uint8_t  pad00[0x04];
    cEffectFlags mFlags_4;                                   // +0x04
};
}
namespace SP {
class cTribeSubObj {
 public:
    PV(0)
    virtual void Slot4();                                    // +0x04
    PV(2)
    virtual void SlotC(int a);                               // +0x0c
    PV(4)
    virtual bool Slot10();                                   // +0x10
};
}
namespace SP {
class cTribe_s00e9_3c60 {
 public:
    PV(0) PV(1) PV(2)
    virtual void* AsInterface(uint32_t id);                  // +0x0c 0x00c8e420
    PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17)
    PV(18) PV(19) PV(20) PV(21)
    virtual void* GetTribe();                                // +0x58
    PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36)
    PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46)
    virtual void* GetList();                                 // +0xbc
    uint8_t  pad00[0x34 - 0x04];
    cSpatial mSpatial;                                       // +0x34
    uint8_t  pad54[0x120 - (0x34 + sizeof(cSpatial))];
    cTribe_s00e9_3c60*  mpTribe_120;                                    // +0x120
    uint8_t  pad124[0x170 - 0x124];
    uint32_t mFlags_170;                                     // +0x170
    uint8_t  pad174[0x1e8 - 0x174];
    Vec3     mPosA_1e8;                                      // +0x1e8
    Vec3     mPosB_1f4;                                      // +0x1f4
    Vec3     mPosC_200;                                      // +0x200
    Vec3     mPosD_20c;                                      // +0x20c
    uint8_t  mByte_218;                                      // +0x218
    uint8_t  pad219[0x21c - 0x219];
    int      mInt_21c;                                       // +0x21c
    uint8_t  pad220[0x234 - 0x220];
    void*    mpObj_234;                                      // +0x234
    uint8_t  pad238[0x2d0 - 0x238];
    cTribeSubObj* mpSub_2d0;                                 // +0x2d0
    uint8_t  pad2d4[0x556 - 0x2d4];
    uint8_t  mByte_556;                                      // +0x556

    bool FUN_00c9bf10();                                     // 0x00c9bf10
    int  FUN_00a1ad10b();                                    // 0x00a1ad10
    void ChooseNewHutModel();                                // 0x00c99c30
};
}
namespace SP {
struct OpaqueModel { uint8_t b[0x11]; };
}
namespace SP {
class cSpatialObjectView {
 public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
    virtual bool  Slot24();                                  // +0x24
    virtual void  Slot28(void* a, void* model);              // +0x28
    virtual cEffectsView* Slot2c();                          // +0x2c
    virtual void* Slot30();                                  // +0x30
    PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
    virtual void* Slot58();                                  // +0x58
    PV(23) PV(24) PV(25)
    virtual float* Slot68();                                 // +0x68
    PV(27) PV(28) PV(29) PV(30) PV(31) PV(32) PV(33)
    virtual bool  Slot88();                                  // +0x88
    PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42)
    virtual cEffectsView* SlotAC();                          // +0xac
    virtual void* SlotB0();                                  // +0xb0
    PV(45)
    virtual cTribe_s00e9_3c60* AsInterface(uint32_t id);                // +0xb8
    virtual void* SlotBC();                                  // +0xbc
    PV(48)
    virtual void  SlotC4(cEffectsView* e, int a, int b, int c);  // +0xc4

    uint8_t  pad04[0x08];
    cSpatialObjectView* mpObject;                            // +0x0c
    uint8_t  pad10[0x08];
    Vec3     mColor;                                         // +0x18
    OpaqueModel mModel_24;                                   // +0x24
    uint8_t  mbTransition_35;                                // +0x35
    uint8_t  pad36[0x02];
    uint32_t mTimerTarget_38;                                // +0x38
    uint32_t mTimerTargetHi_3c;                              // +0x3c
    cSPTimer_s00e9_3c60 mTimer_40;                                      // +0x40
    int      mState_60;                                      // +0x60
    uint8_t  pad64[0x78 - 0x64];
    cSPTimer_s00e9_3c60 mTimer_78;                                      // +0x78
    uint8_t  pad98[0x08];
    uint32_t mMovementSoundID_a0;                            // +0xa0
    uint8_t  padA4[0x0c];
    uint8_t  mbZoomOutScale_b0;                              // +0xb0

    void   MakeView_740(void* a, void* b, void* c, void* d); // 0x00e92740
    void   Init(void* a);                                    // 0x00e92910
    void   HandleSimulationUpdateBase(void* a, void* b);     // 0x00e92ca0
    cTribeView* CreateTribeView(cTribe_s00e9_3c60* iface);              // 0x00e93c60
    void   SetupTribeView(void* a, void* b, void* c, void* d); // 0x00e93d70

    bool   GetEffect(uint32_t id);                           // 0x00c88910
    bool   IsEffectActive(uint32_t id);                      // 0x00c88940
    void   EnableEffect(uint32_t id, int on);                // 0x00c8ad30
    void*  CreateEffect(uint32_t id, int a, uint32_t id2);   // 0x00c8b130
    void*  GetEffectObj(uint32_t id);                        // 0x00c888e0
    void   RemoveEffect(uint32_t id);                        // 0x00c8b1a0
    void   SetEffectFloatA(uint32_t id, float f);            // 0x00c88a00
    void   SetEffectFloatB(uint32_t id, float f);            // 0x00c8a020
    void   SetEffectX(uint32_t id);                          // 0x00c8b210
};
}
namespace SP {
class cTribeView : public cSpatialObjectView {
 public:
    cTribeView();                                            // 0x00e93b80

    void Init(void* a, void* b, void* c, void* d);           // 0x00e94970
    void UpdateHighlight(cTribe_s00e9_3c60* param_2);                   // 0x00e93e10
    void UpdateDamageState(cTribe_s00e9_3c60* param_2, cTribe_s00e9_3c60* param_3);// 0x00e93f50
    void UpdateMatingEffect(cTribe_s00e9_3c60* param_2);                // 0x00e94450
    void HandleSimulationUpdate(void* a, void* b);           // 0x00e946b0
    void FUN_00e93160(int a, int b);                         // 0x00e93160
};
}
namespace SP {
class cVehicleView : public cSpatialObjectView {
 public:
    void Init(void* a);                                      // 0x00e949c0
    void ToggleShowPaths();                                  // 0x00e94a00
};
}
namespace SP {
class cEffectToggle {
 public:
    uint8_t mbActive;                                        // +0x00
    void Update(int a2, float t, float f2, cEmitter* emitter, cEffectTarget* target); // 0x00e94a10
};
}
namespace SP {
void __stdcall FUN_00e948b0(cEmitter* self, cEffectTarget* target);              // 0x00e948b0
}
namespace SP {
void __stdcall FUN_00e94900(cEmitter* self, cEffectTarget* target);              // 0x00e94900
}
namespace SP {
void __stdcall FUN_00e94ad0(cEmitter* self, cEffectTarget* target, int i);       // 0x00e94ad0
}
// ---- items of slice s00e93c60 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern EA::Random::RandomLinearCongruential_s00e9_3c60 sMathRandom;     // 0x01601760

// ---- items of slice s00e94b60 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl FUN_00f473a0(int size, const char* file, int a, int b, int c, int d); // 0x00f473a0 operator_new
extern "C" void* __cdecl FUN_00b5b800(void);                            // 0x00b5b800 SP::GetCurrentGameMode
extern       void  __cdecl FUN_00572020(uint32_t handle, int flag);     // 0x00572020
extern       void* __cdecl FUN_00f47380(void* p);                       // 0x00f47380 operator_delete_array
extern       void  __cdecl FUN_0059c190(float* out, void* quat);        // 0x0059c190 Matrix3FromQuaternion
extern       const char aSimulatorCVehicleView[];                       // 0x01460cdc "Simulator/cVehicleView"
extern float  DAT_014853e0;                    // 0x014853e0 tether angle bias
extern float  DAT_016c5ca0;                    // 0x016c5ca0 mAnimator default
extern float  DAT_016c5ca4;                    // 0x016c5ca4 towed position x default
extern float  DAT_016c5ca8;                    // 0x016c5ca8 towed position y default
extern float  DAT_016c62ac;                    // 0x016c62ac
extern float  DAT_016c62b0;                    // 0x016c62b0
extern float  DAT_016c62b4;                    // 0x016c62b4
extern float  DAT_016c6288[];                  // 0x016c6288 identity matrix source
extern uint32_t DAT_015a8a48;                  // 0x015a8a48
extern uint32_t DAT_015a8a4c;                  // 0x015a8a4c
extern uint32_t DAT_015a8a50;                  // 0x015a8a50
extern void*  DAT_01654c10;                    // 0x01654c10 space game-mode singleton
struct Vec3_s00e9_4b60 {
    float x, y, z;
    Vec3_s00e9_4b60() {}
    Vec3_s00e9_4b60(float a, float b, float c) { x = a; y = b; z = c; }
};
#define VFN(obj, off) (*(void**)((char*)(*(void**)obj) + (off)))
extern "C" void* __cdecl FUN_00b3d520(Vec3_s00e9_4b60* pos, void* parent);        // 0x00b3d520 SP::GonzagoModelWorld
class tHost {
public:
    void   __thiscall FUN_00b63890();                 // 0x00b63890 SP::cGonzagoTimer::cGonzagoTimer
    void   __thiscall FUN_00b638b0();                 // 0x00b638b0 SP::cGonzagoTimer::~cGonzagoTimer
    void*  __thiscall FUN_00c9f650(void* out);        // 0x00c9f650
    void   __thiscall FUN_0041cb40(void* src);        // 0x0041cb40 rw::math::Matrix3::Assign
    void   __thiscall FUN_005a2d90(float angle);      // 0x005a2d90 cXform::PreRotateX
};
struct cTransform {
    uint16_t mFlags;              // +0x00
    uint16_t mModificationCount;  // +0x02
    float    mRotation[9];        // +0x04
    Vec3_s00e9_4b60     mTranslation;        // +0x28
    float    mScale;              // +0x34
};
class cSpatialObjectView_s00e9_4b60 {
public:
    cSpatialObjectView_s00e9_4b60();                       // 0x00e92af0
    virtual ~cSpatialObjectView_s00e9_4b60();              // 0x00e92660
    uint8_t m004[0x14];                         // +0x04
    Vec3_s00e9_4b60    mColor;                             // +0x18
    uint8_t m024[0x14];                         // +0x24 -> +0x38
};
class cVehicleView_s00e9_4b60 : public cSpatialObjectView_s00e9_4b60 {
public:
    uint8_t  m038[0x20];                        // +0x038 cGonzagoTimer (effects)
    uint8_t  m058[0x20];                        // +0x058 cGonzagoTimer (path)
    uint8_t  m078[0x20];                        // +0x078 cGonzagoTimer (trail)
    uint32_t m98;                               // +0x098 elapsed-timer running handle
    uint32_t m9c;                               // +0x09c elapsed-timer callback
    uint32_t ma0;                              // +0x0a0 movement sound id
    float    ma4;                               // +0x0a4 elapsed-timer offset
    float    ma8;                               // +0x0a8 desired scale
    float    mac;                               // +0x0ac current scale
    uint8_t  mb0;                               // +0x0b0 zoom-out scale (byte)
    uint8_t  mPad_b1[3];                        // +0x0b1
    float    mb4;                               // +0x0b4 animator / towed x
    float    mb8;                               // +0x0b8 towed position y
    float    mbc;                               // +0x0bc towed position z
    float    mc0;                               // +0x0c0
    float    mc4;                               // +0x0c4 current tilt angle
    void*    mc8;                               // +0x0c8 selection effect
    void*    mcc;                               // +0x0cc length-of-tether-at-rest handle

    cVehicleView_s00e9_4b60();
    ~cVehicleView_s00e9_4b60();

    void* __thiscall FUN_00e94d10(void* param_1);
    void  __thiscall FUN_00e94e50(int param_2);
    void  __thiscall UpdateTowedItem(void* param_2, void* param_3, int param_4, char param_5);  // 0x00e94f30 (cVehicleView::UpdateTowedItem)
    void  __thiscall ConnectBalloonString(int param_2, void* param_3);  // 0x00e953a0 (cVehicleView::ConnectBalloonString)
};
// ---- items of slice s00e94b60 end

// ---- items of slice s00e956f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);
extern "C" double __cdecl sqrt(double);
#pragma warning(disable: 4100)
#pragma intrinsic(sin, cos, sqrt)
enum GameModeIDs {
    kGameCiv      = 0x1654C04,
    kGameSpace    = 0x1654C05,
    kScenarioMode = 0x1654C10,
};
enum VehicleLocomotion { kVehicleLand = 0, kVehicleWater = 1, kVehicleAir = 2 };
struct Vector3 { float x, y, z; };
struct Quaternion { float x, y, z, w; };
struct Matrix3 {
    float m[3][3];   // rows: x axis, y axis, z axis
    Matrix3& Assign(const Matrix3& other);   // 0x0041CB40
};
struct cSPTransform_s00e9_56f0 {
    uint16_t mFlags;
    uint16_t mModificationCount;
    Vector3  mOffset;
    float    mScale;
    Matrix3  mRotation;

    cSPTransform_s00e9_56f0& operator=(const cSPTransform_s00e9_56f0& other);   // 0x00537DC0
    void Rotate(float angle);                            // 0x006B9050
    void RotateY(float angle);                           // 0x004099B0
    void PreRotateX(float angle);                        // 0x005A2D90

    // offset += rotation * (v * scale)
    void PreTranslate(const Vector3& v) {
        float x = v.x * mScale;
        float y = v.y * mScale;
        float z = v.z * mScale;
        mFlags |= 4;
        mModificationCount++;
        mOffset.x += mRotation.m[0][0] * x + mRotation.m[1][0] * y + mRotation.m[2][0] * z;
        mOffset.y += mRotation.m[0][1] * x + mRotation.m[1][1] * y + mRotation.m[2][1] * z;
        mOffset.z += mRotation.m[0][2] * x + mRotation.m[1][2] * y + mRotation.m[2][2] * z;
    }
};
namespace SP {
extern const Matrix3 kIdentityMatrix3;   // 0x016C624C
}
namespace SP {
extern const Vector3 kWobbleAxisSin;     // 0x016C6270
}
namespace SP {
extern const Vector3 kWobbleAxisCos;     // 0x016C627C
}
namespace SP {
extern float gWobbleAmplitude;           // 0x015A8A54
}
namespace SP {
extern float gScaleOverrideThreshold;    // 0x0169CAB4
}
namespace SP {
extern bool  gShowDebugVehicleEffect;    // 0x0168BCF4
}
namespace SP {
extern uint32_t gModelWorldEffectGroup;  // 0x015A8A44
}
namespace SP {
extern uint32_t gVehicleSpeedSoundParam; // 0x015A8AB0
}
namespace SP {
uint32_t GetCurrentGameMode();                                        // 0x00B5B800
}
namespace SP {
Matrix3* Matrix3FromQuaternion(Matrix3* out, const Quaternion& q);    // 0x0059C190
}
namespace SP {
void Start3dSoundByName(uint32_t name, uint32_t handle, float x, float y, float z);  // 0x00571F80
}
namespace SP {
void SetSoundPosition(uint32_t handle, float x, float y, float z);   // 0x009FBC50
}
namespace SP {
namespace EditorUtils {
void PlayEditorSound(uint32_t handle, uint32_t param, float value, int flag);  // 0x00435F40
}
}
namespace SP {
void AttachSelectionEffect(class cSpatialObject_s00e9_56f0* obj, void* effect, int flag);  // 0x01043860
}
namespace SP {
void AttachRolloverEffect(class cSpatialObject_s00e9_56f0* obj, void* effect, int flag);   // 0x01043A50
}
namespace SP {
class cSPTimer_s00e9_56f0 { public:
    char mData[0x20];
    void Stop();                          // 0x00BC3110
    void Restart();                       // 0x00BC3130
    uint64_t GetElapsedTime();            // 0x00BC3190
    bool IsRunning();                     // 0x00FEBA90
};
}
namespace SP {
struct cModel {
    void*        vtable;
    uint32_t     mFlags;                  // +0x04
    cSPTransform_s00e9_56f0 mTransform;              // +0x08
    char         _pad40[0x0c];
    Vector3      mSelectionPosition;      // +0x4c
    char         _pad58[4];
    uint8_t      mHighlight;              // +0x5c
};
}
namespace SP {
struct IModelWorld {
virtual void _v00();
virtual void _v04();
virtual void _v08();
virtual void _v0c();
virtual void _v10();
virtual void _v14();
virtual void _v18();
virtual void _v1c();
virtual void _v20();
virtual void _v24();
virtual void _v28();
virtual void _v2c();
virtual void _v30();
virtual void _v34();
virtual void _v38();
virtual void _v3c();
virtual void _v40();
virtual void _v44();
virtual void _v48();
virtual void _v4c();
virtual void _v50();
virtual void _v54();
virtual void _v58();
virtual void _v5c();
virtual void _v60();
virtual void _v64();
virtual void _v68();
virtual void _v6c();
    /* 70h */ virtual void StopEffectGroup(cModel* model, uint32_t group, int a, float b, uint32_t id);
};
}
namespace SP {
IModelWorld* GonzagoModelWorld();          // 0x00B3D520
}
namespace SP {
struct IVisualEffect {
virtual void _v00();
virtual void _v04();
virtual void _v08();
virtual void _v0c();
virtual void _v10();
virtual void _v14();
virtual void _v18();
virtual void _v1c();
virtual void _v20();
virtual void _v24();
virtual void _v28();
virtual void _v2c();
virtual void _v30();
virtual void _v34();
virtual void _v38();
virtual void _v3c();
    virtual void _v40();
    /* 44h */ virtual void SetParams(int param, float* values, int count);
};
}
namespace SP {
class cSpatialObject_s00e9_56f0 {
public:
virtual void _v00();
virtual void _v04();
virtual void _v08();
virtual void _v0c();
virtual void _v10();
virtual void _v14();
virtual void _v18();
virtual void _v1c();
    virtual void _v20();
    /* 24h */ virtual bool IsRolledOver();
virtual void _v28();
virtual void _v2c();
virtual void _v30();
virtual void _v34();
virtual void _v38();
virtual void _v3c();
virtual void _v40();
virtual void _v44();
virtual void _v48();
virtual void _v4c();
    /* 50h */ virtual bool IsSelected();
virtual void _v54();
virtual void _v58();
virtual void _v5c();
virtual void _v60();
virtual void _v64();
virtual void _v68();
virtual void _v6c();
virtual void _v70();
virtual void _v74();
virtual void _v78();
virtual void _v7c();
virtual void _v80();
    virtual void _v84();
    /* 88h */ virtual bool HasModelChanged();
virtual void _v8c();
virtual void _v90();
virtual void _v94();
virtual void _v98();
virtual void _v9c();
virtual void _va0();
virtual void _va4();
virtual void _va8();
    /* ach */ virtual cModel* GetModel();
virtual void _vb0();
virtual void _vb4();
    /* b8h */ virtual void* Cast(uint32_t type);

    // effect list (non-virtual)
    IVisualEffect* GetEffectObject(uint32_t id);                             // 0x00C888E0
    bool GetEffect(uint32_t id);                                             // 0x00C88910
    void StartEffect(uint32_t id, int restart);                              // 0x00C88980
    void SetEffectRange(uint32_t id, float range);                           // 0x00C88A00
    void SetEffectPosition(uint32_t id, const Vector3* pos);                 // 0x00C88A30
    void SetEffectScale(uint32_t id, float scale);                           // 0x00C8A020
    void StopEffect(uint32_t id, int hard);                                  // 0x00C8AD30
    void DestroyAllEffects(int flag);                                        // 0x00C8B0A0
    void CreateEffect(uint32_t effectID, int group, uint32_t id);            // 0x00C8B130
    void CreateAttachedEffect(uint32_t effectID, int group, uint32_t id);    // 0x00C8B1B0
    bool SetEffectActive(uint32_t effectID, uint32_t id, bool active, int a);// 0x00C8B220
};
}
namespace SP {
class cLocomotiveObject_s00e9_56f0 {
public:
virtual void _v00();
virtual void _v04();
virtual void _v08();
virtual void _v0c();
virtual void _v10();
virtual void _v14();
virtual void _v18();
virtual void _v1c();
virtual void _v20();
virtual void _v24();
virtual void _v28();
    /* 2ch */ virtual const Vector3& GetPosition();
    /* 30h */ virtual const Quaternion& GetOrientation();
    /* 34h */ virtual float GetScale();
virtual void _v38();
virtual void _v3c();
virtual void _v40();
virtual void _v44();
virtual void _v48();
virtual void _v4c();
virtual void _v50();
virtual void _v54();
    /* 58h */ virtual bool IsPlayerOwned();
virtual void _v5c();
virtual void _v60();
virtual void _v64();
virtual void _v68();
    virtual void _v6c();
    /* 70h */ virtual float GetBoundingRadius();
    /* 74h */ virtual float GetFootprintRadius();
virtual void _v78();
virtual void _v7c();
virtual void _v80();
virtual void _v84();
virtual void _v88();
virtual void _v8c();
virtual void _v90();
virtual void _v94();
virtual void _v98();
virtual void _v9c();
virtual void _va0();
virtual void _va4();
virtual void _va8();
virtual void _vac();
virtual void _vb0();
virtual void _vb4();
virtual void _vb8();
virtual void _vbc();
virtual void _vc0();
virtual void _vc4();
    virtual void _vc8();
    /* cch */ virtual float GetStandardSpeed();

    const Vector3& GetVelocity();         // 0x00D20610
};
}
namespace SP {
class cCombatant_s00e9_56f0 {
public:
virtual void _v00();
virtual void _v04();
virtual void _v08();
virtual void _v0c();
virtual void _v10();
virtual void _v14();
virtual void _v18();
virtual void _v1c();
virtual void _v20();
virtual void _v24();
virtual void _v28();
virtual void _v2c();
virtual void _v30();
virtual void _v34();
virtual void _v38();
    /* 3ch */ virtual bool IsStunned();

    float GetHealthPercentage();          // 0x00BFC490
    bool  IsUnderAttack();                // 0x00BFC5D0
    bool  IsStaticClingStunned();         // 0x00BFC600
};
}
namespace SP {
struct tAttachedEffect {        // 16 bytes
    class cGameData_s00e9_56f0* mpObject;  // +0x00
    int      _pad04;
    uint32_t mEffectID;         // +0x08
    bool     mbActive;          // +0x0c
};
}
namespace SP {
struct tAttachedEffects { tAttachedEffect* mpBegin; tAttachedEffect* mpEnd; };
}
namespace SP {
class cGameData_s00e9_56f0 {
public:
virtual void _v00();
virtual void _v04();
virtual void _v08();
virtual void _v0c();
virtual void _v10();
virtual void _v14();
virtual void _v18();
virtual void _v1c();
virtual void _v20();
virtual void _v24();
virtual void _v28();
virtual void _v2c();
virtual void _v30();
virtual void _v34();
virtual void _v38();
virtual void _v3c();
virtual void _v40();
virtual void _v44();
virtual void _v48();
    /* 4ch */ virtual uint32_t GetPoliticalID();

    struct tOwnerInfo { void* mpOwner; int _pad[3]; int mKind; };
    tOwnerInfo* GetOwnerInfo();            // 0x00CA71D0
    bool IsEffectAttached();               // 0x0104BD50 (on tAttachedEffect::mpObject)
};
}
namespace SP {
struct tGameDataList { cGameData_s00e9_56f0** mpBegin; cGameData_s00e9_56f0** mpEnd; };
}
namespace SP {
class cVehicle_s00e9_56f0 {
public:
    char              _pad00[0x34];
    cLocomotiveObject_s00e9_56f0 mLocomotive;        // +0x34
    char              _pad38[0x84 - 0x38];
    uint32_t          mFlags;             // +0x84
    char              _pad88[0xd9 - 0x88];
    bool              mbHideZoomOut;      // +0xd9
    char              _padda[0x2a4 - 0xda];
    uint8_t           mCargoFlags;        // +0x2a4
    char              _pad2a5[0x508 - 0x2a5];
    cCombatant_s00e9_56f0        mCombatant;         // +0x508
    char              _pad50c[0xaf4 - 0x50c];
    bool              mbUFOCarried;       // +0xaf4
    char              _padaf5[0xb1c - 0xaf5];
    int               mLocomotion;        // +0xb1c
    char              _padb20[0xbcd - 0xb20];
    bool              mbDead;             // +0xbcd
    char              _padbce[0xc58 - 0xbce];
    float             mSpeedStat;         // +0xc58

    Vector3  GetSelectionPosition();       // 0x00C9F650
    float    GetSoundPitch();              // 0x00C9EBF0
    float    GetSoundParam();              // 0x00C9EC00
    tAttachedEffects* GetAttachedEffects();// 0x00C9EC70
    bool     ScaleAnimationSpeed();        // 0x00C9EEF0
    bool     IsHovering();                 // 0x00C9EF20
    uint32_t GetMovementSound();           // 0x00CA0040
    int      PopViewEvent();               // 0x00CA6F70
};
}
namespace SP {
class cCityTerritory_s00e9_56f0 { public: char _pad[0x80]; class cCivTutorial* mpTutorial; };
}
namespace SP {
class cCivTutorial {
public:
    bool IsActive();                       // 0x00D09660
    bool IsHighlighted(cVehicle_s00e9_56f0* vehicle); // 0x00D09740
};
}
namespace SP {
class cCivModeStrategy {
public:
    cCityTerritory_s00e9_56f0* GetPlayerTerritory();             // 0x00CF74F0
    bool HasCivTutorialOccurred(uint32_t id);         // 0x00CF7830
    cVehicle_s00e9_56f0* GetFirstVehicle(int index);             // 0x00CF7D40
};
}
namespace SP {
cCivModeStrategy* CivModeStrategy();                   // 0x00CF74C0
}
namespace SP {
class cGameTimeManager { public: char _pad[0x48]; uint8_t mPauseFlags; };
}
namespace SP {
cGameTimeManager* GameTimeManager();                   // 0x00B3D380
}
namespace SP {
class cPlanetModel_s00e9_56f0 { public: char _pad[0xf0]; bool mbIsRetro; };
}
namespace SP {
cPlanetModel_s00e9_56f0* PlanetModel();                           // 0x00B3D350
}
namespace SP {
class cNounManager {
public:
    tGameDataList* GetVehicleList();                   // 0x00AE73B0
    char* GetCityByPoliticalID(uint32_t id);           // 0x00B25F40
};
}
namespace SP {
cNounManager* NounManager();                           // 0x00B3D300
}
namespace SP {
class InputHost { public: void GetAnglesB(float* a, float* b, float* c); };   // 0x00B0F240
}
namespace SP {
InputHost* GetInputHost();                             // 0x00B3D280
}
namespace SP {
struct Property {
    char _pad[0x12];
    int16_t mnType;
    float* GetFloat();                                // 0x0041EA70
};
}
namespace SP {
class PropertyList {
public:
virtual void AddRef();
virtual void Release();
virtual void _v08();
virtual void _v0c();
virtual void _v10();
virtual void _v14();
virtual void _v18();
virtual void _v1c();
virtual void _v20();
    /* 24h */ virtual bool GetProperty(uint32_t id, Property*& prop);
};
}
namespace SP {
class cPropertyManager_s00e9_56f0 {
public:
virtual void _v00();
virtual void _v04();
virtual void _v08();
virtual void _v0c();
virtual void _v10();
virtual void _v14();
virtual void _v18();
virtual void _v1c();
virtual void _v20();
virtual void _v24();
virtual void _v28();
virtual void _v2c();
    /* 30h */ virtual bool GetPropertyList(uint32_t id, PropertyList*& list);
};
}
namespace SP {
cPropertyManager_s00e9_56f0* PropertyManager();                   // 0x0067DE30
}
namespace SP {
struct PropertyListPtr {
    PropertyList* p;
    PropertyListPtr() : p(0) {}
    ~PropertyListPtr() { if (p) p->Release(); }
    void reset() { if (p) { PropertyList* t = p; p = 0; t->Release(); } }
};
}
namespace SP {
class IAudioSystem {
public:
virtual void _v00();
virtual void _v04();
virtual void _v08();
virtual void _v0c();
    /* 10h */ virtual const float* GetListenerPosition(int index);
virtual void _v14();
virtual void _v18();
virtual void _v1c();
    /* 20h */ virtual uint32_t NewSoundHandle();
virtual void _v24();
virtual void _v28();
virtual void _v2c();
virtual void _v30();
    virtual void _v34();
    /* 38h */ virtual void BeginMessage(uint32_t msg);
    virtual void _v3c();
    /* 40h */ virtual void SetParam(uint32_t key, uint32_t value);
virtual void _v44();
virtual void _v48();
virtual void _v4c();
virtual void _v50();
    virtual void _v54();
    /* 58h */ virtual void SendMessage();
};
}
namespace EA {
namespace Audio {
 SP::IAudioSystem* GetSystemAT();   // 0x00A206F0
}
}
namespace EA {
namespace Hash {
uint32_t FNV1_String8(const char* s, uint32_t seed, int lowercase);    // 0x00932E80
}
}
namespace SP {
class cVehicleAnimator { public:
    bool mbZoomedOut;   // +0x00
    char _pad[0x17];
    void Update(float deltaTime, float speed, float maxSpeed, IModelWorld* world, cModel* model);  // 0x00E94A10
    void AttachEffect(IModelWorld* world, cModel* model, uint32_t effectID);                      // 0x00E94AD0
};
}
namespace SP {
class cSpatialObjectView_s00e9_56f0 {
public:
virtual void _v00();
virtual void _v04();
virtual void _v08();
virtual void _v0c();
    /* 10h */ virtual void SetVisible(int visible);
virtual void _v14();
virtual void _v18();
virtual void _v1c();
virtual void _v20();
virtual void _v24();
virtual void _v28();
    /* 2ch */ virtual cModel* GetViewModel();

    char            _pad04[8];
    cSpatialObject_s00e9_56f0* mpObject;        // +0x0c
    char            _pad10[8];
    Vector3         mPosition;       // +0x18
    char            _pad24[0x40 - 0x24];

    void HandleSimulationUpdate(int deltaTimeMS, float deltaTime);   // 0x00E92CA0
};
}
namespace SP {
class cVehicleView_s00e9_56f0 : public cSpatialObjectView_s00e9_56f0 {
public:
    void HandleSimulationUpdate(int deltaTimeMS, float deltaTime);  // 0x00e956f0 (SP::cVehicleView::HandleSimulationUpdate)
    void SpawnCargoEffect(cVehicle_s00e9_56f0* vehicle);                                       // 0x00E94E50
    void UpdateTowedItem(cVehicle_s00e9_56f0* vehicle, IVisualEffect* effect, float deltaTime, bool tethered);  // 0x00E94F30
    void ConnectBalloonString(cVehicle_s00e9_56f0* vehicle, IVisualEffect* balloon);           // 0x00E953A0

    char             _pad40[0x58 - 0x40];
    cSPTimer_s00e9_56f0         mPathTimer;          // +0x58
    cSPTimer_s00e9_56f0         mWobbleTimer;        // +0x78
    uint32_t         mSoundHandle;        // +0x98
    uint32_t         mSoundName;          // +0x9c
    uint32_t         mWobbleOffset;       // +0xa0
    float            mTargetScale;        // +0xa4
    float            mScale;              // +0xa8
    float            mScaleOverride;      // +0xac
    cVehicleAnimator mAnimator;           // +0xb0
    char             mSelectionEffect[4]; // +0xc8
    char             mRolloverEffect[4];  // +0xcc
};
}
namespace SP {
static __forceinline float WobbleAngle(uint64_t t)
{
    return (float)(t % 6283) * 0.001f;
}
}
// ---- items of slice s00e956f0 end

// @ 0x00e948b0
namespace SP {
void __stdcall FUN_00e948b0(cEmitter* self, cEffectTarget* target)
{
    if (self == 0)
        return;
    if (target == 0)
        return;
    int n = self->EmitterCount(target);
    for (int i = 0; i < n; ++i)
        self->EmitterAdd(target, kEffectId3c, 0, 0.0f, i);
}
}  // namespace SP

// @ 0x00e94900
namespace SP {
void __stdcall FUN_00e94900(cEmitter* self, cEffectTarget* target)
{
    if (self == 0)
        return;
    if (target == 0)
        return;
    int n = self->EmitterCount(target);
    for (int i = 0; i < n; ++i)
    {
        self->EmitterAdd(target, kEffectId3c, 1, 0.0f, i);
        self->EmitterAdd2(target, kEffectId3c, 0.0f, i);
    }
}
}  // namespace SP

// @ 0x00e94970
namespace SP {
void cTribeView::Init(void* a, void* b, void* c, void* d)
{
    MakeView_740(a, b, c, d);
    mbZoomOutScale_b0 = 0;
    mTimer_78.Start();
    mMovementSoundID_a0 = sMathRandom.RandomUint32Uniform(0x188b);
}
}  // namespace SP

// @ 0x00e949c0
namespace SP {
void cVehicleView::Init(void* a)
{
    cSpatialObjectView::Init(a);
    mbZoomOutScale_b0 = 0;
    mTimer_78.Start();
    mMovementSoundID_a0 = sMathRandom.RandomUint32Uniform(0x188b);
}
}  // namespace SP

// @ 0x00e94a00
namespace SP {
void cVehicleView::ToggleShowPaths()
{
    gShowVehiclePaths = (gShowVehiclePaths == 0);
}
}  // namespace SP

// @ 0x00e94a10
namespace SP {
void cEffectToggle::Update(int a2, float t, float f2, cEmitter* emitter, cEffectTarget* target)
{
    (void)a2;
    if (target == 0)
        return;
    if (target->mFlags_4.mBit14 == 0)
        return;
    if (target->mFlags_4.mBit18 != 0)
        return;
    if (kZeroPoint1 < t)
    {
        if (mbActive == 0)
        {
            FUN_00e948b0(emitter, target);
            mbActive = 1;
        }
        emitter->EmitterScale(target, (f2 / kEmitterDivisor) * (t / f2));
        return;
    }
    if (mbActive != 0)
    {
        FUN_00e94900(emitter, target);
        mbActive = 0;
        emitter->EmitterScale(target, kExactlyOne);
    }
}
}  // namespace SP

// @ 0x00e94ad0
namespace SP {
void __stdcall FUN_00e94ad0(cEmitter* self, cEffectTarget* target, int i)
{
    if (self == 0)
        return;
    if (target == 0)
        return;
    if (target->mFlags_4.mBit14 == 0)
        return;
    self->EmitterAdd2(target, kEffectId44, 0.0f, i);
    self->EmitterAdd(target, kEffectId44, 0, 0.0f, i);
    self->EmitterAdd2(target, kEffectId40, 0.0f, i);
    self->EmitterAdd(target, kEffectId40, 2, 0.0f, i);
}
}  // namespace SP

// @ 0x00e94b60
cVehicleView_s00e9_4b60::cVehicleView_s00e9_4b60()
{
    ((tHost*)((char*)this + 0x38))->FUN_00b63890();
    ((tHost*)((char*)this + 0x58))->FUN_00b63890();
    ((tHost*)((char*)this + 0x78))->FUN_00b63890();

    mac = 2.5f;
    m98 = 0;
    m9c = 0;
    ma0 = 0;
    ma4 = 1.0f;
    ma8 = 1.0f;
    mb0 = 0;
    mb4 = DAT_016c5ca0;
    mb8 = DAT_016c5ca4;
    mbc = DAT_016c5ca8;
    mc0 = 0.0f;
    mc4 = 5.0f;
    mc8 = 0;
    mcc = 0;
    Vec3_s00e9_4b60 one(1.0f, 1.0f, 1.0f);
    mColor = one;
}

// @ 0x00e94c50
cVehicleView_s00e9_4b60::~cVehicleView_s00e9_4b60()
{
    uint32_t handle = m98;
    if (handle != 0) {
        FUN_00572020(handle, 0);
    }

    if (mc8 != 0) {
        ((void(__thiscall*)(void*, int))VFN(mc8, 0xc))(mc8, 0);
        void* p = mc8;
        if (p != 0) {
            mc8 = 0;
            ((void(__thiscall*)(void*))VFN(p, 4))(p);
        }
    }

    if (mcc != 0) {
        ((void(__thiscall*)(void*, int))VFN(mcc, 0xc))(mcc, 0);
        void* p = mcc;
        if (p != 0) {
            mcc = 0;
            ((void(__thiscall*)(void*))VFN(p, 4))(p);
        }
    }

    if (mcc != 0) {
        ((void(__thiscall*)(void*))VFN(mcc, 4))(mcc);
    }
    if (mc8 != 0) {
        ((void(__thiscall*)(void*))VFN(mc8, 4))(mc8);
    }

    ((tHost*)((char*)this + 0x78))->FUN_00b638b0();
    ((tHost*)((char*)this + 0x58))->FUN_00b638b0();
    ((tHost*)((char*)this + 0x38))->FUN_00b638b0();
}

// @ 0x00e94d10
void* __thiscall cVehicleView_s00e9_4b60::FUN_00e94d10(void* param_1)
{
    cVehicleView_s00e9_4b60* pNew = (cVehicleView_s00e9_4b60*)FUN_00f473a0(0xd0, aSimulatorCVehicleView, 0, 0, 0, 0);
    if (pNew != 0) {
        pNew = new (pNew) cVehicleView_s00e9_4b60();       // cVehicleView::cVehicleView
    }

    if (param_1 != 0) {
        void* iVar4 = ((void*(__thiscall*)(void*, uint32_t))VFN(param_1, 0xc))(param_1, 0x137e8e0);
        if (iVar4 != 0) {
            void* pSub = (void*)((char*)iVar4 + 0x34);
            uint8_t cVar1 = ((uint8_t(__thiscall*)(void*))VFN(pSub, 0x90))(pSub);
            if (cVar1 == 0) {
                ((void(__thiscall*)(void*, void*))VFN(pNew, 0x24))(pNew, iVar4);
            } else {
                float* pf = (float*)((void*(__thiscall*)(void*))VFN(pSub, 0x98))(pSub);
                Vec3_s00e9_4b60 pos;
                pos.x = pf[0];
                pos.y = pf[1];
                pos.z = pf[2];
                void* model = FUN_00b3d520(&pos, (void*)((char*)this + 0x18));
                ((void(__thiscall*)(void*, void*, void*))VFN(pNew, 0x28))(pNew, param_1, model);
                void* r = ((void*(__thiscall*)(void*))VFN(pNew, 0x2c))(pNew);
                if (r != 0) {
                    if (FUN_00b5b800() == DAT_01654c10) {
                        *(uint32_t*)((char*)r + 4) &= 0xfffffffb;
                        pNew->mColor.x = *(float*)&DAT_015a8a48;
                        pNew->mColor.y = *(float*)&DAT_015a8a4c;
                        pNew->mColor.z = *(float*)&DAT_015a8a50;
                    } else {
                        *(uint32_t*)((char*)r + 4) |= 4;
                        Vec3_s00e9_4b60 tmp;
                        void* q = ((tHost*)param_1)->FUN_00c9f650(&tmp);
                        float* pq = (float*)q;
                        pNew->mColor.x = pq[0];
                        pNew->mColor.y = pq[1];
                        pNew->mColor.z = pq[2];
                    }
                    *(float*)((char*)r + 0x4c) = pNew->mColor.x;
                    *(float*)((char*)r + 0x50) = pNew->mColor.y;
                    *(float*)((char*)r + 0x54) = pNew->mColor.z;
                    return pNew;
                }
            }
        }
    }
    return pNew;
}

// @ 0x00e94e50
void __thiscall cVehicleView_s00e9_4b60::FUN_00e94e50(int param_2)
{
    void* pSub = (void*)((char*)param_2 + 0x34);

    mc0 = 0.0f;

    float* pf = (float*)((void*(__thiscall*)(void*))VFN(pSub, 0x2c))(pSub);
    mb4 = pf[0];
    mb8 = pf[1];
    mbc = pf[2];

    float fAngle = ((float(__thiscall*)(void*))VFN(pSub, 0x70))(pSub);
    fAngle = -(fAngle + DAT_014853e0);

    float* pr = (float*)((void*(__thiscall*)(void*, void*))VFN(pSub, 0x5c))(pSub, (void*)0);
    mb4 = pr[0] * fAngle + mb4;
    mb8 = pr[1] * fAngle + mb8;
    mbc = pr[2] * fAngle + mbc;
}

// @ 0x00e94f30
void __thiscall cVehicleView_s00e9_4b60::UpdateTowedItem(void* param_2, void* param_3, int param_4, char param_5)
{
    void* piVar8 = (void*)((char*)param_2 + 0x34);

    if (((uint8_t(__thiscall*)(void*))VFN(piVar8, 0x48))(piVar8) == 0) return;

    float fVar4 = (float)param_4;
    if (param_4 < 0) {
        fVar4 += 4.2949673e9f;
    }
    fVar4 *= 0.002f;

    float* pfVar6 = (float*)((void*(__thiscall*)(void*))VFN(piVar8, 0x2c))(piVar8);
    float fVar18 = pfVar6[0];
    float fVar1 = pfVar6[1];
    float fVar2 = pfVar6[2];

    float fVar15 = 1.0f / sqrtf((fVar2 * fVar2 + (fVar1 * fVar1 + fVar18 * fVar18)) + 1e-08f);
    float fVar11 = fVar15 * fVar18;
    float fVar13 = fVar1 * fVar15;
    fVar15 = fVar2 * fVar15;

    float stack_74 = fVar11;
    float stack_70 = fVar13;
    float stack_6c = fVar15;

    float fVar17;
    float fVar12, fVar14, fVar16;
    if (param_5 == 0) {
        float fVar10 = ((float(__thiscall*)(void*))VFN(piVar8, 0x70))(piVar8);
        fVar17 = -(fVar10 + 4.0f);
        float* pS = (float*)((void*(__thiscall*)(void*, void*))VFN(piVar8, 0x5c))(piVar8, (void*)0);
        fVar12 = pS[0];
        fVar14 = pS[1];
        fVar16 = pS[2];
    } else {
        int iVar7 = ((int(__thiscall*)(void*))VFN(piVar8, 0x68))(piVar8);
        fVar17 = *(float*)(iVar7 + 0x14) + mc4;
        fVar12 = fVar11;
        fVar14 = fVar13;
        fVar16 = fVar15;
    }

    float stack_78 = (fVar16 * fVar17 + fVar2) - mb8;
    float stack_7c = (fVar14 * fVar17 + fVar1) - mb4;
    float stack_80 = (fVar12 * fVar17 + fVar18) - mbc;

    float fOld4 = mb4;
    float fOldY = mb8;
    mb4 = mb4 + stack_80 * fVar4;
    mb8 = stack_7c * fVar4 + fOldY;
    mbc = stack_78 * fVar4 + fOld4;

    float* pfB = (float*)((void*(__thiscall*)(void*, void*))VFN(piVar8, 0x5c))(piVar8, (void*)0);

    float af[4];
    af[0] = fVar13 * pfB[1] - fVar11 * pfB[2];
    af[1] = fVar2 * pfB[2] - fVar13 * pfB[0];
    af[2] = fVar11 * pfB[0] - fVar2 * pfB[1];
    fVar18 = 1.0f / sqrtf(af[1] * af[1] + (af[2] * af[2] + af[0] * af[0]));
    af[0] = fVar18 * af[0];
    af[2] = af[2] * fVar18;
    af[1] = af[1] * fVar18;

    fVar18 = af[2] * fVar11 - af[1] * fVar13;
    float fStack_20 = af[1] * fVar2 - fVar11 * af[0];
    float fStack_24 = fVar13 * af[0] - af[2] * fVar2;
    af[3] = 1.0f / sqrtf(fVar18 * fVar18 + (fStack_24 * fStack_24 + fStack_20 * fStack_20));
    fStack_20 = fStack_20 * af[3];
    fStack_24 = fStack_24 * af[3];
    af[3] = af[3] * fVar18;

    cTransform xf;
    xf.mTranslation.x = DAT_016c62ac;
    xf.mTranslation.y = DAT_016c62b0;
    xf.mTranslation.z = DAT_016c62b4;
    xf.mFlags = 0;
    xf.mModificationCount = 0;
    xf.mScale = 1.0f;
    ((tHost*)&xf.mRotation)->FUN_0041cb40((void*)DAT_016c6288);

    float fPrevZ = mbc;
    for (int i = 0; i < 9; i++) {
        xf.mRotation[i] = af[i];
    }
    xf.mFlags = (uint16_t)(xf.mFlags | 2);
    xf.mModificationCount = (uint16_t)(xf.mModificationCount + 1);

    fVar18 = (sqrtf(stack_80 * stack_80 + (stack_7c * stack_7c + fVar4 * fVar4)) * 0.035f - fPrevZ) * fVar15 + fPrevZ;
    mbc = fVar18;
    ((tHost*)&xf)->FUN_005a2d90(fVar18);

    xf.mTranslation.z = mb8;
    xf.mTranslation.x = mb4;
    xf.mTranslation.y = mb8;
    xf.mFlags = (uint16_t)((uint16_t)(xf.mModificationCount + 1) << 16 | xf.mFlags | 4);

    ((void(__thiscall*)(void*, void*))VFN(param_2, 0x18))(param_2, &xf);
}

// @ 0x00e953a0
void __thiscall cVehicleView_s00e9_4b60::ConnectBalloonString(int param_2, void* param_3)
{
    void* piVar6 = (void*)((char*)param_2 + 0x34);

    if (((uint8_t(__thiscall*)(void*))VFN(piVar6, 0x48))(piVar6) == 0) return;

    float* pfVar3 = (float*)((void*(__thiscall*)(void*))VFN(piVar6, 0x2c))(piVar6);
    float fStack_13c = pfVar3[0];
    float fStack_138 = pfVar3[1];
    float fStack_134 = pfVar3[2];

    int iVar4 = ((int(__thiscall*)(void*))VFN(piVar6, 0x68))(piVar6);
    float fStack_130 = *(float*)(iVar4 + 0x14) * 0.85f;

    void* uVar5 = ((void*(__thiscall*)(void*))VFN(piVar6, 0x30))(piVar6);
    float afM[6];
    FUN_0059c190(afM, uVar5);

    float fStack_128 = afM[1] * fStack_130 + fStack_138;
    float fStack_124 = afM[2] * fStack_130 + fStack_134;
    float fStack_12c = afM[0] * fStack_130 + fStack_13c;

    float fStack_110 = (mb4 - fStack_128) * 0.0625f;
    float fStack_114 = (mbc - fStack_12c) * 0.0625f;
    float fStack_10c = (mb8 - fStack_124) * 0.0625f;

    float fStack_118 = 1.0f / sqrtf((fStack_12c * fStack_12c + (fStack_124 * fStack_124 + fStack_128 * fStack_128)) + 1e-08f);
    float fStack_120 = fStack_118 * fStack_12c;
    float fStack_11c = fStack_128 * fStack_118;
    fStack_118 = fStack_118 * fStack_124;

    float pts[51];
    int n = 0;
    float fStack_130b = 0.0f;
    do {
        float fPrev = fStack_130b;
        fStack_130b = (float)((8.0f - (float)(int)fStack_130b) < 0 ? -((8.0f - (float)(int)fStack_130b)) : (8.0f - (float)(int)fStack_130b)) * 0.125f;
        float fVar7 = 1.0f - fStack_130b * fStack_130b;
        fStack_13c = fStack_12c - fStack_120 * fVar7;
        fStack_138 = fStack_128 - fStack_11c * fVar7;
        fStack_134 = fStack_124 - fStack_118 * fVar7;

        pts[n++] = fStack_13c;
        pts[n++] = fStack_138;
        pts[n++] = fStack_134;

        fStack_12c = fStack_12c + fStack_114;
        fStack_128 = fStack_128 + fStack_110;
        fStack_124 = fStack_124 + fStack_10c;
        fStack_130b = (float)((int)fPrev + 1);
    } while ((int)fStack_130b < 0x11);

    ((void(__thiscall*)(void*, int, void*, int))VFN(param_3, 0x44))(param_3, 0xd, pts, 0x33);

    if (fStack_114 != 0.0f) {
        FUN_00f47380((void*)0);
    }
}

// @ 0x00e956f0
namespace SP {
void cVehicleView_s00e9_56f0::HandleSimulationUpdate(int deltaTimeMS, float deltaTime)
{
    cVehicle_s00e9_56f0* vehicle = mpObject ? (cVehicle_s00e9_56f0*)mpObject->Cast(0x137e8e0) : 0;
    uint32_t gameMode = GetCurrentGameMode();

    if (mpObject->HasModelChanged() && mpObject->GetModel()) {
        Vector3 pos = vehicle->GetSelectionPosition();
        mPosition = pos;
        mpObject->GetModel()->mSelectionPosition = pos;
        if (GetCurrentGameMode() == kScenarioMode) {
            mpObject->GetModel()->mFlags &= ~0x800;
            mpObject->GetModel()->mFlags &= ~4;
        } else {
            if (vehicle->mLocomotive.IsPlayerOwned())
                mpObject->GetModel()->mFlags &= ~0x800;
            else
                mpObject->GetModel()->mFlags |= 0x800;
            mpObject->GetModel()->mFlags |= 4;
        }
        mpObject->SetEffectPosition(0x2b255e5, &mPosition);
    }
    if (vehicle->mbHideZoomOut)
        mAnimator.mbZoomedOut = false;

    cSpatialObjectView_s00e9_56f0::HandleSimulationUpdate(deltaTimeMS, deltaTime);

    mpObject->IsSelected();
    bool rolledOver = mpObject->IsRolledOver();
    bool underAttack = vehicle->mCombatant.IsUnderAttack();
    cModel* model = mpObject->GetModel();
    bool isSpace = gameMode == kGameSpace;

    bool tutorialActive;
    if (CivModeStrategy() && CivModeStrategy()->GetPlayerTerritory() &&
        CivModeStrategy()->GetPlayerTerritory()->mpTutorial &&
        CivModeStrategy()->GetPlayerTerritory()->mpTutorial->IsActive())
        tutorialActive = true;
    else
        tutorialActive = false;

    if (GetCurrentGameMode() != kScenarioMode && model) {
        bool highlight = false;
        if (tutorialActive) {
            if (vehicle->mLocomotive.IsPlayerOwned() &&
                (rolledOver || CivModeStrategy()->GetPlayerTerritory()->mpTutorial->IsHighlighted(vehicle))) {
                model->mHighlight = 2;
                highlight = true;
            }
        } else if ((rolledOver || underAttack) && !(GameTimeManager()->mPauseFlags & 1) && !isSpace) {
            model->mHighlight = 2;
            highlight = true;
        }
        if (highlight)
            model->mFlags |= 8;
        else
            model->mFlags &= ~8;
    }

    if (isSpace) {
        AttachSelectionEffect(mpObject, mSelectionEffect, 0);
        AttachRolloverEffect(mpObject, mRolloverEffect, 0);
    }

    if (gShowDebugVehicleEffect && !mpObject->GetEffect(0x2b255e5)) {
        mpObject->CreateEffect(0x8568321f, 0, 0x2b255e5);
        mpObject->SetEffectPosition(0x2b255e5, &mPosition);
    } else if (!gShowDebugVehicleEffect && mpObject->GetEffect(0x2b255e5)) {
        mpObject->StopEffect(0x2b255e5, 1);
    }

    if (mpObject->SetEffectActive(0xdb4e05f3, 0x5f8d751, vehicle->IsHovering(), 0))
        mpObject->SetEffectScale(0x5f8d751, vehicle->mLocomotive.GetBoundingRadius() * 0.083333336f);

    // zoom-out scale override
    float angleA = 0.0f, angleB = 0.0f, zoom = 0.0f;
    if (GetInputHost())
        GetInputHost()->GetAnglesB(&angleA, &angleB, &zoom);
    if (zoom > gScaleOverrideThreshold) {
        PropertyListPtr propList;
        cPropertyManager_s00e9_56f0* propManager = PropertyManager();
        propList.reset();
        Property* prop;
        if (propManager->GetPropertyList(0xb6a5c63d, propList.p) && propList.p &&
            propList.p->GetProperty(0x1c3818d, prop) && prop->mnType == 0xd)
            mScaleOverride = *prop->GetFloat();
        mTargetScale = mScaleOverride;
    } else {
        mTargetScale = 1.0f;
    }

    if (mScale != mTargetScale) {
        float t = (float)(unsigned int)deltaTimeMS * 0.008f;
        if (t < 0.0f) t = 0.0f;
        if (t > 1.0f) t = 1.0f;
        if (t == 1.0f)
            mScale = mTargetScale;
        else
            mScale = (mTargetScale - mScale) * t + mScale;
    }
    if (model) {
        model->mTransform.mModificationCount++;
        model->mTransform.mScale = mScale;
    }

    // model transform from the vehicle, plus wobble
    cSPTransform_s00e9_56f0 transform;
    transform.mFlags = 0;
    transform.mModificationCount = 0;
    transform.mRotation.Assign(kIdentityMatrix3);
    transform.mOffset = vehicle->mLocomotive.GetPosition();
    transform.mFlags |= 4;
    transform.mModificationCount++;
    transform.mScale = vehicle->mLocomotive.GetScale();
    transform.mModificationCount++;
    Matrix3 rotation;
    transform.mRotation = *Matrix3FromQuaternion(&rotation, vehicle->mLocomotive.GetOrientation());
    transform.mFlags |= 2;
    transform.mModificationCount++;

    int locomotion = vehicle->mLocomotion;
    bool bobbing = (vehicle->mFlags & 0x1000) == 0x1000;
    if (locomotion == kVehicleWater && !PlanetModel()->mbIsRetro && bobbing) {
        float roll, amplitude;
        if (GetCurrentGameMode() == kScenarioMode) {
            roll = gWobbleAmplitude * 0.002f;
            amplitude = 0.002f;
        } else {
            roll = gWobbleAmplitude * 0.012f;
            amplitude = 0.15f;
        }
        uint64_t t = mWobbleTimer.GetElapsedTime() + mWobbleOffset;
        uint64_t half = t / 2;
        float angle = WobbleAngle(half + half / 4);
        float s = (float)sin(angle);
        transform.Rotate((float)(cos(angle) * roll));
        roll = s * roll;
        transform.RotateY(roll * 0.5f);
        transform.PreRotateX(roll);
        Vector3 v = { kWobbleAxisSin.x * s * amplitude, kWobbleAxisSin.y * s * amplitude,
                      kWobbleAxisSin.z * s * amplitude };
        transform.PreTranslate(v);
    } else if (vehicle->mbUFOCarried) {
        uint64_t t = mWobbleTimer.GetElapsedTime() + mWobbleOffset;
        float angle = WobbleAngle(t * 16);
        float s = (float)sin(angle);
        transform.Rotate((float)(cos(angle) * 0.025f));
        transform.PreRotateX(s * 0.0125f);
        Vector3 v = { kWobbleAxisSin.x * s * 0.05f, kWobbleAxisSin.y * s * 0.05f,
                      kWobbleAxisSin.z * s * 0.05f };
        transform.PreTranslate(v);
    } else if (locomotion == kVehicleAir) {
        uint64_t t = mWobbleTimer.GetElapsedTime() + mWobbleOffset;
        uint64_t half = t / 2;
        float angle = WobbleAngle(half + half / 4);
        float s = (float)sin(angle);
        float c = (float)cos(angle);
        float k = GetCurrentGameMode() == kScenarioMode ? 0.02f : 1.0f;
        Vector3 v1 = { kWobbleAxisSin.x * s * k, kWobbleAxisSin.y * s * k, kWobbleAxisSin.z * s * k };
        transform.PreTranslate(v1);
        Vector3 v2 = { kWobbleAxisCos.x * c * k, kWobbleAxisCos.y * c * k, kWobbleAxisCos.z * c * k };
        transform.PreTranslate(v2);
    }
    if (model)
        model->mTransform = transform;

    if (vehicle->mbDead) {
        SetVisible(0);
        mpObject->DestroyAllEffects(0);
        return;
    }

    // queued view events
    int event;
    while ((event = vehicle->PopViewEvent()) != 0) {
        switch (event) {
        case 1:
        case 7:
            mpObject->CreateEffect(0x24b83dde, 0, 0x1a2c90a);
            break;
        case 3:
            mpObject->CreateEffect(0x525a3ae7, 0, 0x1a2c90a);
            break;
        case 5:
            mpObject->CreateEffect(0x2b09618, 0, 0x1a2c90a);
            break;
        case 2:
        case 4:
        case 6:
        case 8:
            mpObject->StopEffect(0x1a2c90a, 1);
            break;
        case 9:
            mpObject->CreateEffect(0x2f81eb6c, 0, 0x2cb4945);
            break;
        case 10:
            mpObject->CreateAttachedEffect(0x754300d, 0, 0x2ce1024);
            mpObject->SetEffectRange(0x2ce1024, 3.402823466e+38f);
            mpObject->SetEffectPosition(0x2ce1024, &mPosition);
            break;
        case 12:
            mpObject->CreateEffect(0xd68766, 0, 0x4a34ef1);
            mpObject->CreateEffect(0x4ceb8dd6, 0, 0x4dbff4f);
            mpObject->SetEffectPosition(0x4dbff4f, &mPosition);
            if (!mpObject->GetEffect(0x4ffb17f)) {
                mpObject->CreateEffect(0xda481c1f, 0, 0x4ffb17f);
                SpawnCargoEffect(vehicle);
            } else {
                mpObject->StartEffect(0x4ffb17f, 1);
                SpawnCargoEffect(vehicle);
            }
            break;
        case 14:
            mpObject->StopEffect(0x4ffb17f, 1);
            // fall through
        case 13:
            mpObject->StopEffect(0x4a34ef1, 1);
            mpObject->StopEffect(0x4dbff4f, 1);
            break;
        case 15:
            if (!mpObject->GetEffect(0x4288910)) {
                mpObject->CreateEffect(0x540964f0, 0, 0x4288910);
                mpObject->SetEffectPosition(0x4288910, &mPosition);
            }
            break;
        case 16:
            mpObject->StopEffect(0x4288910, 1);
            if (!mpObject->GetEffect(0x4dbff4e)) {
                mpObject->CreateEffect(0x2c6ea0c4, 0, 0x4dbff4e);
                mpObject->SetEffectPosition(0x4dbff4e, &mPosition);
            } else {
                mpObject->StartEffect(0x4dbff4e, 1);
            }
            break;
        case 17:
            mpObject->StopEffect(0x4dbff4e, 1);
            mpObject->StopEffect(0x4ffb17f, 1);
            break;
        case 18:
            if (!mpObject->GetEffect(0x428890e))
                mpObject->CreateEffect(0x8caee048, 0, 0x428890e);
            break;
        case 19:
            mpObject->StopEffect(0x428890e, 1);
            break;
        case 20:
            mpObject->CreateAttachedEffect(0x2abf6155, 0, 0x428890f);
            mpObject->SetEffectPosition(0x428890f, &mPosition);
            mpObject->SetEffectRange(0x428890f, 1024.0f);
            break;
        case 21:
            mpObject->CreateAttachedEffect(0x2241f9c6, 0, 0x4ebf115);
            mpObject->SetEffectPosition(0x4ebf115, &mPosition);
            mpObject->SetEffectRange(0x4ebf115, 1024.0f);
            break;
        case 22:
            mpObject->StopEffect(0x428890f, 1);
            mpObject->CreateAttachedEffect(0x4f014cd5, 0, 0x4288914);
            mpObject->SetEffectPosition(0x4288914, &mPosition);
            mpObject->SetEffectRange(0x4288914, 1024.0f);
            break;
        case 23:
            mpObject->StopEffect(0x4ebf115, 1);
            mpObject->CreateAttachedEffect(0x4683e546, 0, 0x4ebeeac);
            mpObject->SetEffectPosition(0x4ebeeac, &mPosition);
            mpObject->SetEffectRange(0x4ebeeac, 1024.0f);
            break;
        case 24: {
            mpObject->CreateEffect(0xc6adcb63, 0, 0x41a447a);
            tGameDataList* vehicles = NounManager()->GetVehicleList();
            int count = (int)(vehicles->mpEnd - vehicles->mpBegin);
            for (int i = 0; i < count; i++) {
                cGameData_s00e9_56f0* other = vehicles->mpBegin[i];
                cGameData_s00e9_56f0::tOwnerInfo* info = other->GetOwnerInfo();
                if (info->mKind == 1 && info->mpOwner == vehicle) {
                    char* city = NounManager()->GetCityByPoliticalID(other->GetPoliticalID());
                    if (city)
                        mpObject->SetEffectPosition(0x41a447a, (const Vector3*)(city + 0xc4));
                }
            }
            break;
        }
        case 25:
            mpObject->StopEffect(0x41a447a, 1);
            break;
        case 26:
            if (!mpObject->GetEffect(0x4b72043)) {
                uint32_t effectID = 0x70352681;
                if (locomotion == kVehicleWater)
                    effectID = 0xd1f896dd;
                else if (locomotion == kVehicleAir)
                    effectID = 0xda1b35e4;
                mpObject->CreateEffect(effectID, 0, 0x4b72043);
            }
            break;
        case 27:
            mpObject->StopEffect(0x4b72043, 0);
            break;
        case 28:
            mpObject->StopEffect(0x4b72043, 1);
            break;
        }
    }

    // damage effect
    if (vehicle->mFlags & 0x800) {
        if (!mpObject->GetEffect(0x30e8895)) {
            mpObject->CreateEffect(vehicle->mLocomotion != kVehicleAir ? 0x56191017 : 0x36150560, 0, 0x30e8895);
            mpObject->SetEffectScale(0x30e8895, vehicle->mLocomotive.GetFootprintRadius());
            mpObject->SetEffectRange(0x30e8895, 512.0f);
        }
        vehicle->mFlags &= ~0x800;
    } else if (mpObject->GetEffect(0x30e8895)) {
        mpObject->StopEffect(0x30e8895, 1);
    }

    // towed item / balloon
    IVisualEffect* balloon = mpObject->GetEffectObject(0x4ffb17f);
    if (balloon) {
        if (mpObject->GetEffect(0x4dbff4f))
            UpdateTowedItem(vehicle, mpObject->GetEffectObject(0x4dbff4f), deltaTime, false);
        else if (mpObject->GetEffect(0x4288910))
            UpdateTowedItem(vehicle, mpObject->GetEffectObject(0x4288910), deltaTime, true);
        else if (mpObject->GetEffect(0x4dbff4e))
            UpdateTowedItem(vehicle, mpObject->GetEffectObject(0x4dbff4e), deltaTime, false);
        ConnectBalloonString(vehicle, balloon);
    }

    // cargo effect
    if (vehicle->mCargoFlags & 8) {
        if (!mpObject->GetEffect(0x3572487))
            mpObject->CreateEffect(0xe489024c, 0, 0x3572487);
    } else {
        mpObject->StopEffect(0x3572487, 1);
    }

    // animator
    const Vector3& velocity = vehicle->mLocomotive.GetVelocity();
    float speed = (float)sqrt(velocity.x * velocity.x + velocity.y * velocity.y + velocity.z * velocity.z);
    float animSpeed = speed;
    float maxSpeed = vehicle->mLocomotive.GetStandardSpeed();
    if (vehicle->ScaleAnimationSpeed()) {
        float minFraction;
        switch (vehicle->mLocomotion) {
        case kVehicleWater: minFraction = 0.1f; break;
        case kVehicleAir:   minFraction = 0.4f; break;
        default:            minFraction = 0.3f; break;
        }
        float clamped = speed;
        if (clamped < 0.0f) clamped = 0.0f;
        if (clamped > maxSpeed) clamped = maxSpeed;
        animSpeed = (maxSpeed - minFraction * maxSpeed) * (clamped / maxSpeed) + minFraction * maxSpeed;
    }
    mAnimator.Update(deltaTime, animSpeed, maxSpeed, GonzagoModelWorld(), GetViewModel());

    // effects attached to the vehicle's attached objects
    tAttachedEffects* attached = vehicle->GetAttachedEffects();
    int attachedCount = (int)(attached->mpEnd - attached->mpBegin);
    for (int i = 0; i < attachedCount; i++) {
        tAttachedEffect& entry = attached->mpBegin[i];
        if (entry.mpObject->IsEffectAttached()) {
            if (!entry.mbActive) {
                uint32_t effectID = entry.mEffectID;
                entry.mbActive = true;
                mAnimator.AttachEffect(GonzagoModelWorld(), GetViewModel(), effectID);
            }
        } else if (entry.mbActive) {
            entry.mbActive = false;
            uint32_t effectID = entry.mEffectID;
            cModel* viewModel = GetViewModel();
            IModelWorld* world = GonzagoModelWorld();
            if (world && viewModel && ((viewModel->mFlags >> 14) & 1))
                world->StopEffectGroup(viewModel, gModelWorldEffectGroup, 1, 0.0f, effectID);
        }
    }

    // 3D movement sound
    uint32_t soundName = vehicle->GetMovementSound();
    Vector3 position = vehicle->mLocomotive.GetPosition();
    bool inRange = false;
    if (EA::Audio::GetSystemAT()) {
        const float* listener = EA::Audio::GetSystemAT()->GetListenerPosition(1);
        float dx = listener[0] - position.x;
        float dy = listener[1] - position.y;
        float dz = listener[2] - position.z;
        float distance = (float)sqrt(dx * dx + dy * dy + dz * dz);
        if (distance < 250.0f)
            inRange = true;
    }
    if (!inRange || soundName != mSoundName) {
        uint32_t handle = mSoundHandle;
        if (handle) {
            IAudioSystem* audio = EA::Audio::GetSystemAT();
            if (audio) {
                audio->BeginMessage(0x347536b);
                audio->SetParam(0x3475385, handle);
                audio->SetParam(0x34753a0, 0);
                audio->SendMessage();
            }
            mSoundHandle = 0;
            mSoundName = 0;
        }
    }
    if (inRange && !mSoundHandle && soundName) {
        IAudioSystem* audio = EA::Audio::GetSystemAT();
        uint32_t handle = audio ? audio->NewSoundHandle() : 0;
        mSoundHandle = handle;
        mSoundName = soundName;
        Start3dSoundByName(soundName, handle, position.x, position.y, position.z);
        EditorUtils::PlayEditorSound(mSoundHandle, 0x71bc3009, 1.0f / vehicle->GetSoundPitch(), 1);
    }
    if (mSoundHandle) {
        float speedStat = vehicle->mSpeedStat > 0.33f ? vehicle->mSpeedStat : 0.33f;
        float volume = speed / vehicle->mLocomotive.GetStandardSpeed() * speedStat;
        if (volume < 0.0f) volume = 0.0f;
        if (volume > 1.0f) volume = 1.0f;
        SetSoundPosition(mSoundHandle, position.x, position.y, position.z);
        EditorUtils::PlayEditorSound(mSoundHandle, gVehicleSpeedSoundParam, volume, 0);
        EditorUtils::PlayEditorSound(mSoundHandle, 0x70e47545, vehicle->GetSoundParam(), 0);
    }

    // path effect (ground dust / boat wake / air contrails)
    if (speed > 0.1f) {
        if (!mpObject->GetEffect(0x2b216c7)) {
            mPathTimer.Stop();
            float speedStat = vehicle->mSpeedStat;
            const char* name = 0;
            switch (locomotion) {
            case kVehicleLand:
                if (speedStat < 0.33f)      name = "civ_vehicle_ground_moving_slow";
                else if (speedStat < 0.66f) name = "civ_vehicle_ground_moving_medium";
                else                        name = "civ_vehicle_ground_moving_fast";
                break;
            case kVehicleWater:
                if (speedStat < 0.33f)      name = "civ_vehicle_boat_wake_slow";
                else if (speedStat < 0.66f) name = "civ_vehicle_boat_wake_medium";
                else                        name = "civ_vehicle_boat_wake_fast";
                break;
            case kVehicleAir:
                if (speedStat < 0.33f)      name = "civ_vehicle_air_contrails_slow";
                else if (speedStat < 0.66f) name = "civ_vehicle_air_contrails_medium";
                else                        name = "civ_vehicle_air_contrails_fast";
                break;
            }
            mpObject->CreateEffect(EA::Hash::FNV1_String8(name, 0x811c9dc5, 1), 0, 0x2b216c7);
            mpObject->SetEffectRange(0x2b216c7, 3.402823466e+38f);
            mpObject->SetEffectPosition(0x2b216c7, &mPosition);
        } else if (mPathTimer.IsRunning()) {
            mPathTimer.Stop();
            IVisualEffect* effect = mpObject->GetEffectObject(0x2b216c7);
            float intensity = 1.0f;
            effect->SetParams(4, &intensity, 1);
        }
    } else {
        if (mpObject->GetEffect(0x2b216c7)) {
            if (!mPathTimer.IsRunning())
                mPathTimer.Restart();
            if (mPathTimer.GetElapsedTime() > 1000) {
                mpObject->StopEffect(0x2b216c7, 1);
            } else {
                IVisualEffect* effect = mpObject->GetEffectObject(0x2b216c7);
                if (effect) {
                    float intensity = (float)(1000 - mPathTimer.GetElapsedTime()) * 0.001f;
                    effect->SetParams(4, &intensity, 1);
                }
            }
        }
        if (mpObject->GetEffect(0x2def079))
            mpObject->StopEffect(0x2def079, 1);
    }

    // damage smoke by health
    cCombatant_s00e9_56f0* combatant = &vehicle->mCombatant;
    float health = combatant->GetHealthPercentage();
    // 0: healthy, 1: damaged (light smoke), 2: critical (heavy smoke)
    int damageLevel = health >= 0.66f ? 0 : health >= 0.33f ? 1 : health >= 0.0f ? 2 : -1;
    if (damageLevel >= 0) {
        if (damageLevel != 1 && mpObject->GetEffect(0x49b925c))
            mpObject->StopEffect(0x49b925c, 0);
        if (damageLevel != 2) {
            if (mpObject->GetEffect(0x49b925d))
                mpObject->StopEffect(0x49b925d, 0);
            if (damageLevel == 1 && !mpObject->GetEffect(0x49b925c))
                mpObject->CreateEffect(0xfb03011e, 0, 0x49b925c);
        }
        if (damageLevel == 2 && !mpObject->GetEffect(0x49b925d))
            mpObject->CreateEffect(0xb44e37a2, 0, 0x49b925d);
    }

    mpObject->SetEffectActive(0x55ca6d6, 0x591d09c, combatant->IsStunned(), 0);
    uint32_t clingEffect = EA::Hash::FNV1_String8("SG_ufo_static_cling_stunned_vehicle", 0x811c9dc5, 1);
    mpObject->SetEffectActive(clingEffect, 0x5f8d750, combatant->IsStaticClingStunned(), 0);

    // civ tutorial: highlight the player's first vehicle
    if (gameMode == kGameCiv) {
        cCivModeStrategy* civ = CivModeStrategy();
        bool highlight = civ && civ->HasCivTutorialOccurred(0x64e6678) &&
                         !civ->HasCivTutorialOccurred(0x64e6679) && vehicle == civ->GetFirstVehicle(0);
        mpObject->SetEffectActive(0xc66a87f2, 0x6553e09, highlight, 0);
    }
}
}  // namespace SP
