// Slice s005e5d40: SP::cSPEditorVerbIconTray (row of editor verb icons) and one
// cSPEditorVerbIconData string getter. Retail layout differs from the 2008 PDB in the
// middle of the tray (extra window ref at 0x3c, keys moved), so offsets follow the binary.
#include "types.h"

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
};
}  // namespace Math

extern "C" void EASTL_allocator_deallocate(void* p);

namespace eastl {
union EmptyString {
  uint32_t mUint32;
  wchar_t mEmpty16[1];
};
extern EmptyString gEmptyString;

inline unsigned int CharStrlen(const wchar_t* p) {
  const wchar_t* pCurrent = p;
  while (*pCurrent)
    ++pCurrent;
  return (unsigned int)(pCurrent - p);
}

struct allocator {
  allocator() {}
};

class wstring {
 public:
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  allocator mAllocator;

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

template <typename T>
class vector {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  uint32_t mAllocator;
  vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~vector();
  unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
  T& operator[](unsigned int i) { return mpBegin[i]; }
};
}  // namespace eastl

namespace EA {
namespace UTFWin {
class IWinProc {
 public:
  virtual ~IWinProc() {}
  PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
};

class IWindow {
 public:
  virtual int AddRef();                               // +0x00
  virtual int Release();                              // +0x04
  PV(2) PV(3)
  virtual IWindow* GetParent();                       // +0x10
  PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
  virtual const Math::Rectangle& GetArea();           // +0x38
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23)
  virtual void SetArea(const Math::Rectangle& area);  // +0x60
  PV(25) PV(26) PV(27) PV(28) PV(29) PV(30) PV(31) PV(32) PV(33) PV(34)
  PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44)
  PV(45) PV(46) PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53)
  virtual void AddWindow(IWindow* w);                 // +0xd8
  virtual void RemoveWindow(IWindow* w);              // +0xdc
};
}  // namespace UTFWin

template <typename T>
class AutoRefCount {
 public:
  T* mpObject;
  AutoRefCount() : mpObject(0) {}
  ~AutoRefCount() {
    if (mpObject)
      mpObject->Release();
  }
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
  uint32_t instanceID;
  uint32_t typeID;
  uint32_t groupID;
  Key() : instanceID(0), typeID(0), groupID(0) {}
  Key(uint32_t i, uint32_t t, uint32_t g) : instanceID(i), typeID(t), groupID(g) {}
};
}  // namespace ResourceMan
}  // namespace EA

using EA::UTFWin::IWindow;

class cSPUILayout {
 public:
  PV(0)
  virtual int AddRef();   // +0x04
  virtual int Release();  // +0x08
};

namespace SP {
class cString {
 public:
  cString();
  ~cString();
  const wchar_t* c_str() const;
  uint32_t mData[5];
};

class cPropertyList {
 public:
  PV(0)
  virtual int Release();                 // +0x04
  PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual bool HasProperty(uint32_t id);  // +0x1c
};
bool GetPropertyAsText(cPropertyList* list, uint32_t id, cString& out);

namespace SPUIHelpers {
void SetWindowScale(IWindow* w, float scale);
}

enum eLayoutJustification {
  kJustificationNONE = 0,
  kJustificationRight = -401149879,
  kJustificationLeft = 4109362,
  kJustificationTop = 1080872010,
  kJustificationBottom = -396051872,
};

class cSPEditorVerbIconData {
 public:
  PV(0)
  virtual int Release();  // +0x04
  char pad04[0xbc];
  cPropertyList* mpPropList;  // +0xc0

  eastl::wstring GetIconDescription();
};

class cSPEditorVerbIcon {
 public:
  virtual int AddRef();           // +0x00
  virtual int Release();          // +0x04
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual void LayoutShutdown();  // +0x28
  void SetIgnoreKeyPress(bool b);  // FUN_005e1f90
  void SetShowRollover(bool b);    // FUN_005e1fa0
  int GetState();                  // FUN_005e1fc0
  IWindow* GetWindow();            // 0x7f54d0
  void Disappear();
  float GetHeight(bool scaled);    // FUN_005e2910
  float GetWidth(bool scaled);     // FUN_005e28c0
  Math::Rectangle GetArea();       // FUN_005e2890
  void SetArea(Math::Rectangle area);
};

class cSPVerbIconRollover {
 public:
  PV(0)
  virtual int Release();  // +0x04
};

class cSPEditorVerbIconTray : public EA::UTFWin::IWinProc, public EA::RefCountVTemplate<int> {
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

  cSPEditorVerbIconTray();
  ~cSPEditorVerbIconTray();

  // vtable slots 9.. (after the IWinProc slots)
  PV(9) PV(10) PV(11) PV(12) PV(13) PV(14)
  virtual void LayoutTray();                                  // +0x3c

