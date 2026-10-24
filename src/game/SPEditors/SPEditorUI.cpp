// src/game/SPEditors/SPEditorUI.cpp -- migrated from slice(s) s00de8ad0, s005dfbb0, s005dec10, s005ddd60, s005dcd80, s005dbd20, s004bd850 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorUI.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWin/IWinProc.h"
#include "EA/UTFWin/CustomWindow.h"
#include "EA/ResourceMan/Key.h"
#include "EA/UTFWin/Message.h"
#include "EA/Variant.h"
#include "SP/cDirectPropertyList.h"
#include "SP/cAppModeEditorBase.h"
#include "EA/Audio/FactoryBinarySampleData.h"
#include "cSPColorRGB.h"
#include "cSPColorRGBA.h"
#include "SP/cSPEditorTuning.h"
#include "SP/cSPEditorUI.h"
#include "SP/cSPUIAssetBrowser.h"
#include "SP/cSPUIAssetBrowserCallback.h"
#include "cSPUILayout.h"
#include "cSPUITooltipWinProc.h"
#include "SP/cString.h"
#include "EA/UTFWinControls/IWinButton.h"
#include "EA/UTFWinControls/IWinGrid.h"
#include "EA/UTFWin/IWindow.h"
#include "EA/UTFWin/WindowMgr.h"
#include "SP/cRenderer.h"
#include "EA/Audio/IPrimitive.h"
#include "SP/cSPPaletteItemUIOneClickPaint.h"
#include "SP/cStarManager.h"

// unnamed retail callees and globals (address in the comment)
extern uint32_t g_15d86fc;
extern uint32_t g_15d860c;
extern uint32_t g_15d86d8;
extern uint32_t g_15d884c;
extern uint32_t g_15d8a40;
extern uint32_t g_15d86e4;
extern uint32_t g_15d87bc;
extern uint32_t g_15d8608;

// ---- items of slice s004bd850 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct PackedKey {
    uint32_t b0 : 8;
    uint32_t b1 : 8;
    uint32_t b2 : 8;
    uint32_t b3 : 6;
    uint32_t b4 : 2;
};
union PackedKeyUnion {
    uint32_t raw;
    PackedKey f;
};
// ---- items of slice s004bd850 end

