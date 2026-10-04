// slice s005f6df0 - SP::cSPSwatch (retail layout) tail: destructor, Update, a derived "buy" swatch,
// and EASTL helpers (string compare, hash_map<Key,...> node/rehash/erase).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <string.h>
#include <math.h>

#define PV(n) virtual void _pv##n();
#define PV10(n) PV(n##0) PV(n##1) PV(n##2) PV(n##3) PV(n##4) PV(n##5) PV(n##6) PV(n##7) PV(n##8) PV(n##9)

void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void operator delete[](void* p);
inline void* operator new(size_t, void* p) throw() { return p; }

#define EASTL_ALLOCATOR_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

namespace EA {
namespace ResourceMan {
struct Key {
  uint32_t instanceID;
  uint32_t typeID;
  uint32_t groupID;
};
bool operator!=(const Key& a, const Key& b);
}  // namespace ResourceMan

template <typename T>
class AutoRefCount {
 public:
  T* mpObject;
  AutoRefCount() : mpObject(0) {}
  ~AutoRefCount() {
    if (mpObject) mpObject->Release();
  }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};

namespace UTFWin {
class IWindow {
 public:
  PV(0)
  virtual int Release();
  PV10(1) PV10(2) PV(30)
  virtual void SetShadeColor(uint32_t color);  // +0x5c
  PV10(w)
  virtual void SetVisible(bool visible);  // +0x88
};
class IWinProc {
 public:
  virtual ~IWinProc() {}
  PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20)
};
}  // namespace UTFWin

template <typename T>
class RefCountVTemplate {
 public:
  virtual ~RefCountVTemplate() {}
  virtual int AddRef();
  virtual int Release();
  T mnRefCount;
};

namespace Messaging {
class IHandler {
 public:
  virtual ~IHandler() {}
  virtual bool HandleMessage(uint32_t messageID, void* pMessage);
};
}  // namespace Messaging

class Stopwatch {
 public:
  uint64_t mnStartTime;
  uint64_t mnTotalTime;
  int mnUnits;
  float mfStopwatchCyclesToUnitsCoefficient;
  Stopwatch(int units, bool bStartImmediately);  // 0x0093a560
  void Restart();                                // 0x00571e80
  void Stop();                                   // 0x0093a2e0
  uint64_t GetElapsedTime() const;               // 0x0093a5e0
  bool IsRunning() const { return mnStartTime != 0; }
};
}  // namespace EA

namespace eastl {
struct sp_vector_allocator {
  const char* mpName;
  uint32_t mFlags;
  void deallocate(void* p) {
    if (((int*)p)[-1]) operator delete[](p);
  }
};

template <typename T>
class vector {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  sp_vector_allocator mAllocator;
  ~vector() {
    DoDestroyValues(mpBegin, mpEnd);
    if (mpBegin) mAllocator.deallocate(mpBegin);
  }
  void DoDestroyValues(T* first, T* last);
};

// trivially destructible element type: no DoDestroyValues call
template <typename T>
class pod_vector {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  sp_vector_allocator mAllocator;
  ~pod_vector() {
    if (mpBegin) mAllocator.deallocate(mpBegin);
  }
};
}  // namespace eastl

class cSPUILayeredObject {
 public:
  PV(0) PV(1)
  virtual int Release();
  void SetVisible(bool visible);  // 0x0080d7c0
  void* GetDrawable();            // 0x0093b6c0
};

class cSPUIModelsAndEffectsRenderer {
 public:
  int Release();  // 0x0080df80
  void* GetDrawable();  // 0x0080d5f0
};

class cSPUIRenderTarget {
 public:
  PV(0)
  virtual int Release();
  PV10(1) PV10(2) PV(30) PV(31) PV(32) PV(33)
  virtual void SetVisible(bool visible);  // +0x88
};

namespace SP {
class cMWModel;

class cMWWorld {
 public:
  PV10(0) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
  virtual void UpdateModel(cMWModel* model);  // +0x58
  PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV10(3) PV10(4) PV10(5) PV10(6) PV10(7) PV10(8)
  PV(90) PV(91)
  virtual void DestroyModel(cMWModel* model, bool flag);  // +0x170
};

class cMWModel {
 public:
  cMWWorld* mpWorld;   // +0x00
  union {
    uint32_t mFlags;   // +0x04
    volatile struct {
      uint32_t mbFlag0 : 1;
      uint32_t mbUseLOD : 1;
      uint32_t mbFlag2 : 1;
      uint32_t mbForceLOD : 1;
    };
  };
  char pad08[0x38];
  int mnRefCount;      // +0x40
  char pad44[0x18];
  uint8_t mLODMode;    // +0x5c

