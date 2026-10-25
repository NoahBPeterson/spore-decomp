// src/game/SPGonzago/SPUISpace.cpp -- migrated from slice(s) s0107a510, s01077470, s010743a0, s0106ea40, s0106da70, s0106c930, s0106ada0, s0106a0a0, s01068800, s010678e0, s01066a40, s01064990, s00bbb9d0, s00b1fd50, s00435d40 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPUISpace.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

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
extern "C" uint32_t g_dw168a488;              // 0x168a488 empty-key sentinel
extern "C" uint32_t g_dw168a48c;              // 0x168a48c
extern "C" uint32_t g_dw168a490;              // 0x168a490
#pragma warning(disable: 4100)
struct PlanetRecord;
extern "C" PlanetRecord* GetActivePlanet();   // 0x1021260
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
struct PlanetObj {
    void FUN_00c80680(int one, void* key);   // 0xc80680
};
SpeciesMgr* FUN_00b3d420();      // 0xb3d420
// ---- items of slice s00bbb9d0 end

// ---- items of slice s01064990 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
extern float     gF_016e2230;     // 0x016e2230 (bullseye refresh threshold)
extern float     gF_13ec4d0;      // 0x013ec4d0  100.0f
extern float     gF_13f9c6c;      // 0x013f9c6c -100.0f
extern float     gF_13ec4b0;      // 0x013ec4b0    0.6f
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
typedef unsigned short wchar16;
extern wchar16   gW_CivConversionBar[];  // 0x014862ec  L"CivConversionBar"
void*     FUN_00b3d430(int a);                        // 0x00b3d430  TerraformingManager
void*     FUN_00b3d2a0();                             // 0x00b3d2a0  StarManager
void*     FUN_00b3d4a0();                             // 0x00b3d4a0  CommManager
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
void*     FUN_008414c0();                             // 0x008414c0
typedef void   (__thiscall *VF0)(void*);
typedef void*  (__thiscall *VFP)(void*);
typedef void   (__thiscall *VF1)(void*, int);
typedef void   (__thiscall *VF2)(void*, int, int);
typedef void   (__thiscall *VFMP)(void*, float*);
typedef void   (__thiscall *VFMP2)(void*, float, float);
struct SPUIGlobalUI {                 // the global-UI object (pointer at cSPUISpace+0x224)
    char   IsTooltipVisible();        // 0x00e01380
    void   SetVisibility(int v);      // 0x00e01350
    void*  FindWindowByID(uint32_t id);  // 0x00e012b0
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
    void     FUN_01067720(void* p, float f1, float f2, char flag);
    void     FUN_010677b0(CGameNounManager* mgr, float f1, float f2, char flag);
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
void* SP_GetNounManager();                  // 0x00b3d230
void* SP_GetMissionManager();               // 0x00feb9f0
int   SP_IsPlanetArchived();                // 0x01021240
int   FUN_01021230();                       // 0x01021230
void* SP_GetPlayerHomePlanet();             // 0x01021370
u32   SP_GetUniverseContext();              // 0x01021080
void* SP_GetUFOSimulator();                 // 0x00ffbe50
void* SP_GetTriggerManager();               // 0x00b3d4d0
void* SP_GetHUDSpaceFrame();                // 0x0067caf0
void* SP_GetSystemNounManager();            // 0x00b3d410
u32   FUN_00458a40(void* rgb);              // 0x00458a40  ColorRGBToU32
u32   FUN_00c8b540();                       // 0x00c8b540
u32   FUN_00c70e00();                       // 0x00c70e00
u8    FUN_00c70b50();                       // 0x00c70b50
void  FUN_01066630(void* p);                // 0x01066630
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
extern void* FUN_01002bd0();                                            // 0x1002bd0 SP::SpaceGameGet
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
extern void* FUN_0067ddd0();                                            // 0x67ddd0 SP::EffectsManager
extern void* FUN_00b3d4d0();                                            // 0xb3d4d0 GetTriggerMgr
struct Vtbl { void* mSlots[0x120 / 4]; };
typedef void  (__thiscall *VFn_v)(void*);
typedef void* (__thiscall *VFn_p)(void*);
typedef char  (__thiscall *VFn_c)(void*);
typedef int   (__thiscall *VFn_i)(void*);
typedef void  (__thiscall *VFn_vi)(void*, int);
typedef void* (__thiscall *VFn_pi)(void*, int);
typedef void  (__thiscall *VFn_vii)(void*, int, int);
typedef void* (__thiscall *VFn_pii)(void*, int, int);
typedef void  (__thiscall *VFn_vp)(void*, void*);
typedef void  (__thiscall *VFn_vff)(void*, float, float);
typedef void  (__thiscall *VFn_vpp4)(void*, void*, void*, int, int, int);
#define VSLOT(o, n) (((Vtbl*)*(void**)(o))->mSlots[(n) / 4])
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
struct SpaceGame       { uint8_t mPad00[0x20]; void*    mOwner; };        // +0x20
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

