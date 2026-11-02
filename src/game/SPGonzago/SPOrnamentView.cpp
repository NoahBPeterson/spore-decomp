// src/game/SPGonzago/SPOrnamentView.cpp -- migrated from slice(s) s00e8ffa0, s00e8f0b0, s00e8e0d0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPOrnamentView.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cGameDataView.h"
#include "SP/cModelInstance.h"
#include "SP/cSpatialObject.h"
#include <math.h>
#include <string.h>
#include "SP/cCommodityNode.h"
#include "SP/cGameNounManager.h"
#include "SP/cPlanetModel.h"
#include <float.h>
#define __PLACEMENT_NEW_INLINE   // the slices' own placement new/delete win over <new>'s (rewrite.py)
#include <new>
inline void operator delete(void*, void*) {}   // placement delete (<new>'s is skipped, rewrite.py)

// ---- items of slice s00e8e0d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
inline void* operator new(unsigned int, void* p) throw() { return p; }
void* __cdecl operator_new(unsigned size, const char* file, int a, int b, int c, int d);  // 0xf473a0
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float fx, float fy, float fz) : x(fx), y(fy), z(fz) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct cSPTransform_s00e8_e0d0;
struct IRefCounted {
    virtual void v00();
    virtual void Release();                // +0x04
};
template <class T> struct AutoRef {
    T* mpObject;
    AutoRef() : mpObject(0) {}
    ~AutoRef() { if (mpObject) mpObject->Release(); }
    void Reset()
    {
        if (mpObject) {
            T* const pOld = mpObject;
            mpObject = 0;
            pOld->Release();
        }
    }
};
struct cSPUIMeter : IRefCounted {
    void Shutdown(bool immediate);         // 0xe06940
};
struct cModelKey {
    uint32_t mType;                        // +0x00
    uint32_t mGroup;                       // +0x04
    uint32_t mInstance;                    // +0x08
};
struct cGonzagoModel {                     // model attachment at +0x34 of a sim object
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
    virtual bool IsReady();                         // +0x90
    virtual uint32_t v94();
    virtual Vector3* GetModelWorld(const char* name);   // +0x98
virtual void v9c();
virtual void va0();
    virtual void RefreshModelWorld();                // +0xa4
    virtual void* GetModel();                        // +0xac
};
struct cSelection {                        // selection helper embedded at +0x70
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
    virtual const Vector3& GetPosition();            // +0x2c
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
    virtual void SetHighlightRadius(float radius);   // +0x70
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
    virtual void* GetHighlightObject();              // +0xac
};
struct cModelInstance {                    // renderable instance a view owns
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
    void SetTransform(const cSPTransform_s00e8_e0d0& transform);    // render transform lives at +8
    uint32_t mDrawFlags[8];                // +0x44 bit array (32..63)
};
struct cSimulatorObject {                  // the simulation side a view drives
virtual void v00();
virtual void v04();
virtual void v08();
    virtual cSimulatorObject* GetObjectById(uint32_t id);   // +0x0c
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual uint32_t GetId();                                // +0x20
virtual void v24();
virtual void v28();
virtual void v2c();
    virtual void v30();

    uint8_t pad04[0x34 - 0x04];
    cGonzagoModel mModel;                  // +0x34
    uint8_t pad34[0x70 - (0x34 + sizeof(cGonzagoModel))];
    cSelection mSelection;                 // +0x70
    uint8_t pad70[0x84 - (0x70 + sizeof(cSelection))];
    uint32_t mFlags;                       // +0x84
    uint8_t pad88[0xa9 - 0x88];
    bool mbReady;                          // +0xa9
    uint8_t padAA[0xdf - 0xaa];
    bool mbHighlighted;                    // +0xdf
    uint8_t padE0[0x108 - 0xe0];
    int mState;                            // +0x108
    int mLevel;                            // +0x110
    uint8_t pad114[0x120 - 0x114];
    bool mbModelDirty;                     // +0x120
    uint8_t pad121[0x1e8 - 0x121];
    int mEffectKind;                       // +0x1e8
    bool mbEffectPending;                  // +0x1ec
    uint8_t pad1ED[0x1f4 - 0x1ed];
    void* mpToolData;                      // +0x1f4
    uint8_t pad1F8[0x220 - 0x1f8];
    float mEffectScale;                    // +0x220
    uint8_t pad224[0x238 - 0x224];
    float mHighlightMin;                   // +0x238
    float mHighlightGrow;                  // +0x23c
    float mHighlightShrink;                // +0x240
    float mHighlightNear;                  // +0x244
    float mHighlightFar;                   // +0x248

    void SetupNestModelKey();              // 0xe8df50
    void ShowTooltip(bool canMine, void* a);   // 0xc3f8b0
};
struct cSpatialObject {                    // the game side a view is attached to
virtual void v00();
virtual void v04();
virtual void v08();
    virtual cSimulatorObject* GetSimObject(uint32_t id);     // +0x0c
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual uint32_t GetId();                                // +0x20
    virtual bool IsHighlighted();                            // +0x24
    virtual void v28();
    virtual const Vector3& GetPosition();                    // +0x2c
    virtual const void* GetOrientation();                    // +0x30
    virtual float GetScale();                                // +0x34
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
    virtual int GetKind();                                   // +0x60
virtual void v64();
virtual void v68();
virtual void v6c();
    virtual uint32_t GetModelKeyId();                        // +0x70
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
    virtual void* GetHighlightedModel();                     // +0xac
virtual void vb0();
virtual void vb4();
    virtual cSimulatorObject* GetInteractableObject(uint32_t id);    // +0xb8

    bool mIsSelected;                      // +0x2c? (scene flags live after the vftable)
};
struct cSPTransform_s00e8_e0d0 {                      // render transform handed to an effect
    uint16_t mMask;                        // +0x00
    uint16_t mOrientationMask;             // +0x02
    Vector3 mPosition;                     // +0x04
    Vector3 mOrientation;                  // +0x10
    float mScale;                          // +0x1c
    float mBasis[9];                       // +0x20 (optional 3x3 basis)
};
struct cGameDataView {
    virtual void v00();                    // +0x00
    virtual void Release();                // +0x04
    virtual void v08();                    // +0x08
    virtual cSpatialObject* GetOwner();    // +0x0c
    virtual void SetVisible(int visible);  // +0x10
    virtual void v14();                    // +0x14
    virtual void SetActive(int active);    // +0x18
    virtual void v1c();                    // +0x1c
    virtual void v20();                    // +0x20
    virtual void AttachObject(cSpatialObject* pObject);      // +0x24
    virtual void SetModel(void* pObject, void* pModelWorld);            // +0x28
    virtual cModelInstance* GetModel();                      // +0x2c
    virtual void v30();                    // +0x30
    virtual float GetLevel();              // +0x34
};
struct cSpatialObjectView : cGameDataView {
    void* mpPrev;                          // +0x04
    void* mpNext;                          // +0x08
    cSpatialObject* mpObject;              // +0x0c (AutoRef)
    IRefCounted* mpObjectCombatant;        // +0x10 (AutoRef)
    bool mbSelected;                       // +0x14
    uint8_t pad15[3];
    Vector3 mColor;                        // +0x18
    cModelKey mKey;                        // +0x24
    bool mbFlag30;                         // +0x30
    bool mbFlag31;                         // +0x31
    bool mbFlag32;                         // +0x32

