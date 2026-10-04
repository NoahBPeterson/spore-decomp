// slice s005cb060 -- SP::cSPPaletteUI (Init/Shutdown, category selection, expand state, DoMessage,
// ctor/dtor), SP::EditorCommandHandler, a buffered stream object (0x5cbca0-0x5cbf00) and a
// rollover property-layout constructor.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include <new>
#include <string.h>
#include "types.h"

extern "C" void EASTL_allocator_deallocate(void* p);  // 0x00f47380
void* operator new(unsigned int n, const char* name, int flags, unsigned int debugFlags, const char* file,
                   int line);  // 0x00f473a0

#define PV(n) virtual void pv##n();

namespace EA {
template <typename T>
class AutoRefCount {
 public:
  T* mpObject;
  AutoRefCount() : mpObject(0) {}
  AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount() { if (mpObject) mpObject->Release(); }
  AutoRefCount& operator=(T* p) {
    if (p != mpObject) {
      T* const pTemp = mpObject;
      if (p)
        p->AddRef();
      mpObject = p;
      if (pTemp)
        pTemp->Release();
    }
    return *this;
  }
  T*& AsOutParam() {
    if (mpObject) {
      T* const p = mpObject;
      mpObject = 0;
      p->Release();
    }
    return mpObject;
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

namespace COM {
class IUnknown32 {
 public:
  ~IUnknown32() {}
  virtual int AddRef() = 0;
  virtual int Release() = 0;
  virtual int GetTypeID() const;
  virtual void* Cast(uint32_t typeID) const = 0;  // +0xc
};
}  // namespace COM

namespace ResourceMan {
struct Key {
  unsigned int mInstance, mType, mGroup;
  Key() {}
  Key(unsigned int instance, unsigned int type, unsigned int group)
      : mInstance(instance), mType(type), mGroup(group) {}
};
}

struct Vector2 {
  float x, y;
  Vector2() {}
  Vector2(float x_, float y_) : x(x_), y(y_) {}
  Vector2(const Vector2& v) : x(v.x), y(v.y) {}
};
struct Vector3 {
  float x, y, z;
  Vector3() {}
  Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};

namespace UTFWin {
class IWinProc;
class IWindow : public COM::IUnknown32 {
 public:
  virtual IWindow* GetParent();  // +0x10
  PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
  PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
  virtual void SetFlag(int flag, bool value);  // +0x7c
  PV(32) PV(33)
  virtual void Animate();                      // +0x88
  PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47)
  PV(48) PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58) PV(59) PV(60)
  PV(61) PV(62) PV(63) PV(64)
  virtual void AddWinProc(IWinProc* proc);     // +0x104
  virtual void RemoveWinProc(IWinProc* proc);  // +0x108
};

struct Message {
  uint32_t pad0[2];
  uint32_t mEventType;  // +0x8
  int mControlID;       // +0xc
};

class IWinProc : public COM::IUnknown32 {
 public:
  virtual int GetEventFlags();
  virtual bool DoMessage(IWindow* window, const Message& message) = 0;
};
}  // namespace UTFWin

namespace UTFWinControls {
class IWinButton : public COM::IUnknown32 {
 public:
  virtual UTFWin::IWindow* ToWindow();          // +0x10
  PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual void SetButtonStateFlag(int flag, bool value);  // +0x28
  PV(11) PV(12) PV(13) PV(14) PV(15) PV(16)
  virtual void SetCommandData(void* data);      // +0x44
};
}  // namespace UTFWinControls

namespace Messaging {
class IHandler;
class IMessageServer {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void MessageSend(uint32_t messageID, void* message, IHandler* handler);  // +0x14
};
}  // namespace Messaging

namespace Audio {
class IAudioSystem {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
  virtual int GetSystem();  // +0x20
};
IAudioSystem* GetSystemAT();  // 0x00a206f0
}  // namespace Audio
}  // namespace EA

using EA::AutoRefCount;
using EA::Vector2;
using EA::Vector3;
using EA::ResourceMan::Key;
using EA::UTFWin::IWindow;
using EA::UTFWin::IWinProc;
using EA::UTFWin::Message;
using EA::UTFWinControls::IWinButton;

