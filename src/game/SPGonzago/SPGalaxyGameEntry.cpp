// src/game/SPGonzago/SPGalaxyGameEntry.cpp -- migrated from slice(s) s01364b20, s00dff790, s00df9650, s00df7ce0, s00df6700, s00df5670, s00df2d80, s00df1e70, s00df0280, s00def400, s00dee450, s00ded5a0, s00dec7c0, s00deb840, s00dea870, s00de9a00, s00de5040, s00de3300, s00de0910, s00ddf990 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPGalaxyGameEntry.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

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

// ---- items of slice s00ddf990 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(LARGE_INTEGER* lpCount);
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
extern "C" void* __cdecl MessageServer();              // 0x0067dcc0
extern "C" void* __cdecl MovieSystem();                // 0x0067cb10
extern "C" void* __cdecl EA_Audio_GetSystemAT();       // 0x00a206f0
extern "C" void* __cdecl SP_App();                     // 0x0067dd10
extern "C" void* __cdecl SP_AppSystem();               // 0x0067dd00
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
struct cGalaxyHandle {
    virtual void h0();              // vtbl+0x00
    virtual void hRelease();        // vtbl+0x04
    virtual void hStart(int a);     // vtbl+0x08
    virtual void hStop(int a);      // vtbl+0x0c
};
struct cGalaxyManager {
    virtual void m0();                                // vtbl+0x00
    virtual void m1();                                // vtbl+0x04
    virtual bool mAdd(unsigned int id, int a, void** out); // vtbl+0x08
    virtual void m3();                                // vtbl+0x0c
};
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

    MapItr  find(const unsigned int& key);   // 0x00e5c780
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
struct RbTree57 {
    void*   root;       // +0x00 (this+0x04)
    char    pad[0x0c];
    int     count;      // +0x10 (this+0x14)
};
void* __cdecl EAllocNew(int size, const char* file, int flags, int align, void* alloc, int line); // 0x00f473a0
void  __cdecl RBTreeInsert57(void* node, void* parent, void* root, int side);                    // 0x009216a0
struct cGalaxyGameEntryImpl_s00de_5040 {
    char    mPad00[0x04];
    RbTree57 mTree4;            // +0x04
    char    mPad18[0x38 - 0x18];
    RbFind56 mRb38;             // +0x38
    char    mPad44[0x10c - 0x44];
    int     mCurrentDword;      // +0x10c
    char*   mBegin;             // +0x110
    char*   mEnd;               // +0x114
    char    mPad118[0x15c - 0x118];
    void*   mpManager;          // +0x15c
    char    mPad160[0x174 - 0x160];
    void*   mpHandleA;          // +0x174
    char    mPad178[0x1b0 - 0x178];
    void*   mpHandleB;          // +0x1b0
    char    mPad1b4[0x1f5 - 0x1b4];
    char    mFlag1f5;           // +0x1f5
    char    mPad1f6[0x254 - 0x1f6];
    RBTreeThing mRbTree;        // +0x254

    void  UpdateLoginButton(void);      // 0x00de5040
    void  FUN_00de5260(void);           // 0x00de5260
    void  FUN_00de52d0(void);           // 0x00de52d0
    void  FUN_00de5300(void);           // 0x00de5300
    void  FUN_00de5330(char p);         // 0x00de5330
    void  FUN_00de53d0(char p);         // 0x00de53d0
    void  ShowGalaxy(void);             // 0x00de5470
    OutKey3* FUN_00de56f0(OutKey3& pOut, KeyNode* key); // 0x00de56f0
    void  FUN_00de57b0(RbNode57** pOut, RbNode57* parent, Key2* key, char flag); // 0x00de57b0
    void  FUN_00de5950(void);           // 0x00de5950
    bool  FUN_00de5cb0(unsigned int a); // 0x00de5cb0
    void  FUN_00de5d00(void);           // 0x00de5d00
    void  FUN_00de5df0(void);           // 0x00de5df0
};
// ---- items of slice s00de5040 end

