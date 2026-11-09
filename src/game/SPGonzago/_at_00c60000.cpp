// src/game/SPGonzago/_at_00c60000.cpp -- migrated from slice(s) s00c6f6e0, s00c6e710, s00c69300, s00c68280, s00c67560, s00c66760, s00c65940, s00c649b0, s00c63a60, s00c62880, s00c61390, s00c602b0 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00c60000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cGameNounManager.h"
#include "SP/cSPMission.h"
#include "SP/cPlanet.h"
#include "SP/cPlanetModel.h"
#include "SP/cITerrainSphere.h"
#include "EA/Variant.h"
#include "SP/cPropertyList.h"
#include "SP/cTerrainSphere.h"
#include <math.h>
#include "SP/cSPMissionBase.h"
#include <intrin.h>
#include "SP/cCombatant.h"
#include "SP/cGameData.h"
#include "SP/cMovableDestructibleOrnament.h"
#include "SP/cLocomotiveObject.h"
#include "SP/cSpatialObject.h"
#include <stdlib.h>
#include "SP/cHerd.h"
#include "SP/cCityData.h"
#include "SP/cCivData.h"
#include <string.h>

// ---- items of slice s00c602b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8
#define PV32 PV16 PV16
class cSPMission;
class cSPMissionTerraform;
struct cPlanet;
struct cGameNoun;
struct cProperty;
struct cPropertyList;
struct wstring {
    wchar_t* mpBegin;               // +0x00
    wchar_t* mpEnd;                 // +0x04
    bool IsEmpty() const { return mpBegin == mpEnd; }
    wstring& operator=(const wstring& rhs);     // 0x0057cb60
};
struct ResourceKey {
    uint32_t mGroup;                // +0x00
    uint32_t mType;                 // +0x04
    uint32_t mInstance;             // +0x08
};
inline bool operator!=(const ResourceKey& a, const ResourceKey& b)
{
    return a.mGroup != b.mGroup || a.mType != b.mType || a.mInstance != b.mInstance;
}
struct cProperty {
    uint16_t pad00[9];              // +0x00
    uint16_t mwType;                // +0x12 (property type tag; 9 == int)
    int* GetInt();                  // 0x0041e990
};
struct cPropertyList {
    PV8 PV
    virtual bool Find(uint32_t id, cProperty** ppOut);     // +0x24
};
struct cMissionVtbl {
    PV32 PV8 PV                                             // +0x000 .. +0x0a0
    virtual void* FindMissionRecord(uint32_t id, void* pMission, int flags);   // +0x0a4
    PV32                                                    // +0x0a8 .. +0x124
    virtual char IsReady();                                 // +0x128
    PV8                                                     // +0x12c .. +0x148
    virtual void AddMessageHandler(uint32_t id);            // +0x14c
    virtual void RemoveMessageHandler(uint32_t id);         // +0x150
    PV4 PV2 PV                                              // +0x154 .. +0x16c
    virtual void RefreshProgress();                         // +0x170
};
struct cPlanetType {
    uint32_t pad00[2];
    uint32_t mHash;                 // +0x08
};
struct cPlanet {
    void* mpVftable;                // +0x00
    uint32_t mFlags;                // +0x04
    uint32_t pad08[2];              // +0x08
    uint32_t mKey[3];               // +0x0c (EA::ResourceMan::Key)
    float mBounds[3];               // +0x1c
    uint8_t pad28[0x90 - 0x28];
    cPlanetType* mpType;            // +0x90
    uint8_t pad94[0x13c - 0x94];
    void* mpStarRecord;             // +0x13c
};
struct cNounPropertyList {
    PV8 PV4 PV2                                             // +0x000 .. +0x034
    virtual void SetKey(const void* pKey);                  // +0x38
    virtual void SetValue(const float* pValue);             // +0x3c
};
struct cNounFlagBlock {
    uint8_t pad00[0x80];
    uint8_t mb80;                   // +0x80
    void Set(bool value);           // 0x00bfc470
};
struct cGameNoun {
    uint8_t pad00[0x70];
    cNounPropertyList mPropList;    // +0x70
    uint8_t padA4[0x148 - 0xa4];
    cNounFlagBlock mFlagBlock;      // +0x148
    void FUN_00c6f770(uint32_t type, int32_t arg2, int32_t arg3);  // 0x00c6f770
};
struct cTerrainSphere {
    bool FUN_00c772c0(uint32_t id);     // 0x00c772c0
    void FUN_00c77bf0(uint32_t id);     // 0x00c77bf0
};
struct cGameNounManager {
    cGameNoun* CreateNoun(uint32_t type);   // 0x00b20c60
    cTerrainSphere* GetCurrentTerrainSphere();   // 0x00f67d90
};
struct cSimulatorSubsystem {
    void FUN_0106ab20(uint32_t id);     // 0x0106ab20
    void FUN_0106dcd0(uint32_t id);     // 0x0106dcd0
};
struct cToolID {
    uint32_t mGroup;                // +0x00
    uint32_t mType;                 // +0x04
    uint32_t mInstance;             // +0x08
};
struct cPlanetPickParams {
    uint32_t mPlanetType;           // +0x00
    uint32_t mPickMode;             // +0x04
    uint32_t mPad08;                // +0x08
    uint32_t mPad0C;                // +0x0c
    uint32_t mPad10;                // +0x10
    uint32_t mPad14;                // +0x14
    uint32_t mPad18;                // +0x18
    uint32_t mPad1C;                // +0x1c
    uint32_t mPad20;                // +0x20
    uint32_t mPad24;                // +0x24
    uint32_t mPad28;                // +0x28
    uint32_t mPad2C;                // +0x2c
    uint32_t mPad30;                // +0x30
    uint32_t mPad34;                // +0x34
    uint32_t mPad38;                // +0x38
    uint32_t mPad3C;                // +0x3c
    uint32_t mPad40;                // +0x40
    uint32_t mPad44;                // +0x44
    cPlanetPickParams();            // 0x00ba7bd0
    ~cPlanetPickParams();           // 0x00ba8220
};
class cSPMission {
public:
    // The message handler subobject sits 0x34 bytes into a mission object.
    static const uint32_t kHandlerOffset = 0x34;

    uint8_t pad000[0x78];
    uint32_t mMissionTypeKey;       // +0x78 (0xd85005e9 for the terraform missions)
    uint8_t pad07c[0x14c - 0x7c];
    wstring mUITitle;               // +0x14c
    uint8_t pad154[0x180 - 0x154];  // +0x154 .. +0x180 (the base ends where the subclasses' members begin)

    bool Init();                                        // 0x00c4ad50
    bool IsActive();                                    // 0x00c44c80
    uint32_t ReadTargetPlanetType();                    // 0x00c45b40
    void* GetPlanetRecordFromTargetType(uint32_t type); // 0x00c474b0
    void FUN_00c47180(void* pRecord);                   // 0x00c47180
    cPlanet* GetTargetPlanet();                         // 0x00970b30
    cPlanet* PickPlanet(const cPlanetPickParams* pParams);   // 0x00c47e20
    void FUN_00c4a0c0();                                // 0x00c4a0c0
    void TriggerUIUpdate();                             // 0x00c47d80
    void GetText(uint32_t id, wstring* pOut);           // 0x00c487d0
    void GetUITitle(wstring* pOut);                     // 0x00c48d40
    bool GetTagString(uint32_t tag, wstring* pOut);     // 0x00c491c0
    float FUN_00c44d00(cPlanet* pPlanet, void* arg);    // 0x00c44d00
    void FUN_00c44b80();                                // 0x00c44b80
    void FUN_00c44bd0();                                // 0x00c44bd0
    cMissionVtbl* Vtbl() { return (cMissionVtbl*)this; }
};
class cSPMissionTerraform : public cSPMission {
public:
    cPropertyList* mpPropertyList;  // +0x180
    uint8_t pad184[0x194 - 0x184];
    cToolID* mpToolIDsBegin;        // +0x194
    cToolID* mpToolIDsEnd;          // +0x198
    uint8_t pad19c[0x1e8 - 0x19c];
    cPlanet* mpTargetPlanet;        // +0x1e8
    uint8_t pad1ec[0x1f0 - 0x1ec];
    uint32_t mTerraformState;       // +0x1f0
    bool mFlag1F4;                  // +0x1f4
    bool mFlag1F5;                  // +0x1f5

    void OnTerraformSphereChange(int param);            // 0x00c60850
    void RegisterMessages();                            // 0x00c608d0
    void UnregisterMessages();                          // 0x00c60930
    bool HasAnyRequiredTool();                          // 0x00c609d0
    int GetTargetPlanetScore();                         // 0x00c60a70
    int GetTargetTerraformScore();                      // 0x00c60ab0
    bool IsStageOneComplete();                          // 0x00c60af0
    bool IsStageTwoComplete();                          // 0x00c60cc0
    bool Init();                                        // 0x00c60e90
    float ScoreTerraformStep(cPlanet* pPlanet, void* arg);  // 0x00c60fa0
    void GetUITitle(wstring* pOut);                     // 0x00c61070
    bool GetTagString(uint32_t tag, wstring* pOut);     // 0x00c61300
};
cGameNounManager* __cdecl NounManager();                // 0x00b3d300
int  __cdecl GetUniverseContext();                      // 0x01021080
void* __cdecl GetActivePlanetRecord();                  // 0x010212a0
int  __cdecl IsArchivedMission();                       // 0x01021240
void* __cdecl GetActivePlanet();                        // 0x01021260
cSimulatorSubsystem* __cdecl FUN_010666a0();            // 0x010666a0
void* __cdecl FUN_00b8de30(void* pRecord);              // 0x00b8de30
enum {
    kMsgTerraformStep        = 0x248975f,
    kMsgTerraformSubStepA    = 0x2489766,
    kMsgTerraformSubStepB    = 0x248976a,
    kMsgStoryRuinScanned     = 0x44f1189,
    kMsgTerraformArtifact    = 0xf46093da,
    kMsgTerraformAction      = 0x6441936,
};
// ---- items of slice s00c602b0 end

// ---- items of slice s00c61390 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  uint8;
struct Mission {
    // Functions defined by this slice.
    void  FUN_00c61390(int arg);
    void  FUN_00c61450(int msg, int arg);
    void  FUN_00c61550();
    void  FUN_00c61570();
    int   FUN_00c615c0(int param);
    void* FUN_00c61bb0();
    char  FUN_00c61d70();
    int   FUN_00c61dd0(int param);
    void  FUN_00c61e20(int msg, int arg);
    char  FUN_00c61e80(int msg, int out);
    void* FUN_00c61f20();
    int   FUN_00c620c0(int tag);
    void  FUN_00c62100();
    void  FUN_00c62180(int* a, int* b);
    char  FUN_00c62200();
    void  FUN_00c62250(int msg, int arg);
    void* FUN_00c62370();
    char  FUN_00c624c0();
    int   FUN_00c62540(int param);
    void  FUN_00c62590(int msg, int arg);
    int   FUN_00c62710();
    void  FUN_00c62750(int msg, int arg);

    // __thiscall helpers from the rest of the game.
    void* FUN_0970b30();
    void* FUN_00b21340(int a, int b, int c, int d, int e);
    void  FUN_00ba95a0(void* src);
    void  FUN_00bdc4a0(int arg);
    void* FUN_00bbc870(void* out, int score, int id, int zero);
    void* FUN_00bbc950(void* out, int score, int id, int zero);
    void* FUN_00bbca30(void* out, int score, int id);
    int   FUN_00c478b0(int arg);
    void  FUN_00c4a6b0(int msg, int arg);
    void  FUN_00c47d80();
    void  FUN_00c46160();
    void  FUN_00c461d0();
    void  FUN_00c46250();
    void  FUN_00c471c0();
    void  FUN_00c472e0();
    void  FUN_00c46590();
    char  FUN_00c4ad50();
    void  FUN_00c4a0c0();
    void  FUN_00c4b760();
    char  FUN_00c491c0(int msg, int out);
    void* FUN_00bfc5f0();
    int   FUN_00fe6770(int id);
    int   FUN_00fe66f0(int id);
    char  FUN_00fe4180(int id);
    void* FUN_00c451e0();
    int   FUN_00ff0420();
    int   FUN_00ff0870();
    void  FUN_00ff0760();
    char  FUN_00c308e0(int arg);
    void  FUN_00c48e90();
    int   FUN_00c70fb0();
    int   FUN_00c60ab0();
    char  FUN_00c60af0();
    char  FUN_00c60cc0();
    char  FUN_00c609d0();
    void* FUN_005c65e0();
    char  FUN_00ae9390();
    void  FUN_00dd8640(int a, int b, int c, int d, int e, int f);
    void* FUN_008414c0();
    void* FUN_00ba6dc0(int arg);
    void* FUN_00b8de30();
    void* FUN_00b1fdb0();
};
void* FUN_01021260();
void* FUN_01021080();
void* FUN_01021090();
void* FUN_00b3d300();
void* FUN_00b3d2a0();
void* FUN_00b3d3e0();
void* FUN_00b3d4a0();
void* FUN_01002bd0();
char  FUN_006a1250(void* obj, int key, void* out);
char  FUN_006a12a0(void* obj, int key, void* out);
int   FUN_0041e050(void* out, const void* fmt, int v);
int   FUN_01041c50(const char* name, int id, int b);
void  FUN_00f47380(void* p);
typedef char (__thiscall* VTCFn)(void*);
typedef void (__thiscall* VTVFn)(void*);
#define VTC(o,off) (((VTCFn)(*(void***)(o))[(off)/4])((void*)(o)))
#define VTV(o,off) (((VTVFn)(*(void***)(o))[(off)/4])((void*)(o)))
// ---- items of slice s00c61390 end

// ---- items of slice s00c62880 begin (TODO(rewrite): local stubs, replace by canonical classes)
void  __cdecl operator_delete__(void*);
void  __cdecl FUN_00ebb720(int, int);                           // 0xebb720
struct NounIdHelper { void* Dispatch(void* id); };                // 0xb18460
static inline void** Vt(void* p){ return *(void***)p; }
struct MissionBase {
  void BaseCtor();       // 0xc48e90 cGenericPressureEvent ctor
  void BaseDtor();       // 0xc47680 cSPMission dtor
  bool Init();           // 0xc4ad50
  bool IsActive();       // 0xc44c80
  void GetText(int key, void* out);   // 0xc487d0
  void TriggerUIUpdate();             // 0xc47d80
  void FUN_00c472e0();               // 0xc472e0
  void FUN_00c471c0();               // 0xc471c0
  void SetSerializer();              // 0xc2e4e0
};
struct Adj {
  void* Adjust0(void* id);
  void* Adjust1(void* id);
  void* Adjust2(void* id);
};
struct WString12 { void* mBegin; void* mEnd; void* mCap; };
struct CString16 { uint8_t mData[0x10]; };
struct MissionWar {
  uint8_t pad00[0x78];
  uint32_t mKey78;                 // +0x78
  uint8_t pad7c[0x14];
  void* mEmpire90;                 // +0x90
  uint8_t pad94[0xb8];
  WString12 mCachedText;           // +0x14c
  uint8_t pad158[0x98];
  int mState;                      // +0x1f0
  int mProgress;                   // +0x1f4
  int mProgressMax;                // +0x1f8
  uint8_t mFlag;                   // +0x1fc
  uint8_t pad1fd[0x13];
};
struct MsgData {
  uint8_t pad00[8];
  void* mPtr08;                    // +0x08
  uint8_t pad0c[4];
  void* mPtr10;                    // +0x10
};
// ---- items of slice s00c62880 end

// ---- items of slice s00c63a60 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void _ReadWriteBarrier(void);
extern "C" int gMorphData18;   // 0x1693d74
extern "C" int gMorphData1c;   // 0x1693d78
extern "C" int gMorphData20;   // 0x1693d7c
extern uint8_t gTgtMorphKeyData; // 0x15777e4
extern "C" float QuaternionSlerp(void*, void*, void*);
extern "C" void QuaternionSlerpVoid(void*, void*, void*);
extern "C" double sqrt(double);
extern "C" void* __cdecl memset(void* dst, int val, unsigned n);
#pragma intrinsic(_ReadWriteBarrier)
struct VObj {
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
virtual void* v2c();
virtual void v30();
virtual void v34();
    virtual void v38(void* out);
    virtual void v3c(void* q);
    virtual void v40(float f);
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
    virtual void* v60(void* out);
};
struct Ref {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3(int);
    virtual bool v4();
};
struct GameDataBase { void ctorGameData(); };
struct SpatialBase  { void ctorSpatialObject(); };
struct SpatialObj   { void SetModelKey(void* key); };
enum {
    kVtblMorph0  = 0x1470eb8,   // cMorphHandle primary vftable
    kVtblMorph1  = 0x147112c,   // cMorphHandle second base vftable
    kVtblMorphSp = 0x1470df0,   // cMorphHandle spatial sub-object vftable
    kVtblTgt0    = 0x1470ff8,   // cTargetMorphHandle primary vftable
    kVtblTgt1    = 0x1470fe4,   // cTargetMorphHandle second base vftable
    kVtblTgtSp   = 0x1470f20    // cTargetMorphHandle spatial sub-object vftable
};
struct MorphInit {
    uint8_t mFlag;   // +0x00
    char    pad01[0x17];
    int     mA;      // +0x18
    int     mB;      // +0x1c
    int     mC;      // +0x20
    void Init();
};
struct FlagHolder {
    char pad00[0xd0];
    int* mp;         // +0xd0
    void SetFlag(int v);
};
struct GameDataBase2 { void RemoveOwner(int owner); };
int* FUN_00eedba0(void* out, void* in);   // 0x00eedba0
struct cGameDataThing {
    char pad00[0x9c];
    int* mpObj;   // 0x9c
    void RemoveOwnerFn(int owner);
};
struct HandleThing {
    char    pad00[0x34];
    char    mSub[0x1a8 - 0x34];
    float   mA;    // 0x1a8
    float   mB;    // 0x1ac
    float   mC;    // 0x1b0
    uint8_t mEn;   // 0x1b4
    void Fn();
    void SetEnabled(bool v);
};
struct MorphCastHelper {
    void* FUN_00b18460(unsigned id);              // 0x00b18460
};
struct MorphA {
    void* QueryInterface(unsigned id);
};
struct cMorphHandle {
    void*   mpVtbl;          // +0x000  primary vftable
    void*   mpVtbl04;        // +0x004  second base vftable
    char    pad08[0x2c];     // +0x008
    void*   mpVtblSpatial;   // +0x034  spatial sub-object vftable
    char    pad38[0xa2];     // +0x038 ... +0x0d9
    uint8_t mVis;            // +0x0da
    char    padDb[0x2d];     // +0x0db ... +0x107
    float   mF108;           // +0x108
    float   mF10c;           // +0x10c
    float   mF110;           // +0x110
    uint8_t mB114;           // +0x114
    uint8_t mB115;           // +0x115
    char    pad116[2];       // +0x116 ... +0x117
    cMorphHandle();
    void Offset(float* p, int a);
};
struct cTargetMorphHandle : cMorphHandle {
    float   mF118;              // +0x118
    float   mF11c;              // +0x11c
    float   mF120;              // +0x120
    uint8_t mB124;              // +0x124
    char    pad125[3];          // +0x125 ... +0x127
    int     mI128;              // +0x128
    float   mF12c;              // +0x12c
    int     mI130;              // +0x130
    Ref*    mpRef;              // +0x134
    char    pad138[0x200 - 0x138];
    cTargetMorphHandle();
    void Dtor();
    void Release();
};
struct AppObj {
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
    virtual void* v58(void* a, int b);
};
AppObj* SP_App();                // 0x0067dd10
struct Ctx { bool Check(); };    // 0x007c4900
struct KObj {
virtual void k00();
virtual void k04();
virtual void k08();
virtual void k0c();
virtual void k10();
virtual void k14();
virtual void k18();
virtual void k1c();
virtual void k20();
virtual void k24();
virtual void k28();
virtual void k2c();
virtual void k30();
virtual void k34();
virtual void k38();
virtual void k3c();
virtual void k40();
virtual void k44();
virtual void k48();
virtual void k4c();
virtual void k50();
virtual void k54();
virtual void k58();
virtual void k5c();
virtual void k60();
virtual void k64();
virtual void k68();
};
struct VObjDir {
virtual void d00();
virtual void d04();
virtual void d08();
virtual void d0c();
virtual void d10();
virtual void d14();
virtual void d18();
virtual void d1c();
virtual void d20();
virtual void d24();
virtual void d28();
    virtual void* v2c(float* dir);
virtual void d30();
virtual void d34();
    virtual void d38(void* out);
    virtual void d3c(void* q);
    virtual void d40(float f);
virtual void d44();
virtual void d48();
virtual void d4c();
virtual void d50();
virtual void d54();
virtual void d58();
virtual void d5c();
    virtual void* d60(void* out);
};
struct AppObj2 {
virtual void a00();
virtual void a04();
virtual void a08();
virtual void a0c();
virtual void a10();
virtual void a14();
virtual void a18();
virtual void a1c();
virtual void a20();
virtual void a24();
virtual void a28();
virtual void a2c();
virtual void a30();
virtual void a34();
virtual void a38();
virtual void a3c();
virtual void a40();
virtual void a44();
virtual void a48();
virtual void a4c();
virtual void a50();
virtual void a54();
    virtual void* v58(void* a, void* b);
};
struct ViewCtx { void Update(); };
struct PlanetModelObj {
    void* BuildSurfaceOrientation(void* dst, void* src);            // 0x00b7f190
    void* BuildSurfaceOrientation_2(void* dst, void* a, void* b);   // 0x00b7f1f0
    void* BuildSurfaceOrientation2(void* dst, void* src);           // 0x00b7f250
};
PlanetModelObj* PlanetModel();
struct CtxD4 {
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
virtual void s20();
virtual void s24();
virtual void s28();
virtual void s2c();
virtual void s30();
virtual void s34();
virtual void s38();
virtual void s3c();
    virtual void s40();
    virtual bool s44(void* a, void* b, void* t, void* f, void* out);
virtual void s48();
virtual void s4c();
virtual void s50();
virtual void s54();
virtual void s58();
virtual void s5c();
virtual void s60();
virtual void s64();
virtual void s68();
virtual void s6c();
virtual void s70();
    virtual void s74(void* a, int b, float c, void* d);
virtual void s78();
virtual void s7c();
    virtual void s80(void* a, int b, void* c, void* d, void* e);
virtual void s84();
virtual void s88();
virtual void s8c();
virtual void s90();
virtual void s94();
virtual void s98();
virtual void s9c();
virtual void sA0();
virtual void sA4();
virtual void sA8();
virtual void sAc();
virtual void sB0();
virtual void sB4();
virtual void sB8();
virtual void sBc();
virtual void sC0();
virtual void sC4();
virtual void sC8();
virtual void sCc();
virtual void sD0();
virtual void sD4();
virtual void sD8();
virtual void sDc();
virtual void sE0();
virtual void sE4();
virtual void sE8();
virtual void sEc();
virtual void sF0();
virtual void sF4();
virtual void sF8();
virtual void sFc();
virtual void s100();
virtual void s104();
virtual void s108();
    virtual void s10c(void* a, void* b);
};
struct Kin {
    char data[0x200];
    void Fn63cb0();
    void Fn63f90();
    void Fn64170();
    void Fn642e0();
};
struct CtxOut {
    float     a;    // +0x00
    float     b;    // +0x04
    float     c;    // +0x08
    float     d;    // +0x0c
    float     e;    // +0x10
    uint8_t   f0;   // +0x14
    uint8_t   f1;   // +0x15
};
struct TVec { float x, y, z; };
struct TVec4 { float x, y, z, w; };
struct Vec3f { float x, y, z; };
struct CmpObj64 { void Fn(); };
struct PathObj {
    uint8_t   mFlag;    // +0x00
    char      pad01[3];
    void**    mpBegin;  // +0x04
    void**    mpEnd;    // +0x08
    char      pad0c[0x0c];
    float     f18;      // +0x18
    float     f1c;      // +0x1c
    float     f20;      // +0x20
    void Fn64460(void* h);
    void Fn64940(void* h);
};
float CopyPairF(void* a, void* b)
{
    return QuaternionSlerp(((VObj*)((char*)a + 0x34))->v2c(),
                           (char*)b + 0x118,
                           ((VObj*)((char*)b + 0x34))->v2c());
}
// ---- items of slice s00c63a60 end

