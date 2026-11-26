// src/game/SPGonzago/SPUISpace.cpp -- migrated from slice(s) s0106cab0, s01078120, s010727e0, s01074bb0, s01079260, s01071a00, s0106f5b0, s01070ba0, s01070290, s010691e0, s01065c30, s00bbca30, s00b181d0, s007f5300, s00433800, s0107a510, s01077470, s010743a0, s0106ea40, s0106da70, s0106c930, s0106ada0, s0106a0a0, s01068800, s010678e0, s01066a40, s01064990, s00bbb9d0, s00b1fd50, s00435d40 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPUISpace.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

// addresses retail relocates here, named so the build relocates them too
extern "C" char g_149c1f0[];

#define _VA_LIST_DEFINED   // the slices' own va_list typedef wins over <vadefs.h> (rewrite.py)
#include "game/types.h"
#include "SP/cArtilleryProjectile.h"
#include "SP/cGameData.h"
#include "SP/cGameNounManager.h"
#include "SP/cVarListSerializer.h"
#include "SP/cCityData.h"
#include <math.h>
#include <intrin.h>
#include "cSPUIAnimator.h"
#include "SP/cSpaceTradeRouteManager.h"
#include "SP/cPlanet.h"
#include "SP/cPlanetRecord.h"
#include "SP/cString.h"
#include "SP/cCivData.h"
#include "SP/cEmpire.h"
#include "SP/cSPMission.h"
#include "EA/Stopwatch.h"
#include "cSPUILayout.h"
#include "EA/UTFWin/Window.h"
#include "SP/cPlanetModel.h"
#include "SP/cPropertyList.h"
#include "SP/cViewer.h"
#include "SP/cStarRecord.h"
#include <stddef.h>
#include "EA/UTFWin/Image.h"
#include "EA/UTFWin/RenderContext.h"
#include "SP/cSPCreatureBase.h"
#include "SP/cSpeciesProfile.h"
#include "SP/cSPSpaceToolData.h"
#include "SP/cStar.h"
#include "SP/cStarManager.h"

// ---- items of slice s00435d40 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Recorder {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
    virtual int GetState();                               // +0x20
virtual void s9();
virtual void s10();
virtual void s11();
virtual void s12();
    virtual void s13();
    virtual void Begin(uint32_t tag);                     // +0x38
    virtual void WriteFloat(uint32_t tag, float v);       // +0x3C
    virtual void WriteInt(uint32_t tag, uint32_t v);      // +0x40
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
    virtual void s21();
    virtual void End();                                   // +0x58
};
Recorder* GetRecorder();                                  // 0x00A206F0
// ---- items of slice s00435d40 end

// ---- items of slice s00b1fd50 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define _VA_LIST_DEFINED   // the slices' own va_list typedef wins over <vadefs.h> (rewrite.py)
extern "C" void* __cdecl memset(void*, int, unsigned);
extern "C" void* __cdecl memmove(void*, const void*, unsigned);
extern "C" void* __cdecl memcpy(void*, const void*, unsigned);
extern char gEmptyChar;  // 0x01667bac
#pragma intrinsic(memset, memmove, memcpy)
struct ByteString {
    char* mpBegin;      // +0x00
    char* mpEnd;        // +0x04
    char* mpCapacity;   // +0x08
    char* mpField0c;    // +0x0c
    char* mpBase;       // +0x10

    void  __thiscall allocate(unsigned n);            // 0xb1ffd0
    void  __thiscall changeCapacity(unsigned n);      // 0xb230b0
    ByteString& __thiscall append(unsigned n, unsigned char c);     // 0xb1ff30
    void  __thiscall resize(unsigned n);              // 0xb20610
    void  Assign(const char* s);                      // 0x006a4380
    void  Assign(const char* b, const char* e);       // 0x00454cb0
};
// ---- items of slice s00b1fd50 end

// ---- items of slice s00bbb9d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int*  GetActivePlanet2();          // 0x8414c0
extern "C" int   TerraDistClass(float a, float b);         // 0xfc2080
extern "C" uint32_t g_dw168a488;              // 0x168a488 empty-key sentinel
extern "C" uint32_t g_dw168a48c;              // 0x168a48c
extern "C" uint32_t g_dw168a490;              // 0x168a490
#pragma warning(disable: 4100)
struct PlanetRecord;
extern "C" PlanetRecord* GetActivePlanet();   // 0x1021260
extern "C" PlanetRecord* GetActivePlanetRecord();  // 0x10212a0
extern "C" int   GetSetting9_s00bb_b9d0();               // 0x401090
struct SpeciesProfile {
    int  EmblemType();                 // 0xb8f860
    uint32_t field_608;                // +0x608
};
struct KeySink {
    void Store3(int a, int b, int c);             // 0xbbc410
    void Store3B(int a, int b, int c);            // 0xbbc460
    void __fastcall StoreEmpty();                 // 0xbbc4a0
};
struct DrawObj {
    void  Flush(unsigned flags);       // 0xb2a750
    void  FUN_00b2bbe0();              // 0xb2bbe0
};
DrawObj* GetDrawObj();                 // 0xb3d3b0
struct PlanetRecord {
    uint8_t  pad_0000[0xb0];
    float    unk_b0;                   // +0xb0
    float    unk_b4;                   // +0xb4
    uint32_t unk_b8;                   // +0xb8
    int      p_bc;                     // +0xbc  (species id array begin)
    int      p_c0;                     // +0xc0  (species id array end)
    uint8_t  pad_c4[0xc];
    int      p_d0;                     // +0xd0  (profile array begin)
    int      p_d4;                     // +0xd4  (profile array end)
    float GetField64();                // 0xc71d30
    void  SetField64(float v);         // 0xc71da0
};
struct PlanetCellMgr {
    void FUN_00c745d0(int one, void* key);   // 0xc745d0
};
struct SpeciesMgr {
    void* FUN_00b3d420(void* key);           // 0xb3d420
    SpeciesProfile* FUN_00b90410(void* id);  // 0xb90410
};
SpeciesMgr* GetSpeciesManager();             // 0x1021260
SpeciesProfile* GetSpeciesProfile(uint32_t key);   // 0x4df550
struct PlanetObj {
    void FUN_00c80680(int one, void* key);   // 0xc80680
};
SpeciesMgr* FUN_00b3d420();      // 0xb3d420
// ---- items of slice s00bbb9d0 end

// ---- items of slice s01064990 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float    gBakePhase;            // 0x016e2830
extern uint32_t gBakePhaseInit;        // 0x016e2834
extern float    gBakePhaseSpeed;       // 0x015b90e0
typedef void  (__thiscall *Tc2ii)(void*, int, int);
typedef void  (__thiscall *Tc3iii)(void*, int, int, int);
typedef int   (__thiscall *TcRi)(void*);
#define VTS(o, off) (*(void**)((char*)*(void**)(o) + (off)))
void*  MessageServer_67dcc0();
void*  __stdcall TM_a_b3d430(int a);
void*  __stdcall TM_b_b3d430(int a, int b);
class CTM
{
public:
    int  Max_bbc670();
    bool A_bbcda0();
    bool B_bbce00();
};
class CLayout
{
public:
    void* FindWindowByID(int id, int flag);
};
class CGlobalUI
{
public:
    void* FindWindowByID(int id);
};
class cSPUISpace
{
public:
    char       mPad00[0x224];
    CGlobalUI* mpGlobalUI;        // +0x224

    void ShowBakeTimeSplash_01065ab0();
    void HideBakeTimeSplash_01065af0();
    bool IsBakeSplashShown_01065b30();
};
class CTerrainIconOwner
{
public:
    char mPad00[0x544];
    int  m544;      // +0x544
    int  m548;      // +0x548
    int  m54c;      // +0x54c
    int  m550;      // +0x550
    int  m554;      // +0x554

    int GetTerrainIcon_01065ba0(int n);
};
// ---- items of slice s01064990 end

// ---- items of slice s01066a40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void*     gDAT_016e2234;   // 0x016e2234 (global "gate" object)
extern float     gF_016e2230;     // 0x016e2230 (bullseye refresh threshold)
extern float     gF_13ec4d0;      // 0x013ec4d0  100.0f
extern float     gF_13f9c6c;      // 0x013f9c6c -100.0f
extern float     gF_13ec4b0;      // 0x013ec4b0    0.6f
extern float     gF_13eb1bc;      // 0x013eb1bc   -1.0f
extern float     gF_1485720;      // 0x01485720    1.0f
extern float     gF_1471064;      // 0x01471064    0.5f
extern float     gF_149c1a0;      // 0x0149c1a0   25.0f
extern float     gF_1485378;      // 0x01485378    0.0f
extern float     gF_1486374;      // 0x01486374  bullseye threshold hi
extern float     gF_13ec434;      // 0x013ec434  bullseye threshold lo
extern char      gS_13f6b3c[];    // 0x013f6b3c  allocator name
extern char      gImg_15b9390[];  // 0x015b9390  far bullseye image key
extern char      gImg_15b939c[];  // 0x015b939c  mid bullseye image key
extern char      gImg_15b93a8[];  // 0x015b93a8  near bullseye image key
typedef unsigned char  byte;
typedef unsigned short wchar16;
extern wchar16   gW_CivConversionBar[];  // 0x014862ec  L"CivConversionBar"
void*     FUN_00b3d230();                             // 0x00b3d230
void*     FUN_00b3d240();                             // 0x00b3d240
void*     FUN_00b3d430(int a);                        // 0x00b3d430  TerraformingManager
void*     FUN_00b3d4d0();                             // 0x00b3d4d0  TriggerMgr
char      FUN_00b5ca60();                             // 0x00b5ca60
void*     FUN_00b3d2a0();                             // 0x00b3d2a0  StarManager
void*     FUN_00b3d4a0();                             // 0x00b3d4a0  CommManager
void* __stdcall FUN_00b3d3e0(int a);                 // 0x00b3d3e0  EventLog (callee cleans arg)
void*     FUN_00b8de30(void* p, float v);             // 0x00b8de30  BioProtectorSort::operator()
void      FUN_00c8b820(void* a, void* b);             // 0x00c8b820
float     FUN_00c8c7f0(void* p, int* out);            // 0x00c8c7f0
float     FUN_00c8c5d0(void* p, int* out);            // 0x00c8c5d0
void*     FUN_00e2f5c0(void* w, void* key);           // 0x00e2f5c0  SetImageFromKey
void*     FUN_01065ba0(int i);                        // (see cSPUISpace::FUN_01065ba0)
float     FUN_00805080();                             // 0x00805080  GetElapsedSeconds
void*     FUN_00f473a0(unsigned n, const char* file, unsigned a, unsigned b,
                        unsigned c, unsigned d);       // 0x00f473a0  operator new
void*     FUN_007f81d0(void* out, void* win, float a, float b, float c, int d); // 0x007f81d0
void*     FUN_005ca960(void* w);                      // 0x005ca960  interface_cast
uint32_t  FUN_00436ce0(float* a, float* b, float* out); // 0x00436ce0  Vector3_Normalize
float     FUN_006994a0(void* a, void* b);             // 0x006994a0  RaySphereIntersect
void      FUN_00808230(void* w, float* p);            // 0x00808230
void*     FUN_01021260();                             // 0x01021260  GetActivePlanet
char      FUN_0102adf0(void* planet);                 // 0x0102adf0  IsMissionActiveAtPlanet
void*     FUN_00b1fdb0(void* mgr);                    // 0x00b1fdb0  cGameNounManager::GetAvatar
void*     FUN_0067caa0();                             // 0x0067caa0  WindowManager
void*     FUN_0067cab0();                             // 0x0067cab0
char      FUN_00801bb0(void* p, uint32_t id);         // 0x00801bb0  CurMgr::FindLocal
void*     FUN_00435e90();                             // 0x00435e90  GetRecorderState
void*     FUN_00435ed0(uint32_t a, void* b);          // 0x00435ed0  KillSetiEffects
void*     FUN_01002bd0();                             // 0x01002bd0  SpaceGameGet
void*     FUN_008105b0(void* layout, uint32_t id, int b); // 0x008105b0 FindWindowByID
void      FUN_00810590(void* layout, int v);          // 0x00810590  SetVisibility
char      FUN_00810070(void* layout);                 // 0x00810070  IsVisible
void*     FUN_008414c0();                             // 0x008414c0
void*     FUN_00b188b0(void* p);                      // 0x00b188b0
void*     FUN_00b187f0(void* p);                      // 0x00b187f0
void*     FUN_00b18810(void* p);                      // 0x00b18810
void*     FUN_00b187d0(void* p);                      // 0x00b187d0
void*     FUN_00b18890(void* p);                      // 0x00b18890
void*     FUN_00b18870(void* p);                      // 0x00b18870
void      FUN_00b69930(void* p, float f, int a);      // 0x00b69930
void      FUN_00b69990(void* p);                      // 0x00b69990
void      FUN_00b5f950_Assign(void* a, void* b);      // 0x00b5f950 (assignment helper)
typedef void   (__thiscall *VF0)(void*);
typedef void*  (__thiscall *VFP)(void*);
typedef void*  (__thiscall *VFP1)(void*, int);
typedef void   (__thiscall *VF1)(void*, int);
typedef void   (__thiscall *VF1P)(void*, void*);
typedef int    (__thiscall *VFI)(void*, int);
typedef char   (__thiscall *VFC0)(void*);
typedef char   (__thiscall *VFCVP)(void*, float*);
typedef void   (__thiscall *VF2)(void*, int, int);
typedef void   (__thiscall *VF2P)(void*, void*, int);
typedef void   (__thiscall *VFMP)(void*, float*);
typedef void   (__thiscall *VFMP2)(void*, float, float);
struct SPUIGlobalUI {                 // the global-UI object (pointer at cSPUISpace+0x224)
    char   IsTooltipVisible();        // 0x00e01380
    void   SetVisibility(int v);      // 0x00e01350
    void*  FindWindowByID(uint32_t id);  // 0x00e012b0
};
struct SPUIEventLog {
    void SetVisibility();             // 0x00dd8da0
};
struct SPUIMeter {
    void Shutdown(int v);             // 0x00e06940
    void PullToFront();               // 0x00e06d50
    void Init0(void* a);              // 0x00e066d0
    void Init1(void* a);              // 0x00e066e0
    void SetValue(int a, int b);      // 0x00e06710
    void SetPos(float a, float b);    // 0x00e06730
};
struct SPUIAnimator {
    void AddAnimation(void* target, void* win, int id);  // 0x007f8d10
};
class AnimRaw {                       // animation handle produced by SPUICreateWindowAnimationTargetScale
public:
    void Destroy();                   // 0x0059a1e0
};
struct CivBar {                        // meter object created through the 0x50-byte alloc
    char  pad_00[0x50];
    void* Ctor(int a, uint32_t b, uint32_t c, const wchar16* name, uint32_t e);  // 0x00e06a10
};
class MeterRef {                       // EA::AutoRefCount<...> ; first dword is the meter pointer
public:
    SPUIMeter* mpMeter;                // +0x00
    MeterRef& operator=(void* p);      // 0x00b5f950
};
struct CommManager_6a40 {
    char IsActive();                   // 0x00ae9390
};
struct GameObject {                    // a game object, passed by pointer as the `int param`
    int GetKind();                     // 0x00b8dab0
};
struct TerraformingManager {
    int GetState();                    // 0x00bbc670
};
struct StarManager {
    void* GetSystemMgr();              // 0x00ba6490
    void* GetEmpireByID(int id);       // 0x00ba9370
};
struct SpaceTradeRouteManager {
    char  SystemHasTradeRouteWithPlayer(void* player, void* avatar);  // 0x01037d30
    float GetTradeRouteScore(void* player, void* avatar);             // 0x01037dd0
};
struct WideObj {
    float GetScaleX();                 // 0x00c70a20
    float GetScaleY();                 // 0x00c709d0
};
struct CGameNounManager {
    char pad_00[0x70];
    void* mpPlayer;                    // +0x70
    int  GetType();                    // 0x00bb9ae0
    void* GetAvatar();                 // 0x00b1fdb0
};
namespace SP {
class cSPUISpace_s0106_6a40 {
public:
    char          pad_00[0x08];
    uint32_t      mTimer8;             // +0x08
    void*         mpLayout;            // +0x0c  (cSPUILayout*)
    char          pad_10[0x224 - 0x10];
    SPUIGlobalUI* mpGlobal;            // +0x224
    char          pad_228[0x52c - 0x228];
    float         mF52c;               // +0x52c
    char          pad_530[0x558 - 0x530];
    void*         mpArr558[4];         // +0x558  (indexed by terraforming state)
    SPUIAnimator* mpAnimator;          // +0x568
    char          pad_56c[0x5ac - 0x56c];
    MeterRef      m5ac;                // +0x5ac  (foodweb meter)
    MeterRef      m5b0;                // +0x5b0  (unlocked-card meter)
    MeterRef      m5b4;                // +0x5b4  (loyalty meter)
    char          pad_5b8[0x5c4 - 0x5b8];
    void*         mp5c4;               // +0x5c4

    char     FUN_01066a40(int param);
    void     FUN_01066d60();
    void     FUN_01066dd0();
    void     ShowForTutorial(int param);  // 0x01066e30 (cSPUISpace::ShowForTutorial)
    void     UpdateTerraformingBullseye();  // 0x01066f20 (cSPUISpace::UpdateTerraformingBullseye)
    uint32_t UpdateCaptureBarsVisibility(int param);
    int      UpdateCaptureBarsVisibility(CGameNounManager* mgr);
    void     FUN_01067720(void* p, float f1, float f2, char flag);  // 0x01067720 (cSPUISpace::FUN_01067720)
    void     FUN_010677b0(CGameNounManager* mgr, float f1, float f2, char flag);  // 0x010677b0 (cSPUISpace::FUN_010677b0)
    void*    FUN_01065ba0(int i);
};  // namespace SP
}
using SP::cSPUISpace_s0106_6a40;
// ---- items of slice s01066a40 end

// ---- items of slice s010678e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const signed char kNibbleSum[];     // 0x0145d1c4 nibble checksum table
extern float             gChargeCache;     // 0x015b9444 cached tool-charge value
extern const float       kFloatNegOne;     // 0x013eb1bc -1.0f
extern void*             gTooltipGate;     // 0x0169d3c8
extern void*             gTokenTranslator; // 0x016e0d08
#pragma warning(disable : 4100)
typedef unsigned int  u32;
typedef unsigned char u8;
extern const u32         kIconTableA[];    // 0x0149c1a4
extern const u32         kIconTableB[];    // 0x0149c1b0
void* SP_NounManager();                    // 0x00b3d300
void* SP_SpaceGameGet();                   // 0x01002bd0
void* SP_GameTimeManager();                // 0x00b3d380
void* SP_GameInputManager();               // 0x00b3d250
void* SP_CommManager();                    // 0x00b3d4a0
void* SP_WindowManager();                  // 0x0067caa0
void* SP_GetActivePlanet();                // 0x01021260
void* SP_GetActivePlanetRecord();          // 0x010212a0
void* SP_GetSettingHost();                 // 0x00401090
void* SP_GetSystemAT();                    // 0x00a206f0
void* SP_GetPlayerEmpire();                // 0x01021300
void* SP_GetStateManager();                // 0x00b3d3f0
void  SP_DeleteArray(void* p);             // 0x00f47380 operator delete[]
float FUN_00c72030(void* civ);             // 0x00c72030
void  SetTooltipText(void* win, void* text, int a, int b);  // 0x00806de0
void  SetImageFromKey(void* win, void* key);                // 0x00e2f5c0
void  FUN_00572020(u32 handle, u32 on);    // 0x00572020
void __stdcall FUN_00812d80(u32 on);       // 0x00812d80
void  FUN_01066180(void* p, float f);      // 0x01066180
void* FUN_005994b0(void* win);             // 0x005994b0
struct Key {
    u32 m0, m1, m2;
};
struct RefObj {                             // Blk28+0x00 payload
    virtual void AddRef();                  // slot 0
    virtual void Release();                 // slot 1
};
struct ObjRel {                             // Blk28+0x08 payload
    virtual void v0();                      // slot 0
    virtual void v1();                      // slot 1
    virtual void Release();                 // slot 2
};
struct Blk28 {
    RefObj* mpRef;      // +0x00
    u32     m04;        // +0x04
    ObjRel* m08;        // +0x08
    u32     m0c;        // +0x0c
    u32     m10;        // +0x10
    u32     m14;        // +0x14
    u32     m18;        // +0x18
    u8      m1c;        // +0x1c
    u8      mPad[3];
    u32     m20;        // +0x20
    u32     m24;        // +0x24

    Blk28* CopyCtor(const Blk28& src);      // 0x01068450
    Blk28& operator=(const Blk28& src);     // 0x010685a0
    Blk28* Destroy(u8 flags);               // 0x010687d0
};
struct cGameNounManager { void* GetPlayerCivilization(); };
struct cGameData {
    float FUN_00fe67b0();
    void* FUN_00fe42a0();
};
struct cLivingUniverse { void* FUN_00c30cb0(); };
struct cSimManager { u8 FUN_01075500(); };
struct cSimThing  { void FUN_01065d20(); };
struct cSpaceGame {
    u8 pad00[0x14];
    cSimThing*   m14;     // +0x14
    cSimManager* m18;     // +0x18
    u8 pad1c[0x50 - 0x1c];
    u32 m50;              // +0x50
    cGameData* GetPlayerTribe();
};
struct cGameTimeManager {
    u8 pad48[0x48];
    u8 m48;               // +0x48
    void DecPauseGate(u32 id);
};
struct cGameInputManager {
    u8 pad110[0x110];
    u32 m110;             // +0x110
};
struct cCommManager {
    u8 IsActive();
    void CloseCommEvent();
    void FUN_00aed2c0(void* a, void* b);
};
struct cAudioSys {                 // EA::Audio system; only slot 0x28 is called
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
    virtual bool a28(u32 h);       // +0x28
};
struct cToolGate  { void* FUN_00cfe780(void* p); };
struct cPlanet {
    void* FUN_00c71e30();
    u8 pad13c[0x13c];
    void* m13c;           // +0x13c
};
struct cPlanetInfo   { u8 pad84[0x84]; void* m84; };      // +0x84
struct cPlanetRecord { u8 pad2c[0x2c]; u32 mFlags; };     // +0x2c
struct cStarRecordRef { void* GetCommContext(); };
struct cPosse {
    void* FindItem(u32 id);
    u8 pad0[0xa4];
    u32 m0a4;             // +0xa4
    u32 m0a8;             // +0xa8
};
struct cGlobalUI { void* FindWindowByID(u32 id); };
struct cLayout   { void* FindWindowByID(u32 id, u32 rec); };
struct cLayoutHolder {
    void* FindWindowByID(u32 id, u32 rec);
    void  FUN_00e369f0();
    void  FUN_00e365a0(u32 a);
};
struct cProgressBar { void Update(float f, void* p); };
struct cSpeciesMgr  { void* GetProfile(const Key& k); };
struct cTokenTranslator {
    u8 pad14[0x14];
    u32 m14;              // +0x14
    u8 pad18[0x24 - 0x18];
    void* m24;            // +0x24
};
struct cWin61c  { void FUN_00e31030(u32 img, u32 a, u32 b, u32 c); };
struct cStateMgr { u8 ShouldShow(u32 id); };
struct cToolObj {
    virtual void s0();
    virtual void s1();        // +0x04
    virtual void s2();
    virtual void s3(u32);     // +0x0c
};
struct cUIWin {
    virtual void  w00();          // 0x00
    virtual u32   w04();          // 0x04
    virtual void  w08();
    virtual void* w0c(u32);       // 0x0c
    virtual void* w10();          // 0x10
    virtual void  w14();
    virtual void  w18();
    virtual void  w1c();
    virtual u32   w20();          // 0x20
    virtual void  w24();
    virtual u32   w28();          // 0x28
    virtual void  w2c();
    virtual void  w30();
    virtual float* w34();         // 0x34
    virtual float* w38();         // 0x38
    virtual void  w3c();
    virtual void  w40();
    virtual void  w44();
    virtual void  w48();
    virtual void  w4c();
    virtual void  w50();
    virtual void  w54();
    virtual void  w58();
    virtual void  w5c();
    virtual void  w60();
    virtual void  w64();
    virtual void  w68(float, float);   // 0x68
    virtual void  w6c();
    virtual void  w70();
    virtual void  w74();
    virtual void  w78();
    virtual void  w7c(u32, u32);       // 0x7c
    virtual void  w80(u32);            // 0x80
};
struct cString {
    u32 m00, m04, m08, m0c;
    u8  m10, m11, mPad[2];
    cString(u32 a, u32 b, const wchar_t* c);   // 0x006b5770
    ~cString();                                // 0x006b5240
    void* GetText();                           // 0x006b55c0
};
typedef u32  (__thiscall *FnRetU32)(void*);
typedef u8   (__thiscall *FnRetU8)(void*);
typedef void (__thiscall *FnV1)(void*, u32);
typedef void (__thiscall *FnV2)(void*, u32, u32);
typedef void (__thiscall *FnV2f)(void*, float, float);
typedef u32  (__thiscall *FnRetU32_1)(void*, u32);
static __forceinline u32 VCallU32(void* o, u32 off) {
    FnRetU32 f = (FnRetU32)((*(void***)o)[off / 4]);
    return f(o);
}
static __forceinline u8 VCallU8(void* o, u32 off) {
    FnRetU8 f = (FnRetU8)((*(void***)o)[off / 4]);
    return f(o);
}
static __forceinline u32 VCallU32a(void* o, u32 off, u32 a) {
    FnRetU32_1 f = (FnRetU32_1)((*(void***)o)[off / 4]);
    return f(o, a);
}
static __forceinline void VCallV1(void* o, u32 off, u32 a) {
    FnV1 f = (FnV1)((*(void***)o)[off / 4]);
    f(o, a);
}
static __forceinline void VCallV2(void* o, u32 off, u32 a, u32 b) {
    FnV2 f = (FnV2)((*(void***)o)[off / 4]);
    f(o, a, b);
}
static __forceinline void VCallV2f(void* o, u32 off, float a, float b) {
    FnV2f f = (FnV2f)((*(void***)o)[off / 4]);
    f(o, a, b);
}
class cSPUISpace_s0106_78e0 {
public:
    u8 pad00[0x1fc];
    cString       mMinimapOffTip;   // +0x1fc
    cString       mMinimapOnTip;    // +0x210
    cGlobalUI*    mpGlobalUI;       // +0x224
    cProgressBar* mpProgressBar;    // +0x228
    u8 pad22c[0x258 - 0x22c];
    cLayout*      mpLayout;         // +0x258
    u8 pad25c[0x478 - 0x25c];
    cString       mTooltipText;     // +0x478
    u8 pad48c[0x530 - 0x48c];
    Blk28*        mpListBegin;      // +0x530
    Blk28*        mpListEnd;        // +0x534
    u8 pad538[0x5a8 - 0x538];
    cLayoutHolder* mpLayoutHolder;  // +0x5a8
    u8 pad5ac[0x5bc - 0x5ac];
    u32           mAudioHandle;     // +0x5bc
    cToolObj*     mpCurrentTool;    // +0x5c0
    cPosse*       mpPosse;          // +0x5c4
    u32           mProgressCount;   // +0x5c8
    u8 pad5cc[0x61c - 0x5cc];
    void*         mpWindow61c;      // +0x61c

    void  FUN_010678e0();
    void  FUN_010679f0();
    void  UpdateToolChargeBar(float f);  // 0x01067aa0 (cSPUISpace::UpdateToolChargeBar)
    u8    FUN_01067b60();
    void  SetToolTip(void* a1, void* a2, void* a3, void* a4, void* a5);  // 0x01067c50 (cSPUISpace::SetToolTip)
    void  FUN_01067e70(void* p1, Key* key);
    Blk28* FUN_01067ef0(u32 id);
    void  FUN_01067f60(u32 on);
    u8    ToggleSlotsUI();  // 0x01067fb0 (cSPUISpace::ToggleSlotsUI)
    u8    ToggleMinimapUI();  // 0x01068080 (cSPUISpace::ToggleMinimapUI)
    u8    UpdateStarMapFilters();  // 0x01068140 (cSPUISpace::UpdateStarMapFilters)
    void  FUN_010681e0(int a, int b);
    void  FUN_01068230();
    void  FUN_010682a0(u32 id);
    void  FUN_01068300();
    void  FUN_01068330();
    bool  FUN_01068350();
    void  FUN_01066230(u32 on);
};
// ---- items of slice s010678e0 end

// ---- items of slice s01068800 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl op_del_array(void* p);                 // 0x00f47380
extern "C" void  __cdecl SP_SetImageFromKey(void* win, void* key); // 0x00e2f5c0
extern "C" void* __stdcall SP_GetMissionManager(void* obj);     // 0x00feb9f0
extern "C" void* __cdecl SP_PropertyManager();   // 0x0067de30
extern "C" void* __cdecl FUN_01021370();                      // 0x01021370
extern "C" void* __cdecl FUN_00e2eba0(void* a);              // 0x00e2eba0
extern "C" void* __cdecl SP_PropertyManager2();               // 0x0067de30
typedef int            s32;
typedef unsigned short u16;
typedef float          f32;
typedef void  (__thiscall* Fn1)(void*, u32);
typedef void  (__thiscall* Fn2)(void*, u32, u32);
typedef void  (__thiscall* FnP)(void*, void*);
typedef void* (__thiscall* FnFind)(void*, u32, u32);
struct EaString16 {
    u32 mpBegin;   // +0x00
    u32 mpEnd;     // +0x04
    u32 mpCap;     // +0x08
    u32 mPad0C;    // +0x0c
};
struct Obj3 {
    void* FUN_c45ca0(EaString16* out);   // 0x00c45ca0
};
struct MissionMgr {
    u32 FUN_febf80();                    // 0x00febf80
};
typedef void  (__thiscall* FnV)(void*);
typedef void  (__thiscall* Fn3P)(void*, u32, u32, void**);
typedef char  (__thiscall* FnProp24)(void*, u32, void**);
struct Property {
    u8  mPad00[0x12];   // +0x00
    u16 mn12;           // +0x12
    u32* GetUInt();     // 0x0041ea00
};
struct Space {
    u8  mPad00[0x544];  // +0x000
    u32 mVal544;        // +0x544
    u32 mVal548;        // +0x548
    u32 mVal54C;        // +0x54c
    u32 mVal550;        // +0x550
    u32 mVal554;        // +0x554
    u32 mVal558;        // +0x558
    u32 mVal55C;        // +0x55c
    u32 mVal560;        // +0x560
    u32 mVal564;        // +0x564
    void FUN_01068f70();
};
#define TF_LOAD(member, key)                                                   \
    member = 0xffffffffu;                                                      \
    if (prop != 0) {                                                           \
        if (((FnProp24)(*(void***)prop)[0x24 / 4])(prop, (key), &out) &&       \
            ((Property*)out)->mn12 == 10)                                      \
            member = *((Property*)out)->GetUInt();                             \
    }
typedef void* (__thiscall* FnC0)(void*, u32);
typedef void  (__thiscall* FnV1_s0106_8800)(void*, u32);
typedef void  (__thiscall* FnV2_s0106_8800)(void*, u32, u32);
typedef void  (__thiscall* FnV0)(void*);
struct Vec3 { u32 x, y, z; };
struct TfSlot {
    void* mpObj00;   // +0x00
    u32   mn04;      // +0x04
    u32   mn08;      // +0x08
    u32   mn0C;      // +0x0c
    u8    mPad10[8]; // +0x10
    u32   mn18;      // +0x18
    u8    mb1C;      // +0x1c
};
extern "C" TfSlot* __stdcall FUN_01067ef0(u32 a);                  // 0x01067ef0
extern "C" u8 __cdecl FUN_00807cb0(void* w, void* key, int arg);   // 0x00807cb0
typedef void  (__thiscall* FnWin2)(void*, u32, u32);
typedef void  (__thiscall* FnWin1)(void*, u32);
struct Slot {
    u8  mPad00[0x28];   // +0x00
    u32 mn28;           // +0x28
    u8  mPad2C[0x88];   // +0x2c
    f32 mfB4;           // +0xb4
    bool FUN_b8d970();          // 0x00b8d970
    bool FUN_b8dac0();          // 0x00b8dac0
    int  FUN_b8dab0();          // 0x00b8dab0
    u32  FUN_b8e090();          // 0x00b8e090
    void FUN_b8dd60(u32* out);  // 0x00b8dd60
    void* FUN_b8dad0();         // 0x00b8dad0
    void* FUN_ecdba0();         // 0x00ecdba0
};
struct Layout {
    void* FindWindowByID(u32 id, u32 one);   // 0x008105b0
};
struct TfMgr {
    int FUN_bbc670();                        // 0x00bbc670
};
struct SpeciesMgr_s0106_8800 {
    void* GetProfile();                      // 0x004df550
};
struct AutoRef {
    void* mpObject;                          // +0x00
    void** AsPPVoidParam();                  // 0x00a16f40
};
extern "C" void* __cdecl FUN_01021300(u32 a);                // 0x01021300
extern "C" u8    __cdecl FUN_00c70150(void* a, void* b);     // 0x00c70150
extern "C" void* __stdcall GetSetting9(u32 id);               // 0x00401090
extern "C" void* __cdecl GetDominantSpeciesThumbnailKey(u32* out, u32 planet); // 0x01065f00
extern "C" u8    __cdecl SP_GetPropertyAsUint32(void* prop, u32 id, u32* out); // 0x004af210
extern "C" void* __stdcall TerraformingManagerFn(void* slot);   // 0x00b3d430
// ---- items of slice s01068800 end

// ---- items of slice s0106a0a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void*       gSpaceTokenTranslator;   // 0x016e0d08, +0xc = active planet record
extern const float kFHalf;                  // 0x01471064  0.5f
extern const float kF10000;                 // 0x013f0620  10000.0f
extern const float kFOne;                   // 0x01485720  1.0f
extern const float kFNeg10000;              // 0x013f4fd0 -10000.0f
extern float       gEfxVec[3];              // 0x016e2824
extern u8          gEfxMatrixSrc[];         // 0x016e2800
void* SP_GetNounManager();                  // 0x00b3d230
void* SP_GetMissionManager();               // 0x00feb9f0
int   SP_IsPlanetArchived();                // 0x01021240
int   FUN_01021230();                       // 0x01021230
void* SP_GetPlayerHomePlanet();             // 0x01021370
u32   SP_GetUniverseContext();              // 0x01021080
void* SP_GetUFOSimulator();                 // 0x00ffbe50
void* SP_GetTriggerManager();               // 0x00b3d4d0
void* SP_EffectsManager();                  // 0x0067ddd0
void* SP_GetHUDSpaceFrame();                // 0x0067caf0
void* SP_GetSystemNounManager();            // 0x00b3d410
u32   FUN_00458a40(void* rgb);              // 0x00458a40  ColorRGBToU32
u32   FUN_00c8b540();                       // 0x00c8b540
u32   FUN_00c70e00();                       // 0x00c70e00
u8    FUN_00c70b50();                       // 0x00c70b50
void  FUN_01066630(void* p);                // 0x01066630
void  FUN_0041cb40(void* dst, void* src);   // 0x0041cb40  Matrix3::Assign
class cUIWin_s0106_a0a0 {
public:
    virtual void  w00();
    virtual void  w04();
    virtual void  w08();
    virtual void* w0c(u32);
    virtual void* w10();
    virtual void  w14();
    virtual void  w18();
    virtual void  w1c();
    virtual u32   w20();
    virtual void  w24();
    virtual void  w28(u32, u32);              // 0x28
    virtual void  w2c();
    virtual void  w30();
    virtual void* w34();
    virtual void* w38();
    virtual void  w3c();
    virtual void  w40();
    virtual void  w44();
    virtual void  w48();
    virtual void  w4c();
    virtual void  w50();
    virtual void  w54();
    virtual u8    w58();
    virtual void  w5c();
    virtual void  w60(void*);
    virtual void  w64(float, float);
    virtual void  w68();
    virtual void  w6c();
    virtual void  w70(float, float);
    virtual void  w74(float, float);
    virtual void  w78();
    virtual void  w7c(u32, bool);              // 0x7c
    virtual void  w80(void*);
};
struct cUIWinNoArgs {                          // layout windows (slot 0x28 returns u8)
virtual void w00();
virtual void w04();
virtual void w08();
virtual void w0c();
virtual void w10();
virtual void w14();
virtual void w18();
virtual void w1c();
virtual void w20();
virtual void w24();
virtual u8 w28();
};
struct cObj238 { u32 FUN_00ff3f00(); };
struct cNounManager { u8 FUN_00b5ca60(); };
struct cGameNounManager_s0106_a0a0 { void* GetAvatar(); };
struct cGameInputManager_s0106_a0a0 { u8 FUN_00e393b0(); };
struct cTriggerManager { u8 FUN_00ac80f0(); };
struct cAvatar { u8 FUN_00ff6360(); };
struct cSpaceInventory { u8 m74c; };
struct cUFOSimulator { void* GetPlayerInventory(); };
struct cCommMgr { u8 SpaceToolSelect(void* rec, void* ctx); };
struct cCommScreen { u8 IsActive(); };
struct cHud { u8 IsShown(); };
struct cMission {
    u8    IsActive();                          // 0xc44c80
    void* GetModel();                          // 0xc45ce0
};
struct cMissionManager { void** GetMissionList(); };  // 0xfedd50
struct cBannerSort { void* SortBanners(); };           // 0xb8de30
struct cCivData { void** GetCities(void* a, void* b); };
struct cPlanet_s0106_a0a0 {
    void* GetName();  // 0x00c707e0 (cPlanet::GetName)
    void* FUN_00c71e30();
};
struct cEmpire {
    u8    pad84[0x84];
    void* m84;                                 // +0x84
    u8    FUN_00c30910();                      // 0xc30910
    void* GetColor(void* out);                 // 0xc32cd0
};
struct cEfxNode {
virtual void e00();
virtual void e04();
virtual void e08();
virtual void e0c();
virtual void e10();
virtual void e14();
virtual void e18(void*);
virtual void e1c();
virtual void e20();
virtual void e24();
virtual void e28();
virtual void e2c();
};
struct cEffectsMgr {
virtual void m00();
virtual void m04();
virtual void m08();
virtual void m0c();
virtual void m10();
virtual void m14();
virtual void m18();
virtual void m1c();
virtual void m20();
virtual void m24();
virtual void m28();
    virtual u8   m2c(u32 id, u32 a, void* out);
};
class cSPUISpace_s0106_a0a0 {
public:
    u8            pad00[0x224];
    cGlobalUI*    mpGlobalUI;      // +0x224
    u8            pad228[0x238 - 0x228];
    cObj238*      m238;            // +0x238
    u8            pad23c[0x258 - 0x23c];
    cLayout*      mpGlobalLayout;  // +0x258
    u8            pad25c[0x478 - 0x25c];
    cString       mTooltipText;    // +0x478
    u8            pad48c[0x598 - 0x48c];
    void*         mGlowInfoList;   // +0x598
    u8            pad59c[0x5cc - 0x59c];
    u32           mDial;           // +0x5cc
    u8            m5d0;            // +0x5d0
    u8            m5d1;            // +0x5d1
    u8            m5d2;            // +0x5d2

    u32   UpdateMissionRollover(u32 a0, u32 a1, u32 a2, u32 a3);  // 0x0106a0a0 (cSPUISpace::UpdateMissionRollover)
    void  FUN_0106a280();  // 0x0106a280 (cSPUISpace::FUN_0106a280)
    void  UpdateActivePlanetInfo();  // 0x0106a4e0 (cSPUISpace::UpdateActivePlanetInfo)
    void  UpdateCommButtons(void* outState, void* outColor);  // 0x0106a7b0 (cSPUISpace::UpdateCommButtons)
    void  FUN_0106a970();  // 0x0106a970 (cSPUISpace::FUN_0106a970)
    void  FUN_0106aa10(u32 on);  // 0x0106aa10 (cSPUISpace::FUN_0106aa10)
    void  FUN_0106aab0(u32 on);  // 0x0106aab0 (cSPUISpace::FUN_0106aab0)
    void  FUN_0106ab20(int state);  // 0x0106ab20 (cSPUISpace::FUN_0106ab20)
    void  FUN_0106ac90(void* civ);

    // members defined in other slices
    u8    ToggleSlotsUI();         // 0x01067fb0
    u8    ToggleMinimapUI();       // 0x01068080
    u8    UpdateStarMapFilters();  // 0x01068140
    void  FUN_01066230(u32 on);    // 0x01066230
    u8    FUN_01065b30();          // 0x01065b30
    void  FUN_01068800(u32 a, void* b, u32 c);  // 0x01068800
    void* GetDominantSpeciesThumbnailKey(u32* out, u32 planet); // 0x01065f00
};
typedef void* (__thiscall *FnRetP0)(void*);
typedef void* (__thiscall *FnRetP2)(void*, u32, u32);
typedef void  (__thiscall *FnV1p_)(void*, void*);
typedef void  (__thiscall *FnV2f_)(void*, float, float);
typedef void  (__thiscall *FnV2u_)(void*, u32, u32);
static __forceinline void* VCallP0(void* o, u32 off) {
    FnRetP0 f = (FnRetP0)((*(void***)o)[off / 4]); return f(o);
}
static __forceinline void* VCallP2(void* o, u32 off, u32 a, u32 b) {
    FnRetP2 f = (FnRetP2)((*(void***)o)[off / 4]); return f(o, a, b);
}
static __forceinline void VCallV1p(void* o, u32 off, void* a) {
    FnV1p_ f = (FnV1p_)((*(void***)o)[off / 4]); f(o, a);
}
static __forceinline void VCallV2f_s0106_a0a0(void* o, u32 off, float a, float b) {
    FnV2f_ f = (FnV2f_)((*(void***)o)[off / 4]); f(o, a, b);
}
static __forceinline void VCallV2u(void* o, u32 off, u32 a, u32 b) {
    FnV2u_ f = (FnV2u_)((*(void***)o)[off / 4]); f(o, a, b);
}
// ---- items of slice s0106a0a0 end

// ---- items of slice s0106ada0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t DAT_015b9108;   // 0x015b9108
extern void*    DAT_01667bac;   // 0x01667bac  eastl::gEmptyString16
extern uint32_t DAT_01667bae;   // 0x01667bae
extern void* FUN_00805ea0(void* out);                                   // 0x805ea0 SPUIHelpers::GetMainWindowArea
extern void* FUN_00b3d3d0();                                            // 0xb3d3d0
extern void* FUN_00b3d3f0(int a, int b);                                // 0xb3d3f0
extern void* FUN_00b3d3e0(int,int,int,int,int,int);                     // 0xb3d3e0 SP::EventLog
extern void* FUN_00a206f0();                                            // 0xa206f0 EA::Audio::GetSystemAT
extern void  FUN_00435ed0(int a, void* b);                              // 0x435ed0 SP::cSPUISpace::KillSetiEffects
extern void  FUN_00807cb0(void* a, void* b);                            // 0x807cb0
extern void* FUN_008099a0(void* a, int b, int c);                       // 0x8099a0 SPUIHelpers::BeginModal
extern void* FUN_0067cac0(int a, int b);                                // 0x67cac0
extern void* FUN_0067de30();                                            // 0x67de30 SP::PropertyManager
extern void  FUN_006a1360(void* prop, int key, void* out);              // 0x6a1360 SP::GetPropertyAsText
extern void  FUN_006a12a0(void* prop, int key, void* out);              // 0x6a12a0 SP::GetPropertyAsKeyInstance
extern void  FUN_00f47380(void* p);                                     // 0xf47380 operator_delete_array
extern void* FUN_00f473a0(int size, const char* name, int a, int b, void* alloc, int line);  // 0xf473a0 operator_new
extern void  FUN_00806230(void* res, void** out, int a, int b, int c);  // 0x806230 CreateImageFromResource2
extern void* FUN_0067dcd0();                                            // 0x67dcd0 EA::ResourceMan::GetManager
extern void* FUN_009512c0();                                            // 0x9512c0
extern void* FUN_009512d0(int a, int b, const char* name, void* c);     // 0x9512d0
extern void* FUN_00c37230(void* a, void* b, void* c);                     // 0xc37230
extern void* FUN_00ffbe50(int a, int b);                                // 0xffbe50 SP::GetUFOSimulator
extern void* FUN_00b3d380();                                            // 0xb3d380 SP::GameTimeManager
extern void* FUN_01021240(void* a);                                     // 0x1021240
extern float FUN_010434e0(void* a);                                     // 0x10434e0
extern void  FUN_00572020(void* a, int b);                              // 0x572020
extern void  FUN_00434040(void* msg);                                   // 0x434040 XformMsg::XformMsg
extern void  FUN_00571d40(void* msg, void* cities);                     // 0x571d40
extern void* FUN_0067ddd0();                                            // 0x67ddd0 SP::EffectsManager
struct Vtbl { void* mSlots[0x120 / 4]; };
typedef void  (__thiscall *VFn_v)(void*);
typedef void* (__thiscall *VFn_p)(void*);
typedef char  (__thiscall *VFn_c)(void*);
typedef int   (__thiscall *VFn_i)(void*);
typedef void  (__thiscall *VFn_vi)(void*, int);
typedef void* (__thiscall *VFn_pi)(void*, int);
typedef char  (__thiscall *VFn_ci)(void*, int);
typedef void  (__thiscall *VFn_vii)(void*, int, int);
typedef void* (__thiscall *VFn_pii)(void*, int, int);
typedef void  (__thiscall *VFn_vp)(void*, void*);
typedef void  (__thiscall *VFn_vff)(void*, float, float);
typedef void  (__thiscall *VFn_vpp4)(void*, void*, void*, int, int, int);
#define VSLOT(o, n) (((Vtbl*)*(void**)(o))->mSlots[(n) / 4])
extern int   FUN_01021080_s0106_ada0();                                            // 0x1021080 SP::cSPLivingUniverse::GetUniverseContext
struct Engine {
    void* FUN_00e19350();                 // 0xe19350
    void* FUN_00bfc5f0();                 // 0xbfc5f0  cGameNounManager::GetPlayerTribe
    char  FUN_00fe3df0(int a);            // 0xfe3df0
    void* FUN_00fe54d0(int a);            // 0xfe54d0
    void* FUN_00fe5520(int a, int b, void* out);   // 0xfe5520 GetBadgeImageKey
    void  FUN_00fe4710(int a, void* out);          // 0xfe4710 GetBadgeName
    void  FUN_00fe4830(int a, void* out);          // 0xfe4830 GetBadgeHintActionString
    void  FUN_00fe49a0(int a, void* out);          // 0xfe49a0
    int   FUN_0067c420(int a, int b);              // 0x67c420 cUIHints::SetFlag
    char  FUN_0103a040();                          // 0x103a040
    void* FUN_0103a060();                          // 0x103a060
    void  FUN_01068230();                          // 0x1068230
    void* FUN_00e012b0(int id);                    // 0xe012b0 cSPUIGlobalUI::FindWindowByID
    void* FUN_00fe24c90(int item);                 // 0xe24c90 cSPUIPosse::FindItem
    void* FUN_00e259d0(void* arg);                 // 0xe259d0 cSPUIPosseItemSpace ctor
    char  FUN_00bb9fb0();                          // 0xbb9fb0
    void* FUN_00a1ad60();                          // 0xa1ad60 GetPlayerInventory
    float FUN_00ffbfd0();                          // 0xffbfd0 Simulator::cSpatialObject::GetMaxZ
    void  FUN_00c389c0(int a, int b);              // 0xc389c0
    char  FUN_00d09660();                          // 0xd09660
    void* FUN_005c65e0();                          // 0x5c65e0 SP::cCivData::GetCities
    void  FUN_00e01350();                          // placeholder holder, unused
};
struct Node { Node* mNext; Node* mPrev; void* mData; };
struct NodeIterator {
    Node* mpNode;
    NodeIterator(const NodeIterator& other) : mpNode(other.mpNode) {}
    bool operator!=(const NodeIterator& other) const { return mpNode != other.mpNode; }
    NodeIterator& operator++() { mpNode = mpNode->mNext; return *this; }
    void*& operator*() const { return mpNode->mData; }
};
struct Hashtable {
    uint32_t mPad00;        // +0x00
    int*     mpBuckets;     // +0x04
    uint32_t mBucketCount;  // +0x08
    int*     find(void* itOut, void* key);   // 0xa3b2c0  eastl hashtable find (thiscall)
};
struct BadgeHashNode { int mField00; int mValues[1]; };
struct ResourceDesc { void* mResource; uint32_t mKey; uint32_t mType; };
struct BadgeNameBuf {
    uint32_t mBegin;    // +0x00
    uint32_t mField04;  // +0x04
    uint32_t mEnd;      // +0x08
    uint32_t mField0c;  // +0x0c
    uint32_t mTag;      // +0x10
};
struct Vec4 { float mX; float mY; float mZ; float mW; };
struct MsgHeader { int mType; int mId; };
struct XformMsg_s0106_ada0 { uint8_t mBytes[0x40]; };
struct SpaceGame       { uint8_t mPad00[0x20]; void*    mOwner; };        // +0x20
struct GameTimeManager_s0106_ada0 { uint8_t mPad00[0x48]; uint32_t mState; };        // +0x48
struct TriggerManager  { uint8_t mPad00[0x2c]; int      mMode; };         // +0x2c
struct GameNounManager { uint8_t mPad00[0xa0]; uint8_t  mHasSetiBadge; }; // +0xa0
struct ResourceList    { uint8_t mPad00[0x178]; uint8_t* mBegin; uint8_t* mEnd; }; // +0x178
struct cSPUISpace_s0106_ada0 {
    uint8_t   mPad000[0x224];
    void*     mGlobalUI;            // +0x224
    uint8_t   mPad228[0x2a0 - 0x228];
    Hashtable mBadgeTable;          // +0x2a0
    uint8_t   mPad2ac[0x594 - 0x2ac];
    void*     mSetiEffect;          // +0x594
    uint8_t   mPad598[0x5b8 - 0x598];
    void*     mSetiId;              // +0x5b8
    void*     mSetiHandle;          // +0x5bc
    void*     mSetiFX;              // +0x5c0
    void*     mPosse;               // +0x5c4

    void FUN_0106ada0();  // 0x0106ada0 (cSPUISpace::FUN_0106ada0)
    void FUN_0106b220(void* badge);  // 0x0106b220 (cSPUISpace::FUN_0106b220)
    void ManageSeti(void* civ, int arg2);  // 0x0106b310 (cSPUISpace::ManageSeti)
    void FUN_0106b500(void* item);  // 0x0106b500 (cSPUISpace::FUN_0106b500)
    void FUN_0106b630();  // 0x0106b630 (cSPUISpace::FUN_0106b630)
    int  FUN_0106b9b0(int key, int index);  // 0x0106b9b0 (cSPUISpace::FUN_0106b9b0)
    void FUN_01068230();            // 0x1068230 thiscall callee used by ManageSeti
};
// ---- items of slice s0106ada0 end

// ---- items of slice s0106c930 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef char  (__thiscall *VFn_cpp)(void*, void*, void*, int);
typedef int*  (__thiscall *VFn_pvp)(void*, void*);
struct ToolKeyOut { uint32_t mHash; uint32_t mPad0; uint32_t mPad1; };
struct InputMgr_s0106_c930 {
    char IsActiveMode();                 // 0x00fd9d00  input manager mode test
};
InputMgr_s0106_c930* FUN_00fd9c60();                // 0x00fd9c60  InputManager::Get
struct EffectsMgr_s0106_c930 {
    char FUN_00b5ca60();                 // 0x00b5ca60
};
EffectsMgr_s0106_c930* FUN_00b3d230_s0106_c930();              // 0x00b3d230  SP::EffectsManager
int  FUN_01021080_s0106_c930();                     // 0x01021080  SP::cSPLivingUniverse::GetUniverseContext
struct SimCheck {
    char FUN_00d09660();                 // 0x00d09660
};
struct SpaceGame_s0106_c930 {
    uint8_t   mPad00[0x20];
    SimCheck* mSimCheck;                 // +0x20
};
SpaceGame_s0106_c930* FUN_01002bd0_s0106_c930();               // 0x01002bd0  SP::SpaceGameGet
struct cSpaceTool;
struct cSpaceToolView {
    cSpaceTool* GetShownTool();          // 0x00ff3f00  currently shown item
    cSpaceTool* GetOtherTool();          // 0x00ff3f10
};
struct cToolStrategy;                    // virtual slots 0x24 / 0x3c
struct cSpaceTool {
    cToolStrategy* GetStrategy();        // 0x0104f930  dispatch the tool strategy
    char FUN_0104ff10();                 // 0x0104ff10
    char FUN_0104bd50();                 // 0x0104bd50
};
struct cStar;
struct cSPSimulatorPlayerUFO {
    cStar* GetStarRecordUnderMouse();    // 0x00fff8e0
};
cSPSimulatorPlayerUFO* FUN_00ffbe50();   // 0x00ffbe50  SP::GetUFOSimulator
struct cEmpire_s0106_c930 {
    uint8_t  mPad00[0x84];
    uint32_t mEmpireKey;                 // +0x84
};
struct cStarManager {
    cEmpire_s0106_c930* GetEmpireByID(uint32_t avatarID);   // 0x00ba9370 (ret 4)
};
cStarManager* FUN_00b3d2a0_s0106_c930();            // 0x00b3d2a0  SP::StarManager
struct cStar {
    uint8_t  mPad00[0x70];
    uint32_t mKey;                       // +0x70
    int  GetState();                     // 0x00bb9ae0
    uint32_t GetAvatar();                // 0x00b1fdb0
};
struct cCommMgr_s0106_c930 {
    char Has();                           // 0x00ae9c10
};
cCommMgr_s0106_c930* __stdcall FUN_00b3d4a0(uint32_t empireKey, uint32_t starKey); // 0x00b3d4a0 SP::CommManager
struct CurMgr_s0106_c930 {
    uint32_t GetCursor();                // 0x008013c0
    char     FindLocal(uint32_t id);     // 0x00801bb0
};
CurMgr_s0106_c930* FUN_0067cab0_s0106_c930();                  // 0x0067cab0  GetCurMgr
struct cSPUISpace_s0106_c930 {
    uint8_t          mPad000[0x238];
    cSpaceToolView*  mToolView;          // +0x238

    int  FUN_0106b9b0(int key, int index);   // 0x0106b9b0 badge-table lookup
    void FUN_0106c930();                     // 0x0106c930
};
// ---- items of slice s0106c930 end

// The already-landed 0x0106cbd0 (SP::cIntrusiveNode::Construct) needs this stub, but the slice source no longer
// defines it, so a re-apply of s0106c930 would drop it from that slice's items section.  Kept here, outside the
// section, so the landed block keeps compiling (report work/migrate/report_s0106c930_SPUISpace.md).
namespace SP {
struct cIntrusiveNode {
    cIntrusiveNode* mpNext;                                  // +0x00
    cIntrusiveNode* mpPrev;                                  // +0x04

    void Init(cIntrusiveNode* self, void* value, void** src, uint32_t dummy); // 0x0106b950
    void* Construct(void** src);
};
}

// ---- items of slice s0106da70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* gOneBucket[1];                                // 0x0154df28
void operator_delete__(void* p);                                          // 0x00f47380
void EA_Messaging_RemoveHandler(void* h, uint32_t a, uint32_t b, uint32_t c, uint32_t d);  // 0x00571db0
struct IRel1 { virtual void v0(); virtual void Release(); };              // Release at +4
struct IRel2 { virtual void v0(); virtual void v1(); virtual void Release(); };  // Release at +8
struct Arc1 { IRel1* p; Arc1() : p(0) {} ~Arc1() { if (p) p->Release(); } };
struct Arc2 { IRel2* p; Arc2() : p(0) {} ~Arc2() { if (p) p->Release(); } };
struct AutoHandler {
    void*    mpHandler;
    uint32_t mk1, mk2, mk3, mk4;
    AutoHandler() : mpHandler(0), mk1(0), mk2(0), mk3(0), mk4(0) {}
    ~AutoHandler()
    {
        if (mpHandler) {
            void* h = mpHandler;
            mpHandler = 0;
            EA_Messaging_RemoveHandler(h, mk1, mk2, mk3, mk4);
        }
    }
};
struct EAStopwatch {                                                       // EA::Stopwatch
    uint32_t md[9];
    EAStopwatch(int /*bStart*/, bool /*bReset*/);                          // 0x0093a560
};
struct ToolUiState {                                                       // 0x00..0x30
    uint32_t m0, m1, m2;
    ToolUiState() : m0(0), m1(0), m2(0) {}
    ~ToolUiState();                                                        // 0x0106cc00
};
struct cPlanet;
struct IWindow {
    virtual void     v00();
    virtual void     v01();
    virtual void     v02();
    virtual IWindow* v0c(uint32_t id);                     // +0x0c
    virtual void     v10();
    virtual void     v14();
    virtual void     v18();
    virtual void     v1c();
    virtual void     v20();
    virtual void     v24();                                // +0x24
    virtual void     v28(int a, bool b);                   // +0x28
    virtual void     v2c();
    virtual void     v30();
    virtual void     v34(uint32_t id);                     // +0x34
    virtual bool     v38(uint32_t id);                     // +0x38
    virtual void     v3c();
    virtual void     v40();
    virtual void     v44();
    virtual void     v48();
    virtual void     v4c();
    virtual void     v50();
    virtual void     v54(const wchar_t* text);             // +0x54
    virtual void     v58();
    virtual void     v5c();
    virtual void     v60();
    virtual void     v64();
    virtual void     v68();
    virtual void     v6c();
    virtual void     v70();
    virtual void     v74();
    virtual void     v78();
    virtual void     v7c(bool show, bool flag);            // +0x7c
    virtual void     v80(const wchar_t* text);             // +0x80
    virtual void     v84();
    virtual void     v88();
    virtual void     v8c();
    virtual void     v90();                                // +0x90
};
struct cSPUIGlobalUI {
    IWindow* FindWindowByID(uint32_t id);                  // 0x00e012b0
};
struct cSPUILayout_s0106_da70 {
    IWindow* FindWindowByID(uint32_t id, bool searchChildren);   // 0x008105b0
};
struct DeqNode {
    uint32_t*  mpCurrent;
    uint32_t*  mpBegin;
    uint32_t*  mpEnd;
    uint32_t** mpCurrentArrayPtr;
};
struct UIntDeque {
    uint32_t** mpPtrArray;
    int        mnPtrArraySize;
    DeqNode    mItBegin;
    DeqNode    mItEnd;

    void DoPushBackSlow(const uint32_t& value);            // 0x00502dd0

    __forceinline void push_back(const uint32_t& value)
    {
        uint32_t* pCurrent = mItEnd.mpCurrent;

        if ((pCurrent + 1) != mItEnd.mpEnd) {
            mItEnd.mpCurrent = pCurrent + 1;
            if (pCurrent)
                *pCurrent = value;
        } else {
            DoPushBackSlow(value);
        }
    }
};
struct EaHashNode {
    uint32_t      mKey;
    void*         mpValue;
    EaHashNode*   mpNext;
};
struct EaHashTable {
    uint32_t      pad0;
    EaHashNode**  mpBuckets;
    uint32_t      mnBuckets;
    uint32_t      mnElements;

    void DoFreeNodes(EaHashNode** pBuckets, uint32_t nBuckets);   // 0x006b6570

    ~EaHashTable()
    {
        DoFreeNodes(mpBuckets, mnBuckets);
        mnElements = 0;
        if (mnBuckets > 1)
            operator_delete__(mpBuckets);
    }
};
struct HashView {
    uint32_t      pad0;
    EaHashNode**  mpBuckets;
    uint32_t      mnBuckets;
    uint32_t      mnElements;
};
struct ITracerBase  { virtual ~ITracerBase() {} };         // vftable +0x00
struct CVSBase      { virtual ~CVSBase() {} uint32_t mValue; CVSBase() : mValue(0) {} };   // vftable +0x04, value +0x08
struct PaintBase    { virtual ~PaintBase() {} };           // vftable +0x0c
class cSPUIBase : public ITracerBase, public CVSBase, public PaintBase {
public:
    uint32_t    m10, m14, m18;                    // 0x10
    Arc2        m1c;                              // 0x1c
    Arc1        m20, m24, m28, m2c;               // 0x20
    ToolUiState m30;                              // 0x30
    uint32_t    m3c, m40;                         // 0x3c (not initialised)
    uint32_t    m44, m48, m4c, m50, m54, m58, m5c, m60, m64, m68, m6c, m70, m74, m78, m7c;
    uint32_t    m80[17];                          // 0x80 (not initialised)
    uint32_t    mC4;                              // 0xc4 (not initialised)
    EAStopwatch mStopwatch;                       // 0xc8
    AutoHandler mHandler0;                        // 0xec
    AutoHandler mHandler1;                        // 0x100
    AutoHandler mHandler2;                        // 0x114
    AutoHandler mHandler3;                        // 0x128
    uint32_t    m13c;                             // 0x13c

    cSPUIBase();
};
class cSPUISpace_s0106_da70 : public cSPUIBase {
public:
    EaHashTable mToolStrategies;                  // 0x140
    float       mf150;                            // 0x150
    float       mf154;                            // 0x154
    uint32_t    m158;                             // 0x158

    uint32_t       pad15c_178[7];                 // 0x15c .. 0x177
    cSPUILayout_s0106_da70*   mpLayout;                      // 0x178
    uint32_t       pad17c_224[0x2a];              // 0x17c .. 0x223
    cSPUIGlobalUI* mpGlobalUI;                    // 0x224
    uint32_t       pad228_23c[5];                 // 0x228 .. 0x23b
    uint32_t       m23c;                          // 0x23c
    uint32_t*      mpIdsBegin;                    // 0x240
    uint32_t*      mpIdsEnd;                      // 0x244
    uint32_t*      mpIdsCap;                      // 0x248
    uint32_t       pad24c_25c[4];                 // 0x24c .. 0x25b
    HashView       mHash25c;                      // 0x25c
    uint32_t       pad26c_27c[4];                 // 0x26c .. 0x27b
    uint32_t*      mpSortedBegin;                 // 0x27c
    uint32_t*      mpSortedEnd;                   // 0x280
    uint32_t       pad284_594[0xc4];              // 0x284 .. 0x593
    IWindow*       mpActiveWindow;                // 0x594
    uint32_t       pad598_5a8[4];                 // 0x598 .. 0x5a7
    IWindow*       mpTipWindow;                   // 0x5a8
    uint32_t       pad5ac_5d8[0xb];               // 0x5ac .. 0x5d7
    uint32_t*      mpIdArray;                     // 0x5d8
    uint32_t*      mpIdArrayEnd;                  // 0x5dc
    uint32_t       pad5e0_5ec[3];                 // 0x5e0 .. 0x5eb
    UIntDeque      mToolWindowDeque;              // 0x5ec

    cSPUISpace_s0106_da70();  // 0x0106e2d0 (cSPUISpace::cSPUISpace_s0106_da70)

    void UpdateTravelLine(int mode);                          // 0x0106cc70
    void UpdatePlanetRollover(cPlanet* pPlanet);              // 0x0106ba00
    void UpdateStarMapFilters();                              // 0x01068140
    void ToggleToolUI(uint32_t id);                           // 0x0106e3e0
    void FUN_0106aa10(bool b);  // 0x0106aa10 (cSPUISpace::FUN_0106aa10)
    void PushToolWindowId(uint32_t id);                       // 0x0106dcd0
    void FUN_0106dd10(uint32_t index, uint32_t value);  // 0x0106dd10 (cSPUISpace::FUN_0106dd10)
    void AddCursors();                                        // 0x0106e020
    void OnContextDeactivate();                               // 0x0106e270
    void FUN_0106e5e0();  // 0x0106e5e0 (cSPUISpace::FUN_0106e5e0)
    void FUN_0106e630();  // 0x0106e630 (cSPUISpace::FUN_0106e630)
    void FUN_0106e680(uint32_t id);  // 0x0106e680 (cSPUISpace::FUN_0106e680)
    void SetToolTipForItem(uint32_t toolId, void* pItem);     // 0x0106e720
    void FUN_0106e940(uint32_t index);  // 0x0106e940 (cSPUISpace::FUN_0106e940)
};
// ---- items of slice s0106da70 end

// ---- items of slice s0106ea40 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator_new(unsigned size, const char* name, int a, int b, int c, int d);  // 0x00f473a0
void* mem_copy(void* dst, const void* src, unsigned n);                           // 0x011e0744
u32   SP_GetPlayerEmpireID();   // 0x01021090
struct UFO {
    u8    pad00[0x70];
    void* mToolList;                        // +0x70
    void* GetToolListPtr();                 // 0x0108db30 (returns this + 0x70)
};
struct IFace {                              // object whose Release() sits at +4
    virtual void v00();
    virtual void Release4();                // +0x04
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();                     // +0x20  reset/clear hook
    virtual void v24();
    virtual void v28();
    virtual void v2c();
    virtual void v30();
    virtual void v34(void* p);              // +0x34  set current element
    virtual void v38();
    virtual void v3c();
    virtual void v40();
    virtual bool v44();                     // +0x44
    virtual void v48();
    virtual void v4c();
    virtual void v50(u32 id);               // +0x50
    virtual void v54();
    virtual void v58();
    virtual int  v5c();                     // +0x5c  count
    virtual void* v60(u32 i);               // +0x60  element
    virtual int  v64(u32 a, void* b);       // +0x64
};
struct IRelease8 {                          // object whose Release() sits at +8
    virtual void v00();
    virtual void v04();
    virtual void Release8();                // +0x08
};
struct IElement {                           // element with a +0xc(unsigned) slot
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c(u32 flag);             // +0x0c
};
struct Uid { u32 m0; u32 m1; u32 m2; };
struct cSPUIGlobalUI_s0106_ea40 {
    void* FindWindowByID(u32 id);           // 0x00e012b0
};
struct cSPUILayout_s0106_ea40 {
    void* FindWindowByID(u32 id, u32 flag); // 0x008105b0
};
struct LayoutSet {
    u8             m00[0x18];
    cSPUILayout_s0106_ea40**  mpBegin;                 // +0x18
    cSPUILayout_s0106_ea40**  mpEnd;                   // +0x1c
    u8             m20[0x58];
    int            Count();                 // 0x00e09c80
    cSPUILayout_s0106_ea40*   At(int i);               // 0x00e09c90
};
struct cWindow {
    void FUN_00e30ae0(u32 id);                              // 0x00e30ae0
    void FUN_00e31030(u32 a, u32 b, u32 c, u32 d);          // 0x00e31030
};
struct cUIWindow {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void* QueryIn(const Uid& uid, u32 a, u32 b, u32 c, u32 d);  // +0x0c
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
    virtual void SetId(u32 id);                                          // +0x50
};
struct cTextZoomName {
    virtual void v00();
    virtual void AddRef();                  // +0x04
    virtual void Release();                 // +0x08
    virtual void* Query(const Uid& uid, u32 a, u32 b, u32 c, u32 d);   // +0x0c
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
    virtual void v50(u32 id);               // +0x50

    void Shutdown();                        // 0x00834e30
    void SetTargetWindow(void* w);          // 0x00834fa0
    cTextZoomName* Construct();             // 0x008345c0
};
struct Node_s0106_ea40 {
    Node_s0106_ea40* mpNext;       // +0x00
    Node_s0106_ea40* mpPrev;       // +0x04
    u32   mValue;       // +0x08
};
struct ToolList {
    Node_s0106_ea40* mpHead;       // +0x00  (sentinel next, points at itself when empty)
    Node_s0106_ea40* mpTail;       // +0x04  (sentinel prev)

    ToolList() { Node_s0106_ea40* s = (Node_s0106_ea40*)this; s->mpNext = s; s->mpPrev = s; }
    void assign(const ToolList& self, Node_s0106_ea40* first, Node_s0106_ea40* last, u32 flags);  // 0x0106b950
    void pushBack(const u32& v);                                           // 0x00c58360
    void destroy();                                                        // 0x00700f90
};
struct HashNode;
struct HashIter {
    HashNode*  mpNode;      // +0x00
    HashNode** mpBucket;    // +0x04
};
struct HashTable {
    u32         m00;            // +0x00
    HashNode**  mpBuckets;      // +0x04
    u32         mnBuckets;      // +0x08
    u32         mnElements;     // +0x0c

    void find(HashIter* out, const u32& key);       // 0x00645ed0
    void begin(HashIter* out);                      // 0x00594410
    u32* insertEntry(const u32& key);               // 0x00b474c0
    HashIter erase(HashIter pos);                   // 0x01068380
    void freeNodes(HashNode** buckets, u32 n);      // 0x00961d60
    void freeBuckets(HashNode** buckets, u32 n);    // 0x00693230
};
struct HashNode {
    u32        mKey;        // +0x00
    u32        mValue;      // +0x04
    HashNode*  mpNext;      // +0x08
};
struct Blk28_s0106_ea40 {
    RefObj* mpRef;      // +0x00
    u32     m04;        // +0x04
    ObjRel* m08;        // +0x08
    u32     m0c;
    u32     m10;
    u32     m14;
    u32     m18;
    u8      m1c;
    u8      mPad[3];
    u32     m20;
    u32     m24;

    Blk28_s0106_ea40* CopyCtor(const Blk28_s0106_ea40& src);      // 0x01068450
};
Blk28_s0106_ea40*  Blk28_copy_b(Blk28_s0106_ea40* begin, Blk28_s0106_ea40* end, Blk28_s0106_ea40* dst);             // 0x01068610
void    Blk28_reloc_b(Blk28_s0106_ea40* begin, Blk28_s0106_ea40* end, Blk28_s0106_ea40* dst);            // 0x01068690
void    Blk28_fill3(Blk28_s0106_ea40* dst, u32 count, const Blk28_s0106_ea40* src);           // 0x01068530 (3 args)
void    Blk28_fill4(Blk28_s0106_ea40* dst, u32 count, const Blk28_s0106_ea40* src, Blk28_s0106_ea40* x);  // 0x01068530 (4 args)
Blk28_s0106_ea40** Blk28_ccopy(Blk28_s0106_ea40** out, Blk28_s0106_ea40* begin, Blk28_s0106_ea40* end, Blk28_s0106_ea40* dst);  // 0x010684b0
Blk28_s0106_ea40*  Blk28_mback(Blk28_s0106_ea40* begin, Blk28_s0106_ea40* end, Blk28_s0106_ea40* dst);              // 0x01068710
void    Blk28_assignr(Blk28_s0106_ea40* begin, Blk28_s0106_ea40* end, const Blk28_s0106_ea40* src);      // 0x0106cc40
Blk28_s0106_ea40*  Blk28_mvassign(Blk28_s0106_ea40* a, Blk28_s0106_ea40* b, Blk28_s0106_ea40* c);                   // 0x010686d0
struct Blk28Vec {
    Blk28_s0106_ea40* mpBegin;
    Blk28_s0106_ea40* mpEnd;
    Blk28_s0106_ea40* mpCap;

    Blk28_s0106_ea40* erase(Blk28_s0106_ea40* first, Blk28_s0106_ea40* last);                 // 0x0106eb40
    Blk28_s0106_ea40* insert(Blk28_s0106_ea40* pos, u32 n, const Blk28_s0106_ea40& value);    // 0x0106ebb0
};
inline void* MoveRange(void* dst, const void* first, const void* last) {
    return mem_copy(dst, first, (unsigned)((const char*)last - (const char*)first));
}
struct U32Vec3 {
    u32* mpBegin;
    u32* mpEnd;
    u32* mpCap;

    void clear() {
        u32* p = mpEnd;
        MoveRange(mpBegin, p, p);
        mpEnd -= (mpEnd - mpBegin);
    }
    void DoInsertValueI(u32* pos, const u32& value);        // 0x004558a0
};
struct U32Vec2 {
    u32* mpBegin;
    u32* mpEnd;
};
struct PtrVec {
    void** mpBegin;
    void** mpEnd;
    void** mpCap;

    void** eraseA(void** first, void** last);      // 0x00533500
    void** eraseB(void** first, void** last);      // 0x005c2170
    void** insertEntry(void** pos, void** value);  // 0x00f14270
};
struct Sub0c {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void* v0c(u32 key);   // +0x0c
    u32 m10;                      // +0x10
};
struct SpItemVtbl {
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
    virtual bool v44();           // +0x44
};
struct SpItem : SpItemVtbl {
    u8     mPad04[8];             // +0x04 .. +0x0b
    Sub0c  mSub;                  // +0x0c
    u32    mFlag;                 // +0x14
};
struct B8F860 { int  Get(); };      // 0x00b8f860
struct AC0C50 { bool Test(); };     // 0x00ac0c50
class cSPUISpace_s0106_ea40 {
public:
    u8              m000[0x224];                 // +0x000
    cSPUIGlobalUI_s0106_ea40*  mpGlobalUI;                  // +0x224
    u8              m228[0x10];                  // +0x228
    IFace*          mpToolList;                  // +0x238
    u32             m23c;                        // +0x23c
    U32Vec3         mIds;                        // +0x240
    u8              m24c[0x8];                   // +0x24c
    IRelease8*      mp254;                       // +0x254
    u8              m258[0x4];                   // +0x258
    HashTable       mToolTable;                  // +0x25c
    u8              m26c[0x10];                  // +0x26c
    U32Vec3         mSortedIds;                  // +0x27c
    u8              m288[0xc];                   // +0x288
    IFace*          mp294;                       // +0x294
    IFace*          mp298;                       // +0x298
    IFace*          mp29c;                       // +0x29c
    u8              m2a0[0x20];                  // +0x2a0
    U32Vec3         mIds2c0;                     // +0x2c0
    u8              m2cc[0x8];                   // +0x2cc
    HashTable       mStrategyTable;              // +0x2d4
    u8              m2e4[0x10];                  // +0x2e4
    u32             m2f4;                        // +0x2f4
    u8              m2f8[0x10];                  // +0x2f8
    PtrVec          mVec308;                     // +0x308
    u8              m314[0x2c1];                 // +0x314
    u8              m5d5;                        // +0x5d5
    u8              m5d6[0x2];                   // +0x5d6
    U32Vec2         mIdArray;                    // +0x5d8
    u8              m5e0[0x3c];                  // +0x5e0
    cWindow*        mpWindow61c;                 // +0x61c
    LayoutSet       mLayoutSet;                  // +0x620
    PtrVec          mZoomVec;                    // +0x698

    void        FUN_0106ea40(u32 index);                  // 0x0106ea40
    u32         FUN_0106edc0(u32 key);                    // 0x0106edc0
    void        FUN_0106ef30();                           // 0x0106ef30
    void        FUN_0106f120(u32 id);                     // 0x0106f120
    void        FUN_0106f160(u32 id);                     // 0x0106f160
    void        FUN_0106f1a0(int param_2, char param_3);  // 0x0106f1a0
    void        FUN_0106f380();                           // 0x0106f380
    void        FUN_0106f3d0();                           // 0x0106f3d0
    void        FUN_0106f540();                           // 0x0106f540
    void        FUN_0106dd10(u32 index, u32 value);       // 0x0106dd10
    void        FUN_0106e680(u32 id);                     // 0x0106e680
    void        ToggleToolUI(u32 id);                     // 0x0106e3e0
};
// ---- items of slice s0106ea40 end

// ---- items of slice s010743a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint8_t gAudioDebugA;   // 0x016e06ec
extern uint8_t gAudioDebugB;   // 0x016e06ed
extern float   gNextSoundTime; // 0x016e2230
extern const float kSoundPeriod; // 0x0149c174 (0.77f)
extern const float kNegOne;      // 0x013eb1bc (-1.0f)
extern char gSoundPtrA[];        // 0x015b9274
extern char gSoundPtrB[];        // 0x015b9278
typedef unsigned int uint;
struct Key3 { uint a, b, c; };
struct IWindow_s0107_43a0 {
virtual void s00();
virtual void s04();
virtual void s08();
    virtual IWindow_s0107_43a0* QueryInterface(uint id);                      // 0x0c
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
    virtual uint GetState();                                       // 0x20
virtual void s24();
virtual void s28();
virtual void s2c();
virtual void s30();
virtual void s34();
virtual void s38();
virtual void s3c();
virtual void s40();
virtual void s44();
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
virtual void s74();
virtual void s78();
    virtual void SetVisible(int a, bool b);                        // 0x7c
};
struct GlobalUI {
    IWindow_s0107_43a0* FindWindowByID(uint id);                              // 0x00e012b0 (ret 4)
};
struct CommMgr { bool IsActive(); };                              // 0x00ae9390
struct InputMgr {                                                 // singleton 0x00b3d3f0
    bool Query(int a);                                            // 0x00e18c70 (ret 4)
    void Set(int a, int b);                                       // 0x00e18dd0 (ret 8)
};
struct WinMgr {                                                   // singleton 0x0067caa0
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
virtual void s44();
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
virtual void s74();
virtual void s78();
virtual void s7c();
    virtual void s80();
    virtual int GetCapture();                                     // 0x84
};
struct ModeInfo { char pad[0x2c]; int mMode; };
static __forceinline bool ModeIs12(ModeInfo* m) { return m->mMode == 1 || m->mMode == 2; }                   // singleton 0x00b3d4d0
struct SimSlot { virtual void s00(); virtual void s04(); virtual void s08(); virtual void Enable(int a); };  // 0x0c
struct SimSettings {                                              // singleton 0x00b3d470
    char pad[0x30]; SimSlot* mSlot30; SimSlot* mSlot34; int mField38;
};
struct StarSource {                                               // singleton 0x00b3d240
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
    virtual IWindow_s0107_43a0* GetStarRecord();                             // 0x34
};
struct Planet {
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
virtual void s44();
virtual void s48();
virtual void s4c();
virtual void s50();
virtual void s54();
    virtual bool IsSomething();                                   // 0x58
    char pad[0x13c - 4]; struct PlanetMode* mpMode;               // +0x13c
    struct Hlp00c71* GetHelper();                                 // 0x00c71e30
};
struct PlanetMode {
    int GetKind();                                                 // 0x00b8dab0
};
struct Star {                                                     // star record
virtual void s00();
virtual void s04();
virtual void s08();
    virtual void* QueryInterface(uint id);                        // 0x0c
};
struct UFO_s0107_43a0 {                                                      // cSPSimulatorPlayerUFO
    char pad[0x14]; uint8_t mFlag[4];                             // +0x14..+0x17
    Star* GetStarRecordUnderMouse();                              // 0x00fff8e0
};
struct TerrainSphere {
    bool Check(uint id);                                           // 0x00c772c0 (ret 4)
};
struct TerrainEditor {
    TerrainSphere* GetCurrentTerrainSphere();                      // 0x00f67d90
};
struct MissionMgr_s0107_43a0 { void DebugDraw(); };                          // 0x00fee8d0
struct TimeMgr { void IncPauseGate(uint id); };                   // 0x00b32220 (ret 4)
struct Animator {
    void UpdateAnim();                                             // 0x007f63b0
};
struct Obj5a8 {
    void UpdateObj();                                              // 0x00e36540
};
struct Obj61c {
    void UpdateTimer(uint a);                                      // 0x00e30990 (ret 4)
};
struct UISoundHelper { bool GetFlag(); };                         // 0x00a98020 (singleton 0x01015df0)
struct UIObj1046 { void Run(); };                                 // 0x01048f00
struct SoundMgr {                                                 // singleton 0x0067caf0
    void Play(Key3 key, const void* p, int a, float f0, float f1, float f2, void* cb, int b);  // 0x0067aaf0 (ret 0x28)
};
struct Hlp00c71 { char pad[0x84]; int mField84; };
int      __cdecl SpaceGameGet();         // 0x01002bd0 (value unused)
int      __cdecl GetUniverseContext();   // 0x01021080
Planet*  __cdecl GetActivePlanet_s0107_43a0();      // 0x01021260
CommMgr* __cdecl CommManager();          // 0x00b3d4a0
InputMgr* __cdecl GetInputMgr();         // 0x00b3d3f0
SimSettings* __cdecl GetSimSettings();   // 0x00b3d470
StarSource* __cdecl GetStarSource();     // 0x00b3d240
ModeInfo* __cdecl GetModeInfo();         // 0x00b3d4d0
WinMgr* __cdecl WindowManager();         // 0x0067caa0
UFO_s0107_43a0* __cdecl GetUFOSimulator();          // 0x00ffbe50
MissionMgr_s0107_43a0* __cdecl GetMissionManager(); // 0x00feb9f0
TimeMgr* __cdecl GameTimeManager();      // 0x00b3d380
void* __cdecl NounManager();             // 0x00b3d300
SoundMgr* __cdecl GetSoundMgr();         // 0x0067caf0
UISoundHelper* __cdecl GetUISoundHelper();   // 0x01015df0
UIObj1046* __cdecl GetUIObj1046();       // 0x01046fc0
float    __cdecl GetElapsedSeconds();    // 0x00805080
void     __cdecl AudioGuiUpdate();       // 0x00c2e4e0 (empty in retail)
void     __cdecl operator_delete_arr(void* p);   // 0x00f47380
void SoundCb();                  // 0x010701e0
namespace SP {
class cSPUISpace_s0107_43a0 { public:
    char pad000[0x224];
    GlobalUI* mpGlobalUI;                // +0x224
    char pad228[0x568 - 0x228];
    Animator* mpAnimator;                // +0x568
    char pad56c[0x5a8 - 0x56c];
    Obj5a8* mp5a8;                       // +0x5a8
    char pad5ac[0x5d3 - 0x5ac];
    uint8_t mFlag5d3;                    // +0x5d3
    uint8_t mFlag5d4;                    // +0x5d4
    char pad5d5[0x5f4 - 0x5d5];
    // deque<uint32_t> of queued sound ids: start iterator then finish iterator (64 entries per node)
    uint* mStartCur;                     // +0x5f4
    uint* mStartFirst;                   // +0x5f8
    uint* mStartLast;                    // +0x5fc
    uint** mStartNode;                   // +0x600
    uint* mFinishCur;                    // +0x604
    uint* mFinishFirst;                  // +0x608
    uint* mFinishLast;                   // +0x60c
    uint** mFinishNode;                  // +0x610
    char pad614[0x618 - 0x614];
    int mMode618;                        // +0x618
    Obj61c* mp61c;                       // +0x61c

    void Update(uint dt);  // 0x010743a0 (SP::cSPUISpace::Update)

    void UpdateGlobal();                 // 0x01065fe0
    void UpdateActiveToolCursor();       // 0x0106c930
    void UpdateTerraformingSlots();      // 0x01071d70
    void UpdateTerraformingBullseye();   // 0x01066f20
    void UpdateTravelLine(void* star);   // 0x0106cc70 (ret 4)
    void UpdatePlanetRollover(void* p);  // 0x0106ba00 (ret 4)
    void FUN_010678e0();                     // 0x010678e0
    void FUN_010679f0();                     // 0x010679f0
    void FUN_0106a970();                     // 0x0106a970
    void FUN_0106cab0();                     // 0x0106cab0
    void FUN_01072680();                     // 0x01072680
    void FUN_01069aa0();                     // 0x01069aa0
    void FUN_010691e0();                  // 0x010691e0
    void FUN_0106b630();                     // 0x0106b630
    void FUN_01065d20();                     // 0x01065d20

    __forceinline uint PopSound()
    {
        uint v = *mStartCur;
        uint* next = mStartCur + 1;
        if (next == mStartLast) {
            if (mStartFirst)
                operator_delete_arr(mStartFirst);
            ++mStartNode;
            mStartFirst = *mStartNode;
            mStartLast = mStartFirst + 0x40;
            next = mStartFirst;
        }
        mStartCur = next;
        return v;
    }
};  // namespace SP
}
extern void __cdecl ApplyToWindow(int value, IWindow_s0107_43a0* w);   // 0x00e2e6e0
static __forceinline IWindow_s0107_43a0* ToggleButton(GlobalUI* ui, uint id)
{
    IWindow_s0107_43a0* w = ui->FindWindowByID(id);
    return w ? w->QueryInterface(0x8ed27e7a) : 0;
}
static __forceinline void CopyToggle(GlobalUI* ui, uint id, int i)
{
    IWindow_s0107_43a0* q = ToggleButton(ui, id);
    uint st = q->GetState();
    GetUFOSimulator()->mFlag[i] = (uint8_t)((st >> 1) & 1);
}
static __forceinline void OrToggle(GlobalUI* ui, uint id, int i)
{
    IWindow_s0107_43a0* q = ToggleButton(ui, id);
    UFO_s0107_43a0* ufo = GetUFOSimulator();
    ufo->mFlag[i] |= (uint8_t)((q->GetState() >> 1) & 1);
}
// ---- items of slice s010743a0 end

// ---- items of slice s01077470 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int DAT_0149c608[3] = {0, 0, 0}; // 0x0149c608  user message list
struct Obj;
#define VTSLOT(obj, off) ((*(void***)(obj))[(off) / 4])
typedef void  (__thiscall *Fn_v_p)(void*);
typedef void  (__thiscall *Fn_v_pii)(void*, int, int);
typedef void  (__thiscall *Fn_v_pp)(void*, void*);
typedef void  (__thiscall *Fn_v_ppi)(void*, void*, int);
typedef void  (__thiscall *Fn_v_pf)(void*, float);
typedef Obj*  (__thiscall *Fn_p_p)(void*);
typedef Obj*  (__thiscall *Fn_p_pi)(void*, int);
typedef Obj*  (__thiscall *Fn_p_pp)(void*, void*);
typedef Obj*  (__thiscall *Fn_p_ppp)(void*, void*, void*);
typedef bool  (__thiscall *Fn_b_p)(void*);
typedef bool  (__thiscall *Fn_b_pp)(void*, void*);
extern "C" u32 DAT_015b9558 = 0;    // 0x015b9558  tooltip style id
struct cScrollElem {
    void* mpObj;         // +0x00
    float mField4;       // +0x04
    u8    mByte8;        // +0x08
    u8    mPad9[3];
};
struct cObjVec {
    Obj** begin;         // +0x00
    Obj** end;           // +0x04
};
struct cSPUILayout_s0107_7470 {
    cObjVec* GetObjects();                  // 0x008100c0
    Obj*     FindWindowByID(int id, int flag); // 0x008105b0
};
struct cUITimedTooltip {
    u8   mPad00[0x30];
    char Init(u32 a1, u32 a2, u32 a3, u32 a4, int a5, int a6); // 0x00e36b30
    Obj* FindWindow(int id, bool flag);                          // 0x00e36650
};
struct cPlayerInventory_s0107_7470 {
    void* FUN_00ff3f00();        // 0x00ff3f00  currently shown item
    void  FUN_00ff4540(void* p); // 0x00ff4540
    void  FUN_00ff4470(void* p); // 0x00ff4470
};
struct cSPSimulatorSpaceGame_s0107_7470 {
    cPlayerInventory_s0107_7470* GetPlayerInventory();  // 0x00a1ad60
};
struct cSporeItem {
    void* FUN_0106edc0();           // 0x0106edc0
};
Obj*  __cdecl SP_MessageServer();                                      // 0x0067dcc0
void  __cdecl EA_Messaging_RemoveHandler(void*, void*, void*, void*, void*); // 0x00571db0
void  __cdecl EA_Locale_SetNumberString(int value, int a, char* buf, int len); // 0x00881ae0
namespace SP {
struct cSPUISpaceTrading {
    u8    mPad00[0x0c];
    void* mpField0C;             // +0x00c  message-handler target (&mField0C)
    void* mpField10;             // +0x010  NPC scroll container
    void* mpScroll14;            // +0x014  NPC scroll frame (FUN_01077470)
    void* mpOwner18;             // +0x018  NPC scroll frame owner slot
    void* mpField1C;             // +0x01c  user scroll container
    void* mpField20;             // +0x020  user scroll frame (FUN_01077550)
    void* mpField24;             // +0x024  user scroll frame owner slot
    void* mpField28;             // +0x028
    void* mpField2C;             // +0x02c  window collection
    cScrollElem* mpVec30;        // +0x030  cell vector begin
    cScrollElem* mpVecEnd34;     // +0x034  cell vector end
    u8    mPad38[0x50 - 0x38];
    cUITimedTooltip mTooltip;    // +0x050
    u32   mField80;              // +0x080  layout tag (0x120ad1fb)
    u32   mPad84;
    int   mField88;              // +0x088  divisor
    int   mField8C;              // +0x08c  divisor
    u32   mPad90;
    float mField94;              // +0x094  cell pitch x
    float mField98;              // +0x098  cell pitch y
    u8    mByte9C;               // +0x09c  "use window index" flag
    u8    mPad9D[0xac - 0x9d];
    float mFieldAC;              // +0x0ac  tooltip row height (empty)
    float mFieldB0;              // +0x0b0  tooltip row height
    float mFieldB4;              // +0x0b4  cell width
    float mFieldB8;              // +0x0b8  cell height
    float mFieldBC;              // +0x0bc
    float mFieldC0;              // +0x0c0
    u8    mPadC4[0xe0 - 0xc4];
    float mFieldE0;              // +0x0e0  scroll extent (x)
    float mFieldE4;              // +0x0e4  scroll extent (y)
    u8    mByteE8;               // +0x0e8  NPC panel visible
    u8    mByteE9;               // +0x0e9  user panel visible
    u8    mPadEA[2];
    void* mpHandlerEC;           // +0x0ec  registered message handler
    void* mArgsF0[4];            // +0x0f0  handler arguments
    union {
        struct { void* h; void* a1; void* a2; void* a3; void* a4; } mBlk100;
        struct { u32 p0; u32 p1; void* h; void* a1; void* a2; void* a3; void* a4; } mBlk108;
    };
    u8    mByte11C;              // +0x11c
    u8    mByte11D;              // +0x11d
    u16   mPad11E;
    int   mField120;             // +0x120
    u32   mPad124;
    void* mpHandler128;          // +0x128  registered message handler
    void* mArgs12C[4];           // +0x12c  handler arguments

    void  Init();                          // 0x01076180
    void  SetMidPanel();                   // 0x010755d0
    void  FUN_01076a00();                  // 0x01076a00
    void  FUN_01076a60();                  // 0x01076a60
    void* FUN_010666a0(void* p);           // 0x010666a0
    void* FUN_0106edc0(void* p);           // 0x0106edc0 (on FUN_010666a0 result)

    void  FUN_01077470();
    void  FUN_01077550();
    void  FUN_01077630();
    bool  FUN_01077830(void* p);
    int   FUN_01077860(float a, float b);
    u8    FUN_01077900(void* p);
    u32   FUN_01077960(void* p);
    void  FUN_01077990(void* p);
    void  FUN_010779e0();
    bool  FUN_01077b70(void* a1, u32* pOut);
    void  FUN_01077bf0(void* a1);
    void  FUN_01077ce0(void* a1);
    void  FUN_01077d30();
    void  FUN_01077e20();
};  // namespace SP
}
u32 __stdcall FUN_01077ae0(cSPUILayout_s0107_7470* layout);
u32 __cdecl FUN_01077b40(void* p);
// ---- items of slice s01077470 end

// ---- items of slice s0107a510 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void __cdecl FUN_0107a5b0_SideEffect();       // external state change
namespace SP {
class cToolWidget {
public:
    void FUN_0107a510();
    __declspec(noinline) void FUN_0107a5b0();
    void FUN_0107a6b0();
    void FUN_0107a9a0();
    void FUN_0107a300();                                 // 0x0107a300
    void FUN_0107ab20(int32_t value);
    void FUN_0107abb0();

    uint8_t  pad000[0x90];                               // +0x000 .. +0x08f
    int32_t  mField90;                                   // +0x090
    uint8_t  pad094[0xe8 - 0x94];                        // +0x094 .. +0x0e7
    bool     mFlagE8;                                    // +0x0e8
};
}
// ---- items of slice s0107a510 end

// ---- items of slice s00433800 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kZero;                       // 01485378
extern const float kOne;                        // 01485720
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct Matrix3 {
    float m[9];
    Matrix3() {}
    Matrix3(const Matrix3& o);          // 0041CB40
};
extern Vector3 g_DefaultPos;                    // 015D22F0
extern Matrix3 g_IdentityMatrix;                // 015D2638
template <int N> inline void PadN() { uint32_t s[N]; }
struct XformMsg {
    uint16_t flags;
    uint16_t count;
    Vector3  pos;
    float    scale;
    Matrix3  rot;
    XformMsg();
    XformMsg(void* src);                          // 0040CE80
    void SetPos(const Vector3& v)   { pos = v; flags |= 4; ++count; }
    void SetScale(float s)          { scale = s; ++count; }
    void SetRot(const Matrix3& m)   { rot = m; flags |= 2; ++count; }
};
struct Handle {
    virtual void AddRef();
    virtual void Release();
    virtual void v2();
    virtual void Stop(int);
    virtual bool IsPlaying();
    virtual void v5();
    virtual void SetXform(XformMsg*);
};
struct Mixer {
    virtual void p0();
    virtual void p1();
    virtual void p2();
    virtual void p3();
    virtual void p4();
    virtual void p5();
    virtual void p6();
    virtual void p7();
    virtual void p8();
    virtual void p9();
    virtual void p10();
    virtual void p11();
    virtual void p12();
    virtual void p13();
    virtual void p14();
    virtual void p15();
    virtual void p16();
    virtual void p17();
    virtual void p18();
    virtual void p19();
    virtual void p20();
    virtual void p21();
    virtual void p22();
    virtual void p23();
    virtual void p24();
    virtual void p25();
    virtual void p26();
    virtual void p27();
    virtual void p28();
    virtual void SetValue(uint32_t key, uint32_t id, float v, int flag);   // slot 0x74
    virtual void SetFade(uint32_t key, uint32_t id, float v, int flag);    // slot 0x78
};
struct Owner {
    uint32_t pad0[4];
    uint32_t key;      // +0x10
    uint32_t pad1;
    Mixer*   mixer;    // +0x18
    void* GetSource();       // 0043D220
    void  Refresh();         // 0043D420
};
struct EffectDef;
struct Factory { Handle* Create(); };                                  // 0045AC20
Factory* __stdcall GetFactory(EffectDef*, int, XformMsg*, void*);      // 00401050
struct HandlePtr {
    Handle* p;
    HandlePtr() : p(0) {}
    Handle* get() const { return p; }
    Handle* operator->() const { return p; }
    void reset(Handle* n) {
        if (p) {
            Handle* old = p;
            if (n) n->AddRef();
            p = n;
            if (old) old->Release();
        }
    }
    void assign(Handle* n) {
        if (n != p) {
            Handle* old = p;
            if (n) n->AddRef();
            p = n;
            if (old) old->Release();
        }
    }
};
struct FadeController {
    uint32_t   id;          // +0x00
    float      duration;    // +0x04
    float      time;        // +0x08
    float      fadeTime;    // +0x0C
    uint8_t    flag10;      // +0x10
    uint8_t    playing;     // +0x11
    uint16_t   pad12;
    EffectDef* effect;      // +0x14
    uint32_t   pad18[3];
    uint32_t   loopMode;    // +0x24
    uint8_t    flag28;      // +0x28
    uint8_t    fadingOut;   // +0x29
    uint16_t   pad2a;
    Owner*     owner;       // +0x2C
    HandlePtr  handle;      // +0x30

    FadeController();
    void SetOwner(Owner* o);
    void ReleaseHandle();
    void Update(float dt);
    uint8_t IsActive();
    uint8_t IsPlaying();
    void Stop();
    void FinishFade();     // 004341C0
};
// ---- items of slice s00433800 end

// ---- items of slice s00b181d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl sqrt(double);
extern "C" unsigned __int64 __rdtsc();
extern char gTraitKey[];  // 0x013f94d4
#pragma intrinsic(sqrt)
#pragma intrinsic(__rdtsc)
struct IPawn {
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
  virtual void v14();
  virtual void v15();
  virtual void v16();
  virtual void v17();
  virtual void v18();
  virtual void v19();
  virtual bool IsA();
  virtual void v21();
  virtual bool IsB();
};
struct IObj {
  virtual int AddRef();
  virtual int Release();
  virtual void v2();
  virtual IPawn* Query(unsigned id);
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
  virtual int GetKind();
};
struct IServer {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void Post5(unsigned id, int a, int b);
  virtual void Post6(unsigned id, int a, int b, int c);
  virtual void v7();
  virtual void v8();
  virtual void Reg9(void* p, unsigned id);
  virtual void v10();
  virtual void Reg11(void* p, unsigned id, unsigned x);
};
struct IWinMgr {
  virtual void v0();
  virtual void* Get4();
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
  virtual int Get84();
};
IServer* __cdecl MessageServer();     // 0x0067dcc0
namespace SP {
struct cDefTable {
  unsigned Lookup(unsigned id);  // 0x00f3e8a0 (ret 4)
};
}
namespace SP {
class cApp { public:
  char pad[0x74];
  cDefTable* mpDefs;
};
}
namespace SP {
extern cApp* gApp;             // 0x016c7aa4
}
struct cTraitHolder {
  float Value();  // 0x00bfc490
};
struct cLayoutMgr {
  bool IsWorldVisible(unsigned id);  // 0x00810760 (ret 4)
};
cLayoutMgr* __cdecl GetLayoutManager();  // 0x00805070
struct cB3d320 {
  char pad[0x28];
  u8 mFlag28;
};
cB3d320* __cdecl GetB3d320();  // 0x00b3d320
unsigned __cdecl GetCurrentGameMode();  // 0x00b5b800
struct cCreatureModeStrategy {
  bool F();  // 0x00d38880
  static cCreatureModeStrategy* Instance();  // 0x00d38840
};
struct cTribeModeStrategy {
  bool F();    // 0x00cd4490
  bool G();    // 0x00cd44a0
  static cTribeModeStrategy* Instance();  // 0x00cd40b0
};
struct cCivModeStrategy {
  bool F();    // 0x00cf7a40
  char pad[0x148];
  u8 mFlag148;
  static cCivModeStrategy* Get();  // 0x00cf74c0
};
struct cB3d410 {
  bool F();  // 0x00e36fa0
  bool G();  // 0x00e393b0
};
cB3d410* __cdecl GetB3d410();  // 0x00b3d410
struct cB3d4d0 {
  bool F();  // 0x00ac80f0
  void H();  // 0x00ad8f90
  char pad[0x2b];
  u8 mFlag2b;
  int m2c;
};
cB3d4d0* __cdecl GetB3d4d0();  // 0x00b3d4d0
struct cAppG {
  bool G();  // 0x00ef00d0
};
bool __cdecl FUN_00dd1230();
bool __cdecl FUN_00e09540();
bool __cdecl FUN_00b2f740();
struct cFlagObj {
  char pad[0x1c];
  u8 mFlag;
};
cFlagObj* __cdecl SporeGuide();     // 0x00401040
cFlagObj* __cdecl AssetBrowser();   // 0x00401030
IWinMgr* __cdecl WindowManager_s00b1_81d0();   // 0x0067caa0
struct cWinObj {
  bool Test();               // 0x00812d70
  void Set(bool b);          // 0x00812d60 (ret 4)
};
struct cC10666a0 {
  bool F();  // 0x01065e20
};
cC10666a0* __cdecl GetC10666a0();  // 0x010666a0
// ---- items of slice s00b181d0 end

// ---- items of slice s00bbca30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl FUN_010212a0();                       // SP::cSPLivingUniverse::GetActivePlanetRecord
extern "C" void* __cdecl FUN_00401090();                       // SP::cSPEditorSpeciesManager singleton
extern "C" bool  __cdecl EA_ResKeyNeq(void*, void*);           // EA::ResourceMan::operator!=
extern "C" int   __cdecl FUN_00fc2080(float, float);            // 0xfc2080  TerraDistClass
extern "C" void* __cdecl FUN_01021080();                        // GetUniverseContext
extern "C" int   __cdecl FUN_01021090();                        // GetPlayerEmpireID
extern "C" void* __cdecl FUN_01002bd0(int);                     // SpaceGameGet
extern "C" void* __cdecl FUN_0067dcc0();                        // MessageServer
extern "C" void* __cdecl FUN_00b3d470();                        // GetTerraformingManager-ish
extern "C" void* __cdecl FUN_00b3d350();                       // SP::PlanetModel
#define VF(p, off) (*(void**)((char*)(*(void**)(p)) + (off)))
extern uint32_t DAT_0168a488, DAT_0168a48c, DAT_0168a490;
struct Key12_bbca30 { int a, b, c; };   // a resource key (instance, type, group)

class TObj {
public:
    // ---- reused __thiscall callees (addresses in comments) -------------------
    void* F_4df550(void*);              // 0x4df550  GetProfile(const Key&)
    void* F_c745d0(int, void*);         // 0xc745d0
    void* F_8414c0();                   // 0x8414c0
    void  F_c80680(int, void*);         // 0xc80680
    void  F_f921d0(int, int);           // 0xf921d0
    void  F_b2a750();                   // 0xb2a750
    void  F_bbc870(void* out, int a, void* b, int c);   // 0xbbc870
    void  F_bbc540(void* out, void* p);                 // 0xbbc540  UpdateCargoSlots
    void  F_bbc950(void* out, int a, int b, int c);     // 0xbbc950
    void  F_c70a00(float);                              // 0xc70a00
    void  F_c70a50(float);                              // 0xc70a50
    float F_c71d30();                                   // 0xc71d30
    void  F_c71da0(float);                              // 0xc71da0
    char  F_c70a70();                                   // 0xc70a70
    void  F_c70aa0(float);                              // 0xc70aa0
    void* F_c71e30();                                   // 0xc71e30
    void  F_c70de0(int);                                // 0xc70de0
    float F_fbda80();                                   // 0xfbda80
    void  F_fbddb0(float, float, void*);                // 0xfbddb0
    int   F_bbc670(int);                                // 0xbbc670
    char  F_c308b0();                                   // 0xc308b0
    void  F_ffaa90();                                   // 0xffaa90
    void  F_dd8640(int, int, int, int, int, int);       // 0xdd8640
    void* F_b1fdb0();                                   // 0xb1fdb0
    void  F_01034880();                                 // 0x1034880

    // ---- slice targets -------------------------------------------------------
    int*  FUN_00bbca30(int* out, int index, int planet);   // 0xbbca30 (as the callers here spell it)
    Key12_bbca30 FUN_00bbca30(int index, int planet);     // 0xbbca30 (the key is returned by value)
    void  FUN_00bbcb10(void* key, void* planet);           // 0xbbcb10
    char  FUN_00bbcb90(int param_1, int param_2);          // 0xbbcb90
    void  FUN_00bbcf00(void* planet, float f2, float f3, int param_4);  // 0xbbcf00
    void  FUN_00bbd0a0(int delta);                         // 0xbbd0a0
    int*  FUN_00bbd0e0(int* node, int param_3, int** param_4);  // 0xbbd0e0
};
bool __stdcall FUN_00bbcda0(int param_1, int param_2);     // 0xbbcda0
bool __stdcall FUN_00bbce00(int param_1, int param_2);     // 0xbbce00
// ---- items of slice s00bbca30 end

// ---- items of slice s01065c30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" float sqrtf_s0106_5c30(float);  // the CRT sqrtf; math.h declares sqrtf inline, which compiles differently
extern "C" double atan2(double, double);
extern float g_180;                  // 0x013eb17c
extern float g_15b90e0;              // 0x015b90e0
extern float g_149c1fc;              // 0x0149c1fc (20.0)
extern float g_16e2838;              // 0x016e2838
extern int   g_16e283c;              // 0x016e283c
extern float g_15b9420, g_15b9424, g_15b9428;
struct Win {
virtual void w0();
virtual void w1();
virtual void w2();
virtual void w3();
virtual void w4();
virtual void w5();
virtual void w6();
virtual void w7();
virtual void w8();
virtual void w9();
virtual void w10();
virtual void w11();
virtual void w12();
virtual void w13();
virtual void w14();
virtual void w15();
virtual void w16();
virtual void w17();
virtual void w18();
virtual void w19();
virtual void w20();
virtual void w21();
virtual void w22();
virtual void w23();
virtual void w24();
virtual void w25();
virtual void w26();
virtual void w27();
virtual void w28();
virtual void w29();
    virtual int v78(uint id);                // +0x78
    virtual int SetShown(int a, int b);      // +0x7c
    virtual void SetText(const char* s);     // +0x80
};
struct Win28 {
virtual void a0();
virtual void a1();
virtual void a2();
virtual void a3();
virtual void a4();
virtual void a5();
virtual void a6();
virtual void a7();
virtual void a8();
virtual void a9();
    virtual void call28(int a, int b);       // +0x28
};
struct IRefCounted {
    virtual void dtor();                     // +0x00
    virtual void AddRef();                   // +0x04
    virtual void Release();                  // +0x08
};
struct Winc {
virtual void w0();
virtual void w1();
virtual void w2();
    virtual void* v3(uint id);               // +0xc
    virtual void* v4();                      // +0x10
    virtual void v5(int);                    // +0x14
virtual void w6();
virtual void w7();
virtual void w8();
virtual void w9();
    virtual void v10();                      // +0x28
    virtual void w11();
    virtual void* v12();                     // +0x38
    virtual void* v13();                     // +0x3c
virtual void w14();
virtual void w15();
virtual void w16();
virtual void w17();
virtual void w18();
virtual void w19();
virtual void w20();
virtual void w21();
virtual void w22();
virtual void w23();
virtual void w24();
virtual void w25();
virtual void w26();
virtual void w27();
virtual void w28();
virtual void w29();
virtual void w30();
virtual void w31();
virtual void w32();
virtual void w33();
virtual void w34();
virtual void w35();
virtual void w36();
virtual void w37();
virtual void w38();
virtual void w39();
virtual void w40();
virtual void w41();
virtual void w42();
virtual void w43();
virtual void w44();
virtual void w45();
virtual void w46();
virtual void w47();
virtual void w48();
virtual void w49();
virtual void w50();
virtual void w51();
virtual void w52();
virtual void w53();
virtual void w54();
virtual void w55();
virtual void w56();
virtual void w57();
virtual void w58();
virtual void w59();
virtual void w60();
virtual void w61();
virtual void w62();
virtual void w63();
virtual void w64();
virtual void w65();
virtual void w66();
virtual void w67();
virtual void w68();
virtual void w69();
virtual void w70();
virtual void w71();
virtual void w72();
virtual void w73();
virtual void w74();
virtual void w75();
virtual void w76();
virtual void w77();
    virtual void* v78(uint id);              // +0x104  (approx index 65)
};
void* ConfigManager();                                   // 0x0067dd30
void* SpaceGameGet_s0106_5c30();                                    // 0x01002bd0
void* GetUFOSimulator_s0106_5c30();                                 // 0x00ffbe50
void* App();                                             // 0x0067dd10
void* __stdcall GameTimeManager(uint id);               // 0x00b3d380
struct SpGameTime {                                     // 0x4bf38a9 singleton
    void IncPauseGate();                                // 0x00b32220
    void DecPauseGate();                                // 0x00b32250
};
void* StarManager_s0106_5c30();                                     // 0x00b3d2a0
void* GetPlayerEmpire_s0106_5c30();                                 // 0x01021300
int   GetActivePlanet_s0106_5c30();                                 // 0x01021260
void* FUN_0067cac0(uint id);                             // 0x0067cac0
void* FUN_0067cac0();                                    // 0x0067cac0 (no-argument view)
void* FUN_01077b40_s0106_5c30(void* w);                             // 0x01077b40
void* operator_new(int size, const char* file, int line, int a, const char* file2, int line2);  // 0x00f473a0
void* FUN_00e50750(void* a, void* b, void* c);           // 0x00e50750
void* GetMainWindowArea(void* out);                      // 0x00805ea0
char __fastcall FUN_00c372c0(void* inv);                 // 0x00c372c0
char __fastcall FUN_00c37300(void* inv);                 // 0x00c37300
void  EA_SetNumberString(int lo, int hi, void* buf, int n);  // 0x00881ae0
void* FUN_01046fc0();                                    // 0x01046fc0
struct cPlanet_s0106_5c30 {
    int   GetKind();          // 0x00b8dab0
    void* Project();          // 0x00b8de30
    void* GetSpeciesKey();    // 0x00b8e090
    int   GetToolMode();      // 0x00c70e00
};
struct cSpaceGame_s0106_5c30 {
    void* GetAvatar();        // 0x00b1fdb0
};
struct StarMgr_s0106_5c30 {
    void* GetEmpireByID(uint id); // 0x00ba9370
};
struct cEmpire_s0106_5c30 {
    char IsScannable();       // 0x00c30910
};
struct SpeciesMgr_s0106_5c30 {
    void* GetProfile();       // 0x004df550
};
struct SimSpaceGame {
    void* GetPlayerInventory(); // 0x00a1ad60
};
struct cSpaceGameObj {
    char pad0[0x14];
    void* pSpace;               // +0x14
};
struct cPropView {
    bool Test(int i);         // 0x010449e0
};
struct Inv508 {
virtual void i0();
virtual void i1();
virtual void i2();
virtual void i3();
virtual void i4();
virtual void i5();
virtual void i6();
virtual void i7();
virtual void i8();
virtual void i9();
virtual void i10();
virtual void i11();
virtual void i12();
virtual void i13();
virtual void i14();
virtual void i15();
virtual void i16();
virtual void i17();
virtual void i18();
virtual void i19();
virtual void i20();
virtual void i21();
    virtual float Get();      // +0x58
};
void  SetWindowImage(void* win, void* data, int a);      // 0x00807bb0
char  CalloutMessageBox(void* self, void* key);          // 0x00809db0
void  SPUIHelpers_SetTooltipText(void* win, void* text); // 0x00806de0
struct LayoutWindow {
    void SetVisibility(int v);                           // @ 0x00810590
};
extern uint  g_ids149c178[6];        // 0x0149c178
struct SPUISpace {
    char pad0[0x224];
    Win* mGlobalUI;                 // +0x224
    void ShowCameraControls(int param);
    void ShowToolChargeBar();
    void HideToolChargeBar();
    void ToggleStarmapFilters(int param);
    void UpdateGlobal();
    void FUN_01066230(char param);
    void FUN_010666b0();
};
struct LayoutUI {
    Win* FindWindowByID(uint id, int flag);   // 0x008105b0
};
struct GlobalUI_s0106_5c30 {
    char pad0[8];
    LayoutUI* mLayout;                        // +0x08
    Win* FindWindowByID(uint id);             // 0x00e012b0
    void SetProgress(uint id, float v);       // 0x00e012d0
};
struct AppObj {
virtual void a0();
virtual void a1();
virtual void a2();
virtual void a3();
virtual void a4();
virtual void a5();
virtual void a6();
virtual void a7();
virtual void a8();
virtual void a9();
virtual void a10();
virtual void a11();
virtual void a12();
virtual void a13();
virtual void a14();
virtual void a15();
virtual void a16();
virtual void a17();
virtual void a18();
virtual void a19();
virtual void a20();
virtual void a21();
    virtual void* GetViewer();                // +0x58
};
struct cViewer {
    void GetCameraLocationInfo(void* a, void* b, float* cam, void* c); // 0x007c3d30
};
struct VtP {
virtual void p0();
virtual void p1();
virtual void p2();
virtual void p3();
    virtual void* v10();                 // +0x10
    virtual void v14(int v);             // +0x14
};
struct VtS {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
    virtual float* v38();                // +0x38
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
virtual void s22();
virtual void s23();
virtual void s24();
virtual void s25();
virtual void s26();
virtual void s27();
virtual void s28();
    virtual void v74(float a, float b);  // +0x74
};
struct TextZoomName {
    void Activate(uint v);                    // 0x00834a00
    void Deactivate(uint v);                  // 0x00834c60
};
struct T5d20 {
    char pad0[0x618];
    int mState;                     // +0x618
    void f();
    bool isStateSpecial();
    void reset();
};
struct ConfigMgr {
virtual void* v0();
virtual void* v1();
virtual void* v2();
virtual void* v3();
virtual void* v4();
virtual void* v5();
virtual void* v6();
virtual void* v7();
virtual void* v8();
virtual void* v9();
virtual void* v10();
virtual void* v11();
    virtual void* Lookup(uint id);   // +0x30
};
struct CfgMgr {
    void F_67c830(uint id);          // @ 0x0067c830  (ret 4)
    void Set(uint id, int on);       // @ 0x0067c8c0  (ret 8)
};
struct T6120 {
    char pad0[0x224];
    void* mGlobal;
    void* f(uint id);
};
struct CmdDeleteCargo {
    char pad0[8];
    void* pItem;        // +0x08
    int   field0c;      // +0x0c
    uint  windowID;     // +0x10
    void* pSpace;       // +0x14
    int   state;        // +0x18
    bool OnState1();
    bool OnState2();
    bool Run();
};
struct CmdCtor {
    void* mVtbl;                    // +0x00
    int m04;                        // +0x04, untouched by this initializer
    IRefCounted* mpItem08;           // +0x08
    uint mDialogResult0c;            // +0x0c, pending dialog/button result
    uint mWindowID10;                // +0x10
    SPUISpace* mpSpace14;            // +0x14
    int mState18;                    // +0x18
    CmdCtor* init(SPUISpace* space, uint windowID);
};
struct T6610 {
    char pad0[0xc];
    int mField;
    void set(int a, int b);
};
struct InputEvent {
    char pad0[8];
    int  key;       // +0x08
    int  flags;     // +0x0c
    char pad10[8];
    void* obj;      // +0x18
};
struct EvObj {
virtual void e0();
virtual void e1();
virtual void e2();
virtual void e3();
virtual void e4();
virtual void e5();
virtual void e6();
    virtual int GetId();                     // +0x1c
};
struct SpaceZoom {
    char pad0[0x258];
    void* mp258;                             // +0x258
    char pad25c[0x698 - 0x25c];
    void** mZoomBegin;                       // +0x698
    void** mZoomEnd;                         // +0x69c
    void** mZoomCap;                         // +0x6a0
    bool FUN_01066780(int unused, InputEvent* ev);
};
struct LayoutObj {
    bool Init(const wchar_t* name, int a, int b, int c); // 0x00812160
    void Shutdown(int a);                                // 0x00811ad0
    void SetVisibility(int v);                           // 0x00810590
};
struct LayoutAlloc {
    void* Ctor();                                        // 0x00810000
};
struct cString_s0106_5c30 {
    void* mData;             // +0x00
    int   mSize;             // +0x04
    void Ctor(uint id, int a, int b);                    // 0x006b5770
    void* GetText(int a, int b);                         // 0x006b55c0
    void Dtor();                                         // 0x006b5240
};
struct CmdObjBase {
virtual void b0();
virtual void b1();
virtual void b2();
    char pad4[4];            // +0x04 .. +0x07
    void BaseCtor();                                     // 0x008014a0
    void BaseDtor();                                     // 0x008014b0
};
struct CmdObj : CmdObjBase {
    void* m08;               // +0x08
    void* mLayout;           // +0x0c
    CmdObj* Ctor();
    void Dtor();
};
struct T6a10 {
    char pad0[0xc];
    void* mWin;
    void hide();
};
// ---- items of slice s01065c30 end

// ---- items of slice s010691e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma pack(push, 8)
#pragma pack(pop)
struct Vector3_s0106_91e0 { float x, y, z; Vector3_s0106_91e0() {} Vector3_s0106_91e0(float ax, float ay, float az) : x(ax), y(ay), z(az) {} };
namespace Math {
struct Rectangle {
    float x1, y1, x2, y2;
    Rectangle() {}
    Rectangle(float l, float t, float r, float b) : x1(l), y1(t), x2(r), y2(b) {}
    void Union(const Rectangle& a, const Rectangle& b);              // 0x00805530
};
}
struct Matrix3f {
    float m00, m01, m02;
    float m10, m11, m12;
    float m20, m21, m22;
};
struct EffectTransform {
    uint16_t mFlags;                            // +0x00
    uint16_t mnChangeCount;                     // +0x02
    Vector3_s0106_91e0  mOffset;                           // +0x04
    uint32_t pad10;                             // +0x10
    float    mfScale;                           // +0x14
    Matrix3f mMatrix;                           // +0x18
};
namespace EA {
template <class T> class AutoRefCount_s0106_91e0 {
public:
    T* mpObject;
    AutoRefCount_s0106_91e0() : mpObject(0) {}
    ~AutoRefCount_s0106_91e0() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
    T** AsPPTypeParam();                                             // 0x00A16F40 (shared instance)
    __forceinline void Clear()
    {
        if (mpObject != 0) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
    }
};
}
namespace EA {
namespace UTFWin {
class IWindow_s0106_91e0 {
public:
    virtual int AddRef();                                            // +0x0
    virtual int Release();                                           // +0x4
virtual void _v08();
virtual void _v0c();
    virtual IWindow_s0106_91e0* GetParent();                                    // +0x10
virtual void _v14();
virtual void _v18();
virtual void _v1c();
virtual void _v20();
virtual void _v24();
virtual bool _v28();
virtual void _v2c();
virtual void _v30();
    virtual const Math::Rectangle& GetArea();                        // +0x34
    virtual const Math::Rectangle& GetRealArea();                    // +0x38
virtual void _v3c();
virtual void _v40();
virtual void _v44();
virtual void _v48();
virtual void _v4c();
virtual void _v50();
virtual void _v54();
    virtual void _v58();
    virtual void SetShadeColor(uint32_t color);                      // +0x5c
    virtual void SetArea(const Math::Rectangle& area);               // +0x60
    virtual void SetLocation(float x, float y);                      // +0x64
virtual void _v68();
virtual void _v6c();
virtual void _v70();
virtual void _v74();
    virtual void _v78();
    virtual void SetFlag(int flag, bool value);                      // +0x7c
    virtual void SetCaption(const wchar_t* caption);                 // +0x80
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
virtual void _vcc();
virtual void _vd0();
    virtual void _vd4();
    virtual void AddWindow(IWindow_s0106_91e0* pWindow);                        // +0xd8
    virtual void RemoveWindow(IWindow_s0106_91e0* pWindow);                     // +0xdc
virtual void _ve0();
virtual void _ve4();
virtual void _ve8();
virtual void _vec();
    virtual IWindow_s0106_91e0* FindWindowByID(uint32_t id, bool recursive);    // +0xf0
};
}
}
using EA::UTFWin::IWindow_s0106_91e0;
class IWinText {
public:
    virtual int AddRef();                                            // +0x0
    virtual int Release();                                           // +0x4
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
virtual void _v70();
virtual void _v74();
    virtual void _v78();
    virtual void SetFlag(int flag, bool value);                      // +0x7c
    virtual void SetCaption(const wchar_t* caption);                 // +0x80
};
class IWindowManager {
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
virtual void _v4c();
virtual void _v50();
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
    virtual void* GetModalWindow();                                  // +0x84
};
namespace SP {
class cString_s0106_91e0 {   // retail size 0x14
public:
    wchar_t* mpBegin;
    uint32_t pad[4];
    const wchar_t* GetText();                                        // 0x006B55C0
    const wchar_t* c_str() const { return mpBegin; }
};
}
namespace SP {
class cCivData_s0106_91e0;                                                      // size 0x44
}
namespace SP {
class cCityRuntime {
public:
    uint32_t pad00[0x28 / 4];
    int mState;                                 // +0x28
    bool FUN_00b8d970();                         // 0x00B8D970
    int  FUN_00b8dab0();                         // 0x00B8DAB0 (city type)
};
}
namespace SP {
class cCityList {
public:
    uint32_t pad00[0x3c / 4];
    cCityRuntime** mpBegin;                      // +0x3c
    cCityRuntime** mpEnd;                        // +0x40
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
};
}
namespace SP {
class cCivData_s0106_91e0 {
public:
    cCityList* GetCities();                                          // 0x005C65E0 (retail stub name)
};
}
namespace SP {
class cStarRecord_s0106_91e0 {
public:
    cString_s0106_91e0* GetName();                                              // 0x00C707E0
};
}
namespace SP {
class cSpaceGfx {
public:
    class cSlot {
    public:
        virtual int AddRef();                                        // +0x0
        virtual int Release();                                       // +0x4
        virtual void Use(int a);                                     // +0x08 (Show/SetEnabled)
        virtual void Show(bool b);                                   // +0x0c
        virtual bool IsVisible();                                    // +0x10
        virtual void SetTransform(const EffectTransform& t);         // +0x14
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
        virtual void SetParams(int a, const void* data, int count);  // +0x44
    };
    uint32_t pad00[0x30 / 4];
    EA::AutoRefCount_s0106_91e0<cSlot> mSlot30;             // +0x30
    uint32_t pad34;
    cCivData_s0106_91e0* mSelectedID;                       // +0x38
    uint32_t pad3c[(0x94 - 0x3c) / 4];
    class cEffectsMgr {
    public:
virtual void _v00();
virtual void _v04();
        virtual bool CreateVisualEffect(uint32_t id, int flags, void** out);  // +0x08
    }* mpEffectsMgr94;                           // +0x94
};
}
namespace SP {
cSpaceGfx* GetSpaceGfx();                                            // 0x00B3D470 (FUN_00b3d470)
}
namespace SP {
class cPlayerInventory {
public:
    class cCivList {
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
        virtual const Vector3_s0106_91e0& GetPosition();                        // +0x2c
    };
    uint32_t pad00[0x34 / 4];
    cCivList* mpCivList_34;                      // +0x34
    uint32_t pad38[(0x74c - 0x38) / 4];
    uint8_t    mFlag74c;                         // +0x74c
};
}
namespace SP {
class cSimObject {                                                   // object with a window at +0xd4
public:
    uint32_t pad00[0xd4 / 4];
    IWinText* mpText_0d4;                        // +0xd4
};
}
namespace SP {
class cPlayerUFO {
public:
    cPlayerInventory* GetPlayerInventory();                          // 0x00A1AD60
    bool FUN_00ffc8d0(cCivData_s0106_91e0* pCiv);                               // 0x00FFC8D0
    int  FUN_00ffc4e0(cCivData_s0106_91e0* a, cCivData_s0106_91e0* pCiv);                  // 0x00FFC4E0
};
}
namespace SP {
cPlayerUFO* GetUFOSimulator_s0106_91e0();                                       // 0x00FFBE50
}
namespace SP {
class cEmpire_s0106_91e0;
}
namespace SP {
class cSpaceStar;
}
namespace SP {
cCivData_s0106_91e0*  FUN_01021240();                                           // 0x01021240 (active civ)
}
namespace SP {
cSimObject* FUN_01036e20();                                          // 0x01036E20
}
namespace SP {
cSpaceStar* FUN_0067dd50();                                          // 0x0067DD50
}
namespace SP {
cEmpire_s0106_91e0* FUN_01021300();                                             // 0x01021300 (player empire)
}
namespace SP {
int  FUN_01021090();                                                 // 0x01021090 (player empire id)
}
namespace SP {
class cEmpire_s0106_91e0 {
public:
    uint32_t pad00[0x84 / 4];
    int mEmpireID;                              // +0x84
    int FUN_00c30cb0();                                              // 0x00C30CB0
};
}
namespace SP {
class cWindowRef : public EA::AutoRefCount_s0106_91e0<IWindow_s0106_91e0> {
public:
    cWindowRef& operator=(IWindow_s0106_91e0* p);                               // 0x00B5F950 (shared out-of-line instance)
};
}
namespace SP {
class cTextRef : public EA::AutoRefCount_s0106_91e0<IWinText> {
public:
    cTextRef& operator=(IWinText* p);                                // 0x00B5F950 (shared out-of-line instance)
};
}
namespace SP {
class cSPUIMeter {
public:
    bool IsVisible();                                                // 0x00E06970
};
}
namespace SP {
class cMeterHolder {
public:
    class cMeter {
    public:
virtual void _v00();
virtual void _v04();
virtual void _v08();
virtual void _v0c();
        virtual int  GetMaxValue();                                  // +0x10
        virtual void SetValue(int value);                            // +0x14
        virtual int  GetState();                                     // +0x18
    };
    uint32_t pad[0x20c / 4];
    cMeter mMeter;                               // +0x20c
};
}
namespace SP {
cMeterHolder* FUN_00deced0(IWindow_s0106_91e0* pWindow);                         // 0x00DECED0
}
namespace SP {
class cSpaceTokenTranslator_s0106_91e0 {
public:
    uint32_t pad00[3];
    cCityRuntime* mpCity;                        // +0xc
};
}
namespace SP {
extern cSpaceTokenTranslator_s0106_91e0* gpSpaceTokenTranslator;                // 0x016E0D08
}
namespace SP {
struct cModeState { uint32_t pad00[0x2c / 4]; int mState; };          // +0x2c
}
namespace SP {
class cGameModeA { public: bool FUN_00ae9390(); };                    // 0x00AE9390
}
namespace SP {
class cGameModeB { public: bool FUN_00e18c70(int a); };               // 0x00E18C70
}
namespace SP {
class cGameModeC { public: bool FUN_00b5ca60(); };                    // 0x00B5CA60
}
namespace SP {
cGameModeA* FUN_00b3d4a0_s0106_91e0();                                          // 0x00B3D4A0
}
namespace SP {
cGameModeB* FUN_00b3d3f0();                                          // 0x00B3D3F0
}
namespace SP {
cGameModeC* FUN_00b3d230_s0106_91e0();                                          // 0x00B3D230
}
namespace SP {
cModeState* FUN_00b3d4d0_s0106_91e0();                                          // 0x00B3D4D0
}
namespace SP {
IWindowManager* WindowManager_s0106_91e0();                                     // 0x0067CAA0
}
namespace SP {
class cSPUIGlobalUI_s0106_91e0 {
public:
    IWindow_s0106_91e0* FindWindowByID(uint32_t id);                            // 0x00E012B0
};
}
namespace SP {
class cSpaceStar {
public:
virtual void _v00();
virtual void _v04();
virtual void _v08();
virtual void _v0c();
virtual void _v10();
virtual void _v14();
virtual void _v18();
    virtual int* GetRowSpan();                                       // +0x1c
};
}
namespace SP {
void  FUN_010677b0(cCivData_s0106_91e0* pCiv, float x, float y);                // 0x010677B0
}
namespace SP {
void  FUN_01043d10(float* out, void* a, void* b, float c, void* v);  // 0x01043D10
}
namespace SP {
void  Matrix3_Assign(void* m, const void* src);                      // 0x0041CB40
}
namespace SP {
float FUN_00c8c7f0(cCityRuntime* p, int* pOut);                      // 0x00C8C7F0
}
namespace SP {
void* FUN_00bba790(cCivData_s0106_91e0* pCiv);                                  // 0x00BBA790 (city/civ list)
}
namespace SP {
void  SPUIHelpers_SetTooltipText(IWindow_s0106_91e0* w, const wchar_t* text);   // 0x00806DE0
}
namespace SP {
class cSpaceTradeRouteManager_s0106_91e0 {
public:
    float SystemHasTradeRouteWithPlayer(int starID, void* pAvatar);  // 0x01037DD0
};
}
namespace SP {
class cSpaceStarManager {
public:
    cSpaceTradeRouteManager_s0106_91e0* FUN_00ba6490();                         // 0x00BA6490
};
}
namespace SP {
class cGameNounManager_s0106_91e0 { public: void* GetAvatar(); };               // 0x00B1FDB0
}
namespace SP {
cSpaceStarManager* StarManager_s0106_91e0();                                    // 0x00B3D2A0
}
namespace SP {
struct Rect4 { float x1, y1, x2, y2; };
}
namespace SP {
void SPUIHelpers_GetMainWindowArea(Rect4* out);                      // 0x00805EA0
}
namespace SP {
extern uint32_t gStarMeterIDs[5];                                    // 0x0149C158
}
namespace SP {
extern const float kFxOffsetX;                                       // 0x016E2824
}
namespace SP {
extern const float kFxOffsetY;                                       // 0x016E2828
}
namespace SP {
extern const float kFxOffsetZ;                                       // 0x016E282C
}
namespace SP {
extern const Matrix3f kFxMatrixSrc;                                  // 0x016E2800
}
namespace SP {
extern const float kEffectFade;                                      // 0x01488874
}
namespace SP {
extern const float kRolloverBlockHeight;                             // 0x0149C1A4 (26.0f)
}
namespace SP {
namespace SPUIHelpers {
    void DestroyRolloverFrame(IWindow_s0106_91e0* pFrame);                      // 0x008074A0
}
}
namespace SP {
namespace SPUIHelpers {
    IWindow_s0106_91e0* CreateRolloverFrame(const wchar_t* name, float x, float y, float w, float h,
                                 IWindow_s0106_91e0** ppContainer, int a, int b, float radius, uint32_t id);  // 0x008093B0
}
}
namespace SP {
namespace SPUIHelpers {
    void UpdateRolloverFrame(IWindow_s0106_91e0* pFrame, float x, float y, int c, float radius);               // 0x00809370
}
}
namespace SP {
class cSPUISpace_s0106_91e0 {
public:
    uint32_t pad000[(0xe4 - 0x0) / 4];
    cString_s0106_91e0 mStarTooltipA;                      // +0xe4
    cString_s0106_91e0 mStarTooltipB;                      // +0xf8
    uint32_t pad10c[(0x224 - 0x10c) / 4];
    cSPUIGlobalUI_s0106_91e0* mpGlobalUI;                  // +0x224
    uint32_t pad228[(0x588 - 0x228) / 4];
    cTextRef  mStarRolloverText;                // +0x588 (AutoRefCount<IWinText>)
    uint32_t pad58c;
    cWindowRef mStarRolloverFrame;              // +0x590
    uint32_t pad594;
    EA::AutoRefCount_s0106_91e0<IWindow_s0106_91e0> mMissionRolloverRoot;   // +0x598
    EA::AutoRefCount_s0106_91e0<IWindow_s0106_91e0> mStarRolloverRoot;      // +0x59c
    uint32_t pad5a0[3];
    EA::AutoRefCount_s0106_91e0<cSPUIMeter> mpCaptureMeterA;     // +0x5ac
    EA::AutoRefCount_s0106_91e0<cSPUIMeter> mpCaptureMeterB;     // +0x5b0
    EA::AutoRefCount_s0106_91e0<cSPUIMeter> mpAnimator;          // +0x5b4

    void UpdateStarRollover(cStarRecord_s0106_91e0* pStar);                              // 0x010691E0
    void FUN_010697b0(cCivData_s0106_91e0* pCiv);                                        // 0x010697B0
    void FUN_01069aa0();                                                      // 0x01069AA0
    int  UpdateCaptureBarsVisibility(cCivData_s0106_91e0* pCiv);                         // 0x01067510
    void FUN_010677b0(cCivData_s0106_91e0* pCiv, float x, float y, bool b);              // 0x010677B0
};
}
template <class P> static __forceinline void DetachFromParent(const P& pWindow)
{
    if (pWindow->GetParent())
        pWindow->GetParent()->RemoveWindow(pWindow);
}
// ---- items of slice s010691e0 end

// ---- items of slice s01070290 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cProperty;
struct cSavedGameRec;
struct Key_s0107_0290 {
    uint32_t a, b, c;
};
extern Key_s0107_0290 gNullKey;                                    // 0x016e224c
struct Vec3_s0107_0290 { float x, y, z; };
struct Matrix3_s0107_0290 {
    float m[9];
    Matrix3_s0107_0290() {}
    // User-defined copy ctor: retail copies the 3x3 through a stack temporary one float at a time
    // before storing it into the record.
    Matrix3_s0107_0290(const Matrix3_s0107_0290& o) {
        m[0] = o.m[0]; m[1] = o.m[1]; m[2] = o.m[2];
        m[3] = o.m[3]; m[4] = o.m[4]; m[5] = o.m[5];
        m[6] = o.m[6]; m[7] = o.m[7]; m[8] = o.m[8];
    }
};
extern const Vec3_s0107_0290 kSavedGamePos;                        // 0x016e2824
extern const Matrix3_s0107_0290 kSavedGameRot;                     // 0x016e2800
struct cSavedGameRec {
    uint16_t mFlags;                                    // +0x00
    uint16_t mCount;                                    // +0x02
    Vec3_s0107_0290 mPos;                                          // +0x04
    float mW;                                           // +0x10
    Matrix3_s0107_0290 mRot;                                       // +0x14
    // The matrix arrives by reference; retail copies it into a local temporary first (the class has
    // a user copy constructor) and then bit-copies that temporary into the record.
    cSavedGameRec(const Vec3_s0107_0290& pos, const Matrix3_s0107_0290& rot)
        : mFlags(0), mCount(0), mPos(pos), mW(kOne) { mRot = rot; }
};
struct cProperty {
    virtual void AddRef();                              // +0x00
    virtual void Release();                             // +0x04
    virtual void V08(int);                              // +0x08
    virtual void V0c();                                 // +0x0c
    virtual void V10();                                 // +0x10
    virtual void V14(cSavedGameRec* rec);               // +0x14
};
struct cFoodwebSlotInfo {
    cProperty* mpWindow;                                // +0x00  refcounted window (AddRef/Release)
    Key_s0107_0290 mKey2;                                          // +0x04  secondary key, gNullKey by default
    int mKind;                                          // +0x10
    uint32_t mKey;                                      // +0x14
    int mField18;                                       // +0x18
    uint8_t mFlag1c;                                    // +0x1c
    int mIndex;                                         // +0x20
    int mFlag24;                                        // +0x24
    cFoodwebSlotInfo()
        : mpWindow(0), mKey2(gNullKey), mKind(0), mKey(0x3a8be428u),
          mField18(1), mFlag1c(0), mIndex(1), mFlag24(1) {}
};
struct cFoodwebSlotVec {
    cFoodwebSlotInfo* mpBegin;                          // +0x00
    cFoodwebSlotInfo* mpEnd;                            // +0x04
    cFoodwebSlotInfo* mpCapacity;                       // +0x08
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    void insert(cFoodwebSlotInfo* pos, unsigned count, const cFoodwebSlotInfo& value);  // 0x0106ebb0
    void erase(cFoodwebSlotInfo* first, cFoodwebSlotInfo* last);                        // 0x0106eb40
    void resize(unsigned count);
};
struct cPropertyVec {
    cProperty** mpBegin;                                // +0x00
    cProperty** mpEnd;                                  // +0x04
    cProperty** mpCapacity;                             // +0x08
    void insert(cProperty** pos, cProperty* const& value);   // 0x00a0a360 (grow path)
};
struct EffectsManager {
virtual void V00();
virtual void V04();
virtual void V08();
virtual void V0c();
virtual void V10();
virtual void V14();
virtual void V18();
virtual void V1c();
virtual void V20();
virtual void V24();
virtual void V28();
    virtual bool GetProperty(uint32_t key, int arg, cProperty** out);   // +0x2c
};
struct EffectsManager* EffectsManagerPtr();                    // 0x0067ddd0
struct cPointerVec {                                     // eastl::vector<void*, sp_vector_allocator>
    void** mpBegin;                                     // +0x00
    void** mpEnd;                                       // +0x04
    void** mpCapacity;                                  // +0x08
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
};
struct StarManager_s0107_0290 {
    char pad0[0xf0];
    cPointerVec mCivs;                                  // +0xf0 (one entry per empire/civ)
};
StarManager_s0107_0290* StarManager_s0107_0290();                             // 0x00b3d2a0
struct cPlanet_s0107_0290 {
    void* SortBanners();                                // 0x00b8de30
};
cPlanet_s0107_0290* GetPlayerHomePlanet();                         // 0x01021370
struct cCivData_s0107_0290 {
    Vec3_s0107_0290* GetCities();                                  // 0x005c65e0
};
struct cSPUISpace_s0107_0290 {
    char pad0[0x308];
    cPropertyVec mSavedGameList;                        // +0x308
    void F0106f380();                                   // 0x0106f380
    void ShowSavedGames();
};
// ---- items of slice s01070290 end

// ---- items of slice s01070ba0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new(unsigned int size, const char* tag, int a, int b, int c, int d);
namespace EA {
namespace Messaging {
void RemoveHandler(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e);  // 0x00571db0
}
}
namespace SP {
inline float ConstOne() { return *reinterpret_cast<const float*>(0x01485720); }  // 1.0f
}
namespace SP {
inline float ConstTwo() { return *reinterpret_cast<const float*>(0x01470f1c); }  // 2.0f
}
namespace SP {
class cString_s0107_0ba0 {  // retail size 0x14
 public:
  cString_s0107_0ba0();                                                  // 0x006b5060 (thiscall, no args)
  void Load(uint32_t tableId, uint32_t stringId, int flag);   // 0x006b54b0 (thiscall, ret 0xc)
  uint32_t mData[5];
};
}
namespace SP {
class cSpaceTokenTranslator_s0107_0ba0 {  // size 0xc4
 public:
  cSpaceTokenTranslator_s0107_0ba0();                                    // 0x0104a020 (thiscall, returns this)
  uint32_t mData[0x31];
};
}
namespace SP {
namespace UI {
class MissionCardAnimator {  // size 0x20
 public:
  MissionCardAnimator();                                      // 0x007f83e0 (thiscall, returns this)
  uint32_t mData[8];
};  // namespace UI
}
}
namespace SP {
class Callee5ec {
 public:
  void Init(int nFlag);                                       // 0x004ab350 (thiscall, ret 4)
};
}
namespace SP {
class Callee620 {
 public:
  void Init();                                                // 0x00e0a390 (thiscall, plain ret)
};
}
namespace SP {
class IVSlots {
 public:
  virtual void S0();
  virtual void S1();
  virtual void S2();
  virtual void S3();
  virtual void S4();
  virtual void S5();
  virtual void S6();
  virtual void S7(cSpaceTokenTranslator_s0107_0ba0* translator);         // +0x1c
  virtual IVSlots* S8();                                      // +0x20
};
}
namespace SP {
IVSlots* GetVSlotsSingleton();                                // 0x0067de40 (cdecl, no args)
}
namespace SP {
class IWindow_s0107_0ba0 {
 public:
  virtual void V000();          // +0x000
  virtual void V004();          // +0x004  Release()
  virtual void V008();          // +0x008
  virtual void V00c();          // +0x00c
virtual void V010();
virtual void V014();
virtual void V018();
virtual void V01c();
virtual void V020();
virtual void V024();
virtual int V028();
virtual void V02c();
virtual void V030();
virtual void V034();
virtual void V038();
virtual void V03c();
virtual void V040();
virtual void V044();
virtual void V048();
virtual void V04c();
virtual void V050();
virtual void V054();
virtual void V058();
virtual void V05c();
virtual void V060();
virtual void V064();
virtual void V068();
virtual void V06c();
virtual void V070();
virtual void V074();
virtual void V078();
virtual void V07c();
virtual void V080();
virtual void V084();
virtual void V088();
virtual void V08c();
virtual void V090();
virtual void V094();
virtual void V098();
virtual void V09c();
virtual void V0a0();
virtual void V0a4();
virtual void V0a8();
virtual void V0ac();
virtual void V0b0();
virtual void V0b4();
virtual void V0b8();
virtual void V0bc();
virtual void V0c0();
virtual void V0c4();
virtual void V0c8();
virtual void V0cc();
virtual void V0d0();
virtual void V0d4();
virtual void V0d8();
  virtual void V0dc(void* p);
virtual void V0e0();
virtual void V0e4();
virtual void V0e8();
virtual void V0ec();
virtual void V0f0();
virtual void V0f4();
virtual void V0f8();
virtual void V0fc();
virtual void V100();
virtual void V104();
  virtual void V108(void* p);   // +0x108
  void F_fe7e10();              // 0x00fe7e10
};
}
namespace SP {
class ILayout : public IWindow_s0107_0ba0 {
 public:
  IWindow_s0107_0ba0* FindWindowByID(uint32_t id, int flag);  // 0x008105b0
  void Shutdown(uint32_t flag);                    // 0x00811ad0
};
}
namespace SP {
class IGlobalUI : public IWindow_s0107_0ba0 {
 public:
  IWindow_s0107_0ba0* FindWindowByID(uint32_t id);            // 0x00e012b0
};
}
namespace SP {
class IObj8Arg {
 public:
  virtual void V000();
  virtual void V004();
  virtual void V008(int flag);
};
}
namespace SP {
class IObjCArg {
 public:
  virtual void V000();
  virtual void V004();
  virtual void V008();
  virtual void V00c(int flag);
};
}
namespace SP {
class ICheatMgr {
 public:
virtual void V000();
virtual void V004();
virtual void V008();
virtual void V00c();
virtual void V010();
virtual void V014();
virtual void V018();
  virtual void V01c(uint32_t arg);
};
}
namespace SP {
class IObj31c : public IWindow_s0107_0ba0 {
 public:
  void* mpField4;   // +0x4
};
}
namespace SP {
class IRefObj {
 public:
  virtual void OnRelease(int flag);  // +0x0
  volatile int32_t mRef;             // +0x4
  void F_e28a80();                   // 0x00e28a80
  int Release() {
    const int32_t ref = --mRef;
    if (ref == 0) {
      mRef = 1;
      OnRelease(1);
    }
    return ref;
  }
};
}
namespace SP {
class CTooltip {
 public:
  virtual void OnRelease(int flag);  // +0x0
  volatile int32_t mRef;             // +0x4
  void Shutdown();                   // 0x00e36500
  int Release() {
    const int32_t ref = --mRef;
    if (ref == 0) {
      mRef = 1;
      OnRelease(1);
    }
    return ref;
  }
};
}
namespace SP {
class Deque5ec {                     // eastl::deque<SP::cStarRecord*>
 public:
  void clear();                      // 0x00996460
 private:
  char mBytes[0x2c];
};
}
namespace SP {
class Blk28Vec_s0107_0ba0 {                     // 0x28-byte element vector at +0x530
 public:
  uint32_t* mpBegin;                 // +0x0
  uint32_t* mpEnd;                   // +0x4
  uint32_t* mpCapacity;              // +0x8
  void erase(uint32_t* first, uint32_t* last);  // 0x0106eb40
};
}
namespace SP {
struct Space2a0 {
  void* mp0;                         // +0x2a0
  void* mp4;                         // +0x2a4
  uint32_t m8;                       // +0x2a8
  uint32_t mc;                       // +0x2ac
  float mf10;                        // +0x2b0
  float mf14;                        // +0x2b4
  char mRest[0x40];                  // +0x2b8 .. +0x2f7
  void F(void* a, uint32_t b);       // 0x01068400
};
}
namespace SP {
class IGlobal0810 {
 public:
  void SetParent(void* p);           // 0x00dd2800
};
}
namespace SP {
IGlobal0810* GetGlobal0810();        // 0x00dd1ca0
}
namespace SP {
class CurMgr {
 public:
  bool FindLocal(uint32_t id);       // 0x00801bb0
};
}
namespace SP {
CurMgr* GetCurMgr();                 // 0x0067cab0
}
namespace SP {
bool IsWorldLayoutFlagSet(int flag); // 0x00685520
}
namespace SP {
IWindow_s0107_0ba0* FUN_00b3d230_s0107_0ba0();             // 0x00b3d230
}
namespace SP {
ICheatMgr* CheatManager();           // 0x0067de20
}
namespace SP {
extern uint32_t g15b7330;            // 0x015b7330
}
namespace SP {
extern IWindow_s0107_0ba0* g16e2234;            // 0x016e2234
}
namespace SP {
class cSPUISpace_s0107_0ba0 {
 public:
  cSPUISpace_s0107_0ba0();                                               // 0x01070ba0
  void Shutdown();                                            // 0x01071570
  void FUN_0106f540();                                        // 0x0106f540
  void FUN_0106ef30();                                        // 0x0106ef30
  void FUN_01068230();                                        // 0x01068230
  void FUN_010673f0(int flag);                                // 0x010673f0
  void FUN_01067510(int flag);                                // 0x01067510

 private:
  template <class T>
  T& At(uint32_t off) { return *reinterpret_cast<T*>(reinterpret_cast<char*>(this) + off); }
  cString_s0107_0ba0* Str(uint32_t off) { return reinterpret_cast<cString_s0107_0ba0*>(reinterpret_cast<char*>(this) + off); }

 public:
  char mPad000[0x10];               // +0x000 (three vtable pointers + id)
  IObj8Arg* mp10;                   // +0x010
  char mPad014[0x210];              // +0x014 .. +0x223
  IGlobalUI* mpGlobalUI;            // +0x224
  IRefObj* mpRef228;                // +0x228
  ILayout* mpLayout22c;             // +0x22c
  ILayout* mpLayout230;             // +0x230
  ILayout* mpLayout234;             // +0x234
  char mPad238[0x20];               // +0x238 .. +0x257
  ILayout* mpLayout258;             // +0x258
  char mPad25c[0x44];               // +0x25c .. +0x29f
  Space2a0 m2a0;                    // +0x2a0
  int32_t m2f8;                     // +0x2f8
  IObjCArg* mp2fc;                  // +0x2fc
  IObjCArg* mp300;                  // +0x300
  IObjCArg* mp304;                  // +0x304
  char mPad308[0x14];               // +0x308 .. +0x31b
  IObj31c* mp31c;                   // +0x31c
  char mPad320[0x210];              // +0x320 .. +0x52f
  Blk28Vec_s0107_0ba0 mVec530;                 // +0x530
  char mPad53c[0x30];               // +0x53c .. +0x56b
  uint32_t m56c;                    // +0x56c
  uint32_t m570;                    // +0x570
  uint32_t m574;                    // +0x574
  uint32_t m578;                    // +0x578
  uint32_t m57c;                    // +0x57c
  IWindow_s0107_0ba0* mp580;                   // +0x580
  IWindow_s0107_0ba0* mp584;                   // +0x584
  IWindow_s0107_0ba0* mp588;                   // +0x588
  char mPad58c[0xc];                // +0x58c .. +0x597
  IWindow_s0107_0ba0* mp598;                   // +0x598
  IWindow_s0107_0ba0* mp59c;                   // +0x59c
  IWindow_s0107_0ba0* mp5a0;                   // +0x5a0
  IWindow_s0107_0ba0* mp5a4;                   // +0x5a4
  CTooltip* mp5a8;                  // +0x5a8
  char mPad5ac[0x18];               // +0x5ac .. +0x5c3
  IWindow_s0107_0ba0* mp5c4;                   // +0x5c4
  char mPad5c8[0x24];               // +0x5c8 .. +0x5eb
  Deque5ec mDeque5ec;               // +0x5ec
  char mPad618[0x8];                // +0x618, +0x61c
  char mPad620[0x74];               // +0x620 .. +0x693
  IWindow_s0107_0ba0* mp694;                   // +0x694
};
}
// ---- items of slice s01070ba0 end

// ---- items of slice s0106f5b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IRelC0 {                                                              // Release at +0xc0
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
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v1a();
virtual void v1b();
virtual void v1c();
virtual void v1d();
virtual void v1e();
virtual void v1f();
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
virtual void v2a();
virtual void v2b();
virtual void v2c();
virtual void v2d();
virtual void v2e();
virtual void v2f();
    virtual void Release();
};
struct RefCounted {                                  // EA RefCountTemplate: vptr, count at +4, deleting dtor in slot 0
    virtual ~RefCounted();
    int mnRefCount;
    void Release()
    {
        int n = mnRefCount;
        mnRefCount = n - 1;
        n--;
        if (n == 0) {
            mnRefCount = 1;
            delete this;
        }
    }
};
struct Arc1_s0106_f5b0 { IRel1* p; ~Arc1_s0106_f5b0() { if (p) p->Release(); } };
struct Arc2_s0106_f5b0 { IRel2* p; ~Arc2_s0106_f5b0() { if (p) p->Release(); } };
struct ArcC0 { IRelC0* p; ~ArcC0() { if (p) p->Release(); } };
struct ArcRC { RefCounted* p; ~ArcRC() { if (p) p->Release(); } };
struct SpBlock { void* p; ~SpBlock() { if (p && ((int*)p)[-1] != 0) operator_delete__(p); } };
struct RawPtr  { void* p; ~RawPtr() { if (p) operator_delete__(p); } };
struct cString_s0106_f5b0 { uint32_t d[5]; ~cString_s0106_f5b0();                            // 0x006b5240 (out of line)
                 const char* GetText(const void* pKey, int flags); };   // 0x006b55c0
struct StrVec {                                                        // eastl::vector<cString, sp_vector_allocator> (+ 1 dword)
    cString_s0106_f5b0* mpBegin; cString_s0106_f5b0* mpEnd; cString_s0106_f5b0* mpCap; uint32_t alloc; uint32_t extra;
    ~StrVec()
    {
        cString_s0106_f5b0* e = mpEnd;
        for (cString_s0106_f5b0* it = mpBegin; it < e; ++it)
            it->~cString_s0106_f5b0();
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            operator_delete__(mpBegin);
    }
};
struct HashWStr {                                   // hashtable<wchar_t const*, ...>   DoFreeNodes at 0x00693230
    uint32_t pad0; void** mpBuckets; uint32_t mnBuckets; uint32_t mnElements;
    void DoFreeNodes(void** b, uint32_t n);
    ~HashWStr() { DoFreeNodes(mpBuckets, mnBuckets); mnElements = 0; if (mnBuckets > 1) operator_delete__(mpBuckets); }
};
struct HashB {                                      // hashtable at +0x2a0, free routine at 0x01068400
    uint32_t pad0; void** mpBuckets; uint32_t mnBuckets; uint32_t mnElements;
    void DoFreeNodes(void** b, uint32_t n);
    ~HashB() { DoFreeNodes(mpBuckets, mnBuckets); mnElements = 0; if (mnBuckets > 1) operator_delete__(mpBuckets); }
};
struct HashTool {                                   // hashtable<uint, pair<uint, AutoRefCount<cSPToolStrategy>>>   0x00961d60
    uint32_t pad0; void** mpBuckets; uint32_t mnBuckets; uint32_t mnElements;
    void DoFreeNodes(void** b, uint32_t n);
    ~HashTool() { DoFreeNodes(mpBuckets, mnBuckets); mnElements = 0; if (mnBuckets > 1) operator_delete__(mpBuckets); }
};
struct ObjE0A400 { uint32_t d[29]; ~ObjE0A400(); };   // 0x00e0a400
struct Obj4AA120 { uint32_t d[12]; ~Obj4AA120(); };   // 0x004aa120
struct Obj6CB90  { uint32_t d[14]; ~Obj6CB90(); }; // 0x0106cb90 (0x530..0x568)
struct Obj4B5440 { uint32_t d[5]; ~Obj4B5440(); }; // 0x004b5440
struct SharedLibVec { void* a; void* b; void* c; uint32_t alloc; ~SharedLibVec(); };  // 0x005c7f10
struct AutoHandler_s0106_f5b0 {
    void* mpHandler; uint32_t a, b, c, d;
    ~AutoHandler_s0106_f5b0()
    {
        if (mpHandler) {
            void* h = mpHandler;
            mpHandler = 0;
            EA_Messaging_RemoveHandler(h, a, b, c, d);
        }
    }
};
struct BaseRes   { virtual ~BaseRes() {} };                        // GmeEditorResBase-side vptr at +0
struct BaseCount { virtual ~BaseCount() {} int mnRefCount; };      // RefCountVTemplate<int> at +4
struct BaseMsg   { virtual ~BaseMsg() {} };                        // IMsgHandler at +0xc
struct UIMgrA; struct UIMgrB;
UIMgrA* FUN_0067de40();                                            // cdecl, no args
struct UIMgrB { virtual void p00(); virtual void p01(); virtual void p02(); virtual void p03();
virtual void p04();
virtual void p05();
virtual void p06();
virtual void p07();
                virtual void Set(void* v); };                       // +0x20
struct UIMgrA { virtual void p00(); virtual void p01(); virtual void p02(); virtual void p03();
virtual void p04();
virtual void p05();
virtual void p06();
virtual void p07();
                virtual UIMgrB* Get(); };                           // +0x20
struct DeletableObj { virtual ~DeletableObj(); };
struct cSpaceTokenTranslator
{
    char     pad00[0xc];
    uint32_t mPlanetId;    // +0x0c: planet id of the active planet, refreshed on every focus change
    uint32_t mPad14;       // +0x14
    void*    mpRecord;     // +0x24: species profile of the focused record
};
extern cSpaceTokenTranslator* g_16e0d08;                            // 0x016e0d08
namespace SP {
struct cSPUIWidget;
}
namespace SP {
struct cSPUISpace_s0106_f5b0;
}
namespace SP {
struct cSPTool;
}
namespace SP {
struct IFocusTarget;
}
namespace SP {
struct IFocusTarget
{
    virtual void OnFocusLost();                        // +0x00
    virtual void Release();                            // +0x04
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
    virtual uint32_t GetTypeId();                      // +0x1c
    virtual uint32_t GetClassHash();                   // +0x20
    virtual void v09();
    virtual uint32_t GetFocusFlags();                  // +0x28
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
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v1a();
virtual void v1b();
virtual void v1c();
virtual void v1d();
virtual void v1e();
virtual void v1f();
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
virtual void v2a();
virtual void v2b();
virtual void v2c();
virtual void v2d();
virtual void v2e();
virtual void v2f();
    virtual void GetFocusTransform(float u, float v, float* pOut);             // +0xc0 (slot 48)
};
}
namespace SP {
struct cSPUIWindow                                    // UI window handed out by cSPUIGlobalUI::FindWindowByID
{
virtual void w00();
virtual void w01();
virtual void w02();
virtual void w03();
    virtual cSPUIWidget* GetContent();                 // +0x10
virtual void w05();
virtual void w06();
virtual void w07();
virtual void w08();
virtual void w09();
virtual void w0a();
virtual void w0b();
virtual void w0c();
virtual void w0d();
virtual void w0e();
virtual void w0f();
virtual void w10();
virtual void w11();
virtual void w12();
virtual void w13();
virtual void w14();
virtual void w15();
virtual void w16();
virtual void w17();
virtual void w18();
virtual void w19();
virtual void w1a();
virtual void w1b();
    virtual void SetPosition(float x, float y);        // +0x70 (slot 28)
virtual void w1d();
virtual void w1e();
    virtual void SetVisible(bool show, bool focusSame); // +0x7c (slot 31)
};
}
namespace SP {
struct cSPUIWidget : public IFocusTarget              // IFocusTarget supplies slots 0..0xc0
{
    virtual void SetLayoutPosition(float x, float y, const float* pAnchor);   // +0xc4 (slot 49)
};
}
namespace SP {
struct cSPUIGlobalUI_s0106_f5b0
{
    cSPUIWindow* FindWindowByID(uint32_t id);           // 0x00e012b0 (thiscall, not virtual)
};
}
namespace SP {
struct cUITimedTooltip_s0106_f5b0 { void Hide(); };               // 0x00e36620
}
namespace SP {
struct cSPUIRolloverCivRelationship
{
    void ShowRelationshipRollover(IFocusTarget* pTarget, uint32_t civId, bool a);   // 0x00e2d6a0
    void HideRelationshipRollover();                                                // 0x00e2a6c0
};
}
namespace SP {
struct Key_s0106_f5b0 { uint32_t mHash; uint32_t mPad04; uint32_t mPad08; };
}
namespace SP {
struct cSPEditorSpeciesProfile
{
    char pad00[0x51c];
    void* mpIconBlock;                                 // +0x51c
};
}
namespace SP {
struct cSPEditorSpeciesManager_s0106_f5b0
{
    cSPEditorSpeciesProfile* GetProfile(const Key_s0106_f5b0& id); // 0x004df550
};
}
namespace SP {
cSPEditorSpeciesManager_s0106_f5b0* FUN_00401090(const Key_s0106_f5b0& id);  // 0x00401090
}
namespace SP {
struct cSPLivingUniverse
{
    char pad00[0x13c];
    uint32_t mPlanetId;                                // +0x13c
    static cSPLivingUniverse* GetActivePlanet();       // 0x01021260
    static void* GetActivePlanetRecord();              // 0x010212a0
    static cSPLivingUniverse* GetPlayerEmpire();       // 0x01021300
    void* GetFocusedCiv();                             // 0x00c71e30
};
}
namespace SP {
int  GetRecorderState();                               // 0x00435e90
}
namespace SP {
void KillSetiEffects(uint32_t hash, uint32_t value);   // 0x00435ed0
}
namespace SP {
struct cTerraformingManager { int GetUnlockedCount(); };           // 0x00bbe470
}
namespace SP {
cTerraformingManager* TerraformingManager();                       // 0x00b3d430
}
namespace SP {
int FUN_00bbce40(void* pPlanetRecord);                             // 0x00bbce40
}
namespace SP {
struct cGameNounAction { virtual void n00(); virtual const char* GetName(int a, int b, int c); };  // +0x04
}
namespace SP {
struct cGameNoun
{
    char pad00[0x34];
    cGameNounAction mAction;                           // +0x34
};
}
namespace SP {
struct cGameNounList { cGameNoun** mpNouns; };
}
namespace SP {
struct cPlayerCivilization
{
    char pad00[0x84];
    uint32_t mId;                                      // +0x84
    int GetNounCount();                                // 0x00bf01e0
    cGameNounList* GetNounList();                      // 0x00bef6c0
};
}
namespace SP {
struct cGameNounManager_s0106_f5b0
{
    cPlayerCivilization* GetPlayerCivilization();      // 0x00b25fb0
};
}
namespace SP {
cGameNounManager_s0106_f5b0* NounManager_s0106_f5b0();                       // 0x00b3d300
}
namespace SP {
struct cAudioSystem
{
virtual void a00();
virtual void a01();
virtual void a02();
virtual void a03();
virtual void a04();
virtual void a05();
virtual void a06();
virtual void a07();
    virtual void* GetParam();                          // +0x20
};
}
namespace SP {
cAudioSystem* GetSystemAT();                           // 0x00a206f0
}
namespace SP {
struct cSPPlayerInventory;
}
namespace SP {
struct cSPSimulatorSpaceGame
{
    char pad00[0x14];
    cSPUISpace_s0106_f5b0*  mpUISpace;                            // +0x14
    cSPPlayerInventory* GetPlayerInventory();          // 0x00a1ad60
};
}
namespace SP {
cSPSimulatorSpaceGame* SpaceGameGet_s0106_f5b0();                 // 0x01002bd0
}
namespace SP {
inline cSPUISpace_s0106_f5b0* GetUISpace()                        // inlined everywhere: SpaceGameGet() ? ->mpUISpace : 0
{
    cSPSimulatorSpaceGame* pGame = SpaceGameGet_s0106_f5b0();
    return pGame != 0 ? pGame->mpUISpace : 0;
}
}
namespace SP {
bool GetPropertyAsKeyInstance(const void* pList, const Key_s0106_f5b0* pKey, uint32_t& keyInstance);   // 0x006a12a0
}
namespace SP {
struct cSPPlayerInventory
{
    cSPTool* GetToolFromToolID(const Key_s0106_f5b0& id);         // 0x00ff3d40
};
}
namespace SP {
struct cFocusRecord
{
    uint32_t mPad00;                                   // +0x00
    Key_s0106_f5b0      mKey04;                                   // +0x04
    uint32_t mValue0c;                                 // +0x0c
    uint32_t mKind10;                                  // +0x10 (sub kind / key hash)
    uint32_t mSubType14;                               // +0x14
    uint32_t mKind18;                                  // +0x18 (0 = species, 2 = planet, 3 = plant/tool)
    uint8_t  mbFlag1c;                                 // +0x1c
    char     pad1d[3];
    int      mIndex20;                                 // +0x20
};
}
namespace SP {
struct cFocusChangeData
{
    char pad00[0x18];
    IFocusTarget* mpNewTarget;                         // +0x18
};
}
namespace SP {
class cSPUISpace_s0106_f5b0 : public BaseRes, public BaseCount, public BaseMsg { public:
    uint32_t     pad10;               // 0x10
    uint32_t     mDeleteButtonWindow; // 0x14 (focus window id of the delete button)
    ArcC0        m018;                // 0x18
    cString_s0106_f5b0      s01c,
                 s030,
                 s044,
                 s058,
                 s06c,
                 s080,
                 s094,
                 s0a8,
                 s0bc,
                 s0d0,
                 s0e4,
                 s0f8,
                 s10c,
                 s120,
                 s134,
                 s148,
                 s15c,
                 s170,
                 s184,
                 s198,
                 s1ac,
                 s1c0,
                 s1d4,
                 s1e8,
                 s1fc,
                 s210;   // 0x1c .. 0x210 (step 0x14)
    cSPUIGlobalUI_s0106_f5b0* mpGlobalUI;        // 0x224
    ArcRC        m228;                // 0x228
    Arc2_s0106_f5b0         m22c, m230, m234;    // 0x22c
    Arc1_s0106_f5b0         m238;                // 0x238
    uint32_t     pad23c;              // 0x23c
    SpBlock      m240;                // 0x240
    uint32_t     pad244[4];           // 0x244
    Arc2_s0106_f5b0         m254, m258;          // 0x254
    HashTool     m25c;                // 0x25c
    uint32_t     pad26c[4];           // 0x26c
    RawPtr       m27c;                // 0x27c
    uint32_t     pad280[5];           // 0x280
    Arc1_s0106_f5b0         m294, m298, m29c;    // 0x294
    HashB        m2a0;                // 0x2a0
    uint32_t     pad2b0[4];           // 0x2b0
    SpBlock      m2c0;                // 0x2c0
    uint32_t     pad2c4[4];           // 0x2c4
    HashWStr     m2d4;                // 0x2d4
    uint32_t     pad2e4[6];           // 0x2e4
    Arc1_s0106_f5b0         m2fc, m300, m304;    // 0x2fc
    Obj4B5440    m308;                // 0x308
    Arc1_s0106_f5b0         m31c;                // 0x31c
    uint32_t     pad320;              // 0x320
    cString_s0106_f5b0      s324,
                 s338,
                 s34c,
                 s360,
                 s374,
                 s388,
                 s39c,
                 s3b0,
                 s3c4,
                 s3d8,
                 s3ec,
                 s400,
                 s414,
                 s428,
                 s43c,
                 s450,
                 s464,
                 s478,
                 s48c,
                 s4a0,
                 s4b4,
                 s4c8,
                 s4dc,
                 s4f0;   // 0x324 .. 0x4f0 (step 0x14)
    StrVec       v504;                // 0x504
    StrVec       v518;                // 0x518
    uint32_t     pad52c;              // 0x52c
    Obj6CB90     m530;                // 0x530
    DeletableObj* mp568;              // 0x568
    AutoHandler_s0106_f5b0  m56c;                // 0x56c
    Arc1_s0106_f5b0         m580;                // 0x580
    ArcC0        m584;                // 0x584
    Arc1_s0106_f5b0         m588, m58c, m590, m594, m598, m59c, m5a0, m5a4;   // 0x588
    ArcRC        m5a8;                // 0x5a8
    Arc1_s0106_f5b0         m5ac, m5b0, m5b4;    // 0x5ac
    uint32_t     pad5b8[2];           // 0x5b8
    Arc1_s0106_f5b0         m5c0, m5c4;          // 0x5c0
    uint8_t      m5c8[0xb];           // 0x5c8
    uint8_t      mb5d3;               // 0x5d3: delete-button focus state (class hash 0x34ef68d)
    uint8_t      mb5d4;               // 0x5d4: star-object focus state (class hash 0x3e1a6a5)
    uint8_t      pad5d5[3];           // 0x5d5
    SpBlock      m5d8;                // 0x5d8
    uint32_t     pad5dc[4];           // 0x5dc
    Obj4AA120    m5ec;                // 0x5ec
    Arc2_s0106_f5b0         m61c;                // 0x61c
    ObjE0A400    m620;                // 0x620
    Arc1_s0106_f5b0         m694;                // 0x694
    SharedLibVec m698;                // 0x698

    // focus / tooltip plumbing (addresses in the comments)
    cUITimedTooltip_s0106_f5b0* GetTimedTooltip() { return (cUITimedTooltip_s0106_f5b0*)m5a8.p; }
    cSPUIRolloverCivRelationship* GetCivRollover() { return (cSPUIRolloverCivRelationship*)m5a4.p; }
    bool DoFocusChange(IFocusTarget* pOld, const cFocusChangeData* pChange);  // 0x0106fc90
    void SetToolTip(IFocusTarget* pTarget, const char* pText, void* pIconBlock);  // 0x01067c50
    cFocusRecord* FUN_01067ef0(uint32_t typeId);                             // 0x01067ef0
    void FUN_0106f1a0(cFocusRecord* pRecord, int a);                         // 0x0106f1a0
    void* FUN_01066120(uint32_t typeId);                                     // 0x01066120
    void FUN_0106e720(IFocusTarget* pTarget, void* pInfo);                   // 0x0106e720
    void FUN_0106e680(cSPTool* pTool);                                       // 0x0106e680
    uint32_t FUN_0106edc0(cSPTool* pTool);                                   // 0x0106edc0

    virtual ~cSPUISpace_s0106_f5b0();
};
}
namespace SP {
extern const Key_s0106_f5b0 g_propKeyToolSlot;
}
// ---- items of slice s0106f5b0 end

// ---- items of slice s01071a00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kRefreshInterval;                   // 0x016e2230
extern bool gDebugFlag6ec;                             // 0x016e06ec
extern bool gDebugFlag6ed;                             // 0x016e06ed
extern bool gDebugFlag6ee;                             // 0x016e06ee
extern void* __cdecl rt_memcpy(void* dst, const void* src, unsigned size);   // 0x011e0744
extern const float kRatioScale;                        // 0x013ec4d0
extern void FUN_00ad48b0();                            // 0x00ad48b0 (game-data vector filter)
extern void FUN_00cd7d10();   // 0x00cd7d10
extern void FUN_00d3d420();   // 0x00d3d420
extern void FUN_00acdff0();   // 0x00acdff0
extern void FUN_00b1e500();   // 0x00b1e500
extern void FUN_00b2d9d0();   // 0x00b2d9d0
struct Key_s0107_1a00 {                                           // 12-byte resource key (memory order)
    uint32_t a, b, c;
    bool operator==(const Key_s0107_1a00& o) const { return a == o.a && b == o.b && c == o.c; }
};
extern Key_s0107_1a00 gNullKey_s0107_1a00;                                   // 0x016e224c
extern const Key_s0107_1a00 kSlotImages[9];                       // 0x015b93b4 (3 triples of window images)
struct Elem;
struct ElemVector {
    uint32_t mUnused;
    Elem** mpBegin;                                    // +4
    Elem** mpEnd;                                      // +8
};
struct Sim {                                            // Sim sub-object at Elem+0x508
    char pad[0x20c];
    float NodeRatio();                                 // 0x00bfc490
};
struct Elem {
    char pad0[0x508];
    Sim mSim;                                          // +0x508
    int mType;                                         // +0x714
    Key_s0107_1a00 GetKey();                                      // 0x00c3e1e0 (sret, ret 4)
};
struct PlanetRecord_s0107_1a00 {
    char pad0[0x2c];
    uint32_t mFlags;                                   // +0x2c
    char pad1[0xd0 - 0x30];
    char* mpKeysBegin;                                 // +0xd0
    char* mpKeysEnd;                                   // +0xd4
};
struct Planet_s0107_1a00 {
    char pad[0x13c];
    PlanetRecord_s0107_1a00* mpRecord;                            // +0x13c
    bool SetSpeciesAsScanned(const Key_s0107_1a00* key);          // 0x00c73ea0 (thiscall, ret 4)
};
struct TerraformMgr {
    int F670(PlanetRecord_s0107_1a00* rec);                       // 0x00bbc670 (ret 4)
    int GetUnlockedCount(PlanetRecord_s0107_1a00* rec);           // 0x00bbe470 (ret 4)
    Key_s0107_1a00 GetKeyA();                                     // 0x00bbc4f0 (sret, ret 4)
    Key_s0107_1a00 GetKeyB();                                     // 0x00bbc510 (sret, ret 4)
    bool F6a0(int index, PlanetRecord_s0107_1a00* rec);           // 0x00bbc6a0 (ret 8)
    bool F850(int index, int which, PlanetRecord_s0107_1a00* rec);// 0x00bbe850 (ret 0xc)
    Key_s0107_1a00 F870(int index, uint32_t id, PlanetRecord_s0107_1a00* rec);   // 0x00bbc870 (sret, ret 0x10)
    Key_s0107_1a00 F950(int index, int which, PlanetRecord_s0107_1a00* rec);     // 0x00bbc950 (sret, ret 0x10)
    Key_s0107_1a00 Fa30(int index, PlanetRecord_s0107_1a00* rec);                // 0x00bbca30 (sret, ret 0xc)
};
#define VT1(R, o, off, a) \
    ((R (__thiscall*)(void*, void*))(*(void***)(o))[(off) / 4])((o), (void*)(a))
#define VT4F(R, o, off, k, v, a, b) \
    ((R (__thiscall*)(void*, uint32_t, float, int, int))(*(void***)(o))[(off) / 4])((o), (k), (v), (a), (b))
namespace SP {
 class cSPUISpace_s0107_1a00; 
}
struct UIWindow;
struct UILayout {                                      // cSPUILayout (windows owned by a layout)
    UIWindow* FindWindowByID(uint32_t id, int flag);   // 0x008105b0 (ret 8)
};
struct UIWindow {
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
    virtual void SetFlag(int flag, bool value);        // slot 31 (+0x7c)
    virtual void SetCaption(const wchar_t* text);      // slot 32 (+0x80)
};
struct GlobalUI_s0107_1a00 {
    UIWindow* FindWindowByID(uint32_t id);             // 0x00e012b0 (thiscall, ret 4)
};
struct Property_s0107_1a00 {
    char pad[0x12];
    uint16_t mType;                                    // +0x12
    int* GetData();                                    // 0x0041e990 (thiscall)
};
struct PropertyHolder {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
    virtual void v08();
    virtual bool GetProperty(uint32_t id, Property_s0107_1a00** out);   // slot 9 (+0x24)
};
struct TerrainEditor_s0107_1a00;
struct NounManager_s0107_1a00 {
    ElemVector* GetGameDataVector(void* a, void* b, void* c, void* d, uint32_t e);   // 0x00b21340 (ret 0x14)
    TerrainEditor_s0107_1a00* GetCurrentTerrainSphere();          // 0x00f67d90
};
struct TerrainEditor_s0107_1a00 {
    char pad0[0x124c];
    int mField;                                        // +0x124c
};
struct FoodwebSlotInfo {                               // SP::cSPUISpace::cFoodwebSlotInfo
    UIWindow* mpWindow;                                // +0x00 (refcounted: v00 add, v01 release)
    char pad04[0xc];
    int mKind;                                         // +0x10
    uint32_t mKey;                                     // +0x14
    char pad18[8];
    int mIndex;                                        // +0x20
    int mFlag;                                         // +0x24
};
struct FoodwebSlotVector {                             // eastl::vector<cFoodwebSlotInfo> at +0x530
    FoodwebSlotInfo* mpBegin;                          // +0x00
    FoodwebSlotInfo* mpEnd;                            // +0x04
    FoodwebSlotInfo* mpCapacity;                       // +0x08
    void resize(int n);                                // 0x01070af0 (ret 4)
};
struct Key12 { uint32_t a, b, c; };
struct WindowSet {                                     // UI window set at cSPUISpace+0x620
    void RefreshWindows();                                     // 0x00e0a5c0
    void AttachWindow(UIWindow* w, const Key12* desc);       // 0x00e0a4c0 (ret 8)
    void SetFlags(const Key12* key, int count);          // 0x00e0a780 (ret 8)
    void* GetSlotLayout(int i);                               // 0x00e09c90 (ret 4)
};
struct FlagVector {                                    // vector<uint32_t> at cSPUISpace+0x5d8
    uint32_t* mpBegin;                                 // +0x00
    uint32_t* mpEnd;                                   // +0x04
    void SetValues(int arg, const int* value);           // 0x004746c0 (ret 8)
    void erase(uint32_t* first, uint32_t* last) {
        // The retail inline counts the moved tail in elements (the only caller passes an empty range).
        rt_memcpy(first, last, (unsigned)((char*)mpEnd - (char*)last));
        mpEnd -= last - first;
    }
};
struct PosseEntry { uint32_t a, b; };
struct Posse {                                         // cSPUIPosse (at cSPUISpace+0x5c4)
    char pad0[0xa4];
    PosseEntry* mpBegin;                               // +0xa4
    PosseEntry* mpEnd;                                 // +0xa8
    Elem* FindItem(Elem* noun);                        // 0x00e24c90 (ret 4)
};
struct UfoItem {                                       // item returned by cSPUIPosse::FindItem
    void V80(uint32_t key, float ratio, int a, int b); // slot 0x80 (ret 0x10)
};
struct UfoNode {
    UfoNode* mpNext;                                   // +0x00
    char pad04[4];
    int mValue;                                        // +0x08
};
struct UfoList : UfoNode {                             // sentinel node embedded at +0x00
    char pad0c[0x10];
};
struct Ufo {
    UfoList* GetList();                              // 0x0108db30
};
struct PosseItemSpace {
    void* Construct(int a);                            // 0x00e259d0 (ctor-shaped, ret 4)
};
Ufo* GetUFOSimulator_s0107_1a00();                                // 0x00ffbe50
int GetPlayerEmpireID();                               // 0x01021090 (cdecl)
int FUN_0106b860(int arg);                             // 0x0106b860 (cdecl, 1 arg)
struct FixedStr16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
    wchar_t* mpPool;
    wchar_t mBuf[16];
    FixedStr16() {
        mpBegin = mBuf;
        mpEnd = mBuf;
        mpPool = mBuf;
        mpCapacity = mBuf + 16;
        mBuf[0] = 0;
    }
    __forceinline ~FixedStr16() {
        wchar_t* p = mpBegin;
        if (((int)((char*)mpCapacity - (char*)p) & ~1) > 2 && p != 0 && p != mpPool)
            operator_delete__(p);
    }
    void sprintf(const wchar_t* fmt, ...);             // 0x0068d0b0 (variadic, this pushed)
};
struct true_type {};
struct InsertResult { void* it; bool inserted; };
struct KeySet {                                        // eastl::set<Key> (rbtree, retail layout)
    uint32_t mCompare;
    void* mpNodeRight;
    void* mpNodeLeft;
    void* mpNodeParent;
    char mColor;
    uint32_t mnSize;
    KeySet() {
        mpNodeRight = &mpNodeRight;
        mpNodeLeft = &mpNodeRight;
        mpNodeParent = 0;
        mColor = 0;
        mnSize = 0;
    }
    ~KeySet() { DoNuke(mpNodeParent); }
    void DoNuke(void* node);                           // 0x004e8a30
    InsertResult DoInsertValue(const Key_s0107_1a00& value, true_type);   // 0x004290c0 (sret, ret 0xc)
    InsertResult insert(const Key_s0107_1a00& value) { return DoInsertValue(value, true_type()); }
};
float SPUIHelpers_GetElapsedSeconds();                 // 0x00805080 (cdecl, returns st0)
TerraformMgr* GetTerraformingManager();                // 0x00b3d430
void* GetB3d420();                                     // 0x00b3d420
void* GetB3d450();                                     // 0x00b3d450
NounManager_s0107_1a00* GetNounManager();                         // 0x00b3d300
Planet_s0107_1a00* GetActivePlanet_s0107_1a00();                             // 0x01021260
PlanetRecord_s0107_1a00* GetActivePlanetRecord_s0107_1a00();                 // 0x010212a0
PropertyHolder** GetPropertyHolder();                  // 0x01049a10
void SetWindowImageResource(UIWindow* w, const Key_s0107_1a00* res, int index);   // 0x00807cb0 (cdecl)
namespace SP {
class cSPUISpace_s0107_1a00 {
public:
    void UpdateTerraformingSlots();  // 0x01071d70 (SP::cSPUISpace::UpdateTerraformingSlots)
    void InitFoodwebInfo();                            // 0x01071a00
    void SetupFoodwebWindows(int arg);                 // 0x01071c20 (ret 4)
    void RefreshPosseItems();                          // 0x01072680
    void SetSlot(uint32_t id, bool locked, const Key_s0107_1a00* key, bool scanned, bool flagA, bool same);   // 0x01068d30 (ret 0x18)
    void SetSlotValue(int index, uint32_t value);         // 0x0106dd10 (ret 8)
    char pad[0x224];
    GlobalUI_s0107_1a00* mGlobalLayout;                           // +0x224
    char pad228[0x258 - 0x228];
    UILayout* mpLayout;                                // +0x258
    char pad25c[0x530 - 0x25c];
    FoodwebSlotVector mFoodwebSlots;                   // +0x530
    char pad53c[0x5c4 - 0x53c];
    Posse* mpPosse;                                    // +0x5c4
    char pad5c8[0x5d8 - 0x5c8];
    FlagVector mFlags;                                 // +0x5d8
    char pad5e0[0x620 - 0x5e0];
    WindowSet mWindowSet;                              // +0x620
};
}
// ---- items of slice s01071a00 end

// ---- items of slice s01079260 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_UIGlowScale;                   // 0x016e339c
extern uint8_t g_alloc_13ebb38[];      // 0x013ebb38 eastl allocator tag
extern char    g_str_Simulator[];      // 0x013f09b4 "Simulator"
extern char    g_fmt_013f01bc[];       // 0x013f01bc digit format string
extern uint8_t g_key_13f6b3c[];        // 0x013f6b3c heap tag for the dialog object
template<class T> const T& maxref(const T& a, const T& b)
{
    return a < b ? b : a;
}
struct Image { char pad[0x1c]; int width; int height; };                       // +0x1c / +0x20
struct RenderContext {
    uint Begin2D(int flags);                                                    // 0x0095bc10 (ret 4)
    void End2D();                                                               // 0x0095bb20
};
struct IObj_s0107_9260 {                                                                   // generic UI object
virtual void s0();
virtual void s1();
virtual void s2();
    virtual IObj_s0107_9260* Query(uint id);                                               // slot 3 (+0xc)
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
    virtual uint GetFlags();                                                    // slot 8 (+0x20)
virtual void s9();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
    virtual bool CheckFlag();                                                   // slot 16 (+0x40)
};
struct IWin {                                                                   // window (arg1)
virtual void s0();
virtual void s1();
virtual void s2();
    virtual IObj_s0107_9260* Query(uint id);                                               // slot 3 (+0xc)
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
virtual void s10();
virtual void s11();
    virtual uint Get30();                                                       // slot 12 (+0x30)
    virtual void s13();
    virtual const float* GetRect();                                             // slot 14 (+0x38)
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
virtual void s22();
virtual void s23();
virtual void s24();
virtual void s25();
virtual void s26();
virtual void s27();
virtual void s28();
virtual void s29();
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
    virtual uint GetA4();                                                       // slot 41 (+0xa4)
    virtual uint GetA8();                                                       // slot 42 (+0xa8)
virtual void s43();
virtual void s44();
    virtual IObj_s0107_9260* QueryB4(uint id);                                             // slot 45 (+0xb4)
};
struct Msg {                                                                    // message
    IObj_s0107_9260* src;                                                                  // +0
    int pad4;
    uint type;                                                                  // +8
    char pad[0xc];
    RenderContext* ctx;                                                         // +0x18
};
struct ImageSource {                                                            // secondary base at +0xc of Painter
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
    virtual Image* GetImage(int which);                                         // slot 4 (+0x10)
};
struct DrawParams { uint a; uint b; uint c; uint d; };
struct Painter {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
    virtual void Prepare(RenderContext* ctx, const float* rect, const DrawParams* p);   // slot 4 (+0x10)
    int pad4[2];
    ImageSource src;                                                            // +0xc
    float* A830c90(float* tmp, int n);                                          // 0x00830c90 ret 8
    float* A830cc0(float* tmp, int n);                                          // 0x00830cc0 ret 8
    uint   A830c80(int n);                                                      // 0x00830c80 ret 4
    Image* A830cf0(int n);                                                      // 0x00830cf0 ret 4
    float* A830d30(float* tmp, int n);                                          // 0x00830d30 ret 8
    float* A830d60(float* tmp, int n);                                          // 0x00830d60 ret 8
    uint   A830d10(int n);                                                      // 0x00830d10 ret 4
};
struct Item {
    float F1050a60();                                                           // 0x01050a60
    bool  F104feb0();                                                           // 0x0104feb0
    bool  F104ccf0();                                                           // 0x0104ccf0
    bool  F104ccd0();                                                           // 0x0104ccd0
    float F0ce6920();                                                           // 0x00ce6920 (fld [ecx+0x1a8])
};
struct Inventory {
    Item* F00ff3fb0(void* win);    // 0x00ff3fb0
};
struct Game {
    Inventory* GetPlayerInventory();    // 0x00a1ad60
};
struct Comm {
    bool F0ae9390();    // 0x00ae9390
};
struct Marker {
    void F106dcd0(uint id);    // 0x0106dcd0 ret 4
};
struct TSphere {
    bool F00c772c0(uint id);                                                    // 0x00c772c0 ret 4
    void F00c77bf0(uint id);                                                    // 0x00c77bf0 ret 4
};
struct NounMgr {
    TSphere* GetCurrentTerrainSphere();    // 0x00f67d90
};
Game*    SpaceGameGet_s0107_9260();                      // 0x01002bd0
Comm*    CommManager_s0107_9260();                       // 0x00b3d4a0
NounMgr* NounManager_s0107_9260();                       // 0x00b3d300
Marker*  F010666a0();                         // 0x010666a0 (cdecl, no args)
IObj_s0107_9260*    F01077b40(IObj_s0107_9260* src);                // 0x01077b40 (cdecl)
Painter* F0059ed00(uint v);                   // 0x0059ed00 (cdecl)
uint     GetRecorderState_s0107_9260();                  // 0x00435e90
void     KillSetiEffects(uint id, uint arg);  // 0x00435ed0
void     EA_Messaging_RemoveHandler(void* h, uint a, uint b, uint c, uint d);  // 0x00571db0
IObj_s0107_9260*    GetSystemAT_s0107_9260();                       // 0x00a206f0 (returns global)
int  __cdecl FUN_01077fb0(int dst, int src, int last);   // uninitialised move fwd
void __cdecl FUN_010779a0(int a, int b, int c);
void __cdecl FUN_01077f70(int a, int b, int c, int d);
void __cdecl FUN_01077f10(int a, int b, int c, int d, int e);
void __cdecl FUN_01078060(int a, int b, int c);
void __cdecl FUN_01078d30(int a, int b, int c);
void* __cdecl operator_new_eastl(uint size, const char* file, int line, int a,
                                 const char* allocator, int b);              // 0x00f473a0
void __cdecl operator_delete_eastl(int p);                                   // 0x00f47380
void*    __stdcall FUN_01077ae0(IWin* win);          // 0x01077ae0 (ret 4)
void     __cdecl FUN_010799d0(void* buf, const char* fmt, uint n);   // 0x010799d0
void*    __cdecl FUN_010666a0();                    // 0x010666a0
void*    __cdecl FUN_010666a0_s0107_9260();         // 0x010666a0 (same function; a second name keeps cl from inlining the same-TU definition into 0x0107a070)
struct UIGameCtx {
    char  pad000[0x254];
    void* mp254;                                    // +0x254
    void* F106edc0(void* win);                      // 0x0106edc0 (ret 4)
};
uint8_t  __cdecl FUN_00807c70(void* node, uint a, int idx, int b);  // 0x00807c70
uint8_t  __cdecl FUN_00806b20(void* node, int a, int b);            // 0x00806b20
struct ISpaceWin {
    char  pad00[0xc];
    void* mp0c;                                 // +0x0c
    char  pad10[0x14];
    int   mSel24;                               // +0x24
};
void F00805bb0(uint ctxToken, float a, float b, float c, float d, uint e, uint f,
               float g, float h, Image* img, float i);                          // 0x00805bb0 (cdecl, 11 args)
struct IRefObj_s0107_9260 {
    virtual void v00();
    virtual void v01();
    virtual void v02();
};
struct cSPUILayout_s0107_9260 {
    cSPUILayout_s0107_9260* Ctor();                                           // 0x00810000 (ret 0)
    bool Init(const void* key, uint a, uint b);                    // 0x008120d0 (ret 0xc)
    bool SetParentWin(IWin* parent, bool a, uint key);             // 0x008121b0 (ret 0xc)
};
struct INode {
    virtual void     v000();
    virtual void     v004();     // add-ref
    virtual void     v008();     // release
    virtual void     v00c();
    virtual void     v010();
    virtual void     v014();
    virtual void     v018();
    virtual void     v01c();
    virtual uint8_t  v020();     // "is enabled" predicate
    virtual void     v024();
    virtual void     v028();
    virtual void     v02c();
    virtual void     v030(void* out);
    virtual uint8_t  v034(void* a, void* b);
    virtual void     v038();
    virtual void     v03c();
    virtual void     v040();
    virtual void     v044();
    virtual void     v048();
    virtual void     v04c();
    virtual void     v050(void* a);
    virtual void     v054(uint a);
    virtual void     v058();
    virtual void     v05c(uint a);
    virtual void     v060();
    virtual void     v064();
    virtual void     v068();
    virtual void     v06c();
    virtual void     v070(float x, float y);
    virtual void     v074(float x, float y);
    virtual void     v078();
    virtual void     v07c(uint a, uint8_t b);
    virtual void     v080(void* text);
    virtual void     v084();
    virtual void     v088();
    virtual void     v08c();
    virtual void     v090();
    virtual void     v094();
    virtual void     v098();
    virtual void     v09c();
    virtual void     v0a0();
    virtual void     v0a4();
    virtual void     v0a8();
    virtual void     v0ac();
    virtual void     v0b0();
    virtual void     v0b4();
    virtual void     v0b8(uint a, void* b);
    virtual void     v0bc();
    virtual void     v0c0();
    virtual void     v0c4();
    virtual void     v0c8();
    virtual void     v0cc();
    virtual void     v0d0();
    virtual void     v0d4();
    virtual void     v0d8();
    virtual void     v0dc();
    virtual void     v0e0();
    virtual void     v0e4();
    virtual void     v0e8();
    virtual void     v0ec();
    virtual void*    v0f0(uint a, uint b);
    virtual void     v0f4();
    virtual void     v0f8();
    virtual void     v0fc();
    virtual void     v100();
    virtual void     v104(void* a);
};
struct UICell {
    void*   mNode;      // +0
    float   mPos;       // +4
    uint8_t mFlag;      // +8
};
struct AllocHeader { int mCookie; };
struct CellVec {
    UICell* begin;      // +0
    UICell* end;        // +4
    UICell* cap;        // +8
    void F10799f0(UICell* first, UICell* last);   // 0x010799f0 (ret 8)
    void F1079ff0(uint n);                        // 0x01079ff0 (ret 4)
    void F1079a60(UICell* pos, uint n, const UICell* val);  // 0x01079a60 (ret 0xc)
};
struct UISpace {
    char pad[0x24];
    IWin* mpCurrent;                          // +0x24
    char pad28[0x4];
    void* mp2c;                               // +0x2c
    CellVec mCells;                           // +0x30
    char pad3c[0x8];                          // +0x3c
    uint mKey44;                              // +0x44
    uint mKey48;                              // +0x48
    void* mp4c;                               // +0x4c
    uint mKey50;                              // +0x50
    uint mKey54;                              // +0x54
    void* mp58;                               // +0x58
    uint mKey5c;                              // +0x5c
    uint mKey60;                              // +0x60
    void* mp64;                               // +0x64
    uint mKey68;                              // +0x68
    uint mKey6c;                              // +0x6c
    void* mp70;                               // +0x70
    void* mp74;                               // +0x74  layout init key
    char pad78[0x8];                          // +0x78
    uint  mFlags80;                           // +0x80  layout kind
    char pad84[0x4];                          // +0x84
    int   mCols88;                            // +0x88
    int   mRows8c;                            // +0x8c
    uint  mSel90;                             // +0x90
    float mX94;                               // +0x94
    float mY98;                               // +0x98
    char  mFlag9c;                            // +0x9c
    char pad9d[0xb];                          // +0x9d
    uint  mKeyA8;                             // +0xa8
    char padac[0x8];                          // +0xac
    float mSpacingB4;                         // +0xb4
    float mSpacingB8;                         // +0xb8
    float mScaleBc;                           // +0xbc
    float mScaleC0;                           // +0xc0
    char padC4[0x24];                         // +0xc4
    char  mTeardownE8;                        // +0xe8
    char  mFlagE9;                            // +0xe9
    char padEa[0x2a];                         // +0xea
    void* mpHandler114;                       // +0x114
    uint  mHandler118;                        // +0x118
    uint  mHandler11c;                        // +0x11c
    uint  mHandler120;                        // +0x120
    uint  mHandler124;                        // +0x124
    void F1078ec0();                          // 0x01078ec0
    void F1078fa0();                          // 0x01078fa0
    void F1079040(uint index);                // 0x01079040 (ret 4)
    bool F1077900(IObj_s0107_9260* o);                   // 0x01077900 (ret 4)
    bool HandleMessage(IWin* win, Msg* msg);  // 0x01079260 (ret 8)
    bool F1077b70(uint a, uint* out);         // 0x01077b70 (ret 8)
    void F1079890(uint index);                // 0x01079890 (ret 4)
    void F1079f90();                          // 0x01079f90 (ret 0)
    INode* F1079d10(cSPUILayout_s0107_9260* parent, uint index);   // 0x01079d10 (ret 8)
    void   F107a070(ISpaceWin* win);          // 0x0107a070 (ret 4)
    void   F107a300();                        // 0x0107a300 (ret 0)
    void F1077d30();                          // 0x01077d30
    void F1077bf0(void* arg);                 // 0x01077bf0 (ret 4)
    void F1077e20();                          // 0x01077e20
};
struct WStr {
    wchar_t* mpBegin;       // +0x00
    wchar_t* mpEnd;         // +0x04
    wchar_t* mpCap;         // +0x08
    void*    mPad;          // +0x0c
    wchar_t* mpInline;      // +0x10
    wchar_t  mBuf[2];       // +0x14

    WStr()
    {
        mpInline = mBuf;
        mpEnd    = mBuf;
        mpBegin  = mpEnd;
        mpCap    = mpBegin + 1;
        mBuf[0]  = 0;
    }
};
// ---- items of slice s01079260 end

// ---- items of slice s01074bb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const wchar_t gEmptyStr[];        // 0x01667bac (2 chars)
struct IEffect {                         // EA::Swarm::cIVisualEffect (slots used here)
    virtual void v00();
    virtual void Release();              // 0x04
    virtual void Start(int flag);        // 0x08
    virtual void Stop(int flag);         // 0x0c
    virtual bool IsPlaying();            // 0x10
    virtual void v14();
    virtual void SetTransform(void* xf); // 0x18
};
struct EffectRef {                       // EA::AutoRefCount<cIVisualEffect>
    IEffect* p;
    IEffect** AsPPTypeParam();           // 0x00a16f40
    ~EffectRef() { if (p) p->Release(); }
};
struct EffectsMgr {
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
    virtual bool CreateEffect(uint id, int unused, IEffect** out);   // 0x2c
};
EffectsMgr* __cdecl EffectsManager();                                // 0x0067ddd0
struct XformMsg_s0107_4bb0 {                        // 0x38 bytes; ctor 0x00434040
    uint16_t flags;                      // |4 position, |2 matrix
    int16_t count;
    float pos[3];
    float scale;
    float mat[9];
    XformMsg_s0107_4bb0();
    void SetPosition(const float* v);    // 0x00571d40 (ret 4)
};
struct Matrix3_s0107_4bb0 { float m[9]; };
struct IWindow_s0107_4bb0 {
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
    virtual IWindow_s0107_4bb0* Get10();                                        // 0x10
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
virtual void s44();
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
virtual void s74();
virtual void s78();
    virtual void SetVisible(int a, int b);                           // 0x7c
virtual void s80();
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
virtual void sAC();
virtual void sB0();
virtual void sB4();
virtual void sB8();
virtual void sBC();
virtual void sC0();
virtual void sC4();
virtual void sC8();
virtual void sCC();
virtual void sD0();
virtual void sD4();
virtual void sD8();
    virtual void FDC(void* p);                                       // 0xdc
virtual void sE0();
virtual void sE4();
virtual void sE8();
virtual void sEC();
    virtual IWindow_s0107_4bb0* F0(uint id, int flag);                          // 0xf0
virtual void sF4();
virtual void sF8();
virtual void sFC();
virtual void s100();
virtual void s104();
    virtual void F108(void* p);                                      // 0x108
};
struct GlobalUI_s0107_4bb0 {
    IWindow_s0107_4bb0* FindWindowByID(uint id);    // 0x00e012b0 (ret 4)
};
struct cString_s0107_4bb0 {
    char d[0x14]; const wchar_t* GetText(int flags);    // 0x006b55c0 (ret 4)
    void Load(uint a, const wchar_t* b, int c);         // 0x006b54b0 (ret 0xc)
};
struct WString {                         // eastl::basic_string<wchar_t> (begin, end, capacity)
    const wchar_t* mpBegin; const wchar_t* mpEnd; const wchar_t* mpCapacity; uint mAllocator;
    void DeallocateSelf();               // 0x00933960
};
struct Obj288 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void va();
virtual void vb();
    virtual void On(uint a); };                                      // 0x30
struct Planet_s0107_4bb0 {
    bool SetSpeciesAsScanned(const Key3* k);    // 0x00c73ea0 (ret 4)
};
struct Species {
    void GetUiName(WString* out);    // 0x004da330 (ret 4)
};
struct Creature {
    Species* GetSpeciesProfile();                                    // 0x00c0bbd0
    Key3* GetKey();                                                  // 0x00c0bc00
};
Creature* __cdecl CreatureFromObject(void* o);                       // 0x00f19200
void* __cdecl ObjectFromKey(void* o);                                // 0x00c9f060
void* __cdecl IsCreatureOwned(Creature* c);                           // 0x00c0c380
struct Sel { virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
    virtual void* GetSelection(uint idx); };   // 0x1c
struct Sel2 {
    void* Resolve();    // 0x00bd6a60
};
struct Cfg { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void va();
virtual void vb();
    virtual int Query(uint id); };                                   // 0x30
Cfg* __cdecl ConfigManager_s0107_4bb0();                                        // 0x0067dd30
struct MsgSub { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void* GetObj();                      // 0x10
    virtual void v14();
    virtual uint* GetValuePtr(); };              // 0x18
struct Inv34 { virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
    virtual float* GetPosition();                                    // 0x2c
    virtual Matrix3_s0107_4bb0* GetOrientationQ(); };                           // 0x30 (quaternion ptr)
struct PlayerInv { char pad[0x34]; Inv34 sub; };
struct UFOSim {
    PlayerInv* GetPlayerInventory();    // 0x00a1ad60
};
UFOSim* __cdecl GetUFOSimulator_s0107_4bb0();                                   // 0x00ffbe50
Matrix3_s0107_4bb0* __cdecl Matrix3FromQuaternion(void* out, void* q);          // 0x0059c190
struct Empire {
    Key3* GetUFOKey();    // 0x00c326b0
};
Empire* __cdecl GetPlayerEmpire();                                   // 0x01021300
void* __cdecl GetActivePlanet_s0107_4bb0();                                     // 0x01021260
struct GameOwner {
    int GetMode();    // 0x00fe42a0
};
struct SpaceGame_s0107_4bb0 {
    GameOwner* GetOwner2();    // 0x00bfc5f0
};
SpaceGame_s0107_4bb0* __cdecl SpaceGameGet_s0107_4bb0();                                   // 0x01002bd0
bool __cdecl world(int n);                                           // 0x00685520
struct Gate {
    bool Check();    // 0x00b5ca60
};
Gate* __cdecl GetGate();                                             // 0x00b3d230
struct NameTable {
    uint Lookup(const char* name);    // 0x00ad7db0
};
NameTable* __cdecl GetNameTable();                                   // 0x00b3d4d0
struct Notifier {
    void Notify(int code, uint value);    // 0x00e19350 (ret 8)
};
Notifier* __cdecl GetNotifier();                                     // 0x00b3d3f0
struct StarMgr {
    void* Lookup(void* planet);    // 0x00ba6dc0 (ret 4)
};
StarMgr* __cdecl StarManager();                                      // 0x00b3d2a0
struct StarMap {
    void RemoveVisualGroup(uint group, int flag);                    // 0x01045b90 (ret 8)
    void CreatePlanetRecordVisual(void* star, uint group, uint fx, int a, int b); // 0x01045910 (ret 0x14)
};
StarMap* __cdecl GetStarMap();                                       // 0x01046fc0
int __cdecl GetRecorderState();                                      // 0x00435e90
void __cdecl KillSetiEffects(uint id, int state);                    // 0x00435ed0
extern uint g15b929c;                                                // 0x015b929c
extern uint g15b9294;                                                // 0x015b9294
struct UIGlobals { char pad[0x14]; uint f14; char pad2[0xc]; void* f24; };
extern UIGlobals* g16e0d08;                                          // 0x016e0d08
struct Obj22c {
    void* GetField();    // 0x00ff3f00 (reads +0x8c)
};
struct DispStrat {
    uint GetDisplayStrategy();    // 0x0104bfe0 (reads +0x240)
};
struct Win59c {
    void Refresh();    // 0x00e36620
};
struct UISpace_s0107_4bb0 {
    void F106b220(uint a);                                           // 0x0106b220
    void F1068f70();                                                 // 0x01068f70
    void F1067f60(int a);                                            // 0x01067f60
    void UpdateActivePlanetInfo();                                   // 0x0106a4e0
    void F106f120(void* m);                                          // 0x0106f120
    void F106a280();                                                 // 0x0106a280
    void F106aab0(bool b);                                           // 0x0106aab0
    void F106e5e0();                                                 // 0x0106e5e0
    void F106e630();                                                 // 0x0106e630
    void F106f160(void* m);                                          // 0x0106f160
    void F1071570();                                                 // 0x01071570
    void Init();                                                     // 0x01073700
    bool F1065e20();                                                 // 0x01065e20 (body below)
    void F1065e40();                                                 // 0x01065e40
    char pad[0x618]; uint mState618;
    void SetToolTip(void* subject, const wchar_t* title, const wchar_t* text, const Key3* key); // 0x01067c50
};
struct Layout_s0107_4bb0 {
    virtual void v00();
    virtual void v04();
    virtual void Release();                        // +0x08
    IWindow_s0107_4bb0* FindWindowByID(uint id, int flag);    // 0x008105b0 (ret 8)
};
struct LayoutHolder {
    Layout_s0107_4bb0* GetBuffer();    // 0x0093b6c0
};
struct SpaceGameData { char pad[0x14]; struct UIRoot* ui; };
struct UIRoot { char pad[0x224]; LayoutHolder* holder; };
void __cdecl SetWindowImage(IWindow_s0107_4bb0* w, const Key3* key, int idx);   // 0x00807bb0
__declspec(noinline) static void SetUFOImage(const Key3* key)
{
    Key3 k;
    k.a = key->a; k.b = key->b; k.c = key->c;
    k.b = 0x2f7d0004;
    Layout_s0107_4bb0* l = 0;
    SpaceGameData* sg = (SpaceGameData*)SpaceGameGet_s0107_4bb0();
    if (sg && sg->ui)
        l = sg->ui->holder->GetBuffer();
    IWindow_s0107_4bb0* w = l->FindWindowByID(0xb0b00000, 1);
    SetWindowImage(w, &k, -1);
}
struct UIHandler {
    char p0[0x218];
    GlobalUI_s0107_4bb0* mGlobalUI;            // +0x218
    char p1[0x22c - 0x21c];
    Obj22c* m22c;                   // +0x22c
    char p2[0x288 - 0x230];
    Obj288* m288;                   // +0x288
    char p3[0x2f8 - 0x28c];
    EffectRef mEffect;              // +0x2f8
    char p4[0x310 - 0x2fc];
    char* mOwner;                   // +0x310
    uint mLastKey;                  // +0x314
    char p5[0x458 - 0x318];
    cString_s0107_4bb0 mText458;               // +0x458
    cString_s0107_4bb0 mText46c;               // +0x46c
    char p7[0x494 - 0x46c - 0x14];
    cString_s0107_4bb0 mText494;               // +0x494
    char p8[0x59c - 0x494 - 0x14];
    Win59c* m59c;                   // +0x59c
    char p9[0x60c - 0x5a0];
    uint mBadgeState;               // +0x60c

    UISpace_s0107_4bb0* Outer() { return (UISpace_s0107_4bb0*)((char*)this - 0xc); }
    bool HandleMessage(uint msgID, void* msg);
};
// ---- items of slice s01074bb0 end

// ---- items of slice s010727e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void     RecordEvent2(uint32_t id, uint32_t state);  // 0x00435ed0, cdecl, 2 args
void*    WindowManager_s0107_27e0();                            // 0x0067caa0, cdecl, no args
void*    interface_cast_IWinButton(void* window);    // 0x005ca960, cdecl, 1 arg
uint32_t convertStarMapButtonToFilter(uint32_t id);  // 0x010659c0, cdecl, 1 arg
void     FUN_00e02c40();                             // 0x00e02c40, cdecl, no args
void*    FUN_01015df0();                             // 0x01015df0, cdecl, no args
void*    AutoRefCount_Ctor(void* pObject);           // 0x00572660, cdecl, 1 arg; returns the slot
void     ShowContextSensitiveSporeGuide();           // 0x00e02200, cdecl, no args (param unused)
void*    SpaceGameGet_s0107_27e0();                             // 0x01002bd0, cdecl, no args
uint8_t  FUN_00b18e40(void* ecx);                    // 0x00b18e40, thiscall, no args
void*    GetUFOSimulator_s0107_27e0();                          // 0x00ffbe50, cdecl, no args
uint8_t  FUN_00ffc0c0(void* ecx);                    // 0x00ffc0c0, thiscall, no args
void*    FUN_01021240_s0107_27e0();                             // 0x01021240, cdecl, no args
void*    GetPlayerEmpire_s0107_27e0();                          // 0x01021300, cdecl, no args
void*    GameInputManager();                         // 0x00b3d250, cdecl, no args
void*    GetGameTerrainCursor();                     // 0x00b30d70, cdecl, no args
void*    GameTimeManager_s0107_27e0();                          // 0x00b3d380, cdecl, no args
void*    GetResourceManager();                       // 0x0067dcd0, cdecl, no args
void*    GetUpdater490();                            // 0x00b3d490, cdecl, no args
void*    GetSpeciesManager_s0107_27e0();                        // 0x00401090, cdecl, no args
void*    FUN_00b3d3f0_s0107_27e0();                             // 0x00b3d3f0, cdecl, no args
void*    GetGlobalImageKey(void* empire, void* arg); // 0x00dd1ca0, cdecl, 2 args, ignores them
uint32_t ColorRGBToU32(void* color);                 // 0x00458a40, cdecl, 1 arg
uint8_t  FUN_00eed840(const void* key);              // 0x00eed840, cdecl, 1 arg
uint8_t  FUN_00eed970(const void* a, const void* b); // 0x00eed970, cdecl, 2 args
uint8_t  FUN_004eb930(void* out, void* in);          // 0x004eb930, cdecl, 2 args
void     ForwardWindowMessage_7590(uint32_t a, uint32_t b);  // 0x00fe7590, cdecl, 2 args
namespace SP {
struct Vec3i { uint32_t mX, mY, mZ; };
}
namespace SP {
struct IWindow_s0107_27e0 {
    uint32_t v00();
    uint32_t v04();
    uint32_t v08();
    uint32_t v0c();
    uint32_t v10();
    uint32_t v14();
    uint32_t v18();
    uint32_t v1c();                                  // +0x1c  command id
    uint32_t v20();                                  // +0x20  flags
    uint32_t v24();                                  // +0x24
    uint32_t v28(uint32_t a, uint32_t b);            // +0x28  state setter
uint32_t v2c();
uint32_t v30();
uint32_t v34();
    uint32_t v38();                                  // +0x38  area rect getter
uint32_t v3c();
uint32_t v40();
uint32_t v44();
uint32_t v48();
uint32_t v4c();
uint32_t v50();
uint32_t v54();
uint32_t v58();
uint32_t v5c();
uint32_t v60();
uint32_t v64();
uint32_t v68();
    uint32_t v6c(const void* area);                  // +0x6c  set area
uint32_t v70();
uint32_t v74();
uint32_t v78();
    uint32_t v7c(uint32_t a, uint32_t b);            // +0x7c  show / flag
    uint32_t v80(const void* text);                  // +0x80  set text
uint32_t v84();
uint32_t v88();
uint32_t v8c();
uint32_t v90();
uint32_t v94();
uint32_t v98();
uint32_t v9c();
uint32_t va0();
uint32_t va4();
uint32_t va8();
uint32_t vac(uint32_t color);
};
}
namespace SP {
struct cSPUIGlobalUI_s0107_27e0 {
    IWindow_s0107_27e0* FindWindowByID(uint32_t id);            // 0x00e012b0, thiscall, 1 arg
};
}
namespace SP {
struct cSPUILayout {
    IWindow_s0107_27e0* FindWindowByID(uint32_t id, int recurse);     // 0x008105b0, thiscall, 2 args
    void     SetParentWin(void* child, int a, uint32_t id);  // 0x008121b0, thiscall, 3 args
};
}
namespace SP {
struct cStarMap {
    void FilterHelper(uint32_t filter, uint32_t on);       // 0x01048b40, thiscall, 2 args
};
}
namespace SP {
struct cFloatOwner {
    void FUN_01015f30(float value);                        // 0x01015f30, thiscall, 1 arg, ret 4
};
}
namespace SP {
struct cCommandDeleteCargoButtonState {
    void* Ctor(void* owner, uint32_t window);              // 0x010665c0, thiscall, 2 args
uint32_t v00();
uint32_t v04();
    uint32_t v08(uint32_t flag);                           // +0x08
};
}
namespace SP {
struct cOverlay {
    void    SetMode(int mode);                             // 0x00fe76d0, thiscall, 1 arg
    uint8_t Test();                                        // 0x00ffc0c0, thiscall, no args
    void    Show();                                        // 0x00fe7e10, thiscall, no args
    void    Hide(int on);                                  // 0x00fe7280, thiscall, 1 arg
};
}
namespace SP {
void FUN_00812d80(void* ecx, int on);                      // 0x00812d80, thiscall, 1 arg
}
namespace SP {
struct cTerraform {
    void* GetOld (void* out);                              // 0x00bbc4f0, thiscall, 1 arg; returns out
    void* GetNew (void* out);                              // 0x00bbc510, thiscall, 1 arg; returns out
    void  StoreEmpty();                                    // 0x00bbc4a0, thiscall, no args
    void  Store3(int x, int y, int z);                     // 0x00bbc410, thiscall, 3 args
    void  Store3B(int x, int y, int z);                    // 0x00bbc460, thiscall, 3 args
};
}
namespace SP {
void* TerraformingManager_s0107_27e0();                               // 0x00b3d430, cdecl, no args
}
namespace SP {
struct cStarAccess {
    uint32_t GetState();                                   // 0x00b8d9b0, thiscall, no args
};
}
namespace SP {
struct cInvSub {
    uint8_t      pad00[0x13c];
    cStarAccess* mpStar;                                   // +0x13c
};
}
namespace SP {
struct cInventory {
    uint8_t  pad00[0x75c];
    cInvSub* mp75c;                                        // +0x75c
};
}
namespace SP {
struct cSimulator {
    cInventory* GetPlayerInventory();                      // 0x00a1ad60, thiscall, no args
};
}
namespace SP {
struct cCommContext {
    uint32_t GetCommContext();                             // 0x00ce6950, thiscall, no args
};
}
namespace SP {
struct cStarManagerAccess {
    void* GetEmpireByID(uint32_t id);                      // 0x00ba9370, thiscall, 1 arg
};
}
namespace SP {
void* StarManager_s0107_27e0();                                       // 0x00b3d2a0, cdecl, no args
}
namespace SP {
void  CommAdd(uint32_t empire, uint32_t ctx,
              uint32_t a, uint32_t b, int c, int d);       // 0x00aeb720, thiscall, 6 args
}
namespace SP {
void  CommRemove(uint32_t empire, uint32_t ctx,
                 uint32_t a, uint32_t b);                  // 0x00aeaa80, thiscall, 4 args
}
namespace SP {
uint8_t FUN_00b8d970(void* ecx);                           // 0x00b8d970, thiscall, no args
}
namespace SP {
uint32_t FUN_00b8dab0(void* ecx);                          // 0x00b8dab0, thiscall, no args
}
namespace SP {
struct cInputMgr {
    uint8_t  pad00[0x110];
    uint32_t mCounter;                                     // +0x110
};
}
namespace SP {
struct cEmpire_s0107_27e0 {
    Vec3i* GetIds();                                       // 0x00c30f90, thiscall, no args
    void*  GetColor(void* out);                            // 0x00c32cd0, thiscall, 1 arg; returns out
    uint8_t pad00[0x84];
    uint32_t mId;                                          // +0x84
};
}
namespace SP {
struct cSpeciesMgr_s0107_27e0 {
    void* GetProfile(const Vec3i* key);                    // 0x004df550, thiscall, 1 arg
};
}
namespace SP {
struct cImageKey {
    IWindow_s0107_27e0* FUN_00dd2320(void* empire, void* arg);        // 0x00dd2320, thiscall, 2 args
};
}
namespace SP {
struct cAsset {
    uint32_t       v00();                                  // +0x00
    const wchar_t* GetName();                              // 0x00414e10, thiscall, no args
    const wchar_t* GetSummary();                           // 0x005508c0, thiscall, no args
};
}
namespace SP {
struct cString_s0107_27e0 {
    uint32_t m00, m04, m08, m0c;
    uint8_t  m10, m11, mPad[2];
    cString_s0107_27e0(uint32_t a, uint32_t b, const wchar_t* c);     // 0x006b5770
    ~cString_s0107_27e0();                                            // 0x006b5240
    void* GetText();                                       // 0x006b55c0
};
}
namespace SP {
struct cUpdater {
    void BindSlotCreature(void* ids, uint32_t a, const float* rgb,
                          int b, int c, void* win);        // 0x00ae8d00, thiscall, 6 args
    void SwapSlotObjects(int a, int b, int c, int d);      // 0x00ae7e10, thiscall, 4 args
};
}
namespace SP {
extern uint32_t DAT_015b90d8;                              // 0x015b90d8
}
namespace SP {
extern uint32_t DAT_015b9108_s0107_27e0;                              // 0x015b9108
}
namespace SP {
extern uint8_t  DAT_013ec468;                              // 0x013ec468
}
namespace SP {
extern const float kHalf;                                  // 0x01471064
}
namespace SP {
extern const float kOne_s0107_27e0;                                   // 0x01485720
}
namespace SP {
class cSPUISpace_s0107_27e0 {
public:
    uint8_t        pad00[0x10];
    void*          mpCommandDeleteCargoButtonState;        // +0x10
    uint32_t       mDeleteButtonWindow;                    // +0x14
    uint8_t        pad18[0x224 - 0x18];
    cSPUIGlobalUI_s0107_27e0* mpGlobalUI;                             // +0x224
    uint8_t        pad228[0x258 - 0x228];
    cSPUILayout*   mpLayout;                               // +0x258
    uint8_t        pad25c[0x5d0 - 0x25c];
    uint8_t        mb5d0;                                  // +0x5d0
    uint8_t        pad5d1[0x694 - 0x5d1];
    cOverlay*      mpOverlay;                              // +0x694

    // helpers (each keeps its original VA annotation for the difftest resolver)
    bool     DoFocusChange(void* target, const void* msg);   // 0x0106fc90
    void     FUN_01066780(void* target, const void* msg);    // 0x01066780
    bool     FUN_01065e20();                                 // 0x01065e20
    uint32_t FUN_01067b60();                                 // 0x01067b60
    void     FUN_010666b0();                                 // 0x010666b0
    void*    FUN_01067ef0(uint32_t arg);                     // 0x01067ef0
    void     FUN_0106f1a0(void* blk, char mode);             // 0x0106f1a0
    uint8_t  FUN_01067fb0();                                 // 0x01067fb0  ToggleSlotsUI
    uint8_t  FUN_01066570();                                 // 0x01066570
    uint8_t  FUN_01068080();                                 // 0x01068080  ToggleMinimapUI
    uint8_t  FUN_01068140();                                 // 0x01068140  UpdateStarMapFilters
    uint8_t  FUN_01068350();                                 // 0x01068350
    uint32_t FUN_01066150(uint32_t id);                      // 0x01066150
    void     FUN_0106e3e0(uint32_t index);                   // 0x0106e3e0  ToggleToolUI
    void     FUN_0106e940(uint32_t index);                   // 0x0106e940
    void     FUN_0106ea40(uint32_t index);                   // 0x0106ea40
    void     FUN_0106f3d0();                                 // 0x0106f3d0
    void     FUN_0106f540();                                 // 0x0106f540
    void     FUN_01066230(int on);                           // 0x01066230
    void     FUN_01071c20(uint32_t state);                   // 0x01071c20  SetupFoodwebWindows

    bool DoMessage(void* target, uint32_t* msg);             // 0x01072d40, ret 8
    void ShowCreatureTooltip(void* arg1, uint32_t arg2);     // 0x010727e0, ret 8
};
}
using SP::cSPUISpace_s0107_27e0;
using SP::IWindow_s0107_27e0;
using SP::Vec3i;
// ---- items of slice s010727e0 end

// ---- items of slice s01078120 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t g_LayoutPropIDs[5];                                  // 0x0149c5e8
extern uint32_t g_MessageIDs[1];                                     // 0x0149c614
struct ResourceKey {
    uint32_t instanceID, typeID, groupID;
    ResourceKey() {}
    ResourceKey(uint32_t i, uint32_t t, uint32_t g) : instanceID(i), typeID(t), groupID(g) {}
};
namespace Math {
 struct Rectangle_s0107_8120 { float x1, y1, x2, y2; Rectangle_s0107_8120(const Rectangle_s0107_8120& o) : x1(o.x1), y1(o.y1), x2(o.x2), y2(o.y2) {} }; 
}
struct Property_s0107_8120 {
    uint16_t pad[9];
    uint16_t mnType;                                  // +0x12 (1 bool, 10 uint, 13 float)
    bool* GetBool();                                  // 0x0041e920
    uint32_t* GetUInt();                              // 0x0041ea00
    float* GetFloat();                                // 0x0041ea70
};
struct PropertyList {
    virtual int AddRef();
    virtual int Release();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
    virtual bool GetProperty(uint32_t propertyID, Property_s0107_8120*& result);   // +0x24
};
struct PropertyManager {
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
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyList** ppDst);   // +0x2c
};
PropertyManager* PropertyManager_Get();               // 0x0067de30
bool GetPropertyAsKeyInstance(PropertyList* list, uint32_t id, uint32_t* out);   // 0x006a12a0
inline bool GetUIntProp(PropertyList* list, uint32_t id, uint32_t& out)
{
    Property_s0107_8120* p;
    if (list && list->GetProperty(id, p) && p->mnType == 10) { out = *p->GetUInt(); return true; }
    return false;
}
inline bool GetFloatProp(PropertyList* list, uint32_t id, float& out)
{
    Property_s0107_8120* p;
    if (list && list->GetProperty(id, p) && p->mnType == 13) { out = *p->GetFloat(); return true; }
    return false;
}
inline bool GetBoolProp(PropertyList* list, uint32_t id, bool& out)
{
    Property_s0107_8120* p;
    if (list && list->GetProperty(id, p) && p->mnType == 1) { out = *p->GetBool(); return true; }
    return false;
}
template <class T> struct AutoRef_s0107_8120 {
    T* mpObject;
    AutoRef_s0107_8120() : mpObject(0) {}
    ~AutoRef_s0107_8120() { if (mpObject) mpObject->Release(); }
    T* get() const { return mpObject; }
    // Drops the reference and hands out the slot (T** out-parameter idiom).
    T** AsOutParam()
    {
        if (mpObject) { T* pOld = mpObject; mpObject = 0; pOld->Release(); }
        return &mpObject;
    }
    __forceinline AutoRef_s0107_8120& operator=(T* p)
    {
        T* const pTemp = mpObject;
        if (p != pTemp) {
            if (p) p->AddRef();
            mpObject = p;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
};
struct IWinProc { virtual int AddRef(); virtual int Release(); };
struct IWindow_s0107_8120 {
    virtual int AddRef();                                            // +0x00
    virtual int Release();                                           // +0x04
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
    virtual const Math::Rectangle_s0107_8120& GetRealArea();                    // +0x38
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
    virtual void SetPosition(float x, float y);                      // +0x70
    virtual void SetSize(float w, float h);                          // +0x74
    virtual void v78();
    virtual void SetFlag(int flag, bool value);                      // +0x7c
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
virtual void vc4();
virtual void vc8();
virtual void vcc();
virtual void vd0();
virtual void vd4();
virtual void vd8();
virtual void vdc();
    virtual void RemoveWindow(IWindow_s0107_8120* child);                       // +0xe0
virtual void ve4();
virtual void ve8();
virtual void vec();
    virtual IWindow_s0107_8120* FindWindowByID(uint32_t id, bool recursive);    // +0xf0
virtual void vf4();
virtual void vf8();
virtual void vfc();
virtual void v100();
    virtual void AddWinProc(IWinProc* pProc);                        // +0x104
    virtual void RemoveWinProc(IWinProc* pProc);                     // +0x108
};
typedef IWindow_s0107_8120 IWinText_s0107_8120;
IWinText_s0107_8120* __cdecl CreateTextWindow(IWinText_s0107_8120* src);                   // 0x00806370
struct IWinTextRef {
    IWinText_s0107_8120* mpObject;
    IWinTextRef& operator=(IWinText_s0107_8120* p);                             // 0x00b5f950
    void Clear()
    {
        IWinText_s0107_8120* pOld = mpObject;
        if (pOld) { mpObject = 0; pOld->Release(); }
    }
};
class cSPUILayout_s0107_8120 { public:
    char pad[0x18];
    cSPUILayout_s0107_8120();                                                   // 0x00810000
    ~cSPUILayout_s0107_8120();                                                  // 0x00811fe0
    bool Init(const ResourceKey* key, int visible, uint32_t parentID);   // 0x008120d0
    IWindow_s0107_8120* FindWindowByID(uint32_t id, int recursive);             // 0x008105b0
};
struct IMessageServer;
void __cdecl RemoveHandler(void* server, uint32_t a, uint32_t b, uint32_t c, uint32_t d);   // 0x00571db0 (EA::Messaging::RemoveHandler)
struct Connector {
    void* mpServer; uint32_t a, b, c, d;
    void Init(IMessageServer* server, void* handler, const uint32_t* messageIDs, int count);   // 0x004db620
};
struct Stopwatch {
    uint32_t a, b, c, d;
    void SetUnits(int units);                                        // 0x0093a1a0
    void Reset(int units) { a = 0; b = 0; c = 0; d = 0; SetUnits(units); }
};
class cSPPropLayoutPanel : public IWinProc {
public:
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
    virtual void OnShow24();                                         // +0x24
    virtual void OnShow28();                                         // +0x28
    uint32_t pad04[2];                                               // +0x04
    void* mHandler;                                                  // +0x0c (second vptr: message handler base)
    ResourceKey mLayoutKey;                                          // +0x10
    cSPUILayout_s0107_8120* mpLayout;                                           // +0x1c
    AutoRef_s0107_8120<PropertyList> mPropList;                                 // +0x20
    AutoRef_s0107_8120<IWindow_s0107_8120> mWindow;                                        // +0x24
    IWinTextRef mText;                                               // +0x28
    IWinTextRef mTextClone;                                          // +0x2c
    uint32_t pad30[(0x44 - 0x30) / 4];
    ResourceKey mLayoutKeys[5];                                      // +0x44
    uint32_t m80;                                                    // +0x80
    float m84;                                                       // +0x84
    uint32_t mCols;                                                  // +0x88
    uint32_t mRows;                                                  // +0x8c
    uint32_t m90;                                                    // +0x90
    float mPadX;                                                     // +0x94
    float mPadY;                                                     // +0x98
    bool mFlag9c;                                                    // +0x9c
    uint32_t mMode;                                                  // +0xa0
    uint32_t ma4, ma8, mac, mb0;                                     // +0xa4..+0xb0
    float mLayoutW, mLayoutH;                                        // +0xb4, +0xb8
    float mScaledW, mScaledH;                                        // +0xbc, +0xc0
    uint32_t pad_c4;
    Stopwatch mStopwatch;                                            // +0xc8
    uint32_t pad_d8[(0xe0 - 0xd8) / 4];
    float mE0, mE4;                                                  // +0xe0, +0xe4
    bool mFlagE8;                                                    // +0xe8
    bool mFlagE9;                                                    // +0xe9
    uint8_t pad_ea[0x100 - 0xea];
    Connector mConnector;                                            // +0x100

    IWindow_s0107_8120* FUN_01077ae0(cSPUILayout_s0107_8120* layout);                      // 0x01077ae0
    bool Init();
};
// ---- items of slice s01078120 end

// ---- items of slice s0106cab0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(_ReadWriteBarrier)
typedef unsigned int uint32;
namespace eastl {
struct hash_node_s0106_cab0 {
    uint32 mKey;                              // +0x00
    void*  mpValue;                           // +0x04
    hash_node_s0106_cab0* mpNext;                        // +0x08
};
}
namespace eastl {
struct hashtable_iterator {
    hash_node_s0106_cab0*  mpNode;                       // +0x00
    hash_node_s0106_cab0** mpBucket;                     // +0x04
};
}
namespace eastl {
struct hashtable_range {
    hashtable_iterator first;                 // +0x00
    hashtable_iterator second;                // +0x08
};
}
struct IReleasable {
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
    virtual void Release();                   // +0x2c
};
struct Hashtable_s0106_cab0 {
    uint32                          mUnknown00;   // +0x00
    eastl::hash_node_s0106_cab0**              mpBucketArray;  // +0x04
    uint32                          mnBucketCount;  // +0x08
    void equal_range(eastl::hashtable_range* out, const uint32& key);   // 0x009a6dd0
};
struct Win_s0106_cab0 {
virtual void w00();
virtual void w04();
virtual void w08();
virtual void w0c();
virtual void w10();
virtual void w14();
virtual void w18();
virtual void w1c();
virtual void w20();
virtual void w24();
virtual void w28();
virtual void w2c();
virtual void w30();
virtual void w34();
virtual void w38();
virtual void w3c();
virtual void w40();
virtual void w44();
virtual void w48();
virtual void w4c();
virtual void w50();
virtual void w54();
virtual void w58();
virtual void w5c();
virtual void w60();
virtual void w64();
virtual void w68();
virtual void w6c();
virtual void w70();
virtual void w74();
virtual void w78();
    virtual void SetVisible(int a, bool b);   // +0x7c
};
struct cSPUIGlobalUI_s0106_cab0 {
    Win_s0106_cab0* FindWindowByID(uint32 id);           // 0x00e012b0
};
namespace SP {
struct cSPUISpaceCursor {
    char pad00[0x94];
    bool IsActive();                          // 0x00ff3ce0
};
}
namespace SP {
class cSPUISpace_s0106_cab0 {
public:
    char            pad000[0x224];
    cSPUIGlobalUI_s0106_cab0*  mpGlobalUI;               // +0x224
    char            pad228[0x238 - 0x228];
    cSPUISpaceCursor* mpCursor;               // +0x238
    uint32          mCursorKey;               // +0x23c
    char            pad240[0x25c - 0x240];
    Hashtable_s0106_cab0       mCursorTable;             // +0x25c
    char            pad268[0x298 - 0x268];
    IReleasable*    mpRollover298;            // +0x298
    IReleasable*    mpRollover29c;            // +0x29c

    void FUN_0106cab0();
};
}
// ---- items of slice s0106cab0 end

// @ 0x00433b30
void FadeController::Update(float dt)
{
    if (playing) {
        bool wasExpired = (time > duration && fadingOut) ? 1 : 0;
        time = time + dt;

        if (!fadingOut) {
            float v = time;
            if (time > duration) {
                if (loopMode == 1) {
                    time = time - duration;
                    v = time;
                    if (effect) {
                        XformMsg src(owner->GetSource());
                        XformMsg msg;
                        msg.SetScale(src.scale);
                        msg.SetPos(src.pos);
                        msg.SetRot(src.rot);
                        handle.assign(GetFactory(effect, 0, &msg, this)->Create());
                    }
                } else {
                    v = duration;
                    Stop();
                }
            }
            Mixer* m = owner->mixer;
            uint32_t k = owner->key;
            m->SetValue(k, id, v, 0);
            owner->Refresh();
            if (handle.get() && handle->IsPlaying()) {
                XformMsg src(owner->GetSource());
                XformMsg msg;
                msg.SetScale(src.scale);
                msg.SetPos(src.pos);
                msg.SetRot(src.rot);
                handle->SetXform(&msg);
            }
        } else {
            if (time > fadeTime) {
                time = fadeTime;
                playing = 0;
            }
            if (time > kZero) {
                Mixer* m = owner->mixer;
                uint32_t k = owner->key;
                m->SetFade(k, id, kOne - time / fadeTime, 0);
            }
            if (!playing) FinishFade();
        }
    }
}

// @ 0x00434040
XformMsg::XformMsg()
: flags(0), count(0), pos(g_DefaultPos), scale(kOne), rot(g_IdentityMatrix)
{
    PadN<11>();   // unused locals present in the original frame
}

// @ 0x00435e90
int GetRecorderState()
{
    Recorder* rec = GetRecorder();
    int result;
    if (rec)
        result = rec->GetState();
    else
        result = 0;
    return result;
}

// @ 0x00435ed0
void RecordEvent2(uint32_t a, uint32_t b)
{
    Recorder* r = GetRecorder();
    if (r) {
        r->Begin(0x3475365);
        r->WriteInt(0x3475381, a);
        r->WriteInt(0x3475385, b);
        r->End();
    }
}

// @ 0x007f5eb0
namespace EA {
namespace UTFWin {
namespace Color {
unsigned int Lerp(unsigned int c1, unsigned int c2, float t)
{
    uint32_t a1 = c1 >> 0x18;
    uint32_t r1 = (c1 >> 0x10) & 0xff;
    uint32_t g1 = (c1 >> 8) & 0xff;
    uint32_t b1 = c1 & 0xff;
    uint32_t res;
    res = (uint32_t)(int)((float)(int)((c2 >> 0x10 & 0xff) - r1) * t + (float)(int)r1) & 0xff;
    res |= ((uint32_t)(int)((float)(int)((c2 >> 0x18) - a1) * t + (float)(int)a1) & 0xff) << 8;
    res = (res << 8) |
          ((uint32_t)(int)((float)(int)((c2 >> 8 & 0xff) - g1) * t + (float)(int)g1) & 0xff);
    res = (res << 8) |
          ((uint32_t)(int)((float)(int)((c2 & 0xff) - b1) * t + (float)(int)b1) & 0xff);
    return res;
}
}
}
}  // namespace EA::UTFWin::Color

// @ 0x00b188b0
u8 KindIsActive(IObj* o)
{
  switch (o->GetKind()) {
    case 0xe9cb8ba:
    case 0x116d858:
    case 0xee02c7:
    case 0x1a55e4d:
    case 0x436f315:
    case 0x1007ae63:
    case 0xecade42:
    case 0xff10521: {
      cTraitHolder* t = (cTraitHolder*)o->Query((unsigned)gTraitKey);
      return (t->Value() <= 0.0f) ? 1 : 0;
    }
    case 0xd0036e08:
    case 0x4f176642: {
      char* q = (char*)o->Query(0xce9f6639);
      return q[0xb5e];
    }
  }
  return 0;
}

// @ 0x00b189c0
bool __stdcall KeyDownHandler(int key, int mod)
{
  cLayoutMgr* lm = GetLayoutManager();
  if (lm->IsWorldVisible(0x614de4c))
    return true;
  u8 flag28 = GetB3d320()->mFlag28;
  if (flag28)
    return true;
  bool handled;
  switch (GetCurrentGameMode()) {
    case 0x1654c01:
      handled = cCreatureModeStrategy::Instance()->F();
      break;
    case 0x1654c02:
      handled = cTribeModeStrategy::Instance()->F();
      break;
    case 0x1654c04:
      handled = cCivModeStrategy::Get()->F();
      break;
    case 0x1654c05:
      handled = GetB3d410()->F();
      break;
    case 0x1654c10:
      handled = ((cAppG*)SP::gApp)->G();
      break;
    default:
      goto after_modes;
  }
  if (handled)
    return true;
after_modes:
  if (key != 0x1b) {
    if (mod != 0)
      goto L_modnz;
    if ((key == 0x48 || key == 0xbf || key == 0x54 || key == 0x42 || key == 0x50 || key == 0x43 ||
         key == 0x4c) &&
        (FUN_00dd1230() || FUN_00e09540()))
      return true;
    if (key != 0x48 && key != 0xbf)
      goto L_27;
    goto L_c6;
  }
  if (mod == 0)
    return false;
L_modnz:
  if (mod == 1) {
    if (key != 0xbf)
      return false;
    goto L_c6;
  }
  goto L_after;
L_c6:
  if (GetCurrentGameMode() != 0x1654c00) {
    if (!SporeGuide()->mFlag) {
      MessageServer()->Post5(0x5120263, 0, 0);
      return true;
    }
    MessageServer()->Post5(0x5b9ba6c, 0, 0);
    return true;
  }
L_after:
  if (mod == 2) {
    if (key != 0x53) {
      if (key != 0x48)
        return false;
      if (GetCurrentGameMode() == 0x1654c00)
        return false;
      void* w = WindowManager_s00b1_81d0()->Get4();
      cWinObj* wo = w ? (cWinObj*)((char*)w - 4) : 0;
      wo->Set(!wo->Test());
      return false;
    }
    if (GetCurrentGameMode() == 0x1654c00)
      return false;
    if (GetCurrentGameMode() == 0x1654c10)
      return false;
    if (AssetBrowser()->mFlag)
      return false;
    if (GetB3d410()->G())
      return false;
    if (GetB3d4d0()->F())
      return false;
    if (FUN_00b2f740())
      return false;
    if (GetCurrentGameMode() == 0x1654c02) {
      if (cTribeModeStrategy::Instance()->G())
        return false;
    }
    MessageServer()->Post6(0x1cd20f0, 0, 0, 0);
    return true;
  }
  if (mod != 0)
    return false;
L_27:
  if (key == 0x42) {
    if (GetCurrentGameMode() != 0x1654c00) {
      if (!AssetBrowser()->mFlag) {
        MessageServer()->Post5(0x5120264, 0, 0);
        return true;
      }
      MessageServer()->Post5(0x574f0a6, 0, 0);
      return true;
    }
  } else if (key == 0x54) {
    if (WindowManager_s00b1_81d0()->Get84() == 0) {
      if (!GetB3d4d0()->F() &&
          (GetCurrentGameMode() != 0x1654c04 || !cCivModeStrategy::Get()->mFlag148)) {
        if (GetCurrentGameMode() == 0x1654c02) {
          if (cTribeModeStrategy::Instance()->G())
            return true;
        }
        if (GetCurrentGameMode() == 0x1654c05) {
          if (GetC10666a0()->F())
            return true;
        }
        MessageServer()->Post5(0x5120262, 0, 0);
      }
    }
    return true;
  }
  return false;
}

// @ 0x00b20ee0
ByteString* __stdcall UpdateDebugUI(ByteString* out, unsigned kind)
{
    extern char gEmptyChar;
    out->mpBegin = &gEmptyChar;
    out->mpEnd = &gEmptyChar;
    out->mpCapacity = &gEmptyChar + 1;
    switch (kind) {
    case 0: out->Assign("none"); break;
    case 1: out->Assign("creature"); break;
    case 2: out->Assign("tribe"); break;
    case 3: out->Assign("city"); break;
    case 4: out->Assign("civilization"); break;
    case 5: out->Assign("empire"); break;
    default: out->Assign("unknown", "unknown" + 7); break;
    }
    return out;
}

// @ 0x00bbc410
void KeySink::Store3(int a, int b, int c)
{
    char* s = (char*)this;
    *(int*)(s + 0x7c) = a;
    *(int*)(s + 0x80) = b;
    *(int*)(s + 0x84) = c;
    *(int*)(s + 0x88) = g_dw168a488;
    *(int*)(s + 0x8c) = g_dw168a48c;
    *(int*)(s + 0x90) = g_dw168a490;
}

// @ 0x00bbc460
void KeySink::Store3B(int a, int b, int c)
{
    char* s = (char*)this;
    *(int*)(s + 0x7c) = g_dw168a488;
    *(int*)(s + 0x80) = g_dw168a48c;
    *(int*)(s + 0x88) = a;
    *(int*)(s + 0x84) = g_dw168a490;
    *(int*)(s + 0x8c) = b;
    *(int*)(s + 0x90) = c;
}

// @ 0x00bbc4a0
void __fastcall KeySink::StoreEmpty()
{
    char* s = (char*)this;
    *(int*)(s + 0x7c) = g_dw168a488;
    *(int*)(s + 0x80) = g_dw168a48c;
    *(int*)(s + 0x84) = g_dw168a490;
    *(int*)(s + 0x88) = g_dw168a488;
    *(int*)(s + 0x8c) = g_dw168a48c;
    *(int*)(s + 0x90) = g_dw168a490;
}

// @ 0x00bbc540
void __stdcall CargoSlotsUpdate(int* k, void* planetArg)
{
    if (k[0] == (int)g_dw168a488 && k[1] == (int)g_dw168a48c && k[2] == (int)g_dw168a490)
        return;

    void* planet = planetArg;
    if (planet == 0)
        planet = GetActivePlanet();

    ((PlanetCellMgr*)planet)->FUN_00c745d0(1, k);

    int* p2 = GetActivePlanet2();
    if (p2 != 0)
        ((PlanetObj*)p2)->FUN_00c80680(1, k);

    if (planet != GetActivePlanet())
        return;

    GetDrawObj()->FUN_00b2bbe0();
    void* sp = GetSpeciesManager()->FUN_00b3d420(k);
    SpeciesProfile* prof = GetSpeciesManager()->FUN_00b90410(sp);
    if (prof == 0)
        return;

    unsigned cat = prof->EmblemType();
    if (cat == 0x29c388a) {
        GetDrawObj()->Flush(2);
    } else if (cat == 0x3a8be428) {
        GetDrawObj()->Flush(4);
    } else if (cat == 0x6d60a1cc) {
        GetDrawObj()->Flush(1);
    } else {
        GetDrawObj()->Flush(0);
    }
}

// @ 0x00bbc670
int __stdcall PlanetTerraformDist(void* rec)
{
    PlanetRecord* r = (PlanetRecord*)rec;
    if (r == 0)
        r = GetActivePlanetRecord();
    return TerraDistClass(r->unk_b0, r->unk_b4);
}

// @ 0x00bbc6a0
bool __stdcall PlanetTerraformAtLeast(int value, void* rec)
{
    PlanetRecord* r = (PlanetRecord*)rec;
    if (r == 0) {
        r = GetActivePlanetRecord();
        if (r == 0)
            r = GetActivePlanetRecord();
    }
    int dist = TerraDistClass(r->unk_b0, r->unk_b4);
    return dist >= value;
}

// @ 0x00bbc870
void __stdcall fn_bbc870(int* out, int n, int code, void* rec)
{    struct Key3 {
        int a, b, c;
    };

    int found = 0;
    int idx = 0;

    PlanetRecord* r = (PlanetRecord*)rec;
    if (r == 0)
        r = GetActivePlanetRecord();

    SpeciesMgr* mgr = FUN_00b3d420();

    int count = (r->p_c0 - r->p_bc) / 0xc;
    int off = 0;
    idx = 0;
    if (count > 0) {
        do {
            int* entry = (int*)(r->p_bc + off);
            SpeciesProfile* prof = mgr->FUN_00b90410(entry);
            if (prof != 0) {
                if (prof->EmblemType() == code) {
                    ++found;
                    if (found == n) {
                        Key3* __restrict dst = (Key3*)out;
                        *dst = *(const Key3*)entry;
                        return;
                    }
                }
            }
            ++idx;
            off += 0xc;
        } while (idx < count);
    }

    Key3* __restrict dst = (Key3*)out;
    *dst = *(const Key3*)&g_dw168a488;
}

// @ 0x00bbc950
void __stdcall fn_bbc950(int* out, int a, int b, void* rec)
{
    int idx = 0;
    int found = 0;

    PlanetRecord* r = (PlanetRecord*)rec;
    if (r == 0)
        r = GetActivePlanetRecord();

    GetSetting9_s00bb_b9d0();

    int count = (int)((r->p_d4 - r->p_d0) / 0xc);
    int target = a * 2 - 1 + b;
    int off = 0;
    if (count > 0) {
        do {
            SpeciesProfile* prof = (SpeciesProfile*)GetSpeciesProfile(r->p_d0 + off);
            if (prof != 0) {
                if (prof->field_608 == 0)
                    ++found;
                if (found == target) {
                    int* src = (int*)(r->p_d0 + off);
                    out[0] = src[0];
                    out[1] = src[1];
                    out[2] = src[2];
                    return;
                }
            }
            ++idx;
            off += 0xc;
        } while (idx < count);
    }

    out[0] = g_dw168a488;
    out[1] = g_dw168a48c;
    out[2] = g_dw168a490;
}

// @ 0x00bbca30
Key12_bbca30 TObj::FUN_00bbca30(int index, int planet)
{
    if (planet == 0) {
        planet = *(int*)((char*)FUN_01021260() + 0x13c);        // ActivePlanet(); ->+0x13c
    }
    int count = 0;
    TObj* mgr = (TObj*)FUN_00401090();
    int n = (*(int*)(planet + 0xd4) - *(int*)(planet + 0xd0)) / 0xc;
    for (int i = 0; i < n; i++) {
        void* e = (void*)(*(int*)(planet + 0xd0) + i * 0xc);
        TObj* p = (TObj*)mgr->F_4df550(e);
        if (p != 0) {
            if (*(uint32_t*)((char*)p + 0x608) > 0) {
                count++;
            }
            if (count == index) {
                return *(const Key12_bbca30*)e;
            }
        }
    }
    return *(const Key12_bbca30*)&DAT_0168a488;
}

// @ 0x00bbcb90
char TObj::FUN_00bbcb90(int param_1, int param_2)
{
    int iVar3 = param_2;
    if (param_2 == 0) {
        iVar3 = (int)FUN_01021260();
    }
    int iVar1 = *(int*)(iVar3 + 0x13c);
    int k1[3], k2[3], k3[3];
    F_bbc870(k1, param_1, (void*)0x6d60a1cc, iVar1);
    F_bbc540(k1, (void*)iVar3);
    F_bbc870(k2, param_1, (void*)0x29c388a, iVar1);
    F_bbc540(k2, (void*)iVar3);
    F_bbc870(k3, param_1, (void*)0x3a8be428, iVar1);
    F_bbc540(k3, (void*)iVar3);
    char flag = 1;
    if (k1[0] == (int)DAT_0168a488 && k1[1] == (int)DAT_0168a48c && k1[2] == (int)DAT_0168a490 &&
        k2[0] == (int)DAT_0168a488 && k2[1] == (int)DAT_0168a48c && k2[2] == (int)DAT_0168a490 &&
        k3[0] == (int)DAT_0168a488 && k3[1] == (int)DAT_0168a48c && k3[2] == (int)DAT_0168a490) {
        flag = 0;
    }
    if ((*(uint32_t*)(iVar1 + 0x2c) & 0x800) == 0) {
        int kc[3], k18[3], k24[3];
        FUN_00bbca30(kc, param_1, iVar1);
        FUN_00bbcb10(kc, (void*)iVar3);
        F_bbc950(k18, param_1, 1, iVar1);
        FUN_00bbcb10(k18, (void*)iVar3);
        F_bbc950(k24, param_1, 0, iVar1);
        FUN_00bbcb10(k24, (void*)iVar3);
        if (flag == 0) {
            if (k24[0] == (int)DAT_0168a488 && k24[1] == (int)DAT_0168a48c && k24[2] == (int)DAT_0168a490 &&
                k18[0] == (int)DAT_0168a488 && k18[1] == (int)DAT_0168a48c && k18[2] == (int)DAT_0168a490 &&
                !EA_ResKeyNeq(kc, &DAT_0168a488)) {
                return 0;
            }
            return 1;
        }
    }
    return flag;
}

// @ 0x00bbcda0
bool __stdcall FUN_00bbcda0(int param_1, int param_2)
{
    if (param_2 == 0) {
        param_2 = (int)FUN_010212a0();
    }
    int v;
    if ((*(uint32_t*)(param_2 + 0x2c) & 0x800) != 0) {
        v = *(int*)(param_2 + 0xc0) - *(int*)(param_2 + 0xbc);
    } else {
        v = *(int*)(param_2 + 0xd4) - *(int*)(param_2 + 0xd0);
    }
    return v / 0xc >= param_1 * 3;
}

// @ 0x00bbce00
bool __stdcall FUN_00bbce00(int param_1, int param_2)
{
    if (param_2 == 0) {
        param_2 = (int)FUN_010212a0();
    }
    int v = *(int*)(param_2 + 0xc0) - *(int*)(param_2 + 0xbc);
    return v / 0xc >= param_1 * 3;
}

// @ 0x00bbce40
int __stdcall FUN_00bbce40(int param_1)
{
    if (param_1 == 0) {
        param_1 = (int)FUN_010212a0();
    }
    int iVar2 = param_1;
    if (param_1 == 0) {
        iVar2 = (int)FUN_010212a0();
    }
    iVar2 = FUN_00fc2080(*(float*)(iVar2 + 0xb0), *(float*)(iVar2 + 0xb4));
    if (iVar2 > 0) {
        int iVar4 = iVar2 * 3;
        do {
            int iVar3 = param_1;
            if (param_1 == 0) {
                iVar3 = (int)FUN_010212a0();
            }
            int iVar1;
            if ((*(uint32_t*)(iVar3 + 0x2c) & 0x800) != 0) {
                iVar1 = (*(int*)(iVar3 + 0xc0) - *(int*)(iVar3 + 0xbc)) / 0xc;
            } else {
                iVar1 = (*(int*)(iVar3 + 0xd4) - *(int*)(iVar3 + 0xd0)) / 0xc;
            }
            if (iVar1 >= iVar4) {
                return iVar2;
            }
            iVar2--;
            iVar4 -= 3;
        } while (iVar2 > 0);
    }
    return 0;
}

// @ 0x00bbcf00
void TObj::FUN_00bbcf00(void* planet, float f2, float f3, int param_4)
{
    TObj* pl = (TObj*)planet;
    int uVar7 = *(int*)((char*)planet + 0x13c);
    pl->F_c70a00(f2);
    pl->F_c70a50(f3);
    float t0 = pl->F_c71d30();
    pl->F_c71da0(t0);
    if (planet == FUN_01021260()) {
        if (FUN_01021080() == 0) {
            TObj* pm = (TObj*)FUN_00b3d350();
            TObj* sub = (TObj*)*(void**)((char*)pm + 0x24);
            if (sub != 0) {
                TObj* terr = (TObj*)((void*(__thiscall*)(void*))VF(sub, 0x10))(sub);
                if (terr != 0) {
                    float fa = terr->F_fbda80();
                    float lim = f3 - 0.8f;
                    float* pu = &f2;
                    if (f2 <= lim) {
                        pu = &lim;
                    }
                    terr->F_fbddb0(*pu, f3, (void*)param_4);
                    if (terr->F_c70a70() == 0) {
                        pl->F_c70aa0(*(float*)((char*)terr + 0x600));
                    }
                    if (fa != terr->F_fbda80()) {
                        TObj* ms = (TObj*)FUN_0067dcc0();
                        ((void(__thiscall*)(void*, int, int, int))VF(ms, 0x14))(ms, 0x45fe992, 0, 0);
                    }
                }
                TObj* ent = (TObj*)pl->F_c71e30();
                if (ent != 0) {
                    if (ent->F_c308b0() != 0) {
                        if (this->F_bbc670(uVar7) > 0) {
                            int id = FUN_01021090();
                            TObj* av = (TObj*)((TObj*)FUN_01002bd0(id))->F_b1fdb0();
                            av->F_ffaa90();
                            TObj* log = (TObj*)FUN_00b3d3e0(0xc4875746, 0x131a9f54, 0, 0, 1, 0);
                            log->F_dd8640(0xc4875746, 0x131a9f54, 0, 0, 1, 0);
                            pl->F_c70de0(1);
                        }
                    }
                }
            }
            TObj* t = (TObj*)FUN_00b3d470();
            if (t != 0) {
                ((TObj*)FUN_00b3d470())->F_01034880();
            }
        }
    }
}

// @ 0x010659c0
uint32_t convertStarMapButtonToFilter(uint32_t id)
{
    uint32_t v = id;
    switch (v)
    {
    case 0x2e1b6f8: return 0;
    case 0x2e1b708: return 1;
    case 0x2e1b720: return 5;
    case 0x2e1b72c: return 4;
    case 0x2e1b73c: return 3;
    case 0x2e1cbd7: return 2;
    }
    return id;
}

// @ 0x01065a50
#pragma intrinsic(cos, sin)
void BuildBakeOffset(float radius, float angle, float* out)
{
    if ((gBakePhaseInit & 1) == 0)
    {
        gBakePhase = gBakePhaseSpeed * 0.0055555557f;
        gBakePhaseInit |= 1;
    }
    float s = radius * 0.05f;
    float a = gBakePhase * angle;
    out[2] = 0.0f;
    out[0] = -(float)(cos(a) * s);
    out[1] = -(float)(sin(a) * s);
}

// @ 0x01065ab0
void cSPUISpace::ShowBakeTimeSplash_01065ab0()
{
    void* w = mpGlobalUI->FindWindowByID(0x54fc370);
    if (w != 0)
        ((Tc2ii)VTS(w, 0x7c))(w, 1, 1);
    void* srv = MessageServer_67dcc0();
    ((Tc3iii)VTS(srv, 0x14))(srv, 0x604d856, 0, 0);
}

// @ 0x01065af0
void cSPUISpace::HideBakeTimeSplash_01065af0()
{
    void* w = mpGlobalUI->FindWindowByID(0x54fc370);
    if (w != 0)
        ((Tc2ii)VTS(w, 0x7c))(w, 1, 0);
    void* srv = MessageServer_67dcc0();
    ((Tc3iii)VTS(srv, 0x14))(srv, 0x604d85d, 0, 0);
}

// @ 0x01065b30
bool cSPUISpace::IsBakeSplashShown_01065b30()
{
    bool shown = false;
    void* w = mpGlobalUI->FindWindowByID(0x54fc370);
    if (w != 0)
        shown = (((TcRi)VTS(w, 0x28))(w) & 1);
    return shown;
}

// @ 0x01065b60
void __stdcall HideStarPlanet_01065b60(void* layout, uint32_t n)
{
    if (n < 5)
    {
        void* w = ((CLayout*)layout)->FindWindowByID((int)((n + 0x684bc0) * 16), 1);
        if (w != 0)
            return ((Tc2ii)VTS(w, 0x7c))(w, 1, 0);
    }
}

// @ 0x01065ba0
int CTerrainIconOwner::GetTerrainIcon_01065ba0(int n)
{
    void* tm = TM_a_b3d430(0);
    int max = ((CTM*)tm)->Max_bbc670();
    if (n > max)
        return m544;

    void* tm2 = TM_b_b3d430(n, 0);
    if (((CTM*)tm2)->A_bbcda0())
        return m554;

    void* tm3 = TM_b_b3d430(n, 0);
    if (((CTM*)tm3)->B_bbce00())
        return m550;

    if (n != 1)
    {
        void* tm4 = TM_b_b3d430(n - 1, 0);
        if (!((CTM*)tm4)->A_bbcda0())
            return m548;
    }
    return m54c;
}

// @ 0x01065c30
void SPUISpace::ShowCameraControls(int param)
{
    ((GlobalUI_s0106_5c30*)mGlobalUI)->FindWindowByID(0x4cab570)->SetShown(1, param);
    ((GlobalUI_s0106_5c30*)mGlobalUI)->FindWindowByID(0x4cab571)->SetShown(1, param);
    ((GlobalUI_s0106_5c30*)mGlobalUI)->FindWindowByID(0x4cab56e)->SetShown(1, param);
    ((GlobalUI_s0106_5c30*)mGlobalUI)->FindWindowByID(0x4cab56f)->SetShown(1, param);
    ((GlobalUI_s0106_5c30*)mGlobalUI)->FindWindowByID(0x5cab570)->SetShown(1, param);
    ((GlobalUI_s0106_5c30*)mGlobalUI)->FindWindowByID(0x5cab571)->SetShown(1, param);
    ((GlobalUI_s0106_5c30*)mGlobalUI)->FindWindowByID(0x5cab56e)->SetShown(1, param);
    ((GlobalUI_s0106_5c30*)mGlobalUI)->FindWindowByID(0x5cab56f)->SetShown(1, param);
}

// @ 0x01065d20
void T5d20::f()
{
    if (((ConfigMgr*)ConfigManager())->Lookup(0x4ea96cb) == 0) { mState = 8; return; }
    switch (mState) {
    case 0: mState = 1; ((CfgMgr*)FUN_0067cac0(0x43c18587))->F_67c830(0x43c18587); return;
    case 1: mState = 2; ((CfgMgr*)FUN_0067cac0(0x1930f01e))->F_67c830(0x1930f01e); return;
    case 2: mState = 3; return;
    case 3: mState = 4; return;
    case 4: mState = 5; ((CfgMgr*)FUN_0067cac0(0xf98be0b8))->F_67c830(0xf98be0b8); return;
    case 5: mState = 6; return;
    case 6: mState = 7; ((CfgMgr*)FUN_0067cac0(0xe43f6bbd))->F_67c830(0xe43f6bbd); return;
    case 7: break;
    default: return;
    }
    mState = 8;
}

// @ 0x01065e20
bool T5d20::isStateSpecial()
{
    int x = mState;
    if (x != 1 && x != 2 && x != 5 && x != 7) return false;
    return true;
}

// @ 0x01065e40
void T5d20::reset()
{
    mState = 8;
    ((CfgMgr*)FUN_0067cac0())->Set(0x43c18587, 1);
    ((CfgMgr*)FUN_0067cac0())->Set(0x1930f01e, 1);
    ((CfgMgr*)FUN_0067cac0())->Set(0xf98be0b8, 1);
    ((CfgMgr*)FUN_0067cac0())->Set(0xe43f6bbd, 1);
}

// @ 0x01065ea0
void SPUISpace::ShowToolChargeBar()
{
    Win* w = ((GlobalUI_s0106_5c30*)mGlobalUI)->FindWindowByID(0x341ba47);
    if (w) w->SetShown(1, 1);
}

// @ 0x01065ed0
void SPUISpace::HideToolChargeBar()
{
    Win* w = ((GlobalUI_s0106_5c30*)mGlobalUI)->FindWindowByID(0x341ba47);
    if (w) w->SetShown(1, 0);
}

// @ 0x01065f00
void FUN_01065f00(uint* out, void* planet)
{
    cPlanet_s0106_5c30* pl = (cPlanet_s0106_5c30*)planet;
    uint a = 0, b = 0, c = 0;
    int t = pl->GetKind();
    if (t == 2 || t == 4) goto get;
    if (t != 5) goto done;
    {
        void* game = pl->Project();
        void* avatar = ((cSpaceGame_s0106_5c30*)game)->GetAvatar();
        void* emp = ((StarMgr_s0106_5c30*)StarManager_s0106_5c30())->GetEmpireByID((uint)avatar);
        if (!((cEmpire_s0106_5c30*)emp)->IsScannable() && emp != GetPlayerEmpire_s0106_5c30()) {
            out[0] = *(uint*)&g_15b9420;
            out[1] = *(uint*)&g_15b9424;
            out[2] = *(uint*)&g_15b9428;
            return;
        }
    }
get:
    {
        void* key = pl->GetSpeciesKey();
        void* setting = GetSetting9((u32)(size_t)key);
        void* prof = ((SpeciesMgr_s0106_5c30*)setting)->GetProfile();
        if (prof) {
            a = *(uint*)((char*)prof + 0x504);
            c = *(uint*)((char*)prof + 0x50c);
            b = 0x2f7d0004;
        }
    }
done:
    out[0] = a; out[1] = b; out[2] = c;
}

// @ 0x01065fe0
void SPUISpace::UpdateGlobal()
{
    void* inv = ((SimSpaceGame*)GetUFOSimulator_s0106_5c30())->GetPlayerInventory();
    float f = *(float*)((char*)inv + 0x540);
    float div = ((Inv508*)((char*)inv + 0x508))->Get();
    ((GlobalUI_s0106_5c30*)mGlobalUI)->SetProgress(0x1c404ac, f / div);
    int n = (int)f;
    if ((float)n < f) ++n;
    void* layout = *(void**)((char*)mGlobalUI + 8);
    Win* w = ((LayoutUI*)layout)->FindWindowByID(0x4d039a8, 1);
    if (w) {
        char buf[0x20];
        EA_SetNumberString(n, n >> 31, buf, 0x20);
        w->SetText(buf);
    }
    char b1 = FUN_00c372c0(inv);
    ((GlobalUI_s0106_5c30*)mGlobalUI)->FindWindowByID(0x6396b68)->SetShown(2, b1);
    ((GlobalUI_s0106_5c30*)mGlobalUI)->SetProgress(0x5481520,
        *(float*)((char*)inv + 0x7f4) / *(float*)((char*)inv + 0x7f8));
    char b2 = FUN_00c37300(inv);
    ((GlobalUI_s0106_5c30*)mGlobalUI)->FindWindowByID(0x6396b78)->SetShown(2, b2);
}

// @ 0x01066120
void* T6120::f(uint id)
{
    void* r = 0;
    Win* w = ((GlobalUI_s0106_5c30*)mGlobal)->FindWindowByID(id);
    if (w) r = FUN_01077b40_s0106_5c30(w);
    return r;
}

// @ 0x01066150
int __stdcall FUN_01066150(int x)
{
    if ((uint)(x + 0x50000000) <= 0xf) return x + 0x10;
    return 0;
}

// @ 0x01066180
void FUN_01066180(void* p, float f)
{
    VtP* vp = (VtP*)p;
    VtS* s = (VtS*)vp->v10();
    s->v74(1.0f, 1.0f);
    vp->v14(0);
    if (f > 0.0f) {
        float* r = s->v38();
        if (f < r[2] - r[0])
            s->v74(f, 1.0f);
    }
    vp->v14(1);
}

// @ 0x01066200
void SPUISpace::ToggleStarmapFilters(int param)
{
    Win* w = ((GlobalUI_s0106_5c30*)mGlobalUI)->FindWindowByID(0x2e1ad08);
    if (w) w->SetShown(1, param);
}

// @ 0x01066230
void SPUISpace::FUN_01066230(char param)
{
    uint flag = (uint)this;
    ((char*)&flag)[0] = 0;
    Win* w = ((GlobalUI_s0106_5c30*)mGlobalUI)->FindWindowByID(0x5d646c8);
    void* planet = (void*)GetActivePlanet_s0106_5c30();
    if (planet) {
        bool k2 = ((cPlanet_s0106_5c30*)planet)->GetToolMode() > 1;
        bool b1;
        int ctx = GetUniverseContext();
        if (ctx == 2) b1 = true;
        else {
            ctx = GetUniverseContext();
            if (ctx == 1) {
                void* inv = ((SimSpaceGame*)GetUFOSimulator_s0106_5c30())->GetPlayerInventory();
                b1 = (*(char*)((char*)inv + 0x74c) == 0);
            } else b1 = false;
        }
        if (k2 && !b1 && param == 0) ((char*)&flag)[0] = 1;
    }
    w->SetShown(2, (int)flag);
}

// @ 0x01066310
void __stdcall FUN_01066310(int* src)
{
    void* p = operator_new(0x18, "Simulator", 0, 0, (const char*)&g_alloc_13ebb38, 0xd1);
    int* d = (int*)p;
    if (d) { d[0]=src[0]; d[1]=src[1]; d[2]=src[2]; d[3]=src[3]; d[4]=src[4]; }
    d[5] = 0;
}

// @ 0x01066390
float FUN_01066390(float* p, float s)
{
    void* viewer = ((AppObj*)App())->GetViewer();
    float cam[3];
    ((cViewer*)viewer)->GetCameraLocationInfo(0, 0, cam, 0);
    float a[3];
    a[0] = p[0] + cam[0] * s;
    a[1] = p[1] + cam[1] * s;
    a[2] = p[2] + cam[2] * s;
    float x1, y1, x2, y2;
    FUN_00e50750(p, &x1, &y1);
    FUN_00e50750(a, &x2, &y2);
    float dx = x2 - x1;
    float dy = y2 - y1;
    float d = sqrtf_s0106_5c30(dx * dx + dy * dy);
    float area[4];
    float* r = (float*)GetMainWindowArea(area);
    float lim = r[3] * 0.25f;
    if (d > lim) d = lim;
    return d;
}

// @ 0x01066480
bool CmdDeleteCargo::OnState1()
{
    void* pc = 0;
    void* w = ((GlobalUI_s0106_5c30*)((SPUISpace*)pSpace)->mGlobalUI)->FindWindowByID(windowID);
    if (w) pc = FUN_01077b40_s0106_5c30(w);
    void* old = pItem;
    if (pc != old) {
        if (pc) ((IRefCounted*)pc)->AddRef();
        pItem = pc;
        if (old) ((IRefCounted*)old)->Release();
    }
    if (!pItem) { state = 2; return true; }
    if (!CalloutMessageBox(this, (void*)0x15b9268)) { state = 2; return true; }
    state = 1;
    int two = 2;
    return state == two;
}

// @ 0x01066520
bool CmdDeleteCargo::OnState2()
{
    if (pItem && field0c == 0x5107b1a) {
        void* o = *(void**)((char*)pSpace + 0x238);
        ((Win*)o)->v78((uint)pItem);
    }
    Win* w = ((GlobalUI_s0106_5c30*)((SPUISpace*)pSpace)->mGlobalUI)->FindWindowByID(0xb2001000);
    if (w) w->SetShown(1, 0);
    return false;
}

// @ 0x01066570
bool CmdDeleteCargo::Run()
{
    char r = 1;
    for (;;) {
        switch (state) {
        case 0:
            r = OnState1();
            break;
        case 1:
            if (field0c == 0x1510d07) return true;
            state = 2;
            break;
        case 2:
            OnState2();
            return false;
        default:
            return true;
        }
        if (r == 0) return true;
    }
}

// @ 0x010665c0
CmdCtor* CmdCtor::init(SPUISpace* space, uint windowID)
{
    int zero = 0;
    CmdCtor* p = this;
    p->mVtbl = (void*)g_149c1f0;
    p->mpItem08 = 0;
    // Retain the native store order without qualifying the other fields.
    *(SPUISpace* volatile*)&p->mpSpace14 = space;
    p->mWindowID10 = windowID;
    p->mDialogResult0c = 0x1510d07;
    p->mState18 = zero;
    return p;
}

// @ 0x010665f0
void __stdcall FUN_010665f0(int unused)
{
    (void)unused;
    ((SpGameTime*)GameTimeManager(0x4bf38a9))->IncPauseGate();
}

// @ 0x01066610
void T6610::set(int a, int b)
{
    (void)a;
    ((SpGameTime*)GameTimeManager(0x4bf38a9))->DecPauseGate();
    mField = b;
}

// @ 0x01066630
void FUN_01066630(float* p1, float* p2, float* p3)
{
    if ((g_16e283c & 1) == 0) {
        g_16e2838 = g_180 / g_15b90e0;
        g_16e283c |= 1;
    }
    double x = p1[0];
    double y = p1[1];
    *p2 = (float)(sqrt(y * y + x * x) * g_149c1fc);
    *p3 = (float)(atan2(y, x) + g_15b90e0) * g_16e2838;
}

// @ 0x010666a0
void* FUN_010666a0()
{
    void* g = SpaceGameGet_s0106_5c30();
    if (g) return ((cSpaceGameObj*)g)->pSpace;
    return 0;
}

// @ 0x010666b0
void SPUISpace::FUN_010666b0()
{
    for (uint i = 0; i < 6; ++i) {
        Win* w = ((GlobalUI_s0106_5c30*)mGlobalUI)->FindWindowByID(g_ids149c178[i]);
        Win28* q = w ? (Win28*)((Winc*)w)->v3(0x8ed27e7a) : 0;
        void* o = FUN_01046fc0();
        bool b = ((cPropView*)o)->Test(i);
        q->call28(4, b ? 1 : 0);
    }
}

// @ 0x01066720
void FUN_01066720(int* key)
{
    int local[3];
    local[0] = key[0];
    local[1] = 0x2f7d0004;
    local[2] = key[2];
    void* layout = 0;
    void* g = SpaceGameGet_s0106_5c30();
    if (g) {
        void* sp = ((cSpaceGameObj*)g)->pSpace;
        if (sp) {
            void* globalUI = ((SPUISpace*)sp)->mGlobalUI;
            layout = *(void**)((char*)globalUI + 8);
        }
    }
    Win* w = ((LayoutUI*)layout)->FindWindowByID(0xb0b00000, 1);
    SetWindowImage(w, local, -1);
}

// @ 0x01066780
bool SpaceZoom::FUN_01066780(int unused, InputEvent* ev)
{
    (void)unused;
    if (!mp258) return true;
    if (ev->key == 0x1b) {
        if (ev->flags != 1) return true;
        int id = ((EvObj*)ev->obj)->GetId();
        void* z;
        if (id == 0x7edb1e8) z = mZoomBegin[0];
        else if (id == 0x7edb1e9) z = mZoomBegin[1];
        else if (id == 0x7edb1ea) z = mZoomBegin[2];
        else return true;
        if (!z) return true;
        ((TextZoomName*)z)->Activate(0);
        return true;
    }
    if (ev->key == 0x1c) {
        if (ev->flags != 1) return true;
        int id = ((EvObj*)ev->obj)->GetId();
        void* z;
        if (id == 0x7edb1e8) z = mZoomBegin[0];
        else if (id == 0x7edb1e9) z = mZoomBegin[1];
        else if (id == 0x7edb1ea) z = mZoomBegin[2];
        else return true;
        if (z) ((TextZoomName*)z)->Deactivate(0);
    }
    return true;
}

// @ 0x01066880
CmdObj* CmdObj::Ctor()
{
    BaseCtor();
    *(void**)this = (void*)0x149c230;
    m08 = 0;
    mLayout = 0;
    void* p = operator_new(0x18u, (const char*)0x13f6b3c, 0, 0, 0, 0);
    void* layout = 0;
    if (p) layout = ((LayoutAlloc*)p)->Ctor();
    void* old = mLayout;
    if (layout != old) {
        if (layout) ((IRefCounted*)layout)->AddRef();
        mLayout = layout;
        if (old) ((IRefCounted*)old)->Release();
    }
    if (!((LayoutObj*)mLayout)->Init((const wchar_t*)0x149c200, 0x40464100, 1, (int)0xe9f70df9)) {
        ((LayoutObj*)mLayout)->Shutdown(1);
        if (mLayout) {
            void* o = mLayout;
            mLayout = 0;
            ((IRefCounted*)o)->Release();
        }
        return this;
    }
    Win* w = ((LayoutUI*)mLayout)->FindWindowByID(0x37ab944, 1);
    if (w) {
        void* g = SpaceGameGet_s0106_5c30();
        void** vt = *(void***)w;
        ((void (__thiscall*)(void*, void*))vt[0x104 / 4])(w, *(void**)((char*)g + 0x14));
        cString_s0106_5c30 s;
        s.Ctor(0xc0152a6d, 0x6565205, 0);
        void* text = s.GetText(-1, 1);
        SPUIHelpers_SetTooltipText(w, text);
        s.Dtor();
    }
    ((LayoutObj*)mLayout)->SetVisibility(0);
    return this;
}

// @ 0x010669a0
void CmdObj::Dtor()
{
    *(void**)this = (void*)0x149c230;
    if (mLayout) {
        Win* w = ((LayoutUI*)mLayout)->FindWindowByID(0x37ab944, 1);
        if (w) {
            void* g = SpaceGameGet_s0106_5c30();
            void** vt = *(void***)w;
            ((void (__thiscall*)(void*, void*))vt[0x108 / 4])(w, *(void**)((char*)g + 0x14));
        }
        ((LayoutObj*)mLayout)->Shutdown(1);
        if (mLayout) {
            void* o = mLayout;
            mLayout = 0;
            ((IRefCounted*)o)->Release();
        }
    }
    if (mLayout) ((IRefCounted*)mLayout)->Release();
    BaseDtor();
}

// @ 0x01066a10
void T6a10::hide()
{
    if (mWin) ((LayoutWindow*)mWin)->SetVisibility(0);
}

// @ 0x01066a40
char SP::cSPUISpace_s0106_6a40::FUN_01066a40(int param)
{
    mTimer8 += (uint32_t)param;
    void* m = FUN_00b3d230();
    char  c = FUN_00b5ca60();
    int   iVar4;
    void* piVar3;
    int   iVar5;
    (void)m;
    if (c != 0) {
        if (mpLayout == 0) goto LAB_d3c;
        if (FUN_00810070(mpLayout) == 0) goto LAB_d3c;
        void* wm = FUN_0067caa0();
        int   wi = ((VFI)(*(void***)wm)[0x48 / 4])(wm, 1);
        void* w  = FUN_008105b0(mpLayout, 0x37ab944, 1);
        if (w != (void*)(size_t)wi)
            goto LAB_d32;
        iVar4 = (int)(size_t)FUN_0067cab0();
        if (iVar4 != 0)
            FUN_00801bb0((void*)(size_t)iVar4, 0x64e9c00);
    } else {
        int tm = (int)(size_t)FUN_00b3d4d0();
        if (*(int*)((char*)(size_t)tm + 0x2c) == 1 || *(int*)((char*)(size_t)tm + 0x2c) == 2)
            goto LAB_d22;
        if (FUN_01021080() != 0)
            goto LAB_d22;
    }
    {
        void* pi = FUN_00b3d240();
        piVar3 = (void*)((VFP)(*(void***)pi)[0x30 / 4])(pi);
        if (piVar3 == 0) {
            param  = 0;
            iVar4  = 0;
        } else {
            iVar4 = (int)(size_t)((VFP1)(*(void***)piVar3)[0x0c / 4])(piVar3, 0x17f243b);
            if (iVar4 != 0 && FUN_00b188b0((void*)(size_t)iVar4) != 0)
                return 0;
            iVar4 = (int)(size_t)((VFP1)(*(void***)piVar3)[0x0c / 4])(piVar3, 0xb033b403);
            if (iVar4 != 0 && *(int*)((char*)(size_t)iVar4 + 0x714) == 0)
                return 0;
            iVar4 = (int)(size_t)((VFP1)(*(void***)piVar3)[0x0c / 4])(piVar3, 0x1007ae63);
            if (iVar4 != 0 && mpLayout != 0) {
                char cv = ((VFC0)(*(void***)(size_t)(iVar4 + 0x34))[0x58 / 4])((void*)(size_t)(iVar4 + 0x34));
                byte vis;
                if (cv == 0) {
LAB_c12:
                    vis = 0;
                } else {
                    void* plt = FUN_01021260();
                    if (FUN_0102adf0(plt) != 0) goto LAB_c12;
                    vis = 1;
                    if (FUN_00810070(mpLayout) == 0) {
                        void* rs = FUN_00435e90();
                        FUN_00435ed0(0xa47319c2, rs);
                    }
                    void* sg = FUN_01002bd0();
                    FUN_00b5f950_Assign((void*)((char*)sg + 0x28), (void*)(size_t)iVar4);
                    mTimer8 = 0;
                }
                FUN_00810590(mpLayout, vis);
            }
        }
        piVar3 = FUN_008105b0(mpLayout, 0x68afc98, 1);
        {
            void* sg    = FUN_01002bd0();
            void* inner = *(void**)((char*)sg + 0x28);
            if (inner == 0)
                iVar5 = 0;
            else
                iVar5 = (int)(size_t)((VFP1)(*(void***)inner)[0x0c / 4])(inner, 0x1007ae63);
        }
        if (piVar3 != 0 && iVar5 != 0) {
            float out[2];
            char  cv = ((VFCVP)(*(void***)(size_t)(iVar5 + 0x34))[0x7c / 4])((void*)(size_t)(iVar5 + 0x34), out);
            if (cv == 0)
                FUN_00810590(mpLayout, 0);
            else
                ((VFMP2)(*(void***)piVar3)[0x64 / 4])(piVar3, out[0], out[1]);
        }
        if (iVar4 == 0 && mpLayout != 0 && FUN_00810070(mpLayout) != 0 && mTimer8 > 0xbb8)
            FUN_00810590(mpLayout, 0);
        {
            char bl;
            if (FUN_01021080() == 0) {
                void* sg = FUN_01002bd0();
                void* av = FUN_00b1fdb0(sg);
                bl = (*(char*)((char*)av + 0x14) != 0) ? 1 : 0;
            } else {
                bl = 0;
            }
            if (FUN_00b187f0((void*)(size_t)iVar4) == 0 &&
                FUN_00b18810((void*)(size_t)param) == 0 &&
                FUN_00b187d0((void*)(size_t)param) == 0 &&
                FUN_00b18890((void*)(size_t)param) == 0) {
                if (FUN_00b18870((void*)(size_t)param) == 0)
                    return 1;
                goto LAB_do6999;
            }
            if (bl != 0) {
                FUN_00b69930((void*)(size_t)param, gF_13eb1bc, 0);
                return 1;
            }
LAB_do6999:
            FUN_00b69990((void*)(size_t)param);
            return 1;
        }
    }
LAB_d22:
    if (mpLayout == 0) goto LAB_d3c;
    if (FUN_00810070(mpLayout) == 0) goto LAB_d3c;
LAB_d32:
    FUN_00810590(mpLayout, 0);
LAB_d3c:
    {
        int x = (int)(size_t)FUN_0067cab0();
        if (x != 0)
            FUN_00801bb0((void*)(size_t)x, 0x1002);
    }
    return 0;
}

// @ 0x01066d60
void SP::cSPUISpace_s0106_6a40::FUN_01066d60()
{
    if (mpGlobal->IsTooltipVisible()) {
        if (gDAT_016e2234 != 0)
            ((VF0)(*(void***)gDAT_016e2234)[0x18 / 4])(gDAT_016e2234);
        void* m = FUN_00b3d230();
        ((VF1P)(*(void***)m)[0x40 / 4])(m, gDAT_016e2234);
        mpGlobal->SetVisibility(0);
        SPUIEventLog* ev = (SPUIEventLog*)FUN_00b3d3e0(0);
        ev->SetVisibility();
        void* p = mp5c4;
        if (p != 0)
            ((VF1)(*(void***)p)[0xc0 / 4])(p, 0);
    }
}

// @ 0x01066dd0
void SP::cSPUISpace_s0106_6a40::FUN_01066dd0()
{
    if (!mpGlobal->IsTooltipVisible()) {
        void* m = FUN_00b3d230();
        ((VF2P)(*(void***)m)[0x38 / 4])(m, gDAT_016e2234, 1);
        mpGlobal->SetVisibility(1);
        SPUIEventLog* ev = (SPUIEventLog*)FUN_00b3d3e0(1);
        ev->SetVisibility();
        void* p = mp5c4;
        if (p != 0)
            ((VF1)(*(void***)p)[0xc0 / 4])(p, 1);
    }
}

// @ 0x01066e30
void SP::cSPUISpace_s0106_6a40::ShowForTutorial(int param)
{
    float off = 0.0f;
    int   id  = param;
    int   vis = param;
    switch (param) {
    case 0: id = 0x30aa150; off = gF_13f9c6c; vis = 1; break;
    case 1: id = 0x30aa150; off = gF_13ec4d0; vis = 0; break;
    }
    void* w = mpGlobal->FindWindowByID(id);
    if (w != 0)
        ((VF0)(*(void***)w)[0])(w);
    float* r = (float*)((VFP)(*(void***)w)[0x34 / 4])(w);
    float pos[4];
    pos[0] = r[0];
    pos[1] = r[1] + off;
    pos[2] = r[2];
    pos[3] = r[3] + off;
    ((VFMP)(*(void***)w)[0x60 / 4])(w, pos);
    mpGlobal->SetVisibility(vis);
    ((VF0)(*(void***)w)[1])(w);
}

// @ 0x01066f20
void SP::cSPUISpace_s0106_6a40::UpdateTerraformingBullseye()
{
    float t = FUN_00805080();
    if (!(gF_016e2230 <= t))
        return;

    ::TerraformingManager* tfm = (::TerraformingManager*)FUN_00b3d430(0);
    int   state = tfm->GetState();
    void* wA    = mpGlobal->FindWindowByID(0xa80a7e44);
    if (wA == 0) return;
    if (state == -1) {
        ((VF2)(*(void***)wA)[0x7c / 4])(wA, 1, 0);
        return;
    }
    void* planet = FUN_01021260();
    if (planet == 0) return;
    void* wB = mpGlobal->FindWindowByID(0xa80a7e45);
    void* wC = mpGlobal->FindWindowByID(0x4d90456);
    if (wB == 0 || wC == 0) return;

    float* rA = (float*)((VFP)(*(void***)wA)[0x34 / 4])(wA);
    float  a0 = rA[0], a1 = rA[1], a2 = rA[2], a3 = rA[3];
    float* rB = (float*)((VFP)(*(void***)wB)[0x34 / 4])(wB);
    float  b0 = rB[0], b1 = rB[1], b2 = rB[2], b3 = rB[3];
    float* rC = (float*)((VFP)(*(void***)wC)[0x38 / 4])(wC);
    float  c0 = rC[0], c1 = rC[1], c2 = rC[2], c3 = rC[3];

    float tgt = (state < 1) ? gF_13ec4b0 : gF_1485720;
    if (tgt != mF52c) {
        float secs = FUN_00805080();
        AnimRaw anim;
        FUN_007f81d0(&anim, wA, a1, secs, gF_1485720, 0);
        mpAnimator->AddAnimation(&anim, wA, 0x5243cd6);
        mF52c = tgt;
        anim.Destroy();
    }

    float f10 = ((WideObj*)wB)->GetScaleX();
    float f12 = ((WideObj*)wB)->GetScaleY();

    ((VFMP2)(*(void***)wB)[0x64 / 4])(wB,
        (a2 - a0) * f10 - (b2 - b0) * gF_1471064,
        (a3 - a1) * (gF_1485720 - f12) - (b3 - b1) * gF_1471064);
    ((VFMP2)(*(void***)wC)[0x64 / 4])(wC,
        (c2 - c0) * f10 - (a2 - a0) * gF_1471064,
        (c3 - c1) * (gF_1485720 - f12) - (a3 - a1) * gF_1471064);

    void* btn1 = FUN_005ca960(mpGlobal->FindWindowByID(0x5233980));
    void* btn2 = FUN_005ca960(mpGlobal->FindWindowByID(0x52339a8));
    void* btn3 = FUN_005ca960(mpGlobal->FindWindowByID(0x52339c0));
    ((VF2)(*(void***)btn1)[0x28 / 4])(btn1, 4, (state > 0) ? 1 : 0);
    ((VF2)(*(void***)btn2)[0x28 / 4])(btn2, 4, (state > 1) ? 1 : 0);
    ((VF2)(*(void***)btn3)[0x28 / 4])(btn3, 4, (state > 2) ? 1 : 0);
    {
        void* d = (void*)((VFP)(*(void***)btn1)[0x10 / 4])(btn1);
        ((VF1)(*(void***)d)[0x5c / 4])(d, (int)(size_t)FUN_01065ba0(1));
    }
    {
        void* d = (void*)((VFP)(*(void***)btn2)[0x10 / 4])(btn2);
        ((VF1)(*(void***)d)[0x5c / 4])(d, (int)(size_t)FUN_01065ba0(2));
    }
    {
        void* d = (void*)((VFP)(*(void***)btn3)[0x10 / 4])(btn3);
        ((VF1)(*(void***)d)[0x5c / 4])(d, (int)(size_t)FUN_01065ba0(3));
    }

    void* ob = FUN_008414c0();
    float dx = *(float*)((char*)ob + 0x1fd4);
    float dy = *(float*)((char*)ob + 0x1fd8);
    float len = (float)sqrt((double)(dx * dx + dy * dy));
    if (len <= gF_1485378) {
        ((VF2)(*(void***)wA)[0x7c / 4])(wA, 1, 0);
    } else {
        ((VF2)(*(void***)wA)[0x7c / 4])(wA, 1, 1);
        float v0[3];
        float v1[3];
        float v2[3];
        v0[0] = 0.0f; v0[1] = 1.0f; v0[2] = 0.0f;
        v1[0] = -dy / len; v1[1] = 0.0f; v1[2] = dx / len;
        v2[0] = 0.0f; v2[1] = 0.0f; v2[2] = 0.0f;
        FUN_00436ce0(v0, v1, v2);
        float hit = FUN_006994a0(v1, v2);
        float dist[1];
        dist[0] = hit;
        FUN_00808230(wA, dist);
        if (dist[0] > gF_1486374)
            FUN_00e2f5c0(wA, gImg_15b93a8);
        else if (dist[0] > gF_13ec434)
            FUN_00e2f5c0(wA, gImg_15b939c);
        else
            FUN_00e2f5c0(wA, gImg_15b9390);
    }
    ((VF1)(*(void***)wA)[0x5c / 4])(wA, (int)(size_t)mpArr558[state]);
}

// @ 0x010673f0
uint32_t SP::cSPUISpace_s0106_6a40::UpdateCaptureBarsVisibility(int param)
{
    char active = ((CommManager_6a40*)FUN_00b3d4a0())->IsActive();
    if (active != 0 || param == 0)
        goto LAB_65;
    if (((GameObject*)(size_t)param)->GetKind() != 5)
        goto LAB_65;
    {
        int   local = -1;
        float v     = ::FUN_00c8c7f0((void*)(size_t)param, &local);
        if (local != -1) {
            if (((struct StarManager*)FUN_00b3d2a0())->GetEmpireByID(local) == 0)
                FUN_00c8b820(FUN_00b8de30((void*)(size_t)param, v), 0);
            goto LAB_65;
        }
        if (v > gF_1485378) {
            if (m5b4.mpMeter == 0) {
                CivBar* obj  = (CivBar*)FUN_00f473a0(0x50, gS_13f6b3c, 0, 0, 0, 0);
                void*   made = obj ? obj->Ctor(0, 0x3ffb28c, 0x4d428c1, gW_CivConversionBar, 0x6722122) : 0;
                m5b4 = made;
                m5b4.mpMeter->Init1((void*)(size_t)param);
            }
            return 1;
        }
    }
LAB_65:
    if (m5b4.mpMeter != 0) {
        m5b4.mpMeter->Shutdown(1);
        if (m5b4.mpMeter != 0) {
            SPUIMeter* old = m5b4.mpMeter;
            m5b4.mpMeter = 0;
            ((VF0)(*(void***)old)[1])(old);
        }
    }
    return 0;
}

// @ 0x01067510
int SP::cSPUISpace_s0106_6a40::UpdateCaptureBarsVisibility(CGameNounManager* mgr)
{
    int  count  = 0;
    char haveAc = 0;
    char haveUn = 0;
    char active = ((CommManager_6a40*)FUN_00b3d4a0())->IsActive();
    void* sysMgr = ((struct StarManager*)FUN_00b3d2a0())->GetSystemMgr();
    if (active != 0 || mgr == 0)
        goto LAB_d6_check;
    if (mgr->GetType() != 5)
        goto LAB_d6_check;
    {
        void* player = mgr->mpPlayer;
        void* avatar = mgr->GetAvatar();
        if (((SpaceTradeRouteManager*)sysMgr)->SystemHasTradeRouteWithPlayer(player, avatar) != 0) {
            if (m5ac.mpMeter == 0) {
                CivBar* obj  = (CivBar*)FUN_00f473a0(0x50, gS_13f6b3c, 0, 0, 0, 0);
                void*   made = obj ? obj->Ctor(2, 0x3ffb28c, 0x4d428c1, gW_CivConversionBar, 0x6722122) : 0;
                m5ac = made;
                m5ac.mpMeter->Init0(mgr);
            }
            haveAc = 1;
            count  = 1;
        }
    }
    {
        int   local = -1;
        float v     = FUN_00c8c5d0(mgr, &local);
        if (local != -1) {
            if (((struct StarManager*)FUN_00b3d2a0())->GetEmpireByID(local) == 0)
                FUN_00c8b820(mgr, (void*)(size_t)local);
            goto LAB_after_un;
        }
        if (v > gF_1485378) {
            if (m5b0.mpMeter == 0) {
                CivBar* obj  = (CivBar*)FUN_00f473a0(0x50, gS_13f6b3c, 0, 0, 0, 0);
                void*   made = obj ? obj->Ctor(0, 0x3ffb28c, 0x4d428c1, gW_CivConversionBar, 0x6722122) : 0;
                m5b0 = made;
                m5b0.mpMeter->Init0(mgr);
            }
            count++;
            haveUn = 1;
        }
    }
LAB_after_un:
    if (haveAc != 0)
        goto LAB_d6_check;
LAB_d6_check:
    if (m5ac.mpMeter != 0) {
        m5ac.mpMeter->Shutdown(1);
        if (m5ac.mpMeter != 0) {
            SPUIMeter* old = m5ac.mpMeter;
            m5ac.mpMeter = 0;
            ((VF0)(*(void***)old)[1])(old);
        }
    }
    if (haveUn == 0 && m5b0.mpMeter != 0) {
        m5b0.mpMeter->Shutdown(1);
        if (m5b0.mpMeter != 0) {
            SPUIMeter* old = m5b0.mpMeter;
            m5b0.mpMeter = 0;
            ((VF0)(*(void***)old)[1])(old);
        }
    }
    return count;
}

// @ 0x01067720
void SP::cSPUISpace_s0106_6a40::FUN_01067720(void* p, float f1, float f2, char flag)
{
    if (p == 0 || m5b4.mpMeter == 0)
        return;
    int   local = -1;
    float v     = ::FUN_00c8c7f0(p, &local);
    m5b4.mpMeter->SetValue((int)v, local);
    if (flag != 0)
        m5b4.mpMeter->PullToFront();
    m5b4.mpMeter->SetPos(f1, f2);
}

// @ 0x010677b0
void SP::cSPUISpace_s0106_6a40::FUN_010677b0(CGameNounManager* mgr, float f1, float f2, char flag)
{
    if (mgr == 0)
        return;
    int n = 0;
    if (m5ac.mpMeter != 0) {
        void* sysMgr = ((struct StarManager*)FUN_00b3d2a0())->GetSystemMgr();
        void* player = mgr->mpPlayer;
        void* avatar = mgr->GetAvatar();
        int   v      = (int)((SpaceTradeRouteManager*)sysMgr)->GetTradeRouteScore(player, avatar);
        m5ac.mpMeter->SetValue(v, -1);
        m5ac.mpMeter->SetPos(f1, f2);
        if (flag != 0)
            m5ac.mpMeter->PullToFront();
        n = 1;
    }
    if (m5b0.mpMeter != 0) {
        int   local = -1;
        float v     = FUN_00c8c5d0(mgr, &local);
        m5b0.mpMeter->SetValue((int)v, local);
        if (flag != 0)
            m5b0.mpMeter->PullToFront();
        float off = (float)n * gF_149c1a0 + f2;
        m5b0.mpMeter->SetPos(f1, off);
    }
}

// @ 0x010678e0
void cSPUISpace_s0106_78e0::FUN_010678e0()
{
    float v = kFloatNegOne;
    cGameNounManager* nm = (cGameNounManager*)SP_NounManager();
    void* civ = nm->GetPlayerCivilization();
    if (civ != 0) {
        v = FUN_00c72030(civ);
    }
    if (v != gChargeCache) {
        gChargeCache = v;
        void* win = mpGlobalUI->FindWindowByID(0xabcd1001);
        if (win != 0) {
            if (gChargeCache < 0.0f) {
                cString str(0xc0152a6d, 0x4cac3d8, 0);
                SetTooltipText(win, str.GetText(), -1, 1);
            } else {
                void* saved = ((cToolGate*)gTooltipGate)->FUN_00cfe780(civ);
                cString str(0xc0152a6d, 0x65f79f1, 0);
                SetTooltipText(win, str.GetText(), -1, 1);
                ((cToolGate*)gTooltipGate)->FUN_00cfe780(saved);
            }
        }
    }
}

// @ 0x010679f0
void cSPUISpace_s0106_78e0::FUN_010679f0()
{
    cSpaceGame* game = (cSpaceGame*)SP_SpaceGameGet();
    cGameData* tribe = game->GetPlayerTribe();
    if (tribe == 0) return;
    float t = tribe->FUN_00fe67b0();
    cProgressBar* bar = mpProgressBar;
    cLivingUniverse* lu = (cLivingUniverse*)SP_GetPlayerEmpire();
    void* e = lu->FUN_00c30cb0();
    bar->Update(t, e);
    u32 n = (u32)tribe->FUN_00fe42a0();
    u32 i = mProgressCount;
    if (i < n) {
        do {
            cUIWin* win = (cUIWin*)mpGlobalUI->FindWindowByID(i + 0x6161080);
            if (win != 0) {
                void* x = win->w0c(0x106f146);
                if (x != 0) {
                    VCallV1((char*)x + 0x20c, 0x14, 1);
                }
            }
            i = i + 1;
        } while (i < n);
        mProgressCount = n;
    }
}

// @ 0x01067aa0
void cSPUISpace_s0106_78e0::UpdateToolChargeBar(float f)
{
    if (f <= 0.15f) f = 0.15f;
    if (1.0f <= f) f = 1.0f;
    void* w1 = mpGlobalUI->FindWindowByID(0x341ba47);
    void* w2 = mpGlobalUI->FindWindowByID(0x341ba3b);
    if (w1 != 0 && w2 != 0) {
        float* r = (float*)VCallU32(w1, 0x34);
        VCallV2f(w2, 0x68, (r[2] - r[0]) * f, r[3] - r[1]);
    }
}

// @ 0x01067b60
u8 cSPUISpace_s0106_78e0::FUN_01067b60()
{
    cSpaceGame* game = (cSpaceGame*)SP_SpaceGameGet();
    u32 flags = game->m50;
    u32 sum = 0;
    if (flags != 0) {
        do {
            sum += (int)kNibbleSum[flags & 15];
            flags >>= 4;
        } while (flags != 0);
        if (sum > 0) return 1;
    }
    cGameTimeManager* gtm = (cGameTimeManager*)SP_GameTimeManager();
    if (gtm->m48 & 1) return 1;
    void* win = mpGlobalUI->FindWindowByID(0x5d6aa28);
    if (win == 0) return 1;
    if ((((cUIWin*)win)->w28() & 2) == 0) return 1;
    SP_GetActivePlanet();
    cSpaceGame* g2 = (cSpaceGame*)SP_SpaceGameGet();
    if (g2->m18->FUN_01075500()) return 1;
    if (((cStateMgr*)SP_GetStateManager())->ShouldShow(0)) return 1;
    if (((cCommManager*)SP_CommManager())->IsActive()) {
        ((cCommManager*)SP_CommManager())->CloseCommEvent();
        return 1;
    }
    void* planet = SP_GetActivePlanet();
    cPlanetInfo* info = 0;
    if (planet != 0) info = (cPlanetInfo*)((cPlanet*)planet)->FUN_00c71e30();
    cStarRecordRef* ref = (cStarRecordRef*)((cPlanet*)planet)->m13c;
    planet = info->m84;
    void* ctx = ref->GetCommContext();
    ((cCommManager*)SP_CommManager())->FUN_00aed2c0(planet, ctx);
    return 1;
}

// @ 0x01067c50
void cSPUISpace_s0106_78e0::SetToolTip(void* a1, void* a2, void* a3, void* a4, void* a5)
{
    cLayoutHolder* h = mpLayoutHolder;
    void* w1 = h->FindWindowByID(0x44ead4f, 1);
    void* w2 = h->FindWindowByID(0x7064a982, 1);
    void* w3 = h->FindWindowByID(0x9064a9b3, 1);
    void* w4 = h->FindWindowByID(0x6550c98, 1);
    if (w1 == 0 || w2 == 0 || w3 == 0 || w4 == 0) return;
    if (a5 != 0) {
        VCallV2(w1, 0x7c, 1, 1);
        SetImageFromKey(w1, a5);
    } else {
        VCallV2(w1, 0x7c, 1, 0);
    }
    float gap = 0.0f;
    if (a2 != 0) {
        VCallV2(w2, 0x7c, 1, 1);
        VCallV1(w2, 0x80, (u32)a2);
        void* x = FUN_005994b0(w2);
        if (x != 0) {
            FUN_01066180(x, 0.0f);
            float* r = (float*)VCallU32(w2, 0x38);
            float d = r[2] - r[0];
            if (d > 0.0f) gap = d;
        }
    } else {
        VCallV2(w2, 0x7c, 1, 0);
    }
    if (a3 != 0) {
        VCallV2(w3, 0x7c, 1, 1);
        VCallV1(w3, 0x80, (u32)a3);
        void* x = FUN_005994b0(w3);
        if (x != 0) FUN_01066180(x, gap);
    } else {
        VCallV2(w3, 0x7c, 1, 0);
    }
    if (a4 != 0) {
        VCallV2(w4, 0x7c, 1, 1);
        VCallV1(w4, 0x80, (u32)a4);
        void* x = FUN_005994b0(w4);
        if (x != 0) FUN_01066180(x, gap);
    } else {
        VCallV2(w4, 0x7c, 1, 0);
    }
    h->FUN_00e369f0();
    h->FUN_00e365a0((u32)a1);
}

// @ 0x01067e70
void cSPUISpace_s0106_78e0::FUN_01067e70(void* p1, Key* key)
{
    void* prof = ((cSpeciesMgr*)SP_GetSettingHost())->GetProfile(*key);
    if (prof == 0) return;
    Key local = *key;
    local.m1 = 0x2f7d0004;
    cTokenTranslator* tt = (cTokenTranslator*)gTokenTranslator;
    tt->m14 = 0;
    tt->m24 = prof;
    void* img = *(void**)((char*)prof + 0x51c);
    SetToolTip(p1, img, mTooltipText.GetText(), 0, &local);
}

// @ 0x01067ef0
Blk28* cSPUISpace_s0106_78e0::FUN_01067ef0(u32 id)
{
    int count = (int)(mpListEnd - mpListBegin);
    for (int i = 0; i < count; ++i) {
        Blk28* e = &mpListBegin[i];
        if (e->mpRef != 0) {
            if (VCallU32(e->mpRef, 0x1c) == id) return e;
        }
    }
    return 0;
}

// @ 0x01067f60
void cSPUISpace_s0106_78e0::FUN_01067f60(u32 on)
{
    cGameInputManager* gim = (cGameInputManager*)SP_GameInputManager();
    if ((u8)on) gim->m110 = gim->m110 + 1;
    else        gim->m110 = gim->m110 - 1;
    void* wm = SP_WindowManager();
    u32 v = ((cUIWin*)wm)->w04();
    if (v != 0 && v != 4) {
        FUN_00812d80(on);
    }
    FUN_01066230(on);
}

// @ 0x01067fb0
u8 cSPUISpace_s0106_78e0::ToggleSlotsUI()
{
    void* w0 = mpGlobalUI->FindWindowByID(0x4359752);
    void* btn = 0;
    if (w0 != 0) btn = (void*)VCallU32a(w0, 0xc, 0x8ed27e7a);
    void* winA = mpGlobalUI->FindWindowByID(0x58d9b3e0);
    void* winB = mpGlobalUI->FindWindowByID(0x52c2948);
    u8 on = 0;
    if ((VCallU8(btn, 0x20) & 4) != 0) {
        void* p = (void*)VCallU32(btn, 0x10);
        if ((VCallU8(p, 0x28) & 2) != 0) on = 1;
    }
    VCallV2(winA, 0x7c, 1, (u32)on);
    void* rec = SP_GetActivePlanetRecord();
    u8 has = 0;
    if (rec != 0 && (((cPlanetRecord*)rec)->mFlags & 0x800) != 0) has = 1;
    VCallV2(winB, 0x7c, 1, (u32)has);
    return on;
}

// @ 0x01068080
u8 cSPUISpace_s0106_78e0::ToggleMinimapUI()
{
    void* w0 = mpGlobalUI->FindWindowByID(0x562a141);
    void* btn = 0;
    if (w0 != 0) btn = (void*)VCallU32a(w0, 0xc, 0x8ed27e7a);
    void* pw = mpGlobalUI->FindWindowByID(0x34c963f);
    u8 on = 0;
    if ((VCallU8(btn, 0x20) & 4) != 0) {
        void* p = (void*)VCallU32(btn, 0x10);
        if ((VCallU8(p, 0x28) & 1) != 0) on = 1;
    }
    VCallV2(pw, 0x7c, 2, (u32)on);
    cString* tip = (on != 0) ? &mMinimapOnTip : &mMinimapOffTip;
    void* host = (void*)VCallU32(btn, 0x10);
    SetTooltipText(host, tip->GetText(), -1, 1);
    return on;
}

// @ 0x01068140
u8 cSPUISpace_s0106_78e0::UpdateStarMapFilters()
{
    void* w0 = mpGlobalUI->FindWindowByID(0x453ef531);
    void* btn = 0;
    if (w0 != 0) btn = (void*)VCallU32a(w0, 0xc, 0x8ed27e7a);
    void* pw = mpGlobalUI->FindWindowByID(0x5d42af0);
    u32 flags = VCallU32(btn, 0x20);
    u8 on = (u8)((flags >> 2) & 1);
    VCallV2(pw, 0x7c, 2, (u32)on);
    cString* tip = (on != 0) ? &mMinimapOnTip : &mMinimapOffTip;
    void* host = (void*)VCallU32(btn, 0x10);
    SetTooltipText(host, tip->GetText(), -1, 1);
    return on;
}

// @ 0x010681e0
void cSPUISpace_s0106_78e0::FUN_010681e0(int a, int b)
{
    if (a > 0 && b < a) {
        ((cWin61c*)mpWindow61c)->FUN_00e31030(kIconTableA[a], 0x622c8b6, 1, 0);
        return;
    }
    ((cWin61c*)mpWindow61c)->FUN_00e31030(kIconTableB[b], 0x622c8b6, 1, 0);
}

// @ 0x01068230
void cSPUISpace_s0106_78e0::FUN_01068230()
{
    u32 h = mAudioHandle;
    cAudioSys* at = (cAudioSys*)SP_GetSystemAT();
    if (at != 0) {
        if (at->a28(h)) {
            FUN_00572020(mAudioHandle, 1);
        }
    }
    if (mpCurrentTool != 0) {
        mpCurrentTool->s3(0);
        if (mpCurrentTool != 0) {
            cToolObj* p = mpCurrentTool;
            mpCurrentTool = 0;
            return p->s1();
        }
    }
}

// @ 0x010682a0
void cSPUISpace_s0106_78e0::FUN_010682a0(u32 id)
{
    if (mpPosse == 0) return;
    void* item = mpPosse->FindItem(id);
    if (item == 0) return;
    VCallV2(mpPosse, 0xa8, (u32)item, 1);
    cPosse* p = mpPosse;
    if (((p->m0a8 - p->m0a4) & 0xfffffff8) == 0) {
        return ((FnV1)((*(void***)p)[0xc0 / 4]))(p, 0);
    }
}

// @ 0x01068300
void cSPUISpace_s0106_78e0::FUN_01068300()
{
    cPosse* p = mpPosse;
    if (p != 0 && ((p->m0a8 - p->m0a4) & 0xfffffff8) != 0) {
        VCallV1(p, 0xc0, 1);
    }
}

// @ 0x01068330
void cSPUISpace_s0106_78e0::FUN_01068330()
{
    if (mpPosse != 0) VCallV1(mpPosse, 0xc0, 0);
}

// @ 0x01068350
bool cSPUISpace_s0106_78e0::FUN_01068350()
{
    if (mpLayout) {
        void* w = mpLayout->FindWindowByID(0x755f180, 1);
        if (w != 0) return (((cUIWin*)w)->w28() & 1) != 0;
    }
    return false;
}

// @ 0x01068450
Blk28* Blk28::CopyCtor(const Blk28& src)
{
    RefObj* r = src.mpRef;
    mpRef = r;
    if (r != 0) r->AddRef();
    m04 = src.m04;
    m08 = src.m08;
    m0c = src.m0c;
    m10 = src.m10;
    m14 = src.m14;
    m18 = src.m18;
    m1c = src.m1c;
    m20 = src.m20;
    m24 = src.m24;
    return this;
}

// @ 0x010684b0
Blk28** FUN_010684b0(Blk28** out, Blk28* begin, Blk28* end, Blk28* dst)
{
    *out = dst;
    while (begin != end) {
        Blk28* d = *out;
        if (d != 0) {
            RefObj* r = begin->mpRef;
            d->mpRef = r;
            if (r != 0) r->AddRef();
            d->m04 = begin->m04;
            d->m08 = begin->m08;
            d->m0c = begin->m0c;
            d->m10 = begin->m10;
            d->m14 = begin->m14;
            d->m18 = begin->m18;
            d->m1c = begin->m1c;
            d->m20 = begin->m20;
            d->m24 = begin->m24;
        }
        *out = *out + 1;
        begin = begin + 1;
    }
    return out;
}

// @ 0x01068530
void FUN_01068530(Blk28* dst, u32 count, const Blk28* src)
{
    if (count == 0) return;
    do {
        if (dst != 0) {
            RefObj* r = src->mpRef;
            dst->mpRef = r;
            if (r != 0) r->AddRef();
            dst->m04 = src->m04;
            dst->m08 = src->m08;
            dst->m0c = src->m0c;
            dst->m10 = src->m10;
            dst->m14 = src->m14;
            dst->m18 = src->m18;
            dst->m1c = src->m1c;
            dst->m20 = src->m20;
            dst->m24 = src->m24;
        }
        count = count - 1;
        dst = dst + 1;
    } while (count != 0);
}

// @ 0x010685a0
Blk28& Blk28::operator=(const Blk28& src)
{
    RefObj* n = src.mpRef;
    RefObj* o = mpRef;
    if (n != o) {
        if (n != 0) n->AddRef();
        mpRef = n;
        if (o != 0) o->Release();
    }
    m04 = src.m04;
    m08 = src.m08;
    m0c = src.m0c;
    m10 = src.m10;
    m14 = src.m14;
    m18 = src.m18;
    m1c = src.m1c;
    m20 = src.m20;
    m24 = src.m24;
    return *this;
}

// @ 0x01068610
Blk28* FUN_01068610(Blk28* begin, Blk28* end, Blk28* dst)
{
    if (begin != end) {
        do {
            if (dst != 0) {
                RefObj* r = begin->mpRef;
                dst->mpRef = r;
                if (r != 0) r->AddRef();
                dst->m04 = begin->m04;
                dst->m08 = begin->m08;
                dst->m0c = begin->m0c;
                dst->m10 = begin->m10;
                dst->m14 = begin->m14;
                dst->m18 = begin->m18;
                dst->m1c = begin->m1c;
                dst->m20 = begin->m20;
                dst->m24 = begin->m24;
            }
            begin = begin + 1;
            dst = dst + 1;
        } while (begin != end);
    }
    return dst;
}

// @ 0x01068710
Blk28* FUN_01068710(Blk28* begin, Blk28* end, Blk28* dst)
{
    if (begin == end) return dst;
    do {
        RefObj* n = (end - 1)->mpRef;
        RefObj* o = (dst - 1)->mpRef;
        end = end - 1;
        dst = dst - 1;
        if (n != o) {
            if (n != 0) n->AddRef();
            dst->mpRef = n;
            if (o != 0) o->Release();
        }
        dst->m04 = end->m04;
        dst->m08 = end->m08;
        dst->m0c = end->m0c;
        dst->m10 = end->m10;
        dst->m14 = end->m14;
        dst->m18 = end->m18;
        dst->m1c = end->m1c;
        dst->m20 = end->m20;
        dst->m24 = end->m24;
    } while (end != begin);
    return dst;
}

// @ 0x010687a0
void FUN_010687a0()
{
    cGameTimeManager* tm = (cGameTimeManager*)SP_GameTimeManager();
    tm->DecPauseGate(0x4bf38a7);
    cSpaceGame* g = (cSpaceGame*)SP_SpaceGameGet();
    cSimThing* p = g ? g->m14 : 0;
    p->FUN_01065d20();
}

// @ 0x010687d0
Blk28* Blk28::Destroy(u8 flags)
{
    ObjRel* o = m08;
    if (o != 0) o->Release();
    if (flags & 1) SP_DeleteArray(this);
    return this;
}

struct ObjV_01068800 {   // the object whose two strings fill the windows
    virtual void vf00();
    virtual void vf04();
    virtual void vf08();
    virtual void vf0c();
    virtual void vf10();
    virtual void vf14();
    virtual void vf18();
    virtual void vf1c();
    virtual void vf20();
    virtual void vf24();
    virtual void vf28();
    virtual void vf2c();
    virtual void vf30();
    virtual void vf34();
    virtual void vf38();
    virtual void vf3c();
    virtual void vf40();
    virtual void vf44();
    virtual void vf48();
    virtual void vf4c();
    virtual void vf50();
    virtual void vf54();
    virtual void vf58();
    virtual void vf5c();
    virtual void vf60();
    virtual void vf64();
    virtual void vf68();
    virtual void vf6c();
    virtual void vf70();
    virtual void vf74();
    virtual void vf78();
    virtual void vf7c();
    virtual void vf80();
    virtual void vf84();
    virtual void vf88();
    virtual void vf8c();
    virtual void vf90();
    virtual void vf94();
    virtual void vf98();
    virtual void vf9c();
    virtual void vfa0();
    virtual void vfa4();
    virtual void vfa8();
    virtual void vfac();
    virtual void vfb0();
    virtual void vfb4();
    virtual void FillLate(EaString16* out);     // +0xb8
    virtual void vfbc();
    virtual void vfc0();
    virtual void vfc4();
    virtual void FillEarly(EaString16* out);    // +0xc8
};
struct WinV_01068800 {   // UTFWin window, only the caption setter is used here
    virtual void vf00();
    virtual void vf04();
    virtual void vf08();
    virtual void vf0c();
    virtual void vf10();
    virtual void vf14();
    virtual void vf18();
    virtual void vf1c();
    virtual void vf20();
    virtual void vf24();
    virtual void vf28();
    virtual void vf2c();
    virtual void vf30();
    virtual void vf34();
    virtual void vf38();
    virtual void vf3c();
    virtual void vf40();
    virtual void vf44();
    virtual void vf48();
    virtual void vf4c();
    virtual void vf50();
    virtual void vf54();
    virtual void vf58();
    virtual void vf5c();
    virtual void vf60();
    virtual void vf64();
    virtual void vf68();
    virtual void vf6c();
    virtual void vf70();
    virtual void vf74();
    virtual void vf78();
    virtual void vf7c();
    virtual void SetCaption(const void* text);  // +0x80
};

// @ 0x01068800
void __stdcall FUN_01068800(void* layout, u32 index, void* obj, u32 unused)
{
    void* w1 = ((FnFind)(*(void***)layout)[0xf0 / 4])(layout, (index + 0x1c2245) << 4, 1);
    ((Fn2)(*(void***)w1)[0x7c / 4])(w1, 1, 1);

    index <<= 4;
    void* w2 = ((FnFind)(*(void***)layout)[0xf0 / 4])(layout, index + 0x1c22451, 1);

    EaString16 sEarly;
    EaString16 sLate;
    sLate.mpBegin = (u32)&DAT_01667bac;
    sLate.mpEnd = (u32)&DAT_01667bac;
    sLate.mpCap = (u32)&DAT_01667bac + 2;
    ((ObjV_01068800*)obj)->FillLate(&sLate);
    ((WinV_01068800*)w2)->SetCaption((void*)sLate.mpBegin);

    void* w3 = ((FnFind)(*(void***)layout)[0xf0 / 4])(layout, index + 0x1c22452, 1);
    if (w3 != 0) {
        sEarly.mpBegin = (u32)&DAT_01667bac;
        sEarly.mpEnd = (u32)&DAT_01667bac;
        sEarly.mpCap = (u32)&DAT_01667bac + 2;
        ((ObjV_01068800*)obj)->FillEarly(&sEarly);
        ((WinV_01068800*)w3)->SetCaption((void*)sEarly.mpBegin);
        if ((s32)((sEarly.mpCap - sEarly.mpBegin) & 0xfffffffeu) > 2 && sEarly.mpBegin != 0)
            op_del_array((void*)sEarly.mpBegin);
    }

    void* w4 = ((FnFind)(*(void***)layout)[0xf0 / 4])(layout, index + 0x1c22454, 1);
    if (w4 != 0) {
        void* key = ((Obj3*)obj)->FUN_c45ca0(&sEarly);
        SP_SetImageFromKey(w4, key);
        void* mgr = SP_GetMissionManager(obj);
        u32 v = ((MissionMgr*)mgr)->FUN_febf80();
        ((Fn1)(*(void***)w4)[0x5c / 4])(w4, v);
    }

    if ((s32)((sLate.mpCap - sLate.mpBegin) & 0xfffffffeu) > 2 && sLate.mpBegin != 0)
        op_del_array((void*)sLate.mpBegin);
}

// @ 0x01068970
bool __stdcall FUN_01068970(void* layoutRaw, u32 index, void* slotRaw)
{
    Layout* layout = (Layout*)layoutRaw;
    Slot* slot = (Slot*)slotRaw;
    if (index >= 5) return false;
    if (slot->FUN_b8d970()) return false;
    switch (slot->mn28) {
    case 2: case 3: case 4: case 5:
        break;
    default:
        return false;
    }

    u32 color;
    u32 flag18 = 1;
    void* tf = TerraformingManagerFn(slot);
    if (((TfMgr*)tf)->FUN_bbc670() > 0) {
        color = 0xff7dd244;
    } else {
        f32 v = slot->mfB4;
        if (v > *(f32*)0x1485544)
            color = 0xffd42727;
        else if (*(f32*)0x13eb8a0 > v)
            color = 0xff21a5e7;
        else
            color = 0xffffffff;
    }
    if (slot->FUN_b8dac0())
        flag18 = 2;

    void* w1 = layout->FindWindowByID((index + 0x684bc0) << 4, 1);
    if (w1 == 0) return false;
    ((FnWin2)(*(void***)w1)[0x7c / 4])(w1, 1, 1);

    index <<= 4;
    void* w2 = layout->FindWindowByID(index + 0x684bc01, 1);
    void* w3 = layout->FindWindowByID(index + 0x684bc02, 1);
    void* w4 = layout->FindWindowByID(index + 0x684bc03, 1);
    void* w5 = layout->FindWindowByID(index + 0x684bc07, 1);

    ((FnWin2)(*(void***)w2)[0x7c / 4])(w2, 1, 0);
    ((FnWin2)(*(void***)w3)[0x7c / 4])(w3, 1, 0);
    ((FnWin2)(*(void***)w4)[0x7c / 4])(w4, 1, 0);
    ((FnWin2)(*(void***)w5)[0x7c / 4])(w5, 1, 0);

    void* wsel;
    switch (flag18) {
    case 0: wsel = w4; break;
    case 1: wsel = w3; break;
    case 2: wsel = w5; break;
    default: wsel = 0; break;
    }
    ((FnWin2)(*(void***)wsel)[0x7c / 4])(wsel, 1, 1);
    ((FnWin1)(*(void***)wsel)[0x5c / 4])(wsel, color);

    void* w6 = layout->FindWindowByID(index + 0x684bc05, 1);
    u32 countPos = (slot->FUN_b8dab0() > 0);
    ((FnWin2)(*(void***)w6)[0x7c / 4])(w6, 1, countPos);

    if (FUN_01021370() == slot) {
        SP_SetImageFromKey(w6, (void*)0x15b9124);
    } else {
        void* empire = FUN_01021300(0);
        if (FUN_00c70150(slot, empire)) {
            SP_SetImageFromKey(w6, (void*)0x15b9118);
        } else if (countPos != 0) {
            SP_SetImageFromKey(w6, FUN_00e2eba0(slot));
        }
    }

    void* profile;
    if (slot->FUN_b8dab0() < 2) {
        profile = 0;
    } else {
        void* mgr = GetSetting9(slot->FUN_b8e090());
        profile = ((SpeciesMgr_s0106_8800*)mgr)->GetProfile();
    }

    void* w7 = layout->FindWindowByID(index + 0x684bc04, 1);
    void* w8 = layout->FindWindowByID(index + 0x684bc06, 1);
    u32 keyBuf[3];
    if (profile != 0) {
        void* key = GetDominantSpeciesThumbnailKey(keyBuf, (u32)slot);
        SP_SetImageFromKey(w7, key);
    }
    ((FnWin2)(*(void***)w7)[0x7c / 4])(w7, 1, (u32)(profile != 0));

    void* effect = slot->FUN_ecdba0();
    ((FnWin1)(*(void***)w8)[0x80 / 4])(w8, *(u32*)effect);
    ((FnWin2)(*(void***)w8)[0x7c / 4])(w8, 1, 1);

    if (slot->FUN_b8dab0() > 0) {
        u32 k;
        slot->FUN_b8dd60(&k);
        if (k != 0x6334d0ad && k != 0x4f3d572f) {
            AutoRef prop;
            prop.mpObject = 0;
            u32 out = 0;
            void* pm = SP_PropertyManager2();
            void* keyObj = slot->FUN_b8dad0();
            void** pp = prop.AsPPVoidParam();
            ((Fn3P)(*(void***)pm)[0x2c / 4])(pm, *(u32*)keyObj, 0x34d97fa, pp);
            if (SP_GetPropertyAsUint32(prop.mpObject, 0x58cbb75, &out)) {
                ((FnWin1)(*(void***)w5)[0x5c / 4])(w5, out | 0xff000000);
                ((FnWin2)(*(void***)w5)[0x7c / 4])(w5, 1, 1);
            }
            if (prop.mpObject != 0)
                ((FnV0)(*(void***)prop.mpObject)[4 / 4])(prop.mpObject);
        }
    }
    return true;
}

// @ 0x01068d30
void __stdcall FUN_01068d30(volatile u32 a1, Vec3* v, u8 a3, u8 a4, u32 a5, u32 a6)
{
    TfSlot* slot = FUN_01067ef0(a1);
    if (slot == 0) return;
    void* obj = slot->mpObj00;
    if (obj == 0) return;

    void* sub = ((FnC0)(*(void***)obj)[0xc / 4])(obj, 0x8ed27e7a);
    slot->mn04 = v->x;
    slot->mn08 = v->y;
    slot->mn0C = v->z;

    u8 a1flag = (u8)a1;
    if (a4 != 0) {
        if (a1flag == 0) {
            if (slot->mn18 != 2) {
                ((FnV1_s0106_8800)(*(void***)sub)[0x1c / 4])(sub, 1);
                FUN_00807cb0(obj, (void*)0x15b936c, 0);
                FUN_00807cb0(obj, (void*)0x15b9378, 2);
                FUN_00807cb0(obj, (void*)0x15b9384, 3);
            }
            slot->mn18 = 2;
            return;
        }
    } else {
        if (a1flag == 0 &&
            (v->x != *(u32*)0x16e224c || v->y != *(u32*)0x16e2250 || v->z != *(u32*)0x16e2254)) {
            if (slot->mn18 != 0 || slot->mb1C != a3) {
                ((FnV1_s0106_8800)(*(void***)sub)[0x1c / 4])(sub, 2);
                if (a3 == 0) {
                    FUN_00807cb0(obj, (void*)0x15b9300, 0);
                    FUN_00807cb0(obj, (void*)0x15b930c, 2);
                    FUN_00807cb0(obj, (void*)0x15b9318, 3);
                    FUN_00807cb0(obj, (void*)0x15b9324, 4);
                    FUN_00807cb0(obj, (void*)0x15b9330, 6);
                    FUN_00807cb0(obj, (void*)0x15b933c, 7);
                } else {
                    FUN_00807cb0(obj, (void*)0x15b92b8, 0);
                    FUN_00807cb0(obj, (void*)0x15b92c4, 2);
                    FUN_00807cb0(obj, (void*)0x15b92d0, 3);
                    FUN_00807cb0(obj, (void*)0x15b92dc, 4);
                    FUN_00807cb0(obj, (void*)0x15b92e8, 6);
                    FUN_00807cb0(obj, (void*)0x15b92f4, 7);
                }
            }
            ((FnV2_s0106_8800)(*(void***)sub)[0x28 / 4])(sub, 4, a5);
            ((FnV0)(*(void***)obj)[0x90 / 4])(obj);
            slot->mb1C = a3;
            slot->mn18 = 0;
            return;
        }
    }

    if (v->x == *(u32*)0x16e224c && v->y == *(u32*)0x16e2250 && v->z == *(u32*)0x16e2254 && a1flag == 0) {
        if (slot->mn18 != 3) {
            ((FnV1_s0106_8800)(*(void***)sub)[0x1c / 4])(sub, 1);
            FUN_00807cb0(obj, (void*)0x15b9348, 0);
            FUN_00807cb0(obj, (void*)0x15b9354, 2);
            FUN_00807cb0(obj, (void*)0x15b9360, 3);
        }
        slot->mn18 = 3;
        slot->mb1C = 0;
    } else {
        slot->mn18 = 1;
        slot->mb1C = 0;
    }
}

// @ 0x01068f70
void Space::FUN_01068f70()
{
    void* prop = 0;
    void* out;
    void* pm = SP_PropertyManager();
    if (prop != 0) {
        void* old = prop;
        prop = 0;
        ((FnV)(*(void***)old)[4 / 4])(old);
    }
    ((Fn3P)(*(void***)pm)[0x2c / 4])(pm, 0xddb63e53, 0x2ae0c7e, &prop);

    TF_LOAD(mVal544, 0x680fae3);
    TF_LOAD(mVal548, 0x680fae4);
    TF_LOAD(mVal54C, 0x680fae5);
    TF_LOAD(mVal550, 0x680fae6);
    TF_LOAD(mVal554, 0x680fae7);
    TF_LOAD(mVal558, 0x680fb1b);
    TF_LOAD(mVal55C, 0x680fb1c);
    TF_LOAD(mVal560, 0x680fb1d);
    TF_LOAD(mVal564, 0x680fb1e);

    if (prop != 0)
        ((FnV)(*(void***)prop)[4 / 4])(prop);
}

// @ 0x010691e0
void SP::cSPUISpace_s0106_91e0::UpdateStarRollover(SP::cStarRecord_s0106_91e0* pStar)
{
    int modeState;
    if (SP::FUN_00b3d4a0_s0106_91e0()->FUN_00ae9390() ||
        SP::FUN_00b3d3f0()->FUN_00e18c70(0) ||
        SP::FUN_00b3d230_s0106_91e0()->FUN_00b5ca60() ||
        (modeState = SP::FUN_00b3d4d0_s0106_91e0()->mState) == 1 || modeState == 2 ||
        SP::WindowManager_s0106_91e0()->GetModalWindow() != 0)
    {
        mStarRolloverRoot->SetFlag(1, false);
        DetachFromParent(mStarRolloverRoot);
        DetachFromParent(mMissionRolloverRoot);
        SPUIHelpers::DestroyRolloverFrame(mStarRolloverFrame);
        mStarRolloverFrame.Clear();
        mStarRolloverText.Clear();
        return;
    }

    bool bShow = false;
    IWindow_s0106_91e0* pText = mStarRolloverRoot->FindWindowByID(0x1c22501, true);
    if (!pText)
        goto finish;

    {
        SP::cSimObject* pObj = SP::FUN_01036e20();
        if (!pObj) {
            if (mStarRolloverText && mStarRolloverFrame) {
                DetachFromParent(mStarRolloverRoot);
                DetachFromParent(mMissionRolloverRoot);
                SPUIHelpers::DestroyRolloverFrame(mStarRolloverFrame);
                mStarRolloverFrame.Clear();
                mStarRolloverText.Clear();
            }
            mStarRolloverText.Clear();
            goto finish;
        }

        int* pRows = SP::FUN_0067dd50()->GetRowSpan();
        float fRow = (float)pRows[2] - 1.0f;
        float fCol = (float)pRows[3] - 1.0f;
        bShow = true;

        if (mStarRolloverText == pObj->mpText_0d4) {
            SPUIHelpers::UpdateRolloverFrame(mStarRolloverFrame, fRow, fCol, 1, 0.0f);
        } else {
            mStarRolloverText = pObj->mpText_0d4;

            IWindow_s0106_91e0* pOwnerBlock  = mStarRolloverRoot->FindWindowByID(0x684c020, true);
            IWindow_s0106_91e0* pEmpireIcon  = mStarRolloverRoot->FindWindowByID(0x1c22519, true);
            IWindow_s0106_91e0* pPlanetBlock = mStarRolloverRoot->FindWindowByID(0x4cad958, true);
            IWindow_s0106_91e0* pWeaponMeter = mStarRolloverRoot->FindWindowByID(0x1c22518, true);
            IWindow_s0106_91e0* pOwnerColor  = mStarRolloverRoot->FindWindowByID(0x5e62728, true);
            IWindow_s0106_91e0* pTravelText  = mStarRolloverRoot->FindWindowByID(0x6270638, true);

            if (pOwnerBlock)  pOwnerBlock->SetFlag(1, false);
            if (pEmpireIcon)  pEmpireIcon->SetFlag(1, false);
            if (pPlanetBlock) pPlanetBlock->SetFlag(1, false);
            if (pWeaponMeter) pWeaponMeter->SetFlag(1, false);
            if (pOwnerColor)  pOwnerColor->SetFlag(1, false);
            if (pTravelText)  pTravelText->SetFlag(1, false);

            pTravelText->SetCaption(((SP::cStarRecord_s0106_91e0*)pStar)->GetName()->c_str());

            const Math::Rectangle& area = mStarRolloverRoot->GetArea();
            float x1 = area.x1;
            float y1 = area.y1;
            float x2 = area.x2;
            float y2 = area.y1 + SP::kRolloverBlockHeight;
            mStarRolloverRoot->SetArea(Math::Rectangle(x1, y1, x2, y2));
            mStarRolloverRoot->SetLocation(0.0f, 0.0f);

            if (mStarRolloverFrame) {
                DetachFromParent(mStarRolloverRoot);
                DetachFromParent(mMissionRolloverRoot);
                SPUIHelpers::DestroyRolloverFrame(mStarRolloverFrame);
                mStarRolloverFrame.Clear();
            }
            EA::AutoRefCount_s0106_91e0<IWindow_s0106_91e0> pContainer;
            mStarRolloverFrame = SPUIHelpers::CreateRolloverFrame(
                L"RolloverFrameGeneric", fRow, fCol, x2 - x1, y2 - y1,
                pContainer.AsPPTypeParam(), 1, 1, 0.0f, 0xe9f70df9);
            DetachFromParent(mStarRolloverRoot);
            pContainer->AddWindow(mStarRolloverRoot);
        }
    }

finish:
    if (mStarRolloverRoot)
        mStarRolloverRoot->SetFlag(1, bShow);
}

// @ 0x010697b0
void SP::cSPUISpace_s0106_91e0::FUN_010697b0(SP::cCivData_s0106_91e0* pCiv)
{
    SP::cSpaceGfx::cSlot* pSlot = SP::GetSpaceGfx()->mSlot30.mpObject;
    if (!pCiv) {
        pSlot->Show(false);
        SP::GetSpaceGfx()->mSelectedID = 0;
        return;
    }

    SP::cCivData_s0106_91e0* pActive = SP::FUN_01021240();
    if (pCiv == pActive) {
        pSlot->Show(false);
        SP::GetSpaceGfx()->mSelectedID = 0;
        return;
    }

    SP::cCityRuntime** pCities = (SP::cCityRuntime**)pCiv->GetCities();
    SP::cPlayerInventory* pInv = SP::GetUFOSimulator_s0106_91e0()->GetPlayerInventory();
    Vector3_s0106_91e0 vPos(0.0f, 0.0f, 0.0f);
    if (pInv->mFlag74c == 1) {
        if (pCiv == SP::GetSpaceGfx()->mSelectedID)
            return;
        vPos = *(Vector3_s0106_91e0*)pActive->GetCities();
        SP::GetSpaceGfx()->mSelectedID = pCiv;
    } else {
        vPos = SP::GetUFOSimulator_s0106_91e0()->GetPlayerInventory()->mpCivList_34->GetPosition();
    }

    bool bReachable = SP::GetUFOSimulator_s0106_91e0()->FUN_00ffc8d0(pCiv);
    int nCost = SP::GetUFOSimulator_s0106_91e0()->FUN_00ffc4e0(pActive, pCiv);
    if (bReachable) {
        int nLimit = SP::FUN_01021300()->FUN_00c30cb0();
        if (nCost <= nLimit)
            goto havePos;
    }
    vPos = Vector3_s0106_91e0(0.05f, 0.05f, 1.0f);

havePos:
    pSlot->Show(true);

    SP::cSpaceGfx* pGfx = SP::GetSpaceGfx();
    SP::cSpaceGfx::cEffectsMgr* pEffects = pGfx->mpEffectsMgr94;
    pGfx->mSlot30.Clear();
    pEffects->CreateVisualEffect(0x840cea6, 0, (void**)&pGfx->mSlot30);

    SP::cSpaceGfx::cSlot* pSlot2 = SP::GetSpaceGfx()->mSlot30.mpObject;
    if (!pSlot2->IsVisible())
        pSlot2->Use(0);

    EffectTransform xform;
    xform.mOffset = Vector3_s0106_91e0(SP::kFxOffsetX, SP::kFxOffsetY, SP::kFxOffsetZ);
    xform.mFlags = 0;
    xform.mnChangeCount = 0;
    xform.mfScale = 1.0f;
    SP::Matrix3_Assign(&xform.mMatrix, &SP::kFxMatrixSrc);
    xform.mFlags |= 4;
    xform.mnChangeCount++;
    xform.mOffset = vPos;
    pSlot2->SetTransform(xform);

    SP::FUN_01043d10(0, 0, 0, SP::kEffectFade, 0);
    pSlot2->SetParams(0xd, 0, 0);
    pSlot2->SetParams(5, 0, 3);

    (void)pCities;
}

// @ 0x01069aa0
void SP::cSPUISpace_s0106_91e0::FUN_01069aa0()
{
    SP::Rect4 area;
    SP::SPUIHelpers_GetMainWindowArea(&area);
    float cx = (area.y2 - area.y1) * 0.5f + 5.0f;

    int nCaptureBars = UpdateCaptureBarsVisibility(SP::FUN_01021240());
    IWindow_s0106_91e0* pWindow = mpGlobalUI->FindWindowByID(0x65680f8);
    if (!pWindow)
        return;

    pWindow->SetFlag(1, nCaptureBars > 0);
    int nRows = 0;
    bool bSeti = false;
    float fY = 10.0f;
    if (nCaptureBars > 0) {
        const Math::Rectangle& wa = pWindow->GetArea();
        float x1 = wa.x1, y1 = wa.y1, x2 = wa.x2, y2 = wa.y2;
        float pos = (cx - y2) * 0.5f - (x2 - x1) * 0.5f;
        pWindow->SetLocation(pos, 0.0f);

        const Math::Rectangle& wa2 = pWindow->GetArea();
        Math::Rectangle r(wa2.x1, wa2.y1, wa2.x2, (float)nCaptureBars * 25.0f + 49.0f);
        pWindow->SetArea(r);

        this->FUN_010677b0(SP::FUN_01021240(), cx, 13.0f, false);

        IWindow_s0106_91e0* pBar = mpGlobalUI->FindWindowByID(0x6567050);
        if (pBar) {
            pBar->SetFlag(1, mpCaptureMeterA && mpCaptureMeterA->IsVisible());
            if (mpCaptureMeterA && mpCaptureMeterA->IsVisible()) {
                const Math::Rectangle& ba = pBar->GetArea();
                pBar->SetLocation(ba.x1, 10.0f);
                fY = 35.0f;
            }
        }
        pBar = mpGlobalUI->FindWindowByID(0x6567051);
        if (pBar)
            pBar->SetFlag(1, mpCaptureMeterB && mpCaptureMeterB->IsVisible());
        if (mpCaptureMeterB && mpCaptureMeterB->IsVisible()) {
            if (pBar) {
                const Math::Rectangle& ba = pBar->GetArea();
                pBar->SetLocation(ba.x1, fY);
                fY = fY + 25.0f;
            }
            void* pList = SP::FUN_00bba790(SP::FUN_01021240());
            SP::cCityRuntime** pBegin = *(SP::cCityRuntime***)pList;
            int nCities = (int)((SP::cCityRuntime**)(*(SP::cCityRuntime***)((char*)pList + 4) - pBegin));
            bSeti = true;
            for (int i = 0; i < nCities; i++) {
                SP::cCityRuntime* pCity = pBegin[i];
                if (pCity->mState == 1 || pCity->mState == 0)
                    continue;
                if (pCity->FUN_00b8d970())
                    continue;
                if (pCity->FUN_00b8dab0() != 5)
                    continue;
                if (nRows >= 5)
                    goto nextCity;

                {
                    IWindow_s0106_91e0* pMeter = mpGlobalUI->FindWindowByID(SP::gStarMeterIDs[nRows]);
                    SP::cMeterHolder* pHolder = SP::FUN_00deced0(pMeter);
                    bool bVisible = pMeter != 0 && pMeter->_v28();
                    if (pMeter && !bVisible)
                        pMeter->SetFlag(1, true);

                    int empireID = -1;
                    float fDist = SP::FUN_00c8c7f0(pCity, &empireID);
                    if (fDist < 100.0f || empireID == SP::FUN_01021090()) {
                        if (pHolder->mMeter.GetState() != 0 || !bVisible) {
                            SP::gpSpaceTokenTranslator->mpCity = pCity;
                            SP::SPUIHelpers_SetTooltipText(pMeter, mStarTooltipA.GetText());
                            pHolder->mMeter.SetValue(-1);
                        }
                        bSeti = false;
                    } else {
                        if (pHolder->mMeter.GetState() != 1 || !bVisible) {
                            SP::gpSpaceTokenTranslator->mpCity = pCity;
                            SP::SPUIHelpers_SetTooltipText(pMeter, mStarTooltipB.GetText());
                            pHolder->mMeter.SetValue(1);
                        }
                    }
                    nRows++;
                }
nextCity:
                ;
            }

            IWindow_s0106_91e0* pHeight = mpGlobalUI->FindWindowByID(0x65b9b00);
            if (pHeight) {
                const Math::Rectangle& ha = pHeight->GetArea();
                pHeight->SetLocation((float)(5 - nRows) * 16.5f + 27.0f, ha.y1);
            }
        }
    }

    IWindow_s0106_91e0* pSetiFrame = mpGlobalUI->FindWindowByID(0x65680e8);
    if (pSetiFrame) {
        pSetiFrame->SetFlag(1, bSeti);
        if (bSeti) {
            const Math::Rectangle& sa = pSetiFrame->GetArea();
            pSetiFrame->SetLocation(sa.x1, fY + 5.0f);
        }
    }

    IWindow_s0106_91e0* pTrade = mpGlobalUI->FindWindowByID(0x65ce2da);
    if (pTrade) {
        SP::cSpaceTradeRouteManager_s0106_91e0* pMgr = SP::StarManager_s0106_91e0()->FUN_00ba6490();
        float fTrade = pMgr->SystemHasTradeRouteWithPlayer(
            *(int*)((char*)SP::FUN_01021240() + 0x70),
            ((SP::cGameNounManager_s0106_91e0*)SP::FUN_01021240())->GetAvatar());
        pTrade->SetFlag(1, fTrade >= 100.0f);
        if (fTrade >= 100.0f) {
            const Math::Rectangle& ta = pTrade->GetArea();
            pTrade->SetLocation(ta.x1, fY + 5.0f);
        }
    }

    if (nRows < 5) {
        for (int i = nRows; i < 5; i++) {
            IWindow_s0106_91e0* pMeter = mpGlobalUI->FindWindowByID(SP::gStarMeterIDs[i]);
            if (pMeter)
                pMeter->SetFlag(1, false);
        }
    }
}

// @ 0x0106a0a0
u32 cSPUISpace_s0106_a0a0::UpdateMissionRollover(u32 a0, u32 a1, u32 a2, u32 a3)
{
    void* nm = SP_GetNounManager();
    u8 bl = ((cNounManager*)nm)->FUN_00b5ca60();
    void* gl = mGlowInfoList;
    VCallV2u(gl, 0xf0, 0x1c22446, 1);
    int count = 0;
    u8 any = 0;
    if (bl == 0) {
        void* mm = SP_GetMissionManager();
        void** list = ((cMissionManager*)mm)->GetMissionList();
        void** it = (void**)list[0];
        void** end = (void**)list[1];
        if (it != end) {
            do {
                cMission* m = (cMission*)*it;
                if (m->IsActive() != 0 && *(u32*)((char*)m + 0x17c) == 0) {
                    void* model = m->GetModel();
                    if (model != 0) {
                        int ok = 0;
                        if (a1 != 0 && a1 == (u32)model) ok = 1;
                        else if (a2 != 0 &&
                                 a2 == (u32)((cBannerSort*)((char*)model + 0x13c))->SortBanners()) ok = 1;
                        if (ok && count < 3) {
                            any = 1;
                            FUN_01068800((u32)gl, (void*)m, 1);
                            count++;
                        }
                    }
                }
                it++;
            } while (it != end);
            if (any != 0) {
                VCallV2f_s0106_a0a0(gl, 0x64, *(float*)&a3, 0.0f);
                float* p = (float*)VCallP0(gl, 0x34);
                float v[4];
                v[0] = p[0];
                v[1] = p[1];
                v[2] = p[2];
                v[3] = *(float*)&a1;
                int n = count * 0x22;
                if (n < 0) v[3] = (float)n + kFNeg10000;
                VCallV1p(gl, 0x60, v);
            }
        }
    }
    if (count < 3) {
        u32 id = (u32)(count + 0x1c2245) << 4;
        int n = 3 - count;
        do {
            void* w = VCallP2(gl, 0xf0, id, 1);
            VCallV2u(w, 0x7c, 1, 0);
            id += 0x10;
            n--;
        } while (n != 0);
    }
    VCallV2u(gl, 0x7c, 1, (u32)any);
    if (any == 0) return 0;
    return (u32)mGlowInfoList;
}

// @ 0x0106a280
void cSPUISpace_s0106_a0a0::FUN_0106a280()
{
    void* home = SP_GetPlayerHomePlanet();
    cCivData* civ = (cCivData*)((cBannerSort*)home)->SortBanners();
    cCivData* rec = (cCivData*)SP_IsPlanetArchived();
    if (civ == 0 || rec == 0) return;

    cUIWin_s0106_a0a0* w0 = (cUIWin_s0106_a0a0*)mpGlobalUI->FindWindowByID(0x616ebc0);
    cUIWin_s0106_a0a0* w1 = (cUIWin_s0106_a0a0*)mpGlobalUI->FindWindowByID(0x616ebb8);
    cUIWin_s0106_a0a0* w2 = (cUIWin_s0106_a0a0*)mpGlobalUI->FindWindowByID(0x6174050);
    if (w0 == 0 || w1 == 0 || w2 == 0) return;

    FUN_01066630(civ->GetCities(0, 0));
    FUN_01066630(rec->GetCities(0, 0));

    {
        cString s(0xf5e156f8, 0x66dde72, (const wchar_t*)0x149c250);
        SetTooltipText(w2, s.GetText(), -1, 1);
    }
    float* pf0 = (float*)w0->w38();
    float len = pf0[2] - pf0[0];
    float* pf1 = (float*)w1->w38();
    float f = ((pf1[2] + pf1[0]) * kFHalf) / len;
    float ratio;
    if (*(float*)&civ <= *(float*)&rec) {
        ratio = (kFOne - *(float*)&civ / *(float*)&rec) * (kFOne - f) + f;
    } else {
        ratio = (kFOne - (*(float*)&civ - *(float*)&rec) / (kF10000 - *(float*)&rec)) * f;
    }
    float v = ratio;
    if (ratio > 1.0f) v = 1.0f;
    else if (ratio < 0.0f) v = 0.0f;
    v = v * len;
    float* pw = (float*)w2->w38();
    w2->w70(v - (pw[2] - pw[0]) * kFHalf, pw[1]);

    cUIWin_s0106_a0a0* w3 = (cUIWin_s0106_a0a0*)mpGlobalUI->FindWindowByID(0x616ebc8);
    if (w3 != 0) {
        float* pf = (float*)w3->w38();
        w3->w74(0.0f, pf[3] - pf[1]);
    }
}

// @ 0x0106a4e0
void cSPUISpace_s0106_a0a0::UpdateActivePlanetInfo()
{
    u8 flag = 0;
    if (mpGlobalLayout != 0) {
        cUIWinNoArgs* w = (cUIWinNoArgs*)mpGlobalLayout->FindWindowByID(0x755f180, 1);
        if (w != 0) flag = (u8)(w->w28() & 1);
    }
    FUN_01066230(flag);
    void* planet = SP_GetActivePlanet();
    void* rec = SP_GetActivePlanetRecord();
    *(void**)((char*)gSpaceTokenTranslator + 0xc) = rec;

    int level;
    cUIWin_s0106_a0a0* pw = (cUIWin_s0106_a0a0*)mpGlobalUI->FindWindowByID(0x562a2da);
    if (pw != 0) {
        if (planet != 0) {
            pw->w80(((cPlanet_s0106_a0a0*)planet)->GetName());
        } else if (FUN_01021230() != 0) {
            pw->w80((void*)FUN_00c8b540());
        } else {
            pw->w80((void*)0x13ec468);
        }
        level = (int)FUN_00c70e00();
    } else if (planet != 0) {
        level = (int)FUN_00c70e00();
    } else {
        level = 0;
    }

    {
        cUIWin_s0106_a0a0* w = (cUIWin_s0106_a0a0*)mpGlobalUI->FindWindowByID(0x36fe7c1);
        if (w != 0) {
            bool has = 0 < level;
            w->w7c(1, has);
            if (has) {
                u32* pi = (u32*)planet;
                if (pi[0x4f] == (u32)SP_GetPlayerHomePlanet()) {
                    SetImageFromKey(w, (void*)0x15b9124);
                } else if (((cEmpire*)planet)->FUN_00c30910() == 0) {
                    SetImageFromKey(w, (void*)FUN_00e2eba0((void *)pi[0x4f]));
                    cString s(0x2db6dad3, 0x473d0cf, 0);
                    SetTooltipText(w, s.GetText(), -1, 1);
                } else {
                    SetImageFromKey(w, (void*)0x15b9118);
                }
            }
        }
    }

    cUIWin_s0106_a0a0* wa = (cUIWin_s0106_a0a0*)mpGlobalUI->FindWindowByID(0x36c0957);
    cUIWin_s0106_a0a0* wb = (cUIWin_s0106_a0a0*)mpGlobalUI->FindWindowByID(0x44d94d1);
    if (level < 2 || wa == 0 || wb == 0) {
        wb->w7c(1, 0);
        wa->w7c(1, 0);
    } else {
        cString s(0x2db6dad3, 0x3e81c64, 0);
        wb->w80(s.GetText());
        wb->w7c(1, 1);
        SetTooltipText(wb, s.GetText(), -1, 1);
        u32 key;
        SetImageFromKey(wa, GetDominantSpeciesThumbnailKey(&key, ((u32*)planet)[0x4f]));
        wa->w7c(1, 1);
    }

    cUIWin_s0106_a0a0* wc = (cUIWin_s0106_a0a0*)mpGlobalUI->FindWindowByID(0x6748980);
    if (wc != 0) {
        u8 v = 0;
        if (planet != 0) v = FUN_00c70b50();
        wc->w7c(1, v);
    }
}

// @ 0x0106a7b0
void cSPUISpace_s0106_a0a0::UpdateCommButtons(void* outState, void* outColor)
{
    u8 show = 0;
    u8 cam = 0;
    *(u32*)outColor = 0xffffffff;
    void* planet = SP_GetActivePlanet();
    if (planet == 0) goto tail;
    {
        void* p13c = *(void**)((char*)planet + 0x13c);
        cEmpire* emp = (cEmpire*)((cPlanet_s0106_a0a0*)planet)->FUN_00c71e30();
        if (emp != 0 && p13c != 0) {
            cGameNounManager_s0106_a0a0* gnm = (cGameNounManager_s0106_a0a0*)SP_SpaceGameGet();
            void* avatar = gnm->GetAvatar();
            u8 bVar2;
            if (((cGameInputManager_s0106_a0a0*)SP_GetSystemNounManager())->FUN_00e393b0() != 0) bVar2 = 1;
            else if (FUN_01065b30() != 0) bVar2 = 1;
            else if (((cTriggerManager*)SP_GetTriggerManager())->FUN_00ac80f0() != 0) bVar2 = 1;
            else if (avatar != 0 && ((cAvatar*)avatar)->FUN_00ff6360() != 0) bVar2 = 1;
            else bVar2 = 0;

            u8 bVar3;
            if (SP_GetUniverseContext() == 2) {
                bVar3 = 1;
            } else if (SP_GetUniverseContext() == 1 &&
                       ((cSpaceInventory*)((cUFOSimulator*)SP_GetUFOSimulator())->GetPlayerInventory())->m74c == 0) {
                bVar3 = 1;
            } else {
                bVar3 = 0;
            }

            if (bVar2 || bVar3) {
                show = 0;
                cam = 0;
            } else {
                show = 1;
                cam = 0;
                if (emp->FUN_00c30910() != 0) {
                    if (((cCommMgr*)SP_CommManager())->SpaceToolSelect(emp->m84,
                            ((cStarRecordRef*)p13c)->GetCommContext()) != 0) {
                        if (((cHud*)SP_GetHUDSpaceFrame())->IsShown() != 0) cam = 1;
                    }
                } else {
                    if (((cHud*)SP_GetHUDSpaceFrame())->IsShown() != 0) cam = 1;
                }
            }

            u32 color;
            *(u32*)outColor = FUN_00458a40(emp->GetColor(&color));
        }
    }
tail:
    {
        u8 active;
        if (((cCommScreen*)SP_CommManager())->IsActive() == 0) {
            bool flag = false;
            if (mpGlobalLayout != 0) {
                cUIWinNoArgs* w = (cUIWinNoArgs*)mpGlobalLayout->FindWindowByID(0x755f180, 1);
                if (w != 0 && (w->w28() & 1) != 0) flag = true;
            }
            active = (u8)flag;
        } else {
            active = 1;
        }
        if (cam != 0 && active == 0) { *(u32*)outState = 1; return; }
        if (show != 0 && active == 0) { *(u32*)outState = 0; return; }
    }
    *(u32*)outState = 2;
}

// @ 0x0106a970
void cSPUISpace_s0106_a0a0::FUN_0106a970()
{
    cSPUISpace_s0106_a0a0* self = this;
    UpdateCommButtons(&mDial, &self);
    cUIWin_s0106_a0a0* w0 = (cUIWin_s0106_a0a0*)mpGlobalUI->FindWindowByID(0x5d6aa28);
    cUIWin_s0106_a0a0* w1 = (cUIWin_s0106_a0a0*)mpGlobalUI->FindWindowByID(0x17f29bf);
    cUIWin_s0106_a0a0* w2 = (cUIWin_s0106_a0a0*)mpGlobalUI->FindWindowByID(0x61b0530);
    if (w0 != 0 && w1 != 0 && w2 != 0) {
        w0->w7c(2, mDial != 2);
        w1->w7c(2, mDial != 2);
        w2->w7c(2, mDial == 1);
    }
}

// @ 0x0106aa10
void cSPUISpace_s0106_a0a0::FUN_0106aa10(u32 on)
{
    if (m5d0 == 0) {
        if (m238->FUN_00ff3f00() == 0) {
            cUIWin_s0106_a0a0* w = (cUIWin_s0106_a0a0*)mpGlobalUI->FindWindowByID(0x4359752);
            cUIWin_s0106_a0a0* p = (w != 0) ? (cUIWin_s0106_a0a0*)w->w0c(0x8ed27e7a) : 0;
            u32 v = p->w20();
            if (((v >> 2) & 1) != (u8)on) {
                p->w28(4, on);
                ToggleSlotsUI();
            }
            m5d1 = (u8)on;
        } else {
            m5d1 = (u8)on;
        }
    } else {
        m5d1 = (u8)on;
    }
}

// @ 0x0106aab0
void cSPUISpace_s0106_a0a0::FUN_0106aab0(u32 on)
{
    if (m5d0 == 0 && m5d1 == 0) {
        cUIWin_s0106_a0a0* w = (cUIWin_s0106_a0a0*)mpGlobalUI->FindWindowByID(0x4359752);
        cUIWin_s0106_a0a0* p;
        if (w != 0) p = (cUIWin_s0106_a0a0*)w->w0c(0x8ed27e7a);
        else p = 0;
        u32 v = p->w20();
        if (((v >> 2) & 1) != (u8)on) {
            p->w28(4, on);
            ToggleSlotsUI();
        }
    }
}

// @ 0x0106ab20
void cSPUISpace_s0106_a0a0::FUN_0106ab20(int state)
{
    bool b = state != 0;
    cUIWin_s0106_a0a0* w1 = (cUIWin_s0106_a0a0*)mpGlobalUI->FindWindowByID(0x4359752);
    cUIWin_s0106_a0a0* w2 = (cUIWin_s0106_a0a0*)mpGlobalUI->FindWindowByID(0x562a141);
    cUIWin_s0106_a0a0* w3 = (cUIWin_s0106_a0a0*)mpGlobalUI->FindWindowByID(0x453ef531);
    cUIWin_s0106_a0a0* p = 0;
    if (w3 != 0) p = (cUIWin_s0106_a0a0*)w3->w0c(0x8ed27e7a);
    if (w1 == 0) return;
    if (w2 == 0) return;
    w1->w7c(2, b);
    ToggleSlotsUI();
    w2->w7c(1, b);
    ToggleMinimapUI();
    u32 fill;
    if (b) {
        if (m5d2 == 0) fill = 1;
        else fill = 0;
    } else {
        u32 v = p->w20();
        m5d2 = ~(u8)(v >> 2) & 1;
        fill = 0;
    }
    p->w28(4, fill);
    UpdateStarMapFilters();
    if (state == 2 || state == 3) {
        cUIWin_s0106_a0a0* w = (cUIWin_s0106_a0a0*)mpGlobalUI->FindWindowByID(0x4359752);
        if (w != 0) {
            w = (cUIWin_s0106_a0a0*)w->w0c(0x8ed27e7a);
            if (w != 0) {
                u32 v = w->w20();
                if ((u8)((v >> 2) & 1) != (u8)(state == 3)) {
                    w->w28(4, state);
                    ToggleSlotsUI();
                }
            }
        }
    }
}

// @ 0x0106ac90
void cSPUISpace_s0106_a0a0::FUN_0106ac90(void* civ)
{
    if (SP_GetUniverseContext() == 0) return;
    cEfxNode* node = 0;
    cEffectsMgr* mgr = (cEffectsMgr*)SP_EffectsManager();
    if (node != 0) { node->e04(); node = 0; }
    u8 ok = mgr->m2c(0x3e2cc60, 0, &node);
    if (ok != 0) {
        node->e08();
        struct { u16 f0; u16 f2; u16 f4; float x, y, z; } args;
        args.f0 = 0; args.f2 = 0; args.f4 = 0;
        args.x = gEfxVec[0]; args.y = gEfxVec[1]; args.z = gEfxVec[2];
        u8 mat[0x30];
        FUN_0041cb40(mat, gEfxMatrixSrc);
        if (SP_GetUniverseContext() == 2) {
            void** p = ((cCivData*)civ)->GetCities(0, 0);
            *(u32*)&args.x = (u32)p[0];
            *(u32*)&args.y = (u32)p[1];
            *(u32*)&args.z = (u32)p[2];
            args.f0 = (u16)(args.f0 | 4);
            args.f2 = (u16)(args.f2 + 1);
        }
        node->e18(&args);
    }
    if (node != 0) node->e04();
}

// @ 0x0106ada0
void cSPUISpace_s0106_ada0::FUN_0106ada0()
{
    void* r = FUN_00b3d3f0(-0xc, (int)this->mSetiId);
    ((Engine*)r)->FUN_00e19350();

    void* tribe = ((Engine*)FUN_01002bd0())->FUN_00bfc5f0();

    void* mgr = FUN_00b3d3d0();
    char  ok  = ((Engine*)mgr)->FUN_0103a040();

    void* win = ((Engine*)this->mGlobalUI)->FUN_00e012b0(0x664c270);
    if (win == 0 || ok == 0)
        return;

    if (((Engine*)tribe)->FUN_00fe3df0((int)this->mSetiId) != 0)
        return;

    void* audio = FUN_00a206f0();
    void* audiofx = audio != 0 ? ((VFn_p)VSLOT(audio, 0x20))(audio) : 0;
    FUN_00435ed0((int)0xed858785, audiofx);

    Vec4 area;
    FUN_00805ea0(&area);
    float f = (area.mZ - area.mX) * 0.5f;
    Vec4* rect = (Vec4*)((VFn_p)VSLOT(win, 0x34))(win);
    f -= (rect->mZ - rect->mX) * 0.5f;
    Vec4* rect2 = (Vec4*)((VFn_p)VSLOT(win, 0x34))(win);
    ((VFn_vff)VSLOT(win, 0x64))(win, f, rect2->mY);

    void* child;
    child = ((VFn_pii)VSLOT(win, 0xf0))(win, 0x664a9d6, 1); ((VFn_vii)VSLOT(child, 0x7c))(child, 1, 0);
    child = ((VFn_pii)VSLOT(win, 0xf0))(win, 0x664a9d7, 1); ((VFn_vii)VSLOT(child, 0x7c))(child, 1, 0);
    child = ((VFn_pii)VSLOT(win, 0xf0))(win, 0x664a9d8, 1); ((VFn_vii)VSLOT(child, 0x7c))(child, 1, 0);
    child = ((VFn_pii)VSLOT(win, 0xf0))(win, 0x664a9d9, 1); ((VFn_vii)VSLOT(child, 0x7c))(child, 1, 0);
    child = ((VFn_pii)VSLOT(win, 0xf0))(win, 0x664a9da, 1); ((VFn_vii)VSLOT(child, 0x7c))(child, 1, 0);
    child = ((VFn_pii)VSLOT(win, 0xf0))(win, 0x664a9d0, 1); ((VFn_vii)VSLOT(child, 0x7c))(child, 1, 0);
    ((VFn_vii)VSLOT(win, 0x7c))(win, 1, 1);
    child = ((VFn_pii)VSLOT(win, 0xf0))(win, 0x674aa78, 1); ((VFn_vii)VSLOT(child, 0x7c))(child, 1, 1);
    void* icon = ((VFn_pii)VSLOT(win, 0xf0))(win, 0x664a9d4, 1); ((VFn_vii)VSLOT(icon, 0x7c))(icon, 1, 1);

    void* imgKey = 0;
    void* key = ((Engine*)tribe)->FUN_00fe5520((int)this->mSetiId, 0, &imgKey);
    FUN_00807cb0(icon, key);

    BadgeNameBuf name;
    name.mBegin   = (uint32_t)(int)&DAT_01667bac;
    name.mField04 = (uint32_t)(int)&DAT_01667bac;
    name.mTag     = DAT_01667bae;
    ((Engine*)tribe)->FUN_00fe4710((int)this->mSetiId, &name);
    child = ((VFn_pii)VSLOT(win, 0xf0))(win, 0x664a9d3, 1);
    ((VFn_vi)VSLOT(child, 0x80))(child, (int)name.mBegin);

    ((Engine*)tribe)->FUN_00fe4830((int)this->mSetiId, &name);
    child = ((VFn_pii)VSLOT(win, 0xf0))(win, 0x6779ee0, 1);
    ((VFn_vi)VSLOT(child, 0x80))(child, (int)name.mBegin);

    ((Engine*)tribe)->FUN_00fe49a0((int)this->mSetiId, &name);
    child = ((VFn_pii)VSLOT(win, 0xf0))(win, 0x678cd68, 1);
    ((VFn_vi)VSLOT(child, 0x80))(child, (int)name.mBegin);

    FUN_008099a0(win, 0, 0);
    ((VFn_vi)VSLOT(win, 0x104))(win, (int)this);

    void* hints = FUN_0067cac0(0, 1);
    ((Engine*)hints)->FUN_0067c420(0, 1);

    for (int i = 0; i < 5; ++i) {
        if (!((Engine*)mgr)->FUN_0103a040())
            break;
        void* slot = ((Engine*)mgr)->FUN_0103a060();
        void* prop = 0;
        void* pmgr = FUN_0067de30();
        if (prop != 0) {
            void* t = prop; prop = 0;
            ((VFn_v)VSLOT(t, 4))(t);
        }
        ((VFn_vpp4)VSLOT(pmgr, 0x2c))(pmgr, slot, (void*)0x34d97fa, (int)&prop, 0, 0);
        if (prop != 0) {
            BadgeNameBuf str;
            FUN_006a1360(prop, 0x3068d95d, &str);
            void* c = ((VFn_pii)VSLOT(win, 0xf0))(win, i + 0x664a9d6, 1);
            ((VFn_vii)VSLOT(c, 0x7c))(c, 1, 1);
            ((VFn_vi)VSLOT(c, 0x80))(c, (int)str.mBegin);
            void* inst = 0;
            FUN_006a12a0(prop, 0x35d5cb4, &inst);
            void* r2 = FUN_00b3d3f0(-0xb, (int)inst);
            ((Engine*)r2)->FUN_00e19350();
            if (prop) {
                void* t = prop; prop = 0;
                ((VFn_v)VSLOT(t, 4))(t);
            }
        }
    }

    void* evt = FUN_00b3d3e0(0x2e7b3501, 0x131a9f54, 0, 0, 1, 0);
    ((Engine*)evt)->FUN_00fe49a0(0, 0);   // PostFeedbackEvent
    if (((name.mEnd - name.mBegin) & 0xfffffffeu) > 2 && name.mBegin != 0)
        FUN_00f47380((void*)(int)name.mBegin);
}

// @ 0x0106b220
void cSPUISpace_s0106_ada0::FUN_0106b220(void* badge)
{
    void* tribe = ((Engine*)FUN_01002bd0())->FUN_00bfc5f0();
    char  haveEffect = ((Engine*)tribe)->FUN_00fe3df0((int)badge);
    void* fx = ((Engine*)tribe)->FUN_00fe54d0((int)badge);

    if (haveEffect == 0) {
        if (fx != 0) {
            void* emgr = FUN_0067ddd0();
            if (this->mSetiEffect != 0) {
                void* t = this->mSetiEffect; this->mSetiEffect = 0;
                ((VFn_v)VSLOT(t, 4))(t);
            }
            ((VFn_vpp4)VSLOT(emgr, 0x2c))(emgr, fx, (void*)0, (int)&this->mSetiEffect, 0, 0);
            if (this->mSetiEffect != 0)
                ((VFn_vi)VSLOT(this->mSetiEffect, 8))(this->mSetiEffect, 0);
        }
    } else {
        void* inv = ((Engine*)FUN_00ffbe50(4, 1))->FUN_00a1ad60();
        ((Engine*)inv)->FUN_00c389c0(4, 1);
    }

    void* inv2 = ((Engine*)FUN_00ffbe50(6, 1))->FUN_00a1ad60();
    ((Engine*)inv2)->FUN_00c389c0(6, 1);

    this->mSetiId = badge;
    if (haveEffect == 0 && fx == 0)
        this->FUN_0106ada0();
    *(uint8_t*)((char*)tribe + 0xa0) = 1;
}

// @ 0x0106b310
void cSPUISpace_s0106_ada0::ManageSeti(void* civ, int arg2)
{
    (void)arg2;

    if (FUN_01021080_s0106_ada0() != 2) {
        this->FUN_01068230();
        return;
    }
    void* inv = ((Engine*)FUN_01002bd0())->FUN_00a1ad60();
    if (((VFn_ci)VSLOT(inv, 0x74))(inv, 0x16e2368) == 0) {
        this->FUN_01068230();
        return;
    }
    if ((((GameTimeManager_s0106_ada0*)FUN_00b3d380())->mState >> 1) & 1) {
        this->FUN_01068230();
        return;
    }

    if (civ != 0) {
        float z    = FUN_010434e0(FUN_01021240(((Engine*)civ)->FUN_005c65e0()));
        float maxz = ((Engine*)FUN_00ffbe50(0, 0))->FUN_00ffbfd0();
        if (maxz >= z) {
            char  ok = ((Engine*)civ)->FUN_00bb9fb0();
            void* h  = this->mSetiHandle;
            void* audio = FUN_00a206f0();
            bool  playing = false;
            if (audio != 0)
                playing = ((VFn_ci)VSLOT(audio, 0x28))(audio, (int)h) != 0;
            if (!playing) {
                void* p = audio != 0 ? ((VFn_p)VSLOT(audio, 0x20))(audio) : 0;
                int msg = ok != 0 ? 0x40ffb740 : 0x61fcea3d;
                this->mSetiHandle = p;
                FUN_00435ed0(msg, p);
            }
            if (ok != 0 && this->mSetiFX == 0) {
                void* emgr = FUN_0067ddd0();
                if (this->mSetiFX != 0) {
                    void* t = this->mSetiFX; this->mSetiFX = 0;
                    ((VFn_v)VSLOT(t, 4))(t);
                }
                ((VFn_vpp4)VSLOT(emgr, 0x2c))(emgr, (void*)0x28115ab8, (void*)0, (int)&this->mSetiFX, 0, 0);
                if (this->mSetiFX != 0) {
                    XformMsg_s0106_ada0 msg;
                    FUN_00434040(&msg);
                    FUN_00571d40(&msg, ((Engine*)civ)->FUN_005c65e0());
                    ((VFn_vp)VSLOT(this->mSetiFX, 0x14))(this->mSetiFX, &msg);
                    ((VFn_vi)VSLOT(this->mSetiFX, 8))(this->mSetiFX, 0);
                }
            }
            return;
        }
    }

    // ---- shared tail --------------------------------------------------------
    void* h = this->mSetiHandle;
    void* audio = FUN_00a206f0();
    if (audio != 0 && ((VFn_ci)VSLOT(audio, 0x28))(audio, (int)h) != 0) {
        FUN_00572020(h, 1);
        void* sys = FUN_00a206f0();
        void* v = sys != 0 ? ((VFn_p)VSLOT(sys, 0x20))(sys) : 0;
        FUN_00435ed0(0x17b6fd56, v);
    }
    this->FUN_01068230();
}

// @ 0x0106b500
void cSPUISpace_s0106_ada0::FUN_0106b500(void* item)
{
    if (this->mPosse == 0)
        return;
    if (((Engine*)this->mPosse)->FUN_00fe24c90((int)item) != 0)
        return;

    void* found = ((Engine*)this->mPosse)->FUN_00fe24c90(0);
    while (found != 0) {
        ((VFn_vii)VSLOT(this->mPosse, 0xa8))(this->mPosse, (int)found, 1);
        found = ((Engine*)this->mPosse)->FUN_00fe24c90(0);
    }

    void* res   = FUN_009512c0();
    void* p     = FUN_009512d0(0x14c, 4, "UI/PosseItem", res);
    void* space = p != 0 ? ((Engine*)p)->FUN_00e259d0(item) : 0;
    ((VFn_vi)VSLOT(this->mPosse, 0xa4))(this->mPosse, (int)space);
    ((VFn_vi)VSLOT(this->mPosse, 0xc0))(this->mPosse, 1);

    uint32_t handle[3];
    handle[0] = 0;
    handle[1] = 0;
    handle[2] = 0;
    FUN_00c37230(space, handle, &space);

    uint32_t resHandle[2];
    resHandle[0] = 0;
    resHandle[1] = 0x2f7d0004;
    void* img = 0;
    FUN_00806230(resHandle, &img, 0, -1, -1);
    if (img != 0) {
        ((VFn_vii)VSLOT(space, 0x94))(space, (int)img, 0);
        if (img != 0)
            ((VFn_v)VSLOT(img, 4))(img);
    }
}

// @ 0x0106b630
void cSPUISpace_s0106_ada0::FUN_0106b630()
{
    ((Engine*)FUN_00b3d3d0())->FUN_0103a040();
    void* win = ((Engine*)this->mGlobalUI)->FUN_00e012b0(0x664c270);

    if (this->mSetiEffect != 0) {
        void* fx = this->mSetiEffect;
        char alive = ((VFn_c)VSLOT(fx, 0x10))(fx);
        if (alive == 0) {
            void* game = FUN_01002bd0();
            if (((Engine*)((SpaceGame*)game)->mOwner)->FUN_00d09660() == 0) {
                int state = ((TriggerManager*)FUN_00b3d4d0())->mMode;
                if (state != 1 && state != 2) {
                    if (this->mSetiEffect != 0) {
                        void* t = this->mSetiEffect; this->mSetiEffect = 0;
                        ((VFn_v)VSLOT(t, 4))(t);
                    }
                    if (this->mSetiId != 0) {
                        this->FUN_0106ada0();
                        this->mSetiId = 0;
                    }
                }
            }
        }
    }

    void* tribe = ((Engine*)FUN_01002bd0())->FUN_00bfc5f0();
    if (((GameNounManager*)tribe)->mHasSetiBadge == 0)
        return;

    void* panel = ((VFn_pii)VSLOT(win, 0xf0))(win, 0x674aa78, 1);
    if (panel != 0) {
        void* inner = ((VFn_p)VSLOT(panel, 0x14))(panel);
        MsgHeader hdr;
        hdr.mId = 0;
        hdr.mType = 0x10002;
        ((VFn_vpp4)VSLOT(inner, 0x10))(inner, panel, (void*)&hdr, 0, 0, 0);
    }
    if (this->mSetiEffect != 0)
        return;
    if (((VFn_i)VSLOT(win, 0x28))(win) & 1)
        return;

    void* tribe2 = ((Engine*)FUN_01002bd0())->FUN_00bfc5f0();
    ((GameNounManager*)tribe2)->mHasSetiBadge = 0;
    FUN_008099a0(win, 0, 0);
    void* hints = FUN_0067cac0(1, 1);
    ((Engine*)hints)->FUN_0067c420(1, 1);

    void* audio = FUN_00a206f0();
    void* value = audio ? ((VFn_p)VSLOT(audio, 0x20))(audio) : 0;

    void* sys = FUN_00a206f0();
    if (sys == 0)
        return;
    ((VFn_vi)VSLOT(sys, 0x38))(sys, 0x3475365);
    ((VFn_vii)VSLOT(sys, 0x40))(sys, 0x3475381, 0x67687b73);
    ((VFn_vii)VSLOT(sys, 0x40))(sys, 0x3475385, (int)value);
    ((VFn_v)VSLOT(sys, 0x58))(sys);
}

// @ 0x0106b7e0
char __stdcall FUN_0106b7e0(void* self, void* icon)
{
    if (self != 0) {
        void* w = ((VFn_p)VSLOT(self, 0xa8))(self);
        if (w != 0) {
            void* h = ((VFn_pi)VSLOT(w, 0x0c))(w, 0xef3c47cf);
            if (h != 0) {
                void* img = 0;
                FUN_00806230(icon, &img, 0, -1, -1);
                if (img != 0) {
                    ((VFn_vp)VSLOT(h, 0x14))(h, img);
                    if (img != 0)
                        ((VFn_v)VSLOT(img, 4))(img);
                    return 1;
                }
            }
        }
    }
    return 0;
}

// @ 0x0106b860
int FUN_0106b860(void* res)
{
    int count = 3;
    if (res == 0)
        return count;

    ResourceDesc desc;
    desc.mResource = res;
    desc.mKey      = 0x366a930d;
    desc.mType     = DAT_015b9108;

    void* out = 0;
    void* mgr = FUN_0067dcd0();
    if (out != 0) {
        void* t = out; out = 0;
        ((VFn_v)VSLOT(t, 4))(t);
    }
    ((VFn_vpp4)VSLOT(mgr, 0x0c))(mgr, &desc, (void*)&out, 0, 0, 0);

    if (out != 0) {
        void* list = ((VFn_pi)VSLOT(out, 0x0c))(out, 0xe742574a);
        if (list != 0) {
            ResourceList* rl = (ResourceList*)list;
            int n = (int)(rl->mEnd - rl->mBegin) / 0x38;
            int empty = 0;
            if (n > 0) {
                uint8_t* p = rl->mBegin + 0x20;
                do {
                    if (*p == 0)
                        ++empty;
                    p += 0x38;
                } while (--n);
                if (empty < count)
                    count = empty;
            }
        }
        if (out != 0) {
            void* t = out; out = 0;
            ((VFn_v)VSLOT(t, 4))(t);
        }
    }
    return count;
}

// @ 0x0106b950
void __stdcall FUN_0106b950(Node* head, NodeIterator begin, NodeIterator end, int unused)
{
    (void)unused;
    for (; begin != end; ++begin) {
        void*& value = *begin;
        Node* n = (Node*)FUN_00f473a0(0xc, "Simulator", 0, 0, (void*)&g_alloc_13ebb38, 0xd1);
        if (&n->mData != 0)
            n->mData = value;
        n->mNext = head;
        n->mPrev = head->mPrev;
        head->mPrev->mNext = n;
        head->mPrev = n;
    }
}

// @ 0x0106b9b0
int cSPUISpace_s0106_ada0::FUN_0106b9b0(int key, int index)
{
    Hashtable* h = &this->mBadgeTable;
    uint32_t it[2];
    int result = 0x1002;
    int* found = h->find(it, &key);
    int v = *found;
    if (h->mpBuckets[h->mBucketCount] != v)
        result = ((BadgeHashNode*)(int)v)->mValues[index];
    return result;
}

// @ 0x0106c930
void cSPUISpace_s0106_c930::FUN_0106c930()
{
    if (FUN_00fd9c60()->IsActiveMode())
        return;

    int id = 0x1002;

    if (!FUN_00b3d230_s0106_c930()->FUN_00b5ca60()) {
        cSpaceTool* tool = this->mToolView->GetShownTool();

        if (tool != 0 && FUN_01021080_s0106_c930() == 0) {
            // the engine looks the sim-check slot up by reference, so the
            // original keeps the address of the +0x20 member as well as its value
            SimCheck*& simCheck = FUN_01002bd0_s0106_c930()->mSimCheck;

            if (!simCheck->FUN_00d09660()) {
            ToolKeyOut scratch;
            ToolKeyOut keyOut;

            cToolStrategy* strategy = tool->GetStrategy();

            ((VFn_vp)VSLOT(strategy, 0x3c))(strategy, &scratch);

            cSpaceTool* other = this->mToolView->GetOtherTool();

            if (tool->FUN_0104ff10()) {
                id = 3;
            } else if (tool->FUN_0104bd50()) {
                id = 2;
            } else {
                id = !((VFn_cpp)VSLOT(strategy, 0x24))(strategy, tool, &scratch, 0);
            }

            int* key;
            if (other != 0)
                key = ((VFn_pvp)VSLOT(other, 0x38))(other, &keyOut);
            else
                key = ((VFn_pvp)VSLOT(tool, 0x38))(tool, &keyOut);

            id = this->FUN_0106b9b0(*key, id);
            }
        }

        if (FUN_01021080_s0106_c930() == 2) {
            cStar* star = FUN_00ffbe50()->GetStarRecordUnderMouse();
            if (star != 0 && star->GetState() == 5) {
                uint32_t avatar = star->GetAvatar();
                cEmpire_s0106_c930* empire = FUN_00b3d2a0_s0106_c930()->GetEmpireByID(avatar);
                uint32_t starKey = star->mKey;
                uint32_t empireKey = empire->mEmpireKey;
                if (FUN_00b3d4a0(empireKey, starKey)->Has())
                    id = 0x057f997d;
            }
        }
    }

    CurMgr_s0106_c930* mgr = FUN_0067cab0_s0106_c930();
    if (mgr->GetCursor() != (uint32_t)id)
        mgr->FindLocal((uint32_t)id);
}

// @ 0x0106cab0
void SP::cSPUISpace_s0106_cab0::FUN_0106cab0()
{
    bool active = mpCursor->IsActive();
    if (active) {
        eastl::hashtable_range range;
        mCursorTable.equal_range(&range, mCursorKey);
        eastl::hash_node_s0106_cab0*  node = range.first.mpNode;
        eastl::hash_node_s0106_cab0*  end  = range.second.mpNode;
        _ReadWriteBarrier();          // keeps end's load before the bucket load, so cl picks ebx directly
        eastl::hash_node_s0106_cab0** bucket = range.first.mpBucket;
        while (node != end) {
            ((IReleasable*)node->mpValue)->Release();
            node = node->mpNext;
            if (!node) {
                do {
                    node = *++bucket;
                } while (!node);
            }
        }
        IReleasable* rollover = mpRollover298;
        if (rollover)
            rollover->Release();
        rollover = mpRollover29c;
        if (rollover)
            rollover->Release();
    }

    Win_s0106_cab0* window = mpGlobalUI->FindWindowByID(0x5d42af0);
    window->SetVisible(1, active && !GetUISoundHelper()->GetFlag());
}

// @ 0x0106cbd0
void* SP::cIntrusiveNode::Construct(void** src)
{
    bool dummy = false;
    mpNext = this;
    mpPrev = this;
    Init(this, *src, src, *(uint32_t*)&dummy);
    return this;
}

// @ 0x0106da70
cSPUIBase::cSPUIBase()
: m10(0), m14(0), m18(0),
      m44(0), m48(0), m4c(0), m50(0), m54(0), m58(0), m5c(0), m60(0), m64(0),
      m68(0), m6c(0), m70(0), m74(0), m78(0), m7c(0),
      mStopwatch(0, false)
{
}

// @ 0x0106dcd0
void cSPUISpace_s0106_da70::PushToolWindowId(uint32_t id)
{
    mToolWindowDeque.push_back(id);
}

// @ 0x0106dd10
void cSPUISpace_s0106_da70::FUN_0106dd10(uint32_t index, uint32_t value)
{
    IWindow* pWindow;

    if (mpLayout == 0)
        return;

    pWindow = mpGlobalUI->FindWindowByID(value);
    if (pWindow == 0)
        return;

    if (index == 0)
        m23c = value;
    else
        mpIdsBegin[index] = value;
}

// @ 0x0106e020
void cSPUISpace_s0106_da70::AddCursors()
{
    uint32_t i;

    for (i = 0; i < (uint32_t)(mpIdsEnd - mpIdsBegin); ++i) {
        if (mpIdsBegin[i] == m23c) {
            mpIdsBegin[i] = mpIdsBegin[(i + 1) % (uint32_t)(mpIdsEnd - mpIdsBegin)];
        }
    }
}

// @ 0x0106e270
void cSPUISpace_s0106_da70::OnContextDeactivate()
{
    IWindow* pWindow;

    UpdateTravelLine(0);
    UpdatePlanetRollover(0);

    pWindow = mpGlobalUI->FindWindowByID(0x2c38ab9);
    if (pWindow)
        pWindow->v7c(true, false);

    pWindow = mpActiveWindow;
    if (pWindow)
        pWindow->v0c(1);
}

// @ 0x0106e2d0
cSPUISpace_s0106_da70::cSPUISpace_s0106_da70()
{
    *(volatile float*)&mf150 = 1.0f;
    *(volatile float*)&mf154 = 2.0f;
    _ReadWriteBarrier();
    mToolStrategies.mnElements = 0;
    m158 = 0;
    mToolStrategies.mnBuckets = 1;
    mToolStrategies.mpBuckets = (EaHashNode**)gOneBucket;
}

// @ 0x0106e3e0
void cSPUISpace_s0106_da70::ToggleToolUI(uint32_t id)
{
    IWindow* pPanel = mpGlobalUI->FindWindowByID(0x453ef531);

    if (pPanel)
        pPanel = pPanel->v0c(0x8ed27e7a);
    pPanel->v28(4, true);

    UpdateStarMapFilters();

    if (id == m23c)
        return;

    if (m23c != 0) {
        IWindow* pOld;

        pOld = mpGlobalUI->FindWindowByID(m23c);
        pOld->v7c(true, false);
        pOld = mpGlobalUI->FindWindowByID(m23c - 0x10);
        if (pOld)
            pOld = pOld->v0c(0x8ed27e7a);
        pOld->v28(4, false);
    }

    m23c = id;

    if (id != 0) {
        IWindow* pNew;

        pNew = mpGlobalUI->FindWindowByID(id);
        pNew->v7c(true, true);
        pNew = mpGlobalUI->FindWindowByID(id - 0x10);
        if (pNew)
            pNew = pNew->v0c(0x8ed27e7a);
        pNew->v28(4, true);
    }

    FUN_0106aa10(mpSortedEnd != mpSortedBegin &&
                 m23c <= mpSortedEnd[-1]);
}

// @ 0x0106e5e0
void cSPUISpace_s0106_da70::FUN_0106e5e0()
{
    uint32_t count = (uint32_t)(mpIdsEnd - mpIdsBegin);
    uint32_t next = 0;
    _ReadBarrier();
    for (uint32_t i = 0; i < count; ++i) {
        const uint32_t* pIds = mpIdsBegin;
        if (pIds[i] == m23c)
            next = pIds[(i + 1) % count];
    }
    ToggleToolUI(next);
}

// @ 0x0106e630
void cSPUISpace_s0106_da70::FUN_0106e630()
{
    uint32_t count = (uint32_t)(mpIdsEnd - mpIdsBegin);
    uint32_t next = 0;
    _ReadBarrier();
    for (uint32_t i = 0; i < count; ++i) {
        const uint32_t* pIds = mpIdsBegin;
        if (pIds[i] == m23c)
            next = pIds[(count - 1 + i) % count];
    }
    ToggleToolUI(next);
}

// @ 0x0106e680
void cSPUISpace_s0106_da70::FUN_0106e680(uint32_t id)
{
    EaHashNode** pBucket = mHash25c.mpBuckets;
    EaHashNode*  pNode = *pBucket;
    EaHashNode*  pEnd = mHash25c.mpBuckets[mHash25c.mnBuckets];

    if (pNode == 0) {
        do
            ++pBucket;
        while (*pBucket == 0);
        pNode = *pBucket;
    }

    while (pNode != pEnd) {
        IWindow* pWindow = (IWindow*)pNode->mpValue;

        if (pWindow->v38(id)) {
            uint32_t key = pNode->mKey;

            if (key != 0) {
                ToggleToolUI(key);
                pWindow->v34(id);
            }
            return;
        }

        pNode = pNode->mpNext;
        if (pNode == 0) {
            do
                ++pBucket;
            while (*pBucket == 0);
            pNode = *pBucket;
        }
    }
}

// @ 0x0106e720
void cSPUISpace_s0106_da70::SetToolTipForItem(uint32_t toolId, void* pItem)
{
    if (pItem == 0) {
        if (mpTipWindow)
            mpTipWindow->v00();
        return;
    }
}

// @ 0x0106e940
void cSPUISpace_s0106_da70::FUN_0106e940(uint32_t index)
{
    if (index >= (uint32_t)(mpIdArrayEnd - mpIdArray))
        return;

    mpIdArray[index] = index;
}

// @ 0x0106ea40
void cSPUISpace_s0106_ea40::FUN_0106ea40(u32 index)
{
    if (index >= 3)
        return;
    if ((int)index >= (int)(mIdArray.mpEnd - mIdArray.mpBegin))
        return;

    u32* pValue = &mIdArray.mpBegin[index];

    UFO* ufo = (UFO*)SP_GetUFOSimulator();
    ToolList* src = (ToolList*)ufo->GetToolListPtr();

    ToolList lst;
    lst.assign(lst, src->mpHead, (Node_s0106_ea40*)src, 0);

    u32 empire = SP_GetPlayerEmpireID();
    lst.pushBack(empire);

    Node_s0106_ea40* head = lst.mpHead;
    Node_s0106_ea40* p = head;
    while (p != (Node_s0106_ea40*)&lst) {
        if (p->mValue == *pValue)
            break;
        p = p->mpNext;
    }
    if (p != (Node_s0106_ea40*)&lst) {
        if (p->mValue == head->mValue)
            *pValue = lst.mpTail->mValue;
        else
            *pValue = p->mpPrev->mValue;
        FUN_0106dd10(index, *pValue);
    }
    lst.destroy();
}

// @ 0x0106eb40
Blk28_s0106_ea40* Blk28Vec::erase(Blk28_s0106_ea40* first, Blk28_s0106_ea40* last)
{
    Blk28_s0106_ea40* p = Blk28_mvassign(last, mpEnd, first);
    Blk28_s0106_ea40* end = mpEnd;
    while (p < end) {
        if (p->mpRef != 0)
            p->mpRef->Release();
        p += 1;
    }
    mpEnd -= last - first;
    return first;
}

// @ 0x0106ebb0
Blk28_s0106_ea40* Blk28Vec::insert(Blk28_s0106_ea40* position, u32 n, const Blk28_s0106_ea40& value)
{
    if ((u32)(mpCap - mpEnd) < n) {
        u32 size = (u32)(mpEnd - mpBegin);
        u32 newCap = size + n;
        u32 doubled = size * 2;
        if (doubled == 0)
            doubled = 1;
        if (doubled > newCap)
            newCap = doubled;
        Blk28_s0106_ea40* newBegin = 0;
        if (newCap != 0)
            newBegin = (Blk28_s0106_ea40*)operator_new(newCap * 0x28u, "Simulator", 0, 0, 0, 0xd1);
        Blk28_s0106_ea40* dst1 = Blk28_copy_b(mpBegin, position, newBegin);
        Blk28_reloc_b(mpBegin, position, dst1);
        Blk28_fill4(dst1, n, &value, dst1);
        Blk28_s0106_ea40* dst2 = dst1 + n;
        Blk28_s0106_ea40* dst3 = Blk28_copy_b(position, mpEnd, dst2);
        Blk28_reloc_b(position, mpEnd, dst3);
        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
            operator_delete__(mpBegin);
        mpBegin = newBegin;
        mpEnd = dst3;
        mpCap = newBegin + newCap;
    } else if (n != 0) {
        Blk28_s0106_ea40 temp;
        temp.CopyCtor(value);
        Blk28_s0106_ea40* oldEnd = mpEnd;
        u32 after = (u32)(mpEnd - position);
        if (n < after) {
            Blk28_s0106_ea40* srcEnd = oldEnd - n;
            Blk28_s0106_ea40* dstEnd;
            Blk28_ccopy(&dstEnd, srcEnd, oldEnd, oldEnd);
            mpEnd += n;
            Blk28_mback(position, srcEnd, oldEnd);
            Blk28_assignr(position, position + n, &temp);
        } else {
            Blk28_fill3(oldEnd, n - after, &temp);
            mpEnd += n - after;
            Blk28_s0106_ea40* dstEnd;
            Blk28_ccopy(&dstEnd, position, oldEnd, mpEnd);
            Blk28_assignr(position, oldEnd, &temp);
        }
        if (temp.mpRef != 0)
            temp.mpRef->Release();
    }
    return position;
}

// @ 0x0106edc0
u32 cSPUISpace_s0106_ea40::FUN_0106edc0(u32 key)
{
    HashIter it;
    mStrategyTable.find(&it, key);
    if (mStrategyTable.mpBuckets[mStrategyTable.mnBuckets] != it.mpNode)
        return it.mpNode->mValue;

    u32 n = m2f4;
    if (n != 0x68e0310) {
        m2f4 = n + 1;
        *mStrategyTable.insertEntry(key) = n;
        return n;
    }

    if (mIds2c0.mpBegin == mIds2c0.mpEnd) {
        HashIter cur;
        mToolTable.begin(&cur);
        while (cur.mpNode != mToolTable.mpBuckets[mToolTable.mnBuckets]) {
            u32 v = cur.mpNode->mValue;
            if (mpGlobalUI->FindWindowByID(v) == 0) {
                cur = mToolTable.erase(cur);
                if (mIds2c0.mpEnd < mIds2c0.mpCap) {
                    u32* slot = mIds2c0.mpEnd++;
                    if (slot != 0)
                        *slot = v;
                } else {
                    mIds2c0.DoInsertValueI(mIds2c0.mpEnd, v);
                }
            } else {
                cur.mpNode = cur.mpNode->mpNext;
                while (cur.mpNode == 0) {
                    ++cur.mpBucket;
                    cur.mpNode = *cur.mpBucket;
                }
            }
        }
    }

    if (mIds2c0.mpBegin != mIds2c0.mpEnd) {
        u32 v = mIds2c0.mpEnd[-1];
        mIds2c0.mpEnd -= 1;
        *mStrategyTable.insertEntry(key) = v;
        return v;
    }
    return 0;
}

// @ 0x0106ef30
void cSPUISpace_s0106_ea40::FUN_0106ef30()
{
    {
        HashIter it;
        it.mpBucket = mToolTable.mpBuckets;
        it.mpNode = *it.mpBucket;
        while (it.mpNode == 0) {
            ++it.mpBucket;
            it.mpNode = *it.mpBucket;
        }
        HashNode* end = mToolTable.mpBuckets[mToolTable.mnBuckets];
        while (it.mpNode != end) {
            ((IFace*)it.mpNode->mValue)->v20();
            it.mpNode = it.mpNode->mpNext;
            while (it.mpNode == 0) {
                ++it.mpBucket;
                it.mpNode = *it.mpBucket;
            }
        }
    }

    if (mp294 != 0) {
        IFace* p = mp294;
        mp294 = 0;
        p->Release4();
    }
    if (mp298 != 0)
        mp298->v20();
    if (IFace* p = mp298) {
        mp298 = 0;
        p->Release4();
    }
    if (mp29c != 0)
        mp29c->v20();
    if (IFace* p = mp29c) {
        mp29c = 0;
        p->Release4();
    }
    if (IFace* p = mpToolList) {
        mpToolList = 0;
        p->Release4();
    }
    m23c = 0;

    mIds.clear();
    mToolTable.freeNodes(mToolTable.mpBuckets, mToolTable.mnBuckets);
    mToolTable.mnElements = 0;
    mSortedIds.clear();
    mIds2c0.clear();

    mStrategyTable.freeBuckets(mStrategyTable.mpBuckets, mStrategyTable.mnBuckets);
    mStrategyTable.mnElements = 0;
    m2f4 = 0x68e0210;

    IRelease8* p = mp254;
    if (p != 0) {
        mp254 = 0;
        p->Release8();
    }
}

// @ 0x0106f120
void cSPUISpace_s0106_ea40::FUN_0106f120(u32 id)
{
    if (m5d5 != 0) {
        FUN_0106e680(id);
        cWindow* w = mpWindow61c;
        w->FUN_00e31030(FUN_0106edc0(id), 0x622c8f6, 0, 0);
    }
}

// @ 0x0106f160
void cSPUISpace_s0106_ea40::FUN_0106f160(u32 id)
{
    if (m5d5 != 0) {
        FUN_0106e680(id);
        cWindow* w = mpWindow61c;
        w->FUN_00e31030(FUN_0106edc0(id), 0x651886d, 0, 0x5f72e19);
    }
}

// @ 0x0106f1a0
void cSPUISpace_s0106_ea40::FUN_0106f1a0(int param_2, char param_3)
{
    if (param_3 != 0)
        ToggleToolUI(0xb0000016);

    if (m23c != 0xb0000016)
        return;

    u32 flag = (*(int*)((char*)param_2 + 0x10) != 0) ? 1 : 0;
    int kind = *(int*)((char*)param_2 + 0x18);

    if (kind == 0) {
        int r = mpToolList->v64(flag, (void*)((char*)param_2 + 4));
        if (r <= 0)
            return;
        mpWindow61c->FUN_00e30ae0(0x622c9ce);
        void* item = mpToolList->v60((u32)r);
        mp294->v34(item);
        mpWindow61c->FUN_00e31030(FUN_0106edc0((u32)item), 0x622c9ce, 0, 0);
        return;
    }
    if (kind != 3)
        return;

    mpWindow61c->FUN_00e30ae0(0x622c9ce);
    char first = 1;
    int count = mpToolList->v5c();
    if (count <= 0)
        return;

    int i = 0;
    for (;;) {
        SpItem* item = (SpItem*)mpToolList->v60((u32)i);
        if (item->mFlag == flag && !item->v44()) {
            void* a = item->mSub.v0c(0x70a2863c);
            void* b = item->mSub.v0c(0x30fc270b);
            int sel = *(int*)((char*)param_2 + 0x10);
            bool hit = false;
            if (sel == 0)
                hit = (((B8F860*)a)->Get() == *(int*)((char*)param_2 + 0x14));
            else if (sel == 1)
                hit = !((AC0C50*)b)->Test();
            else if (sel == 2)
                hit = ((AC0C50*)b)->Test();
            if (hit) {
                if (first) {
                    mp294->v34(item);
                    first = 0;
                }
                mpWindow61c->FUN_00e31030(FUN_0106edc0((u32)item), 0x622c9ce, 0, 0);
            }
        }
        ++i;
        if (i >= count)
            return;
    }
}

// @ 0x0106f380
void cSPUISpace_s0106_ea40::FUN_0106f380()
{
    PtrVec& v = mVec308;
    u32 n = (u32)(v.mpEnd - v.mpBegin);
    u32 i = 0;
    while (i < n) {
        ((IElement*)v.mpBegin[i])->v0c(1);
        ++i;
    }
    v.eraseA(v.mpBegin, v.mpEnd);
}

// @ 0x0106f3d0
void cSPUISpace_s0106_ea40::FUN_0106f3d0()
{
    int n = (int)(mZoomVec.mpEnd - mZoomVec.mpBegin);
    for (int i = 0; i < n; ++i) {
        cTextZoomName* p = (cTextZoomName*)mZoomVec.mpBegin[i];
        if (p != 0)
            p->Shutdown();
    }
    mZoomVec.eraseB(mZoomVec.mpBegin, mZoomVec.mpEnd);

    LayoutSet* ls = &mLayoutSet;
    int count = ls->Count();
    for (int i = 0; i < count; ++i) {
        cSPUILayout_s0106_ea40* lay = ls->At(i);
        if (lay == 0)
            continue;

        cTextZoomName* t = (cTextZoomName*)operator_new(0x78u, "UI/cSPUITextZoom", 0, 0, 0, 0);
        if (t == 0) {
            t = 0;
        } else {
            t = t->Construct();
        }

        cTextZoomName* local = t;
        if (local != 0)
            local->AddRef();

        if (mZoomVec.mpEnd < mZoomVec.mpCap) {
            void** slot = mZoomVec.mpEnd++;
            if (slot != 0) {
                *slot = local;
                if (local != 0)
                    local->AddRef();
            }
        } else {
            mZoomVec.insertEntry(mZoomVec.mpEnd, (void**)&local);
        }
        if (local != 0)
            local->Release();

        cUIWindow* win = (cUIWindow*)lay->FindWindowByID(0x7edb1e8, 1);
        if (win != 0) {
            win->SetId(0x7edb1e8 + (u32)i);
            Uid uid;
            uid.m0 = 0;
            uid.m1 = 0;
            uid.m2 = 0;
            void* w2 = win->QueryIn(uid, 0, 0, 0, 0xf15f4bd);
            ((cTextZoomName*)mZoomVec.mpBegin[i])->SetTargetWindow(w2);
        }
    }
}

// @ 0x0106f540
void cSPUISpace_s0106_ea40::FUN_0106f540()
{
    PtrVec& v = mZoomVec;
    int n = (int)(v.mpEnd - v.mpBegin);
    for (int i = 0; i < n; ++i) {
        if (v.mpBegin[i] != 0) {
            ((cTextZoomName*)v.mpBegin[i])->Shutdown();
            if (v.mpBegin[i] != 0) {
                cTextZoomName* p = (cTextZoomName*)v.mpBegin[i];
                v.mpBegin[i] = 0;
                p->Release();
            }
        }
    }
    v.eraseB(v.mpBegin, v.mpEnd);
}

// @ 0x0106f5b0
namespace SP {
cSPUISpace_s0106_f5b0::~cSPUISpace_s0106_f5b0()
{
    delete mp568;
    mp568 = 0;
    FUN_0067de40()->Get()->Set(g_16e0d08);
    g_16e0d08 = 0;
}
}  // namespace SP

// @ 0x0106fc90
namespace SP {
bool cSPUISpace_s0106_f5b0::DoFocusChange(IFocusTarget* pOld, const cFocusChangeData* pChange)
{
    cSPLivingUniverse* pPlanet = cSPLivingUniverse::GetActivePlanet();
    if (pPlanet != 0)
        g_16e0d08->mPlanetId = pPlanet->mPlanetId;

    IFocusTarget* pNew = pChange->mpNewTarget;
    if (pNew != 0)
        pNew->OnFocusLost();

    const bool same = (pOld == pNew);
    if (GetTimedTooltip() != 0)
        GetTimedTooltip()->Hide();

    const uint32_t typeId = pOld->GetTypeId();
    const uint32_t classHash = pOld->GetClassHash();

    bool refreshAudio = false;       // the delete button and the editor focus end in the tooltip / audio refresh

    if (classHash == 0x5232c00)
    {
        // editor plane windows: the class id picks two windows that become visible together
        cSPUIWindow* pWindowA = 0;
        cSPUIWindow* pWindowB = 0;
        if (typeId == 0x5233980) {
            pWindowA = mpGlobalUI->FindWindowByID(0x51dec70);
            pWindowB = mpGlobalUI->FindWindowByID(0x5243538);
        }
        else if (typeId == 0x52339a8) {
            pWindowA = mpGlobalUI->FindWindowByID(0x51decd0);
            pWindowB = mpGlobalUI->FindWindowByID(0x5243548);
        }
        else if (typeId == 0x52339c0) {
            pWindowA = mpGlobalUI->FindWindowByID(0x51decd8);
            pWindowB = mpGlobalUI->FindWindowByID(0x5243558);
        }
        else {
            pWindowA = (cSPUIWindow*)pNew;
            pWindowB = (cSPUIWindow*)pNew;
        }
        if (pWindowA != 0 && pWindowB != 0)
        {
            pWindowA->SetVisible(true, same);
            pWindowB->SetVisible(true, same);
        }
    }
    else if (classHash == 0x34ef68d)
    {
        mb5d3 = same;
        if (same)
        {
            // place the delete button window on the focused object
            float anchor[2] = { 0.0f, 0.0f };
            float pos[4];
            pOld->GetFocusTransform(anchor[0], anchor[1], pos);
            cSPUIWindow* pDeleteButton = mpGlobalUI->FindWindowByID(0xb2001000);
            cSPUIWidget* pContent = pDeleteButton->GetContent();
            pContent->SetLayoutPosition(pos[0], pos[1], pos);
            pDeleteButton->SetPosition(pos[0], pos[1]);
            mDeleteButtonWindow = pOld->GetTypeId();
            refreshAudio = true;
        }
        else
            goto done;
    }
    else if (classHash == 0x37e9018)
    {
            if (!same)
                goto done;
            cFocusRecord* pRecord = FUN_01067ef0(typeId);
            if (pRecord == 0)
                goto done;
            FUN_0106f1a0(pRecord, 0);
            if (pRecord->mKind18 == 0)
            {
                // species / planet record: the localised name becomes the tooltip
                KillSetiEffects(0xd0840db7, GetRecorderState());
                cSPEditorSpeciesProfile* pProfile =
                    FUN_00401090(pRecord->mKey04)->GetProfile(pRecord->mKey04);
                if (pProfile == 0)
                    goto done;
                g_16e0d08->mPad14 = 0;
                g_16e0d08->mpRecord = pProfile;
                cString_s0106_f5b0* pText = (pRecord->mKind10 != 0) ? &s478 : &s48c;
                if (pRecord->mbFlag1c == 0)
                    SetToolTip(pOld, pText->GetText(0, 0), 0);
                else
                {
                    Key_s0106_f5b0 key = pRecord->mKey04;
                    key.mHash = 0x2f7d0004;
                    SetToolTip(pOld, pText->GetText(&key, 0), pProfile->mpIconBlock);
                }
            }
            else if (pRecord->mKind18 == 2)
            {
                // planet statistics: the last unlocked planet reads differently
                const int numPlanets = FUN_00bbce40(cSPLivingUniverse::GetActivePlanetRecord()) + 1;
                cString_s0106_f5b0* pText = (pRecord->mIndex20 == numPlanets) ? &s388 : &s39c;
                SetToolTip(pOld, pText->GetText(0, 0), 0);
            }
            else if (pRecord->mKind18 == 3)
            {
                // editor verb icon: the plant / tool size picks the tooltip string
                cString_s0106_f5b0* pText = 0;
                if (pRecord->mKind10 == 0)
                {
                    if (pRecord->mSubType14 == 0x29c388a)      pText = &s338;
                    else if (pRecord->mSubType14 == 0x3a8be428) pText = &s34c;
                    else if (pRecord->mSubType14 == 0x6d60a1cc) pText = &s324;
                }
                else if (pRecord->mKind10 == 1)                pText = &s360;
                else if (pRecord->mKind10 == 2)                pText = &s374;
                if (pText == 0)
                    goto done;
                SetToolTip(pOld, pText->GetText(0, 0), 0);
            }
            else
                goto done;
    }
    else if (classHash == 0x3e1a6a5)                        // star object
    {
        mb5d4 = same;
    }
    else if (classHash == 0x678fa20)
    {
        // terraforming manager: count the unlocked planets to pick the tooltip string
        if (!same)
            goto done;
        const int index = (int)typeId - 0x535cbd8;
        const int numUnlocked = TerraformingManager()->GetUnlockedCount();
        cPlayerCivilization* pCiv = NounManager_s0106_f5b0()->GetPlayerCivilization();
        if (numUnlocked > index)
        {
            if (pCiv != 0 && index < pCiv->GetNounCount())
            {
                cGameNoun* pNoun = pCiv->GetNounList()->mpNouns[index];
                SetToolTip(pOld, pNoun->mAction.GetName(0, 0, 0), 0);
                goto done;
            }
            SetToolTip(pOld, s4f0.GetText(0, 0), 0);
            goto done;
        }
        SetToolTip(pOld, s4dc.GetText(0, 0), 0);
        goto done;
    }
    else if (classHash == 0x70648eae)
    {
        refreshAudio = true;
    }
    else
    {
        // any other class: a civilization rollover follows the planet's focused civ
        if (typeId != 0x36c0957)
            goto done;
        cSPLivingUniverse* pActive = cSPLivingUniverse::GetActivePlanet();
        if (pActive == 0)
            goto done;
        cPlayerCivilization* pCiv = (cPlayerCivilization*)pActive->GetFocusedCiv();
        if (pCiv != 0 && pCiv != (cPlayerCivilization*)cSPLivingUniverse::GetPlayerEmpire() && same)
            GetCivRollover()->ShowRelationshipRollover(pOld, pCiv->mId, false);
        else
            GetCivRollover()->HideRelationshipRollover();
    }

    // the delete button / editor focus also refreshes the editor info and the tooltip audio
    if (refreshAudio && same)
    {
        void* pInfo = FUN_01066120(typeId);
        FUN_0106e720(pOld, pInfo);
        if ((pOld->GetFocusFlags() & 2) != 0)
        {
            cAudioSystem* pAudio = GetSystemAT();
            KillSetiEffects(0xe784e681, pAudio != 0 ? (uint32_t)pAudio->GetParam() : 0);
        }
        else
        {
            cAudioSystem* pAudio = GetSystemAT();
            KillSetiEffects(0xb284b22, pAudio != 0 ? (uint32_t)pAudio->GetParam() : 0);
        }
    }

done:
    if (pNew != 0)
        pNew->Release();
    return false;
}
}  // namespace SP

// @ 0x010701e0
namespace SP {
uint32_t FUN_010701e0(const void* pList)
{
    uint32_t keyInstance = 0;
    Key_s0106_f5b0 toolId;
    if (GetPropertyAsKeyInstance(pList, &g_propKeyToolSlot, keyInstance))
    {
        toolId.mHash = keyInstance;
        toolId.mPad04 = 0;
        toolId.mPad08 = 0;
        cSPPlayerInventory* pInventory = SpaceGameGet_s0106_f5b0()->GetPlayerInventory();
        cSPTool* pTool = pInventory->GetToolFromToolID(toolId);
        if (pTool != 0)
        {
            GetUISpace()->FUN_0106e680(pTool);
            return GetUISpace()->FUN_0106edc0(pTool);
        }
        return 0;
    }
    return 0;
}
}  // namespace SP

// @ 0x01070890
void cSPUISpace_s0107_0290::ShowSavedGames()
{
    F0106f380();
    unsigned count = StarManager_s0107_0290()->mCivs.size();
    for (unsigned i = 0; i < count; ++i) {
        cProperty* value = 0;
        void* civ = StarManager_s0107_0290()->mCivs.mpBegin[i];
        if (civ != GetPlayerHomePlanet()->SortBanners()) {
            struct EffectsManager* effects = EffectsManagerPtr();
            if (value != 0) {
                cProperty* old = value;
                value = 0;
                old->Release();
            }
            if (effects->GetProperty(0xf0eb627c, 0, &value))
                value->V08(0);
            if (value != 0) {
                Matrix3_s0107_0290 rot = kSavedGameRot;
                cSavedGameRec rec(kSavedGamePos, rot);
                rec.mPos = *((cCivData_s0107_0290*)StarManager_s0107_0290()->mCivs.mpBegin[i])->GetCities();
                rec.mFlags |= 4;
                rec.mCount += 1;
                value->V14(&rec);
            }
            if (mSavedGameList.mpEnd < mSavedGameList.mpCapacity) {
                *mSavedGameList.mpEnd++ = value;
                if (value != 0)
                    value->AddRef();
            } else {
                mSavedGameList.insert(mSavedGameList.mpEnd, value);
            }
        }
        if (value != 0)
            value->Release();
    }
}

// @ 0x01070af0
void cFoodwebSlotVec::resize(unsigned count)
{
    if (count > size()) {
        cFoodwebSlotInfo value;
        insert(mpEnd, count - size(), value);
    } else {
        erase(mpBegin + count, mpEnd);
    }
}

// @ 0x01070ba0
#define cString cString_s0107_0ba0
namespace SP {
cSPUISpace_s0107_0ba0::cSPUISpace_s0107_0ba0()
{
  At<uint32_t>(0x4) = 0x13ec458;
  At<uint32_t>(0x8) = 0;
  At<uint32_t>(0xc) = 0x13eb384;
  At<uint32_t>(0x0) = 0x149c3ec;
  At<uint32_t>(0x4) = 0x149c3dc;
  At<uint32_t>(0xc) = 0x149c3cc;
  At<uint32_t>(0x10) = 0;
  At<uint32_t>(0x18) = 0;
  Str(0x1c)->cString::cString();
  Str(0x30)->cString::cString();
  Str(0x44)->cString::cString();
  Str(0x58)->cString::cString();
  Str(0x6c)->cString::cString();
  Str(0x80)->cString::cString();
  Str(0x94)->cString::cString();
  Str(0xa8)->cString::cString();
  Str(0xbc)->cString::cString();
  Str(0xd0)->cString::cString();
  Str(0xe4)->cString::cString();
  Str(0xf8)->cString::cString();
  Str(0x10c)->cString::cString();
  Str(0x120)->cString::cString();
  Str(0x134)->cString::cString();
  Str(0x148)->cString::cString();
  Str(0x15c)->cString::cString();
  Str(0x170)->cString::cString();
  Str(0x184)->cString::cString();
  Str(0x198)->cString::cString();
  Str(0x1ac)->cString::cString();
  Str(0x1c0)->cString::cString();
  Str(0x1d4)->cString::cString();
  Str(0x1e8)->cString::cString();
  Str(0x1fc)->cString::cString();
  Str(0x210)->cString::cString();
  At<uint32_t>(0x224) = 0;
  At<uint32_t>(0x228) = 0;
  At<uint32_t>(0x22c) = 0;
  At<uint32_t>(0x230) = 0;
  At<uint32_t>(0x234) = 0;
  At<uint32_t>(0x238) = 0;
  At<uint32_t>(0x23c) = 0;
  At<uint32_t>(0x240) = 0;
  At<uint32_t>(0x244) = 0;
  At<uint32_t>(0x248) = 0;
  At<uint32_t>(0x254) = 0;
  At<uint32_t>(0x258) = 0;
  At<float>(0x26c) = ConstOne();
  At<float>(0x270) = ConstTwo();
  At<uint32_t>(0x268) = 0;
  At<uint32_t>(0x274) = 0;
  At<uint32_t>(0x264) = 0x1;
  At<uint32_t>(0x260) = 0x154df28;
  At<uint32_t>(0x27c) = 0;
  At<uint32_t>(0x280) = 0;
  At<uint32_t>(0x284) = 0;
  At<uint32_t>(0x294) = 0;
  At<uint32_t>(0x298) = 0;
  At<uint32_t>(0x29c) = 0;
  At<float>(0x2b0) = ConstOne();
  At<float>(0x2b4) = ConstTwo();
  At<uint32_t>(0x2a4) = 0x154df28;
  At<uint32_t>(0x2a8) = 0x1;
  At<uint32_t>(0x2ac) = 0;
  At<uint32_t>(0x2b8) = 0;
  At<uint32_t>(0x2c0) = 0;
  At<uint32_t>(0x2c4) = 0;
  At<uint32_t>(0x2c8) = 0;
  At<float>(0x2e4) = ConstOne();
  At<float>(0x2e8) = ConstTwo();
  At<uint32_t>(0x2d8) = 0x154df28;
  At<uint32_t>(0x2dc) = 0x1;
  At<uint32_t>(0x2e0) = 0;
  At<uint32_t>(0x2ec) = 0;
  At<uint32_t>(0x2f4) = 0x68e0210;
  At<uint32_t>(0x2f8) = 0xffffffff;
  At<uint32_t>(0x2fc) = 0;
  At<uint32_t>(0x300) = 0;
  At<uint32_t>(0x304) = 0;
  At<uint32_t>(0x308) = 0;
  At<uint32_t>(0x30c) = 0;
  At<uint32_t>(0x310) = 0;
  At<uint32_t>(0x31c) = 0;
  Str(0x324)->cString::cString();
  Str(0x338)->cString::cString();
  Str(0x34c)->cString::cString();
  Str(0x360)->cString::cString();
  Str(0x374)->cString::cString();
  Str(0x388)->cString::cString();
  Str(0x39c)->cString::cString();
  Str(0x3b0)->cString::cString();
  Str(0x3c4)->cString::cString();
  Str(0x3d8)->cString::cString();
  Str(0x3ec)->cString::cString();
  Str(0x400)->cString::cString();
  Str(0x414)->cString::cString();
  Str(0x428)->cString::cString();
  Str(0x43c)->cString::cString();
  Str(0x450)->cString::cString();
  Str(0x464)->cString::cString();
  Str(0x478)->cString::cString();
  Str(0x48c)->cString::cString();
  Str(0x4a0)->cString::cString();
  Str(0x4b4)->cString::cString();
  Str(0x4c8)->cString::cString();
  Str(0x4dc)->cString::cString();
  Str(0x4f0)->cString::cString();
  At<uint32_t>(0x504) = 0;
  At<uint32_t>(0x508) = 0;
  At<uint32_t>(0x50c) = 0;
  At<uint32_t>(0x518) = 0;
  At<uint32_t>(0x51c) = 0;
  At<uint32_t>(0x520) = 0;
  At<float>(0x52c) = ConstOne();
  At<uint32_t>(0x530) = 0;
  At<uint32_t>(0x534) = 0;
  At<uint32_t>(0x538) = 0;
  At<uint32_t>(0x56c) = 0;
  At<uint32_t>(0x570) = 0;
  At<uint32_t>(0x574) = 0;
  At<uint32_t>(0x578) = 0;
  At<uint32_t>(0x57c) = 0;
  At<uint32_t>(0x580) = 0;
  At<uint32_t>(0x584) = 0;
  At<uint32_t>(0x588) = 0;
  At<uint32_t>(0x58c) = 0;
  At<uint32_t>(0x590) = 0;
  At<uint32_t>(0x594) = 0;
  At<uint32_t>(0x598) = 0;
  At<uint32_t>(0x59c) = 0;
  At<uint32_t>(0x5a0) = 0;
  At<uint32_t>(0x5a4) = 0;
  At<uint32_t>(0x5a8) = 0;
  At<uint32_t>(0x5ac) = 0;
  At<uint32_t>(0x5b0) = 0;
  At<uint32_t>(0x5b4) = 0;
  At<uint32_t>(0x5b8) = 0;
  At<uint32_t>(0x5bc) = 0;
  At<uint32_t>(0x5c0) = 0;
  At<uint32_t>(0x5c4) = 0;
  At<uint32_t>(0x5c8) = 0;
  At<uint32_t>(0x5cc) = 2;
  At<uint8_t>(0x5d0) = 0;
  At<uint8_t>(0x5d1) = 0;
  At<uint8_t>(0x5d2) = 0;
  At<uint8_t>(0x5d3) = 0;
  At<uint8_t>(0x5d4) = 0;
  At<uint8_t>(0x5d5) = 1;
  At<uint32_t>(0x5d8) = 0;
  At<uint32_t>(0x5dc) = 0;
  At<uint32_t>(0x5e0) = 0;
  At<uint32_t>(0x5ec) = 0;
  At<uint32_t>(0x5f0) = 0;
  At<uint32_t>(0x5f4) = 0;
  At<uint32_t>(0x5f8) = 0;
  At<uint32_t>(0x5fc) = 0;
  At<uint32_t>(0x600) = 0;
  At<uint32_t>(0x604) = 0;
  At<uint32_t>(0x608) = 0;
  At<uint32_t>(0x60c) = 0;
  At<uint32_t>(0x610) = 0;

  reinterpret_cast<Callee5ec*>(reinterpret_cast<char*>(this) + 0x5ec)->Init(0);
  At<uint32_t>(0x618) = 0;
  At<uint32_t>(0x61c) = 0;
  reinterpret_cast<Callee620*>(reinterpret_cast<char*>(this) + 0x620)->Init();
  At<uint32_t>(0x694) = 0;
  At<uint32_t>(0x698) = 0;
  At<uint32_t>(0x69c) = 0;
  At<uint32_t>(0x6a0) = 0;
  UI::MissionCardAnimator* animator =
      new (reinterpret_cast<const char*>(0x013f6b3c), 0, 0, 0, 0) UI::MissionCardAnimator();
  At<UI::MissionCardAnimator*>(0x568) = animator;
  *reinterpret_cast<cSpaceTokenTranslator_s0107_0ba0**>(0x016e0d08) =
      new ("Simulator", 0, 0, 0, 0) cSpaceTokenTranslator_s0107_0ba0();
  GetVSlotsSingleton()->S8()->S7(*reinterpret_cast<cSpaceTokenTranslator_s0107_0ba0**>(0x016e0d08));
  Str(0x324)->Load(0x2db6dad3, 0x539aa94, 0);
  Str(0x338)->Load(0x2db6dad3, 0x539aa95, 0);
  Str(0x34c)->Load(0x2db6dad3, 0x539aa96, 0);
  Str(0x360)->Load(0x2db6dad3, 0x539aa97, 0);
  Str(0x374)->Load(0x2db6dad3, 0x539aa98, 0);
  Str(0x388)->Load(0x2db6dad3, 0x539aae8, 0);
  Str(0x39c)->Load(0x2db6dad3, 0x61dfe83, 0);
  Str(0x3b0)->Load(0x2db6dad3, 0x3e81c64, 0);
  Str(0x3c4)->Load(0x2db6dad3, 0x3e98b08, 0);
  Str(0x3d8)->Load(0x2db6dad3, 0x63c3d96, 0);
  Str(0x3ec)->Load(0x2db6dad3, 0x6748f94, 0);
  Str(0x400)->Load(0x2db6dad3, 0x3e98b09, 0);
  Str(0x414)->Load(0x2db6dad3, 0x3e98b0a, 0);
  Str(0x43c)->Load(0x2db6dad3, 0x3eadfd0, 0);
  Str(0x450)->Load(0x2db6dad3, 0x3eafdd3, 0);
  Str(0x464)->Load(0x2db6dad3, 0x3ebf7a8, 0);
  Str(0x478)->Load(0x2db6dad3, 0x3edfdd4, 0);
  Str(0x4a0)->Load(0x2db6dad3, 0x4729a65, 0);
  Str(0x48c)->Load(0x2db6dad3, 0x3edfdd5, 0);
  Str(0x4c8)->Load(0x2db6dad3, 0x37c32cc, 0);
  Str(0x1c)->Load(0x63bfe3fe, 0x3ffe77b, 0);
  Str(0x30)->Load(0x63bfe3fe, 0x3ffe7fb, 0);
  Str(0x44)->Load(0x63bfe3fe, 0x3ffe7ff, 0);
  Str(0x58)->Load(0x63bfe3fe, 0x3ffe803, 0);
  Str(0x6c)->Load(0x63bfe3fe, 0x4374114, 0);
  Str(0x80)->Load(0x63bfe3fe, 0x4374125, 0);
  Str(0x94)->Load(0x63bfe3fe, 0x4377191, 0);
  Str(0xa8)->Load(0x63bfe3fe, 0x4377196, 0);
  Str(0xbc)->Load(0x63bfe3fe, 0x43ad9e0, 0);
  Str(0xd0)->Load(0x63bfe3fe, 0x43ad9f2, 0);
  Str(0xe4)->Load(0x2db6dad3, 0x654cb13, 0);
  Str(0xf8)->Load(0x2db6dad3, 0x654cb16, 0);
  Str(0x10c)->Load(0x2db6dad3, 0x654cb0a, 0);
  Str(0x120)->Load(0x2db6dad3, 0x654cb0f, 0);
  Str(0x134)->Load(0x2db6dad3, 0x43db6b2, 0);
  Str(0x148)->Load(0x2db6dad3, 0x43db6b1, 0);
  Str(0x15c)->Load(0x2db6dad3, 0x43db6b3, 0);
  Str(0x170)->Load(0x2db6dad3, 0x43db6b4, 0);
  Str(0x184)->Load(0x2db6dad3, 0x43db6b5, 0);
  Str(0x198)->Load(0x2db6dad3, 0x43db6b7, 0);
  Str(0x1ac)->Load(0x2db6dad3, 0x43db6b8, 0);
  Str(0x1e8)->Load(0x2db6dad3, 0x43db6b9, 0);
  Str(0x1c0)->Load(0x2db6dad3, 0x4c82968, 0);
  Str(0x1d4)->Load(0x2db6dad3, 0x510b24f, 0);
  Str(0x4b4)->Load(0x2db6dad3, 0x473d0cf, 0);
  Str(0x1fc)->Load(0xc0152a6d, 0x615ffa7, 0);
  Str(0x210)->Load(0xc0152a6d, 0x615ffa8, 0);
  Str(0x4dc)->Load(0x2db6dad3, 0x678eecf, 0);
  Str(0x4f0)->Load(0x2db6dad3, 0x678eed0, 0);
}
#undef cString
}  // namespace SP

// @ 0x01071570
namespace SP {
void cSPUISpace_s0107_0ba0::Shutdown()
{
  GetCurMgr()->FindLocal(0x1002);

  m2a0.F(m2a0.mp4, m2a0.m8);
  m2a0.mc = 0;

  if (IsWorldLayoutFlagSet(2)) {
    if (mp694) {
      if (mpLayout258) {
        IWindow_s0107_0ba0* pWnd = mpLayout258->FindWindowByID(0x755f180, 1);
        if (pWnd->V028() & 1) mp694->F_fe7e10();
      }
      if (mp694) {
        IWindow_s0107_0ba0* p = mp694;
        if (p) {
          mp694 = 0;
          p->V004();
        }
      }
    }
    ILayout* pLayout = mpLayout258;
    if (pLayout) {
      pLayout->Shutdown(1);
      ILayout* p = mpLayout258;
      if (p) {
        mpLayout258 = 0;
        p->V008();
      }
    }
  }

  FUN_0106f540();
  mDeque5ec.clear();
  IGlobal0810* pGlobal = GetGlobal0810();
  if (pGlobal) pGlobal->SetParent(0);
  mVec530.erase(mVec530.mpBegin, mVec530.mpEnd);
  FUN_0106ef30();
  FUN_01068230();

  {
    CTooltip* p = mp5a8;
    if (p) {
      p->Shutdown();
      CTooltip* q = mp5a8;
      if (q) {
        mp5a8 = 0;
        q->Release();
      }
    }
  }
  {
    IWindow_s0107_0ba0* p = mp59c;
    if (p) {
      mp59c = 0;
      p->V004();
    }
  }
  {
    IWindow_s0107_0ba0* p = mp598;
    if (p) {
      mp598 = 0;
      p->V004();
    }
  }
  {
    IWindow_s0107_0ba0* p = mp5a0;
    if (p) {
      mp5a0 = 0;
      p->V004();
    }
  }

  mpRef228->F_e28a80();
  {
    IRefObj* p = mpRef228;
    if (p) {
      mpRef228 = 0;
      p->Release();
    }
  }

  {
    IWindow_s0107_0ba0* p = mp580;
    if (p) {
      mp580 = 0;
      p->V004();
    }
  }

  mp5a4->V024();
  {
    IWindow_s0107_0ba0* p = mp5a4;
    if (p) {
      mp5a4 = 0;
      p->V004();
    }
  }

  m2f8 = -1;
  if (mp10) {
    mp10->V008(1);
    mp10 = 0;
  }

  IWindow_s0107_0ba0* pWindow = mpGlobalUI->FindWindowByID(0xffffffff);
  if (pWindow) {
    pWindow->V000();
    pWindow->V108(this);
  }

  FUN_00b3d230_s0107_0ba0()->V044();

  if (g16e2234) {
    g16e2234->V008();
    g16e2234 = 0;
  }

  {
    ILayout* p = mpLayout22c;
    if (p) {
      p->Shutdown(1);
      ILayout* q = mpLayout22c;
      if (q) {
        mpLayout22c = 0;
        q->V008();
      }
    }
  }
  {
    ILayout* p = mpLayout230;
    if (p) {
      p->Shutdown(1);
      ILayout* q = mpLayout230;
      if (q) {
        mpLayout230 = 0;
        q->V008();
      }
    }
  }
  {
    ILayout* p = mpLayout234;
    if (p) {
      p->Shutdown(1);
      ILayout* q = mpLayout234;
      if (q) {
        mpLayout234 = 0;
        q->V008();
      }
    }
  }

  if (mp31c) {
    IWindow_s0107_0ba0* pWnd = mpGlobalUI->FindWindowByID(0x190722e);
    if (pWnd) pWnd->V0dc(mp31c ? &mp31c->mpField4 : 0);
    mp31c->V01c();
    IObj31c* p = mp31c;
    if (p) {
      mp31c = 0;
      p->V004();
    }
  }

  {
    IObjCArg* p = mp2fc;
    if (p) {
      p->V00c(1);
      IObjCArg* q = mp2fc;
      if (q) {
        mp2fc = 0;
        q->V004();
      }
    }
  }
  {
    IObjCArg* p = mp300;
    if (p) {
      p->V00c(1);
      IObjCArg* q = mp300;
      if (q) {
        mp300 = 0;
        q->V004();
      }
    }
  }
  {
    IObjCArg* p = mp304;
    if (p) {
      p->V00c(1);
      IObjCArg* q = mp304;
      if (q) {
        mp304 = 0;
        q->V004();
      }
    }
  }

  if (mpGlobalUI) {
    mpGlobalUI->V00c();
    mpGlobalUI = 0;
  }

  if (m56c) {
    EA::Messaging::RemoveHandler(m56c, m570, m574, m578, m57c);
    m56c = 0;
  }

  CheatManager()->V01c(g15b7330);

  {
    IWindow_s0107_0ba0* p = mp5c4;
    if (p) {
      p->V088();
      IWindow_s0107_0ba0* q = mp5c4;
      if (q) {
        mp5c4 = 0;
        q->V004();
      }
    }
  }

  FUN_010673f0(0);
  FUN_01067510(0);

  {
    IWindow_s0107_0ba0* p = mp588;
    if (p) {
      mp588 = 0;
      p->V004();
    }
  }
  {
    IWindow_s0107_0ba0* p = mp584;
    if (p) {
      mp584 = 0;
      p->V0c0();
    }
  }

  if (pWindow) pWindow->V004();
}
}  // namespace SP

// @ 0x01071a00
void SP::cSPUISpace_s0107_1a00::InitFoodwebInfo()
{
    mFoodwebSlots.resize(0x12);
    for (int i = 0; i < 9; i++) {
        FoodwebSlotInfo& slot = mFoodwebSlots.mpBegin[i];
        UIWindow* w = mGlobalLayout->FindWindowByID((uint32_t)(i + 0x37e89d0));
        UIWindow* old = slot.mpWindow;
        if (w != old) {
            if (w != 0)
                w->v00();
            slot.mpWindow = w;
            if (old != 0)
                old->v01();
        }
        slot.mKind = 0;
        if (i == 0 || i == 3 || i == 6)
            slot.mKey = 0x6d60a1cc;
        else if (i == 1 || i == 4 || i == 7)
            slot.mKey = 0x29c388a;
        else
            slot.mKey = 0x3a8be428;
        slot.mIndex = (int)((unsigned)i / 3) + 1;
        VT1(void, slot.mpWindow, 0x104, this);
    }
    for (int i = 0; i < 6; i++) {
        FoodwebSlotInfo& slot = mFoodwebSlots.mpBegin[9 + i];
        UIWindow* w = mGlobalLayout->FindWindowByID((uint32_t)(i + 0x37e89d9));
        UIWindow* old = slot.mpWindow;
        if (w != old) {
            if (w != 0)
                w->v00();
            slot.mpWindow = w;
            if (old != 0)
                old->v01();
        }
        slot.mIndex = (int)((unsigned)i >> 1) + 1;
        slot.mFlag = i & 1;
        slot.mKind = 1;
        VT1(void, slot.mpWindow, 0x104, this);
    }
    // Rows 15..17 hold the three crop slots.
    for (int i = 0; i < 3; i++) {
        FoodwebSlotInfo& slot = mFoodwebSlots.mpBegin[15 + i];
        UIWindow* w = mGlobalLayout->FindWindowByID((uint32_t)(i + 0x37e89df));
        UIWindow* old = slot.mpWindow;
        if (w != old) {
            if (w != 0)
                w->v00();
            slot.mpWindow = w;
            if (old != 0)
                old->v01();
        }
        slot.mKind = 2;
        slot.mIndex = i + 1;
        VT1(void, slot.mpWindow, 0x104, this);
    }
    for (int i = 0; i < 3; i++) {
        UIWindow* w = mGlobalLayout->FindWindowByID((uint32_t)(i + 0x535cbd8));
        VT1(void, w, 0x104, this);
    }
}

// @ 0x01071c20
void SP::cSPUISpace_s0107_1a00::SetupFoodwebWindows(int arg)
{
    int count = FUN_0106b860(arg);
    mFlags.erase(mFlags.mpBegin, mFlags.mpEnd);
    int empire = GetPlayerEmpireID();
    mFlags.SetValues(count, &empire);
    mWindowSet.RefreshWindows();
    UIWindow* w = mpLayout->FindWindowByID(0x755f9b8, 1);
    Key12 desc;
    desc.a = 0;
    desc.b = 0;
    desc.c = 0;
    mWindowSet.AttachWindow(w, &desc);
    Key12 key;
    key.a = 0x1879822f;
    key.b = 0x510a95b;
    key.c = 0x40464100;
    mWindowSet.SetFlags(&key, 3);
    Ufo* ufo = GetUFOSimulator_s0107_1a00();
    UfoList* list = ufo->GetList();
    UfoNode* it = list->mpNext;
    for (int i = 0; i < 3; i++) {
        if (i < count) {
            if (it != list) {
                mFlags.mpBegin[i] = (uint32_t)it->mValue;
                it = it->mpNext;
            }
            SetSlotValue(i, mFlags.mpBegin[i]);
        } else {
            void* p = mWindowSet.GetSlotLayout(i);
            if (p == 0)
                return;
            UIWindow* w2 = ((UILayout*)p)->FindWindowByID(0x7eb2ea0, 1);
            if (w2 != 0)
                w2->SetFlag(1, 1);
        }
    }
}

// @ 0x01071d70
void SP::cSPUISpace_s0107_1a00::UpdateTerraformingSlots()
{
    {
    uint32_t idsLock[4] = { 0, 0x36969ff, 0x3696a10, 0x3696a1a };
    uint32_t idsTool[4] = { 0, 0x3693f49, 0x3693f3e, 0x3693f23 };
    uint32_t idsIcon[4] = { 0, 0x535cbd8, 0x535cbd9, 0x535cbda };

    if (SPUIHelpers_GetElapsedSeconds() > kRefreshInterval) {
        TerraformMgr* tm = GetTerraformingManager();
        if (tm->F670(0) == -1)
            return;
        NounManager_s0107_1a00* nm = GetNounManager();
        ElemVector* dataVec = nm->GetGameDataVector((void*)FUN_00cd7d10, (void*)FUN_00d3d420,
                                                    (void*)FUN_00acdff0, (void*)FUN_00b1e500, 0x18c43e8);
        int count1 = (int)(dataVec->mpEnd - dataVec->mpBegin);
        int count2 = tm->GetUnlockedCount(0);
        Planet_s0107_1a00* planet = GetActivePlanet_s0107_1a00();
        PlanetRecord_s0107_1a00* rec = planet->mpRecord;
        Key_s0107_1a00 keyA = tm->GetKeyA();
        Key_s0107_1a00 keyB = tm->GetKeyB();
        Key_s0107_1a00 k = gNullKey_s0107_1a00;
        int i = 1;
        int c4 = 0x37e89da;
        int d0 = 0x37e89d2;
        do {
            UIWindow* w = mGlobalLayout->FindWindowByID(idsIcon[i]);
            if (w) {
                if (count1 >= i) {
                    SetWindowImageResource(w, &kSlotImages[0], 0);
                    SetWindowImageResource(w, &kSlotImages[1], 2);
                    SetWindowImageResource(w, &kSlotImages[2], 3);
                } else if (count2 < i) {
                    SetWindowImageResource(w, &kSlotImages[6], 0);
                    SetWindowImageResource(w, &kSlotImages[7], 2);
                    SetWindowImageResource(w, &kSlotImages[8], 3);
                } else {
                    SetWindowImageResource(w, &kSlotImages[3], 0);
                    SetWindowImageResource(w, &kSlotImages[4], 2);
                    SetWindowImageResource(w, &kSlotImages[5], 3);
                }
            }
            bool locked = !tm->F6a0(i, rec);
            UIWindow* w1 = mGlobalLayout->FindWindowByID(idsLock[i]);
            UIWindow* w2 = mGlobalLayout->FindWindowByID(idsTool[i]);
            if (w1 && w2) {
                w1->SetFlag(1, locked);
                w2->SetFlag(1, !locked);
            }
            bool same, flagA, scanned;

            flagA = locked || !tm->F850(i, 1, rec);
            k = tm->F870(i, 0x6d60a1cc, rec);
            scanned = planet->SetSpeciesAsScanned(&k);
            same = !(gNullKey_s0107_1a00 == keyA) && k == keyA;
            SetSlot(d0 - 2, locked, &k, scanned, flagA, same);

            flagA = locked || !tm->F850(i, 2, rec);
            k = tm->F870(i, 0x29c388a, rec);
            scanned = planet->SetSpeciesAsScanned(&k);
            same = !(gNullKey_s0107_1a00 == keyA) && k == keyA;
            SetSlot(d0 - 1, locked, &k, scanned, flagA, same);

            flagA = locked || !tm->F850(i, 3, rec);
            k = tm->F870(i, 0x3a8be428, rec);
            scanned = planet->SetSpeciesAsScanned(&k);
            same = !(gNullKey_s0107_1a00 == keyA) && k == keyA;
            SetSlot(d0, locked, &k, scanned, flagA, same);

            flagA = locked || !tm->F850(i, 4, rec);
            k = tm->F950(i, 0, rec);
            scanned = planet->SetSpeciesAsScanned(&k);
            same = !(gNullKey_s0107_1a00 == keyB) && k == keyB;
            SetSlot(c4 - 1, locked, &k, scanned, flagA, same);

            flagA = locked || !tm->F850(i, 5, rec);
            k = tm->F950(i, 1, rec);
            scanned = planet->SetSpeciesAsScanned(&k);
            same = !(gNullKey_s0107_1a00 == keyB) && k == keyB;
            SetSlot(c4, locked, &k, scanned, flagA, same);

            flagA = locked || !tm->F850(i, 6, rec);
            k = tm->Fa30(i, rec);
            scanned = planet->SetSpeciesAsScanned(&k);
            same = !(gNullKey_s0107_1a00 == keyB) && k == keyB;
            SetSlot(i + 0x37e89de, locked, &k, scanned, flagA, same);
            d0 += 3;
            c4 += 2;
            ++i;
        } while (c4 <= 0x37e89de);
        bool bit = (GetActivePlanetRecord_s0107_1a00()->mFlags >> 11) & 1;
        UIWindow* wb = mGlobalLayout->FindWindowByID(0x52c2948);
        if (wb)
            wb->SetFlag(1, bit);
        if (bit) {
            UIWindow* wc = mGlobalLayout->FindWindowByID(0x680d440);
            if (wc) {
                int v = 100;
                PropertyHolder* holder = *GetPropertyHolder();
                Property_s0107_1a00* prop;
                if (holder && holder->GetProperty(0x5469bf8, &prop) && prop->mType == 9)
                    v = *prop->GetData();
                FixedStr16 s;
                s.sprintf(L"%d/%d", (rec->mpKeysEnd - rec->mpKeysBegin) / 12, v);
                wc->SetCaption(s.mpBegin);
            }
        }
    }
    }
    if (gDebugFlag6ee && !gDebugFlag6ec && !gDebugFlag6ed) {
        GetTerraformingManager();
        GetB3d420();
        GetB3d450();
        GetActivePlanet_s0107_1a00();
        KeySet set;
        NounManager_s0107_1a00* nm = GetNounManager();
        ElemVector* dataVec = nm->GetGameDataVector((void*)FUN_00cd7d10, (void*)FUN_00d3d420,
                                                    (void*)FUN_00b2d9d0, (void*)FUN_00b1e500, 0x18c84a9);
        int n = (int)(dataVec->mpEnd - dataVec->mpBegin);
        for (int i = 0; i < n; ++i)
            set.insert(dataVec->mpBegin[i]->GetKey());
    }
}

// @ 0x01072680
void SP::cSPUISpace_s0107_1a00::RefreshPosseItems()
{
    if (mpPosse == 0)
        return;
    ElemVector* v = GetNounManager()->GetGameDataVector((void*)FUN_00cd7d10, (void*)FUN_00d3d420,
                                                        (void*)FUN_00ad48b0, (void*)FUN_00b1e500,
                                                        0x18ebadc);
    Elem** it = v->mpBegin;
    Elem** end = v->mpEnd;
    while (it != end) {
        Elem* noun = *it;
        if (noun->mType == 3) {
            UfoItem* item = (UfoItem*)mpPosse->FindItem(noun);
            if (item != 0)
                VT4F(void, item, 0x80, 0x3d99162, noun->mSim.NodeRatio() * kRatioScale, 1, 1);
        }
        ++it;
    }
    TerrainEditor_s0107_1a00* te = GetNounManager()->GetCurrentTerrainSphere();
    int n = te->mField;
    while ((int)(mpPosse->mpEnd - mpPosse->mpBegin) < n) {
        void* raw = FUN_009512d0(0x14c, 4, "UI/PosseItem", FUN_009512c0());
        void* item = raw != 0 ? ((PosseItemSpace*)raw)->Construct(0) : 0;
        VT1(void, mpPosse, 0xa4, item);
        VT1(void, mpPosse, 0xc0, 1);
    }
}

// @ 0x010727e0
uint8_t __stdcall FUN_0106b7e0_s0107_27e0(void* self, void* icon);  // 0x0106b7e0
#define FnU0 FnU0_s0107_27e0
#define FnV0 FnV0_s0107_27e0
#define FnV2 FnV2_s0107_27e0
#define FnVP2 FnVP2_s0107_27e0
#define FnVU1 FnVU1_s0107_27e0
#define FnRU1 FnRU1_s0107_27e0
#define FnPU1 FnPU1_s0107_27e0
#define FnObj FnObj_s0107_27e0
#define FnVP2_6 FnVP2_6_s0107_27e0
#define FnVP2_1 FnVP2_1_s0107_27e0
#define Vt Vt_s0107_27e0
#define VCall0 VCall0_s0107_27e0
#define VCallU1 VCallU1_s0107_27e0
#define VCallV0 VCallV0_s0107_27e0
#define VCallV2 VCallV2_s0107_27e0
#define VCallVP2 VCallVP2_s0107_27e0
#define VCallVP2_1 VCallVP2_1_s0107_27e0
#define VCallP1 VCallP1_s0107_27e0
#define AudioSlot8 AudioSlot8_s0107_27e0
#define Lu32 Lu32_s0107_27e0
namespace {

typedef uint32_t (__thiscall* FnU0)(void*);
typedef void     (__thiscall* FnV0)(void*);
typedef void     (__thiscall* FnV2)(void*, uint32_t, uint32_t);
typedef void     (__thiscall* FnVP2)(void*, void*, void*);
typedef void     (__thiscall* FnVU1)(void*, uint32_t);
typedef uint32_t (__thiscall* FnRU1)(void*, uint32_t);
typedef void*    (__thiscall* FnPU1)(void*, uint32_t);
typedef void*    (__thiscall* FnObj)(void*);
typedef void     (__thiscall* FnVP2_6)(void*, const void*, void*, int, int, int, int);
typedef void     (__thiscall* FnVP2_1)(void*, const void*);

inline void** Vt(void* p) { return *(void***)p; }

uint32_t VCall0(void* o, uint32_t off) { return ((FnU0)Vt(o)[off / 4])(o); }
uint32_t VCallU1(void* o, uint32_t off, uint32_t a) { return ((FnRU1)Vt(o)[off / 4])(o, a); }
void     VCallV0(void* o, uint32_t off) { ((FnV0)Vt(o)[off / 4])(o); }
void     VCallV2(void* o, uint32_t off, uint32_t a, uint32_t b) {
    ((FnV2)Vt(o)[off / 4])(o, a, b);
}
void     VCallVP2(void* o, uint32_t off, void* a, void* b) {
    ((FnVP2)Vt(o)[off / 4])(o, a, b);
}
void     VCallVP2_1(void* o, uint32_t off, const void* a) { ((FnVP2_1)Vt(o)[off / 4])(o, a); }
void*    VCallP1(void* o, uint32_t off, uint32_t a) { return ((FnPU1)Vt(o)[off / 4])(o, a); }

uint32_t AudioSlot8()
{
    void* at = FUN_00a206f0();
    return at ? VCall0(at, 0x20) : 0;
}

inline uint32_t Lu32(const void* p) { return *(const uint32_t*)p; }

}  // namespace
void SP::cSPUISpace_s0107_27e0::ShowCreatureTooltip(void* arg1, uint32_t arg2)
{
    void* game = SpaceGameGet_s0107_27e0();
    void* spaceUI = game ? *(void**)((uint8_t*)game + 0x14) : 0;

    IWindow_s0107_27e0* w = ((cSPUISpace_s0107_27e0*)spaceUI)->mpGlobalUI->FindWindowByID(0x5e66e88);
    if (w) {
        mpLayout->SetParentWin(0, 1, 0x5b598fa);
        mpLayout->SetParentWin(w, 1, 0x5b598fa);
    }
    w = mpLayout->FindWindowByID(0x755f180, 1);
    if (w)
        VCallV2(w, 0x7c, 1, 1);

    cEmpire_s0107_27e0* empire = (cEmpire_s0107_27e0*)GetPlayerEmpire_s0107_27e0();
    Vec3i ids = *empire->GetIds();

    // foodweb key (used by the SetupFoodwebWindows call and the tooltip lookup)
    uint32_t state = 0;
    cSimulator* sim = (cSimulator*)GetUFOSimulator_s0107_27e0();
    cInventory* inv = sim->GetPlayerInventory();
    if (inv->mp75c)
        state = inv->mp75c->mpStar->GetState();

    uint32_t foodwebKey[3];
    foodwebKey[0] = state;
    foodwebKey[1] = 0x366a930du;
    foodwebKey[2] = DAT_015b9108_s0107_27e0;

    FUN_01071c20(state);

    if (*(uint8_t*)arg1 != 0) {
        if (arg2 == 0x7ce1750u)
            ((cOverlay*)mpOverlay)->SetMode(0);
        else if (arg2 == 0x7ce3cb0u)
            ((cOverlay*)mpOverlay)->SetMode(2);
    } else if (((cOverlay*)mpOverlay)->Test()) {
        ((cOverlay*)mpOverlay)->SetMode(0);
    } else {
        // asset lookup for this creature
        uint32_t iconKey[3];
        iconKey[0] = ids.mX;
        iconKey[1] = 0x30bdee3u;
        iconKey[2] = DAT_015b9108_s0107_27e0;

        void* res = 0;
        void* mgr = GetResourceManager();
        ((FnVP2_6)Vt(mgr)[0xc / 4])(mgr, iconKey, &res, 0, 0, 0, 0);
        if (res) {
            void* asset = VCallP1(res, 0xc, 0x30bdee3u);
            if (asset) {
                ((FnU0)Vt(asset)[0])(asset);
                const wchar_t* name = ((cAsset*)asset)->GetName();
                const wchar_t* summary = ((cAsset*)asset)->GetSummary();
                w = mpLayout->FindWindowByID(0x75608a4, 1);
                if (w) {
                    VCallV2(w, 0x7c, 1, 1);
                    VCallVP2_1(w, 0x80, (void*)summary);
                }
                w = mpLayout->FindWindowByID(0x76b68d2, 1);
                if (w) {
                    VCallV2(w, 0x7c, 1, 1);
                    VCallVP2_1(w, 0x80, (void*)name);
                }
            }
            w = mpLayout->FindWindowByID(0x7c7c590, 1);
            if (w) {
                if (FUN_00eed840(&ids)) {
                    cString_s0107_27e0 tip(0x3dade1bbu, 0x7ec9f8cu, 0);
                    VCallVP2_1(w, 0x80, tip.GetText());
                    VCallV2(w, 0x7c, 1, 1);
                } else if (FUN_00eed970(&ids, foodwebKey)) {
                    cString_s0107_27e0 tip(0x3dade1bbu, 0x7ec9f8bu, 0);
                    VCallVP2_1(w, 0x80, tip.GetText());
                    VCallV2(w, 0x7c, 1, 1);
                } else {
                    VCallV2(w, 0x7c, 1, 0);
                }
            }
            uint32_t imgKey[3];
            imgKey[0] = ids.mX;
            imgKey[1] = 0x2f7d0004u;
            imgKey[2] = DAT_015b9108_s0107_27e0;

            w = mpLayout->FindWindowByID(0x756083b, 1);
            if (w) {
                if (FUN_0106b7e0_s0107_27e0(w, imgKey)) {
                    float* area = (float*)VCall0(w, 0x38);
                    float x0 = area[0], y0 = area[1];
                    float x1 = area[2], y1 = area[3];
                    float cx = (x0 + x1) * kHalf;
                    float cy = (y0 + y1) * kHalf;
                    float ww = x1 - x0;
                    float hh = y1 - y0;
                    float rad = (ww > hh ? hh : ww) * kHalf;
                    float rect[4] = { cx - rad, cy - rad, cx + rad, cy + rad };
                    VCallVP2_1(w, 0x6c, rect);
                }
            }
            ((cOverlay*)mpOverlay)->SetMode(1);
            VCallV0(res, 4);
        }
    }

    void* game2 = SpaceGameGet_s0107_27e0();
    void* spaceUI2 = game2 ? *(void**)((uint8_t*)game2 + 0x14) : 0;
    ((cInputMgr*)GameInputManager())->mCounter++;
    void* wm = WindowManager_s0107_27e0();
    void* modal = ((FnObj)Vt(wm)[4 / 4])(wm);
    if (modal && (uint8_t*)modal - 4 != 0)
        FUN_00812d80((uint8_t*)modal - 4, 1);
    ((cSPUISpace_s0107_27e0*)spaceUI2)->FUN_01066230(1);

    w = mpLayout->FindWindowByID(0x7551618, 1);
    if (w) {
        float rgb[3] = { kOne_s0107_27e0, kOne_s0107_27e0, kOne_s0107_27e0 };
        ((cUpdater*)GetUpdater490())->BindSlotCreature(&ids, 0x4d594c50u, rgb, 0, 0, w);
        ((cUpdater*)GetUpdater490())->SwapSlotObjects(1, 0, 0, 0);
    }

    Vec3i ids2 = *((cEmpire_s0107_27e0*)GetPlayerEmpire_s0107_27e0())->GetIds();
    if (((cSpeciesMgr_s0107_27e0*)GetSpeciesManager_s0107_27e0())->GetProfile(&ids2)) {
        for (uint32_t id = 0x7746f28u; id <= 0x7746f33u; id++) {
            w = mpLayout->FindWindowByID(id, 1);
            if (w)
                SetTooltipText(w, &DAT_013ec468, -1, 1);
        }
    }

    cEmpire_s0107_27e0* empire2 = (cEmpire_s0107_27e0*)GetPlayerEmpire_s0107_27e0();
    w = mpLayout->FindWindowByID(0x5edff88, 1);
    if (w) {
        void* keyObj = GetGlobalImageKey(empire2, 0);
        IWindow_s0107_27e0* image = ((cImageKey*)keyObj)->FUN_00dd2320(empire2, 0);
        SetImageFromKey(w, image);
    }
    w = mpLayout->FindWindowByID(0x6243260, 1);
    if (w) {
        uint8_t color[12];
        empire2->GetColor(color);
        VCallU1(w, 0xac, ColorRGBToU32(color));
    }

    void* gtm = GameTimeManager_s0107_27e0();
    ((FnVU1)Vt(gtm)[0x00b32220 / 4])(gtm, 0x7e9e4b7u);
    FUN_0106f3d0();
}

// @ 0x01072d40
bool SP::cSPUISpace_s0107_27e0::DoMessage(void* target, uint32_t* msg)
{
    if (msg[3] == DAT_015b90d8)
        return false;

    void* win = (void*)VCall0(target, 0x1c);

    if (msg[2] == 10)
        return DoFocusChange(target, msg);

    if (msg[2] == 7 && (VCall0(target, 0x28) & 2) == 0)
        RecordEvent2(0x566853b1u, AudioSlot8());

    if (msg[2] == 2 && (msg[4] == 0x1b || msg[4] == 0xd)) {
        IWindow_s0107_27e0* w = mpGlobalUI->FindWindowByID(0x664c270);
        if (w && (VCall0(w, 0x28) & 1)) {
            VCallV2(w, 0x7c, 1, 0);
            return true;
        }
    }

    FUN_01066780(target, msg);

    uint32_t id = msg[3];

    if (id == 0x3e1a6a5u) {
        RecordEvent2(0x399e11fbu, AudioSlot8());
        if (VCall0(target, 0x1c) != 0xffffffffu)
            return false;
        if (msg[2] != 0x287259f6u)
            return false;
        if (mpCommandDeleteCargoButtonState != 0)
            return true;

        void* pObj = operator_new(0x1cu, "Simulator", 0, 0, 0, 0);
        if (pObj)
            pObj = ((SP::cCommandDeleteCargoButtonState*)pObj)->Ctor(this, mDeleteButtonWindow);
        else
            pObj = 0;
        mpCommandDeleteCargoButtonState = pObj;

        IWindow_s0107_27e0* w = mpGlobalUI->FindWindowByID(0xffffffffu);
        AutoRefCount_Ctor(w);

        uint32_t k[4];
        k[2] = 0x410812au;
        k[3] = 0x410812au;

        void* wm = WindowManager_s0107_27e0();
        VCallVP2(wm, 0x10, win, k);
        if (win)
            VCallV0(win, 4);
        return true;
    }

    if (id == 0x2e1b720u || id == 0x2e1b6f8u || id == 0x2e1b708u ||
        id == 0x2e1cbd7u || id == 0x2e1b72cu || id == 0x2e1b73cu) {
        RecordEvent2(0xb2a58920u, GetRecorderState());
        IWindow_s0107_27e0* w = mpGlobalUI->FindWindowByID(id);
        if (w == 0)
            return true;
        void* button = interface_cast_IWinButton(w);
        if (button == 0)
            return true;
        uint32_t filter = convertStarMapButtonToFilter(id);
        cStarMap* sm = (cStarMap*)FUN_01046fc0();
        if (VCall0(button, 0x20) & 4)
            sm->FilterHelper(filter, 1);
        if ((VCall0(button, 0x20) & 4) == 0)
            sm->FilterHelper(filter, 0);
        FUN_010666b0();
        return true;
    }

    if (id == 0x2c38abau) {
        ((cFloatOwner*)FUN_01015df0())->FUN_01015f30(0.0f);
        return true;
    }
    if (id == 0x2699440u) {
        FUN_00e02c40();
        return true;
    }
    if (id == 0x17f29bfu) {
        if (FUN_01065e20())
            return false;
        return FUN_01067b60() != 0;
    }

    if (id == 0x37ab944u) {
        if (msg[2] != 0x287259f6u)
            return true;
        if (GetUniverseContext() != 0)
            return true;
        void* input = GameInputManager();
        ((FnV2)Vt(input)[0x64 / 4])(input, 0x37ab944u, 1);
        void* cursor = GetGameTerrainCursor();
        VCallV0(cursor, 0x64);
        return true;
    }

    if (id == 0x37e9018u) {
        if (msg[2] != 0x287259f6u)
            return true;

        void* blk = FUN_01067ef0((uint32_t)win);
        uint32_t mode = *(uint32_t*)((uint8_t*)blk + 0x18);
        if (mode != 0) {
            if (mode != 3)
                return true;
            FUN_0106f1a0(blk, 1);
            return true;
        }

        uint8_t bOld = (*(uint32_t*)((uint8_t*)blk + 0x10) == 0);
        Vec3i tmp;
        cTerraform* tm = (cTerraform*)TerraformingManager_s0107_27e0();
        Vec3i* src = (Vec3i*)(bOld ? tm->GetOld(&tmp) : tm->GetNew(&tmp));
        Vec3i cur;
        cur.mX = src->mX;
        cur.mY = src->mY;
        cur.mZ = src->mZ;
        Vec3i here = *(Vec3i*)((uint8_t*)blk + 4);

        if (FUN_004eb930(&cur, &here)) {
            ((cTerraform*)TerraformingManager_s0107_27e0())->StoreEmpty();
            RecordEvent2(0x53eca8bdu, GetRecorderState());
            return true;
        }
        if (bOld)
            ((cTerraform*)TerraformingManager_s0107_27e0())->Store3((int)here.mX, (int)here.mY, (int)here.mZ);
        else
            ((cTerraform*)TerraformingManager_s0107_27e0())->Store3B((int)here.mX, (int)here.mY, (int)here.mZ);
        RecordEvent2(0x3c7c63bcu, GetRecorderState());
        return true;
    }

    if (id == 0x447060au) {
        ShowContextSensitiveSporeGuide();
        return true;
    }

    if (id == 0x410812au) {
        if (VCall0(target, 0x1c) != 0xffffffffu)
            return false;
        if (FUN_01066570()) {
            IWindow_s0107_27e0* w = mpGlobalUI->FindWindowByID(0xffffffffu);
            AutoRefCount_Ctor(w);
            uint32_t k[4];
            k[0] = 0x410812au;
            k[1] = 0x410812au;
            void* wm = WindowManager_s0107_27e0();
            VCallVP2(wm, 0x18, win, k);
            goto shared_tail;
        }
        if (mpCommandDeleteCargoButtonState != 0)
            VCallU1(mpCommandDeleteCargoButtonState, 8, 1);
        mpCommandDeleteCargoButtonState = 0;
        return true;
    }

    if (id == 0x4359752u) {
        if (msg[2] != 0x287259f6u)
            return true;
        mb5d0 = (msg[5] != 0) ? 1 : 0;
        FUN_01067fb0();
        RecordEvent2(0xefaaa0c7u, GetRecorderState());
        return true;
    }

    if (id == 0x5232c00u) {
        if (msg[2] != 0x18)
            return true;
        void* button = interface_cast_IWinButton((void*)msg[0]);
        if (button == 0)
            return true;
        uint32_t flags = VCall0(button, 0x20);
        VCallV2(button, 0x28, 4, ((flags >> 2) & 1) == 0 ? 1 : 0);
        return true;
    }

    if (id == 0x562a141u) {
        if (msg[2] != 0x287259f6u)
            return false;
        uint8_t b = FUN_01068080();
        RecordEvent2(0x98b8139du + (b ? 0x6c491d1au : 0), GetRecorderState());
        return true;
    }

    if (id == 0x65680e8u || id == 0x65ce2da) {
        if (msg[2] != 0x287259f6u)
            return true;
        if (FUN_00b18e40(SpaceGameGet_s0107_27e0()))
            return true;
        if (FUN_00ffc0c0(GetUFOSimulator_s0107_27e0()))
            return true;

        void* avatarMgr = FUN_01021240_s0107_27e0();
        void* vec = VCallP1(avatarMgr, 0x00bba790, 0);
        uint32_t* begin = *(uint32_t**)vec;
        uint32_t* end   = *((uint32_t**)vec + 1);
        void* found = 0;
        int count = (int)(end - begin);
        if (count > 0) {
            for (int i = 0; i < count; i++) {
                void* o = (void*)begin[i];
                uint32_t s = *(uint32_t*)((uint8_t*)o + 0x28);
                if (s == 1 || s == 0)
                    continue;
                if (FUN_00b8d970(o))
                    continue;
                if (FUN_00b8dab0(o) == 5) {
                    found = o;
                    break;
                }
            }
        }
        if (!found)
            return true;

        void* game = FUN_01021240_s0107_27e0();
        uint32_t avatarId = (uint32_t)((FnObj)Vt(game)[0x00b1fdb0 / 4])(game);
        void* empire = ((cStarManagerAccess*)StarManager_s0107_27e0())->GetEmpireByID(avatarId);
        uint32_t empireId = *(uint32_t*)((uint8_t*)empire + 0x84);
        void* ctxObj = FUN_010212a0();
        uint32_t ctx = ((cCommContext*)ctxObj)->GetCommContext();

        if (id == 0x65680e8u) {
            CommAdd(empireId, ctx, 0xc8fbf7d7u, 0x934c7dd1u, 0, 0);
        } else {
            CommRemove(empireId, ctx, 0x95bbbbfcu, 0xdd33319cu);
            void* e2 = ((cStarManagerAccess*)StarManager_s0107_27e0())->GetEmpireByID(avatarId);
            uint32_t id2 = *(uint32_t*)((uint8_t*)e2 + 0x84);
            void* c2 = FUN_010212a0();
            uint32_t ctx2 = ((cCommContext*)c2)->GetCommContext();
            CommAdd(id2, ctx2, 0xc8fbf7d7u, 0xd2a61d3u, 0, 0);
        }
        return true;
    }

    if (id == 0x674c4d0u) {
        if (msg[2] == 0x287259f6u) {
            IWindow_s0107_27e0* w = mpGlobalUI->FindWindowByID(0x664c270);
            if (w)
                VCallV2(w, 0x7c, 1, 0);
        }
        return true;
    }

    if (id == 0x7bb7790u) {
        void* tm = GameTimeManager_s0107_27e0();
        if ((Lu32((uint8_t*)tm + 0x48) & 1) && !FUN_01068350()) {
            ForwardWindowMessage_7590(4, 0);
        } else {
            void* o = FUN_00b3d3f0_s0107_27e0();
            if (VCallU1(o, 0x00e18c70, 0)) {
                o = FUN_00b3d3f0_s0107_27e0();
                ((FnVU1)Vt(o)[0x00e190c0 / 4])(o, 0);
            }
        }
        if (FUN_01068350()) {
            VCallV0(mpOverlay, 0x00fe7e10);
            FUN_0106f540();
        } else {
            ((cOverlay*)mpOverlay)->Hide(1);
            ShowCreatureTooltip(0, 0);
        }
        goto shared_tail;
    }

    if (id == 0x453ef531u) {
        if (msg[2] != 0x287259f6u)
            return false;
        uint8_t b = FUN_01068140();
        RecordEvent2(0x98b8139du + (b ? 0x6c491d1au : 0), GetRecorderState());
        return true;
    }

    if (id == 0x505a4528u)
        return true;

    if (msg[2] != 0x287259f6u)
        return false;
    {
        uint32_t r = FUN_01066150(id);
        if (r == 0)
            goto shared_tail;
        FUN_0106e3e0(r);
        RecordEvent2(0xefaaa0c7u, GetRecorderState());
        return true;
    }

shared_tail:
    if (msg[2] != 0x287259f6u)
        return false;
    win = (void*)msg[0];
    if (win == 0)
        return false;
    {
        uint32_t sub = VCall0(win, 0x20);
        if (sub == 0x447b980u || sub == 0x447b981u || sub == 0x447b982u) {
            FUN_0106ea40(sub - 0x447b980u);
            return false;
        }
        if (sub == 0x447b968u || sub == 0x447b969u || sub == 0x447b96au) {
            FUN_0106e940(sub - 0x447b968u);
            return false;
        }
    }
    return false;
}
#undef FnU0
#undef FnV0
#undef FnV2
#undef FnVP2
#undef FnVU1
#undef FnRU1
#undef FnPU1
#undef FnObj
#undef FnVP2_6
#undef FnVP2_1
#undef Vt
#undef VCall0
#undef VCallU1
#undef VCallV0
#undef VCallV2
#undef VCallVP2
#undef VCallVP2_1
#undef VCallP1
#undef AudioSlot8
#undef Lu32

// @ 0x010743a0
void SP::cSPUISpace_s0107_43a0::Update(uint dt)
{
    SpaceGameGet();
    int ctx = GetUniverseContext();

    IWindow_s0107_43a0* wA = mpGlobalUI->FindWindowByID(0x61f54b8);
    IWindow_s0107_43a0* wB = mpGlobalUI->FindWindowByID(0x6b821a8);
    if (wA && wB) {
        bool show = false;
        if (CommManager()->IsActive() || GetInputMgr()->Query(0))
            show = true;
        wA->SetVisible(1, show);
        wB->SetVisible(1, show);
    }

    FUN_010678e0();
    FUN_010679f0();
    FUN_0106a970();
    UpdateGlobal();
    UpdateActiveToolCursor();
    FUN_0106cab0();

    IWindow_s0107_43a0* wC = mpGlobalUI->FindWindowByID(0xb2001000);
    if (wC) {
        bool vis = (mFlag5d3 || mFlag5d4) ? true : false;
        wC->SetVisible(1, vis);
    }

    mp61c->UpdateTimer(dt);
    FUN_01072680();
    mpAnimator->UpdateAnim();
    mp5a8->UpdateObj();

    if (GetUniverseContext() != 2) {
        Planet* planet = GetActivePlanet_s0107_43a0();
        if (planet) {
            PlanetMode* mode = planet->mpMode;
            IWindow_s0107_43a0* w = mpGlobalUI->FindWindowByID(0x3fea475);
            bool show;
            if (mode->GetKind() == 5 && !planet->IsSomething()) {
                ApplyToWindow(planet->GetHelper()->mField84, w);
                show = true;
            } else {
                show = false;
            }
            w->SetVisible(1, show);
        }
    }

    if (ctx == 0) {
        UpdateTerraformingSlots();
        UpdateTerraformingBullseye();
        FUN_01069aa0();
    } else if (ctx != 1) {
        mpGlobalUI->FindWindowByID(0x65680f8)->SetVisible(1, false);
    } else {
        FUN_01069aa0();
    }

    Star* star = 0;
    if (GetUniverseContext() == 2) {
        star = GetUFOSimulator()->GetStarRecordUnderMouse();
    } else {
        GetSimSettings()->mSlot30->Enable(1);
        GetSimSettings()->mField38 = 0;
        GetSimSettings()->mSlot34->Enable(1);
    }
    if (!star) {
        star = (Star*)GetStarSource()->GetStarRecord();
        GetSimSettings()->mSlot30->Enable(1);
        GetSimSettings()->mField38 = 0;
    }

    // Copy the toggle buttons' bit 1 into the four UFO flag bytes, then OR in the second set.
    CopyToggle(mpGlobalUI, 0x4cab570, 0);
    CopyToggle(mpGlobalUI, 0x4cab571, 1);
    CopyToggle(mpGlobalUI, 0x4cab56e, 2);
    CopyToggle(mpGlobalUI, 0x4cab56f, 3);
    OrToggle(mpGlobalUI, 0x5cab570, 0);
    OrToggle(mpGlobalUI, 0x5cab571, 1);
    OrToggle(mpGlobalUI, 0x5cab56e, 2);
    OrToggle(mpGlobalUI, 0x5cab56f, 3);

    switch (GetUniverseContext()) {
    case 0: {
        FUN_010691e0();
        IWindow_s0107_43a0* w = mpGlobalUI->FindWindowByID(0x2c38ab9);
        if (w)
            w->SetVisible(1, GetUISoundHelper()->GetFlag());
        break;
    }
    case 1:
        GetUIObj1046()->Run();
        UpdateTravelLine(star);
        if (star)
            UpdatePlanetRollover(star->QueryInterface(0x3275872));
        else
            UpdatePlanetRollover(0);
        break;
    case 2:
        UpdateTravelLine(star);
        GetUIObj1046()->Run();
        break;
    }

    GetMissionManager()->DebugDraw();

    if (gAudioDebugA || gAudioDebugB)
        AudioGuiUpdate();

    if (gNextSoundTime < GetElapsedSeconds())
        gNextSoundTime = GetElapsedSeconds() + kSoundPeriod;

    bool playedSpecial;
    if (CommManager()->IsActive() || GetInputMgr()->Query(0) || WindowManager()->GetCapture() != 0
        || ModeIs12(GetModeInfo()))
        playedSpecial = true;
    else
        playedSpecial = false;

    FUN_0106b630();

    if (mStartCur != mFinishCur /* queue not empty */ && !playedSpecial) {
        GameTimeManager()->IncPauseGate(0x4bf38a7);
        int n = ((mFinishNode - mStartNode) << 6) + (int)(mFinishCur - mFinishFirst) + (int)(mStartLast - mStartCur) - 0x41;
        for (; n > 0; --n) {
            uint id = PopSound();
            if (id == 0x3826c46f || id == 0xa9c3987b)
                playedSpecial = true;
            Key3 k = { id, 0xb1b104, 0x3629f036 };
            GetSoundMgr()->Play(k, 0, 0, kNegOne, kNegOne, 0.0f, (void*)SoundCb, 0);
        }
        uint id = PopSound();
        const void* p = (id == 0x3826c46f || id == 0xa9c3987b || playedSpecial) ? gSoundPtrB : gSoundPtrA;
        Key3 k = { id, 0xb1b104, 0x3629f036 };
        GetSoundMgr()->Play(k, p, 0, kNegOne, kNegOne, 0.0f, (void*)SoundCb, 0);
    }

    if (mMode618 == 4) {
        if (GetInputMgr()->Query(0)) {
            TerrainSphere* t = ((TerrainEditor*)NounManager())->GetCurrentTerrainSphere();
            if (t && !t->Check(0x65e5039)) {
                GetInputMgr()->Set(-0xc, 0);
                return;
            }
        } else {
            TerrainSphere* t = ((TerrainEditor*)NounManager())->GetCurrentTerrainSphere();
            if (!t || t->Check(0x65e5039))
                FUN_01065d20();
            else
                GetInputMgr()->Set(-0xc, 0);
        }
    }
}

// @ 0x01074bb0
bool UIHandler::HandleMessage(uint msgID, void* msg)
{
    char* m = (char*)msg;
    switch (msgID) {
    case 0x38cf2fc:
        Outer()->F106b220(*(uint*)(m + 8));
        return true;
    case 0xf62def:
        if (*(uint*)(m + 0x18) == 0xddb63e53) {
            Outer()->F1068f70();
            return false;
        }
        break;
    case 0x3ac86ad:
        Outer()->F1067f60(1);
        if (world(2)) {
            IWindow_s0107_4bb0* w = mGlobalUI->FindWindowByID(0x7ce6631);
            if (w) w->SetVisible(1, 0);
        }
        return false;
    case 0x44f1189: {
        uint id = *(uint*)(m + 8);
        if (id == GetNameTable()->Lookup("SPG_MasterBadge")) {
            if (mEffect.p && mEffect.p->IsPlaying())
                mEffect.p->Stop(1);
        }
        return false;
    }
    case 0x3ac86b5:
        Outer()->F1067f60(0);
        if (world(2)) {
            IWindow_s0107_4bb0* w = mGlobalUI->FindWindowByID(0x7ce6631);
            if (w) w->SetVisible(1, 1);
        }
        return false;
    case 0x490d429:
        Outer()->UpdateActivePlanetInfo();
        return true;
    case 0x5da932e:
        SetUFOImage(GetPlayerEmpire()->GetUFOKey());
        return false;
    case 0x534052c: {
        if (GetUniverseContext() != 0) return false;
        if (GetGate()->Check()) return false;
        void* o = ((MsgSub*)msg)->GetObj();
        void* sel = ((Sel*)o)->GetSelection(0);
        Creature* c = CreatureFromObject(ObjectFromKey(((Sel2*)sel)->Resolve()));
        if (c) {
            void* owned = IsCreatureOwned(c);
            Species* sp = c->GetSpeciesProfile();
            Key3 key;
            WString name;
            name.mpBegin = gEmptyStr; name.mpEnd = gEmptyStr; name.mpCapacity = gEmptyStr + 1;
            sp->GetUiName(&name);
            UIGlobals* g = g16e0d08;
            g->f14 = 0;
            g->f24 = sp;
            {
                Key3* k = c->GetKey();
                key.a = k->a; key.b = k->b; key.c = k->c;
            }
            key.b = 0x2f7d0004;
            if (key.a != mLastKey) {
                mLastKey = key.a;
                void* planet = GetActivePlanet_s0107_4bb0();
                char* target;
                if (owned) {
                    target = mOwner ? mOwner + 4 : 0;
                    const wchar_t* title = name.mpBegin;
                    Outer()->SetToolTip(target, title, mText458.GetText(0), &key);
                } else {
                    if (planet && !((Planet_s0107_4bb0*)planet)->SetSpeciesAsScanned(c->GetKey())) {
                        target = mOwner ? mOwner + 4 : 0;
                        Outer()->SetToolTip(target, mText494.GetText(0), 0, 0);
                    } else {
                        target = mOwner ? mOwner + 4 : 0;
                        const wchar_t* title = name.mpBegin;
                        Outer()->SetToolTip(target, title, mText46c.GetText(0), &key);
                    }
                }
            }
            name.DeallocateSelf();
            return false;
        }
        if (m59c) m59c->Refresh();
        return false;
    }
    case 0x5e793a6:
        Outer()->F106f120(msg);
        if (*(int*)(m + 0x14) == 2) {
            uint* r = ((MsgSub*)msg)->GetValuePtr();
            GetNotifier()->Notify(-0xb, *r);
        }
        return false;
    case 0x6174b67:
        Outer()->F106a280();
        return true;
    case 0x5e793b4:
        if (m288) m288->On(*(uint*)m);
        return false;
    case 0x61dae5c:
        if (msg == m22c->GetField()) {
            bool b = ((DispStrat*)msg)->GetDisplayStrategy() == 0xe7c9ede0;
            Outer()->F106aab0(b);
        }
        return false;
    case 0x62b45bb:
        KillSetiEffects(0xefaaa0c7, GetRecorderState());
        Outer()->F106e5e0();
    retTrue:
        return true;
    case 0x61dae65:
        if (msg == m22c->GetField())
            Outer()->F106aab0(false);
        return false;
    case 0x62b45c3:
        KillSetiEffects(0xefaaa0c7, GetRecorderState());
        Outer()->F106e630();
        return true;
    case 0x64e43b9:
        if (*(uint*)(m + 8) == 0x4dc4aacb)
            mBadgeState = 3;
        return false;
    case 0x635ae73:
        Outer()->F106f160(msg);
        return false;
    case 0x65ff54a:
        if (*(uint*)(m + 0x10) == g15b929c && *(uint*)(m + 0x18) == g15b9294) {
            UISpace_s0107_4bb0* o = Outer();
            o->F1071570();
            o->Init();
        }
        return false;
    case 0x665e639: {
        EffectRef ref;
        ref.p = 0;
        EffectsManager()->CreateEffect(0x31a596d6, 0, ref.AsPPTypeParam());
        if (ref.p) {
            PlayerInv* inv = GetUFOSimulator_s0107_4bb0()->GetPlayerInventory();
            XformMsg_s0107_4bb0 xf;
            xf.SetPosition(inv->sub.GetPosition());
            Matrix3_s0107_4bb0 tmp;
            Matrix3_s0107_4bb0* mat = Matrix3FromQuaternion(&tmp, inv->sub.GetOrientationQ());
            *(Matrix3_s0107_4bb0*)xf.mat = *mat;
            xf.flags |= 2;
            xf.count += 1;
            ref.p->SetTransform(&xf);
            ref.p->Start(0);
        }
        return false;
    }
    case 0x665e1ab: {
        uint id;
        switch (SpaceGameGet_s0107_4bb0()->GetOwner2()->GetMode()) {
        case 0: id = 0xe14ab551; break;
        case 1: id = 0xe14ab550; break;
        case 2: id = 0xe14ab553; break;
        case 3: id = 0xe14ab552; break;
        case 4: id = 0xe14ab555; break;
        case 5: id = 0xe14ab554; break;
        case 6: id = 0xe14ab557; break;
        case 7: id = 0xe14ab556; break;
        case 8: id = 0xe14ab559; break;
        case 9: id = 0xe14ab558; break;
        case 10: id = 0xf89b6cc0; break;
        default:
            goto retTrue;
        }
        EffectRef& r = mEffect;
        if (r.p && r.p->IsPlaying())
            r.p->Stop(1);
        EffectsManager()->CreateEffect(id, 0, r.AsPPTypeParam());
        if (r.p)
            r.p->Start(0);
        return true;
    }
    case 0x670eccd:
        if (ConfigManager_s0107_4bb0()->Query(0x4ea96cb) == 0) {
            if (Outer()->F1065e20()) {
                Outer()->F1065e40();
                return false;
            }
        }
        return false;
    case 0x68996fb: {
        uint planet = *(uint*)(m + 8);
        if (planet) {
            void* star = StarManager()->Lookup((void*)planet);
            if (star) {
                GetStarMap()->RemoveVisualGroup(0x626fd8e, 1);
                if (*(int*)(m + 0x10) == 1)
                    GetStarMap()->CreatePlanetRecordVisual(star, 0x626fd8e, 0x587f7ac7, 1, 1);
            }
        }
        return true;
    }
    case 0x6779f04: {
        uint v = *(uint*)m;
        GetNotifier()->Notify(-0xd, v);
        return false;
    }
    }
    return false;
}

// same-TU callee of the 0x01074bb0 handler (lets cl keep ECX across the call); the retail function is
// 0x01065e20, whose own row is above, so this copy carries no marker
__declspec(noinline) bool UISpace_s0107_4bb0::F1065e20()
{
    int s = mState618;
    if (s == 1 || s == 2 || s == 5 || s == 7) return true;
    return false;
}

// @ 0x01077830
bool SP::cSPUISpaceTrading::FUN_01077830(void* p)
{
    int local[3];
    Obj* r = ((Fn_p_pp)VTSLOT(p, 0x38))(p, local);
    return *(void**)r == mpField10;
}

// @ 0x01077860
int SP::cSPUISpaceTrading::FUN_01077860(float a, float b)
{
    int xi = (int)(__int64)(a / (mFieldB4 + mField94));
    int yi = (int)(__int64)(b / (mFieldB8 + mField98));
    if (mField80 == 0x120ad1fb)
        return mField88 * yi + xi;
    return mField8C * xi + yi;
}

// @ 0x01077900
u8 SP::cSPUISpaceTrading::FUN_01077900(void* p)
{
    cPlayerInventory_s0107_7470* inv =
        ((cSPSimulatorSpaceGame_s0107_7470*)SP_SpaceGameGet())->GetPlayerInventory();
    if (inv != 0) {
        if (((Fn_b_p)VTSLOT(p, 0x40))(p)) {
            if (*(u8*)((char*)p + 0x28) != 0)
                inv->FUN_00ff4540(p);
            else
                inv->FUN_00ff4470(p);
        }
    }
    return *(u8*)((char*)p + 0x28);
}

// @ 0x01077960
u32 SP::cSPUISpaceTrading::FUN_01077960(void* p)
{
    cPlayerInventory_s0107_7470* inv =
        ((cSPSimulatorSpaceGame_s0107_7470*)SP_SpaceGameGet())->GetPlayerInventory();
    if (inv != 0) {
        if (inv->FUN_00ff3f00() == p)
            return 1;
    }
    return 0;
}

// @ 0x01077990
void SP::cSPUISpaceTrading::FUN_01077990(void* p)
{
    ((Fn_v_p)VTSLOT(p, 0x48))(p);
}

// @ 0x010779e0
void SP::cSPUISpaceTrading::FUN_010779e0()
{
    ((Fn_v_p)VTSLOT(this, 0x28))(this);

    void* h = mpHandlerEC;
    if (h != 0) {
        mpHandlerEC = 0;
        EA_Messaging_RemoveHandler(h, mArgsF0[0], mArgsF0[1], mArgsF0[2], mArgsF0[3]);
    }
    void* h2 = mBlk100.h;
    if (h2 != 0) {
        mBlk100.h = 0;
        EA_Messaging_RemoveHandler(h2, mBlk100.a1, mBlk100.a2, mBlk100.a3, mBlk100.a4);
    }
    if (mpField1C != 0) {
        Obj* x = (Obj*)mpField1C;
        mpField1C = 0;
        ((Fn_v_p)VTSLOT(x, 8))(x);
    }
    if (mpField20 != 0) {
        Obj* x = (Obj*)mpField20;
        mpField20 = 0;
        ((Fn_v_p)VTSLOT(x, 4))(x);
    }
    if (mpField24 != 0)
        ((Fn_v_pp)VTSLOT(mpField24, 0x108))(mpField24, this);
    if (mpField28 != 0 && mpField2C != 0)
        ((Fn_v_pp)VTSLOT(mpField28, 0xe0))(mpField28, mpField2C);
    if (mpField24 != 0) {
        Obj* x = (Obj*)mpField24;
        mpField24 = 0;
        ((Fn_v_p)VTSLOT(x, 4))(x);
    }
    if (mpField28 != 0) {
        Obj* x = (Obj*)mpField28;
        mpField28 = 0;
        ((Fn_v_p)VTSLOT(x, 4))(x);
    }
    if (mpField2C != 0) {
        Obj* x = (Obj*)mpField2C;
        mpField2C = 0;
        ((Fn_v_p)VTSLOT(x, 4))(x);
    }
}

// @ 0x01077ae0
u32 __stdcall FUN_01077ae0(cSPUILayout_s0107_7470* layout)
{
    u32 ret = 0;
    if (layout == 0)
        return ret;
    cObjVec* vec = layout->GetObjects();
    Obj** cur = vec->begin;
    Obj** end = vec->end;
    while (cur != end) {
        u32 v = 0;
        if (*cur != 0)
            v = (u32)((Fn_p_pi)VTSLOT(*cur, 0xc))(*cur, 0xeeee8218);
        if (v != 0) {
            ret = v;
            break;
        }
        ++cur;
    }
    return ret;
}

// @ 0x01077b40
u32 __cdecl FUN_01077b40(void* p)
{
    Obj* a = ((Fn_p_pi)VTSLOT(p, 0xb4))(p, 0x600db9c);
    if (a != 0)
        return (u32)((Fn_p_pi)VTSLOT(a, 0xc))(a, 0x707459dd);
    return 0;
}

// @ 0x01077b70
bool SP::cSPUISpaceTrading::FUN_01077b70(void* a1, u32* pOut)
{
    bool bRet = false;
    if (mByte9C != 0) {
        *pOut = *(u32*)((char*)a1 + 0x24);
        bRet = true;
    } else {
        void* item = ((cSporeItem*)FUN_010666a0(a1))->FUN_0106edc0();
        Obj* r = ((Fn_p_ppp)VTSLOT(mpField2C, 0xf0))(mpField2C, item, 0);
        if (r != 0) {
            float* v = (float*)((Fn_p_p)VTSLOT(r, 0x38))(r);
            float f[2];
            f[0] = v[0];
            f[1] = v[1];
            *pOut = (u32)FUN_01077860(f[0], f[1]);
            bRet = true;
        }
    }
    return bRet;
}

// @ 0x01077bf0
void SP::cSPUISpaceTrading::FUN_01077bf0(void* a1)
{
    int local;
    void* item = ((cSporeItem*)FUN_010666a0(a1))->FUN_0106edc0();
    Obj* a = ((Fn_p_ppp)VTSLOT(mpField2C, 0xf0))(mpField2C, item, 0);
    if (a == 0)
        return;
    Obj* b = ((Fn_p_ppp)VTSLOT(a, 0xf0))(a, (void*)0x5f72e19, 0);
    if (b == 0)
        return;
    if (((Fn_b_pp)VTSLOT((void*)a1, 0x3c))((void*)a1, &local) == false) {
        ((Fn_v_pii)VTSLOT(b, 0x7c))(b, 1, 0);
        return;
    }
    char buf[0x20];
    EA_Locale_SetNumberString(local, 0, buf, 0x20);
    ((Fn_v_pp)VTSLOT(b, 0x80))(b, buf);
    if (local == 0)
        ((Fn_v_pf)VTSLOT(b, 0x5c))(b, mFieldB0);
    else
        ((Fn_v_pf)VTSLOT(b, 0x5c))(b, mFieldAC);
    ((Fn_v_pii)VTSLOT(b, 0x7c))(b, 1, 1);
}

// @ 0x01077ce0
void SP::cSPUISpaceTrading::FUN_01077ce0(void* a1)
{
    if (FUN_01077b70(a1, (u32*)&a1)) {
        cScrollElem* e = mpVec30 + (u32)a1;
        if (e->mByte8 == 0) {
            void* p = e->mpObj;
            e->mByte8 = 1;
            if (p != 0) {
                e->mpObj = 0;
                ((Fn_v_p)VTSLOT(p, 8))(p);
            }
            e->mField4 = 0.0f;
        }
    }
}

// @ 0x01077d30
void SP::cSPUISpaceTrading::FUN_01077d30()
{
    cScrollElem* cur = mpVec30;
    cScrollElem* end = mpVecEnd34;
    while (cur != end) {
        if (cur->mpObj != 0) {
            Obj* w = ((cSPUILayout_s0107_7470*)cur->mpObj)->FindWindowByID(0x62840d8, 1);
            if (w != 0)
                ((Fn_v_pii)VTSLOT(w, 0x7c))(w, 1, mByteE9);
        }
        ++cur;
    }
    if (mByteE8 != 0 && mByteE9 != 0) {
        void* target = &mpField0C;
        Obj* ms = SP_MessageServer();
        mpHandler128 = ms;
        mArgs12C[0] = target;
        mArgs12C[1] = (void*)DAT_0149c608;
        mArgs12C[2] = (void*)3;
        mArgs12C[3] = 0;
        if (ms != 0 && target != 0) {
            u8* ids = (u8*)DAT_0149c608;
            for (u32 o = 0; o < 0xc; o += 4)
                ((Fn_v_ppi)VTSLOT(ms, 0x24))(ms, target, *(int*)(ids + o));
        }
    } else {
        void* h = mpHandler128;
        if (h != 0) {
            mpHandler128 = 0;
            EA_Messaging_RemoveHandler(h, mArgs12C[0], mArgs12C[1], mArgs12C[2], mArgs12C[3]);
        }
    }
}

// @ 0x01077e20
void SP::cSPUISpaceTrading::FUN_01077e20()
{
    float* v = (float*)((Fn_p_p)VTSLOT(mpField2C, 0x38))(mpField2C);
    float a = v[0];
    float b = v[1];
    float c = v[2];
    float d = v[3];
    bool flag1 = true;
    bool flag2 = true;
    if (mField80 == 0x120ad1fb) {
        if (!(mFieldE4 > (mFieldC0 - (d - b))))
            flag1 = false;
        if (!(0.0f > mFieldE4))
            flag2 = false;
    } else {
        if (!(mFieldE0 > (mFieldBC - (c - a))))
            flag1 = false;
        if (!(0.0f > mFieldE0))
            flag2 = false;
    }
    Obj* w1 = ((Fn_p_ppp)VTSLOT(mpField24, 0xf0))(mpField24, (void*)0x5f72d7c, (void*)1);
    if (w1 != 0)
        ((Fn_v_pii)VTSLOT(w1, 0x7c))(w1, 1, flag1);
    Obj* w2 = ((Fn_p_ppp)VTSLOT(mpField24, 0xf0))(mpField24, (void*)0x5f72d8a, (void*)1);
    if (w2 != 0)
        ((Fn_v_pii)VTSLOT(w2, 0x7c))(w2, 1, flag2);
}

// @ 0x01077f10
cScrollElem** __cdecl FUN_01077f10(cScrollElem** pOut, cScrollElem* first, cScrollElem* last, cScrollElem* value)
{
    *pOut = value;
    while (first != last) {
        cScrollElem* d = *pOut;
        if (d != 0) {
            void* p = first->mpObj;
            d->mpObj = p;
            if (p != 0)
                ((Fn_v_p)VTSLOT(p, 4))(p);
            d->mField4 = first->mField4;
            d->mByte8 = first->mByte8;
        }
        ++(*pOut);
        ++first;
    }
    return pOut;
}

// @ 0x01077f70
void __cdecl FUN_01077f70(cScrollElem* dst, u32 count, cScrollElem* src)
{
    cScrollElem* p = dst;
    for (; 0 < count; --count, ++p) {
        if (p != 0) {
            void* q = src->mpObj;
            p->mpObj = q;
            if (q != 0)
                ((Fn_v_p)VTSLOT(q, 4))(q);
            p->mField4 = src->mField4;
            p->mByte8 = src->mByte8;
        }
    }
}

// @ 0x01077fb0
cScrollElem* __cdecl FUN_01077fb0(cScrollElem* first, cScrollElem* last, cScrollElem* dst)
{
    if (first != last) {
        do {
            if (dst != 0) {
                void* p = first->mpObj;
                dst->mpObj = p;
                if (p != 0)
                    ((Fn_v_p)VTSLOT(p, 4))(p);
                dst->mField4 = first->mField4;
                dst->mByte8 = first->mByte8;
            }
            ++first;
            ++dst;
        } while (first != last);
    }
    return dst;
}

// @ 0x01078000
cScrollElem* __cdecl FUN_01078000(cScrollElem* first, cScrollElem* last, cScrollElem* dst)
{
    if (first != last) {
        do {
            void* p = first->mpObj;
            void* q = dst->mpObj;
            if (p != q) {
                if (p != 0)
                    ((Fn_v_p)VTSLOT(p, 4))(p);
                dst->mpObj = p;
                if (q != 0)
                    ((Fn_v_p)VTSLOT(q, 8))(q);
            }
            dst->mField4 = first->mField4;
            dst->mByte8 = first->mByte8;
            ++first;
            ++dst;
        } while (first != last);
    }
    return dst;
}

// @ 0x01078060
cScrollElem* __cdecl FUN_01078060(cScrollElem* first, cScrollElem* last, cScrollElem* dst)
{
    if (last != first) {
        do {
            --last;
            --dst;
            void* p = last->mpObj;
            void* q = dst->mpObj;
            if (p != q) {
                if (p != 0)
                    ((Fn_v_p)VTSLOT(p, 4))(p);
                dst->mpObj = p;
                if (q != 0)
                    ((Fn_v_p)VTSLOT(q, 8))(q);
            }
            dst->mField4 = last->mField4;
            dst->mByte8 = last->mByte8;
        } while (last != first);
    }
    return dst;
}

// @ 0x01078120
bool cSPPropLayoutPanel::Init()
{
    void* server = mConnector.mpServer;
    if (server) {
        mConnector.mpServer = 0;
        RemoveHandler(server, mConnector.a, mConnector.b, mConnector.c, mConnector.d);
    }
    bool ok = false;
    if (mWindow.mpObject)
        mWindow.mpObject->RemoveWinProc(this);
    if (mText.mpObject && mTextClone.mpObject)
        mText.mpObject->RemoveWindow(mTextClone.mpObject);
    mWindow = 0;
    mText.Clear();
    mTextClone.Clear();
    mStopwatch.Reset(5);

    PropertyManager* pm = PropertyManager_Get();
    uint32_t windowID;
    if (pm->GetPropertyList(mLayoutKey.instanceID, mLayoutKey.groupID, mPropList.AsOutParam())
        && GetUIntProp(mPropList.get(), 0x1a561f11, windowID)) {
        m80 = 0x41478d35;
        GetUIntProp(mPropList.get(), 0x6498e0ef, m80);
        m84 = 0.0f;
        GetFloatProp(mPropList.get(), 0x7ae5959, m84);
        mCols = 1;
        GetUIntProp(mPropList.get(), 0x44833f26, mCols);
        mRows = 1;
        GetUIntProp(mPropList.get(), 0x44ae2034, mRows);
        m90 = (uint32_t)-1;
        GetUIntProp(mPropList.get(), 0x86eec9cd, m90);
        mPadX = 0.0f;
        GetFloatProp(mPropList.get(), 0xe603d9c3, mPadX);
        mPadY = 0.0f;
        GetFloatProp(mPropList.get(), 0xdfef8f2d, mPadY);
        mFlag9c = true;
        GetBoolProp(mPropList.get(), 0x2ba82aec, mFlag9c);
        mMode = (uint32_t)-1;
        GetUIntProp(mPropList.get(), 0xd2df8e4d, mMode);
        ma4 = (uint32_t)-1;
        GetUIntProp(mPropList.get(), 0x930166a3, ma4);
        ma8 = 0xfff0f0f0;
        GetUIntProp(mPropList.get(), 0xa798fc58, ma8);
        mac = (uint32_t)-1;
        GetUIntProp(mPropList.get(), 0xfcfe75a2, mac);
        mb0 = 0xff555555;
        GetUIntProp(mPropList.get(), 0xbef43c38, mb0);

        bool loaded = false;
        for (int k = 0; k < 5; ++k) {
            ResourceKey* key = &mLayoutKeys[k];
            *key = ResourceKey(0, 0x510a95b, 0x40464100);
            if (GetPropertyAsKeyInstance(mPropList.get(), g_LayoutPropIDs[k], &key->instanceID) && !loaded) {
                cSPUILayout_s0107_8120 layout;
                if (!layout.Init(key, 0, 0x5b598fa)) {
                    key->instanceID = 0;
                } else {
                    IWindow_s0107_8120* win = FUN_01077ae0(&layout);
                    if (win) {
                        Math::Rectangle_s0107_8120 r = win->GetRealArea();
                        mLayoutW = r.x2 - r.x1;
                        mLayoutH = r.y2 - r.y1;
                        loaded = true;
                    }
                }
            }
        }

        if (loaded) {
            mScaledW = (mLayoutW + mPadX) * (float)mCols;
            mScaledH = (mLayoutH + mPadY) * (float)mRows;
            if (mpLayout) {
                mWindow = mpLayout->FindWindowByID(windowID, 1);
                if (mWindow.get()) {
                    mText = mWindow.get()->FindWindowByID(0x5f7c9b3, false);
                    if (mText.mpObject) {
                        mWindow.get()->AddWinProc(this);
                        Math::Rectangle_s0107_8120 r = mText.mpObject->GetRealArea();
                        mText.mpObject->SetPosition(((r.x2 - r.x1) - mScaledW) * 0.5f + r.x1,
                                                    ((r.y2 - r.y1) - mScaledH) * 0.5f + r.y1);
                        mText.mpObject->SetSize(mScaledW, mScaledH);
                        mText.mpObject->SetFlag(0x400, true);
                        mTextClone = CreateTextWindow(mText.mpObject);
                        mE0 = 0.0f;
                        mE4 = 0.0f;
                        if (mMode != (uint32_t)-1) {
                            mFlagE9 = (mMode == 1);
                            mConnector.Init((IMessageServer*)MessageServer(), &mHandler, g_MessageIDs, 1);
                        }
                        if (mFlagE8) {
                            OnShow28();
                            OnShow24();
                        }
                        ok = true;
                    }
                }
            }
        }
    }
    return ok;
}

// @ 0x01079260
bool UISpace::HandleMessage(IWin* win, Msg* msg)
{
    bool result = false;
    if (msg->type == 0xd) {
        if (mpCurrent != win) {
            IObj_s0107_9260* a = win ? win->Query(0x8ed27e7a) : 0;
            IObj_s0107_9260* o2 = win->QueryB4(0x600db9c);
            IObj_s0107_9260* b = o2 ? o2->Query(0x707459dd) : 0;
            Inventory* inv = SpaceGameGet_s0107_9260()->GetPlayerInventory();
            if (a && inv && b) {
                float f = inv->F00ff3fb0(b)->F1050a60() * 0.95f + 0.05f;
                uint8_t flag = (uint8_t)(a->GetFlags() >> 2);
                flag &= 1;
                RenderContext* ctx = msg->ctx;
                Painter* p = F0059ed00(win->GetA8());
                const float* r = win->GetRect();
                float rect[4];
                rect[0] = 0.0f; rect[1] = 0.0f;
                rect[2] = r[2] - r[0]; rect[3] = r[3] - r[1];
                uint v30 = win->Get30();
                DrawParams dp;
                dp.a = 1; dp.b = 0; dp.c = win->GetA4(); dp.d = v30;
                p->Prepare(ctx, rect, &dp);
                float u0, u1;
                if (flag) {
                    u0 = 1.5707964f;
                    u1 = 1.5707964f - g_UIGlowScale * f;
                } else {
                    u1 = 1.5707964f - g_UIGlowScale;
                    u0 = 1.5707964f - g_UIGlowScale * f;
                }
                float hw = (rect[2] - rect[0]) * 0.5f;
                float hh = (rect[3] - rect[1]) * 0.5f;
                ImageSource* is = &p->src;
                Image* img = is->GetImage(4);
                if (img) {
                    float w = (float)img->width;
                    float h = (float)img->height;
                    float t0[2], t1[2];
                    float* q0 = p->A830c90(t0, 4);
                    float x0 = q0[0], y0 = q0[1];
                    float* q1 = p->A830cc0(t1, 4);
                    float x1 = q1[0], y1 = q1[1];
                    uint c = p->A830c80(4);
                    uint tok = ctx->Begin2D(0);
                    F00805bb0(tok, x1 + hw, y1 + hh, x0 * w, y0 * h, c, c, u1, u0, img, 0.05f);
                    ctx->End2D();
                }
                img = p->A830cf0(0);
                if (img) {
                    float w = (float)img->width;
                    float h = (float)img->height;
                    float t0[2], t1[2];
                    float* q0 = p->A830d30(t0, 4);
                    float x0 = q0[0], y0 = q0[1];
                    float* q1 = p->A830d60(t1, 4);
                    float x1 = q1[0], y1 = q1[1];
                    uint c = p->A830d10(4);
                    uint tok = ctx->Begin2D(0);
                    F00805bb0(tok, x1 + hw, y1 + hh, x0 * w, y0 * h, c, c, u1, u0, img, 0.05f);
                    ctx->End2D();
                }
                result = true;
            }
        }
    } else if (msg->type == 0x287259f6) {
        uint id = msg->src->GetFlags();
        switch (id) {
        case 0x5f72d7c:
            F1078ec0();
            KillSetiEffects(0xa25c8861, GetRecorderState_s0107_9260());
            return true;
        case 0x5f72d8a: {
            F1078fa0();
            IObj_s0107_9260* at = GetSystemAT_s0107_9260();
            KillSetiEffects(0xa25c8861, at ? at->GetFlags() : 0);
            return true;
        }
        case 0x34ef68d:
        case 0x70648eae: {
            IObj_s0107_9260* o = F01077b40(msg->src);
            bool ok = F1077900(o);
            IObj_s0107_9260* at = GetSystemAT_s0107_9260();
            uint v = at ? at->GetFlags() : 0;
            KillSetiEffects(ok ? 0xa9c4342u : 0x42f52773u, v);
            result = true;
            if (ok && o && o->CheckFlag() && !CommManager_s0107_9260()->F0ae9390()) {
                Inventory* inv = SpaceGameGet_s0107_9260()->GetPlayerInventory();
                if (inv) {
                    Item* it = inv->F00ff3fb0(o);
                    if (it && !it->F104feb0()) {
                        TSphere* ts = NounManager_s0107_9260()->GetCurrentTerrainSphere();
                        if (ts && !ts->F00c772c0(0x65fef10)) {
                            ts->F00c77bf0(0x65fef10);
                            F010666a0()->F106dcd0(0x34235299);
                        }
                        if (it->F0ce6920() > 0.0f && ts && !ts->F00c772c0(0x6788f1c)) {
                            ts->F00c77bf0(0x6788f1c);
                            F010666a0()->F106dcd0(0xb396e5bb);
                        }
                    }
                }
            }
            return result;
        }
        default:
            if (id - 0x5f72da0u <= 9u) {
                F1079040(id - 0x5f72da0u);
                KillSetiEffects(0xa25c8861, GetRecorderState_s0107_9260());
                return true;
            }
            return false;
        }
    }
    return result;
}

// @ 0x01079890
void UISpace::F1079890(uint index)
{
    if (F1077b70(index, &index))
        F1079040(index / (uint)(mRows8c * mCols88));
}

// @ 0x01079a60
void CellVec::F1079a60(UICell* pos, uint n, const UICell* val)
{
    if (n <= (uint)(cap - end))
    {
        if (n > 0)
        {
            UICell tmp;
            tmp.mNode = val->mNode;
            if (tmp.mNode != 0)
                ((IRefObj_s0107_9260*)tmp.mNode)->v01();
            tmp.mFlag = val->mFlag;
            tmp.mPos  = val->mPos;
            UICell* oldend = end;
            uint avail = (uint)(end - pos);
            if (n < avail)
            {
                UICell* moveto = oldend - n;
                FUN_01077f10((int)&val, (int)moveto, (int)oldend, (int)oldend, (int)pos);
                end = end + n;
                FUN_01078060((int)pos, (int)moveto, (int)oldend);
                FUN_01078d30((int)pos, (int)(pos + n), (int)&tmp);
            }
            else
            {
                FUN_01077f70((int)oldend, n - avail, (int)&tmp, (int)pos);
                end = end + (n - avail);
                FUN_01077f10((int)&pos, (int)pos, (int)oldend, (int)end, (int)pos);
                end = end + avail;
                FUN_01078d30((int)pos, (int)oldend, (int)&tmp);
            }
            if (tmp.mNode != 0)
                ((IRefObj_s0107_9260*)tmp.mNode)->v02();
        }
    }
    else
    {
        int size = (int)(end - begin);
        uint newcap = (uint)(size * 2);
        if (size == 0)
            newcap = 1;
        uint room = n + (uint)size;
        if (room < newcap)
            room = newcap;
        UICell* buf = 0;
        if (room != 0)
            buf = (UICell*)operator_new_eastl(room * 0xc, g_str_Simulator, 0, 0,
                                              (const char*)g_alloc_13ebb38, 0xd1);
        UICell* endpos = pos;
        UICell* oldbegin = begin;
        UICell* p = (UICell*)FUN_01077fb0((int)oldbegin, (int)pos, (int)buf);
        FUN_010779a0((int)oldbegin, (int)endpos, (int)buf);
        FUN_01077f70((int)p, n, (int)val, (int)p);
        UICell* mid = p + n;
        UICell* oldend = end;
        UICell* r = (UICell*)FUN_01077fb0((int)endpos, (int)oldend, (int)mid);
        FUN_010779a0((int)endpos, (int)oldend, (int)mid);
        if (begin != 0 && ((AllocHeader*)begin)[-1].mCookie != 0)
            operator_delete_eastl((int)begin);
        begin = buf;
        end   = r;
        cap   = buf + room;
    }
}

// @ 0x01079d10
INode* UISpace::F1079d10(cSPUILayout_s0107_9260* parent, uint index)
{
    INode* node = (INode*)FUN_01077ae0((IWin*)parent);
    if (node != 0)
    {
        parent->SetParentWin((IWin*)mp2c, 0, 0x5b598fa);

        uint a, b;
        if (mFlags80 == 0x120ad1fb)
        {
            b = index / (uint)mCols88;
            a = index % (uint)mCols88;
        }
        else
        {
            a = index / (uint)mRows8c;
            b = index % (uint)mRows8c;
        }
        node->v070((float)a * (mSpacingB4 + mX94), (float)b * (mSpacingB8 + mY98));

        INode* child = (INode*)node->v0f0(0x62840d8, 0);
        if (child != 0)
        {
            WStr buf;
            uint rem = index % (uint)(mRows8c * mCols88);
            if (rem < 10)
                FUN_010799d0(&buf, g_fmt_013f01bc, (uint)((rem + 1) % 10));
            child->v080(buf.mpBegin);
            child->v05c(mKeyA8);
            child->v07c(1, mFlagE9);
            if ((int)(((int)buf.mpCap - (int)buf.mpBegin) & 0xfffffffe) > 2 &&
                buf.mpBegin != 0 && buf.mpBegin != buf.mpInline)
                operator_delete_eastl((int)buf.mpBegin);
        }
    }
    return node;
}

// @ 0x01079f90
void UISpace::F1079f90()
{
    mCells.F10799f0(mCells.begin, mCells.end);
    if (mpHandler114)
    {
        void* h = mpHandler114;
        mpHandler114 = 0;
        EA_Messaging_RemoveHandler(h, mHandler118, mHandler11c, mHandler120, mHandler124);
    }
    mTeardownE8 = 0;
    return F1077d30();
}

// @ 0x01079ff0
void CellVec::F1079ff0(uint n)
{
    UICell* first = begin;
    UICell* last  = end;
    if ((uint)((last - first) / 0xc) < n)
    {
        UICell val;
        val.mNode = 0;
        val.mPos  = 0.0f;
        val.mFlag = 1;
        F1079a60(last, n - (uint)((last - first) / 0xc), &val);
    }
    else
    {
        F10799f0(first + n, last);
    }
}

// @ 0x0107a070
void UISpace::F107a070(ISpaceWin* win)
{
    uint sel;
    if (mFlag9c == 0 || (sel = (uint)win->mSel24) == 0xffffffffu)
    {
        sel = 0;
        UICell* c = mCells.begin;
        UICell* e = mCells.end;
        while (c != e && c->mFlag == 0)
        {
            c += 1;
            ++sel;
        }
    }

    if (sel >= (uint)(mCells.end - mCells.begin))
        mCells.F1079ff0(sel + 1);

    UICell* cell = mCells.begin + sel;
    if (cell->mFlag != 0)
    {
        struct Key { uint a; uint b; void* c; } key;
        key.a = mKey44;
        key.b = mKey48;
        key.c = mp4c;

        Item* it = SpaceGameGet_s0107_9260()->GetPlayerInventory()->F00ff3fb0(win);
        if (it != 0)
        {
            if (it->F104ccf0())
            {
                key.a = mKey68; key.b = mKey6c; key.c = mp70;
            }
            else if (it->F104feb0())
            {
                key.a = mKey5c; key.b = mKey60; key.c = mp64;
            }
            else if (it->F104ccd0())
            {
                key.a = mKey50; key.b = mKey54; key.c = mp58;
            }
        }

        cSPUILayout_s0107_9260* node = (cSPUILayout_s0107_9260*)operator_new_eastl(0x18, (const char*)g_key_13f6b3c,
                                                             0, 0, 0, 0);
        if (node != 0)
            node = node->Ctor();
        else
            node = 0;

        cSPUILayout_s0107_9260* old = (cSPUILayout_s0107_9260*)cell->mNode;
        if (node != old)
        {
            if (node != 0)
                ((IRefObj_s0107_9260*)node)->v01();
            cell->mNode = node;
            if (old != 0)
                ((IRefObj_s0107_9260*)old)->v02();
        }

        cSPUILayout_s0107_9260* cur = (cSPUILayout_s0107_9260*)cell->mNode;
        if (!cur->Init(&key, 0, 0x5b598fa))
        {
            cSPUILayout_s0107_9260* bad = (cSPUILayout_s0107_9260*)cell->mNode;
            if (bad != 0)
            {
                cell->mNode = 0;
                ((IRefObj_s0107_9260*)bad)->v02();
            }
        }
        else
        {
            INode* n2 = F1079d10(cur, (uint)sel);
            if (n2 != 0)
            {
                n2->v050(((UIGameCtx*)FUN_010666a0_s0107_9260())->F106edc0(win));
                uint en = ((INode*)win)->v020();
                n2->v054((-(uint)(en != 0) & 0x92ea67df) + 0x70648eae);
                n2->v0b8(0x600db9c, &win->mp0c);
                n2->v104(FUN_010666a0_s0107_9260());
                uint out;
                ((INode*)win)->v030(&out);
                FUN_00807c70(n2, (uint)((UIGameCtx*)FUN_010666a0_s0107_9260())->mp254, (int)out, -1);
                uint v18, v14;
                if (((INode*)win)->v034(&v18, &v14))
                    FUN_00806b20(n2, (int)v18, (int)v14);
                F1077bf0(win);
                cell->mFlag = 0;
            }
        }
    }

    if (mFlag9c != 0)
        win->mSel24 = (int)sel;
}

// @ 0x0107a300
void UISpace::F107a300()
{
    uint cells  = (uint)(mCells.end - mCells.begin);
    uint perRow = (uint)(mRows8c * mCols88);

    uint u = maxref(cells, 1u) - 1;
    if (u != 0)
    {
        uint8_t* pc = &mCells.begin[u].mFlag;
        do
        {
            if (*pc == 0)
                break;
            u -= 1;
            pc -= 0xc;
        } while (u > 0);
    }

    uint total;
    if (mSel90 == 0xffffffffu)
        total = (u / perRow + 1) * perRow;
    else
        total = maxref(mSel90, u + 1);

    uint n = total;
    mCells.F1079ff0(n);

    for (uint i = 0; i < n; ++i)
    {
        UICell* cell = mCells.begin + i;
        if (cell->mFlag != 0 && cell->mNode == 0 && mp74 != 0)
        {
            cSPUILayout_s0107_9260* node = (cSPUILayout_s0107_9260*)operator_new_eastl(0x18, (const char*)g_key_13f6b3c,
                                                                 0, 0, 0, 0);
            cSPUILayout_s0107_9260* made;
            if (node != 0)
                made = node->Ctor();
            else
                made = 0;

            cSPUILayout_s0107_9260* old = (cSPUILayout_s0107_9260*)cell->mNode;
            if (made != old)
            {
                if (made != 0)
                    ((IRefObj_s0107_9260*)made)->v01();
                cell->mNode = made;
                if (old != 0)
                    ((IRefObj_s0107_9260*)old)->v02();
            }

            ((cSPUILayout_s0107_9260*)cell->mNode)->Init(&mp74, 0, 0x5b598fa);
            F1079d10((cSPUILayout_s0107_9260*)cell->mNode, i);
        }
    }

    uint rows = maxref(total, 1u);
    rows = (rows - 1) / perRow + 1;
    if (mFlags80 == 0x120ad1fb)
        ((INode*)mp2c)->v074(mScaleBc, (float)rows * mScaleC0);
    else
        ((INode*)mp2c)->v074((float)rows * mScaleBc, mScaleC0);
    F1077e20();
}

// @ 0x0107a510
void __thiscall SP::cToolWidget::FUN_0107a510()
{
}

// @ 0x0107a5b0
__declspec(noinline) void __thiscall SP::cToolWidget::FUN_0107a5b0()
{
    FUN_0107a5b0_SideEffect();                           // clobbers ecx like the original
}

// @ 0x0107a6b0
void __thiscall SP::cToolWidget::FUN_0107a6b0()
{
}

// @ 0x0107a9a0
void __thiscall SP::cToolWidget::FUN_0107a9a0()
{
}

// @ 0x0107ab20
void __thiscall SP::cToolWidget::FUN_0107ab20(int32_t value)
{
    bool wasActive = mFlagE8;
    mField90 = value;
    if (wasActive)
        FUN_0107a300();
}

// @ 0x0107ab40
void __cdecl FUN_0107ab40()
{
}

// @ 0x0107abb0
void __thiscall SP::cToolWidget::FUN_0107abb0()
{
    if (!mFlagE8) {
        FUN_0107a5b0();
        mFlagE8 = true;
    }
}
