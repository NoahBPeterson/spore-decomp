// src/game/SPGonzago/SPCellSlowCompile.cpp -- migrated from slice(s) s00e84850, s00e83910, s00e829c0, s00e819b0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCellSlowCompile.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>
#include <intrin.h>

// ---- items of slice s00e819b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
int   FUN_00e932e80(int a, int b, int c);   // 0x00e932e80
int*  FUN_00a206f0();                        // 0x00a206f0
void  Start3dSoundByName(int a, int b, int c, int d, int e);   // 0x00571f80
void  KillSetiEffects();                     // 0x00435ed0
void* GameInputManager();                 // 0x00b3d250
int*  FUN_0067dd00();                     // 0x0067dd00
int*  FUN_006eea10();                     // 0x006eea10
struct IVtbl17 {
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
    virtual char m(int a, int b);
};
struct IVtbl30 {
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
    virtual void m(int a);
};
int   SetGlobalProperty(int a, float b);  // 0x005ca880
void  PlayEditorSound(int a, int b, float c, int d);  // 0x00435f40
void  FUN_00572020(int a, int b);         // 0x00572020
void  FUN_009fbc50(int a, float x, float y, float z);  // 0x009fbc50
// ---- items of slice s00e819b0 end

// ---- items of slice s00e829c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma warning(disable : 4100)
namespace SP {
class cSPUILayoutManager {
public:
    bool IsWorldVisible(uint32_t worldId);              // 0x00810760
    void SetWorldVisible(uint32_t worldId, bool visible); // 0x00810660
    void DoLayout(uint32_t worldId, bool visible);      // 0x0080...
};
}
namespace SP {
cSPUILayoutManager* __cdecl GetLayoutManager();         // 0x00805070
}
namespace SP {
void* __cdecl FUN_0067cb30(uint32_t variantId, void* pAsset, int32_t low, int32_t high);
}
namespace SP {
void* __cdecl FUN_0067cac0(void* pAsset, ...);
}
namespace SP {
struct cAssetVariantUpdater {
    void UpdateAssetVariant(uint32_t variantId, void* pAsset, int32_t low, int32_t high);
    void UpdateVariantForAsset();
    void ClearVariant();
    void SetVariantFlag(int value);
};
}
namespace SP {
struct cVec3 {
    float mX;                                           // +0x00
    float mY;                                           // +0x04
    float mZ;                                           // +0x08
};
}
namespace SP {
struct cLayoutData {
    uint8_t  pad00[0x18];
    cVec3    mPosition;                                 // +0x18
    uint8_t  pad24[0x2c0];
    void*    mpEntries;                                 // +0x2e4 -> cLayoutEntryList
};
}
namespace SP {
struct cLayoutOwner {
    uint8_t     pad000[0x17c];
    cLayoutData* mpLayout;                              // +0x17c
};
}
namespace SP {
void* __cdecl FUN_0067caf0(cVec3 key, int a, int worldId, cVec3 offset, int c, int d);
}
namespace SP {
struct cLayoutPlacement {
    void Commit();                                      // 0x0067aaf0
};
}
namespace SP {
namespace Achievements {
class Controller {
public:
    void AwardAchievement(uint32_t id);                 // 0x00676710
    void DecrementAccumulatorValue();                   // 0x00676f20
    void SetAchievementProgress(uint32_t a, uint32_t b, uint32_t c);
    void Flush();
    void Flush(uint32_t a, uint32_t b, uint32_t c);     // 0x00676ed0
};
}
}
namespace SP {
namespace Achievements {
Controller* __cdecl GetController();                    // 0x00675250
}
}
namespace SP {
namespace Achievements {
Controller* __cdecl GetController(uint32_t a, uint32_t b, uint32_t c);
}
}
namespace SP {
struct cSettingsSection {
    uint8_t pad00[0x1c];
    uint8_t mbEnabled;                                  // +0x1c
};
}
namespace SP {
cSettingsSection* __cdecl AssetBrowserSettings();       // 0x00401030
}
namespace SP {
cSettingsSection* __cdecl SporeGuideSettings();         // 0x00401040
}
namespace SP {
void* __cdecl FUN_00b3d340();                           // 0x00b3d340
}
namespace SP {
void* __cdecl FUN_00b3d4f0();                           // 0x00b3d4f0
}
namespace SP {
struct cController {
virtual void c00();
virtual void c04();
virtual void c08();
virtual void c0c();
virtual void c10();
virtual void c14();
virtual void c18();
virtual void c1c();
virtual void c20();
virtual void c24();
virtual void c28();
virtual void c2c();
virtual void c30();
virtual void c34();
    virtual void SetFloatProperty(uint32_t id);         // +0x38 (index 14)
};
}
namespace SP {
struct cWorldManager {
virtual void w00();
virtual void w04();
virtual void w08();
virtual void w0c();
virtual void w10();
virtual void w14();
virtual void w18();
    virtual void RefreshScene();                        // +0x1c
};
}
namespace SP {
struct tLayoutKey {
    uint32_t mId;                                       // +0x00
    uint32_t mGroup;                                    // +0x04
    uint32_t mName;                                     // +0x08
    uint32_t mExtra;                                    // +0x0c
};
}
namespace SP {
struct cEditorState {
    uint32_t mMode;                                     // +0x0c
    tLayoutKey mPosition;                               // +0x18 (x/y/z)
    uint32_t mTarget;                                   // +0x34
    uint8_t  mbFlag;                                    // +0x44
};
}
namespace SP {
struct cEditorWorld {
    uint32_t mMode;                                     // +0x00
    uint8_t  pad04[0x0c];
    uint8_t  mbVisible;                                 // +0x10
};
}
// ---- items of slice s00e829c0 end

