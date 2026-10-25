// src/game/SPGonzago/SPCreatureCamera.cpp -- migrated from slice(s) s00d27a70, s00d26790, s00d247f0, s00d22f30, s00d213b0, s00d20620 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCreatureCamera.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cGameNounManager.h"
#include "SP/cLocalInputState.h"
#include "SP/cPlanetModel.h"
#include "SP/cViewer.h"
#include <math.h>
#include "EA/Variant.h"
#include "SP/cPropertyList.h"
#include "SP/cPropertyManager.h"

// ---- items of slice s00d20620 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct tVec3 { float x, y, z; };
struct tVec4 { float x, y, z, w; };
typedef long double float10;
struct tCamCtrl {
    char  pad_00[0x1c];
    float m1c;                 // +0x1c
    float m20;                 // +0x20
    float m24;                 // +0x24
    char  pad_28[0x48 - 0x28];
    float m48;                 // +0x48
    float m4c;                 // +0x4c
    float m50;                 // +0x50
    float m54;                 // +0x54
    float m58;                 // +0x58
    float m5c;                 // +0x5c
    char  pad_60[0x94 - 0x60];
    float m94;                 // +0x94
    float m98;                 // +0x98
    float m9c;                 // +0x9c
    float ma0;                 // +0xa0
    float ma4;                 // +0xa4
    float ma8;                 // +0xa8
    char  pad_ac[0x100 - 0xac];
    float m100;                // +0x100
    char  pad_104[0x108 - 0x104];
    float m108;                // +0x108
    float m10c;                // +0x10c
    float m110;                // +0x110
    float m114;                // +0x114
    float m118;                // +0x118
    float m11c;                // +0x11c
    char  pad_120[0x12c - 0x120];
    float m12c;                // +0x12c
    float m130;                // +0x130
    float m134;                // +0x134
    float m138;                // +0x138
    float m13c;                // +0x13c
    float m140;                // +0x140
    float m144;                // +0x144
    char  pad_148[0x17c - 0x148];
    float m17c;                // +0x17c
    char  pad_180[0x188 - 0x180];
    float m188;                // +0x188
    char  pad_18c[0x194 - 0x18c];
    float m194;                // +0x194
    char  pad_198[0x1ac - 0x198];
    tVec3 m1ac;                // +0x1ac
    tVec4 m1b8;                // +0x1b8
    tVec3 m1c8;                // +0x1c8
    tVec4 m1d4;                // +0x1d4
    char  pad_1e4[0x1e8 - 0x1e4];
    unsigned m1e8;             // +0x1e8
    char  pad_1ec[0x210 - 0x1ec];
    float m210;                // +0x210
    float m214;                // +0x214
    char  pad_218[0x258 - 0x218];
    float m258;                // +0x258
    float m25c;                // +0x25c
    char  pad_260[0x298 - 0x260];
    unsigned char m298;        // +0x298

    float10 FUN_00d20620(float p);                       // 0x00d20620
    void   FUN_00d20880(const tVec3& a, const tVec4& b); // 0x00d20880
    void   FUN_00d20910(float f);                       // 0x00d20910
    void   FUN_00d20950(unsigned n);                    // 0x00d20950
};
void* __cdecl GetCurrentGameMode(void);          // 0x00b5b800  SP::GetCurrentGameMode
void* __cdecl CreatureModeStrategy_Instance(void); // 0x00d38840  SP::cCreatureModeStrategy::Instance
struct cModeTarget {
    char          pad_00[0x54];
    unsigned char m54;    // +0x54
};
struct cCreatureModeStrategy {
    char         pad_00[0x64];
    cModeTarget* m64;     // +0x64
};
struct cGlobalMgr {
    char         pad_00[0x68];
    cModeTarget* m68;     // +0x68
};
// ---- items of slice s00d20620 end

// ---- items of slice s00d213b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char  gModeCreatureB;  // 0x01654c01  creature-mode sentinel
extern const char  gModeCreatureA;  // 0x01654c10
extern unsigned char gUsePitchArg;  // 0x0169de80  GetPitch mode flag
extern unsigned char gUsePitchRefine;  // 0x0169de81
struct Vec2 { float x, y; };
struct Vec3 { float x, y, z; };
struct Quat { float x, y, z, w; };
struct Vec4 { float x, y, z, w; };
struct Matrix44 {
    Vec4 xAxis, yAxis, zAxis, wAxis;
    void FUN_007c3da0(float* dst);                          // 0x007c3da0 (3x3 copy)
};
extern const Vec2  kInputConst;   // 0x0169dea8
extern const Vec3  kZeroVec;      // 0x0169deb0  (0,0,0)
struct cGameNounManager;
struct cPlanetModel;
struct cApp;
cGameNounManager* NounManager();                       // 0x00b3d300
cPlanetModel* PlanetModel();                           // 0x00b3d350
cApp*  App();                                          // 0x0067dd10
void*  GameInputManager();                             // 0x00b3d250
void* FUN_0067cab0();                                 // 0x0067cab0
float* normalized_safe(float* out, const float* v);    // 0x00449c20
float* FUN_0046d660(float* out, const float* m);       // 0x0046d660
Vec3*  FUN_0059aed0(Vec3* out, const Vec3* v, const Quat* q);  // 0x0059aed0
float  Acos(float x);                                  // 0x011e08c8
struct cCameraMathView {
    float RefinePitch(float v);                        // 0x00d20620  ret 4
    float AdjustPitchAndDistance(float a, float b);    // 0x00d20700  ret 8
};
struct cMsgObj {
    virtual void  pv0();
    virtual void  pv1();
    virtual void  pv2();
    virtual void  pv3();
    virtual void* vf10();                              // +0x10
    virtual void  pv5();
    virtual void  pv6();
    virtual void** vf1c(int which);                     // +0x1c
};
struct cApp {
virtual void pv00();
virtual void pv01();
virtual void pv02();
virtual void pv03();
virtual void pv04();
virtual void pv05();
virtual void pv06();
virtual void pv07();
virtual void pv08();
virtual void pv09();
virtual void pv0a();
virtual void pv0b();
virtual void pv0c();
virtual void pv0d();
virtual void pv0e();
virtual void pv0f();
virtual void pv10();
virtual void pv11();
virtual void pv12();
virtual void pv13();
virtual void pv14();
virtual void pv15();
    virtual void* vf58();                              // +0x58 -> cViewer
};
struct cGameInputManager {
virtual void pv0();
virtual void pv1();
virtual void pv2();
virtual void pv3();
virtual void pv4();
virtual void pv5();
    virtual bool vf18(int id);                         // +0x18
};
struct cUiObject {
    void Set40(bool on);                               // 0x008013d0
    void Set(bool on);                                 // 0x00801980
};
struct cCreatureModeInputStrategy {
    char pad54[0x54];
    unsigned char mb54;                                // +0x54
    char pad55[3];
    bool DidDoubleClick(int id);                       // 0x00d30ee0
};
struct cCreatureModeStrategy_s00d2_13b0 {
    char pad64[0x64];
    cCreatureModeInputStrategy* mpInputStrategy;       // +0x64
    static cCreatureModeStrategy_s00d2_13b0* Instance();          // 0x00d38840
};
struct cLocoAnimState {
    char pad14[0x14];
    float mf14;                                        // +0x14
};
struct cLoco {
virtual void pv00();
virtual void pv01();
virtual void pv02();
virtual void pv03();
virtual void pv04();
virtual void pv05();
virtual void pv06();
virtual void pv07();
virtual void pv08();
virtual void pv09();
virtual void pv0a();
    virtual Vec3* vf2c();                              // +0x2c  position
virtual void pv0c();
virtual void pv0d();
virtual void pv0e();
virtual void pv0f();
virtual void pv10();
virtual void pv11();
virtual void pv12();
virtual void pv13();
virtual void pv14();
virtual void pv15();
virtual void pv16();
    virtual Vec3* vf5c(Vec3* out);                     // +0x5c  anchor position
virtual void pv18();
virtual void pv19();
    virtual cLocoAnimState* vf68();                    // +0x68
};
struct cAvatar {
    char padC0[0xc0];
    cLoco mLoco;                                       // +0xc0
};
struct cPlanetModel {
    Vec3* DirectionToSurfacePosition(Vec3* out, const Vec3* in);  // 0x00b815a0
    Vec3* FUN_00b81630(Vec3* out, const Vec3* in);                // 0x00b81630
};
struct cGameNounManager {
    cAvatar* GetAvatar();                              // 0x00b1fdb0
};
struct cViewer {
    Matrix44 mCameraToWorldTransform;   // +0x00
    void GetCameraLocationInfo(Vec3* pos, Vec3* dir, Vec3* up, Vec3* right);  // 0x007c3d30
};
struct cLocalInputState {
    char data[0x48];
    void OnMouseDown(unsigned int id, float x, float y, unsigned int flags);  // 0x00697ab0
};
struct ICamBase { void* mVptr; };
struct IGB1 { void* mVptr; };
struct RefCountV { void* mVptr; int mRefCount; };
struct RbTreeAnchor {
    RbTreeAnchor* mpRight;
    RbTreeAnchor* mpLeft;
    RbTreeAnchor* mpParent;
    unsigned int mColor;
    unsigned int mnSize;
};
class cCreatureCameraIGB1 : public IGB1 {
public:
    char mPad004[0x128 - 0x004];
    float mF12C;                                             // camera +0x12c
    float mF130;                                             // camera +0x130
    char mPad130[0x1e4 - 0x130];
    unsigned int mI1E8;                                      // camera +0x1e8
    unsigned int mI1EC;                                      // camera +0x1ec
    unsigned int mI1F0;                                      // camera +0x1f0
    bool mb1F4;                                              // camera +0x1f4
    char mPad1F1[0x295 - 0x1f1];
    bool mbCameraReverse;                                    // camera +0x299
    char mPad296[0x310 - 0x296];
    bool mb314;                                              // camera +0x314
    bool mb315;                                              // camera +0x315
    bool HandleMessage(unsigned int id, void* msg);          // 0x00d213b0
};
class cCreatureCamera : public ICamBase, public IGB1, public RefCountV {
public:
    bool OnMouseDown(unsigned int id, float x, float y, unsigned int flags);  // 0x00d217e0
    float GetPitch(float a, float b);                        // 0x00d21810
    Vec3* GetAudioAnchorPosition(Vec3* out);                 // 0x00d21c50
    void UpdateCamera_Free();                                // 0x00d21d90
    void SetCameraUI(bool on);                               // 0x00d20430
    void FUN_00d21b10(float x, float y, float z);            // 0x00d21b10
    void FUN_00d21bc0(float x, float y, float z);            // 0x00d21bc0

