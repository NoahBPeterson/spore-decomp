// slice s0058cee0 -- SP::cAppModeEditorBase::LoadModel / NewModel (editor model load path).
// Module flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast (no /EHsc: the release helper is a plain
// inline destructor sequence, retail emits no unwind funclets).
#include "types.h"

// ---------------------------------------------------------------------------
// value types
// ---------------------------------------------------------------------------
struct Rect16 { uint32_t d[4]; };
struct Bits128 { uint32_t w[4]; };
struct ResourceKey { uint32_t instanceID, typeID, groupID, pad; };
struct Vector3 { float x, y, z; };

// ---------------------------------------------------------------------------
// out-of-line helpers (all named from the image, addresses verified by the calls)
// ---------------------------------------------------------------------------
bool __cdecl GetLoadRect(const ResourceKey* key, int* handle, Rect16* rect);   // 0x004badd0
bool __cdecl IntersectsRects(Rect16 loaded, Rect16 requested);                 // 0x004f3d60
void __stdcall HandleRects(Rect16 a, Rect16 b);                                // 0x005721b0
int  __cdecl GetModelCreatorKind(const ResourceKey* key);                      // 0x00552300
void __cdecl RecordEvent4(uint32_t a, uint32_t b, float c, uint32_t d);        // 0x00435f40
float __cdecl CalculateModelSize(void* model);                                 // 0x0048ca10
int   __cdecl CountModelParts(void* model);                                    // 0x0048cc20
void  __cdecl ApplySkinPaintThemeToModel(void* model, void* palette);          // 0x004b76c0

// The load handle released at every exit: {unk, ref-counted block}, where the count reaching zero
// re-arms it and dispatches slot 0 of the block at +4 (retail's release sequence).
struct cRefCounted { void** mpVtbl; int mnCount; };
struct cLoadRef { uint32_t mUnk0; cRefCounted mValue; };

inline void ReleaseLoad(int* handle)
{
    cLoadRef* ref = (cLoadRef*)handle;
    if (ref != 0 && --ref->mValue.mnCount == 0) {
        ref->mValue.mnCount = 1;
        ((void (__thiscall*)(cRefCounted*, int))ref->mValue.mpVtbl[0])(&ref->mValue, 1);
    }
}

// ---------------------------------------------------------------------------
// classes reached through the editor's accessors
// ---------------------------------------------------------------------------
#define VSLOT(n) virtual void n();

class cCameraList;
class cCamera;
class cPropertyList;

class cCameraManager {
public:
    VSLOT(v00) VSLOT(v04) VSLOT(v08) VSLOT(v0c) VSLOT(v10) VSLOT(v14) VSLOT(v18) VSLOT(v1c)
    VSLOT(v20) VSLOT(v24) VSLOT(v28) VSLOT(v2c) VSLOT(v30) VSLOT(v34)
    virtual cCameraList* GetCameras();                       // +0x38
};

class cIApp {
public:
    VSLOT(v00) VSLOT(v04) VSLOT(v08) VSLOT(v0c) VSLOT(v10) VSLOT(v14) VSLOT(v18) VSLOT(v1c)
    VSLOT(v20) VSLOT(v24) VSLOT(v28) VSLOT(v2c) VSLOT(v30) VSLOT(v34) VSLOT(v38) VSLOT(v3c)
    VSLOT(v40) VSLOT(v44) VSLOT(v48) VSLOT(v4c)
    virtual cCameraManager* GetCameraManager();              // +0x50
};

class cCameraList {
public:
    VSLOT(v00) VSLOT(v04) VSLOT(v08)
    virtual cCamera* GetCamera(uint32_t id);                 // +0x0c
};

class cCamera {
public:
    VSLOT(v00) VSLOT(v04) VSLOT(v08) VSLOT(v0c) VSLOT(v10) VSLOT(v14) VSLOT(v18) VSLOT(v1c)
    VSLOT(v20) VSLOT(v24) VSLOT(v28) VSLOT(v2c) VSLOT(v30) VSLOT(v34) VSLOT(v38) VSLOT(v3c)
    VSLOT(v40) VSLOT(v44) VSLOT(v48) VSLOT(v4c)
    virtual void RefreshTerrainBinding();                    // +0x50
    void UpdatePitch();                                      // 0x005a22d0
};

class cPropertyList {
public:
    VSLOT(v00) VSLOT(v04) VSLOT(v08) VSLOT(v0c) VSLOT(v10) VSLOT(v14) VSLOT(v18)
    virtual bool HasProperty(uint32_t propertyID);           // +0x1c
};