    void FUN_0106ada0();
    void FUN_0106b220(void* badge);
    void ManageSeti(void* civ, int arg2);  // 0x0106b310 (cSPUISpace::ManageSeti)
    void FUN_0106b500(void* item);
    void FUN_0106b630();
    int  FUN_0106b9b0(int key, int index);
    void FUN_01068230();            // 0x1068230 thiscall callee used by ManageSeti
};
// ---- items of slice s0106ada0 end

// ---- items of slice s0106c930 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct cIntrusiveNode {
    cIntrusiveNode* mpNext;                                  // +0x00
    cIntrusiveNode* mpPrev;                                  // +0x04

    void Init(cIntrusiveNode* self, void* value, void** src, uint32_t dummy); // 0x0106b950
    void* Construct(void** src);
};  // namespace SP
}
// ---- items of slice s0106c930 end

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
    void FUN_010691e0();                     // 0x010691e0
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
struct Obj;
#define VTSLOT(obj, off) ((*(void***)(obj))[(off) / 4])
typedef void  (__thiscall *Fn_v_p)(void*);
typedef void  (__thiscall *Fn_v_pp)(void*, void*);
typedef Obj*  (__thiscall *Fn_p_p)(void*);
typedef Obj*  (__thiscall *Fn_p_pi)(void*, int);
typedef Obj*  (__thiscall *Fn_p_ppp)(void*, void*, void*);
extern "C" u32 DAT_015b9558 = 0;    // 0x015b9558  tooltip style id
struct cScrollElem {
    void* mpObj;         // +0x00
    float mField4;       // +0x04
    u8    mByte8;        // +0x08
    u8    mPad9[3];
};
struct cUITimedTooltip {
    u8   mPad00[0x30];
    char Init(u32 a1, u32 a2, u32 a3, u32 a4, int a5, int a6); // 0x00e36b30
    Obj* FindWindow(int id, bool flag);                          // 0x00e36650
};
struct cSporeItem {
    void* FUN_0106edc0();           // 0x0106edc0
};
void  __cdecl EA_Messaging_RemoveHandler(void*, void*, void*, void*, void*); // 0x00571db0
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
u32 __cdecl FUN_01077b40(void* p);
// ---- items of slice s01077470 end

// ---- items of slice s0107a510 begin (TODO(rewrite): local stubs, replace by canonical classes)
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

    TerraformingManager* tfm = (TerraformingManager*)FUN_00b3d430(0);
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
        float v     = FUN_00c8c7f0((void*)(size_t)param, &local);
        if (local != -1) {
            if (((StarManager*)FUN_00b3d2a0())->GetEmpireByID(local) == 0)
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
    void* sysMgr = ((StarManager*)FUN_00b3d2a0())->GetSystemMgr();
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
            if (((StarManager*)FUN_00b3d2a0())->GetEmpireByID(local) == 0)
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
    float v     = FUN_00c8c7f0(p, &local);
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
        void* sysMgr = ((StarManager*)FUN_00b3d2a0())->GetSystemMgr();
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
    if (begin == end) return dst;
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
    if (g != 0) {
        cSimThing* p = g->m14;
        return p->FUN_01065d20();
    } else {
        cSimThing* p = 0;
        return p->FUN_01065d20();
    }
}

// @ 0x010687d0
Blk28* Blk28::Destroy(u8 flags)
{
    ObjRel* o = m08;
    if (o != 0) o->Release();
    if (flags & 1) SP_DeleteArray(this);
    return this;
}