// ---- items of slice s005dbd20 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new(unsigned int n, const char* pName, int flags = 0, unsigned int debugFlags = 0, const char* pFile = 0, int line = 0) throw();   // 0x00F473A0
namespace EA {
namespace ResourceMan {
struct Key_s005d_bd20 { uint32_t mInstance, mType, mGroup; };
}
}
using EA::ResourceMan::Key_s005d_bd20;
namespace EA {
namespace UTFWin {
struct Message_s005d_bd20 {
    uint32_t pad0[2];
    uint32_t eventType;   // +0x8
    union {
        struct { float x, y; } mouse;             // +0xc
        struct { uint32_t chr, vkey; } key;       // +0xc
    };
    uint32_t modifiers;   // +0x14
    uint32_t button;      // +0x18
};
}
}
namespace EA {
namespace UTFWin {
class IWindow_s005d_bd20 {
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
}
}
namespace EA {
namespace UTFWin {
class IWinProc_s005d_bd20 {
public:
    virtual ~IWinProc_s005d_bd20() {}
    virtual int AddRef() = 0;
    virtual int Release() = 0;
    virtual uint32_t GetEventFlags() = 0;
    virtual bool HandleUIMessage(IWindow_s005d_bd20* pWindow, const Message_s005d_bd20& msg) = 0;
};
}
}
using EA::UTFWin::IWindow_s005d_bd20;
using EA::UTFWin::Message_s005d_bd20;
namespace EA {
namespace Messaging {
void RemoveHandler(void* pServer, void* pHandler, const uint32_t* pIdArray, uint32_t nIdCount, int nPriority);   // 0x00571DB0
}
}
namespace EA {
namespace Messaging {
class IHandler_s005d_bd20 {
public:
    virtual ~IHandler_s005d_bd20() {}
    virtual bool HandleMessage(uint32_t messageID, void* pMessage) = 0;
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};
}
}
namespace EA {
namespace Messaging {
class IHandlerRC_s005d_bd20 : public IHandler_s005d_bd20 {};
}
}
namespace EA {
namespace Messaging {
class IMessageServer {
public:
#define PH(n) virtual void ph##n();
    PH(0) PH(1) PH(2) PH(3) PH(4) PH(5) PH(6) PH(7) PH(8)
#undef PH
    virtual void AddHandler(IHandler_s005d_bd20* pHandler, uint32_t messageID);   // +0x24
};
}
}
namespace EA {
namespace Messaging {
struct AutoHandler_s005d_bd20 {
    IMessageServer* mpServer;        // +0x0
    IHandler_s005d_bd20* mpHandler;             // +0x4
    const uint32_t* mpIdArray;       // +0x8
    uint32_t mnIdArrayCount;         // +0xc
    int mnPriority;                  // +0x10
    ~AutoHandler_s005d_bd20() { Unregister(); }
    void Register(IMessageServer* pServer, IHandler_s005d_bd20* pHandler, const uint32_t* pIdArray, uint32_t nIdCount, int nPriority) {
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
}
}
namespace EA {
template <class T> struct RefCountVTemplate_s005d_bd20 {
    virtual ~RefCountVTemplate_s005d_bd20() {}
    T mRefCount;
};
}
namespace EA {
template <class T> struct AutoRefCount_s005d_bd20 {
    T* mpObject;
    ~AutoRefCount_s005d_bd20() {
        if (mpObject)
            mpObject->Release();
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
    AutoRefCount_s005d_bd20& operator=(T* pObject) {
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
EA::Messaging::IMessageServer* MessageServer_s005d_bd20();   // 0x0067DCC0
}
namespace SP {
class cSPUILayout {
public:
    ~cSPUILayout();                                       // 0x00811FE0
    IWindow_s005d_bd20* FindWindowByID(uint32_t id, bool bRecursive);   // 0x008105B0
    uint32_t mData[6];
};
}
namespace SP {
class cString_s005d_bd20 {
public:
    cString_s005d_bd20();                                            // 0x006B5060
    ~cString_s005d_bd20();                                           // 0x006B5240
    bool Load(uint32_t tableID, uint32_t instanceID, int flags);   // 0x006B54B0
    const wchar_t* GetText(int index);                    // 0x006B55C0
    uint32_t mData[5];
};
}
namespace SP {
class cSPUITooltipWinProc {
public:
    virtual int AddRef();
    virtual int Release();
    void SetText(const wchar_t* pText, bool bRefresh);    // 0x00835ED0
};
}
namespace SP {
struct cRefObject1 {   // AddRef/Release in slots 0/1
    virtual int AddRef();
    virtual int Release();
};
}
namespace SP {
struct cRefObject2 {   // Release in slot 2
    virtual void v0();
    virtual int AddRef();
    virtual int Release();
};
}
namespace SP {
class cSPEditorLoadDialog {
public:
    cSPEditorLoadDialog(Key_s005d_bd20* pKey);                        // 0x005FE600
    virtual int AddRef();
    virtual int Release();
    void Setup(int source, bool bFlag);                    // 0x005FEA60
    void Show();                                           // 0x005FE6C0
    uint32_t mData[7];
};
}
namespace SP {
class cSPUIAssetBrowserCallback_s005d_bd20 {
public:
    virtual void OnAssetBrowserClosed();
};
}
namespace SP {
struct cSPUIAssetBrowserLaunchInfo {
    cSPUIAssetBrowserLaunchInfo();      // 0x00644B10
    ~cSPUIAssetBrowserLaunchInfo();     // 0x00644B60
    uint32_t mLayoutID;                 // +0x0
    uint32_t pad04[3];
    bool mbAllowEdit;                   // +0x10
    uint32_t pad14[7];
    uint32_t mCallbackID;               // +0x30
    uint32_t pad34;
    cSPUIAssetBrowserCallback_s005d_bd20* mpCallback;   // +0x38
    uint32_t pad3c[3];
};
}
namespace SP {
class cSPUIAssetBrowser_s005d_bd20 {
public:
    static void Launch(uint32_t layoutID, cSPUIAssetBrowserCallback_s005d_bd20* pCallback, uint32_t callbackID);   // 0x0064BC50
    static void AdvancedLaunch(cSPUIAssetBrowserLaunchInfo& info);                                      // 0x0064A990
};
}
namespace SP {
class cEditorTypeProvider {
public:
#define PH(n) virtual void ph##n();
    PH(0) PH(1) PH(2) PH(3) PH(4) PH(5) PH(6) PH(7) PH(8) PH(9) PH(10) PH(11) PH(12)
#undef PH
    virtual void SetName(const wchar_t* pName);   // +0x34
};
}
namespace SP {
class cEditorTypeRegistry {
public:
#define PH(n) virtual void ph##n();
    PH(0) PH(1) PH(2) PH(3) PH(4) PH(5) PH(6) PH(7)
#undef PH
    virtual cEditorTypeProvider* GetProvider();   // +0x20
};
}
namespace SP {
cEditorTypeRegistry* EditorTypeRegistry();        // 0x0067DE40
}
namespace SP {
struct cEditorPaletteEntry {
    char pad[0x78];
    cString_s005d_bd20 mName;                                // +0x78
};
}
namespace SP {
class cEditorPaletteDB {
public:
    cEditorPaletteEntry* FindEntry(uint32_t id);  // 0x0067AEE0
    void Select(uint32_t id);                     // 0x0067C830
};
}
namespace SP {
cEditorPaletteDB* EditorPaletteDB();              // 0x0067CAC0
}
namespace SP {
struct cRect16 { float x1, y1, x2, y2; };
}
namespace SP {
int HitTestRegion(cRect16 a, cRect16 b);          // 0x004F3B40
}
namespace SP {
uint32_t RegionToPaletteID(int region);           // 0x004F3C40
}
namespace SP {
void AssignKey(Key_s005d_bd20* pDst, const Key_s005d_bd20* pSrc);       // 0x00809DB0
}
namespace SP {
extern const Key_s005d_bd20 kEditorKeyA;                     // 0x01519940
}
namespace SP {
extern const Key_s005d_bd20 kEditorKeyB;                     // 0x0151994C
}
namespace SP {
namespace EditorUtils {
bool GetCreatorType(const Key_s005d_bd20* pKey);             // 0x00641900
}
}
namespace SP {
int GetUploadState(const Key_s005d_bd20* pKey);              // 0x00552300
}
namespace SP {
class cEditorPlayModeController {
public:
#define PH(n) virtual void ph##n();
    PH(0) PH(1) PH(2) PH(3) PH(4) PH(5) PH(6)
#undef PH
    virtual void Activate(bool bOn);              // +0x1c
};
}
namespace SP {
struct cEditorModel {
    char pad[0xc];
    Key_s005d_bd20 mKey;                                     // +0xc
};
}
namespace SP {
class cAppModeEditorBase_s005d_bd20 {
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
}
namespace SP {
class cSPEditorUI_s005d_bd20 : public cSPUIAssetBrowserCallback_s005d_bd20, public EA::UTFWin::IWinProc_s005d_bd20,
                    public EA::Messaging::IHandlerRC_s005d_bd20, public EA::RefCountVTemplate_s005d_bd20<int> {
public:
    ~cSPEditorUI_s005d_bd20();
    IWindow_s005d_bd20* FindWindowByID(uint32_t id) {
        IWindow_s005d_bd20* pWindow = mLayout.FindWindowByID(id, true);
        if (pWindow)
            return pWindow;
        return mSharedLayout.FindWindowByID(id, true);
    }
    void SetWindowVisibility(uint32_t id, bool bVisible);  // 0x005dc340 (SP::cSPEditorUI::SetWindowVisibility)
    void StartListeningToMessages();  // 0x005dc380 (SP::cSPEditorUI::StartListeningToMessages)
    void StopListeningToMessages();  // 0x005dc400 (SP::cSPEditorUI::StopListeningToMessages)
    void ShowGeneralMessage(const wchar_t* pText);  // 0x005dc460 (SP::cSPEditorUI::ShowGeneralMessage)
    void HandleRequestedPostSaveAction(uint32_t action);  // 0x005dc4d0 (SP::cSPEditorUI::HandleRequestedPostSaveAction)
    void EnableUIButton(uint32_t id, bool bEnable);  // 0x005dc610 (SP::cSPEditorUI::EnableUIButton)
    void SetShowNew(bool bShow);  // 0x005dcba0 (SP::cSPEditorUI::SetShowNew)
    void SetShowSave(bool bShow);  // 0x005dcbf0 (SP::cSPEditorUI::SetShowSave)
    void SetShowPublish(bool bShow);  // 0x005dcc40 (SP::cSPEditorUI::SetShowPublish)
    void SetShowLoad(bool bShow);  // 0x005dcc90 (SP::cSPEditorUI::SetShowLoad)
    bool IsLoadDialog(uint32_t dialogID);  // 0x005dc250 (SP::cSPEditorUI::IsLoadDialog)
    void SetLoadDialogOptions(bool bUseDialog, int source, bool bFlag);  // 0x005dc280 (SP::cSPEditorUI::SetLoadDialogOptions)
    bool OnPaletteDrop(cRect16 a, cRect16 b, Key_s005d_bd20 key);  // 0x005dc190 (SP::cSPEditorUI::OnPaletteDrop)
    void SelectKeyA();  // 0x005dc560 (SP::cSPEditorUI::SelectKeyA)
    void SelectKeyB();  // 0x005dc580 (SP::cSPEditorUI::SelectKeyB)
    void UpdateSaveButtons();  // 0x005dc800 (SP::cSPEditorUI::UpdateSaveButtons)
    void EnableUndoRedo(bool bEnable);  // 0x005dc970 (SP::cSPEditorUI::EnableUndoRedo)
    void OnPaletteClick(cRect16 a);  // 0x005dca00 (SP::cSPEditorUI::OnPaletteClick)
    void OpenDialog(uint32_t dialogID, bool bFlag);  // 0x005dcaa0 (SP::cSPEditorUI::OpenDialog)

    cSPUILayout mLayout;                           // +0x14
    cSPUILayout mSharedLayout;                     // +0x2c
    cSPUILayout mCameraControlsLayout;             // +0x44
    cAppModeEditorBase_s005d_bd20* mApp;                      // +0x5c
    uint32_t pad60[6];
    EA::AutoRefCount_s005d_bd20<cRefObject1> mRef78;          // +0x78
    EA::AutoRefCount_s005d_bd20<cRefObject1> mRef7C;          // +0x7c
    uint32_t pad80[2];
    EA::AutoRefCount_s005d_bd20<cSPUITooltipWinProc> mSaveTooltip;   // +0x88
    EA::AutoRefCount_s005d_bd20<cRefObject1> mRef8C;          // +0x8c
    EA::AutoRefCount_s005d_bd20<cRefObject1> mRef90;          // +0x90
    uint32_t pad94;
    int mGeneralMessageFadeTimer;                  // +0x98
    uint32_t pad9c[6];
    Key_s005d_bd20 mKeyToLoad;                                // +0xb4
    uint32_t padc0[2];
    uint32_t mKeyToLoadType;                       // +0xc8
    uint32_t mCurrentDialogID;                     // +0xcc
    bool mbD0;                                     // +0xd0
    bool mbCanSave;                                // +0xd1
    char padd2[0xe5 - 0xd2];
    bool mbLoadDialogFlag;                         // +0xe5
    char pade6[2];
    EA::AutoRefCount_s005d_bd20<cSPEditorLoadDialog> mLoadDialog;   // +0xe8
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
    EA::AutoRefCount_s005d_bd20<cRefObject1> mRef108;         // +0x108
    uint32_t pad10c;
    EA::AutoRefCount_s005d_bd20<cRefObject2> mRef110;         // +0x110
    bool mHandlerInstalled;                        // +0x114
    EA::Messaging::AutoHandler_s005d_bd20 mAutoMsgHandler;    // +0x118
};
}
namespace SP {
extern const uint32_t kEditorUIMessageIDs[7];      // 0x013F9240
}
// ---- items of slice s005dbd20 end

// ---- items of slice s005dcd80 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void _pv##n();
namespace Math {
struct Rectangle {
  float x1, y1, x2, y2;
  Rectangle(const Rectangle& r) : x1(r.x1), y1(r.y1), x2(r.x2), y2(r.y2) {}
  float GetWidth() const { return x2 - x1; }
  float GetHeight() const { return y2 - y1; }
};  // namespace Math
}
namespace EA {
namespace ResourceMan {
struct Key_s005d_cd80 {
  uint32_t instanceID;
  uint32_t typeID;
  uint32_t groupID;
  Key_s005d_cd80(uint32_t i, uint32_t t, uint32_t g) : instanceID(i), typeID(t), groupID(g) {}
};  // namespace ResourceMan
}
}
namespace EA {
namespace UTFWin {
class IWinProc_s005d_cd80 {
 public:
  PV(0)
};
}
}
namespace EA {
namespace UTFWin {
class IWindow_s005d_cd80;
}
}
namespace EA {
namespace UTFWin {
class IWinButton {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual void SetButtonStateFlag(int flag, bool value);  // +0x28
};
}
}
namespace EA {
namespace UTFWin {
class IWindow_s005d_cd80 {
 public:
  PV(0) PV(1) PV(2)
  virtual void* Cast(uint32_t typeID);                // +0x0c
  virtual IWindow_s005d_cd80* GetParent();                       // +0x10
  PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual uint32_t GetFlags();                        // +0x28
  PV(11) PV(12)
  virtual const Math::Rectangle& GetRealArea();       // +0x34
  virtual const Math::Rectangle& GetArea();           // +0x38
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22)
  virtual void SetShadeColor(uint32_t color);         // +0x5c
  virtual void SetArea(const Math::Rectangle& area);  // +0x60
  virtual void SetSize(float w, float h);             // +0x64
  PV(26)
  virtual void SetLayoutArea(const Math::Rectangle& area);  // +0x6c
  PV(28) PV(29) PV(30)
  virtual void SetFlag(int flag, bool value);         // +0x7c
  PV(32) PV(33) PV(34) PV(35)
  virtual void Revalidate();                          // +0x90
  virtual void Invalidate();                          // +0x94
  PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47)
  PV(48) PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57)
  virtual void BringToFront(IWindow_s005d_cd80* child);          // +0xe8
  PV(59) PV(60) PV(61) PV(62) PV(63) PV(64) PV(65)
  virtual void RemoveWinProc(IWinProc_s005d_cd80* proc);         // +0x108
};
}
}
namespace EA {
namespace UTFWin {
class IWindowManager {
 public:
  PV(0)
  virtual IWindow_s005d_cd80* GetMainWindow();                   // +0x04
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
  PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
  virtual void ReleaseCapture(int type, IWindow_s005d_cd80* w);  // +0x58
  virtual void SetCapture(int type, IWindow_s005d_cd80* w);      // +0x5c
};
}
}
namespace EA {
namespace UTFWinControls {
class IWinGrid_s005d_cd80 {
 public:
  struct Range {
    int left, top, right, bottom;
  };
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
  PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
  PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
  PV(30) PV(31) PV(32) PV(33) PV(34)
  virtual void SetSelectedCell(int index);            // +0x8c
  PV(36) PV(37) PV(38) PV(39) PV(40) PV(41)
  virtual void ScrollToCell(int col, int row);        // +0xa8
  PV(43) PV(44) PV(45) PV(46) PV(47) PV(48)
  virtual bool GetCellRange(Range& range);            // +0xc4
  PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58) PV(59)
  PV(60) PV(61) PV(62) PV(63) PV(64) PV(65) PV(66) PV(67) PV(68) PV(69)
  PV(70) PV(71) PV(72) PV(73) PV(74) PV(75) PV(76) PV(77) PV(78) PV(79)
  PV(80) PV(81) PV(82) PV(83) PV(84) PV(85) PV(86) PV(87) PV(88) PV(89)
  PV(90) PV(91) PV(92) PV(93) PV(94) PV(95) PV(96) PV(97) PV(98) PV(99)
  PV(100) PV(101) PV(102) PV(103) PV(104) PV(105) PV(106) PV(107) PV(108) PV(109)
  PV(110) PV(111) PV(112)
  virtual int GetCellValue(int col, int row);         // +0x1c4
};  // namespace UTFWinControls
}
}
namespace EA {
template <typename T>
class AutoRefCount_s005d_cd80 {
 public:
  T* mpObject;
  AutoRefCount_s005d_cd80& operator=(T* pObject) {
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
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};
}
using EA::UTFWin::IWindow_s005d_cd80;
using EA::UTFWin::IWinButton;
void* operator new(unsigned int size, const char* pName, int flags, unsigned debugFlags,
                   const char* file, int line);
class cSPUILayout_s005d_cd80 {
 public:
  PV(0)
  virtual int AddRef();   // +0x04
  virtual int Release();  // +0x08
  cSPUILayout_s005d_cd80();
  bool Init(const EA::ResourceMan::Key_s005d_cd80& key, bool visible, uint32_t parentID);  // 0x008120d0 (cSPUILayout::Init)
  void SetVisibility(bool visible);  // 0x00810590 (cSPUILayout::SetVisibility)
  IWindow_s005d_cd80* FindWindowByID(uint32_t id, bool recursive);  // 0x008105b0 (cSPUILayout::FindWindowByID)
  void Shutdown(bool unused);  // 0x00811ad0 (cSPUILayout::Shutdown)
  bool SetParentWin(IWindow_s005d_cd80* parent, bool b, uint32_t id);  // 0x008121b0 (cSPUILayout::SetParentWin)
  uint32_t mData[5];
};
namespace SP {
EA::UTFWin::IWindowManager* WindowManager();
}
namespace SP {
namespace SPUIHelpers {
void* GetLayoutManager();
}
}
namespace SP {
namespace SPUIHelpers {
void CenterWindowInRect(IWindow_s005d_cd80* w, const Math::Rectangle& r);
}
}
namespace SP {
namespace EditorUtils {
bool GetCreatorType(const EA::ResourceMan::Key_s005d_cd80* key);
}
}
namespace SP {
struct DialogDesc {
  uint32_t mID;
  uint32_t mData[2];
};
}
namespace SP {
void ShowDialog(void* callback, const DialogDesc* desc);  // FUN_00809db0
}
namespace SP {
class cString_s005d_cd80 {
 public:
  cString_s005d_cd80();
  ~cString_s005d_cd80();
  uint32_t mData[5];
};
}
namespace SP {
struct bitset128 {
  uint32_t mWord[4];
  bitset128() {}
  bitset128(const bitset128& x) {
    mWord[0] = x.mWord[0];
    mWord[1] = x.mWord[1];
    mWord[2] = x.mWord[2];
    mWord[3] = x.mWord[3];
  }
  bitset128 operator~() const {
    bitset128 r;
    r.mWord[0] = ~mWord[0];
    r.mWord[1] = ~mWord[1];
    r.mWord[2] = ~mWord[2];
    r.mWord[3] = ~mWord[3];
    return r;
  }
  bitset128& operator&=(const bitset128& x) {
    mWord[0] &= x.mWord[0];
    mWord[1] &= x.mWord[1];
    mWord[2] &= x.mWord[2];
    mWord[3] &= x.mWord[3];
    return *this;
  }
};
}
namespace SP {
inline bitset128 operator&(const bitset128& a, const bitset128& b) {
  bitset128 r(a);
  r &= b;
  return r;
}
}
namespace SP {
bool BitsetContains(bitset128 a, bitset128 b);  // FUN_004f3d60
}
namespace SP {
class cEditorModel_s005d_cd80 {
 public:
  PV(0)
  virtual uint32_t GetModelType();  // +0x04
  uint32_t pad04[2];
  EA::ResourceMan::Key_s005d_cd80 mKey;        // +0x0c
  char pad18[0x40];
  int mSelectedType;                // +0x58
};
}
namespace SP {
class cAppModeEditorBase_s005d_cd80 {
 public:
  int GetEditorSaveability();  // 0x0057aaa0 (SP::cAppModeEditorBase::GetEditorSaveability)
  bool SetMode(int mode, bool b);  // 0x00587270 (SP::cAppModeEditorBase::SetMode)
  int CanEnterMode(int b);                // FUN_00574a20
  bool IsPaintModeAvailable();            // 0xb1e4d0
  bitset128 GetPartFlags();               // FUN_0057a9e0
  char pad00[0x98];
  cEditorModel_s005d_cd80* mpEditorModel;  // +0x98
};
}
namespace SP {
class cEditorHistory {  // FUN_005d60c0 target (global at 0x15eebec)
 public:
  void SetModelType(uint32_t type);
};
}
namespace SP {
extern cEditorHistory* gEditorHistory;
}
namespace SP {
class IOnlineManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
  virtual void SetState(int s);   // +0x20
  virtual bool IsLoggedIn();      // +0x24
  PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16)
  virtual void Update();          // +0x44
};
}
namespace SP {
IOnlineManager* OnlineManager();  // FUN_00607a60
}
namespace SP {
class IGameCamera {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
  PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
  PV(20) PV(21) PV(22)
  virtual void PushInputMode(int a, int b);  // +0x5c
  virtual void PopInputMode(int a, int b);   // +0x60
};
}
namespace SP {
IGameCamera* CameraManager();  // FUN_0067dd50
}
namespace SP {
class cRenderer_s005d_cd80 {
 public:
  void SetPaused(bool a, bool b);  // FUN_0067c420
};
}
namespace SP {
cRenderer_s005d_cd80* Renderer();  // FUN_0067cac0
}
namespace SP {
class cAudioState {
 public:
  void Push(int a, int b, uint32_t id);  // FUN_0045ae40
  void Pop();                            // FUN_0045b150
};
}
namespace SP {
cAudioState* __stdcall AudioState(uint32_t id);  // FUN_00401050
}
namespace SP {
void PlayUISound(uint32_t id);  // FUN_004a88d0
}
namespace SP {
extern const char kLayoutAllocName[];
}
namespace SP {
extern const EA::ResourceMan::Key_s005d_cd80 kModalLayoutKey;  // 0x151991c
}
namespace SP {
extern const DialogDesc kDialogSaveA;               // 0x1519928
}
namespace SP {
extern const DialogDesc kDialogSaveB;               // 0x1519934
}
namespace SP {
extern const bitset128 gFlagsA;  // 0x15dab94
}
namespace SP {
extern const bitset128 gFlagsB;  // 0x15da7c4
}
namespace SP {
extern const bitset128 gMask;    // 0x15da7ec
}
namespace SP {
class cSPUIAssetBrowserCallback_s005d_cd80 {
 public:
  PV(0)
};
}
namespace SP {
class cSPEditorUI_s005d_cd80 : public cSPUIAssetBrowserCallback_s005d_cd80, public EA::UTFWin::IWinProc_s005d_cd80 {
 public:
  uint32_t pad08[3];
  cSPUILayout_s005d_cd80 mLayout;                                  // +0x14
  cSPUILayout_s005d_cd80 mSharedLayout;                            // +0x2c
  cSPUILayout_s005d_cd80 mCameraControlsLayout;                    // +0x44
  cAppModeEditorBase_s005d_cd80* mApp;                             // +0x5c
  int mUIEditorMode;                                    // +0x60
  IWindow_s005d_cd80* mWinLeftPanelFrame;                          // +0x64
  IWindow_s005d_cd80* mWinPartPaletteRoot;                         // +0x68
  IWindow_s005d_cd80* mWinPaintPaletteRoot;                        // +0x6c
  IWindow_s005d_cd80* mWindowTypeBrowser;                          // +0x70
  EA::UTFWinControls::IWinGrid_s005d_cd80* mGridTypes;             // +0x74
  IWindow_s005d_cd80* mClickCatcher;                               // +0x78
  uint32_t pad7c;
  IWindow_s005d_cd80* mWin80;                                      // +0x80
  IWindow_s005d_cd80* mWin84;                                      // +0x84
  uint32_t pad88[6];
  bool pada0;
  bool mInputBlocked;                                   // +0xa1
  char pada2[0x12];
  uint32_t mDialogResultCallback[2];                    // +0xb4
  uint32_t padbc[3];
  uint32_t mCurrentDialogID;                            // +0xc8
  int mCurrentCommand;                                  // +0xcc
  bool mButtonDepressed;                                // +0xd0
  bool mSaveEnabled;                                    // +0xd1
  char padd2[0x30];
  bool mShowSaveButton;                                 // +0x102
  bool mUIDisabled;                                     // +0x103
  char pad104[0xc];
  EA::AutoRefCount_s005d_cd80<cSPUILayout_s005d_cd80> mpModalLayout;          // +0x110