    cSpatialObjectView();
    virtual ~cSpatialObjectView();
    virtual void HandleSimulationUpdate(void* a, void* b);   // 0xe92ca0
    void StartEffect(float scale, int a);                    // 0xc88f??
};
struct cTotemPoleView : cSpatialObjectView {
    bool mbFlag34;                         // +0x34
    cTotemPoleView() : mbFlag34(false) {}
};
struct cOrnamentView : cSpatialObjectView {
    virtual ~cOrnamentView();               // 0xe8eaa0
};
struct cMineralView : cSpatialObjectView {
    uint32_t mField34;                     // +0x34
    bool mbLoadingModel;                   // +0x38
    bool mbAnimationsStarted;              // +0x39
    bool mbEffectsInLOD;                   // +0x3a
    bool mbField3b;                        // +0x3b
    AutoRef<cSPUIMeter> mProgressMeter;    // +0x3c
    AutoRef<cSPUIMeter> mGeyserMeter;      // +0x40
    AutoRef<cSPUIMeter> mPumpMeter;        // +0x44

    cMineralView();
    virtual ~cMineralView();                                            // 0xe8f000
    void OnMouseDown(void* a, void* b);                                 // 0xe8ec30
    void UpdateMiningTooltip(void* a);                                  // 0xe8ef10
};
void* __cdecl GonzagoModelWorld(void* pModel);                                    // 0xb3d520
void* __cdecl GetToolData(uint32_t id);                                           // 0xd37cb0
IRefCounted* __cdecl GetToolByKey(uint32_t key);                                  // 0xb6fa60
void* __cdecl Viewer();                                                           // App()->vtbl+0x58
void __cdecl GetCameraLocation(void* a, float* pOut);                             // 0x7c3d30
extern uint32_t gNestModelName;          // 0x015a88a8
// ---- items of slice s00e8e0d0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern uint32_t gNestModelName;          // 0x015a88a8

// ---- items of slice s00e8f0b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void FUN_00e8ef10();
extern "C" void FUN_00c90460();
extern void* gPropertyManager;      // 0x0158128c
extern const float kOrnamentMinScale;   // 0x01473c70
extern const float kOrnamentMaxScale;   // 0x013eecd8
typedef unsigned char      u8;
typedef unsigned int       u32;
#define VS(o, off)              (*(void**)(*(char**)(o) + (off)))
#define VC0(R, o, off)          ((R (__thiscall*)(void*))VS(o, off))((void*)(o))
#define VC1(R, o, off, T1, a1)  ((R (__thiscall*)(void*, T1))VS(o, off))((void*)(o), (a1))
typedef void (__thiscall *Fn00e8ef10)(void* self, int flag);                      // 0x00e8ef10
typedef void* (__thiscall *Fn00c90460)(void* self);                               // 0x00c90460
void* FUN_00ac8730(void* handle);                                                 // 0x00ac8730
void* FUN_00d08d70();                                                             // 0x00d08d70
const u32 kKeyAnimalTrapView   = 0x061494bd;
const u32 kKeyTribeFoodMatView = 0x0629baec;
const u32 kKeyOrnamentView     = 0x0175cdc9;
const u32 kKeyInteractable     = 0x03a25119;
const u32 kKeyTotemPoleView    = 0x055cf8e3;
struct Vec3 { float x, y, z; };
struct ModelKey {
    u32 mName;   // +0x00
    u32 mSub;    // +0x04
    u32 mKind;   // +0x08
};
struct cSpatialObjectSub {
    char  pad_00[0x18];
    Vec3  mModelPos18;      // +0x18: model-world position passed to the view Init
    char  pad_24[0x34 - 0x24];
    void* mpCallback1;      // +0x34: object used by the vt[0x94]/[0xa4]/[0x98] callbacks
    char  pad_38[0x38];
    void* mpSub70;          // +0x70: the hit-sphere/interaction sub-object
    char  pad_74[0x94];
    void** mpVectorBegin;   // +0x108: pointer vector begin
    void** mpVectorEnd;     // +0x10c: pointer vector end
    char  pad_110[0x118];
    int   mKey;             // +0x228: ornament model-key selector (== cSpatialObject::mKey)
    int   mSubKey;          // +0x22c
};
struct cInteractionSub {
    char  pad_00[8];
    void* mpModel;          // +0x08
};
struct cSubVectorElem {
    void* mpThis;           // +0x00: object whose vftable holds the slot being called
    u32   mFlags;           // +0x04: bit 0 = visible, bit 15 = in-world
};
struct cSpatialObjectFlag {
    char pad_00[0x108];
    u8   mbFlag;            // +0x108
};
struct cSpatialObject_s00e8_f0b0 {
    char pad00[0x228];
    int  mKey;           // +0x228: the ornament model key selector
    int  mSubKey;        // +0x22c: sub-key / model override, when non-zero
    char pad230[0x38 - 0x2c];
    int  mField38;       // +0x38
    int  mField3c;       // +0x3c
    int  mField40;       // +0x40
    int  mField44;       // +0x44
    char pad48[0x2c0 - 0x48];
    float mModelScale;   // +0x2c0
};
class cSpatialObjectView_s00e8_f0b0 {
public:
    virtual void  SetIsInWorld(bool b);           // +0x00  0x00e92620
    virtual u8    GetIsInWorld();                 // +0x04  0x00e92c60
    virtual void  SetIsVisible(bool b);           // +0x08  0x00e889f0
    virtual u8    GetIsVisible();                 // +0x0c  0x00e92c80
    virtual void  SetClassFlag(u8 b);             // +0x10
    virtual u8    GetClassFlag();                 // +0x14
    virtual void  v18();
    virtual void* v1c();
    virtual void  v20();
    virtual void  Init(void* g);                  // +0x24 0x00e92910
    virtual void  Init(void* a, void* w);         // +0x28 0x00e92910
    virtual void* GetModel();                     // +0x2c
    virtual void* GetTransform();                 // +0x30

    void  HandleSimulationUpdate(int a, int b);   // non-virtual, 0x00e92ca0

    // 0x00e8eb90 (thiscall; ecx = the creating view, arg1 = the QI result, arg2 = the key buffer)
    bool BuildSubKey(void* sub, ModelKey* out);

    cSpatialObjectView_s00e8_f0b0();                         // 0x00e92af0

