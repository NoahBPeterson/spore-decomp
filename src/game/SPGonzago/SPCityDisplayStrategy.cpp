// src/game/SPGonzago/SPCityDisplayStrategy.cpp -- migrated from slice(s) s00ce8160, s00b8bb70, s00cec6d0, s00ceb710, s00cea090, s00ce90c0, s00ae3ed0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCityDisplayStrategy.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <intrin.h>
#include "cSPUILayout.h"
#include "SP/cGameData.h"
#include "SP/cPlanetModel.h"
#include "SP/cSpatialObject.h"
#include "SP/cViewer.h"
#include <xmmintrin.h>
#include <math.h>
#include "SP/cGameNounManager.h"
#include "SP/cString.h"
#include "SP/cCity.h"
#include "SP/cCivilization.h"
#include "SP/cPlanet.h"
#include "SP/cRenderer.h"
#pragma intrinsic(_InterlockedExchangeAdd)

// ---- items of slice s00ae3ed0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
class cCityDisplayStrategy {
 public:
  unsigned char mPad0[0x14];       // +0x00
  void* mpArrayBegin;              // +0x14
  unsigned char mPad1[0x94];       // +0x18
  int mCount;                      // +0xac

  void UpdateMinimapCityIcon(int icon);  // 0x00ae4ec0
};
}
namespace {

struct Quaternion {
  float x, y, z, w;
};

// 3x3 float matrix; Assign is a thiscall (dst in ECX, src pushed).
struct Matrix33T {
  float m[9];
  void Assign(const void* src);  // 0x0041cb40
};

// The message handed to the effect objects.
struct XformMsg {
  unsigned short mStatus;  // +0x00
  short mField2;           // +0x02
  float mPosition[3];      // +0x04
  float mField10;          // +0x10
  Matrix33T mMatrix;       // +0x14
};

struct IRefCounted {
  virtual void AddRef();   // +0x0
  virtual void Release();  // +0x4
};

// vtable slots used across the slice.
struct IEffect {
  virtual void f0();                          // +0x00
  virtual void Release();                     // +0x04
  virtual void SetFlag0(int);                 // +0x08
  virtual void fc();                          // +0x0c
  virtual void f10();                         // +0x10
  virtual void f14();                         // +0x14
  virtual void SetTransform(XformMsg*);       // +0x18
  virtual void f1c();                         // +0x1c
  virtual void SetPosition(XformMsg*);        // +0x20
  virtual void f24();                         // +0x24
  virtual void f28();                         // +0x28
  virtual void f2c();                         // +0x2c
  virtual void f30();                         // +0x30
  virtual void f34();                         // +0x34
  virtual void f38();                         // +0x38
  virtual void f3c();                         // +0x3c
  virtual void f40();                         // +0x40
  virtual void SetParam(int, float*, int);    // +0x44
};

struct IImageSource {
  virtual void f0();   // +0x00
  virtual void f4();   // +0x04
  virtual void f8();   // +0x08
  virtual void fc();   // +0x0c
  virtual void f10();  // +0x10
  virtual void f14();  // +0x14
  virtual void f18();  // +0x18
  virtual void* GetImage(unsigned int a, unsigned int b, unsigned int c,
                         int d);  // +0x1c
};

struct IManager {
  virtual void f0();   // +0x00
  virtual void f4();   // +0x04
  virtual void f8();   // +0x08
  virtual void fc();   // +0x0c
  virtual void f10();  // +0x10
  virtual void f14();  // +0x14
  virtual void f18();  // +0x18
  virtual void f1c();  // +0x1c
  virtual void f20();  // +0x20
  virtual void f24();  // +0x24
  virtual void f28();  // +0x28
  virtual bool GetEntry(unsigned int key, int a, void* value);  // +0x2c
};

// Icon object: only the flag word at +0x04 is touched.
struct IconFlagWord {
  unsigned int mFlags;  // +0x00 (object base: the +4 flag is modelled at +0x04)
};

// Minimap sub-object: the object at root->+0x34.
struct IMinimapEntry {
  virtual void f0();   // +0x00
  virtual void f4();   // +0x04
  virtual void f8();   // +0x08
  virtual void fc();   // +0x0c
  virtual void f10();  // +0x10
  virtual void f14();  // +0x14
  virtual void f18();  // +0x18
  virtual void f1c();  // +0x1c
  virtual void f20();  // +0x20
  virtual void f24();  // +0x24
  virtual void f28();  // +0x28
  virtual float* GetQuaternion(float* q);  // +0x2c
  virtual float* GetPosition();            // +0x30
  virtual void f34();  // +0x34
  virtual void f38();  // +0x38
  virtual void f3c();  // +0x3c
  virtual void f40();  // +0x40
  virtual void f44();  // +0x44
  virtual bool IsActive();                 // +0x48
  virtual void f4c();  // +0x4c
  virtual void f50();  // +0x50
  virtual void f54();  // +0x54
  virtual void f58();  // +0x58
  virtual void f5c();  // +0x5c
  virtual void f60();  // +0x60
  virtual void f64();  // +0x64
  virtual void f68();  // +0x68
  virtual void f6c();  // +0x6c
  virtual void f70();  // +0x70
  virtual void f74();  // +0x74
  virtual void f78();  // +0x78
  virtual void f7c();  // +0x7c
  virtual void f80();  // +0x80
  virtual void f84();  // +0x84
  virtual void f88();  // +0x88
  virtual void f8c();  // +0x8c
  virtual void f90();  // +0x90
  virtual void f94();  // +0x94
  virtual void f98();  // +0x98
  virtual void f9c();  // +0x9c
  virtual void fa0();  // +0xa0
  virtual void fa4();  // +0xa4
  virtual void fa8();  // +0xa8
  virtual unsigned int* GetIconObject();   // +0xac (returns ptr with a flag at +4)
};

// Minimap root object: the pointer stored in the record.
struct IMinimapRoot {
  virtual void f0();   // +0x00
  virtual void f4();   // +0x04
  virtual void f8();   // +0x08
  virtual void fc();   // +0x0c
  virtual void f10();  // +0x10
  virtual void f14();  // +0x14
  virtual void f18();  // +0x18
  virtual void f1c();  // +0x1c
  virtual void f20();  // +0x20
  virtual void f24();  // +0x24
  virtual void f28();  // +0x28
  virtual void f2c();  // +0x2c
  virtual void f30();  // +0x30
  virtual void f34();  // +0x34
  virtual void f38();  // +0x38
  virtual void f3c();  // +0x3c
  virtual void f40();  // +0x40
  virtual void f44();  // +0x44
  virtual void f48();  // +0x48
  virtual void f4c();  // +0x4c
  virtual void f50();  // +0x50
  virtual void f54();  // +0x54
  virtual void f58();  // +0x58
  virtual void f5c();  // +0x5c
  virtual void f60();  // +0x60
  virtual void f64();  // +0x64
  virtual void f68();  // +0x68
  virtual void f6c();  // +0x6c
  virtual void f70();  // +0x70
  virtual void f74();  // +0x74
  virtual void f78();  // +0x78
  virtual void f7c();  // +0x7c
  virtual void f80();  // +0x80
  virtual void f84();  // +0x84
  virtual void f88();  // +0x88
  virtual void f8c();  // +0x8c
  virtual void f90();  // +0x90
  virtual void f94();  // +0x94
  virtual void f98();  // +0x98
  virtual void f9c();  // +0x9c
  virtual void fa0();  // +0xa0
  virtual void fa4();  // +0xa4
  virtual void fa8();  // +0xa8
  virtual void* GetEntry34();              // +0xac (returns ptr; sub-object at +0x34)
  virtual void fb0();  // +0xb0
  virtual void fb4();  // +0xb4
  virtual void fb8();  // +0xb8
  virtual void** GetVec();                 // +0xbc (returns {begin,end} ptr)
};

}  // namespace
namespace SP {
struct MinimapVectorElem {
  unsigned char mPad0[0x34];
  IMinimapEntry mEntry;  // +0x34
};  // namespace SP
}
// ---- items of slice s00ae3ed0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void __stdcall StartEffect(float* position, float* quaternion);  // 0x00ae4810 (stays in the slice: not this object's)

// ---- items of slice s00ce90c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
typedef unsigned char u8;
typedef unsigned int u32;
void* __cdecl FUN_00f473a0(uint, const char*, int, int, const char*, int); // 0x00f473a0 operator new
void  __cdecl FUN_00ce8d00(void*, void*, void*);                   // 0x00ce8d00
void* __cdecl FUN_00cf74c0();                                      // 0x00cf74c0 cCivModeStrategy::Get
void  __cdecl FUN_00cf74d0();                                      // 0x00cf74d0
void* __cdecl FUN_00b3d280();                                      // 0x00b3d280 GetCameraCtl
void* __cdecl FUN_00b3d350();                                      // 0x00b3d350 PlanetModel
void* __cdecl FUN_00b30d70();                                      // 0x00b30d70 GetGameTerrainCursor
void* __cdecl FUN_0067ddd0();                                      // 0x0067ddd0 EffectsManager
void* __cdecl FUN_00a206f0();                                      // 0x00a206f0 EA::Audio::GetSystemAT
u8    __cdecl FUN_00e01380(void*);                                 // 0x00e01380
void* __cdecl FUN_00b10260(void*);                                 // 0x00b10260 cTerrainCameraController::GetTarget
void* __cdecl FUN_00ca10a0();                                      // 0x00ca10a0
void  __cdecl FUN_00b146a0(void*, int, int);                       // 0x00b146a0
void  __cdecl FUN_00e05930(void*, int);                            // 0x00e05930
void* __cdecl FUN_00cf8d70(void*, void*);                          // 0x00cf8d70 SetCameraTrackObject
uint  __cdecl FUN_00e23250();                                      // 0x00e23250 item count (static)
void  __cdecl FUN_00ca3350(void*, int);                            // 0x00ca3350
void  __cdecl FUN_00bfc5e0(void*, int);                            // 0x00bfc5e0
void  __cdecl FUN_00c9e870(void*, u32);                            // 0x00c9e870
struct Vec4 { float x, y, z, w; };
Vec4* __cdecl SPUIHelpers_GetMainWindowArea(Vec4* out); // 0x00805ea0
struct CIcon {
    void  Refresh();          // 0x00e21960
    void  RefreshAlt();       // 0x00e21980
    void  SetEnabled(u8);     // 0x00e215d0
    void* GetTaskSource();    // 0x00ca71d0
    void* FindItem(void*);    // 0x00e24c90
};
struct CSPUILayout {
    void* GetLayout();                 // 0x0093b6c0 (on cSPUIGlobalUICiv)
    void* FindWindowByID(u32 id, int); // 0x008105b0
    void  Shutdown(uint);              // 0x00811ad0
};
struct Sub34 {
    void* mpVtbl;            // +0x00
    char  pad04[0x2c - 4];
};
struct EffectHandle {
    void* mpVtbl;            // +0x00
    void* mpField4;          // +0x04
};
struct MapValue {
    char  pad00[0x34];
    Sub34 mSub34;            // +0x34 : embedded, first word is a vtable
    char  pad6c[0x4a8];      // to +0x508
    void* mField508;         // +0x508
};
struct cSPUIPosse {
    char   pad00[0xa4];
    void** mpItemBegin;   // +0xa4
    void** mpItemEnd;     // +0xa8
    char   pad_ac[0x1e4 - 0xac];
    u8     mbFlag;        // +0x1e4

    int ItemCount() { return (int)((char*)mpItemEnd - (char*)mpItemBegin) >> 3; }
    void Refresh() { ((CIcon*)this)->Refresh(); }        // 0x00e21960
    void RefreshAlt() { ((CIcon*)this)->RefreshAlt(); }  // 0x00e21980
    void* FindItem(void* key) { return ((CIcon*)this)->FindItem(key); } // 0x00e24c90
};
struct cGameData {
    char pad00[0xb1c];
    int  mContinent;   // +0xb1c
    int  mCivIndex;    // +0xb20
    char pad24[0xb68 - 0xb24];
    void* mpField_b68; // +0xb68
    void* mpField_b6c; // +0xb6c
};
struct CTaskSource {
    char pad00[0x10];
    int  mTask;   // +0x10
};
struct RefPtr {
    static void AddRef(void* p)  { if (p) ((void(__thiscall*)(void*))(*(void**)p))(p); }
    static void Release(void* p) { if (p) ((void(__thiscall*)(void*))((*(void***)p)[1]))(p); }
};
struct cTerrainCamera {
    char pad00[0x14];
    u8   mbFlag14;  // +0x14
    u8   mbFlag15;  // +0x15
    u8   mbFlag16;  // +0x16
    u8   mbFlag17;  // +0x17
};
struct cPlanetModel_s00ce_90c0 {
    char pad00[0x64];
    int  mContinentFlags;  // +0x64
    void* __thiscall GetContinent(void* key);   // 0x00b88590
};
struct CDS {
    void*  mpVtbl;                    // +0x00
    char   pad04[0x38 - 4];
    void*  mpIHandlerVtbl;            // +0x38
    u8     mbGodModeActive;           // +0x3c
    int    mGodModeVehiclePurpose;    // +0x40
    int    mGodModeVehicleLocomotion; // +0x44
    uint   mGodModeCiv;               // +0x48
    void*  mAutoHandler0;             // +0x4c
    void*  mAutoHandler4;             // +0x50
    void*  mAutoHandler8;             // +0x54
    void*  mAutoHandlerC;             // +0x58
    void*  mAutoHandler10;            // +0x5c
    void*  mpMode;                    // +0x60
    void*  mpGlobalCivUI;             // +0x64
    int    mDebugAIPage;              // +0x68
    cSPUIPosse* mPosses[4];           // +0x6c
    char   mMaps[4 * 0x1c];           // +0x7c
    void*  mpPosseIconLayout;         // +0xec
    void*  mpMiniMapWin;              // +0xf0
    void*  mpTargetingReticle;        // +0xf4
    void*  mpErrorReticle;            // +0xf8
    void*  mpExtraReticle;            // +0xfc
    void*  mAudioSounds[3];           // +0x100
    void*  mpSelEff0;                 // +0x10c
    void*  mpSelEff1;                 // +0x110
    void*  mpSelEff2;                 // +0x114
    void*  mpSelEff3;                 // +0x118
    void*  mpSelEff4;                 // +0x11c

    // map anchor / node accessors for mVehiclePosseMaps[i]
    // anchor is at +0x80 + i*0x1c ; node key at node+0x14, value at node+0x10.
    char* MapAnchor(int i) { return (char*)this + 0x80 + i * 0x1c; }
    char* MapEnd(int i)    { return (char*)this + 0x80 + i * 0x1c; }

