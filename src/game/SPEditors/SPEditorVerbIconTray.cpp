// src/game/SPEditors/SPEditorVerbIconTray.cpp -- migrated from slice(s) s005e7830, s005e6b40, s005e5d40 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorVerbIconTray.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPEditorVerbIconTray.h"
#include "EA/ResourceMan/Key.h"
#include "SP/cPropertyList.h"
#include "SP/cSPEditorVerbIcon.h"
#include "SP/cSPEditorVerbIconData.h"
#include "SP/cString.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
#include "SP/eLayoutJustification.h"
#include "EA/UTFWin/IWinProc.h"
#include "EA/UTFWin/IWindow.h"
#include "EA/Variant.h"
#include "SP/cPropertyManager.h"
#include "cSPUILayout.h"
#include "cSPVerbIconRollover.h"

// ---- items of slice s005e5d40 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void _pv##n();
namespace Math {
struct Rectangle {
  float x1, y1, x2, y2;
  Rectangle() {}
  Rectangle(float left, float top, float right, float bottom)
      : x1(left), y1(top), x2(right), y2(bottom) {}
  Rectangle(const Rectangle& r) : x1(r.x1), y1(r.y1), x2(r.x2), y2(r.y2) {}
  Rectangle& operator=(const Rectangle& r) {
    x1 = r.x1;
    y1 = r.y1;
    x2 = r.x2;
    y2 = r.y2;
    return *this;
  }
  float Width() const { return x2 - x1; }
  float Height() const { return y2 - y1; }
};  // namespace Math
}
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
namespace eastl {
union EmptyString {
  uint32_t mUint32;
  wchar_t mEmpty16[1];
};
}
namespace eastl {
extern EmptyString gEmptyString;
}
namespace eastl {
inline unsigned int CharStrlen(const wchar_t* p) {
  const wchar_t* pCurrent = p;
  while (*pCurrent)
    ++pCurrent;
  return (unsigned int)(pCurrent - p);
}
}
namespace eastl {
struct allocator_s005e_5d40 {
  allocator_s005e_5d40() {}
};
}
namespace eastl {
class wstring {
 public:
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  allocator_s005e_5d40 mAllocator;