  eastl::vector<EA::AutoRefCount<cSPEditorVerbIcon> > mVerbIcons;  // +0x0c
  uint32_t pad1c;                                             // +0x1c
  EA::AutoRefCount<cSPEditorVerbIconData> mOverrideData;      // +0x20
  void* mpOwner;                                              // +0x24
  EA::AutoRefCount<cSPUILayout> mLayout;                      // +0x28
  EA::AutoRefCount<IWindow> mWinRoot;                         // +0x2c
  EA::AutoRefCount<IWindow> mWinIconPanel;                    // +0x30
  EA::AutoRefCount<IWindow> mWinLevel;                        // +0x34
  EA::AutoRefCount<IWindow> mWinIcon;                         // +0x38
  EA::AutoRefCount<IWindow> mWinOverride;                     // +0x3c
  EA::AutoRefCount<cPropertyList> mVerbTrayProperties;        // +0x40
  EA::ResourceMan::Key mIconKey;                              // +0x44
  uint32_t mImageGroup;                                       // +0x50
  EA::ResourceMan::Key mLayoutKey;                            // +0x54
  EA::ResourceMan::Key mTrayKey;                              // +0x60
  uint32_t mSoundKey;                                         // +0x6c
  bool mShowIcons;                                            // +0x70
  bool mAnimateIcons;                                         // +0x71
  int mResizeStyle;                                           // +0x74
  int mLayoutJustification;                                   // +0x78
  EA::ResourceMan::Key mRolloverLayout;                       // +0x7c
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
  EA::AutoRefCount<cSPVerbIconRollover> mRollover;            // +0x110
  uint32_t mAbilityArray;                                     // +0x114
  uint32_t mRepresentativeAnimation;                          // +0x118
  EA::AutoRefCount<cSPVerbIconRollover> mCollection;          // +0x11c

