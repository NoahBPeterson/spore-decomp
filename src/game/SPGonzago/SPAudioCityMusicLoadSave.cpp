// src/game/SPGonzago/SPAudioCityMusicLoadSave.cpp -- migrated from slice(s) s00ea28f0, s00ea1900 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPAudioCityMusicLoadSave.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPUILayout.h"
#include <stddef.h>

// unnamed retail callees and globals (address in the comment)
extern const wchar_t kSaveDialogLayoutKey[];
extern const wchar_t kThumbnailLayoutKey[];

// ---- items of slice s00ea1900 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef int intptr_t;
#define nullptr 0
struct Vec2 {
    float mX;
    float mY;
};
class IRefCounted {
public:
    virtual void AddRef();                      // 0x00
    virtual void Release();                     // 0x04
    virtual void v08();
    virtual void* Query(const void* pType);     // 0x0c
    virtual void v10();
};
class IWinProc {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void ProcessMessage(void* pMessage);    // 0x10
    virtual void v14();
};
class IWindow : public IRefCounted {
public:
    virtual void v14();
    virtual void v18();
    virtual void SetVisible(bool bVisible);
    virtual void v20();
    virtual void v24();
    virtual void v28(int a);
    virtual void v2c();
    virtual void* GetArea();
    virtual void SetFont(void* pFont);
    virtual void SetText(const wchar_t* pText);
};
class cSPUILayout_s00ea_1900 : public IRefCounted {
public:
    bool Init(const void* pKey, int a, uint32_t flags);  // 0x008120d0 (cSPUILayout::Init)
    IWindow* FindWindowByID(uint32_t nId, int bFind);  // 0x008105b0 (cSPUILayout::FindWindowByID)
    IWindow* FindWindowByID(uint32_t nId);  // 0x008105b0 (cSPUILayout::FindWindowByID)
    void SetParentWin(IWindow* pParent, int a, uint32_t flags);  // 0x008121b0 (cSPUILayout::SetParentWin)
    void SetReloadCallback(void* pCallback, void* pOwner);  // 0x00810090 (cSPUILayout::SetReloadCallback)
    void SetVisibility(bool bVisible);  // 0x00810590 (cSPUILayout::SetVisibility)
    void Shutdown(int bDelete);  // 0x00811ad0 (cSPUILayout::Shutdown)
};
class cPlayerCityMusic : public IRefCounted {
public:
    virtual void v14();
    void Play(bool bPlay);
    bool LoadData(void* pData);
    void PlayMelody(int a);
    void SaveData(void* pWriter);
};
class cCityMusicViewer : public IRefCounted {
public:
    bool Init(cSPUILayout_s00ea_1900* pLayout);
    void SetMusic(cPlayerCityMusic* pMusic);
    void Shutdown();
};
class cAssetMetadata : public IRefCounted {
public:
    cAssetMetadata();
};
class cMessageServer {
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
    virtual void RegisterHandler(void* pHandler, uint32_t nMessage);
    virtual void UnregisterHandler(void* pHandler, uint32_t nMessage, int nFlags);
};
class cCityMusicLoadSave : public IWinProc {
public:
    cCityMusicLoadSave();
    void Load();
    void StartDialog(IWindow* pDialog);
    void StopDialog(IWindow* pDialog);
    void Init();
    void SetMusic(cPlayerCityMusic* pMusic);
    void SaveThumbnail();
    void FinishSave();
    bool DoMessage(void* pMessage, int* pData);
    void Shutdown();
    bool LoadKey(int a, int b, int nKey);
    uint32_t QueryKey(uint32_t nValue, int nKey);

