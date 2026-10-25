// src/game/SPGonzago/SPAudioCityMusicLoadSave.cpp -- migrated from slice(s) s00ea1900 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPAudioCityMusicLoadSave.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

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
void SetViewerMusic(cCityMusicViewer* pViewer, cPlayerCityMusic* pMusic);
cCityMusicViewer* CreateCityMusicViewer(void* pMemory);
cAssetMetadata* CreateAssetMetadata(void* pMemory);
void ResetMusicThumbnailState();
void* GetResourceData(void* pObject);
extern const wchar_t kSaveDialogLayoutKey[];
extern const wchar_t kThumbnailLayoutKey[];
// ---- items of slice s00ea1900 end

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