// ---- items of slice s00c649b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl SP_ModelManager();                        // 0x67dd80
void  __fastcall FUN_00c8a420(void* self);              // 0xc8a420 (thiscall)
void  __fastcall FUN_00b184c0(void* self);              // 0xb184c0 (thiscall)
void  __cdecl FUN_00c640e0();                           // 0xc640e0
void  __cdecl FUN_00c64170();                           // 0xc64170
struct Vec3 { float x, y, z; };
struct APos { char _pad[0x150]; Vec3 pos; };
struct A {
  bool __thiscall Contains(int key);
  void __thiscall EnableFlag(char b);
  void __thiscall SetA(float v);
  void __thiscall SetB(float v);
  void __thiscall SetC(float v);
  void __thiscall SetPos(float* p);
  void __thiscall FUN_00c64db0();
};
// ---- items of slice s00c649b0 end

// ---- items of slice s00c65940 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float g_1693DD4, g_1693DD8, g_1693DDC;
extern const float g_1693DC8, g_1693DCC, g_1693DD0;
extern const float g_1693D74, g_1693D78, g_1693D7C;
extern const float g_15777D0, g_15777D4, g_15777D8, g_15777DC;
extern const float g_1485720;
extern const float g_13EC4B8;
extern void* vtbl_cMorphHandleSub[];   // 0x14711a4
extern void* vtbl_ringPrimary[];       // 0x1471288
extern void* vtbl_ring004[];           // 0x1471274
extern void* vtbl_ring118[];           // 0x14711a8
extern void* vtbl_ring034[];           // 0x14711b0
extern void* vtbl_ballPrimary[];       // 0x14713c8
extern void* vtbl_ball004[];           // 0x14713b4
extern void* vtbl_ball118[];           // 0x14712ec
extern void* vtbl_ball034[];           // 0x14712f0
extern const char DAT_015777FC[];      // 0x15777fc
extern const char DAT_01577808[];      // 0x1577808
struct cSPVector3_s00c6_5940    { float x, y, z; };
struct cSPQuaternion_s00c6_5940 { float x, y, z, w; };
struct cSimpleRotationRing;
struct cSimpleRotationBall;
struct cViewRef {
    char pad0[4];
    int  mFlags;                     // +0x04
};
struct cEventRef {
    char          pad0[4];
    unsigned int  mFlags;            // +0x04
    char          pad8[0x5d - 0x08];
    unsigned char mKind;             // +0x5d
};
struct cSpatialHead {
    void** vftable;                  // +0x00
    void SetKey(const void* key);    // 0xc88810
};
struct cSub128 {
    float mScale;                            // +0x000
    float mMat00, mMat01, mMat02;            // +0x004,+0x008,+0x00c
    float mMat10, mMat11, mMat12;            // +0x010,+0x014,+0x018
    float mMat20;                            // +0x01c
    union { float mMat21; int mMat21i; };    // +0x020
    union { float mMat22; int mMat22i; };    // +0x024
    void Ctor(int a, int b);                 // 0x93a560
    void Init(int a, int b);                 // 0x93a480
};
struct cMorphHandle_s00c6_5940 {
    void**  vftable;                 // +0x000
    void**  vftable004;              // +0x004
    char    pad008[0x034 - 0x008];   // +0x008 .. +0x034
    cSpatialHead mSpatial;           // +0x034
    char    pad038[0x050 - 0x038];   // +0x038 .. +0x050
    unsigned int mEventFlags;        // +0x050
    char    pad054[0x09c - 0x054];   // +0x054 .. +0x09c
    cEventRef* mPtr9c;               // +0x09c
    void*   mPtrA0;                  // +0x0a0
    char    pad0a4[0x0d0 - 0x0a4];   // +0x0a4 .. +0x0d0
    cViewRef* mViewRef;              // +0x0d0
    char    pad0d4[0x118 - 0x0d4];   // +0x0d4 .. +0x118

    // The constructor also stores the sub-object vtable here (see ctors).
    union {
        void**        vftable118;    // +0x118
        unsigned char mFlags118;     // +0x118
    };
    float   mBaseX;                  // +0x11c
    union {
        float         mBaseY;        // +0x120
        unsigned char mByte120;      // +0x120
    };
    union {
        float   mBaseZ;              // +0x124
        int     mBaseZInt;           // +0x124
    };
    cSub128 mSub128;                 // +0x128 (scale + matrix)
    union { float mOffX; int mOffXi; };  // +0x150
    float   mOffY, mOffZ;            // +0x154,+0x158
    float   mAxisX, mAxisY, mAxisZ;  // +0x15c,+0x160,+0x164
    float   mVec1X, mVec1Y, mVec1Z;  // +0x168,+0x16c,+0x170
    float   mLo;                     // +0x174
    float   mHi;                     // +0x178
    float   mT;                      // +0x17c
    float   mU, mV;                  // +0x180,+0x184
    float   mF188;                   // +0x188
    float   mViewX, mViewY, mViewZ;  // +0x18c,+0x190,+0x194
    cSPQuaternion_s00c6_5940 mQuat198;          // +0x198,+0x19c,+0x1a0,+0x1a4
    float   mSpeed;                  // +0x1a8
    float   mPhase;                  // +0x1ac
    float   mAmplitude;              // +0x1b0
    union {
        char  mActive;               // +0x1b4 (ball)
        float mRing1b4;              // +0x1b4 (ring)
    };

    cMorphHandle_s00c6_5940();                  // 0xc63be0

    // Embedded cSpatialObject (at +0x34) vtable accessors.
    void**  SpatialVt() { return mSpatial.vftable; }
    void SetPosition(cSPVector3_s00c6_5940* p) {
        ((void(__thiscall*)(void*, cSPVector3_s00c6_5940*))SpatialVt()[0x38 / 4])(&mSpatial, p);
    }
    void SetOrientation(cSPQuaternion_s00c6_5940* q) {
        ((void(__thiscall*)(void*, cSPQuaternion_s00c6_5940*))SpatialVt()[0x3c / 4])(&mSpatial, q);
    }
    void SetScale(float s) {
        ((void(__thiscall*)(void*, float))SpatialVt()[0x40 / 4])(&mSpatial, s);
    }

    void SetFacing(const cSPVector3_s00c6_5940& dir);   // 0xc65940
    void SetT(float t);                      // 0xc65af0
    void SetTLerp(float t);                  // 0xc65b50
    bool OnEvent(void* p);                   // 0xc65e80
    void OnView(void* view);                 // 0xc660f0
    void SetPhase(float v);                  // 0xc662b0
    void SetAmplitude(float v);              // 0xc66310
    void UpdateMatrix();                     // 0xc66370
    void SetRange(float lo, float hi);       // 0xc666f0

    // Declared-only helpers defined elsewhere in the module (addresses in comments).
    void UpdatePos();                        // 0xc64db0
    void UpdateQuat();                       // 0xc64f00
    void UpdateBallPos();                    // 0xc65610
    void RefreshScale();                     // 0xc63ae0
    char OnEventCheck(void* p);              // 0xc656c0
    void SetRingReset();                     // 0xc64170
};
struct cSimpleRotationRing : cMorphHandle_s00c6_5940 {
    int   mRing1b8;                  // +0x1b8
    float mRing1bc;                  // +0x1bc
    float mRing1c0;                  // +0x1c0
    float mRing1c4;                  // +0x1c4
    float mRing1c8;                  // +0x1c8
    float mRing1cc;                  // +0x1cc
    int   mRing1d0;                  // +0x1d0
    cSimpleRotationRing();                   // 0xc65c00
    void* ScalarDtor(unsigned char flags);   // 0xc65bc0
};
struct cSimpleRotationBall : cMorphHandle_s00c6_5940 {
    cSimpleRotationBall();                   // 0xc65f00
};
// ---- items of slice s00c65940 end

