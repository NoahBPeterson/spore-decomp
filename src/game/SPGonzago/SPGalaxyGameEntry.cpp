// src/game/SPGonzago/SPGalaxyGameEntry.cpp -- migrated from slice(s) s00dfa5c0, s00df8730, s00df47b0, s00de8ad0, s00e00760, s00dfe460, s00dfd5b0, s00dfc5b0, s00dfb5b0, s00df6db0, s00df3be0, s00df10d0, s00de6170, s00de41b0, s00de23a0, s00de1710, s00ddcdc0, s006775f0, s01364b20, s00dff790, s00df9650, s00df7ce0, s00df6700, s00df5670, s00df2d80, s00df1e70, s00df0280, s00def400, s00dee450, s00ded5a0, s00dec7c0, s00deb840, s00dea870, s00de9a00, s00de5040, s00de3300, s00de0910, s00ddf990 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPGalaxyGameEntry.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

// addresses retail relocates here, named so the build relocates them too
extern "C" char g_13eb938[];
extern "C" char g_147dba8[];
extern "C" char g_147dd00[];
extern "C" char g_147e3b0[];
extern "C" char g_147e618[];
extern "C" char g_15a2df8[];
extern "C" char g_1667bac[];
extern "C" char g_1667bae[];

#include "game/types.h"
#include "SP/cString.h"
#include "EA/DateTime/DateTime.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "EA/Stopwatch.h"
#include "SP/cGameData.h"
#include "SP/FunctionalMatch/Constraint.h"
#include "SP/cGameInfo.h"
#include "SP/cPropertyList.h"
#include "cSPUILayout.h"
#include "eastl/map.h"
#include "SP/cStarManager.h"
#include "EA/Variant.h"
#include "SP/cSPUIAssetBrowser.h"
#include "SP/cPlanetModel.h"
#include "SP/cStarRecord.h"
#include "SP/cTerrainSphere.h"
#include <intrin.h>
#include <string.h>
#include "cSPUILayeredObject.h"
#include "SP/cSpeciesProfile.h"
#include <math.h>
#include "cSPUIPropertyLayout.h"
#include "SP/cPlanetRecord.h"
#include "SP/cPropertyManager.h"
#include "SP/cVarListSerializer.h"
#include "cSPVector3.h"
#define __PLACEMENT_NEW_INLINE   // the slices' own placement new/delete win over <new>'s (rewrite.py)
#include <new>
#include "EA/ResourceMan/Key.h"
#include "EA/Text/Font.h"
#include <stdlib.h>
#include "SP/cSPEditorUI.h"
#include "SP/cSPUIAssetBrowserCallback.h"
#include "EA/LimitStopwatch.h"
inline void operator delete(void*, void*) {}   // placement delete (<new>'s is skipped, rewrite.py)

// ---- items of slice s00ddf990 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gInterfaceValue;
extern float gInterfaceBlend;
extern float gInterfaceAngle;
extern float gInterfaceAlpha;
extern float gInterfaceTargetX;
extern float gInterfaceTargetY;
extern float gInterfaceTargetZ;
extern float gInterfaceStep;
extern float gInterfaceSpeed;
struct cMethodTable {
    void* mSlots[0x40];
};
struct cDispatchObject {
    cMethodTable* mpMethods;                    // 0x00

    void* Call(int nSlot) {
        return ((void* (*)(void*))mpMethods->mSlots[nSlot >> 2])(this);
    }
    void* Call(int nSlot, uint32_t nArg1) {
        return ((void* (*)(void*, uint32_t))mpMethods->mSlots[nSlot >> 2])(this, nArg1);
    }
    void* Call(int nSlot, uint32_t nArg1, uint32_t nArg2) {
        return ((void* (*)(void*, uint32_t, uint32_t))mpMethods->mSlots[nSlot >> 2])(this, nArg1, nArg2);
    }
    void* Call(int nSlot, void* pArg1) {
        return ((void* (*)(void*, void*))mpMethods->mSlots[nSlot >> 2])(this, pArg1);
    }
    void* Call(int nSlot, void* pArg1, int nArg2) {
        return ((void* (*)(void*, void*, int))mpMethods->mSlots[nSlot >> 2])(this, pArg1, nArg2);
    }
};
class cInterfaceState {
public:
    cInterfaceState(cDispatchObject* pTarget);
    ~cInterfaceState();
    bool ResetDefaults();
    void PushMatrix(uint32_t nKey);
    void UpdateTransition(unsigned int nElapsed, uint32_t nFlags);
    void UpdateFade(float fDelta);
    void UpdateSequence(int nDelta);
    void UpdateAlpha(int nDelta);
    void BeginSequence(uint8_t bFirst, uint8_t bSecond);
    void ResetSequence();
    void NotifySequence();
    bool IsIdle();

    uint32_t mpVftable;                         // 0x00
    int mnTimer;                                // 0x04
    uint8_t mPad08[0x18];                       // 0x08
    float mfValue20;                            // 0x20
    float mfValue24;                            // 0x24
    float mfValue28;                            // 0x28
    float mfValue2c;                            // 0x2c
    float mfValue30;                            // 0x30
    float mfTolerance;                          // 0x34
    float mfStart38;                            // 0x38
    float mfStart3c;                            // 0x3c
    uint8_t mbFlag40;                           // 0x40
    uint8_t mPad41[0x03];                       // 0x41
    float mfTo44;                               // 0x44
    float mfTo48;                               // 0x48
    float mfTo4c;                               // 0x4c
    float mfFrom50;                             // 0x50
    float mfFrom54;                             // 0x54
};
struct cInterfaceDefaults {
    float mfUnknown00;                          // 0x00
    float mfUnknown04;                          // 0x04
    float mfX;                                  // 0x08
    float mfY;                                  // 0x0c
    float mfZ;                                  // 0x10
};
extern cInterfaceDefaults gInterfaceFrom;
extern uint32_t gInterfaceTimer;
extern uint8_t gInterfaceStarted;
void PostInterfaceMessage(uint32_t nId, int nValue);
int RoundToInt(float fValue);
// ---- items of slice s00ddf990 end

// ---- items of slice s00de0910 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void*    __cdecl FUN_00f473a0(uint32_t size, const char* name, int a, int b, int c, int d); // 0x00f473a0 operator_new
extern "C" void*    __cdecl FUN_00a206f0(void);            // 0x00a206f0 EA::Audio::GetSystemAT
extern "C" void*    __cdecl FUN_00df5f40(void);            // 0x00df5f40
extern "C" void      __cdecl FUN_00de5d00(uint32_t a1, void* a2, int a3, int a4, int a5, void* a6, void* a7); // 0x00de5d00
extern uint32_t DAT_015da784;     // 0x015da784
extern uint32_t DAT_015da788;     // 0x015da788
extern uint32_t DAT_015da78c;     // 0x015da78c
extern uint32_t DAT_015da790;     // 0x015da790
extern char k_szSporepedia[];     // 0x013fa29c "Sporepedia"
union LARGE_INTEGER {
    struct { uint32_t LowPart; int32_t HighPart; } u;
    int64_t QuadPart;
};
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(void* lpCount);
#define VFN(obj, off) (*(void**)((char*)(*(void**)obj) + (off)))
class tHost {
public:
    void*   __thiscall FindWindowByID(uint32_t id);              // 0x00e012b0 cSPUIGlobalUI::FindWindowByID
    void*   __thiscall FUN_008105b0(uint32_t id, int flag);      // 0x008105b0 cSPUILayout::FindWindowByID
    void    __thiscall FUN_00e01350(int v);                      // 0x00e01350 cSPUIGlobalUI::SetVisibility
    void*   __thiscall FUN_005a9080();                           // 0x005a9080 cEditorLaunchData::cEditorLaunchData
    void    __thiscall FUN_006b5060();                           // 0x006b5060 cString ctor
    void    __thiscall FUN_006b5240();                           // 0x006b5240 cString dtor
    void    __thiscall FUN_00de0670(uint8_t a, uint8_t b);       // 0x00de0670 cInterfaceState::BeginSequence
    void    __thiscall FUN_0093a2e0();                           // 0x0093a2e0 cDirectPropertyList::SetBoolProperty
    void    __thiscall FUN_00de53d0(uint32_t a);                 // 0x00de53d0
    void    __thiscall FUN_00de86d0(int a, int b);               // 0x00de86d0
    void    __thiscall FUN_00e00670(uint32_t a, void* b);        // 0x00e00670
    void    __thiscall FUN_00e00650(uint32_t a, void* b);        // 0x00e00650
    void    __thiscall FUN_00e00760(uint32_t a);                 // 0x00e00760 ShowContextSporepedia
    void    __thiscall FUN_00ddb760();                           // 0x00ddb760
    void    __thiscall FUN_00e3e350();                           // 0x00e3e350
    bool    __thiscall FUN_00ec5a60(void* pVec, int a, int b);   // 0x00ec5a60
    bool*   __thiscall FUN_0041e920();                           // 0x0041e920 cProperty::GetBool
    void    __thiscall FUN_00b1dee0();                           // 0x00b1dee0
};
class cPanelIDs {
public:
    uint8_t  mPad000[0x108];   // +0x000
    int32_t  m108;             // +0x108
    uint8_t  mPad10c[0x38];    // +0x10c
    uint8_t  m144[0x40];       // +0x144 cSPUILayout subobject
    void*    m184;             // +0x184 cSPUIGlobalUI*
    uint32_t m188;             // +0x188
    uint32_t m18c;             // +0x18c
    uint32_t m190;             // +0x190
    uint8_t  m194[4];          // +0x194
    uint8_t  m198[0x40];       // +0x198 cInterfaceState subobject
    void**   m1d8;             // +0x1d8 vector begin
    void**   m1dc;             // +0x1dc vector end
};
extern cPanelIDs* kGUI_PanelIDs;   // 0x016a1344
class cContentValidationSummarizer {
public:
    void*    mVtbl0;     // +0x00
    volatile void* mVtbl4; // +0x04 (volatile: the ctor stores it twice, as the base then derived vfptr)
    uint32_t m08;        // +0x08
    void*    m0c;        // +0x0c
    uint8_t  m10;        // +0x10
    uint8_t  mPad11[3];
    void* __thiscall FUN_00de0a90(void* pOuter, uint8_t b);
};
class cEditorLaunchData {
public:
    uint8_t  mPad00[0x0c];   // +0x000
    uint32_t m0c;            // +0x00c
    uint32_t m10;            // +0x010
    uint32_t m14;            // +0x014
    uint32_t m18;            // +0x018
    uint8_t  mPad1c[8];      // +0x01c
    uint32_t m24;            // +0x024
    uint32_t m28;            // +0x028
    uint32_t m2c;            // +0x02c
    uint32_t m30;            // +0x030
    uint8_t  m34;            // +0x034
    uint8_t  m35;            // +0x035
    uint8_t  m36;            // +0x036
    uint8_t  m37;            // +0x037
    uint8_t  m38;            // +0x038
    uint8_t  m39;            // +0x039
    uint8_t  m3a;            // +0x03a
    uint8_t  mPad3b;         // +0x03b
    uint8_t  m3c;            // +0x03c
    uint8_t  m3d;            // +0x03d
    uint8_t  mPad3e[0x26];   // +0x03e
    uint8_t  m64;            // +0x064
    uint8_t  mPad65[7];      // +0x065
    uint8_t  m6c;            // +0x06c
    uint8_t  m6d;            // +0x06d
    uint8_t  m6e;            // +0x06e
    uint8_t  m6f;            // +0x06f
    uint8_t  mPad70[0x20];   // +0x070
    void*    m90;            // +0x090
    void*    m94;            // +0x094
    void*    m98;            // +0x098
};
class cGalaxyGameEntryImpl {
public:
    uint8_t  mPad00[0x20];   // +0x000
    uint8_t  m20;            // +0x020
    uint8_t  mPad21[3];      // +0x021
    uint32_t m24;            // +0x024
    uint32_t m28;            // +0x028
    uint32_t m2c;            // +0x02c
    uint32_t m30;            // +0x030
    void*    m34;            // +0x034
    uint32_t m38;            // +0x038
    uint32_t m3c;            // +0x03c
    uint8_t  mPad40[0x68];   // +0x040
    void*    ma8;            // +0x0a8
    void*    mac;            // +0x0ac
    uint8_t  mPadb0[8];      // +0x0b0
    uint32_t mb8;            // +0x0b8
    uint32_t mbc;            // +0x0bc
    uint32_t mc0;            // +0x0c0
    uint32_t mc4;            // +0x0c4
    int32_t  mc8;            // +0x0c8
    uint8_t  mPadcc[4];      // +0x0cc
    uint8_t  md0;            // +0x0d0
    uint8_t  mPadd1[3];      // +0x0d1
    uint32_t md4;            // +0x0d4
    uint32_t md8;            // +0x0d8
    uint32_t mdc;            // +0x0dc
    uint32_t me0;            // +0x0e0

    uint32_t __thiscall FUN_00de0910(uint32_t key);
    void     __thiscall FUN_00de0a30(uint32_t param_1, void* param_2);
    void     __thiscall FUN_00de0ae0(uint32_t arg);
    void     __thiscall FUN_00de0bc0(uint32_t param_2, uint32_t param_3, uint32_t param_4);
    void     __thiscall FUN_00de0e90(uint32_t param_1, uint32_t* param_2, int param_3);
    void     __thiscall FUN_00de0f90();
    bool     __thiscall FUN_00de10a0(uint32_t key, uint32_t* param_2);
    void     __thiscall FUN_00de11a0();
    void     __thiscall FUN_00de1320();
    void     __thiscall FUN_00de1330(uint32_t param_1);
    void     __thiscall FUN_00de13d0(uint32_t param_1, uint32_t param_2);
    void     __thiscall FUN_00de1600(uint32_t* param_1);
};
static void AssignRef(void** ppTarget, void* pNew, int nAddSlot, int nRelSlot)
{
    void* pOld = *ppTarget;
    if (pNew != pOld) {
        if (pNew != 0)
            ((void(__thiscall*)(void*))VFN(pNew, nAddSlot))(pNew);
        *ppTarget = pNew;
        if (pOld != 0)
            ((void(__thiscall*)(void*))VFN(pOld, nRelSlot))(pOld);
    }
}
// ---- items of slice s00de0910 end

// ---- items of slice s00de3300 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl FUN_0067cab0();               // 0x0067cab0
extern "C" void* __cdecl MessageServer();              // 0x0067dcc0
extern "C" void* __cdecl MovieSystem();                // 0x0067cb10
extern "C" int* __cdecl EA_Audio_GetSystemAT();       // 0x00a206f0
struct Obj; extern "C" Obj* __cdecl SP_App();                     // 0x0067dd10
extern "C" int* __cdecl SP_AppSystem();               // 0x0067dd00
extern "C" void* __cdecl SP_PropertyManager();         // 0x0067de30
extern "C" void  __cdecl op_del_array(void* p);        // 0x00f47380
extern "C" void* __cdecl FUN_00b3d410();                        // 0x00b3d410
extern "C" void  __cdecl SPUIHelpers_GetMainWindowArea(void* area); // 0x00805ea0
extern "C" void  __cdecl FUN_00881720(int a, int b, int c, wchar_t* buf, int d, int e); // 0x00881720
extern "C" void  __cdecl SetDateFromTm(void* tm, void* dt);         // 0x0092e440
typedef unsigned int   u32;
typedef int            s32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef float          f32;
typedef void  (__thiscall* FnV)(void*);
typedef u32   (__thiscall* FnU)(void*);
typedef void  (__thiscall* Fn1)(void*, u32);
typedef void  (__thiscall* Fn2)(void*, u32, u32);
typedef void  (__thiscall* Fn3)(void*, u32, u32, u32);
typedef void  (__thiscall* FnP)(void*, void*);
typedef void  (__thiscall* Fn2P)(void*, u32, u32, void**);
typedef void  (__thiscall* FnUP)(void*, u32, void*);
typedef void* (__thiscall* FnPP)(void*);
typedef void* (__thiscall* FnC)(void*, u32);
typedef char  (__thiscall* FnQC)(void*, u32, u32, void**);
extern "C" void  __cdecl KillSetiEffects(u32 id, u32 v);        // 0x00435ed0
void  __cdecl KillSetiEffects(u32 id, void* v);               // 0x00435ed0 (pointer-argument spelling)
extern "C" void* __cdecl SPUIHelpers_GetImageFromLayout(void* layout, u32 which); // 0x008061c0
extern "C" void  __cdecl FUN_008068d0(void* win, void* img, u32 a); // 0x008068d0
extern "C" char  __cdecl SPUIHelpers_CreateImageFromResource2(void* res, void** out,
                                                              s32 a, s32 b, s32 c); // 0x00806230
extern "C" char  __cdecl SP_GetPropertyAsString16(void* obj, u32 key, void* out); // 0x006a1400
struct Stopwatch {
    void Ctor(int a, int b);      // 0x0093a560
    void SetUnits(int u);         // 0x0093a1a0
    void Restart();               // 0x00571e80
    u8   mPad[0x18];
};
struct EaString16 {
    u32 mpBegin;                  // +0x00
    u32 mpEnd;                    // +0x04
    u32 mpCap;                    // +0x08
    void Assign(u32 first, u32 last);      // 0x00423650
    void RangeInit(const wchar_t* text);   // 0x00579a90
};
struct Obj198Sub {
    void* mpVtbl;                 // +0x00
};
struct Obj198 {
    u8        mn00[4];            // +0x00
    Obj198Sub mSub04;             // +0x04
    void Do();                    // 0x00dde570
};
struct UI {
    void* FindWindowByID(u32 id);   // 0x00e012b0
    void  SetVisibility(u32 v);     // 0x00e01350
};
struct Layout {
    void* FindWindowByID(u32 id, u32 one);   // 0x008105b0
};
struct F8Obj {
    u8     mPad00[0xb8];
    Layout* mpLayoutB8;             // +0xb8
};
struct Root {
    void FUN_df95d0();              // 0x00df95d0
};
struct EntryBase {
    void BaseCtor();                // 0x00e00630
};
struct GameEntry : EntryBase {
    void*      mpVtbl;              // +0x00
    u32        mn04;                // +0x04
    Stopwatch  mStopwatch;          // +0x08
    EaString16 mStr20;              // +0x20
    u32        mn2C;                // +0x2c
    EaString16 mStr30;              // +0x30
    u32        mn3C;                // +0x3c
    u32        mn40;                // +0x40
    u32        mn44;                // +0x44
    u32        mp48;                // +0x48
    u8         mPad4C[0xac];        // +0x4c
    void*      mpF8;                // +0xf8
    u8         mPadFC[0x48];        // +0xfc
    u8         mLayout144[0x18];    // +0x144
    void*      mp15C;               // +0x15c
    u8         mPad160[0x24];       // +0x160
    void*      mp184;               // +0x184
    u8         mPad188[0x10];       // +0x188
    Obj198*    mp198;               // +0x198
    u8         mPad19C[0x3c];       // +0x19c
    u32        mp1D8;               // +0x1d8
    u32        mn1DC;               // +0x1dc
    u8         mPad1E0[0x11];       // +0x1e0
    u8         mb1F1;               // +0x1f1

    void       FUN_de3300();                       // 0x00de3300
    GameEntry* Ctor_de3370();                      // 0x00de3370
    void       OnModalWindowEnd(u32 a2, u32 a3);   // 0x00de33e0
    void       Dtor_de35d0();                      // 0x00de35d0
    void       BlowSavedGameUpRealGood();          // 0x00de3650
    void       FUN_de38b0(u32 id, u32 arg);        // 0x00de38b0
    void       ShowGalaxy(u32 on);                 // 0x00de5470
    void       FUN_de53d0(u32 a);                  // 0x00de53d0
    void       FUN_de86d0(u32 a, u32 b);           // 0x00de86d0
    void       FUN_de52d0();                       // 0x00de52d0
    void       FUN_e00650(u32 id, u32 arg);        // 0x00e00650
};
struct Mgr {
    u32  FUN_8013c0();              // 0x008013c0
    bool FindLocal(u32 id);         // 0x00801bb0
};
struct CursorCtx {
    void GetInfo(void* out, void* arg);   // 0x007c4180
};
struct ObjE3 {
    void Do(u32 a, u32 mode, u32 b);   // 0x00e3e350
};
struct AnimObj {
    u8  mPad00[0xa4];
    u32 mnA4;                       // +0xa4
};
struct Vec3f {
    f32 x;                          // +0x00
    f32 y;                          // +0x04
    f32 z;                          // +0x08
};
struct Vec4f {
    f32 x;                          // +0x00
    f32 y;                          // +0x04
    f32 z;                          // +0x08
    f32 w;                          // +0x0c
};
struct Vec3i {
    s32 x;                          // +0x00
    s32 y;                          // +0x04
    s32 z;                          // +0x08
};
struct Vec3iList {
    s32 mpBegin;                    // +0x00
    s32 mpEnd;                      // +0x04
};
struct RandomLCG {
    u32 RandomUint32Uniform(u32 n); // 0x00a68fb0
};
struct VisualOut {
    u8  mPad00[0x80];
    f32 mf80;                       // +0x80
    f32 mf84;                       // +0x84
    f32 mf88;                       // +0x88
};
struct Mat33 {
    f32 m[9];
};
struct Xform {
    u16   mn00;                     // +0x00
    u16   mn02;                     // +0x02
    f32   mf04;                     // +0x04
    f32   mf08;                     // +0x08
    f32   mf0C;                     // +0x0c
    f32   mf10;                     // +0x10
    Mat33 mMat;                     // +0x14
};
struct WString16 {
    u32 mpBegin;                    // +0x00
    u32 mpEnd;                      // +0x04
    u32 mpCap;                      // +0x08
    u32 mnPadC;                     // +0x0c
};
struct DateTime {
    u8  mPad[8];
    void Set(int v);                // 0x0092e3d0
    int  GetParameter(int p);       // 0x0092df80
};
struct CString20 {
    CString20();                                        // 0x006b5060
    CString20(u32 a, u32 b, const wchar_t* c);          // 0x006b5770
    ~CString20();                                       // 0x006b5240
    CString20& operator=(const CString20& other);       // 0x006b5430
    const wchar_t* GetText();                           // 0x006b55c0
    u8 mPad[0x14];
};
// ---- items of slice s00de3300 end

// ---- items of slice s00de5040 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const wchar_t* g_pNameA;     // 0x016a0d44  alternate galaxy layout name
extern const wchar_t* g_pNameB;     // 0x016a0d34  default galaxy layout name
extern const wchar_t* g_pUIKeyName; // 0x016a0d24
struct Vec3_s00de_5040 {
    float x, y, z;
    Vec3_s00de_5040() {}
    Vec3_s00de_5040(float fx, float fy, float fz) : x(fx), y(fy), z(fz) {}
};
struct Matrix3_s00de_5040 { float m[9]; };
struct XformMsg_s00de_5040 {
    uint16_t flags;         // +0x00
    uint16_t count;         // +0x02
    Vec3_s00de_5040     pos;           // +0x04
    float    scale;         // +0x10
    Matrix3_s00de_5040  rot;           // +0x14

    XformMsg_s00de_5040();                                     // 0x00434040
    void Init();                                    // 0x00832dc0 identity transform
    void SetPos(const Vec3_s00de_5040& v) { pos = v; flags |= 4; ++count; }
    void SetScale(float s)     { scale = s; ++count; }
};
inline Vec3_s00de_5040 operator*(const Vec3_s00de_5040& v, const Matrix3_s00de_5040& m)
{
    return Vec3_s00de_5040(v.x * m.m[0] + v.y * m.m[3] + v.z * m.m[6],
                v.x * m.m[1] + v.y * m.m[4] + v.z * m.m[7],
                v.x * m.m[2] + v.y * m.m[5] + v.z * m.m[8]);
}
inline Vec3_s00de_5040& operator+=(Vec3_s00de_5040& a, const Vec3_s00de_5040& b)
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return a;
}
struct cGalaxyHandle {
    virtual void h0();              // vtbl+0x00
    virtual void hRelease();        // vtbl+0x04
    virtual void hStart(int a);     // vtbl+0x08
    virtual void hStop(int a);      // vtbl+0x0c
    virtual void h10();             // vtbl+0x10
    virtual void h14();             // vtbl+0x14
    virtual void h18(XformMsg_s00de_5040* pMsg); // vtbl+0x18  set transform
};
struct cGalaxyManager {
    virtual void m0();                                // vtbl+0x00
    virtual void m1();                                // vtbl+0x04
    virtual bool mAdd(unsigned int id, int a, void** out); // vtbl+0x08
    virtual void m3();                                // vtbl+0x0c
};
struct GalaxyHandleSlot {
    cGalaxyHandle* mpHandle;        // +0x00

    void Create(cGalaxyManager* pManager, uint32_t nId);   // inlined at every call site
    void Stop(int32_t nFlags);
};
inline void GalaxyHandleSlot::Create(cGalaxyManager* pManager, uint32_t nId)
{
    if (mpHandle != 0) {
        cGalaxyHandle* pOld = mpHandle;
        mpHandle = 0;
        pOld->hRelease();
    }
    pManager->mAdd(nId, 0, (void**)&mpHandle);
}
inline void GalaxyHandleSlot::Stop(int32_t nFlags)
{
    if (mpHandle != 0)
        mpHandle->hStop(nFlags);
}
struct VecHeader {
    int begin;      // +0
    int cur;        // +4
    int end;        // +8
    int cap;        // +0xc
};
struct RecBC {
    VecHeader a;            // +0x00
    VecHeader b;            // +0x10
    VecHeader c;            // +0x20
    char      rest[0xbc - 0x30];
};
void operator_delete_array(void* p);
struct Str16 {
    wchar_t* begin;     // +0
    wchar_t* end;       // +4
    wchar_t* cap;       // +8
    int      unused;    // +0xc

    Str16()
    {
        begin = (wchar_t*)g_1667bac;
        end   = (wchar_t*)g_1667bac;
        cap   = (wchar_t*)g_1667bae;
    }
};
struct cGameData {
    Str16 s0;                       // +0x00
    Str16 s1;                       // +0x10
    Str16 s2;                       // +0x20
    int   z30, z34, z38, z3c, z40, z44;
    int   keep48;                   // +0x48 (not zeroed here)
    int   z4c, z50, z54, z58, z5c, z60, z64, z68, z6c, z70, z74, z78;

    void        FUN_00b26fb0(unsigned int a);  // 0x00b26fb0
    cGameData(unsigned int p2);                // 0x00de60f0
};
inline void FreeHeader(VecHeader& v)
{
    int n = v.end - v.begin;
    if ((n & ~1) > 2 && v.begin != 0)
        operator_delete_array((void*)v.begin);
}
struct cAchievements {
    bool FUN_00675e80(void);    // 0x00675e80 (hash-map lookup)
    bool FUN_005c0dd0(void);    // 0x005c0dd0
    void AwardAchievement(void); // 0x00676710
};
cAchievements* __stdcall FUN_00675250(unsigned int a);   // 0x00675250
cAchievements* __stdcall FUN_00675250_0(void);           // 0x00675250 (no-arg form)
struct RBNode { char pad[0x10]; unsigned int id; };
void* __cdecl RBTreeIncrement(void* n);   // 0x00921580
struct MapItr { void* node; };
struct RBTreeThing {
    int     count;      // +0x000
    void*   sentinel;   // +0x004
    void*   root;       // +0x008

    MapItr* find(MapItr& out, const unsigned int& key);   // 0x00e5c780
};
struct KeyNode {
    char pad[0x1c];
    int  v1c;   // +0x1c
    int  v20;   // +0x20
    int  v24;   // +0x24
};
struct OutKey3 { int a, b, c; };
struct RbFind56 {
    int     count;      // +0x00
    void*   sentinel;   // +0x04 (this+0x3c)
    void*   root;       // +0x08

    void*   Find(void* a, void** b);   // 0x00a21dc0
};
struct Key2 { int a, b; };
struct RbNode57 { char pad[0x10]; Key2 key; };
// rbtree iterator, returned by value through the hidden result pointer
struct RbIter57
{
    RbNode57* mpNode;
    explicit RbIter57(RbNode57* p) : mpNode(p) {}
    RbIter57(const RbIter57& o) : mpNode(o.mpNode) {}
};
struct RbTree57 {
    void*   root;       // +0x00 (this+0x04)
    char    pad[0x0c];
    int     count;      // +0x10 (this+0x14)
};
void* __cdecl EAllocNew(int size, const char* file, int flags, int align, void* alloc, int line); // 0x00f473a0
void  __cdecl RBTreeInsert57(void* node, void* parent, void* root, int side);                    // 0x009216a0
struct Wnd;
struct cSPUILayout_s00de_5040 {
    void**   mpVtbl;            // +0x00
    int32_t  mnRefCount;        // +0x04
    uint32_t mHash;             // +0x08
    uint32_t mId;               // +0x0c
    uint32_t mGroup;            // +0x10
    void*    mpCollection;      // +0x14

    bool Init(const wchar_t* pName, uint32_t nId, char bFlag, uint32_t nGroup); // 0x00812160
    Wnd* FindWindowByID(uint32_t nId, char bFlag);                              // 0x008105b0
};
struct cGalaxyGameEntryImpl_s00de_5040 {
    char       mPad00[0x04];
    RbTree57   mTree4;             // +0x04
    char       mPad18[0x38 - 0x18];
    RbFind56   mRb38;              // +0x38
    char       mPad44[0x100 - 0x44];
    char       mb100;              // +0x100  galaxy shown
    char       mPad101[0x103 - 0x101];
    char       mb103;              // +0x103
    char       mPad104[0x10c - 0x104];
    int        mCurrentDword;      // +0x10c
    char*      mBegin;             // +0x110
    char*      mEnd;               // +0x114
    char       mPad118[0x144 - 0x118];
    cSPUILayout_s00de_5040 mLayout144;        // +0x144
    void*      mpManager;          // +0x15c  cGalaxyManager*
    GalaxyHandleSlot mHandle160;   // +0x160
    GalaxyHandleSlot mHandle164;   // +0x164
    char       mPad168[0x16c - 0x168];
    GalaxyHandleSlot mHandle16c;   // +0x16c
    GalaxyHandleSlot mHandle170;   // +0x170
    void*      mpHandleA;          // +0x174
    char       mPad178[0x184 - 0x178];
    void*      mpGlobalUI;         // +0x184  cSPUIGlobalUI*
    char       mPad188[0x194 - 0x188];
    float      mf194;              // +0x194  minimum login-button width
    char       mPad198[0x1a0 - 0x198];
    GalaxyHandleSlot mHandle1a0;   // +0x1a0
    char       mPad1a4[0x1b0 - 0x1a4];
    void*      mpHandleB;          // +0x1b0
    char       mPad1b4[0x1f5 - 0x1b4];
    char       mFlag1f5;           // +0x1f5
    char       mPad1f6[0x254 - 0x1f6];
    RBTreeThing mRbTree;           // +0x254
    char       mPad260[0x271 - 0x260];
    char       mb271;              // +0x271  network-activity indicator preference

    void  UpdateLoginButton(char param2);  // 0x00de5040
    void  FUN_00de5260(void);           // 0x00de5260
    void  FUN_00de52d0(void);           // 0x00de52d0
    void  FUN_00de5300(void);           // 0x00de5300
    void  FUN_00de5330(char p);         // 0x00de5330
    void  FUN_00de53d0(char p);         // 0x00de53d0
    void  ShowGalaxy(char param2);      // 0x00de5470
    OutKey3* FUN_00de56f0(OutKey3& pOut, KeyNode* key); // 0x00de56f0
    RbIter57 FUN_00de57b0(RbNode57* parent, Key2* key, char flag); // 0x00de57b0
    void  FUN_00de4910(void);           // 0x00de4910
    void  FUN_00de41b0(void);           // 0x00de41b0
    void  FUN_00de5950(void);           // 0x00de5950
    bool  FUN_00de5cb0(unsigned int a); // 0x00de5cb0
    void  FUN_00de5d00(void);           // 0x00de5d00
    void  FUN_00de5df0(void);           // 0x00de5df0
};
struct RectF_s00de_5040 {
    float left;      // +0x00
    float top;       // +0x04
    float right;     // +0x08
    float bottom;    // +0x0c
};
struct Wnd {
virtual void  w00();
virtual void  w01();
virtual void  w02();
    virtual void* w03(uint32_t nId);                 // +0x0c  named child
    virtual void* w04();                             // +0x10  owner
virtual void  w05();
virtual void  w06();
virtual void  w07();
virtual void  w08();
virtual void  w09();
virtual void  w10();
virtual void  w11();
virtual void  w12();
virtual void  w13();
    virtual RectF_s00de_5040* w14();                            // +0x38  window area
virtual void  w15();
virtual void  w16();
virtual void  w17();
virtual void  w18();
virtual void  w19();
virtual void  w20();
virtual void  w21();
virtual void  w22();
virtual void  w23();
virtual void  w24();
virtual void  w25();
virtual void  w26();
virtual void  w27();
virtual void  w28();
    virtual void  w29(float fWidth, float fHeight);  // +0x74  set size
    virtual void  w30();
    virtual void  w31(int32_t nA, int32_t nB);       // +0x7c  flag pair
    virtual void  w32(const wchar_t* pText);         // +0x80  set text
virtual void  w33();
virtual void  w34();
virtual void  w35();
virtual void  w36();
virtual void  w37();
virtual void  w38();
virtual void  w39();
virtual void  w40();
virtual void  w41();
virtual void  w42();
virtual void  w43();
virtual void  w44();
virtual void  w45();
virtual void  w46();
virtual void  w47();
virtual void  w48();
virtual void  w49();
virtual void  w50();
virtual void  w51();
virtual void  w52();
virtual void  w53();
virtual void  w54();
virtual void  w55();
    virtual void  w56(void* pObject);                // +0xe0  attach
virtual void  w57();
virtual void  w58();
virtual void  w59();
virtual void  w60();
virtual void  w61();
virtual void  w62();
virtual void  w63();
virtual void  w64();
    virtual void  w65(void* pProc);                  // +0x104 add window proc
};
struct cAuth {
virtual void a00();
virtual void a01();
virtual void a02();
virtual void a03();
virtual void a04();
virtual void a05();
virtual void a06();
virtual void a07();
    virtual void a08();
    virtual bool a09();                              // +0x24
virtual void a10();
virtual void a11();
virtual void a12();
virtual void a13();
    virtual const wchar_t* a14();                    // +0x38  account name
virtual void a15();
virtual void a16();
virtual void a17();
virtual void a18();
virtual void a19();
virtual void a20();
virtual void a21();
    virtual bool a22();                              // +0x58  logged in
};
struct ResKey {
    uint32_t mHash;          // +0x00
    uint32_t mId;            // +0x04
    uint32_t mGroup;         // +0x08
};
struct cGlobalUI {
    virtual void g00();                              // +0x00
    virtual void g04();                              // +0x04
    virtual bool g08(const ResKey* pKey);            // +0x08  load layout
virtual void g0c();
virtual void g10();
virtual void g14();
virtual void g18();
    virtual void g1c();

    cGlobalUI* Construct();                          // 0x00e03ab0
    Wnd* FindWindowByID(uint32_t nId);               // 0x00e012b0
};
struct WString16_s00de_5040 {
    wchar_t* mpBegin;        // +0x00
    wchar_t* mpEnd;          // +0x04
    wchar_t* mpCapacity;     // +0x08
    uint32_t mPad0c;
    uint32_t mPad10;
    void DeallocateSelf();                           // 0x00933960
};
inline const float* MaxPtr(const float* a, const float* b) { return (*a < *b) ? b : a; }
struct cString47a0 {
    uint32_t m00, m04, m08, m0c;
    void          ctor();                            // 0x006b5060
    void          dtor();                            // 0x006b5240
    bool          Load(uint32_t a, uint32_t b, const wchar_t* pText);  // 0x006b54b0
    const wchar_t* GetText();                        // 0x006b55c0
};
cAuth* __cdecl PollenAuthManager(void);                                    // 0x00607a60
void   __cdecl ConvertToString16(WString16_s00de_5040* pOut, const wchar_t* pText);   // 0x0093c6d0
void   __cdecl AutoSizeWindowForText(Wnd* pWnd, int nA, int nB);           // 0x00806e40
struct cGameEntryOwner {
    void FUN_00df9510(void);        // 0x00df9510
};
cGameEntryOwner* __cdecl FUN_00df5f40_s00de_5040(void);   // 0x00df5f40
struct IWinProc { virtual void w00(); virtual void w04(); virtual void w08(); };
union VariantPayload {
    uint8_t  mbValue;            // +0x00  inline bool
    void*    mpData;             // +0x00  indirect payload
};
struct cVariant_s00de_5040 {
    VariantPayload mValue;       // +0x00
    uint32_t mPad04;             // +0x04
    uint32_t mPad08;             // +0x08
    uint32_t mPad0c;             // +0x0c
    uint16_t mnFlags10;          // +0x10
    uint16_t mnTypeId12;         // +0x12

    void   SetBool(bool bValue) { mValue.mbValue = bValue; mnTypeId12 = 1; mnFlags10 = 0; }
    // the bool is stored inline unless the flags say the payload is indirect
    uint8_t GetBool() { return (mnFlags10 & 0x30) ? *(uint8_t*)mValue.mpData : mValue.mbValue; }
    void   Destruct(int32_t nFlags);                 // 0x0093db80
};
struct cPropertyList_s00de_5040 {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
    virtual void v10();
    virtual void v14(uint32_t nKey, cVariant_s00de_5040* pValue);          // +0x14
virtual void* v18();
virtual void* v1c();
virtual void* v20();
    virtual bool v24(uint32_t nKey, cVariant_s00de_5040** ppValue);        // +0x24
};
extern cPropertyList_s00de_5040* g_pAppPreferences_s00de_5040;             // 0x015fd91c
inline bool GetBoolProperty_s00de_5040(cPropertyList_s00de_5040* pPrefs, uint32_t nKey, uint8_t* pValue)
{
    if (pPrefs == 0)
        return false;
    cVariant_s00de_5040* pVar;
    if (!pPrefs->v24(nKey, &pVar))
        return false;
    if (pVar->mnTypeId12 != 1)
        return false;
    *pValue = pVar->GetBool();
    return true;
}
struct NetworkActivityProc {
    NetworkActivityProc* Ctor();                     // 0x00e01690 (returns its this)
};
struct cWindowManager_s00de_5040 {
    virtual void* w04();                             // +0x04
virtual void  w08();
virtual void  w0c();
virtual void  w10();
virtual void  w14();
virtual void  w18();
virtual void  w1c();
virtual void  w20();
virtual void  w24();
virtual void  w28();
virtual void  w2c();
virtual void  w30();
virtual void  w34();
virtual void  w38();
virtual void  w3c();
virtual void  w40();
virtual void  w44();
    virtual void  w48();
    virtual void  w4c(int32_t nMode, void* pArg);    // +0x4c
};
struct cAppSystem_s00de_5040 {
virtual void* a00();
virtual void* a04();
virtual void* a08();
virtual void* a0c();
virtual void* a10();
virtual void* a14();
virtual void* a18();
virtual void* a1c();
virtual void* a20();
virtual void* a24();
virtual void* a28();
virtual void* a2c();
virtual void* a30();
virtual void* a34();
virtual void* a38();
virtual void* a3c();
virtual void* a40();
virtual void* a44();
virtual void* a48();
virtual void* a4c();
    virtual void* a50();
    virtual bool  a54();                             // +0x54
};
cWindowManager_s00de_5040* __cdecl WindowManager_s00de_5040(void);         // 0x0067caa0
cAppSystem_s00de_5040*     __cdecl AppSystem_s00de_5040(void);             // 0x0067dd00
bool     __cdecl IsWorldLayoutFlagSet(uint32_t nFlag);          // 0x00685520
uint32_t __cdecl FNV1_String16(uint32_t nBasis, const wchar_t* pText, int nMode); // 0x00932f30
void     __cdecl SP_SaveResource(cPropertyList_s00de_5040* pPrefs, void* pArea);             // 0x006b1d50
void*    __cdecl SP_GetSaveArea(uint32_t nId, int32_t nFlags);                    // 0x006b1f90
struct GuiHandle {
    virtual void h00();
    virtual void h04();          // +0x04  release
    virtual void h08();
    virtual void h0c(int a);     // +0x0c  stop
};
struct RefObj2 {
    virtual void r00();
    virtual void r04();          // +0x04  add reference
    virtual void r08();          // +0x08  destroy
};
struct PanelReq {
    uint32_t m00;                // +0x00
    uint32_t m04;                // +0x04
    uint32_t m08;                // +0x08
    uint32_t m0c;                // +0x0c
    uint8_t  m10;                // +0x10
    uint8_t  mPad11[7];
    uint32_t m18;                // +0x18
    uint32_t m1c;                // +0x1c
    uint32_t m20;                // +0x20
    uint8_t  m24;                // +0x24
    uint8_t  mPad25[0xb];
    uint32_t m30;                // +0x30
    uint32_t m34;                // +0x34
    uint32_t m38;                // +0x38
    uint32_t m3c;                // +0x3c
    RefObj2* mpRef;              // +0x40
    uint32_t m44;                // +0x44

    void __thiscall Ctor(void);  // 0x00644b10
    void __thiscall Dtor(void);  // 0x00644b60
};
struct GuiPanelMgr {
    char       mPad000[0x1b0];
    GuiHandle* mpHandle;         // +0x1b0
    char       mPad1b4[0x24c - 0x1b4];
    uint8_t    mbDirty;          // +0x24c
};
extern GuiPanelMgr* gGuiPanelMgr;                        // 0x016a1344
void __cdecl LaunchPanel(const PanelReq* pReq);          // 0x0064a990
struct HashNode8 {
    uint32_t   mKey;             // +0x00
    HashNode8* mpNext;           // +0x04
};
struct InsertResult8 {
    HashNode8* mpNode;           // +0x00
    void*      mpBucket;         // +0x04
    uint8_t    mbInserted;       // +0x08
};
struct RehashInfo {
    uint8_t  mbNeedsRehash;      // +0x00
    uint8_t  mPad01[3];
    uint32_t mCount;             // +0x04
};
struct RehashPolicy {
    void GetNextRehashInfo(RehashInfo* pOut, uint32_t nBuckets, uint32_t nSize,
                           uint32_t nMinBuckets);                    // 0x00921440
};
struct HashTable34 {
    char        mPad00[4];
    HashNode8** mppBuckets;      // +0x04
    uint32_t    mBucketCount;    // +0x08
    uint32_t    mSize;           // +0x0c
    RehashPolicy mPolicy;        // +0x10

    void DoRehash(uint32_t nCount);                                  // 0x00c764f0
    // retail leaves the result pointer in eax and pops three argument dwords (`ret 0xc`),
    // so the helper returns the result pointer and takes an extra trailing argument.
    InsertResult8* FUN_00de5df0(InsertResult8* pOut, const uint32_t* pKey, uint32_t nReserved); // 0x00de5df0
};
// ---- items of slice s00de5040 end

// ---- items of slice s00de9a00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t g_nSavedGameLimit;      // 0x016a1088 number of games to keep
extern uint32_t g_gameFlags[8];         // 0x016a1848 bit set of live game entries
extern uint8_t* g_pPanelIDs;            // 0x016a1344 the global UI panel block
extern void*    g_pAppPreferences;      // 0x015fd91c the app's preference list
extern uint8_t  g_cDefaultChar;         // 0x015d9c70 fallback byte for unknown value types
extern uint8_t  g_bGalaxyIntroA;        // 0x016a0e08
extern uint8_t  g_bGalaxyIntroB;        // 0x016a0e18
extern void*    g_pGameGlobals;         // 0x016c7aa4
template <class T> const T& MinRef(const T& a, const T& b)
{
    return a < b ? a : b;
}
void*    __cdecl AppSystem();                                       // 0x0067dd00
void*    __cdecl CheatManager();                                    // 0x0067de20
void*    __stdcall StarManager(uint32_t nKey);                      // 0x00b3d2a0
void*    __cdecl ObjectTemplateDB_s00de_9a00();                                // 0x0067cb40
void*    __cdecl AuthManager();                                     // 0x00607a60
void*    __cdecl GameTimeManager();                                 // 0x00b3d380
void*    __cdecl GameInputManager();                                // 0x00b3d250
void*    __cdecl FUN_00b3d360();                                    // 0x00b3d360
void*    __stdcall FUN_00b3d410(uint32_t nA, uint32_t nB, uint32_t nC); // 0x00b3d410
void*    __cdecl FUN_0067dd20();                                    // 0x0067dd20
void*    __stdcall FUN_00dd9190(uint32_t nKind);                    // 0x00dd9190
uint32_t __cdecl GetRecorderState();                                // 0x00435e90
void     __cdecl FUN_00de3e40(uint32_t nId);                        // 0x00de3e40
void     __cdecl FUN_00dde570(void* pObject);                       // 0x00dde570

uint8_t* __cdecl FUN_004e42a0(void** ppValue);                      // 0x004e42a0
void __cdecl Launch(uint32_t nId, uint32_t nA, uint32_t nB);                // 0x0064bc50
bool __cdecl GetBoolProperty(void* pList, uint32_t nKey, uint8_t* pValue);  // 0x00407190
void __cdecl SP_SaveResource(void* pList, void* pSaveArea);                 // 0x006b1d50
void* __cdecl SP_GetSaveArea(uint32_t nId, int32_t nFlag);                  // 0x006b1f90
class tIWindow {
public:
    virtual void* v00();                        // +0x00
    virtual void* v04();                        // +0x04
    virtual void* v08();                        // +0x08
    virtual void* v0c(uint32_t nKey);           // +0x0c
    virtual void* v10();                        // +0x10
    virtual void* v14();                        // +0x14
    virtual void* v18();                        // +0x18
    virtual void* v1c();                        // +0x1c
    virtual void* v20();                        // +0x20
    virtual void* v24();                        // +0x24
    virtual void* v28();                        // +0x28
    virtual void* v2c();                        // +0x2c
    virtual void* v30();                        // +0x30
    virtual void* v34();                        // +0x34
    virtual void* v38();                        // +0x38
    virtual void* v3c();                        // +0x3c
    virtual void* v40();                        // +0x40
    virtual void* v44();                        // +0x44
    virtual void* v48();                        // +0x48
    virtual void* v4c();                        // +0x4c
    virtual void* v50();                        // +0x50
    virtual void* v54();                        // +0x54
    virtual void* v58();                        // +0x58
    virtual void* v5c();                        // +0x5c
    virtual void* v60();                        // +0x60
    virtual void* v64();                        // +0x64
    virtual void* v68();                        // +0x68
    virtual void* v6c();                        // +0x6c
    virtual void* v70();                        // +0x70
    virtual void* v74();                        // +0x74
    virtual void* v78();                        // +0x78
    virtual void  v7c(int32_t nA, int32_t nB);  // +0x7c visible/state pair
};
class cSPUILayout_s00de_9a00 {
public:
    uint32_t  mPad00[13];                                           // +0x000
    tIWindow* FindWindowByID(uint32_t nID, int32_t nFlag);          // 0x008105b0
    void      SetVisibility(int32_t nFlag);                         // 0x00810590
    void      Shutdown(uint32_t nFlag);                             // 0x00811ad0
};
class tRefObj {
public:
    virtual void* v00();                        // +0x00
    virtual void* v04();                        // +0x04
    virtual void* v08();                        // +0x08 Release
    virtual void* v0c();                        // +0x0c
    virtual void* v10();                        // +0x10
    virtual void* v14();                        // +0x14
    virtual void* v18();                        // +0x18
    virtual void* v1c();                        // +0x1c
    virtual void* v20();                        // +0x20
    virtual void* v24();                        // +0x24
    virtual void* v28();                        // +0x28
    virtual void* v2c();                        // +0x2c
    virtual void* v30();                        // +0x30
    virtual void* v34();                        // +0x34
    virtual void* v38();                        // +0x38
    virtual void* v3c();                        // +0x3c
    virtual void* v40();                        // +0x40
};
class cIEffectsWorld {
public:
    virtual void* v00();                        // +0x00
    virtual void* v04();                        // +0x04
    virtual void* v08();                        // +0x08
    virtual void* v0c();                        // +0x0c
    virtual void* v10();                        // +0x10
    virtual void* v14();                        // +0x14
    virtual void* v18();                        // +0x18
    virtual void* v1c();                        // +0x1c
    virtual void* v20();                        // +0x20
    virtual void* v24();                        // +0x24
    virtual void* v28();                        // +0x28
    virtual void* v2c();                        // +0x2c
    virtual void* v30();                        // +0x30
    virtual void* v34();                        // +0x34
    virtual void* v38();                        // +0x38
    virtual void* v3c();                        // +0x3c
    virtual void* v40();                        // +0x40
    virtual void* v44();                        // +0x44
    virtual void  v48(void* pEffect);           // +0x48
    virtual void  v4c();                        // +0x4c
};
class cMessageBody {
public:
    virtual void*    v00();                     // +0x00
    virtual void*    v04();                     // +0x04
    virtual void*    v08();                     // +0x08
    virtual void*    v0c();                     // +0x0c
    virtual void*    v10();                     // +0x10
    virtual void*    v14();                     // +0x14
    virtual void*    v18();                     // +0x18
    virtual uint32_t v1c();                     // +0x1c the message key
};
class cUIMessage {
public:
    cMessageBody* mp00;                         // +0x00
    uint32_t      mn04;                         // +0x04
    uint32_t      mn08;                         // +0x08 message id
};
class cUIObject {
public:
    virtual void*    v00();                                 // +0x00
    virtual void*    v04();                                 // +0x04
    virtual void*    v08();                                 // +0x08
    virtual void*    v0c();                                 // +0x0c
    virtual void*    v10();                                 // +0x10
    virtual void*    v14(uint32_t nKey, void* pValue);      // +0x14
    virtual void*    v18(uint32_t nA, uint32_t nB, uint32_t nC, uint32_t nD); // +0x18
    virtual void*    v1c();                                 // +0x1c
    virtual void*    v20(void* pListener, uint32_t nTag);   // +0x20
    virtual void*    v24();                                 // +0x24
    virtual void*    v28(int32_t nState);                   // +0x28
    virtual void*    v2c(void* pSender, uint32_t nTag, int32_t nData); // +0x2c
    virtual void*    v30();                                 // +0x30
    virtual void*    v34();                                 // +0x34
    virtual void*    v38(void* pOut, void* pIn);            // +0x38
    virtual void*    v3c();                                 // +0x3c
    virtual void*    v40();                                 // +0x40
    virtual void*    v44();                                 // +0x44
    virtual void*    v48();                                 // +0x48
    virtual void*    v4c(int32_t nFlag);                    // +0x4c
    virtual void*    v50();                                 // +0x50
    virtual bool     v54();                                 // +0x54
    virtual void*    v58();                                 // +0x58
    virtual void*    v5c();                                 // +0x5c
    virtual void     v60(uint32_t nA, uint32_t nB);         // +0x60

    bool FUN_00ec4320();                                    // 0x00ec4320
};
class cUIMessageRouter {
public:
    virtual void*    v00();                                 // +0x00
    virtual void*    v04();                                 // +0x04
    virtual void*    v08();                                 // +0x08
    virtual void*    v0c();                                 // +0x0c
    virtual void*    v10();                                 // +0x10
    virtual void*    v14(uint32_t nKey, void* pValue);      // +0x14
    virtual void*    v18(uint32_t nA, uint32_t nB, uint32_t nC, uint32_t nD); // +0x18
    virtual void*    v1c();                                 // +0x1c
    virtual void*    v20(void* pListener, uint32_t nTag);   // +0x20
    virtual void*    v24();                                 // +0x24
    virtual void*    v28(int32_t nState);                   // +0x28
    virtual void*    v2c(void* pSender, uint32_t nTag, int32_t nData); // +0x2c
    virtual void*    v30();                                 // +0x30
    virtual void*    v34();                                 // +0x34
    virtual void*    v38(void* pOut, void* pIn);            // +0x38
    virtual void*    v3c();                                 // +0x3c
    virtual void*    v40();                                 // +0x40
    virtual void*    v44();                                 // +0x44
    virtual void*    v48();                                 // +0x48
    virtual void*    v4c(int32_t nFlag);                    // +0x4c
    virtual void*    v50();                                 // +0x50
    virtual bool     v54();                                 // +0x54
    virtual void     v58(uint32_t nArg, cUIMessage* pMsg);  // +0x58
    void FUN_00e00670(uint32_t nA, uint32_t nB);            // 0x00e00670
};
class cSaveGameUI : public cUIObject {
public:
    void GetSavedGames(void* pBegin, uint32_t nCount);      // 0x00df7f60
};
class cRecorderUI : public cUIObject {
public:
    uint32_t FUN_00df66e0();                                // 0x00df66e0
};
class cEffectHandle {
public:
    void FUN_00e3e350();                                    // 0x00e3e350
};
class cMovieSystem_s00de_9a00 {
public:
    virtual void* v00();                        // +0x00
    virtual void* v04();                        // +0x04
    virtual void* v08();                        // +0x08
    virtual void* v0c();                        // +0x0c
    virtual void* v10();                        // +0x10
    virtual bool v14();                         // +0x14
    virtual void* v18();                        // +0x18
    virtual void* v1c();                        // +0x1c
    virtual void* v20();                        // +0x20
    virtual bool v24();                         // +0x24
};
class cGameTime : public cUIObject {
public:
    void FUN_00b32110();                                    // 0x00b32110
};
class cGameInput {
public:
    uint32_t mPad00[0x110 / 4];                             // +0x000
    uint32_t mn110;                                         // +0x110
};
class cGameGlobalsRoot {
public:
    uint32_t   mPad00[7];                       // +0x00
    cUIObject* mp1c;                            // +0x1c
};
class cMsgHandler {
public:
    uint32_t mPad00[2];                         // +0x00
};
class cGameInfoVector;
struct tScratchQuad {
    uint32_t mn00;                              // +0x00
    uint32_t mn04;                              // +0x04
    uint32_t mn08;                              // +0x08
    uint32_t mn0c;                              // +0x0c
};
class cByteVector {
public:
    tScratchQuad mPad000;                       // +0x000 .. +0x00f
    tScratchQuad mPad010;                       // +0x010 .. +0x01f
    tScratchQuad mPad020;                       // +0x020 .. +0x02f
    tScratchQuad mPad030;                       // +0x030 .. +0x03f
    tScratchQuad mPad040;                       // +0x040 .. +0x04f
    tScratchQuad mPad050;                       // +0x050 .. +0x05f
    tScratchQuad mPad060;                       // +0x060 .. +0x06f
    tScratchQuad mPad070;                       // +0x070 .. +0x07f
    tScratchQuad mPad080;                       // +0x080 .. +0x08f
    tScratchQuad mPad090;                       // +0x090 .. +0x09f
    tScratchQuad mPad0a0;                       // +0x0a0 .. +0x0af
    uint32_t     mPad0b0;                       // +0x0b0
    uint32_t     mPad0b4;                       // +0x0b4
    uint32_t     mPad0b8;                       // +0x0b8

    cByteVector();                              // 0x00b26d00
    ~cByteVector();                             // 0x00b26db0
};
class cGameInfoVector {
public:
    uint8_t* mpBegin;                           // +0x00
    uint8_t* mpEnd;                             // +0x04
    uint8_t* mpCapacity;                        // +0x08

    void FUN_00de97a0(void* pBegin, void* pEnd);                            // 0x00de97a0
    void FUN_00de97f0(void* pEnd, uint32_t nCount, const cByteVector& scratch); // 0x00de97f0
    void FUN_00de5ee0(void* pBegin, void* pEnd);                            // 0x00de5ee0
    void FUN_00de9e20(uint32_t nCount);                                     // 0x00de9e20
};
class cSavedGameEntry {
public:
    void FUN_00ddc820();                        // 0x00ddc820
    void FUN_00ddb9f0();                        // 0x00ddb9f0
};
class cStarManager {
public:
    uint32_t FUN_00ba6d80();                    // 0x00ba6d80
};
class cGameInfoKey {
public:
    uint32_t mn00;                              // +0x00 the star-system id
    uint32_t mPad04[10];                        // +0x04 .. +0x2b
    uint32_t mn2c;                              // +0x2c non-zero when the system has content
};
class cGameInfo_s00de_9a00 {
public:
    uint32_t     mn00;                          // +0x000
    uint32_t     mPad04[0x78 / 4];              // +0x004
    cGameInfoKey mKey7c;                        // +0x07c (0x30 bytes)
    uint32_t     mPadAc[4];                     // +0x0ac
};
class cAssetBrowser;
class cPosseWatcher;
class cAssetBrowser {
public:
    uint32_t          mPad00[13];               // +0x000
    cUIMessageRouter* mp34;                     // +0x034
    uint32_t          mPad38[51];               // +0x038 .. +0x103
    int32_t           mn104;                    // +0x104
    int32_t           mn108;                    // +0x108
    uint32_t          mPad10c[13];              // +0x10c .. +0x13f
    cSPUILayout_s00de_9a00       mLayout140;               // +0x140
    void*             mp174;                    // +0x174
    uint32_t          mPad178[7];               // +0x178 .. +0x193
    cPosseWatcher*    mp194;                    // +0x194

    bool FUN_00de9a00(uint32_t nArg, cUIMessage* pMsg);         // 0x00de9a00
};
class cPosseWatcher {
public:
    void FUN_00dde570();                        // 0x00dde570
};
class cAssetBrowserHost {
public:
    uint32_t      mPad00;                       // +0x00
    cAssetBrowser mBrowser;                     // +0x04

    void FUN_00de52d0();                        // 0x00de52d0
};
class cKeyTree {
public:
    void*   mp00;                               // +0x00
    void*   mp04;                               // +0x04 end node
    void**  Find(void** ppOut, const void* pKey);   // 0x00a21dc0
};
class cRecordMap {
public:
    uint32_t mPad00[14];                        // +0x00 .. +0x37
    cKeyTree mTree38;                           // +0x38

    void FUN_00de9600(const void* pKey);                        // 0x00de9600
    void FUN_00de9dc0(const void* nKey);                        // 0x00de9dc0
    void FUN_00de6f20(uint32_t nKey, void* pValue);             // 0x00de6f20
    void FUN_00de7010();                                        // 0x00de7010
    void FUN_00de9fc0();                                        // 0x00de9fc0
};
class cVisitNode {
public:
    uint32_t  mPad00[5];                        // +0x00
    tRefObj*  mp14;                             // +0x14
};
class cGalaxyGameEntryImpl_s00de_9a00 {
public:
    uint32_t    mPad00[2];                      // +0x000
    cMsgHandler mHandler08;                     // +0x008 the handler registered with the message server
    uint32_t    mPad10[10];                     // +0x010 .. +0x037
    cIEffectsWorld* mp38;                       // +0x038
    cRecordMap  mRecords3c;                     // +0x03c (0x40 bytes)
    uint8_t     mPad7c[0x4d];                   // +0x07c .. +0x0c8
    uint8_t     mb0c9;                          // +0x0c9
    uint8_t     mPad0ca[0x3e];                  // +0x0ca .. +0x107
    int32_t     mn108;                          // +0x108
    int32_t     mn10c;                          // +0x10c
    uint32_t    mPad110[6];                     // +0x110 .. +0x127
    void*       mp128;                          // +0x128 the tree's root node
    void*       mp12c;                          // +0x12c the tree's first node
    uint32_t    mPad130[4];                     // +0x130 .. +0x13f
    uint8_t     mb140;                          // +0x140
    uint8_t     mPad141[0xb5];                  // +0x141 .. +0x1f5
    uint8_t     mb1f6;                          // +0x1f6
    uint8_t     mPad1f7[0x55];                  // +0x1f7 .. +0x24b
    uint8_t     mb24c;                          // +0x24c
    uint8_t     mb24d;                          // +0x24d
    uint8_t     mPad24e[2];                     // +0x24e .. +0x24f
    tRefObj*    mp250;                          // +0x250

    void OnActivate();                          // 0x00de4720
    void FUN_00de5950();                        // 0x00de5950
    void ShowGalaxy(int32_t nFlag);             // 0x00de5470
    bool FUN_00dea200();                        // 0x00dea200
    void FUN_00dea420();                        // 0x00dea420
};
class cConstraint {
public:
    uint32_t mPad00[9];                         // +0x00 (0x24 bytes)

    cConstraint(uint32_t nId, int32_t nKind, int32_t nValue);   // 0x00558960
    void FUN_00606880(const cConstraint* pOther);               // 0x00606880
};
class cConstraintList {
public:
    cConstraint* mpBegin;                       // +0x00
    cConstraint* mpEnd;                         // +0x04
    cConstraint* mpCapacity;                    // +0x08

    void DoInsertValue(cConstraint* pEnd, cConstraint* pValue);     // 0x004e39d0
    void DoDestroyValues(cConstraint* pBegin, cConstraint* pEnd);  // 0x004e39a0
};
class cKeyList {
public:
    void* mpBegin;                              // +0x00
    void* mpEnd;                                // +0x04
    void* mpCapacity;                           // +0x08

    void DoDestroyValues(void* pBegin, void* pEnd);             // 0x004e39a0
};
struct tResourceKey {
    uint32_t mn00;                              // +0x00
    uint32_t mn04;                              // +0x04
    uint32_t mn08;                              // +0x08
};
class cVariant {
public:
    uint32_t mPad00[4];                         // +0x00
    uint32_t mnFlags10;                         // +0x10

    void FUN_005dd750(uint32_t* pOut);          // 0x005dd750
    void Destruct(int32_t nFlag);               // 0x0093db80
};
class cPropertyList {
public:
    virtual void* v00();                        // +0x00
    virtual void* v04();                        // +0x04
    virtual void* v08();                        // +0x08
    virtual void* v0c();                        // +0x0c
    virtual void* v10();                        // +0x10
    virtual void* v14(uint32_t nKey, cVariant* pValue);  // +0x14
    int32_t GetModificationCount();                       // 0x006237a0
};
class cProperty {
public:
    virtual void* v00();                        // +0x00
    virtual void* v04();                        // +0x04
    virtual void* v08();                        // +0x08
    virtual void* v0c();                        // +0x0c
    virtual void* v10();                        // +0x10
    virtual void* v14();                        // +0x14
    virtual void* v18();                        // +0x18
    virtual void* v1c();                        // +0x1c
    virtual void* v20();                        // +0x20
    virtual bool  v24(uint32_t nKey, void** ppValue);       // +0x24
};
class cVariantValue {
public:
    uint8_t* mp00;                              // +0x00
    uint32_t mPad04[3];                         // +0x004
    uint8_t  mb10;                              // +0x010
    uint8_t  mPad11;                            // +0x011
    uint16_t mn12;                              // +0x012
};
class cSavedGameRecord {
public:
    uint32_t        mp00;                       // +0x000
    uint32_t        mPad04[0x2c / 4];           // +0x004
    cPropertyList*  mp30;                       // +0x030
    uint32_t        mn34;                       // +0x034
};
class cValueObject {
public:
    uint8_t* FUN_004e42a0();                    // 0x004e42a0
};
class cWatcherBase {
public:
    uint8_t     mb00;                           // +0x000
    uint8_t     mPad01[3];                      // +0x001
    void*       mp04;                           // +0x004 the watched record
    uint32_t    mn08;                           // +0x008
    int32_t     mn0c;                           // +0x00c last observed modification count

    bool FUN_00dea730();                        // 0x00dea730
    void FUN_00dea7b0(cProperty* pProperty);    // 0x00dea7b0
};
class cPaintBaseA {
public:
    virtual void* v00();                        // +0x000
    uint32_t      mn04;                         // +0x004

    cPaintBaseA();                              // 0x00e00630
};
class cPaintBaseB {
public:
    virtual void* v08();                        // +0x008
    uint8_t  mb0c;                              // +0x00c
    uint8_t  mb0d;                              // +0x00d
    uint8_t  mb0e;                              // +0x00e
    uint8_t  mb0f;                              // +0x00f
    uint8_t  mb10;                              // +0x010
    uint8_t  mb11;                              // +0x011
    uint8_t  mb12;                              // +0x012
    uint8_t  mPad13;                            // +0x013

    cPaintBaseB() { _ReadWriteBarrier(); ClearState(); }
    void ClearState()
    {
        mb0d = 0;
        mb0e = 0;
        mb0f = 0;
        mb10 = 0;
        mb11 = 0;
        mb12 = 0;
    }
};
class cPaintSystem : public cPaintBaseA, public cPaintBaseB {
public:
    virtual void* v14();                        // the paint system's own vtable entry
    void*    mp14;                              // +0x014
    float    mf18;                              // +0x018
    float    mf1c;                              // +0x01c
    float    mf20;                              // +0x020
    uint8_t  mb24;                              // +0x024
    uint8_t  mPad25[3];                         // +0x025
    int32_t  mn28;                              // +0x028

    cPaintSystem();                             // 0x00dea500
    void FUN_00e00650(uint32_t nId, uint32_t nData);            // 0x00e00650
    void FUN_00dea560();                                        // 0x00dea560
    void FUN_00dea600(uint32_t nId, uint32_t nData);            // 0x00dea600
};
class cPanelIDs_s00de_9a00 {
public:
    uint8_t     mPad000[0x144];                 // +0x000
    cSPUILayout_s00de_9a00 mLayout144;                     // +0x144 (0x34 bytes)
    uint32_t    mPad178[0x74 / 4];              // +0x178 .. +0x1eb
    int32_t     mn1ec;                          // +0x1ec
    uint8_t     mPad1f0[2];                     // +0x1f0 .. +0x1f1
    uint8_t     mb1f2;                          // +0x1f2
    uint8_t     mb1f3;                          // +0x1f3
    uint8_t     mb1f4;                          // +0x1f4
    uint8_t     mPad1f5[3];                     // +0x1f5
    uint32_t    mPad1f8[4];                     // +0x1f8 .. +0x207
    float       mf208;                          // +0x208
    float       mf20c;                          // +0x20c
};
static void AddConstraint(cConstraintList* pList, uint32_t nId, int32_t nValue)
{
    cConstraint c(nId, 0, nValue);
    if (pList->mpEnd < pList->mpCapacity)
    {
        cConstraint* pSlot = pList->mpEnd;
        pList->mpEnd = pList->mpEnd + 1;
        if (pSlot != 0)
            pSlot->FUN_00606880(&c);
    }
    else
    {
        pList->DoInsertValue(pList->mpEnd, &c);
    }
}
// ---- items of slice s00de9a00 end

// ---- items of slice s00dea870 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const uint32_t* const g_kPanelIDs;              // 0x016a1344
extern uint32_t DAT_01654c01;
extern uint32_t DAT_01654c02;
extern uint32_t DAT_01654c04;
extern uint32_t DAT_01654c05;
extern int g_vtbl_GalaxyGameEntryDeb;   // 0x0147dba8
struct LocInfo { uint32_t mData[3]; };
struct LocBuf  { wchar_t mName[64]; uint16_t mTail; };
class cIVisualEffect {
public:
    virtual void vf0();                                        // +0x00
    virtual void AddRef();                                     // +0x04
    virtual void Release();                                    // +0x08
    virtual void Tick(int);                                    // +0x0c
    virtual bool Find(uint32_t id, void* out, int b, int c, int d); // +0x10
};
class cEffectsWorldSub {
public:
virtual void v0();
virtual void v1();
virtual void v2();
    virtual bool Find(uint32_t id, void* out, int a, int b, int c, int d); // +0x0c
    virtual bool Find2(uint32_t id, void* out);                            // +0x10
    virtual bool Find3(uint32_t id, void* out);                            // +0x14
virtual void v6();
virtual void v7();
virtual void v8();
    virtual bool Find4(uint32_t id, void* out);                            // +0x24
};
class cMovieSystem {
public:
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
    virtual void PlayMovie(void* pEntry, const void* pDesc);   // +0x10
    virtual bool IsMoviePlaying();                             // +0x14
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
    virtual void StopMovies(int);                              // +0x40
};
struct IWindow {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
    virtual void PlayAnim(int a, int b);                       // +0x7c
};
class cSPUILayout_s00de_a870 {
public:
    bool Init(const wchar_t* name, int a, char b, int c, uint32_t d); // 0x00812160
    void SetVisibility(bool v);                                       // 0x00810590
    IWindow* FindWindowByID(uint32_t id, int a);                      // 0x008105b0
};
class cSPUIGlobalUI_s00de_a870 {
public:
    void SetVisibility(bool v);                                       // 0x00e01350
};
class cMessageServer_s00de_a870 {
public:
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
    virtual int SendMessage(uint32_t id, uint32_t type, uint32_t a, uint32_t b); // +0x18
virtual void v7();
virtual void v8();
    virtual int AddHandler(void* obj, uint32_t id);                   // +0x24
};
class DBCheck {
public:
    DBCheck();                                                        // 0x0060b220
    virtual void Prepare();                                           // +0x10
    virtual void Show();                                              // +0x18
};
void* __cdecl EAAllocate(uint32_t size, const char* pFile, int a, int b, int c, int d); // 0x00f473a0
void* __cdecl FUN_0067dcc0();                          // 0x0067dcc0 -> cMessageServer*
void* __cdecl FUN_0067cb10();                          // 0x0067cb10 -> cMovieSystem*
void* __cdecl FUN_0067de20();                          // 0x0067de20 -> CheatManager*
void* __cdecl FUN_0067de30();                          // 0x0067de30 -> PropertyManager*
void* __cdecl FUN_0067de40();                          // 0x0067de40 -> Locale manager*
void* __cdecl FUN_0067dcd0();                          // 0x0067dcd0 -> ResourceMan::GetManager
void* __cdecl FUN_00b3d240();                          // 0x00b3d240
void* __cdecl FUN_00b3d300();                          // 0x00b3d300
void* __stdcall FUN_00b3d410(int a, int* pKey, int b);  // 0x00b3d410 (args ignored; returns mgr)
void* __cdecl FUN_00ad7db0();                          // 0x00ad7db0
char  __fastcall FUN_00ad7e20(void* self);             // 0x00ad7e20
struct ModalShim { void SetModal(int a); };            // 0x00ad7e40  thiscall, ret 4
char  __cdecl FUN_00805180();                          // 0x00805180
void* __cdecl FUN_00401090();                          // 0x00401090
char  __cdecl FUN_00e01380();                          // 0x00e01380
struct TrigMgrShim { void Func(int a, int b); };         // 0x00de86d0  ret 8, this in ecx
void  __cdecl FUN_00dea560();                          // 0x00dea560
void  __cdecl FUN_00dea730();                          // 0x00dea730
void  __fastcall FUN_00dea7b0(void* self, void* list); // 0x00dea7b0  ret 4, self in ecx
void* __cdecl FUN_00e00630_s00de_a870();                          // 0x00e00630
void* __cdecl FUN_0060b3c0();                          // 0x0060b3c0 -> UI::DBCheck*
void  __cdecl FUN_0060b3e0(DBCheck*);                  // 0x0060b3e0
void  __cdecl FUN_00ae0930();                          // 0x00ae0930
char  __cdecl FUN_006ab760(void*, const wchar_t*);     // 0x006ab760
char  __cdecl FUN_0087da90(LocInfo*, const void*);     // 0x0087da90
char  __cdecl FUN_0087e130(const LocInfo*, LocBuf*);   // 0x0087e130
void  __fastcall FUN_005942e0(void* self);             // 0x005942e0
uint32_t __cdecl FUN_004df420(void*);                  // 0x004df420
void  __fastcall FUN_00b33d20(void* self);             // 0x00b33d20 (tail-jumped, this in ecx)
void  __fastcall FUN_00deac20(void* self);             // 0x00deac20
void  __fastcall FUN_00deb0b0(void* self);             // 0x00deb0b0
void  __fastcall FUN_00de95a0(void* self);             // 0x00de95a0
void  __fastcall FUN_00deb4a0(void* self);             // 0x00deb4a0
void  __fastcall FUN_00deb6d0(void* self);             // 0x00deb6d0
void  __fastcall FUN_00deb770(void* self, void* param); // 0x00deb770  ret 4
void* __fastcall FUN_00f67d90(void* self);             // 0x00f67d90
void* __cdecl FUN_00810000_s00de_a870(void* mem);                 // 0x00810000 cConnectionDialog ctor
void  __cdecl FUN_00807bb0(void* wnd, const void* pRect, int a); // 0x00807bb0 SetWindowImage
void  __cdecl FUN_004df310(void* self, const void* key); // 0x004df310
void* __cdecl FUN_0041ea70(void* pProp);               // 0x0041ea70 GetPropertyAsFloat
inline uint32_t& PI(uint32_t off) { return *(uint32_t*)((char*)g_kPanelIDs + off); }
inline uint8_t& PIB(uint32_t off)  { return *(uint8_t*)((char*)g_kPanelIDs + off); }
inline void*&   PIP(uint32_t off)  { return *(void**)((char*)g_kPanelIDs + off); }
struct cGalaxyGameEntryImpl_s00de_a870 {
    virtual void vf0();                                   // +0x00
virtual void vf1();
virtual void vf2();
virtual void vf3();
    char pad[8];                   // +0x04..0x0b
    void* mp0c;                    // +0x0c
    uint8_t mb0d;                  // +0x0d
    uint8_t mb0e;                  // +0x0e
    uint8_t mb0f;                  // +0x0f
    uint8_t mb10;                  // +0x10
    uint8_t mb11;                  // +0x11
    uint8_t mb12;                  // +0x12
    uint8_t mb13;                  // +0x13
    cSPUILayout_s00de_a870* mp14;             // +0x14
    float mf18;                    // +0x18
    float mf1c;                    // +0x1c
    float mf20;                    // +0x20
    uint8_t mb24;                  // +0x24
    char pad25[3];
    uint32_t mu28;                 // +0x28
    char pad2c[0x20];
    uint32_t mKey4c[3];            // +0x4c
    uint32_t mu58;                 // +0x58
};
void cGalaxyGameEntryImpl_PlayOpeningMovie(cGalaxyGameEntryImpl_s00de_a870* self); // 0x00deaad0
class cFxMan {
public:
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
    virtual bool Register(const void* pKey, uint32_t id, void** ppOut); // +0x30
};
class cFxObj {
public:
    virtual void v0();                    // +0x00
    virtual void Release();               // +0x04
    virtual void v2();                    // +0x08
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
    virtual bool GetProp(uint32_t id, void** ppOut);  // +0x24
};
class cRandomLC {
public:
    void SetSeed(uint32_t s);                          // 0x00936090
    uint32_t RandomUint32Uniform(uint32_t n);          // 0x00a68fb0
};
struct MovieDesc {
    uint32_t mId;      // +0x00
    float    mF0;      // +0x04
    float    mF1;      // +0x08
    float    mF2;      // +0x0c
    float    mF3;      // +0x10
    uint8_t  mB0;      // +0x14
    uint8_t  mB1;      // +0x15
};
struct AppPropsList {
    virtual void vf0();                 // +0x00
    virtual void Release();             // +0x04
};
struct FlagPair {
    uint8_t  mFlag;      // +0x00
    char     pad1[3];
    void*    mp04;       // +0x04
    uint32_t mId08;      // +0x08
    uint32_t mId0c;      // +0x0c
};
struct SetWindowImageFn { void* a; uint32_t b; uint32_t c; };
struct Screen {
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
    virtual void StopCheats(int);                             // +0x4c
};
class cTriggerReceiver {
public:
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
    void PostTriggerSimple();                                 // 0x00e3e350 thiscall, ret 0xc
};
struct cGalaxyGameEntryDeb {
    void** mpVtbl;                      // 0x00
    void* DestroyDeb(unsigned int flags);  // 0x00deb6a0
};
struct CbInner {
    virtual void v0();
    virtual void Send(uint32_t id, void* p);     // +0x04
};
struct CbObj {
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
    virtual void Stop();                          // +0x50
};
struct ResourceKey3 { uint32_t m[3]; };
struct ResMgr {
virtual void v0();
virtual void v1();
virtual void v2();
    virtual bool FindKey(const ResourceKey3* key, void** ppOut, int a, int b, int c, int d); // +0xc
};
struct PlayerObj {
    char pad[0x10e8];
    void* mpItems;     // +0x10e8
};
struct TerrainObj {
virtual void v0();
virtual void v1();
virtual void v2();
    virtual void UnlockAssociatedParts(void*);                 // +0xc
};
struct CollectItems { void EnsureBaseUnlocks(uint32_t id); };  // 0x00598540
// ---- items of slice s00dea870 end

// ---- items of slice s00deb840 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* vtbl_RefBaseA22[];         // 0x013eb90c
extern void* vtbl_UIBehaviorMessage[];  // 0x013eb844
extern const char gStateNameTable[];            // 0x01654c00
extern const uint32_t kResetWindowIDs[5];       // 0x0147e51c
extern const uint32_t kButtonWindowIDs[6];      // 0x0147e4d8
extern const uint32_t kWindowFlagParam;         // 0x013ec468
extern const float kfZoomDuration;              // 0x015a2df4
extern const wchar_t* const gpSporePathBegin;   // 0x015689a8
extern const uint32_t kAssetKey;                // 0x015a3e90
extern const uint32_t kNotFoundText;            // 0x015a3dc8
extern uint32_t gDeferredWindowMask[];          // 0x016a1848
extern void* gpTestSystem;                      // 0x015fd928
void* operator new(unsigned int size, const char* name, int flags, unsigned int align,
                   const char* file, int line);            // 0x00f473a0
void operator delete[](void* p);                            // 0x00f47380
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8
struct IWindow_s00de_b840 {
    PV8 PV2 PV
    virtual uint32_t GetState();                        // +0x2c
    PV8 PV8 PV2 PV
    virtual void SetFlag(int flag, int value);          // +0x7c
    virtual void SetParam(const void* param);            // +0x80
};
class cSPUILayout_s00de_b840 {
public:
    uint32_t pad[3];
    IWindow_s00de_b840* FindWindowByID(uint32_t id, bool recursive);   // 0x008105b0
    void SetVisibility(bool visible);                       // 0x00810590
};
class cSPUIGlobalUI {
public:
    uint32_t pad[3];
    void SetVisibility(bool visible);                       // 0x00e01350
};
class IRefObj {
public:
    virtual void vf0();                                 // +0x00
    virtual void Release();                             // +0x04
    virtual void SetFlag(int value);                    // +0x08
    virtual IRefObj* vf3(int value);                    // +0x0c
    void Zoom(float seconds);                           // 0x00dde900
};
class IEffectStore {
public:
    virtual void vf0();                                 // +0x00
    virtual void vf1();                                 // +0x04
    virtual void Find(uint32_t id, int flags, IRefObj** out);   // +0x08
};
struct EffectPtrVector {
    IRefObj** mpBegin;      // +0x00
    IRefObj** mpEnd;        // +0x04
    IRefObj** mpCapacity;   // +0x08
    void DoFree(IRefObj** begin, IRefObj** end);        // 0x00533500
};
struct IMessageServer {
    PV4
    virtual void v4();                                       // +0x10
    virtual void Send(uint32_t id, const void* payload, int arg);  // +0x14
    virtual void Send2(uint32_t id, const void* payload, int a, int b); // +0x18
};
class WString {
public:
    WString(const wchar_t* psz, bool* pOk);                 // 0x0041df50
    WString(const wchar_t* psz) : mpBegin(0), mpEnd(0), mpCapacity(0)
    {
        RangeInitialize(psz);                              // 0x00579a90
    }
    WString(const WString& other) : mpBegin(0), mpEnd(0), mpCapacity(0)
    {
        uint32_t count = (uint32_t)(other.mpEnd - other.mpBegin);
        AllocateSelf(count + 1);                           // 0x00429760
        memcpy(mpBegin, other.mpBegin, count * sizeof(wchar_t));
        mpEnd = mpBegin + count;
        *mpEnd = 0;
    }
    ~WString() { DeallocateSelf(); }
    WString& operator=(const WString& other)
    {
        if (this != &other)
            assign(other.mpBegin, other.mpEnd);            // 0x00423650
        return *this;
    }
    void DeallocateSelf()
    {
        if (mpCapacity - mpBegin > 1 && mpBegin)
            ::operator delete[]((char*)mpBegin);
    }
    void AllocateSelf(uint32_t n);                          // 0x00429760
    void RangeInitialize(const wchar_t* psz);               // 0x00579a90
    void assign(const wchar_t* first, const wchar_t* last);  // 0x00423650
    wchar_t* mpBegin;       // +0x00
    wchar_t* mpEnd;         // +0x04
    wchar_t* mpCapacity;    // +0x08
    uint32_t mAllocator;    // +0x0c
};
WString __cdecl PathJoin(const WString& name, const wchar_t* pBase);  // 0x0057cba0
WString __cdecl PathPick(const WString& a, const WString& b);         // 0x00688f00
struct GGEGlobal {
    uint8_t pad000[0xef];
    bool mbEF;                  // +0xef
    uint8_t padF0[4];
    bool mbF4;                  // +0xf4
    uint8_t padF5[0x0b];
    bool mb100;                 // +0x100
    bool mb101;                 // +0x101
    bool mb102;                 // +0x102
    uint8_t pad103;
    uint32_t mu104;             // +0x104
    uint32_t mu108;             // +0x108
    uint32_t mu10c;             // +0x10c
    uint8_t pad110[0x30];
    bool mb140;                 // +0x140
    uint8_t pad141[3];
    cSPUILayout_s00de_b840 mLayout;        // +0x144
    uint8_t pad150[0x0c];
    IEffectStore* mpEffectStore;    // +0x15c
    uint8_t pad160[0x24];
    cSPUIGlobalUI* mpGlobalUI;      // +0x184
    uint8_t pad188[0x10];
    IRefObj* mp198;                 // +0x198 (zoom helper object)
    IRefObj* mp19c;                 // +0x19c
    uint8_t pad1a0;
    IRefObj* mp1a4;                 // +0x1a4
    uint8_t pad1a8[0x30];
    EffectPtrVector mEffects;       // +0x1d8
    uint8_t pad1e4[0x0c];
    bool mb1f0;                     // +0x1f0

    void MoveTo(bool mode);                         // 0x00de53d0
    void NotifyStateChange(int mode, bool flag);    // 0x00de86d0
    void PopModeStack();                            // 0x00de52d0
};
extern GGEGlobal* gpGGE;                            // 0x016a1344
struct cAvatarProfile {
    uint8_t pad000[0x4ec];
    float mf4ec;                // +0x4ec
    float mf4f0;                // +0x4f0
    float mf4f4;                // +0x4f4
};
struct ResourceKey {
    uint32_t mnInstanceID;      // +0x00
    uint32_t mnTypeID;          // +0x04
    uint32_t mnGroupID;         // +0x08
};
struct Vector3 {
    float x, y, z;
};
struct cStarName;
struct cStarRecord {
    uint8_t pad00[0x58];
    uint32_t m58;               // +0x58
    uint8_t pad5c[0x50];
    bool mbAC;                  // +0xac
    uint32_t Get58();                   // 0x00989360
    void Measure(int flags);            // 0x00bbaa80
    cStarName* GetName(int index);      // 0x00bbaa60
    void SetKey(const ResourceKey* pKey);   // 0x00bb9b90
};
struct cStarName {
    uint8_t pad00[0x18];
    WString mName;              // +0x18
    uint8_t pad28[0x17c];
    Vector3 mPos;               // +0x1a4
    Vector3* GetPosition();     // 0x00b8d8e0
};
struct cGameInfo {
    WString mPath;              // +0x00
    uint8_t pad10[0x10];
    WString mName;              // +0x20
    uint8_t pad30[0x18];
    cAvatarProfile* mpAvatar;   // +0x48
    ResourceKey mKey4C;         // +0x4c
    ResourceKey mKey58;         // +0x58
    ResourceKey mKey64;         // +0x64
    ResourceKey mKey70;         // +0x70
    uint32_t mnStarID;          // +0x7c
    uint8_t pad80[0x0c];
    uint32_t m8C;               // +0x8c
    uint32_t m90;               // +0x90
    uint8_t pad94[0x10];
    uint32_t mA4;               // +0xa4
    uint32_t mA8;               // +0xa8
    bool mbAC;                  // +0xac
    uint8_t padAD[0x0b];
    cSPUILayout_s00de_b840* mpLayout;      // +0xb8
    cStarRecord* GetStarRecord();   // 0x00de4610
};
struct cTerrainSphere {
    uint8_t pad000[0x68c];
    uint32_t mu68c;             // +0x68c
    uint32_t mu690;             // +0x690
    uint32_t mu694;             // +0x694
    uint8_t pad698[0xa64];
    uint32_t mu10fc;            // +0x10fc
    uint32_t mu1100;            // +0x1100
    uint32_t mu1104;            // +0x1104
    uint32_t mu1108;            // +0x1108
    uint8_t pad110c[0x44];
    uint32_t mu1150;            // +0x1150
    uint32_t mu1154;            // +0x1154
    uint32_t mu1158;            // +0x1158
    uint32_t mu115c;            // +0x115c
    uint32_t mu1160;            // +0x1160
    uint32_t mu1164;            // +0x1164
    uint32_t mu1168;            // +0x1168
    uint32_t mu116c;            // +0x116c
    uint32_t mu1170;            // +0x1170
    uint32_t mu1174;            // +0x1174
};
struct cGalaxyGameEntryUIStateMachine {
    uint8_t pad00[8];
    int mCountdown;             // +0x08
    cGameInfo* mpGameInfo;      // +0x0c
    uint8_t pad10[0x18];
    cSPUILayout_s00de_b840 mLayout;        // +0x28
    uint8_t pad34[0x50];
    struct PlayEntry {
        uint8_t pad00[0xac];
        uint32_t mAC;           // +0xac
        uint32_t mB0;           // +0xb0
        uint32_t mB4;           // +0xb4
        uint8_t padB8[8];
    };
    PlayEntry mEntries[6];      // +0x84
    uint32_t mu504;             // +0x504
    uint32_t mu508;             // +0x508
    uint32_t mu50c;             // +0x50c
    uint32_t mu510;             // +0x510
    uint8_t pad514[0xd0];
    uint32_t mu5e4;             // +0x5e4
    uint8_t pad5e8[0x40];
    cGameInfo* mpGameInfo628;   // +0x628

    void SpawnBehaviorMessage(cGameInfo* gameInfo);     // 0x00deb840
    void StartGame();                                   // 0x00deb930
    bool OnMessageCloseZoom(uint32_t id, int arg);      // 0x00debe30
    void EnterPlanet(const WString& name);              // 0x00debec0
    void StartNewGameZoom();                            // 0x00dec020
    void Update(int arg);                               // 0x00dec170
    void RefreshWhenIdle(int arg);                      // 0x00dec3f0
    void SetDeferredWindow(uint32_t id, void* param);   // 0x00dec430 -> 0x00e00650
    void ResetGameUI();                                 // 0x00dec460
    bool CanPlay();                                     // 0x00dec4a0
    void ResetButtons();                                // 0x00dec500
    bool IsAssetWindowOn(uint32_t id);                  // 0x00dec540
    void UpdateLocks();                                 // 0x00dec570
    void ShowSkin(uint32_t id);                         // 0x00dec6d0
    void QueueEditorLaunch(uint32_t id, const uint32_t* key); // 0x00dec770

    void StopZoomTransition();                          // 0x00deb5d0
    void SetupTerrainFromGame(cGameInfo* gameInfo);     // 0x00deb770
    void SetWindowParam(uint32_t id, void* param);      // 0x00e00650
};
struct UIBehaviorMessage {
    void** mpVfptr;             // +0x00
    uint32_t mnRefCount;        // +0x04
    const char* mpStateName;    // +0x08
    uint32_t pad0c;
    uint32_t mu10;              // +0x10
    uint32_t pad14[7];
    uint32_t mnMessageID;       // +0x30
    uint32_t mu34;              // +0x34
    uint32_t mu38;              // +0x38
    uint32_t mu3c;              // +0x3c

    UIBehaviorMessage()
    {
        mnMessageID = 0;
        mpVfptr = vtbl_RefBaseA22;
        _InterlockedExchange((volatile long*)&mnRefCount, 0);
        mpVfptr = vtbl_UIBehaviorMessage;
        mu38 = 0;
        ((void (__thiscall*)(UIBehaviorMessage*))mpVfptr[1])(this);
    }
    void Release()
    {
        ((void (__thiscall*)(UIBehaviorMessage*))mpVfptr[2])(this);
    }
};
void*  __cdecl NounManager();                      // 0x00b3d300
void*  __cdecl GetGameMode();                      // 0x00b3d340
void*  __cdecl GetPlanetModel();                   // 0x00b3d350
void*  __cdecl GetTriggerMgr();                    // 0x00b3d4d0
void*  __cdecl GetSetting9();                      // 0x00401090
void*  __cdecl GetSetting3();                      // 0x00401030
void*  __cdecl GetResourceManager();               // 0x0067dcd0
void*  __cdecl GetSystemX();                       // 0x0067dd20
void*  __cdecl LocaleManager();                    // 0x0067de40
IMessageServer* __cdecl MessageServer_s00de_b840();           // 0x0067dcc0
void*  __cdecl GetAux0();                          // 0x00b3d360
void*  __cdecl GetAux410();                        // 0x00b3d410
char   __cdecl IsWorldLayoutFlagSet_s00de_b840(int flag);     // 0x00685520
void   __cdecl FUN_00de3be0(cGameInfo* gameInfo);  // 0x00de3be0
char   __cdecl FUN_00550970(void* self);           // 0x00550970 (this in ecx)
uint32_t __cdecl FUN_00556140(ResourceKey* key, uint32_t id);  // 0x00556140
void   __cdecl FUN_00e83910(ResourceKey* key, int a, int b, int c); // 0x00e83910
void   __cdecl FUN_00eebf90(void* a, void* b);     // 0x00eebf90
void   __cdecl FUN_005bf3a0(ResourceKey* key, const uint32_t* id, void** out, int flags); // 0x005bf3a0
void   __cdecl FUN_005bf3a0(void* self, void* a, void** out, int b);  // 0x005bf3a0 (untyped spelling used by s00dfb5b0)
void   __cdecl CalloutMessageBox(int a, const void* b); // 0x00809db0
void   __cdecl FUN_00b6e4b0(Vector3 v, float a, float b, Vector3* out); // 0x00b6e4b0
void   __cdecl FUN_00b6f140();                     // 0x00b6f140
void   __cdecl FUN_00b6f180();                     // 0x00b6f180
struct cTriggerMgr {
    void ClearTimers();                             // 0x00adffd0
    void PostTrigger(const char* name, int a, int b, int c, int d, int e); // 0x00ae0930
};
struct cResourceManager {
    PV2 PV
    virtual bool GetResource(const ResourceKey* pKey, IRefObj** ppOut, int a, int b, int c, int d); // +0x0c
};
struct cGameMode {
    PV4
    virtual void PopState(cGameInfo* gameInfo);         // +0x10
    void SavePath(const wchar_t* path);                 // 0x00b27ee0
    void AddStar(cGameInfo* gameInfo);                  // 0x00b27160
    bool QualifyName(const wchar_t* name, uint32_t* a, uint32_t* b); // 0x00b275a0
};
struct cLocaleText {
    PV16 PV4
    virtual void SetText(const wchar_t* text, int flags);   // +0x34
};
struct cLocale {
    PV8 PV2
    virtual cLocaleText* GetCalloutText();                  // +0x20
};
struct cAppSystem {
    PV16 PV
    virtual bool IsFeatureEnabled();                        // +0x50
};
struct cSetting410 {
    uint8_t pad000[0x508];
    bool mb508;                 // +0x508
};
struct NounMgr {
    uint8_t pad00[0x74];
    void* mpTerrainSphere;      // +0x74
    void ResetEdits();          // 0x00b20fb0
    cTerrainSphere* GetCurrentTerrainSphere();   // 0x00f67d90
};
struct cPlanetModel {
    bool SetPosition(Vector3* pos, int a, int b);   // 0x00b8d8a0
};
struct cPlanetLoader {
    void Reset();                                   // 0x00b7dec0
};
struct cSystemX {
    PV8 PV2
    virtual void PostMessage(uint32_t id);          // +0x28
};
struct AssetBrowserObj {
    uint8_t pad00[0x1c];
    bool mb1c;                  // +0x1c
    bool CloneModelAsset(ResourceKey key, ResourceKey* pOut, uint32_t id, bool flag); // 0x00646370
};
struct cSetting9 {
    cAvatarProfile* GetAvatarProfile();   // 0x004df420
};
// ---- items of slice s00deb840 end

// ---- items of slice s00dec7c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern bool gbFlag16a0ee8;                                      // 0x016a0ee8
extern bool gbFlag16a0e48;                                      // 0x016a0e48
extern uint32_t gThemeIconCount;                                // 0x016a0db0
extern const uint32_t kGUI_PanelButtonIDs[6];                   // 0x0147e4d8
extern const float kRealOne;                                    // 0x01485720
struct Key {
    uint32_t mnA;                                               // 0x000
    uint32_t mnB;                                               // 0x004
    uint32_t mnC;                                               // 0x008
};
struct Vec3 {
    float x, y, z;
};
class cUIWindow {
public:
virtual void w00();
virtual void w04();
virtual void w08();
    virtual cUIWindow* FindChild(uint32_t nID);                 // 0x00c
    virtual void w10();
    virtual void SetParams(int32_t nA, int32_t nB);             // 0x014
    virtual void w18();
    virtual bool HasEntry(uint32_t nID);                        // 0x01c
virtual void w20();
virtual void w24();
    virtual void SetFlag(int32_t nA, bool bB);                  // 0x028
    virtual uint32_t GetFlags();                                // 0x02c
virtual void w30();
virtual void w34();
virtual void w38();
virtual void w3c();
    virtual void OnCommand(int32_t nCommand);                   // 0x040
    virtual void SelectPanel(int32_t nIndex, int32_t nParam);   // 0x044
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
    virtual void Show(int32_t nShow, bool bEnable);             // 0x07c
virtual void w80();
virtual void w84();
virtual void w88();
virtual void w8c();
    virtual void w90();                                         // 0x090
virtual void w94();
virtual void w98();
virtual void w9c();
virtual void wa0();
virtual void wa4();
    virtual cUIWindow* GetContent();                            // 0x0a8
};
class cSPUILayout_s00de_c7c0 {
public:
    cUIWindow* FindWindowByID(uint32_t nWindowID, int32_t nSearchChildren); // 0x008105b0
    uint8_t mPad000[0x34];
};
class cPanelButtonWindow {
public:
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
    virtual uint32_t GetState();                                // 0x028
};
class Drawable_s0083_0c00 {
public:
    void SetImageIcon(int32_t nIndex, void* pImage);
};
class cUICommHost {
public:
    void BindSlot(void* pKey, uint32_t nID, Vec3* pPos, uint32_t a, uint32_t b,
                  cUIWindow* pWindow);                          // 0x00ae8d00
    void Flush(uint32_t a, uint32_t b, uint32_t c, uint32_t d); // 0x00ae7e10
};
cUICommHost* __cdecl GetUiCtl();                                // 0x00b3d490
class cEditorModel {
public:
    uint8_t mPad000[0x4c];                                      // 0x000
    Key mKey4C;                                                 // 0x04c
    uint8_t mPad058[0x0c];                                      // 0x058
    Key mKey64;                                                 // 0x064
    Key mKey70;                                                 // 0x070
    uint8_t mPad07C[0x28];                                      // 0x07c
    int32_t mnFieldA4;                                          // 0x0a4
    int32_t mnFieldA8;                                          // 0x0a8
};
class cNewGameModePanel {
public:
    uint8_t mPad000[0x10];                                      // 0x000
    int32_t mnField10;                                          // 0x010
    uint8_t mPad014[0x60];                                      // 0x014
    uint32_t* mpValuesBegin;                                    // 0x074
    uint32_t* mpValuesEnd;                                      // 0x078
    uint8_t mPad07C[0x14];                                      // 0x07c
    int32_t mnComboValue;                                       // 0x090
    void* mpImageCreature;                                      // 0x094
    void* mpImageVehicle;                                       // 0x098
    void* mpImageBuilding;                                      // 0x09c
    int32_t mnWindowIDA0;                                       // 0x0a0
    int32_t mnWindowIDA4;                                       // 0x0a4
    int32_t mnWindowIDA8;                                       // 0x0a8
    uint32_t mnCreatureKey;                                     // 0x0ac
    uint32_t mnBuildingKey;                                     // 0x0b0
    uint32_t mnVehicleKey;                                      // 0x0b4
    int32_t mnHighlightWindowID;                                // 0x0b8
    bool mbFieldBC;                                             // 0x0bc
    uint8_t mPad0BD[0x03];
};
class cUIStateList {
public:
    void Reset();                                               // 0x00e20e00
    uint8_t mPad000[0x10];
};
class cGameModeManager {
public:
    void SetGuideState(int32_t nState);                         // 0x00de53d0
    uint8_t mPad000[0x24];                                      // 0x000
    uint32_t* mpPanelIDBegin;                                   // 0x024
    uint32_t* mpPanelIDEnd;                                     // 0x028
};
extern cGameModeManager* gpGameMode;                            // 0x016a1344
class cEditorEntry {
public:
    uint8_t mPad000[0x84];                                      // 0x000
    uint32_t mnField84;                                         // 0x084
    uint32_t mnField88;                                         // 0x088
};
class cAssetEntryList {
public:
    PV4 PV2 PV                                         // 0x00 .. 0x18
    virtual bool Matches(uint32_t nKey);                        // 0x01c
};
class cUIEventQueue {
public:
    PV8 PV8 PV4 PV2                                    // 0x00 .. 0x54
    virtual cAssetEntryList* GetSelectedEntry(uint32_t a, uint32_t b); // 0x058
};
cUIEventQueue* __cdecl GetUIEventQueue();                       // 0x00401010
bool __cdecl FUN_00de3d00(cSPUILayout_s00de_c7c0* pLayout, uint32_t nWindowID, void* pImage);
namespace SP {
class cGalaxyGameEntryUIStateMachine_s00de_c7c0 {
public:
    void MakeNewAsset(uint32_t nAssetType);                     // 0x00dec7c0
    void LoadAsset(uint32_t nAssetType);                        // 0x00dec940
    void ShowAssetButtonsForLevel(int32_t nLevel);              // 0x00decad0
    void SetupStartState();                                     // 0x00dece10
    void HighlightPanelButton(uint32_t nWindowID);              // 0x00decf70
    void ToggleAssetLock(uint32_t nWindowID);                   // 0x00decfd0
    void ResetAssetButtons(bool bBuilding, bool bCreature, bool bVehicle); // 0x00ded140
    void ResetThemeIcons();                                     // 0x00ded390
    void EditExistingAsset(uint32_t nAssetType);                // 0x00ded410

    void FUN_00decd10(int32_t nLevel);                          // 0x00decd10
    void FUN_00ded030();                                        // 0x00ded030
    bool FUN_00ded0b0(Key* pKey);                               // 0x00ded0b0

    void QueueEditorLaunch(uint32_t nLaunchID, const Key& rKey); // 0x00dec770
    void ResetButtons();                                        // 0x00dec500
    void UpdateLocks();                                         // 0x00dec570
    void HandleEvent(uint32_t nEvent);                          // 0x00df3be0

    uint8_t mPad000[0x28];                                      // 0x000
    cSPUILayout_s00de_c7c0 mLayout;                                        // 0x028
    uint8_t mPad05C[0x1c];                                      // 0x05c
    int32_t mnRolloverCount;                                    // 0x078
    uint32_t* mpRolloverWindowIDs;                              // 0x07c
    uint8_t mPad080[0x04];                                      // 0x080
    cNewGameModePanel maModePanels[7];                          // 0x084
    uint8_t mPad5C4[0x24];                                      // 0x5c4
    int32_t mnPendingAssetAction;                               // 0x5e8
    int32_t mnField5EC;                                         // 0x5ec
    uint8_t mPad5F0[0x18];                                      // 0x5f0
    cUIStateList mStateList;                                    // 0x608
    void* mpAssetIconCreature;                                  // 0x618
    void* mpAssetIconVehicle;                                   // 0x61c
    void* mpAssetIconBuilding;                                  // 0x620
    void* mpThemeIconBlank;                                     // 0x624
    cEditorModel* mpModel;                                      // 0x628
};  // namespace SP
}
using SP::cGalaxyGameEntryUIStateMachine_s00de_c7c0;
class cPanelWidget {
public:
    uint8_t mPad000[0x81];
    uint8_t mbField81;                                          // 0x081
};
class cPanelHost {
public:
    void FUN_00decf00(int32_t nID);                             // 0x00decf00
    uint8_t mPad000[0x10];
    cPanelWidget* mpWidget;                                     // 0x010
};
// ---- items of slice s00dec7c0 end

// ---- items of slice s00ded5a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint8_t gEditorMenuSource;            // 0x016a0dd0
extern uint8_t gPlanetPreviewEnabled;        // 0x016a0dc0
extern float gPlanetPreviewBlend;            // 0x016a0d90
extern void* gAppPreferences;                // 0x015fd91c
extern uint32_t gWindowIdTable[11];          // 0x0147e4f0
struct IWindow_s00de_d5a0;
struct cString_s00de_d5a0 {
    uint32_t mTable;
    uint32_t mKey;
    uint32_t mText;
    cString_s00de_d5a0();                                                       // 0x006b5060
    cString_s00de_d5a0(uint32_t nTable, uint32_t nKey, const wchar_t* pText);   // 0x006b5770
    ~cString_s00de_d5a0();                                                      // 0x006b5240
    bool Load(uint32_t nTable, uint32_t nKey, const wchar_t* pText); // 0x006b54b0
    const wchar_t* GetText() const;                                  // 0x006b55c0
};
class cString_s00df_00b0 {
public:
    cString_s00df_00b0();                                                       // 0x006b5060
    cString_s00df_00b0(uint32_t nTable, uint32_t nKey, const wchar_t* pText);   // 0x006b5770
    ~cString_s00df_00b0();                                                      // 0x006b5240
    cString_s00df_00b0& operator=(const cString_s00df_00b0& rOther);            // 0x006b5430
    bool Load(uint32_t nTable, uint32_t nKey, const wchar_t* pText);            // 0x006b54b0
    const wchar_t* c_str() const;                                               // 0x006b55c0
public:
    uint32_t mTable;
    uint32_t mKey;
    uint32_t mText;
    uint32_t mPad0C[2];
};
struct IWindow_s00de_d5a0 {
    virtual void v00();                // 0x000
    virtual void v04();                // 0x004
    virtual void* v08();               // 0x008
    virtual void* v0C(uint32_t nId);   // 0x00c
    virtual void* v10();               // 0x010
    virtual void* v14();               // 0x014
    virtual void* v18();               // 0x018
    virtual void* v1C();               // 0x01c
    virtual void* v20();               // 0x020
    virtual void* v24();               // 0x024
    virtual int32_t v28();             // 0x028
    virtual void* v2C();               // 0x02c
    virtual void* v30();               // 0x030
    virtual void* v34();               // 0x034
    virtual void* v38();               // 0x038
    virtual void* v3C();               // 0x03c
    virtual void* v40();               // 0x040
    virtual void* v44();               // 0x044
    virtual void* v48();               // 0x048
    virtual void* v4C();               // 0x04c
    virtual void* v50();               // 0x050
    virtual void* v54();               // 0x054
    virtual void* v58();               // 0x058
    virtual void* v5C();               // 0x05c
    virtual void* v60();               // 0x060
    virtual void* v64();               // 0x064
    virtual void* v68();               // 0x068
    virtual void* v6C();               // 0x06c
    virtual void* v70();               // 0x070
    virtual void* v74();               // 0x074
    virtual void* v78();               // 0x078
    virtual void v7C(bool bA, bool bB);            // 0x07c
    virtual void v80(const wchar_t* pText);        // 0x080
    virtual void* v84();               // 0x084
    virtual void* v88();               // 0x088
    virtual void* v8C();               // 0x08c
    virtual void* v90();               // 0x090
    virtual void* v94();               // 0x094
    virtual void* v98();               // 0x098
    virtual void* v9C();               // 0x09c
    virtual void* vA0();               // 0x0a0
    virtual void* vA4();               // 0x0a4
    virtual IWindow_s00de_d5a0* vA8();            // 0x0a8
    virtual void* vAC();               // 0x0ac
    virtual void* vB0();               // 0x0b0
    virtual void* vB4();               // 0x0b4
    virtual void* vB8();               // 0x0b8
    virtual void* vBC();               // 0x0bc
    virtual void* vC0();               // 0x0c0
    virtual void* vC4();               // 0x0c4
    virtual void* vC8();               // 0x0c8
    virtual void* vCC();               // 0x0cc
    virtual void* vD0();               // 0x0d0
    virtual void* vD4();               // 0x0d4
    virtual void* vD8();               // 0x0d8
    virtual void* vDC();               // 0x0dc
    virtual void* vE0();               // 0x0e0
    virtual void* vE4();               // 0x0e4
    virtual void* vE8();               // 0x0e8
    virtual void* vEC();               // 0x0ec
    virtual void* vF0();               // 0x0f0
    virtual void* vF4();               // 0x0f4
    virtual void* vF8();               // 0x0f8
    virtual void* vFC();               // 0x0fc
    virtual void* v100();              // 0x100
    virtual void v104(void* pOwner);   // 0x104
};
class cSPUILayout_s00de_d5a0 { public:              // sizeof == 0x18
    uint8_t mData[0x18];
    bool Init(const wchar_t* pName, int32_t nFlags, bool bAppend, uint32_t nGroup); // 0x00812160
    IWindow_s00de_d5a0* FindWindowByID(uint32_t nId, bool bRecursive);                         // 0x008105b0
    void Shutdown(uint32_t nFlags);                                                 // 0x00811ad0
};
struct cSPUIPopupMenuWin2 {              // IWindow-derived popup menu
    void Reset();                                                        // 0x0081cce0
    void* AddMenuItem3(uint32_t nKey, uint32_t nFlags, uint32_t nText,
                       bool bSelect);                                    // 0x0081b6a0
    void OnMenuItemSelected(void* pA, void* pB);                         // 0x0081bef0
};
struct cSPUILayeredObject_s00de_d5a0 {
    void RemoveAllModels();                                              // 0x0080ea50
    void FUN_0080dda0(IWindow_s00de_d5a0* pWindow, int32_t nFlags);                 // 0x0080dda0
};
struct cPlanetModelView {                // 12-byte view helper at +0x608
    uint8_t mData[0x0c];
    void FUN_00e21260(const void* pKey, const void* pText, void* pModel); // 0x00e21260
    void FUN_00e20d30(float fValue);                                      // 0x00e20d30
    void FUN_00e20e00();                                                  // 0x00e20e00
    void FUN_00e20d60(const void* pArg);                                  // 0x00e20d60
};
struct cGalaxyEditorState {              // what 0x00de4610 returns
    uint8_t mPad00[0xac];
    uint8_t mIsActive;                   // +0xac
};
struct cGalaxyEditorFlow {               // +0x628 member
    uint8_t mPad00[0x4c];
    void* mpField4C;                     // +0x4c
    void* mpField50;                     // +0x50
    uint8_t mPad54[0x10];
    void* mpField64;                     // +0x64
    uint8_t mPad68[8];
    void* mpField70;                     // +0x70
    cGalaxyEditorState* FUN_00de4610(int32_t nIndex);   // 0x00de4610
};
struct EditorMenuItem {
    uint32_t mField00;                   // +0x00
    uint8_t mPad04[0x14];
    uint32_t mField18;                   // +0x18
    uint8_t mPad1C[0x4c];
    int32_t mKind;                       // +0x68
    uint8_t mPad6C[4];
};
struct EditorMenuSource {                // FUN_0067cb30 result
    uint8_t mPad00[0xb4];
    EditorMenuItem* mpItemsB4;           // +0xb4
    EditorMenuItem* mpItemsB8;           // +0xb8
    uint8_t mPadBC[0x0c];
    EditorMenuItem* mpItemsC8;           // +0xc8
    EditorMenuItem* mpItemsCC;           // +0xcc
};
struct cRefMethodTable {
    uint8_t mPad00[0x170];
    void (__stdcall* mpRelease)(void* pObject, uint32_t nFlags);  // +0x170
};
struct cRefObject {                      // refcounted object (+0x40 count, +0x04 flags)
    void** mpMeta;                       // +0x00  (meta table; [0] -> method table)
    uint32_t mFlags;                     // +0x04
    uint8_t mPad08[0x38];
    int32_t mRefCount;                   // +0x40
};
void* __cdecl FUN_0067cb30();                                        // 0x0067cb30
void* __cdecl FUN_0080d710(void* pBox);                              // 0x0080d710
void* __fastcall FUN_0080f730(void* pBox);                           // 0x0080f730
void* __fastcall FUN_00bbaa60(void* pObject);                        // 0x00bbaa60
void* __fastcall FUN_00b8d8e0(void* pObject);                        // 0x00b8d8e0
void* __cdecl StarManager_s00de_d5a0();                                         // 0x00b3d2a0
void* __cdecl FUN_00b3d360(const void* pKey);                        // 0x00b3d360
bool  __cdecl FUN_00b7d4f0(void* pHandle);                           // 0x00b7d4f0
void  __cdecl FUN_00b7d440(void* pHandle, void* pA, void* pB);       // 0x00b7d440
bool  __cdecl IsWorldLayoutFlagSet(int32_t nFlag);                   // 0x00685520
IWindow_s00de_d5a0* __cdecl GetSystemAT();                                      // 0x00a206f0
struct DSub {
    int32_t GetField10(int32_t nArg);                                // 0x00830cf0
};
void* __cdecl GlobalBoundingBox();                                   // 0x0067cad0 (no-arg form)
void* __cdecl AddBoundingBoxEx(void* pOwner, int32_t nA, int32_t nB); // 0x0067cad0 (3-arg form)
#define LAYOUT_WINDOW_IDS                                                      \
    0x07d275bb, 0x07d27876, 0x05384d05, 0x05933fe0, 0x05384eec, 0x05384fbb,    \
    0x05385002, 0x053f00c7, 0x053f06e1, 0x053f06ee, 0x053f06f5, 0x053f06fc,    \
    0x053f0707, 0x0684bbe8, 0x05400fa5, 0x054045ce, 0x054045e3, 0x05404617,    \
    0x0588ab05, 0x0595e0a8, 0x05951103, 0x059434c0, 0x06451450, 0x06451451,    \
    0x059434c1, 0x059461b2, 0x059461b1, 0x059461b0, 0x05a725b4, 0x05942cd0,    \
    0x95964773, 0x95964775, 0x95964774, 0x95964779, 0x9596477b, 0x9596477a,    \
    0x95964776, 0x95964778, 0x95964777, 0x06149007, 0x06149008, 0x06149009,    \
    0x0614c680, 0x0614c681, 0x0614c682, 0x06775e1f, 0x06775e20, 0x06775e22,    \
    0x06775e23, 0x06775e21
struct cGalaxyGameEntryUIStateMachine_s00de_d5a0 {  // PDB candidate: SP::cGalaxyGameEntryUIStateMachine
    void* mpVTable;                         // +0x000
    uint8_t mPad004[0x24];                  // +0x004
    cSPUILayout_s00de_d5a0 mLayout;                    // +0x028
    uint8_t mPad040[0x34];                  // +0x040
    int32_t mFlowState;                     // +0x074
    uint8_t mPad078[8];                     // +0x078
    uint8_t mIsLayoutBroken;                // +0x080
    uint8_t mPad081[0x587];                 // +0x081
    cPlanetModelView mPlanetView;           // +0x608
    cSPUILayeredObject_s00de_d5a0* mpLayeredObject;    // +0x614
    IWindow_s00de_d5a0* mpWindow618;                   // +0x618
    IWindow_s00de_d5a0* mpWindow61C;                   // +0x61c
    IWindow_s00de_d5a0* mpWindow620;                   // +0x620
    IWindow_s00de_d5a0* mpWindow624;                   // +0x624
    cGalaxyEditorFlow* mpEditorFlow;        // +0x628

    bool PopulateContextMenu();                                     // 0x00ded5a0
    void ShowPlanetModel();                                         // 0x00ded7d0
    void PickStarForEditorToGameFlow(uint32_t nID, int32_t nMode);  // 0x00ded920
    bool SetLayout(const wchar_t* pLayoutName);                     // 0x00dedda0
    void TearDownUI();                                              // 0x00dee2a0
};
struct MenuTextKey {
    uint32_t mTable;
    uint32_t mKey;
    uint32_t mPage;
};
struct MenuTextIds {
    uint32_t mId0;
    uint32_t mId1;
    uint32_t mId2;
    uint32_t mId3;
};
struct cNotifyAttackListenerBase {
    void* mpVTable;                      // +0x00
    uint8_t mFlag04;                     // +0x04, cleared by base constructor
    uint8_t mPad05[3];
    cNotifyAttackListenerBase();         // 0x00e00630
};
struct cNotifyAttackListener : cNotifyAttackListenerBase {
    uint32_t mField08;                   // +0x08
    uint32_t mField0C;                   // +0x0c
    uint8_t mField10;                    // +0x10
    uint8_t mPad11[3];
    uint32_t mField14;                   // +0x14
    cNotifyAttackListener();             // 0x00dee320
};
extern cNotifyAttackListener* gNotifyListener;   // 0x016a1570
struct cProperty_s00de_d5a0 {
    uint8_t mPad00[0x12];
    uint16_t mType;                      // +0x12
    uint8_t* GetBool();                  // 0x0041e920
};
struct cPropertyList_s00de_d5a0 {
virtual bool v00();
virtual bool v04();
virtual bool v08();
virtual bool v0C();
virtual bool v10();
virtual bool v14();
virtual bool v18();
virtual bool v1C();
    virtual bool v20();
    virtual bool FindProperty(uint32_t nId, cProperty_s00de_d5a0** ppOut);  // 0x24
};
struct cGalaxyGameEntryMode_s00de_d5a0 {
    cRefObject* mpObject00;                             // +0x00
    cRefObject* mpObject04;                             // +0x04
    cGalaxyGameEntryUIStateMachine_s00de_d5a0* mpStateMachine;     // +0x08
    void RefreshNotifyAttackToggle();                   // 0x00dee360
    void ReleaseOwned();                                // 0x00dee3d0
};
static void ReleaseRef(cRefObject* pObject)
{
    if (!pObject)
        return;
    uint32_t nFlags = pObject->mFlags >> 31;
    if (pObject->mRefCount > 1) {
        --pObject->mRefCount;
        return;
    }
    cRefMethodTable* pTable = *(cRefMethodTable**)pObject->mpMeta;
    pTable->mpRelease(pObject, nFlags & 1);
}
// ---- items of slice s00ded5a0 end

struct cGalaxyGameEntryMode {
    cRefObject* mpObject00;                             // +0x00
    cRefObject* mpObject04;                             // +0x04
    cGalaxyGameEntryUIStateMachine_s00de_d5a0* mpStateMachine;     // +0x08
    void FUN_00e00760(uint32_t a);                      // 0x00e00760
    void FUN_00df0a40(uint32_t arg);                    // 0x00df0a40
    void RefreshNotifyAttackToggle();                   // 0x00dee360
    void ReleaseOwned();                                // 0x00dee3d0
};

// ---- items of slice s00dee450 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int  gvtbl_notify;      // 0x0147e618
extern int  gvtbl_base;        // 0x0147dba8
extern int  gDAT_16a1570;      // 0x016a1570
extern int  gDAT_16a1580;      // 0x016a1580
extern int  gDAT_13ebc58;      // 0x013ebc58  "App"
extern int  gDAT_13f09b4;      // 0x013f09b4  "Simulator"
extern "C" int iswctype(int ch, int type);                   // import
typedef unsigned char  byte;
typedef unsigned short wchar16;
void  operator delete[](void* p) throw();                                   // 0x00f47380
void* operator new(unsigned n, const char* file, unsigned line,
                   unsigned a, unsigned b);                                 // 0x00f473a0
extern byte gDAT_16a0f08;      // 0x016a0f08
struct PanelIDs_s00de_e450; extern PanelIDs_s00de_e450* gkGUI_PanelIDs_s00de_e450;   // 0x016a1344  (pointer global)
void      FUN_00de53d0(unsigned a);                          // 0x00de53d0
struct PanelIDs; extern PanelIDs* gkGUI_PanelIDs;   // 0x016a1344  (pointer global)
void      FUN_00ded920(unsigned a, unsigned b);              // 0x00ded920
char __stdcall FUN_00de5cb0(unsigned a);                     // 0x00de5cb0
uint32_t  FUN_00dec990(void* p);                             // 0x00dec990
uint32_t  FUN_004bafc0(void* a, void** b);                   // 0x004bafc0
void* __stdcall FUN_004010a0(void* a, unsigned b);           // 0x004010a0 (callee pops the 2 args)
struct NameGen;
void*     EffectsManagerPtr();                               // 0x0067ddd0
void*     APP_Ptr();                                         // 0x0067dd10
void*     MessageServerPtr();                                // 0x0067dcc0
char      Editor_Launch();                                   // 0x005a9200
struct RBNode_s00de_e450;
RBNode_s00de_e450*   RBTreeIncrement(RBNode_s00de_e450* n);                        // 0x00921580
struct WString_s00de_e450 {
    void* mpBegin;                                             // +0x00
    void* mpEnd;                                               // +0x04
    void* mCap;                                                // +0x08
    void* Assign(void* first, void* last);                     // 0x00423650
};
struct NameGen {
    void* GetName();                                           // 0x005ecf80
};
char      CreateImageFromResource2(void* a, void** b, char c, int d, int e); // 0x00806230
void      RemoveHandler(void* a, unsigned b, unsigned c, unsigned d, unsigned e); // 0x00571db0
void*     RbtreeFind(void* outIter, const void* key, void* tree);  // 0x00e39fb0
void*     memcpy_(void* d, const void* s, unsigned n);       // import
struct Hashtable {
    uint32_t mHash;                   // +0x00
    void**   mTable;                  // +0x04
    uint32_t mnBucketCount;           // +0x08
    void*    find_(void* outIter, const void* key);   // 0x00645ed0
};
struct HashPair {
    uint32_t key;                     // +0x00
    uint32_t value;                   // +0x04
};
struct Layout_s00de_e450 {                       // cSPUILayout (at GalaxyUI + 0x28)
    void*    FindWindowByID(uint32_t id, int b);      // 0x008105b0
    char     mPad[0x18];
};
struct PanelIDs_s00de_e450 {                     // kGUI_PanelIDs target (pointer at 0x016a1344)
    char     pad_00[0x19c];
    void*    mpHandler;               // +0x19c
    char     pad_1a0[0x1f5 - 0x1a0];
    byte     mFlag;                   // +0x1f5

    void FUN_00de5d00(void* a, void* b, void* c, void* d, void* e, void* f, void* g);
    void FUN_00de5d00(void* a, void* b, void* c, const struct PanelIds_s00de_ef20& d, int e, void* f, void* g);
};
struct GridObj {                      // the editor grid object (at GalaxyUI + 0x628)
    char      pad_00[0x20];
    wchar16*  mpName;                 // +0x20 (eastl wstring data)
    char      pad_24[0x80 - 0x24];
    float     x;                      // +0x80
    float     y;                      // +0x84
    float     z;                      // +0x88
    char      pad_8c[0xa8 - 0x8c];
    int32_t   mIndex;                 // +0xa8
    char      pad_ac[0xb0 - 0xac];
    void*     mB0;                    // +0xb0
};
struct Record {                       // 0xc0-byte layout record (GalaxyUI + 0x84 + i*0xc0)
    char       pad0[0x20];
    Hashtable  mHash;                 // +0x20
    char       pad2[0xc0 - 0x2c];

    bool FUN_00deed00(uint32_t key);
};
struct RBNode_s00de_e450 {
    char      pad_00[0x10];
    uint32_t  mKey;                   // +0x10
    union { uint32_t mValue; byte mFlag; };   // +0x14
};
struct Rbtree {                       // eastl::rbtree header (0x18 bytes)
    uint32_t  m00;                    // +0x00
    void*     mpAnchor;               // +0x04  (sentinel "node"; &mpAnchor is the end node)
    void*     mpRoot;                 // +0x08
    void*     mp0c;                   // +0x0c
    byte      mFlag;                  // +0x10
    char      pad_11[0x03];
    uint32_t  mnSize;                 // +0x14

    void DoNukeSubtree(void* node);   // 0x009a9600
    void reset_s00de_ed40()
    {
        DoNukeSubtree(mp0c);
        mpRoot   = &mpAnchor;
        mp0c     = 0;
        mFlag    = 0;
        mnSize   = 0;
        mpAnchor = &mpAnchor;
    }
};
struct UIDrawable {                    // a drawable window returned by a window vtable slot
    void** vtbl;                       // +0x00
    void   SetImageIcon(int a, void* b);   // 0x00831760
};
struct LaunchData_s00de_e450 {                    // editor launch-data object (operator new 0x9c)
    char       pad_00[0x0c];
    uint32_t   f0c;                    // +0x0c
    uint32_t   f10;                    // +0x10
    uint32_t   f14;                    // +0x14
    uint32_t   f18;                    // +0x18
    char       pad_1c[0x88 - 0x1c];
    void*      f88;                    // +0x88
    uint32_t   f8c;                    // +0x8c
    uint32_t   f90;                    // +0x90
    uint32_t   f94;                    // +0x94
    uint32_t   f98;                    // +0x98
    uint32_t   f9c;                    // +0x9c

    LaunchData_s00de_e450* Ctor();                // 0x005a9080
};
typedef void   (__thiscall *VF0)(void*);
typedef void   (__thiscall *VF1)(void*, int);
typedef void*  (__thiscall *VFP)(void*);
typedef void*  (__thiscall *VFP1)(void*, int);
typedef int    (__thiscall *VFI)(void*);
typedef void   (__thiscall *VF2)(void*, int, int);
typedef void   (__thiscall *VF2P)(void*, void*, int);
typedef char   (__thiscall *VFC2F)(void*, float, float);
typedef void   (__thiscall *VFC8)(void*, float, float, float*);
typedef void   (__thiscall *VFIP)(void*, int, void*);
typedef void   (__thiscall *VF3)(void*, int, int, int);
typedef void   (__thiscall *VF1P)(void*, void*);
struct MsgCtx {
    char  pad_00[0x18];
    float mLocal[9];                  // +0x18  (3x3 matrix)
    char  pad_3c[0x48 - 0x3c];
    byte  mFlag44;                    // +0x44
};
namespace SP {
struct Sub608 {                       // sub-object at GalaxyUI + 0x608
    char pad_00[0x0c];
    void FUN_00e20e80();              // 0x00e20e80
};
}
namespace SP {
class GalaxyUI {                      // cGalaxyGameEntryUIStateMachine
public:
    void**     vtbl0;                 // +0x00
    void**     vtbl1;                 // +0x04
    void*      field_08;              // +0x08
    void*      field_0c;              // +0x0c
    void*      field_10;              // +0x10
    void*      mpRef14;               // +0x14
    uint32_t   f18;                   // +0x18
    uint32_t   f1c;                   // +0x1c
    uint32_t   f20;                   // +0x20
    uint32_t   f24;                   // +0x24
    Layout_s00de_e450     mLayout;               // +0x28
    Rbtree     mMap40;                // +0x40
    char       pad_58[0x18];
    uint32_t   mFlag70;               // +0x70
    uint32_t   mHoverFlag;            // +0x74
    char       pad_78[0x84 - 0x78];
    Record     mRecords[1];           // +0x84  (variable-length, 0xc0 stride)
    char       pad_144[0x500 - 0x144];
    uint32_t   f500;                  // +0x500
    uint32_t   f504;                  // +0x504
    uint32_t   f508;                  // +0x508
    uint32_t   f50c;                  // +0x50c
    uint32_t   f510;                  // +0x510
    char       pad_514[0x520 - 0x514];
    Rbtree     mMap520;               // +0x520
    char       pad_538[0x5e0 - 0x538];
    uint32_t   f5e0;                  // +0x5e0
    char       pad_5e4[0x608 - 0x5e4];
    Sub608     mSub;                  // +0x608
    void*      mpRef614;              // +0x614
    char       pad_618[0x624 - 0x618];
    GridObj*   mp624;                 // +0x624
    GridObj*   mpGrid;                // +0x628

    void      FUN_00dee2a0();         // 0x00dee2a0
    void*     FUN_00deebc0(unsigned flags);
    void      FUN_00deed40();
    void      FUN_00deede0();
    char      FUN_00deee80(int mode);
    void      FUN_00deef20(int key, void* map, unsigned b);
    uint32_t  FUN_00deefb0(uint32_t key);
    void      FUN_00dee9a0(float a, float b);
    void      FUN_00dee770(uint32_t id, void* refObj);
    void      FUN_00dee800(uint32_t id, uint32_t imageId);
    char      FUN_00dee450(int msg, void* ctx);
    char      FUN_00def050(void* nameObj);
};
}
namespace SP {
class Wrapper {                       // |this| of the hover wrappers (00deec00 / 00def020)
public:
    char       pad0[0x08];
    GalaxyUI*  mpP;                   // +0x08
    char       pad_0c[0x14 - 0x0c];
    void*      mpRef14;               // +0x14

    void FUN_00deec00(float a, float b, float c);
    void FUN_00def020();
};
}
using SP::GalaxyUI;
using SP::Wrapper;
// ---- items of slice s00dee450 end

struct PanelIDs {                     // kGUI_PanelIDs target (pointer at 0x016a1344)
    char     pad_00[0x19c];
    void*    mpHandler;               // +0x19c
    char     pad_1a0[0x1f5 - 0x1a0];
    byte     mFlag;                   // +0x1f5

    void FUN_00de5d00(void* a, void* b, void* c, void* d, void* e, void* f, void* g);
    void FUN_00de53d0(uint32_t a);                    // 0x00de53d0
};

// ---- items of slice s00def400 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma warning(disable : 4100)
namespace eastl {
struct cHashNode {
    uint8_t     pad000[0x14];                            // +0x00 .. +0x13
    cHashNode*  mpNext;                                  // +0x14
};
}
namespace eastl {
struct cHashIterator {
    cHashNode*  mpNode;                                  // +0x00
    cHashNode** mppBucket;                               // +0x04
};
}
namespace eastl {
int __cdecl Locale_CompareKeys(const wchar_t* pKey, cHashNode* pNode); // 0x0087d9a0
}
namespace eastl {
class cHashTable {
public:
    uint8_t     pad000[4];                               // +0x00
    cHashNode** mppBuckets;                              // +0x04
    uint32_t    mBucketCount;                            // +0x08

    cHashIterator FUN_00def5f0(const wchar_t** ppKey);
};
}
struct NameString_s00df_fc80;
namespace SP {
class cGalaxyGameEntryUIStateMachine_s00de_f400 {
public:
    __declspec(noinline) bool FUN_00def400(u32 nText);
    void FUN_00def690();
    void FUN_00def750(uint32_t id, uint32_t value);
    void FUN_00def7c0();
    __declspec(noinline) void UpdateNavigationControls();  // 0x00def8c0 (SP::cGalaxyGameEntryUIStateMachine::UpdateNavigationControls)
    NameString_s00df_fc80 FUN_00defc00();
    void MakeRandomName();  // 0x00defc80 (SP::cGalaxyGameEntryUIStateMachine::MakeRandomName)
    void SetStateSummaryText(int32_t nField, uint32_t nKey, const wchar_t* pText); // 0x00defd10
    void SelectTheme();  // 0x00defdd0 (SP::cGalaxyGameEntryUIStateMachine::SelectTheme)
    void FillComboBoxes();  // 0x00df00b0 (SP::cGalaxyGameEntryUIStateMachine::FillComboBoxes)
    void UpdateSpecialitySummaryText();  // 0x00df0190 (SP::cGalaxyGameEntryUIStateMachine::UpdateSpecialitySummaryText)
};  // namespace SP
}
// ---- items of slice s00def400 end

// ---- items of slice s00df0280 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
class cGalaxyStateMachine {
public:
    __declspec(noinline) void SetCurrentState(int32_t state);  // 0x00df0670
    void FUN_00dee2a0();                                       // 0x00dee2a0
};
}
namespace SP {
class cGalaxyGameEntryUIStateMachine_s00df_0280 {
public:
    void ShowPanel();  // 0x00df0280 (SP::cGalaxyGameEntryUIStateMachine::ShowPanel)
    __declspec(noinline) void SetCurrentState(int32_t state);  // 0x00df0670 (SP::cGalaxyGameEntryUIStateMachine::SetCurrentState)
    void FUN_00df0980();  // 0x00df0980 (SP::cGalaxyGameEntryUIStateMachine::FUN_00df0980)

    uint8_t              pad000[8];                          // +0x00 .. +0x07
    cGalaxyStateMachine* mpStateMachine;                     // +0x08
};
}
// ---- items of slice s00df0280 end

// ---- items of slice s00df1e70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float g_fMillisecondsPerSecond;                    // 0x013ec5b4
extern const float g_fElapsedTimeScale;                         // 0x013f5c88
extern void* gsNewGameFlowLayout;                               // 0x016a0cf8
#define nullptr 0
class KeyVec {
public:
    void DoInsertKey(Key* pPosition, const Key& rKey);          // 0x004e3e10
    KeyVec& operator=(const KeyVec& rOther);                    // 0x006609a0
    Key* mpBegin;                                               // 0x000
    Key* mpEnd;                                                 // 0x004
    Key* mpCap;                                                 // 0x008
};
struct cMatchConstraint {
    cMatchConstraint(int32_t nValue);                           // 0x00558830
    cMatchConstraint(uint32_t nKey, int32_t nEqual, int32_t nValue); // 0x00558860
    void Destroy();                                             // 0x006066f0
    uint32_t mnData[9];                                         // 0x000
};
struct cObjectTemplateVtbl {
    void* mpReserved[13];                                       // 0x000
    void (*mpfnFindMatches)(void* pDatabase, KeyVec* pOut, ...); // 0x034
};
struct cObjectTemplateDB {
    cObjectTemplateVtbl* mpVtbl;                                // 0x000
};
cObjectTemplateDB* ObjectTemplateDB();                          // 0x0067cb40
class cRandomLC_s00df_1e70 {
public:
    uint32_t RandomUint32Uniform(uint32_t nRange);              // 0x00a68fb0
};
extern cRandomLC_s00df_1e70 gRandom;                                       // 0x01601760
class cTimerList {
public:
    void Restart();                                             // 0x00571e80
    long long GetElapsedTime();                                 // 0x0093a5e0
    void SetBoolProperty();                                     // 0x0093a2e0
    int32_t mnTimeLow;                                          // 0x000
    int32_t mnTimeHigh;                                         // 0x004
    uint8_t mPad008[0x10];                                      // 0x008
};
class cUIWindow_s00df_1e70;
class cSPUILayout_s00df_1e70 {
public:
    cUIWindow_s00df_1e70* FindWindowByID(int32_t nWindowID, int32_t nSearchChildren); // 0x008105b0
    uint8_t mPad000[0x34];                                      // 0x000
};
class cUIPropertyList {
public:
virtual void p00();
virtual void p04();
virtual void p08();
virtual void p0c();
virtual void p10();
    virtual void SetInt(int32_t nValue);                        // 0x014
};
class cButtonDrawable {
public:
    Key mKey;                                                   // 0x000
    uint32_t mnExtra;                                           // 0x00c
};
class cUIWindow_s00df_1e70 {
public:
virtual void w00();
virtual void w04();
virtual void w08();
    virtual cUIWindow_s00df_1e70* FindChild(uint32_t nID);                 // 0x00c
    virtual void w10();
    virtual void SetParams(int32_t nA, int32_t nB);             // 0x014
virtual void w18();
virtual void w1c();
virtual void w20();
virtual void w24();
    virtual void SetFlag(int32_t nA, int32_t nB);               // 0x028
    virtual uint32_t GetFlags();                                // 0x02c
virtual void w30();
virtual void w34();
virtual void w38();
virtual void w3c();
    virtual void OnCommand(int32_t nCommand);                   // 0x040
virtual void w44();
virtual void w48();
    virtual void SetSelection(Key* pKey, Key* pParam);          // 0x04c
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
    virtual void Show(int32_t nShow, int32_t nEnable);          // 0x07c
virtual void w80();
virtual void w84();
virtual void w88();
virtual void w8c();
    virtual void OnClick();                                     // 0x090
virtual void w94();
virtual void w98();
virtual void w9c();
virtual void wa0();
virtual void wa4();
    virtual cUIWindow_s00df_1e70* GetContent();                            // 0x0a8
    uint8_t mPad004[0x208];                                     // 0x004
    cUIPropertyList mPropertyList;                              // 0x20c
};
class cEditorModel_s00df_1e70 {
public:
    uint8_t mPad000[0x4c];                                      // 0x000
    Key mKey4C;                                                 // 0x04c
    uint8_t mPad058[0x0c];                                      // 0x058
    Key mKey64;                                                 // 0x064
    Key mKey70;                                                 // 0x070
    uint8_t mPad07C[0x14];                                      // 0x07c
    int32_t mnField90;                                          // 0x090
    uint8_t mPad094[0x0c];                                      // 0x094
    int32_t mnFieldA0;                                          // 0x0a0
    int32_t mnFieldA4;                                          // 0x0a4
    int32_t mnFieldA8;                                          // 0x0a8
    int32_t mnFieldAC;                                          // 0x0ac
    int32_t mnFieldB0;                                          // 0x0b0
};
class cNewGameModePanel_s00df_1e70 {
public:
    uint8_t mPad000[0x10];                                      // 0x000
    int32_t mnField10;                                          // 0x010
    uint8_t mPad014[0x60];                                      // 0x014
    uint32_t* mpValuesBegin;                                    // 0x074
    uint32_t* mpValuesEnd;                                      // 0x078
    uint8_t mPad07C[0x14];                                      // 0x07c
    int32_t mnComboValue;                                       // 0x090
    uint8_t mPad094[0x0c];                                      // 0x094
    int32_t mnWindowIDA0;                                       // 0x0a0
    int32_t mnWindowIDA4;                                       // 0x0a4
    int32_t mnWindowIDA8;                                       // 0x0a8
    int32_t mnFieldAC;                                          // 0x0ac
    uint8_t mPad0B0[0x10];                                      // 0x0b0
};
class cUIStateList_s00df_1e70 {
public:
    void Reset();                                               // 0x00e20e00
    void Remove(int32_t nID);                                   // 0x00e21040
    uint8_t mPad000[0x14];                                      // 0x000
    int32_t mnField14;                                          // 0x014
    uint8_t mPad018[0x08];                                      // 0x018
};
class cGameModeManager_s00df_1e70 {
public:
    void SetGuideState(int32_t nState);                         // 0x00de53d0
    void LoadMode(int32_t nMode, int32_t nFlag);                // 0x00de86d0
};
extern cGameModeManager_s00df_1e70* gpGameMode_s00df_1e70;                            // 0x016a1344
class cGameUIController {
public:
virtual void u00();
virtual void u04();
virtual void u08();
virtual void u0c();
virtual void u10();
virtual void u14();
virtual void u18();
virtual void u1c();
virtual void u20();
virtual void u24();
virtual void u28();
virtual void u2c();
virtual void u30();
virtual void u34();
virtual void u38();
virtual void u3c();
virtual void u40();
virtual void u44();
virtual void u48();
virtual void u4c();
virtual void u50();
virtual void u54();
virtual void u58();
    virtual void SetModeObject(cEditorModel_s00df_1e70* pModel);           // 0x05c
};
extern cGameUIController* gpGameUI;                             // 0x016a1484
class cUIEvents {
public:
virtual void e00();
virtual void e04();
virtual void e08();
virtual void e0c();
virtual void e10();
virtual void e14();
virtual void e18();
virtual void e1c();
virtual void e20();
virtual void e24();
virtual void e28();
virtual void e2c();
virtual void e30();
virtual void e34();
virtual void e38();
virtual void e3c();
    virtual void OnCommand(uint32_t nCommand);                  // 0x040
virtual void e44();
virtual void e48();
    virtual void OnSelect(Key* pKey, Key* pParam);              // 0x04c
};
cUIEvents* UIEventQueue();                                      // 0x00401010
class cSettings4 {
public:
    uint8_t mPad000[0x1c];                                      // 0x000
    uint8_t mbField1C;                                          // 0x01c
};
cSettings4* GetSetting4();                                      // 0x00401040
class cSomething {
public:
    void DoUpdate();                                            // 0x00b7dec0
};
cSomething* FUN_00b3d360_s00df_1e70();                                     // 0x00b3d360
class cCommHost {
public:
    void Update();                                              // 0x00ae8510
};
cCommHost* FUN_00b3d490(int32_t nID);                           // 0x00b3d490
void FUN_00804ed0(float* pA, float* pB);                        // 0x00804ed0
void __stdcall FUN_00dee9a0(float fA, float fB);                // 0x00dee9a0
void FUN_00de3d40(Key* pOut, KeyVec* pKeys, Key* pBaseKey);     // 0x00de3d40
namespace SP {
class cGalaxyGameEntryUIStateMachine_s00df_1e70 {
public:
    void UpdateSummaryCreatureName();                           // 0x00df2080
    void OnAssetBrowserSelection(Key* pKey);                    // 0x00df21d0
    void DoStartNewGame(int32_t nElapsedMs);                    // 0x00df23b0
    void SelectNextState();                                     // 0x00df2550
    void SelectPreviousState();                                 // 0x00df2660
    void OnModeSelection(int32_t nModeID);                      // 0x00df2770
    void OnSummarySelection(int32_t nModeID);                   // 0x00df2920
    void PickRandomByMode(int32_t nPendingAction, uint32_t nFilterValue,
                          Key* pBaseKey);                       // 0x00df2a60
    void PickRandomCreature();                                  // 0x00df2bb0
    void PickRandomBuilding();                                  // 0x00df2d60

    void GetRandomKey(KeyVec* pKeys);                           // 0x00df1e70

    void SetCurrentState(int32_t nState);                       // 0x00df0670
    void SetLayout(void* pLayout);                              // 0x00dedda0
    void UpdateLocks();                                         // 0x00dec570
    void UpdateButtonStdDrawable(int32_t nWindowID, cButtonDrawable* pParam); // 0x00dee770
    void SetStateSummaryText(int32_t nField, uint32_t nKey, uint16_t* pText); // 0x00defd10
    void ToggleAssetLock(int32_t nWindowID);                    // 0x00decfd0
    void UpdateSpecialitySummaryText();                         // 0x00df0190
    void UpdateNavigationControls();                            // 0x00def8c0
    void FillComboBoxes();                                      // 0x00df00b0
    bool FUN_00dec4a0();                                        // 0x00dec4a0
    void FUN_00dee2a0();                                        // 0x00dee2a0
    bool FUN_00ded0b0(Key* pKey);                               // 0x00ded0b0
    void FUN_00ded030();                                        // 0x00ded030
    bool FUN_00deee80(int32_t nState);                          // 0x00deee80

    uint8_t mPad000[0x28];                                      // 0x000
    cSPUILayout_s00df_1e70 mLayout;                                        // 0x028
    int32_t* mpStateListBegin;                                  // 0x05c
    int32_t* mpStateListEnd;                                    // 0x060
    uint8_t mPad064[0x0c];                                      // 0x064
    uint8_t mbField70;                                          // 0x070
    uint8_t mPad071[0x03];                                      // 0x071
    int32_t mnCurrentState;                                     // 0x074
    uint8_t mPad078[0x08];                                      // 0x078
    uint8_t mbField80;                                          // 0x080
    uint8_t mPad081[0x03];                                      // 0x081
    cNewGameModePanel_s00df_1e70 maModePanels[7];                          // 0x084
    uint8_t mPad5C4[0x24];                                      // 0x5c4
    int32_t mnPendingAssetAction;                               // 0x5e8
    uint8_t mPad5EC[0x04];                                      // 0x5ec
    cTimerList mTimer;                                          // 0x5f0
    cUIStateList_s00df_1e70 mStateList;                                    // 0x608
    cEditorModel_s00df_1e70* mpModel;                                      // 0x628
    uint8_t mPad62C[0x10];                                      // 0x62c
};  // namespace SP
}
using SP::cGalaxyGameEntryUIStateMachine_s00df_1e70;
class cGalaxyGameEntryScreen {
public:
    void Update(float fDelta);                                  // 0x00df29d0
    uint8_t mPad000[0x08];                                      // 0x000
    cGalaxyGameEntryUIStateMachine_s00df_1e70* mpStateMachine;             // 0x008
    uint8_t mPad00C[0x04];                                      // 0x00c
    uint8_t mbStartRequested;                                   // 0x010
    uint8_t mPad011[0x03];                                      // 0x011
};
// ---- items of slice s00df1e70 end

// ---- items of slice s00df2d80 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char DAT_016a0f78;                           // a config byte
extern const unsigned kUIFlagIds[5];        // 0x0147e530
extern const unsigned kUIPanelButtonIds[5]; // 0x0147e4d8
struct IWindow_s00df_2d80 {                                   // a cSPUIWindow / cSPUILayout window
    PV2 PV
    PV4 PV2 PV                                     // +0x0c..+0x24  (unused slots)
    virtual char     Slot28();                     // +0x28  -> predicate (low byte)
    virtual unsigned Slot2C();                     // +0x2c  -> state value
    PV8 PV8 PV2 PV                                 // +0x30..+0x78  (unused slots)
    virtual void     Slot7C(int a, int b);         // +0x7c  SetVisible/flag
    virtual void     Slot80(const wchar_t* s);     // +0x80  set label text
};
struct SPUILayout {
    char pad[0x18];
    IWindow_s00df_2d80* FindWindowByID(unsigned id, int flag); // 0x008105b0  __thiscall
};
struct GGE {                                        // kGUI_PanelIDs
    char pad00[0x103];
    char m103;                                      // +0x103
    char pad104[0xb0];                              // +0x104..+0x1b3
    int  mPanelIds[8];                              // +0x1b4  panel-id table indexed by mode/level
    void Fn53d0(int);                               // 0x00de53d0
};
extern GGE* kGUI_PanelIDs_s00df_2d80;                          // 0x016a1344
void* __cdecl operator_new(unsigned size, const char* name, int, int, int, int); // 0x00f473a0
struct Key_s00df_2d80 { int a; int b; int c; };
struct Hashtable_s00df_2d80 {
    unsigned   m00;              // +0x00
    unsigned** mBuckets;         // +0x04
    unsigned   mBucketCount;     // +0x08
    unsigned   m0c;              // +0x0c
    unsigned   m10;              // +0x10
    unsigned   m14;              // +0x14
    unsigned   m18;              // +0x18
    unsigned*  LookupOrInsert(const void* key);  // 0x00de7630
};
class cString {
public:
    cString();                                             // 0x006b5060
    cString(unsigned table, unsigned instance, const wchar_t* def); // 0x006b5770
    cString& operator=(const cString& rhs);                // 0x006b5430
    ~cString();                                            // 0x006b5240
    const wchar_t* GetText();                              // 0x006b55c0
private:
    unsigned mData[7];
};
struct tNewGameFlow {
    char      pad00[0x20];       // +0x00..+0x1f
    Hashtable_s00df_2d80 mMap20;            // +0x20  key -> value map used by SetLevel
    char      pad3c[0x10];       // +0x3c..+0x4b
    Key_s00df_2d80       m4c;               // +0x4c
    char      pad58[0x08];       // +0x58..+0x5f
    unsigned* m60;               // +0x60  begin of {id, textId} pairs
    unsigned* m64;               // +0x64  end
    char      pad68[0x20];       // +0x68..+0x87
    unsigned  m88;               // +0x88  number of enabled flags
    char      pad8c[0x34];       // +0x8c..+0xbf  (stride is 0xc0)
};
static bool HashHasKey(Hashtable_s00df_2d80* t, unsigned key)
{
    if (t->mBucketCount == 0)
        return false;
    unsigned* node = (unsigned*)t->mBuckets[key % t->mBucketCount];
    while (node != 0) {
        if (node[0] == key)
            return true;
        node = (unsigned*)node[2];
    }
    return false;
}
struct GameEntry_s00df_2d80 {                                  // object at StateMachine+0x628
    char pad00[0x20];                               // +0x00..+0x1f
    unsigned short* m20;                            // +0x20  begin of a 16-bit vector
    unsigned short* m24;                            // +0x24  end
    char pad28[0x24];                               // +0x28..+0x4b
    Key_s00df_2d80  m4c;                                       // +0x4c
    char pad58[0x0c];                               // +0x58..+0x63
    Key_s00df_2d80  m64;                                       // +0x64
    Key_s00df_2d80  m70;                                       // +0x70
    char pad7c[0x14];                               // +0x7c..+0x8f
    int  m90;                                       // +0x90
    char pad94[0x10];                               // +0x94..+0xa3
    int  mA4;                                       // +0xa4
    int  mA8;                                       // +0xa8
};
struct StateMachine {
    char pad00[0x28];                               // +0x00..+0x27
    SPUILayout mLayout;                             // +0x28
    char pad40[0x41];                               // +0x40..+0x80
    unsigned char m81;                              // +0x81  "herbivore layout chosen" flag
    char pad82[0x02];                               // +0x82..+0x83
    tNewGameFlow mFlow[6];                          // +0x84  stride 0xc0
    char pad504[0x1c];                              // +0x504..+0x51f
    Hashtable_s00df_2d80 mHash[7];                             // +0x520  stride 0x1c
    int m5e4;                                       // +0x5e4
    int m5e8;                                       // +0x5e8  last panel id applied
    char pad5ec[0x3c];                              // +0x5ec..+0x627
    GameEntry_s00df_2d80* mEntry;                              // +0x628

    void PickRandomVehicle();                       // 0x00df2d80
    void OnAssetBrowserSelection(Key_s00df_2d80* p);           // 0x00df21d0  (ret 4)
    void SelectNextState();                         // 0x00df2550
    void PickRandomCreature();                      // 0x00df2bb0
    void PickRandomAssets(char flag);               // 0x00df3ab0  (ret 4)
    void PickRandomByMode(unsigned id, int tag, Key_s00df_2d80* key); // 0x00df2a60  (ret 0xc)
    void SetLevel(int level);                       // 0x00df2ea0  (ret 4)
    void Init(int flowId);                          // 0x00df32d0  (ret 4)
    void SelectTheme(int theme);                    // 0x00defdd0
    void ShowSkin(unsigned skinId);                 // 0x00dec6d0
    void SetStateSummaryText(int a, unsigned b, const wchar_t* text); // 0x00defd10
    void ResetAssetButtons(int a, int b, int c);    // 0x00ded140
    int  FnEE890(Key_s00df_2d80* key);                         // 0x00dee890
    void FnEF20(int a, Hashtable_s00df_2d80* table, unsigned panelId); // 0x00deef20
};
struct Impl {
    char pad00[0x20];
    SPUILayout mLayout;                             // +0x20
    char pad38[0x34];                               // +0x38..+0x6b
    int  m6c;                                       // +0x6c
    char pad70[0x570];                              // +0x70..+0x5df
    int  m5e0;                                      // +0x5e0

    void TestEditorToGame(int* p);                  // 0x00df2e20  (ret 4)
};
struct Sim {
    char pad[0x630];
    Sim* Ctor();                                    // 0x00df0c00  (returns this)
    void Fn3410();                                  // 0x00df3410
};
struct Holder { char pad[8]; Sim* m8; };            // object taking the new Simulator
// ---- items of slice s00df2d80 end

// ---- items of slice s00df5670 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float DAT_01486114;   // 0x01486114
extern const float DAT_01485720;   // 0x01485720
extern const float DAT_01486110;   // 0x01486110
extern const float DAT_014853e0;   // 0x014853e0
extern const float DAT_01471064;   // 0x01471064
extern float DAT_016a16a4;         // 0x016a16a4
extern float DAT_016a16a8;         // 0x016a16a8
extern const float DAT_016a0e98;   // 0x016a0e98
extern const float DAT_016a0ea8;   // 0x016a0ea8
extern const float DAT_016a0eb8;   // 0x016a0eb8
extern const float DAT_016a0ec8;   // 0x016a0ec8
extern const float DAT_014007f4;   // 0x014007f4
extern char* kGUI;                 // 0x016a1344
extern char vtbl_UI_cDownloadDialog_A[];   // 0x0147e9d0
extern char vtbl_UI_cDownloadDialog_B[];   // 0x0147e9b4
extern char vtbl_UI_cDownloadDialog_C[];   // 0x0147ea70
extern char vtbl_UI_cDownloadDialog_D[];   // 0x0147ea54
extern char vtbl_Resource_Async[];         // 0x013fa72c
typedef unsigned int uint;
struct Vec4 { float x, y, z, w; };
struct Obj;
struct cSPUILayout_s00df_5670;
struct cSPUILayout_s00df_5670 {
    void* FindWindowByID(uint id, int b);              // 0x008105b0 (ret 8) -> IWinNode*
    void* FindWindowByIDB(uint id, int b);             // 0x008105b0 (ret 8)
    bool  Init(const void* key, bool b, uint id);      // 0x008120d0 (ret 0xc)
    void  Shutdown(uint b);                            // 0x00811ad0 (ret 4)
    void  dtor();                                      // 0x00811fe0
    void  ctor();                                      // 0x00810000
};
struct IRefCount { virtual void r00(); virtual void r04(); };
struct IWinNode : IRefCount {
virtual void  v08();
virtual void  v0c(int b);
virtual void  v10();
virtual void  v14();
virtual void  v18();
virtual int   v1c();
virtual void  v20();
virtual void  v24();
virtual void  v28();
virtual void  v2c();
virtual void  v30();
virtual Vec4* v34();
    virtual Vec4* v38();
virtual void  v3c();
virtual void  v40();
virtual void  v44();
virtual void  v48();
virtual void  v4c();
virtual void  v50();
    virtual void  v54();
    virtual void* v58();
    virtual void  v5c(void* p);
    virtual void  v60(const float* rect);
    virtual void  v64(float a, float b);
virtual void  v68();
virtual void  v6c();
virtual void  v70();
virtual void  v74();
    virtual void  v78();
    virtual void  v7c(int a, int b);
virtual bool  v80(const wchar_t* s);
virtual void  v84();
virtual void  v88();
virtual void  v8c();
virtual void  v90();
virtual void  v94();
virtual void  v98();
virtual void  v9c();
virtual void  va0();
virtual void  va4();
virtual void  va8();
virtual void  vac();
virtual void  vb0();
virtual void  vb4();
virtual void  vb8();
virtual void  vbc();
virtual void  vc0();
virtual void  vc4();
virtual void  vc8();
virtual void  vcc();
virtual void  vd0();
virtual void  vd4();
virtual void  vd8();
virtual void  vdc();
virtual void  ve0();
virtual void  ve4();
virtual void  ve8();
    virtual void  vec();
    virtual void* vf0(int a, int b, float* p);
virtual void  vf4();
virtual void  vf8();
    virtual void  vfc();
    virtual void  v100();
    virtual void  v104(void* p);
    virtual void  v108(void* p);
};
struct MsgObj {
virtual void  m00();
virtual void  m04();
virtual void  m08();
virtual void  m0c();
    virtual void  m10();
    virtual int   m14(int a, int b, int c);
};
struct AudioSys {
virtual void  a00();
virtual void  a04();
virtual void  a08();
virtual void  a0c();
virtual void  a10();
virtual void  a14();
virtual void  a18();
virtual void  a1c();
    virtual void  a20();
};
void  __cdecl SPUIHelpers_EndModal(void* p, int a, int b);              // 0x00809c50 (cdecl)
void* __cdecl SPUIHelpers_GetMainWindowArea_s00df_5670(Vec4* out);                 // 0x00805ea0 (ret 4)
Obj*  __cdecl SP_App();                                                 // 0x0067dd10
Obj*  __cdecl SP_StarManager();                                         // 0x00b3d2a0
void  __cdecl FUN_00df5610(float f);                                    // 0x00df5610 (ret 4)
void  __cdecl FUN_00de3c70(void* p, float* a, float* b);                // 0x00de3c70 (ret 0xc)
void  __cdecl FUN_00e00670(uint a, void* b);                            // 0x00e00670 (ret 8)
void  __cdecl FUN_00e00650(uint a, void* b);                            // 0x00e00650 (ret 8)
void  __cdecl FUN_00de86d0(uint a, int b);                              // 0x00de86d0 (ret 8)
void  __stdcall SP_cSPUISpace_KillSetiEffects(Obj* a, int flag);        // 0x00435ed0 (ret 8)
bool  __cdecl FUN_005f2350(const float* v);                             // 0x005f2350
Obj*  __cdecl FUN_00dd9190();                                           // 0x00dd9190
void  __fastcall FUN_00ddb760(Obj* p);                                  // 0x00ddb760 (this in ecx)
void  __fastcall FUN_00de9ec0(Obj* p);                                  // 0x00de9ec0 (this in ecx)
struct Quat { float v[4]; };
char   __fastcall FUN_007c4510(void* app, float a, float b, const float* qa, const float* qb); // 0x007c4510 (ret 0x10)
float  __cdecl FUN_00698b30(const float* a, const float* b, const float* out);               // 0x00698b30 (ret 0xc)
void   __fastcall FUN_007c4180(void* app, const float* in, float* out);                       // 0x007c4180 (ret 8)
struct WinTextRef {
    void* m_p;                                          // +0x00
    WinTextRef& operator=(void* p);                     // 0x00b5f950 (ret 4)
};
extern uint DAT_016a1848[];        // 0x016a1848 (bitset)
struct RandomLinCong {
    double next();                                      // 0x009360d0
};
extern RandomLinCong sMathRandom;   // 0x1601760
struct cDownloadDialog;
struct cDownloadDialog {
    void* mpVtbl_00;        // +0x00
    void* mpVtbl_04;        // +0x04  Resource::Async
    void* mpVal_08;         // +0x08  (vector begin for the +0x08/+0x0c vector view)
    union { void* mpNode_0c; void* m_entryEnd; cSPUILayout_s00df_5670* mpLayout_0c; }; // +0x0c
    float m_timerBase;      // +0x10
    float m_timerPeriod;    // +0x14
    char  m_active;         // +0x18
    char  m_latch;          // +0x19
    char pad1[0x1c - 0x1a];
    float m_p1c;            // +0x1c
    float m_p20;            // +0x20
    union { float m_p24; void* mpNode_24; }; // +0x24
    float m_p28;            // +0x28
    char  m_paused;         // +0x2c
    char pad2[0x30 - 0x2d];
    void* m_label;          // +0x30 AutoRefCount<IWinText>
    float m_r34;            // +0x34
    float m_r38;            // +0x38
    float m_r3c;            // +0x3c
    float m_r40;            // +0x40
    float m_progress;       // +0x44
    void* m_entry;          // +0x48
    int   m_count;          // +0x4c
    int   m_index;          // +0x50
    char  m_layout[0x08];   // +0x54 cSPUILayout

    cSPUILayout_s00df_5670* Layout() { return (cSPUILayout_s00df_5670*)((char*)this + 0x54); }
    cSPUILayout_s00df_5670* LayoutB() { return (cSPUILayout_s00df_5670*)((char*)this + 0x0c); }

    void   FUN_00df5670(char b);        // 0x00df5670 (ret 4)
    void   FUN_00df57d0(int b);         // 0x00df57d0 (ret 4)
    bool   FUN_00df5830(void* retaddr); // 0x00df5830 (ret 4)
    void   FUN_00df58f0();              // 0x00df58f0
    bool   FUN_00df59c0(void* p);       // 0x00df59c0 (ret 4)
    void   FUN_00df5aa0(char b);        // 0x00df5aa0 (ret 4)
    bool   FUN_00df5ac0(int b);         // 0x00df5ac0 (ret 4)
    void   FUN_00df5cd0();              // 0x00df5cd0
    void*  FUN_00df5d30(int b);         // 0x00df5d30 (ret 4)
    bool   FUN_00df5d90(void* a, void* b); // 0x00df5d90 (ret 8)
    void   FUN_00df6040();              // 0x00df6040
    bool   FUN_00df6140(Obj* a, float x, float y); // 0x00df6140 (ret 0xc)
    void   FUN_00df6330(uint id, void* p, uint b); // 0x00df6330 (ret 8)
    int    FUN_00df64c0(float a, float b, float c); // 0x00df64c0 (ret 0xc)
    void   FUN_00df65e0(void* a, void* b, float c); // 0x00df65e0 (ret 0xc)
};
static double RandRangeD(double lo, double hi)
{
    double u = sMathRandom.next();
    return u * (hi - lo) + lo;
}
struct StarVec { uint32_t* mpBegin; uint32_t* mpEnd; int size() { return (int)(mpEnd - mpBegin); } };
struct StarManagerObj { char pad_00[0xf0]; StarVec mVec; };
// ---- items of slice s00df5670 end

// ---- items of slice s00df6700 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_p16a1344;              // 0x016a1344  GUI panel-id / layout manager
extern char  g_c16a0dd0[];            // 0x016a0dd0
extern const float g_f16a0da0;        // 0x016a0da0
extern void* g_p15fd91c;              // 0x015fd91c  _sAppPreferences_SP
extern const float g_f1485720;        // 0x01485720  _HK_REAL_ONE (1.0f)
extern const float g_posX;            // 0x016a1698
extern const float g_posY;            // 0x016a169c
extern const float g_posZ;            // 0x016a16a0
extern const float g_mat00;           // 0x016a1674
extern const float g_mat10;           // 0x016a1678
extern const float g_mat20;           // 0x016a167c
extern const float g_mat01;           // 0x016a1680
extern const float g_mat11;           // 0x016a1684
extern const float g_mat21;           // 0x016a1688
extern const float g_mat02;           // 0x016a168c
extern const float g_mat12;           // 0x016a1690
extern const float g_mat22;           // 0x016a1694
extern "C" void*   __fastcall FUN_00fc7e50(void* self);   // EA::XHTML::DOM::Node::Type
extern "C" void    __fastcall FUN_0080ea50(void* self);   // cSPUILayeredObject::RemoveAllModels
extern "C" void    __fastcall FUN_00409930(void* self);
extern "C" void    __fastcall FUN_005aa530(void* self);
extern "C" void*   __cdecl    FUN_00dd9190_0();
extern "C" void*   __stdcall  FUN_00dd9190_1(void* a);
extern "C" void*   __stdcall  FUN_00dd9190_2(void* a, void* b);
extern "C" void    __fastcall FUN_00ddab00(void* self);
extern "C" void    __fastcall FUN_00dda090(void* self);
extern "C" void*   __cdecl    FUN_006b1f90(unsigned id);  // SP_GetSaveArea
extern "C" void    __cdecl    FUN_006b1d50(void* p, void* r, int c);  // SP_SaveResource
#define PVN(n) virtual void pv##n();
struct MsgArg {                       // message payload passed to FUN_00df68c0
    uint32_t m00;                     // +0x00
    uint32_t m04;                     // +0x04
    int32_t  m08;                     // +0x08
};
extern int (__stdcall *g_pQueryPerformanceCounter)(void*);  // 0x013cc2b8
struct NodeVt {
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7)
    PVN(8) PVN(9) PVN(10) PVN(11) PVN(12) PVN(13) PVN(14) PVN(15)
    PVN(16) PVN(17) PVN(18) PVN(19) PVN(20) PVN(21) PVN(22) PVN(23)
    PVN(24) PVN(25) PVN(26) PVN(27) PVN(28) PVN(29) PVN(30)
    virtual void v7c(int, void*);
};
struct RefVt {                        // ref-counted object stored at +0x34
    virtual void v00();
    virtual void v04();
    virtual void v08(void*);
    virtual void v0c(int);
virtual void d10();
virtual void d14();
virtual void d18();
virtual void d1c();
virtual void d20();
virtual void d24();
virtual void d28();
virtual void d2c();
virtual void d30();
virtual void d34();
virtual void d38();
virtual void d3c();
virtual void d40();
virtual void d44();
    virtual void v48(int, void*, int);
};
struct RetVt {                        // object produced by the panel-id lookup
    virtual void q00();
    virtual void q04();
    virtual void q08(int);
    virtual void q0c();
    virtual void q10();
    virtual void q14();
    virtual void q18(void*);
};
struct PathProp {                     // object stored at panel manager +0x15c
    virtual void p00();
    virtual void p04();
    virtual void p08(int, int, void**);
};
struct WinVt {                        // window returned by FindWindowByID
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7)
    PVN(8) PVN(9) PVN(10) PVN(11) PVN(12) PVN(13) PVN(14) PVN(15)
    PVN(16) PVN(17) PVN(18) PVN(19) PVN(20) PVN(21) PVN(22) PVN(23)
    PVN(24) PVN(25) PVN(26) PVN(27) PVN(28) PVN(29) PVN(30)
    virtual void v7c(int, unsigned char);
};
struct PropList {                     // _sAppPreferences_SP object
virtual void y00();
virtual void y04();
virtual void y08();
virtual void y0c();
    virtual void y10();
    virtual void y14(int, void*);
virtual void y18();
virtual void y1c();
virtual void y20();
    virtual char y24(int, void**);
};
struct Rec {                          // 0xbc-byte element of the array at +0x08
    char    pad080[0x80];
    float   fX;                       // +0x80
    float   fY;                       // +0x84
    float   fZ;                       // +0x88
    char    pad08c[0xac - 0x8c];
    uint8_t bAC;                      // +0xac
    uint8_t bAD;                      // +0xad
    char    pad0ae[0xbc - 0xae];
};
struct Stopwatch_s00df_6700 {
    uint64_t mStart;                  // +0x00
    uint64_t mElapsed;                // +0x08
    int32_t  mUnits;                  // +0x10
    uint32_t mPad;                    // +0x14
    void SetUnits(int);  // 0x0093a1a0 (Stopwatch::SetUnits)
};
struct GObj_s00df_6700 {                         // object behind FUN_00b3d360()
    char FUN_00b7d4f0(void* p);
    void FUN_00b7d440(Vec3 v, void*, void*, void*, void*, void*, void*);
};
struct Banner2 {                      // banner-list holder (panel manager entry)
    char      pad000[0x7c];
    void*     mp7c;                   // +0x7c
    char      pad080[0x84 - 0x80];
    void*     mp84;                   // +0x84
    char      pad088[0xac - 0x88];
    uint8_t   bAC;                    // +0xac
    Banner2*  FUN_00de4610();         // 0x00de4610
    Banner2*  FUN_00bbaa60(int idx);  // 0x00bbaa60
    Vec3*     FUN_00b8d8e0();         // 0x00b8d8e0
};
struct GfxPoint {                     // 0x14-byte display point handed to a window
    uint16_t m00;                     // +0x00
    uint16_t m02;                     // +0x02
    float    m04;                     // +0x04
    float    m08;                     // +0x08
    float    m0c;                     // +0x0c
    float    m10;                     // +0x10
};
struct Transform34 { char m[0x38]; };
struct Variant_s00df_6700 {
    char    mData[0x10];
    uint16_t mFlagsW;                 // +0x10
    uint16_t mAuxW;                   // +0x12
    void SetChar(char* p);  // 0x00422e20 (Variant::SetChar)
    void Destruct(bool b);  // 0x0093db80 (Variant::Destruct)
};
struct Prop {                         // cProperty returned by PropList::y24
    char  pad000[0x12];
    uint16_t m12;                     // +0x12
    char* GetBool();
};
struct PanelMgr;                      // layout sub-object + property list
struct LayoutObj {
    char pad000[0x18];
    WinVt* FindWindowByID(uint32_t id, int b);   // 0x008105b0
};
struct PanelMgr {
    char       pad000[0x144];
    LayoutObj  mLayout;               // +0x144
    PathProp*  mp15c;                 // +0x15c
    void FUN_00de9ec0();              // 0x00de9ec0
    void FUN_00de5330(int v);         // 0x00de5330
};
struct SW20Obj {                      // embedded object at WinA+0x20
    char  pad000[0x10];
    void* mp10;                       // +0x10  (WinA+0x30)
    void FUN_00e21260(void*, void*, void*);
    void FUN_00e20d60(void*);
    void FUN_00e20d30(float);
};
struct WinA {
    char     pad020[0x20];
    SW20Obj  m20;                     // +0x20
    RefVt*   mp34;                    // +0x34
    char     pad038[0x50 - 0x38];
    uint8_t  m50;                     // +0x50
    char     pad051[0x8c - 0x51];
    void*    mp8c;                    // +0x8c
    void FUN_00df6700(void* param);
    void FUN_00df6740();
    bool FUN_00df6850(RefVt* param);
    bool FUN_00df68c0(uint32_t msg, void* param3);
};
struct WinB {
    char      pad008[8];
    Rec*      mpBegin;                // +0x08
    Rec*      mpEnd;                  // +0x0c
    char      pad010[0x20 - 0x10];
    Stopwatch_s00df_6700 sw20;                   // +0x20
    Stopwatch_s00df_6700 sw38;                   // +0x38
    void FUN_00df6980();
    void FUN_00df6c40();
};
extern "C" GObj_s00df_6700*   FUN_00b3d360_s00df_6700();                        // 0x00b3d360 global getter
// ---- items of slice s00df6700 end

// ---- items of slice s00df9650 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern unsigned DAT_016a0FB8;                      // swarm spawn min
extern unsigned DAT_016a0FC8;                      // swarm spawn max
extern int  DAT_015da7c4, DAT_015da7c8, DAT_015da7cc, DAT_015da7d0;
extern int  kIDs[4][3];                            // 0x0147ebc8
extern char LAB_00ad0e52;                          // 0x00ad0e52 a code label stored as a value
extern char vtbl_AddRef[];                         // 0x0147dc04
extern char vtbl_FUN_0149bad8[];                   // 0x0149bad8
extern char vtbl_ContentValidationSummarizer[];    // 0x013ec458
struct IWindow_s00df_9650 {                          // a cSPUIWindow / cSPUILayout window
    PV2 PV
    virtual void* Slot0C(unsigned a);              // +0x0c  (id) -> sub-object
    virtual void* Slot10();                        // +0x10  -> child
    virtual void  Slot14(unsigned id, void* p, int z); // +0x14  MessageServer::Send
    PV4
    virtual void  Slot28(int a, int b);            // +0x28
    PV4 PV
    virtual void  Slot40(int a);                   // +0x40
    PV4
    virtual char  Slot54();                        // +0x54
    PV2
    virtual void  Slot60(void* v, int z);          // +0x60
    PV
    virtual void  Slot68();                        // +0x68
    PV4
    virtual void  Slot7C(int a, int b);            // +0x7c  SetVisible/flag
    virtual void  Slot80(void* p);                 // +0x80  SetText
};
struct SPUILayout_s00df_9650 {
    char pad[0x18];
    void      Shutdown(unsigned);                  // 0x00811ad0  __thiscall
    IWindow_s00df_9650*  FindWindowByID(unsigned id, int flag); // 0x008105b0  __thiscall
};
struct LocaleLookup_s00de_f400 {                       // 0x00ad3da0
    unsigned* Find(unsigned* pKey);
};
struct GlobalUI {
    void SetVisibility(int v);                     // 0x00e01350  __thiscall
};
struct Map3C { void Fn9dc0(void* key); };          // 0x00de9dc0 (ecx = map)
struct EcB   { char Fn4320(); };                   // 0x00ec4320
struct EcA   { char pad[0x1c]; EcB* m1c; };
struct GGE_s00df_9650 {
    char  pad00[0x3c];
    Map3C mMap3C;                                  // +0x03c  (map passed to FUN_00de9dc0)
    char  pad3D[0xcb];                             // +0x03d..+0x107
    int   m108;                                    // +0x108
    char  pad10C[0x38];                            // +0x10c..+0x143
    SPUILayout_s00df_9650 mLayout;                            // +0x144
    char  pad15C[0x28];                            // +0x15c..+0x183
    GlobalUI* mGlobalUI;                           // +0x184
    char  pad188[0x50];                            // +0x188..+0x1d7
    int   m1D8;                                    // +0x1d8
    int   m1DC;                                    // +0x1dc
    char  pad1E0[0x18];                            // +0x1e0..+0x1f7
    int   m1F8;                                    // +0x1f8

    void Fn5260();                                 // 0x00de5260
    void Fn5300();                                 // 0x00de5300
    void Fn53d0(int);                              // 0x00de53d0
    void Fn9ec0();                                 // 0x00de9ec0
};
extern GGE_s00df_9650* kGUI_PanelIDs_s00df_9650;                         // 0x016a1344
extern EcA* DAT_016c7AA4;                          // -> [+0x1c] object
struct RandomLCG_s00df_9650 { unsigned RandomUint32Uniform(unsigned n); };  // 0x00a68fb0
extern RandomLCG_s00df_9650 _sMathRandom;                     // 0x01601760
struct Stopwatch_s00df_9650 {  // 0x0093a1a0
    int mUnits;
    void SetUnits(int u);  // 0x0093a1a0 (Stopwatch::SetUnits)
};
struct AGSwarm   { void FnB760(); void SpawnOne(); void FnBad0(void* arg); };
struct B3        { void Fn7dec0(); };              // 0x00b7dec0
struct ImgKey { int a; int tag; int c; };
struct LaunchData {
    int   m00;                                      // +0x00
    void* m04;                                      // +0x04
    char  pad08[0x09];                              // +0x08..+0x10
    char  m11;                                      // +0x11
    char  m12;                                      // +0x12
    char  pad13[0x1d];                              // +0x13..+0x2f
    void* m30;                                      // +0x30
    char  pad34[0x04];                              // +0x34..+0x37
    void* m38;                                      // +0x38
    char  pad3C[0x0c];                              // +0x3c..+0x47

    void Fn4b10();                                  // 0x00644b10 (ctr)
    void Fn4b60();                                  // 0x00644b60 (dtor)
};
struct LD2 {
    int   m00;                                      // +0x00
    void* m04;                                      // +0x04
    void* m08;                                      // +0x08
    void* m0c;                                      // +0x0c
    char  pad10;                                    // +0x10
    char  m11;                                      // +0x11
    char  pad12[0x06];                              // +0x12..+0x17
    int   m18;                                      // +0x18
    int   m1c;                                      // +0x1c
    int   m20;                                      // +0x20
    unsigned char m24;                              // +0x24
    char  pad25[0x0b];                              // +0x25..+0x2f
    void* m30;                                      // +0x30
    char  pad34[0x04];                              // +0x34..+0x37
    void* m38;                                      // +0x38
    void* m3c;                                      // +0x3c
    void* m40;                                      // +0x40
    void* m44;                                      // +0x44

    void Fn4b10();                                  // 0x00644b10 (ctr)
    void Fn4b60();                                  // 0x00644b60 (dtor)
};
struct LI { unsigned LowPart; int HighPart; };     // LARGE_INTEGER
struct cString_s00df_9650 {                                   // SP::cString
    void* mData;                                    // +0x00
    void  FUN_006b5770(unsigned, unsigned, unsigned);  // 0x006b5770 ctor
    void  FUN_006b5240();                           // 0x006b5240 dtor
    const wchar_t* FUN_006b55c0();                  // 0x006b55c0 GetText
};
void* __cdecl FUN_00dd9190_s00df_9650();                     // 0x00dd9190 -> object*
void  __cdecl FUN_00de3f00(void* win, void* key, void* z); // 0x00de3f00
char  __cdecl FUN_00eed840(void* p);               // 0x00eed840
char  __cdecl FUN_00eed920(void* a, void* b);      // 0x00eed920
char  __cdecl FUN_00eed970(void* a, void* b);      // 0x00eed970
void  __cdecl FUN_006447c0(int, void*);            // 0x006447c0
void  __cdecl FUN_0064a990(void*);                 // 0x0064a990 AdvancedLaunch
void  __cdecl FUN_00ef7d90();                      // 0x00ef7d90
int* __cdecl SP_MovieSystem();                    // 0x0067cb10
void* __cdecl SP_MessageServer();                  // 0x0067dcc0
struct GGUI;
struct Item {                    // 0x24-byte entry of the +0x0c vector
    int  id;                     // +0x00
    char pad[0x1c];              // +0x04..+0x1f
    int  state;                  // +0x20
};
struct Slot {                    // 0x38-byte entry of the +0xc0 array
    int  x;                      // +0x00
    int  y;                      // +0x04
    int  z;                      // +0x08
    char pad[0x14];              // +0x0c..+0x1f
    char state;                  // +0x20
    char pad2[0x17];             // +0x21..+0x37
};
struct PropKey {                 // 0x18-byte property key at +0x8c
    int type;                    // +0x00
    int a1, a2, a3, a4, a5;      // +0x04..+0x17
};
struct Obj4C {                   // object filled by FUN_006447c0 (used by 00dfa460)
    virtual void FnV0();
    virtual void FnV4();
    virtual void FnV8();
    char  pad04[0x20];           // +0x04..+0x23
    int   m24;                   // +0x24
    int   m28;                   // +0x28
    int   m2c;                   // +0x2c
    int   m30;                   // +0x30
    char  m34;                   // +0x34
    char  pad35;                 // +0x35
    char  m36;                   // +0x36
};
struct Summ13 {                  // 0x14-byte object from operator_new (used by 00dfa460)
    int  v0;                     // +0x00
    int  v4;                     // +0x04
    int  v8;                     // +0x08
    int  vc;                     // +0x0c
    char v10;                    // +0x10
};
struct GGUI {
    void*    mVftable;           // +0x000
    char     pad04[0x04];        // +0x004..+0x007
    char     mBase8[0x04];       // +0x008..+0x00b  (second-base subobject; &mBase8 == this+8)
    Item*    mItemBegin;         // +0x00c
    Item*    mItemEnd;           // +0x010
    char     pad14[0x0c];        // +0x014..+0x01f
    Stopwatch_s00df_9650 mTimer20;          // +0x020  (mUnits doubles as the UI state)
    char     pad24[0x08];        // +0x024..+0x02b
    int      mIndex;             // +0x02c
    unsigned mCount;             // +0x030
    int      mCur;               // +0x034
    char     pad38[0x10];        // +0x038..+0x047
    SPUILayout_s00df_9650 mLayout;          // +0x048
    int      m60;                // +0x060
    int      m64;                // +0x064
    int      m68;                // +0x068
    int      m6c;                // +0x06c
    Stopwatch_s00df_9650 mTimer70;          // +0x070  (mUnits selects rdtsc vs QPC)
    char     pad74[0x04];        // +0x074
    int      m78;                // +0x078
    char     m7c;                // +0x07c
    char     m7d;                // +0x07d
    char     m7e;                // +0x07e
    char     m7f;                // +0x07f
    char     pad80[0x0c];        // +0x080..+0x08b
    PropKey  m8c;                // +0x08c..+0x0a3
    int      mA4;                // +0x0a4
    int      mA8;                // +0x0a8
    int      mAC;                // +0x0ac
    char     mB0[0x10];          // +0x0b0..+0x0bf
    Slot     mSlots[3];          // +0x0c0..+0x167
    void*    m168;               // +0x168
    void*    m16c;               // +0x16c

    void      FUN_00df95d0();                            // 0x00df95d0
    void      FUN_00df6c40();                            // 0x00df6c40
    void      FUN_00df6980();                            // 0x00df6980
    void      FUN_00df97d0();                            // 0x00df97d0
    void      FUN_00df9770();                            // 0x00df9770
    void      FUN_00df97e0();                            // 0x00df97e0
    void      FUN_00df9850(unsigned index);              // 0x00df9850
    void      FUN_00df98f0();                            // 0x00df98f0
    void      FUN_00df9ad0();                            // 0x00df9ad0
    void      FUN_00df9b30(int v);                       // 0x00df9b30
    void      FUN_00df9c80(unsigned id);                 // 0x00df9c80
    void      FUN_00df9d20(void* v);                     // 0x00df9d20
    void      FUN_00df9dc0(unsigned index, int v);       // 0x00df9dc0
    void      FUN_00df9e60();                            // 0x00df9e60
    void      FUN_00df9ef0();                            // 0x00df9ef0
    void      FUN_00df9be0();                            // 0x00df9be0
    void      FUN_00df9fc0();                            // 0x00df9fc0
    void      FUN_00dfa460(int*, unsigned char);         // 0x00dfa460
    void      FUN_00df8330();                            // 0x00df8330
    void      FUN_00df9650();                            // 0x00df9650
    void      FUN_00e00640();                            // 0x00e00640
};
void __fastcall FUN_00df9990(GGUI* p);
void __fastcall FUN_00df9a00(GGUI* p);
void __fastcall FUN_00df9a70(GGUI* p);
// ---- items of slice s00df9650 end

// ---- items of slice s00dff790 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl SP_AssetBrowser();
extern "C" void* __cdecl SP_SporeGuide();
extern "C" void* __cdecl SP_GetCurrentGameMode();
extern "C" void  __cdecl sub_644b10(void*);
extern "C" void  __cdecl sub_644b60(void*);
extern "C" void  __cdecl sub_e02040(void*);
extern "C" void  __cdecl sub_ec5a60(void*, int, int);
extern "C" void* __cdecl sub_67dcd0();                       // EA::ResourceMan::GetManager
extern "C" int   __cdecl sub_dfa370();
extern "C" void* __cdecl sub_ef19f0();
extern "C" int   __cdecl sub_b3d410();                       // *(int*)0x167eb28
extern "C" int   __cdecl sub_dd9190();                       // *(int*)0x16a0b08
extern "C" int   __cdecl sub_401090();                       // GetSetting9
extern "C" int   __cdecl sub_eed920(void*, void*);           // SetIntProperty(key, wstr)
extern "C" int   __cdecl sub_de3f00(void*, void*, int);
extern "C" void* __cdecl sub_dff2b0(void* src, void* srcEnd, void* dst);
extern "C" void* __cdecl sub_dff2f0(void* src, void* srcEnd, void* dst);
extern "C" void* __cdecl sub_dff4a0(void** slot, void* src, void* srcEnd, void* dst, void* extra);
extern "C" void* __cdecl sub_dff4e0(void** slot, void* src, void* srcEnd, void* dst, void* extra);
extern "C" void  __cdecl sub_f47380(void* p);                // operator delete
struct EC { char sub_ec4320(); };
struct GObj { char pad_00[0x108]; int field108; char pad_10c[0x270 - 0x10c]; u8 b270; void sub_de52d0(); };
struct VBase {
    void** vftable;              // +0x00
    u8     b4;                   // +0x04
    VBase();
};
struct KeyObj { char pad[0x44]; int key44(); void Dispatch(int, int); };
static inline void releaseHandle(void* p) {
    if (p) ((void (__thiscall*)(void*))(*(void***)p)[1])(p);  // handle->vtable[4]
}
struct Eco {                                     // *(void**)(*(int*)0x16c7aa4 + 0x1c)
    char sub_ec4320();
    char sub_ec5a60(int* key, int a, int b);
};
struct Ctx39 {                                   // *(int*)0x16a1344 + 0x3c
    void sub_de9dc0(int* ev);
};
struct GObj2 {                                   // *(int*)0x16a1344
    void sub_de86d0(int a, int b);
    void sub_de5470(int a);
};
struct X19 {                                     // sub_ef19f0() result
    int f00, f04, f08;
    u8  pad0c[0x0c];
    int f18, f1c, f20;
};
struct Timeline {                                // sub_b3d410() result
    void sub_e3e350(int a, int* key, int b);
};
struct Item_s00df_f790 {                                    // resource item
    void* sub_414e10();                          // GetName
};
struct ClsA { void sub_dda0d0(int v); };
struct ClsB { void sub_ddb760(); };
struct SpeciesMgr { void* sub_4df550(int* key); };
struct Species { void sub_4da330(void* wstr); };
struct WString_s00df_f790 {
    void* b; void* e; void* c;
    void sub_423650(void* first, void* last);    // basic_string<wchar_t>::assign
    WString_s00df_f790& operator=(const WString_s00df_f790& o) {
        if (this != &o) sub_423650(o.b, o.e);
        return *this;
    }
};
struct CStr47a0 {
    u8 raw[0x14];
    int* sub_6b5430(const CStr47a0* src);
    CStr47a0& operator=(const CStr47a0& o) { sub_6b5430(&o); return *this; }
};
struct Pair18 {
    u8 raw[0x38];
    int sub_dfca50(const Pair18* src);
    Pair18& operator=(const Pair18& o) { sub_dfca50(&o); return *this; }
};
struct Buf178 {
    void* begin; void* end; void* cap; u8 raw[0xb4];
    int* sub_dfb720(const Buf178* src);
    Buf178& operator=(const Buf178& o) { sub_dfb720(&o); return *this; }
};
struct Blob23c {
    u8 raw[0x19b8];
    int* sub_dff650(const Blob23c* src);
    Blob23c& operator=(const Blob23c& o) { sub_dff650(&o); return *this; }
};
struct Sub14 {
    u8 raw[0x14];
    int* sub_dff330(const Sub14* src);
    Sub14& operator=(const Sub14& o) { sub_dff330(&o); return *this; }
};
struct G2c10 { Sub14 s; u32 f14; u32 f18; };
struct VecFloatSound {
    void* begin; void* end; void* cap; u8 raw[0x0c];
    int* sub_eae540(const VecFloatSound* src);
    VecFloatSound& operator=(const VecFloatSound& o) { sub_eae540(&o); return *this; }
};
struct KeyVec_s00df_f790 {
    u8 raw[0x14];
    int* sub_6609a0(const KeyVec_s00df_f790* src);
    KeyVec_s00df_f790& operator=(const KeyVec_s00df_f790& o) { sub_6609a0(&o); return *this; }
};
struct PropGroup {
    CStr47a0 cs; WString_s00df_f790 w14; u32 gap20; u32 f24; u32 f28; WString_s00df_f790 w2c; u32 gap38;
};
struct Layout_s00df_f790 {
    u8 raw[0x34];
    void* sub_8105b0(int id, int flag);          // cSPUILayout::FindWindowByID
};
struct Vec27e0 {
    void* begin; void* end; void* cap; u8 pad[0x08];
    void* sub_dff590(unsigned n, void* first, void* last);
    void  sub_dfdf70(void* first, void* last);
    Vec27e0& sub_dff790(const Vec27e0& x);
};
struct Vec27e8 {
    void* begin; void* end; void* cap; u8 pad[0x08];
    void* sub_dff5f0(unsigned n, void* first, void* last);
    void  sub_dfe910(void* first, void* last);
    Vec27e8& sub_dff8e0(const Vec27e8& x);
};
struct PropBaseA22 {
    u8  pad00[0x08];                    // +0x00 (vftable + ...)
    u32 f08;                            // +0x08
    u32 f0c;                            // +0x0c
    u32 f10;                            // +0x10
    u32 f14;                            // +0x14
    Pair18 p18;                         // +0x18
    float f50;                          // +0x50
    float f54;                          // +0x54
    float f58;                          // +0x58
    u8  f5c;                            // +0x5c
    u8  pad5d[0x03];
    float f60;                          // +0x60
    u8  f64;                            // +0x64
    u8  pad65[0x03];
    u32 f68;                            // +0x68
    u32 f6c;
    u32 f70;
    u32 f74;
    u32 f78;                            // +0x78
    PropGroup g7c;                      // +0x7c
    PropGroup gb8;                      // +0xb8
    PropGroup gf4;                      // +0xf4
    u32 blk130[8];                      // +0x130
    u32 f150;                           // +0x150
    u32 f154;
    u32 f158;
    u32 f15c;
    u32 f160;
    u32 f164;
    u32 f168;                           // +0x168
    float f16c;                         // +0x16c
    float f170;                         // +0x170
    u8  f174;                           // +0x174
    u8  f175;                           // +0x175
    u8  pad176[0x02];
    Buf178 b178;                        // +0x178
    u32 f238;                           // +0x238
    Blob23c b23c;                       // +0x23c
    Vec27e8 v2bf4;                      // +0x2bf4
    u8  f2c08;                          // +0x2c08
    u8  pad2c09[0x03];
    u32 f2c0c;                          // +0x2c0c
    G2c10 g2c10;                        // +0x2c10
    u8  f2c2c;                          // +0x2c2c
    u8  f2c2d;                          // +0x2c2d
    u8  pad2c2e[0x02];
    u32 f2c30;                          // +0x2c30
    u32 f2c34;
    u32 f2c38;
    u32 f2c3c;
    u32 f2c40;
    u32 f2c44;
    u32 f2c48;                          // +0x2c48
    float f2c4c;                        // +0x2c4c
    u32 f2c50;                          // +0x2c50
    VecFloatSound v2c54;                // +0x2c54
    Vec27e0 v2c6c;                      // +0x2c6c
    KeyVec_s00df_f790 k2c80;                       // +0x2c80
    u32 f2c94;                          // +0x2c94
    u32 f2c98;
    u32 f2c9c;
    u32 f2ca0;
    u32 f2ca4;
    u32 f2ca8;                          // +0x2ca8

    void sub_f2e7d0();                  // ctor
    void sub_f2b3d0();
    void sub_dfef70();                  // dtor
    PropBaseA22& sub_dffa30(const PropBaseA22& x);
};
struct EditorEntry {
    u32 f00; u32 f04; u32 f08; u8 pad0c[0x14]; u32 f20; u8 pad24[0x14];  // 0x38
};
struct cEditorModeUI_s00df_f790 {
    u8  pad00[0x0c];
    int* p0c;                           // +0x0c
    u8  pad10[0x10];                    // +0x10
    int mode;                           // +0x20
    int prevMode;                       // +0x24
    int f28;                            // +0x28
    int f2c;                            // +0x2c
    int count;                          // +0x30
    u8  pad34[0x14];                    // +0x34
    Layout_s00df_f790 layout;                      // +0x48
    u8  b7c;                            // +0x7c
    u8  b7d;                            // +0x7d
    u8  b7e;                            // +0x7e
    u8  b7f;                            // +0x7f
    u8  pad80[0x04];
    void* p84;                          // +0x84
    u8  pad88[0x04];
    int keyA[3];                        // +0x8c
    int keyB[3];                        // +0x98
    int keyC[3];                        // +0xa4
    u8  padb0[0x10];
    EditorEntry entries[3];             // +0xc0
    WString_s00df_f790 wstr;                       // +0x168

    void sub_e000a0(int* key);
    void sub_e001a0(int* ev);
    bool sub_e002b0(int msg, int* params);
    void sub_dffda0();

    void sub_dfab20(int enabled);       // SetModeEnabled
    void sub_df9dc0(unsigned i, int v);
    void sub_df9c80(int v);
    void sub_df9d20(int* ev);
    void sub_dfaca0(int* ev);           // EnterMode8
    void sub_dfad50(int* ev);           // EnterMode9
    void sub_dfa710(int v);             // TogglePodPanel1
    void sub_dfb0d0(void* buf);         // Update
    void sub_df98f0();
};
// ---- items of slice s00dff790 end

// ---- items of slice s01364b20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int      __cdecl atexit(void (__cdecl*)());
extern "C" uint32_t __cdecl FNVHash(const char* name, uint32_t seed, int lowercased);  // 0x00932e80
extern const char g_propKey147d3b8;                        // 0x0147d3b8
extern void FUN_013c6000();                                // 0x013c6000 atexit destructor
#pragma warning(disable: 4100)
struct PropertyNode {
    const char*  mpKey;                                    // +0x00
    uint32_t     mHash;                                    // +0x04
    PropertyNode* mpNext;                                  // +0x08
};
struct GGEProperty : PropertyNode {                        // 0x18 bytes
    float        mValue0c;                                 // +0x0c
    float        mValue10;                                 // +0x10
    float        mValue14;                                 // +0x14
};
extern PropertyNode* sGGEProperties;                       // 0x015a2ff8
extern GGEProperty  kImpostorOffset;                       // 0x016a0dc4
// ---- items of slice s01364b20 end

// ---- items of slice s006775f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct RectF {
    float mLeft, mTop, mRight, mBottom;
    int Contains(float x, float y);   // 0x00677E80
};
// ---- items of slice s006775f0 end

// ---- items of slice s00ddcdc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned int n);   // CRT memcpy (0x011e0744)
extern "C" void* __cdecl G7New(unsigned int size, const char* name, int a, int b, int c, int d);  // 0x00f473a0
extern "C" void* __fastcall FUN_00dda920(void* mem);                                             // 0x00dda920
extern "C" int   __stdcall  FUN_00b3d230(int v);                                                 // 0x00b3d230
extern "C" void  __fastcall FUN_00b5e9a0(int v);                                                 // 0x00b5e9a0
extern "C" void* __cdecl    FUN_006895b0();                                                      // 0x006895b0
extern const char gSimulatorName[];   // "Simulator"          @ 0x013f09b4
extern const char gPatchMgrName[];    // "UI/GGE/PatchManager" @ 0x0147d3a4
extern char gCheatArg;                // 0x0147d2ec
extern unsigned char gFlag0c80;       // 0x016a0c80
extern "C" unsigned __int64 __cdecl __rdtsc();
#pragma intrinsic(memcpy)
#pragma intrinsic(__rdtsc)
inline void* operator new(unsigned int, void* p) { return p; }
void __cdecl EASTL_allocator_deallocate(void* p);                               // 0x00f47380
#define V1(n) virtual void n();
#define V4(p) V1(p##0) V1(p##1) V1(p##2) V1(p##3)
#define V16(p) V4(p##0) V4(p##1) V4(p##2) V4(p##3)
template <class T>
struct AutoRef {
    T* mp;
    AutoRef() : mp(0) {}
    AutoRef& operator=(T* p)
    {
        T* old = mp;
        if (p != old) {
            if (p) p->AddRef();
            mp = p;
            if (old) old->Release();
        }
        return *this;
    }
    T* operator->() const { return mp; }
    T** AsOutParam()
    {
        if (mp) {
            T* t = mp;
            mp = 0;
            t->Release();
        }
        return &mp;
    }
    ~AutoRef() { if (mp) mp->Release(); }
};
struct IRef {
    virtual int AddRef();       // +0x00
    virtual int Release();      // +0x04
};
struct ILight : IRef {
    V4(l0) V4(l1) V1(l2) V1(l3)                                   // slots 2..11
    virtual void SetName(uint32_t id);                            // +0x30
};
struct ILayer : IRef {
    V4(y0) V1(y1)                                                 // slots 2..6
    virtual void AddModel(void* model, int a, int b, int c, int d);   // +0x1c
};
struct IModel : IRef {
    V16(m0) V16(m1) V16(m2) V16(m3) V4(m4) V4(m5) V1(m6) V1(m7) V1(m8)   // slots 2..76
    virtual void SetFlag(int on);                                 // +0x134
    V1(m9)                                                        // +0x138
    virtual int GetModelType(int a, int b);                       // +0x13c
    virtual void Attach(ILight* light, int a, int b);             // +0x140
};
struct sp_vector_allocator {
    const char* mpName;
    uint32_t mFlags;
    sp_vector_allocator() {}
};
inline void FreeArray(void* p)
{
    if (p) {
        if (((int*)p)[-1])
            EASTL_allocator_deallocate(p);
    }
}
namespace SP {
namespace FunctionalMatch {
struct Constraint_s00dd_cdc0;
}
}
struct ConstraintVec {
    SP::FunctionalMatch::Constraint_s00dd_cdc0* mpBegin;
    SP::FunctionalMatch::Constraint_s00dd_cdc0* mpEnd;
    SP::FunctionalMatch::Constraint_s00dd_cdc0* mpCapacity;
    sp_vector_allocator mAllocator;
    ConstraintVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~ConstraintVec();
    void DoDestroyValues(SP::FunctionalMatch::Constraint_s00dd_cdc0* first, SP::FunctionalMatch::Constraint_s00dd_cdc0* last);  // 0x004e39a0
    void DoInsertValue(SP::FunctionalMatch::Constraint_s00dd_cdc0* pos, const SP::FunctionalMatch::Constraint_s00dd_cdc0& v);   // 0x004e39d0
    void push_back(const SP::FunctionalMatch::Constraint_s00dd_cdc0& value);
};
namespace SP {
namespace FunctionalMatch {
enum EqualConstraint_s00dd_cdc0 { kEquals_s00dd_cdc0 = 0 };
}
}
namespace SP {
namespace FunctionalMatch {
struct Constraint_s00dd_cdc0 {
    unsigned int mParameter;
    int mType;
    int mMin;
    int mMax;
    ConstraintVec mConstraints;
    Constraint_s00dd_cdc0(unsigned int param, EqualConstraint_s00dd_cdc0, int value);   // 0x00558960
    Constraint_s00dd_cdc0(const Constraint_s00dd_cdc0& other);                          // 0x00606880
    ~Constraint_s00dd_cdc0()
    {
        mConstraints.DoDestroyValues(mConstraints.mpBegin, mConstraints.mpEnd);
        FreeArray(mConstraints.mpBegin);
    }
};
}
}
inline void ConstraintVec::push_back(const SP::FunctionalMatch::Constraint_s00dd_cdc0& value)
{
    if (mpEnd < mpCapacity)
        ::new (mpEnd++) SP::FunctionalMatch::Constraint_s00dd_cdc0(value);
    else
        DoInsertValue(mpEnd, value);
}
inline ConstraintVec::~ConstraintVec()
{
    DoDestroyValues(mpBegin, mpEnd);
    FreeArray(mpBegin);
}
struct ResourceKey_s00dd_cdc0 {
    uint32_t mInstanceID, mTypeID, mGroupID;
};
struct KeyVec_s00dd_cdc0 {
    ResourceKey_s00dd_cdc0* mpBegin;
    ResourceKey_s00dd_cdc0* mpEnd;
    ResourceKey_s00dd_cdc0* mpCapacity;
    sp_vector_allocator mAllocator;
    KeyVec_s00dd_cdc0() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~KeyVec_s00dd_cdc0() { FreeArray(mpBegin); }
};
class cISPObjectTemplateDB_s00dd_cdc0 {
public:
    V4(d0) V4(d1) V4(d2) V1(d3) V1(d4)                            // slots 0..13
    virtual void FindAssets(KeyVec_s00dd_cdc0& results, const ConstraintVec& query);   // +0x38
};
cISPObjectTemplateDB_s00dd_cdc0* ObjectTemplateDB_s00dd_cdc0();                         // 0x0067cb40
struct cModelSetup {
    uint32_t pad0[0x14 / 4];
    AutoRef<IModel> mModelC;         // +0x14
    AutoRef<IModel> mModelA;         // +0x18
    AutoRef<IModel> mModelB;         // +0x1c
    AutoRef<ILight> mLight;          // +0x20
    uint32_t pad24[(0x70 - 0x24) / 4];
    AutoRef<ILayer> mLayer;          // +0x70

    void Setup();
};
void* __cdecl WindowManager();                                                                   // 0x0067caa0
void* __cdecl GetLayoutManager();                                                                // 0x00805070

void  __fastcall FUN_00c2e4e0(void* p);                                                          // 0x00c2e4e0
void  __fastcall FUN_00e20800(void* p);                                                          // 0x00e20800
void* __fastcall FUN_00e20780(void* mem);                                                        // 0x00e20780
extern cModelSetup* gSimulator;       // 0x016a0b08
inline void* VFn(void* p, int off) { return *(void**)(*(char**)p + off); }
struct PanelOps {
    void M4450(int a, float b, float c, int d);   // 0x00de4450
    void M44a0(int a, float b, float c, int d);   // 0x00de44a0
    void M44f0(float a, float b, int c);          // 0x00de44f0
    void M8760(float a, float b);                 // 0x00de8760
    void Ma200();                                 // 0x00dea200
    int  M81b0();                                 // 0x00de81b0
    void M7eb0();                                 // 0x00de7eb0
};
struct cGUIPanel {
    int  m0;                   // +0x00
    void* mSubVt;              // +0x04
    char mPad08[0x38 - 0x08];
    void* mp38;                // +0x38
    char mPad3c[0x108 - 0x3c];
    int  mState;               // +0x108
    int  mState2;              // +0x10c
    char mPad110[0x178 - 0x110];
    void* mp178;               // +0x178
    unsigned char mFlag17c;    // +0x17c
};
extern cGUIPanel* kGUI_PanelIDs_s00dd_cdc0;   // 0x016a1344
struct cGUIHandler {
    char mPad0c[0xc];
    void* mp0c;                // +0x0c
};
struct LayoutOps {
    char Is(int id);           // 0x00810760
    void M660(int id, int v);  // 0x00810660
};
// ---- items of slice s00ddcdc0 end

// ---- items of slice s00de1710 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int* sAppPreferences;                // 0x015fd91c  SP::_sAppPreferences
extern "C" void __cdecl operator_delete(void*);              // 0x00f47380  ??3@YAXPAX@Z
extern int* kGUI_PanelIDs_s00de_1710;                  // 0x016a1344  the GUI panel base pointer
struct Layout_s00de_1710 {
    int* FindWindowByID(int id, int flag);          // 0x008105b0  __thiscall
};
struct GlobalUI_s00de_1710 {
    int* FindWindowByID(int id);                    // 0x00e012b0  __thiscall
    void SetVisibility(int v);                      // 0x00e01350  __thiscall
};
void  __cdecl SP_cSPUISpace_KillSetiEffects(int, int);      // 0x00435ed0
void  __cdecl SP_cSPUIAssetBrowser_AdvancedLaunch(void*);   // 0x0064a990
void  __cdecl FUN_00de53d0(int);                            // 0x00de53d0  (ecx = kGUI_PanelIDs)
void  __cdecl FUN_00644b10();                               // 0x00644b10
int   __cdecl FUN_00644b60();                               // 0x00644b60
void  __cdecl FUN_005dd750(void*);                          // 0x005dd750
void  __cdecl FUN_00407190(void*, int, void*);              // 0x00407190  GetBoolProperty
int*  __cdecl SP_GetSaveArea(int, int);                     // SP::GetSaveArea
void  __cdecl EA_Variant_Destruct(void*, int);              // EA::Variant::Destruct
void  __cdecl EA_Stopwatch_SetUnits(void*, int);            // 0x0093a1a0
void  __fastcall SP_cString_dtor(void*);                   // 0x006b5240
int*  __cdecl FUN_00dd9190(int, int);                       // 0x00dd9190  __stdcall
struct HT {
    void find(void*, void*);                                // 0x00aea1b0  eastl hashtable::find
};
struct SG {
    void  FUN_00de11a0();                                   // 0x00de11a0
    char  FUN_00de13d0(int, int);                           // 0x00de13d0
    void  FUN_00de0ae0(int);                                // 0x00de0ae0  $E441
    void  FUN_00de0670(int, int);                           // 0x00de0670
    void  FUN_00de5330(int);                                // 0x00de5330
    void  FUN_00de5260();                                   // 0x00de5260
    void  FUN_00de5300();                                   // 0x00de5300
    void  FUN_00dda090();                                   // 0x00dda090
    void  FUN_00de1a90(int);
    bool  FUN_00de1ae0(int, void*);
    void  FUN_00de1e50(float, float, int);
    void  FUN_00de20e0(int);
    void  FUN_00de2180(float, float, int);
};
// ---- items of slice s00de1710 end

// ---- items of slice s00de23a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint8_t gCalloutWindowsEnabled;       // 0x016a0e68
extern uint32_t gHintWindowId;               // 0x016a0e88
extern float gCalloutFadePeriod;             // 0x016a0f48
extern float gCalloutSpinRate;               // 0x016a114c
extern float gCalloutSpinBias;               // 0x016a0f58
extern float gCalloutTimeout;                // 0x016a0ed8
extern uint32_t gCalloutMessageSpec;  // 0x015a3328
extern uint32_t gGalaxyMessageSpec;   // 0x015a331c
extern const wchar_t gEmptyString16[];   // 0x01667bac
#define VSLOT(n) virtual void _v##n();
struct Vector3_s00de_23a0 {
    float x, y, z;
    Vector3_s00de_23a0() {}
    Vector3_s00de_23a0(float fX, float fY, float fZ) : x(fX), y(fY), z(fZ) {}
};
struct Matrix3 {
    float m[3][3];
};
struct XformMsg {
    uint16_t mnFlags;       // +0x00
    uint16_t mnVersion;     // +0x02
    Vector3_s00de_23a0 mPos;           // +0x04
    float mfScale;          // +0x10
    Matrix3 mMatrix;        // +0x14
};
namespace EA {
// 4-byte alignment: the timer sits at +0x08 behind a vfptr and a byte flag (the slice packs it with #pragma pack(push, 4))
#pragma pack(push, 4)
class Stopwatch_s00de_23a0 {
public:
    enum Units { kUnitsCycles = 0, kUnitsMilliseconds = 4, kUnitsSeconds = 5 };
    Stopwatch_s00de_23a0(int nUnits, bool bStartImmediately);   // 0x0093A560
    int64_t GetElapsedTime() const;                  // 0x0093A3A0
    void SetUnits(int nUnits);                       // 0x0093A1A0
    void Reset();                                    // 0x0093A2E0
    uint64_t mnStartTime;         // +0x00
    uint64_t mnTotalElapsedTime;  // +0x08
    int32_t mnUnits;              // +0x10
    float mfUnitsPerCycle;        // +0x14
};
#pragma pack(pop)
}  // namespace EA
class IRefCounted {
public:
    VSLOT(0)
    virtual int Release();                                          // +0x04
};
class IVisualEffect {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5)
    virtual void SetTransform(const XformMsg* pMsg);                  // +0x18
};
class cPropertyList_s00de_23a0 : public IRefCounted {
public:
};
class cPropertyManager_s00de_23a0 {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9)
    VSLOT(10)
    virtual bool GetProperty(void* pObject, int32_t nFlags, cPropertyList_s00de_23a0** ppList);  // +0x2c
};
template <class T>
class AutoRefCount {
public:
    AutoRefCount() : mpObject(0) {}
    AutoRefCount& operator=(T* pObject) {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    T* mpObject;
};
namespace SP {
cPropertyManager_s00de_23a0* PropertyManager();                                             // 0x0067de30
}
namespace SP {
bool GetPropertyAsUint32Array(cPropertyList_s00de_23a0* pList, uint32_t nProperty,
                              int32_t* pnCount, uint32_t** ppValues);            // 0x006a0840
}
namespace SP {
bool GetPropertyAsString16(cPropertyList_s00de_23a0* pList, uint32_t nProperty,
                           const wchar_t** ppString);                            // 0x006a1400
}
namespace SP {
uint32_t FNV1_String16(const wchar_t* pString, uint32_t nSeed, uint32_t nSalt);  // 0x00932f30
}
namespace SP {
class cString_s00de_23a0 {
public:
    cString_s00de_23a0(uint32_t nTable, uint32_t nKey, const wchar_t* pString);
    cString_s00de_23a0(const cString_s00de_23a0& other);   // 0x006b56f0
    ~cString_s00de_23a0();                      // 0x006b5240
    uint32_t mnTable;                // +0x00
    uint32_t mnKey;                  // +0x04
};
}
namespace SP {
void InsertStringEntry(void* pTable, uint32_t nKey, const cString_s00de_23a0& value, bool bFlag);  // 0x00de19a0
}
namespace SP {
void DeleteArray(void* pBlock);                                                          // 0x00f47380
}
struct sHashNode;
extern sHashNode* gEmptyBucketArray[1];   // 0x0154df28
struct sU32List {
    uint32_t* mpBegin;      // +0x00
    uint32_t* mpEnd;        // +0x04
    uint32_t* mpCapacity;   // +0x08
    uint32_t* InsertAt(uint32_t* pWhere, const uint32_t* pValue);   // 0x004558a0
};
struct sHashNode {
    uint32_t mnKey;         // +0x00
    sU32List mValues;       // +0x04
    uint32_t mnPad10;       // +0x10
    uint32_t mnPad14;       // +0x14
    sHashNode* mpNext;      // +0x18
};
struct sTableIterator {
    sHashNode* mpNode;      // +0x00
    sHashNode** mppBucket;  // +0x04
};
struct sKeyValuePair {
    uint32_t mnKey;         // +0x00
    sU32List mValues;       // +0x04
};
struct sInsertResult {
    sHashNode* mpNode;      // +0x00
    sHashNode** mppBucket;  // +0x04
    uint8_t mbInserted;     // +0x08
    uint8_t mnPad09[0x03];  // +0x09
};
inline void FreeU32List(sU32List& list) {
    if (list.mpBegin) {
        int32_t* pHeader = (int32_t*)list.mpBegin - 1;
        if (*pHeader != 0)
            SP::DeleteArray(list.mpBegin);
    }
    list.mpBegin = 0;
    list.mpEnd = 0;
    list.mpCapacity = 0;
}
struct sHashTable {
    uint32_t mnFlags;         // +0x00  (left untouched by the ctor)
    sHashNode** mpBuckets;    // +0x04
    uint32_t mnBucketCount;   // +0x08
    uint32_t mnElementCount;  // +0x0c
    float mfMaxLoadFactor;    // +0x10
    float mfGrowthFactor;     // +0x14
    uint32_t mnPad18;         // +0x18
    uint32_t mnPad1c;         // +0x1c
    sHashTable() : mfMaxLoadFactor(1.0f), mfGrowthFactor(2.0f), mnElementCount(0),
                   mnPad18(0), mnBucketCount(1), mpBuckets(gEmptyBucketArray) {}
    void Find(sTableIterator* pIt, const uint32_t* pKey) const;           // 0x00aea1b0
    void Insert(sInsertResult* pOut, const sKeyValuePair* pPair, bool bFindExisting); // 0x00aeb960
    void DestroyBuckets(sHashNode** pBuckets, uint32_t nBucketCount);     // 0x00aeb030
    void DestroyStringBuckets(sHashNode** pBuckets, uint32_t nBucketCount); // 0x00de2350
    void Reset() {
        DestroyBuckets(mpBuckets, mnBucketCount);
        mnElementCount = 0;
    }
    void ResetStrings() {
        DestroyStringBuckets(mpBuckets, mnBucketCount);
        mnElementCount = 0;
    }
    void Free() {
        DestroyBuckets(mpBuckets, mnBucketCount);
        mnElementCount = 0;
        if (mnBucketCount > 1)
            SP::DeleteArray(mpBuckets);
    }
    void FreeStrings() {
        DestroyStringBuckets(mpBuckets, mnBucketCount);
        mnElementCount = 0;
        if (mnBucketCount > 1)
            SP::DeleteArray(mpBuckets);
    }
};
class cPropertyTableTriple {
public:
    sHashTable mTable0;     // +0x00
    sHashTable mTable1;     // +0x20
    sHashTable mTable2;     // +0x40
    cPropertyTableTriple() {}   // inlined into 0x00de2d00
    void LoadStringPairs(uint32_t nObject, uint32_t nProperty);   // 0x00de28f0
    void Clear();                                                 // 0x00de29f0
    void Destroy();                                               // 0x00de2a50
    void AddValue1(uint32_t nKey, uint32_t nValue);               // 0x00de2ae0
    void AddValue0(uint32_t nKey, uint32_t nValue);               // 0x00de2bf0
    void LoadGroup0(uint32_t nObject, uint32_t nProperty);        // 0x00de2e20
    void LoadGroup1(uint32_t nObject, uint32_t nProperty);        // 0x00de2ed0
};
class cUIPropertyBase {
public:
    cUIPropertyBase();
};
class cUIPropertyTableSet : public cUIPropertyBase {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9)
    VSLOT(10) VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15) VSLOT(16) VSLOT(17) VSLOT(18)
    VSLOT(19) VSLOT(20) VSLOT(21) VSLOT(22) VSLOT(23) VSLOT(24) VSLOT(25) VSLOT(26)
    virtual ~cUIPropertyTableSet();                               // 0x00de2de0
    cUIPropertyTableSet();                                        // 0x00de2d00
    void Init();                                                  // 0x00de2f80
    uint32_t mnPad04;               // +0x04 (never touched)
    EA::Stopwatch_s00de_23a0 mTimer;           // +0x08
    uint32_t mnPad20;               // +0x20
    uint32_t mnPad24;               // +0x24
    uint32_t mnPad28;               // +0x28
    uint32_t mnPad2c;               // +0x2c
    uint32_t mnPad30;               // +0x30
    IRefCounted* mpListener;        // +0x34
    uint32_t mnPad38;               // +0x38
    uint32_t mnPad3c;               // +0x3c
    cPropertyTableTriple mTables;   // +0x40
    uint8_t mbA0;                   // +0xa0
    uint32_t mnPadA4;               // +0xa4
    uint32_t mnPadA8;               // +0xa8
    uint32_t mnPadAC;               // +0xac
    void* mpB0;                     // +0xb0
    uint32_t mnPadB4;               // +0xb4
    EA::Stopwatch_s00de_23a0 mTimer2;          // +0xb8
    uint8_t mbD0;                   // +0xd0
    uint32_t mnPadD4;               // +0xd4
    uint32_t mnPadD8;               // +0xd8
    uint32_t mnPadDC;               // +0xdc
    uint32_t mnPadE0;               // +0xe0
};
class cUIWindow_s00de_23a0;
class cStarEntry;
class cWindowManager {
public:
    cUIWindow_s00de_23a0* FindWindowByID(uint32_t nID);    // 0x00e012b0
    void* GetActiveXform();                     // 0x0093b6c0
};
class cSPUIGlobalUI_s00de_23a0 {
public:
    uint8_t mnPad000[0x101];        // +0x000
    uint8_t mbMenuActive;           // +0x101
    uint8_t mbOverlayActive;        // +0x102
    uint8_t mnPad103[0x05];         // +0x103
    int32_t mnMode;                 // +0x108
    uint8_t mnPad10c[0x78];         // +0x10c
    cWindowManager* mpWindows;      // +0x184
    uint8_t mnPad188[0x50];         // +0x188
    cStarEntry** mppStars;          // +0x1d8
    cStarEntry** mppStarsEnd;       // +0x1dc
    cStarEntry** mppStarsCapacity;  // +0x1e0
    uint8_t mnPad1e4[0x0d];         // +0x1e4
    uint8_t mbNoCallouts;           // +0x1f1
    uint8_t mnPad1f2[0x7e];         // +0x1f2
    uint8_t mbGalaxyOpen;           // +0x270
    void SetCalloutEnabled(int bEnabled);          // 0x00de53d0
    void SetEditorMode(int nMode, int nArg);       // 0x00de86d0
    void UpdateCalloutWindows();                   // 0x00de5260
};
extern cSPUIGlobalUI_s00de_23a0* gUI;                   // 0x016a1344
extern Matrix3 gCalloutMatrix;               // 0x016a1184
extern Vector3_s00de_23a0 gCalloutTranslation;          // 0x016a11a8
struct cAppSettings {
    uint8_t mnPad00[0x1c];      // +0x00
    uint8_t mbFreeCam;          // +0x1c
};
cAppSettings* GetSetting3_s00de_23a0();                    // 0x00401030
class cUIWindow_s00de_23a0 {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9)
    virtual bool IsPlaying();                                  // +0x28
    VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15) VSLOT(16) VSLOT(17) VSLOT(18) VSLOT(19)
    VSLOT(20) VSLOT(21) VSLOT(22) VSLOT(23) VSLOT(24) VSLOT(25) VSLOT(26) VSLOT(27) VSLOT(28)
    VSLOT(29) VSLOT(30)
    virtual void SetVisible(bool bVisible, bool bFlag);        // +0x7c
};
void SetWindowScale(cUIWindow_s00de_23a0* pWindow, float fX, float fY);     // 0x00808190
void CalloutMessageBox(void* pOwner, const void* pMsgSpec);      // 0x00809db0
void GetCameraBasis(float* pfA, float* pfB);                     // 0x00804ed0
struct sPositionEvent {
    int32_t mFrom[3];       // +0x00
    int32_t mTo[3];         // +0x0c
    int32_t mnPad18;        // +0x18
    int32_t mnPad1c;        // +0x1c
    int32_t mnPad20;        // +0x20
    int32_t mnType;         // +0x24
    int32_t mnPad28;        // +0x28
};
sPositionEvent* ResetPositionEvent();                            // 0x00ef19f0
class cEventDispatcher {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9)
    virtual void Dispatch(uint32_t nEventId);                    // +0x28
};
cEventDispatcher* GetEventDispatcher();                          // 0x0067dd20
class cUICalloutSequencer {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9)
    VSLOT(10) VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15) VSLOT(16) VSLOT(17) VSLOT(18)
    VSLOT(19) VSLOT(20) VSLOT(21) VSLOT(22)
    virtual void OnCalloutEnded();                                // +0x5c
    void Update(float fDeltaTime);                                // 0x00de23a0
    uint8_t mbBlocked;              // +0x04
    uint8_t mnPad05[0x03];          // +0x05
    EA::Stopwatch_s00de_23a0 mTimer;           // +0x08
    uint8_t mbStarted;              // +0x20
    uint8_t mbPreviousFreeCam;      // +0x21
    uint8_t mnPad22[0x02];          // +0x22
    int32_t mnValue24;              // +0x24
    int32_t mnValue28;              // +0x28
    int32_t mnValue2C;              // +0x2c
    int32_t mnCountdown;            // +0x30
    IVisualEffect* mpEffect;        // +0x34
    uint32_t mnEventID;             // +0x38
    uint32_t mnPad3C;               // +0x3c
    uint32_t mnPad40;               // +0x40
    uint32_t mnPad44;               // +0x44
    void* mpOwner;                  // +0x48
    uint8_t mnPad4C[0x54];          // +0x4c
    uint8_t mbA0;                   // +0xa0
    uint8_t mnPadA1[0x03];          // +0xa1
    uint32_t mnPadA4;               // +0xa4
    uint32_t mnPadA8;               // +0xa8
    uint32_t mnPadAC;               // +0xac
    void* mpB0;                     // +0xb0
    uint32_t mnPadB4;               // +0xb4
    EA::Stopwatch_s00de_23a0 mTimer2;          // +0xb8
    uint8_t mbD0;                   // +0xd0
};
void PostCalloutXform(void* pXform, float fA, float fB, uint32_t nEventID);   // 0x00de2180
class cEffectSet;
struct cCalloutOwner {
    uint32_t mnID;              // +0x00
    uint8_t mnPad04[0xb4];      // +0x04
    cEffectSet* mpEffectSet;    // +0xb8
};
class cPlanetRecord_s00de_23a0 {
public:
    void Setup();                                             // 0x00b28850
};
cPlanetRecord_s00de_23a0* __stdcall GetPlanetRecord(uint32_t nID);       // 0x00b3d340 (callee pops its arg)
class cStarManager_s00de_23a0 {
public:
    void UpdateRolloverStars();                               // 0x00bb6040
    void UpdateStarEffects();                                 // 0x00bb7620
};
cStarManager_s00de_23a0* StarManager();                                  // 0x00b3d2a0
class cLocalPlayer {
public:
    bool FindLocal(uint32_t nID);                             // 0x00801bb0
};
cLocalPlayer* __stdcall GetLocalPlayer(uint32_t nID);         // 0x0067cab0 (callee pops its arg)
class cEffectSet {
public:
    void SetFlag(int nFlag);                                  // 0x00df6850
    void Highlight(int nFlag);                                // 0x00df6700
};
class cRolloverManager {
public:
    void SetupRolloverStarEffects();                          // 0x00df8330
};
cRolloverManager* GetRolloverManager();                       // 0x00df5f40
void* GetGameData();                                          // 0x0067de40
class cGameDataIface {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
    virtual cGameDataIface* GetSub();                         // +0x20
    VSLOT(9) VSLOT(10) VSLOT(11) VSLOT(12)
    virtual void SetStar(uint32_t nID, bool bValue);           // +0x34
};
class cStarEntry {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9)
    VSLOT(10) VSLOT(11)
    virtual void SetFlag(int nFlag);                          // +0x30
};
class cUIHintTrigger {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9)
    VSLOT(10) VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15) VSLOT(16) VSLOT(17) VSLOT(18)
    VSLOT(19) VSLOT(20) VSLOT(21) VSLOT(22)
    virtual void OnTriggerEnded();                            // +0x5c
    void Tick(float fDeltaTime);                              // 0x00de3130
    void Close();                                             // 0x00de3240
    uint32_t mnPad04;           // +0x04 (never touched)
    EA::Stopwatch_s00de_23a0 mTimer;       // +0x08
    uint32_t mnValue20;         // +0x20
    uint8_t mnPad24[0x1c];      // +0x24
    int32_t mnCountdown;        // +0x40
    uint32_t mnCalloutID;       // +0x44
    cCalloutOwner* mpOwner;     // +0x48
};
struct sString16 {
    const wchar_t* mpBegin;      // +0x00
    const wchar_t* mpCapacity;   // +0x04
    const wchar_t* mpEnd;        // +0x08
    sString16() {
        mpBegin = gEmptyString16;
        mpCapacity = gEmptyString16;
        mpEnd = gEmptyString16 + 1;
    }
    ~sString16() {
        if ((((uint32_t)mpEnd - (uint32_t)mpBegin) & 0xfffffffe) > 2)
            SP::DeleteArray((void*)mpBegin);
    }
};
extern cPropertyList_s00de_23a0* gScriptProperties;   // 0x015a2df8
// ---- items of slice s00de23a0 end

// ---- items of slice s00de41b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl FUN_00f47380(void* pBlock);                                       // 0x00f47380 operator delete
extern "C" void  __cdecl FUN_00806e40(void* pWindow, int nA, int nB);                      // 0x00806e40 AutoSizeWindowForText
extern "C" void  __cdecl FUN_00806ee0(void* pWindow, float fDelta);                        // 0x00806ee0
extern "C" void  __cdecl FUN_0093aa70(void* pStream, void* pValue, int nCount, int nEndian); // 0x0093aa70 EA::IO::WriteUint32
extern "C" void  __cdecl FUN_00ae2e40(void* pStream, void* pValue);                        // 0x00ae2e40
extern "C" void* __cdecl FUN_00921580(void* pNode);                                        // 0x00921580 RBTreeIncrement
extern "C" bool  __cdecl FUN_00685520(int nFlag);                                          // 0x00685520 IsWorldLayoutFlagSet
extern "C" char  __cdecl FUN_00809db0(void* pA, void* pB);                                 // 0x00809db0 UI::CalloutMessageBox
extern "C" void* __cdecl FUN_00688fa0(const wchar_t* szName);                              // 0x00688fa0 open file
extern "C" void  __cdecl FUN_006891f0(const wchar_t* szFrom, const wchar_t* szTo);          // 0x006891f0 commit/rename
extern "C" void* __cdecl FUN_009512c0();                                                   // 0x009512c0 heap
extern "C" void* __cdecl FUN_009512d0(int nSize, int nAlign, const char* szTag, void* pHeap); // 0x009512d0 allocate
extern "C" void* __cdecl FUN_00b3d2a0();                                                   // 0x00b3d2a0 SP::StarManager
extern "C" void* __cdecl FUN_00b3d4d0();                                                   // 0x00b3d4d0 trigger manager
extern "C" void* __cdecl FUN_0067dd10();                                                   // 0x0067dd10 SP::App
extern "C" void* __cdecl FUN_0067ddd0();                                                   // 0x0067ddd0 SP::EffectsManager
extern "C" void* __cdecl FUN_0067cad0();                                                   // 0x0067cad0 SP::AddBoundingBox
extern uint8_t         g_bGalaxyActive;                // 0x016a1348
extern void*           g_p16a0d18;                     // 0x016a0d18
extern uint32_t        g_dw1897c18;                    // 0x01897c18
extern uint32_t        g_dw15a38b8;                    // 0x015a38b8
extern uint32_t        g_dw15a41d4;                    // 0x015a41d4
extern uint32_t        g_dw15a3860;                    // 0x015a3860
extern "C" uint32_t __cdecl FUN_00de4e70(uint32_t a, uint32_t b);
typedef unsigned int uint32;
struct Property {
    char pad[0x12];
    short type;                 // +0x12, 9 = int
    int* GetInt();              // thiscall, returns int& (asm: Property::GetInt)
};
struct PropertyList {
    virtual void v0();
    virtual void Release();     // slot 1
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual bool GetProperty(uint32 id, Property** out);  // slot 9 (+0x24)
};
struct PropertyListRef {
    PropertyList* p;
    PropertyListRef() : p(0) {}
    void Reset() {
        if (p) {
            PropertyList* old = p;
            p = 0;
            old->Release();
        }
    }
};
struct PropertyManager_s00de_41b0 {
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
    virtual bool GetPropertyList(uint32 a, uint32 b, PropertyListRef* out);  // slot 11 (+0x2c)
};
PropertyManager_s00de_41b0* GetPropertyManager();   // free function, no args (SP::PropertyManager)
extern "C" void* __cdecl FUN_00b3d230_s00de_41b0();                                                   // 0x00b3d230
class cGalaxyGameEntryImpl_s00de_41b0;
class cSPUILayout_s00de_41b0;
class cSPUIGlobalUI_s00de_41b0;
class tGUIObject;
class cDownloadDialog_s00de_41b0;
class cPanelIDs_s00de_41b0 {                                      // 0x016a1344
public:
    uint8_t  mPad000[0xc8];
    bool     mb0c8;                                    // +0x0c8
    bool     mb0c9;                                    // +0x0c9
    uint8_t  mPad0ca[0x108 - 0xca];
    int32_t  mn108;                                    // +0x108
};
extern cPanelIDs_s00de_41b0*      kGUI_PanelIDs_s00de_41b0;                  // 0x016a1344
extern cDownloadDialog_s00de_41b0* g_pDownloadDialogA;            // 0x016a15f8
extern cDownloadDialog_s00de_41b0* g_pDownloadDialogB;            // 0x016a15f4
class tGUIObject {                                     // an SPUI window / widget
public:
    virtual void        v00();
    virtual void        v04();
    virtual void        v08();
    virtual tGUIObject* v0c(uint32_t nID);             // +0x0c
    virtual void        v10();
    virtual void        v14();
    virtual void        v18();
    virtual void        v1c();
    virtual void        v20();
    virtual void        v24();
    virtual void        v28(int nID, bool bState);              // +0x28
    virtual void        v2c();
    virtual void        v30();
    virtual void        v34();
    virtual float*      v38();                          // +0x38  returns the window rect
    virtual void        v3c();
    virtual void        v40();
    virtual void        v44();
    virtual void        v48();
    virtual void        v4c();
    virtual void        v50();
    virtual void        v54();
    virtual void        v58();
    virtual void        v5c();
    virtual void        v60();
    virtual void        v64();
    virtual void        v68();
    virtual void        v6c(float* pRect);              // +0x6c
    virtual void        v70();
    virtual void        v74(float fA, float fB);        // +0x74
};
class cSPUIGlobalUI_s00de_41b0 {                                  // the global UI
public:
    tGUIObject* __thiscall FindWindowByID(uint32_t nID);           // 0x00e012b0
};
class cSPUILayout_s00de_41b0 {                                     // a named SPUI layout
public:
    uint8_t     mPad00[0x18];
    tGUIObject* __thiscall FindWindowByID(uint32_t nID, int nFlag); // 0x008105b0
};
class tEntryIface38 {                                   // the entry's UI-forwarding interface at +0x38
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual bool v18(uint32_t a, uint32_t b);                       // +0x18
    virtual bool v1c(uint32_t a, uint32_t b);                       // +0x1c
    virtual bool v20(float fA, float fB, int c);                    // +0x20
    virtual bool v24(uint32_t a, float fB, float fC, uint32_t d);   // +0x24
    virtual bool v28(uint32_t a, float fB, float fC, uint32_t d);   // +0x28
    virtual void v2c();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3c();
    virtual void v40(uint32_t a);                                   // +0x40
};
class tEntryIface2c {                                   // the entry's notification sink at +0x2c
public:
    virtual void v0(uint32_t nArg);                                 // +0x00
    virtual void v4(void* pObj, uint32_t nArg);                     // +0x04
};
class tGameMode {                                       // the game-mode object at +0xf0
public:
    uint8_t mPad00[0x3c];
    int32_t mn3c;                                       // +0x3c
    uint8_t mPad40[4];
    uint8_t mObj44[0x10];                               // +0x44  handed to the download dialog
    bool __thiscall FUN_00e205d0();                     // 0x00e205d0
    void __thiscall FUN_00e20860();                     // 0x00e20860
};
class tTriggerMgr {                                     // the trigger manager (0x00b3d4d0)
public:
    uint8_t mPad00[0x2c];
    int32_t mn2c;                                       // +0x2c
    void __thiscall FUN_00ad7dc0();                     // 0x00ad7dc0
    void __thiscall FUN_00ad7d40();                     // 0x00ad7d40
    void __thiscall FUN_00adffd0();                     // 0x00adffd0
};
class tBannerList {
public:
    int __thiscall FUN_00ba6d80(uint32_t nID);          // 0x00ba6d80
};
class tBBoxOwner {
public:
    uint32_t __thiscall FUN_0080dc90();                 // 0x0080dc90
    void     __thiscall FUN_0080dc50(void* pArg);       // 0x0080dc50
};
class tBoundObj {                                       // the object at +0x168
public:
    uint8_t mPad00[0x0c];
    void __thiscall FUN_00b5cde0(uint32_t nTag);        // 0x00b5cde0
};
class cDownloadDialog_s00de_41b0 {
public:
    uint8_t mPad00[0x2c];
    int32_t mn2c;                                       // +0x2c
    void __thiscall FUN_00df5540();                     // 0x00df5540
    bool __thiscall FUN_00df5830(void* pArg);           // 0x00df5830
    void __thiscall FUN_00df58f0();                     // 0x00df58f0
    bool __thiscall FUN_00df59c0(void* pArg);           // 0x00df59c0
    void __thiscall FUN_00df55b0(int nArg);             // 0x00df55b0
    void __thiscall FUN_00df5670(char bFlag);           // 0x00df5670
    uint32_t __thiscall FUN_00df5aa0(char bFlag);       // 0x00df5aa0
    bool __thiscall FUN_00df5420();                     // 0x00df5420
    cDownloadDialog_s00de_41b0* __thiscall ctor5c80();             // 0x00df5c80
    cDownloadDialog_s00de_41b0* __thiscall ctor5940();             // 0x00df5940
};
class tFileStream {
public:
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
virtual void s10();
virtual void s14();
virtual void s18();
    virtual void s1c();                                 // +0x1c
};
class tFile {
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
    virtual void v2c();                                 // +0x2c
    tFileStream mStream;                                // +0x04
};
class cVarListSerializer {
public:
    uint8_t m00[0x14];
    void __thiscall ctor(void* pOwner, void* pName, uint32_t nSig);     // 0x00692f90
    void __thiscall Serialize(void* pValue);                            // 0x00692900
};
class C3 {                                              // the archive stream used to write the save
public:
    void* mpVtbl;                                       // +0x00
    void* mpState;                                      // +0x04
    void* mpSerialized;                                 // +0x08
    cVarListSerializer mSerializer;                     // +0x0c
    uint8_t mWork[0xa00];                               // +0x20
    C3*  __thiscall ctorB(tFile* pFile, void* pA, void* pB, void* pC);  // 0x00693d60
    void __thiscall FUN_00692ea0();                     // 0x00692ea0
    void __thiscall FUN_00693900();                     // 0x00693900
};
class tRBNode {
public:
    uint32_t m00, m04, m08, m0c;
    uint32_t mKey;                                      // +0x10
    uint32_t m14, m18;
    uint32_t mValue;                                    // +0x1c
};
class tRBTree {
public:
    uint32_t  m00;
    tRBNode*  mEnd;                                     // +0x04
    tRBNode*  mBegin;                                   // +0x08
    uint32_t  m0c, m10;
    uint32_t  mCount;                                   // +0x14
};
class tArchive {
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
    virtual void* v18();                                // +0x18
    virtual void  v1c();                                // +0x1c
    virtual tArchive* v20();                            // +0x20
};
class tSimData {
public:
    uint32_t m00, m04, m08, m0c, m10, m14;
};
struct tSimAlloc {                                      // 0x28-byte allocation: 0x10 header + data
    uint8_t  mHead[0x10];
    tSimData mData;
};
class tSimElem {
public:
    uint32_t m0;                                        // +0x00
    uint32_t m4;                                        // +0x04
};
struct tSimVec {
    tSimElem* begin;
    tSimElem* end;
    tSimElem* cap;
};
struct tSimBuffer {                                     // the vector's buffer: a 4-byte refcount head
    uint32_t mnRefs;                                    // +0x00, i.e. buffer[-1]
    tSimElem maElems[1];                                // +0x04
};
class tSimContainer {
public:
    void __thiscall Init(void* pOut, int nA, int nB);           // 0x00596900
    void __thiscall Add(uint32_t a, uint32_t b, int nC);        // 0x00596da0
    void __thiscall Query(void* pOut, uint32_t nKey);           // 0x00596fc0
    void __thiscall Insert(uint32_t a, uint32_t b);             // 0x00596d70
    void __thiscall Clear();                                    // 0x005942e0
};
static __forceinline void AssignRef_s00de_41b0(void** ppTarget, void* pNew, int nAddSlot, int nRelSlot)
{
    void* pOld = *ppTarget;
    if (pNew != pOld) {
        if (pNew != 0)
            ((void(__thiscall*)(void*))VFN(pNew, nAddSlot))(pNew);
        *ppTarget = pNew;
        if (pOld != 0)
            ((void(__thiscall*)(void*))VFN(pOld, nRelSlot))(pOld);
    }
}
class tList2 {                                          // a two-pointer list header
public:
    tList2* mpNext;                                     // +0x00
    tList2* mpPrev;                                     // +0x04
};
class cGalaxyGameEntryImpl_s00de_41b0 {
public:
    uint8_t mPad00[0x20];
    tList2  m20;                                        // +0x20
    uint8_t mPad28[0x04];
    tEntryIface2c* mp2c;                                // +0x2c
    uint8_t mPad30[0x04];
    void*   mp34;                                       // +0x34
    tEntryIface38* mp38;                                // +0x38
    uint8_t mPad3c[0x7c - 0x3c];
    uint32_t m7c;                                       // +0x7c
    uint8_t mPad80[0xcc - 0x80];
    uint32_t mcc;                                       // +0xcc
    uint8_t mPadD0[0xe8 - 0xd0];
    int32_t me8;                                        // +0x0e8
    uint8_t mec;                                        // +0x0ec
    uint8_t med;                                        // +0x0ed
    uint8_t mee;                                        // +0x0ee
    uint8_t mef;                                        // +0x0ef
    tGameMode* mf0;                                     // +0x0f0
    uint8_t mPadF4[0xfc - 0xf4];
    int32_t mfc;                                        // +0x0fc
    int32_t m100;                                       // +0x100
    uint8_t mPad104[0x108 - 0x104];
    int32_t m108;                                       // +0x108
    int32_t m10c;                                       // +0x10c
    uint8_t mPad110[0x144 - 0x110];
    cSPUILayout_s00de_41b0 mLayout144;                             // +0x144
    void*   m15c;                                       // +0x15c
    uint8_t mPad160[0x168 - 0x160];
    tBoundObj* m168;                                    // +0x168
    int32_t m16c;                                       // +0x16c
    uint8_t mPad170[0x178 - 0x170];
    void*   m178;                                       // +0x178
    uint8_t mPad17c[0x184 - 0x17c];
    cSPUIGlobalUI_s00de_41b0* mpGlobalUI184;                       // +0x184
    uint8_t mPad188[0x198 - 0x188];
    void*   m198;                                       // +0x198
    uint8_t mPad19c[0x1ec - 0x19c];
    int32_t m1ec;                                       // +0x1ec
    uint8_t mPad1f0;
    uint8_t m1f1;                                       // +0x1f1
    uint8_t mPad1f2[0x24c - 0x1f2];
    uint8_t m24c;                                       // +0x24c

    void   __thiscall FUN_00de41b0();
    uint32_t __thiscall FUN_00de4360(uint32_t nID);
    void   __thiscall FUN_00de43b0(uint32_t nArg);
    bool   __thiscall FUN_00de43d0(uint32_t a, uint32_t b);
    bool   __thiscall FUN_00de4410(uint32_t a, uint32_t b);
    bool   __thiscall FUN_00de4450(uint32_t a, float fB, float fC, uint32_t d);
    bool   __thiscall FUN_00de44a0(uint32_t a, float fB, float fC, uint32_t d);
    bool   __thiscall FUN_00de44f0(float fA, float fB, uint32_t c);
    void   __thiscall FUN_00de4570(uint32_t nArg);
    void   __thiscall FUN_00de4590(void* pObj, uint32_t nArg);
    uint32_t __thiscall FUN_00de4610();
    void   __thiscall FUN_00de4630();
    int    __thiscall FUN_00de46e0();
    void   __thiscall OnActivate();  // 0x00de4720 (cGalaxyGameEntryImpl::OnActivate)
    void   __thiscall FUN_00de4850();
    void   __thiscall FUN_00de4910();
    void   __thiscall FUN_00de4a70();
    void   __thiscall FUN_00de4b30();
    void   __thiscall FUN_00de4c20(char bFlag);
    void   __thiscall FUN_00ddd970();
};
// ---- items of slice s00de41b0 end

// ---- items of slice s00de6170 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct ERBTree {
    void*         mpNode;    // +0x00
    void*         mpLeft;    // +0x04  (begin(); self-linked while empty)
    void*         mpRight;   // +0x08  (== &mpLeft while empty)
    void*         mpRoot;    // +0x0c  (root passed to DoNukeSubtree)
    union {
        unsigned char mFlag;     // +0x10  red/black flag byte
        unsigned int  mFlagWord; // +0x10  the whole word, zeroed by init passes
    };
    unsigned int  mCount;    // +0x14
    void*         mpPad18;   // +0x18
    void DoNukeSubtree(void* root);   // 0x9a9600
    void* find(void* out, void* key);                  // 0xe5c780
    void  insert(void* out, void* key, unsigned int);  // 0xa17a70
};
struct CRefCounted {
    virtual void V00();      // +0x00
    virtual void Release();  // +0x04
    virtual void Destroy();  // +0x08
};
struct CWString {
    wchar_t* mpBegin;   // +0x00
    wchar_t* mpEnd;     // +0x04
    wchar_t* mpCap;     // +0x08
};
struct CSPUILayout {
    unsigned int mData[6];      // +0x00 .. +0x17
    void Construct();           // 0x810000
    void Destroy();             // 0x811fe0
};
struct CDe1d8Block {
    unsigned int mBegin;        // +0x00
    unsigned int mEnd;          // +0x04
    unsigned int mCap;          // +0x08
    void Destroy();             // 0x4b5440
};
void __cdecl EA_OperatorDelete(void* p);      // 0xf47380
void __cdecl EA_Messaging_RemoveHandler(void* handler, void* a, void* b, void* c, void* d); // 0x571db0
__forceinline void FreeStringBuffer(wchar_t* begin, wchar_t* cap) {
    long bytes = (long)((char*)cap - (char*)begin);
    if (((bytes & ~1L) > 2) && begin != 0)
        EA_OperatorDelete(begin);
}
struct CGGEUserData {
    void*           mpVtbl00;      // +0x000
    void*           mpVtbl04;      // +0x004
    void*           mpVtbl08;      // +0x008
    void*           mpVtbl0c;      // +0x00c
    void*           mpHandler;     // +0x010 (EA::Messaging handler)
    void*           mHandlerArg0;  // +0x014
    void*           mHandlerArg1;  // +0x018
    void*           mHandlerArg2;  // +0x01c
    void*           mHandlerArg3;  // +0x020
    void*           mpHeap24;      // +0x024
    unsigned int    mZero28;       // +0x028
    unsigned int    mZero2c;       // +0x02c
    unsigned int    mPad30;        // +0x030
    unsigned int    mPad34;        // +0x034
    unsigned int    mZero38;       // +0x038
    ERBTree         mTree3c;       // +0x03c
    ERBTree         mTree58;       // +0x058
    ERBTree         mTree74;       // +0x074
    ERBTree         mTree90;       // +0x090
    ERBTree         mTreeAc;       // +0x0ac
    unsigned char   mFlagC8;       // +0x0c8
    unsigned char   mFlagC9;       // +0x0c9
    unsigned char   mPadCa[2];     // +0x0ca
    unsigned int    mZeroCc;       // +0x0cc
    CWString        mPath;         // +0x0d0
    unsigned int    mPadDc;        // +0x0dc
    unsigned int    mZeroE0;       // +0x0e0
    unsigned char   mFlagE4;       // +0x0e4
    unsigned char   mPadE5[3];     // +0x0e5
    unsigned int    mZeroE8;       // +0x0e8
    unsigned char   mByteEc;       // +0x0ec
    unsigned char   mByteEd;       // +0x0ed
    unsigned char   mByteEe;       // +0x0ee
    unsigned char   mByteEf;       // +0x0ef
    unsigned int    mZeroF0;       // +0x0f0
    unsigned char   mByteF4;       // +0x0f4
    unsigned char   mPadF5[3];     // +0x0f5
    unsigned int    mZeroF8;       // +0x0f8
    unsigned int    mZeroFc;       // +0x0fc
    unsigned char   mByte100;      // +0x100
    unsigned char   mByte101;      // +0x101
    unsigned char   mByte102;      // +0x102
    unsigned char   mFlag103;      // +0x103
    unsigned char   mByte104;      // +0x104
    unsigned char   mPad105[3];    // +0x105
    unsigned int    mZero108;      // +0x108
    unsigned int    mConst10c;     // +0x10c (initialised to 9)
    void*           mpHeap110;     // +0x110
    unsigned int    mZero114;      // +0x114
    unsigned int    mZero118;      // +0x118
    unsigned int    mPad11c;       // +0x11c
    unsigned int    mPad120;       // +0x120
    ERBTree         mTree124;      // +0x124
    unsigned int    mPad140;       // +0x140
    CSPUILayout     mLayout144;    // +0x144
    CRefCounted*    mpRef15c;      // +0x15c
    CRefCounted*    mpRef160;      // +0x160
    CRefCounted*    mpRef164;      // +0x164
    CRefCounted*    mpRef168;      // +0x168
    CRefCounted*    mpRef16c;      // +0x16c
    CRefCounted*    mpRef170;      // +0x170
    CRefCounted*    mpRef174;      // +0x174
    unsigned int    mZero178;      // +0x178
    unsigned char   mByte17c;      // +0x17c
    unsigned char   mPad17d[3];    // +0x17d
    unsigned int    mPad180;       // +0x180
    unsigned int    mZero184;      // +0x184
    unsigned int    mZero188;      // +0x188
    unsigned int    mZero18c;      // +0x18c
    unsigned int    mZero190;      // +0x190
    float           mZero194;      // +0x194
    CRefCounted*    mpRef198;      // +0x198
    CRefCounted*    mpRef19c;      // +0x19c
    CRefCounted*    mpRef1a0;      // +0x1a0
    CRefCounted*    mpRef1a4;      // +0x1a4
    CRefCounted*    mpRef1a8;      // +0x1a8
    CRefCounted*    mpRef1ac;      // +0x1ac
    CRefCounted*    mpRef1b0;      // +0x1b0
    CRefCounted*    mpRef1b4;      // +0x1b4
    CRefCounted*    mpRef1b8;      // +0x1b8
    CRefCounted*    mpRef1bc;      // +0x1bc
    CRefCounted*    mpRef1c0;      // +0x1c0
    CRefCounted*    mpRef1c4;      // +0x1c4
    CRefCounted*    mpRef1c8;      // +0x1c8
    CRefCounted*    mpRef1cc;      // +0x1cc
    CRefCounted*    mpRef1d0;      // +0x1d0
    CRefCounted*    mpRef1d4;      // +0x1d4
    CDe1d8Block     mBlock1d8;     // +0x1d8
    unsigned int    mPad1e4;       // +0x1e4
    unsigned int    mPad1e8;       // +0x1e8
    unsigned int    mZero1ec;      // +0x1ec
    unsigned char   mByte1f0;      // +0x1f0
    unsigned char   mByte1f1;      // +0x1f1
    unsigned char   mPad1f2[3];    // +0x1f2
    unsigned char   mByte1f5;      // +0x1f5
    unsigned char   mByte1f6;      // +0x1f6
    unsigned char   mPad1f7;       // +0x1f7
    unsigned int    mZero1f8;      // +0x1f8
    unsigned int    mZero1fc;      // +0x1fc
    unsigned int    mPad200[19];   // +0x200 .. +0x24b
    unsigned char   mByte24c;      // +0x24c
    unsigned char   mByte24d;      // +0x24d
    unsigned char   mPad24e[2];    // +0x24e
    void*           mpPtr250;      // +0x250
    ERBTree         mTree254;      // +0x254
    unsigned char   mByte270;      // +0x270
    unsigned char   mByte271;      // +0x271

    void FUN_00de6650(float x, float y);
};
struct CHeapCookie {
    unsigned int mCookie;   // +0x00 (immediately before the payload)
};
// ---- items of slice s00de6170 end

// ---- items of slice s00df10d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern wchar_t gEmptyWideString[];   // 0x01667bac (shared empty wide string, capacity is +1)
extern uint32_t gNewGameFlowPropListID;                     // 0x015a2df8
extern bool gbFlag16a0d60;                                  // 0x016a0d60
extern const wchar_t kWStr_0x08d[];                          // 0x0147e784 L"0x%08d"
extern const wchar_t kWStr_starLs[];                         // 0x0147e794 L"* %ls"
void FreeNode(void* p);              // 0x00f47380
namespace eastl {
class allocator_s00df_10d0 { public:
    allocator_s00df_10d0() {}
};
}
namespace eastl {
template <typename T> struct basic_string_s00df_10d0 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    allocator_s00df_10d0 mAllocator;
    basic_string_s00df_10d0()
        : mpBegin((T*)gEmptyWideString), mpEnd((T*)gEmptyWideString),
          mpCapacity((T*)gEmptyWideString + 1) {}
    basic_string_s00df_10d0(const basic_string_s00df_10d0& other);   // 0x0056e2d0 (out of line in the original)
    ~basic_string_s00df_10d0()
    {
        if (((int)((char*)mpCapacity - (char*)mpBegin) & ~1) > 2 && mpBegin)
            FreeNode(mpBegin);
    }
    const T* c_str() const { return mpBegin; }
};
}
namespace eastl {
typedef basic_string_s00df_10d0<wchar_t> string16_s00df_10d0;
}
namespace eastl {
template <typename T> class vector_s00df_10d0 { public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    allocator_s00df_10d0 mAllocator;

    vector_s00df_10d0() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~vector_s00df_10d0()
    {
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            FreeNode(mpBegin);
    }

    void DoInsertValue(T* position, const T& value);   // 0x004558a0 (vector<uint32_t>)
    T& operator[](int i) { return mpBegin[i]; }
    unsigned getSize() const { return (unsigned)(mpEnd - mpBegin); }
    T* erase(T* first, T* last)
    {
        memcpy(first, last, (size_t)((char*)mpEnd - (char*)last));
        mpEnd -= (last - first);
        return first;
    }
    void clear() { erase(mpBegin, mpEnd); }
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);  // 0x00621fc0 (eastl::vector::DoInsertValue)
    }
};
}
using eastl::string16_s00df_10d0;
struct Property_s00df_10d0 {
    uint32_t mData[4];
    uint16_t mFlags;   // +0x10
    uint16_t mType;    // +0x12 (1 bool, 10 uint32)
    bool* GetValueBool();       // 0x0041e920
    uint32_t* GetValueUInt32(); // 0x0041ea00
};
struct cPropList {
    virtual int AddRef();
    virtual int Release();
virtual void pv2();
virtual void pv3();
virtual void pv4();
virtual void pv5();
virtual void pv6();
virtual void pv7();
virtual void pv8();
    virtual bool GetProperty(uint32_t id, Property_s00df_10d0*& result);   // +0x24
};
template <typename T> struct intrusive_ptr {
    T* mpObject;
    intrusive_ptr() : mpObject(0) {}
    ~intrusive_ptr()
    {
        if (mpObject)
            mpObject->Release();
    }
    intrusive_ptr& operator=(T* p)
    {
        if (p != mpObject) {
            T* const pTemp = mpObject;
            if (p)
                p->AddRef();
            mpObject = p;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    void reset_null()
    {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
    }
    T* get() const { return mpObject; }
};
typedef intrusive_ptr<cPropList> PropListPtr;
struct cPropManager {
virtual void pv0();
virtual void pv1();
virtual void pv2();
virtual void pv3();
virtual void pv4();
virtual void pv5();
virtual void pv6();
virtual void pv7();
virtual void pv8();
virtual void pv9();
virtual void pv10();
    virtual bool GetPropertyListImpl(uint32_t instanceID, uint32_t groupID, PropListPtr& dst);   // +0x2c
virtual void pv12();
virtual void pv13();
virtual void pv14();
virtual void pv15();
virtual void pv16();
virtual void pv17();
    virtual void GetInstanceIDs(uint32_t groupID, eastl::vector_s00df_10d0<uint32_t>& dst);                   // +0x48
    bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropListPtr& dst)
    {
        dst.reset_null();
        return GetPropertyListImpl(instanceID, groupID, dst);
    }
};
cPropManager* PropertyManager_s00df_10d0();   // 0x0067de30
namespace EA {
namespace Hash {
uint32_t FNV1_String8(const char* s, uint32_t seed, bool lowercase);       // 0x00932e80
}
}
namespace EA {
namespace Hash {
uint32_t FNV1_String16(const wchar_t* s, uint32_t seed, bool lowercase);   // 0x00932f30
}
}
static inline uint32_t id(const char* s) { return EA::Hash::FNV1_String8(s, 0x811c9dc5, true); }
static inline uint32_t id(const wchar_t* s) { return EA::Hash::FNV1_String16(s, 0x811c9dc5, true); }
struct cAppSystem_s00df_10d0 {
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
    virtual bool IsFeatureEnabled();                        // +0x54
};
cAppSystem_s00df_10d0* AppSystem_s00df_10d0();                                    // 0x0067dd00
class IWindow_s00df_10d0 {
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
    virtual void SetFlag(int flag, bool value);             // +0x7c
};
namespace EA {
namespace UTFWinControls {
class IWinComboBox_s00df_10d0 {
public:
    virtual int AddRef();                                   // +0x00
    virtual int Release();                                  // +0x04
virtual void v08();
virtual void v0c();
    virtual IWindow_s00df_10d0* ToWindow();                            // +0x10
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual void AddItem(const wchar_t* text);              // +0x20
virtual void v24();
virtual void v28();
    virtual void RemoveAll();                               // +0x2c
};
}
}
struct cGGEGlobal {
    uint8_t pad00[0x24];
    eastl::vector_s00df_10d0<uint32_t> mStarterWorlds;                 // +0x24
};
extern cGGEGlobal* gpGGEGlobal;                             // 0x016a1344
void WStr_Format(string16_s00df_10d0* out, const wchar_t* fmt, ...);    // 0x0041e050
namespace SP {
bool GetPropertyAsString16(const cPropList* list, uint32_t id, string16_s00df_10d0* out);   // 0x006a1400
}
namespace SP {
class cGalaxyGameEntryUIStateMachine_s00df_10d0 {
public:
    bool FillStarterWorldCombo(EA::UTFWinControls::IWinComboBox_s00df_10d0* combo);         // 0x00df1ba0
};
}
// ---- items of slice s00df10d0 end

// ---- items of slice s00df3be0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const uint32_t kLevelWindowIDs[];        // 0x0147e7f4
extern uint32_t g_uiEventMask[];                   // 0x016a1848
struct WStr;
struct WStr {
    wchar_t* mpBegin;   // +0x00
    wchar_t* mpEnd;     // +0x04
    wchar_t* mpCap;     // +0x08
    WStr(const wchar_t* s, const void* tag);     // 0x0041df50
    ~WStr();                                     // 0x00933960
    WStr& operator=(const WStr& o);              // 0x0057cb60
    WStr& operator=(const wchar_t* s);           // 0x005c3d90
};
struct IWindow_s00df_3be0 {
    PV2 PV
    virtual IWindow_s00df_3be0* FindChild(uint32_t id);     // +0x0c
    PV4 PV2
    virtual uint32_t IsVisible();                // +0x28
    PV4 PV
    virtual int GetIndex();                      // +0x40
    PV8 PV4 PV2
    virtual void SetFlag(int flag, bool v);  // +0x7c
};
class cSPUILayout_s00df_3be0 { public:
    uint32_t pad[3];
    IWindow_s00df_3be0* FindWindowByID(uint32_t id, bool recursive);   // 0x008105b0
};
struct IRefObj_s00df_3be0 {
    PV
    virtual void v1();   // +0x04
    PV
    virtual void v3(int arg);   // +0x0c
};
struct Zero3 {
    uint32_t x, y, z;
    Zero3() { x = 0; y = 0; z = 0; }
};
struct GGE_s00df_3be0 {
    uint8_t pad00[0x24];
    uint32_t* m24;                             // +0x24 (panel id table)
    uint8_t pad28[0x170];                      // +0x28 .. +0x197
    void* m198;
    IRefObj_s00df_3be0* m19c;
    void Unk_de5d00(uint32_t id, void* cb, uint32_t v, const Zero3& zeros, int a, int b, int c);   // 0x00de5d00
    void Unk_de86d0(int a, int b);                                                              // 0x00de86d0
};
extern GGE_s00df_3be0* gpGGE_s00df_3be0;   // 0x016a1344
struct cPanelThing { void Unk_bbac80(uint32_t v, int flag); };   // 0x00bbac80
struct cGameInfo_s00df_3be0 {
    uint32_t m00;            // +0x00
    uint32_t pad04[7];       // +0x04 .. +0x1f
    WStr m20;                // +0x20
    uint32_t pad2c[0x19];    // +0x2c .. +0x8f
    uint32_t m90;            // +0x90
    uint32_t pad94[5];
    uint32_t mA8;            // +0xa8
    uint32_t padac;
    uint32_t mB0;            // +0xb0
    cPanelThing* Unk_de4610();                  // 0x00de4610
    cGameInfo_s00df_3be0& operator=(const WStr& s);        // 0x0057cb60 (name copy)
};
struct IAT {
    PV8
    virtual int GetState();   // +0x20
};
IAT* GetSystemAT_s00df_3be0();           // 0x00a206f0
int GetRecorderState_s00df_3be0();       // 0x00435e90
static __forceinline int ATState()
{
    IAT* p = GetSystemAT_s00df_3be0();
    return p ? p->GetState() : 0;
}
struct DeadEnd { void Fn_dde570(); };   // thiscall, no args (0x00dde570)
struct IEventSource;
struct GalaxyEvent;
struct cGalaxyGameEntryUIStateMachine_s00df_3be0 {
    uint32_t pad00[2];
    uint32_t mCallback;                        // +0x08 (sub-object, passed by address)
    uint32_t pad0c[7];
    cSPUILayout_s00df_3be0 mLayout;                       // +0x28
    uint32_t pad34[0xf];
    uint8_t mb70;                              // +0x70
    uint8_t pad71[3];                          // +0x71 .. +0x73
    uint32_t m74;                              // +0x74
    uint8_t pad78[0x4a8];                      // +0x78 .. +0x51f
    uint32_t m520;                             // +0x520 (passed by address)
    uint8_t pad524[0xc4];
    uint32_t mCurrentButton;                   // +0x5e8
    uint8_t pad5ec[0x3c];
    cGameInfo_s00df_3be0* mpGameInfo;                     // +0x628

    void UpdateNavigationControls();           // 0x00def8c0
    void SetLevel(int level);                  // 0x00df2ea0
    void Unk_df2550();                         // 0x00df2550
    void Unk_deef20(uint32_t a, void* b, int c);   // 0x00deef20
    void PickRandomAssets(int a);              // 0x00df3ab0
    void Unk_df2660();                         // 0x00df2660
    bool Unk_dec540(uint32_t a);               // 0x00dec540
    void PickRandomVehicle();                  // 0x00df2d80
    void PickRandomBuilding();                 // 0x00df2d60
    void PickRandomCreature();                 // 0x00df2bb0
    void SetCurrentState(int s);               // 0x00df0670
    void MakeRandomName();                     // 0x00defc80
    void SetStateSummaryText(int a, uint32_t b, uint32_t c);   // 0x00defd10
    void SetupPanelA(uint32_t id);             // 0x00df2920
    void SetupPanelB(uint32_t id);             // 0x00df2770
    void Init(uint32_t id);                    // 0x00df32d0
    void EditExistingAsset(uint32_t id);       // 0x00ded410
    void Unk_deede0();                         // 0x00deede0
    void MakeNewAsset(uint32_t id);            // 0x00dec7c0
    void LoadAsset(uint32_t id);               // 0x00dec940

    void HandleEvent(uint32_t id);
    void SelectTheme(uint32_t theme);                  // 0x00defdd0
    bool FUN_00def7c0(WStr* str);                       // 0x00def7c0
    bool BeginNewGameFlow(uint32_t unused, GalaxyEvent* e);   // 0x00df43d0
};
struct IEventSource {
    PV4 PV2 PV
    virtual uint32_t GetEventId();                  // +0x1c
};
struct GalaxyEvent {
    IEventSource* source;   // +0x00
    uint32_t field04;       // +0x04
    uint32_t type;          // +0x08
    uint32_t field0c;       // +0x0c
    uint32_t data;          // +0x10
};
struct Variant {
    uint32_t data[4];       // +0x00
    uint16_t flags;         // +0x10
    uint16_t type;          // +0x12
    Variant(const bool& b) : flags(0), type(0) { Store((bool*)&b); }
    void Store(bool* p);                        // 0x00422e20
    void Free(int a);                           // 0x0093db80
    ~Variant() { if (flags & 4) Free(0); }
};
struct IPrefs {
    PV4 PV
    virtual void SetProperty(uint32_t id, const Variant& v);   // +0x14
};
extern IPrefs* g_sAppPreferences;               // 0x015fd91c
void GetBoolProperty(IPrefs* p, uint32_t id, bool* out);   // 0x00407190
int GetSaveArea(uint32_t id);                              // 0x006b1f90
void SaveResource(void* prefs, int area, char flag);       // 0x006b1d50
struct IWinTextEdit {
    PV8 PV8 PV4 PV
    virtual const wchar_t* GetText();                          // +0x54
    PV2
    virtual void SetText(const wchar_t* text, int len);        // +0x60
};
IWinTextEdit* InterfaceCastTextEdit(IWindow_s00df_3be0* w);   // 0x005febd0
struct cGalaxyGameEntryUIHost {
    uint8_t pad00[8];
    cGalaxyGameEntryUIStateMachine_s00df_3be0* mpState;              // +0x08
    void Unk_e00670(uint32_t id, uint32_t arg);           // 0x00e00670
    void HandleUIEvent(uint32_t id, uint32_t arg);        // 0x00df46d0
};
// ---- items of slice s00df3be0 end

// ---- items of slice s00df6db0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern wchar_t g_EmptyWStr[];   // 0x1667bac
extern "C" void    __cdecl operator_delete_arr(void* p);        // 0xf47380
extern float g_PlanetScale;   // 0x16a0da0
extern char g_PlanetKey[];    // 0x16a0dd0
extern float g_ColorK;        // 0x1485720
struct cVec3 { float x, y, z; };
struct cRect4 {
  float x, y, w, h;
  cRect4() {}
  cRect4(const cRect4& r) : x(r.x), y(r.y), w(r.w), h(r.h) {}
};
struct cColorRGBA { float r, g, b, a; };
struct cZero3 { u32 a, b, c; };
struct cWStr {
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  void DeallocateSelf();   // 0x933960
};
class cWin {
public:
  virtual void AddRef();                               // 0x00
  virtual void Release();                              // 0x04
virtual void s02();
virtual void* GetProperty(u32 id);
virtual void s04();
virtual void s05();
virtual void s06();
virtual u32 GetWindowID();
virtual void s08();
virtual void s09();
virtual void s10();
virtual void s11();
virtual void s12();
  virtual u32  GetThing();                             // 0x34
  virtual float* GetArea();                            // 0x38
virtual void s15();
virtual int GetIndex();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
virtual void s22();
  virtual void SetColor(u32 c);                        // 0x5c
  virtual void SetThing(u32 v);                        // 0x60
virtual void s25();
virtual void s26();
virtual void s27();
virtual void s28();
virtual void s29();
virtual void s30();
  virtual void SetVisible(int a, int b);               // 0x7c
  virtual void SetText(const void* p);                 // 0x80
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
  virtual void* FindHandler(u32 id);                   // 0xb4
  virtual void SetHandler(u32 id, void* p);            // 0xb8
virtual void s47();
virtual void s48();
virtual void s49();
virtual void s50();
virtual void s51();
virtual void s52();
virtual void s53();
virtual void s54();
virtual void s55();
virtual void s56();
virtual void s57();
virtual void s58();
virtual void s59();
virtual void s60();
virtual void s61();
virtual void s62();
virtual void s63();
virtual void s64();
  virtual void SetWindowArg(void* p);                  // 0x104
};
class cWindowManager_s00df_6db0 {
public:
virtual void s00();
virtual void s01();
virtual void s02();
virtual void s03();
virtual void s04();
virtual void s05();
virtual void s06();
virtual void s07();
virtual void s08();
virtual void s09();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
  virtual void SetFocus(int a, cWin* w);               // 0x4c
};
class cSpeciesProfile {
public:
  void GetUiName(cWStr* out);                          // 0x4da330
};
class cAudioMgr {
public:
  bool Query(const cVec3* v);                          // 0xb7d4f0
  void Fill(cVec3 v, int a, int b, int c, int d, cZero3* o1, cZero3* o2);   // 0xb7d440
};
class cModelObj {
public:
  cVec3* GetPos();                                     // 0xb8d8e0
};
class cPlanetModel_s00df_6db0 {
public:
  u32 pad[3];
  void Query(cZero3* a, cZero3* b, void* c);          // 0xe21260
  void SetA(const void* p);                            // 0xe20d60
  void SetB(float f);                                  // 0xe20d30
};
class cInfo {
public:
  u32 mFirst;                  // 0x00
  char pad04[0x2c];
  u32 m30;                     // 0x30
  char pad34[8];
  u32 m3c;                     // 0x3c
  char pad40[8];
  cSpeciesProfile* mpSpecies;  // 0x48
  char pad4c[0x5c];
  u32 mA8;                     // 0xa8
  unsigned char mFlagAC;       // 0xac
  char padAD[0xb];
  u32 mB8;                     // 0xb8
  cInfo* Resolve();            // 0xde4610
  cModelObj* Get(int i);       // 0xbbaa60
};
class cMgr8c {
public:
  virtual void v00();
  virtual void AddRef();                               // 0x04
  virtual void Release();                              // 0x08
  void Attach(cWin* w, int flag);                      // 0x80dda0
};
class cSPBoundingBoxMgr {
public:
  cMgr8c* GetCollection();                             // 0x80f730
};
class cSPUILayout_s00df_6db0 {
public:
  char pad0[0x20];
  cWin* FindWindowByID(u32 id, int flag);              // 0x8105b0
  void  Shutdown(u32 flag);                            // 0x811ad0
  bool  Init(const wchar_t* pName, int a, bool b, u32 c);   // 0x812160
};
extern "C" void*   __cdecl GetRecorderState_s00df_6db0();                  // 0x435e90
extern "C" void    __cdecl Pollinator(cWin* w, cRect4* r);      // 0x806d10
extern "C" cWin*   __cdecl FUN_00de3e00(cWin* w);               // sGetWindowImage
extern "C" cAudioMgr* __cdecl FUN_00b3d360_s00df_6db0();
extern "C" u32     __cdecl ColorRGBAToU32(const cColorRGBA* c); // 0x4580c0
extern "C" cWindowManager_s00df_6db0* __cdecl WindowManager_s00df_6db0();             // 0x67caa0
namespace {

class cGameUIData : public cSPUILayout_s00df_6db0 {
public:
  cPlanetModel_s00df_6db0 mPlanet;        // 0x20
  int    mUIState;             // 0x2c
  cInfo* mpInfo;               // 0x30
  char pad34[0x58];
  cMgr8c* mpMgr;               // 0x8c
  bool SetUIState(int newState);
  bool SetLayout(const wchar_t* pName, void* pArg);
};

// =====================================================================================
// Slice s00df6db0 -- cGameUIData::SetLayout (0x00DF76C0): called with a layout name and a
// window argument, it tears the old screen down, builds the new one and hands the argument
// to the four panels that own a per-layout window.
// =====================================================================================
extern unsigned char g_16a0f88;                        // 0x016a0f88  "layout already built" flag

// 0x0067CAD0 returns the bounding-box singleton, whose 0x0080F730 member yields the
// object stored in cGameUIData::mpMgr (refcounted, vtable +0x04 AddRef / +0x08 Release).
extern "C" cSPBoundingBoxMgr* __cdecl AddBoundingBox(); // 0x0067cad0

}  // namespace
class cGalaxyGameEntry;
class cStarManager_s00df_6db0;
struct cMessage {
  cWin* mpObject;              // 0x00
  cWin* mpWindow;              // 0x04
  u32   mId;                   // 0x08
  u32   mSub;                  // 0x0c
  char  pad10[8];
  cWin* mpWindow2;             // 0x18
};
class cEntryTable {
public:
  cGalaxyGameEntry*& GetEntry(int index) {
    return *(cGalaxyGameEntry**)((char*)this + index * 4);
  }
};
class cGalaxyGameEntry {
public:
  char pad00[0x80];
  char mSub80[0x2c];           // 0x80
  unsigned char mEntryKind;    // 0xac
  char padAD[0xb];
  cGameUIData* mpLayout;       // 0xb8
  cStarManager_s00df_6db0* Resolve(void* key, int flag);          // 0x00de4610
};
class cUIHints {
public:
  void Next(int id, char flag);                        // 0x0067c3b0
};
class cPushMatrixOwner {
public:
  void PushMatrix(const void* p);                      // 0x00ddfb50
};
class cAudioSystemAT {
public:
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
  virtual u32  GetHandle();                            // 0x20
};
struct cSpaceGame {
  char pad00[0x24];
  cEntryTable* mpArray24;      // 0x24  id -> entry table
  char pad28[0xa0];
  unsigned char mC8;           // 0xc8
  char padC9[0x2f];
  cGalaxyGameEntry* mpDisplayed;   // 0xf8
  cGalaxyGameEntry* mpPending;     // 0xfc
  char pad100[8];
  int   m108;                  // 0x108
  char pad10c[0x8c];
  cPushMatrixOwner* mp198;     // 0x198
  char pad19c[0xd5];
  unsigned char m271;          // 0x271
  cUIHints* GetUIHints();                              // 0x0067cac0
  void FUN_00de86d0(int a, int b);                     // 0x00de86d0
  void FUN_00de9ec0();                                 // 0x00de9ec0
  void FUN_00de53d0(int a);                            // 0x00de53d0
};
struct cUISingleton48 {
  char pad00[0x48];
  cGalaxyGameEntry* mp48;      // 0x48
};
class cFont {
public:
  void SetUserData(void* p);                           // 0x00fd9450
};
class cGalaxyGameEntryImpl_s00df_6db0 {
public:
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
  virtual void v5c(int a);                             // 0x5c
  virtual void v60(void* p, int b);                    // 0x60
  virtual void v64(cGalaxyGameEntry* p, float f1, float f2);   // 0x64

  bool DoMessage(u32 msg, cMessage* pMsg);             // 0x00df7830
  void SetPendingGame(cGalaxyGameEntry* pGame, char flag);     // 0x00df7af0
  void SetDisplayedEntry(cGalaxyGameEntry* pEntry);    // 0x00df7c20
};
extern cSpaceGame* g_16a1344;                          // 0x016a1344
extern cGalaxyGameEntryImpl_s00df_6db0* g_16a1484;                // 0x016a1484
extern cFont* g_16a1570;                               // 0x016a1570
extern cGalaxyGameEntryImpl_s00df_6db0* g_16a15fc;                // 0x016a15fc
extern cUISingleton48* g_16a11b4;                      // 0x016a11b4
class cHintOwner {
public:
  void ResetHints();                                   // 0x00dda0d0
};
extern "C" cHintOwner* __stdcall FUN_00dd9190_s00df_6db0(int a);           // 0x00dd9190
class cStarManager_s00df_6db0 {
public:
  void SetStar();                                      // 0x00bbac80
};
// ---- items of slice s00df6db0 end

// ---- items of slice s00dfb5b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl EA_Allocate(uint32_t size, const char* name, int a, int b,
                                     const char* file, int line);        // 0xf473a0
extern "C" void  __cdecl EA_Free(void* p);                                // 0xf47380
extern "C" void  __cdecl MemThunk(void* dst, const void* src, uint32_t n); // 0x11e0744
extern "C" void  __cdecl FUN_00e00630();
extern "C" void  __cdecl FUN_00810000(void*);
extern "C" void  __cdecl FUN_0093a560_fn(void*, int, int);
extern "C" void  __cdecl FUN_00f257b0(void*);
extern "C" void  __cdecl FUN_00811fe0(void*);
extern "C" void* __cdecl FUN_00ef19f0();
extern "C" void  __cdecl FUN_00de4850(void*);
extern "C" void* __cdecl FUN_00401010();
extern "C" char  __cdecl FUN_00f56f0(wchar_t c);
extern "C" char  __cdecl FUN_005bf0e0(void* self, void** out);
extern "C" char  __cdecl FUN_006419f0(void* self);
extern "C" uint32_t __cdecl FUN_00eecba0(void* self);
extern "C" void  __cdecl FUN_00646370(void*, void*, void*, void*, uint32_t, int);
extern "C" void  __cdecl FUN_00ddb760();
extern "C" void  __cdecl FUN_00dfab20(int);
extern "C" void* __cdecl Vec38_AllocCopy(void* self, int n, void* first, void* last); // 0xdfb1b0
extern "C" void  __cdecl Vec38_Copy(void* first, void* last, void* dest);             // 0xdfb210
extern "C" void  __cdecl FUN_0050f740(void* a, void* b, void* c);
extern "C" void  __cdecl VecInsertKey(void* self, void* pos, void* val);
extern "C" void  __cdecl FUN_00473500(void* dst, const void* src);   // 0x473500 (cdecl form)
extern wchar_t gEmptyA_1667bac;   // 0x1667bac
extern wchar_t gEmptyB_1667bae;   // 0x1667bae
extern "C" char*   g_16c7aa4;      // 0x16c7aa4
extern "C" float g_scale_1485720;     // 0x1485720
extern "C" float g_depth_147eeac;     // 0x147eeac
static __declspec(noinline) void* AllocSizeD(uint32_t elements) {
  return EA_Allocate(elements * 0x44, "Simulator", 0, 0,
      "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
}
struct SubVec38 {                                  // 12-byte eastl vector at TypeB+0x1c
  uint32_t b, e, c;
  void assign_00473460(const void* src);           // 0x473460 (thiscall, 1 arg)
  void assign_00473500(const void* src);           // 0x473500 (thiscall, 1 arg)
};
struct Swarm_s00df_b5b0 {                                     // global swarm container (0xdd9190)
  int  GetLinkCount(int id);                       // 0xdda060
  char IsReady();                                  // 0xdd91a0
};
extern "C" Swarm_s00df_b5b0* __cdecl FUN_00dd9190_s00df_b5b0();          // 0xdd9190
struct Swarm {                                     // global swarm container (0xdd9190)
  int  GetLinkCount(int id);                       // 0xdda060
  char IsReady();                                  // 0xdd91a0
};
static inline void** Vt(void* p) { return *(void***)p; }
struct WString_s00df_b5b0 {                    // eastl::basic_string<wchar_t,eastl::allocator> (12 bytes)
  wchar_t* begin;                   // +0x00
  wchar_t* end;                     // +0x04
  wchar_t* cap;                     // +0x08
  void AllocateSelf(int n);                       // 0x429760
  void Assign(const wchar_t* b, const wchar_t* e); // 0x423650
  void push_back(wchar_t c);                      // 0x4f6510
  void RangeInitialize(const wchar_t* s);         // 0x579a90
};
struct CString {                    // SP::cString (0x14 bytes)
  uint32_t a0, a4, a8, ac, b0;
  void CStrCtor(const CString* src);   // 0x6b56f0
  CString* Assign(const CString* src); // 0x6b5430
};
struct TypeC {                      // 0x38 bytes
  CString  cs;       // +0x00
  WString_s00df_b5b0  s1;       // +0x14
  uint32_t pad20;    // +0x20
  uint32_t f24;      // +0x24
  uint32_t f28;      // +0x28
  WString_s00df_b5b0  s2;       // +0x2c
  TypeC* CopyCtor(const TypeC* src);   // 0xdfb280
  void   dtor_f280f0();                // 0xf280f0 (out of line)
};
struct TypeD {                      // 0x44 bytes
  uint32_t f0;       // +0x00
  TypeC    c;        // +0x04
  uint32_t pad3c;    // +0x3c
  uint32_t f40;      // +0x40
  TypeD* CopyCtor(const TypeD* src);   // element copy (inline TypeC + fields)
  void   Dtor();                        // element dtor
};
struct TypeA {                      // 0x24 bytes
  float    f0;       // +0x00
  uint32_t f4;       // +0x04
  uint32_t f8;       // +0x08
  uint8_t  fC;       // +0x0c
  uint8_t  pad[3];   // +0x0d
  WString_s00df_b5b0  s;        // +0x10
  uint32_t f20;      // +0x20
  TypeA* CopyCtor(const TypeA* src);   // 0xdfb130
  void   Dtor();                        // element string dtor
};
struct TypeB {                      // 0x34 bytes
  float    f0;       // +0x00
  uint32_t f4, f8, fC, f10, f14, f18;  // +0x04..+0x1c
  SubVec38 v1c;                        // +0x1c eastl::vector (12 bytes)
  uint32_t pad28, pad2c;               // +0x28
  uint32_t f30;                        // +0x30
  TypeB* CopyCtorA(const TypeB* src);  // 0xdfb890
  TypeB* CopyCtorB(const TypeB* src);  // 0xdfbd00
};
struct Vec38 {                       // 0x38-byte element vector (12-byte header)
  uint32_t b, e, c;
  Vec38* Assign(const Vec38& x);      // 0xdfb720
};
struct VecA {                        // 0x24-byte element vector
  uint32_t b, e, c;
  void Insert(TypeA* position, const TypeA* value);  // 0xdfc000
};
struct Big {
  void Init();          // 0xdfb9c0
  void Destroy();       // 0xdfbac0
  void DestroyVec18();  // 0xdfbb60
  void Update();        // 0xdfbd70
  void Update2(int);    // 0xdfc240
  char Check();         // 0xdfc500
  void sub_dfa370();    // 0xdfa370 (thiscall)
  void sub_df9fc0();    // 0xdf9fc0 (thiscall)
  void sub_dfa790(int); // 0xdfa790 (thiscall, 1 arg)
};
struct B3Obj {                     // object returned by 0x00b3d360
  char   pad[0x20];
  void*  head;                     // +0x20 (self-referential while empty)
  char   sub_de46e0();             // 0xde46e0 (thiscall)
};
struct Obj3c   { void sub_de7010(); };          // 0xde7010 (thiscall) on g_16a1344 + 0x3c
struct Ec43    { char sub_ec4320(); };          // 0xec4320 (thiscall)
struct Svc410  { void sub_e3e350(int, void*, int); };  // 0xe3e350 (thiscall, 3 args)
struct Stopwatch_s00df_b5b0 { long long sub_0093a3a0(); };        // 0x93a3a0 (thiscall, __int64 result)
extern "C" B3Obj*  __cdecl FUN_00b3d360_s00df_b5b0();
extern "C" Svc410* __cdecl FUN_00b3d410_s00df_b5b0();
extern "C" char*   g_16a1344_s00df_b5b0;      // 0x16a1344
struct Vec3g { float x, y, z; };
struct Mat3g {                        // 0x24 bytes (cSPMatrix3)
  float m[9];
  void CopyCtor_0041cb40(const Mat3g* src);   // 0x41cb40 (thiscall, 1 arg)
};
struct Desc38 {
  int16_t kind;                       // +0x00
  int16_t sub;                        // +0x02
  Vec3g   pos;                        // +0x04
  float   scale;                      // +0x10
  Mat3g   mat;                        // +0x14
};
extern "C" Vec3g g_vec_16a173c;       // 0x16a173c
extern "C" Mat3g g_mat_16a1718;       // 0x16a1718
struct Huge {
  void Destroy();       // 0xdfbba0
};
static void DestroyVec44(char* v) {
  char* e = *(char**)(v + 4);
  char* b = *(char**)(v);
  for (char* q = b; q < e; q += 0x44) ((TypeC*)(q + 4))->dtor_f280f0();
  b = *(char**)(v);
  if (b && *(int*)(b - 4) != 0) EA_Free(b);
}
CString* CString::Assign(const CString* src) {
  a0 = src->a0; a4 = src->a4; a8 = src->a8; ac = src->ac; b0 = src->b0;
  return this;
}
TypeC* TypeC::CopyCtor(const TypeC* o) {
  cs.CStrCtor(&o->cs);
  int n1 = (int)((char*)o->s1.end - (char*)o->s1.begin) >> 1;
  s1.begin = s1.end = s1.cap = 0;
  s1.AllocateSelf(n1 + 1);
  MemThunk(s1.begin, o->s1.begin, n1 * 2);
  s1.end = (wchar_t*)((char*)s1.begin + n1 * 2);
  *s1.end = 0;
  f24 = o->f24;
  f28 = o->f28;
  int n2 = (int)((char*)o->s2.end - (char*)o->s2.begin) >> 1;
  s2.begin = s2.end = s2.cap = 0;
  s2.AllocateSelf(n2 + 1);
  MemThunk(s2.begin, o->s2.begin, n2 * 2);
  s2.end = (wchar_t*)((char*)s2.begin + n2 * 2);
  *s2.end = 0;
  return this;
}
TypeA* TypeA::CopyCtor(const TypeA* o) {
  f0 = o->f0; f4 = o->f4; f8 = o->f8; fC = o->fC;
  int n = (int)((char*)o->s.end - (char*)o->s.begin) >> 1;
  s.begin = s.end = s.cap = 0;
  s.AllocateSelf(n + 1);
  MemThunk(s.begin, o->s.begin, n * 2);
  s.end = (wchar_t*)((char*)s.begin + n * 2);
  *s.end = 0;
  f20 = o->f20;
  return this;
}
void TypeA::Dtor() {
  if ((char*)s.cap - (char*)s.begin > 2 && s.begin) EA_Free(s.begin);
}
TypeD* TypeD::CopyCtor(const TypeD* o) {
  f0 = o->f0;
  c.CopyCtor(&o->c);
  f40 = o->f40;
  return this;
}
void TypeD::Dtor() { c.dtor_f280f0(); }
// ---- items of slice s00dfb5b0 end

// ---- items of slice s00dfc5b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void __cdecl sub_f280f0(void* p);   // (element + 4) destructor
extern "C" void* __fastcall FUN_00dfc690(void* self, int dummy, unsigned n, void* first,
                                         void* last);                    // 0x00dfc690 (ret 0xc)
extern "C" void* __cdecl FUN_00dfc170(void* first, void* last, void* dest); // 0x00dfc170 (caller cleans)
extern "C" void  __fastcall FUN_00dfb850(void* self, int dummy, void* first, void* last); // 0x00dfb850
extern "C" void  __cdecl vec34UninitCopy(void** out, void* f, void* l,
                                         void* d, void* last);            // 0x00dfbc80
extern "C" void  __fastcall FUN_00423650(void* self, int dummy, void* b, void* e);   // 0x00423650 (ret 8)
extern "C" void* __fastcall FUN_00c06b10(void* self, int dummy, const void* src); // 0x00c06b10
extern "C" void* __fastcall FUN_006b5430(void* self, int dummy, const void* src); // 0x006b5430
extern "C" void* __cdecl UninitCopyD(void* out, const void* first, const void* last,
                                     void* dest, const void* arg5);   // 0x00dfb8e0
extern "C" void* __cdecl placeCopy20(void** cur, void* first, void* last, void* dst,
                                     const void* arg5);               // 0x00c04920
extern "C" void  __fastcall FUN_00dfaaf0(void* self, int dummy, void* first, void* last); // 0x00dfaaf0
extern "C" void* __fastcall FUN_00dfc1e0(void* self, int dummy, unsigned n, void* first,
                                         void* last);                 // 0x00dfc1e0
extern "C" void  __fastcall FUN_00dfa400(void* self, int dummy, unsigned n, void* srcBuf); // 0x00dfa400
extern "C" void  __fastcall FUN_0093a1a0(void* self, int dummy, int units);   // 0x0093a1a0
extern "C" void  __fastcall FUN_007c4010(void* viewer, int dummy, int* out);  // 0x007c4010
extern "C" void* __fastcall FUN_00dfb280(void* self, int dummy, const void* src);  // 0x00dfb280
struct Elem44  { void sub_f280f0(); };
struct Elem4e0 { void sub_dfbba0(); };
struct Sub28Vec { void sub_dfb850(void* first, void* last); };
struct Vec44 {
    void* mpBegin;           // +0x00
    void* mpEnd;             // +0x04
    void* mpCap;             // +0x08
    char  pad0c[0x14 - 0xc];
    void* mOwner;            // +0x14  (0 => self-allocating)
    Vec44& assignFrom(const Vec44& o);           // 0x00dfcb00 (retail: operator=)
private:
    // declared, never defined: suppresses the implicit memberwise copy-assign so that
    // `vec = other` cannot silently copy the three pointers instead of the elements
    Vec44& operator=(const Vec44& o);
};
struct Vec34M {
    void* mpBegin;           // +0x00
    void* mpEnd;             // +0x04
    void* mpCap;             // +0x08
    char  pad0c[0x14 - 0xc];
    void* mOwner;            // +0x14
};
struct Vec34 {
    void* mpBegin;           // +0x00
    void* mpEnd;             // +0x04
    void* mpCap;             // +0x08
    char  pad0c[0x14 - 0xc];
    void* mOwner;            // +0x14
    Vec34& assignFrom(const Vec34& o);            // 0x00dfcee0 (retail: operator=)
private:
    Vec34& operator=(const Vec34& o);             // never defined (see Vec44)
};
struct Entry188 {
    u32   m00, m04, m08, m0c;    // +0x00 .. +0x0c
    u8    m10;                   // +0x10
    char  pad11[3];
    u32   m14;                   // +0x14
    Vec44 mVec;                  // +0x18  (mVec.mOwner at +0x2c)
    char  pad30[0x184 - 0x30];   // inline 0x44-element storage
    u32   m184;                  // +0x184
    Entry188& operator=(const Entry188& o);      // 0x00dfcc90
    Entry188& ctorr(const Entry188& o);          // 0x00dfd020
};
struct VariantPair;
namespace eastl {
template<class A, class B, class R> struct binary_function_s00df_c5b0 {
    typedef A first_argument_type;
    typedef B second_argument_type;
    typedef R result_type;
};
}
namespace eastl {
template<class T> struct less_s00df_c5b0 : binary_function_s00df_c5b0<T, T, bool> {
    bool operator()(const T& a, const T& b) const { return a < b; }
};
}
namespace eastl {
template<class Key, class Value, class Compare>
class map_value_compare : public binary_function_s00df_c5b0<Value, Value, bool> {
public:
    Compare c;
    map_value_compare(const Compare& x) : c(x) {}
    bool operator()(const Value& a, const Value& b) const { return c(a.first, b.first); }
    bool operator()(const Value& a, const Key& b) const { return c(a.first, b); }
    bool operator()(const Key& a, const Value& b) const { return c(a, b.first); }
    bool operator()(const Key& a, const Key& b) const { return c(a, b); }
};
}
namespace eastl {
class pvector {
public:
    VariantPair* mpBegin;
    VariantPair* mpEnd;
    VariantPair* mpCapacity;
    u32 mAllocA;
    u32 mAllocB;
    pvector& operator=(const pvector& src);      // 0x006a1e80
};
}
struct Vec38_s00df_c5b0 : public eastl::pvector {
    typedef eastl::map_value_compare<u32, VariantPair, eastl::less_s00df_c5b0<u32> > value_compare;
    value_compare mCompare;                    // +0x14
    Vec38_s00df_c5b0& operator=(const Vec38_s00df_c5b0& src) {
        eastl::pvector::operator=(src);
        mCompare = value_compare(src.mCompare);
        return *this;
    }
};
struct Entry38 {
    char  pad00[8];
    u32   m08, m0c, m10, m14;
    Vec38_s00df_c5b0 mVec;              // +0x18
    void* mp30;              // +0x30  (ref-counted: v[0] AddRef, v[4] Release)
    u32   m34;               // +0x34
    Entry38& operator=(const Entry38& o);        // 0x00dfca50
};
struct FVec {                                     // float vector at +0x20c
    char pad00[0x14];
    FVec& operator=(const FVec& o);               // 0x0050d4e0 (external)
};
struct BigRec {
    u8    m00, m01, m02;     // +0x00
    u8    pad03;
    Vec44 mVec04;            // +0x04
    char  pad1c[0x170 - 0x1c];
    Vec44 mVec170;           // +0x170
    char  pad188[0x2dc - 0x188];
    Vec44 mVec2dc;           // +0x2dc
    char  pad2f4[0x448 - 0x2f4];
    void* mStr448;           // +0x448  (cString; assign 0x006b5430)
    char  pad44c[0x45c - 0x44c];
    void* mW45c;             // +0x45c  (wstring range)
    void* mW460;             // +0x460
    u32   m46c;              // +0x46c
    u32   m470;              // +0x470
    void* mW474;             // +0x474
    void* mW478;             // +0x478
    float f484;              // +0x484
    float f488, f48c, f490, f494, f498, f49c, f4a0;
    u32   m4a4, m4a8, m4ac, m4b0, m4b4, m4b8, m4bc, m4c0, m4c4;
    u8    m4c8;              // +0x4c8
    char  pad4c9[0x4cc - 0x4c9];
    BigRec& ctorr(const BigRec& o);               // 0x00dfcce0
};
struct Sub028 {
    u32   m00, m04, m08, m0c, m10, m14, m18, m1c;
    float f20, f24;                               // +0x20, +0x24
    Vec34 mVec28;                                 // +0x28
    char  pad40[0x1e0 - 0x40];
    float f1e0, f1e4;                             // +0x1e0, +0x1e4
    u32   m1e8, m1ec, m1f0, m1f4, m1f8, m1fc, m200;
    float f204;                                   // +0x204
    u8    b208, b209;                             // +0x208, +0x209
    char  pad20a[0x20c - 0x20a];
    FVec  m20c;                                   // +0x20c
    float f220;                                   // +0x220
    u32   m224, m228, m22c, m230;
    Sub028& operator=(const Sub028& o);           // 0x00dfd3a0
};
struct Blob5b0 {
    char pad_00[0x28];
    void* mp28;              // +0x28
    void* mp2c;              // +0x2c
    char pad_30[0x20c - 0x30];
    void* mp20c;             // +0x20c
    void dtor();
};
struct EffectVec { void EraseRange(u32 first, u32 last); };
struct BlobAC0 {
    u32 mpBegin;             // +0x00
    u32 mpEnd;               // +0x04
    void dtor();
};
struct BlobC40 {
    int   mField00;          // +0x00 sign flag
    char  pad_04[0x2c - 0x04];
    void* mp2c;              // +0x2c
    void* mp30;              // +0x30
    char pad_34[0x210 - 0x34];
    int   mField210;         // +0x210
    void dtor();
};
struct Elem3c { void sub_f280f0(); };
struct BlobE40 {
    char pad_00[0x3c];
    Elem3c m3c;              // +0x3c
    char pad_40[0x84 - 0x40];
    void* mp84;              // +0x84
    void* mp88;              // +0x88
    void dtor();
};
struct BlobE90 {
    char pad_00[0x70];
    u32 mpBegin70;           // +0x70
    u32 mpEnd74;             // +0x74
    char pad_78[0x2788 - 0x78];
    Elem3c m2788;            // +0x2788
    void dtor();
};
extern "C" void* __fastcall FUN_008105b0(void* self, int dummy, u32 id, int recursive); // 0x008105b0
extern "C" void  __fastcall FUN_00812160(void* layout, int dummy, void* name, u32 type,
                                         int a, u32 id);                  // 0x00812160
struct GgeLayout {
    char   pad_00[0x0c];
    void*  mpVecBegin;       // +0x0c  eastl vector of 0x24-byte panel entries
    void*  mpVecEnd;         // +0x10
    void*  mpVecCap;         // +0x14
    u8     pad_18[0x38 - 0x18];
    u8     pad_38[0x48 - 0x38];
    u8     mWin48[0x18];     // +0x48  UI window subobject
    u8     mStop60[0x1c];    // +0x60  EA::Stopwatch
    void Init();
};
struct GgeEntry {                      // 0x24-byte element of the +0x0c vector
    u32      f0;                       // +0x00  label ID + index
    u32      f4, f8;                   // +0x04, +0x08
    u8       fC;                       // +0x0c
    u8       pad0d[3];
    void*    mpStrBegin;               // +0x10  wstring buffer (owned)
    void*    mpStrEnd;                 // +0x14
    void*    mpStrCap;                 // +0x18
    u32      gap1c;                    // +0x1c  (not copied by the 0x24 copy ctor)
    u32      f20;                      // +0x20
    void Dtor();
};
void GgeEntry::Dtor() {
    char* b = (char*)mpStrBegin;
    if ((((int)((char*)mpStrCap - b) & 0xfffffffe)) > 2 && b)
        FUN_00f47380(b);
}
struct GgeRect { int left, top, right, bottom; };
static __forceinline void* Vfn(void* p, int slot) { return (*(void***)p)[slot / 4]; }
static __forceinline void AddPanelEntry(void* self, u32 i, const wchar_t* name) {
    char* s = (char*)self;
    GgeEntry e2;
    e2.f0 = 0x7bfb2a0 + i;
    e2.f4 = 0x5384d05 + i;
    e2.f8 = 0x5933fe0 + i;
    e2.mpStrBegin = e2.mpStrEnd = e2.mpStrCap = 0;
    ((void (__fastcall*)(void*, int, const wchar_t*))0x579a90)(&e2.mpStrBegin, 0, name);
    e2.fC = 1;
    e2.f20 = i + 1;
    GgeEntry* end = *(GgeEntry**)(s + 0x10);
    if ((void*)end < *(void**)(s + 0x14)) {
        *(void**)(s + 0x10) = (char*)end + 0x24;
        if (end) ((void (__fastcall*)(void*, int, GgeEntry*))0xdfb130)(end, 0, &e2);
    } else {
        ((void (__fastcall*)(void*, int, void*, GgeEntry*))0xdfc000)(s + 0x0c, 0, end, &e2);
    }
    e2.Dtor();
}
struct Huge_s00df_c5b0 {
    u8    m00, m01, m02;     // +0x00
    u8    pad03;
    Vec44 mVec04;            // +0x04  inline buffer at +0x1c, capacity 0x154
    char  pad1c[0x170 - 0x1c];
    Vec44 mVec170;           // +0x170
    char  pad188[0x2dc - 0x188];
    Vec44 mVec2dc;           // +0x2dc
    char  pad2f4[0x448 - 0x2f4];
    void* mSub448;           // +0x448  0x38-byte sub-object (0x00dfb280 copy ctor)
    char  pad44c[0x484 - 0x44c];
    float f484, f488, f48c, f490, f494, f498, f49c, f4a0;
    u32   m4a4, m4a8, m4ac, m4b0, m4b4, m4b8, m4bc, m4c0, m4c4;
    u8    m4c8;              // +0x4c8
    char  pad4c9[0x4cc - 0x4c9];
    void* mp4ccBegin;        // +0x4cc  eastl vector of 0x20-byte elements
    void* mp4ccEnd;          // +0x4d0
    void* mp4ccCap;          // +0x4d4
    char  pad4d8[4];
    Huge_s00df_c5b0& copyCtor(const Huge_s00df_c5b0& o);  // 0x00dfd080 (Huge::copyCtor)
};
// ---- items of slice s00dfc5b0 end

// ---- items of slice s00dfd5b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern unsigned g_16a1058;                       // 0x016a1058 mission-field id
extern unsigned g_147ebe0[3];                    // 0x0147ebe0 slot window ids
extern unsigned g_147ebec[3];                    // 0x0147ebec slot label ids
void  operator_delete_(void* p);            // 0x00f47380
struct Lay   { void* FindWindowByID(int id, int a); };  // 0x008105b0 thiscall ret8
void  FUN_d3a0(void* self, void* p);        // 0x00dfd3a0 (__thiscall ret4, see TFun2)
void  FUN_e0e0(void* self, void* p);        // 0x00dfdfe0 (__thiscall ret4, see TFun2)
typedef void (__thiscall* TFun2)(void* self, void* p);
struct F28 { void M(); };                   // 0x00f280f0 thiscall
struct VecC { void F(unsigned a, unsigned b); }; // 0x00dfc600 thiscall ret8
struct Obj4 { void F_bba0(); };             // 0x00dfbba0 thiscall
struct VecB { void F_b850(unsigned a, unsigned b); }; // 0x00dfb850 thiscall ret8
struct UI2 {
    void M_d8a0();              // 0x00dfd8a0 thiscall
    void F_de90();              // 0xdfde90
    void* F_e170(int* p);       // 0xdfe170
    UI2(const UI2& s);          // 0x00dfdfe0 thiscall ret4
};
void* ObjectTemplateDB_s00df_d5b0();                        // 0x0067cb40
void* GetManager_67dcd0();                       // 0x0067dcd0 ResourceManager
void* AppSystem_67dd00();                        // 0x0067dd00 SP::AppSystem
int   GetAssetState_552300(const void* key);     // 0x00552300 (caller pops)
void __fastcall Vec34_assign_dfcee0(void* self, void* d, const void* src);  // 0x00dfcee0 ret4
void __fastcall PtrVecBase_4aa350(void* self, void* d, unsigned n, const void* allocTag); // 0x004aa350 ret8
static inline void freeQuery(void* p) {
    if (p != 0 && ((int*)p)[-1] != 0)
        operator_delete_(p);
}
extern void*    g_16a1344_s00df_d5b0;                       // 0x016a1344 kGUI_PanelIDs
namespace SP {
namespace FunctionalMatch {
 struct Constraint_s00df_d5b0; struct CVec; 
}
}
void __fastcall Constraint_copyCtor_606880(SP::FunctionalMatch::Constraint_s00df_d5b0* self, void* d,
                                           const SP::FunctionalMatch::Constraint_s00df_d5b0* src); // 0x00606880
namespace SP {
namespace FunctionalMatch {
struct CVec {                                   // vector of Constraint, 0x14 bytes
    Constraint_s00df_d5b0* mpBegin;                        // +0x00
    Constraint_s00df_d5b0* mpEnd;                          // +0x04
    Constraint_s00df_d5b0* mpCapacity;                     // +0x08
    const char* mpName;                         // +0x0c
    unsigned    mFlags;                         // +0x10
    CVec() : mpBegin(0), mpEnd(0), mpCapacity(0), mpName(0), mFlags(0) {}
    CVec(const CVec& x);                                       // 0x004e38d0
    void DoDestroyValues(Constraint_s00df_d5b0* first, Constraint_s00df_d5b0* last); // 0x004e39a0
    void DoInsertValue(Constraint_s00df_d5b0* pos, const Constraint_s00df_d5b0& v);  // 0x004e39d0
    void push_back(const Constraint_s00df_d5b0& v);
    void destroy();
};
}
}
namespace SP {
namespace FunctionalMatch {
struct Constraint_s00df_d5b0 {                             // 0x24 bytes
    unsigned mParameter;                        // +0x00
    unsigned mType;                             // +0x04
    unsigned mValueMin;                         // +0x08
    unsigned mValueMax;                         // +0x0c
    CVec     mConstraints;                      // +0x10 (0x14 bytes)
};
}
}
namespace SP {
namespace FunctionalMatch {
inline void CVec::push_back(const Constraint_s00df_d5b0& v) {
    if (mpEnd < mpCapacity) {
        Constraint_s00df_d5b0* slot = mpEnd;
        mpEnd = (Constraint_s00df_d5b0*)((char*)mpEnd + 0x24);
        if (slot != 0)
            Constraint_copyCtor_606880(slot, 0, &v);
    } else {
        DoInsertValue(mpEnd, v);
    }
}
}
}
namespace SP {
namespace FunctionalMatch {
inline void CVec::destroy() {
    DoDestroyValues(mpBegin, mpEnd);
    if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
        operator_delete_(mpBegin);
}
}
}
void __fastcall Constraint_ctorEqual_558960(SP::FunctionalMatch::Constraint_s00df_d5b0* self, void* d,
                                            unsigned id, int op, int val);   // 0x00558960
void __fastcall Constraint_ctorNotEq_558a20(SP::FunctionalMatch::Constraint_s00df_d5b0* self, void* d,
                                            unsigned id, int op, int val);   // 0x00558a20
void __fastcall Constraint_ctorAny_558ae0 (SP::FunctionalMatch::Constraint_s00df_d5b0* self, void* d,
                                            int any, SP::FunctionalMatch::CVec vec); // 0x00558ae0
static inline void DBFindTemplates(void* out, void* query) {
    void* db = ObjectTemplateDB_s00df_d5b0();
    ((void(__fastcall*)(void*, void*, void*, void*))(*(void***)db)[0x38 / 4])(db, 0, out, query);
}
namespace EA {
namespace Random {
struct RandomLinearCongruential_s00df_d5b0 { unsigned RandomUint32Uniform(unsigned n); };  // 0x00a68fb0
}
}
extern EA::Random::RandomLinearCongruential_s00df_d5b0 cRandomGlobal;      // 0x01601760
struct Slot_s00df_d5b0 {                                   // 0x38-byte window slot entry
    int  x;                                     // +0x00
    int  y;                                     // +0x04
    int  z;                                     // +0x08
    char pad0c[0x14];                           // +0x0c..+0x1f
    char state;                                 // +0x20
    char pad21[0x17];                           // +0x21..+0x37
};
struct PropKey_s00df_d5b0 {                                // selection key, 0x18 bytes
    int type;                                   // +0x00
    int a1;                                     // +0x04
    int a2;                                     // +0x08
    int a3;                                     // +0x0c
    int a4;                                     // +0x10
    int a5;                                     // +0x14
};
struct WString_s00df_d5b0 {                                // eastl::basic_string<wchar_t>, 0x10 bytes
    void* mpBegin;                              // +0x00
    void* mpEnd;                                // +0x04
    void* mpCap;                                // +0x08
    void* mpName;                               // +0x0c
    void Assign(const unsigned short* b, const unsigned short* e);   // 0x00423650
};
struct GGUI_s00df_d5b0 {                                   // Simulator UI base (cf. slice s00df9650)
    void*    mVftable;                          // +0x000
    char     pad004[0x08];                      // +0x004..+0x00b
    void*    mItem;                             // +0x00c Item*: [0]=id, [0x20]=state
    char     pad010[0x10];                      // +0x010..+0x01f
    unsigned mTimer20;                          // +0x020
    char     pad024[0x08];                      // +0x024..+0x02b
    int      mIndex;                            // +0x02c
    unsigned mCount;                            // +0x030
    int      mCur;                              // +0x034
    char     pad038[0x10];                      // +0x038..+0x047
    char     mLayout[0x18];                     // +0x048 (SPUILayout; only &mLayout is used)
    char     pad060[0x1c];                      // +0x060..+0x07b
    char     m7c;                               // +0x07c
    char     m7d;                               // +0x07d
    char     m7e;                               // +0x07e
    char     m7f;                               // +0x07f
    char     pad080[0x0c];                      // +0x080..+0x08b
    PropKey_s00df_d5b0  m8c;                               // +0x08c..+0x0a3
    int      mA4;                               // +0x0a4
    int      mA8;                               // +0x0a8
    int      mAC;                               // +0x0ac
    char     mB0[0x10];                         // +0x0b0..+0x0bf
    Slot_s00df_d5b0     mSlots[3];                         // +0x0c0..+0x167
    WString_s00df_d5b0  mName;                             // +0x168..+0x177
    void FUN_00df97e0_GGUI();                   // 0x00df97e0
    void FUN_00df9c80_GGUI(unsigned id);        // 0x00df9c80
    void FUN_00df9b30_GGUI(int a);              // 0x00df9b30
    void FUN_00df9ef0_GGUI();                   // 0x00df9ef0
};
namespace Simulator {
struct cEditorModeUI : GGUI_s00df_d5b0 {                   // editor-mode template panel
    void Setup();                               // 0x00dfd5b0
    void RebuildPanel();                        // 0x00dfd8a0
    void Setup2();                              // 0x00dfdc50
};
}
namespace SP {
struct cSPUIMissions : GGUI_s00df_d5b0 {                   // mission-fields panel
    int* QueryMissionFields(void* out);         // 0x00dfda50
    void UpdateMissionFieldsSpace();            // 0x00dfe220
};
}
// ---- items of slice s00dfd5b0 end

// ---- items of slice s00dfe460 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __fastcall FUN_00f280f0(void* self, int dummy);
extern "C" void  __fastcall FUN_00dfbba0(void* self, int dummy);
extern "C" void  __cdecl FUN_00dfdfe0(void*);
extern "C" void* __cdecl FUN_00dfd250(void*, void*, void*);
extern "C" void* __cdecl FUN_00dfd2c0(void*, void*, void*);
extern "C" void  __cdecl FUN_00dfd4e0(void*, void*, void*, void*, void*);
extern "C" void __fastcall WStr_Assign(void* self, int dummy, void* begin, void* end); // 0x00423650 thiscall ret 8
extern "C" uint32_t __cdecl FUN_00435e90();     // GetRecorderState
extern "C" void  __cdecl FUN_00435ed0(uint32_t id, uint32_t value);  // RecordEvent2
extern "C" void* __cdecl FUN_00dfe9a0(void* f, void* l, void* d);                 // 0x00dfe9a0
extern "C" void* __cdecl FUN_00dff270(void* f, void* l, void* d);                 // 0x00dff270
extern "C" void  __cdecl FUN_00dfeaa0(void** out, void* f, void* l, void* d, void* o); // 0x00dfeaa0
extern "C" void  __cdecl FUN_00dff460(void** out, void* f, void* l, void* d, void* o); // 0x00dff460
struct V188 {
    void* b; void* e; void* cap;
    V188* Assign(V188* other);                       // 0x00dfeb00 ret 4
    void* Alloc(uint32_t n, void* f, void* l);       // 0x00dfe9e0 ret 0xc
    void  Destroy(void* f, void* l);                 // 0x00dfc600 ret 8
};
struct V4e0 {
    void* b; void* e; void* cap;
    V4e0* Assign(V4e0* other);                       // 0x00dfec50 ret 4
    V4e0* AssignWrap(V4e0* other);                   // 0x00dfed90 ret 4
    void* Alloc(uint32_t n, void* f, void* l);       // 0x00dfea40 ret 0xc
    void  Destroy(void* f, void* l);                 // 0x00dfc660 ret 8
};
struct CStr {
    uint8_t mData[0x3c];                             // own storage, 0x3c bytes
    void Assign(void* o);                            // 0x006b5430 thiscall ret 4
    void Destroy();                                  // 0x00f280f0 thiscall, ??1CStr@@QAE@XZ
};
struct ElemA {                                       // 0x2788-class
    void* CopyAssign(void* o);                       // 0x00dfedb0 ret 4
    void* CopyCtor(void* o);                         // 0x00dff1a0 ret 4
};
struct ElemB {                                       // 0x27e8-class
    void* CopyCtor(void* o);                         // 0x00dfee80 ret 4
    void* Init(void* o);                             // 0x00dff130 ret 4
};
struct Buf3c {
    void Copy(void* o);                              // 0x00dfb280 thiscall ret 4
};
struct Any3 {                                       // three-word command payload
    uint32_t a, b, c;
};
struct CmdObj {                                     // command object carried by a message
    virtual uint32_t Vf00();
    virtual uint32_t Vf01();
    virtual uint32_t Vf02();
    virtual uint32_t Vf03();
    virtual uint32_t Vf04();
    virtual uint32_t Vf05();
    virtual uint32_t Vf06();
    virtual uint32_t CommandId();                   // +0x1c
    virtual uint32_t Vf08();
    virtual uint32_t Vf09();
    virtual uint8_t  Flags();                       // +0x28
};
struct GGUIMsg {
    CmdObj*  mpObj;                                 // +0x00
    uint32_t mPad004;                               // +0x04
    uint32_t mType08;                               // +0x08
};
struct AudioSys_s00df_e460 {
    virtual uint32_t Vf00();
    virtual uint32_t Vf01();
    virtual uint32_t Vf02();
    virtual uint32_t Vf03();
    virtual uint32_t Vf04();
    virtual uint32_t Vf05();
    virtual uint32_t Vf06();
    virtual uint32_t Vf07();
    virtual uint32_t EventId();                     // +0x20
};
struct cSPUIWindow {                                // window object
    virtual uint32_t Vf00();
    virtual uint32_t Vf01();
    virtual uint32_t Vf02();
    virtual cSPUIWindow* FindChild(uint32_t id);    // +0x0c
    virtual uint32_t Vf04();
    virtual uint32_t Vf05();
    virtual uint32_t Vf06();
    virtual uint32_t Vf07();
    virtual uint32_t Vf08();
    virtual uint32_t Vf09();
    virtual uint32_t Vf10();
    virtual uint32_t Vf11();
    virtual uint32_t Vf12();
    virtual uint32_t Vf13();
    virtual uint32_t Vf14();
    virtual uint32_t Vf15();
    virtual uint32_t Vf16();
    virtual uint32_t Vf17();
    virtual uint32_t Vf18();
    virtual uint32_t Vf19();
    virtual uint32_t Vf20();
    virtual void*    GetText();                     // +0x54
    virtual uint32_t Vf22();
    virtual uint32_t Vf23();
    virtual void     SetText(void* text, int b);    // +0x60
};
struct cSPUILayout_s00df_e460 {                                // layout anchored at space+0x48
    uint8_t mData[0x36];
    cSPUIWindow* FindWindowByID(uint32_t id, int flag);   // 0x008105b0 ret 8
};
struct WString_s00df_e460 {
    wchar_t* mpData;                                // +0x00
    void Append(void* text);                        // 0x005c3d90 ret 4
};
struct SomeActive {                                 // object behind globals+0x1c
    char IsActive();                                // 0x00ec4320
};
struct cEditorGlobals {                             // object behind 0x016c7aa4
    uint32_t    mPad000[7];
    SomeActive* mpActive1c;                         // +0x001c
};
struct IfcStateSub {                                // object behind ifcstate+0x198
    void NotifySequence();                          // 0x00de0890
};
struct cInterfaceState_s00df_e460 {                            // object behind 0x016a1344
    uint32_t    mPad000[0x198 / 4];
    IfcStateSub* mpSub198;                          // +0x198
    void SetSlotMode(uint32_t a, uint32_t b);       // 0x00de86d0
    void SetEntryFlag(char v);                      // 0x00de5330
};
extern "C" cEditorGlobals*    g_pEditorGlobals;    // 0x016c7aa4
extern "C" cInterfaceState_s00df_e460*   g_pInterfaceState;   // 0x016a1344
struct cSPUISpace {
    uint32_t     mPad000[(0x20 - 0x00) / 4];
    int32_t      mMode20;                           // +0x20  current editor mode
    uint32_t     mPad024[(0x48 - 0x24) / 4];
    cSPUILayout_s00df_e460  mLayout48;                         // +0x48
    uint8_t      mFlag7e;                           // +0x7e
    uint8_t      mPad07f[0xa4 - 0x7f];
    Any3         mAny3A4;                           // +0x0a4
    uint32_t     mPad0b0[(0x168 - 0xb0) / 4];
    WString_s00df_e460      mStr168;                           // +0x168
    char DoMessage(int arg1, GGUIMsg* msg);         // 0x00dfe460 ret 8
    void Fn9990();                                  // 0x00df9990
    void Fn9ef0();                                  // 0x00df9ef0
    void Fn9e60();                                  // 0x00df9e60
    void Fn9a70();                                  // 0x00df9a70
    void Fn9a00();                                  // 0x00df9a00
    void Fn9ad0();                                  // 0x00df9ad0
    void SetModeEnabled(int on);                    // 0x00dfab20 ret 4
    void FnAe50();                                  // 0x00dfae50
    void FnA460(Any3* p, int b);                    // 0x00dfa460 ret 8
    void LaunchAssetBrowser(int kind);              // 0x00dfa5c0 ret 4
    void FnAf80();                                  // 0x00dfaf80
    void FnD5b0();                                  // 0x00dfd5b0
    void FnDc50();                                  // 0x00dfdc50
    void FnDe90();                                  // 0x00dfde90
    void FnE220();                                  // 0x00dfe220
    char CheckX();                                  // 0x00dfc500
};
static __forceinline void RecordEvent(uint32_t id) { // 0x00435ed0 wrapper
    FUN_00435ed0(id, FUN_00435e90());
}
static __forceinline uint32_t AudioEventValue() {   // audio system event tag
    AudioSys_s00df_e460* p = (AudioSys_s00df_e460*)FUN_00a206f0();
    return p ? p->EventId() : 0;
}
struct Elem27e8 { char pad[0x78]; void* mp; };   // vector member at +0x78
Elem27e8* __stdcall DestroyRange27e8(Elem27e8* first, Elem27e8* last);  // 0x00dfe910 (defined below; used by a stub's inline body)
struct VecAny {
    void* mpBegin;                                   // +0x00
    void* mpEnd;                                     // +0x04
    void* mpCapacity;                                // +0x08
    void DestroyRange(void* first, void* last);           // 0x00dfdf70 ret 8
    void DestroyRangeUnk(void* first, void* last);        // 0x00dfd300 ret 8
    void DestroyRange27e8(void* first, void* last);       // 0x00dfe910 ret 8
    void DestroyRange534(void* first, void* last);        // 0x00dfdf10 ret 8
    void DestroyRangeVariant(void* first, void* last);    // 0x00685a30 ret 8
};
struct cUISpaceRes {
    void*     mpVtbl00;                              // +0x0000
    uint32_t  mPad04[(0x18 - 0x04) / 4];
    void*     mpVtbl18;                              // +0x0018
    uint32_t  mPad1c[(0x30 - 0x1c) / 4];
    VecAny    mVec30;                                // +0x0030  EA::Variant vector
    uint32_t  mPad3c[(0x48 - 0x3c) / 4];
    void*     mpTracer48;                            // +0x0048  object with a virtual dtor
    uint32_t  mPad4c[(0x7c - 0x4c) / 4];
    CStr      mStr7c;                                // +0x007c
    CStr      mStrB8;                                // +0x00b8
    CStr      mStrF4;                                // +0x00f4
    uint32_t  mPad130[(0x178 - 0x130) / 4];
    void*     mpOwned178;                            // +0x0178  owned allocation ([-4] flag)
    uint32_t  mPad17c[(0x23c - 0x17c) / 4];
    VecAny    mPod23c;                               // +0x023c  eastl::pod_array<0x534>
    uint32_t  mPad248[(0x2bf4 - 0x248) / 4];
    VecAny    mVec2bf4;                              // +0x2bf4  vector of 0x27e8 elements
    uint32_t  mPad2c00[(0x2c10 - 0x2c00) / 4];
    VecAny    mVec2c10;                              // +0x2c10  vector of unnamed elements
    uint32_t  mPad2c1c[(0x2c54 - 0x2c1c) / 4];
    void*     mpRaw2c54;                             // +0x2c54  raw allocation
    uint32_t  mPad2c58[(0x2c6c - 0x2c58) / 4];
    VecAny    mVec2c6c;                              // +0x2c6c  vector of 0x27e0 elements
    uint32_t  mPad2c78[(0x2c80 - 0x2c78) / 4];
    void*     mpOwned2c80;                           // +0x2c80  owned allocation ([-4] flag)
    void Destroy();                                  // 0x00dfef70  destructor body
};
static inline void OwnedFree(void* p) {
    if (p && ((int*)p)[-1] != 0)
        EA_Free(p);
}
static inline void RawFree(void* p) {
    if (p)
        EA_Free(p);
}
struct V238 {
    void* mpBegin; void* mpEnd; void* mpCapacity;
    V238* Assign(V238* other);                       // 0x00dff330 ret 4
    void* Alloc(uint32_t n, void* f, void* l);       // 0x00dff0d0 ret 0xc
    void  DestroyRange(void* f, void* l);            // 0x00dfd300 ret 8
};
struct V534 {
    void* mpBegin; void* mpEnd; void* mpCapacity;
    V534* Assign(V534* other);                       // 0x00dff650 ret 4
    void* Alloc(uint32_t n, void* f, void* l);       // 0x00dff530 ret 0xc
    void  DestroyRange(void* f, void* l);            // 0x00dfdf10 ret 8
};
// ---- items of slice s00dfe460 end

// ---- items of slice s00e00760 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl FUN_0093a560();
extern "C" void  __cdecl FUN_0093a480();
extern "C" void  __cdecl FUN_004b5440();
extern "C" void  __cdecl FUN_00de5ee0();
extern "C" void* __cdecl FUN_00de0a90();
extern "C" void  __cdecl FUN_00e02040(void* arg);
extern "C" double __cdecl cos(double);
#pragma intrinsic(cos)
extern "C" void  __cdecl FUN_0093a1a0_s00e0_0760();
typedef void  (__thiscall* VFnV)(void*);
typedef void* (__thiscall* VFnPU)(void*, uint32_t);
#define VSLOT_s00e0_0760(o, off) (*(void**)((char*)(*(void**)(o)) + (off)))
struct AllocObj { void* FUN_00de0a90(void* gp, int flag); };
struct CtxObj { void ShowContextSporepedia(void* info); uint8_t PeekObjFlag(void* p); };
void* g_16a1344_s00e0_0760;
void* g_016a15fc;
struct MgrObj { void* Ctor(); void Dtor(); };
struct StopwatchObj {
    void  FUN_0093a560(int units, int start);   // EA::Stopwatch::Stopwatch
    void  FUN_0093a1a0_s00e0_0760(int units);              // EA::Stopwatch::SetUnits
    uint64_t mnStartTime;                       // +0x00
    uint64_t mnTotalElapsedTime;                // +0x08
    int      mnUnits;                           // +0x10
    float    mfCyclesToUnitsCoefficient;        // +0x14
};
struct LimitStopwatchObj : StopwatchObj {
    uint64_t mnEndTime;                         // +0x18
    void  FUN_0093a480(unsigned int limit, int start);   // EA::LimitStopwatch::SetTimeLimit
};
struct RefVecObj {
    void  FUN_004b5440();                       // vector-of-refcounted destructor
    void  FUN_00de5ee0(void* begin, void* end); // destroy range (this = vector)
    void* mpBegin;                              // +0x00
    void* mpEnd;                                // +0x04
    void* mpEndCap;                             // +0x08
};
struct LaunchCtx {                       // stack temp built by 0x00644b10
    uint32_t pad00;                      // +0x00
    uint32_t pad04;                      // +0x04
    uint32_t pad08;                      // +0x08
    void*    mpObj;                      // +0x0c  allocated launcher object
    uint8_t  f10;                        // +0x10
    uint16_t pad11;                      // +0x11
    uint8_t  f13;                        // +0x13
    uint32_t pad14;                      // +0x14
    uint32_t f18;                        // +0x18
    uint32_t f1c;                        // +0x1c
    uint32_t f20;                        // +0x20
    uint8_t  f24;                        // +0x24
    uint32_t pad2c;                      // +0x2c
    void Ctor();                         // 0x00644b10
    void Dtor();                         // 0x00644b60
};
// ---- items of slice s00e00760 end

// ---- items of slice s00de8ad0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern bool gbSkipSave;                                                  // 0x016a0f28
extern "C" void* __cdecl memmove(void*, const void*, unsigned int);
typedef wchar_t char16;
struct ResourceKey_s00de_8ad0 { uint32_t instanceID, typeID, groupID; };
struct allocator { allocator() {} };
struct string16 {
    char16* mpBegin;
    char16* mpEnd;
    char16* mpCapacity;
    uint32_t mAllocator;
    string16(const char16* p, const allocator& a = allocator());          // 0x0041df50
    ~string16() { DeallocateSelf(); }
    void DeallocateSelf();                                                // 0x00933960
    unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
    string16 substr(unsigned int position, unsigned int n) const;         // 0x00453d20
    string16& operator=(const string16& x);                               // 0x0057cb60
};
struct cString_s00de_8ad0 {
    uint32_t mData[4];
    cString_s00de_8ad0();                                                            // 0x006b5060
    ~cString_s00de_8ad0();                                                           // 0x006b5240
    void Load(uint32_t tableID, uint32_t instanceID, const char16* pDefault);  // 0x006b54b0
    const char16* GetText();                                              // 0x006b55c0
};
class IHandlerForward {
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
    virtual bool DoMessage(uint32_t messageID, void* pMessage);          // 34
};
class IWindow_s00de_8ad0 {
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
    virtual void SetEnabled(bool a, bool b);                              // 7c
};
class cSPUIGlobalUI_s00de_8ad0 { public:
    IWindow_s00de_8ad0* FindWindowByID(uint32_t id);                                 // 0x00e012b0
    void SetVisibility(bool visible);                                     // 0x00e01350
};
struct cSPUIBrowser { void Update(); };                                  // 0x0064ab20
struct cAssetBrowserState { uint32_t pad[0x1c / 4]; bool mbBusy; };       // +1c
cSPUIBrowser* AssetBrowser();                                            // 0x00401030
cSPUIBrowser* SporeGuide();                                              // 0x00401040
struct cMessageServer {
virtual void _v00();
virtual void _v04();
virtual void _v08();
virtual void _v0c();
    virtual void _v10();
    virtual void SendMessage(uint32_t messageID, void* msg, int a);       // 14
};
cMessageServer* MessageServer_s00de_8ad0();                                         // 0x0067dcc0
struct cTextDisplay {
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
    virtual void ShowText(const char16* text, int flags);                 // 34
};
struct cTextDisplayHost {
virtual void _v00();
virtual void _v04();
virtual void _v08();
virtual void _v0c();
virtual void _v10();
virtual void _v14();
virtual void _v18();
virtual void _v1c();
    virtual cTextDisplay* GetTextDisplay();                               // 20
};
cTextDisplayHost* TextDisplayHost();                                     // 0x0067de40
struct cAchievementsController {
    bool IsDisabled();                                                   // 0x005c0dd0
    void AwardAchievement(uint32_t id);                                   // 0x00676710
};
cAchievementsController* AchievementsController();                       // 0x00675250
struct cStarManager_s00de_8ad0 {
    void SaveState();                                                    // 0x00bb6650
    void LoadStarDatabase();                                             // 0x00bb8b20
    void RefreshState();                                                 // 0x00bb7620
};
cStarManager_s00de_8ad0* StarManager_s00de_8ad0();                                             // 0x00b3d2a0
struct cPollenEntry { uint32_t pad[0xb8 / 4]; struct cPollenItem* mpItem; };  // 0xbc bytes
struct cPollenItem { void Refresh(); };                                  // 0x00df6740
template <typename T> struct sp_vector {
    T* mpBegin; T* mpEnd; T* mpCapacity; uint32_t mAllocator;
    unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
    T& operator[](unsigned int n) { return mpBegin[n]; }
};
struct cPollenManager {
    uint32_t pad00[2];
    sp_vector<cPollenEntry> mEntries;                                    // +08
    void Refresh();                                                      // 0x00df95d0
};
cPollenManager* PollenManager();                                         // 0x00df5f40
struct cEditorGlobal { void SetPaused(bool b); };                        // 0x00df53d0
extern cEditorGlobal* gpEditorGlobal;                                    // 0x016a15f4
struct cCalloutTarget { uint32_t pad; };
extern cCalloutTarget gCalloutTarget;                                    // 0x015a41d4
extern const ResourceKey_s00de_8ad0 kCalloutPublish;                                // 0x015a3860
extern const ResourceKey_s00de_8ad0 kCalloutSave;                                   // 0x015a386c
extern const ResourceKey_s00de_8ad0 kCalloutSaveConfirm;                            // 0x015a3878
extern const ResourceKey_s00de_8ad0 kCalloutExit;                                   // 0x015a3884
extern const ResourceKey_s00de_8ad0 kCalloutError;                                  // 0x015a3890
extern const ResourceKey_s00de_8ad0 kCalloutExitConfirm;                            // 0x015a389c
extern const ResourceKey_s00de_8ad0 kCalloutCloseConfirm;                           // 0x015a38a8
void CalloutMessageBox(cCalloutTarget* target, const ResourceKey_s00de_8ad0* key);  // 0x00809db0
int GetCurrentGameMode();                                                // 0x00b5b800
void ShowContextSensitiveSporeGuide();                                   // 0x00e02200
void OpenSporepedia();                                                   // 0x00e02c40
struct cDialogOwner { uint32_t pad[0xc / 4]; void* mpOwner; };           // +0c
cDialogOwner* FindDialog(void* key);                                     // 0x00de46c0
struct cEditorDialog {
    uint32_t pad[0x3c / 4];
    int mResult;                                                         // +3c
    bool mbWasPaused;                                                    // +40
    bool IsReadyToClose();                                               // 0x00e205d0
    void Close();                                                        // 0x00e20860
};
struct cPendingDialog { uint32_t pad[0xac / 4]; bool mbOpen; };          // +ac
struct cLaunchData { uint32_t pad[0x18 / 4]; ResourceKey_s00de_8ad0 mKey; };        // +18
struct cLaunchDataPtr {
    cLaunchData* mpObject;
    void Set(void* p);                                                   // 0x00572620
};
struct cInsertResult { void* mpNode; bool mbInserted; cInsertResult() {} };
struct cMessage_s00de_8ad0;
struct cMessageSet { cInsertResult insert(cMessage_s00de_8ad0* const& value); };        // 0x00a18440
struct cSubPanel { void HandleMessage(void* pMessage); };                // 0x00de6e80
struct cMessage_s00de_8ad0 { uint32_t pad[2]; int mValue; };                        // +08
class cSPUIAssetBrowserCallback { public: virtual void _cb0(); };
class IWinProc_s00de_8ad0 { public: virtual void _wp0(); };
class IHandlerRC {
public:
    virtual bool DoMessage(uint32_t messageID, void* pMessage) = 0;
};
class cSPEditorUI : public cSPUIAssetBrowserCallback, public IWinProc_s00de_8ad0, public IHandlerRC {
public:
    uint32_t pad0C[(0x38 - 0xc) / 4];
    IHandlerForward* mpForwardHandler;       // +38
    cSubPanel mSubPanel;                     // +3c
    uint8_t pad3D[0xc9 - 0x3d];
    bool mbHasModel;                         // +c9
    uint8_t padCA[0xd0 - 0xca];
    string16 mModelName;                     // +d0
    int mUndoCount;                          // +e0
    bool mbLoginPending;                     // +e4
    uint8_t padE5[3];
    int mDialogState;                        // +e8
    uint8_t padEC;
    bool mbRefreshPending;                   // +ed
    bool mbBrowserPending;                   // +ee
    bool mbActivated;                        // +ef
    cEditorDialog* mpDialog;                 // +f0
    uint32_t padF4[2];
    cPendingDialog* mpPendingDialog;         // +fc
    uint8_t pad100;
    bool mbAssetBrowserOpen;                 // +101
    bool mbPublishOpen;                      // +102
    uint8_t pad103;
    bool mbSaveRequested;                    // +104
    uint8_t pad105[3];
    int mLoginState;                         // +108
    int mLoginAction;                        // +10c
    uint32_t pad110[(0x184 - 0x110) / 4];
    cSPUIGlobalUI_s00de_8ad0* mpGlobalUI;               // +184
    ResourceKey_s00de_8ad0 mKeyToLoad;                  // +188
    uint32_t pad194[(0x1f0 - 0x194) / 4];
    uint8_t pad1F0;
    bool mbHidden;                           // +1f1
    uint8_t pad1F2[3];
    bool mbAchievementSent;                  // +1f5
    uint8_t pad1F6[0x24c - 0x1f6];
    bool mbResultsReceived;                  // +24c
    bool mbTutorialDone;                     // +24d
    uint8_t pad24E[2];
    cLaunchDataPtr mpLaunchData;             // +250
    cMessageSet mPendingMessages;            // +254
    uint8_t pad255[0x270 - 0x255];
    bool mbInputLocked;                      // +270

    virtual bool DoMessage(uint32_t messageID, void* pMessage);

    void UpdateLoginButton(bool b);          // 0x00de5040
    void OnBrowserClosed();                  // 0x00de4630
    void ShowSaveDialog();                   // 0x00de5260
    void ShowDialog(int id, int a);          // 0x00de86d0
    void OnSaveAccepted();                   // 0x00de4a70
    void OnSaveRejected();                   // 0x00de4b30
    void LockUI(bool b);                     // 0x00de4bc0
    bool IsPaused();                         // 0x00de4c00
    void SetPaused(bool b);                  // 0x00de4c20
    void Refresh();                          // 0x00de52d0
    void ShowPublish(int a);                 // 0x00de53d0
    void PreparePublish();                   // 0x00de4b00
    void UpdateTitle();                      // 0x00de4850
    void OnExitRequested();                  // 0x00de95a0
};
struct cMessageSlot {
    uint8_t mData[0x1c];
    void* GetData(void* key);                // 0x00de7590
};
struct cEditorMessageTarget {
    uint8_t pad00[0x38];
    cMessageSlot mSlot38;                    // +38
    cMessageSlot mSlot54;                    // +54
    cMessageSlot mSlot70;                    // +70
    void OnEditorMessageReceived(void* pMessage);  // 0x00de9600
};
struct IAttachment {
    virtual void _a00();
    virtual void Release();                  // +04
};
struct IMessageReader {
virtual void _r00();
virtual void _r04();
virtual void _r08();
    virtual bool ReadMessage(void* arg, void* out, int a, int b, int c, int d);  // +0c
};
IMessageReader* CreateMessageReader();                                    // 0x0067dcd0
struct IEditorNode {
virtual void _n00();
virtual void _n04();
virtual void _n08();
virtual void _n0c();
virtual void _n10();
virtual void _n14();
virtual void _n18();
virtual void _n1c();
virtual void _n20();
virtual void _n24();
virtual void _n28();
    virtual void SetAttachment(void* p);                                 // +2c
};
IEditorNode* CreateEditorNode(void* source);                              // 0x006a1c40
void SetEditorNodeValue(IEditorNode* node, void* value);                 // 0x006a1710
void ReleaseEditorNode(IEditorNode* node);                               // 0x006a3dd0
struct cEntryVector {
    cPollenEntry* mpBegin;                   // +00
    cPollenEntry* mpEnd;                     // +04
    cPollenEntry* mpCapacity;                // +08
    uint32_t mAllocator;                     // +0c

    cPollenEntry* MoveTail(cPollenEntry* first, cPollenEntry* last);      // 0x00de97a0
    void insert(cPollenEntry* position, unsigned int count,
                const cPollenEntry& value);                              // 0x00de97f0
    void DestroyRange(cPollenEntry* first, cPollenEntry* last);           // 0x00de5ee0
};
cPollenEntry* CopyConstructEntries(cPollenEntry* first, cPollenEntry* last,
                                   cPollenEntry* dest);                   // 0x00de6070
void* __cdecl MessageAllocate(unsigned int size, const char* name, int flags,
                              int align, const char* file, int line);      // 0x00f473a0
void __cdecl MessageFree(void* p);                                        // 0x00f47380
bool cSPEditorUI::DoMessage(uint32_t messageID, void* pMessage)
{
    if (mpForwardHandler)
        mpForwardHandler->DoMessage(messageID, pMessage);

    switch (messageID) {
    case 0x30c11c7:
        if (pMessage) {
            cDialogOwner* owner = FindDialog((char*)pMessage + 0x10);
            if (owner && owner->mpOwner == this) {
                mpLaunchData.Set(pMessage);
                mKeyToLoad = mpLaunchData.mpObject->mKey;
            }
        }
        mbResultsReceived = true;
        break;

    case 0x238de9c:
        mbSaveRequested = true;
        ShowSaveDialog();
        break;

    case 0x44db12e:
        mbAssetBrowserOpen = false;
        if (pMessage && mbLoginPending && !((cAssetBrowserState*)AssetBrowser())->mbBusy) {
            UpdateLoginButton(true);
            mbLoginPending = false;
            OnBrowserClosed();
            return false;
        }
        UpdateLoginButton(pMessage != 0);
        if (mLoginState == 1 || mLoginState == 0)
            mLoginAction = 2;
        break;

    case 0x4519b5f: {
        mbHidden = false;
        if (mbBrowserPending) {
            mbBrowserPending = false;
            OnBrowserClosed();
        }
        IWindow_s00de_8ad0* window = mpGlobalUI->FindWindowByID(0x10ed874);
        if (window)
            window->SetEnabled(true, true);
        mpGlobalUI->SetVisibility(true);
        return false;
    }

    case 0x4fd2bce:
        if (mbHasModel)
            mbPublishOpen = true;
        break;

    case 0x4fd2bd3:
        mbPublishOpen = false;
        break;

    case 0x5120263:
        ShowContextSensitiveSporeGuide();
        break;

    case 0x5120264:
        if (GetCurrentGameMode() == 0x2ccd1d2) {
            ShowDialog(7, 1);
            return false;
        }
        OpenSporepedia();
        break;

    case 0x56bbd7f:
        mbAssetBrowserOpen = true;
        break;

    case 0x574f0a6:
        AssetBrowser()->Update();
        break;

    case 0x5b9ba6c:
        SporeGuide()->Update();
        break;

    case 0x5bd6378:
        if (!mbActivated)
            mbActivated = true;
        if (mLoginAction != 10)
            ShowDialog(10, 1);
        break;

    case 0x5d3c4e1:
        mbTutorialDone = true;
        break;

    case 0x5d6404b: {
        int button = ((cMessage_s00de_8ad0*)pMessage)->mValue;
        if (button == 0x1510d07)
            return false;
        switch (mDialogState) {
        case 1:
            if (button == -15) {
                MessageServer_s00de_8ad0()->SendMessage(0xce7afa41, 0, 0);
                mDialogState = 0;
            }
            break;
        case 2:
            switch (button) {
            case 0x5107b17:
                OnSaveAccepted();
                return true;
            case 0x5107b19:
                mDialogState = 0;
                break;
            case 0x5107b1a:
                OnSaveRejected();
                return true;
            }
            break;
        case 3:
            switch (button) {
            case 0x5107b19:
                mDialogState = 4;
                CalloutMessageBox(&gCalloutTarget, &kCalloutSaveConfirm);
                return true;
            case 0x5107b1a:
                mDialogState = 0;
                if (mpDialog) {
                    mpDialog->mResult = 3;
                    mpDialog->Close();
                    return true;
                }
                break;
            }
            break;
        case 4:
        case 6:
        case 7:
            if (button == -15) {
                mDialogState = 0;
                return true;
            }
            break;
        case 5:
            switch (button) {
            case 0x5107b19:
                if (gpEditorGlobal)
                    gpEditorGlobal->SetPaused(true);
                SetPaused(mpDialog->mbWasPaused);
                return true;
            case 0x5107b1a:
                LockUI(false);
                mDialogState = 7;
                CalloutMessageBox(&gCalloutTarget, &kCalloutExitConfirm);
                mpDialog->mResult = 7;
                mpDialog->Close();
                return true;
            }
            break;
        default:
            return false;
        }
        return true;
    }

    case 0x5d663cd:
        mpDialog->mbWasPaused = IsPaused();
        if (gpEditorGlobal)
            gpEditorGlobal->SetPaused(false);
        SetPaused(true);
        mDialogState = 5;
        CalloutMessageBox(&gCalloutTarget, &kCalloutExit);
        return true;

    case 0x5d66be3:
        LockUI(true);
        mDialogState = 3;
        CalloutMessageBox(&gCalloutTarget, &kCalloutSave);
        return true;

    case 0x5d6714b:
        if (IsPaused())
            SetPaused(false);
        else
            SetPaused(true);
        return true;

    case 0x5d676ed: {
        LockUI(false);
        uint32_t textID = 0;
        switch (((cMessage_s00de_8ad0*)pMessage)->mValue) {
        case 0: textID = 0x5d67a45; break;
        case 1: textID = 0x5d67a51; break;
        case 2: textID = 0x5ee138e; break;
        case 3: textID = 0x5ee1398; break;
        case 4: textID = 0x5f7a60e; break;
        }
        cString_s00de_8ad0 text;
        text.Load(0xd7f9d626, textID, L"*error message*");
        TextDisplayHost()->GetTextDisplay()->ShowText(text.GetText(), 0);
        mDialogState = 6;
        CalloutMessageBox(&gCalloutTarget, &kCalloutError);
        return true;
    }

    case 0x5dd52c7:
        if (!mbActivated)
            return false;
        mbActivated = false;
        if (mbRefreshPending) {
            mbRefreshPending = false;
            OnBrowserClosed();
        }
        Refresh();
        break;

    case 0x6203fdc:
        mbHidden = true;
        mpGlobalUI->SetVisibility(false);
        break;

    case 0x625d27c:
        StarManager_s00de_8ad0()->SaveState();
        StarManager_s00de_8ad0()->LoadStarDatabase();
        PollenManager()->Refresh();
        StarManager_s00de_8ad0()->RefreshState();
        break;

    case 0x625d27d:
        PollenManager()->Refresh();
        break;

    case 0x625e26a:
        if (mpPendingDialog && mpPendingDialog->mbOpen)
            ShowPublish(1);
        break;

    case 0x6382db7:
        PreparePublish();
        mDialogState = 2;
        CalloutMessageBox(&gCalloutTarget, &kCalloutPublish);
        break;

    case 0x64a5044:
        if (mbHasModel)
            ShowDialog(6, 1);
        break;

    case 0x64a504a:
        if (mbHasModel)
            Refresh();
        break;

    case 0x6579712:
        if (!mbAchievementSent && !AchievementsController()->IsDisabled()) {
            mPendingMessages.insert((cMessage_s00de_8ad0*)pMessage);
            if (!gbSkipSave)
                ShowSaveDialog();
            UpdateTitle();
        }
        break;

    case 0x680c633: {
        string16 name((const char16*)pMessage);
        if (name.size() > 4) {
            mModelName = name.substr(0, name.size() - 4);
            UpdateTitle();
        }
        return false;
    }

    case 0x7ca274b:
        ++mUndoCount;
        if (mUndoCount == 10)
            AchievementsController()->AwardAchievement(0xb5e59f);
        break;

    case 0x8085c4c:
        mLoginAction = 1;
        return true;

    case 0x275a9c8c:
        return true;

    case 0x634297ad:
        return true;

    case 0x67c75bd6:
        if (((cMessage_s00de_8ad0*)pMessage)->mValue == 1 && mLoginState == 8)
            mLoginAction = 9;
        return true;

    case 0x99eda4cd: {
        sp_vector<cPollenEntry>& entries = PollenManager()->mEntries;
        for (unsigned int i = 0; i < entries.size(); i++) {
            cPollenItem* item = entries[i].mpItem;
            if (item)
                item->Refresh();
        }
        mSubPanel.HandleMessage(pMessage);
        return false;
    }

    case 0xcc0bf724:
        mbInputLocked = false;
        break;

    case 0xcc0bf725:
        mbInputLocked = true;
        break;

    case 0xeda117de:
        return true;
    }
    return false;
}
// ---- items of slice s00de8ad0 end

// ---- items of slice s00df47b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const wchar_t* sNewGameFlowLayout; // 0x016a0cf8
extern const uint32_t kLevelIDs[4];       // 0x0147e800
extern const uint32_t kLevelButtonIDs[4]; // 0x0147e810
namespace eastl {
class allocator_s00df_47b0 { public:
    allocator_s00df_47b0() {}
};
}
namespace eastl {
template <bool B> struct integral_constant { };
}
namespace eastl {
typedef integral_constant<true> true_type;
}
namespace eastl {
template <typename T> struct basic_string_s00df_47b0 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    allocator_s00df_47b0 mAllocator;

    basic_string_s00df_47b0(const T* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p); }
    ~basic_string_s00df_47b0() { DeallocateSelf(); }

    void RangeInitialize(const T* pBegin);   // 0x00579a90
    void DoFree(T* p, size_t n)
    {
        if (p)
            delete[] (char*)p;
    }
    void DeallocateSelf()
    {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin, mpCapacity - mpBegin);
    }
    void clear()
    {
        if (mpBegin != mpEnd) {
            *mpBegin = 0;
            mpEnd = mpBegin;
        }
    }
};
}
namespace eastl {
typedef basic_string_s00df_47b0<wchar_t> string16_s00df_47b0;
}
namespace eastl {
template <typename T> class vector_s00df_47b0 { public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    allocator_s00df_47b0 mAllocator;

    void DoInsertValue(T* position, const T& value);   // 0x00b96600
    T* erase(T* first, T* last)
    {
        memcpy(first, last, (size_t)((char*)mpEnd - (char*)last));
        mpEnd -= (last - first);
        return first;
    }
    void clear() { erase(mpBegin, mpEnd); }
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);  // 0x00621fc0 (eastl::vector::DoInsertValue)
    }
};
}
namespace eastl {
template <typename T1, typename T2> struct pair_s00df_47b0 {
    T1 first;
    T2 second;
    pair_s00df_47b0(const T1& a, const T2& b);   // 0x008d6580 for <const string16, uint32_t>
};
}
namespace eastl {
struct hash_node_s00df_47b0 {
    pair_s00df_47b0<const string16_s00df_47b0, uint32_t> mValue;
    hash_node_s00df_47b0* mpNext;
};
}
namespace eastl {
extern void* gpEmptyBucketArray[2];   // 0x0154df28
}
namespace eastl {
struct hash_iterator {
    hash_node_s00df_47b0* mpNode;
    hash_node_s00df_47b0** mpBucket;
    hash_iterator(hash_node_s00df_47b0** pBucket) : mpNode(*pBucket), mpBucket(pBucket) {}
    hash_iterator(const hash_iterator& x) : mpNode(x.mpNode), mpBucket(x.mpBucket) {}
    pair_s00df_47b0<const string16_s00df_47b0, uint32_t>* operator->() const { return &mpNode->mValue; }
    bool operator!=(const hash_iterator& x) const { return mpNode != x.mpNode; }
};
}
namespace eastl {
struct prime_rehash_policy_s00df_47b0 {
    float mfMaxLoadFactor;
    float mfGrowthFactor;
    uint32_t mnNextResize;
    prime_rehash_policy_s00df_47b0(float fMaxLoadFactor = 1.0f)
        : mfMaxLoadFactor(fMaxLoadFactor), mfGrowthFactor(2.0f), mnNextResize(0) {}
};
}
namespace eastl {
struct hash_map_string16_uint {
    typedef pair_s00df_47b0<const string16_s00df_47b0, uint32_t> value_type;
    struct insert_return_type {
        hash_iterator first;
        bool second;
    };

    uint32_t mEmptyBases;   // the empty hash/equal functor bases occupy 4 bytes under MSVC
    hash_node_s00df_47b0** mpBucketArray;
    uint32_t mnBucketCount;
    uint32_t mnElementCount;
    prime_rehash_policy_s00df_47b0 mRehashPolicy;
    allocator_s00df_47b0 mAllocator;

    hash_map_string16_uint() : mnBucketCount(0), mnElementCount(0), mRehashPolicy() { reset(); }
    ~hash_map_string16_uint()
    {
        clear();
        DoFreeBuckets(mpBucketArray, mnBucketCount);
    }
    void reset()
    {
        mnElementCount = 0;
        mnBucketCount = 1;
        mpBucketArray = (hash_node_s00df_47b0**)&gpEmptyBucketArray[0];
        mRehashPolicy.mnNextResize = 0;
    }
    void DoFreeNodes(hash_node_s00df_47b0** pBucketArray, uint32_t n);   // 0x007c7050
    void DoFreeBuckets(hash_node_s00df_47b0** pBucketArray, uint32_t n)
    {
        if (n > 1)
            delete[] (char*)pBucketArray;
    }
    void clear()
    {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
    }
    hash_iterator end() { return hash_iterator(mpBucketArray + mnBucketCount); }
    hash_iterator find(const string16_s00df_47b0& k);                                     // 0x00def5f0
    insert_return_type DoInsertValue(const value_type& value, true_type);     // 0x00df0ad0
    insert_return_type insert(const value_type& value) { return DoInsertValue(value, true_type()); }
};
}
using eastl::string16_s00df_47b0;
struct ResourceKey_s00df_47b0 {
    uint32_t instanceID, typeID, groupID;
    ResourceKey_s00df_47b0(uint32_t i, uint32_t t, uint32_t g) : instanceID(i), typeID(t), groupID(g) {}
};
struct cRefCounted {
    virtual int AddRef();
    virtual int Release();
};
template <typename T> struct intrusive_ptr_s00df_47b0 {
    T* mpObject;
    intrusive_ptr_s00df_47b0() : mpObject(0) {}
    ~intrusive_ptr_s00df_47b0()
    {
        if (mpObject)
            mpObject->Release();
    }
    intrusive_ptr_s00df_47b0& operator=(T* p)
    {
        if (p != mpObject) {
            T* const pTemp = mpObject;
            if (p)
                p->AddRef();
            mpObject = p;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    T* get() const { return mpObject; }
};
struct cPropList_s00df_47b0 : cRefCounted { };
typedef intrusive_ptr_s00df_47b0<cPropList_s00df_47b0> PropListPtr_s00df_47b0;
struct cPropManager_s00df_47b0 {
    PV8 PV2 PV
    virtual bool GetPropertyListImpl(uint32_t instanceID, uint32_t groupID, PropListPtr_s00df_47b0& dst);   // +0x2c
    bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropListPtr_s00df_47b0& dst)
    {
        dst = 0;
        return GetPropertyListImpl(instanceID, groupID, dst);
    }
};
cPropManager_s00df_47b0* PropertyManager_s00df_47b0();                                                                  // 0x0067de30
bool GetPropertyAsString16Array(const cPropList_s00df_47b0* list, uint32_t id, int& count, string16_s00df_47b0*& dst);  // 0x006a0bc0
uint32_t FNV1_String16(const wchar_t* s, uint32_t seed, bool lowercase);                         // 0x00932f30
struct Rect {
    float left, top, right, bottom;
    Rect(const Rect& r) : left(r.left), top(r.top), right(r.right), bottom(r.bottom) {}
};
struct IntRect { int left, top, right, bottom; };
struct IWindow_s00df_47b0 {
    PV2 PV
    virtual IWindow_s00df_47b0* FindWindowByID(uint32_t id);   // +0x0c
    PV8 PV2
    virtual const Rect& GetArea();                  // +0x38
    PV8 PV2
    virtual void SetLocation(float x, float y);     // +0x64
    PV4 PV
    virtual void SetFlag(int flag, bool value);     // +0x7c
    virtual void SetText(const wchar_t* text);      // +0x80
};
class cSPUILayout_s00df_47b0 { public:
    uint32_t pad[3];
    IWindow_s00df_47b0* FindWindowByID(uint32_t id, bool recursive);   // 0x008105b0
};
struct cAppWindow {
    void GetClientRect(IntRect* rect);   // 0x007c4010
};
struct cApp {
    PV16 PV4 PV2
    virtual cAppWindow* GetMainWindow();   // +0x58
};
cApp* App();   // 0x0067dd10
struct cAppSystem_s00df_47b0 {
    PV16 PV4 PV
    virtual bool IsFeatureEnabled();   // +0x54
};
cAppSystem_s00df_47b0* AppSystem_s00df_47b0();   // 0x0067dd00
struct cStarRecord_s00df_47b0 {
    uint32_t pad[0x16];
    uint32_t m58;
    uint32_t Get58();                  // 0x00989360 (returns m58)
    void Reset(int flags);             // 0x00bbaa80
};
struct cStarManager_s00df_47b0 {
    void SetActiveStar(cStarRecord_s00df_47b0* star);   // 0x00bb7510
};
cStarManager_s00df_47b0* StarManager_s00df_47b0();   // 0x00b3d2a0
struct cGameInfo_s00df_47b0 {
    uint32_t pad00[8];
    string16_s00df_47b0 mName;          // +0x20
    uint32_t pad30[7];
    ResourceKey_s00df_47b0 mKey4C;      // +0x4c
    uint32_t pad58[3];
    ResourceKey_s00df_47b0 mKey64;      // +0x64
    ResourceKey_s00df_47b0 mKey70;      // +0x70
    uint32_t mStarID;        // +0x7c
    uint32_t pad80[5];
    ResourceKey_s00df_47b0 mKey94;      // +0x94
    int mA0;                 // +0xa0
    int mA4;                 // +0xa4
    int mA8;                 // +0xa8
    uint32_t padac;
    int mB0;                 // +0xb0
    cStarRecord_s00df_47b0* GetStarRecord();   // 0x00de4610
};
const ResourceKey_s00df_47b0& GetKeyForID(uint32_t id);   // 0x00b6f0c0
struct cGGEGlobal_s00df_47b0 {
    uint8_t pad0[0x144];
    cSPUILayout_s00df_47b0 mLayout144;                // +0x144
    uint8_t pad150[0xa5];
    bool mbAllLevelsUnlocked;              // +0x1f5
    bool IsLevelUnlocked(uint32_t level);  // 0x00de5cb0
};
extern cGGEGlobal_s00df_47b0* gpGGEGlobal_s00df_47b0;   // 0x016a1344
struct Stopwatch_s00df_47b0 {
    uint64_t mnStartTime;      // +0x00
    uint64_t mnTotalElapsed;   // +0x08
    int mnUnits;               // +0x10 (1 = CPU cycles)
    float mfCyclesToUnits;     // +0x14
    uint64_t GetStopwatchCycle()
    {
        if (mnUnits == 1)
            return __rdtsc();
        int64_t t;
        QueryPerformanceCounter(&t);
        return (uint64_t)t;
    }
    void Restart()
    {
        mnStartTime = GetStopwatchCycle();
        mnTotalElapsed = 0;
    }
};
struct cGalaxyGameEntryUIStateMachine_s00df_47b0 {
    uint32_t pad00[0xa];
    cSPUILayout_s00df_47b0 mLayout;                       // +0x28
    uint32_t pad34[0xa];
    eastl::vector_s00df_47b0<uint32_t> mNewGameFlow;      // +0x5c
    uint32_t pad6c;
    bool mb70;                                 // +0x70
    uint8_t pad71[0x4a3];
    ResourceKey_s00df_47b0 mKey514;                       // +0x514
    uint32_t pad520[0x34];
    Stopwatch_s00df_47b0 mZoomTimer;                      // +0x5f0
    uint32_t pad608[8];
    cGameInfo_s00df_47b0* mpGameInfo;                     // +0x628

    void ResetGameUI();                                  // 0x00dec460
    void MakeRandomName();                               // 0x00defc80
    void SetupPanelA(uint32_t id);                       // 0x00df2920
    void SetupPanelB(uint32_t id);                       // 0x00df2770
    void SetCurrentState(int state);                     // 0x00df0670
    void RefreshUI();                                    // 0x00ded7d0
    void FillStarterWorldCombo(IWindow_s00df_47b0* combo);          // 0x00df1ba0
    void SelectStarterWorld(IWindow_s00df_47b0* combo, uint32_t v); // 0x00decf20
    void UpdateNavigationControls();                     // 0x00def8c0

    void SetupForGame(cGameInfo_s00df_47b0* gameInfo);

    void FUN_00df5330();
    void FUN_00df53d0(bool show);
    void FUN_00df5430(int mode);  // 0x00df5430 (cGalaxyGameEntryUIStateMachine::FUN_00df5430)
    long double FUN_00df54f0(float offset);  // 0x00df54f0 (cGalaxyGameEntryUIStateMachine::FUN_00df54f0)
    void FUN_00df5540();  // 0x00df5540 (cGalaxyGameEntryUIStateMachine::FUN_00df5540)
    void FUN_00df55b0(int mode);  // 0x00df55b0 (cGalaxyGameEntryUIStateMachine::FUN_00df55b0)
    void FUN_00df5610(float t);  // 0x00df5610 (cGalaxyGameEntryUIStateMachine::FUN_00df5610)
};
struct GalaxyLayoutState
{
    void SetLayout(const wchar_t* layout);      // 0x00dedda0
};
struct GalaxyStateBase
{
    void FUN_00dee360();                        // state reset
};
struct GalaxyView
{
    uint8_t       m_pad0[8];                    // +0x00
    GalaxyLayoutState* m_state8;                // +0x08
    cGameInfo_s00df_47b0*    m_game0c;                     // +0x0c
    uint8_t       m_pad10[0x20];                // +0x10
    void*         m_effect30;                   // +0x30
    float         m_x34;                        // +0x34
    float         m_y38;                        // +0x38
    float         m_z3c;                        // +0x3c
    float         m_w40;                        // +0x40
    uint8_t       m_pad44[8];                   // +0x44
    uint32_t      m_count4c;                    // +0x4c
    uint32_t      m_value50;                    // +0x50
    cSPUILayout_s00df_47b0   mLayout54;                    // +0x54
};
class cSPUIGlobalUI_s00df_47b0
{
public:
    void SetVisibility(bool visible);           // 0x00e01350
};
struct cGGEGlobalView
{
    uint8_t          m_pad0[0x184];             // +0x00
    cSPUIGlobalUI_s00df_47b0*   m_global184;               // +0x184
};
class cMessageServer_s00df_47b0
{
public:
    PV4 PV
    virtual void post(uint32_t message, uint32_t param, int flags);   // +0x14
};
cMessageServer_s00df_47b0* MessageServer_s00df_47b0();                // 0x0067dcc0
// ---- items of slice s00df47b0 end

// ---- items of slice s00df8730 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl sqrt(double);
extern float g_fLinkChance;                                // 0x015a41e0
extern float g_fNoticeTime;                                // 0x016a0ef8
extern char g_vtblGGEUIData[];                             // 0x0147eb60
extern void* g_pGameRolloverLayout;                        // 0x016a0d08
extern bool g_bGGEUIDataReady;                             // 0x016a0f88
#pragma intrinsic(sqrt)
struct Vector3_s00df_8730 {
    float x, y, z;
    Vector3_s00df_8730() {}
    Vector3_s00df_8730(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3_s00df_8730(const Vector3_s00df_8730& o) : x(o.x), y(o.y), z(o.z) {}
    Vector3_s00df_8730 operator-(const Vector3_s00df_8730& o) const { return Vector3_s00df_8730(x - o.x, y - o.y, z - o.z); }
    Vector3_s00df_8730 operator+(const Vector3_s00df_8730& o) const
    {
        Vector3_s00df_8730 r(*this);
        r.x += o.x;
        r.y += o.y;
        r.z += o.z;
        return r;
    }
    Vector3_s00df_8730 operator*(float s) const { return Vector3_s00df_8730(x * s, y * s, z * s); }
    float Length() const { return (float)sqrt(x * x + y * y + z * z); }
};
struct BoundingBox {
    Vector3_s00df_8730 lower;
    Vector3_s00df_8730 upper;
    BoundingBox(const Vector3_s00df_8730& lo, const Vector3_s00df_8730& hi) : lower(lo), upper(hi) {}
};
struct Matrix3_s00df_8730 {
    float m[3][3];
    Vector3_s00df_8730 operator*(const Vector3_s00df_8730& v) const
    {
        return Vector3_s00df_8730(v.z * m[2][0] + v.y * m[1][0] + v.x * m[0][0],
                       v.z * m[2][1] + v.y * m[1][1] + v.x * m[0][1],
                       v.z * m[2][2] + v.y * m[1][2] + v.x * m[0][2]);
    }
};
struct Transform {
    uint16_t mFlags;
    uint16_t mRefCount;
    Vector3_s00df_8730 mOffset;
    float mfScale;
    Matrix3_s00df_8730 mRotation;
    Transform();                                           // 0x00409930
    Transform(const Vector3_s00df_8730& offset, const Matrix3_s00df_8730& rot)
        : mFlags(4), mRefCount(1), mOffset(offset), mfScale(1.0f), mRotation(rot) {}
};
namespace SP {
    Vector3_s00df_8730 normalized_safe(const Vector3_s00df_8730& v);            // 0x00449c20
}
namespace SP {
    struct cSporeGuide { uint32_t pad[7]; bool mbActive; };  // +0x1c
}
namespace SP {
    cSporeGuide* SporeGuide_s00df_8730();                             // 0x00401040
}
Vector3_s00df_8730 RandomPointInBox(const BoundingBox& box);          // 0x00df5f50
void GetScaledMouse(float* x, float* y);                   // 0x00804ed0
struct RandomLinearCongruential {
    uint32_t RandomUint32Uniform(uint32_t nLimit);         // 0x00a68fb0
    double RandomDoubleUniform();                          // 0x009360d0
    double RandomDoubleUniform(double limit)
    {
        double r = RandomDoubleUniform() * limit;
        if (r >= limit)
            return limit;
        if (r < 0.0)
            return 0.0;
        return r;
    }
};
extern RandomLinearCongruential g_SPRandom;                // 0x01601760
struct Stopwatch_s00df_8730 {
    uint64_t mnStartTime;
    uint64_t mnTotalElapsedTime;
    int mnUnits;
    float mfStopwatchCyclesToUnitsCoefficient;
    void Stop();                                           // 0x0093a2e0
    uint64_t GetElapsedTime() const;                       // 0x0093a3a0
    bool IsRunning() const { return mnStartTime != 0; }
    void Reset() { mnStartTime = 0; mnTotalElapsedTime = 0; }
    float GetElapsedTimeFloat() const
    {
        return (float)(int64_t)GetElapsedTime() * mfStopwatchCyclesToUnitsCoefficient;
    }
};
struct LimitStopwatch : Stopwatch_s00df_8730 {
    uint64_t mnEndTime;
    void SetTimeLimit(uint32_t nLimit, bool bStartImmediately);   // 0x0093a480
    bool IsTimeUp() const
    {
        uint64_t t;
        QueryPerformanceCounter(&t);
        return (int64_t)(mnEndTime - t) < 0;
    }
};
struct cIVisualEffect_s00df_8730 {
    virtual int AddRef();
    virtual int Release();
    virtual bool Start(int flags);                 // 0x08
    virtual bool Stop(int flags);                  // 0x0c
    virtual bool IsRunning();                      // 0x10
    virtual void v14();
    virtual void SetTransform(const Transform& t); // 0x18
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2c();
    virtual void SetVisible(bool b);               // 0x30
};
template<class T> struct AutoRefCount_s00df_8730 {
    T* mpObject;
    AutoRefCount_s00df_8730() : mpObject(0) {}
    AutoRefCount_s00df_8730(const AutoRefCount_s00df_8730& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount_s00df_8730() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
typedef AutoRefCount_s00df_8730<cIVisualEffect_s00df_8730> EffectRef;
struct cIEffectsWorld_s00df_8730 {
    virtual void v00();
    virtual void v04();
    virtual bool CreateVisualEffect(uint32_t instanceId, int flags, EffectRef& out);   // 0x08
};
EffectRef* copy(EffectRef* first, EffectRef* last, EffectRef* result);   // 0x0042f530
template<class T> struct sp_vector_s00df_8730 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    void* mAllocator;
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T& operator[](uint32_t n) { return mpBegin[n]; }
    T& back() { return *(mpEnd - 1); }
    bool empty() const { return mpBegin == mpEnd; }
    void DoInsertValue(T* position, const T& value);
    void DestroyRange(T* first, T* last);                  // 0x00de5ee0
    void Resize(int n);                                    // 0x00de9e20
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new(mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
    T* erase(T* first, T* last)
    {
        memmove(first, last, (unsigned int)((char*)mpEnd - (char*)last));
        mpEnd -= (last - first);
        return first;
    }
    T* erase(T* position)
    {
        if ((position + 1) < mpEnd)
            copy(position + 1, mpEnd, position);
        --mpEnd;
        mpEnd->~T();
        return position;
    }
    void clear() { erase(mpBegin, mpEnd); }
};
struct IWindow_s00df_8730 {
virtual void v00();
virtual void v04();
virtual void v08();
    virtual void* v0c(uint32_t id);                        // 0x0c
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
    virtual void SetVisible(bool b);                       // 0x30
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
    virtual void SetFlag(int flag, bool value);            // 0x7c
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
    virtual void SetSomething(int a, int b);               // 0xb8
};
class cSPUILayout_s00df_8730 { public:
    IWindow_s00df_8730* FindWindowByID(uint32_t id, bool recursive);  // 0x008105b0
    void Shutdown(uint32_t flags);                         // 0x00811ad0
    uint32_t pad[3];
};
class cSPUIGlobalUI_s00df_8730 { public:
    void SetVisibility(bool visible);                      // 0x00e01350
};
struct cGameUIData_s00df_8730 {
    uint32_t pad[8];
    struct Anim { void Update(uint32_t ms); } mAnim;  // 0x00e21040 (member at +0x20)
    uint32_t pad2[4];
    IWindow_s00df_8730* mpWindow;                                     // +0x34
};
struct cGameInfo_s00df_8730 {                                         // size 0xbc (retail)
    uint32_t pad[0x20];
    Vector3_s00df_8730 mStarLocationAbsolute;                         // +0x80
    int mField8c;                                          // +0x8c
    uint32_t pad90[6];
    int mType;                                             // +0xa8
    bool mbSaved;                                          // +0xac
    bool mbVisibleInGalaxy;                                // +0xad
    uint16_t pad_ae;                                       // +0xae
    uint32_t mFieldb0;                                     // +0xb0
    uint32_t mFieldb4;                                     // +0xb4
    cGameUIData_s00df_8730* mpUIData;                                 // +0xb8
    cGameInfo_s00df_8730& operator=(const cGameInfo_s00df_8730& other);   // 0x00b26fb0
};
inline cGameInfo_s00df_8730* CopyGameInfos(cGameInfo_s00df_8730* first, cGameInfo_s00df_8730* last,
                                           cGameInfo_s00df_8730* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
struct cGGECamera {
    void GetTransform(Transform& t);                       // 0x00dde590
    Transform GetTransform() { Transform t; GetTransform(t); return t; }
    void SetMouseActive(bool b);                           // 0x00dde5b0
};
struct cGalaxyGameEntryUI {                                // global at 0x016a1344
    uint32_t m04;                                          // +0x04 (passed to FUN_00df76c0)
    uint32_t pad0[0x3d];
    int mf8;                                               // +0xf8
    int mfc;                                               // +0xfc
    uint32_t pad1[0x11];
    cSPUILayout_s00df_8730 mLayout;                                   // +0x144
    uint32_t pad2[3];
    cIEffectsWorld_s00df_8730* mpEffectsWorld;                        // +0x15c
    uint32_t pad3[9];
    cSPUIGlobalUI_s00df_8730* mpGlobalUI;                             // +0x184
    uint32_t pad4[4];
    cGGECamera* mpCamera;                                  // +0x198
    uint32_t pad5[0xf];
    sp_vector_s00df_8730<IWindow_s00df_8730*> mWindows;                          // +0x1d8
    uint32_t pad6[2];
    bool mb1f0;                                            // +0x1f0
    char pad7[0x80];
    bool mb271;                                            // +0x271
    void Refresh();                                        // 0x00de5260
    void ShowPanel(int which);                             // 0x00de53d0
};
extern cGalaxyGameEntryUI* g_pGalaxyGameEntryUI;           // 0x016a1344
struct cGalaxyStarLinks {
    uint32_t GetLinkCount(int kind);                       // 0x00dda060
    uint32_t GetPulseCount();                              // 0x00dda380
    void AddLongLink(Vector3_s00df_8730* a, Vector3_s00df_8730* b);              // 0x00ddcad0
    void AddLink(Vector3_s00df_8730* a, Vector3_s00df_8730* b, bool c, bool d);  // 0x00ddc910
    void AddPulse();                                       // 0x00ddcdc0
};
cGalaxyStarLinks* GalaxyStarLinks();                       // 0x00dd9190
extern Matrix3_s00df_8730 g_galaxyRotation;                           // 0x016a1674
extern Vector3_s00df_8730 g_galaxyOffset;                             // 0x016a1698
class cGalaxyGameEntryScreen_s00df_8730 {
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
    virtual void v10();
    virtual void Update(float dt);                         // 0x14 0x00df29d0
virtual void v18();
virtual void v1c();
    virtual void OnMouseMove(float x, float y, int flags); // 0x20
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
    virtual void UpdateRollover();                         // 0x68

    void ClearGames();                                     // 0x00df9510
    void BuildGames();                                     // 0x00df9230
    void ResetGames();                                     // 0x00df95d0
    void LoadGameRange(cGameInfo_s00df_8730* first, int count);        // 0x00df7ce0
    void LoadSavedGames(cGameInfo_s00df_8730* first, int count);       // 0x00df7f60
    void SetupRolloverStarEffects();                        // 0x00df8330

    sp_vector_s00df_8730<cGameInfo_s00df_8730> mGames;                           // +0x08
    uint32_t pad18[2];
    Stopwatch_s00df_8730 mNoticeTimer;                                // +0x20
    Stopwatch_s00df_8730 mHintTimer;                                  // +0x38
    bool mbWaitForGuide;                                   // +0x50
    sp_vector_s00df_8730<uint32_t> mCandidates;                       // +0x54
    uint32_t pad64;
    int mHighlightIndex;                                   // +0x68
    uint32_t pad6c;
    LimitStopwatch mHighlightTimer;                        // +0x70
    sp_vector_s00df_8730<EffectRef> mHighlightEffects;                // +0x90
};
inline void UpdateMouse(cGalaxyGameEntryScreen_s00df_8730* self)
{
    float x, y;
    GetScaledMouse(&x, &y);
    self->OnMouseMove(x, y, 0);
}
struct cBaseCtor { void Construct(); };                    // 0x00810000
void* operator new(unsigned int size, const char* name, int a, int b, int c, int d);  // 0x00f473a0
void GameFree(void* p);                                    // 0x00f47380
namespace SP {
struct cString_s00df_8730 {
    uint32_t mData[5];                                          // 0x14 bytes (retail)
    cString_s00df_8730(uint32_t id, uint32_t name, const wchar_t* text);   // 0x006b5770
    ~cString_s00df_8730();                                                 // 0x006b5240
    const void* GetText(int start, ...);                        // 0x006b55c0
};
}
void SetTooltipText(IWindow_s00df_8730* window, const void* text);     // 0x00806de0
struct cGGEWindowSub {
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
    virtual void s10();
    virtual void SetValue(int value);                      // +0x14
};
struct cGGEWindowEx {
    uint32_t pad[0x83];                                    // 0x000 .. 0x20b
    cGGEWindowSub mSub;                                    // +0x20c
};
struct cGameUIDataBlock;
struct cGGEGameUIDataChild {
    virtual void v00();
    virtual void v04();                                    // destroy
    virtual void v08(int value);
    virtual void v0c(int value);
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
    virtual void Setup(int kind, cGameInfo_s00df_8730** ppOwner, int flags);   // +0x48
};
struct cGameUIDataBlock {                                  // 0x90 (retail)
    uint32_t pad00[6];                                     // +0x00
    void* mpVtbl2;                                         // +0x18
    int m1c;                                               // +0x1c
    uint32_t m20;                                          // +0x20
    uint32_t m24;                                          // +0x24
    uint32_t m28;                                          // +0x28
    uint32_t m2c;                                          // +0x2c
    cGameInfo_s00df_8730* mpGameInfo;                                 // +0x30
    cGGEGameUIDataChild* mpChild;                          // +0x34
    uint16_t* mpVecBegin;                                  // +0x38
    uint16_t* mpVecEnd;                                    // +0x3c
    uint16_t* mpVecCapacity;                               // +0x40
    void* mpVecAllocator;                                  // +0x44
    uint16_t* mpInlineBegin;                               // +0x48
    uint16_t mInline[0x20];                                // +0x4c
    uint32_t m8c;                                          // +0x8c

    cGameUIDataBlock(cGameInfo_s00df_8730* info)
    {
        ((cBaseCtor*)this)->Construct();
        mpVtbl2 = g_vtblGGEUIData;
        m20 = 0;
        m24 = 0;
        m28 = 0;
        m2c = 0;
        mpGameInfo = info;
        mpChild = 0;
        mpInlineBegin = mInline;
        mpVecCapacity = mpInlineBegin + 0x20;
        mpVecEnd = mInline;
        mpVecBegin = mInline;
        mInline[0] = 0;
        m8c = 0;
        m1c = (int)info;
    }
};
struct cGameUIDataBlockOps {
    void InitRollover(void* layout, void* owner);          // 0x00df76c0
    void Destroy();                                        // 0x00df82d0
};
struct cStarManagerList {
    int* mpBegin;
    int* mpEnd;
    int* mpCapacity;
    int size() const { return (int)(mpEnd - mpBegin); }
};
struct cStarManager_s00df_8730 {
    uint32_t pad[0x3c];
    cStarManagerList mList;                                // +0xf0
    cStarManagerList* QueryList();                         // 0x00ba6300
};
cStarManager_s00df_8730* StarManager_s00df_8730();                               // 0x00b3d2a0
// ---- items of slice s00df8730 end

// ---- items of slice s00dfa5c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_panels;        // 0x016a1344
extern void* g_editor;        // 0x016c7aa4
extern float g_one;           // 0x013ec468 (wstring empty)
extern int  g_arr15a4318[];      // 0x015a4318 (32 panel ids)
extern int  g_15da7c4;           // 0x015da7c4
extern int  g_15da7c8;           // 0x015da7c8
extern int  g_15da7cc;           // 0x015da7cc
extern int  g_15da7d0;           // 0x015da7d0
extern char g_d1654c10[];        // 0x01654c10
extern void* g_appPrefs;         // 0x015fd91c
extern char vtbl_147dc04, vtbl_149bad8, vtbl_13ec458, LAB_ad0e52;
void  WString_Assign(void* a, void* b);     // 0x00423650
void* operator_new(unsigned int n, const char* cat, int a, int b, const char* file, int line); // 0x00f473a0
void  FUN_00dfa3c0(void* a, void* b, void* c, void* d, int e); // 0x00dfa3c0
struct Swarm;
void   __fastcall FUN_00ddb760(Swarm* a);   // 0x00ddb760
void* GetSaveArea_s00df_a5c0(int a, int b);            // 0x006b1f90
void  SaveResource(void* a, void* b);       // 0x006b1d50
void  SetTooltipText(void* w, void* txt, int a, int b); // 0x00806de0
void* AssetBrowser_s00df_a5c0();                        // 0x00401030
struct AssetBrowserT { void Update(); };     // 0x0064ab20 thiscall
void  KillSetiEffects2(void* a, int b);     // 0x00435ed0
void* GetSystemAT_s00df_a5c0();                         // 0x00a206f0
void* FUN_004010a0();                        // 0x004010a0
struct UI_s00df_a5c0 {
    // vtable helpers via raw casts
    void FUN_a710(char on);      // 0xdfa710
    void FUN_a790(char on);      // 0xdfa790
    void FUN_a5c0(int a);        // 0xdfa5c0
    void FUN_a810();             // 0xdfa810
    void FUN_a930();             // 0xdfa930
    void FUN_ab20(bool enable);  // 0xdfab20
    void FUN_9990();             // 0xdf9990
    void FUN_9a00();             // 0xdf9a00
    void FUN_9a70();             // 0xdf9a70
    void FUN_a370();             // 0xdfa370
    void FUN_a460(void* a, int b); // 0xdfa460
    void FUN_aca0(int* pos);     // 0xdfaca0
    void FUN_ad50(int* pos);     // 0xdfad50
    UI_s00df_a5c0*  FUN_ae00(void* other);  // 0xdfae00
    void FUN_ae50();             // 0xdfae50
    void FUN_ae90();             // 0xdfae90
    void FUN_af80();             // 0xdfaf80
    void FUN_b040(int key, int arg2); // 0xdfb040
    void FUN_b0d0(char unused);  // 0xdfb0d0
    void FUN_b430(int a);        // 0xdfb430
    void FUN_b450();             // 0xdfb450
    void FUN_b470(int a);        // 0xdfb470
    void FUN_97e0();             // 0x00df97e0 (this file's callee)
    void FUN_9ad0();             // 0x00df9ad0
    void FUN_9be0();             // 0x00df9be0
};
struct Obj_s00df_a5c0 {
    void  M_de53d0(int a);                          // 0x00de53d0
    void  M_de5470(int a);                          // 0x00de5470
    void  M_de5330(int a);                          // 0x00de5330
    void  M_de86d0(int a, int b);                   // 0x00de86d0
    void  M_de0890();                               // 0x00de0890
    void  M_de07a0(float f);                        // 0x00de07a0
    void  M_e01350(int v);                          // 0x00e01350
    unsigned char M_ec4320();                       // 0x00ec4320
    unsigned char M_ec5a60(int* pos, int a, int b); // 0x00ec5a60
    void* M_8105b0(int id, int flag);               // 0x008105b0
    unsigned char M_810590(int v);                  // 0x00810590
    void  M_e3e350(int a, void* b, int c);          // 0x00e3e350
    void  M_93db80(int a);                          // 0x0093db80
    void  M_422e20(void* p);                        // 0x00422e20
    char* M_41e920();                               // 0x0041e920
    void  M_6b5770(int a, int b, int c);            // 0x006b5770
    void  M_6b5240();                               // 0x006b5240
    wchar_t* M_6b55c0();                            // 0x006b55c0
    void* M_5ecf80(void* out, int key);             // 0x005ecf80
    void* M_644b10();                               // 0x00644b10
    void  M_644b60();                               // 0x00644b60
};
struct Eff9 { int f[9]; };                          // 0x15accc8 singleton
void* __cdecl F_ef19f0(void);        // 0x00ef19f0
void* __cdecl F_b3d410(void);        // 0x00b3d410
void  __cdecl F_6447c0(int a, void** out); // 0x006447c0
void  __cdecl F_64a990(void* p);     // 0x0064a990
void* __cdecl GetSaveArea_s00df_a5c0(unsigned int a); // 0x006b1f90
void  __cdecl SaveResource(void* a, unsigned int b, char c); // 0x006b1d50
struct Vec44_s00df_a5c0 {
    unsigned int b, e;
    void Dtor();
};
struct CStr_s00df_a5c0 {
    void Assign(void* o);   // 0x006b5430 thiscall ret 4
};
struct WStrAssign {
    void assign(void* b, void* e);   // 0x00423650 thiscall ret 8
};
struct cSPUILayoutX {
    void* FindWindowByID(unsigned int id, char flag);   // 0x8105b0
    unsigned char SetVisibility(char v);                // 0x810590
};
struct cSPUIGlobalUIX {
    void SetVisibility(int v);                          // 0xe01350
};
struct WStrX {
    void* mpBegin;      // +0x00
    void* mpEnd;        // +0x04
    void* mpCapacity;   // +0x08
    void* mAlloc;       // +0x0c
    void assign(const void* b, const void* e);          // 0x423650
};
struct cStringX {
    int f[5];                                           // 0x14 bytes
    void  Ctor(unsigned int a, unsigned int b, const wchar_t* c); // 0x6b5770
    void  Dtor();                                       // 0x6b5240
    const void* GetText();                              // 0x6b55c0
};
struct VariantX {
    int f[4];                    // +0x00..0x0f
    unsigned short mFlags;       // +0x10
    unsigned short mTypeId;      // +0x12
    void SetBool(const bool* b); // 0x422e20
};
struct LaunchInfo {
    unsigned int type;          // +0x00
    void* self;                 // +0x04
    unsigned int pad8;          // +0x08
    void* obj;                  // +0x0c
    unsigned char f10, f11, f12, f13, f14;  // +0x10..0x14
    unsigned char p15, p16, p17;
    int v18, v1c, v20;          // +0x18,0x1c,0x20
    unsigned char b24;          // +0x24
    unsigned char p25, p26, p27;
    unsigned int f28;           // +0x28
    unsigned char b2c;          // +0x2c
    unsigned char p2d, p2e, p2f;
    void* fn;                   // +0x30
    unsigned int f34;           // +0x34
    void* f38;                  // +0x38
    unsigned int f3c;           // +0x3c
    void* sp40;                 // +0x40
    void* sp44;                 // +0x44
};
struct LaunchInfoOps { void Ctor(); void Dtor(); };
struct RefCountBase { void* vtbl; unsigned int count; };
static __forceinline void PtrAssign(void*& slot, void* p)
{
    if (p != slot) {
        void* old = slot;
        if (p) ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
        slot = p;
        if (old) ((void(__thiscall*)(void*))(*(void***)old)[2])(old);
    }
}
struct V3 { int x, y, z; };
struct EltStr {                 // eastl::basic_string<wchar_t> (12 bytes)
    wchar_t* mpBegin;           // +0x00
    wchar_t* mpEnd;             // +0x04
    wchar_t* mpCapacity;        // +0x08
    void AllocateSelf(int n);   // 0x429760
    void assign(void* b, void* e); // 0x423650
};
struct CStrData {               // SP::cString (0x14 bytes)
    int f[5];
    void Assign(const void* src);    // 0x6b5430
    void CStrCtor(const void* src);  // 0x6b56f0
};
struct TypeA_s00df_a5c0 {                  // 0x24-byte collection element
    int  f0;                    // +0x00
    int  f4;                    // +0x04
    int  f8;                    // +0x08
    unsigned char fC;           // +0x0c
    EltStr s;                   // +0x10
    int  pad1C;                 // +0x1c (not copied)
    int  f20;                   // +0x20
    TypeA_s00df_a5c0* CopyCtor(const TypeA_s00df_a5c0* o);
};
struct TypeC_s00df_a5c0 {                  // 0x38-byte collection element
    CStrData cs;                // +0x00
    EltStr s1;                  // +0x14
    int  pad20;                 // +0x20 (not copied)
    int  f24;                   // +0x24
    int  f28;                   // +0x28
    EltStr s2;                  // +0x2c
    TypeC_s00df_a5c0* CopyCtor(const TypeC_s00df_a5c0* o);
};
struct TypeD_s00df_a5c0 {                  // 0x44-byte collection element
    int   f0;                   // +0x00
    TypeC_s00df_a5c0 c;                    // +0x04
    int   pad3c;                // +0x3c (not copied)
    int   f40;                  // +0x40
    TypeD_s00df_a5c0& Assign(const TypeD_s00df_a5c0& o);
};
// ---- items of slice s00dfa5c0 end

// forward declarations: helpers defined later in VA order (rewrite.py forward_protos)
EaString16* __cdecl FUN_00de3fa0(EaString16* out, u32 sel);   // defined at 0x00de3fa0, called earlier in the TU

// forward declarations: helpers defined later in VA order (rewrite.py forward_protos)
EaString16* __cdecl FUN_00de40e0(EaString16* out, void* tm);   // defined at 0x00de40e0, called earlier in the TU

// forward declarations: helpers defined later in VA order (rewrite.py forward_protos)
TypeD* CopyAssignD(TypeD* first, TypeD* last, TypeD* dest);   // defined at 0x00dfb930, called earlier in the TU

// @ 0x00677e80
int RectF::Contains(float x, float y)
{
    return x >= mLeft && y >= mTop && x < mRight && y < mBottom;
}

// @ 0x00ddd970
void FUN_00ddd970()
{
    void* mem = G7New(0x74, gSimulatorName, 0, 0, 0, 0);
    cModelSetup* s;
    if (mem)
        s = (cModelSetup*)FUN_00dda920(mem);
    else
        s = 0;
    gSimulator = s;
    s->Setup();
}

// @ 0x00ddd9b0
char __fastcall FUN_00ddd9b0(void* self)
{
    ((void (__thiscall*)(void*, int, float, float, int))VFn(self, 0x2c))(self, 0x3ea, 0.0f, 0.0f, 0);
    ((void (__thiscall*)(void*, int, float, float, int))VFn(self, 0x30))(self, 0x3ea, 0.0f, 0.0f, 0);
    ((PanelOps*)kGUI_PanelIDs_s00dd_cdc0)->Ma200();
    cISPObjectTemplateDB_s00dd_cdc0* db = ObjectTemplateDB_s00dd_cdc0();
    if (db)
        ((void (__thiscall*)(void*))VFn(db, 0x54))(db);
    LayoutOps* lm = (LayoutOps*)GetLayoutManager();
    if (lm->Is(0x614de4c))
        lm->M660(0x614de4c, 0);
    return 1;
}

// @ 0x00ddda30
int __fastcall FUN_00ddda30(void* self)
{
    ((void (__thiscall*)(void*, int, float, float, int))VFn(self, 0x2c))(self, 0x3ea, 0.0f, 0.0f, 0);
    ((void (__thiscall*)(void*, int, float, float, int))VFn(self, 0x30))(self, 0x3ea, 0.0f, 0.0f, 0);
    return ((PanelOps*)kGUI_PanelIDs_s00dd_cdc0)->M81b0();
}

// @ 0x00dddaa0
char __stdcall FUN_00dddaa0(int a1, float a2, float a3, int a4)
{
    ((PanelOps*)kGUI_PanelIDs_s00dd_cdc0)->M4450(a1, a2, a3, a4);
    if (kGUI_PanelIDs_s00dd_cdc0->mState == 4)
        return 1;
    if (a1 == 0x3ea) {
        void* wm = WindowManager();
        ((void (__thiscall*)(void*, int, int))VFn(wm, 0x58))(wm, 1, 0);
        kGUI_PanelIDs_s00dd_cdc0->mFlag17c = 0;
    }
    return 0;
}

// @ 0x00dddb10
char __stdcall FUN_00dddb10(int a1, float a2, float a3, int a4)
{
    if (kGUI_PanelIDs_s00dd_cdc0 != 0)
        ((PanelOps*)kGUI_PanelIDs_s00dd_cdc0)->M44a0(a1, a2, a3, a4);
    if (kGUI_PanelIDs_s00dd_cdc0->mState == 4)
        return 1;
    if (a1 == 0x3ea) {
        void* wm1 = WindowManager();
        void* wm2 = WindowManager();
        int r = ((int (__thiscall*)(void*))VFn(wm1, 4))(wm1);
        ((void (__thiscall*)(void*, int, int))VFn(wm2, 0x58))(wm2, 1, r);
        kGUI_PanelIDs_s00dd_cdc0->mFlag17c = 1;
    }
    return 0;
}

// @ 0x00dddba0
void __stdcall FUN_00dddba0(float a1, float a2, int a3)
{
    ((PanelOps*)kGUI_PanelIDs_s00dd_cdc0)->M44f0(a1, a2, a3);
}

// @ 0x00dddbd0
void __stdcall FUN_00dddbd0(float a1, float a2)
{
    int t = (int)(float)(a2 * 1000.0f);
    ((PanelOps*)kGUI_PanelIDs_s00dd_cdc0)->M8760(a1, a2);
    FUN_00b5e9a0(FUN_00b3d230(t));
}

// @ 0x00dddc30
char __fastcall FUN_00dddc30(cGUIHandler* self)
{
    void* mem = G7New(0x2080, gPatchMgrName, 0, 0, 0, 0);
    void* np;
    if (mem)
        np = FUN_00e20780(mem);
    else
        np = 0;
    void* old = self->mp0c;
    if (np != old) {
        if (np)
            ((int (__thiscall*)(void*))VFn(np, 4))(np);
        self->mp0c = np;
        if (old)
            ((void (__thiscall*)(void*))VFn(old, 8))(old);
    }
    FUN_00c2e4e0(self->mp0c);
    return 1;
}

// @ 0x00dddca0
char __fastcall FUN_00dddca0(cGUIHandler* self)
{
    void* m = FUN_006895b0();
    ((void (__thiscall*)(void*, int))VFn(m, 0x28))(m, 0x4530082);
    ((PanelOps*)kGUI_PanelIDs_s00dd_cdc0)->M7eb0();
    if (kGUI_PanelIDs_s00dd_cdc0) {
        void* sub = (char*)kGUI_PanelIDs_s00dd_cdc0 + 4;
        ((void (__thiscall*)(void*, int))VFn(sub, 8))(sub, 1);
    }
    FUN_00e20800(self->mp0c);
    if (self->mp0c) {
        void* o = self->mp0c;
        self->mp0c = 0;
        ((void (__thiscall*)(void*))VFn(o, 8))(o);
    }
    void* cm = FUN_0067de20();
    if (cm) {
        ((void (__thiscall*)(void*, void*))VFn(cm, 0x1c))(cm, &gCheatArg);
        gFlag0c80 = 0;
    }
    return 1;
}

// @ 0x00de0670
void cInterfaceState::BeginSequence(uint8_t bFirst, uint8_t bSecond)
{
    if (bSecond != 0) {
        gInterfaceTimer = (uint32_t)RoundToInt((gInterfaceStep + gInterfaceStep) * 1000.0f);
        return;
    }

    gInterfaceTargetX = gInterfaceTargetY;
    gInterfaceTargetY = gInterfaceTargetY;
    gInterfaceTargetZ = gInterfaceTargetY;
    gInterfaceFrom.mfX = gInterfaceTargetX;
    gInterfaceFrom.mfY = gInterfaceTargetX;
    gInterfaceFrom.mfZ = (bFirst != 0) ? 1.0f : 2.0f;
    gInterfaceValue = gInterfaceTargetZ;
    gInterfaceTimer = 0;
    gInterfaceSpeed = gInterfaceStep;

    PostInterfaceMessage(0x7c3cd3d, (bFirst != 0) ? 1.0f : 2.0f);
    gInterfaceStarted = 0;
}

// @ 0x00de07a0
void cInterfaceState::ResetSequence()
{
    gInterfaceAlpha = 0.0f;
    gInterfaceStep = 0.0f;
    gInterfaceValue = gInterfaceTargetY;
    gInterfaceBlend = gInterfaceTargetY;
    if (gInterfaceTargetY < gInterfaceAlpha || gInterfaceTargetX + gInterfaceAlpha < gInterfaceTargetY)
        gInterfaceAngle = gInterfaceTargetX;
    else
        gInterfaceAngle = 0.0f;
    gInterfaceTargetZ = gInterfaceTargetX;
    gInterfaceFrom.mfX = gInterfaceTargetX;
    gInterfaceSpeed = 0.0f;
    gInterfaceFrom.mfZ = gInterfaceTargetZ;
    gInterfaceStarted = 0;

    PostInterfaceMessage(0x7be7df5, 0);
}

// @ 0x00de0890
void cInterfaceState::NotifySequence()
{
    gInterfaceSpeed = 2.0f;
    gInterfaceStep = 0.0f;
    PostInterfaceMessage(0x7be7df5, 3);
}

// @ 0x00de0900
bool cInterfaceState::IsIdle()
{
    return *(uint8_t*)((uint8_t*)&mnTimer) == 0;
}

// @ 0x00de0ae0
void __thiscall cGalaxyGameEntryImpl::FUN_00de0ae0(uint32_t arg)
{
    void* pAudio = FUN_00a206f0();
    uint32_t v = 0;
    if (pAudio != 0)
        v = ((uint32_t(__thiscall*)(void*))VFN(pAudio, 0x20))(pAudio);

    pAudio = FUN_00a206f0();
    if (pAudio != 0) {
        ((void(__thiscall*)(void*, uint32_t))VFN(pAudio, 0x38))(pAudio, 0x3475365);
        ((void(__thiscall*)(void*, uint32_t, uint32_t))VFN(pAudio, 0x40))(pAudio, 0x3475381, 0x41a43586);
        ((void(__thiscall*)(void*, uint32_t, uint32_t))VFN(pAudio, 0x40))(pAudio, 0x3475385, v);
        ((void(__thiscall*)(void*))VFN(pAudio, 0x58))(pAudio);
    }

    void* pObj = FUN_00df5f40();
    ((void(__thiscall*)(void*, int, int))VFN(pObj, 0x60))(pObj, 0, 1);

    m38 = arg;
    ma8 = mac;

    uint32_t nHi;
    if (mc8 == 1) {
        unsigned long long nTsc = __rdtsc();
        mb8 = (uint32_t)nTsc;
        nHi = (uint32_t)(nTsc >> 32);
    } else {
        LARGE_INTEGER li;
        QueryPerformanceCounter(&li);
        mb8 = li.u.LowPart;
        nHi = li.u.HighPart;
    }
    mc4 = 0;
    mc0 = 0;
    mbc = nHi;
}

// @ 0x00de0bc0
void __thiscall cGalaxyGameEntryImpl::FUN_00de0bc0(uint32_t param_2, uint32_t param_3, uint32_t param_4)
{
    if (param_2 == md4) {
        m38 = 0x156276d1;
    } else if (param_2 == md8) {
        m38 = 0x9adf00a9;
    } else if (param_2 == mdc) {
        m38 = 0x37e82da1;
    } else {
        if (param_2 != me0)
            return;
        m38 = 0xa56567f7;
    }
    m3c = param_2;

    cEditorLaunchData* pEd1;
    {
        void* pRaw = FUN_00f473a0(0x9c, k_szSporepedia, 0, 0, 0, 0);
        if (pRaw == 0)
            pEd1 = 0;
        else
            pEd1 = (cEditorLaunchData*)((tHost*)pRaw)->FUN_005a9080();
    }
    pEd1->m0c = m38;
    pEd1->m90 = 0;
    {
        void* pCVS;
        void* pRaw = FUN_00f473a0(0x14, k_szSporepedia, 0, 0, 0, 0);
        if (pRaw == 0)
            pCVS = 0;
        else
            pCVS = ((cContentValidationSummarizer*)pRaw)->FUN_00de0a90(this, 1);
        AssignRef(&pEd1->m94, pCVS, 0, 4);
    }
    pEd1->m24 = DAT_015da784;
    pEd1->m28 = DAT_015da788;
    pEd1->m2c = DAT_015da78c;
    pEd1->m30 = DAT_015da790;
    pEd1->m34 = 0;
    pEd1->m36 = 1;
    pEd1->m37 = 1;
    pEd1->m38 = 1;
    pEd1->m3a = 1;
    pEd1->m3d = 0;
    pEd1->m3c = 1;
    pEd1->m64 = 1;
    pEd1->m6d = 0;
    pEd1->m6e = 0;
    pEd1->m6f = 1;
    pEd1->m6c = 1;

    cEditorLaunchData* pEd2;
    {
        void* pRaw = FUN_00f473a0(0x9c, k_szSporepedia, 0, 0, 0, 0);
        if (pRaw == 0)
            pEd2 = 0;
        else
            pEd2 = (cEditorLaunchData*)((tHost*)pRaw)->FUN_005a9080();
    }
    pEd2->m0c = 0x465c50ba;
    pEd2->m90 = 0;
    {
        void* pCVS;
        void* pRaw = FUN_00f473a0(0x14, k_szSporepedia, 0, 0, 0, 0);
        if (pRaw == 0)
            pCVS = 0;
        else
            pCVS = ((cContentValidationSummarizer*)pRaw)->FUN_00de0a90(this, 1);
        AssignRef(&pEd2->m94, pCVS, 0, 4);
    }
    pEd2->m24 = DAT_015da784;
    pEd2->m28 = DAT_015da788;
    pEd2->m2c = DAT_015da78c;
    pEd2->m30 = DAT_015da790;
    pEd2->m34 = 0;
    pEd2->m36 = 1;
    pEd2->m37 = 1;
    pEd2->m38 = 1;
    pEd2->m3a = 1;
    pEd2->m3d = 0;
    pEd2->m3c = 0;
    pEd2->m64 = 1;
    pEd2->m6d = 0;
    pEd2->m6e = 0;
    pEd2->m6f = 1;

    AssignRef(&pEd2->m98, pEd1, 4, 8);

    void* pCVS4;
    {
        void* pRaw = FUN_00f473a0(0x14, k_szSporepedia, 0, 0, 0, 0);
        if (pRaw == 0)
            pCVS4 = 0;
        else
            pCVS4 = ((cContentValidationSummarizer*)pRaw)->FUN_00de0a90(this, 1);
    }

    FUN_00de5d00(param_2, kGUI_PanelIDs, 0, param_3, param_4, pCVS4, pEd2);
}

// @ 0x00de1710
extern "C" void __fastcall FUN_00de1710(int param_1)
{
    int* piVar4;
    int* piVar1;
    int* piVar6;
    unsigned uVar5;
    LI LStack_8;

    *(int*)(param_1 + 0x38) = 0;
    ((SG*)*(void**)((char*)kGUI_PanelIDs_s00de_1710 + 0x198))->FUN_00de0670(1, 0);
    ((SG*)kGUI_PanelIDs_s00de_1710)->FUN_00de5330(0);
    ((SG*)kGUI_PanelIDs_s00de_1710)->FUN_00de5260();
    piVar4 = SP_MovieSystem();
    if (piVar4 != 0) {
        ((void(__thiscall*)(void*, int))((void**)(*(int**)piVar4))[0x40 / 4])(piVar4, 1);
    }
    ((SG*)kGUI_PanelIDs_s00de_1710)->FUN_00de5300();
    *(int*)(param_1 + 0xa8) = 0;
    *(char*)(param_1 + 0x21) = 0;
    *(char*)(param_1 + 0xd0) = 0;
    piVar4 = ((Layout_s00de_1710*)((char*)kGUI_PanelIDs_s00de_1710 + 0x144))->FindWindowByID(0x615a5ff, 1);
    if (piVar4 != 0) {
        ((void(__thiscall*)(void*, int, int))((void**)(*(int**)piVar4))[0x7c / 4])(piVar4, 1, 0);
    }
    ((GlobalUI_s00de_1710*)*(void**)((char*)kGUI_PanelIDs_s00de_1710 + 0x184))->SetVisibility(1);
    *(int*)(param_1 + 0x38) = 0;
    EA_Stopwatch_SetUnits((void*)(param_1 + 8), 4);
    unsigned uLow;
    if (*(int*)(param_1 + 0x18) == 1) {
        unsigned long long uVar2 = __rdtsc();
        *(int*)(param_1 + 0xc) = (int)(uVar2 >> 0x20);
        uLow = (unsigned)uVar2;
    } else {
        QueryPerformanceCounter(&LStack_8);
        *(int*)(param_1 + 0xc) = LStack_8.HighPart;
        uLow = LStack_8.LowPart;
    }
    *(unsigned*)(param_1 + 8) = uLow;
    *(int*)(param_1 + 0x10) = 0;
    *(int*)(param_1 + 0x14) = 0;
    piVar4 = EA_Audio_GetSystemAT();
    if (piVar4 == 0) {
        uVar5 = 0;
    } else {
        uVar5 = ((unsigned(__thiscall*)(void*))((void**)(*(int**)piVar4))[0x20 / 4])(piVar4);
    }
    piVar4 = EA_Audio_GetSystemAT();
    if (piVar4 != 0) {
        ((void(__thiscall*)(void*, int))((void**)(*(int**)piVar4))[0x38 / 4])(piVar4, 0x3475365);
        ((void(__thiscall*)(void*, int, int))((void**)(*(int**)piVar4))[0x40 / 4])(piVar4, 0x3475381,
                                                                                   0x981429e1);
        ((void(__thiscall*)(void*, int, int))((void**)(*(int**)piVar4))[0x40 / 4])(piVar4, 0x3475385,
                                                                                   (int)uVar5);
        ((void(__thiscall*)(void*))((void**)(*(int**)piVar4))[0x58 / 4])(piVar4);
    }
    piVar4 = (int*)(param_1 + 0x34);
    *(char*)((char*)kGUI_PanelIDs_s00de_1710 + 0x103) = 1;
    if ((int*)*piVar4 != 0) {
        ((void(__thiscall*)(void*, int))((void**)(*(int**)*piVar4))[0xc / 4])((void*)*piVar4, 0);
        piVar6 = (int*)*piVar4;
        if (piVar6 != 0) {
            *piVar4 = 0;
            ((void(__thiscall*)(void*))((void**)(*(int**)piVar6))[4 / 4])(piVar6);
        }
    }
    int* puVar7 = *(int**)((char*)kGUI_PanelIDs_s00de_1710 + 0x1d8);
    if (puVar7 != *(int**)((char*)kGUI_PanelIDs_s00de_1710 + 0x1dc)) {
        do {
            ((void(__thiscall*)(void*, int))((void**)(*(int**)*puVar7))[0x2c / 4])((void*)*puVar7, 1);
            puVar7 = puVar7 + 1;
        } while (puVar7 != *(int**)((char*)kGUI_PanelIDs_s00de_1710 + 0x1dc));
    }
    piVar6 = (int*)*piVar4;
    piVar1 = *(int**)((char*)kGUI_PanelIDs_s00de_1710 + 0x15c);
    if (piVar6 != 0) {
        *piVar4 = 0;
        ((void(__thiscall*)(void*))((void**)(*(int**)piVar6))[4 / 4])(piVar6);
    }
    ((void(__thiscall*)(void*, int, int, int*))((void**)(*(int**)piVar1))[8 / 4])(piVar1, 0xb0237cdc,
                                                                                    0, piVar4);
    if ((int*)*piVar4 != 0) {
        ((void(__thiscall*)(void*, int))((void**)(*(int**)*piVar4))[8 / 4])((void*)*piVar4, 0);
    }
    char cVar3 = FUN_00685520(2);
    if (cVar3 == 0) goto LAB_00de1982;
    piVar4 = ((GlobalUI_s00de_1710*)*(void**)((char*)kGUI_PanelIDs_s00de_1710 + 0x184))->FindWindowByID(0x7a7ec60);
    if (piVar4 != 0) {
        if (*(int*)((char*)kGUI_PanelIDs_s00de_1710 + 0x1f8) == 0) {
            piVar6 = SP_AppSystem();
            uVar5 = ((unsigned(__thiscall*)(void*))((void**)(*(int**)piVar6))[0x54 / 4])(piVar6);
            if ((char)uVar5 != 0) goto LAB_00de1924;
        } else {
LAB_00de1924:
            uVar5 = 1;
        }
        ((void(__thiscall*)(void*, int, int))((void**)(*(int**)piVar4))[0x7c / 4])(piVar4, 2,
                                                                                    (int)uVar5);
    }
    piVar4 = ((GlobalUI_s00de_1710*)*(void**)((char*)kGUI_PanelIDs_s00de_1710 + 0x184))->FindWindowByID(0x7291fb7);
    if (piVar4 == 0) goto LAB_00de1982;
    if (*(int*)((char*)kGUI_PanelIDs_s00de_1710 + 0x1f8) == 0) {
        piVar6 = SP_AppSystem();
        uVar5 = ((unsigned(__thiscall*)(void*))((void**)(*(int**)piVar6))[0x54 / 4])(piVar6);
        if ((char)uVar5 != 0) goto LAB_00de1971;
    } else {
LAB_00de1971:
        uVar5 = 1;
    }
    ((void(__thiscall*)(void*, int, int))((void**)(*(int**)piVar4))[0x7c / 4])(piVar4, 2, (int)uVar5);
LAB_00de1982:
    ((SG*)param_1)->FUN_00de11a0();
    int* pTmp = FUN_00dd9190(2, 0);
    ((SG*)pTmp)->FUN_00dda090();
}

// @ 0x00de1a90
void SG::FUN_00de1a90(int param_2)
{
    int self = (int)this;
    if (*(int*)(self + 0x38) != 0) {
        void* piVar1 = EA_Audio_GetSystemAT();
        int uVar5 = (piVar1 != 0)
                        ? ((int(__thiscall*)(void*))((void**)(*(int**)piVar1))[0x20 / 4])(piVar1)
                        : 0;
        SP_cSPUISpace_KillSetiEffects(0x8e82b51c, uVar5);
        ((SG*)self)->FUN_00de13d0(*(int*)(self + 0x38), param_2);
    }
}

// @ 0x00de1ae0
bool SG::FUN_00de1ae0(int param_2, void* param_3)
{
    int self = (int)this;
    int* piVar1;
    int* piVar2;
    unsigned uVar4;
    unsigned char acStack_7f[3];
    int uStack_7c;
    int uStack_78;
    int uStack_74;
    unsigned long long VStack_70;
    unsigned long long VStack_5c;
    int uStack_48;
    int iStack_44;
    int* puStack_18;
    int iStack_10;
    int p = 0;

    if (((int*)param_3)[2] != 0x287259f6) goto caseD_4096dd1;
    p = ((int(__thiscall*)(void*))((void**)(*(int**)*(int**)param_3))[0x1c / 4])(
        *(void**)param_3);
    piVar1 = sAppPreferences;
    uStack_7c = 0;
    uStack_78 = 0;
    uStack_74 = 0;
    if (p < 0x62afb0e) {
        if (p != 0x62afb0d) {
            if (p < 0x4656453) {
                if (p != 0x4656452) {
                    switch (p) {
                        case 0x4096dd0:
                        case 0x4096dd3:
                        case 0x4096dd7:
                        case 0x4096dda:
                            break;
                        default:
                            goto caseD_4096dd1;
                    }
                }
            } else if (p < 0x6285661) {
                if (p < 0x628565e) {
                    if (p < 0x625cd50) goto caseD_4096dd1;
                    if (0x625cd54 < p) {
                        if (p == 0x6260bc8) {
                            ((SG*)self)->FUN_00de1a90((int)&uStack_7c);
                            *(int*)((char*)kGUI_PanelIDs_s00de_1710 + 0x108) = 3;
                            *(int*)((char*)kGUI_PanelIDs_s00de_1710 + 0x10c) = 3;
                            return false;
                        }
                        goto caseD_4096dd1;
                    }
                }
            } else {
                if (p < 0x629c446) goto caseD_4096dd1;
                if (0x629c448 < p) return false;
            }
        }
    caseD_4096dd0:;
    } else {
        if (0x7a7ec60 < p) {
            if (p < 0x7a7f79a) {
                if (p == 0x7a7f799) {
                    FUN_00de53d0(0);
                    FUN_00644b10();
                    iStack_10 = (int)kGUI_PanelIDs_s00de_1710;
                    uStack_48 = 0x7edf94a2;
                    *(int*)(self + 0x38) = 0x7a7f799;
                } else {
                    if (p != 0x7a7f798) goto caseD_4096dd1;
                    FUN_00de53d0(0);
                    FUN_00644b10();
                    iStack_10 = (int)kGUI_PanelIDs_s00de_1710;
                    uStack_48 = 0x8f6443b2;
                    *(int*)(self + 0x38) = 0x7a7f798;
                }
                puStack_18 = (int*)0x00ad0e52;
                iStack_44 = self;
                SP_cSPUIAssetBrowser_AdvancedLaunch(&uStack_48);
                uVar4 = (unsigned)FUN_00644b60();
                return (uVar4 & 0xffffff00) != 0;
            }
            if (p < 0x1628565e || 0x16285660 < p) goto caseD_4096dd1;
            goto caseD_4096dd0;
        }
        if (p == 0x7a7ec60) {
            acStack_7f[0] = 0;
            FUN_00407190(sAppPreferences, 0x80d8470, acStack_7f);
            if (acStack_7f[0] == 0) {
                piVar2 = ((GlobalUI_s00de_1710*)*(void**)((char*)kGUI_PanelIDs_s00de_1710 + 0x184))
                             ->FindWindowByID(0x809b111);
                if (piVar2 != 0) {
                    ((void(__thiscall*)(void*, int, int))((void**)(*(int**)piVar2))[0x7c / 4])(
                        piVar2, 1, 0);
                }
                acStack_7f[2] = 1;
                FUN_005dd750(acStack_7f + 2);
                ((void(__thiscall*)(void*, int, unsigned long long*))(
                    (void**)(*(int**)piVar1))[0x14 / 4])(piVar1, 0x80d8470, &VStack_70);
                if (((unsigned char)VStack_70 & 4) != 0) {
                    EA_Variant_Destruct(&VStack_70, 0);
                }
                int* uVar3 = SP_GetSaveArea(0x11ac192, 0);
                SP_SaveResource(piVar1, uVar3);
            }
            p = 0x7a7ec60;
        } else {
            if (p < 0x6526b7e) {
                if (p != 0x6526b7d && p != 0x62afb1c && p != 0x62afb2b) {
                    return false;
                }
                goto caseD_4096dd0;
            }
            if (p != 0x7291fb7) goto caseD_4096dd1;
            acStack_7f[0] = 0;
            FUN_00407190(sAppPreferences, 0x80d8460, acStack_7f);
            if (acStack_7f[0] == 0) {
                piVar2 = ((GlobalUI_s00de_1710*)*(void**)((char*)kGUI_PanelIDs_s00de_1710 + 0x184))
                             ->FindWindowByID(0x7a7ee50);
                if (piVar2 != 0) {
                    ((void(__thiscall*)(void*, int, int))((void**)(*(int**)piVar2))[0x7c / 4])(
                        piVar2, 1, 0);
                }
                acStack_7f[1] = 1;
                FUN_005dd750(acStack_7f + 1);
                ((void(__thiscall*)(void*, int, unsigned long long*))(
                    (void**)(*(int**)piVar1))[0x14 / 4])(piVar1, 0x80d8460, &VStack_5c);
                if (((unsigned char)VStack_5c & 4) != 0) {
                    EA_Variant_Destruct(&VStack_5c, 0);
                }
                int* uVar3 = SP_GetSaveArea(0x11ac192, 0);
                SP_SaveResource(piVar1, uVar3);
            }
            p = 0x7291fb7;
        }
    }
    ((SG*)self)->FUN_00de0ae0(p);
caseD_4096dd1:
    return false;
}

// @ 0x00de1e50
void SG::FUN_00de1e50(float param_2, float param_3, int param_4)
{
    int self = (int)this;
    int iVar1;
    char cVar2;
    int* piVar3;
    unsigned uVar4;
    int uVar5;
    int* puVar6;
    unsigned uVar7;
    int local_14;
    int uStack_10;
    int* local_c;
    float local_8[2];

    *(char*)(self + 0x60) = 0;
    local_14 = 0;
    if (*(int*)(self + 0x70) != 0) {
        local_c = *(int**)(self + 0x24);
        puVar6 = (int*)*local_c;
        if (puVar6 == 0) {
            local_c = local_c + 1;
            iVar1 = (int)*local_c;
            while (iVar1 == 0) {
                local_c = local_c + 1;
                iVar1 = (int)*local_c;
            }
            puVar6 = (int*)*local_c;
        }
        if (puVar6 != (int*)*(int*)(*(int*)(self + 0x24) + *(int*)(self + 0x28) * 4)) {
            do {
                piVar3 = ((Layout_s00de_1710*)*(void**)(self + 0x70))->FindWindowByID(*puVar6, 1);
                if (piVar3 != 0) {
                    ((void(__thiscall*)(void*, float, float, float*))(
                        (void**)(*(int**)piVar3))[200 / 4])(piVar3, param_2, param_3, local_8);
                    cVar2 = ((char(__thiscall*)(void*, float, float))(
                        (void**)(*(int**)piVar3))[0xbc / 4])(piVar3, local_8[0], local_8[1]);
                    if (cVar2 == 0 || *(char*)(self + 0x60) != 0) {
                        uVar7 = 0;
                        uVar4 = (unsigned)((puVar6[2] - puVar6[1]) >> 2);
                        if (uVar4 != 0) {
                            do {
                                piVar3 = ((Layout_s00de_1710*)*(void**)(self + 0x70))
                                             ->FindWindowByID(*(int*)(puVar6[1] + uVar7 * 4), 1);
                                if (piVar3 != 0) {
                                    ((void(__thiscall*)(void*, int, int))(
                                        (void**)(*(int**)piVar3))[0x7c / 4])(piVar3, 1, 0);
                                }
                                uVar7 = uVar7 + 1;
                            } while (uVar7 < uVar4);
                        }
                    } else {
                        uVar4 = ((unsigned(__thiscall*)(void*))((void**)(*(int**)piVar3))[0x28 / 4])(
                            piVar3);
                        if ((uVar4 & 1) != 0) {
                            local_14 = ((int(__thiscall*)(void*))((void**)(*(int**)piVar3))[0x1c / 4])(
                                piVar3);
                        }
                        uVar4 = 0;
                        uVar7 = (unsigned)((puVar6[2] - puVar6[1]) >> 2);
                        if (uVar7 != 0) {
                            do {
                                if (*(int*)(puVar6[1] + uVar4 * 4) != 0 &&
                                    (piVar3 = ((Layout_s00de_1710*)*(void**)(self + 0x70))
                                                  ->FindWindowByID(*(int*)(puVar6[1] + uVar4 * 4), 1),
                                     piVar3 != 0)) {
                                    ((void(__thiscall*)(void*, int, int))(
                                        (void**)(*(int**)piVar3))[0x7c / 4])(piVar3, 1, 1);
                                    *(char*)(self + 0x60) = 1;
                                }
                                uVar4 = uVar4 + 1;
                            } while (uVar4 < uVar7);
                        }
                    }
                }
                puVar6 = (int*)puVar6[6];
                while (puVar6 == 0) {
                    int** piVarTmp = (int**)(local_c + 1);
                    local_c = local_c + 1;
                    puVar6 = (int*)*piVarTmp;
                }
            } while (puVar6 != (int*)*(int*)(*(int*)(self + 0x24) + *(int*)(self + 0x28) * 4));
        }
        if (*(char*)(self + 0x60) == 0 && param_4 != 0) {
            ((HT*)(self + 0x20))->find(local_8, &param_4);
            puVar6 = (int*)*(int*)local_8;
            if ((int)puVar6 != *(int*)(*(int*)(self + 0x24) + *(int*)(self + 0x28) * 4)) {
                uVar4 = 0;
                uVar7 = (unsigned)((puVar6[2] - puVar6[1]) >> 2);
                if (uVar7 != 0) {
                    do {
                        piVar3 = ((Layout_s00de_1710*)*(void**)(self + 0x70))
                                     ->FindWindowByID(*(int*)(puVar6[1] + uVar4 * 4), 1);
                        if (piVar3 != 0) {
                            ((void(__thiscall*)(void*, int, int))(
                                (void**)(*(int**)piVar3))[0x7c / 4])(piVar3, 1, 1);
                            *(char*)(self + 0x60) = 1;
                        }
                        uVar4 = uVar4 + 1;
                    } while (uVar4 < uVar7);
                }
            }
        }
    }
    if (local_14 != *(int*)(self + 100) && local_14 != 0) {
        piVar3 = EA_Audio_GetSystemAT();
        if (piVar3 == 0) {
            uVar5 = 0;
        } else {
            uVar5 = ((int(__thiscall*)(void*))((void**)(*(int**)piVar3))[0x20 / 4])(piVar3);
        }
        piVar3 = EA_Audio_GetSystemAT();
        if (piVar3 != 0) {
            ((void(__thiscall*)(void*, int))((void**)(*(int**)piVar3))[0x38 / 4])(piVar3, 0x3475365);
            ((void(__thiscall*)(void*, int, int))((void**)(*(int**)piVar3))[0x40 / 4])(
                piVar3, 0x3475381, 0xd607a5a7);
            ((void(__thiscall*)(void*, int, int))((void**)(*(int**)piVar3))[0x40 / 4])(
                piVar3, 0x3475385, uVar5);
            ((void(__thiscall*)(void*))((void**)(*(int**)piVar3))[0x58 / 4])(piVar3);
        }
    }
    *(int*)(self + 100) = local_14;
}

// @ 0x00de20e0
void SG::FUN_00de20e0(int param_2)
{
    int self = (int)this;
    if (*(int*)(self + 0x70) != 0) {
        int* piVar4 = *(int**)(self + 0x24);
        int* piVar3 = (int*)*piVar4;
        if (piVar3 == 0) {
            piVar4 = piVar4 + 1;
            int iVar1 = (int)*piVar4;
            while (iVar1 == 0) {
                piVar4 = piVar4 + 1;
                iVar1 = (int)*piVar4;
            }
            piVar3 = (int*)*piVar4;
        }
        if (piVar3 != (int*)*(int*)(*(int*)(self + 0x24) + *(int*)(self + 0x28) * 4)) {
            do {
                int* piVar2 = ((Layout_s00de_1710*)*(void**)(self + 0x70))->FindWindowByID(*piVar3, 1);
                if (piVar2 != 0 &&
                    (piVar2 = (int*)((int(__thiscall*)(void*, int))(
                        (void**)(*(int**)piVar2))[0xc / 4])(piVar2, 0x8ed27e7a),
                     piVar2 != 0)) {
                    bool bEq = (*piVar3 == param_2);
                    ((void(__thiscall*)(void*, int, int))((void**)(*(int**)piVar2))[0x28 / 4])(
                        piVar2, 4, bEq);
                }
                piVar3 = (int*)piVar3[6];
                while (piVar3 == 0) {
                    piVar3 = (int*)*(piVar4 + 1);
                    piVar4 = piVar4 + 1;
                }
            } while (piVar3 != (int*)*(int*)(*(int*)(self + 0x24) + *(int*)(self + 0x28) * 4));
        }
    }
}

// @ 0x00de2180
void SG::FUN_00de2180(float param_2, float param_3, int param_4)
{
    int self = (int)this;
    char cVar1;
    int* piVar2;
    unsigned uVar3;
    int iVar4;
    unsigned uVar5;
    int* piVar6;
    int* puVar7;
    int uVar8;
    int* local_c;
    float local_8[2];

    ((SG*)self)->FUN_00de1e50(param_2, param_3, param_4);
    ((SG*)self)->FUN_00de20e0(param_4);
    param_4 = 0;
    if (*(int*)(self + 0x70) != 0) {
        piVar2 = *(int**)(self + 4);
        puVar7 = (int*)*piVar2;
        local_c = piVar2;
        if (puVar7 == 0) {
            local_c = piVar2 + 1;
            iVar4 = (int)*local_c;
            while (iVar4 == 0) {
                local_c = local_c + 1;
                iVar4 = (int)*local_c;
            }
            puVar7 = (int*)*local_c;
        }
        iVar4 = 0;
        piVar6 = local_c;
        if (puVar7 != (int*)piVar2[*(int*)(self + 8)]) {
            do {
                piVar2 = ((Layout_s00de_1710*)*(void**)(self + 0x70))->FindWindowByID(*puVar7, 1);
                if (piVar2 != 0) {
                    ((void(__thiscall*)(void*, float, float, float*))(
                        (void**)(*(int**)piVar2))[200 / 4])(piVar2, param_2, param_3, local_8);
                    cVar1 = ((char(__thiscall*)(void*, float, float))(
                        (void**)(*(int**)piVar2))[0xbc / 4])(piVar2, local_8[0], local_8[1]);
                    if (cVar1 == 0) {
                        uVar3 = 0;
                        uVar5 = (unsigned)((puVar7[2] - puVar7[1]) >> 2);
                        piVar6 = local_c;
                        if (uVar5 != 0) {
                            do {
                                piVar2 = ((Layout_s00de_1710*)*(void**)(self + 0x70))
                                             ->FindWindowByID(*(int*)(puVar7[1] + uVar3 * 4), 1);
                                if (piVar2 != 0) {
                                    ((void(__thiscall*)(void*, int, int))(
                                        (void**)(*(int**)piVar2))[0x7c / 4])(piVar2, 1, 0);
                                }
                                uVar3 = uVar3 + 1;
                            } while (uVar3 < uVar5);
                        }
                    } else if ((int)((puVar7[2] - puVar7[1]) >> 2) != 0) {
                        piVar2 = ((Layout_s00de_1710*)*(void**)(self + 0x70))->FindWindowByID((int)puVar7[1], 1);
                        uVar3 = ((unsigned(__thiscall*)(void*))((void**)(*(int**)piVar2))[0x28 / 4])(
                            piVar2);
                        if ((uVar3 & 1) != 0) {
                            param_4 = (int)puVar7[1];
                            *(int*)(self + 0x6c) = param_4;
                        }
                    }
                }
                puVar7 = (int*)puVar7[6];
                while (puVar7 == 0) {
                    int** piVarTmp = (int**)(piVar6 + 1);
                    piVar6 = piVar6 + 1;
                    local_c = piVar6;
                    puVar7 = (int*)*piVarTmp;
                }
                iVar4 = param_4;
            } while (puVar7 != (int*)*(int*)(*(int*)(self + 4) + *(int*)(self + 8) * 4));
        }
        if (*(int*)(self + 0x68) != 0 &&
            (piVar2 = ((Layout_s00de_1710*)*(void**)(self + 0x70))->FindWindowByID(*(int*)(self + 0x68), 1),
             piVar2 != 0)) {
            if (iVar4 == 0 || iVar4 == *(int*)(self + 0x68)) {
                uVar8 = 1;
            } else {
                uVar8 = 0;
            }
            ((void(__thiscall*)(void*, int, int))((void**)(*(int**)piVar2))[0x7c / 4])(piVar2, 1,
                                                                                        uVar8);
        }
    }
}

// @ 0x00de2350
extern "C" void __stdcall FUN_00de2350(int* param_1, unsigned param_2)
{
    for (unsigned uVar3 = 0; uVar3 < param_2; uVar3++) {
        int iVar2 = param_1[uVar3];
        while (iVar2 != 0) {
            int iVar1 = iVar2;
            iVar2 = *(int*)(iVar1 + 0x18);
            SP_cString_dtor((void*)(iVar1 + 4));
            operator_delete((void*)iVar1);
        }
        param_1[uVar3] = 0;
    }
}

// @ 0x00de23a0
void cUICalloutSequencer::Update(float fDeltaTime)
{
    if (mnCountdown != 0) {
        --mnCountdown;
        if (mnCountdown == 0) {
            if (mnEventID == 0x7a7f799) {
                mnEventID = 0;
                if (mnValue24 != 0) {
                    sPositionEvent* pEvent = ResetPositionEvent();
                    pEvent->mFrom[0] = mnValue24;
                    pEvent->mFrom[1] = mnValue28;
                    pEvent->mFrom[2] = mnValue2C;
                    pEvent->mTo[0] = 0;
                    pEvent->mTo[1] = 0;
                    pEvent->mTo[2] = 0;
                    pEvent->mnPad18 = 0;
                    pEvent->mnPad1c = 0;
                    pEvent->mnPad20 = 0;
                    pEvent->mnType = 1;
                    pEvent->mnPad28 = 0;
                    GetEventDispatcher()->Dispatch(0x21851ebe);
                    return;
                }
            } else if (mnEventID == 0x7a7f798) {
                mnEventID = 0;
                if (mnValue24 != 0) {
                    sPositionEvent* pEvent = ResetPositionEvent();
                    pEvent->mFrom[0] = 0;
                    pEvent->mFrom[1] = 0;
                    pEvent->mFrom[2] = 0;
                    pEvent->mTo[0] = mnValue24;
                    pEvent->mTo[1] = mnValue28;
                    pEvent->mTo[2] = mnValue2C;
                    pEvent->mnPad18 = 0;
                    pEvent->mnPad1c = 0;
                    pEvent->mnPad20 = 0;
                    pEvent->mnType = 1;
                    pEvent->mnPad28 = 0;
                    GetEventDispatcher()->Dispatch(0x21851ebe);
                    return;
                }
            }
        }
    }
    if (mTimer2.mnStartTime) {
        uint32_t aWindowIDs[4] = {0x7a7f799, 0x7a7f798, 0x5943b78, 0x6260bc8};
        float fFade = (float)mTimer2.GetElapsedTime() * mTimer2.mfUnitsPerCycle /
                      (gCalloutFadePeriod * 1000.0f);
        for (uint32_t i = 0; i < 4; ++i) {
            cUIWindow_s00de_23a0* pWindow = gUI->mpWindows->FindWindowByID(aWindowIDs[i]);
            if (!pWindow)
                continue;
            if (1.0f <= fFade) {
                SetWindowScale(pWindow, 1.0f, 1.0f);
                mTimer2.Reset();
            } else {
                float fScale = (float)sin((double)gCalloutSpinRate * (double)fFade) *
                                   (1.0f - fFade) * gCalloutSpinBias + 1.0f;
                SetWindowScale(pWindow, fScale, fScale);
            }
        }
    }
    gUI->UpdateCalloutWindows();
    cAppSettings* pSettings = GetSetting3_s00de_23a0();
    uint8_t bFreeCam = pSettings->mbFreeCam;
    if (!bFreeCam && mbPreviousFreeCam) {
        gUI->SetCalloutEnabled(0);
        gUI->SetCalloutEnabled(1);
        if (gUI->mnMode == 3)
            gUI->SetEditorMode(5, 0);
        mnPadA8 = 0;
    }
    IVisualEffect* pEffect = mpEffect;
    mbPreviousFreeCam = bFreeCam;
    if (pEffect) {
        XformMsg msg;
        Vector3_s00de_23a0 vZero(0.0f, 0.0f, 0.0f);
        msg.mnVersion = 1;
        msg.mnFlags = 4;
        msg.mMatrix = gCalloutMatrix;
        msg.mfScale = 1.0f;
        msg.mPos.x = (gCalloutMatrix.m[2][0] + gCalloutMatrix.m[0][0]) * vZero.x -
                     gCalloutMatrix.m[1][0] * 10.0f + gCalloutTranslation.x;
        msg.mPos.y = (gCalloutMatrix.m[2][1] + gCalloutMatrix.m[0][1]) * vZero.y -
                     gCalloutMatrix.m[1][1] * 10.0f + gCalloutTranslation.y;
        msg.mPos.z = (gCalloutMatrix.m[2][2] + gCalloutMatrix.m[0][2]) * vZero.z -
                     gCalloutMatrix.m[1][2] * 10.0f + gCalloutTranslation.z;
        pEffect->SetTransform(&msg);
    }
    if (mTimer.mnStartTime) {
        if ((float)mTimer.GetElapsedTime() * mTimer.mfUnitsPerCycle <= gCalloutTimeout)
            return;
        mTimer.Reset();
        return;
    }
    cUIWindow_s00de_23a0* pWindow = gUI->mpWindows->FindWindowByID(0x3685038);
    if (pWindow) {
        bool bPlaying = pWindow->IsPlaying();
        bool bShouldPlay = !(gUI->mbMenuActive || bFreeCam || mbBlocked || mbStarted ||
                             gUI->mbGalaxyOpen || gUI->mbOverlayActive);
        if (bPlaying) {
            if (!bShouldPlay) {
                gUI->SetCalloutEnabled(0);
                pWindow->SetVisible(1, false);
            }
        } else if (bShouldPlay) {
            gUI->SetCalloutEnabled(1);
            pWindow->SetVisible(1, true);
        }
    }
    if (!gCalloutWindowsEnabled)
        return;
    if (gUI->mbNoCallouts)
        return;
    float fA;
    float fB;
    GetCameraBasis(&fB, &fA);
    if (!pSettings || !pSettings->mbFreeCam) {
        mpB0 = gUI->mpWindows->GetActiveXform();
        PostCalloutXform(&mnPad40, fA, fB, mnEventID);
    }
    pWindow = gUI->mpWindows->FindWindowByID(gHintWindowId);
    if (pWindow)
        pWindow->SetVisible(1, mbA0 == 0);
    bool bGalaxyHint;
    if (mnEventID != 0 && mnEventID != 0x7a7ec60 && gUI->mbGalaxyOpen)
        bGalaxyHint = true;
    else
        bGalaxyHint = false;
    pWindow = gUI->mpWindows->FindWindowByID(0x689a975);
    if (pWindow)
        pWindow->SetVisible(1, bGalaxyHint);
    bool bGalaxyEntry = (mnEventID == 0x7a7ec60);
    uint32_t aHintIDs[2] = {0x7a7f799, 0x7a7f798};
    if (IsWorldLayoutFlagSet(2)) {
        for (uint32_t i = 0; i < 2; ++i) {
            pWindow = gUI->mpWindows->FindWindowByID(aHintIDs[i]);
            if (pWindow)
                pWindow->SetVisible(1, bGalaxyEntry);
        }
    }
}

// @ 0x00de28f0
void cPropertyTableTriple::LoadStringPairs(uint32_t nObject, uint32_t nProperty)
{
    AutoRefCount<cPropertyList_s00de_23a0> props;
    cPropertyManager_s00de_23a0* pManager = SP::PropertyManager();
    props = (cPropertyList_s00de_23a0*)0;
    if (pManager->GetProperty((void*)nObject, 0, &props.mpObject)) {
        int32_t nCount;
        uint32_t* pValues = 0;
        nCount = 0;
        SP::GetPropertyAsUint32Array(props.mpObject, nProperty, &nCount, &pValues);
        for (int32_t i = 0; i < nCount; i += 2) {
            SP::cString_s00de_23a0 name(0x2b7a0311, pValues[i + 1], 0);
            SP::InsertStringEntry(&mTable2, pValues[i], name, false);
        }
    }
    if (props.mpObject)
        props.mpObject->Release();
}

// @ 0x00de29f0
void cPropertyTableTriple::Clear()
{
    mTable0.Reset();
    mTable1.Reset();
    mTable2.ResetStrings();
}

// @ 0x00de2a50
void cPropertyTableTriple::Destroy()
{
    mTable2.FreeStrings();
    mTable1.Free();
    mTable0.Free();
}

// @ 0x00de2ae0
void cPropertyTableTriple::AddValue1(uint32_t nKey, uint32_t nValue)
{
    sTableIterator it;
    mTable1.Find(&it, &nKey);
    if (it.mpNode == mTable1.mpBuckets[mTable1.mnBucketCount]) {
        sKeyValuePair pair;
        pair.mnKey = nKey;
        pair.mValues.mpBegin = 0;
        pair.mValues.mpEnd = 0;
        pair.mValues.mpCapacity = 0;
        pair.mValues.InsertAt(0, &nValue);
        sInsertResult result;
        mTable1.Insert(&result, &pair, false);
        FreeU32List(pair.mValues);
    } else {
        uint32_t* pEnd = it.mpNode->mValues.mpEnd;
        if (pEnd < it.mpNode->mValues.mpCapacity) {
            it.mpNode->mValues.mpEnd = pEnd + 1;
            if (pEnd)
                *pEnd = nValue;
        } else {
            it.mpNode->mValues.InsertAt(pEnd, &nValue);
        }
    }
}

// @ 0x00de2bf0
void cPropertyTableTriple::AddValue0(uint32_t nKey, uint32_t nValue)
{
    sTableIterator it;
    mTable0.Find(&it, &nKey);
    if (it.mpNode == mTable0.mpBuckets[mTable0.mnBucketCount]) {
        sKeyValuePair pair;
        pair.mnKey = nKey;
        pair.mValues.mpBegin = 0;
        pair.mValues.mpEnd = 0;
        pair.mValues.mpCapacity = 0;
        pair.mValues.InsertAt(0, &nValue);
        sInsertResult result;
        mTable0.Insert(&result, &pair, false);
        FreeU32List(pair.mValues);
    } else {
        uint32_t* pEnd = it.mpNode->mValues.mpEnd;
        if (pEnd < it.mpNode->mValues.mpCapacity) {
            it.mpNode->mValues.mpEnd = pEnd + 1;
            if (pEnd)
                *pEnd = nValue;
        } else {
            it.mpNode->mValues.InsertAt(pEnd, &nValue);
        }
    }
}

// @ 0x00de2d00
cUIPropertyTableSet::cUIPropertyTableSet()
: mTimer(0, false), mnPad24(0), mnPad28(0), mnPad2c(0), mnPad30(0), mpListener(0),
      mTables(), mbA0(0), mnPadA4(0), mnPadA8(0), mpB0(0), mTimer2(0, false) {
    mbD0 = 0;
}

// @ 0x00de2de0
cUIPropertyTableSet::~cUIPropertyTableSet()
{
    mTables.Destroy();
    if (mpListener)
        mpListener->Release();
}

// @ 0x00de2e20
void cPropertyTableTriple::LoadGroup0(uint32_t nObject, uint32_t nProperty)
{
    AutoRefCount<cPropertyList_s00de_23a0> props;
    cPropertyManager_s00de_23a0* pManager = SP::PropertyManager();
    props = (cPropertyList_s00de_23a0*)0;
    if (pManager->GetProperty((void*)nObject, 0, &props.mpObject)) {
        int32_t nCount;
        uint32_t* pValues = 0;
        nCount = 0;
        SP::GetPropertyAsUint32Array(props.mpObject, nProperty, &nCount, &pValues);
        for (int32_t i = 0; i < nCount; i += 2)
            AddValue1(pValues[i], pValues[i + 1]);
    }
    if (props.mpObject)
        props.mpObject->Release();
}

// @ 0x00de2ed0
void cPropertyTableTriple::LoadGroup1(uint32_t nObject, uint32_t nProperty)
{
    AutoRefCount<cPropertyList_s00de_23a0> props;
    cPropertyManager_s00de_23a0* pManager = SP::PropertyManager();
    props = (cPropertyList_s00de_23a0*)0;
    if (pManager->GetProperty((void*)nObject, 0, &props.mpObject)) {
        int32_t nCount;
        uint32_t* pValues = 0;
        nCount = 0;
        SP::GetPropertyAsUint32Array(props.mpObject, nProperty, &nCount, &pValues);
        for (int32_t i = 0; i < nCount; i += 2)
            AddValue0(pValues[i], pValues[i + 1]);
    }
    if (props.mpObject)
        props.mpObject->Release();
}

// @ 0x00de2f80
void cUIPropertyTableSet::Init()
{
    mTables.LoadGroup1(0xb33d24db, 0x95eb6ed);
    mTables.LoadGroup0(0xb33d24db, 0x34419b24);
    mTables.LoadStringPairs(0xb33d24db, 0x7d5f207d);
    mTimer2.SetUnits(EA::Stopwatch_s00de_23a0::kUnitsMilliseconds);
    AutoRefCount<cPropertyList_s00de_23a0> props;
    cPropertyManager_s00de_23a0* pManager = SP::PropertyManager();
    props = (cPropertyList_s00de_23a0*)0;
    if (pManager->GetProperty(gScriptProperties, 0, &props.mpObject)) {
        sString16 name;
        if (SP::GetPropertyAsString16(props.mpObject, 0xb08e885a, &name.mpBegin))
            mnPadD4 = SP::FNV1_String16(name.mpBegin, 0x811c9dc5, 1);
        if (SP::GetPropertyAsString16(props.mpObject, 0xc3398948, &name.mpBegin))
            mnPadD8 = SP::FNV1_String16(name.mpBegin, 0x811c9dc5, 1);
        if (SP::GetPropertyAsString16(props.mpObject, 0x5ad618b8, &name.mpBegin))
            mnPadDC = SP::FNV1_String16(name.mpBegin, 0x811c9dc5, 1);
        if (SP::GetPropertyAsString16(props.mpObject, 0xd74f5e46, &name.mpBegin))
            mnPadE0 = SP::FNV1_String16(name.mpBegin, 0x811c9dc5, 1);
    }
    if (props.mpObject)
        props.mpObject->Release();
}

// @ 0x00de3130
void cUIHintTrigger::Tick(float fDeltaTime)
{
    if (mnCountdown > 0) {
        --mnCountdown;
        if (mnCountdown <= 0) {
            mnCountdown = 0;
            GetPlanetRecord((uint32_t)mpOwner)->Setup();
            OnTriggerEnded();
            StarManager()->UpdateRolloverStars();
            StarManager()->UpdateStarEffects();
            GetLocalPlayer(mnCalloutID)->FindLocal(0);
        }
    }
    if (mTimer.mnStartTime) {
        if (200.0f < (float)mTimer.GetElapsedTime() * mTimer.mfUnitsPerCycle)
            mpOwner->mpEffectSet->SetFlag(0);
        if (2000.0f < (float)mTimer.GetElapsedTime() * mTimer.mfUnitsPerCycle) {
            cGameDataIface* pData = ((cGameDataIface*)GetGameData())->GetSub();
            pData->SetStar(mnValue20, false);
            CalloutMessageBox(this, &gCalloutMessageSpec);
            mTimer.Reset();
            mTimer.mnStartTime = 0;
            mTimer.mnTotalElapsedTime = 0;
        }
    }
}

// @ 0x00de3240
void cUIHintTrigger::Close()
{
    if (mpOwner == 0) {
        gUI->SetEditorMode(2, 0);
        return;
    }
    GetRolloverManager()->SetupRolloverStarEffects();
    for (uint32_t i = 0; i < (uint32_t)(gUI->mppStarsEnd - gUI->mppStars); ++i)
        gUI->mppStars[i]->SetFlag(1);
    mpOwner->mpEffectSet->Highlight(0);
    cGameDataIface* pData = ((cGameDataIface*)GetGameData())->GetSub();
    pData->SetStar(mpOwner->mnID, false);
    CalloutMessageBox(this, &gGalaxyMessageSpec);
}

// @ 0x00de3300
void GameEntry::FUN_de3300()
{
    void* p = FUN_00df5f40();
    ((Fn2)(*(void***)p)[0x60 / 4])(p, 0, 1);
    p = FUN_00df5f40();
    ((Fn1)(*(void***)p)[0x5c / 4])(p, 0);
    ((GameEntry*)*(u32*)&g_16a1344)->ShowGalaxy(0);
    ((GameEntry*)*(u32*)&g_16a1344)->ShowGalaxy(1);
    ((GameEntry*)*(u32*)&g_16a1344)->mp198->Do();
    mp48 = 0;
    p = FUN_00df5f40();
    return ((Root*)p)->FUN_df95d0();
}

// @ 0x00de3370
GameEntry* GameEntry::Ctor_de3370()
{
    BaseCtor();
    mpVtbl = g_147dd00;
    mStopwatch.Ctor(0, 0);
    mStr20.mpBegin = (u32)g_1667bac;
    mStr20.mpEnd = (u32)g_1667bac;
    _ReadWriteBarrier();
    mStr20.mpCap = (u32)g_1667bae;
    mStr30.mpCap = (u32)g_1667bae;
    mStr30.mpBegin = (u32)g_1667bac;
    mStr30.mpEnd = (u32)g_1667bac;
    _ReadWriteBarrier();
    mp48 = 0;
    mStopwatch.SetUnits(4);
    g_16a11b4 = (cUISingleton48*)this;
    return this;
}

// @ 0x00de33e0
void GameEntry::OnModalWindowEnd(u32 a2, u32 a3)
{
    ((GameEntry*)*(u32*)0x16a1344)->FUN_de53d0(0);
    if (mp48 == 0)
        return ((GameEntry*)*(u32*)0x16a1344)->FUN_de86d0(2, 0);

    for (u32 i = 0;
         i < (u32)(((s32)((*(GameEntry**)0x16a1344)->mn1DC -
                          (*(GameEntry**)0x16a1344)->mp1D8)) >> 2); ++i) {
        void* e = ((void**)(*(GameEntry**)0x16a1344)->mp1D8)[i];
        ((Fn1)(*(void***)e)[0x30 / 4])(e, 0);
    }

    void* audio = EA_Audio_GetSystemAT();
    if (a3 == 0x5107b1a) {
        u32 v = 0;
        if (audio != 0)
            v = ((FnU)(*(void***)audio)[0x20 / 4])(audio);
        audio = EA_Audio_GetSystemAT();
        if (audio != 0) {
            ((Fn1)(*(void***)audio)[0x38 / 4])(audio, 0x3475365);
            ((Fn2)(*(void***)audio)[0x40 / 4])(audio, 0x3475381, 0xb7d87b0c);
            ((Fn2)(*(void***)audio)[0x40 / 4])(audio, 0x3475385, v);
            ((FnV)(*(void***)audio)[0x58 / 4])(audio);
        }
        mn40 = *(u32*)0x16a0f18;
        Mgr* mgr = (Mgr*)FUN_0067cab0();
        mn44 = mgr->FUN_8013c0();
        mgr = (Mgr*)FUN_0067cab0();
        mgr->FindLocal(0x1003);
        return;
    }

    u32 v = 0;
    if (audio != 0)
        v = ((FnU)(*(void***)audio)[0x20 / 4])(audio);
    audio = EA_Audio_GetSystemAT();
    if (audio != 0) {
        ((Fn1)(*(void***)audio)[0x38 / 4])(audio, 0x3475365);
        ((Fn2)(*(void***)audio)[0x40 / 4])(audio, 0x3475381, 0x6bd55b2e);
        ((Fn2)(*(void***)audio)[0x40 / 4])(audio, 0x3475385, v);
        ((FnV)(*(void***)audio)[0x58 / 4])(audio);
    }
    mp48 = 0;
    Vec3f ctx;
    ctx.x = 0.0f;
    ctx.y = 0.0f;
    ctx.z = 0.0f;
    GameEntry* g = *(GameEntry**)0x16a1344;
    if (g->mp198 != 0) {
        Obj198Sub* sub = &g->mp198->mSub04;
        ((FnUP)(*(void***)sub)[4 / 4])(sub, 0x2ca298e9, &ctx);
    }
    ((GameEntry*)*(u32*)0x16a1344)->FUN_de86d0(2, 0);
}

// @ 0x00de35d0
void GameEntry::Dtor_de35d0()
{
    mpVtbl = (void*)g_147dd00;
    *(u32*)&g_16a11b4 = 0;
    u32 p = mStr30.mpBegin;
    if ((s32)((mStr30.mpCap - p) & 0xfffffffe) > 2 && p != 0)
        op_del_array((void*)p);
    p = mStr20.mpBegin;
    if ((s32)((mStr20.mpCap - p) & 0xfffffffe) > 2 && p != 0)
        op_del_array((void*)p);
    mpVtbl = (void*)g_147dba8;
}

// @ 0x00de3650
void GameEntry::BlowSavedGameUpRealGood()
{
    if (mp48 == 0)
        return;

    GameEntry* g = *(GameEntry**)0x16a1344;
    void* out = 0;
    void* obj = g->mp15C;
    ((Fn2P)(*(void***)obj)[8 / 4])(obj, 0x339dccf3, 0, &out);

    if (out != 0) {
        VisualOut* vo = (VisualOut*)out;
        f32 f80 = vo->mf80;
        f32 f84 = vo->mf84;
        f32 f88 = vo->mf88;
        Mat33 mat = *(const Mat33*)0x16a122c;
        Xform x;
        x.mMat = mat;
        x.mf04 = ((f84 * *(f32*)0x16a1238 + f88 * *(f32*)0x16a1244)
                  + *(f32*)0x16a122c * f80) + *(f32*)0x16a1250;
        x.mf08 = *(f32*)0x16a1254
                 + ((f84 * *(f32*)0x16a123c + f88 * *(f32*)0x16a1248)
                    + *(f32*)0x16a1230 * f80);
        x.mf0C = *(f32*)0x16a1258
                 + ((f84 * *(f32*)0x16a1240 + f88 * *(f32*)0x16a124c)
                    + *(f32*)0x16a1234 * f80);
        x.mn00 = 4;
        x.mn02 = 1;
        x.mf10 = *(f32*)0x1485720;
        ((FnP)(*(void***)out)[0x18 / 4])(out, &x);
        ((Fn1)(*(void***)out)[8 / 4])(out, 0);
    }

    Vec3f ctx;
    ctx.x = 0.0f;
    ctx.y = 0.0f;
    ctx.z = 0.0f;
    GameEntry* g2 = *(GameEntry**)0x16a1344;
    if (g2->mp198 != 0) {
        Obj198Sub* sub = &g2->mp198->mSub04;
        ((FnUP)(*(void***)sub)[4 / 4])(sub, 0x2ca298e9, &ctx);
    }
    mStopwatch.Restart();
    if (mp48 != (u32)&mStr20) {
        EaString16* s = (EaString16*)mp48;
        mStr20.Assign(s->mpBegin, s->mpEnd);
    }
    if (out != 0)
        ((FnV)(*(void***)out)[4 / 4])(out);
}

// @ 0x00de38b0
void GameEntry::FUN_de38b0(u32 id, u32 arg)
{
    if ((((u32*)&DAT_016a1848)[id >> 5] >> (id & 0x1f)) & 1)
        return;
    if (id == 0x1b && (*(GameEntry**)&g_16a1344)->mb1F1 == 0) {
        void* audio = EA_Audio_GetSystemAT();
        KillSetiEffects(0x5da7b944,
                        audio != 0 ? ((FnU)(*(void***)audio)[0x20 / 4])(audio) : 0);
        ((GameEntry*)*(u32*)&g_16a1344)->FUN_de52d0();
    }
    FUN_e00650(id, arg);
}

// @ 0x00de3930
void __cdecl FUN_00de3930()
{
    void* ms = MessageServer();
    ((Fn3)(*(void***)ms)[0x14 / 4])(ms, 0x695d2ed, 0, 0);
    void* movie = MovieSystem();
    if (movie != 0)
        ((Fn1)(*(void***)movie)[0x40 / 4])(movie, 1);
    ((GameEntry*)*(u32*)0x16a1344)->FUN_de53d0(1);
    for (void** p = (void**)(*(GameEntry**)0x16a1344)->mp1D8;
         p != (void**)(*(GameEntry**)0x16a1344)->mn1DC; ++p) {
        void* e = *p;
        ((Fn1)(*(void***)e)[0x30 / 4])(e, 1);
    }
    GameEntry* g = *(GameEntry**)0x16a1344;
    void* w = ((UI*)g->mp184)->FindWindowByID(0x10f33e0);
    if (w != 0)
        ((Fn2)(*(void***)w)[0x7c / 4])(w, 1, 0);
    g = *(GameEntry**)0x16a1344;
    w = ((UI*)g->mp184)->FindWindowByID(0x10ed874);
    if (w != 0)
        ((Fn2)(*(void***)w)[0x7c / 4])(w, 1, (u32)(g->mb1F1 == 0));
    g = *(GameEntry**)0x16a1344;
    ((UI*)g->mp184)->SetVisibility((u32)(g->mb1F1 == 0));
    g = *(GameEntry**)0x16a1344;
    w = ((Layout*)g->mLayout144)->FindWindowByID(0x615a5ff, 1);
    if (w != 0)
        ((Fn2)(*(void***)w)[0x7c / 4])(w, 1, 0);
    g = *(GameEntry**)0x16a1344;
    if (g->mpF8 != 0) {
        w = ((F8Obj*)g->mpF8)->mpLayoutB8->FindWindowByID(0x2e5a4a8, 1);
        if (w != 0)
            ((Fn2)(*(void***)w)[0x7c / 4])(w, 1, 0);
    }
    g = *(GameEntry**)0x16a1344;
    w = ((UI*)g->mp184)->FindWindowByID(0x10ed852);
    if (w == 0) {
        g->mpF8 = 0;
        return;
    }
    void* w2 = ((FnC)(*(void***)w)[0xc / 4])(w, 0x8ed27e7a);
    if (w2 == 0) {
        g->mpF8 = 0;
        return;
    }
    ((Fn2)(*(void***)w2)[0x28 / 4])(w2, 4, 1);
    g->mpF8 = 0;
}

// @ 0x00de3ae0
void __cdecl FUN_00de3ae0()
{
    void* ms = MessageServer();
    ((Fn3)(*(void***)ms)[0x14 / 4])(ms, 0x695d2f5, 0, 0);
    ((GameEntry*)*(u32*)0x16a1344)->FUN_de53d0(0);
    for (void** p = (void**)(*(GameEntry**)0x16a1344)->mp1D8;
         p != (void**)(*(GameEntry**)0x16a1344)->mn1DC; ++p) {
        void* e = *p;
        ((Fn1)(*(void***)e)[0x30 / 4])(e, 0);
    }
    GameEntry* g = *(GameEntry**)0x16a1344;
    void* w = ((UI*)g->mp184)->FindWindowByID(0x10ed874);
    if (w != 0)
        ((Fn2)(*(void***)w)[0x7c / 4])(w, 1, 0);
    g = *(GameEntry**)0x16a1344;
    w = ((UI*)g->mp184)->FindWindowByID(0x10f33e0);
    if (w != 0)
        ((Fn2)(*(void***)w)[0x7c / 4])(w, 1, 1);
    g = *(GameEntry**)0x16a1344;
    w = ((Layout*)g->mLayout144)->FindWindowByID(0x615a5ff, 1);
    if (w != 0)
        ((Fn2)(*(void***)w)[0x7c / 4])(w, 1, 1);
    g = *(GameEntry**)0x16a1344;
    w = ((UI*)g->mp184)->FindWindowByID(0x10ed852);
    if (w != 0) {
        void* w2 = ((FnC)(*(void***)w)[0xc / 4])(w, 0x8ed27e7a);
        if (w2 != 0)
            ((Fn2)(*(void***)w2)[0x28 / 4])(w2, 4, 0);
    }
}

// @ 0x00de3be0
void __cdecl FUN_00de3be0(AnimObj* p)
{
    switch (p->mnA4) {
    case 1:
        ((ObjE3*)FUN_00b3d410())->Do(1, (u32)0x1654c01, 1);
        return;
    case 2:
        ((ObjE3*)FUN_00b3d410())->Do(1, (u32)0x1654c02, 1);
        return;
    case 4:
        ((ObjE3*)FUN_00b3d410())->Do(1, (u32)0x1654c04, 1);
        return;
    case 5:
        ((ObjE3*)FUN_00b3d410())->Do(1, (u32)0x1654c05, 1);
        return;
    }
}

// @ 0x00de3c70
void __cdecl FUN_00de3c70(void* param1, f32* param2, f32* param3)
{
    void* app = SP_App();
    void* x = ((FnPP)(*(void***)app)[0x58 / 4])(app);
    Vec3f local;
    ((CursorCtx*)x)->GetInfo(&local, param1);
    Vec4f area;
    SPUIHelpers_GetMainWindowArea(&area);
    const f32 one = *(f32*)0x1485720;
    *param2 = ((area.z - area.x) * (local.x + one)) * *(f32*)0x1471064;
    *param3 = (one - (local.y + one) * *(f32*)0x1471064) * (area.w - area.y);
}

// @ 0x00de3d00
bool __cdecl FUN_00de3d00(Layout* layout, u32 id, u32 which)
{
    void* img = SPUIHelpers_GetImageFromLayout(layout, which);
    if (img != 0) {
        void* win = layout->FindWindowByID(id, 1);
        if (win != 0)
            FUN_008068d0(win, img, 0);
    }
    return false;
}

// @ 0x00de3d40
void __cdecl FUN_00de3d40(Vec3i* out, Vec3iList* list, Vec3i* exclude)
{
    s32* base = (s32*)list->mpBegin;
    s32* end = (s32*)list->mpEnd;
    if (base != end) {
        if ((list->mpEnd - list->mpBegin) / 12 == 1) {
            s32 x = base[0];
            s32 y = base[1];
            s32 z = base[2];
            out->x = x;
            out->y = y;
            out->z = z;
            return;
        }
        s32* pCur;
        u32 i;
        do {
            i = ((RandomLCG*)0x1601760)->RandomUint32Uniform(
                    (u32)((list->mpEnd - list->mpBegin) / 12));
            pCur = (s32*)list->mpBegin;
        } while (pCur[i * 3] == exclude->x &&
                 pCur[i * 3 + 1] == exclude->y &&
                 pCur[i * 3 + 2] == exclude->z);
        s32 x = pCur[i * 3];
        s32 y = pCur[i * 3 + 1];
        s32 z = pCur[i * 3 + 2];
        out->x = x;
        out->y = y;
        out->z = z;
        return;
    }
    out->x = 0;
    out->y = 0;
    out->z = 0;
}

// @ 0x00de3e00
u32 __cdecl sGetWindowImage(void* w)
{
    if (w != 0) {
        void* a = ((FnPP)(*(void***)w)[0xa8 / 4])(w);
        if (a != 0) {
            void* b = ((FnC)(*(void***)a)[0xc / 4])(a, 0xef3c47cf);
            if (b != 0)
                return ((FnU)(*(void***)b)[0x18 / 4])(b);
        }
    }
    return 0;
}

// @ 0x00de3e40
void __cdecl FUN_00de3e40(u32 arg)
{
    void* prop = 0;
    void* pm = SP_PropertyManager();
    if (prop != 0) {
        void* old = prop;
        prop = 0;
        ((FnV)(*(void***)old)[4 / 4])(old);
    }
    char ok = ((FnQC)(*(void***)pm)[0x2c / 4])(pm, *(u32*)g_15a2df8, 0, &prop);
    if (ok) {
        WString16 ws;
        ws.mpBegin = (int)&gEmptyA_1667bac;
        ws.mpEnd = (int)&gEmptyA_1667bac;
        ws.mpCap = (int)&gEmptyB_1667bae;
        if (SP_GetPropertyAsString16(prop, arg, &ws)) {
            void* app = SP_AppSystem();
            ((Fn1)(*(void***)app)[0x5c / 4])(app, ws.mpBegin);
        }
        if ((s32)((ws.mpCap - ws.mpBegin) & 0xfffffffe) > 2 && ws.mpBegin != 0)
            op_del_array((void*)ws.mpBegin);
    }
    if (prop != 0)
        ((FnV)(*(void***)prop)[4 / 4])(prop);
}

// @ 0x00de3f00
bool __cdecl FUN_00de3f00(void* win, u32 res, void* image)
{
    if (win != 0) {
        void* a = ((FnPP)(*(void***)win)[0xa8 / 4])(win);
        if (a != 0) {
            void* b = ((FnC)(*(void***)a)[0xc / 4])(a, 0xef3c47cf);
            if (b != 0) {
                void* cur = image;
                if (cur != 0)
                    ((FnV)(*(void***)cur)[0 / 4])(cur);
                if (cur == 0)
                    SPUIHelpers_CreateImageFromResource2((void*)res, &cur, 0, -1, -1);
                if (cur != 0) {
                    ((Fn1)(*(void***)b)[0x14 / 4])(b, (u32)cur);
                    ((FnV)(*(void***)win)[0x90 / 4])(win);
                    if (cur != 0)
                        ((FnV)(*(void***)cur)[4 / 4])(cur);
                    return true;
                }
            }
        }
    }
    return false;
}

void __cdecl FUN_00de3fa0(void* out, u32 sel);  // 0x00de3fa0 (declaration-only alias for a caller that passes a slice string stand-in)

// @ 0x00de3fa0
EaString16* __cdecl FUN_00de3fa0(EaString16* out, u32 sel)
{
    CString20 str;
    switch (sel) {
    case 0:
        str = CString20(0x2b7a0311, 0x5b08702, 0);
        break;
    case 1:
        str = CString20(0x2b7a0311, 0x5b08703, 0);
        break;
    case 2:
        str = CString20(0x2b7a0311, 0x5b08704, 0);
        break;
    case 4:
        str = CString20(0x2b7a0311, 0x5b08705, 0);
        break;
    case 5:
        str = CString20(0x2b7a0311, 0x5b08706, 0);
        break;
    }
    const wchar_t* text = str.GetText();
    out->mpBegin = 0;
    out->mpEnd = 0;
    out->mpCap = 0;
    out->RangeInit(text);
    return out;
}

void __cdecl FUN_00de40e0(void* out, void* tm);  // 0x00de40e0 (declaration-only alias for a caller that passes a slice string stand-in)

// @ 0x00de40e0
EaString16* __cdecl FUN_00de40e0(EaString16* out, void* tm)
{
    DateTime dt;
    dt.Set(2);
    SetDateFromTm(tm, &dt);
    int a = dt.GetParameter(6);
    int b = dt.GetParameter(2);
    int c = dt.GetParameter(1);
    wchar_t buf[256];
    FUN_00881720(a, b, c, buf, 0xff, 0);
    out->mpBegin = 0;
    out->mpEnd = 0;
    out->mpCap = 0;
    out->RangeInit(buf);
    return out;
}

// @ 0x00de41b0
void __thiscall cGalaxyGameEntryImpl_s00de_41b0::FUN_00de41b0()
{
    if (mpGlobalUI184 == 0)
        return;
    tGUIObject* pWindow = mpGlobalUI184->FindWindowByID(0x469975e);
    if (pWindow == 0)
        return;

    float* pRect = pWindow->v38();
    float fOldW = pRect[2] - pRect[0];
    float fOldH = pRect[3] - pRect[1];
    FUN_00806e40(pWindow, 0, 0);
    float fNewW = pRect[2] - pRect[0];
    float fDelta = fNewW - fOldW;
    pWindow->v74(fOldW, fOldH);
    if (fDelta > 0.0f) {
        tGUIObject* pOther = mpGlobalUI184->FindWindowByID(0x10ed874);
        if (pOther != 0) {
            float* pR2 = pOther->v38();
            float afRect[4];
            afRect[0] = pR2[0] - fDelta * 0.5f;
            afRect[1] = pR2[1];
            afRect[2] = (pR2[2] - pR2[0]) + afRect[0] + fDelta;
            afRect[3] = pR2[3];
            pOther->v6c(afRect);
        }
        float fHalf = fDelta * -0.5f;
        FUN_00806ee0(mpGlobalUI184->FindWindowByID(0x447060a), fHalf);
        FUN_00806ee0(mpGlobalUI184->FindWindowByID(0x469975e), fHalf);
        FUN_00806ee0(mpGlobalUI184->FindWindowByID(0x43b72d0), fHalf);
        FUN_00806ee0(mpGlobalUI184->FindWindowByID(0x10f366d), fHalf);
    }
}

// @ 0x00de4360
uint32_t __thiscall cGalaxyGameEntryImpl_s00de_41b0::FUN_00de4360(uint32_t nID)
{
    if (nID == 0x2f009dd0)
        return ((uint32_t)this - 4 != 0) ? (uint32_t)this : 0;
    return 0;
}

// @ 0x00de4380
bool __cdecl FUN_00de4380()
{
    if (kGUI_PanelIDs_s00de_41b0->mb0c9 == false)
        return true;
    if (kGUI_PanelIDs_s00de_41b0->mn108 != 2)
        return true;
    return kGUI_PanelIDs_s00de_41b0->mb0c8 ? false : true;
}

// @ 0x00de43b0
void __thiscall cGalaxyGameEntryImpl_s00de_41b0::FUN_00de43b0(uint32_t nArg)
{
    m24c = 0;
    if (mp38 != 0)
        ((void(__thiscall*)(void*, uint32_t))VFN(mp38, 0x40))(mp38, nArg);
}

// @ 0x00de43d0
bool __thiscall cGalaxyGameEntryImpl_s00de_41b0::FUN_00de43d0(uint32_t a, uint32_t b)
{
    int32_t nCur = m108;
    if ((m10c == nCur || nCur == 0) && mp38 != 0)
        mp38->v1c(a, b);
    return false;
}

// @ 0x00de4410
bool __thiscall cGalaxyGameEntryImpl_s00de_41b0::FUN_00de4410(uint32_t a, uint32_t b)
{
    int32_t nCur = m108;
    if (m10c == nCur || nCur == 0) {
        if (m178 != 0)
            return true;
        if (mp38 != 0)
            mp38->v18(a, b);
    }
    return false;
}

// @ 0x00de4450
bool __thiscall cGalaxyGameEntryImpl_s00de_41b0::FUN_00de4450(uint32_t a, float fB, float fC, uint32_t d)
{
    if (m10c != m108)
        return false;
    if (mp38 != 0)
        mp38->v28(a, fB, fC, d);
    return true;
}

// @ 0x00de44a0
bool __thiscall cGalaxyGameEntryImpl_s00de_41b0::FUN_00de44a0(uint32_t a, float fB, float fC, uint32_t d)
{
    if (m10c != m108)
        return false;
    if (mp38 != 0)
        mp38->v24(a, fB, fC, d);
    return true;
}

// @ 0x00de44f0
bool __thiscall cGalaxyGameEntryImpl_s00de_41b0::FUN_00de44f0(float fA, float fB, uint32_t c)
{
    if (m10c != m108)
        return false;
    if (mp38 != 0)
        mp38->v20(fA, fB, c);
    int32_t nState = ((tTriggerMgr*)FUN_00b3d4d0())->mn2c;
    if (nState != 1 && nState != 2) {
        void* pMovie = FUN_0067cb10();
        if (((char(__thiscall*)(void*))VFN(pMovie, 0x14))(pMovie) == 0 && m1ec != 1)
            return false;
    }
    return true;
}

// @ 0x00de4570
void __thiscall cGalaxyGameEntryImpl_s00de_41b0::FUN_00de4570(uint32_t nArg)
{
    m16c = nArg;
    if (mp2c != 0)
        mp2c->v0(nArg);
}

// @ 0x00de4590
void __thiscall cGalaxyGameEntryImpl_s00de_41b0::FUN_00de4590(void* pObj, uint32_t nArg)
{
    m16c = 0;
    if (pObj != 0) {
        void* pQ = ((void*(__thiscall*)(void*))VFN(pObj, 0x10))(pObj);
        if (pQ != 0) {
            pQ = ((void*(__thiscall*)(void*))VFN(pObj, 0x10))(pObj);
            ((void(__thiscall*)(void*, void*))VFN(pQ, 0xe0))(pQ, pObj);
        }
    }
    if (mfc == 0) {
        mfc = 1;
        m100 = 2;
        return;
    }
    if (mp2c != 0)
        ((void(__thiscall*)(void*, void*, uint32_t))VFN(mp2c, 4))(mp2c, pObj, nArg);
}

// @ 0x00de4610
uint32_t __thiscall cGalaxyGameEntryImpl_s00de_41b0::FUN_00de4610()
{
    return ((tBannerList*)FUN_00b3d2a0())->FUN_00ba6d80(m7c);
}

// @ 0x00de4630
void __thiscall cGalaxyGameEntryImpl_s00de_41b0::FUN_00de4630()
{
    if (!mf0->FUN_00e205d0())
        return;
    char c = mef;
    if (c != 0) {
        med = 1;
    } else if (m1f1 == c) {
        mec = 1;
        me8 = 2;
        FUN_00809db0(&g_dw15a41d4, &g_dw15a3860);
    } else if (mef != 0) {
        med = 1;
    } else {
        _ReadWriteBarrier();
        if (m1f1 != 0)
            mee = 1;
    }
}

// @ 0x00de46e0
int __thiscall cGalaxyGameEntryImpl_s00de_41b0::FUN_00de46e0()
{
    if (m20.mpNext == &m20 && mp34 == 0)
        return 1;
    return 0;
}

// @ 0x00de4720
void __thiscall cGalaxyGameEntryImpl_s00de_41b0::OnActivate()
{
    FUN_00ddd970();
    if (m15c != 0) {
        g_bGalaxyActive = 1;
    } else {
        g_bGalaxyActive = 1;
        void* pEM = FUN_0067ddd0();
        void* pWorld = ((void*(__thiscall*)(void*, uint32_t, const char*))VFN(pEM, 0x4c))(pEM, 0x2dda976, "GGE effects world");
        AssignRef_s00de_41b0(&m15c, pWorld, 0, 4);
    }
    {
        void* pEM = FUN_0067ddd0();
        ((void(__thiscall*)(void*, int, int))VFN(pEM, 0x98))(pEM, 10, 1);
    }
    mcc = ((tBBoxOwner*)FUN_0067cad0())->FUN_0080dc90();
    ((tBBoxOwner*)FUN_0067cad0())->FUN_0080dc50(g_p16a0d18);
    if (m168 != 0)
        ((void(__thiscall*)(void*, int))VFN(m168, 0x0c))(m168, 1);
    ((tBoundObj*)FUN_00b3d230_s00de_41b0())->FUN_00b5cde0(0x780786fd);
    if (m198 == 0) {
        void* pApp = FUN_0067dd10();
        void* pQ = ((void*(__thiscall*)(void*))VFN(pApp, 0x50))(pApp);
        void* pR = ((void*(__thiscall*)(void*))VFN(pQ, 0x38))(pQ);
        AssignRef_s00de_41b0(&m198, pR, 0, 4);
    }
    ((tTriggerMgr*)FUN_00b3d4d0())->FUN_00ad7dc0();
    ((tTriggerMgr*)FUN_00b3d4d0())->FUN_00ad7d40();
    ((tTriggerMgr*)FUN_00b3d4d0())->FUN_00adffd0();
}

// @ 0x00de4850
void __thiscall cGalaxyGameEntryImpl_s00de_41b0::FUN_00de4850()
{
    C3 archive;
    tFile* pFile = (tFile*)FUN_00688fa0(L"GGEUserData.dat.tmp");
    if (pFile != 0) {
        pFile->v00();
        archive.ctorB(pFile, &g_dw1897c18, &g_dw1897c18, &g_dw1897c18);
        archive.FUN_00692ea0();
        archive.mSerializer.ctor(this, &g_dw15a38b8, 0x1a80d26);
        archive.mSerializer.Serialize(archive.mpSerialized);
        archive.FUN_00693900();
    }
    pFile->v2c();
    pFile->mStream.s1c();
    pFile->mStream.s08();
    FUN_006891f0(L"GGEUserData.dat.tmp", L"GGEUserData.dat");
    pFile->v04();
}

// @ 0x00de4910
void __thiscall cGalaxyGameEntryImpl_s00de_41b0::FUN_00de4910()
{
    uint32_t nKey = 0x61dd69b;
    switch (m108) {
    case 5:  nKey = 0x615b966; break;
    case 6:  return;
    case 0xd: nKey = 0x70d74e7; break;
    }

    uint32_t aIDs[5] = { 0x61dd69b, 0x615b966, 0x615b616, 0x70d74e7, 0x70d7509 };
    unsigned i = 0;
    cSPUILayout_s00de_41b0* pLayout = &mLayout144;
    for (; i < 3; i++) {
        tGUIObject* pWindow = pLayout->FindWindowByID(aIDs[i], 1);
        if (pWindow != 0) {
            tGUIObject* pWidget = pWindow->v0c(0x8ed27e7a);
            if (pWidget != 0) {
                pWidget->v28(4, nKey == aIDs[i]);
                pWidget->v28(2, 0);
                pWidget->v28(8, 0);
                pWidget->v28(0x10, 0);
            }
        }
    }
    if (FUN_00685520(2)) {
        for (i = 3; i < 5; i++) {
            tGUIObject* pWindow = pLayout->FindWindowByID(aIDs[i], 1);
            if (pWindow != 0) {
                tGUIObject* pWidget = pWindow->v0c(0x8ed27e7a);
                if (pWidget != 0) {
                    pWidget->v28(4, nKey == aIDs[i]);
                    pWidget->v28(2, 0);
                    pWidget->v28(8, 0);
                    pWidget->v28(0x10, 0);
                }
            }
        }
    }
}

// @ 0x00de4a70
void __thiscall cGalaxyGameEntryImpl_s00de_41b0::FUN_00de4a70()
{
    cDownloadDialog_s00de_41b0* pObj = (cDownloadDialog_s00de_41b0*)FUN_009512d0(0x28, 4, "UI/cDownloadDialog", FUN_009512c0());
    cDownloadDialog_s00de_41b0* pDlg = pObj ? pObj->ctor5c80() : 0;
    AssignRef_s00de_41b0((void**)&g_pDownloadDialogA, pDlg, 0, 4);
    if (g_pDownloadDialogA->FUN_00df5830(&mf0->mObj44))
        g_pDownloadDialogA->FUN_00df5540();
}

// @ 0x00de4b00
void __cdecl FUN_00de4b00()
{
    if (g_pDownloadDialogA != 0) {
        g_pDownloadDialogA->FUN_00df58f0();
        if (g_pDownloadDialogA != 0) {
            cDownloadDialog_s00de_41b0* pOld = g_pDownloadDialogA;
            g_pDownloadDialogA = 0;
            ((void(__thiscall*)(void*))VFN(pOld, 4))(pOld);
        }
    }
}

// @ 0x00de4b30
void __thiscall cGalaxyGameEntryImpl_s00de_41b0::FUN_00de4b30()
{
    cDownloadDialog_s00de_41b0* pObj = (cDownloadDialog_s00de_41b0*)FUN_009512d0(0x6c, 4, "UI/cDownloadDialog", FUN_009512c0());
    cDownloadDialog_s00de_41b0* pDlg = pObj ? pObj->ctor5940() : 0;
    AssignRef_s00de_41b0((void**)&g_pDownloadDialogB, pDlg, 0, 4);
    if (g_pDownloadDialogB->FUN_00df59c0(mf0))
        g_pDownloadDialogB->FUN_00df55b0(0);
}

// @ 0x00de4bc0
void __stdcall FUN_00de4bc0(char bFlag)
{
    if (g_pDownloadDialogB != 0) {
        g_pDownloadDialogB->FUN_00df5aa0(bFlag);
        if (g_pDownloadDialogB != 0) {
            cDownloadDialog_s00de_41b0* pOld = g_pDownloadDialogB;
            g_pDownloadDialogB = 0;
            ((void(__thiscall*)(void*))VFN(pOld, 4))(pOld);
        }
    }
}

// @ 0x00de4c00
bool __cdecl FUN_00de4c00()
{
    if (g_pDownloadDialogB != 0)
        return g_pDownloadDialogB->FUN_00df5420();
    return true;
}

// @ 0x00de4c20
void __thiscall cGalaxyGameEntryImpl_s00de_41b0::FUN_00de4c20(char bFlag)
{
    if (g_pDownloadDialogB == 0)
        return;
    g_pDownloadDialogB->FUN_00df5670(bFlag);
    if (bFlag != 0) {
        if (mf0->mn3c != 5)
            mf0->mn3c = 4;
    } else {
        if (mf0->mn3c != 2)
            mf0->mn3c = 6;
    }
    mf0->FUN_00e20860();
}

// @ 0x00de4c80
void __cdecl FUN_00de4c80(tArchive* pSer, tRBTree* pTree)
{
    uint32_t nCount = pTree->mCount;
    FUN_0093aa70(pSer->v20()->v18(), &nCount, 1, 0);
    tRBNode* pEnd = (tRBNode*)&pTree->mEnd;
    for (tRBNode* pNode = pTree->mBegin; pNode != pEnd; pNode = (tRBNode*)FUN_00921580(pNode)) {
        uint32_t nKey = pNode->mKey;
        FUN_0093aa70(pSer->v20()->v18(), &nKey, 1, 0);
        pSer->v1c();
    }
    pSer->v1c();
}

// @ 0x00de4d90
void __cdecl FUN_00de4d90(tArchive* pSer, tRBTree* pTree)
{
    uint32_t nCount = pTree->mCount;
    FUN_0093aa70(pSer->v20()->v18(), &nCount, 1, 0);
    tRBNode* pEnd = (tRBNode*)&pTree->mEnd;
    for (tRBNode* pNode = pTree->mBegin; pNode != pEnd; pNode = (tRBNode*)FUN_00921580(pNode)) {
        FUN_00ae2e40(pSer, &pNode->mKey);
        pSer->v1c();
        FUN_00ae2e40(pSer, &pNode->mValue);
        pSer->v1c();
    }
    pSer->v1c();
}

// @ 0x00de4e20
void __stdcall FUN_00de4e20(const tSimData* pSrc)
{
    tSimAlloc* pAlloc = (tSimAlloc*)FUN_00f473a0(0x28, "Simulator", 0, 0, 0x13ebb38, 0xd1);
    tSimData* pData = &pAlloc->mData;
    if (pData != 0)
        *pData = *pSrc;
}

// @ 0x00de4e70
int ReadIntPropertyPair(uint32 a1, uint32 a2)
{
    int ret = 0;
    int v1 = 0;
    PropertyListRef list;
    PropertyManager_s00de_41b0* mgr = GetPropertyManager();
    list.Reset();
    if (mgr->GetPropertyList(a1, a2, &list)) {
        Property* tmp;
        if (list.p && list.p->GetProperty(0x22e7847, &tmp)) {
            if (tmp->type == 9) {
                v1 = *tmp->GetInt();
            }
        }
        int v2 = 0;
        if (list.p && list.p->GetProperty(0x22e785c, &tmp)) {
            if (tmp->type == 9) {
                v2 = *tmp->GetInt();
            }
        }
        if (v1 > 0) {
            ret = (v2 <= 0) ? 4 : 2;
        } else if (v2 > 0) {
            ret = 1;
        }
    }
    if (list.p) {
        list.p->Release();
    }
    return ret;
}

// @ 0x00de4f50
void __cdecl FUN_00de4f50(tSimContainer* pObj, uint32_t nMask)
{
    tSimVec v = { 0, 0, 0 };
    pObj->Init(&v, 0, 0);
    for (int i = 0; i < v.end - v.begin; i++)
        pObj->Add(v.begin[i].m0, v.begin[i].m4, 0);
    pObj->Query(&v, 0x887c91bb);
    for (int i = 0; i < v.end - v.begin; i++) {
        uint64_t nKey = *(uint64_t*)&v.begin[i];
        uint32_t nHi = (uint32_t)(nKey >> 32);
        uint32_t nRes = FUN_00de4e70((uint32_t)nKey, nHi);
        if ((nMask & nRes) != 0)
            pObj->Insert((uint32_t)nKey, nHi);
    }
    pObj->Clear();
    if (v.begin != 0 && ((tSimBuffer*)v.begin - 1)->mnRefs != 0)
        FUN_00f47380(v.begin);
}

// @ 0x00de5040
void cGalaxyGameEntryImpl_s00de_5040::UpdateLoginButton(char param2)
{
    Wnd* pWin = ((cGlobalUI*)mpGlobalUI)->FindWindowByID(0x4810f47);
    cAuth* pAuth = PollenAuthManager();
    if (pWin == 0)
        return;
    if (pAuth == 0)
        return;
    if (param2 != 0 && pAuth->a22() && !pAuth->a09()) {
        WString16_s00de_5040 str;
        ConvertToString16(&str, pAuth->a14());
        pWin->w32(str.mpBegin);
        str.DeallocateSelf();
    } else {
        cString47a0 str;
        str.ctor();
        if (!pAuth->a22())
            str.Load(0xb7bcef68, 0x562d9e4, L"Register");
        else
            str.Load(0xb7bcef68, 0x662d9ea, L"Login");
        pWin->w32(str.GetText());
        str.dtor();
    }
    const RectF_s00de_5040* pRect = pWin->w14();
    float fOldWidth = pRect->right - pRect->left;
    AutoSizeWindowForText(pWin, 0, 0);
    float fNewWidth = pRect->right - pRect->left;
    float fWidth = *MaxPtr(&fNewWidth, &mf194);
    pWin->w29(fWidth, pRect->bottom - pRect->top);
    float fDelta = fWidth - fOldWidth;
    if (fDelta != 0.0f) {
        Wnd* pWin2 = ((cGlobalUI*)mpGlobalUI)->FindWindowByID(0x48102ca);
        if (pWin2 != 0) {
            const RectF_s00de_5040* pRect2 = pWin2->w14();
            pWin2->w29((pRect2->right - pRect2->left) + fDelta, pRect2->bottom - pRect2->top);
        }
        Wnd* pWin3 = ((cGlobalUI*)mpGlobalUI)->FindWindowByID(0x695ea48);
        if (pWin3 != 0) {
            const RectF_s00de_5040* pRect3 = pWin3->w14();
            pWin3->w29((pRect3->right - pRect3->left) + fDelta, pRect3->bottom - pRect3->top);
        }
    }
}

// @ 0x00de5260
void cGalaxyGameEntryImpl_s00de_5040::FUN_00de5260(void)
{
    if (mFlag1f5 == 0) {
        if (!FUN_00675250_0()->FUN_005c0dd0()) {
            for (RBNode* n = (RBNode*)mRbTree.root;
                 n != (RBNode*)((char*)this + 0x258);
                 n = (RBNode*)RBTreeIncrement(n)) {
                if (!FUN_00675250(n->id)->FUN_00675e80())
                    FUN_00675250(n->id)->AwardAchievement();
            }
        }
    }
}

// @ 0x00de52d0
void cGalaxyGameEntryImpl_s00de_5040::FUN_00de52d0(void)
{
    if (mBegin != mEnd) {
        _ReadWriteBarrier();
        mCurrentDword = ((int*)mEnd)[-1];
        _ReadWriteBarrier();
        mEnd -= 4;
        return;
    }
    mCurrentDword = 2;
}

// @ 0x00de5300
void cGalaxyGameEntryImpl_s00de_5040::FUN_00de5300(void)
{
    while (mBegin != mEnd)
        mEnd -= 4;
}

// @ 0x00de5330
void cGalaxyGameEntryImpl_s00de_5040::FUN_00de5330(char param2)
{
    if (param2 != 0) {
        cGalaxyHandle** field = (cGalaxyHandle**)&mpHandleA;
        if (mpHandleA != 0)
            return;
        cGalaxyHandle* h = *field;
        cGalaxyManager* m = (cGalaxyManager*)mpManager;
        if (h != 0) {
            *field = 0;
            h->hRelease();
        }
        if (m->mAdd(0x11e401e1, 0, (void**)field)) {
            (*field)->hStart(0);
            return;
        }
    } else {
        cGalaxyHandle* h = (cGalaxyHandle*)mpHandleA;
        if (h != 0) {
            h->hStop(0);
            cGalaxyHandle* h2 = (cGalaxyHandle*)mpHandleA;
            if (h2 != 0) {
                mpHandleA = 0;
                h2->hRelease();
                return;
            }
        }
    }
}

// @ 0x00de53d0
void cGalaxyGameEntryImpl_s00de_5040::FUN_00de53d0(char param2)
{
    if (param2 != 0) {
        cGalaxyHandle** field = (cGalaxyHandle**)&mpHandleB;
        if (mpHandleB != 0)
            return;
        cGalaxyManager* m = (cGalaxyManager*)mpManager;
        if (m == 0)
            return;
        cGalaxyHandle* h = *field;
        if (h != 0) {
            *field = 0;
            h->hRelease();
        }
        if (m->mAdd(0x4c4ba0a9, 0, (void**)field)) {
            (*field)->hStart(0);
            return;
        }
    } else {
        cGalaxyHandle* h = (cGalaxyHandle*)mpHandleB;
        if (h != 0) {
            h->hStop(0);
            cGalaxyHandle* h2 = (cGalaxyHandle*)mpHandleB;
            if (h2 != 0) {
                mpHandleB = 0;
                h2->hRelease();
                return;
            }
        }
    }
}

// @ 0x00de5470
void cGalaxyGameEntryImpl_s00de_5040::ShowGalaxy(char param2)
{
    if (param2 != 0) {
        if (mb100 == 0) {
            mHandle160.Create((cGalaxyManager*)mpManager, 0xef572ebb);
            if (mHandle160.mpHandle != 0)
                mHandle160.mpHandle->hStart(0);
            mHandle1a0.Create((cGalaxyManager*)mpManager, 0xf07cd744);
            if (mHandle1a0.mpHandle != 0) {
                mHandle1a0.mpHandle->hStart(0);
                XformMsg_s00de_5040 msg;
                msg.Init();
                msg.SetScale(0.4f);
                msg.pos += Vec3_s00de_5040(0.0f, 0.0f, -60.0f) * msg.rot;
                msg.flags |= 4;
                ++msg.count;
                mHandle1a0.mpHandle->h18(&msg);
            }
            mHandle16c.Create((cGalaxyManager*)mpManager, 0xedd3f703);
            mHandle170.Create((cGalaxyManager*)mpManager, 0xa97afd43);
        }
    } else {
        mHandle1a0.Stop(1);
        mHandle164.Stop(1);
        mHandle160.Stop(1);
        mHandle16c.Stop(1);
        mHandle170.Stop(1);
        FUN_00df5f40_s00de_5040()->FUN_00df9510();
    }
    mb100 = param2;
}

// @ 0x00de56f0
OutKey3* cGalaxyGameEntryImpl_s00de_5040::FUN_00de56f0(OutKey3& pOut, KeyNode* key)
{
    mRb38.Find((void*)&key, (void**)key);
    if (key != (KeyNode*)&mRb38.sentinel) {
        pOut.a = key->v1c;
        int mid = key->v20;
        int last = key->v24;
        _ReadWriteBarrier();
        pOut.b = mid;
        pOut.c = last;
        return &pOut;
    }
    pOut.a = 0;
    pOut.b = 0;
    pOut.c = 0;
    return &pOut;
}

extern char g_13f09b4[];   // 0x013f09b4 "Simulator"
extern char g_13ebb38[];   // 0x013ebb38 allocator name
// @ 0x00de57b0
RbIter57 cGalaxyGameEntryImpl_s00de_5040::FUN_00de57b0(RbNode57* parent, Key2* key, char flag)
{
    int left = (flag == 0 && parent != (RbNode57*)&mTree4.root
                && key->a >= parent->key.a) ? 1 : 0;
    RbNode57* node = (RbNode57*)EAllocNew(0x18, g_13f09b4, 0, 0, g_13ebb38, 0xd1);
    if (&node->key != 0)
        node->key = *key;
    RBTreeInsert57(node, parent, &mTree4.root, left);
    mTree4.count++;
    return RbIter57(node);
}

// @ 0x00de58c0
RecBC* FUN_00de58c0(RecBC* p, RecBC* q, RecBC* out)
{
    while (p != q) {
        FreeHeader(p->c);
        FreeHeader(p->b);
        FreeHeader(p->a);
        p++;
        out++;
    }
    return out;
}

// @ 0x00de5950
void cGalaxyGameEntryImpl_s00de_5040::FUN_00de5950(void)
{
    mLayout144.Init(IsWorldLayoutFlagSet(2) ? g_pNameA : g_pNameB, 0x40464100, 1, 0x5b598fa);

    const uint32_t ids[5] = { 0x615b966, 0x61dd69b, 0x615b616, 0x70d74e7, 0x70d7509 };
    uint32_t i;
    for (i = 0; i < 3; ++i)
        mLayout144.FindWindowByID(ids[i], 1)->w65(this != 0 ? (IWinProc*)&mTree4 : 0);

    if (IsWorldLayoutFlagSet(2)) {
        for (i = 3; i < 5; ++i)
            mLayout144.FindWindowByID(ids[i], 1)->w65(this != 0 ? (IWinProc*)&mTree4 : 0);

        mb271 = 1;
        cPropertyList_s00de_5040* pPrefs = g_pAppPreferences_s00de_5040;
        GetBoolProperty_s00de_5040(pPrefs, 0x8069a6c, (uint8_t*)&mb271);
        if (mb271 != 0) {
            cVariant_s00de_5040 value;
            value.SetBool(false);
            pPrefs->v14(0x8069a6c, &value);
            if ((value.mnFlags10 & 4) != 0)
                value.Destruct(0);
            SP_SaveResource(pPrefs, SP_GetSaveArea(0x11ac192, 0));
        }
    }

    FUN_00de4910();

    cGlobalUI* pNewUI = (cGlobalUI*)EAllocNew(0x68, "UI/GGE/GlobalUI", 0, 0, 0, 0);
    mpGlobalUI = (pNewUI != 0) ? pNewUI->Construct() : 0;
    mb103 = 1;

    ResKey key;
    key.mHash = FNV1_String16(0x811c9dc5, g_pUIKeyName, 1);
    key.mId = 0x510a95b;
    key.mGroup = 0x40464100;
    if (((cGlobalUI*)mpGlobalUI)->g08(&key)) {
        ((cGlobalUI*)mpGlobalUI)->FindWindowByID(0xffffffff)->w65((IWinProc*)&mTree4);
        Wnd* pOwner = ((cGlobalUI*)mpGlobalUI)->FindWindowByID(0x36c4a10);
        if (pOwner != 0) {
            void* pTarget = pOwner->w04();
            ((Wnd*)pTarget)->w56(pOwner);
        }
    }

    UpdateLoginButton(1);
    FUN_00de41b0();

    Wnd* pLogin = ((cGlobalUI*)mpGlobalUI)->FindWindowByID(0x4810f47);
    if (pLogin != 0) {
        const RectF_s00de_5040* pRect = pLogin->w14();
        mf194 = pRect->right - pRect->left;
    }

    Wnd* pConn = ((cGlobalUI*)mpGlobalUI)->FindWindowByID(0x10ed852);
    if (pConn != 0) {
        Wnd* pProcHost = (Wnd*)pConn->w03(0x8ed27e7a);
        if (pProcHost != 0) {
            NetworkActivityProc* pProc =
                (NetworkActivityProc*)EAllocNew(0x34, "UI/NetworkActivityProc", 0, 0, 0, 0);
            pProc = (pProc != 0) ? pProc->Ctor() : 0;
            ((Wnd*)pProcHost->w04())->w65(pProc);
        }
    }

    WindowManager_s00de_5040()->w4c(1, WindowManager_s00de_5040()->w04());

    if (!AppSystem_s00de_5040()->a54()) {
        if (((cGlobalUI*)mpGlobalUI)->FindWindowByID(0x3e30d88) != 0)
            ((cGlobalUI*)mpGlobalUI)->FindWindowByID(0x3e30d88)->w31(1, 0);
    }
}

// @ 0x00de5cb0
bool cGalaxyGameEntryImpl_s00de_5040::FUN_00de5cb0(unsigned int a)
{
    cAchievements* c = FUN_00675250(a);
    if (c->FUN_00675e80())
        return true;
    MapItr it;
    MapItr* out = mRbTree.find(it, a);
    void* found = out->node;
    _ReadWriteBarrier();
    return found != (void*)&mRbTree.sentinel;
}

// @ 0x00de5d00
void __stdcall FUN_00de5d00(uint32_t a1, uint32_t a2, uint32_t a3, const uint32_t* aIds, uint8_t aFlag, uint32_t a6, RefObj2* aRef)
{
    GuiHandle** ppHandle = &gGuiPanelMgr->mpHandle;
    if (*ppHandle != 0) {
        (*ppHandle)->h0c(0);
        if (*ppHandle != 0) {
            GuiHandle* pOld = *ppHandle;
            *ppHandle = 0;
            pOld->h04();
        }
    }
    PanelReq req;
    req.Ctor();
    req.m08 = a3;
    req.m38 = a2;
    req.m00 = a1;
    req.m18 = aIds[0];
    req.m0c = a6;
    req.m1c = aIds[1];
    req.m20 = aIds[2];
    req.m30 = 0xad0e52;
    req.m24 = aFlag;
    req.m10 = 1;
    RefObj2* pOld = req.mpRef;
    if (aRef != pOld) {
        if (aRef != 0)
            aRef->r04();
        req.mpRef = aRef;
        if (pOld != 0)
            pOld->r08();
    }
    gGuiPanelMgr->mbDirty = 1;
    LaunchPanel(&req);
    req.Dtor();
}

// @ 0x00de5df0
InsertResult8* HashTable34::FUN_00de5df0(InsertResult8* pOut, const uint32_t* pKey, uint32_t nReserved)
{
    (void)nReserved;
    const uint32_t nKey = *pKey;
    uint32_t nSlot = nKey % mBucketCount;
    HashNode8** ppBucket = &mppBuckets[nSlot];
    HashNode8* pNode = *ppBucket;
    while (pNode != 0) {
        if (pNode->mKey == nKey)
            break;
        pNode = pNode->mpNext;
    }
    if (pNode != 0) {
        pOut->mpNode = pNode;
        pOut->mpBucket = ppBucket;
        pOut->mbInserted = 0;
        return pOut;
    }
    RehashInfo info;
    mPolicy.GetNextRehashInfo(&info, mBucketCount, mSize, 1);
    HashNode8* pNew = (HashNode8*)EAllocNew(8, (const char*)0x13f09b4, 0, 0, (void*)0x13ebb38, 0xd1);
    if (pNew != 0)
        pNew->mKey = *pKey;
    pNew->mpNext = 0;
    if (info.mbNeedsRehash != 0) {
        nSlot = nKey % info.mCount;
        DoRehash(info.mCount);
    }
    pNew->mpNext = mppBuckets[nSlot];
    mppBuckets[nSlot] = pNew;
    mSize++;
    pOut->mpNode = pNew;
    pOut->mpBucket = &mppBuckets[nSlot];
    pOut->mbInserted = 1;
    return pOut;
}

// @ 0x00de5ee0
void __stdcall FUN_00de5ee0(RecBC* p, RecBC* q)
{
    for (; p < q; p++) {
        FreeHeader(p->c);
        FreeHeader(p->b);
        FreeHeader(p->a);
    }
}

// @ 0x00de60f0
cGameData::cGameData(unsigned int p2)
{
    z30 = 0; z34 = 0; z38 = 0; z3c = 0; z40 = 0; z44 = 0;
    z4c = 0; z50 = 0; z54 = 0; z58 = 0; z5c = 0; z60 = 0;
    z64 = 0; z68 = 0; z6c = 0; z70 = 0; z74 = 0; z78 = 0;
    FUN_00b26fb0(p2);
}

// @ 0x00de6170
void __fastcall FUN_00de6170(CGGEUserData* p)
{
    p->mpVtbl00 = (void*)0x147e0fc;
    p->mpVtbl04 = (void*)0x147e0e0;
    p->mpVtbl08 = (void*)0x147e0d0;
    p->mpVtbl0c = (void*)0x147e0c4;

    p->mTree254.DoNukeSubtree(p->mTree254.mpRoot);
    if (p->mpPtr250 != 0)
        ((CRefCounted*)p->mpPtr250)->Destroy();

    p->mBlock1d8.Destroy();

    if (p->mpRef1d4 != 0) p->mpRef1d4->Release();
    if (p->mpRef1d0 != 0) p->mpRef1d0->Release();
    if (p->mpRef1cc != 0) p->mpRef1cc->Release();
    if (p->mpRef1c8 != 0) p->mpRef1c8->Release();
    if (p->mpRef1c4 != 0) p->mpRef1c4->Release();
    if (p->mpRef1c0 != 0) p->mpRef1c0->Release();
    if (p->mpRef1bc != 0) p->mpRef1bc->Release();
    if (p->mpRef1b8 != 0) p->mpRef1b8->Release();
    if (p->mpRef1b4 != 0) p->mpRef1b4->Release();

    if (p->mpRef1b0 != 0) p->mpRef1b0->Release();
    if (p->mpRef1ac != 0) p->mpRef1ac->Release();
    if (p->mpRef1a8 != 0) p->mpRef1a8->Release();
    if (p->mpRef1a4 != 0) p->mpRef1a4->Release();
    if (p->mpRef1a0 != 0) p->mpRef1a0->Release();
    if (p->mpRef19c != 0) p->mpRef19c->Release();
    if (p->mpRef198 != 0) p->mpRef198->Release();

    if (p->mpRef174 != 0) p->mpRef174->Release();
    if (p->mpRef170 != 0) p->mpRef170->Release();
    if (p->mpRef16c != 0) p->mpRef16c->Release();
    if (p->mpRef168 != 0) p->mpRef168->Release();
    if (p->mpRef164 != 0) p->mpRef164->Release();
    if (p->mpRef160 != 0) p->mpRef160->Release();
    if (p->mpRef15c != 0) p->mpRef15c->Release();

    p->mLayout144.Destroy();
    p->mTree124.DoNukeSubtree(p->mTree124.mpRoot);

    if (p->mpHeap110 != 0 && ((CHeapCookie*)p->mpHeap110)[-1].mCookie != 0)
        EA_OperatorDelete(p->mpHeap110);

    // The path buffer is only owned when at least two wide characters were
    // allocated past the shared empty string.
    FreeStringBuffer(p->mPath.mpBegin, p->mPath.mpCap);

    p->mTreeAc.DoNukeSubtree(p->mTreeAc.mpRoot);
    p->mTree90.DoNukeSubtree(p->mTree90.mpRoot);
    p->mTree74.DoNukeSubtree(p->mTree74.mpRoot);
    p->mTree58.DoNukeSubtree(p->mTree58.mpRoot);
    p->mTree3c.DoNukeSubtree(p->mTree3c.mpRoot);

    if (p->mpHeap24 != 0 && ((CHeapCookie*)p->mpHeap24)[-1].mCookie != 0)
        EA_OperatorDelete(p->mpHeap24);

    if (p->mpHandler != 0) {
        void* handler = p->mpHandler;
        void* arg0 = p->mHandlerArg0;
        void* arg1 = p->mHandlerArg1;
        void* arg2 = p->mHandlerArg2;
        void* arg3 = p->mHandlerArg3;
        p->mpHandler = 0;
        EA_Messaging_RemoveHandler(handler, arg0, arg1, arg2, arg3);
    }

    p->mpVtbl04 = (void*)0x13eb938;
    p->mpVtbl08 = (void*)0x13eb394;
}

// @ 0x00de95a0
void cSPEditorUI::OnExitRequested()
{
    if (mpDialog->IsReadyToClose()) {
        mDialogState = 1;
        CalloutMessageBox(&gCalloutTarget, &kCalloutCloseConfirm);
    } else {
        MessageServer_s00de_8ad0()->SendMessage(0xce7afa41, 0, 0);
    }
    if (mLoginAction != 10)
        ShowDialog(10, 1);
}

// @ 0x00de9600
void cEditorMessageTarget::OnEditorMessageReceived(void* pMessage)
{
    IMessageReader* reader = CreateMessageReader();
    void* attachment = 0;
    if (!reader || !reader->ReadMessage(pMessage, &attachment, 0, 0, 0, 0))
        return;
    if (!attachment)
        return;

    void* source = reinterpret_cast<char*>(attachment) + 0x18;
    IEditorNode* node = CreateEditorNode(source);
    if (!node)
        return;

    node->SetAttachment(source);
    SetEditorNodeValue(node, *reinterpret_cast<void**>(reinterpret_cast<char*>(source) + 0x30));

    // The retail code copies three 12-byte payloads into the editor panels at
    // +38, +54 and +70; the first two come from the attachment/node, the last
    // is the message's own 12-byte payload.
    uint32_t* sourceValues = reinterpret_cast<uint32_t*>(source);
    uint32_t* messageValues = reinterpret_cast<uint32_t*>(pMessage);
    if (void* data = mSlot38.GetData(pMessage)) {
        uint32_t* out = reinterpret_cast<uint32_t*>(data);
        out[0] = sourceValues[0];
        out[1] = sourceValues[1];
        out[2] = sourceValues[2];
    }
    if (void* data = mSlot54.GetData(pMessage)) {
        uint32_t* out = reinterpret_cast<uint32_t*>(data);
        out[0] = sourceValues[0];
        out[1] = sourceValues[1];
        out[2] = sourceValues[2];
    }
    if (void* data = mSlot70.GetData(pMessage)) {
        uint32_t* out = reinterpret_cast<uint32_t*>(data);
        out[0] = messageValues[0];
        out[1] = messageValues[1];
        out[2] = messageValues[2];
    }

    ReleaseEditorNode(node);
    reinterpret_cast<IAttachment*>(attachment)->Release();
}

// @ 0x00de97a0
cPollenEntry* cEntryVector::MoveTail(cPollenEntry* first, cPollenEntry* last)
{
    // erase(first, last): slide the tail [last, end) down onto first, destroy the leftovers
    cPollenEntry* const newEnd = CopyConstructEntries(last, mpEnd, first);
    DestroyRange(newEnd, mpEnd);
    mpEnd -= last - first;
    return first;
}

// @ 0x00de97f0
void cEntryVector::insert(cPollenEntry* position, unsigned int count, const cPollenEntry& value)
{
    if (count == 0)
        return;

    const unsigned int index = (unsigned int)(position - mpBegin);
    const unsigned int oldSize = (unsigned int)(mpEnd - mpBegin);

    if (count > (unsigned int)(mpCapacity - mpEnd)) {
        unsigned int grow = oldSize * 2;
        if (oldSize == 0)
            grow = 1;
        const unsigned int newSize = grow > oldSize + count ? grow : oldSize + count;
        cPollenEntry* newData = newSize
            ? (cPollenEntry*)MessageAllocate(newSize * sizeof(cPollenEntry),
                                             (const char*)0x013f09b4, 0, 0,
                                             (const char*)0x013ebb38, 0xd1)
            : 0;
        if (oldSize)
            memmove(newData, mpBegin, oldSize * sizeof(cPollenEntry));
        if (mpBegin != 0 && *((unsigned int*)mpBegin - 1) != 0)
            MessageFree(mpBegin);
        mpBegin = newData;
        mpEnd = newData + oldSize;
        mpCapacity = newData + newSize;
    }

    position = mpBegin + index;
    memmove(position + count, position,
            (unsigned int)(mpEnd - position) * sizeof(cPollenEntry));
    for (unsigned int i = 0; i < count; ++i)
        position[i] = value;
    mpEnd += count;
}

// @ 0x00de9a00
bool cAssetBrowser::FUN_00de9a00(uint32_t nArg, cUIMessage* pMsg)
{
    if (this->mp174 != 0)
        return false;
    if (((cGameGlobalsRoot*)g_pGameGlobals)->mp1c->FUN_00ec4320() != 0)
        return false;
    if (this->mp34 != 0)
        this->mp34->v58(nArg, pMsg);
    if (pMsg->mn08 == 0x287259f6)
    {
    uint32_t nKey = pMsg->mp00->v1c();
    switch (nKey)
    {
    case 0x36c4a10:
        ((cUIObject*)FUN_00df5f40())->v60(0, 1);
        ((cUIObject*)FUN_0067dd20())->v28(1);
        return false;

    case 0x36850d4:
    case 0x43b72d0:
    case 0x447060a:
        ((cUIObject*)FUN_00df5f40())->v60(0, 1);
        return false;

    case 0x48102ca:
        KillSetiEffects(GetRecorderState(), 0x8cbe8393);
        ((cUIObject*)FUN_00df5f40())->v60(0, 1);
        if (AuthManager() != 0)
            ((cUIObject*)AuthManager())->v44();
        return false;

    case 0x4699799:
        KillSetiEffects(GetRecorderState(), 0xd094b811);
        ((cUIObject*)FUN_00df5f40())->v60(0, 1);
        Launch(0x55bdb30f, 0, 0);
        return false;

    case 0x469975e:
        KillSetiEffects(GetRecorderState(), 0x66be5739);
        ((cUIObject*)FUN_00df5f40())->v60(0, 1);
        FUN_00de3e40(0x509cf4cb);
        return false;

    case 0x595e0a8:
        ((cAssetBrowserHost*)((uint8_t*)this - 4))->FUN_00de52d0();
        return false;

    case 0x61dd69b:
    case 0x62d88e9:
        this->mn104 = 2;
        this->mn108 = 2;
        return false;

    case 0x615b966:
        KillSetiEffects(GetRecorderState(), 0x2ccf3a4d);
        this->mn104 = 5;
        this->mn108 = 5;
        return false;

    case 0x2f1cd64:
    case 0x615b616:
        if (this->mp34 != 0)
            this->mp34->FUN_00e00670(0x42, 0);
        return false;

    case 0x6709a13:
        KillSetiEffects(GetRecorderState(), 0xb7a63c50);
        ((cUIObject*)FUN_00df5f40())->v60(0, 1);
        this->mp194->FUN_00dde570();
        break;

    case 0x7bfb76e:
        KillSetiEffects(GetRecorderState(), 0xebadb118);
        this->mn108 = 2;
        return false;

    case 0x70d74e7:
        {
            if (!IsWorldLayoutFlagSet(2))
                return false;

            cPropertyList* pPrefs = (cPropertyList*)g_pAppPreferences;
            uint8_t bEnabled = 0;
            GetBoolProperty(pPrefs, 0x80d7de1, &bEnabled);
            if (bEnabled == 0)
            {
                tIWindow* pWindow = this->mLayout140.FindWindowByID(0x806a310, 1);
                if (pWindow != 0)
                    pWindow->v7c(1, 0);

                uint32_t nResource = 1;
                cVariant variant;
                variant.FUN_005dd750(&nResource);
                pPrefs->v14(0x80d7de1, &variant);
                if ((variant.mnFlags10 & 4) != 0)
                    variant.Destruct(0);
                SP_SaveResource(pPrefs, SP_GetSaveArea(0x11ac192, 0));
            }
            KillSetiEffects(GetRecorderState(), 0x6cd343dc);
            this->mn108 = 0xd;
            this->mn104 = 0xd;
        }
        return false;
    }
    }
    return false;
}

// @ 0x00de9dc0
void cRecordMap::FUN_00de9dc0(const void* pKey)
{
    void* pFound;
    this->mTree38.Find(&pFound, pKey);
    void* pNode = pFound;
    if (pNode == (void*)&this->mTree38.mp04)
    {
        this->FUN_00de9600(pKey);
        pNode = *this->mTree38.Find(&pFound, pKey);
        if (pNode == (void*)&this->mTree38.mp04)
            return;
    }
    this->FUN_00de6f20((uint32_t)pKey, (uint8_t*)pNode + 0x1c);
}

// @ 0x00de9e20
void cGameInfoVector::FUN_00de9e20(uint32_t nCount)
{
    int32_t nHave = (int32_t)(mpEnd - mpBegin) / 0xbc;
    if (nCount > nHave)
    {
        FUN_00de97f0(this->mpEnd, nCount - (int32_t)(this->mpEnd - this->mpBegin) / 0xbc,
                     cByteVector());
    }
    else
    {
        FUN_00de97a0(mpBegin + nCount * 0xbc, mpEnd);
    }
}

// @ 0x00de9ec0
void __cdecl FUN_00de9ec0()
{
    if (g_nSavedGameLimit == 0)
        return;

    ((cSavedGameEntry*)FUN_00dd9190(2))->FUN_00ddc820();
    uint32_t nCount = ((cRecorderUI*)FUN_00df5f40())->FUN_00df66e0();

    cGameInfoVector games;
    games.mpBegin = 0;
    games.mpEnd = 0;
    games.mpCapacity = 0;
    games.FUN_00de9e20(nCount);

    uint8_t* pBegin = games.mpBegin;
    ((cSaveGameUI*)FUN_00df5f40())->GetSavedGames(pBegin, nCount);

    uint32_t nLoaded = (uint32_t)((int32_t)(games.mpEnd - pBegin) / 0xbc);
    uint32_t nWalk = MinRef(nLoaded, g_nSavedGameLimit);
    cGameInfoKey* pKey = &((cGameInfo_s00de_9a00*)pBegin)->mKey7c;
    for (uint32_t i = 0; i < nWalk; ++i)
    {
        if (pKey->mn2c != 0)
        {
            cStarManager* pStars = (cStarManager*)StarManager(pKey->mn00);
            ((cSavedGameEntry*)FUN_00dd9190(pStars->FUN_00ba6d80()))->FUN_00ddb9f0();
        }
        pKey = (cGameInfoKey*)((uint8_t*)pKey + 0xbc);
    }

    games.FUN_00de5ee0(pBegin, games.mpEnd);
    if (pBegin != 0 && *(int32_t*)(pBegin - 4) != 0)
        operator_delete_array(pBegin);
}

// @ 0x00de9fc0
void cRecordMap::FUN_00de9fc0()
{
    cConstraintList list;
    list.mpBegin = 0;
    list.mpEnd = 0;
    list.mpCapacity = 0;

    AddConstraint(&list, 0x2dd90af, 0x366a930d);
    AddConstraint(&list, 0x3cc89b1, 0x913b23be);
    AddConstraint(&list, 0x54a32960, 1);

    cKeyList keys;
    keys.mpBegin = 0;
    keys.mpEnd = 0;
    keys.mpCapacity = 0;
    ((cUIObject*)ObjectTemplateDB_s00de_9a00())->v38(&keys, &list);

    uint8_t* pKey = (uint8_t*)keys.mpBegin;
    int32_t nCount = (int32_t)((uint8_t*)keys.mpEnd - (uint8_t*)keys.mpBegin) / 0xc;
    for (int32_t i = 0; i < nCount; ++i)
    {
        tResourceKey key;
        key.mn00 = *(uint32_t*)(pKey + 0);
        key.mn04 = *(uint32_t*)(pKey + 4);
        key.mn08 = *(uint32_t*)(pKey + 8);

        void* pFound;
        void** ppSlot = this->mTree38.Find(&pFound, &key);
        if (*ppSlot == (void*)&this->mTree38.mp04)
        {
            this->FUN_00de9600(&key);
            nCount = (int32_t)((uint8_t*)keys.mpEnd - (uint8_t*)keys.mpBegin) / 0xc;
        }
        pKey += 0xc;
    }

    this->FUN_00de7010();

    if (keys.mpBegin != 0 && *(int32_t*)((uint8_t*)keys.mpBegin - 4) != 0)
        operator_delete_array(keys.mpBegin);
    list.DoDestroyValues(list.mpBegin, list.mpEnd);
    if (list.mpBegin != 0 && *(int32_t*)((uint8_t*)list.mpBegin - 4) != 0)
        operator_delete_array(list.mpBegin);
}

// @ 0x00dea200
bool cGalaxyGameEntryImpl_s00de_9a00::FUN_00dea200()
{
    this->mb0c9 = 1;
    this->OnActivate();
    this->FUN_00de5950();
    this->ShowGalaxy(1);
    this->mb140 = 0;
    this->mb1f6 = 1;

    uint8_t* pStars = (uint8_t*)FUN_00b3d360();
    uint8_t* pRoot = pStars + 0x20;
    if ((*(uint32_t*)pRoot != (uint32_t)pRoot || *(uint32_t*)(pStars + 0x34) != 0) &&
        g_bGalaxyIntroA != 0 && g_bGalaxyIntroB != 0)
    {
        ((cEffectHandle*)FUN_00b3d410(1, 0x2ccd1d2, 0))->FUN_00e3e350();
    }

    ((cGameTime*)GameTimeManager())->FUN_00b32110();
    ((cGameInput*)GameInputManager())->mn110 = 0;
    this->mRecords3c.FUN_00de9fc0();

    if (this->mn108 == 1)
        this->mn10c = 2;

    void* pHandler = &this->mHandler08;
    ((cUIObject*)MessageServer())->v20(pHandler, 0x4360e14);
    ((cUIObject*)MessageServer())->v20(pHandler, 0x56bbd7f);
    ((cUIObject*)MessageServer())->v20(pHandler, 0x44db12e);
    ((cUIObject*)MessageServer())->v20(pHandler, 0x5bd6378);
    ((cUIObject*)MessageServer())->v20(pHandler, 0x5dd52c7);
    ((cUIObject*)MessageServer())->v20(pHandler, 0x6203fdc);
    ((cUIObject*)MessageServer())->v20(pHandler, 0x4519b5f);
    ((cUIObject*)MessageServer())->v20(pHandler, 0x625d27d);
    ((cUIObject*)MessageServer())->v20(pHandler, 0x67c75bd6);
    ((cUIObject*)MessageServer())->v20(pHandler, 0x634297ad);
    ((cUIObject*)MessageServer())->v20(pHandler, 0x275a9c8c);
    ((cUIObject*)MessageServer())->v20(pHandler, 0xeda117de);
    ((cUIObject*)MessageServer())->v20(pHandler, 0x8085c4c);

    cIEffectsWorld* pWorld = this->mp38;
    if (this->mb24c != 0)
    {
        if (pWorld != 0)
            pWorld->v48(this->mp250);
        this->mb24c = 0;
        _ReadWriteBarrier();
        tRefObj* pEffect = this->mp250;
        if (pEffect != 0)
        {
            this->mp250 = 0;
            pEffect->v08();
        }
        this->mb24d = 0;
    }
    else
    {
        if (pWorld != 0)
            pWorld->v4c();
    }

    uint8_t* pCur = (uint8_t*)this->mp12c;
    uint8_t* pEnd = (uint8_t*)&this->mp128;
    for (; pCur != pEnd; pCur = (uint8_t*)RBTreeIncrement(pCur))
        ((cVisitNode*)pCur)->mp14->v38();

    return true;
}

// @ 0x00dea420
void cGalaxyGameEntryImpl_s00de_9a00::FUN_00dea420()
{
    cUIObject* pCheats = (cUIObject*)CheatManager();
    if (pCheats != 0)
        pCheats->v4c(1);

    cUIObject* pServer = (cUIObject*)MessageServer();
    if (pServer != 0)
    {
        pServer->v2c(this != 0 ? (void*)&this->mHandler08 : 0, 0x67c75bd6, -9999);
        pServer->v2c(this != 0 ? (void*)&this->mHandler08 : 0, 0x634297ad, -9999);
        pServer->v2c(this != 0 ? (void*)&this->mHandler08 : 0, 0x275a9c8c, -9999);
        pServer->v2c(this != 0 ? (void*)&this->mHandler08 : 0, 0xeda117de, -9999);
        pServer->v2c(this != 0 ? (void*)&this->mHandler08 : 0, 0x8085c4c, -9999);
    }

    ((cPanelIDs_s00de_9a00*)g_pPanelIDs)->mLayout144.SetVisibility(1);
}

// @ 0x00dea500
cPaintSystem::cPaintSystem()
{
    _ReadWriteBarrier();
    this->mp14 = 0;
    this->mn28 = -1;
}

// @ 0x00dea560
void cPaintSystem::FUN_00dea560()
{
    this->mb24 = 6;
    this->mf18 = 0.0f;

    cPanelIDs_s00de_9a00* pPanels = (cPanelIDs_s00de_9a00*)g_pPanelIDs;
    if (pPanels->mb1f3 != 0)
    {
        pPanels->mb1f3 = 0;
        ((cUIObject*)MessageServer())->v18(0x66f6b6f, 0, 0, 0);
    }

    if (this->mp14 != 0)
    {
        tIWindow* pA = ((cSPUILayout_s00de_9a00*)this->mp14)->FindWindowByID(0x6776fe0, 1);
        pA->v7c(1, 0);
        tIWindow* pB = ((cSPUILayout_s00de_9a00*)this->mp14)->FindWindowByID(0x6776fe1, 1);
        pB->v7c(1, 0);
        ((cSPUILayout_s00de_9a00*)this->mp14)->Shutdown(1);

        tRefObj* pOld = (tRefObj*)this->mp14;
        if (pOld != 0)
        {
            this->mp14 = 0;
            pOld->v08();
        }
    }
}

// @ 0x00dea600
void cPaintSystem::FUN_00dea600(uint32_t nId, uint32_t nData)
{
    if ((g_gameFlags[nId >> 5] >> (nId & 0x1f) & 1) != 0)
        return;

    if (nId == 0x1b)
    {
        if (((cUIObject*)AppSystem())->v54() == 0 && ((cPanelIDs_s00de_9a00*)g_pPanelIDs)->mb1f4 != 0)
        {
            this->FUN_00e00650(nId, nData);
            return;
        }
        if (((cMovieSystem_s00de_9a00*)MovieSystem())->v24() != 0)
        {
            if (((cMovieSystem_s00de_9a00*)MovieSystem())->v14() == 0)
            {
                if (((cUIObject*)AppSystem())->v54() != 0)
                {
                    this->FUN_00dea560();
                    ((cPanelIDs_s00de_9a00*)g_pPanelIDs)->mn1ec = 6;
                    ((cUIObject*)MessageServer())->v18(0x66f8f25, 0, 0, 0);
                    this->FUN_00e00650(nId, nData);
                    return;
                }
                this->mb24 = 0;
                this->mf18 = ((cPanelIDs_s00de_9a00*)g_pPanelIDs)->mf20c;
                this->mf1c = ((cPanelIDs_s00de_9a00*)g_pPanelIDs)->mf208;
                this->mf20 = 0.0f;
                ((cPanelIDs_s00de_9a00*)g_pPanelIDs)->mb1f2 = 1;
            }
        }
    }
    this->FUN_00e00650(nId, nData);
}

// @ 0x00dea730
bool cWatcherBase::FUN_00dea730()
{
    cSavedGameRecord* pRecord = (cSavedGameRecord*)this->mp04;
    if (pRecord != 0)
    {
        int32_t nStamp = pRecord->mp30 != 0 ? pRecord->mp30->GetModificationCount() : 0;
        if (this->mn0c != (int32_t)(pRecord->mn34 + nStamp))
        {
            int32_t nNew = pRecord->mp30 != 0 ? pRecord->mp30->GetModificationCount() : 0;
            this->mn0c = pRecord->mn34 + nNew;

            void* pValue;
            if (((cProperty*)pRecord)->v24(this->mn08, &pValue))
            {
                uint8_t cValue = *((cValueObject*)pValue)->FUN_004e42a0();
                if (this->mb00 != cValue)
                {
                    this->mb00 = cValue;
                    return true;
                }
            }
        }
    }
    return false;
}

// @ 0x00dea7b0
void cWatcherBase::FUN_00dea7b0(cProperty* pProperty)
{
    cVariantValue* pValue;
    if (pProperty->v24(this->mn08, (void**)&pValue))
    {
        uint16_t nType = pValue->mn12;
        uint8_t* pByte;
        if (nType == 1 || nType == 0x10)
        {
            if ((pValue->mb10 & 0x30) != 0)
                pByte = pValue->mp00;
            else
                pByte = nType != 0 ? (uint8_t*)pValue : (uint8_t*)0;
        }
        else
        {
            pByte = &g_cDefaultChar;
        }
        this->mb00 = *pByte;
    }

    cSavedGameRecord* pRecord = (cSavedGameRecord*)this->mp04;
    this->mn0c = pRecord->mn34 + (pRecord->mp30 != 0 ? pRecord->mp30->GetModificationCount() : 0);
}

// @ 0x00dea870
bool AppMode_OnMessage(uint8_t* self, uint32_t msgID, uint32_t msgType, int param)
{
    (void)msgType;
    switch (msgID) {
    case 0x61d72de:
        PI(0x1ec) = 3;
        return true;
    case 0x44f1189:
        if (FUN_00b3d4d0() == 0)
            goto ret_true;
        if ((uint32_t)FUN_00ad7db0() != *(uint32_t*)((char*)param + 8))
            goto ret_true;
        ((ModalShim*)FUN_00b3d4d0())->SetModal(1);
        PI(0x1ec) = 6;
        ((cMessageServer_s00de_a870*)FUN_0067dcc0())->SendMessage(0x66f8f25, 0, 0, 0);
        if (PIP(0x1ac) != 0) {
            ((cIVisualEffect*)PIP(0x1ac))->Tick(1);
            if (PIP(0x1ac) != 0) {
                cIVisualEffect* e = (cIVisualEffect*)PIP(0x1ac);
                PIP(0x1ac) = 0;
                e->Release();
            }
        }
        goto ret_true;
    case 0x49731ad:
        if (FUN_00b3d4d0() == 0)
            goto ret_true;
        if (PI(0x1ec) == 3) {
            PI(0x1ec) = 4;
            goto ret_true;
        }
        PI(0x1ec) = 5;
        if (PIP(0x15c) != 0) {
            cEffectsWorldSub* w = (cEffectsWorldSub*)PIP(0x15c);
            if (w->Find(0xc19878cd, PIP(0x1ac), 0, 0, 0, 0)) {
                ((cIVisualEffect*)PIP(0x1ac))->Tick(0);
                ((cIVisualEffect*)PIP(0x1ac))->Release();
            }
        }
        FUN_00ae0930();
        goto ret_true;
    case 0x66f6b6f:
        PIB(0x1f4) = 0;
        ((ModalShim*)FUN_00b3d4d0())->SetModal(1);
        PI(0x1ec) = 6;
        ((cMessageServer_s00de_a870*)FUN_0067dcc0())->SendMessage(0x66f8f25, 0, 0, 0);
        goto ret_true;
    case 0x67c75bd6:
        *(bool*)(self + 0xe) = (*(uint32_t*)((char*)param + 8) == 1);
        return true;
    case 0x275a9c8c:
        *(bool*)(self + 0x10) = (*(uint32_t*)((char*)param + 8) == 1);
        return true;
    case 0x634297ad:
        *(bool*)(self + 0xf) = (*(uint32_t*)((char*)param + 8) == 1);
        return true;
    case 0xeda117de:
        *(uint32_t*)(self + 0x28) = *(uint32_t*)((char*)param + 8);
        return true;
    case 0x8085c4c:
        *(bool*)(self + 0x12) = true;
        return true;
    default:
        return false;
    }
ret_true:
    return true;
}

// @ 0x00deaad0
void cGalaxyGameEntryImpl_PlayOpeningMovie(cGalaxyGameEntryImpl_s00de_a870* self)
{
    (void)self;
    cRandomLC rng;
    rng.SetSeed(0xffffffff);
    cFxObj* pFx = 0;
    cFxMan* pMgr = (cFxMan*)FUN_0067de30();
    if (pFx != 0) {
        cFxObj* dead = pFx;
        pFx = 0;
        dead->Release();
    }
    if (!pMgr->Register(0, 0xeadc458c, (void**)&pFx))
        goto release;
    {
        float fVal;
        cFxObj* pObj = pFx;
        fVal = 0.0f;
        if (pObj != 0) {
            void* pProp = 0;
            if (pObj->GetProp(0x435ba69, (void**)&pProp)) {
                if (*(uint16_t*)((char*)pProp + 0x12) == 0xd)
                    fVal = *(float*)FUN_0041ea70(pProp);
            }
        }
        MovieDesc desc;
        desc.mId = 0;
        desc.mF0 = 0.0f;
        desc.mF1 = 0.0f;
        desc.mF2 = 0.0f;
        desc.mF3 = 0.0f;
        desc.mB0 = 0;
        desc.mB1 = 1;
        uint32_t r = rng.RandomUint32Uniform(0xffffffff);
        desc.mF0 = fVal;
        desc.mF1 = 4.0f;
        *(uint32_t*)((char*)pFx + r * 12 + 4) = 0x376840d7;
        ((cMovieSystem*)FUN_0067cb10())->PlayMovie((void*)((char*)pFx + r * 12), &desc);
    }
release:
    if (pFx != 0)
        pFx->Release();
}

// @ 0x00deac20
void __fastcall FUN_00deac20(cGalaxyGameEntryImpl_s00de_a870* self)
{
    AppPropsList* pProps = *(AppPropsList**)0x15fd918;
    FlagPair local;
    AppPropsList* pKeep = pProps;
    local.mFlag = 0;
    local.mp04 = pProps;
    if (pProps != 0)
        pProps->vf0();
    local.mId08 = 0xc14680ef;
    local.mId0c = 0;
    if (pKeep != 0)
        FUN_00dea7b0(&local, pKeep);
    FUN_00dea730();
    if (local.mFlag) {
        cGalaxyGameEntryImpl_PlayOpeningMovie(self);
        PI(0x1ec) = 2;
    } else {
        FUN_00dea560();
        PI(0x1ec) = 6;
        ((cMessageServer_s00de_a870*)FUN_0067dcc0())->SendMessage(0x66f8f25, 0, 0, 0);
    }
    if (pKeep != 0) {
        AppPropsList* p = *(AppPropsList**)&local.mp04;
        if (p != 0) {
            p->Release();
        }
    }
}

// @ 0x00deacd0
void __fastcall FUN_00deacd0(cGalaxyGameEntryImpl_s00de_a870* self, float dt)
{
    cSPUILayout_s00de_a870* ui = self->mp14;
    if (ui == 0)
        return;
    switch (PI(0x200)) {
    case 1: {
        uint8_t step;
        if (FUN_00805180())
            self->mf1c = self->mf1c - dt;
        if (self->mf1c > 0.0f)
            return;
        if (!PIB(0x1f2))
            return;
        PIB(0x1f2) = 0;
        {
            IWindow* w = ui->FindWindowByID(
                *(uint32_t*)((char*)g_kPanelIDs + (self->mb24 + 0x2b) * 12), 1);
            if (w != 0)
                w->PlayAnim(1, self->mb24 != 2);
        }
        if (self->mb24 == 0) {
            IWindow* w = ui->FindWindowByID(0x67763d0, 1);
            w->PlayAnim(1, 1);
        } else if (self->mb24 == 2) {
            IWindow* w = ui->FindWindowByID(0x67763d0, 1);
            w->PlayAnim(1, 0);
        }
        if (self->mb24 == 5)
            PIB(0x1f4) = 1;
        PI(0x200) = 2;
        return;
    }
    case 2: {
        uint8_t step;
        if (PIB(0x1f4)) {
            if (!((cMovieSystem*)FUN_0067cb10())->IsMoviePlaying()) {
                FUN_00dea560();
                PI(0x200) = 0;
            }
        }
        if (FUN_00805180())
            self->mf18 = self->mf18 - dt;
        if (self->mf18 > 0.0f || self->mf18 == 0.0f)
            break;
        step = self->mb24;
        if (step >= 6)
            break;
        if (step != 0) {
            IWindow* w = ui->FindWindowByID(
                *(uint32_t*)((char*)g_kPanelIDs + (step + 0x2b) * 12), 1);
            if (w != 0)
                w->PlayAnim(1, 0);
        }
        if (self->mb24 == 2) {
            self->mb24 = 6;
            PIB(0x1f3) = 1;
        } else {
            self->mb24 = step + 1;
        }
        PI(0x200) = 3;
        return;
    }
    case 3:
        if (self->mf20 > 0.0f && FUN_00805180()) {
            self->mf20 = self->mf20 - dt;
            return;
        }
        PI(0x200) = 4;
        return;
    case 4: {
        uint8_t step;
        if (self->mb24 == 6) {
            if (!((cMovieSystem*)FUN_0067cb10())->IsMoviePlaying()) {
                FUN_00dea560();
                PI(0x200) = 0;
                return;
            }
        }
        step = self->mb24;
        if (step >= 6)
            return;
        self->mf18 = *(float*)((char*)g_kPanelIDs + step * 12 + 0x20c);
        self->mf1c = *(float*)((char*)g_kPanelIDs + step * 12 + 0x208);
        PIB(0x1f2) = 1;
        if (step == 1)
            self->mf20 = 1.0f;
        if (step == 5) {
            IWindow* w = ui->FindWindowByID(0x5bfe3a8, 1);
            if (w != 0)
                w->PlayAnim(1, 0);
            FUN_00deac20(self);
        }
        PI(0x200) = 1;
        return;
    }
    default:
        return;
    }
}

// @ 0x00deafc0
void __fastcall FUN_00deafc0(cGalaxyGameEntryImpl_s00de_a870* self, float dt)
{
    uint32_t oldState;
    FUN_00deacd0(self, dt);
    oldState = PI(0x1ec);
    if (!((cMovieSystem*)FUN_0067cb10())->IsMoviePlaying() && oldState == 6) {
        if (!self->mb11) {
            if (FUN_0060b3c0() == 0) {
                DBCheck* p = (DBCheck*)EAAllocate(0x18, "UI/DBCheck", 0, 0, 0, 0);
                if (p != 0)
                    p->DBCheck::DBCheck();
                p->Prepare();
                FUN_0060b3e0(p);
            }
            ((DBCheck*)FUN_0060b3c0())->Show();
            self->mb11 = 1;
        } else if (self->mb12 && !self->mb13) {
            FUN_00de95a0((void*)g_kPanelIDs);
            self->mb13 = 1;
        }
    }
    {
        void* mgr = FUN_00b3d4d0();
        int ms = (int)(dt * 1000.0f);
        typedef void (__thiscall *FNFire)(void*, int, int);
        ((FNFire)*(void**)(*(char**)mgr + 0x38))((char*)mgr + 4, ms, ms);
    }
}

// @ 0x00deb0b0
void __fastcall FUN_00deb0b0(cGalaxyGameEntryImpl_s00de_a870* self)
{
    // kGUI+0x204..0x248 : 6 x { panelID, float, float }
    *(uint32_t*)((char*)g_kPanelIDs + 0x208) = 0;
    *(uint32_t*)((char*)g_kPanelIDs + 0x20c) = 0x3dcccccd;
    *(uint32_t*)((char*)g_kPanelIDs + 0x204) = 0x670a3f8;
    *(uint32_t*)((char*)g_kPanelIDs + 0x214) = 0;
    *(uint32_t*)((char*)g_kPanelIDs + 0x218) = 0x40833333;
    *(uint32_t*)((char*)g_kPanelIDs + 0x210) = 0x5b82b38;
    *(uint32_t*)((char*)g_kPanelIDs + 0x220) = 0;
    *(uint32_t*)((char*)g_kPanelIDs + 0x224) = 0x3f000000;
    *(uint32_t*)((char*)g_kPanelIDs + 0x21c) = 0x670a3f8;
    *(uint32_t*)((char*)g_kPanelIDs + 0x22c) = 0;
    *(uint32_t*)((char*)g_kPanelIDs + 0x230) = 0x40900000;
    *(uint32_t*)((char*)g_kPanelIDs + 0x228) = 0x5bfdc38;
    *(uint32_t*)((char*)g_kPanelIDs + 0x238) = 0;
    *(uint32_t*)((char*)g_kPanelIDs + 0x23c) = 0x40900000;
    *(uint32_t*)((char*)g_kPanelIDs + 0x234) = 0x5bfdc68;
    *(uint32_t*)((char*)g_kPanelIDs + 0x244) = 0x41280000;
    *(uint32_t*)((char*)g_kPanelIDs + 0x248) = 0x40900000;
    *(uint32_t*)((char*)g_kPanelIDs + 0x240) = 0x66f3c30;

    if (FUN_00e01380())
        ((cSPUIGlobalUI_s00de_a870*)PIP(0x184))->SetVisibility(false);

    cSPUILayout_s00de_a870* pNew = (cSPUILayout_s00de_a870*)EAAllocate(0x18, "UI/SporeTitleSeq", 0, 0, 0, 0);
    if (pNew != 0)
        pNew = (cSPUILayout_s00de_a870*)FUN_00810000_s00de_a870(pNew);
    cSPUILayout_s00de_a870* pOld = self->mp14;
    if (pNew != pOld) {
        if (pNew != 0)
            ((AppPropsList*)pNew)->vf0();
        self->mp14 = pNew;
        if (pOld != 0)
            ((AppPropsList*)pOld)->Release();
    }
    if (self->mp14 != 0)
        self->mp14->Init(L"SporeTitleSeq", 0x40464100, 1, (char)0x5b598fa, 0);

    void* pLoc = FUN_0067de40();
    if (FUN_006ab760(*(void**)(*(char**)pLoc + 0x14), L"zh-cn")) {
        self->mb24 = 3;
        IWindow* w = self->mp14->FindWindowByID(0x5bfe3a8, 1);
        if (w != 0)
            w->PlayAnim(1, 1);
    } else {
        self->mb24 = 5;
    }

    if (self->mp14 != 0) {
        uint32_t step = self->mb24;
        self->mf18 = *(float*)((char*)g_kPanelIDs + step * 12 + 0x20c);
        self->mf1c = *(float*)((char*)g_kPanelIDs + step * 12 + 0x208);
        self->mf20 = 0.0f;
        PIB(0x1f3) = 0;
        PIB(0x1f4) = 0;
        PIB(0x1f2) = 1;
        PI(0x200) = 1;

        SetWindowImageFn img;
        img.a = (void*)0x38f538d6;
        img.b = 0x2f7d0004;
        img.c = 0x8a7be0c0;
        IWindow* w1 = self->mp14->FindWindowByID(0x79035d0, 1);
        if (w1 != 0)
            FUN_00807bb0(w1, &img, -1);
        IWindow* w2 = self->mp14->FindWindowByID(0x79035c8, 1);
        if (w2 != 0)
            FUN_00807bb0(w2, &img, -1);

        if (self->mb24 == 5)
            FUN_00deac20(self);

        if (self->mp14 != 0) {
            LocInfo loc;
            LocBuf buf;
            if (FUN_0087da90(&loc, (const void*)0x15a3cb0)) {
                if (FUN_0087e130(&loc, &buf)) {
                    char c = FUN_006ab760(&buf, L"en-us");
                    if (c != 0) {
                        void* pL = FUN_0067de40();
                        if (FUN_006ab760(*(void**)(*(char**)pL + 0x14), L"en-us")) {
                            IWindow* w3 = self->mp14->FindWindowByID(0x5b8bd48, 1);
                            if (w3 != 0)
                                w3->PlayAnim(1, 1);
                            IWindow* w4 = self->mp14->FindWindowByID(0x66f6ef0, 1);
                            if (w4 != 0)
                                w4->PlayAnim(1, 1);
                        }
                    }
                }
            }
            (void)loc; (void)buf;
        }
    }
}

// @ 0x00deb4a0
void __fastcall FUN_00deb4a0(cGalaxyGameEntryImpl_s00de_a870* self)
{
    void* pCheat = FUN_0067de20();
    if (pCheat != 0)
        ((Screen*)pCheat)->StopCheats(0);
    void* pMovie = FUN_0067cb10();
    if (pMovie != 0)
        ((cMovieSystem*)pMovie)->StopMovies(0);
    void* pMsg = FUN_0067dcc0();
    if (pMsg != 0) {
        cMessageServer_s00de_a870* srv = (cMessageServer_s00de_a870*)pMsg;
        void* handler = (self != 0) ? (void*)((char*)self + 8) : 0;
        srv->AddHandler(handler, 0x67c75bd6);
        handler = (self != 0) ? (void*)((char*)self + 8) : 0;
        srv->AddHandler(handler, 0x634297ad);
        handler = (self != 0) ? (void*)((char*)self + 8) : 0;
        srv->AddHandler(handler, 0x275a9c8c);
        handler = (self != 0) ? (void*)((char*)self + 8) : 0;
        srv->AddHandler(handler, 0xeda117de);
        handler = (self != 0) ? (void*)((char*)self + 8) : 0;
        srv->AddHandler(handler, 0x8085c4c);
    }
    *(uint8_t*)((char*)self + 0xd) = 0;
    if (PI(0x1ec) == 1)
        FUN_00deb0b0(self);
    ((cSPUIGlobalUI_s00de_a870*)PIP(0x184))->SetVisibility(false);
    {
        void* mgr = FUN_00b3d4d0();
        if (FUN_00ad7e20(mgr) == 0)
            ((ModalShim*)FUN_00b3d4d0())->SetModal(1);
    }
    ((cSPUILayout_s00de_a870*)((char*)g_kPanelIDs + 0x144))->SetVisibility(false);
}

// @ 0x00deb5d0
void __fastcall FUN_00deb5d0(void* self)
{
    uint32_t state = *(uint32_t*)(*(char**)((char*)self + 0xc) + 0xa8);
    if (state > 5)
        return;
    switch (state) {
    case 0:
        FUN_00b33d20(FUN_00b3d240());
        return;
    case 1:
        ((cTriggerReceiver*)FUN_00b3d410(1, (int*)&DAT_01654c01, 1))->PostTriggerSimple();
        return;
    case 2:
        ((cTriggerReceiver*)FUN_00b3d410(1, (int*)&DAT_01654c02, 1))->PostTriggerSimple();
        return;
    case 4:
        ((cTriggerReceiver*)FUN_00b3d410(1, (int*)&DAT_01654c04, 1))->PostTriggerSimple();
        return;
    case 5:
        ((cTriggerReceiver*)FUN_00b3d410(1, (int*)&DAT_01654c05, 1))->PostTriggerSimple();
        return;
    default:
        return;
    }
}

// @ 0x00deb670
void* __fastcall FUN_00deb670(void* self)
{
    FUN_00e00630_s00de_a870();
    *(uint32_t*)self = (int)g_147e3b0;
    *(void**)&g_16a1484 = self;
    return self;
}

// @ 0x00deb6a0
void* cGalaxyGameEntryDeb::DestroyDeb(unsigned int flags)
{
    *(void**)&g_16a1484 = 0;
    *(int**)this = &g_vtbl_GalaxyGameEntryDeb;
    if (flags & 1)
        FUN_00f47380(this);
    return this;
}

// @ 0x00deb6d0
void __fastcall FUN_00deb6d0(void* self)
{
    if (PI(0x108) != 0xc)
        return;
    *(uint32_t*)((char*)self + 0xc) = 0;
    if (PIP(0x198) != 0) {
        ((CbObj*)PIP(0x198))->Stop();
        Vec3g zero = {0.0f, 0.0f, 0.0f};
        Vec3g dir = zero;
        ((CbInner*)((char*)PIP(0x198) + 4))->Send(0x2ca298e9, &dir);
    }
    ((TrigMgrShim*)(void*)g_kPanelIDs)->Func(2, 0);
}

// @ 0x00deb770
void __fastcall FUN_00deb770(void* self, void* unused)
{
    (void)unused;
    void* pOut = 0;
    ResMgr* mgr = (ResMgr*)FUN_0067dcd0();
    if (pOut != 0) {
        pOut = 0;
        ((AppPropsList*)pOut)->Release();
    }
    void* pLocal = 0;
    if (mgr->FindKey((ResourceKey3*)((char*)self + 0x4c), &pLocal, 0, 0, 0, 0)) {
        TerrainObj* terr = (TerrainObj*)FUN_00b3d300();
        PlayerObj* pl = (PlayerObj*)FUN_00f67d90(terr);
        void* arg = 0;
        if (pLocal != 0) {
            typedef uint32_t (__thiscall *FNC)(void*, uint32_t);
            arg = (void*)((FNC)*(void**)(*(char**)pLocal + 0xc))(pLocal, 0x3c609f8);
        }
        ((TerrainObj*)(void*)pl)->UnlockAssociatedParts(arg);
        if (*(uint32_t*)((char*)pl + 0x10e8) != 0) {
            ((CollectItems*)*(void**)((char*)pl + 0x10e8))->EnsureBaseUnlocks(0x465c50ba);
            FUN_005942e0(*(void**)((char*)pl + 0x10e8));
        }
        void* pSpec = FUN_00401090();
        FUN_004df310(pSpec, (ResourceKey3*)((char*)self + 0x4c));
    }
    void* pSpec2 = FUN_00401090();
    *(uint32_t*)((char*)self + 0x48) = FUN_004df420(pSpec2);
    if (pLocal != 0) {
        ((AppPropsList*)pLocal)->Release();
    }
}

// @ 0x00deb840
void cGalaxyGameEntryUIStateMachine::SpawnBehaviorMessage(cGameInfo* gameInfo)
{
    if (!gameInfo)
        return;

    const char* name = (const char*)-1;
    switch (gameInfo->mA4) {
    case 0:
        name = &gStateNameTable[0];
        break;
    case 1:
        name = &gStateNameTable[1];
        break;
    case 2:
        name = &gStateNameTable[2];
        break;
    case 3:
    case 4:
        name = &gStateNameTable[4];
        break;
    case 5:
        name = &gStateNameTable[5];
        break;
    }

    UIBehaviorMessage* msg = new ("Simulator", 0, 0, 0, 0) UIBehaviorMessage();
    msg->mnMessageID = 0x4b719d4;
    msg->mpStateName = name;
    msg->mu10 = gameInfo->GetStarRecord()->Get58();
    MessageServer_s00de_b840()->Send2(msg->mnMessageID, msg, 0, 0);
    msg->Release();
}

// @ 0x00deb930
void cGalaxyGameEntryUIStateMachine::StartGame()
{
    cGameInfo* gi = mpGameInfo;

    ((NounMgr*)NounManager())->ResetEdits();
    cTerrainSphere* sphere = ((NounMgr*)NounManager())->GetCurrentTerrainSphere();
    gpGGE->mb1f0 = false;

    ResourceKey query = gi->mKey4C;
    query.mnTypeID = 0x30bdee3;

    IRefObj* pResource = 0;
    cResourceManager* pManager = (cResourceManager*)GetResourceManager();
    if (pResource) {
        pResource = 0;
        pResource->Release();
    }

    if (pManager->GetResource(&query, &pResource, 0, 0, 0, 0)) {
        IRefObj* pPart = 0;
        if (pResource)
            pPart = pResource->vf3(0x30bdee3);
        if (pPart)
            pPart->vf0();
        bool bOK = FUN_00550970(pPart) != 0;
        if (pPart)
            pPart->Release();
        if (bOK) {
            switch (gi->mA4) {
            case 5:
                sphere->mu1108 = FUN_00556140(&gi->mKey4C, 0xbeb528cb);
            case 4:
                sphere->mu1104 = FUN_00556140(&gi->mKey4C, 0xf71fa311);
            case 2:
                sphere->mu1100 = FUN_00556140(&gi->mKey4C, 0xad56080c);
            case 1:
                sphere->mu10fc = FUN_00556140(&gi->mKey4C, 0xa426730b);
            }
        }
    }

    if (gi->mA4 == 5 && IsWorldLayoutFlagSet_s00de_b840(2)) {
        ((AssetBrowserObj*)GetSetting3())->CloneModelAsset(gi->mKey4C, &gi->mKey58, 0x4178b8e8, true);
        void* pOut = 0;
        FUN_005bf3a0(&gi->mKey58, &kAssetKey, &pOut, 0);
        FUN_00eebf90(pOut, &gi->mName);
        MessageServer_s00de_b840()->Send(0x73e46f6, &gi->mKey58, 0);
        if (pOut)
            ((IRefObj*)pOut)->Release();
    }

    if (gi->mA8 == 0) {
        sphere->mu68c = gi->mKey4C.mnInstanceID;
        sphere->mu690 = gi->mKey4C.mnTypeID;
        sphere->mu694 = gi->mKey4C.mnGroupID;
    } else if (gi->mKey4C.mnTypeID == 0x3d97a8e4) {
        FUN_00e83910(&gi->mKey4C, 0, 0, 0);
    } else {
        SetupTerrainFromGame(gi);
    }

    gi->mpAvatar = ((cSetting9*)GetSetting9())->GetAvatarProfile();
    if (((cAppSystem*)AppSystem())->IsFeatureEnabled()) {
        if (gi->GetStarRecord()->mbAC)
            gi->GetStarRecord()->Measure(1);
    }

    cTerrainSphere* sphere2 = ((NounMgr*)NounManager())->GetCurrentTerrainSphere();
    sphere2->mu1150 = gi->mKey70.mnInstanceID;
    sphere2->mu1154 = gi->mKey70.mnTypeID;
    sphere2->mu1158 = gi->mKey70.mnGroupID;

    gi->GetStarRecord()->SetKey(&gi->mKey4C);

    uint32_t* pDest = 0;
    if (gi->mA4 == 5) {
        pDest = &sphere->mu1168;
    } else if (gi->mA4 == 4) {
        cAvatarProfile* pAvatar = gi->mpAvatar;
        Vector3 v;
        v.x = pAvatar->mf4ec;
        v.y = pAvatar->mf4f0;
        v.z = pAvatar->mf4f4;
        Vector3 out;
        FUN_00b6e4b0(v, 0.5f, 0.5f, &out);
        FUN_00b6f140();
        FUN_00b6f180();
        sphere->mu1174 = gi->m90;
        pDest = &sphere->mu115c;
    }
    if (pDest) {
        pDest[0] = gi->mKey64.mnInstanceID;
        pDest[1] = gi->mKey64.mnTypeID;
        pDest[2] = gi->mKey64.mnGroupID;
    }

    SpawnBehaviorMessage(gi);

    if (gi->mA4 == 0 && (gpTestSystem == 0 || *(void**)((char*)gpTestSystem + 0x70) == (char*)gpTestSystem + 0x70)) {
        ((cTriggerMgr*)GetTriggerMgr())->ClearTimers();
        ((cGameMode*)GetGameMode())->AddStar(gi);
        if (gi->GetStarRecord()->mbAC) {
            cStarName* pName = gi->GetStarRecord()->GetName(0);
            Vector3 pos = *pName->GetPosition();
            pName->mName = gi->mPath;
            ((cPlanetModel*)GetPlanetModel())->SetPosition(&pos, 0, 1);
            ((cSystemX*)GetSystemX())->PostMessage(0x7b023a50);
            ((cTriggerMgr*)GetTriggerMgr())->PostTrigger("GGE2CLG", 1, 0, 0, 0, 0);
        }
    } else {
        if (gi->GetStarRecord()->mbAC) {
            cStarName* pName = gi->GetStarRecord()->GetName(0);
            pName->mName = gi->mPath;
            ((cGameMode*)GetGameMode())->PopState(gi);
        }
    }

    gpGGE->mp198->SetFlag(0);
    mpGameInfo = 0;
    if (pResource)
        pResource->Release();
}

// @ 0x00debe30
bool cGalaxyGameEntryUIStateMachine::OnMessageCloseZoom(uint32_t id, int arg)
{
    (void)arg;
    if (id == 0x4360e14) {
        if (gpGGE->mb1f0) {
            ((cTriggerMgr*)GetTriggerMgr())->ClearTimers();
            IRefObj* pZoom = gpGGE->mp1a4;
            if (pZoom) {
                gpGGE->mp1a4 = 0;
                pZoom->Release();
            }
            IRefObj* pBlur = gpGGE->mp19c;
            if (pBlur) {
                gpGGE->mp19c = 0;
                pBlur->Release();
            }
            gpGGE->mb100 = false;
            StartGame();
        }
        return true;
    }
    return false;
}

// @ 0x00debec0
void cGalaxyGameEntryUIStateMachine::EnterPlanet(const WString& name)
{
    WString str(name);
    str = PathPick(str, gpSporePathBegin);
    MessageServer_s00de_b840()->Send(0x680c633, str.mpBegin, 0);
    ((cPlanetLoader*)GetAux0())->Reset();
    ((cGameMode*)GetGameMode())->SavePath(str.mpBegin);
    gpGGE->mp198->SetFlag(0);
    if (!gpGGE->mbF4)
        StopZoomTransition();
}

// @ 0x00dec020
void cGalaxyGameEntryUIStateMachine::StartNewGameZoom()
{
    ((cPlanetLoader*)GetAux0())->Reset();
    gpGGE->MoveTo(0);
    mpGameInfo->mpLayout->SetVisibility(false);

    for (IRefObj** it = gpGGE->mEffects.mpBegin; it != gpGGE->mEffects.mpEnd; ++it)
        (*it)->vf3(1);
    gpGGE->mEffects.DoFree(gpGGE->mEffects.mpBegin, gpGGE->mEffects.mpEnd);

    // the zoom effects live in AutoRefCount handles: the slot outlives the calls
    IRefObj** ppZoom = &gpGGE->mp1a4;
    IEffectStore* pStore = gpGGE->mpEffectStore;
    IRefObj* pZoom = *ppZoom;
    if (pZoom) {
        *ppZoom = 0;
        pZoom->Release();
    }
    pStore->Find(0x61ebc5d1, 0, ppZoom);
    if (gpGGE->mp1a4)
        gpGGE->mp1a4->SetFlag(0);

    ((cTriggerMgr*)GetTriggerMgr())->PostTrigger("GGE_zoom_modal", 0, 0, 0, 0, 0);
    gpGGE->mp198->Zoom(kfZoomDuration);

    IRefObj* pEffect = 0;
    gpGGE->mpEffectStore->Find(0xdc4678a3, 0, &pEffect);
    if (pEffect)
        pEffect->SetFlag(0);
    gpGGE->mb1f0 = true;
    if (pEffect)
        pEffect->Release();
}

// @ 0x00dec170
void cGalaxyGameEntryUIStateMachine::Update(int arg)
{
    (void)arg;
    cGameInfo* gi = mpGameInfo;
    if (!gi || gpGGE->mb1f0)
        return;

    if (mCountdown > 0) {
        if (gi->mbAC) {
            if (mCountdown == 2) {
                StopZoomTransition();
                --mCountdown;
                return;
            }
        } else {
            if (mCountdown == 2) {
                FUN_00de3be0(gi);
                --mCountdown;
                return;
            }
        }
        if (mCountdown == 1 && !gpGGE->mb140 && gi->mA8 != 0) {
            if (!((cSetting410*)GetAux410())->mb508)
                mCountdown = 2;
        }
        --mCountdown;
        return;
    }

    if (gpGGE->mb140) {
        gpGGE->NotifyStateChange(2, false);
        ((cGameMode*)GetGameMode())->PopState(gi);
        return;
    }

    if (gi->mbAC) {
        SpawnBehaviorMessage(gi);
        bool bOk;
        WString path(gi->mPath.mpBegin, &bOk);
        path = PathJoin(path, gpSporePathBegin);
        uint32_t a;
        uint32_t b;
        if (!((cGameMode*)GetGameMode())->QualifyName(path.mpBegin, &a, &b) && a == 0 && b == 0)
            gi->m8C = 3;
        if (gi->m8C == 3) {
            ((cLocale*)LocaleManager())->GetCalloutText()->SetText(path.mpBegin, 0);
            CalloutMessageBox(0, &kNotFoundText);
            gpGGE->NotifyStateChange(2, false);
            return;
        }
        EnterPlanet(path);
        return;
    }

    if (gi->mA8 != 0)
        StartGame();
    else
        StartNewGameZoom();
}

// @ 0x00dec360
void CloseAssetBrowserUI()
{
    IWindow_s00de_b840* pWindow = gpGGE->mLayout.FindWindowByID(0x615a5ff, true);
    if (pWindow)
        pWindow->SetFlag(1, 0);
    gpGGE->MoveTo(1);
    gpGGE->mpGlobalUI->SetVisibility(false);
}

// @ 0x00dec3b0
void ShowGlobalUI()
{
    gpGGE->mpGlobalUI->SetVisibility(true);
    bool bBrowserOpen = GetSetting3() && ((AssetBrowserObj*)GetSetting3())->mb1c;
    gpGGE->MoveTo(bBrowserOpen);
}

// @ 0x00dec3f0
void cGalaxyGameEntryUIStateMachine::RefreshWhenIdle(int arg)
{
    (void)arg;
    if (gpGGE->mu108 == 10 && gpGGE->mu10c == 10 && !gpGGE->mbEF && !gpGGE->mb102 && !gpGGE->mb101)
        gpGGE->PopModeStack();
}

// @ 0x00dec430
void cGalaxyGameEntryUIStateMachine::SetDeferredWindow(uint32_t id, void* param)
{
    if (((gDeferredWindowMask[id >> 5] >> (id & 31)) & 1) == 0)
        SetWindowParam(id, param);
}

// @ 0x00dec460
void cGalaxyGameEntryUIStateMachine::ResetGameUI()
{
    for (uint32_t i = 0; i < 5; ++i) {
        IWindow_s00de_b840* pWindow = mLayout.FindWindowByID(kResetWindowIDs[i], true);
        if (pWindow)
            pWindow->SetParam(&kWindowFlagParam);
    }
}

// @ 0x00dec4a0
bool cGalaxyGameEntryUIStateMachine::CanPlay()
{
    cGameInfo* gi = mpGameInfo628;
    if (!gi || gi->mA4 == 6)
        return false;
    PlayEntry* pEntry = &mEntries[gi->mA4];
    if (pEntry->mAC != 0 && gi->mKey4C.mnInstanceID == 0)
        return false;
    if (pEntry->mB0 != 0 && gi->mKey70.mnInstanceID == 0)
        return false;
    if (pEntry->mB4 != 0 && gi->mKey64.mnInstanceID == 0)
        return false;
    return true;
}

// @ 0x00dec500
void cGalaxyGameEntryUIStateMachine::ResetButtons()
{
    ResetGameUI();
    for (uint32_t i = 0; i < 6; ++i)
        mLayout.FindWindowByID(kButtonWindowIDs[i], true)->SetFlag(2, 0);
}

// @ 0x00dec540
bool cGalaxyGameEntryUIStateMachine::IsAssetWindowOn(uint32_t id)
{
    IWindow_s00de_b840* pWindow = mLayout.FindWindowByID(id, true);
    if (pWindow)
        return (pWindow->GetState() >> 2) & 1;
    return false;
}

// @ 0x00dec570
void cGalaxyGameEntryUIStateMachine::UpdateLocks()
{
    switch (mpGameInfo628->mA8) {
    case 0:
    case 1:
    case 2:
        mLayout.FindWindowByID(0x59461b1, true)->SetFlag(1, 0);
        mLayout.FindWindowByID(0x59461b0, true)->SetFlag(1, 0);
        mLayout.FindWindowByID(0x59461b2, true)->SetFlag(1, 0);
        break;
    case 4:
    case 5:
        mLayout.FindWindowByID(0x59461b1, true)->SetFlag(1, 1);
        mLayout.FindWindowByID(0x59461b0, true)->SetFlag(1, 1);
        mLayout.FindWindowByID(0x59461b2, true)->SetFlag(1, 1);
        break;
    }
    if (mpGameInfo628->mKey4C.mnInstanceID == 0)
        mLayout.FindWindowByID(0x59461b1, true)->SetFlag(1, 0);
    if (mpGameInfo628->mKey64.mnInstanceID == 0)
        mLayout.FindWindowByID(0x59461b0, true)->SetFlag(1, 0);
    if (mpGameInfo628->mKey70.mnInstanceID == 0)
        mLayout.FindWindowByID(0x59461b2, true)->SetFlag(1, 0);
}

// @ 0x00dec6d0
void cGalaxyGameEntryUIStateMachine::ShowSkin(uint32_t id)
{
    const uint32_t skins[5] = {0x5b218d1, 0x5b218c9, 0x5adf8e2, 0x5b8a143, 0x5b218d9};
    for (uint32_t i = 0; i < 5; ++i) {
        if (mLayout.FindWindowByID(skins[i], true))
            mLayout.FindWindowByID(skins[i], true)->SetFlag(1, 0);
    }
    if (id) {
        if (mLayout.FindWindowByID(id, true))
            mLayout.FindWindowByID(id, true)->SetFlag(1, 1);
    }
}

// @ 0x00dec770
void cGalaxyGameEntryUIStateMachine::QueueEditorLaunch(uint32_t id, const uint32_t* key)
{
    mu504 = id;
    mu5e4 = 10;
    mu508 = key[0];
    mu50c = key[1];
    mu510 = key[2];
    MessageServer_s00de_b840()->Send2(0x5b5c746, 0, 0, 0);
}

// @ 0x00dec7c0
void SP::cGalaxyGameEntryUIStateMachine_s00de_c7c0::MakeNewAsset(uint32_t nAssetType)
{
    if (mpModel == 0)
        return;

    uint32_t nLaunchID = 0;

    switch (nAssetType) {
    case 0x9596477b:
        mnPendingAssetAction = 0x54045ce;
        if (mpModel->mnFieldA8 == 0) {
            mLayout.FindWindowByID(0x5384881, 1)->Show(1, 0);
            nLaunchID = 0xef18a560;
        } else if (mpModel->mnFieldA8 == 1) {
            mLayout.FindWindowByID(0x5384881, 1)->Show(1, 0);
            nLaunchID = 0xe46c381e;
        } else {
            mLayout.FindWindowByID(0x5384881, 1)->Show(1, 0);
            nLaunchID = 0x465c50ba;
        }
        break;

    case 0x95964778:
        mnPendingAssetAction = 0x54045e3;
        if (mpModel->mnFieldA8 == 5) {
            mLayout.FindWindowByID(0x5384881, 1)->Show(1, 0);
            nLaunchID = 0x96b24187;
        } else if (mpModel->mnFieldA8 == 4) {
            mLayout.FindWindowByID(0x5384881, 1)->Show(1, 0);
            nLaunchID = 0x7d433fad;
        } else {
            return;
        }
        break;

    case 0x95964775:
        mnPendingAssetAction = 0x5404617;
        mLayout.FindWindowByID(0x5384881, 1)->Show(1, 0);
        nLaunchID = 0x99e92f05;
        break;

    default:
        return;
    }

    QueueEditorLaunch(nLaunchID, Key());
}

// @ 0x00dec940
void SP::cGalaxyGameEntryUIStateMachine_s00de_c7c0::LoadAsset(uint32_t nAssetType)
{
    switch (nAssetType) {
    case 0x9596477a:
        HandleEvent(0x54045ce);
        break;
    case 0x95964777:
        HandleEvent(0x54045e3);
        break;
    case 0x95964774:
        HandleEvent(0x5404617);
        break;
    }
}

// @ 0x00dec990
uint32_t __cdecl FUN_00dec990(cEditorEntry* pEntry)
{
    cUIEventQueue* pQueue = GetUIEventQueue();
    cAssetEntryList* pList = pQueue->GetSelectedEntry(pEntry->mnField88, pEntry->mnField84);
    if (pList == 0)
        return 1;

    if (pList->Matches(0x100f0f5a)) return 0xc;
    if (pList->Matches(0x11b79a74)) return 2;
    if (pList->Matches(0x11b79a70)) return 3;
    if (pList->Matches(0x032f92e6)) return 9;
    if (pList->Matches(0x11b79a72)) return 0xa;
    if (pList->Matches(0x11b79a71)) return 7;
    if (pList->Matches(0x11b79a78)) return 4;
    if (pList->Matches(0x11b79a75)) return 6;
    if (pList->Matches(0x11b79a76)) return 5;
    if (pList->Matches(0x11b79a77)) return 8;
    return pList->Matches(0x11b79a73) ? 11 : 1;
}

// @ 0x00decad0
void SP::cGalaxyGameEntryUIStateMachine_s00de_c7c0::ShowAssetButtonsForLevel(int32_t nLevel)
{
    cNewGameModePanel* pPanel = &maModePanels[nLevel];

    cUIWindow* pWindow = mLayout.FindWindowByID(0x54045ce, 1);
    if (pWindow != 0) {
        pWindow->Show(2, pPanel->mbFieldBC);
        pWindow->Show(1, pPanel->mnCreatureKey != 0);
    }

    for (int32_t i = 0; i < mnRolloverCount; ++i) {
        cUIWindow* pRollover = mLayout.FindWindowByID(mpRolloverWindowIDs[i], 1);
        if (pRollover != 0)
            pRollover->Show(1, 0);
    }

    pWindow = mLayout.FindWindowByID(pPanel->mnWindowIDA0, 1);
    if (pWindow != 0)
        pWindow->Show(1, mpModel->mKey4C.mnA == 0);

    pWindow = mLayout.FindWindowByID(pPanel->mnWindowIDA8, 1);
    if (pWindow != 0)
        pWindow->Show(1, mpModel->mKey70.mnA == 0);

    pWindow = mLayout.FindWindowByID(pPanel->mnWindowIDA4, 1);
    if (pWindow != 0)
        pWindow->Show(1, mpModel->mKey64.mnA == 0);

    pWindow = mLayout.FindWindowByID(0x5404617, 1);
    if (pWindow != 0)
        pWindow->Show(1, pPanel->mnBuildingKey != 0);

    pWindow = mLayout.FindWindowByID(0x54045e3, 1);
    if (pWindow != 0)
        pWindow->Show(1, pPanel->mnVehicleKey != 0);

    if (pPanel->mpImageBuilding != 0)
        FUN_00de3d00(&mLayout, 0x5404617, pPanel->mpImageBuilding);

    if (pPanel->mpImageCreature != 0)
        FUN_00de3d00(&mLayout, 0x54045ce, pPanel->mpImageCreature);

    if (pPanel->mpImageVehicle != 0)
        FUN_00de3d00(&mLayout, 0x54045e3, pPanel->mpImageVehicle);

    bool bSelected = true;
    bool bNotSelected = false;
    if ((((cPanelButtonWindow*)mLayout.FindWindowByID(0x5404617, 1))->GetState() & 1) == 0) {
        bSelected = false;
        bNotSelected = true;
    }

    pWindow = mLayout.FindWindowByID(0x59434c0, 1);
    if (pWindow != 0)
        pWindow->Show(1, bSelected);

    pWindow = mLayout.FindWindowByID(0x6451450, 1);
    if (pWindow != 0)
        pWindow->Show(1, bNotSelected);

    UpdateLocks();
}

// @ 0x00decd10
void SP::cGalaxyGameEntryUIStateMachine_s00de_c7c0::FUN_00decd10(int32_t nLevel)
{
    uint32_t windows[6] = {0x677345c, 0x67731fa, 0x6773513,
                           0x65fbfa0, 0x6775ebb, 0x6775ebc};
    for (uint32_t i = 0; i < 6; ++i) {
        cUIWindow* pWindow = mLayout.FindWindowByID(windows[i], 1);
        if (pWindow != 0)
            pWindow->Show(1, 0);
    }

    cUIWindow* pHighlight = mLayout.FindWindowByID(0x669f710, 1);
    cNewGameModePanel& rPanel = maModePanels[nLevel];
    if (pHighlight != 0) {
        int32_t nOtherID = rPanel.mnHighlightWindowID;
        if (nOtherID != 0) {
            cUIWindow* pOther = mLayout.FindWindowByID(nOtherID, 1);
            if (pOther == 0)
                goto done;
            pOther->Show(1, 1);
            pHighlight->Show(1, 1);
            goto done;
        }
        pHighlight->Show(1, 0);
    }
done:
    cUIWindow* pWindow;
    if (nLevel == 0)
        pWindow = mLayout.FindWindowByID(0x6775ebb, 1);
    else
        pWindow = mLayout.FindWindowByID(0x6775ebc, 1);
    if (pWindow != 0)
        pWindow->Show(1, 1);
}

// @ 0x00dece10
void SP::cGalaxyGameEntryUIStateMachine_s00de_c7c0::SetupStartState()
{
    if (mLayout.FindWindowByID(0x5384881, 1) == 0)
        return;

    mLayout.FindWindowByID(0x5384881, 1)->Show(1, 0);
    mLayout.FindWindowByID(0x5812792, 1)->Show(1, 0);
    mLayout.FindWindowByID(0x57f74f6, 1)->Show(1, 0);
    mLayout.FindWindowByID(0x5beb40d, 1)->Show(1, 1);
    ResetButtons();
    gpGameMode->SetGuideState(0);
    mStateList.Reset();
    mnField5EC = 0;
}

// @ 0x00decf00
void cPanelHost::FUN_00decf00(int32_t nID)
{
    if (mpWidget != 0)
        mpWidget->mbField81 = 1;
}

// @ 0x00decf20
void __stdcall FUN_00decf20(cUIWindow* pWindow, int32_t nPanelID)
{
    uint32_t nCount = (uint32_t)(gpGameMode->mpPanelIDEnd - gpGameMode->mpPanelIDBegin);
    for (uint32_t i = 0; i < nCount; ++i) {
        if (gpGameMode->mpPanelIDBegin[i] == (uint32_t)nPanelID) {
            pWindow->SelectPanel((int32_t)i, 0);
            return;
        }
    }
}

// @ 0x00decf70
void SP::cGalaxyGameEntryUIStateMachine_s00de_c7c0::HighlightPanelButton(uint32_t nWindowID)
{
    for (uint32_t i = 0; i < 6; ++i) {
        cUIWindow* pWindow = mLayout.FindWindowByID(kGUI_PanelButtonIDs[i], 1);
        if (pWindow != 0) {
            cUIWindow* pChild = pWindow->FindChild(0x8ed27e7a);
            if (pChild != 0) {
                if (kGUI_PanelButtonIDs[i] == nWindowID)
                    pChild->SetFlag(4, 1);
                else
                    pChild->SetFlag(4, 0);
            }
        }
    }
}

// @ 0x00decfd0
void SP::cGalaxyGameEntryUIStateMachine_s00de_c7c0::ToggleAssetLock(uint32_t nWindowID)
{
    cUIWindow* pWindow = mLayout.FindWindowByID(nWindowID, 1);
    cUIWindow* pChild = pWindow != 0 ? pWindow->FindChild(0x8ed27e7a) : 0;
    if ((pWindow->GetFlags() & 4) != 0)
        pChild->SetFlag(4, 0);
    else
        pChild->SetFlag(4, 1);
}

// @ 0x00ded030
void SP::cGalaxyGameEntryUIStateMachine_s00de_c7c0::FUN_00ded030()
{
    if (!gbFlag16a0ee8)
        return;

    cUIWindow* pWindow = mLayout.FindWindowByID(0x657ce07, 1);
    Vec3 one = {kRealOne, kRealOne, kRealOne};
    GetUiCtl()->BindSlot(&mpModel->mKey4C, 0x4d594c50, &one, 0, 0, pWindow);
    GetUiCtl()->Flush(0, 0, 0, 0);
}

// @ 0x00ded0b0
bool SP::cGalaxyGameEntryUIStateMachine_s00de_c7c0::FUN_00ded0b0(Key* pKey)
{
    if (!gbFlag16a0e48)
        return true;

    cNewGameModePanel* pPanel = &maModePanels[mpModel->mnFieldA4];
    int32_t nExpected = 0;
    switch (mnPendingAssetAction) {
    case 0x54045ce:
        nExpected = (int32_t)pPanel->mnCreatureKey;
        break;
    case 0x54045e3:
        return pPanel->mnVehicleKey == pKey->mnB;
    case 0x5404617:
        return pPanel->mnBuildingKey == pKey->mnB;
    }
    return pKey->mnB == (uint32_t)nExpected;
}

// @ 0x00ded140
void SP::cGalaxyGameEntryUIStateMachine_s00de_c7c0::ResetAssetButtons(bool bBuilding, bool bCreature, bool bVehicle)
{
    if (mpModel == 0)
        return;

    cNewGameModePanel* pPanel = &maModePanels[mpModel->mnFieldA4];

    if (bCreature) {
        cUIWindow* pWindow = mLayout.FindWindowByID(0x5b744bc, 1);
        cUIWindow* pContent = pWindow->GetContent();
        cUIWindow* pChild = pContent != 0 ? pContent->FindChild(0x103c1908) : 0;
        pChild->SetParams(0, (int32_t)mpAssetIconCreature);
        mLayout.FindWindowByID(pPanel->mnWindowIDA0, 1)->Show(1, 1);
        mLayout.FindWindowByID(0x5b69a71, 1)->Show(1, 0);
        pWindow = mLayout.FindWindowByID(0x59461b1, 1);
        bool bLocked = false;
        if (pWindow != 0)
            bLocked = ((pWindow->GetFlags() >> 2) & 1) != 0;
        if (bLocked)
            ToggleAssetLock(0x59461b1);
    }

    if (bBuilding) {
        cUIWindow* pWindow = mLayout.FindWindowByID(0x5b73f5b, 1);
        cUIWindow* pContent = pWindow->GetContent();
        cUIWindow* pChild = pContent != 0 ? pContent->FindChild(0x103c1908) : 0;
        pChild->SetParams(0, (int32_t)mpAssetIconBuilding);
        mLayout.FindWindowByID(pPanel->mnWindowIDA8, 1)->Show(1, 1);
        mLayout.FindWindowByID(0x5b69a72, 1)->Show(1, 0);
        pWindow = mLayout.FindWindowByID(0x59461b2, 1);
        bool bLocked = false;
        if (pWindow != 0)
            bLocked = ((pWindow->GetFlags() >> 2) & 1) != 0;
        if (bLocked)
            ToggleAssetLock(0x59461b2);
    }

    if (bVehicle) {
        cUIWindow* pWindow = mLayout.FindWindowByID(0x5b745cc, 1);
        cUIWindow* pContent = pWindow->GetContent();
        cUIWindow* pChild = pContent != 0 ? pContent->FindChild(0x103c1908) : 0;
        pChild->SetParams(0, (int32_t)mpAssetIconVehicle);
        mLayout.FindWindowByID(pPanel->mnWindowIDA4, 1)->Show(1, 1);
        mLayout.FindWindowByID(0x5b69a70, 1)->Show(1, 0);
        pWindow = mLayout.FindWindowByID(0x59461b0, 1);
        bool bLocked = false;
        if (pWindow != 0)
            bLocked = ((pWindow->GetFlags() >> 2) & 1) != 0;
        if (bLocked)
            ToggleAssetLock(0x59461b0);
    }
}

// @ 0x00ded390
void SP::cGalaxyGameEntryUIStateMachine_s00de_c7c0::ResetThemeIcons()
{
    for (uint32_t i = 0; i < gThemeIconCount; ++i) {
        cUIWindow* pWindow = mLayout.FindWindowByID(0x57f74f6 + i, 1);
        if (pWindow != 0) {
            cUIWindow* pContent = pWindow->GetContent();
            cUIWindow* pChild = pContent != 0 ? pContent->FindChild(0x53eb526) : 0;
            ((Drawable_s0083_0c00*)pChild)->SetImageIcon(0, mpThemeIconBlank);
            pWindow->w90();
        }
    }
}

// @ 0x00ded410
void SP::cGalaxyGameEntryUIStateMachine_s00de_c7c0::EditExistingAsset(uint32_t nAssetType)
{
    if (mpModel == 0)
        return;

    switch (nAssetType) {
    case 0x95964779:
        if (mpModel->mKey4C.mnA == 0)
            return;
        mnPendingAssetAction = 0x54045ce;
        mLayout.FindWindowByID(0x5384881, 1)->Show(1, 0);
        if (mpModel->mnFieldA8 == 0)
            QueueEditorLaunch(0xef18a560, mpModel->mKey4C);
        else if (mpModel->mnFieldA8 == 1)
            QueueEditorLaunch(0xe46c381e, mpModel->mKey4C);
        else
            QueueEditorLaunch(0x465c50ba, mpModel->mKey4C);
        break;

    case 0x95964776:
        if (mpModel->mKey64.mnA == 0)
            return;
        mnPendingAssetAction = 0x54045e3;
        if (mpModel->mnFieldA8 == 5) {
            mLayout.FindWindowByID(0x5384881, 1)->Show(1, 0);
            QueueEditorLaunch(0x96b24187, mpModel->mKey64);
        } else if (mpModel->mnFieldA8 == 4) {
            mLayout.FindWindowByID(0x5384881, 1)->Show(1, 0);
            QueueEditorLaunch(0x7d433fad, mpModel->mKey64);
        }
        break;

    case 0x95964773:
        if (mpModel->mKey70.mnA == 0)
            return;
        mLayout.FindWindowByID(0x5384881, 1)->Show(1, 0);
        mnPendingAssetAction = 0x5404617;
        QueueEditorLaunch(0x99e92f05, mpModel->mKey70);
        break;
    }
}

// @ 0x00ded5a0
bool cGalaxyGameEntryUIStateMachine_s00de_d5a0::PopulateContextMenu()
{
    IWindow_s00de_d5a0* pWindow = mLayout.FindWindowByID(0x0684bbe8, true);
    if (!pWindow)
        return false;
    cSPUIPopupMenuWin2* pMenu = (cSPUIPopupMenuWin2*)pWindow->v0C(0x04c058d5);
    if (!pMenu)
        return false;

    pMenu->Reset();

    cString_s00de_d5a0 title(0x2b7a0311, 0x5b08761, 0);

    MenuTextKey key1 = { 0xa10d844a, 0x510a95b, 0x40464100 };
    void* pFirst = pMenu->AddMenuItem3((uint32_t)&key1, 0, (uint32_t)title.GetText(), false);

    EditorMenuSource* pSource = (EditorMenuSource*)FUN_0067cb30();
    int32_t nItems = (int32_t)(pSource->mpItemsCC - pSource->mpItemsC8);
    if (nItems > 0) {
        for (int32_t i = 0; i < nItems; ++i) {
            EditorMenuItem* pItem = &pSource->mpItemsC8[i];
            MenuTextKey key;
            key.mTable = 0xa10d844a;
            key.mKey = 0x510a95b;
            key.mPage = 0x40464100;
            uint32_t nText = pItem->mKind == 2 ? pItem->mField00 : pItem->mField18;
            pMenu->AddMenuItem3((uint32_t)&key, 0, nText, false);
        }
    }

    pSource = (EditorMenuSource*)FUN_0067cb30();
    nItems = (int32_t)(pSource->mpItemsB8 - pSource->mpItemsB4);
    if (nItems > 0) {
        for (int32_t i = 0; i < nItems; ++i) {
            EditorMenuItem* pItem = &pSource->mpItemsB4[i];
            if (pItem->mKind == 7) {
                cString_s00de_d5a0 name;
                name.Load(0x21671745, 0x10002, L"My Creations");
                MenuTextKey key;
                key.mTable = 0xa10d844a;
                key.mKey = 0x510a95b;
                key.mPage = 0x40464100;
                pMenu->AddMenuItem3((uint32_t)&key, 0, (uint32_t)name.GetText(), false);
                name.~cString_s00de_d5a0();
            } else {
                MenuTextKey key;
                key.mTable = 0xa10d844a;
                key.mKey = 0x510a95b;
                key.mPage = 0x40464100;
                pMenu->AddMenuItem3((uint32_t)&key, 0, pItem->mField18, false);
            }
        }
    }

    pMenu->OnMenuItemSelected(0, pFirst);

    void* pBox = AddBoundingBoxEx((uint8_t*)pMenu + 4, 1, 1);
    FUN_0080d710(pBox);

    title.~cString_s00de_d5a0();
    return true;
}

// @ 0x00ded7d0
void cGalaxyGameEntryUIStateMachine_s00de_d5a0::ShowPlanetModel()
{
    if (!mpEditorFlow->FUN_00de4610(0)->mIsActive)
        return;

    StarManager_s00de_d5a0();

    cGalaxyEditorState* pEditor = mpEditorFlow->FUN_00de4610(0);
    void* pSelection = FUN_00bbaa60(pEditor);
    float* pPosition = (float*)FUN_00b8d8e0(pSelection);

    struct { float mX, mY, mZ; } vSeed = { pPosition[0], pPosition[1], pPosition[2] };
    MenuTextIds ids = { 0, 0, 0, 0 };
    MenuTextIds ids2 = { 0, 0, 0, 0 };

    void* pKey = FUN_00b3d360(&vSeed);
    if (!FUN_00b7d4f0(pKey)) {
        mPlanetView.FUN_00e20e00();
        mPlanetView.FUN_00e20d60(&gEditorMenuSource);
        return;
    }

    void* pHandle = FUN_00b3d360(&vSeed);
    FUN_00b7d440(pHandle, &ids2, &ids);

    if (ids.mId0 != 0) {
        mpLayeredObject->RemoveAllModels();
        if (gPlanetPreviewEnabled) {
            ids.mId0 = 0xcf571b4e;
            ids.mId1 = 0xd94352ed;
            ids.mId2 = 0xcf571b4e;
            ids.mId3 = 0xd94352ed;
        }
        mPlanetView.FUN_00e21260(&ids, &ids.mId2, mpLayeredObject);
        mPlanetView.FUN_00e20d30(gPlanetPreviewBlend);
    }
    mPlanetView.FUN_00e20d60(&gEditorMenuSource);
}

// @ 0x00ded920
void cGalaxyGameEntryUIStateMachine_s00de_d5a0::PickStarForEditorToGameFlow(uint32_t nID, int32_t nMode)
{
    if (!mpEditorFlow)
        return;

    MenuTextIds ids = { 0, 0, 0, 0x2b7a0311 };
    bool bWorldFlag = IsWorldLayoutFlagSet(2);

    if (!bWorldFlag || nMode != 0) {
        if (nMode != 1)
            return;

        uint32_t nWindowId = 0;
        if (nID < 0x54045cf) {
            switch (nID) {
            case 0x53f06e1: nWindowId = 0x5b218d0; break;
            case 0x53f06ee: nWindowId = 0x5b218c8; break;
            case 0x53f06f5: nWindowId = 0x5adf8e1; break;
            case 0x53f06fc: nWindowId = 0x5adf8e0; break;
            case 0x53f0707: nWindowId = 0x5b218d8; break;
            default: break;
            }
        } else if (nID > 0x54045cf) {
            switch (nID) {
            case 0x54045e4: nWindowId = 0x5b69a70; break;
            case 0x5404618: nWindowId = 0x5b69a72; break;
            default: break;
            }
        }

        if (nWindowId != 0) {
            IWindow_s00de_d5a0* pPage = mLayout.FindWindowByID(nWindowId, true);
            if (pPage)
                pPage->v7C(true, false);
        }
        IWindow_s00de_d5a0* pDescription = mLayout.FindWindowByID(0x5b82168, true);
        if (pDescription)
            pDescription->v7C(true, true);
        return;
    }

    uint32_t nSelectedWindow = 0;

    if (nID < 0x54045cf) {
        if (nID != 0x54045ce) {
            switch (nID) {
            case 0x53f06e1:
                nSelectedWindow = 0x5b218d0;
                ids.mId0 = 0x5b08708;
                ids.mId1 = 0x5b08708;
                ids.mId2 = 0x668e2b7;
                break;
            case 0x53f06ee:
                nSelectedWindow = 0x5b218c8;
                ids.mId0 = 0x5b08709;
                ids.mId1 = 0x65f8fbc;
                ids.mId2 = 0x668e2b8;
                break;
            case 0x53f06f5:
                nSelectedWindow = 0x5adf8e1;
                ids.mId0 = 0x5b08710;
                ids.mId1 = 0x65f8fc5;
                ids.mId2 = 0x668e2b9;
                break;
            case 0x53f06fc:
                nSelectedWindow = 0x5adf8e0;
                ids.mId0 = 0x5b08711;
                ids.mId1 = 0x65f8fd0;
                ids.mId2 = 0x668e2ba;
                break;
            case 0x53f0707:
                nSelectedWindow = 0x5b218d8;
                ids.mId1 = 0x65f8fdb;
                if (IsWorldLayoutFlagSet(2)) {
                    ids.mId0 = 0x7a7b627;
                    ids.mId3 = 0x3dade1bb;
                } else {
                    ids.mId0 = 0x5b08712;
                }
                ids.mId2 = 0x668e2bb;
                break;
            default:
                break;
            }
        } else {
            if (mpEditorFlow->mpField4C) {
                IWindow_s00de_d5a0* pPage = mLayout.FindWindowByID(0x5b69a71, true);
                if (pPage)
                    pPage->v7C(true, true);
            }
            KillSetiEffects(0xd607a5a7, GetRecorderState());
        }
    } else if (nID > 0x5951103) {
        if (nID >= 0x6775e1f && nID <= 0x6775e23)
            KillSetiEffects(0xd607a5a7, GetRecorderState());
    } else if (nID != 0x5951103) {
        if (nID == 0x54045e3) {
            if (mpEditorFlow->mpField64) {
                IWindow_s00de_d5a0* pPage = mLayout.FindWindowByID(0x5b69a70, true);
                if (pPage)
                    pPage->v7C(true, true);
            }
            KillSetiEffects(0xd607a5a7, GetRecorderState());
        } else if (nID == 0x5404617) {
            if (mpEditorFlow->mpField70) {
                IWindow_s00de_d5a0* pPage = mLayout.FindWindowByID(0x5b69a72, true);
                if (pPage)
                    pPage->v7C(true, true);
            }
            KillSetiEffects(0xd607a5a7, GetRecorderState());
        }
    } else if (mFlowState == 0xb) {
        KillSetiEffects(0xd607a5a7, GetRecorderState());
    }

    IWindow_s00de_d5a0* pDescription = mLayout.FindWindowByID(0x5b82168, true);
    if (nSelectedWindow == 0) {
        if (pDescription)
            pDescription->v7C(true, true);
        return;
    }

    IWindow_s00de_d5a0* pAudio = GetSystemAT();
    uint32_t nAudioState = 0;
    if (pAudio)
        nAudioState = (uint32_t)pAudio->v20();
    KillSetiEffects(0xd607a5a7, nAudioState);
    if (pDescription)
        pDescription->v7C(true, false);

    bool bToggled = false;
    IWindow_s00de_d5a0* pSource = mLayout.FindWindowByID(nID, true);
    if (pSource)
        bToggled = ((uint32_t)pSource->v28() >> 1) & 1;

    IWindow_s00de_d5a0* pPage = mLayout.FindWindowByID(nSelectedWindow, true);
    if (pPage)
        pPage->v7C(true, true);

    IWindow_s00de_d5a0* pText = mLayout.FindWindowByID(ids.mId1, true);
    if (pText) {
        uint32_t nTable = bToggled ? ids.mId3 : 0x2b7a0311;
        uint32_t nKey = bToggled ? ids.mId0 : ids.mId2;
        cString_s00df_00b0 text(nTable, nKey, 0);
        pText->v80(text.c_str());
        text.~cString_s00df_00b0();
    }
}

// @ 0x00dedda0
bool cGalaxyGameEntryUIStateMachine_s00de_d5a0::SetLayout(const wchar_t* pLayoutName)
{
    mLayout.Shutdown(1);
    if (!pLayoutName)
        return false;

    bool bInit = mLayout.Init(pLayoutName, 1, true, 0x5b598fa);
    mIsLayoutBroken = bInit ? 0 : 1;

    const uint32_t nWindowIds[0x32] = { LAYOUT_WINDOW_IDS };
    for (int32_t i = 0; i < 0x32; ++i) {
        IWindow_s00de_d5a0* pWindow = mLayout.FindWindowByID(nWindowIds[i], true);
        if (pWindow)
            pWindow->v104(this);
    }

    IWindow_s00de_d5a0* pPreview = mLayout.FindWindowByID(0x5812792, true);
    if (pPreview)
        pPreview->v7C(true, false);

    cSPUILayeredObject_s00de_d5a0* pLayer =
        (cSPUILayeredObject_s00de_d5a0*)FUN_0080f730(GlobalBoundingBox());
    if (pLayer != mpLayeredObject) {
        if (pLayer)
            ((IWindow_s00de_d5a0*)pLayer)->v04();
        cSPUILayeredObject_s00de_d5a0* pOld = mpLayeredObject;
        mpLayeredObject = pLayer;
        if (pOld)
            ((IWindow_s00de_d5a0*)pOld)->v08();
    }

    pPreview = mLayout.FindWindowByID(0x5812792, true);
    if (pPreview)
        mpLayeredObject->FUN_0080dda0(pPreview, 1);

    PopulateContextMenu();

    IWindow_s00de_d5a0* pRoot = mLayout.FindWindowByID(0x5b744bc, true);
    if (pRoot) {
        IWindow_s00de_d5a0* pA = pRoot->vA8();
        IWindow_s00de_d5a0* pB = 0;
        if (pA)
            pB = (IWindow_s00de_d5a0*)pA->v0C(0x103c1908);
        IWindow_s00de_d5a0* pNew = 0;
        if (pB)
            pNew = (IWindow_s00de_d5a0*)pB->v10();
        if (pNew != mpWindow618) {
            if (pNew)
                pNew->v00();
            IWindow_s00de_d5a0* pOld = mpWindow618;
            mpWindow618 = pNew;
            if (pOld)
                pOld->v04();
        }
    }

    pRoot = mLayout.FindWindowByID(0x5b73f5b, true);
    if (pRoot) {
        IWindow_s00de_d5a0* pA = pRoot->vA8();
        IWindow_s00de_d5a0* pB = 0;
        if (pA)
            pB = (IWindow_s00de_d5a0*)pA->v0C(0x103c1908);
        IWindow_s00de_d5a0* pNew = 0;
        if (pB)
            pNew = (IWindow_s00de_d5a0*)pB->v10();
        if (pNew != mpWindow620) {
            if (pNew)
                pNew->v00();
            IWindow_s00de_d5a0* pOld = mpWindow620;
            mpWindow620 = pNew;
            if (pOld)
                pOld->v04();
        }
    }

    pRoot = mLayout.FindWindowByID(0x5b745cc, true);
    if (pRoot) {
        IWindow_s00de_d5a0* pA = pRoot->vA8();
        IWindow_s00de_d5a0* pB = 0;
        if (pA)
            pB = (IWindow_s00de_d5a0*)pA->v0C(0x103c1908);
        IWindow_s00de_d5a0* pNew = 0;
        if (pB)
            pNew = (IWindow_s00de_d5a0*)pB->v10();
        if (pNew != mpWindow61C) {
            if (pNew)
                pNew->v00();
            IWindow_s00de_d5a0* pOld = mpWindow61C;
            mpWindow61C = pNew;
            if (pOld)
                pOld->v04();
        }
    }

    pRoot = mLayout.FindWindowByID(0x57f74f6, true);
    if (pRoot) {
        IWindow_s00de_d5a0* pA = pRoot->vA8();
        IWindow_s00de_d5a0* pB = 0;
        if (pA)
            pB = (IWindow_s00de_d5a0*)pA->v0C(0x53eb526);
        int32_t nNew = 0;
        if (pB)
            nNew = ((DSub*)pB)->GetField10(0);
        if ((IWindow_s00de_d5a0*)nNew != mpWindow624) {
            if (nNew)
                ((IWindow_s00de_d5a0*)nNew)->v00();
            IWindow_s00de_d5a0* pOld = mpWindow624;
            mpWindow624 = (IWindow_s00de_d5a0*)nNew;
            if (pOld)
                pOld->v04();
        }
    }

    for (int32_t i = 0; i < 0x0b; ++i) {
        IWindow_s00de_d5a0* pWindow = mLayout.FindWindowByID(gWindowIdTable[i], true);
        if (pWindow)
            pWindow->v7C(true, false);
    }

    return bInit;
}

// @ 0x00dee2a0
void cGalaxyGameEntryUIStateMachine_s00de_d5a0::TearDownUI()
{
    if (IWindow_s00de_d5a0* pWindow = mpWindow618) {
        mpWindow618 = 0;
        pWindow->v04();
    }
    if (IWindow_s00de_d5a0* pWindow = mpWindow61C) {
        mpWindow61C = 0;
        pWindow->v04();
    }
    if (IWindow_s00de_d5a0* pWindow = mpWindow620) {
        mpWindow620 = 0;
        pWindow->v04();
    }
    if (IWindow_s00de_d5a0* pWindow = mpWindow624) {
        mpWindow624 = 0;
        pWindow->v04();
    }

    mIsLayoutBroken = 1;
    mLayout.Shutdown(1);
}

// @ 0x00dee320
cNotifyAttackListener::cNotifyAttackListener()
: cNotifyAttackListenerBase()
{
    mpVTable = (void*)g_147e618;
    *(uint32_t volatile*)&mField14 = 0;
    mField08 = 0;
    gNotifyListener = this;
    mField0C = 0;
    mField10 = 0;
}

// @ 0x00dee360
void cGalaxyGameEntryMode_s00de_d5a0::RefreshNotifyAttackToggle()
{
    char cValue = 0;
    cPropertyList_s00de_d5a0* pPreferences = (cPropertyList_s00de_d5a0*)gAppPreferences;
    if (pPreferences) {
        cProperty_s00de_d5a0* pProperty;
        if (pPreferences->FindProperty(0x80eaa93, &pProperty) && pProperty->mType == 1)
            cValue = *pProperty->GetBool();
    }

    IWindow_s00de_d5a0* pCheck = mpStateMachine->mLayout.FindWindowByID(0x809b720, true);
    if (pCheck)
        pCheck->v7C(true, cValue == 0);
}

// @ 0x00dee3d0
void cGalaxyGameEntryMode::ReleaseOwned()
{
    IWindow_s00de_d5a0* pStateMachine = (IWindow_s00de_d5a0*)mpStateMachine;
    if (pStateMachine)
        pStateMachine->v08();
    ReleaseRef(mpObject04);
    ReleaseRef(mpObject00);
}

// @ 0x00dee450
char SP::GalaxyUI::FUN_00dee450(int msg, void* ctx)
{
    if (msg == 0x625e26a) {
        if (mFlag70 != 0) {
            FUN_00de53d0(1);
            float m[9];
            memcpy_(m, &gDAT_16a1580, sizeof(m));
            void*     em  = EffectsManagerPtr();
            PanelIDs_s00de_e450* ids = gkGUI_PanelIDs_s00de_e450;
            if (ids->mpHandler != 0) {
                void* h = ids->mpHandler;
                ids->mpHandler = 0;
                ((VF0)(*(void***)h)[1])(h);
            }
            ((VF2P)(*(void***)em)[0x2c / 4])(em, &ids->mpHandler, 0x3d6ef67);
            if (ids->mpHandler != 0) {
                void* h = ids->mpHandler;
                ((VF1)(*(void***)h)[0x18 / 4])(h, (int)(size_t)ctx);
                ((VF1)(*(void***)h)[0x08 / 4])(h, 0);
            }
            void* w = mLayout.FindWindowByID(0x5384881, 1);
            ((VF2)(*(void***)w)[0x7c / 4])(w, 1, 1);
        }
        return 1;
    }
    if (msg == 0x5b5c746) {
        if (f5e0 == 0) {
            FUN_00de53d0(0);
            LaunchData_s00de_e450* d = (LaunchData_s00de_e450*)operator new(0x9c, "App", 0, 0, 0);
            if (d != 0) {
                void* app = APP_Ptr();
                LaunchData_s00de_e450* obj = d->Ctor();
                if (obj != 0) {
                    obj->f0c = f500;
                    obj->f10 = f504;
                    obj->f14 = f508;
                    obj->f18 = f50c;
                    obj->f90 = ((VFI)(*(void***)app)[0x38 / 4])(app);
                    obj->f88 = 0;
                    obj->f8c = ((VFI)(*(void***)app)[0x0c / 4])(app);
                    if (obj->f8c != 0)
                        ((VF0)(*(void***)(size_t)obj->f8c)[1])((void*)(size_t)obj->f8c);
                    obj->f94 = (uint32_t)(size_t)&gDAT_13f09b4;   // "Simulator"
                    obj->f98 = (uint32_t)(size_t)&gDAT_13ebc58;   // "App"
                    obj->f9c = 0;
                    Editor_Launch();
                    ((VF0)(*(void***)obj)[1])(obj);
                }
            }
            return 1;
        }
        f5e0 = f5e0 - 1;
        void* ms = MessageServerPtr();
        ((VF3)(*(void***)ms)[0x18 / 4])(ms, 0x5b5c746, 0, 0);
        return 1;
    }
    if (msg == 0x30c11c7 && mFlag70 != 0) {
        void* w = mLayout.FindWindowByID(0x5384881, 0);
        ((VF1)(*(void***)w)[0x7c / 4])(w, 1);
        if (((MsgCtx*)ctx)->mFlag44 == 0)
            ((VF1P)this->vtbl1[0])(&this->vtbl1, ((MsgCtx*)ctx)->mLocal);
        return 1;
    }
    return 1;
}

struct Res_s00de_e770 {
    virtual void AddRef();
    virtual void Release();
};
struct Img_s00de_e770 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); 
    virtual void v10(); 
    virtual void SetImage(int index, Res_s00de_e770* image);
};
struct Drawable_s00de_e770 {
    virtual void v00(); virtual void v04(); virtual void v08(); 
    virtual Img_s00de_e770* Cast(uint32_t iid);
};
struct Win_s00de_e770 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); 
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c(); 
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c(); 
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c(); 
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c(); 
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c(); 
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c(); 
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c(); 
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c(); 
    
    virtual void Invalidate();
    virtual void w94(); virtual void w98(); virtual void w9c(); virtual void wa0(); virtual void wa4(); 
    virtual Drawable_s00de_e770* GetDrawable();
};

// @ 0x00dee770
void SP::GalaxyUI::FUN_00dee770(uint32_t id, void* refObj)
{
    Win_s00de_e770* w = (Win_s00de_e770*)mLayout.FindWindowByID(id, 1);
    if (w == 0) return;
    Drawable_s00de_e770* d = w->GetDrawable();
    if (d == 0) return;
    Img_s00de_e770* img = d->Cast(0x103c1908);
    if (img == 0) return;
    Res_s00de_e770* res = 0;            // the original keeps it in id's argument slot
    CreateImageFromResource2(refObj, (void**)&res, 0, -1, -1);
    img->SetImage(0, res);
    w->Invalidate();
    if (res != 0)
        res->Release();
}

struct ImageRef_s00dee800 {
    void* mpImage;
    ImageRef_s00dee800() : mpImage(0) {}
    ~ImageRef_s00dee800() { if (mpImage) ((VF0)(*(void***)mpImage)[1])(mpImage); }
};
// @ 0x00dee800
void SP::GalaxyUI::FUN_00dee800(uint32_t id, uint32_t imageId)
{
    void* w = mLayout.FindWindowByID(id, 1);
    if (w == 0) return;
    void* d = ((VFP)(*(void***)w)[0xa8 / 4])(w);
    if (d == 0) return;
    void* obj = ((VFP1)(*(void***)d)[0x0c / 4])(d, 0x53eb526);
    if (obj == 0) return;
    ImageRef_s00dee800 image;
    CreateImageFromResource2((void*)(size_t)imageId, &image.mpImage, 0, -1, -1);
    ((UIDrawable*)obj)->SetImageIcon(0, image.mpImage);
    ((VF0)(*(void***)w)[0x90 / 4])(w);
}

// @ 0x00dee890
uint32_t __stdcall FUN_00dee890(void* editor)
{
    void*  list  = 0;
    FUN_004bafc0(editor, &list);
    void** listv = (void**)list;
    if (listv == 0)
        return 2;
    int count = (int)((char*)listv[0x27] - (char*)listv[0x26]) / 0x8c;
    int n = (count > 0x40) ? 0x40 : count;
    char hasBad = 0;
    char flag   = 0;
    for (int i = 0; i < n; ++i) {
        uint32_t r = FUN_00dec990(*(void**)((char*)listv[0x26] + i * 0x8c));
        if (r == 2) {
            hasBad = 1;
        } else if (r == 3) {
            flag = 1;
        } else if (r == 4) {
            flag = 1;
            hasBad = 1;
        }
    }
    uint32_t result = 0;
    if (hasBad)
        result = (flag == 0) ? 1 : 2;
    if (listv != 0)
        ((VF0)(*(void***)listv)[1])(listv);
    return result;
}

// @ 0x00dee9a0
void SP::GalaxyUI::FUN_00dee9a0(float a, float b)
{
    Rbtree* tree = &mMap40;
    RBNode_s00de_e450* end  = (RBNode_s00de_e450*)&tree->mpAnchor;
    RBNode_s00de_e450* n;
    for (n = (RBNode_s00de_e450*)tree->mpRoot; n != end; n = RBTreeIncrement(n)) {
        void* w = mLayout.FindWindowByID(n->mKey, 1);
        if (w == 0) continue;
        void** vt = *(void***)w;
        char   ok = (char)(((VFI)vt[0x28 / 4])(w) & 1);
        void*  c  = ((VFP)vt[0x10 / 4])(w);
        while (ok & 1) {
            if (c == 0) {
                float out[2];
                ((VFC8)vt[0xc8 / 4])(w, a, b, out);
                char hit = ((VFC2F)vt[0xbc / 4])(w, out[0], out[1]);
                if (hit == 0 && n->mFlag == 1) {
                    FUN_00ded920(n->mKey, 1);
                    n->mFlag = 0;
                }
                break;
            }
            void** cvt = *(void***)c;
            ok = (char)(((VFI)cvt[0x28 / 4])(c) & 1);
            c  = ((VFP)cvt[0x10 / 4])(c);
        }
    }
    for (n = (RBNode_s00de_e450*)tree->mpRoot; n != end; n = RBTreeIncrement(n)) {
        void* w = mLayout.FindWindowByID(n->mKey, 1);
        if (w == 0) continue;
        void** vt = *(void***)w;
        char   ok = (char)(((VFI)vt[0x28 / 4])(w) & 1);
        void*  c  = ((VFP)vt[0x10 / 4])(w);
        while (ok & 1) {
            if (c == 0) {
                float out[2];
                ((VFC8)vt[0xc8 / 4])(w, a, b, out);
                char hit = ((VFC2F)vt[0xbc / 4])(w, out[0], out[1]);
                if (hit != 0 && n->mFlag == 0) {
                    FUN_00ded920(n->mKey, 0);
                    n->mFlag = 1;
                }
                break;
            }
            void** cvt = *(void***)c;
            ok = (char)(((VFI)cvt[0x28 / 4])(c) & 1);
            c  = ((VFP)cvt[0x10 / 4])(c);
        }
    }
}

// @ 0x00deebc0
void* SP::GalaxyUI::FUN_00deebc0(unsigned flags)
{
    void* ref;
    this->vtbl0 = (void**)&gvtbl_notify;
    gDAT_16a1570 = 0;
    ref = this->mpRef14;
    if (ref != 0)
        ((VF0)((void**)*(void**)ref)[1])(ref);
    this->vtbl0 = (void**)&gvtbl_base;
    if (flags & 1)
        operator delete[](this);
    return this;
}

// @ 0x00deec00
void SP::Wrapper::FUN_00deec00(float a, float b, float c)
{
    GalaxyUI* p = this->mpP;
    if (p->mHoverFlag != 0) {
        p->FUN_00dee9a0(a, b);
    }
    (void)c;
}

// @ 0x00deed00
bool Record::FUN_00deed00(uint32_t key)
{
    struct Iter { void* node; void* end; } it;
    Hashtable* ht = &mHash;
    ht->find_(&it, &key);
    return it.node != ht->mTable[ht->mnBucketCount];
}

// @ 0x00deed40
void SP::GalaxyUI::FUN_00deed40()
{
    mSub.FUN_00e20e80();
    FUN_00dee2a0();
    if (mpRef14 != 0) {
        void* h = mpRef14;
        mpRef14 = 0;
        RemoveHandler(h, f18, f1c, f20, f24);
    }
    if (mpRef614 != 0) {
        void* r = mpRef614;
        mpRef614 = 0;
        ((VF0)(*(void***)r)[2])(r);
    }
    mMap520.reset_s00de_ed40();
    mMap40.reset_s00de_ed40();
}

// @ 0x00deede0
void SP::GalaxyUI::FUN_00deede0()
{
    GridObj* g = this->mpGrid;
    if (g == 0) return;
    // rebuild the grid's display name from the localized id, then (when the generator
    // handed back a different string object) copy that range over the grid's name
    void* tmp[3];                                      // eastl::wstring temp (begin/end/cap)
    void* gen  = FUN_004010a0(tmp, 0x51aa76bb);
    void* name = ((NameGen*)gen)->GetName();
    if (name != (void*)&g->mpName)
        ((WString_s00de_e450*)(void*)&g->mpName)->Assign(((void**)name)[0], ((void**)name)[1]);
    int tmpBytes = (int)((char*)tmp[1] - (char*)tmp[0]) & ~1;
    if (tmpBytes > 2 && tmp[0] != 0)
        operator delete[](tmp[0]);
    void* w = mLayout.FindWindowByID(0x7d275bb, 1);
    if (w == 0) return;
    void** wvt = *(void***)w;
    void*  img = ((VFP1)wvt[0x0c / 4])(w, 0xcf428691);
    if (img == 0) return;
    ((VF2P)(*(void***)img)[0x60 / 4])(img, g->mpName, 0);
}

// @ 0x00deee80
char SP::GalaxyUI::FUN_00deee80(int mode)
{
    if (mode != 0xb && mode != 1) {
        if (gkGUI_PanelIDs->mFlag == 0 &&
            FUN_00de5cb0(0x26b05664) == 0 &&
            mode == 6 &&
            gDAT_16a0f08 != 0)
            return 0;
        {
            GridObj* g = this->mpGrid;
            if (g == 0) return 0;
            Record*   rec = &this->mRecords[g->mIndex];
            Hashtable* ht = &rec->mHash;
            void* end = ht->mTable[ht->mnBucketCount];
            struct Iter { void* node; void* end; } it;
            uint32_t k = (uint32_t)mode;
            void* r = ht->find_(&it, &k);
            if (*(void**)r == end) return 0;
        }
    }
    return 1;
}

struct PanelIds_s00de_ef20 {
    uint32_t a, b, c;
    PanelIds_s00de_ef20() : a(0), b(0), c(0) {}
};
struct IntRbIter {
    RBNode_s00de_e450* mpNode;
    IntRbIter(RBNode_s00de_e450* p) : mpNode(p) {}
};
struct IntRbTree {
    IntRbIter find(const int32_t* pKey);   // 0x00e39fb0
};
struct PanelWindow_s00de_ef20 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78();
    virtual void SetVisible(int a, int b);
};

// @ 0x00deef20
void SP::GalaxyUI::FUN_00deef20(int key, void* map, unsigned b)
{
    RBNode_s00de_e450* node = ((IntRbTree*)map)->find(&key).mpNode;
    if (node == (RBNode_s00de_e450*)&((Rbtree*)map)->mpAnchor) return;
    ((PanelWindow_s00de_ef20*)mLayout.FindWindowByID(0x5384881, 1))->SetVisible(1, 0);
    gkGUI_PanelIDs_s00de_e450->FUN_00de5d00((void*)(size_t)node->mValue, this ? (void*)&this->field_08 : 0,
                                  (void*)mpGrid->mB0, PanelIds_s00de_ef20(), 0, (void*)(size_t)b, 0);
}

// @ 0x00deefb0
uint32_t SP::GalaxyUI::FUN_00deefb0(uint32_t key)
{
    GridObj* g = this->mpGrid;
    if (g != 0 && g->mIndex != 6) {
        Record*    rec = &this->mRecords[g->mIndex];
        Hashtable* ht  = &rec->mHash;
        struct Iter { void* node; void* end; } it;
        ht->find_(&it, &key);
        if (it.node != ht->mTable[ht->mnBucketCount])
            return ((HashPair*)it.node)->value;
    }
    return 0;
}

// @ 0x00def020
void SP::Wrapper::FUN_00def020()
{
    GalaxyUI* p = this->mpP;
    if (p != 0) {
        p->FUN_00deed40();
        p = this->mpP;
        if (p != 0)
            ((VF1)p->vtbl0[2])(p, 1);
        this->mpP = 0;
    }
}

// @ 0x00def050
char SP::GalaxyUI::FUN_00def050(void* nameObj)
{
    // NOTE: approximate reimplementation of the retail in-place wstring sanitation
    // (strip leading characters that are not alpha-numeric, then runs of separators).
    wchar16** s     = (wchar16**)nameObj;
    wchar16*  begin = s[0];
    wchar16*  end   = s[1];
    char      changed = 0;
    while (begin != end && !iswctype(*begin, 0x107)) {
        for (wchar16* p = begin; p + 1 != end; ++p)
            *p = p[1];
        if (end != begin) --end;
        changed = 1;
    }
    if (begin != end) {
        static const wchar16 kBad[] = { '.', ',', '/', '?', ']', '$', '[', '{',
                                        '\\', '|', ';', ':', '*', '\'', '"', 0 };
        wchar16* w = begin;
        while (w != end) {
            char bad = 0;
            for (int i = 0; kBad[i] != 0; ++i)
                if (*w == kBad[i]) { bad = 1; break; }
            if (bad) {
                changed = 1;
                wchar16* q = w;
                while (q != end && *q == *w) ++q;
                for (wchar16* p = q; p != end; ++p)
                    *(w + (p - q)) = *p;
                end -= (q - w);
            } else {
                ++w;
            }
        }
    }
    s[0] = begin;
    s[1] = end;
    return changed;
}

// @ 0x00def400
__declspec(noinline) bool __thiscall SP::cGalaxyGameEntryUIStateMachine_s00de_f400::FUN_00def400(u32 nText)
{
    return *(const wchar_t*)nText != 0;
}

// @ 0x00def5f0
eastl::cHashIterator __thiscall eastl::cHashTable::FUN_00def5f0(const wchar_t** ppKey)
{
    const wchar_t* pKey = *ppKey;
    uint32_t hash = 2166136261u;
    uint32_t ch = (uint32_t)*pKey;
    if (ch != 0) {
        do {
            hash *= 16777619u;
            ++pKey;
            hash ^= ch;
            ch = (uint32_t)*pKey;
        } while (ch != 0);
    }

    eastl::cHashIterator it;
    eastl::cHashNode** pBucket = &mppBuckets[hash % mBucketCount];
    eastl::cHashNode* pNode = *pBucket;
    while (pNode) {
        if (eastl::Locale_CompareKeys(*ppKey, pNode))
            break;
        pNode = pNode->mpNext;
    }
    if (pNode) {
        it.mpNode = pNode;
        it.mppBucket = pBucket;
    } else {
        it.mpNode = mppBuckets[mBucketCount];
        it.mppBucket = &mppBuckets[mBucketCount];
    }
    return it;
}

// @ 0x00def690
namespace SP {
struct HashTable_s00de_f400 {
    char      pad000[4];                 // +0x00
    void**    mpBuckets;                 // +0x04
    uint32_t  mnCount;                   // +0x08
    uint32_t  mnZero;                    // +0x0c
    void DoFreeNodes(void** pBuckets, uint32_t nCount);
};
void __thiscall cGalaxyGameEntryUIStateMachine_s00de_f400::FUN_00def690()
{
    char* self = (char*)this;

    void* p = *(void**)(self + 0x74);
    if (p != 0 && *(int*)((char*)p - 4) != 0)
        op_del_array(p);
    p = *(void**)(self + 0x60);
    if (p != 0 && *(int*)((char*)p - 4) != 0)
        op_del_array(p);

    HashTable_s00de_f400* h = (HashTable_s00de_f400*)(self + 0x40);
    h->DoFreeNodes(h->mpBuckets, h->mnCount);
    h->mnZero = 0;
    if (h->mnCount > 1)
        op_del_array(h->mpBuckets);

    h = (HashTable_s00de_f400*)(self + 0x20);
    h->DoFreeNodes(h->mpBuckets, h->mnCount);
    h->mnZero = 0;
    if (h->mnCount > 1)
        op_del_array(h->mpBuckets);

    h = (HashTable_s00de_f400*)self;
    h->DoFreeNodes(h->mpBuckets, h->mnCount);
    h->mnZero = 0;
    if (h->mnCount > 1)
        op_del_array(h->mpBuckets);
}
}  // namespace SP

// @ 0x00def750
namespace SP {
void __thiscall cGalaxyGameEntryUIStateMachine_s00de_f400::FUN_00def750(uint32_t id, uint32_t value)
{
    int idx = *(int*)(*(int*)((char*)this + 0x628) + 0xa8);
    char* pBase = (char*)this + 0x84 + idx * 0xc0;
    uint32_t key = id;
    LocaleLookup_s00de_f400* pLookup = (LocaleLookup_s00de_f400*)(pBase + 0x40);
    uint32_t* pId = pLookup->Find(&key);
    uint32_t found = *pId;
    IWindow_s00df_9650* w =
        ((SPUILayout_s00df_9650*)((char*)this + 0x28))->FindWindowByID(found, 1);
    if (w != 0) {
        void* pArg = (void*)value;
        w->Slot80(pArg);
        w->Slot7C(1, 1);
    }
}
}  // namespace SP

// @ 0x00def7c0
namespace SP {
void __thiscall cGalaxyGameEntryUIStateMachine_s00de_f400::FUN_00def7c0()
{
}
}  // namespace SP

// @ 0x00def8c0
namespace SP {
__declspec(noinline) void __thiscall cGalaxyGameEntryUIStateMachine_s00de_f400::UpdateNavigationControls()
{
    (void)*(volatile int*)this;
}
}  // namespace SP

void* __cdecl FUN_004010a0(void);                      // 0x004010a0 (returns the name generator)
class cSPNameGenerator_s005e_cf80 {
public:
    void* GetName(void* out, u32 key);                             // 0x005ecf80
};

struct NameString_s00df_fc80 {
    u32 mpBegin;
    u32 mpEnd;
    u32 mpCap;
    u32 mnPadC;
    NameString_s00df_fc80& operator=(const NameString_s00df_fc80& other)
    {
        if (&other != this)
            ((EaString16*)this)->Assign(other.mpBegin, other.mpEnd);
        return *this;
    }
    ~NameString_s00df_fc80()
    {
        if ((s32)((mpCap - mpBegin) & 0xfffffffe) > 2 && mpBegin != 0)
            op_del_array((void*)mpBegin);
    }
};

// @ 0x00defc00
namespace SP {
NameString_s00df_fc80 __thiscall cGalaxyGameEntryUIStateMachine_s00de_f400::FUN_00defc00()
{
    NameString_s00df_fc80 out;
    out.mpBegin = (int)&gEmptyA_1667bac;
    out.mpEnd = (int)&gEmptyA_1667bac;
    out.mpCap = (int)&gEmptyB_1667bae;
    u32 text;
    do {
        WString16 key;
        EaString16* found =
            (EaString16*)((cSPNameGenerator_s005e_cf80*)FUN_004010a0())->GetName(&key.mpBegin, 0x7e1310a);
        if (found != (EaString16*)&out)
            ((EaString16*)&out)->Assign(found->mpBegin, found->mpEnd);
        if ((s32)((key.mpCap - key.mpBegin) & 0xfffffffe) > 2 && key.mpBegin != 0)
            op_del_array((void*)key.mpBegin);
    text = out.mpBegin;
    } while (FUN_00def400(text));
    return out;
}
}  // namespace SP

// @ 0x00defc80
namespace SP {
void __thiscall cGalaxyGameEntryUIStateMachine_s00de_f400::MakeRandomName()
{
    char* self = (char*)this;
    if (*(void**)(self + 0x628) != 0) {
        *(NameString_s00df_fc80*)*(void**)(self + 0x628) = FUN_00defc00();

        IWindow_s00df_9650* w = ((SPUILayout_s00df_9650*)(self + 0x28))
                                    ->FindWindowByID(0x5400fa5, 1);
        if (w != 0) {
            IWindow_s00df_9650* o = (IWindow_s00df_9650*)w->Slot0C(0xcf428691);
            if (o != 0)
                o->Slot60((void*)(*(NameString_s00df_fc80**)(self + 0x628))->mpBegin, 0);
        }
    }
}
}  // namespace SP

struct SummaryTextServices {
    PV8
    virtual SummaryTextServices* Slot20();
    PV2
    virtual void Slot2C(const wchar_t* pText, NameString_s00df_fc80* pOut);
    PV
    virtual void Slot34(const wchar_t* pText, int32_t nFlags);
};

// @ 0x00defd10
namespace SP {
void __thiscall cGalaxyGameEntryUIStateMachine_s00de_f400::SetStateSummaryText(
    int32_t nField, uint32_t nKey, const wchar_t* pText)
{
    cString text(0x2b7a0311, nKey, 0);
    ((SummaryTextServices*)FUN_0067de40())->Slot20()->Slot34(pText, 0);

    NameString_s00df_fc80 detokenized;
    detokenized.mpBegin = (int)&gEmptyA_1667bac;
    detokenized.mpEnd = (int)&gEmptyA_1667bac;
    detokenized.mpCap = (int)&gEmptyB_1667bae;
    ((SummaryTextServices*)FUN_0067de40())->Slot20()->Slot2C(text.c_str(), &detokenized);
    FUN_00def750(nField, detokenized.mpBegin);
}
}  // namespace SP

// @ 0x00defdd0
namespace SP {
void __thiscall cGalaxyGameEntryUIStateMachine_s00de_f400::SelectTheme()
{
}
}  // namespace SP

// @ 0x00df00b0
namespace SP {
void __thiscall cGalaxyGameEntryUIStateMachine_s00de_f400::FillComboBoxes()
{
    cString_s00df_00b0 text;
    int nKind = *(int*)(*(int*)((char*)this + 0x628) + 0xa0);
    switch (nKind) {
    case 0:
        text = cString_s00df_00b0(0x2b7a0311, 0x5b08772, 0);
        break;
    case 1:
        text = cString_s00df_00b0(0x2b7a0311, 0x5b08773, 0);
        break;
    case 2:
        text = cString_s00df_00b0(0x2b7a0311, 0x5b08774, 0);
        break;
    }

    int idx = *(int*)(*(int*)((char*)this + 0x628));
    (void)idx;
    int idxp = *(int*)((char*)this + 0x628);
    if (idxp != 0 && *(int*)(idxp + 0xa8) != 6)
        SetStateSummaryText(5, 0x5b08775, text.c_str());
}
}  // namespace SP

// @ 0x00df0190
namespace SP {
void __thiscall cGalaxyGameEntryUIStateMachine_s00de_f400::UpdateSpecialitySummaryText()
{
}
}  // namespace SP

// @ 0x00df0280
void __thiscall SP::cGalaxyGameEntryUIStateMachine_s00df_0280::ShowPanel()
{
}

// @ 0x00df0670
void __thiscall SP::cGalaxyGameEntryUIStateMachine_s00df_0280::SetCurrentState(int32_t state)
{
}

// @ 0x00df0830
void __cdecl FUN_00df0830()
{
}

// @ 0x00df0980
void __thiscall SP::cGalaxyGameEntryUIStateMachine_s00df_0280::FUN_00df0980()
{
    SP::cGalaxyStateMachine* pMachine = mpStateMachine;
    pMachine->SetCurrentState(0);
    mpStateMachine->FUN_00dee2a0();
}

// @ 0x00df09a0
void __cdecl FUN_00df09a0()
{
}

// @ 0x00df0a40
void __thiscall cGalaxyGameEntryMode::FUN_00df0a40(uint32_t arg)
{
    FUN_00e00760(arg);
    cGalaxyGameEntryUIStateMachine_s00de_d5a0* sm = mpStateMachine;
    if (sm->mFlowState != 0) {
        IWindow_s00de_d5a0* w = sm->mLayout.FindWindowByID(0x5384881, 1);
        w->v7C(1, 1);
        ((SP::cGalaxyGameEntryUIStateMachine_s00de_f400*)sm)->UpdateNavigationControls();
        gkGUI_PanelIDs->FUN_00de53d0(1);
    }
    IWindow_s00de_d5a0* w2 = ((cSPUILayout_s00de_d5a0*)((char*)gkGUI_PanelIDs + 0x144))
                                 ->FindWindowByID(0x615a5ff, 1);
    if (w2 != 0)
        w2->v7C(1, 0);
    ((GlobalUI*)*(void**)((char*)gkGUI_PanelIDs + 0x184))->SetVisibility(0);
    RefreshNotifyAttackToggle();
}

// @ 0x00df0ad0
void __cdecl FUN_00df0ad0()
{
}

// @ 0x00df0c00
void __cdecl FUN_00df0c00()
{
}

// @ 0x00df0f20
void __cdecl FUN_00df0f20()
{
}

// @ 0x00df1ba0
namespace SP {
bool cGalaxyGameEntryUIStateMachine_s00df_10d0::FillStarterWorldCombo(EA::UTFWinControls::IWinComboBox_s00df_10d0* combo)
{
    if (combo == 0)
        return false;

    if (!AppSystem_s00df_10d0()->IsFeatureEnabled()) {
        combo->ToWindow()->SetFlag(1, false);
        return false;
    }

    PropListPtr propList;
    if (PropertyManager_s00df_10d0()->GetPropertyList(gNewGameFlowPropListID, 0, propList))
        combo->ToWindow()->SetFlag(1, gbFlag16a0d60);

    combo->RemoveAll();
    gpGGEGlobal->mStarterWorlds.clear();

    eastl::vector_s00df_10d0<uint32_t> ids;
    PropertyManager_s00df_10d0()->GetInstanceIDs(0xe38475d9, ids);

    unsigned count = (unsigned)(ids.mpEnd - ids.mpBegin);
    for (unsigned i = 0; i < count; i++) {
        PropListPtr world;
        if (PropertyManager_s00df_10d0()->GetPropertyList(ids[i], 0xe38475d9, world)) {
            string16_s00df_10d0 name;
            if (GetPropertyAsString16(world.get(), 0x121a6dca, &name)) {
                Property_s00df_10d0* prop;
                if (world.get() && world.get()->GetProperty(0xea288a88, prop) && prop->mType == 1 &&
                    *prop->GetValueBool()) {
                    string16_s00df_10d0 text(name);
                    WStr_Format(&name, kWStr_starLs, text.c_str());
                }
                combo->AddItem(name.c_str());
                gpGGEGlobal->mStarterWorlds.push_back(ids[i]);
            } else {
                // the original renders a numeric fallback here and drops the result
                WStr_Format(&name, kWStr_0x08d, ids[i]);
            }
        }
    }
    return true;
}
}  // namespace SP

// @ 0x00df1e70
void SP::cGalaxyGameEntryUIStateMachine_s00df_1e70::GetRandomKey(KeyVec* pKeys)
{
    KeyVec matches;
    KeyVec filtered;

    matches.mpBegin = nullptr;
    matches.mpEnd = nullptr;
    matches.mpCap = nullptr;
    filtered.mpBegin = nullptr;
    filtered.mpEnd = nullptr;
    filtered.mpCap = nullptr;

    if (mpModel->mnFieldB0 != 0) {
        cObjectTemplateDB* pDatabase = ObjectTemplateDB();
        cMatchConstraint first(0);
        cMatchConstraint second(0x3cc89b1, 0, mpModel->mnFieldB0);

        pDatabase->mpVtbl->mpfnFindMatches(pDatabase, &matches, first, second);

        for (Key* pKey = pKeys->mpBegin; pKey != pKeys->mpEnd; ++pKey) {
            for (Key* pMatch = matches.mpBegin; pMatch != matches.mpEnd; ++pMatch) {
                if (pMatch->mnA == pKey->mnA && pMatch->mnB == pKey->mnB &&
                    pMatch->mnC == pKey->mnC) {
                    if (filtered.mpEnd < filtered.mpCap) {
                        *filtered.mpEnd = *pMatch;
                        ++filtered.mpEnd;
                    } else {
                        filtered.DoInsertKey(filtered.mpEnd, *pMatch);
                    }
                    break;
                }
            }
        }

        if (filtered.mpBegin != filtered.mpEnd)
            *pKeys = filtered;
    }

    if (matches.mpBegin != nullptr)
        operator_delete_array(matches.mpBegin);
    if (filtered.mpBegin != nullptr)
        operator_delete_array(filtered.mpBegin);
}

// @ 0x00df21d0
void SP::cGalaxyGameEntryUIStateMachine_s00df_1e70::OnAssetBrowserSelection(Key* pKey)
{
    if (mpModel == nullptr)
        return;

    cNewGameModePanel_s00df_1e70* pPanel = &maModePanels[mpModel->mnFieldA4];
    int32_t nWindowID = 0;
    int32_t nDrawableID = 0;

    if (pKey->mnA == 0)
        return;

    if (!FUN_00ded0b0(pKey))
        return;

    if (mnPendingAssetAction == 0x54045ce) {
        mpModel->mKey4C = *pKey;

        cButtonDrawable param;
        param.mKey.mnA = pKey->mnA;
        param.mKey.mnB = 0x2f7d0004;
        param.mKey.mnC = pKey->mnC;
        UpdateButtonStdDrawable(0x65fbfa0, &param);

        nWindowID = pPanel->mnWindowIDA0;
        nDrawableID = 0x5b744bc;
        UpdateSummaryCreatureName();
        FUN_00ded030();
        UpdateLocks();
    } else if (mnPendingAssetAction == 0x54045e3) {
        mpModel->mKey64 = *pKey;

        cButtonDrawable param;
        param.mKey.mnA = 0x5cc02f6;
        param.mKey.mnB = 1;
        param.mKey.mnC = 0;

        nWindowID = pPanel->mnWindowIDA4;
        nDrawableID = 0x5b745cc;
        UpdateLocks();

        UIEventQueue()->OnCommand(0x5cc02f6);
        UIEventQueue()->OnSelect(pKey, &param.mKey);
    } else if (mnPendingAssetAction == 0x5404617) {
        mpModel->mKey70 = *pKey;

        nWindowID = pPanel->mnWindowIDA8;
        nDrawableID = 0x5b73f5b;
        UpdateLocks();
    }

    if (mnPendingAssetAction != 0 && nDrawableID != 0) {
        cButtonDrawable param;
        param.mKey.mnA = pKey->mnA;
        param.mKey.mnB = 0x2f7d0004;
        param.mKey.mnC = pKey->mnC;
        UpdateButtonStdDrawable(nDrawableID, &param);
        mnPendingAssetAction = 0;
    }

    if (nWindowID != 0) {
        cUIWindow_s00df_1e70* pWindow = mLayout.FindWindowByID(nWindowID, 1);
        pWindow->Show(1, 0);
    }

    UpdateNavigationControls();
}

// @ 0x00df23b0
void SP::cGalaxyGameEntryUIStateMachine_s00df_1e70::DoStartNewGame(int32_t nElapsedMs)
{
    if (mbField70 != 0) {
        if (!FUN_00dec4a0())
            return;

        mLayout.FindWindowByID(0x5384881, 1)->Show(1, 0);
        mLayout.FindWindowByID(0x5812792, 1)->Show(1, 0);
        SetCurrentState(0);
        FUN_00dee2a0();
        gpGameUI->SetModeObject(mpModel);
        mStateList.Reset();
        FUN_00b3d360_s00df_1e70()->DoUpdate();
        gpGameMode_s00df_1e70->LoadMode(0xc, 0);
        mpModel = nullptr;
        return;
    }

    float afPair[2];
    FUN_00804ed0(&afPair[0], &afPair[1]);
    FUN_00dee9a0(afPair[1], afPair[0]);

    mStateList.Remove(nElapsedMs);
    FUN_00b3d490(nElapsedMs)->Update();

    if (mnCurrentState != 0xc)
        return;

    if (mTimer.mnTimeLow == 0 && mTimer.mnTimeHigh == 0)
        mTimer.Restart();

    long long nElapsed = mTimer.GetElapsedTime();
    if ((float)(uint64_t)nElapsed * g_fElapsedTimeScale > 1.0f) {
        mTimer.SetBoolProperty();
        if (maModePanels[6].mnField10 == 0) {
            SetCurrentState(1);
            return;
        }
        SetCurrentState(mpStateListBegin[0]);
    }
}

// @ 0x00df2550
void SP::cGalaxyGameEntryUIStateMachine_s00df_1e70::SelectNextState()
{
    int32_t nCurrent = mnCurrentState;
    uint32_t nIndex = 0;

    if (nCurrent != 1) {
        uint32_t nCount = (uint32_t)(mpStateListEnd - mpStateListBegin);
        while (nIndex < nCount) {
            if (mpStateListBegin[nIndex] == nCurrent)
                break;
            ++nIndex;
        }
        if (nIndex == nCount)
            return;
        ++nIndex;
    }

    uint32_t nCount = (uint32_t)(mpStateListEnd - mpStateListBegin);
    if (nIndex >= nCount)
        return;

    for (;;) {
        if (nIndex >= nCount)
            return;
        if (FUN_00deee80(mpStateListBegin[nIndex]))
            break;
        ++nIndex;
    }

    SetCurrentState(mpStateListBegin[nIndex]);
    mLayout.FindWindowByID(0x5384881, 1)->OnClick();

    cUIWindow_s00df_1e70* pWindow = mLayout.FindWindowByID(0x5944089, 1);
    if (pWindow == nullptr)
        return;

    if (nIndex == nCount - 1)
        mLayout.FindWindowByID(0x5944089, 1)->Show(1, 0);
    else
        mLayout.FindWindowByID(0x5944089, 1)->Show(1, 1);
}

// @ 0x00df2660
void SP::cGalaxyGameEntryUIStateMachine_s00df_1e70::SelectPreviousState()
{
    uint32_t nIndex = 0;

    if ((uint32_t)(mpStateListEnd - mpStateListBegin) != 0) {
        int32_t nCurrent = mnCurrentState;
        int32_t* pState = mpStateListBegin;
        do {
            if (*pState == nCurrent)
                break;
            ++nIndex;
            ++pState;
        } while (nIndex < (uint32_t)(mpStateListEnd - mpStateListBegin));

        if (nIndex != 0 && nCurrent != 2 && nCurrent != 3 &&
            nIndex != (uint32_t)(mpStateListEnd - mpStateListBegin)) {
            int32_t nPrevious = (int32_t)nIndex - 1;
            if (nPrevious < 0)
                return;

            for (;;) {
                if (FUN_00deee80(mpStateListBegin[nPrevious]))
                    break;
                --nPrevious;
                if (nPrevious < 0)
                    return;
            }

            SetCurrentState(mpStateListBegin[nPrevious]);
            mLayout.FindWindowByID(0x5384881, 1)->OnClick();

            if (mLayout.FindWindowByID(0x5944089, 1) == nullptr)
                return;

            mLayout.FindWindowByID(0x5944089, 1)->Show(1, 1);
            return;
        }
        return;
    }

    SetCurrentState(1);
    mLayout.FindWindowByID(0x5384881, 1)->OnClick();
}

// @ 0x00df2770
void SP::cGalaxyGameEntryUIStateMachine_s00df_1e70::OnModeSelection(int32_t nModeID)
{
    int32_t nOldValue = mpModel->mnField90;
    int32_t anModeIDs[6] = {0x614c680, 0x614c681, 0x614c682, 0, 2, 1};

    for (int32_t i = 0; i < 3; ++i) {
        int32_t nID = anModeIDs[i];
        cUIWindow_s00df_1e70* pWindow = mLayout.FindWindowByID(nID, 1);
        if (pWindow == nullptr)
            continue;

        cUIWindow_s00df_1e70* pButton = pWindow->FindChild(0x8ed27e7a);
        if (pButton == nullptr)
            continue;

        if (nID == nModeID) {
            mpModel->mnField90 = anModeIDs[i + 3];
            pButton->SetFlag(4, 1);
        } else {
            pButton->SetFlag(4, 0);
        }
    }

    if (mpModel != nullptr && mpModel->mnFieldA4 != 6 &&
        nOldValue != mpModel->mnField90) {
        mpModel->mKey64.mnA = 0;
        mpModel->mKey64.mnB = 0;
        mpModel->mKey64.mnC = 0;

        cUIWindow_s00df_1e70* pWindow = mLayout.FindWindowByID(0x5b745cc, 1);
        cUIWindow_s00df_1e70* pControl = pWindow->GetContent();
        if (pControl != nullptr)
            pControl = pControl->FindChild(0x103c1908);
        pControl->SetParams(0, mStateList.mnField14);

        cNewGameModePanel_s00df_1e70* pPanel = &maModePanels[mpModel->mnFieldA4];
        mLayout.FindWindowByID(pPanel->mnWindowIDA4, 1)->Show(1, 1);
        mLayout.FindWindowByID(0x5b69a70, 1)->Show(1, 0);

        pWindow = mLayout.FindWindowByID(0x59461b0, 1);
        if (pWindow != nullptr && ((pWindow->GetFlags() >> 2) & 1) != 0)
            ToggleAssetLock(0x59461b0);
    }

    UpdateSpecialitySummaryText();
}

// @ 0x00df2920
void SP::cGalaxyGameEntryUIStateMachine_s00df_1e70::OnSummarySelection(int32_t nModeID)
{
    uint32_t nOffset = 0;
    int32_t anModeIDs[6] = {0x6149007, 0x6149008, 0x6149009, 0, 1, 2};

    for (; nOffset < 3 * sizeof(int32_t); nOffset += sizeof(int32_t)) {
        int32_t nID = *(const int32_t*)((const uint8_t*)anModeIDs + nOffset);
        cUIWindow_s00df_1e70* pWindow = mLayout.FindWindowByID(nID, 1);
        if (pWindow == nullptr)
            continue;

        cUIWindow_s00df_1e70* pButton = pWindow->FindChild(0x8ed27e7a);
        if (pButton == nullptr)
            continue;

        if (nID == nModeID) {
            mpModel->mnFieldA0 =
                *(const int32_t*)((const uint8_t*)anModeIDs + nOffset + 3 * sizeof(int32_t));
            pButton->SetFlag(4, 1);
        } else {
            pButton->SetFlag(4, 0);
        }
    }

    FillComboBoxes();
}

// @ 0x00df29d0
void cGalaxyGameEntryScreen::Update(float fDelta)
{
    if (mpStateMachine != nullptr && mpStateMachine->mbField80 != 0)
        mpStateMachine->SetLayout(gsNewGameFlowLayout);

    if (mbStartRequested) {
        if (GetSetting4()->mbField1C == 0) {
            mbStartRequested = 0;
            gpGameMode_s00df_1e70->SetGuideState(0);
            gpGameMode_s00df_1e70->SetGuideState(1);
        }
    }

    long long nMilliseconds = (long long)(fDelta * g_fMillisecondsPerSecond);
    mpStateMachine->DoStartNewGame((int32_t)nMilliseconds);
}

// @ 0x00df2a60
void SP::cGalaxyGameEntryUIStateMachine_s00df_1e70::PickRandomByMode(int32_t nPendingAction, uint32_t nFilterValue, Key* pBaseKey)
{
    KeyVec keys;
    keys.mpBegin = nullptr;
    keys.mpEnd = nullptr;
    keys.mpCap = nullptr;

    cObjectTemplateDB* pDatabase = ObjectTemplateDB();
    cMatchConstraint first(0);
    cMatchConstraint second(0x2dc9d1e, 0, (int32_t)nFilterValue);

    pDatabase->mpVtbl->mpfnFindMatches(pDatabase, &keys, first, second);

    GetRandomKey(&keys);

    if (keys.mpBegin != keys.mpEnd) {
        Key key;
        FUN_00de3d40(&key, &keys, pBaseKey);
        if (key.mnA != 0) {
            mnPendingAssetAction = nPendingAction;
            OnAssetBrowserSelection(&key);
        }
    }

    if (keys.mpBegin != nullptr)
        operator_delete_array(keys.mpBegin);
}

// @ 0x00df2bb0
void SP::cGalaxyGameEntryUIStateMachine_s00df_1e70::PickRandomCreature()
{
    cNewGameModePanel_s00df_1e70* pPanel = &maModePanels[mpModel->mnFieldA4];

    if (pPanel->mpValuesBegin != pPanel->mpValuesEnd) {
        uint32_t nCount = (uint32_t)(pPanel->mpValuesEnd - pPanel->mpValuesBegin);
        uint32_t nIndex = gRandom.RandomUint32Uniform(nCount);

        Key key;
        key.mnA = pPanel->mpValuesBegin[nIndex];
        key.mnB = 0;
        key.mnC = (uint32_t)pPanel->mnFieldAC;
        mnPendingAssetAction = 0x54045ce;
        OnAssetBrowserSelection(&key);
        return;
    }

    if (pPanel->mnComboValue == 0)
        return;

    KeyVec keys;
    keys.mpBegin = nullptr;
    keys.mpEnd = nullptr;
    keys.mpCap = nullptr;

    cObjectTemplateDB* pDatabase = ObjectTemplateDB();
    cMatchConstraint first(0);
    cMatchConstraint second(0x54a32960, 0, 1);
    cMatchConstraint third(0x52def3f, 0, pPanel->mnComboValue);

    pDatabase->mpVtbl->mpfnFindMatches(pDatabase, &keys, first, second, third);

    GetRandomKey(&keys);

    if (keys.mpBegin != keys.mpEnd) {
        Key key;
        FUN_00de3d40(&key, &keys, &mpModel->mKey4C);
        if (key.mnA != 0) {
            mnPendingAssetAction = 0x54045ce;
            OnAssetBrowserSelection(&key);
        }
    }

    if (keys.mpBegin != nullptr)
        operator_delete_array(keys.mpBegin);
}

// @ 0x00df2d60
void SP::cGalaxyGameEntryUIStateMachine_s00df_1e70::PickRandomBuilding()
{
    PickRandomByMode(0x5404617, 0x99e92f05, &mpModel->mKey70);
}

// @ 0x00df2d80
void StateMachine::PickRandomVehicle()
{
    GameEntry_s00df_2d80* p = this->mEntry;
    switch (p->mA4) {
    case 4:
        switch (p->m90) {
        case 0:
            this->PickRandomByMode(0x54045e3, 0x7d433fad, &p->m64);
            return;
        case 1:
            this->PickRandomByMode(0x54045e3, 0x9ad7d4aa, &p->m64);
            return;
        case 2:
            this->PickRandomByMode(0x54045e3, 0xf670aa43, &p->m64);
            return;
        }
        break;
    case 5:
        this->PickRandomByMode(0x54045e3, 0x98e03c0d, &p->m64);
        return;
    }
    this->PickRandomByMode(0x54045e3, (int)this, &p->m64);
}

// @ 0x00df2e20
void Impl::TestEditorToGame(int* p)
{
    IWindow_s00df_2d80* w = this->mLayout.FindWindowByID(0x5384881, 1);
    w->Slot7C(1, 1);
    kGUI_PanelIDs_s00df_2d80->Fn53d0(1);
    kGUI_PanelIDs_s00df_2d80->m103 = 1;
    if (*p != 0) {
        char b = (this->m6c == 2);
        if (this->m5e0 == 0x54045ce && (b || DAT_016a0f78 != 0))
            b = 1;
        StateMachine* sm = (StateMachine*)((char*)this - 8);
        sm->OnAssetBrowserSelection((Key_s00df_2d80*)p);
        if (b)
            sm->SelectNextState();
    }
}

// @ 0x00df2ea0
void StateMachine::SetLevel(int level)
{
    GameEntry_s00df_2d80* p = this->mEntry;
    if (p != 0) {
        p->mA8 = level;
        p->mA4 = level;
        if (p->m20 != p->m24) {
            *p->m20 = 0;
            p->m24 = p->m20;
        }
        p->m70.a = 0;
        p->m70.b = 0;
        p->m70.c = 0;
        p->m4c = p->m70;
        p->m64 = p->m4c;
        this->SelectTheme(0);
    }

    unsigned ids[5];
    ids[0] = 0x5a72f76;
    ids[1] = 0x6149c87;
    ids[2] = 0x5a72f77;
    ids[3] = 0x5a72f78;
    ids[4] = 0x5a72f79;
    for (int i = 0; i < 5; i++)
        this->mLayout.FindWindowByID(ids[i], 1)->Slot7C(1, 0);

    IWindow_s00df_2d80* w = this->mLayout.FindWindowByID(0x62f1f94, 1);
    if (w != 0)
        w->Slot7C(1, 0);

    cString summary;

    tNewGameFlow* flow = &this->mFlow[level];
    if (!HashHasKey(&flow->mMap20, 8) && !HashHasKey(&flow->mMap20, 3))
        this->PickRandomCreature();

    switch (level) {
    case 0: summary = cString(0x2b7a0311, 0x5b08702, 0); this->ShowSkin(0x5b218d1); break;
    case 1: summary = cString(0x2b7a0311, 0x5b08703, 0); this->ShowSkin(0x5b218c9); break;
    case 2: summary = cString(0x2b7a0311, 0x5b08704, 0); this->ShowSkin(0x5adf8e2); break;
    case 4: summary = cString(0x2b7a0311, 0x5b08705, 0); this->ShowSkin(0x5b8a143); break;
    case 5: summary = cString(0x2b7a0311, 0x5b08706, 0); this->ShowSkin(0x5b218d9); break;
    }

    this->SetStateSummaryText(1, 0x5b08739, summary.GetText());
    this->SelectNextState();

    this->mLayout.FindWindowByID(0x5af2b91, 1);

    for (unsigned i = 0; i < 5; i++) {
        IWindow_s00df_2d80* flagW = this->mLayout.FindWindowByID(kUIFlagIds[i], 1);
        if (flagW != 0)
            flagW->Slot7C(1, i < flow->m88);
        IWindow_s00df_2d80* btnW = this->mLayout.FindWindowByID(kUIPanelButtonIds[i], 1);
        if (btnW != 0)
            btnW->Slot7C(1, i < flow->m88);
    }

    unsigned* begin = flow->m60;
    unsigned count = (unsigned)(flow->m64 - flow->m60) >> 2;
    for (unsigned i = 0; i < count; i += 2) {
        unsigned* e = begin + i;
        IWindow_s00df_2d80* lw = this->mLayout.FindWindowByID(e[0], 1);
        cString text(0x2b7a0311, e[1], 0);
        if (lw != 0)
            lw->Slot80(text.GetText());
    }

    this->ResetAssetButtons(1, 1, 1);
}

// @ 0x00df32d0
void StateMachine::Init(int flowId)
{
    int mode = this->mEntry->mA4;
    if (mode == 0) {
        int want = (flowId == 0x6775e23 || flowId == 0x6775e20) ? 1 : 0;
        do {
            this->PickRandomCreature();
        } while (this->FnEE890(&this->mEntry->m4c) != want);
        this->SelectNextState();
        return;
    }

    bool herbivore = (this->m81 != 0) && (mode == 1);

    int sel = 0;
    Hashtable_s00df_2d80* table = 0;
    switch (flowId) {
    case 0x6775e1f:
    case 0x6775e22:
        sel = 1;
        table = herbivore ? &this->mHash[4] : &this->mHash[1];
        break;
    case 0x6775e20:
    case 0x6775e23:
        sel = 0;
        table = herbivore ? &this->mHash[5] : &this->mHash[2];
        break;
    case 0x6775e21:
        sel = 2;
        table = herbivore ? &this->mHash[6] : &this->mHash[3];
        break;
    }

    int row = (mode == 1) ? 1 : (mode == 2) ? 2 : 0;
    unsigned panelId = kGUI_PanelIDs_s00df_2d80->mPanelIds[sel + 3 * row];
    this->m5e8 = 0x54045ce;
    this->FnEF20(this->mEntry->mA8, table, panelId);
}

// @ 0x00df3a70
void __fastcall FUN_00df3a70(Holder* h)
{
    Sim* o = (Sim*)operator_new(0x630, "Simulator", 0, 0, 0, 0);
    if (o)
        o = o->Ctor();
    else
        o = 0;
    h->m8 = o;
    o->Fn3410();
}

// @ 0x00df3ab0
void StateMachine::PickRandomAssets(char flag)
{
    if (this->mEntry == 0)
        return;

    IWindow_s00df_2d80* w = this->mLayout.FindWindowByID(0x59461b1, 1);
    u8 bit = w != 0 ? (u8)((w->Slot2C() >> 2) & 1) : 0;
    if (w == 0 || bit == 0) {
        IWindow_s00df_2d80* w2 = this->mLayout.FindWindowByID(0x54045ce, 1);
        if ((w2->Slot28() & 1) != 0 && (flag != 0 || this->mEntry->m4c.a == 0))
            this->PickRandomCreature();
    }

    w = this->mLayout.FindWindowByID(0x59461b0, 1);
    u8 bit2 = w != 0 ? (u8)((w->Slot2C() >> 2) & 1) : 0;
    if (w == 0 || bit2 == 0) {
        IWindow_s00df_2d80* w2 = this->mLayout.FindWindowByID(0x54045e3, 1);
        if ((w2->Slot28() & 1) != 0 && (flag != 0 || this->mEntry->m64.a == 0))
            this->PickRandomVehicle();
    }

    w = this->mLayout.FindWindowByID(0x59461b2, 1);
    u8 bit3 = w != 0 ? (u8)((w->Slot2C() >> 2) & 1) : 0;
    if (w == 0 || bit3 == 0) {
        IWindow_s00df_2d80* w2 = this->mLayout.FindWindowByID(0x5404617, 1);
        if ((w2->Slot28() & 1) != 0 && (flag != 0 || this->mEntry->m70.a == 0))
            this->PickRandomByMode(0x5404617, 0x99e92f05, &this->mEntry->m70);
    }
}

// @ 0x00df3be0
void cGalaxyGameEntryUIStateMachine_s00df_3be0::HandleEvent(uint32_t id)
{
    switch (id) {
    case 0x5a725b4:
        KillSetiEffects(0x91be3241, ATState());
        MakeRandomName();
        SetStateSummaryText(4, 0x5b08740, mpGameInfo->m00);
        UpdateNavigationControls();
        return;
    case 0x54045e3: {
        mCurrentButton = 0x54045e3;
        if (mpGameInfo->mA8 == 5) {
            mLayout.FindWindowByID(0x5384881, true)->SetFlag(1, false);
            gpGGE_s00df_3be0->Unk_de5d00(0x9c5c0628, &mCallback, mpGameInfo->mB0, Zero3(), 0, 0, 0);
        } else {
            mLayout.FindWindowByID(0x5384881, true)->SetFlag(1, false);
            gpGGE_s00df_3be0->Unk_de5d00(kLevelWindowIDs[mpGameInfo->m90], &mCallback, mpGameInfo->mB0, Zero3(), 0, 0, 0);
        }
        UpdateNavigationControls();
        return;
    }
    case 0x5384d05:
        KillSetiEffects(0xed10ce15, GetRecorderState_s00df_3be0());
        Unk_df2550();
        UpdateNavigationControls();
        return;
    case 0x53f06e1:
        KillSetiEffects(0x8e82b51c, GetRecorderState_s00df_3be0());
        SetLevel(0);
        UpdateNavigationControls();
        return;
    case 0x53f06ee:
        KillSetiEffects(0x8e82b51c, GetRecorderState_s00df_3be0());
        SetLevel(1);
        UpdateNavigationControls();
        return;
    case 0x53f06f5:
        KillSetiEffects(0x8e82b51c, GetRecorderState_s00df_3be0());
        SetLevel(2);
        UpdateNavigationControls();
        return;
    case 0x53f06fc:
        KillSetiEffects(0x8e82b51c, GetRecorderState_s00df_3be0());
        SetLevel(4);
        UpdateNavigationControls();
        return;
    case 0x53f0707:
        KillSetiEffects(0x8e82b51c, GetRecorderState_s00df_3be0());
        SetLevel(5);
        UpdateNavigationControls();
        return;
    case 0x54045ce:
        mCurrentButton = 0x54045ce;
        Unk_deef20(mpGameInfo->mA8, &m520, 0);
        UpdateNavigationControls();
        return;
    case 0x5404617: {
        mCurrentButton = 0x5404617;
        mLayout.FindWindowByID(0x5384881, true)->SetFlag(1, false);
        gpGGE_s00df_3be0->Unk_de5d00(0x695cbb72, &mCallback, mpGameInfo->mB0, Zero3(), 0, 0, 0);
        UpdateNavigationControls();
        return;
    }
    case 0x5933fe0:
        KillSetiEffects(0xed10ce15, GetRecorderState_s00df_3be0());
        Unk_df2660();
        UpdateNavigationControls();
        return;
    case 0x59434c0:
    case 0x6451450:
        KillSetiEffects(0x91be3241, GetRecorderState_s00df_3be0());
        PickRandomAssets(1);
        UpdateNavigationControls();
        return;
    case 0x59434c1:
        KillSetiEffects(0x91be3241, GetRecorderState_s00df_3be0());
        if (!Unk_dec540(0x59461b0)) {
            if (mLayout.FindWindowByID(0x54045e3, true)->IsVisible() & 1)
                PickRandomVehicle();
        }
        if (!Unk_dec540(0x59461b2)) {
            if (mLayout.FindWindowByID(0x5404617, true)->IsVisible() & 1)
                PickRandomBuilding();
        }
        UpdateNavigationControls();
        return;
    case 0x59461b0:
    case 0x59461b1:
    case 0x59461b2:
        KillSetiEffects(0xa59524f9, GetRecorderState_s00df_3be0());
        UpdateNavigationControls();
        UpdateNavigationControls();
        return;
    case 0x5951103:
        KillSetiEffects(0xddd740f9, GetRecorderState_s00df_3be0());
        mb70 = 1;
        UpdateNavigationControls();
        return;
    case 0x595e0a8: {
        IRefObj_s00df_3be0* p = gpGGE_s00df_3be0->m19c;
        if (p) {
            p->v3(1);
            p = gpGGE_s00df_3be0->m19c;
            if (p) {
                gpGGE_s00df_3be0->m19c = 0;
                p->v1();
            }
        }
        KillSetiEffects(0xb7a63c50, GetRecorderState_s00df_3be0());
        void* q = gpGGE_s00df_3be0->m198;
        if (q)
            ((DeadEnd*)q)->Fn_dde570();
        SetCurrentState(0);
        gpGGE_s00df_3be0->Unk_de86d0(2, 0);
        UpdateNavigationControls();
        return;
    }
    case 0x6149007:
    case 0x6149008:
    case 0x6149009:
        KillSetiEffects(0x216a4ce, GetRecorderState_s00df_3be0());
        SetupPanelA(id);
        UpdateNavigationControls();
        return;
    case 0x614c680:
    case 0x614c681:
    case 0x614c682:
        KillSetiEffects(0x216a4ce, GetRecorderState_s00df_3be0());
        SetupPanelB(id);
        UpdateNavigationControls();
        return;
    case 0x6451451:
        KillSetiEffects(0x91be3241, GetRecorderState_s00df_3be0());
        if (!Unk_dec540(0x59461b1)) {
            if (mLayout.FindWindowByID(0x54045ce, true)->IsVisible() & 1)
                PickRandomCreature();
        }
        UpdateNavigationControls();
        return;
    case 0x6775e1f:
    case 0x6775e20:
    case 0x6775e21:
    case 0x6775e22:
    case 0x6775e23:
        KillSetiEffects(0xed10ce15, ATState());
        Init(id);
        UpdateNavigationControls();
        return;
    case 0x7d27876:
        KillSetiEffects(0x91be3241, GetRecorderState_s00df_3be0());
        Unk_deede0();
        UpdateNavigationControls();
        return;
    case 0x95964773:
    case 0x95964776:
    case 0x95964779:
        KillSetiEffects(0xe72fd2be, GetRecorderState_s00df_3be0());
        EditExistingAsset(id);
        UpdateNavigationControls();
        return;
    case 0x95964775:
    case 0x95964778:
    case 0x9596477b:
        KillSetiEffects(0xe72fd2be, GetRecorderState_s00df_3be0());
        MakeNewAsset(id);
        UpdateNavigationControls();
        return;
    case 0x95964774:
    case 0x95964777:
    case 0x9596477a:
        KillSetiEffects(0xe72fd2be, ATState());
        LoadAsset(id);
        UpdateNavigationControls();
        return;
    default:
        break;
    }
    UpdateNavigationControls();
}

// @ 0x00df43d0
bool cGalaxyGameEntryUIStateMachine_s00df_3be0::BeginNewGameFlow(uint32_t unused, GalaxyEvent* e)
{
    if (e->type == 0x685a2b9) {
        KillSetiEffects(0xb0cc7e7, ATState());
        return false;
    }
    if (e->type == 0x287259f6) {
        uint32_t id = e->source->GetEventId();
        if (id == 0x53f0707) {
            IPrefs* prefs = g_sAppPreferences;
            bool isSet = false;
            GetBoolProperty(prefs, 0x80eaa93, &isSet);
            if (!isSet) {
                IWindow_s00df_3be0* w = mLayout.FindWindowByID(0x809b720, true);
                if (w)
                    w->SetFlag(1, false);
                isSet = true;
                {
                    Variant v(isSet);
                    prefs->SetProperty(0x80eaa93, v);
                }
                SaveResource(prefs, GetSaveArea(0x11ac192), 0);
            }
        }
        HandleEvent(id);
        return false;
    }
    if (e->type == 0x4f5527e8) {
        uint32_t id = e->source->GetEventId();
        if (id == 0x588ab05) {
            IWindow_s00df_3be0* w = mLayout.FindWindowByID(id, true);
            if (w) {
                IWindow_s00df_3be0* child = w->FindChild(0x2f5528d9);
                if (child) {
                    uint32_t& panel = gpGGE_s00df_3be0->m24[child->GetIndex()];
                    mpGameInfo->Unk_de4610()->Unk_bbac80(panel, 1);
                }
            }
        }
        return false;
    }
    if (e->type == 0x9b1552d8) {
        KillSetiEffects(0x1ac6d1af, ATState());
        uint32_t id = e->source->GetEventId();
        if (id == 0x5400fa5) {
            IWinTextEdit* te = InterfaceCastTextEdit(mLayout.FindWindowByID(id, true));
            bool tag;
            WStr text(te->GetText(), &tag);   // 2nd ctor argument is an unused tag
            if (FUN_00def7c0(&text))
                te->SetText(text.mpBegin, 0);
            if (mpGameInfo) {
                *mpGameInfo = text;
                SetStateSummaryText(4, 0x5b08740, mpGameInfo->m00);
            }
            UpdateNavigationControls();
            return false;
        }
        if (id == 0x7d275bb) {
            IWinTextEdit* te = InterfaceCastTextEdit(mLayout.FindWindowByID(id, true));
            mpGameInfo->m20 = te->GetText();
            UpdateNavigationControls();
            return false;
        }
        return false;
    }
    if (e->type == 0x4cab02d) {
        KillSetiEffects(0xddd740f9, GetRecorderState_s00df_3be0());
        SelectTheme(e->data);
        return false;
    }
    return false;
}

// @ 0x00df46d0
void cGalaxyGameEntryUIHost::HandleUIEvent(uint32_t id, uint32_t arg)
{
    if (mpState->mb70 == 0 &&
        ((g_uiEventMask[id >> 5] >> (id & 31)) & 1) == 0 &&
        (Unk_e00670(id, arg), id == 0x1b) &&
        mpState->m74 != 0) {
        cGalaxyGameEntryUIStateMachine_s00df_3be0* ui = mpState;
        IRefObj_s00df_3be0* p = gpGGE_s00df_3be0->m19c;
        if (p) {
            p->v3(1);
            p = gpGGE_s00df_3be0->m19c;
            if (p) {
                gpGGE_s00df_3be0->m19c = 0;
                p->v1();
            }
        }
        KillSetiEffects(0xb7a63c50, GetRecorderState_s00df_3be0());
        void* q = gpGGE_s00df_3be0->m198;
        if (q)
            ((DeadEnd*)q)->Fn_dde570();
        ui->SetCurrentState(0);
        gpGGE_s00df_3be0->Unk_de86d0(2, 0);
        ui->UpdateNavigationControls();
    }
}

// @ 0x00df47b0
void cGalaxyGameEntryUIStateMachine_s00df_47b0::SetupForGame(cGameInfo_s00df_47b0* gameInfo)
{
    mpGameInfo = gameInfo;
    gameInfo->mB0 = 0;
    mb70 = false;
    mpGameInfo->mName.clear();
    ResetGameUI();

    if (mpGameInfo) {
        IWindow_s00df_47b0* window = mLayout.FindWindowByID(0x5944089, true);
        if (window)
            window->SetFlag(1, true);
        MakeRandomName();

        PropListPtr_s00df_47b0 propList;
        cPropManager_s00df_47b0* propManager = PropertyManager_s00df_47b0();
        propList = 0;
        if (propManager->GetPropertyListImpl(gNewGameFlowPropListID, 0, propList)) {
            mNewGameFlow.clear();

            eastl::hash_map_string16_uint panels;
            typedef eastl::hash_map_string16_uint::value_type value_type;
            panels.insert(value_type(string16_s00df_47b0(L"level"), 1));
            panels.insert(value_type(string16_s00df_47b0(L"diet"), 2));
            panels.insert(value_type(string16_s00df_47b0(L"creature"), 3));
            panels.insert(value_type(string16_s00df_47b0(L"name"), 4));
            panels.insert(value_type(string16_s00df_47b0(L"difficulty"), 5));
            panels.insert(value_type(string16_s00df_47b0(L"theme"), 6));
            panels.insert(value_type(string16_s00df_47b0(L"specialty"), 7));
            panels.insert(value_type(string16_s00df_47b0(L"assets"), 8));
            panels.insert(value_type(string16_s00df_47b0(L"assets and creature"), 9));
            panels.insert(value_type(string16_s00df_47b0(L"captain name"), 10));
            panels.insert(value_type(string16_s00df_47b0(L"start"), 11));

            int count;
            string16_s00df_47b0* names;
            uint32_t layoutID = FNV1_String16(sNewGameFlowLayout, 0x811c9dc5, true);
            if (GetPropertyAsString16Array(propList.get(), layoutID, count, names)) {
                for (int i = 0; i < count; i++) {
                    eastl::hash_iterator it = panels.find(names[i]);
                    if (it != panels.end())
                        mNewGameFlow.push_back(it->second);
                }
            }
        }

        SetupPanelA(0x6149007);
        SetupPanelB(0x614c680);
        StarManager_s00df_47b0()->SetActiveStar(mpGameInfo->GetStarRecord());
        mpGameInfo->GetStarRecord()->Reset(0);
        mpGameInfo->mKey70 = ResourceKey_s00df_47b0(0, 0, 0);
        mpGameInfo->mKey4C = mpGameInfo->mKey70;
        mpGameInfo->mKey64 = mpGameInfo->mKey4C;
        mKey514 = mpGameInfo->mKey64;
        mpGameInfo->mA8 = 6;
        mpGameInfo->mA4 = 6;
        mpGameInfo->mA0 = 0;

        IntRect client;
        App()->GetMainWindow()->GetClientRect(&client);
        float cx = (float)((client.right - client.left) / 2);
        float cy = (float)((client.bottom - client.top) / 2);
        window = mLayout.FindWindowByID(0x5384881, true);
        if (window) {
            Rect area = window->GetArea();
            window->SetLocation(cx - (area.right - area.left) * 0.5f, cy - (area.bottom - area.top) * 0.5f);
        }
        mpGameInfo->mKey94 = GetKeyForID(0x53dbcf5);
    }

    SetCurrentState(0);
    SetCurrentState(0xc);
    mpGameInfo = gameInfo;
    RefreshUI();
    mZoomTimer.Restart();
    mpGameInfo->mB0 = 0;

    IWindow_s00df_47b0* window = mLayout.FindWindowByID(0x657ce07, true);
    if (window)
        window->SetFlag(1, gbFlag16a0ee8);
    window = mLayout.FindWindowByID(0x5b744bc, true);
    if (window)
        window->SetFlag(1, !gbFlag16a0ee8);
    window = mLayout.FindWindowByID(0x4ec1b8d8, true);
    if (window) {
        if (!AppSystem_s00df_47b0()->IsFeatureEnabled())
            window->SetFlag(1, false);
        else
            window->SetFlag(1, gbFlag16a0d60);
    }
    window = mLayout.FindWindowByID(0x588ab05, true);
    if (window) {
        IWindow_s00df_47b0* combo = window->FindWindowByID(0x2f5528d9);
        if (combo) {
            FillStarterWorldCombo(combo);
            if (mpGameInfo && mpGameInfo->GetStarRecord())
                SelectStarterWorld(combo, mpGameInfo->GetStarRecord()->Get58());
        }
    }

    bool allUnlocked = gpGGEGlobal_s00df_47b0->mbAllLevelsUnlocked || AppSystem_s00df_47b0()->IsFeatureEnabled();
    for (uint32_t i = 0; i < 4; i++) {
        window = mLayout.FindWindowByID(kLevelButtonIDs[i], true);
        if (window)
            window->SetFlag(2, allUnlocked || gpGGEGlobal_s00df_47b0->IsLevelUnlocked(kLevelIDs[i]));
    }
    UpdateNavigationControls();
}

// @ 0x00df5330
void cGalaxyGameEntryUIStateMachine_s00df_47b0::FUN_00df5330()
{
    if (FUN_00685520(2)) {
        if (!gpGGEGlobal_s00df_47b0->IsLevelUnlocked(0x2887b6de)) {
            cMessageServer_s00df_47b0* server = MessageServer_s00df_47b0();
            server->post(0x6579712, 0x2887b6de, 0);
        }
    }

    GalaxyView* view = (GalaxyView*)this;
    view->m_state8->SetLayout(sNewGameFlowLayout);
    ((cGalaxyGameEntryUIStateMachine_s00df_47b0*)view->m_state8)->SetupForGame(view->m_game0c);

    IWindow_s00df_47b0* window = gpGGEGlobal_s00df_47b0->mLayout144.FindWindowByID(0x615a5ff, true);
    if (window)
        window->SetFlag(1, false);

    cSPUIGlobalUI_s00df_47b0* global = ((cGGEGlobalView*)gpGGEGlobal_s00df_47b0)->m_global184;
    global->SetVisibility(false);
    ((GalaxyStateBase*)this)->FUN_00dee360();
}

// @ 0x00df5830
bool cDownloadDialog::FUN_00df5830(void* retaddr)
{
    uint key[3];
    key[0] = 0xf7082241;
    key[1] = 0x0510a95b;
    key[2] = 0x40464100;
    cSPUILayout_s00df_5670* lay = (cSPUILayout_s00df_5670*)((char*)this + 0x0c);
    if (!lay->Init(key, 1, 0x5b598fa))
        return false;
    IWinNode* w = (IWinNode*)lay->FindWindowByID(0x6383590, 1);
    if (!w) {
        lay->Shutdown(1);
        return false;
    }
    w->v104(this);
    IWinNode* old = *(IWinNode**)((char*)this + 0x24);
    if (w != old) {
        w->r00();
        *(void**)((char*)this + 0x24) = w;
        if (old)
            old->r04();
    }
    IWinNode* w2 = (IWinNode*)lay->FindWindowByID(0x6393e18, 1);
    w2->v80((const wchar_t*)retaddr);
    return true;
}

// @ 0x00df58f0
void cDownloadDialog::FUN_00df58f0()
{
    SPUIHelpers_EndModal(mpNode_24, 0, 1);
    ((IWinNode*)mpNode_24)->v108(this);
    if (mpNode_24) {
        IWinNode* p = (IWinNode*)mpNode_24;
        mpNode_24 = 0;
        p->r04();
    }
    LayoutB()->Shutdown(1);
}

// @ 0x00df5940
cDownloadDialog* __fastcall cDownloadDialog_ctor_5940(cDownloadDialog* self)
{
    float f0 = DAT_01486114;
    float f1 = DAT_01485720;
    *(void**)((char*)self + 0x04) = (void*)vtbl_Resource_Async;
    self->mpVal_08 = 0;
    *(void**)self = (void*)vtbl_UI_cDownloadDialog_A;
    *(void**)((char*)self + 0x04) = (void*)vtbl_UI_cDownloadDialog_B;
    self->mpNode_0c = 0;
    self->m_timerPeriod = f0;
    self->m_active = 0;
    self->m_latch = 0;
    self->m_p1c = 0.0f;
    self->m_p20 = 0.0f;
    self->m_p24 = f1;
    self->m_p28 = 0.0f;
    self->m_paused = 0;
    self->m_label = 0;
    self->m_entry = 0;
    self->m_count = 1;
    self->m_index = 0;
    ((cSPUILayout_s00df_5670*)((char*)self + 0x54))->ctor();
    return self;
}

// @ 0x00df59c0
bool cDownloadDialog::FUN_00df59c0(void* p)
{
    uint key[3];
    key[0] = 0xdd6e903b;
    key[1] = 0x0510a95b;
    key[2] = 0x40464100;
    cSPUILayout_s00df_5670* lay = Layout();
    if (!lay->Init(key, 1, 0x5b598fa))
        return false;
    IWinNode* w = (IWinNode*)lay->FindWindowByID(0x431e538, 1);
    if (!w) {
        lay->Shutdown(1);
        return false;
    }
    w->v104(this);
    IWinNode* w2 = (IWinNode*)lay->FindWindowByID(0x5d68ee8, 1);
    if (w2) {
        Vec4* r = w2->v34();
        m_r34 = r->x;
        m_r38 = r->y;
        m_r3c = r->z;
        m_r40 = r->w;
        ((WinTextRef*)((char*)this + 0x30))->operator=(w2);
        m_progress = 0.0f;
        FUN_00df5610(0.0f);
    }
    *(void**)((char*)this + 0x48) = p;
    *(int*)((char*)this + 0x4c) = *(int*)((char*)p + 0x58);
    (void)w2;
    return true;
}

// @ 0x00df5aa0
void cDownloadDialog::FUN_00df5aa0(char b)
{
    if (b != 0) {
        *(char*)((char*)this + 0x18) = 1;
        return;
    }
    FUN_00df57d0(0);
}

// @ 0x00df5c80
cDownloadDialog* __fastcall cDownloadDialog_ctor_5c80(cDownloadDialog* self)
{
    *(void* volatile*)((char*)self + 0x04) = (void*)vtbl_Resource_Async;
    self->mpVal_08 = 0;
    *(void**)self = (void*)vtbl_UI_cDownloadDialog_C;
    *(void**)((char*)self + 0x04) = (void*)vtbl_UI_cDownloadDialog_D;
    ((cSPUILayout_s00df_5670*)((char*)self + 0x0c))->ctor();
    *(void**)((char*)self + 0x24) = 0;
    return self;
}

// @ 0x00df5ef0
bool FUN_00df5ef0()
{
    return *(int*)(kGUI + 0xfc) == 0;
}

// @ 0x00df5f10
void FUN_00df5f10()
{
    Obj* p = FUN_00dd9190();
    FUN_00ddb760(p);
    FUN_00de9ec0((Obj*)kGUI);
}

// @ 0x00df5f50
float* FUN_00df5f50(float* out, const float* r)
{
    {
        double lo = r[0];
        double hi = r[3];
        double v = RandRangeD(lo, hi);
        if (v < hi) {
            if (v < lo) v = lo;
        } else {
            v = hi;
        }
        out[0] = (float)v;
    }
    {
        double lo = r[1];
        double hi = r[4];
        double v = RandRangeD(lo, hi);
        if (v < hi) {
            if (v < lo) v = lo;
        } else {
            v = hi;
        }
        out[1] = (float)v;
    }
    {
        double lo = r[2];
        double hi = r[5];
        double v = RandRangeD(lo, hi);
        if (v < hi) {
            if (v < lo) v = lo;
        } else {
            v = hi;
        }
        out[2] = (float)v;
    }
    return out;
}

// @ 0x00df6040
void cDownloadDialog::FUN_00df6040()
{
    int n = (int)((char*)m_entryEnd - (char*)mpVal_08) / 0xbc;
    if (n != 0) {
        char* base = (char*)mpVal_08;
        for (int i = 0; i < n; i++) {
            char* e = base + i * 0xbc;
            float a, b;
            FUN_00de3c70(e + 0x80, &a, &b);
            ((IWinNode*)this)->v64(a, b);
        }
    }
    float z[3] = { 0.0f, 0.0f, 0.0f };
    float a, b;
    FUN_00de3c70(z, &a, &b);
    if (fabsf(DAT_016a16a8 - a) > DAT_01486110)
        DAT_016a16a8 = a;
    if (fabsf(DAT_016a16a4 - b) > DAT_01486110)
        DAT_016a16a4 = b;
}

// @ 0x00df6140
bool cDownloadDialog::FUN_00df6140(Obj* a, float x, float y)
{
    if (*(void**)((char*)a + 0xb8) == 0)
        return false;
    cSPUILayout_s00df_5670* lay = *(cSPUILayout_s00df_5670**)((char*)a + 0xb8);
    IWinNode* w = (IWinNode*)lay->FindWindowByID(0x2e5a4a8, 0);
    if (w) {
        Vec4 area;
        SPUIHelpers_GetMainWindowArea_s00df_5670(&area);
        Vec4* r1 = w->v38();
        float a0 = r1->x, a1 = r1->y, a2 = r1->z, a3 = r1->w;
        Vec4* r2 = w->v34();
        float p0 = r2->x, p1 = r2->y;
        x = x - (a2 - a0) * DAT_01471064;
        y = y - (a3 - a1) * DAT_01471064;
        if (*(char*)((char*)a + 0xac) != 0) {
            float ty = (area.z - area.x) - DAT_016a0ec8;
            float tx = (area.w - area.y) - DAT_016a0ea8;
            float limx = DAT_016a0e98;
            float limy = DAT_016a0eb8;
            if (y <= ty) { /* keep y */ } else y = ty;
            if (limy <= y) y = limy;
            if (x <= tx) { /* keep x */ } else x = tx;
            if (limx <= x) x = limx;
        }
        if (fabsf(p0 - x) > DAT_014853e0 || fabsf(p1 - y) > DAT_014853e0) {
            w->v64(x, y);
        }
    }
    return w != 0;
}

// @ 0x00df6330
void cDownloadDialog::FUN_00df6330(uint id, void* p, uint b)
{
    if (((DAT_016a1848[id >> 5] >> (id & 0x1f)) & 1) != 0)
        return;
    FUN_00e00670(id, p);
    if (id == 0x1b) {
        if (*(char*)(kGUI + 0x1f0) == 0) {
            if (*(int*)(kGUI + 0xfc) != 0) {
                AudioSys* au = (AudioSys*)EA_Audio_GetSystemAT();
                if (au)
                    au->a20();
                SP_cSPUISpace_KillSetiEffects(0, 0xb7a63c50);
                if (*(char*)(*(int*)(kGUI + 0xfc) + 0xac) != 0)
                    FUN_00dde570(*(void**)(kGUI + 0x198));
                ((IWinNode*)this)->v5c(0);
                FUN_00e00650(id, p);
                return;
            }
            FUN_00de86d0(6, 1);
            AudioSys* au = (AudioSys*)EA_Audio_GetSystemAT();
            if (au)
                au->a20();
            SP_cSPUISpace_KillSetiEffects(0, 0x5da7b944);
            MsgObj* s = (MsgObj*)SP_MessageServer();
            s->m14(0x64a5044, 0, 0);
        } else {
            IWinNode* w1 = *(IWinNode**)(kGUI + 0x160);
            if (w1) {
                w1->v0c(1);
                IWinNode* t1 = *(IWinNode**)(kGUI + 0x160);
                if (t1) {
                    *(void**)(kGUI + 0x160) = 0;
                    t1->r04();
                }
            }
            IWinNode* w2 = *(IWinNode**)(kGUI + 0x1a0);
            if (w2) {
                w2->v0c(1);
                IWinNode* t2 = *(IWinNode**)(kGUI + 0x1a0);
                if (t2) {
                    *(void**)(kGUI + 0x1a0) = 0;
                    t2->r04();
                }
            }
            MsgObj* s = (MsgObj*)SP_MessageServer();
            s->m14(0x4360e14, 0, 0);
        }
    }
    FUN_00e00650(id, p);
}

// @ 0x00df64c0
int cDownloadDialog::FUN_00df64c0(float a, float b, float c)
{
    Obj* app = SP_App();
    void* ctx = (*(void*(**)())(*(int*)app + 0x58))();
    Quat qa, qb;
    if (!FUN_007c4510(ctx, a, b, qa.v, qb.v))
        return 0;
    int n = (int)((char*)m_entryEnd - (char*)mpVal_08) / 0xbc;
    char* best = 0;
    float bestd = c;
    if (n != 0) {
        char* base = (char*)mpVal_08;
        for (int i = 0; i < n; i++) {
            char* e = base + i * 0xbc;
            float d = FUN_00698b30((const float*)(e + 0x80), qa.v, qb.v);
            if (d < bestd) {
                bestd = d;
                best = e;
            }
        }
        if (best != 0) {
            Obj* app2 = SP_App();
            void* ctx2 = (*(void*(**)())(*(int*)app2 + 0x58))();
            FUN_007c4180(ctx2, (const float*)(best + 0x80), qa.v);
        }
    }
    return (int)best;
}

// @ 0x00df65e0
void cDownloadDialog::FUN_00df65e0(void* a, void* b, float c)
{
    if (*(char*)(kGUI + 0x17c) != 0)
        return;
    int r = FUN_00df64c0(*(float*)&a, *(float*)&b, DAT_014007f4);
    int cur = *(int*)(kGUI + 0xf8);
    if (cur == 0 || cur == r) {
        ((IWinNode*)this)->v5c((void*)r);
        return;
    }
    cSPUILayout_s00df_5670* lay = *(cSPUILayout_s00df_5670**)(cur + 0xb8);
    if (lay == 0)
        return;
    IWinNode* w = (IWinNode*)lay->FindWindowByID(0x2e5a4a8, 1);
    if (w == 0)
        return;
    Vec4* rect = w->v38();
    float v2[4];
    v2[0] = *(float*)&a;
    v2[1] = *(float*)&b;
    v2[2] = rect->x;
    v2[3] = rect->y;
    if (!FUN_005f2350(v2)) {
        ((IWinNode*)this)->v5c(0);
        return;
    }
}

// @ 0x00df66e0
int FUN_00df66e0()
{
    StarManagerObj* m = (StarManagerObj*)SP_StarManager();
    return m->mVec.size();
}

// @ 0x00df6700
void WinA::FUN_00df6700(void* param)
{
    if (mp8c != 0) {
        void* n = FUN_00fc7e50(mp8c);
        if (n != 0) {
            ((NodeVt*)FUN_00fc7e50(mp8c))->v7c(1, param);
        }
    }
}

// @ 0x00df6740
void WinA::FUN_00df6740()
{
    if (mp8c == 0) return;
    if (((Banner2*)m20.mp10)->FUN_00de4610()->bAC == 0) return;

    Vec3 v3 = *((Banner2*)m20.mp10)->FUN_00de4610()->FUN_00bbaa60(0)->FUN_00b8d8e0();
    int local18[6] = { 0, 0, 0, 0, 0, 0 };
    FUN_0080ea50(mp8c);
    if (FUN_00b3d360_s00df_6700()->FUN_00b7d4f0(&v3) != 0) {
        FUN_00b3d360_s00df_6700()->FUN_00b7d440(v3, 0, 0, 0, 0, &local18[0], &local18[3]);
        if (local18[0] != 0) {
            m20.FUN_00e21260(&local18[0], &local18[3], mp8c);
            m20.FUN_00e20d60(g_c16a0dd0);
            m20.FUN_00e20d30(g_f16a0da0);
        }
    }
}

// @ 0x00df6850
bool WinA::FUN_00df6850(RefVt* param)
{
    if (mp34 != 0) mp34->v0c(1);
    RefVt* old = mp34;
    if (param != old) {
        if (param != 0) param->v00();
        mp34 = param;
        if (old != 0) old->v04();
    }
    if (mp34 != 0) {
        mp34->v08(0);
        param = (RefVt*)m20.mp10;
        mp34->v48(9, &param, 1);
    }
    return true;
}

// @ 0x00df68c0
bool WinA::FUN_00df68c0(uint32_t msg, void* param3)
{
    if (msg == 0x5120263) {
        m50 = 1;
        return true;
    }
    if (msg == 0x7be7df5) {
        if (((MsgArg*)param3)->m08 == 5) {
            Transform34 tf;
            FUN_00409930(&tf);
            FUN_005aa530(&tf);
            FUN_00ddab00(FUN_00dd9190_1(&tf));
            FUN_00ddb760((Obj*)FUN_00dd9190_0());
        }
        if (((MsgArg*)param3)->m08 == 4) {
            ((PanelMgr*)g_p16a1344)->FUN_00de9ec0();
            ((PanelMgr*)g_p16a1344)->FUN_00de5330(0);
        }
        return true;
    }
    if (msg == 0x7c3cd3d) {
        if (((MsgArg*)param3)->m08 == 5) {
            FUN_00dda090(FUN_00dd9190_2((void*)2, (void*)1));
        }
        return true;
    }
    return false;
}

// @ 0x00df6980
void WinB::FUN_00df6980()
{
    if (sw20.mStart != 0) return;

    int count = (int)(mpEnd - mpBegin);
    if (count != 0) {
        int i = 0;
        do {
            Rec* r = &mpBegin[i];
            if (r->bAD != 0) {
                RetVt* obj = 0;
                if (r->bAC == 0)
                    ((PanelMgr*)g_p16a1344)->mp15c->p08(0x37cf81e6, 0, (void**)&obj);
                else
                    ((PanelMgr*)g_p16a1344)->mp15c->p08(0xa77c6b11, 0, (void**)&obj);
                if (obj != 0) {
                    GfxPoint p;
                    p.m04 = (g_mat00 * r->fX + g_mat01 * r->fY) + g_mat02 * r->fZ + g_posX;
                    p.m08 = (g_mat10 * r->fX + g_mat11 * r->fY) + g_mat12 * r->fZ + g_posY;
                    p.m0c = (g_mat20 * r->fX + g_mat21 * r->fY) + g_mat22 * r->fZ + g_posZ;
                    p.m00 = 4;
                    p.m02 = 1;
                    p.m10 = g_f1485720;
                    obj->q18(&p);
                    obj->q08(0);
                    if (obj != 0) obj->q04();
                }
            }
            ++i;
        } while (i < count);
    }

    if (sw20.mUnits == 1) {
        uint64_t t = __rdtsc();
        sw20.mElapsed = 0;
        sw20.mStart = t;
        return;
    }
    uint64_t t;
    g_pQueryPerformanceCounter(&t);
    sw20.mElapsed = 0;
    sw20.mStart = t;
}

// @ 0x00df6c40
void WinB::FUN_00df6c40()
{
    PropList* pl = (PropList*)g_p15fd91c;
    unsigned char b = 0;
    union { void* p; uint64_t u; } slot;
    if (pl != 0 && pl->y24(0x80d7de1, &slot.p) != 0) {
        if (((Prop*)slot.p)->m12 == 1) b = *((Prop*)slot.p)->GetBool();
    }

    WinVt* w = ((PanelMgr*)g_p16a1344)->mLayout.FindWindowByID(0x806a310, 1);
    if (w != 0) w->v7c(1, b == 0);

    if (pl != 0 && pl->y24(0x80d97fe, &slot.p) != 0) {
        if (((Prop*)slot.p)->m12 == 1) {
            if (*((Prop*)slot.p)->GetBool() != 0) return;
        }
    }

    WinVt* w2 = ((PanelMgr*)g_p16a1344)->mLayout.FindWindowByID(0x806aa00, 1);
    if (w2 != 0) w2->v7c(1, 0);

    char flag = 1;
    Variant_s00df_6700 v;
    v.mFlagsW = 0;
    v.mAuxW = 0;
    v.SetChar(&flag);
    pl->y14(0x80d97fe, &v);
    if ((v.mFlagsW & 4) != 0) v.Destruct(false);

    FUN_006b1d50(pl, FUN_006b1f90(0x11ac192), 0);

    Stopwatch_s00df_6700* sw = &sw38;
    sw->SetUnits(4);
    if (sw->mStart != 0) return;
    if (sw->mUnits == 1) {
        uint64_t t = __rdtsc();
        sw->mStart = t;
        return;
    }
    g_pQueryPerformanceCounter(&slot.u);
    sw->mStart = slot.u;
}

// @ 0x00df6db0
bool cGameUIData::SetUIState(int newState)
{
  if (mUIState == newState) return true;
  switch (newState) {
  case 2:
    KillSetiEffects(0xd06d9182, GetRecorderState_s00df_6db0());
    FindWindowByID(0x46a9ca7, 1)->SetVisible(1, 0);
    FindWindowByID(0x4656452, 1)->SetVisible(1, 1);
    FindWindowByID(0x5b31710, 1)->SetVisible(1, 1);
    mUIState = newState;
    return true;
  case 3:
    KillSetiEffects(0xd06d9182, GetRecorderState_s00df_6db0());
    FindWindowByID(0x46a9ca7, 1)->SetVisible(1, 1);
    WindowManager_s00df_6db0()->SetFocus(1, FindWindowByID(0x46a9ca7, 1));
    mUIState = newState;
    FindWindowByID(0x2e712e4, 1)->SetText((const void*)mpInfo->mFirst);
    FindWindowByID(0x46ea550, 1)->SetText((const void*)mpInfo->mFirst);
    FindWindowByID(0x5b31710, 1)->SetVisible(1, 1);
    return true;
  case 4:
    KillSetiEffects(0xd2fc3ad5, GetRecorderState_s00df_6db0());
    FindWindowByID(0x4656452, 1)->SetVisible(1, 0);
    FindWindowByID(0x5b31710, 1)->SetVisible(1, 0);
    return true;
  case 5: {
    KillSetiEffects(0x6c6da889, GetRecorderState_s00df_6db0());
    FindWindowByID(0x4656452, 1)->SetVisible(1, 0);
    FindWindowByID(0x46a9ca7, 1)->SetVisible(1, 0);
    FindWindowByID(0x3753f40, 1)->SetVisible(1, 1);
    cWin* w = FindWindowByID(0x5b31710, 1);
    if (w) {
      w->SetThing(FindWindowByID(0x5b34d93, 1)->GetThing());
      w->SetVisible(1, 1);
    }
    break;
  }
  case 1: {
    cWStr str;
    cZero3 z1, z2, z3, z4;
    cWin* w = FindWindowByID(0x2e5a4a8, 1);
    if (!w) break;
    w->SetVisible(1, 1);
    cRect4 R(*(const cRect4*)w->GetArea());
    float nl = -R.x, nt = -R.y;
    R.x = nl + R.x;
    R.y = nt + R.y;
    R.w = R.w + nl;
    R.h = R.h + nt;
    u32 ids[3];
    ids[0] = 0x3753f40; ids[1] = 0x4656452; ids[2] = 0x46a9ca7;
    FindWindowByID(0x5b31710, 1)->SetVisible(1, 0);
    for (u32 i = 0; i < 3; ++i) {
      cWin* c = FindWindowByID(ids[i], 1);
      c->SetVisible(1, 0);
      Pollinator(c, &R);
    }
    if (mpInfo->m3c != 0) {
      cWin* c1 = FindWindowByID(0x2e71340, 1);
      FUN_00de3f00(c1, &mpInfo->m3c, 0);
      c1 = FindWindowByID(0x46ea568, 1);
      FUN_00de3f00(c1, &mpInfo->m3c, 0);
    } else {
      cWin* c = FindWindowByID(0x2e71340, 1);
      if (c) c->SetVisible(1, 0);
      c = FindWindowByID(0x46ea568, 1);
      if (c) c->SetVisible(1, 0);
      c = FindWindowByID(0x68dac20, 1);
      if (c) c->SetVisible(1, 1);
      c = FindWindowByID(0x68dac21, 1);
      if (c) c->SetVisible(1, 1);
    }
    cWin* c = FindWindowByID(0x46a9a21, 1);
    FUN_00de3f00(c, &mpInfo->m30, 0);
    c = FindWindowByID(0x46ea4b6, 1);
    FUN_00de3f00(c, &mpInfo->m30, 0);
    c->SetHandler(0x37ac490, (void*)(mpInfo->mB8 + 0x18));
    FUN_00de3fa0(&str, mpInfo->mA8);
    c = FindWindowByID(0x594a640, 1);
    if (c) c->SetText(str.mpBegin);
    c = FindWindowByID(0x5ff9352, 1);
    if (c) c->SetText(str.mpBegin);
    if (mpInfo->mpSpecies) {
      cWStr name;
      name.mpBegin = g_EmptyWStr;
      name.mpEnd = g_EmptyWStr;
      name.mpCapacity = g_EmptyWStr + 1;
      c = FindWindowByID(0x5ff9ad2, 1);
      if (c) {
        mpInfo->mpSpecies->GetUiName(&name);
        c->SetText(name.mpBegin);
      }
      c = FindWindowByID(0x5ff9d44, 1);
      if (c) {
        mpInfo->mpSpecies->GetUiName(&name);
        c->SetText(name.mpBegin);
      }
      name.DeallocateSelf();
    }
    u32 id = (mpInfo->mFlagAC ? 0x14de36a : 0) + 0x4656452;
    cWin* w5 = FindWindowByID(0x5b31710, 1);
    mpMgr->Attach(w5, 1);
    w5->SetThing(FindWindowByID(id, 1)->GetThing());
    if (mpInfo->Resolve()->mFlagAC) {
      cVec3 v = *mpInfo->Resolve()->Get(0)->GetPos();
      cZero3 a = {0, 0, 0};
      cZero3 b = {0, 0, 0};
      if (FUN_00b3d360_s00df_6db0()->Query(&v)) {
        FUN_00b3d360_s00df_6db0()->Fill(v, 0, 0, 0, 0, &a, &b);
        if (a.a != 0) {
          mPlanet.Query(&a, &b, mpMgr);
          mPlanet.SetA(g_PlanetKey);
          mPlanet.SetB(g_PlanetScale);
        }
      }
    }
    cWin* img = FUN_00de3e00(FindWindowByID(mpInfo->mA8 + 0x3744ff0, 1));
    if (img) img->AddRef();
    z1.a = 0; z1.b = 0; z1.c = 0;
    FUN_00de3f00(FindWindowByID(0x2e713a8, 1), &z1, img);
    z2.a = 0; z2.b = 0; z2.c = 0;
    FUN_00de3f00(FindWindowByID(0x46ea523, 1), &z2, img);
    z3.a = 0; z3.b = 0; z3.c = 0;
    FUN_00de3f00(FindWindowByID(0x26e0001, 1), &z3, img);
    z4.a = 0; z4.b = 0; z4.c = 0;
    FUN_00de3f00(FindWindowByID(0x26e0002, 1), &z4, img);
    c = FindWindowByID(0x2e712e4, 1);
    if (c) c->SetText((const void*)mpInfo->mFirst);
    c = FindWindowByID(0x46ea550, 1);
    if (c) c->SetText((const void*)mpInfo->mFirst);
    if (mpInfo && mpInfo->Resolve()) {
      cWStr s2;
      FUN_00de40e0(&s2, (char*)mpInfo->Resolve() + 0x18);
      FindWindowByID(0x46a9a9b, 1)->SetText(s2.mpBegin);
      FindWindowByID(0x46ea507, 1)->SetText(s2.mpBegin);
      cWin* cc = FindWindowByID(0x47e3cd3, 1);
      cColorRGBA col;
      col.r = 0.0f; col.g = g_ColorK; col.b = 0.0f; col.a = g_ColorK;
      cc->SetColor(ColorRGBAToU32(&col));
      s2.DeallocateSelf();
    }
    if (img) img->Release();
    if ((int)((str.mpCapacity - str.mpBegin) * 2 & ~1) > 2 && str.mpBegin)
      operator_delete_arr(str.mpBegin);
    mUIState = newState;
    return true;
  }
  default:
    return true;
  }
  mUIState = newState;
  return true;
}

// @ 0x00df76c0
bool cGameUIData::SetLayout(const wchar_t* pName, void* pArg)
{
  mUIState = 0;
  cWin* w = FindWindowByID(0x46ea4b6, 1);
  if (w)
    w->SetHandler(0x37ac490, 0);
  Shutdown(1);
  if (pName) {
    bool ok = Init(pName, 0x40464100, 1, 0x5b598fa);
    cMgr8c* pNew = AddBoundingBox()->GetCollection();
    cMgr8c* pOld = mpMgr;
    if (pNew != pOld) {
      if (pNew)
        pNew->AddRef();
      mpMgr = pNew;
      if (pOld)
        pOld->Release();
    }
    if (ok && SetUIState(1)) {
      FindWindowByID(0x3753f40, 1)->SetWindowArg(pArg);
      FindWindowByID(0x4656452, 1)->SetWindowArg(pArg);
      FindWindowByID(0x46a9ca7, 1)->SetWindowArg(pArg);
      FindWindowByID(0x638491d, 1)->SetWindowArg(pArg);
      if (mpInfo && mpInfo->mA8 == 5 && !g_16a0f88) {
        cWin* c = FindWindowByID(0x3c4925e, 1);
        if (c)
          c->SetVisible(2, 0);
      }
    }
    return ok;
  }
  return false;
}

// @ 0x00df7830
bool cGalaxyGameEntryImpl_s00df_6db0::DoMessage(u32 msg, cMessage* pMsg)
{
  if (pMsg->mId == 0x4f5527e8) {
    cWin* w = g_16a1344->mpPending->mpLayout->FindWindowByID(0x3f56d9e, 1);
    if (w) {
      cWin* p = (cWin*)w->GetProperty(0x2f5528d9);
      if (p) {
        int idx = p->GetIndex();
        g_16a1344->mpPending->Resolve(
            g_16a1344->mpArray24->GetEntry(idx), 1)->SetStar();
      }
    }
  }
  if (pMsg->mId == 10 && pMsg->mSub == 1 && pMsg->mpWindow != 0 &&
      pMsg->mpWindow->GetWindowID() == 0x4656452) {
    cWin* p = (cWin*)pMsg->mpWindow->FindHandler(0x37ac490);
    cWin* q;
    void* v = (p != 0 && (q = (cWin*)p->GetProperty(0x37ac490)) != 0)
                  ? *(void**)((char*)q + 4)
                  : 0;
    if (pMsg->mpWindow != pMsg->mpWindow2 && v == (void*)g_16a1344->mpDisplayed)
      v5c(0);
  }
  if (pMsg->mId == 7 && g_16a1344->mpDisplayed != 0) {
    cWin* a = g_16a1344->mpDisplayed->mpLayout->FindWindowByID(0x4656452, 1);
    cWin* b = g_16a1344->mpDisplayed->mpLayout->FindWindowByID(0x638491d, 1);
    if (pMsg->mpWindow == a || pMsg->mpWindow == b) {
      if (g_16a1344->mpDisplayed->mEntryKind == 0) {
        g_16a1570->SetUserData(g_16a1344->mpDisplayed);
        g_16a1344->FUN_00de86d0(4, 0);
      } else {
        g_16a1344->mp198->PushMatrix(&g_16a1344->mpDisplayed->mSub80[0]);
      }
      g_16a15fc->v60(g_16a1344->mpDisplayed, 1);
    }
  }
  if (pMsg->mId == 0x287259f6) {
    u32 id = pMsg->mpObject->GetWindowID();
    if (id == 0x3c4925e) {
      if (g_16a1344->mpPending) {
        cAudioSystemAT* pAudio = (cAudioSystemAT*)FUN_00a206f0();
        u32 handle = pAudio ? pAudio->GetHandle() : 0;
        KillSetiEffects(0x4e53ef11, (void*)handle);
        g_16a11b4->mp48 = g_16a1344->mpPending;
        g_16a1344->FUN_00de86d0(0xb, 0);
        return true;
      }
    } else if (id == 0x375408c) {
      cAudioSystemAT* pAudio = (cAudioSystemAT*)FUN_00a206f0();
      u32 handle = pAudio ? pAudio->GetHandle() : 0;
      KillSetiEffects(0x4e53ef11, (void*)handle);
      g_16a1344->mpPending->mpLayout->SetUIState(1);
      g_16a1484->v5c((int)g_16a1344->mpPending);
      g_16a1344->FUN_00de86d0(0xc, 0);
      return true;
    } else if (id == 0x3754098 || id == 0x3743e9c) {
      v60(0, 1);
    }
  }
  return true;
}

// @ 0x00df7af0
void cGalaxyGameEntryImpl_s00df_6db0::SetPendingGame(cGalaxyGameEntry* pGame, char flag)
{
  if (g_16a1344->mpPending == pGame)
    return;
  if (pGame) {
    v5c(0);
    FUN_00dd9190_s00df_6db0(2)->ResetHints();
    g_16a1344->m271 = 0;
    cSpaceGame* pSingleton = g_16a1344;
    pSingleton->mC8 = 0;
    pSingleton->GetUIHints()->Next(0x2e25815e, 0);
  } else if (g_16a1344->m108 == 2) {
    g_16a1344->FUN_00de9ec0();
    if (g_16a1344->mpPending) {
      cGameUIData* pLayout = g_16a1344->mpPending->mpLayout;
      if (pLayout) {
        cWin* w = pLayout->FindWindowByID(0x46ad82d, 1);
        if (w)
          w->SetVisible(1, 0);
        g_16a1344->FUN_00de53d0(0);
      }
    }
  }
  if (g_16a1344->mpPending && flag)
    g_16a1344->mpPending->mpLayout->SetUIState(1);
  g_16a1344->mpPending = 0;
  if (pGame) {
    g_16a1344->mpPending = pGame;
    if (flag) {
      if (pGame->mEntryKind)
        pGame->mpLayout->SetUIState(5);
      else
        pGame->mpLayout->SetUIState(4);
    }
  }
}

// @ 0x00df7c20
void cGalaxyGameEntryImpl_s00df_6db0::SetDisplayedEntry(cGalaxyGameEntry* pEntry)
{
  if (g_16a1344->mpPending)
    return;
  cGalaxyGameEntry* pOld = g_16a1344->mpDisplayed;
  if (pOld == pEntry)
    return;
  if (pOld)
    pOld->mpLayout->SetUIState(1);
  g_16a1344->mpDisplayed = 0;
  if (!pEntry || !pEntry->mpLayout)
    return;
  if (pEntry->mEntryKind)
    pEntry->mpLayout->SetUIState(3);
  else
    pEntry->mpLayout->SetUIState(2);
  v60(0, 1);
  float f1, f2;
  FUN_00de3c70(&pEntry->mSub80[0], &f1, &f2);
  v64(pEntry, f2, f1);
  g_16a1344->mpDisplayed = pEntry;
}

// @ 0x00df7ce0
void __cdecl FUN_00df7ce0()
{
}

// @ 0x00df7f60
void __cdecl GetSavedGames()
{
}

// @ 0x00df82d0
struct Dtor_s00df_82d0 {
    char                mPad00[0x18];
    void*               mpTracerVtbl18;                 // +0x18
    char                mPad1c[4];
    cGalaxyGameEntryMode mode20;                        // +0x20
    char                mPad2c[8];
    void*               mpObject34;                     // +0x34
    void*               mpBegin38;                      // +0x38
    char                mPad3c[4];
    void*               mpEnd40;                        // +0x40
    char                mPad44[4];
    void*               mpCap48;                        // +0x48
    char                mPad4c[0x40];
    void*               mpObject8c;                     // +0x8c
};
void __fastcall FUN_00df82d0(Dtor_s00df_82d0* self)
{
    if (self->mpObject8c != 0)
        (*(void(__thiscall**)(void*))((char*)*(void**)self->mpObject8c + 8))(self->mpObject8c);

    char* begin = (char*)self->mpBegin38;
    char* end = (char*)self->mpEnd40;
    if ((int)((unsigned)(end - begin) & ~1u) > 2 && begin != 0 && begin != (char*)self->mpCap48)
        op_del_array(begin);

    if (self->mpObject34 != 0)
        (*(void(__thiscall**)(void*))((char*)*(void**)self->mpObject34 + 4))(self->mpObject34);

    self->mode20.ReleaseOwned();
    *(void* volatile*)((char*)self + 0x18) = (void*)g_13eb938;
    _ReadWriteBarrier();
    ((cSPUILayout_s00df_5670*)self)->dtor();
}

// @ 0x00df8330
void __cdecl SetupRolloverStarEffects()
{
}

// @ 0x00df85e0
void __cdecl SetGameToEnter()
{
}

// @ 0x00df8730
void cGalaxyGameEntryScreen_s00df_8730::Update(float dt)
{
    if (GalaxyStarLinks()->GetLinkCount(1) < 5
        && g_SPRandom.RandomDoubleUniform(g_fLinkChance) <= 1.0)
    {
        if (g_SPRandom.RandomUint32Uniform(5) < 3) {
            uint32_t a = g_SPRandom.RandomUint32Uniform(mGames.size());
            uint32_t b;
            do {
                b = g_SPRandom.RandomUint32Uniform(mGames.size());
            } while (b == a);
            Vector3_s00df_8730 posA(mGames[a].mStarLocationAbsolute);
            Vector3_s00df_8730 posB(mGames[b].mStarLocationAbsolute);
            if ((posA - posB).Length() > 200.0f)
                GalaxyStarLinks()->AddLongLink(&posA, &posB);
            else
                GalaxyStarLinks()->AddLink(&posA, &posB, true, true);
        } else {
            Vector3_s00df_8730 far = (g_SPRandom.RandomUint32Uniform(2) == 0
                ? SP::normalized_safe(g_pGalaxyGameEntryUI->mpCamera->GetTransform().mOffset)
                : SP::normalized_safe(RandomPointInBox(
                      BoundingBox(Vector3_s00df_8730(-1.0f, -1.0f, -1.0f), Vector3_s00df_8730(1.0f, 1.0f, 1.0f))))) * 1500.0f;
            uint32_t i = g_SPRandom.RandomUint32Uniform(mGames.size());
            Vector3_s00df_8730 pos(mGames[i].mStarLocationAbsolute);
            if (g_SPRandom.RandomUint32Uniform(2) == 0)
                GalaxyStarLinks()->AddLink(&far, &pos, false, true);
            else
                GalaxyStarLinks()->AddLink(&pos, &far, true, false);
        }
    }

    if (g_pGalaxyGameEntryUI->mb1f0 && GalaxyStarLinks()->GetPulseCount() < 15)
        GalaxyStarLinks()->AddPulse();

    IWindow_s00df_8730* w = g_pGalaxyGameEntryUI->mLayout.FindWindowByID(0x615a5ff, true);
    if (w)
        w->SetFlag(1, g_pGalaxyGameEntryUI->mfc == 0);
    g_pGalaxyGameEntryUI->mpGlobalUI->SetVisibility(g_pGalaxyGameEntryUI->mfc == 0);
    g_pGalaxyGameEntryUI->Refresh();

    if (g_pGalaxyGameEntryUI->mf8)
        UpdateMouse(this);

    for (uint32_t i = 0; i < mGames.size(); ++i) {
        if (mGames[i].mpUIData)
            mGames[i].mpUIData->mAnim.Update((uint32_t)(dt * 1000.0f));
    }

    if (g_pGalaxyGameEntryUI->mf8) {
        UpdateMouse(this);
        g_pGalaxyGameEntryUI->mpCamera->SetMouseActive(true);
    } else
        g_pGalaxyGameEntryUI->mpCamera->SetMouseActive(false);
    if (g_pGalaxyGameEntryUI->mf8)
        UpdateRollover();

    if (g_pGalaxyGameEntryUI->mfc) {
        UpdateRollover();
        g_pGalaxyGameEntryUI->mpGlobalUI->SetVisibility(false);
    } else if (!g_pGalaxyGameEntryUI->mb1f0) {
        g_pGalaxyGameEntryUI->mpGlobalUI->SetVisibility(true);
    }

    if (mNoticeTimer.IsRunning() && mNoticeTimer.GetElapsedTimeFloat() > g_fNoticeTime) {
        mNoticeTimer.Stop();
        mNoticeTimer.Reset();
    }

    if (g_pGalaxyGameEntryUI->mb271) {
        if (!mHighlightTimer.IsRunning() || mHighlightTimer.IsTimeUp()) {
            if (!mHighlightEffects.empty())
                mHighlightEffects.back()->Stop(0);

            for (int i = 0; i < mGames.size(); ++i) {
                if (i != mHighlightIndex && !mGames[i].mbSaved && mGames[i].mbVisibleInGalaxy)
                    mCandidates.push_back(i);
            }

            uint32_t n = mCandidates.size();
            if (n > 0) {
                mHighlightIndex = mCandidates[g_SPRandom.RandomUint32Uniform(n)];
                cGameInfo_s00df_8730& game = mGames[mHighlightIndex];
                EffectRef effect;
                if (g_pGalaxyGameEntryUI->mpEffectsWorld->CreateVisualEffect(0xdaae81f8, 0, effect)) {
                    Transform t(g_galaxyOffset + g_galaxyRotation * game.mStarLocationAbsolute,
                                g_galaxyRotation);
                    effect->SetTransform(t);
                    effect->Start(0);
                    mHighlightEffects.push_back(effect);
                    mHighlightTimer.SetTimeLimit(3000, true);
                }
            } else {
                mHighlightIndex = -1;
            }
            mCandidates.clear();
        }
    }

    bool noticeShowing = mNoticeTimer.IsRunning();
    bool panelOpen = g_pGalaxyGameEntryUI->mfc != 0;
    IWindow_s00df_8730* highlighted;
    if (mHighlightIndex > 0)
        highlighted = mGames[mHighlightIndex].mpUIData->mpWindow;
    else
        highlighted = 0;

    for (uint32_t i = 0; i < g_pGalaxyGameEntryUI->mWindows.size(); ++i) {
        IWindow_s00df_8730* win = g_pGalaxyGameEntryUI->mWindows[i];
        win->SetVisible(noticeShowing || panelOpen || win == highlighted);
    }

    for (uint32_t i = 0; i < mHighlightEffects.size(); ) {
        cIVisualEffect_s00df_8730* e = mHighlightEffects[i];
        if (e->IsRunning()) {
            e->SetVisible(noticeShowing || panelOpen);
            ++i;
        } else {
            mHighlightEffects.erase(mHighlightEffects.mpBegin + i);
        }
    }

    if (mbWaitForGuide && !SP::SporeGuide_s00df_8730()->mbActive) {
        mbWaitForGuide = false;
        if (g_pGalaxyGameEntryUI->mfc) {
            g_pGalaxyGameEntryUI->ShowPanel(0);
            g_pGalaxyGameEntryUI->ShowPanel(1);
        }
    }

    if (mHintTimer.IsRunning() && mHintTimer.GetElapsedTimeFloat() > 1000.0f) {
        IWindow_s00df_8730* hint = g_pGalaxyGameEntryUI->mLayout.FindWindowByID(0x806aa00, true);
        if (hint)
            hint->SetFlag(1, true);
        mHintTimer.Stop();
        mHintTimer.Reset();
    }
}

// @ 0x00df9190
void FUN_00df9190(cGameUIDataBlock* self)
{
    if (self->mpChild)
        self->mpChild->v0c(1);
    cGGEGameUIDataChild* child = self->mpChild;
    if (child) {
        self->mpChild = 0;
        child->v04();
    }
    if (self->mpChild) {
        self->mpChild->v08(0);
        cGameInfo_s00df_8730* owner = self->mpGameInfo;
        self->mpChild->Setup(9, &owner, 1);
    }
    self->m2c = 0;
    IWindow_s00df_8730* w = ((cSPUILayout_s00df_8730*)self)->FindWindowByID(0x46ea4b6, true);
    if (w)
        w->SetSomething(0x37ac490, 0);
    ((cSPUILayout_s00df_8730*)self)->Shutdown(1);
    ((cGameUIDataBlockOps*)self)->Destroy();
    GameFree(self);
}

// @ 0x00df9230
void cGalaxyGameEntryScreen_s00df_8730::BuildGames()
{
    uint32_t count = mGames.size();
    if (count != 0) {
        for (uint32_t i = 0; i != count; ++i) {
            if (mGames[i].mpUIData)
                FUN_00df9190((cGameUIDataBlock*)mGames[i].mpUIData);
            cGameInfo_s00df_8730* g = &mGames[i];
            mGames[i].mpUIData = (cGameUIData_s00df_8730*)new ("UI/GGE_game_ui_data", 0, 0, 0, 0)
                cGameUIDataBlock(g);
            ((cGameUIDataBlockOps*)mGames[i].mpUIData)->InitRollover(
                g_pGameRolloverLayout,
                g_pGalaxyGameEntryUI ? (void*)((int)g_pGalaxyGameEntryUI + 4) : 0);
            if (mGames[i].mbSaved) {
                int n = 0;
                const wchar_t* text = (const wchar_t*)0x67735d4;
                switch (mGames[i].mType) {
                case 1:
                    n = 1;
                    break;
                case 2:
                    n = 2;
                    break;
                case 4:
                    n = 3;
                    break;
                case 5:
                    text = (const wchar_t*)0x67735d5;
                    n = 4;
                    break;
                }
                IWindow_s00df_8730* win = ((cSPUILayout_s00df_8730*)mGames[i].mpUIData)->FindWindowByID(0x26e0001, true);
                if (win) {
                    void* sub = win->v0c(0x106f146);
                    if (sub)
                        ((cGGEWindowEx*)sub)->mSub.SetValue(n);
                }
                win = ((cSPUILayout_s00df_8730*)mGames[i].mpUIData)->FindWindowByID(0x26e0002, true);
                if (win) {
                    void* sub = win->v0c(0x106f146);
                    if (sub)
                        ((cGGEWindowEx*)sub)->mSub.SetValue(n);
                }
                if (!g_bGGEUIDataReady) {
                    win = ((cSPUILayout_s00df_8730*)mGames[i].mpUIData)->FindWindowByID(0x3c4925e, true);
                    if (win) {
                        SP::cString_s00df_8730 text2(0x2b7a0311, (uint32_t)text, 0);
                        SetTooltipText(win, text2.GetText(-1, true));
                    }
                }
            }
            if (mGames[i].mField8c == 3) {
                IWindow_s00df_8730* win = ((cSPUILayout_s00df_8730*)mGames[i].mpUIData)->FindWindowByID(0x60a1102, true);
                if (win)
                    win->SetFlag(1, true);
                win = ((cSPUILayout_s00df_8730*)mGames[i].mpUIData)->FindWindowByID(0x60a1103, true);
                if (win)
                    win->SetFlag(1, true);
                win = ((cSPUILayout_s00df_8730*)mGames[i].mpUIData)->FindWindowByID(0x375408c, true);
                if (win)
                    win->SetFlag(2, false);
                win = ((cSPUILayout_s00df_8730*)mGames[i].mpUIData)->FindWindowByID(0x5944088, true);
                win->SetFlag(1, false);
            }
        }
    }
}

// @ 0x00df9510
void cGalaxyGameEntryScreen_s00df_8730::ClearGames()
{
    uint32_t count = mGames.size();
    for (uint32_t i = 0; i < count; ++i) {
        if (mGames[i].mpUIData)
            FUN_00df9190((cGameUIDataBlock*)mGames[i].mpUIData);
        mGames[i].mFieldb4 = 0;
        mGames[i].mpUIData = 0;
    }
    sp_vector_s00df_8730<cGameInfo_s00df_8730>& games = mGames;
    cGameInfo_s00df_8730* first = games.mpBegin;
    cGameInfo_s00df_8730* last = games.mpEnd;
    cGameInfo_s00df_8730* dst = CopyGameInfos(last, games.mpEnd, first);
    games.DestroyRange(dst, games.mpEnd);
    games.mpEnd -= (last - first);
}

// @ 0x00df95d0
void cGalaxyGameEntryScreen_s00df_8730::ResetGames()
{
    ClearGames();
    int saved = StarManager_s00df_8730()->mList.size();
    cStarManagerList* q = StarManager_s00df_8730()->QueryList();
    int added = (int)(q->mpEnd - q->mpBegin);
    int total = saved + added;
    mGames.Resize(total);
    LoadGameRange(mGames.mpBegin + saved, total - saved);
    LoadSavedGames(mGames.mpBegin, saved);
    BuildGames();
    SetupRolloverStarEffects();
}

// @ 0x00df9650
void GGUI::FUN_00df9650()
{
    bool eq = (kGUI_PanelIDs_s00df_9650->m1D8 == kGUI_PanelIDs_s00df_9650->m1DC);
    IWindow_s00df_9650* ms = (IWindow_s00df_9650*)SP_MovieSystem();
    if (ms)
        ms->Slot40(1);
    kGUI_PanelIDs_s00df_9650->Fn5300();
    kGUI_PanelIDs_s00df_9650->mGlobalUI->SetVisibility(1);
    FUN_00df95d0();
    ((IWindow_s00df_9650*)this)->Slot68();
    FUN_00df8330();
    m68 = -1;
    mTimer70.SetUnits(4);
    if (eq) {
        mTimer20.SetUnits(4);
        FUN_00df6980();
    }
    kGUI_PanelIDs_s00df_9650->Fn5260();
    IWindow_s00df_9650* w = kGUI_PanelIDs_s00df_9650->mLayout.FindWindowByID(0x615a5ff, 1);
    if (w)
        w->Slot7C(1, 1);
    FUN_00df6c40();
    kGUI_PanelIDs_s00df_9650->mGlobalUI->SetVisibility(1);
    ((AGSwarm*)FUN_00dd9190_s00df_9650())->FnB760();
    kGUI_PanelIDs_s00df_9650->Fn9ec0();
    int flag = 1;
    IWindow_s00df_9650* srv = (IWindow_s00df_9650*)SP_MessageServer();
    srv->Slot14(0x80d7451, &flag, 0);
}

// @ 0x00df9770
void GGUI::FUN_00df9770()
{
    FUN_00e00640();
    if (kGUI_PanelIDs_s00df_9650->m108 == 2) {
        IWindow_s00df_9650* w = kGUI_PanelIDs_s00df_9650->mLayout.FindWindowByID(0x615a5ff, 1);
        if (w)
            w->Slot7C(1, 1);
        kGUI_PanelIDs_s00df_9650->mGlobalUI->SetVisibility(1);
        FUN_00df95d0();
        FUN_00df6c40();
    }
}

// @ 0x00df97d0
void GGUI::FUN_00df97d0()
{
    mLayout.Shutdown(1);
}

// @ 0x00df97e0
void GGUI::FUN_00df97e0()
{
    int ids[4] = { 0x7bfb2a0, 0x7bfb2a1, 0x7bfb2a2, 0x7bfb2a3 };
    for (unsigned i = 0; i < 4; ++i) {
        IWindow_s00df_9650* w = mLayout.FindWindowByID(ids[i], 1);
        if (w)
            w->Slot7C(1, 0);
    }
}

// @ 0x00df9850
void GGUI::FUN_00df9850(unsigned index)
{
    int x = mSlots[index].x;
    int y = mSlots[index].y;
    int z = mSlots[index].z;
    IWindow_s00df_9650* w = mLayout.FindWindowByID((unsigned)kIDs[1][index], 1);
    if (!w)
        return;
    if (x == 0) {
        w->Slot7C(1, 0);
        return;
    }
    w->Slot7C(1, 1);
    ImgKey key = { x, y, z };
    key.tag = 0x2f7d0004;
    FUN_00de3f00(w, &key, 0);
}

// @ 0x00df98f0
void GGUI::FUN_00df98f0()
{
    if (mA4 == 0)
        return;
    ImgKey key = { mA4, mA8, mAC };
    key.tag = 0x2f7d0004;
    IWindow_s00df_9650* w = mLayout.FindWindowByID(0x7ca46c1, 1);
    if (w) {
        w->Slot7C(1, 1);
        FUN_00de3f00(w, &key, 0);
    }
    IWindow_s00df_9650* w2 = mLayout.FindWindowByID(0x65fbfa0, 1);
    if (w2)
        FUN_00de3f00(w2, &key, 0);
}

// @ 0x00df9990
void __fastcall FUN_00df9990(GGUI* p)
{
    kGUI_PanelIDs_s00df_9650->Fn53d0(0);
    LaunchData d;
    d.Fn4b10();
    d.m04 = p;
    d.m38 = p ? (void*)&p->mBase8 : 0;
    d.m00 = 0x7edf94a2;
    d.m30 = &LAB_00ad0e52;
    d.m11 = 1;
    FUN_0064a990(&d);
    d.Fn4b60();
}

// @ 0x00df9a00
void __fastcall FUN_00df9a00(GGUI* p)
{
    kGUI_PanelIDs_s00df_9650->Fn53d0(0);
    LaunchData d;
    d.Fn4b10();
    d.m04 = p;
    d.m38 = p ? (void*)&p->mBase8 : 0;
    d.m00 = 0x7edf94a2;
    d.m30 = &LAB_00ad0e52;
    d.m11 = 0;
    d.m12 = 1;
    FUN_0064a990(&d);
    d.Fn4b60();
}

// @ 0x00df9a70
void __fastcall FUN_00df9a70(GGUI* p)
{
    kGUI_PanelIDs_s00df_9650->Fn53d0(0);
    LaunchData d;
    d.Fn4b10();
    d.m04 = p;
    d.m38 = p ? (void*)&p->mBase8 : 0;
    d.m00 = 0x8f6443b2;
    d.m30 = &LAB_00ad0e52;
    FUN_0064a990(&d);
    d.Fn4b60();
}

// @ 0x00df9ad0
void GGUI::FUN_00df9ad0()
{
    FUN_00df97e0();
    IWindow_s00df_9650* w = mLayout.FindWindowByID(0x7ca16b4, 1);
    if (w)
        w->Slot7C(1, 1);
    w = mLayout.FindWindowByID(0x7bfce80, 1);
    if (w)
        w->Slot7C(1, 0);
    mTimer20.mUnits = 0;
}

// @ 0x00df9b30
void GGUI::FUN_00df9b30(int v)
{
    int ids[5] = { 0x5384d05, 0x5384d06, 0x5384d07, 0x5951103, 0x5951104 };
    for (unsigned i = 0; i < 5; ++i) {
        IWindow_s00df_9650* w = mLayout.FindWindowByID(ids[i], 1);
        if (w)
            w->Slot7C(2, v);
    }
    ids[0] = 0x7ccda83;
    ids[1] = 0x7ccda8d;
    ids[2] = 0x7ccdaaa;
    for (unsigned i = 0; i < 3; ++i) {
        IWindow_s00df_9650* w = mLayout.FindWindowByID(ids[i], 1);
        if (w)
            w->Slot7C(1, v);
    }
}

// @ 0x00df9be0
void GGUI::FUN_00df9be0()
{
    ((B3*)FUN_00b3d360())->Fn7dec0();
    if (mTimer20.mUnits == 10)
        kGUI_PanelIDs_s00df_9650->mMap3C.Fn9dc0(&m8c);
    if (mTimer20.mUnits == 9)
        kGUI_PanelIDs_s00df_9650->mMap3C.Fn9dc0(&mB0[0]);
    m78 = 0;
    unsigned __int64 fr;
    if (mTimer70.mUnits == 1) {
        fr = __rdtsc();
    } else {
        QueryPerformanceCounter((LI*)&fr);
    }
    m64 = (int)(fr >> 32);
    m60 = (unsigned)fr;
    m68 = 0;
    m6c = 0;
    ((AGSwarm*)FUN_00dd9190_s00df_9650())->FnBad0(&m8c);
}

// @ 0x00df9c80
void GGUI::FUN_00df9c80(unsigned id)
{
    IWindow_s00df_9650* w = mLayout.FindWindowByID(id, 1);
    if (w)
        w->Slot7C(1, 1);
    if (id == 0x7bfb2a2) {
        IWindow_s00df_9650* a = mLayout.FindWindowByID(0x5400fa5, 1);
        if (a) {
            IWindow_s00df_9650* b = (IWindow_s00df_9650*)a->Slot0C(0xcf428691);
            if (b)
                b->Slot60(m168, 0);
        }
        IWindow_s00df_9650* c = mLayout.FindWindowByID(0x7cce848, 1);
        if (c)
            c->Slot80(m168);
    }
}

// @ 0x00df9d20
void GGUI::FUN_00df9d20(void* v)
{
    int* p = (int*)v;
    if (mTimer20.mUnits == 4) {
        Slot& s = mSlots[mCur];
        s.x = p[0];
        s.y = p[1];
        s.z = p[2];
        FUN_00df9850(mCur);
    }
    if (mTimer20.mUnits == 2) {
        mA4 = p[0];
        mA8 = p[1];
        mAC = p[2];
        if (m168 != m16c) {
            *(short*)m168 = 0;
            m16c = m168;
        }
        m7f = (FUN_00eed920(&mA4, &m168) == 0);
        FUN_00df98f0();
    }
}

// @ 0x00df9dc0
void GGUI::FUN_00df9dc0(unsigned index, int v)
{
    IWindow_s00df_9650* w = mLayout.FindWindowByID((unsigned)kIDs[2][index], 1);
    if (w) {
        IWindow_s00df_9650* s = (IWindow_s00df_9650*)w->Slot0C(0x8ed27e7a);
        if (s) {
            s->Slot28(4, v);
            IWindow_s00df_9650* c = (IWindow_s00df_9650*)s->Slot10();
            c->Slot7C(0x10, 1);
        }
    }
    IWindow_s00df_9650* w2 = mLayout.FindWindowByID((unsigned)kIDs[3][index], 1);
    if (w2) {
        bool ok = ((char)v == 0);
        w2->Slot7C(2, ok);
    }
}

// @ 0x00df9e60
void GGUI::FUN_00df9e60()
{
    if (mIndex == 0) {
        FUN_00df9ad0();
        return;
    }
    --mIndex;
    mTimer20.mUnits = mItemBegin[mIndex].state;
    FUN_00df97e0();
    FUN_00df9c80(mItemBegin[mIndex].id);
    if (mTimer20.mUnits == 2 && m7c == 0)
        FUN_00df9e60();
    if (mTimer20.mUnits == 1) {
        char v = ((IWindow_s00df_9650*)SP_AppSystem())->Slot54();
        if (v == 0 && kGUI_PanelIDs_s00df_9650->m1F8 == 0)
            FUN_00df9e60();
    }
    m7e = 1;
}

// @ 0x00df9ef0
void GGUI::FUN_00df9ef0()
{
    if (mIndex < (unsigned)(mItemEnd - mItemBegin) - 1) {
        for (;;) {
            ++mIndex;
            mTimer20.mUnits = mItemBegin[mIndex].state;
            FUN_00df97e0();
            FUN_00df9c80(mItemBegin[mIndex].id);
            if (mTimer20.mUnits == 3) {
                IWindow_s00df_9650* w = mLayout.FindWindowByID(0x5951103, 1);
                if (w)
                    w->Slot7C(1, (m7d == 0));
            }
            if ((mTimer20.mUnits != 2 || m7c != 0) &&
                (mTimer20.mUnits != 4 || m7d != 0))
                break;
            if ((unsigned)(mItemEnd - mItemBegin) - 1 <= mIndex)
                return;
        }
        m7e = 1;
    }
}

// @ 0x00df9fc0
void GGUI::FUN_00df9fc0()
{
    IWindow_s00df_9650* w;
    w = mLayout.FindWindowByID(0x5951103, 1);
    if (w)
        w->Slot7C(1, (m7d == 0));
    w = mLayout.FindWindowByID(0x6451156, 1);
    if (w)
        w->Slot7C(1, (mA4 == 0));
    w = mLayout.FindWindowByID(0x7ca46c1, 1);
    if (w)
        w->Slot7C(1, (mA4 != 0));
    w = mLayout.FindWindowByID(0x7cd1558, 1);
    if (w)
        w->Slot7C(1, (m7f == 0));
    w = mLayout.FindWindowByID(0x7cd1559, 1);
    if (w)
        w->Slot7C(1, m7f);
    w = mLayout.FindWindowByID(0x5400fa5, 1);
    if (w)
        w->Slot7C(1, m7f);
    w = mLayout.FindWindowByID(0x7cce848, 1);
    if (w)
        w->Slot7C(1, (m7f == 0));
    w = mLayout.FindWindowByID(0x7cd0034, 1);
    if (w)
        w->Slot7C(1, m7f);
    w = mLayout.FindWindowByID(0x7ccc2a4, 1);
    if (w)
        w->Slot7C(1, m7f);
    w = mLayout.FindWindowByID(0x7ee01a0, 1);
    if (w) {
        if (FUN_00eed840(&mA4) == 0) {
            if (FUN_00eed970(&mA4, &m8c) != 0) {
                cString_s00df_9650 s;
                s.FUN_006b5770(0x3dade1bb, 0x7ec9f8c, 0);
                w->Slot80((void*)s.FUN_006b55c0());
                w->Slot7C(1, 1);
                s.FUN_006b5240();
            } else {
                w->Slot7C(1, 0);
            }
        } else {
            cString_s00df_9650 s;
            s.FUN_006b5770(0x3dade1bb, 0x7ec9f8c, 0);
            w->Slot80((void*)s.FUN_006b55c0());
            w->Slot7C(1, 1);
            s.FUN_006b5240();
        }
    }
    unsigned i = 0;
    do {
        w = mLayout.FindWindowByID((unsigned)kIDs[0][i], 1);
        if (w)
            w->Slot7C(1, (mSlots[i].x == 0));
        w = mLayout.FindWindowByID((unsigned)kIDs[1][i], 1);
        if (w)
            w->Slot7C(1, (mSlots[i].x != 0));
        w = mLayout.FindWindowByID((unsigned)kIDs[3][i], 1);
        if (w) {
            if (i < mCount) {
                w->Slot7C(1, 1);
                FUN_00df9850(i);
                FUN_00df9dc0(i, (unsigned char)mSlots[i].state);
            } else {
                w->Slot7C(1, 0);
            }
        }
        ++i;
    } while (i < 3);
    char flag = 0;
    int k = mCount;
    if (k != 0) {
        Slot* p = &mSlots[1];
        do {
            if (p->state == 0)
                flag = 1;
            ++p;
        } while (--k != 0);
    }
    w = mLayout.FindWindowByID(0x7ccc115, 1);
    if (w)
        w->Slot7C(2, flag);
    int st = mTimer20.mUnits;
    char flag2 = 1;
    if (st == 1)
        flag2 = (m8c.type != 0);
    else if (st == 2)
        flag2 = (mA4 != 0);
    else if (st == 3 && m7f != 0)
        flag2 = (m168 != m16c);
    if (DAT_016c7AA4->m1c->Fn4320() != 0)
        flag2 = 0;
    FUN_00df9b30(flag2);
}

// @ 0x00dfa370
void FUN_00dfa370()
{
    AGSwarm* o = (AGSwarm*)FUN_00dd9190_s00df_9650();
    o->FnB760();
    if (DAT_016a0FC8 > DAT_016a0FB8) {
        int n = _sMathRandom.RandomUint32Uniform(DAT_016a0FC8 - DAT_016a0FB8);
        n = n + DAT_016a0FB8;
        for (; n != 0; --n)
            ((AGSwarm*)FUN_00dd9190_s00df_9650())->SpawnOne();
    }
}

// @ 0x00dfa460
void GGUI::FUN_00dfa460(int* param_2, unsigned char param_3)
{
    kGUI_PanelIDs_s00df_9650->Fn53d0(0);
    Obj4C* obj = 0;
    FUN_006447c0(0, &obj);
    obj->m24 = DAT_015da7c4;
    obj->m28 = DAT_015da7c8;
    obj->m2c = DAT_015da7cc;
    obj->m30 = DAT_015da7d0;
    obj->m34 = 0;
    obj->m36 = 0;
    LD2 d;
    d.Fn4b10();
    d.m04 = this;
    Summ13* a = (Summ13*)operator_new(0x14, "Sporepedia", 0, 0, 0, 0);
    if (a == 0) {
        a = 0;
    } else {
        a->v4 = (int)vtbl_ContentValidationSummarizer;
        a->v8 = 0;
        a->v0 = (int)vtbl_AddRef;
        a->v4 = (int)vtbl_FUN_0149bad8;
        a->vc = (int)kGUI_PanelIDs_s00df_9650;
        a->v10 = 0;
    }
    d.m0c = a;
    d.m38 = this ? (void*)&mBase8 : 0;
    d.m18 = param_2[0];
    d.m1c = param_2[1];
    d.m20 = param_2[2];
    d.m00 = 0x32ece105;
    d.m30 = (void*)0x00ad0e52;
    d.m11 = 1;
    d.m24 = param_3;
    if (obj != (Obj4C*)d.m44) {
        if (obj != 0)
            obj->FnV4();
        Obj4C* prev = (Obj4C*)d.m44;
        d.m44 = obj;
        if (prev != 0)
            prev->FnV8();
    }
    FUN_0064a990(&d);
    FUN_00ef7d90();
    d.Fn4b60();
    if (obj != 0)
        obj->FnV8();
}

// @ 0x00dfa5c0
void UI_s00df_a5c0::FUN_a5c0(int a)
{
    *(int*)((char*)this + 0x34) = a;
    ((Obj_s00df_a5c0*)g_panels)->M_de53d0(0);
    void* out = 0;
    F_6447c0(0, &out);
    *(unsigned int*)((char*)out + 0x24) = (unsigned int)g_15da7c4;
    *(unsigned int*)((char*)out + 0x28) = (unsigned int)g_15da7c8;
    *(unsigned int*)((char*)out + 0x2c) = (unsigned int)g_15da7cc;
    *(unsigned int*)((char*)out + 0x30) = (unsigned int)g_15da7d0;
    *(unsigned char*)((char*)out + 0x34) = 0;
    LaunchInfo data;
    ((LaunchInfoOps*)&data)->Ctor();
    data.self = this;
    void* obj = operator_new(0x14, "Sporepedia", 0, 0, 0, 0);
    if (obj) {
        RefCountBase* b = (RefCountBase*)((char*)obj + 4);
        *(void* volatile*)&b->vtbl = &vtbl_13ec458;
        b->count = 0;
        *(void**)((char*)obj + 0x00) = &vtbl_147dc04;
        *(void**)((char*)obj + 0x04) = &vtbl_149bad8;
        *(void**)((char*)obj + 0x0c) = g_panels;
        *(unsigned char*)((char*)obj + 0x10) = 0;
    }
    data.obj = obj;
    data.f38 = (char*)this + 8;
    char* p = (char*)this + *(int*)((char*)this + 0x34) * 0x38 + 0xc0;
    data.type = 0xf25aef31;
    data.fn = &LAB_ad0e52;
    data.v18 = *(int*)p;
    data.v1c = *(int*)(p + 4);
    data.v20 = *(int*)(p + 8);
    data.b24 = 0;
    PtrAssign(data.sp44, out);
    F_64a990(&data);
    ((LaunchInfoOps*)&data)->Dtor();
    if (out) ((void(__thiscall*)(void*))(*(void***)out)[2])(out);
}

// @ 0x00dfa710
void UI_s00df_a5c0::FUN_a710(char on)
{
    void* vt = (char*)this + 0x84;
    if (*(int*)vt != 0) {
        void* o = *(void**)vt;
        ((void(__thiscall*)(void*, int))(*(void***)o)[0xc / 4])(o, 1);
        o = *(void**)vt;
        if (o != 0) {
            *(int*)vt = 0;
            ((void(__thiscall*)(void*))(*(void***)o)[4 / 4])(o);
        }
    }
    if (on != 0) {
        void* mgr = *(void**)((char*)g_panels + 0x15c);
        if (mgr != 0) {
            void* o = *(void**)vt;
            if (o != 0) {
                *(int*)vt = 0;
                ((void(__thiscall*)(void*))(*(void***)o)[4 / 4])(o);
            }
            unsigned char ok = ((unsigned char(__thiscall*)(void*, int, int, void*))(*(void***)mgr)[8 / 4])(mgr, 0x4827b9d4, 0, vt);
            if (ok) {
                void* p = *(void**)vt;
                ((void(__thiscall*)(void*, int))(*(void***)p)[8 / 4])(p, 0);
            }
        }
    }
}

// @ 0x00dfa790
void UI_s00df_a5c0::FUN_a790(char on)
{
    void* vt = (char*)this + 0x88;
    if (*(int*)vt != 0) {
        void* o = *(void**)vt;
        ((void(__thiscall*)(void*, int))(*(void***)o)[0xc / 4])(o, 1);
        o = *(void**)vt;
        if (o != 0) {
            *(int*)vt = 0;
            ((void(__thiscall*)(void*))(*(void***)o)[4 / 4])(o);
        }
    }
    if (on != 0) {
        void* mgr = *(void**)((char*)g_panels + 0x15c);
        if (mgr != 0) {
            void* o = *(void**)vt;
            if (o != 0) {
                *(int*)vt = 0;
                ((void(__thiscall*)(void*))(*(void***)o)[4 / 4])(o);
            }
            unsigned char ok = ((unsigned char(__thiscall*)(void*, int, int, void*))(*(void***)mgr)[8 / 4])(mgr, 0x139f4a74, 0, vt);
            if (ok) {
                void* p = *(void**)vt;
                ((void(__thiscall*)(void*, int))(*(void***)p)[8 / 4])(p, 0);
            }
        }
    }
}

// @ 0x00dfa810
void UI_s00df_a5c0::FUN_a810()
{
    ((Obj_s00df_a5c0*)g_panels)->M_de5470(1);
    char* lay = (char*)this + 0x48;
    for (unsigned int i = 0; i < 0x80; i += 4) {
        void* w = ((cSPUILayoutX*)lay)->FindWindowByID(*(unsigned int*)((char*)g_arr15a4318 + i), 1);
        if (w != 0) {
            void* cb = g_panels ? (char*)g_panels + 4 : 0;
            w = ((cSPUILayoutX*)lay)->FindWindowByID(*(unsigned int*)((char*)g_arr15a4318 + i), 1);
            ((void(__thiscall*)(void*, void*))(*(void***)w)[0x108 / 4])(w, cb);
        }
    }
    switch (*(int*)((char*)this + 0x20)) {
    case 1: case 2: case 4: case 5: case 7:
        break;
    default:
        if (*(int*)((char*)this + 0x84) != 0) {
            void* o = *(void**)((char*)this + 0x84);
            ((void(__thiscall*)(void*, int))(*(void***)o)[0xc / 4])(o, 1);
            o = *(void**)((char*)this + 0x84);
            if (o != 0) {
                *(int*)((char*)this + 0x84) = 0;
                ((void(__thiscall*)(void*))(*(void***)o)[4 / 4])(o);
            }
        }
        V3 zero = { 0, 0, 0 };
        *(V3*)((char*)this + 0x8c) = zero;
        *(V3*)((char*)this + 0x98) = zero;
        *(V3*)((char*)this + 0xa4) = zero;
        *(V3*)((char*)this + 0xb0) = zero;
    }
}

// @ 0x00dfa930
void UI_s00df_a5c0::FUN_a930()
{
    void* prefs = g_appPrefs;
    char value = 1;
    if (prefs != 0) {
        int prop;
        if (((unsigned char(__thiscall*)(void*, int, int*))(*(void***)prefs)[0x24 / 4])(prefs, 0x806dbba, &prop) &&
            *(short*)(prop + 0x12) == 1)
            value = *(char*)((Obj_s00df_a5c0*)prop)->M_41e920();
    }
    bool saved = false;
    if (*(int*)((char*)g_panels + 0x1f8) == 1 && value != 0) {
        saved = true;
        VariantX v;
        v.mFlags = 0;
        v.mTypeId = 0;
        bool b = false;
        v.SetBool(&b);
        ((void(__thiscall*)(void*, int, void*))(*(void***)prefs)[0x14 / 4])(prefs, 0x806dbba, &v);
        if (v.mFlags & 4)
            ((Obj_s00df_a5c0*)&v)->M_93db80(0);
        SaveResource(prefs, (unsigned int)GetSaveArea_s00df_a5c0(0x11ac192), 0);
    }
    void* lay = (char*)this + 0x48;
    void* w = ((cSPUILayoutX*)lay)->FindWindowByID(0x806e700, 1);
    if (w != 0)
        ((void(__thiscall*)(void*, int, int))(*(void***)w)[0x7c / 4])(w, 1, saved);
    w = ((cSPUILayoutX*)lay)->FindWindowByID(0x806e720, 1);
    if (w != 0)
        ((void(__thiscall*)(void*, int, int))(*(void***)w)[0x7c / 4])(w, 1, saved);
}

// @ 0x00dfaa40
int F_dfa40(int a, int b, int c)
{
    if (a != b) {
        do {
            int p = *(int*)(a + 0x10);
            if ((2 < (int)(*(int*)(a + 0x18) - p & 0xfffffffeU)) && p != 0)
                operator_delete_((void*)p);
            a += 0x24;
            c += 0x24;
        } while (a != b);
    }
    return c;
}

// @ 0x00dfaa90
int F_dfa90(int a, int b, int c)
{
    if (b == a) return c;
    do {
        int src = b - 0x24;
        int dst = c - 0x24;
        *(int*)dst = *(int*)src;
        *(int*)(dst + 4) = *(int*)(src + 4);
        *(int*)(dst + 8) = *(int*)(src + 8);
        *(unsigned char*)(dst + 0xc) = *(unsigned char*)(src + 0xc);
        if ((void*)(src + 0x10) != (void*)(dst + 0x10))
            WString_Assign(*(void**)(src + 0x10), *(void**)(src + 0x14));
        *(int*)(dst + 0x20) = *(int*)(src + 0x20);
        b = src;
        c = dst;
    } while (b != a);
    return c;
}

// @ 0x00dfaaf0
void __stdcall F_dfaf0(unsigned int a, unsigned int b)
{
    for (; a < b; a += 0x44)
        ((F28*)(a + 4))->M();
}

// @ 0x00dfab20
void UI_s00df_a5c0::FUN_ab20(bool enable)
{
    if (((Obj_s00df_a5c0*)*(void**)((char*)g_editor + 0x1c))->M_ec4320())
        enable = false;
    char* lay = (char*)this + 0x48;
    void* w;
    w = ((cSPUILayoutX*)lay)->FindWindowByID(0x733ebd5, 1);
    if (w != 0)
        ((void(__thiscall*)(void*, int, int))(*(void***)w)[0x7c / 4])(w, 1, enable);
    w = ((cSPUILayoutX*)lay)->FindWindowByID(0x7c4f832, 1);
    if (w != 0)
        ((void(__thiscall*)(void*, int, int))(*(void***)w)[0x7c / 4])(w, 1, enable);
    w = ((cSPUILayoutX*)lay)->FindWindowByID(0x73bba58, 1);
    int buf[5];
    ((cStringX*)buf)->Ctor(0x3dade1bb, 0x7eb5184, 0);
    if (w != 0) {
        bool on;
        if (*(int*)((char*)g_panels + 0x1f8) == 0) {
            void* app = AppSystem();
            on = ((unsigned char(__thiscall*)(void*))(*(void***)app)[0x54 / 4])(app);
        } else {
            on = true;
        }
        ((void(__thiscall*)(void*, int, int))(*(void***)w)[0x7c / 4])(w, 2, on);
        const void* text = on ? (const void*)&g_one : ((cStringX*)buf)->GetText();
        SetTooltipText(w, (void*)text, -1, 1);
    }
    w = ((cSPUILayoutX*)lay)->FindWindowByID(0x74d0932, 1);
    if (w != 0) {
        bool on;
        if (*(int*)((char*)g_panels + 0x1f8) == 0) {
            void* app = AppSystem();
            on = ((unsigned char(__thiscall*)(void*))(*(void***)app)[0x54 / 4])(app);
        } else {
            on = true;
        }
        ((void(__thiscall*)(void*, int, int))(*(void***)w)[0x7c / 4])(w, 2, on);
        const void* text = on ? (const void*)&g_one : ((cStringX*)buf)->GetText();
        SetTooltipText(w, (void*)text, -1, 1);
    }
    if (enable)
        FUN_a930();
    ((cStringX*)buf)->Dtor();
}

// @ 0x00dfaca0
void UI_s00df_a5c0::FUN_aca0(int* pos)
{
    *(int*)((char*)this + 0x20) = 8;
    *(int*)((char*)this + 0x24) = 9;
    *(V3*)((char*)this + 0x98) = *(V3*)pos;
    V3 zero = { 0, 0, 0 };
    *(V3*)((char*)this + 0xb0) = zero;
    FUN_ab20(0);
    void* ed = *(void**)((char*)g_editor + 0x1c);
    unsigned char ok = ((Obj_s00df_a5c0*)ed)->M_ec5a60(pos, 1, 0);
    if (ok == 0) {
        V3 z = { 0, 0, 0 };
        *(V3*)((char*)this + 0x8c) = z;
        *(V3*)((char*)this + 0x98) = z;
        *(int*)((char*)this + 0x20) = 0;
        FUN_ab20(1);
        *(unsigned char*)((char*)this + 0x7e) = 1;
    }
}

// @ 0x00dfad50
void UI_s00df_a5c0::FUN_ad50(int* pos)
{
    *(int*)((char*)this + 0x20) = 9;
    FUN_ab20(0);
    *(V3*)((char*)this + 0xb0) = *(V3*)pos;
    V3 zero = { 0, 0, 0 };
    *(V3*)((char*)this + 0x8c) = zero;
    *(int*)((char*)this + 0x28) = 10;
    Eff9* e = (Eff9*)F_ef19f0();
    e->f[0] = *(int*)((char*)this + 0x8c);
    e->f[1] = *(int*)((char*)this + 0x90);
    e->f[2] = *(int*)((char*)this + 0x94);
    e->f[3] = pos[0];
    e->f[4] = pos[1];
    e->f[5] = pos[2];
    V3 z6 = { 0, 0, 0 };
    *(V3*)&e->f[6] = z6;
    ((Obj_s00df_a5c0*)F_b3d410())->M_e3e350(1, (void*)g_d1654c10, 1);
}

// @ 0x00dfae00
UI_s00df_a5c0* UI_s00df_a5c0::FUN_ae00(void* other)
{
    char* o = (char*)other;
    ((CStr_s00df_a5c0*)this)->Assign(other);
    {
        void** src = (void**)(o + 0x14);
        if ((void*)src != (void*)((char*)this + 0x14))
            ((WStrAssign*)((char*)this + 0x14))->assign(src[0], src[1]);
    }
    *(int*)((char*)this + 0x24) = *(int*)(o + 0x24);
    *(int*)((char*)this + 0x28) = *(int*)(o + 0x28);
    {
        void** src = (void**)(o + 0x2c);
        if ((void*)src != (void*)((char*)this + 0x2c))
            ((WStrAssign*)((char*)this + 0x2c))->assign(src[0], src[1]);
    }
    return this;
}

// @ 0x00dfae50
void UI_s00df_a5c0::FUN_ae50()
{
    FUN_9ad0();
    FUN_ab20(0);
    *(int*)((char*)this + 0x20) = 10;
    *(unsigned char*)((char*)this + 0x80) = 1;
    *(int*)((char*)this + 0x28) = 10;
    ((cSPUILayoutX*)((char*)g_panels + 0x144))->SetVisibility(0);
    FUN_9be0();
}

// @ 0x00dfae90
void UI_s00df_a5c0::FUN_ae90()
{
    char* lay = (char*)this + 0x48;
    for (unsigned int i = 0; i < 0x80; i += 4) {
        void* w = ((cSPUILayoutX*)lay)->FindWindowByID(*(unsigned int*)((char*)g_arr15a4318 + i), 1);
        if (w != 0) {
            void* cb = g_panels ? (char*)g_panels + 4 : 0;
            w = ((cSPUILayoutX*)lay)->FindWindowByID(*(unsigned int*)((char*)g_arr15a4318 + i), 1);
            ((void(__thiscall*)(void*, void*))(*(void***)w)[0x104 / 4])(w, cb);
        }
    }
    void* gui = *(void**)((char*)g_panels + 0x184);
    ((cSPUIGlobalUIX*)gui)->SetVisibility(0);
    void* w = ((cSPUILayoutX*)((char*)g_panels + 0x144))->FindWindowByID(0x615a5ff, 1);
    if (w != 0)
        ((void(__thiscall*)(void*, int, int))(*(void***)w)[0x7c / 4])(w, 1, 0);
    FUN_a930();
    switch (*(int*)((char*)this + 0x20)) {
    case 1: case 2: case 4: case 5: case 7:
        break;
    default:
        *(int*)((char*)this + 0x24) = 9;
        *(int*)((char*)this + 0x20) = 0xb;
        ((Obj_s00df_a5c0*)*(void**)((char*)g_panels + 0x198))->M_de07a0(1.0f);
    }
}

// @ 0x00dfaf80
void UI_s00df_a5c0::FUN_af80()
{
    WStrX buf;
    void* q = ((Obj_s00df_a5c0*)FUN_004010a0())->M_5ecf80(&buf, 0x51aa76bb);
    if (q != (char*)this + 0x168)
        ((WStrX*)((char*)this + 0x168))->assign(*(void**)q, *(void**)((char*)q + 4));
    if ((2 < ((int)((char*)buf.mpCapacity - (char*)buf.mpBegin) & (int)0xfffffffe)) && buf.mpBegin != 0)
        operator_delete_(buf.mpBegin);
    char* lay = (char*)this + 0x48;
    void* w = ((cSPUILayoutX*)lay)->FindWindowByID(0x5400fa5, 1);
    if (w != 0) {
        void* t = ((void*(__thiscall*)(void*, int))(*(void***)w)[0xc / 4])(w, 0xcf428691);
        if (t != 0)
            ((void(__thiscall*)(void*, void*, int))(*(void***)t)[0x60 / 4])(t, *(void**)((char*)this + 0x168), 0);
    }
    w = ((cSPUILayoutX*)lay)->FindWindowByID(0x7cce848, 1);
    if (w != 0)
        ((void(__thiscall*)(void*, void*))(*(void***)w)[0x80 / 4])(w, *(void**)((char*)this + 0x168));
    *(unsigned char*)((char*)this + 0x7e) = 1;
}

// @ 0x00dfb040
void UI_s00df_a5c0::FUN_b040(int key, int arg2)
{
    (void)arg2;
    if (*(unsigned char*)((char*)this + 0x80) != 0)
        return;
    if (key != 0x1b)
        return;
    if (*(int*)((char*)this + 0x20) == 0) {
        FUN_ab20(0);
        void* au = GetSystemAT_s00df_a5c0();
        int r;
        if (au != 0) {
            r = ((int(__thiscall*)(void*))(*(void***)au)[0x20 / 4])(au);
        } else {
            r = 0;
        }
        KillSetiEffects2((void*)0xebadb118, r);
        ((Obj_s00df_a5c0*)*(void**)((char*)g_panels + 0x198))->M_de0890();
        ((Obj_s00df_a5c0*)g_panels)->M_de86d0(2, 0);
        ((Obj_s00df_a5c0*)g_panels)->M_de5330(1);
    } else {
        FUN_9ad0();
        *(int*)((char*)this + 0x20) = 0;
    }
}

// @ 0x00dfb0d0
void UI_s00df_a5c0::FUN_b0d0(char unused)
{
    (void)unused;
    int mode = *(int*)((char*)this + 0x20);
    if (mode == 7 || mode == 5)
        return;
    void* ab = AssetBrowser_s00df_a5c0();
    if (*(char*)((char*)ab + 0x1c) == 0)
        return;
    char* gp = (char*)g_panels;
    if (*(char*)(gp + 0xc9) == 0)
        return;
    if (*(int*)(gp + 0x108) != 0xd)
        return;
    ((AssetBrowserT*)AssetBrowser_s00df_a5c0())->Update();
    FUN_9ad0();
    FUN_ab20(true);
}

// @ 0x00dfb130
TypeA_s00df_a5c0* TypeA_s00df_a5c0::CopyCtor(const TypeA_s00df_a5c0* o)
{
    f0 = o->f0; f4 = o->f4; f8 = o->f8; fC = o->fC;
    s.mpBegin = s.mpEnd = s.mpCapacity = 0;
    int n = (int)((char*)o->s.mpEnd - (char*)o->s.mpBegin) >> 1;
    s.AllocateSelf(n + 1);
    wchar_t* d = s.mpBegin;
    MemThunk(d, o->s.mpBegin, (unsigned int)(n * 2));
    s.mpEnd = (wchar_t*)((char*)d + n * 2);
    *s.mpEnd = 0;
    f20 = o->f20;
    return this;
}

// @ 0x00dfb1b0
TypeC_s00df_a5c0* __stdcall Vec38_AllocCopy(int n, const void* first, const void* last)
{
    TypeC_s00df_a5c0* buf;
    if (n != 0)
        buf = (TypeC_s00df_a5c0*)operator_new((unsigned int)n * 0x38, (const char*)0x13f09b4, 0, 0,
                                  (const char*)0x13ebb38, 0xd1);
    else
        buf = 0;
    int count = n;
    FUN_00dfa3c0(&n, (void*)first, (void*)last, buf, count);
    return buf;
}

// @ 0x00dfb240
void __stdcall F_dfb240(unsigned int a, unsigned int b)
{
    for (; a < b; a += 0x24) {
        int p = *(int*)(a + 0x10);
        if ((2 < (int)(*(int*)(a + 0x18) - p & 0xfffffffeU)) && p != 0)
            operator_delete_((void*)p);
    }
}

// @ 0x00dfb280
TypeC_s00df_a5c0* TypeC_s00df_a5c0::CopyCtor(const TypeC_s00df_a5c0* o)
{
    cs.CStrCtor(o);
    s1.mpBegin = s1.mpEnd = s1.mpCapacity = 0;
    int n1 = (int)((char*)o->s1.mpEnd - (char*)o->s1.mpBegin) >> 1;
    s1.AllocateSelf(n1 + 1);
    wchar_t* d1 = s1.mpBegin;
    MemThunk(d1, o->s1.mpBegin, (unsigned int)(n1 * 2));
    s1.mpEnd = (wchar_t*)((char*)d1 + n1 * 2);
    *s1.mpEnd = 0;
    f24 = o->f24;
    f28 = o->f28;
    s2.mpBegin = s2.mpEnd = s2.mpCapacity = 0;
    int n2 = (int)((char*)o->s2.mpEnd - (char*)o->s2.mpBegin) >> 1;
    s2.AllocateSelf(n2 + 1);
    wchar_t* d2 = s2.mpBegin;
    MemThunk(d2, o->s2.mpBegin, (unsigned int)(n2 * 2));
    s2.mpEnd = (wchar_t*)((char*)d2 + n2 * 2);
    *s2.mpEnd = 0;
    return this;
}

// @ 0x00dfb380
void Vec44_s00df_a5c0::Dtor()
{
    unsigned int* v = (unsigned int*)this;
    unsigned int end = v[1];
    for (unsigned int p = *v; p < end; p += 0x44)
        ((F28*)(p + 4))->M();
    unsigned int b = *v;
    if (b != 0 && *(int*)(b - 4) != 0)
        operator_delete_((void*)b);
}

// @ 0x00dfb3c0
TypeD_s00df_a5c0& TypeD_s00df_a5c0::Assign(const TypeD_s00df_a5c0& o)
{
    TypeC_s00df_a5c0& src = *(TypeC_s00df_a5c0*)&o.c;
    TypeC_s00df_a5c0& dst = c;
    f0 = o.f0;
    dst.cs.Assign(&src.cs);
    EltStr* sp1 = &src.s1;
    if (sp1 != &dst.s1)
        dst.s1.assign(sp1->mpBegin, sp1->mpEnd);
    dst.f24 = src.f24;
    dst.f28 = src.f28;
    EltStr* sp2 = &src.s2;
    if (sp2 != &dst.s2)
        dst.s2.assign(sp2->mpBegin, sp2->mpEnd);
    f40 = o.f40;
    return *this;
}

// @ 0x00dfb430
void UI_s00df_a5c0::FUN_b430(int a)
{
    (void)a;
    FUN_ab20(0);
    FUN_97e0();
}

// @ 0x00dfb450
void UI_s00df_a5c0::FUN_b450()
{
    FUN_ab20(0);
    FUN_97e0();
}

// @ 0x00dfb470
void UI_s00df_a5c0::FUN_b470(int a)
{
    (void)a;
    ((Obj_s00df_a5c0*)g_panels)->M_de5470(0);
    FUN_a710(1);
    void* w = ((Obj_s00df_a5c0*)((char*)g_panels + 0x144))->M_8105b0(0x615a5ff, 1);
    if (w != 0)
        ((void(__thiscall*)(void*, int, int))(*(void***)w)[0x7c / 4])(w, 1, 0);
    int mode = *(int*)((char*)this + 0x20);
    switch (mode) {
    case 2:
    case 4:
    case 6: {
        V3 local = { 0, 0, 0 };
        if (a != 0) {
            local.x = *(int*)(a + 0x18);
            local.y = *(int*)(a + 0x1c);
            local.z = *(int*)(a + 0x20);
            if (local.x != 0) {
                ((void(__thiscall*)(void*, V3*))(*(void***)this)[0x40 / 4])(this, &local);
                break;
            }
        }
        if (mode == 4)
            FUN_a5c0(*(int*)((char*)this + 0x34));
        else
            FUN_a460((char*)this + 0xa4, 0);
        break;
    }
    case 1:
        FUN_9990();
        break;
    case 5:
        FUN_9a70();
        break;
    case 7:
        FUN_9a00();
        break;
    default:
        FUN_ab20(true);
        break;
    }
    ((cSPUIGlobalUIX*)*(void**)((char*)g_panels + 0x184))->SetVisibility(0);
    FUN_00ddb760(FUN_00dd9190());
    FUN_a370();
}

// @ 0x00dfb5b0
void* __fastcall FUN_00dfb5b0(int state_obj)
{
  const wchar_t* names[12];
  names[0]  = L"Neutral";
  names[1]  = L"SelectingScenarioForPlay";
  names[2]  = L"SelectingAvatarForPlay";
  names[3]  = L"NamingAvatar";
  names[4]  = L"SelectingPosse";
  names[5]  = L"SelectingTerrainForEdit";
  names[6]  = L"SelectingAvatarForEdit";
  names[7]  = L"SelectingScenarioForEdit";
  names[8]  = L"WaitingForAutoPollinate";
  names[9]  = L"ReadyToLaunchScenarioForEdit";
  names[10] = L"ReadyToLaunchScenarioForPlay";
  names[11] = L"DoingModeSelectZoomIn";

  WString_s00df_b5b0 result;
  result.begin = &gEmptyA_1667bac;
  result.end   = &gEmptyA_1667bac;
  result.cap   = &gEmptyB_1667bae;
  const wchar_t* n = names[*(int*)(state_obj + 0x20)];
  result.RangeInitialize(n);
  return &result;
}

// @ 0x00dfb720
Vec38* Vec38::Assign(const Vec38& x)
{
  if (this != &x) {
    uint32_t n = (uint32_t)((x.e - x.b) / 0x38);
    if ((uint32_t)((c - b) / 0x38) < n) {
      void* nb = Vec38_AllocCopy(this, (int)n, (void*)x.b, (void*)x.e);
      if (b && *(int*)(b - 4) != 0) EA_Free((void*)b);
      b = (uint32_t)nb;
      c = (uint32_t)((char*)nb + n * 0x38);
    } else {
      uint32_t cur = (uint32_t)((e - b) / 0x38);
      if (cur < n) {
        Vec38_Copy((void*)x.b, (void*)(x.b + cur * 0x38), (void*)b);
        VecInsertKey(this, (void*)(b + cur * 0x38), 0);
      } else {
        Vec38_Copy((void*)x.b, (void*)x.e, (void*)b);
      }
    }
    e = b + n * 0x38;
  }
  return this;
}

// @ 0x00dfb890
TypeB* TypeB::CopyCtorA(const TypeB* o)
{
  *(float*)&f0 = *(const float*)&o->f0;
  *(float*)&f4 = *(const float*)&o->f4;
  *(float*)&f8 = *(const float*)&o->f8;
  *(float*)&fC = *(const float*)&o->fC;
  *(float*)&f10 = *(const float*)&o->f10;
  *(float*)&f14 = *(const float*)&o->f14;
  *(float*)&f18 = *(const float*)&o->f18;
  v1c.assign_00473460(&o->v1c);
  f30 = o->f30;
  return this;
}

// @ 0x00dfb8e0
void* UninitCopyD_5(void* outP, const void* firstP, const void* lastP, void* dest, int n)
{
  (void)n;  // the element count is passed but never read by the original
  TypeD** out = (TypeD**)outP;
  const TypeD* first = (const TypeD*)firstP;
  const TypeD* last = (const TypeD*)lastP;
  *out = (TypeD*)dest;
  while (first != last) {
    TypeD* d = *out;
    if (d) { d->f0 = first->f0; d->c.CopyCtor(&first->c); d->f40 = first->f40; }
    *out = (TypeD*)((char*)*out + 0x44);
    first = (const TypeD*)((const char*)first + 0x44);
  }
  return outP;
}

void* CopyAssignD(void* first, void* last, void* dest);  // 0x00dfb930 (declaration-only alias: untyped spelling used by s00dfc5b0)

// @ 0x00dfb930
TypeD* CopyAssignD(TypeD* first, TypeD* last, TypeD* dest)
{
  if (first != last) {
    do {
      dest->f0 = first->f0;
      dest->c.cs.Assign(&first->c.cs);
      if (&dest->c.s1 != &first->c.s1)
        dest->c.s1.Assign(first->c.s1.begin, first->c.s1.end);
      dest->c.f24 = first->c.f24;
      dest->c.f28 = first->c.f28;
      if (&dest->c.s2 != &first->c.s2)
        dest->c.s2.Assign(first->c.s2.begin, first->c.s2.end);
      dest->f40 = first->f40;
      first = (TypeD*)((char*)first + 0x44);
      dest  = (TypeD*)((char*)dest + 0x44);
    } while (first != last);
  }
  return dest;
}

// @ 0x00dfb9c0
void Big::Init()
{
  char* self = (char*)this;
  FUN_00e00630();
  *(void**)(self + 0x08) = (void*)0x140b5a0;
  *(wchar_t**)(self + 0x38) = &gEmptyA_1667bac;
  *(wchar_t**)(self + 0x3c) = &gEmptyA_1667bac;
  *(wchar_t**)(self + 0x40) = &gEmptyB_1667bae;
  *(void**)self = (void*)0x147ee50;
  *(void**)(self + 0x08) = (void*)0x147ee4c;
  for (int i = 3; i <= 5; ++i)  *(uint32_t*)(self + i*4) = 0;   // 0x0c..0x14
  *(uint32_t*)(self + 0x20) = 0;
  *(uint32_t*)(self + 0x28) = 0;
  *(uint32_t*)(self + 0x30) = 0;
  *(uint32_t*)(self + 0x34) = 0;
  FUN_00810000(self + 0x48);
  FUN_0093a560_fn(self + 0x60, 0, 0);
  *(uint8_t*)(self + 0x7e) = 0;
  *(uint8_t*)(self + 0x7f) = 0;
  *(uint8_t*)(self + 0x80) = 0;
  for (int i = 0; i < 14; ++i) *(uint32_t*)(self + 0x84 + i*4) = 0;
  for (int i = 2; i >= 0; --i) FUN_00f257b0(self + 0xc0 + i*0x38);
  *(wchar_t**)(self + 0x168) = &gEmptyA_1667bac;
  *(wchar_t**)(self + 0x16c) = &gEmptyA_1667bac;
  *(wchar_t**)(self + 0x170) = &gEmptyB_1667bae;
}

// @ 0x00dfbac0
void Big::Destroy()
{
  char* self = (char*)this;
  wchar_t* p = *(wchar_t**)(self + 0x168);
  if ((int)((char*)*(wchar_t**)(self + 0x170) - (char*)p) > 2 && p) EA_Free(p);
  void* q = *(void**)(self + 0x88);
  if (q) ((void(__thiscall*)(void*))Vt(q)[1])(q);
  q = *(void**)(self + 0x84);
  if (q) ((void(__thiscall*)(void*))Vt(q)[1])(q);
  FUN_00811fe0(self + 0x48);
  {
    wchar_t* a = *(wchar_t**)(self + 0x38);
    if ((int)((char*)*(wchar_t**)(self + 0x40) - (char*)a) > 2 && a) EA_Free(a);
  }
  {
    TypeA* b0 = *(TypeA**)(self + 0x0c);
    TypeA* e0 = *(TypeA**)(self + 0x10);
    for (TypeA* t = b0; t < e0; ++t) t->Dtor();

    if (b0 && *(int*)((char*)b0 - 4) != 0) EA_Free(b0);
  }
  *(void**)self = (void*)0x147dba8;
}

// @ 0x00dfbb60
void Big::DestroyVec18()
{
  char* self = (char*)this;
  char* b = *(char**)(self + 0x18);
  char* e = *(char**)(self + 0x1c);
  for (char* p = b; p < e; p += 0x44) ((TypeC*)(p + 4))->dtor_f280f0();
  b = *(char**)(self + 0x18);
  if (b && *(int*)(b - 4) != 0) EA_Free(b);
}

// @ 0x00dfbba0
void Huge::Destroy()
{
  char* self = (char*)this;
  void* p = *(void**)(self + 0x4cc);
  if (p && *(int*)((char*)p - 4) != 0) EA_Free(p);
  ((TypeC*)(self + 0x448))->dtor_f280f0();
  DestroyVec44(self + 0x2dc);
  DestroyVec44(self + 0x170);
  DestroyVec44(self + 0x04);
}

// @ 0x00dfbc80
void* UninitCopyB(void* out, const void* first, const void* last, void* dest)
{
  TypeB* d = (TypeB*)dest;
  TypeB* f = (TypeB*)first;
  TypeB* l = (TypeB*)last;
  for (; f != l; ++f) {
    if (d) d->CopyCtorA(f);
    d = (TypeB*)((char*)d + 0x34);
  }
  return out;
}

// @ 0x00dfbd00
TypeB* TypeB::CopyCtorB(const TypeB* o)
{
  f0 = o->f0; f4 = o->f4; f8 = o->f8; fC = o->fC; f10 = o->f10; f14 = o->f14; f18 = o->f18;
  v1c.assign_00473500(&o->v1c);
  f30 = o->f30;
  return this;
}

// @ 0x00dfbd70
void Big::Update()
{
  char* self = (char*)this;
  uint32_t* out = (uint32_t*)FUN_00ef19f0();
  if (*(uint32_t*)(self + 0x20) == 9) {
    out[0] = *(uint32_t*)(self + 0x8c);
    out[1] = *(uint32_t*)(self + 0x90);
    out[2] = *(uint32_t*)(self + 0x94);
    out[3] = *(uint32_t*)(self + 0xb0);
    out[4] = *(uint32_t*)(self + 0xb4);
    out[5] = *(uint32_t*)(self + 0xb8);
    out[9] = 1;
    out[10] = 0;
    FUN_00de4850(*(void**)self);
  } else {
    FUN_00de4850(*(void**)self);
    out[0] = *(uint32_t*)(self + 0x8c);
    out[1] = *(uint32_t*)(self + 0x90);
    out[2] = *(uint32_t*)(self + 0x94);
    out[9] = 2;
    out[10] = 1;
    FUN_0050f740(out + 0xc, (void*)out[0xc], (void*)out[0xd]);
    uint32_t cnt = *(uint32_t*)(self + 0x30);
    for (uint32_t i = 0; i < cnt; ++i) {
      char* e = self + 0xc0 + i * 0x38;
      if (*(uint8_t*)(e + 0x20) == 0) {
        uint32_t* dst = (uint32_t*)out[0xd];
        if (dst < (uint32_t*)out[0xe]) {
          out[0xd] = (uint32_t)(dst + 3);
          if (dst) { dst[0] = *(uint32_t*)e; dst[1] = *(uint32_t*)(e+4); dst[2] = *(uint32_t*)(e+8); }
        } else {
          VecInsertKey(out + 0xc, dst, e);
        }
      }
    }
    if (*(uint8_t*)(self + 0x7c)) {
      char* q = self + 0xa4;
      if (FUN_00eecba0(q) != 0x4178b8e8)
        FUN_00646370(q, q + 4, q + 8, q, 0x4178b8e8, 1);
      void* tmp = 0;
      if (!FUN_005bf0e0(q, &tmp)) {
        if (tmp) { ((void(__thiscall*)(void*))Vt(tmp)[1])(tmp); tmp = 0; }
        FUN_005bf3a0(q, (void*)0x15a44c0, &tmp, 0);
        FUN_00eebf90(tmp, self + 0x168);
      }
      if (FUN_006419f0(q)) {
        void* ms = FUN_0067dd20();
        ((void(__thiscall*)(void*, uint32_t, void*, int))Vt(ms)[5])(ms, 0x73e46f6, q, 0);
      }
      if (tmp) ((void(__thiscall*)(void*))Vt(tmp)[1])(tmp);
    }
    out[6] = *(uint32_t*)(self + 0xa4);
    out[7] = *(uint32_t*)(self + 0xa8);
    out[8] = *(uint32_t*)(self + 0xac);
  }
  *(uint32_t*)(self + 0x20) = 0;
  void* r = *(void**)(self + 0x84);
  if (r) {
    ((void(__thiscall*)(void*, int))Vt(r)[3])(r, 1);
    r = *(void**)(self + 0x84);
    if (r) { *(void**)(self + 0x84) = 0; ((void(__thiscall*)(void*))Vt(r)[1])(r); }
  }
  FUN_00dfab20(0);
  r = *(void**)(self + 0x88);
  if (r) {
    ((void(__thiscall*)(void*, int))Vt(r)[3])(r, 1);
    r = *(void**)(self + 0x88);
    if (r) { *(void**)(self + 0x88) = 0; ((void(__thiscall*)(void*))Vt(r)[1])(r); }
  }
  FUN_00dd9190_s00df_b5b0();
  FUN_00ddb760();
  void* w = FUN_0067dd20();
  ((void(__thiscall*)(void*, uint32_t))Vt(w)[10])(w, 0x21851ebe);
}

// @ 0x00dfc000
void VecA::Insert(TypeA* position, const TypeA* value)
{
  char* s = (char*)this;
  uint32_t end = *(uint32_t*)(s + 4);
  const TypeA* val = value;
  if (end != *(uint32_t*)(s + 8)) {
    if ((uint32_t)val >= (uint32_t)position && (uint32_t)val < end)
      val = (TypeA*)((char*)val + 0x24);
    if (end) ((TypeA*)end)->CopyCtor((TypeA*)(end - 0x24));
    // copy_backward of [begin, end-0x24) into (position, end)
    char* src = (char*)end - 0x24;
    char* dst = (char*)end;
    while (src > (char*)position) {
      src -= 0x24; dst -= 0x24;
      ((TypeA*)dst)->CopyCtor((TypeA*)src);
      ((TypeA*)src)->Dtor();
    }
    position->f0 = val->f0; position->f4 = val->f4; position->f8 = val->f8;
    position->fC = val->fC;
    if (&position->s != &val->s) position->s.Assign(val->s.begin, val->s.end);
    position->f20 = val->f20;
    *(uint32_t*)(s + 4) = end + 0x24;
    return;
  }
  int n = (int)(((char*)end - *(char**)s) / 0x24);
  int cap = (n == 0) ? 1 : n * 2;
  void* buf = 0;
  if (cap != 0)
    buf = EA_Allocate(cap * 0x24, "Simulator", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
  char* oldb = *(char**)s;
  char* o = (char*)buf;
  for (char* p = oldb; p != (char*)end; p += 0x24) {
    if (p == (char*)position) { ((TypeA*)o)->CopyCtor(val); }
    else ((TypeA*)o)->CopyCtor((TypeA*)p);
    o += 0x24;
  }
  if (position == (TypeA*)end) ((TypeA*)o)->CopyCtor(val);
  if (oldb && *(int*)(oldb - 4) != 0) EA_Free(oldb);
  *(void**)s = buf;
  *(void**)(s + 4) = (char*)buf + (n + 1) * 0x24;
  *(void**)(s + 8) = (char*)buf + cap * 0x24;
}

// @ 0x00dfc170
void* CopyRangeB(void* first, void* last, void* dest)
{
  while (first != last) {
    *(float*)dest = *(float*)first;
    ((uint32_t*)dest)[1] = ((uint32_t*)first)[1];
    ((uint32_t*)dest)[2] = ((uint32_t*)first)[2];
    ((uint32_t*)dest)[3] = ((uint32_t*)first)[3];
    ((uint32_t*)dest)[4] = ((uint32_t*)first)[4];
    ((uint32_t*)dest)[5] = ((uint32_t*)first)[5];
    ((uint32_t*)dest)[6] = ((uint32_t*)first)[6];
    FUN_00473500((char*)dest + 0x1c, (char*)first + 0x1c);
    ((uint32_t*)dest)[0xc] = ((uint32_t*)first)[0xc];
    first = (char*)first + 0x34;
    dest  = (char*)dest + 0x34;
  }
  return dest;
}

// @ 0x00dfc1e0
void* __stdcall AllocCopyD(int n, void* first, void* last)
{
  // the pool request keeps the element count in eax and derives the byte size from it
  void* buf = n ? AllocSizeD((uint32_t)n) : 0;
  // retail pushes the element count as a fourth (never read) argument slot
  UninitCopyD_5((void**)&n, first, last, buf, n);
  return buf;
}

// @ 0x00dfc240
void Big::Update2(int arg)
{
  char* self = (char*)this;
  (void)arg;
  if (*(uint32_t*)(self + 0x20) == 0) {
    if (!FUN_00dd9190_s00df_b5b0()->GetLinkCount(0)) sub_dfa370();
  }
  if (*(uint8_t*)(self + 0x7e)) { sub_df9fc0(); *(uint8_t*)(self + 0x7e) = 0; }
  if (*(uint32_t*)(self + 0x20) != 0xb) {
    void* obj84 = *(void**)(self + 0x84);
    if (obj84) {
      Desc38 d;
      Vec3g pos;
      pos = g_vec_16a173c;                   // defaults (overwritten below)
      d.pos = pos;
      d.scale = g_scale_1485720;
      d.mat.CopyCtor_0041cb40(&g_mat_16a1718);
      d.kind = 4;
      d.sub = 1;
      pos.x = 0.0f;
      pos.y = 0.0f;
      pos.z = g_depth_147eeac;
      d.pos = pos;
      d.scale = g_scale_1485720;
      d.mat = g_mat_16a1718;
      ((void(__thiscall*)(void*, Desc38*))Vt(obj84)[5])(obj84, &d);
    }
    if (*(uint8_t*)(self + 0x80) == 0) {
      uint32_t e = *(uint32_t*)(self + 0x28);
      if (e) { *(uint32_t*)(self + 0x28) = e - 1; return; }
      uint32_t st = *(uint32_t*)(self + 0x20);
      if (st == 10 || st == 9) { Update(); return; }
      if (FUN_00b3d360_s00df_b5b0()->sub_de46e0()) { ((Obj3c*)(g_16a1344_s00df_b5b0 + 0x3c))->sub_de7010(); return; }
    } else {
      if (*(uint32_t*)(self + 0x78) == 0) {
        double t = (double)((Stopwatch_s00df_b5b0*)(self + 0x60))->sub_0093a3a0();
        if (t * *(float*)(self + 0x74) > 0.5f) {
          sub_dfa790(1);
          *(uint32_t*)(self + 0x78) = 1;
        }
      }
      if (*(uint32_t*)(self + 0x78) == 1) {
        B3Obj* g = FUN_00b3d360_s00df_b5b0();
        int empty = ((int)g->head == (int)&g->head);
        void* w = FUN_00401010();
        int v = ((int(__thiscall*)(void*))Vt(w)[10])(w);
        char busy = ((Ec43*)(*(char**)(g_16c7aa4 + 0x1c)))->sub_ec4320();
        if (!busy && v < 1 && empty) *(uint32_t*)(self + 0x78) = 2;
      }
      if (*(uint32_t*)(self + 0x78) == 2) {
        if (FUN_00dd9190_s00df_b5b0()->IsReady()) {
          *(uint8_t*)(self + 0x80) = 0;
          *(uint32_t*)(self + 0x28) = 10;
          void* r = *(void**)(self + 0x84);
          if (r) {
            ((void(__thiscall*)(void*, int))Vt(r)[3])(r, 1);
            r = *(void**)(self + 0x84);
            if (r) { *(void**)(self + 0x84) = 0; ((void(__thiscall*)(void*))Vt(r)[1])(r); }
          }
          uint32_t* o = (uint32_t*)FUN_00ef19f0();
          o[0] = *(uint32_t*)(self + 0x8c);
          o[1] = *(uint32_t*)(self + 0x90);
          o[2] = *(uint32_t*)(self + 0x94);
          o[6] = *(uint32_t*)(self + 0xa4);
          o[7] = *(uint32_t*)(self + 0xa8);
          o[8] = *(uint32_t*)(self + 0xac);
          FUN_00b3d410_s00df_b5b0()->sub_e3e350(1, (void*)0x1654c10, 1);
          return;
        }
      }
    }
  }
}

// @ 0x00dfc500
char Big::Check()
{
  char* self = (char*)this;
  WString_s00df_b5b0 tmp;
  tmp.begin = &gEmptyA_1667bac;
  tmp.end   = &gEmptyA_1667bac;
  tmp.cap   = &gEmptyB_1667bae;
  char res = 0;
  WString_s00df_b5b0* src = (WString_s00df_b5b0*)(self + 0x168);
  int n = (int)((char*)src->end - (char*)src->begin) >> 1;
  if (n != 0) {
    for (int i = 0; i < n; ++i) {
      wchar_t c = src->begin[i];
      if (!FUN_00f56f0(c)) res = 1;
      else tmp.push_back(c);
    }
    if (res && &tmp != src) src->Assign(tmp.begin, tmp.end);
  }
  if ((char*)tmp.cap - (char*)tmp.begin > 2 && tmp.begin) EA_Free(tmp.begin);
  return res;
}

// @ 0x00dfc5b0
void Blob5b0::dtor()
{
    if (mp20c && *(int*)((char*)mp20c - 4) != 0) operator_delete(mp20c);
    Sub28Vec* v = (Sub28Vec*)((char*)this + 0x28);
    v->sub_dfb850(*(void**)v, ((void**)v)[1]);
    void* b = *(void**)v;
    if (b && *(int*)((char*)b - 4) != 0) operator_delete(b);
}

// @ 0x00dfc600
void EffectVec::EraseRange(u32 first, u32 last)
{
    if (first >= last) return;
    do {
        u32 end = *(u32*)(first + 0x1c);
        for (u32 e = *(u32*)(first + 0x18); e < end; e += 0x44) {
            ((Elem44*)(e + 4))->sub_f280f0();
        }
        int p = *(int*)(first + 0x18);
        if (p && *(int*)(p - 4) != 0) operator_delete((void*)p);
        first += 0x188;
    } while (first < last);
}

// @ 0x00dfc6f0
void GgeLayout::Init()
{
    char* self = (char*)this;
    const wchar_t* base = (const wchar_t*)0x147ef18;      // L"GGENewScenariov3"
    const wchar_t* e = base;
    do { ++e; } while (*e);
    FUN_00423650(self + 0x38, 0, (void*)base, (void*)e);
    FUN_00812160(self + 0x48, 0, *(void**)(self + 0x38), 0x40464100u, 1, 0x5b598fau);
    FUN_0093a1a0(self + 0x60, 0, 5);
    GgeRect client;    void* app = FUN_0067dd10();
    void* mainWin = ((void* (__fastcall*)(void*, int))Vfn(app, 0x58))(app, 0);
    FUN_007c4010(mainWin, 0, (int*)&client);
    float cx = (float)((client.right - client.left) / 2);
    float cy = (float)((client.bottom - client.top) / 2);
    void* win = FUN_008105b0(self + 0x48, 0, 0x733ebd5u, 1);
    if (win) {
        float* a = ((float* (__fastcall*)(void*, int))Vfn(win, 0x38))(win, 0);
        const float k = *(float*)0x1471064;
        ((void (__fastcall*)(void*, int, float, float))Vfn(win, 0x64))(
            win, 0, cx - (a[2] - a[0]) * k, cy - (a[3] - a[1]) * k);
        ((void (__fastcall*)(void*, int, int, int))Vfn(win, 0x7c))(win, 0, 1, 0);
    }
    AddPanelEntry(self, 0, (const wchar_t*)0x147eef4);     // "choose adventure"
    AddPanelEntry(self, 1, (const wchar_t*)0x147eecc);     // "choose captain name"
    AddPanelEntry(self, 2, (const wchar_t*)0x147eecc);     // "choose captain name"
    AddPanelEntry(self, 3, (const wchar_t*)0x147eeb0);     // "choose posse"
}

// @ 0x00dfca50
Entry38& Entry38::operator=(const Entry38& o)
{
    m08 = o.m08;
    m0c = o.m0c;
    m10 = o.m10;
    m14 = o.m14;
    mVec = o.mVec;
    void* src = o.mp30;
    void* cur = mp30;
    if (src != cur) {
        if (src) {
            typedef int (__thiscall *RefFn)(void*);
            RefFn f = *(RefFn*)(*(void**)src);
            f(src);
        }
        mp30 = src;
        if (cur) {
            typedef int (__thiscall *RefFn)(void*);
            RefFn f = *(RefFn*)((char*)*(void**)cur + 4);
            f(cur);
        }
    }
    m34 = o.m34;
    return *this;
}

// @ 0x00dfcac0
void BlobAC0::dtor()
{
    u32 end = mpEnd;
    for (u32 e = mpBegin; e < end; e += 0x4e0) ((Elem4e0*)e)->sub_dfbba0();
    u32 v = mpBegin;
    if (v && *(int*)(v - 4) != 0) operator_delete((void*)v);
}

// @ 0x00dfcb00
Vec44& Vec44::assignFrom(const Vec44& o)
{
    if ((void*)&o == (void*)this)
        return *this;
    unsigned n = (unsigned)((char*)o.mpEnd - (char*)o.mpBegin) / 0x44;
    unsigned c = (unsigned)((char*)mpCap - (char*)mpBegin) / 0x44;
    if (c < n) {
        void* p = FUN_00dfc1e0(this, 0, n, o.mpBegin, o.mpEnd);
        FUN_00dfaaf0(this, 0, mpBegin, mpEnd);
        if (mpBegin && *(int*)((char*)mpBegin - 4) != 0)
            operator_delete(mpBegin);
        mpBegin = p;
        mpCap   = (char*)p + n * 0x44;
    } else {
        unsigned sz = (unsigned)((char*)mpEnd - (char*)mpBegin) / 0x44;
        if (sz < n) {
            CopyAssignD(o.mpBegin, (char*)o.mpBegin + sz * 0x44, mpBegin);
            void* srcEnd = o.mpEnd;
            UninitCopyD(&srcEnd, (char*)o.mpBegin + sz * 0x44, o.mpEnd, mpEnd,
                        o.mpEnd);
        } else {
            void* dst = CopyAssignD(o.mpBegin, o.mpEnd, mpBegin);
            FUN_00dfaaf0(this, 0, dst, mpEnd);
        }
    }
    mpEnd = (char*)mpBegin + n * 0x44;
    return *this;
}

// @ 0x00dfcc40
void BlobC40::dtor()
{
    bool skip = (((unsigned)mField00 >> 31) & 1) != 0;
    if (skip) return;
    int a = mField210;
    if (a && *(int*)(a - 4) != 0) operator_delete((void*)a);
    Sub28Vec* v = (Sub28Vec*)((char*)this + 0x2c);
    v->sub_dfb850(*(void**)v, ((void**)v)[1]);
    int b = *(int*)v;
    if (b && *(int*)(b - 4) != 0) operator_delete((void*)b);
}

// @ 0x00dfcc90
Entry188& Entry188::operator=(const Entry188& o)
{
    m00 = o.m00;
    m04 = o.m04;
    m08 = o.m08;
    m0c = o.m0c;
    m10 = o.m10;
    m14 = o.m14;
    mVec.assignFrom(o.mVec);
    m184 = o.m184;
    return *this;
}

// @ 0x00dfcce0
BigRec& BigRec::ctorr(const BigRec& o)
{
    m00 = o.m00;
    m01 = o.m01;
    m02 = o.m02;
    mVec04.assignFrom(o.mVec04);
    mVec170.assignFrom(o.mVec170);
    mVec2dc.assignFrom(o.mVec2dc);
    FUN_006b5430((char*)this + 0x448, 0, (const char*)&o + 0x448);
    if ((char*)&o + 0x45c != (char*)this + 0x45c)
        FUN_00423650((char*)this + 0x45c, 0, o.mW45c, o.mW460);
    m46c = o.m46c;
    m470 = o.m470;
    if ((char*)&o + 0x474 != (char*)this + 0x474)
        FUN_00423650((char*)this + 0x474, 0, o.mW474, o.mW478);
    f484 = o.f484;
    f488 = o.f488; f48c = o.f48c; f490 = o.f490; f494 = o.f494;
    f498 = o.f498; f49c = o.f49c; f4a0 = o.f4a0;
    m4a4 = o.m4a4; m4a8 = o.m4a8; m4ac = o.m4ac; m4b0 = o.m4b0;
    m4b4 = o.m4b4; m4b8 = o.m4b8; m4bc = o.m4bc; m4c0 = o.m4c0; m4c4 = o.m4c4;
    m4c8 = o.m4c8;
    FUN_00c06b10((char*)this + 0x4cc, 0, (const char*)&o + 0x4cc);
    return *this;
}

// @ 0x00dfce40
void BlobE40::dtor()
{
    ((EffectVec*)((char*)this + 0x84))->EraseRange((u32)mp84, (u32)mp88);
    if (mp84 && *(int*)((char*)mp84 - 4) != 0) operator_delete(mp84);
    m3c.sub_f280f0();
    ((Elem3c*)this)->sub_f280f0();
}

// @ 0x00dfce90
void BlobE90::dtor()
{
    m2788.sub_f280f0();
    u32 end = mpEnd74;
    for (u32 e = mpBegin70; e < end; e += 0x4e0) ((Elem4e0*)e)->sub_dfbba0();
    u32 v = mpBegin70;
    if (v && *(int*)(v - 4) != 0) operator_delete((void*)v);
}

// @ 0x00dfcee0
Vec34& Vec34::assignFrom(const Vec34& o)
{
    if ((void*)&o == (void*)this)
        return *this;
    Vec34M* t = (Vec34M*)this;
    Vec34M* s = (Vec34M*)&o;
    unsigned n = (unsigned)((char*)s->mpEnd - (char*)s->mpBegin) / 0x34;
    unsigned c = (unsigned)((char*)t->mpCap - (char*)t->mpBegin) / 0x34;
    if (c < n) {
        void* p = FUN_00dfc690(t, 0, n, s->mpBegin, s->mpEnd);
        FUN_00dfb850(t, 0, t->mpBegin, t->mpEnd);
        if (t->mpBegin && *(int*)((char*)t->mpBegin - 4) != 0)
            operator_delete(t->mpBegin);
        t->mpEnd   = (char*)p + n * 0x34;
        t->mpBegin = p;
        t->mpCap   = (char*)p + n * 0x34;
        return *this;
    }
    unsigned sz = (unsigned)((char*)t->mpEnd - (char*)t->mpBegin) / 0x34;
    if (sz < n) {
        FUN_00dfc170(s->mpBegin, (char*)s->mpBegin + sz * 0x34, t->mpBegin);
        void* srcEnd = s->mpEnd;
        void* dstMid = (char*)t->mpBegin + sz * 0x34;
        vec34UninitCopy(&t->mpEnd, (char*)s->mpBegin + sz * 0x34, srcEnd, dstMid,
                        srcEnd);
        t->mpEnd = (char*)t->mpBegin + n * 0x34;
        return *this;
    }
    char* p2 = (char*)FUN_00dfc170(s->mpBegin, s->mpEnd, t->mpBegin);
    FUN_00dfb850(t, 0, p2, t->mpEnd);
    t->mpEnd = (char*)t->mpBegin + n * 0x34;
    return *this;
}

// @ 0x00dfd020
Entry188& Entry188::ctorr(const Entry188& o)
{
    m00 = o.m00;
    m04 = o.m04;
    m08 = o.m08;
    m0c = o.m0c;
    m10 = o.m10;
    m14 = o.m14;
    Vec44* v = &mVec;
    char* beg = (char*)v + 0x18;
    v->mpBegin = beg;
    v->mpEnd   = beg;
    v->mpCap   = beg + 0x154;
    v->mOwner  = 0;
    mVec.assignFrom(o.mVec);
    m184 = o.m184;
    return *this;
}

// @ 0x00dfd080
Huge_s00df_c5b0& Huge_s00df_c5b0::copyCtor(const Huge_s00df_c5b0& o)
{
    m00 = o.m00;
    m01 = o.m01;
    m02 = o.m02;
    struct Init { static void Run(Vec44* v) {
        char* beg = (char*)v + 0x18;
        v->mpBegin = beg;
        v->mpEnd   = beg;
        v->mpCap   = beg + 0x154;
        v->mOwner  = 0;
    } };
    Init::Run(&mVec04);
    mVec04.assignFrom(o.mVec04);
    Init::Run(&mVec170);
    mVec170.assignFrom(o.mVec170);
    Init::Run(&mVec2dc);
    mVec2dc.assignFrom(o.mVec2dc);
    FUN_00dfb280((char*)this + 0x448, 0, (const char*)&o + 0x448);
    f484 = o.f484; f488 = o.f488; f48c = o.f48c; f490 = o.f490;
    f494 = o.f494; f498 = o.f498; f49c = o.f49c; f4a0 = o.f4a0;
    m4a4 = o.m4a4; m4a8 = o.m4a8; m4ac = o.m4ac; m4b0 = o.m4b0;
    m4b4 = o.m4b4; m4b8 = o.m4b8; m4bc = o.m4bc; m4c0 = o.m4c0; m4c4 = o.m4c4;
    m4c8 = o.m4c8;
    unsigned n = (unsigned)((char*)o.mp4ccEnd - (char*)o.mp4ccBegin) / 0x20;
    FUN_00dfa400(&mp4ccBegin, 0, n, (char*)&o + 0x4d8);
    void* cur = mp4ccBegin;
    placeCopy20(&cur, o.mp4ccBegin, o.mp4ccEnd, mp4ccBegin, &o);
    mp4ccEnd = cur;
    return *this;
}

// @ 0x00dfd250
char* uninitCopy188(char* first, char* last, char* dst)
{
    for (; first != last; first += 0x188, dst += 0x188) {
        Entry188* d = (Entry188*)dst;
        Entry188* s = (Entry188*)first;
        d->m00 = s->m00;
        d->m04 = s->m04;
        d->m08 = s->m08;
        d->m0c = s->m0c;
        d->m10 = s->m10;
        d->m14 = s->m14;
        d->mVec.assignFrom(s->mVec);
        d->m184 = s->m184;
    }
    return dst;
}

// @ 0x00dfd300
void __stdcall d300(int* first, int* last)
{
    if (first >= last) return;
    int* pi = first + 0x84;
    do {
        bool negative = (((u32)*first) >> 31) & 1;
        if (!negative) {
            int x = *pi;
            if (x && *(int*)(x - 4) != 0) operator_delete((void*)x);
            u32 e1 = (u32)pi[-0x78];
            for (u32 u = (u32)pi[-0x79]; u < e1; u += 0x34) {
                int y = *(int*)(u + 0x1c);
                if (y && *(int*)(y - 4) != 0) operator_delete((void*)y);
            }
            int z = pi[-0x79];
            if (z && *(int*)(z - 4) != 0) operator_delete((void*)z);
        }
        first += 0x8e;
        pi += 0x8e;
    } while (first < last);
}

// @ 0x00dfd3a0
Sub028& Sub028::operator=(const Sub028& o)
{
    m00 = o.m00; m04 = o.m04; m08 = o.m08; m0c = o.m0c;
    m10 = o.m10; m14 = o.m14; m18 = o.m18; m1c = o.m1c;
    f20 = o.f20;
    f24 = o.f24;
    mVec28.assignFrom(o.mVec28);
    f1e0 = o.f1e0;
    f1e4 = o.f1e4;
    m1e8 = o.m1e8; m1ec = o.m1ec; m1f0 = o.m1f0; m1f4 = o.m1f4;
    m1f8 = o.m1f8; m1fc = o.m1fc; m200 = o.m200;
    f204 = o.f204;
    b208 = o.b208;
    b209 = o.b209;
    m20c = o.m20c;
    f220 = o.f220;
    m224 = o.m224; m228 = o.m228; m22c = o.m22c; m230 = o.m230;
    return *this;
}

// @ 0x00dfd4e0
char** placeCopy188(char** cur, char* first, char* last, char* dst)
{
    *cur = dst;
    for (; first != last; first += 0x188) {
        Entry188* p = (Entry188*)*cur;
        if (p) {
            Entry188* s = (Entry188*)first;
            p->m00 = s->m00;
            p->m04 = s->m04;
            p->m08 = s->m08;
            p->m0c = s->m0c;
            p->m10 = s->m10;
            p->m14 = s->m14;
            p->mVec.mpBegin = (char*)p + 0x30;
            p->mVec.mpEnd   = (char*)p + 0x30;
            p->mVec.mOwner  = 0;
            p->mVec.mpCap   = (char*)p + 0x184;
            p->mVec.assignFrom(s->mVec);
            p->m184 = s->m184;
        }
        *cur = *cur + 0x188;
    }
    return cur;
}

// @ 0x00dfd5b0
void Simulator::cEditorModeUI::Setup()
{
    using namespace SP::FunctionalMatch;
    CVec constraints;
    char cbuf[0x24];
    Constraint_s00df_d5b0* c = (Constraint_s00df_d5b0*)cbuf;

    Constraint_ctorEqual_558960(c, 0, 0x2dd90af, 0, 0x2b978c46);
    constraints.push_back(*c);
    c->mConstraints.destroy();

    Constraint_ctorEqual_558960(c, 0, 0x54a32960, 0, 1);
    constraints.push_back(*c);
    c->mConstraints.destroy();

    CVec sub;
    Constraint_ctorEqual_558960(c, 0, 0xec2942cd, 0, 1);
    sub.push_back(*c);
    c->mConstraints.destroy();

    Constraint_ctorNotEq_558a20(c, 0, 0x2dc9d1e, 0, 0x4178b8e8);
    sub.push_back(*c);
    c->mConstraints.destroy();

    char abuf[0x24];
    Constraint_s00df_d5b0* any = (Constraint_s00df_d5b0*)abuf;
    Constraint_ctorAny_558ae0(any, 0, 0, sub);
    constraints.push_back(*any);
    any->mConstraints.destroy();

    CVec templates;
    DBFindTemplates(&templates, &constraints);
    if (templates.mpBegin != templates.mpEnd) {
        unsigned n = (unsigned)((char*)templates.mpEnd - (char*)templates.mpBegin) / 0xc;
        unsigned i = cRandomGlobal.RandomUint32Uniform(n);
        unsigned* e = (unsigned*)((char*)templates.mpBegin + i * 0xc);
        unsigned elem[3];
        elem[0] = e[0];
        elem[1] = e[1];
        elem[2] = e[2];
        ((void(__thiscall*)(void*, void*))(*(void***)this)[0x40 / 4])(this, elem);
    }
    freeQuery(templates.mpBegin);
    sub.destroy();
    constraints.destroy();
}

// @ 0x00dfd8a0
void Simulator::cEditorModeUI::RebuildPanel()
{
    using namespace SP::FunctionalMatch;
    CVec constraints;
    char cbuf[0x24];
    Constraint_s00df_d5b0* c = (Constraint_s00df_d5b0*)cbuf;

    Constraint_ctorEqual_558960(c, 0, 0x2dd90af, 0, 0x2b978c46);
    constraints.push_back(*c);
    c->mConstraints.destroy();

    Constraint_ctorEqual_558960(c, 0, 0x54a32960, 0, 1);
    constraints.push_back(*c);
    c->mConstraints.destroy();

    CVec templates;
    DBFindTemplates(&templates, &constraints);
    if (templates.mpBegin != templates.mpEnd) {
        unsigned n = (unsigned)((char*)templates.mpEnd - (char*)templates.mpBegin) / 0xc;
        unsigned i = cRandomGlobal.RandomUint32Uniform(n);
        unsigned* e = (unsigned*)((char*)templates.mpBegin + i * 0xc);
        unsigned elem[3];
        elem[0] = e[0];
        elem[1] = e[1];
        elem[2] = e[2];
        ((void(__thiscall*)(void*, void*))(*(void***)this)[0x40 / 4])(this, elem);
    }
    freeQuery(templates.mpBegin);
    constraints.destroy();
}

// @ 0x00dfda50
int* SP::cSPUIMissions::QueryMissionFields(void* outPtr)
{
    using namespace SP::FunctionalMatch;
    CVec constraints;
    char cbuf[0x24];
    Constraint_s00df_d5b0* c = (Constraint_s00df_d5b0*)cbuf;

    Constraint_ctorEqual_558960(c, 0, 0x2dd90af, 0, 0x366a930d);
    constraints.push_back(*c);
    c->mConstraints.destroy();

    Constraint_ctorEqual_558960(c, 0, 0x54a32960, 0, 1);
    constraints.push_back(*c);
    c->mConstraints.destroy();

    CVec templates;
    DBFindTemplates(&templates, &constraints);

    unsigned* out = (unsigned*)outPtr;
    unsigned* p = (unsigned*)templates.mpBegin;
    unsigned* last = (unsigned*)templates.mpEnd;
    while (p != last) {
        unsigned elem[3];
        elem[0] = p[0];
        elem[1] = p[1];
        elem[2] = p[2];
        int state = GetAssetState_552300(elem);
        if (state == 0 && elem[0] == g_16a1058) {
            out[0] = elem[0];
            out[1] = elem[1];
            out[2] = elem[2];
            freeQuery(templates.mpBegin);
            constraints.destroy();
            return (int*)out;
        }
        p += 3;
    }
    out[0] = 0;
    out[1] = 0;
    out[2] = 0;
    freeQuery(templates.mpBegin);
    constraints.destroy();
    return (int*)out;
}

// @ 0x00dfdc50
void Simulator::cEditorModeUI::Setup2()
{
    using namespace SP::FunctionalMatch;
    CVec constraints;
    char cbuf[0x24];
    Constraint_s00df_d5b0* c = (Constraint_s00df_d5b0*)cbuf;

    Constraint_ctorEqual_558960(c, 0, 0x2dd90af, 0, 0x366a930d);
    constraints.push_back(*c);
    c->mConstraints.destroy();

    Constraint_ctorEqual_558960(c, 0, 0x54a32960, 0, 1);
    constraints.push_back(*c);
    c->mConstraints.destroy();

    CVec templates;
    DBFindTemplates(&templates, &constraints);

    char* tbl = (char*)templates.mpBegin;
    unsigned n = (tbl != (char*)templates.mpEnd)
               ? (unsigned)((char*)templates.mpEnd - tbl) / 0xc : 0;
    if (n != 0) {
        unsigned elem[3];
        bool done;
        void* ref;
        do {
            unsigned i = cRandomGlobal.RandomUint32Uniform(n - 1);
            unsigned* e = (unsigned*)(tbl + i * 0xc);
            elem[0] = e[0];
            elem[1] = e[1];
            elem[2] = e[2];

            ref = 0;
            void* mgr = GetManager_67dcd0();
            char ok = ((char(__thiscall*)(void*, void*, void*, void*, void*, void*, void*))
                       (*(void***)mgr)[0xc / 4])(mgr, elem, &ref, 0, 0, 0, 0);

            if (ref != 0) {
                void* r = ref;
                ref = 0;
                ((void(__thiscall*)(void*, void*))(*(void***)r)[4 / 4])(r, 0);
            }

            done = (ok != 0)
                && !((unsigned)m8c.type == elem[0]
                  && (unsigned)m8c.a1 == elem[1]
                  && (unsigned)m8c.a2 == elem[2]);
        } while (!done);

        ((void(__thiscall*)(void*, void*))(*(void***)this)[0x40 / 4])(this, elem);
        mTimer20 = 1;
    }
    freeQuery(templates.mpBegin);
    constraints.destroy();
}

// @ 0x00dfde90
void UI2::F_de90()
{
    char* base = (char*)this + 0xe0;
    for (unsigned int i = 0; i < 3; ++i) {
        if (base[i * 0x38] == 0) {
            *(int*)((char*)this + 0x34) = i;
            M_d8a0();
        }
    }
    *(unsigned char*)((char*)this + 0x7e) = 1;
    // The "was any slot empty" flag: retail keeps it in a single byte (mov byte
    // [esp+0x10],0 / ,1) and pushes that byte's stack dword to the window.
    bool local = false;
    if (*(int*)((char*)this + 0x30) != 0) {
        char* p = base;
        int n = *(int*)((char*)this + 0x30);
        do {
            if (*p == 0) local = true;
            p += 0x38;
            --n;
        } while (n != 0);
    }
    void* w = ((Lay*)((char*)this + 0x48))->FindWindowByID(0x7ccc115, 1);
    if (w != 0)
        ((void(__thiscall*)(void*, int, bool))(*(void***)w)[0x7c / 4])(w, 2, local);
}

// @ 0x00dfdf10
void __stdcall F_df10(unsigned int a, unsigned int b)
{
    for (; a < b; a += 0x534) {
        ((VecC*)(a + 0x84))->F(*(unsigned*)(a + 0x84), *(unsigned*)(a + 0x88));
        int p = *(int*)(a + 0x84);
        if (p != 0 && *(int*)(p - 4) != 0)
            operator_delete_((void*)p);
        ((F28*)(a + 0x3c))->M();
        ((F28*)a)->M();
    }
}

// @ 0x00dfdf70
void __stdcall F_df70(unsigned int a, unsigned int b)
{
    for (; a < b; a += 0x27e0) {
        ((F28*)(a + 0x2788))->M();
        unsigned end = *(unsigned*)(a + 0x74);
        for (unsigned p = *(unsigned*)(a + 0x70); p < end; p += 0x4e0)
            ((Obj4*)p)->F_bba0();
        int q = *(int*)(a + 0x70);
        if (q != 0 && *(int*)(q - 4) != 0)
            operator_delete_((void*)q);
    }
}

// @ 0x00dfdfe0
UI2::UI2(const UI2& s)
{
    char* d = (char*)this;
    char* src = (char*)&s;

    for (int i = 0; i < 10; ++i)
        ((unsigned*)d)[i] = ((const unsigned*)src)[i];

    *(void**)(d + 0x28) = d + 0x40;
    *(void**)(d + 0x2c) = d + 0x40;
    *(void**)(d + 0x30) = d + 0x40 + 0x1a0;
    *(unsigned*)(d + 0x3c) = 0;
    Vec34_assign_dfcee0(d + 0x28, 0, src + 0x28);

    for (int i = 0; i < 10; ++i)
        ((unsigned*)d)[0x78 + i] = ((const unsigned*)src)[0x78 + i];
    d[0x208] = src[0x208];
    d[0x209] = src[0x209];

    unsigned nbytes = *(unsigned*)(src + 0x210) - *(unsigned*)(src + 0x20c);
    PtrVecBase_4aa350(d + 0x20c, 0, nbytes >> 2, src + 0x218);
    unsigned* dst = *(unsigned**)(d + 0x20c);
    memcpy(dst, *(const void**)(src + 0x20c), nbytes);
    *(unsigned**)(d + 0x210) = (unsigned*)((char*)dst + (nbytes >> 2) * 4);

    *(unsigned*)(d + 0x220) = *(unsigned*)(src + 0x220);
    *(unsigned*)(d + 0x224) = *(unsigned*)(src + 0x224);
    *(unsigned*)(d + 0x228) = *(unsigned*)(src + 0x228);
    *(unsigned*)(d + 0x22c) = *(unsigned*)(src + 0x22c);
    *(unsigned*)(d + 0x230) = *(unsigned*)(src + 0x230);
}

// @ 0x00dfe170
void* UI2::F_e170(int* p)
{
    if ((*p < 0) && (-1 < *(int*)this)) {
        int v = *(int*)((char*)this + 0x210);
        if (v != 0 && *(int*)(v - 4) != 0)
            operator_delete_((void*)v);
        ((VecB*)((char*)this + 0x2c))->F_b850(*(unsigned*)((char*)this + 0x2c), *(unsigned*)((char*)this + 0x30));
        int w = *(int*)((char*)this + 0x2c);
        if (w != 0 && *(int*)(w - 4) != 0) {
            operator_delete_((void*)w);
            *(int*)this = *p;
            return this;
        }
    } else if (-1 < *p) {
        if (*(int*)this < 0) {
            if (this != (UI2*)0xfffffffc) {
                ((TFun2)FUN_e0e0)((char*)this + 4, p + 1);
                *(int*)this = *p;
                return this;
            }
        } else {
            ((TFun2)FUN_d3a0)((char*)this + 4, p + 1);
        }
    }
    *(int*)this = *p;
    return this;
}

// @ 0x00dfe220
void SP::cSPUIMissions::UpdateMissionFieldsSpace()
{
    FUN_00df97e0_GGUI();

    mIndex = 0;
    mCount = 0;
    mCur = 0;
    m7f = 0;

    char* item = (char*)mItem;
    FUN_00df9c80_GGUI(*(unsigned*)item);
    mTimer20 = *(unsigned*)(item + 0x20);
    m7c = 1;

    mName.Assign((const unsigned short*)0x13ec468, (const unsigned short*)0x13ec468);

    m8c.type = 0;
    m8c.a1 = 0;
    m8c.a2 = 0;
    m8c.a3 = 0;
    m8c.a4 = 0;
    m8c.a5 = 0;
    mA4 = 0;
    mA8 = 0;
    mAC = 0;
    *(unsigned*)&mB0[0] = 0;
    *(unsigned*)&mB0[4] = 0;
    *(unsigned*)&mB0[8] = 0;

    unsigned table[8] = { 0x7ca16b4, 0, 0x7bfce80, 1, 0x7ca3288, 0, 0x7ca46c1, 0 };

    char* lay = mLayout;
    for (int i = 0; i < 3; ++i) {
        Slot_s00df_d5b0& sl = mSlots[i];
        sl.x = 0;
        sl.y = 0;
        sl.z = 0;
        sl.state = 0;

        void* win = ((Lay*)lay)->FindWindowByID((int)g_147ebe0[i], 1);
        if (win != 0) {
            void* box = ((void*(__thiscall*)(void*, unsigned))(*(void***)win)[0xc / 4])
                          (win, 0x8ed27e7a);
            if (box != 0) {
                ((void(__thiscall*)(void*, int, int))(*(void***)box)[0x28 / 4])(box, 4, 0);
                void* panel = ((void*(__thiscall*)(void*))(*(void***)box)[0x10 / 4])(box);
                ((void(__thiscall*)(void*, int, int))(*(void***)panel)[0x7c / 4])(panel, 0x10, 1);
            }
        }
        win = ((Lay*)lay)->FindWindowByID((int)g_147ebec[i], 1);
        if (win != 0)
            ((void(__thiscall*)(void*, int, int))(*(void***)win)[0x7c / 4])(win, 2, 1);
    }

    for (int i = 0; i < 8; i += 2) {
        void* win = ((Lay*)lay)->FindWindowByID((int)table[i], 1);
        ((void(__thiscall*)(void*, int, int))(*(void***)win)[0x7c / 4])
            (win, 1, table[i + 1] != 0);
    }

    void* win = ((Lay*)lay)->FindWindowByID(0x7ccdc3b, 1);
    if (win != 0)
        ((void(__thiscall*)(void*, unsigned))(*(void***)win)[0x80 / 4])(win, 0x13ec468);

    win = ((Lay*)lay)->FindWindowByID(0x7e0bb68, 1);
    if (win != 0)
        ((void(__thiscall*)(void*, int, int))(*(void***)win)[0x7c / 4])(win, 1, 0);

    FUN_00df9b30_GGUI(0);
    m7e = 1;

    void* app = AppSystem_67dd00();
    char active = ((char(__thiscall*)(void*))(*(void***)app)[0x54 / 4])(app);
    if (active == 0 && *(unsigned*)((char*)g_16a1344_s00df_d5b0 + 0x1f8) == 0) {
        unsigned qmf[3];
        QueryMissionFields(qmf);
        if (qmf[0] != 0) {
            ((void(__thiscall*)(void*, void*))(*(void***)this)[0x40 / 4])(this, qmf);
            FUN_00df9ef0_GGUI();
        }
    }
}

// @ 0x00dfe460
char cSPUISpace::DoMessage(int arg1, GGUIMsg* msg)
{
    (void)arg1;
    if (msg->mType08 == 0x287259f6) {
        if (mMode20 != 0xb && !g_pEditorGlobals->mpActive1c->IsActive()) {
            switch (msg->mpObj->CommandId()) {
            case 0x54045ce:
                Fn9990();
                return 1;
            case 0x5384d05:
            case 0x5384d06:
            case 0x5384d07:
            case 0x5384d08:
                RecordEvent(0x8e82b51c);
                Fn9ef0();
                return 1;
            case 0x5933fe0:
            case 0x5933fe1:
            case 0x5933fe2:
            case 0x5933fe3:
                RecordEvent(0x8e82b51c);
                Fn9e60();
                return 1;
            case 0x5951103:
            case 0x5951104:
                RecordEvent(0xddd740f9);
                FnAe50();
                return 1;
            case 0x733b57f:
                SetModeEnabled(0);
                mMode20 = 9;
                return 1;
            case 0x733fe09: {
                Any3 t;
                t.a = 0;
                t.b = 0;
                t.c = 0;
                FnA460(&t, 0);
                mMode20 = 6;
                SetModeEnabled(0);
                return 1;
            }
            case 0x733fe08:
                RecordEvent(0x8e82b51c);
                FnE220();
                return 1;
            case 0x73bba58:
                mMode20 = 5;
                SetModeEnabled(0);
                Fn9a70();
                return 1;
            case 0x74d0932:
                Fn9a00();
                mMode20 = 7;
                SetModeEnabled(0);
                return 1;
            case 0x7c683f0:
                LaunchAssetBrowser(0);
                return 1;
            case 0x7bfb76e:
            case 0x7bfcff8:
                if (mMode20 == 0) {
                    SetModeEnabled(0);
                    RecordEvent(0xebadb118);
                    g_pInterfaceState->mpSub198->NotifySequence();
                    g_pInterfaceState->SetSlotMode(2, 0);
                    g_pInterfaceState->SetEntryFlag(1);
                } else {
                    RecordEvent(0x8e82b51c);
                    Fn9ad0();
                    mMode20 = 0;
                }
                return 1;
            case 0x7c683f1:
                LaunchAssetBrowser(1);
                return 1;
            case 0x7c683f2:
                LaunchAssetBrowser(2);
                return 1;
            case 0x7ca4119:
                FnA460(&mAny3A4, 0);
                return 1;
            case 0x7ccc126:
                RecordEvent(0x91be3241);
                FnD5b0();
                return 1;
            case 0x7ccc115:
                FnDe90();
                return 1;
            case 0x7ccc133:
                RecordEvent(0x91be3241);
                FnDc50();
                return 1;
            case 0x7ccc2a4:
                RecordEvent(0x91be3241);
                FnAf80();
                return 1;
            default:
                break;
            }
        }
    } else if (msg->mType08 == 0x9b1552d8) {
        FUN_00435ed0(0x1ac6d1af, AudioEventValue());
        uint32_t cmd = msg->mpObj->CommandId();
        if (cmd == 0x5400fa5) {
            cSPUIWindow* w = mLayout48.FindWindowByID(cmd, 1);
            if (w != 0) {
                cSPUIWindow* child = w->FindChild(0xcf428691);
                if (child != 0) {
                    mStr168.Append(child->GetText());
                    if (CheckX())
                        child->SetText(mStr168.mpData, 0);
                }
            }
            mFlag7e = 1;
            return 1;
        }
    } else if (msg->mType08 == 0x1b) {
        uint32_t cmd = msg->mpObj->CommandId();
        if (cmd == 0x73bba58 || cmd == 0x733fe08 || cmd == 0x74d0932) {
            if ((msg->mpObj->Flags() & 2) != 0)
                FUN_00435ed0(0xd607a5a7, AudioEventValue());
        }
    }
    return 1;
}

// @ 0x00dfe910
Elem27e8* __stdcall DestroyRange27e8(Elem27e8* first, Elem27e8* last)
{
    Elem27e8* result = first;
    while (first < last) {
        FUN_00f280f0((char*)first + 0x78 + 0x2718, 0);
        void** begin = *(void***)((char*)first + 0x78);
        void** end = *(void***)((char*)first + 0x7c);
        while (begin < end) {
            FUN_00dfbba0(begin, 0);
            begin = (void**)((char*)begin + 0x4e0);
        }
        void* p = *(void**)((char*)first + 0x78);
        result = (Elem27e8*)p;
        if (p != 0 && *((int*)p - 1) != 0) {
            EA_Free(p);
        }
        first = (Elem27e8*)((char*)first + 0x27e8);
    }
    return result;
}

// @ 0x00dfeaa0
void** UninitCopy238(void** dstp, int* first, int* last, int val)
{
    *dstp = (void*)val;
    while (first != last) {
        char* d = (char*)*dstp;
        if (d != 0) {
            *(int*)d = *first;
            if (*first >= 0) {
                d += 4;
                if (d != 0) {
                    FUN_00dfdfe0(first + 1);
                }
            }
        }
        *dstp = (char*)*dstp + 0x238;
        first = (int*)((char*)first + 0x238);
    }
    return dstp;
}

// @ 0x00dfeb00
V188* V188::Assign(V188* other_)
{
    void** self = (void**)this; int* other = (int*)other_;
    if (other == (int*)self) {
        return this;
    }
    int iVar1 = *other;
    uint32_t uVar2 = (uint32_t)((other[1] - iVar1) / 0x188);
    int iVar5 = (int)*self;
    if ((uint32_t)(((int*)self)[2] - iVar5) / 0x188 < uVar2) {
        iVar5 = (int)Alloc(uVar2, (void*)iVar1, (void*)other[1]);
        Destroy(*self, (void*)((int*)self)[1]);
        int p = (int)*self;
        if (p != 0 && *(int*)(p - 4) != 0) {
            EA_Free((void*)p);
        }
        ((int*)self)[1] = uVar2 * 0x188 + iVar5;
        *self = (void*)iVar5;
        ((int*)self)[2] = uVar2 * 0x188 + iVar5;
        return this;
    }
    uint32_t uVar3 = (uint32_t)(((int*)self)[1] - iVar5) / 0x188;
    if (uVar3 < uVar2) {
        FUN_00dfd250((void*)iVar1, (void*)(uVar3 * 0x188 + iVar1), (void*)iVar5);
        other = (int*)other[1];
        FUN_00dfd4e0(&other, (void*)((((int*)self)[1] - (int)*self) / 0x188 * 0x188 + *other),
                     other, (void*)((int*)self)[1], other);
        ((int*)self)[1] = uVar2 * 0x188 + (int)*self;
        return this;
    }
    void* uVar6 = FUN_00dfd250((void*)iVar1, (void*)other[1], (void*)iVar5);
    Destroy(uVar6, (void*)((int*)self)[1]);
    ((int*)self)[1] = uVar2 * 0x188 + (int)*self;
    return this;
}

// @ 0x00dfec50
V4e0* V4e0::Assign(V4e0* other_)
{
    void** self = (void**)this; int* other = (int*)other_;
    if (other == (int*)self) {
        return this;
    }
    int iVar1 = *other;
    uint32_t uVar2 = (uint32_t)((other[1] - iVar1) / 0x4e0);
    int ebp0 = (int)*self;
    if ((uint32_t)(((int*)self)[2] - ebp0) / 0x4e0 < uVar2) {
        int iVar5 = (int)Alloc(uVar2, (void*)iVar1, (void*)other[1]);
        Destroy(*self, (void*)((int*)self)[1]);
        int p = (int)*self;
        if (p != 0 && *(int*)(p - 4) != 0) {
            EA_Free((void*)p);
        }
        *self = (void*)iVar5;
        ((int*)self)[2] = uVar2 * 0x4e0 + iVar5;
        ((int*)self)[1] = uVar2 * 0x4e0 + iVar5;
        return this;
    }
    uint32_t uVar3 = (uint32_t)(((int*)self)[1] - ebp0) / 0x4e0;
    if (uVar3 < uVar2) {
        FUN_00dfd2c0((void*)iVar1, (void*)(uVar3 * 0x4e0 + iVar1), (void*)ebp0);
        other = (int*)other[1];
        FUN_00dfd4e0(&other, (void*)((((int*)self)[1] - (int)*self) / 0x4e0 * 0x4e0 + *other),
                     other, (void*)((int*)self)[1], other);
        ((int*)self)[1] = uVar2 * 0x4e0 + (int)*self;
        return this;
    }
    void* uVar6 = FUN_00dfd2c0((void*)iVar1, (void*)other[1], (void*)ebp0);
    Destroy(uVar6, (void*)((int*)self)[1]);
    ((int*)self)[1] = uVar2 * 0x4e0 + (int)*self;
    return this;
}

// @ 0x00dfed90
V4e0* V4e0::AssignWrap(V4e0* other)
{
    Assign(other);
    return this;
}

// @ 0x00dfedb0
void* ElemA::CopyAssign(void* o)
{
    void* s = this;
    ((CStr*)s)->Assign(o);
    if ((void*)((char*)o + 0x14) != (void*)((char*)s + 0x14)) {
        WStr_Assign((char*)s + 0x14, 0, *(void**)((char*)o + 0x14), *(void**)((char*)o + 0x18));
    }
    *(uint32_t*)((char*)s + 0x24) = *(uint32_t*)((char*)o + 0x24);
    *(uint32_t*)((char*)s + 0x28) = *(uint32_t*)((char*)o + 0x28);
    if ((void*)((char*)o + 0x2c) != (void*)((char*)s + 0x2c)) {
        WStr_Assign((char*)s + 0x2c, 0, *(void**)((char*)o + 0x2c), *(void**)((char*)o + 0x30));
    }
    ((CStr*)((char*)s + 0x3c))->Assign((char*)o + 0x3c);
    if ((void*)((char*)o + 0x50) != (void*)((char*)s + 0x50)) {
        WStr_Assign((char*)s + 0x50, 0, *(void**)((char*)o + 0x50), *(void**)((char*)o + 0x54));
    }
    *(uint32_t*)((char*)s + 0x60) = *(uint32_t*)((char*)o + 0x60);
    *(uint32_t*)((char*)s + 0x64) = *(uint32_t*)((char*)o + 0x64);
    if ((void*)((char*)o + 0x68) != (void*)((char*)s + 0x68)) {
        WStr_Assign((char*)s + 0x68, 0, *(void**)((char*)o + 0x68), *(void**)((char*)o + 0x6c));
    }
    *(uint32_t*)((char*)s + 0x78) = *(uint32_t*)((char*)o + 0x78);
    *(uint8_t*)((char*)s + 0x7c) = *(uint8_t*)((char*)o + 0x7c);
    *(uint32_t*)((char*)s + 0x80) = *(uint32_t*)((char*)o + 0x80);
    ((V188*)((char*)s + 0x84))->Assign((V188*)((char*)o + 0x84));
    return s;
}

// @ 0x00dfee80
void* ElemB::CopyCtor(void* o)
{
    void* s = this;
    for (int i = 0; i < 8; ++i) ((uint32_t*)s)[i] = ((uint32_t*)o)[i];
    *(uint8_t*)((char*)s + 0x20) = *(uint8_t*)((char*)o + 0x20);
    *(uint32_t*)((char*)s + 0x24) = *(uint32_t*)((char*)o + 0x24);
    for (int i = 0; i < 8; ++i) ((uint32_t*)((char*)s + 0x28))[i] = ((uint32_t*)((char*)o + 0x28))[i];
    *(uint32_t*)((char*)s + 0x48) = *(uint32_t*)((char*)o + 0x48);
    for (int i = 0; i < 8; ++i) ((uint32_t*)((char*)s + 0x50))[i] = ((uint32_t*)((char*)o + 0x50))[i];
    ((V4e0*)((char*)s + 0x70))->Assign((V4e0*)((char*)o + 0x70));
    ((CStr*)((char*)s + 0x2788))->Assign((char*)o + 0x2788);
    if ((void*)((char*)o + 0x2788 + 0x14) != (void*)((char*)s + 0x2788 + 0x14)) {
        WStr_Assign((char*)s + 0x2788 + 0x14, 0, *(void**)((char*)o + 0x2788 + 0x14), *(void**)((char*)o + 0x2788 + 0x18));
    }
    *(uint32_t*)((char*)s + 0x27ac) = *(uint32_t*)((char*)o + 0x27ac);
    *(uint32_t*)((char*)s + 0x27b0) = *(uint32_t*)((char*)o + 0x27b0);
    if ((void*)((char*)o + 0x2788 + 0x2c) != (void*)((char*)s + 0x2788 + 0x2c)) {
        WStr_Assign((char*)s + 0x2788 + 0x2c, 0, *(void**)((char*)o + 0x2788 + 0x2c), *(void**)((char*)o + 0x2788 + 0x30));
    }
    *(uint32_t*)((char*)s + 0x27c4) = *(uint32_t*)((char*)o + 0x27c4);
    *(uint32_t*)((char*)s + 0x27c8) = *(uint32_t*)((char*)o + 0x27c8);
    *(uint32_t*)((char*)s + 0x27cc) = *(uint32_t*)((char*)o + 0x27cc);
    *(uint32_t*)((char*)s + 0x27d0) = *(uint32_t*)((char*)o + 0x27d0);
    *(uint32_t*)((char*)s + 0x27d8) = *(uint32_t*)((char*)o + 0x27d8);
    *(uint32_t*)((char*)s + 0x27dc) = *(uint32_t*)((char*)o + 0x27dc);
    return s;
}

// @ 0x00dfef70
void cUISpaceRes::Destroy()
{
    OwnedFree(mpOwned2c80);
    mVec2c6c.DestroyRange(mVec2c6c.mpBegin, mVec2c6c.mpEnd);       // 0x00dfdf70
    OwnedFree(mVec2c6c.mpBegin);
    RawFree(mpRaw2c54);
    mVec2c10.DestroyRangeUnk(mVec2c10.mpBegin, mVec2c10.mpEnd);    // 0x00dfd300
    RawFree(mVec2c10.mpBegin);
    mVec2bf4.DestroyRange27e8(mVec2bf4.mpBegin, mVec2bf4.mpEnd);   // 0x00dfe910
    RawFree(mVec2bf4.mpBegin);
    mPod23c.DestroyRange534(mPod23c.mpBegin, mPod23c.mpEnd);       // 0x00dfdf10
    OwnedFree(mPod23c.mpBegin);
    OwnedFree(mpOwned178);
    mStrF4.Destroy();
    mStrB8.Destroy();
    mStr7c.Destroy();
    if (mpTracer48)
        ((void (__thiscall*)(void*))(*(void***)mpTracer48)[1])(mpTracer48);
    mVec30.DestroyRangeVariant(mVec30.mpBegin, mVec30.mpEnd);      // 0x00685a30
    RawFree(mVec30.mpBegin);
    mpVtbl18 = (void*)&g_13eb938;
    _ReadWriteBarrier();
    mpVtbl00 = (void*)g_13eb938;
}

// @ 0x00dff130
void* ElemB::Init(void* o)
{
    void* s = this;
    ((Buf3c*)s)->Copy(o);
    ((Buf3c*)((char*)s + 0x3c))->Copy((char*)o + 0x3c);
    *(uint32_t*)((char*)s + 0x78) = *(uint32_t*)((char*)o + 0x78);
    *(uint8_t*)((char*)s + 0x7c) = *(uint8_t*)((char*)o + 0x7c);
    *(uint32_t*)((char*)s + 0x80) = *(uint32_t*)((char*)o + 0x80);
    *(void**)((char*)s + 0x84) = (char*)s + 0x9c;
    *(void**)((char*)s + 0x88) = (char*)s + 0x9c;
    *(void**)((char*)s + 0x98) = 0;
    *(void**)((char*)s + 0x8c) = (char*)s + 0x534;
    ((V188*)((char*)s + 0x84))->Assign((V188*)((char*)o + 0x84));
    return s;
}

// @ 0x00dff1a0
void* ElemA::CopyCtor(void* o)
{
    void* s = this;
    for (int i = 0; i < 8; ++i) ((uint32_t*)s)[i] = ((uint32_t*)o)[i];
    *(uint8_t*)((char*)s + 0x20) = *(uint8_t*)((char*)o + 0x20);
    *(uint32_t*)((char*)s + 0x24) = *(uint32_t*)((char*)o + 0x24);
    for (int i = 0; i < 8; ++i) ((uint32_t*)((char*)s + 0x28))[i] = ((uint32_t*)((char*)o + 0x28))[i];
    *(uint32_t*)((char*)s + 0x48) = *(uint32_t*)((char*)o + 0x48);
    for (int i = 0; i < 8; ++i) ((uint32_t*)((char*)s + 0x50))[i] = ((uint32_t*)((char*)o + 0x50))[i];
    *(void**)((char*)s + 0x70) = (char*)s + 0x88;
    *(void**)((char*)s + 0x74) = (char*)s + 0x88;
    *(void**)((char*)s + 0x78) = (char*)s + 0x2788;
    *(void**)((char*)s + 0x84) = 0;
    ((V4e0*)((char*)s + 0x70))->Assign((V4e0*)((char*)o + 0x70));
    ((Buf3c*)((char*)s + 0x2788))->Copy((char*)o + 0x2788);
    *(uint32_t*)((char*)s + 0x27c4) = *(uint32_t*)((char*)o + 0x27c4);
    *(uint32_t*)((char*)s + 0x27c8) = *(uint32_t*)((char*)o + 0x27c8);
    *(uint32_t*)((char*)s + 0x27cc) = *(uint32_t*)((char*)o + 0x27cc);
    *(uint32_t*)((char*)s + 0x27d0) = *(uint32_t*)((char*)o + 0x27d0);
    *(uint32_t*)((char*)s + 0x27d8) = *(uint32_t*)((char*)o + 0x27d8);
    *(uint32_t*)((char*)s + 0x27dc) = *(uint32_t*)((char*)o + 0x27dc);
    return s;
}

// @ 0x00dff330
V238* V238::Assign(V238* other)
{
    if (other == this)
        return this;
    char* oEnd = (char*)other->mpEnd;
    char* oBeg = (char*)other->mpBegin;
    uint32_t nOther = (uint32_t)((oEnd - oBeg) / 0x238);
    char* sBeg = (char*)mpBegin;
    if (nOther > (uint32_t)(((char*)mpCapacity - sBeg) / 0x238)) {
        char* p = (char*)Alloc(nOther, oBeg, oEnd);
        DestroyRange(mpBegin, mpEnd);
        if (mpBegin)
            EA_Free(mpBegin);
        mpBegin = p;
        mpCapacity = p + nOther * 0x238;
    } else {
        uint32_t nHave = (uint32_t)(((char*)mpEnd - sBeg) / 0x238);
        if (nOther > nHave) {
            FUN_00dfe9a0(oBeg, oBeg + nHave * 0x238, sBeg);
            FUN_00dfeaa0((void**)&other,
                         (char*)other->mpBegin +
                             (((char*)mpEnd - (char*)mpBegin) / 0x238) * 0x238,
                         other->mpEnd, mpEnd, other);
        } else {
            void* e = FUN_00dfe9a0(oBeg, oEnd, sBeg);
            DestroyRange(e, mpEnd);
        }
    }
    mpEnd = (char*)mpBegin + nOther * 0x238;
    return this;
}

// @ 0x00dff4e0
void** UninitCopy27e8(void** dstp, int* first, int* last, int val)
{
    *dstp = (void*)val;
    while (first != last) {
        char* d = (char*)*dstp;
        if (d != 0) {
            *(int*)d = *first;
            ((ElemA*)(d + 8))->CopyCtor(first + 2);
        }
        *dstp = (char*)*dstp + 0x27e8;
        first = (int*)((char*)first + 0x27e8);
    }
    return dstp;
}

// @ 0x00dff650
V534* V534::Assign(V534* other)
{
    if (other == this)
        return this;
    char* oEnd = (char*)other->mpEnd;
    char* oBeg = (char*)other->mpBegin;
    uint32_t nOther = (uint32_t)((oEnd - oBeg) / 0x534);
    char* sBeg = (char*)mpBegin;
    if (nOther > (uint32_t)(((char*)mpCapacity - sBeg) / 0x534)) {
        char* p = (char*)Alloc(nOther, oBeg, oEnd);
        DestroyRange(mpBegin, mpEnd);
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            EA_Free(mpBegin);
        mpBegin = p;
        mpCapacity = p + nOther * 0x534;
    } else {
        uint32_t nHave = (uint32_t)(((char*)mpEnd - sBeg) / 0x534);
        if (nOther > nHave) {
            FUN_00dff270(oBeg, oBeg + nHave * 0x534, sBeg);
            FUN_00dff460((void**)&other,
                         (char*)other->mpBegin +
                             (((char*)mpEnd - (char*)mpBegin) / 0x534) * 0x534,
                         other->mpEnd, mpEnd, other);
        } else {
            void* e = FUN_00dff270(oBeg, oEnd, sBeg);
            DestroyRange(e, mpEnd);
        }
    }
    mpEnd = (char*)mpBegin + nOther * 0x534;
    return this;
}

// @ 0x00dff790
Vec27e0& Vec27e0::sub_dff790(const Vec27e0& x)
{
    if (&x != this) {
        unsigned n = (unsigned)(((char*)x.end - (char*)x.begin) / 0x27e0);
        if ((unsigned)(((char*)cap - (char*)begin) / 0x27e0) < n) {
            void* p = sub_dff590(n, x.begin, x.end);
            sub_dfdf70(begin, end);
            if (begin != 0 && *(int*)((char*)begin - 4) != 0)
                sub_f47380(begin);
            begin = p;
            end = (char*)p + n * 0x27e0;
            cap = (char*)p + n * 0x27e0;
            return *this;
        }
        unsigned cur = (unsigned)(((char*)end - (char*)begin) / 0x27e0);
        if (cur < n) {
            sub_dff2b0(x.begin, (char*)x.begin + cur * 0x27e0, begin);
            void* slot = x.end;
            sub_dff4a0(&slot, (char*)x.begin + cur * 0x27e0, x.end, end, x.end);
            end = (char*)begin + n * 0x27e0;
        } else {
            void* dstEnd = sub_dff2b0(x.begin, x.end, begin);
            sub_dfdf70(dstEnd, end);
            end = (char*)begin + n * 0x27e0;
        }
    }
    return *this;
}

// @ 0x00dff8e0
Vec27e8& Vec27e8::sub_dff8e0(const Vec27e8& x)
{
    if (&x != this) {
        unsigned n = (unsigned)(((char*)x.end - (char*)x.begin) / 0x27e8);
        if ((unsigned)(((char*)cap - (char*)begin) / 0x27e8) < n) {
            void* p = sub_dff5f0(n, x.begin, x.end);
            sub_dfe910(begin, end);
            if (begin != 0)
                sub_f47380(begin);
            begin = p;
            end = (char*)p + n * 0x27e8;
            cap = (char*)p + n * 0x27e8;
            return *this;
        }
        unsigned cur = (unsigned)(((char*)end - (char*)begin) / 0x27e8);
        if (cur < n) {
            sub_dff2f0(x.begin, (char*)x.begin + cur * 0x27e8, begin);
            void* slot = x.end;
            sub_dff4e0(&slot, (char*)x.begin + cur * 0x27e8, x.end, end, x.end);
            end = (char*)begin + n * 0x27e8;
        } else {
            void* dstEnd = sub_dff2f0(x.begin, x.end, begin);
            sub_dfe910(dstEnd, end);
            end = (char*)begin + n * 0x27e8;
        }
    }
    return *this;
}

// @ 0x00dffa30
PropBaseA22& PropBaseA22::sub_dffa30(const PropBaseA22& x)
{
    f08 = x.f08;
    f0c = x.f0c;
    f10 = x.f10;
    f14 = x.f14;
    p18 = x.p18;
    f50 = x.f50;
    f54 = x.f54;
    f58 = x.f58;
    f5c = x.f5c;
    f60 = x.f60;
    f64 = x.f64;
    f68 = x.f68;
    f6c = x.f6c;
    f70 = x.f70;
    f74 = x.f74;
    f78 = x.f78;
    g7c.cs = x.g7c.cs;
    g7c.w14 = x.g7c.w14;
    g7c.f24 = x.g7c.f24;
    g7c.f28 = x.g7c.f28;
    g7c.w2c = x.g7c.w2c;
    gb8.cs = x.gb8.cs;
    gb8.w14 = x.gb8.w14;
    gb8.f24 = x.gb8.f24;
    gb8.f28 = x.gb8.f28;
    gb8.w2c = x.gb8.w2c;
    gf4.cs = x.gf4.cs;
    gf4.w14 = x.gf4.w14;
    gf4.f24 = x.gf4.f24;
    gf4.f28 = x.gf4.f28;
    gf4.w2c = x.gf4.w2c;
    for (int i = 0; i < 8; i++) blk130[i] = x.blk130[i];
    f150 = x.f150; f154 = x.f154; f158 = x.f158; f15c = x.f15c;
    f160 = x.f160; f164 = x.f164; f168 = x.f168;
    f16c = x.f16c; f170 = x.f170;
    f174 = x.f174; f175 = x.f175;
    b178 = x.b178;
    f238 = x.f238;
    b23c = x.b23c;
    v2bf4 = x.v2bf4;
    f2c08 = x.f2c08;
    f2c0c = x.f2c0c;
    g2c10.s = x.g2c10.s;
    g2c10.f14 = x.g2c10.f14;
    g2c10.f18 = x.g2c10.f18;
    f2c2c = x.f2c2c;
    f2c2d = x.f2c2d;
    f2c30 = x.f2c30; f2c34 = x.f2c34; f2c38 = x.f2c38; f2c3c = x.f2c3c;
    f2c40 = x.f2c40; f2c44 = x.f2c44; f2c48 = x.f2c48;
    f2c4c = x.f2c4c;
    f2c50 = x.f2c50;
    v2c54 = x.v2c54;
    v2c6c = x.v2c6c;
    k2c80 = x.k2c80;
    f2c94 = x.f2c94; f2c98 = x.f2c98; f2c9c = x.f2c9c;
    f2ca0 = x.f2ca0; f2ca4 = x.f2ca4; f2ca8 = x.f2ca8;
    return *this;
}

// @ 0x00dffda0
void cEditorModeUI_s00df_f790::sub_dffda0()
{
    void* local = 0;
    void* rm = sub_67dcd0();
    if (local) { void* t = local; local = 0; releaseHandle(t); }
    char ok = ((char (__thiscall*)(void*, void*, void**, int, int, int, int))
               (*(void***)rm)[3])(rm, keyA, &local, 0, 0, 0, 0);
    if (ok) {
        PropBaseA22 tmp;
        tmp.sub_f2e7d0();
        tmp.sub_dffa30(*(const PropBaseA22*)local);
        tmp.sub_f2b3d0();
        ((Ctx39*)(*(int*)0x16a1344 + 0x3c))->sub_de9dc0(keyA);
        if (tmp.f175 == 0) {
            keyC[0] = 0; keyC[1] = 0; keyC[2] = 0;
            b7c = 1;
            if (wstr.b != wstr.e) { *(u16*)wstr.b = 0; wstr.e = wstr.b; }
            b7f = 1;
        } else {
            b7c = 0;
            b7f = 0;
            if (wstr.b != wstr.e) { *(u16*)wstr.b = 0; wstr.e = wstr.b; }
            keyC[0] = tmp.blk130[0];
            keyC[1] = tmp.blk130[1];
            keyC[2] = tmp.blk130[2];
            if (!sub_eed920(keyC, &wstr)) {
                void* prof = ((SpeciesMgr*)sub_401090())->sub_4df550(keyC);
                if (prof) ((Species*)prof)->sub_4da330(&wstr);
            }
        }
        sub_df98f0();
        int n = (int)(((char*)tmp.b178.end - (char*)tmp.b178.begin) / 0x38);
        b7d = (n != 0);
        count = n;
        if (n > 0) {
            u32* dst = (u32*)entries;
            u32* src = (u32*)tmp.b178.begin;
            for (int i = 0; i < n; i++)
                for (int w = 0; w < 14; w++)
                    dst[i * 14 + w] = src[i * 14 + w];
        }
        void* w1 = layout.sub_8105b0(0x7ca3288, 1);
        if (w1) {
            ((void (__thiscall*)(void*, int, int))(*(void***)w1)[0x7c / 4])(w1, 1, 1);
            int k4[4];
            k4[0] = keyA[0]; k4[1] = 0x2f7d0004; k4[2] = keyA[2]; k4[3] = 0;
            sub_de3f00(w1, k4, 0);
        }
        void* w2 = layout.sub_8105b0(0x7ccdc3b, 1);
        if (w2) {
            int k2[3];
            k2[0] = keyA[0]; k2[1] = 0x30bdee3; k2[2] = keyA[2];
            void* h = 0;
            void* rm2 = sub_67dcd0();
            ((char (__thiscall*)(void*, void*, void**, int, int, int, int))
             (*(void***)rm2)[3])(rm2, k2, &h, 0, 0, 0, 0);
            if (h) {
                void* item = ((void* (__thiscall*)(void*, int))(*(void***)h)[3])(h, 0x30bdee3);
                if (item) {
                    ((void (__thiscall*)(void*))(*(void***)item)[0])(item);
                    void* nm = ((Item_s00df_f790*)item)->sub_414e10();
                    ((void (__thiscall*)(void*, void*))(*(void***)w2)[0x80 / 4])(w2, nm);
                    ((void (__thiscall*)(void*))(*(void***)item)[1])(item);
                }
                releaseHandle(h);
            }
        }
        void* w3 = layout.sub_8105b0(0x7e0bb68, 1);
        if (w3) {
            ((void (__thiscall*)(void*, int, int))(*(void***)w3)[0x7c / 4])(w3, 1, b7f);
        }
        tmp.sub_dfef70();
    }
    if (local) { void* t = local; local = 0; releaseHandle(t); }
}

// @ 0x00e000a0
void cEditorModeUI_s00df_f790::sub_e000a0(int* key)
{
    void* local = 0;
    void* rm = sub_67dcd0();
    if (local) { void* t = local; local = 0; releaseHandle(t); }
    char ok = ((char (__thiscall*)(void*, void*, void**, int, int, int, int))
               (*(void***)rm)[3])(rm, key, &local, 0, 0, 0, 0);
    if (ok) {
        keyB[0] = key[0];
        keyB[1] = key[1];
        keyB[2] = key[2];
        void* ec = *(void**)(*(int*)0x16c7aa4 + 0x1c);
        if (!((Eco*)ec)->sub_ec5a60(keyB, 0, 0)) {
            keyB[0] = 0; keyB[1] = 0; keyB[2] = 0;
        } else if (((Eco*)ec)->sub_ec4320()) {
            sub_dfab20(0);
            prevMode = mode;
            mode = 8;
        } else {
            keyA[0] = keyB[0]; keyA[1] = keyB[1]; keyA[2] = keyB[2];
            keyB[0] = 0; keyB[1] = 0; keyB[2] = 0;
            sub_dffda0();
        }
    }
    if (local) { void* t = local; local = 0; releaseHandle(t); }
}

// @ 0x00e001a0
void cEditorModeUI_s00df_f790::sub_e001a0(int* ev)
{
    if (ev[0] == 0) {
        if (mode == 5 || mode == 7) {
            mode = 0;
            sub_dfab20(1);
        }
    } else if (ev[1] == 0x366a930d) {
        ((Ctx39*)(*(int*)0x16a1344 + 0x3c))->sub_de9dc0(ev);
        unsigned i = 0;
        do {
            entries[i].f00 = 0;
            entries[i].f04 = 0;
            entries[i].f08 = 0;
            entries[i].f20 = 0;
            sub_df9dc0(i, 0);
            i++;
        } while (i < 3);
        int m = mode;
        if (m == 7) sub_dfaca0(ev);
        else if (m == 5) sub_dfad50(ev);
        else if (m == 1) sub_e000a0(ev);
    } else if (ev[1] == 0x2b978c46) {
        sub_df9d20(ev);
    }
    if (mode > 0 && (mode <= 2 || mode == 4)) {
        void* ec = *(void**)(*(int*)0x16c7aa4 + 0x1c);
        if (!((Eco*)ec)->sub_ec4320()) {
            sub_dfab20(1);
            sub_df9c80(p0c[f2c * 9]);
        }
    }
    b7e = 1;
}

// @ 0x00e002b0
bool cEditorModeUI_s00df_f790::sub_e002b0(int msg, int* params)
{
    if (msg == 0x04249453) {
        u8 buf[12];
        sub_dfb0d0(buf);
        return true;
    }
    if (msg == 0x07be7df5) {
        int a = params[2];
        if (a == 4) {
            ((GObj2*)*(int*)0x16a1344)->sub_de86d0(2, 0);
            return true;
        }
        if (a == 3) {
            void* r = (void*)sub_dd9190();
            ((ClsA*)r)->sub_dda0d0(0);
            if (p84) {
                ((void (__thiscall*)(void*, int))(*(void***)p84)[3])(p84, 1);
                if (p84) {
                    void* t = p84;
                    p84 = 0;
                    ((void (__thiscall*)(void*))(*(void***)t)[1])(t);
                }
            }
            return true;
        }
        if (a == 0) {
            void* r = (void*)sub_dd9190();
            ((ClsA*)r)->sub_dda0d0(2);
            sub_dfa710(1);
            return true;
        }
        if (a == 2) {
            mode = 0;
            ((GObj2*)*(int*)0x16a1344)->sub_de5470(0);
            return true;
        }
        if (a == 5) {
            void* r = (void*)sub_dd9190();
            ((ClsB*)r)->sub_ddb760();
            return true;
        }
        if (a == 1) {
            sub_dfa370();
            sub_dfab20(1);
            return true;
        }
        return true;
    }
    if (msg == 0xcc0bf723) {
        if (mode == 8 && params != 0) {
            int x = params[0];
            if (x == 1 || x == 3) {
                int pm = prevMode;
                if (pm == 1) {
                    mode = 1;
                    b7e = 1;
                    keyB[0] = 0; keyB[1] = 0; keyB[2] = 0;
                } else if (pm == 9) {
                    keyA[0] = 0; keyA[1] = 0; keyA[2] = 0;
                    mode = 0;
                    keyB[0] = 0; keyB[1] = 0; keyB[2] = 0;
                }
                sub_dfab20(1);
                b7e = 1;
                return true;
            }
            if (x == 2) {
                keyA[0] = keyB[0]; keyA[1] = keyB[1]; keyA[2] = keyB[2];
                keyB[0] = 0; keyB[1] = 0; keyB[2] = 0;
                mode = prevMode;
                if (mode == 1) {
                    sub_dffda0();
                    b7e = 1;
                    sub_dfab20(1);
                    b7e = 1;
                    return true;
                }
                if (mode == 9) {
                    X19* e = (X19*)sub_ef19f0();
                    e->f00 = keyA[0]; e->f04 = keyA[1]; e->f08 = keyA[2];
                    e->f18 = 0; e->f1c = 0; e->f20 = 0;
                    ((Timeline*)sub_b3d410())->sub_e3e350(1, (int*)0x1654c10, 1);
                    f28 = 0xa;
                    return true;
                }
            }
        }
        return true;
    }
    return false;
}

// @ 0x00e00560
void __stdcall e00560(int dummy)
{
    (void)dummy;
    void* ab = SP_AssetBrowser();
    GObj* g = *(GObj**)&g_16a1344;
    if (g->field108 == 7 &&
        *(char*)((char*)ab + 0x1c) == 0 &&
        g->b270 == 0) {
        int* mm = *(int**)&DAT_016c7AA4;
        EC* ec = *(EC**)((char*)mm + 0x1c);
        if (!ec->sub_ec4320()) {
            (*(GObj**)&g_16a1344)->sub_de52d0();
        }
    }
}

// @ 0x00e005b0
struct Scope_e005b0 {
    char d0[0xc];
    int* mp0c;
    char d10[0x14];
    char mb24;
    char d25[0x23];
    void Init();     // 0x00644b10
    void Done();     // 0x00644b60
};
void __cdecl e005b0()
{
    Scope_e005b0 scope;
    scope.Init();
    if ((int)SP_GetCurrentGameMode() == 0x2ccd1d2) {
        scope.mb24 = 0;
        int* q = (int*)operator_new(0x14, k_szSporepedia, 0, 0, 0, 0);
        if (q) {
            int* g = *(int**)&g_16a1344;
            *(volatile int*)(q + 1) = (int)&vtbl_13ec458;
            q[2] = 0;
            q[0] = (int)&vtbl_147dc04;
            q[1] = (int)&vtbl_FUN_0149bad8;
            q[3] = (int)g;
            *(u8*)(q + 4) = 0;
            scope.mp0c = q;
        } else scope.mp0c = 0;
        sub_e02040(&scope);
    }
    scope.Done();
}

// @ 0x00e00630
VBase::VBase()
{
    vftable = (void**)g_147dba8;
    b4 = 0;
}

// @ 0x00e00670
void KeyObj::Dispatch(int param2, int param3)
{
    KeyObj* self = this;
    if (param3 == 0) {
        if (param2 == 0x48) goto joined;
    } else {
        if (param3 != 1) goto after;
    }
joined:
    if (param2 != 0xbf) goto after;
    {
        void* sg = SP_SporeGuide();
        int* ms;
        int msg;
        if (*(char*)((char*)sg + 0x1c) == 0) { ms = (int*)SP_MessageServer(); msg = 0x5120263; }
        else                                  { ms = (int*)SP_MessageServer(); msg = 0x5b9ba6c; }
        ((void(__thiscall*)(void*, int, int, int))(*(void***)ms)[0x14 / 4])(ms, msg, 0, 0);
    }
after:
    if (param2 != 0x42 || param3 != 0) return;
    if (*(char*)(*(int**)0x16a1344 + 0xef) != 0) return;
    {
        int* mv = (int*)SP_MovieSystem();
        char c = ((char(__thiscall*)(void*))(*(void***)mv)[0x14 / 4])(mv);
        if (c) return;
    }
    if (*(int*)(*(char**)0x16a1344 + 0x1ec) == 1) return;
    {
        void* ab = SP_AssetBrowser();
        if (*(char*)((char*)ab + 0x1c) != 0) {
            int* ms = (int*)SP_MessageServer();
            ((void(__thiscall*)(void*, int, int, int))(*(void***)ms)[0x14 / 4])(ms, 0x574f0a6, 0, 0);
            return;
        }
        if (self->key44()) {
            int* ms = (int*)SP_MessageServer();
            ((void(__thiscall*)(void*, int, int, int))(*(void***)ms)[0x14 / 4])(ms, 0x5120264, 0, 0);
        }
    }
}

// @ 0x00e00760
void CtxObj::ShowContextSporepedia(void* info)
{
    ((uint8_t*)this)[4] = 0;
    if (info == 0) return;
    char bMatch = (*(uint32_t*)((char*)info + 0xc) == 0x13c5a95eu) ? 1 : 0;
    void* obj = 0;
    void* p = *(void**)((char*)info + 0x10);
    if (p != 0) {
        obj = ((VFnPU)VSLOT_s00e0_0760(p, 0xc))(p, 0xf5e905cdu);
        if (obj != 0) {
            ((VFnV)VSLOT_s00e0_0760(obj, 0))(obj);
        }
    }
    if (!bMatch && ((uint8_t*)info)[0x44] != 0) goto done1;
    if (((uint8_t*)g_16a1344_s00e0_0760)[0x24d] != 0) goto done1;
    {
        LaunchCtx launch;
        uint8_t flag = 0;
        if (obj != 0) flag = ((uint8_t*)obj)[0x10];
        launch.Ctor();
        launch.f18 = *(uint32_t*)((char*)info + 0x18);
        launch.f1c = *(uint32_t*)((char*)info + 0x1c);
        launch.f20 = *(uint32_t*)((char*)info + 0x20);
        if (((uint8_t*)info)[0x44] != 0) {
            launch.f24 = 0;
            void* mem = EA_Allocate(0x14, (const char*)0x13fa29c, 0, 0, 0, 0);
            launch.mpObj = mem ? ((AllocObj*)mem)->FUN_00de0a90(g_16a1344_s00e0_0760, 0) : 0;
        } else {
            launch.f13 = (uint8_t)(bMatch == 0);
            launch.f24 = 1;
            void* mem = EA_Allocate(0x14, (const char*)0x13fa29c, 0, 0, 0, 0);
            launch.mpObj = mem ? ((AllocObj*)mem)->FUN_00de0a90(g_16a1344_s00e0_0760, flag) : 0;
        }
        FUN_00e02040(&launch);
        launch.Dtor();
    }
done1:
    if (obj != 0) {
        ((VFnV)VSLOT_s00e0_0760(obj, 4))(obj);
    }
}

// @ 0x00e008e0
void* MgrObj::Ctor()
{
    void* self = this;
    *(uint8_t*)((char*)self + 4) = 0;
    *(void**)self = (void*)0x147f000;
    *(void**)((char*)self + 8) = 0;
    *(void**)((char*)self + 0xc) = 0;
    *(void**)((char*)self + 0x10) = 0;
    ((StopwatchObj*)((char*)self + 0x20))->FUN_0093a560(0, 0);
    ((StopwatchObj*)((char*)self + 0x38))->FUN_0093a560(0, 0);
    *(void**)((char*)self + 0x54) = 0;
    *(void**)((char*)self + 0x58) = 0;
    *(void**)((char*)self + 0x5c) = 0;
    ((LimitStopwatchObj*)((char*)self + 0x70))->FUN_0093a560(0, 0);
    ((LimitStopwatchObj*)((char*)self + 0x70))->FUN_0093a480(0, 0);
    *(void**)((char*)self + 0x90) = 0;
    *(void**)((char*)self + 0x94) = 0;
    *(void**)((char*)self + 0x98) = 0;
    *(uint8_t*)((char*)self + 0x50) = 0;
    *(int*)((char*)self + 0x68) = -1;
    g_016a15fc = self;
    return self;
}

// @ 0x00e00970
void MgrObj::Dtor()
{
    void* self = this;
    ((RefVecObj*)((char*)self + 0x90))->FUN_004b5440();
    void* p = *(void**)((char*)self + 0x54);
    if (p != 0 && *((int*)p - 1) != 0) {
        EA_Free(p);
    }
    ((RefVecObj*)((char*)self + 8))->FUN_00de5ee0(*(void**)((char*)self + 8),
                                                  *(void**)((char*)self + 0xc));
    p = *(void**)((char*)self + 8);
    if (p != 0 && *((int*)p - 1) != 0) {
        EA_Free(p);
    }
    *(void**)self = (void*)0x147dba8;
}

// @ 0x0136bfb0
void init_16a0dc4()
{
    kImpostorOffset.mHash = FNVHash("ImpostorOffset", 0x811c9dc5, 1);
    kImpostorOffset.mpNext = sGGEProperties;
    sGGEProperties = &kImpostorOffset;
    kImpostorOffset.mpKey = &g_propKey147d3b8;
    kImpostorOffset.mValue0c = 0.0F;
    kImpostorOffset.mValue10 = 0.0F;
    kImpostorOffset.mValue14 = 0.0F;
    atexit(&FUN_013c6000);
}