// ---- items of slice s00de9a00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void*    g_pAppPreferences;      // 0x015fd91c the app's preference list
extern void*    g_pGameGlobals;         // 0x016c7aa4
void*    __cdecl AuthManager();                                     // 0x00607a60
void*    __cdecl FUN_0067dd20();                                    // 0x0067dd20
uint32_t __cdecl GetRecorderState();                                // 0x00435e90
void     __cdecl FUN_00de3e40(uint32_t nId);                        // 0x00de3e40
void     __cdecl FUN_00dde570(void* pObject);                       // 0x00dde570
bool     __cdecl IsWorldLayoutFlagSet(uint32_t nFlag);              // 0x00685520
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
class cGameGlobalsRoot {
public:
    uint32_t   mPad00[7];                       // +0x00
    cUIObject* mp1c;                            // +0x1c
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
// ---- items of slice s00de9a00 end

// ---- items of slice s00dea870 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
void* __cdecl FUN_0067cb10();                          // 0x0067cb10 -> cMovieSystem*
void* __cdecl FUN_0067de30();                          // 0x0067de30 -> PropertyManager*
void* __cdecl FUN_0041ea70(void* pProp);               // 0x0041ea70 GetPropertyAsFloat
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
// ---- items of slice s00dea870 end

// ---- items of slice s00deb840 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t gDeferredWindowMask[];          // 0x016a1848
void operator delete[](void* p);                            // 0x00f47380
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
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
void*  __cdecl GetSetting3();                      // 0x00401030
IMessageServer* __cdecl MessageServer_s00de_b840();           // 0x0067dcc0
struct AssetBrowser {
    uint8_t pad00[0x1c];
    bool mb1c;                  // +0x1c
    bool CloneModelAsset(ResourceKey key, ResourceKey* pOut, uint32_t id, bool flag); // 0x00646370
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
extern uint32_t gWindowIdTable[11];          // 0x0147e4f0
struct IWindow_s00de_d5a0;
struct cString {
    uint32_t mTable;
    uint32_t mKey;
    uint32_t mText;
    cString();                                                       // 0x006b5060
    cString(uint32_t nTable, uint32_t nKey, const wchar_t* pText);   // 0x006b5770
    ~cString();                                                      // 0x006b5240
    bool Load(uint32_t nTable, uint32_t nKey, const wchar_t* pText); // 0x006b54b0
    const wchar_t* GetText() const;                                  // 0x006b55c0
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
void* __fastcall FUN_0080f730(void* pBox);                           // 0x0080f730
bool  __cdecl IsWorldLayoutFlagSet(int32_t nFlag);                   // 0x00685520
IWindow_s00de_d5a0* __cdecl GetSystemAT();                                      // 0x00a206f0
struct DSub {
    int32_t GetField10(int32_t nArg);                                // 0x00830cf0
};
void* __cdecl GlobalBoundingBox();                                   // 0x0067cad0 (no-arg form)
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
struct MenuTextIds {
    uint32_t mId0;
    uint32_t mId1;
    uint32_t mId2;
    uint32_t mId3;
};
struct cGalaxyGameEntryMode {
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

// ---- items of slice s00dee450 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int  gvtbl_notify;      // 0x0147e618
extern int  gvtbl_base;        // 0x0147dba8
extern int  gDAT_16a1570;      // 0x016a1570
typedef unsigned char  byte;
typedef unsigned short wchar16;
void  operator delete[](void* p) throw();                                   // 0x00f47380
extern byte gDAT_16a0f08;      // 0x016a0f08
struct PanelIDs; extern PanelIDs* gkGUI_PanelIDs;   // 0x016a1344  (pointer global)
void      FUN_00ded920(unsigned a, unsigned b);              // 0x00ded920
char __stdcall FUN_00de5cb0(unsigned a);                     // 0x00de5cb0
uint32_t  FUN_00dec990(void* p);                             // 0x00dec990
uint32_t  FUN_004bafc0(void* a, void** b);                   // 0x004bafc0
struct RBNode_s00de_e450;
RBNode_s00de_e450*   RBTreeIncrement(RBNode_s00de_e450* n);                        // 0x00921580
char      CreateImageFromResource2(void* a, void** b, char c, int d, int e); // 0x00806230
void      RemoveHandler(void* a, unsigned b, unsigned c, unsigned d, unsigned e); // 0x00571db0
void*     RbtreeFind(void* outIter, const void* key, void* tree);  // 0x00e39fb0
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
struct PanelIDs {                     // kGUI_PanelIDs target (pointer at 0x016a1344)
    char     pad_00[0x19c];
    void*    mpHandler;               // +0x19c
    char     pad_1a0[0x1f5 - 0x1a0];
    byte     mFlag;                   // +0x1f5