// ---- items of slice s00e83910 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* gMemPool;                             // 0x016c8b44
#pragma warning(disable: 4100)
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed int     i32;
typedef unsigned __int64 u64;
typedef float          f32;
#define MOPS(p) ((COps*)(p))
#define VT(p)   (*(void***)(p))
static inline void Release(void* p)
{
    if (p) { void** vt = *(void***)p; ((void (__thiscall*)(void*))vt[1])(p); }
}
void* __cdecl FUN_0067de40();                                     // 0x0067de40
void* __cdecl FUN_0067de60();                                     // 0x0067de60
void* __cdecl FUN_0067dcd0();                                     // 0x0067dcd0
void* __cdecl FUN_00675250();                                     // 0x00675250
u8    __cdecl FUN_006ab760(void* a, const u16* b);                // 0x006ab760
i32*  __cdecl FUN_0041ea00();                                     // 0x0041ea00
void* __cdecl FUN_00b3d300();                                     // 0x00b3d300
u64   __cdecl FUN_00593980(u32 a, i32 b);                         // 0x00593980
void* __cdecl FUN_00f473a0(u32 size, const char* file, u32 a, u32 b, u32 c, u32 d); // 0x00f473a0
void  __cdecl FUN_00f47380(void* p);                              // 0x00f47380
void  __cdecl FUN_004ba150(void* out);                            // 0x004ba150
u8    __cdecl FUN_006ad010(char* name);                           // 0x006ad010
void* __cdecl FUN_008de1a0();                                     // 0x008de1a0
void* __cdecl FUN_006b1f90(u32 area, u32 b, void* c);             // 0x006b1f90
void  __cdecl FUN_006b4b60(void* a, void* b);                     // 0x006b4b60
void* __cdecl FUN_00401090();                                     // 0x00401090
void* __cdecl FUN_009289f0(void* pool, u32 a, u32 b, u32 c, u32 d, u32 e); // 0x009289f0
void* __cdecl FUN_008ddb00(void* a, void* b, void* c, void* d, u32 e, void* f); // 0x008ddb00
u8    __cdecl FUN_008ddb90(void* a, void* b, void* c, void* d, u32 e); // 0x008ddb90
void  __cdecl FUN_009276c0(void* pool, void* p);                  // 0x009276c0
i32   __cdecl FUN_00e82770(void* p);                              // 0x00e82770
void  __cdecl FUN_004bafc0(void* a, void* b);                     // 0x004bafc0
void  __cdecl FUN_0059c190(f32* mat, f32* q);                     // 0x0059c190
void  __cdecl FUN_005a9200(void* launch);                         // 0x005a9200
void* __cdecl FUN_011e0744(void* d, const void* s, u32 n);        // 0x011e0744
void* __cdecl FUN_0067dcc0();                                     // 0x0067dcc0
extern u16 gEmptyString16[];                       // 0x01667bac
extern u16 gString16_b[];                          // 0x01667bae
extern f32 gHalf;                                  // 0x01471064
extern f32 gOne;                                   // 0x01485720
extern f32 gVerbScale;                             // 0x01486114
extern f32 gQScale;                                // 0x01470f1c
extern u32 gEditorVecA;                            // 0x016b4504
extern u32 gEditorVecB;                            // 0x016b4508
extern u32 gEditorVecC;                            // 0x016b450c
extern u32 gEditorMat[9];                          // 0x016b4554
extern u32 gVerbTable[];                           // 0x014860ac
extern u32 gVerbBaseA;                             // 0x0150d6d8
extern u32 gVerbBaseB;                             // 0x0150d6dc
struct COps
{
    void* FUN_00f67d90();                              // 0x00f67d90
    void  FUN_006751a0(u32 a, void** out);             // 0x006751a0
    void  FUN_00c7a1f0(u32 player);                    // 0x00c7a1f0
    void  FUN_00598540(u32 key);                       // 0x00598540
    void  FUN_00598db0(i32 a, i32 b, i32 c, i32 d, i32 e,
                       i32 f, i32 g, f32 h, i32 i);    // 0x00598db0
    void  FUN_00596d70(i32 a, i32 b);                  // 0x00596d70
    u8    FUN_00595110(void* a, i32 b);                // 0x00595110
    void  FUN_00596da0(i32 a, i32 b, i32 c);           // 0x00596da0
    void  FUN_005942e0();                              // 0x005942e0
    void* FUN_00414e10();                              // 0x00414e10
    void  FUN_004df310(void* key);                     // 0x004df310
    void  FUN_00423650(const u16* first, const u16* last);// 0x00423650
    void  FUN_00475ab0(u32 n);                         // 0x00475ab0
    void  FUN_00550cf0(u16** wstr);                    // 0x00550cf0
    void* FUN_005508c0(u32 id, u32 a, u32 b);          // 0x005508c0
    void  FUN_00551240(void* a, const u16* name, const u16* summary,
                       u32 b, void* c, u32 d, u32 e);  // 0x00551240
    void* FUN_005a9080();                              // 0x005a9080
    void  FUN_005a9080_b();                            // 0x005a9080
};
struct cTerrainSphere
{
    u8    pad0[0x10e8];        // +0x0000
    void* mpCollectables;      // +0x10e8
    u32   mKeyA;               // +0x10ec
    u8    pad10f0[0x0c];       // +0x10f0
    u32   mKeyB;               // +0x10fc
};
struct cResKey
{
    u32 v0;                    // +0x00
    u32 v1;                    // +0x04
    u32 v2;                    // +0x08
    u32 pad;                   // +0x0c
};
struct cEditorLaunch
{
    void* mpVtbl;      // +0x00
    u8    pad04[0x0c];
    u32   mField0c;    // +0x0c
    u32   mField10;    // +0x10
    u32   mField14;    // +0x14
    u32   mField18;    // +0x18
    u8    pad1c[0x20 - 0x1c];
    u8    mField20;    // +0x20
    u8    pad21[0x34 - 0x21];
    u8    mField34;    // +0x34
    u8    mField36;    // +0x36
    u8    mField37;    // +0x37
    u8    mField38;    // +0x38
    u8    mField39;    // +0x39
    u8    pad3a[0x3c - 0x3a];
    u8    mField3c;    // +0x3c
    u8    mField3d;    // +0x3d
    u8    pad3e[0x60 - 0x3e];
    f32   mField60;    // +0x60
    u8    mField64;    // +0x64
};
struct cRegMessage
{
    void* mpVtbl;      // +0x00
    u32   mField04;    // +0x04
    u32   mField08;    // +0x08
    u32   mField0c;    // +0x0c
    u32   mField10;    // +0x10
    u32   mField14;    // +0x14
    u32   mField18;    // +0x18
    u8    pad1c[0x30 - 0x1c];
    u32   mField30;    // +0x30
    u8    pad34[0x38 - 0x34];
    u32   mField38;    // +0x38
};
struct cString8
{
    u8*  mpBegin;      // +0x00
    u8*  mpEnd;        // +0x04
    u8*  mpCap;        // +0x08
    u8   pad0c[4];     // +0x0c
    u32  mKey0;        // +0x10
    u32  mKey1;        // +0x14

