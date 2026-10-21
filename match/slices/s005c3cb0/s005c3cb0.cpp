// Slice s005c3cb0 -- SP::cSPPaletteCategoryUI methods (Spore UI), part 3
// Flags for this region: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc)
#include <new>
#include "types.h"

#define PV(n) virtual void pv##n();

extern "C" void EASTL_allocator_deallocate(void* p);  // 0x00f47380
void* __cdecl EASTL_allocator_allocate(unsigned sz, const char* name, int a, int b, const char* file, int line);  // 0x00f473a0

struct ChildLink { ChildLink* mpNext; };
struct ChildIter { ChildLink* mpLink; };

namespace EA {
template <typename T>
class AutoRefCount {
 public:
  T* mpObject;
  AutoRefCount() : mpObject(0) {}
  ~AutoRefCount() { if (mpObject) mpObject->Release(); }
};

// AutoRefCount with operator= (the PageUIEntry / PaintLikeThis element type)
template <typename T>
class AutoRefPtr {
 public:
  T* mpObject;
  __forceinline AutoRefPtr(const AutoRefPtr& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefPtr() { if (mpObject) mpObject->Release(); }
};

namespace Messaging {
class Server;
class IHandler;
void RemoveHandler(Server* server, IHandler* handler, const uint32_t* ids, uint32_t count, int priority);  // 0x00571db0 (cdecl)
class AutoHandler { public:
  Server* mpServer;
  IHandler* mpHandler;
  const uint32_t* mpIdArray;
  uint32_t mnIdArrayCount;
  int mnPriority;
  AutoHandler() : mpServer(0), mpHandler(0), mpIdArray(0), mnIdArrayCount(0), mnPriority(0) {}
  ~AutoHandler() {
    if (mpServer) {
      Server* const pServer = mpServer;
      mpServer = 0;
      RemoveHandler(pServer, mpHandler, mpIdArray, mnIdArrayCount, mnPriority);
    }
  }
};
}  // namespace Messaging

namespace Audio {
class IAudioSystem {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
  virtual uint32_t GetState();  // +0x20
};
IAudioSystem* GetSystemAT();  // 0x00a206f0
}  // namespace Audio

namespace UTFWin {
class IWindow;
class Message { public:
  IWindow* mpSource;  // +0x0
  uint32_t pad4;
  uint32_t mType;     // +0x8
  uint32_t mID;       // +0xc
};
class IWindow {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual uint32_t GetCommandID();  // +0x1c (slot 7)
  virtual uint32_t GetControlID();  // +0x20 (slot 8)
  PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20)
  PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30) PV(31) PV(32)
  PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44)
  PV(45) PV(46) PV(47) PV(48) PV(49) PV(50)
  virtual void GetChildBegin(ChildIter* result);       // +0xcc (slot 51)
  virtual ChildIter* GetChildEnd(ChildIter* result);  // +0xd0 (slot 52)
};
}  // namespace UTFWin
}  // namespace EA

using EA::UTFWin::IWindow;
using EA::UTFWin::Message;

extern int gChildLinkOffset;  // 0x01440aec
class IWindowQI {
 public:
  PV(0) PV(1) PV(2)
  virtual IWindow* QueryInterface(uint32_t iid);  // +0x0c
};