    bool mbEnableInput;                       // +0x10
    bool mbSkipInit;                          // +0x11
    Vec2 mInputConst;                         // +0x14
    float mDt, mOscillationTime, mBreathOffset;            // +0x1c
    Vec3 mShakeOffset;                                     // +0x28
    float mRoll;                                           // +0x34
    Vec3 mReferenceHeading;                                // +0x38
    float mWantInterpolationTimer;                         // +0x44
    Vec3 mV48;                                             // +0x48
    Vec3 mV54;                                             // +0x54
    Quat mQ60;                                             // +0x60
    Vec3 mV70, mV7c, mV88, mV94, mVa0, mVac, mVb8, mVc4;   // +0x70 ..
    Vec3 mBoundsMin;                                       // +0xd0
    Vec3 mBoundsMax;                                       // +0xdc
    bool mbE8, mbE9;                                       // +0xe8
    float mFieldEC, mFieldF0, mFieldF4, mFieldF8, mFieldFC; // +0xec
    float mField100;                                       // +0x100
    bool mb104, mb105;                                     // +0x104
    Vec3 mV108, mV114, mV120;                              // +0x108
    float mF12C, mF130, mF134, mF138;                       // +0x12c
    Vec3 mV13C, mV148;                                     // +0x13c
    Quat mQ154;                                            // +0x154
    bool mb164;                                            // +0x164
    Vec3 mV168;                                            // +0x168
    float mF174, mF178, mF17C;                             // +0x174
    float mF180, mF184, mF188, mF18C, mF190, mF194, mF198; // +0x180
    bool mb19C, mb19D;                                     // +0x19c
    float mF1A0, mF1A4, mF1A8;                             // +0x1a0
    Vec3 mV1AC;                                            // +0x1ac
    Quat mQ1B8;                                            // +0x1b8
    Vec3 mAudioAnchor;                                     // +0x1c8
    Quat mQ1D4;                                            // +0x1d4
    float mF1E4;                                           // +0x1e4
    unsigned int mI1E8, mI1EC, mI1F0;                      // +0x1e8
    bool mb1F4;                                            // +0x1f4
    float mMouseSensitivityX, mMouseSensitivityY;          // +0x1f8
    float mMouseSensitivityZ;                              // +0x200
    float mMaxAnchorDistance;                              // +0x204
    Vec2 mPitchLimits;                                     // +0x208
    float mMinCameraPhi;                                   // +0x210
    float mMaxCameraPhi;                                   // +0x214
    float mMinCameraDistance, mMaxCameraDistance;          // +0x218
    float mInitialDistance, mInitialRotation;              // +0x220
    float mNearClip, mFarClip, mInterpolateAnchorTime;     // +0x228
    float mInterpolateOrientationTime;                     // +0x234
    float mInterpolateThetaTime;                           // +0x238
    bool mbAutoPitchActive;                                // +0x23c
    float mInterpolatePitchTime;                           // +0x240
    float mInterpolateDistanceTime;                        // +0x244
    float mAutoPitch248, mAutoPitch24C, mAutoPitch250, mAutoPitch254;  // +0x248
    float mInterpolateAnchorMultiplier;                    // +0x258
    float mField25C;                                       // +0x25c
    char mCameraToWorld[0x38];                             // +0x260
    bool mTransformNeedsUpdating;                          // +0x298
    bool mCameraReverse;                                   // +0x299
    unsigned int mMsgReg[5];                               // +0x29c
    bool mbCanToggleFirstPersonView;                       // +0x2b0
    bool mbLockOutPlayerDeltas, mbAllowRealignment, mbRealignAvatar, mbB4;  // +0x2b1
    float mLftMouseDownDuration;                           // +0x2b8
    cLocalInputState mLocalInputState;                     // +0x2bc
    bool mbActive;                                         // +0x304
    void* mConfig;                                         // +0x308
    char pad30c[0x314 - 0x30c];
    bool mb314, mb315;                                     // +0x314
    unsigned int pad318;
    RbTreeAnchor mTree;                                    // +0x31c
};
static inline float AbsValue(float v)
{
    if (v >= 0.0f)
        return v;
    return -v;
}
// ---- items of slice s00d213b0 end

// ---- items of slice s00d22f30 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
typedef unsigned short u16;
typedef short          i16;
typedef float          f32;
typedef double         f64;
struct SP_Vector3 { f32 x, y, z; };
struct SP_Vector4 { f32 x, y, z, w; };
extern f32 DAT_0169df44;      // 0x0169df44  forward basis x
extern f32 _HK_REAL_ZERO;     // 0x01485378  Havok 0.0f
class cCreatureCamera_s00d2_2f30 {
public:
    void FUN_00d22f30();                                  // 0x00d22f30
    void FUN_00d23320();                                  // 0x00d23320
    void FUN_00d23840();                                  // 0x00d23840
    f32  FUN_00d20880(f32* p, void* v);                   // 0x00d20880
    void FUN_00d21bc0(f32 a, f32 b, f32 c);               // 0x00d21bc0

