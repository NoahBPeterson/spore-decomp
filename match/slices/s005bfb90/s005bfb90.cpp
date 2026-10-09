// SP::cSPEditorNaming (creature name/tag edit panel), SP::cSPEditorPageControls (palette page
// arrows + "n/m" label) and SP::cSPEditorPaintLikeThis::SetImage.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include <new>
#include <string.h>
#include "types.h"

void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380

#define PV(n) virtual void pv##n();

namespace eastl {
extern wchar_t gEmptyString[2];
template <typename T>
inline unsigned int CharStrlen(const T* p) {
  const T* pCurrent = p;
  while (*pCurrent)
    ++pCurrent;
  return (unsigned int)(pCurrent - p);
}
class wstring {
 public:
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  int mAllocator;
  wstring() {
    mpEnd = mpBegin = gEmptyString;
    mpCapacity = mpBegin + 1;
  }
  wstring(const wchar_t* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p); }
  ~wstring() {
    if ((mpCapacity - mpBegin) > 1 && mpBegin)
      EASTL_allocator_deallocate(mpBegin);
  }
  void RangeInitialize(const wchar_t* p);
  wstring& trim();
  void sprintf(const wchar_t* fmt, ...);
  wstring& assign(const wchar_t* first, const wchar_t* last);  // WString_Assign (0x00423650)
  const wchar_t* c_str() const { return mpBegin; }
  bool empty() const { return mpEnd == mpBegin; }
};
}  // namespace eastl

namespace EA {
template <typename T>
class AutoRefCount {
 public:
  T* mpObject;
  AutoRefCount() : mpObject(0) {}
  ~AutoRefCount() { if (mpObject) mpObject->Release(); }
  AutoRefCount& operator=(T* pObject) {
    if (pObject != mpObject) {
      T* const pTemp = mpObject;
      if (pObject) pObject->AddRef();
      mpObject = pObject;
      if (pTemp) pTemp->Release();
    }
    return *this;
  }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};

template <typename T>
class RefCountVTemplate {
 public:
  RefCountVTemplate() : mRefCount(0) {}
  virtual ~RefCountVTemplate() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};

namespace ResourceMan {
struct Key {
  unsigned int mInstance, mType, mGroup;
  Key(unsigned int i, unsigned int t, unsigned int g) : mInstance(i), mType(t), mGroup(g) {}
};
}

namespace UTFWin {
class IWinProc;
class IWindow {
 public:
  virtual int AddRef();
  virtual int Release();
  PV(2)
  virtual void* Cast(uint32_t typeID);                  // +0xc
  PV(4) PV(5) PV(6)
  virtual uint32_t GetControlID();                      // +0x1c
  PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14)
  virtual const wchar_t* GetCaption();                  // +0x3c
  PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
  virtual void SetFlag(int flag, bool value);           // +0x7c
  virtual void SetCaption(const wchar_t* text);         // +0x80
  PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41)
  virtual IWindow* GetDrawable();                       // +0xa8
  PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58)
  PV(59) PV(60) PV(61) PV(62) PV(63) PV(64)
  virtual void AddWinProc(IWinProc* proc);              // +0x104
  virtual void RemoveWinProc(IWinProc* proc);           // +0x108
};
class IWinProc {
 public:
  ~IWinProc() {}
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4)
  virtual bool HandleUIMessage(IWindow* window, const void* message);  // +0x14
  PV(6)
};
class IButtonDrawable {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual void SetImageState(int state, bool value);    // +0x28
};
class ITextEdit {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
  PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
  PV(31) PV(32) PV(33) PV(34) PV(35) PV(36)
  virtual void SetSelection(int start, int end);        // +0x94
  PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49) PV(50) PV(51) PV(52)
  PV(53) PV(54)
  virtual void SelectAll();                             // +0xdc
};
class IColorDrawable {
 public:
  PV(0) PV(1) PV(2) PV(3)
  virtual uint32_t GetColor(int index);                 // +0x10
  virtual void SetColor(int index, uint32_t color);     // +0x14
};
}  // namespace UTFWin