    void FUN_00de5d00(void* a, void* b, void* c, void* d, void* e, void* f, void* g);
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
};
struct UIDrawable {                    // a drawable window returned by a window vtable slot
    void** vtbl;                       // +0x00
    void   SetImageIcon(int a, void* b);   // 0x00831760
};
typedef void   (__thiscall *VF0)(void*);
typedef void   (__thiscall *VF1)(void*, int);
typedef void*  (__thiscall *VFP)(void*);
typedef void*  (__thiscall *VFP1)(void*, int);
typedef int    (__thiscall *VFI)(void*);
typedef void   (__thiscall *VF2)(void*, int, int);
typedef char   (__thiscall *VFC2F)(void*, float, float);
typedef void   (__thiscall *VFC8)(void*, float, float, float*);
typedef void   (__thiscall *VFIP)(void*, int, void*);
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
    void      FUN_00deef20(unsigned a, unsigned b, void* map);
    uint32_t  FUN_00deefb0(uint32_t key);
    void      FUN_00dee9a0(float a, float b);
    void      FUN_00dee770(uint32_t id, void* refObj);
    void      FUN_00dee800(uint32_t id);
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
namespace SP {
class cGalaxyGameEntryUIStateMachine_s00de_f400 {
public:
    void FUN_00def400();
    void FUN_00def690();
    void FUN_00def750(uint32_t id, uint32_t value);
    void FUN_00def7c0();
    void UpdateNavigationControls();  // 0x00def8c0 (SP::cGalaxyGameEntryUIStateMachine::UpdateNavigationControls)
    void FUN_00defc00();
    void MakeRandomName();  // 0x00defc80 (SP::cGalaxyGameEntryUIStateMachine::MakeRandomName)
    void SetStateSummaryText();  // 0x00defd10 (SP::cGalaxyGameEntryUIStateMachine::SetStateSummaryText)
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
    void FUN_00df0980();

    uint8_t              pad000[8];                          // +0x00 .. +0x07
    cGalaxyStateMachine* mpStateMachine;                     // +0x08
};
}
// ---- items of slice s00df0280 end

// ---- items of slice s00df1e70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float g_fMillisecondsPerSecond;                    // 0x013ec5b4
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
struct IWindow_s00df_2d80 {                                   // a cSPUIWindow / cSPUILayout window
    PV2 PV
    PV4 PV2 PV                                     // +0x0c..+0x24  (unused slots)
    virtual char     Slot28();                     // +0x28  -> predicate (low byte)
    virtual unsigned Slot2C();                     // +0x2c  -> state value
    PV8 PV8 PV2 PV                                 // +0x30..+0x78  (unused slots)
    virtual void     Slot7C(int a, int b);         // +0x7c  SetVisible/flag
};
struct SPUILayout {
    char pad[0x18];
    IWindow_s00df_2d80* FindWindowByID(unsigned id, int flag); // 0x008105b0  __thiscall
};
struct GGE {                                        // kGUI_PanelIDs
    char pad00[0x103];
    char m103;                                      // +0x103
    void Fn53d0(int);                               // 0x00de53d0
};
extern GGE* kGUI_PanelIDs_s00df_2d80;                          // 0x016a1344
void* __cdecl operator_new(unsigned size, const char* name, int, int, int, int); // 0x00f473a0
struct Key_s00df_2d80 { int a; int b; int c; };
struct GameEntry_s00df_2d80 {                                  // object at StateMachine+0x628
    char pad00[0x4c];
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
    char pad00[0x28];
    SPUILayout mLayout;                             // +0x28
    char pad40[0x5e8];                              // +0x40..+0x627
    GameEntry_s00df_2d80* mEntry;                              // +0x628