    void GodModeUpdateReticles();          // 0x00ce90c0
    void AccumulatePosseArea(Vec4* out);   // 0x00ce9380
    void SetVehicleTask(cGameData* data, cGameData* vehicle); // 0x00ce9460
    void ResetPosses();                    // 0x00ce9560
    void UpdateUI(int dummy);              // 0x00ce9590
    void SetReticlesVisible(u8 visible); // 0x00ce96b0
    void ShutdownAll();                    // 0x00ce97e0
    int  HandleMessage(int msgID, void* msg); // 0x00ce9920
    void SelectVehicle(void* vehicle, int flag, int param4); // 0x00ce9b70
    void RefreshVehicleIcons(cGameData* vehicle);   // 0x00ce9c30
    void UpdateVehicleContinent(cGameData* vehicle); // 0x00ce9d30
    void BuildEffectDesc(int type, int variant);     // 0x00ce9e20
};
struct EffectTarget {
    void* mpVtbl;     // +0x00
    void* mField4;    // +0x04
    u8    mField8;    // +0x08
    char  pad09[0xc - 9];
    u32   mColor;     // +0x0c
    int   mType;      // +0x10
    int   mVariant;   // +0x14
};
struct EffectDesc {
    u32   mId;        // +0x00
    u32   mField4;    // +0x04
    u8    mbField8;   // +0x08
    char  pad09[0xc - 9];
    u8    mbFlagC;    // +0x0c
    u8    mbFlagD;    // +0x0d
    u8    mbFlagE;    // +0x0e
    u8    mbFlagF;    // +0x0f
    float mFloat10;   // +0x10
    u32   mField14;   // +0x14
    u32   mField18;   // +0x18
    u32   mField1c;   // +0x1c
};
// ---- items of slice s00ce90c0 end

// ---- items of slice s00cea090 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl FUN_00f473a0(uint, const char*, int, int, int, int); // 0x00f473a0 EAAllocate
void  __cdecl FUN_00f47380(void*);                                 // 0x00f47380 operator delete
void* __cdecl FUN_00cf74f0(void*);                                 // 0x00cf74f0 GetState
void* __cdecl FUN_00b3d300();                                      // 0x00b3d300 NounManager
void* __cdecl FUN_00b25fb0(void*);                                 // 0x00b25fb0 GetPlayerCivilization
void* __cdecl FUN_00bda200(void*, int, int*);                      // 0x00bda200
void* __cdecl FUN_0067dcc0();                                      // 0x0067dcc0 MessageServer
void* __cdecl FUN_00b3d3e0();                                      // 0x00b3d3e0 EventLog
void* __cdecl FUN_00e24c90(void*, void*);                          // 0x00e24c90 cSPUIPosse::FindItem
void  __cdecl FUN_00af1430(void*);                                 // 0x00af1430 TimerOwner::Dtor
void* __cdecl FUN_00921580(void*);                                 // 0x00921580 RBTreeIncrement
void  __cdecl FUN_00921880(void*, void*);                          // 0x00921880 RBTreeErase
void  __cdecl FUN_00f240d0(void*, int*);                           // 0x00f240d0 EventTree::Destroy
void  __cdecl FUN_0040ce80(void*);                                 // 0x0040ce80
void  __cdecl FUN_00f33a80(void*, void*, void*);                   // 0x00f33a80
void* __cdecl FUN_00537dc0(void*, const void*);                    // 0x00537dc0 cSPTransformOps::Assign
struct RBTH { void __thiscall Fn(void*, void*); };
struct LayoutObj {
    void* __thiscall ctor0();
    char  __thiscall InitLayout(const void* w, int a, int b, int c);
    void  __thiscall SetVis(int v);
};
struct SelEffObj { void __thiscall Set(int a, int b); };
struct TimerOwnerObj { void __thiscall Ctor(); };
struct EventLogObj { void __thiscall Apply(float a, float b); };
struct CDS_s00ce_a090 {
    void*  mpVtbl;         // +0x00
    char   pad00[0x38];
    void*  mpIHandlerVtbl; // +0x38
    uint8_t mbGodModeActive; // +0x3c
    int    mGodModeVehiclePurpose;   // +0x40
    int    mGodModeVehicleLocomotion;// +0x44
    uint   mGodModeCiv;    // +0x48
    void*  mAutoHandler0;  // +0x4c  message id / handler ptr
    void*  mAutoHandler4;  // +0x50
    void*  mAutoHandler8;  // +0x54
    int    mAutoHandlerC;  // +0x58
    void*  mAutoHandler10; // +0x5c
    void*  mpMode;         // +0x60
    void*  mpGlobalCivUI;  // +0x64
    int    mDebugAIPage;   // +0x68
    void*  mPosses[4];     // +0x6c
    char   mMaps[4 * 0x1c];// +0x7c
    void*  mpPosseIconLayout; // +0xec
    void*  mpMiniMapWin;   // +0xf0
    void*  mpTargetingReticle; // +0xf4
    void*  mpErrorReticle; // +0xf8
    char   pad_fc[0x10c - 0xfc];
    void*  mpSelEff0;      // +0x10c
    void*  mpSelEff1;      // +0x110
    void*  mpSelEff2;      // +0x114
    void*  mpSelEff3;      // +0x118
    void*  mpSelEff4;      // +0x11c
    char   pad_end[0];

    void Init();  // 0x00cea090 (CDS::Init)
    void Update();
    void Update2(void* a, int b);
    void Refresh();
    void Assign(void* other);
    void* RemoveVehicle(void* out, void* node);  // 0x00ceaac0 (CDS::RemoveVehicle)
    int  EraseKey(void* key);  // 0x00ceab20 (CDS::EraseKey)
    void Destruct();  // 0x00ceac50 (CDS::Destruct)
    void* ctor(void* a);  // 0x00ceb090 (CDS::ctor)
};
// ---- items of slice s00cea090 end

// ---- items of slice s00ceb710 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3 { float x, y, z; };
struct Matrix3 { float m[9]; };
struct Transform {
    uint16_t m_flags;      // +0
    uint16_t m_count;      // +2
    Vector3  m_offset;     // +4
    float    m_scale;      // +0x10
    Matrix3  m_rot;        // +0x14
};
struct cSpatialObject {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
    virtual uint32_t GetTypeId();                                      // slot 8  (+0x20)
virtual void s9();
virtual void s10();
    virtual const Vector3* GetPosition();                              // slot 11 (+0x2c)
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
virtual void s22();
    virtual const Vector3* GetDirection(Vector3* tmp);                 // slot 23 (+0x5c)
virtual void s24();
virtual void s25();
virtual void s26();
virtual void s27();
virtual void s28();
    virtual float GetScale();                                          // slot 29 (+0x74)
virtual void s30();
virtual void s31();
virtual void s32();
virtual void s33();
virtual void s34();
virtual void s35();
virtual void s36();
virtual void s37();
virtual void s38();
virtual void s39();
virtual void s40();
virtual void s41();
virtual void s42();
virtual void s43();
virtual void s44();
    virtual void s45();
    virtual void* QueryInterface(uint32_t id);                         // slot 46 (+0xb8)
    virtual void s47();
    virtual void Release();                                            // slot 48 (+0xc0)
    uint8_t m_pad[0x73];
    uint8_t m_isPlanetSurface;     // +0x77
    float DistanceToCamera();      // FUN_00c887c0 (thiscall, float in st0)
};
struct cSpatialObjectComponent { uint8_t pad[0xb1c]; int m_state; };   // +0xb1c
struct cViewer {
    void GetCameraLocationInfo(Vector3* pos, Vector3* dir, int a, int b);   // 0x007c3d30
};
struct cPlanetModel {
    const Vector3* FUN_00b7e3b0(Vector3* out, const Vector3* in);          // 0x00b7e3b0
};
struct IAppLayer {
virtual void a0();
virtual void a1();
virtual void a2();
virtual void a3();
virtual void a4();
virtual void a5();
virtual void a6();
    virtual cViewer* GetViewer();                                          // slot 7 (+0x1c)
};
struct cApp {
virtual void b0();
virtual void b1();
virtual void b2();
virtual void b3();
virtual void b4();
virtual void b5();
virtual void b6();
virtual void b7();
virtual void b8();
virtual void b9();
virtual void b10();
virtual void b11();
virtual void b12();
virtual void b13();
virtual void b14();
virtual void b15();
virtual void b16();
virtual void b17();
virtual void b18();
virtual void b19();
    virtual IAppLayer* GetLayer();                                         // slot 20 (+0x50)
};
struct ObjectVec {
    cSpatialObject** m_begin; cSpatialObject** m_end; cSpatialObject** m_cap;
    int m_pad0, m_pad1, m_zero;
    cSpatialObject* m_buf[64];
};
struct TransformVec {
    Transform* m_begin; Transform* m_end; Transform* m_cap;
    int m_pad; Transform* m_fixed; int m_pad2;
    Transform m_buf[64];
    void push_back_default();                      // FUN_00ceb350
};
struct FloatVec {
    float* m_begin; float* m_end; float* m_cap;
    int m_pad; float* m_fixed;
    float m_buf[64];
    void push_back(const float& v);                // FUN_00a1a4d0
    void grow_push_back(float* pos, const float& v);   // FUN_00a1a1e0
};
struct ITerrainCursor {
virtual void t0();
virtual void t1();
virtual void t2();
virtual void t3();
virtual void t4();
virtual void t5();
virtual void t6();
virtual void t7();
virtual void t8();
virtual void t9();
virtual void t10();
virtual void t11();
virtual void t12();
virtual void t13();
virtual void t14();
virtual void t15();
virtual void t16();
virtual void t17();
virtual void t18();
virtual void t19();
virtual void t20();
virtual void t21();
virtual void t22();
    virtual void GetObjects(ObjectVec* out);                               // slot 23 (+0x5c)
};
struct IVertexSink {
    virtual int  Lock(int count, char** base, int* stride);                // slot 0
    virtual void v1();
    virtual void Unlock();                                                 // slot 2
};
struct GameState { uint8_t pad[0x2c]; int m_mode; };
GameState* FUN_00b3d4d0();                                  // 0x00b3d4d0
cPlanetModel* PlanetModel();                                // SP::PlanetModel 0x00b3d350
uint32_t GetCurrentGameMode();                              // 0x00b5b800
cApp* App();                                                // SP::App 0x0067dd10
ITerrainCursor* GetGameTerrainCursor();                     // 0x00b30d70
const Vector3* normalized_safe(Vector3* out, const Vector3* in);                       // 0x00449c20
const Matrix3* Matrix3FromFacingAndUp(Matrix3* out, const Vector3* facing, const Vector3* up);   // 0x0069b440
extern Vector3 g_vecDefault;       // 0x0169ba50
const uint32_t kGameModeTerrain = 0x01654c02;
const uint32_t kTypeIdPlanet = 0x018c6de8;
void operator delete[](void* p);   // 0x00f47380
static inline uint32_t ColorByte(float v)
{
    __m128 k = _mm_set_ss(255.0f);
    return (uint8_t)_mm_cvtss_si32(_mm_min_ss(_mm_mul_ss(_mm_max_ss(_mm_setzero_ps(), _mm_set_ss(v)), k), k));
}
struct cBillboardRenderer {
    uint8_t m_pad0[8];
    uint8_t m_posOffset;       // +8   vertex position offset
    uint8_t m_colorOffset;     // +9   vertex colour offset
    uint8_t m_uvOffset;        // +0xa vertex texcoord offset
    uint8_t m_pad1[5];
    int m_mode;                // +0x10 (2 = alternate set, 1 = half alpha)
    int m_fadeMode;            // +0x14

    void Render(IVertexSink* sink);
};
    void operator delete(void*); // 0x00f47380
// ---- items of slice s00ceb710 end

// ---- items of slice s00cec6d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl operator new(uint32_t nSize, const char* pName, int32_t nA, int32_t nB,
                           const char* pFile, int32_t nLine);                       // 0x00f473a0
void  __cdecl operator_delete(void* pBlock);                                        // 0x00f47380
double __cdecl sqrt(double dValue);                                                 // CRT intrinsic
float g_fRealZero;                      // 0x01485378 _HK_REAL_ZERO
float g_fRealOne;                       // 0x01485720 _HK_REAL_ONE
uint8_t  g_funCD7D10;                   // 0x00cd7d10 game-data vector callback
uint8_t  g_funD3D420;                   // 0x00d3d420 game-data vector callback
uint8_t  g_funB1E500;                   // 0x00b1e500 game-data vector callback
uint8_t  g_funAE5EA0;                   // 0x00ae5ea0 game-data vector callback
uint8_t  g_funACDFF0;                   // 0x00acdff0 game-data vector callback
uint8_t  g_funAE72D0;                   // 0x00ae72d0 game-data vector callback
uint8_t  g_classKey403df5c[4];          // 0x0403df5c the class the first vehicle lookup walks
uint8_t  g_classKey18c43e8[4];          // 0x018c43e8 the class the city-object lookup walks
uint8_t  g_classKey18c6de8[4];          // 0x018c6de8 the class the second vehicle lookup walks
void* __cdecl FUN_009512c0();                                                       // 0x009512c0
void* __cdecl FUN_009512d0(uint32_t nSize, int32_t nDtor, const char* pName,
                           void* pHeap);                                            // 0x009512d0
void* __cdecl FUN_00b993c0(int32_t nTribeId);                                       // 0x00b993c0
void* __cdecl FUN_00b25c30(void* pManager);                                         // 0x00b25c30
void* __cdecl FUN_00e057a0(void* pCivUI);                                           // 0x00e057a0
namespace SP {
class cString_s00ce_c6d0 {
public:
    uint32_t mnTableHash;                       // +0x000 the text table it is looked up in
    uint32_t mnKeyHash;                         // +0x004 the key inside that table
    void*    mpText;                            // +0x008 the resolved text
    void*    mpTextEnd;                         // +0x00c
    void*    mpTextAlloc;                       // +0x010

    cString_s00ce_c6d0(uint32_t nTableHash, uint32_t nKeyHash,
            const wchar_t* pDefaultText);                                   // 0x006b5770
    ~cString_s00ce_c6d0();                                                             // 0x006b5240
    const wchar_t* GetText();                                               // 0x006b55c0
};
}
struct fVector2 {
    float fx;                                   // +0x00
    float fy;                                   // +0x04
};
struct fVector3 {
    float fx;                                   // +0x00
    float fy;                                   // +0x04
    float fz;                                   // +0x08
};
struct fRect {
    float fLeft;                                // +0x00
    float fTop;                                 // +0x04
    float fRight;                               // +0x08
    float fBottom;                              // +0x0c
};
class cRefObject {
public:
    virtual void AddRef();                      // +0x000
    virtual void Release();                     // +0x004
};
class cWindowListener {
public:
    virtual void v00();                         // +0x000
    virtual void AddRef();                      // +0x004
    virtual void Release();                     // +0x008
};
class cGlobalCivUI {
public:
    virtual void AddRef();                      // +0x000
    virtual void Release();                     // +0x004
    virtual void Init(void* pArgs);             // +0x008
    virtual void Shutdown();                    // +0x00c tears the owned panels down
    uint8_t        mPad004[0x64];               // +0x004 .. +0x067
    cWindowListener mListener;                  // +0x068

