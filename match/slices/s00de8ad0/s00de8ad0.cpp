// Slice s00de8ad0: SP::cSPEditorUI::DoMessage (0x00DE8AD0, 2756 bytes), name from symbols/pdb_names.json
// (anchor). The retail object is much larger than the 2008 PDB layout, so members are raw offsets from the
// retail disassembly (named after what they do here).
// Flags: /O2 /MD /Gy /TP (UI module: no /arch:SSE, no /EHsc: the cString/string16 locals have no EH frame).
//
// The handler is the override of the messaging interface that sits at +8 in the object, so `this` arrives
// as that sub-object (every call on the full object is `lea ecx,[esi-8]`). It forwards every message to
// a nested handler first, then dispatches on the message ID: editor dialog flow (the callout message box
// state machine in mDialogState, answered by button-press messages 0x5d6404b), login/asset-browser
// state, achievements and Sporepedia/Sporeguide refreshes. It returns true for the messages it consumes.
// Callees that only have FUN_ names are named after their use here (descriptive, not PDB).
#include "types.h"

typedef wchar_t char16;

struct ResourceKey { uint32_t instanceID, typeID, groupID; };

// ---- EASTL string16 (out-of-line ctor/substr/assign in this module) --------------------------------
struct allocator { allocator() {} };
struct string16 {
    char16* mpBegin;
    char16* mpEnd;
    char16* mpCapacity;
    uint32_t mAllocator;
    string16(const char16* p, const allocator& a = allocator());          // 0x0041df50
    ~string16() { DeallocateSelf(); }
    void DeallocateSelf();                                                // 0x00933960
    unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
    string16 substr(unsigned int position, unsigned int n) const;         // 0x00453d20
    string16& operator=(const string16& x);                               // 0x0057cb60
};

// SP::cString (localized string)
struct cString {
    uint32_t mData[4];
    cString();                                                            // 0x006b5060
    ~cString();                                                           // 0x006b5240
    void Load(uint32_t tableID, uint32_t instanceID, const char16* pDefault);  // 0x006b54b0
    const char16* GetText();                                              // 0x006b55c0
};

// ---- collaborators -------------------------------------------------------------------------------
class IHandlerForward {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2c();
    virtual void _v30();
    virtual bool DoMessage(uint32_t messageID, void* pMessage);          // 34
};

class IWindow {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2c();
    virtual void _v30(); virtual void _v34(); virtual void _v38(); virtual void _v3c();
    virtual void _v40(); virtual void _v44(); virtual void _v48(); virtual void _v4c();
    virtual void _v50(); virtual void _v54(); virtual void _v58(); virtual void _v5c();
    virtual void _v60(); virtual void _v64(); virtual void _v68(); virtual void _v6c();
    virtual void _v70(); virtual void _v74(); virtual void _v78();
    virtual void SetEnabled(bool a, bool b);                              // 7c
};

class cSPUIGlobalUI { public:
    IWindow* FindWindowByID(uint32_t id);                                 // 0x00e012b0
    void SetVisibility(bool visible);                                     // 0x00e01350
};

struct cSPUIBrowser { void Update(); };                                  // 0x0064ab20
struct cAssetBrowserState { uint32_t pad[0x1c / 4]; bool mbBusy; };       // +1c
cSPUIBrowser* AssetBrowser();                                            // 0x00401030
cSPUIBrowser* SporeGuide();                                              // 0x00401040

struct cMessageServer {
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10();
    virtual void SendMessage(uint32_t messageID, void* msg, int a);       // 14
};
cMessageServer* MessageServer();                                         // 0x0067dcc0

struct cTextDisplay {
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2c();
    virtual void _v30();
    virtual void ShowText(const char16* text, int flags);                 // 34
};
struct cTextDisplayHost {
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual cTextDisplay* GetTextDisplay();                               // 20
};
cTextDisplayHost* TextDisplayHost();                                     // 0x0067de40

struct cAchievementsController {
    bool IsDisabled();                                                   // 0x005c0dd0
    void AwardAchievement(uint32_t id);                                   // 0x00676710
};
cAchievementsController* AchievementsController();                       // 0x00675250

