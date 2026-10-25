// Slice s00600260 - cOnlineTab / cGraphicsTab ctor+dtor / cSPUISettings helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE
#include "../s005fa8d0/s005fa8d0.h"

struct ConfigManagerStub {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual void vt2c(uint32_t id, uint8_t v);       // +0x2c
  virtual uint8_t vt30(uint32_t id);               // +0x30
};
ConfigManagerStub* ConfigManager();   // 0x0067dd30

struct LayoutStub {
  char pad[0x41];
  void* FindWindowByID(uint32_t id, int recurse);  // 0x008105b0
};

struct WinWithIDStub {
  PV(0) PV(1) PV(2)
  virtual void* vt0c(uint32_t id);                 // +0x0c
  PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual void vt28(int a, bool b);                // +0x28
};

struct OnlineTabStub {
  char pad0[8];
  LayoutStub mLayout;       // +0x8 (0x41 bytes)
  uint8_t mbFlag;           // +0x49
  void DoMessageTab();      // 0x00600260
};

// @ 0x00600260
void OnlineTabStub::DoMessageTab()
{
  ConfigManager()->vt2c(0x5de7b4a, mbFlag);
  mbFlag = ConfigManager()->vt30(0x5de7b4a);
  WinWithIDStub* w = (WinWithIDStub*)mLayout.FindWindowByID(0x5b1cc48, 1);
  if (w) {
    WinWithIDStub* p = (WinWithIDStub*)w->vt0c(0x8ed27e7a);
    if (p) p->vt28(4, mbFlag == 1);
  }
}

// --- shared UI scaffolding for this slice ---------------------------------------------
namespace EA {
// Stopwatch (0x20 bytes); the (timer id, auto-start) ctor is 0x0093a560.
class Stopwatch {
 public:
  // The EA::Stopwatch constructor, called out of line on an existing member.
  void Init(int type, bool start);   // 0x0093a560
  uint32_t mData[8];
};
}  // namespace EA

class IWinText;
struct UIMsg;

// UTFWin window: only the slots this slice touches.
class IWindow {
 public:
  virtual int AddRef();                                       // +0x00
  virtual int Release();                                      // +0x04
  virtual void Activate(bool on);                             // +0x08
  virtual IWindow* FindChild(uint32_t id);                    // +0x0c
  virtual IWindow* GetParent();                               // +0x10
  PV(5) PV(6)
  virtual uint32_t GetID();                                   // +0x1c
  virtual uint32_t GetFlags();                                // +0x20
  PV(9)
  virtual void SetFlag(int flag, bool on);                    // +0x28
  PV(11) PV(12) PV(13)
  virtual const void* GetArea();                              // +0x38
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24)
  virtual void SetOffset(float x, float y);                   // +0x64
  PV(26)
  virtual void SetRect(const void* area);                     // +0x6c
  PV(28) PV(29) PV(30)
  virtual void SetVisible(int part, bool on);                 // +0x7c
  virtual void SetText(const wchar_t* text);                  // +0x80
  PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43)
  PV(44) PV(45) PV(46) PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53)
  virtual void SetScrollWindow(IWindow* p);                   // +0xd8
  virtual void ClearScrollWindow(IWindow* p);                 // +0xdc
  PV(56) PV(57)
  virtual void SetScrollTarget(IWindow* p);                   // +0xe8
  PV(59)
  virtual IWindow* FindWindowByID(uint32_t id, int recurse);  // +0xf0
  PV(61) PV(62) PV(63) PV(64)
  virtual void HandleMessage(IWindow* p);                     // +0x104
};

class IWinText : public IWindow {};

// Ref-counted pointer: assigning releases the previous object (the new one is AddRef'd first).
template <typename T>
class AutoRefCount {
 public:
  T* mpObject;
  AutoRefCount& operator=(T* p) {
    if (p != mpObject) {
      if (p) p->AddRef();
      T* old = mpObject;
      mpObject = p;
      if (old) old->Release();
    }
    return *this;
  }
  // Drops the reference without clearing the slot (used by the owning dtor).
  void ReleaseObject() {
    if (mpObject) mpObject->Release();
  }
};

