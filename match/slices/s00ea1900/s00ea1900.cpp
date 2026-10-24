// Recovered from SporeApp.exe (retail).
// Batch gold6 / worker 43 / slice s00ea1900.
//
// City-music asset views: the large asset view (layout, windows, music viewer)
// and the load/save dialog driver used by the music picker.

typedef unsigned int size_t;
typedef unsigned int uint;
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
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

class cSPUIWinProc : public IWinProc {
public:
    uint8_t mPad1c[0x0c];                   // 0x1c
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

class cSPUILayout : public IRefCounted {
public:
    bool Init(const void* pKey, int a, uint32_t flags);
    IWindow* FindWindowByID(uint32_t nId, int bFind);
    IWindow* FindWindowByID(uint32_t nId);
    void SetParentWin(IWindow* pParent, int a, uint32_t flags);
    void SetReloadCallback(void* pCallback, void* pOwner);
    void SetVisibility(bool bVisible);
    void Shutdown(int bDelete);
};

class cSPAssetData : public IRefCounted {
public:
    virtual void v14();
    virtual void v18();
    virtual void* GetMetadata();
    virtual void GetName(void* pString);
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
    bool Init(cSPUILayout* pLayout);
    void SetMusic(cPlayerCityMusic* pMusic);
    void Shutdown();
};

class cAssetMetadata : public IRefCounted {
public:
    cAssetMetadata();
};

class cCityMusicLargeAssetView : public cSPUIWinProc {
public:
    cCityMusicLargeAssetView();
    ~cCityMusicLargeAssetView();
    void Hide();
    void Update();
    void InitLayout();
    bool Show(IWindow* pParent, cSPAssetData* pData);
    void BindWindows();
    void ReleaseWindows();

