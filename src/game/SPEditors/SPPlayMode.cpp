// src/game/SPEditors/SPPlayMode.cpp -- migrated from slice(s) s0062da00, s0062e7e0, s0062bb40, s0062abd0, s00629c50, s00628d50, s00627d50 by tools/migrate/rewrite.py
// Object file: SPEditors/SPPlayMode.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Audio/FactoryBinarySampleData.h"
#include "SP/cSPPlayModeAnimation.h"
#include "SP/cSPPlayModeSubModeAction.h"
#include "cSPVector3.h"
#include "SP/cAnimatingCreature.h"
#include "SP/cAppModeEditorBase.h"
#include "SP/cCreatureCameraBase.h"
#include "SP/cCreatureCameraDepends.h"
#include "SP/cSPEditorAnimatedCreatureManager.h"
#include "SP/cICameraController.h"
#include "cSPBoundingBox.h"
#include "SP/cSPPlayMode.h"
#include "SP/cSPPlayModeUI.h"
#include "cSPQuaternion.h"
#include "SP/cTexturePreload.h"
#include "SP/tAvatarData.h"
#include <new>
#include <string.h>
#include <math.h>
#include <float.h>
#include <intrin.h>
#include "EA/Audio/ISystem.h"
#include "SP/cSPPlayModeBGMgr.h"
#include "SP/cILightingWorld.h"
#include "SP/cSPPlayModeAnimLoadInfo.h"
#include "SP/cSPPlayModeAnimPanelInfo.h"
#include "SP/cString.h"

// ---- items of slice s00627d50 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);
namespace SP {
struct ISubMode {
    PV4 PV2 PV
    virtual bool OnMouseUp(int a, float b, float c, int d);   // +0x1c
    virtual bool OnMouseMove(float a, float b, int c);        // +0x20
    virtual bool OnKeyDown(int a, int b);                     // +0x24
    virtual bool OnKeyUp(int a, int b);                       // +0x28
};
}
namespace SP {
struct IAnimator {   // cSPPlayModeAnimation (vtable at +0)
    PV2 PV
    virtual float PlayAnim(unsigned creatureId, unsigned animId, int a, int b, int c);   // +0x0c
    void ResetCurAnimWindow();    // 0x62e7a0
    void UpdatePageCount();       // 0x62e600
};
}
namespace SP {
struct cSPPlayModeAnimation_s0062_7d50 : IAnimator {
    char data[0x8c - 4];
};
}
namespace SP {
struct IEventInfo {
    void Fire(int arg);           // 0x59aea0 (cSPEditorAnimatedEventInfo ctor)
};
}
namespace SP {
struct ICreatureT {
    PV16 PV8 PV4 PV
    virtual int QueryPart(char* buf, int n, int h, void* pQuery, int z);   // +0x74
    char padC[0x17c - 4];
    int* mp17c;                   // +0x17c
};
}
namespace SP {
struct cCreatureManager {
    ICreatureT* GetCreature(unsigned id);              // 0x59ca70
    IEventInfo* GetCreatureStructure(unsigned id);     // 0x59cac0
};
}
namespace SP {
struct tElem48 {
    unsigned mId;
    char pad[0x30 - 4];
};
}
namespace SP {
struct tEditorState {
    char pad[0x360];
    cCreatureManager* mpManager;   // +0x360
    unsigned mCreatureId;          // +0x364
    char pad2[0x36c - 0x368];
    tElem48* mpVecBegin;           // +0x36c
    tElem48* mpVecEnd;             // +0x370
    char pad3[0x378 - 0x374];
    float mHeightOffsetDummy;
};
}
namespace SP {
struct cSPPlayModeUI_s0062_7d50 {
    void* FindEditorUIWindow(unsigned id);   // 0x634e40
};
}
namespace SP {
namespace EA {
namespace Random {
class RandomLinearCongruential {
public:
    unsigned mnSeed;
    unsigned RandomUint32Uniform(unsigned n);
};
}
}
}
namespace SP {
extern EA::Random::RandomLinearCongruential sMathRandomA;   // 0x1601760
}
namespace SP {
class cSPPlayMode_s0062_7d50 {
public:
    char pad0[0x0c];
    cSPPlayModeUI_s0062_7d50* mpUI;                   // +0x0c
    char pad1[0x4e - 0x10];
    unsigned char mBabyPhotoMode[3];       // +0x4e
    char pad2[0xc8 - 0x51];
    ISubMode* mSubModes[4];                // +0xc8
    char pad3[0x3588 - 0xd8];
    cSPPlayModeAnimation_s0062_7d50 mAnimation;       // +0x3588
    tEditorState* mpState;                 // +0x3614
    char pad4[0x36d0 - 0x3618];
    unsigned char mLevel;                  // +0x36d0
    char pad5[3];
    unsigned mLastEnvAnim;                 // +0x36d4
    int mBabyAnimIds[3];                   // +0x36d8

