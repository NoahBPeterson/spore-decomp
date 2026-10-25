// src/game/SPGonzago/SPCommunityEditor.cpp -- migrated from slice(s) s00d130d0, s00d124e0, s00d10840, s00d0e170, s00d0d0e0, s00d0c010, s00d0b090, s00d0a160, s00d091c0, s00d084d0, s00bf4170, s00afab70, s004215f0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCommunityEditor.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <intrin.h>
#include "EA/Random/RandomLinearCongruential.h"
#include "SP/cPlanetModel.h"
#include <math.h>
#include "SP/cCity.h"
#include "SP/cGameData.h"
#include "SP/cGameNounManager.h"
#include "SP/cTerrainSphere.h"
#include "SP/cString.h"
#include "SP/cCivilization.h"
#include "SP/cCommunity.h"
#include "SP/cEmpire.h"
#include "SP/cSPGameDataUFO.h"
#include "SP/cSPPaletteUI.h"
#include "SP/cSpatialObject.h"
#include <stddef.h>
#include "SP/cSPPaletteItem.h"
#include "cSPUILayout.h"
#include "SP/cSPEditorBudget.h"
#include <float.h>
#include "SP/cCombatant.h"
#include "SP/cSPEditorSellBackRollover.h"
#include "SP/cTribe.h"
#include "SP/cBuilding.h"
#include "SP/cEditorResource.h"
#include "SP/cPlanet.h"
#include "SP/cRotationRing.h"
#include "SP/cTribeTool.h"
#include "SP/cVehicle.h"

// ---- items of slice s004215f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Unknown { virtual void v0(); virtual void v1(); virtual void v2(); virtual void* Query(uint32_t iid); };
// ---- items of slice s004215f0 end

// ---- items of slice s00afab70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_fFLTMax;        // 0x145c45c = FLT_MAX
namespace EA {
class IRefCounted {
 public:
  virtual int AddRef();
  virtual int Release();
};
}
namespace EA {
template <class T>
class AutoRefCount_s00af_ab70 {
 public:
  T* mpObject;
  AutoRefCount_s00af_ab70() : mpObject(0) {}
  AutoRefCount_s00af_ab70(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  AutoRefCount_s00af_ab70(const AutoRefCount_s00af_ab70& o) : mpObject(o.mpObject) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount_s00af_ab70() { if (mpObject) mpObject->Release(); }
  AutoRefCount_s00af_ab70& operator=(T* p) {
    if (p != mpObject) {
      T* const old = mpObject;
      if (p) p->AddRef();
      mpObject = p;
      if (old) old->Release();
    }
    return *this;
  }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};
}
namespace SP {
struct cSPVector3_s00af_ab70 { float mX, mY, mZ; };
}
namespace SP {
struct cSPQuaternion { float x, y, z, w; };
}
namespace SP {
class cGameData_s00af_ab70 : public EA::IRefCounted {};
}
namespace SP {
class cInteractionAgent_s00af_ab70 : public EA::IRefCounted {};
}
namespace SP {
class cActionCircle_s00af_ab70 {
 public:
  class tSlot {
   public:
    bool mOccupied;                                 // +0x0
    char _pad0[3];
    EA::AutoRefCount_s00af_ab70<cGameData_s00af_ab70> mpReservingNoun;    // +0x4
    unsigned int mReservingId;                      // +0x8
    cSPVector3_s00af_ab70 mPos;                                // +0xc

    void Clear() {
      *(volatile bool*)&mOccupied = false;
      *(volatile unsigned int*)&mReservingId = 0;
      cGameData_s00af_ab70* old = *(cGameData_s00af_ab70* volatile*)&mpReservingNoun.mpObject;
      mpReservingNoun.mpObject = (cGameData_s00af_ab70*)0;
      if (old) old->Release();
    }
  };

  struct AgentVector {
    EA::AutoRefCount_s00af_ab70<cInteractionAgent_s00af_ab70>* mpBegin;   // +0x0
    EA::AutoRefCount_s00af_ab70<cInteractionAgent_s00af_ab70>* mpEnd;     // +0x4
    EA::AutoRefCount_s00af_ab70<cInteractionAgent_s00af_ab70>* mpCapacity;// +0x8
    int mAllocator[2];                              // +0xc
    void Destroy();                                 // 0xafb7a0
  };

  struct SlotVector {
    tSlot* mpBegin;                                 // +0x0
    tSlot* mpEnd;                                   // +0x4
    tSlot* mpCapacity;                              // +0x8
    int mAllocator[2];                              // +0xc
    int GetSize() const { return (int)(mpEnd - mpBegin); }
    void Destroy();                                 // 0xafb090
  };

  cSPVector3_s00af_ab70 mFacing;                               // +0x00
  float mRadius;                                    // +0x0c
  float mSlotRadius;                                // +0x10
  cSPVector3_s00af_ab70 mCenter;                               // +0x14
  float mAltitude;                                  // +0x20
  int mPacking;                                     // +0x24
  bool mbRelative;                                  // +0x28
  char _pad28[3];
  cSPQuaternion mOrientation;                       // +0x2c
  AgentVector mAgents;                              // +0x3c
  SlotVector mSlots;                                // +0x50

  cActionCircle_s00af_ab70();
  ~cActionCircle_s00af_ab70();

  int StartSnapAttractorEffects(const cSPVector3_s00af_ab70* p);   // 0xafab70
  int FindSlotByAgent(cGameData_s00af_ab70* agent);                // 0xafad30
  tSlot* FindClosestFreeSlotPtr(const cSPVector3_s00af_ab70* p);   // 0xafad70
  void RemoveAgent(cGameData_s00af_ab70* agent);                   // 0xafae50
  void ProjectSlotsOntoPlanet();                        // 0xafaec0
  void ClearSlots();                                    // 0xafafd0
  void RemoveSlotsByReservingId(unsigned int id);       // 0xafb020
  int FindClosestFreeSlot(const cSPVector3_s00af_ab70* p);         // 0xafa5d0
};
}
using SP::cSPVector3_s00af_ab70;
using SP::cActionCircle_s00af_ab70;
using SP::cGameData_s00af_ab70;
// ---- items of slice s00afab70 end

// ---- items of slice s00bf4170 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef int intptr_t;
class cCity;
class cCommunityEditor;
class cPlayerCityMusic;
struct Vec3 {
    float mX;
    float mY;
    float mZ;
};
class IRefCounted_s00bf_4170 {
public:
    virtual void AddRef();          // 0x00
    virtual void Release();         // 0x04
    virtual void v08();
    virtual void* Query(const void* pType);   // 0x0c
    virtual void v10();
};
class cGameData : public IRefCounted_s00bf_4170 {
public:
    uint8_t mPad14[0x20];
};
class cEditorObject : public cGameData {
public:
    Vec3 mPosition;                 // 0x34
    uint8_t mPad40[0x10];
    void* GetIcon();                // 0x50
    uint8_t mPad54[0xac8];
    int mCityKind;                  // 0xb1c
    int mCityLevel;                 // 0xb20
};
class cCity : public cEditorObject {
public:
    int GetVehicleSpecialty();      // 0x94 via terrain sphere, direct here
    void* GetCityHall();            // 0xa4
};
class cPlayerCityMusic : public IRefCounted_s00bf_4170 {
public:
    cPlayerCityMusic();
    void PlayMelody(int bLoop);
    uint8_t mPad14[0x20c];
};
void* GetCurrentGameMode();
extern uint8_t gGameModeSpace;
class cCommunityEditor : public cEditorObject {
public:
    // Editor flags used by the city-reduction paths.
    uint8_t mBadgeToasterShown;      // 0x89
    uint8_t mCityBadgeReady;         // 0x8a
    uint8_t mOneCityBadgeShown;      // 0x8b
    uint8_t mPad8c[0x06];
    uint8_t mCitiesInitialized;      // 0x92
    uint8_t mPad93[0x09];
    cCity** mpCitiesBegin;           // 0x9c
    cCity** mpCitiesEnd;             // 0xa0
    cCity** mpCitiesCap;             // 0xa4
    uint8_t mPadA8[0x08];
    void** mpRemovedBegin;           // 0xb0
    void** mpRemovedEnd;             // 0xb4
    uint8_t mPadB8[0x0c];
    Vec3 mSpawnPosition;             // 0xc4
    uint8_t mPadD0[0x1a4];
    cPlayerCityMusic* mpCityMusicEditor;  // 0x274
    uint8_t mPad278[0x1e0];
    IRefCounted_s00bf_4170* mpTrackedRefA;      // 0x458
    IRefCounted_s00bf_4170* mpTrackedRefB;      // 0x45c
    IRefCounted_s00bf_4170* mpTrackedRefC;      // 0x460
    uint8_t mPad464[0x6c];
    int mMaxCityCount;               // 0x4d0

    void InsertCityAt(int* pPosition, cCity* pCity, int nCount);   // 0x00bf4170
    cCommunityEditor* AttachCity(cCity* pCity);                     // 0x00bf4350
    void ReduceCitiesOnPlanet(cCity* pCity);                        // 0x00bf4370
    void DetachCity(cCity* pCity, int bRemoving);                   // 0x00bf45f0
    void NotifySubEditor();                                         // 0x00bf49e0
    void CreateVehicleFromModelType(cCity* pCity, const Vec3* pPosition);  // 0x00bf4b10
    void RemoveAllCities(cCity* pCity);                             // 0x00bf4e50
    void RebuildCityFromTerrainSphere();                            // 0x00bf4eb0
    void CreateVehicleFromTerrainSphere();                          // 0x00bf4fc0
};
void SetModelTypeKey(int* pKey, const Vec3* pValue);         // 0x00bf4a60
void RefreshCityStatistics(cCommunityEditor* pEditor);        // 0x00bf3b50
// ---- items of slice s00bf4170 end

// ---- items of slice s00d084d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl SP_GameInputManager();                      // 0x00b3d250
extern "C" void* __cdecl GetCameraCtl();                             // 0x00b3d280
extern "C" void* __cdecl SP_App();                                   // 0x0067dd10
extern "C" void  __cdecl sub_64a990(void*);                          // 0x0064a990
extern "C" char  __cdecl FUN_00b673c0(void*);                        // 0x00b673c0
extern "C" char  __cdecl FUN_00b188b0(void*);                        // 0x00b188b0
extern "C" char  __cdecl FUN_00b18740(void*);                        // 0x00b18740
extern "C" char  __cdecl FUN_00b18760(void*);                        // 0x00b18760
extern "C" char  __cdecl FUN_00b187b0(void*);                        // 0x00b187b0
extern "C" char  __cdecl FUN_00b18790(void*);                        // 0x00b18790
extern "C" char  __cdecl FUN_00b187f0(void*);                        // 0x00b187f0
extern "C" void  __cdecl FUN_00b69990(void*);                        // 0x00b69990
typedef unsigned int   u32;
typedef int            s32;
typedef unsigned char  u8;
typedef float          f32;
typedef void* (__thiscall* FnP1)(void*, u32);
typedef void* (__thiscall* FnP0)(void*);
typedef void  (__thiscall* Fn3S)(void*, u32, const char*);
extern "C" u32   __cdecl SP_GetCurrentGameMode();                    // 0x00b5b800
extern "C" void  __cdecl FUN_00572020(void*, u32);                   // 0x00572020
struct CameraCtl {
    void Do(u32* v, u32 a);              // 0x00b13bb0
};
struct CivObj {
    float GetCost(u32 a, u32 b);         // 0x00bf2170
};
struct CityObj {
    CivObj* GetCivilization();            // 0x00bd9bf0
};
struct LaunchInit {
    void Init();                         // 0x00644b10
    void Destroy();                      // 0x00644b60
};
struct Obj8A70 {
    u8    mPad00[0x2b8];
    void* mp2B8;                        // +0x2b8
    u32   Do(u32 a, u32 b);
};
struct Req8D80 {
    u8  mPad00[8];
    u32 mn08;                            // +0x08
    f32 mf0C;                            // +0x0c
    f32 mf10;                            // +0x10
    u32 mn14;                            // +0x14
    u32 mn18;                            // +0x18
};
struct Editor8FA0 {
    u8    mPad00[0x40];
    void* mp40;                          // +0x40
    int   GetVehicleCost(u32 type);
};
struct Launch8B50 {
    u32 mn00;                            // +0x00
    u32 mn04;                            // +0x04
    u32 mn08;                            // +0x08
    u32 mn0C;                            // +0x0c
    u8  mb10;                            // +0x10
    u8  mb11;
    u8  mb12;
    u8  mb13;
    u8  mb14;                            // +0x14
    u8  mPad15[3];
    u32 mn18;                            // +0x18
    u32 mn1C;                            // +0x1c
    u32 mn20;                            // +0x20
    u8  mb24;                            // +0x24
    u8  mPad25[3];
    u32 mn28;                            // +0x28
    u8  mb2C;                            // +0x2c
    u8  mPad2D[3];
    u32 mn30;                            // +0x30
    u32 mn34;                            // +0x34
    u32 mn38;                            // +0x38
    u32 mn3C;                            // +0x3c
    u32 mn40;                            // +0x40
    u32 mn44;                            // +0x44
};
struct Editor8B50 {
    u8  mPad00[0x48];
    u32 mn48;                            // +0x48
    void Setup(u32 modelType, u32 p3, u32 p4, u32 p5, u8 p6);
};
// ---- items of slice s00d084d0 end

// ---- items of slice s00d091c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct ResourceKey {                                      // EA::ResourceMan::Key
    uint32_t instanceID, typeID, groupID;
};
struct Vector3 { float x, y, z; };
struct Quaternion { float x, y, z, w; };
extern Vector3 g_Vector3Zero;                             // 0x0169d58c
template <class T> struct sp_vector {                     // vector<T, sp_vector_allocator>
    T* mpBegin; T* mpEnd; T* mpCapacity; const char* mAllocName;
    int size() const { return (int)(mpEnd - mpBegin); }
};
enum { kGameModeCiv = 0x1654c04, kGameModeSpace = 0x1654c05 };
struct cTerrainSphere;
class cNounManager;
struct cSPLivingUniverse;
struct cGameNounManager;
struct cSPSimulatorSpaceGame;
struct cSPGameDataUFO;
struct cEmpire;
cNounManager*       NounManager();                        // 0x00b3d300
class cNounManager { public:
    cTerrainSphere* GetCurrentTerrainSphere();             // 0x00f67d90 (cTerrainEditor)
};
void                FUN_00c77bf0(cTerrainSphere*);        // 0x00c77bf0
cEmpire*            GetPlayerEmpire_01021300();           // 0x01021300
cSPLivingUniverse*  GetActivePlanetOwner_01021260();      // 0x01021260
void*               App_0067dd10();                       // 0x0067dd10
void*               SpaceGameGet_01002bd0(int, int);      // 0x01002bd0
cSPSimulatorSpaceGame* GetUFOSimulator_00ffbe50();        // 0x00ffbe50
void*               NounHost_00b3d240();                  // 0x00b3d240
void*               CameraCtl_00b3d280();                 // 0x00b3d280
void                CameraCtl_SetDir_00b13bb0(void*, const Vector3*, int);   // 0x00b13bb0
bool                RayHitsObject_00b35bf0(void*, const Vector3*, class cSpatialObject*); // 0x00b35bf0
void                FUN_007c4900(Vector3*, Vector3*);     // 0x007c4900
class cPlanetModel { public:
    void DirectionToSurface(Vector3* out, const Vector3* dir);        // 0x00b815a0
};
cPlanetModel*       PlanetModel_00b3d350(void*, const Vector3*);      // 0x00b3d350
void                FUN_00fe5430(void*, int);             // 0x00fe5430
void                FUN_00c8f470(void*, void*, int, int, float, int);  // 0x00c8f470 (cTribe::SetStimuli)
int  FUN_00bd7f60();                                      // 0x00bd7f60
int  FUN_00bd7f40();                                      // 0x00bd7f40
int  FUN_00bd7f50();                                      // 0x00bd7f50
void FUN_00be2070(void*, int);                            // 0x00be2070
void FUN_00be33e0(void*);                                 // 0x00be33e0
void FUN_00be34a0(void*, int);                            // 0x00be34a0
struct INameable {
virtual void v0();
virtual const wchar_t* GetName();
virtual const Vector3* GetPosition();
};
class cCommunity;   // fwd
enum { TYPE_cCity = 0xee9b2232, TYPE_cTribe = 0x4f396a66 };
class cSpatialObject {
public:
virtual void v00();
virtual void Release();
virtual void v02();
    virtual void* Cast0C(uint32_t typeID);                                // 0x0c
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
    virtual const Vector3* GetPosition();                                 // 0x2c
    virtual const Quaternion* GetOrientation();                           // 0x30
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v30();
virtual void v31();
virtual void v32();
virtual void v33();
virtual void v34();
virtual void v35();
virtual void v36();
virtual void v37();
virtual void v38();
virtual void v39();
virtual void v40();
virtual void v41();
virtual void v42();
virtual void v43();
virtual void v44();
    virtual void v45();                                                   // 0xb4
    virtual void* Cast(uint32_t typeID);                                  // 0xb8
    virtual void v67();                                                   // 0xbc
    virtual void v68();                                                   // 0xc0
    uint8_t pad04[0x72 - 4];
    uint8_t mFlag72;                                                      // +0x72
};
class cCommunity {
public:
    virtual void AddRef();                                // 0x00
    virtual void Release();                               // 0x04
    virtual void v02();
    virtual void* Cast(uint32_t typeID);                  // 0x0c
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
    virtual void v24();
    virtual const Vector3* GetPosition();                 // 0x64
    virtual void v26();
    virtual void* GetMode();                              // 0x6c
};
class cCivilization {
public:
    uint8_t   pad00[0x34];
    INameable mNameable;                                  // +0x34
    uint8_t   pad38[0x40 - 0x38];
    int       mPoliticalID;                               // +0x40
    const ResourceKey* GetModelTypeKey(uint32_t modelType);                       // 0x00bf9770
    void CreateVehicleFromModelType(uint32_t modelType, const ResourceKey* key);  // 0x00bf4b10
};
struct cHallNoun { uint8_t pad[0x34]; INameable mSpatial; };   // +0x34 spatial
class cCity_s00d0_91c0 : public cCommunity {
public:
    cCivilization* GetCivilization();                     // 0x00bd9bf0
    cHallNoun*     GetCityHall();                         // 0x00bd9b40
    void* FUN_00bddda0(int a, int b, uint32_t kx, uint32_t ky, uint32_t kz, int space); // ret 0x18
    uint8_t pad04[0x298 - 4];
    cSpatialObject* mpSpecific_298;                       // +0x298
};
class cSPPaletteUI {
public:
virtual void AddRef();
virtual void Release();
    uint32_t data[(0x6c - 4) / 4];
    int GetCurrentCategoryIndex();                        // 0x005ca9c0
};
class cEmpire {
public:
    void SetUFOKey(const ResourceKey*);                   // 0x00c35740
    const ResourceKey* GetUFOKey();                       // 0x00c326b0
};
class cSPGameDataUFO {
public:
    void SetDesiredModel(const ResourceKey*, int);        // 0x00c37180
};
class cSPSimulatorSpaceGame {
public:
    cSPGameDataUFO* GetPlayerInventory();                 // 0x00a1ad60
};
class cSPLivingUniverse {
public:
    bool FUN_00c70b50();                                  // 0x00c70b50
};
class cGameNounManager {
public:
    void* GetPlayerTribe();                               // (0x00bfc5f0 path)
};
class cCommunityEditor_s00d0_91c0 {
public:
    virtual void HandleMessage();                         // IHandlerRC primary base (vptr +0) 0x00d130d0

    uint32_t pad04[4];
    uint8_t  mActiveAutoHandler[0x14];                    // +0x14
    uint8_t  mPassiveAutoHandler[0x14];                   // +0x28
    void*    mConfigProps;                                // +0x3c
    cCommunity* mpCommunity;                              // +0x40
    uint32_t mSelectedCategoryID;                         // +0x44
    uint32_t mShoppingModelType;                          // +0x48
    uint32_t mLastShoppingModelType;                      // +0x4c
    uint32_t mRecentlyEditedModelKey[3];                  // +0x50
    bool     mbFromShopping;                              // +0x5c
    uint8_t  pad5d[3];
    uint8_t  pad60[0x88 - 0x60];
    uint8_t  mEditorUI;                                   // +0x88 (cSPUILayout head, opaque)
    uint8_t  pad89[0xb4 - 0x89];
    cSPPaletteUI*  mpPaletteUI;                           // +0xb4
    uint32_t padb8;
    cSpatialObject* mpAnchorRing;                         // +0xbc
    cSpatialObject* mpManipulatedObject;                  // +0xc0
    cSpatialObject* mpSelectedObject;                     // +0xc4
    uint32_t padc8;
    Vector3  mAnchorDir_cc;                               // +0xcc
    Quaternion mAnchorQuat;                               // +0xd8
    Vector3  mSnapPoint;                                  // +0xe8
    int      mLastSwapPointIndex;                         // +0xf4
    uint8_t  padf8[0x114 - 0xf8];
    uint8_t  mAnimatedObjectMap[0x1c];                    // +0x114 (eastl::map)
    sp_vector<void*> mPreExistingBuildings;               // +0x130
    uint32_t pad140;
    sp_vector<void*> mPreExistingNouns;                   // +0x144
    uint8_t  pad154[0x1dc - 0x154];
    sp_vector<void*> mPreExistingTurrets;                 // +0x1dc
    uint32_t pad1ec;
    sp_vector<void*> mPreExistingTools;                   // +0x1f0
    uint8_t  pad200[0x278 - 0x200];
    cSpatialObject* mpManipulatedObject_278;              // +0x278
    uint32_t mSpecificA_27c;                              // +0x27c
    uint32_t mSpecificB_280;                              // +0x280
    uint32_t mSpecificC_284;                              // +0x284
    uint32_t mSpecificD_288;                              // +0x288
    uint32_t mSpecificE_28c;                              // +0x28c
    uint32_t mSpecificF_290;                              // +0x290
    uint32_t mSpecificG_294;                              // +0x294
    void*    mpCaptureWindow;                             // +0x298

    void   FUN_00d091c0(uint32_t modelType);                                  // 0x00d091c0
    void   SetKeyForModelType(uint32_t modelType, const ResourceKey* key);    // 0x00d09560
    const ResourceKey* GetKeyForModelType(uint32_t modelType);               // 0x00d09600
    int    FUN_00d09670();                                                    // 0x00d09670
    bool   FUN_00d096b0(void* obj);                                           // 0x00d096b0
    bool   FUN_00d096e0(void* obj);                                           // 0x00d096e0
    bool   FUN_00d09710(void* obj);                                           // 0x00d09710
    bool   FUN_00d09740(void* obj);                                           // 0x00d09740
    void*  FUN_00d09770(int, int);                                            // 0x00d09770
    uint32_t GetCameraZoomProgramID();                                        // 0x00d098b0
    const Vector3* GetCommunityCenter();                                      // 0x00d09960
    void   CameraTrackMouse(cSpatialObject* obj);                             // 0x00d099c0
    void   SetObjectSpecificData();                                           // 0x00d09ad0
    void   RemoveObjectFromCommunity(cSpatialObject* obj);                    // 0x00d09d30
    Vector3* SnapPointToPlanetIfNecessary(Vector3* out, float x, float y, float z, cSpatialObject* obj); // 0x00d09f00
    void   SetManipulatedObject(cSpatialObject* obj);                         // 0x00d09f60
    void   ComputeMouseOffset(cSpatialObject* obj);                           // 0x00d0a040
};
static inline void* CastTo(cCommunity* c, uint32_t typeID)
{
    return c ? c->Cast(typeID) : 0;
}
static inline cCity_s00d0_91c0* AsCity(cCommunity* c)
{
    return (cCity_s00d0_91c0*)CastTo(c, TYPE_cCity);
}
struct cCamHost {                                          // FUN_00b3d240 result vtbl
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
    virtual const Vector3* GetCamPos(Vector3* out, int flag);      // 0x38
    virtual void           GetCamPos3C(Vector3* out, int flag);    // 0x3c
};
class cDisplay {
public:
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
    virtual void GetMousePos(Vector3* a, Vector3* b);     // 0x1c
};
struct cApp {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
    virtual void* GetDisplay();                           // 0x50
};
// ---- items of slice s00d091c0 end

// ---- items of slice s00d0a160 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl PropertyManager();                          // 0xbd9d10-ish
extern "C" void* __cdecl MessageServer();                            // 0x67dcc0
extern "C" void* __cdecl WindowManagerObj();                         // 0x67caa0
extern "C" void* __cdecl AppObject();                                // SP::App
extern "C" void* __cdecl NounManagerObj();                           // 0xb3d300
extern "C" void* __cdecl NounManager(void* noun);                    // 0xb3d300
extern "C" void  __cdecl NounMgr_RemoveNoun(void* mgr, void* noun);  // 0xb225d0
extern "C" void* __cdecl GetPlayerEmpire();                          // 0x1021300
extern "C" void  __cdecl SporeFreeArray(void* p);                    // 0xf47380
typedef unsigned short u16;
typedef unsigned int   SIZE_T;
struct Vec3_s00d0_a160 { float x, y, z; };
struct Vec4 { float x, y, z, w; };
struct IWindow {
  virtual void  AddRef();               // 0x00
  virtual void  Release();              // 0x04
  virtual void  Slot08();               // 0x08
  virtual void* Slot0c(u32 id);         // 0x0c (query interface)
  virtual void  Slot10();               // 0x10
  virtual void  Slot14(s32 v);          // 0x14
  virtual void  Slot18();               // 0x18
  virtual void  Slot1c(s32 v);          // 0x1c (is-max-value query)
  virtual void  Slot20();               // 0x20
  virtual void  Slot24();               // 0x24
  virtual void  Slot28();               // 0x28
  virtual void  Slot2c();               // 0x2c
  virtual void* Slot30();               // 0x30
  virtual void  Slot34();               // 0x34
  virtual Vec4* Slot38();               // 0x38 (area/rect accessor)
  virtual void  Slot3c(void* a, s32 b);  // 0x3c
  virtual void  Slot40();               // 0x40
  virtual void  Slot44();               // 0x44
  virtual void  Slot48();               // 0x48
  virtual void  Slot4c();               // 0x4c
  virtual void  Slot50();               // 0x50
  virtual void  Slot54();               // 0x54
  virtual void  Slot58(s32 v, void* p);  // 0x58
  virtual void  Slot5c(s32 v, void* p);  // 0x5c
  virtual void  Slot60();               // 0x60
  virtual void  Slot64();               // 0x64
  virtual void  Slot68();               // 0x68
  virtual void  Slot6c(Vec4* v);        // 0x6c
  virtual void  Slot70();               // 0x70
  virtual void  Slot74();               // 0x74
  virtual void  Slot78(s32 v);          // 0x78
  virtual void  Slot7c(s32 a, s32 b);   // 0x7c
  virtual void  Slot80();               // 0x80
  virtual void  Slot84();               // 0x84
  virtual void  Slot88();               // 0x88
  virtual void  Slot8c();               // 0x8c
  virtual void  Slot90();               // 0x90
  virtual void  Slot94();               // 0x94
  virtual void  Slot98();               // 0x98
  virtual void  Slot9c();               // 0x9c
  virtual void  SlotA0();               // 0xa0
  virtual void  SlotA4();               // 0xa4
  virtual void  SlotA8();               // 0xa8
  virtual void  SlotAc();               // 0xac
  virtual void  SlotB0();               // 0xb0
  virtual void  SlotB4();               // 0xb4
  virtual void* SlotB8(u32 id);         // 0xb8
  virtual void  SlotBc();               // 0xbc
  virtual void  SlotC0();               // 0xc0
  virtual void  SlotC4();               // 0xc4
  virtual void  SlotC8();               // 0xc8
  virtual void  SlotCc();               // 0xcc
  virtual void  SlotD0();               // 0xd0
  virtual void  SlotD4();               // 0xd4
  virtual void  SlotD8(void* p);        // 0xd8
  virtual void  SlotDc();               // 0xdc
  virtual void  SlotE0();               // 0xe0
  virtual void  SlotE4();               // 0xe4
  virtual void  SlotE8();               // 0xe8
  virtual void  SlotEc();               // 0xec
  virtual void  SlotF0();               // 0xf0
  virtual void  SlotF4();               // 0xf4
  virtual void  SlotF8();               // 0xf8
  virtual void  SlotFc();               // 0xfc
  virtual void  Slot100();              // 0x100
  virtual void  Slot104(void* handler); // 0x104 (set win proc)
};
struct IProperty {
  virtual void  AddRef();                    // 0x00
  virtual void  Release();                   // 0x04
  virtual void  Slot08();                    // 0x08
  virtual void* Slot0c(u32 id);              // 0x0c
  virtual void  Slot10();                    // 0x10
  virtual void  Slot14(u32 id, void* var);   // 0x14
  virtual void  Slot18();                    // 0x18
  virtual u8    Slot1c(u32 id);              // 0x1c
  virtual void  Slot20();                    // 0x20
  virtual void  Slot24();                    // 0x24
  virtual void  Slot28();                    // 0x28
  virtual u8    Slot2c(u32 a, u32 b, void** out);  // 0x2c
  virtual void  Slot30();                    // 0x30
  virtual void  Slot34();                    // 0x34
  virtual void  Slot38();                    // 0x38
  virtual void  Slot3c();                    // 0x3c
  virtual void  Slot40();                    // 0x40
  virtual void  Slot44();                    // 0x44
  virtual void  Slot48();                    // 0x48
  virtual void  Slot4c();                    // 0x4c
  virtual void  Slot50();                    // 0x50
  virtual void  Slot54();                    // 0x54
  virtual u32   Slot58();                    // 0x58
  virtual float Slot5c();                    // 0x5c
  virtual void  Slot60();                    // 0x60
  virtual void  Slot64();                    // 0x64
  virtual void  Slot68();                    // 0x68
  virtual void  Slot6c();                    // 0x6c
  virtual void  Slot70();                    // 0x70
  virtual void  Slot74();                    // 0x74
  virtual void  Slot78();                    // 0x78
  virtual void  Slot7c();                    // 0x7c
  virtual void  Slot80();                    // 0x80
  virtual void  Slot84();                    // 0x84
  virtual void  Slot88();                    // 0x88
  virtual void  Slot8c();                    // 0x8c
  virtual void  Slot90();                    // 0x90
  virtual void  Slot94();                    // 0x94
  virtual void  Slot98();                    // 0x98
  virtual void  Slot9c();                    // 0x9c
  virtual void  SlotA0();                    // 0xa0
  virtual void  SlotA4();                    // 0xa4
  virtual void  SlotA8();                    // 0xa8
  virtual void  SlotAc();                    // 0xac
  virtual void  SlotB0();                    // 0xb0
  virtual void  SlotB4();                    // 0xb4
  virtual void* SlotB8(u32 id);              // 0xb8
};
struct IRollover {
  virtual void  Show(void* window);     // 0x00
  virtual void  Release();              // 0x04
  virtual void  Slot08();               // 0x08
};
struct IWindowMgr {
  virtual void  Slot00();
  virtual void  Slot04();
  virtual void  Slot08();
  virtual void  Slot0c();
  virtual void  Slot10();
  virtual void  Slot14();
  virtual void  Slot18();
  virtual void  Slot1c();
  virtual void  Slot20();
  virtual void  Slot24();
  virtual void  Slot28();
  virtual void  Slot2c();
  virtual void  Slot30();
  virtual void  Slot34();
  virtual void  Slot38();
  virtual void  Slot3c();
  virtual void  Slot40();
  virtual void  Slot44();
  virtual void  Slot48();
  virtual void  Slot4c();
  virtual void  Slot50();
  virtual void  Slot54();
  virtual void  Slot58(s32 v, void* p);   // 0x58
  virtual void  Slot5c(s32 v, void* p);   // 0x5c
};
struct IApp {
  virtual void  Slot00();
  virtual void  Slot04();
  virtual void  Slot08();
  virtual void  Slot0c();
  virtual void  Slot10();
  virtual void  Slot14();
  virtual void  Slot18();
  virtual void* Slot1c(void* a, void* b);  // 0x1c
  virtual void  Slot20();
  virtual void  Slot24();
  virtual void  Slot28();
  virtual void  Slot2c();
  virtual void  Slot30();
  virtual void  Slot34();
  virtual void  Slot38();
  virtual void  Slot3c();
  virtual void  Slot40();
  virtual void  Slot44();
  virtual void  Slot48();
  virtual void  Slot4c();
  virtual void* Slot50();                  // 0x50
};
struct CommunityStub {
  virtual void* Slot0c(u32 id);          // 0x0c (query interface)
  u8 pad04[0x34 - 0x04];
  IWindow mNameProvider_34;              // 0x34 (embedded provider, slot 1 = name)
};
struct SelectableObj {
  u8  pad00[0xb1c];
  u32 mKeyA_b1c;                         // 0xb1c
  u32 mKeyB_b20;                         // 0xb20
};
struct ModelType {
  u8  pad00[0x0c];
  u32 mKeyA_0c;                          // 0x0c
  u8  pad10[0x14 - 0x10];
  u32 mKeyB_14;                          // 0x14
};
struct WindowCtrl {
  u32     mFlags_00;                     // 0x00
  IWindow mWindow_04;                    // 0x04
};
struct CopyValue {
  IWindow* mpA_00;                       // 0x00
  IWindow* mpB_04;                       // 0x04
  float    mF_08;                        // 0x08
  float    mF_0c;                        // 0x0c
  float    mF_10;                        // 0x10
  float    mF_14;                        // 0x14
  float    mF_18;                        // 0x18
  float    mF_1c;                        // 0x1c
  u32      mU32_20;                      // 0x20
  u32      mU32_24;                      // 0x24
  u8       mB_28;                        // 0x28

