// Slice s0066daf0: SP::cSPUILargeAssetView::LoadAssetViewLarge (0x66daf0, 4924 bytes).
// Sporepedia large asset card: finds every child window of the card layout, creates the
// comment/expansion/verb/zoom helpers, positions the title/author widgets, loads the asset's
// resource, builds the verb tray and the preview swatch.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-, no /EHsc (the string16 local has no EH frame).
//
// Layout: retail class matches ModAPI Sporepedia::cSPUILargeAssetView (size 0xCC).
#include "types.h"

// EA allocator form: new("UI", 0, 0, 0, 0) T()
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);
void operator delete[](void* p);

namespace SP {

struct ResourceKey {
    uint32_t instanceID, typeID, groupID;
    ResourceKey(uint32_t i = 0, uint32_t t = 0, uint32_t g = 0) : instanceID(i), typeID(t), groupID(g) {}
};

struct Rect {
    float x1, y1, x2, y2;
    Rect(const Rect& r) : x1(r.x1), y1(r.y1), x2(r.x2), y2(r.y2) {}
    Rect& operator=(const Rect& r) { x1 = r.x1; y1 = r.y1; x2 = r.x2; y2 = r.y2; return *this; }
};

struct Point {
    float x, y;
    Point(float ax, float ay) : x(ax), y(ay) {}
};

// ------------------------------------------------------------------ interfaces
struct IWindow {
    virtual int AddRef();                                   // 0x00
    virtual int Release();                                  // 0x04
    virtual void v08();
    virtual void* Cast(uint32_t typeID);                    // 0x0C
    virtual IWindow* GetParent();                           // 0x10
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20();
    virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30();
    virtual const Rect& GetArea();                          // 0x34
    virtual const Rect& GetRealArea();                      // 0x38
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
    virtual void v4c(); virtual void v50(); virtual void v54(); virtual void v58();
    virtual void v5c(); virtual void v60();
    virtual void SetLocation(float x, float y);             // 0x64
    virtual void v68();
    virtual void SetLayoutArea(const Rect& area);           // 0x6C
    virtual void v70(); virtual void v74();
    virtual void SetCursorID(uint32_t id);                  // 0x78
    virtual void SetFlag(int flag, bool value);             // 0x7C
    virtual void SetCaption(const wchar_t* caption);        // 0x80
    virtual void v84(); virtual void v88(); virtual void v8c(); virtual void v90();
    virtual void v94(); virtual void v98(); virtual void v9c(); virtual void va0();
    virtual void va4(); virtual void va8(); virtual void vac(); virtual void vb0();
    virtual void vb4(); virtual void vb8(); virtual void vbc(); virtual void vc0();
    virtual void vc4(); virtual void vc8(); virtual void vcc(); virtual void vd0();
    virtual void vd4(); virtual void vd8(); virtual void vdc(); virtual void ve0();
    virtual void ve4(); virtual void ve8(); virtual void vec(); virtual void vf0();
    virtual void vf4(); virtual void vf8(); virtual void vfc(); virtual void v100();
    virtual void AddWinProc(void* winProc);                 // 0x104
};

struct cSPUILayout {
    IWindow* FindWindowByID(uint32_t id, bool recursive);   // 008105B0
};

struct ICastable {
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual void* Cast(uint32_t typeID);                    // 0x0C
};

struct string16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    string16();
    ~string16();
    const wchar_t* c_str() const { return mpBegin; }
};
extern wchar_t gEmptyString16[1];                           // 01667BAC
inline string16::string16() : mpBegin(gEmptyString16), mpEnd(gEmptyString16), mpCapacity(gEmptyString16 + 1) {}
inline string16::~string16() {
    if ((mpCapacity - mpBegin) > 1 && mpBegin)
        operator delete[](mpBegin);
}

