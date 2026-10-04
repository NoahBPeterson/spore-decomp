// Slice s005dbd20: SP::cSPEditorTuning::LoadTuningValues and SP::cSPEditorUI (editor HUD:
// window lookups, button state, dialogs, message listening, two window procs).
#include "types.h"

void* operator new(unsigned int n, const char* pName, int flags = 0, unsigned int debugFlags = 0, const char* pFile = 0, int line = 0) throw();   // 0x00F473A0

// ---------------------------------------------------------------------------------------------
// Properties
struct cSPColorRGB { float r, g, b; };
struct cSPColorRGBA { float r, g, b, a; };
namespace EA { namespace ResourceMan {
struct Key { uint32_t mInstance, mType, mGroup; };
} }
using EA::ResourceMan::Key;

namespace App {
class Property {
public:
    float* GetValueFloat();          // 0x0041EA70
    uint16_t pad[9];
    uint16_t mnType;                 // +0x12 (0xd = float)
};
class PropertyList {
public:
    virtual int AddRef();
    virtual int Release();
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool GetProperty(uint32_t propertyID, Property*& result);   // +0x24
};
}
namespace SP {
bool GetPropertyAsColorRGB(App::PropertyList* pList, uint32_t propertyID, cSPColorRGB* pValue);     // 0x006A11B0
bool GetPropertyAsColorRGBA(App::PropertyList* pList, uint32_t propertyID, cSPColorRGBA* pValue);   // 0x006A1200
bool GetPropertyAsKey(App::PropertyList* pList, uint32_t propertyID, Key* pValue);                 // 0x006A1250
inline bool GetPropertyAsFloat(App::PropertyList* pList, uint32_t propertyID, float& value)
{
    App::Property* pProp;
    if (pList && pList->GetProperty(propertyID, pProp) && pProp->mnType == 0xd) {
        value = *pProp->GetValueFloat();
        return true;
    }
    return false;
}

class cSPEditorTuning {
public:
    void LoadTuningValues(App::PropertyList* pList);

    void* vftable;                            // +0x0
    cSPColorRGB mSpineHandleColor;            // +0x4
    float mSpineHandleSize;                   // +0x10
    float mSpineHandleAlpha;                  // +0x14
    float mSpineHandleOverdrawAlpha;          // +0x18
    float mSpineHandleDistance;               // +0x1c
    cSPColorRGBA mVertebraTorsoRolloverColor; // +0x20
    cSPColorRGBA mVertebraTorsoSelectedColor; // +0x30
    cSPColorRGBA mVertebraHighlightColor;     // +0x40
    cSPColorRGBA mVertebraUnselectedColor;    // +0x50
    Key mRotationBallHandleTuningKey;         // +0x60
    Key mDeformHandleTuningKey;               // +0x6c
    Key mBallConnectorHandleTuningKey;        // +0x78
    Key mUnknownKey84;                        // +0x84
    Key mRotationRingHandleTuningKey;         // +0x90
    Key mUnknownKey9C;                        // +0x9c
    Key mUnknownKeyA8;                        // +0xa8
    float mVertebraFadeTime;                  // +0xb4
};
}

using namespace SP;