    u8  mPad_000[0x1c];       // 0x00
    f32 m01c;                 // 0x1c  pitch cos scale
    f32 m020;                 // 0x20  yaw accumulator
    u8  mPad_024[0x04];       // 0x24
    f32 m028;                 // 0x28  position x
    f32 m02c;                 // 0x2c  position y
    f32 m030;                 // 0x30  position z
    f32 m034;                 // 0x34  pitch
    u8  mPad_038[0x0c];       // 0x38
    f32 m044;                 // 0x44  "attached / cockpit" flag value
    f32 m048;                 // 0x48  accumulated anchor x
    f32 m04c;                 // 0x4c  accumulated anchor y
    f32 m050;                 // 0x50  accumulated anchor z
    f32 m054;                 // 0x54  velocity x
    f32 m058;                 // 0x58  velocity y
    f32 m05c;                 // 0x5c  velocity z
    u8  mPad_060[0x1c];       // 0x60
    f32 m07c;                 // 0x7c  strafe x
    f32 m080;                 // 0x80  strafe y
    f32 m084;                 // 0x84  strafe z
    f32 m088;                 // 0x88  bob x
    f32 m08c;                 // 0x8c  bob y
    f32 m090;                 // 0x90  bob z
    u8  mPad_094[0x18];       // 0x94
    f32 m0ac;                 // 0xac  accel x
    f32 m0b0;                 // 0xb0  accel y
    f32 m0b4;                 // 0xb4  accel z
    u8  mPad_0b8[0x5c];       // 0xb8
    f32 m114;                 // 0x114  desired position x
    f32 m118;                 // 0x118  desired position y
    f32 m11c;                 // 0x11c  desired position z
    u8  mPad_120[0x1c];       // 0x120
    f32 m13c;                 // 0x13c  eye anchor x
    f32 m140;                 // 0x140  eye anchor y
    f32 m144;                 // 0x144  eye anchor z
    u8  mPad_148[0x0c];       // 0x148
    f32 m154;                 // 0x154  orientation / basis x
    f32 m158;                 // 0x158  orientation / basis y
    f32 m15c;                 // 0x15c  orientation / basis z
    f32 m160;                 // 0x160  orientation / basis w
    u8  m164;                 // 0x164  "use +0x168 anchor" flag
    u8  mPad_165[0x03];       // 0x165
    f32 m168;                 // 0x168  alternate anchor x
    f32 m16c;                 // 0x16c  alternate anchor y
    f32 m170;                 // 0x170  alternate anchor z
    u8  mPad_174[0x38];       // 0x174
    f32 m1ac;                 // 0x1ac  cached desired x
    f32 m1b0;                 // 0x1b0  cached desired y
    f32 m1b4;                 // 0x1b4  cached desired z
    f32 m1b8;                 // 0x1b8  cached basis x
    f32 m1bc;                 // 0x1bc  cached basis y
    f32 m1c0;                 // 0x1c0  cached basis z
    f32 m1c4;                 // 0x1c4  cached basis w
    u8  mPad_1c8[0x58];       // 0x1c8
    f32 m220;                 // 0x220  field of view / unit scale
    u8  mPad_224[0x34];       // 0x224
    f32 m258;                 // 0x258  planet water-line angle
    f32 m25c;                 // 0x25c  surface offset angle
    u16 m260;                 // 0x260  state flags
    i16 m262;                 // 0x262  surface-contact counter
    f32 m264;                 // 0x264  orientation basis x
    f32 m268;                 // 0x268  orientation basis y
    f32 m26c;                 // 0x26c  orientation basis z
    f32 m270;                 // 0x270  current radius
    f32 m274;                 // 0x274  basis x row 0
    f32 m278;                 // 0x278  basis y row 0
    f32 m27c;                 // 0x27c  basis z row 0
    f32 m280;                 // 0x280  basis x row 1
    f32 m284;                 // 0x284  basis y row 1
    f32 m288;                 // 0x288  basis z row 1
    f32 m28c;                 // 0x28c  basis x row 2
    f32 m290;                 // 0x290  basis y row 2
    f32 m294;                 // 0x294  basis z row 2
};
extern "C" f32* FUN_0059aed0_s00d2_2f30(void* out, void* basis, void* orient);  // 0x0059aed0
// ---- items of slice s00d22f30 end

// ---- items of slice s00d247f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kDeg2Rad;   // 0x0147a304
extern const float kHalfDeg;   // 0x0147a330
extern bool g_158275c;
extern bool g_158275e;
extern bool g_158275f;
extern float g_1582760;
extern float g_1582764;
extern float g_1582768;
extern float g_158276c;
extern float g_1582770;
extern float g_1582774;
extern float g_1582778;
extern float g_158277c;
extern float g_1582780;
extern bool g_1582784;
extern bool g_1582785;
extern bool g_1582786;
extern float g_1582788;
extern float g_158278c;
extern float g_1582790;
extern float g_1582794;
extern float g_1582798;
extern float g_158279c;
extern float g_15827a0;
extern float g_15827a4;
extern float g_15827a8;
extern float g_15827b0;
extern float g_15827b4;
extern float g_15827b8;
extern float g_15827bc;
extern float g_15827c0;
extern float g_15827c4;
extern float g_15827c8;
extern float g_15827cc;
extern float g_15827d0;
extern float g_15827d4;
extern float g_15827d8;
extern float g_15827f0;
extern float g_15827f4;
extern float g_15827f8;
extern float g_15827fc;
extern float g_1582850;
extern float g_1582854;
extern float g_1582858;
extern float g_158285c;
extern float g_1582860;
extern float g_1582864;
extern float g_1582870;
extern float g_1582874;
extern bool g_169de80;
extern bool g_169de81;
extern bool g_169de82;
extern bool g_169de83;
extern bool g_169de84;
extern float g_169de90;
extern float g_169de94;
extern float g_169de98;
extern bool g_158275d;
extern char g_Mode_1654c10;
extern char g_Mode_1654c01;
struct Property {
    uint32_t pad0[4];
    uint16_t pad10; uint16_t mnType;
    float* GetFloat();     // 0x0041ea70
    int*   GetInt();       // 0x0041e990
    bool*  GetBool();      // 0x0041e920
};
struct cPropertyList_s00d2_47f0 {
    virtual void AddRef();
    virtual void Release();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
    virtual bool GetProperty(uint32_t id, Property** out);   // +0x24
};
struct cPropertyManager_s00d2_47f0 {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
    virtual bool GetPropertyList(uint32_t a, uint32_t b, cPropertyList_s00d2_47f0** out);   // +0x2c
};
struct Vec2_s00d2_47f0 { float x, y; inline void Scale(float s) { x = x * s; y = y * s; } };
cPropertyManager_s00d2_47f0* PropertyManager();                     // 0x0067de30
struct TerrainMgr { cPropertyList_s00d2_47f0* Fn1(); };             // 0x00b1daf0
TerrainMgr* __stdcall FUN_00b3d320(int a, void* mode);   // 0x00b3d320
void GetPropertyAsVector2(cPropertyList_s00d2_47f0* p, uint32_t id, Vec2_s00d2_47f0* out);   // 0x006a10c0
static const unsigned kDead_b1b104 = 0x00b1b104;
struct Local { Property* prop; uint32_t a; const void* dead; uint32_t b; };
#define PF(id, dst, mul) if (p && p->GetProperty(id, &loc.prop) && loc.prop->mnType == 0xd) dst = *loc.prop->GetFloat() mul
#define PB(id, dst) if (p && p->GetProperty(id, &loc.prop) && loc.prop->mnType == 1) dst = *loc.prop->GetBool()
#define PI(id, dst) if (p && p->GetProperty(id, &loc.prop) && loc.prop->mnType == 9) { uint32_t v = *(uint32_t*)loc.prop->GetInt(); if (v <= 2) dst = v; }
namespace SP {
class cCreatureCamera_s00d2_47f0 {
public:
    uint32_t pad0[0x1ec / 4];

    int m_1ec;
    uint32_t pad_1f0[2];
    float m_1f8;
    float m_1fc;
    float m_200;
    uint32_t pad_204[1];
    float m_208;
    float m_20c;
    float m_210;
    float m_214;
    float m_218;
    float m_21c;
    float m_220;
    float m_224;
    float m_228;
    float m_22c;
    float m_230;
    float m_234;
    float m_238;
    uint32_t pad_23c[1];
    float mDistA_x;
    float mDistA_y;
    float mFar_x;
    float mFar_y;
    float m_250;
    float m_254;
    uint32_t pad_258[44];
    cPropertyList_s00d2_47f0* mConfig;
    void ReloadTuning();  // 0x00d247f0 (SP::cCreatureCamera::ReloadTuning)
};
}
// ---- items of slice s00d247f0 end

// ---- items of slice s00d26790 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma warning(disable: 4100 4189 4244 4311 4312 4244)
typedef unsigned int   u32;
struct CalleeSet {
    void  FUN_00d38840();                            // 0x00d38840
    void  FUN_00d247f0();                            // 0x00d247f0
    void  FUN_00d21d90();                            // 0x00d21d90
    void  FUN_00d21b10(float a, float b, float c);   // 0x00d21b10
    void  FUN_00d26c90();                            // 0x00d26c90
    void  FUN_00d100b0(int a, int b);                // 0x00d100b0
    void  FUN_00d263d0(int n);                       // 0x00d263d0
};
#define SELF(o) ((CalleeSet*)(o))
struct Mat3 { float r0c0, r0c1, r0c2, r1c0, r1c1, r1c2, r2c0, r2c1, r2c2; };
struct cCamView {
    u8      mGap00[0x04];
    void*   mp04;              // +0x004  container handle
    u8      mGap08[0x14];
    float   mF1c;              // +0x01c
    u8      mGap20[0x18];
    Vec3    mF38;              // +0x038
    u8      mGap44[0x04];
    Vec3    mA48;              // +0x048
    u8      mGap54[0x0c];
    Vec4    mB60;              // +0x060
    Vec3    mC70;              // +0x070
    Vec3    mD7c;              // +0x07c
    Vec3    mE88;              // +0x088
    Vec3    mF94;              // +0x094
    u8      mGapA0[0x58];
    float   mFf8;              // +0x0f8
    float   mFfc;              // +0x0fc
    float   mF100;             // +0x100
    u8      mGap104[0x04];
    Vec3    mF108;             // +0x108  direction (3 floats)
    Vec3    mF114;             // +0x114
    u8      mGap120[0x34];
    Vec4    mF154;             // +0x154
    u8      mGap164[0x10];
    float   mF174;             // +0x174
    float   mF178;             // +0x178
    float   mF17c;             // +0x17c
    u8      mGap180[0x0c];
    float   mF18c;             // +0x18c
    float   mF190;             // +0x190
    float   mF194;             // +0x194
    u8      mGap198[0x14];
    Vec3    mF1ac;             // +0x1ac
    Vec4    mF1b8;             // +0x1b8
    Vec3    mF1c8;             // +0x1c8
    Vec4    mF1d4;             // +0x1d4
    u8      mGap1e4[0x08];
    u32     mW1ec;             // +0x1ec
    u8      mGap1f0[0x18];
    float   mF208;             // +0x208
    float   mF20c;             // +0x20c
    float   mF210;             // +0x210
    float   mF214;             // +0x214
    u8      mGap218[0x08];
    float   mF220;             // +0x220
    u8      mGap224[0x14];
    float   mF238;             // +0x238
    u8      mGap23c[0x24];
    u32     mW260;             // +0x260
    float   mF264;             // +0x264
    float   mF268;             // +0x268
    float   mF26c;             // +0x26c
    float   mF270;             // +0x270
    Mat3    mMat274;           // +0x274
    u8      mB298;             // +0x298
    u8      mGap299[0x03];
    void*   mp29c;             // +0x29c
    void*   mp2a0;             // +0x2a0
    void*   mp2a4;             // +0x2a4
    u32     mW2a8;             // +0x2a8
    void*   mp2ac;             // +0x2ac
    u8      mGap2b0[0x0c];
    u32     mW2bc;             // +0x2bc
    u8      mGap2c0[0x44];
    u8      mB304;             // +0x304