  bool IsLoaded() const { return (mFlags >> 14) & 1; }
  bool IsTransient() const { return (mFlags >> 31) & 1; }
  void Release() {
    if (mnRefCount > 1)
      --mnRefCount;
    else
      mpWorld->DestroyModel(this, IsTransient());
  }
};

class cAnimatingCreature {
 public:
  int Release();  // 0x00a05270
};

class cISPCreatureAnimWorld {
 public:
  PV(0)
  virtual int Release();
};

class cSPEditorPaintTheme {
 public:
  void Apply(cMWModel* model, cMWWorld* world, int a, int b);  // 0x004b31d0
};

struct cSPPaintThemeHolder {
  PV(0) PV(1)
  virtual int Release();
  char pad04[0x8];
  cSPEditorPaintTheme* mpTheme;  // +0x0c
};

struct Point2D {
  float x, y;
  Point2D() {}
  Point2D(float x_, float y_) : x(x_), y(y_) {}
  Point2D(const Point2D& b) : x(b.x), y(b.y) {}
  Point2D& operator=(const Point2D& b) {
    x = b.x;
    y = b.y;
    return *this;
  }
  Point2D operator-(const Point2D& b) const { return Point2D(x - b.x, y - b.y); }
  Point2D operator*(float f) const { return Point2D(x * f, y * f); }
  Point2D& operator+=(const Point2D& b) {
    x += b.x;
    y += b.y;
    return *this;
  }
  float Length() const { return sqrtf(x * x + y * y); }
};
inline void Interpolate(Point2D& cur, const Point2D& target, float t) {
  cur.x = (target.x - cur.x) * t + cur.x;
  cur.y = (target.y - cur.y) * t + cur.y;
}

struct cSPMatrix3 {
  float m[9];
};

// retail cSwatch3DView: 0x30 bytes (2008 PDB: 0x28)
class cSwatch3DView {
 public:
  bool mVisible;                                              // +0x00
  EA::AutoRefCount<cSPUILayeredObject> mLayeredObject;        // +0x04
  eastl::vector<EA::AutoRefCount<cMWModel> > mModels;         // +0x08
  EA::AutoRefCount<cAnimatingCreature> mAnimatingCreature;    // +0x1c
  EA::AutoRefCount<cISPCreatureAnimWorld> mAnimWorld;         // +0x20
  EA::AutoRefCount<EA::UTFWin::IWindow> mWindow;              // +0x24
  EA::AutoRefCount<cSPUIRenderTarget> mRenderTarget;          // +0x28
  EA::AutoRefCount<cSPUIModelsAndEffectsRenderer> mRenderer;  // +0x2c

  ~cSwatch3DView();         // 0x005f6b40
  void Update(int deltaTime);  // 0x005f3810
  __forceinline void Hide() {
    if (mLayeredObject) mLayeredObject->SetVisible(false);
    if (mRenderer) mWindow->SetVisible(false);
    mVisible = false;
  }
  void* GetDrawable() {
    if (mLayeredObject) return mLayeredObject->GetDrawable();
    if (mRenderer) return mRenderer.mpObject->GetDrawable();
    return 0;
  }
};

void SizeViewportToWindowAndRemainOnScreen(void* drawable, EA::UTFWin::IWindow* window, float scale, Point2D center);  // 0x005f2390
}  // namespace SP

namespace SPUIHelpers {
void SetWindowAlpha(EA::UTFWin::IWindow* window, float alpha);                         // 0x00804fc0
float GetWindowAlpha(EA::UTFWin::IWindow* window);                                     // 0x00805040
void SetWindowScale(EA::UTFWin::IWindow* window, float scale);                         // 0x00808210
void SetWindowSPMaterial(EA::UTFWin::IWindow* window, uint32_t material, int flags);   // 0x00808ad0
struct Rect { float x1, y1, x2, y2; };
void GetWindowArea(Rect* area, EA::UTFWin::IWindow* window);                                       // 0x00805fe0
}  // namespace SPUIHelpers