    u32   mField04;                               // +0x04
    u32   mField08;                               // +0x08
    void* mpObject;                               // +0x0c
    void* mpObjectCombatant;                      // +0x10
    u8    mField14;                               // +0x14
    char  pad_15[3];
    Vec3  mModelPos;                              // +0x18
    Vec3  mModelRot;                              // +0x24
    u8    mField30;                               // +0x30
    u8    mField31;                               // +0x31
    u8    mField32;                               // +0x32
    char  pad_33[1];
};
class cMineralView_s00e8_f0b0 : public cSpatialObjectView_s00e8_f0b0 {
public:
    int   mAnimId;              // +0x34
    u8    mbLoadingModel;       // +0x38
    u8    mbAnimationsStarted;  // +0x39
    u8    mbEffectsInLOD;       // +0x3a
    char  pad_3b[1];
    u32   mField3c;             // +0x3c
    u32   mField40;             // +0x40
    u32   mField44;             // +0x44

    cMineralView_s00e8_f0b0* MakeView(void* gameData);       // 0x00e8f0b0
    void Update(void* a, void* b);                // 0x00e8f490
};
class cTotemPoleView_s00e8_f0b0 : public cSpatialObjectView_s00e8_f0b0 {
public:
    u8 mField34;                // +0x34

    void SetIsInWorld(bool b);                    // 0x00e8f1f0
    u8   GetIsInWorld();                          // 0x00e8f260
    void SetIsVisible(bool b);                    // 0x00e8f2d0
    u8   GetIsVisible();                          // 0x00e8f330
};
class cTribeFoodMatView : public cSpatialObjectView_s00e8_f0b0 {
public:
    cTribeFoodMatView* MakeView(void* gameData);  // 0x00e8f5e0
    bool BuildKey(cTribeFoodMatView* self, ModelKey* out);   // 0x00e8f550
    void Update(void* a, void* b);                // 0x00e8f6b0
};
class cOrnamentView_s00e8_f0b0 : public cSpatialObjectView_s00e8_f0b0 {
public:
    cOrnamentView_s00e8_f0b0* MakeView(void* gameData);      // 0x00e8fa00
    void Update(void* a, void* b);                // 0x00e8fae0
};
class cInteractableObjectView : public cSpatialObjectView_s00e8_f0b0 {
public:
    cInteractableObjectView* MakeView(void* gameData);   // 0x00e8fe80
    void Update(void* a, void* b);                // 0x00e8ff10
};
extern u32 gOrnamentKeyCounter;     // 0x016c53a0
float GetPropertyFloat(void* mgr, u32 key, float def);
bool ResourceMan_NotEqual(void* key, void* handle);
struct cSPUIMeter_e8f0 {
  void* Init(unsigned a, unsigned b, unsigned c, const wchar_t* name, unsigned d);  // 0x00e06a10 thiscall, ret 0x14, returns this
  void  Shutdown(int flag);       // 0x00e06940 SP::cSPUIMeter::Shutdown, thiscall
  void  Func_e06ca0(unsigned v);  // 0x00e06ca0 thiscall, ret 4
  void  Func_e06cf0(void* obj);   // 0x00e06cf0 thiscall, ret 4
};
struct cMineralView_e8f0 {
  uint32_t pad[3];                // base cSpatialObjectView header up to +0xc
  void*    mpObject;              // +0x0c  EA::AutoRefCount<cSpatialObject> (raw pointer)

  cSPUIMeter_e8f0* UpdateLoyaltyBar(cSPUIMeter_e8f0* p, char bShow, unsigned hdr);  // 0x00e8f120
};
// ---- items of slice s00e8f0b0 end

// ---- items of slice s00e8ffa0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned short     u16;
#define VC5(R, o, off, T1, a1, T2, a2, T3, a3, T4, a4, T5, a5) \
    ((R (__thiscall*)(void*, T1, T2, T3, T4, T5))VS(o, off))((void*)(o), (a1), (a2), (a3), (a4), (a5))
struct XformMsg {
    u16   flags;      // +0x00  |2 = rotation, |4 = position
    u16   count;      // +0x02
    float pos[3];     // +0x04
    float scale;      // +0x10
    float rot[9];     // +0x14
    XformMsg();                           // 0x00434040
    void Combine(const void* src);        // 0x0040ccb0
};
struct cSpatialObject_s00e8_ffa0 {
    bool  GetEffect(int id);                          // 0x00c88910
    void* FindEffect(int id);                         // 0x00c888e0
    void  SetEffectParam(int id, float f);            // 0x00c88a00
    void  SetEffectPos(int id, void* p);              // 0x00c88a30
    void  KillEffect(int id, int flag);               // 0x00c8ad30
    void  CreateEffect(int effId, int p3, int id);    // 0x00c8b130
    void  CreateEffectB(int effId, int p3, int id);   // 0x00c8b1b0
    void  sub_a020(int id, float f);                  // 0x00c8a020
};
struct cPlanetModel_s00e8_ffa0 {
    char  pad[0x64];
    u8*   mpTable;                                    // +0x64 per-cell flag table
    bool  sub_b7e3e0(const Vec3* pos);                // 0x00b7e3e0 (thiscall, ret 4)
    int   GetContinent(const Vec3* pos);              // 0x00b88590 (thiscall, ret 4): cell index
    void* BuildSurfaceOrientation(void* out, const Vec3* pos);   // 0x00b7f190 (ret 8)
};
struct cFxRecord {
    u32   pad0;
    u32   mFlags;       // +0x04
    char  pad1[0x4c - 8];
    float mColor[3];    // +0x4c
};
struct cCommodityNode_s00e8_ffa0 {
    cFxRecord* GetFxRecord();     // 0x009600f0: returns field at +0x1dc
    float      GetResourceFraction();   // 0x00bfdea0: fld [ecx+0x1d0]; fdiv [ecx+0x1d4]
    bool       sub_bfe0c0();      // 0x00bfe0c0
};
struct cGameNounManager_s00e8_ffa0 {
    char* GetObject(int id);                          // 0x00b25f40 (thiscall, ret 4)
    void* GetObjectByKey(const void* key);            // 0x00b262c0 (thiscall, ret 4)
};
struct cSPUIMeter_e8ff {};   // vtbl slot 0 = AddRef, slot 1 = Release
int                GetCurrentGameMode();               // 0x00b5b800
cPlanetModel_s00e8_ffa0*      PlanetModel();                      // 0x00b3d350
cGameNounManager_s00e8_ffa0*  NounManager();                      // 0x00b3d300
void*              GetUniverseGlobal();                // 0x00b3d460
void*              GonzagoModelWorld();                // 0x00b3d520
char*              GetActivePlanet();                  // 0x01021260
u32                SPIDFromName(const char* name);     // 0x00571cf0
float*             Matrix3FromQuaternion(float* out, void* q);   // 0x0059c190
bool               Vector3_NotEqual(const Vec3* a, const Vec3* b);   // 0x0041dd30
extern const u32   kGeyserEffectIds[];                 // 0x014868b0
namespace SP {
class cMineralView_s00e8_ffa0 {
public:
    void** mVTable;                                   // +0x00
    char   pad0[8];
    cSpatialObject_s00e8_ffa0* mpObject;                         // +0x0c
    char   pad1[0x18 - 0x10];
    Vec3   mColor;                                    // +0x18
    char   pad2[0x34 - 0x24];
    int    mEffectMode;                               // +0x34
    u8     mShieldFxOn;                               // +0x38
    char   mLastFlag;                               // +0x39
    u8     mHotSpotFxOn;                              // +0x3a
    char   pad3;
    cSPUIMeter_e8ff* mpConstructionMeter;             // +0x3c
    cSPUIMeter_e8ff* mpCulturalMeter;                 // +0x40
    cSPUIMeter_e8ff* mpMilitaryMeter;                 // +0x44

