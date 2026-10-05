// Slice s005e4190: SP::cSPEditorVerbIcon methods (editor verb/ability icon).
// Class layout follows the retail-correct layout recovered in match/slices/s005e2470
// (mIconData +0x170, mRollover +0x174).
#include "types.h"
#include <xmmintrin.h>

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

extern "C" void EASTL_allocator_deallocate(void* p);

namespace eastl {
union EmptyString {
  uint32_t mUint32;
  wchar_t mEmpty16[1];
};
extern EmptyString gEmptyString;

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
  void AllocateSelf() {
    mpBegin = gEmptyString.mEmpty16;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + 1;
  }
  void DeallocateSelf() {
    if ((mpCapacity - mpBegin) > 1)
      EASTL_allocator_deallocate(mpBegin);
  }
  ~wstring() { DeallocateSelf(); }
};
}  // namespace eastl

extern "C" void EASTL_allocator_deallocate(void* p);
extern "C" void EASTL_allocator_deallocate(void* p);
void WStr_Format(eastl::wstring* out, const wchar_t* format, ...);

namespace EA {
namespace ResourceMan {
struct Key {
  uint32_t instanceID;
  uint32_t typeID;
  uint32_t groupID;
  Key() : instanceID(0), typeID(0), groupID(0) {}
  Key(uint32_t i, uint32_t t, uint32_t g) : instanceID(i), typeID(t), groupID(g) {}
};
}  // namespace ResourceMan

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
  PV(11) PV(12)
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
  PV(48) PV(49) PV(50) PV(51) PV(52) PV(53)
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

namespace SP {
class cSPVerbIconRollover {
 public:
  cSPVerbIconRollover();
  cSPVerbIconRollover(uint32_t arg);
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5)
  PV(6)
  PV(7)
  void SetVisibility(uint32_t key, bool visible);
  void Layout();
  IWindow* GetRootWindow();
  void SetPositionAndOffset(float x, float y, float w, float h);
};

class cSPEditorVerbIconData {
 public:
  virtual int AddRef();                      // +0x00
  virtual int Release();                     // +0x04
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
  virtual void Slot20(void* out, int arg);   // +0x20
  virtual void Slot24(void* out);            // +0x24
  PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
  bool mUseDescription;       // +0x0c
  bool mShowLevel;            // +0x0d
  bool mShowHotKey;           // +0x0e
  bool mShowZeroLevel;        // +0x0f
  int mHotKeyProp;            // +0x10
  int mUnknown14;             // +0x14
  float mLevel;               // +0x18
  uint32_t pad1c[0xd];        // +0x1c..0x4f
  int mArrayIndex;            // +0x50
  uint32_t pad54[5];          // +0x54..0x67
  uint32_t mUnknown68;        // +0x68
  uint32_t pad6c[3];          // +0x6c..0x77
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
  };
  struct cVerbIconOscillatingAlpha {
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
  uint32_t pad44;
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

  void UpdateRollover(IWindow* parent);
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
  if (mIconData != data)
    mIconData = data;
  cPropertyList* props = data->mpPropList;
  if (props != 0 && props->HasProperty(0x4bf1b5f)) {
    if (!mUnknown6b || mUnknown6a) {
      void* prop = 0;
      if (props->GetProperty(0x4bf1b5f, &prop)) {
        if (*(unsigned short*)((char*)prop + 0x12) == 1)
          mUnknown6a = *((cProperty*)prop)->GetBool();
      }
    }
  }
  if (props != 0 && props->HasProperty(0x5407d4b)) {
    void* prop = 0;
    if (props->GetProperty(0x5407d4b, &prop)) {
      if (*(unsigned short*)((char*)prop + 0x12) == 1)
        mUnknown73 = *((cProperty*)prop)->GetBool();
    }
  }
}

// @ 0x005e4560
void cSPEditorVerbIcon::UpdateRollover(IWindow* parent) {
  (void)parent;
}

// @ 0x005e49c0
bool cSPEditorVerbIcon::HandleMessage(IWindow* w, void* msg) {
  (void)w;
  (void)msg;
  return false;
}
}  // namespace SP