// @ 0x005DBD20
void cSPEditorTuning::LoadTuningValues(App::PropertyList* pList)
{
    GetPropertyAsColorRGB(pList, 0x04DC44CB, &mSpineHandleColor);
    GetPropertyAsFloat(pList, 0x04DC44CC, mSpineHandleSize);
    GetPropertyAsFloat(pList, 0x04DC44CD, mSpineHandleAlpha);
    GetPropertyAsFloat(pList, 0x04DC44CE, mSpineHandleOverdrawAlpha);
    GetPropertyAsFloat(pList, 0x04DC44CF, mSpineHandleDistance);
    GetPropertyAsColorRGBA(pList, 0x04FE1603, &mVertebraTorsoRolloverColor);
    GetPropertyAsColorRGBA(pList, 0x04FE1604, &mVertebraTorsoSelectedColor);
    GetPropertyAsColorRGBA(pList, 0x04FE1605, &mVertebraHighlightColor);
    GetPropertyAsColorRGBA(pList, 0x04FE1606, &mVertebraUnselectedColor);
    GetPropertyAsFloat(pList, 0x04FE1607, mVertebraFadeTime);
    GetPropertyAsKey(pList, 0x050FC283, &mRotationBallHandleTuningKey);
    GetPropertyAsKey(pList, 0x050FC284, &mRotationRingHandleTuningKey);
    GetPropertyAsKey(pList, 0x050FC286, &mUnknownKeyA8);
    GetPropertyAsKey(pList, 0x050FC285, &mUnknownKey9C);
    GetPropertyAsKey(pList, 0x050FC287, &mDeformHandleTuningKey);
    GetPropertyAsKey(pList, 0xB8E88BEC, &mBallConnectorHandleTuningKey);
    GetPropertyAsKey(pList, 0x3042E156, &mUnknownKey84);
}

// ---------------------------------------------------------------------------------------------
// UTFWin
namespace EA { namespace UTFWin {
struct Message {
    uint32_t pad0[2];
    uint32_t eventType;   // +0x8
    union {
        struct { float x, y; } mouse;             // +0xc
        struct { uint32_t chr, vkey; } key;       // +0xc
    };
    uint32_t modifiers;   // +0x14
    uint32_t button;      // +0x18
};
class IWindow {
public:
#define PH(n) virtual void ph##n();
    PH(0) PH(1) PH(2) PH(3) PH(4) PH(5) PH(6)
    virtual uint32_t GetControlID();                       // +0x1c
    PH(8) PH(9) PH(10) PH(11) PH(12) PH(13) PH(14) PH(15) PH(16) PH(17) PH(18) PH(19) PH(20)
    PH(21) PH(22)
    virtual void SetShadeColor(uint32_t color);            // +0x5c
    PH(24) PH(25) PH(26) PH(27) PH(28) PH(29) PH(30)
    virtual void SetFlag(int flag, bool value);            // +0x7c
    virtual void SetCaption(const wchar_t* pText);         // +0x80
    PH(33) PH(34) PH(35) PH(36)
    virtual void Invalidate();                             // +0x94
#undef PH
};
class IWindowManager {
public:
#define PH(n) virtual void ph##n();
    PH(0) PH(1) PH(2) PH(3) PH(4) PH(5) PH(6) PH(7) PH(8) PH(9) PH(10) PH(11) PH(12) PH(13) PH(14)
    PH(15) PH(16) PH(17) PH(18) PH(19) PH(20)
    virtual IWindow* GetCapture(int type);                 // +0x54
    PH(22)
    virtual void SetCapture(int type, IWindow* pWindow);   // +0x5c
#undef PH
};
class IWinProc {
public:
    virtual ~IWinProc() {}
    virtual int AddRef() = 0;
    virtual int Release() = 0;
    virtual uint32_t GetEventFlags() = 0;
    virtual bool HandleUIMessage(IWindow* pWindow, const Message& msg) = 0;
};
} }
using EA::UTFWin::IWindow;
using EA::UTFWin::Message;

