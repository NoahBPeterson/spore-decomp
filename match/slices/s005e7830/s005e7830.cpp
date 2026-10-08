// Slice s005e7830: SP::cSPEditorVerbIconTray::Init (0x5e7830, reconstructed) and a large helper
// (0x5e8130, skeleton, see partial.txt).  Layout follows the retail binary (ModAPI cSPEditorVerbIconTray,
// extra window ref at 0x3c); see also match/slices/s005e5d40.
#include "types.h"

typedef unsigned int size_t;
#define PV(n) virtual void _pv##n();
void* operator new[](size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line); // 0xf473a0
inline void* operator new(size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line)
{ return operator new[](size, name, flags, debugFlags, file, line); }

namespace Math {
struct Rectangle {
  float x1, y1, x2, y2;
  Rectangle() {}
  Rectangle(const Rectangle& r) : x1(r.x1), y1(r.y1), x2(r.x2), y2(r.y2) {}
};
}  // namespace Math

namespace EA {
namespace ResourceMan {
struct Key {
  uint32_t instanceID;
  uint32_t typeID;
  uint32_t groupID;
  Key() : instanceID(0), typeID(0), groupID(0) {}

};
}  // namespace ResourceMan

template <typename T>
class AutoRefCount {
 public:
  T* mpObject;
  AutoRefCount() : mpObject(0) {}
  ~AutoRefCount() { if (mpObject) mpObject->Release(); }
  T** AsOutParam() {
    if (mpObject) { T* pOld = mpObject; mpObject = 0; pOld->Release(); }
    return &mpObject;
  }
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

namespace UTFWin {
class IWinProc {
 public:
  virtual ~IWinProc() {}
  PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
};
class IWindow {
 public:
  virtual int AddRef();                                // +0x00
  virtual int Release();                               // +0x04
  PV(2)
  virtual IWindow* FindChild(uint32_t id);             // +0x0c
  PV(4) PV(5) PV(6) PV(7) PV(8)
  virtual uint32_t GetColor();                         // +0x24
  PV(10) PV(11) PV(12) PV(13)
  virtual const Math::Rectangle& GetArea();            // +0x38
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
  virtual void SetFlag(uint32_t flag, bool value);     // +0x7c
  PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44)
  PV(45) PV(46) PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58)
  PV(59) PV(60) PV(61) PV(62) PV(63) PV(64)
  virtual void AddWinProc(IWinProc* p);                // +0x104
};
}  // namespace UTFWin

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

using EA::UTFWin::IWindow;
using EA::ResourceMan::Key;
using EA::AutoRefCount;

// Property system (App::Property / PropertyList / PropertyManager), retail vtable slots
class Property {
 public:
  bool* GetBool();  // 0x41e920
  char pad[0x10];
  uint16_t flags;   // +0x10
  uint16_t type;    // +0x12
};

namespace SP {
class cPropertyList {
 public:
  PV(0)
  virtual int Release();                                   // +0x04
  PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual bool HasProperty(uint32_t id);                   // +0x1c
  PV(8)
  virtual bool GetProperty(uint32_t id, Property*& out);   // +0x24
};
class cPropertyManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, cPropertyList** out);  // +0x2c
};
cPropertyManager* PropertyManager();  // 0x67de30
bool GetPropertyAsKey(cPropertyList* list, uint32_t id, Key& out);                      // 0x6a1250
bool GetPropertyAsKeyInstance(cPropertyList* list, uint32_t id, uint32_t& out);         // 0x6a12a0
bool GetKeyArray(cPropertyList* list, uint32_t id, int* count, Key** arr);              // 0x6a0ae0

inline void GetBoolProp(cPropertyList* l, uint32_t id, bool& out) {
  Property* p;
  if (l && l->GetProperty(id, p) && p->type == 1) out = *p->GetBool();
}

class cSPUILayout {
 public:
  uint32_t mPad[5];
  cSPUILayout();                                                     // 0x810000
  PV(0)
  virtual int AddRef();                                              // +0x04
  virtual int Release();                                             // +0x08
  void Init(const Key* key, int a, uint32_t b);                      // 0x8120d0
  IWindow* FindWindowByID(uint32_t id, int flag);                    // 0x8105b0
};

namespace SPUIHelpers {
uint32_t GetImageFromLayout(uint32_t id);                            // 0x458de0
bool SetDrawableImage(IWindow* w, uint32_t image, int index);        // 0x8068d0
}

enum eLayoutJustification { kJustificationRight = -401149879 };