  IWindow_s005d_cd80* FindWindowByID(uint32_t id) {
    if (IWindow_s005d_cd80* w = mLayout.FindWindowByID(id, true))
      return w;
    return mSharedLayout.FindWindowByID(id, true);
  }
  void SetWindowVisibility(uint32_t id, bool visible);  // 0x005dc340 (SP::cSPEditorUI::SetWindowVisibility)
  void StopListeningToMessages();  // 0x005dc400 (SP::cSPEditorUI::StopListeningToMessages)
  void StartListeningToMessages();  // 0x005dc380 (SP::cSPEditorUI::StartListeningToMessages)
  void UpdateUndoRedo(bool disabled);  // FUN_005dc970
  void UpdateSaveButtons();            // FUN_005dc800
  bool CheckWarnings(bitset128 flags, bitset128 partFlags, EA::ResourceMan::Key_s005d_cd80 key);  // FUN_005dc190

  void SetUIDisabled(bool disabled);
  void EnableRedoButton(bool enable);  // 0x005dce40 (SP::cSPEditorUI::EnableRedoButton)
  void EnableUndoButton(bool enable);  // 0x005dceb0 (SP::cSPEditorUI::EnableUndoButton)
  void SetSelected(uint32_t id, bool selected, bool alsoState20);  // 0x005dcf20 (SP::cSPEditorUI::SetSelected)
  void EnablePlayModeButton(bool enable);  // 0x005dcf90 (SP::cSPEditorUI::EnablePlayModeButton)
  void Hide();  // 0x005dd050 (SP::cSPEditorUI::Hide)
  void Show();  // 0x005dd070 (SP::cSPEditorUI::Show)
  void SetInputBlocked(bool blocked);
  void SelectCurrentTypeInGrid();
  void ShowSaveDialog();
  void OnSaveRequested();
  void OnLoginResult(bool success);
  void CloseModalLayout();
  void OpenModalLayout();
  void SetPaintMode(bool paint);
  void UpdateUIBasedOnModelSaveability();  // 0x005dd7a0 (SP::cSPEditorUI::UpdateUIBasedOnModelSaveability)
  uint32_t GetWarning(bitset128 flags);
  void SetMode(int mode);  // 0x005dda30 (SP::cSPEditorUI::SetMode)
};
}
// ---- items of slice s005dcd80 end

// ---- items of slice s005ddd60 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern unsigned g_basicButtonIds[18];  // 0x01519a60
extern char* g_ptr15fd918;             // 0x015fd918 (struct whose +0x3c holds a state block)
extern char vtblA_13f92dc[], vtblA_13f92c0[], vtblA_13f92b0[], vtblA_13f92a0[];
extern char vtblB_14426a0[], vtblB_13eb384[], vtblB_13ec458[], vtblC_13f925c[];
struct Widget;
struct Widget {
    virtual void v0();
    virtual void Release();
    virtual void v2();
    virtual Widget* GetChild(unsigned id);
    virtual Widget* GetParent();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual int GetFlags();
    virtual void v9();
    virtual void SetState(int, int);
    virtual void v11();
    virtual unsigned GetColor();
    virtual float* GetArea();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void SetLayoutId(unsigned id);
    virtual void v21();
    virtual void v22();
    virtual void SetColor(unsigned c);
    virtual void SetArea(const float* r);
    virtual void SetSize(float w, float h);
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void SetFlag(int flag, int on);
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void Refresh();
    virtual void Notify();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void Slot42(int, int);
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual void v53();
    virtual void v54();
    virtual void RemoveChild(Widget* w);
    virtual void v56();
    virtual void v57();
    virtual void AddChild(Widget* w);
    virtual void v59();
    virtual void v60();
    virtual void v61();
    virtual void v62();
    virtual void v63();
    virtual void v64();
    virtual void AddWinProc(void* p);
    virtual void RemoveWinProc(void* p);
    virtual void v67();
    virtual void v68();
    virtual void v69();
    virtual void v70();
    virtual void v71();
    virtual void v72();
    virtual void v73();
    virtual void v74();
    virtual void v75();
    virtual void v76();
    virtual void v77();
    virtual void v78();
    virtual void v79();
    virtual void v80();
    virtual void v81();
    virtual void v82();
    virtual void v83();
    virtual void v84();
    virtual void v85();
    virtual void v86();
    virtual void v87();
    virtual void v88();
    virtual void v89();
    virtual void v90();
    virtual void v91();
    virtual void v92();
    virtual void v93();
    virtual void v94();
    virtual void v95();
    virtual void v96();
    virtual void v97();
    virtual void v98();
    virtual void v99();
    virtual void v100();
    virtual void v101();
    virtual void v102();
    virtual void v103();
    virtual void v104();
    virtual void GridSetItem(int, int, void* v);
    virtual void v106();
    virtual void v107();
    virtual void v108();
    virtual void v109();
    virtual void v110();
    virtual void v111();
    virtual void GridSetData(int, int, void* v);
};
struct Key { unsigned inst, type, group; };
struct Layout {
    Widget* FindWindowByID(int id, int recurse);       // 0x008105b0
    bool Init(const Key* key, int a, unsigned id);     // 0x008120d0
    bool Init(const wchar_t* name, unsigned group, int a, unsigned id); // 0x00812160
    void SetParentWin(Widget* w, int a, unsigned id);  // 0x008121b0
    void SetVisibility(int v);                         // 0x00810590
    void Shutdown(int a);                              // 0x00811ad0
    void Ctor();                                       // 0x00810000
    char pad[0x18];
};
template <class T> struct Ref {       // AutoRefCount::operator=
    T* p;
    Ref& Set(T* v);                   // 0x00b5f950
};
struct IBase { virtual void a(); };
struct RCBase { virtual void rcv(); int rc; RCBase() : rc(0) {} };
struct BlockerBase : IBase, RCBase { Widget* app; };
struct BlockerA : BlockerBase { virtual void a(); virtual void rcv(); BlockerA() {} };
struct BlockerB : BlockerBase { virtual void a(); virtual void rcv(); BlockerB() { app = 0; } };
void* operator new(unsigned size, const char* tag, int a, int b, int c, int d);   // 0x00f473a0
struct TooltipProc {
    void Ctor();                       // 0x00835cc0
};
void* AllocTooltip(int size, const char* name, int a, void* pool);   // 0x009512d0 (cdecl)
void* GetTooltipPool();                                // 0x009512c0
Widget* CreateWindowFor(Widget* parent);               // 0x00806370 (cdecl)
void SetWindowAlpha(Widget* w, float a);               // 0x00804fc0 (cdecl)
struct WMgr { virtual void v0(); virtual Widget* GetRoot(); };
WMgr* WindowManager_s005d_dd60();                                 // 0x0067caa0
struct LayoutMgr { Widget* GetWorldMainWindow(); };    // 0x00810620
LayoutMgr* __stdcall GetLayoutManager(unsigned id);    // 0x00805070
struct CursorMgr { void SetLocalCursor(); };           // 0x00801bb0
CursorMgr* __stdcall GetCursorManager(int id);         // 0x0067cab0
Widget* InterfaceCast(Widget* w);                      // 0x005dc6a0 (cdecl)
void* MakeGridCell(void* item, int a, int b, int c);   // 0x004bb510 (cdecl)
unsigned ColorRGBAToU32(const float* c);               // 0x004580c0 (cdecl)
struct TerrainTool { void Brush5a2200(float v); void Brush5a2240(float v); };   // 0x005a2200 / 0x005a2240
struct AppMode {
    void NewModel(int);                // 0x0058d1c0
    TerrainTool* FUN_00574590();
    bool IsAvailable();                // 0x00b1e4d0
    char pad[0x31c];
    int mMode;                         // +0x31c
    char pad2[0x14];
    void** mItemsBegin;                // +0x334
    void** mItemsEnd;                  // +0x338
};
struct WinCtl {
    virtual void v0();
    virtual void Release();            // vtable slot 1 (the original calls [vtbl+4])
    void FUN_005fe650();
};
struct EditorUI {
    void* vt0; void* vt4; void* vt8; void* vtc; int f10;
    Layout mLayout;      // +0x14
    Layout mCamera;      // +0x2c
    Layout mPalette;     // +0x44
    AppMode* mApp;       // +0x5c
    Widget* f60;
    Widget* mBudget;     // +0x64
    Widget* mComplexity; // +0x68
    Widget* mHighlight;  // +0x6c
    Widget* mCapture;    // +0x70
    Widget* mGrid;       // +0x74
    Ref<Widget> mClick;  // +0x78
    Ref<BlockerBase> mClickProc;   // +0x7c
    Widget* f80;
    Widget* f84;
    Ref<TooltipProc> mTooltip;     // +0x88
    Ref<Widget> mBlock;            // +0x8c
    Ref<BlockerBase> mBlockProc;   // +0x90
    int f94;
    int mFade;           // +0x98
    int f9c;
    char fa0, fa1, fa2, fa3;
    int fa4, fa8, fac, fb0;
    void* fb4; EditorUI* fb8; int fbc, fc0, fc4, fc8, fcc;
    char fd0, fd1, fd2, fd3;
    int fd4, fd8, fdc, fe0;
    char fe4, fe5, fe6, fe7;
    WinCtl* mfe8;        // +0xe8
    char fec, fed, fee, fef;
    int ff0; char ff4, ff5, ff6, ff7;
    int ff8, ffc;
    char f100, f101, f102, f103, f104, f105, f106, f107;
    int f108; char f10c, f10d, f10e, f10f;
    int f110; char f114, f115, f116, f117;
    int f118, f11c, f120, f124, f128;