    void HandleSimulationUpdate(int a, int b);        // 0x00e8ffa0
    void HandleSimulationUpdateBase(int a, int b);    // 0x00e92ca0 (cSpatialObjectView)
    cSPUIMeter_e8ff* UpdateLoyaltyBar(cSPUIMeter_e8ff* p, char bShow, unsigned hdr);   // 0x00e8f120
};  // namespace SP
}
#define FU8(p, off)   (*(u8*)((char*)(p) + (off)))
#define FI32(p, off)  (*(int*)((char*)(p) + (off)))
#define FU32(p, off)  (*(u32*)((char*)(p) + (off)))
#define FF32(p, off)  (*(float*)((char*)(p) + (off)))
static inline void AssignMeter(cSPUIMeter_e8ff*& dst, cSPUIMeter_e8ff* src)
{
    cSPUIMeter_e8ff* old = dst;
    if (src != old) {
        if (src) VC0(void, src, 0);
        dst = src;
        if (old) VC0(void, old, 4);
    }
}
static __forceinline void MakeColor(Vec3* out)
{
    GetUniverseGlobal();
    u32 c = *(u32*)(GetActivePlanet() + 0x1c4);
    out->x = (float)(int)(u8)(c >> 16) * 0.003921569f;
    out->y = (float)(int)(u8)(c >> 8) * 0.003921569f;
    out->z = (float)(int)(u8)c * 0.003921569f;
}
namespace SP {
class cSpatialObjectView_s00e8_ffa0 {
public:
    void** mVTable;                    // +0x00
    void*  mpPrev;                     // +0x04
    void*  mpNext;                     // +0x08
    void*  mpObject;                   // +0x0c
    void*  mpObjectCombatant;          // +0x10
    u8     mField14;                   // +0x14
    u8     mPad15[3];
    Vec3   mColor;                     // +0x18
    u32    mKeyType;                   // +0x24
    u32    mKeyGroup;                  // +0x28
    u32    mKeyInstance;               // +0x2c
    u8     mField30;                   // +0x30
    u8     mField31;                   // +0x31
    u8     mField32;                   // +0x32
    u8     mPad33;                     // +0x33

    void BaseCtor();                   // 0x00e92af0
    void HandleSimulationUpdate(int a, int b);   // 0x00e92ca0
};
}
namespace SP {
class cTotemPoleView_s00e8_ffa0 : public cSpatialObjectView_s00e8_ffa0 {
public:
    u8 mField34;                       // +0x34 (retail size 0x38)

    void HandleSimulationUpdate_90820(int a, int b);
};
}
using SP::cSpatialObjectView_s00e8_ffa0;
using SP::cTotemPoleView_s00e8_ffa0;
struct cTotemPoleSpatial {
    void** mVTable;                    // +0x00 (subobject at node + 0x34)
    char   mPad04[0x70];
    u8     mbFlagA8;                   // +0x74 == node + 0xa8
    char   mPad75[3];
};
struct cTotemPoleNode {
    void** mVTable;                    // +0x00
    char   mPad04[0x30];
    cTotemPoleSpatial mSpatial;        // +0x34
    char   mPadAC[0x108 - 0xac];
    void** mpSegmentsBegin;            // +0x108
    void** mpSegmentsEnd;              // +0x10c
    char   mPad110[0x148 - 0x110];
    u8     mbVisible;                  // +0x148
};
struct cTotemTransform {
    u8 mData[0x70];
    bool NotEqual(const void* other) const;   // 0x00537dc0
};
struct cTotemModel {
    char  mPad00[8];
    cTotemTransform mTransform;        // +0x08
    float mBaseScale;                  // +0x78
    char  mPad7C[0x84 - 0x7c];
    float mScale;                      // +0x84
};
struct cTotemSegment {
    void* mVTable;                     // +0x00
    u32   mFlags;                      // +0x04
    cTotemTransform mTransform;        // +0x08
    float mBaseScale;                  // +0x78
    char  mPad7C[0x84 - 0x7c];
    float mScale;                      // +0x84
};
static inline void* VCall0(void* obj, unsigned off)
{
    return ((void* (__thiscall*)(void*))((void**)(*(void***)obj))[off / 4])(obj);
}
static inline void* VCall1(void* obj, unsigned off, void* a)
{
    return ((void* (__thiscall*)(void*, void*))((void**)(*(void***)obj))[off / 4])(obj, a);
}
static inline float VCallFloat0(void* obj, unsigned off)
{
    return ((float (__thiscall*)(void*))((void**)(*(void***)obj))[off / 4])(obj);
}
static inline u8 VCallBool0(void* obj, unsigned off)
{
    return ((u8 (__thiscall*)(void*))((void**)(*(void***)obj))[off / 4])(obj);
}
static inline void VCallVoid1(void* obj, unsigned off, void* a)
{
    ((void (__thiscall*)(void*, void*))((void**)(*(void***)obj))[off / 4])(obj, a);
}
static inline void VCallVoidByte(void* obj, unsigned off, u8 a)
{
    ((void (__thiscall*)(void*, u8))((void**)(*(void***)obj))[off / 4])(obj, a);
}
// ---- items of slice s00e8ffa0 end

// @ 0x00e8eaa0
cOrnamentView::~cOrnamentView()
{
}

// @ 0x00e8eaf0
cTotemPoleView* __cdecl CreateTotemPoleView(cSimulatorObject* pOwner)
{
    cTotemPoleView* pView = 0;
    if (pOwner && pOwner->GetId() == 0x55cf865) {
        pView = (cTotemPoleView*)operator_new(sizeof(cTotemPoleView), "Simulator/cTotemPoleView", 0, 0, 0, 0);
        if (pView)
            new (pView) cTotemPoleView();
        void* const pModelWorld = GonzagoModelWorld(pOwner->mModel.GetModelWorld((const char*)&gNestModelName));
        pView->SetModel(pOwner, pModelWorld);
    }
    return pView;
}

// @ 0x00e8eb90
bool __stdcall GetOrnamentModelKey(const cSimulatorObject* pObject, cModelKey* pOutKey)
{
    cModelKey key;
    switch (pObject->mState) {
    case 0:
        key.mType = 0x1e42e0c6;
        break;
    case 1:
    case 2:
    case 3:
    case 4:
        key.mType = 0x1e42e0c5;
        break;
    case 5:
        key.mType = 0;
        key.mGroup = 0;
        key.mInstance = 0;
        *pOutKey = key;
        return true;
    default:
        return false;
    }
    key.mGroup = 0;
    key.mInstance = 0xf37c24e6;
    *pOutKey = key;
    return true;
}