namespace Messaging {
struct Message;
class IHandler {
 public:
  IHandler() {}
  ~IHandler() {}
  virtual bool HandleMessage(uint32_t messageID, void* message);
};
class IMessageServer {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void PostMSG(uint32_t messageID, void* data, void* source);       // +0x14
  PV(6) PV(7)
  virtual void AddHandler(IHandler* handler, uint32_t messageID);           // +0x20
  PV(9) PV(10)
  virtual void RemoveHandler(IHandler* handler, uint32_t messageID, int priority);  // +0x2c
};
}  // namespace Messaging
}  // namespace EA

using EA::UTFWin::IWindow;

class cSPUILayout {
 public:
  PV(0)
  virtual int AddRef();
  virtual int Release();
  cSPUILayout();
  IWindow* FindWindowByID(uint32_t id, bool recursive);
  bool Init(const EA::ResourceMan::Key& key, bool b, uint32_t id);
  void SetParentWin(IWindow* parent, bool b, uint32_t id);
  void Shutdown(bool b);
  char pad[0x18 - 4];
};

namespace SP {
EA::Messaging::IMessageServer* MessageServer();
class IWindowManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16)
  PV(17) PV(18)
  virtual void SetFocusWindow(int a, IWindow* window);  // +0x4c
};
IWindowManager* WindowManager();
void PlayUISound(uint32_t id, uint32_t arg);  // 0x00435ed0

class INameGenerator {
 public:
  eastl::wstring GenerateName(uint32_t nameType);  // FUN_005ecf80
};
INameGenerator* NameGenerator();  // FUN_004010a0

namespace Audio {
class ISystem {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
  virtual uint32_t GetSoundContext();  // +0x20
};
}
Audio::ISystem* GetAudioSystem();  // EA::Audio::GetSystemAT (0x00a206f0)

class cISPEditorNameProvider {
 public:
  virtual void SetName(const wchar_t* name);          // +0x0
  virtual const wchar_t* GetName();                   // +0x4
  virtual void SetTag(const wchar_t* tag);            // +0x8
  virtual const wchar_t* GetTag();                    // +0xc
  virtual void SetDescription(const wchar_t* desc);   // +0x10
  virtual const wchar_t* GetDescription();            // +0x14
};

class cSPNameGuard : public EA::UTFWin::IWinProc, public EA::RefCountVTemplate<int> {
 public:
  virtual int AddRef();
  virtual int Release();
};

struct UIMessage {
  uint32_t pad0;
  IWindow* mpSource;   // +0x4
  int mType;           // +0x8
  int mParam1;         // +0xc
  int mParam2;         // +0x10
  int mParam3;         // +0x14
};

class cSPEditorNaming : public EA::UTFWin::IWinProc, public EA::Messaging::IHandler, public EA::RefCountVTemplate<int> {
 public:
  bool mIsExpanded;                              // +0x10
  bool mAllowNameEdit;                           // +0x11
  EA::AutoRefCount<cSPNameGuard> mNameGuard;     // +0x14
  EA::AutoRefCount<cSPUILayout> mLayout;         // +0x18
  cISPEditorNameProvider* mpDataProvider;        // +0x1c
  unsigned int mNameType;                        // +0x20
  eastl::wstring mNamePrompt;                    // +0x24
  IWindow* mOriginalParent;                      // +0x34

  cSPEditorNaming();
  ~cSPEditorNaming();
  virtual int AddRef();
  virtual int Release();
  virtual void SetExpanded(bool expanded);  // IWinProc slot 7 (+0x1c)
  bool HandleUIMessage(IWindow* window, const void* message);
  bool HandleMessage(uint32_t messageID, void* message);
  void Shutdown();
  void SetTagField(bool enabled);
  void SetDataProvider(cISPEditorNameProvider* provider);
  void Init(cISPEditorNameProvider* provider, IWindow* parent, uint32_t layoutID, bool allowNameEdit, unsigned int nameType);
  void SetPrompt(const wchar_t* prompt);
  void SetDisplayText(const wchar_t* text);
};