  wstring() { AllocateSelf(); }
  wstring(const wchar_t* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p); }
  wstring(const wstring& x);
  ~wstring() { DeallocateSelf(); }
  wstring& operator=(const wchar_t* p) { return assign(p, p + CharStrlen(p)); }
  wstring& assign(const wchar_t* pBegin, const wchar_t* pEnd);
  void RangeInitialize(const wchar_t* p);
  void AllocateSelf() {
    mpBegin = gEmptyString.mEmpty16;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + 1;
  }
  void DeallocateSelf() {
    if ((mpCapacity - mpBegin) > 1)
      DoFree(mpBegin);
  }
  void DoFree(wchar_t* p) {
    if (p)
      EASTL_allocator_deallocate(p);
  }
};
}
namespace eastl {
template <typename T>
class vector_s005e_5d40 {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  uint32_t mAllocator;
  vector_s005e_5d40() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~vector_s005e_5d40();
  unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
  T& operator[](unsigned int i) { return mpBegin[i]; }
};
}
namespace EA {
namespace UTFWin {
class IWinProc_s005e_5d40 {
 public:
  virtual ~IWinProc_s005e_5d40() {}
  PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
};
}
}
namespace EA {
namespace UTFWin {
class IWindow_s005e_5d40 {
 public:
  virtual int AddRef();                               // +0x00
  virtual int Release();                              // +0x04
  PV(2) PV(3)
  virtual IWindow_s005e_5d40* GetParent();                       // +0x10
  PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
  virtual const Math::Rectangle& GetArea();           // +0x38
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23)
  virtual void SetArea(const Math::Rectangle& area);  // +0x60
  PV(25) PV(26) PV(27) PV(28) PV(29) PV(30) PV(31) PV(32) PV(33) PV(34)
  PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44)
  PV(45) PV(46) PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53)
  virtual void AddWindow(IWindow_s005e_5d40* w);                 // +0xd8
  virtual void RemoveWindow(IWindow_s005e_5d40* w);              // +0xdc
};
}
}
namespace EA {
template <typename T>
class AutoRefCount_s005e_5d40 {
 public:
  T* mpObject;
  AutoRefCount_s005e_5d40() : mpObject(0) {}
  ~AutoRefCount_s005e_5d40() {
    if (mpObject)
      mpObject->Release();
  }
  AutoRefCount_s005e_5d40& operator=(T* pObject) {
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
class RefCountVTemplate_s005e_5d40 {
 public:
  RefCountVTemplate_s005e_5d40() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s005e_5d40() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace EA {
namespace ResourceMan {
struct Key_s005e_5d40 {
  uint32_t instanceID;
  uint32_t typeID;
  uint32_t groupID;
  Key_s005e_5d40() : instanceID(0), typeID(0), groupID(0) {}
  Key_s005e_5d40(uint32_t i, uint32_t t, uint32_t g) : instanceID(i), typeID(t), groupID(g) {}
};  // namespace ResourceMan
}
}
using EA::UTFWin::IWindow_s005e_5d40;
class cSPUILayout_s005e_5d40 {
 public:
  PV(0)
  virtual int AddRef();   // +0x04
  virtual int Release();  // +0x08
};
namespace SP {
class cString_s005e_5d40 {
 public:
  cString_s005e_5d40();
  ~cString_s005e_5d40();
  const wchar_t* c_str() const;  // 0x006b5240 (SP::cString::c_str)
  uint32_t mData[5];
};
}
namespace SP {
class cPropertyList_s005e_5d40 {
 public:
  PV(0)
  virtual int Release();                 // +0x04
  PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual bool HasProperty(uint32_t id);  // +0x1c 0x006a2470
};
}
namespace SP {
bool GetPropertyAsText(cPropertyList_s005e_5d40* list, uint32_t id, cString_s005e_5d40& out);
}
namespace SP {
namespace SPUIHelpers {
void SetWindowScale(IWindow_s005e_5d40* w, float scale);
}
}
namespace SP {
enum eLayoutJustification_s005e_5d40 {
  kJustificationNONE_s005e_5d40 = 0,
  kJustificationRight_s005e_5d40 = -401149879,
  kJustificationLeft_s005e_5d40 = 4109362,
  kJustificationTop_s005e_5d40 = 1080872010,
  kJustificationBottom_s005e_5d40 = -396051872,
};
}
namespace SP {
class cSPEditorVerbIconData_s005e_5d40 {
 public:
  PV(0)
  virtual int Release();  // +0x04
  char pad04[0xbc];
  cPropertyList_s005e_5d40* mpPropList;  // +0xc0

  eastl::wstring GetIconDescription();
};
}
namespace SP {
class cSPEditorVerbIcon_s005e_5d40 {
 public:
  virtual int AddRef();           // +0x00
  virtual int Release();          // +0x04
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual void LayoutShutdown();  // +0x28
  void SetIgnoreKeyPress(bool b);  // FUN_005e1f90
  void SetShowRollover(bool b);    // FUN_005e1fa0
  int GetState();                  // FUN_005e1fc0
  IWindow_s005e_5d40* GetWindow();            // 0x7f54d0
  void Disappear();  // 0x005e3d50 (SP::cSPEditorVerbIcon::Disappear)
  float GetHeight(bool scaled);    // FUN_005e2910
  float GetWidth(bool scaled);     // FUN_005e28c0
  Math::Rectangle GetArea();       // FUN_005e2890
  void SetArea(Math::Rectangle area);  // 0x005e2960 (SP::cSPEditorVerbIcon::SetArea)
};
}
namespace SP {
class cSPVerbIconRollover {
 public:
  PV(0)
  virtual int Release();  // +0x04
};
}
namespace SP {
class cSPEditorVerbIconTray_s005e_5d40 : public EA::UTFWin::IWinProc_s005e_5d40, public EA::RefCountVTemplate_s005e_5d40<int> {
 public:
  struct cVerbIconInterpolationValue {
    float mTargetValue;
    float mCurrentValue;
    float mElapsedTime;
    float mInitialValue;
    float mDuration;
    float mOverShoot;
    float mDampenPercent;
    cVerbIconInterpolationValue()
        : mCurrentValue(1.0f), mElapsedTime(1.0f), mInitialValue(0.0f), mDuration(1.0f),
          mOverShoot(0.0f), mDampenPercent(0.0f) {}
  };

  cSPEditorVerbIconTray_s005e_5d40();
  ~cSPEditorVerbIconTray_s005e_5d40();

  // vtable slots 9.. (after the IWinProc slots)
  PV(9) PV(10) PV(11) PV(12) PV(13) PV(14)
  virtual void LayoutTray();                                  // +0x3c 0x005e6400

  eastl::vector_s005e_5d40<EA::AutoRefCount_s005e_5d40<cSPEditorVerbIcon_s005e_5d40> > mVerbIcons;  // +0x0c
  uint32_t pad1c;                                             // +0x1c
  EA::AutoRefCount_s005e_5d40<cSPEditorVerbIconData_s005e_5d40> mOverrideData;      // +0x20
  void* mpOwner;                                              // +0x24
  EA::AutoRefCount_s005e_5d40<cSPUILayout_s005e_5d40> mLayout;                      // +0x28
  EA::AutoRefCount_s005e_5d40<IWindow_s005e_5d40> mWinRoot;                         // +0x2c
  EA::AutoRefCount_s005e_5d40<IWindow_s005e_5d40> mWinIconPanel;                    // +0x30
  EA::AutoRefCount_s005e_5d40<IWindow_s005e_5d40> mWinLevel;                        // +0x34
  EA::AutoRefCount_s005e_5d40<IWindow_s005e_5d40> mWinIcon;                         // +0x38
  EA::AutoRefCount_s005e_5d40<IWindow_s005e_5d40> mWinOverride;                     // +0x3c
  EA::AutoRefCount_s005e_5d40<cPropertyList_s005e_5d40> mVerbTrayProperties;        // +0x40
  EA::ResourceMan::Key_s005e_5d40 mIconKey;                              // +0x44
  uint32_t mImageGroup;                                       // +0x50
  EA::ResourceMan::Key_s005e_5d40 mLayoutKey;                            // +0x54
  EA::ResourceMan::Key_s005e_5d40 mTrayKey;                              // +0x60
  uint32_t mSoundKey;                                         // +0x6c
  bool mShowIcons;                                            // +0x70
  bool mAnimateIcons;                                         // +0x71
  int mResizeStyle;                                           // +0x74
  int mLayoutJustification;                                   // +0x78
  EA::ResourceMan::Key_s005e_5d40 mRolloverLayout;                       // +0x7c
  float mLevelTotal;                                          // +0x88
  float mMaxLevel;                                            // +0x8c
  bool mShowLevel;                                            // +0x90
  bool pad91;
  bool mShowLevelText;                                        // +0x92
  bool mShowLevelBar;                                         // +0x93
  uint32_t mBaseTextColor;                                    // +0x94
  bool mShowVerbIconWhenCollapsed;                            // +0x98
  float mDisplayedLevel;                                      // +0x9c
  float mOriginalWidth;                                       // +0xa0
  float mOriginalHeight;                                      // +0xa4
  Math::Rectangle mMaxArea;                                   // +0xa8
  Math::Rectangle mGutters;                                   // +0xb8
  int mAbilityCount;                                          // +0xc8
  float mVerbIconAspectRatio;                                 // +0xcc
  float mIconHeight;                                          // +0xd0
  float mIconWidth;                                           // +0xd4
  bool mDoIconLevelsExist;                                    // +0xd8
  bool mOverrideAggregate;                                    // +0xd9
  bool mIsEnabled;                                            // +0xda
  bool mIsHealthBar;                                          // +0xdb
  bool mIgnoreKeyPress;                                       // +0xdc
  uint32_t mAlertID;                                          // +0xe0
  bool mIsPlayMode;                                           // +0xe4
  bool mSetHaveChargeDials;                                   // +0xe5
  bool mSetForceEnabled;                                      // +0xe6
  bool mIconsHaveChargeDials;                                 // +0xe7
  bool mIconsForceEnabled;                                    // +0xe8
  cVerbIconInterpolationValue mBaseStat;                      // +0xec
  float mBaseStatTarget;                                      // +0x108
  bool mShowRollover;                                         // +0x10c
  EA::AutoRefCount_s005e_5d40<cSPVerbIconRollover> mRollover;            // +0x110
  uint32_t mAbilityArray;                                     // +0x114
  uint32_t mRepresentativeAnimation;                          // +0x118
  EA::AutoRefCount_s005e_5d40<cSPVerbIconRollover> mCollection;          // +0x11c

  void SetRolloverLayout(EA::ResourceMan::Key_s005e_5d40 key);
  void SetLayoutKey(EA::ResourceMan::Key_s005e_5d40 key);
  void SetLayoutID(uint32_t id);
  void SetHaveChargeDials(bool b);
  void SetForceEnabled(bool b);
  float GetMaxVerbWidth();  // 0x005e5f10 (SP::cSPEditorVerbIconTray::GetMaxVerbWidth)
  float GetMaxVerbHeight();  // 0x005e5fa0 (SP::cSPEditorVerbIconTray::GetMaxVerbHeight)
  void SetVerbIconSize();  // 0x005e6030 (SP::cSPEditorVerbIconTray::SetVerbIconSize)
  void RemoveVerbIconInternal(int index);  // 0x005e60d0 (SP::cSPEditorVerbIconTray::RemoveVerbIconInternal)
  void SetShowRollover(bool b);
  void SetIgnoreKeyPress(bool b);
  void SetParent(IWindow_s005e_5d40* parent, bool resize);
  float GetHeight();
  void SetMaxArea(const Math::Rectangle& area);
  eastl::wstring GetTrayName(int unused);  // 0x005e6a60 (SP::cSPEditorVerbIconTray::GetTrayName)
  eastl::wstring GetTrayDescription();
};
}
// ---- items of slice s005e5d40 end

// ---- items of slice s005e6b40 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace Math {
struct Rectangle_s005e_6b40 {
  float x1, y1, x2, y2;
  float Width() const { return x2 - x1; }
  float Height() const { return y2 - y1; }
};  // namespace Math
}
namespace EA {
namespace UTFWin {
class IWinProc_s005e_6b40;
}
}
namespace EA {
namespace UTFWin {
class IWindow_s005e_6b40 {
 public:
  virtual int AddRef();   // +0x00
  virtual int Release();  // +0x04
  PV(2) PV(3) PV(4)
  PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
  virtual const Math::Rectangle_s005e_6b40& GetArea();  // +0x38
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23)
  virtual void SetArea(const Math::Rectangle_s005e_6b40& area);  // +0x60
  PV(25) PV(26) PV(27) PV(28) PV(29) PV(30) PV(31) PV(32) PV(33)
  virtual void AddWindow(IWindow_s005e_6b40* w);     // +0xd8
  virtual void RemoveWindow(IWindow_s005e_6b40* w);  // +0xdc
};
}
}
namespace EA {
namespace UTFWin {
class IWinProc_s005e_6b40 {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
};
}
}
using EA::UTFWin::IWindow_s005e_6b40;
using EA::UTFWin::IWinProc_s005e_6b40;
namespace SP {
class cSPEditorVerbIconTray_s005e_6b40;
}
namespace SP {
class cSPVerbIconRollover_s005e_6b40 {
 public:
  PV(0)
  virtual int Release();  // +0x04
  void MarkDirty();
};
}
namespace SP {
class cSPEditorVerbIcon_s005e_6b40 {
 public:
  PV(0)
  virtual int Release();
  void UpdateRollover(IWindow_s005e_6b40* parent);
  void RefreshLevel();
};
}
namespace SP {
class cSPEditorVerbIconTray_s005e_6b40 : public IWinProc_s005e_6b40 {
 public:
  char pad00[0x20];
  cSPEditorVerbIcon_s005e_6b40* mpOwner;  // +0x24
  char pad28[0x10];
  IWindow_s005e_6b40* mWinIcon;            // +0x38
  char pad3c[0xd0];
  bool mShowRollover;           // +0x10c
  char pad10d[3];
  cSPVerbIconRollover_s005e_6b40* mRollover;  // +0x110

