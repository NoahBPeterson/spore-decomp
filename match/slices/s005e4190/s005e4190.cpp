// Slice s005e4190: SP::cSPEditorVerbIcon methods (editor verb/ability icon).
// Class layout follows the retail-correct layout recovered in match/slices/s005e2470
// (mIconData +0x170, mRollover +0x174).
#include "types.h"
#include <xmmintrin.h>
#include <new>

#define PV(n) virtual void _pv##n();

namespace Math {
struct Rectangle {
  float x1, y1, x2, y2;
  Rectangle() {}
  Rectangle(float l, float t, float r, float b) : x1(l), y1(t), x2(r), y2(b) {}
  Rectangle(const Rectangle& r) : x1(r.x1), y1(r.y1), x2(r.x2), y2(r.y2) {}
  Rectangle& operator=(const Rectangle& r) {
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
};
}  // namespace Math

extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380

namespace eastl {
union EmptyString {
  uint32_t mUint32;
  wchar_t mEmpty16[1];
};
extern EmptyString gEmptyString16;  // 0x01667bac

class allocator { public:
  allocator() {}
};

class wstring : private allocator {
 public:
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  wstring() { AllocateSelf(); }
  void AllocateSelf() {
    mpBegin = gEmptyString16.mEmpty16;
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
}  // namespace eastl

extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
void WStr_Format(eastl::wstring* out, const wchar_t* format, ...);

namespace EA {
namespace ResourceMan {
class Key { public:
  uint32_t instanceID;
  uint32_t typeID;
  uint32_t groupID;
  Key() : instanceID(0), typeID(0), groupID(0) {}
  Key(uint32_t i, uint32_t t, uint32_t g) : instanceID(i), typeID(t), groupID(g) {}
};
}  // namespace ResourceMan

struct Point {
  float x;
  float y;
};
}  // namespace EA

namespace EA {
namespace UTFWin {
class IWinProc;

class IWindow {
 public:
  virtual int AddRef();                               // +0x00
  virtual int Release();                              // +0x04
  PV(2)
  virtual void* Cast(uint32_t typeID);                // +0x0c
  virtual IWindow* GetParent();                       // +0x10
  PV(5) PV(6)
  virtual uint32_t GetID();                           // +0x1c
  PV(8) PV(9)
  virtual uint32_t GetFlags();                        // +0x28
  PV(11)
  virtual uint32_t GetShadeColor();                   // +0x30
  virtual const Math::Rectangle& GetRealArea();       // +0x34
  virtual const Math::Rectangle& GetArea();           // +0x38
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22)
  virtual void SetShadeColor(uint32_t color);         // +0x5c
  virtual void SetArea(const Math::Rectangle& area);  // +0x60
  PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
  virtual void SetFlag(int flag, bool value);         // +0x7c
  virtual void SetText(const wchar_t* text);          // +0x80
  PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39)
  PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47)
  virtual EA::Point ToClient(float x, float y);       // +0xc0
  PV(49) PV(50) PV(51) PV(52) PV(53)
  virtual void AddWindow(IWindow* w);                 // +0xd8
  virtual void RemoveWindow(IWindow* w);              // +0xdc
};

class IWinText {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
  virtual uint32_t GetTextColor();  // +0x24
};

class IWinProc {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5)
  virtual bool HandleMessage(IWindow* w, void* msg);  // +0x18 slot 6
  PV(7) PV(8)
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
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}  // namespace EA

using EA::UTFWin::IWindow;

void* operator new(unsigned int size, const char* pName, int flags, unsigned debugFlags,
                   const char* file, int line);
extern const char kEditorAllocName[];  // "Editor"

class cProperty {
 public:
  bool* GetBool();
};

class cPropertyList {
 public:
  virtual int AddRef();                              // +0x00
  virtual int Release();                             // +0x04
  PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual bool HasProperty(uint32_t id);             // +0x1c
  PV(8)
  virtual bool GetProperty(uint32_t id, void** out);  // +0x24
};

class cSPUILayout {
 public:
  PV(0)
  virtual int AddRef();   // +0x04
  virtual int Release();  // +0x08
  cSPUILayout();
  bool Init(const EA::ResourceMan::Key& key, bool visible, uint32_t parentID);
  IWindow* FindWindowByID(uint32_t id, bool recursive);
  void Shutdown(bool unused);
  uint32_t mData[5];
};

// A wstring whose storage is filled in by a callee (no constructor runs here).
struct RawWStr {
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  uint32_t mAllocator;
};

// Wide-string buffer a callee fills in; released on scope exit like an eastl::wstring.
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
char FUN_00806aa0(IWindow* w, int image, int flag);  // 0x00806aa0 (cdecl)

// Types used by HandleMessage (0x005e49c0).
struct UIMsg {
  uint32_t pad00[2];
  uint32_t id;       // +0x08
  uint32_t sub;      // +0x0c
  uint32_t arg;      // +0x10
  uint32_t pad14;
  IWindow* src;      // +0x18 (source window; a RenderContext* for the draw message)
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
struct RenderContext {
  Painter* Begin2D(int flag);  // 0x0095bc10
  void End2D();                // 0x0095bb20
};
struct DrawTarget {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
  virtual void PrepareDraw(UIMsg* m);  // +0x20
};
extern float g_015f0090;
extern float g_015f00e0;
extern float g_0151a184;
extern int g_0151a040;
double __cdecl iat_floor(double x);  // 0x011e0906
void FUN_00805940(void* p, float a, float b, float c, int d, int e, float f, float g, void* img, float h);  // 0x00805940

namespace SP {
// Localized-text holder (0x14 bytes) filled by GetPropertyAsText / cString::Load.
class cString {
 public:
  cString();                 // 0x006b5060
  ~cString();                // 0x006b5240
  const wchar_t* GetText();  // 0x006b55c0
 private:
  uint32_t mField00;
  uint32_t mField04;
  uint32_t mField08;
  uint32_t mField0c;
  uint32_t mField10;
};

void GetPropertyAsText(cPropertyList* pProps, uint32_t id, cString* pText);  // 0x006a1360

class cWindowManager {
 public:
  PV(0)
  virtual IWindow* GetMainWindow();  // +0x04
};
cWindowManager* WindowManager();     // 0x0067caa0
}  // namespace SP

// Object behind the global pointer at 0x015ee298: the rounded icon level is mirrored here.
struct cSPVerbLevelMirror {
  uint32_t mPad00[0x16];  // +0x00..0x57
  int mDisplayedLevel;    // +0x58
};
extern cSPVerbLevelMirror* g_p015ee298;  // 0x015ee298

namespace EA {
// Variant carrying a wide string: 0x10 bytes of payload, flags at +0x10, type id at +0x12.
struct Variant {
  uint32_t mData0;
  uint32_t mData1;
  uint32_t mData2;
  uint32_t mData3;
  uint16_t mFlags;   // +0x10
  uint16_t mTypeId;  // +0x12
  Variant(const void* pText) : mFlags(0), mTypeId(0) { Construct(0x13, 9, pText, 0x10, 1); }
  ~Variant() {
    if (mFlags & 4)
      Destruct(false);
  }
  bool Construct(unsigned short type, unsigned short subType, const void* pData, unsigned int size, unsigned int flags);  // 0x0093dd80
  void Destruct(bool arg);  // 0x0093db80
};
}  // namespace EA

namespace SP {
class cSPVerbIconRollover {
 public:
  cSPVerbIconRollover();
  cSPVerbIconRollover(uint32_t arg);
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
  void SetProperty(uint32_t key, const EA::Variant& value, bool a, bool b);  // 0x00828c30
  void Layout();                                                           // 0x006053a0
  IWindow* GetRootWindow();                                                // 0x00828100
  void SetPositionAndOffset(float x, float y, float w, float h);           // 0x008283a0
};

class cSPEditorVerbIconData {
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
  cPropertyList* mpPropList;  // +0xc0
};

class cSPEditorVerbIcon : public EA::UTFWin::IWinProc, public EA::RefCountVTemplate<int> {
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