namespace eastl {
template <typename T, int kAllocatorWords = 2>
class sp_vector {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  int mAllocator[kAllocatorWords];
  unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
  T& operator[](unsigned int i) { return mpBegin[i]; }
  T* DoInsertValue(T* position, const T& value);
  void push_back(const T& value) {
    if (mpEnd < mpCapacity)
      ::new (mpEnd++) T(value);
    else
      DoInsertValue(mpEnd, value);
  }
};

// vector<AutoRefCount<T>, sp_vector_allocator>: constructor inline, destructor/erase out of line
template <typename T>
class sp_ref_vector : public sp_vector<EA::AutoRefCount<T> > {
 public:
  typedef EA::AutoRefCount<T> value_type;
  sp_ref_vector() {
    this->mpBegin = 0;
    this->mpEnd = 0;
    this->mpCapacity = 0;
  }
  ~sp_ref_vector();
  value_type* erase(value_type* first, value_type* last);
  void clear() { erase(this->mpBegin, this->mpEnd); }
};
}  // namespace eastl

class cSPUILayout {
 public:
  cSPUILayout();                                                      // 0x00810000
  virtual ~cSPUILayout();
  virtual int AddRef();
  virtual int Release();
  bool Init(const Key& key, bool visible, uint32_t parentID);        // 0x008120d0
  void SetParentWin(IWindow* parent, bool visible, uint32_t parentID);  // 0x008121b0
  IWindow* FindWindowByID(uint32_t id, bool recursive);              // 0x008105b0
  void Shutdown(bool destroy);                                        // 0x00811ad0
  uint32_t mData[5];
};

class cCustomWindowBase {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
  PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
  PV(30) PV(31) PV(32) PV(33)
  virtual void StartAnimation();  // +0x88
};
class cSPUIAnimatedIconWin : public cCustomWindowBase, public IWindow {
 public:
  using cCustomWindowBase::StartAnimation;
};

namespace SPUIHelpers {
void AnchorWindowToWindow(IWindow* anchor, IWindow* window, uint32_t flags, int offset);  // 0x00807340
void SetWindowAreaToParent(IWindow* window);                                             // 0x00806bf0
IWinButton* CreateButtonFromKeys(Key* keys, int state, int index, Vector2 offset, IWindow* parent);  // 0x00808930
IWinButton* CreateButtonFromKey(Key* key, int state, int index, Vector2 offset, IWindow* parent);    // 0x00807a50
}

namespace UI {
class Tooltip {
 public:
  Tooltip(const wchar_t* table, uint32_t id, const wchar_t* text, const Vector2& offset, int a, const wchar_t* extra,
          int b);  // 0x00835e30
  virtual int AddRef();
  virtual int Release();
  uint32_t mData[0x68 / 4 - 1];
};
class IFadeEffect {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5)
  virtual void SetDuration(float seconds);  // +0x18
  PV(7)
  virtual void SetFadeIn(bool fadeIn);      // +0x20
};
class FadeEffect {
 public:
  FadeEffect();  // 0x0096f060
  virtual int AddRef();
  virtual int Release();
  uint32_t pad04[2];
  IFadeEffect mEffect;  // +0xc
  uint32_t mData[(0x60 - 0x10) / 4];
};
}  // namespace UI
void* GetUIAllocator();                                                     // 0x009512c0
void* operator new(unsigned int size, int align, const char* name, void* allocator);  // 0x009512d0