    void SetMode(int);                       // 0x005dda30
    void FUN_005de9e0();
    EditorUI* Construct();
    bool Init(AppMode* app, int a2, unsigned a3, int a4);
    void Update(int dt);
    void EnableBasicEditorButtons(int a, char b);
    bool Shutdown();
    void StopListeningToMessages();
    void StartListeningToMessages();
    void UpdateUIBasedOnModelSaveability();  // 0x005dd7a0
    void UpdateSaveButtons();                // 0x005dc800
    void FUN_005dc970(int a);
    void FUN_005dd090(int a);
    void FUN_005dd390();
    void FUN_005dc5a0(unsigned a);           // 0x005dc5a0
    Widget* FUN_005dc310(unsigned id);
    void SetSelected(unsigned id, int a, int b);
};
static __forceinline Widget* FindWindow(EditorUI* p, unsigned id)
{
    Widget* w = p->mLayout.FindWindowByID(id, 1);
    if (!w)
        w = p->mCamera.FindWindowByID(id, 1);
    return w;
}
static __forceinline void ReleaseRef(Widget** pp)
{
    Widget* o = *pp;
    if (o) {
        *pp = 0;
        ((WinCtl*)o)->Release();
    }
}
static __forceinline void SetButton(Widget* w, int on, char c)
{
    w->SetFlag(2, on);
    w->SetFlag(0x10, c == 0);
    w->Notify();
}
static __forceinline void DetachPair(Widget** pOwner, Widget** pProc)
{
    Widget* owner = *pOwner;
    if (owner) {
        if (*pProc) {
            owner->RemoveWinProc(*pProc);
            ReleaseRef(pProc);
        }
        if (owner->GetParent())
            owner->GetParent()->RemoveChild(*pOwner);
        ReleaseRef(pOwner);
    }
}
// ---- items of slice s005ddd60 end

// ---- items of slice s005dec10 begin (TODO(rewrite): local stubs, replace by canonical classes)
    void CalloutMessageBox(...); // 0x00809db0
#undef ui
struct Layout_s005d_ec10 {
    void* FindWindowByID(int, int);   // 0x8105b0
    char pad[0x18];
};
struct Widget_s005d_ec10 {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
    virtual char Slot10();         // +0x28
};
__forceinline Widget_s005d_ec10* FindWindowRaw(void* base, int id)
{
    Widget_s005d_ec10* w = (Widget_s005d_ec10*)((Layout_s005d_ec10*)((char*)base + 0x14))->FindWindowByID(id, 1);
    if (!w)
        w = (Widget_s005d_ec10*)((Layout_s005d_ec10*)((char*)base + 0x2c))->FindWindowByID(id, 1);
    return w;
}
void __cdecl FUN_004a88d0(int);
struct EditorFrame {
    char pad[0xcc];
    int mcc;              // +0xcc
    void FUN_005df470(int a, int b);
    void FUN_005df8d0();
};
struct DialogTarget { void DoDialogEnd(int code); };
struct EditorFrame2 {
    char pad[4];
    DialogTarget* mpTarget;   // +0x04
    void FUN_005dfb30(int a, int b);
};
struct EditorUI2 {
    char pad[0x5c];
    void* m5c;                // +0x5c
    char pad60[0x18];
    void* m78;                // +0x78
    char pad7c[0x50];
    int mcc;                  // +0xcc
    void FUN_005df470(int a, int b);
    void DoSaveAndExit();
};
struct Key12 { uint32_t a, b, c; };
struct Key16 { uint32_t a, b, c, d; };
struct Res {
    virtual void v0();
    virtual void Release();           // +4
    virtual void v2();
    virtual void* QueryInterface(uint32_t id);   // +0xc
};
struct EditorRes { char pad[0x18]; uint32_t mType; };
struct ResMgr {
virtual void v0();
virtual void v1();
virtual void v2();
    virtual bool GetResource(const Key12* key, Res** out, int, int, int, int);   // +0xc
};
struct MsgServer {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
    virtual void Post(uint32_t id, int, int, int);      // +0x18
};
struct ConfigMgr {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
    virtual void SetValue(uint32_t id, int v);          // +0x2c
virtual void v12();
virtual void v13();
virtual void v14();
    virtual void Commit();                              // +0x3c
};
struct AudioSys {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
    virtual uint32_t GetValue();                        // +0x20
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
    virtual void v13();
    virtual void Begin(uint32_t id);                    // +0x38
    virtual void v15();
    virtual void SetParam(uint32_t id, uint32_t v);     // +0x40
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
    virtual void v21();
    virtual void End();                                 // +0x58
};
struct WinObj {
    virtual void v0();
    virtual void Release();           // +4
    char pad[0x18];
    WinObj(void* a);                  // FUN_005fe600
    bool FUN_005fe5f0();
    uint32_t GetAccessFlags();        // 0xff0420
    uint32_t FUN_006c0200();
    void FUN_005fea60(uint32_t a, uint8_t b);
    void FUN_005fe6c0();
};
void* __cdecl operator new(unsigned int, const char*, int, int, int, int);   // 0xf473a0
struct RefPtr {
    WinObj* p;
    void assign(WinObj* o);   // 0xb5f950
};
struct AppBase {
    char pad[0x4b1];
    char m4b1;
    int GetEditorSaveability();                         // 0x57aaa0
    void FUN_00572190(Key16* out);
    Key16* FUN_00572160(Key16* out);
    Key16* GetMask(Key16* out);                         // 0x57a960
    void FUN_005724a0();
    bool FUN_00574d60();
    bool FUN_00573070(EditorRes* r);
    bool FUN_00573050();
    void FUN_00573fb0();
    void SetCurrentConfig(uint32_t cfg, Key12 key);   // 0x579720
    void LoadModelKey(const Key12* k, Key16 k16, int f);   // 0x58cee0
    void LoadModel(int a, int b, int c);                   // 0x58a350
    void FUN_005721b0(Key16 a, Key16 b);
};
ResMgr* __cdecl GetManager();   // 0x67dcd0
MsgServer* __cdecl GetMessageServer();   // 0x67dcc0
ConfigMgr* __cdecl GetConfigManager();   // 0x67dd30
AudioSys* __cdecl GetSystemAT();   // 0xa206f0
uint32_t __cdecl RemapTypeId(uint32_t t);   // 0x432f10
EditorRes* __cdecl interface_cast_EditorRes(Res** r);   // 0x421eb0
struct Obj67 { void FUN_0067c830(); };
Obj67* __stdcall FUN_0067cac0(uint32_t id);
struct Obj45 { void FUN_0045ae10(); };
Obj45* __stdcall FUN_00401050(uint32_t id, int x);
void __cdecl CalloutMessageBox(void* where, const Key12* key);   // 0x809db0
bool __cdecl FUN_004f3d60(Key16 a, Key16 b);
void __cdecl FUN_004a88d0_(uint32_t id);
extern Key12 g1519958, g1519964, g1519970, g151997c, g1519988, g15199a0, g15199b8, g15199c4,
    g15199dc, g15199e8, g15199f4, g1519a0c, g1519a3c, g15199d0, g15199ec, g1519994, g1519a00;
struct EditorResOps : EditorRes { void FUN_004bac30(Key16* out, Key16 k, int f); };
void __cdecl AssetBrowserLaunch(uint32_t a, void* b, uint32_t c);
struct EUI {
    char pad0[0x5c];
    AppBase* app;                 // +0x5c
    char pad60[0x40];
    uint8_t ma0;                  // +0xa0
    char pada1[0x13];
    char mb4[8];                  // +0xb4 callout target
    Key12 mkey;                   // +0xbc
    uint32_t mc8;                 // +0xc8
    uint32_t mcc;                 // +0xcc
    uint8_t md0;                  // +0xd0
    char padd1[3];
    Key16 msaved;                 // +0xd4
    uint8_t me4;                  // +0xe4
    uint8_t me5;                  // +0xe5
    char pade6[2];
    RefPtr me8;                   // +0xe8
    uint8_t mec;                  // +0xec
    char paded[3];
    uint32_t mf0;                 // +0xf0
    uint8_t mf4;                  // +0xf4
    char padf5[3];
    uint32_t mf8;                 // +0xf8
    uint32_t mfc;                 // +0xfc