// ---------------------------------------------------------------- the PageUIEntry vector helpers
namespace SP {
class cSPPalettePageUI {
 public:
  virtual int AddRef();
  virtual int Release();
  uint32_t GetPackID();  // FUN_005c8fc0
};
class cSPEditorPaintLikeThisBase { public: virtual void v0(); int mA, mB; };
class cSPEditorPaintLikeThisRef {
 public:
  virtual int AddRef();
  virtual int Release();
};
class cSPEditorPaintLikeThis : public cSPEditorPaintLikeThisBase, public cSPEditorPaintLikeThisRef {};

struct PageUIEntry {
  EA::AutoRefPtr<cSPPalettePageUI> mpPageUI;  // +0x0
  bool mVisible;                              // +0x4
  bool mShown;                                // +0x5
  bool mDisabled;                             // +0x6
  __forceinline PageUIEntry(const PageUIEntry& x)
      : mpPageUI(x.mpPageUI), mVisible(x.mVisible), mShown(x.mShown), mDisabled(x.mDisabled) {}
};
struct PageUIEntryAssign : PageUIEntry {
  PageUIEntryAssign& operator=(const PageUIEntryAssign& x);  // 0x005c35c0
};
typedef EA::AutoRefPtr<cSPEditorPaintLikeThis> PaintLikeThisRef;

template <typename T>
struct copy_impl_do {
  static T* do_copy(T* first, T* last, T* result);
};
template <typename T>
inline T* copy(T* first, T* last, T* result) {
  return copy_impl_do<T>::do_copy(first, last, result);
}
// copy_impl_do<PaintLikeThisRef>::do_copy = 0x005c2f40, copy_impl_do<PageUIEntry>::do_copy = 0x005c3610
PageUIEntry* copy_backward(PageUIEntry* first, PageUIEntry* last, PageUIEntry* resultEnd);           // 0x005c3680
PageUIEntry* uninitialized_copy_ptr(PageUIEntry* first, PageUIEntry* last, PageUIEntry* result);     // 0x005c2ef0
PageUIEntry* destroy_range(PageUIEntry* first, PageUIEntry* last, PageUIEntry* result);              // 0x00f9ae40 (cdecl)

template <typename T>
inline void destruct(T* first, T* last) {
  for (; first < last; ++first)
    first->~T();
}

__forceinline PageUIEntry* uninitialized_move_ptr(PageUIEntry* first, PageUIEntry* last, PageUIEntry* result) {
  PageUIEntry* const end = SP::uninitialized_copy_ptr(first, last, result);
  SP::destroy_range(first, last, result);
  return end;
}

class PaintLikeThisVec {
 public:
  PaintLikeThisRef* mpBegin;
  PaintLikeThisRef* mpEnd;
  PaintLikeThisRef* mpCapacity;
  PaintLikeThisRef* erase(PaintLikeThisRef* first, PaintLikeThisRef* last);
};

// @ 0x005C41B0  vector<AutoRefCount<cSPEditorPaintLikeThis>, sp_vector_allocator>::erase
PaintLikeThisRef* PaintLikeThisVec::erase(PaintLikeThisRef* first, PaintLikeThisRef* last) {
  PaintLikeThisRef* const position = SP::copy(last, mpEnd, first);
  destruct(position, mpEnd);
  mpEnd -= (last - first);
  return first;
}

class PageUIVec {
 public:
  PageUIEntry* mpBegin;
  PageUIEntry* mpEnd;
  PageUIEntry* mpCapacity;
  int mAllocator[2];
  PageUIEntry* erase(PageUIEntry* first, PageUIEntry* last);
  void insert(PageUIEntry* position, const PageUIEntry& value);
};

// @ 0x005C4330
PageUIEntry* PageUIVec::erase(PageUIEntry* first, PageUIEntry* last) {
  PageUIEntry* const position = SP::copy(last, mpEnd, first);
  destruct(position, mpEnd);
  mpEnd -= (last - first);
  return first;
}

// @ 0x005C4390
void PageUIVec::insert(PageUIEntry* position, const PageUIEntry& value) {
  if (mpEnd != mpCapacity) {
    const PageUIEntry* pValue = &value;
    if (pValue >= position && pValue < mpEnd)
      ++pValue;
    if (mpEnd)
      ::new (mpEnd) PageUIEntry(mpEnd[-1]);
    SP::copy_backward(position, mpEnd - 1, mpEnd);
    *(PageUIEntryAssign*)position = *(const PageUIEntryAssign*)pValue;
    ++mpEnd;
    return;
  }
  unsigned int prevSize = (unsigned int)(mpEnd - mpBegin);
  unsigned int newSize = (prevSize > 0) ? prevSize * 2 : 1;
  PageUIEntry* newData = newSize ? (PageUIEntry*)EASTL_allocator_allocate(
                                       newSize * sizeof(PageUIEntry), "Editor", 0, 0,
                                       "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                                       0xd1)
                                 : 0;
  PageUIEntry* newPosition = uninitialized_move_ptr(mpBegin, position, newData);
  if (newPosition)
    ::new (newPosition) PageUIEntry(value);
  PageUIEntry* newEnd = uninitialized_move_ptr(position, mpEnd, newPosition + 1);
  if (mpBegin && ((int*)mpBegin)[-1] != 0)
    EASTL_allocator_deallocate(mpBegin);
  mpBegin = newData;
  mpEnd = newEnd;
  mpCapacity = newData + newSize;
}
}  // namespace SP

// ---------------------------------------------------------------- cSPPaletteCategoryUI
namespace EA {
template <typename T>
class RefCountVTemplate {
 public:
  RefCountVTemplate() : mRefCount(0) {}
  virtual ~RefCountVTemplate() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}  // namespace EA

namespace SP {
class IHandlerRC {
 public:
  ~IHandlerRC() {}
  virtual bool HandleMessage(uint32_t messageID, void* message);
};
class IWinProc {
 public:
  ~IWinProc() {}
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3)
  virtual bool HandleUIMessage(EA::UTFWin::IWindow* window, const EA::UTFWin::Message& msg);
};

// objects released through RefCountVTemplate (Release at slot 2, +8) and through IUnknown32-style
// (Release at slot 1, +4)
class cRefA { public: virtual ~cRefA(); virtual int AddRef(); virtual int Release(); };
class cRefB { public: virtual int AddRef(); virtual int Release(); };

class cSPUILayout : public cRefA {};
class cSPEditorColorPicker : public cRefA {};
class cSPPaletteCategory : public cRefA {};
class cSPSwatch : public cRefB {};
class cSPEditorPageControls : public cRefB {};
class cSPPaletteSubCategoryUI : public cRefB {};
class IWinButton : public cRefB {
 public:
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual void SetState(int state, bool value);  // +0x28
};

struct cSPColorRGB {
  float r, g, b;
  cSPColorRGB() {}
  cSPColorRGB(const cSPColorRGB& c) : r(c.r), g(c.g), b(c.b) {}
};
extern cSPColorRGB kSwatchColor;  // 0x01514eb8

class cRefVector {
 public:
  void** mpBegin;
  void** mpEnd;
  void** mpCapacity;
  int mAllocator[2];
  cRefVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~cRefVector();  // 0x005c8fd0
};

class IWindowPtrVec {
 public:
  IWindow** mpBegin;
  IWindow** mpEnd;
  IWindow** mpCapacity;
  int mAllocator[2];
  void Grow(IWindow** position, IWindow* const& value);  // 0x00630b30 (DoInsertValue)
  void push_back(IWindow* value) {
    if (mpEnd < mpCapacity)
      ::new (mpEnd++) IWindow*(value);
    else
      Grow(mpEnd, value);
  }
};

class ButtonVec {  // vector<IWinButton*>
 public:
  IWinButton** mpBegin;
  IWinButton** mpEnd;
  IWinButton** mpCapacity;
  int mAllocator[2];
  ButtonVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~ButtonVec();  // 0x00ae6970
  unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
  bool NotEmpty() const { return size() > 0; }
  IWinButton*& operator[](unsigned int i) { return mpBegin[i]; }
};

class PageUIVecOwner : public PageUIVec {
 public:
  PageUIVecOwner() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; }
  ~PageUIVecOwner();  // 0x005c3dc0
};

void KillSeti(int id);                                  // 0x004a88d0 (cdecl)
namespace cSPUISpace { void KillSetiEffects(uint32_t id, uint32_t state); }  // 0x00435ed0 (cdecl)

class cSPPaletteCategoryUI : public IHandlerRC, public IWinProc, public EA::RefCountVTemplate<int> {
 public:
  EA::AutoRefCount<cSPUILayout> mLayout;                    // +0x10
  EA::AutoRefCount<cSPUILayout> mExpansionPackLayout;       // +0x14
  EA::AutoRefCount<cRefB> mWinCategory;                     // +0x18
  EA::AutoRefCount<cRefB> mWinPageButtons;                  // +0x1c
  EA::AutoRefCount<cRefB> mWinEPUIHolder;                   // +0x20
  EA::AutoRefCount<cRefB> mWinColorPickerHolder;            // +0x24
  EA::AutoRefCount<cRefB> mWinPalettePage;                  // +0x28
  EA::AutoRefCount<cRefB> mWinFullPalettePage;              // +0x2c
  EA::AutoRefCount<cSPEditorColorPicker> mColorPicker1;     // +0x30
  EA::AutoRefCount<cSPEditorColorPicker> mColorPicker2;     // +0x34
  float mRects[(0x68 - 0x38) / 4];                                // +0x38 (uninitialised by the ctor)
  EA::AutoRefCount<cSPSwatch> mPreviewSwatch;               // +0x68
  EA::AutoRefCount<cSPPaletteCategory> mData;               // +0x6c
  EA::AutoRefCount<cSPEditorPageControls> mPageControls;    // +0x70
  ButtonVec mPackButtons;                                   // +0x74
  PageUIVecOwner mPageUIs;                                  // +0x88
  EA::AutoRefCount<cSPPaletteSubCategoryUI> mSubCategoryUI; // +0x9c
  int mCurrentPageIndex;                                    // +0xa0
  int mFilterSetId;                                         // +0xa4
  int mExpansionPackChunkIndex;                             // +0xa8
  uint32_t mCurrentPackID;                                  // +0xac
  int mExpansionPacksPerPage;                               // +0xb0
  EA::Messaging::AutoHandler mAutoMsgHandler;               // +0xb4
  uint32_t mSelectedItemID;                                 // +0xc8
  cSPColorRGB mSelectedColor1;                              // +0xcc
  cSPColorRGB mSelectedColor2;                              // +0xd8
  bool mIsColor1Default;                                    // +0xe4
  bool mIsColor2Default;                                    // +0xe5
  cRefVector mPaintLikeThisWidgets;                         // +0xe8