float AngleDifference(float a, float b);                 // 0x00699730
float RotateAngleTowards(float from, float to, float step);  // 0x0069b840
uint32_t GetAudioContext();                              // 0x00435e90
void PlayAudioEvent(uint32_t id, uint32_t context);      // 0x00435ed0

namespace SP {
struct Color {
  uint8_t b, g, r, a;
  float GetAlpha() const { return (float)a / 255.0f; }
};

class cSPSwatch : public EA::UTFWin::IWinProc, public EA::RefCountVTemplate<int>, public EA::Messaging::IHandler {
 public:
  cSwatch3DView m3DView;                                       // +0x10
  EA::ResourceMan::Key mOriginalItemKey;                       // +0x40
  EA::ResourceMan::Key mModelKey;                              // +0x4c
  uint32_t mUnknown58;                                         // +0x58
  EA::AutoRefCount<EA::UTFWin::IWindow> mBaseWindow;           // +0x5c
  EA::AutoRefCount<EA::UTFWin::IWindow> mModelWindow;          // +0x60
  float mActualViewportScale;                                  // +0x64
  float mActualAngle;                                          // +0x68
  float mTargetAngle;                                          // +0x6c
  float mTargetViewportScale;                                  // +0x70
  float mOriginalWindowArea[4];                                // +0x74
  Point2D mActualViewportCenter;                               // +0x84
  Point2D mTargetViewportCenter;                               // +0x8c
  float mMaxViewportScaleFactor;                               // +0x94
  cSPMatrix3 mSwatchRotation;                                  // +0x98
  bool mUnknownBC;                                             // +0xbc
  float mTargetWindowAlpha;                                    // +0xc0
  float mCurrentWindowAlpha;                                   // +0xc4
  Color mCurrentShadeColor;                                    // +0xc8
  Color mTargetShadeColor;                                     // +0xcc
  uint32_t mCurrentMaterial;                                   // +0xd0
  uint32_t mTargetMaterial;                                    // +0xd4
  float mTargetModelAlpha;                                     // +0xd8
  float mCurrentModelAlpha;                                    // +0xdc
  uint32_t mUnknownE0;                                         // +0xe0
  uint32_t mUnknownE4;                                         // +0xe4
  bool mLoadModelOnDemand;                                     // +0xe8
  bool mNeverLoadModel;                                        // +0xe9
  bool mDisplay3DModel;                                        // +0xea
  bool mBakedAsset;                                            // +0xeb
  bool mMouseOverWindow;                                       // +0xec
  EA::AutoRefCount<cAnimatingCreature> mAnimatingCreature;     // +0xf0
  int mLOD;                                                    // +0xf4
  uint32_t mAnimID;                                            // +0xf8
  bool mAnimIsIdle;                                            // +0xfc
  bool mIsPlayingAnimation;                                    // +0xfd
  uint32_t mTriggerBehavior;                                   // +0x100
  eastl::vector<EA::AutoRefCount<cMWModel> > mStaticEffects;   // +0x104
  EA::AutoRefCount<cMWModel> mModel;                           // +0x118
  eastl::vector<EA::AutoRefCount<cMWModel> > mAdditionalModels;  // +0x11c
  eastl::pod_vector<EA::ResourceMan::Key> mAdditionalModelKeys;  // +0x130
  EA::AutoRefCount<EA::UTFWin::IWindow> mTooltipWindow;        // +0x144
  eastl::pod_vector<uint32_t> mStaticEffectsTransforms;        // +0x148
  float mLifetime;                                             // +0x15c
  bool mHasBeenFramed;                                         // +0x160
  bool mModelLoaded;                                           // +0x161
  bool mModelLoadStarted;                                      // +0x162
  bool mIsModelBaked;                                          // +0x163
  bool mCreatedCreature;                                       // +0x164
  bool mUseStaticEffects;                                      // +0x165
  bool mVisible;                                               // +0x166
  bool mForceRotation;                                         // +0x167
  bool mIgnoreFocusChange;                                     // +0x168
  bool mWantToRenderModel;                                     // +0x169
  bool mAllowRotation;                                         // +0x16a
  bool mAllowTooltip;                                          // +0x16b
  bool mHideModelWindow;                                       // +0x16c
  bool mCapturedMouseButtons[5];                               // +0x16d
  uint32_t mCamera;                                            // +0x174
  uint32_t mID;                                                // +0x178