    void FUN_00475ab0(u32 n);                       // 0x00475ab0
    cString8* FUN_00e847f0(u32* src, u32* key);
};
// ---- items of slice s00e83910 end

// ---- items of slice s00e84850 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memcpy_(void* pDest, const void* pSrc, unsigned int size);
struct tNameSource {
    const char* mpFirst;                                 // +0x00
    const char* mpLast;                                  // +0x04
    uint8_t     pad008[8];                               // +0x08 .. +0x0f
    uint32_t    mField10;                                // +0x10
    uint32_t    mField14;                                // +0x14
};
class cLayoutName {
public:
    cLayoutName* FUN_00e84850(tNameSource* pSource);

    // eastl::basic_string<char> range initialisation (external).
    void RangeInitialize(int32_t size);                  // 0x00475ab0

    char*     mpBegin;                                   // +0x00
    char*     mpEnd;                                     // +0x04
    char*     mpCapacity;                                // +0x08
    uint8_t   pad00c[4];                                 // +0x0c
    uint32_t  mField10;                                  // +0x10
    uint32_t  mField14;                                  // +0x14
};
// ---- items of slice s00e84850 end

// @ 0x00e82620
int FUN_00e82620(int param_1, int* param_2)
{
    int uVar1 = FUN_00e932e80(param_1, 0x811c9dc5, 1);
    int* piVar2 = (int*)FUN_00a206f0();
    int uVar3;
    if (piVar2 == 0)
        uVar3 = 0;
    else
        uVar3 = (*(int(**)(void))(*piVar2 + 0x20))();
    if (param_2 != 0) {
        Start3dSoundByName(uVar1, uVar3, param_2[0], param_2[1], param_2[2]);
        return uVar3;
    }
    KillSetiEffects();
    return uVar3;
}

// @ 0x00e82690
void FUN_00e82690(int a, float b)
{
    SetGlobalProperty(a, b);
}

// @ 0x00e826b0
void FUN_00e826b0(int a, int b, float c)
{
    if (a != 0)
        PlayEditorSound(a, b, c, 0);
}

// @ 0x00e826e0
void FUN_00e826e0(int a)
{
    if (a != 0)
        FUN_00572020(a, 0);
}

// @ 0x00e82700
void FUN_00e82700(int a, float* v)
{
    if (a != 0)
        FUN_009fbc50(a, v[0], v[1], v[2]);
}

// @ 0x00e82730
int* FUN_00e82730(int a)
{
    int* p = (int*)FUN_006eea10();
    ((IVtbl30*)p)->m(a);
    return p;
}

// @ 0x00e82760
void FUN_00e82760()
{
    int* p = (int*)FUN_0067dd00();
    int* vt = (int*)*p;
    (*(void(__fastcall*)(void*))vt[0x54 / 4])(p);
}

// @ 0x00e82900
bool FUN_00e82900(int a, int b)
{
    int* p = (int*)GameInputManager();
    return ((IVtbl17*)p)->m(a, b) != 0;
}

// @ 0x00e829c0
namespace SP {
void __cdecl FUN_00e829c0(uint32_t worldId, bool visible)
{
    cSPUILayoutManager* pManager = GetLayoutManager();
    while (pManager->IsWorldVisible(worldId) == !visible)
        pManager->SetWorldVisible(worldId, visible);
}
}  // namespace SP

// @ 0x00e82a10
namespace SP {
void __cdecl FUN_00e82a10(uint32_t worldId, bool visible)
{
    cSPUILayoutManager* pManager = GetLayoutManager();
    if (pManager->IsWorldVisible(worldId) != visible)
        pManager->SetWorldVisible(worldId, visible);
}
}  // namespace SP

// @ 0x00e82be0
namespace SP {
void __cdecl FUN_00e82be0(void* pAsset, bool enabled)
{
    if (enabled) {
        cAssetVariantUpdater* pUpdater = (cAssetVariantUpdater*)FUN_0067cac0(pAsset);
        pUpdater->UpdateVariantForAsset();
    } else {
        cAssetVariantUpdater* pUpdater = (cAssetVariantUpdater*)FUN_0067cac0(pAsset, 0);
        pUpdater->ClearVariant();
    }
}
}  // namespace SP