// @ 0x005BFB90
void cSPEditorNaming::Shutdown() {
  IWindow* window = mLayout->FindWindowByID(0xc7ceb1bd, true);
  if (window)
    window->RemoveWinProc(mNameGuard);
  if (mNameGuard)
    mNameGuard = 0;
  window = mLayout->FindWindowByID(0x272eb68e, true);
  if (window)
    window->RemoveWinProc(this);
  MessageServer()->RemoveHandler(this, 0x14418c3f, -9999);
  MessageServer()->RemoveHandler(this, 0x7aa519dc, -9999);
  MessageServer()->RemoveHandler(this, 0x1ee1001, -9999);
  if (mLayout->FindWindowByID(0x5415e48, true))
    MessageServer()->AddHandler(this, 0x73127e6);
  if (mLayout) {
    mLayout->Shutdown(true);
    mLayout = 0;
  }
  mpDataProvider = 0;
}

// @ 0x005BFC90
void cSPEditorNaming::SetTagField(bool enabled) {
  IWindow* window = mLayout->FindWindowByID(0x272eb68e, true);
  if (window)
    window->SetFlag(2, enabled);
}

// @ 0x005BFCC0
void cSPEditorNaming::SetDataProvider(cISPEditorNameProvider* provider) {
  mpDataProvider = provider;
  if (provider) {
    SetDisplayText(provider->GetName());
    IWindow* window = mLayout->FindWindowByID(0xaddc11ef, true);
    if (window) {
      const wchar_t* tag = mpDataProvider->GetTag();
      window->SetCaption(tag);
    }
    window = mLayout->FindWindowByID(0x5415e48, true);
    if (window) {
      const wchar_t* desc = mpDataProvider->GetDescription();
      window->SetCaption(desc);
    }
  }
}

// @ 0x005BFD40
void cSPEditorNaming::Init(cISPEditorNameProvider* provider, IWindow* parent, uint32_t layoutID, bool allowNameEdit,
                           unsigned int nameType) {
  mLayout = new ("Editor", 0, 0, 0, 0) cSPUILayout();
  mLayout->Init(EA::ResourceMan::Key(layoutID, 0x510a95b, 0x40464100), true, 0x5b598fa);
  mLayout->SetParentWin(parent, true, 0x5b598fa);
  mAllowNameEdit = allowNameEdit;
  mNameType = allowNameEdit ? nameType : 0;
  mIsExpanded = false;
  mOriginalParent = parent;
  SetDataProvider(provider);
  MessageServer()->AddHandler(this, 0x7aa519dc);
  MessageServer()->AddHandler(this, 0x14418c3f);
  MessageServer()->AddHandler(this, 0x1ee1001);
  if (mLayout->FindWindowByID(0x5415e48, true))
    MessageServer()->AddHandler(this, 0x73127e6);
  IWindow* window = mLayout->FindWindowByID(0x272eb68e, true);
  if (window) {
    window->SetFlag(1, true);
    window->AddWinProc(this);
  }
  if (!mAllowNameEdit) {
    IWindow* src = mLayout->FindWindowByID(0x272eb68e, true);
    IWindow* dst = mLayout->FindWindowByID(0x56c1e03, true);
    if (src && dst) {
      IWindow* d = src->GetDrawable();
      EA::UTFWin::IColorDrawable* srcColors = d ? (EA::UTFWin::IColorDrawable*)d->Cast(0x103c1908) : 0;
      d = dst->GetDrawable();
      EA::UTFWin::IColorDrawable* dstColors = d ? (EA::UTFWin::IColorDrawable*)d->Cast(0x103c1908) : 0;
      if (srcColors && dstColors) {
        for (int i = 0; i < 8; i++)
          srcColors->SetColor(i, dstColors->GetColor(i));
      }
    }
  }
  IWindow* nameWindow = mLayout->FindWindowByID(0xc7ceb1bd, true);
  if (nameWindow) {
    mNameGuard = new ("Editor", 0, 0, 0, 0) cSPNameGuard();
    nameWindow->AddWinProc(mNameGuard);
  }
}