    cSPUILayout* mpLayout;                  // 0x10
    cPlayerCityMusic* mpMusic;              // 0x14
    IWindow* mpWindow18;                    // 0x18
    IWindow* mpWindow1c;                    // 0x1c
    IWindow* mpWindow20;                    // 0x20
    IWindow* mpWindow24;                    // 0x24
    IWindow* mpWindow28;                    // 0x28
    IWindow* mpWindow2c;                    // 0x2c
    cSPAssetData* mpAssetData;              // 0x30
    uint8_t mIsVisible;                     // 0x34
    uint8_t mPad35[0x03];                   // 0x35
    cCityMusicViewer* mpViewer;             // 0x38
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
    cSPUILayout* mpThumbnailLayout;         // 0x20
    cPlayerCityMusic* mpMusic;              // 0x24
    cSPUILayout* mpSaveDialogLayout;        // 0x28
    cCityMusicViewer* mpViewer;             // 0x2c
    uint8_t mbWaitingForSaveDialog;         // 0x31
    uint8_t mbWaitingForThumbnail;          // 0x32
    uint8_t mPad33[0x09];                   // 0x33
    uint32_t mPageID;                       // 0x3c
    uint32_t mAllocID;                      // 0x40
};

void* operator_new(size_t nSize, const char* pName, int a, int b, int c, int d);
void* operator_new(size_t nSize, const char* pName, int a);
void operator_delete__(void* pMemory);
cMessageServer* MessageServer();
void* CenterWindowInRect(void* pLayout, void* pArea);
void SetWindowAreaToParent(IWindow* pWindow);
void* GetResourceManager();
void SetWindowText(IWindow* pWindow, const wchar_t* pText);
void* GetMainWindowArea(void* pOut);
void LaunchAssetBrowser(uint32_t id, void* pCallback, void* pProc);
void BeginModal(IWindow* pWindow, int a, int b);
void EndModal(IWindow* pWindow, int a, int b);
void SetLayoutVisible(cSPUILayout* pLayout, bool bVisible);
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
bool IsMetadataValid(cSPAssetData* pData);
bool QueryProperty(void* pData, uint32_t nKey, void** ppOut);
cPlayerCityMusic* CreatePlayerCityMusic(void* pMemory);
cCityMusicViewer* CreateCityMusicViewer(void* pMemory);
cAssetMetadata* CreateAssetMetadata(void* pMemory);
void ResetMusicThumbnailState();
void* GetPropertyAsFloat();
void* GetPropertyAsString();
void* LoadMusicResource(void* pKey, int a, int b, int c);
bool GetResource(int a, int b);
void* GetResourceData(void* pObject);

extern uint32_t gSaveDialogKey;
extern const wchar_t kSaveDialogLayoutKey[];
extern const wchar_t kThumbnailLayoutKey[];
extern const wchar_t kMissingText[];

// ---------------------------------------------------------------------------
// 0x00ea1900  Simulator::cCityMusicLargeAssetView::cCityMusicLargeAssetView
// ---------------------------------------------------------------------------
// @ 0x00ea1900
cCityMusicLargeAssetView::cCityMusicLargeAssetView()
{
    mpLayout = nullptr;
    mpMusic = nullptr;
    mpWindow18 = nullptr;
    mpWindow1c = nullptr;
    mpWindow20 = nullptr;
    mpWindow24 = nullptr;
    mpWindow28 = nullptr;
    mpWindow2c = nullptr;
    mpAssetData = nullptr;
    mIsVisible = 0;
    mpViewer = nullptr;

    cPlayerCityMusic* pMusic = nullptr;
    void* pMemory = (void*)(intptr_t)operator_new(0x220, "Audio", 0, 0, 0, 0);
    if (pMemory != nullptr)
        pMusic = CreatePlayerCityMusic(pMemory);

    cPlayerCityMusic* pOldMusic = mpMusic;
    if (pMusic != pOldMusic) {
        if (pMusic != nullptr)
            pMusic->AddRef();
        mpMusic = pMusic;
        if (pOldMusic != nullptr)
            pOldMusic->Release();
    }

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

    mpViewer->SetMusic(mpMusic);
}

// ---------------------------------------------------------------------------
// 0x00ea1a30  Simulator::cCityMusicLargeAssetView::~cCityMusicLargeAssetView
// ---------------------------------------------------------------------------
// @ 0x00ea1a30
cCityMusicLargeAssetView::~cCityMusicLargeAssetView()
{
    if (mpViewer != nullptr)
        mpViewer->Release();
    if (mpMusic != nullptr)
        mpMusic->Release();
    if (mpAssetData != nullptr)
        mpAssetData->Release();
    if (mpWindow2c != nullptr)
        mpWindow2c->Release();
    if (mpWindow28 != nullptr)
        mpWindow28->Release();
    if (mpWindow24 != nullptr)
        mpWindow24->Release();
    if (mpWindow20 != nullptr)
        mpWindow20->Release();
    if (mpWindow1c != nullptr)
        mpWindow1c->Release();
    if (mpWindow18 != nullptr)
        mpWindow18->Release();
    if (mpLayout != nullptr)
        mpLayout->Shutdown(0);
}

// ---------------------------------------------------------------------------
// 0x00ea1b00  SP::Audio::cCityMusicLargeAssetView::Hide
// ---------------------------------------------------------------------------
// @ 0x00ea1b00
void cCityMusicLargeAssetView::Hide()
{
    cPlayerCityMusic* pMusic = mpMusic;
    mIsVisible = 0;
    pMusic->Play(false);

    cSPUILayout* pLayout = mpLayout;
    if (pLayout != nullptr) {
        pLayout->Shutdown(1);
        pLayout = mpLayout;
        if (pLayout != nullptr) {
            mpLayout = nullptr;
            pLayout->FindWindowByID(0);
        }
    }
}

// ---------------------------------------------------------------------------
// 0x00ea1b40  SP::Audio::cCityMusicLargeAssetView::Update
// ---------------------------------------------------------------------------
// @ 0x00ea1b40
void cCityMusicLargeAssetView::Update()
{
    mpViewer->Shutdown();
}

// ---------------------------------------------------------------------------
// 0x00ea1b50  cCityMusicLargeAssetView::ReleaseWindows
// ---------------------------------------------------------------------------
// @ 0x00ea1b50
void cCityMusicLargeAssetView::ReleaseWindows()
{
    if (mIsVisible == 0)
        return;

    ResetMusicViewer();

    if (mpWindow18 != nullptr)
        mpWindow18->v18();
    IWindow* pWindow = mpWindow18;
    if (pWindow != nullptr) {
        mpWindow18 = nullptr;
        pWindow->Release();
    }
    pWindow = mpWindow1c;
    if (pWindow != nullptr) {
        mpWindow1c = nullptr;
        pWindow->Release();
    }
    pWindow = mpWindow20;
    if (pWindow != nullptr) {
        mpWindow20 = nullptr;
        pWindow->Release();
    }
    pWindow = mpWindow24;
    if (pWindow != nullptr) {
        mpWindow24 = nullptr;
        pWindow->Release();
    }
    pWindow = mpWindow28;
    if (pWindow != nullptr) {
        mpWindow28 = nullptr;
        pWindow->Release();
    }
    pWindow = mpWindow2c;
    if (pWindow != nullptr) {
        mpWindow2c = nullptr;
        pWindow->Release();
    }
    mIsVisible = 0;
}

// ---------------------------------------------------------------------------
// 0x00ea1c10  cCityMusicLargeAssetView::BindWindows
// ---------------------------------------------------------------------------
// @ 0x00ea1c10
void cCityMusicLargeAssetView::BindWindows()
{
    if (mIsVisible != 0)
        return;

    IWindow* pWindow = mpLayout->FindWindowByID(0xf3c6dc19u, 1);
    IWindow* pOld = mpWindow18;
    if (pWindow != pOld) {
        if (pWindow != nullptr)
            pWindow->AddRef();
        mpWindow18 = pWindow;
        if (pOld != nullptr)
            pOld->Release();
    }
    if (mpWindow18 != nullptr) {
        mpWindow18->v10();
        SetWindowAreaToParent(mpWindow18);
    }

    pWindow = mpLayout->FindWindowByID(0x34ac3265u, 1);
    pOld = mpWindow1c;
    if (pWindow != pOld) {
        if (pWindow != nullptr)
            pWindow->AddRef();
        mpWindow1c = pWindow;
        if (pOld != nullptr)
            pOld->Release();
    }
    if (mpAssetData != nullptr && mpWindow18 != nullptr && mpWindow1c != nullptr) {
        mpAssetData->v14();
        mpAssetData->v18();
    }

    pWindow = mpLayout->FindWindowByID(0x53d6fe29u, 1);
    pOld = mpWindow20;
    if (pWindow != pOld) {
        if (pWindow != nullptr)
            pWindow->AddRef();
        mpWindow20 = pWindow;
        if (pOld != nullptr)
            pOld->Release();
    }
    if (mpWindow20 != nullptr && mpAssetData != nullptr) {
        void* pName = mpAssetData->GetMetadata();
        const wchar_t* pText = pName != nullptr ? kMissingText : kMissingText;
        mpWindow20->SetText(pText);
    }

    pWindow = mpLayout->FindWindowByID(0x53d6fe2au, 1);
    pOld = mpWindow24;
    if (pWindow != pOld) {
        if (pWindow != nullptr)
            pWindow->AddRef();
        mpWindow24 = pWindow;
        if (pOld != nullptr)
            pOld->Release();
    }
    if (mpWindow24 != nullptr && mpAssetData != nullptr) {
        void* pName = mpAssetData->GetMetadata();
        const wchar_t* pText = pName != nullptr ? kMissingText : kMissingText;
        mpWindow24->SetText(pText);
    }

    pWindow = mpLayout->FindWindowByID(0xb456a483u, 1);
    pOld = mpWindow28;
    if (pWindow != pOld) {
        if (pWindow != nullptr)
            pWindow->AddRef();
        mpWindow28 = pWindow;
        if (pOld != nullptr)
            pOld->Release();
    }
    void* pMetadata = nullptr;
    if (mpAssetData != nullptr)
        pMetadata = mpAssetData->GetMetadata();
    if (mpWindow28 != nullptr && pMetadata != nullptr) {
        mpWindow28->SetText(kMissingText);
    }

    pWindow = mpLayout->FindWindowByID(0xb456a47au, 1);
    pOld = mpWindow2c;
    if (pWindow != pOld) {
        if (pWindow != nullptr)
            pWindow->AddRef();
        mpWindow2c = pWindow;
        if (pOld != nullptr)
            pOld->Release();
    }
    if (mpWindow2c != nullptr && mpAssetData != nullptr) {
        void* pName = nullptr;
        mpAssetData->GetName(&pName);
        mpWindow2c->SetText(kMissingText);
        if (pName != nullptr)
            operator_delete__(pName);
    }

    mpViewer->Init(mpLayout);
    mIsVisible = 1;
}

// ---------------------------------------------------------------------------
// 0x00ea1ee0  SP::Audio::cCityMusicLargeAssetView::InitLayout
// ---------------------------------------------------------------------------
// @ 0x00ea1ee0
void cCityMusicLargeAssetView::InitLayout()
{
    cSPUILayout* pLayout = nullptr;
    void* pMemory = (void*)(intptr_t)operator_new(0x18, "Editor", 0, 0, 0, 0);
    if (pMemory != nullptr) {
        Vec2 area;
        pLayout = (cSPUILayout*)CenterWindowInRect(pMemory, &area);
    }

    cSPUILayout* pOldLayout = mpLayout;
    if (pLayout != pOldLayout) {
        if (pLayout != nullptr)
            pLayout->AddRef();
        mpLayout = pLayout;
        if (pOldLayout != nullptr)
            pOldLayout->Release();
    }

    uint32_t key[3];
    key[0] = 0x72959eb5u;
    key[1] = 0x510a95bu;
    key[2] = 0x40464100u;
    mpLayout->Init(key, 1, 0x5b598fau);
    mpLayout->SetParentWin(mpWindow18, 1, 0x5b598fau);
    mpLayout->SetReloadCallback((void*)0, this);
    BindWindows();
}

// ---------------------------------------------------------------------------
// 0x00ea1f90  SP::Audio::cCityMusicLargeAssetView::Show
// ---------------------------------------------------------------------------
// @ 0x00ea1f90
bool cCityMusicLargeAssetView::Show(IWindow* pParent, cSPAssetData* pData)
{
    mIsVisible = 1;

    cSPAssetData* pOldData = mpAssetData;
    if (pData != pOldData) {
        if (pData != nullptr)
            pData->AddRef();
        mpAssetData = pData;
        if (pOldData != nullptr)
            pOldData->Release();
    }

    IWindow* pOldParent = mpWindow18;
    if (pParent != pOldParent) {
        if (pParent != nullptr)
            pParent->AddRef();
        mpWindow18 = pParent;
        if (pOldParent != nullptr)
            pOldParent->Release();
    }

    InitLayout();

    void* pManager = GetResourceManager();
    void* pKey = nullptr;
    void* pResource = nullptr;
    if (pKey != nullptr)
        pKey = nullptr;
    if (IsMetadataValid(pData)) {
        void* pData2 = nullptr;
        mpMusic->LoadData(pData2);
        pResource = GetResourceData(pManager);
        mpMusic->v14();
    }
    return true;
}

// ---------------------------------------------------------------------------
// 0x00ea20a0  SP::Audio::cCityMusicLoadSave::Load
// ---------------------------------------------------------------------------
// @ 0x00ea20a0
void cCityMusicLoadSave::Load()
{
    LaunchAssetBrowser(0xc132061au, (cCityMusicLoadSave*)this, (void*)0);
    mbWaitingForSaveDialog = 1;
}

// ---------------------------------------------------------------------------
// 0x00ea20d0  SP::Audio::cCityMusicLoadSave::StartDialog
// ---------------------------------------------------------------------------
// @ 0x00ea20d0
void cCityMusicLoadSave::StartDialog(IWindow* pDialog)
{
    BeginModal(pDialog, 0, 1);
    pDialog->v24();
    pDialog->v10();
    mbWaitingForThumbnail = 1;
}

// ---------------------------------------------------------------------------
// 0x00ea2120  SP::Audio::cCityMusicLoadSave::StopDialog
// ---------------------------------------------------------------------------
// @ 0x00ea2120
void cCityMusicLoadSave::StopDialog(IWindow* pDialog)
{
    pDialog->v18();
    pDialog->v24();
    EndModal(pDialog, 0, 1);
    mbWaitingForThumbnail = 0;
}

// ---------------------------------------------------------------------------
// 0x00ea2170  SP::Audio::cCityMusicLoadSave::cCityMusicLoadSave
// ---------------------------------------------------------------------------
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

