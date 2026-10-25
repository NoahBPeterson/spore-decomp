#include "types.h"

// Slice s005dfbb0: SP editor play-mode / creature-ability UI.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-.

// ---------------------------------------------------------------------------------------------
// cSPRolloverModelData: model rollover payload for the palette (layout data + UI element list).

namespace EA {
template <typename T>
class RefCountTemplate {
 public:
  RefCountTemplate() : mRefCount(0) {}
  virtual ~RefCountTemplate() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}  // namespace EA

namespace SP {
struct Key {
  uint32_t mInstance;
  uint32_t mType;
  uint32_t mGroup;
};

class IWindow;

class cSPUILayout {
 public:
  virtual void v0();
  virtual int AddRef();    // +0x04
  virtual int Release();   // +0x08
  cSPUILayout();                                         // 0x00810000
  ~cSPUILayout();                                        // 0x00811fe0
  bool IsVisible();                                      // 0x00810070
  bool Init(const Key& key, bool visible, uint32_t parentID);   // 0x008120d0
  bool SetParentWin(IWindow* parent, bool visible, uint32_t id);  // 0x008121b0
  IWindow* FindWindowByID(uint32_t id, bool recursive);   // 0x008105b0
  void Shutdown(bool destroyWindows);  // 0x00811ad0
  char mPad04[0x14];                   // +0x04 .. +0x17
};

template <typename T>
class AutoRefCount {
 public:
  T* mpObject;
  AutoRefCount() : mpObject(0) {}
  AutoRefCount(T* p) : mpObject(p) { if (p) p->AddRef(); }
  AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount() { if (mpObject) mpObject->Release(); }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};

void operator delete[](void* p);  // 0x00f47380

template <class T>
class vector {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~vector() {
    T* last = mpEnd;
    T* first = mpBegin;
    for (; first < last; ++first) first->~T();
    if (mpBegin && ((int*)mpBegin)[-1] != 0) operator delete[](mpBegin);
  }
  int size() const { return (int)(mpEnd - mpBegin); }
  T& operator[](int i) { return mpBegin[i]; }
  T* begin() { return mpBegin; }
  T* end() { return mpEnd; }
  T* erase(T* first, T* last);  // 0x005c2170
  void grow(T* pos, const T* value);  // 0x005c8480
  void push_back(const T& value) {
    if (mpEnd < mpCapacity) {
      T* slot = mpEnd++;
      slot->mpObject = value.mpObject;
      if (slot->mpObject) slot->mpObject->AddRef();
    } else {
      grow(mpEnd, &value);
    }
  }
};

class cRefCounted {
 public:
  cRefCounted() : mnRefCount(0) {}
  virtual ~cRefCounted() {}
  int mnRefCount;
};

class cSPRolloverModelDataBase {
 public:
  virtual ~cSPRolloverModelDataBase() {}
};

class cSPRolloverModelData : public cSPRolloverModelDataBase, public cRefCounted {
 public:
  cSPRolloverModelData(const Key& modelKey, const Key& itemKey, uint32_t layoutID,
                       uint32_t layoutGroup, uint32_t textID);  // 0x005e0370
  virtual ~cSPRolloverModelData();                              // 0x005e0440