  CopyValue* AssignFrom(const CopyValue* src);   // 0x00d0a670
};
struct PosNode {
  PosNode* mpLeft_00;                    // 0x00
  PosNode* mpRight_04;                   // 0x04
  u8       pad08[0x10 - 0x08];
  s32      mKey0_10;                     // 0x10
  s32      mKey1_14;                     // 0x14
};
struct PosTree {
  u32      mCount_00;                    // 0x00
  PosNode* mpSentinel_04;                // 0x04 (header node anchor)
  u32      mFlags_08;                    // 0x08
  PosNode* mpRoot_0c;                    // 0x0c

  void InsertPos(PosNode** out, const s32* key);   // 0x00d0a630
};
struct cString {
  u32 mD[4];
  void Ctor();                                 // 0x006b5060
  void Dtor();                                 // 0x006b5240
  bool Load(u32 a, u32 b, s32 c);              // 0x006b54b0
  const u16* GetText();                        // 0x006b55c0
};
struct UiLayout {
  u8 mBytes_00[0x1c];                          // 0x00 (cSPUILayout body)
  void* FindWindowByID(u32 id, s32 flag);      // 0x008105b0
};
struct BudgetObj {
  void SetText(const u16* text);               // 0x00458b50
};
struct cCommunityEditor_s00d0_a160 {
  u8  pad00[0x40];
  CommunityStub* mpCommunity_40;         // 0x40
  u8  pad44[0x6c - 0x44];
  IWindow*  mpBudget_6c;                 // 0x6c (cSPEditorBudget)
  u8  pad70[0x7c - 0x70];
  IRollover* mpSellback_7c;              // 0x7c
  u32        mLimitMode_80;              // 0x80
  IRollover* mpRollover_84;              // 0x84
  UiLayout  mEditorUI_88;                // 0x88 (cSPUILayout, 0x1c bytes here)
  IWindow*   mpVerbIconTray_a4;          // 0xa4
  u8  padA8[0xb0 - 0xa8];
  void*      mpProjector_b0;             // 0xb0
  u8  padB4[0xbc - 0xb4];
  void*      mpRotationRing_bc;          // 0xbc (created noun)
  void*      mpPreviewObject_c0;         // 0xc0
  void*      mpRingDefinition_c4;        // 0xc4
  u8  padC8[0x108 - 0xc8];
  Vec3_s00d0_a160       mPreviewPos_108;            // 0x108
  u8  pad114[0x1e4 - 0x114];
  Vec3_s00d0_a160       mWavePos_1e4;               // 0x1e4
  s32*       mpSelectedIds_1f0;          // 0x1f0 (vector begin)
  s32*       mpSelectedEnd_1f4;          // 0x1f4 (vector end)
  u8  pad1f8[0x208 - 0x1f8];
  u8         mFlag_208;                  // 0x208
  u8  pad209[0x2f8 - 0x209];
  WindowCtrl* mpWindowCtrl_2f8;          // 0x2f8
  u8  pad2fc[0x340 - 0x2fc];
  IWindow*   mpBlockerWindow_340;        // 0x340 (embedded window holder)

  u8  CanShowPreview();                  // 0x00d0a160
  void UpdateLimitMeter(s32 mode);       // 0x00d0a1e0
  void RefreshTooltip();                 // 0x00d0a390
  s32  GetSelectedCost(SelectableObj* p); // 0x00d0a3f0
  void ShowRolloverWindows(u32 idA, u32 idB); // 0x00d0a470
  void ShowPlacementCursor();            // 0x00d0a540
  void HidePlacementCursor();            // 0x00d0a5b0
  void Init(u32 const* pLayoutId, u32 propKey, IWindow* pBudget, u8 bFlag); // 0x00d0a760
  void RefreshBuildingCosts();           // 0x00d0aa70
  s32  GetObjectCost(IWindow* pObj, u8 bRefund, u32 typeKey); // 0x00d0abd0
  u32  UpdateVehiclePlacement();         // 0x00d0ae50
  void SetRotationRingVisibility(u8 bShow); // 0x00d0b010
};
extern "C" void* __cdecl NounMgr_CreateNoun(void* mgr, u32 id);      // 0xb20c60
extern "C" void* __cdecl SporeAlloc(u32 size, const char* pName, u32 a, u32 b, u32 c, u32 d); // 0xf473a0
extern "C" s32   __cdecl SPIDFromName(const char* pName, ...);       // variadic id builder
void* __cdecl FUN_00d06eb0(u32 a);        // 0xd06eb0
void* __cdecl FUN_00d1deb0(u32 a);        // 0xd1deb0
void* __cdecl FUN_00d07420(u32 a);        // 0xd07420
void* __cdecl FUN_00d07720(u32 a);        // 0xd07720
void* __cdecl FUN_00d07a40(cCommunityEditor_s00d0_a160* self); // 0xd07a40
void* __cdecl FUN_005c7b80();             // 0x5c7b80
void  __cdecl FUN_005c7bc0(u32 a);        // 0x5c7bc0
u32   __cdecl FUN_005c7e80(u32,u32,u32,u32); // 0x5c7e80
u32   __cdecl FUN_005c7e20(u32,u32,u32,u32); // 0x5c7e20
s32   __cdecl GetPlayerBuildingCostFromType(); // 0xc9e7c0
s32   __cdecl FUN_00c9e7c0_();            // fallback (same idea)
s32   __cdecl FUN_00bda3b0(u32 id);       // 0xbda3b0
s32   __cdecl FUN_00c9cec0(u32 a);        // 0xc9cec0
s32   __cdecl FUN_00c9cfd0();             // 0xc9cfd0
u8    __cdecl FUN_00d09710(IWindow* p);   // 0xd09710
u8    __cdecl FUN_00d096b0(IWindow* p);   // 0xd096b0
u8    __cdecl FUN_00d096e0(IWindow* p);   // 0xd096e0
float __fastcall FUN_00bf2170(void* civ, int dummy);       // 0xbf2170
void  __fastcall City_GetCivilization(void* city, int dummy, u32 a, u32 b); // 0xbd9bf0
s32   __cdecl FUN_00cf74c0();             // 0xcf74c0
float __cdecl FUN_00cf7a50();             // 0xcf7a50
s32   __cdecl GetDamageState(void* combatant); // 0xc??
void  __cdecl FUN_007c4900(void* a, void* b);  // 0x7c4900
void* __cdecl FUN_00b3d240();             // 0xb3d240
void  __cdecl FUN_00698e00(void* a, void* b, void* c, void* d); // 0x698e00
void  __cdecl PlanetModel(void* out, void* a, void* b);        // 0x?
void  __cdecl FUN_00b7f1f0(void* a, void* b, void* c);         // 0xb7f1f0
void* __cdecl FUN_00b33e60(u32 a);        // 0xb33e60
void  __cdecl Rollover_Show(IRollover* r, u32 v1, u32 v2, u32 v3); // 0x?
void  __cdecl FUN_0067cab0(void* a);      // 0x67cab0
void  __cdecl FUN_008017f0(void* a);      // 0x8017f0
void  __cdecl FUN_005cc690();             // 0x5cc690
void* __cdecl GetPropertyAsKeyInstance(void* p, u32 id, void** out); // 0x6a12a0
void  __cdecl DeclareMenuCommands();      // 0x?
void* __cdecl SellbackDetachedRollover_ctor(void* p);  // 0x?
void  __fastcall UiLayout_Init(void* layout, int dummy, u32 a, u32 b, s32 c, u32 d); // 0x?
void  __fastcall UiLayout_SetVisibility(void* layout, int dummy, s32 v); // 0x?
void* __cdecl Window_New(u32 size, u32 a, const char* pClass, void* b); // 0x9512d0
void* __cdecl FUN_009512c0();             // 0x9512c0
static const u16 kPreviewName[] = { 'P','r','e','v','i','e','w','M','o','d','e','l', 0 };
// ---- items of slice s00d0a160 end

// ---- items of slice s00d0b090 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(_InterlockedExchange)
struct V3 { float x, y, z; };
struct Quat { float x, y, z, w; };
struct Matrix33 { float m[9]; void Assign(const Matrix33* src); };
uint32_t __cdecl FNVHash(const char* s, uint32_t seed, int lowercase);   // 0x00932e80
static inline uint32_t id(const char* s) { return FNVHash(s, 0x811c9dc5, 1); }
uint32_t __cdecl SPIDFromName(const char* name);                        // 0x00571cf0
float GetPropertyF(uint32_t group, int, uint32_t prop, float def);       // 0x00bcea30
class cSpatialObject_s00d0_b090;
class cCommunity_s00d0_b090;
class cEditorEconomy;
class cSPEditorBudget;
class cCommunity_s00d0_b090 {
public:
    virtual void AddRef();
    virtual void Release();
    virtual void v02();
    virtual void* Cast(uint32_t typeID);   // +0x0c
};
class cEditorEconomy {
public:
    virtual void Dtor(int flags);
    uint32_t mnRefCount;                   // +0x4
};
class cSPEditorBudget {
public:
    virtual void Dtor();
    uint32_t mnRefCount;                   // +0x4
    void Shutdown();                       // 0x004581d0
};
template <class T> class AutoRefCount {
public:
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(T* p) : mpObject(p) { if (p) p->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
};
class cSpatialObject_s00d0_b090 { public:
virtual void v00();
virtual void v01();
virtual void v02();
    virtual void* Cast(uint32_t typeID);   // +0x0c
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
    virtual cSpatialObject_s00d0_b090* GetMode();     // +0x6c
virtual void v28();
virtual void v29();
virtual void v30();
virtual void v31();
virtual void v32();
virtual void v33();
virtual void v34();
virtual void v35();
virtual void v36();
virtual void v37();
virtual void v38();
virtual void v39();
virtual void v40();
virtual void v41();
virtual void v42();
virtual void v43();
virtual void v44();
virtual void* CastB(uint32_t typeID);
};
class cCommunityEditor_s00d0_b090 { public:
    virtual void v00();
    uint32_t pad04[4];
    uint32_t pad14[11];
    AutoRefCount<cCommunity_s00d0_b090> mpCommunity;          // +0x40
    uint32_t pad44[9];
    AutoRefCount<cEditorEconomy>  mEconomy;        // +0x68
    AutoRefCount<cSPEditorBudget> mBudget;         // +0x6c
    uint32_t pad70[19];
    uint32_t mpRotationNoun;                       // +0xbc
    cSpatialObject_s00d0_b090* mpRotationAnchor;              // +0xc0
    cSpatialObject_s00d0_b090* mpSelectedObject;              // +0xc4
    uint32_t padc8[12];
    int mSnapIndices[4];                           // +0xf8
    uint32_t pad108[15];
    void** mpNounBegin;                            // +0x144
    void** mpNounEnd;                              // +0x148
    uint32_t mNounCap;                             // +0x14c
    uint32_t pad150[75];
    uint32_t mEffectID;                            // +0x27c

    const V3* GetCommunityCenter();                // 0x00d09960
    void SetManipulatedObject(cSpatialObject_s00d0_b090* o);  // 0x00d09f60
    void FUN_00d0b010(bool b);                     // 0x00d0b010
    float GetMaxCameraAnchorDistanceFromCommunityCenter();  // 0x00d0b090 (cCommunityEditor::GetMaxCameraAnchorDistanceFromCommunityCenter)
    float GetDefaultCameraDistance();  // 0x00d0b220 (cCommunityEditor::GetDefaultCameraDistance)
    void  SetDefaultCamera(bool b);  // 0x00d0b3b0 (cCommunityEditor::SetDefaultCamera)
    bool  IsPositionInsideCommunityBounds(V3 pos);  // 0x00d0b4d0 (cCommunityEditor::IsPositionInsideCommunityBounds)
    void  BoundPositionInsideCommunity(V3* out, float x, float y, float z);  // 0x00d0b540 (cCommunityEditor::BoundPositionInsideCommunity)
    int   GetIndexOfClosestSnapPoint(void* a, void* snapPoints, void* c, void* d, bool b, void** out);  // 0x00d0b710 (cCommunityEditor::GetIndexOfClosestSnapPoint)
    void* CreateOneShotEffect(int id, float x, float y, float z);  // 0x00d0ba80 (cCommunityEditor::CreateOneShotEffect)
    void  FUN_00d0bbd0(void** effect, float x, float y, float z);
    void  SetSelectedObject(cSpatialObject_s00d0_b090* o);
    void  ClearResources();
};
struct cIntPairTree {
    uint32_t pad[4];          // +0x00
    uint32_t* lower_bound(int* key, void** out);  // 0x00d0bd60
};
struct cCameraCtl {
    uint32_t pad00[4];
    void FUN_00b10340(float a, float b, float c);  // 0x00b10340
    void FUN_00b10540(float a, float b, float c);  // 0x00b10540
    void GetAnglesA(float* a, float* b, float* c); // 0x00b0f210
    void GetAnglesB(float* a, float* b, float* c); // 0x00b0f240
    void GetTargetOrientation(Quat* out);          // 0x00b137d0
    float* GetTargetPosition();                    // 0x00b10200
    void FUN_00b13bb0(const V3* target, bool snap); // 0x00b13bb0
};
cCameraCtl* GetCameraCtl_s00d0_b090();                        // 0x00b3d280
class cPlanetModel_s00d0_b090 {
public:
    float DistanceBetweenPoints(const V3* a, const V3* b);   // 0x00b81470
    const Matrix33* BuildSurfaceOrientation(const V3* pos, const V3* dir); // 0x00b7f190
};
cPlanetModel_s00d0_b090* PlanetModel();                        // 0x00b3d350
void* FUN_00fcc210(void* elem);            // 0x00fcc210
bool  FUN_00c3f540(void* obj);             // 0x00c3f540
int   GetFileCount(void* obj);             // 0x008e7f80 (cCombatant::GetDamageState shape)
enum { kTypeCity = 0xee9b2232, kTypeTribe = 0x4f396a66,
       kCastCombatant = 0xe9cb8ba, kCastSnap = 0x436f315, kCastSnapOut = 0x1186577 };
// ---- items of slice s00d0b090 end

// ---- items of slice s00d0c010 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char kEastlAllocatorHeader[];
#pragma warning(disable : 4100)
void* operator_new(size_t nSize, const char* pName, int a, int b, const void* pFile, int nLine);
inline void* operator new(size_t, void* pWhere) { return pWhere; }
namespace SP {
class IRefCounted_s00d0_c010 {
public:
    virtual void Destroy();                             // +0x00
    virtual void Release();                             // +0x04
};
}
namespace SP {
struct tMapValue {
    uint32_t mId;                                       // +0x00
    float    mVal0;                                     // +0x04
    float    mVal1;                                     // +0x08
    float    mVal2;                                     // +0x0c
};
}
namespace SP {
struct tTreeNode {
    tTreeNode* mpParent;                                // +0x00
    tTreeNode* mpLeft;                                  // +0x04
    tTreeNode* mpRight;                                 // +0x08
    uint32_t   mColor;                                  // +0x0c
    tMapValue  mValue;                                  // +0x10
};
}
namespace SP {
struct tTreeHead {
    tTreeNode* mpParent;                                // +0x00
    tTreeNode* mpLeft;                                  // +0x04
    tTreeNode* mpRight;                                 // +0x08
    uint32_t   mColor;                                  // +0x0c
};
}
namespace SP {
struct cMapInsert {
    int32_t   mSize;                                    // +0x00
    tTreeHead mHeader;                                  // +0x04 (sentinel node)
    int32_t   mCount;                                   // +0x14
    int32_t   mPad18;                                   // +0x18
    int32_t   mPad1c;                                   // +0x1c
};
}
namespace SP {
struct tListChild {
    tListChild*  mpFirst;                               // +0x00
    tListChild*  mpNext;                                // +0x04
    uint8_t      pad08[0x10];                           // +0x08 .. +0x17
    IRefCounted_s00d0_c010* mpPayloadA;                            // +0x18
    IRefCounted_s00d0_c010* mpPayloadB;                            // +0x1c
};
}
namespace SP {
struct cListOwner {
    uint8_t pad00[4];                                   // +0x00

    void FUN_00d0c8e0(tListChild* pChild);
};
}
namespace SP {
const char kEastlAllocatorHeader[] = "EASTL/allocator.h";
}
namespace SP {
void __cdecl eastl_RBTreeInsert(tTreeNode* pNode, tTreeNode* pParent, tTreeNode* pHeader, int side);
}
namespace SP {
struct tVec3 {
    float mX;                                           // +0x00
    float mY;                                           // +0x04
    float mZ;                                           // +0x08
};
}
namespace SP {
class ISpaceObject {
public:
    virtual void o00();
    virtual void o04();
    virtual void o08();
    virtual void* QueryInterface(uint32_t interfaceId);  // +0x0c
};
}
namespace SP {
class cCity_s00d0_c010 {
public:
    void* GetCivilization();                             // 0x00bd9bf0
};
}
namespace SP {
struct cTerrainEditor {
    uint8_t pad0000[0x1150];                             // +0x0000
    tVec3   mTerrainSphere;                              // +0x1150
};
}
namespace SP {
cTerrainEditor* __cdecl GetCurrentTerrainSphere();        // 0x00f67d90
}
namespace SP {
struct cCommunityEditor_s00d0_c010 {
    uint8_t       pad000[0x3c];                          // +0x000
    ISpaceObject* mpSpaceObject;                         // +0x03c
    int32_t       mPad040;                               // +0x040
    int32_t       mLastSelection;                        // +0x044
    uint8_t       pad048[0x14];                          // +0x048 .. +0x05b
    int32_t       mModelType;                            // +0x05c
    uint8_t       pad060[0xb4];                          // +0x060 .. +0x113
    cMapInsert    mTree;                                 // +0x114

    void UpdateSwatchForModelType(int modelType, const tVec3* pPos, const tVec3* pAlt);  // 0x00d0c820 (SP::cCommunityEditor::UpdateSwatchForModelType)
    void SetKeyForModelType(int modelType, const tVec3* pPos);   // 0x00d09560
    void OnAssetBrowserSelection(const tVec3* pPos);
};
}
namespace SP {
struct cTribeToolView {
    uint8_t pad000[4];                                  // +0x000

    bool UpdateRotationSound();
};
}
// ---- items of slice s00d0c010 end

// ---- items of slice s00d0d0e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
struct RCObj {
    virtual void AddRef();                 // +0x00
    virtual void Release();                // +0x04
};
struct PtrVec {
    RCObj** mBegin;                        // +0x260
    RCObj** mEnd;                          // +0x264
    RCObj** mCap;                          // +0x268
    // 0x00533500  __thiscall (ecx = &vec): erase/clear [first,last)
    void Fn533500(RCObj** first, RCObj** last);
    // 0x00a0a360  __thiscall (ecx = &vec): grow + insert, ret 8
    void FnA0A360(RCObj** pos, RCObj** value);
    void push_back(RCObj* v)
    {
        if (mEnd < mCap) {
            RCObj** p = mEnd;
            mEnd = p + 1;
            if (p != 0)
                *p = v;
            if (v != 0)
                v->AddRef();
        } else {
            FnA0A360(mEnd, &v);
        }
    }
};
struct Obj;
struct Obj {
    PV2 PV
    virtual void* Slot0C(unsigned id);             // +0x0c
    virtual void* Slot10();
    PV8 PV8 PV4                                    // slots +0x10 .. +0x58
    virtual char  Slot58();                        // +0x58
    PV
    virtual Vector3* Slot5C();                     // +0x60-ish (unused here)
    // non-virtual helpers
    void FnBDCA30(Vector3* out, void* param);      // 0x00bdca30
};
struct CE {
    char   pad000[0x40];
    Obj*   m40;                            // +0x40
    char   pad044[0x260 - 0x44];
    PtrVec mSpan;                          // +0x260  vector<RCObj*>
    char   pad26C[0x10];                   // +0x26c..+0x27b
    int    m27c;                           // +0x27c

    void FUN_00d0dea0();
    void StartVehicleAttractorEffects(void* param_2);  // 0x00d0ddc0
    void FnBBD0(Vector3 v, RCObj** out);               // 0x00d0bbd0, ret 0x10
};
// ---- items of slice s00d0d0e0 end

// ---- items of slice s00d0e170 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void EASTL_allocator_deallocate(void* p);      // 0x00f47380
extern const uint32_t kCommunityEditorMessageIDs[26];     // 0x01479158
extern bool g_bCommunityEditorFirstActivate;              // 0x0158236c
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);           // 0x00f473a0 (EA allocator new)
struct ResourceKey_s00d0_e170 {                                      // EA::ResourceMan::Key
    uint32_t instanceID, typeID, groupID;
    ResourceKey_s00d0_e170() : instanceID(0), typeID(0), groupID(0) {}
    ResourceKey_s00d0_e170(uint32_t i, uint32_t t, uint32_t g) : instanceID(i), typeID(t), groupID(g) {}
};
bool Vector3Equal(const Vector3* a, const Vector3* b);    // 0x004232c0 (cdecl)
template <class T> struct sp_vector_s00d0_e170 {                     // vector<T, sp_vector_allocator>
    T* mpBegin; T* mpEnd; T* mpCapacity; const char* mAllocName;
    sp_vector_s00d0_e170() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~sp_vector_s00d0_e170() {                                        // sp_vector_allocator::deallocate
        if (mpBegin && reinterpret_cast<int*>(mpBegin)[-1] != 0)
            EASTL_allocator_deallocate(mpBegin);
    }
    int size() const { return (int)(mpEnd - mpBegin); }
    T& operator[](int i) { return mpBegin[i]; }
    void DoInsertValue(T* position, const T& value);      // 0x004558a0 (uint32 instance)
    void push_back(const T& value) {                      // 0x00454860 when not inlined
        if (mpEnd < mpCapacity) { T* p = mpEnd++; if (p) *p = value; }
        else DoInsertValue(mpEnd, value);
    }
    sp_vector_s00d0_e170& operator=(const sp_vector_s00d0_e170& x);             // 0x01011cc0
};
struct rbtree_map {                                       // eastl::map<K,V> (0x1c bytes)
    struct anchor_t { void* mpNodeRight; void* mpNodeLeft; void* mpNodeParent; char mColor; };
    uint32_t mCompare;
    anchor_t mAnchor;
    uint32_t mnSize;
    const char* mAllocName;
    void DoNukeSubtree(void* node);                       // 0x009a9600
    void clear() {
        DoNukeSubtree(mAnchor.mpNodeParent);
        mAnchor.mpNodeRight  = &mAnchor;
        mAnchor.mpNodeLeft   = &mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor       = 0;
        mnSize               = 0;
    }
};
template <class T> struct AutoRefCount_s00d0_e170 {
    T* mpObject;
    AutoRefCount_s00d0_e170& operator=(T* p) {
        T* old = mpObject;
        if (p != old) {
            if (p) p->AddRef();
            mpObject = p;
            if (old) old->Release();
        }
        return *this;
    }
    AutoRefCount_s00d0_e170& operator=(const AutoRefCount_s00d0_e170& x) { return operator=(x.mpObject); }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
namespace UTFWin {
struct IWindow_s00d0_e170 {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
    virtual const float* GetRealArea();                   // 0x38
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
    virtual void SetShadeColor(uint32_t color);           // 0x5c
    virtual void v24();
    virtual void SetLocation(float x, float y);           // 0x64
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
    virtual void v30();
    virtual void SetFlag(int flag, bool value);           // 0x7c
    virtual void SetCaption(const wchar_t* caption);      // 0x80
};
}
using UTFWin::IWindow_s00d0_e170;
enum { kWinFlagVisible = 1 };
class cSPUILayout_s00d0_e170 { public:                                      // 0xc bytes
    uint32_t pad[3];
    void SetVisibility(bool visible);                     // 0x00810590
    IWindow_s00d0_e170* FindWindowByID(uint32_t controlID, bool recursive); // 0x008105b0
};
struct CursorAttachmentLayout { void SetWindow(IWindow_s00d0_e170* w); };   // 0x008017f0
CursorAttachmentLayout* FUN_0067cab0();
class cUIHints { public: uint32_t pad[0x12]; int mState; void UpdateHints(int a, bool b); }; // 0x0067c350
cUIHints* FUN_0067cac0();
struct cSwatchManager {
    IWindow_s00d0_e170* FUN_0080dc90();
    void     FUN_0080dc50(uint32_t swatchID);
};
cSwatchManager* FUN_0067cad0();
struct cUnknownCF74 { void FUN_00cf7a30(); };
cUnknownCF74* FUN_00cf74c0_s00d0_e170();
class cSPUIPropertyLayout_s00d0_e170 { public:                              // city-stats rollover (0xb0 bytes)
virtual void AddRef();
virtual void Release();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
    virtual void SetProperty(uint32_t id);                // 0x28
    uint32_t data[(0xb0 - 4) / 4];
    cSPUIPropertyLayout_s00d0_e170();                                // 0x00e2b8e0
    void SetKey(const wchar_t* name, uint32_t group);     // 0x00827fc0
    void FUN_00e2ad50(bool b);
    void FUN_00e2abc0();
    IWindow_s00d0_e170* GetRootWindow();                             // 0x00828100
};
struct IMessageServer {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
    virtual void PostMSG(uint32_t msgID, void* msg, int flags);     // 0x14
virtual void v6();
virtual void v7();
virtual void v8();
    virtual void AddHandler(void* handler, uint32_t msgID);         // 0x24
};
IMessageServer* MessageServer_s00d0_e170();                          // 0x0067dcc0
struct AutoHandler {                                      // EA::Messaging::AutoHandler
    IMessageServer* mpServer;
    void*           mpHandler;
    const uint32_t* mpIdArray;
    uint32_t        mnIdCount;
    uint32_t        mbPassive;
    void Register(IMessageServer* server, void* handler, const uint32_t* ids, uint32_t count) {
        mpServer = server; mpHandler = handler; mpIdArray = ids; mnIdCount = count; mbPassive = 0;
        if (server)
            for (uint32_t i = 0; i < count; ++i)
                server->AddHandler(handler, ids[i]);
    }
};
struct cMsgBase { virtual void Base0(); };
struct cMsgData { virtual void Data0(); int mField8; int mFieldC; cMsgData() : mField8(0) {} };
struct cSetCreationMsg : cMsgBase, cMsgData {
    ResourceKey_s00d0_e170 mKey;
    int         mToolType;
    explicit cSetCreationMsg(int toolType) : mToolType(toolType) {}
    virtual void Base0();
};
enum { kMsgSetCreation = 0x53850baf };
struct cBehaviorMessage {
    virtual void Dtor();
    virtual void AddRef();
    virtual void Release();
    volatile long mnRefCount;
    int      mField8;
    uint32_t pad0c[9];
    uint32_t mMessageID;
    uint32_t pad34;
    cBehaviorMessage() : mMessageID(0) { _InterlockedExchange(&mnRefCount, 0); }
};
struct cActivateBehaviorMessage : cBehaviorMessage {
    int mField38;
    uint32_t pad3c;
    cActivateBehaviorMessage() : mField38(0) {}
    virtual void Dtor();
};
template <class T> struct intrusive_ptr {
    T* mp;
    intrusive_ptr(T* p) : mp(p) { if (p) p->AddRef(); }
    ~intrusive_ptr() { if (mp) mp->Release(); }
    T* operator->() const { return mp; }
    T* get() const { return mp; }
};
namespace SP {
class cDirectPropertyList_s00d0_e170 { public: void SetBoolProperty(uint32_t id, bool value); };  // 0x006a17e0
}
namespace SP {
extern cDirectPropertyList_s00d0_e170* g_pDirectProps;               // 0x015fd918
}
namespace SP {
class cGameTimeManager { public: void IncPauseGate(uint32_t gate); };                 // 0x00b32220
}
namespace SP {
cGameTimeManager* GameTimeManager();                      // 0x00b3d380
}
namespace SP {
struct cCommunityCamera {                                 // 0x00b3d280 accessor
    uint32_t pad00[4];
    bool     mb10;
    uint8_t  pad11[0x308 - 0x11];
    uint32_t mZoomState;                                  // +0x308
    const uint32_t* GetAnchorDirection();                 // 0x00b10260 (3 dwords)
    void GetAngles(uint32_t* a, uint32_t* b, uint32_t* c);// 0x00b0f210
    void SetZoomProgram(uint32_t id);                     // 0x00b11870
    void SetPreRotate(float x, float z);                  // 0x00b0f700
    void FUN_00b13bb0(const Vector3* target, bool snap);
    void FUN_00b13b50();
};
}
namespace SP {
cCommunityCamera* FUN_00b3d280();
}
namespace SP {
struct cIVisualEffect { virtual void v0(); virtual void v1(); virtual void Stop(int flags); };
}
namespace SP {
struct cEffectsManager {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
    virtual bool GetEffect(uint32_t id, int group, cIVisualEffect** out);       // 0x2c
};
}
namespace SP {
cEffectsManager* EffectsManager();                        // 0x0067ddd0
}
namespace SP {
struct cGameNoun;
}
namespace SP {
class cCivilization_s00d0_e170;
}
namespace SP {
class cGameNounManager_s00d0_e170 { public:
    void RemoveNoun(cGameNoun* noun);                     // 0x00b225d0
    cCivilization_s00d0_e170* GetPlayerCivilization();               // 0x00b25fb0
    void* GetCurrentTerrainSphere();                      // 0x00f67d90
};
}
namespace SP {
cGameNounManager_s00d0_e170* NounManager_s00d0_e170();                          // 0x00b3d300
}
namespace SP {
struct INameable_s00d0_e170 {                                        // the +0x34 subobject
    virtual void v0();
    virtual const wchar_t* GetName();                     // slot 1
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
    virtual const Vector3* GetPosition();                 // 0x2c
};
}
namespace SP {
struct cToolTemplate { uint8_t pad[0x504]; ResourceKey_s00d0_e170 mKey; };   // +0x504
}
namespace SP {
class cCivilization_s00d0_e170 { public:
    uint8_t   pad00[0x34];
    INameable_s00d0_e170 mNameable;                                  // +0x34
    uint8_t   pad38[0x40 - 0x38];
    int       mPoliticalID;                               // +0x40
    sp_vector_s00d0_e170<void*>* FUN_00bef6c0();                     // list of cities
    cToolTemplate*    FUN_00bef950();
    const ResourceKey_s00d0_e170* GetModelTypeKey(uint32_t modelType);         // 0x00bf9770
};
}
namespace SP {
struct cEmpireName { const wchar_t* mpBegin; };
}
namespace SP {
class cEmpire_s00d0_e170 { public:
    const cEmpireName* GetName();                         // 0x005c65e0
    const ResourceKey_s00d0_e170* GetUFOKey();                       // 0x00c326b0
};
}
namespace SP {
cEmpire_s00d0_e170* GetPlayerEmpire_s00d0_e170();                               // 0x01021300 (cSPLivingUniverse)
}
namespace SP {
struct cCommunityMode {                                   // community vfunc 0x6c result
    bool FUN_00bec860();                                  // colony?
    const ResourceKey_s00d0_e170* FUN_00bebe10();
    uint32_t FUN_00bebe20();
};
}
namespace SP {
struct cHallNoun_s00d0_e170 { uint8_t pad[0x34]; INameable_s00d0_e170 mSpatial; };
}
namespace SP {
class cCommunity_s00d0_e170 { public:
    virtual void AddRef();                                // 0x00
    virtual void Release();                               // 0x04
    virtual void v02();
    virtual void* Cast(uint32_t typeID);                  // 0x0c
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
    virtual void v24();
    virtual const Vector3* GetPosition();                 // 0x64
    virtual void v26();
    virtual cCommunityMode* GetMode();                    // 0x6c
virtual void v28();
virtual void v29();
virtual void v30();
virtual void v31();
virtual void v32();
virtual void v33();
virtual void v34();
virtual void v35();
virtual void v36();
virtual void v37();
virtual void v38();
virtual void v39();
virtual void v40();
virtual void v41();
virtual void v42();
virtual void v43();
virtual void v44();
virtual void v45();
virtual void v46();
    virtual void* GetToolList();                          // 0xbc (cTribe)
    uint32_t  pad04[(0x34 - 4) / 4];
    INameable_s00d0_e170 mNameable;                                  // +0x34
    uint8_t   pad38[0x192 - 0x38];
    bool      mbBeingEdited;                              // +0x192
};
}
namespace SP {
struct cSpatialNoun {                                     // element of mPreExistingNouns
    uint8_t pad[0x34]; INameable_s00d0_e170 mSpatial;
    struct cModel { void FUN_00c3f160(const Vector3* p, float radius); };
    cModel* FUN_00bce470();
};
}
namespace SP {
class cCity_s00d0_e170 : public cCommunity_s00d0_e170 { public:
    cCivilization_s00d0_e170* GetCivilization();                     // 0x00bd9bf0
    void FUN_00bdc4a0(int);
    void* GetBuildings();                                 // 0x00c8e810 (vector)
    void FUN_00be5700(sp_vector_s00d0_e170<cSpatialNoun*>* out);
    void FUN_00bdde70(cSPUIPropertyLayout_s00d0_e170* stats);
    void FUN_00bd7f30();
    int  GetVehicleSpecialty();                           // 0x00bd81d0
    int  GetCreatureCount();                              // 0x00bd8120
    bool FUN_00bdb930(int specialty, int slot);
    const Vector3* FUN_00fa0e00();
    cHallNoun_s00d0_e170* GetCityHall();                             // 0x00bd9b40
};
}
namespace SP {
enum { TYPE_cCity_s00d0_e170 = 0xee9b2232, TYPE_cTribe_s00d0_e170 = 0x4f396a66 };
}
namespace SP {
class cTribe_s00d0_e170 : public cCommunity_s00d0_e170 { public:
    uint16_t FUN_00c8e9f0();
    bool     IsHerbivore();                               // 0x00c8e850
    cToolTemplate* FUN_00c8e820(int toolType);
    void*    GetToolOfType(int toolType);                 // 0x00c8f6e0
};
}
namespace SP {
inline uint32_t TribeChief(cTribe_s00d0_e170* t) { return *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(t) + 0x234); }
}
namespace SP {
template <class T> inline T* object_cast(cCommunity_s00d0_e170* p, uint32_t typeID)
{
    return p ? static_cast<T*>(p->Cast(typeID)) : 0;
}
}
namespace SP {
struct cEditorEconomy_s00d0_e170 {                                   // vtbl 0x1479484/0x14794a4/0x1479468
    virtual ~cEditorEconomy_s00d0_e170();
    int mnRefCount;
    cEditorEconomy_s00d0_e170() : mnRefCount(0) {}
    void AddRef() { ++mnRefCount; }
    void Release() { if (--mnRefCount == 0) { mnRefCount = 1; delete this; } }
};
}
namespace SP {
struct cSpaceColonyEconomy : cEditorEconomy_s00d0_e170 {
    cEmpire_s00d0_e170* mpEmpire; cCity_s00d0_e170* mpCity;
    cSpaceColonyEconomy(cEmpire_s00d0_e170* e, cCity_s00d0_e170* c) : mpEmpire(e), mpCity(c) {}
    virtual ~cSpaceColonyEconomy();
};
}
namespace SP {
struct cCivCityEconomy : cEditorEconomy_s00d0_e170 {
    cCity_s00d0_e170* mpCity;
    explicit cCivCityEconomy(cCity_s00d0_e170* c) : mpCity(c) {}
    virtual ~cCivCityEconomy();
};
}
namespace SP {
struct cTribeEconomy : cEditorEconomy_s00d0_e170 {
    cTribe_s00d0_e170* mpTribe;
    explicit cTribeEconomy(cTribe_s00d0_e170* t) : mpTribe(t) {}
    virtual ~cTribeEconomy();
};
}
namespace SP {
template <> struct AutoRefCount_s00d0_e170<cEditorEconomy_s00d0_e170> {
    cEditorEconomy_s00d0_e170* mpObject;
    AutoRefCount_s00d0_e170& operator=(cEditorEconomy_s00d0_e170* p);           // 0x00572680 (out of line)
    void Assign(cEditorEconomy_s00d0_e170* p) {                      // inlined form (tribe path)
        cEditorEconomy_s00d0_e170* old = mpObject;
        if (p != old) {
            if (p) p->AddRef();
            mpObject = p;
            if (old) old->Release();
        }
    }
    operator cEditorEconomy_s00d0_e170*() const { return mpObject; }
};
}
namespace SP {
struct cCityMusicEditor {                                 // SP::Audio (0x114 bytes)
virtual void AddRef();
virtual void Release();
    uint32_t data[(0x114 - 4) / 4];
    cCityMusicEditor();                                   // 0x00ea0ea0
    void Init();                                          // 0x00ea17b0
};
}
namespace SP {
class cCollectableItems_s00d0_e170 { public:                                // 0x6dac bytes
virtual void AddRef();
virtual void Release();
    struct Key { uint32_t a, b; };
    uint32_t data[(0x6dac - 4) / 4];
    cCollectableItems_s00d0_e170();                                  // 0x00597e00
    void FUN_00597a20();
    void AddUnlock(Key k, int, int, int, int, int, float, int);   // 0x00598db0
    void Unlock(Key k);                                   // 0x00596e10
};
}
namespace SP {
cCollectableItems_s00d0_e170::Key FUN_00593980(uint32_t listID, uint32_t itemID);  // cdecl
}
namespace SP {
class cSPPalette_s00d0_e170 { public:                                       // 0x40 bytes
virtual void v0();
virtual void AddRef();
virtual void Release();
    uint32_t data[(0x40 - 4) / 4];
    cSPPalette_s00d0_e170();                                         // 0x005c5e30
    bool Init(const ResourceKey_s00d0_e170* key, int, int, int, int, int, int);   // 0x005c6340
};
}
namespace SP {
struct cPaletteInfo {                                     // 0x34 bytes
virtual void v0();
virtual void AddRef();
virtual void Release();
    uint32_t pad04;
    AutoRefCount_s00d0_e170<cEditorEconomy_s00d0_e170>     mEconomy;            // +0x08 (inline refcount)
    uint32_t pad0c;
    AutoRefCount_s00d0_e170<cCollectableItems_s00d0_e170>  mCollectables;       // +0x10
    uint32_t pad14;
    uint16_t mLimitType;                                  // +0x18
    uint16_t pad1a;
    uint32_t pad1c[(0x34 - 0x1c) / 4];
    cPaletteInfo();                                       // 0x005c64e0
};
}
namespace SP {
class cSPPaletteUI_s00d0_e170 { public:                                     // 0x6c bytes
virtual void AddRef();
virtual void Release();
    uint32_t data[(0x6c - 4) / 4];
    cSPPaletteUI_s00d0_e170();                                       // 0x005cb3b0
    void Init(cSPPalette_s00d0_e170* palette, IWindow_s00d0_e170* window, int, cPaletteInfo* info);   // 0x005cb5a0
    int  FindCategoryIndex();                             // 0x005ca9c0
};
}
namespace SP {
class cSPEditorBudget_s00d0_e170 { public:                                  // 0x74 bytes
virtual void v0();
virtual void v1();
virtual void AddRef();
virtual void Release();
    uint32_t data[(0x74 - 4) / 4];
    cSPEditorBudget_s00d0_e170();                                    // 0x004575d0
    void Init(const ResourceKey_s00d0_e170* layout, cEditorEconomy_s00d0_e170* economy, int limitType,
              IWindow_s00d0_e170* window, const wchar_t* title);     // 0x00457af0
};
}
namespace SP {
class cSPEditorNaming_s00d0_e170 { public:                                  // 0x38 bytes
virtual void AddRef();
virtual void Release();
    uint32_t data[(0x38 - 4) / 4];
    cSPEditorNaming_s00d0_e170();                                    // 0x005bfff0
    void Init(INameable_s00d0_e170* nameable, IWindow_s00d0_e170* window, uint32_t a, bool b, uint32_t c);   // 0x005bfd40
    void SetPrompt(const wchar_t* prompt);                // 0x005c0320
};
}
namespace SP {
struct cLimitMeter {
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
    virtual void SetLimitType(int type);                  // 0x28
};
}
namespace SP {
class cString_s00d0_e170 { public:
    uint32_t data[4];
    cString_s00d0_e170();                                            // 0x006b5060
    ~cString_s00d0_e170();                                           // 0x006b5240
    void Load(uint32_t tableID, uint32_t instanceID, int);// 0x006b54b0
    const wchar_t* GetText();                             // 0x006b55c0
};
}
namespace SP {
struct cPropertyList_s00d0_e170;
}
namespace SP {
bool GetPropertyAsText(cPropertyList_s00d0_e170* props, uint32_t id, cString_s00d0_e170* out);   // 0x006a1360
}
namespace SP {
float GetPropertyF(uint32_t group, int, uint32_t prop, float def);         // 0x00bcea30
}
namespace SP {
int   GetPropertyInt(uint32_t group, int, uint32_t prop, int def);         // 0x00bda3b0
}
namespace SP {
uint32_t ColorRGBToU32(const void* rgb);                  // 0x00458a40
}
namespace SP {
const void* FUN_00b6f0c0(uint32_t colorID);
}
namespace SP {
uint32_t GetCurrentGameMode();                            // 0x00b5b800
}
namespace SP {
enum { kGameModeCiv_s00d0_e170 = 0x1654c04, kGameModeSpace_s00d0_e170 = 0x1654c05 };
}
namespace SP {
void FUN_00be2440(cCity_s00d0_e170* city, int, int);
}
namespace SP {
struct cUnkB3D3F0 { void FUN_00e19010(); };
}
namespace SP {
cUnkB3D3F0* FUN_00b3d3f0();
}
namespace SP {
struct cUnkB3D400 { void FUN_00e14c10(int); };
}
namespace SP {
cUnkB3D400* FUN_00b3d400();
}
namespace SP {
struct cUnkB3D230 {
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
virtual void v11();
virtual void v12();
virtual void v13();
    virtual void FUN_slot14(uint32_t id, bool b);         // 0x38
};
}
namespace SP {
cUnkB3D230* FUN_00b3d230();
}
namespace SP {
struct cUnk401090 { const ResourceKey_s00d0_e170* FUN_004df400(); };
}
namespace SP {
cUnk401090* FUN_00401090();
}
namespace SP {
void FUN_00e3c7c0(uint32_t eventID, const ResourceKey_s00d0_e170* key, ResourceKey_s00d0_e170* a, ResourceKey_s00d0_e170* b,
                  int politicalID, int, int);
}
namespace SP {
void FUN_00e398e0(uint32_t eventID, const ResourceKey_s00d0_e170* key, ResourceKey_s00d0_e170* a, ResourceKey_s00d0_e170* b,
                  uint32_t chief, int, int);
}
namespace SP {
void FUN_00ba58e0(cTribe_s00d0_e170* tribe, int);
}
namespace SP {
void FUN_00ba5a60(cCivilization_s00d0_e170* civ, int);
}
namespace SP {
class cCommunityEditor_s00d0_e170;
}
namespace SP {
extern cCommunityEditor_s00d0_e170* g_pCommunityEditor;              // 0x0169d580
}
namespace SP {
class cCommunityEditor_s00d0_e170 { public:
    virtual void HandleMessage();                         // IHandlerRC primary base (vptr +0) 0x00d130d0
    uint32_t pad04[4];
    AutoHandler   mActiveAutoHandler;                     // +0x14
    uint32_t      mPassiveAutoHandler[5];                 // +0x28
    cPropertyList_s00d0_e170* mConfigProps;                          // +0x3c
    AutoRefCount_s00d0_e170<cCommunity_s00d0_e170> mpCommunity;                 // +0x40
    uint32_t      mSelectedCategoryID;                    // +0x44
    uint32_t      mShoppingModelType;                     // +0x48
    uint32_t      mLastShoppingModelType;                 // +0x4c
    ResourceKey_s00d0_e170   mRecentlyEditedModelKey;                // +0x50
    bool          mbFromShopping;                         // +0x5c
    uint8_t       pad5d[3];
    int           mEconomyState;                          // +0x60
    uint32_t      mPaletteInstance;                       // +0x64
    AutoRefCount_s00d0_e170<cEditorEconomy_s00d0_e170>  mEconomy;               // +0x68
    AutoRefCount_s00d0_e170<cSPEditorBudget_s00d0_e170> mBudget;                // +0x6c
    IWindow_s00d0_e170*      mpWinBudget;                            // +0x70
    uint32_t      pad74;
    AutoRefCount_s00d0_e170<cCollectableItems_s00d0_e170> mCollectableItems;    // +0x78
    uint32_t      pad7c[2];
    cLimitMeter*  mpLimitMeter;                           // +0x84
    cSPUILayout_s00d0_e170   mEditorUI;                              // +0x88
    uint32_t      pad94[3];
    AutoRefCount_s00d0_e170<cSPUIPropertyLayout_s00d0_e170> mCityStats;         // +0xa0
    AutoRefCount_s00d0_e170<cSPEditorNaming_s00d0_e170>     mNaming;            // +0xa4
    IWindow_s00d0_e170*      mpWinSwatchRoot;                        // +0xa8
    AutoRefCount_s00d0_e170<cCityMusicEditor>    mCityMusicEditor;   // +0xac
    AutoRefCount_s00d0_e170<cSPPalette_s00d0_e170>          mPaletteData;       // +0xb0
    AutoRefCount_s00d0_e170<cSPPaletteUI_s00d0_e170>        mPaletteUI;         // +0xb4
    IWindow_s00d0_e170*      mWinPaletteRoot;                        // +0xb8
    cGameNoun*    mpRotationRing;                         // +0xbc
    uint32_t      padc0;
    void*         mpSelectedObject;                       // +0xc4
    uint8_t       padc8[0x114 - 0xc8];
    rbtree_map    mAnimatedObjectMap;                     // +0x114
    sp_vector_s00d0_e170<void*>         mPreExistingBuildings;       // +0x130
    uint32_t      pad140;
    sp_vector_s00d0_e170<cSpatialNoun*> mPreExistingNouns;           // +0x144
    uint8_t       pad154[0x1dc - 0x154];
    sp_vector_s00d0_e170<void*>         mPreExistingTools;           // +0x1dc
    uint8_t       pad1ec[0x204 - 0x1ec];
    int           mActivationMode;                        // +0x204
    bool          mbEffectsDirty;                         // +0x208
    bool          mbHintsIdle;                            // +0x209
    uint8_t       pad20a[0x2c4 - 0x20a];
    uint32_t      mSavedCameraZoomState;                  // +0x2c4
    uint8_t       pad2c8[0x2d8 - 0x2c8];
    uint32_t      mSavedAnchorDir[3];                     // +0x2d8
    uint32_t      mSavedAngles[3];                        // +0x2e4
    cCommunity_s00d0_e170*   mpSavedCameraCommunity;                 // +0x2f0

