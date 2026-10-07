// Slice s0064c8e0 -- the retail Sporepedia asset browser's message handler
// (EA::Messaging::IHandler::HandleMessage override; the PDB "caller-single" candidate
// SP::cSPUIAssetBrowser::SetSporeGuideVisibility is a mis-attribution: the function
// dispatches on a message id and returns bool, `ret 8`).
// Module flags: /O2 /MD /Gy /TP (UI module: no /arch:SSE, no /EHsc -- the stack
// message objects with destructors get no EH frame).
//
// The retail cSPUIAssetBrowser is ~0x250 bytes (the 2008 PDB layout is 0x100), so the
// members below are named after their use; offsets were taken from the disassembly.
#include "types.h"

#define VPAD4(p)  virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3();
#define VPAD8(p)  VPAD4(p##a) VPAD4(p##b)
#define VPAD16(p) VPAD8(p##c) VPAD8(p##d)
#define VPAD32(p) VPAD16(p##e) VPAD16(p##f)

struct ResourceKey {
    uint32_t instance, type, group;
};

// ---- small interfaces (only the vtable slots used here) ----------------------------
struct IVisibleObject {                 // windows / views / large asset views
    VPAD16(a) VPAD8(b) VPAD4(c) virtual void v1c(); virtual void v1d(); virtual void v1e();
    virtual void SetVisible(bool visible, bool animate);       // +0x7c
};

struct IAssetDataList {
    VPAD32(a) VPAD16(b) VPAD8(c) VPAD4(d)
    virtual IVisibleObject* FindView(uint32_t id, bool create);  // +0xf0
};

struct IAuthManager {
    VPAD8(a) virtual void v20(); virtual bool IsLoggedIn();                         // +0x24
};

struct IMessageServer {
    VPAD4(a) virtual void v10();
    virtual void MessageSend(uint32_t messageID, void* pMessage, void* pHandler);  // +0x14
};

struct IGameModeManager {
    VPAD8(a) VPAD4(b) virtual void v30(); virtual void v34();
    virtual uint32_t GetActiveModeID();                          // +0x38
};

struct Viewport { int x, y; };

struct IRenderView {
    VPAD32(a) VPAD16(b) virtual void v30(); virtual void v31(); virtual void v32();
    virtual void v33(); virtual void v34(); virtual void v35();
    virtual void GetViewport(Viewport* pRect);                        // +0xd8
};

struct ICameraManager {
    VPAD16(a) VPAD4(b) virtual void v14(); virtual void v15(); virtual void v16();
    virtual void SetMode(int a, int b);                          // +0x5c
};

struct IKeySource {
    VPAD16(a) virtual const ResourceKey* GetKey();               // +0x40
};

struct IUpdatable {
    VPAD8(a) virtual void v20(); virtual void Update();                             // +0x24
};

struct ITypedObject {
    VPAD4(a) virtual uint32_t GetType();                         // +0x10
};

struct IBoolQuery {
    VPAD4(a) virtual bool IsActive();                            // +0x10
};

struct cCaptureJob {
    void Capture(Viewport* pViewport);                                // 0x0076dee0
};

struct cSPUILayoutCollection {
    void Hide();                                                 // 0x00801380
};

struct SporeGuideState {
    uint32_t pad0[7];
    bool mbVisible;                                              // +0x1c
};

struct AppProperties {
    uint32_t pad0[15];
    struct Inner { uint32_t pad[0x118 / 4]; uint32_t mValue; }* mpInner;   // +0x3c
};

// ---- feed list items ---------------------------------------------------------------
struct cSPUIFeedListItem {
    uint32_t pad0[0x128 / 4];
    const wchar_t* mWebURL;          // +0x128
    const wchar_t* mSporeGuidePage;  // +0x12c
    uint32_t pad130;
    uint32_t mFeedArg;               // +0x134
    uint32_t pad138[6];
    uint32_t mFeedID;                // +0x150
    uint32_t mConfigID;              // +0x154
    uint32_t pad158[8];
    uint32_t mItemType;              // +0x178
    uint32_t mItemID;                // +0x17c

