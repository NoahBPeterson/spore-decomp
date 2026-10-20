// src/game/SPEditors/SPEditorPaletteUI.cpp -- migrated from slice(s) s00662d70, s005cb060, s005ca070 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorPaletteUI.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPPaletteUI.h"
#include "EA/UTFWinControls/IButtonDrawable.h"
#include "EA/UTFWin/IDrawable.h"
#include "EA/UTFWinControls/IWinButton.h"
#include "EA/UTFWin/IWinProc.h"
#include "EA/UTFWin/IWindow.h"
#include "SP/cSPPaletteCategory.h"
#include "SP/cSPPaletteCategoryUI.h"
#include "SP/cSPPaletteSubCategoryUI.h"
#include "cSPUILayout.h"
#include "SP/cString.h"
#include <new>
#include "EA/UTFWin/Message.h"
#include "SP/cSPPalette.h"
#include "cSPUIPropertyLayout.h"
#include <string.h>
#include <intrin.h>

// ---- items of slice s005ca070 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl FUN_011e0744(void* dst, const void* src, unsigned int n); // 0x011e0744
void* operator new(unsigned int n, const char* name, int flags, unsigned int debugFlags,
                   const char* file, int line); // 0x00f473a0
#define PV(n) virtual void pv##n();
struct Vector2_s005c_a070;
struct Pt2;
namespace EA {
namespace UTFWin {
class IUnknown32 {
 public:
  virtual int AddRef();   // +0
  virtual int Release();  // +4
};
}
}
namespace EA {
namespace UTFWin {
struct Rect {  // EA::RectT<float>: user copy ctor (movss) and operator= (fld/fstp), as in the original
  float mLeft, mTop, mRight, mBottom;
  Rect() {}
  Rect(const Rect& r) : mLeft(r.mLeft), mTop(r.mTop), mRight(r.mRight), mBottom(r.mBottom) {}
  Rect& operator=(const Rect& r) {
    mLeft = r.mLeft;
    mTop = r.mTop;
    mRight = r.mRight;
    mBottom = r.mBottom;
    return *this;
  }
};
}
}
namespace EA {
namespace UTFWin {
class IButtonDrawable {  // what IDrawable::Cast(0x103c1908) returns
 public:
  virtual int AddRef();   // +0
  virtual int Release();  // +4
  PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual void SetImageIndex(int index);  // +0x1c
};
}
}
namespace EA {
namespace UTFWin {
class IDrawable_s005c_a070 : public IUnknown32 {
 public:
  PV(2)
  virtual IButtonDrawable* Cast(unsigned int typeID);  // +0xc
};
}
}
namespace EA {
namespace UTFWin {
class IWinProc_s005c_a070 {
 public:
  virtual int AddRef();
  virtual int Release();
};
}
}
namespace EA {
namespace UTFWin {
class IWindow_s005c_a070 : public IUnknown32 {
 public:
  PV(2) PV(3)
  virtual IWindow_s005c_a070* GetSlot4();  // +0x10
  PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
  virtual const Rect& GetArea();      // +0x34
  virtual const Rect& GetRealArea();  // +0x38
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23)
  virtual void SetArea(const Rect& area);        // +0x60
  virtual void SetLocation(float x, float y);    // +0x64
  virtual void SetSize(float w, float h);        // +0x68
  PV(27) PV(28) PV(29) PV(30)
  virtual void SetFlag(int flag, bool value);    // +0x7c
  virtual void SetCaption(const wchar_t* text);  // +0x80
  virtual void SetTextFontID(unsigned int id);   // +0x84
  PV(34) PV(35)
  virtual void Invalidate();                     // +0x90
  PV(37) PV(38) PV(39) PV(40) PV(41)
  virtual IDrawable_s005c_a070* GetDrawable();              // +0xa8
  PV(43) PV(44) PV(45) PV(46) PV(47)
  virtual const Vector2_s005c_a070 TransformA(Vector2_s005c_a070 v);  // +0xc0
  virtual const Vector2_s005c_a070 TransformB(Vector2_s005c_a070 v);  // +0xc4
  PV(50) PV(51) PV(52) PV(53) PV(54) PV(55)
  PV(56) PV(57) PV(58) PV(59) PV(60) PV(61) PV(62) PV(63) PV(64)
  virtual void AddWinProc(IWinProc_s005c_a070* proc);       // +0x104
  virtual void RemoveWinProc(IWinProc_s005c_a070* proc);    // +0x108
};
}
}
namespace EA {
namespace UTFWin {
class IWinButton : public IUnknown32 {
 public:
  PV(2) PV(3)
  virtual IWindow_s005c_a070* ToWindow();  // +0x10
  PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual void SetButtonStateFlag(int flag, bool value);  // +0x28
  PV(11) PV(12) PV(13) PV(14) PV(15) PV(16)
  virtual void SetButtonGroupID(unsigned int id);         // +0x44
};
}
}
using EA::UTFWin::IWindow_s005c_a070;
using EA::UTFWin::IWinButton;
using EA::UTFWin::IWinProc_s005c_a070;
using EA::UTFWin::Rect;
namespace eastl {
template <typename T>
class sp_vector {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  int mAllocator[2];
  sp_vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~sp_vector();
};  // namespace eastl
}
class cSPUILayout_s005c_a070 {
 public:
  IWindow_s005c_a070* FindWindowByID(unsigned int id, bool recursive);  // 0x008105b0
};
class cSPPaletteCategory;
class cSPPaletteCategoryUI {
 public:
  virtual int pvIHandler0();
  virtual int pvIHandler1();
  virtual int AddRef();   // +8
  virtual int Release();  // +0xc
  cSPPaletteCategoryUI();                                                   // 0x005c3e00
  void Init(cSPPaletteCategory* data, IWindow_s005c_a070* parent, unsigned int arg3);  // 0x005c53c0
  void SetVisibility(bool visible);                                         // 0x005c2960
  void SetPackPaneVisible(bool visible);                                    // 0x005c2ec0
  void Update(int deltaTime);    // 0x005c28b0
  void Shutdown();               // 0x005c4e40
  bool IsPaintByNumber();        // 0x005c2cd0
};
class cSPPaletteUI {
 public:
  char pad0[0xc];                                        // vtable + refcount bases
  cSPUILayout_s005c_a070* mLayout;                                  // +0xc
  IWindow_s005c_a070* mWinCategoryIcons;                            // +0x10
  IWindow_s005c_a070* mLeftBackground;                              // +0x14
  IWindow_s005c_a070* mRightBackground;                             // +0x18
  IWindow_s005c_a070* mFullBackground;                              // +0x1c
  struct SelBg { IWindow_s005c_a070* AsWindow() { return (IWindow_s005c_a070*)((char*)this + 4); } };
  SelBg* mWinSelectedCategoryBackground;                 // +0x20 (IWindow is a secondary base at +4)
  char pad24[0x34 - 0x24];
  eastl::sp_vector<cSPPaletteCategoryUI*> mCategories;   // +0x34
  eastl::sp_vector<IWinButton*> mVec48;                  // +0x48
  int mPad5c;                                            // +0x5c
  int mVisibleChunk;                                     // +0x60
  cSPPaletteCategoryUI* mSelectedCategory;               // +0x64