    void FUN_005dec10(uint32_t a);
    void FUN_005def30(uint32_t param);
    void FUN_005df470(uint32_t cmd, int b);
    bool FUN_005df8f0(Key12 key);
    bool FUN_005dc250(uint32_t cmd);
    void FUN_005dcaa0(uint32_t cmd, uint32_t flag);
    void FUN_005dca00(Key16 k);
    void FUN_005dc190(Key16 a, Key16 b, Key12 c);
    uint32_t FUN_005dd860(Key16 k);
    void FUN_005dd360(bool b);
    void FUN_005dc4d0(int a);
    void FUN_005dda30(int a);
    void FUN_005de9e0();
};
struct HandlerSub {
    char pad[0xac];
    char mac[0x14];              // +0xac (= EUI +0xb4)
    uint32_t mc0;                // +0xc0 (= EUI +0xc8)
    uint32_t mc4;                // +0xc4 (= EUI +0xcc)
    bool HandleMessage(uint32_t msg, int data);
};
    void* operator new(unsigned int, char*, int, int, int, int); // 0x00f473a0
// ---- items of slice s005dec10 end

// ---- items of slice s00de8ad0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern bool gbSkipSave;                                                  // 0x016a0f28
typedef wchar_t char16;
struct ResourceKey { uint32_t instanceID, typeID, groupID; };
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
struct cString {
    uint32_t mData[4];
    cString();                                                            // 0x006b5060
    ~cString();                                                           // 0x006b5240
    void Load(uint32_t tableID, uint32_t instanceID, const char16* pDefault);  // 0x006b54b0
    const char16* GetText();                                              // 0x006b55c0
};
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
struct cCalloutTarget { uint32_t pad; };
extern cCalloutTarget gCalloutTarget;                                    // 0x015a41d4
extern const ResourceKey kCalloutPublish;                                // 0x015a3860
extern const ResourceKey kCalloutSave;                                   // 0x015a386c
extern const ResourceKey kCalloutSaveConfirm;                            // 0x015a3878
extern const ResourceKey kCalloutExit;                                   // 0x015a3884
extern const ResourceKey kCalloutError;                                  // 0x015a3890
extern const ResourceKey kCalloutExitConfirm;                            // 0x015a389c
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
};
// ---- items of slice s00de8ad0 end

// @ 0x004bd850
uint32_t FUN_004bd850(uint32_t key)
{
    switch (key) {
    case 0x6fd7d545: {
        PackedKeyUnion u;
        u.raw = 0;
        u.f.b4 = 1;
        u.f.b2 = 0x60;
        u.f.b1 = 0x60;
        return u.raw;
    }
    case 0xe67cff28: return g_15d86fc;
    case 0xf1fac055: return g_15d860c;
    case 0x3d0706da: return g_15d86d8;
    case 0x9735dda7: return g_15d86d8;
    case 0x3673ceff: return g_15d884c;
    case 0x326ba4c4: return g_15d860c;
    case 0x8c6f7366: return g_15d8a40;
    case 0xffbbdaee: return g_15d86e4;
    case 0x3d644e05: return g_15d87bc;
    case 0x46f485f5: return g_15d8608;
    default: return key;
    }
}

// @ 0x005dc190
bool SP::cSPEditorUI_s005d_bd20::OnPaletteDrop(SP::cRect16 a, SP::cRect16 b, Key_s005d_bd20 key)
{
    const int region = SP::HitTestRegion(a, b);
    if (region != 0x1c) {
        SP::cEditorPaletteEntry* pEntry = SP::EditorPaletteDB()->FindEntry(SP::RegionToPaletteID(region));
        if (pEntry) {
            SP::EditorTypeRegistry()->GetProvider()->SetName(pEntry->mName.GetText(0));
            SP::AssignKey(&mKeyToLoad, &key);
            return true;
        }
    }
    return false;
}

// @ 0x005dc250
bool SP::cSPEditorUI_s005d_bd20::IsLoadDialog(uint32_t dialogID)
{
    return dialogID == 0x102 || dialogID == 0x103 || dialogID == 0x107;
}

// @ 0x005dc280
void SP::cSPEditorUI_s005d_bd20::SetLoadDialogOptions(bool bUseDialog, int source, bool bFlag)
{
    mbUseLoadDialog = bUseDialog;
    mLoadDialogSource = source;
    mbLoadDialogOption = bFlag;
}

// @ 0x005dc340
void SP::cSPEditorUI_s005d_bd20::SetWindowVisibility(uint32_t id, bool bVisible)
{
    IWindow_s005d_bd20* pWindow = mLayout.FindWindowByID(id, true);
    if (!pWindow)
        pWindow = mSharedLayout.FindWindowByID(id, true);
    if (pWindow)
        pWindow->SetFlag(1, bVisible);
}

// @ 0x005dc380
void SP::cSPEditorUI_s005d_bd20::StartListeningToMessages()
{
    if (!mHandlerInstalled) {
        EA::Messaging::IMessageServer* const pServer = SP::MessageServer_s005d_bd20();
        mAutoMsgHandler.Register(pServer, this, SP::kEditorUIMessageIDs, 7, 0);
        mHandlerInstalled = true;
    }
}

// @ 0x005dc400
void SP::cSPEditorUI_s005d_bd20::StopListeningToMessages()
{
    if (mHandlerInstalled) {
        mAutoMsgHandler.Unregister();
        mHandlerInstalled = false;
    }
}

// @ 0x005dc460
void SP::cSPEditorUI_s005d_bd20::ShowGeneralMessage(const wchar_t* pText)
{
    if (FindWindowByID(0x3088953B)) {
        FindWindowByID(0x3088953B)->SetCaption(pText);
        mGeneralMessageFadeTimer = 7000;
    }
}

// @ 0x005dc4d0
void SP::cSPEditorUI_s005d_bd20::HandleRequestedPostSaveAction(uint32_t action)
{
    if (action == 0x056B7488) {
        SP::cSPUIAssetBrowser_s005d_bd20::Launch(0xDB184ACB, this, 0x54ACB9F1);
        return;
    }
    SP::cSPUIAssetBrowserLaunchInfo info;
    info.mLayoutID = mApp->IsInPlayMode() ? mApp->GetPlayModeBrowserLayout() : mApp->GetBrowserLayout();
    info.mpCallback = this;
    info.mCallbackID = 0x54ACB9F1;
    info.mbAllowEdit = mApp->CanEditAssets();
    SP::cSPUIAssetBrowser_s005d_bd20::AdvancedLaunch(info);
}

// @ 0x005dc560
void SP::cSPEditorUI_s005d_bd20::SelectKeyA()
{
    mKeyToLoadType = SP::kEditorKeyA.mInstance;
    SP::AssignKey(&mKeyToLoad, &SP::kEditorKeyA);
}

// @ 0x005dc580
void SP::cSPEditorUI_s005d_bd20::SelectKeyB()
{
    mKeyToLoadType = SP::kEditorKeyB.mInstance;
    SP::AssignKey(&mKeyToLoad, &SP::kEditorKeyB);
}

// @ 0x005dc610
void SP::cSPEditorUI_s005d_bd20::EnableUIButton(uint32_t id, bool bEnable)
{
    if (IWindow_s005d_bd20* pWindow = FindWindowByID(id)) {
        pWindow->SetFlag(2, bEnable);
        pWindow->SetFlag(0x10, !bEnable);
        if (bEnable)
            pWindow->SetShadeColor(0xFFFFFFFF);
        else
            pWindow->SetShadeColor(0xA0A0A0A0);
        pWindow->Invalidate();
    }
}

// @ 0x005dc6c0
SP::cSPEditorUI_s005d_bd20::~cSPEditorUI_s005d_bd20()
{
}

// @ 0x005dc800
void SP::cSPEditorUI_s005d_bd20::UpdateSaveButtons()
{
    bool bSave = true;
    bool bSaveAs = false;
    bool bEnabled = true;
    const Key_s005d_bd20* pKey = &mApp->GetEditorModel()->mKey;
    if (EditorUtils::GetCreatorType(pKey)) {
        bSaveAs = true;
        bSave = false;
        bEnabled = false;
    }
    if (mApp->GetEditorSaveability() != 3) {
        bSave = true;
        bEnabled = false;
        bSaveAs = false;
    } else if (SP::GetUploadState(pKey) != 1) {
        bSave = false;
        bSaveAs = false;
    }
    if (!mbCanSave)
        bEnabled = false;
    if (!mbSaveAllowed) {
        bSave = false;
        bSaveAs = false;
    }
    if (IWindow_s005d_bd20* pWindow = FindWindowByID(0x0612EFEA)) {
        pWindow->SetFlag(1, bSave);
        pWindow->SetFlag(2, bEnabled);
        SP::cString_s005d_bd20 text;
        if (bEnabled)
            text.Load(0xC0152A6D, 0x0612F6B6, 0);
        else
            text.Load(0xC0152A6D, 0x0615DD1C, 0);
        mSaveTooltip->SetText(text.GetText(-1), true);
    }
    if (IWindow_s005d_bd20* pWindow = FindWindowByID(0x0612EFEB))
        pWindow->SetFlag(1, bSaveAs);
}

// @ 0x005dc970
void SP::cSPEditorUI_s005d_bd20::EnableUndoRedo(bool bEnable)
{
    if (!mbUndoRedoAllowed)
        bEnable = false;
    if (IWindow_s005d_bd20* pWindow = FindWindowByID(0x055FDCA8))
        pWindow->SetFlag(2, bEnable);
    if (IWindow_s005d_bd20* pWindow = FindWindowByID(0x047BC958))
        pWindow->SetFlag(2, bEnable);
}

// @ 0x005dca00
void SP::cSPEditorUI_s005d_bd20::OnPaletteClick(SP::cRect16 a)
{
    const int region = SP::HitTestRegion(a, mApp->GetViewRect());
    if (region != 0x1c)
        SP::EditorPaletteDB()->Select(SP::RegionToPaletteID(region));
    if (region == 4 || region == 0x14 || region == 0x15)
        mApp->mpPlayModeController->Activate(true);
}

// @ 0x005dcaa0
void SP::cSPEditorUI_s005d_bd20::OpenDialog(uint32_t dialogID, bool bFlag)
{
    mCurrentDialogID = dialogID;
    if (IsLoadDialog(dialogID)) {
        if (mbUseLoadDialog) {
            mKeyToLoadType = 0x061C7098;
            mLoadDialog = new ("Editor") SP::cSPEditorLoadDialog(&mKeyToLoad);
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

// @ 0x005dcba0
void SP::cSPEditorUI_s005d_bd20::SetShowNew(bool bShow)
{
    mShowNew = bShow;
    if (IWindow_s005d_bd20* pWindow = FindWindowByID(0x04766FF0))
        pWindow->SetFlag(1, bShow);
}

// @ 0x005dcbf0
void SP::cSPEditorUI_s005d_bd20::SetShowSave(bool bShow)
{
    mShowSave = bShow;
    if (IWindow_s005d_bd20* pWindow = FindWindowByID(0x063C290C))
        pWindow->SetFlag(1, bShow);
}

// @ 0x005dcc40
void SP::cSPEditorUI_s005d_bd20::SetShowPublish(bool bShow)
{
    mShowPublish = bShow;
    if (IWindow_s005d_bd20* pWindow = FindWindowByID(0x90439D7C))
        pWindow->SetFlag(1, mShowPublish);
}

// @ 0x005dcc90
void SP::cSPEditorUI_s005d_bd20::SetShowLoad(bool bShow)
{
    mShowLoad = bShow;
    const bool bHide = !bShow;
    if (IWindow_s005d_bd20* pWindow = FindWindowByID(0x05B6E49C))
        pWindow->SetFlag(1, bShow);
    if (IWindow_s005d_bd20* pWindow = FindWindowByID(0x04766FE0))
        pWindow->SetFlag(1, bShow);
    if (IWindow_s005d_bd20* pWindow = FindWindowByID(0x06313DEA))
        pWindow->SetFlag(1, bHide);
    if (IWindow_s005d_bd20* pWindow = FindWindowByID(0x06313DEB))
        pWindow->SetFlag(1, bHide);
}

// @ 0x005dcd80
namespace SP {
void cSPEditorUI_s005d_cd80::SetUIDisabled(bool disabled)
{
  mUIDisabled = disabled;
  if (IWindow_s005d_cd80* w = FindWindowByID(0x682102a))
    w->SetFlag(1, !disabled);
  if (IWindow_s005d_cd80* w = FindWindowByID(0x682102b))
    w->SetFlag(1, !disabled);
  UpdateUndoRedo(mUIDisabled);
}
}  // namespace SP

// @ 0x005dce40
namespace SP {
void cSPEditorUI_s005d_cd80::EnableRedoButton(bool enable)
{
  IWindow_s005d_cd80* w = FindWindowByID(0xf006efa5);
  if (w) {
    w->SetFlag(2, enable);
    w->SetFlag(0x10, !enable);
    w->Invalidate();
  }
}
}  // namespace SP

// @ 0x005dceb0
namespace SP {
void cSPEditorUI_s005d_cd80::EnableUndoButton(bool enable)
{
  IWindow_s005d_cd80* w = FindWindowByID(0xb006ef6e);
  if (w) {
    w->SetFlag(2, enable);
    w->SetFlag(0x10, !enable);
    w->Invalidate();
  }
}
}  // namespace SP

// @ 0x005dcf20
namespace SP {
void cSPEditorUI_s005d_cd80::SetSelected(uint32_t id, bool selected, bool alsoState20)
{
  IWindow_s005d_cd80* w = FindWindowByID(id);
  if (w) {
    IWinButton* button = (IWinButton*)w->Cast(0x8ed27e7a);
    button->SetButtonStateFlag(4, selected);
    if (alsoState20)
      button->SetButtonStateFlag(0x20, selected);
    w->Invalidate();
  }
}
}  // namespace SP

// @ 0x005dcf90
namespace SP {
void cSPEditorUI_s005d_cd80::EnablePlayModeButton(bool enable)
{
  IWindow_s005d_cd80* button = FindWindowByID(0x70218642);
  IWindow_s005d_cd80* blocker = FindWindowByID(0x66ff240);
  if (button) {
    button->SetFlag(2, enable);
    button->SetFlag(0x10, !enable);
    if (enable)
      button->SetShadeColor(0xffffffff);
    else
      button->SetShadeColor(0xa0a0a0a0);
    button->Revalidate();
  }
  if (blocker)
    blocker->SetFlag(1, !enable);
}
}  // namespace SP

// @ 0x005dd050
void SP::cSPEditorUI::Hide()
{
  mLayout.SetVisibility(false);
  mSharedLayout.SetVisibility(false);
  StopListeningToMessages();
}

// @ 0x005dd070
void SP::cSPEditorUI::Show()
{
  StartListeningToMessages();
  mLayout.SetVisibility(true);
  mSharedLayout.SetVisibility(true);
}

// @ 0x005dd090
namespace SP {
void cSPEditorUI_s005d_cd80::SetInputBlocked(bool blocked)
{
  bool wasBlocked = mInputBlocked;
  mInputBlocked = blocked;
  if (mClickCatcher) {
    mClickCatcher->SetFlag(1, !blocked);
    if (!mInputBlocked) {
      IWindow_s005d_cd80* parent = mClickCatcher->GetParent();
      if (parent) {
        Math::Rectangle area = parent->GetRealArea();
        mClickCatcher->SetArea(area);
        mClickCatcher->SetSize(area.GetWidth() * 2.0f, area.GetHeight() * 2.0f);
      }
    }
    EA::UTFWin::IWindowManager* wm = SP::WindowManager();
    if (mInputBlocked && !wasBlocked) {
      wm->SetCapture(0, mClickCatcher);
      wm->SetCapture(1, mClickCatcher);
    } else if (!mInputBlocked) {
      wm->ReleaseCapture(0, mClickCatcher);
      wm->ReleaseCapture(1, mClickCatcher);
    }
  }
}
}  // namespace SP

// @ 0x005dd1d0
namespace SP {
void cSPEditorUI_s005d_cd80::SelectCurrentTypeInGrid()
{
  int type = mApp->mpEditorModel->mSelectedType;
  EA::UTFWinControls::IWinGrid_s005d_cd80::Range range;
  if (mGridTypes->GetCellRange(range)) {
    for (int i = 0; i <= range.bottom; i++) {
      if (type == mGridTypes->GetCellValue(0, i)) {
        mGridTypes->ScrollToCell(0, i);
        mGridTypes->SetSelectedCell(i);
        return;
      }
    }
  }
}
}  // namespace SP

// @ 0x005dd250
namespace SP {
void cSPEditorUI_s005d_cd80::ShowSaveDialog()
{
  cString_s005d_cd80 str;
  mCurrentCommand = 0x10a;
  cEditorHistory* history = gEditorHistory;
  history->SetModelType(mApp->mpEditorModel->GetModelType());
  if (EditorUtils::GetCreatorType(&mApp->mpEditorModel->mKey)) {
    mCurrentDialogID = kDialogSaveA.mID;
    ShowDialog(0, &kDialogSaveA);
    UpdateSaveButtons();
  } else {
    mCurrentDialogID = kDialogSaveB.mID;
    ShowDialog(mDialogResultCallback, &kDialogSaveB);
  }
}
}  // namespace SP

// @ 0x005dd300
namespace SP {
void cSPEditorUI_s005d_cd80::OnSaveRequested()
{
  if (mApp->GetEditorSaveability() == 3) {
    if (OnlineManager()->IsLoggedIn()) {
      IOnlineManager* online = OnlineManager();
      online->SetState(0);
      online->Update();
      mCurrentCommand = 0x10a;
    } else {
      ShowSaveDialog();
    }
  }
}
}  // namespace SP

// @ 0x005dd360
namespace SP {
void cSPEditorUI_s005d_cd80::OnLoginResult(bool success)
{
  if (mCurrentCommand == 0x10a) {
    if (success)
      ShowSaveDialog();
    else
      mCurrentCommand = 0;
  }
}
}  // namespace SP

// @ 0x005dd390
namespace SP {
void cSPEditorUI_s005d_cd80::CloseModalLayout()
{
  if (mpModalLayout) {
    if (mpModalLayout->FindWindowByID(0x864a77d, true))
      mpModalLayout->FindWindowByID(0x864a77d, true)->RemoveWinProc(this);
    if (mpModalLayout->FindWindowByID(0x864a768, true))
      mpModalLayout->FindWindowByID(0x864a768, true)->RemoveWinProc(this);
    if (mpModalLayout->FindWindowByID(0x864a771, true))
      mpModalLayout->FindWindowByID(0x864a771, true)->RemoveWinProc(this);
    IWindow_s005d_cd80* blocker = mpModalLayout->FindWindowByID(0x864a5fa, true);
    if (blocker)
      SP::WindowManager()->SetCapture(0, blocker);
    mpModalLayout->Shutdown(true);
    mpModalLayout = 0;
  }
}
}  // namespace SP

// @ 0x005dd4a0
namespace SP {
void cSPEditorUI_s005d_cd80::OpenModalLayout()
{
  CloseModalLayout();
  mpModalLayout = new (kLayoutAllocName, 0, 0, 0, 0) cSPUILayout_s005d_cd80();
  mpModalLayout->Init(kModalLayoutKey, true, 0x5b598fa);
  mpModalLayout->SetVisibility(true);
  IWindow_s005d_cd80* dialog = mpModalLayout->FindWindowByID(0x864a5d3, true);
  if (dialog) {
    IWindow_s005d_cd80* blocker = mpModalLayout->FindWindowByID(0x864a5fa, true);
    if (blocker) {
      blocker->SetLayoutArea(SP::WindowManager()->GetMainWindow()->GetArea());
      SP::WindowManager()->SetCapture(0, blocker);
    }
    if (dialog->GetParent()) {
      SPUIHelpers::CenterWindowInRect(dialog, SP::WindowManager()->GetMainWindow()->GetArea());
      dialog->GetParent()->BringToFront(dialog);
    }
    mpModalLayout->FindWindowByID(0x864a77d, true);
    mpModalLayout->FindWindowByID(0x864a768, true);
    mpModalLayout->FindWindowByID(0x864a771, true);
  }
}
}  // namespace SP

// @ 0x005dd610
namespace SP {
void cSPEditorUI_s005d_cd80::SetPaintMode(bool paint)
{
  IWindow_s005d_cd80* w = FindWindowByID(0x47bc920);
  if (w && (bool)(w->GetFlags() & 1) != paint) {
    Renderer()->SetPaused(!paint, true);
    SPUIHelpers::GetLayoutManager();
    if (paint) {
      CameraManager()->PushInputMode(0x16, 2);
      AudioState(0x4c4ba0a9)->Push(1, 0, 0x4c4ba0a9);
      SetWindowVisibility(0x47bc920, true);
      SetWindowVisibility(0x65e561d, true);
      SetWindowVisibility(0x65e4ef4, false);
      SetSelected(0x47bc8d8, true, false);
    } else {
      SetSelected(0x47bc8d8, false, false);
      SetWindowVisibility(0x65e4ef4, true);
      SetWindowVisibility(0x47bc920, false);
      SetWindowVisibility(0x65e561d, false);
      AudioState(0x4c4ba0a9)->Pop();
      CameraManager()->PopInputMode(0x16, 2);
    }
  }
}
}  // namespace SP

// @ 0x005dd7a0
namespace SP {
void cSPEditorUI_s005d_cd80::UpdateUIBasedOnModelSaveability()
{
  int saveability = mApp->GetEditorSaveability();
  bool visible = false;
  bool enabled = false;
  if (mShowSaveButton) {
    switch (saveability) {
      case 3:
      case 4:
        enabled = false;
        visible = true;
        break;
      case 0:
      case 1:
      case 2:
        enabled = true;
        visible = true;
        break;
    }
  }
  if (!mSaveEnabled)
    enabled = false;
  IWindow_s005d_cd80* w = FindWindowByID(0x5b6e484);
  if (w) {
    w->SetFlag(1, visible);
    w->SetFlag(2, enabled);
  }
  UpdateSaveButtons();
}
}  // namespace SP

// @ 0x005dd860
namespace SP {
uint32_t cSPEditorUI_s005d_cd80::GetWarning(bitset128 flags)
{
  bitset128 maskedA = gFlagsA & ~gMask;
  bitset128 maskedB = gFlagsB & ~gMask;
  bool noA = !BitsetContains(flags, maskedA);
  bool noB = !BitsetContains(flags, maskedB);
  uint32_t id;
  if (noB)
    id = noA ? 0xf207647f : 0x7b355311;
  else
    id = noA ? 0xb129f37e : 0xa1520d7f;
  if (CheckWarnings(flags, mApp->GetPartFlags(), EA::ResourceMan::Key_s005d_cd80(id, 0xb1b104, 0x490f6945)))
    return id;
  return 0;
}
}  // namespace SP

// @ 0x005dda30
namespace SP {
void cSPEditorUI_s005d_cd80::SetMode(int mode)
{
  if (mode == 2 && !mApp->CanEnterMode(0))
    return;
  if (mUIEditorMode == mode)
    return;
  if (!mApp->SetMode(mode, false))
    return;
  PlayUISound(0x8c35f293);
  SetPaintMode(false);
  switch (mUIEditorMode) {
    case 0:
      if (mWinPartPaletteRoot)
        mWinPartPaletteRoot->SetFlag(1, false);
      if (mWin80)
        mWin80->SetFlag(1, false);
      if (mWin84)
        mWin84->SetFlag(1, false);
      break;
    case 1:
      if (mWinPaintPaletteRoot)
        mWinPaintPaletteRoot->SetFlag(1, false);
      break;
    case 2: {
      if (mWinLeftPanelFrame)
        mWinLeftPanelFrame->SetFlag(1, true);
      if (IWindow_s005d_cd80* w = FindWindowByID(0x578ec50))
        w->SetFlag(1, true);
      if (IWindow_s005d_cd80* w = FindWindowByID(0xf006efa5))
        w->SetFlag(1, true);
      if (IWindow_s005d_cd80* w = FindWindowByID(0xb006ef6e))
        w->SetFlag(1, true);
      if (IWindow_s005d_cd80* w = FindWindowByID(0x1140129d))
        w->SetFlag(1, mApp->IsPaintModeAvailable());
      break;
    }
  }
  IWindow_s005d_cd80* parent = 0;
  switch (mode) {
    case 0:
      if (mWinPartPaletteRoot)
        mWinPartPaletteRoot->SetFlag(1, true);
      if (IWindow_s005d_cd80* w = FindWindowByID(0x578ec50))
        w->SetFlag(1, true);
      if (IWindow_s005d_cd80* w = FindWindowByID(0xf006efa5))
        w->SetFlag(1, true);
      if (IWindow_s005d_cd80* w = FindWindowByID(0xb006ef6e))
        w->SetFlag(1, true);
      if (mWin80)
        mWin80->SetFlag(1, true);
      if (mWin84)
        mWin84->SetFlag(1, true);
      parent = mLayout.FindWindowByID(0x4fcc580, true);
      SetSelected(0xf019c2e7, true, true);
      break;
    case 1:
      if (mWinPaintPaletteRoot)
        mWinPaintPaletteRoot->SetFlag(1, true);
      parent = mLayout.FindWindowByID(0x4fcc581, true);
      break;
    case 2:
      if (mWinLeftPanelFrame)
        mWinLeftPanelFrame->SetFlag(1, false);
      if (IWindow_s005d_cd80* w = FindWindowByID(0x578ec50))
        w->SetFlag(1, false);
      if (IWindow_s005d_cd80* w = FindWindowByID(0xf006efa5))
        w->SetFlag(1, false);
      if (IWindow_s005d_cd80* w = FindWindowByID(0xb006ef6e))
        w->SetFlag(1, false);
      if (IWindow_s005d_cd80* w = FindWindowByID(0x1140129d))
        w->SetFlag(1, false);
      break;
  }
  if (parent) {
    mCameraControlsLayout.SetParentWin(parent, true, 0x5b598fa);
    mCameraControlsLayout.SetVisibility(true);
  } else {
    mCameraControlsLayout.SetVisibility(false);
  }
  mUIEditorMode = mode;
}
}  // namespace SP

// @ 0x005ddd60
bool EditorUI::Init(AppMode* app, int a2, unsigned a3, int a4)
{
    mApp = app;
    if (!app)
        return false;
    fa0 = (char)a4;
    if (a2) {
        Key key; key.inst = a2; key.type = 0x510a95b; key.group = a3;
        if (!mLayout.Init(&key, 1, 0x5b598fa))
            return false;
    }
    if (!mCamera.Init(L"EditorSharedUI", a3, 1, 0x5b598fa))
        return false;
    mPalette.Init(L"CameraControls", a3, 1, 0x5b598fa);

    Widget* a = mLayout.FindWindowByID(-1, 1);
    Widget* b = mCamera.FindWindowByID(-1, 1);
    if (a) {
        a->AddWinProc((char*)this + 4);
        a->SetFlag(1, 0);
        if (mHighlight)
            mHighlight->SetFlag(1, 0);
        mBudget = FindWindow(this, 0x5100b176);
        mComplexity = FindWindow(this, 0xf006f308);
        mHighlight = FindWindow(this, 0xf006f309);
        if (mHighlight)
            mHighlight->SetFlag(1, 0);
        if (mComplexity)
            mComplexity->SetFlag(1, 1);
        f80 = FindWindow(this, 0x908891a7);
        f84 = FindWindow(this, 0xf383c97d);

        WindowManager_s005d_dd60();
        Widget* world = GetLayoutManager(0x5b598fa)->GetWorldMainWindow();
        mClick.Set(CreateWindowFor(world));
        mClick.p->SetFlag(0x40, 1);
        mClick.p->SetFlag(2, 1);
        SetWindowAlpha(mClick.p, 0.0f);
        mClick.p->SetFlag(1, 0);
        mClick.p->SetFlag(0x10, 0);
        float* area = a->GetArea();
        float r[4];
        r[0] = area[0]; r[1] = area[1]; r[2] = area[2]; r[3] = area[3];
        mClick.p->SetArea(r);
        mClick.p->SetSize((r[2] - r[0]) * 0.5f, (r[3] - r[1]) * 0.5f);
        mClick.p->SetLayoutId(0x52dac0d);
        mClick.p->GetParent()->AddChild(mClick.p);

        mClickProc.Set(new ("Editor", 0, 0, 0, 0) BlockerA);
        mClickProc.p->app = (Widget*)mApp;
        mClick.p->AddWinProc(mClickProc.p);

        ReleaseRef((Widget**)&mBlock);
        ReleaseRef((Widget**)&mBlockProc);
        mBlock.Set(CreateWindowFor(world));
        mBlock.p->SetFlag(2, 1);
        mBlock.p->SetFlag(1, 0);
        mBlockProc.Set(new ("Editor", 0, 0, 0, 0) BlockerB);
        mBlockProc.p->app = (Widget*)mApp;
        mBlock.p->AddWinProc(mBlockProc.p);

        FUN_005dc5a0(0x58a3350);
        Widget* tip = FindWindow(this, 0x612efea);
        if (tip) {
            void* mem = AllocTooltip(0x68, "UI/Tooltip", 4, GetTooltipPool());
            TooltipProc* tp = 0;
            if (mem) {
                tp = (TooltipProc*)mem;
                tp->Ctor();
            }
            mTooltip.Set(tp);
            tip->AddWinProc(mTooltip.p);
        }
    }
    if (b) {
        b->AddWinProc((char*)this + 4);
        b->SetFlag(1, 1);
        mCapture = FindWindow(this, 0xd0353720);
        if (mCapture) {
            Widget* g = FUN_005dc310(0x503517b0);
            if (g)
                mGrid = InterfaceCast(g);
            int n = (int)(mApp->mItemsEnd - mApp->mItemsBegin);
            if (n == 1) {
                mCapture->SetFlag(n, 0);
            } else {
                mCapture->SetFlag(1, 1);
                for (int i = 0; i < n; ++i) {
                    void* item = mApp->mItemsBegin[i];
                    mGrid->GridSetItem(0, i, MakeGridCell(item, 0, 1, 0));
                    mGrid->GridSetData(0, i, mApp->mItemsBegin[i]);
                }
                mGrid->Slot42(0, 0);
            }
        }
    }
    Widget* bw = FindWindow(this, 0x1140129d);
    if (bw)
        bw->SetFlag(1, mApp->IsAvailable());
    GetCursorManager(0x1002)->SetLocalCursor();
    if (*(int*)(*(char**)(g_ptr15fd918 + 0x3c) + 0x118) != 0) {
        Widget* w1 = FindWindow(this, 0x4766ff0);
        w1->SetFlag(1, 1);
        Widget* w2 = FindWindow(this, 0x47bc9d0);
        w2->SetFlag(1, 1);
    }
    Widget* pp = mLayout.FindWindowByID(0x4fcc580, 1);
    if (pp) {
        mPalette.SetParentWin(pp, 1, 0x5b598fa);
        mPalette.SetVisibility(1);
    } else {
        mPalette.SetVisibility(0);
    }
    SetSelected(0xf019c2e7, 1, 1);
    WindowManager_s005d_dd60()->GetRoot()->AddWinProc((char*)this + 4);
    FUN_005dd090(1);
    StartListeningToMessages();
    return a4 != 0;
}

// @ 0x005de450
void EditorUI::Update(int dt)
{
    int t = mFade - dt;
    int zero = 0;
    const int* pick = &t;
    if (t <= 0)
        pick = &zero;
    mFade = *pick;
    Widget* w = FindWindow(this, 0x3088953b);
    if (w) {
        unsigned c = w->GetColor();
        float f[4];
        f[3] = (float)mFade * 0.00014285714f;
        f[0] = (float)((c >> 16) & 0xff) * 0.003921569f;
        f[1] = (float)((c >> 8) & 0xff) * 0.003921569f;
        f[2] = (float)(c & 0xff) * 0.003921569f;
        w->SetColor(ColorRGBAToU32(f));
        w->Refresh();
    }
    Widget* p;
    p = mPalette.FindWindowByID(0x4cab570, 1);
    if (p && (p->GetChild(0x8ed27e7a)->GetFlags() & 2)) {
        TerrainTool* tt = mApp->FUN_00574590();
        if (tt) tt->Brush5a2200(-0.015f);
    }
    p = mPalette.FindWindowByID(0x4cab571, 1);
    if (p && (p->GetChild(0x8ed27e7a)->GetFlags() & 2)) {
        TerrainTool* tt = mApp->FUN_00574590();
        if (tt) tt->Brush5a2200(0.015f);
    }
    p = mPalette.FindWindowByID(0x4cab56f, 1);
    if (p && (p->GetChild(0x8ed27e7a)->GetFlags() & 2)) {
        TerrainTool* tt = mApp->FUN_00574590();
        if (tt) tt->Brush5a2240(-0.02f);
    }
    p = mPalette.FindWindowByID(0x4cab56e, 1);
    if (p && (p->GetChild(0x8ed27e7a)->GetFlags() & 2)) {
        TerrainTool* tt = mApp->FUN_00574590();
        if (tt) tt->Brush5a2240(0.02f);
    }
    if (f10c) {
        FUN_005dd390();
        f10c = 0;
    }
}

// @ 0x005de690
void EditorUI::EnableBasicEditorButtons(int a, char b)
{
    char c = (char)a;
    fd1 = c;
    const unsigned* ids = g_basicButtonIds;
    do {
        Widget* w = FindWindow(this, *ids);
        if (w)
            SetButton(w, a, c);
        ++ids;
    } while ((int)ids < (int)(g_basicButtonIds + 18));
    if (b) {
        Widget* w = FindWindow(this, 0x70218642);
        if (w && mApp->mMode != 2)
            SetButton(w, a, c);
        w = FindWindow(this, 0xf019c2f3);
        if (w && mApp->mMode != 1)
            SetButton(w, a, c);
        w = FindWindow(this, 0xf019c2e7);
        if (w && mApp->mMode != 0)
            SetButton(w, a, c);
    }
    UpdateUIBasedOnModelSaveability();
    UpdateSaveButtons();
    FUN_005dc970(a);
}

// @ 0x005de870
bool EditorUI::Shutdown()
{
    if (mfe8) {
        mfe8->FUN_005fe650();
        if (mfe8) {
            WinCtl* o = mfe8;
            mfe8 = 0;
            o->Release();
        }
    }
    WindowManager_s005d_dd60();
    Widget* world = GetLayoutManager(0x5b598fa)->GetWorldMainWindow();
    FUN_005dd090(1);
    world->RemoveWinProc((char*)this + 4);
    StopListeningToMessages();
    mLayout.Shutdown(1);
    mCamera.Shutdown(1);
    mPalette.Shutdown(1);
    DetachPair((Widget**)&mBlock, (Widget**)&mBlockProc);
    DetachPair((Widget**)&mClick, (Widget**)&mClickProc);
    return true;
}

// @ 0x005de9e0
void EditorUI::FUN_005de9e0()
{
    SetMode(0);
    mApp->NewModel(0);
    Widget* w = FindWindow(this, 0xf019c2e7);
    if (w) {
        Widget* p = w->GetChild(0x8ed27e7a);
        p->SetState(4, 1);
        p->SetState(0x20, 1);
        w->Notify();
    }
}

// @ 0x005dea60
EditorUI* EditorUI::Construct()
{
    vt4 = vtblB_14426a0;
    vt8 = vtblB_13eb384;
    vtc = vtblB_13ec458;
    f10 = 0;
    vt0 = vtblA_13f92dc;
    vt4 = vtblA_13f92c0;
    vt8 = vtblA_13f92b0;
    vtc = vtblA_13f92a0;
    mLayout.Ctor();
    mCamera.Ctor();
    mPalette.Ctor();
    mApp = 0; f60 = 0; mBudget = 0; mComplexity = 0; mHighlight = 0; mCapture = 0; mGrid = 0;
    mClick.p = 0; mClickProc.p = 0; f80 = 0; f84 = 0; mTooltip.p = 0; mBlock.p = 0; mBlockProc.p = 0;
    mFade = 0; f9c = 0;
    fa0 = 0; fa2 = 0; fa3 = (char)0xff; fa1 = 1;
    fa8 = 0; fac = 0; fb0 = 0;
    fb4 = vtblC_13f925c;
    fbc = 0; fc0 = 0; fc4 = 0; fcc = 0;
    fd0 = 1; fd1 = 1;
    fd8 = 0; fdc = 0; fe0 = 0; fd4 = 0;
    fe4 = 0; fe5 = 0; mfe8 = 0; fec = 0; ff0 = 0; ff4 = 0; ff8 = 0; ffc = 0;
    f100 = 0; f101 = 0; f102 = 0; f103 = 1; f104 = 0; f105 = 0; f106 = 1;
    f108 = 0; f10c = 0; f110 = 0; f114 = 0; f118 = 0; f11c = 0; f120 = 0; f124 = 0; f128 = 0;
    fb8 = this;
    return this;
}

// @ 0x005dec10
void EUI::FUN_005dec10(uint32_t a)
{
    switch (a) {
    case 0x100: {
        ResMgr* mgr = GetManager();
        Res* res = 0;
        if (mgr && mgr->GetResource(&mkey, &res, 0, 0, 0, 0)) {
            EditorRes* er = interface_cast_EditorRes(&res);
            if (er) {
                uint32_t cfg = RemapTypeId(er->mType);
                if (md0 && app->FUN_00573070(er)) {
                    if (app->FUN_00573050()) {
                        app->SetCurrentConfig(cfg, mkey);
                    } else {
                        FUN_0067cac0(0xffc453c6)->FUN_0067c830();
                    }
                    if (res) res->Release();
                    return;
                }
            }
        }
        FUN_005dda30(0);
        Key16 tmp;
        Key16* k = app->FUN_00572160(&tmp);
        app->LoadModelKey(&mkey, *k, 1);
        FUN_00401050(0x3f1bf54, 0)->FUN_0045ae10();
        if (res) res->Release();
        return;
    }
    case 0x102:
        if (mec) {
            mc8 = 0x61c7098;
            WinObj* o = new ("Editor", 0, 0, 0, 0) WinObj(mb4);
            me8.assign(o);
            me8.p->FUN_005fea60(mf0, mf4);
            me8.p->FUN_005fe6c0();
        } else {
            app->LoadModel(1, 2, 1);
        }
        return;
    case 0x103:
        app->LoadModel(2, 2, 1);
        return;
    case 0x104:
        FUN_005de9e0();
        return;
    case 0x107:
        GetMessageServer()->Post(0x153c326, 0, 0, 0);
        return;
    }
}

// @ 0x005dee70
bool HandlerSub::HandleMessage(uint32_t msg, int data)
{
#define ui ((EUI*)((char*)this - 8))
    switch (msg) {
    case 0x44db12e:
        ui->FUN_005dd360(data != 0);
        return false;
    case 0x165e841:
        if (mc4) {
            if (!ui->FUN_005dc250(mc4)) {
                mc0 = g1519958.a;
                CalloutMessageBox(mac, &g1519958);
                return false;
            }
            ui->FUN_005dec10(mc4);
            return false;
        }
        return false;
    case 0x5b98f52:
    case 0x5b96086:
    case 0x5bd6378:
    case 0x5c5594a:
    case 0x5dd52c7:
        if (mc4 == 0x10a)
            mc4 = 0;
        return false;
    }
    return false;
}

// @ 0x005def30
void EUI::FUN_005def30(uint32_t param)
{
    void* volatile self = this;
    (void)self;
    AudioSys* au = GetSystemAT();
    uint32_t v = au ? au->GetValue() : 0;
    au = GetSystemAT();
    if (au) {
        au->Begin(0x3475365);
        au->SetParam(0x3475381, 0xa03e74b2);
        au->SetParam(0x3475385, v);
        au->End();
    }
    switch (mc8) {
    case 0x61c7098:
        if (!me8.p)
            return;
        if (me8.p->FUN_005fe5f0()) {
            mcc = 0;
        } else {
            mf8 = me8.p->GetAccessFlags();
            mfc = me8.p->FUN_006c0200();
            app->LoadModel(0, 2, me5);
        }
        if (me8.p) {
            WinObj* o = me8.p;
            me8.p = 0;
            o->Release();
        }
        return;
    case 0x604fa6b:
    case 0x604fab1:
        if (param == 0x5107b17) {
            GetConfigManager()->SetValue(0x604a51a, 0);
            GetConfigManager()->Commit();
        }
        if (mc8 == 0x604fa6b) {
            mcc = 0x100;
            FUN_004a88d0_(0xa03e74b2);
            FUN_005dc4d0(0);
            return;
        }
        if (mc8 == 0x604fab1) {
            mcc = 0x105;
            FUN_004a88d0_(0xa03e74b2);
            AssetBrowserLaunch(0xdb184acb, this, 0x54acb9f1);
        }
        return;
    case 0x3b182dc3:
    case 0x9a24fbe5:
        mcc = 0;
        return;
    case 0x7b355311:
    case 0xa1520d7f:
    case 0xb129f37e:
    case 0xf207647f:
        if (param == 0x5107b1a)
            FUN_005dcaa0(mcc, me5);
        return;
    case 0x3a5ea067:
    case 0x5cd172a9:
    case 0xc6bdfccc:
    case 0xe6c74f99:
    case 0xf46fbea9:
        if (param == 0x5107b1a)
            FUN_005dec10(mcc);
        return;
    case 0x3cc9f2f3:
        FUN_005dec10(mcc);
        return;
    case 0xa2509b6a:
        if (param == 0x5107b19) {
            mcc = 0;
        } else if (param == 0x5107b1a) {
            app->FUN_00573fb0();
        }
        return;
    case 0x811778da:
        if (param == 0x5107b19) {
            if (me4) {
                mc8 = FUN_005dd860(msaved);
                me5 = 1;
            } else {
                FUN_005dcaa0(mcc, 1);
            }
        } else if (param == 0x5107b1a) {
            if (me4) {
                mc8 = FUN_005dd860(msaved);
                me5 = 0;
            } else {
                FUN_005dcaa0(mcc, 0);
            }
        }
        return;
    case 0x12b8ba66:
    case 0x8bf4d3f2:
    case 0x9d533cda:
    case 0xbe186a9a:
        if (param == 0x5107b17) {
            FUN_005dec10(mcc);
        } else if (param == 0x5107b19) {
            if (me4) {
                mc8 = FUN_005dd860(msaved);
                me5 = 1;
            } else {
                FUN_005dcaa0(mcc, 1);
            }
        } else if (param == 0x5107b1a) {
            if (me4) {
                mc8 = FUN_005dd860(msaved);
                me5 = 0;
            } else {
                FUN_005dcaa0(mcc, 0);
            }
        }
        return;
    case 0x48ee60f0:
    case 0x53830374:
    case 0x7c1ea6a4:
    case 0xb016b570:
    case 0xc2b30789:
    case 0xcf4c3d25:
    case 0xeb3bc709:
    case 0xebdc80d5: {
        uint8_t flag = 0;
        if (mc8 == 0xebdc80d5 || mc8 == 0xc2b30789 || mc8 == 0xcf4c3d25 || mc8 == 0xeb3bc709)
            flag = 1;
        if (param == 0x5107b17) {
            FUN_005dec10(mcc);
        } else if (param == 0x5107b1a) {
            if (me4) {
                mc8 = FUN_005dd860(msaved);
                me5 = flag;
            } else {
                FUN_005dcaa0(mcc, flag);
            }
        }
        return;
    }
    }
}

// @ 0x005df470
void EUI::FUN_005df470(uint32_t cmd, int b)
{
    int sv = app->GetEditorSaveability();
    Key16 saved;
    app->FUN_00572190(&saved);
    mcc = cmd;
    me4 = 0;
    app->FUN_005724a0();
    Key12 loc;
    if (cmd != 0x103 && cmd != 0x107) {
        switch (sv) {
        case 1:
            msaved = saved;
            me4 = 1;
            // fall through
        case 0: {
            bool ok = app->FUN_00574d60();
            if (cmd == 0x101) {
                if (app->m4b1 != 0 || !ok) {
                    if (!me4) {
                        FUN_005dcaa0(0x101, 0);
                        return;
                    }
                    mc8 = FUN_005dd860(msaved);
                    me5 = 0;
                    return;
                }
                mc8 = g1519964.a;
                CalloutMessageBox(mb4, &g1519964);
                return;
            }
            if (ma0 == 0 && app->m4b1 == 0 && ok) {
                bool c = FUN_005dc250(cmd);
                loc = g1519a3c;
                if (!c) {
                    loc = g15199dc;
                    if (cmd != 0x100) {
                        loc = g1519a0c;
                        if (cmd != 0x104)
                            loc = g15199a0;
                    }
                }
            } else {
                if (FUN_005dc250(cmd)) {
                    if (!me4) {
                        FUN_005dcaa0(cmd, ok);
                        return;
                    }
                    mc8 = FUN_005dd860(msaved);
                    me5 = ok;
                    return;
                }
                if (!ok) {
                    loc = g15199c4;
                    if (cmd != 0x100) {
                        loc = g15199f4;
                        if (cmd != 0x104)
                            loc = g1519988;
                    }
                } else {
                    loc = g15199b8;
                    if (cmd != 0x100) {
                        loc = g15199e8;
                        if (cmd != 0x104)
                            loc = g151997c;
                    }
                }
            }
            mc8 = loc.a;
            CalloutMessageBox(mb4, &loc);
            return;
        }
        case 2:
            if (cmd != 0x101 && !FUN_005dc250(cmd)) {
                Key12 k;
                k = g1519994;
                if (cmd == 0x100) k = g15199d0;
                else if (cmd == 0x104) k = g1519a00;
                mc8 = k.a;
                Key16 tmp;
                Key16* m = app->GetMask(&tmp);
                FUN_005dc190(saved, *m, k);
                return;
            }
            FUN_005dca00(saved);
            mcc = 0;
            return;
        case 3:
            FUN_005dec10(cmd);
            return;
        case 4:
            if (cmd != 0x101 && !FUN_005dc250(cmd)) {
                FUN_005dec10(cmd);
                return;
            }
            FUN_005dca00(saved);
            mcc = 0;
            return;
        }
        return;
    }
    if (sv == 3 || sv == 4) {
        FUN_005dec10(cmd);
        return;
    }
    mc8 = g1519970.a;
    CalloutMessageBox(mb4, &g1519970);
}

// @ 0x005df8d0
void EditorFrame::FUN_005df8d0()
{
    mcc = 0x103;
    FUN_005df470(0x103, 1);
}

// @ 0x005df8f0
bool EUI::FUN_005df8f0(Key12 key)
{
    ResMgr* mgr = GetManager();
    Res* res = 0;
    md0 = 1;
    if (mgr && mgr->GetResource(&key, &res, 0, 0, 0, 0) && res) {
        EditorRes* er = (EditorRes*)res->QueryInterface(0x3c609f8);
        if (er) {
            Key16 tmp;
            Key16 out;
            Key16* k = app->FUN_00572160(&tmp);
            // FUN_004bac30(ecx=er, &out, *k, 1)
            ((EditorResOps*)er)->FUN_004bac30(&out, *k, 1);
            k = app->FUN_00572160(&tmp);
            if (!FUN_004f3d60(out, *k)) {
                Key16 z = { 0x4000000, 0, 0, 0 };
                app->FUN_005721b0(z, z);
                if (res) { res->Release(); }
                return false;
            }
            RemapTypeId(er->mType); // 0x00432f10
            if (!app->FUN_00573070(er)) {
                md0 = 0;
            } else if (!app->FUN_00573050()) {
                FUN_0067cac0(0xffc453c6)->FUN_0067c830();
                if (res) res->Release();
                return false;
            }
            mkey = key;
            mcc = 0x100;
            FUN_005df470(0x100, 1);
            if (res) res->Release();
            return true;
        }
    }
    Key16 z = { 0x4000000, 0, 0, 0 };
    app->FUN_005721b0(z, z);
    if (res) res->Release();
    return false;
}

// @ 0x005dfb30
void EditorFrame2::FUN_005dfb30(int a, int b)
{
    mpTarget->DoDialogEnd(b);
}

// @ 0x005dfb40
void EditorUI2::DoSaveAndExit()
{
    void* a = m5c;
    char* b = *(char**)((char*)a + 0x7c);
    char* c = *(char**)(b + 0xc);
    if (c[0x44]) {
        void* base = *(void**)((char*)a + 0x78);
        Widget_s005d_ec10* w = FindWindowRaw(base, 0x3f67620);
        if ((w->Slot10() & 1) != 0)
            return;
    }
    FUN_004a88d0(0xf515d2c3);
    mcc = 0x102;
    FUN_005df470(0x102, 1);
}

// @ 0x005dfbb0
void FUN_005dfbb0(void* self)
{ (void)self; }

// @ 0x005dfd00
void FUN_005dfd00(void* self, int cmd)
{ (void)self; (void)cmd; }

// @ 0x005e0000
void FUN_005e0000(void* self)
{ (void)self; }

// @ 0x00de8ad0
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