    class cWindowObject* FindWindowByID(uint32_t nWindowID);                 // 0x00e012b0
};
class cWindowObject {
public:
    virtual void AddRef();                      // +0x000
    virtual void Release();                     // +0x004
    virtual void Init(void* pArgs);             // +0x008
    virtual void v0c();                         // +0x00c
    virtual void v10();                         // +0x010
    virtual void v14();                         // +0x014
    virtual void v18();                         // +0x018
    virtual void v1c();                         // +0x01c
    virtual void v20();                         // +0x020
    virtual void v24();                         // +0x024
    virtual void v28();                         // +0x028
    virtual void v2c();                         // +0x02c
    virtual void v30();                         // +0x030
    virtual void v34();                         // +0x034
    virtual fRect* GetRect();                   // +0x038 the window's client rect
    uint8_t mPad004[0x78];                      // +0x004 .. +0x07b
    void    SetChildWindow(void* pIWindow);     // retail slot +0x0d8
};
class cPosseWindow : public cRefObject {
public:
    virtual void v08();                         // +0x008
    virtual void v0c();                         // +0x00c
    uint8_t mPad010[0x70];                      // +0x010 .. +0x07f
    // retail slot map: +0x080 BindPosseBar, +0x094 SetMode, +0x0b8 SetText
    bool BindPosseBar(const wchar_t* pBarName, float fFill);                 // +0x080
    void DestroyPosseBar();                                                  // +0x088
    void SetMode(int32_t nMode);                                             // +0x094
    void SetText(const wchar_t* pText);                                      // +0x0b8

    cPosseWindow* PosseCtor();                                               // 0x00e25710
};
class cAutoRef {
public:
    cRefObject* mpObject;                       // +0x00
};
class EventTree {
public:
    uint32_t mnAllocTag;                        // +0x00
    void*    mpAnchorLeft;                      // +0x04 points at itself while the tree is empty
    void*    mpAnchorRight;                     // +0x08
    void*    mpRoot;                            // +0x0c
    uint8_t  mbColor;                           // +0x10
    uint8_t  mPad011[3];                        // +0x11 .. +0x13
    uint32_t mnSize;                            // +0x14
    uint32_t mPad018;                           // +0x18

    void Destroy(void* pRoot);                                               // 0x00f240d0
};
class cEastlAllocator {
public:
    uint32_t mnTag;                             // +0x00
    uint32_t mnPad004;                          // +0x04
    uint32_t mnPad008;                          // +0x08
};
class cNounPtrVector {
public:
    void**          mpBegin;                    // +0x00
    void**          mpEnd;                      // +0x04
    void**          mpEndAlloc;                 // +0x08
    cEastlAllocator mAllocator;                 // +0x0c .. +0x17

    // 0x00b93c60: only allocates nCount slots and leaves mpBegin == mpEnd == the allocation
    void   Resize(int32_t nCount, cEastlAllocator* pAllocator);
};
void** __cdecl _Construct(void*** ppOut, void** ppFirst, void** ppLast, void** ppDst,
                          void** ppSeed);
class cGameDataVector {
public:
    void*          mpOwner;                     // +0x00
    cNounPtrVector mVector;                     // +0x04
};
class cGameNounManager_s00ce_c6d0;
cGameNounManager_s00ce_c6d0* __cdecl NounManager();                                         // 0x00b3d300
class cGameNounManager_s00ce_c6d0 {
public:
    cGameDataVector* GetGameDataVector(const void* pFilter1, const void* pFilter2,
                                       const void* pFilter3, const void* pFilter4,
                                       const void* pClassKey);                   // 0x00b21340
    void* SetGameDataOwner2();                                                  // 0x00bfc5f0
};
class cIWindow {
public:
    virtual void v00();                         // +0x000
};
class cMinimapWindow : public cRefObject {
public:
    cIWindow mWindowInterface;                  // +0x004 the interface handed to the parent window
    uint8_t  mPad008[0x33c];                    // +0x008 .. +0x343
    float    mfAngles[3];                       // +0x344 .. +0x34f the view angles

    void SetDirection(const fVector3& rDirection);                           // 0x00e0c1f0
    void SetViewMode(int32_t nMode);                                         // 0x00e0ad00
    void Refresh();                                                          // 0x00e0e1a0

    cMinimapWindow* MinimapCtor(int32_t nWidth, int32_t nHeight, const fVector2* pMin,
                                const fVector2* pMax, int32_t nA, int32_t nB); // 0x00e0fc90
};
class cSimSingleton {
public:
    uint8_t  mPad000[0x14];                     // +0x000 .. +0x013
    int32_t* mpPlayerTribeId;                   // +0x014 the player's tribe id, -1 when unset

    cSimSingleton* SimSingletonCtor();                                       // 0x00ae5c30
};
cSimSingleton* g_pSimSingleton;                 // 0x0167a60c
class cLookAt {
public:
    virtual fVector3* PointAt();                // retail slot +0x02c
};
class cTribeObject {
public:
    uint8_t  mPad000[0x120];                    // +0x000 .. +0x11f
    cLookAt  mLookAt;                           // +0x120
};
class cTribeView {
public:
    uint8_t  mPad000[0x34];                     // +0x000 .. +0x033
    cLookAt  mLookAt;                           // +0x034
};
namespace Simulator {
class cCityDisplayStrategy_s00ce_c6d0 {
public:
    virtual void v00();                         // +0x000
    uint8_t   mPad004[0x60];                    // +0x004 .. +0x063
    cAutoRef  mGlobalCivUI;                     // +0x064 the SPGlobalUI-CivUI window
    cAutoRef  mSelectionPosse;                  // +0x068
    cAutoRef  mPosses[4];                       // +0x06c .. +0x07b
    EventTree mVehiclePosseMaps[4];             // +0x07c .. +0x0eb
    uint32_t  mn0ec;                            // +0x0ec cleared by the constructor
    cAutoRef  mMiniMapWin;                      // +0x0f0 the UI/CivMinimap window
    uint32_t  mn0f4;                            // +0x0f4
    uint32_t  mn0f8;                            // +0x0f8
    uint32_t  mn0fc;                            // +0x0fc
    uint32_t  mn100;                            // +0x100
    uint32_t  mn104;                            // +0x104
    uint32_t  mn108;                            // +0x108
    void*     mpSelectionStreamers[5];          // +0x10c .. +0x11f

    void FUN_00cec6d0();                                                // 0x00cec6d0
    void DestroyAndRecreateCivUI(uint8_t bBuild);                       // 0x00cec7a0
    void NoteVehicleAdded(void* pNoun);                                 // 0x00ceb430
    void RebuildPosseBars();                                            // 0x00ce90c0
    void RefreshCityObject(void* pNoun);                                // 0x00ce8de0
};  // namespace Simulator
}
void __cdecl FUN_00ce8f70(void* pNoun, void* pMinimap);                         // 0x00ce8f70
// ---- items of slice s00cec6d0 end

// ---- items of slice s00b8bb70 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange, _InterlockedDecrement)
struct SVector3 {
    float x, y, z;
};
void* operator new(size_t size, const char* pName, int nFlags, unsigned nDebugFlags,
                   const char* pFile, int nLine);
class RCSub {
public:
    virtual void Del(int);
    volatile long mnRefCount;                  // +0x04
    long Release()
    {
        long n = _InterlockedDecrement(&mnRefCount);
        if (n == 0) {
            _InterlockedExchange(&mnRefCount, 1);
            if (this)
                Del(1);
        }
        return n;
    }
};
class cMinimapGfx {
public:
    char     pad00[0x0c];
    bool     mbDirty;                          // +0x0c
    char     pad0d[0x24 - 0x0d];
    RCSub*   mpRefObject;                      // +0x24
    bool     mbActive;                         // +0x28
};
class cPlanet {
public:
    void SetRampEnabled(bool bEnabled);        // 0x00fbd6b0
};
class IWorldEditor {
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
    virtual cPlanet* v10();                    // +0x10
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
virtual void vA0();
virtual void vA4();
virtual void vA8();
virtual void vAC();
virtual void vB0();
virtual void vB4();
virtual void vB8();
virtual void vBC();
virtual void vC0();
virtual void vC4();
virtual void vC8();
virtual void vCC();
virtual void vD0();
virtual void vD4();
virtual void vD8();
virtual void vDC();
virtual void vE0();
virtual void vE4();
virtual void vE8();
virtual void vEC();
virtual void vF0();
virtual void vF4();
virtual void vF8();
virtual void vFC();
virtual void v100();
virtual void v104();
virtual void v108();
virtual void v10C();
    virtual void ShutdownScene();              // +0x110
};
class IPlanetSphere {
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
    virtual void SetInputManager(void* pManager);        // +0x90
virtual void v94();
virtual void v98();
virtual void v9c();
    virtual void vA0();
    virtual void vA4();                        // +0xa4
    virtual void vA8();
    virtual void vAC();                        // +0xac
virtual void vB0();
virtual void vB4();
virtual void vB8();
virtual void vBC();
virtual void vC0();
virtual void vC4();
virtual void vC8();
virtual void vCC();
virtual void vD0();
virtual void vD4();
virtual void vD8();
virtual void vDC();
virtual void vE0();
virtual void vE4();
virtual void vE8();
    virtual void vEC();                        // +0xec
virtual void vF0();
virtual void vF4();
    virtual void vF8();                        // +0xf8
};
struct CityPair {
    void* mpFirst;
    void* mpSecond;
};
struct LandRoute {
    uint8_t mData[0x1c];
};
class CityPairVector {
public:
    CityPair* mpBegin;                         // +0x00
    CityPair* mpEnd;                           // +0x04
    CityPair* mpCapacity;                      // +0x08
    uint32_t  mAllocator;                      // +0x0c
    void EraseRange(CityPair* pFirst, CityPair* pLast);        // 0x00d018d0
    void Clear() { EraseRange(mpBegin, mpEnd); }
};
class LandRouteVector {
public:
    LandRoute* mpBegin;                        // +0x00
    LandRoute* mpEnd;                          // +0x04
    LandRoute* mpCapacity;                     // +0x08
    uint32_t   mAllocator;                     // +0x0c
    void EraseRange(LandRoute* pFirst, LandRoute* pLast);      // 0x00b897d0
    void Clear() { EraseRange(mpBegin, mpEnd); }
};
class cCivilization {
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
    virtual int GetID();                       // +0x4c
};
class IPositionSource {
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
    virtual const SVector3* GetPosition();     // +0x2c
};
class cCity {
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
    virtual int GetOwnerID(bool bPrimary);     // +0x4c
    char              pad04[0x34 - 0x04];
    IPositionSource   mNodeValue;              // +0x34
    char              pad38[0x120 - 0x38];
    IPositionSource   mPosition;               // +0x120
    cCivilization*    GetCivilization();       // 0x00bd9bf0
};
class cPlaceholder {
public:
    char              pad00[0x34];
    IPositionSource   mNodeValue;              // +0x34
};
struct GraphNodeValue {
    uint32_t mValue[3];
};
struct GraphNode {
    int32_t         mnID;                      // +0x00
    GraphNodeValue  mValue;                    // +0x04
    bool            mbResourceNode;            // +0x10
    bool            mbDirty;                   // +0x11
    uint16_t        pad12;
    cCity*          mpCity;                    // +0x14
};
class GraphNodeVector {
public:
    GraphNode* mpBegin;                        // +0x00
    GraphNode* mpEnd;                          // +0x04
    GraphNode* mpCapacity;                     // +0x08
    uint32_t   mAllocator;                     // +0x0c
};
template <class T>
struct SpVector {
    T*       mpBegin;                          // +0x00
    T*       mpEnd;                            // +0x04
    T*       mpCapacity;                       // +0x08
    uint32_t mAllocator;                       // +0x0c
};
struct tGameDataVector {
    uint32_t            pad00;
    SpVector<cCity*>    mData;                 // +0x04
};
class cGameNounManager {
public:
    tGameDataVector* GetGameDataVector(void* pfnA, void* pfnB, void* pfnC,
                                       void* pfnD, void* pFilter);      // 0x00b21340
};
class cEffMgr {
public:
    char pad00[0xac];
    int  mnSlotCount;                          // +0xac
};
namespace Simulator {
struct SimSlot {
    uint32_t mnNounID;                         // +0x00
    char     pad04[0x2c];
    bool     mbInactive;                       // +0x30
    char     pad31[0x64 - 0x31];
};
}
namespace Simulator {
struct SimSlotVector {
    SimSlot* mpBegin;                          // +0x00
    SimSlot* mpEnd;                            // +0x04
    SimSlot* mpCapacity;                       // +0x08
    uint32_t mAllocator;                       // +0x0c
};
}
namespace Simulator {
class SimSingleton {
public:
    char          pad00[0x14];
    SimSlotVector mVec;                        // +0x14
    char          pad24[0xc8 - 0x24];
    SimSingleton();                            // 0x00ae5c30
    static SimSingleton* sInstance;            // 0x0167a60c
};
}
struct IVec3U {
    uint32_t mX, mY, mZ;
    IVec3U() {}
    IVec3U(uint32_t x, uint32_t y, uint32_t z) : mX(x), mY(y), mZ(z) {}
};
class cPlanetModel_s00b8_bb70 {
public:
    char            pad00[0x20];
    IWorldEditor*   mpWorldEditor;             // +0x20
    IPlanetSphere*  mpISphere;                 // +0x24
    char            pad28[0x2c - 0x28];
    IVec3U          mField2C;                  // +0x2c
    uint16_t*       mpIndexBegin;              // +0x38
    uint16_t*       mpIndexEnd;                // +0x3c
    char            pad40[0x48 - 0x40];
    bool            mbRegistered;              // +0x48
    char            pad49[0x4c - 0x49];
    uint32_t*       mContinentMap;             // +0x4c
    char            pad50[0x64 - 0x50];
    uint8_t*        mContinentAboveWater;      // +0x64
    char            pad68[0x7c - 0x68];
    uint32_t*       mpCellNibbles;             // +0x7c
    GraphNodeVector mNodes;                    // +0x80
    char            pad90[0x94 - 0x90];
    uint8_t*        mpZoneMap;                 // +0x94
    uint8_t*        mpZoneMapEnd;              // +0x98
    char            pad9c[0xa8 - 0x9c];
    cMinimapGfx*    mpMinimapGfx;              // +0xa8
    CityPairVector  mSeaTradeRoutes;           // +0xac
    char            padBC[0xc0 - 0xbc];
    CityPairVector  mLandTradeRoutes;          // +0xc0
    char            padD0[0xd4 - 0xd0];
    LandRouteVector mPathRoutes;               // +0xd4
    char            padE4[0xe8 - 0xe4];
    bool            mbSeaRoutesDirty;          // +0xe8
    bool            mbLandRoutesDirty;         // +0xe9
    bool            mbPathRoutesDirty;         // +0xea

    bool RayCast(const SVector3* pOrigin, float fDirection, SVector3* pOut,
                 float fRadius, bool bLayer, uint32_t nMask);          // 0x00b88770
    bool FindClosestWater(const SVector3* pOrigin, float fDirection,
                          SVector3* pOut);                             // 0x00b8bb70
    void Reset();                                                      // 0x00b87bb0
    int  AddNode(const SVector3* pValue, bool bResourceNode);          // 0x00b86500
    void SetNodeFlag(int nIndex, bool bValue);                         // 0x00b7ea30
    void SetNodeID(int nIndex, int nValue);                            // 0x00b841a0
    int  GetContinent(const SVector3* pPosition);                      // 0x00b88590
    void BuildPoliticalZoneMap();                                      // 0x00b8aea0
    void Shutdown();                                                   // 0x00b8c0f0
    void AddResourceNodes();                                           // 0x00b8bba0
};
extern "C" cGameNounManager* __cdecl NounManager_s00b8_bb70();                    // 0x00b3d300
extern "C" cEffMgr* __cdecl GetEffMgr();                               // 0x00b26930
extern "C" cPlaceholder* __cdecl FindPlaceholder(int nID);             // 0x00b993c0
extern "C" void* __cdecl GetCurrentGameMode_s00b8_bb70();                         // 0x00b5b800
// ---- items of slice s00b8bb70 end