// @ 0x00e82c10
namespace SP {
void __cdecl FUN_00e82c10(void* pAsset, int32_t a, int32_t b, int32_t c)
{
    cAssetVariantUpdater* pUpdater;

    pUpdater = (cAssetVariantUpdater*)FUN_0067cb30(0x20f60c49, pAsset, a, a >> 31);
    pUpdater->UpdateAssetVariant(0x20f60c49, pAsset, a, a >> 31);

    pUpdater = (cAssetVariantUpdater*)FUN_0067cb30(0xf43a2c4b, pAsset, b, b >> 31);
    pUpdater->UpdateAssetVariant(0xf43a2c4b, pAsset, b, b >> 31);

    pUpdater = (cAssetVariantUpdater*)FUN_0067cb30(0x3f2955cd, pAsset, c, c >> 31);
    pUpdater->UpdateAssetVariant(0x3f2955cd, pAsset, c, c >> 31);
}
}  // namespace SP

// @ 0x00e82c70
namespace SP {
void __cdecl FUN_00e82c70()
{
    ((cWorldManager*)FUN_00b3d340())->RefreshScene();
}
}  // namespace SP

// @ 0x00e82c80
namespace SP {
void __cdecl FUN_00e82c80(cEditorState* pState, uint32_t* pMode, uint8_t* pFlag, uint32_t* pTarget, tLayoutKey* pPosition)
{
    *pMode = pState->mMode;
    *pFlag = pState->mbFlag;
    *pTarget = pState->mTarget;
    pPosition->mId = pState->mPosition.mId;
    pPosition->mGroup = pState->mPosition.mGroup;
    pPosition->mName = pState->mPosition.mName;
}
}  // namespace SP

// @ 0x00e82cc0
namespace SP {
uint8_t __cdecl FUN_00e82cc0()
{
    return AssetBrowserSettings()->mbEnabled;
}
}  // namespace SP

// @ 0x00e82cd0
namespace SP {
uint8_t __cdecl FUN_00e82cd0()
{
    return SporeGuideSettings()->mbEnabled;
}
}  // namespace SP

// @ 0x00e82cf0
namespace SP {
void __cdecl FUN_00e82cf0(uint32_t a, uint32_t b, uint32_t c)
{
    Achievements::GetController(a, b, c)->Flush(a, b, c);
}
}  // namespace SP

// @ 0x00e82d10
namespace SP {
void __cdecl FUN_00e82d10(uint32_t achievementId)
{
    Achievements::GetController()->AwardAchievement(achievementId);
}
}  // namespace SP

// @ 0x00e82d30
namespace SP {
void __cdecl FUN_00e82d30()
{
    Achievements::GetController()->DecrementAccumulatorValue();
}
}  // namespace SP

// @ 0x00e82d50
namespace SP {
void __cdecl FUN_00e82d50(cVec3* pKey, int worldId)
{
    cVec3 offset;
    offset.mX = -1.0f;
    offset.mY = -1.0f;
    offset.mZ = 0.0f;

    cLayoutPlacement* pPlacement =
        (cLayoutPlacement*)FUN_0067caf0(*pKey, 0, worldId, offset, 0, 0);
    pPlacement->Commit();
}
}  // namespace SP

// @ 0x00e82de0
namespace SP {
void __cdecl FUN_00e82de0(uint32_t a, uint32_t b)
{
    cController* pController = (cController*)FUN_00b3d4f0();
    pController->SetFloatProperty(a);
}
}  // namespace SP

// @ 0x00e82e00
namespace SP {
void __cdecl FUN_00e82e00(cEditorState* pState, cEditorState* pOther, int mode)
{
    if (!pState || !pOther)
        return;
    pState->mMode = (uint32_t)mode;
    pState->mPosition.mId = pOther->mPosition.mId;
    pState->mPosition.mGroup = pOther->mPosition.mGroup;
    pState->mPosition.mName = pOther->mPosition.mName;
}
}  // namespace SP

// @ 0x00e83040
namespace SP {
void __cdecl FUN_00e83040(cEditorState* pState, int mode)
{
    if (!pState)
        return;
    pState->mMode = (uint32_t)mode;
    pState->mbFlag = mode != 0;
}
}  // namespace SP

// @ 0x00e831a0
namespace SP {
void __cdecl FUN_00e831a0(tLayoutKey* pKey, uint32_t id, uint32_t group)
{
    pKey->mId = id;
    pKey->mGroup = group;
    pKey->mName = 0;
}
}  // namespace SP

// @ 0x00e831d0
namespace SP {
uint32_t __cdecl FUN_00e831d0(int mode)
{
    switch (mode) {
    case 0:
        return 0x20f60c49;
    case 1:
        return 0xf43a2c4b;
    case 2:
        return 0x3f2955cd;
    default:
        return 0;
    }
}
}  // namespace SP

// @ 0x00e83350
namespace SP {
void __cdecl FUN_00e83350(cVec3* pOut, cLayoutOwner* pOwner)
{
    cLayoutData* pLayout = pOwner->mpLayout;
    *pOut = pLayout->mPosition;
}
}  // namespace SP

// @ 0x00e83380
namespace SP {
uint32_t __cdecl FUN_00e83380(cEditorWorld* pWorld, int mode, float* pOut)
{
    if (!pWorld)
        return 0;
    *pOut = (float)mode;
    return pWorld->mbVisible;
}
}  // namespace SP

// @ 0x00e833f0
namespace SP {
void __cdecl FUN_00e833f0(uint32_t a, uint32_t b, uint32_t c)
{
    cSPUILayoutManager* pManager = GetLayoutManager();
    pManager->DoLayout(a, b != 0);
    pManager->DoLayout(c, b != 0);
}
}  // namespace SP