class cSPEditorUI {
public:
    void UpdateUIBasedOnModelSaveability();                  // 0x005dd7a0
};

class cSPEditorModel {
public:
    VSLOT(v00)
    virtual void* GetEditorObject();                         // +0x04
};

class cSPEditorSkinManager {
public:
    void* GetSkinPart(int identifier);                       // 0x004c49e0
};

class cSPEditorPaintTheme {
public:
    bool ReadFromProp(uint32_t propertyID);                  // 0x004b2bb0
};

// wrapper held at cAppModeEditorBase::+0x29c; the paint-theme id sits at +0x144
class cPaintThemeHolder {
public:
    char pad00[0x144];
    uint32_t mPaintThemeID;                                  // +0x144
};

// the pending-download queue at 0x015fd928: an intrusive list whose sentinel node lives at +0x70
struct cListNode { cListNode* mpNext; cListNode* mpPrev; };
class cPendingDownloads {
public:
    char pad00[0x70];
    cListNode mQueue;                                        // +0x70 (sentinel when empty)
};

// main-window access: WindowManager() returns an object whose slot 1 hands out the window's
// base sub-object, which sits at +4 inside cSPUIMainWin (hence the -4 adjustment).
class cWindowOther { public: VSLOT(o0) };
class cWindowBase {
public:
    VSLOT(b0)
    virtual cWindowBase* GetSelf();                          // +0x04
};
class cSPUIMainWin : public cWindowOther, public cWindowBase {
public:
    uint64_t GetMouseRefs();                                 // 0x008130a0
};
class cWindowManager {
public:
    VSLOT(v00)
    virtual cWindowBase* GetMainWindow();                    // +0x04
};
cWindowManager* WindowManager();                             // 0x0067caa0

extern cPendingDownloads* g_pPendingDownloads;               // 0x015fd928

// ---------------------------------------------------------------------------
// SP::cAppModeEditorBase -- only the members these two functions touch are named; the gaps are
// padding at the offsets the disassembly uses (the retail layout differs from the 2008 PDB).
// ---------------------------------------------------------------------------
namespace SP {

class cAppModeEditorBase {
public:
    char pad00[0x20];
    cIApp* mApp;                                             // +0x20
    cPropertyList* mpPropList;                               // +0x24
    char pad28[0x48 - 0x28];
    Bits128 mPartMask;                                       // +0x48
    char pad58[0x78 - 0x58];
    cSPEditorUI* mpEditorUI;                                 // +0x78
    char pad7c[0x98 - 0x7c];
    cSPEditorModel* mpEditorModel;                           // +0x98
    char pad9c[0x150 - 0x9c];
    cSPEditorSkinManager* mSkinManager;                      // +0x150
    char pad154[0x178 - 0x154];
    void** mField178;                                        // +0x178 (element count/source at -4)
    char pad17c[0x1cc - 0x17c];
    int mLaunchKeyType;                                      // +0x1cc
    Vector3 mParentModelKey;                                 // +0x1d0
    char pad1dc[0x20e - 0x1dc];
    uint8_t mbReportStats;                                   // +0x20e
    char pad20f[0x29c - 0x20f];
    cPaintThemeHolder* mpPaintThemeHolder;                   // +0x29c
    cSPEditorPaintTheme* mpPaintTheme;                       // +0x2a0
    char pad2a4[0x310 - 0x2a4];
    uint8_t mbKeepModelKey;                                  // +0x310
    char pad311[0x3c0 - 0x311];
    void* mField3c0;                                         // +0x3c0
    char pad3c4[0x440 - 0x3c4];
    uint64_t mModelStartTime;                                // +0x440
    char pad448[0x4b0 - 0x448];
    uint8_t mbLoaded;                                        // +0x4b0
    uint8_t mbLoadFlagB1;                                    // +0x4b1
    uint8_t mbLoadFlagB2;                                    // +0x4b2
    uint8_t mbLoadFlagB3;                                    // +0x4b3
    uint8_t mbLoadFlagB4;                                    // +0x4b4

    // inlined copy of 0x00574590 GetCurrentCameraContext
    cCamera* GetCameraContext()
    {
        cCameraList* cams = mApp->GetCameraManager()->GetCameras();
        if (cams != 0)
            return cams->GetCamera(0x29da727);
        return 0;
    }