namespace SP {
EA::Messaging::IMessageServer* MessageServer();  // 0x0067dcc0
void PlayAudio(uint32_t id, int system);         // 0x00435ed0
void PlayUISound(uint32_t id);                   // 0x004a88d0
namespace EditorUtils {
void PlayEditorSound(uint32_t id, uint32_t param, float value, int flags);  // 0x00435f40
}
void SetGlobalProperty(uint32_t id, float value);  // 0x005ca880
extern float gCategoryToggle;                      // 0x015ed22c

class cString {
 public:
  const wchar_t* GetText();  // 0x006b55c0
  uint32_t pad[5];
};

class cSPPaletteCategory {
 public:
  uint32_t pad00[0x5c / 4];
  cString mCategoryName;          // +0x5c
  uint32_t pad70[3];
  Key mButtonImageKey;            // +0x7c
  Key* mpButtonImageKeys;         // +0x88
};

class cSPPalette : public EA::RefCountVTemplate<int>, public EA::COM::IUnknown32 {
 public:
  virtual int AddRef();
  virtual int Release();
  eastl::sp_vector<AutoRefCount<cSPPaletteCategory>, 1> mCategories;  // +0xc
  unsigned int mLayoutInstanceID;     // +0x1c
  unsigned int mImageGroupID;         // +0x20
  uint32_t pad24[5];
  int mStartupCategoryIndex;          // +0x38
  cSPPaletteCategory* GetCategory(int index);  // 0x005c5de0
};

class cSPPaletteInfo : public EA::RefCountVTemplate<int> {};

struct cCategoryInfo {
  cCategoryInfo() {}
  cCategoryInfo(int index, const Vector3& color, const Vector3& highlight)
      : mIndex(index), mColor(color), mHighlight(highlight) {}
  int mIndex;
  Vector3 mColor;
  Vector3 mHighlight;
};
extern const Vector3 kDefaultCategoryColor;  // 0x015168c0

class cSPPaletteCategoryUI {
 public:
  cSPPaletteCategoryUI();  // 0x005c3e00
  PV(0) PV(1)
  virtual int AddRef();   // +0x8
  virtual int Release();  // +0xc
  bool IsExpanded();                                                              // 0x005c2940
  void SetActive(bool active);                                                    // 0x005c2960
  cCategoryInfo* GetCategoryInfo(cCategoryInfo* result);                          // 0x005c2d30
  void Init(cSPPaletteCategory* category, IWindow* parent, cSPPaletteInfo* info);  // 0x005c53c0
  void Shutdown();                                                                // 0x005c4e40
  uint32_t mData[0xfc / 4 - 1];
};

class cSPPaletteUI : public IWinProc, public EA::RefCountVTemplate<int> {
 public:
  cSPPaletteUI();
  ~cSPPaletteUI();
  virtual int AddRef();
  virtual int Release();
  virtual void* Cast(uint32_t typeID) const;
  virtual bool DoMessage(IWindow* window, const Message& message);

  void Init(cSPPalette* palette, IWindow* parent, int unused, cSPPaletteInfo* info);
  void Shutdown();
  void SetCurrentCategoryIndex(int index);
  int GetCurrentCategoryIndex();     // 0x005ca9c0
  void SetVisibleChunk(int chunk);   // 0x005cadb0
  void LayoutCategoryButtons();      // 0x005cae60
  void SetExpanded(bool expanded);
  void SetVisible(bool visible);
  cCategoryInfo GetCategoryInfo();
  void ToggleExpanded();