    void SetSelected(bool b);                                    // 0x00666490
    void GetAssetList(void* pList);                              // 0x00668d90
};

struct cSPUIFeedList {
    cSPUIFeedListItem* FindItem(uint32_t id);                    // 0x00662960
    cSPUIFeedListItem* FindItemByIndex(uint32_t id);             // 0x006629a0
};

struct cSPUIFeedEdit {
    void SetEditActive(bool active);                             // 0x0065d9f0
    void Refresh();                                              // 0x0065e720
    void OnEvent(void* pMsg);                                    // 0x0065dd30
};

struct cSPUIAssetWebBrowser {
    void SetActive(bool active);                                 // 0x0065b2a0
    void ClearPage();                                            // 0x0065b510
};

struct cSPUISporeGuidePage {
    void LoadSporeGuidePage(const wchar_t* name);                // 0x00675080
};

void operator delete[](void* p);                                 // 0x00f47380

// eastl::vector_set<uint32_t> (only the members used here; the dtor is inline)
struct InsertResult { uint32_t* it; bool inserted; };
struct IDSet {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    IDSet() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~IDSet() { if (mpBegin) delete[] (char*)mpBegin; }
    void reserve(uint32_t n);                                    // 0x00565f50
    InsertResult insert(const uint32_t& value);                  // 0x00554020
};

struct FeedEntry {                  // 0x34 bytes
    uint32_t mID;
    uint32_t pad[12];
};

struct FeedEntryVector {
    FeedEntry* mpBegin;
    FeedEntry* mpEnd;
    FeedEntry* mpCapacity;
    FeedEntryVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~FeedEntryVector();                                          // 0x00647080
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
};

struct AssetList {                   // 12 bytes, dtor 0x007a41a0
    uint32_t mpBegin, mpEnd, mpCapacity;
    AssetList() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~AssetList();                                                // 0x007a41a0
};

struct cAssetFilterPreview {
    void SetFeedFilter(IDSet* pIDs);                             // 0x00661380
    void Apply(uint32_t feedID, uint32_t configID, bool reset);  // 0x00662750
};

struct cSPUIAssetGrid {
    uint32_t pad0[0xe0 / 4];
    cAssetFilterPreview* mpFilterPreview;                        // +0xe0
    uint32_t pade4[(0x1e4 - 0xe4) / 4];
    bool mbIsEditorGrid;                                         // +0x1e4

    const ResourceKey* GetEntryByID(uint32_t id);                // 0x006505d0
    bool SelectAsset(const ResourceKey* key, bool a, bool b, bool c);   // 0x00655840
    void ResetScroll();                                          // 0x0064e5b0
    void Repopulate();                                           // 0x0064f310
    void SetAssetList(AssetList* list);                          // 0x00656310
    void SetFeed(struct cBrowserConfig* config, cSPUIFeedListItem* item);       // 0x00654730
    void ShowItem(struct cBrowserConfig* config, cSPUIFeedListItem* item);      // 0x00654f50
};

struct ConfigMapIterator { void* mpNode; };
struct ConfigMap {                   // eastl::map<ResourceKey, ...>
    uint32_t mCompare;
    uint32_t mAnchor[5];
    ConfigMapIterator find(const ResourceKey& key);              // 0x00a21dc0
};

struct QueryKey {                    // ResourceKey + extra flag, 16 bytes
    ResourceKey key;
    uint32_t flags;
};

struct cBrowserConfig {
    uint32_t pad0[0x48 / 4];
    ConfigMap mConfigs;                                          // +0x48
    void SetQuery(const QueryKey* q, int flags);                 // 0x00643f70
    void SetQueryKey(const ResourceKey* key);                    // 0x006435e0
    void SetAssets(AssetList* list, int flags);                  // 0x00644550
};