// @ 0x005BFFF0
cSPEditorNaming::cSPEditorNaming()
    : mIsExpanded(false), mAllowNameEdit(true), mpDataProvider(0), mNameType(0), mOriginalParent(0) {}

// @ 0x005C0070
cSPEditorNaming::~cSPEditorNaming() {}

// @ 0x005C0100
bool cSPEditorNaming::HandleUIMessage(IWindow* window, const void* message) {
  const UIMessage* msg = (const UIMessage*)message;
  switch (msg->mType) {
    case 0x287259f6:
      if (msg->mParam1 == 2) {
        Audio::ISystem* sys = GetAudioSystem();
        PlayUISound(0xa03e74b2, sys ? sys->GetSoundContext() : 0);
        eastl::wstring name = NameGenerator()->GenerateName(mNameType);
        SetDisplayText(name.c_str());
        return true;
      }
      break;
    case 1:
      if (msg->mParam1 == 1) {
        SetExpanded(msg->mParam3 == 1);
        return true;
      }
      break;
    case 0x18: {
      int key = msg->mParam2;
      if (key == 0xd || key == 0x1b) {
        if (!(msg->mParam3 & 0x47) && mIsExpanded) {
          SetExpanded(false);
          WindowManager()->SetFocusWindow(0, mOriginalParent);
          return true;
        }
      } else if (key == 9 && msg->mpSource) {
        uint32_t id = msg->mpSource->GetControlID();
        if (id == 0xc7ceb1bd) {
          IWindow* next = mLayout->FindWindowByID(0xaddc11ef, true);
          if (next) {
            WindowManager()->SetFocusWindow(0, next);
            return true;
          }
        } else if (id == 0xaddc11ef) {
          IWindow* next = mLayout->FindWindowByID(0x5415e48, true);
          if (next) {
            WindowManager()->SetFocusWindow(0, next);
            return true;
          }
          next = mLayout->FindWindowByID(0xc7ceb1bd, true);
          if (next) {
            WindowManager()->SetFocusWindow(0, next);
            return true;
          }
        } else if (id == 0x5415e48) {
          IWindow* next = mLayout->FindWindowByID(0xc7ceb1bd, true);
          if (next) {
            WindowManager()->SetFocusWindow(0, next);
            return true;
          }
        }
      }
      break;
    }
  }
  return false;
}

// @ 0x005C0320
void cSPEditorNaming::SetPrompt(const wchar_t* prompt) {
  mNamePrompt.assign(prompt, prompt + eastl::CharStrlen(prompt));
  IWindow* window = mLayout->FindWindowByID(0xc7ceb1bd, true);
  if (window)
    SetDisplayText(window->GetCaption());
}