    void FUN_00d26790();
    void FUN_00d26bb0();
    void FUN_00d26c90();
    void FUN_00d26ed0(const Vec3* pA, const Vec4* pB, float c, float d, float e);
    void FUN_00d270a0(Vec3* pOut);
    void FUN_00d271d0(Vec3* pOut);
    void FUN_00d272e0();
};
// ---- items of slice s00d26790 end

// ---- items of slice s00d27a70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_169de9c;       // 0x0169de9c
extern float g_169dea0;       // 0x0169dea0
extern float g_169dea4;       // 0x0169dea4
extern float kEpsilon;        // 0x0147a31c  (1.5258789e-05)
extern float gRotAxisX;       // 0x0169df5c
extern float gRotAxisY;       // 0x0169df60
extern float gRotAxisZ;       // 0x0169df64
#pragma intrinsic(sqrt, fabs, sin, cos)
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
__forceinline float Clamp(float value, float minValue, float maxValue)
{
    __asm {
        movss xmm0, value
        maxss xmm0, minValue
        minss xmm0, maxValue
        movss value, xmm0
    }
    return value;
}
struct Vec3_s00d2_7a70 {
    float x, y, z;
    Vec3_s00d2_7a70() {}
    Vec3_s00d2_7a70(float a, float b, float c) : x(a), y(b), z(c) {}
    Vec3_s00d2_7a70(const Vec3_s00d2_7a70& v) : x(v.x), y(v.y), z(v.z) {}
};
inline Vec3_s00d2_7a70 operator-(const Vec3_s00d2_7a70& a, const Vec3_s00d2_7a70& b)
{
    Vec3_s00d2_7a70 r(a.x - b.x, a.y - b.y, a.z - b.z);
    return r;
}
__declspec(noinline) static float VecDistance(const Vec3_s00d2_7a70& a, const Vec3_s00d2_7a70& b)
{
    double dx = (double)a.x - (double)b.x;
    double dy = (double)a.y - (double)b.y;
    double dz = (double)a.z - (double)b.z;
    return (float)sqrt((dx * dx + dz * dz) + dy * dy);
}
void  __cdecl operator_delete__(void* p) throw();                   // 0x00f47380
Vec3_s00d2_7a70* __cdecl normalized_safe(Vec3_s00d2_7a70* out, const Vec3_s00d2_7a70* in);           // 0x00449c20
void  __cdecl RotateAroundAxis(Vec3_s00d2_7a70* out, const Vec3_s00d2_7a70* v, const Vec3_s00d2_7a70* axis, float angle);   // 0x00d21d10
struct IRayWorld {
    PV8 PV2
    virtual int RayCast(const Vec3_s00d2_7a70* from, const Vec3_s00d2_7a70* to, float* tOut, void* filter);   // 0x28
};
struct IModelManager {
    PV4 PV2 PV
    virtual IRayWorld* GetWorld(uint32_t id);                       // 0x1c
};
IModelManager* __cdecl ModelManager();                              // 0x0067dd80
struct cPlanetModel_s00d2_7a70 {
    Vec3_s00d2_7a70* DirectionToSurfacePosition(Vec3_s00d2_7a70* out, const Vec3_s00d2_7a70* in);    // 0x00b815a0
    Vec3_s00d2_7a70* SnapToSurface(Vec3_s00d2_7a70* out, const Vec3_s00d2_7a70* in, int flag);       // 0x00b82b40
    Quat* SurfaceOrientation(Quat* out, const Vec3_s00d2_7a70* in, const Quat* prev);   // 0x00b7f1f0
};
cPlanetModel_s00d2_7a70* __cdecl PlanetModel_s00d2_7a70();                                // 0x00b3d350
struct cSpatialQuery {
    int QueryNear(const Vec3_s00d2_7a70* pos, float radius, int flags, void* outHits);                          // 0x00b7a1d0
    int QueryNearBlocked(const Vec3_s00d2_7a70* from, const Vec3_s00d2_7a70* tmp, float radius, void* outHits, int flag);  // 0x00b7a4a0
};
cSpatialQuery* __cdecl SpatialQuery();                              // 0x00b3d3c0
struct cAvatarBody {
    PV8 PV8 PV8 PV4 PV
    virtual float GetMinDistance();                                 // 0x74
};
struct cAvatar_s00d2_7a70 { char pad[0xc0]; cAvatarBody mBody; };
struct cNounManager { cAvatar_s00d2_7a70* GetAvatar(); };                      // 0x00b1fdb0
cNounManager* __cdecl NounManager_s00d2_7a70();                                // 0x00b3d300
struct HitObject {
    char  pad00[0x38];
    Vec3_s00d2_7a70  mCenter;      // +0x38
    float m44;          // +0x44
    char  pad48[4];
    float m4c;          // +0x4c
    char  pad50[0x88 - 0x50];
    int   mType;        // +0x88
};
bool __cdecl RayHitsObject(const Vec3_s00d2_7a70* origin, const Vec3_s00d2_7a70* dir, const Vec3_s00d2_7a70* center, const Vec3_s00d2_7a70* centerUnit,
                           float a, float b, float* tOut, float* out2);       // 0x00698fa0
struct HitVec {
    HitObject** mpBegin;
    HitObject** mpEnd;
    HitObject** mpCap;
    int         mAlloc0, mAlloc1;
    int         mCookie;
    HitObject*  mBuf[256];
    HitVec() { mCookie = 0; mpBegin = mBuf; mpEnd = mBuf; mpCap = mBuf + 256; }
    ~HitVec() { if (mpBegin && ((int*)mpBegin)[-1] != 0) operator_delete__(mpBegin); }
};
struct RayFilter { int a, b, c, d, e; char kind; char flag; };
namespace SP {
class cCreatureCamera_s00d2_7a70 {
public:
    char  pad00[0x48];
    Vec3_s00d2_7a70  m48;
    char  pad54[0xa0 - 0x54];
    Vec3_s00d2_7a70  mA0;
    char  padac[0xec - 0xac];
    float mEC, mF0, mF4;
    float mF8, mFC, m100;
    char  pad104[0x108 - 0x104];
    Vec3_s00d2_7a70  mP1;
    Vec3_s00d2_7a70  mAnchor;       // +0x114
    char  pad120[0x13c - 0x120];
    Vec3_s00d2_7a70  mCamPos;       // +0x13c
    char  pad148[0x174 - 0x148];
    float m174, m178, m17c;
    char  pad180[0x2b0 - 0x180];
    bool  mb2b0;

    float GetPitch(float a, float b);                       // 0x00d21810
    void  ApplyPlayerDeltas(bool flag);                     // @ 0x00d27a70
};  // namespace SP
}
extern float kDeg2Rad_s00d2_7a70;        // 0x0147a304
extern Vec3_s00d2_7a70  gDefaultDir;     // 0x0169deb0
bool __cdecl IsGameRunning();                                         // 0x00805180
Quat* __cdecl QuatMultiply(Quat* out, const Quat* a, const Quat* b);  // 0x007dcb00
Vec3_s00d2_7a70* __cdecl QuatRotate(Vec3_s00d2_7a70* out, const Vec3_s00d2_7a70* v, const Quat* q);    // 0x0059aed0
struct cGameInputManager_s00d2_7a70 {
    PV4 PV2
    virtual bool IsKeyDown(int key);                                  // 0x18
};
cGameInputManager_s00d2_7a70* __cdecl GameInputManager_s00d2_7a70();                        // 0x00b3d250
struct ITerrain {
    PV8 PV4 PV2
    virtual void ProjectPosition(Vec3_s00d2_7a70& pos, int mode, Vec3_s00d2_7a70 dir);      // 0x38
};
ITerrain* __cdecl GetTerrain();                                       // 0x00b3d240
template <class T> inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }
class cFreeCamera {
public:
    char  pad00[0x1c];
    float mDeltaTime;            // +0x1c
    char  pad20[0x180 - 0x20];
    float mYaw;                  // +0x180
    float mPitch;                // +0x184
    float mDistance;             // +0x188
    float mRollAngle;            // +0x18c
    char  pad190[4];
    float mDistance2;            // +0x194
    char  pad198[0x1ac - 0x198];
    Vec3_s00d2_7a70  mPos;                  // +0x1ac
    Quat  mOrient;               // +0x1b8
    Vec3_s00d2_7a70  mAnchor;               // +0x1c8
    Quat  mRot;                  // +0x1d4
    char  pad1e4[0x208 - 0x1e4];
    float mMinPitch, mMaxPitch, mMinDistance;   // +0x208, +0x20c, +0x210
    char  pad214[0x254 - 0x214];
    float mSpeed;                // +0x254

