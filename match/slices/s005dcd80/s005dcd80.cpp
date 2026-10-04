// Slice s005dcd80: SP::cSPEditorUI (Spore editor UI) methods.
// Retail layout: cSPUILayout grew to 0x18 bytes, so every member after the layouts is
// shifted relative to the 2008 PDB (mApp 0x38 -> 0x5c, mUIEditorMode 0x3c -> 0x60, ...).
#include "types.h"

#define PV(n) virtual void _pv##n();

namespace Math {
struct Rectangle {
  float x1, y1, x2, y2;
  Rectangle(const Rectangle& r) : x1(r.x1), y1(r.y1), x2(r.x2), y2(r.y2) {}
  float GetWidth() const { return x2 - x1; }
  float GetHeight() const { return y2 - y1; }
};
}  // namespace Math

namespace EA {
namespace ResourceMan {
struct Key {
  uint32_t instanceID;
  uint32_t typeID;
  uint32_t groupID;
  Key(uint32_t i, uint32_t t, uint32_t g) : instanceID(i), typeID(t), groupID(g) {}
};
}  // namespace ResourceMan

namespace UTFWin {
class IWinProc {
 public:
  PV(0)
};

class IWindow;

class IWinButton {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual void SetButtonStateFlag(int flag, bool value);  // +0x28
};

class IWindow {
 public:
  PV(0) PV(1) PV(2)
  virtual void* Cast(uint32_t typeID);                // +0x0c
  virtual IWindow* GetParent();                       // +0x10
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
  virtual void BringToFront(IWindow* child);          // +0xe8
  PV(59) PV(60) PV(61) PV(62) PV(63) PV(64) PV(65)
  virtual void RemoveWinProc(IWinProc* proc);         // +0x108
};

class IWindowManager {
 public:
  PV(0)
  virtual IWindow* GetMainWindow();                   // +0x04
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
  PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
  virtual void ReleaseCapture(int type, IWindow* w);  // +0x58
  virtual void SetCapture(int type, IWindow* w);      // +0x5c
};
}  // namespace UTFWin

namespace UTFWinControls {
class IWinGrid {
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
};
}  // namespace UTFWinControls

template <typename T>
class AutoRefCount {
 public:
  T* mpObject;
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
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};
}  // namespace EA

using EA::UTFWin::IWindow;
using EA::UTFWin::IWinButton;

void* operator new(unsigned int size, const char* pName, int flags, unsigned debugFlags,
                   const char* file, int line);

class cSPUILayout {
 public:
  PV(0)
  virtual int AddRef();   // +0x04
  virtual int Release();  // +0x08
  cSPUILayout();
  bool Init(const EA::ResourceMan::Key& key, bool visible, uint32_t parentID);
  void SetVisibility(bool visible);
  IWindow* FindWindowByID(uint32_t id, bool recursive);
  void Shutdown(bool unused);
  bool SetParentWin(IWindow* parent, bool b, uint32_t id);
  uint32_t mData[5];
};