  bool CheckMessage(IWindow_s005e_6b40* w, void* msg);
  void DoMessage(IWindow_s005e_6b40* w);
  void SetLevelText(float level);  // 0x005e7030 (SP::cSPEditorVerbIconTray::SetLevelText)
  void Update(float dt);  // 0x005e71d0 (SP::cSPEditorVerbIconTray::Update)
  void SetBaseStat(float value);  // 0x005e75c0 (SP::cSPEditorVerbIconTray::SetBaseStat)
  void Shutdown();  // 0x005e76b0 (SP::cSPEditorVerbIconTray::Shutdown)
};
}
// ---- items of slice s005e6b40 end

// ---- items of slice s005e7830 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new[](size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line); // 0xf473a0
inline void* operator new(size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line)
{ return operator new[](size, name, flags, debugFlags, file, line); }
namespace Math {
struct Rectangle_s005e_7830 {
  float x1, y1, x2, y2;
  Rectangle_s005e_7830() {}
  Rectangle_s005e_7830(const Rectangle_s005e_7830& r) : x1(r.x1), y1(r.y1), x2(r.x2), y2(r.y2) {}
};  // namespace Math
}
namespace EA {
namespace ResourceMan {
struct Key_s005e_7830 {
  uint32_t instanceID;
  uint32_t typeID;
  uint32_t groupID;
  Key_s005e_7830() : instanceID(0), typeID(0), groupID(0) {}

};  // namespace ResourceMan
}
}
namespace EA {
template <typename T>
class AutoRefCount_s005e_7830 {
 public:
  T* mpObject;
  AutoRefCount_s005e_7830() : mpObject(0) {}
  ~AutoRefCount_s005e_7830() { if (mpObject) mpObject->Release(); }
  T** AsOutParam() {
    if (mpObject) { T* pOld = mpObject; mpObject = 0; pOld->Release(); }
    return &mpObject;
  }
  AutoRefCount_s005e_7830& operator=(T* pObject) {
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
namespace UTFWin {
class IWinProc_s005e_7830 {
 public:
  virtual ~IWinProc_s005e_7830() {}
  PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
};
}
}
namespace EA {
namespace UTFWin {
class IWindow_s005e_7830 {
 public:
  virtual int AddRef();                                // +0x00
  virtual int Release();                               // +0x04
  PV(2)
  virtual IWindow_s005e_7830* FindChild(uint32_t id);             // +0x0c
  PV(4) PV(5) PV(6) PV(7) PV(8)
  virtual uint32_t GetColor();                         // +0x24
  PV(10) PV(11) PV(12) PV(13)
  virtual const Math::Rectangle_s005e_7830& GetArea();            // +0x38
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
  virtual void SetFlag(uint32_t flag, bool value);     // +0x7c
  PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44)
  PV(45) PV(46) PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58)
  PV(59) PV(60) PV(61) PV(62) PV(63) PV(64)
  virtual void AddWinProc(IWinProc_s005e_7830* p);                // +0x104
};
}
}
namespace EA {
template <typename T>
class RefCountVTemplate_s005e_7830 {
 public:
  RefCountVTemplate_s005e_7830() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s005e_7830() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
using EA::UTFWin::IWindow_s005e_7830;
using EA::ResourceMan::Key_s005e_7830;
using EA::AutoRefCount_s005e_7830;
class Property {
 public:
  bool* GetBool();  // 0x41e920
  char pad[0x10];
  uint16_t flags;   // +0x10
  uint16_t type;    // +0x12
};
namespace SP {
class cPropertyList_s005e_7830 {
 public:
  PV(0)
  virtual int Release();                                   // +0x04
  PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual bool HasProperty(uint32_t id);                   // +0x1c 0x006a2470
  PV(8)
  virtual bool GetProperty(uint32_t id, Property*& out);   // +0x24
};
}
namespace SP {
class cPropertyManager_s005e_7830 {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, cPropertyList_s005e_7830** out);  // +0x2c
};
}
namespace SP {
cPropertyManager_s005e_7830* PropertyManager();  // 0x67de30
}
namespace SP {
bool GetPropertyAsKey(cPropertyList_s005e_7830* list, uint32_t id, Key_s005e_7830& out);                      // 0x6a1250
}
namespace SP {
bool GetPropertyAsKeyInstance(cPropertyList_s005e_7830* list, uint32_t id, uint32_t& out);         // 0x6a12a0
}
namespace SP {
bool GetKeyArray(cPropertyList_s005e_7830* list, uint32_t id, int* count, Key_s005e_7830** arr);              // 0x6a0ae0
}
namespace SP {
inline void GetBoolProp(cPropertyList_s005e_7830* l, uint32_t id, bool& out) {
  Property* p;
  if (l && l->GetProperty(id, p) && p->type == 1) out = *p->GetBool();
}
}
namespace SP {
class cSPUILayout {
 public:
  uint32_t mPad[5];
  cSPUILayout();                                                     // 0x810000
  PV(0)
  virtual int AddRef();                                              // +0x04
  virtual int Release();                                             // +0x08
  void Init(const Key_s005e_7830* key, int a, uint32_t b);                      // 0x8120d0
  IWindow_s005e_7830* FindWindowByID(uint32_t id, int flag);                    // 0x8105b0
};
}
namespace SP {
namespace SPUIHelpers {
uint32_t GetImageFromLayout(uint32_t id);                            // 0x458de0
}
}
namespace SP {
namespace SPUIHelpers {
bool SetDrawableImage(IWindow_s005e_7830* w, uint32_t image, int index);        // 0x8068d0
}
}
namespace SP {
enum eLayoutJustification_s005e_7830 { kJustificationRight_s005e_7830 = -401149879 };
}
namespace SP {
class cSPEditorVerbIcon_s005e_7830 {
 public:
  virtual int AddRef();
  virtual int Release();
};
}
namespace SP {
class cSPVerbIconRollover_s005e_7830 {
 public:
  char mPad[0x74];
  cSPVerbIconRollover_s005e_7830();                       // 0x6051d0
  cSPVerbIconRollover_s005e_7830(uint32_t id);            // 0x605220
  virtual int AddRef();                        // +0x00
  virtual int Release();                       // +0x04
  PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual void Setup();                        // +0x1c
};
}
namespace SP {
template <typename T>
struct IconVector {
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  uint32_t mAllocator;
  unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
  struct RawRef { void* p; };
  void insert(T* pos, unsigned int n, const RawRef& value);   // 0x5e7400
  void erase(T* first, T* last);                         // 0xe25bd0
  void resize(unsigned int n) {
    RawRef value;
    value.p = 0;
    if (n > size()) {
      insert(mpEnd, n - size(), value);
    } else
      erase(mpBegin + n, mpEnd);
  }
};
}
namespace SP {
class cSPEditorVerbIconTray_s005e_7830 : public EA::UTFWin::IWinProc_s005e_7830, public EA::RefCountVTemplate_s005e_7830<int> {
 public:
  struct cVerbIconInterpolationValue {
    float mTargetValue, mCurrentValue, mElapsedTime, mInitialValue, mDuration, mOverShoot, mDampenPercent;
    void Init(float a, float b, float c, float d, float e);   // 0x5e1c80
  };