// ---- items of slice s00c66760 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);
extern float gF_1471064;      // 0x1471064  half (0.5f)
extern float gF_15777a8;      // 0x15777a8  sin/cos table build angle
extern float gF_1693de0;      // 0x1693de0  table 1 basis X
extern float gF_1693de4;      // 0x1693de4  table 1 basis Y
extern float gF_1693de8;      // 0x1693de8  table 1 basis Z
extern float gF_1693dc8;      // 0x1693dc8  table 2 basis X
extern float gF_1693dcc;      // 0x1693dcc  table 2 basis Y
extern float gF_1693dd0;      // 0x1693dd0  table 2 basis Z
extern uint32_t gF_1693d64;   // 0x1693d64  table-built flags
#pragma intrinsic(sqrt, sin, cos)
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    float Length() const { return (float)sqrt((double)(x * x + y * y + z * z)); }
    float SquaredLength() const { return x * x + y * y + z * z; }
};
inline Vector3 operator+(const Vector3& a, const Vector3& b) { return Vector3(a.x + b.x, a.y + b.y, a.z + b.z); }
inline Vector3 operator-(const Vector3& a, const Vector3& b) { return Vector3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline Vector3 operator*(const Vector3& a, float s) { return Vector3(a.x * s, a.y * s, a.z * s); }
inline Vector3 operator*(float s, const Vector3& a) { return Vector3(s * a.x, s * a.y, s * a.z); }
inline float Dot(const Vector3& a, const Vector3& b) { return (a.x * b.x + a.y * b.y) + a.z * b.z; }
struct Quaternion {
    float x, y, z, w;
    Quaternion() {}
    Quaternion(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
};
static const float kEpsilon = 1e-8f;
inline float InvSqrtEps(float sq) { return 1.0f / (float)sqrt((double)sq + (double)kEpsilon); }
Quaternion* Vec4Transform(void* out, const void* q, const void* v);                      // 0x0059aed0
float AngleAroundAxis(const Vector3* d);                                                 // 0x006994a0
bool IntersectRaySphere(const Vector3* org, const Vector3* dir, const Vector3* center,
                        float radius, float* outT);                                      // 0x005a9c40
void* AppGet();                                                                          // 0x0067dd10  SP::App
bool GetCameraRay(void* viewer, Vector3* origin, Vector3* dir);                          // 0x007c4900
Vector3* ConstrainToPlane(Vector3* out, const Vector3* in);                              // 0x00c650d0
void CtrlNotifyChanged(void* self);                                                      // 0x00c65610
void CtrlResetBase(void* self);                                                          // 0x00c63cb0
void BuildSurfaceOrientation_2(Vector3* out, const Vector3* a, const Vector3* b);        // 0x00b7f1f0
void QuaternionFromDirections(Quaternion* out, const Vector3* fwd, const Vector3* up);   // 0x00698180
Quaternion* Vec4Rotate(void* out, const Quaternion* q, const Vector3* v);                // 0x007dcb00
void* CopyRange(const void* first, const void* last, void* dest);                        // 0x00b115c0
void* AllocVectorBytes(int size);                                                        // 0x00f473a0
void FreeVectorBytes(void* p);                                                           // 0x00f47380
extern Quaternion gQ_1693d54; // 0x1693d54  cached sin/cos quaternion (state 1)
extern Quaternion gQ_1693d44; // 0x1693d44  cached sin/cos quaternion (state 0)
extern Vector3 gV_1693dd4;    // 0x1693dd4  reference up direction
struct TargetSub {
    PV8 PV2 PV
    virtual const Vector3* GetPosition();             // +0x2c
    virtual void SetOrientation(const Quaternion& q); // +0x3c
    PV8 PV8
    virtual Vector3* GetDirPoint(Vector3* out, const Vector3* a, const Vector3* b);  // +0x5c
    PV
    virtual const void* GetExtents(void* out);        // +0x60
};
struct Ctrl {
    uint32_t pad00[0xd];
    TargetSub mTarget;              // +0x34  embedded target/event sub-object
    uint32_t pad38[0x34];           // 0x38..0x108
    Vector3 mFocus;                 // +0x108  tracked focus point
    uint32_t pad114;
    void* mConstrain;               // +0x118  constraint object (ConstrainToPlane)
    uint32_t pad11c[0x10];          // 0x11c..0x15c
    uint8_t mb120;                  // +0x120  accumulator-valid flag
    uint32_t pad124;
    Quaternion mZeroQuat;           // +0x128  accumulator zeroed by the frame update
    uint32_t pad138[0x9];           // 0x138..0x15c
    Quaternion mApproach;           // +0x15c  derived approach orientation
    uint32_t pad16c;
    Vector3 mAxis;                  // +0x170  orbit axis / plane normal
    Vector3 mDirRef;                // +0x17c  reference direction
    Quaternion mBase;               // +0x188  base orientation
    Quaternion mCached;             // +0x198  last published orientation
    Quaternion mOut;                // +0x1a4  current output orientation
    float mScaleA;                  // +0x1b4
    int32_t mState;                 // +0x1b8  orientation source state (0/1/2)
    uint32_t pad1bc;
    float mScaleB;                  // +0x1c0

    void FrameUpdate();             // 0x00c66760
    void FlushOrientation();        // 0x00c66c10
    void Approach();                // 0x00c66e60
};
struct Vector4 {
    float x, y, z, w;
    Vector4() {}
    Vector4(const Vector4& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
};
struct Vector4Array {
    Vector4* mpBegin;
    Vector4* mpEnd;
    Vector4* mpCapacity;
    void insert(Vector4* dest, const Vector4* value);
};
void* CopyBackward(const void* first, const void* last, void* resultEnd);
// ---- items of slice s00c66760 end

// ---- items of slice s00c67560 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl fabs(double);
#pragma intrinsic(sqrt, sin, cos, fabs)
#define P4(n) virtual void p##n##a(); virtual void p##n##b(); virtual void p##n##c(); virtual void p##n##d();
struct V3 { float x, y, z; };
struct Quat { float x, y, z, w; };
struct V3c {
    float x, y, z;
    V3c(const V3& o) : x(o.x), y(o.y), z(o.z) {}
};
static inline float fabsf_(float v) { return (float)fabs((double)v); }
struct Viewer {
    void GetCameraRay(V3* origin, V3* dir);               // 0x007c4900 (ret 8)
};
struct AppObj_s00c6_7560 {
    P4(0) P4(1) P4(2) P4(3) P4(4)
virtual void p5a();
virtual void p5b();
    virtual Viewer* GetViewer();                          // +0x58
};
AppObj_s00c6_7560* AppGet_s00c6_7560();                                         // 0x0067dd10 (SP::App)
V3* __cdecl RotateByQuat(V3* out, const V3* v, const Quat* q);   // 0x0059aed0
float __cdecl AngleAroundAxis(const V3* a, const V3* b, const V3* axis);   // 0x006994a0 (result in st0)
struct TargetObj {
P4(0) P4(1) virtual void p2a();
virtual void p2b();
virtual void p2c();
    virtual const V3* GetPosition();                      // +0x2c
};
struct ConstrainObj {
    V3* Apply(V3* out, const V3* in);                     // 0x00c650d0 (ret 8)
};
struct Ctrl_s00c6_7560 {
    uint8_t pad00[0x34];
    TargetObj mTarget;               // +0x34
    uint8_t pad38[0x108 - 0x38];
    V3 mFocus;                       // +0x108
    uint8_t pad114[0x118 - 0x114];
    ConstrainObj mConstrain;         // +0x118
    uint8_t pad11c[0x170 - 0x11c];
    V3 mAxis;                        // +0x170
    V3 mDirRef;                      // +0x17c
    Quat mBase;                      // +0x188
    uint8_t pad198[0x1a4 - 0x198];
    Quat mOut;                       // +0x1a4
    float mScaleA;                   // +0x1b4
    uint8_t pad1b8[0x1c0 - 0x1b8];
    float mScaleB;                   // +0x1c0

    void MarkChanged();              // 0x00c66c10

    void Update();
};
// ---- items of slice s00c67560 end

// ---- items of slice s00c67560_g7 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl F7ec550(void* first, void* last, void* result);   // 0x007ec550 eastl::copy
extern "C" void  __cdecl F6a4100(void* dst, unsigned n, const void* src);  // 0x006a4100 CopyVec12
extern "C" void  __cdecl Fabced0(void* first, void* last, void* result);   // 0x00abced0 copy_backward
extern "C" void  __cdecl Fa177f0(void* first, void* last, const void* v);  // 0x00a177f0 fill
extern "C" void  __cdecl F4797a0(const void* value, void* a, void* b, void* c, void* pos);  // 0x004797a0
extern "C" void* __cdecl Ff473a0(int size, const char* name, int flags, int align,
                                 const char* file, int line);              // 0x00f473a0 operator new
extern "C" void  __cdecl Ff47380(void* p);                                 // 0x00f47380 operator delete
extern "C" void  __cdecl F6782c0(void* first, void* last, void* result);   // 0x006782c0 do_copy
extern "C" char  __cdecl Fc64400(void* a, void* b);                        // 0x00c64400 ComparePairDist
#pragma intrinsic(sqrt)
struct cGameNounManager_s00c6_7560__g7 {
    void RemoveNoun(void* noun);                                           // 0x00b225d0
};
cGameNounManager_s00c6_7560__g7* __cdecl NounManager_s00c6_7560__g7();                                   // 0x00b3d300
#define ALLOC_FILE \
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
struct Vec12 { float x, y, z; };
struct Vec12Vector {
    Vec12*   mpBegin;        // +0x00
    Vec12*   mpEnd;          // +0x04
    Vec12*   mpCapacity;     // +0x08
    uint32_t mPad0c;         // +0x0c
    Vec12*   mpInlineBuf;    // +0x10 (inline storage; never freed)

    void Insert(Vec12* pos, unsigned n, const Vec12& value);
};
struct CtrlTarget {
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
virtual void v0a();
    virtual const V3* GetPosition();                                   // +0x2c
    virtual const Quat* GetOrientation();                              // +0x30
virtual void v0d();
virtual void v0e();
virtual void v0f();
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
virtual void v1a();
virtual void v1b();
    virtual float GetSpan();                                           // +0x70
    virtual float GetSpan2();                                          // +0x74
};
struct TrackedRef {
    void*    mVtbl;          // +0x00
    uint32_t mFlags;         // +0x04
};
struct Ctrl_s00c6_7560__g7 {
    uint8_t pad00[0xd0];
    TrackedRef* mpTargetRef;         // +0xd0
    uint8_t padD4[0x198 - 0xd4];
    V3   mPos;                       // +0x198
    Quat mOut;                       // +0x1a4
    float mScale;                    // +0x1b4
    int   mState;                    // +0x1b8

    void MarkChanged();              // 0x00c640e0
    void Recompute();                // 0x00c64170
    void FlushOrientation();         // 0x00c66c10

    void Attach(CtrlTarget* target);
    void SetState(int state);
};
struct PtrVec {
    void** mpBegin;      // +0x00
    void** mpEnd;        // +0x04
    void** mpCapacity;   // +0x08
};
struct Noun {
    virtual void v00();          // +0x00
    virtual void Release();      // +0x04
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v0a();
virtual void v0b();
virtual void v0c();
virtual void v0d();
virtual void v0e();
virtual void v0f();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
    virtual void Detach(int arg);    // +0x54
};
void RemoveFromVec(PtrVec* vec, void* noun);
struct PathObj_s00c6_7560__g7 {
    uint8_t mFlag;           // +0x00
    char    pad01[3];
    void**  mpBegin;         // +0x04
    void**  mpEnd;           // +0x08
    char    pad0c[0x0c];
    V3      mV;              // +0x18 (anchor triple)

    void Fn64460(void* h);   // 0x00c64460
    void Fn68190(void* h);
    bool Fn68250(void* h);
};
extern "C" V3 g1693d74;      // 0x01693d74: anchor position
// ---- items of slice s00c67560_g7 end

// ---- items of slice s00c68280 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define VTSLOT(o, off) (*(void**)((char*)(*(void**)o) + (off)))
typedef void   (__thiscall *TFv_v)(void*);
typedef void   (__thiscall *TFv_i)(void*, int);
typedef void   (__thiscall *TFv_p)(void*, void*);
typedef char   (__thiscall *TFc_v)(void*);
typedef int    (__thiscall *TFi_v)(void*);
typedef void*  (__thiscall *TFp_i)(void*, int);
typedef char   (__thiscall *TFc_iii)(void*, int, int, void*);
struct Vector3_s00c6_8280 { float x, y, z; };
struct Vec {
    int** begin;
    int** end;
    int** cap;
    void erase(int** a, int** b);                 // 0x00e25bd0
    void F_00b05b40(int** pos, int** val);        // 0x00b05b40
    void DoInsertPtr(int** pos, int** val);       // 0x00aea5d0
};
struct Vector3Vec {
    Vector3_s00c6_8280* mpBegin;
    Vector3_s00c6_8280* mpEnd;
    Vector3_s00c6_8280* mpCapacity;
    void erase(Vector3_s00c6_8280* a, Vector3_s00c6_8280* b);           // 0x0050f740
    void DoInsertValue(Vector3_s00c6_8280* pos, Vector3_s00c6_8280* val); // 0x004b5ad0
    void push_back(Vector3_s00c6_8280* v) {
        Vector3_s00c6_8280* e = mpEnd;
        if (e < mpCapacity) {
            mpEnd = e + 1;
            if (e != 0) { e->x = v->x; e->y = v->y; e->z = v->z; }
        } else {
            DoInsertValue(e, v);
        }
    }
};
struct Elem16 { float x, y, z, w; };
struct Vec16 {
    Elem16* mpBegin;
    Elem16* mpEnd;
    Elem16* mpCapacity;
    void Resize(unsigned n);                      // 0x00c00e90
    void Grow(Elem16* pos, Elem16* val);          // 0x00c67440
};
void* __cdecl FUN_00705250(void* first, void* last, void* dst);   // 0x00705250
struct cSpatial {
    void** vt;
    float* GetPosition() {
        typedef float* (__thiscall* Fn)(cSpatial*);
        return ((Fn)vt[0x2c / 4])(this);
    }
    float* GetPositionI(int i) {
        typedef float* (__thiscall* Fn)(cSpatial*, int);
        return ((Fn)vt[0x2c / 4])(this, i);
    }
    void SetPosition(void* p) {
        ((void(__thiscall*)(cSpatial*, void*))vt[0x38 / 4])(this, p);
    }
    void F_00c421b0(void* p);                     // 0x00c421b0
    void Shutdown();                              // 0x00c43f90
};
struct CObject {
    char     pad0[0x34];
    cSpatial mSpatial;
};
struct COrnList {
    char  mFlag0;
    char  pad001[3];
    Vec   mVec;                                   // +0x04
    void Collect(Vector3Vec* dst, char* out);     // 0x00c688a0
};
struct CModelHead { char pad[4]; unsigned mFlags; };
struct cGameData {
    void* mVt0;                                   // +0x00
    void* mVt4;                                   // +0x04
    char  pad08[0x34 - 0x08];
    cGameData();                                  // 0x00b18660
    ~cGameData();                                 // 0x00b184c0
};
struct cCombatant {
    void* mVt;
    char  pad04[0xc8 - 0x04];
    cCombatant();                                 // 0x00bfd4e0
    ~cCombatant();                                // 0x00bfcd00
};
struct cSpatialObjectBase {
    void* mVt;                                    // +0x00 (= obj +0x34)
    char  pad04[0xd4 - 0x04];
    cSpatialObjectBase();                         // 0x00c89630
    ~cSpatialObjectBase();                        // 0x00c8a420
};
struct cNanoDrone : cGameData {
    cSpatialObjectBase mSpatial;                  // +0x34
    cCombatant         mCombatant;                // +0x108
    void* mp1d0;                                  // +0x1d0
    int   m1d4;                                   // +0x1d4
    cNanoDrone();                                 // 0x00c69150
    ~cNanoDrone();                                // 0x00c69290
};
struct cAgentOrderManager { void F_00bcae90(); }; // 0x00bcae90
struct COrnCombatantSlot { void* mVt; void F_00bfc720(); };  // 0x00bfc720
struct COrnTailSlot      { void* mVt; void F_00abf710(); };  // 0x00abf710
struct COrn {
    char   mByte0;                     // +0x00
    char   pad001[3];
    Vec    mVec4;                      // +0x04  noun-ref vector
    char   pad010[0x2c - 0x10];
    int*   mp2c;                       // +0x2c (interface, released in Shutdown)
    char   pad030[0x34 - 0x30];
    cSpatial mSpatial;                 // +0x34
    char   pad038[0xd0 - 0x38];
    int*   mpModel;                    // +0xd0
    char   pad0d4[0x118 - 0xd4];
    float  mPosX, mPosY, mPosZ;        // +0x118,+0x11c,+0x120
    char   mFlag124;                   // +0x124
    char   pad125[3];
    int    mKey128;                    // +0x128
    float  mF12c;                      // +0x12c
    int    mCount130;                  // +0x130 (segment count)
    int*   mVec134;                    // +0x134 (view / effect object)
    char   pad138[0x508 - 0x138];
    COrnCombatantSlot mCombatant;      // +0x508
    char   pad50c[0x5d0 - 0x50c];
    COrnTailSlot mTail;                // +0x5d0

    __declspec(noinline) void Update();  // 0xc68280
    void H3f90();                      // 0xc63f90
    void H4460(int x);                 // 0xc64460
    void E850(int* noun);              // 0xc68850
    void E930();                       // 0xc68930
    void E980(void* view);             // 0xc68980
    void Eaa0();                       // 0xc68aa0
    void Eae0(float* p);               // 0xc68ae0
    void Eb40(int key);                // 0xc68b40
    void Ebd0(float v);                // 0xc68bd0
    char Ed20(int* noun);              // 0xc68d20
    void Ed70(Vector3_s00c6_8280* pos, Vector3Vec* v); // 0xc68d70
    void F030();                       // 0xc69030
    void F090();                       // 0xc69090
    int  Ef30(int id);                 // 0xc68f30
    int  F1e0(int id);                 // 0xc691e0
    cSpatial* Spatial() { return (cSpatial*)((char*)this + 0x34); }
};
void __cdecl ClearVector(Vec* v);                 // 0xc687e0
char __cdecl FUN_00c649b0(Vec* dst, Vector3Vec* v);  // 0xc649b0
void __cdecl FUN_00ebb720(void* p, unsigned int flags);
struct IQuery {
    int QI(int id);   // 0xb18460
    int QJ(int id);   // 0xc884f0
    int QK(int id);   // 0xc41d00
    int QL(int id);   // 0xbfc380
    int QM(int id);   // 0xabf740
};
void* __cdecl FUN_0067ddd0();                     // SP::EffectsManager
void* __cdecl FUN_00b3d260();                     // SP::BehaviorManager
struct cGameNounManager_s00c6_8280 {
    int* CreateNoun(int tag);                     // 0x00b20c60
    void RemoveNoun(int* noun);                   // 0x00b225d0
};
void* __cdecl FUN_00f473a0(unsigned int size, const char* name, int a, int b, int c, int d); // 0xf473a0
struct CTexRun {
    char  pad00[0x30];
    Vec16 mVec;                       // +0x30
    void Build(unsigned count, float* pts, float* angles); // 0x00c686d0
};
struct cGroundLoco { void* mVt0; void* mVt4; void* mVt8; void* mVtC; };
// ---- items of slice s00c68280 end

// ---- items of slice s00c69300 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cGameData_s00c6_9300 {
    char Slot40(int param);       // 0x00b183f0
    void Refresh();               // 0x00c69600

    char Activate(int param);     // 0x00c697e0
};
// ---- items of slice s00c69300 end

// ---- items of slice s00c6e710 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float DAT_01471064;   // 0.5f
extern float DAT_01486374;   // 0.8f
extern float DAT_01693eac;   // 2*pi / segment
extern float DAT_015778b4;   // half-segment sweep
extern float DAT_015778b8, DAT_015778bc, DAT_015778c0; // row0 basis
extern float DAT_015778c4, DAT_015778c8, DAT_015778cc; // row1 basis
typedef unsigned int   u32;
typedef unsigned char  u8;
typedef          int   s32;
void  __cdecl operator_delete_array(void*);      // 0x00f47380
void* __cdecl SP_NounManager();                  // 0x00b3d300 SP::NounManager()
void* __cdecl FUN_00b3d350();                    // 0x00b3d350 (alias)
float __cdecl FUN_00b7f250(void* self, void* out, void* dir, void* up); // 0x00b7f250 BuildSurfaceOrientation2
float __cdecl FUN_00b7f190(void* self, void* out, void* pos); // 0x00b7f190 BuildSurfaceOrientation
void* __cdecl FUN_00b81780(void* self, void* out, void* pos, void* , void* ); // 0x00b81780 MakeRandomWorldPosition
float __cdecl FUN_00b82970(void* self, void* pos);  // 0x00b82970 cPlanetModel::SnapB
void* __cdecl FUN_00d539d0();                     // 0x00d539d0 SP::cPosseSimulator::Instance
s32   __cdecl FUN_00d52df0(void* self);           // 0x00d52df0 posse max-eggs
float __cdecl FUN_007dcb00(float* out, float* a, float* b); // 0x007dcb00 mat3 mul
float __cdecl FUN_0059aed0(void* a, void* b, void* c);      // 0x0059aed0 mat4 mul
void* __cdecl FUN_00c87660(void* self);           // 0x00c87660 cSPSpaceInventoryItem ctor
void* __cdecl FUN_00c87770(void* self);           // 0x00c87770 cSPSpaceInventoryItem dtor
bool  __cdecl FUN_00c87580(void* self);           // 0x00c87580 serialize helper
bool  __cdecl FUN_00c879a0(void* self);           // 0x00c879a0 deserialize helper
bool  __cdecl FUN_00e3aa70(void* stream, const u32* value, int count, int); // 0x00e3aa70 IO::WriteUint32
bool  __cdecl FUN_00e3a780(void* stream, void* out, int count, int);        // 0x00e3a780 IO::ReadInt32
void* __cdecl FUN_00692f90(void* self, void* a, void* b, int c); // 0x00692f90 cVarListSerializer ctor
bool  __cdecl FUN_00692900(void* self, void* stream);            // 0x00692900 Serialize (write)
bool  __cdecl FUN_00693e10(void* self, void* stream);            // 0x00693e10 Serialize (read)
extern u32   DAT_01693ea0;    // up-vector seed
// ---- items of slice s00c6e710 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void __fastcall FUN_00c6e710(void* self, void* /*edx*/, u32 count);  // 0x00c6e710 (stays in the slice: not this object's)

// ---- items of slice s00c6f6e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int    DAT_01578698;
extern void*  DAT_016c7aa4;                            // 0x016c7aa4  globals
extern void*  PTR_FUN_0146c56c;
extern void*  PTR_FUN_01466c14;
extern void*  vtbl_Simulator_cOrnament;
extern void*  PTR_AddRef_01472180;
extern void*  PTR_FUN_0147216c;
extern void*  PTR_FUN_01472160;
extern void*  PTR_FUN_0147213c;
extern void*  PTR_FUN_01472120;
extern void*  PTR_FUN_014720b8;
extern void*  PTR_AddRef_014722d8;
extern void*  PTR_FUN_014722c4;
extern void*  vtbl_cPlaceholderColonyEditorCursorAttachment;
extern void*  FUN_00b1e500;
extern void*  FUN_00acdff0;
extern void*  FUN_00d3d420;
extern void*  FUN_00cd7d10;
extern void*  DAT_018c43e8;
typedef unsigned char  uchar;
struct WorldObject;
void* __cdecl FUN_00c884f0(void* id);                 // 0xc884f0  Simulator::cSpatialObject::Cast
void* __cdecl FUN_00bfc380(void* id);                 // 0xbfc380
void* __cdecl FUN_00b18460(void* id);                 // 0xb18460  (class-id dispatch)
void* __cdecl FUN_00c751c0(void* id);                 // 0xc751c0
void* __cdecl FUN_00b3d350(void* pId);               // 0xb3d350  SP::PlanetModel
void  __cdecl FUN_00b83c40(void* model, float a, int b, int c); // 0xb83c40  SP::cPlanetModel::FUN_00b83c40
void* __cdecl FUN_00b21340(void* mgr, void* a, void* b, void* c, void* d, void* e); // 0xb21340 GetGameDataVector
void* __cdecl FUN_00ac9310(void* a, void* b, void* c); // 0xac9310
void* __cdecl FUN_00bd9710(void* a);                  // 0xbd9710
void* __cdecl FUN_00b18530(void* pSelf);              // 0xb18530  SP::cGameData
void* __cdecl FUN_00b18590(void* a, void* b);         // 0xb18590  SP::cGameData::Write
void* __cdecl FUN_00c88a90(void* a, void* b);         // 0xc88a90  Simulator::cSpatialObject::Write
void* __cdecl FUN_00692f90(void* a, void* b, void* c, void* d); // 0x692f90 cVarListSerializer::cVarListSerializer
void* __cdecl FUN_00692900_s00c6_f6e0(void* a, void* b);         // 0x692900 cVarListSerializer::Serialize
void* __cdecl FUN_0093aa70(void* a, void* b, void* c, void* d); // 0x93aa70 EA::IO::WriteUint32
void* __cdecl FUN_00ac0450(void* self);               // 0xac0450
void* __cdecl FUN_00c8b2e0(void* self);                // 0xc8b2e0  Simulator::cSpatialObject
void* __cdecl FUN_00c8a550(void* a, void* b);         // 0xc8a550  Simulator::cSpatialObject::LoadModel
void* __cdecl FUN_00c884f0(void* self, unsigned type); // 0xc884f0  Simulator::cSpatialObject::Cast
void* __cdecl FUN_00bfc380(void* self, unsigned type); // 0xbfc380  cCombatant::Cast
void* __cdecl FUN_00b18460(void* self, unsigned type); // 0xb18460  cGameData::Cast
void* __cdecl FUN_00c751c0(void* self, unsigned type); // 0xc751c0  cast at +0x144
int   __cdecl FUN_00b1f9d0(void* mgr);                // 0xb1f9d0  GetPlayerEmpireOrMinus1 (this=mgr)
WorldObject* __cdecl FUN_00b8de30_s00c6_f6e0(void* a);           // 0xb8de30 (free form used by Func6fe50)
void* __cdecl FUN_00bb9ae0(void* a);                  // 0xbb9ae0
void* __cdecl FUN_00b1fdb0(void* a);                  // 0xb1fdb0  cGameNounManager::GetAvatar
void* __cdecl FUN_00b3d2a0(void* a);                  // 0xb3d2a0  SP::StarManager
void* __cdecl FUN_00ba9370(void* a);                  // 0xba9370  cStarManager::GetEmpireByID
void* __cdecl FUN_00c31730(void* a);                  // 0xc31730  cEmpire::GetHomePlanet
static void* vc(void* obj, int off) { return ((void**)*(void**)obj)[off / 4]; }
struct SimOrnament {
    uchar pad_000[0x2c];
    void* mpRefCount_2c;       // 0x2c  refcounted object released in Destroy
    uchar pad_030[0x4];
    void* mpVftbl_34;          // 0x34
    int   mPowerupType_38;     // 0x38
    int   mInstanceID_3c;      // 0x3c
    int   mTypeID_40;          // 0x40
    int   mGroupID_44;         // 0x44
    bool  mbField_48;          // 0x48
    void* mpPropList_4c;       // 0x4c
    void* mpField20_50;        // 0x50
    void* mpField1c_54;        // 0x54
    uchar pad_058[0x0c];
    bool  mbHasBeenThrown_64;  // 0x64
    float mTimeInFlight_68;    // 0x68
    void* mpThrowObjective_6c; // 0x6c
    uchar mSpatial_70[0xa6];   // 0x70..0x116  cSpatialObject sub-object (part)
    bool  mbField_116;         // 0x116
    uchar mSpatial_b_117[0x2d];// 0x117..0x144 cSpatialObject sub-object (rest)
    void* mpVftbl_144;         // 0x144
    uchar mCombatant_148[0xc8];// 0x148..0x210  cCombatant sub-object
    uchar mIntTarget_210[0x18];// 0x210..0x228  cInteractionTarget sub-object
    int   mStyle_228;          // 0x228
    int   mModelID_22c;        // 0x22c
    bool  mbVisible_230;       // 0x230

    void* Cast(unsigned type);                       // 0x00c6f6e0
    void  SetStyleModel(int style, void* a, int model); // 0x00c6f770
    bool  IsPlayerOwned();                           // 0x00c6f7b0
    SimOrnament();                                   // 0x00c6f7f0
    bool  Write(void* pArchive);                     // 0x00c6f990
    void  Destroy();                                 // 0x00c6fac0
};
struct SimCursorAttachment {
    uchar mGameData_000[0x2c]; // 0x00..0x2c cGameData
    void* mpRefCount_2c;       // 0x2c  AutoRefCount target
    uchar pad_030[0x4];
    uchar mSpatial_34[0x2c];   // 0x34..0x60 cSpatialObject

    SimCursorAttachment();                           // 0x00c6fcd0
    void* Cast(unsigned type);                       // 0x00c6fd20
    void  Destroy();                                 // 0x00c6fdc0
};
struct SimSpatial {
    uchar      pad_000[0x1b8];
    int        mStyle_1b8;          // 0x1b8  (== ornament +0x228)
    uchar      pad_1bc[0x3c];

    bool IsPlayerOwnedOrnament();                    // 0x00c6f7b0
    bool LoadModelOrnament(void* pModel);            // 0x00c6fb80
};
struct WorldObject {                    // the `b8de30`/`b8dab0`/`b8dad0` result
    uchar      pad_000[0x3c];
    void**     mpVec3c_3c;              // 0x3c  vector<X*>::begin
    void**     mpVec3c_40;              // 0x40  vector<X*>::end
    uchar      pad_044[0x40];
    int        mPlayerID_84;            // 0x84
    void  Func70860();                  // 0xb8de30 -> later vtable call
    int   GetType();                    // 0xbb9ae0
    void  SetSomething(void* a);        // 0xbb9b90
};
struct VarListSerializer { uchar mData_000[0xa14]; };
struct GameDataBase_s00c6_f6e0 { void ctor(); };              // 0xb18660
struct SpatialBase_s00c6_f6e0  { void ctor(); };              // 0xc89630
struct CombatantBase{ void ctor(); };              // 0xbfd4e0
struct IntTargetBase{ void ctor(); };              // 0xac03d0
// ---- items of slice s00c6f6e0 end

// @ 0x00c60850
void cSPMissionTerraform::OnTerraformSphereChange(int param)
{
    switch (param) {
    case 1: {
        if (!IsActive())
            return;
        if (GetTargetPlanet() != GetActivePlanet())
            return;
        cTerrainSphere* pSphere = NounManager()->GetCurrentTerrainSphere();
        if (pSphere == 0)
            return;
        if (pSphere->FUN_00c772c0(0x6626789))
            return;
        FUN_010666a0()->FUN_0106ab20(3);
        pSphere->FUN_00c77bf0(0x6626789);
        FUN_010666a0()->FUN_0106dcd0(0x3a90f931);
        break;
    }
    }
}

// @ 0x00c608d0
void cSPMissionTerraform::RegisterMessages()
{
    FUN_00c44b80();
    Vtbl()->AddMessageHandler(kMsgTerraformStep);
    Vtbl()->AddMessageHandler(kMsgTerraformSubStepA);
    Vtbl()->AddMessageHandler(kMsgTerraformSubStepB);
    Vtbl()->AddMessageHandler(0x43f2583);
    Vtbl()->AddMessageHandler(0x490d429);
}

// @ 0x00c60930
void cSPMissionTerraform::UnregisterMessages()
{
    FUN_00c44bd0();
    Vtbl()->RemoveMessageHandler(kMsgTerraformStep);
    Vtbl()->RemoveMessageHandler(kMsgTerraformSubStepA);
    Vtbl()->RemoveMessageHandler(kMsgTerraformSubStepB);
    Vtbl()->RemoveMessageHandler(0x43f2583);
    Vtbl()->RemoveMessageHandler(0x490d429);
}

// @ 0x00c61070
void cSPMissionTerraform::GetUITitle(wstring* pOut)
{
    if (mUITitle.IsEmpty() && mMissionTypeKey == 0xd85005e9) {
        switch (mTerraformState) {
        case 0:
            if (mFlag1F4) {
                GetText(0x2fd4e76a, pOut);
                mUITitle = *pOut;
                return;
            }
            if (GetUniverseContext() == 1) {
                if (GetActivePlanetRecord() != 0) {
                    void* pRecord = GetTargetPlanet() != 0 ?
                                    GetTargetPlanet()->mpStarRecord : 0;
                    if (GetActivePlanetRecord() == pRecord) {
                        GetText(0x791cfa76, pOut);
                        mUITitle = *pOut;
                        return;
                    }
                }
                int archived = IsArchivedMission();
                void* pRecord = GetTargetPlanet() != 0 ?
                                FUN_00b8de30(GetTargetPlanet()->mpStarRecord) : 0;
                if (archived != 0 && archived == (int)(size_t)pRecord) {
                    GetText(0x639f0b00, pOut);
                    mUITitle = *pOut;
                    return;
                }
            } else if (GetUniverseContext() == 0) {
                if (GetActivePlanetRecord() != 0) {
                    void* pRecord = GetTargetPlanet() != 0 ?
                                    GetTargetPlanet()->mpStarRecord : 0;
                    if (GetActivePlanetRecord() == pRecord) {
                        GetText(0xdf81d02e, pOut);
                        mUITitle = *pOut;
                        return;
                    }
                }
            }
            break;
        case 1:
            if (GetUniverseContext() == 0) {
                if (GetActivePlanetRecord() != 0) {
                    void* pRecord = GetTargetPlanet() != 0 ?
                                    GetTargetPlanet()->mpStarRecord : 0;
                    if (GetActivePlanetRecord() == pRecord) {
                        GetText(0x14dae625, pOut);
                        mUITitle = *pOut;
                        return;
                    }
                }
            }
            break;
        case 2:
            if (GetUniverseContext() == 0) {
                if (GetActivePlanetRecord() != 0) {
                    void* pRecord = GetTargetPlanet() != 0 ?
                                    GetTargetPlanet()->mpStarRecord : 0;
                    if (GetActivePlanetRecord() == pRecord) {
                        GetText(0xe050be3a, pOut);
                        mUITitle = *pOut;
                        return;
                    }
                }
            }
            break;
        case 3:
            if (mFlag1F5) {
                GetText(0x8c5de162, pOut);
                mUITitle = *pOut;
                return;
            }
            GetText(0xc1f54b2f, pOut);
            mUITitle = *pOut;
            return;
        }
    }
    cSPMission::GetUITitle(pOut);
}

// @ 0x00c61390
void Mission::FUN_00c61390(int arg)
{
    void* planet = this->FUN_0970b30();
    void* active = FUN_01021260();
    if (active != planet)
        return;
    if (FUN_01021080() != 0)
        return;

    void* nm = FUN_00b3d300();
    void* vec = ((Mission*)nm)->FUN_00b21340(
        0x00cd7d10, 0x00d3d420, 0x00acdff0, 0x00b1e500, 0x018c43e8);
    int local[5];
    ((Mission*)local)->FUN_00ba95a0((char*)vec + 4);
    int* begin = (int*)local[0];
    int* end = (int*)local[1];

    for (int* it = begin; it != end; it++)
        if (*it)
            ((Mission*)*it)->FUN_00bdc4a0(arg);
    for (int* it = begin; it < end; it++)
        if (*it)
            VTV((void*)*it, 4);
    if (begin != 0 && begin[-1] != 0)
        FUN_00f47380(begin);
}

// @ 0x00c61450
void Mission::FUN_00c61450(int msg, int arg)
{
    switch (msg) {
    case 0x248975f:
        if (*(int*)((char*)this + 0x44) != (int)0xd85005e9)
            goto handle;
        if (*(int*)((char*)this + 0x1bc) == 0)
            ((Mission*)((char*)this - 0x34))->FUN_00c46160();
        goto lab_14a9;
    case 0x2489766:
    case 0x248976a:
    case 0x490d429:
        goto lab_1514;
    case 0x43f2583:
        goto lab_14a9;
    default:
        goto handle;
    }

lab_1514:
    if (*(int*)((char*)this + 0x44) == (int)0xd85005e9) {
        Mission* p = (Mission*)((char*)this - 0x34);
        if (VTC(p, 0xf8) == 0)
            p->FUN_00c47d80();
    }
    goto handle;

lab_14a9:
    if (*(int*)((char*)this + 0x44) == (int)0xd85005e9) {
        Mission* p = (Mission*)((char*)this - 0x34);
        void* planet = p->FUN_0970b30();
        if (FUN_01021260() == planet) {
            if (VTC(p, 0xf8) == 0) {
                p->FUN_00c47d80();
                p->FUN_00c61390(*(int*)((char*)this + 0x1bc) == 3);
            }
        }
    }
handle:
    this->FUN_00c4a6b0(msg, arg);
}

// @ 0x00c61550
void Mission::FUN_00c61550()
{
    this->FUN_00c46590();
    this->FUN_00c61390(0);
}

// @ 0x00c61570
void Mission::FUN_00c61570()
{
    if (*(int*)((char*)this + 0x1f0) == 4)
        return;
    VTV(this, 0x6c);
    if (*(int*)((char*)this + 0x1f0) != 4) {
        if (*(int*)((char*)this + 0x78) == (int)0xd85005e9)
            this->FUN_00c61390(0);
        *(int*)((char*)this + 0x1f0) = 4;
        this->FUN_00c47d80();
    }
    this->FUN_00c472e0();
    this->FUN_00c471c0();
}

// @ 0x00c61bb0
void* Mission::FUN_00c61bb0()
{
    this->FUN_00c48e90();
    *(int*)((char*)this + 0x1f0) = 0;
    *(int*)((char*)this + 0x1f4) = 0;
    *(int*)((char*)this + 0x1f8) = 0;
    *(void**)((char*)this + 0) = (void*)0x01470330;
    *(void**)((char*)this + 4) = (void*)0x0146dfb4;
    *(void**)((char*)this + 0x34) = (void*)0x01470320;
    return this;
}

// @ 0x00c61d70
char Mission::FUN_00c61d70()
{
    if (!this->FUN_00c4ad50())
        return 0;
    FUN_006a12a0(*(void**)((char*)this + 0x180), 0x6d03cf73,
                 (char*)this + 0x1f4);
    void* gd = ((Mission*)FUN_01002bd0())->FUN_00bfc5f0();
    *(int*)((char*)this + 0x1f8) =
        ((Mission*)gd)->FUN_00fe6770(*(int*)((char*)this + 0x1f4));
    this->FUN_00c4a0c0();
    return 1;
}

// @ 0x00c61dd0
int Mission::FUN_00c61dd0(int param)
{
    int rc = this->FUN_00c478b0(param);
    if (VTC(this, 0xf8) == 0) {
        if (((Mission*)((Mission*)FUN_01002bd0())->FUN_00bfc5f0())->
                FUN_00fe4180(*(int*)((char*)this + 0x1f4)))
            this->FUN_00c4b760();
    }
    return rc;
}

// @ 0x00c61e20
void Mission::FUN_00c61e20(int msg, int arg)
{
    int* pa = (int*)arg;
    switch (msg) {
    case 0x038cf2fb:
        ((Mission*)((char*)this - 0x34))->FUN_00c47d80();
        break;
    case 0x038cf2fc:
        if (pa[2] == *(int*)((char*)this + 0x1c0)) {
            ((Mission*)((char*)this - 0x34))->FUN_00c4b760();
            this->FUN_00c4a6b0(msg, arg);
            return;
        }
        break;
    }
    this->FUN_00c4a6b0(msg, arg);
}

// @ 0x00c61e80
char Mission::FUN_00c61e80(int msg, int out)
{
    void* gd = ((Mission*)FUN_01002bd0())->FUN_00bfc5f0();
    if (msg == (int)0xe58ee16c) {
        FUN_0041e050((void*)out, (const void*)0x013f01bc,
                     *(int*)((char*)this + 0x1f8));
        return 1;
    }
    if (msg == (int)0xd4814edd) {
        int a = ((Mission*)gd)->FUN_00fe6770(*(int*)((char*)this + 0x1f4));
        int b = ((Mission*)gd)->FUN_00fe66f0(*(int*)((char*)this + 0x1f4));
        FUN_0041e050((void*)out, (const void*)0x013f01bc, a - b);
        return 1;
    }
    return this->FUN_00c491c0(msg, out);
}

// @ 0x00c61f20
void* Mission::FUN_00c61f20()
{
    this->FUN_00c48e90();
    *(int*)((char*)this + 0x1f0) = 0;
    *(int*)((char*)this + 0x1f4) = 0;
    *(int*)((char*)this + 0x1f8) = 0;
    *(uint8*)((char*)this + 0x1fc) = 0;
    *(uint8*)((char*)this + 0x1fd) = 0;
    *(void**)((char*)this + 0) = (void*)0x01470540;
    *(void**)((char*)this + 4) = (void*)0x0146dfb4;
    *(void**)((char*)this + 0x34) = (void*)0x01470530;
    return this;
}

// @ 0x00c620c0
int Mission::FUN_00c620c0(int tag)
{
    int id = *(int*)((char*)this + 0x1f4);
    switch (id) {
    case 0x082af541:
        return tag == 0x082af541;
    case 0x7ecbe6f5:
        return tag == 0x7ecbe6f5;
    }
    return id & 0xffffff00;
}

// @ 0x00c62100
void Mission::FUN_00c62100()
{
    if (*(int*)((char*)this + 0x1f0) != 0)
        return;
    VTV(this, 0x6c);
    if (*(int*)((char*)this + 0x1f0) != 1) {
        *(int*)((char*)this + 0x1f0) = 1;
        this->FUN_00c47d80();
    }
    this->FUN_00c472e0();
    this->FUN_00c471c0();
    if (*(int*)((char*)this + 0x78) == (int)0xdec64aa7) {
        ((Mission*)FUN_00b3d3e0())->FUN_00dd8640(
            0xe737105a, 0x131a9f54, 0, 0, 1, 0);
    }
}

// @ 0x00c62180
void Mission::FUN_00c62180(int* a, int* b)
{
    void* obj = *(void**)((char*)this + 0x180);
    int k1[3] = {0, 0, 0};
    if (FUN_006a1250(obj, 0x6d03cf71, k1))
        *a = k1[0];
    void* obj2 = *(void**)((char*)this + 0x180);
    int k2[3] = {0, 0, 0};
    if (FUN_006a1250(obj2, 0x6d03cf72, k2))
        *b = k2[0];
}

// @ 0x00c62200
char Mission::FUN_00c62200()
{
    if (!this->FUN_00c4ad50())
        return 0;
    VTV(this, 0x16c);
    this->FUN_00c62180((int*)((char*)this + 0x1f4),
                       (int*)((char*)this + 0x1f8));
    this->FUN_00c4a0c0();
    VTV(this, 0x170);
    return 1;
}

// @ 0x00c62250
void Mission::FUN_00c62250(int msg, int arg)
{
    if (msg == (int)0xf46092c1 && *(int*)((char*)this + 0x1bc) == 0) {
        int v1 = *(int*)(arg + 8);
        void* v2 = *(void**)(arg + 0x28);
        void* v3 = *(void**)(arg + 0x10);
        char ok = 1;
        if (*(int*)((char*)this + 0x44) == (int)0xdec64aa7) {
            void* p = ((Mission*)FUN_00b3d2a0())->FUN_00ba6dc0((int)v2);
            if (p != 0) {
                void* av = ((Mission*)p)->FUN_00b8de30();
                av = ((Mission*)av)->FUN_00b1fdb0();
                int pid = (int)FUN_01021090();
                ok = (av != (void*)pid);
            }
        }
        if (((Mission*)((char*)this - 0x34))->FUN_00c620c0((int)v3) && ok) {
            if (v1 == 0)
                *(uint8*)((char*)this + 0x1c9) = 1;
            else
                *(uint8*)((char*)this + 0x1c8) = 1;
        }
        switch (*(int*)((char*)this + 0x1c4)) {
        case 0x2a99c94f:
            if (*(uint8*)((char*)this + 0x1c8))
                goto do_update;
            break;
        case 0x8f063c70:
            if (*(uint8*)((char*)this + 0x1c8))
                goto do_update;
            if (*(uint8*)((char*)this + 0x1c9))
                goto do_update;
            break;
        case 0x31e0a061:
            if (*(uint8*)((char*)this + 0x1c9))
                goto do_update;
            break;
        case 0x52f6f862:
            if (!*(uint8*)((char*)this + 0x1c8))
                goto handle;
            if (*(uint8*)((char*)this + 0x1c9))
                goto do_update;
            break;
        }
    }
handle:
    this->FUN_00c4a6b0(msg, arg);
    return;
do_update:
    ((Mission*)((char*)this - 0x34))->FUN_00c62100();
    this->FUN_00c4a6b0(msg, arg);
}

// @ 0x00c62370
void* Mission::FUN_00c62370()
{
    this->FUN_00c48e90();
    *(int*)((char*)this + 0x1f0) = 0;
    *(uint8*)((char*)this + 0x1f4) = 0;
    *(void**)((char*)this + 0) = (void*)0x01470758;
    *(void**)((char*)this + 4) = (void*)0x0146dfb4;
    *(void**)((char*)this + 0x34) = (void*)0x01470748;
    return this;
}

// @ 0x00c624c0
char Mission::FUN_00c624c0()
{
    if (!this->FUN_00c4ad50())
        return 0;
    if (!VTC(this, 0x128))
        return 0;
    this->FUN_00c4a0c0();
    VTV(this, 0x170);
    return 1;
}

// @ 0x00c62540
int Mission::FUN_00c62540(int param)
{
    if (*(uint8*)((char*)this + 0x1f4) != 0) {
        void* cm = FUN_00b3d4a0();
        if (!((Mission*)cm)->FUN_00ae9390()) {
            *(uint8*)((char*)this + 0x1f4) = 0;
            FUN_01041c50("SPG_TutorialTradeRoute", 0xf6691319, 1);
        }
    }
    return this->FUN_00c478b0(param);
}

// @ 0x00c62590
void Mission::FUN_00c62590(int msg, int arg)
{
    if (msg == (int)0xf46092d1 && *(int*)((char*)this + 0x1bc) == 0) {
        int a = *(int*)(arg + 0x20);
        int b = *(int*)(arg + 0x18);
        int pid = (int)FUN_01021090();
        if (b == pid || a == pid) {
            ((Mission*)((char*)this - 0x34))->FUN_00c4b760();
            unsigned u = *(unsigned*)((char*)this + 0xfc);
            if ((u >> 3) & 1)
                *(uint8*)((char*)this + 0x1c0) = 1;
        }
    }
    this->FUN_00c4a6b0(msg, arg);
}

// @ 0x00c62710
int Mission::FUN_00c62710()
{
    int n = *(int*)((char*)this + 0x20c) - *(int*)((char*)this + 0x208);
    int result = 0;
    int i = 0;
    if (n > 0) {
        const char* flags = (const char*)*(int*)((char*)this + 0x208);
        for (; i < n; i++) {
            if (flags[i] == 0) {
                result = *(int*)(*(int*)((char*)this + 0x1f4) + i * 12);
                break;
            }
        }
    }
    return result;
}

// @ 0x00c62750
void Mission::FUN_00c62750(int msg, int arg)
{
    if (msg == 0x056690bb && *(int*)((char*)this + 0x1bc) == 0) {
        int* rec = *(int**)(arg + 8);
        int n = (*(int*)((char*)this + 0x1c4) - *(int*)((char*)this + 0x1c0)) / 12;
        char found = 0;
        int i;
        for (i = 0; i < n; i++) {
            int* p = (int*)(*(int*)((char*)this + 0x1c0) + i * 12);
            if (p[0] == rec[0] && p[1] == rec[1] && p[2] == rec[2]) {
                *(uint8*)(*(int*)((char*)this + 0x1d4) + i) = 1;
                found = 1;
            }
        }
        if (found) {
            Mission* m = (Mission*)((char*)this - 0x34);
            m->FUN_00c47d80();
            n = (*(int*)((char*)this + 0x1c4) - *(int*)((char*)this + 0x1c0)) / 12;
            for (i = 0; i < n; i++) {
                if (*(uint8*)(*(int*)((char*)this + 0x1d4) + i) == 0)
                    goto handle;
            }
            if (*(int*)((char*)m + 0x1f0) == 0) {
                VTV(m, 0x6c);
                if (*(int*)((char*)m + 0x1f0) != 1) {
                    *(int*)((char*)m + 0x1f0) = 1;
                    m->FUN_00c47d80();
                }
                m->FUN_00c472e0();
                m->FUN_00c471c0();
            }
        }
    }
handle:
    this->FUN_00c4a6b0(msg, arg);
}

// @ 0x00c62880
void* __fastcall cMissionUseTool_ctor(void* self, int _e)
{
  ((MissionBase*)self)->BaseCtor();
  *(int*)((char*)self + 0x1f0) = 0;
  *(void**)self = (void*)0x1470970;
  *(void**)((char*)self + 4) = (void*)0x1470960;
  *(void**)((char*)self + 0x34) = (void*)0x1470950;
  *(int*)((char*)self + 0x1f4) = 0;
  *(int*)((char*)self + 0x1f8) = 0;
  *(int*)((char*)self + 0x1fc) = 0;
  *(int*)((char*)self + 0x208) = 0;
  *(int*)((char*)self + 0x20c) = 0;
  *(int*)((char*)self + 0x210) = 0;
  return self;
}

// @ 0x00c62930
void* __fastcall cMissionUseTool_dtor(void* self, int _e, uint8_t del)
{
  void* p = *(void**)((char*)self + 0x208);
  if (p && *(int*)((char*)p - 4) != 0) operator_delete__(p);
  p = *(void**)((char*)self + 0x1f4);
  if (p && *(int*)((char*)p - 4) != 0) operator_delete__(p);
  ((MissionBase*)self)->BaseDtor();
  if (del & 1) operator_delete__(self);
  return self;
}

// @ 0x00c62990
uint32_t __fastcall M_C62990(void* self, int _e, int key, void* out)
{
  if (key == (int)0x581c7d4c) {
    void* obj = ((void*(__cdecl*)())0x00c62710)();
    if (obj) {
      void* pm = ((void*(__cdecl*)())0x0067de30)();
      void* list = 0;
      ((void(__thiscall*)(void*, void*, int, void**))Vt(pm)[0x2c/4])(pm, obj, 0x30608f0b, &list);

      CString16 cstr;
      ((void(__thiscall*)(void*))0x006b5060)(&cstr);
      ((void(__cdecl*)(void*, int, void*))0x006a1360)(list, 0x3068d95d, &cstr);

      const wchar_t* text = ((const wchar_t*(__thiscall*)(void*))0x006b55c0)(&cstr);
      WString12 local = { 0, 0, 0 };
      ((void(__thiscall*)(void*, const wchar_t*))0x00579a90)(&local, text);

      if (out != &local)
        ((void(__thiscall*)(void*, void*, void*))0x00423650)(out, local.mBegin, local.mEnd);

      int bytes = (int)((char*)local.mEnd - (char*)local.mBegin) & ~1;
      if (bytes > 2 && local.mBegin)
        ((void(__cdecl*)(void*))0x00f47380)(local.mBegin);

      ((void(__thiscall*)(void*))0x006b5240)(&cstr);
      return 1;
    }
  }
  return ((uint32_t(__thiscall*)(void*, int, void*))0x00c491c0)(self, key, out);
}

// @ 0x00c62cc0
void* __fastcall cMissionWar_ctor(void* self, int _e)
{
  ((MissionBase*)self)->BaseCtor();
  *(int*)((char*)self + 0x1f0) = 0;
  *(int*)((char*)self + 0x1f4) = 0;
  *(uint8_t*)((char*)self + 0x1fc) = 0;
  *(void**)self = (void*)0x1470b88;
  *(void**)((char*)self + 4) = (void*)0x146dfb4;
  *(void**)((char*)self + 0x34) = (void*)0x1470b74;
  *(int*)((char*)self + 0x1f8) = -1;
  return self;
}

// @ 0x00c637b0
void __fastcall M_C637b0(void* self, int _e, int msg, void* data)
{
  MissionWar* w = (MissionWar*)((char*)self - 0x34);
  MsgData* d = (MsgData*)data;

  if (msg == 0x2489766) {
    ((void(__thiscall*)(void*))0x00c47d80)(w);
  } else if (msg == 0x248975f) {
    void* planet = d->mPtr10;
    if (planet == ((void*(__thiscall*)(void*))0x00970b30)(w)) {
      if (w->mProgressMax == -1)
        w->mProgressMax = ((int(__thiscall*)(void*))0x00c635c0)(w);
      if (!w->mFlag) {
        char tmp[16] = { 0 };
        ((void(__thiscall*)(void*, int, void*))0x0057ed80)(tmp, 0x1470d50, data);
        void* game = ((void*(__cdecl*)())0x01002bd0)();
        ((void(__thiscall*)(void*, int, int, int, int, int, int))0x0100a7c0)(
            game, 0x5fa70d2, 1, 0, 0, 0, 0);
      }
    }
    ((void(__thiscall*)(void*))0x00c47d80)(w);
  } else if (msg == 0x2489760) {
    void* planet = d->mPtr08;
    if (planet == ((void*(__thiscall*)(void*))0x00970b30)(w))
      ((void(__thiscall*)(void*))0x00c44f20)(w);
    ((void(__thiscall*)(void*))0x00c47d80)(w);
  } else if (msg == 0x3337cbb && w->mState == 0) {
    void* target = ((void*(__thiscall*)(void*))0x00970b30)(w);
    if (((void*(__cdecl*)())0x01021260)() == target && d->mPtr08) {
      void* obj = d->mPtr08;
      void* v = ((void*(__thiscall*)(void*, int))Vt(obj)[0xc/4])(obj, 0xee9b2232);
      if (v) {
        if (w->mFlag) {
          ((void(__thiscall*)(void*))0x00c63130)(w);
        } else {
          void* empire = ((void*(__thiscall*)(void*))0x00c452a0)(w);
          int empireId = *(int*)((char*)empire + 0x84);
          if (((int(__thiscall*)(void*))Vt(v)[0x4c/4])(v) == empireId) {
            w->mProgress++;
            void* nm = ((void*(__cdecl*)())0x00b3d300)();
            void* vec = ((void*(__thiscall*)(void*))0x00ace2c0)(nm);
            void** begin = *(void***)vec;
            void** end = *(void***)((char*)vec + 4);
            char other = 0;
            for (void** p = begin; p != end; p++) {
              void* o = *p;
              if (o != v &&
                  ((int(__thiscall*)(void*))Vt(o)[0x4c/4])(o) == empireId) {
                other = 1;
                break;
              }
            }
            if (!other) ((void(__thiscall*)(void*))0x00c631b0)(w);
            ((void(__thiscall*)(void*))0x00c47d80)(w);
          }
        }
      }
    }
  }

  ((void(__thiscall*)(void*, int, void*))0x00c4a6b0)(self, msg, data);
}

// @ 0x00c639a0
void* Adj::Adjust0(void* id)
{
  if (id == (void*)0x1186577) return this ? (char*)this + 0x34 : 0;
  if (id == (void*)0x7a309fb) return this;
  return ((NounIdHelper*)this)->Dispatch(id);
}

// @ 0x00c639d0
void* Adj::Adjust1(void* id)
{
  if (id == (void*)0x76c67df || id == (void*)0x7a309fb) return this;
  if (id == (void*)0x1186577) return this ? (char*)this + 0x34 : 0;
  return ((NounIdHelper*)this)->Dispatch(id);
}

// @ 0x00c63a10
void FUN_00c63a10()
{ FUN_00ebb720(0, 0); }

// @ 0x00c63a20
void* Adj::Adjust2(void* id)
{
  if (id == (void*)0x771ad6a || id == (void*)0x7a309fb) return this;
  if (id == (void*)0x1186577) return this ? (char*)this + 0x34 : 0;
  return ((NounIdHelper*)this)->Dispatch(id);
}

// @ 0x00c63a60
void* MorphA::QueryInterface(unsigned id)
{
    if (id == 0x7a81824)
        return this;
    if (id == 0x1186577)
        return this ? (char*)this + 0x34 : 0;
    return (id == 0x7a309fb) ? (void*)this : ((MorphCastHelper*)this)->FUN_00b18460(id);
}

// @ 0x00c63aa0
void * SP::cSPMissionBase::AsInterface(EA::COM::InterfaceId id)
{
    if (id == 0x7abdd8d)
        return this;
    if (id == 0x1186577)
        return this ? (char*)this + 0x34 : 0;
    return (id == 0x7a309fb) ? (void*)this : ((MorphCastHelper*)this)->FUN_00b18460(id);
}

// @ 0x00c63ae0
void HandleThing::Fn()
{
    VObj* p = (VObj*)((char*)this + 0x34);
    if (mEn)
        p->v40(mC * mA + mB);
    else
        p->v40(1.0f);
}

// @ 0x00c63b20
void MorphInit::Init()
{
    mA = gMorphData18;
    mB = gMorphData1c;
    mC = gMorphData20;
    mFlag = 0;
}

// @ 0x00c63b40
char ComparePair(void* a, void* b, void* c)
{
    float r = QuaternionSlerp(((VObj*)((char*)c + 0x34))->v2c(), b,
                              ((VObj*)((char*)a + 0x34))->v2c());
    if (r > 2.0f)
        return 0;
    return 1;
}

// @ 0x00c63b90
void CopyPair(void* a, void* b)
{
    QuaternionSlerpVoid(((VObj*)((char*)a + 0x34))->v2c(),
                        (char*)b + 0x118,
                        ((VObj*)((char*)b + 0x34))->v2c());
}

// @ 0x00c63be0
cMorphHandle::cMorphHandle()
{
    ((GameDataBase*)this)->ctorGameData();
    ((SpatialBase*)&mpVtblSpatial)->ctorSpatialObject();
    _ReadWriteBarrier();
    mpVtbl = (void*)kVtblMorph0;
    _ReadWriteBarrier();
    mpVtbl04 = (void*)kVtblMorph1;
    _ReadWriteBarrier();
    mpVtblSpatial = (void*)kVtblMorphSp;
    _ReadWriteBarrier();
    mF108 = 0.0f;
    _ReadWriteBarrier();
    mF10c = 0.0f;
    _ReadWriteBarrier();
    mF110 = 0.0f;
    _ReadWriteBarrier();
    mB114 = 1;
    _ReadWriteBarrier();
    mB115 = 1;
    _ReadWriteBarrier();
    mVis = 0;
}

// @ 0x00c63c40
void cGameDataThing::RemoveOwnerFn(int owner)
{
    ((GameDataBase2*)this)->RemoveOwner(owner);
    int* p = mpObj;
    if (p) {
        int tmp[3];
        int* r = FUN_00eedba0(tmp, (char*)this - 0x34);
        *(int*)((char*)p + 0x4c) = r[0];
        *(int*)((char*)p + 0x50) = r[1];
        *(int*)((char*)p + 0x54) = r[2];
    }
}

// @ 0x00c63c90
void FlagHolder::SetFlag(int v)
{
    int* p = mp;
    if (p) {
        if (v)
            p[1] |= 1;
        else
            p[1] &= ~1;
    }
}

// @ 0x00c63cb0
void Kin::Fn63cb0()
{
    char* self = (char*)this;
    float f;
    CtxOut out;
    float v2[3];
    float v1[3];
    ((ViewCtx*)((AppObj2*)SP_App())->v58(v1, v2))->Update();
    memset(&out, 0, 22);
    int t = *(int*)(self + 0xd0);
    if (((CtxD4*)*(void**)(self + 0xd4))->s44(v1, v2, (void*)t, &f, &out)) {
        out.a = v1[0] + (v2[0] - v1[0]) * f;
        out.b = v1[1] + (v2[1] - v1[1]) * f;
        out.c = v1[2] + (v2[2] - v1[2]) * f;
        float* p = (float*)((VObj*)(self + 0x34))->v2c();
        *(float*)(self + 0x108) = p[0] - out.a;
        *(float*)(self + 0x10c) = p[1] - out.b;
        *(float*)(self + 0x110) = p[2] - out.c;
    }
}

// @ 0x00c63dd0
void cMorphHandle::Offset(float* p, int a)
{
    Ctx* c = (Ctx*)((AppObj*)SP_App())->v58(p, a);
    if (c->Check()) {
        float x = mF108 + p[0];
        float y = mF10c + p[1];
        float z = mF110 + p[2];
        p[0] = x;
        p[1] = y;
        p[2] = z;
    }
}

// @ 0x00c63e30
cTargetMorphHandle::cTargetMorphHandle()
{
    mpVtbl = (void*)kVtblTgt0;
    _ReadWriteBarrier();
    mpVtbl04 = (void*)kVtblTgt1;
    _ReadWriteBarrier();
    mpVtblSpatial = (void*)kVtblTgtSp;
    _ReadWriteBarrier();
    SpatialObj* spatial = (SpatialObj*)&mpVtblSpatial;
    mF118 = 0.0f;
    _ReadWriteBarrier();
    mF11c = 0.0f;
    _ReadWriteBarrier();
    mF120 = 0.0f;
    _ReadWriteBarrier();
    mB124 = 0;
    _ReadWriteBarrier();
    mI128 = 0;
    _ReadWriteBarrier();
    mF12c = 0.0f;
    _ReadWriteBarrier();
    mI130 = 3;
    _ReadWriteBarrier();
    mpRef = 0;
    _ReadWriteBarrier();
    spatial->SetModelKey(&gTgtMorphKeyData);
}

// @ 0x00c63ef0
void cTargetMorphHandle::Dtor()
{
    mpVtbl = (void*)kVtblTgt0;
    mpVtbl04 = (void*)kVtblTgt1;
    mpVtblSpatial = (void*)kVtblTgtSp;
    _ReadWriteBarrier();
    if (mpRef)
        mpRef->v1();
    mpVtbl = (void*)kVtblMorph0;
    mpVtbl04 = (void*)kVtblMorph1;
    mpVtblSpatial = (void*)kVtblMorphSp;
    ((SpatialBase*)&mpVtblSpatial)->ctorSpatialObject();
    ((GameDataBase*)this)->ctorGameData();
}

// @ 0x00c63f40
void cTargetMorphHandle::Release()
{
    if (mpRef) {
        if (mpRef->v4())
            mpRef->v3(0);
    }
    Ref* p = mpRef;
    if (p) {
        mpRef = 0;
        p->v1();
    }
}

// @ 0x00c63f90
void Kin::Fn63f90()
{
    char* self = (char*)this;
    float* p = (float*)((VObj*)(self + 0x34))->v2c();
    float* r;
    if (*(float*)(self + 0x118) == p[0] && *(float*)(self + 0x11c) == p[1]
        && *(float*)(self + 0x120) == p[2]) {
        float dst[4];
        r = (float*)PlanetModel()->BuildSurfaceOrientation(
                dst, ((VObj*)(self + 0x34))->v2c());
    } else {
        float* q = (float*)((VObj*)(self + 0x34))->v2c();
        float dx = *(float*)(self + 0x118) - q[0];
        float dy = *(float*)(self + 0x11c) - q[1];
        float dz = *(float*)(self + 0x120) - q[2];
        float k = 1.0f / (float)sqrt((double)((dx * dx + dy * dy) + dz * dz + 1e-8f));
        float dir[3];
        dir[0] = k * dx;
        dir[1] = k * dy;
        dir[2] = k * dz;
        float dst2[4];
        r = (float*)PlanetModel()->BuildSurfaceOrientation2(
                dst2, ((VObjDir*)(self + 0x34))->v2c(dir));
    }
    float quat[4];
    quat[0] = r[0];
    quat[1] = r[1];
    quat[2] = r[2];
    quat[3] = r[3];
    ((VObj*)(self + 0x34))->v3c(quat);
}

// @ 0x00c640e0
void CmpObj64::Fn()
{
    char* self = (char*)this;
    float tmp[3];
    Vec3f* v = (Vec3f*)((VObj*)(self + 0x34))->v60(tmp);
    float s = *(float*)(self + 0x1bc);
    Vec3f sc;
    sc.x = v->x * s;
    sc.y = v->y * s;
    sc.z = v->z * s;
    Vec3f out;
    out.x = sc.x + *(float*)(self + 0x198);
    out.y = sc.y + *(float*)(self + 0x19c);
    out.z = sc.z + *(float*)(self + 0x1a0);
    ((VObj*)(self + 0x34))->v38(&out);
}

// @ 0x00c64170
void Kin::Fn64170()
{
    char* self = (char*)this;
    void* d0 = *(void**)(self + 0xd0);
    if (!d0)
        return;
    float a = *(float*)(self + 0x1c4);
    float b = *(float*)(self + 0x1c0) + *(float*)(self + 0x1b4);
    float c = *(float*)(self + 0x1c8) * a;
    float d = *(float*)(self + 0x1cc) * a;
    if (c > b) {
        a = (a / c) * b;
        b = c;
    } else if (d < b) {
        a = (a / d) * b;
        b = d;
    }
    ((VObj*)(self + 0x34))->v40(a);
    float ratio = (c == d) ? 1.0f : (b - c) / (d - c);
    float abc[3];
    abc[0] = 0.0f;
    abc[1] = ratio;
    abc[2] = 0.0f;
    CtxD4* ctx = (CtxD4*)*(void**)(self + 0xd4);
    ctx->s80(d0, *(int*)(self + 0x1d0), &abc[2], abc, 0);
    ctx->s74(d0, *(int*)(self + 0x1d0), (abc[0] - abc[2]) * abc[1] + abc[2], 0);
    ctx->s10c(d0, 0);
}

// @ 0x00c642e0
void Kin::Fn642e0()
{
    char* self = (char*)this;
    Fn63cb0();
    *(TVec4*)(self + 0x17c) = *(TVec4*)(self + 0x198);
    *(TVec*)(self + 0x170) = *(TVec*)(self + 0x18c);
    TVec4 local;
    PlanetModel()->BuildSurfaceOrientation_2(&local, self + 0x18c, self + 0x198);
    *(int*)(self + 0x128) = 0;
    *(int*)(self + 0x12c) = 0;
    *(int*)(self + 0x130) = 0;
    *(int*)(self + 0x134) = 0;
    int* lv = (int*)&local;
    *(int*)(self + 0x15c) = lv[0];
    *(int*)(self + 0x160) = lv[1];
    *(int*)(self + 0x164) = lv[2];
    *(int*)(self + 0x168) = lv[3];
    *(uint8_t*)(self + 0x120) = 0;
}

// @ 0x00c643a0
void HandleThing::SetEnabled(bool v)
{
    if (mEn == v)
        return;
    mEn = v;
    if (v)
        ((VObj*)((char*)this + 0x34))->v40(mC * mA + mB);
    else
        ((VObj*)((char*)this + 0x34))->v40(1.0f);
}

// @ 0x00c64400
char FUN_c64400(void* a, void* b)
{
    float* p1 = (float*)((VObj*)((char*)b + 0x34))->v2c();
    float* p2 = (float*)((VObj*)((char*)a + 0x34))->v2c();
    float dx = p2[0] - p1[0];
    float dy = p2[1] - p1[1];
    float dz = p2[2] - p1[2];
    float len = (float)sqrt((double)((dx * dx + dz * dz) + dy * dy));
    if (2.0f < len)
        return 0;
    return 1;
}

// @ 0x00c64460
void PathObj::Fn64460(void* h)
{
    int count = (int)(((char*)mpEnd - (char*)mpBegin) >> 2);
    if ((unsigned)count > 1 && mpBegin[count - 1] == h) {
        void* first = mpBegin[0];
        float* p = (float*)((VObj*)((char*)h + 0x34))->v2c();
        float dx = p[0] - *(float*)((char*)first + 0x118);
        float dy = p[1] - *(float*)((char*)first + 0x11c);
        float dz = p[2] - *(float*)((char*)first + 0x120);
        if ((float)sqrt((double)(dz * dz + dy * dy + dx * dx)) < 2.5f) {
            ((VObj*)((char*)this + 0x34))->v38((char*)first + 0x118);
            mFlag = 1;
        } else {
            mFlag = 0;
        }
    } else {
        mFlag = 0;
    }
    TVec cur;
    cur.x = *(float*)((char*)mpBegin[0] + 0x118);
    cur.y = *(float*)((char*)mpBegin[0] + 0x11c);
    cur.z = *(float*)((char*)mpBegin[0] + 0x120);
    for (int i = 0; i < (int)(((char*)mpEnd - (char*)mpBegin) >> 2); ++i) {
        char* e = (char*)mpBegin[i];
        *(TVec*)(e + 0x118) = cur;
        cur = *(TVec*)((VObj*)(e + 0x34))->v2c();
        ((KObj*)e)->k68();
    }
}

// @ 0x00c64590
float FUN_c64590(void** vec, int idx, void* a, void* b)
{
    void** begin = (void**)vec[0];
    void** end = (void**)vec[1];
    int count = (int)(((char*)end - (char*)begin) >> 2);
    if (idx + 2 == count) {
        float* p1 = (float*)((VObj*)((char*)b + 0x34))->v2c();
        float* p2 = (float*)((VObj*)((char*)a + 0x34))->v2c();
        float dx = p2[0] - p1[0];
        float dy = p2[1] - p1[1];
        float dz = p2[2] - p1[2];
        return (float)sqrt((double)(dz * dz + (dy * dy + dx * dx))) - 0.05f;
    }
    return QuaternionSlerp(((VObj*)((char*)a + 0x34))->v2c(),
                           ((VObj*)((char*)b + 0x34))->v2c(),
                           ((VObj*)((char*)begin[idx + 2] + 0x34))->v2c());
}

// @ 0x00c64630
int FUN_c64630(void** vec, void* h, float px, float py, float pz)
{
    if (py * py + pz * pz + px * px < 1.5258789e-05f) {
        float* p = (float*)((VObj*)((char*)h + 0x34))->v2c();
        px = p[0];
        py = p[1];
        pz = p[2];
    }
    void** begin = (void**)vec[0];
    void** end = (void**)vec[1];
    int count = (int)(((char*)end - (char*)begin) >> 2);
    int i = 0;
    for (; i < count; ++i)
        if (begin[i] == h)
            break;
    if (i == count)
        i = 0;
    if (count == 1)
        return 0;
    if (i == 0) {
        void* next = begin[1];
        if (!ComparePair(h, &px, next))
            return 0;
        float slerp = QuaternionSlerp(((VObj*)((char*)h + 0x34))->v2c(),
                                      (char*)h + 0x118,
                                      ((VObj*)((char*)next + 0x34))->v2c());
        if (slerp <= FUN_c64590(vec, 0, h, next))
            return 0;
        return (int)next;
    }
    if (i == count - 1) {
        void* prev = begin[i - 1];
        if (!ComparePair(h, &px, prev))
            return 0;
        float* p1 = (float*)((VObj*)((char*)prev + 0x34))->v2c();
        float* p2 = (float*)((VObj*)((char*)h + 0x34))->v2c();
        float dx = p2[0] - p1[0];
        float dy = p2[1] - p1[1];
        float dz = p2[2] - p1[2];
        float cp = CopyPairF(h, prev) + 0.5f;
        if ((float)sqrt((double)((dz * dz + dy * dy) + dx * dx)) - 0.05f <= cp)
            return 0;
        return (int)prev;
    }
    void* next = begin[i + 1];
    void* prev = begin[i - 1];
    float slerp = QuaternionSlerp(((VObj*)((char*)h + 0x34))->v2c(),
                                  (char*)h + 0x118,
                                  ((VObj*)((char*)next + 0x34))->v2c());
    float r1 = FUN_c64590(vec, i, h, next);
    float cp = CopyPairF(h, prev);
    if (ComparePair(h, &px, next) && slerp > r1 && cp > r1)
        return (int)next;
    if (!ComparePair(h, &px, prev))
        return 0;
    if (slerp <= cp)
        return 0;
    return (int)prev;
}

// @ 0x00c64880
void FUN_c64880(void** vec, void* a, void* b)
{
    void** begin = (void**)vec[0];
    void** end = (void**)vec[1];
    int count = (int)(((char*)end - (char*)begin) >> 2);
    int ia = 0;
    if (count > 0) {
        void** p = begin;
        for (int i = 0; i < count; ++i, ++p)
            if (*p == a) {
                ia = i;
                break;
            }
    }
    int ib = 0;
    if (count > 0) {
        void** p = begin;
        for (int i = 0; i < count; ++i, ++p)
            if (*p == b) {
                ib = i;
                break;
            }
    }
    void* old = begin[ia];
    if (b != old) {
        if (b)
            ((Ref*)b)->v0();
        begin[ia] = b;
        if (old)
            ((Ref*)old)->v1();
    }
    old = begin[ib];
    if (a != old) {
        if (a)
            ((Ref*)a)->v0();
        begin[ib] = a;
        if (old)
            ((Ref*)old)->v1();
    }
}

// @ 0x00c64940
void PathObj::Fn64940(void* h)
{
    int r = FUN_c64630((void**)((char*)this + 4), h, f18, f1c, f20);
    if (r)
        FUN_c64880((void**)((char*)this + 4), h, (void*)r);
    Fn64460(h);
    int* p = (int*)((VObj*)((char*)h + 0x34))->v2c();
    *(int*)((char*)this + 0x18) = p[0];
    *(int*)((char*)this + 0x1c) = p[1];
    *(int*)((char*)this + 0x20) = p[2];
}

// @ 0x00c64a70
bool __thiscall A::Contains(int key)
{
  volatile int* p = *(int**)((char*)this + 4);
  for (int i = 0; i < ((int)*(int**)((char*)this + 8) - (int)*(int**)((char*)this + 4)) >> 2; ++i, ++p) {
    if (key == *p) return true;
  }
  return false;
}

// @ 0x00c64ad0
void __cdecl FUN_00c64ad0(float* out, float* in)
{
  float inv = 1.0f / sqrtf(in[0] * in[0] + in[1] * in[1] + in[2] * in[2] + in[3] * in[3] + 1e-08f);
  float r[4];
  r[0] = in[0] * inv;
  r[1] = in[1] * inv;
  r[2] = in[2] * inv;
  r[3] = in[3] * inv;
  out[0] = r[0];
  out[1] = r[1];
  out[2] = r[2];
  out[3] = r[3];
}

// @ 0x00c64b50
void __thiscall A::EnableFlag(char b)
{
  *(char*)((char*)this + 0x115) = b;
  if (*(int*)((char*)this + 0xd0) != 0) {
    void* mm = SP_ModelManager();
    int base = *(int*)((char*)this + 0xd0);
    char c = *(char*)((char*)this + 0x115);
    unsigned idx = (*(unsigned(__thiscall*)(void*, int, int))((*(void***)mm)[0x28 / 4]))(mm, 0x7aa969b, 0);
    if (idx < 0x40) {
      if (c != 0) ((unsigned*)(base + 0x44))[idx >> 5] |= 1u << (idx & 0x1f);
      else        ((unsigned*)(base + 0x44))[idx >> 5] &= ~(1u << (idx & 0x1f));
    }
  }
}

// @ 0x00c653e0
void __fastcall FUN_00c653e0(void* self)
{
  void* sub = (char*)self + 0x34;
  *(void**)self = (void*)0x1471288;
  *(void**)((char*)self + 4) = (void*)0x1471274;
  *(void**)sub = (void*)0x14711b0;
  *(void* volatile*)((char*)self + 0x118) = (void*)0x14711a8;
  *(void* volatile*)((char*)self + 0x118) = (void*)0x14711a4;
  void* p = *(void**)((char*)self + 0x148);
  if (p && *(int*)((char*)p - 4) != 0) operator_delete__(p);
  *(void**)self = (void*)0x1470eb8;
  *(void**)((char*)self + 4) = (void*)0x147112c;
  *(void**)sub = (void*)0x1470df0;
  FUN_00c8a420(sub);
  FUN_00b184c0(self);
}

// @ 0x00c654b0
void __thiscall A::SetA(float v)
{
  if (*(float*)((char*)this + 0x1bc) != v) {
    *(float*)((char*)this + 0x1bc) = v;
    FUN_00c640e0();
  }
}

// @ 0x00c654e0
void __thiscall A::SetB(float v)
{
  if (*(float*)((char*)this + 0x1c0) != v) {
    *(float*)((char*)this + 0x1c0) = v;
    FUN_00c64170();
  }
}

// @ 0x00c65510
void __thiscall A::SetC(float v)
{
  if (*(float*)((char*)this + 0x1c4) != v) {
    *(float*)((char*)this + 0x1c4) = v;
    FUN_00c64170();
  }
}

// @ 0x00c65540
void __fastcall FUN_00c65540(void* self)
{
  void* sub = (char*)self + 0x34;
  *(void**)self = (void*)0x14713c8;
  *(void**)((char*)self + 4) = (void*)0x14713b4;
  *(void**)sub = (void*)0x14712f0;
  *(void* volatile*)((char*)self + 0x118) = (void*)0x14712ec;
  *(void* volatile*)((char*)self + 0x118) = (void*)0x14711a4;
  void* p = *(void**)((char*)self + 0x148);
  if (p && *(int*)((char*)p - 4) != 0) operator_delete__(p);
  *(void**)self = (void*)0x1470eb8;
  *(void**)((char*)self + 4) = (void*)0x147112c;
  *(void**)sub = (void*)0x1470df0;
  FUN_00c8a420(sub);
  FUN_00b184c0(self);
}

// @ 0x00c658e0
void __thiscall A::SetPos(float* p)
{
  APos* s = (APos*)this;
  if (s->pos.x != p[0] || s->pos.y != p[1] || s->pos.z != p[2]) {
    s->pos = *(Vec3*)p;
    FUN_00c64db0();
  }
}

// @ 0x00c65940
void cMorphHandle_s00c6_5940::SetFacing(const cSPVector3_s00c6_5940& dir)
{
    double dx = dir.x, dy = dir.y, dz = dir.z;
    double lenSq = dx * dx + dy * dy + dz * dz + (double)g_13EC4B8;
    float v = (float)(1.0 / sqrt(lenSq));
    cSPVector3_s00c6_5940 n;
    n.x = dir.x * v;
    n.y = dir.y * v;
    n.z = dir.z * v;
    if (mAxisX == n.x && mAxisY == n.y && mAxisZ == n.z)
        return;
    mAxisX = n.x; mAxisY = n.y; mAxisZ = n.z;
    cSPVector3_s00c6_5940 m;
    if ((mAxisX == g_1693DD4 && mAxisY == g_1693DD8 && mAxisZ == g_1693DDC) ||
        (mAxisX == -g_1693DD4 && mAxisY == -g_1693DD8 && mAxisZ == -g_1693DDC)) {
        m.x = g_1693DC8; m.y = g_1693DCC; m.z = g_1693DD0;
    } else {
        m.x = g_1693DD4; m.y = g_1693DD8; m.z = g_1693DDC;
    }
    mVec1X = m.x; mVec1Y = m.y; mVec1Z = m.z;
    UpdatePos();
    UpdateQuat();
}

// @ 0x00c65af0
void cMorphHandle_s00c6_5940::SetT(float t)
{
    float* pf = &mHi;
    if (mHi > t)
        pf = &t;
    float* pg = &mLo;
    if (*pf > mLo)
        pg = pf;
    if (mT != *pg) {
        mT = *pg;
        UpdatePos();
    }
}

// @ 0x00c65b50
void cMorphHandle_s00c6_5940::SetTLerp(float t)
{
    float* pf = &mHi;
    float* pg = &mLo;
    t = (mHi - mLo) * t + mLo;
    if (t < *pf)
        pf = &t;
    if (*pf <= *pg)
        pf = pg;
    if (mT != *pf) {
        mT = *pf;
        UpdatePos();
    }
}

// @ 0x00c65bc0
void* cSimpleRotationRing::ScalarDtor(unsigned char flags)
{
    vftable = vtbl_cMorphHandleSub;
    _ReadWriteBarrier();
    int* p = *(int**)((char*)this + 0x30);
    if (p != 0 && *(p - 1) != 0)
        ::operator delete(p);
    if (flags & 1)
        ::operator delete(this);
    return this;
}

// @ 0x00c65c00
cSimpleRotationRing::cSimpleRotationRing()
{
    vftable118 = vtbl_cMorphHandleSub;      // 0x14711a4
    mByte120 = 0;
    mBaseZInt = 0;
    mSub128.Ctor(4, 0);
    mSub128.Init(0, 0);
    mSub128.mMat21i = 0;
    mSub128.mMat22i = 0;
    mOffXi = 0;
    mAxisX = g_15777D0;
    mAxisY = g_15777D4;
    mAxisZ = g_15777D8;
    mVec1X = g_15777DC;
    vftable = vtbl_ringPrimary;
    vftable004 = vtbl_ring004;
    mSpatial.vftable = vtbl_ring034;
    vftable118 = vtbl_ring118;
    mVec1Z = g_1693DD4;
    mLo = g_1693DD8;
    mHi = g_1693DDC;
    mT = g_1693DC8;
    mU = g_1693DCC;
    mV = g_1693DD0;
    mF188 = g_15777D0;
    mViewX = g_15777D4;
    mViewY = g_15777D8;
    mViewZ = g_15777DC;
    mQuat198.x = g_1693D74;
    mQuat198.y = g_1693D78;
    mQuat198.z = g_1693D7C;
    mQuat198.w = g_15777D0;
    mSpeed = g_15777D4;
    mPhase = g_15777D8;
    mAmplitude = g_15777DC;
    mRing1b4 = 0.0f;
    mRing1b8 = 2;
    mRing1bc = 0.0f;
    mRing1c0 = 0.0f;
    float one = g_1485720;
    mRing1c4 = one;
    mRing1c8 = 0.0f;
    mRing1cc = one;
    mRing1d0 = 0;
    mSpatial.SetKey(DAT_015777FC);
    if (mRing1c8 != 0.0f || mRing1cc != 7.0f) {
        mRing1c8 = 0.0f;
        mRing1cc = 7.0f;
        SetRingReset();
    }
}

// @ 0x00c65e80
bool cMorphHandle_s00c6_5940::OnEvent(void* p)
{
    mEventFlags |= 8;
    if (!OnEventCheck(p))
        return false;

    mPtr9c->mFlags |= 0x100;
    mPtr9c->mKind = 4;
    bool b = ((int(__thiscall*)(void*, cEventRef*, int))(*(void***)mPtrA0)[0x68 / 4])(
                 mPtrA0, mPtr9c, 0) == 1;
    if (b) {
        ((void(__thiscall*)(void*, cEventRef*, float*, int))(*(void***)mPtrA0)[0x6c / 4])(
            mPtrA0, mPtr9c, &mQuat198.y, 0);
        ((cMorphHandle_s00c6_5940*)((char*)this - 0x34))->SetRingReset();
    }
    return b;
}

// @ 0x00c65f00
cSimpleRotationBall::cSimpleRotationBall()
{
    vftable118 = vtbl_cMorphHandleSub;      // 0x14711a4
    mByte120 = 0;
    mBaseZInt = 0;
    mSub128.Ctor(4, 0);
    mSub128.Init(0, 0);
    mSub128.mMat21i = 0;
    mSub128.mMat22i = 0;
    mOffXi = 0;
    mAxisX = g_15777D0;
    mAxisY = g_15777D4;
    mAxisZ = g_15777D8;
    mVec1X = g_15777DC;
    vftable = vtbl_ballPrimary;
    vftable004 = vtbl_ball004;
    mSpatial.vftable = vtbl_ball034;
    vftable118 = vtbl_ball118;
    mVec1Z = g_1693D74;
    mLo = g_1693D78;
    mHi = g_1693D7C;
    mT = g_15777D0;
    mU = g_15777D4;
    mV = g_15777D8;
    mF188 = g_15777DC;
    mViewX = g_1693D74;
    mViewY = g_1693D78;
    mViewZ = g_1693D7C;
    mQuat198.x = g_15777D0;
    mQuat198.y = g_15777D4;
    mQuat198.z = g_15777D8;
    mQuat198.w = g_15777DC;
    mSpeed = 0.0f;
    mPhase = 0.0f;
    mAmplitude = g_1485720;
    mActive = 0;
    mSpatial.SetKey(DAT_01577808);
}

// @ 0x00c660f0
void cMorphHandle_s00c6_5940::OnView(void* view)
{
    if (mViewRef != 0) {
        if (view == 0) {
            mViewRef->mFlags &= ~1;
            return;
        }
        mViewRef->mFlags |= 1;
    }
    if (view == 0)
        return;

    bool changed = false;

    cSPVector3_s00c6_5940* pp = ((cSPVector3_s00c6_5940*(__thiscall*)(void*))(*(void***)view)[0x2c / 4])(view);
    cSPVector3_s00c6_5940 v;
    v.x = pp->x;
    v.y = pp->y;
    v.z = pp->z;
    if (mViewX != v.x || mViewY != v.y || mViewZ != v.z) {
        mViewX = v.x;
        mViewY = v.y;
        mViewZ = v.z;
        changed = true;
    }

    cSPQuaternion_s00c6_5940* pq = ((cSPQuaternion_s00c6_5940*(__thiscall*)(void*))(*(void***)view)[0x30 / 4])(view);
    cSPQuaternion_s00c6_5940 q;
    q.x = pq->x;
    q.y = pq->y;
    q.z = pq->z;
    q.w = pq->w;
    if (mQuat198.x != q.x || mQuat198.y != q.y ||
        mQuat198.z != q.z || mQuat198.w != q.w) {
        mQuat198.x = q.x;
        mQuat198.y = q.y;
        mQuat198.z = q.z;
        mQuat198.w = q.w;
        changed = true;
        SetOrientation(&mQuat198);
    }

    float s = ((float(__thiscall*)(void*))(*(void***)view)[0x70 / 4])(view);
    if (mSpeed != s) {
        mSpeed = s;
        if (mActive != 0)
            RefreshScale();
        UpdateBallPos();
    } else if (changed) {
        UpdateBallPos();
    }
}

// @ 0x00c662b0
void cMorphHandle_s00c6_5940::SetPhase(float v)
{
    if (mPhase != v) {
        mPhase = v;
        UpdateBallPos();
        if (mActive != 0)
            SetScale(mAmplitude * mSpeed + mPhase);
    }
}

// @ 0x00c66310
void cMorphHandle_s00c6_5940::SetAmplitude(float v)
{
    if (mAmplitude != v) {
        mAmplitude = v;
        UpdateBallPos();
        if (mActive != 0)
            SetScale(mSpeed * mAmplitude + mPhase);
    }
}

// @ 0x00c66370
void cMorphHandle_s00c6_5940::UpdateMatrix()
{
    cSPVector3_s00c6_5940 A, B, C;
    ((void(__thiscall*)(void*, cSPVector3_s00c6_5940*, cSPVector3_s00c6_5940*))vftable[0x60 / 4])(this, &A, &B);
    ((void(__thiscall*)(void*, cSPVector3_s00c6_5940*))SpatialVt()[0x5c / 4])(&mSpatial, &C);

    // u = B x C (third component as emitted), then g = -(u x C)
    float u0 = B.y * C.z - B.z * C.y;
    float u1 = B.z * C.x - C.z * B.x;
    float u2 = C.y * B.x - B.y * C.x;
    float g0 = u2 * C.y - u1 * C.z;
    float g1 = u0 * C.z - u2 * C.x;
    float g2 = u1 * C.x - u0 * C.y;

    float lenSq = g2 * g2 + g1 * g1 + g0 * g0 + g_13EC4B8;
    float inv = 1.0f / sqrtf(lenSq);
    g0 *= inv;
    g1 *= inv;
    g2 *= inv;

    float m0, m1, m2;
    if (mFlags118 & 2) {
        float x = mOffX, y = mOffY, z = mOffZ;
        m0 = (mSub128.mMat20 * z + mSub128.mMat10 * y) + mSub128.mMat00 * x;
        m1 = (mSub128.mMat01 * x + mSub128.mMat21 * z) + mSub128.mMat11 * y;
        m2 = (mSub128.mMat02 * x + mSub128.mMat22 * z) + mSub128.mMat12 * y;
    } else {
        m0 = mOffX;
        m1 = mOffY;
        m2 = mOffZ;
    }

    float s = mSub128.mScale;
    float px = mBaseX + m0 * s;
    float py = mBaseY + m1 * s;
    float pz = mBaseZ + m2 * s;

    float dot = (g0 * px + pz * g2) + py * g1;
    float denom = (g0 * B.x + g1 * B.y) + g2 * B.z;
    if (denom == 0.0f)
        return;

    float num = ((A.x * g0 + A.z * g2) + A.y * g1) - dot;
    float t = -(num / denom);
    if (-t < 0.0f)
        return;

    float qx = A.x + t * B.x;
    float qy = A.y + t * B.y;
    float qz = A.z + t * B.z;
    float f = (qy - py) * C.y;
    f += (qx - px) * C.x;
    f += (qz - pz) * C.z;

    float* pf = &mHi;
    if (mHi > f)
        pf = &f;
    float* pg;
    if (*pf > mLo)
        pg = pf;
    else
        pg = &mLo;
    if (mT != *pg) {
        mT = *pg;
        UpdatePos();
    }
}

// @ 0x00c666f0
void cMorphHandle_s00c6_5940::SetRange(float lo, float hi)
{
    *(volatile float*)&mLo = lo;
    *(volatile float*)&mHi = hi;
    float t = mT;
    float* pf = &mHi;
    if (mHi > t)
        pf = &t;
    float* pg;
    if (*pf > mLo)
        pg = pf;
    else
        pg = &mLo;
    if (mT != *pg) {
        mT = *pg;
        UpdatePos();
    }
}

// @ 0x00c66760
void Ctrl::FrameUpdate()
{
    CtrlResetBase(this);

    Vector3 origin, dir;
    GetCameraRay(*((void**)((char*)AppGet() + 0)), &origin, &dir);

    // mAxis <- current extents sample; mBase <- previous output orientation.
    mTarget.GetExtents(&mAxis);
    mBase = mOut;

    const Vector3* pos = mTarget.GetPosition();
    float axisDotDir = Dot(dir, mAxis);
    if (axisDotDir == 0.0f)
        return;

    float t = -((Dot(origin, mAxis) - Dot(*pos, mAxis)) / axisDotDir);
    if (!(t >= 0.0f))
        return;

    const Vector3* pos2 = mTarget.GetPosition();
    Vector3 hit = origin + dir * t - *pos2;
    mDirRef = hit * InvSqrtEps(hit.SquaredLength());

    Vector3 surf;
    BuildSurfaceOrientation_2(&surf, mTarget.GetPosition(), (const Vector3*)&mOut);

    Vector3 about;
    mTarget.GetDirPoint(&about, &mDirRef, &mAxis);

    float half = AngleAroundAxis(&about) * gF_1471064;
    float sh = (float)sin((double)half);
    float ch = (float)cos((double)half);
    Quaternion q(sh * mDirRef.x, sh * mDirRef.y, sh * mDirRef.z, ch);

    Quaternion rot;
    Vec4Transform(&rot, &q, &mAxis);

    Quaternion R;
    R.x = (rot.w * mBase.x + rot.x * mBase.w) + (rot.z * mBase.y - rot.y * mBase.z);
    R.y = (rot.w * mBase.y + rot.y * mBase.w) + (rot.z * mBase.x - rot.x * mBase.z);
    R.z = (rot.w * mBase.z + rot.z * mBase.w) + (rot.y * mBase.x - rot.x * mBase.y);
    R.w = rot.w * mBase.w - ((rot.z * mBase.z + rot.y * mBase.y) + rot.x * mBase.x);

    mZeroQuat.x = 0.0f;
    mZeroQuat.y = 0.0f;
    mZeroQuat.z = 0.0f;
    mZeroQuat.w = 0.0f;
    mb120 = 0;

    float inv = InvSqrtEps(R.x * R.x + R.y * R.y + R.z * R.z + R.w * R.w);
    mApproach.x = inv * R.x;
    mApproach.y = inv * R.y;
    mApproach.z = inv * R.z;
    mApproach.w = inv * R.w;
    (void)surf;
}

// @ 0x00c66c10
void Ctrl::FlushOrientation()
{
    if ((gF_1693d64 & 1) == 0) {
        gF_1693d64 |= 1;
        float a = gF_15777a8 * gF_1471064 * gF_1471064;
        float sh = (float)sin((double)a);
        float ch = (float)cos((double)a);
        gQ_1693d54.x = gF_1693de0 * sh;
        gQ_1693d54.y = gF_1693de4 * sh;
        gQ_1693d54.z = gF_1693de8 * sh;
        gQ_1693d54.w = ch;
    }
    if ((gF_1693d64 & 2) == 0) {
        gF_1693d64 |= 2;
        float a = gF_15777a8 * gF_1471064 * gF_1471064;
        float sh = (float)sin((double)a);
        float ch = (float)cos((double)a);
        gQ_1693d44.x = gF_1693dc8 * sh;
        gQ_1693d44.y = gF_1693dcc * sh;
        gQ_1693d44.z = gF_1693dd0 * sh;
        gQ_1693d44.w = ch;
    }

    Quaternion q;
    switch (mState) {
    case 0: {
        Vec4Rotate(&q, &gQ_1693d44, (const Vector3*)&mOut);
        float inv = InvSqrtEps(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
        q.x = inv * q.x;
        q.y = inv * q.y;
        q.z = inv * q.z;
        q.w = q.w * inv;
        break;
    }
    case 1: {
        Vec4Rotate(&q, &gQ_1693d54, (const Vector3*)&mOut);
        float inv = InvSqrtEps(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
        q.x = inv * q.x;
        q.y = inv * q.y;
        q.z = inv * q.z;
        q.w = q.w * inv;
        break;
    }
    case 2:
        q = mOut;
        break;
    default:
        return;
    }
    mTarget.SetOrientation(q);
}

// @ 0x00c66e60
void Ctrl::Approach()
{
    Vector3 extA, extB;
    mTarget.GetExtents(&extA);

    // Radius of the target sphere from the stored output orientation components.
    float radius = mOut.w * mOut.y + mOut.z;

    Vector3 org, rayDir;
    float t;
    bool hit = IntersectRaySphere(&org, &rayDir, &mAxis, radius, &t);

    const Vector3* pos = mTarget.GetPosition();
    Vector3 delta;
    if (hit) {
        delta.x = (extA.x + org.x) - pos->x;
        delta.y = (extA.y + rayDir.y) - pos->y;
        delta.z = (extA.z + rayDir.z) - pos->z;
    } else {
        delta.x = pos->x - extA.x;
        delta.y = pos->y - extA.y;
        delta.z = pos->z - extA.z;
    }

    Vector3 approachDir = delta * InvSqrtEps(delta.SquaredLength());
    (void)extB;

    Vector3 constrained;
    ConstrainToPlane(&constrained, &approachDir);

    Vector3 ref;
    Vec4Transform(&ref, &gV_1693dd4, &mDirRef);
    Quaternion targetRot;
    QuaternionFromDirections(&targetRot, &ref, &constrained);

    Quaternion R;
    R.x = (targetRot.w * mBase.x + targetRot.x * mBase.w) + (targetRot.z * mBase.y - targetRot.y * mBase.z);
    R.y = (targetRot.w * mBase.y + targetRot.y * mBase.w) + (targetRot.x * mBase.z - targetRot.z * mBase.x);
    R.z = (targetRot.w * mBase.z + targetRot.z * mBase.w) + (targetRot.y * mBase.x - targetRot.x * mBase.y);
    R.w = targetRot.w * mBase.w - ((targetRot.z * mBase.z + targetRot.y * mBase.y) + targetRot.x * mBase.x);

    Quaternion N;
    float inv = InvSqrtEps(R.x * R.x + R.y * R.y + R.z * R.z + R.w * R.w);
    N.x = inv * R.x;
    N.y = inv * R.y;
    N.z = inv * R.z;
    N.w = R.w * inv;

    if (mCached.x != N.x || mCached.y != N.y || mCached.z != N.z || mCached.w != N.w) {
        mCached = N;
        mTarget.SetOrientation(mCached);
        CtrlNotifyChanged(this);
    }
}

// @ 0x00c67440
void Vector4Array::insert(Vector4* dest, const Vector4* value)
{
    Vector4* begin = mpBegin;
    Vector4* end = mpEnd;
    if (end != mpCapacity) {
        const Vector4* v = value;
        if (dest <= v && v < end)
            v = v + 1;
        if (end != 0)
            end[0] = end[-1];
        CopyBackward(dest, end - 1, end);
        *dest = *v;
        mpEnd = end + 1;
        return;
    }

    int newCap = (int)(end - begin) >> 4;
    if (newCap <= 0) {
        newCap = 1;
    } else {
        newCap = newCap * 2;
        if (newCap == 0) {
            mpBegin = 0;
            mpEnd = 0;
            mpCapacity = 0;
            return;
        }
    }

    Vector4* mem = (Vector4*)AllocVectorBytes(newCap << 4);
    Vector4* after = (Vector4*)CopyRange(begin, dest, mem);
    if (after != 0)
        *after = *value;
    Vector4* newEnd = (Vector4*)CopyRange(dest, end, after + 1);
    if (begin != 0 && ((int*)begin)[-1] != 0)
        FreeVectorBytes(begin);
    mpBegin = mem;
    mpEnd = newEnd;
    mpCapacity = (Vector4*)((newCap << 4) + (int)mem);
}

// @ 0x00c67560
void Vec12Vector::Insert(Vec12* pos, unsigned n, const Vec12& value)
{
    if (n <= (unsigned)(mpCapacity - mpEnd)) {
        if (n > 0) {
            Vec12 saved = value;
            unsigned elems = (unsigned)(mpEnd - pos);
            if (n < elems) {
                Vec12* oldEnd = mpEnd;
                Vec12* p = oldEnd - n;
                F4797a0(&value, p, oldEnd, oldEnd, pos);
                mpEnd += n;
                Fabced0(pos, p, oldEnd);
                Fa177f0(pos, pos + n, &saved);
                return;
            }
            unsigned extra = n - elems;
            Vec12* oldEnd = mpEnd;
            F6a4100(mpEnd, extra, &saved);
            mpEnd += extra;
            F4797a0(pos, pos, oldEnd, mpEnd, pos);
            mpEnd += elems;
            Fa177f0(pos, oldEnd, &saved);
        }
    } else {
        unsigned size = (unsigned)(mpEnd - mpBegin);
        unsigned newCap = size * 2;
        if (size == 0)
            newCap = 1;
        unsigned need = size + n;
        if (newCap > need)
            need = newCap;

        Vec12* pNew;
        if (need == 0)
            pNew = 0;
        else
            pNew = (Vec12*)Ff473a0((int)(need * 0xc), "Simulator", 0, 0, ALLOC_FILE, 0xd1);

        Vec12* newPos = (Vec12*)F7ec550(mpBegin, pos, pNew);
        F6a4100(newPos, n, &value);
        Vec12* newEnd = (Vec12*)F7ec550(pos, mpEnd, newPos + n);

        if (mpBegin != 0 && mpBegin != mpInlineBuf)
            Ff47380(mpBegin);
        mpBegin = pNew;
        mpEnd = newEnd;
        mpCapacity = pNew + need;
    }
}

// @ 0x00c67730
void Ctrl_s00c6_7560__g7::Attach(CtrlTarget* target)
{
    if (mpTargetRef != 0) {
        if (target == 0) {
            mpTargetRef->mFlags &= ~1u;
            return;
        }
        mpTargetRef->mFlags |= 1u;
    }
    if (target == 0)
        return;

    bool changed = false;

    V3 pos = *target->GetPosition();
    if (mPos.x != pos.x || mPos.y != pos.y || mPos.z != pos.z) {
        mPos = pos;
        changed = true;
    }

    Quat q = *target->GetOrientation();
    if (mOut.x != q.x || mOut.y != q.y || mOut.z != q.z || mOut.w != q.w) {
        mOut = q;
        changed = true;
        FlushOrientation();
    }

    float f = (mState == 2) ? target->GetSpan2() : target->GetSpan();
    if (mScale != f) {
        mScale = f;
        Recompute();
    }

    if (changed)
        MarkChanged();
}

// @ 0x00c678f0
void Ctrl_s00c6_7560::Update()
{
    V3 origin, dir;
    AppGet_s00c6_7560()->GetViewer()->GetCameraRay(&origin, &dir);

    const V3* tp = mTarget.GetPosition();
    V3 d;
    d.y = tp->y - origin.y;
    d.z = tp->z - origin.z;
    d.x = tp->x - origin.x;
    float inv = 1.0f / (float)sqrt((double)(d.x * d.x + d.z * d.z + d.y * d.y));
    d.x = inv * d.x;
    d.z = d.z * inv;
    d.y = d.y * inv;
    float dot = (mAxis.z * d.z + mAxis.y * d.y) + mAxis.x * d.x;

    static float cosLimit = (float)cos(1.2566370517015457);

    V3 res;
    V3 scratch;
    if (fabsf_(dot) < cosLimit) {
        V3 c;
        c.x = mAxis.z * d.y - mAxis.y * d.z;
        c.z = mAxis.y * d.x - mAxis.x * d.y;
        c.y = mAxis.x * d.z - mAxis.z * d.x;
        float inv2 = 1.0f / (float)sqrt((double)(c.x * c.x + c.z * c.z + c.y * c.y));
        c.x = inv2 * c.x;
        c.y = c.y * inv2;
        c.z = c.z * inv2;
        const V3* p = mTarget.GetPosition();
        V3 r;
        r.x = p->x - mFocus.x;
        r.z = p->z - mFocus.z;
        r.y = p->y - mFocus.y;
        float num = -((r.x * d.x + r.z * d.z) + r.y * d.y);
        float den = (dir.x * d.x + dir.z * d.z) + dir.y * d.y;
        float t = dot;
        if (den != 0.0f)
            t = -((((d.x * origin.x + d.z * origin.z) + d.y * origin.y) + num) / den);
        V3 h;
        h.x = dir.x * t + origin.x;
        h.y = dir.y * t + origin.y;
        h.z = dir.z * t + origin.z;
        V3 rel;
        rel.x = h.x - r.x;
        rel.y = h.y - r.y;
        rel.z = h.z - r.z;
        float ang = ((rel.z * c.z + rel.y * c.y) + rel.x * c.x) * 1.5707964f / (mScaleB + mScaleA) * 0.5f;
        float s = (float)sin((double)ang);
        float cw = (float)cos((double)ang);
        V3c ax(mAxis);
        Quat q;
        q.x = ax.x * s;
        q.y = ax.y * s;
        q.z = ax.z * s;
        q.w = cw;
        const V3* rot = RotateByQuat(&scratch, &mDirRef, &q);
        res.x = rot->x;
        res.y = rot->y;
        res.z = rot->z;
    } else {
        const V3* p = mTarget.GetPosition();
        float nn = -((p->z * mAxis.z + p->y * mAxis.y) + p->x * mAxis.x);
        float den = (mAxis.z * dir.z + mAxis.y * dir.y) + mAxis.x * dir.x;
        float t = dot;
        if (den != 0.0f)
            t = -((((mAxis.x * origin.x + mAxis.z * origin.z) + mAxis.y * origin.y) + nn) / den);
        V3 h;
        h.x = dir.x * t + origin.x;
        h.y = dir.y * t + origin.y;
        h.z = dir.z * t + origin.z;
        const V3* p2 = mTarget.GetPosition();
        V3 e;
        e.x = h.x - p2->x;
        e.z = h.z - p2->z;
        e.y = h.y - p2->y;
        float inv3 = 1.0f / (float)sqrt((double)(e.x * e.x + e.z * e.z + e.y * e.y + 1e-8f));
        scratch.x = inv3 * e.x;
        scratch.y = e.y * inv3;
        scratch.z = e.z * inv3;
        res = scratch;
    }

    res = *mConstrain.Apply(&scratch, &res);

    float half = AngleAroundAxis(&mDirRef, &res, &mAxis) * 0.5f;
    float s2 = (float)sin((double)half);
    float w = (float)cos((double)half);
    float vx = s2 * mAxis.x;
    float vy = mAxis.y * s2;
    float vz = mAxis.z * s2;
    float qx = mBase.x, qy = mBase.y, qz = mBase.z, qw = mBase.w;
    Quat R;
    R.x = (w * qx + vx * qw) + (qz * vy - qy * vz);
    R.y = (w * qy + vy * qw) + (vz * qx - qz * vx);
    R.z = (w * qz + vz * qw) + (qy * vx - vy * qx);
    R.w = w * qw - ((qz * vz + qy * vy) + qx * vx);
    float inv4 = 1.0f / (float)sqrt((double)(R.w * R.w + R.x * R.x + R.y * R.y + R.z * R.z + 1e-8f));
    Quat N;
    N.x = inv4 * R.x;
    N.y = inv4 * R.y;
    N.z = inv4 * R.z;
    N.w = R.w * inv4;
    if (mOut.x != N.x || mOut.y != N.y || mOut.z != N.z || mOut.w != N.w) {
        mOut = N;
        MarkChanged();
    }
}

// @ 0x00c680d0
void Ctrl_s00c6_7560__g7::SetState(int state)
{
    if (mState != state) {
        mState = state;
        MarkChanged();
        FlushOrientation();
    }
}

// @ 0x00c68100
void RemoveFromVec(PtrVec* vec, void* noun)
{
    ((Noun*)noun)->Detach(0);
    NounManager_s00c6_7560__g7()->RemoveNoun(noun);

    int i = 0;
    while (i < (int)((char*)vec->mpEnd - (char*)vec->mpBegin) >> 2) {
        if (vec->mpBegin[i] == noun)
            goto found;
        ++i;
    }
    i = 0;
found:

    void** begin = vec->mpBegin;
    void** end = vec->mpEnd;
    void** p = begin + i;
    if (p + 1 < end)
        F6782c0(p + 1, end, p);

    vec->mpEnd -= 1;
    Noun* last = (Noun*)*vec->mpEnd;
    if (last != 0)
        last->Release();
}

// @ 0x00c68190
void PathObj_s00c6_7560__g7::Fn68190(void* h)
{
    mV = g1693d74;
    PtrVec* vec = (PtrVec*)&mpBegin;

    for (;;) {
        void** p = vec->mpBegin;
        int count = (int)((char*)vec->mpEnd - (char*)p) >> 2;
        int i = 0;
        if (count > 0) {
            do {
                if (*p == h) {
                    if (i <= 0)
                        goto forward;
                    void* prev = vec->mpBegin[i - 1];
                    if (!Fc64400(prev, h))
                        goto forward;
                    RemoveFromVec(vec, prev);
                    goto top;
                }
                ++i;
                ++p;
            } while (i < count);
        }
        i = 0;

    forward:
        if (((int)((char*)vec->mpEnd - (char*)vec->mpBegin) >> 2) - 1 <= i)
            break;
        void* next = vec->mpBegin[i + 1];
        if (!Fc64400(next, h))
            break;
        RemoveFromVec(vec, next);
    top:;
    }

    return Fn64460(0);
}

// @ 0x00c68250
bool PathObj_s00c6_7560__g7::Fn68250(void* h)
{
    PtrVec* vec = (PtrVec*)&mpBegin;
    if (vec->mpEnd - vec->mpBegin == 1)
        return false;
    RemoveFromVec(vec, h);
    return true;
}

// @ 0x00c686d0
void CTexRun::Build(unsigned count, float* pts, float* angles)
{
    Elem16* last = mVec.mpEnd;
    Elem16* first = mVec.mpBegin;
    FUN_00705250(last, last, first);
    mVec.mpEnd = (Elem16*)((char*)last + (int)(last - first) * -16);
    mVec.Resize(count);
    for (unsigned i = 0; i < count; ++i) {
        Elem16* e = mVec.mpEnd;
        if (e < mVec.mpCapacity) {
            mVec.mpEnd = e + 1;
        } else {
            Elem16 tmp;
            mVec.Grow(e, &tmp);
        }
        Elem16* w = mVec.mpEnd;
        float* pf = pts + i * 3;
        float a = pf[0];
        float b = pf[1];
        float c = pf[2];
        float inv = 1.0f / sqrtf(((a * a + b * b) + c * c) + 1e-8f);
        w[-1].x = a * inv;
        w[-1].y = inv * b;
        w[-1].z = c * inv;
        w[-1].w = (float)cos((double)angles[i] * 0.017453292);
    }
}

// @ 0x00c687e0
void __cdecl ClearVector(Vec* v)
{
    for (int i = 0; i < (int)(v->end - v->begin); ++i) {
        int* noun = v->begin[i];
        ((TFv_i)VTSLOT(noun, 0x54))(noun, 0);
        ((cGameNounManager_s00c6_8280*)FUN_00b3d300())->RemoveNoun(v->begin[i]);
    }
    v->erase(v->begin, v->end);
}

// @ 0x00c68840
void __fastcall F68840(COrn* o)
{
    ClearVector((Vec*)((char*)o + 4));
}

// @ 0x00c68850
void COrn::E850(int* noun)
{
    if (noun == 0) {
        ClearVector((Vec*)((char*)this + 4));
        return;
    }
    int* first = mVec4.begin[0];
    float* p = ((cSpatial*)noun)->GetPosition();
    int* dst = (int*)((char*)first + 0x118);
    dst[0] = ((int*)p)[0];
    dst[1] = ((int*)p)[1];
    dst[2] = ((int*)p)[2];
    H4460(0);
}

// @ 0x00c688a0
void COrnList::Collect(Vector3Vec* dst, char* out)
{
    dst->erase(dst->mpBegin, dst->mpEnd);
    int i = 0;
    if ((int)(mVec.end - mVec.begin) > 0) {
        do {
            CObject* o = (CObject*)mVec.begin[i];
            float* p = o->mSpatial.GetPosition();
            Vector3_s00c6_8280 v;
            v.x = p[0];
            v.y = p[1];
            v.z = p[2];
            dst->push_back(&v);
            ++i;
        } while (i < (int)(mVec.end - mVec.begin));
    }
    *out = mFlag0;
}

// @ 0x00c68930
void COrn::E930()
{
    H3f90();
    Update();
    if (mVec134 != 0) {
        int* v = mVec134;
        if (((TFc_v)VTSLOT(v, 0x10))(v) == 0)
            ((TFv_i)VTSLOT(mVec134, 8))(mVec134, 0);
    }
    if (mpModel != 0) {
        int* m = mpModel;
        ((CModelHead*)m)->mFlags |= 1;
    }
}

// @ 0x00c68980
void COrn::E980(void* view)
{
    if (mpModel != 0) {
        if (view == 0) {
            ((CModelHead*)mpModel)->mFlags &= ~1u;
            goto lab;
        }
        ((CModelHead*)mpModel)->mFlags |= 1;
    }
    if (view != 0) {
        float* p = ((cSpatial*)view)->GetPosition();
        if (mPosX != p[0] || mPosY != p[1] || mPosZ != p[2]) {
            mPosX = p[0]; mPosY = p[1]; mPosZ = p[2];
            H3f90();
            Update();
        }
        if (mVec134 != 0) {
            char c = ((TFc_v)VTSLOT(mVec134, 0x10))(mVec134);
            if (c == 0)
                ((TFv_i)VTSLOT(mVec134, 8))(mVec134, 0);
        }
        return;
    }
lab:
    if (mVec134 != 0) {
        char c = ((TFc_v)VTSLOT(mVec134, 0x10))(mVec134);
        if (c != 0)
            ((TFv_i)VTSLOT(mVec134, 0x0c))(mVec134, 0);
    }
}

// @ 0x00c68aa0
void COrn::Eaa0()
{
    cSpatial* sp = Spatial();
    if (mFlag124 != 0)
        FUN_00ebb720(sp, 0x1707u);
    else
        FUN_00ebb720(sp, 0x705u);
    H3f90();
    Update();
}

// @ 0x00c68ae0
void COrn::Eae0(float* p)
{
    float* cur = Spatial()->GetPosition();
    if (cur[0] != p[0] || cur[1] != p[1] || cur[2] != p[2]) {
        Spatial()->SetPosition(p);
        H3f90();
        Update();
    }
}

// @ 0x00c68b40
void COrn::Eb40(int key)
{
    if (mKey128 == key)
        return;
    if (mVec134 != 0) {
        ((TFv_i)VTSLOT(mVec134, 0x0c))(mVec134, 0);
        int* p = mVec134;
        if (p != 0) {
            mVec134 = 0;
            ((TFv_v)VTSLOT(p, 4))(p);
        }
    }
    mKey128 = key;
    void* eff = FUN_0067ddd0();
    int* old = mVec134;
    if (old != 0) {
        mVec134 = 0;
        ((TFv_v)VTSLOT(old, 4))(old);
    }
    if (((TFc_iii)VTSLOT(eff, 0x2c))(eff, mKey128, 0, &mVec134) != 0)
        Update();
}

// @ 0x00c68bd0
void COrn::Ebd0(float v)
{
    if (mF12c != v) {
        mF12c = v;
        Update();
    }
}

// @ 0x00c68c00
COrn* __cdecl FUN_00c68c00(Vec* refVec, Vector3_s00c6_8280* pos, int index)
{
    cGameNounManager_s00c6_8280* mgr = (cGameNounManager_s00c6_8280*)FUN_00b3d300();
    COrn* noun = (COrn*)mgr->CreateNoun(0x76f6e64);
    if (noun != 0)
        noun = (COrn*)((TFp_i)VTSLOT(noun, 0x0c))(noun, 0x76c67df);
    else
        noun = 0;
    noun->Eb40(0x7553f996);
    if (noun->mF12c != 2.0f) {
        noun->mF12c = 2.0f;
        noun->Update();
    }
    noun->Spatial()->SetPosition(pos);
    noun->mFlag124 = 1;
    if (index == -1 || index == (int)(refVec->end - refVec->begin)) {
        ((TFi_v)VTSLOT(noun, 0))(noun);
        int** e = refVec->end;
        if (e < refVec->cap) {
            refVec->end = e + 1;
            if (e != 0) {
                *e = (int*)noun;
                ((TFi_v)VTSLOT(noun, 0))(noun);
            }
        } else {
            refVec->DoInsertPtr(e, (int**)&noun);
        }
    } else {
        ((TFi_v)VTSLOT(noun, 0))(noun);
        refVec->F_00b05b40(refVec->begin + index, (int**)&noun);
    }
    if (noun != 0)
        ((TFv_v)VTSLOT(noun, 4))(noun);
    return noun;
}

// @ 0x00c68d20
char COrn::Ed20(int* noun)
{
    int i = 0;
    int n = (int)(mVec4.end - mVec4.begin);
    if (n > 0) {
        for (; i < n; ++i) {
            if (mVec4.begin[i] == noun)
                goto found;
        }
        i = 0;
    }
found:
    float* p = ((cSpatial*)((char*)noun + 0x34))->GetPositionI(i);
    FUN_00c68c00(&mVec4, (Vector3_s00c6_8280*)p, i);
    return 1;
}

// @ 0x00c68d70
void COrn::Ed70(Vector3_s00c6_8280* pos, Vector3Vec* v)
{
    if (FUN_00c649b0(&mVec4, v) != 0) {
        ClearVector(&mVec4);
        int i = 0;
        if ((int)(v->mpEnd - v->mpBegin) > 0) {
            do {
                FUN_00c68c00(&mVec4, &v->mpBegin[i], -1);
                ++i;
            } while (i < (int)(v->mpEnd - v->mpBegin));
        }
        int* first = mVec4.begin[0];
        int* dst = (int*)((char*)first + 0x118);
        dst[0] = ((int*)pos)[0];
        dst[1] = ((int*)pos)[1];
        dst[2] = ((int*)pos)[2];
        H4460(0);
    }
}

// @ 0x00c69030
void COrn::F030()
{
    mCombatant.F_00bfc720();
    mSpatial.Shutdown();
    mTail.F_00abf710();
    int* p = mp2c;
    if (p != 0) {
        mp2c = 0;
        ((TFv_v)VTSLOT(p, 4))(p);
    }
}

// @ 0x00c69090
void COrn::F090()
{
    cGroundLoco* o = (cGroundLoco*)FUN_00f473a0(0x10, "Simulator/cGroundLocomotion", 0, 0, 0, 0);
    if (o != 0) {
        o->mVt8 = (void*)0x13ec458;
        o->mVtC = 0;
        o->mVt0 = (void*)0x146a34c;
        o->mVt8 = (void*)0x1475114;
    }
    mSpatial.F_00c421b0(o);
    void* mgr = FUN_00b3d260();
    if (mgr != 0) {
        void* arg = (void*)&mTail.mVt;
        void* m2 = FUN_00b3d260();
        ((TFv_p)VTSLOT(m2, 0x38))(m2, arg);
    }
}

// @ 0x00c69150
cNanoDrone::cNanoDrone()
{
    mSpatial.mVt = (void*)0x1471780;
    mVt0 = (void*)0x1471728;
    mVt4 = (void*)0x1471718;
    mp1d0 = 0;
    m1d4 = -1;
    mCombatant.mVt = (void*)0x14716b0;
}

// @ 0x00c691e0
int COrn::F1e0(int id)
{
    int r;
    if (id != 0x6ef0ec9) {
        r = ((IQuery*)this)->QI(id);
        if (r == 0) {
            r = ((IQuery*)&mSpatial)->QJ(id);
            if (r == 0)
                return ((IQuery*)((char*)this + 0x108))->QL(id);
        }
    } else {
        r = (int)this;
    }
    return r;
}

// @ 0x00c69290
cNanoDrone::~cNanoDrone()
{
    void* p = mp1d0;
    mVt0 = (void*)0x1471728;
    mVt4 = (void*)0x1471718;
    mSpatial.mVt = (void*)0x1471780;
    mCombatant.mVt = (void*)0x14716b0;
    if (p != 0) {
        ((cAgentOrderManager*)p)->F_00bcae90();
        FUN_00f47380(p);
        mp1d0 = 0;
    }
}

// @ 0x00c697e0
char cGameData_s00c6_9300::Activate(int param)
{
    char ok = Slot40(param);
    if (ok)
        Refresh();
    return ok;
}

// @ 0x00c6ee40
void __fastcall FUN_00c6ee40(void* self, void* /*edx*/, u8 visible, float* pos)
{
  char* p = (char*)self;
  float* bp = pos;
  if (visible == *(u8*)(p + 0x198)) return;
  SP_NounManager();
  *(u8*)(p + 0x198) = visible;
  *(u8*)(p + 0xfc) = 1;
  if (*(u8*)(p + 0x84) == 0) {
    if (visible == 0) { FUN_00c6e710(p, 0, 0); return; }
    FUN_00c6e710(p, 0, 1);
    char* t = *(char**)(p + 0x54);
    char* n0 = *(char**)(t);
    *(u32*)(n0 + 0x1e8) = 0;
    *(u8*)(n0 + 0x1ec) = 1;
    ((void(__thiscall*)(void*, float*))(*(void***)(n0 + 0x34))[0x38 / 4])(n0 + 0x34, bp);
    char* dbg = *(char**)(p + 0x160);
    if (dbg == 0) {
      float d[3];
      void* pm = (void*)FUN_00b3d350();
      FUN_00b7f190(pm, d, bp);
      ((void(__thiscall*)(void*, float*))(*(void***)(n0 + 0x34))[0x3c / 4])(n0 + 0x34, d);
      return;
    }
    void* v = ((void*(__thiscall*)(void*))(*(void***)(dbg + 0x34))[0x30 / 4])(dbg + 0x34);
    ((void(__thiscall*)(void*, void*))(*(void***)(n0 + 0x34))[0x3c / 4])(n0 + 0x34, v);
    return;
  }
  if (visible == 0) { FUN_00c6e710(p, 0, 0); return; }

  s32 adv = FUN_00d52df0(FUN_00d539d0());
  s32 total = adv + 1;
  FUN_00c6e710(p, 0, (u32)total);

  // Two rotation matrices around the sweep angle, multiplied into bp.
  float sweep = DAT_015778b4 * 0.5f;
  float sn = (float)sinf(sweep);
  float cs = (float)cosf(sweep);
  float row0a[3] = { sn, sn * DAT_015778bc, sn * DAT_015778b8 };
  (void)row0a;
  float M0[9];
  M0[0] = cs;
  M0[1] = sn * DAT_015778b8;
  M0[2] = sn * DAT_015778bc;
  M0[3] = sn * DAT_015778c0;
  M0[4] = 0.0f;
  (void)cs;
  float M1[9];
  float sn2 = (float)sinf(sweep);
  float cs2 = (float)cosf(sweep);
  M1[0] = cs2;
  M1[1] = sn2 * DAT_015778c4;
  M1[2] = sn2 * DAT_015778c8;
  M1[3] = sn2 * DAT_015778cc;
  float tmp[9];
  FUN_007dcb00(tmp, M0, M1);
  float p3[3];
  FUN_0059aed0(p3, bp, tmp);
  float up[3];
  float pm2 = (void*)FUN_00b3d350() ? 0.0f : 0.0f;
  (void)pm2;
  void* pl = (void*)FUN_00b3d350();
  FUN_00b7f250(pl, up, bp, p3);

  float axis[3];
  FUN_0059aed0(axis, &DAT_01693ea0, up);
  float inv = 1.0f /
      (float)sqrtf(axis[0] * axis[0] + axis[1] * axis[1] + axis[2] * axis[2]);
  axis[0] *= inv; axis[1] *= inv; axis[2] *= inv;
  float invp = 1.0f /
      (float)sqrtf(bp[0] * bp[0] + bp[1] * bp[1] + bp[2] * bp[2]);
  float upn[3] = { bp[0] * invp, bp[1] * invp, bp[2] * invp };

  s32 i = 0;
  s32 ringCount = 1;
  s32 ringIdx = 0;
  s32 seg = 6;
  if (total <= 0) return;
  do {
    float base[3] = { bp[0], bp[1], bp[2] };
    if (i > 0) {
      s32 act = seg;
      if (seg <= ringIdx) {
        ringCount++;
        act = seg + 6;
        ringIdx = 0;
      }
      float r = (float)ringCount * DAT_01486374;
      float ang = ((float)ringIdx * DAT_01693eac / (float)act) * DAT_01471064;
      float sa = (float)sinf(ang);
      float ca = (float)cosf(ang);
      float upscaled[3] = { upn[0] * sa, upn[1] * sa, upn[2] * sa };
      (void)ca;
      float tmpv[3];
      FUN_0059aed0(tmpv, axis, upscaled);
      base[0] += tmpv[0] * r;
      base[1] += tmpv[1] * r;
      base[2] += tmpv[2] * r;
      ringIdx++;
      seg = act;
    }
    void* pl2 = (void*)FUN_00b3d350();
    float rnd[3];
    FUN_00b81780(pl2, rnd, base, (void*)0x40000000, (void*)0x40a00000);
    float delta[3] = { rnd[0] - base[0], rnd[1] - base[1], rnd[2] - base[2] };
    float ori[9];
    FUN_00b7f250(pl2, ori, base, delta);
    char* noun = *(char**)(*(u32**)(p + 0x54) + i * 4);
    *(u32*)(noun + 0x1e8) = 0;
    *(u8*)(noun + 0x1ec) = 1;
    FUN_00b82970((void*)FUN_00b3d350(), base);
    ((void(__thiscall*)(void*, float*))(*(void***)(noun + 0x34))[0x38 / 4])(noun + 0x34, base);
    ((void(__thiscall*)(void*, float*))(*(void***)(noun + 0x34))[0x3c / 4])(noun + 0x34, ori);
    i++;
  } while (i < total);
}

// @ 0x00c6f3d0
void* __fastcall FUN_00c6f3d0(void* self, void* /*edx*/)
{
  char* p = (char*)self;
  ((void*(__thiscall*)(void*))FUN_00c87660)(self);   // base ctor
  *(u32*)(p + 0x00) = 0x01472008;     // vtbl cObjectInstanceInventoryItem
  *(u32*)(p + 0x08) = 0x01472000;
  *(u32*)(p + 0x0c) = 0x01471fdc;
  *(u32*)(p + 0x7c) = 0;              // mObject
  *(u8*)(p + 0x1c) = 1;              // mbIsUnique
  *(u32*)(p + 0x14) = 8;             // mItemType = ObjectInstance
  return self;
}

// @ 0x00c6f470
u8 __fastcall FUN_00c6f470(void* self, void* /*edx*/, void* stream)
{
  char* p = (char*)self;
  char* a = (char*)((void*(__thiscall*)(void*))(*(void***)stream)[0x20 / 4])(stream);
  u32 tag = 0x073905ae;
  void* s = ((void*(__thiscall*)(void*))(*(void***)a)[0x18 / 4])(a);
  FUN_00e3aa70(s, &tag, 1, 0);
  u8 ok = ((u8(__thiscall*)(void*, void*))FUN_00c87580)(self, stream);
  u32 ser[645];   // cVarListSerializer, 0xa14 bytes
  ((void*(__thiscall*)(void*, void*, void*, int))FUN_00692f90)(
      ser, p - 0xc, (void*)0x01578618, 0x1a80d26);
  u8 ok2 = ((u8(__thiscall*)(void*, void*))FUN_00692900)(ser, stream);
  return (ok2 != 0 && ok != 0);
}

// @ 0x00c6f500
u8 __fastcall FUN_00c6f500(void* self, void* /*edx*/, void* stream)
{
  char* p = (char*)self;
  char* a = (char*)((void*(__thiscall*)(void*))(*(void***)stream)[0x20 / 4])(stream);
  void* s = ((void*(__thiscall*)(void*))(*(void***)a)[0x18 / 4])(a);
  u32 tag;
  FUN_00e3a780(s, &tag, 1, 0);
  u8 ok = ((u8(__thiscall*)(void*, void*))FUN_00c879a0)(self, stream);
  u32 ser[645];   // cVarListSerializer, 0xa14 bytes
  ((void*(__thiscall*)(void*, void*, void*, int))FUN_00692f90)(
      ser, p - 0xc, (void*)0x01578618, 0x1a80d26);
  u8 ok2 = ((u8(__thiscall*)(void*, void*))FUN_00693e10)(ser, stream);
  return (ok2 != 0 && ok != 0);
}

// @ 0x00c6f590
void* __fastcall FUN_00c6f590(void* self, void* /*edx*/, u32 flags)
{
  char* p = (char*)self;
  *(u32*)(p + 0x00) = 0x01472008;
  *(u32*)(p + 0x08) = 0x01472000;
  *(u32*)(p + 0x0c) = 0x01471fdc;
  void* obj = *(void**)(p + 0x7c);
  if (obj != 0) {
    ((void(__thiscall*)(void*))(*(void***)obj)[4 / 4])(obj);
  }
  ((void*(__thiscall*)(void*))FUN_00c87770)(self);
  if (flags & 1) {
    operator_delete_array(self);
  }
  return self;
}

// @ 0x00c6f5e0
void __fastcall FUN_00c6f5e0(void* self, void* /*edx*/, void* obj)
{
  char* p = (char*)self;
  void* old = *(void**)(p + 0x7c);
  if (obj != old) {
    if (obj != 0) {
      ((void(__thiscall*)(void*))(*(void***)obj)[0 / 4])(obj);
    }
    *(void**)(p + 0x7c) = obj;
    if (old != 0) {
      ((void(__thiscall*)(void*))(*(void***)old)[4 / 4])(old);
    }
  }
  if (obj != 0) {
    char* gd = (char*)((void*(__thiscall*)(void*, u32))(*(void***)obj)[0xc / 4])(
        obj, 0x01186577);
    if (gd != 0) {
      *(u8*)(gd + 0x75) = 0;
      u32* q = (u32*)((void*(__thiscall*)(void*))(*(void***)gd)[0xac / 4])(gd);
      if (q != 0) {
        q[1] &= ~1u;
        ((void(__thiscall*)(void*, int))(*(void***)q)[0x16c / 4])(q, 0);
      }
    }
  }
  *(u32*)(p + 0x10) = 1;
}

// @ 0x00c6f660
void* __fastcall FUN_00c6f660(void* self, void* /*edx*/)
{
  char* p = (char*)self;
  void* result = 0;
  if (*(void**)(p + 0x7c) != 0) {
    if (*(void**)(p + 0x7c) != 0) {
      void* obj = *(void**)(p + 0x7c);
      char* gd = (char*)((void*(__thiscall*)(void*, u32))(*(void***)obj)[0xc / 4])(
          obj, 0x01186577);
      if (gd != 0) {
        *(u8*)(gd + 0x75) = 1;
        u32* q = (u32*)((void*(__thiscall*)(void*))(*(void***)gd)[0xac / 4])(gd);
        if (q != 0) {
          q[1] |= 1u;
          ((void(__thiscall*)(void*, int))(*(void***)q)[0x16c / 4])(q, 1);
        }
      }
    }
    result = *(void**)(p + 0x7c);
    *(u32*)(p + 0x7c) = 0;
    if (result != 0) {
      ((void(__thiscall*)(void*))(*(void***)result)[4 / 4])(result);
    }
    *(u32*)(p + 0x10) = 0;
  }
  return result;
}

// @ 0x00c6f6e0
void* SimOrnament::Cast(unsigned type)
{
    if (type == 0x175cdc9) return this;
    if (type == 0x102a041a) return this ? (uchar*)this + 0x210 : 0;
    if (type == 0x8367427)  return this ? (uchar*)this + 0x34 : 0;
    void* r = ((void* (__thiscall*)(void*, unsigned))FUN_00c884f0)(mSpatial_70, type);
    if (r) return r;
    r = ((void* (__thiscall*)(void*, unsigned))FUN_00bfc380)(mCombatant_148, type);
    if (r) return r;
    r = ((void* (__thiscall*)(void*, unsigned))FUN_00b18460)(this, type);
    if (r) return r;
    return ((void* (__thiscall*)(void*, unsigned))FUN_00c751c0)(&mpVftbl_144, type);
}

// @ 0x00c6f770
void SimOrnament::SetStyleModel(int style, void* a, int model)
{
    mStyle_228   = style;
    mModelID_22c = model;
    ((void (__thiscall*)(SimOrnament*, void*))vc(this, 0x48))(this, a);
    if (mStyle_228 == 0x65658d2) mbField_116 = false;
}

// @ 0x00c6f7b0
bool SimSpatial::IsPlayerOwnedOrnament()
{
    SimOrnament* p = (SimOrnament*)((uchar*)this - 0x70);
    void* pMgr = FUN_00b3d300();
    int id = ((int (__thiscall*)(void*))FUN_00b1f9d0)(pMgr);
    int mine = ((int (__thiscall*)(SimOrnament*))((void**)*(void**)p)[0x4c / 4])(p);
    return mine == id;
}

// @ 0x00c6f7f0
SimOrnament::SimOrnament()
{
    ((GameDataBase_s00c6_f6e0*)this)->ctor();
    mpVftbl_34 = &PTR_FUN_0146c56c;
    mPowerupType_38 = 0;
    mInstanceID_3c  = 0;
    mTypeID_40      = 0;
    mGroupID_44     = 0;
    mbField_48      = false;
    mpPropList_4c   = 0;
    mpField20_50    = 0;
    mpField1c_54    = 0;
    mbHasBeenThrown_64 = false;
    mTimeInFlight_68   = 0.0f;
    mpThrowObjective_6c = 0;
    ((SpatialBase_s00c6_f6e0*)mSpatial_70)->ctor();
    mpVftbl_144 = &PTR_FUN_01466c14;
    ((CombatantBase*)mCombatant_148)->ctor();
    ((IntTargetBase*)mIntTarget_210)->ctor();
    *(void**)mSpatial_70 = &vtbl_Simulator_cOrnament;
    mStyle_228   = 0;
    mModelID_22c = 0;
    *(void**)this   = &PTR_AddRef_01472180;
    *(void**)((uchar*)this + 4)       = &PTR_FUN_0147216c;
    mpVftbl_34      = &PTR_FUN_01472160;
    mpVftbl_144     = &PTR_FUN_0147213c;
    *(void**)mIntTarget_210 = &PTR_FUN_01472120;
    mbVisible_230   = true;
    *(void**)mCombatant_148 = &PTR_FUN_014720b8;
}

// @ 0x00c6f990
bool SimOrnament::Write(void* pArchive)
{
    void* p1 = ((void* (__thiscall*)(void*))vc(pArchive, 0x20))(pArchive);
    unsigned id = 0x175cdc9;
    unsigned handle = ((unsigned (__thiscall*)(void*))vc(p1, 0x18))(p1);
    FUN_0093aa70((void*)handle, &id, (void*)1, 0);
    bool b = ((bool (__thiscall*)(void*, void*))FUN_00b18590)(this, pArchive);
    if (b) {
        b = ((bool (__thiscall*)(void*, void*))FUN_00c88a90)(mSpatial_70, pArchive);
    }
    VarListSerializer ser;
    FUN_00692f90(&ser, this, &DAT_01578698, (void*)0x1a80d26);
    if (b) {
        if (FUN_00692900_s00c6_f6e0(&ser, pArchive)) return true;
    }
    return false;
}

// @ 0x00c6fac0
void SimOrnament::Destroy()
{
    void* p = mpRefCount_2c;
    if (p) {
        mpRefCount_2c = 0;
        ((void (__thiscall*)(void*))vc(p, 4))(p);
    }
    ((void (__thiscall*)(void*))FUN_00ac0450)(mIntTarget_210);
    ((void (__thiscall*)(void*))FUN_00c8b2e0)(mSpatial_70);
}

// @ 0x00c6fb80
bool SimSpatial::LoadModelOrnament(void* pModel)
{
    bool ok = ((bool (__thiscall*)(void*, void*))FUN_00c8a550)(this, pModel);
    if (ok) {
        if (mStyle_1b8 == 0x65658d2) {
            SimOrnament* pOrn = (SimOrnament*)((uchar*)this - 0x70);
            void* pv = ((void* (__thiscall*)(void*))vc(this, 0x68))(this);
            float a = *(float*)((uchar*)pv + 0x10);
            if (a < 0) a = -a;
            void* pv2 = ((void* (__thiscall*)(void*))vc(this, 0x68))(this);
            float b = *(float*)((uchar*)pv2 + 4);
            if (b < 0) b = -b;
            float m = a > b ? a : b;
            void* pPlanetModel = ((void* (__thiscall*)(void*, float, int, int))vc(this, 0x2c))(this, m, 0x10000000, 0);
            FUN_00b83c40(FUN_00b3d350(pPlanetModel), m, 0x10000000, 0);
            void* pVec = FUN_00b21340(FUN_00b3d300(), (void*)FUN_00cd7d10, (void*)FUN_00d3d420, (void*)FUN_00acdff0, (void*)FUN_00b1e500, &DAT_018c43e8);
            void* pk = ((void* (__thiscall*)(void*))vc(this, 0x2c))(this);
            void* found = FUN_00ac9310((uchar*)pVec + 4, pk, 0);
            if (found) FUN_00bd9710(found);
        } else if (mStyle_1b8 == 1) {
            int tg = *(int*)((uchar*)this - 0x38);
            if (tg == 0xb || (tg == 0xe && *(int*)((uchar*)DAT_016c7aa4 + 0xcc) == 1)) {
                void* pGd = FUN_00b18530((uchar*)this - 0x70);
                int r = ((int (__thiscall*)(void*))vc(this, 0xac))(this);
                if (r != 0 && (pGd == 0 || *(int*)((uchar*)pGd + 0x24) != 2)) {
                    *(unsigned*)((uchar*)r + 4) |= 0x100;
                    *(uchar*)((uchar*)r + 0x5d) = 1;
                }
            }
        }
    }
    return ok;
}

// @ 0x00c6fcd0
SimCursorAttachment::SimCursorAttachment()
{
    ((GameDataBase_s00c6_f6e0*)this)->ctor();
    ((SpatialBase_s00c6_f6e0*)mSpatial_34)->ctor();
    *(void**)mSpatial_34 = &vtbl_cPlaceholderColonyEditorCursorAttachment;
    *(void**)this       = &PTR_AddRef_014722d8;
    *(void**)((uchar*)this + 4) = &PTR_FUN_014722c4;
}

// @ 0x00c6fd20
void* SimCursorAttachment::Cast(unsigned type)
{
    if (type == 0x2c5c935) return this;
    void* r = ((void* (__thiscall*)(void*, unsigned))FUN_00b18460)(this, type);
    if (!r) r = ((void* (__thiscall*)(void*, unsigned))FUN_00c884f0)(mSpatial_34, type);
    return r;
}

// @ 0x00c6fdc0
void SimCursorAttachment::Destroy()
{
    void* p = mpRefCount_2c;
    if (p) {
        mpRefCount_2c = 0;
        ((void (__thiscall*)(void*))vc(p, 4))(p);
    }
    ((void (__thiscall*)(void*))FUN_00c8b2e0)(mSpatial_34);
}

// @ 0x00c6fe00
int Func6fe00(int type)
{
    switch (type) {
    case 4: case 10: case 11: return 1;
    case 5: case 7: case 8: case 9: return 2;
    case 6: case 12: return 0;
    default: return 0;
    }
}

// @ 0x00c6fe50
bool Func6fe50(WorldObject* pObj)
{
    WorldObject* pType = (WorldObject*)((void* (__thiscall*)(void*))FUN_00b8de30_s00c6_f6e0)(pObj);
    if (((int (__thiscall*)(void*))FUN_00bb9ae0)(pType) != 5) return false;
    void* pAvatar = ((void* (__thiscall*)(void*))FUN_00b1fdb0)(pType);
    void* pMgr = ((void* (__stdcall*)(void*))FUN_00b3d2a0)(pAvatar);
    void* pEmpire = ((void* (__thiscall*)(void*))FUN_00ba9370)(pMgr);
    return ((void* (__thiscall*)(void*))FUN_00c31730)(pEmpire) == pObj;
}
