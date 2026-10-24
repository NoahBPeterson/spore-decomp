// Slice s00e829c0 -- editor/UI helper thunks: world visibility toggles, asset-variant update
// fan-out, achievement-controller forwards, layout key accessors and a handful of small view
// predicates.
//
// Most of these are one-line forwards into SPUIHelpers / Achievements::Controller / the layout
// manager, so they are modelled as thin wrappers around those singletons.
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast
#include "types.h"

#pragma warning(disable : 4100)

namespace SP {

// ---------------------------------------------------------------------------------------------
// cSPUILayoutManager -- world visibility of a named UI world
// ---------------------------------------------------------------------------------------------
class cSPUILayoutManager {
public:
    bool IsWorldVisible(uint32_t worldId);              // 0x00810760
    void SetWorldVisible(uint32_t worldId, bool visible); // 0x00810660
    void DoLayout(uint32_t worldId, bool visible);      // 0x0080...
};

cSPUILayoutManager* __cdecl GetLayoutManager();         // 0x00805070

// ---------------------------------------------------------------------------------------------
// editor asset / variant plumbing
// ---------------------------------------------------------------------------------------------
void* __cdecl FUN_0067cb30(uint32_t variantId, void* pAsset, int32_t low, int32_t high);

// Editor variant context lookup: returns the variant context bound to an asset (optionally for a
// sub-selection index).
void* __cdecl FUN_0067cac0(void* pAsset, ...);

struct cAssetVariantUpdater {
    void UpdateAssetVariant(uint32_t variantId, void* pAsset, int32_t low, int32_t high);
    void UpdateVariantForAsset();
    void ClearVariant();
    void SetVariantFlag(int value);
};

// ---------------------------------------------------------------------------------------------
// layout authoring helpers
// ---------------------------------------------------------------------------------------------
struct cVec3 {
    float mX;                                           // +0x00
    float mY;                                           // +0x04
    float mZ;                                           // +0x08
};

struct cLayoutNode {
    uint8_t  pad00[0x18];
    cVec3    mPosition;                                 // +0x18
};

struct cLayoutEntry {
    uint8_t  pad00[0x04];
    uint32_t mId;                                       // +0x04
    float    mValue;                                    // +0x08
    uint8_t  pad0c[8];                                  // +0x0c
    float    mWeight;                                   // +0x14 (entry end)
};

struct cLayoutEntryList {
    uint8_t  pad00[0xa0];
    int32_t  mCount;                                    // +0xa0
    uint8_t  padA4[4];                                  // +0xa4 -- first entry body starts here
};

struct cLayoutData {
    uint8_t  pad00[0x18];
    cVec3    mPosition;                                 // +0x18
    uint8_t  pad24[0x2c0];
    void*    mpEntries;                                 // +0x2e4 -> cLayoutEntryList
};

struct cLayoutOwner {
    uint8_t     pad000[0x17c];
    cLayoutData* mpLayout;                              // +0x17c
};

// Pushes a placement (position + offset + scale) for one layout key into the editor's scene.
void* __cdecl FUN_0067caf0(cVec3 key, int a, int worldId, cVec3 offset, int c, int d);

struct cLayoutPlacement {
    void Commit();                                      // 0x0067aaf0
};

// ---------------------------------------------------------------------------------------------
// achievements
// ---------------------------------------------------------------------------------------------
namespace Achievements {
class Controller {
public:
    void AwardAchievement(uint32_t id);                 // 0x00676710
    void DecrementAccumulatorValue();                   // 0x00676f20
    void SetAchievementProgress(uint32_t a, uint32_t b, uint32_t c);
    void Flush();
    void Flush(uint32_t a, uint32_t b, uint32_t c);     // 0x00676ed0
};
Controller* __cdecl GetController();                    // 0x00675250
Controller* __cdecl GetController(uint32_t a, uint32_t b, uint32_t c);
} // namespace Achievements

// ---------------------------------------------------------------------------------------------
// misc singletons
// ---------------------------------------------------------------------------------------------
struct cSettingsSection {
    uint8_t pad00[0x1c];
    uint8_t mbEnabled;                                  // +0x1c
};
cSettingsSection* __cdecl AssetBrowserSettings();       // 0x00401030
cSettingsSection* __cdecl SporeGuideSettings();         // 0x00401040

struct cSimulator {
    void* mState;                                       // +0x00
};
void* __cdecl FUN_00b3d340();                           // 0x00b3d340
void* __cdecl FUN_00b3d4f0();                           // 0x00b3d4f0

struct cController {
    virtual void c00(); virtual void c04(); virtual void c08(); virtual void c0c();
    virtual void c10(); virtual void c14(); virtual void c18(); virtual void c1c();
    virtual void c20(); virtual void c24(); virtual void c28(); virtual void c2c();
    virtual void c30(); virtual void c34();
    virtual void SetFloatProperty(uint32_t id);         // +0x38 (index 14)
};
cController* __cdecl FUN_00b3d340Controller();          // alias of FUN_00b3d340

// UI world / cursor manager used by the fade helper
struct cWorldManager {
    virtual void w00(); virtual void w04(); virtual void w08(); virtual void w0c();
    virtual void w10(); virtual void w14(); virtual void w18();
    virtual void RefreshScene();                        // +0x1c
};
cWorldManager* __cdecl FUN_00b3d340World();              // 0x00b3d340

struct cGameModeSwitcher {
    virtual void g00(); virtual void g04(); virtual void g08(); virtual void g0c();
    virtual void g10(); virtual void g14(); virtual void g18(); virtual void g1c();
    virtual void g20(); virtual void g24(); virtual void g28(); virtual void g2c();
    virtual void g30(); virtual void g34();
    virtual void SetMode(uint32_t mode);                // +0x38
};

// ---------------------------------------------------------------------------------------------
// layout keys (id/group/name triples) shared by the small accessors
// ---------------------------------------------------------------------------------------------
struct tLayoutKey {
    uint32_t mId;                                       // +0x00
    uint32_t mGroup;                                    // +0x04
    uint32_t mName;                                     // +0x08
    uint32_t mExtra;                                    // +0x0c
};

struct cEditorState {
    uint32_t mMode;                                     // +0x0c
    tLayoutKey mPosition;                               // +0x18 (x/y/z)
    uint32_t mTarget;                                   // +0x34
    uint8_t  mbFlag;                                    // +0x44
};

struct cEditorWorld {
    uint32_t mMode;                                     // +0x00
    uint8_t  pad04[0x0c];
    uint8_t  mbVisible;                                 // +0x10
};

} // namespace SP