    void Activate(cCommunity_s00d0_e170* community, bool bSpaceGame);  // 0x00d0e170 (SP::cCommunityEditor::Activate)
    uint32_t GetCameraZoomProgramID();                    // 0x00d098b0
    void SetDefaultCamera(bool b);                        // 0x00d0b3b0
    void SetManipulatedObject(void* obj);                 // 0x00d09f60
    void FUN_00d0aa70();
    void SetKeyForModelType(uint32_t modelType, ResourceKey_s00d0_e170* key);         // 0x00d09560
    void UpdateSwatchForModelType(uint32_t modelType, const ResourceKey_s00d0_e170* key, uint32_t extra); // 0x00d0c820
    void SetupShoppingUI(uint32_t modelType, ResourceKey_s00d0_e170 key, bool b);     // 0x00d08b50
    void UpdateLimitMeter(int category);                  // 0x00d0a1e0
};
}
namespace SP {
static __forceinline void UnlockItems(cCollectableItems_s00d0_e170* items, uint32_t listID, sp_vector_s00d0_e170<uint32_t>& ids)
{
    int n = ids.size();
    for (int i = 0; i < n; ++i) {
        cCollectableItems_s00d0_e170::Key k = FUN_00593980(listID, ids[i]);
        items->AddUnlock(k, 0, 0, 0, 0, 0, 0.0f, 0);
        items->Unlock(k);
    }
}
}
namespace SP {
static __forceinline void FireModelTypeEvent(uint32_t eventID, ResourceKey_s00d0_e170* modelKey)
{
    ResourceKey_s00d0_e170 none;
    FUN_00e3c7c0(eventID, &NounManager_s00d0_e170()->GetPlayerCivilization()->FUN_00bef950()->mKey,
                 modelKey, &none, NounManager_s00d0_e170()->GetPlayerCivilization()->mPoliticalID, 0, 0);
}
}
// ---- items of slice s00d0e170 end

namespace __equiv_ann1 {
struct I {
    void DoInsertValue();   // 0x004558a0 (equiv t2)
};
}

// ---- items of slice s00d10840 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define VS1(n) virtual void n();
#define VS4(n) VS1(n##0) VS1(n##1) VS1(n##2) VS1(n##3)
struct Vector3_s00d1_0840 {
    float x, y, z;
    Vector3_s00d1_0840() {}
    Vector3_s00d1_0840(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    Vector3_s00d1_0840(const Vector3_s00d1_0840& v) : x(v.x), y(v.y), z(v.z) {}
};
inline Vector3_s00d1_0840 operator-(const Vector3_s00d1_0840& a, const Vector3_s00d1_0840& b) { Vector3_s00d1_0840 r; r.x = a.x - b.x; r.y = a.y - b.y; r.z = a.z - b.z; return r; }
inline Vector3_s00d1_0840 operator+(const Vector3_s00d1_0840& a, const Vector3_s00d1_0840& b) { Vector3_s00d1_0840 r; r.x = a.x + b.x; r.y = a.y + b.y; r.z = a.z + b.z; return r; }
inline Vector3_s00d1_0840 operator*(const Vector3_s00d1_0840& a, float f) { Vector3_s00d1_0840 r; r.x = a.x * f; r.y = a.y * f; r.z = a.z * f; return r; }
inline Vector3_s00d1_0840 Cross(const Vector3_s00d1_0840& a, const Vector3_s00d1_0840& b) { Vector3_s00d1_0840 r; r.x = a.y * b.z - a.z * b.y; r.y = a.z * b.x - a.x * b.z; r.z = a.x * b.y - a.y * b.x; return r; }
struct BoundingBox {
    Vector3_s00d1_0840 lower;
    Vector3_s00d1_0840 upper;
};
namespace SP {
class cCity_s00d1_0840;
}
namespace SP {
class cBuilding_s00d1_0840;
}
namespace SP {
class cPlaceable;
}
namespace SP {
class cBuildingSet;
}
namespace SP {
class cSnapEntry;
}
namespace SP {
class cSpatialObject_s00d1_0840 {
public:
    VS4(a) VS4(b) VS1(c0) VS1(c1) VS1(c2)                       // 0x00 .. 0x28
    virtual const Vector3_s00d1_0840& GetPosition();                        // +0x2c
    VS1(d0) VS1(d1)                                              // +0x30, +0x34
    virtual void SetPosition(const Vector3_s00d1_0840& position);           // +0x38
    virtual void SetOrientation(const Quaternion& q);            // +0x3c
    VS4(e) VS1(f0) VS1(f1) VS1(f2)                               // +0x40 .. +0x58
    virtual Vector3_s00d1_0840 GetDirection();                              // +0x5c
    VS1(g0) VS1(g1)                                              // +0x60, +0x64
    virtual const BoundingBox& GetLocalExtents();                // +0x68
    VS4(h) VS4(i) VS4(j) VS4(k) VS1(l0) VS1(l1) VS1(l2)          // +0x6c .. +0xb4
    virtual void* Cast(uint32_t type);                           // +0xb8
    uint32_t pad04[(0x6e - 4) / 4];                              // up to +0x6c
    uint16_t pad6c;
    bool mbIsInvalid;                                            // +0x6e
};
}
namespace SP {
class cCommunity_s00d1_0840 {
public:
    VS1(a0) VS1(a1) VS1(a2)
    virtual void* Cast(uint32_t type);                           // +0x0c
    VS4(b) VS4(c) VS4(d) VS4(e) VS1(f0) VS1(f1)                  // +0x10 .. +0x54
    virtual Vector3_s00d1_0840 GetCenter();                                 // +0x58 (hidden out pointer)
};
}
namespace SP {
class cCity_s00d1_0840 {
public:
    VS4(a) VS4(b) VS4(c) VS4(d) VS4(e) VS1(f0) VS1(f1)           // +0x00 .. +0x57
    virtual Vector3_s00d1_0840 GetPosition();                               // +0x58 (hidden out pointer)
    void RefreshAfterEdit();                                     // 0x00bd7f30
    bool FUN_00bdfb00(cPlaceable* pPlaceable, Quaternion* pOut); // 0x00bdfb00
};
}
namespace SP {
class ICameraManager {
public:
    VS4(a) VS4(b) VS4(c) VS1(d0) VS1(d1)
    virtual Vector3_s00d1_0840 Pick(int mode, Vector3_s00d1_0840 screen);              // +0x38
    VS4(e) VS4(f)                                                // +0x3c .. +0x58
    virtual void PlayEffect(uint32_t effectID, const Vector3_s00d1_0840& position, const Vector3_s00d1_0840& direction, int a, int cost, float f);   // +0x5c
};
}
namespace SP {
class cPlanetModel_s00d1_0840 {
public:
    Vector3_s00d1_0840 ToSurface(const Vector3_s00d1_0840& pos);                                     // 0x00b81630
    Quaternion BuildSurfaceOrientation(const Vector3_s00d1_0840& pos, const Vector3_s00d1_0840& dir); // 0x00b7f250
};
}
namespace SP {
class IAudioSystem {
public:
    VS4(a) VS4(b)
    virtual uint32_t GetState();                                 // +0x20
};
}
namespace SP {
struct cSnapEntry {
    uint8_t mbUsed;       // +0x00
    uint8_t pad01[3];
    void* mpObject;       // +0x04
    uint32_t pad08;
    Vector3_s00d1_0840 mPosition;    // +0x0c
    void Clear();                       // 0x00afa0a0
    void Occupy(void* pObject);         // 0x00afa030
};
}
namespace SP {
class cSnapLayout {
public:
    uint32_t pad[0x50 / 4];
    cSnapEntry* mpEntries;              // +0x50
};
}
namespace SP {
class cSellBackRollover {
public:
    uint32_t pad[0x9e / 4];
    void HideWin();                     // 0x005cc690
    void Show(const wchar_t* text, int cost, int arg);   // 0x005cc750
};
}
namespace SP {
class cSellBackRolloverBase {
public:
    VS1(a0) VS1(a1)
    virtual void Hide();                                        // +0x08
};
}
namespace SP {
class cString_s00d1_0840 {
public:
    uint32_t mData[9];
    cString_s00d1_0840();                                          // 0x006b5060
    ~cString_s00d1_0840();                                         // 0x006b5240
    void Load(uint32_t tableID, uint32_t instanceID, const wchar_t* pDefault);  // 0x006b54b0
    const wchar_t* GetText();                           // 0x006b55c0
};
}
namespace SP {
class cCursorAttachment {
public:
    void SetWindow(void* pWindow);                      // 0x008017f0
};
}
namespace SP {
struct cSPVector3 {
    float x, y, z;
    cSPVector3& operator=(const Vector3_s00d1_0840& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
}
namespace SP {
class cAnimatedObjectMap {
public:
    cSPVector3& operator[](cSpatialObject_s00d1_0840* const& key);    // 0x00d0fee0
};
}
namespace SP {
ICameraManager* CameraManager();                         // 0x00b3d240
}
namespace SP {
cPlanetModel_s00d1_0840* PlanetModel_s00d1_0840();                             // 0x00b3d350
}
namespace SP {
IAudioSystem* GetSystemAT();                             // 0x00a206f0
}
namespace SP {
uint32_t GetAudioState();                                // 0x00435e90 (GetSystemAT() ? ->GetState() : 0)
}
namespace SP {
void KillSetiEffects(uint32_t id, uint32_t state);      // 0x00435ed0 (cdecl)
}
namespace SP {
uint32_t SPIDFromName(const char* name);                 // 0x00571cf0
}
namespace SP {
float GetPropertyT_float(uint32_t listID, uint32_t groupID, uint32_t propID, float defaultValue);  // 0x00bcea30
}
namespace SP {
Vector3_s00d1_0840 normalized_safe(const Vector3_s00d1_0840& v);               // 0x00449c20
}
namespace SP {
Vector3_s00d1_0840 Vector3_Normalize(const Vector3_s00d1_0840& v);             // 0x00436ce0
}
namespace SP {
void* GetObjectSnapInterface(cSpatialObject_s00d1_0840* pObject);  // 0x00ae66d0 (Cast(0x17f243b))
}
namespace SP {
cCursorAttachment* CursorAttachment();                   // 0x0067cab0
}
namespace SP {
cBuilding_s00d1_0840* interface_cast_building(cSpatialObject_s00d1_0840* p);   // 0x00cf10b0
}
namespace SP {
void FUN_00be2440(cCity_s00d1_0840* pCity, int a, int b);           // 0x00be2440 (cdecl)
}
namespace SP {
struct ResourceKey_s00d1_0840 {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};
}
namespace SP {
class IWindow_s00d1_0840 {
public:
    VS4(a) VS1(b0) VS1(b1)
    virtual void SetFlag(int flag, int value);                   // +0x18
};
}
namespace SP {
class cCombatant_s00d1_0840 {
public:
    int GetDamageState();                                        // 0x008e7f80
};
}
namespace SP {
class cPlaceable {                                               // Cast(0xe9cb8ba)
public:
    uint32_t pad04[12];
    cSpatialObject_s00d1_0840 mSpatial;                                     // +0x34 (embedded spatial interface)
    bool FUN_00c3f540();                                         // 0x00c3f540
};
}
namespace SP {
class cSellEffect {                                              // Cast(0xe89adf71)
public:
    VS1(a0) VS1(a1) VS1(a2)
    virtual uint32_t GetEffectID();                              // +0x0c
};
}
namespace SP {
class cTool {                                                    // Cast(0x116d858)
public:
    VS4(a) VS4(b) VS4(c) VS4(d) VS4(e) VS1(f0) VS1(f1)           // +0x00 .. +0x57
    virtual int GetToolType();                                   // +0x58
};
}
namespace SP {
class cTribe_s00d1_0840 {
public:
    uint32_t pad[0x234 / 4];
    uint32_t mField234;                                          // +0x234
    void FUN_00c947d0(float amount, const Vector3_s00d1_0840* pPosition);   // 0x00c947d0
    bool FUN_00c8ec00(int toolType);                             // 0x00c8ec00
    char* FUN_00c8e820(int toolType);                            // 0x00c8e820
    void FUN_00c8ebe0(int toolType);                             // 0x00c8ebe0
};
}
namespace SP {
class cTerrainSphere_s00d1_0840 {
public:
    void FUN_00c78420(const ResourceKey_s00d1_0840* pKey);                  // 0x00c78420
    int FUN_00c75420();                                          // 0x00c75420
};
}
namespace SP {
class cGameNounManager_s00d1_0840 {
public:
    cTerrainSphere_s00d1_0840* GetCurrentTerrainSphere();                   // 0x00f67d90
};
}
namespace SP {
cGameNounManager_s00d1_0840* NounManager_s00d1_0840();                                 // 0x00b3d300
}
namespace SP {
class IMessageServer_s00d1_0840 {
public:
    VS4(a) VS1(b0)
    virtual void PostMessage(uint32_t messageID, void* pMessage, int flags);   // +0x14
};
}
namespace SP {
IMessageServer_s00d1_0840* MessageServer_s00d1_0840();                                 // 0x0067dcc0
}
namespace SP {
struct cMsgBase_s00d1_0840 { virtual void Base0(); };
}
namespace SP {
struct cMsgData_s00d1_0840 { virtual void Data0(); int mField8; int mFieldC; cMsgData_s00d1_0840() : mField8(0) {} };
}
namespace SP {
struct cSetCreationMsg_s00d1_0840 : cMsgBase_s00d1_0840, cMsgData_s00d1_0840 {
    ResourceKey_s00d1_0840 mKey;
    int         mToolType;
    explicit cSetCreationMsg_s00d1_0840(int toolType) : mToolType(toolType) {}
    virtual void Base0();
};
}
namespace SP {
void Start3dSoundByName(uint32_t soundID, uint32_t state, Vector3_s00d1_0840 position);   // 0x00571f80 (cdecl)
}
namespace SP {
int FUN_00c9cec0(int toolType);                                  // 0x00c9cec0 (cdecl)
}
namespace SP {
void FUN_00e398e0(uint32_t id, char* pKey, const Vector3_s00d1_0840* pPos, int a, uint32_t b, int c, int d);   // 0x00e398e0 (cdecl)
}
namespace SP {
int FUN_00d08f00(cSpatialObject_s00d1_0840* pObject);                       // 0x00d08f00 (cdecl)
}
namespace SP {
class cCommunityEditor_s00d1_0840 {
public:
    uint32_t pad00[0x40 / 4];
    cCommunity_s00d1_0840* mpCommunity;                // +0x40
    uint32_t pad44[(0x68 - 0x44) / 4];
    IWindow_s00d1_0840* mpWinBudget;                   // +0x68
    uint32_t pad6c[(0x7c - 0x6c) / 4];
    cSellBackRolloverBase* mpSellbackRollover;  // +0x7c
    uint32_t pad80;
    cSellBackRollover* mpSellbackLayout;    // +0x84
    uint32_t pad88[(0xc0 - 0x88) / 4];
    cSpatialObject_s00d1_0840* mpManipulatedObject;    // +0xc0
    uint32_t padc4;
    cSpatialObject_s00d1_0840* mpSwapObject;           // +0xc8
    uint32_t padcc[(0xe8 - 0xcc) / 4];
    Vector3_s00d1_0840 mCursorScreenPos;               // +0xe8
    cSnapLayout* mpCurrentSnapLayout;       // +0xf4
    int mOriginalSnapPointIndex;            // +0xf8
    int mCurrentSnapPointIndex;             // +0xfc
    int mLastSnapPointIndex;                // +0x100
    int mLastSwapPointIndex;                // +0x104
    uint32_t pad108[(0x110 - 0x108) / 4];
    cAnimatedObjectMap mAnimatedObjectMap;  // +0x110 (the map's anchor sits at +0x114)
    uint32_t pad114[(0x27c - 0x114) / 4];
    uint32_t mAttractorEffectID;            // +0x27c
    uint32_t mSnapEffectID;                 // +0x280
    uint32_t mUnsnapEffectID;               // +0x284
    uint32_t mPlunkEffectID;                // +0x288
    uint32_t mRipEffectID;                  // +0x28c