    uint8_t mPad10[0x10];                   // 0x10
    cSPUILayout_s00ea_1900* mpThumbnailLayout;         // 0x20
    cPlayerCityMusic* mpMusic;              // 0x24
    cSPUILayout_s00ea_1900* mpSaveDialogLayout;        // 0x28
    cCityMusicViewer* mpViewer;             // 0x2c
    uint8_t mbWaitingForSaveDialog;         // 0x31
    uint8_t mbWaitingForThumbnail;          // 0x32
    uint8_t mPad33[0x09];                   // 0x33
    uint32_t mPageID;                       // 0x3c
    uint32_t mAllocID;                      // 0x40
};
void* operator_new(size_t nSize, const char* pName, int a, int b, int c, int d);
void* operator_new(size_t nSize, const char* pName, int a);
cMessageServer* MessageServer();
void* CenterWindowInRect(void* pLayout, void* pArea);
void* GetResourceManager();
void LaunchAssetBrowser(uint32_t id, void* pCallback, void* pProc);
void BeginModal(IWindow* pWindow, int a, int b);
void EndModal(IWindow* pWindow, int a, int b);
void ResetMusicViewer();
void* GetSaveArea();
void RefreshMusicDialog();
void RefreshMusicThumbnail();
void* GetThumbnailManager();
void* GetMusicObjectDB();
void* GetLayoutManager();
void SaveThumbnailToDisk(cPlayerCityMusic* pMusic, void* pMetadata);
void DownloadThumbnail(void* pData);
void AwardAutoTest(uint32_t nId, int a);
void* ControllerFind(uint32_t nId, int a);
void ResetAssetBrowser();
void* RTTManager();
void SetViewerMusic(cCityMusicViewer* pViewer, cPlayerCityMusic* pMusic);
cCityMusicViewer* CreateCityMusicViewer(void* pMemory);
cAssetMetadata* CreateAssetMetadata(void* pMemory);
void ResetMusicThumbnailState();
void* GetResourceData(void* pObject);
extern uint32_t gSaveDialogKey;
extern const wchar_t kSaveDialogLayoutKey[];
extern const wchar_t kThumbnailLayoutKey[];
// ---- items of slice s00ea1900 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern uint32_t gSaveDialogKey;

// ---- items of slice s00ea28f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void** vtbl_UI_BehaviorMessage;   // 0x013eb90c
extern void** vtbl_Behavior;             // 0x01452a38
extern void* vtbl_LoadSave_00[];         // 0x01487280
extern void* vtbl_LoadSave_08[];         // 0x0148727c
extern void* vtbl_LoadSave_0c[];         // 0x01487260
extern void* vtbl_LoadSave_10[];         // 0x01487258
extern void* vtbl_PaintSystem[];         // 0x013eb394
extern void* vtbl_ITracerBase[];         // 0x013eb938
extern void* vtbl_ContentValidation[];   // 0x013ec458
typedef unsigned char  u8;
typedef unsigned int   u32;
typedef int            s32;
static inline void** VTP(void* p) { return *(void***)p; }
void* __cdecl operator new(unsigned int size);
void* __cdecl FUN_0067dda0();            // UI manager
void* __cdecl FUN_0067dd50();            // window manager
void* __cdecl cSPUITooltipPanel_ctor(void* mem, u32 a, void* layout, u32 b, u32 c, u32 d); // 0x00e36150
struct cSPUILayout_s00ea_28f0;
struct LoadSaveKey {                     // 12-byte resource key
    u32 mType_00;
    u32 mGroup_04;
    u32 mName_08;
};
struct KeyVec {
    LoadSaveKey* mpBegin_00;
    LoadSaveKey* mpEnd_04;
    LoadSaveKey* mpCap_08;
};
struct LoadSaveMsg {
    KeyVec* mpKeys_00;                   // +0x00 key list (for the load-key message)
    u32     mPad_04;
    void*   mpSender_08;                 // +0x08 window that sent the message
};
struct cSPUILayout_s00ea_28f0 {
    void** mpVtbl_00;
    void SetVisibility(bool visible);                              // 0x00810590
    cSPUILayout_s00ea_28f0* FindWindowByID(u32 id, s32 flag);                 // 0x008105b0
    bool SetParentWin(cSPUILayout_s00ea_28f0* parent, bool flag, u32 name);   // 0x008121b0
};
struct cCityMusicViewer_s00ea_28f0 {
    u8   mPad_00[0x04];
    void Redraw();                                                 // 0x00ea4610
};
struct cCityMusicLoadSave_s00ea_28f0 {
    void** mpVtbl_00;                    // +0x00
    u32    mField_04;                    // +0x04
    void** mpVtbl_08;                    // +0x08
    void** mpVtbl_0c;                    // +0x0c
    void** mpVtbl_10;                    // +0x10
    void*  mpField_14;                   // +0x14  IRefCounted (release at vtable+4)
    void*  mpViewer_18;                  // +0x18  viewer (IRefCounted subobject at +4)
    cSPUILayout_s00ea_28f0* mpLayout_1c;            // +0x1c  thumbnail layout
    cSPUILayout_s00ea_28f0* mpLayout_20;            // +0x20  save-dialog layout
    u8     mFlag_24;                     // +0x24
    u8     mFlag_25;                     // +0x25  waiting for save dialog
    u8     mFlag_26;                     // +0x26  waiting for thumbnail
    u8     mPad_27;
    void*  mpWindow_28;                  // +0x28
    u32    mField_2c;                    // +0x2c
    u32    mField_30;                    // +0x30
    u8     mPad_34[0x0c];