// Entry of the graphics tab's option list (0x58 bytes, dtor 0x005fe4b0).
class GraphicsTabEntry {
 public:
  ~GraphicsTabEntry();   // 0x005fe4b0
  uint32_t mData[0x16];
};

// Allocation header word stored just before free-block payloads.
struct AllocHeader {
  uint32_t mAllocSize;
};

// begin/end/capacity triple of the option list plus its manual teardown.
class GraphicsTabEntries {
 public:
  GraphicsTabEntry* mpBegin;     // +0x00
  GraphicsTabEntry* mpEnd;       // +0x04
  GraphicsTabEntry* mpCapacity;  // +0x08
  void Destroy();
};

// cSPUILayout: the window-tree owner embedded in each settings tab (+0x08).
class cSPUILayout {
 public:
  cSPUILayout();                                      // 0x00810000
  ~cSPUILayout();                                     // 0x00811fe0
  IWindow* FindWindowByID(uint32_t id, int recurse);  // 0x008105b0
  uint32_t mData[7];
};

// Leading view of the embedded cSPUILayout in the settings page (+0x08..+0x13).
class cSPUILayoutHead {
 public:
  IWindow* FindWindowByID(uint32_t id, int recurse);  // 0x008105b0
  uint32_t mData[3];
};

// Base of every settings tab: vptr + the owner window.
class cSettingsTab {
 public:
  virtual ~cSettingsTab() {}
  IWindow* mpWindow;    // +0x04
};

// cGraphicsTab: display-option tab of the settings screen.
class cGraphicsTab : public cSettingsTab {
 public:
  virtual ~cGraphicsTab();                    // 0x00600df0
  cGraphicsTab();                             // 0x00600da0
  void ReloadOptions();                       // 0x00600c00
  cSPUILayout mLayout;                        // +0x08
  GraphicsTabEntries mEntries;                // +0x24
  uint32_t mPad30[5];                         // +0x30..0x43
  AutoRefCount<IWindow> mWinScroll;           // +0x44
  AutoRefCount<IWindow> mWinList;             // +0x48
  AutoRefCount<IWindow> mWinSlider;           // +0x4c
  AutoRefCount<IWinText> mTextQuality;        // +0x50
  uint32_t mPad54[3];                         // +0x54..0x5f
  EA::Stopwatch mWatchA;                      // +0x60
  EA::Stopwatch mWatchB;                      // +0x80
};

// cSPUISettings: the audio/video settings page.
class cSPUISettings : public cSettingsTab {
 public:
  virtual bool DoMessage(uint32_t message, UIMsg* pMsg);   // 0x006002d0 (ret 8)
  virtual bool OnModalWindowEnd(uint32_t message);          // 0x006008c0
  void ShowWindow();                                        // 0x00600ab0
  cSPUILayoutHead mLayout;                                  // +0x08
  cSPUILayout* mpSettingsLayout;                            // +0x14
  uint32_t mPad18[3];                                       // +0x18..0x23
  bool mMusicOn;                                            // +0x24
  uint32_t mLevelProp;                                      // +0x28
  uint32_t mViewProp;                                       // +0x2c
  uint32_t mPad30[0x7c];                                    // +0x30..0x21f
  AutoRefCount<IWindow> mEffectWindow;                      // +0x220
};

struct UIMsg {
  IWindow* mpTarget;    // +0x00
  uint32_t mPad04;
  uint32_t id;          // +0x08
  uint32_t sub;         // +0x0c
  uint32_t mPad10;
  uint32_t mPad14;
  IWindow* src;         // +0x18
};

// Message server: +0x14 posts a message.
struct MessageServerStub {
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void Post(uint32_t id, uint32_t a, uint32_t b);   // +0x14
};
MessageServerStub* MessageServer();    // 0x0067dcc0

// Effects manager: +0x2c creates or fetches an effect window.
struct EffectsManagerStub {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual bool AcquireEffect(uint32_t id, int arg, IWindow** out);   // +0x2c
};
EffectsManagerStub* EffectsManager();  // 0x0067ddd0

// Layout-manager singleton, used to hide every world while the modal page is up.
class cSPUILayoutManager {
 public:
  void SetAllWorldsVisibility(bool visible);   // 0x008106a0
  void SetWorldFlag(uint32_t id, bool on);     // 0x00810660
};
cSPUILayoutManager* LayoutManager();   // 0x0080fee0