  Key mModelKey;      // +0x0c
  Key mItemKey;       // +0x18
  Key mLayoutKey;     // +0x24
  Key mGroupKey;      // +0x30
  vector<AutoRefCount<cSPUILayout> > mItems;  // +0x3c
  uint32_t mUnk48;    // +0x48
  uint32_t mUnk4c;    // +0x4c
  uint32_t mUnk50;    // +0x50
  uint32_t mTextID;   // +0x54
};
}  // namespace SP

// @ 0x005e0370
SP::cSPRolloverModelData::cSPRolloverModelData(const Key& modelKey, const Key& itemKey,
                                               uint32_t layoutID, uint32_t layoutGroup,
                                               uint32_t textID)
    : mModelKey(), mItemKey(), mLayoutKey(), mGroupKey(), mItems(), mTextID(0)
{
  mModelKey = modelKey;
  mItemKey = itemKey;
  mLayoutKey.mInstance = layoutID;
  mLayoutKey.mType = 0x510a95b;
  mLayoutKey.mGroup = 0x40464100;
  mGroupKey.mInstance = layoutGroup;
  mGroupKey.mType = 0x510a95b;
  mGroupKey.mGroup = 0x40464100;
  mTextID = textID;
  if (mTextID == 0) mTextID = 0x4ecf38a;
}

// @ 0x005e0440
SP::cSPRolloverModelData::~cSPRolloverModelData()
{
  int count = mItems.size();
  for (int i = 0; i < count; i++)
    mItems[i]->Shutdown(true);
  vector<AutoRefCount<cSPUILayout> >& items = mItems;
  items.erase(items.begin(), items.end());
  mTextID = 0;
}

// ---------------------------------------------------------------------------------------------
// SP::cSPEditorUI command dispatch.
#define PV(n) virtual void _pv##n();

namespace SP {
struct Vec4 {
  float x, y, z, w;
};

struct cEditorApp {
  char pad0[0x48];
  Vec4 mColor;                 // +0x48
  char pad58[0x174];           // +0x58 .. +0x1cb
  struct cEditorState* mState; // +0x1cc
  Vec4 GetColor() const;       // 0x00572190
  void ShowTutorial();         // 0x00572260
};

struct cEditorState {
  char pad0[0x10];
  Key mKey;          // +0x10
  char pad1c[0x74];  // +0x1c .. +0x8f
  uint32_t mType;    // +0x90
};

struct Rect {
  float x1, y1, x2, y2;
  Rect() {}
  Rect(const Rect& o) : x1(o.x1), y1(o.y1), x2(o.x2), y2(o.y2) {}
};

class IWindow {
 public:
  virtual int AddRef();   // +0x00
  virtual int Release();  // +0x04
  PV(2)
  virtual IWindow* Cast(uint32_t typeID);  // +0x0c
  PV(4) PV(5) PV(6)
  virtual void SetVisible(bool visible);   // +0x1c
  PV(8) PV(9)
  virtual uint32_t GetFlags();             // +0x28
  PV(11) PV(12) PV(13)
  virtual Rect& GetArea();                 // +0x38
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26)
  virtual void SetLayoutArea(const Rect& area);  // +0x6c
  PV(28)
  virtual void SetSize(float w, float h);  // +0x74
  PV(30)
  virtual void SetFlag(int flag, bool value);  // +0x7c
  virtual void SetText(const wchar_t* text);   // +0x80
  PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43)
  PV(44) PV(45) PV(46) PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53)
  virtual void AddWindow(IWindow* child);      // +0xd8
  PV(55) PV(56) PV(57) PV(58) PV(59)
  virtual IWindow* FindWindowByID(uint32_t id, bool recursive);  // +0xf0
};

class IWinButton {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual void SetButtonStateFlag(int flag, bool value);  // +0x28
};

class IWinGrid {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
  PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
  PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
  PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39)
  PV(40)
  virtual bool GetLastUsedCell(int* col, int* row);  // +0xa4
  PV(42) PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49) PV(50) PV(51)
  PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58) PV(59)
  PV(60) PV(61) PV(62) PV(63) PV(64) PV(65) PV(66) PV(67) PV(68) PV(69)
  PV(70) PV(71) PV(72) PV(73) PV(74) PV(75) PV(76) PV(77) PV(78) PV(79)
  PV(80) PV(81) PV(82) PV(83) PV(84) PV(85) PV(86) PV(87) PV(88) PV(89)
  PV(90) PV(91) PV(92) PV(93) PV(94) PV(95) PV(96) PV(97) PV(98) PV(99)
  PV(100) PV(101) PV(102) PV(103) PV(104) PV(105) PV(106) PV(107) PV(108)
  PV(109) PV(110) PV(111) PV(112)
  virtual int GetCellValue(int col, int row);  // +0x1c4
};

class IWindowManager {
 public:
  PV(0)
  virtual IWindow* GetMainWindow();  // +0x04
};
IWindowManager* GetManager();  // 0x00957f30

class cModel {
 public:
  char pad0[0x58];
  uint32_t mSelectedType;  // +0x58
};

class IPlayModeCallout {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5)
  virtual bool Invoke(void* arg, void* msg);  // +0x18
};

class IPlayMode {
 public:
  char pad0[0xc];
  IPlayModeCallout* mpCallout;  // +0x0c
};

class cAppModeEditorBase {
 public:
  char pad0[0x3c];
  uint32_t mStateFlags;    // +0x3c
  char pad40[0x3c];        // +0x40 .. +0x7b
  IPlayMode* mpPlayMode;   // +0x7c
  char pad80[0x18];        // +0x80 .. +0x97
  cModel* mpModel;         // +0x98