    unsigned char OnMouseUp(int a, float b, float c, int d);   // 0x628520
    unsigned char OnMouseMove(float a, float b, int c);        // 0x628570
    unsigned char OnKeyUp(int a, int b);                       // 0x6285c0
    static bool __stdcall IsWalkTypeAnim(unsigned id);         // 0x628610
    unsigned GetRandomEnvironmentReactionAnim();               // 0x6286a0
    int FindFreeBabyAnimSlot();                                // 0x628500
    int FindBabyAnimSlot(int id);                              // 0x628720
    unsigned char GetBabyPhotoMode(int id);                    // 0x628750
    float SetMomCelebrationAnim(bool* pOut);                   // 0x628780
    float SetMomCrouchAnimation();                             // 0x628830
    float SetBabyCrouchAnimation(unsigned creatureId);         // 0x628860
    void SetAllBabyPhotoModes(bool b);                         // 0x6288a0
    void ResetExpansionAnimWindow();                           // 0x6288f0
    float GetHeightOffset();                                   // 0x628a40
    int GetMouthPartIdx();                                     // 0x628a80
    unsigned char OnKeyDown(int key, int flag);                // 0x628af0
    void W6288d0(bool b);                                      // 0x6288d0
    bool W628940();                                            // 0x628940
};
}
namespace SP {
struct cResetable {
    char pad[0x1f];
    bool mFlagA;    // +0x1f
    bool mFlagB;    // +0x20
    char pad2[0x34 - 0x21];
    float mValueA;  // +0x34
    float mValueB;  // +0x38
    void Reset();
};
}
namespace SP {
struct cSPPlayModeAnimation2 : cSPPlayModeAnimation_s0062_7d50 {
    void FUN_0062ebe0();
    void FUN_0062ec30();
};
}
namespace SP {
void __cdecl FUN_00809db0(int a, void* b);
}
namespace SP {
extern char gUnknown1522480;
}
namespace SP {
struct cSubObj3618 {
    bool FUN_0062f6c0();
};
}
namespace SP {
struct Quat4 {
    float x, y, z, w;
    Quat4(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {}
};
}
namespace SP {
struct cTexturePreload_s0062_7d50 {
    virtual void AddRef();
    virtual void Release();
    char pad[0x34 - 4];
    cTexturePreload_s0062_7d50(int a);                              // 0x7b07e0
    void PreloadTextureList(const unsigned* pKey);       // 0x7b1e90
};
}
namespace SP {
struct cPreloadOwner {
    char pad[0x94];
    cTexturePreload_s0062_7d50* mpPreload;   // +0x94
    void EnsurePreload();
};
}
namespace SP {
struct cAppModeEditorBaseT {
    char pad[0x3614];
    tEditorState* mpState;
    void SendButtonEventToBabies(int arg);
};
}
// ---- items of slice s00627d50 end

// ---- items of slice s00628d50 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float gAngleRef; // 0x15f6e6c (opaque constant block)
extern const float gTwo;       // 0x1470f1c
extern const float gMs;        // 0x13f9428 (0.001f)
extern const float gOne;       // 0x15f6de4
extern const float gAngleScale;// 0x15f6ee4
extern const float gA, gB, gC; // 0x1522250, 0x13fe0e4, 0x15224b0
struct V3 {
  float x, y, z;
  V3() {}
  V3(float a, float b, float c) : x(a), y(b), z(c) {}
  V3(const V3& o) : x(o.x), y(o.y), z(o.z) {}
  V3& operator=(const V3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
inline V3 operator-(const V3& a, const V3& b) { return V3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline V3 operator-(const V3& a) { return V3(-a.x, -a.y, -a.z); }
extern const V3 gUpAxis;      // 0x15f6ee8
namespace EA {
namespace Audio {
struct ISystem_s0062_8d50 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
  virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void* Notify(); };
}
}
namespace EA {
namespace Audio {
ISystem_s0062_8d50* GetSystemAT();
}
}
void KillSetiEffects(uint32_t id, void* sys);   // SP::cSPUISpace::KillSetiEffects (cdecl)
struct Animator {
  virtual void v0(); virtual void v1(); virtual void v2();
  virtual float Play(uint32_t creature, uint32_t anim, int a, int b, int c);  // +0x0c
};
struct Baby {
  uint32_t id;
  uint8_t pad0[0x14];
  uint8_t b18;      // +0x18
  uint8_t spawned;  // +0x19
  uint8_t b1a;      // +0x1a
  int8_t state;     // +0x1b
  int8_t callState; // +0x1c
  uint8_t pad1[3];
  float t20;        // +0x20
  float timer;      // +0x24
  float timer2;     // +0x28
  uint8_t pad2[4];
};
struct Creature {
  virtual void v0(); virtual void v1();
  virtual uint32_t A(uint32_t a, int b);      // +0x08
  virtual void B(uint32_t h, int b);          // +0x0c
  virtual void v4(); virtual void v5();
  virtual void C(uint32_t h);                 // +0x18
  virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
  virtual void v12(); virtual void v13();
  virtual void D(uint32_t h, float f);        // +0x38
  virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
  virtual void v20(); virtual void v21();
  virtual void F(uint32_t* a, uint32_t* b, uint32_t* c, int d);  // +0x58
  virtual void v23();
  virtual float E(uint32_t h);                // +0x60
  bool IsOrientIdleAnim(uint32_t anim);   // 0x00a027a0 (equiv t2)
};
struct CreatureStruct {
  uint32_t pad0[2];
  Creature* anim;     // +0x08
  uint32_t pad1[(0x48 - 0x0c) / 4];
  float angle;        // +0x48
  float f4c;          // +0x4c
  float f50;          // +0x50
};
struct RandomLinearCongruential_s0062_8d50 {
  uint32_t seed;
  void SetSeed(uint32_t s);  // 0x00936090 (RandomLinearCongruential::SetSeed)
  uint32_t RandomUint32Uniform(uint32_t n);
};
struct DanceSub { bool IsDancingAnim(uint32_t anim, int flag); };
struct ActionSub { float SetIdleAnimation(Creature* c, uint32_t id, int a, int b); };
struct BabyVec {
  Baby* mpBegin;
  Baby* mpEnd;
  uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
  int ssize() const { return (int)(mpEnd - mpBegin); }
  uint32_t IDAt(uint32_t i) {
    uint32_t n = size();
    Baby* b = mpBegin;
    if (n == 0) return 0xffffffff;
    if (i < n) return b[i].id;
    return b[0].id;
  }
  Baby* begin() { return mpBegin; }
  Baby* end() { return mpEnd; }
  Baby& operator[](uint32_t i) { return *(i + mpBegin); }
};
struct Flagged { uint32_t pad; uint32_t flags; };
struct CreatureMgr {
  Creature* GetCreature(uint32_t id);   // 0x0059ca70 (equiv t2)
  void GetCreaturePosition(uint32_t id, V3* out);   // 0x0059d110 (equiv t2)
  CreatureStruct* GetCreatureStructure(uint32_t id);
  bool IsPlayingAnimation(uint32_t id);   // 0x0059cd20 (equiv t2)
};
struct Editor {
  uint32_t pad0[0x2b];
  Flagged* flagged;            // +0xac
  uint32_t pad1[(0x360 - 0xb0) / 4];
  CreatureMgr* mgr;            // +0x360
  uint32_t momId;              // +0x364
  uint32_t pad2;
  BabyVec babies;              // +0x36c
  void FUN_00574110(uint32_t id, int a, float b, float c);
  void FUN_005dbbb0(int v);
};
struct SubMode { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
  virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
  virtual bool HandleButton(uint32_t id); };   // +0x2c
struct ButtonState {
  bool FUN_0062f7f0(int id);
  bool FUN_0062f6c0();
};
class cSPPlayMode {
 public:
  uint32_t pad00[8];
  uint8_t mFlag20;                          // +0x20
  uint8_t pad20[3];
  uint32_t mCrouchBaby;                     // +0x24
  uint32_t pad28[5];
  float mMomCrouchChangeTime;               // +0x3c
  float mBabyCelebratingChangeTime[3];      // +0x40
  uint32_t pad1[(0xc8 - 0x4c) / 4];
  SubMode* mSubModes[4];                    // +0xc8
  uint32_t pad2[(0x3588 - 0xd8) / 4];
  Animator mAnimator;                       // +0x3588
  uint32_t pad3[(0x3614 - 0x358c) / 4];
  Editor* mEditor;                          // +0x3614
  ButtonState mButtons;                     // +0x3618
  uint8_t pad4[0x36d0 - 0x3619];
  uint8_t mNumBabies;                       // +0x36d0

  bool HandleButton(int id);
  void SetMomToFaceBaby(uint32_t baby);
  uint32_t GetLatestBabyID();
  int GetLatestBabyIndex();
  uint32_t GetAnimatedBabyIndex(uint32_t id);
  uint32_t FUN_006291d0(uint32_t index);
  void SetAllBabySitUp();
  uint32_t GetRandomEnvironmentReactionAnim();
  void SendButtonEventToBabies(bool b);
  void SetAllOtherBabiesToIdle(uint32_t id, uint32_t anim, float f);
  void SetBabySpawned(uint32_t index, uint8_t v);
  void SetBabySocialCallState(uint32_t id, uint32_t anim, float f);
  float SetBabyCelebrationAnim();
  int GetMouthPartIdx();
  bool FUN_00629590();
  void ForceBabiesToIdle(int param);
  void FUN_006298b0(uint32_t exceptId);
  void FUN_00629960(int dt);
  bool BabiesReachedTargetAngle();
  void SetAllBabyRotateSpeeds(float speed);
  float FUN_00629bd0(CreatureStruct* s);
};
V3 Fn_0059aed0(const V3& a, const void* c);
bool Fn_0059ab70(V3* v);
float Fn_0069b760(const V3& a, const V3& b, const float* c);
float Fn_009b3c10(float a, float b);
template <class T> inline const T& MinRef(const T& a, const T& b) { return (b < a) ? b : a; }
namespace __equiv_ann1 {
struct DanceSub {
    void IsDancingAnim();   // 0x0063b570 (equiv t2)
};
}
// ---- items of slice s00628d50 end

// ---- items of slice s00629c50 begin (TODO(rewrite): local stubs, replace by canonical classes)
static inline void** Vt(void* p) { return *(void***)p; }
static inline void Release2(void* p) { if (p) ((void(__thiscall*)(void*))Vt(p)[2])(p); }
struct cSPPlayMode_s0062_9c50 {
  char pad[0x3620];
  bool HasActivePath(int creatureID);
  uint8_t OnMouseDown(void* a, void* b, void* c, void* d);
  void SetAllBabySitState();
};
void* __cdecl FUN_0062cb20(const float* p, float a, int b, float c);   // 0x62cb20
void  __cdecl FUN_0062cb90();                                        // 0x62cb90
void* __cdecl PropertyManager();                                     // 0x67dd? 
void* __cdecl ModelManager();                                        // 0x67dd80
void  __cdecl SetAllBabySitUp(cSPPlayMode_s0062_9c50* m);                       // 0x628? 
uint32_t __cdecl GetMouthPartIdx(cSPPlayMode_s0062_9c50* m);                    // 0x628a80
void  __cdecl cSPEditorAnimMgr_GetCreature(char* cm, void* id);      // 0x59ca70
struct Mgr029 {
  void* Find(int id);        // 0x9cab60
  void  Remove(void* p);     // 0x9cb460
};
void SetBabySitState(cSPPlayMode_s0062_9c50* m, uint32_t index);
void WakeupCreature(cSPPlayMode_s0062_9c50* m);
// ---- items of slice s00629c50 end

// ---- items of slice s0062abd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* CALLEE_572400(...);
extern "C" void CALLEE_62ffd0(...);
extern float gHalf;              // 0x1471064
typedef void  (__thiscall *TF0)(void*);
typedef void  (__thiscall *TF1)(void*, int);
typedef void  (__thiscall *TF2)(void*, int, int);
struct AnimRef {                 // AutoRefCount-ish: slot1 = Release
  virtual void s0();
  virtual void s1();
  virtual void s2();
};
struct Vector12 {                // eastl vector (3 pointers)
  void* a; void* b; void* c;
  Vector12() : a(0), b(0), c(0) {}
  ~Vector12();
};
struct cSPPlayModeAnimation {
  virtual void slot0();
  void* mEditorBase;             // 0x4
  unsigned int mCurrAnimID;      // 0x8
  Vector12 mAnimPanelInfo;       // 0xc
  int mF18;                      // 0x18
  int mF1C;                      // 0x1c
  int mF20;                      // 0x20
  int mF24;                      // 0x24
  int mF28;                      // 0x28
  AnimRef* pTooltip[24];         // 0x2c

  cSPPlayModeAnimation();
  ~cSPPlayModeAnimation();
};
struct HkWorldObject { void removeReference(); };
struct Bp { void FUN_01083110(int a); };
// ---- items of slice s0062abd0 end

// ---- items of slice s0062bb40 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec  { void erase(void* first, void* last); };
struct VecB { void DoInsertValue(void* dst, void* src, int n); };
struct CreatureMgr_s0062_bb40 {
  void* GetCreature(int idx);
  void* GetCreatureStructure(int idx);
  int   RunSkinPaintOnEditorModel(int a, int b);
  void  DestroyAnimatedCreature(int a, int b);
};
struct PM {
  void FUN_0062bb40(int a, int b);   // @ 0x0062bb40
  void FUN_0062bec0();               // @ 0x0062bec0
  void FUN_0062bdb0();               // @ 0x0062bdb0
  void FUN_0062bf10(int a);          // @ 0x0062bf10
  void Stop();                       // @ 0x0062c340
  void Update(int a);                // @ 0x0062c550
  bool FUN_0062c7e0(int idx, int a); // @ 0x0062c7e0
  void FUN_0062c910();               // @ 0x0062c910
  void FUN_0062c990(int id);         // @ 0x0062c990
  int  GetLatestBabyID();
  void SetMomToFaceBaby(int id);
  void SetBabyIdleAnim(int id);
  bool IsEventForBaby(int id);
};
// ---- items of slice s0062bb40 end

// ---- items of slice s0062da00_ui begin (TODO(rewrite): local stubs, replace by canonical classes)
struct AnimLoadInfo {
  uint32_t pad[2];
  uint32_t mAnimID;        // +0x08
  uint32_t mAnimBabyID;    // +0x0c
  float mAnimBabySpeed;    // +0x10
  float mAnimBabyDelay;    // +0x14
};
struct LoadInfoVector {
  AnimLoadInfo** mpBegin;
  AnimLoadInfo** mpEnd;
  AnimLoadInfo** mpCapacity;
  uint32_t mAllocator;
  uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
};
struct AnimPanelInfo {
  uint32_t pad[5];
  LoadInfoVector mAnimLoadInfo;     // +0x14
};
struct PanelVector {
  AnimPanelInfo** mpBegin;
  AnimPanelInfo** mpEnd;
  AnimPanelInfo** mpCapacity;
  uint32_t mAllocator;
  uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
};
struct IWindow {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
  virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
  virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
  virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
  virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
  virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
  virtual void v30();
  virtual void SetFlag(int flag, bool value);          // +0x7c
  virtual void SetCaption(const wchar_t* text);        // +0x80
  virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37();
  virtual void v38(); virtual void v39(); virtual void v40(); virtual void v41(); virtual void v42();
  virtual void v43(); virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
  virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51(); virtual void v52();
  virtual void v53(); virtual void v54(); virtual void v55(); virtual void v56(); virtual void v57();
  virtual void v58(); virtual void v59(); virtual void v60(); virtual void v61(); virtual void v62();
  virtual void v63(); virtual void v64();
  virtual void SetWinProc(void* proc);                 // +0x104
};
struct cSPPlayModeUI {
  IWindow* FindPlayModeUIWindow(uint32_t id);
  void SetUIGroupVisible(uint32_t group, bool visible);
};
struct UITooltip {
  virtual void AddRef();
  virtual void Release();
  uint32_t pad[25];
  UITooltip(const wchar_t* name, uint32_t id, const wchar_t* text, const float* pos, int a,
            const void* b, int c);
};
struct AnimController;   // object at creature+0x184
struct AnimSlot;
struct AnimatingCreature {
  virtual void v0(); virtual void v1();
  virtual uint32_t CreateAnim(uint32_t anim, int a);     // +0x08
  virtual void SetAnimParam(uint32_t h, uint32_t v);     // +0x0c
  virtual void v4(); virtual void v5();
  virtual void Start(uint32_t h);                        // +0x18
  virtual void v7();
  virtual void SetLooping(uint32_t h, int v);            // +0x20
  virtual void SetBlend(uint32_t h, float v);            // +0x24
  virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
  virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
  virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
  virtual float GetAnimLength(uint32_t anim);            // +0x60
  uint32_t pad[(0x184 - 4) / 4];
  AnimController* mController;      // +0x184
  uint32_t mFadeOutHandle;          // +0x188
  uint32_t mCurHandle;              // +0x18c
  bool IsMoveIdleAnim(uint32_t anim);
  bool FUN_00a02800(uint32_t anim);
};
struct AnimController {
  void FUN_00a00f90(void* slot, int v);
  void FUN_00a01f10(uint32_t handle, int v);
};
struct AnimSlot { uint32_t pad[0x36]; uint32_t mAnimID; };   // +0xd8
void* FUN_009ff6f0(AnimController* ctl, uint32_t handle);
struct CreatureStructure {
  uint32_t pad[2];
  AnimatingCreature* mCreature;   // +0x08
  void FUN_007cd950(uint32_t anim);
};
struct EditorBase { uint32_t pad[0x360 / 4]; struct AnimMgr* mgr; };
struct AnimMgr { CreatureStructure* GetCreatureStructure(uint32_t id); };
class cSPPlayModeAnimation_s0062_da00__ui {
 public:
  void* vftable;
  EditorBase* mEditorBase;       // +0x04
  uint32_t mCurrAnimID;          // +0x08
  PanelVector mAnimPanelInfo;    // +0x0c
  uint32_t pad1c;                // +0x1c
  uint32_t mPageCount;           // +0x20
  uint32_t mViewMode;            // +0x24
  cSPPlayModeUI* mUI;            // +0x28
  UITooltip* pTooltip[24];       // +0x2c

  __declspec(noinline) int GetAnimCount();  // 0x0062e4b0 (cSPPlayModeAnimation::GetAnimCount)
  bool GetExpansionAnimInfo(int buttonId, uint32_t* id, uint32_t* babyId, float* speed, float* delay);  // 0x0062e4f0 (cSPPlayModeAnimation::GetExpansionAnimInfo)
  bool IsExtraAnims();
  void UpdatePageCount();  // 0x0062e600 (cSPPlayModeAnimation::UpdatePageCount)
  void Activate();
  void ResetCurAnimWindow();  // 0x0062e7a0 (cSPPlayModeAnimation::ResetCurAnimWindow)
  float StartNewAnimation(uint32_t creatureId, uint32_t anim, bool flag, uint32_t param, uint32_t* outHandle);
};
// ---- items of slice s0062da00_ui end

// @ 0x00628610
namespace SP {
bool __stdcall cSPPlayMode_s0062_7d50::IsWalkTypeAnim(unsigned id)
{
    switch (id) {
    case 0x44828e9:
    case 0x4482906:
    case 0x4482911:
    case 0x4482918:
    case 0x448291f:
    case 0x4485a08:
    case 0x4485a0f:
    case 0x452b634:
    case 0x452b64a:
    case 0x452b651:
        return true;
    }
    return false;
}
}  // namespace SP







// @ 0x006286a0
namespace SP {
unsigned cSPPlayMode_s0062_7d50::GetRandomEnvironmentReactionAnim()
{
    unsigned anim;
    do {
        switch (sMathRandomA.RandomUint32Uniform(6)) {
        case 0:
            anim = 0x431df93;
            break;
        case 1:
            anim = 0x431df9a;
            break;
        case 2:
            anim = 0x431df9f;
            break;
        case 3:
            anim = 0x431dfa6;
            break;
        case 4:
            anim = 0x44d798c;
            break;
        case 5:
            anim = 0x44d7999;
            break;
        }
    } while (mLastEnvAnim == anim);
    mLastEnvAnim = anim;
    return anim;
}
}  // namespace SP







// @ 0x00628720
namespace SP {
int cSPPlayMode_s0062_7d50::FindBabyAnimSlot(int id)
{
    unsigned i = 0;
    int* p = mBabyAnimIds;
    do {
        if (*p == id)
            return i;
        ++i;
        ++p;
    } while (i < 3);
    return -1;
}
}  // namespace SP







// @ 0x00628750
namespace SP {
unsigned char cSPPlayMode_s0062_7d50::GetBabyPhotoMode(int id)
{
    unsigned i = 0;
    int* p = mBabyAnimIds;
    do {
        if (*p == id)
            return mBabyPhotoMode[i];
        ++i;
        ++p;
    } while (i < 3);
    return 0;
}
}  // namespace SP







// @ 0x00628810
namespace SP {
void cResetable::Reset()
{
    mFlagA = false;
    mFlagB = false;
    mValueA = 0.0f;
    mValueB = 0.0f;
}
}  // namespace SP







// @ 0x00628860
namespace SP {
float cSPPlayMode_s0062_7d50::SetBabyCrouchAnimation(unsigned creatureId)
{
    return mAnimation.PlayAnim(creatureId, 0x43736cd, 0, 1, 0);
}
}  // namespace SP







// @ 0x006288d0
namespace SP {
void cSPPlayMode_s0062_7d50::W6288d0(bool b)
{
    if (b) {
        ((cSPPlayModeAnimation2*)&mAnimation)->FUN_0062ebe0();
        return;
    }
    ((cSPPlayModeAnimation2*)&mAnimation)->FUN_0062ec30();
}
}  // namespace SP







// @ 0x006288f0
namespace SP {
void cSPPlayMode_s0062_7d50::ResetExpansionAnimWindow()
{
    mAnimation.ResetCurAnimWindow();
    mAnimation.UpdatePageCount();
}
}  // namespace SP







// @ 0x00628910
namespace SP {
void __cdecl W628910()
{
    FUN_00809db0(0, &gUnknown1522480);
}
}  // namespace SP







// @ 0x00628940
namespace SP {
bool cSPPlayMode_s0062_7d50::W628940()
{
    return ((cSubObj3618*)((char*)this + 0x3618))->FUN_0062f6c0() == 0;
}
}  // namespace SP







// @ 0x00628970
namespace SP {
Quat4* ForceQuat(void* p, float a, float b, float c, float d)
{ return new (p) Quat4(a, b, c, d); }
}  // namespace SP







// @ 0x006289a0
namespace SP {
void cPreloadOwner::EnsurePreload()
{
    if (!mpPreload) {
        cTexturePreload_s0062_7d50* pNew = new ("Editor", 0, 0, 0, 0) cTexturePreload_s0062_7d50(-1);
        cTexturePreload_s0062_7d50* pOld = mpPreload;
        if (pNew != pOld) {
            if (pNew)
                pNew->AddRef();
            mpPreload = pNew;
            if (pOld)
                pOld->Release();
        }
        unsigned key[3] = { 0x7518573e, 0x510a95b, 0x40464100 };
        mpPreload->PreloadTextureList(key);
    }
}
}  // namespace SP







// @ 0x00628ca0
namespace SP {
void cAppModeEditorBaseT::SendButtonEventToBabies(int arg)
{
    tEditorState* st = mpState;
    cCreatureManager* mgr = st->mpManager;
    unsigned id = st->mCreatureId;
    if (mgr->GetCreatureStructure(id))
        mgr->GetCreatureStructure(id)->Fire(arg);
    st = mpState;
    int n = (int)(st->mpVecEnd - st->mpVecBegin);
    if (n != 0) {
        int off = 0;
        do {
            unsigned eid = *(unsigned*)((char*)st->mpVecBegin + off);
            if (mgr->GetCreatureStructure(eid))
                mgr->GetCreatureStructure(*(unsigned*)((char*)st->mpVecBegin + off))->Fire(arg);
            off += 0x30;
            --n;
        } while (n != 0);
    }
}
}  // namespace SP






// @ 0x00628d50
bool cSPPlayMode::HandleButton(int id)
{
  bool result = false;
  if (mButtons.FUN_0062f7f0(id)) {
  EA::Audio::ISystem_s0062_8d50* sys = EA::Audio::GetSystemAT();
  void* r0 = sys ? sys->Notify() : 0;
  KillSetiEffects(0xa03e74b2, r0);
  Flagged* f = mEditor->flagged;
  if (f) {
    if (mButtons.FUN_0062f6c0()) f->flags |= 1; else f->flags &= ~1u;
  }
  bool b = mButtons.FUN_0062f6c0();
  SendButtonEventToBabies(b);
  if (id == 0x445b018 || id == 0x445b318 || id == 0x445b340 || id == 0x445b388) {
    uint32_t anim = GetRandomEnvironmentReactionAnim();
    mAnimator.Play(mEditor->momId, anim, 0, 1, 0);
    mAnimator.Play(mEditor->momId, 0x4330667, 1, 0, 0);
    mEditor->FUN_00574110(0x70842ef6, -1, 1.0f, 0.0f);
    switch (id) {
      case 0x445b018: mEditor->FUN_005dbbb0(0); return true;
      case 0x445b318: mEditor->FUN_005dbbb0(1); return true;
      case 0x445b340: mEditor->FUN_005dbbb0(2); return true;
      case 0x445b388: mEditor->FUN_005dbbb0(3); break;
    }
  }
  return true;
  }
  for (int i = 0; i < 4; i++) result |= mSubModes[i]->HandleButton(id);
  return result;
}






// @ 0x00628f10
void cSPPlayMode::SetMomToFaceBaby(uint32_t baby)
{
  CreatureMgr* mgr = mEditor->mgr;
  mgr->GetCreature(baby);
  uint32_t mom = mEditor->momId;
  char* c = (char*)mgr->GetCreature(mom);
  V3 momPos, babyPos;
  mgr->GetCreaturePosition(mom, &momPos);
  mgr->GetCreaturePosition(baby, &babyPos);
  V3 up = -gUpAxis;
  V3 a = up;
  a = Fn_0059aed0(a, c + 0x10);
  if (!Fn_0059ab70(&a)) a = up;
  Fn_0069b760(babyPos - momPos, a, &gAngleRef);
  float ang = Fn_0069b760(babyPos - momPos, -gUpAxis, &gAngleRef);
  mgr->GetCreatureStructure(mom);
  mMomCrouchChangeTime = -ang;
}






// @ 0x00629110
uint32_t cSPPlayMode::GetLatestBabyID()
{
  Editor* e = mEditor;
  BabyVec& v = e->babies;
  int n = v.size();
  if (n == 0) return 0xffffffff;
  Baby* b = v.mpBegin;
  return b[n - 1].id;
}






// @ 0x00629150
int cSPPlayMode::GetLatestBabyIndex()
{
  Editor* e = mEditor;
  return e->babies.ssize() - 1;
}






// @ 0x00629180
uint32_t cSPPlayMode::GetAnimatedBabyIndex(uint32_t id)
{
  Editor* e = mEditor;
  BabyVec& v = e->babies;
  uint32_t n = v.size();
  Baby* b = v.mpBegin;
  for (uint32_t i = 0; i < n; i++, b++) {
    if (b->id == id) return i;
  }
  return 0xffffffff;
}






// @ 0x006291d0
uint32_t cSPPlayMode::FUN_006291d0(uint32_t index)
{
  Editor* e = mEditor;
  BabyVec& v = e->babies;
  uint32_t n = v.size();
  Baby* b = v.mpBegin;
  if (n == 0) return 0xffffffff;
  if (index < n) return b[index].id;
  return b[0].id;
}






// @ 0x00629220
void cSPPlayMode::SetAllBabySitUp()
{
  Editor* e = mEditor;
  BabyVec& v = e->babies;
  uint32_t n = v.size();
  for (uint32_t i = 0; i < n; i++) {
    Baby* b = &v[i];
    if (b->state >= 3 && b->state == 4) mAnimator.Play(b->id, 0x4079859, 0, 1, 0);
    v[i].state = 0;
    v[i].timer = 0.0f;
  }
}






// @ 0x006292b0
void cSPPlayMode::SetAllOtherBabiesToIdle(uint32_t id, uint32_t anim, float f)
{
  Editor* e = mEditor;
  BabyVec* pv = &e->babies;
  BabyVec& v = *pv;
  uint32_t idx = GetAnimatedBabyIndex(id);
  if (idx < v.size() && v[idx].state == 1) {
    v[idx].state = 2;
    Creature* c = mEditor->mgr->GetCreature(id);
    uint32_t h = c->A(anim, 0);
    c->B(h, 1);
    c->C(h);
    c->D(h, f);
    v[idx].timer = c->E(anim) * f * 0.5f;
  }
}






// @ 0x00629380
void cSPPlayMode::SetBabySpawned(uint32_t index, uint8_t value)
{
  BabyVec& v = mEditor->babies;
  if (index < v.size()) v[index].spawned = value;
}






// @ 0x006293d0
void cSPPlayMode::SetBabySocialCallState(uint32_t id, uint32_t anim, float f)
{
  Editor* e = mEditor;
  BabyVec& v = e->babies;
  uint32_t idx = GetAnimatedBabyIndex(id);
  if (idx < v.size() && v[idx].callState == 1) {
    Creature* c = e->mgr->GetCreature(id);
    uint32_t h = c->A(anim, 0);
    c->B(h, 1);
    c->C(h);
    c->D(h, f);
    v[idx].timer = c->E(anim) * f * 0.5f;
    if (GetMouthPartIdx() != -1) {
      v[idx].timer2 = f * 0.5f;
      v[idx].callState = 2;
    } else {
      v[idx].callState = 3;
    }
  }
}






// @ 0x006294e0
float cSPPlayMode::SetBabyCelebrationAnim()
{
  Editor* e = mEditor;
  Baby* b = e->babies.mpBegin;
  int latest;
  int n0 = (int)(e->babies.mpEnd - b);
  if (n0 == 0) latest = -1; else latest = b[n0 - 1].id;
  float result = 0.0f;
  if (latest != -1) {
    int n = (int)(e->babies.mpEnd - b);
    float t = mAnimator.Play(latest, 0x43736c5, 0, 1, 0);
    mBabyCelebratingChangeTime[n - 1] = t;
    mAnimator.Play(latest, 0x4330667, 1, 0, 0);
  }
  return result;
}






// @ 0x00629590
bool cSPPlayMode::FUN_00629590()
{
  bool result = false;
  if (mNumBabies != 0) {
    RandomLinearCongruential_s0062_8d50 rng;
    rng.SetSeed(0xffffffff);
    if (rng.RandomUint32Uniform(100) > 0x46) {
      uint32_t baby;
      if (mNumBabies == 1) {
        baby = FUN_006291d0(0);
      } else {
        do {
          uint32_t r = rng.RandomUint32Uniform(mNumBabies);
          BabyVec& v = mEditor->babies;
          uint32_t n = v.size();
          Baby* b = v.mpBegin;
          if (n == 0) baby = 0xffffffff;
          else if (r < n) baby = b[r].id;
          else baby = b[0].id;
        } while (baby == mCrouchBaby);
      }
      V3 momPos, babyPos;
      CreatureMgr* mgr = mEditor->mgr;
      mgr->GetCreaturePosition(mEditor->momId, &momPos);
      mgr->GetCreaturePosition(baby, &babyPos);
      float dz = momPos.z - babyPos.z;
      float dy = momPos.y - babyPos.y;
      float dx = momPos.x - babyPos.x;
      if (gTwo <= dz * dz + dy * dy + dx * dx) {
        SetMomToFaceBaby(baby);
        mCrouchBaby = baby;
        mFlag20 = 1;
        result = true;
      }
    }
  }
  return result;
}






// @ 0x006296e0
void cSPPlayMode::ForceBabiesToIdle(int param)
{
  uint32_t i = 0;
  bool flag = false;
  if (mNumBabies > 0) {
    int off = 0;
    float* p = (float*)&mBabyCelebratingChangeTime[0];
    do {
      Editor* e = mEditor;
      BabyVec& v = e->babies;
      uint32_t n = v.size();
      Baby* b = v.mpBegin;
      uint32_t id;
      if (n == 0) id = 0xffffffff;
      else if (i < n) id = *(uint32_t*)(off + (char*)b);
      else id = b[0].id;
      bool doIdle;
      if (param == -1) {
        flag = true;
        doIdle = true;
      } else {
        CreatureMgr* mgr = e->mgr;
        CreatureStruct* cs = mgr->GetCreatureStructure(id);
        uint32_t a, bb, c;
        if (mgr->IsPlayingAnimation(id) && (cs->anim->F(&a, &bb, &c, 0), (int)a == param)) {
          flag = true;
          doIdle = true;
        } else {
          doIdle = flag;
        }
      }
      if (doIdle) {
        mAnimator.Play(id, 0x4330667, 1, 1, 0);
        { BabyVec& w = mEditor->babies; if (i < w.size()) ((Baby*)(off + (char*)w.mpBegin))->spawned = 0; }
        *p = 0.0f;
        { BabyVec& w = mEditor->babies; if (i < w.size()) ((Baby*)(off + (char*)w.mpBegin))->b18 = 0; }
        { BabyVec& w = mEditor->babies; if (i < w.size()) ((Baby*)(off + (char*)w.mpBegin))->b1a = 0; }
      }
      p++;
      off += 0x30;
      i++;
    } while (i < mNumBabies);
  }
}






// @ 0x006298b0
void cSPPlayMode::FUN_006298b0(uint32_t exceptId)
{
  BabyVec& v = mEditor->babies;
  uint32_t n = v.size();
  for (uint32_t i = 0; i < n; i++) {
    uint32_t id = v[i].id;
    if (id != exceptId) {
      Creature* c = mEditor->mgr->GetCreature(id);
      ((ActionSub*)((char*)this + 0xd8))->SetIdleAnimation(c, id, 0, 0);
      mAnimator.Play(id, 0x4330667, 1, 0, 0);
    }
  }
}






// @ 0x00629960
void cSPPlayMode::FUN_00629960(int dt)
{
  BabyVec& v = mEditor->babies;
  uint32_t n = v.size();
  for (uint32_t i = 0; i < n; i++) {
    Baby* b = &v[i];
    if (b->b1a != 0) {
      if (v[i].t20 > 0.0f) v[i].t20 = v[i].t20 - (float)(uint32_t)dt * gMs;
      if (v[i].t20 < 0.0f) {
        Creature* c = mEditor->mgr->GetCreature(v[i].id);
        uint32_t anim;
        c->F(&anim, 0, 0, 0);
        if (!c->IsOrientIdleAnim(anim) &&
            !((DanceSub*)((char*)this + 0x11b0))->IsDancingAnim(anim, 1) &&
            !mEditor->mgr->IsPlayingAnimation(v[i].id)) {
          v[i].b1a = 0;
          v[i].b18 = 0;
          v[i].spawned = 0;
        }
      }
    }
  }
}






// @ 0x00629a90
bool cSPPlayMode::BabiesReachedTargetAngle()
{
  CreatureMgr* mgr = mEditor->mgr;
  uint8_t i = 0;
  while (i < mNumBabies) {
    uint32_t idx = i;
    uint32_t id = mEditor->babies.IDAt(idx);
    if (mgr->GetCreatureStructure(id)->angle != mMomCrouchChangeTime) return false;
    i++;
  }
  return true;
}






// @ 0x00629b30
void cSPPlayMode::SetAllBabyRotateSpeeds(float speed)
{
  CreatureMgr* mgr = mEditor->mgr;
  for (int i = 0; i < (int)mNumBabies; i++) {
    uint32_t id = mEditor->babies.IDAt(i);
    CreatureStruct* cs = mgr->GetCreatureStructure(id);
    cs->f4c = 2.5f;
    cs->f50 = speed;
  }
}






// @ 0x00629bd0
float cSPPlayMode::FUN_00629bd0(CreatureStruct* s)
{
  if (s) {
    float sa = s->angle;
    float d = Fn_009b3c10(mMomCrouchChangeTime - sa, gAngleScale);
    float k = gA * gB;
    float m = fabsf(d) * gC;
    return MinRef(m, k);
  }
  return gOne;
}





// @ 0x00629c50
void FUN_00629c50(cSPPlayMode_s0062_9c50* m)
{ (void)m; }





// @ 0x00629d90
void __stdcall FUN_00629d90(int arg1, int arg2)
{
  if (arg2 == -1) return;
  void* v = (*(Mgr029**)(arg1 + 0x17c))->Find(arg2);
  if (v == 0) return;
  if (*(void**)((char*)v + 0x8c)) {
    void* o = *(void**)((char*)v + 0x8c);
    ((void(__thiscall*)(void*, int))Vt(o)[3])(o, 1);
  }
  (*(Mgr029**)(arg1 + 0x17c))->Remove(v);
}





// @ 0x00629de0
void FUN_00629de0(cSPPlayMode_s0062_9c50* m)
{ (void)m; }





// @ 0x0062a1a0
void StopWalk(cSPPlayMode_s0062_9c50* m, void* a, int b)
{ (void)m; (void)a; (void)b; }





// @ 0x0062a230
void SetBabyPath(cSPPlayMode_s0062_9c50* m, uint32_t id, float x, float y, float z)
{
  char* begin = *(char**)((char*)m + 0x7c);
  char* end = *(char**)((char*)m + 0x80);
  uint32_t n = (uint32_t)((end - begin) >> 2);
  uint32_t i = 0;
  for (; i < n; ++i)
    if (*(int*)(*(char**)(begin + i * 4) + 0x1c) == (int)id) break;
  if (i >= n) return;
  char* c = *(char**)(begin + i * 4);
  char* data = *(char**)(c + 0x10);
  if (data == 0) return;
  if (((*(float*)(data + 0x38) != x) || (*(float*)(data + 0x3c) != y)) || z != 0.0f) {
    FUN_0062cb90();
    void* t = FUN_0062cb20(&x, 1.0f, 0, 0.5f);
    *(uint8_t*)((char*)t + 0x2a) = 1;
    (void)t;
  }
}





// @ 0x0062a360
bool cSPPlayMode_s0062_9c50::HasActivePath(int creatureID)
{
  cSPPlayMode_s0062_9c50* m = this;
  char* cm = *(char**)((char*)m + 0x3610);
  int n = (*(int*)(cm + 0x370) - *(int*)(cm + 0x36c)) / 0x30;
  char* begin = *(char**)(cm + 0x36c);
  int i = 0;
  while (*(int*)(*(char**)(begin + i * 4) + 0x1c) != creatureID) {
    ++i;
    if ((unsigned)i >= (unsigned)n) return false;
  }
  if ((unsigned)i < (unsigned)n) {
    char* c = *(char**)(begin + i * 4);
    if (*(float*)(c + 0x34) > 0.0f) return true;
    char* c0 = *(char**)begin;
    if (*(char*)(c0 + 0x24) != 0 && *(char*)(c + 0x24) != 0) return true;
  }
  return false;
}





// @ 0x0062a3d0
void PlayMode_Init(cSPPlayMode_s0062_9c50* m, void* a, uint8_t b)
{
  *(void**)((char*)m + 0x3624) = a;
  *(uint8_t*)((char*)m + 0x3628) = b;
}





// @ 0x0062a550
void FUN_0062a550(cSPPlayMode_s0062_9c50* m)
{ (void)m; }





// @ 0x0062a760
void WakeupCreature(cSPPlayMode_s0062_9c50* m)
{
  if (*(char*)((char*)m + 0x1f0) != 0) {
    void* ui = *(void**)((char*)m + 0x1f8);
    if (ui != 0) {
      ((void(__thiscall*)(void*))Vt(ui)[3])(ui);
      ui = *(void**)((char*)m + 0x1f8);
      if (ui != 0) {
        *(void**)((char*)m + 0x1f8) = 0;
        ((void(__thiscall*)(void*))Vt(ui)[1])(ui);
      }
    }
  }
  uint8_t b = *(uint8_t*)((char*)m + 0x1f1);
  *(void**)((char*)m + 0x200) = 0;
  *(float*)((char*)m + 0x1f4) = 0.0f;
  *(uint8_t*)((char*)m + 0x1f0) = 0;
  if (b > 1) {
    if (b == 3) { /* effect trigger; see partial.txt */ }
    *(uint8_t*)((char*)m + 0x1f1) = 0;
    *(int*)((char*)m + 0x1fc) = 0;
    SetAllBabySitUp(m);
  }
}





// @ 0x0062a7f0
uint8_t cSPPlayMode_s0062_9c50::OnMouseDown(void* a, void* b, void* c, void* d)
{
  cSPPlayMode_s0062_9c50* m = this;
  WakeupCreature(m);
  *(uint8_t*)((char*)m + 0x1f) = 0;
  *(uint8_t*)((char*)m + 0x20) = 0;
  *(uint32_t*)((char*)m + 0x34) = 0;
  *(uint32_t*)((char*)m + 0x38) = 0;
  uint8_t r = 0;
  int* p = (int*)((char*)m + 0xc8);
  for (int i = 4; i != 0; --i, ++p) {
    if (*p != 0) {
      uint8_t x = ((uint8_t(__thiscall*)(void*, void*, void*, void*, void*))Vt((void*)*p)[6])
                      ((void*)*p, a, b, c, d);
      r = (uint8_t)(r | x);
    }
  }
  return r;
}





// @ 0x0062a860
void SetupFromConfigFile(cSPPlayMode_s0062_9c50* m)
{
  Release2(*(void**)((char*)m + 0x1b8));
  *(void**)((char*)m + 0x1b8) = 0;
  (void)PropertyManager();
  (void)ModelManager();
}





// @ 0x0062a990
void BabyStartSocialCallEffect(cSPPlayMode_s0062_9c50* m)
{
  uint32_t idx = GetMouthPartIdx(m);
  if (idx == 0xffffffffu) return;
}





// @ 0x0062aa90
void SetBabySitState(cSPPlayMode_s0062_9c50* m, uint32_t index)
{
  char* cm = *(char**)((char*)m + 0x3610);
  char* vec = *(char**)(cm + 0x36c);
  int n = (*(int*)(cm + 0x370) - (int)vec) / 0x30;
  void* id = (index < (uint32_t)n) ? *(void**)(vec + index * 0x30) : *(void**)vec;
  int off = index * 0x30;
  if (*(int*)(vec + off + 0x2c) != -1) {
    cSPEditorAnimMgr_GetCreature(*(char**)(cm + 0x360), id);
    int h = *(int*)(vec + off + 0x2c);
    if (h != -1) {
      Mgr029* mgr = *(Mgr029**)((char*)m + 0x3610);
      (void)mgr;
      void* v = 0;
      if (v) {
        if (*(void**)((char*)v + 0x8c)) {
          void* o = *(void**)((char*)v + 0x8c);
          ((void(__thiscall*)(void*, int))Vt(o)[3])(o, 1);
        }
      }
    }
    *(int*)(vec + off + 0x2c) = -1;
  }
  *(uint32_t*)(vec + off + 0x24) = 0;
  *(uint32_t*)(vec + off + 0x28) = 0;
  *(uint8_t*)(vec + off + 0x1c) = 0;
}





// @ 0x0062ab80
void cSPPlayMode_s0062_9c50::SetAllBabySitState()
{
  cSPPlayMode_s0062_9c50* m = this;
  char* cm = *(char**)((char*)m + 0x3610);
  int n = (*(int*)(cm + 0x370) - *(int*)(cm + 0x36c)) / 0x30;
  for (int i = 0; i < n; ++i) SetBabySitState(m, (uint32_t)i);
}




// @ 0x0062abd0
void __fastcall cSPPlayMode_MakeCreaturesFaceCamera(void* self)
{
  char* s = (char*)self;
  float cam[3];
  float pos[3];
  float tmp[6];
  *(unsigned short*)(s + 0x4e) = 0x0101;
  *(unsigned char*)(s + 0x50) = 1;
  void* mgr = (void*)CALLEE_572400(cam);
  // GetCurrentCameraPosition(mgr, cam)
  ((TF1)(*(void**)(*(char**)mgr + 0x0)))(mgr, 0); // placeholder, refined below
  (void)pos; (void)tmp;
}




// @ 0x0062ace0
float __stdcall FUN_0062ace0(void* p, char b)
{
  char* q = *(char**)((char*)p + 0x180);
  float* v = (float*)(q + 0x70);
  float dx = v[3] - v[0];
  float dy = v[4] - v[1];
  float d  = dx;
  if (dy > dx) d = dy;
  if (b) d = *(float*)((char*)p + 0x3c) * d;
  return d * gHalf;
}




// @ 0x0062ad70
void __fastcall cSPPlayMode_ad70(void* self, void*, int, int, float, float, float, float)
{
  (void)self;
}




// @ 0x0062b000
void __fastcall FUN_0062b000(void* self)
{
  char* s = (char*)self;
  unsigned n = (*(unsigned*)(s + 0x3670) - *(unsigned*)(s + 0x366c)) >> 2;
  if (n != 0) {
    for (unsigned i = 0; i < n; ++i) {
      char* o = *(char**)(*(unsigned*)(s + 0x366c) + i * 4);
      char* m0 = *(char**)o;
      char* vtb = *(char**)m0;
      TF1 fn = (TF1)(*(void**)(vtb + 0x16c));
      fn(m0, 0);
    }
    for (unsigned k = n; k != 0; --k) {
      *(unsigned*)(s + 0x3670) -= 4;
      char* o = **(char***)(s + 0x3670);
      if (o != 0) {
        if (*(int*)(o + 0x40) < 2) {
          char* m0 = *(char**)o;
          char* vtb = *(char**)m0;
          TF2 fn = (TF2)(*(void**)(vtb + 0x170));
          fn(m0, (int)o, (*(unsigned*)(o + 4)) >> 31 & 1);
        } else {
          (*(int*)(o + 0x40)) -= 1;
        }
      }
    }
  }
  unsigned m = (*(unsigned*)(s + 0x3698) - *(unsigned*)(s + 0x3694)) >> 2;
  for (unsigned i = 0; i < m; ++i) {
    char* o = *(char**)(*(unsigned*)(s + 0x3694) + i * 4);
    int x = *(int*)(o + 8);
    char b = 0;
    ((Bp*)(char*)x)->FUN_01083110((int)&b);
    ((HkWorldObject*)o)->removeReference();
  }
  for (unsigned k = m; k != 0; --k) {
    *(unsigned*)(s + 0x3698) -= 4;
  }
}




// @ 0x0062b0f0
cSPPlayModeAnimation::cSPPlayModeAnimation()
{
  mF20 = 0;
  for (int i = 0; i < 24; ++i) pTooltip[i] = 0;
}




// @ 0x0062b160
cSPPlayModeAnimation::~cSPPlayModeAnimation()
{
  AnimRef** p = pTooltip + 24;
  int n = 23;
  do {
    AnimRef* t = *--p;
    if (t != 0) t->s1();
  } while (--n >= 0);
}




// @ 0x0062b1c0
void __fastcall cSPPlayMode_ctor(void* self)
{
  (void)self;
}




// @ 0x0062b3a0
void __fastcall cSPPlayMode_dtor(void* self)
{
  (void)self;
}




// @ 0x0062b5c0
unsigned __fastcall cSPPlayMode_HandleMessage(void* self, unsigned, int)
{
  (void)self;
  return 0;
}




// @ 0x0062b980
void __fastcall FUN_0062b980(void* self, int id)
{
  char* s = (char*)self;
  char** end = *(char***)(s + 0x80);
  char** it  = *(char***)(s + 0x7c);
  while (it != end) {
    char* o = *it;
    if (o != 0) {
      char* v = *(char**)o;
      ((TF0)(*(void**)(v + 4)))(v);
    }
    if (*(int*)(o + 0x1c) == id) {
      if ((char**)(it + 1) < *(char***)(s + 0x80)) {
        CALLEE_62ffd0(it + 1, *(char***)(s + 0x80), it);
      }
      *(unsigned*)(s + 0x80) -= 4;
      char* last = **(char***)(s + 0x80);
      if (last != 0) {
        char* lv = *(char**)last;
        ((TF0)(*(void**)(lv + 8)))(lv);
      }
      char* ov = *(char**)o;
      ((TF0)(*(void**)(ov + 8)))(ov);
      return;
    }
    it = (char**)((char*)it + 4);
    char* ov = *(char**)o;
    ((TF0)(*(void**)(ov + 8)))(ov);
  }
}




// @ 0x0062ba10
void __fastcall cSPPlayMode_IsEventForBaby(void* self, int)
{
  (void)self;
}



// @ 0x0062bb40
__declspec(noinline) void PM::FUN_0062bb40(int, int)
{}



// @ 0x0062bdb0
void PM::FUN_0062bdb0()
{
  char* s = (char*)this;
  unsigned n = (*(unsigned*)(s + 0x68) - *(unsigned*)(s + 0x64)) >> 2;
  if (n == 0) return;
  int ids[8];
  for (int k = 0; k < 8; ++k) ids[k] = -1;
  unsigned cnt = 0;
  void* mgr = *(void**)((char*)*(void**)(s + 0x3614) + 0x360);
  for (unsigned i = 0; i < n; ++i) {
    int id = *(int*)(*(unsigned*)(s + 0x64) + i * 4);
    char* cr = (char*)((CreatureMgr_s0062_bb40*)mgr)->GetCreature(id);
    if (cr != 0 && (*(unsigned char*)(*(char**)(cr + 0x180) + 6) & 1)) {
      FUN_0062bb40(id, id != *(int*)((char*)*(void**)(s + 0x3614) + 0x364));
      ids[cnt++] = id;
    }
  }
  for (unsigned j = 0; j < cnt; ++j) {
    int* d = *(int**)(s + 0x64);
    int* e = *(int**)(s + 0x68);
    while (d != e) {
      if (ids[j] == *d) {
        if (d + 1 < e) {
          ((VecB*)(s + 0x64))->DoInsertValue(d, d + 1, (int)e - (int)(d + 1));
        }
        *(unsigned*)(s + 0x68) -= 4;
        break;
      }
      ++d;
    }
  }
}



// @ 0x0062bec0
void PM::FUN_0062bec0()
{
  char* s = (char*)this;
  unsigned n = (*(unsigned*)(s + 0x80) - *(unsigned*)(s + 0x7c)) >> 2;
  Vec* vec = (Vec*)(s + 0x7c);
  unsigned i = 0;
  while (i < n) {
    int* arr = *(int**)vec;
    int o = arr[i];
    if (o != 0) {
      arr[i] = 0;
      ((TF0)(*(void**)(*(char**)o + 8)))((void*)o);
    }
    ++i;
  }
  vec->erase(*(void**)vec, *(void**)((char*)vec + 4));
}



// @ 0x0062bf10
__declspec(noinline) void PM::FUN_0062bf10(int)
{}



// @ 0x0062c340
void SP::cSPPlayMode::Stop()
{}



// @ 0x0062c550
void SP::cSPPlayMode::Update(unsigned int a0)
{}


// @ 0x0062e2e0
float cSPPlayModeAnimation_s0062_da00__ui::StartNewAnimation(uint32_t creatureId, uint32_t anim, bool flag, uint32_t param, uint32_t* outHandle)
{
  EditorBase* eb = mEditorBase;
  uint32_t cid = creatureId;
  CreatureStructure* cs = eb->mgr->GetCreatureStructure(cid);
  if (cs != 0) {
    AnimatingCreature* c = cs->mCreature;
    if (c != 0) {
      if (c->IsMoveIdleAnim(anim)) {
        AnimSlot* slot = (AnimSlot*)FUN_009ff6f0(c->mController, c->mCurHandle);
        if (slot == 0 || slot->mAnimID != anim) {
          uint32_t h = c->CreateAnim(anim, 0);
          c->mCurHandle = h;
          c->SetAnimParam(h, param);
          c->Start(c->mCurHandle);
        }
        if (slot != 0 && slot->mAnimID != anim) c->mController->FUN_00a00f90(slot, 0);
        if (flag) {
          c->SetLooping(c->mCurHandle, 1);
          c->SetBlend(c->mCurHandle, -1.0f);
        }
        if (outHandle != 0) *outHandle = c->mCurHandle;
      } else {
        uint32_t h = c->CreateAnim(anim, 0);
        c->SetAnimParam(h, param);
        c->Start(h);
        if (flag) {
          c->SetLooping(h, 1);
          c->SetBlend(h, -1.0f);
        }
        if (outHandle != 0) *outHandle = h;
        if (!c->FUN_00a02800(anim)) {
          c->mController->FUN_00a01f10(c->mFadeOutHandle, 0);
          c->mController->FUN_00a01f10(c->mCurHandle, 0);
        }
        cs->FUN_007cd950(anim);
      }
      mCurrAnimID = anim;
      return cs->mCreature->GetAnimLength(anim);
    }
  }
  if (outHandle != 0) *outHandle = 0;
  return -1.0f;
}

// @ 0x0062f2a0
void SP::cSPPlayModeAnimation::Init(SP::cAppModeEditorBase * editorBase, SP::cSPPlayModeUI * ui)
{
  mUI = ui;
  mEditorBase = (SP::cAppModeEditorBase*)editorBase;
  mCurrAnimID = 0xffffffff;
  LoadAllAnimInfoFromGroup();
  uint32_t n = (uint32_t)(mAnimPanelInfo.mpEnd - mAnimPanelInfo.mpBegin) >> 2;
  uint32_t pages = n + 1;
  mPageCount = pages;
  if (((char*)mAnimPanelInfo.mpEnd - (char*)mAnimPanelInfo.mpBegin) & 0xc) {
    pages++;
    mPageCount = pages;
  }
}