// ---- stack messages ----------------------------------------------------------------
struct BrowserMessage {              // id 0xb3d53f95
    uint32_t pad0[3];
    uint32_t mFeedItemID;            // +0x0c
    cSPUIFeedListItem* mpItem;       // +0x10
    bool mbByIndex;                  // +0x14
    bool mbForceReset;               // +0x15
    uint16_t pad16;
    explicit BrowserMessage(uint32_t feedItemID);               // 0x00666af0
    explicit BrowserMessage(cSPUIFeedListItem* item);           // 0x00666a60
    ~BrowserMessage();                                          // 0x00644ff0
};

template<typename T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(T* p);                              // 0x00b5f950
    T* get() const { return mpObject; }
};

struct cRefFeedListItem : cSPUIFeedListItem {};
struct RefItem { virtual void AddRef(); virtual void Release(); };

struct SelectItemMessage {           // id 0x3b60b3ad, 0x20 bytes
    uint32_t pad0[3];
    AutoRefCount<RefItem> mpItem;    // +0x0c
    ResourceKey mKey;                // +0x10
    bool mbHasQueryFlags;            // +0x1c
    uint8_t pad1d;
    uint16_t pad1e;
    SelectItemMessage(cSPUIFeedListItem* item, const ResourceKey* key, int flags);   // 0x00644a80
    ~SelectItemMessage();                                       // 0x00644af0
};

struct AssetPollinatedMessage {      // id 0x068cd252
    bool mbSuccess;                  // +0x00
    uint8_t pad1[3];
    ResourceKey mKey;                // +0x04
};

struct DialogResultMessage {         // id 0x1dd7bda9
    int mResult;
    ITypedObject* mpDialog;
};

struct EventMessage {                // id 0x54495773
    uint8_t pad0[0x33];
    uint8_t mBrowserIndex;           // +0x33
};

// ---- the browser -------------------------------------------------------------------
struct IHandlerBase { virtual void h0(); };
struct IModalWindowCallback { virtual void m0(); };

class cSPUIAssetBrowser : public IHandlerBase, public IModalWindowCallback {
public:
    uint32_t pad08[5];
    bool mIsVisible;                         // +0x1c
    uint8_t pad1d[0xc];
    uint8_t mBrowserIndex;                   // +0x29
    bool mbIsForEditor;                      // +0x2a
    uint8_t pad2b[0x15];
    uint32_t mCardWindows[4];                // +0x40
    uint32_t pad50[5];
    IAssetDataList* mpAssetListData;         // +0x64
    uint32_t pad68[10];
    IVisibleObject* mpLargeViewA;            // +0x90
    IVisibleObject* mpLargeViewB;            // +0x94
    IVisibleObject* mpSporeGuideView;        // +0x98
    uint32_t pad9c[7];
    cBrowserConfig* mpConfig;                // +0xb8
    cSPUIAssetGrid* mpAssetGrid;             // +0xbc
    cSPUIFeedList* mpFeedList;               // +0xc0
    cSPUIFeedEdit* mpFeedEditor;             // +0xc4
    uint32_t padc8;
    uint8_t* mSelectionBegin;                // +0xcc  (vector of 20-byte entries)
    uint8_t* mSelectionEnd;                  // +0xd0
    uint32_t padd4[0x21];
    IBoolQuery* mpFilterPanel;               // +0x158
    uint32_t pad15c[8];
    uint32_t mCallToAction;                  // +0x17c
    uint32_t pad180[0x12];
    bool mbLockSelection;                    // +0x1c8
    uint8_t pad1c9[0x17];
    uint32_t mPendingButton;                 // +0x1e0
    uint32_t mFeedOverride;                  // +0x1e4
    uint32_t mConfigOverride;                // +0x1e8
    uint8_t pad1ec;
    bool mbForceReset;                       // +0x1ed
    uint8_t pad1ee[0x22];
    uint32_t mCurrentWebURL;                 // +0x210
    uint32_t pad214[2];
    cSPUIAssetWebBrowser* mpWebBrowserA;     // +0x21c
    cSPUIAssetWebBrowser* mpWebBrowserB;     // +0x220
    cSPUISporeGuidePage* mpSporeGuide;       // +0x224
    AutoRefCount<cRefFeedListItem> mpCurrentItem;   // +0x228
    uint32_t pad22c[2];
    bool mbLaunchingEditor;                  // +0x234
    bool mbEnteringEditor;                   // +0x235
    uint8_t pad236[0x17];
    bool mbPublishAllowed;                   // +0x24d
    bool mbAwaitingPollination;              // +0x24e
    bool mbPublishBlocked;                   // +0x24f