// @ 0x01068800
void __stdcall FUN_01068800(void* layout, u32 index, void* obj, u32 unused)
{
    void* w1 = ((FnFind)(*(void***)layout)[0xf0 / 4])(layout, (index + 0x1c2245) << 4, 1);
    ((Fn2)(*(void***)w1)[0x7c / 4])(w1, 1, 1);

    index <<= 4;
    void* w2 = ((FnFind)(*(void***)layout)[0xf0 / 4])(layout, index + 0x1c22451, 1);

    EaString16 sEarly;
    EaString16 sLate;
    sLate.mpBegin = 0x1667bac;
    sLate.mpEnd = 0x1667bac;
    FnP fnB8 = (FnP)(*(void***)obj)[0xb8 / 4];
    sLate.mpCap = 0x1667bae;
    fnB8(obj, &sLate);
    ((FnP)(*(void***)w2)[0x80 / 4])(w2, (void*)sLate.mpBegin);

    void* w3 = ((FnFind)(*(void***)layout)[0xf0 / 4])(layout, index + 0x1c22452, 1);
    if (w3 != 0) {
        sEarly.mpBegin = 0x1667bac;
        sEarly.mpEnd = 0x1667bac;
        FnP fnC8 = (FnP)(*(void***)obj)[0xc8 / 4];
        sEarly.mpCap = 0x1667bae;
        fnC8(obj, &sEarly);
        ((FnP)(*(void***)w3)[0x80 / 4])(w3, (void*)sEarly.mpBegin);
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
    FUN_00435ed0(0xed858785, audiofx);

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
    if (self == 0)
        return 0;
    void* w = ((VFn_p)VSLOT(self, 0xa8))(self);
    if (w == 0)
        return 0;
    void* h = ((VFn_pi)VSLOT(w, 0x0c))(w, 0xef3c47cf);
    if (h == 0)
        return 0;
    void* img = 0;
    FUN_00806230(icon, &img, 0, -1, -1);
    if (img == 0)
        return 0;
    ((VFn_vp)VSLOT(h, 0x14))(h, img);
    if (img != 0)
        ((VFn_v)VSLOT(img, 4))(img);
    return 1;
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
void __stdcall FUN_0106b950(Node* head, Node* begin, Node* end, int unused)
{
    (void)unused;
    for (; begin != end; begin = begin->mNext) {
        Node* n = (Node*)FUN_00f473a0(0xc, "Simulator", 0, 0, (void*)0x13ebb38, 0xd1);
        if (&n->mData != 0)
            n->mData = begin->mData;
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
: mf150(1.0f), mf154(2.0f)
{
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
    uint32_t i;

    if (count != 0) {
        const uint32_t* pIds = mpIdsBegin;
        uint32_t pivot = m23c;

        for (i = 0; i < count; ++i) {
            if (pIds[i] == pivot)
                next = pIds[(i + 1) % count];
        }
    }
    ToggleToolUI(next);
}

// @ 0x0106e630
void cSPUISpace_s0106_da70::FUN_0106e630()
{
    uint32_t count = (uint32_t)(mpIdsEnd - mpIdsBegin);
    uint32_t next = 0;
    uint32_t i;

    if (count != 0) {
        const uint32_t* pIds = mpIdsBegin;
        uint32_t pivot = m23c;

        for (i = 0; i < count; ++i) {
            if (pIds[i] == pivot)
                next = pIds[(count - 1 + i) % count];
        }
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
    mpEnd += last - first;
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
            newBegin = (Blk28_s0106_ea40*)operator_new(newCap * 0x28, "Simulator", 0, 0, 0, 0xd1);
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

        cTextZoomName* t = (cTextZoomName*)operator_new(0x78, "UI/cSPUITextZoom", 0, 0, 0, 0);
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

// @ 0x0107a6b0
void __thiscall SP::cToolWidget::FUN_0107a6b0()
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

// @ 0x0107abb0
void __thiscall SP::cToolWidget::FUN_0107abb0()
{
    if (!mFlagE8) {
        FUN_0107a5b0();
        mFlagE8 = true;
    }
}