struct IAssetData {
    virtual int AddRef();                                   // 0x00
    virtual int Release();                                  // 0x04
    virtual void v08();
    virtual const wchar_t* GetName();                       // 0x0C
    virtual const wchar_t* GetAuthor();                     // 0x10
    virtual const wchar_t* GetDescription();                // 0x14
    virtual void v18(); virtual void v1c();
    virtual void GetTags(string16& out);                    // 0x20
    virtual uint32_t GetModelType();                        // 0x24
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual int GetParentID();                              // 0x38
    virtual float GetSize();                                // 0x3C
    virtual const ResourceKey* GetKey();                    // 0x40
    virtual void v44(); virtual void v48(); virtual void v4c(); virtual void v50();
    virtual void v54(); virtual void v58(); virtual void v5c(); virtual void v60();
    virtual bool HasVerbs();                                // 0x64
    virtual void v68(); virtual void v6c();
    virtual bool IsPublished();                             // 0x70

    uint32_t pad04[3];
    ICastable mObject;                                      // +0x10
};

struct cPlayableAsset {
    bool IsPlayable();                                      // 006418E0
};

struct cAssetMetadata {
    uint64_t GetAssetKey();                                 // 005508A0
};

struct IAuthManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20();
    virtual bool IsOffline();                               // 0x24
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual void v3c();
    virtual uint64_t GetUserID();                           // 0x40
};

struct cDownloadEntry {                                     // 0x70 bytes
    uint32_t pad00[4];
    uint64_t mAssetKey;                                     // +0x10
    uint32_t pad18[(0x68 - 0x18) / 4];
    int      mState;                                        // +0x68
    uint32_t pad6c;
};

struct cDownloadList {
    cDownloadEntry* mpBegin;
    unsigned size();                                        // 0065B160
};

struct cDownloadManager {
    uint32_t pad00[0xc8 / 4];
    cDownloadList mList;                                    // +0xC8
};

struct ResourceObject {
    virtual int AddRef();
    virtual int Release();
};

struct IResourceManager {
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual bool GetResource(const ResourceKey& key, ResourceObject** ppOut,
                             int a, int b, int c, int d);   // 0x0C
};

struct cPropertyList {
    virtual int AddRef();
    virtual int Release();
};

struct IPropertyManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, cPropertyList** ppOut); // 0x2C
};

struct IModelManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20();
    virtual void SetPreviewModel(int model);                // 0x24
};

struct cDirectValues {
    uint32_t pad[0x118 / 4];
    int mOfflineMode;                                       // +0x118
};

struct cDirectPropertyList {
    uint32_t pad[0x3c / 4];
    cDirectValues* mpValues;                                // +0x3C
    bool GetDescription(uint32_t propertyID);               // 006A25A0
    float GetFloatProperty(uint32_t propertyID);            // 006A2710
};
extern cDirectPropertyList* gAppProperties;                 // 015FD918

// --------------------------------------------------------------- owned objects
struct cSPUIAssetComments {
    virtual int AddRef();
    virtual int Release();
    cSPUIAssetComments();                                   // 0064E170
    void Init(IWindow* window);                             // 0064E230
    uint32_t pad04[(0x78 - 4) / 4];
};

struct cSPUIMissingExpansionPackPage {
    virtual int AddRef();
    virtual int Release();
    cSPUIMissingExpansionPackPage();                        // 006715D0
    void Init(IWindow* window);                             // 00671690
    uint32_t pad04[(0x78 - 4) / 4];
};

struct cSPCardInventory {
    virtual int AddRef();
    virtual int Release();
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18();
    virtual void Show();                                    // 0x1C
    cSPCardInventory();                                     // 005994D0
    void SetMessageID(uint32_t id, int value);              // 00827FA0
    uint32_t pad04[(0xb0 - 4) / 4];
};

struct cSPCardStats {
    virtual int AddRef();
    virtual int Release();
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1c();
    virtual void Load(cSPUILayout* layout, cAssetMetadata* metadata);   // 0x20
    cSPCardStats();                                         // 006700D0
    uint32_t pad04[(0xd0 - 4) / 4];
};

struct cSPUIAssetVerbs {
    virtual int AddRef();
    virtual int Release();
    cSPUIAssetVerbs();                                      // 00656B00
    void Init(IWindow* window);                             // 00656B80
    uint32_t pad04[(0x5c - 4) / 4];
};