// @ 0x00e8ec30
void __thiscall cMineralView::OnMouseDown(void* a, void* b)
{
    cSpatialObjectView::HandleSimulationUpdate(a, b);

    cSpatialObject* const pOwner = mpObject;
    if (!pOwner)
        return;

    cSimulatorObject* const pTarget = pOwner->GetInteractableObject(0x2e71a5a);
    if (!pTarget || !pTarget->mSelection.GetHighlightObject())
        return;

    const Vector3& highlightPos = pTarget->mSelection.GetPosition();
    float camPos[4];
    GetCameraLocation(Viewer(), camPos);

    const float dx = camPos[0] - highlightPos.x;
    const float dy = camPos[1] - highlightPos.y;
    const float dz = camPos[2] - highlightPos.z;
    const float distance = (float)sqrt(dx * dx + dy * dy + dz * dz);

    const float grown = pTarget->mHighlightGrow * distance;
    const float shrunk = distance * pTarget->mHighlightShrink;
    float radius = pTarget->mHighlightMin;
    if (radius < grown)
        radius = grown;
    if (shrunk <= radius)
        radius = shrunk;

    pTarget->mSelection.SetHighlightRadius(radius);
    pTarget->mbHighlighted = pTarget->mHighlightNear <= distance && distance < pTarget->mHighlightFar;
}

// @ 0x00e8ef10
void __thiscall cMineralView::UpdateMiningTooltip(void* a)
{
    if (!mpObject)
        return;

    cSimulatorObject* const pObject = mpObject->GetInteractableObject(0x398420d);
    if (!pObject)
        return;

    const int level = pObject->mLevel;
    bool canMine = false;
    if ((pObject->mFlags & 0x100) == 0 && GetToolData(0) != 0 && level == 4) {
        IRefCounted* const pToolA = GetToolByKey(0x4ad11866);
        IRefCounted* const pToolB = GetToolByKey(0x8d61d137);
        if (pToolA || pToolB)
            canMine = true;
    }

    pObject->ShowTooltip(canMine, a);
    (void)a;
}

// @ 0x00e8efd0
cMineralView::cMineralView()
: mField34(0), mbLoadingModel(false), mbAnimationsStarted(false),
      mbEffectsInLOD(false)
{
}

// @ 0x00e8f000
cMineralView::~cMineralView()
{
    if (mProgressMeter.mpObject) {
        mProgressMeter.mpObject->Shutdown(true);
        mProgressMeter.Reset();
    }
    if (mGeyserMeter.mpObject) {
        mGeyserMeter.mpObject->Shutdown(true);
        mGeyserMeter.Reset();
    }
    if (mPumpMeter.mpObject) {
        mPumpMeter.mpObject->Shutdown(true);
        mPumpMeter.Reset();
    }
}

// @ 0x00e8f120
cSPUIMeter_e8f0* cMineralView_e8f0::UpdateLoyaltyBar(cSPUIMeter_e8f0* p, char bShow, unsigned hdr)
{
  if (bShow != 0) {
    unsigned v;
    if (mpObject) {
      void* obj = mpObject;
      v = ((unsigned (__thiscall*)(void*, unsigned))((*(void***)obj)[46]))(obj, 0x403df5f);
    } else {
      v = 0;
    }
    if (p == 0) {
      cSPUIMeter_e8f0* np;
      void* mem = operator_new(0x50, (const char*)0x013f6b3c, 0, 0, 0, 0);
      if (mem) {
        np = (cSPUIMeter_e8f0*)((cSPUIMeter_e8f0*)mem)->Init(hdr, 0x3ffb28c, 0x4d428c1, L"CivConversionBar", 0xe9f70df9);
      } else {
        np = 0;
      }
      np->Func_e06ca0(v);
      np->Func_e06cf0(mpObject);
      return np;
    }
    return p;
  }
  if (p) { p->Shutdown(1); p = 0; }
  return p;
}

// @ 0x00e8f1f0
void cTotemPoleView_s00e8_f0b0::SetIsInWorld(bool b)
{
    cSpatialObjectView_s00e8_f0b0::SetIsInWorld(b);
    void* obj = mpObject;
    if (obj == 0)
        return;
    void* sub = (void*)VC1(void*, obj, 0xb8, u32, kKeyTotemPoleView);
    if (sub == 0)
        return;
    cSpatialObjectSub* vec = (cSpatialObjectSub*)sub;
    cSubVectorElem** begin = (cSubVectorElem**)vec->mpVectorBegin;
    cSubVectorElem** end   = (cSubVectorElem**)vec->mpVectorEnd;
    for (; begin != end; ++begin) {
        cSubVectorElem* o = *begin;
        if (o != 0) {
            void* self = o->mpThis;
            void** vtbl = *(void***)self;
            ((void (__thiscall*)(void*, cSubVectorElem*, bool))vtbl[0x16c / 4])(self, o, b);
        }
    }
}

// @ 0x00e8f260
u8 cTotemPoleView_s00e8_f0b0::GetIsInWorld()
{
    u8 r = cSpatialObjectView_s00e8_f0b0::GetIsInWorld();
    if (r == 0) {
        void* obj = mpObject;
        if (obj != 0) {
            void* sub = (void*)VC1(void*, obj, 0xb8, u32, kKeyTotemPoleView);
            if (sub != 0) {
                cSpatialObjectSub* vec = (cSpatialObjectSub*)sub;
                cSubVectorElem** begin = (cSubVectorElem**)vec->mpVectorBegin;
                cSubVectorElem** end   = (cSubVectorElem**)vec->mpVectorEnd;
                for (; begin != end; ++begin) {
                    cSubVectorElem* o = *begin;
                    if (o != 0) {
                        u8 bit = (u8)(o->mFlags >> 0xf);
                        if ((bit & 1) != 0)
                            return 1;
                    }
                }
            }
        }
    }
    return r;
}

// @ 0x00e8f2d0
void cTotemPoleView_s00e8_f0b0::SetIsVisible(bool b)
{
    cSpatialObjectView_s00e8_f0b0::SetIsVisible(b);
    void* obj = mpObject;
    if (obj == 0)
        return;
    void* sub = (void*)VC1(void*, obj, 0xb8, u32, kKeyTotemPoleView);
    if (sub == 0)
        return;
    cSpatialObjectSub* vec = (cSpatialObjectSub*)sub;
    cSubVectorElem** begin = (cSubVectorElem**)vec->mpVectorBegin;
    cSubVectorElem** end   = (cSubVectorElem**)vec->mpVectorEnd;
    if (begin == end)
        return;
    for (; begin != end; ++begin) {
        cSubVectorElem* o = *begin;
        if (o != 0) {
            if (b)
                o->mFlags |= 1;
            else
                o->mFlags &= 0xfffffffe;
        }
    }
}

