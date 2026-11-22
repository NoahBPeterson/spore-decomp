// src/game/SPEditors/SPEditorVerbIcon.cpp -- migrated from slice(s) s005e4190, s005dfbb0, s005e2470, s005e16c0 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorVerbIcon.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ResourceMan/Key.h"
#include "SP/cSPEditorVerbIcon.h"
#include "SP/cSPEditorVerbIconData.h"
#include "SP/eLayoutJustification.h"
#include "SP/cAppModeEditorBase.h"
#include "SP/cPropertyList.h"
#include "SP/cSPEditorUI.h"
#include "cSPUILayout.h"
#include "SP/cString.h"
#include "EA/Variant.h"
#include "EA/UTFWin/IWinProc.h"
#include "EA/UTFWin/IWindow.h"
#include "EA/UTFWin/RenderContext.h"
#include "cSPVerbIconRollover.h"
#include <xmmintrin.h>
#include <new>

// ---- items of slice s005e16c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct cVerbIconInterpolationValue_s005e_16c0 {
    float mTarget;      // +0x00
    float mCurrent;     // +0x04
    float mElapsed;     // +0x08
    float mInitial;     // +0x0c
    float mDuration;    // +0x10
    float mOverShoot;   // +0x14
    float mDampen;      // +0x18
    void Init(float a, float b, float c, float d, float e);  // 0x005e1c80 (SP::cVerbIconInterpolationValue::Init)
    int IsAtTarget();
};
}
using SP::cVerbIconInterpolationValue_s005e_16c0;
namespace SP {
struct cSPEditorVerbIcon_s005e_16c0 {
    char pad[0x6a];
    char m6a;   // +0x6a
    char m6b;   // +0x6b
    void SetFlag(char b);
};
}
// ---- items of slice s005e16c0 end