    bool HandleMessage(uint32_t messageID, void* pMessage);

    // out-of-line members called from here
    void ShowPublishDialog();                                    // 0x00645e20
    void OnRefresh();                                            // 0x0064c6b0
    void LaunchEditorEnd();                                      // 0x0064acd0
    void OnLayoutChanged();                                      // 0x00645260
    void SetLargeCardState(bool show, uint32_t id);              // 0x00644d10
    void ShowLargeCard(bool show, uint32_t a, uint32_t b);       // 0x00644c50
    void SetLargeCardVisibility(bool a, bool b, bool c);         // 0x006478c0
    void Update();                                               // 0x0064ab20
    void OnTabChanged();                                         // 0x00644a40
    uint32_t GetSelectedID();                                    // 0x006452c0
    IKeySource* GetSelectedAsset();                              // 0x00645300
    void FilterGridEntries(void* filter);                        // 0x00648d90
    void ClosePollinationUI(int a);                              // 0x00644e20
    bool IsWebPageShown();                                       // 0x00644dd0
    void SetWebBrowserVisibility(bool visible, const wchar_t* url);   // 0x00644b90
    void OnEditorChosen();                                       // 0x0064c0d0
    int CanLaunchEditor();                                       // 0x00645cc0
    void SetVisibility(int a, int b, int c);                     // 0x0064a400
    void HandleEvent(void* pMsg);                                // 0x0064b6b0

    __forceinline void HideLargeViewA();
    __forceinline void HideLargeViewB();
};

// ---- free functions ----------------------------------------------------------------
IAuthManager* AuthManager();                                     // 0x00607a60
IMessageServer* MessageServer();                                 // 0x0067dcc0
IRenderView* RenderView();                                       // 0x0067dd40
cCaptureJob* CaptureJob();                                       // 0x0067dda0
ICameraManager* CameraManager();                                 // 0x0067dd50
IGameModeManager* GameModeManager();                             // 0x0067dd10
cSPUILayoutCollection* LayoutCollection();                       // 0x0067cab0
SporeGuideState* SporeGuide();                                   // 0x00401040
cSPUIAssetBrowser* AssetBrowser();                               // 0x00401030
uint32_t GetRecorderState();                                     // 0x00435e90
void KillSetiEffects(uint32_t id, uint32_t state);               // 0x00435ed0
uint32_t SPIDFromName(const char* name);                         // 0x00571cf0
void CalloutMessageBox(IModalWindowCallback* cb, const ResourceKey* key);   // 0x00809db0
bool KeysEqual(const ResourceKey* a, const ResourceKey* b);      // 0x004eb930
bool GetCreatorType(const ResourceKey* key);                     // 0x00641900
IUpdatable* UpdateSaveAreas(const ResourceKey* key);             // 0x006b22a0
void GetFeedEntries(uint32_t feedID, FeedEntryVector* out);      // 0x00661900
bool SetAssetData(uint32_t id, bool b);                          // 0x004bbe20

