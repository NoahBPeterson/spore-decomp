// src/game/SPEditors/SPEditorPageControls.cpp -- migrated from slice(s) s005bfb90 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorPageControls.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Messaging/IHandler.h"
#include "EA/Messaging/Server.h"
#include "EA/UTFWin/IWinProc.h"
#include "EA/UTFWin/IWindow.h"
#include "EA/ResourceMan/Key.h"
#include "SP/cISPEditorNameProvider.h"
#include "SP/cSPEditorNaming.h"
#include "SP/cSPEditorPageControls.h"
#include "SP/cSPEditorPaintLikeThis.h"
#include "SP/cSPNameGuard.h"
#include "SP/cSPPaletteCategoryUI.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
#include <new>
#include <string.h>
#include "cSPUILayout.h"

// ---- items of slice s005bfb90 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
#define PV(n) virtual void pv##n();
namespace eastl {
extern wchar_t gEmptyString[2];
}
namespace eastl {
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
}
namespace EA {
template <typename T>
class AutoRefCount_s005b_fb90 {
 public:
  T* mpObject;
  AutoRefCount_s005b_fb90() : mpObject(0) {}
  ~AutoRefCount_s005b_fb90() { if (mpObject) mpObject->Release(); }
  AutoRefCount_s005b_fb90& operator=(T* pObject) {
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
}
namespace EA {
template <typename T>
class RefCountVTemplate_s005b_fb90 {
 public:
  RefCountVTemplate_s005b_fb90() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s005b_fb90() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace EA {
namespace ResourceMan {
struct Key_s005b_fb90 {
  unsigned int mInstance, mType, mGroup;
  Key_s005b_fb90(unsigned int i, unsigned int t, unsigned int g) : mInstance(i), mType(t), mGroup(g) {}
};
}
}
namespace EA {
namespace UTFWin {
class IWinProc_s005b_fb90;
}
}
namespace EA {
namespace UTFWin {
class IWindow_s005b_fb90 {
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
  virtual IWindow_s005b_fb90* GetDrawable();                       // +0xa8
  PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58)
  PV(59) PV(60) PV(61) PV(62) PV(63) PV(64)
  virtual void AddWinProc(IWinProc_s005b_fb90* proc);              // +0x104
  virtual void RemoveWinProc(IWinProc_s005b_fb90* proc);           // +0x108
};
}
}
namespace EA {
namespace UTFWin {
class IWinProc_s005b_fb90 {
 public:
  ~IWinProc_s005b_fb90() {}
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4)
  virtual bool HandleUIMessage(IWindow_s005b_fb90* window, const void* message);  // +0x14
  PV(6)
};
}
}
namespace EA {
namespace Messaging {
class IHandler_s005b_fb90 {
 public:
  IHandler_s005b_fb90() {}
  ~IHandler_s005b_fb90() {}
  virtual bool HandleMessage(uint32_t messageID, void* message);
};
}
}
using EA::UTFWin::IWindow_s005b_fb90;
class cSPUILayout_s005b_fb90 {
 public:
  PV(0)
  virtual int AddRef();
  virtual int Release();
  cSPUILayout_s005b_fb90();
  IWindow_s005b_fb90* FindWindowByID(uint32_t id, bool recursive);  // 0x008105b0 (cSPUILayout::FindWindowByID)
  bool Init(const EA::ResourceMan::Key_s005b_fb90& key, bool b, uint32_t id);  // 0x008120d0 (cSPUILayout::Init)
  void SetParentWin(IWindow_s005b_fb90* parent, bool b, uint32_t id);  // 0x008121b0 (cSPUILayout::SetParentWin)
  void Shutdown(bool b);  // 0x00811ad0 (cSPUILayout::Shutdown)
  char pad[0x18 - 4];
};
namespace SP {
struct UIMessage {
  uint32_t pad0;
  IWindow_s005b_fb90* mpSource;   // +0x4
  int mType;           // +0x8
  int mParam1;         // +0xc
  int mParam2;         // +0x10
  int mParam3;         // +0x14
};
}
namespace SP {
class cSPPaletteCategoryUI_s005b_fb90 {
 public:
  PV(0) PV(1)
  virtual int AddRef();
  virtual int Release();
  void CyclePage(int direction);  // 0x005c3c20 (SP::cSPPaletteCategoryUI::CyclePage)
  bool IsPageVisible(int page);  // FUN_005c29c0
  char pad04[0x88 - 4];
  struct Page { uint32_t a, b; }* mPagesBegin;  // +0x88
  Page* mPagesEnd;                               // +0x8c
  char pad90[0xa0 - 0x90];
  int mCurrentPage;                              // +0xa0
};
}
namespace SP {
class cSPEditorPageControls_s005b_fb90 : public EA::UTFWin::IWinProc_s005b_fb90, public EA::Messaging::IHandler_s005b_fb90, public EA::RefCountVTemplate_s005b_fb90<int> {
 public:
  EA::AutoRefCount_s005b_fb90<cSPUILayout_s005b_fb90> mLayout;                   // +0x10
  EA::AutoRefCount_s005b_fb90<cSPPaletteCategoryUI_s005b_fb90> mCategoryUI;      // +0x14
  EA::AutoRefCount_s005b_fb90<IWindow_s005b_fb90> mWinPageNumberText;            // +0x18
  EA::AutoRefCount_s005b_fb90<IWindow_s005b_fb90> mWinRoot;                      // +0x1c
  int mCurrentPage;                                        // +0x20
  int mPageCount;                                          // +0x24