// ---- items of slice s00ce8160 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef          int   s32;
void* __cdecl SP_NounManager();                      // 0x00b3d300 SP::NounManager
void* __cdecl SP_PlanetModel();                      // 0x00b3d350 SP::PlanetModel
void  __cdecl FUN_00e0f9c0(void* self, void* obj, int a, int b); // 0x00e0f9c0 cSPUIMinimapWin::RemoveIcon
void  __cdecl FUN_00e10580(void* self, void* obj, void* data, int a, int b); // 0x00e10580 cSPUIMinimapWin::AddIcon
void* __cdecl FUN_00bd9bf0(void* self);              // 0x00bd9bf0 SP::cCity::GetCivilization
void* __cdecl FUN_00b25f40(void* self, u32 id);      // 0x00b25f40 FindNounByID
void* __cdecl FUN_00b6f310(void* self);              // 0x00b6f310
void* __cdecl FUN_00b81780(void* self, void* out, void* a, void* b, void* c); // 0x00b81780 MakeRandomWorldPosition
void* __cdecl FUN_00bfc490(void* self);              // 0x00bfc490
// ---- items of slice s00ce8160 end

// @ 0x00ae4ec0
namespace SP {
void cCityDisplayStrategy::UpdateMinimapCityIcon(int icon)
{
  int count = mCount;
  if (count <= 0)
    return;
  char* rec = (char*)mpArrayBegin + 0x38;
  int i = 0;
  IMinimapRoot* root = 0;
  for (;;) {
    if (rec[-8] == 1) {
      root = *(IMinimapRoot**)rec;
      if (root != 0)
        break;
    }
    i++;
    rec += 0x64;
    if (i >= count)
      return;
  }
  char* owner = (char*)root->GetEntry34();
  if (owner == 0)
    return;
  IMinimapEntry* entry = (IMinimapEntry*)(owner + 0x34);
  if (!entry->IsActive())
    return;
  if (icon == 1) {
    float* a = entry->GetPosition();
    float* q = entry->GetQuaternion(a);
    StartEffect(q, a);
  } else if (icon == 2) {
    entry->GetIconObject()[1] &= ~1u;
  }
  void** vec = root->GetVec();
  MinimapVectorElem** it = (MinimapVectorElem**)vec[0];
  MinimapVectorElem** stop = (MinimapVectorElem**)vec[1];
  for (; it != stop; it++) {
    IMinimapEntry* e = &(*it)->mEntry;
    if (icon == 1) {
      float* a = e->GetPosition();
      float* q = e->GetQuaternion(a);
      StartEffect(q, a);
    } else if (icon == 2) {
      e->GetIconObject()[1] &= ~1u;
    }
  }
}
}  // namespace SP

// @ 0x00b8bba0
void cPlanetModel_s00b8_bb70::AddResourceNodes()
{
    if (mpISphere == 0)
        return;

    Reset();

    if (GetCurrentGameMode_s00b8_bb70() != (void*)0x1654c04)
        return;

    int nSlots = GetEffMgr()->mnSlotCount;
    for (int i = 0; i < nSlots; ++i) {
        Simulator::SimSingleton* pSim = Simulator::SimSingleton::sInstance;
        if (pSim == 0)
            pSim = Simulator::SimSingleton::sInstance =
                new ("Simulator/SimSingleton", 0, 0, 0, 0) Simulator::SimSingleton();

        Simulator::SimSlot* pSlot = &pSim->mVec.mpBegin[i];
        if (pSlot->mbInactive == false) {
            cPlaceholder* pPlaceholder = FindPlaceholder(pSlot->mnNounID);
            if (pPlaceholder != 0) {
                int nIndex = AddNode(pPlaceholder->mNodeValue.GetPosition(), true);
                SetNodeFlag(nIndex, true);
            }
        }
    }

    SpVector<cCity*>& cityList = NounManager_s00b8_bb70()->GetGameDataVector(
        (void*)0xcd7d10, (void*)0xd3d420, (void*)0xacdff0, (void*)0xb1e500,
        (void*)0x18c43e8)->mData;
    int nCities = (int)(cityList.mpEnd - cityList.mpBegin);
    for (int i = 0; i < nCities; ++i) {
        int nIndex = AddNode(cityList.mpBegin[i]->mPosition.GetPosition(), true);
        if (nIndex > 0 && nIndex < (uint32_t)(mNodes.mpEnd - mNodes.mpBegin) &&
            mNodes.mpBegin[nIndex].mbDirty != true) {
            mNodes.mpBegin[nIndex].mbDirty = true;
            mpMinimapGfx->mbDirty = true;
        }
    }

    SpVector<cCity*>& resourceList = NounManager_s00b8_bb70()->GetGameDataVector(
        (void*)0xcd7d10, (void*)0xd3d420, (void*)0xae5ea0, (void*)0xb1e500,
        (void*)0x403df5c)->mData;
    int nResources = (int)(resourceList.mpEnd - resourceList.mpBegin);
    for (int i = 0; i < nResources; ++i) {
        cCity* pEntity = resourceList.mpBegin[i];
        int nContinent = GetContinent(pEntity->mNodeValue.GetPosition());
        if (mContinentAboveWater[nContinent]) {
            int nIndex = AddNode(pEntity->mNodeValue.GetPosition(), false);
            SetNodeID(nIndex, pEntity->GetOwnerID(false));
            if (nIndex > 0 && nIndex < (uint32_t)(mNodes.mpEnd - mNodes.mpBegin) &&
                mNodes.mpBegin[nIndex].mbDirty != true) {
                mNodes.mpBegin[nIndex].mbDirty = true;
                mpMinimapGfx->mbDirty = true;
            }
        }
    }

    BuildPoliticalZoneMap();

    int nNodeCount = (int)(mNodes.mpEnd - mNodes.mpBegin);
    for (int i = 1; i < nNodeCount; ++i)
        mNodes.mpBegin[i].mpCity = 0;

    for (int i = 0; i < nCities; ++i) {
        cCity* pCity = cityList.mpBegin[i];
        if (pCity != 0 && pCity->GetCivilization() != 0) {
            const SVector3* pPos = pCity->mPosition.GetPosition();
            float ax = fabsf(pPos->x);
            float ay = fabsf(pPos->y);
            float az = fabsf(pPos->z);
            int nFirst;
            int nSecond;
            int nFace;
            if (az < ax || az < ay) {
                if (ay < ax) {
                    nFirst  = (int)((pPos->y / pPos->x + 1.0f) * 32.0f);
                    nSecond = (int)((pPos->z / ax + 1.0f) * 32.0f);
                    nFace   = (pPos->x < 0.0f) ? 3 : 2;
                } else {
                    nFirst  = (int)((pPos->z / pPos->y + 1.0f) * 32.0f);
                    nSecond = (int)((pPos->x / ay + 1.0f) * 32.0f);
                    nFace   = (pPos->y < 0.0f) ? 5 : 4;
                }
            } else {
                nFirst  = (int)((pPos->x / pPos->z + 1.0f) * 32.0f);
                nSecond = (int)((pPos->y / az + 1.0f) * 32.0f);
                nFace   = (pPos->z < 0.0f) ? 1 : 0;
            }
            if (nFirst == 0x40)
                nFirst = 0x3f;
            if (nSecond == 0x40)
                nSecond = 0x3f;
            int nZone = mpZoneMap[(nFace * 0x40 + nSecond) * 0x40 + nFirst];
            if (nZone > 0 && mNodes.mpBegin[nZone].mbResourceNode)
                mNodes.mpBegin[nZone].mpCity = pCity;
        }
    }

    nNodeCount = (int)(mNodes.mpEnd - mNodes.mpBegin);
    for (int i = 1; i < nNodeCount; ++i) {
        GraphNode& node = mNodes.mpBegin[i];
        if (node.mbResourceNode) {
            int nCiv = -1;
            if (node.mpCity != 0)
                nCiv = node.mpCity->GetCivilization()->GetID();
            if (node.mnID != nCiv) {
                mpMinimapGfx->mbDirty = true;
                node.mnID = nCiv;
                node.mbDirty = true;
            }
        }
    }
}

// @ 0x00ce8d00
void __fastcall FUN_00ce8d00(void* self, void* /*edx*/, void* cmd, void* owner)
{
  char* o = (char*)owner;
  float r = ((float(__thiscall*)(void*))FUN_00bfc490)(o + 0x508);
  void* self2 = cmd;
  void** vtbl = *(void***)self2;
  if (r < *(float*)0x013ef74c) {
    ((void(__thiscall*)(void*, int, int))vtbl[0x84 / 4])(self2, 0, 2);
  } else if (o[0xbcc] != 0) {
    ((void(__thiscall*)(void*, int, int))vtbl[0x84 / 4])(self2, 0, 1);
  } else {
    ((void(__thiscall*)(void*, int, int))vtbl[0x84 / 4])(self2, 0, 0);
  }
}

// @ 0x00ce8de0
void __fastcall FUN_00ce8de0(void* self, void* /*edx*/, char* city)
{
  char* p = (char*)self;
  void* win = *(void**)(p + 0xf0);
  if (win == 0) return;

  struct IconData {
    u32 color;   // +0
    float x;     // +4
    float y;     // +8
    float z;     // +0xc
    u32 flags;   // +0x10
    u32 pad;     // +0x14
    u32 pad2;    // +0x18
    void* ref;   // +0x1c
  } icon;
  icon.color = 0;
  icon.x = 0.0f;
  icon.y = 0.0f;
  icon.z = 0.0f;
  icon.flags = 1;
  icon.pad = 0;
  icon.pad2 = 0;
  icon.ref = 0;

  ((void(__thiscall*)(void*, void*, int, int))FUN_00e0f9c0)(win, city, 1, 0);
  icon.flags = 1;

  char* comp = city + 0x120;
  u8 c = ((u8(__thiscall*)(void*))(*(void***)comp)[0x58 / 4])(comp);
  if (c != 0) icon.flags |= 8;

  float* pos = (float*)((void*(__thiscall*)(void*))(*(void***)comp)[0x2c / 4])(comp);
  icon.x = pos[0];
  icon.y = pos[1];
  icon.z = pos[2];
  void* civ = FUN_00bd9bf0(city);
  icon.color = (u32)FUN_00b6f310((char*)civ + 0x3c);

  char* oldRef = (char*)icon.ref;
  if (city != oldRef) {
    ((void(__thiscall*)(void*))(*(void***)city)[0 / 4])(city);
    icon.ref = city;
    if (oldRef != 0) {
      ((void(__thiscall*)(void*))(*(void***)oldRef)[4 / 4])(oldRef);
    }
  }
  ((void(__thiscall*)(void*, void*, void*, int, int))FUN_00e10580)(win, city, &icon, 0, 0);
  void* r = icon.ref;
  if (r != 0) {
    ((void(__thiscall*)(void*))(*(void***)r)[4 / 4])(r);
  }
}

// @ 0x00ce8f70
void __cdecl FUN_00ce8f70(void* obj, void* win)
{
  char* o = (char*)obj;
  ((void(__thiscall*)(void*, void*, int, int))FUN_00e0f9c0)(win, o, 1, 0);

  struct IconData {
    u32 color;   // +0
    float x;     // +4
    float y;     // +8
    float z;     // +0xc
    u32 flags;   // +0x10
    u32 pad;     // +0x14
    u32 pad2;    // +0x18
    u32 pad3;    // +0x1c
    void* ref;   // +0x20
  } icon;
  icon.color = 0xff808080;
  icon.x = 0.0f;
  icon.y = 0.0f;
  icon.z = 0.0f;
  icon.flags = 0x4000;
  icon.pad = 0;
  icon.pad2 = 0;
  icon.pad3 = 0;
  icon.ref = 0;

  s32 id = ((s32(__thiscall*)(void*))(*(void***)o)[0x4c / 4])(o);
  if (id != -1) {
    void* nm = SP_NounManager();
    char* noun = (char*)FUN_00b25f40(nm, (u32)id);
    if (noun != 0) {
      icon.color = (u32)FUN_00b6f310(noun + 0x3c);
    }
  }

  float s = *(float*)0x013eecd8;
  ((void(__thiscall*)(void*))(*(void***)(o + 0x34))[0x2c / 4])(o + 0x34);
  (void)s;
  void* pm = SP_PlanetModel();
  FUN_00b81780(pm, &icon.x, (void*)0x41a00000, (void*)0x41a00000, 0);

  char* oldRef = (char*)icon.ref;
  if (o != oldRef) {
    ((void(__thiscall*)(void*))(*(void***)o)[0 / 4])(o);
    icon.ref = o;
    if (oldRef != 0) {
      ((void(__thiscall*)(void*))(*(void***)oldRef)[4 / 4])(oldRef);
    }
  }
  FUN_00e10580(win, o, &icon, 0, 0);
  void* r = icon.ref;
  if (r != 0) {
    ((void(__thiscall*)(void*))(*(void***)r)[4 / 4])(r);
  }
}

// @ 0x00ce90c0
void CDS::GodModeUpdateReticles()
{
    int counts[4];
    int smooth[4];
    float widths[4];
    float fAcc = 0.0f;
    float fMaxW = 0.0f;
    float fSumW = 0.0f;
    float fLimit;
    int iter = 0;
    int i;
    int ci, cj, sel;

    counts[0] = mPosses[0]->ItemCount();
    counts[1] = mPosses[1]->ItemCount();
    counts[2] = mPosses[2]->ItemCount();
    counts[3] = mPosses[3]->ItemCount();
    smooth[0] = counts[0];
    smooth[1] = counts[1];
    smooth[2] = counts[2];
    smooth[3] = counts[3];

    float area[4];
    SPUIHelpers_GetMainWindowArea((Vec4*)area);
    fLimit = (area[3] - area[2]) - 100.0f;

    do {
        fSumW = 0.0f;
        ci = smooth[0];
        cj = counts[0];
        sel = 0;
        if (!(ci > 0 || (ci == 0 && counts[0] <= 0x400))) {
            ci = 0;
            cj = 0x400;
        }
        if (ci < smooth[1] || (ci == smooth[1] && cj <= counts[1])) {
            sel = 1;
            ci = smooth[1];
            cj = counts[1];
        }
        if (ci < smooth[2] || (ci == smooth[2] && cj <= counts[2])) {
            sel = 2;
            ci = smooth[2];
            cj = counts[2];
        }
        if (ci < smooth[3] || (ci == smooth[3] && cj <= counts[3])) {
            sel = 3;
        }
        if (iter > 0) {
            smooth[sel] = (smooth[sel] + 1) >> 1;
        }
        for (i = 0; i < 4; i++) {
            cSPUIPosse* p = mPosses[i];
            Vec4* r = ((Vec4*(__thiscall*)(void*, Vec4*, int, int, float))
                       (*(void**)(*(char**)p + 0x98)))(p, (Vec4*)0, counts[i], smooth[i], -1.0f);
            widths[i] = r->w - r->z;
            if (fAcc < r->y - r->x) fAcc = r->y - r->x;
            fSumW += r->w - r->z;
        }
        iter++;
    } while (fLimit <= fSumW);

    fSumW = 100.0f;
    for (i = 0; i < 4; i++) {
        cSPUIPosse* p = mPosses[i];
        ((void(__thiscall*)(void*, int, float, int, int))
         (*(void**)(*(char**)p + 0x90)))(p, 0, fSumW, 0, 0);
        ((void(__thiscall*)(void*, float))
         (*(void**)(*(char**)p + 0x94)))(p, fMaxW);
        fSumW += widths[i];
    }

    if (mpGlobalCivUI != 0 && FUN_00e01380(mpGlobalCivUI) != 0) {
        for (i = 0; i < 4; i++) {
            cSPUIPosse* p = mPosses[i];
            if (p != 0) {
                ((void(__thiscall*)(void*, int))
                 (*(void**)(*(char**)p + 0xc0)))(p, p->ItemCount() != 0);
            }
        }
    }
}