struct TextZoomName {
    TextZoomName();                                         // 008345C0
    void SetTargetWindow(void* window, int a, int b, int c, ResourceKey key);  // 00834FA0
    uint32_t pad00[0x78 / 4];
};

struct cVerbIconSlot {
    uint32_t GetSoundID();                                  // 01137690
    float GetSize();                                        // 00885D10
};

struct cVerbTrayBase {
    virtual int AddRef();
    virtual int Release();
    virtual void v08(); virtual void v0c();
    virtual void Load(IWindow* window, ResourceKey key, int keys, int count, int flags); // 0x10
    virtual void v14();
    virtual void Clear();                                   // 0x18
    int GetIconCount();                                     // 00605930
    float GetHeight();                                      // 006058B0
    cVerbIconSlot* GetSlot(int index);                      // 005C1CE0
};

struct cSPVerbTray : cVerbTrayBase {
    cSPVerbTray();                                          // 005E0CF0
    uint32_t pad04[(0xbc - 4) / 4];
};

struct cSPSporepediaVerbTray : cVerbTrayBase {
    cSPSporepediaVerbTray();                                // 005E8920
    uint32_t pad04[(0x54 - 4) / 4];
};

struct cSwatchModel {
    int GetModel();                                         // 005F2770
};

struct cSPSwatch {
    virtual int AddRef();
    virtual int Release();
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28();
    virtual void SetActive(bool active);                    // 0x2C
    uint32_t pad04[3];
    cSwatchModel mModel;                                    // +0x10
    char pad14[0x163 - 0x14];
    bool mIsAnimated;                                       // +0x163

    void Init(const ResourceKey& key, IWindow* window, int a, int b, int c, int d, uint32_t modelType); // 005F4F80
    void SetUpdating(int value);                            // 005F2260
    void SetEditorCameraController(int value);              // 005F6500
};

struct cSPSwatchManager {
    cSPSwatch* CreateSwatch(int flags);                     // 005F0CA0
};

// Small ref-counted rollover animation helper (inline ctor, 0x20 bytes).
struct cCardRollover {
    virtual ~cCardRollover();
    int   mnRefCount;   // +0x04
    int   field_08;
    int   field_0c;
    int   field_10;
    int   field_14;
    float mSpeedIn;     // +0x18
    float mSpeedOut;    // +0x1C

    cCardRollover() : mnRefCount(0), field_08(0), field_0c(0), field_10(0), field_14(0),
                      mSpeedIn(0.01f), mSpeedOut(0.02f) {}
    int AddRef() { return ++mnRefCount; }
    int Release() {
        if (--mnRefCount == 0) {
            mnRefCount = 1;
            delete this;
            return 0;
        }
        return mnRefCount;
    }
    void Attach(cSPUILayout* layout);                       // 0066BD80
};