  PV(9)
  virtual void SetParent(IWindow_s005e_7830* parent, bool resize);        // +0x28
  PV(11) PV(12) PV(13) PV(14)
  virtual void LayoutTray();                                   // +0x3c 0x005e6400

  IconVector<AutoRefCount_s005e_7830<cSPEditorVerbIcon_s005e_7830> > mVerbIcons;     // +0x0c
  uint32_t pad1c;                                              // +0x1c
  void* mOverrideData;                                         // +0x20
  void* mpOwner;                                               // +0x24
  AutoRefCount_s005e_7830<cSPUILayout> mLayout;                           // +0x28
  AutoRefCount_s005e_7830<IWindow_s005e_7830> mWinRoot;                              // +0x2c
  AutoRefCount_s005e_7830<IWindow_s005e_7830> mWinIconPanel;                         // +0x30
  AutoRefCount_s005e_7830<IWindow_s005e_7830> mWinLevel;                             // +0x34
  AutoRefCount_s005e_7830<IWindow_s005e_7830> mWinIcon;                              // +0x38
  AutoRefCount_s005e_7830<IWindow_s005e_7830> mWinText;                              // +0x3c
  AutoRefCount_s005e_7830<cPropertyList_s005e_7830> mVerbTrayProperties;             // +0x40
  Key_s005e_7830 mIconKey;                                                // +0x44
  uint32_t mSoundKey;                                          // +0x50
  Key_s005e_7830 mLayoutKey;                                              // +0x54
  Key_s005e_7830 mTrayKey;                                                // +0x60
  uint32_t mIconID;                                            // +0x6c
  bool mShowIcons;                                             // +0x70
  bool mAnimateIcons;                                          // +0x71
  int mResizeStyle;                                            // +0x74
  int mLayoutJustification;                                    // +0x78
  Key_s005e_7830 mRolloverLayout;                                         // +0x7c
  float mLevelTotal;                                           // +0x88
  float mMaxLevel;                                             // +0x8c
  bool mShowLevel;                                             // +0x90
  bool mRolloverShowLevel;                                     // +0x91
  bool mShowPercent;                                           // +0x92
  bool mShowPercentInRollover;                                 // +0x93
  uint32_t mBaseTextColor;                                     // +0x94
  bool mShowVerbIconWhenCollapsed;                             // +0x98
  float mDisplayedLevel;                                       // +0x9c
  float mOriginalWidth;                                        // +0xa0
  float mOriginalHeight;                                       // +0xa4
  Math::Rectangle_s005e_7830 mMaxArea;                                    // +0xa8
  Math::Rectangle_s005e_7830 mGutters;                                    // +0xb8
  int mAbilityCount;                                           // +0xc8
  float mVerbIconAspectRatio;                                  // +0xcc
  float mIconHeight;                                           // +0xd0
  float mIconWidth;                                            // +0xd4
  bool mDoIconLevelsExist;                                     // +0xd8
  bool mOverrideAggregate;                                     // +0xd9
  bool mIsEnabled;                                             // +0xda
  bool mIsHealthBar;                                           // +0xdb
  bool mIgnoreKeyPress;                                        // +0xdc
  uint32_t mAlertID;                                           // +0xe0
  bool field_E4;                                               // +0xe4
  bool mSetHaveChargeDials;                                    // +0xe5
  bool mSetForceEnabled;                                       // +0xe6
  bool mIconsHaveChargeDials;                                  // +0xe7
  bool mIconsForceEnabled;                                     // +0xe8
  uint32_t mOverrideType;                                      // +0xec
  cVerbIconInterpolationValue mBaseStat;                       // +0xf0
  bool mShowRollover;                                          // +0x10c
  AutoRefCount_s005e_7830<cSPVerbIconRollover_s005e_7830> mRollover;                 // +0x110
  uint32_t* mAbilityArray;                                     // +0x114
  uint32_t mRepresentativeAnimation;                           // +0x118