namespace SP {
EA::UTFWin::IWindowManager* WindowManager();

namespace SPUIHelpers {
void* GetLayoutManager();
void CenterWindowInRect(IWindow* w, const Math::Rectangle& r);
}  // namespace SPUIHelpers

namespace EditorUtils {
bool GetCreatorType(const EA::ResourceMan::Key* key);
}

struct DialogDesc {
  uint32_t mID;
  uint32_t mData[2];
};
void ShowDialog(void* callback, const DialogDesc* desc);  // FUN_00809db0

class cString {
 public:
  cString();
  ~cString();
  uint32_t mData[5];
};

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
inline bitset128 operator&(const bitset128& a, const bitset128& b) {
  bitset128 r(a);
  r &= b;
  return r;
}
bool BitsetContains(bitset128 a, bitset128 b);  // FUN_004f3d60

class cEditorModel {
 public:
  PV(0)
  virtual uint32_t GetModelType();  // +0x04
  uint32_t pad04[2];
  EA::ResourceMan::Key mKey;        // +0x0c
  char pad18[0x40];
  int mSelectedType;                // +0x58
};

class cAppModeEditorBase {
 public:
  int GetEditorSaveability();
  bool SetMode(int mode, bool b);
  int CanEnterMode(int b);                // FUN_00574a20
  bool IsPaintModeAvailable();            // 0xb1e4d0
  bitset128 GetPartFlags();               // FUN_0057a9e0
  char pad00[0x98];
  cEditorModel* mpEditorModel;  // +0x98
};

class cEditorHistory {  // FUN_005d60c0 target (global at 0x15eebec)
 public:
  void SetModelType(uint32_t type);
};
extern cEditorHistory* gEditorHistory;

class IOnlineManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
  virtual void SetState(int s);   // +0x20
  virtual bool IsLoggedIn();      // +0x24
  PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16)
  virtual void Update();          // +0x44
};
IOnlineManager* OnlineManager();  // FUN_00607a60

class IGameCamera {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
  PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
  PV(20) PV(21) PV(22)
  virtual void PushInputMode(int a, int b);  // +0x5c
  virtual void PopInputMode(int a, int b);   // +0x60
};
IGameCamera* CameraManager();  // FUN_0067dd50

class cRenderer {
 public:
  void SetPaused(bool a, bool b);  // FUN_0067c420
};
cRenderer* Renderer();  // FUN_0067cac0

class cAudioState {
 public:
  void Push(int a, int b, uint32_t id);  // FUN_0045ae40
  void Pop();                            // FUN_0045b150
};
cAudioState* __stdcall AudioState(uint32_t id);  // FUN_00401050

void PlayUISound(uint32_t id);  // FUN_004a88d0

extern const char kLayoutAllocName[];
extern const EA::ResourceMan::Key kModalLayoutKey;  // 0x151991c
extern const DialogDesc kDialogSaveA;               // 0x1519928
extern const DialogDesc kDialogSaveB;               // 0x1519934
extern const bitset128 gFlagsA;  // 0x15dab94
extern const bitset128 gFlagsB;  // 0x15da7c4
extern const bitset128 gMask;    // 0x15da7ec

class cSPUIAssetBrowserCallback {
 public:
  PV(0)
};

class cSPEditorUI : public cSPUIAssetBrowserCallback, public EA::UTFWin::IWinProc {
 public:
  uint32_t pad08[3];
  cSPUILayout mLayout;                                  // +0x14
  cSPUILayout mSharedLayout;                            // +0x2c
  cSPUILayout mCameraControlsLayout;                    // +0x44
  cAppModeEditorBase* mApp;                             // +0x5c
  int mUIEditorMode;                                    // +0x60
  IWindow* mWinLeftPanelFrame;                          // +0x64
  IWindow* mWinPartPaletteRoot;                         // +0x68
  IWindow* mWinPaintPaletteRoot;                        // +0x6c
  IWindow* mWindowTypeBrowser;                          // +0x70
  EA::UTFWinControls::IWinGrid* mGridTypes;             // +0x74
  IWindow* mClickCatcher;                               // +0x78
  uint32_t pad7c;
  IWindow* mWin80;                                      // +0x80
  IWindow* mWin84;                                      // +0x84
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
  EA::AutoRefCount<cSPUILayout> mpModalLayout;          // +0x110

  IWindow* FindWindowByID(uint32_t id) {
    if (IWindow* w = mLayout.FindWindowByID(id, true))
      return w;
    return mSharedLayout.FindWindowByID(id, true);
  }
  void SetWindowVisibility(uint32_t id, bool visible);
  void StopListeningToMessages();
  void StartListeningToMessages();
  void UpdateUndoRedo(bool disabled);  // FUN_005dc970
  void UpdateSaveButtons();            // FUN_005dc800
  bool CheckWarnings(bitset128 flags, bitset128 partFlags, EA::ResourceMan::Key key);  // FUN_005dc190