  virtual bool HandleMessage(IWindow* w, void* msg);
  PV(9) PV(10) PV(11) PV(12)
  virtual void SetLevel(float level);                  // +0x34 slot 13
  virtual void UpdateLevelDisplay(float level);        // +0x38 slot 14
  PV(15)
  virtual bool IsToggled();                            // +0x40 slot 16
  virtual void Slot17();                               // +0x44 slot 17
  virtual void InitData(cSPEditorVerbIconData* data);  // +0x48 slot 18
  PV(19) PV(20)
  virtual void SetVerbID(uint32_t id);                 // +0x54

  EA::AutoRefCount<cSPUILayout> mLayout;                   // +0x0c
  EA::AutoRefCount<IWindow> mWinRoot;                      // +0x10
  EA::AutoRefCount<IWindow> mWinIcon;                      // +0x14
  EA::AutoRefCount<IWindow> mWinLevel;                     // +0x18
  EA::AutoRefCount<IWindow> mWinHighlight;                 // +0x1c
  EA::AutoRefCount<IWindow> mWinShortcutText;              // +0x20
  EA::AutoRefCount<IWindow> mWin24;                        // +0x24
  EA::AutoRefCount<IWindow> mWinFlashingGlow;              // +0x28
  EA::AutoRefCount<IWindow> mWinChargeDial;                // +0x2c
  EA::AutoRefCount<IWindow> mWinLevelPips[5];              // +0x30
  SPImageObj* mpImage44;                                   // +0x44
  EA::ResourceMan::Key mNormalKey;                         // +0x48
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
  Math::Rectangle mArea;                                   // +0x88
  cVerbIconLinearInterpolationValue mCharge;               // +0x98
  cVerbIconInterpolationValue mScaleX;                     // +0xac
  cVerbIconInterpolationValue mScaleY;                     // +0xc8
  cVerbIconLinearInterpolationValue mLevel;                // +0xe4
  cVerbIconInterpolationValue mUpgradeScale;               // +0xf8
  cVerbIconMiddleInterpolationValue mUpgradeHighlightFade;  // +0x114
  cVerbIconMiddleInterpolationValue mIconAlpha;            // +0x134
  cVerbIconOscillatingAlpha mFlashAlpha;                   // +0x154
  EA::AutoRefCount<cSPEditorVerbIconData> mIconData;       // +0x170
  EA::AutoRefCount<cSPVerbIconRollover> mRollover;         // +0x174
  uint32_t mBaseTextColor;                                 // +0x178
  uint32_t mCollectionID;                                  // +0x17c
  float mAspectRatio;                                      // +0x180