  void ForwardMouseDownToTorsoTool();     // 0x005724a0
  void SetActiveBlock(void* block, int r);  // 0x00573c00
  void DeactivateHelper();                // 0x0058a950
  void Undo(char a, char b);              // 0x0058a5a0
  bool ExportPaintTheme(bool showDialog); // 0x0057c590
};

struct UIMessageSender {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
  virtual int GetCommandID();  // +0x20
};

struct UIMessage {
  UIMessageSender* mpSender;  // +0x00
  uint32_t m04;               // +0x04
  int mId;                    // +0x08
  int mSubId;                 // +0x0c
  uint32_t m10;               // +0x10
  uint32_t m14;               // +0x14
  IWindow* mpWindow;          // +0x18
};

// IWinProc base subobject of the editor UI (lives at cSPEditorUI+4).
class cSPEditorUIProc {
 public:
  PV(0)
  char pad04[0x0c];                 // +0x04 .. +0x0f
  cSPUILayout mLayout;              // +0x10
  char pad28[0x30];                 // +0x28 .. +0x57
  cAppModeEditorBase* mApp;         // +0x58
  char pad5c[0x14];                 // +0x5c .. +0x6f
  IWinGrid* mGridTypes;             // +0x70
  char pad74[0x29];                 // +0x74 .. +0x9c
  bool mb9d;                        // +0x9d
  bool mb9e;                        // +0x9e
  char pad9f[0x69];                 // +0x9f .. +0x107
  bool mb108;                       // +0x108
  char pad109[3];
  AutoRefCount<cSPUILayout> mpModalLayout;  // +0x10c

  bool DoMessage(void* arg, UIMessage* msg);  // 0x005e0000
};

struct ConfigManagerObj {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11)
  virtual int GetValue(uint32_t id);  // +0x30
};
struct MessageServerObj {
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void PostCmd(uint32_t id, uint32_t a, uint32_t b);       // +0x14
  virtual void Post(uint32_t id, void* msg, int a, int b);        // +0x18
};
struct EditorProperties {
  char pad0[0x3c];
  struct DirectPropertyList* mpList;  // +0x3c
};
struct DirectPropertyList {
  char pad0[0x118];
  int mFlag118;  // +0x118
};

extern EditorProperties* gAppProperties;  // 0x015fd918
extern Key gDialogBoxKey;                 // 0x01519a48

ConfigManagerObj* __cdecl ConfigManager();     // 0x0067dd30
MessageServerObj* __cdecl MessageServer();     // 0x0067dcc0
void __cdecl KillSeti(uint32_t id);            // 0x004a88d0
void __cdecl CalloutMessageBox(void* where, const Key* key);  // 0x00809db0
void __cdecl Launch(uint32_t a, void* b, uint32_t c);         // 0x0064bc50
bool __cdecl ShowSettingsWindow(int id);       // 0x006035d0
void __cdecl Set895(uint8_t v);                // 0x008098f0

struct cSPEditorUI {
  char pad0[0x5c];
  cEditorApp* mApp;               // +0x5c
  char pad60[0x48];               // +0x60 .. +0xa7
  Key mDroppedKey;                // +0xa8
  char mDialogResultCallback[0x14];  // +0xb4
  uint32_t mCurrentDialogID;      // +0xc8
  int mCurrentCommand;            // +0xcc
  bool mButtonDepressed;          // +0xd0

  bool DoCommand(int cmd);                       // 0x005dfd00
  void SetMode(int mode);                        // 0x005dda30
  void OnFileDrop(const Key& key);               // 0x005dfbb0
  void HandleFileDrop(Key key);                  // 0x005df8f0
  void DoPaletteClick(Vec4 color);               // 0x005dca00
  void FUN_005df470(uint32_t cmd, int b);        // 0x005df470
  void DoSaveAndExit();                          // 0x005dfb40
  void FUN_005df8d0();                           // 0x005df8d0
  void OnSaveRequested();                        // 0x005dd300
  void HandleRequestedPostSaveAction(uint32_t a);  // 0x005dc4d0
  void SetPaintMode(bool paint);                 // 0x005dd610
  IWindow* FindWindowByID(uint32_t id);          // 0x005dc310
};
}  // namespace SP

using SP::cSPEditorUI;

// ---------------------------------------------------------------------------------------------
// UI::BehaviorMessage (editor drop notification payload).
extern char vtbl_BehaviorMessage[];  // 0x013eb90c
extern char vtbl_13eb844[];          // 0x013eb844
void* __cdecl operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                           const char* file, int line);  // 0x00f473a0
extern "C" long _InterlockedExchange(long volatile*, long);