// ----------------------------------------------------------- smart pointers
template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(T* pObject) {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    void Reset() {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
    }
    T** AsPPTypeParam() {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};

// Instances whose assignment / AsPPTypeParam were emitted out of line.
template <class T> struct AutoRefCountOOL {
    T* mpObject;
    AutoRefCountOOL() : mpObject(0) {}
    ~AutoRefCountOOL() { if (mpObject) mpObject->Release(); }
    AutoRefCountOOL& operator=(T* pObject);                 // 00B5F950
    T** AsPPTypeParam();                                    // 00A16F40
    __forceinline void Reset() {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};

struct TextZoomPtr {
    TextZoomName* mpObject;
    TextZoomPtr& operator=(TextZoomName* p);                // 00572620
    TextZoomName* operator->() const { return mpObject; }
};

// ---------------------------------------------------------------- free helpers

namespace SPUIHelpers {
void __cdecl SetWindowAreaToParent(IWindow* window);                      // 00806BF0
void __cdecl AutoSizeWindowForText(IWindow* window, int a, int b);        // 00806E40
void __cdecl CenterWindow(IWindow* window, Point center);                 // 00806CA0
}
IAuthManager* __cdecl AuthManager();                                      // 00607A60
cDownloadManager* __cdecl DownloadManager();                              // 0067CB30
IResourceManager* __cdecl ResourceManager();                              // 0067DCD0
IPropertyManager* __cdecl PropertyManager();                              // 0067DE30
IModelManager* __cdecl ModelManager();                                    // 0067DD80
cSPSwatchManager* __cdecl SwatchManager();                                // 00401020
struct cAssetBrowser { uint32_t pad[0x1cc / 4]; uint32_t mFilterModelType; };
cAssetBrowser* __cdecl AssetBrowser();                                    // 00401030
int __cdecl GetEditorForModelType(uint32_t modelType);                    // 004BB860
void __cdecl GetVerbIconKeysForLargeCard(uint32_t modelType, float size,
                                          ResourceKey* verbKey, ResourceKey* layoutKey); // 0066CD20
void __cdecl GetPropertyArrayKeys(cPropertyList* props, uint32_t id, int* count, int* keys); // 006A0AE0
bool __cdecl GetBoolProperty(cPropertyList* props, uint32_t id, bool& out);   // 00407190
bool __cdecl GetPropertyAsKeyInstance(cPropertyList* props, uint32_t id, uint32_t* out); // 006A12A0
bool __cdecl ComputeVerbIcons(const ResourceKey* key, ResourceObject** ppOut);           // 004BAFC0
int __cdecl GetCreatureCaps(uint32_t modelType);                          // 004D1370
void __cdecl FillCreatureVerbTray(ResourceObject* res, cVerbTrayBase* tray, int caps, float size); // 004E87F0
struct cEditorResource;
cEditorResource* __cdecl interface_cast_EditorResource(const AutoRefCount<ResourceObject>& res); // 00421EB0
void __cdecl FillBuildingVerbTray(cEditorResource* res, cVerbTrayBase* tray);   // 004E6C10
void __cdecl FillVehicleVerbTray(cEditorResource* res, cVerbTrayBase* tray);    // 004E7E50
void __cdecl FillUFOVerbTray(cEditorResource* res, cVerbTrayBase* tray);        // 004E7DA0
int __cdecl GetAssetKeyType(const ResourceKey* key);                      // 00552300
uint32_t __cdecl RemapTypeId(uint32_t modelType);                         // 00432F10
void __cdecl KillSetiEffects(uint32_t instanceID, uint32_t groupID);      // 00435ED0
void __cdecl PlayEditorSound(uint32_t id, uint32_t param, float value, int flags); // 00435F40
void __cdecl SetShaderParam(int index, float* value, int count);          // 00777AE0
extern uint32_t gCardInventoryParam;                                      // 01527E74
extern uint32_t gEditorConfigGroupID;                                     // 01527DA4

// ------------------------------------------------------------------- the view
struct cSPUILargeAssetView {
    uint32_t pad00[6];
    cSPUILayout* mLayout;                                   // +0x18
    AutoRefCount<IWindow> mWinParent;                       // +0x1C
    AutoRefCount<IWindow> mWinRoot;                         // +0x20
    AutoRefCount<IWindow> mWinBakingArea;                   // +0x24
    AutoRefCount<IWindow> mWin28;                           // +0x28
    AutoRefCount<IWindow> mWinRenderWindow;                 // +0x2C
    AutoRefCount<IWindow> mWin30;                           // +0x30
    AutoRefCount<IWindow> mWinName;                         // +0x34
    AutoRefCount<IWindow> mWinAuthor;                       // +0x38
    AutoRefCount<IWindow> mWinDescription;                  // +0x3C
    AutoRefCount<IWindow> mWinTags;                         // +0x40
    AutoRefCount<IWindow> mWinVerbContainer;                // +0x44
    AutoRefCount<IWindow> mWinBakingForeground;             // +0x48
    AutoRefCount<IWindow> mWinPublished;                    // +0x4C
    AutoRefCount<IWindow> mWinShare;                        // +0x50
    AutoRefCount<IWindow> mWinShareIcon;                    // +0x54
    AutoRefCount<IWindow> mWinDownloaded;                   // +0x58
    AutoRefCount<IWindow> mWin5c;                           // +0x5C
    AutoRefCountOOL<cSPUIAssetComments> mCommentsBrowser;   // +0x60
    AutoRefCount<cSPUIMissingExpansionPackPage> mExpansionPackBrowser; // +0x64
    AutoRefCountOOL<cVerbTrayBase> mVerbIcons;                // +0x68
    AutoRefCount<IWindow> mWinAssetVerbs;                   // +0x6C
    AutoRefCount<cSPUIAssetVerbs> mAssetVerbs;              // +0x70
    AutoRefCount<IAssetData> mAssetData;                    // +0x74
    cAssetMetadata* mpMetadata;                             // +0x78
    AutoRefCount<cSPSwatch> mSwatch;                        // +0x7C
    AutoRefCount<cCardRollover> mRollover;                  // +0x80
    AutoRefCount<cSPCardInventory> mInventory;              // +0x84
    uint32_t field_88;
    AutoRefCount<cSPCardStats> mStats;                      // +0x8C
    TextZoomPtr mTextZoom;                                  // +0x90
    bool mIsOnline;                                         // +0x94
    Rect mBakingArea;                                       // +0x98
    bool mIsLoaded;                                         // +0xA8
    bool mIsPlayable;                                       // +0xA9
    bool field_aa;
    bool mHasResource;                                      // +0xAB
    bool mIsEditable;                                       // +0xAC
    float mSwatchZoom;                                      // +0xB0

    void UpdateDescription();                               // 0066D280
    void SetupAdventure();                                  // 0066C9E0
    void LoadAssetViewLarge();
};

// @ 0x0066daf0
void cSPUILargeAssetView::LoadAssetViewLarge()
{
    if (mIsLoaded)
        return;

    mWinRoot = mLayout->FindWindowByID(0xf3c6dc19, true);
    if (mWinRoot) {
        mWinRoot->AddWinProc(this);
        SPUIHelpers::SetWindowAreaToParent(mWinRoot);
        if (mIsOnline) {
            mCommentsBrowser = new("UI", 0, 0, 0, 0) cSPUIAssetComments();
            mCommentsBrowser->Init(mWinRoot);
        }
        mExpansionPackBrowser = new("UI", 0, 0, 0, 0) cSPUIMissingExpansionPackPage();
        mExpansionPackBrowser->Init(mWinRoot);
        mInventory = new("UI", 0, 0, 0, 0) cSPCardInventory();
        mInventory->SetMessageID(0x14e46c34, gCardInventoryParam);
        mInventory->Show();
    }

    mWinBakingArea = mLayout->FindWindowByID(0x65f79e0, true);
    mWin28 = mLayout->FindWindowByID(0x65f79d8, true);
    if (mWinBakingArea)
        mBakingArea = mWinBakingArea->GetArea();

    mStats = new("UI", 0, 0, 0, 0) cSPCardStats();
    mStats->Load(mLayout, mpMetadata);

    IWindow* shareIconWin;
    if (gAppProperties->mpValues->mOfflineMode == 0) {
        mWinShare = mLayout->FindWindowByID(0x6135298, true);
        if (mWinShare && !AuthManager()->IsOffline()) {
            bool downloaded = false;
            if (mpMetadata) {
                cDownloadList* list = &DownloadManager()->mList;
                unsigned count = list->size();
                for (unsigned i = 0; i < count; ++i) {
                    cDownloadEntry* entry = &list->mpBegin[i];
                    if (entry->mState == 2 && entry->mAssetKey == mpMetadata->GetAssetKey()) {
                        downloaded = true;
                        break;
                    }
                }
            }
            mWinDownloaded = mLayout->FindWindowByID(0x615c7a8, true);
            if (mWinDownloaded)
                mWinDownloaded->SetFlag(1, downloaded);
            mWinShare->SetFlag(1, mpMetadata != 0 && !downloaded &&
                                  mpMetadata->GetAssetKey() != AuthManager()->GetUserID() &&
                                  mpMetadata->GetAssetKey() != 0xfffffffffffffffeULL);
        } else if (mWinShare) {
            mWinShare->SetFlag(1, false);
        }
        mWinShareIcon = mLayout->FindWindowByID(0x6136d30, true);
        shareIconWin = mWinShareIcon;
    } else {
        mWinShare = mLayout->FindWindowByID(0x6135298, true);
        shareIconWin = mWinShare;
    }
    if (shareIconWin)
        shareIconWin->SetFlag(1, false);

    mWinAssetVerbs = mLayout->FindWindowByID(0x34af0c8f, true);
    if (mWinAssetVerbs) {
        mAssetVerbs = new("UI", 0, 0, 0, 0) cSPUIAssetVerbs();
        mAssetVerbs->Init(mWinAssetVerbs);
    }

    mWinRenderWindow = mLayout->FindWindowByID(0xf3c6d819, true);
    if (mWinRenderWindow)
        mWinRenderWindow->SetFlag(1, false);

    mWinName = mLayout->FindWindowByID(0x53d6fe29, true);
    if (mWinName && mAssetData) {
        mWinName->SetCaption(mAssetData->GetName() ? mAssetData->GetName() : L"<Missing>");
        mTextZoom = new("UI/cSPUITextZoom", 0, 0, 0, 0) TextZoomName();
        mTextZoom->SetTargetWindow(mWinName ? mWinName->Cast(0xf15f4bd) : 0, 0, 0, 0, ResourceKey(0, 0, 0));
    }

    mWinAuthor = mLayout->FindWindowByID(0x53d6fe2a, true);
    if (mWinAuthor && mAssetData) {
        mWinAuthor->SetCaption(mAssetData->GetAuthor() ? mAssetData->GetAuthor() : L"<Missing>");
        SPUIHelpers::AutoSizeWindowForText(mWinAuthor, 0, 0);
        if (mWinAuthor->GetParent()) {
            const Rect& parentArea = mWinAuthor->GetParent()->GetRealArea();
            float left = parentArea.x1;
            float right = parentArea.x2;
            const Rect& area = mWinAuthor->GetRealArea();
            mWinAuthor->SetLocation((right + left) * 0.5f - (area.x2 - area.x1) * 0.5f, area.y1);
        }
        if (mWinShare) {
            float authorRight = mWinAuthor->GetRealArea().x2;
            mWinShare->SetLocation(authorRight, mWinShare->GetRealArea().y1);
            Rect shareArea = mWinShare->GetRealArea();
            if (mWinShareIcon)
                SPUIHelpers::CenterWindow(mWinShareIcon, Point((shareArea.x2 + shareArea.x1) * 0.5f,
                                                               (shareArea.y2 + shareArea.y1) * 0.5f));
            if (mWinDownloaded)
                SPUIHelpers::CenterWindow(mWinDownloaded, Point((shareArea.x2 + shareArea.x1) * 0.5f,
                                                                (shareArea.y2 + shareArea.y1) * 0.5f));
        }
        cPlayableAsset* playable;
        if (mAssetData && (playable = (cPlayableAsset*)mAssetData->mObject.Cast(0x13d55dc8)) != 0 &&
            playable->IsPlayable())
            mWinAuthor->SetFlag(0x10, true);
        else
            mWinAuthor->SetFlag(0x10, false);
    }

    mWinPublished = mLayout->FindWindowByID(0x56e3f98, true);
    if (mWinPublished && mAssetData)
        mWinPublished->SetFlag(1, mAssetData->IsPublished());

    mWinDescription = mLayout->FindWindowByID(0xb456a483, true);
    const wchar_t* description = mAssetData->GetDescription();
    if (mWinDescription && mAssetData && description)
        mWinDescription->SetCaption(description);
    if (mWinDescription && mWinDescription->GetParent())
        mWinDescription->GetParent()->AddWinProc(this);

    mWinTags = mLayout->FindWindowByID(0xb456a47a, true);
    if (mWinTags && mAssetData) {
        string16 tags;
        mAssetData->GetTags(tags);
        mWinTags->SetCaption(tags.c_str());
    }
    if (mWinTags && mWinTags->GetParent())
        mWinTags->GetParent()->AddWinProc(this);

    mWin5c = mLayout->FindWindowByID(0x6664868, true);
    mWin30 = mLayout->FindWindowByID(0x3431bd1e, true);
    mWinBakingForeground = mLayout->FindWindowByID(0x34a0979a, true);
    if (mWinBakingForeground)
        mWinBakingForeground->SetFlag(1, false);

    mRollover = new("UI", 0, 0, 0, 0) cCardRollover();
    mRollover->Attach(mLayout);

    AutoRefCount<ResourceObject> resource;
    if (mHasResource) {
        IAssetData* assetData = mAssetData;
        IResourceManager* resourceManager = ResourceManager();
        if (!resourceManager->GetResource(*assetData->GetKey(), resource.AsPPTypeParam(), 0, 0, 0, 0)) {
            resource.Reset();
            mHasResource = false;
            mIsPlayable = false;
            mIsEditable = false;
        }
    }

    if (!mHasResource) {
        if (mWinBakingForeground)
            mWinBakingForeground->SetFlag(1, false);
        if (mWinRenderWindow)
            mWinRenderWindow->SetFlag(1, 0);
    } else {
        mWinVerbContainer = mLayout->FindWindowByID(0x3fbba82, true);
        if (mWinVerbContainer && resource) {
            ResourceKey verbKey;
            ResourceKey layoutKey;
            uint32_t modelType = mAssetData->GetModelType();
            if (AssetBrowser() && AssetBrowser()->mFilterModelType) {
                uint32_t filterType = AssetBrowser()->mFilterModelType;
                if (GetEditorForModelType(filterType) == GetEditorForModelType(modelType))
                    modelType = filterType;
            }
            GetVerbIconKeysForLargeCard(modelType, mAssetData->GetSize(), &verbKey, &layoutKey);
            if (verbKey.instanceID != 0 && mAssetData->HasVerbs()) {
                AutoRefCountOOL<cPropertyList> verbProps;
                PropertyManager()->GetPropertyList(verbKey.instanceID, verbKey.groupID, verbProps.AsPPTypeParam());
                int keyCount = 0;
                int keys = 0;
                GetPropertyArrayKeys(verbProps, 0x4aa3838, &keyCount, &keys);
                if (verbKey.instanceID != 0 && layoutKey.instanceID != 0) {
                    if (mVerbIcons)
                        mVerbIcons->Clear();
                    bool editorTray = false;
                    IWindow* trayWindow = mLayout->FindWindowByID(0x630c829, true);
                    GetBoolProperty(verbProps, 0x630a7a2, editorTray);
                    if (editorTray) {
                        mVerbIcons = new("Editor", 0, 0, 0, 0) cSPVerbTray();
                        if (trayWindow)
                            trayWindow->SetFlag(1, false);
                    } else {
                        mVerbIcons = new("Sporepedia", 0, 0, 0, 0) cSPSporepediaVerbTray();
                        if (trayWindow)
                            trayWindow->SetFlag(1, true);
                    }
                    mVerbIcons->Load(mWinVerbContainer, layoutKey, keys, keyCount, 0);
                }
            } else {
                if (mVerbIcons)
                    mVerbIcons->Clear();
                mVerbIcons.Reset();
            }

            if (mVerbIcons) {
                if (mAssetData->GetKey()->typeID == 0x2b978c46) {
                    AutoRefCountOOL<ResourceObject> creatureRes;
                    if (!ComputeVerbIcons(mAssetData->GetKey(), creatureRes.AsPPTypeParam())) {
                        creatureRes.Reset();
                    } else {
                        int caps = GetCreatureCaps(mAssetData->GetModelType());
                        FillCreatureVerbTray(creatureRes, mVerbIcons, caps, mAssetData->GetSize());
                    }
                } else if (mAssetData->GetModelType() == 0xdfad9f51) {
                    FillBuildingVerbTray(interface_cast_EditorResource(resource), mVerbIcons);
                } else if (mAssetData->GetKey()->typeID != 0x24682294 &&
                           mAssetData->GetKey()->typeID != 0x476a98c7) {
                    FillVehicleVerbTray(interface_cast_EditorResource(resource), mVerbIcons);
                } else {
                    FillUFOVerbTray(interface_cast_EditorResource(resource), mVerbIcons);
                }
                IWindow* trayWindow = mLayout->FindWindowByID(0x630c829, true);
                if (trayWindow) {
                    if (mVerbIcons && mVerbIcons->GetIconCount() > 0) {
                        Rect trayArea = trayWindow->GetRealArea();
                        trayArea.y2 = trayArea.y1 + mVerbIcons->GetHeight() + 15.0f;
                        trayWindow->SetLayoutArea(trayArea);
                    } else {
                        trayWindow->SetFlag(1, false);
                    }
                }
            } else {
                IWindow* trayWindow = mLayout->FindWindowByID(0x630c829, true);
                if (trayWindow)
                    trayWindow->SetFlag(1, false);
            }
        }

        if ((mAssetData && (GetAssetKeyType(mAssetData->GetKey()) == 1 ||
                            mAssetData->GetParentID() == 0x7fffffff)) ||
            gAppProperties->GetDescription(0xb4daca6a))
            UpdateDescription();

        IAssetData* asset = mAssetData;
        AutoRefCount<cPropertyList> editorProps;
        IPropertyManager* propertyManager = PropertyManager();
        if (propertyManager->GetPropertyList(RemapTypeId(asset->GetModelType()), gEditorConfigGroupID,
                                             editorProps.AsPPTypeParam())) {
            uint32_t soundGroup = 0;
            if (GetPropertyAsKeyInstance(editorProps, 0x5d29fdd, &soundGroup)) {
                KillSetiEffects(soundGroup, 0x5d2b737);
                PlayEditorSound(0x5d2b737, 0xbd5385c8, 0.0f, 0);
                if (mVerbIcons) {
                    int iconCount = mVerbIcons->GetIconCount();
                    for (int i = 0; i < iconCount; ++i) {
                        if (mVerbIcons->GetSlot(i)->GetSoundID() > 0)
                            PlayEditorSound(0x1d6253c0, mVerbIcons->GetSlot(i)->GetSoundID(),
                                            mVerbIcons->GetSlot(i)->GetSize(), 0);
                    }
                }
            }
        }

        if (!mSwatch)
            mSwatch = SwatchManager()->CreateSwatch(0);
        if (mSwatch) {
            ResourceKey key = *mAssetData->GetKey();
            bool isAdventure = false;
            if (key.typeID == 0x3d97a8e4 || key.typeID == 0x2b978c46 || key.typeID == 0x438f6347) {
                isAdventure = true;
                mSwatch->Init(key, mWinRenderWindow, 1, 0, 2, 1, mAssetData->GetModelType());
            } else {
                mSwatch->Init(key, mWinRenderWindow, 0, 0, 1, 1, mAssetData->GetModelType());
            }
            mSwatch->SetActive(true);
            mSwatch->SetUpdating(0);
            mSwatch->SetEditorCameraController(1);
            mSwatchZoom = gAppProperties->GetFloatProperty(0x678aff6);
            SetShaderParam(0x236, &mSwatchZoom, 1);
            if (!mSwatch->mIsAnimated) {
                mWinBakingForeground->SetFlag(1, true);
                mWinRenderWindow->SetFlag(1, false);
                if (mWinRoot)
                    mWinRoot->SetCursorID(0x1024);
            } else {
                mWinBakingForeground->SetFlag(1, false);
                mWinRenderWindow->SetFlag(1, true);
                if (mWinRoot)
                    mWinRoot->SetCursorID(0x1002);
            }
            if (isAdventure)
                SetupAdventure();
            ModelManager()->SetPreviewModel(mSwatch->mModel.GetModel());
        }
    }

    mIsLoaded = true;
}

} // namespace SP