  cSPEditorPageControls_s005b_fb90();
  ~cSPEditorPageControls_s005b_fb90();
  virtual int AddRef();
  virtual int Release();
  void Init(IWindow_s005b_fb90* parent, cSPPaletteCategoryUI_s005b_fb90* categoryUI);  // 0x005c0840 (SP::cSPEditorPageControls::Init)
  void Shutdown();  // 0x005c0990 (SP::cSPEditorPageControls::Shutdown)
  bool HandleUIMessage(IWindow_s005b_fb90* window, const void* message);
  void Update(float deltaTime);  // 0x005c0a60 (SP::cSPEditorPageControls::Update)
};
}
// ---- items of slice s005bfb90 end

// @ 0x005c0770
namespace SP {
cSPEditorPageControls_s005b_fb90::cSPEditorPageControls_s005b_fb90()
: mCurrentPage(-1), mPageCount(-1) {}
}  // namespace SP

// @ 0x005c07d0
namespace SP {
cSPEditorPageControls_s005b_fb90::~cSPEditorPageControls_s005b_fb90()
{}
}  // namespace SP

// @ 0x005c0840
namespace SP {
void cSPEditorPageControls_s005b_fb90::Init(IWindow_s005b_fb90* parent, cSPPaletteCategoryUI_s005b_fb90* categoryUI)
{
  if (parent && categoryUI) {
    mLayout = new ("Editor", 0, 0, 0, 0) cSPUILayout_s005b_fb90();
    mLayout->Init(EA::ResourceMan::Key_s005b_fb90(0xb0039d21, 0x510a95b, 0x40464100), true, 0x5b598fa);
    mLayout->SetParentWin(parent, true, 0x5b598fa);
    mWinRoot = mLayout->FindWindowByID(0xffffffff, true);
    if (mWinRoot)
      mWinRoot->AddWinProc(this);
    mCategoryUI = categoryUI;
    mWinPageNumberText = mLayout->FindWindowByID(0x734afa63, true);
  }
}
}  // namespace SP

// @ 0x005c0990
namespace SP {
void cSPEditorPageControls_s005b_fb90::Shutdown()
{
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
}  // namespace SP

// @ 0x005c0a00
namespace SP {
bool cSPEditorPageControls_s005b_fb90::HandleUIMessage(IWindow_s005b_fb90* window, const void* message)
{
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
}  // namespace SP

// @ 0x005c0a60
namespace SP {
void cSPEditorPageControls_s005b_fb90::Update(float deltaTime)
{
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
}  // namespace SP