namespace SP {
EA::UTFWin::IWindowManager* WindowManager();   // 0x0067CAA0

// Something that owns an editor window proc and receives its mouse events.
class cSPEditorMouseListener {
public:
#define PH(n) virtual void ph##n();
    PH(0) PH(1) PH(2) PH(3) PH(4) PH(5) PH(6) PH(7) PH(8) PH(9) PH(10)
#undef PH
    virtual bool OnMouseDown(uint32_t button, float x, float y, uint32_t modifiers);   // +0x2c
    virtual bool OnMouseUp(uint32_t button, float x, float y, uint32_t modifiers);     // +0x30
    virtual void OnMouseMove(float x, float y, uint32_t modifiers);                    // +0x34
    virtual void OnMouseWheel(uint32_t button, float x, float y, uint32_t modifiers);  // +0x38
    void OnKeyDown(uint32_t key, uint32_t modifiers);    // 0x00585830
    void OnKeyUp(uint32_t key, uint32_t modifiers);      // 0x00585860
};

class cSPEditorKeyWinProc : public EA::UTFWin::IWinProc {
public:
    virtual bool HandleUIMessage(IWindow* pWindow, const Message& msg);
    int mRefCount;                         // +0x4
    uint32_t mUnknown8;                    // +0x8
    cSPEditorMouseListener* mpListener;    // +0xc
};

class cSPEditorInputWinProc : public EA::UTFWin::IWinProc {
public:
    virtual bool HandleUIMessage(IWindow* pWindow, const Message& msg);
    int mRefCount;                         // +0x4
    uint32_t mUnknown8;                    // +0x8
    cSPEditorMouseListener* mpListener;    // +0xc
};
}

// @ 0x005DBEF0
bool cSPEditorKeyWinProc::HandleUIMessage(IWindow* pWindow, const Message& msg)
{
    switch (msg.eventType) {
    case 1:
        if (mpListener)
            mpListener->OnKeyDown(msg.key.vkey, msg.modifiers);
        return true;
    case 2:
        if (mpListener)
            mpListener->OnKeyUp(msg.key.vkey, msg.modifiers);
        return true;
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        return true;
    }
    return false;
}