struct cPropertySubList {
  uint32_t mPad00[0x46];       // +0x00..0x117
  uint32_t mModalActive;       // +0x118
};
struct cDirectPropertyList {
  uint32_t mPad00[0xf];            // +0x00..0x3b
  cPropertySubList* mpModalSub;    // +0x3c
  bool GetDescription(uint32_t id);  // 0x006a25a0
};
extern cDirectPropertyList* sAppProperties;  // 0x015fd918

IWindow* FUN_00807600(const wchar_t* name, IWindow** out, void* unused);  // 0x00807600
IWinText* FUN_005ff680(IWindow* p);                                       // 0x005ff680
void FUN_00809910(IWindow* p);                                            // 0x00809910
void SPUIHelpers_BeginModal(IWindow* p, int a, int b);                    // 0x008099a0

namespace SP {
// Localized-text holder (0x14 bytes).
class cString {
 public:
  cString(uint32_t tableID, uint32_t instanceID, const wchar_t* pDefault);  // 0x006b5770
  ~cString();                                                              // 0x006b5240
  const wchar_t* GetText();                                                // 0x006b55c0
 private:
  uint32_t mField00;
  uint32_t mField04;
  uint32_t mField08;
  uint32_t mField0c;
  uint32_t mField10;
};
}  // namespace SP

// @ 0x00600da0
cGraphicsTab::cGraphicsTab() {
  mEntries.mpBegin = 0;
  mEntries.mpEnd = 0;
  mEntries.mpCapacity = 0;
  mWinScroll.mpObject = 0;
  mWinList.mpObject = 0;
  mWinSlider.mpObject = 0;
  mTextQuality.mpObject = 0;
  mWatchA.Init(4, false);
  mWatchB.Init(5, false);
}

// @ 0x00600df0
cGraphicsTab::~cGraphicsTab() {
  mTextQuality.ReleaseObject();
  mWinSlider.ReleaseObject();
  mWinList.ReleaseObject();
  mWinScroll.ReleaseObject();
  for (GraphicsTabEntry* p = mEntries.mpBegin; p < mEntries.mpEnd; ++p) p->~GraphicsTabEntry();
  if (mEntries.mpBegin && ((AllocHeader*)mEntries.mpBegin)[-1].mAllocSize != 0)
    operator delete(mEntries.mpBegin);
}

// @ 0x00600ab0
void cSPUISettings::ShowWindow() {
  IWindow* pPage = mpSettingsLayout->FindWindowByID(0x43c8b98, 1);
  if (sAppProperties->mpModalSub->mModalActive) FUN_00809910(pPage);
  pPage->HandleMessage((IWindow*)this);
  mpSettingsLayout->FindWindowByID(0xaded51d5, 1)->HandleMessage((IWindow*)this);
  mpSettingsLayout->FindWindowByID(0x8bdd39ec, 1)->HandleMessage((IWindow*)this);
  mpSettingsLayout->FindWindowByID(0x3af239c4, 1)->HandleMessage((IWindow*)this);
  mpSettingsLayout->FindWindowByID(0x9a0474a, 1)->HandleMessage((IWindow*)this);

  EffectsManagerStub* pEffects = EffectsManager();
  if (pEffects) {
    mEffectWindow = (IWindow*)0;
    if (pEffects->AcquireEffect(0x4c4ba0a9, 0, &mEffectWindow.mpObject))
      mEffectWindow.mpObject->Activate(false);
  }

  cSPUILayoutManager* pLayouts = LayoutManager();
  pLayouts->SetAllWorldsVisibility(false);
  pLayouts->SetWorldFlag(0x5b598f7, true);
  pLayouts->SetWorldFlag(0x5b598f6, true);
  MessageServer()->Post(0x6203fdc, 0, 0);
  SPUIHelpers_BeginModal(pPage, 0, 1);
}