  AutoRefCount<cSPUILayout> mLayout;                           // +0xc
  IWindow* mWinCategoryIcons;                                  // +0x10
  IWindow* mLeftBackground;                                    // +0x14
  IWindow* mRightBackground;                                   // +0x18
  IWindow* mFullBackground;                                    // +0x1c
  cSPUIAnimatedIconWin* mWinSelectedCategoryBackground;        // +0x20
  IWindow* mWinCategory;                                       // +0x24
  IWindow* mWinRoot;                                           // +0x28
  AutoRefCount<cSPPalette> mData;                              // +0x2c
  AutoRefCount<cSPPaletteInfo> mInfo;                          // +0x30
  eastl::sp_ref_vector<cSPPaletteCategoryUI> mCategoryUIs;     // +0x34
  eastl::sp_ref_vector<IWinButton> mCategoryButtons;           // +0x48
  int mSelectedSet;                                            // +0x5c
  int mCurrentCategoryChunk;                                   // +0x60
  cSPPaletteCategoryUI* mCurrentCategory;                      // +0x64
  bool mbIgnoreNextExpand;                                     // +0x68
  bool mbExpandable;                                           // +0x69
};

// @ 0x005CB060
void cSPPaletteUI::SetExpanded(bool expanded) {
  if (mbIgnoreNextExpand) {
    mbIgnoreNextExpand = false;
    return;
  }
  if (!mbExpandable)
    return;
  IWindow* expandWin = mLayout->FindWindowByID(0x7bce6e8, true);
  IWinButton* expandButton = expandWin ? (IWinButton*)expandWin->Cast(0x8ed27e7a) : 0;
  IWindow* panel = mLayout->FindWindowByID(0x7bcefd0, true);
  mCurrentCategory->SetActive(expanded);
  if (expanded)
    MessageServer()->MessageSend(0x7d11fe1, this, 0);
  else
    MessageServer()->MessageSend(0x7d11fe0, this, 0);
  if (expandButton) {
    expandButton->SetButtonStateFlag(4, !expanded);
    IWindow* buttonWin = expandButton->ToWindow();
    SPUIHelpers::AnchorWindowToWindow(buttonWin->GetParent(), expandButton->ToWindow(), 0x900, 0);
  }
  if (panel) {
    panel->SetFlag(1, !expanded);
    if (expandButton)
      SPUIHelpers::AnchorWindowToWindow(expandButton->ToWindow()->GetParent(), panel, 0x900, 0);
  }
}

// @ 0x005CB180
void cSPPaletteUI::SetVisible(bool visible) {
  if (mWinRoot)
    mWinRoot->SetFlag(1, visible);
  SetExpanded(visible);
}

// @ 0x005CB1B0
cCategoryInfo cSPPaletteUI::GetCategoryInfo() {
  cCategoryInfo info(0, kDefaultCategoryColor, kDefaultCategoryColor);
  if (mCurrentCategory) {
    cCategoryInfo tmp;
    info = *mCurrentCategory->GetCategoryInfo(&tmp);
  }
  return info;
}

// @ 0x005CB240
void cSPPaletteUI::SetCurrentCategoryIndex(int index) {
  if (index < 0 || index >= (int)mCategoryUIs.size())
    return;
  bool hasButtons = mCategoryButtons.size() > 0;
  if (mCurrentCategory) {
    if (hasButtons) {
      int current = GetCurrentCategoryIndex();
      if (current != -1)
        mCategoryButtons[current]->SetButtonStateFlag(4, false);
    }
    mCurrentCategory->SetActive(false);
  }
  mCurrentCategory = mCategoryUIs[index];
  mCurrentCategory->SetActive(true);
  if (hasButtons) {
    mCategoryButtons[index]->SetButtonStateFlag(4, true);
    mWinSelectedCategoryBackground->StartAnimation();
  }
  SetVisibleChunk((unsigned int)index / 9);
  PlayUISound(0x38eb66f8);
  EditorUtils::PlayEditorSound(0x1d6253c0, 0x3597e2da, (float)index, 0);
  MessageServer()->MessageSend(0x44ef2b8, this, 0);
  gCategoryToggle = (float)(gCategoryToggle == 0.0f);
  SetGlobalProperty(0x6ca71431, gCategoryToggle);
  SetExpanded(true);
}

// @ 0x005CB380
void cSPPaletteUI::ToggleExpanded() {
  SetExpanded(!mCurrentCategory->IsExpanded());
}

// @ 0x005CB3B0
cSPPaletteUI::cSPPaletteUI()
    : mWinCategoryIcons(0), mLeftBackground(0), mRightBackground(0), mFullBackground(0),
      mWinSelectedCategoryBackground(0), mWinCategory(0), mSelectedSet(0), mCurrentCategoryChunk(0),
      mCurrentCategory(0), mbIgnoreNextExpand(false), mbExpandable(false) {}

// @ 0x005CB420
cSPPaletteUI::~cSPPaletteUI() {}

// @ 0x005CB4A0
bool cSPPaletteUI::DoMessage(IWindow* window, const Message& message) {
  if (message.mEventType == 0x287259f6) {
    int id = message.mControlID;
    if (id == 0x5aec4b8) {
      int numChunks = (int)((mCategoryButtons.size() + 8) / 9);
      int chunk = (mCurrentCategoryChunk + numChunks - 1) % numChunks;
      SetVisibleChunk(chunk);
      SetCurrentCategoryIndex(chunk * 9);
    } else if (id == 0x5aec4b9) {
      int numChunks = (int)((mCategoryButtons.size() + 8) / 9);
      int chunk = (mCurrentCategoryChunk + 1) % numChunks;
      SetVisibleChunk(chunk);
      SetCurrentCategoryIndex(chunk * 9);
    } else if (id == 0x7bce6e8) {
      EA::Audio::IAudioSystem* audio = EA::Audio::GetSystemAT();
      PlayAudio(0x38eb66f8, audio ? audio->GetSystem() : 0);
      ToggleExpanded();
    } else if (GetCurrentCategoryIndex() == id) {
      ToggleExpanded();
    } else {
      SetCurrentCategoryIndex(id);
    }
    return true;
  }
  return false;
}

// @ 0x005CB5A0
void cSPPaletteUI::Init(cSPPalette* palette, IWindow* parent, int, cSPPaletteInfo* info) {
  mData = palette;
  mInfo = info;
  mLayout = new ("Editor", 0, 0, 0, 0) cSPUILayout();
  if (mLayout->Init(Key(palette->mImageGroupID, 0x510a95b, 0x40464100), true, 0x5b598fa)) {
    mLayout->SetParentWin(parent, true, 0x5b598fa);
    mWinRoot = mLayout->FindWindowByID(0xffffffff, true);
    if (mWinRoot)
      SPUIHelpers::SetWindowAreaToParent(mWinRoot);
    IWindow* selected = mLayout->FindWindowByID(0x49afe6a1, true);
    mWinSelectedCategoryBackground = selected ? static_cast<cSPUIAnimatedIconWin*>(selected) : 0;
    if (mWinSelectedCategoryBackground)
      static_cast<IWindow*>(mWinSelectedCategoryBackground)->SetFlag(1, false);
    mLeftBackground = mLayout->FindWindowByID(0xba83c461, true);
    mRightBackground = mLayout->FindWindowByID(0x90d4aadc, true);
    mFullBackground = mLayout->FindWindowByID(0x5aeff7f, true);
    mWinCategoryIcons = mLayout->FindWindowByID(0x72df4cee, true);
    mWinCategory = mLayout->FindWindowByID(0x93019dbc, true);
  }
  IWindow* window = mLayout->FindWindowByID(0x5aec4b8, true);
  if (window)
    window->AddWinProc(this);
  window = mLayout->FindWindowByID(0x5aec4b9, true);
  if (window)
    window->AddWinProc(this);
  window = mLayout->FindWindowByID(0x7bce6e8, true);
  if (window)
    window->AddWinProc(this);

  int numCategories = (int)mData->mCategories.size();
  int buttonIndex = 0;
  for (int i = 0; i < numCategories; i++) {
    cSPPaletteCategory* category = mData->GetCategory(i);
    cSPPaletteCategoryUI* categoryUI = new ("Editor", 0, 0, 0, 0) cSPPaletteCategoryUI();
    AutoRefCount<cSPPaletteCategoryUI> categoryUIRef(categoryUI);
    categoryUI->Init(category, mWinCategory, info);
    mCategoryUIs.push_back(categoryUIRef);
    if (mWinCategoryIcons && numCategories > 1) {
      IWinButton* button =
          category->mpButtonImageKeys
              ? SPUIHelpers::CreateButtonFromKeys(category->mpButtonImageKeys, 3, buttonIndex, Vector2(0.0f, 0.0f),
                                                  mWinCategoryIcons)
              : SPUIHelpers::CreateButtonFromKey(&category->mButtonImageKey, 3, buttonIndex, Vector2(0.0f, 0.0f),
                                                 mWinCategoryIcons);
      if (button) {
        button->SetCommandData(&mData);
        button->ToWindow()->AddWinProc(this);
        AutoRefCount<UI::Tooltip> tooltip = new (4, "UI/Tooltip", GetUIAllocator())
            UI::Tooltip(L"Tooltips", 0x3754e6c, category->mCategoryName.GetText(), Vector2(), 1, L"", 0);
        button->ToWindow()->AddWinProc((IWinProc*)(UI::Tooltip*)tooltip);
        AutoRefCount<UI::FadeEffect> fade = new (8, "UI/Category Fade", GetUIAllocator()) UI::FadeEffect();
        fade->mEffect.SetFadeIn(true);
        fade->mEffect.SetDuration(0.3f);
        button->ToWindow()->AddWinProc((IWinProc*)(UI::FadeEffect*)fade);
        mCategoryButtons.push_back(AutoRefCount<IWinButton>(button));
      }
    }
    buttonIndex++;
  }
  LayoutCategoryButtons();
  mCurrentCategoryChunk = 0;
  if (mData->mStartupCategoryIndex != -1)
    SetCurrentCategoryIndex(mData->mStartupCategoryIndex);
  else
    SetCurrentCategoryIndex(0);
  if (mCurrentCategory)
    mCurrentCategory->SetActive(true);
}

// @ 0x005CBA90
void cSPPaletteUI::Shutdown() {
  int numCategories = (int)mCategoryUIs.size();
  for (int i = 0; i < numCategories; i++)
    mCategoryUIs[i]->Shutdown();
  mCategoryUIs.clear();
  mData.AsOutParam();
  mInfo.AsOutParam();
  mWinCategoryIcons = 0;
  mLeftBackground = 0;
  mRightBackground = 0;
  mFullBackground = 0;
  mWinSelectedCategoryBackground = 0;
  mWinCategory = 0;
  mWinRoot = 0;
  if (mLayout) {
    IWindow* window = mLayout->FindWindowByID(0x5aec4b8, true);
    if (window)
      window->RemoveWinProc(this);
    window = mLayout->FindWindowByID(0x5aec4b9, true);
    if (window)
      window->RemoveWinProc(this);
    mLayout->Shutdown(true);
    mLayout.AsOutParam();
  }
}

void GetDirectory(uint32_t id, void* out, int flags);  // 0x00688830
inline int GetAudioSystem() {
  EA::Audio::IAudioSystem* audio = EA::Audio::GetSystemAT();
  return audio ? audio->GetSystem() : 0;
}

// @ 0x005CBB70
bool EditorCommandHandler(const char* command, void* context, uint32_t* args, int* results) {
  if (strcmp(command, "EditorTest") == 0)
    return true;
  if (strcmp(command, "PlayAudio") == 0) {
    if (*results == 0)
      PlayAudio(*args, GetAudioSystem());
    else
      PlayAudio(*args, *results);
    return true;
  }
  if (strcmp(command, "GetDirectory") == 0) {
    GetDirectory(*args, results, 0);
    return true;
  }
  return false;
}
}  // namespace SP