  void UpdateCategories(int deltaTime);                  // 0x005ca980
  void SetButtonPositions();                             // 0x005cae60
  __declspec(noinline) int FindCategoryIndex();          // 0x005ca9c0
  __forceinline bool ShowChunkButtons() {
    if (((unsigned int)((char*)mVec48.mpEnd - (char*)mVec48.mpBegin) >> 2) != 0) {
      for (unsigned int i = 0; i < (unsigned int)(mVec48.mpEnd - mVec48.mpBegin); i++) {
        if (i / 9 != (unsigned int)mVisibleChunk)
          mVec48.mpBegin[i]->ToWindow()->SetFlag(1, false);
        else
          mVec48.mpBegin[i]->ToWindow()->SetFlag(1, true);
      }
      int idx = FindCategoryIndexInline();
      if ((unsigned int)idx / 9 == (unsigned int)mVisibleChunk)
        return true;
    }
    return false;
  }
  __forceinline int FindCategoryIndexInline() {          // same body, inlined at the first use
    int count = (int)(mCategories.mpEnd - mCategories.mpBegin);
    for (int i = 0; i < count; i++) {
      if (mCategories.mpBegin[i] == mSelectedCategory)
        return i;
    }
    return -1;
  }
  bool IsPaintByNumber();                                // 0x005ca920
  void SetVisibleChunk(int value);                       // 0x005cadb0
  void UpdateNavigationVisiblity();                      // 0x005ca9f0 (out of line)
};
struct Key_s005c_a070 {
  unsigned int mInstance, mType, mGroup;
  Key_s005c_a070() {}
  Key_s005c_a070(unsigned int instance, unsigned int type, unsigned int group)
      : mInstance(instance), mType(type), mGroup(group) {}
};
struct Pt2 {
  float x, y;
  Pt2(const Pt2& v) : x(v.x), y(v.y) {}
};
struct Vector2_s005c_a070 {
  float x, y;
  Vector2_s005c_a070(float x_, float y_) : x(x_), y(y_) {}
  Vector2_s005c_a070(const Vector2_s005c_a070& v) : x(v.x), y(v.y) {}
  Vector2_s005c_a070(const Pt2& v) : x(v.x), y(v.y) {}
};
namespace eastl {
template <typename T>
class sp_vec {  // vector<T, sp_vector_allocator>: begin/end/capacity + 2-word allocator
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  int mAllocator[2];
  unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
  T& operator[](unsigned int i) { return mpBegin[i]; }
  void clear() {
    T* last = mpEnd;
    T* first = mpBegin;
    FUN_011e0744(first, last, (unsigned int)((char*)mpEnd - (char*)last));
    mpEnd = mpEnd + (-(last - first));
  }
  T* erase(T* first, T* last);  // 0x00663430
  void DoInsertValue(T* position, const T& value);
  void push_back(const T& value) {
    if (mpEnd < mpCapacity)
      ::new (mpEnd++) T(value);
    else
      DoInsertValue(mpEnd, value);
  }
};  // namespace eastl
}
class cString {
 public:
  const wchar_t* GetText();  // 0x006b55c0
};
class cSPPaletteCategory {  // retail layout (RefCountVTemplate + IUnknown32 bases)
 public:
  char pad0[0x34];
  eastl::sp_vec<cSPPaletteCategory*> mSubCategories;  // +0x34 (really AutoRefCount elements)
  char pad48[0x5c - 0x48];
  cString mCategoryName;                              // +0x5c
  char pad6c[0x7c - 0x5c - 0x14];
  Key_s005c_a070 mButtonImageKey;                                // +0x7c
  cSPPaletteCategory* GetSubCategory(int index);      // 0x005cae30
};
    void* operator new(unsigned int, char*, int, unsigned int, char*, int); // 0x00f473a0