    bool UpdateObjectPlacement(void* pWindow, void* pMessage);  // 0x00d10840 (SP::cCommunityEditor::UpdateObjectPlacement)
    bool EndObjectPlacement(void* pWindow, void* pMessage);  // 0x00d10f90 (SP::cCommunityEditor::EndObjectPlacement)

    int GetIndexOfClosestSnapPoint(cSnapLayout* pLayout, Vector3_s00d1_0840 position, int arg, cSpatialObject_s00d1_0840** ppSwapObject); // 0x00d0b710
    Vector3_s00d1_0840* SnapPointToPlanetIfNecessary(Vector3_s00d1_0840* pOut, Vector3_s00d1_0840 position, cSpatialObject_s00d1_0840* pObject); // 0x00d09f00
    void CreateOneShotEffect(uint32_t effectID, Vector3_s00d1_0840 position);   // 0x00d0ba80
    void HandleSwapObject();                                         // 0x00d10720
    int GetObjectCost(cSpatialObject_s00d1_0840* pObject, int a, int b);        // 0x00d0abd0
    void RemoveObjectFromCommunity(cSpatialObject_s00d1_0840* pObject);         // 0x00d09d30
    void SetManipulatedObject(cSpatialObject_s00d1_0840* pObject);              // 0x00d09f60
    void FUN_00d0bcf0(cSpatialObject_s00d1_0840* pObject);                      // 0x00d0bcf0
    void FUN_00d0dea0();                                             // 0x00d0dea0
    void FUN_00d0a390();                                             // 0x00d0a390
    void FUN_00d0a5b0();                                             // 0x00d0a5b0
    bool FUN_00d096e0(cBuildingSet* pSet);                           // 0x00d096e0
};
}
// ---- items of slice s00d10840 end

// s00d124e0's member-pointer typedefs: rewrite's item_names() does not see the name in
// `typedef void (VtblObj::*PMF0)();`, so the slice's VCall0/VCall1 helpers lose them (C2065).
// The forward declaration goes through a macro so it does not make the slice's `struct VtblObj`
// look like a conflicting TU item (which would rename it and split the type).
#define SPCOMMUNITYEDITOR_FWD_VTBLOBJ struct VtblObj;
SPCOMMUNITYEDITOR_FWD_VTBLOBJ;
typedef void  (VtblObj::*PMF0)();
typedef void  (VtblObj::*PMF1)(void*);

// ---- items of slice s00d124e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma warning(disable: 4100 4189 4244 4311 4312)
void  Free5(void* a, void* b, void* c, void* d, void* e);                    // 0x00571db0
struct CalleeSet {
    void  FUN_00d11f80(void* a, int n, void* b);      // 0x00d11f80
    void  FUN_00d0c5b0(void* a);                      // 0x00d0c5b0
    void  FUN_00d100b0(int a, int b);                 // 0x00d100b0
    void  FUN_00d099c0(void* a);                      // 0x00d099c0
    void  FUN_00d0b540(void* a);                      // 0x00d0b540
    u8    FUN_00d0a160();                             // 0x00d0a160
    void  FUN_00d0e170(void* a, int b);               // 0x00d0e170
    void  FUN_00d0b3b0(void* a);                      // 0x00d0b3b0
    void  FUN_00d0fcc0(void* a);                      // 0x00d0fcc0
    void  FUN_00d10840(void* a, void* b);             // 0x00d10840
    void  FUN_00d10f90(void* a, void* b);             // 0x00d10f90
    void  FUN_00d09770(void* a, void* b);             // 0x00d09770
    void  FUN_00d0c170(void* a, void* b);             // 0x00d0c170
    void  FUN_00d0ae50(void* a, void* b);             // 0x00d0ae50
    void  FUN_00d11730(void* a, void* b);             // 0x00d11730
    void  FUN_00d0a470(void* a, void* b);             // 0x00d0a470
    void  FUN_00d08ad0();                             // 0x00d08ad0
    void  FUN_00d08a70(void* a, void* b);             // 0x00d08a70
    void  FUN_00d08aa0();                             // 0x00d08aa0
    void  FUN_00d0d570(void* a);                      // 0x00d0d570
    void  FUN_005ca980(void* a);                      // 0x005ca980
    void  FUN_005cb240(void* a);                      // 0x005cb240
    void  FUN_005a7840();                             // 0x005a7840
    void  FUN_004582b0(void* a);                      // 0x004582b0
    void  FUN_00bdde70(void* a);                      // 0x00bdde70
    void  FUN_00ea13e0();                             // 0x00ea13e0
    void* FUN_00b25fb0();                             // 0x00b25fb0
    void* FUN_00bef6c0();                             // 0x00bef6c0
    void  FUN_00b10c40(int b);                        // 0x00b10c40
    void  FUN_00b0f210();                             // 0x00b0f210
    void* FUN_00b10260();                             // 0x00b10260
    void  FUN_00b10340();                             // 0x00b10340
    void  FUN_00b13bb0(void* a, void* b);             // 0x00b13bb0
    void* FUN_00b7f190();                             // 0x00b7f190
    void* FUN_00434040();                             // 0x00434040
    void* FUN_00b3d350(void* a);                      // 0x00b3d350
    void* FUN_0059c190(void* a);                      // 0x0059c190
    void* FUN_00705b0(void* a, void* b);              // 0x008105b0
    void  FUN_00811ad0(void* a);                      // 0x00811ad0
};
#define SELF(o) ((CalleeSet*)(o))
struct VtblObj {
    void  C0();
    void  C1(void*);
    void  C2(void*, void*);
    void  C3(void*, void*, void*);
    void* R0();
    void* R1(void*);
    void* R2(void*, void*);
    u8    B1(void*);
};
inline void  VCall0(void* p, u32 o)                            { (((VtblObj*)p)->*(*(PMF0*)((u8*)*(void**)p + o)))(); }
inline void  VCall1(void* p, u32 o, void* a)                   { (((VtblObj*)p)->*(*(PMF1*)((u8*)*(void**)p + o)))(a); }
inline void RefRelease(void* p) { if (p) VCall0(p, 0x04); }
struct Class12 {
    u8      mGap00[0x28];
    void*   mp28;
    void*   mp2c;
    void*   mp30;
    void*   mp34;
    void*   mp38;
    void*   mp3c;
    void*   mp40;
    void*   mp44;
    u8      mGap48[0x20];
    void*   mp68;
    void*   mp6c;
    u8      mGap70[0x04];
    void*   mp74;
    u8      mGap78[0x0c];
    void*   mp84;
    u8      mGap88[0x18];
    void*   mpA0;
    u8      mGapA4[0x08];
    void*   mpAc;
    u8      mGapB0[0x04];
    void*   mpB4;
    u8      mGapB8[0x08];
    void*   mpC0;
    u8      mGapC4[0x144];
    u8      mB208;
    u8      mGap209[0x03];
    void*   mp20c;
    u8      mGap210[0x18];
    void*   mp228;
    u8      mGap22c[0x48];
    u8      mB274;
    u8      mGap275[0x03];
    void*   mp278;
    u8      mGap27c[0x14];
    void*   mp290;
    void*   mp294;
    u8      mGap298[0x24];
    u8      mB2bc;
    u8      mGap2bd[0x03];
    void*   mp2c0;
    u8      mGap2c4[0x04];
    float   mF2c8;
    float   mF2cc;
    float   mF2d0;
    float   mF2d4;
    u8      mGap2d8[0x14];
    u32     mF2ec;
    u8      mGap2f0[0x08];
    void*   mp2f8;

    void FUN_00d124e0(void* pArg);
    u8   FUN_00d12910(void* pMsg, int nType);
    u8   FUN_00d12d00(void* pMsg, int nType);
    void FUN_00d12fc0();
};
// ---- items of slice s00d124e0 end

// ---- items of slice s00d130d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char kAppAllocName[]; // "App" (0x013ebc58)
struct ResourceKey_s00d1_30d0 {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};
struct Vector3_s00d1_30d0 {
    float x, y, z;
    Vector3_s00d1_30d0() {}
    Vector3_s00d1_30d0(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    Vector3_s00d1_30d0(const Vector3_s00d1_30d0& v) : x(v.x), y(v.y), z(v.z) {}
};
#define VS16(n) VS4(n##a) VS4(n##b) VS4(n##c) VS4(n##d)
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file,
                   int line);
namespace EA {
template <typename T> class AutoRefCount_s00d1_30d0 {
public:
    T* mpObject;
    AutoRefCount_s00d1_30d0() : mpObject(0) {}
    AutoRefCount_s00d1_30d0(T* p); // 0x00572660
    ~AutoRefCount_s00d1_30d0()
    {
        if (mpObject)
            mpObject->Release();
    }
    AutoRefCount_s00d1_30d0& operator=(T* p); // 0x00b5f950
    T** AsPPTypeParam();           // 0x00a16f40
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};  // namespace EA
}
namespace eastl {
template <typename T> class intrusive_ptr_s00d1_30d0 {
public:
    T* mpObject;
    intrusive_ptr_s00d1_30d0(T* p); // 0x0061df40
    ~intrusive_ptr_s00d1_30d0() { mpObject->Release(); }
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }
};
}
namespace eastl {
template <typename T> class vector_s00d1_30d0 {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator;
    void push_back(const T& value); // 0x00454860 (uint32_t), 0x00e1c7f0 (AutoRefCount)
    T& operator[](uint32_t n) { return mpBegin[n]; }
    int size() const { return (int)(mpEnd - mpBegin); }
};
}
namespace eastl {
struct wstring {
    uint32_t mData[9];
    wstring& operator=(const wchar_t* p); // 0x005c3d90
};
}
namespace SP {
class cCity_s00d1_30d0;
}
namespace SP {
class cTribe_s00d1_30d0;
}
namespace SP {
class cCommunity_s00d1_30d0;
}
namespace SP {
class cSpatialObject_s00d1_30d0;
}
namespace SP {
class cSPPaletteItem_s00d1_30d0;
}
namespace SP {
struct RefObject {
    virtual int AddRef();
    virtual int Release();
};
}
namespace SP {
class cPropertyList_s00d1_30d0 : public RefObject { public:};
}
namespace SP {
struct cSwatch : RefObject {};
}
namespace SP {
class IResource : public RefObject {};
}
namespace SP {
class cEditorResource_s00d1_30d0 {
public:
    uint32_t pad00[6];
    uint32_t mModelType; // +0x18
};
}
namespace SP {
class IResourceManager {
public:
    VS1(v00) VS1(v04) VS1(v08)
    virtual bool GetResource(const ResourceKey_s00d1_30d0& name, IResource** ppResource, int arg8, void* pDBPF,
                             void* pFactory, const ResourceKey_s00d1_30d0* pCacheName); // +0x0c
};
}
namespace SP {
class IPropertyManager {
public:
    VS4(v) VS4(w) VS1(x0) VS1(x1) VS1(x2)
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, cPropertyList_s00d1_30d0** ppList); // +0x2c
};
}
namespace SP {
class IConfigManager {
public:
    VS4(v) VS4(w) VS4(x)
    virtual uint32_t GetConfigValue(uint32_t id); // +0x30
};
}
namespace SP {
class IApp_s00d1_30d0 {
public:
    VS4(v) VS4(w) VS4(x) VS1(y0) VS1(y1)
    virtual uint32_t GetCurrentModeID(); // +0x38
};
}
namespace SP {
class IMessage {
public:
    virtual void v00();
    virtual int AddRef();  // +0x04
    virtual int Release(); // +0x08
};
}
namespace SP {
class IMessageServer_s00d1_30d0 {
public:
    VS4(v) VS1(w0)
    virtual void PostMessage(uint32_t messageID, IMessage* pMessage, int flags);           // +0x14
    virtual void MessageSend(uint32_t messageID, void* pData, int flags, void* pHandler); // +0x18
};
}
namespace SP {
class SlotMessage : public IMessage {
public:
    uint32_t pad04;
    int mSlot;           // +0x08
    uint32_t pad0c[9];
    uint32_t mMessageID; // +0x30
    uint32_t pad34[3];
    explicit SlotMessage(int arg); // 0x00421c80
};
}
namespace SP {
namespace Editor {
struct cEditorLaunchData_s00d1_30d0 : public IMessage { private:
public:
    uint32_t pad04[2];
    uint32_t mConfig;                   // +0x0c
    ResourceKey_s00d1_30d0 mModelKey;              // +0x10
    uint32_t mCallingAppModeID;         // +0x1c
    uint32_t pad20;
    uint32_t mEditorValidationLevel[4]; // +0x24
    bool mCanSwitchEditor;              // +0x34
    bool mUseAlternateName;             // +0x35
    bool mShowLoadButton;               // +0x36
    bool mShowSaveButton;               // +0x37
    bool mShowNewButton;                // +0x38
    bool mConfirmOnExit;                // +0x39
    bool pad3a[2];
    bool mShowPublishButton;            // +0x3c
    bool mAllowNaming;                  // +0x3d
    bool pad3e[2];
    eastl::wstring mAlternateName;      // +0x40
    bool mUsePlanetColors;              // +0x64
    bool pad65[8];
    bool mUseSphere;                    // +0x6d
    bool pad6e[2];
    eastl::vector_s00d1_30d0<uint32_t> mPlanetColors; // +0x70
    uint32_t pad80[4];
    uint32_t mCallerID;                 // +0x90
    EA::AutoRefCount_s00d1_30d0<RefObject> mCallerData; // +0x94
    uint32_t pad98;

    cEditorLaunchData_s00d1_30d0(); // 0x005a9080
};  // namespace Editor
}
}
namespace SP {
class cEditorManager {
public:
    void LaunchEditor(Editor::cEditorLaunchData_s00d1_30d0* pData); // 0x00b1dee0
};
}
namespace SP {
class cLocaleTable {
public:
    const wchar_t* GetText(uint32_t id); // 0x00b6a6e0
};
}
namespace SP {
class cTerrainSphere_s00d1_30d0 {
public:
    uint32_t pad[0x10fc / 4];
    int mColors[5];      // +0x10fc
    void ShowUIHint(uint32_t hintID); // 0x00c77bf0
};
}
namespace SP {
class cGameNounManager_s00d1_30d0 {
public:
    cTerrainSphere_s00d1_30d0* GetCurrentTerrainSphere();      // 0x00f67d90
    void* CreateNoun(uint32_t nounID);              // 0x00b20c60
    void RemoveNoun(uint32_t id);                   // 0x00b225d0
    class cCivilization_s00d1_30d0* GetPlayerCivilization();   // 0x00b25fb0
};
}
namespace SP {
class cGameTimeManager_s00d1_30d0 {
public:
    void IncPauseGate(uint32_t id); // 0x00b32220
};
}
namespace SP {
class cTribeModeStrategy {
public:
    uint32_t pad[0x19c / 4];
    EA::AutoRefCount_s00d1_30d0<RefObject> mTribeText; // +0x19c
    uint32_t pad1a0[(0x24c - 0x1a0) / 4];
    uint32_t mEditedToolType;               // +0x24c
    static cTribeModeStrategy* Instance();  // 0x00cd40b0
};
}
namespace SP {
class cEmpire_s00d1_30d0 {
public:
    uint32_t pad[3];
    cLocaleTable mNames; // +0x0c
};
}
namespace SP {
class cCivilization_s00d1_30d0 {
public:
    VS16(v) VS1(w0) VS1(w1) VS1(w2)
    virtual uint32_t GetModelTypeForItem(uint32_t itemID); // +0x4c
    uint32_t pad04[14];
    struct tGameData {
        cLocaleTable mNames;      // +0x3c (string table lookup at +8)
        uint32_t mPoliticalID;    // +0x40
        uint32_t GetPoliticalID() const { return mPoliticalID; }
    } mData;                      // +0x3c
    void* GetCitizenAudio();      // 0x00bef950
    uint32_t GetModelTypeKey(uint32_t modelType); // 0x00bf9770
    int CanAffordVehicle(int specialty);          // 0x00bf2100
    void* CreateVehicleFromModelType(uint32_t modelType, const ResourceKey_s00d1_30d0& key); // 0x00bf4b10
};
}
namespace SP {
class cCityHall {
public:
    VS16(v) VS4(w) VS4(x)
    virtual void SetCityID(uint32_t id); // +0x60
};
}
namespace SP {
class cCity_s00d1_30d0 {
public:
    VS16(v) VS4(w) VS4(x) VS1(y0) VS1(y1) VS1(y2)
    virtual cCityHall* GetCityHall(); // +0x6c 0x00bd9b40
    cCivilization_s00d1_30d0* GetCivilization();         // 0x00bd9bf0
    int GetVehicleSpecialty();                // 0x00bd81d0
    Vector3_s00d1_30d0 GetVehicleSpawnPoint(int locomotion); // 0x00bdca30
    void* CreateBuilding();                   // 0x00be1fb0
    void AddDecoration(void* pObject);        // 0x00be1e80
    void AddBuilding(void* pObject, int arg); // 0x00be1ef0
};
}
namespace SP {
class cCityHallBuildingSet {
public:
    void Refresh(); // 0x00be6f40
};
}
namespace SP {
class cSpatialObject_s00d1_30d0 {
public:
    VS4(v) VS4(w) VS1(x0) VS1(x1) VS1(x2)
    virtual void* SetScale(float scale);                  // +0x2c
    virtual const Quaternion& GetOrientation();           // +0x30
    virtual void v34();
    virtual void SetPosition(const Vector3_s00d1_30d0& position);    // +0x38
    virtual void SetOrientation(const Quaternion& q);     // +0x3c
    VS16(z) VS4(q) VS1(r)
    virtual void SetModelKey(uint32_t key);               // +0x94
    virtual void* GetModelWorldPosition();                // +0x98
};
}
namespace SP {
class cToolSpatial {
public:
    VS4(v) VS4(w) VS1(x0) VS1(x1) VS1(x2)
    virtual int GetSnapLocator(); // +0x2c
};
}
namespace SP {
class cTribeTool_s00d1_30d0 {
public:
    VS16(v) VS4(w) VS4(x) VS1(y)
    virtual void SetTribe(cTribe_s00d1_30d0* pTribe); // +0x64
    uint32_t pad04[12];
    cToolSpatial mSpatial;                 // +0x34
    uint32_t pad38[19];
    uint32_t mFlags;                       // +0x84
    uint32_t pad88[6];
    bool padA0[2];
    bool mbIsBeingPlaced;                  // +0xa2
    void Prepare();                        // 0x00c9d140
};
}
namespace SP {
struct tSnapSlot {
    uint32_t data[6];
    void StartEffect(); // 0x00afa0a0
};
}
namespace SP {
class cToolSnapSet {
public:
    uint32_t pad[0x50 / 4];
    tSnapSlot* mpSlots;                       // +0x50
    int FindSlotIndex(int locator);           // 0x00afab70
};
}
namespace SP {
class cTribe_s00d1_30d0 {
public:
    VS16(v) VS16(w) VS4(x) VS4(y) VS4(z) VS1(q)
    virtual cTribeTool_s00d1_30d0* CreateTool(uint32_t toolType);   // +0xb4
    virtual void RemoveTool(cTribeTool_s00d1_30d0* pTool);          // +0xb8
    uint32_t pad04[(0x3b4 - 4) / 4];
    cToolSnapSet mToolSnapSet;                           // +0x3b4
    cTribeTool_s00d1_30d0* GetToolOfType(uint32_t toolType);        // 0x00c8f6e0
};
}
namespace SP {
class cBuilding_s00d1_30d0 {
public:
    VS16(v) VS4(w) VS1(x)
    virtual void SetCity(cCity_s00d1_30d0* pCity); // +0x54
    uint32_t pad04[12];
    cSpatialObject_s00d1_30d0 mSpatial;            // +0x34
    uint32_t pad38[26];
    bool padA0[2];
    bool mbIsBeingPlaced;               // +0xa2
    void* GetModel();                   // 0x00bce470
};
}
namespace SP {
class cBuildingModel {
public:
    void SetRadius(void* p); // 0x00c3f160
};
}
namespace SP {
class cDecoration {
public:
    uint32_t pad[0x70 / 4];
    cSpatialObject_s00d1_30d0 mSpatial;            // +0x70
    uint32_t pad74[(0xde - 0x74) / 4];
    bool padDC[2];
    bool mbIsBeingPlaced;               // +0xde
    void SetModelProperty(uint32_t propertyID, uint32_t value); // 0x00c6f770
};
}
namespace SP {
class cVehicle_s00d1_30d0 {
public:
    virtual void v00();
    virtual int Release(); // +0x04
    uint32_t pad04[12];
    cSpatialObject_s00d1_30d0 mSpatial;            // +0x34
    uint32_t pad38[(0x5d0 - 0x38) / 4];
    uint32_t mBehavior;                 // +0x5d0
    uint32_t pad5d4[(0xb1c - 0x5d4) / 4];
    int mLocomotion;                    // +0xb1c
    int mPurpose;                       // +0xb20
    void SetJustEyeCandy(bool value);   // 0x00c9ecb0
    void SetSpeedBoost(int value);      // 0x00ca80e0
};
}
namespace SP {
class IBehaviorManager {
public:
    VS4(v) VS4(w) VS4(x) VS1(y0) VS1(y1)
    virtual void Track(void* pBehavior); // +0x38
};
}
namespace SP {
class IGameInputManager {
public:
    VS16(v) VS4(w) VS4(x) VS1(y)
    virtual void SetCursor(int cursorID, int arg); // +0x64
};
}
namespace SP {
class IWindow_s00d1_30d0 {
public:
    VS4(v) VS1(w0) VS1(w1)
    virtual void SetFlag(int flag, int value); // +0x18
};
}
namespace SP {
class cSellBackRollover_s00d1_30d0 {
public:
    VS1(v0) VS1(v1)
    virtual void Hide(); // +0x08
};
}
namespace SP {
class ICameraManager_s00d1_30d0 {
public:
    VS4(v) VS4(w) VS4(x) VS1(y0) VS1(y1)
    virtual Vector3_s00d1_30d0 Pick(int mode, Vector3_s00d1_30d0 screen); // +0x38
};
}
namespace SP {
class cPlanetModel_s00d1_30d0 {
public:
    Vector3_s00d1_30d0 ToSurface(const Vector3_s00d1_30d0& pos);                           // 0x00b81630
    Quaternion GetSurfaceOrientation(const Vector3_s00d1_30d0& pos, const Quaternion& q); // 0x00b7f1f0
};
}
namespace SP {
class cAudioState {};
}
namespace SP {
class cSpaceInventory {
public:
    uint32_t pad[3];
    struct { uint32_t pad[7]; float mValue; }* mpData; // +0x0c
    void SetMode(int mode);                           // 0x007eb820
};
}
namespace SP {
class cSimulatorSpaceGame {
public:
    cSpaceInventory* GetInventory(int which); // 0x01005180
    class cGameData_s00d1_30d0* GetPlayerTribe(int arg); // 0x00bfc5f0
};
}
namespace SP {
class cGameData_s00d1_30d0 {
public:
    void SetGameDataOwner(int arg); // 0x00fe5430
};
}
namespace SP {
class cPlanetSurface {
public:
    VS16(v) VS1(w0) VS1(w1) VS1(w2)
    virtual void* GetSurfaceData(); // +0x4c
};
}
namespace SP {
class cPlanet_s00d1_30d0 {
public:
    uint32_t pad[0xd4 / 4];
    cPlanetSurface mSurface;     // +0xd4
    bool IsHomeworld();          // 0x00c70b50
};
}
namespace SP {
class cCivModeStrategy {
public:
    void OnVehicleCreated(cVehicle_s00d1_30d0* pVehicle);         // 0x00cf8ec0
    void DoNextCivTutorial(uint32_t id, int arg);      // 0x00cfa990
};
}
namespace SP {
class cUIHintManager {
public:
    void ShowHint(ResourceKey_s00d1_30d0 key, const void* pLayout, int arg, Vector3_s00d1_30d0 position, int arg2,
                  int arg3);                           // 0x0067aaf0
};
}
namespace SP {
class cUIHints_s00d1_30d0 {
public:
    void SetEnabled(int arg, int enabled);             // 0x0067c420
};
}
namespace SP {
class cRotationRing_s00d1_30d0 {
public:
    void SetVisibility(bool visible); // 0x00ea0010
};
}
namespace SP {
class cSPPaletteUI_s00d1_30d0 {
public:
    int FindCategoryIndex(); // 0x005ca9c0
};
}
namespace SP {
class cSPPaletteItem_s00d1_30d0 {
public:
    uint32_t pad[3];
    uint32_t mInstanceID; // +0x0c
    uint32_t pad10;
    uint32_t mGroupID;    // +0x14
    uint32_t pad18[3];
    uint32_t mItemType;   // +0x24
};
}
namespace SP {
class cCommunity_s00d1_30d0 {};
}
namespace SP {
cTribe_s00d1_30d0* GetTribe(cCommunity_s00d1_30d0* const& pCommunity);  // 0x00d08ee0 (Cast 0x4f396a66)
}
namespace SP {
cCity_s00d1_30d0* GetCity(cCommunity_s00d1_30d0* const& pCommunity);    // 0x00d08ec0 (Cast 0xee9b2232)
}
namespace SP {
uint32_t GetModelType(cSPPaletteItem_s00d1_30d0* pItem);     // 0x00d0a6e0
}
namespace SP {
uint32_t GetEditorConfigFromModelType(uint32_t modelType); // 0x00432f10
}
namespace SP {
cGameNounManager_s00d1_30d0* NounManager_s00d1_30d0();                  // 0x00b3d300
}
namespace SP {
cEditorManager* EditorManager();                  // 0x00b3d320
}
namespace SP {
IApp_s00d1_30d0* App();                                      // 0x0067dd10
}
namespace SP {
IConfigManager* ConfigManager();                  // 0x0067dd30
}
namespace SP {
IMessageServer_s00d1_30d0* MessageServer_s00d1_30d0();                  // 0x0067dcc0
}
namespace SP {
IResourceManager* ResourceManager();              // 0x0067dcd0
}
namespace SP {
IPropertyManager* PropertyManager_s00d1_30d0();              // 0x0067de30
}
namespace SP {
cGameTimeManager_s00d1_30d0* GameTimeManager_s00d1_30d0();              // 0x00b3d380
}
namespace SP {
IGameInputManager* GameInputManager();            // 0x00b3d250
}
namespace SP {
IBehaviorManager* BehaviorManager();              // 0x00b3d260
}
namespace SP {
ICameraManager_s00d1_30d0* CameraManager_s00d1_30d0();                  // 0x00b3d240
}
namespace SP {
cPlanetModel_s00d1_30d0* PlanetModel_s00d1_30d0();                      // 0x00b3d350
}
namespace SP {
cEmpire_s00d1_30d0* GetPlayerEmpire_s00d1_30d0();                       // 0x01021300
}
namespace SP {
cPlanet_s00d1_30d0* GetActivePlanet();                       // 0x01021260
}
namespace SP {
cSimulatorSpaceGame* SpaceGame();                 // 0x01002bd0
}
namespace SP {
cCivModeStrategy* CivModeStrategy();              // 0x00cf74c0
}
namespace SP {
cUIHintManager* UIHintManager();                  // 0x0067caf0
}
namespace SP {
cUIHints_s00d1_30d0* UIHints();                              // 0x0067cac0
}
namespace SP {
cAudioState* GetAudioState_s00d1_30d0();                     // 0x00435e90
}
namespace SP {
void PlayAudio(uint32_t soundID, cAudioState* pState); // 0x00435ed0
}
namespace SP {
cVehicle_s00d1_30d0* AsVehicle(cSpatialObject_s00d1_30d0* pObject);     // 0x00b33e60
}
namespace SP {
void SetBeingPlaced(void* pObject, bool value);   // 0x00ba57a0
}
namespace SP {
float GetHomeTerrainScore(void* pSurface);        // 0x00bce400
}
namespace SP {
float GetTerrainScore(void* pSurface);            // 0x00bcde40
}
namespace SP {
void PlayVehicleAudio(uint32_t eventID, void* pAudio, void* pPosition, const Vector3_s00d1_30d0& offset,
                      uint32_t politicalID, int arg6, int arg7); // 0x00e3c7c0
}
namespace SP {
bool GetPropertyAsUint32(cPropertyList_s00d1_30d0* pList, uint32_t id, uint32_t& value);   // 0x004af210
}
namespace SP {
bool GetPropertyAsKeyInstance(cPropertyList_s00d1_30d0* pList, uint32_t id, uint32_t& value); // 0x006a12a0
}
namespace SP {
cSPPaletteItem_s00d1_30d0* interface_cast_PaletteItem(EA::AutoRefCount_s00d1_30d0<RefObject>* p);    // 0x005767b0
}
namespace SP {
cEditorResource_s00d1_30d0* interface_cast_EditorResource(EA::AutoRefCount_s00d1_30d0<IResource>* p); // 0x00421eb0
}
namespace SP {
extern const ResourceKey_s00d1_30d0 kVehicleHintKey;   // 0x01582544
}
namespace SP {
extern const ResourceKey_s00d1_30d0 kBuildingHintKey;  // 0x01582574
}
namespace SP {
extern const void* const kHintLayout;       // 0x015825c8
}
namespace SP {
extern const uint32_t kDefaultValidationLevel[4]; // 0x015da7c4
}
namespace SP {
extern const float kToolScale;              // 0x014853e0 (4.0)
}
namespace SP {
struct tPaletteSelectMessage {
    uint32_t pad[5];
    uint32_t mModelType;   // +0x14
    ResourceKey_s00d1_30d0 mKey;      // +0x18
    uint32_t pad24[8];
    uint32_t mPaletteInstance; // +0x44
};
}
namespace SP {
struct tEditModelMessage {
    uint32_t pad[3];
    uint32_t mConfig;      // +0x0c
    ResourceKey_s00d1_30d0 mKey;      // +0x10
    uint32_t mToolType;    // +0x1c
};
}
namespace SP {
struct tShopMessage {
    uint32_t mModelType;   // +0x00
    uint32_t pad04;
    int mMode;             // +0x08
};
}
namespace SP {
struct tPaletteItemMessage {
    uint32_t pad[8];
    EA::AutoRefCount_s00d1_30d0<RefObject> mItem; // +0x20
};
}
namespace SP {
class cCommunityEditor_s00d1_30d0 {
public:
    virtual void v00();
    virtual void v04();
    virtual int Release(); // +0x08
    uint32_t pad04[(0x40 - 4) / 4];
    cCommunity_s00d1_30d0* mpCommunity;                 // +0x40
    uint32_t pad44[2];
    uint32_t mRecentlyEditedModelType;       // +0x4c
    ResourceKey_s00d1_30d0 mRecentlyEditedModelKey;     // +0x50 (instance, type, group)
    uint8_t mPaletteInstance;                // +0x5c
    uint8_t pad5d[3];
    uint32_t mShoppingModelType;             // +0x60
    uint32_t pad64;
    IWindow_s00d1_30d0* mpWinBudget;                    // +0x68
    uint32_t pad6c[4];
    cSellBackRollover_s00d1_30d0* mpSellbackRollover;   // +0x7c
    uint32_t pad80[11];
    cRotationRing_s00d1_30d0* mpRotationRing;           // +0xac
    uint32_t padb0;
    cSPPaletteUI_s00d1_30d0* mpPaletteUI;               // +0xb4
    uint32_t padb8;
    uint32_t mRotationAnchorNoun;            // +0xbc
    cSpatialObject_s00d1_30d0* mpManipulatedObject;     // +0xc0
    uint32_t mRotationAnchorFlags;           // +0xc4
    uint32_t mAnchorState;                   // +0xc8
    uint32_t padcc[7];
    Vector3_s00d1_30d0 mCursorScreenPos;                // +0xe8
    uint32_t padf4;
    int mSnapIndices[4];                     // +0xf8
    uint32_t pad108[(0x1f0 - 0x108) / 4];
    eastl::vector_s00d1_30d0<EA::AutoRefCount_s00d1_30d0<cVehicle_s00d1_30d0> > mPlacedVehicles; // +0x1f0
    uint32_t pad200[2];
    bool mbIsShutDown;                       // +0x208