// ---------------------------------------------------------------------------------------------
// buffered output stream (RefCountVTemplate + IStream at +8) with an inline 0x3a88-byte heap
struct HeapBlock {
  uint32_t mSize;
  uint32_t mFlags;
};
struct HeapFreeNode {
  uint32_t mSize;
  HeapBlock* mpBlock;
};
struct HeapHeader {
  uint32_t mMagic;
  uint32_t mCapacity;
  uint32_t mFreeSize;
  HeapFreeNode* mpFirstFree;
  uint32_t mFlags10;
};

class cStreamBuffer {
 public:
  cStreamBuffer();
  bool Open(void* target);                       // 0x004bd9f0
  int GetSize();                                 // 0x004bdbd0
  bool Write(const void* data, int size, bool flush);  // 0x004bdc60
  bool Finish();                                 // 0x004be5d0
  void Reset();                                  // 0x004bdae0
  void destroy_shared();                         // 0x004bca10
  ~cStreamBuffer() {
    if (mpHeap && (mpHeap->mFlags10 & 0x40000000))
      destroy_shared();
    mpHeap = 0;
  }
  HeapHeader* mpHeap;
  uint32_t mBuffer[0x42b4 / 4];
};

// @ 0x005CBE40
cStreamBuffer::cStreamBuffer() {
  mpHeap = (HeapHeader*)mBuffer;
  if (mpHeap) {
    mpHeap->mMagic = 0x86421357;
    mpHeap->mCapacity = 0x3a88;
    HeapBlock* block = (HeapBlock*)((char*)mpHeap + 0x10);
    block->mSize = 8;
    block->mFlags = 0;
    HeapFreeNode* node = (HeapFreeNode*)(block + 1);
    node->mSize = mpHeap->mCapacity - 8;
    node->mpBlock = block;
    mpHeap->mFreeSize = mpHeap->mCapacity - 8;
    mpHeap->mpFirstFree = node;
  } else {
    mpHeap = 0;
  }
}