struct __declspec(novtable) BehaviorMessageBase {
  virtual void v0();
  virtual int AddRef();
  virtual int Release();
  long rc;             // +0x04
  void* data;          // +0x08
  char pad0c[0x24];    // +0x0c .. +0x2f
  uint32_t id;         // +0x30
  uint32_t pad34;
  __forceinline BehaviorMessageBase() : id(0) {
    *(void**)this = vtbl_BehaviorMessage;
    _InterlockedExchange(&rc, 0);
  }
};
struct __declspec(novtable) BehaviorMessage : BehaviorMessageBase {
  uint32_t f38;        // +0x38
  uint32_t pad3c;
  __forceinline BehaviorMessage() : f38(0) { *(void**)this = vtbl_13eb844; }
};

// @ 0x005dfbb0
void cSPEditorUI::OnFileDrop(const SP::Key& key)
{
  if (key.mInstance == 0) return;
  SP::EditorProperties* props = SP::gAppProperties;
  if (props->mpList->mFlag118 != 0 && mApp->mState->mType == 0x517560a) {
    BehaviorMessage* msg = new ("Casual", 0, 0, 0, 0) BehaviorMessage();
    if (msg) msg->AddRef();
    mDroppedKey = key;
    msg->data = &mDroppedKey;
    SP::MessageServer()->Post(0x4a34c11, (BehaviorMessage*)msg, 0, 0);
    BehaviorMessage* msg2 = new ("Casual", 0, 0, 0, 0) BehaviorMessage();
    mApp->mState->mKey = mDroppedKey;
    msg2->data = (void*)0x418a508;
    SP::MessageServer()->Post(0xe11332, (BehaviorMessage*)msg2, 0, 0);
    msg->Release();
    return;
  }
  HandleFileDrop(key);
}

// @ 0x005dfd00
bool cSPEditorUI::DoCommand(int cmd)
{
  mButtonDepressed = true;
  switch (cmd) {
  case 0x100:
    break;
  case 0x101:
  case 0x107:
    mCurrentCommand = cmd;
    FUN_005df470(cmd, 1);
    return true;
  case 0x102:
    mCurrentCommand = cmd;
    DoSaveAndExit();
    return true;
  case 0x103:
    mCurrentCommand = cmd;
    FUN_005df8d0();
    return true;
  case 0x104:
    mCurrentCommand = cmd;
    SP::KillSeti(0xa03e74b2);
    FUN_005df470(mCurrentCommand, 1);
    return true;
  case 0x10a:
    SP::KillSeti(0xa03e74b2);
    OnSaveRequested();
    return true;
  case 0x105:
    if (SP::gAppProperties->mpList->mFlag118 != 0 &&
        SP::ConfigManager()->GetValue(0x604a51a) != 0) {
      mCurrentDialogID = 0x604fab1;
      SP::CalloutMessageBox(mDialogResultCallback, &SP::gDialogBoxKey);
      return true;
    }
    mCurrentCommand = cmd;
    SP::KillSeti(0xa03e74b2);
    SP::Launch(0xdb184acb, this, 0x54acb9f1);
    return true;
  case 0x106:
    mCurrentCommand = cmd;
    SP::KillSeti(0xa03e74b2);
    SP::ShowSettingsWindow(0xdbdba1);
    if (SP::gAppProperties->mpList->mFlag118 != 0) SP::Set895(1);
    return true;
  case 0x10c:
    SP::MessageServer()->PostCmd(0xf40f8fe4, 0, 0);
    return true;
  case 0x108:
    mCurrentCommand = cmd;
    SP::KillSeti(0xa03e74b2);
    mApp->ShowTutorial();
    return true;
  case 0x109:
    mCurrentCommand = 0;
    DoPaletteClick(mApp->GetColor());
    return true;
  case 0x10d: {
    SP::KillSeti(0xa03e74b2);
    IWindow* w = FindWindowByID(0x47bc920);
    if (w) {
      bool paintMode = w->GetFlags() & 1;
      SetPaintMode(!paintMode);
    }
    return true;
  }
  default:
    return false;
  }
  if (SP::gAppProperties->mpList->mFlag118 != 0 &&
      SP::ConfigManager()->GetValue(0x604a51a) != 0) {
    mCurrentDialogID = 0x604fa6b;
    SP::CalloutMessageBox(mDialogResultCallback, &SP::gDialogBoxKey);
    return true;
  }
  mCurrentCommand = cmd;
  SP::KillSeti(0xa03e74b2);
  HandleRequestedPostSaveAction(0);
  return true;
}