// @ 0x00ce9460
void CDS::SetVehicleTask(cGameData* data, cGameData* vehicle)
{
    (void)vehicle;
    CTaskSource* src = (CTaskSource*)((CIcon*)data)->GetTaskSource();
    u32 taskID;
    switch (src->mTask) {
    case 1:
        if (data->mCivIndex == 0) taskID = 0x5d68776;
        else if (data->mCivIndex == 1) taskID = 0x5d687f1;
        else taskID = (data->mCivIndex == 2 ? 0 : 0x14) + 0x5d68802;
        break;
    case 2:  taskID = 0x5d68851; break;
    case 3:  taskID = 0x5d688bc; break;
    case 4:  taskID = 0x5d68bb2; break;
    case 5:  taskID = 0x5d68c25; break;
    case 6:  taskID = 0x6032276; break;
    case 7:  taskID = 0x5d68c7e; break;
    case 8:  taskID = 0x5d68eed; break;
    case 9:
    case 10:
    case 11: taskID = 0x5d68f22; break;
    default:
        ((void(__thiscall*)(cGameData*, int))(*(void**)(*(char**)data + 0xa4)))(data, 0);
        return;
    }
    ((void(__thiscall*)(cGameData*, u32, void*, int))
     (*(void**)(*(char**)data + 0x9c)))(data, taskID, mpPosseIconLayout, 0);
}

// @ 0x00ce9560
void CDS::ResetPosses()
{
    int i;
    for (i = 0; i < 4; i++) {
        cSPUIPosse* p = mPosses[i];
        if (p != 0) {
            p->Refresh();
        }
    }
}

// @ 0x00ce9590
void CDS::UpdateUI(int dummy)
{
    (void)dummy;
    void* civUI = mpGlobalCivUI;
    cTerrainCamera* cam = (cTerrainCamera*)FUN_00b3d280();
    if (civUI == 0 || cam == 0) return;
    void* layout = ((CSPUILayout*)civUI)->GetLayout();
    if (layout == 0) return;

    void* w = ((CSPUILayout*)layout)->FindWindowByID(0x4cab570, 1);
    if (w != 0) {
        void* c = ((void*(__thiscall*)(void*, u32))(*(void**)(*(char**)w + 0xc)))(w, 0x8ed27e7a);
        if (c != 0) {
            u32 v = ((u32(__thiscall*)(void*))(*(void**)(*(char**)c + 0x20)))(c);
            cam->mbFlag14 = (u8)(v >> 1) & 1;
        }
    }
    w = ((CSPUILayout*)layout)->FindWindowByID(0x4cab571, 1);
    if (w != 0) {
        void* c = ((void*(__thiscall*)(void*, u32))(*(void**)(*(char**)w + 0xc)))(w, 0x8ed27e7a);
        if (c != 0) {
            u32 v = ((u32(__thiscall*)(void*))(*(void**)(*(char**)c + 0x20)))(c);
            cam->mbFlag15 = (u8)(v >> 1) & 1;
        }
    }
    w = ((CSPUILayout*)layout)->FindWindowByID(0x4cab56f, 1);
    if (w != 0) {
        void* c = ((void*(__thiscall*)(void*, u32))(*(void**)(*(char**)w + 0xc)))(w, 0x8ed27e7a);
        if (c != 0) {
            u32 v = ((u32(__thiscall*)(void*))(*(void**)(*(char**)c + 0x20)))(c);
            cam->mbFlag17 = (u8)(v >> 1) & 1;
        }
    }
    w = ((CSPUILayout*)layout)->FindWindowByID(0x4cab56e, 1);
    if (w != 0) {
        void* c = ((void*(__thiscall*)(void*, u32))(*(void**)(*(char**)w + 0xc)))(w, 0x8ed27e7a);
        if (c != 0) {
            u32 v = ((u32(__thiscall*)(void*))(*(void**)(*(char**)c + 0x20)))(c);
            cam->mbFlag16 = (u8)(v >> 1) & 1;
        }
    }
}

// @ 0x00ce96b0
void CDS::SetReticlesVisible(u8 visible)
{
    if (mpTargetingReticle != 0) {
        void* p = mpTargetingReticle;
        ((void(__thiscall*)(void*, int))(*(void**)(*(char**)p + 0xc)))(p, visible != 0);
        p = mpTargetingReticle;
        mpTargetingReticle = 0;
        if (p != 0) {
            ((void(__thiscall*)(void*))(*(void**)(*(char**)p + 4)))(p);
        }
    }
    if (mpExtraReticle != 0) {
        void* p = mpExtraReticle;
        ((void(__thiscall*)(void*, int))(*(void**)(*(char**)p + 0xc)))(p, visible != 0);
        p = mpExtraReticle;
        mpExtraReticle = 0;
        if (p != 0) {
            ((void(__thiscall*)(void*))(*(void**)(*(char**)p + 4)))(p);
        }
    }
    if (mpErrorReticle != 0) {
        void* p = mpErrorReticle;
        ((void(__thiscall*)(void*, int))(*(void**)(*(char**)p + 0xc)))(p, visible != 0);
        p = mpErrorReticle;
        mpErrorReticle = 0;
        if (p != 0) {
            ((void(__thiscall*)(void*))(*(void**)(*(char**)p + 4)))(p);
        }
    }
    int i;
    for (i = 0; i < 3; i++) {
        void* snd = mAudioSounds[i];
        void* sys = FUN_00a206f0();
        if (sys != 0) {
            ((void(__thiscall*)(void*, u32))(*(void**)(*(char**)sys + 0x38)))(sys, 0x347536b);
            ((void(__thiscall*)(void*, u32, void*))(*(void**)(*(char**)sys + 0x40)))(sys, 0x3475385, snd);
            ((void(__thiscall*)(void*, u32, int))(*(void**)(*(char**)sys + 0x40)))(sys, 0x34753a0, 1);
            ((void(__thiscall*)(void*))(*(void**)(*(char**)sys + 0x58)))(sys);
        }
    }
}

// @ 0x00ce97e0
void CDS::ShutdownAll()
{
    int i;
    ((CSPUILayout*)mpPosseIconLayout)->Shutdown(1);
    void* layout = mpPosseIconLayout;
    if (layout != 0) {
        mpPosseIconLayout = 0;
        ((void(__thiscall*)(void*))(*(void**)(*(char**)layout + 8)))(layout);
    }
    EffectHandle* e;
    e = (EffectHandle*)mpSelEff0;
    {
        void* mgr = FUN_0067ddd0();
        void* sub = ((void*(__thiscall*)(void*))(*(void**)(*(char**)mgr + 0x5c)))(mgr);
        void* sub2 = ((void*(__thiscall*)(void*))(*(void**)(*(char**)sub + 0x20)))(sub);
        ((void(__thiscall*)(void*, void*))(*(void**)(*(char**)sub2 + 0x1c)))(sub2, e->mpField4);
    }
    e = (EffectHandle*)mpSelEff1;
    {
        void* mgr = FUN_0067ddd0();
        void* sub = ((void*(__thiscall*)(void*))(*(void**)(*(char**)mgr + 0x5c)))(mgr);
        void* sub2 = ((void*(__thiscall*)(void*))(*(void**)(*(char**)sub + 0x20)))(sub);
        ((void(__thiscall*)(void*, void*))(*(void**)(*(char**)sub2 + 0x1c)))(sub2, e->mpField4);
    }
    e = (EffectHandle*)mpSelEff2;
    {
        void* mgr = FUN_0067ddd0();
        void* sub = ((void*(__thiscall*)(void*))(*(void**)(*(char**)mgr + 0x5c)))(mgr);
        void* sub2 = ((void*(__thiscall*)(void*))(*(void**)(*(char**)sub + 0x20)))(sub);
        ((void(__thiscall*)(void*, void*))(*(void**)(*(char**)sub2 + 0x1c)))(sub2, e->mpField4);
    }
    e = (EffectHandle*)mpSelEff3;
    {
        void* mgr = FUN_0067ddd0();
        void* sub = ((void*(__thiscall*)(void*))(*(void**)(*(char**)mgr + 0x5c)))(mgr);
        void* sub2 = ((void*(__thiscall*)(void*))(*(void**)(*(char**)sub + 0x20)))(sub);
        ((void(__thiscall*)(void*, void*))(*(void**)(*(char**)sub2 + 0x1c)))(sub2, e->mpField4);
    }
    e = (EffectHandle*)mpSelEff4;
    {
        void* mgr = FUN_0067ddd0();
        void* sub = ((void*(__thiscall*)(void*))(*(void**)(*(char**)mgr + 0x5c)))(mgr);
        void* sub2 = ((void*(__thiscall*)(void*))(*(void**)(*(char**)sub + 0x20)))(sub);
        ((void(__thiscall*)(void*, void*))(*(void**)(*(char**)sub2 + 0x1c)))(sub2, e->mpField4);
    }
    SetReticlesVisible(1);
    for (i = 0; i < 3; i++) {
        void* snd = mAudioSounds[i];
        if (snd != 0) {
            void* sys = FUN_00a206f0();
            if (sys != 0) {
                ((void(__thiscall*)(void*, void*))(*(void**)(*(char**)sys + 0x2c)))(sys, snd);
            }
            mAudioSounds[i] = 0;
        }
    }
}

// @ 0x00ce9920
int CDS::HandleMessage(int msgID, void* msg)
{
    char* m = (char*)msg;
    void* key = *(void**)(m + 8);
    if (key == 0) return 1;

    if (msgID == 0x3deb129) {
        u8 bDone = 0;
        int idx = 0;
        char* anchor = (char*)this + 0x48;
        do {
            if (bDone) return 1;
            char* end = anchor;
            char* node = *(char**)(end + 4);
            while (node != end && !bDone) {
                if (*(void**)(node + 0x14) == key) {
                    MapValue* vel = *(MapValue**)(node + 0x10);
                    u32 flags = *(u32*)(m + 0x10);
                    void** vt = (void**)vel->mSub34.mpVtbl;
                    u8 b = ((u8(__thiscall*)(void*))vt[0x50 / 4])(&vel->mSub34);
                    u8 bNew = (u8)(flags & 1) != 0;
                    if (bNew) b = (b == 0);
                    bDone = bNew;
                    FUN_00ca3350(&vel->mSub34, bNew);
                    FUN_00bfc5e0(&vel->mField508, (u8)(flags & 2) != 0);
                    FUN_00c9e870(vel, flags);
                    void* cur = FUN_00b30d70();
                    ((void(__thiscall*)(void*))(*(void**)(*(char**)cur + 0x74)))(cur);
                    cur = FUN_00b30d70();
                    ((void(__thiscall*)(void*))(*(void**)(*(char**)cur + 0xc8)))(cur);
                    if (b != 0) {
                        FUN_00e05930(*(void**)((char*)this + 0x2c), -1);
                    }
                    FUN_00cf74d0();
                }
                node = (char*)FUN_00921580(node);
            }
            idx++;
            anchor += 0x1c;
        } while (idx < 4);
        return 1;
    }
    if (msgID == 0x3deb12a) {
        u8 bDone = 0;
        int idx = 0;
        char* anchor = (char*)this + 0x48;
        while (!bDone) {
            char* end = anchor;
            char* node = *(char**)(end + 4);
            for (; node != end; node = (char*)FUN_00921580(node)) {
                if (*(void**)(node + 0x14) == key) {
                    MapValue* vel = *(MapValue**)(node + 0x10);
                    bDone = 1;
                    void* cam = FUN_00b3d280();
                    FUN_00b10260(cam);
                    void** vt = (void**)vel->mSub34.mpVtbl;
                    void* p = ((void*(__thiscall*)(void*, int, int))vt[0x2c / 4])(&vel->mSub34, 1, 1);
                    void* cam2 = FUN_00b3d280();
                    FUN_00b146a0(cam2, (int)p, 1);
                    void* civ = FUN_00cf74c0();
                    FUN_00cf8d70(civ, (void*)0);
                }
            }
            idx++;
            anchor += 0x1c;
            if (idx >= 4) return 1;
        }
        return 1;
    }
    if (msgID == 0x61ed580 && key != 0) {
        cSPUIPosse** posses = (cSPUIPosse**)((char*)this + 0x34);
        int n = 4;
        do {
            cSPUIPosse* p = *posses;
            if (p != 0) {
                if (p == key && p->ItemCount() != (int)FUN_00e23250()) {
                    ((CIcon*)p)->RefreshAlt();
                } else {
                    ((CIcon*)p)->Refresh();
                }
            }
            posses++;
        } while (--n);
        return 1;
    }
    return 1;
}

// @ 0x00ce9b70
void CDS::SelectVehicle(void* vehicle, int flag, int param4)
{
    int i;
    for (i = 0; i < 4; i++) {
        char* anchor = (char*)this + 0x80 + i * 0x1c;
        RefPtr::AddRef(vehicle);
        char* parent = *(char**)(anchor + 8);
        char* best = anchor;
        while (parent != 0) {
            if (*(void**)(parent + 0x10) < vehicle) {
                parent = *(char**)(parent + 4);
            } else {
                best = parent;
                parent = *(char**)(parent);
            }
        }
        char* found = (best != anchor && *(void**)(best + 0x10) <= vehicle) ? best : anchor;
        RefPtr::Release(vehicle);
        if (found != anchor) {
            void* key = *(void**)(found + 0x14);
            void* item = ((CIcon*)mPosses[i])->FindItem(key);
            if (item != 0) {
                if (flag != 0) {
                    ((CIcon*)item)->SetEnabled((u8)param4);
                }
                SetVehicleTask((cGameData*)item, (cGameData*)vehicle);
                FUN_00ce8d00(item, vehicle, 0);
            }
            return;
        }
    }
}