struct cStarManager {
    void SaveState();                                                    // 0x00bb6650
    void LoadStarDatabase();                                             // 0x00bb8b20
    void RefreshState();                                                 // 0x00bb7620
};
cStarManager* StarManager();                                             // 0x00b3d2a0

struct cPollenEntry { uint32_t pad[0xb8 / 4]; struct cPollenItem* mpItem; };  // 0xbc bytes
struct cPollenItem { void Refresh(); };                                  // 0x00df6740
template <typename T> struct sp_vector {
    T* mpBegin; T* mpEnd; T* mpCapacity; uint32_t mAllocator;
    unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
    T& operator[](unsigned int n) { return mpBegin[n]; }
};
struct cPollenManager {
    uint32_t pad00[2];
    sp_vector<cPollenEntry> mEntries;                                    // +08
    void Refresh();                                                      // 0x00df95d0
};
cPollenManager* PollenManager();                                         // 0x00df5f40

struct cEditorGlobal { void SetPaused(bool b); };                        // 0x00df53d0
extern cEditorGlobal* gpEditorGlobal;                                    // 0x016a15f4
extern bool gbSkipSave;                                                  // 0x016a0f28

struct cCalloutTarget { uint32_t pad; };
extern cCalloutTarget gCalloutTarget;                                    // 0x015a41d4
extern const ResourceKey kCalloutPublish;                                // 0x015a3860
extern const ResourceKey kCalloutSave;                                   // 0x015a386c
extern const ResourceKey kCalloutSaveConfirm;                            // 0x015a3878
extern const ResourceKey kCalloutExit;                                   // 0x015a3884
extern const ResourceKey kCalloutError;                                  // 0x015a3890
extern const ResourceKey kCalloutExitConfirm;                            // 0x015a389c
extern const ResourceKey kCalloutCloseConfirm;                           // 0x015a38a8
void CalloutMessageBox(cCalloutTarget* target, const ResourceKey* key);  // 0x00809db0

int GetCurrentGameMode();                                                // 0x00b5b800
void ShowContextSensitiveSporeGuide();                                   // 0x00e02200
void OpenSporepedia();                                                   // 0x00e02c40

struct cDialogOwner { uint32_t pad[0xc / 4]; void* mpOwner; };           // +0c
cDialogOwner* FindDialog(void* key);                                     // 0x00de46c0

struct cEditorDialog {
    uint32_t pad[0x3c / 4];
    int mResult;                                                         // +3c
    bool mbWasPaused;                                                    // +40
    bool IsReadyToClose();                                               // 0x00e205d0
    void Close();                                                        // 0x00e20860
};

struct cPendingDialog { uint32_t pad[0xac / 4]; bool mbOpen; };          // +ac

struct cLaunchData { uint32_t pad[0x18 / 4]; ResourceKey mKey; };        // +18
struct cLaunchDataPtr {
    cLaunchData* mpObject;
    void Set(void* p);                                                   // 0x00572620
};

struct cInsertResult { void* mpNode; bool mbInserted; cInsertResult() {} };
struct cMessage;
struct cMessageSet { cInsertResult insert(cMessage* const& value); };        // 0x00a18440

struct cSubPanel { void HandleMessage(void* pMessage); };                // 0x00de6e80

struct cMessage { uint32_t pad[2]; int mValue; };                        // +08

// ---- the editor UI -------------------------------------------------------------------------------
class cSPUIAssetBrowserCallback { public: virtual void _cb0(); };
class IWinProc { public: virtual void _wp0(); };
class IHandlerRC {
public:
    virtual bool DoMessage(uint32_t messageID, void* pMessage) = 0;
};