    void Update(float dt);       // @ 0x00d28300
};
// ---- items of slice s00d27a70 end

// @ 0x00d20620
float10 tCamCtrl::FUN_00d20620(float p)
{
    float lo = m210;
    if (p < lo)
        return *(float*)0x01582854;
    float hi = m214;
    if (hi < p)
        return *(float*)0x01582860;
    if (p <= lo)
        p = lo;
    if (hi <= p)
        p = hi;
    float t = (p - lo) / (hi - lo);
    float r = (((3.0f - t * 2.0f) * t) * t) * (*(float*)0x01582860 - *(float*)0x01582854)
              + *(float*)0x01582854;
    return r;
}

// @ 0x00d20880
void tCamCtrl::FUN_00d20880(const tVec3& a, const tVec4& b)
{
    m1ac = a;
    m1c8 = a;
    m1b8 = b;
    m1d4 = b;
    m298 = 1;
}

// @ 0x00d20910
void tCamCtrl::FUN_00d20910(float f)
{
    m17c = f;
    m100 = f;
    m188 = f;
    m194 = f;
}

// @ 0x00d20950
void tCamCtrl::FUN_00d20950(unsigned n)
{
    if (n <= 7)
        m1e8 = n;
}

// @ 0x00d20970
unsigned char FUN_00d20970(void)
{
    unsigned char r = 0;
    if (GetCurrentGameMode() == (void*)0x01654c05)
        return 1;
    if (static_cast<cCreatureModeStrategy*>(CreatureModeStrategy_Instance())->m64 != 0)
        return static_cast<cCreatureModeStrategy*>(CreatureModeStrategy_Instance())->m64->m54;
    cGlobalMgr* g = *(cGlobalMgr**)0x016c7aa4;
    cModeTarget* t = g->m68;
    if (t == 0)
        return r;
    return t->m54;
}

// @ 0x00d213b0
bool cCreatureCameraIGB1::HandleMessage(unsigned int id, void* msg)
{
    unsigned int p = 0;

    switch (id) {
    case 0x25db76a:
    case 0x25db76f:
    case 0x35f7b83:
    case 0x51cbb29:
    case 0x51cbb2d:
    case 0x507cc87f:
    case 0x6493c83:
    case 0x705673e1:
    case 0x705673e9: {
        cMsgObj* m = (cMsgObj*)msg;
        cMsgObj* sel = (cMsgObj*)m->vf10();
        unsigned int* payload = (unsigned int*)sel->vf1c(1);
        p = payload ? *payload : 0;
        break;
    }
    }

    switch (id) {
    case 0x25db76a:
        mI1E8 = (p > 0) ? 4 : 0;
        break;
    case 0x25db76f:
        mI1E8 = (p > 0) ? 5 : 0;
        break;
    case 0x705673e1:
        mI1E8 = (p > 0) ? 1 : 0;
        break;
    case 0x705673e9:
        mI1E8 = (p > 0) ? 2 : 0;
        break;
    case 0x51cbb29:
        mI1E8 = (p > 0) ? 6 : 0;
        break;
    case 0x51cbb2d:
        mI1E8 = (p > 0) ? 7 : 0;
        break;
    case 0x50567351:
        if (mI1EC == 2)
            break;
        mI1E8 = 3;
        break;
    case 0x1c38e3b:
        if (mI1EC == 2)
            break;
        mI1F0 = 0;
        break;
    case 0x19edcf3:
        if (mI1EC == 2)
            break;
        mI1F0 = 0;
        mb315 = true;
        break;
    case 0x27c67ea:
        if (mI1EC == 2)
            break;
        if (!mb315)
            mI1F0 = 1;
        if (mI1F0 == 1)
            break;
        mb1F4 = false;
        break;
    case 0x27c7119:
        if (mI1EC == 2)
            break;
        if (!mb315)
            mI1F0 = 1;
        mb1F4 = true;
        break;
    case 0x35f7b83: {
        cCreatureModeStrategy_s00d2_13b0* strategy = cCreatureModeStrategy_s00d2_13b0::Instance();
        cCreatureModeInputStrategy*& input = strategy->mpInputStrategy;
        bool doubleClicked = false;
        if (input && input->mb54 && input->DidDoubleClick(0x18))
            doubleClicked = true;
        if (p && !doubleClicked)
            break;
        mF12C = 0.0f;
        mF130 = 0.0f;
        break;
    }
    case 0x507cc87f:
        if (mbCameraReverse != (p > 0))
            mbCameraReverse = (p > 0);
        break;
    case 0x6493c83:
        ((cCreatureCamera*)((char*)this - 4))->SetCameraUI(p > 0);
        break;
    case 0xd02dcc68: {
        if (mI1EC == 2)
            break;
        cGameInputManager* input = (cGameInputManager*)GameInputManager();
        if (!input) {
            mb315 = false;
            break;
        }
        bool active = input->vf18(1) || input->vf18(2) || input->vf18(3) || input->vf18(4);
        mb315 = false;
        mI1F0 = active ? 1 : 0;
        break;
    }
    case 0x62663dd:
    case 0x4d9686f:
    case 0xd33b6aa2:
    case 0xf3327645: {
        void* mode = GetCurrentGameMode();
        if (mode == &gModeCreatureB || mode == &gModeCreatureA) {
            ((cUiObject*)FUN_0067cab0())->Set40(true);
            ((cUiObject*)FUN_0067cab0())->Set(false);
            mb314 = false;
            mb315 = false;
        }
        break;
    }
    }
    return false;
}

// @ 0x00d217e0
bool cCreatureCamera::OnMouseDown(unsigned int id, float x, float y, unsigned int flags)
{
    mLocalInputState.OnMouseDown(id, x, y, flags);
    return true;
}

// @ 0x00d21810
float cCreatureCamera::GetPitch(float a, float b)
{
    if (gUsePitchArg) {
        b = a;
    } else if (gUsePitchRefine) {
        b = ((cCameraMathView*)this)->RefinePitch(b);
    } else {
        b = ((cCameraMathView*)this)->AdjustPitchAndDistance(a, b);
    }

    cAvatar* avatar = (cAvatar*)NounManager()->GetAvatar();
    if (avatar) {
        if (PlanetModel()) {
            Vec3 pos = *avatar->mLoco.vf2c();
            float len = sqrtf(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z);
            float inv = 1.0f / sqrtf(mV48.x * mV48.x + mV48.y * mV48.y + mV48.z * mV48.z + 1e-8f);
            Vec3 scaled;
            scaled.x = (mV48.x * inv) * len;
            scaled.y = (mV48.y * inv) * len;
            scaled.z = (mV48.z * inv) * len;

            Vec3 target;
            ((cPlanetModel*)PlanetModel())->FUN_00b81630(&target, &mV48);

            Vec3 d;
            d.x = scaled.x - pos.x;
            d.y = scaled.y - pos.y;
            d.z = scaled.z - pos.z;
            float invD = 1.0f / sqrtf(d.x * d.x + d.y * d.y + d.z * d.z + 1e-8f);
            Vec3 u;
            u.x = d.x * invD;
            u.y = d.y * invD;
            u.z = d.z * invD;

            Vec3 w;
            w.x = target.x - pos.x;
            w.y = target.y - pos.y;
            w.z = target.z - pos.z;
            float invW = 1.0f / sqrtf(w.x * w.x + w.y * w.y + w.z * w.z + 1e-8f);
            w.x = w.x * invW;
            w.y = w.y * invW;
            w.z = w.z * invW;

            float dot = (w.x * u.x + w.z * u.z) + w.y * u.y;
            if (dot < -1.0f)
                dot = -1.0f;
            if (dot > 1.0f)
                dot = 1.0f;

            float ang = Acos(dot);
            mF1E4 = ang;
            float sign = (len <= sqrtf((target.x * target.x + target.z * target.z) + target.y * target.y))
                             ? 1.0f : -1.0f;
            mF1E4 = ang * sign;
            b = ang * sign + b;
        }
    }
    return b;
}