// @ 0x00e83430
namespace SP {
int __cdecl FUN_00e83430(cEditorWorld* pWorld)
{
    if (!pWorld)
        return 0;
    return pWorld->mbVisible ? 1 : 0;
}
}  // namespace SP

// @ 0x00e83470
namespace SP {
int __cdecl FUN_00e83470(cEditorWorld* pWorld, int mode)
{
    if (!pWorld || !pWorld->mbVisible)
        return 0;
    return (int)pWorld->mMode == mode;
}
}  // namespace SP

// @ 0x00e834d0
namespace SP {
void __cdecl FUN_00e834d0(cEditorState* pState, int mode, int flag)
{
    if (!pState)
        return;
    pState->mMode = (uint32_t)mode;
    pState->mTarget = (uint32_t)flag;
}
}  // namespace SP

// @ 0x00e83590
namespace SP {
void __cdecl FUN_00e83590(cEditorState* pState)
{
    if (!pState)
        return;
    pState->mPosition.mId = 0;
    pState->mPosition.mGroup = 0;
    pState->mPosition.mName = 0;
    pState->mbFlag = 0;
}
}  // namespace SP

// @ 0x00e83640
namespace SP {
void __cdecl FUN_00e83640(cEditorState* pState, uint32_t value)
{
    if (!pState)
        return;
    pState->mTarget = value;
}
}  // namespace SP

// @ 0x00e836f0
namespace SP {
void __cdecl FUN_00e836f0()
{
    cSPUILayoutManager* pManager = GetLayoutManager();
    pManager->SetWorldVisible(0, true);
}
}  // namespace SP

// @ 0x00e837c0
namespace SP {
float __cdecl FUN_00e837c0()
{
    cEditorWorld* pWorld = (cEditorWorld*)FUN_00b3d340();
    if (!pWorld)
        return 0.0f;
    return pWorld->mbVisible ? 1.0f : 0.0f;
}
}  // namespace SP

// @ 0x00e83910
void FUN_00e83910(u32 arg1, u32 arg2, u32 arg3)
{
    cTerrainSphere* ed = (cTerrainSphere*)MOPS(FUN_00b3d300())->FUN_00f67d90();
    ed->mKeyA = arg2;
    ed->mKeyB = arg3;

    cResKey local_40;
    local_40.v0 = 0;
    local_40.v1 = 0;
    local_40.v2 = 0;

    void* idgen = FUN_0067de60();
    ((void (__thiscall*)(void*, void*, u32, u32, u32, u32, u32))VT(idgen)[0x04 / 4])(
        idgen, &local_40, 0x2b978c46, 0x62, 0, 0x62, 0);

    void* guard = 0;
    void* mgr = FUN_0067dcd0();
    if (guard) Release(guard);

    void* obj = 0;
    u8 ok = ((u8 (__thiscall*)(void*, u32, void**, u32, u32, u32, u32))VT(mgr)[0x0c / 4])(
                mgr, arg1, &obj, 0, 0, 0, 0);
    if (ok)
    {
        MOPS(ed)->FUN_00c7a1f0(*(u32*)&obj);
        if (ed->mpCollectables)
        {
            MOPS(ed->mpCollectables)->FUN_00598540(0x465c50ba);
            u32* p = gVerbTable;
            do
            {
                u64 a = FUN_00593980(gVerbBaseA, p[-1]);
                u64 b = FUN_00593980(gVerbBaseB, p[0]);
                MOPS(ed->mpCollectables)->FUN_00598db0(
                    (i32)b, (i32)(b >> 32), 0, 0, 0, 0, 0, 0.0f, 0);
                MOPS(ed->mpCollectables)->FUN_00596d70((i32)b, (i32)(b >> 32));
                if (guard && MOPS(ed->mpCollectables)->FUN_00595110((void*)a, (i32)(a >> 32)))
                    MOPS(ed->mpCollectables)->FUN_00596da0((i32)b, (i32)(b >> 32), 0);
                p += 2;
            } while ((u32)p < 0x148610c);
            MOPS(ed->mpCollectables)->FUN_005942e0();
        }
        void* blk = 0;
        FUN_004ba150(&blk);
        *((u32*)blk + 2) = local_40.v0;
        *((u32*)blk + 3) = local_40.v1;
        *((u32*)blk + 4) = local_40.v2;
        FUN_006ad010((char*)blk);
        cResKey key2;
        key2.v0 = local_40.v0;
        key2.v1 = local_40.v1;
        key2.v2 = 0x1a99b06b;
        void* dbg = FUN_008de1a0();
        ((void (__thiscall*)(void*, void*, u32))VT(dbg)[0x6c / 4])(dbg, blk, 1);
        void* sa = FUN_006b1f90(0x11ac199, 0, &key2);
        FUN_006b4b60(blk, sa);
        void* spm = FUN_00401090();
        MOPS(spm)->FUN_004df310(&local_40);
        Release(blk);
    }

    cResKey keyA;
    keyA.v0 = *(u32*)&local_40.v0;
    keyA.v1 = 0x2f7d0004;
    keyA.v2 = local_40.v2;
    void* resmgr = FUN_0067dcd0();
    void* res = ((void* (__thiscall*)(void*, void*))VT(resmgr)[0x58 / 4])(resmgr, &keyA);
    void* sa2 = FUN_006b1f90(0x11ac199, 0, 0);
    u8 flag = 0;

    if (res && sa2)
    {
        u8 c1 = ((u8 (__thiscall*)(void*, void*, u32, u32, u32, u32, void*))VT(res)[0x34 / 4])(
                    res, &keyA, 0, 1, 6, 0, &keyA.v2);
        if (c1 && keyA.v2 != 0xffffffff)
        {
            void* p = FUN_009289f0(gMemPool, keyA.v2, 0, 0, 0, 0);
            void* r2 = FUN_008ddb00(res, &keyA, p, (void*)keyA.v2, 1, 0);
            if (r2 == (void*)keyA.v2)
                flag = FUN_008ddb90(sa2, &keyA, p, r2, 1);
            if (p) FUN_009276c0(gMemPool, p);
            if (flag)
            {
                keyA.v1 = (keyA.v1 & 0xffffff01) | 1;
                u8 c2 = ((u8 (__thiscall*)(void*, void*, u32, u32, u32, u32, void*))VT(res)[0x34 / 4])(
                            res, &keyA, 0, 1, 6, 0, &keyA.v2);
                if (c2 && keyA.v2 != 0xffffffff)
                {
                    void* q = FUN_009289f0(gMemPool, keyA.v2, 0, 0, 0, 0);
                    void* r3 = FUN_008ddb00(res, &keyA, q, (void*)keyA.v2, 1, 0);
                    if (r3 == (void*)keyA.v2)
                        flag = FUN_008ddb90(sa2, &keyA, q, r3, 1);
                    if (q) FUN_009276c0(gMemPool, q);
                }
            }
        }
    }

    cResKey keyB;
    keyB.v0 = ((u32*)&keyA.v0)[0];
    keyB.v1 = 0x30bdee3;
    keyB.v2 = ((u32*)&keyA.v0)[2];
    void* guard2 = 0;
    if (flag)
    {
        void* mgr2 = FUN_0067dcd0();
        if (guard2) Release(guard2);
        void* obj2 = 0;
        if (((u8 (__thiscall*)(void*, void*, void**, u32, u32, u32, u32))VT(mgr2)[0x0c / 4])(
                mgr2, &keyB, &obj2, 0, 0, 0, 0))
        {
            void* meta = obj2
                ? ((void* (__thiscall*)(void*, u32))VT(obj2)[0x0c / 4])(obj2, 0x30bdee3)
                : 0;
            void* aobj = FUN_00f473a0(0xd8, "Pollinator", 0, 0, 0, 0);
            if (aobj)
            {
                void* md = MOPS(aobj)->FUN_005a9080();
                if (md) Release(md);
            }
            u16* ws0 = gEmptyString16;
            u16* ws1 = gEmptyString16;
            u16* ws2 = gString16_b;
            MOPS(meta)->FUN_00550cf0(&ws0);
            void* mid = MOPS(meta)->FUN_005508c0((u32)ws0, (u32)meta, 0);
            void* nm = MOPS(meta)->FUN_00414e10();
            MOPS(meta)->FUN_00551240(&keyB, (const u16*)nm, (const u16*)mid,
                                     (u32)ws0, &keyB, 0, 0);
            void* mgr3 = FUN_0067dcd0();
            ((void (__thiscall*)(void*, void*, u32, void*, u32, u32))VT(mgr3)[0x20 / 4])(
                mgr3, meta, 0, sa2, 0, 0);
            if (((u32)ws2 - (u32)ws0 & 0xfffffffe) > 2 && ws0)
                FUN_00f47380(ws0);
            Release(meta);
        }
        Release(guard2);
    }
}