class cSPEditorUI : public cSPUIAssetBrowserCallback, public IWinProc, public IHandlerRC {
public:
    uint32_t pad0C[(0x38 - 0xc) / 4];
    IHandlerForward* mpForwardHandler;       // +38
    cSubPanel mSubPanel;                     // +3c
    uint8_t pad3D[0xc9 - 0x3d];
    bool mbHasModel;                         // +c9
    uint8_t padCA[0xd0 - 0xca];
    string16 mModelName;                     // +d0
    int mUndoCount;                          // +e0
    bool mbLoginPending;                     // +e4
    uint8_t padE5[3];
    int mDialogState;                        // +e8
    uint8_t padEC;
    bool mbRefreshPending;                   // +ed
    bool mbBrowserPending;                   // +ee
    bool mbActivated;                        // +ef
    cEditorDialog* mpDialog;                 // +f0
    uint32_t padF4[2];
    cPendingDialog* mpPendingDialog;         // +fc
    uint8_t pad100;
    bool mbAssetBrowserOpen;                 // +101
    bool mbPublishOpen;                      // +102
    uint8_t pad103;
    bool mbSaveRequested;                    // +104
    uint8_t pad105[3];
    int mLoginState;                         // +108
    int mLoginAction;                        // +10c
    uint32_t pad110[(0x184 - 0x110) / 4];
    cSPUIGlobalUI* mpGlobalUI;               // +184
    ResourceKey mKeyToLoad;                  // +188
    uint32_t pad194[(0x1f0 - 0x194) / 4];
    uint8_t pad1F0;
    bool mbHidden;                           // +1f1
    uint8_t pad1F2[3];
    bool mbAchievementSent;                  // +1f5
    uint8_t pad1F6[0x24c - 0x1f6];
    bool mbResultsReceived;                  // +24c
    bool mbTutorialDone;                     // +24d
    uint8_t pad24E[2];
    cLaunchDataPtr mpLaunchData;             // +250
    cMessageSet mPendingMessages;            // +254
    uint8_t pad255[0x270 - 0x255];
    bool mbInputLocked;                      // +270

    virtual bool DoMessage(uint32_t messageID, void* pMessage);

    void UpdateLoginButton(bool b);          // 0x00de5040
    void OnBrowserClosed();                  // 0x00de4630
    void ShowSaveDialog();                   // 0x00de5260
    void ShowDialog(int id, int a);          // 0x00de86d0
    void OnSaveAccepted();                   // 0x00de4a70
    void OnSaveRejected();                   // 0x00de4b30
    void LockUI(bool b);                     // 0x00de4bc0
    bool IsPaused();                         // 0x00de4c00
    void SetPaused(bool b);                  // 0x00de4c20
    void Refresh();                          // 0x00de52d0
    void ShowPublish(int a);                 // 0x00de53d0
    void PreparePublish();                   // 0x00de4b00
    void UpdateTitle();                      // 0x00de4850
    void OnExitRequested();                  // 0x00de95a0
};

struct cMessageSlot {
    uint8_t mData[0x1c];
    void* GetData(void* key);                // 0x00de7590
};

struct cEditorMessageTarget {
    uint8_t pad00[0x38];
    cMessageSlot mSlot38;                    // +38
    cMessageSlot mSlot54;                    // +54
    cMessageSlot mSlot70;                    // +70
    void OnEditorMessageReceived(void* pMessage);  // 0x00de9600
};

struct IAttachment {
    virtual void _a00();
    virtual void Release();                  // +04
};

struct IMessageReader {
    virtual void _r00(); virtual void _r04(); virtual void _r08();
    virtual bool ReadMessage(void* arg, void* out, int a, int b, int c, int d);  // +0c
};
IMessageReader* CreateMessageReader();                                    // 0x0067dcd0

struct IEditorNode {
    virtual void _n00(); virtual void _n04(); virtual void _n08(); virtual void _n0c();
    virtual void _n10(); virtual void _n14(); virtual void _n18(); virtual void _n1c();
    virtual void _n20(); virtual void _n24(); virtual void _n28();
    virtual void SetAttachment(void* p);                                 // +2c
};
IEditorNode* CreateEditorNode(void* source);                              // 0x006a1c40
void SetEditorNodeValue(IEditorNode* node, void* value);                 // 0x006a1710
void ReleaseEditorNode(IEditorNode* node);                               // 0x006a3dd0

// The 0xbc-byte entry vector also has an insert/move-tail pair in this slice.
struct cEntryVector {
    cPollenEntry* mpBegin;                   // +00
    cPollenEntry* mpEnd;                     // +04
    cPollenEntry* mpCapacity;                // +08
    uint32_t mAllocator;                     // +0c

    cPollenEntry* MoveTail(cPollenEntry* first, cPollenEntry* dest);      // 0x00de97a0
    void insert(cPollenEntry* position, unsigned int count,
                const cPollenEntry& value);                              // 0x00de97f0
    void DestroyRange(cPollenEntry* first, cPollenEntry* last);           // 0x00de5ee0
};

