// src/game/SPGonzago/SPAudioCityMusicLargeAssetView.cpp -- migrated from slice(s) s00ea1900, s00ea0910 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPAudioCityMusicLargeAssetView.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cGameNounManager.h"
#include "cSPUILayout.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* MessageServer();                                             // 0x0067dcc0

// ---- items of slice s00ea0910 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int u32;
struct IObject {
virtual void  o00();
virtual void  o04();
virtual void  o08();
    virtual void* o0c(u32 id);
    virtual void  o10();
    virtual void  o14(int a, void* b);
    virtual void  o18();
    virtual int   o1c();
virtual void  o20();
virtual void  o24();
    virtual int   o28(int a, int b);
    virtual int   o2c();
    virtual int   o30();
};
struct IMessageServer {
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
    virtual void s10();
    virtual int  s14(int a, int b, int c);
};
struct Message {
    IObject* mpObject;   // +0x00
    int      mField04;   // +0x04
    int      mType;      // +0x08
    int      mId;        // +0x0c
    int      mField10;   // +0x10
    int      mSelected;  // +0x14
    int      mField18;   // +0x18
};
struct cCityMusicLargeAssetView {
    char DoMessage(int unused, Message* msg);                        // 0x00ea18c0 (ret 8)
};
extern "C" void* MessageServer();                                             // 0x0067dcc0
// ---- items of slice s00ea0910 end

// ---- items of slice s00ea1900 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const wchar_t kMissingText[];
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
class cSPUIWinProc_s00ea_1900 : public IWinProc {
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
    bool Init(cSPUILayout_s00ea_1900* pLayout);
    void SetMusic(cPlayerCityMusic* pMusic);
    void Shutdown();
};
class cCityMusicLargeAssetView_s00ea_1900 : public cSPUIWinProc_s00ea_1900 {
public:
    cCityMusicLargeAssetView_s00ea_1900();
    ~cCityMusicLargeAssetView_s00ea_1900();
    void Hide();  // 0x00ea1b00 (cCityMusicLargeAssetView::Hide)
    void Update();
    void InitLayout();  // 0x00ea1ee0 (cCityMusicLargeAssetView::InitLayout)
    bool Show(IWindow* pParent, cSPAssetData* pData);  // 0x00ea1f90 (cCityMusicLargeAssetView::Show)
    void BindWindows();
    void ReleaseWindows();

    cSPUILayout_s00ea_1900* mpLayout;                  // 0x10
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
void* operator_new(size_t nSize, const char* pName, int a, int b, int c, int d);
void* operator_new(size_t nSize, const char* pName, int a);
void operator_delete__(void* pMemory);
void* CenterWindowInRect(void* pLayout, void* pArea);
void SetWindowAreaToParent(IWindow* pWindow);
void* GetResourceManager();
void ResetMusicViewer();
bool IsMetadataValid(cSPAssetData* pData);
cPlayerCityMusic* CreatePlayerCityMusic(void* pMemory);
cCityMusicViewer* CreateCityMusicViewer(void* pMemory);
void* GetResourceData(void* pObject);
// ---- items of slice s00ea1900 end

// @ 0x00ea18c0
char cCityMusicLargeAssetView::DoMessage(int unused, Message* msg)
{
    if (msg->mType == 0x287259f6 && msg->mId == 0x74174c59) {
        IMessageServer* server = (IMessageServer*)MessageServer();
        server->s14(0x14ac4938, 0, 0);
        return 1;
    } else {
        return 0;
    }
}

// @ 0x00ea1900
cCityMusicLargeAssetView_s00ea_1900::cCityMusicLargeAssetView_s00ea_1900()
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

// @ 0x00ea1a30
cCityMusicLargeAssetView_s00ea_1900::~cCityMusicLargeAssetView_s00ea_1900()
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

// @ 0x00ea1b00
void cCityMusicLargeAssetView_s00ea_1900::Hide()
{
    cPlayerCityMusic* pMusic = mpMusic;
    mIsVisible = 0;
    pMusic->Play(false);

    cSPUILayout_s00ea_1900* pLayout = mpLayout;
    if (pLayout != nullptr) {
        pLayout->Shutdown(1);
        pLayout = mpLayout;
        if (pLayout != nullptr) {
            mpLayout = nullptr;
            pLayout->FindWindowByID(0);
        }
    }
}

// @ 0x00ea1b40
void cCityMusicLargeAssetView_s00ea_1900::Update()
{
    mpViewer->Shutdown();
}

// @ 0x00ea1b50
void cCityMusicLargeAssetView_s00ea_1900::ReleaseWindows()
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

// @ 0x00ea1c10
void cCityMusicLargeAssetView_s00ea_1900::BindWindows()
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

// @ 0x00ea1ee0
void cCityMusicLargeAssetView_s00ea_1900::InitLayout()
{
    cSPUILayout_s00ea_1900* pLayout = nullptr;
    void* pMemory = (void*)(intptr_t)operator_new(0x18, "Editor", 0, 0, 0, 0);
    if (pMemory != nullptr) {
        Vec2 area;
        pLayout = (cSPUILayout_s00ea_1900*)CenterWindowInRect(pMemory, &area);
    }

    cSPUILayout_s00ea_1900* pOldLayout = mpLayout;
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

// @ 0x00ea1f90
bool cCityMusicLargeAssetView_s00ea_1900::Show(IWindow* pParent, cSPAssetData* pData)
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