  void SetRolloverLayout(EA::ResourceMan::Key key);
  void SetLayoutKey(EA::ResourceMan::Key key);
  void SetLayoutID(uint32_t id);
  void SetHaveChargeDials(bool b);
  void SetForceEnabled(bool b);
  float GetMaxVerbWidth();
  float GetMaxVerbHeight();
  void SetVerbIconSize();
  void RemoveVerbIconInternal(int index);
  void SetShowRollover(bool b);
  void SetIgnoreKeyPress(bool b);
  void SetParent(IWindow* parent, bool resize);
  float GetHeight();
  void SetMaxArea(const Math::Rectangle& area);
  eastl::wstring GetTrayName(int unused);
  eastl::wstring GetTrayDescription();
};

// @ 0x005e5d40
eastl::wstring cSPEditorVerbIconData::GetIconDescription() {
  if (mpPropList->HasProperty(0x3249a320)) {
    cString text;
    GetPropertyAsText(mpPropList, 0x3249a320, text);
    eastl::wstring result(text.c_str());
    return result;
  }
  return eastl::wstring();
}

// @ 0x005e5e40
void cSPEditorVerbIconTray::SetRolloverLayout(EA::ResourceMan::Key key) {
  mRolloverLayout.instanceID = key.instanceID;
  mRolloverLayout.groupID = 0x40464100;
  mRolloverLayout.typeID = 0x510a95b;
}

// @ 0x005e5e60
void cSPEditorVerbIconTray::SetLayoutKey(EA::ResourceMan::Key key) {
  mLayoutKey.instanceID = key.instanceID;
  mLayoutKey.groupID = 0x40464100;
  mLayoutKey.typeID = 0x510a95b;
}

// @ 0x005e5e80
void cSPEditorVerbIconTray::SetLayoutID(uint32_t id) {
  mLayoutKey.instanceID = id;
  mLayoutKey.groupID = 0x40464100;
  mLayoutKey.typeID = 0x510a95b;
}

// @ 0x005e5ea0
void cSPEditorVerbIconTray::SetHaveChargeDials(bool b) {
  mSetHaveChargeDials = true;
  mIconsHaveChargeDials = b;
}

// @ 0x005e5ec0
void cSPEditorVerbIconTray::SetForceEnabled(bool b) {
  mSetForceEnabled = true;
  mIconsForceEnabled = b;
}

// @ 0x005e5f10
float cSPEditorVerbIconTray::GetMaxVerbWidth() {
  float width;
  if (mResizeStyle == 1 && mWinIconPanel)
    width = mWinIconPanel->GetArea().Width();
  else
    width = mMaxArea.Width() - mGutters.x1 - mGutters.x2;
  if (mLayoutJustification == kJustificationRight || mLayoutJustification == kJustificationLeft)
    return width / mVerbIcons.size();
  return width;
}

// @ 0x005e5fa0
float cSPEditorVerbIconTray::GetMaxVerbHeight() {
  float height;
  if (mResizeStyle == 1 && mWinIconPanel)
    height = mWinIconPanel->GetArea().Height();
  else
    height = mMaxArea.Height() - mGutters.y1 - mGutters.y2;
  if (mLayoutJustification == kJustificationRight || mLayoutJustification == kJustificationLeft)
    return height;
  return height / mVerbIcons.size();
}

// @ 0x005e6030
void cSPEditorVerbIconTray::SetVerbIconSize() {
  mIconWidth = GetMaxVerbWidth();
  float height = GetMaxVerbHeight();
  mIconHeight = height;
  if (mLayoutJustification == kJustificationRight || mLayoutJustification == kJustificationLeft) {
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

// @ 0x005e60d0
void cSPEditorVerbIconTray::RemoveVerbIconInternal(int index) {
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

// @ 0x005e6170
void cSPEditorVerbIconTray::SetShowRollover(bool b) {
  mShowRollover = b;
  int count = mVerbIcons.size();
  for (int i = 0; i < count; i++)
    mVerbIcons[i]->SetShowRollover(b);
}

// @ 0x005e61b0
void cSPEditorVerbIconTray::SetIgnoreKeyPress(bool b) {
  mIgnoreKeyPress = b;
  int count = mVerbIcons.size();
  for (int i = 0; i < count; i++) {
    if (mVerbIcons[i])
      mVerbIcons[i]->SetIgnoreKeyPress(b);
  }
}

// @ 0x005e6200
void cSPEditorVerbIconTray::SetParent(IWindow* parent, bool resize) {
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
        if (mLayoutJustification == kJustificationRight ||
            mLayoutJustification == kJustificationLeft) {
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

// @ 0x005e6390
float cSPEditorVerbIconTray::GetHeight() {
  return mWinRoot->GetArea().Height();
}

// @ 0x005e63b0
void cSPEditorVerbIconTray::SetMaxArea(const Math::Rectangle& area) {
  mMaxArea = area;
  SetVerbIconSize();
  mWinRoot->SetArea(area);
  LayoutTray();
}

// @ 0x005e6400
void cSPEditorVerbIconTray::LayoutTray() {
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
          cSPEditorVerbIcon* icon = mVerbIcons[i];
          float iconHeight = icon->GetHeight(true);
          float iconWidth = mVerbIcons[i]->GetWidth(true);
          float areaWidth = mVerbIcons[i]->GetArea().Width();
          float areaHeight = mVerbIcons[i]->GetArea().Height();
          if (mLayoutJustification == kJustificationRight ||
              mLayoutJustification == kJustificationLeft) {
            top = 0.0f;
            left = x;
            x += iconWidth;
          } else if (mLayoutJustification == kJustificationTop ||
                     mLayoutJustification == kJustificationBottom) {
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
    if (mLayoutJustification == kJustificationRight || mLayoutJustification == kJustificationLeft)
      height = area.Height();
    else
      height = mGutters.y2 + mGutters.y1 + y;
    float width;
    if (mLayoutJustification == kJustificationTop || mLayoutJustification == kJustificationBottom)
      width = area.Width();
    else
      width = mGutters.x2 + mGutters.x1 + x;
    if (mLayoutJustification == kJustificationRight)
      area.x1 = area.x2 - width;
    else if (mLayoutJustification == kJustificationBottom)
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
      if (mLayoutJustification == kJustificationRight)
        newArea.x1 = newArea.x2 - newWidth;
      else if (mLayoutJustification == kJustificationBottom)
        newArea.y1 = newArea.y2 - newHeight;
      newArea.x2 = newArea.x1 + newWidth;
      newArea.y2 = newArea.y1 + newHeight;
      mWinRoot->SetArea(newArea);
    }
  }
}

// @ 0x005e67f0
cSPEditorVerbIconTray::cSPEditorVerbIconTray()
    : mpOwner(0),
      mImageGroup(0),
      mSoundKey(0),
      mAnimateIcons(true),
      mResizeStyle(0),
      mLayoutJustification(kJustificationRight),
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

// @ 0x005e6980
cSPEditorVerbIconTray::~cSPEditorVerbIconTray() {}

// @ 0x005e6a60
eastl::wstring cSPEditorVerbIconTray::GetTrayName(int unused) {
  cString text;
  GetPropertyAsText(mVerbTrayProperties, 0x4acedf4, text);
  eastl::wstring name;
  name = text.c_str();
  return name;
}

// @ 0x005e6ae0
eastl::wstring cSPEditorVerbIconTray::GetTrayDescription() {
  cString text;
  GetPropertyAsText(mVerbTrayProperties, 0x4acedf9, text);
  eastl::wstring desc(text.c_str());
  return desc;
}
}  // namespace SP