    void Shutdown();                                    // 0x00ea26f0
    bool LoadKey(LoadSaveKey key);                      // 0x00ea2790
    void SaveThumbnail();                               // 0x00ea23e0
    void StartDialog(cSPUILayout_s00ea_28f0* dlg);                 // 0x00ea20d0
    void Destroy();                                     // 0x00ea29b0
    void SaveDialog();                                  // 0x00ea2a60
};
struct LoadSaveMsgProc {
    u8           mPad_00[0x0c];
    cSPUILayout_s00ea_28f0* mpLayout_0c;            // object+0x1c
    u8           mPad_10[6];
    u8           mFlag_16;               // object+0x26
    u8           mPad_17[0x05];
    void*        mpA_1c;                 // object+0x2c
    void*        mpB_20;                 // object+0x30
    bool HandleMessage(u32 type, LoadSaveMsg* msg);   // 0x00ea28f0
};
struct LoadSaveIface8 {
    u8  mPad_00[0x1c];
    u8  mFlag_1c;                        // object+0x24
    void LoadKeyAndClear(LoadSaveKey* key);           // 0x00ea2a30
};
// ---- items of slice s00ea28f0 end

// @ 0x00ea20a0
void cCityMusicLoadSave::Load()
{
    LaunchAssetBrowser(0xc132061au, (cCityMusicLoadSave*)this, (void*)0);
    mbWaitingForSaveDialog = 1;
}

// @ 0x00ea20d0
void cCityMusicLoadSave::StartDialog(IWindow* pDialog)
{
    BeginModal(pDialog, 0, 1);
    pDialog->v24();
    pDialog->v10();
    mbWaitingForThumbnail = 1;
}

// @ 0x00ea2120
void cCityMusicLoadSave::StopDialog(IWindow* pDialog)
{
    pDialog->v18();
    pDialog->v24();
    EndModal(pDialog, 0, 1);
    mbWaitingForThumbnail = 0;
}

// @ 0x00ea2170
cCityMusicLoadSave::cCityMusicLoadSave()
{
    mpThumbnailLayout = nullptr;
    mpMusic = nullptr;
    mpSaveDialogLayout = nullptr;
    mpViewer = nullptr;
    mbWaitingForSaveDialog = 0;
    mbWaitingForThumbnail = 0;
    mPageID = 0xffffffffu;
    mAllocID = 0xffffffffu;

    cCityMusicViewer* pViewer = nullptr;
    void* pViewerMemory = (void*)(intptr_t)operator_new(0x10c, "Audio", 0, 0, 0, 0);
    if (pViewerMemory != nullptr)
        pViewer = CreateCityMusicViewer(pViewerMemory);

    cCityMusicViewer* pOldViewer = mpViewer;
    if (pViewer != pOldViewer) {
        if (pViewer != nullptr)
            pViewer->AddRef();
        mpViewer = pViewer;
        if (pOldViewer != nullptr)
            pOldViewer->Release();
    }

    cSPUILayout_s00ea_1900* pThumbnail = nullptr;
    void* pMemory = (void*)(intptr_t)operator_new(0x18, "Audio", 0, 0, 0, 0);
    if (pMemory != nullptr) {
        Vec2 area;
        pThumbnail = (cSPUILayout_s00ea_1900*)CenterWindowInRect(pMemory, &area);
    }
    cSPUILayout_s00ea_1900* pOldThumbnail = mpThumbnailLayout;
    if (pThumbnail != pOldThumbnail) {
        if (pThumbnail != nullptr)
            pThumbnail->AddRef();
        mpThumbnailLayout = pThumbnail;
        if (pOldThumbnail != nullptr)
            pOldThumbnail->Release();
    }

    cSPUILayout_s00ea_1900* pDialog = nullptr;
    void* pDialogMemory = (void*)(intptr_t)operator_new(0x18, "Audio", 0, 0, 0, 0);
    if (pDialogMemory != nullptr) {
        Vec2 area;
        pDialog = (cSPUILayout_s00ea_1900*)CenterWindowInRect(pDialogMemory, &area);
    }
    cSPUILayout_s00ea_1900* pOldDialog = mpSaveDialogLayout;
    if (pDialog != pOldDialog) {
        if (pDialog != nullptr)
            pDialog->AddRef();
        mpSaveDialogLayout = pDialog;
        if (pOldDialog != nullptr)
            pOldDialog->Release();
    }
}