// @ 0x00e83e30
void FUN_00e83e30(i32* param_1, u8* param_2, u32* param_3)
{
    if (param_3[1] == 0x476a98c7)
    {
        *param_1 = 1;
        param_2[0] = 1;
        *(u32*)(param_2 + 4) = 0xb;
        *(u32*)(param_2 + 8) = gEditorVecA;
        *(u32*)(param_2 + 0xc) = gEditorVecB;
        *(u32*)(param_2 + 0x10) = gEditorVecC;
        for (int i = 0; i < 9; i++)
            ((u32*)(param_2 + 0x14))[i] = gEditorMat[i];
        *(f32*)(param_2 + 0x38) = gOne;
        *(u32*)(param_2 + 0x3c) = gEditorVecA;
        *(u32*)(param_2 + 0x40) = gEditorVecB;
        *(u32*)(param_2 + 0x44) = gEditorVecC;
        return;
    }

    void* local_2c = 0;
    FUN_004bafc0(param_3, &local_2c);
    i32 cnt = (*(i32*)((u8*)local_2c + 0x9c) - *(i32*)((u8*)local_2c + 0x98)) / 0x8c;
    i32 n = cnt > 0x40 ? 0x40 : cnt;
    *param_1 = 0;
    for (i32 i = 0; i < n; i++)
    {
        u8* p = (u8*)(*(i32*)((u8*)local_2c + 0x98) + i * 0x8c);
        i32 r = FUN_00e82770(p);
        i32 idx = *param_1;
        *param_1 = idx + 1;
        u8* rec = param_2 + idx * 0x48;
        *(i32*)(rec + 4) = r;
        rec[0] = (*(u16*)(p + 6) == 0xffff) ? 1 : 0;

        f32 s = *(f32*)(p + 0x2c);
        f32 m14 = s * (*(f32*)(p + 0x14) * gVerbScale);
        f32 m18 = s * (*(f32*)(p + 0x18) * gVerbScale);
        f32 m1c = s * (*(f32*)(p + 0x1c) * gVerbScale);
        f32 m20 = s * (*(f32*)(p + 0x20) * gVerbScale);
        f32 m24 = s * (*(f32*)(p + 0x24) * gVerbScale);
        f32 m28 = s * (*(f32*)(p + 0x28) * gVerbScale);

        f32 t14 = (m28 + m1c) * gHalf;
        f32 t18 = (m20 - m14) * gHalf;
        f32 t1c = (m20 + m14) * gHalf;
        f32 t20 = (m24 + m18) * gHalf;
        f32 t24 = (m28 - m1c) * gHalf;

        *(f32*)(rec + 8) = *(f32*)(p + 0x54) * gVerbScale +
            (*(f32*)(p + 0x48) * t14 + *(f32*)(p + 0x3c) * t20 + *(f32*)(p + 0x30) * t1c);
        *(f32*)(rec + 0xc) = *(f32*)(p + 0x58) * gVerbScale +
            (*(f32*)(p + 0x4c) * t14 + *(f32*)(p + 0x40) * t20 + *(f32*)(p + 0x34) * t1c);
        *(u32*)(rec + 0x10) = 0;

        f32 a1 = fabsf(t24);
        f32 a2 = fabsf(t18);
        f32 mx = a1 > a2 ? a1 : a2;
        *(f32*)(rec + 0x38) = mx;
        f32 sc = (r == 2 && *param_3 == 0xd9007204) ? gHalf : gOne;
        *(f32*)(rec + 0x38) = mx * sc;

        for (int k = 0; k < 9; k++)
            ((u32*)(rec + 0x14))[k] = ((u32*)(p + 0x30))[k];
        *(u32*)(rec + 0x3c) = *(u32*)(p + 0x60);
        *(u32*)(rec + 0x40) = *(u32*)(p + 0x64);
        *(u32*)(rec + 0x44) = *(u32*)(p + 0x68);
    }
    if (local_2c) Release(local_2c);
}