// @ 0x005DBF80
bool cSPEditorInputWinProc::HandleUIMessage(IWindow* pWindow, const Message& msg)
{
    IWindow* const pCapture = WindowManager()->GetCapture(1);
    if (WindowManager()->GetCapture(1) != pWindow)
        return false;
    switch (msg.eventType) {
    case 1:
        if (mpListener)
            mpListener->OnKeyDown(msg.key.vkey, msg.modifiers);
        return true;
    case 2:
        if (mpListener)
            mpListener->OnKeyUp(msg.key.vkey, msg.modifiers);
        return true;
    case 5:
        return true;
    case 6:
        if (msg.button == 1000) {
            if (mpListener && mpListener->OnMouseDown(msg.button, msg.mouse.x, msg.mouse.y, msg.modifiers))
                return true;
            return false;
        }
        return true;
    case 8:
        if (mpListener)
            mpListener->OnMouseMove(msg.mouse.x, msg.mouse.y, msg.modifiers);
        return true;
    case 9:
        if (mpListener)
            mpListener->OnMouseWheel(msg.button, msg.mouse.x, msg.mouse.y, msg.modifiers);
        return true;
    case 0x287259F6:
        return true;
    case 7:
        if (msg.button == 1000) {
            pCapture->SetFlag(1, false);
            WindowManager()->SetCapture(1, pWindow);
            WindowManager()->SetCapture(0, pWindow);
            if (!mpListener)
                return false;
            if (!mpListener->OnMouseUp(msg.button, msg.mouse.x, msg.mouse.y, msg.modifiers))
                return false;
        }
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------------------------
// cSPEditorUI
namespace EA { namespace Messaging {
void RemoveHandler(void* pServer, void* pHandler, const uint32_t* pIdArray, uint32_t nIdCount, int nPriority);   // 0x00571DB0
class IHandler {
public:
    virtual ~IHandler() {}
    virtual bool HandleMessage(uint32_t messageID, void* pMessage) = 0;
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};
class IHandlerRC : public IHandler {};
class IMessageServer {
public:
#define PH(n) virtual void ph##n();
    PH(0) PH(1) PH(2) PH(3) PH(4) PH(5) PH(6) PH(7) PH(8)
#undef PH
    virtual void AddHandler(IHandler* pHandler, uint32_t messageID);   // +0x24
};
struct AutoHandler {
    IMessageServer* mpServer;        // +0x0
    IHandler* mpHandler;             // +0x4
    const uint32_t* mpIdArray;       // +0x8
    uint32_t mnIdArrayCount;         // +0xc
    int mnPriority;                  // +0x10
    ~AutoHandler() { Unregister(); }
    void Register(IMessageServer* pServer, IHandler* pHandler, const uint32_t* pIdArray, uint32_t nIdCount, int nPriority) {
        mpServer = pServer;
        mpHandler = pHandler;
        mpIdArray = pIdArray;
        mnIdArrayCount = nIdCount;
        mnPriority = nPriority;
        if (pServer && pHandler) {
            for (uint32_t i = 0; i < nIdCount; i++)
                pServer->AddHandler(pHandler, pIdArray[i]);
        }
    }
    void Unregister() {
        if (mpServer) {
            IMessageServer* const pServer = mpServer;
            mpServer = 0;
            RemoveHandler(pServer, mpHandler, mpIdArray, mnIdArrayCount, mnPriority);
        }
    }
};
} }
namespace EA {
template <class T> struct RefCountVTemplate {
    virtual ~RefCountVTemplate() {}
    T mRefCount;
};
template <class T> struct AutoRefCount {
    T* mpObject;
    ~AutoRefCount() {
        if (mpObject)
            mpObject->Release();
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
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
};
}

namespace SP {
EA::Messaging::IMessageServer* MessageServer();   // 0x0067DCC0

class cSPUILayout {
public:
    ~cSPUILayout();                                       // 0x00811FE0
    IWindow* FindWindowByID(uint32_t id, bool bRecursive);   // 0x008105B0
    uint32_t mData[6];
};
class cString {
public:
    cString();                                            // 0x006B5060
    ~cString();                                           // 0x006B5240
    bool Load(uint32_t tableID, uint32_t instanceID, int flags);   // 0x006B54B0
    const wchar_t* GetText(int index);                    // 0x006B55C0
    uint32_t mData[5];
};
class cSPUITooltipWinProc {
public:
    virtual int AddRef();
    virtual int Release();
    void SetText(const wchar_t* pText, bool bRefresh);    // 0x00835ED0
};
struct cRefObject1 {   // AddRef/Release in slots 0/1
    virtual int AddRef();
    virtual int Release();
};
struct cRefObject2 {   // Release in slot 2
    virtual void v0();
    virtual int AddRef();
    virtual int Release();
};
class cSPEditorLoadDialog {
public:
    cSPEditorLoadDialog(Key* pKey);                        // 0x005FE600
    virtual int AddRef();
    virtual int Release();
    void Setup(int source, bool bFlag);                    // 0x005FEA60
    void Show();                                           // 0x005FE6C0
    uint32_t mData[7];
};
class cSPUIAssetBrowserCallback {
public:
    virtual void OnAssetBrowserClosed();
};
struct cSPUIAssetBrowserLaunchInfo {
    cSPUIAssetBrowserLaunchInfo();      // 0x00644B10
    ~cSPUIAssetBrowserLaunchInfo();     // 0x00644B60
    uint32_t mLayoutID;                 // +0x0
    uint32_t pad04[3];
    bool mbAllowEdit;                   // +0x10
    uint32_t pad14[7];
    uint32_t mCallbackID;               // +0x30
    uint32_t pad34;
    cSPUIAssetBrowserCallback* mpCallback;   // +0x38
    uint32_t pad3c[3];
};
class cSPUIAssetBrowser {
public:
    static void Launch(uint32_t layoutID, cSPUIAssetBrowserCallback* pCallback, uint32_t callbackID);   // 0x0064BC50
    static void AdvancedLaunch(cSPUIAssetBrowserLaunchInfo& info);                                      // 0x0064A990
};
class cEditorTypeProvider {
public:
#define PH(n) virtual void ph##n();
    PH(0) PH(1) PH(2) PH(3) PH(4) PH(5) PH(6) PH(7) PH(8) PH(9) PH(10) PH(11) PH(12)
#undef PH
    virtual void SetName(const wchar_t* pName);   // +0x34
};
class cEditorTypeRegistry {
public:
#define PH(n) virtual void ph##n();
    PH(0) PH(1) PH(2) PH(3) PH(4) PH(5) PH(6) PH(7)
#undef PH
    virtual cEditorTypeProvider* GetProvider();   // +0x20
};
cEditorTypeRegistry* EditorTypeRegistry();        // 0x0067DE40
struct cEditorPaletteEntry {
    char pad[0x78];
    cString mName;                                // +0x78
};
class cEditorPaletteDB {
public:
    cEditorPaletteEntry* FindEntry(uint32_t id);  // 0x0067AEE0
    void Select(uint32_t id);                     // 0x0067C830
};
cEditorPaletteDB* EditorPaletteDB();              // 0x0067CAC0
struct cRect16 { float x1, y1, x2, y2; };
int HitTestRegion(cRect16 a, cRect16 b);          // 0x004F3B40
uint32_t RegionToPaletteID(int region);           // 0x004F3C40
void AssignKey(Key* pDst, const Key* pSrc);       // 0x00809DB0
extern const Key kEditorKeyA;                     // 0x01519940
extern const Key kEditorKeyB;                     // 0x0151994C
namespace EditorUtils {
bool GetCreatorType(const Key* pKey);             // 0x00641900
}
int GetUploadState(const Key* pKey);              // 0x00552300

class cEditorPlayModeController {
public:
#define PH(n) virtual void ph##n();
    PH(0) PH(1) PH(2) PH(3) PH(4) PH(5) PH(6)
#undef PH
    virtual void Activate(bool bOn);              // +0x1c
};
struct cEditorModel {
    char pad[0xc];
    Key mKey;                                     // +0xc
};
class cAppModeEditorBase {
public:
#define PH(n) virtual void ph##n();
    PH(0) PH(1) PH(2) PH(3) PH(4) PH(5) PH(6) PH(7) PH(8) PH(9) PH(10) PH(11) PH(12) PH(13) PH(14)
    PH(15)
#undef PH
    virtual cEditorModel* GetEditorModel();       // +0x40
    int GetEditorSaveability();                   // 0x0057AAA0
    cRect16 GetViewRect();                        // 0x0057A960
    bool IsInPlayMode();                          // 0x00573050
    uint32_t GetPlayModeBrowserLayout();          // 0x005723F0
    uint32_t GetBrowserLayout();                  // 0x005723E0
    bool CanEditAssets();                         // 0x00573950
    void ShowDialog(int a, int b, bool bFlag);    // 0x0058A350
    void ExecuteCommand(bool bFlag, int arg);     // 0x005802F0
    char pad04[0x358 - 4];
    cEditorPlayModeController* mpPlayModeController;   // +0x358
};

class cSPEditorUI : public cSPUIAssetBrowserCallback, public EA::UTFWin::IWinProc,
                    public EA::Messaging::IHandlerRC, public EA::RefCountVTemplate<int> {
public:
    ~cSPEditorUI();
    IWindow* FindWindowByID(uint32_t id) {
        IWindow* pWindow = mLayout.FindWindowByID(id, true);
        if (pWindow)
            return pWindow;
        return mSharedLayout.FindWindowByID(id, true);
    }
    void SetWindowVisibility(uint32_t id, bool bVisible);
    void StartListeningToMessages();
    void StopListeningToMessages();
    void ShowGeneralMessage(const wchar_t* pText);
    void HandleRequestedPostSaveAction(uint32_t action);
    void EnableUIButton(uint32_t id, bool bEnable);
    void SetShowNew(bool bShow);
    void SetShowSave(bool bShow);
    void SetShowPublish(bool bShow);
    void SetShowLoad(bool bShow);
    bool IsLoadDialog(uint32_t dialogID);
    void SetLoadDialogOptions(bool bUseDialog, int source, bool bFlag);
    bool OnPaletteDrop(cRect16 a, cRect16 b, Key key);
    void SelectKeyA();
    void SelectKeyB();
    void UpdateSaveButtons();
    void EnableUndoRedo(bool bEnable);
    void OnPaletteClick(cRect16 a);
    void OpenDialog(uint32_t dialogID, bool bFlag);

    cSPUILayout mLayout;                           // +0x14
    cSPUILayout mSharedLayout;                     // +0x2c
    cSPUILayout mCameraControlsLayout;             // +0x44
    cAppModeEditorBase* mApp;                      // +0x5c
    uint32_t pad60[6];
    EA::AutoRefCount<cRefObject1> mRef78;          // +0x78
    EA::AutoRefCount<cRefObject1> mRef7C;          // +0x7c
    uint32_t pad80[2];
    EA::AutoRefCount<cSPUITooltipWinProc> mSaveTooltip;   // +0x88
    EA::AutoRefCount<cRefObject1> mRef8C;          // +0x8c
    EA::AutoRefCount<cRefObject1> mRef90;          // +0x90
    uint32_t pad94;
    int mGeneralMessageFadeTimer;                  // +0x98
    uint32_t pad9c[6];
    Key mKeyToLoad;                                // +0xb4
    uint32_t padc0[2];
    uint32_t mKeyToLoadType;                       // +0xc8
    uint32_t mCurrentDialogID;                     // +0xcc
    bool mbD0;                                     // +0xd0
    bool mbCanSave;                                // +0xd1
    char padd2[0xe5 - 0xd2];
    bool mbLoadDialogFlag;                         // +0xe5
    char pade6[2];
    EA::AutoRefCount<cSPEditorLoadDialog> mLoadDialog;   // +0xe8
    bool mbUseLoadDialog;                          // +0xec
    int mLoadDialogSource;                         // +0xf0
    bool mbLoadDialogOption;                       // +0xf4
    char padf5[0x100 - 0xf5];
    bool mShowLoad;                                // +0x100
    bool mShowNew;                                 // +0x101
    bool mb102;                                    // +0x102
    bool mbUndoRedoAllowed;                        // +0x103
    bool mbSaveAllowed;                            // +0x104
    bool mShowSave;                                // +0x105
    bool mShowPublish;                             // +0x106
    char pad107;
    EA::AutoRefCount<cRefObject1> mRef108;         // +0x108
    uint32_t pad10c;
    EA::AutoRefCount<cRefObject2> mRef110;         // +0x110
    bool mHandlerInstalled;                        // +0x114
    EA::Messaging::AutoHandler mAutoMsgHandler;    // +0x118
};
extern const uint32_t kEditorUIMessageIDs[7];      // 0x013F9240
}

// @ 0x005DC190
bool cSPEditorUI::OnPaletteDrop(cRect16 a, cRect16 b, Key key)
{
    const int region = HitTestRegion(a, b);
    if (region != 0x1c) {
        cEditorPaletteEntry* pEntry = EditorPaletteDB()->FindEntry(RegionToPaletteID(region));
        if (pEntry) {
            EditorTypeRegistry()->GetProvider()->SetName(pEntry->mName.GetText(0));
            AssignKey(&mKeyToLoad, &key);
            return true;
        }
    }
    return false;
}

// @ 0x005DC250
bool cSPEditorUI::IsLoadDialog(uint32_t dialogID)
{
    return dialogID == 0x102 || dialogID == 0x103 || dialogID == 0x107;
}

// @ 0x005DC280
void cSPEditorUI::SetLoadDialogOptions(bool bUseDialog, int source, bool bFlag)
{
    mbUseLoadDialog = bUseDialog;
    mLoadDialogSource = source;
    mbLoadDialogOption = bFlag;
}

// @ 0x005DC310
IWindow* EmitFindWindowByID(cSPEditorUI* pUI, uint32_t id);
#pragma inline_depth(0)
IWindow* EmitFindWindowByID(cSPEditorUI* pUI, uint32_t id) { return pUI->FindWindowByID(id); }
#pragma inline_depth(254)

// @ 0x005DC340
void cSPEditorUI::SetWindowVisibility(uint32_t id, bool bVisible)
{
    IWindow* pWindow = mLayout.FindWindowByID(id, true);
    if (!pWindow)
        pWindow = mSharedLayout.FindWindowByID(id, true);
    if (pWindow)
        pWindow->SetFlag(1, bVisible);
}

// @ 0x005DC380
void cSPEditorUI::StartListeningToMessages()
{
    if (!mHandlerInstalled) {
        EA::Messaging::IMessageServer* const pServer = MessageServer();
        mAutoMsgHandler.Register(pServer, this, kEditorUIMessageIDs, 7, 0);
        mHandlerInstalled = true;
    }
}

// @ 0x005DC400
void cSPEditorUI::StopListeningToMessages()
{
    if (mHandlerInstalled) {
        mAutoMsgHandler.Unregister();
        mHandlerInstalled = false;
    }
}

// @ 0x005DC460
void cSPEditorUI::ShowGeneralMessage(const wchar_t* pText)
{
    if (FindWindowByID(0x3088953B)) {
        FindWindowByID(0x3088953B)->SetCaption(pText);
        mGeneralMessageFadeTimer = 7000;
    }
}

// @ 0x005DC4D0
void cSPEditorUI::HandleRequestedPostSaveAction(uint32_t action)
{
    if (action == 0x056B7488) {
        cSPUIAssetBrowser::Launch(0xDB184ACB, this, 0x54ACB9F1);
        return;
    }
    cSPUIAssetBrowserLaunchInfo info;
    info.mLayoutID = mApp->IsInPlayMode() ? mApp->GetPlayModeBrowserLayout() : mApp->GetBrowserLayout();
    info.mpCallback = this;
    info.mCallbackID = 0x54ACB9F1;
    info.mbAllowEdit = mApp->CanEditAssets();
    cSPUIAssetBrowser::AdvancedLaunch(info);
}

// @ 0x005DC560
void cSPEditorUI::SelectKeyA()
{
    mKeyToLoadType = kEditorKeyA.mInstance;
    AssignKey(&mKeyToLoad, &kEditorKeyA);
}

// @ 0x005DC580
void cSPEditorUI::SelectKeyB()
{
    mKeyToLoadType = kEditorKeyB.mInstance;
    AssignKey(&mKeyToLoad, &kEditorKeyB);
}

// @ 0x005DC610
void cSPEditorUI::EnableUIButton(uint32_t id, bool bEnable)
{
    if (IWindow* pWindow = FindWindowByID(id)) {
        pWindow->SetFlag(2, bEnable);
        pWindow->SetFlag(0x10, !bEnable);
        if (bEnable)
            pWindow->SetShadeColor(0xFFFFFFFF);
        else
            pWindow->SetShadeColor(0xA0A0A0A0);
        pWindow->Invalidate();
    }
}

// @ 0x005DC6C0
cSPEditorUI::~cSPEditorUI()
{
}

// @ 0x005DC800
void cSPEditorUI::UpdateSaveButtons()
{
    bool bSave = true;
    bool bSaveAs = false;
    bool bEnabled = true;
    const Key* pKey = &mApp->GetEditorModel()->mKey;
    if (EditorUtils::GetCreatorType(pKey)) {
        bSaveAs = true;
        bSave = false;
        bEnabled = false;
    }
    if (mApp->GetEditorSaveability() != 3) {
        bSave = true;
        bEnabled = false;
        bSaveAs = false;
    } else if (GetUploadState(pKey) != 1) {
        bSave = false;
        bSaveAs = false;
    }
    if (!mbCanSave)
        bEnabled = false;
    if (!mbSaveAllowed) {
        bSave = false;
        bSaveAs = false;
    }
    if (IWindow* pWindow = FindWindowByID(0x0612EFEA)) {
        pWindow->SetFlag(1, bSave);
        pWindow->SetFlag(2, bEnabled);
        cString text;
        if (bEnabled)
            text.Load(0xC0152A6D, 0x0612F6B6, 0);
        else
            text.Load(0xC0152A6D, 0x0615DD1C, 0);
        mSaveTooltip->SetText(text.GetText(-1), true);
    }
    if (IWindow* pWindow = FindWindowByID(0x0612EFEB))
        pWindow->SetFlag(1, bSaveAs);
}

// @ 0x005DC970
void cSPEditorUI::EnableUndoRedo(bool bEnable)
{
    if (!mbUndoRedoAllowed)
        bEnable = false;
    if (IWindow* pWindow = FindWindowByID(0x055FDCA8))
        pWindow->SetFlag(2, bEnable);
    if (IWindow* pWindow = FindWindowByID(0x047BC958))
        pWindow->SetFlag(2, bEnable);
}

// @ 0x005DCA00
void cSPEditorUI::OnPaletteClick(cRect16 a)
{
    const int region = HitTestRegion(a, mApp->GetViewRect());
    if (region != 0x1c)
        EditorPaletteDB()->Select(RegionToPaletteID(region));
    if (region == 4 || region == 0x14 || region == 0x15)
        mApp->mpPlayModeController->Activate(true);
}

// @ 0x005DCAA0
void cSPEditorUI::OpenDialog(uint32_t dialogID, bool bFlag)
{
    mCurrentDialogID = dialogID;
    if (IsLoadDialog(dialogID)) {
        if (mbUseLoadDialog) {
            mKeyToLoadType = 0x061C7098;
            mLoadDialog = new ("Editor") cSPEditorLoadDialog(&mKeyToLoad);
            mLoadDialog->Setup(mLoadDialogSource, mbLoadDialogOption);
            mLoadDialog->Show();
            mbLoadDialogFlag = bFlag;
        } else {
            mCurrentDialogID = 0;
            mApp->ShowDialog(0, 2, bFlag);
        }
    } else {
        mApp->ExecuteCommand(bFlag, 0);
    }
}

// @ 0x005DCBA0
void cSPEditorUI::SetShowNew(bool bShow)
{
    mShowNew = bShow;
    if (IWindow* pWindow = FindWindowByID(0x04766FF0))
        pWindow->SetFlag(1, bShow);
}

// @ 0x005DCBF0
void cSPEditorUI::SetShowSave(bool bShow)
{
    mShowSave = bShow;
    if (IWindow* pWindow = FindWindowByID(0x063C290C))
        pWindow->SetFlag(1, bShow);
}

// @ 0x005DCC40
void cSPEditorUI::SetShowPublish(bool bShow)
{
    mShowPublish = bShow;
    if (IWindow* pWindow = FindWindowByID(0x90439D7C))
        pWindow->SetFlag(1, mShowPublish);
}

// @ 0x005DCC90
void cSPEditorUI::SetShowLoad(bool bShow)
{
    mShowLoad = bShow;
    const bool bHide = !bShow;
    if (IWindow* pWindow = FindWindowByID(0x05B6E49C))
        pWindow->SetFlag(1, bShow);
    if (IWindow* pWindow = FindWindowByID(0x04766FE0))
        pWindow->SetFlag(1, bShow);
    if (IWindow* pWindow = FindWindowByID(0x06313DEA))
        pWindow->SetFlag(1, bHide);
    if (IWindow* pWindow = FindWindowByID(0x06313DEB))
        pWindow->SetFlag(1, bHide);
}