  cSPPaletteCategoryUI();
  virtual ~cSPPaletteCategoryUI();
  virtual bool HandleUIMessage(EA::UTFWin::IWindow* window, const EA::UTFWin::Message& msg);

  void SetVisibleChunk(int chunkIndex);                    // 0x005c2590
  int GetPageIndexForPackID(uint32_t packID);              // 0x005c29e0
  int GetChunkIndexForPackID(uint32_t packID);             // 0x005c2a30
  cSPPalettePageUI* GetPageUI(int index);                  // 0x005c2e50
  bool SetPageIndex(int index);                            // 0x005c3bd0
  void SetSelectedPack(uint32_t packID);
  void GetWindowsWithMatchingID(EA::UTFWin::IWindow* window, uint32_t id, IWindowPtrVec* out);
};

// @ 0x005C3CB0
void cSPPaletteCategoryUI::SetSelectedPack(uint32_t packID) {
  const uint32_t oldPack = mCurrentPackID;
  const int oldIndex = GetChunkIndexForPackID(oldPack);
  const int newIndex = GetChunkIndexForPackID(packID);
  mCurrentPackID = packID;
  if (newIndex >= 0 && newIndex < (int)mPackButtons.size()) {
    if (mPackButtons.NotEmpty()) {
      if (oldIndex != -1)
        mPackButtons[oldIndex]->SetState(4, false);
      mPackButtons[newIndex]->SetState(4, true);
    }
    if (oldPack != mCurrentPackID) {
      SetVisibleChunk(newIndex / mExpansionPacksPerPage);
      KillSeti(0x38eb66f8);
      const uint32_t current = mCurrentPackID;
      if (GetPageUI(mCurrentPageIndex)->GetPackID() != current)
        SetPageIndex(GetPageIndexForPackID(current));
    }
  }
}

// @ 0x005C40B0  IWinProc::HandleUIMessage override
bool cSPPaletteCategoryUI::HandleUIMessage(EA::UTFWin::IWindow* window, const EA::UTFWin::Message& msg) {
  if (msg.mType == 0x287259f6) {
    if (msg.mID == 0x5d1ad44) {
      int numChunks = (int)((mPackButtons.size() + mExpansionPacksPerPage - 1) / mExpansionPacksPerPage);
      SetVisibleChunk((mExpansionPackChunkIndex - 1 + numChunks) % numChunks);
      return true;
    }
    if (msg.mID == 0x5d1ad3f) {
      int numChunks = (int)((mPackButtons.size() + mExpansionPacksPerPage - 1) / mExpansionPacksPerPage);
      SetVisibleChunk((mExpansionPackChunkIndex + 1) % numChunks);
      return true;
    }
    EA::Audio::IAudioSystem* audio = EA::Audio::GetSystemAT();
    cSPUISpace::KillSetiEffects(0x38eb66f8, audio ? audio->GetState() : 0);
    SetSelectedPack(msg.mpSource->GetControlID());
    return true;
  }
  return false;
}

// @ 0x005C3E00
cSPPaletteCategoryUI::cSPPaletteCategoryUI()
    : mCurrentPageIndex(0), mFilterSetId(0), mExpansionPackChunkIndex(0), mCurrentPackID(0),
      mExpansionPacksPerPage(6), mSelectedItemID(0), mSelectedColor1(kSwatchColor),
      mSelectedColor2(kSwatchColor), mIsColor1Default(true), mIsColor2Default(true) {}

// @ 0x005C3F60
cSPPaletteCategoryUI::~cSPPaletteCategoryUI() {}

// @ 0x005C4210
void cSPPaletteCategoryUI::GetWindowsWithMatchingID(EA::UTFWin::IWindow* window, uint32_t id, IWindowPtrVec* out) {
  if (window) {
    ChildIter it, tmp;
    window->GetChildBegin(&it);
    if (it.mpLink != window->GetChildEnd(&tmp)->mpLink) {
      do {
        IWindowQI* node = (IWindowQI*)((char*)it.mpLink + gChildLinkOffset);
        IWindow* child = node ? node->QueryInterface(0xeeee8218) : 0;
        if (child->GetCommandID() == id)
          out->push_back(child);
        GetWindowsWithMatchingID(child, id, out);
        it.mpLink = it.mpLink->mpNext;
      } while (it.mpLink != window->GetChildEnd(&tmp)->mpLink);
    }
  }
}
}  // namespace SP