// @ 0x00ea22c0
uint32_t cCityMusicLoadSave::QueryKey(uint32_t nValue, int nKey)
{
    if (nKey != 0x2f009dd0 && nKey != 0x2f009dd0 - 0x2611d610)
        return 0;
    if (nValue != 0xc)
        return 0;
    return nValue;
}

// @ 0x00ea2310
void cCityMusicLoadSave::Init()
{
    if (!mpSaveDialogLayout->Init(kSaveDialogLayoutKey, 1, 0x5b598fau))
        return;
    if (!mpThumbnailLayout->Init(kThumbnailLayoutKey, 1, 0x5b598fau))
        return;
    if (!mpViewer->Init(mpThumbnailLayout))
        return;

    mpSaveDialogLayout->SetVisibility(false);
    ResetMusicViewer();

    cMessageServer* pServer = MessageServer();
    pServer->RegisterHandler(this, 0x50b4709u);
    pServer = MessageServer();
    pServer->RegisterHandler(this, 0x5132389u);
}

// @ 0x00ea23a0
void cCityMusicLoadSave::SetMusic(cPlayerCityMusic* pMusic)
{
    cPlayerCityMusic* pOldMusic = mpMusic;
    if (pMusic != pOldMusic) {
        if (pMusic != nullptr)
            pMusic->AddRef();
        mpMusic = pMusic;
        if (pOldMusic != nullptr)
            pOldMusic->Release();
    }
    SetViewerMusic(mpViewer, pMusic);
}

// @ 0x00ea23e0
void cCityMusicLoadSave::SaveThumbnail()
{
    if (mbWaitingForSaveDialog != 0 || mbWaitingForThumbnail != 0)
        return;

    IWindow* pFirst = mpSaveDialogLayout->FindWindowByID(0x50229a8u, 1);
    IWindow* pSecond = mpSaveDialogLayout->FindWindowByID(0x5023398u, 1);

    pFirst->v14();
    RefreshMusicDialog();
    pSecond->v14();
    RefreshMusicThumbnail();

    void* pSaveArea = GetSaveArea();
    uint32_t rect[3];
    rect[0] = 0;
    rect[1] = 0;
    rect[2] = 0;

    cAssetMetadata* pMetadata = (cAssetMetadata*)
        (intptr_t)operator_new(0xd8, "Audio", 0);
    if (pMetadata != nullptr)
        pMetadata = CreateAssetMetadata(pMetadata);

    void* pThumbnailData = GetThumbnailManager();
    void* pMusicData = nullptr;
    if (mpMusic != nullptr)
        pMusicData = GetResourceData((uint8_t*)mpMusic + 0x178);

    mpMusic->SaveData(pFirst);
    void* pResourceManager = GetResourceManager();
    pResourceManager = pResourceManager;
    SaveThumbnailToDisk(mpMusic, pMetadata);

    void* pObjectDb = GetMusicObjectDB();
    void* pLayoutManager = GetLayoutManager();
    DownloadThumbnail(pMetadata);
    (void)pObjectDb;
    (void)pLayoutManager;
    (void)pThumbnailData;
    (void)pMusicData;
    (void)pSaveArea;
    (void)rect;
}

// @ 0x00ea25f0
void cCityMusicLoadSave::FinishSave()
{
    if (mbWaitingForThumbnail == 0 && mbWaitingForSaveDialog == 0)
        return;

    void* pManager = GetThumbnailManager();
    if (pManager != nullptr) {
        void* pLayoutManager = GetThumbnailManager();
        ResetMusicViewer();
        (void)pLayoutManager;
    }
    if (mbWaitingForThumbnail != 0) {
        void* pLayoutManager = GetLayoutManager();
        if (pLayoutManager != nullptr)
            ResetMusicThumbnailState();
    }
    mbWaitingForThumbnail = 0;
    if (mbWaitingForSaveDialog != 0) {
        IWindow* pDialog = mpSaveDialogLayout->FindWindowByID(0x50232c0u, 1);
        StopDialog(pDialog);
    }
    mbWaitingForSaveDialog = 0;
}