    void PickRandomVehicle();                       // 0x00df2d80
    void OnAssetBrowserSelection(Key_s00df_2d80* p);           // 0x00df21d0  (ret 4)
    void SelectNextState();                         // 0x00df2550
    void PickRandomCreature();                      // 0x00df2bb0
    void PickRandomAssets(char flag);               // 0x00df3ab0  (ret 4)
    void PickRandomByMode(unsigned id, int tag, Key_s00df_2d80* key); // 0x00df2a60  (ret 0xc)
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
typedef unsigned int uint;
struct Vec4 { float x, y, z, w; };
struct Obj;
struct cSPUILayout_s00df_5670;
struct cSPUILayout_s00df_5670 {
    void* FindWindowByID(uint id, int b);              // 0x008105b0 (ret 8) -> IWinNode*
    bool  Init(const void* key, bool b, uint id);      // 0x008120d0 (ret 0xc)
    void  Shutdown(uint b);                            // 0x00811ad0 (ret 4)
    void  dtor();                                      // 0x00811fe0
    void  ctor();                                      // 0x00810000
};
struct IWinNode {
virtual void  v00();
virtual void  v04();
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
virtual void  v58();
    virtual void  v5c(void* p);
    virtual void  v60(int a, int b);
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
void* __cdecl SPUIHelpers_GetMainWindowArea_s00df_5670(Vec4* out);                 // 0x00805ea0 (ret 4)
void  __cdecl FUN_00de3c70(void* p, float* a, float* b);                // 0x00de3c70 (ret 0xc)
bool  __cdecl FUN_005f2350(const float* v);                             // 0x005f2350
Obj*  __cdecl FUN_00dd9190();                                           // 0x00dd9190
void  __fastcall FUN_00ddb760(Obj* p);                                  // 0x00ddb760 (this in ecx)
void  __fastcall FUN_00de9ec0(Obj* p);                                  // 0x00de9ec0 (this in ecx)
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
// ---- items of slice s00df5670 end

// ---- items of slice s00df6700 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_p16a1344;              // 0x016a1344  GUI panel-id / layout manager
extern "C" void    __fastcall FUN_00409930(void* self);
extern "C" void    __fastcall FUN_005aa530(void* self);
extern "C" void*   __cdecl    FUN_00dd9190_0();
extern "C" void*   __stdcall  FUN_00dd9190_1(void* a);
extern "C" void*   __stdcall  FUN_00dd9190_2(void* a, void* b);
extern "C" void    __fastcall FUN_00ddab00(void* self);
extern "C" void    __fastcall FUN_00dda090(void* self);
#define PVN(n) virtual void pv##n();
struct MsgArg {                       // message payload passed to FUN_00df68c0
    uint32_t m00;                     // +0x00
    uint32_t m04;                     // +0x04
    int32_t  m08;                     // +0x08
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
struct Transform34 { char m[0x38]; };
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
// ---- items of slice s00df6700 end

// ---- items of slice s00df9650 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
struct GlobalUI {
    void SetVisibility(int v);                     // 0x00e01350  __thiscall
};
struct Map3C { void Fn9dc0(void* key); };          // 0x00de9dc0 (ecx = map)
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
struct Stopwatch_s00df_9650 {  // 0x0093a1a0
    int mUnits;
    void SetUnits(int u);  // 0x0093a1a0 (Stopwatch::SetUnits)
};
struct AGSwarm   { void FnB760(); void SpawnOne(); void FnBad0(void* arg); };
void* __cdecl FUN_00dd9190_s00df_9650();                     // 0x00dd9190 -> object*
void* __cdecl SP_MovieSystem();                    // 0x0067cb10
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
// ---- items of slice s00df9650 end

// ---- items of slice s00dff790 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl SP_AssetBrowser();
extern "C" void* __cdecl SP_GetCurrentGameMode();
extern "C" void  __cdecl sub_644b10(void*);
extern "C" void  __cdecl sub_644b60(void*);
extern "C" void  __cdecl sub_e02040(void*);
struct EC { char sub_ec4320(); };
struct GObj { char pad_00[0x108]; int field108; char pad_10c[0x270 - 0x10c]; u8 b270; void sub_de52d0(); };
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