  void SetVerbIconSize();                                      // 0x5e6030
  void SetLevelText(float level);                              // 0x5e7030
  void Init(IWindow_s005e_7830* parent, Key_s005e_7830 trayKey, uint32_t justification, bool animateIcons, int unused);   // @ 0x5e7830
};
}
namespace SP {
inline IWindow_s005e_7830* FindChildOrNull(IWindow_s005e_7830* w, uint32_t id) { return w ? w->FindChild(id) : 0; }
}
namespace SP {
inline uint32_t GetLevelColor(IWindow_s005e_7830* w) { return FindChildOrNull(w, 0xf15f4bd)->GetColor(); }
}
// ---- items of slice s005e7830 end

// @ 0x005e5e40
void SP::cSPEditorVerbIconTray::SetRolloverLayout(EA::ResourceMan::Key key)
{
  mVerbLayout.mGroup = key.mInstance;
  mRolloverLayout.mType = 0x40464100;
  mRolloverLayout.mInstance = 0x510a95b;
}



// @ 0x005e5e60
namespace SP {
void cSPEditorVerbIconTray_s005e_5d40::SetLayoutKey(EA::ResourceMan::Key_s005e_5d40 key)
{
  mLayoutKey.instanceID = key.instanceID;
  mLayoutKey.groupID = 0x40464100;
  mLayoutKey.typeID = 0x510a95b;
}
}  // namespace SP



// @ 0x005e5e80
namespace SP {
void cSPEditorVerbIconTray_s005e_5d40::SetLayoutID(uint32_t id)
{
  mLayoutKey.instanceID = id;
  mLayoutKey.groupID = 0x40464100;
  mLayoutKey.typeID = 0x510a95b;
}
}  // namespace SP



// @ 0x005e5ea0
namespace SP {
void cSPEditorVerbIconTray_s005e_5d40::SetHaveChargeDials(bool b)
{
  mSetHaveChargeDials = true;
  mIconsHaveChargeDials = b;
}
}  // namespace SP



// @ 0x005e5ec0
namespace SP {
void cSPEditorVerbIconTray_s005e_5d40::SetForceEnabled(bool b)
{
  mSetForceEnabled = true;
  mIconsForceEnabled = b;
}
}  // namespace SP



// @ 0x005e5f10
namespace SP {
float cSPEditorVerbIconTray_s005e_5d40::GetMaxVerbWidth()
{
  float width;
  if (mResizeStyle == 1 && mWinIconPanel)
    width = mWinIconPanel->GetArea().Width();
  else
    width = mMaxArea.Width() - mGutters.x1 - mGutters.x2;
  if (mLayoutJustification == kJustificationRight_s005e_5d40 || mLayoutJustification == kJustificationLeft_s005e_5d40)
    return width / mVerbIcons.size();
  return width;
}
}  // namespace SP



// @ 0x005e5fa0
namespace SP {
float cSPEditorVerbIconTray_s005e_5d40::GetMaxVerbHeight()
{
  float height;
  if (mResizeStyle == 1 && mWinIconPanel)
    height = mWinIconPanel->GetArea().Height();
  else
    height = mMaxArea.Height() - mGutters.y1 - mGutters.y2;
  if (mLayoutJustification == kJustificationRight_s005e_5d40 || mLayoutJustification == kJustificationLeft_s005e_5d40)
    return height;
  return height / mVerbIcons.size();
}
}  // namespace SP



// @ 0x005e6030
namespace SP {
void cSPEditorVerbIconTray_s005e_5d40::SetVerbIconSize()
{
  mIconWidth = GetMaxVerbWidth();
  float height = GetMaxVerbHeight();
  mIconHeight = height;
  if (mLayoutJustification == kJustificationRight_s005e_5d40 || mLayoutJustification == kJustificationLeft_s005e_5d40) {
    if (mVerbIconAspectRatio != -1.0f)
      mIconWidth = mVerbIconAspectRatio * height;
    else
      mIconWidth = 0.0f;
  } else {
    if (mVerbIconAspectRatio != -1.0f)
      mIconHeight = mIconWidth / mVerbIconAspectRatio;
    else
      mIconHeight = 0.0f;
  }
}
}  // namespace SP



// @ 0x005e60d0
namespace SP {
void cSPEditorVerbIconTray_s005e_5d40::RemoveVerbIconInternal(int index)
{
  if (mVerbIcons[index]) {
    if (mAnimateIcons && mShowIcons) {
      if (mVerbIcons[index]->GetState() != 0 && mVerbIcons[index]->GetState() != 1)
        mVerbIcons[index]->Disappear();
    } else {
      if (mWinIconPanel)
        mWinIconPanel->RemoveWindow(mVerbIcons[index]->GetWindow());
      mVerbIcons[index]->LayoutShutdown();
      mVerbIcons[index] = 0;
    }
  }
}
}  // namespace SP



// @ 0x005e6170
void SP::cSPEditorVerbIconTray::SetShowRollover(bool b)
{
  mShowRollover = b;
  int count = mVerbIcons.size();
  for (int i = 0; i < count; i++)
    mVerbIcons[i]->SetShowRollover(b);
}



// @ 0x005e61b0
void SP::cSPEditorVerbIconTray::SetIgnoreKeyPress(bool b)
{
  mDoIconLevelsExist = b;
  int count = mVerbIcons.size();
  for (int i = 0; i < count; i++) {
    if (mVerbIcons[i])
      mVerbIcons[i]->SetIgnoreKeyPress(b);
  }
}



// @ 0x005e6200
namespace SP {
void cSPEditorVerbIconTray_s005e_5d40::SetParent(IWindow_s005e_5d40* parent, bool resize)
{
  if (mWinRoot->GetParent())
    mWinRoot->GetParent()->RemoveWindow(mWinRoot);
  if (parent) {
    parent->AddWindow(mWinRoot);
    if (resize) {
      Math::Rectangle area = mWinRoot->GetArea();
      float width = area.Width();
      float height = area.Height();
      area.x1 = 0.0f;
      area.x2 = width;
      area.y1 = 0.0f;
      area.y2 = height;
      mWinRoot->SetArea(area);
      if (mResizeStyle == 2 || mResizeStyle == 1) {
        Math::Rectangle parentArea = parent->GetArea();
        if (mLayoutJustification == kJustificationRight_s005e_5d40 ||
            mLayoutJustification == kJustificationLeft_s005e_5d40) {
          mMaxArea.x1 = 0.0f;
          mMaxArea.x2 = parentArea.Width();
          if (mMaxArea.Height() > parentArea.Height()) {
            mMaxArea.y1 = 0.0f;
            mMaxArea.y2 = parentArea.Height();
          }
        } else {
          float parentWidth = parentArea.Width();
          mMaxArea.y1 = 0.0f;
          mMaxArea.y2 = parentWidth;
          if (mMaxArea.Width() > parentWidth) {
            mMaxArea.x1 = 0.0f;
            mMaxArea.x2 = parentWidth;
          }
        }
        SetVerbIconSize();
      }
    }
    LayoutTray();
  }
}
}  // namespace SP



// @ 0x005e6390
namespace SP {
float cSPEditorVerbIconTray_s005e_5d40::GetHeight()
{
  return mWinRoot->GetArea().Height();
}
}  // namespace SP



// @ 0x005e63b0
namespace SP {
void cSPEditorVerbIconTray_s005e_5d40::SetMaxArea(const Math::Rectangle& area)
{
  mMaxArea = area;
  SetVerbIconSize();
  mWinRoot->SetArea(area);
  LayoutTray();
}
}  // namespace SP



// @ 0x005e6400
namespace SP {
void cSPEditorVerbIconTray_s005e_5d40::LayoutTray()
{
  if ((mShowIcons && mWinIconPanel) || mWinOverride) {
    float x = 0.0f;
    float y = 0.0f;
    if (mWinOverride) {
      x = mWinOverride->GetArea().Width();
    } else {
      float left;
      float top;
      int count = mVerbIcons.size();
      for (int i = 0; i < count; i++) {
        if (mVerbIcons[i].mpObject) {
          cSPEditorVerbIcon_s005e_5d40* icon = mVerbIcons[i];
          float iconHeight = icon->GetHeight(true);
          float iconWidth = mVerbIcons[i]->GetWidth(true);
          float areaWidth = mVerbIcons[i]->GetArea().Width();
          float areaHeight = mVerbIcons[i]->GetArea().Height();
          if (mLayoutJustification == kJustificationRight_s005e_5d40 ||
              mLayoutJustification == kJustificationLeft_s005e_5d40) {
            top = 0.0f;
            left = x;
            x += iconWidth;
          } else if (mLayoutJustification == kJustificationTop_s005e_5d40 ||
                     mLayoutJustification == kJustificationBottom_s005e_5d40) {
            left = 0.0f;
            top = y;
            y += iconHeight;
          }
          icon->SetArea(Math::Rectangle(left, top, left + areaHeight, top + areaWidth));
        }
      }
    }
    Math::Rectangle area = mMaxArea;
    float height;
    if (mLayoutJustification == kJustificationRight_s005e_5d40 || mLayoutJustification == kJustificationLeft_s005e_5d40)
      height = area.Height();
    else
      height = mGutters.y2 + mGutters.y1 + y;
    float width;
    if (mLayoutJustification == kJustificationTop_s005e_5d40 || mLayoutJustification == kJustificationBottom_s005e_5d40)
      width = area.Width();
    else
      width = mGutters.x2 + mGutters.x1 + x;
    if (mLayoutJustification == kJustificationRight_s005e_5d40)
      area.x1 = area.x2 - width;
    else if (mLayoutJustification == kJustificationBottom_s005e_5d40)
      area.y1 = area.y2 - height;
    area.x2 = area.x1 + width;
    area.y2 = area.y1 + height;
    mWinRoot->SetArea(area);
  } else if (mResizeStyle != 0 && mWinRoot) {
    Math::Rectangle area = mWinRoot->GetArea();
    float width = area.Width();
    float height = area.Height();
    float scaleX = mMaxArea.Width() / width;
    float scaleY = mMaxArea.Height() / height;
    float scale = scaleY > scaleX ? scaleX : scaleY;
    if (mResizeStyle != 1) {
      float shrink = 1.0f - scale;
      area.x1 -= shrink * width * 0.5f;
      area.y1 -= shrink * height * 0.5f;
      area.x2 = area.x1 + width;
      area.y2 = area.y1 + height;
      mWinRoot->SetArea(area);
      SPUIHelpers::SetWindowScale(mWinRoot, scale);
    } else {
      Math::Rectangle newArea = mMaxArea;
      float newWidth = scale * width;
      float newHeight = scale * height;
      if (mLayoutJustification == kJustificationRight_s005e_5d40)
        newArea.x1 = newArea.x2 - newWidth;
      else if (mLayoutJustification == kJustificationBottom_s005e_5d40)
        newArea.y1 = newArea.y2 - newHeight;
      newArea.x2 = newArea.x1 + newWidth;
      newArea.y2 = newArea.y1 + newHeight;
      mWinRoot->SetArea(newArea);
    }
  }
}
}  // namespace SP



// @ 0x005e67f0
namespace SP {
cSPEditorVerbIconTray_s005e_5d40::cSPEditorVerbIconTray_s005e_5d40()
: mpOwner(0),
      mImageGroup(0),
      mSoundKey(0),
      mAnimateIcons(true),
      mResizeStyle(0),
      mLayoutJustification(kJustificationRight_s005e_5d40),
      mLevelTotal(0.0f),
      mShowLevel(true),
      mShowLevelText(false),
      mShowLevelBar(false),
      mShowVerbIconWhenCollapsed(false),
      mDisplayedLevel(-1.0f),
      mOriginalWidth(-1.0f),
      mOriginalHeight(-1.0f),
      mAbilityCount(0),
      mVerbIconAspectRatio(-1.0f),
      mIconHeight(-1.0f),
      mIconWidth(-1.0f),
      mDoIconLevelsExist(false),
      mOverrideAggregate(false),
      mIsEnabled(true),
      mIsHealthBar(false),
      mIgnoreKeyPress(false),
      mAlertID(0),
      mIsPlayMode(false),
      mSetHaveChargeDials(false),
      mSetForceEnabled(false),
      mIconsHaveChargeDials(false),
      mIconsForceEnabled(false),
      mBaseStatTarget(0.0f),
      mShowRollover(true),
      mAbilityArray(0),
      mRepresentativeAnimation(0) {}
}  // namespace SP



// @ 0x005e6980
namespace SP {
cSPEditorVerbIconTray_s005e_5d40::~cSPEditorVerbIconTray_s005e_5d40()
{}
}  // namespace SP



// @ 0x005e6a60
namespace SP {
eastl::wstring cSPEditorVerbIconTray_s005e_5d40::GetTrayName(int unused)
{
  cString_s005e_5d40 text;
  GetPropertyAsText(mVerbTrayProperties, 0x4acedf4, text);
  eastl::wstring name;
  name = text.c_str();
  return name;
}
}  // namespace SP



// @ 0x005e6ae0
namespace SP {
eastl::wstring cSPEditorVerbIconTray_s005e_5d40::GetTrayDescription()
{
  cString_s005e_5d40 text;
  GetPropertyAsText(mVerbTrayProperties, 0x4acedf9, text);
  eastl::wstring desc(text.c_str());
  return desc;
}
}  // namespace SP


// @ 0x005e6b40
namespace SP {
void cSPEditorVerbIconTray_s005e_6b40::DoMessage(IWindow_s005e_6b40* w)
{ (void)w; }
}  // namespace SP


// @ 0x005e6fb0
namespace SP {
bool cSPEditorVerbIconTray_s005e_6b40::CheckMessage(IWindow_s005e_6b40* w, void* msg)
{
  if (*(int*)((char*)msg + 8) == 10 && *(int*)((char*)msg + 0xc) == 1) {
    IWindow_s005e_6b40* target = *(IWindow_s005e_6b40**)((char*)msg + 0x18);
    if (target == mWinIcon) {
      if (mShowRollover && mRollover) {
        if (mpOwner) {
          mpOwner->UpdateRollover(w);
          return false;
        } else {
          DoMessage(w);
          return false;
        }
      }
    } else {
      if (mRollover)
        mRollover->MarkDirty();
      if (mpOwner)
        mpOwner->RefreshLevel();
    }
  }
  return false;
}
}  // namespace SP


// @ 0x005e7030
void SP::cSPEditorVerbIconTray::SetLevelText(float level)
{ (void)level; }


// @ 0x005e71d0
namespace SP {
void cSPEditorVerbIconTray_s005e_6b40::Update(float dt)
{ (void)dt; }
}  // namespace SP


// @ 0x005e7390
namespace SP {
void* VectorDoAllocate(void* dst, unsigned int count, const unsigned char* value)
{
  (void)dst;
  (void)count;
  (void)value;
  return 0;
}
}  // namespace SP


// @ 0x005e7400
namespace SP {
void VectorDoInsert(void* out, unsigned int count, void* value)
{
  (void)out;
  (void)count;
  (void)value;
}
}  // namespace SP


// @ 0x005e75c0
void SP::cSPEditorVerbIconTray::SetBaseStat(float value)
{ (void)value; }


// @ 0x005e76b0
void SP::cSPEditorVerbIconTray::Shutdown()
{}


// @ 0x005e77e0
namespace SP {
void VectorResize(void* self, unsigned int count)
{
  (void)self;
  (void)count;
}
}  // namespace SP

// @ 0x005e7830
namespace SP {
void cSPEditorVerbIconTray_s005e_7830::Init(IWindow_s005e_7830* parent, Key_s005e_7830 trayKey, uint32_t justification, bool animateIcons, int unused)
{
  mTrayKey = trayKey;
  PropertyManager()->GetPropertyList(trayKey.instanceID, 0xaf028f41, mVerbTrayProperties.AsOutParam());

  if (mVerbTrayProperties->HasProperty(0x4c1ab51))
    GetBoolProp(mVerbTrayProperties, 0x4c1ab51, mShowLevel);
  else
    mShowLevel = true;
  mRolloverShowLevel = mShowLevel;
  GetBoolProp(mVerbTrayProperties, 0x63955a8, mRolloverShowLevel);
  mShowPercent = false;
  GetBoolProp(mVerbTrayProperties, 0x642984a, mShowPercent);
  mShowPercentInRollover = false;
  GetBoolProp(mVerbTrayProperties, 0x6429c96, mShowPercentInRollover);
  mIsHealthBar = false;
  GetBoolProp(mVerbTrayProperties, 0x4cb27fd, mIsHealthBar);
  mShowVerbIconWhenCollapsed = false;
  GetBoolProp(mVerbTrayProperties, 0x4d1a4ee, mShowVerbIconWhenCollapsed);

  mSoundKey = 0;
  GetPropertyAsKeyInstance(mVerbTrayProperties, 0x5ac7e77, mSoundKey);
  mAlertID = 0;
  GetPropertyAsKeyInstance(mVerbTrayProperties, 0x5b6b8b4, mAlertID);

  if (mVerbTrayProperties->HasProperty(0x4abc0f1)) {
    mOverrideAggregate = true;
    uint32_t type;
    GetPropertyAsKeyInstance(mVerbTrayProperties, 0x4abc0f1, type);
    mOverrideType = type;
  } else {
    mOverrideAggregate = false;
  }

  if (mVerbTrayProperties->HasProperty(0x4acea45)) {
    GetPropertyAsKey(mVerbTrayProperties, 0x4acea45, mRolloverLayout);
    mRolloverLayout.groupID = 0x40464100;
    mRolloverLayout.typeID = 0x510a95b;
  }

  if (!mSetForceEnabled)
    GetBoolProp(mVerbTrayProperties, 0x4c8b6b3, mIconsForceEnabled);
  if (!mSetHaveChargeDials)
    GetBoolProp(mVerbTrayProperties, 0x4c8b6ae, mIconsHaveChargeDials);

  mIconID = 0;
  GetPropertyAsKeyInstance(mVerbTrayProperties, 0x6286814, mIconID);
  if (justification) {
    mLayoutJustification = justification;
  } else {
    Key_s005e_7830 keyA;
    if (GetPropertyAsKey(mVerbTrayProperties, 0x4a213b2, keyA))
      mLayoutJustification = keyA.instanceID;
    else
      mLayoutJustification = kJustificationRight_s005e_7830;
  }

  mRepresentativeAnimation = 0;
  Key_s005e_7830 keyB;
  if (GetPropertyAsKey(mVerbTrayProperties, 0x4bdc904, keyB))
    mRepresentativeAnimation = keyB.instanceID;

  Key_s005e_7830* abilities;
  GetKeyArray(mVerbTrayProperties, 0x4a20feb, &mAbilityCount, &abilities);
  if (mAbilityCount > 0) {
    mAbilityArray = new ("Editor", 0, 0, 0, 0) uint32_t[mAbilityCount];
    for (int i = 0; i < mAbilityCount; i++)
      mAbilityArray[i] = abilities[i].instanceID;
    mVerbIcons.resize(mAbilityCount);
  }

  if (mLayoutKey.instanceID == 0)
    GetPropertyAsKey(mVerbTrayProperties, 0x4a20fe1, mLayoutKey);
  mLayoutKey.groupID = 0x40464100;
  mLayoutKey.typeID = 0x510a95b;
  mIconKey = Key_s005e_7830();
  {
    Property* p;
    if (mVerbTrayProperties && mVerbTrayProperties->GetProperty(0xf1fa52af, p) && p->type == 1) {
      bool* v = (p->flags & 0x30) ? *(bool**)p : (bool*)p;
      if (*v) {
        GetPropertyAsKey(mVerbTrayProperties, 0x4a20fe7, mIconKey);
        if (mIconKey.instanceID != 0) {
          if (mIconKey.groupID == 0 || mIconKey.groupID == 0xffffffff)
            mIconKey.groupID = 0x40464100;
          mIconKey.typeID = 0x510a95b;
        }
      }
    }
  }

  mLayout = new ("Editor", 0, 0, 0, 0) cSPUILayout();
  mLayout->Init(&mLayoutKey, 1, 0x5b598fa);
  mWinRoot = mLayout->FindWindowByID(0x902d3163, 1);
  mWinIconPanel = mLayout->FindWindowByID(0x4978d2d, 1);
  mWinLevel = mLayout->FindWindowByID(0x4a61762, 1);
  mWinIcon = mLayout->FindWindowByID(0x4ab090b, 1);
  mWinText = mLayout->FindWindowByID(0x62d6f99, 1);

  if (mWinIcon) mWinIcon->AddWinProc(this);
  if (mWinIcon.mpObject != 0 && mIconID != 0) {
    uint32_t image = SPUIHelpers::GetImageFromLayout(mIconID);
    SPUIHelpers::SetDrawableImage(mWinIcon.mpObject, image, -1);
  }

  Math::Rectangle_s005e_7830 area = mWinRoot->GetArea();
  mAnimateIcons = animateIcons;
  float width = area.x2 - area.x1;
  float height = area.y2 - area.y1;
  mMaxArea.x1 = 0.0f;
  mMaxArea.x2 = width;
  mMaxArea.y1 = 0.0f;
  mMaxArea.y2 = height;
  mResizeStyle = 0;
  mOriginalHeight = height;
  mOriginalWidth = width;
  mShowIcons = false;
  if (mWinIconPanel) {
    mShowIcons = true;
    Math::Rectangle_s005e_7830 a = mWinIconPanel->GetArea();
    mGutters.x1 = a.x1;
    mGutters.x2 = width - a.x2;
    mGutters.y1 = a.y1;
    mGutters.y2 = height - a.y2;
    SetVerbIconSize();
  } else if (mWinText) {
    Math::Rectangle_s005e_7830 a = mWinText->GetArea();
    mGutters.x1 = a.x1;
    mGutters.x2 = width - a.x2;
    mGutters.y1 = a.y1;
    mGutters.y2 = height - a.y2;
  } else {
    mGutters.x1 = 0.0f;
    mGutters.x2 = 0.0f;
    mGutters.y1 = 0.0f;
    mGutters.y2 = 0.0f;
  }

  if (mShowRollover) {
    cSPVerbIconRollover_s005e_7830* r;
    if (mRolloverLayout.instanceID)
      r = new ("Editor", 0, 0, 0, 0) cSPVerbIconRollover_s005e_7830(mRolloverLayout.instanceID);
    else
      r = new ("Editor", 0, 0, 0, 0) cSPVerbIconRollover_s005e_7830();
    mRollover = r;
    if (mRollover) mRollover->Setup();
  }

  mLevelTotal = 0.0f;
  mBaseStat.Init(0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
  if (mWinLevel)
    mBaseTextColor = GetLevelColor(mWinLevel);
  else
    mBaseTextColor = 0xffffffff;
  SetLevelText(mLevelTotal);
  mWinRoot->SetFlag(0x10, true);
  mWinRoot->SetFlag(2, false);
  SetParent(parent, true);
  LayoutTray();
}
}  // namespace SP

// @ 0x005e8130
namespace SP {
void FUN_005e8130()
{}
}  // namespace SP