// @ 0x00600c00
void cGraphicsTab::ReloadOptions() {
  mWinSlider = (IWindow*)0;
  IWindow* pScrollFrame = FUN_00807600(L"ScrollFrameVerticalGeneric", &mWinSlider.mpObject, 0);
  mWinList = pScrollFrame;
  IWindow* pItemList = mLayout.FindWindowByID(0x6036e80, 1);
  IWindow* pSlider = mLayout.FindWindowByID(0x6036e78, 1);
  mWinScroll = pSlider;
  mWinScroll.mpObject->SetVisible(0x10, true);
  if (mWinList.mpObject && mWinSlider.mpObject && pItemList && mWinScroll.mpObject) {
    pItemList->SetScrollWindow(mWinList.mpObject);
    pItemList->SetScrollTarget(mWinList.mpObject);
    mWinList.mpObject->SetRect(mWinScroll.mpObject->GetArea());
    IWindow* pParent = mWinScroll.mpObject->GetParent();
    pParent->ClearScrollWindow(mWinScroll.mpObject);
    mWinSlider.mpObject->SetScrollWindow(mWinScroll.mpObject);
    mWinScroll.mpObject->SetOffset(0.0f, 0.0f);
    mWinSlider.mpObject->HandleMessage(mpWindow);
    IWinText* pText = FUN_005ff680(mWinList.mpObject->FindWindowByID(0x4ab5e70, 0));
    if (pText) {
      mTextQuality = pText;
      mTextQuality.mpObject->SetVisible(1, true);
    }
  }
}

// @ 0x006008c0
bool cSPUISettings::OnModalWindowEnd(uint32_t message) {
  mLevelProp = 0;
  mViewProp = 0;
  switch (message) {
    case 0x01654c00:
      mLevelProp = 0x679b833;
      mViewProp = 0x679bebd;
      break;
    case 0x01654c01:
      mLevelProp = 0x679b85e;
      mViewProp = 0x679bed6;
      break;
    case 0x01654c02:
      mLevelProp = 0x679b868;
      mViewProp = 0x679bee7;
      break;
    case 0x01654c04:
      mLevelProp = 0x679b873;
      mViewProp = 0x679bef7;
      break;
    case 0x01654c05:
      mLevelProp = 0x679b880;
      mViewProp = 0x679bf0b;
    default:
      if (message != 0x01654c05) return false;
  }
  mMusicOn = ConfigManager()->vt30(mLevelProp) != 0;
  IWindow* pPage = mLayout.FindWindowByID(mViewProp, 1);
  if (pPage) {
    pPage->SetVisible(1, true);
    pPage->SetVisible(2, true);
    pPage->SetVisible(0x10, false);
    for (int i = 0; i < 0xb; ++i) {
      IWindow* pLine = pPage->FindWindowByID(0x67a0a6d + i, 0);
      if (pLine) pLine->HandleMessage(mpWindow);
    }
    IWindow* pDialog = pPage->FindWindowByID(0x679b630, 1);
    if (pDialog) {
      IWindow* pCheck = pDialog->FindChild(0x8ed27e7a);
      if (pCheck) pCheck->SetFlag(4, mMusicOn);
    }
  }
  return true;
}