    cSPUILayout* pThumbnail = nullptr;
    void* pMemory = (void*)(intptr_t)operator_new(0x18, "Audio", 0, 0, 0, 0);
    if (pMemory != nullptr) {
        Vec2 area;
        pThumbnail = (cSPUILayout*)CenterWindowInRect(pMemory, &area);
    }
    cSPUILayout* pOldThumbnail = mpThumbnailLayout;
    if (pThumbnail != pOldThumbnail) {
        if (pThumbnail != nullptr)
            pThumbnail->AddRef();
        mpThumbnailLayout = pThumbnail;
        if (pOldThumbnail != nullptr)
            pOldThumbnail->Release();
    }

    cSPUILayout* pDialog = nullptr;
    void* pDialogMemory = (void*)(intptr_t)operator_new(0x18, "Audio", 0, 0, 0, 0);
    if (pDialogMemory != nullptr) {
        Vec2 area;
        pDialog = (cSPUILayout*)CenterWindowInRect(pDialogMemory, &area);
    }
    cSPUILayout* pOldDialog = mpSaveDialogLayout;
    if (pDialog != pOldDialog) {
        if (pDialog != nullptr)
            pDialog->AddRef();
        mpSaveDialogLayout = pDialog;
        if (pOldDialog != nullptr)
            pOldDialog->Release();
    }
}

// ---------------------------------------------------------------------------
// 0x00ea22c0  cCityMusicLoadSave::QueryKey
// ---------------------------------------------------------------------------
// @ 0x00ea22c0
uint32_t cCityMusicLoadSave::QueryKey(uint32_t nValue, int nKey)
{
    if (nKey != 0x2f009dd0 && nKey != 0x2f009dd0 - 0x2611d610)
        return 0;
    if (nValue != 0xc)
        return 0;
    return nValue;
}

// ---------------------------------------------------------------------------
// 0x00ea2310  SP::Audio::cCityMusicLoadSave::Init
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00ea23a0  SP::Audio::cCityMusicLoadSave::SetMusic
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00ea23e0  cCityMusicLoadSave::SaveThumbnail
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00ea25f0  SP::Audio::cCityMusicLoadSave::FinishSave
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00ea2670  SP::Audio::cCityMusicLoadSave::DoMessage
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00ea26f0  SP::Audio::cCityMusicLoadSave::Shutdown
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00ea2790  SP::Audio::cCityMusicLoadSave::LoadKey
// ---------------------------------------------------------------------------
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