// @ 0x00ce9c30
void CDS::RefreshVehicleIcons(cGameData* vehicle)
{
    int idx = vehicle->mCivIndex;
    if (mPosses[idx] == 0) return;
    char* anchor = (char*)this + idx * 0x1c + 0x80;
    char* node = *(char**)(anchor + 4);
    cPlanetModel_s00ce_90c0* pm;
    for (; node != anchor; node = (char*)FUN_00921580(node)) {
        cGameData* other = *(cGameData**)(node + 0x10);
        void* item = ((CIcon*)mPosses[idx])->FindItem(*(void**)(node + 0x14));
        if (other == 0 || item == 0) continue;
        if (other->mContinent != vehicle->mContinent) continue;
        pm = (cPlanetModel_s00ce_90c0*)FUN_00b3d350();
        if (pm == 0) continue;
        if (other->mContinent == 0) {
            void* ka = ((void*(__thiscall*)(void*))(*(void**)(*(char**)vehicle + 0x2c)))((char*)vehicle + 0x34);
            void* cb = pm->GetContinent(ka);
            void* kb = ((void*(__thiscall*)(void*))(*(void**)(*(char**)other + 0x2c)))((char*)other + 0x34);
            void* cc = pm->GetContinent(kb);
            if (cc != cb) continue;
        }
        ((void(__thiscall*)(void*, int))(*(void**)(*(char**)item + 0xb8)))(item, 2);
    }
}

// @ 0x00ce9d30
void CDS::UpdateVehicleContinent(cGameData* vehicle)
{
    cPlanetModel_s00ce_90c0* pm = (cPlanetModel_s00ce_90c0*)FUN_00b3d350();
    if (pm == 0) return;
    void* cont = pm->GetContinent(vehicle);
    u8 flag = *(u8*)((char*)cont + pm->mContinentFlags);

    int idx;
    for (idx = 0; idx < 4; idx++) {
        cSPUIPosse* posse = mPosses[idx];
        if (posse == 0) continue;
        char* anchor = (char*)this + 0x80 + idx * 0x1c;
        char* node = *(char**)(anchor + 4);
        for (; node != anchor; node = (char*)FUN_00921580(node)) {
            cGameData* other = *(cGameData**)(node + 0x10);
            void* item = ((CIcon*)posse)->FindItem(*(void**)(node + 0x14));
            if (other == 0 || item == 0) continue;
            u32 u = other->mContinent;
            if (u != 2) {
                if (u != (flag == 0)) continue;
                if (u != 2) {
                    void* kb = ((void*(__thiscall*)(void*))(*(void**)(*(char**)other + 0x2c)))((char*)other + 0x34);
                    void* cc = pm->GetContinent(kb);
                    if (cc != cont) continue;
                }
            }
            ((void(__thiscall*)(void*, int))(*(void**)(*(char**)item + 0xb8)))(item, 2);
        }
    }
}

// @ 0x00ce9e20
void CDS::BuildEffectDesc(int type, int variant)
{
    EffectTarget* self = (EffectTarget*)this;
    void* mgr = FUN_0067ddd0();
    void* sub = ((void*(__thiscall*)(void*))(*(void**)(*(char**)mgr + 0x5c)))(mgr);
    void* fx = ((void*(__thiscall*)(void*))(*(void**)(*(char**)sub + 0x20)))(sub);

    EffectDesc desc;
    desc.mbField8 = 0;
    desc.mField18 = 0xffffffff;
    desc.mField1c = 0xffffffff;
    self->mVariant = variant;
    desc.mbFlagF = 0;
    desc.mFloat10 = 0.0f;
    if (type == 2) {
        desc.mId = 0x784c7cc8;
    } else {
        desc.mId = 0xd21f4398;
        if (variant != 0) desc.mId = 0x748de859;
    }
    desc.mbFlagD = (type == 1);
    desc.mField4 = 0;
    desc.mbFlagC = 0;
    desc.mbFlagE = 3;
    ((void(__thiscall*)(void*, EffectTarget*, EffectDesc*, void*))
     (*(void**)(*(char**)fx + 0x18)))(fx, self, &desc, &self->mField4);
    ((void(__thiscall*)(void*, void*, u8))
     (*(void**)(*(char**)fx + 0x10)))(fx, &self->mField8, desc.mbField8);
    desc.mField14 = 0;
    desc.mField18 = 0;
    desc.mField1c = 0;
    void* c = FUN_00ca10a0();
    float fArg = (type == 1) ? 0.5f : 1.0f;
    ((void(__thiscall*)(void*, void*, void*, float))
     (*(void**)(*(char**)fx + 0x20)))(fx, &self->mField4, c, fArg);
    ((void(__thiscall*)(void*, void*, int))
     (*(void**)(*(char**)fx + 0x24)))(fx, &self->mField4, 1);

    float f = (type == 1) ? 0.5f : 1.0f;
    float fv = (f >= 0.0f) ? f : 0.0f;
    float fscaled = fv * 255.0f;
    if (fscaled > 255.0f) fscaled = 255.0f;
    u32 alpha = (u32)(int)fscaled;
    self->mColor = ((alpha & 0xff) << 24) | (0xff << 16) | (0xf2 << 8) | 0x99;
    self->mType = type;
}

// @ 0x00cea030
void* __fastcall FUN_00cea030(void* unused1, void* unused2, void** src)
{
    (void)unused1; (void)unused2;
    char* obj = (char*)FUN_00f473a0(0x18, "Simulator", 0, 0, "c:\\BuildAgent", 0xd1);
    char* base = obj + 0x10;
    if (base != 0) {
        void* p0 = src[0];
        ((void**)base)[0] = p0;
        if (p0 != 0) {
            ((void(__thiscall*)(void*))(*(void**)(*(char**)p0)))(p0);
        }
        void* p1 = src[1];
        ((void**)base)[1] = p1;
        if (p1 != 0) {
            ((void(__thiscall*)(void*))(*(void**)(*(char**)p1)))(p1);
        }
    }
    return obj;
}

// @ 0x00cea090
void CDS_s00ce_a090::Init()
{
    char* self = (char*)this;
    void* obj = FUN_00f473a0(0x18, "Simulator/PosseItemCivIcons", 0, 0, 0, 0);
    void* pNew;
    if (obj != 0) {
        pNew = ((LayoutObj*)obj)->ctor0();
    } else {
        pNew = 0;
    }
    void* old = *(void**)(self + 0xec);
    if (pNew != old) {
        if (pNew != 0) {
            typedef void(__thiscall* AddR)(void*);
            ((AddR)(*(void**)(*(char**)pNew + 4)))(pNew);
        }
        *(void**)(self + 0xec) = pNew;
        if (old != 0) {
            typedef void(__thiscall* Rel)(void*);
            ((Rel)(*(void**)(*(char**)old + 8)))(old);
        }
    }

    void* layout = *(void**)(self + 0xec);
    char ok = ((LayoutObj*)layout)->InitLayout((const void*)0x1477e3c, 0x40464100, 1, 0x5b598fa);
    if (ok) {
        void* l2 = *(void**)(self + 0xec);
        ((LayoutObj*)l2)->SetVis(0);
    }

    ((SelEffObj*)*(void**)(self + 0x10c))->Set(0, 0);
    ((SelEffObj*)*(void**)(self + 0x110))->Set(1, 0);
    ((SelEffObj*)*(void**)(self + 0x114))->Set(2, 0);
    ((SelEffObj*)*(void**)(self + 0x118))->Set(0, 1);
    ((SelEffObj*)*(void**)(self + 0x11c))->Set(1, 1);

    char* arr = self + 0x100;
    int n = 3;
    do {
        void* sys = FUN_00a206f0();
        void* r;
        if (sys != 0) {
            typedef void* (__thiscall* M)(void*);
            r = ((M)(*(void**)(*(char**)sys + 0x24)))(sys);
        } else {
            r = 0;
        }
        *(void**)arr = r;
        arr += 4;
    } while (--n);
}

// @ 0x00cea1a0
void CDS_s00ce_a090::Update()
{
    char* self = (char*)this;
    char* st = (char*)FUN_00cf74f0(FUN_00cf74c0());
    int idx = *(int*)(st + 0x140);
    if (idx == -1) return;

    char* reticle = self + 0xf4;
    void* fx;
    if (*(void**)(self + 0xf4) == 0) {
        fx = FUN_0067ddd0();
        void* cur = *(void**)reticle;
        if (cur != 0) {
            *(void**)reticle = 0;
            typedef void(__thiscall* Rel)(void*);
            ((Rel)(*(void**)(*(char**)cur + 4)))(cur);
        }
        typedef char(__thiscall* Mk)(void*, int, int, void*);
        char ok = ((Mk)(*(void**)(*(char**)fx + 0x2c)))(fx, *(int*)(idx * 4 + 0x1477f40), 0, reticle);
        if (ok) {
            void* e = *(void**)reticle;
            typedef void(__thiscall* P)(void*, int);
            ((P)(*(void**)(*(char**)e + 8)))(e, 0);
        }
    }

    char* reticle2 = self + 0xfc;
    if (*(void**)(self + 0xfc) == 0) {
        fx = FUN_0067ddd0();
        void* cur = *(void**)reticle2;
        if (cur != 0) {
            *(void**)reticle2 = 0;
            typedef void(__thiscall* Rel)(void*);
            ((Rel)(*(void**)(*(char**)cur + 4)))(cur);
        }
        typedef char(__thiscall* Mk)(void*, int, int, void*);
        char ok = ((Mk)(*(void**)(*(char**)fx + 0x2c)))(fx, 0x78beeec5, 0, reticle2);
        if (ok) {
            void* e = *(void**)reticle2;
            typedef void(__thiscall* P)(void*, int);
            ((P)(*(void**)(*(char**)e + 8)))(e, 0);
        }
    }

    if (*(int*)(idx * 4 + 0x1477f10) != 0) {
        char* r3 = self + 0xf8;
        fx = FUN_0067ddd0();
        void* cur = *(void**)r3;
        if (cur != 0) {
            *(void**)r3 = 0;
            typedef void(__thiscall* Rel)(void*);
            ((Rel)(*(void**)(*(char**)cur + 4)))(cur);
        }
        typedef char(__thiscall* Mk)(void*, int, int, void*);
        char ok = ((Mk)(*(void**)(*(char**)fx + 0x2c)))(fx, *(int*)(idx * 4 + 0x1477f40), 0, r3);
        if (ok) {
            void* e = *(void**)r3;
            typedef void(__thiscall* P)(void*, int);
            ((P)(*(void**)(*(char**)e + 8)))(e, 0);
        }
    }

    void* mode = *(void**)st;
    typedef void(__thiscall* GV)(void*);
    int v = (int)(((GV*)(*(void**)((char*)mode + 0x34)))[0], *(void**)((char*)mode + 0x34));
    (void)v;
}

// @ 0x00cea6f0
void CDS_s00ce_a090::Update2(void* a, int b)
{
    int idx;
    char* st = (char*)FUN_00cf74f0(FUN_00cf74c0());
    idx = *(int*)(st + 0x140);
    if (idx == -1) return;
    void* ref = *(void**)(idx * 4 + 0x1477f70);
    if (ref == 0) return;

    char buf[0x10];
    FUN_00bda200(buf, idx, (int*)a);
    void* fx = FUN_0067ddd0();
    typedef char(__thiscall* Mk)(void*, void*, int, void*);
    char ok = ((Mk)(*(void**)(*(char**)fx + 0x2c)))(fx, *(void**)(idx * 4 + 0x1477f70), 0, buf);
    if (!ok) return;
    (void)b;
}

// @ 0x00cea970
void CDS_s00ce_a090::Refresh()
{
    char* self = (char*)this;
    void* cam = FUN_00b3d280();
    if (cam != 0) {
        void* minimap = *(void**)self ? 0 : *(void**)(self + 0xf0);
        (void)minimap;
        if (*(void**)(self + 0xf0) != 0) {
            char tmp[0x10];
            typedef void* (__thiscall* M)(void*, void*);
            char* r = (char*)((M)0xb13900)(cam, tmp);
            typedef void* (__thiscall* M2)(void*);
            void* r2 = ((M2)0xb10200)(cam);
            (void)r; (void)r2;
        }
    }
    void* nm = FUN_00b3d300();
    void* civ = FUN_00b25fb0(nm);
    Update();
    if (*(int*)(self + 0x64) != 0 && civ != 0) {
        float f = *(float*)((char*)civ + 0x98);
        int n = (int)f;
        float fn = (float)n;
        if (f < fn) n -= 1;
        void* v = *(void**)(self + 0x64);
        void* ms = FUN_00cf74c0();
        float r = ((float(__thiscall*)(void*, int))0xcf8e20)(ms, n);
        typedef void(__thiscall* S)(void*, float);
        ((S)0xe04540)(v, r);
    }
    void* posses = self + 0x6c;
    int n = 4;
    do {
        if (*(void**)posses != 0) {
            void* item = FUN_00e24c90(*(void**)posses, 0);
            (void)item;
        }
        posses = (char*)posses + 4;
    } while (--n);
}

// @ 0x00ceaac0
void* CDS_s00ce_a090::RemoveVehicle(void* out, void* node)
{
    char* self = (char*)this;
    (*(int*)(self + 0x14)) -= 1;
    void* volatile next = FUN_00921580(node);
    FUN_00921880(node, self + 4);
    void* p0 = *(void**)((char*)node + 0x14);
    if (p0 != 0) {
        typedef void(__thiscall* Rel)(void*);
        ((Rel)(*(void**)(*(char**)p0 + 4)))(p0);
    }
    void* p1 = *(void**)((char*)node + 0x10);
    if (p1 != 0) {
        typedef void(__thiscall* Rel)(void*);
        ((Rel)(*(void**)(*(char**)p1 + 4)))(p1);
    }
    FUN_00f47380(node);
    void** result = *(void** volatile*)&out;
    *result = next;
    return result;
}

// @ 0x00ceab20
int CDS_s00ce_a090::EraseKey(void* key)
{
    ((RBTH*)this)->Fn(&key, key);
    if (key != (char*)this + 4) {
        char* n = (char*)key;
        RemoveVehicle(&key, n);
        return 1;
    }
    return 0;
}