cPollenEntry* CopyConstructEntries(cPollenEntry* first, cPollenEntry* last,
                                   cPollenEntry* dest);                   // 0x00de6070
void CopyConstructEntry(cPollenEntry* dest, const cPollenEntry& value);   // 0x00de60f0
void* __cdecl MessageAllocate(unsigned int size, const char* name, int flags,
                              int align, const char* file, int line);      // 0x00f473a0
void __cdecl MessageFree(void* p);                                        // 0x00f47380

// @ 0x00de95a0
void cSPEditorUI::OnExitRequested()
{
    if (mpDialog->IsReadyToClose()) {
        mDialogState = 1;
        CalloutMessageBox(&gCalloutTarget, &kCalloutCloseConfirm);
    } else {
        MessageServer()->SendMessage(0xce7afa41, 0, 0);
    }
    if (mLoginAction != 10)
        ShowDialog(10, 1);
}

// @ 0x00de9600
void cEditorMessageTarget::OnEditorMessageReceived(void* pMessage)
{
    IMessageReader* reader = CreateMessageReader();
    void* attachment = 0;
    if (!reader || !reader->ReadMessage(pMessage, &attachment, 0, 0, 0, 0))
        return;
    if (!attachment)
        return;

    void* source = reinterpret_cast<char*>(attachment) + 0x18;
    IEditorNode* node = CreateEditorNode(source);
    if (!node)
        return;

    node->SetAttachment(source);
    SetEditorNodeValue(node, *reinterpret_cast<void**>(reinterpret_cast<char*>(source) + 0x30));

    // The retail code copies three 12-byte payloads into the editor panels at
    // +38, +54 and +70; the first two come from the attachment/node, the last
    // is the message's own 12-byte payload.
    uint32_t* sourceValues = reinterpret_cast<uint32_t*>(source);
    uint32_t* messageValues = reinterpret_cast<uint32_t*>(pMessage);
    if (void* data = mSlot38.GetData(pMessage)) {
        uint32_t* out = reinterpret_cast<uint32_t*>(data);
        out[0] = sourceValues[0];
        out[1] = sourceValues[1];
        out[2] = sourceValues[2];
    }
    if (void* data = mSlot54.GetData(pMessage)) {
        uint32_t* out = reinterpret_cast<uint32_t*>(data);
        out[0] = sourceValues[0];
        out[1] = sourceValues[1];
        out[2] = sourceValues[2];
    }
    if (void* data = mSlot70.GetData(pMessage)) {
        uint32_t* out = reinterpret_cast<uint32_t*>(data);
        out[0] = messageValues[0];
        out[1] = messageValues[1];
        out[2] = messageValues[2];
    }

    ReleaseEditorNode(node);
    reinterpret_cast<IAttachment*>(attachment)->Release();
}

extern "C" void* __cdecl memmove(void*, const void*, unsigned int);

// @ 0x00de97a0
cPollenEntry* cEntryVector::MoveTail(cPollenEntry* first, cPollenEntry* dest)
{
    cPollenEntry* const newEnd = CopyConstructEntries(first, mpEnd, dest);
    DestroyRange(newEnd, mpEnd);
    mpEnd += dest - first;
    return first;
}

// @ 0x00de97f0
void cEntryVector::insert(cPollenEntry* position, unsigned int count,
                          const cPollenEntry& value)
{
    if (count == 0)
        return;

    const unsigned int index = (unsigned int)(position - mpBegin);
    const unsigned int oldSize = (unsigned int)(mpEnd - mpBegin);

    if (count > (unsigned int)(mpCapacity - mpEnd)) {
        unsigned int grow = oldSize * 2;
        if (oldSize == 0)
            grow = 1;
        const unsigned int newSize = grow > oldSize + count ? grow : oldSize + count;
        cPollenEntry* newData = newSize
            ? (cPollenEntry*)MessageAllocate(newSize * sizeof(cPollenEntry),
                                             (const char*)0x013f09b4, 0, 0,
                                             (const char*)0x013ebb38, 0xd1)
            : 0;
        if (oldSize)
            memmove(newData, mpBegin, oldSize * sizeof(cPollenEntry));
        if (mpBegin != 0 && *((unsigned int*)mpBegin - 1) != 0)
            MessageFree(mpBegin);
        mpBegin = newData;
        mpEnd = newData + oldSize;
        mpCapacity = newData + newSize;
    }

    position = mpBegin + index;
    memmove(position + count, position,
            (unsigned int)(mpEnd - position) * sizeof(cPollenEntry));
    for (unsigned int i = 0; i < count; ++i)
        position[i] = value;
    mpEnd += count;
}