// ---------------------------------------------------------------------------------------------
// Support objects used by the editor UI message handler.

namespace SP {
class cVariant {
 public:
  uint32_t mPad00[4];   // +0x00
  uint32_t mnFlags10;   // +0x10
  void FUN_005dd750(bool* pValue);      // 0x005dd750
  void Destruct(int flag);              // 0x0093db80
};

class cPropertyList {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void* v14(uint32_t key, cVariant* value);  // +0x14
};

void* SP_GetSaveArea(uint32_t id);                             // 0x006b1f90
void SP_SaveResource(cPropertyList* prefs, void* area, int flag);  // 0x006b1d50
void* GetImageFromLayout(uint32_t value);                      // 0x00458de0
void Pollinator(IWindow* window, Rect* rect);                  // 0x00806d10

IWinButton* interface_cast_button(IWindow* window);            // 0x005ca960
void SetImageA(IWindow* window, void* image, int flags);       // 0x00806aa0
void SetImageB(IWindow* window, void* image, int flags);       // 0x008068d0
}  // namespace SP

extern SP::cPropertyList* _sAppPreferences_SP;  // 0x015fd91c

// ---------------------------------------------------------------------------------------------
// @ 0x005e0000
bool SP::cSPEditorUIProc::DoMessage(void* pArg, UIMessage* msg)
{
  if (!mLayout.IsVisible()) return false;
  if (!mb9d) return false;
  if (mb9e) return false;

  if (msg->mId == 0x9a1552d3) {
    if (msg->mSubId == 0x503517b0) {
      int col;
      int row;
      if (mGridTypes->GetLastUsedCell(&col, &row))
        mApp->mpModel->mSelectedType = mGridTypes->GetCellValue(col, row);
    }
    return true;
  } else if (msg->mId == 0x287259f6) {
    cSPEditorUI* ui = (cSPEditorUI*)((char*)this - 4);
    if (ui->DoCommand(msg->mpSender->GetCommandID())) return true;

    switch (msg->mSubId) {    case (int)0xf006efa5:
      KillSeti(0x677f1fb8);
      mApp->DeactivateHelper();
      return true;

    case (int)0xb006ef6e:
      KillSeti(0xc355901a);
      mApp->Undo(1, 1);
      return true;

    case (int)0xf019c2e7:
      ui->SetMode(0);
      return true;

    case (int)0xf019c2f3:
      ui->SetMode(1);
      return true;

    case 0x3f67720:
    case 0x447b968:
    case 0x447b980:
    case 0x447c040:
    case 0x447c4e8:
    case 0x56be960:
    case 0x5adbea8:
      return mApp->mpPlayMode->mpCallout->Invoke(pArg, msg);

    case 0x47bc978:
      KillSeti(0xa03e74b2);
      ShowSettingsWindow(0xdbdba1);
      return true;

    case 0x864a768: {
      cPropertyList* prefs = _sAppPreferences_SP;
      bool value = true;
      cVariant variant;
      variant.FUN_005dd750(&value);
      prefs->v14(0x87c4363, &variant);
      if ((variant.mnFlags10 & 4) != 0) variant.Destruct(0);
      SP_SaveResource(prefs, SP_GetSaveArea(0x11ac192), 0);
      mb108 = true;
      if (mApp) mApp->ExportPaintTheme(false);
      return false;
    }
    case 0x864a77d: {
      IWindow* w = mpModalLayout->FindWindowByID(0x864a768, true);
      if (w) {
        IWinButton* button = interface_cast_button(w);
        bool bState = ((w->GetFlags() >> 1) & 1) != 0;
        button->SetButtonStateFlag(1, !bState);
        w->SetFlag(2, !bState);
        w->SetFlag(0x10, bState);
      }
      return false;
    }

    case 0x864a771:
      mb108 = true;
      return false;

    case 0x70218642:
      ui->SetMode(2);
      return true;

    default:
      break;
    }
  } else if (msg->mId == 0x1c && msg->mSubId == 1) {
    if (msg->mpWindow == GetManager()->GetMainWindow()) {
      mApp->ForwardMouseDownToTorsoTool();
      if ((mApp->mStateFlags & 0x100) != 0) mApp->SetActiveBlock(0, -1);
    }
  }
  return false;
}