// @ 0x00d21b10
void cCreatureCamera::FUN_00d21b10(float x, float y, float z)
{
    mF180 = x;
    mF18C = x;
    // retail clamps with maxss/minss: the value is the second operand on NaN, so the
    // comparison forms below (not "if (v < lo)") are the ones with matching semantics.
    float yy = y > mPitchLimits.x ? y : mPitchLimits.x;
    yy = yy < mPitchLimits.y ? yy : mPitchLimits.y;
    mF184 = yy;
    mF190 = yy;
    float zz = z > 0.1f ? z : 0.1f;
    mF188 = zz;
    mF194 = zz;
    mTransformNeedsUpdating = true;
}

// @ 0x00d21bc0
void cCreatureCamera::FUN_00d21bc0(float x, float y, float z)
{
    mF180 = x;
    float yy = y > mPitchLimits.x ? y : mPitchLimits.x;
    yy = yy < mPitchLimits.y ? yy : mPitchLimits.y;
    mF184 = yy;
    mF188 = z > 0.1f ? z : 0.1f;
}

// @ 0x00d21c50
Vec3* cCreatureCamera::GetAudioAnchorPosition(Vec3* out)
{
    cPlanetModel* planet = (cPlanetModel*)PlanetModel();
    if (planet) {
        planet->DirectionToSurfacePosition(out, &mAudioAnchor);
        return out;
    }
    out->x = mAudioAnchor.x;
    out->y = mAudioAnchor.y;
    out->z = mAudioAnchor.z;
    return out;
}

// @ 0x00d21ca0
int FUN_00d21ca0(const Vec3* a, const Vec3* b, float tolerance)
{
    if (AbsValue(a->x - b->x) <= tolerance) {
        if (AbsValue(a->y - b->y) <= tolerance) {
            if (AbsValue(a->z - b->z) <= tolerance)
                return 1;
        }
    }
    return 0;
}

// @ 0x00d21d10
Vec3* FUN_00d21d10(Vec3* out, const Vec3* v, const Vec3* axis, float angle)
{
    float half = angle * 0.5f;
    float s = sinf(half);
    float c = cosf(half);
    Quat q;
    q.x = axis->x;
    q.y = axis->y;
    q.z = axis->z;
    q.x = q.x * s;
    q.y = q.y * s;
    q.z = q.z * s;
    q.w = c;
    Vec3 tmp;
    Vec3* r = FUN_0059aed0(&tmp, v, &q);
    out->x = r->x;
    out->y = r->y;
    out->z = r->z;
    return out;
}

// @ 0x00d21d90
void cCreatureCamera::UpdateCamera_Free()
{
    cAvatar* avatar = (cAvatar*)NounManager()->GetAvatar();
    cViewer* viewer = (cViewer*)App()->vf58();
    if (avatar && viewer) {
        cLoco* loco = &avatar->mLoco;

        Vec3 anchor;
        Vec3* anchorPos = loco->vf5c(&anchor);
        mVb8.x = anchorPos->x;
        mVb8.y = anchorPos->y;
        mVb8.z = anchorPos->z;

        Vec3* velocity = loco->vf2c();
        float inv = 1.0f / sqrtf(velocity->x * velocity->x + velocity->y * velocity->y
                                 + velocity->z * velocity->z + 1e-8f);
        mVc4.x = velocity->x * inv;
        mVc4.y = velocity->y * inv;
        mVc4.z = velocity->z * inv;

        float scale = loco->vf68()->mf14;
        Vec3 offset;
        offset.x = mVc4.x * scale;
        offset.y = mVc4.y * scale;
        offset.z = mVc4.z * scale;
        Vec3* position = loco->vf2c();
        mVa0.x = position->x + offset.x;
        mVa0.y = position->y + offset.y;
        mVa0.z = position->z + offset.z;

        mV114 = mVa0;
        mV1AC = mVa0;
        mAudioAnchor = mVa0;

        if (!mbSkipInit) {
            Vec3 camPos, camDir, camUp, camRight;
            viewer->GetCameraLocationInfo(&camPos, &camDir, &camUp, &camRight);

            float mat9[9];
            viewer->mCameraToWorldTransform.FUN_007c3da0(mat9);

            mV48 = camPos;
            mV13C = camPos;

            Quat q;
            FUN_0046d660(&q.x, mat9);
            mQ60 = q;
            mQ154 = q;
            mQ1B8 = q;
            mQ1D4 = q;

            float dx = mV114.x - mV48.x;
            float dy = mV114.y - mV48.y;
            float dz = mV114.z - mV48.z;
            float dist = sqrtf(dx * dx + dy * dy + dz * dz);
            if (dist < mMinCameraPhi)
                dist = mMinCameraPhi;
            if (dist > mMaxCameraPhi)
                dist = mMaxCameraPhi;

            Vec3 normal;
            normalized_safe(&normal.x, &mV48.x);
            float d1 = (normal.x * camDir.x + normal.z * camDir.z) + normal.y * camDir.y;
            Vec3 projected;
            projected.x = camDir.x - normal.x * d1;
            projected.y = camDir.y - normal.y * d1;
            projected.z = camDir.z - normal.z * d1;

            Vec3 up;
            normalized_safe(&up.x, &projected.x);
            float d2 = (up.x * camDir.x + up.y * camDir.y) + up.z * camDir.z;
            if (d2 < -1.0f)
                d2 = -1.0f;
            if (d2 > 1.0f)
                d2 = 1.0f;

            mReferenceHeading = up;
            mF174 = 0.0f;
            mFieldF8 = 0.0f;
            mF17C = dist;
            mField100 = dist;
            mF188 = dist;
            mF194 = dist;

            float ang = Acos(d2);
            float lifted = ((cCameraMathView*)this)->AdjustPitchAndDistance(ang, dist);
            mF178 = lifted;
            mFieldFC = lifted;
        }

        mTransformNeedsUpdating = true;
        mInputConst = kInputConst;
        mV54 = kZeroVec;
        mV148 = kZeroVec;
        mOscillationTime = 0.0f;
        mBreathOffset = 0.0f;
        mShakeOffset = kZeroVec;
        mRoll = 0.0f;
        mb104 = false;
        mb105 = false;
        mF130 = 0.0f;
        mF12C = 0.0f;
        mF138 = 0.0f;
        mF134 = 0.0f;
        mV108.x = mVa0.x - mVb8.x;
        mV108.y = mVa0.y - mVb8.y;
        mV108.z = mVa0.z - mVb8.z;
        mF1E4 = 0.0f;
    }
    mbSkipInit = false;
}

// @ 0x00d23840
void cCreatureCamera_s00d2_2f30::FUN_00d23840()
{
    f32* pa = (m164 != 0) ? &m168 : &m13c;
    f32 vx = pa[0];
    f32 vy = pa[1];
    f32 vz = pa[2];

    f32 tmp[3];
    f32* pf = FUN_0059aed0_s00d2_2f30(tmp, &DAT_0169df44, &m154);

    f32 f = sqrt(((f64)m114 - (f64)m13c) * ((f64)m114 - (f64)m13c)
               + ((f64)m118 - (f64)m140) * ((f64)m118 - (f64)m140)
               + ((f64)m11c - (f64)m144) * ((f64)m11c - (f64)m144));

    vx = pf[0] * f + vx;
    vy = pf[1] * f + vy;
    vz = pf[2] * f + vz;

    f32 val = f;
    if (m044 > _HK_REAL_ZERO) {
        // cache the desired position and the orientation frame
        *(SP_Vector3 *)&m1ac = *(SP_Vector3 *)&m114;
        *(SP_Vector4 *)&m1b8 = *(SP_Vector4 *)&m154;
    } else {
        val = FUN_00d20880(&vx, &m154);
    }
    FUN_00d21bc0(0.0f, 0.0f, val);
}