  void SetUIDisabled(bool disabled);
  void EnableRedoButton(bool enable);
  void EnableUndoButton(bool enable);
  void SetSelected(uint32_t id, bool selected, bool alsoState20);
  void EnablePlayModeButton(bool enable);
  void Hide();
  void Show();
  void SetInputBlocked(bool blocked);
  void SelectCurrentTypeInGrid();
  void ShowSaveDialog();
  void OnSaveRequested();
  void OnLoginResult(bool success);
  void CloseModalLayout();
  void OpenModalLayout();
  void SetPaintMode(bool paint);
  void UpdateUIBasedOnModelSaveability();
  uint32_t GetWarning(bitset128 flags);
  void SetMode(int mode);
};

// @ 0x005dcd80
void cSPEditorUI::SetUIDisabled(bool disabled) {
  mUIDisabled = disabled;
  if (IWindow* w = FindWindowByID(0x682102a))
    w->SetFlag(1, !disabled);
  if (IWindow* w = FindWindowByID(0x682102b))
    w->SetFlag(1, !disabled);
  UpdateUndoRedo(mUIDisabled);
}

// @ 0x005dce40
void cSPEditorUI::EnableRedoButton(bool enable) {
  IWindow* w = FindWindowByID(0xf006efa5);
  if (w) {
    w->SetFlag(2, enable);
    w->SetFlag(0x10, !enable);
    w->Invalidate();
  }
}

// @ 0x005dceb0
void cSPEditorUI::EnableUndoButton(bool enable) {
  IWindow* w = FindWindowByID(0xb006ef6e);
  if (w) {
    w->SetFlag(2, enable);
    w->SetFlag(0x10, !enable);
    w->Invalidate();
  }
}

// @ 0x005dcf20
void cSPEditorUI::SetSelected(uint32_t id, bool selected, bool alsoState20) {
  IWindow* w = FindWindowByID(id);
  if (w) {
    IWinButton* button = (IWinButton*)w->Cast(0x8ed27e7a);
    button->SetButtonStateFlag(4, selected);
    if (alsoState20)
      button->SetButtonStateFlag(0x20, selected);
    w->Invalidate();
  }
}