// ---- items of slice s005ca070 end

// ---- items of slice s005cb060 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
template <typename T>
class AutoRefCount_s005c_b060 {
 public:
  T* mpObject;
  AutoRefCount_s005c_b060() : mpObject(0) {}
  AutoRefCount_s005c_b060(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  AutoRefCount_s005c_b060(const AutoRefCount_s005c_b060& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount_s005c_b060() { if (mpObject) mpObject->Release(); }
  AutoRefCount_s005c_b060& operator=(T* p) {
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
}
namespace EA {
template <typename T>
class RefCountVTemplate_s005c_b060 {
 public:
  RefCountVTemplate_s005c_b060() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s005c_b060() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace EA {
namespace COM {
class IUnknown32_s005c_b060 {
 public:
  ~IUnknown32_s005c_b060() {}
  virtual int AddRef() = 0;
  virtual int Release() = 0;
  virtual int GetTypeID() const;
  virtual void* Cast(uint32_t typeID) const = 0;  // +0xc
};  // namespace COM
}
}
namespace EA {
namespace ResourceMan {
struct Key_s005c_b060 {
  unsigned int mInstance, mType, mGroup;
  Key_s005c_b060() {}
  Key_s005c_b060(unsigned int instance, unsigned int type, unsigned int group)
      : mInstance(instance), mType(type), mGroup(group) {}
};
}
}
namespace EA {
struct Vector2 {
  float x, y;
  Vector2() {}
  Vector2(float x_, float y_) : x(x_), y(y_) {}
  Vector2(const Vector2& v) : x(v.x), y(v.y) {}
};
}
namespace EA {
struct Vector3 {
  float x, y, z;
  Vector3() {}
  Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};
}
namespace EA {
namespace UTFWin {
class IWinProc_s005c_b060;
}
}
namespace EA {
namespace UTFWin {
class IWindow_s005c_b060 : public COM::IUnknown32_s005c_b060 {
 public:
  virtual IWindow_s005c_b060* GetParent();  // +0x10
  PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
  PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
  virtual void SetFlag(int flag, bool value);  // +0x7c
  PV(32) PV(33)
  virtual void Animate();                      // +0x88
  PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47)
  PV(48) PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58) PV(59) PV(60)
  PV(61) PV(62) PV(63) PV(64)
  virtual void AddWinProc(IWinProc_s005c_b060* proc);     // +0x104
  virtual void RemoveWinProc(IWinProc_s005c_b060* proc);  // +0x108
};
}
}
namespace EA {
namespace UTFWin {
struct Message_s005c_b060 {
  uint32_t pad0[2];
  uint32_t mEventType;  // +0x8
  int mControlID;       // +0xc
};
}
}
namespace EA {
namespace UTFWin {
class IWinProc_s005c_b060 : public COM::IUnknown32_s005c_b060 {
 public:
  virtual int GetEventFlags();
  virtual bool DoMessage(IWindow_s005c_b060* window, const Message_s005c_b060& message) = 0;
};
}
}
namespace EA {
namespace UTFWinControls {
class IWinButton_s005c_b060 : public COM::IUnknown32_s005c_b060 {
 public:
  virtual UTFWin::IWindow_s005c_b060* ToWindow();          // +0x10
  PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual void SetButtonStateFlag(int flag, bool value);  // +0x28
  PV(11) PV(12) PV(13) PV(14) PV(15) PV(16)
  virtual void SetCommandData(void* data);      // +0x44
};  // namespace UTFWinControls
}
}
namespace EA {
namespace Messaging {
class IHandler_s005c_b060;
}
}
namespace EA {
namespace Messaging {
class IMessageServer {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void MessageSend(uint32_t messageID, void* message, IHandler_s005c_b060* handler);  // +0x14
};
}
}
namespace EA {
namespace Audio {
class IAudioSystem {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
  virtual int GetSystem();  // +0x20
};
}
}
namespace EA {
namespace Audio {
IAudioSystem* GetSystemAT();  // 0x00a206f0
}
}
using EA::AutoRefCount_s005c_b060;
using EA::Vector2;
using EA::Vector3;
using EA::ResourceMan::Key_s005c_b060;
using EA::UTFWin::IWindow_s005c_b060;
using EA::UTFWin::IWinProc_s005c_b060;
using EA::UTFWin::Message_s005c_b060;
using EA::UTFWinControls::IWinButton_s005c_b060;
namespace eastl {
template <typename T, int kAllocatorWords = 2>
class sp_vector_s005c_b060 {
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
}
namespace eastl {
template <typename T>
class sp_ref_vector : public sp_vector_s005c_b060<EA::AutoRefCount_s005c_b060<T> > {
 public:
  typedef EA::AutoRefCount_s005c_b060<T> value_type;
  sp_ref_vector() {
    this->mpBegin = 0;
    this->mpEnd = 0;
    this->mpCapacity = 0;
  }
  ~sp_ref_vector();
  value_type* erase(value_type* first, value_type* last);
  void clear() { erase(this->mpBegin, this->mpEnd); }
};
}
class cSPUILayout_s005c_b060 {
 public:
  cSPUILayout_s005c_b060();                                                      // 0x00810000
  virtual ~cSPUILayout_s005c_b060();
  virtual int AddRef();
  virtual int Release();
  bool Init(const Key_s005c_b060& key, bool visible, uint32_t parentID);        // 0x008120d0
  void SetParentWin(IWindow_s005c_b060* parent, bool visible, uint32_t parentID);  // 0x008121b0
  IWindow_s005c_b060* FindWindowByID(uint32_t id, bool recursive);              // 0x008105b0
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
class cSPUIAnimatedIconWin : public cCustomWindowBase, public IWindow_s005c_b060 {
 public:
  using cCustomWindowBase::StartAnimation;
};
namespace SPUIHelpers {
void AnchorWindowToWindow(IWindow_s005c_b060* anchor, IWindow_s005c_b060* window, uint32_t flags, int offset);  // 0x00807340
}
namespace SPUIHelpers {
void SetWindowAreaToParent(IWindow_s005c_b060* window);                                             // 0x00806bf0
}
namespace SPUIHelpers {
IWinButton_s005c_b060* CreateButtonFromKeys(Key_s005c_b060* keys, int state, int index, Vector2 offset, IWindow_s005c_b060* parent);  // 0x00808930
}
namespace SPUIHelpers {
IWinButton_s005c_b060* CreateButtonFromKey(Key_s005c_b060* key, int state, int index, Vector2 offset, IWindow_s005c_b060* parent);    // 0x00807a50
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
}
namespace UI {
class IFadeEffect {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5)
  virtual void SetDuration(float seconds);  // +0x18
  PV(7)
  virtual void SetFadeIn(bool fadeIn);      // +0x20
};
}
namespace UI {
class FadeEffect {
 public:
  FadeEffect();  // 0x0096f060
  virtual int AddRef();
  virtual int Release();
  uint32_t pad04[2];
  IFadeEffect mEffect;  // +0xc
  uint32_t mData[(0x60 - 0x10) / 4];
};
}
void* GetUIAllocator();                                                     // 0x009512c0
void* operator new(unsigned int size, int align, const char* name, void* allocator);  // 0x009512d0
namespace SP {
EA::Messaging::IMessageServer* MessageServer();  // 0x0067dcc0
}
namespace SP {
void PlayAudio(uint32_t id, int system);         // 0x00435ed0
}
namespace SP {
void PlayUISound(uint32_t id);                   // 0x004a88d0
}
namespace SP {
namespace EditorUtils {
void PlayEditorSound(uint32_t id, uint32_t param, float value, int flags);  // 0x00435f40
}
}
namespace SP {
void SetGlobalProperty(uint32_t id, float value);  // 0x005ca880
}
namespace SP {
extern float gCategoryToggle;                      // 0x015ed22c
}
namespace SP {
class cString_s005c_b060 {
 public:
  const wchar_t* GetText();  // 0x006b55c0
  uint32_t pad[5];
};
}
namespace SP {
class cSPPaletteCategory_s005c_b060 {
 public:
  uint32_t pad00[0x5c / 4];
  cString_s005c_b060 mCategoryName;          // +0x5c
  uint32_t pad70[3];
  Key_s005c_b060 mButtonImageKey;            // +0x7c
  Key_s005c_b060* mpButtonImageKeys;         // +0x88
};
}
namespace SP {
class cSPPalette_s005c_b060 : public EA::RefCountVTemplate_s005c_b060<int>, public EA::COM::IUnknown32_s005c_b060 {
 public:
  virtual int AddRef();
  virtual int Release();
  eastl::sp_vector_s005c_b060<AutoRefCount_s005c_b060<cSPPaletteCategory_s005c_b060>, 1> mCategories;  // +0xc
  unsigned int mLayoutInstanceID;     // +0x1c
  unsigned int mImageGroupID;         // +0x20
  uint32_t pad24[5];
  int mStartupCategoryIndex;          // +0x38
  cSPPaletteCategory_s005c_b060* GetCategory(int index);  // 0x005c5de0
};
}
namespace SP {
class cSPPaletteInfo_s005c_b060 : public EA::RefCountVTemplate_s005c_b060<int> {};
}
namespace SP {
struct cCategoryInfo {
  cCategoryInfo() {}
  cCategoryInfo(int index, const Vector3& color, const Vector3& highlight)
      : mIndex(index), mColor(color), mHighlight(highlight) {}
  int mIndex;
  Vector3 mColor;
  Vector3 mHighlight;
};
}
namespace SP {
extern const Vector3 kDefaultCategoryColor;  // 0x015168c0
}
namespace SP {
class cSPPaletteCategoryUI_s005c_b060 {
 public:
  cSPPaletteCategoryUI_s005c_b060();  // 0x005c3e00
  PV(0) PV(1)
  virtual int AddRef();   // +0x8
  virtual int Release();  // +0xc
  bool IsExpanded();                                                              // 0x005c2940
  void SetActive(bool active);                                                    // 0x005c2960
  cCategoryInfo* GetCategoryInfo(cCategoryInfo* result);                          // 0x005c2d30
  void Init(cSPPaletteCategory_s005c_b060* category, IWindow_s005c_b060* parent, cSPPaletteInfo_s005c_b060* info);  // 0x005c53c0
  void Shutdown();                                                                // 0x005c4e40
  uint32_t mData[0xfc / 4 - 1];
};
}
namespace SP {
class cSPPaletteUI_s005c_b060 : public IWinProc_s005c_b060, public EA::RefCountVTemplate_s005c_b060<int> {
 public:
  cSPPaletteUI_s005c_b060();
  ~cSPPaletteUI_s005c_b060();
  virtual int AddRef();
  virtual int Release();
  virtual void* Cast(uint32_t typeID) const;
  virtual bool DoMessage(IWindow_s005c_b060* window, const Message_s005c_b060& message);

  void Init(cSPPalette_s005c_b060* palette, IWindow_s005c_b060* parent, int unused, cSPPaletteInfo_s005c_b060* info);  // 0x005cb5a0 (SP::cSPPaletteUI::Init)
  void Shutdown();  // 0x005cba90 (SP::cSPPaletteUI::Shutdown)
  void SetCurrentCategoryIndex(int index);  // 0x005cb240 (SP::cSPPaletteUI::SetCurrentCategoryIndex)
  int GetCurrentCategoryIndex();     // 0x005ca9c0
  void SetVisibleChunk(int chunk);   // 0x005cadb0
  void LayoutCategoryButtons();      // 0x005cae60
  void SetExpanded(bool expanded);
  void SetVisible(bool visible);
  cCategoryInfo GetCategoryInfo();
  void ToggleExpanded();

  AutoRefCount_s005c_b060<cSPUILayout_s005c_b060> mLayout;                           // +0xc
  IWindow_s005c_b060* mWinCategoryIcons;                                  // +0x10
  IWindow_s005c_b060* mLeftBackground;                                    // +0x14
  IWindow_s005c_b060* mRightBackground;                                   // +0x18
  IWindow_s005c_b060* mFullBackground;                                    // +0x1c
  cSPUIAnimatedIconWin* mWinSelectedCategoryBackground;        // +0x20
  IWindow_s005c_b060* mWinCategory;                                       // +0x24
  IWindow_s005c_b060* mWinRoot;                                           // +0x28
  AutoRefCount_s005c_b060<cSPPalette_s005c_b060> mData;                              // +0x2c
  AutoRefCount_s005c_b060<cSPPaletteInfo_s005c_b060> mInfo;                          // +0x30
  eastl::sp_ref_vector<cSPPaletteCategoryUI_s005c_b060> mCategoryUIs;     // +0x34
  eastl::sp_ref_vector<IWinButton_s005c_b060> mCategoryButtons;           // +0x48
  int mSelectedSet;                                            // +0x5c
  int mCurrentCategoryChunk;                                   // +0x60
  cSPPaletteCategoryUI_s005c_b060* mCurrentCategory;                      // +0x64
  bool mbIgnoreNextExpand;                                     // +0x68
  bool mbExpandable;                                           // +0x69
};
}
// ---- items of slice s005cb060 end

// ---- items of slice s00662d70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* CopyImpl(void* first, void* last, void* dest);
typedef void(__thiscall* FnP)(void*);
static inline void* Vslot(void* o, int off) { return ((void**)(*(void**)o))[off / 4]; }
struct VecAutoRef {
    void* begin; void* end; void* cap;
    void erase(void* first, void* last);
};
// ---- items of slice s00662d70 end

// @ 0x005ca9f0
void cSPPaletteUI::UpdateNavigationVisiblity()
{
  if (!ShowChunkButtons()) {
    if (mFullBackground)
      mFullBackground->SetFlag(1, true);
    if (mLeftBackground)
      mLeftBackground->SetFlag(1, false);
    if (mRightBackground)
      mRightBackground->SetFlag(1, false);
    if (mWinSelectedCategoryBackground)
      mWinSelectedCategoryBackground->AsWindow()->SetFlag(1, false);
    if (mSelectedCategory)
      mSelectedCategory->SetPackPaneVisible(false);
  } else {
    if (mFullBackground)
      mFullBackground->SetFlag(1, false);
    if (mLeftBackground && mRightBackground && mWinSelectedCategoryBackground) {
      mWinSelectedCategoryBackground->AsWindow()->SetFlag(1, true);
      mLeftBackground->SetFlag(1, true);
      mRightBackground->SetFlag(1, true);
      IWindow_s005c_a070* catWin = mVec48.mpBegin[FindCategoryIndex()]->ToWindow();
      const Rect* catArea = &catWin->GetRealArea();
      float width = (catArea->mRight - catArea->mLeft) + 3.0f;
      IWindow_s005c_a070* leftWin = mLeftBackground->GetSlot4();
      const Rect* leftArea = &leftWin->GetRealArea();
      float x1 = leftWin->TransformB(catWin->TransformA(Vector2_s005c_a070(-3.0f, 0.0f))).x;
      float x2 = leftWin->TransformB(catWin->TransformA(Vector2_s005c_a070(width, 0.0f))).x;
      Rect r1 = mLeftBackground->GetArea();
      r1.mLeft = 0.0f;
      r1.mRight = x1;
      mLeftBackground->SetArea(r1);
      Rect r2 = mRightBackground->GetArea();
      r2.mLeft = x2;
      r2.mRight = leftArea->mRight - leftArea->mLeft;
      mRightBackground->SetArea(r2);
      IWindow_s005c_a070* selWin = mWinSelectedCategoryBackground->AsWindow();
      Rect r3 = selWin->GetArea();
      r3.mLeft = x1;
      r3.mRight = x2;
      selWin->SetArea(r3);
    }
    if (mSelectedCategory)
      mSelectedCategory->SetPackPaneVisible(true);
  }
}

// @ 0x005cadb0
void cSPPaletteUI::SetVisibleChunk(int value)
{
  mVisibleChunk = value;
  int count = (int)(mVec48.mpEnd - mVec48.mpBegin);
  unsigned int pages = (unsigned int)(count + 8) / 9;
  IWindow_s005c_a070* w = mLayout->FindWindowByID(0x5aec4b8, true);
  if (w)
    w->SetFlag(1, value > 0);
  IWindow_s005c_a070* w2 = mLayout->FindWindowByID(0x5aec4b9, true);
  if (w2)
    w2->SetFlag(1, value + 1 < (int)pages);
  UpdateNavigationVisiblity();
}

// @ 0x005cae60
void cSPPaletteUI::SetButtonPositions()
{
  if (!mWinCategoryIcons)
    return;
  if (mVec48.mpBegin == mVec48.mpEnd)
    return;

  const Rect& iconFrame = mWinCategoryIcons->GetRealArea();
  float iconW = iconFrame.mRight - iconFrame.mLeft;
  const Rect& iconFrame2 = mWinCategoryIcons->GetRealArea();
  float iconH = iconFrame2.mBottom - iconFrame2.mTop;

  IWindow_s005c_a070* firstBtn = mVec48.mpBegin[0]->ToWindow();
  const Rect& btnRect = firstBtn->GetArea();
  float btnW = btnRect.mRight - btnRect.mLeft;
  IWindow_s005c_a070* firstBtn2 = mVec48.mpBegin[0]->ToWindow();
  const Rect& btnRect2 = firstBtn2->GetArea();
  float btnH = btnRect2.mBottom - btnRect2.mTop;

  const unsigned int total = (unsigned int)(mVec48.mpEnd - mVec48.mpBegin);
  unsigned int n = total;
  if (n > 9)
    n = 9;
  if (iconW < (float)n * btnW) {
    float scale = iconW / ((float)n * btnW);
    btnW = scale * btnW;
    btnH = scale * btnH;
  }
  if (iconH < btnH) {
    float scale = iconH / btnH;
    btnW = scale * btnW;
    btnH = scale * btnH;
  }
  float step = (iconW - (float)n * btnW) / (float)(n + 1);
  float gap = (iconH - btnH) * 0.5f;
  int count = (int)(mVec48.mpEnd - mVec48.mpBegin);
  for (int i = 0; i < count; i++) {
    IWindow_s005c_a070* btnWin = mVec48.mpBegin[i]->ToWindow();
    Rect area = btnWin->GetArea();
    area.mLeft = (float)(i % n + 1) * step + (float)(i % n) * btnW;
    area.mTop = gap;
    area.mRight = area.mLeft + btnW;
    area.mBottom = area.mTop + btnH;
    btnWin->SetArea(area);
  }
}

// @ 0x005cb060
namespace SP {
void cSPPaletteUI_s005c_b060::SetExpanded(bool expanded)
{
  if (mbIgnoreNextExpand) {
    mbIgnoreNextExpand = false;
    return;
  }
  if (!mbExpandable)
    return;
  IWindow_s005c_b060* expandWin = mLayout->FindWindowByID(0x7bce6e8, true);
  IWinButton_s005c_b060* expandButton = expandWin ? (IWinButton_s005c_b060*)expandWin->Cast(0x8ed27e7a) : 0;
  IWindow_s005c_b060* panel = mLayout->FindWindowByID(0x7bcefd0, true);
  mCurrentCategory->SetActive(expanded);
  if (expanded)
    MessageServer()->MessageSend(0x7d11fe1, this, 0);
  else
    MessageServer()->MessageSend(0x7d11fe0, this, 0);
  if (expandButton) {
    expandButton->SetButtonStateFlag(4, !expanded);
    IWindow_s005c_b060* buttonWin = expandButton->ToWindow();
    SPUIHelpers::AnchorWindowToWindow(buttonWin->GetParent(), expandButton->ToWindow(), 0x900, 0);
  }
  if (panel) {
    panel->SetFlag(1, !expanded);
    if (expandButton)
      SPUIHelpers::AnchorWindowToWindow(expandButton->ToWindow()->GetParent(), panel, 0x900, 0);
  }
}
}  // namespace SP

// @ 0x005cb180
namespace SP {
void cSPPaletteUI_s005c_b060::SetVisible(bool visible)
{
  if (mWinRoot)
    mWinRoot->SetFlag(1, visible);
  SetExpanded(visible);
}
}  // namespace SP

// @ 0x005cb1b0
namespace SP {
cCategoryInfo cSPPaletteUI_s005c_b060::GetCategoryInfo()
{
  cCategoryInfo info(0, kDefaultCategoryColor, kDefaultCategoryColor);
  if (mCurrentCategory) {
    cCategoryInfo tmp;
    info = *mCurrentCategory->GetCategoryInfo(&tmp);
  }
  return info;
}
}  // namespace SP

// @ 0x005cb240
namespace SP {
void cSPPaletteUI_s005c_b060::SetCurrentCategoryIndex(int index)
{
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
}  // namespace SP

// @ 0x005cb380
namespace SP {
void cSPPaletteUI_s005c_b060::ToggleExpanded()
{
  SetExpanded(!mCurrentCategory->IsExpanded());
}
}  // namespace SP

// @ 0x005cb3b0
namespace SP {
cSPPaletteUI_s005c_b060::cSPPaletteUI_s005c_b060()
: mWinCategoryIcons(0), mLeftBackground(0), mRightBackground(0), mFullBackground(0),
      mWinSelectedCategoryBackground(0), mWinCategory(0), mSelectedSet(0), mCurrentCategoryChunk(0),
      mCurrentCategory(0), mbIgnoreNextExpand(false), mbExpandable(false) {}
}  // namespace SP

// @ 0x005cb420
namespace SP {
cSPPaletteUI_s005c_b060::~cSPPaletteUI_s005c_b060()
{}
}  // namespace SP

// @ 0x005cb4a0
namespace SP {
bool cSPPaletteUI_s005c_b060::DoMessage(IWindow_s005c_b060* window, const Message_s005c_b060& message)
{
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
}  // namespace SP

// @ 0x005cb5a0
namespace SP {
void cSPPaletteUI_s005c_b060::Init(cSPPalette_s005c_b060* palette, IWindow_s005c_b060* parent, int, cSPPaletteInfo_s005c_b060* info)
{
  mData = palette;
  mInfo = info;
  mLayout = new ("Editor", 0, 0, 0, 0) cSPUILayout_s005c_b060();
  if (mLayout->Init(Key_s005c_b060(palette->mImageGroupID, 0x510a95b, 0x40464100), true, 0x5b598fa)) {
    mLayout->SetParentWin(parent, true, 0x5b598fa);
    mWinRoot = mLayout->FindWindowByID(0xffffffff, true);
    if (mWinRoot)
      SPUIHelpers::SetWindowAreaToParent(mWinRoot);
    IWindow_s005c_b060* selected = mLayout->FindWindowByID(0x49afe6a1, true);
    mWinSelectedCategoryBackground = selected ? static_cast<cSPUIAnimatedIconWin*>(selected) : 0;
    if (mWinSelectedCategoryBackground)
      static_cast<IWindow_s005c_b060*>(mWinSelectedCategoryBackground)->SetFlag(1, false);
    mLeftBackground = mLayout->FindWindowByID(0xba83c461, true);
    mRightBackground = mLayout->FindWindowByID(0x90d4aadc, true);
    mFullBackground = mLayout->FindWindowByID(0x5aeff7f, true);
    mWinCategoryIcons = mLayout->FindWindowByID(0x72df4cee, true);
    mWinCategory = mLayout->FindWindowByID(0x93019dbc, true);
  }
  IWindow_s005c_b060* window = mLayout->FindWindowByID(0x5aec4b8, true);
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
    cSPPaletteCategory_s005c_b060* category = mData->GetCategory(i);
    cSPPaletteCategoryUI_s005c_b060* categoryUI = new ("Editor", 0, 0, 0, 0) cSPPaletteCategoryUI_s005c_b060();
    AutoRefCount_s005c_b060<cSPPaletteCategoryUI_s005c_b060> categoryUIRef(categoryUI);
    categoryUI->Init(category, mWinCategory, info);
    mCategoryUIs.push_back(categoryUIRef);
    if (mWinCategoryIcons && numCategories > 1) {
      IWinButton_s005c_b060* button =
          category->mpButtonImageKeys
              ? SPUIHelpers::CreateButtonFromKeys(category->mpButtonImageKeys, 3, buttonIndex, Vector2(0.0f, 0.0f),
                                                  mWinCategoryIcons)
              : SPUIHelpers::CreateButtonFromKey(&category->mButtonImageKey, 3, buttonIndex, Vector2(0.0f, 0.0f),
                                                 mWinCategoryIcons);
      if (button) {
        button->SetCommandData(&mData);
        button->ToWindow()->AddWinProc(this);
        AutoRefCount_s005c_b060<UI::Tooltip> tooltip = new (4, "UI/Tooltip", GetUIAllocator())
            UI::Tooltip(L"Tooltips", 0x3754e6c, category->mCategoryName.GetText(), Vector2(), 1, L"", 0);
        button->ToWindow()->AddWinProc((IWinProc_s005c_b060*)(UI::Tooltip*)tooltip);
        AutoRefCount_s005c_b060<UI::FadeEffect> fade = new (8, "UI/Category Fade", GetUIAllocator()) UI::FadeEffect();
        fade->mEffect.SetFadeIn(true);
        fade->mEffect.SetDuration(0.3f);
        button->ToWindow()->AddWinProc((IWinProc_s005c_b060*)(UI::FadeEffect*)fade);
        mCategoryButtons.push_back(AutoRefCount_s005c_b060<IWinButton_s005c_b060>(button));
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
}  // namespace SP

// @ 0x005cba90
namespace SP {
void cSPPaletteUI_s005c_b060::Shutdown()
{
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
    IWindow_s005c_b060* window = mLayout->FindWindowByID(0x5aec4b8, true);
    if (window)
      window->RemoveWinProc(this);
    window = mLayout->FindWindowByID(0x5aec4b9, true);
    if (window)
      window->RemoveWinProc(this);
    mLayout->Shutdown(true);
    mLayout.AsOutParam();
  }
}
}  // namespace SP

// @ 0x00663430
void VecAutoRef::erase(void* first, void* last)
{
    char* r = (char*)CopyImpl(last, end, first);
    char* e = (char*)end;
    while (r < e) {
        void* p = *(void**)r;
        if (p) (*(FnP)Vslot(p, 0xc))(p);
        r += 4;
    }
    *(int*)&end += -((((int)((char*)last - (char*)first)) >> 2) * 4);
}