// @ 0x00e8f330
u8 cTotemPoleView_s00e8_f0b0::GetIsVisible()
{
    u8 r = cSpatialObjectView_s00e8_f0b0::GetIsVisible();
    if (r == 0) {
        void* obj = mpObject;
        if (obj != 0) {
            void* sub = (void*)VC1(void*, obj, 0xb8, u32, kKeyTotemPoleView);
            if (sub != 0) {
                cSpatialObjectSub* vec = (cSpatialObjectSub*)sub;
                cSubVectorElem** begin = (cSubVectorElem**)vec->mpVectorBegin;
                cSubVectorElem** end   = (cSubVectorElem**)vec->mpVectorEnd;
                if (begin != end) {
                    for (; begin != end; ++begin) {
                        cSubVectorElem* o = *begin;
                        if (o != 0 && (o->mFlags & 1) != 0)
                            return 1;
                    }
                }
            }
        }
    }
    return r;
}

// @ 0x00e8f490
void cMineralView_s00e8_f0b0::Update(void* a, void* b)
{
    HandleSimulationUpdate((int)a, (int)b);
    void* obj = mpObject;
    if (obj == 0)
        return;
    void* sub = (void*)VC1(void*, obj, 0xb8, u32, kKeyAnimalTrapView);
    if (sub == 0)
        return;
    ModelKey key = { 0, 0, 0 };
    if (!((cSpatialObjectView_s00e8_f0b0*)this)->BuildSubKey(sub, &key))
        return;
    void* inner = &((cSpatialObjectSub*)sub)->mpCallback1;
    if (key.mName != 0)
        VC1(void, inner, 0x94, void*, &key);
    else
        VC0(void, inner, 0xa4);
}

// @ 0x00e8f550
bool cTribeFoodMatView::BuildKey(cTribeFoodMatView* self, ModelKey* out)
{
    cSpatialObjectSub* obj = (cSpatialObjectSub*)self;
    out->mKind = 0xc279c707;
    out->mName = 0xb5efedbb;
    void* vecEnd = obj->mpVectorEnd;
    if (!((Fn00c90460)&FUN_00c90460)(vecEnd))
        return true;
    out->mKind = 0xf37c24e6;
    void* r = ((Fn00c90460)&FUN_00c90460)(vecEnd);
    cInteractionSub* inner = (cInteractionSub*)&((cSpatialObjectSub*)r)->mpCallback1;
    u32* v = (u32*)VC0(void*, inner, 0x98);
    if (*v == 0x93256b8) {
        out->mName = 0x512dfc22;
    } else if (*v == 0x93256b9) {
        out->mName = 0x512dfc23;
    } else if (*v == 0x93256ba) {
        out->mName = 0x512dfc20;
    } else {
        return false;
    }
    return true;
}

// @ 0x00e8f6b0
void cTribeFoodMatView::Update(void* a, void* b)
{
    HandleSimulationUpdate((int)a, (int)b);
    void* obj = mpObject;
    void* sub;
    if (obj != 0)
        sub = (void*)VC1(void*, obj, 0xb8, u32, kKeyTribeFoodMatView);
    else
        sub = 0;
    cSpatialObjectFlag* flagObj = (cSpatialObjectFlag*)sub;
    u8 flag = flagObj->mbFlag;
    if (GetClassFlag() != flag)
        SetClassFlag(flagObj->mbFlag);
    if (GetClassFlag()) {
        ModelKey key = { 0, 0, 0 };
        if (((cTribeFoodMatView*)this)->BuildKey((cTribeFoodMatView*)sub, &key)) {
            void* inner = &((cSpatialObjectSub*)sub)->mpCallback1;
            VC1(void, inner, 0x94, void*, &key);
        }
    }
}

// @ 0x00e8f760
bool GetOrnamentModelKey(cSpatialObject_s00e8_f0b0* obj, ModelKey* out)
{
    int key = obj->mKey;
    switch (key) {
    case 0x611a05e:
        out->mName = 0xba6596d3;
        out->mKind = 0x41842000;
        return true;
    case 0x611a05f:
        out->mName = 0x9597ce64;
        out->mKind = 0x41842000;
        return true;
    case 0x65658d2:
        out->mName = obj->mSubKey;
        out->mKind = 0x40828100;
        return true;
    case 0x750f022:
        out->mName = 0xcf571b4e;
        out->mKind = 0xd94352ed;
        return true;
    case 0x5d97f762:
        out->mName = 0x975f9185;
        out->mKind = 0xf37c24e6;
        return true;
    case 0x345bd5d:
        if (obj->mSubKey != 0) {
            out->mName = obj->mSubKey;
            out->mKind = 0;
            return true;
        }
        return true;
    case 0x356eb8a:
        return false;
    case 0x5b9a06e:
    {
        out->mName = 0xc5c2d389;
        out->mKind = 0xf37c24e6;
        void* h = (void*)VC0(void*, obj, 0x30);
        void* r = (void*)FUN_00ac8730(h);
        if (r == 0)
            return true;
        float lo = GetPropertyFloat(gPropertyManager, 0xd2078a9b, kOrnamentMinScale);
        float hi = GetPropertyFloat(gPropertyManager, 0xad06ca38, kOrnamentMaxScale);
        float s = ((cSpatialObject_s00e8_f0b0*)r)->mModelScale;
        if (hi <= s) {
            out->mName = 0x7d3993a4;
            return true;
        }
        if (lo < s) {
            out->mName = 0xda6fd23b;
            return true;
        }
        return true;
    }
    case 1:
        if (obj->mField38 == 9) {
            out->mName = 0;
            out->mSub  = 0;
            out->mKind = 0;
            return false;
        }
        out->mName = obj->mField3c;
        out->mSub  = obj->mField40;
        out->mKind = obj->mField44;
        return true;
    case 0x2ae5ba7:
        if (obj->mSubKey != 0) {
            out->mName = obj->mSubKey;
            out->mKind = 0x9430add7;
            return true;
        } else {
            u32 c = gOrnamentKeyCounter;
            u32 rem = c % 5;
            gOrnamentKeyCounter = c + 1;
            switch (rem) {
            case 0:  out->mName = 0x7afab880; break;
            case 1:  out->mName = 0x14b55883; break;
            case 2:  out->mName = 0x4b44c8c9; break;
            case 3:  out->mName = 0x7c6c1c1b; break;
            case 4:  out->mName = 0x7afab880; break;
            default: return true;
            }
            out->mSub  = 0;
            out->mKind = 0x9430add7;
            return true;
        }
    default:
        return false;
    }
}