// @ 0x005dcf90
void cSPEditorUI::EnablePlayModeButton(bool enable) {
  IWindow* button = FindWindowByID(0x70218642);
  IWindow* blocker = FindWindowByID(0x66ff240);
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

// @ 0x005dd050
void cSPEditorUI::Hide() {
  mLayout.SetVisibility(false);
  mSharedLayout.SetVisibility(false);
  StopListeningToMessages();
}

// @ 0x005dd070
void cSPEditorUI::Show() {
  StartListeningToMessages();
  mLayout.SetVisibility(true);
  mSharedLayout.SetVisibility(true);
}

// @ 0x005dd090
void cSPEditorUI::SetInputBlocked(bool blocked) {
  bool wasBlocked = mInputBlocked;
  mInputBlocked = blocked;
  if (mClickCatcher) {
    mClickCatcher->SetFlag(1, !blocked);
    if (!mInputBlocked) {
      IWindow* parent = mClickCatcher->GetParent();
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

// @ 0x005dd1d0
void cSPEditorUI::SelectCurrentTypeInGrid() {
  int type = mApp->mpEditorModel->mSelectedType;
  EA::UTFWinControls::IWinGrid::Range range;
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

// @ 0x005dd250
void cSPEditorUI::ShowSaveDialog() {
  cString str;
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

// @ 0x005dd300
void cSPEditorUI::OnSaveRequested() {
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

// @ 0x005dd360
void cSPEditorUI::OnLoginResult(bool success) {
  if (mCurrentCommand == 0x10a) {
    if (success)
      ShowSaveDialog();
    else
      mCurrentCommand = 0;
  }
}

// @ 0x005dd390
void cSPEditorUI::CloseModalLayout() {
  if (mpModalLayout) {
    if (mpModalLayout->FindWindowByID(0x864a77d, true))
      mpModalLayout->FindWindowByID(0x864a77d, true)->RemoveWinProc(this);
    if (mpModalLayout->FindWindowByID(0x864a768, true))
      mpModalLayout->FindWindowByID(0x864a768, true)->RemoveWinProc(this);
    if (mpModalLayout->FindWindowByID(0x864a771, true))
      mpModalLayout->FindWindowByID(0x864a771, true)->RemoveWinProc(this);
    IWindow* blocker = mpModalLayout->FindWindowByID(0x864a5fa, true);
    if (blocker)
      SP::WindowManager()->SetCapture(0, blocker);
    mpModalLayout->Shutdown(true);
    mpModalLayout = 0;
  }
}

// @ 0x005dd4a0
void cSPEditorUI::OpenModalLayout() {
  CloseModalLayout();
  mpModalLayout = new (kLayoutAllocName, 0, 0, 0, 0) cSPUILayout();
  mpModalLayout->Init(kModalLayoutKey, true, 0x5b598fa);
  mpModalLayout->SetVisibility(true);
  IWindow* dialog = mpModalLayout->FindWindowByID(0x864a5d3, true);
  if (dialog) {
    IWindow* blocker = mpModalLayout->FindWindowByID(0x864a5fa, true);
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

// @ 0x005dd610
void cSPEditorUI::SetPaintMode(bool paint) {
  IWindow* w = FindWindowByID(0x47bc920);
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

// @ 0x005dd7a0
void cSPEditorUI::UpdateUIBasedOnModelSaveability() {
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
  IWindow* w = FindWindowByID(0x5b6e484);
  if (w) {
    w->SetFlag(1, visible);
    w->SetFlag(2, enabled);
  }
  UpdateSaveButtons();
}

// @ 0x005dd860
uint32_t cSPEditorUI::GetWarning(bitset128 flags) {
  bitset128 maskedA = gFlagsA & ~gMask;
  bitset128 maskedB = gFlagsB & ~gMask;
  bool noA = !BitsetContains(flags, maskedA);
  bool noB = !BitsetContains(flags, maskedB);
  uint32_t id;
  if (noB)
    id = noA ? 0xf207647f : 0x7b355311;
  else
    id = noA ? 0xb129f37e : 0xa1520d7f;
  if (CheckWarnings(flags, mApp->GetPartFlags(), EA::ResourceMan::Key(id, 0xb1b104, 0x490f6945)))
    return id;
  return 0;
}

// @ 0x005dda30
void cSPEditorUI::SetMode(int mode) {
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
      if (IWindow* w = FindWindowByID(0x578ec50))
        w->SetFlag(1, true);
      if (IWindow* w = FindWindowByID(0xf006efa5))
        w->SetFlag(1, true);
      if (IWindow* w = FindWindowByID(0xb006ef6e))
        w->SetFlag(1, true);
      if (IWindow* w = FindWindowByID(0x1140129d))
        w->SetFlag(1, mApp->IsPaintModeAvailable());
      break;
    }
  }
  IWindow* parent = 0;
  switch (mode) {
    case 0:
      if (mWinPartPaletteRoot)
        mWinPartPaletteRoot->SetFlag(1, true);
      if (IWindow* w = FindWindowByID(0x578ec50))
        w->SetFlag(1, true);
      if (IWindow* w = FindWindowByID(0xf006efa5))
        w->SetFlag(1, true);
      if (IWindow* w = FindWindowByID(0xb006ef6e))
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
      if (IWindow* w = FindWindowByID(0x578ec50))
        w->SetFlag(1, false);
      if (IWindow* w = FindWindowByID(0xf006efa5))
        w->SetFlag(1, false);
      if (IWindow* w = FindWindowByID(0xb006ef6e))
        w->SetFlag(1, false);
      if (IWindow* w = FindWindowByID(0x1140129d))
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