// ---------------------------------------------------------------------------------------------
// 0x005e04d0: SP::AbilityLayoutData::LayoutLine -- lay out one ability row in the editor dialog.
namespace SP {
extern wchar_t gEmptyString16[];  // 0x01667bac
class cString {
 public:
  cString();                      // 0x006b5060
  ~cString();                     // 0x006b5240
  const wchar_t* GetText();       // 0x006b55c0
  uint32_t mData[5];
};

class cWStr {
 public:
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  cWStr() : mpBegin(gEmptyString16), mpEnd(gEmptyString16), mpCapacity(gEmptyString16 + 1) {}
  ~cWStr() {
    if (mpCapacity - mpBegin > 1 && mpBegin) operator delete[]((void*)mpBegin);
  }
};
cWStr* WStr_Format(cWStr* str, const wchar_t* fmt, ...);  // 0x0041e050

class AbilityLayoutData {
 public:
  char pad0[0xc];             // +0x00 .. +0x0b
  Key mVehicleKey;            // +0x0c
  Key mTypeKey;               // +0x18
  Key mLineKey;               // +0x24
  Key mRowKey;                // +0x30
  vector<AutoRefCount<cSPUILayout> > mPages;  // +0x3c
  char pad4c[8];              // +0x48 .. +0x53
  uint32_t mAbilityPropId;    // +0x54

  float LayoutLine(IWindow* window, const Key* key, float startY, uint32_t value,
                   const Key* subKey, cString* text, float number);  // 0x005e04d0
};
}  // namespace SP

// @ 0x005e04d0
float SP::AbilityLayoutData::LayoutLine(IWindow* window, const Key* key, float startY,
                                        uint32_t value, const Key* subKey, cString* text,
                                        float number)
{
  AutoRefCount<cSPUILayout> dialog(new ("Editor", 0, 0, 0, 0) cSPUILayout());

  dialog->Init(*key, true, 0x5b598fa);
  dialog->SetParentWin(window, true, 0x5b598fa);

  IWindow* row = dialog->FindWindowByID(0x4c01bd5, true);
  Rect rowArea = row->GetArea();
  float height = rowArea.y2 - rowArea.y1;
  const Rect& windowArea = window->GetArea();
  row->SetSize(windowArea.x2 - windowArea.x1, height);

  if (value != 0) {
    IWindow* holder = dialog->FindWindowByID(0x4c01bbe, true);
    IWindow* subWindow = 0;
    if (subKey->mInstance != 0) {
      cSPUILayout sub;
      sub.Init(*subKey, true, 0x5b598fa);
      subWindow = sub.FindWindowByID(0x902d3163, true);
      if (subWindow) subWindow->AddRef();
    }
    if (subWindow) {
      holder->AddWindow(subWindow);
      Rect pollArea = holder->GetArea();
      pollArea.x2 -= pollArea.x1;
      pollArea.y2 -= pollArea.y1;
      pollArea.x1 = 0.0f;
      pollArea.y1 = 0.0f;
      Pollinator(subWindow, &pollArea);
      IWindow* button = subWindow->FindWindowByID(0x6283c92, false);
      if (!button) button = subWindow->FindWindowByID(0x4976e19, false);
      if (button) {
        button->SetFlag(0x10, true);
        SetImageA(button, GetImageFromLayout(value), 0);
      }
      subWindow->Release();
    } else if (holder) {
      SetImageB(holder, GetImageFromLayout(value), 0);
    }
  }

  IWindow* textWindow = dialog->FindWindowByID(0x4c01bc4, true);
  if (textWindow) {
    Rect savedArea = textWindow->GetArea();
    textWindow->SetText(text->GetText());
    IWindow* inner = textWindow->Cast(0xf15f4bd);
    inner->SetVisible(true);
    Rect& newArea = textWindow->GetArea();
    float delta = (newArea.y2 - newArea.y1) - (savedArea.y2 - savedArea.y1);
    if (delta < 0.0f) {
      textWindow->SetLayoutArea(savedArea);
      delta = 0.0f;
    }
    height += delta;
  }

  IWindow* numberWindow = dialog->FindWindowByID(0x4c01bca, true);
  if (numberWindow) {
    if (number == -1.0f) {
      numberWindow->SetText(L"");
    } else {
      cWStr str;
      WStr_Format(&str, L"%d", (int)number);
      numberWindow->SetText(str.mpBegin);
    }
  }

  Rect layoutArea;
  layoutArea.x1 = 0.0f;
  layoutArea.x2 = windowArea.x2 - windowArea.x1;
  layoutArea.y1 = startY;
  layoutArea.y2 = startY + height;
  row->SetLayoutArea(layoutArea);

  mPages.push_back(dialog);
  return height;
}