// @ 0x00e84150
void FUN_00e84150(u8* param_1, i32 param_2, u16* param_3)
{
    i32* P = *(i32**)(param_1 + 0x17c);
    i32* V = (i32*)*P;
    i32 count = (*(i32*)((u8*)V + 0x388) - *(i32*)((u8*)V + 0x384)) / 0x468;
    i32 i20 = *(i32*)((u8*)P + 0x2e4);
    i32* pi23 = (i32*)(*(i32*)((u8*)V + 0x384) + 0x21c);
    i32 idx = 0;
    while (idx < count)
    {
        if (*pi23 == param_2)
        {
            u8* pP = (u8*)P;
            u8* p20 = (u8*)i20;
            f32 a = *(f32*)(pP + 0x3c);
            f32 b = *(f32*)(pP + 0x40);
            f32 c = *(f32*)(pP + 0x44);
            f32 d = *(f32*)(pP + 0x48);
            f32 e = *(f32*)(p20 + 0x10);
            f32 f = *(f32*)(p20 + 0x14);
            f32 g = *(f32*)(p20 + 0x18);
            f32 h = *(f32*)(p20 + 0x1c);
            f32 k = *(f32*)(p20 + 0x20);
            f32 l = *(f32*)(p20 + 0x24);
            f32 m = *(f32*)(p20 + 0x28);

            f32 q[4];
            q[0] = ((a * m + h * d) - b * l) + c * k;
            q[1] = ((l * a + b * m) + k * d) - c * h;
            q[2] = ((l * d - k * a) + c * m) + b * h;
            q[3] = ((m * d - a * h) - k * b) - c * l;

            f32 mat[9];
            FUN_0059c190(mat, q);

            *param_3 |= 6;
            *(f32*)((u8*)param_3 + 4) =
                *(f32*)(pP + 0x18) +
                ((((a * c + b * d) * g + (-(b * b) - (c * c)) * e) +
                  (a * b - c * d) * f) * gQScale + e);
            *(u16*)((u8*)param_3 + 2) += 2;
            *(f32*)((u8*)param_3 + 8) =
                *(f32*)(pP + 0x1c) +
                ((((b * c - a * d) * g + (-(a * a) - (c * c)) * f) +
                  (a * b + c * d) * e) * gQScale + f);
            *(f32*)((u8*)param_3 + 0xc) = 0.0f;
            for (int i = 0; i < 9; i++)
                ((u32*)((u8*)param_3 + 0x14))[i] = ((u32*)mat)[i];
            return;
        }
        idx++;
        i20 += 0x2bc;
        pi23 = (i32*)((u8*)pi23 + 0x468);
    }

    for (int i = 0; i < 9; i++)
        ((u32*)((u8*)param_3 + 0x14))[i] = gEditorMat[i];
    *(f32*)((u8*)param_3 + 0x10) = gOne;
    *(u32*)((u8*)param_3 + 4) = gEditorVecA;
    *(u32*)((u8*)param_3 + 8) = gEditorVecB;
    *(u32*)((u8*)param_3 + 0xc) = gEditorVecC;
    *(u16*)((u8*)param_3 + 0) = 0;
    *(u16*)((u8*)param_3 + 2) = 0;
}

// @ 0x00e84470
void FUN_00e84470()
{
    void* mgr = FUN_0067de40();
    FUN_006ab760(((void* (__thiscall*)(void*))VT(mgr)[0x14 / 4])(mgr), (const u16*)L"fr-fr");
}

// @ 0x00e84490
i32 FUN_00e84490(u32 param_1, u32 param_2)
{
    void* local_8 = 0;
    void* local_4;

    MOPS(FUN_00675250())->FUN_006751a0(param_1, &local_8);

    if (local_8 != 0)
    {
        i32 result =
            (((u8 (__thiscall*)(void*, u32, void**))VT(local_8)[0x24 / 4])(local_8, param_2, &local_4) &&
             *(u16*)((u8*)local_4 + 0x12) == 10)
                ? *FUN_0041ea00()
                : (i32)(size_t)local_4;
        Release(local_8);
        return result;
    }
    return (i32)(size_t)local_4;
}