    int LoadModel(const ResourceKey* key, Rect16 rect, bool asTemplate);   // 0x0058cee0
    void NewModel(bool randomBackground);                                  // 0x0058d1c0

    void LoadModelInternal(int handle);                                    // 0x0058a1e0
    void RefreshEditor();                                                  // 0x00584070
    void RefreshAfterLoad();                                               // 0x00582d00
    void ResetEconomy();                                                   // 0x005754c0
    void InitializeUndoList();                                             // 0x00586690
    void PrepareAppForNewModel(void* model);                               // 0x00586b00
    Bits128* BuildPartMask(Bits128* out, void* a, void* b, int c);         // 0x0057ac00
    ResourceKey GetNextBackground();                                       // 0x00574990
    ResourceKey GetRandomBackground();                                     // 0x00574900
};

}  // namespace SP

using namespace SP;

// @ 0x0058cee0
int cAppModeEditorBase::LoadModel(const ResourceKey* key, Rect16 rect, bool asTemplate)
{
    int handle = 0;
    Rect16 loaded = { 0, 0, 0, 0 };
    if (!GetLoadRect(key, &handle, &loaded)) {
        Rect16 failRect = { 0x4000000, 0, 0, 0 };
        HandleRects(failRect, failRect);
        ReleaseLoad(&handle);
        return 0;
    }
    if (!IntersectsRects(loaded, rect)) {
        Rect16 failRect = { 0x4000000, 0, 0, 0 };
        HandleRects(failRect, failRect);
        ReleaseLoad(&handle);
        return 0;
    }

    mbLoadFlagB1 = 0;
    mbLoadFlagB2 = 1;
    mbLoaded = (GetModelCreatorKind(key) == 1);
    LoadModelInternal(handle);

    if (asTemplate) {
        if (mbKeepModelKey)
            mParentModelKey = *(const Vector3*)key;
        else
            mParentModelKey = Vector3();
        mModelStartTime = ((cSPUIMainWin*)WindowManager()->GetMainWindow())->GetMouseRefs();
    }

    GetCameraContext()->RefreshTerrainBinding();
    GetCameraContext()->UpdatePitch();
    RefreshEditor();
    ReleaseLoad(&handle);
    return 1;
}

// @ 0x0058d1c0
void cAppModeEditorBase::NewModel(bool randomBackground)
{
    GetCameraContext()->RefreshTerrainBinding();
    GetCameraContext()->UpdatePitch();
    ResetEconomy();

    if (mpPropList != 0 && mpPropList->HasProperty(0x503d2f60)) {
        ResourceKey key;
        if (randomBackground == 0)
            key = GetNextBackground();
        else
            key = GetRandomBackground();
        Rect16 noRect = { 0, 0, 0, 0 };
        LoadModel(&key, noRect, false);
        mbLoadFlagB1 = 1;
        if (mSkinManager != 0 && mSkinManager->GetSkinPart(1) != 0 &&
            (g_pPendingDownloads == 0 ||
             g_pPendingDownloads->mQueue.mpNext == &g_pPendingDownloads->mQueue))
            ApplySkinPaintThemeToModel(mpEditorModel, mField3c0);
        InitializeUndoList();
        Bits128 mask;
        mPartMask = *BuildPartMask(&mask, mField178[-1], mpEditorModel->GetEditorObject(), 1);
        mpEditorUI->UpdateUIBasedOnModelSaveability();
    }
    else {
        mbLoadFlagB1 = 1;
        PrepareAppForNewModel(0);
        InitializeUndoList();
        if (mpPaintThemeHolder != 0) {
            uint32_t propertyID = mpPaintThemeHolder->mPaintThemeID;
            if (propertyID != 0)
                mpPaintTheme->ReadFromProp(propertyID);
        }
    }

    mbLoaded = 0;
    RefreshAfterLoad();
    mbLoadFlagB3 = 0;
    mbLoadFlagB4 = 0;
    mpEditorUI->UpdateUIBasedOnModelSaveability();
    mParentModelKey = Vector3();
    mModelStartTime = ((cSPUIMainWin*)WindowManager()->GetMainWindow())->GetMouseRefs();

    if (mbReportStats) {
        float size = CalculateModelSize(mpEditorModel);
        RecordEvent4(0x1d6253c0, 0xdef22b96, size, 0);
        if (mbReportStats) {
            int parts = CountModelParts(mpEditorModel);
            RecordEvent4(0x1d6253c0, 0x5ee38119, (float)parts, 0);
        }
    }
}