// @ 0x006002d0
bool cSPUISettings::DoMessage(uint32_t message, UIMsg* pMsg) {
  if (pMsg->id == 0x287259f6) {
    if (pMsg->mpTarget->GetID() != 0x679b630) return false;
    IWindow* pPage = mLayout.FindWindowByID(mViewProp, 1);
    if (!pPage) return false;
    IWindow* pDialog = pPage->FindWindowByID(0x679b630, 1);
    if (!pDialog) return false;
    IWindow* pCheck = pDialog->FindChild(0x8ed27e7a);
    if (!pCheck) return false;
    uint32_t flags = pCheck->GetFlags();
    ConfigManager()->vt2c(mLevelProp, (uint8_t)((flags >> 2) & 1));
    MessageServer()->Post(0x679c40d, 0, 0);
    return true;
  }

  if (pMsg->id != 10) return false;
  if (pMsg->sub != 1) return false;
  if (!pMsg->src) return false;

  mMusicOn = ConfigManager()->vt30(mLevelProp) != 0;

  IWindow* pKind1 = mLayout.FindWindowByID(0x67a0ab3, 1);
  IWindow* pKind2 = mLayout.FindWindowByID(0x67a0ab4, 1);
  IWindow* pKind3 = mLayout.FindWindowByID(0x67a0ab5, 1);
  IWindow* pKind4 = mLayout.FindWindowByID(0x67a0ab6, 1);
  IWindow* pKind5 = mLayout.FindWindowByID(0x67a0ab7, 1);
  IWindow* pKind6 = mLayout.FindWindowByID(0x67a0ab8, 1);
  IWindow* pKind7 = mLayout.FindWindowByID(0x67a0ab9, 1);
  IWindow* pKind8 = mLayout.FindWindowByID(0x67a0aba, 1);
  IWindow* pKind9 = mLayout.FindWindowByID(0x67a0abb, 1);
  IWindow* pKind10 = mLayout.FindWindowByID(0x67a0abc, 1);
  IWindow* pKind11 = mLayout.FindWindowByID(0x67a0abe, 1);
  IWindow* pDesc = mLayout.FindWindowByID(0x67a0abd, 1);

  pKind1->SetVisible(1, false);
  pKind2->SetVisible(1, false);
  pKind3->SetVisible(1, false);
  pKind4->SetVisible(1, false);
  pKind5->SetVisible(1, false);
  pKind6->SetVisible(1, false);
  pKind8->SetVisible(1, false);
  pKind9->SetVisible(1, false);
  pKind7->SetVisible(1, false);
  pKind10->SetVisible(1, false);
  pKind11->SetVisible(1, false);
  pDesc->SetVisible(1, false);

  uint32_t textId;
  switch (pMsg->src->GetID()) {
    case 0x67a0a6d:
      pKind2->SetVisible(1, true);
      pKind11->SetVisible(1, true);
      pKind4->SetVisible(1, true);
      pKind9->SetVisible(1, true);
      textId = 0x90a50aa;
      break;
    case 0x67a0a6e:
      pKind1->SetVisible(1, true);
      pKind7->SetVisible(1, true);
      textId = 0x90a50a6;
      break;
    case 0x67a0a6f:
      pKind1->SetVisible(1, true);
      pKind6->SetVisible(1, true);
      textId = 0x90a50a5;
      break;
    case 0x67a0a70:
      pKind1->SetVisible(1, true);
      pKind5->SetVisible(1, true);
      textId = 0x90a50a2;
      break;
    case 0x67a0a71:
      pKind1->SetVisible(1, true);
      pKind5->SetVisible(1, true);
      textId = 0x90a50a3;
      break;
    case 0x67a0a72:
      pKind1->SetVisible(1, true);
      pKind6->SetVisible(1, true);
      textId = 0x90a50a4;
      break;
    case 0x67a0a73:
    case 0x67a0a76:
      if (!mMusicOn) {
        pKind1->SetVisible(1, true);
        pKind5->SetVisible(1, true);
        pKind6->SetVisible(1, true);
        textId = sAppProperties->GetDescription(0x61b67b6) ? 0x90a50ab : 0x90a50a7;
      } else {
        pKind1->SetVisible(1, true);
        pKind6->SetVisible(1, true);
        textId = 0x90a50a5;
      }
      break;
    case 0x67a0a74:
      pKind1->SetVisible(1, true);
      pKind5->SetVisible(1, true);
      textId = 0x90a50a3;
      break;
    case 0x67a0a75:
      if (mMusicOn) {
        pKind10->SetVisible(1, true);
        pKind8->SetVisible(1, true);
        textId = 0x90a50a1;
      } else {
        pKind9->SetVisible(1, true);
        pKind10->SetVisible(1, true);
        pKind4->SetVisible(1, true);
        pKind9->SetVisible(1, true);
        textId = 0x90a50a8;
      }
      break;
    case 0x67a0a77:
      if (mMusicOn) {
        pKind1->SetVisible(1, true);
        pKind6->SetVisible(1, true);
        textId = 0x90a50a5;
      } else {
        pKind1->SetVisible(1, true);
        pKind7->SetVisible(1, true);
        textId = 0x90a50ac;
      }
      break;
    default:
      pKind1->SetVisible(1, true);
      return false;
  }

  SP::cString text(0xad7b2086, textId, 0);
  pDesc->SetText(text.GetText());
  pDesc->SetVisible(1, true);
  return false;
}