// @ 0x00e84510
u32 FUN_00e84510(u32* param_1)
{
    if (param_1[0] != 0)
    {
        u32 key[3];
        key[0] = param_1[0];
        key[1] = 0x30bdee3;
        key[2] = param_1[2];

        void* obj = 0;
        void* mgr = FUN_0067dcd0();
        if (obj) Release(obj);
        u8 ok = ((u8 (__thiscall*)(void*, u32*, void**, u32, u32, u32, u32))VT(mgr)[0x0c / 4])(
                    mgr, key, &obj, 0, 0, 0, 0);
        if (ok)
        {
            void* meta = obj
                ? ((void* (__thiscall*)(void*, u32))VT(obj)[0x0c / 4])(obj, 0x30bdee3)
                : 0;
            const u16* nm = (const u16*)MOPS(meta)->FUN_00414e10();
            const u16* e = nm;
            while (*e)
                ++e;
            MOPS(obj)->FUN_00423650(nm, e);
            Release(obj);
            return 1;
        }
        Release(obj);
    }
    return 0;
}

// @ 0x00e84600
void FUN_00e84600(u8 a1, i32 a2, u8 a3, u32* a4, f32 a5, u8 a6, void* a7, u32 a8, u32 a9)
{
    u32 payload;
    if (a1 != 0)
    {
        cEditorLaunch* d = (cEditorLaunch*)FUN_00f473a0(0x9c, "App", 0, 0, 0, 0);
        if (d)
        {
            MOPS(d)->FUN_005a9080();
            Release(d);
        }
        if (a3 != 0)
            d->mField20 = 1;
        d->mField0c = a2;
        d->mField10 = a4[0];
        d->mField14 = a4[1];
        d->mField18 = a4[2];
        *(u32*)((u8*)d + 0x90) = 0x1100000;
        d->mField60 = a5;
        FUN_005a9200(d);
        ((void (__thiscall*)(void*))VT(d)[0x08 / 4])(d);
        payload = 1000;
    }
    else if (a6 == 0)
    {
        cEditorLaunch* d = (cEditorLaunch*)FUN_00f473a0(0x9c, "App", 0, 0, 0, 0);
        if (d)
        {
            MOPS(d)->FUN_005a9080();
            Release(d);
        }
        if (a3 != 0)
            d->mField20 = 1;
        d->mField0c = a2;
        d->mField10 = a4[0];
        d->mField14 = a4[1];
        d->mField18 = a4[2];
        *(u32*)((u8*)d + 0x90) = 0x1100000;
        void* old = *(void**)((u8*)d + 0x94);
        if (a7 != old)
        {
            if (a7) ((void (__thiscall*)(void*))VT(a7)[0])(a7);
            *(void**)((u8*)d + 0x94) = a7;
            if (old) Release(old);
        }
        d->mField34 = 0;
        d->mField36 = 0;
        d->mField38 = 0;
        d->mField37 = 0;
        d->mField39 = 0;
        d->mField3c = 1;
        d->mField3d = 0;
        d->mField64 = 0;
        d->mField60 = a5;
        FUN_005a9200(d);
        ((void (__thiscall*)(void*))VT(d)[0x08 / 4])(d);
        payload = a9;
    }
    else
    {
        payload = a1;
    }

    void* ms = FUN_0067dcc0();
    cRegMessage* rm = (cRegMessage*)FUN_00f473a0(0x40, "App", 0, 0, 0, 0);
    if (rm)
    {
        rm->mField30 = 0;
        rm->mpVtbl = (void*)0x13eb90c;
        _InterlockedExchange((volatile long*)&rm->mField04, 0);
        rm->mpVtbl = (void*)0x13eb844;
        rm->mField38 = 0;
    }
    rm->mField30 = 0x90a03fdf;
    rm->mField08 = payload;
    rm->mField10 = 0;
    rm->mField18 = 1;
    ((void (__thiscall*)(void*, u32, void*, u32, u32))VT(ms)[0x18 / 4])(
        ms, rm->mField30, rm, 0, 0);
}

// @ 0x00e847f0
cString8* cString8::FUN_00e847f0(u32* src, u32* key)
{
    mpBegin = 0;
    mpEnd = 0;
    mpCap = 0;

    u8* begin = (u8*)src[0];
    u8* end = (u8*)src[1];
    u32 count = (u32)(end - begin);

    FUN_00475ab0(count + 1);

    u8* dst = mpBegin;
    FUN_011e0744(dst, begin, count);

    u8* p = dst + (end - begin);
    mpEnd = p;
    *p = 0;

    mKey0 = key[0];
    mKey1 = key[1];
    return this;
}

// @ 0x00e84850
cLayoutName* __thiscall cLayoutName::FUN_00e84850(tNameSource* pSource)
{
    mpBegin = 0;
    mpEnd = 0;
    mpCapacity = 0;
    int32_t length = (int32_t)(pSource->mpLast - pSource->mpFirst);
    RangeInitialize(length + 1);
    memcpy_(mpBegin, pSource->mpFirst, (unsigned int)length);
    mpEnd = mpBegin + length;
    *mpEnd = 0;
    mField10 = pSource->mField10;
    mField14 = pSource->mField14;
    return this;
}

// @ 0x00e848c0
void __cdecl FUN_00e848c0()
{
}

// @ 0x00e84940
void __cdecl DoNukeSubtree()
{
}

// @ 0x00e84a20
void __cdecl FUN_00e84a20()
{
}

// @ 0x00e84b20
void __cdecl FUN_00e84b20()
{
}

// @ 0x00e84bf0
void __cdecl FUN_00e84bf0()
{
}

// @ 0x00e84c80
void __cdecl FUN_00e84c80()
{
}

// @ 0x00e84d90
void __cdecl FUN_00e84d90()
{
}

// @ 0x00e84e40
void __cdecl FUN_00e84e40()
{
}

// @ 0x00e84f30
void __cdecl GetPollinatedCell()
{
}