// @ 0x005C0380
void cSPEditorNaming::SetExpanded(bool expanded) {
  if (mIsExpanded != expanded) {
    mIsExpanded = expanded;
    if (expanded) {
      IWindow* window = mLayout->FindWindowByID(0x272eb68e, true);
      if (window)
        ((EA::UTFWin::IButtonDrawable*)window->Cast(0x8ed27e7a))->SetImageState(4, true);
      window = mLayout->FindWindowByID(0x453ef531, true);
      if (window)
        ((EA::UTFWin::IButtonDrawable*)window->Cast(0x8ed27e7a))->SetImageState(4, true);
      if (mAllowNameEdit) {
        IWindow* nameWindow = mLayout->FindWindowByID(0xc7ceb1bd, true);
        if (nameWindow) {
          nameWindow->SetFlag(1, true);
          EA::UTFWin::ITextEdit* edit = (EA::UTFWin::ITextEdit*)nameWindow->Cast(0xcf428691);
          edit->SetSelection(wcslen(nameWindow->GetCaption()), 0);
          edit->SelectAll();
          WindowManager()->SetFocusWindow(0, nameWindow);
        }
        window = mLayout->FindWindowByID(0xd0e6d04b, true);
        if (window)
          window->SetFlag(1, false);
      }
      window = mLayout->FindWindowByID(0xaddc11ef, true);
      if (window)
        window->SetFlag(2, true);
      window = mLayout->FindWindowByID(0x5415e48, true);
      if (window)
        window->SetFlag(2, true);
      window = mLayout->FindWindowByID(0x552c901, true);
      if (window && mNameType) {
        window->SetFlag(1, true);
        window->SetFlag(2, true);
      }
      PlayUISound(0x6871e3b9, 0x46adfee);
      MessageServer()->PostMSG(0x716d445, 0, 0);
    } else {
      IWindow* window = mLayout->FindWindowByID(0x272eb68e, true);
      if (window)
        ((EA::UTFWin::IButtonDrawable*)window->Cast(0x8ed27e7a))->SetImageState(4, false);
      window = mLayout->FindWindowByID(0x453ef531, true);
      if (window)
        ((EA::UTFWin::IButtonDrawable*)window->Cast(0x8ed27e7a))->SetImageState(4, false);
      if (mAllowNameEdit) {
        IWindow* nameWindow = mLayout->FindWindowByID(0xc7ceb1bd, true);
        if (nameWindow)
          nameWindow->SetFlag(1, false);
        eastl::wstring name(nameWindow->GetCaption());
        name.trim();
        if (name.empty()) {
          SetDisplayText(mpDataProvider->GetName());
        } else {
          SetDisplayText(name.c_str());
          mpDataProvider->SetName(name.c_str());
        }
        window = mLayout->FindWindowByID(0xd0e6d04b, true);
        if (window)
          window->SetFlag(1, true);
      }
      window = mLayout->FindWindowByID(0xaddc11ef, true);
      if (window) {
        mpDataProvider->SetTag(window->GetCaption());
        window->SetFlag(2, false);
      }
      window = mLayout->FindWindowByID(0x5415e48, true);
      if (window) {
        mpDataProvider->SetDescription(window->GetCaption());
        window->SetFlag(2, false);
      }
      window = mLayout->FindWindowByID(0x552c901, true);
      if (window) {
        window->SetFlag(1, false);
        window->SetFlag(2, false);
      }
      PlayUISound(0x6871e3b9, 0x46adfee);
      MessageServer()->PostMSG(0x716d446, 0, 0);
    }
  }
}

class cSPPaletteCategoryUI {
 public:
  PV(0) PV(1)
  virtual int AddRef();
  virtual int Release();
  void CyclePage(int direction);
  bool IsPageVisible(int page);  // FUN_005c29c0
  char pad04[0x88 - 4];
  struct Page { uint32_t a, b; }* mPagesBegin;  // +0x88
  Page* mPagesEnd;                               // +0x8c
  char pad90[0xa0 - 0x90];
  int mCurrentPage;                              // +0xa0
};

class cSPEditorPageControls : public EA::UTFWin::IWinProc, public EA::Messaging::IHandler, public EA::RefCountVTemplate<int> {
 public:
  EA::AutoRefCount<cSPUILayout> mLayout;                   // +0x10
  EA::AutoRefCount<cSPPaletteCategoryUI> mCategoryUI;      // +0x14
  EA::AutoRefCount<IWindow> mWinPageNumberText;            // +0x18
  EA::AutoRefCount<IWindow> mWinRoot;                      // +0x1c
  int mCurrentPage;                                        // +0x20
  int mPageCount;                                          // +0x24

  cSPEditorPageControls();
  ~cSPEditorPageControls();
  virtual int AddRef();
  virtual int Release();
  void Init(IWindow* parent, cSPPaletteCategoryUI* categoryUI);
  void Shutdown();
  bool HandleUIMessage(IWindow* window, const void* message);
  void Update(float deltaTime);
};