// @ 0x00ceac50
void CDS_s00ce_a090::Destruct()
{
    char* self = (char*)this;
    *(int*)(self) = 0x1477fa8;
    *(int*)(self + 0x38) = 0x1477fa0;

    if (*(void**)(self + 0x4c) != 0) {
        void* h = *(void**)(self + 0x4c);
        void* a1 = *(void**)(self + 0x5c);
        void* a2 = *(void**)(self + 0x58);
        void* a3 = *(void**)(self + 0x54);
        void* a4 = *(void**)(self + 0x50);
        *(void**)(self + 0x4c) = 0;
        ((void(__cdecl*)(void*, void*, void*, void*, void*))0x571db0)(h, a4, a3, a2, a1);
    }

    if (*(void**)(self + 0x64) != 0) {
        void* p = *(void**)(self + 0x64);
        typedef void(__thiscall* M)(void*);
        ((M)(*(void**)(*(char**)p + 0xc)))(p);
        p = *(void**)(self + 0x64);
        if (p != 0) {
            char* sub = (char*)p + 0x68;
            *(void**)(self + 0x64) = 0;
            typedef void(__thiscall* M2)(void*);
            ((M2)(*(void**)(*(char**)sub + 8)))(sub);
        }
    }

    char* posses = self + 0x6c;
    char* maps = self + 0x80;
    int n = 4;
    do {
        if (*(void**)posses != 0) {
            void* p = *(void**)posses;
            typedef void(__thiscall* M)(void*);
            ((M)(*(void**)(*(char**)p + 0x88)))(p);
            p = *(void**)posses;
            if (p != 0) {
                *(void**)posses = 0;
                typedef void(__thiscall* Rel)(void*);
                ((Rel)(*(void**)(*(char**)p + 4)))(p);
            }
        }
        FUN_00f240d0(maps - 4, *(int**)(maps + 8));
        *(void**)(maps) = maps;
        *(void**)(maps + 4) = maps;
        *(int*)(maps + 8) = 0;
        *(uint8_t*)(maps + 0xc) = 0;
        *(int*)(maps + 0x10) = 0;
        posses += 4;
        maps += 0x1c;
    } while (--n);

    if (*(void**)0x169ba4c == self) *(void**)0x169ba4c = 0;

    if (*(void**)(self + 0x10c) != 0) {
        void* p = *(void**)(self + 0x10c);
        typedef void(__thiscall* M)(void*, int);
        ((M)(*(void**)(*(char**)p + 4)))(p, 1);
    }
    if (*(void**)(self + 0x110) != 0) {
        void* p = *(void**)(self + 0x110);
        typedef void(__thiscall* M)(void*, int);
        ((M)(*(void**)(*(char**)p + 4)))(p, 1);
    }
    if (*(void**)(self + 0x114) != 0) {
        void* p = *(void**)(self + 0x114);
        typedef void(__thiscall* M)(void*, int);
        ((M)(*(void**)(*(char**)p + 4)))(p, 1);
    }
    if (*(void**)(self + 0x118) != 0) {
        void* p = *(void**)(self + 0x118);
        typedef void(__thiscall* M)(void*, int);
        ((M)(*(void**)(*(char**)p + 4)))(p, 1);
    }
    if (*(void**)(self + 0x11c) != 0) {
        void* p = *(void**)(self + 0x11c);
        typedef void(__thiscall* M)(void*, int);
        ((M)(*(void**)(*(char**)p + 4)))(p, 1);
    }
    if (*(void**)(self + 0xfc) != 0) {
        void* p = *(void**)(self + 0xfc);
        typedef void(__thiscall* M)(void*);
        ((M)(*(void**)(*(char**)p + 4)))(p);
    }
    if (*(void**)(self + 0xf8) != 0) {
        void* p = *(void**)(self + 0xf8);
        typedef void(__thiscall* M)(void*);
        ((M)(*(void**)(*(char**)p + 4)))(p);
    }
    if (*(void**)(self + 0xf4) != 0) {
        void* p = *(void**)(self + 0xf4);
        typedef void(__thiscall* M)(void*);
        ((M)(*(void**)(*(char**)p + 4)))(p);
    }
    if (*(void**)(self + 0xf0) != 0) {
        void* p = *(void**)(self + 0xf0);
        typedef void(__thiscall* M)(void*);
        ((M)(*(void**)(*(char**)p + 4)))(p);
    }
    if (*(void**)(self + 0xec) != 0) {
        void* p = *(void**)(self + 0xec);
        typedef void(__thiscall* M)(void*);
        ((M)(*(void**)(*(char**)p + 8)))(p);
    }

    char* e = self + 0xec;
    int k = 3;
    do {
        e -= 0x1c;
        FUN_00f240d0(e, *(int**)(e + 0x10));
    } while (--k >= 0);

    char* v = self + 0x7c;
    int m = 3;
    do {
        v -= 4;
        if (*(void**)v != 0) {
            void* p = *(void**)v;
            typedef void(__thiscall* Rel)(void*);
            ((Rel)(*(void**)(*(char**)p + 4)))(p);
        }
    } while (--m >= 0);

    if (*(void**)(self + 0x64) != 0) {
        void* p = *(void**)(self + 0x64);
        char* sub = (char*)p + 0x68;
        typedef void(__thiscall* M)(void*);
        ((M)(*(void**)(*(char**)sub + 8)))(sub);
    }

    if (*(void**)(self + 0x4c) != 0) {
        void* h = *(void**)(self + 0x4c);
        void* a1 = *(void**)(self + 0x5c);
        void* a2 = *(void**)(self + 0x58);
        void* a3 = *(void**)(self + 0x54);
        void* a4 = *(void**)(self + 0x50);
        *(void**)(self + 0x4c) = 0;
        ((void(__cdecl*)(void*, void*, void*, void*, void*))0x571db0)(h, a4, a3, a2, a1);
    }

    *(int*)(self + 0x38) = 0x13eb394;
    FUN_00af1430(self);
}

// @ 0x00ceae70
void CDS_s00ce_a090::Assign(void* other)
{
    (void)other;
    void* gm = (void*)0x1654c04;
    if (((void* (*)())0xb5b800)() != gm) return;
    char* self = (char*)this;
    char* o = (char*)other;
    typedef char(__thiscall* IsX)(void*);
    char al = ((IsX)(*(void**)(*(char**)(o + 0x34) + 0x58)))(o + 0x34);
    int idx = *(int*)(o + 0xb20);
    if (*(void**)(self + idx * 4 + 0x6c) == 0) return;
    if (!al) return;
    (void)idx;
}

// @ 0x00ceaf70
void* __cdecl FUN_00ceaf70(void* self, void* a, void* b)
{
    char* s = (char*)self;
    void* end = *(void**)(s + 4);
    void* from = a;
    if (end == *(void**)(s + 8)) {
        // need to grow
        int cur = (int)end - *(int*)(s);
        (void)cur;
    }
    {
        char* dest = (char*)end + 0x38;
        (void)dest;
    }
    if (end != *(void**)(s + 8)) {
        void* src = b;
        if ((char*)b >= (char*)a && (char*)b < (char*)end) src = (char*)b + 0x38;
        if (end != 0) FUN_0040ce80((char*)end - 0x38);
        void* e2 = *(void**)(s + 4);
        FUN_00f33a80(e2, (char*)e2 - 0x38, from);
        FUN_00537dc0(a, src);
        *(void**)(s + 4) = (char*)(*(void**)(s + 4)) + 0x38;
        return a;
    }
    return 0;
}

// @ 0x00ceb090
void* CDS_s00ce_a090::ctor(void* a)
{
    char* self = (char*)this;
    ((TimerOwnerObj*)self)->Ctor();
    *(volatile int*)(self + 0x38) = 0x13eb394;
    *(int*)(self) = 0x1477fa8;
    *(int*)(self + 0x38) = 0x1477fa0;
    *(char*)(self + 0x3c) = 0;
    *(int*)(self + 0x40) = 0;
    *(int*)(self + 0x44) = 0;
    *(int*)(self + 0x48) = -1;
    *(int*)(self + 0x4c) = 0;
    *(int*)(self + 0x50) = 0;
    *(int*)(self + 0x54) = 0;
    *(int*)(self + 0x58) = 0;
    *(int*)(self + 0x5c) = 0;
    *(void**)(self + 0x60) = a;
    *(int*)(self + 0x64) = 0;
    *(int*)(self + 0x68) = 0;
    *(int*)(self + 0x6c) = 0;
    *(int*)(self + 0x70) = 0;
    *(int*)(self + 0x74) = 0;
    *(int*)(self + 0x78) = 0;

    char* m = self + 0x80;
    int n = 3;
    do {
        *(int*)(m + 0xc) = 0;
        *(void**)(m) = m;
        *(void**)(m + 4) = m;
        *(int*)(m + 8) = 0;
        *(char*)(m + 0xc) = 0;
        *(int*)(m + 0x10) = 0;
        m += 0x1c;
    } while (--n >= 0);

    *(int*)(self + 0xec) = 0;
    *(int*)(self + 0xf0) = 0;
    *(int*)(self + 0xf4) = 0;
    *(int*)(self + 0xf8) = 0;
    *(int*)(self + 0xfc) = 0;
    *(int*)(self + 0x10c) = 0;
    *(int*)(self + 0x110) = 0;
    *(int*)(self + 0x118) = 0;
    *(int*)(self + 0x11c) = 0;

    void* ms = FUN_0067dcc0();
    void* handler = self + 0x38;
    *(void**)(self + 0x4c) = ms;
    *(void**)(self + 0x50) = handler;
    *(int*)(self + 0x54) = 0x1477fb0;
    *(int*)(self + 0x58) = 3;
    *(int*)(self + 0x5c) = 0;
    if (ms != 0 && handler != 0) {
        int off = 0;
        do {
            void* id = *(void**)(off + 0x1477fb0);
            void* h2 = self + 0x38;
            typedef void(__thiscall* Sub)(void*, void*, void*);
            ((Sub)(*(void**)(*(char**)ms + 0x24)))(ms, h2, id);
            off += 4;
        } while (off < 0xc);
    }

    float c = *(float*)0x146138c;
    void* el = FUN_00b3d3e0();
    *(void**)0x169ba4c = self;
    ((EventLogObj*)el)->Apply(0.0f, c);

    void* o0 = FUN_00f473a0(0x18, "Simulator/cSelectionEffectStreamer", 0, 0, 0, 0);
    if (o0 != 0) *(int*)((char*)o0) = 0x1477e30;
    *(void**)(self + 0x10c) = o0;
    void* o1 = FUN_00f473a0(0x18, "Simulator/cSelectionEffectStreamer", 0, 0, 0, 0);
    if (o1 != 0) *(int*)((char*)o1) = 0x1477e30;
    *(void**)(self + 0x110) = o1;
    void* o2 = FUN_00f473a0(0x18, "Simulator/cSelectionEffectStreamer", 0, 0, 0, 0);
    if (o2 != 0) *(int*)((char*)o2) = 0x1477e30;
    *(void**)(self + 0x114) = o2;
    void* o3 = FUN_00f473a0(0x18, "Simulator/cSelectionEffectStreamer", 0, 0, 0, 0);
    if (o3 != 0) *(int*)((char*)o3) = 0x1477e30;
    *(void**)(self + 0x118) = o3;
    void* o4 = FUN_00f473a0(0x18, "Simulator/cSelectionEffectStreamer", 0, 0, 0, 0);
    if (o4 != 0) *(int*)((char*)o4) = 0x1477e30;
    *(void**)(self + 0x11c) = o4;

    *(int*)(self + 0x100) = 0;
    *(int*)(self + 0x104) = 0;
    *(int*)(self + 0x108) = 0;
    return self;
}