  cSPSwatch();            // 0x005f6bd0
  virtual ~cSPSwatch();
  virtual void UpdateSwatch(int deltaTime);    // +0x54
  PV(22)
  virtual bool NeedsLayout();                  // +0x5c
  virtual void DoLayout();                     // +0x60
  PV(25)
  virtual void UpdateRotation();               // +0x68
  virtual void OnShow();                       // +0x6c
  virtual void OnHide();                       // +0x70
  virtual bool IsShown();                      // +0x74

  void Update(int deltaTime);
  void ReleaseModelWindow();                   // 0x005f68a0
  bool IsModelVisible();                       // 0x005f2180
  void LoadModel(const EA::ResourceMan::Key& key);  // 0x005f5b40
  void OnModelLoad();                          // 0x005f69a0
  void FrameModel();                           // 0x005f3cf0
};

// @ 0x005f6df0
cSPSwatch::~cSPSwatch() {
  if (mBaseWindow) ReleaseModelWindow();
}

// @ 0x005f6f40
void cSPSwatch::Update(int deltaTime) {
  if (!mModelWindow || !mBaseWindow) return;
  m3DView.Update(deltaTime);
  if (NeedsLayout()) DoLayout();
  UpdateSwatch(deltaTime);

  float t = (float)(uint32_t)deltaTime * 0.012f;
  if (t > 1.0f) t = 1.0f;

  Interpolate(mActualViewportCenter, mTargetViewportCenter, t);
  const float dy = mTargetViewportCenter.y - mActualViewportCenter.y;
  const float dx = mTargetViewportCenter.x - mActualViewportCenter.x;
  if (sqrtf(dy * dy + dx * dx) < 1.0f) {
    mActualViewportCenter.x = mTargetViewportCenter.x;
    mActualViewportCenter.y = mTargetViewportCenter.y;
  }

  if (mAllowRotation) {
    mActualAngle = RotateAngleTowards(mActualAngle, mTargetAngle, AngleDifference(mTargetAngle, mActualAngle) * t);
  } else {
    mActualAngle = 0.0f;
    mTargetAngle = 0.0f;
  }
  if (AngleDifference(mActualAngle, mTargetAngle) < 0.01f) mActualAngle = mTargetAngle;

  mActualViewportScale = (mTargetViewportScale - mActualViewportScale) * t + mActualViewportScale;
  if (fabsf(mActualViewportScale - mTargetViewportScale) < 0.01f) mActualViewportScale = mTargetViewportScale;

  const bool shown = IsShown();
  if (shown && !mModelLoadStarted && !mModelLoaded && !mNeverLoadModel) {
    LoadModel(mModelKey);
    if (mModel && !mAnimatingCreature) mModel->mpWorld->UpdateModel(mModel);
  }
  if (mModel && mModel->IsLoaded() && !mModelLoaded) OnModelLoad();
  if (mModelLoaded && !mHasBeenFramed) FrameModel();

  const bool visible = (IsModelVisible() && shown) ? true : false;
  if (visible != m3DView.mVisible) {
    if (visible)
      OnShow();
    else
      OnHide();
  } else if (mModelWindow) {
    if (mCurrentWindowAlpha != SPUIHelpers::GetWindowAlpha(mModelWindow)) SPUIHelpers::SetWindowAlpha(mModelWindow, mCurrentWindowAlpha);
  }
  if (mHideModelWindow) SPUIHelpers::SetWindowAlpha(mModelWindow, 0.0f);

  UpdateRotation();

  if (mCurrentMaterial != mTargetMaterial) {
    mCurrentMaterial = mTargetMaterial;
    if (mModelWindow && !mHideModelWindow) SPUIHelpers::SetWindowSPMaterial(mModelWindow, mCurrentMaterial, 0);
  }
  if (*(uint32_t*)&mCurrentShadeColor != *(uint32_t*)&mTargetShadeColor) {
    *(uint32_t*)&mCurrentShadeColor = *(uint32_t*)&mTargetShadeColor;
    if (mModelWindow && !mHideModelWindow) mModelWindow->SetShadeColor(*(uint32_t*)&mCurrentShadeColor);
  }
  if (mCurrentWindowAlpha != mTargetWindowAlpha) {
    mCurrentWindowAlpha = mTargetWindowAlpha;
    if (mModelWindow && !mHideModelWindow) {
      const float alpha = mCurrentShadeColor.GetAlpha();
      SPUIHelpers::SetWindowAlpha(mModelWindow, alpha * mCurrentWindowAlpha);
    }
  }
  if (mCurrentModelAlpha != mTargetModelAlpha) {
    mCurrentModelAlpha = mTargetModelAlpha;
    if (mTargetModelAlpha != 0.0f) return;
  } else {
    if (mCurrentModelAlpha != 0.0f) return;
    if (!m3DView.mVisible) return;
  }
  m3DView.Hide();
}

// retail-only swatch subclass (vtables 0x013f9eb8/0x013f9ea4/0x01489590) with a glow/purchase animation
class cSPAnimatedSwatch : public cSPSwatch {
 public:
  EA::AutoRefCount<cSPPaintThemeHolder> mpPaintTheme;     // +0x17c
  EA::AutoRefCount<cSPPaintThemeHolder> mpUnknown180;     // +0x180
  bool mbPlayingGlow;                                     // +0x184
  float mfUnknown188;                                     // +0x188
  EA::AutoRefCount<EA::UTFWin::IWindow> mUnknown18C;      // +0x18c
  uint32_t mUnknown190;                                   // +0x190
  EA::AutoRefCount<EA::UTFWin::IWindow> mUnknown194;      // +0x194
  bool mbUnknown198;                                      // +0x198
  bool mbUnknown199;                                      // +0x199
  bool mbPaintApplied;                                    // +0x19a
  EA::Stopwatch mGlowTimer;                               // +0x1a0
  EA::AutoRefCount<EA::UTFWin::IWindow> mGlowWindow;      // +0x1b8
  EA::AutoRefCount<EA::UTFWin::IWindow> mFlashWindow;     // +0x1bc