bool cSPEditorUI::DoMessage(uint32_t messageID, void* pMessage)
{
    if (mpForwardHandler)
        mpForwardHandler->DoMessage(messageID, pMessage);

    switch (messageID) {
    case 0x30c11c7:
        if (pMessage) {
            cDialogOwner* owner = FindDialog((char*)pMessage + 0x10);
            if (owner && owner->mpOwner == this) {
                mpLaunchData.Set(pMessage);
                mKeyToLoad = mpLaunchData.mpObject->mKey;
            }
        }
        mbResultsReceived = true;
        break;

    case 0x238de9c:
        mbSaveRequested = true;
        ShowSaveDialog();
        break;

    case 0x44db12e:
        mbAssetBrowserOpen = false;
        if (pMessage && mbLoginPending && !((cAssetBrowserState*)AssetBrowser())->mbBusy) {
            UpdateLoginButton(true);
            mbLoginPending = false;
            OnBrowserClosed();
            return false;
        }
        UpdateLoginButton(pMessage != 0);
        if (mLoginState == 1 || mLoginState == 0)
            mLoginAction = 2;
        break;

    case 0x4519b5f: {
        mbHidden = false;
        if (mbBrowserPending) {
            mbBrowserPending = false;
            OnBrowserClosed();
        }
        IWindow* window = mpGlobalUI->FindWindowByID(0x10ed874);
        if (window)
            window->SetEnabled(true, true);
        mpGlobalUI->SetVisibility(true);
        return false;
    }

    case 0x4fd2bce:
        if (mbHasModel)
            mbPublishOpen = true;
        break;

    case 0x4fd2bd3:
        mbPublishOpen = false;
        break;

    case 0x5120263:
        ShowContextSensitiveSporeGuide();
        break;

    case 0x5120264:
        if (GetCurrentGameMode() == 0x2ccd1d2) {
            ShowDialog(7, 1);
            return false;
        }
        OpenSporepedia();
        break;

    case 0x56bbd7f:
        mbAssetBrowserOpen = true;
        break;

    case 0x574f0a6:
        AssetBrowser()->Update();
        break;

    case 0x5b9ba6c:
        SporeGuide()->Update();
        break;

    case 0x5bd6378:
        if (!mbActivated)
            mbActivated = true;
        if (mLoginAction != 10)
            ShowDialog(10, 1);
        break;

    case 0x5d3c4e1:
        mbTutorialDone = true;
        break;

    case 0x5d6404b: {
        int button = ((cMessage*)pMessage)->mValue;
        if (button == 0x1510d07)
            return false;
        switch (mDialogState) {
        case 1:
            if (button == -15) {
                MessageServer()->SendMessage(0xce7afa41, 0, 0);
                mDialogState = 0;
            }
            break;
        case 2:
            switch (button) {
            case 0x5107b17:
                OnSaveAccepted();
                return true;
            case 0x5107b19:
                mDialogState = 0;
                break;
            case 0x5107b1a:
                OnSaveRejected();
                return true;
            }
            break;
        case 3:
            switch (button) {
            case 0x5107b19:
                mDialogState = 4;
                CalloutMessageBox(&gCalloutTarget, &kCalloutSaveConfirm);
                return true;
            case 0x5107b1a:
                mDialogState = 0;
                if (mpDialog) {
                    mpDialog->mResult = 3;
                    mpDialog->Close();
                    return true;
                }
                break;
            }
            break;
        case 4:
        case 6:
        case 7:
            if (button == -15) {
                mDialogState = 0;
                return true;
            }
            break;
        case 5:
            switch (button) {
            case 0x5107b19:
                if (gpEditorGlobal)
                    gpEditorGlobal->SetPaused(true);
                SetPaused(mpDialog->mbWasPaused);
                return true;
            case 0x5107b1a:
                LockUI(false);
                mDialogState = 7;
                CalloutMessageBox(&gCalloutTarget, &kCalloutExitConfirm);
                mpDialog->mResult = 7;
                mpDialog->Close();
                return true;
            }
            break;
        default:
            return false;
        }
        return true;
    }

    case 0x5d663cd:
        mpDialog->mbWasPaused = IsPaused();
        if (gpEditorGlobal)
            gpEditorGlobal->SetPaused(false);
        SetPaused(true);
        mDialogState = 5;
        CalloutMessageBox(&gCalloutTarget, &kCalloutExit);
        return true;

    case 0x5d66be3:
        LockUI(true);
        mDialogState = 3;
        CalloutMessageBox(&gCalloutTarget, &kCalloutSave);
        return true;

    case 0x5d6714b:
        if (IsPaused())
            SetPaused(false);
        else
            SetPaused(true);
        return true;

    case 0x5d676ed: {
        LockUI(false);
        uint32_t textID = 0;
        switch (((cMessage*)pMessage)->mValue) {
        case 0: textID = 0x5d67a45; break;
        case 1: textID = 0x5d67a51; break;
        case 2: textID = 0x5ee138e; break;
        case 3: textID = 0x5ee1398; break;
        case 4: textID = 0x5f7a60e; break;
        }
        cString text;
        text.Load(0xd7f9d626, textID, L"*error message*");
        TextDisplayHost()->GetTextDisplay()->ShowText(text.GetText(), 0);
        mDialogState = 6;
        CalloutMessageBox(&gCalloutTarget, &kCalloutError);
        return true;
    }

    case 0x5dd52c7:
        if (!mbActivated)
            return false;
        mbActivated = false;
        if (mbRefreshPending) {
            mbRefreshPending = false;
            OnBrowserClosed();
        }
        Refresh();
        break;

    case 0x6203fdc:
        mbHidden = true;
        mpGlobalUI->SetVisibility(false);
        break;

    case 0x625d27c:
        StarManager()->SaveState();
        StarManager()->LoadStarDatabase();
        PollenManager()->Refresh();
        StarManager()->RefreshState();
        break;

    case 0x625d27d:
        PollenManager()->Refresh();
        break;

    case 0x625e26a:
        if (mpPendingDialog && mpPendingDialog->mbOpen)
            ShowPublish(1);
        break;

    case 0x6382db7:
        PreparePublish();
        mDialogState = 2;
        CalloutMessageBox(&gCalloutTarget, &kCalloutPublish);
        break;

    case 0x64a5044:
        if (mbHasModel)
            ShowDialog(6, 1);
        break;

    case 0x64a504a:
        if (mbHasModel)
            Refresh();
        break;

    case 0x6579712:
        if (!mbAchievementSent && !AchievementsController()->IsDisabled()) {
            mPendingMessages.insert((cMessage*)pMessage);
            if (!gbSkipSave)
                ShowSaveDialog();
            UpdateTitle();
        }
        break;

    case 0x680c633: {
        string16 name((const char16*)pMessage);
        if (name.size() > 4) {
            mModelName = name.substr(0, name.size() - 4);
            UpdateTitle();
        }
        return false;
    }

    case 0x7ca274b:
        ++mUndoCount;
        if (mUndoCount == 10)
            AchievementsController()->AwardAchievement(0xb5e59f);
        break;

    case 0x8085c4c:
        mLoginAction = 1;
        return true;

    case 0x275a9c8c:
        return true;

    case 0x634297ad:
        return true;

    case 0x67c75bd6:
        if (((cMessage*)pMessage)->mValue == 1 && mLoginState == 8)
            mLoginAction = 9;
        return true;

    case 0x99eda4cd: {
        sp_vector<cPollenEntry>& entries = PollenManager()->mEntries;
        for (unsigned int i = 0; i < entries.size(); i++) {
            cPollenItem* item = entries[i].mpItem;
            if (item)
                item->Refresh();
        }
        mSubPanel.HandleMessage(pMessage);
        return false;
    }

    case 0xcc0bf724:
        mbInputLocked = false;
        break;

    case 0xcc0bf725:
        mbInputLocked = true;
        break;

    case 0xeda117de:
        return true;
    }
    return false;
}
