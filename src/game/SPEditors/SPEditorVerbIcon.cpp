// src/game/SPEditors/SPEditorVerbIcon.cpp -- migrated from slice(s) s005e2470, s005e16c0 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorVerbIcon.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ResourceMan/Key.h"
#include "SP/cSPEditorVerbIcon.h"
#include "SP/cSPEditorVerbIconData.h"
#include "SP/eLayoutJustification.h"

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