// @ 0x00d247f0
namespace SP {
void cCreatureCamera_s00d2_47f0::ReloadTuning()
{
    Local loc;
    cPropertyList_s00d2_47f0* p;
    #define Q(id, dst, mul) if (mConfig && mConfig->GetProperty(id, &loc.prop) && loc.prop->mnType == 0xd) dst = *loc.prop->GetFloat() mul

    Q(0x1102b20, this->m_220);
    Q(0x1102b2f, this->m_224);
    #undef Q
    cPropertyManager_s00d2_47f0* pm = PropertyManager();
    p = 0;
    uint32_t keyA = 0xd03a25cf, keyB = 0xad56080c;
    if (GetCurrentGameMode() == &g_Mode_1654c10) {
        keyA = 0x70ec1123; keyB = 0x408a0100;
        loc.dead = (const void*)kDead_b1b104;
    }
    if (p) { cPropertyList_s00d2_47f0* t = p; p = 0; t->Release(); }
    if (pm->GetPropertyList(keyA, keyB, &p)) {
    PI(0xb060e649, this->m_1ec);
    PF(0xb03ee61d, this->m_218, );
    PF(0x503ee62b, this->m_21c, * kDeg2Rad);
    PF(0x303eb34d, this->m_210, );
    PF(0x703eb357, this->m_214, );
    PB(0xd0723c18, g_169de80);
    PB(0x30723c1d, g_169de81);
    PF(0x50723c22, g_1582850, * kDeg2Rad);
    PF(0xf0723c26, g_1582854, * kDeg2Rad);
    PF(0x70723c2c, g_1582858, * kDeg2Rad);
    PF(0x70723c32, g_158285c, * kDeg2Rad);
    PF(0x90723c38, g_1582860, * kDeg2Rad);
    PF(0xb0723c3c, g_1582864, * kDeg2Rad);
    PF(0x7b68967, this->m_208, * kDeg2Rad);
    PF(0x7b68979, this->m_20c, * kDeg2Rad);
    PB(0x19bdd9c, g_169de82);
    PB(0x19d778a, g_158275c);
    PF(0xf06d1e9b, this->m_1f8, * kHalfDeg);
    PF(0x306d1e9e, this->m_1fc, * kHalfDeg);
    PF(0x506d1ea0, this->m_200, );
        {
            GetPropertyAsVector2(p, 0xedb1e6ec, (Vec2_s00d2_47f0*)&this->mDistA_x);
            float* pf = &this->mDistA_x;
            const float k1 = kDeg2Rad;
            *pf = *pf * k1;
            this->mDistA_y = this->mDistA_y * k1;
            GetPropertyAsVector2(p, 0x50c6e997, (Vec2_s00d2_47f0*)&this->mFar_x);
            float* pf2 = &this->mFar_x;
            const float k2 = kDeg2Rad;
            *pf2 = *pf2 * k2;
            this->mFar_y = this->mFar_y * k2;
        }
    PF(0x22fb568c, this->m_250, );
    PF(0x14f8c017, g_15827b4, );
    PF(0xeec1bc52, g_15827a4, );
    PF(0x47a9c597, g_1582870, );
        g_1582870 = g_1582870 * kDeg2Rad;
    PF(0x8c78383d, g_1582874, );
        g_1582874 = g_1582874 * kDeg2Rad;
    PF(0xc8624936, g_15827a8, );
    PF(0x3dbe5f51, g_15827b0, );
    PF(0x126ecc27, g_15827b8, );
    PF(0xe815bc27, g_15827bc, );
    PF(0xb5f3ddd9, g_15827c0, );
    PF(0x61197290, g_15827c4, );
    PF(0xbc7c9cee, g_15827c8, );
    PF(0x60ea71bd, g_15827cc, );
    PF(0x8a1a6bc7, g_15827d0, );
    PF(0x29ce91, g_15827d4, );
    PF(0x8d98b7f8, g_15827d8, );
    PF(0xff6e121b, g_169de90, );
    PF(0xca517888, g_169de94, );
    PF(0x7be527ed, g_169de98, );
    PF(0x1a57b85, g_1582760, );
    PF(0x1a57b91, g_1582764, );
    PF(0x1a57b9b, g_1582768, );
    PF(0x2797fff, this->m_254, );
    PF(0xd03ee49b, this->m_228, );
    PF(0x703ee4a1, this->m_22c, );
    PF(0x503ee4a2, this->m_230, );
    PF(0x303ee4a4, this->m_234, );
    PF(0xf03ee4a8, this->m_238, );
    PB(0x50652350, g_158275e);
    PB(0x50692031, g_158275f);
    PF(0x90652352, g_158276c, );
    PF(0x70652353, g_1582770, );
    PF(0x10652354, g_1582774, );
    PF(0xf0652355, g_1582778, );
    PF(0xf0652356, g_158277c, );
    PF(0x3065235a, g_1582780, );
    PB(0x706913e6, g_1582784);
    PB(0x50692288, g_1582785);
    PF(0xf06913e7, g_1582788, );
    PF(0x706913e8, g_158278c, );
    PF(0xd06913ea, g_1582790, );
    PF(0xd06913ea, g_1582794, );
    PF(0x106913eb, g_1582798, );
    PF(0x506913ed, g_158279c, );
    PF(0xf0692887, g_15827a0, );
    PF(0x582c3384, g_15827f0, );
    PB(0x1c71aad, g_1582786);
    PB(0xb057d114, g_169de83);
    PB(0x306536a3, g_169de84);
    }
    {
        cPropertyList_s00d2_47f0* np = FUN_00b3d320(1, GetCurrentGameMode())->Fn1();
        if (np != p) {
            cPropertyList_s00d2_47f0* old = p;
            if (np) np->AddRef();
            p = np;
            if (old) old->Release();
        }
    }
    PF(0x2648458, g_15827f4, );
    PF(0x3d03d69, g_15827f8, );
    PF(0x556a736a, g_15827fc, );
    g_158275d = GetCurrentGameMode() == &g_Mode_1654c01;
    if (p) p->Release();
}
}  // namespace SP

// @ 0x00d270a0
void cCamView::FUN_00d270a0(Vec3* pOut)
{
    if (mB298 != 0)
        SELF(this)->FUN_00d26c90();
    Vec3 t;
    t.x = *(float*)0x169deb0;
    t.y = *(float*)0x169deb4;
    t.z = *(float*)0x169deb8;
    pOut->x = t.x; pOut->y = t.y; pOut->z = t.z;
    if (mW260 & 2) {
        pOut->x = mMat274.r0c0 * t.x + mMat274.r0c1 * t.y + mMat274.r0c2 * t.z;
        pOut->y = mMat274.r1c0 * t.x + mMat274.r1c1 * t.y + mMat274.r1c2 * t.z;
        pOut->z = mMat274.r2c0 * t.x + mMat274.r2c1 * t.y + mMat274.r2c2 * t.z;
    }
    float s = mF270;
    pOut->x = pOut->x * s + mF264;
    pOut->y = pOut->y * s + mF268;
    pOut->z = pOut->z * s + mF26c;
}

// @ 0x00d271d0
void cCamView::FUN_00d271d0(Vec3* pOut)
{
    if (mB298 != 0)
        SELF(this)->FUN_00d26c90();
    float x = *(float*)0x169df44;
    float y = *(float*)0x169df48;
    float z = *(float*)0x169df4c;
    pOut->x = x; pOut->y = y; pOut->z = z;
    if (mW260 & 2) {
        pOut->x = mMat274.r0c0 * x + mMat274.r0c1 * y + mMat274.r0c2 * z;
        pOut->y = mMat274.r1c0 * x + mMat274.r1c1 * y + mMat274.r1c2 * z;
        pOut->z = mMat274.r2c0 * x + mMat274.r2c1 * y + mMat274.r2c2 * z;
    }
    float s = mF270;
    pOut->x = s * pOut->x;
    pOut->y = s * pOut->y;
    pOut->z = s * pOut->z;
}

// @ 0x00d272e0
void cCamView::FUN_00d272e0()
{
    if (mW1ec == 2)
        SELF(this)->FUN_00d263d0(0);
    else
        SELF(this)->FUN_00d263d0(2);
}