// ---- items of slice s005e2470 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void _pv##n();
namespace Math {
struct Rectangle {
  float x1, y1, x2, y2;
  Rectangle& operator=(const Rectangle& r) {
    x1 = r.x1;
    y1 = r.y1;
    x2 = r.x2;
    y2 = r.y2;
    return *this;
  }
  void Set(float left, float top, float right, float bottom) {
    x1 = left;
    y1 = top;
    x2 = right;
    y2 = bottom;
  }
  float Width() const { return x2 - x1; }
  float Height() const { return y2 - y1; }
};  // namespace Math
}
namespace EA {
namespace ResourceMan {
struct Key_s005e_2470 {
  uint32_t instanceID;
  uint32_t typeID;
  uint32_t groupID;
};  // namespace ResourceMan
}
}
namespace EA {
namespace UTFWin {
class IWinProc_s005e_2470 {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
};
}
}
namespace EA {
namespace UTFWin {
class IWindow_s005e_2470 {
 public:
  virtual int AddRef();                               // +0x00
  virtual int Release();                              // +0x04
  PV(2)
  virtual void* Cast(uint32_t typeID);                // +0x0c
  virtual IWindow_s005e_2470* GetParent();                       // +0x10
  PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual uint32_t GetFlags();                        // +0x28
  PV(11) PV(12)
  virtual const Math::Rectangle& GetRealArea();       // +0x34
  virtual const Math::Rectangle& GetArea();           // +0x38
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22)
  virtual void SetShadeColor(uint32_t color);         // +0x5c
  virtual void SetArea(const Math::Rectangle& area);  // +0x60
  PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
  virtual void SetFlag(int flag, bool value);         // +0x7c
  PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39)
  PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49)
  PV(50) PV(51) PV(52) PV(53)
  virtual void AddWindow(IWindow_s005e_2470* w);                 // +0xd8
  virtual void RemoveWindow(IWindow_s005e_2470* w);              // +0xdc
  PV(56) PV(57) PV(58) PV(59) PV(60) PV(61) PV(62) PV(63) PV(64)
  virtual void AddWinProc(IWinProc_s005e_2470* proc);            // +0x104
  virtual void RemoveWinProc(IWinProc_s005e_2470* proc);         // +0x108
};
}
}
namespace EA {
namespace UTFWin {
class IWinText {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
  virtual uint32_t GetTextColor();                    // +0x24
};
}
}
namespace EA {
template <typename T>
class AutoRefCount_s005e_2470 {
 public:
  T* mpObject;
  AutoRefCount_s005e_2470& operator=(T* pObject) {
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
namespace EA {
template <typename T>
class RefCountVTemplate_s005e_2470 {
 public:
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
using EA::UTFWin::IWindow_s005e_2470;
void* operator new(unsigned int size, const char* pName, int flags, unsigned debugFlags,
                   const char* file, int line);
template <typename T>
inline T* object_cast(const EA::AutoRefCount_s005e_2470<IWindow_s005e_2470>& w, uint32_t typeID) {
  return w ? (T*)w->Cast(typeID) : 0;
}
class cSPUILayout_s005e_2470 {
 public:
  PV(0)
  virtual int AddRef();   // +0x04
  virtual int Release();  // +0x08
  cSPUILayout_s005e_2470();
  bool Init(const EA::ResourceMan::Key_s005e_2470& key, bool visible, uint32_t parentID);  // 0x008120d0 (cSPUILayout::Init)
  IWindow_s005e_2470* FindWindowByID(uint32_t id, bool recursive);  // 0x008105b0 (cSPUILayout::FindWindowByID)
  void Shutdown(bool unused);  // 0x00811ad0 (cSPUILayout::Shutdown)
  uint32_t mData[5];
};
class cSPUILayoutManager_s005e_2470 {
 public:
  IWindow_s005e_2470* GetWorldMainWindow(uint32_t id);  // 0x00810620 (cSPUILayoutManager::GetWorldMainWindow)
};
namespace SP {
namespace SPUIHelpers {
cSPUILayoutManager_s005e_2470* GetLayoutManager();
}
}
namespace SP {
namespace SPUIHelpers {
float GetWindowScaleX(IWindow_s005e_2470* w);  // FUN_00805200
}
}
namespace SP {
namespace SPUIHelpers {
float GetWindowScaleY(IWindow_s005e_2470* w);  // FUN_00805230
}
}
namespace SP {
namespace SPUIHelpers {
void SetWindowImage(IWindow_s005e_2470* w, const EA::ResourceMan::Key_s005e_2470* key, bool b);
}
}
namespace SP {
namespace SPUIHelpers {
void SetWindowAlpha(IWindow_s005e_2470* w, float alpha);
}
}
namespace SP {
class IMessageServer {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void PostMSG(uint32_t id, void* data, void* sender);  // +0x14
};
}
namespace SP {
IMessageServer* MessageServer();
}
namespace SP {
enum eLayoutJustification_s005e_2470 {
  kJustificationNONE_s005e_2470 = 0,
  kJustificationRight_s005e_2470 = -401149879,
  kJustificationLeft_s005e_2470 = 4109362,
  kJustificationTop_s005e_2470 = 1080872010,
  kJustificationBottom_s005e_2470 = -396051872,
};
}
namespace SP {
class cSPEditorVerbIconData_s005e_2470 {
 public:
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4)
  virtual void Shutdown();  // +0x14
  uint32_t pad04[5];
  float mLevel;             // +0x18
  uint32_t pad1c[3];
  int mVerbID;              // +0x28
  bool HasVerb() const {
    bool result = false;
    if (mVerbID != -1)
      result = true;
    return result;
  }
};
}
namespace SP {
class cSPVerbIconRollover {
 public:
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
  virtual void Shutdown();  // +0x24
};
}
namespace SP {
extern const char kEditorAllocName[];  // "Editor"
}
namespace SP {
class cSPEditorVerbIcon_s005e_2470 : public EA::UTFWin::IWinProc_s005e_2470, public EA::RefCountVTemplate_s005e_2470<int> {
 public:
  struct cVerbIconLinearInterpolationValue {
    float mTargetValue;
    float mCurrentValue;
    float mElapsedTime;
    float mInitialValue;
    float mDuration;
    void Reset(float value) {
      mInitialValue = value;
      mCurrentValue = value;
      mTargetValue = value;
      mDuration = 0.0f;
      mElapsedTime = 0.0f;
    }
    void Start(float from, float to, float duration) {
      mInitialValue = from;
      mCurrentValue = from;
      mTargetValue = to;
      mDuration = duration;
      mElapsedTime = 0.0f;
    }
  };
  struct cVerbIconInterpolationValue {
    float mTargetValue;
    float mCurrentValue;
    float mElapsedTime;
    float mInitialValue;
    float mDuration;
    float mOverShoot;
    float mDampenPercent;
    void Reset(float value) {
      mInitialValue = value;
      mCurrentValue = value;
      mTargetValue = value;
      mDuration = 0.0f;
      mOverShoot = 0.0f;
      mDampenPercent = 0.0f;
      mElapsedTime = 0.0f;
    }
    void Start(float from, float to, float duration, float overShoot, float dampen) {
      mInitialValue = from;
      mCurrentValue = from;
      mTargetValue = to;
      mOverShoot = overShoot;
      mDampenPercent = dampen;
      mDuration = duration;
      mElapsedTime = 0.0f;
    }
  };
  struct cVerbIconMiddleInterpolationValue {
    float mEndValue;
    float mMiddleValue;
    float mCurrentValue;
    float mElapsedTime;
    float mInitialValue;
    float mMiddleStart;
    float mMiddleEnd;
    float mDuration;
    void Start(float from, float middle, float to, float middleStart, float middleEnd,
               float duration) {
      mMiddleValue = middle;
      mMiddleStart = middleStart;
      mInitialValue = from;
      mCurrentValue = from;
      mMiddleEnd = middleEnd;
      mEndValue = to;
      mDuration = duration;
      mElapsedTime = 0.0f;
    }
  };
  struct cVerbIconOscillatingAlpha {
    float mInitialValue;
    float mEndValue;
    float mCurrentValue;
    float mElapsedTime;
    float mDuration;
    float mSpeed;
    uint32_t mColor;
    void Reset() {
      mCurrentValue = 0.0f;
      mInitialValue = 0.0f;
      mEndValue = 0.0f;
      mDuration = 0.0f;
      mElapsedTime = 0.0f;
      mSpeed = 0.5f;
    }
  };

  // vtable slots 9.. (after the IWinProc slots)
  virtual void LayoutInit(EA::ResourceMan::Key_s005e_2470 key);             // +0x24 0x005e2470
  PV(10) PV(11) PV(12)
  virtual void SetLevel(float level);                            // +0x34 0x005e2ec0
  virtual void UpdateLevelDisplay(float level);                  // +0x38
  PV(15)
  virtual bool IsToggled();                                      // +0x40
  PV(17)
  virtual void SetVerbID(uint32_t id);                           // +0x48

  EA::AutoRefCount_s005e_2470<cSPUILayout_s005e_2470> mLayout;                         // +0x0c
  EA::AutoRefCount_s005e_2470<IWindow_s005e_2470> mWinRoot;                            // +0x10
  EA::AutoRefCount_s005e_2470<IWindow_s005e_2470> mWinIcon;                            // +0x14
  EA::AutoRefCount_s005e_2470<IWindow_s005e_2470> mWinLevel;                           // +0x18
  EA::AutoRefCount_s005e_2470<IWindow_s005e_2470> mWinHighlight;                       // +0x1c
  EA::AutoRefCount_s005e_2470<IWindow_s005e_2470> mWinShortcutText;                    // +0x20
  EA::AutoRefCount_s005e_2470<IWindow_s005e_2470> mWin24;                              // +0x24
  EA::AutoRefCount_s005e_2470<IWindow_s005e_2470> mWinFlashingGlow;                    // +0x28
  EA::AutoRefCount_s005e_2470<IWindow_s005e_2470> mWinChargeDial;                      // +0x2c
  EA::AutoRefCount_s005e_2470<IWindow_s005e_2470> mWinLevelPips[5];                    // +0x30
  uint32_t pad44;
  EA::ResourceMan::Key_s005e_2470 mNormalKey;                               // +0x48
  uint32_t pad54[3];
  uint32_t mRolloverLayout;                                      // +0x60
  int mState;                                                    // +0x64
  bool mAnimate;                                                 // +0x68
  bool mIsVisible;                                               // +0x69
  bool pad6a[3];
  bool mShowingLevel;                                            // +0x6d
  bool mLevelHighlightShown;                                     // +0x6e
  bool mForceEnable;                                             // +0x6f
  bool mIsEnabled;                                               // +0x70
  bool mHasChargeDial;                                           // +0x71
  int mDirection;                                                // +0x74
  uint32_t pad78[4];
  Math::Rectangle mArea;                                         // +0x88
  cVerbIconLinearInterpolationValue mCharge;                     // +0x98
  cVerbIconInterpolationValue mScaleX;                           // +0xac
  cVerbIconInterpolationValue mScaleY;                           // +0xc8
  cVerbIconLinearInterpolationValue mLevel;                      // +0xe4
  cVerbIconInterpolationValue mUpgradeScale;                     // +0xf8
  cVerbIconMiddleInterpolationValue mUpgradeHighlightFade;       // +0x114
  cVerbIconMiddleInterpolationValue mIconAlpha;                  // +0x134
  cVerbIconOscillatingAlpha mFlashAlpha;                         // +0x154
  EA::AutoRefCount_s005e_2470<cSPEditorVerbIconData_s005e_2470> mIconData;             // +0x170
  EA::AutoRefCount_s005e_2470<cSPVerbIconRollover> mRollover;               // +0x174
  uint32_t mBaseTextColor;                                       // +0x178
  uint32_t mCollectionID;                                        // +0x17c
  float mAspectRatio;                                            // +0x180

  float GetLevel(bool current);
  float GetWidth(bool scaled);
  float GetHeight(bool scaled);
  void SetArea(Math::Rectangle area);  // 0x005e2960 (SP::cSPEditorVerbIcon::SetArea)
  void LayoutShutdown();
  bool IsChargeReady();
  void OnClick();  // 0x005e2c30 (SP::cSPEditorVerbIcon::OnClick)
  void SetEnabled(bool enabled);
  void Hide();
  void SetIconData(cSPEditorVerbIconData_s005e_2470* data);
  void EndCharge();  // 0x005e2e50 (SP::cSPEditorVerbIcon::EndCharge)
  void EndFlashing();  // 0x005e3180 (SP::cSPEditorVerbIcon::EndFlashing)
  void Init(IWindow_s005e_2470* parent, EA::ResourceMan::Key_s005e_2470 key, uint32_t verbID, uint32_t rolloverLayout,
            bool animate, int direction, bool forceEnable, bool hasChargeDial);
};
}
namespace SP {
inline void ScaleExtent(float& lo, float& hi, float scale) {
  float size = hi - lo;
  lo -= (size - size * scale) * 0.5f;
  hi = lo + size;
}
}
namespace SP {
struct VerbIconClickMessage {
  VerbIconClickMessage(cSPEditorVerbIconData_s005e_2470* data, uint32_t collection)
      : mpIconData(data), mCollectionID(collection), mFlags(0) {}
  cSPEditorVerbIconData_s005e_2470* mpIconData;
  uint32_t pad04;
  uint32_t mCollectionID;
  uint32_t pad0c;
  uint32_t mFlags;
  uint32_t pad14;
};
}
// ---- items of slice s005e2470 end

// ---- items of slice s005dfbb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct Key {
  uint32_t mInstance;
  uint32_t mType;
  uint32_t mGroup;
};
}
namespace SP {
class IWindow;
}
namespace SP {
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
}
namespace SP {
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
}
namespace SP {
void operator delete[](void* p);  // 0x00f47380
}
namespace SP {
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
}
namespace SP {
struct Rect {
  float x1, y1, x2, y2;
  Rect() {}
  Rect(const Rect& o) : x1(o.x1), y1(o.y1), x2(o.x2), y2(o.y2) {}
};
}
namespace SP {
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
}
namespace SP {
void* GetImageFromLayout(uint32_t value);                      // 0x00458de0
}
namespace SP {
void Pollinator(IWindow* window, Rect* rect);                  // 0x00806d10
}
namespace SP {
void SetImageA(IWindow* window, void* image, int flags);       // 0x00806aa0
}
namespace SP {
void SetImageB(IWindow* window, void* image, int flags);       // 0x008068d0
}
namespace SP {
extern wchar_t gEmptyString16[];  // 0x01667bac
}
namespace SP {
class cString_s005d_fbb0 {
 public:
  cString_s005d_fbb0();                      // 0x006b5060
  ~cString_s005d_fbb0();                     // 0x006b5240
  const wchar_t* GetText();       // 0x006b55c0
  uint32_t mData[5];
};
}
namespace SP {
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
}
namespace SP {
cWStr* WStr_Format(cWStr* str, const wchar_t* fmt, ...);  // 0x0041e050
}
namespace SP {
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
                   const Key* subKey, cString_s005d_fbb0* text, float number);  // 0x005e04d0
};
}
// ---- items of slice s005dfbb0 end