  cSPAnimatedSwatch();
  virtual ~cSPAnimatedSwatch();
  void Update(int deltaTime);
};

// @ 0x005f7380
cSPAnimatedSwatch::cSPAnimatedSwatch()
    : mbPlayingGlow(false),
      mfUnknown188(1.0f),
      mUnknown190(0),
      mbUnknown198(true),
      mbPaintApplied(false),
      mGlowTimer(0, false) {}

// @ 0x005f7400
cSPAnimatedSwatch::~cSPAnimatedSwatch() {}

// @ 0x005f7490
void cSPAnimatedSwatch::Update(int deltaTime) {
  if (!mBaseWindow || !mModelWindow) return;
  if (m3DView.GetDrawable())
    SizeViewportToWindowAndRemainOnScreen(m3DView.GetDrawable(), mModelWindow, mActualViewportScale, mActualViewportCenter);

  if (mGlowWindow && mFlashWindow) {
    if (!mGlowTimer.IsRunning() && mbPlayingGlow) {
      SPUIHelpers::SetWindowAlpha(mBaseWindow, 0.0f);
      SPUIHelpers::Rect area;
      SPUIHelpers::GetWindowArea(&area, mBaseWindow);
      if ((area.x1 + area.x2) * 0.5f > 0.0f) {
        mGlowTimer.Restart();
        PlayAudioEvent(0xfd91ff9d, GetAudioContext());
      }
    }
    if (mGlowTimer.IsRunning()) {
      const float elapsed = (float)mGlowTimer.GetElapsedTime() * 0.0005f;
      if (elapsed < 0.5f) {
        const float u = elapsed * 2.0f;
        SPUIHelpers::SetWindowAlpha(mBaseWindow, 0.0f);
        SPUIHelpers::SetWindowAlpha(mGlowWindow, u);
        SPUIHelpers::SetWindowScale(mGlowWindow, u * u * (1.2f - 0.25f) + 0.25f);
        SPUIHelpers::SetWindowAlpha(mFlashWindow, 1.0f - u);
      } else if (elapsed < 1.0f) {
        const float u = (elapsed - 0.5f) * 2.0f;
        const float alpha = mCurrentShadeColor.GetAlpha();
        SPUIHelpers::SetWindowAlpha(mBaseWindow, alpha * u);
        SPUIHelpers::SetWindowAlpha(mGlowWindow, (1.0f - u) * (1.0f - 0.65f) + 0.65f);
        SPUIHelpers::SetWindowScale(mGlowWindow, (1.0f - u * u) * (1.2f - 0.9f) + 0.9f);
        SPUIHelpers::SetWindowAlpha(mFlashWindow, 0.0f);
      } else {
        mbPlayingGlow = false;
        SPUIHelpers::SetWindowAlpha(mBaseWindow, mCurrentShadeColor.GetAlpha());
        SPUIHelpers::SetWindowAlpha(mGlowWindow, 0.65f);
        SPUIHelpers::SetWindowScale(mGlowWindow, 0.9f);
        SPUIHelpers::SetWindowAlpha(mFlashWindow, 0.0f);
        mGlowTimer.Stop();
      }
    }
  }

  cSPSwatch::Update(deltaTime);

  cMWModel* model = mModel;
  if (mpPaintTheme && mpPaintTheme->mpTheme && !mbPaintApplied && model && model->IsLoaded()) {
    model->mbUseLOD = false;
    model->mbForceLOD = true;
    model->mLODMode = 7;
    mpPaintTheme->mpTheme->Apply(model, model->mpWorld, 0, 0);
    mbPaintApplied = true;
  }
}
}  // namespace SP