    bool HandleMessage(uint32_t messageID, void* pMessage);  // 0x00d130d0 (SP::cCommunityEditor::HandleMessage)
    bool HandlePaletteMessage(uint32_t messageID, void* pMessage);          // 0x00d12910
    const ResourceKey_s00d1_30d0* GetKeyForModelType(uint32_t modelType);              // 0x00d09600
    void SetupShoppingUI(uint32_t modelType, ResourceKey_s00d1_30d0 key, int arg);     // 0x00d08b50
    void HandleSwatchRolloverOff(cSwatch* pSwatch);                  // 0x00d0def0
    void HandleSwatchRolloverOn(cSwatch* pSwatch);                     // 0x00d0e0c0
    void UpdateSwatchForModelType(uint32_t modelType, const ResourceKey_s00d1_30d0& key, int arg); // 0x00d0c820
    void UpdateLimitMeter(int category);                                    // 0x00d0a1e0
    const Vector3_s00d1_30d0* GetCommunityCenter(int arg);                             // 0x00d09960
    void SetCameraTarget(Vector3_s00d1_30d0 position);                                 // 0x00d08aa0
    cVehicle_s00d1_30d0* CreateVehicle(uint32_t modelType);                            // 0x00d091c0
    void SetManipulatedObject(cSpatialObject_s00d1_30d0* pObject);                     // 0x00d09f60
    void SetObjectSpecificData();                                           // 0x00d09ad0
    void UpdateVehicleList();                                               // 0x00d0c010
    int GetObjectCost(cSpatialObject_s00d1_30d0* pObject, int arg, int modelType);     // 0x00d0abd0
    void PlaceVehicle(cVehicle_s00d1_30d0* pVehicle);                                  // 0x00d0d570
    void UpdateSnapping();                                                  // 0x00d0db30
    void UpdatePlacementEffects();                                          // 0x00d0a540