extern AppProperties* sAppProperties;                            // 0x015fd918
extern const ResourceKey kPollinateFailedDialog;                 // 0x01525840
extern const ResourceKey kConfirmDialogA;                        // 0x015258b8
extern const ResourceKey kConfirmDialogB;                        // 0x015258c4

__forceinline void cSPUIAssetBrowser::HideLargeViewA() {
    AuthManager()->IsLoggedIn();
    if (mpAssetListData) {
        IVisibleObject* view = mpAssetListData->FindView(0x561e0a8, true);
        if (view)
            view->SetVisible(true, false);
    }
    if (mpLargeViewA)
        mpLargeViewA->SetVisible(true, false);
    if (mpWebBrowserA)
        mpWebBrowserA->SetActive(false);
}

__forceinline void cSPUIAssetBrowser::HideLargeViewB() {
    AuthManager()->IsLoggedIn();
    if (mpAssetListData) {
        IVisibleObject* view = mpAssetListData->FindView(0x561e0a8, true);
        if (view)
            view->SetVisible(true, false);
    }
    if (mpLargeViewB)
        mpLargeViewB->SetVisible(true, false);
    if (mpWebBrowserB)
        mpWebBrowserB->SetActive(false);
}

// @ 0x0064c8e0
bool cSPUIAssetBrowser::HandleMessage(uint32_t messageID, void* pMessage) {
    switch (messageID) {
    case 0x044edd9c:
        if (mIsVisible) {
            IRenderView* view = RenderView();
            if (view) {
                Viewport viewport;
                viewport.x = -1;
                viewport.y = -1;
                view->GetViewport(&viewport);
                cCaptureJob* job = CaptureJob();
                if (job)
                    job->Capture(&viewport);
            }
        }
        break;

    case 0x044db12e:
        if (pMessage && mbPublishAllowed && !mbPublishBlocked)
            ShowPublishDialog();
        break;

    case 0x0141a7b3:
        OnRefresh();
        break;

    case 0x0462c656:
        if (mbLaunchingEditor)
            LaunchEditorEnd();
        break;

    case 0x05132389:
        if (*(uint32_t*)pMessage && mpCurrentItem.get() && mIsVisible) {
            BrowserMessage msg(mpCurrentItem.get()->mItemID);
            MessageServer()->MessageSend(0xb3d53f95, &msg, 0);
        }
        break;

    case 0x05a86fa1:
        if (mpCurrentItem.get())
            OnLayoutChanged();
        break;

    case 0x05b96086:
    case 0x05b98f52:
    case 0x05c5594a:
        mbPublishAllowed = false;
        break;

    case 0x05bd6378:
        mbPublishBlocked = true;
        break;

    case 0x05dd52c7:
        mbPublishBlocked = false;
        if (mbPublishAllowed)
            ShowPublishDialog();
        break;

    case 0x05de7b4a:
        if (!mIsVisible && mpFeedList)
            mPendingButton = 0;
        break;

    case 0x05e7cb29:
        if (mCallToAction)
            CameraManager()->SetMode(0x16, 2);
        break;

    case 0x06134914: {
        cSPUIFeedListItem* item = (cSPUIFeedListItem*)pMessage;
        if (item->mItemType == 0x11f44f6b) {
            HideLargeViewA();
            HideLargeViewB();
            if (mpSporeGuideView)
                mpSporeGuideView->SetVisible(true, false);
            SetLargeCardState(true, item->mFeedArg);
        }
        break;
    }

    case 0x06255f5e: {
        uint32_t id = *(uint32_t*)pMessage;
        if (id) {
            cSPUIFeedListItem* item = mpFeedList->FindItemByIndex(id);
            if (item && item->mItemType == 0x11f44f6b) {
                BrowserMessage msg(item);
                MessageServer()->MessageSend(0xb3d53f95, &msg, 0);
                HideLargeViewA();
                if (mpSporeGuideView)
                    mpSporeGuideView->SetVisible(true, false);
                HideLargeViewB();
                SetLargeCardState(true, id);
            }
        }
        break;
    }

    case 0x0639cceb:
        if (pMessage && mpFeedEditor)
            mpFeedEditor->OnEvent(pMessage);
        break;

    case 0x062d7860:
        KillSetiEffects(0x2ddb6155, GetRecorderState());
        HideLargeViewB();
        break;

    case 0x06299932:
        if (pMessage) {
            uint32_t a = ((uint32_t*)pMessage)[0];
            uint32_t b = ((uint32_t*)pMessage)[1];
            if (mpSporeGuideView)
                mpSporeGuideView->SetVisible(true, false);
            ShowLargeCard(true, a, b);
        }
        break;

    case 0x066fcce4: {
        cSPUIFeedList* feedList = mpFeedList;
        cSPUIFeedListItem* item = feedList->FindItem(SPIDFromName("Feed_RecentDownloads"));
        if (item)
            item->SetSelected(true);
        break;
    }

    case 0x068cd252: {
        if (!mIsVisible)
            break;
        AssetPollinatedMessage* msg = (AssetPollinatedMessage*)pMessage;
        if (!msg)
            break;
        ResourceKey key;
        key.instance = 0;
        key.type = 0;
        key.group = 0;
        if (GetSelectedAsset())
            key = *GetSelectedAsset()->GetKey();
        if (KeysEqual(&key, &msg->mKey) && mbAwaitingPollination) {
            ClosePollinationUI(0);
            if (mCardWindows[0] | mCardWindows[1]) {
                LayoutCollection()->Hide();
                mCardWindows[0] = 0;
                mCardWindows[1] = 0;
                mCardWindows[2] = 0;
                mCardWindows[3] = 0;
            }
            if (msg->mbSuccess) {
                if (GetCreatorType(&key)) {
                    if (mbIsForEditor) {
                        if (mpFeedList) {
                            BrowserMessage m(mpCurrentItem.get());
                            MessageServer()->MessageSend(0xb3d53f95, &m, 0);
                        }
                    } else {
                        SetLargeCardVisibility(false, false, false);
                        SetLargeCardVisibility(true, false, false);
                    }
                }
            } else {
                CalloutMessageBox(this, &kPollinateFailedDialog);
            }
            if (key.instance && key.group) {
                IUpdatable* p = UpdateSaveAreas(&key);
                if (p)
                    p->Update();
            }
            mbAwaitingPollination = false;
            break;
        }
        if (!mbIsForEditor || !mpFeedList)
            break;
        cSPUIFeedListItem* item = mpCurrentItem.get();
        if (!item)
            break;
        cBrowserConfig* config = mpConfig;
        if (!config || !mpAssetGrid)
            break;
        if (item->mItemType == 0x11f44f6b) {
            if (config->mConfigs.find(key).mpNode == (void*)&config->mConfigs.mAnchor)
                break;
            SelectItemMessage m(item, &msg->mKey, 0);
            MessageServer()->MessageSend(0x3b60b3ad, &m, 0);
            mpAssetGrid->ResetScroll();
            m.mbHasQueryFlags = true;
            MessageServer()->MessageSend(0x3b60b3ad, &m, 0);
        } else if (item->mItemType == 0xe8104769) {
            BrowserMessage m(item);
            MessageServer()->MessageSend(0xb3d53f95, &m, 0);
        }
        break;
    }

    case 0x148f5c9d:
        if (mpCurrentItem.get())
            OnTabChanged();
        break;

    case 0x14ac4938:
        KillSetiEffects(0x2ddb6155, GetRecorderState());
        SetLargeCardVisibility(false, false, false);
        if (mbIsForEditor) {
            if (mpAssetGrid && mpAssetGrid->mbIsEditorGrid && GetSelectedID() && GetSelectedAsset()) {
            ResourceKey key;
            key.instance = 0;
            key.type = 0;
            key.group = 0;
            ResourceKey entryKey;
            entryKey.instance = 0;
            entryKey.type = 0;
            entryKey.group = 0;
            key = *GetSelectedAsset()->GetKey();
            mpAssetGrid->GetEntryByID(GetSelectedID());
            FilterGridEntries(0);
            if (!mpAssetGrid->SelectAsset(&entryKey, false, true, false))
                mpAssetGrid->SelectAsset(&key, false, true, false);
            }
        } else {
            Update();
        }
        break;

    case 0x1dd7bda9: {
        DialogResultMessage* msg = (DialogResultMessage*)pMessage;
        if (!msg || !msg->mpDialog)
            break;
        bool accepted = msg->mResult == 1;
        if (msg->mpDialog->GetType() == 0x3ffd6b1) {
            if (accepted) {
            send_refresh:
                BrowserMessage m(0xe2415c7d);
                MessageServer()->MessageSend(0xb3d53f95, &m, 0);
                MessageServer()->MessageSend(0x53dd093, 0, 0);
                break;
            }
            CalloutMessageBox(this, &kConfirmDialogA);
        } else if (msg->mpDialog->GetType() == 0x3cf01e6) {
            if (accepted)
                goto send_refresh;
            CalloutMessageBox(this, &kConfirmDialogB);
        }
        break;
    }

    case 0x3b60b3ad: {
        SelectItemMessage* msg = (SelectItemMessage*)pMessage;
        cSPUIFeedListItem* item =
            (cSPUIFeedListItem*)(msg ? msg->mpItem : AutoRefCount<RefItem>()).get();
        if (msg && item && item == mpCurrentItem.get() && !mbLockSelection &&
            item->mItemType != 0x49daa92a && !item->mWebURL && !item->mSporeGuidePage &&
            mpConfig && mpAssetGrid) {
            if (msg->mbHasQueryFlags) {
                QueryKey q;
                q.key = msg->mKey;
                q.flags = 0;
                mpConfig->SetQuery(&q, 0);
            } else {
                mpConfig->SetQueryKey(&msg->mKey);
            }
            mpAssetGrid->ShowItem(mpConfig, item);
        }
        return false;
    }

    case 0x54495773: {
        EventMessage* msg = (EventMessage*)pMessage;
        if (mIsVisible && mpFeedList && msg && msg->mBrowserIndex == mBrowserIndex)
            HandleEvent(msg);
        break;
    }

    case 0x94174b89:
        if (pMessage)
            FilterGridEntries(pMessage);
        break;

    case 0xb3d53f95: {
        if (!mIsVisible || !mpFeedList)
            break;
        BrowserMessage* msg = (BrowserMessage*)pMessage;
        if (!msg)
            break;
        if (!mBrowserIndex && SporeGuide()->mbVisible)
            break;
        bool webPageShown = IsWebPageShown();
        HideLargeViewA();
        HideLargeViewB();
        if (mpSporeGuideView)
            mpSporeGuideView->SetVisible(true, false);
        SetLargeCardState(false, 0);

        cSPUIFeedListItem* item = msg->mpItem;
        if (!item) {
            if (msg->mbByIndex)
                item = mpFeedList->FindItemByIndex(msg->mFeedItemID);
            else
                item = mpFeedList->FindItem(msg->mFeedItemID);
        }
        AssetList assets;
        if (item) {
            mCurrentWebURL = (uint32_t)item->mWebURL;
            if (item->mItemType == 0x49daa92a) {
                bool loggedIn = AuthManager()->IsLoggedIn();
                if (mpAssetListData) {
                    IVisibleObject* view = mpAssetListData->FindView(0x561e0a8, true);
                    if (view)
                        view->SetVisible(true, loggedIn);
                }
                if (mpFeedEditor) {
                    if (!loggedIn) {
                        mpFeedEditor->SetEditActive(true);
                        mpFeedEditor->Refresh();
                    } else {
                        mpFeedEditor->SetEditActive(false);
                    }
                }
            } else if (item->mWebURL) {
                SetWebBrowserVisibility(true, item->mWebURL);
                goto update_grid;
            } else if (item->mSporeGuidePage) {
                if (mpSporeGuideView) {
                    mpSporeGuideView->SetVisible(true, true);
                    mpSporeGuide->LoadSporeGuidePage(item->mSporeGuidePage);
                }
            } else {
                if (mpAssetGrid) {
                    uint32_t feedID = mFeedOverride;
                    if (!feedID)
                        feedID = item->mFeedID;
                    uint32_t configID = mConfigOverride;
                    if (!configID)
                        configID = item->mConfigID;
                    bool reset = msg->mbForceReset || mbForceReset;
                    mbForceReset = false;
                    IDSet ids;
                    if (feedID != item->mFeedID) {
                        FeedEntryVector entries;
                        GetFeedEntries(item->mFeedID, &entries);
                        ids.reserve(entries.size());
                        for (uint32_t i = 0; i < entries.size(); ++i) {
                            if (entries.mpBegin[i].mID)
                                ids.insert(entries.mpBegin[i].mID);
                        }
                    }
                    cAssetFilterPreview* preview = mpAssetGrid->mpFilterPreview;
                    if (preview) {
                        preview->SetFeedFilter(&ids);
                        preview->Apply(feedID, configID, !reset);
                    }
                    if (reset)
                        mpAssetGrid->Repopulate();
                }
                item->GetAssetList(&assets);
            }
        }
        if (webPageShown && mpWebBrowserA)
            mpWebBrowserA->ClearPage();
    update_grid:
        if (mpConfig && mpAssetGrid) {
            bool haveKeys = false;
            bool filterActive = false;
            ResourceKey key;
            key.instance = 0;
            key.type = 0;
            key.group = 0;
            ResourceKey entryKey;
            entryKey.instance = 0;
            entryKey.type = 0;
            entryKey.group = 0;
            if ((mSelectionEnd - mSelectionBegin) / 20 == 1 && GetSelectedID() && GetSelectedAsset()) {
                key = *GetSelectedAsset()->GetKey();
                const ResourceKey* entry = mpAssetGrid->GetEntryByID(GetSelectedID());
                if (entry)
                    entryKey = *entry;
                haveKeys = true;
            }
            if (mpFilterPanel && mpFilterPanel->IsActive())
                filterActive = true;
            FilterGridEntries(0);
            mpAssetGrid->SetAssetList(&assets);
            mpConfig->SetAssets(&assets, 0);
            mpAssetGrid->SetFeed(mpConfig, item);
            if (haveKeys && !mpAssetGrid->SelectAsset(&entryKey, filterActive, true, false))
                mpAssetGrid->SelectAsset(&key, filterActive, true, false);
        }
        mpCurrentItem = (cRefFeedListItem*)item;
        break;
    }

    case 0xbf7280e2:
        if (AssetBrowser() && AssetBrowser()->CanLaunchEditor()) {
            mbEnteringEditor = true;
            if (sAppProperties->mpInner->mValue && GameModeManager()->GetActiveModeID() == 0xdbdba1) {
                MessageServer()->MessageSend(0x56d39e9, 0, 0);
                mbEnteringEditor = false;
                AssetBrowser()->SetVisibility(0, 0, 0);
            } else {
                OnEditorChosen();
            }
        }
        break;

    case 0xcadf3aca: {
        ResourceKey key = *(ResourceKey*)pMessage;
        if (!mpAssetGrid->SelectAsset(&key, true, true, false) && SetAssetData(key.type, true)) {
            BrowserMessage m(0xe2415c7d);
            MessageServer()->MessageSend(0xb3d53f95, &m, 0);
            mpAssetGrid->SelectAsset(&key, true, true, false);
        }
        break;
    }
    }
    return true;
}