namespace eastl {
// @ 0x005f7870
int Compare(const char* p1, const char* p2, size_t n) { return memcmp(p1, p2, n); }

template <typename T>
inline const T& min_alt(const T& a, const T& b) {
  return b < a ? b : a;
}

inline size_t CharStrlen(const char* p) {
  const char* pCurrent = p;
  while (*pCurrent) ++pCurrent;
  return (size_t)(pCurrent - p);
}

class string {
 public:
  char* mpBegin;
  char* mpEnd;
  char* mpCapacity;
  sp_vector_allocator mAllocator;

  static int compare(const char* pBegin1, const char* pEnd1, const char* pBegin2, const char* pEnd2) {
    const ptrdiff_t n1 = pEnd1 - pBegin1;
    const ptrdiff_t n2 = pEnd2 - pBegin2;
    const ptrdiff_t nMin = min_alt(n1, n2);
    const int cmp = Compare(pBegin1, pBegin2, (size_t)nMin);
    return cmp != 0 ? cmp : (n1 < n2 ? -1 : (n1 > n2 ? 1 : 0));
  }
  int comparei(const char* p) const;
};

// @ 0x005f79e0
int string::comparei(const char* p) const { return compare(mpBegin, mpEnd, p, p + strlen(p)); }

class string16 {
 public:
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  sp_vector_allocator mAllocator;
  size_t size() const { return (size_t)(mpEnd - mpBegin); }
  wchar_t& operator[](size_t i) { return mpBegin[i]; }
  void make_lower();  // 0x005e8e80
};
}  // namespace eastl

// @ 0x005f7970
void NormalizePath(eastl::string16& path) {
  path.make_lower();
  for (size_t i = 0; i < path.size(); ++i) {
    if (path[i] == L'\\') path[i] = L'/';
  }
}

namespace EA {
namespace ResourceMan {
// @ 0x005f78f0
bool operator!=(const Key& a, const Key& b) {
  return !(a.instanceID == b.instanceID && a.typeID == b.typeID && a.groupID == b.groupID);
}
}  // namespace ResourceMan
}  // namespace EA

namespace eastl {
template <typename K, typename V>
struct pair {
  K first;
  V second;
  pair(const K& k, const V& v) : first(k), second(v) {}
};

template <typename Value>
struct hash_node {
  Value mValue;
  hash_node* mpNext;
};

template <typename T, typename Node>
struct hashtable_iterator {
  Node* mpNode;
  Node** mpBucket;
  hashtable_iterator() {}
  hashtable_iterator(Node* pNode, Node** pBucket) : mpNode(pNode), mpBucket(pBucket) {}
  void increment() {
    mpNode = mpNode->mpNext;
    while (mpNode == 0) mpNode = *++mpBucket;
  }
  hashtable_iterator& operator++() {
    increment();
    return *this;
  }
};

struct allocator {
  void* allocate(size_t n) { return operator new[](n, "Editor", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1); }
  void deallocate(void* p) { operator delete[](p); }
};

template <typename Value>
class hashtable {
 public:
  typedef hash_node<Value> node_type;
  typedef hashtable_iterator<Value, node_type> iterator;