class IStream {
 public:
  ~IStream() {}
  virtual int GetState();                          // +0x0
  virtual int GetSize();                           // +0x4
  virtual int GetValue(int which);                 // +0x8
  virtual int Matches(int value, int which);      // +0xc
  virtual bool Write(const void* data, int size);  // +0x10
  virtual bool Close();                            // +0x14
  virtual void Flush();                            // +0x18
};

class cBufferedStream : public EA::RefCountVTemplate<int>, public IStream {
 public:
  cBufferedStream();
  virtual ~cBufferedStream();
  virtual int GetState();
  virtual int GetSize();
  virtual int GetValue(int which);
  virtual int Matches(int value, int which);
  virtual bool Write(const void* data, int size);
  virtual bool Close();
  bool Open(EA::COM::IUnknown32* target);

  bool mbOpen;                        // +0xc
  bool mbOK;                          // +0xd
  int mPosition;                      // +0x10
  cStreamBuffer mBuffer;              // +0x14
  EA::COM::IUnknown32* mpTarget;      // +0x42cc
};

// @ 0x005CBCA0
int cBufferedStream::GetState() {
  return mbOpen ? 2 : 0;
}

// @ 0x005CBCB0
int cBufferedStream::GetSize() {
  if (mbOpen) {
    if (!mbOK)
      return mBuffer.GetSize();
    return 0;
  }
  return -2;
}