// @ 0x00e8fae0
void cOrnamentView_s00e8_f0b0::Update(void* a, void* b)
{
    HandleSimulationUpdate((int)a, (int)b);
    void* obj = mpObject;
    if (obj == 0)
        return;
    cSpatialObjectSub* sub = (cSpatialObjectSub*)VC1(void*, obj, 0xb8, u32, kKeyOrnamentView);
    if (sub == 0)
        return;
    u8 v = (u8)VC0(u8, sub, 0x58);
    if (GetClassFlag() != v)
        SetClassFlag((u8)VC0(u8, sub, 0x58));
    cInteractionSub* inner = (cInteractionSub*)&sub->mpSub70;
    if (sub->mKey == 0x2ae5ba7) {
        u32* r = (u32*)VC0(void*, this, 0x2c);
        if (r != 0) {
            void* d = FUN_00d08d70();
            if (d != 0 && (u8)VC0(u8, inner, 0x24)) {
                r[1] |= 8;
                ((cSpatialObjectFlag*)r)->mbFlag = 2;
                return;
            }
            r[1] &= 0xfffffff7;
        }
    } else if (sub->mKey == 0x5b9a06e) {
        if ((u8)VC0(u8, inner, 0x48)) {
            ModelKey* h = (ModelKey*)VC0(void*, inner, 0x98);
            ModelKey key;
            key.mName = h->mName;
            key.mSub  = h->mSub;
            key.mKind = h->mKind;
            GetOrnamentModelKey((cSpatialObject_s00e8_f0b0*)sub, &key);
            if (ResourceMan_NotEqual(&key, h))
                VC1(void, inner, 0x94, void*, &key);
        }
    }
}

// @ 0x00e8ff10
void cInteractableObjectView::Update(void* a, void* b)
{
    HandleSimulationUpdate((int)a, (int)b);
    ((Fn00e8ef10)&FUN_00e8ef10)(this, 0);
    void* obj = mpObject;
    if (obj == 0)
        return;
    void* sub = (void*)VC1(void*, obj, 0xb8, u32, kKeyInteractable);
    if (sub == 0)
        return;
    u8 v = (u8)VC0(u8, sub, 0x64);
    if (GetClassFlag() != v)
        SetClassFlag((u8)VC0(u8, sub, 0x64));
}

// @ 0x00e8ffa0
void SP::cMineralView_s00e8_ffa0::HandleSimulationUpdate(int a, int b)
{
    HandleSimulationUpdateBase(a, b);
    int mode = GetCurrentGameMode();
    if (mode != 0x1654c04 && mode != 0x1654c05) {
        if (!PlanetModel()->sub_b7e3e0((const Vec3*)VC0(void*, mpObject, 0x2c)) &&
            !mpObject->GetEffect(0x4652727)) {
            mpObject->CreateEffect(0x16dd36c1, 0, 0x4652727);
            mpObject->SetEffectParam(0x4652727, 2048.0f);
            Vec3 col;
            MakeColor(&col);
            mpObject->SetEffectPos(0x4652727, &col);
        }
        return;
    }

    if (!mpObject) return;
    cCommodityNode_s00e8_ffa0* node = (cCommodityNode_s00e8_ffa0*)VC1(void*, mpObject, 0xb8, u32, 0x403df5f);
    if (!node) return;

    cFxRecord* rec = node->GetFxRecord();
    if (rec) {
        node->GetResourceFraction();
        char flag = node->sub_bfe0c0();
        if ((flag == 0 && mEffectMode != 5) || mLastFlag != flag) {
            mEffectMode = 5;
            if (mpObject->GetEffect(0x4652727)) {
                mpObject->KillEffect(0x4652727, 1);
                mpObject->KillEffect(0x4652728, 1);
            }
            int cell = PlanetModel()->GetContinent((const Vec3*)VC0(void*, (char*)node + 0x34, 0x2c));
            if (flag != 0) {
                const char* name;
                if (PlanetModel()->mpTable[cell] == 0) {
                    mpObject->CreateEffect(0xa8de65b4, 0, 0x4652727);
                    name = "object_resource_geyser_ocean_capped_icon";
                } else {
                    mpObject->CreateEffect(0x66dbfed1, 0, 0x4652727);
                    name = "object_resource_geyser_capped_icon";
                }
                mpObject->CreateEffect(SPIDFromName(name), 0, 0x4652728);
                mpObject->SetEffectParam(0x4652727, 2048.0f);
                mpObject->SetEffectParam(0x4652728, 2048.0f);
            } else {
                u32 id;
                if (PlanetModel()->mpTable[cell] == 0) {
                    id = 0x98e0bd04;
                } else {
                    int five = 5;
                    const int& idx = (mEffectMode < 5) ? mEffectMode : five;
                    id = kGeyserEffectIds[idx];
                }
                mpObject->CreateEffect(id, 0, 0x4652727);
                mpObject->SetEffectParam(0x4652727, 2048.0f);
            }
        }
        mLastFlag = flag;

        void* effA = mpObject->FindEffect(0x4652727);
        void* effB = mpObject->FindEffect(0x4652728);
        if (effA) {
            Vec3 pos;
            pos.x = FF32(rec, 0xc);
            pos.y = FF32(rec, 0x10);
            pos.z = FF32(rec, 0x14);
            XformMsg msg;
            float q[4];
            float tmp[9];
            float* m = Matrix3FromQuaternion(tmp, PlanetModel()->BuildSurfaceOrientation(q, &pos));
            for (int i = 0; i < 9; ++i) msg.rot[i] = m[i];
            msg.pos[0] = pos.x;
            msg.pos[1] = pos.y;
            msg.pos[2] = pos.z;
            msg.flags |= 2;
            msg.flags |= 4;
            msg.count++;
            msg.count++;
            VC1(void, effA, 0x18, void*, &msg);
            Vec3 col;
            MakeColor(&col);
            mpObject->SetEffectPos(0x4652727, &col);
            if (effB) {
                col.x = 1.0f;
                col.y = 1.0f;
                col.z = 1.0f;
                int nid = VC0(int, node, 0x4c);
                if (nid != -1) {
                    char* n = NounManager()->GetObject(nid);
                    if (n) {
                        col.x = FF32(n, 0xc4);
                        col.y = FF32(n, 0xc8);
                        col.z = FF32(n, 0xcc);
                    }
                }
                VC1(void, effB, 0x18, void*, &msg);
                mpObject->SetEffectPos(0x4652728, &col);
            }
        }
        if (VC0(u8, (char*)node + 0x34, 0x24)) {
            rec->mFlags |= 8;
            FU8(rec, 0x5c) = 2;
        } else {
            rec->mFlags &= 0xfffffff7;
        }
    }

    char bShow = (FI32(node, 0x214) != -1 && 100.0f > FF32(node, 0x224)) ? 1 : 0;
    AssignMeter(mpConstructionMeter, UpdateLoyaltyBar(mpConstructionMeter, bShow, 3));
    AssignMeter(mpCulturalMeter, UpdateLoyaltyBar(mpCulturalMeter, FI32(node, 0x21c) != -1, 1));
    AssignMeter(mpMilitaryMeter, UpdateLoyaltyBar(mpMilitaryMeter, FI32(node, 0x218) != -1, 0));

    int nounId = VC0(int, node, 0x4c);
    cFxRecord* R = (cFxRecord*)VC0(void*, this, 0x2c);
    int mineState = FI32(node, 0x1ec);
    if (R && mineState) {
        char* n = NounManager()->GetObject(nounId);
        if (FF32(node, 0x224) >= 100.0f)
            n = NounManager()->GetObject(FI32(node, 0x218));
        Vec3 tmpc;
        const Vec3* src;
        if (nounId == -1 || !n) {
            tmpc.x = 0.5f;
            tmpc.y = 0.5f;
            tmpc.z = 0.5f;
            src = &tmpc;
        } else {
            src = (const Vec3*)(n + 0xc4);
        }
        Vec3 c;
        c.x = src->x;
        c.y = src->y;
        c.z = src->z;
        if (Vector3_NotEqual(&c, &mColor)) {
            mColor.x = c.x;
            mColor.y = c.y;
            mColor.z = c.z;
            R->mColor[0] = c.x;
            R->mColor[1] = c.y;
            R->mColor[2] = c.z;
            if (VC0(u8, (char*)node + 0x34, 0x58))
                R->mFlags &= 0xfffff7ff;
            else
                R->mFlags |= 0x800;
        }
        switch (mineState) {
        case 1:
            R->mFlags &= 0xfffffffe;
            if (FU8(node, 0x1e9)) {
                mShieldFxOn = 0;
                FU8(node, 0x1e9) = 0;
            }
            if (FU8(node, 0x1e8)) {
                mpObject->FindEffect(0x547efc1);
                if (!mShieldFxOn) {
                    int cell = PlanetModel()->GetContinent((const Vec3*)VC0(void*, mpObject, 0x2c));
                    u32 id = (PlanetModel()->mpTable[cell] == 0) ? 0x70df71a8 : 0x40966708;
                    mpObject->CreateEffectB(id, 0, 0x547efc1);
                    mpObject->SetEffectParam(0x547efc1, FLT_MAX);
                    mpObject->SetEffectPos(0x547efc1, &mColor);
                    mShieldFxOn = 1;
                }
            }
            break;
        case 2:
            if (mpObject->FindEffect(0x547efc1))
                mpObject->KillEffect(0x547efc1, 1);
            R->mFlags |= 5;
            FU8(node, 0x1e6) = 1;
            break;
        case 3:
            if (((R->mFlags >> 14) & 1) && mHotSpotFxOn) {
                void* w = GonzagoModelWorld();
                VC5(void, w, 0x70, void*, R, u32, 0x6fb760ff, int, 1, float, 0.0f, int, 0);
                mHotSpotFxOn = 0;
            }
            break;
        case 4:
            if (((R->mFlags >> 14) & 1) && !mHotSpotFxOn) {
                void* w = GonzagoModelWorld();
                VC5(void, w, 0x70, void*, R, u32, 0x6fb760ff, int, 0, float, 0.0f, int, 0);
                mHotSpotFxOn = 1;
            }
            break;
        case 6:
            mShieldFxOn = 0;
            R->mFlags &= 0xfffffffe;
            break;
        }
    }

    if (FU32(node, 0x84) & 0x800) {
        if (!mpObject->GetEffect(0x30e8811)) {
            int id = VC0(int, node, 0x4c);
            u32 effId = (id != -1 ? 0xd37b39cdu : 0u) + 0x829de64au;
            mpObject->CreateEffect(effId, 0, 0x30e8811);
            mpObject->SetEffectParam(0x30e8811, 512.0f);
            mpObject->sub_a020(0x30e8811, 16.0f);
        }
        FU32(node, 0x84) &= 0xfffff7ff;
        return;
    }
    if (mpObject->GetEffect(0x30e8811))
        mpObject->KillEffect(0x30e8811, 1);
}