  __declspec(noinline) void UpdateRollover(IWindow* parent);
};

// Standalone helper with the field layout used by 005e4d60 (unknown owning class).
class cIconVerbHelper {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual void Slot7(int v);  // +0x1c
  uint32_t pad04[4];          // +0x04..0x13
  int mUnknown14;             // +0x14
  uint32_t pad18[0x19];       // +0x18..0x7b
  int mUnknown7c;             // +0x7c
  void SetIndex(int v);
};

// @ 0x005e4d30
int FloatToInt(float value) {
  __asm {
    cvtss2si eax, [esp + 4]
  }
}

// @ 0x005e4d60
void cIconVerbHelper::SetIndex(int v) {
  mUnknown7c = v;
  if (mUnknown14 == -1)
    return Slot7(v + 0x31);
}

// @ 0x005e4c90
void cSPEditorVerbIcon::UpdateLevelDisplay(float value) {
  if (mWinHighlight) {
    eastl::wstring text;
    WStr_Format(&text, reinterpret_cast<const wchar_t*>(0x13f01bc), (int)value);
    mWinHighlight->SetText(text.mpBegin);
  }
}

// @ 0x005e4190
void cSPEditorVerbIcon::InitData(cSPEditorVerbIconData* data) {
  mIconData = data;
  if (data->mpPropList->HasProperty(0x4bf1b5f)) {
    if (!mUnknown6b || mUnknown6a) {
      cPropertyList* props = data->mpPropList;
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
    cPropertyList* props = data->mpPropList;
    if (props) {
      void* prop;
      if (props->GetProperty(0x5407d4b, &prop)) {
        if (*(unsigned short*)((char*)prop + 0x12) == 1)
          mUnknown73 = *((cProperty*)prop)->GetBool();
      }
    }
  }
  if ((mIsVisible && mUnknown6a) || mUnknown6c) {
    cSPVerbIconRollover* r;
    if (mRolloverLayout)
      r = new (kEditorAllocName, 0, 0, 0, 0) cSPVerbIconRollover(mRolloverLayout);
    else
      r = new (kEditorAllocName, 0, 0, 0, 0) cSPVerbIconRollover();
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
  IWindow* dial = mWinChargeDial;
  if (dial) {
    RawWStr tmp;
    RawWStr* r = mIconData->Slot20(&tmp, 0);
    dial->SetText(r->mpBegin);
    if ((tmp.mpCapacity - tmp.mpBegin) > 1 && tmp.mpBegin)
      EASTL_allocator_deallocate(tmp.mpBegin);
  }
  int idx = data->mArrayIndex;
  if (idx >= 0 && (unsigned)idx < 5) {
    IWindow* pip = mWinLevelPips[idx];
    if (pip) {
      uint32_t color = pip->GetShadeColor();
      if (mWinIcon)
        mWinIcon->SetShadeColor(color);
      if (mWinLevel)
        mWinLevel->SetShadeColor(color);
    }
  }
}

// @ 0x005e4560
void cSPEditorVerbIcon::UpdateRollover(IWindow* parent) {
  SP::cString text;
  if (mIconData->mShowZeroLevel) {
    g_p015ee298->mDisplayedLevel = (int)mIconData->mLevel;
    SP::GetPropertyAsText(mIconData->mpPropList, 0x62d00e8, &text);
    eastl::wstring levelText(text.GetText());
    mRollover->SetProperty(0x4d97708, EA::Variant(&levelText), true, false);
  } else {
    static eastl::wstring sNoLevelText;
    mRollover->SetProperty(0x4d97708, EA::Variant(&sNoLevelText), true, false);
  }

  WStrOut nameText;
  mRollover->SetProperty(0x331cc0e, EA::Variant(mIconData->Slot20(&nameText, 0)), true, false);

  WStrOut descriptionText;
  mRollover->SetProperty(0x331cc0f, EA::Variant(mIconData->Slot24(&descriptionText)), true, false);

  if (mIconData->mHotKeyEnabled && mIconData->mUnknown14 > -1) {
    mRollover->SetVisibility(0x4d97710, true);
    mRollover->SetProperty(0x4d97710, EA::Variant(&mIconData->mHotKeyText), true, false);
  } else {
    mRollover->SetVisibility(0x4d97710, false);
  }

  mRollover->Slot8();
  mRollover->Layout();

  // The rollover is centred on the parent's area and sized from the main window's world area.
  const Math::Rectangle& area = parent->GetArea();
  IWindow* pParent = parent->GetParent();
  float centerY = (area.y2 + area.y1) * 0.5f;
  float centerX = (area.x2 + area.x1) * 0.5f;
  EA::Point client = pParent->ToClient(centerX, centerY);

  const Math::Rectangle& realArea = SP::WindowManager()->GetMainWindow()->GetRealArea();
  float width = (realArea.x2 - realArea.x1) * 0.025f;
  float height = (realArea.y2 - realArea.y1) * 0.033333335f;
  IWindow* pRoot = mRollover->GetRootWindow();
  if (pRoot) {
    const Math::Rectangle& rootArea = pRoot->GetArea();
    width = -(rootArea.x2 - rootArea.x1) - width;
  }

  mRollover->FUN_006052f0();
  mRollover->SetPositionAndOffset(client.x, client.y, width, height);
}

// @ 0x005e49c0
bool cSPEditorVerbIcon::HandleMessage(IWindow* w, void* msgv) {
  UIMsg* m = (UIMsg*)msgv;
  if (m->id == 10 && m->sub == 1) {
    IWindow* src = m->src;
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
        RenderContext* ctx = (RenderContext*)m->src;
        dt->PrepareDraw(m);
        Painter* p = ctx->Begin2D(0);
        Math::Rectangle buf;
        bool saved = p->GetState(&buf);
        SPImageObj* img = mpImage44;
        if (img)
          img->AddRef();
        Math::Rectangle r;
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