// @ 0x00ea2670
bool cCityMusicLoadSave::DoMessage(void* pMessage, int* pData)
{
    int nKind = pData[2];
    if (nKind == 0x17) {
        int nButton = *(int*)(*(int*)pData) + 0x1c;
        (void)nButton;
        if (pData[0] != 0x50229b0) {
            if (pData[0] != 0x50229b8)
                return false;
            IWindow* pDialog = mpSaveDialogLayout->FindWindowByID(0x50232c0u, 1);
            StopDialog(pDialog);
            SaveThumbnail();
            void* pController = ControllerFind(0x1f9c52aeu, 1);
            AwardAutoTest(0x1f9c52aeu, 1);
            (void)pController;
            return true;
        }
        FinishSave();
    }
    return nKind == 0x17;
}

// @ 0x00ea26f0
void cCityMusicLoadSave::Shutdown()
{
    if (mbWaitingForSaveDialog != 0) {
        ResetAssetBrowser();
        RTTManager();
    }
    mbWaitingForSaveDialog = 0;
    FinishSave();

    cPlayerCityMusic* pMusic = mpMusic;
    if (pMusic != nullptr) {
        mpMusic = nullptr;
        pMusic->Release();
    }

    cMessageServer* pServer = MessageServer();
    pServer->UnregisterHandler(this, 0x50b4709u, 0xffffd8f1);
    pServer = MessageServer();
    pServer->UnregisterHandler(this, 0x5132389u, 0xffffd8f1);

    ResetMusicViewer();
    mpThumbnailLayout->Shutdown(1);
    mpSaveDialogLayout->Shutdown(1);
}

// @ 0x00ea2790
bool cCityMusicLoadSave::LoadKey(int a, int b, int nKey)
{
    if (gSaveDialogKey != (uint32_t)nKey)
        return false;

    void* pManager = GetResourceManager();
    void* pResourceA = nullptr;
    int nFlags = 0;
    (void)nFlags;
    if (pResourceA != nullptr)
        pResourceA = nullptr;

    int nFirst = 0;
    int nSecond = 0;
    if (pResourceA != nullptr) {
        nFirst = 0;
        (void)nFirst;
    }

    void* pManager2 = GetResourceManager();
    if (pManager2 != nullptr) {
        nSecond = (int)(intptr_t)GetResourceData(pManager2);
    }

    if (nFirst != 0 && nSecond != 0) {
        RefreshMusicDialog();
        RefreshMusicThumbnail();
        if (mpMusic->LoadData((void*)(intptr_t)nSecond)) {
            mpMusic->PlayMelody(0);
            return true;
        }
    }
    (void)pManager;
    (void)a;
    (void)b;
    return false;
}

// @ 0x00ea28f0
bool LoadSaveMsgProc::HandleMessage(u32 type, LoadSaveMsg* msg)
{
    if (type == 0x50b4709) {
        if (msg->mpSender_08 == (cCityMusicLoadSave_s00ea_28f0*)((char*)this - 0x10)) {
            if (mFlag_16) {
                mFlag_16 = 0;
                mpLayout_0c->SetVisibility(false);
                ((cCityMusicLoadSave_s00ea_28f0*)((char*)this - 0x10))->SaveThumbnail();
                return true;
            }
            void* pm = FUN_0067dda0();
            ((void (__thiscall*)(void*, void*, void*))VTP(pm)[0x14 / 4])(pm, mpA_1c, mpB_20);
        }
    } else if (type == 0x5132389) {
        LoadSaveKey* it = msg->mpKeys_00->mpBegin_00;
        LoadSaveKey* end = msg->mpKeys_00->mpEnd_04;
        while (it != end) {
            if (((cCityMusicLoadSave_s00ea_28f0*)((char*)this - 0x10))->LoadKey(*it))
                return true;
            ++it;
        }
        return true;
    } else {
        return false;
    }
    return true;
}

// @ 0x00ea29b0
void cCityMusicLoadSave_s00ea_28f0::Destroy()
{
    mpVtbl_00 = vtbl_LoadSave_00;
    mpVtbl_08 = vtbl_LoadSave_08;
    mpVtbl_0c = vtbl_LoadSave_0c;
    mpVtbl_10 = vtbl_LoadSave_10;
    Shutdown();

    void* p20 = mpLayout_20;
    if (p20)
        ((void (__thiscall*)(void*))VTP(p20)[2])(p20);
    void* p1c = mpLayout_1c;
    if (p1c)
        ((void (__thiscall*)(void*))VTP(p1c)[2])(p1c);
    void* p18 = mpViewer_18;
    if (p18) {
        void* sub = (char*)p18 + 4;
        ((void (__thiscall*)(void*))VTP(sub)[2])(sub);
    }
    void* p14 = mpField_14;
    if (p14)
        ((void (__thiscall*)(void*))VTP(p14)[1])(p14);

    mpVtbl_10 = vtbl_PaintSystem;
    mpVtbl_0c = vtbl_ITracerBase;
    mpVtbl_00 = vtbl_ContentValidation;
}