using namespace SP;

namespace SP {

// ---------------------------------------------------------------------------------------------
// @ 0xe829c0 FUN_00e829c0
// ---------------------------------------------------------------------------------------------
void __cdecl FUN_00e829c0(uint32_t worldId, bool visible)
{
    cSPUILayoutManager* pManager = GetLayoutManager();
    while (pManager->IsWorldVisible(worldId) == !visible)
        pManager->SetWorldVisible(worldId, visible);
}

// ---------------------------------------------------------------------------------------------
// @ 0xe82a10 FUN_00e82a10
// ---------------------------------------------------------------------------------------------
void __cdecl FUN_00e82a10(uint32_t worldId, bool visible)
{
    cSPUILayoutManager* pManager = GetLayoutManager();
    if (pManager->IsWorldVisible(worldId) != visible)
        pManager->SetWorldVisible(worldId, visible);
}

// ---------------------------------------------------------------------------------------------
// @ 0xe82be0 FUN_00e82be0
// ---------------------------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------------------------
// @ 0xe82c10 FUN_00e82c10
// ---------------------------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------------------------
// @ 0xe82c70 FUN_00e82c70
// ---------------------------------------------------------------------------------------------
void __cdecl FUN_00e82c70()
{
    ((cWorldManager*)FUN_00b3d340())->RefreshScene();
}

// ---------------------------------------------------------------------------------------------
// @ 0xe82c80 FUN_00e82c80
// ---------------------------------------------------------------------------------------------
void __cdecl FUN_00e82c80(cEditorState* pState, uint32_t* pMode, uint8_t* pFlag,
                          uint32_t* pTarget, tLayoutKey* pPosition)
{
    *pMode = pState->mMode;
    *pFlag = pState->mbFlag;
    *pTarget = pState->mTarget;
    pPosition->mId = pState->mPosition.mId;
    pPosition->mGroup = pState->mPosition.mGroup;
    pPosition->mName = pState->mPosition.mName;
}

// ---------------------------------------------------------------------------------------------
// @ 0xe82cc0 FUN_00e82cc0
// ---------------------------------------------------------------------------------------------
uint8_t __cdecl FUN_00e82cc0()
{
    return AssetBrowserSettings()->mbEnabled;
}

// ---------------------------------------------------------------------------------------------
// @ 0xe82cd0 FUN_00e82cd0
// ---------------------------------------------------------------------------------------------
uint8_t __cdecl FUN_00e82cd0()
{
    return SporeGuideSettings()->mbEnabled;
}

// ---------------------------------------------------------------------------------------------
// @ 0xe82cf0 FUN_00e82cf0
// ---------------------------------------------------------------------------------------------
void __cdecl FUN_00e82cf0(uint32_t a, uint32_t b, uint32_t c)
{
    Achievements::GetController(a, b, c)->Flush(a, b, c);
}

// ---------------------------------------------------------------------------------------------
// @ 0xe82d10 FUN_00e82d10
// ---------------------------------------------------------------------------------------------
void __cdecl FUN_00e82d10(uint32_t achievementId)
{
    Achievements::GetController()->AwardAchievement(achievementId);
}

// ---------------------------------------------------------------------------------------------
// @ 0xe82d30 FUN_00e82d30
// ---------------------------------------------------------------------------------------------
void __cdecl FUN_00e82d30()
{
    Achievements::GetController()->DecrementAccumulatorValue();
}

// ---------------------------------------------------------------------------------------------
// @ 0xe82d40 FUN_00e82d40
// ---------------------------------------------------------------------------------------------
void __cdecl FUN_00e82d40()
{
    cAssetVariantUpdater* pUpdater = (cAssetVariantUpdater*)FUN_0067cb30(0, 0, 0, 0);
    pUpdater->SetVariantFlag(0);
}

// ---------------------------------------------------------------------------------------------
// @ 0xe82d50 FUN_00e82d50
// ---------------------------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------------------------
// @ 0xe82dc0 FUN_00e82dc0
// ---------------------------------------------------------------------------------------------
void __cdecl FUN_00e82dc0(uint32_t value)
{
    cController* pController = (cController*)FUN_00b3d4f0();
    pController->SetFloatProperty(value);
}

// ---------------------------------------------------------------------------------------------
// @ 0xe82de0 FUN_00e82de0
// ---------------------------------------------------------------------------------------------
void __cdecl FUN_00e82de0(uint32_t a, uint32_t b)
{
    cController* pController = (cController*)FUN_00b3d4f0();
    pController->SetFloatProperty(a);
}

// ---------------------------------------------------------------------------------------------
// @ 0xe82e00 FUN_00e82e00
// ---------------------------------------------------------------------------------------------
void __cdecl FUN_00e82e00(cEditorState* pState, cEditorState* pOther, int mode)
{
    if (!pState || !pOther)
        return;
    pState->mMode = (uint32_t)mode;
    pState->mPosition.mId = pOther->mPosition.mId;
    pState->mPosition.mGroup = pOther->mPosition.mGroup;
    pState->mPosition.mName = pOther->mPosition.mName;
}

// ---------------------------------------------------------------------------------------------
// @ 0xe83040 FUN_00e83040
// ---------------------------------------------------------------------------------------------
void __cdecl FUN_00e83040(cEditorState* pState, int mode)
{
    if (!pState)
        return;
    pState->mMode = (uint32_t)mode;
    pState->mbFlag = mode != 0;
}

// ---------------------------------------------------------------------------------------------
// @ 0xe831a0 FUN_00e831a0
// ---------------------------------------------------------------------------------------------
void __cdecl FUN_00e831a0(tLayoutKey* pKey, uint32_t id, uint32_t group)
{
    pKey->mId = id;
    pKey->mGroup = group;
    pKey->mName = 0;
}

// ---------------------------------------------------------------------------------------------
// @ 0xe831d0 FUN_00e831d0
// ---------------------------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------------------------
// @ 0xe83350 FUN_00e83350
// ---------------------------------------------------------------------------------------------
void __cdecl FUN_00e83350(cVec3* pOut, cLayoutOwner* pOwner)
{
    cLayoutData* pLayout = pOwner->mpLayout;
    *pOut = pLayout->mPosition;
}

// ---------------------------------------------------------------------------------------------
// @ 0xe83380 FUN_00e83380
// ---------------------------------------------------------------------------------------------
uint32_t __cdecl FUN_00e83380(cEditorWorld* pWorld, int mode, float* pOut)
{
    if (!pWorld)
        return 0;
    *pOut = (float)mode;
    return pWorld->mbVisible;
}

// ---------------------------------------------------------------------------------------------
// @ 0xe833f0 FUN_00e833f0
// ---------------------------------------------------------------------------------------------
void __cdecl FUN_00e833f0(uint32_t a, uint32_t b, uint32_t c)
{
    cSPUILayoutManager* pManager = GetLayoutManager();
    pManager->DoLayout(a, b != 0);
    pManager->DoLayout(c, b != 0);
}

// ---------------------------------------------------------------------------------------------
// @ 0xe83430 FUN_00e83430
// ---------------------------------------------------------------------------------------------
int __cdecl FUN_00e83430(cEditorWorld* pWorld)
{
    if (!pWorld)
        return 0;
    return pWorld->mbVisible ? 1 : 0;
}

// ---------------------------------------------------------------------------------------------
// @ 0xe83470 FUN_00e83470
// ---------------------------------------------------------------------------------------------
int __cdecl FUN_00e83470(cEditorWorld* pWorld, int mode)
{
    if (!pWorld || !pWorld->mbVisible)
        return 0;
    return (int)pWorld->mMode == mode;
}

// ---------------------------------------------------------------------------------------------
// @ 0xe834d0 FUN_00e834d0
// ---------------------------------------------------------------------------------------------
void __cdecl FUN_00e834d0(cEditorState* pState, int mode, int flag)
{
    if (!pState)
        return;
    pState->mMode = (uint32_t)mode;
    pState->mTarget = (uint32_t)flag;
}

// ---------------------------------------------------------------------------------------------
// @ 0xe83590 FUN_00e83590
// ---------------------------------------------------------------------------------------------
void __cdecl FUN_00e83590(cEditorState* pState)
{
    if (!pState)
        return;
    pState->mPosition.mId = 0;
    pState->mPosition.mGroup = 0;
    pState->mPosition.mName = 0;
    pState->mbFlag = 0;
}

// ---------------------------------------------------------------------------------------------
// @ 0xe83640 FUN_00e83640
// ---------------------------------------------------------------------------------------------
void __cdecl FUN_00e83640(cEditorState* pState, uint32_t value)
{
    if (!pState)
        return;
    pState->mTarget = value;
}

// ---------------------------------------------------------------------------------------------
// @ 0xe836f0 FUN_00e836f0
// ---------------------------------------------------------------------------------------------
void __cdecl FUN_00e836f0()
{
    cSPUILayoutManager* pManager = GetLayoutManager();
    pManager->SetWorldVisible(0, true);
}

// ---------------------------------------------------------------------------------------------
// @ 0xe837c0 FUN_00e837c0
// ---------------------------------------------------------------------------------------------
float __cdecl FUN_00e837c0()
{
    cEditorWorld* pWorld = (cEditorWorld*)FUN_00b3d340();
    if (!pWorld)
        return 0.0f;
    return pWorld->mbVisible ? 1.0f : 0.0f;
}

} // namespace SP