// @ 0x00ceb710
void cBillboardRenderer::Render(IVertexSink* sink)
{
    GameState* gs = FUN_00b3d4d0();
    if (gs->m_mode == 1 || gs->m_mode == 2)
        return;

    cPlanetModel* planet = PlanetModel();
    bool terrainMode = (GetCurrentGameMode() == kGameModeTerrain);
    bool hasCamera = false;

    TransformVec transforms;
    transforms.m_begin = transforms.m_end = transforms.m_buf;
    transforms.m_cap = transforms.m_buf + 64;
    transforms.m_fixed = transforms.m_buf;

    FloatVec alphas;
    alphas.m_begin = alphas.m_end = alphas.m_buf;
    alphas.m_cap = alphas.m_buf + 64;
    alphas.m_fixed = alphas.m_buf;

    Vector3 camPos = g_vecDefault;
    Vector3 camDir = g_vecDefault;

    cViewer* viewer = App()->GetLayer()->GetViewer();
    if (viewer) {
        viewer->GetCameraLocationInfo(&camPos, &camDir, 0, 0);
        hasCamera = true;
    }

    ObjectVec objects;
    objects.m_begin = objects.m_end = objects.m_buf;
    objects.m_cap = objects.m_buf + 64;
    objects.m_zero = 0;
    GetGameTerrainCursor()->GetObjects(&objects);

    for (cSpatialObject** it = objects.m_begin; it != objects.m_end; ++it) {
        cSpatialObject* obj = *it;
        if (!obj) continue;

        bool alt = false;
        void* q = obj->QueryInterface(0x17f243b);
        if (q && ((cSpatialObject*)q)->GetTypeId() == kTypeIdPlanet) {
            cSpatialObjectComponent* c = (cSpatialObjectComponent*)obj->QueryInterface(0x137e8e0);
            alt = (c->m_state == 2);
        }
        if (alt != (m_mode == 2)) continue;

        float dist = obj->DistanceToCamera();
        if (m_fadeMode == 0 && dist > 300.0f) continue;
        if (m_fadeMode == 1 && 200.0f > dist) continue;

        if (alt && hasCamera) {
            // Camera-oriented orientation from the object position and camera.
            const Vector3* pp = obj->GetPosition();
            Vector3 pos = *pp;
            Vector3 n1;
            normalized_safe(&n1, &pos);
            if ((n1.x * camDir.x + camDir.y * n1.y) + camDir.z * n1.z > 0.0f) continue;

            transforms.push_back_default();
            Transform* t = transforms.m_end - 1;
            Vector3 d = { camPos.x - pos.x, camPos.y - pos.y, camPos.z - pos.z };
            Vector3 n2;
            normalized_safe(&n2, &d);
            Vector3 c1 = { n1.y * n2.z - n1.z * n2.y, n1.z * n2.x - n1.x * n2.z, n1.x * n2.y - n1.y * n2.x };
            Vector3 c1n;
            normalized_safe(&c1n, &c1);
            Vector3 c2 = { c1n.z * n2.y - c1n.y * n2.z, c1n.x * n2.z - n2.x * c1n.z, n2.x * c1n.y - c1n.x * n2.y };
            Vector3 c2n;
            normalized_safe(&c2n, &c2);
            Matrix3 m;
            const Matrix3* r = Matrix3FromFacingAndUp(&m, &c2n, &n2);
            t->m_rot = *r;
            t->m_flags |= 6;
            t->m_count += 2;
            t->m_offset = pos;
            float sc = obj->GetScale();
            t->m_count += 1;
            t->m_scale = sc;
            float one = 1.0f;
            alphas.push_back(one);
            continue;
        }

        // General case.
        const Vector3* pp = obj->GetPosition();
        Vector3 dirTmp, up;
        const Vector3* dp;
        if (terrainMode && obj->m_isPlanetSurface) {
            dp = planet->FUN_00b7e3b0(&dirTmp, pp);
        } else {
            float x = pp->x, y = pp->y, z = pp->z;
            float inv = (float)(1.0 / sqrt((double)(z * z + (y * y + x * x) + 1e-08f)));
            dirTmp.x = inv * x; dirTmp.y = inv * y; dirTmp.z = inv * z;
            dp = &dirTmp;
        }
        up.x = dp->x; up.y = dp->y; up.z = dp->z;

        Vector3 facing;
        if (!hasCamera) {
            Vector3 tmp2;
            const Vector3* fp = obj->GetDirection(&tmp2);
            facing.x = fp->x; facing.y = fp->y; facing.z = fp->z;
        } else {
            if ((camDir.z * up.z + camDir.y * up.y) + camDir.x * up.x > 0.0f) continue;
            Vector3 d = { camPos.x - pp->x, camPos.y - pp->y, camPos.z - pp->z };
            Vector3 n;
            const Vector3* np = normalized_safe(&n, &d);
            float dd = (np->y * up.y + np->z * up.z) + up.x * np->x;
            facing.x = np->x - dd * up.x;
            facing.y = np->y - dd * up.y;
            facing.z = np->z - dd * up.z;
        }

        transforms.push_back_default();
        Transform* t = transforms.m_end - 1;
        Matrix3 m;
        const Matrix3* r = Matrix3FromFacingAndUp(&m, &facing, &up);
        t->m_rot = *r;
        t->m_flags |= 2;
        t->m_count += 1;

        if (!terrainMode) {
            Vector3 off = { pp->x + up.x * 0.5f, pp->y + up.y * 0.5f, pp->z + up.z * 0.5f };
            t->m_offset = off;
            t->m_flags |= 4;
            t->m_count += 1;
            float sc = obj->GetScale() * 1.5f;
            t->m_count += 1;
            t->m_scale = sc;
        } else {
            float sc = obj->GetScale() * 1.5f;
            t->m_count += 1;
            t->m_scale = sc;
            float s = obj->DistanceToCamera() * 0.010000001f;
            s = _mm_cvtss_f32(_mm_min_ss(_mm_max_ss(_mm_set_ss(s), _mm_set_ss(0.1f)), _mm_set_ss(0.5f)));
            Vector3 off = { pp->x + s * up.x, pp->y + s * up.y, pp->z + s * up.z };
            t->m_flags |= 4;
            t->m_count += 1;
            t->m_offset = off;
        }

        float fade = 1.0f;
        if (m_fadeMode == 0 && dist > 200.0f)
            fade = 1.0f - (dist - 200.0f) * 0.01f;
        else if (m_fadeMode == 1 && 300.0f > dist)
            fade = (dist - 200.0f) * 0.01f;
        if (alphas.m_end < alphas.m_cap) {
            if (alphas.m_end) *alphas.m_end = fade;
            alphas.m_end++;
        } else {
            alphas.grow_push_back(alphas.m_end, fade);
        }
    }

    // ---- emit one quad per transform ----
    if (transforms.m_begin != transforms.m_end) {
        int total = (int)(transforms.m_end - transforms.m_begin);
        int i = 0;
        while (i < total) {
            char* vb;
            int stride;
            int got = sink->Lock(total - i, &vb, &stride);
            if (!got) break;
            int limit = got + i;
            for (; i < limit; ++i) {
                const Transform* t = &transforms.m_begin[i];
                float zero = 0.0f, one = 1.0f;
                Vector3 A = { one, zero, zero };
                Vector3 B = { zero, one, zero };
                if (t->m_flags & 2) {
                    const float* mm = t->m_rot.m;
                    A.y = (mm[7] + mm[4]) * zero + mm[1];
                    A.x = (mm[6] + mm[3]) * zero + mm[0];
                    A.z = (mm[8] + mm[5]) * zero + mm[2];
                    B.x = (mm[6] + mm[0]) * zero + mm[3];
                    B.y = (mm[7] + mm[1]) * zero + mm[4];
                    B.z = (mm[8] + mm[2]) * zero + mm[5];
                }
                float s = t->m_scale;
                A.x *= s; A.y *= s; A.z *= s;
                B.x *= s; B.y *= s; B.z *= s;

                float a = alphas.m_begin[i];
                if (m_mode == 1) a *= 0.5f;
                uint32_t color = (((ColorByte(a) << 8 | ColorByte(1.0f)) << 8 | ColorByte(0.95f)) << 8) | ColorByte(0.6f);

                float px = t->m_offset.x, py = t->m_offset.y, pz = t->m_offset.z;
                float lx = px - A.x, ly = py - A.y, lz = pz - A.z;   // P - A
                float rx = px + A.x, ry = py + A.y, rz = pz + A.z;   // P + A
                static const float uv[4][2] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
                float vx[4] = { lx - B.x, rx - B.x, rx + B.x, lx + B.x };
                float vy[4] = { ly - B.y, ry - B.y, ry + B.y, ly + B.y };
                float vz[4] = { lz - B.z, rz - B.z, rz + B.z, lz + B.z };
                for (int k = 0; k < 4; ++k) {
                    float* pos = (float*)(vb + m_posOffset);
                    pos[0] = vx[k]; pos[1] = vy[k]; pos[2] = vz[k];
                    *(uint32_t*)(vb + m_colorOffset) = color;
                    ((float*)(vb + m_uvOffset))[0] = uv[k][0];
                    ((float*)(vb + m_uvOffset))[1] = uv[k][1];
                    vb += stride;
                }
            }
            sink->Unlock();
        }
    }

    // ---- cleanup of the three containers ----
    for (cSpatialObject** p = objects.m_begin; p < objects.m_end; ++p)
        if (*p) (*p)->Release();
    if (objects.m_begin && ((int*)objects.m_begin)[-1] != 0)
        operator delete[](objects.m_begin);
    if (alphas.m_begin && alphas.m_begin != alphas.m_fixed)
        operator delete[](alphas.m_begin);
    if (transforms.m_begin && transforms.m_begin != transforms.m_fixed)
        operator delete[](transforms.m_begin);
}

// @ 0x00cec6d0
namespace Simulator {
void cCityDisplayStrategy_s00ce_c6d0::FUN_00cec6d0()
{
    if (mMiniMapWin.mpObject == 0)
        return;

    cGameNounManager_s00ce_c6d0* pManager = NounManager();
    cGameDataVector* pVehicles = pManager->GetGameDataVector(&g_funCD7D10, &g_funD3D420,
                                                             &g_funAE5EA0, &g_funB1E500,
                                                             &g_classKey403df5c);
    cNounPtrVector* pVector = &pVehicles->mVector;
    cNounPtrVector local;
    local.Resize((int32_t)(pVector->mpEnd - pVector->mpBegin), &pVector->mAllocator);

    void** ppCopiedEnd = local.mpBegin;
    _Construct(&ppCopiedEnd, pVector->mpBegin, pVector->mpEnd, local.mpBegin, ppCopiedEnd);

    for (void** pp = local.mpBegin; pp != ppCopiedEnd; ++pp)
        FUN_00ce8f70(*pp, mMiniMapWin.mpObject);

    for (void** pp = local.mpBegin; pp < ppCopiedEnd; ++pp)
    {
        cRefObject* pObject = (cRefObject*)*pp;
        if (pObject != 0)
            pObject->Release();
    }

    // the allocator counts its live blocks in the word in front of the buffer
    if (local.mpBegin != 0 && ((uint32_t*)local.mpBegin)[-1] != 0)
        operator_delete(local.mpBegin);
}
}  // namespace Simulator

// @ 0x00cec7a0
namespace Simulator {
void cCityDisplayStrategy_s00ce_c6d0::DestroyAndRecreateCivUI(uint8_t bBuild)
{
    // tear the current civ UI down: its panels first, then the window's listener
    cGlobalCivUI* pCivUI = (cGlobalCivUI*)mGlobalCivUI.mpObject;
    if (pCivUI != 0)
    {
        pCivUI->Shutdown();
        pCivUI = (cGlobalCivUI*)mGlobalCivUI.mpObject;
        if (pCivUI != 0)
        {
            mGlobalCivUI.mpObject = 0;
            pCivUI->mListener.Release();
        }
    }

    // the four posses and their lookup trees
    for (int32_t i = 0; i < 4; ++i)
    {
        cPosseWindow* pPosse = (cPosseWindow*)mPosses[i].mpObject;
        if (pPosse != 0)
        {
            pPosse->DestroyPosseBar();
            if (mPosses[i].mpObject != 0)
            {
                mPosses[i].mpObject = 0;
                pPosse->Release();
            }
        }

        EventTree& rTree = mVehiclePosseMaps[i];
        rTree.Destroy(rTree.mpRoot);
        void* pAnchor = &rTree.mpAnchorLeft;
        rTree.mpAnchorLeft = pAnchor;
        rTree.mpAnchorRight = pAnchor;
        rTree.mpRoot = 0;
        rTree.mbColor = 0;
        rTree.mnSize = 0;
    }

    if (bBuild == 0)
        return;

    // the four posse bar labels, resolved through the localised text table
    SP::cString_s00ce_c6d0 kMilitary(0xbeb528cb, 0x4d175ca, L"!!!Military");
    SP::cString_s00ce_c6d0 kReligious(0xbeb528cb, 0x4d175cb, L"!!!Religious");
    SP::cString_s00ce_c6d0 kEconomic(0xbeb528cb, 0x4d175cc, L"!!!Economic");
    SP::cString_s00ce_c6d0 kHarvester(0xbeb528cb, 0x4d175cd, L"!!!Harvester");

    const wchar_t* apBarText[4];
    apBarText[0] = kMilitary.GetText();
    apBarText[1] = kReligious.GetText();
    apBarText[2] = kEconomic.GetText();
    apBarText[3] = kHarvester.GetText();

    // one bar per political category
    for (int32_t i = 0; i < 4; ++i)
    {
        cPosseWindow* pNew = (cPosseWindow*)FUN_009512d0(0x20c, 4, "UI/Posse", FUN_009512c0());
        if (pNew != 0)
            pNew = pNew->PosseCtor();

        cPosseWindow* pOld = (cPosseWindow*)mPosses[i].mpObject;
        if (pNew != pOld)
        {
            if (pNew != 0)
                pNew->AddRef();
            mPosses[i].mpObject = (cRefObject*)pNew;
            if (pOld != 0)
                pOld->Release();
        }

        cPosseWindow* pBar = (cPosseWindow*)mPosses[i].mpObject;
        if (!pBar->BindPosseBar(L"PosseBar", 3.1251f))
        {
            if (mPosses[i].mpObject != 0)
            {
                mPosses[i].mpObject = 0;
                pBar->Release();
            }
        }
        else
        {
            pBar->SetText(apBarText[i]);
            ((cPosseWindow*)mPosses[i].mpObject)->SetMode(2);
        }
    }

    RebuildPosseBars();

    cGameDataVector* pCityObjects = NounManager()->GetGameDataVector(&g_funCD7D10, &g_funD3D420,
                                                                     &g_funACDFF0, &g_funB1E500,
                                                                     &g_classKey18c43e8);

    // the global civ UI window, created on first use
    if (mGlobalCivUI.mpObject == 0)
    {
        cGlobalCivUI* pNew = (cGlobalCivUI*)operator new(0xf8, "Simulator/cSPGlobalUI-CivUI",
                                                         0, 0, 0, 0);
        if (pNew != 0)
            pNew = (cGlobalCivUI*)FUN_00e057a0(pNew);

        cGlobalCivUI* pOld = (cGlobalCivUI*)mGlobalCivUI.mpObject;
        if (pNew != pOld)
        {
            if (pNew != 0)
                pNew->mListener.AddRef();
            mGlobalCivUI.mpObject = (cRefObject*)pNew;
            if (pOld != 0)
                pOld->mListener.Release();
        }
        ((cGlobalCivUI*)mGlobalCivUI.mpObject)->Init(&g_classKey403df5c);
    }

    // the minimap window, sized from the civ UI's map rect
    cWindowObject* pCivWindow = ((cGlobalCivUI*)mGlobalCivUI.mpObject)->FindWindowByID(0x190722e);
    fRect* pMapRect = pCivWindow->GetRect();
    fRect afRect;
    afRect.fLeft = pMapRect->fLeft;
    afRect.fTop = pMapRect->fTop;
    afRect.fRight = pMapRect->fRight;
    afRect.fBottom = pMapRect->fBottom;

    cMinimapWindow* pNewMap = (cMinimapWindow*)FUN_009512d0(0x9a8, 8, "UI/CivMinimap",
                                                            FUN_009512c0());
    if (pNewMap != 0)
    {
        fVector2 fMin;
        fMin.fx = 0.0f;
        fMin.fy = 0.0f;
        fVector2 fMax;
        fMax.fx = -1.0f;
        fMax.fy = 1.0f;
        pNewMap = pNewMap->MinimapCtor((int32_t)(afRect.fRight - afRect.fLeft),
                                       (int32_t)(afRect.fBottom - afRect.fTop),
                                       &fMin, &fMax, 0, 0);
    }

    cMinimapWindow* pOldMap = (cMinimapWindow*)mMiniMapWin.mpObject;
    if (pNewMap != pOldMap)
    {
        if (pNewMap != 0)
            pNewMap->AddRef();
        mMiniMapWin.mpObject = (cRefObject*)pNewMap;
        if (pOldMap != 0)
            pOldMap->Release();
    }

    void* pIWindow = 0;
    if (mMiniMapWin.mpObject != 0)
        pIWindow = &((cMinimapWindow*)mMiniMapWin.mpObject)->mWindowInterface;
    pCivWindow->SetChildWindow(pIWindow);

    if (mMiniMapWin.mpObject != 0)
    {
        if (g_pSimSingleton == 0)
        {
            cSimSingleton* pSingleton = (cSimSingleton*)operator new(0xc8, "Simulator/SimSingleton",
                                                                     0, 0, 0, 0);
            if (pSingleton != 0)
                pSingleton = pSingleton->SimSingletonCtor();
            g_pSimSingleton = pSingleton;
        }

        // aim the minimap at the direction the player's tribe looks in
        cLookAt* pLookAt;
        if (*g_pSimSingleton->mpPlayerTribeId == -1)
        {
            cTribeObject* pTribe = (cTribeObject*)NounManager()->SetGameDataOwner2();
            if (pTribe != 0)
                pLookAt = &pTribe->mLookAt;
            else
                pLookAt = &((cTribeObject*)FUN_00b25c30(NounManager()))->mLookAt;
        }
        else
        {
            pLookAt = &((cTribeView*)FUN_00b993c0(*g_pSimSingleton->mpPlayerTribeId))->mLookAt;
        }

        fVector3* pView = pLookAt->PointAt();
        fVector3 afDir;
        afDir.fx = pView->fx;
        afDir.fy = pView->fy;
        float fScale = (float)(1.0 / sqrt(afDir.fy * afDir.fy + afDir.fx * afDir.fx + 1e-08f));
        afDir.fx = fScale * afDir.fx;
        afDir.fy = afDir.fy * fScale;
        afDir.fz = fScale * g_fRealZero;

        cMinimapWindow* pMap = (cMinimapWindow*)mMiniMapWin.mpObject;
        pMap->SetDirection(afDir);
        pMap->mfAngles[0] = 0.0f;
        pMap->mfAngles[1] = 0.0f;
        pMap->mfAngles[2] = g_fRealOne;
        pMap->SetViewMode(4);
        pMap->Refresh();

        // refresh every city object and vehicle the new map covers
        for (void** pp = pCityObjects->mVector.mpBegin; pp != pCityObjects->mVector.mpEnd; ++pp)
            RefreshCityObject(*pp);

        cGameDataVector* pVehicleNouns = NounManager()->GetGameDataVector(&g_funCD7D10,
                                                                          &g_funD3D420,
                                                                          &g_funAE72D0,
                                                                          &g_funB1E500,
                                                                          &g_classKey18c6de8);
        for (void** pp = pVehicleNouns->mVector.mpBegin; pp != pVehicleNouns->mVector.mpEnd; ++pp)
        {
            if (mMiniMapWin.mpObject != 0)
                NoteVehicleAdded(*pp);
        }
    }
}
}  // namespace Simulator