// @ 0x00d27a70
namespace SP {
void cCreatureCamera_s00d2_7a70::ApplyPlayerDeltas(bool flag)
{
    if (mb2b0) {
        Vec3_s00d2_7a70 d = mP1 - mA0;
        float dxz = d.x * d.x + d.z * d.z;
        float lenSq = dxz + d.y * d.y;
        HitVec hits;
        float len = (float)sqrt((double)lenSq);
        float inv = (float)(1.0 / sqrt((double)lenSq + 1e-8f));
        Vec3_s00d2_7a70 dir;
        dir.x = d.x * inv;
        dir.y = d.y * inv;
        dir.z = d.z * inv;
        if (g_158275d) {
            IRayWorld* world = ModelManager()->GetWorld(0x3fbae24);
            RayFilter filter = { 0, 0, 0, 0, 0, 4, 0 };
            float t;
            if (world->RayCast(&mA0, &mP1, &t, &filter) && t > kEpsilon) {
                float k = t * len - 1.0f;
                mP1.x = mA0.x + dir.x * k;
                mP1.y = mA0.y + dir.y * k;
                mP1.z = mA0.z + dir.z * k;
            } else {
                Vec3_s00d2_7a70 tmp;
                PlanetModel_s00d2_7a70()->DirectionToSurfacePosition(&tmp, &mP1);
                SpatialQuery()->QueryNearBlocked(&mA0, &tmp, 1.0f, &hits, 0);
            }
        } else {
            SpatialQuery()->QueryNear(&mP1, 1.0f, 0x18, &hits);
        }
        int n = (int)(hits.mpEnd - hits.mpBegin);
        if (n <= 0) {
            g_169de9c = mF8;
            g_169dea4 = mFC;
            g_169dea0 = m100;
        } else if (!g_158275d) {
            mP1 = mCamPos;
            m174 = g_169de9c; mF8 = g_169de9c;
            m178 = g_169dea4; mFC = g_169dea4;
            m17c = g_169dea0; m100 = g_169dea0;
        } else {
            float minT = len;
            for (int i = 0; i < n; ++i) {
                HitObject* o = hits.mpBegin[i];
                if ((1 << (o->mType & 31)) & 8) {
                    const Vec3_s00d2_7a70& c = o->mCenter;
                    float cinv = 1.0f / (float)sqrt((double)(c.x * c.x + c.y * c.y + c.z * c.z + 1e-8f));
                    Vec3_s00d2_7a70 cu;
                    cu.x = c.x * cinv; cu.y = c.y * cinv; cu.z = c.z * cinv;
                    float t, out2;
                    if (RayHitsObject(&mA0, &dir, &o->mCenter, &cu, o->m44, o->m4c, &t, &out2) &&
                        t > 0.0f && minT > t)
                        minT = t;
                }
            }
            cAvatar_s00d2_7a70* avatar = NounManager_s00d2_7a70()->GetAvatar();
            if (avatar) {
                float v = minT;
                float lo = avatar->mBody.GetMinDistance();
                float hi = m17c;
                v = Clamp(v, lo, hi);
                mP1.x = mA0.x + dir.x * v;
                mP1.y = mA0.y + dir.y * v;
                mP1.z = mA0.z + dir.z * v;
            }
        }
        m48 = mP1;
        mCamPos = mP1;
        return;
    }

    if (fabs(mEC) > kEpsilon) {
        float inv = 1.0f / (float)sqrt((double)(mAnchor.x * mAnchor.x + mAnchor.y * mAnchor.y + mAnchor.z * mAnchor.z + 1e-8f));
        Vec3_s00d2_7a70 n;
        n.x = mAnchor.x * inv; n.y = mAnchor.y * inv; n.z = mAnchor.z * inv;
        Vec3_s00d2_7a70 d;
        d.x = mAnchor.x - mCamPos.x;
        d.y = mAnchor.y - mCamPos.y;
        d.z = mAnchor.z - mCamPos.z;
        Vec3_s00d2_7a70 r;
        RotateAroundAxis(&r, &d, &n, mEC);
        mCamPos.x = mAnchor.x - r.x;
        mCamPos.y = mAnchor.y - r.y;
        mCamPos.z = mAnchor.z - r.z;
    }
    if (fabs(mF0) > kEpsilon) {
        float p = mF0 + mFC;
        // The original keeps the anchor-minus-campos differences and their squares on the
        // x87 stack (fsub/fmul/faddp, no float rounding), squared in the order
        // (dx*dx + dz*dz) + dy*dy before fsqrt.
        float len = VecDistance(mAnchor, mCamPos);
        Vec3_s00d2_7a70 d;
        d.x = mAnchor.x - mCamPos.x;
        d.y = mAnchor.y - mCamPos.y;
        d.z = mAnchor.z - mCamPos.z;
        if (fabs(p - GetPitch(p, len)) < kEpsilon) {
            Vec3_s00d2_7a70 c;
            c.x = d.y * mCamPos.z - d.z * mCamPos.y;
            c.y = d.z * mCamPos.x - mCamPos.z * d.x;
            c.z = mCamPos.y * d.x - d.y * mCamPos.x;
            Vec3_s00d2_7a70 nrm;
            normalized_safe(&nrm, &c);
            Vec3_s00d2_7a70 r;
            RotateAroundAxis(&r, &d, &nrm, -mF0);
            mCamPos.x = mAnchor.x - r.x;
            mCamPos.y = mAnchor.y - r.y;
            mCamPos.z = mAnchor.z - r.z;
        }
    }
    if (flag) {
        float zoom = mF4;
        if (fabs(zoom) > kEpsilon) {
            Vec3_s00d2_7a70 d;
            d.x = mAnchor.x - mCamPos.x;
            d.y = mAnchor.y - mCamPos.y;
            d.z = mAnchor.z - mCamPos.z;
            float len = (float)sqrt((double)(d.z * d.z + (d.y * d.y + d.x * d.x)));
            if (len > kEpsilon) {
                float scale = (zoom + len) / len;
                mCamPos.x = mAnchor.x - d.x * scale;
                mCamPos.y = mAnchor.y - d.y * scale;
                mCamPos.z = mAnchor.z - d.z * scale;
            }
        }
    }
}
}  // namespace SP

// @ 0x00d28300
void cFreeCamera::Update(float dt)
{
    mDeltaTime = dt;
    cPlanetModel_s00d2_7a70* pm = PlanetModel_s00d2_7a70();
    if (!pm) return;
    if (!IsGameRunning()) return;

    if (GameInputManager_s00d2_7a70()->IsKeyDown(0x16)) {
        Vec3_s00d2_7a70 pos;
        GetTerrain()->ProjectPosition(pos, 1, gDefaultDir);
        if (pos.y * pos.y + pos.z * pos.z + pos.x * pos.x > 0.0f) {
            Vec3_s00d2_7a70 d = pos - mAnchor;
            float s = mSpeed * mDistance2;
            Vec3_s00d2_7a70 d2 = d;
            Quat buf;
            Vec3_s00d2_7a70* n = normalized_safe((Vec3_s00d2_7a70*)&buf, &d);
            Vec3_s00d2_7a70 step;
            step.x = n->x * s; step.y = n->y * s; step.z = n->z * s;
            if (d2.x * d2.x + d2.z * d2.z + d2.y * d2.y > step.x * step.x + step.z * step.z + step.y * step.y) {
                d.x = mAnchor.x + step.x;
                d.y = mAnchor.y + step.y;
                d.z = mAnchor.z + step.z;
            } else {
                d.x = mAnchor.x + d2.x;
                d.y = mAnchor.y + d2.y;
                d.z = mAnchor.z + d2.z;
            }
            Vec3_s00d2_7a70* p = pm->SnapToSurface((Vec3_s00d2_7a70*)&buf, &d, 0);
            mPos = *p;
            Quat* q = pm->SurfaceOrientation(&buf, &d, &mOrient);
            mOrient = *q;
        }
    }

    cGameInputManager_s00d2_7a70* gim = GameInputManager_s00d2_7a70();
    if (!gim) return;
    float a = 0.0f, c = 0.0f, b = 0.0f, d = 0.0f;
    if (gim->IsKeyDown(0x10)) a = -1.0f;
    if (gim->IsKeyDown(0x11)) a = a + 1.0f;
    if (gim->IsKeyDown(1)) b = -1.0f;
    if (gim->IsKeyDown(2)) b = b + 1.0f;
    if (gim->IsKeyDown(3)) c = 1.0f;
    if (gim->IsKeyDown(4)) c = c - 1.0f;
    if (gim->IsKeyDown(0x12)) d = dt * -3.0f;
    float nd;
    if (gim->IsKeyDown(0x13)) nd = dt * 3.0f + d;
    else nd = d;
    float v = nd + mDistance;
    const float& r = Max(v, mMinDistance);
    mDistance = r;
    mDistance2 = r;
    mYaw = a * kDeg2Rad_s00d2_7a70 + mYaw;
    mPitch = Clamp(mPitch, mMinPitch, mMaxPitch);
    if (c != 0.0f || b != 0.0f) {
        float half = mRollAngle * 0.5f;
        float sn = (float)sin((double)half);
        Quat q;
        q.x = sn * gRotAxisX;
        q.y = sn * gRotAxisY;
        q.z = sn * gRotAxisZ;
        q.w = (float)cos((double)half);
        Quat qm;
        Vec3_s00d2_7a70 dir;
        dir.x = c; dir.y = b; dir.z = 0.0f;
        Vec3_s00d2_7a70 rot;
        Vec3_s00d2_7a70* rp = QuatRotate(&rot, &dir, QuatMultiply(&qm, &mRot, &q));
        Vec3_s00d2_7a70 rv = *rp;
        float s2 = mSpeed * mDistance2;
        Quat tmpq;
        Vec3_s00d2_7a70* n = normalized_safe((Vec3_s00d2_7a70*)&tmpq, &rv);
        float nx = n->x * s2, ny = n->y * s2, nz = n->z * s2;
        mPos.x = mAnchor.x - nx;
        mPos.y = mAnchor.y - ny;
        mPos.z = mAnchor.z - nz;
        Vec3_s00d2_7a70* p = pm->SnapToSurface((Vec3_s00d2_7a70*)&tmpq, &mPos, 0);
        mPos = *p;
        Quat* qo = pm->SurfaceOrientation(&tmpq, &mPos, &mOrient);
        mOrient = *qo;
    }
}