// @ 0x00ea2a30
void LoadSaveIface8::LoadKeyAndClear(LoadSaveKey* key)
{
    cCityMusicLoadSave_s00ea_28f0* self = (cCityMusicLoadSave_s00ea_28f0*)((char*)this - 8);
    self->LoadKey(*key);
    mFlag_1c = 0;
}

// @ 0x00ea2a60
void cCityMusicLoadSave_s00ea_28f0::SaveDialog()
{
    if (mFlag_25 || mFlag_26)
        return;

    mpLayout_1c->SetParentWin(0, true, 0x5b598fa);
    mpLayout_1c->SetVisibility(true);
    ((cCityMusicViewer_s00ea_28f0*)mpViewer_18)->Redraw();
    mpLayout_1c->SetParentWin(0, false, 0x5b598fa);

    // ask the window manager for the thumbnail-sized rect of the music viewer
    void* pm = FUN_0067dda0();
    u32 rect[2];
    ((void (__thiscall*)(void*, u32*, u32, s32, s32, s32, u32, u32))VTP(pm)[0x10 / 4])(
        pm, rect, 0x80, 0x80, 1, -1, 0, 0);
    mField_2c = rect[0];
    mField_30 = rect[1];

    // create the "CityMusicThumbnail" property on the music object
    void* pw = FUN_0067dda0();
    ((void (__thiscall*)(void*, u32, u32, const char*))VTP(pw)[0x48 / 4])(
        pw, mField_2c, mField_30, "CityMusicThumbnail");

    // tooltip panel over the thumbnail
    void* mem = operator new(0x30);
    void* tooltip = 0;
    if (mem)
        tooltip = cSPUITooltipPanel_ctor(mem, 0x43000000, mpLayout_1c, mField_2c, mField_30, 0);
    if (tooltip)
        ((void (__thiscall*)(void*))VTP(tooltip)[0])(tooltip);

    // a small behaviour object that forwards the thumbnail click
    void* mem2 = operator new(0x18);
    void* behavior = 0;
    if (mem2) {
        *(u32*)((char*)mem2 + 0x10) = 0;
        *(void**)mem2 = vtbl_UI_BehaviorMessage;
        *(u32*)((char*)mem2 + 4) = 0;
        *(void**)mem2 = vtbl_Behavior;
        behavior = mem2;
        ((void (__thiscall*)(void*))VTP(behavior)[1])(behavior);
    }
    *(void**)((char*)behavior + 8) = this;

    struct DialogMsg {
        u32 mPad_00[4];
        u32 mType_10;
        void* mpObj_14;
        u32 mPad_18[4];
    } msg;
    msg.mPad_00[0] = 0;
    msg.mPad_00[1] = 0;
    msg.mPad_00[2] = 1;
    msg.mPad_00[3] = 0;
    msg.mType_10 = 0x50b4709;
    msg.mpObj_14 = behavior;
    msg.mPad_18[0] = 0;
    msg.mPad_18[1] = 0;
    msg.mPad_18[2] = 0;
    msg.mPad_18[3] = 0;

    void* pmgr = FUN_0067dd50();
    mField_2c = (u32)((void* (__thiscall*)(void*, void*, void*, void*))VTP(pmgr)[0x78 / 4])(
        pmgr, tooltip, 0, &msg);
    mFlag_26 = 1;

    cSPUILayout_s00ea_28f0* dlg = mpLayout_20->FindWindowByID(0x50232c0, 1);
    void* btn = ((void* (__thiscall*)(cSPUILayout_s00ea_28f0*, u32, s32))VTP(dlg)[0xf0 / 4])(dlg, 0x50229a8, 0);

    void* label = ((void* (__thiscall*)(cSPUILayout_s00ea_28f0*, u32, s32))VTP(dlg)[0xf0 / 4])(dlg, 0x5023398, 0);
    ((void (__thiscall*)(void*, u32))VTP(label)[0x80 / 4])(label, mField_30);

    StartDialog(dlg);
    ((void (__thiscall*)(void*))VTP(behavior)[2])(behavior);
    if (btn)
        ((void (__thiscall*)(void*))VTP(btn)[1])(btn);
}