    uint32_t nLo = 0;
    uint32_t nHi = 0;
    if (mc8 == 1) {
        __asm { rdtsc }
        __asm { mov nLo, eax }
        __asm { mov nHi, edx }
    } else {
        LARGE_INTEGER li;
        QueryPerformanceCounter(&li);
        nLo = li.u.LowPart;
        nHi = li.u.HighPart;
    }
    mb8 = nLo;
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

// @ 0x00de3300
void GameEntry::FUN_de3300()
{
    void* p = FUN_00df5f40();
    ((Fn2)(*(void***)p)[0x60 / 4])(p, 0, 1);
    p = FUN_00df5f40();
    ((Fn1)(*(void***)p)[0x5c / 4])(p, 0);
    ((GameEntry*)*(u32*)0x16a1344)->ShowGalaxy(0);
    ((GameEntry*)*(u32*)0x16a1344)->ShowGalaxy(1);
    ((GameEntry*)*(u32*)0x16a1344)->mp198->Do();
    mp48 = 0;
    p = FUN_00df5f40();
    return ((Root*)p)->FUN_df95d0();
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
    if ((((u32*)0x16a1848)[id >> 5] >> (id & 0x1f)) & 1)
        return;
    if (id == 0x1b && (*(GameEntry**)0x16a1344)->mb1F1 == 0) {
        void* audio = EA_Audio_GetSystemAT();
        KillSetiEffects(0x5da7b944,
                        audio != 0 ? ((FnU)(*(void***)audio)[0x20 / 4])(audio) : 0);
        ((GameEntry*)*(u32*)0x16a1344)->FUN_de52d0();
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
    char ok = ((FnQC)(*(void***)pm)[0x2c / 4])(pm, *(u32*)0x15a2df8, 0, &prop);
    if (ok) {
        WString16 ws;
        ws.mpBegin = 0x1667bac;
        ws.mpEnd = 0x1667bac;
        ws.mpCap = 0x1667bae;
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
    char* b = mBegin;
    if (b != mEnd) {
        mCurrentDword = *(int*)(mEnd - 4);
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

// @ 0x00de56f0
OutKey3* cGalaxyGameEntryImpl_s00de_5040::FUN_00de56f0(OutKey3& pOut, KeyNode* key)
{
    mRb38.Find((void*)&key, (void**)key);
    if (key != (KeyNode*)&mRb38.sentinel) {
        pOut.a = key->v1c;
        pOut.b = key->v20;
        pOut.c = key->v24;
        return &pOut;
    }
    pOut.a = 0;
    pOut.b = 0;
    pOut.c = 0;
    return &pOut;
}

// @ 0x00de57b0
void cGalaxyGameEntryImpl_s00de_5040::FUN_00de57b0(RbNode57** pOut, RbNode57* parent, Key2* key, char flag)
{
    int left = (flag == 0 && parent != (RbNode57*)&mTree4.root
                && key->a >= parent->key.a) ? 1 : 0;
    RbNode57* node = (RbNode57*)EAllocNew(0x18, (const char*)0x13f09b4, 0, 0, (void*)0x13ebb38, 0xd1);
    if (&node->key != 0)
        node->key = *key;
    RBTreeInsert57(node, parent, &mTree4.root, left);
    *pOut = node;
    mTree4.count++;
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

// @ 0x00de5cb0
bool cGalaxyGameEntryImpl_s00de_5040::FUN_00de5cb0(unsigned int a)
{
    cAchievements* c = FUN_00675250(a);
    if (c->FUN_00675e80())
        return true;
    MapItr it = mRbTree.find(a);
    return it.node != (void*)&mRbTree.sentinel;
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
    bool bBrowserOpen = GetSetting3() && ((AssetBrowser*)GetSetting3())->mb1c;
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
        cString text(nTable, nKey, 0);
        pText->v80(text.GetText());
        text.~cString();
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

// @ 0x00dee3d0
void cGalaxyGameEntryMode::ReleaseOwned()
{
    IWindow_s00de_d5a0* pStateMachine = (IWindow_s00de_d5a0*)mpStateMachine;
    if (pStateMachine)
        pStateMachine->v08();
    ReleaseRef(mpObject04);
    ReleaseRef(mpObject00);
}

// @ 0x00dee770
void SP::GalaxyUI::FUN_00dee770(uint32_t id, void* refObj)
{
    void* w = mLayout.FindWindowByID(id, 1);
    if (w == 0) return;
    void** wvt = *(void***)w;
    void*  d   = ((VFP)wvt[0xa8 / 4])(w);
    if (d == 0) return;
    void** dvt = *(void***)d;
    void*  img = ((VFP1)dvt[0x0c / 4])(d, 0x103c1908);
    if (img == 0) return;
    void*  res = 0;
    CreateImageFromResource2((void*)(size_t)id, &res, 0, -1, -1);
    ((VFIP)dvt[0x14 / 4])(d, 0, res);
    ((VF0)wvt[0x90 / 4])(w);
    if (refObj != 0)
        ((VF0)(*(void***)refObj)[1])(refObj);
}

// @ 0x00dee800
void SP::GalaxyUI::FUN_00dee800(uint32_t id)
{
    void* w = mLayout.FindWindowByID(id, 1);
    if (w == 0) return;
    void** wvt = *(void***)w;
    void*  d   = ((VFP)wvt[0xa8 / 4])(w);
    if (d == 0) return;
    void** dvt = *(void***)d;
    void*  obj = ((VFP1)dvt[0x0c / 4])(d, 0x53eb526);
    if (obj == 0) return;
    void*  res = 0;
    CreateImageFromResource2((void*)(size_t)id, &res, 0, -1, -1);
    ((UIDrawable*)obj)->SetImageIcon(0, res);
    ((VF0)wvt[0x90 / 4])(w);
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
    mMap520.DoNukeSubtree(mMap520.mp0c);
    mMap520.mpRoot  = &mMap520.mpAnchor;
    mMap520.mp0c    = 0;
    mMap520.mFlag   = 0;
    mMap520.mnSize  = 0;
    mMap520.mpAnchor = &mMap520.mpAnchor;
    mMap40.DoNukeSubtree(mMap40.mp0c);
    mMap40.mp0c     = 0;
    mMap40.mFlag    = 0;
    mMap40.mnSize   = 0;
    mMap40.mpRoot   = &mMap40.mpAnchor;
    mMap40.mpAnchor = &mMap40.mpAnchor;
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

// @ 0x00deef20
void SP::GalaxyUI::FUN_00deef20(unsigned a, unsigned b, void* map)
{
    Rbtree* tree = (Rbtree*)map;
    void*   end  = &tree->mpAnchor;
    void*   it[2];
    uint32_t key = b;
    void**  found = (void**)RbtreeFind(it, &key, map);
    RBNode_s00de_e450* node  = (RBNode_s00de_e450*)*found;
    if (node == (RBNode_s00de_e450*)end) return;
    void* w = mLayout.FindWindowByID(0x5384881, 1);
    ((VF2)(*(void***)w)[0x7c / 4])(w, 1, 0);
    GridObj* g = this->mpGrid;
    void* self = (this != 0) ? (void*)&this->field_08 : 0;
    gkGUI_PanelIDs->FUN_00de5d00((void*)(size_t)node->mValue, self,
                                  (void*)g->mB0, 0, 0, (void*)(size_t)b, 0);
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

// @ 0x00def400
void __thiscall SP::cGalaxyGameEntryUIStateMachine_s00de_f400::FUN_00def400()
{
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
void __thiscall cGalaxyGameEntryUIStateMachine_s00de_f400::FUN_00def690()
{
}
}  // namespace SP

// @ 0x00def750
namespace SP {
void __thiscall cGalaxyGameEntryUIStateMachine_s00de_f400::FUN_00def750(uint32_t id, uint32_t value)
{
    (void)id;
    (void)value;
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
void __thiscall cGalaxyGameEntryUIStateMachine_s00de_f400::UpdateNavigationControls()
{
}
}  // namespace SP

// @ 0x00defc00
namespace SP {
void __thiscall cGalaxyGameEntryUIStateMachine_s00de_f400::FUN_00defc00()
{
}
}  // namespace SP

// @ 0x00defc80
namespace SP {
void __thiscall cGalaxyGameEntryUIStateMachine_s00de_f400::MakeRandomName()
{
}
}  // namespace SP

// @ 0x00defd10
namespace SP {
void __thiscall cGalaxyGameEntryUIStateMachine_s00de_f400::SetStateSummaryText()
{
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
void __cdecl FUN_00df0a40()
{
}

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
    if (w == 0 || (((char)(w->Slot2C() >> 2)) & 1) == 0) {
        IWindow_s00df_2d80* w2 = this->mLayout.FindWindowByID(0x54045ce, 1);
        if ((w2->Slot28() & 1) != 0 && (flag != 0 || this->mEntry->m4c.a == 0))
            this->PickRandomCreature();
    }

    w = this->mLayout.FindWindowByID(0x59461b0, 1);
    if (w == 0 || (((char)(w->Slot2C() >> 2)) & 1) == 0) {
        IWindow_s00df_2d80* w2 = this->mLayout.FindWindowByID(0x54045e3, 1);
        if ((w2->Slot28() & 1) != 0 && (flag != 0 || this->mEntry->m64.a == 0))
            this->PickRandomVehicle();
    }

    w = this->mLayout.FindWindowByID(0x59461b2, 1);
    if (w == 0 || (((char)(w->Slot2C() >> 2)) & 1) == 0) {
        IWindow_s00df_2d80* w2 = this->mLayout.FindWindowByID(0x5404617, 1);
        if ((w2->Slot28() & 1) != 0 && (flag != 0 || this->mEntry->m70.a == 0))
            this->PickRandomByMode(0x5404617, 0x99e92f05, &this->mEntry->m70);
    }
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

// @ 0x00df7ce0
void __cdecl FUN_00df7ce0()
{
}

// @ 0x00df7f60
void __cdecl GetSavedGames()
{
}

// @ 0x00df82d0
void __cdecl FUN_00df82d0()
{
}

// @ 0x00df8330
void __cdecl SetupRolloverStarEffects()
{
}

// @ 0x00df85e0
void __cdecl SetGameToEnter()
{
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

// @ 0x00e00560
void __stdcall e00560(int dummy)
{
    (void)dummy;
    void* ab = SP_AssetBrowser();
    GObj* g = *(GObj**)0x16a1344;
    if (g->field108 == 7 &&
        *(char*)((char*)ab + 0x1c) == 0 &&
        g->b270 == 0) {
        int* mm = *(int**)0x16c7aa4;
        EC* ec = *(EC**)((char*)mm + 0x1c);
        if (!ec->sub_ec4320()) {
            (*(GObj**)0x16a1344)->sub_de52d0();
        }
    }
}

// @ 0x00e005b0
void __cdecl e005b0()
{
    char buf[0x48];
    sub_644b10(buf);
    if ((int)SP_GetCurrentGameMode() == 0x2ccd1d2) {
        int* p = (int*)operator_new(0x14, "Sporepedia", 0, 0, 0, 0);
        if (p) {
            int* g = *(int**)0x16a1344;
            p[1] = 0x13ec458;
            p[2] = 0;
            p[0] = 0x147dc04;
            p[1] = 0x149bad8;
            p[3] = (int)g;
            *(u8*)(p + 4) = 0;
        }
        sub_e02040(buf);
    }
    sub_644b60(buf);
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