// @ 0x005C0770
cSPEditorPageControls::cSPEditorPageControls() : mCurrentPage(-1), mPageCount(-1) {}

// @ 0x005C07D0
cSPEditorPageControls::~cSPEditorPageControls() {}

// @ 0x005C0840
void cSPEditorPageControls::Init(IWindow* parent, cSPPaletteCategoryUI* categoryUI) {
  if (parent && categoryUI) {
    mLayout = new ("Editor", 0, 0, 0, 0) cSPUILayout();
    mLayout->Init(EA::ResourceMan::Key(0xb0039d21, 0x510a95b, 0x40464100), true, 0x5b598fa);
    mLayout->SetParentWin(parent, true, 0x5b598fa);
    mWinRoot = mLayout->FindWindowByID(0xffffffff, true);
    if (mWinRoot)
      mWinRoot->AddWinProc(this);
    mCategoryUI = categoryUI;
    mWinPageNumberText = mLayout->FindWindowByID(0x734afa63, true);
  }
}

// @ 0x005C0990
void cSPEditorPageControls::Shutdown() {
  if (mWinRoot) {
    mWinRoot->RemoveWinProc(this);
    mWinRoot = 0;
  }
  if (mLayout) {
    mLayout->Shutdown(true);
    mLayout = 0;
  }
  mCategoryUI = 0;
  mWinPageNumberText = 0;
}

// @ 0x005C0A00
bool cSPEditorPageControls::HandleUIMessage(IWindow* window, const void* message) {
  const UIMessage* msg = (const UIMessage*)message;
  if (msg->mType == 0x287259f6) {
    switch ((uint32_t)msg->mParam1) {
      case 0x92df6fd6:
        mCategoryUI->CyclePage(1);
        break;
      case 0x92df6fd7:
        mCategoryUI->CyclePage(-1);
        break;
    }
  }
  return false;
}

// @ 0x005C0A60
void cSPEditorPageControls::Update(float deltaTime) {
  if (mCategoryUI && mWinPageNumberText) {
    int numPages = (int)(mCategoryUI->mPagesEnd - mCategoryUI->mPagesBegin);
    int visiblePages = 0;
    int currentPage = 0;
    for (int i = 0; i < numPages; i++) {
      if (mCategoryUI->IsPageVisible(i)) {
        if (i == mCategoryUI->mCurrentPage)
          currentPage = visiblePages;
        visiblePages++;
      }
    }
    if (visiblePages < 2) {
      if (mWinRoot)
        mWinRoot->SetFlag(1, false);
      return;
    }
    if (mWinRoot)
      mWinRoot->SetFlag(1, true);
    if (mCurrentPage != currentPage || mPageCount != visiblePages) {
      eastl::wstring text;
      text.sprintf(L"%i/%i", currentPage + 1, visiblePages);
      mWinPageNumberText->SetCaption(text.c_str());
      mCurrentPage = currentPage;
      mPageCount = visiblePages;
    }
  }
}

namespace SPUIHelpers {
void SetWindowImage(IWindow* window, const EA::ResourceMan::Key* key, int flags);
}

class cSPEditorPaintLikeThis {
 public:
  char pad00[0x94];
  EA::ResourceMan::Key mDefaultKey;  // +0x94
  char padA0[0xb4 - 0xa0];
  IWindow* mWinRoot;                 // +0xb4
  void SetImage(EA::ResourceMan::Key key);
};

// @ 0x005C0BA0
void cSPEditorPaintLikeThis::SetImage(EA::ResourceMan::Key key) {
  key.mType = 0x2f7d0004;
  if (key.mInstance == 0)
    SPUIHelpers::SetWindowImage(mWinRoot, &mDefaultKey, -1);
  else
    SPUIHelpers::SetWindowImage(mWinRoot, &key, -1);
  if (mWinRoot)
    mWinRoot->SetFlag(1, true);
}
}  // namespace SP