// @ 0x00e90820
void SP::cTotemPoleView_s00e8_ffa0::HandleSimulationUpdate_90820(int a, int b)
{
    (void)a;
    (void)b;

    cTotemPoleNode* node = (cTotemPoleNode*)VCall1(mpObject, 0xb8, (void*)0x55cf8e3);
    if (!node)
        return;

    bool run = false;
    if (node->mSpatial.mbFlagA8) {
        node->mSpatial.mbFlagA8 = 0;
        run = true;
    } else if (VCallBool0(&node->mSpatial, 0x88)) {
        run = true;
    } else if (mField34) {
        run = true;
    }

    if (run) {
        // Transform of the totem-pole noun itself.
        XformMsg msg;
        msg.flags = 4;
        msg.count = 1;
        Vec3* p = (Vec3*)VCall0(mpObject, 0x2c);
        msg.pos[0] = p->x;
        msg.pos[1] = p->y;
        msg.pos[2] = p->z;
        msg.scale = VCallFloat0(&node->mSpatial, 0x34);
        Matrix3FromQuaternion(msg.rot, VCall0(&node->mSpatial, 0x30));
        msg.flags |= 2;
        msg.count++;

        if (VCallBool0(&node->mSpatial, 0x88)) {
            static Vec3 sWhite = { 1.0f, 1.0f, 1.0f };
            void* extra = VCall1(&node->mSpatial, 0x98, &sWhite);
            void* world = GonzagoModelWorld();
            void* owner = VCall1(this, 0x0c, world);
            (void)extra;
            VCallVoid1(this, 0x28, owner);
        }

        float scaleDelta = 0.0f;
        cTotemModel* model = (cTotemModel*)VCall0(this, 0x2c);
        if (model) {
            model->mTransform.NotEqual(&msg);
            scaleDelta = model->mScale - model->mBaseScale;
        }

        // Per-segment transforms: the pole is assembled from its visible pieces.
        XformMsg part;
        part.flags = 0;
        part.count = 0;
        part.pos[0] = 0.0f;
        part.pos[1] = 0.0f;
        part.pos[2] = scaleDelta;
        part.scale = 1.0f;
        for (int i = 0; i < 9; ++i)
            part.rot[i] = msg.rot[i];

        mField34 = 0;
        int count = (int)((char*)node->mpSegmentsEnd - (char*)node->mpSegmentsBegin) / 4;
        for (int i = 0; i < count; ++i) {
            cTotemSegment* seg = (cTotemSegment*)node->mpSegmentsBegin[i];
            if (!seg)
                continue;

            if (((seg->mFlags >> 14) & 1) == 0) {
                mField34 = 1;
                continue;
            }

            XformMsg combined;
            combined.flags = 4 | 2;
            combined.count = msg.count + 1;
            combined.pos[0] = msg.pos[0];
            combined.pos[1] = msg.pos[1];
            combined.pos[2] = msg.pos[2];
            combined.scale = msg.scale;
            for (int j = 0; j < 9; ++j)
                combined.rot[j] = msg.rot[j];

            combined.Combine(&part);
            seg->mTransform.NotEqual(&combined);
            scaleDelta += seg->mScale - seg->mBaseScale;
        }
    }

    u8 visible = node->mbVisible;
    if (VCallBool0(this, 0x14) != visible)
        VCallVoidByte(this, 0x10, visible);
}