    __forceinline void ClearRotationAnchor()
    {
        uint32_t noun = mRotationAnchorNoun;
        mRotationAnchorFlags = 0;
        if (noun) {
            NounManager_s00d1_30d0()->RemoveNoun(noun);
            mRotationAnchorNoun = 0;
        }
    }
};
}
namespace SP {
static __forceinline void ShowFirstTimeHint(const ResourceKey_s00d1_30d0& key)
{
    GameTimeManager_s00d1_30d0()->IncPauseGate(0x4bf38a7);
    UIHintManager()->ShowHint(key, &kHintLayout, 0, Vector3_s00d1_30d0(-1.0f, -1.0f, 0.0f), 0, 0);
    UIHints()->SetEnabled(0, 1);
}
}
namespace SP {
static bool sVehicleHintShown;  // 0x0169d587
}
namespace SP {
static bool sBuildingHintShown; // 0x0169d584
}
namespace SP {
static bool sDecorHintShown;    // 0x0169d588
}
// ---- items of slice s00d130d0 end

// @ 0x00421eb0
void* __cdecl QueryA(Unknown** ref)
{
    void* result;
    Unknown* p = *ref;
    Unknown* pTmp;
    Unknown* pCast;
    if (p) {
        pCast = pTmp;
        pCast = *ref;
        result = pCast->Query(0x3c609f8);
    } else {
        result = 0;
    }
    return result;
}

// @ 0x00afab70
int SP::cActionCircle_s00af_ab70::StartSnapAttractorEffects(const cSPVector3_s00af_ab70* p)
{
  int n = (int)(mSlots.mpEnd - mSlots.mpBegin);
  float best = g_fFLTMax;
  int i = 0;
  int found = -1;
  if (3 < n) {
    float px = p->mX;
    float py = p->mY;
    float pz = p->mZ;
    tSlot* s = mSlots.mpBegin;
    do {
      {
        float dx = px - s[0].mPos.mX, dy = py - s[0].mPos.mY, dz = pz - s[0].mPos.mZ;
        float dist = (dx * dx + dy * dy) + dz * dz;
        if (dist < best) { found = i; best = dist; }
      }
      {
        float dx = px - s[1].mPos.mX, dy = py - s[1].mPos.mY, dz = pz - s[1].mPos.mZ;
        float dist = (dx * dx + dy * dy) + dz * dz;
        if (dist < best) { found = i + 1; best = dist; }
      }
      {
        float dx = px - s[2].mPos.mX, dy = py - s[2].mPos.mY, dz = pz - s[2].mPos.mZ;
        float dist = (dx * dx + dy * dy) + dz * dz;
        if (dist < best) { found = i + 2; best = dist; }
      }
      {
        float dx = px - s[3].mPos.mX, dy = py - s[3].mPos.mY, dz = pz - s[3].mPos.mZ;
        float dist = (dx * dx + dy * dy) + dz * dz;
        if (dist < best) { found = i + 3; best = dist; }
      }
      i += 4;
      s += 4;
    } while (i < n - 3);
  }
  for (; i < n; i++) {
    tSlot* s = mSlots.mpBegin + i;
    float dx = p->mX - s->mPos.mX, dy = p->mY - s->mPos.mY, dz = p->mZ - s->mPos.mZ;
    float dist = (dx * dx + dy * dy) + dz * dz;
    if (dist < best) { found = i; best = dist; }
  }
  return found;
}

// @ 0x00bf4b10
void cCommunityEditor::CreateVehicleFromModelType(cCity* pCity, const Vec3* pPosition)
{
    SetModelTypeKey((int*)pCity, pPosition);

    uint32_t nModel = (uint32_t)(intptr_t)pCity;
    int nKind = 0;
    int nLevel = 0;

    switch (nModel) {
    case 0x1f2a25b6:
        nKind = 1;
        nLevel = 1;
        break;
    case 0x2090a11b:
    case 0x1a4e0708:
        nKind = 2;
        nLevel = 2;
        break;
    case 0x2a5147a9:
        nKind = 2;
        nLevel = 1;
        break;
    case 0x441cd3e6:
        nKind = 0;
        nLevel = 1;
        break;
    case 0x449c040f:
        nKind = 1;
        nLevel = 2;
        break;
    case 0x47c10953:
    case 0x4e3f7777:
    case 0x72c49181:
        RefreshCityStatistics(this);
        nKind = 0;
        nLevel = 0;
        break;
    case 0x7d433fad:
        nKind = 0;
        nLevel = 0;
        break;
    case 0x9ad7d4aa:
        nKind = 1;
        nLevel = 0;
        break;
    case 0xf670aa43:
    case 0xbe105f3e:
    case 0xc0b74287:
        nKind = 2;
        nLevel = 0;
        break;
    default:
        return;
    }

    int nCount = (int)(mpCitiesEnd - mpCitiesBegin);
    for (int i = 0; i < nCount; ++i) {
        cCity* pEntry = mpCitiesBegin[i];
        if (pEntry->mCityKind == nLevel &&
            (GetCurrentGameMode() == &gGameModeSpace || pEntry->mCityLevel == nKind)) {
            ((IRefCounted_s00bf_4170*)pEntry->GetIcon())->Query(pPosition);
        }
    }
}

// @ 0x00d08930
void FUN_00d08930()
{
    void* mgr = SP_GameInputManager();
    if (mgr == 0)
        return;
    ((Fn3S)(*(void***)mgr)[0x40 / 4])(mgr, 0x3e80, (const char*)0x14792a4);
    ((Fn3S)(*(void***)mgr)[0x40 / 4])(mgr, 0x3e82, (const char*)0x1479288);
    ((Fn3S)(*(void***)mgr)[0x40 / 4])(mgr, 0x3e81, (const char*)0x147926c);
    ((Fn3S)(*(void***)mgr)[0x40 / 4])(mgr, 0x3e83, (const char*)0x1479250);
    ((Fn3S)(*(void***)mgr)[0x40 / 4])(mgr, 0x3e84, (const char*)0x1479234);
    ((Fn3S)(*(void***)mgr)[0x40 / 4])(mgr, 0x3e85, (const char*)0x1479218);
    ((Fn3S)(*(void***)mgr)[0x40 / 4])(mgr, 0x3e86, (const char*)0x1479200);
}

// @ 0x00d08a70
u32 Obj8A70::Do(u32 a, u32 b)
{
    if (mp2B8 != 0) {
        FUN_00572020(mp2B8, 0);
        mp2B8 = 0;
    }
    return 0;
}

// @ 0x00d08aa0
void __stdcall FUN_00d08aa0(u32 a1, u32 a2, u32 a3, u32 a4)
{
    if (GetCameraCtl() != 0)
        ((CameraCtl*)GetCameraCtl())->Do(&a1, a4);
}

// @ 0x00d08ad0
void FUN_00d08ad0(void* obj)
{
    if (obj == 0)
        return;
    if (!FUN_00b673c0(obj))
        return;
    u32 mode = SP_GetCurrentGameMode();
    if (mode == 0x1654c02)
        return;
    if ((u32)(mode + 0xfe9ab3fc) <= 1) {
        if (FUN_00b188b0(obj))
            return;
        if (FUN_00b18740(obj) && !FUN_00b18760(obj))
            return;
        if (FUN_00b187b0(obj))
            return;
        if (FUN_00b18790(obj))
            return;
        if (FUN_00b187f0(obj))
            return;
    }
    FUN_00b69990(obj);
}

// @ 0x00d08b50
void Editor8B50::Setup(u32 modelType, u32 p3, u32 p4, u32 p5, u8 p6)
{
    mn48 = modelType;

    u32 h;
    switch ((s32)modelType) {
    case 0x2090a11b: h = 0x5b38a3b2; break;
    case 0xc15695da: h = 0xaafaf799; break;
    case 0x99e92f05: h = 0x695cbb72; break;
    case 0x8f963dcb: h = 0xbdf55802; break;
    case 0x98e03c0d: h = 0x9c5c0628; break;
    case 0x9ad7d4aa: h = 0xa32e702d; break;
    case 0xbc1041e6: h = 0xa1986101; break;
    case 0x1a4e0708: h = 0xa64eb2c3; break;
    case 0xccc35c46: h = 0x58d29fb5; break;
    case 0xf670aa43: h = 0x7d042d12; break;
    case 0x1f2a25b6: h = 0x46934e5d; break;
    case 0x47c10953: h = 0x47f2ebb2; break;
    case 0x441cd3e6: h = 0x11e8c369; break;
    case 0x2a5147a9: h = 0x8a551fdc; break;
    case 0x372e2c04: h = 0x261aee8b; break;
    case 0x449c040f: h = 0xbbe19f1e; break;
    case 0x72c49181: h = 0xed90d2e6; break;
    case 0x4e3f7777: h = 0x8049b6dc; break;
    case 0x65672ade: h = 0x40e24ee9; break;
    case 0x7d433fad: h = 0xb7c9952c; break;
    default: return;
    }

    Launch8B50 launch;
    ((LaunchInit*)&launch)->Init();
    launch.mb14 = 1;
    launch.mn38 = (u32)((char*)this + 4);
    launch.mn30 = 0xad0e52;
    launch.mn04 = SP_GetCurrentGameMode();
    launch.mn18 = p3;
    launch.mn1C = p4;
    launch.mn00 = h;
    launch.mn20 = p5;
    launch.mb24 = p6;
    launch.mb10 = 1;
    sub_64a990(&launch);
    ((LaunchInit*)&launch)->Destroy();
}

// @ 0x00d08d80
char __stdcall FUN_00d08d80(Req8D80* req)
{
    void* ctl;
    void* app = SP_App();
    if (app != 0)
        ctl = ((FnP0)(*(void***)app)[0x2c / 4])(app);
    else
        ctl = 0;

    switch (req->mn08 - 1) {
    case 0:
    case 1:
    case 4:
        break;
    default:
        return 0;
    case 5:
        if (req->mn18 == 1000) {
            char r;
            if (ctl == 0)
                return 0;
            r = ((char (__thiscall*)(void*, u32, f32, f32, u32))
                 (*(void***)ctl)[0x2c / 4])(ctl, 1000, req->mf0C, req->mf10, req->mn14);
            if (!r)
                return 0;
            goto ret1;
        }
        break;
    case 6:
        if (req->mn18 == 1000) {
            if (ctl == 0)
                return 0;
            if (!((char (__thiscall*)(void*, u32, f32, f32, u32))
                  (*(void***)ctl)[0x30 / 4])(ctl, 1000, req->mf0C, req->mf10, req->mn14))
                return 0;
            goto ret1;
        }
        break;
    case 7:
        if (ctl == 0)
            return 0;
        if (((char (__thiscall*)(void*, f32, f32, u32))
             (*(void***)ctl)[0x34 / 4])(ctl, req->mf0C, req->mf10, req->mn14))
            goto ret1;
        return 0;
    case 8:
        if (ctl == 0)
            return 0;
        if (!((char (__thiscall*)(void*, u32, f32, f32, u32))
              (*(void***)ctl)[0x38 / 4])(ctl, req->mn18, req->mf0C, req->mf10, req->mn14))
            return 0;
        goto ret1;
    }
ret1:
    return 1;
}

// @ 0x00d08fa0
int Editor8FA0::GetVehicleCost(u32 type)
{
    void* c = 0;
    if (mp40 != 0)
        c = ((FnP1)(*(void***)mp40)[0xc / 4])(mp40, 0xee9b2232);
    CityObj* city = (CityObj*)c;

    switch (type) {
    case 0x7d433fad:
        return (int)city->GetCivilization()->GetCost(0, 0);
    case 0x2a5147a9:
        return (int)city->GetCivilization()->GetCost(2, 1);
    case 0x1a4e0708:
        return (int)city->GetCivilization()->GetCost(2, 2);
    case 0x1f2a25b6:
        return (int)city->GetCivilization()->GetCost(1, 1);
    case 0x2090a11b:
        return (int)city->GetCivilization()->GetCost(2, 2);
    case 0x441cd3e6:
        return (int)city->GetCivilization()->GetCost(0, 2);
    case 0x449c040f:
        return (int)city->GetCivilization()->GetCost(1, 2);
    case 0x8f963dcb:
        return (int)city->GetCivilization()->GetCost(0, 1);
    case 0x9ad7d4aa:
        return (int)city->GetCivilization()->GetCost(1, 0);
    case 0xbc1041e6:
        return (int)city->GetCivilization()->GetCost(2, 0);
    case 0xc0b74287:
        return (int)city->GetCivilization()->GetCost(2, 0);
    case 0xc15695da:
        return (int)city->GetCivilization()->GetCost(2, 1);
    case 0xf670aa43:
        return (int)city->GetCivilization()->GetCost(2, 0);
    }
    return 0x19;
}

// @ 0x00d091c0
void cCommunityEditor_s00d0_91c0::FUN_00d091c0(uint32_t modelType)
{
    if (!mpCommunity) return;
    cCity_s00d0_91c0* city = AsCity(mpCommunity);
    if (!city) return;

    bool inSpace = (SP_GetCurrentGameMode() == kGameModeSpace);

    if (SP_GetCurrentGameMode() == kGameModeCiv &&
        (modelType == 0x441cd3e6 || modelType == 0x449c040f || modelType == 0x1a4e0708)) {
        cTerrainSphere* ts = NounManager()->GetCurrentTerrainSphere();
        FUN_00c77bf0(ts);
    }

    int a = -1, b = -1;
    switch (modelType) {
    case 0x1a4e0708: a = 2; b = 1; break;
    case 0xbc1041e6: a = 2; b = 2; break;
    case 0x9ad7d4aa: a = 1; b = 0; break;
    case 0x8f963dcb: a = 0; b = 1; break;
    case 0xc0b74287: a = 2; b = 2; break;
    case 0xf670aa43: a = 2; b = 2; break;
    case 0xc15695da: a = 2; b = 1; break;
    case 0x2a5147a9: a = 1; b = 1; break;
    case 0x2090a11b: a = 2; b = 2; break;
    case 0x1f2a25b6: a = 1; b = 1; break;
    case 0x441cd3e6: a = 0; b = 2; break;
    case 0x449c040f: a = 1; b = 2; break;
    case 0x7d433fad: a = 0; b = 0; break;
    default: return;
    }
    cCivilization* civ = city->GetCivilization();
    const ResourceKey* key = civ->GetModelTypeKey(modelType);
    city->FUN_00bddda0(a, b, key->instanceID, key->typeID, key->groupID, inSpace ? 1 : 0);
}

// @ 0x00d09560
void cCommunityEditor_s00d0_91c0::SetKeyForModelType(uint32_t modelType, const ResourceKey* key)
{
    if (modelType == 0x98e03c0d) {
        GetPlayerEmpire_01021300()->SetUFOKey(key);
        cSPSimulatorSpaceGame* sim = GetUFOSimulator_00ffbe50();
        cSPGameDataUFO* inv = sim->GetPlayerInventory();
        if (inv) { inv->SetDesiredModel(key, 1); return; }
        return;
    }
    cCommunity* comm = mpCommunity;
    cCity_s00d0_91c0* city = comm ? (cCity_s00d0_91c0*)comm->Cast(TYPE_cCity) : 0;
    city->GetCivilization()->CreateVehicleFromModelType(modelType, key);
    if (modelType == 0x99e92f05) {
        cTerrainSphere* ts = NounManager()->GetCurrentTerrainSphere();
        *(uint32_t*)((char*)ts + 0x1150) = key->instanceID;
        *(uint32_t*)((char*)ts + 0x1154) = key->typeID;
        *(uint32_t*)((char*)ts + 0x1158) = key->groupID;
    }
}

// @ 0x00d09600
const ResourceKey* cCommunityEditor_s00d0_91c0::GetKeyForModelType(uint32_t modelType)
{
    if (modelType == 0x98e03c0d) {
        cEmpire* empire = GetPlayerEmpire_01021300();
        return empire->GetUFOKey();
    }
    cCommunity* comm = mpCommunity;
    cCity_s00d0_91c0* city = comm ? (cCity_s00d0_91c0*)comm->Cast(TYPE_cCity) : 0;
    return city->GetCivilization()->GetModelTypeKey(modelType);
}

// @ 0x00d09670
int cCommunityEditor_s00d0_91c0::FUN_00d09670()
{
    if (mpPaletteUI) return mpPaletteUI->GetCurrentCategoryIndex();
    return -1;
}

// @ 0x00d096b0
bool cCommunityEditor_s00d0_91c0::FUN_00d096b0(void* obj)
{
    void** end = mPreExistingBuildings.mpEnd;
    void** it  = mPreExistingBuildings.mpBegin;
    if (it != end) {
        do { if (*it == obj) break; ++it; } while (it != end);
    }
    return (it == end) ? false : true;
}

// @ 0x00d096e0
bool cCommunityEditor_s00d0_91c0::FUN_00d096e0(void* obj)
{
    void** end = mPreExistingNouns.mpEnd;
    void** it  = mPreExistingNouns.mpBegin;
    if (it != end) {
        do { if (*it == obj) break; ++it; } while (it != end);
    }
    return (it == end) ? false : true;
}

// @ 0x00d09710
bool cCommunityEditor_s00d0_91c0::FUN_00d09710(void* obj)
{
    void** end = mPreExistingTurrets.mpEnd;
    void** it  = mPreExistingTurrets.mpBegin;
    if (it != end) {
        do { if (*it == obj) break; ++it; } while (it != end);
    }
    return (it == end) ? false : true;
}

// @ 0x00d09740
bool cCommunityEditor_s00d0_91c0::FUN_00d09740(void* obj)
{
    void** end = mPreExistingTools.mpEnd;
    void** it  = mPreExistingTools.mpBegin;
    if (it != end) {
        do { if (*it == obj) break; ++it; } while (it != end);
    }
    return (it == end) ? false : true;
}

// @ 0x00d09770
void* cCommunityEditor_s00d0_91c0::FUN_00d09770(int, int)
{
    if (mpSelectedObject) {
        cCamHost* host = (cCamHost*)NounHost_00b3d240();
        const Vector3* objPos = mpSelectedObject->GetPosition();
        Vector3 camBuf = g_Vector3Zero;
        const Vector3* camPos = host->GetCamPos(&camBuf, 0);
        float dx = camPos->x - objPos->x;
        float dy = camPos->y - objPos->y;
        float dz = camPos->z - objPos->z;
        float inv = 1.0f / (float)sqrt(dx*dx + dy*dy + dz*dz);
        mAnchorDir_cc.x = inv * dx;
        mAnchorDir_cc.y = inv * dy;
        mAnchorDir_cc.z = inv * dz;
        const Quaternion* q = mpSelectedObject->GetOrientation();
        mAnchorQuat.x = q->x;
        mAnchorQuat.y = q->y;
        mAnchorQuat.z = q->z;
        mAnchorQuat.w = q->w;
    }
    return 0;
}

// @ 0x00d098b0
uint32_t cCommunityEditor_s00d0_91c0::GetCameraZoomProgramID()
{
    const uint32_t kDefault = 0x225d13ad;
    if (!mpCommunity) return kDefault;

    cCommunity* a = mpCommunity ? (cCommunity*)mpCommunity->Cast(TYPE_cCity) : 0;
    cCommunity* b = mpCommunity ? (cCommunity*)mpCommunity->Cast(TYPE_cTribe) : 0;

    if (a == 0) {
        if (b != 0) return 0x5b2dd8b4;
    } else {
        if (a->GetMode() != 0) {
            cCommunity* m2 = (cCommunity*)a->GetMode();
            if (m2->GetMode() != 0) {
                cCommunity* m3 = (cCommunity*)a->GetMode();
                if (m3->GetMode() != (void*)2)
                    return 0x0c24c2b5;
            }
        }
    }
    return kDefault;
}

// @ 0x00d09960
const Vector3* cCommunityEditor_s00d0_91c0::GetCommunityCenter()
{
    if (!mpCommunity) return &g_Vector3Zero;
    if (SP_GetCurrentGameMode() == kGameModeSpace && mpCommunity) {
        cCommunity* comm = mpCommunity;
        cCity_s00d0_91c0* city = comm ? (cCity_s00d0_91c0*)comm->Cast(TYPE_cCity) : 0;
        if (city) {
            if (city->GetCityHall()) {
                cSpatialObject* sp = (cSpatialObject*)((char*)city->GetCityHall() + 0x34);
                return sp->GetPosition();
            }
        }
    }
    return mpCommunity->GetPosition();
}

// @ 0x00d099c0
void cCommunityEditor_s00d0_91c0::CameraTrackMouse(cSpatialObject* obj)
{
    cCamHost* host = (cCamHost*)NounHost_00b3d240();
    Vector3 buf;
    host->GetCamPos3C(&buf, 1);
    if (obj) {
        cSpatialObject* r = (cSpatialObject*)obj->Cast0C(0x01186577);
        if (r) {
            const Vector3* p = r->GetPosition();
            buf.x = p->x; buf.y = p->y; buf.z = p->z;
        }
    }
    const Vector3* center = GetCommunityCenter();
    float len = (float)sqrt(center->x*center->x + center->y*center->y + center->z*center->z);
    float inv = 1.0f / (float)sqrt(buf.x*buf.x + buf.y*buf.y + buf.z*buf.z);
    Vector3 dir;
    dir.x = (inv * buf.x) * len;
    dir.y = (inv * buf.y) * len;
    dir.z = (inv * buf.z) * len;
    if (CameraCtl_00b3d280()) {
        CameraCtl_SetDir_00b13bb0(CameraCtl_00b3d280(), &dir, 0);
    }
}

// @ 0x00d09ad0
void cCommunityEditor_s00d0_91c0::SetObjectSpecificData()
{
    if (!mpManipulatedObject) return;
    cCommunity* a = (cCommunity*)CastTo(mpCommunity, TYPE_cCity);
    cCommunity* b = (cCommunity*)CastTo(mpCommunity, TYPE_cTribe);
    cSpatialObject* obj = mpManipulatedObject;
    void* f1 = obj->Cast(0x0436f315);
    void* f2 = obj->Cast(0x0e9cb8ba);
    void* f3 = obj->Cast(0x0116d858);
    void* f4 = obj->Cast(0x0175cdc9);

    if (f1 && a) {
        mSpecificA_27c = 0xf089377b; mSpecificB_280 = 0x1641ae13;
        mSpecificC_284 = 0xde3f8c28; mSpecificD_288 = 0x414c841f;
        mSpecificE_28c = 0x97b71138; mSpecificF_290 = 0x869764ee;
        mSpecificG_294 = 0xefca2d60;
        mLastSwapPointIndex = FUN_00bd7f60();
        return;
    }
    if (f2 && a) {
        mSpecificA_27c = 0x9fdf8751; mSpecificB_280 = 0x7fa0a9e9;
        mSpecificC_284 = 0xa94b3e0e; mSpecificD_288 = 0x7f232c6d;
        mSpecificE_28c = 0xd393ef5e; mSpecificF_290 = 0xdffee948;
        mSpecificG_294 = 0x215d6086;
        mLastSwapPointIndex = FUN_00bd7f40();
        return;
    }
    if (f3 && b) {
        mSpecificA_27c = 0xeeef054f; mSpecificB_280 = 0xbc866537;
        mSpecificC_284 = 0x9e017694; mSpecificD_288 = 0x98ff936a;
        mSpecificE_28c = 0x5546e1e4; mSpecificF_290 = 0xbb2a2e9a;
        mSpecificG_294 = 0xd9c01f7c;
        mLastSwapPointIndex = (int)b + 0x3b4;
        return;
    }
    if (f4 && a) {
        mSpecificA_27c = 0xf081d484; mSpecificB_280 = 0x769de34c;
        mSpecificC_284 = 0x63614239; mSpecificD_288 = 0x0ff4d3c0;
        mSpecificE_28c = 0x86c46889; mSpecificF_290 = 0xfd7cf077;
        mSpecificG_294 = 0x0d05b881;
        mLastSwapPointIndex = FUN_00bd7f50();
    }
}

// @ 0x00d09d30
void cCommunityEditor_s00d0_91c0::RemoveObjectFromCommunity(cSpatialObject* obj)
{
    if (!mpCommunity) return;
    cCity_s00d0_91c0* city = AsCity(mpCommunity);
    cCommunity* comm = (cCommunity*)CastTo(mpCommunity, TYPE_cTribe);
    if (!obj) return;

    void* f1 = obj->Cast(0x0436f315);
    void* f2 = obj->Cast(0x0e9cb8ba);
    void* f3 = obj->Cast(0x0116d858);
    void* f4 = obj->Cast(0x0175cdc9);

    if (f1 && city) { FUN_00be2070(f1, 0); return; }
    if (f2 && city) {
        FUN_00be33e0(f2);
        if (SP_GetCurrentGameMode() == kGameModeSpace) {
            cSPLivingUniverse* lu = GetActivePlanetOwner_01021260();
            if (!lu->FUN_00c70b50()) {
                cGameNounManager* sg = (cGameNounManager*)SpaceGameGet_01002bd0(0, -1);
                void* tribe = sg->GetPlayerTribe();
                FUN_00fe5430(tribe, -1);
                return;
            }
        }
        return;
    }
    if (f3 && comm) {
        FUN_00c8f470(comm, f3, 0, 0x800000, *(float*)0x14791d8, 0);
        return;
    }
    if (f4 && comm) { FUN_00be34a0(f4, 0); }
}

// @ 0x00d09f00
Vector3* cCommunityEditor_s00d0_91c0::SnapPointToPlanetIfNecessary(Vector3* out, float x, float y, float z, cSpatialObject* obj)
{
    if (obj && obj->Cast(0x0436f315)) {
        out->x = x; out->y = y; out->z = z;
        return out;
    }
    PlanetModel_00b3d350(out, (Vector3*)&x)->DirectionToSurface(out, (Vector3*)&x);
    return out;
}

// @ 0x00d09f60
void cCommunityEditor_s00d0_91c0::SetManipulatedObject(cSpatialObject* obj)
{
    if (mpManipulatedObject_278 && mpManipulatedObject != obj) {
        mpManipulatedObject_278->Cast0C(1);
        if (mpManipulatedObject_278) {
            cSpatialObject* p = mpManipulatedObject_278;
            mpManipulatedObject_278 = 0;
            p->Release();
        }
    }
    if (mpManipulatedObject) mpManipulatedObject->mFlag72 = 0;
    mpManipulatedObject = obj;
    if (obj) obj->mFlag72 = 1;

    mSnapPoint = g_Vector3Zero;
    cCommunity* comm = mpCommunity;

    if (comm) {
        cCity_s00d0_91c0* city = (cCity_s00d0_91c0*)comm->Cast(TYPE_cCity);
        if (city) {
            cSpatialObject* cur  = mpManipulatedObject;
            cSpatialObject* prev = city->mpSpecific_298;
            if (cur != prev) {
                if (cur) cur->v67();
                city->mpSpecific_298 = cur;
                if (prev) prev->v68();
            }
        }
    }
}

// @ 0x00d0a040
void cCommunityEditor_s00d0_91c0::ComputeMouseOffset(cSpatialObject* obj)
{
    if (!obj) return;
    mSnapPoint.x = g_Vector3Zero.x;
    mSnapPoint.y = g_Vector3Zero.y;
    mSnapPoint.z = g_Vector3Zero.z;

    cApp* app = (cApp*)App_0067dd10();
    cDisplay* display = (cDisplay*)app->GetDisplay();
    Vector3 a = { 0, 0, 0 };
    Vector3 b = { 0, 0, 0 };
    display->GetMousePos(&a, &b);
    FUN_007c4900(&a, &b);
    float scale = *(float*)0x13ec5b4;
    Vector3 target;
    target.x = a.x + b.x * scale;
    target.y = a.y + b.y * scale;
    target.z = a.z + b.z * scale;
    if (RayHitsObject_00b35bf0(NounHost_00b3d240(), &target, obj)) {
        const Vector3* p = obj->GetPosition();
        mSnapPoint.x = p->x - target.x;
        mSnapPoint.y = p->y - target.y;
        mSnapPoint.z = p->z - target.z;
    }
}

// @ 0x00d0a160
u8 cCommunityEditor_s00d0_a160::CanShowPreview()
{
  if (mpPreviewObject_c0 == 0) {
    const u16* name = (const u16*)mpCommunity_40->mNameProvider_34.Slot0c(0);
    // (the retail build inlines a two-wchar-at-a-time compare here)
    const u16* a = name;
    const u16* b = kPreviewName;
    s32 cmp;
    for (;;) {
      u16 c = *a;
      if (c != *b) { cmp = (c < *b) ? -1 : 1; break; }
      if (c == 0) { cmp = 0; break; }
      c = a[1];
      if (c != b[1]) { cmp = (c < b[1]) ? -1 : 1; break; }
      a += 2; b += 2;
      if (c == 0) { cmp = 0; break; }
    }
    if (cmp != 0 || mpVerbIconTray_a4 == 0) {
      mFlag_208 = 1;
      return 1;
    }
    mpVerbIconTray_a4->Slot1c(1);
  }
  return 0;
}

// @ 0x00d0a1e0
void cCommunityEditor_s00d0_a160::UpdateLimitMeter(s32 mode)
{
  u32 want = 0;
  if (mpCommunity_40 != 0) {
    void* p = mpCommunity_40->Slot0c(0xee9b2232);
    if (p != 0) {
      if (GetCurrentGameMode() == (void*)0x1654c05) {
        want = (mode != 1) ? 3u : 4u;
      } else if (mode == 1 || mode == 0) {
        want = 2;
      } else {
        want = 1;
      }
    }
  }
  if (want == mLimitMode_80)
    return;
  IRollover* old = mpSellback_7c;
  if (old != 0) {
    old->Release();
    SporeFreeArray(old);
    mpSellback_7c = 0;
  }
  u32 arg = 0;
  if (mpCommunity_40 != 0)
    arg = (u32)(SIZE_T)mpCommunity_40->Slot0c(0xee9b2232);
  IWindow* win = (IWindow*)mEditorUI_88.FindWindowByID(0x499da93, 1);
  IRollover* made = 0;
  if (win != 0) {
    switch (want) {
    case 1:
      if (SporeAlloc(0xc, "Editor", 0, 0, 0, 0) != 0)
        made = (IRollover*)FUN_00d06eb0(arg);
      break;
    case 2:
      if (SporeAlloc(0xc, "Editor", 0, 0, 0, 0) != 0)
        made = (IRollover*)FUN_00d1deb0(arg);
      break;
    case 3:
      if (SporeAlloc(0xc, "Editor", 0, 0, 0, 0) != 0)
        made = (IRollover*)FUN_00d07420((u32)(SIZE_T)GetPlayerEmpire());
      break;
    case 4:
      if (SporeAlloc(0xc, "Editor", 0, 0, 0, 0) != 0)
        made = (IRollover*)FUN_00d07720((u32)(SIZE_T)GetPlayerEmpire());
      break;
    default:
      break;
    }
    mpSellback_7c = made;
  }
  IRollover* cur = mpSellback_7c;
  if (cur != 0) {
    cur->Show(win);
    cur->Slot08();
  }
  mLimitMode_80 = want;
}

// @ 0x00d0a390
void cCommunityEditor_s00d0_a160::RefreshTooltip()
{
  if ((uint32_t)SP_GetCurrentGameMode() != 0x1654c04 &&
      (uint32_t)SP_GetCurrentGameMode() != 0x1654c05)
    return;
  u32 pad_00;
  cString s;
  s.Ctor();
  s.Load(0xc0152a6d, 0x65f79f0, 0);
  ((BudgetObj*)mpBudget_6c)->SetText(s.GetText());
  s.Dtor();
  (void)pad_00;
}

// @ 0x00d0a3f0
s32 cCommunityEditor_s00d0_a160::GetSelectedCost(SelectableObj* p)
{
  s32* it = mpSelectedIds_1f0;
  s32* end = mpSelectedEnd_1f4;
  if (it != end) {
    for (; it != end; ++it)
      if (*it == (s32)(SIZE_T)p) break;
    if (it != end && mpCommunity_40 != 0) {
      void* city = mpCommunity_40->Slot0c(0xee9b2232);
      if (city != 0) {
        City_GetCivilization(city, 0, p->mKeyA_b1c, p->mKeyB_b20);
        return (s32)FUN_00bf2170(city, 0);
      }
    }
  }
  return (s32)FUN_00c9e7c0_();
}

// @ 0x00d0a470
void cCommunityEditor_s00d0_a160::ShowRolloverWindows(u32 idA, u32 idB)
{
  IWindow* wA = (IWindow*)mEditorUI_88.FindWindowByID(idA, 1);
  IWindow* wB = (IWindow*)mEditorUI_88.FindWindowByID(idB, 1);
  IWindow* wC = (wB != 0) ? (IWindow*)wB->Slot0c(0xf15f4bd) : 0;
  if (wA != 0 && wB != 0 && wC != 0) {
    wC->Slot14(1);
    wB->Slot38();
    Vec4* rA = wA->Slot38();
    Vec4* rB = (Vec4*)0;      // result of wB->Slot38(), kept local
    (void)rB;
    Vec4 v;
    v.x = rA->x;
    v.y = rA->y;
    v.z = rA->z;
    v.w = rA->w;
    wA->Slot6c(&v);
  }
}

// @ 0x00d0a540
void cCommunityEditor_s00d0_a160::ShowPlacementCursor()
{
  mpWindowCtrl_2f8->mWindow_04.Slot7c(1, 1);
  WindowCtrl* c = mpWindowCtrl_2f8;
  void* p = (c != 0) ? (void*)&c->mWindow_04 : 0;
  ((IWindowMgr*)WindowManagerObj())->Slot58(1, p);
  if (mpWindowCtrl_2f8 != 0) {
    ((IWindowMgr*)WindowManagerObj())->Slot58(0, &mpWindowCtrl_2f8->mWindow_04);
    return;
  }
  ((IWindowMgr*)WindowManagerObj())->Slot58(0, 0);
}

// @ 0x00d0a5b0
void cCommunityEditor_s00d0_a160::HidePlacementCursor()
{
  void* p = (mpWindowCtrl_2f8 != 0) ? (void*)&mpWindowCtrl_2f8->mWindow_04 : 0;
  ((IWindowMgr*)WindowManagerObj())->Slot5c(1, p);
  void* q = (mpWindowCtrl_2f8 != 0) ? (void*)&mpWindowCtrl_2f8->mWindow_04 : 0;
  ((IWindowMgr*)WindowManagerObj())->Slot5c(0, q);
  mpWindowCtrl_2f8->mWindow_04.Slot7c(1, 0);
}

// @ 0x00d0a630
void PosTree::InsertPos(PosNode** out, const s32* key)
{
  PosNode* node = this->mpRoot_0c;
  PosNode* best = (PosNode*)&this->mpSentinel_04;
  while (node != 0) {
    if (key[0] > node->mKey0_10 ||
        (key[0] == node->mKey0_10 && node->mKey1_14 < key[1])) {
      node = node->mpLeft_00;
    } else {
      best = node;
      node = node->mpRight_04;
    }
  }
  *out = best;
}

// @ 0x00d0a670
CopyValue* CopyValue::AssignFrom(const CopyValue* src)
{
  this->mpA_00 = src->mpA_00;
  if (this->mpA_00 != 0)
    this->mpA_00->AddRef();
  this->mpB_04 = src->mpB_04;
  if (this->mpB_04 != 0)
    this->mpB_04->AddRef();
  this->mF_08 = src->mF_08;
  this->mF_0c = src->mF_0c;
  this->mF_10 = src->mF_10;
  this->mF_14 = src->mF_14;
  this->mF_18 = src->mF_18;
  this->mF_1c = src->mF_1c;
  this->mU32_20 = src->mU32_20;
  this->mU32_24 = src->mU32_24;
  this->mB_28 = src->mB_28;
  return this;
}

// @ 0x00d0a6e0
u32 __cdecl GetModelType(ModelType* p)
{
  u32 result = 0xffffffff;
  if (p == 0)
    return result;
  IProperty* mgr = (IProperty*)PropertyManager();
  IProperty* inst = 0;
  if (inst != 0) {
    inst = 0;
    inst->Release();
  }
  if (mgr->Slot2c(p->mKeyA_0c, p->mKeyB_14, (void**)&inst) != 0)
    GetPropertyAsKeyInstance(p, 0x5338876f, (void**)&result);
  if (p != 0)
    ((IProperty*)p)->Release();
  return result;
}

// @ 0x00d0a760
void cCommunityEditor_s00d0_a160::Init(u32 const* pLayoutId, u32 propKey, IWindow* pBudget, u8 bFlag)
{
  DeclareMenuCommands();
  IRollover* roll = 0;
  if (SporeAlloc(0xa8, "Editor", 0, 0, 0, 0) != 0)
    roll = (IRollover*)SellbackDetachedRollover_ctor(SporeAlloc(0xa8, "Editor", 0, 0, 0, 0));
  IRollover* oldRoll = mpSellback_7c;
  if (roll != oldRoll) {
    if (roll != 0)
      roll->Show(0);
    mpSellback_7c = roll;
    if (oldRoll != 0)
      oldRoll->Release();
  }
  mpBudget_6c = pBudget;
  if (bFlag != 0) {
    IRollover* shopping = 0;
    if (SporeAlloc(0xc, "Editor", 0, 0, 0, 0) != 0)
      shopping = (IRollover*)FUN_00d07a40(this);
    IRollover* oldShop = (IRollover*)mpRollover_84;
    if (shopping != oldShop) {
      if (shopping != 0)
        shopping->Release();
      mpRollover_84 = shopping;
      if (oldShop != 0)
        oldShop->Slot08();
    }
  }
  UiLayout_Init(&mEditorUI_88, 0, *pLayoutId, 0x40464100, 1, 0x5b598fa);
  UiLayout_SetVisibility(&mEditorUI_88, 0, 0);
  IWindow* root = (IWindow*)mEditorUI_88.FindWindowByID(0xffffffff, 1);
  if (root != 0) {
    root->Slot104(this);
    void* cls = FUN_009512c0();
    IWindow* blocker = (IWindow*)Window_New(0x20c, 4, "UI/cUIBlockingWin", cls);
    if (blocker == 0)
      blocker = 0;
    IWindow* oldBlock = mpBlockerWindow_340;
    if (blocker != oldBlock) {
      if (blocker != 0)
        blocker->AddRef();
      mpBlockerWindow_340 = blocker;
      if (oldBlock != 0)
        oldBlock->Release();
    }
    mpBlockerWindow_340->Slot60();
    mpBlockerWindow_340->Slot7c(1, 0);
    mpBlockerWindow_340->Slot78(0x6493807);
    root->SlotD8(mpBlockerWindow_340);
  }
  mpVerbIconTray_a4 = (IWindow*)mEditorUI_88.FindWindowByID(0xd0527aad, 1);
  IProperty* pmgr = (IProperty*)PropertyManager();
  IProperty* cfg = 0;
  if (cfg != 0) {
    cfg = 0;
    cfg->Release();
  }
  pmgr->Slot2c(propKey, 0xa19b317d, (void**)&cfg);
  mpPreviewObject_c0 = (void*)mEditorUI_88.FindWindowByID(0xf006f308, 1);
  mpRingDefinition_c4 = MessageServer();
  if (mpRingDefinition_c4 != 0)
    ((IProperty*)mpRingDefinition_c4)->Slot24();
}

// @ 0x00d0aa70
void cCommunityEditor_s00d0_a160::RefreshBuildingCosts()
{
  if (SporeAlloc(0x20, "Editor", 0, 0, 0, 0) == 0)
    return;
  void* iter = (void*)FUN_005c7b80();
  if (iter == 0)
    return;
  ((IWindow*)iter)->Release();
  FUN_005c7bc0((u32)(SIZE_T)mpProjector_b0);
  for (u32 i = FUN_005c7e80(0, 0, 0, 0); i != 0; i = FUN_005c7e20(0, 0, 0, 0)) {
    u32 type = GetModelType((ModelType*)i);
    s32 cost = GetPlayerBuildingCostFromType();
    if (cost != -1) {
      IProperty* inst = 0;
      IProperty* pmgr = (IProperty*)PropertyManager();
      if (inst != 0) {
        inst = 0;
        inst->Release();
      }
      if (pmgr->Slot2c(((ModelType*)i)->mKeyA_0c, ((ModelType*)i)->mKeyB_14,
                       (void**)&inst) != 0 &&
          inst->Slot1c(0x2166464) != 0) {
        u32 var[3];
        var[0] = 0;
        var[1] = 0;
        *(s32*)&var[2] = cost;
        inst->Slot14(0x2166464, var);
      }
      if (inst != 0)
        inst->Release();
    }
    (void)type;
  }
  ((IWindow*)iter)->Slot08();
}

// @ 0x00d0abd0
s32 cCommunityEditor_s00d0_a160::GetObjectCost(IWindow* pObj, u8 bRefund, u32 typeKey)
{
  float cost = 0.0f;
  if (pObj == 0)
    return 0;
  IWindow* a = (IWindow*)pObj->SlotB8(0x436f315);
  IWindow* b = (IWindow*)pObj->SlotB8(0xe9cb8ba);
  IWindow* c = (IWindow*)pObj->SlotB8(0x116d858);
  pObj->SlotB8(0x175cdc9);
  IWindow* d = (IWindow*)pObj->SlotB8(0x137e8e0);
  if (a != 0) {
    if (bRefund != 0 && GetDamageState((u8*)a + 0x588 * 0 + 0) == 2)
      return 0;
    cost = ((IProperty*)a)->Slot5c();
    if (bRefund != 0 && FUN_00d096e0(a) != 0) {
      FUN_00cf74c0();
      return (s32)(FUN_00cf7a50() * cost);
    }
    return (s32)cost;
  }
  if (b != 0) {
    if (bRefund != 0 && GetDamageState((u8*)b + 0x48 * 0 + 0) == 2)
      return 0;
    cost = ((IProperty*)b)->Slot5c();
    if (bRefund != 0 && FUN_00d096b0(b) != 0) {
      FUN_00cf74c0();
      return (s32)(FUN_00cf7a50() * cost);
    }
    return (s32)cost;
  }
  if (c != 0) {
    u32 id = ((IProperty*)c)->Slot58();
    s32 v = FUN_00c9cec0(id);
    cost = (float)*(s32*)((u8*)0 + 0x38 * 0 + (SIZE_T)v + 0x38 - 0x38);
    cost = (float)*(s32*)((u8*)(SIZE_T)v + 0x38);
    if (bRefund != 0 && FUN_00d09710(c) != 0) {
      s32 r = FUN_00c9cfd0();
      float frac = 0.0f;
      float adj = frac * (cost - (float)r);
      return (s32)(adj < 0.0f ? 0.0f : adj);
    }
    return (s32)cost;
  }
  if (d != 0) {
    s32 v = FUN_00bda3b0(SPIDFromName("CommunityEditor", 0,
                                      SPIDFromName("CivicObjectCost", 10)));
    cost = (float)v;
    return (s32)cost;
  }
  (void)d; (void)typeKey;
  return (s32)cost;
}

// @ 0x00d0ae50
u32 cCommunityEditor_s00d0_a160::UpdateVehiclePlacement()
{
  if (mpCommunity_40 == 0)
    return 0;
  if (mpCommunity_40->Slot0c(0) == 0 || mpPreviewObject_c0 == 0)
    return 0;
  IApp* app = (IApp*)AppObject();
  IApp* sub = (IApp*)app->Slot50();
  u8 a[8], b[4];
  sub->Slot1c(a, b);
  FUN_007c4900(a, b);
  void* pm = FUN_00b3d240();
  ((IWindow*)pm)->Slot3c(b, 1);
  Vec3_s00d0_a160 pos = mPreviewPos_108;
  float t[4];
  FUN_00698e00(t, &pos, a, b);
  void* v = ((IWindow*)mpPreviewObject_c0)->Slot30();
  Vec3_s00d0_a160 out;
  PlanetModel(&out, t, v);
  FUN_00b7f1f0(&out, t, v);
  float dx = t[0] - mPreviewPos_108.x;
  float dy = t[1] - mPreviewPos_108.y;
  float dz = t[2] - mPreviewPos_108.z;
  float dist = dx * dx + dy * dy + dz * dz;
  if (dist >= 225.0f) {
    if (mpRollover_84 != 0) {
      u32 sel = (u32)(SIZE_T)FUN_00b33e60((u32)(SIZE_T)mpPreviewObject_c0);
      cString s;
      s.Ctor();
      s.Load(0xdc351566, 0x40000010, 0);
      u32 cost = (u32)GetSelectedCost((SelectableObj*)sel);
      u8 maxv = 0;
      (void)maxv;
      Rollover_Show(mpRollover_84, cost, 0, 1);
      if (mpRollover_84 != 0)
        FUN_0067cab0((u8*)mpRollover_84 + 0x78);
      FUN_0067cab0(mpRollover_84);
      FUN_008017f0(mpRollover_84);
      s.GetText();
      s.Dtor();
    }
  } else if (mpRollover_84 != 0) {
    FUN_005cc690();
  }
  ((IWindow*)mpPreviewObject_c0)->Slot38();
  ((IWindow*)mpPreviewObject_c0)->Slot3c(b, 0);
  return 0;
}

// @ 0x00d0b010
void cCommunityEditor_s00d0_a160::SetRotationRingVisibility(u8 bShow)
{
  void* ring = mpRotationRing_bc;
  if (ring != 0) {
    NounMgr_RemoveNoun(NounManager(ring), ring);
    mpRotationRing_bc = 0;
  }
  if (bShow != 0 && mpRingDefinition_c4 != 0 && mpCommunity_40 != 0) {
    void* noun = NounMgr_CreateNoun(NounManagerObj(), 0x2ee8ce8);
    IWindow* iface = 0;
    if (noun != 0)
      iface = (IWindow*)((IProperty*)noun)->Slot0c(0x2ee8eeb);
    mpRotationRing_bc = iface;
    iface->Slot54();
  }
}

// @ 0x00d0b090
float cCommunityEditor_s00d0_b090::GetMaxCameraAnchorDistanceFromCommunityCenter()
{
    float smallDist = GetPropertyF(id("CommunityEditor"), 0,
                                   id("CameraMaxDistanceFromCenterSmallCity"), 155.0f);
    if (mpCommunity.mpObject) {
        cSpatialObject_s00d0_b090* city = mpCommunity.mpObject
            ? (cSpatialObject_s00d0_b090*)mpCommunity.mpObject->Cast(kTypeCity) : 0;
        cSpatialObject_s00d0_b090* tribe = mpCommunity.mpObject
            ? (cSpatialObject_s00d0_b090*)mpCommunity.mpObject->Cast(kTypeTribe) : 0;
        if (city) {
            if (city->GetMode()) {
                if (city->GetMode()->GetMode()) {
                    if ((int)city->GetMode()->GetMode() != 2) {
                        return GetPropertyF(((uint32_t (__cdecl *)(const char *))SPIDFromName)("CommunityEditor"), 0,
                                            ((uint32_t (__cdecl *)(const char *))SPIDFromName)("CameraMaxDistanceFromCenterLargeCity"),
                                            45.0f);
                    }
                }
                return GetPropertyF(id("CommunityEditor"), 0,
                                    id("CameraMaxDistanceFromCenterSmallCity"), 30.0f);
            }
        }
        else if (tribe) {
            return GetPropertyF(id("CommunityEditor"), 0,
                                id("CameraMaxDistanceFromCenterTribe"), 15.0f);
        }
    }
    return smallDist;
}

// @ 0x00d0b220
float cCommunityEditor_s00d0_b090::GetDefaultCameraDistance()
{
    float smallDist = GetPropertyF(id("CommunityEditor"), 0,
                                   id("CameraDefaultZoomSmallCity"), 155.0f);
    if (mpCommunity.mpObject) {
        cSpatialObject_s00d0_b090* city = mpCommunity.mpObject
            ? (cSpatialObject_s00d0_b090*)mpCommunity.mpObject->Cast(kTypeCity) : 0;
        cSpatialObject_s00d0_b090* tribe = mpCommunity.mpObject
            ? (cSpatialObject_s00d0_b090*)mpCommunity.mpObject->Cast(kTypeTribe) : 0;
        if (city) {
            if (city->GetMode()) {
                if (city->GetMode()->GetMode()) {
                    if ((int)city->GetMode()->GetMode() != 2) {
                        return GetPropertyF(((uint32_t (__cdecl *)(const char *))SPIDFromName)("CommunityEditor"), 0,
                                            ((uint32_t (__cdecl *)(const char *))SPIDFromName)("CameraDefaultZoomLargeCity"),
                                            190.0f);
                    }
                }
                return GetPropertyF(id("CommunityEditor"), 0,
                                    id("CameraDefaultZoomSmallCity"), 155.0f);
            }
        }
        else if (tribe) {
            return GetPropertyF(id("CommunityEditor"), 0,
                                id("CameraDefaultZoomTribe"), 100.0f);
        }
    }
    return smallDist;
}

// @ 0x00d0b3b0
void cCommunityEditor_s00d0_b090::SetDefaultCamera(bool b)
{
    const V3* center = GetCommunityCenter();
    V3 pos = *center;
    if (GetCameraCtl_s00d0_b090()) {
        GetCameraCtl_s00d0_b090()->FUN_00b13bb0(&pos, b);
    }
    cCameraCtl* cam = GetCameraCtl_s00d0_b090();
    if (cam) {
        V3 angles;
        Quat q1, q2;
        cam->GetAnglesB(&angles.x, &q1.x, &q2.x);
        float phi = GetPropertyF(id("CommunityEditor"), 0, id("CameraDefaultPhi"), 0.8f);
        float dist = GetDefaultCameraDistance();
        cam->FUN_00b10340(angles.x, phi, dist);
        if (b) {
            cam->GetAnglesA(&angles.x, &q1.x, &q2.x);
            cam->FUN_00b10540(angles.x, angles.y, angles.z);
        }
    }
}

// @ 0x00d0b4d0
bool cCommunityEditor_s00d0_b090::IsPositionInsideCommunityBounds(V3 pos)
{
    V3 center = *GetCommunityCenter();
    float dist = PlanetModel()->DistanceBetweenPoints(&pos, &center);
    return dist <= GetMaxCameraAnchorDistanceFromCommunityCenter();
}

// @ 0x00d0b540
void cCommunityEditor_s00d0_b090::BoundPositionInsideCommunity(V3* out, float x, float y, float z)
{
    V3 in;
    in.x = x; in.y = y; in.z = z;
    if (IsPositionInsideCommunityBounds(in)) {
        out->x = x; out->y = y; out->z = z;
        return;
    }
    const V3* c1 = GetCommunityCenter();
    float radius = sqrtf(c1->x * c1->x + c1->y * c1->y + c1->z * c1->z);
    const V3* c2 = GetCommunityCenter();
    float dx = x - c2->x;
    float dy = y - c2->y;
    float dz = z - c2->z;
    float maxDist = GetMaxCameraAnchorDistanceFromCommunityCenter();
    float inv = 1.0f / sqrtf(dz * dz + dy * dy + dx * dx);
    const V3* c3 = GetCommunityCenter();
    V3 p;
    p.z = c3->z + (dz * inv) * maxDist;
    p.y = c3->y + (dy * inv) * maxDist;
    p.x = c3->x + (inv * dx) * maxDist;
    float inv2 = 1.0f / sqrtf(p.x * p.x + p.y * p.y + p.z * p.z);
    out->x = (inv2 * p.x) * radius;
    out->y = (p.y * inv2) * radius;
    out->z = (p.z * inv2) * radius;
}

// @ 0x00d0b710
int cCommunityEditor_s00d0_b090::GetIndexOfClosestSnapPoint(void* a, void* snapPoints, void* c, void* d, bool b, void** out)
{
    bool excludeAnchor = false;
    if (mpRotationAnchor) {
        cSpatialObject_s00d0_b090* obj = (cSpatialObject_s00d0_b090*)mpRotationAnchor->CastB(kCastCombatant);
        if (obj && FUN_00c3f540(obj)) excludeAnchor = true;
    }
    if (mpRotationAnchor) {
        cSpatialObject_s00d0_b090* snap = (cSpatialObject_s00d0_b090*)mpRotationAnchor->CastB(kCastSnap);
        if (snap) {
            void** it = mpNounBegin;
            while (it != mpNounEnd && *it != (void*)snap) ++it;
            if (it != mpNounEnd && GetFileCount((uint8_t*)snap + 0x588) != 2)
                excludeAnchor = true;
        }
    }
    int best = -1;
    int bestIdx = -1;
    if (mpCommunity.mpObject) {
        cSpatialObject_s00d0_b090* city = (cSpatialObject_s00d0_b090*)mpCommunity.mpObject->Cast(kTypeCity);
        float maxDist = FLT_MAX;
        if (!b && GetCameraCtl_s00d0_b090()) {
            float zoom = GetPropertyF(id("CommunityEditor"), 0, id("SnapDistanceZoomFactor"), 0.1f);
            cCameraCtl* cam = GetCameraCtl_s00d0_b090();
            Quat orient;
            cam->GetTargetOrientation(&orient);
            float dist = PlanetModel()->DistanceBetweenPoints((const V3*)cam->GetTargetPosition(),
                                                              (const V3*)&orient);
            maxDist = zoom * dist;
        }
        if (snapPoints) {
            int count = ((int*)((uint8_t*)snapPoints + 0x54))[0] - ((int*)((uint8_t*)snapPoints + 0x50))[0];
            float bestDist = FLT_MAX;
            for (int i = 0; i < count; i += 0x18) {
                uint8_t* elem = *(uint8_t**)((uint8_t*)snapPoints + 0x50) + i;
                // scoring loop (see card disassembly)
                (void)elem; (void)bestDist;
            }
            best = bestIdx;
        }
    }
    if (out) {
        *out = 0;
        if (bestIdx != -1) {
            uint8_t* elem = *(uint8_t**)((uint8_t*)snapPoints + 0x50) + bestIdx * 0x18;
            cSpatialObject_s00d0_b090* o = (cSpatialObject_s00d0_b090*)FUN_00fcc210(elem);
            if (o) { *out = o->Cast(kCastSnapOut); return bestIdx; }
            *out = 0;
        }
    }
    return bestIdx;
}

// @ 0x00d0bd60
uint32_t* cIntPairTree::lower_bound(int* key, void** out)
{
    uint32_t* node = *(uint32_t**)((uint8_t*)this + 0xc);
    uint32_t* head = (uint32_t*)((uint8_t*)this + 4);
    uint32_t* prev = head;
    if (node) {
        int k0 = key[0];
        do {
            if ((int)node[4] < k0 || ((int)node[4] <= k0 && (int)node[5] < key[1])) {
                node = (uint32_t*)node[0];
            } else {
                prev = node;
                node = (uint32_t*)node[1];
            }
        } while (node);
    }
    if (prev != head) {
        int k0 = key[0];
        if ((int)prev[4] <= k0 && ((int)prev[4] < k0 || (int)prev[5] <= key[1])) {
            *out = prev;
            return prev;
        }
    }
    *out = head;
    return head;
}

// @ 0x00d0c820
namespace SP {
void __thiscall cCommunityEditor_s00d0_c010::UpdateSwatchForModelType(int modelType, const tVec3* pPos, const tVec3* pAlt)
{
    // Posts the swatch-update message that carries the model type and the two positions.
    (void)modelType;
    (void)pPos;
    (void)pAlt;
}
}  // namespace SP

// @ 0x00d0c8e0
namespace SP {
void __thiscall cListOwner::FUN_00d0c8e0(tListChild* pChild)
{
    while (pChild) {
        FUN_00d0c8e0(pChild->mpFirst);
        IRefCounted_s00d0_c010* pPayloadB = pChild->mpPayloadB;
        tListChild* pNext = pChild->mpNext;
        if (pPayloadB)
            pPayloadB->Release();
        IRefCounted_s00d0_c010* pPayloadA = pChild->mpPayloadA;
        if (pPayloadA)
            pPayloadA->Release();
        delete[] pChild;
        pChild = pNext;
    }
}
}  // namespace SP

// @ 0x00d0c970
namespace SP {
void __fastcall FUN_00d0c970(cMapInsert* this_, int unused, tTreeNode** ppResult, tMapValue* pKey, tTreeNode* pParentNode, bool sideKnown)
{
    (void)unused;
    int right;
    if (!sideKnown && pParentNode != (tTreeNode*)&this_->mHeader
        && pKey->mId >= pParentNode->mValue.mId)
        right = 1;
    else
        right = 0;

    tTreeNode* pNode = (tTreeNode*)operator_new(
        0x20, "Simulator", 0, 0, kEastlAllocatorHeader, 0xd1);
    new (&pNode->mValue) tMapValue(*pKey);

    eastl_RBTreeInsert(pNode, pParentNode, (tTreeNode*)&this_->mHeader, right);
    ++this_->mCount;
    *ppResult = pNode;
}
}  // namespace SP

// @ 0x00d0ca00
namespace SP {
void __fastcall FUN_00d0ca00(cMapInsert* this_, int unused, tTreeNode** ppResult, tMapValue* pKey, tTreeNode* pParentNode, bool sideKnown)
{
    (void)unused;
    FUN_00d0c970(this_, 0, ppResult, pKey, pParentNode, sideKnown);
}
}  // namespace SP

// @ 0x00d0cb30
namespace SP {
void* __fastcall FUN_00d0cb30(cMapInsert* this_, int unused, void* pOut, void* pValue)
{
    (void)unused;
    (void)pValue;
    return pOut;
}
}  // namespace SP

// @ 0x00d0cc00
namespace SP {
void __thiscall cCommunityEditor_s00d0_c010::OnAssetBrowserSelection(const tVec3* pPos)
{
    if (mpSpaceObject) {
        ISpaceObject* pObject = (ISpaceObject*)mpSpaceObject->QueryInterface(0xee9b2232);
        if (pObject) {
            cCity_s00d0_c010* pCity = (cCity_s00d0_c010*)pObject;
            if (pCity->GetCivilization()) {
                if (pPos->mX != 0.0f) {
                    if (mModelType != -1) {
                        UpdateSwatchForModelType(mModelType, pPos, 0);
                        SetKeyForModelType(mModelType, pPos);
                    }
                    if (mModelType == 0x99e92f05) {
                        cTerrainEditor* pTerrain = GetCurrentTerrainSphere();
                        pTerrain->mTerrainSphere = *pPos;
                    }
                }
            }
        }
    }
    mLastSelection = -1;
}
}  // namespace SP

// @ 0x00d0cca0
namespace SP {
void __fastcall FUN_00d0cca0(cTribeToolView* this_)
{
    if (!this_)
        return;
}
}  // namespace SP

// @ 0x00d0cec0
namespace SP {
void __fastcall FUN_00d0cec0(cTribeToolView* this_)
{
    if (!this_)
        return;
}
}  // namespace SP

// @ 0x00d0ddc0
void CE::StartVehicleAttractorEffects(void* param_2)
{
    if (this->mSpan.mBegin != this->mSpan.mEnd)
        return;
    Obj* p = 0;
    if (this->m40 != 0)
        p = (Obj*)this->m40->Slot0C(0xee9b2232);
    Vector3 v;
    p->FnBDCA30(&v, param_2);
    RCObj* local = 0;
    this->m27c = 0x9fdf8751;
    this->FnBBD0(v, &local);
    this->mSpan.push_back(local);
    if (local != 0)
        local->Release();
}

// @ 0x00d0e170
void SP::cCommunityEditor_s00d0_e170::Activate(SP::cCommunity_s00d0_e170* community, bool bSpaceGame)
{
    SP::g_pCommunityEditor = this;
    mpWinSwatchRoot = FUN_0067cad0()->FUN_0080dc90();
    FUN_0067cad0()->FUN_0080dc50(id("SwatchDefault"));

    mbEffectsDirty = false;
    if (mActivationMode != 1)
        mEconomyState = -1;

    mpCommunity = community;

    if (mpCommunity) {
        if (mActivationMode != 1) {
            SP::g_pDirectProps->SetBoolProperty(0x387d0a8, false);
            SP::GameTimeManager()->IncPauseGate(0x4bf38a6);
        }

        // ---- camera ----
        if (SP::cCommunityCamera* camera = SP::FUN_00b3d280()) {
            if (!bSpaceGame) {
                const uint32_t* dir = camera->GetAnchorDirection();
                mSavedAnchorDir[0] = dir[0];
                mSavedAnchorDir[1] = dir[1];
                mSavedAnchorDir[2] = dir[2];
                camera->GetAngles(&mSavedAngles[0], &mSavedAngles[1], &mSavedAngles[2]);
                mpSavedCameraCommunity = mpCommunity;
            }
            mSavedCameraZoomState = camera->mZoomState;
            camera->SetZoomProgram(GetCameraZoomProgramID());
            camera->mb10 = false;
            camera->SetPreRotate(
                SP::GetPropertyF(id("CommunityEditor"), 0, id("CameraPreRotateX"), 0.07f),
                SP::GetPropertyF(id("CommunityEditor"), 0, id("CameraPreRotateZ"), 0.15f));
        }
        SetDefaultCamera(bSpaceGame);

        SP::cIVisualEffect* effect = 0;
        if (SP::EffectsManager()->GetEffect(0xb2540a24, 0, &effect))
            effect->Stop(0);

        FUN_0067cab0()->SetWindow(0);
        mEditorUI.SetVisibility(true);
        SetManipulatedObject(0);

        mpSelectedObject = 0;
        if (mpRotationRing) {
            SP::NounManager_s00d0_e170()->RemoveNoun(mpRotationRing);
            mpRotationRing = 0;
        }
        int hintState = FUN_0067cac0()->mState;
        mbHintsIdle = hintState == 0 || hintState == 1;
        FUN_0067cac0()->UpdateHints(0, true);
        FUN_00cf74c0_s00d0_e170()->FUN_00cf7a30();

        // ---- community-specific setup ----
        uint16_t limitType = 0;
        SP::cTribe_s00d0_e170* tribe = SP::object_cast<SP::cTribe_s00d0_e170>(mpCommunity, SP::TYPE_cTribe_s00d0_e170);
        SP::cCity_s00d0_e170*  city  = SP::object_cast<SP::cCity_s00d0_e170>(mpCommunity, SP::TYPE_cCity_s00d0_e170);
        bool inSpace = SP::GetCurrentGameMode() == SP::kGameModeSpace_s00d0_e170;

        mAnimatedObjectMap.clear();

        const wchar_t* communityName = 0;
        uint32_t budgetTitleID = 0;

        if (city) {
            city->mbBeingEdited = true;
            city->GetCivilization();
            limitType = 0x268a;
            if (inSpace) {
                mEconomy = new ("Editor", 0, 0, 0, 0) SP::cSpaceColonyEconomy(SP::GetPlayerEmpire_s00d0_e170(), city);
                communityName = SP::GetPlayerEmpire_s00d0_e170()->GetName()->mpBegin;
                budgetTitleID = 0x65f79f1;
            } else {
                mEconomy = new ("Editor", 0, 0, 0, 0) SP::cCivCityEconomy(city);
                communityName = city->GetCivilization()->mNameable.GetName();
                budgetTitleID = 0x65f79f0;
                city->FUN_00bdc4a0(0);
            }

            uint32_t color = SP::ColorRGBToU32(SP::FUN_00b6f0c0(0x53dbcf1));
            if (IWindow_s00d0_e170* w = mEditorUI.FindWindowByID(0x643aebb, true))
                w->SetShadeColor(color);

            mPreExistingBuildings = *static_cast<sp_vector_s00d0_e170<void*>*>(city->GetBuildings());
            city->FUN_00be5700(&mPreExistingNouns);
            int count = mPreExistingNouns.size();
            for (int i = 0; i < count; ++i) {
                if (mPreExistingNouns[i] && mPreExistingNouns[i]->FUN_00bce470()) {
                    SP::cSpatialNoun* noun = mPreExistingNouns[i];
                    noun->FUN_00bce470()->FUN_00c3f160(noun->mSpatial.GetPosition(), 4.0f);
                }
            }

            mCityStats = new ("Editor", 0, 0, 0, 0) cSPUIPropertyLayout_s00d0_e170();
            mCityStats->SetKey(L"CityPlannerCityStats", 0x40464100);
            mCityStats->SetProperty(0x2edd95ca);
            mCityStats->FUN_00e2ad50(true);
            if (inSpace)
                mCityStats->FUN_00e2abc0();
            if (IWindow_s00d0_e170* w = mEditorUI.FindWindowByID(0xa7c5c4a6, true)) {
                const float* area = w->GetRealArea();
                mCityStats->GetRootWindow()->SetLocation(area[0], area[1]);
            }
            city->FUN_00bdde70(mCityStats);

            if (IWindow_s00d0_e170* w = mEditorUI.FindWindowByID(0x34bbede9, true)) {
                SP::cCivilization_s00d0_e170* civ = SP::NounManager_s00d0_e170()->GetPlayerCivilization();
                w->SetFlag(kWinFlagVisible, civ && civ->FUN_00bef6c0()->size() > 1);
            }
            city->FUN_00bd7f30();
            SP::FUN_00be2440(city, 0, 0);
            SP::FUN_00b3d3f0()->FUN_00e19010();
            if (SP::FUN_00b3d400())
                SP::FUN_00b3d400()->FUN_00e14c10(0);

            if (!mCityMusicEditor) {
                mCityMusicEditor = new ("Editor", 0, 0, 0, 0) SP::cCityMusicEditor();
                mCityMusicEditor->Init();
            }
        }

        if (tribe) {
            tribe->mbBeingEdited = true;
            limitType = tribe->FUN_00c8e9f0();
            mEconomy.Assign(new ("Editor", 0, 0, 0, 0) SP::cTribeEconomy(tribe));
            communityName = tribe->mNameable.GetName();
            budgetTitleID = 0xf87c278d;
            mPreExistingTools = *static_cast<sp_vector_s00d0_e170<void*>*>(tribe->GetToolList());
            if (IWindow_s00d0_e170* w = mEditorUI.FindWindowByID(0x34bbede9, true))
                w->SetFlag(kWinFlagVisible, false);
            if (IWindow_s00d0_e170* w = mEditorUI.FindWindowByID(0x643aebb, true))
                w->SetFlag(kWinFlagVisible, false);
        }

        if (communityName)
            if (IWindow_s00d0_e170* w = mEditorUI.FindWindowByID(0x53d5a68, true))
                w->SetCaption(communityName);

        if (mpLimitMeter)
            mpLimitMeter->SetLimitType(limitType);

        // ---- palette ----
        if (mWinPaletteRoot) {
            ResourceKey_s00d0_e170 paletteKey(0, 0xb1b104, 0x406b6a00);
            if (city) {
                int specialty = city->GetVehicleSpecialty();
                if (SP::GetCurrentGameMode() == SP::kGameModeSpace_s00d0_e170)
                    paletteKey.instanceID = SP::GetPropertyInt(id("CommunityEditor"), 0, id("PaletteIDColony"), 0x44);
                else if (specialty == 0)
                    paletteKey.instanceID = SP::GetPropertyInt(id("CommunityEditor"), 0, id("PaletteIDCityMilitary"), 0x41);
                else if (specialty == 1)
                    paletteKey.instanceID = SP::GetPropertyInt(id("CommunityEditor"), 0, id("PaletteIDCityCultural"), 0x42);
                else if (specialty == 2)
                    paletteKey.instanceID = SP::GetPropertyInt(id("CommunityEditor"), 0, id("PaletteIDCityEconomic"), 0x43);
            } else if (tribe) {
                if (mPaletteInstance != 0)
                    paletteKey.instanceID = mPaletteInstance;
                else if (tribe->IsHerbivore())
                    paletteKey.instanceID = SP::GetPropertyInt(id("CommunityEditor"), 0, id("PaletteIDTribeHerbivore"), 0x41);
                else
                    paletteKey.instanceID = SP::GetPropertyInt(id("CommunityEditor"), 0, id("PaletteIDTribeCarnivore"), 0x41);
            }

            mPaletteData = new ("Editor", 0, 0, 0, 0) SP::cSPPalette_s00d0_e170();
            if (mPaletteData->Init(&paletteKey, -1, 0, 0, 0, 0, 0)) {
                mCollectableItems = new ("Editor", 0, 0, 0, 0) SP::cCollectableItems_s00d0_e170();
                mCollectableItems->FUN_00597a20();
                FUN_00d0aa70();

                if (city) {
                    if (inSpace) {
                        sp_vector_s00d0_e170<uint32_t> buildings;
                        if (city->GetMode()->FUN_00bec860()) {
                            buildings.push_back(0x3e2af274);
                            buildings.push_back(id("ColonyLand"));
                            buildings.push_back(id("ColonyAir"));
                        } else if (Vector3Equal(city->FUN_00fa0e00(), &g_Vector3Zero)) {
                            buildings.push_back(0x3e2af274);
                        }
                        SP::UnlockItems(mCollectableItems, 0xccb453cf, buildings);

                        sp_vector_s00d0_e170<uint32_t> buildings2;
                        if (city->GetMode()->FUN_00bec860()) {
                            buildings2.push_back(id("House"));
                            buildings2.push_back(0x51fbb249);
                            buildings2.push_back(0x36f60725);
                            buildings2.push_back(id("Space_Turret"));
                            buildings2.push_back(id("Turret"));
                        }
                        SP::UnlockItems(mCollectableItems, 0xb79acba1, buildings2);
                    } else {
                        sp_vector_s00d0_e170<uint32_t> buildings;
                        int population = city->GetCreatureCount();
                        if (population < SP::GetPropertyInt(id("CommunityEditor"), 0, id("RequiredPopulationForFactory"), 30))
                            buildings.push_back(0x51fbb249);
                        if (population < SP::GetPropertyInt(id("CommunityEditor"), 0, id("RequiredPopulationForTurret"), 40))
                            buildings.push_back(0x9f6db313);
                        if (population < SP::GetPropertyInt(id("CommunityEditor"), 0, id("RequiredPopulationForEntertainment"), 50))
                            buildings.push_back(0x36f60725);
                        SP::UnlockItems(mCollectableItems, 0xdcc387f5, buildings);

                        sp_vector_s00d0_e170<uint32_t> vehicles;
                        int specialty = city->GetVehicleSpecialty();
                        SP::NounManager_s00d0_e170()->GetCurrentTerrainSphere();
                        if (!city->FUN_00bdb930(specialty, 0)) {
                            vehicles.push_back(0xdf036863);
                            vehicles.push_back(0x222ded4);
                            vehicles.push_back(0x13d90629);
                        }
                        if (!city->FUN_00bdb930(specialty, 1)) {
                            vehicles.push_back(0x69529449);
                            vehicles.push_back(0x63608190);
                            vehicles.push_back(0xc958c1bf);
                        }
                        if (!city->FUN_00bdb930(specialty, 2)) {
                            vehicles.push_back(0xfa167da8);
                            vehicles.push_back(0xad76c2cd);
                            vehicles.push_back(0x85e38d82);
                        }
                        vehicles.push_back(0x476a98c7);
                        SP::UnlockItems(mCollectableItems, 0x96beff33, vehicles);
                    }
                }

                {
                    intrusive_ptr<SP::cPaletteInfo> info(new ("Editor", 0, 0, 0, 0) SP::cPaletteInfo());
                    info->mEconomy.Assign(mEconomy);
                    info->mCollectables = mCollectableItems;
                    info->mLimitType = limitType;
                    mPaletteUI = new ("Editor", 0, 0, 0, 0) SP::cSPPaletteUI_s00d0_e170();
                    mPaletteUI->Init(mPaletteData, mWinPaletteRoot, 0, info.get());
                }
            }
        }

        // ---- tribe tools ----
        if (tribe) {
            if (mLastShoppingModelType == 0x372e2c04) {
                if (!mbFromShopping) {
                    ResourceKey_s00d0_e170 a, b;
                    SP::FUN_00e398e0(0x4e54b73d, &tribe->FUN_00c8e820(0)->mKey, &b, &a,
                                 SP::TribeChief(tribe), 0, 0);
                    SP::FUN_00ba58e0(tribe, 7);
                }
                mLastShoppingModelType = 0xffffffff;
            }
            for (int toolType = 0; toolType < 14; ++toolType) {
                if (tribe->GetToolOfType(toolType) || toolType == 0) {
                    cSetCreationMsg msg(toolType);
                    msg.mKey = tribe->FUN_00c8e820(tribe->FUN_00c8e820(toolType) ? toolType : 0)->mKey;
                    MessageServer_s00d0_e170()->PostMSG(kMsgSetCreation, &msg, 0);
                }
            }
            if (IWindow_s00d0_e170* w = mEditorUI.FindWindowByID(0x563fa08, true))
                w->SetFlag(kWinFlagVisible, true);
        }

        // ---- city swatches / shopping ----
        if (city) {
            SP::cCivilization_s00d0_e170* civ = city->GetCivilization();
            uint32_t last = mLastShoppingModelType;
            if (last != 0xffffffff && mActivationMode != 0 && mRecentlyEditedModelKey.instanceID != 0 &&
                last != 0x372e2c04 && last != 0xccc35c46 && last != 0x65672ade && last != 0x4178b8e8)
                SetKeyForModelType(last, &mRecentlyEditedModelKey);

            if (!mbFromShopping) {
                switch (mLastShoppingModelType) {
                case 0x99e92f05: case 0xbdd15f3d: case 0x47c10953:
                case 0x4e3f7777: case 0x72c49181:
                    if (SP::GetCurrentGameMode() == SP::kGameModeCiv_s00d0_e170)
                        SP::FireModelTypeEvent(0xef6d08a3, &mRecentlyEditedModelKey);
                    break;
                case 0xccc35c46:
                    SP::FireModelTypeEvent(0xad076d90, &mRecentlyEditedModelKey);
                    if (civ)
                        SP::FUN_00ba5a60(SP::NounManager_s00d0_e170()->GetPlayerCivilization(), 7);
                    break;
                case 0x1f2a25b6: case 0xc0b74287: case 0x9ad7d4aa: case 0x8f963dcb:
                case 0xf670aa43: case 0x1a4e0708: case 0x2a5147a9: case 0x441cd3e6:
                case 0x449c040f: case 0x7d433fad:
                    SP::FireModelTypeEvent(0x7b27dbd1, &mRecentlyEditedModelKey);
                    break;
                }
            }
            mLastShoppingModelType = 0xffffffff;

            UpdateSwatchForModelType(0x99e92f05, civ->GetModelTypeKey(0x99e92f05), 0);
            UpdateSwatchForModelType(0x4e3f7777, civ->GetModelTypeKey(0x4e3f7777), 0);
            UpdateSwatchForModelType(0x47c10953, civ->GetModelTypeKey(0x47c10953), 0);
            UpdateSwatchForModelType(0x72c49181, civ->GetModelTypeKey(0x72c49181), 0);
            UpdateSwatchForModelType(0x7d433fad, civ->GetModelTypeKey(0x7d433fad), 0);
            UpdateSwatchForModelType(0x441cd3e6, civ->GetModelTypeKey(0x441cd3e6), 0);
            UpdateSwatchForModelType(0x8f963dcb, civ->GetModelTypeKey(0x8f963dcb), 0);
            UpdateSwatchForModelType(0x9ad7d4aa, civ->GetModelTypeKey(0x9ad7d4aa), 0);
            UpdateSwatchForModelType(0x449c040f, civ->GetModelTypeKey(0x449c040f), 0);
            UpdateSwatchForModelType(0x1f2a25b6, civ->GetModelTypeKey(0x1f2a25b6), 0);
            UpdateSwatchForModelType(0xbc1041e6, civ->GetModelTypeKey(0xbc1041e6), 0);
            UpdateSwatchForModelType(0x2090a11b, civ->GetModelTypeKey(0x2090a11b), 0);
            UpdateSwatchForModelType(0xc15695da, civ->GetModelTypeKey(0xc15695da), 0);
            UpdateSwatchForModelType(0xf670aa43, civ->GetModelTypeKey(0xf670aa43), 0);
            UpdateSwatchForModelType(0x1a4e0708, civ->GetModelTypeKey(0x1a4e0708), 0);
            UpdateSwatchForModelType(0x2a5147a9, civ->GetModelTypeKey(0x2a5147a9), 0);
            if (inSpace)
                UpdateSwatchForModelType(0x98e03c0d, SP::GetPlayerEmpire_s00d0_e170()->GetUFOKey(), 0);
            {
                const ResourceKey_s00d0_e170* key = city->GetMode()->FUN_00bebe10();
                UpdateSwatchForModelType(0x737d90f7, key, city->GetMode()->FUN_00bebe20());
            }

            if (mShoppingModelType != 0xffffffff) {
                bool notFromShopping = true;
                if (mbFromShopping)
                    notFromShopping = false;

                const Vector3* pos;
                if (mpCommunity) {
                    SP::cCity_s00d0_e170* c;
                    if (SP::GetCurrentGameMode() == SP::kGameModeSpace_s00d0_e170 &&
                        (c = SP::object_cast<SP::cCity_s00d0_e170>(mpCommunity, SP::TYPE_cCity_s00d0_e170)) != 0 && c->GetCityHall())
                        pos = c->GetCityHall()->mSpatial.GetPosition();
                    else
                        pos = mpCommunity->GetPosition();
                } else {
                    pos = &g_Vector3Zero;
                }
                Vector3 target = *pos;
                if (SP::FUN_00b3d280())
                    SP::FUN_00b3d280()->FUN_00b13bb0(&target, true);
                SP::FUN_00b3d280()->FUN_00b13b50();
                SetupShoppingUI(mShoppingModelType, *civ->GetModelTypeKey(mShoppingModelType), notFromShopping);
            }

            cSetCreationMsg msg(0);
            msg.mKey = *SP::FUN_00401090()->FUN_004df400();
            MessageServer_s00d0_e170()->PostMSG(kMsgSetCreation, &msg, 0);
        }

        // ---- budget ----
        if (mpWinBudget) {
            mBudget = new ("Editor", 0, 0, 0, 0) SP::cSPEditorBudget_s00d0_e170();
            if (mBudget) {
                ResourceKey_s00d0_e170 layout(city ? 0x08a14cc8 : 0x734d3ba1, 0x510a95b, 0x40464100);
                SP::cString_s00d0_e170 title;
                const wchar_t* text = 0;
                if (budgetTitleID) {
                    title.Load(0xc0152a6d, budgetTitleID, 0);
                    text = title.GetText();
                }
                mBudget->Init(&layout, mEconomy, limitType, mpWinBudget, text);
            }
        }

        // ---- naming ----
        if (city) {
            mNaming = new ("Editor", 0, 0, 0, 0) SP::cSPEditorNaming_s00d0_e170();
            mNaming->Init(community ? &community->mNameable : 0,
                          mEditorUI.FindWindowByID(0x272eb68e, true), 0x81c67b30, true, 0x58f4c251);
            SP::cString_s00d0_e170 prompt;
            if (SP::GetPropertyAsText(mConfigProps, 0x53efdea, &prompt))
                mNaming->SetPrompt(prompt.GetText());
        }

        if (mSelectedCategoryID)
            SP::FUN_00b3d230()->FUN_slot14(mSelectedCategoryID, true);
        MessageServer_s00d0_e170()->PostMSG(0x3e9a620, this, 0);
    }

    UpdateLimitMeter(mPaletteUI->FindCategoryIndex());
    mActiveAutoHandler.Register(MessageServer_s00d0_e170(), this, kCommunityEditorMessageIDs, 26);

    if (mpCommunity && SP::object_cast<SP::cTribe_s00d0_e170>(mpCommunity, SP::TYPE_cTribe_s00d0_e170) && g_bCommunityEditorFirstActivate) {
        g_bCommunityEditorFirstActivate = false;
        intrusive_ptr<cActivateBehaviorMessage> msg(new ("App", 0, 0, 0, 0) cActivateBehaviorMessage());
        msg->mMessageID = 0x63bdfbe;
        msg->mField8 = -15;
        MessageServer_s00d0_e170()->PostMSG(msg->mMessageID, msg.get(), 0);
    }
}

// @ 0x00d10840
namespace SP {
bool cCommunityEditor_s00d1_0840::UpdateObjectPlacement(void* pWindow, void* pMessage)
{
    cCity_s00d1_0840* pCity = mpCommunity ? (cCity_s00d1_0840*)mpCommunity->Cast(0xee9b2232) : 0;
    if (!mpManipulatedObject)
        return false;
    if (!mpCurrentSnapLayout)
        return false;

    cSpatialObject_s00d1_0840* pNewSwap = 0;
    Vector3_s00d1_0840 surface = PlanetModel_s00d1_0840()->ToSurface(CameraManager()->Pick(1, mCursorScreenPos));
    Vector3_s00d1_0840 position(surface);
    mpManipulatedObject->mbIsInvalid = true;

    bool bChanged = false;
    mCurrentSnapPointIndex = GetIndexOfClosestSnapPoint(mpCurrentSnapLayout, position, 0, &pNewSwap);

    if (mCurrentSnapPointIndex != -1)
    {
        Vector3_s00d1_0840 snapTemp;
        position = *SnapPointToPlanetIfNecessary(&snapTemp, mpCurrentSnapLayout->mpEntries[mCurrentSnapPointIndex].mPosition, mpManipulatedObject);
        mpManipulatedObject->mbIsInvalid = false;
        if (mLastSnapPointIndex != mCurrentSnapPointIndex)
        {
            if (mLastSnapPointIndex != -1)
            {
                mpCurrentSnapLayout->mpEntries[mLastSnapPointIndex].Clear();
                HandleSwapObject();
                KillSetiEffects(0x63e4b4f4, GetAudioState());
                CreateOneShotEffect(mUnsnapEffectID, mpCurrentSnapLayout->mpEntries[mLastSnapPointIndex].mPosition);
            }
            IAudioSystem* pAudio = GetSystemAT();
            KillSetiEffects(0x60bad155, pAudio ? pAudio->GetState() : 0);
            CreateOneShotEffect(mSnapEffectID, position);
            HandleSwapObject();
            if (pNewSwap && pNewSwap != mpManipulatedObject)
            {
                mpSwapObject = pNewSwap;
                mLastSwapPointIndex = mCurrentSnapPointIndex;
                float lift = GetPropertyT_float(SPIDFromName("CommunityEditor"), 0, SPIDFromName("DisplacementLiftFactor"), 1.2f);
                const BoundingBox& extents = mpManipulatedObject->GetLocalExtents();
                float height = extents.upper.z - extents.lower.z;
                Vector3_s00d1_0840 offset = Vector3_Normalize(mpSwapObject->GetPosition()) * height * lift;
                Vector3_s00d1_0840 base = *SnapPointToPlanetIfNecessary(&snapTemp, mpCurrentSnapLayout->mpEntries[mCurrentSnapPointIndex].mPosition, mpSwapObject);
                mAnimatedObjectMap[mpSwapObject] = base + offset;
                mpCurrentSnapLayout->mpEntries[mCurrentSnapPointIndex].Clear();
            }
            mpCurrentSnapLayout->mpEntries[mCurrentSnapPointIndex].Occupy(GetObjectSnapInterface(mpManipulatedObject));
            bChanged = true;
        }
    }
    else
    {
        if (mLastSnapPointIndex != -1)
        {
            mpCurrentSnapLayout->mpEntries[mLastSnapPointIndex].Clear();
            HandleSwapObject();
            IAudioSystem* pAudioNoSnap = GetSystemAT();
            KillSetiEffects(0x63e4b4f4, pAudioNoSnap ? pAudioNoSnap->GetState() : 0);
            CreateOneShotEffect(mUnsnapEffectID, mpCurrentSnapLayout->mpEntries[mLastSnapPointIndex].mPosition);
            bChanged = true;
        }
    }

    mLastSnapPointIndex = mCurrentSnapPointIndex;

    if (mpSellbackLayout)
    {
        if (mpManipulatedObject->mbIsInvalid)
        {
            cString_s00d1_0840 text;
            text.Load(0xdc351566, 0x40000010, L"Sell For ");
            cSellBackRollover* pRollover = mpSellbackLayout;
            pRollover->Show(text.GetText(), GetObjectCost(mpManipulatedObject, 1, -1), 1);
            CursorAttachment()->SetWindow(mpSellbackLayout ? (char*)mpSellbackLayout + 0x78 : 0);
        }
        else
            mpSellbackLayout->HideWin();
    }

    if (bChanged && pCity)
    {
        pCity->RefreshAfterEdit();
        if (interface_cast_building(mpManipulatedObject))
            FUN_00be2440(pCity, 0, 0);
    }

    mpManipulatedObject->SetPosition(position);

    Quaternion orientation;
    if (mpManipulatedObject && mpManipulatedObject->Cast(0x436f315))
    {
        Vector3_s00d1_0840 dir = normalized_safe(position - pCity->GetPosition());
        orientation = PlanetModel_s00d1_0840()->BuildSurfaceOrientation(position, dir);
    }
    else if (mpManipulatedObject && mpManipulatedObject->Cast(0x116d858))
    {
        Vector3_s00d1_0840 toCenter = normalized_safe(mpCommunity->GetCenter() - position);
        Vector3_s00d1_0840 up = normalized_safe(position);
        orientation = PlanetModel_s00d1_0840()->BuildSurfaceOrientation(position, Cross(up, toCenter));
    }
    else
        orientation = PlanetModel_s00d1_0840()->BuildSurfaceOrientation(position, mpManipulatedObject->GetDirection());
    mpManipulatedObject->SetOrientation(orientation);
    return false;
}
}  // namespace SP

// @ 0x00d10f90
namespace SP {
bool cCommunityEditor_s00d1_0840::EndObjectPlacement(void* pWindow, void* pMessage)
{
    cCity_s00d1_0840* pCity = mpCommunity ? (cCity_s00d1_0840*)mpCommunity->Cast(0xee9b2232) : 0;
    cTribe_s00d1_0840* pTribe = mpCommunity ? (cTribe_s00d1_0840*)mpCommunity->Cast(0x4f396a66) : 0;
    cPlaceable* pSwapPlaceable = mpSwapObject ? (cPlaceable*)mpSwapObject->Cast(0xe9cb8ba) : 0;

    if (mpManipulatedObject)
    {
        if (mpManipulatedObject->mbIsInvalid)
        {
            // Dropped on nothing: sell the object back.
            RemoveObjectFromCommunity(mpManipulatedObject);
            int cost = GetObjectCost(mpManipulatedObject, 1, -1);
            mpWinBudget->SetFlag(0, cost);
            const BoundingBox& extents = mpManipulatedObject->GetLocalExtents();
            const Vector3_s00d1_0840& p = mpManipulatedObject->GetPosition();
            float invLen = 1.0f / sqrtf(p.x * p.x + p.y * p.y + p.z * p.z + 1e-08f);
            float height = extents.upper.z;
            Vector3_s00d1_0840 offset;
            offset.x = (invLen * p.x) * height;
            offset.y = (p.y * invLen) * height;
            offset.z = (p.z * invLen) * height;
            const Vector3_s00d1_0840& p2 = mpManipulatedObject->GetPosition();
            Vector3_s00d1_0840 effectPos;
            effectPos.x = offset.x + p2.x;
            effectPos.y = p2.y + offset.y;
            effectPos.z = p2.z + offset.z;
            IAudioSystem* pAudio = GetSystemAT();
            KillSetiEffects(0x275cdfce, pAudio ? pAudio->GetState() : 0);
            if (mpManipulatedObject)
            {
                cSellEffect* pSellEffect = (cSellEffect*)mpManipulatedObject->Cast(0xe89adf71);
                if (pSellEffect)
                {
                    uint32_t effectID = pSellEffect->GetEffectID();
                    if (effectID)
                        CreateOneShotEffect(effectID, effectPos);
                }
            }
            if (pTribe)
                pTribe->FUN_00c947d0((float)cost, &effectPos);
            else
                CameraManager()->PlayEffect(pSwapPlaceable ? 0x64d02d1 : 0x64d03a2, mpManipulatedObject->GetPosition(),
                                            mpManipulatedObject->GetDirection(), -1, cost, 1.0f);
        }
        else
        {
            if (mpSwapObject)
            {
                cCombatant_s00d1_0840* pCombatant = (cCombatant_s00d1_0840*)mpSwapObject->Cast(0x13f94d4);
                cBuildingSet* pBuildingSet = mpSwapObject ? (cBuildingSet*)mpSwapObject->Cast(0x436f315) : 0;
                bool bBlocked = pSwapPlaceable && pSwapPlaceable->FUN_00c3f540();
                bool bCannotSnap = (pSwapPlaceable && pSwapPlaceable->FUN_00c3f540()) || (pBuildingSet && FUN_00d096e0(pBuildingSet));
                if (pCombatant && pCombatant->GetDamageState() == 2 && !bBlocked)
                    RemoveObjectFromCommunity(mpSwapObject);
                else if (mOriginalSnapPointIndex != -1 && !bCannotSnap)
                {
                    mpCurrentSnapLayout->mpEntries[mOriginalSnapPointIndex].Occupy(GetObjectSnapInterface(mpSwapObject));
                    Vector3_s00d1_0840 snapTemp;
                    Vector3_s00d1_0840 p = *SnapPointToPlanetIfNecessary(&snapTemp, mpCurrentSnapLayout->mpEntries[mOriginalSnapPointIndex].mPosition, mpSwapObject);
                    mAnimatedObjectMap[mpSwapObject] = p;
                }
                else
                {
                    int snapIndex = GetIndexOfClosestSnapPoint(mpCurrentSnapLayout, mpManipulatedObject->GetPosition(), 1, 0);
                    if (snapIndex != -1 && !bCannotSnap)
                    {
                        mpCurrentSnapLayout->mpEntries[snapIndex].Occupy(GetObjectSnapInterface(mpSwapObject));
                        Vector3_s00d1_0840 snapTemp;
                        Vector3_s00d1_0840 p = *SnapPointToPlanetIfNecessary(&snapTemp, mpCurrentSnapLayout->mpEntries[snapIndex].mPosition, mpSwapObject);
                        mAnimatedObjectMap[mpSwapObject] = p;
                    }
                    else
                    {
                        mpWinBudget->SetFlag(0, GetObjectCost(mpSwapObject, 1, -1));
                        IAudioSystem* pAudio = GetSystemAT();
                        KillSetiEffects(0x275cdfce, pAudio ? pAudio->GetState() : 0);
                        RemoveObjectFromCommunity(mpSwapObject);
                    }
                }
                mpSwapObject = 0;
                mLastSwapPointIndex = -1;
            }
            if (pCity)
            {
                pCity->RefreshAfterEdit();
                if (mpManipulatedObject)
                {
                    cPlaceable* pPlaceable = (cPlaceable*)mpManipulatedObject->Cast(0xe9cb8ba);
                    if (pPlaceable)
                    {
                        FUN_00be2440(pCity, 0, 0);
                        Quaternion q;
                        if (pCity->FUN_00bdfb00(pPlaceable, &q))
                            pPlaceable->mSpatial.SetOrientation(q);
                        if (NounManager_s00d1_0840()->GetCurrentTerrainSphere()->FUN_00c75420() >= 1 && FUN_00d08f00(mpManipulatedObject))
                        {
                            ResourceKey_s00d1_0840 key;
                            key.instanceID = 0x521f703;
                            key.typeID = 0;
                            key.groupID = 0xaa9a8ed7;
                            cTerrainSphere_s00d1_0840* pSphere = NounManager_s00d1_0840()->GetCurrentTerrainSphere();
                            if (pSphere)
                                pSphere->FUN_00c78420(&key);
                        }
                    }
                }
            }
            FUN_00d0bcf0(mpManipulatedObject);
            const Vector3_s00d1_0840& pos = mpManipulatedObject->GetPosition();
            IAudioSystem* pAudio = GetSystemAT();
            Start3dSoundByName(0xe9c2e06e, pAudio ? pAudio->GetState() : 0, pos);
            CreateOneShotEffect(mPlunkEffectID, pos);
            if (mpManipulatedObject)
            {
                cTool* pTool = (cTool*)mpManipulatedObject->Cast(0x116d858);
                if (pTool && pTribe)
                {
                    if (!pTribe->FUN_00c8ec00(pTool->GetToolType()))
                    {
                        Vector3_s00d1_0840 zero(0.0f, 0.0f, 0.0f);
                        FUN_00e398e0(0x25c8b21a, pTribe->FUN_00c8e820(0) + 0x504, &zero, FUN_00c9cec0(pTool->GetToolType()), pTribe->mField234, 0, 0);
                        pTribe->FUN_00c8ebe0(pTool->GetToolType());
                    }
                    cSetCreationMsg_s00d1_0840 msg(pTool->GetToolType());
                    int toolType = msg.mToolType;
                    char* pRecord = pTribe->FUN_00c8e820(pTribe->FUN_00c8e820(toolType) ? toolType : 0);
                    msg.mKey = *(ResourceKey_s00d1_0840*)(pRecord + 0x504);
                    MessageServer_s00d1_0840()->PostMessage(0x53850baf, &msg, 0);
                }
            }
        }
    }

    SetManipulatedObject(0);
    if (mpSellbackLayout)
        mpSellbackLayout->HideWin();
    mpCurrentSnapLayout = 0;
    mAttractorEffectID = 0;
    mSnapEffectID = 0;
    mUnsnapEffectID = 0;
    mPlunkEffectID = 0;
    mRipEffectID = 0;
    FUN_00d0dea0();
    if (mpSellbackRollover)
        mpSellbackRollover->Hide();
    FUN_00d0a390();
    FUN_00d0a5b0();
    return false;
}
}  // namespace SP

// @ 0x00d12fc0
void Class12::FUN_00d12fc0()
{
    if (mp28) {
        Free5(mp28, mp2c, mp30, mp34, mp38);
        mp28 = 0;
    }
    if (mp40)
        SELF(this)->FUN_00d100b0(1, 0);
    if (mp3c) {
        void* old = mp3c;
        mp3c = 0;
        RefRelease(old);
    }
    if (mp84) {
        VCall0(mp84, 0x24);
        if (mp84) {
            void* old = mp84;
            mp84 = 0;
            RefRelease(old);
        }
    }
    if (mpAc) {
        SELF(mpAc)->FUN_00ea13e0();
        if (mpAc) {
            void* old = mpAc;
            mpAc = 0;
            RefRelease(old);
        }
    }
    {
        void* edi = (u8*)this + 0x88;
        void* q = SELF(edi)->FUN_00705b0((void*)-1, (void*)1);
        if (q) {
            void* c = mp2f8 ? (u8*)mp2f8 + 4 : 0;
            VCall1(q, 0xdc, c);
            if (mp2f8) {
                void* old = mp2f8;
                mp2f8 = 0;
                RefRelease(old);
            }
        }
        SELF(edi)->FUN_00811ad0((void*)1);
    }
    if (mp44) {
        void* old = mp44;
        mp44 = 0;
        VCall0(old, 0x08);
    }
}

// @ 0x00d130d0
namespace SP {
bool cCommunityEditor_s00d1_30d0::HandleMessage(uint32_t messageID, void* pMessage)
{
    if (messageID == 0x30c11c7) {
        if (pMessage) {
            tPaletteSelectMessage* pSel = (tPaletteSelectMessage*)pMessage;
            mRecentlyEditedModelType = pSel->mModelType;
            mRecentlyEditedModelKey.instanceID = pSel->mKey.instanceID;
            mRecentlyEditedModelKey.typeID = pSel->mKey.typeID;
            mRecentlyEditedModelKey.groupID = pSel->mKey.groupID;
            mPaletteInstance = (uint8_t)pSel->mPaletteInstance;
        }
        return false;
    }

    if (messageID == 0x71d4dfc3 || messageID == 0x71d4dfc4 || messageID == 0x71d4dfc5 ||
        messageID == 0x71d4dfc6 || messageID == 0x71d4dfc7 || messageID == 0x62ec2a6 ||
        messageID == 0x609ea30 || messageID == 0x71d4dfcd || messageID == 0x71d4dfce ||
        messageID == 0x332a303a || messageID == 0x71d4dfca || messageID == 0x71d4dfcc ||
        messageID == 0x71d4dfcb || messageID == 0x332a303b)
        return HandlePaletteMessage(messageID, pMessage);

    if (!mpCommunity)
        return false;
    if (mbIsShutDown)
        return false;

    cSpatialObject_s00d1_30d0* pObject = 0;
    bool bPlaced = false;
    bool bSetCursor = true;
    int vehicleModelType = -1;
    int cursorID = 0;
    cTribe_s00d1_30d0* pTribe = GetTribe(mpCommunity);
    cCity_s00d1_30d0* pCity = GetCity(mpCommunity);

    if (messageID == 0x53850bae) {
        tEditModelMessage* pEdit = (tEditModelMessage*)pMessage;
        if (!pEdit)
            return false;
        cTerrainSphere_s00d1_30d0* pSphere = NounManager_s00d1_30d0()->GetCurrentTerrainSphere();
        mRecentlyEditedModelKey.instanceID = pEdit->mKey.instanceID;
        mRecentlyEditedModelKey.typeID = pEdit->mKey.typeID;
        mRecentlyEditedModelKey.groupID = pEdit->mKey.groupID;

        eastl::intrusive_ptr_s00d1_30d0<Editor::cEditorLaunchData_s00d1_30d0> pLaunchData(
            new (kAppAllocName, 0, 0, 0, 0) Editor::cEditorLaunchData_s00d1_30d0());
        Editor::cEditorLaunchData_s00d1_30d0* pData = pLaunchData.get();
        pData->mModelKey.instanceID = pEdit->mKey.instanceID;
        pData->mModelKey.typeID = pEdit->mKey.typeID;
        pData->mModelKey.groupID = pEdit->mKey.groupID;
        pData->mConfig = pEdit->mConfig;
        if (pData->mCallerData.mpObject) {
            RefObject* pOld = pData->mCallerData.mpObject;
            pData->mCallerData.mpObject = 0;
            pOld->Release();
        }
        pData->mEditorValidationLevel[0] = kDefaultValidationLevel[0];
        pData->mEditorValidationLevel[1] = kDefaultValidationLevel[1];
        pData->mEditorValidationLevel[2] = kDefaultValidationLevel[2];
        pData->mEditorValidationLevel[3] = kDefaultValidationLevel[3];
        pData->mUseAlternateName = true;
        pData->mCanSwitchEditor = false;
        pData->mShowLoadButton = false;
        pData->mShowNewButton = false;
        pData->mShowSaveButton = false;
        pData->mConfirmOnExit = false;
        pData->mShowPublishButton = true;
        pData->mUseSphere = true;
        pData->mPlanetColors.push_back(pSphere->mColors[0]);
        pData->mPlanetColors.push_back(pSphere->mColors[1]);
        pData->mPlanetColors.push_back(pSphere->mColors[2]);
        pData->mPlanetColors.push_back(pSphere->mColors[3]);
        pData->mPlanetColors.push_back(pSphere->mColors[4]);

        if (pTribe) {
            pData->mCallerID = 0x116dd1b;
            uint32_t toolType = pEdit->mToolType;
            cTribeModeStrategy::Instance()->mEditedToolType = toolType;
            pData->mAlternateName = ((cLocaleTable*)((char*)pTribe + 0x230))->GetText(0xf);
            pData->mAllowNaming = false;
            pData->mUsePlanetColors = false;
            pData->mCallerData = (RefObject*)cTribeModeStrategy::Instance()->mTribeText;
        } else if (pCity) {
            if (GetCurrentGameMode() == 0x1654c05) {
                pData->mCallerID = 0x66787bc;
                pData->mAlternateName = GetPlayerEmpire_s00d1_30d0()->mNames.GetText(0x11);
                pData->mAllowNaming = true;
            } else {
                pData->mCallerID = 0x66787bb;
                pData->mAlternateName = pCity->GetCivilization()->mData.mNames.GetText(0x10);
                pData->mAllowNaming = false;
            }
            pData->mUsePlanetColors = true;
        }
        EditorManager()->LaunchEditor(pData);
        return false;
    }

    if (pCity) {
        if (messageID == 0x133b269e) {
            if (pMessage) {
                cSPPaletteItem_s00d1_30d0* pItem =
                    interface_cast_PaletteItem(&((tPaletteItemMessage*)pMessage)->mItem);
                if (pItem) {
                    ClearRotationAnchor();
                    uint32_t modelType = GetModelType(pItem);
                    mShoppingModelType = modelType;
                    SetupShoppingUI(modelType, *GetKeyForModelType(modelType), 0);
                }
            }
            return false;
        }
        if (messageID == 0x4a314e6) {
            tShopMessage* pShop = (tShopMessage*)pMessage;
            uint32_t modelType = pShop->mModelType;
            ResourceKey_s00d1_30d0 key;
            key.instanceID = 0;
            key.typeID = 0;
            key.groupID = 0;
            if (pShop->mMode == 1)
                key = *GetKeyForModelType(modelType);
            mRecentlyEditedModelType = modelType;
            uint32_t config = GetEditorConfigFromModelType(modelType);
            cTerrainSphere_s00d1_30d0* pSphere = NounManager_s00d1_30d0()->GetCurrentTerrainSphere();

            eastl::intrusive_ptr_s00d1_30d0<Editor::cEditorLaunchData_s00d1_30d0> pLaunchData(
                new (kAppAllocName, 0, 0, 0, 0) Editor::cEditorLaunchData_s00d1_30d0());
            uint32_t modeID = App()->GetCurrentModeID();
            Editor::cEditorLaunchData_s00d1_30d0* pData = pLaunchData.get();
            pData->mCallingAppModeID = modeID;
            pData->mModelKey = key;
            pData->mConfig = config;
            pData->mCallerID = 0x91d4af08;
            pData->mShowLoadButton = true;
            pData->mShowNewButton = true;
            pData->mShowSaveButton = true;
            pData->mConfirmOnExit = false;
            pData->mShowPublishButton = true;
            pData->mAllowNaming = true;
            pData->mEditorValidationLevel[0] = kDefaultValidationLevel[0];
            pData->mEditorValidationLevel[1] = kDefaultValidationLevel[1];
            pData->mEditorValidationLevel[2] = kDefaultValidationLevel[2];
            pData->mEditorValidationLevel[3] = kDefaultValidationLevel[3];
            pData->mUsePlanetColors = true;
            pData->mUseSphere = true;
            pData->mPlanetColors.push_back(pSphere->mColors[0]);
            pData->mPlanetColors.push_back(pSphere->mColors[1]);
            pData->mPlanetColors.push_back(pSphere->mColors[2]);
            pData->mPlanetColors.push_back(pSphere->mColors[3]);
            pData->mPlanetColors.push_back(pSphere->mColors[4]);
            EditorManager()->LaunchEditor(pData);
            return true;
        }
    }

    if (messageID == 0x522f9cd) {
        EA::AutoRefCount_s00d1_30d0<cSwatch> pRollover(*(cSwatch**)pMessage);
        HandleSwatchRolloverOff(pRollover);
        return true;
    }
    if (messageID == 0x522f9ce) {
        EA::AutoRefCount_s00d1_30d0<cSwatch> pRollover(*(cSwatch**)pMessage);
        HandleSwatchRolloverOn(pRollover);
        return true;
    }

    switch (messageID) {
    case 0x44ef2b8: {
        int category = mpPaletteUI->FindCategoryIndex();
        if (mpRotationRing && mpPaletteUI) {
            GetCurrentGameMode();
            mpRotationRing->SetVisibility(category == 3);
        }
        UpdateLimitMeter(category);
        SetCameraTarget(*GetCommunityCenter(0));
        if (GetCurrentGameMode() == 0x1654c05)
            return false;
        if (!pCity)
            return false;
        if (category == 0) {
            NounManager_s00d1_30d0()->GetCurrentTerrainSphere()->ShowUIHint(0x566493f);
            if (sVehicleHintShown)
                return false;
            sVehicleHintShown = true;
            eastl::intrusive_ptr_s00d1_30d0<SlotMessage> pHint(new (kAppAllocName, 0, 0, 0, 0) SlotMessage(0));
            SlotMessage* pMsg = pHint.get();
            pMsg->mMessageID = 0x63c0580;
            pMsg->mSlot = -15;
            MessageServer_s00d1_30d0()->PostMessage(pMsg->mMessageID, pMsg, 0);
        } else if (category == 1) {
            NounManager_s00d1_30d0()->GetCurrentTerrainSphere()->ShowUIHint(0x566492c);
            if (GetCurrentGameMode() == 0x1654c05)
                return false;
            if (sBuildingHintShown)
                return false;
            sBuildingHintShown = true;
            eastl::intrusive_ptr_s00d1_30d0<SlotMessage> pHint(new (kAppAllocName, 0, 0, 0, 0) SlotMessage(0));
            SlotMessage* pMsg = pHint.get();
            pMsg->mMessageID = 0x63c0504;
            pMsg->mSlot = -15;
            MessageServer_s00d1_30d0()->PostMessage(pMsg->mMessageID, pMsg, 0);
        }
        return false;
    }

    case 0x5132389: {
        eastl::vector_s00d1_30d0<ResourceKey_s00d1_30d0>* pKeys = *(eastl::vector_s00d1_30d0<ResourceKey_s00d1_30d0>**)pMessage;
        EA::AutoRefCount_s00d1_30d0<IResource> pResource;
        if (!pKeys)
            return false;
        int count = pKeys->size();
        if (count > 0) {
            for (int i = 0; i < count; i++) {
                ResourceKey_s00d1_30d0 key = (*pKeys)[i];
                if (ResourceManager()->GetResource(key, pResource.AsPPTypeParam(), 0, 0, 0, 0)) {
                    cEditorResource_s00d1_30d0* pEditorResource = interface_cast_EditorResource(&pResource);
                    if (pEditorResource) {
                        pCity->GetCivilization()->CreateVehicleFromModelType(
                            pEditorResource->mModelType, key);
                        UpdateSwatchForModelType(pEditorResource->mModelType, key, 0);
                    }
                }
            }
        }
        return false;
    }

    case 0x63bdfbe:
        if (ConfigManager()->GetConfigValue(0x4ea96cb))
            ShowFirstTimeHint(kVehicleHintKey);
        return false;

    case 0x63c0504:
    case 0x63c0580:
        if (!sDecorHintShown) {
            sDecorHintShown = true;
            if (ConfigManager()->GetConfigValue(0x4ea96cb) > 0)
                ShowFirstTimeHint(kBuildingHintKey);
        }
        return false;

    case 0xb2e18705: {
        cSPPaletteItem_s00d1_30d0* pItem =
            interface_cast_PaletteItem(&((tPaletteItemMessage*)pMessage)->mItem);
        uint32_t modelType = GetModelType(pItem);

        switch (pItem->mItemType) {
        case 0x2b885df4: // city hall decoration set
            if (!pCity)
                return false;
            if (!pCity->GetCityHall())
                return false;
            pCity->GetCityHall()->SetCityID(pItem->mInstanceID);
            ((cCityHallBuildingSet*)pCity)->Refresh();
            return false;

        case 0xfcafd26: { // tribe tool
            if (!pTribe)
                return false;
            EA::AutoRefCount_s00d1_30d0<cPropertyList_s00d1_30d0> pProps;
            uint32_t toolType = 0;
            if (PropertyManager_s00d1_30d0()->GetPropertyList(pItem->mInstanceID, pItem->mGroupID,
                                                   pProps.AsPPTypeParam()) &&
                (GetPropertyAsUint32(pProps, 0x4294750, toolType), toolType)) {
                cTribeTool_s00d1_30d0* pOldTool = pTribe->GetToolOfType(toolType);
                cTribeTool_s00d1_30d0* pTool = pTribe->CreateTool(toolType);
                if (pTool) {
                    pTool->mFlags |= 8;
                    pObject = (cSpatialObject_s00d1_30d0*)&pTool->mSpatial;
                    bPlaced = true;
                    pTool->SetTribe(pTribe);
                    pTool->Prepare();
                    SetManipulatedObject(pObject);
                    pTool->mbIsBeingPlaced = true;
                    cursorID = 0x3e84;
                    cToolSnapSet* pSnapSet = &pTribe->mToolSnapSet;
                    if (pOldTool && pSnapSet) {
                        int slot = pSnapSet->FindSlotIndex(pOldTool->mSpatial.GetSnapLocator());
                        pSnapSet->mpSlots[slot].StartEffect();
                        pTribe->RemoveTool(pOldTool);
                    }
                }
            }
            break;
        }

        case 0x142462a: { // building
            if (!pCity)
                return false;
            cBuilding_s00d1_30d0* pBuilding = (cBuilding_s00d1_30d0*)pCity->CreateBuilding();
            if (!pBuilding)
                return false;
            pObject = &pBuilding->mSpatial;
            bSetCursor = true;
            pBuilding->mbIsBeingPlaced = true;
            if (pBuilding->GetModel())
                ((cBuildingModel*)pBuilding->GetModel())->SetRadius(pObject->SetScale(kToolScale));
            SetManipulatedObject(pObject);
            cursorID = 0x3e81;
            if (GetCurrentGameMode() == 0x1654c05) {
                cSpaceInventory* pInventory = SpaceGame()->GetInventory(0x12);
                pInventory->SetMode(8);
                pInventory->mpData->mValue =
                    GetHomeTerrainScore(GetActivePlanet()->mSurface.GetSurfaceData());
            }
            goto placed;
        }

        case 0x4d863c8b: { // decoration
            if (!pCity)
                return false;
            cDecoration* pDecor = (cDecoration*)NounManager_s00d1_30d0()->CreateNoun(0x18c88e4);
            if (!pDecor)
                return false;
            pObject = &pDecor->mSpatial;
            pDecor->SetModelProperty(0x2ae5ba7,
                                     pCity->GetCivilization()->GetModelTypeForItem(pItem->mInstanceID));
            pDecor->mbIsBeingPlaced = true;
            pCity->AddDecoration(pDecor);
            SetManipulatedObject(pObject);
            cursorID = 0x3e83;
            SetObjectSpecificData();
            goto placed;
        }

        case 0x8bfac054: { // vehicle
            if (!pCity)
                return false;
            if (modelType == (uint32_t)-1)
                return false;
            if (!pCity->GetCivilization()->CanAffordVehicle(pCity->GetVehicleSpecialty())) {
                MessageServer_s00d1_30d0()->MessageSend(0x2cb6a8f, 0, 0, 0);
                return false;
            }
            vehicleModelType = modelType;
            cVehicle_s00d1_30d0* pVehicle = CreateVehicle(modelType);
            if (!pVehicle)
                return false;
            pObject = &pVehicle->mSpatial;
            EA::AutoRefCount_s00d1_30d0<cPropertyList_s00d1_30d0> pProps;
            bool bSpawnAtPoint = false;
            uint32_t vehicleKind;
            bool bSpawn = bSpawnAtPoint;
            if (PropertyManager_s00d1_30d0()->GetPropertyList(pItem->mInstanceID, pItem->mGroupID,
                                                   pProps.AsPPTypeParam()) &&
                GetPropertyAsKeyInstance(pProps, 0x57fb25a, vehicleKind) &&
                vehicleKind == 0x5e71ab9b)
                bSpawn = true;
            SetManipulatedObject(pObject);
            if (!bSpawn) {
                cursorID = 0x3e85;
            } else {
                pObject->SetPosition(pCity->GetVehicleSpawnPoint(pVehicle->mLocomotion));
                pVehicle->SetSpeedBoost(10);
                bSetCursor = false;
            }
            UpdateVehicleList();
            {
                EA::AutoRefCount_s00d1_30d0<cVehicle_s00d1_30d0> pRef(pVehicle);
                mPlacedVehicles.push_back(pRef);
            }
            SetBeingPlaced(pVehicle, true);
            if (GetCurrentGameMode() == 0x1654c05) {
                pVehicle->SetJustEyeCandy(true);
                IBehaviorManager* pBehaviors = BehaviorManager();
                if (pBehaviors)
                    pBehaviors->Track(&pVehicle->mBehavior);
            } else {
                CivModeStrategy()->OnVehicleCreated(pVehicle);
                uint32_t eventID = 0x703af052;
                switch (pVehicle->mLocomotion) {
                case 0:
                    switch (pVehicle->mPurpose) {
                    case 1: eventID = 0xad067a5e; break;
                    case 2: eventID = 0xe7454134; break;
                    }
                    break;
                case 1:
                    CivModeStrategy()->DoNextCivTutorial(0x6d3814ed, 0);
                    switch (pVehicle->mPurpose) {
                    case 0: eventID = 0x300602f6; break;
                    case 1: eventID = 0x10d02b2a; break;
                    case 2: eventID = 0x8b3fcdf4; break;
                    }
                    break;
                case 2:
                    CivModeStrategy()->DoNextCivTutorial(0xced8b9d4, 0);
                    switch (pVehicle->mPurpose) {
                    case 0: eventID = 0xf5195d53; break;
                    case 1: eventID = 0x1181713f; break;
                    case 2: eventID = 0x1ca7441; break;
                    }
                    break;
                }
                PlayVehicleAudio(eventID,
                                 (char*)NounManager_s00d1_30d0()->GetPlayerCivilization()->GetCitizenAudio() +
                                     0x504,
                                 pObject->GetModelWorldPosition(), Vector3_s00d1_30d0(0.0f, 0.0f, 0.0f),
                                 NounManager_s00d1_30d0()->GetPlayerCivilization()->mData.GetPoliticalID(), 0, 0);
            }
            goto placed;
        }

        case 0x81c74dbc: { // creature / citizen
            if (!pCity)
                return false;
            uint32_t nounID = 0;
            EA::AutoRefCount_s00d1_30d0<cPropertyList_s00d1_30d0> pProps;
            if (PropertyManager_s00d1_30d0()->GetPropertyList(pItem->mInstanceID, pItem->mGroupID,
                                                   pProps.AsPPTypeParam()))
                GetPropertyAsKeyInstance(pProps, 0x456b66a, nounID);
            if (nounID && modelType != (uint32_t)-1) {
                cBuilding_s00d1_30d0* pNoun = (cBuilding_s00d1_30d0*)NounManager_s00d1_30d0()->CreateNoun(nounID);
                if (pNoun) {
                    bPlaced = true;
                    pObject = &pNoun->mSpatial;
                    pNoun->SetCity(pCity);
                    pNoun->mbIsBeingPlaced = true;
                    pObject->SetModelKey(pCity->GetCivilization()->GetModelTypeKey(modelType));
                    pCity->AddBuilding(pNoun, 0);
                    if (GetCurrentGameMode() == 0x1654c05) {
                        cSpaceInventory* pInventory = SpaceGame()->GetInventory(0x11);
                        pInventory->SetMode(8);
                        pInventory->mpData->mValue =
                            GetTerrainScore(GetActivePlanet()->mSurface.GetSurfaceData());
                        if (!GetActivePlanet()->IsHomeworld())
                            SpaceGame()->GetPlayerTribe(0)->SetGameDataOwner(1);
                    }
                    SetBeingPlaced(pNoun, true);
                    SetManipulatedObject(pObject);
                    cursorID = 0x3e82;
                }
            }
            break;
        }

        default:
            return false;
        }

        if (!bPlaced)
            return false;

    placed:
        mpWinBudget->SetFlag(0, -GetObjectCost(pObject, 0, vehicleModelType));
        PlayAudio(0x3d2f6e8e, GetAudioState_s00d1_30d0());
        if (bSetCursor)
            GameInputManager()->SetCursor(cursorID, 1);
        ClearRotationAnchor();
        mAnchorState = 0;
        SetObjectSpecificData();
        mSnapIndices[0] = -1;
        mSnapIndices[1] = -1;
        mSnapIndices[2] = -1;
        mSnapIndices[3] = -1;
        if (bSetCursor) {
            EA::AutoRefCount_s00d1_30d0<cVehicle_s00d1_30d0> pVehicle(AsVehicle(mpManipulatedObject));
            if (pVehicle) {
                int locomotion = pVehicle->mLocomotion;
                Vector3_s00d1_30d0 spawn = GetCity(mpCommunity)->GetVehicleSpawnPoint(locomotion);
                pVehicle->mSpatial.SetPosition(spawn);
                PlaceVehicle(pVehicle);
                return false;
            }
            if (mpManipulatedObject) {
                Vector3_s00d1_30d0 picked = CameraManager_s00d1_30d0()->Pick(1, mCursorScreenPos);
                Vector3_s00d1_30d0 surface = PlanetModel_s00d1_30d0()->ToSurface(picked);
                mpManipulatedObject->SetPosition(surface);
                mpManipulatedObject->SetOrientation(PlanetModel_s00d1_30d0()->GetSurfaceOrientation(
                    surface, mpManipulatedObject->GetOrientation()));
                UpdateSnapping();
                UpdatePlacementEffects();
            }
        } else {
            SetManipulatedObject(0);
            if (mpSellbackRollover)
                mpSellbackRollover->Hide();
        }
        return false;
    }
    }
    return false;
}
}  // namespace SP