// ---- items of slice s005e4190 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern const char kEditorAllocName[];  // "Editor"
extern float g_015f0090;
extern float g_015f00e0;
extern float g_0151a184;
extern int g_0151a040;
namespace Math {
struct Rectangle_s005e_4190 {
  float x1, y1, x2, y2;
  Rectangle_s005e_4190() {}
  Rectangle_s005e_4190(float l, float t, float r, float b) : x1(l), y1(t), x2(r), y2(b) {}
  Rectangle_s005e_4190(const Rectangle_s005e_4190& r) : x1(r.x1), y1(r.y1), x2(r.x2), y2(r.y2) {}
  Rectangle_s005e_4190& operator=(const Rectangle_s005e_4190& r) {
    x1 = r.x1;
    y1 = r.y1;
    x2 = r.x2;
    y2 = r.y2;
    return *this;
  }
  void Set(float l, float t, float r, float b) {
    x1 = l;
    y1 = t;
    x2 = r;
    y2 = b;
  }
  float Width() const { return x2 - x1; }
  float Height() const { return y2 - y1; }
};  // namespace Math
}
namespace eastl {
union EmptyString {
  uint32_t mUint32;
  wchar_t mEmpty16[1];
};
}
namespace eastl {
extern EmptyString gEmptyString16_s005e_4190;  // 0x01667bac
}
namespace eastl {
class allocator_s005e_4190 { public:
  allocator_s005e_4190() {}
};
}
namespace eastl {
class wstring : private allocator_s005e_4190 {
 public:
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  wstring() { AllocateSelf(); }
  void AllocateSelf() {
    mpBegin = gEmptyString16_s005e_4190.mEmpty16;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + 1;
  }
  void DeallocateSelf() {
    if ((mpCapacity - mpBegin) > 1 && mpBegin)
      EASTL_allocator_deallocate(mpBegin);
  }
  ~wstring() { DeallocateSelf(); }
  void range_initialize(const wchar_t* pStr);  // 0x00579a90
  wstring(const wchar_t* pStr) : mpBegin(0), mpEnd(0), mpCapacity(0) { range_initialize(pStr); }
};
}
namespace EA {
namespace ResourceMan {
class Key_s005e_4190 { public:
  uint32_t instanceID;
  uint32_t typeID;
  uint32_t groupID;
  Key_s005e_4190() : instanceID(0), typeID(0), groupID(0) {}
  Key_s005e_4190(uint32_t i, uint32_t t, uint32_t g) : instanceID(i), typeID(t), groupID(g) {}
};  // namespace ResourceMan
}
}
namespace EA {
struct Point {
  float x;
  float y;
};
}
namespace EA {
namespace UTFWin {
class IWinProc_s005e_4190;
}
}
namespace EA {
namespace UTFWin {
class IWindow_s005e_4190 {
 public:
  virtual int AddRef();                               // +0x00
  virtual int Release();                              // +0x04
  PV(2)
  virtual void* Cast(uint32_t typeID);                // +0x0c
  virtual IWindow_s005e_4190* GetParent();                       // +0x10
  PV(5) PV(6)
  virtual uint32_t GetID();                           // +0x1c
  PV(8) PV(9)
  virtual uint32_t GetFlags();                        // +0x28
  PV(11)
  virtual uint32_t GetShadeColor();                   // +0x30
  virtual const Math::Rectangle_s005e_4190& GetRealArea();       // +0x34
  virtual const Math::Rectangle_s005e_4190& GetArea();           // +0x38
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22)
  virtual void SetShadeColor(uint32_t color);         // +0x5c
  virtual void SetArea(const Math::Rectangle_s005e_4190& area);  // +0x60
  PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
  virtual void SetFlag(int flag, bool value);         // +0x7c
  virtual void SetText(const wchar_t* text);          // +0x80
  PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39)
  PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47)
  virtual EA::Point ToClient(float x, float y);       // +0xc0
  PV(49) PV(50) PV(51) PV(52) PV(53)
  virtual void AddWindow(IWindow_s005e_4190* w);                 // +0xd8
  virtual void RemoveWindow(IWindow_s005e_4190* w);              // +0xdc
};
}
}
namespace EA {
namespace UTFWin {
class IWinProc_s005e_4190 {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5)
  virtual bool HandleMessage(IWindow_s005e_4190* w, void* msg);  // +0x18 slot 6
  PV(7) PV(8)
};
}
}
namespace EA {
template <typename T>
class AutoRefCount_s005e_4190 {
 public:
  T* mpObject;
  AutoRefCount_s005e_4190() : mpObject(0) {}
  ~AutoRefCount_s005e_4190() {
    if (mpObject)
      mpObject->Release();
  }
  AutoRefCount_s005e_4190& operator=(T* pObject) {
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
namespace EA {
template <typename T>
class RefCountVTemplate_s005e_4190 {
 public:
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
using EA::UTFWin::IWindow_s005e_4190;
class cProperty {
 public:
  bool* GetBool();
};
class cPropertyList_s005e_4190 {
 public:
  virtual int AddRef();                              // +0x00
  virtual int Release();                             // +0x04
  PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual bool HasProperty(uint32_t id);             // +0x1c 0x006a2470
  PV(8)
  virtual bool GetProperty(uint32_t id, void** out);  // +0x24
};
class cSPUILayout_s005e_4190 {
 public:
  PV(0)
  virtual int AddRef();   // +0x04
  virtual int Release();  // +0x08
  cSPUILayout_s005e_4190();
  bool Init(const EA::ResourceMan::Key_s005e_4190& key, bool visible, uint32_t parentID);  // 0x008120d0 (cSPUILayout::Init)
  IWindow_s005e_4190* FindWindowByID(uint32_t id, bool recursive);  // 0x008105b0 (cSPUILayout::FindWindowByID)
  void Shutdown(bool unused);  // 0x00811ad0 (cSPUILayout::Shutdown)
  uint32_t mData[5];
};
struct RawWStr {
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  uint32_t mAllocator;
};
struct WStrOut {
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  ~WStrOut() {
    if ((mpCapacity - mpBegin) > 1 && mpBegin)
      EASTL_allocator_deallocate(mpBegin);
  }
};
int SPUIHelpers_GetImageFromLayout(void* key);  // 0x00458de0 (cdecl)
char FUN_00806aa0(IWindow_s005e_4190* w, int image, int flag);  // 0x00806aa0 (cdecl)
struct UIMsg {
  uint32_t pad00[2];
  uint32_t id;       // +0x08
  uint32_t sub;      // +0x0c
  uint32_t arg;      // +0x10
  uint32_t pad14;
  IWindow_s005e_4190* src;      // +0x18 (source window; a RenderContext* for the draw message)
};
struct SPImageObj {
  virtual int AddRef();   // +0x00
  virtual int Release();  // +0x04
  uint32_t pad[6];        // +0x04..0x1b
  int mWidth;             // +0x1c
  int mHeight;            // +0x20
};
struct Painter {
  PV(0) PV(1) PV(2)
  virtual bool GetState(void* buf);          // +0x0c
  virtual void SetState(bool v, void* buf);  // +0x10
};
struct RenderContext_s005e_4190 {
  Painter* Begin2D(int flag);  // 0x0095bc10
  void End2D();                // 0x0095bb20
};
struct DrawTarget {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
  virtual void PrepareDraw(UIMsg* m);  // +0x20
};
double __cdecl iat_floor(double x);  // 0x011e0906
void FUN_00805940(void* p, float a, float b, float c, int d, int e, float f, float g, void* img, float h);  // 0x00805940
namespace SP {
class cString_s005e_4190 {
 public:
  cString_s005e_4190();                 // 0x006b5060
  ~cString_s005e_4190();                // 0x006b5240
  const wchar_t* GetText();  // 0x006b55c0
 private:
  uint32_t mField00;
  uint32_t mField04;
  uint32_t mField08;
  uint32_t mField0c;
  uint32_t mField10;
};
}
namespace SP {
void GetPropertyAsText(cPropertyList_s005e_4190* pProps, uint32_t id, cString_s005e_4190* pText);  // 0x006a1360
}
namespace SP {
class cWindowManager {
 public:
  PV(0)
  virtual IWindow_s005e_4190* GetMainWindow();  // +0x04
};
}
namespace SP {
cWindowManager* WindowManager();     // 0x0067caa0
}
struct cSPVerbLevelMirror {
  uint32_t mPad00[0x16];  // +0x00..0x57
  int mDisplayedLevel;    // +0x58
};
extern cSPVerbLevelMirror* g_p015ee298;  // 0x015ee298
namespace EA {
struct Variant_s005e_4190 {
  uint32_t mData0;
  uint32_t mData1;
  uint32_t mData2;
  uint32_t mData3;
  uint16_t mFlags;   // +0x10
  uint16_t mTypeId;  // +0x12
  Variant_s005e_4190(const void* pText) : mFlags(0), mTypeId(0) { Construct(0x13, 9, pText, 0x10, 1); }
  ~Variant_s005e_4190() {
    if (mFlags & 4)
      Destruct(false);  // 0x0093db80 (EA::Variant::Destruct)
  }
  bool Construct(unsigned short type, unsigned short subType, const void* pData, unsigned int size, unsigned int flags);  // 0x0093dd80
  void Destruct(bool arg);  // 0x0093db80
};  // namespace EA
}
namespace SP {
class cSPVerbIconRollover_s005e_4190 {
 public:
  cSPVerbIconRollover_s005e_4190();
  cSPVerbIconRollover_s005e_4190(uint32_t arg);
  static void* operator new(unsigned int size, const char* pName, int a, int b, int c, int d) {
    return ::operator new(size, pName, a, (unsigned)b, (const char*)c, d);
  }
  static void operator delete(void*, const char*, int, int, int, int) {}
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4) PV(5)
  PV(6)
  virtual void Slot7();   // +0x1c
  virtual void Slot8();   // +0x20
  void FUN_00605300();    // 0x00605300
  void FUN_006052f0();    // 0x006052f0
  void SetVisibility(uint32_t key, bool visible);                          // 0x006052c0
  void SetProperty(uint32_t key, const EA::Variant_s005e_4190& value, bool a, bool b);  // 0x00828c30
  void Layout();                                                           // 0x006053a0
  IWindow_s005e_4190* GetRootWindow();                                                // 0x00828100
  void SetPositionAndOffset(float x, float y, float w, float h);           // 0x008283a0
};
}
namespace SP {
class cSPEditorVerbIconData_s005e_4190 {
 public:
  virtual int AddRef();                      // +0x00
  virtual int Release();                     // +0x04
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
  virtual RawWStr* Slot20(void* out, int arg);  // +0x20
  virtual RawWStr* Slot24(void* out);           // +0x24
  PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
  uint32_t pad04[2];          // +0x04..0x0b
  bool mUseDescription;       // +0x0c
  bool mShowLevel;            // +0x0d
  bool mShowHotKey;           // +0x0e
  bool mShowZeroLevel;        // +0x0f
  bool mHotKeyEnabled;        // +0x10
  int mUnknown14;             // +0x14
  float mLevel;               // +0x18
  uint32_t pad1c[0xd];        // +0x1c..0x4f
  int mArrayIndex;            // +0x50
  uint32_t pad54[5];          // +0x54..0x67
  eastl::wstring mHotKeyText; // +0x68
  uint32_t pad74;             // +0x74
  uint32_t mUnknown78;        // +0x78
  int mUnknown7c;             // +0x7c
  uint32_t pad80[4];          // +0x80..0x8f
  void* mpImage90;            // +0x90
  void* mpImage94;            // +0x94
  uint32_t pad98[10];         // +0x98..0xbf
  cPropertyList_s005e_4190* mpPropList;  // +0xc0
};
}
namespace SP {
class cSPEditorVerbIcon_s005e_4190 : public EA::UTFWin::IWinProc_s005e_4190, public EA::RefCountVTemplate_s005e_4190<int> {
 public:
  class cVerbIconLinearInterpolationValue { public:
    float mTargetValue;
    float mCurrentValue;
    float mElapsedTime;
    float mInitialValue;
    float mDuration;
    void Reset(float value) {
      mInitialValue = value;
      mCurrentValue = value;
      mTargetValue = value;
      mDuration = 0.0f;
      mElapsedTime = 0.0f;
    }
    void Start(float from, float to, float duration) {
      mInitialValue = from;
      mCurrentValue = from;
      mTargetValue = to;
      mDuration = duration;
      mElapsedTime = 0.0f;
    }
  };
  class cVerbIconInterpolationValue { public:
    float mTargetValue;
    float mCurrentValue;
    float mElapsedTime;
    float mInitialValue;
    float mDuration;
    float mOverShoot;
    float mDampenPercent;
  };
  class cVerbIconMiddleInterpolationValue { public:
    float mEndValue;
    float mMiddleValue;
    float mCurrentValue;
    float mElapsedTime;
    float mInitialValue;
    float mMiddleStart;
    float mMiddleEnd;
    float mDuration;
  };
  class cVerbIconOscillatingAlpha { public:
    float mInitialValue;
    float mEndValue;
    float mCurrentValue;
    float mElapsedTime;
    float mDuration;
    float mSpeed;
    uint32_t mColor;
  };

  virtual bool HandleMessage(IWindow_s005e_4190* w, void* msg);
  PV(9) PV(10) PV(11) PV(12)
  virtual void SetLevel(float level);                  // +0x34 slot 13 0x005e2ec0
  virtual void UpdateLevelDisplay(float level);        // +0x38 slot 14
  PV(15)
  virtual bool IsToggled();                            // +0x40 slot 16
  virtual void Slot17();                               // +0x44 slot 17
  virtual void InitData(cSPEditorVerbIconData_s005e_4190* data);  // +0x48 slot 18 0x005e4190
  PV(19) PV(20)
  virtual void SetVerbID(uint32_t id);                 // +0x54

  EA::AutoRefCount_s005e_4190<cSPUILayout_s005e_4190> mLayout;                   // +0x0c
  EA::AutoRefCount_s005e_4190<IWindow_s005e_4190> mWinRoot;                      // +0x10
  EA::AutoRefCount_s005e_4190<IWindow_s005e_4190> mWinIcon;                      // +0x14
  EA::AutoRefCount_s005e_4190<IWindow_s005e_4190> mWinLevel;                     // +0x18
  EA::AutoRefCount_s005e_4190<IWindow_s005e_4190> mWinHighlight;                 // +0x1c
  EA::AutoRefCount_s005e_4190<IWindow_s005e_4190> mWinShortcutText;              // +0x20
  EA::AutoRefCount_s005e_4190<IWindow_s005e_4190> mWin24;                        // +0x24
  EA::AutoRefCount_s005e_4190<IWindow_s005e_4190> mWinFlashingGlow;              // +0x28
  EA::AutoRefCount_s005e_4190<IWindow_s005e_4190> mWinChargeDial;                // +0x2c
  EA::AutoRefCount_s005e_4190<IWindow_s005e_4190> mWinLevelPips[5];              // +0x30
  SPImageObj* mpImage44;                                   // +0x44
  EA::ResourceMan::Key_s005e_4190 mNormalKey;                         // +0x48
  uint32_t pad54[3];
  uint32_t mRolloverLayout;                                // +0x60
  int mState;                                              // +0x64
  bool mAnimate;                                           // +0x68
  bool mIsVisible;                                         // +0x69
  bool mUnknown6a;                                         // +0x6a
  bool mUnknown6b;                                         // +0x6b
  bool mUnknown6c;                                         // +0x6c
  bool mShowingLevel;                                      // +0x6d
  bool mLevelHighlightShown;                               // +0x6e
  bool mForceEnable;                                       // +0x6f
  bool mIsEnabled;                                         // +0x70
  bool mHasChargeDial;                                     // +0x71
  bool mUnknown72;                                         // +0x72
  bool mUnknown73;                                         // +0x73
  int mDirection;                                          // +0x74
  uint32_t pad78[4];
  Math::Rectangle_s005e_4190 mArea;                                   // +0x88
  cVerbIconLinearInterpolationValue mCharge;               // +0x98
  cVerbIconInterpolationValue mScaleX;                     // +0xac
  cVerbIconInterpolationValue mScaleY;                     // +0xc8
  cVerbIconLinearInterpolationValue mLevel;                // +0xe4
  cVerbIconInterpolationValue mUpgradeScale;               // +0xf8
  cVerbIconMiddleInterpolationValue mUpgradeHighlightFade;  // +0x114
  cVerbIconMiddleInterpolationValue mIconAlpha;            // +0x134
  cVerbIconOscillatingAlpha mFlashAlpha;                   // +0x154
  EA::AutoRefCount_s005e_4190<cSPEditorVerbIconData_s005e_4190> mIconData;       // +0x170
  EA::AutoRefCount_s005e_4190<cSPVerbIconRollover_s005e_4190> mRollover;         // +0x174
  uint32_t mBaseTextColor;                                 // +0x178
  uint32_t mCollectionID;                                  // +0x17c
  float mAspectRatio;                                      // +0x180

  __declspec(noinline) void UpdateRollover(IWindow_s005e_4190* parent);
};
}
// ---- items of slice s005e4190 end

// @ 0x005e04d0
float SP::AbilityLayoutData::LayoutLine(IWindow* window, const Key* key, float startY, uint32_t value, const Key* subKey, cString_s005d_fbb0* text, float number)
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

// @ 0x005e1c80
void SP::cVerbIconInterpolationValue_s005e_16c0::Init(float a, float b, float c, float d, float e)
{
    mInitial = a;
    mCurrent = a;
    mTarget = b;
    mDuration = c;
    mOverShoot = e;
    mDampen = d;
    mElapsed = 0.0f;
}

// @ 0x005e1cd0
int SP::cVerbIconInterpolationValue_s005e_16c0::IsAtTarget()
{
    if (mCurrent == mTarget && mElapsed >= mDuration)
        return 1;
    return 0;
}

// @ 0x005e1d00
void FUN_005e1d00(void* self)
{ (void)self; }

// @ 0x005e1e90
void FUN_005e1e90(void* self)
{ (void)self; }

// @ 0x005e1fa0
void SP::cSPEditorVerbIcon_s005e_16c0::SetFlag(char b)
{
    m6b = 1;
    m6a = b;
}

// @ 0x005e2000
void FUN_005e2000(void* self)
{ (void)self; }

// @ 0x005e2280
void FUN_005e2280(void* self)
{ (void)self; }

// @ 0x005e23b0
void FUN_005e23b0(void* self)
{ (void)self; }

// @ 0x005e2470
namespace SP {
void cSPEditorVerbIcon_s005e_2470::LayoutInit(EA::ResourceMan::Key_s005e_2470 key)
{
  mLayout = new (kEditorAllocName, 0, 0, 0, 0) cSPUILayout_s005e_2470();
  mLayout->Init(key, true, 0x5b598fa);
  mWinRoot = mLayout->FindWindowByID(0x902d3163, true);
  mWinIcon = mLayout->FindWindowByID(0x4976e19, true);
  mWinLevel = mLayout->FindWindowByID(0x6283c92, true);
  mWinHighlight = mLayout->FindWindowByID(0x4a4ff55, true);
  mWinShortcutText = mLayout->FindWindowByID(0x4a5cd15, true);
  mWin24 = mLayout->FindWindowByID(0x4c5fc88, true);
  mWinFlashingGlow = mLayout->FindWindowByID(0xf41a7da1, true);
  mWinChargeDial = mLayout->FindWindowByID(0x7c8ccc0, true);
  mArea = mWinRoot->GetArea();
  mAspectRatio = mArea.Width() / mArea.Height();
  for (uint32_t i = 0; i < 5; i++)
    mWinLevelPips[i] = mLayout->FindWindowByID(0x7d62860 + i, true);
  if (mWinLevel)
    mWinLevel->AddWinProc(this);
  if (mWinIcon)
    mWinIcon->AddWinProc(this);
  mWinRoot->AddWinProc(this);
  SPUIHelpers::GetLayoutManager()->GetWorldMainWindow(0x5b598fa)->AddWinProc(this);
  mScaleX.Reset(0.08f);
  mScaleY.Reset(0.08f);
  if (mWinHighlight) {
    mBaseTextColor =
        object_cast<EA::UTFWin::IWinText>(mWinHighlight, 0xf15f4bd)->GetTextColor();
  } else {
    mBaseTextColor = 0xffffffff;
    mShowingLevel = false;
    mLevelHighlightShown = false;
  }
}
}  // namespace SP

// @ 0x005e2860
namespace SP {
float cSPEditorVerbIcon_s005e_2470::GetLevel(bool current)
{
  if (!mShowingLevel)
    return 1.0f;
  if (current)
    return mLevel.mCurrentValue;
  return mIconData->mLevel;
}
}  // namespace SP

// @ 0x005e28c0
namespace SP {
float cSPEditorVerbIcon_s005e_2470::GetWidth(bool scaled)
{
  if (mWinRoot) {
    const Math::Rectangle& area = mWinRoot->GetArea();
    float width = area.x2 - area.x1;
    if (scaled)
      return SPUIHelpers::GetWindowScaleX(mWinRoot) * width;
    return width;
  }
  return 0.0f;
}
}  // namespace SP

// @ 0x005e2910
namespace SP {
float cSPEditorVerbIcon_s005e_2470::GetHeight(bool scaled)
{
  if (mWinRoot) {
    const Math::Rectangle& area = mWinRoot->GetArea();
    float height = area.y2 - area.y1;
    if (scaled)
      return SPUIHelpers::GetWindowScaleY(mWinRoot) * height;
    return height;
  }
  return 0.0f;
}
}  // namespace SP

// @ 0x005e2960
namespace SP {
void cSPEditorVerbIcon_s005e_2470::SetArea(Math::Rectangle area)
{
  float scaleX = mWinRoot ? SPUIHelpers::GetWindowScaleX(mWinRoot) : 1.0f;
  float scaleY = mWinRoot ? SPUIHelpers::GetWindowScaleY(mWinRoot) : 1.0f;
  if (scaleX != 1.0f || scaleY != 1.0f) {
    if (mDirection == kJustificationRight_s005e_2470 || mDirection == kJustificationLeft_s005e_2470)
      ScaleExtent(area.x1, area.x2, scaleX);
    else
      ScaleExtent(area.y1, area.y2, scaleY);
  }
  mWinRoot->SetArea(area);
}
}  // namespace SP

// @ 0x005e2a80
namespace SP {
void cSPEditorVerbIcon_s005e_2470::LayoutShutdown()
{
  SPUIHelpers::GetLayoutManager()->GetWorldMainWindow(0x5b598fa)->RemoveWinProc(this);
  if (mWinLevel) {
    mWinLevel->RemoveWinProc(this);
    mWinLevel = 0;
  }
  if (mWinIcon) {
    mWinIcon->RemoveWinProc(this);
    mWinIcon = 0;
  }
  if (mLayout) {
    mLayout->Shutdown(true);
    mLayout = 0;
  }
  if (mIconData) {
    mIconData->Shutdown();
    mIconData = 0;
  }
  if (mRollover) {
    mRollover->Shutdown();
    mRollover = 0;
  }
  mWinRoot = 0;
  mWinIcon = 0;
  mWinHighlight = 0;
  mWinShortcutText = 0;
  mWinChargeDial = 0;
  for (int i = 0; i < 5; i++)
    mWinLevelPips[i] = 0;
}
}  // namespace SP

// @ 0x005e2be0
namespace SP {
bool cSPEditorVerbIcon_s005e_2470::IsChargeReady()
{
  return mCharge.mCurrentValue == mCharge.mTargetValue &&
         mCharge.mElapsedTime >= mCharge.mDuration && mWinLevel && mIsEnabled &&
         (mWinLevel->GetFlags() & 2);
}
}  // namespace SP

// @ 0x005e2c30
namespace SP {
void cSPEditorVerbIcon_s005e_2470::OnClick()
{
  if (IsToggled()) {
    VerbIconClickMessage msg(mIconData, mCollectionID);
    MessageServer()->PostMSG(0x4aca143, &msg, 0);
  } else {
    VerbIconClickMessage msg(mIconData, mCollectionID);
    MessageServer()->PostMSG(0xd418db2d, &msg, 0);
  }
}
}  // namespace SP

// @ 0x005e2cc0
namespace SP {
void cSPEditorVerbIcon_s005e_2470::SetEnabled(bool enabled)
{
  if (mWinIcon) {
    mIsEnabled = enabled;
    mWinIcon->SetFlag(2, enabled);
  }
}
}  // namespace SP

// @ 0x005e2ce0
namespace SP {
void cSPEditorVerbIcon_s005e_2470::Hide()
{
  mState = 1;
  if (mIsVisible && mWinRoot)
    mWinRoot->SetFlag(1, false);
}
}  // namespace SP

// @ 0x005e2d10
namespace SP {
void cSPEditorVerbIcon_s005e_2470::SetIconData(cSPEditorVerbIconData_s005e_2470* data)
{
  if (mIconData != data) {
    mIconData = data;
    if (mWinIcon && mCharge.mCurrentValue == mCharge.mTargetValue &&
        mCharge.mElapsedTime >= mCharge.mDuration) {
      bool enable;
      if (!mIsEnabled)
        enable = false;
      else if (mForceEnable)
        enable = true;
      else if (!mWinLevel)
        enable = false;
      else
        enable = mIconData->HasVerb();
      mWinIcon->SetFlag(2, enable);
    }
    if (mShowingLevel) {
      if (mIconData->mLevel == -1.0f) {
        mLevelHighlightShown = false;
        if (mWinHighlight)
          mWinHighlight->SetFlag(1, false);
      } else {
        if (!mLevelHighlightShown && mWinHighlight) {
          mLevelHighlightShown = true;
          mWinHighlight->SetFlag(1, true);
        }
        float level = mIconData->mLevel;
        if (level != mLevel.mTargetValue)
          SetLevel(level);
      }
    }
  }
}
}  // namespace SP

// @ 0x005e2e50
namespace SP {
void cSPEditorVerbIcon_s005e_2470::EndCharge()
{
  if (mHasChargeDial) {
    mCharge.Reset(1.0f);
    if (mWinIcon) {
      SPUIHelpers::SetWindowImage(mWinIcon, &mNormalKey, true);
      mWinIcon->SetFlag(2, mIsEnabled);
    }
  }
}
}  // namespace SP

// @ 0x005e2ec0
namespace SP {
void cSPEditorVerbIcon_s005e_2470::SetLevel(float level)
{
  if (mAnimate) {
    float current = mLevel.mCurrentValue;
    if (level > current) {
      mState = 4;
      mLevel.Start(current, level, 0.7f);
      if (mIsVisible) {
        mUpgradeScale.Start(0.9f, 1.0f, 0.7f, 1.7f, 0.75f);
        mUpgradeHighlightFade.Start(0.0f, 0.75f, 0.0f, 0.4f, 0.6f, 0.7f);
        if (mWinShortcutText) {
          mWinShortcutText->SetShadeColor(0xff00ff00);
          SPUIHelpers::SetWindowAlpha(mWinShortcutText, 0.0f);
          mWinShortcutText->SetFlag(1, true);
        }
      }
    } else if (level < current) {
      mState = 5;
      mLevel.Start(current, level, 0.7f);
      if (mIsVisible) {
        mUpgradeScale.Start(1.1f, 1.0f, 0.7f, 1.7f, 0.75f);
        mUpgradeHighlightFade.Start(0.0f, 0.75f, 0.0f, 0.4f, 0.6f, 0.7f);
        if (mWinShortcutText) {
          mWinShortcutText->SetShadeColor(0xffff0000);
          SPUIHelpers::SetWindowAlpha(mWinShortcutText, 0.0f);
          mWinShortcutText->SetFlag(1, true);
        }
      }
    }
  } else {
    mLevel.Reset(level);
    UpdateLevelDisplay(level);
  }
}
}  // namespace SP

// @ 0x005e3180
namespace SP {
void cSPEditorVerbIcon_s005e_2470::EndFlashing()
{
  if (mWinFlashingGlow) {
    mFlashAlpha.Reset();
    SPUIHelpers::SetWindowAlpha(mWinFlashingGlow, mFlashAlpha.mCurrentValue);
  }
}
}  // namespace SP

// @ 0x005e31e0
namespace SP {
void cSPEditorVerbIcon_s005e_2470::Init(IWindow_s005e_2470* parent, EA::ResourceMan::Key_s005e_2470 key, uint32_t verbID, uint32_t rolloverLayout, bool animate, int direction, bool forceEnable, bool hasChargeDial)
{
  mAnimate = animate;
  mDirection = direction;
  mRolloverLayout = rolloverLayout;
  mHasChargeDial = hasChargeDial;
  mForceEnable = forceEnable;
  mIsVisible = true;
  LayoutInit(key);
  if (mWinRoot->GetParent())
    mWinRoot->GetParent()->RemoveWindow(mWinRoot);
  parent->AddWindow(mWinRoot);
  SetVerbID(verbID);
}
}  // namespace SP

// @ 0x005e4190
namespace SP {
void cSPEditorVerbIcon_s005e_4190::InitData(cSPEditorVerbIconData_s005e_4190* data)
{
  mIconData = data;
  if (data->mpPropList->HasProperty(0x4bf1b5f)) {
    if (!mUnknown6b || mUnknown6a) {
      cPropertyList_s005e_4190* props = data->mpPropList;
      if (props) {
        void* prop;
        if (props->GetProperty(0x4bf1b5f, &prop)) {
          if (*(unsigned short*)((char*)prop + 0x12) == 1)
            mUnknown6a = *((cProperty*)prop)->GetBool();
        }
      }
    }
  }
  if (data->mpPropList->HasProperty(0x5407d4b)) {
    cPropertyList_s005e_4190* props = data->mpPropList;
    if (props) {
      void* prop;
      if (props->GetProperty(0x5407d4b, &prop)) {
        if (*(unsigned short*)((char*)prop + 0x12) == 1)
          mUnknown73 = *((cProperty*)prop)->GetBool();
      }
    }
  }
  if ((mIsVisible && mUnknown6a) || mUnknown6c) {
    cSPVerbIconRollover_s005e_4190* r;
    if (mRolloverLayout)
      r = new (kEditorAllocName, 0, 0, 0, 0) cSPVerbIconRollover_s005e_4190(mRolloverLayout);
    else
      r = new (kEditorAllocName, 0, 0, 0, 0) cSPVerbIconRollover_s005e_4190();
    mRollover = r;
    if (mRollover)
      mRollover->Slot7();
  }
  mShowingLevel = mIconData->mShowLevel;
  if (mIconData->mLevel == -1.0f) {
    mLevel.Reset(0.0f);
  }
  if (mLevelHighlightShown) {
    if (mAnimate) {
      float lv = mIconData->mLevel;
      mLevel.mTargetValue = lv;
      mLevel.mInitialValue = 0.0f;
      mLevel.mCurrentValue = 0.0f;
      mLevel.mDuration = 0.7f;
      mLevel.mElapsedTime = 0.0f;
      mLevelHighlightShown = true;
    } else {
      float lv = mIconData->mLevel;
      mLevel.Reset(lv);
      mLevelHighlightShown = true;
    }
  } else {
    float lv = mIconData->mLevel;
    mLevel.Reset(lv);
  }
  if (!mShowingLevel)
    mLevelHighlightShown = false;
  if (mLevelHighlightShown) {
    if (mWinHighlight)
      mWinHighlight->SetFlag(1, true);
  } else {
    if (mWinHighlight)
      mWinHighlight->SetFlag(1, false);
  }
  if (mIsVisible) {
    int image;
    if (mIconData->mpImage94)
      image = SPUIHelpers_GetImageFromLayout(mIconData->mpImage94);
    else
      image = SPUIHelpers_GetImageFromLayout(mIconData->mpImage90);
    if (mWinIcon)
      FUN_00806aa0(mWinIcon, image, 0);
    if (mWinLevel)
      FUN_00806aa0(mWinLevel, image, 0);
    if (mIsVisible) {
      UpdateLevelDisplay(mIconData->mLevel);
      if (mWin24 && mIconData->mUnknown7c != -1)
        mWin24->SetText((const wchar_t*)mIconData->mHotKeyText.mpBegin);
    }
  }
  IWindow_s005e_4190* dial = mWinChargeDial;
  if (dial) {
    RawWStr tmp;
    RawWStr* r = mIconData->Slot20(&tmp, 0);
    dial->SetText(r->mpBegin);
    if ((tmp.mpCapacity - tmp.mpBegin) > 1 && tmp.mpBegin)
      EASTL_allocator_deallocate(tmp.mpBegin);
  }
  int idx = data->mArrayIndex;
  if (idx >= 0 && (unsigned)idx < 5) {
    IWindow_s005e_4190* pip = mWinLevelPips[idx];
    if (pip) {
      uint32_t color = pip->GetShadeColor();
      if (mWinIcon)
        mWinIcon->SetShadeColor(color);
      if (mWinLevel)
        mWinLevel->SetShadeColor(color);
    }
  }
}
}  // namespace SP

// @ 0x005e4560
namespace SP {
void cSPEditorVerbIcon_s005e_4190::UpdateRollover(IWindow_s005e_4190* parent)
{
  SP::cString_s005e_4190 text;
  if (mIconData->mShowZeroLevel) {
    g_p015ee298->mDisplayedLevel = (int)mIconData->mLevel;
    SP::GetPropertyAsText(mIconData->mpPropList, 0x62d00e8, &text);
    eastl::wstring levelText(text.GetText());
    mRollover->SetProperty(0x4d97708, EA::Variant_s005e_4190(&levelText), true, false);
  } else {
    static eastl::wstring sNoLevelText;
    mRollover->SetProperty(0x4d97708, EA::Variant_s005e_4190(&sNoLevelText), true, false);
  }

  WStrOut nameText;
  mRollover->SetProperty(0x331cc0e, EA::Variant_s005e_4190(mIconData->Slot20(&nameText, 0)), true, false);

  WStrOut descriptionText;
  mRollover->SetProperty(0x331cc0f, EA::Variant_s005e_4190(mIconData->Slot24(&descriptionText)), true, false);

  if (mIconData->mHotKeyEnabled && mIconData->mUnknown14 > -1) {
    mRollover->SetVisibility(0x4d97710, true);
    mRollover->SetProperty(0x4d97710, EA::Variant_s005e_4190(&mIconData->mHotKeyText), true, false);
  } else {
    mRollover->SetVisibility(0x4d97710, false);
  }

  mRollover->Slot8();
  mRollover->Layout();

  // The rollover is centred on the parent's area and sized from the main window's world area.
  const Math::Rectangle_s005e_4190& area = parent->GetArea();
  IWindow_s005e_4190* pParent = parent->GetParent();
  float centerY = (area.y2 + area.y1) * 0.5f;
  float centerX = (area.x2 + area.x1) * 0.5f;
  EA::Point client = pParent->ToClient(centerX, centerY);

  const Math::Rectangle_s005e_4190& realArea = SP::WindowManager()->GetMainWindow()->GetRealArea();
  float width = (realArea.x2 - realArea.x1) * 0.025f;
  float height = (realArea.y2 - realArea.y1) * 0.033333335f;
  IWindow_s005e_4190* pRoot = mRollover->GetRootWindow();
  if (pRoot) {
    const Math::Rectangle_s005e_4190& rootArea = pRoot->GetArea();
    width = -(rootArea.x2 - rootArea.x1) - width;
  }

  mRollover->FUN_006052f0();
  mRollover->SetPositionAndOffset(client.x, client.y, width, height);
}
}  // namespace SP

// @ 0x005e49c0
namespace SP {
bool cSPEditorVerbIcon_s005e_4190::HandleMessage(IWindow_s005e_4190* w, void* msgv)
{
  UIMsg* m = (UIMsg*)msgv;
  if (m->id == 10 && m->sub == 1) {
    IWindow_s005e_4190* src = m->src;
    if (src && (src == mWinLevel || src == mWinIcon)) {
      if (mUnknown6a && mRollover)
        UpdateRollover(w);
    } else {
      if (mRollover)
        mRollover->FUN_00605300();
    }
  }
  if (m->id == 6 && w->GetID() == 0x6283c92)
    Slot17();
  if (m->id == 0x287259f6)
    w->GetID();
  if (!mUnknown72 && !mUnknown73 && m->id == 1) {
    if (m->arg == mIconData->mUnknown78)
      Slot17();
    return false;
  } else if (m->id == 0xd) {
    uint32_t id = w->GetID();
    if ((id == 0x4976e19 || id == 0x6283c92) && mpImage44) {
      if (mCharge.mCurrentValue != mCharge.mTargetValue || !(mCharge.mElapsedTime >= mCharge.mDuration)) {
        void* c = w->Cast(0x8ed27e7a);
        DrawTarget* dt = c ? (DrawTarget*)((char*)c - 0x20c) : 0;
        RenderContext_s005e_4190* ctx = (RenderContext_s005e_4190*)m->src;
        dt->PrepareDraw(m);
        Painter* p = ctx->Begin2D(0);
        Math::Rectangle_s005e_4190 buf;
        bool saved = p->GetState(&buf);
        SPImageObj* img = mpImage44;
        if (img)
          img->AddRef();
        Math::Rectangle_s005e_4190 r;
        r.x1 = 0.0f;
        r.y1 = 0.0f;
        r.x2 = (float)img->mWidth;
        r.y2 = (float)img->mHeight;
        p->SetState(saved, &r);
        float hh = (float)img->mHeight * 0.5f;
        float hw = (float)img->mWidth * 0.5f;
        float mn;
        if (hh > hw)
          mn = hw;
        else
          mn = hh;
        float v = mCharge.mCurrentValue * g_015f0090 + g_0151a184;
        float fc = v - g_0151a184;
        double fl = iat_floor((double)((fc + 0.01f) / g_015f0090));
        if (v - ((float)fl * g_015f0090 + g_0151a184) > 1.52587890625e-05f)
          FUN_00805940(p, hw, hh, mn * 0.95f, g_0151a040, g_0151a040, g_0151a184,
                       (g_0151a184 - fc) + g_015f0090, img, g_015f00e0);
        p->SetState(saved, &buf);
        ctx->End2D();
        img->Release();
        return true;
      }
    }
  }
  return false;
}
}  // namespace SP