class cSPEditorVerbIcon {
 public:
  virtual int AddRef();
  virtual int Release();
};
class cSPVerbIconRollover {
 public:
  char mPad[0x74];
  cSPVerbIconRollover();                       // 0x6051d0
  cSPVerbIconRollover(uint32_t id);            // 0x605220
  virtual int AddRef();                        // +0x00
  virtual int Release();                       // +0x04
  PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual void Setup();                        // +0x1c
};

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

class cSPEditorVerbIconTray : public EA::UTFWin::IWinProc, public EA::RefCountVTemplate<int> {
 public:
  struct cVerbIconInterpolationValue {
    float mTargetValue, mCurrentValue, mElapsedTime, mInitialValue, mDuration, mOverShoot, mDampenPercent;
    void Init(float a, float b, float c, float d, float e);   // 0x5e1c80
  };

  PV(9)
  virtual void SetParent(IWindow* parent, bool resize);        // +0x28
  PV(11) PV(12) PV(13) PV(14)
  virtual void LayoutTray();                                   // +0x3c

  IconVector<AutoRefCount<cSPEditorVerbIcon> > mVerbIcons;     // +0x0c
  uint32_t pad1c;                                              // +0x1c
  void* mOverrideData;                                         // +0x20
  void* mpOwner;                                               // +0x24
  AutoRefCount<cSPUILayout> mLayout;                           // +0x28
  AutoRefCount<IWindow> mWinRoot;                              // +0x2c
  AutoRefCount<IWindow> mWinIconPanel;                         // +0x30
  AutoRefCount<IWindow> mWinLevel;                             // +0x34
  AutoRefCount<IWindow> mWinIcon;                              // +0x38
  AutoRefCount<IWindow> mWinText;                              // +0x3c
  AutoRefCount<cPropertyList> mVerbTrayProperties;             // +0x40
  Key mIconKey;                                                // +0x44
  uint32_t mSoundKey;                                          // +0x50
  Key mLayoutKey;                                              // +0x54
  Key mTrayKey;                                                // +0x60
  uint32_t mIconID;                                            // +0x6c
  bool mShowIcons;                                             // +0x70
  bool mAnimateIcons;                                          // +0x71
  int mResizeStyle;                                            // +0x74
  int mLayoutJustification;                                    // +0x78
  Key mRolloverLayout;                                         // +0x7c
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
  Math::Rectangle mMaxArea;                                    // +0xa8
  Math::Rectangle mGutters;                                    // +0xb8
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
  AutoRefCount<cSPVerbIconRollover> mRollover;                 // +0x110
  uint32_t* mAbilityArray;                                     // +0x114
  uint32_t mRepresentativeAnimation;                           // +0x118

  void SetVerbIconSize();                                      // 0x5e6030
  void SetLevelText(float level);                              // 0x5e7030
  void Init(IWindow* parent, Key trayKey, uint32_t justification, bool animateIcons, int unused);   // @ 0x5e7830
};

inline IWindow* FindChildOrNull(IWindow* w, uint32_t id) { return w ? w->FindChild(id) : 0; }
inline uint32_t GetLevelColor(IWindow* w) { return FindChildOrNull(w, 0xf15f4bd)->GetColor(); }

// @ 0x005e7830
void cSPEditorVerbIconTray::Init(IWindow* parent, Key trayKey, uint32_t justification, bool animateIcons, int unused) {
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
    Key keyA;
    if (GetPropertyAsKey(mVerbTrayProperties, 0x4a213b2, keyA))
      mLayoutJustification = keyA.instanceID;
    else
      mLayoutJustification = kJustificationRight;
  }

  mRepresentativeAnimation = 0;
  Key keyB;
  if (GetPropertyAsKey(mVerbTrayProperties, 0x4bdc904, keyB))
    mRepresentativeAnimation = keyB.instanceID;

  Key* abilities;
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
  mIconKey = Key();
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

  Math::Rectangle area = mWinRoot->GetArea();
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
    Math::Rectangle a = mWinIconPanel->GetArea();
    mGutters.x1 = a.x1;
    mGutters.x2 = width - a.x2;
    mGutters.y1 = a.y1;
    mGutters.y2 = height - a.y2;
    SetVerbIconSize();
  } else if (mWinText) {
    Math::Rectangle a = mWinText->GetArea();
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
    cSPVerbIconRollover* r;
    if (mRolloverLayout.instanceID)
      r = new ("Editor", 0, 0, 0, 0) cSPVerbIconRollover(mRolloverLayout.instanceID);
    else
      r = new ("Editor", 0, 0, 0, 0) cSPVerbIconRollover();
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

// @ 0x005e8130
void FUN_005e8130() {}
}  // namespace SP