// @ 0x005CBCD0
int cBufferedStream::GetValue(int which) {
  switch (which) {
    case 0:
      return mPosition;
    case 1:
      return 0;
    case 2:
      return -1;
  }
  return -1;
}

// @ 0x005CBD00
int cBufferedStream::Matches(int value, int which) {
  if ((which == 0 && value == mPosition) || (which == 1 && value == 0))
    return 1;
  return 0;
}

// @ 0x005CBD30
bool cBufferedStream::Open(EA::COM::IUnknown32* target) {
  if (!mbOpen && !mpTarget) {
    mpTarget = target;
    target->AddRef();
    mBuffer.Open(mpTarget);
    mPosition = 0;
    mbOpen = true;
    mbOK = true;
    return true;
  }
  mbOK = false;
  Flush();
  return mbOK;
}

// @ 0x005CBD90
bool cBufferedStream::Write(const void* data, int size) {
  if (mbOpen && mpTarget) {
    mbOK = mBuffer.Write(data, size, false);
    mPosition += size;
    return mbOK;
  }
  return false;
}

// @ 0x005CBDD0
bool cBufferedStream::Close() {
  if (mbOpen && mbOK) {
    mbOK = mBuffer.Write(0, 0, true);
    mbOK = mbOK && mBuffer.Finish();
  }
  mbOpen = false;
  if (mpTarget) {
    mpTarget->Release();
    mpTarget = 0;
  }
  mBuffer.Reset();
  return mbOK;
}

// @ 0x005CBEC0
cBufferedStream::cBufferedStream() : mbOpen(false), mbOK(false), mPosition(0), mpTarget(0) {}

// @ 0x005CBF00  cBufferedStream scalar deleting dtor (??_G, inlines the dtor below)
cBufferedStream::~cBufferedStream() {
  cBufferedStream::Close();
}

// ---------------------------------------------------------------------------------------------
class ILayoutListener {
 public:
  virtual void OnLayout();
};
class cSPUIPropertyLayoutBase {
 public:
  virtual ~cSPUIPropertyLayoutBase();
};
class cSPUIPropertyLayout : public cSPUIPropertyLayoutBase, public ILayoutListener {
 public:
  cSPUIPropertyLayout();  // 0x008286d0
  virtual ~cSPUIPropertyLayout();
  virtual void OnLayout();
  void SetLayoutName(const wchar_t* name, uint32_t groupID);  // 0x00827fc0
  uint32_t pad08[0x78 / 4 - 2];
};

class cSPUISellBackRollover : public cSPUIPropertyLayout {
 public:
  cSPUISellBackRollover();
  virtual ~cSPUISellBackRollover();
  virtual void OnLayout();
  uint32_t mField78, mField7c, mField80, mField84, mField88, mField8c, mField90;
  short mShort94;     // +0x94
  bool mbVisible;     // +0x96
  int mField98;       // +0x98
};

// @ 0x005CBF60
cSPUISellBackRollover::cSPUISellBackRollover()
    : mField78(0), mField7c(0), mField80(0), mField84(0), mField88(0), mField8c(0), mField90(0), mShort94(0),
      mbVisible(true), mField98(0) {
  SetLayoutName(L"RolloverEditorSellBack", 0x40464100);
}