  uint32_t mHashCodeBase;          // +0x00
  node_type** mpBucketArray;       // +0x04
  uint32_t mnBucketCount;          // +0x08
  uint32_t mnElementCount;         // +0x0c
  float mRehashPolicy[3];          // +0x10
  allocator mAllocator;            // +0x1c

  static uint32_t hash_of(const Value& v) { return v.first.groupID; }
  node_type** DoAllocateBuckets(uint32_t n) {
    node_type** const pBucketArray = (node_type**)mAllocator.allocate((n + 1) * sizeof(node_type*));
    memset(pBucketArray, 0, n * sizeof(node_type*));
    pBucketArray[n] = reinterpret_cast<node_type*>((uintptr_t)~0);
    return pBucketArray;
  }
  void DoFreeBuckets(node_type** pBucketArray, uint32_t n) {
    if (n > 1) mAllocator.deallocate(pBucketArray);
  }
  void DoFreeNode(node_type* pNode) { mAllocator.deallocate(pNode); }
  void DoRehash(uint32_t nNewBucketCount);
  node_type* DoAllocateNode(const Value& value);
  iterator erase(iterator i);
};

template <typename Value>
void hashtable<Value>::DoRehash(uint32_t nNewBucketCount) {
  node_type** const pBucketArray = DoAllocateBuckets(nNewBucketCount);
  for (uint32_t i = 0; i < mnBucketCount; ++i) {
    node_type* pNode;
    while ((pNode = mpBucketArray[i]) != 0) {
      const uint32_t nNewBucketIndex = hash_of(pNode->mValue) % nNewBucketCount;
      mpBucketArray[i] = pNode->mpNext;
      pNode->mpNext = pBucketArray[nNewBucketIndex];
      pBucketArray[nNewBucketIndex] = pNode;
    }
  }
  DoFreeBuckets(mpBucketArray, mnBucketCount);
  mnBucketCount = nNewBucketCount;
  mpBucketArray = pBucketArray;
}

template <typename Value>
typename hashtable<Value>::node_type* hashtable<Value>::DoAllocateNode(const Value& value) {
  node_type* const pNode = (node_type*)mAllocator.allocate(sizeof(node_type));
  ::new (&pNode->mValue) Value(value);
  pNode->mpNext = 0;
  return pNode;
}

template <typename Value>
typename hashtable<Value>::iterator hashtable<Value>::erase(iterator i) {
  iterator iNext(i.mpNode, i.mpBucket);
  iNext.increment();
  node_type* pNode = i.mpNode;
  node_type* pNodeCurrent = *i.mpBucket;
  if (pNodeCurrent == pNode)
    *i.mpBucket = pNodeCurrent->mpNext;
  else {
    node_type* pNodeNext = pNodeCurrent->mpNext;
    while (pNodeNext != pNode) {
      pNodeCurrent = pNodeNext;
      pNodeNext = pNodeCurrent->mpNext;
    }
    pNodeCurrent->mpNext = pNodeNext->mpNext;
  }
  DoFreeNode(pNode);
  --mnElementCount;
  return iNext;
}
}  // namespace eastl

typedef eastl::pair<EA::ResourceMan::Key, EA::ResourceMan::Key> KeyPair;

struct KeyPairEntry {  // pair<Key,Key>-like value with a user copy constructor
  EA::ResourceMan::Key first;
  EA::ResourceMan::Key second;
  KeyPairEntry(const KeyPairEntry& o) : first(o.first), second(o.second) {}
};
struct KeyRecord {  // 0x1c-byte value
  EA::ResourceMan::Key first;
  uint32_t value[4];
};

// @ 0x005f7940  pair<Key,Key>::pair(const Key&, const Key&)
template struct eastl::pair<EA::ResourceMan::Key, EA::ResourceMan::Key>;

// @ 0x005f79b0  hashtable_iterator::operator++ (0x1c-byte values)
template struct eastl::hashtable_iterator<KeyRecord, eastl::hash_node<KeyRecord> >;

// @ 0x005f7b80  hashtable<KeyPairEntry>::DoAllocateNode
template class eastl::hashtable<KeyPairEntry>;

// @ 0x005f7a50  hashtable<pair<Key,Key>>::erase
// @ 0x005f7be0  hashtable<pair<Key,Key>>::DoRehash
// @ 0x005f7c90  hashtable<pair<Key,Key>>::DoAllocateNode
template class eastl::hashtable<KeyPair>;
