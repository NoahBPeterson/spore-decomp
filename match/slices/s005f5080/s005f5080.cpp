// slice s005f2780 -- SP::cSPSwatch (the 3D model swatch window proc: HandleMessage, DoMessage,
// viewport/rotation updates, image layers, show/hide, capture helpers) and a palette-swatch
// subclass (cost display, cursor, rollover), plus eastl::vector<AutoRefCount<cMWModel>>::DoDestroyValues.
// Retail cSPSwatch is 0x17c bytes (mID at +0x178); fields after it belong to the subclass.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include <math.h>
#include "types.h"

extern "C" void EASTL_allocator_deallocate(void* p);  // 0x00f47380
void* operator new(unsigned int n, const char* name, int flags, unsigned int debugFlags,
                   const char* file, int line);  // 0x00f473a0
#define EASTL_ALLOCATOR_FILE \
  "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

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
  AutoRefCount& operator=(const AutoRefCount& x) { return operator=(x.mpObject); }
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
class RefCountTemplate {
 public:
  RefCountTemplate() : mRefCount(0) {}
  virtual ~RefCountTemplate() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
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
  virtual int AddRef() = 0;
  virtual int Release() = 0;
  virtual void* Cast(uint32_t typeID) const = 0;
};
}  // namespace COM

namespace ResourceMan {
struct Key {
  unsigned int mInstance, mType, mGroup;
  bool operator==(const Key& b) const {
    return mInstance == b.mInstance && mType == b.mType && mGroup == b.mGroup;
  }
  Key() : mInstance(0), mType(0), mGroup(0) {}
  Key(unsigned int instance, unsigned int type, unsigned int group)
      : mInstance(instance), mType(type), mGroup(group) {}
};
}  // namespace ResourceMan

struct Point2D {
  float x, y;
  Point2D() {}
  Point2D(float ax, float ay) : x(ax), y(ay) {}
  Point2D(const Point2D& p) : x(p.x), y(p.y) {}
  Point2D& operator=(const Point2D& p) {
    x = p.x;
    y = p.y;
    return *this;
  }
};

struct RectT {
  RectT() {}
  float left, top, right, bottom;
  RectT(const RectT& r) : left(r.left), top(r.top), right(r.right), bottom(r.bottom) {}
  bool Contains(const Point2D& p) const {
    return p.x >= left && p.y >= top && p.x < right && p.y < bottom;
  }
};

namespace UTFWin {
class IWinProc;
class IWindow : public COM::IUnknown32 {
 public:
  PV(3)
  virtual IWindow* GetParent();                     // +0x10
  PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual uint32_t GetFlags();                      // +0x28
  PV(11) PV(12) PV(13)
  virtual const RectT& GetRealArea();               // +0x38
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22)
  virtual void SetShadeColor(uint32_t color);       // +0x5c
  PV(24) PV(25) PV(26)
  virtual void SetArea(const RectT& area);          // +0x6c
  PV(28) PV(29)
  virtual void SetCursorID(uint32_t id);            // +0x78
  virtual void SetFlag(int flag, bool value);       // +0x7c
  virtual void SetCaption(const wchar_t* caption);  // +0x80
  PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41)
  virtual int IsAnimationDone();                    // +0xa8
  PV(43) PV(44) PV(45) PV(46) PV(47)
  virtual Point2D GlobalToLocal(Point2D p);         // +0xc0
  PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58)
  PV(59) PV(60) PV(61) PV(62) PV(63) PV(64)
  virtual void AddWinProc(IWinProc* proc);     // +0x104
  virtual void RemoveWinProc(IWinProc* proc);  // +0x108
};

struct Message {
  uint32_t pad0[2];
  uint32_t mEventType;                         // +0x8
  union { uint32_t mParam0c; float mX; };      // +0xc
  union { uint32_t mParam10; float mY; };      // +0x10
  uint32_t mModifiers;                         // +0x14
  union { uint32_t mButton; IWindow* mpWindow; struct cCursorData* mpCursorData; };
};
struct cCursorData { uint32_t pad[6]; uint32_t mCursorID; };  // +0x18
struct MessageDummy {  // +0x18
};

class IWinProc : public COM::IUnknown32 {
 public:
  virtual void* CastInterface(uint32_t typeID);  // +0xc
  virtual bool DoMessage(IWindow* window, const Message& message) = 0;
};
}  // namespace UTFWin

namespace Messaging {
class IHandler {
 public:
  virtual ~IHandler() {}
  virtual bool HandleMessage(uint32_t messageID, void* message) = 0;
};
class IHandlerRC : public IHandler {
 public:
  virtual int AddRef() = 0;
  virtual int Release() = 0;
};
class Server {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void MessageSend(uint32_t messageID, void* message, IHandler* handler);  // +0x14
  PV(6) PV(7) PV(8)
  virtual void AddHandler(IHandler* handler, uint32_t messageID);  // +0x24
  PV(10)
  virtual void RemoveHandler(IHandler* handler, uint32_t messageID, int priority);  // +0x2c
};
void RemoveHandler(Server* server, IHandler* handler, const uint32_t* ids, uint32_t count,
                   int priority);  // 0x00571db0

struct AutoHandler {
  Server* mpServer;
  IHandler* mpHandler;
  const uint32_t* mpIdArray;
  uint32_t mnIdArrayCount;
  int mnPriority;
  AutoHandler() : mpServer(0), mpHandler(0), mpIdArray(0), mnIdArrayCount(0), mnPriority(0) {}
  ~AutoHandler() { Clear(); }
  void Clear() {
    if (mpServer) {
      Server* const pServer = mpServer;
      mpServer = 0;
      RemoveHandler(pServer, mpHandler, mpIdArray, mnIdArrayCount, mnPriority);
    }
  }
};
}  // namespace Messaging
}  // namespace EA

using EA::AutoRefCount;
using EA::ResourceMan::Key;
using EA::UTFWin::IWindow;
using EA::UTFWin::IWinProc;
using EA::UTFWin::Message;

struct cDirectPropertyList;
class cSPUILayout : public EA::RefCountVTemplate<int> {
 public:
  void Shutdown(bool destroyWindows);                                              // 0x00811ad0
  cSPUILayout();                                                                   // 0x00810000
  void Init(const Key& key, bool visible, uint32_t parentID);                      // 0x008120d0
  void SetParentWin(IWindow* window, bool visible, uint32_t parentID);             // 0x008121b0
  IWindow* FindWindowByID(uint32_t id, bool recursive);                            // 0x008105b0
  uint32_t pad[4];
};

namespace SPUIHelpers {
void SetWindowAreaToParent(IWindow* window);                    // 0x00806bf0
void SetWindowImage(IWindow* window, const Key* key, int index);  // 0x00807bb0
}  // namespace SPUIHelpers


using EA::Point2D;
using EA::RectT;

namespace SP {
class cString {
 public:
  cString();   // 0x006b5060
  ~cString();  // 0x006b5240
  uint32_t pad[5];
};
EA::Messaging::Server* MessageServer();  // 0x0067dcc0

class cSPEditorEconomy {
 public:
  PV(0) PV(1)
  virtual bool IsItemAvailable(const Key* key);                   // +0x8
  virtual bool CanAfford(int currency, int cost);                 // +0xc
  virtual int GetItemStatus(const Key* key, struct cItemCostInfo* info);  // +0x10
};

struct cSPPaletteItemRollover;
struct cSPPaletteInfo : public EA::RefCountTemplate<int> {
  cSPEditorEconomy* mEconomy;               // +0x8
  void* mTheme;                             // +0xc
  void* mCollectableItems;                  // +0x10
  cSPPaletteItemRollover* mRollover;        // +0x14
  uint32_t pad18[6];
  bool mUseModelKey;                        // +0x30 (padding byte)
  bool mUseModelKeyForCost;                 // +0x31
};

struct cSPPaletteItemRollover {
  void Hide();  // 0x005ed6c0
};
class cSPSwatchManager {
 public:
  cSPPaletteItemRollover* GetSwatchRollover();  // 0x0113ae10
  class cICameraManager* GetCameraManager();    // 0x01137690
};
cSPSwatchManager* SwatchManager();  // 0x00401020

class cICameraController {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
  virtual void OnMouseEnter(bool inside);                              // +0x24
  virtual bool OnKeyDown(uint32_t key, uint32_t modifiers);            // +0x28
  virtual bool OnKeyUp(uint32_t key, uint32_t modifiers);              // +0x2c
  virtual bool OnMouseDown(uint32_t button, float x, float y, uint32_t modifiers);  // +0x30
  virtual bool OnMouseUp(uint32_t button, float x, float y, uint32_t modifiers);    // +0x34
  virtual bool OnMouseMove(float x, float y, uint32_t modifiers);                   // +0x38
  virtual bool OnMouseWheel(int wheel, float x, float y, uint32_t modifiers);       // +0x3c
};
class cICamera {
 public:
  PV(0) PV(1) PV(2)
  virtual cICameraController* Cast(uint32_t typeID);  // +0xc
};
class cICameraManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
  virtual cICamera* GetActiveCamera();  // +0x38
};

class IWindowManager {
 public:
  PV(0)
  virtual IWindow* GetMainWindow();                    // +0x4
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14)
  virtual Point2D GetMousePosition();                  // +0x3c
  PV(16) PV(17) PV(18)
  virtual void SetFocus(int which, IWindow* window);   // +0x4c
  PV(20)
  virtual IWindow* GetFocus(int which);                // +0x54
  virtual void SetCapture(int which, IWindow* window); // +0x58
  virtual void ReleaseCapture(int which, IWindow* window);  // +0x5c
};
IWindowManager* WindowManager();  // 0x0067caa0

class cInputManager {
 public:
  bool IsCapturing();                                // 0x006c1100
  void* GetCaptured();                               // 0x006c10e0
  bool SetCapture(IWindow* window, void* object);    // 0x008045a0
};
cInputManager* InputManager();  // 0x00804500

class cRenderManager {
 public:
  void SetHighlight(IWindow* window, bool a, bool b);  // 0x0080d710
};
cRenderManager* RenderManager();  // 0x0067cad0

bool IsKeyDown(int key);                     // 0x008d2fb0
int GetAudioSystem();                        // 0x00435e90
void PlayAudio(uint32_t id, int system);     // 0x00435ed0
void GetWindowGlobalArea(RectT* area, IWindow* window);  // 0x00805fe0
IWindow* CreateCostWindow(IWindow* parent);              // 0x00806370
struct cImageInfo { uint32_t pad[7]; int mWidth; int mHeight; };  // +0x1c / +0x20
cImageInfo* GetImageInfo(uint32_t imageID);              // 0x00458de0
void SetWindowImageInfo(IWindow* window, cImageInfo* image, int index);  // 0x008068d0

extern const wchar_t* const kSwatchMaterialNormal;   // 0x0151c41c
extern const wchar_t* const kSwatchMaterialCost;     // 0x0151c414
extern const wchar_t* const kSwatchMaterialLocked;   // 0x0151c418
extern const wchar_t* const kSwatchParamsBlink;      // 0x0151c420
extern const wchar_t* const kSwatchParamsDefault;    // 0x0151c424
extern uint32_t kSwatchEffectDefault;                // 0x0151c40c
extern uint32_t kSwatchEffectCreature;               // 0x0151c410
extern float kTwoPI;                                 // 0x0151c428

struct cItemCostInfo {
  cItemCostInfo();  // 0x005a7810
  ~cItemCostInfo() {}
  cString mName;        // +0x0
  cString mText;        // +0x14
  uint32_t mColor;      // +0x28
  uint32_t mImageID;    // +0x2c
  uint32_t mCost;       // +0x30
};

class cModelWorld {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14)
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24)
  virtual int GetEffectCount(class cMWModel* model);  // +0x64
  PV(26) PV(27)
  virtual void StartEffect(cMWModel* model, uint32_t effectID, int a, float b, int index);  // +0x70
  PV(29) PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42)
  PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56)
  PV(57) PV(58) PV(59) PV(60) PV(61) PV(62) PV(63) PV(64) PV(65) PV(66) PV(67) PV(68) PV(69) PV(70)
  PV(71) PV(72) PV(73) PV(74) PV(75) PV(76) PV(77) PV(78) PV(79) PV(80) PV(81) PV(82) PV(83) PV(84)
  PV(85) PV(86) PV(87) PV(88) PV(89) PV(90) PV(91)
  virtual void DestroyModel(class cMWModel* model, bool immediate);  // +0x170
};
class cMWModel {
 public:
  cModelWorld* mpWorld;  // +0x0
  uint32_t mFlags;       // +0x4
  uint32_t pad8[14];
  int mRefCount;         // +0x40
  void AddRef() { mRefCount++; }
  void Release();
};
class cModelWorldRelease {
 public:
};

class cImageLayers {
 public:
  PV(0) PV(1)
  virtual uint32_t AddLayer(uint32_t imageID, int flags);  // +0x8
  virtual void SetLayerVisible(uint32_t layer, bool on);   // +0xc
  virtual void SetLayerScaled(uint32_t layer, bool on);    // +0x10
  PV(5)
  virtual void Refresh(uint32_t layer);                    // +0x18
  PV(7)
  virtual void SetLayerTiled(uint32_t layer, bool on);     // +0x20
  virtual void SetLayerAlpha(uint32_t layer, float alpha); // +0x24
  uint32_t pad4[0x18];
  bool mVisible;  // +0x64
};

class cUILayeredObject {
 public:
  void SetVisible(bool visible);   // 0x0080d7c0
  void RemoveModel(void* model);   // 0x0080e980
  void AddModel(void* model);      // 0x0080fc50
};
class cSwatchTexture { public: void* GetTexture(); };                // 0x0080d610

namespace eastl {
template <typename T>
class vector {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  int size() const { return (int)(mpEnd - mpBegin); }
  T& operator[](int i) { return mpBegin[i]; }
  T& back() { return mpEnd[-1]; }
  void pop_back() {
    --mpEnd;
    mpEnd->~T();
  }
};
}  // namespace eastl
class cSwatchRenderer {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14)
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28)
  PV(29) PV(30) PV(31) PV(32) PV(33)
  virtual void SetTexture(void* texture);  // +0x88
};

struct cSwatch3DView {
  bool mVisible;                                            // +0x00
  cUILayeredObject* mLayeredObject;                         // +0x04
  eastl::vector<AutoRefCount<cMWModel> > mModels;           // +0x08
  uint32_t pad14;                                           // +0x14
  uint32_t pad18;                                           // +0x18
  void* mAnimWorld;                                         // +0x1c
  IWindow* mWindow;                                         // +0x20
  cSwatchRenderer* mRenderer;                               // +0x24
  uint32_t pad28;                                           // +0x28
  cSwatchTexture* mTexture;                                 // +0x2c
  void RemoveModel(cMWModel* model);                        // 0x005f4eb0
  cMWModel* AddModel(uint32_t a, uint32_t b);               // 0x005f59b0
  void RemoveAllModels();                                   // 0x005f5aa0
};

struct cModelChangedMessage {
  uint32_t pad0[2];
  uint32_t mInstanceID;  // +0x8
  uint32_t pad0c;
  uint32_t mGroupID;     // +0x10
  uint32_t pad14;
  uint32_t mTypeID;      // +0x18
};

class cSPSwatch : public IWinProc, public EA::RefCountVTemplate<int>, public EA::Messaging::IHandler {
 public:
  virtual int AddRef();
  virtual int Release();
  virtual void* Cast(uint32_t typeID) const;
  virtual void* CastInterface(uint32_t typeID);
  virtual bool DoMessage(IWindow* window, const Message& message);
  PV(5) PV(6) PV(7) PV(8)
  virtual void Vt24(void* key);                   // +0x24
  PV(10) PV(11) PV(12)
  virtual IWindow* GetWindow();                   // +0x34
  PV(14) PV(15)
  virtual void OnMouseDown();                     // +0x40
  virtual bool IsDragging();                      // +0x44
  virtual void OnMouseEnter();                    // +0x48
  virtual void OnMouseLeave();                    // +0x4c
  virtual void OnClick();                         // +0x50
  PV(21)
  virtual float GetTargetZoom();                  // +0x58
  PV(23) PV(24)
  virtual void ReloadModel();                     // +0x64
  virtual bool HandleMessage(uint32_t messageID, void* message);

  bool IsCapturedBySelf() {
    cInputManager* input = InputManager();
    if (input->IsCapturing()) {
      void* self = CastInterface(0xee3f516e);
      if (self == input->GetCaptured())
        return true;
    }
    return false;
  }
  __forceinline bool AnyMouseButtonCaptured() const {
    for (unsigned int i = 0; i < 5; i++)
      if (mCapturedMouseButtons[i])
        return true;
    return false;
  }
  void UpdateSwatchPosition(uint32_t deltaTime);
  uint32_t SetImage(uint32_t imageID, bool overlay);
  void Show3DModel();
  void Hide3DModel();
  void StartModelEffects();
  bool IsAnimating();
  bool TakeCapture();
  void EndInteraction();
  bool HasCapture();
  int IsBusy();
  void UpdateViewport(uint32_t deltaTime);

  void Init(Key* key, uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t scale);   // 0x005f4f80
  void Init(Key* key, void* a, void* b, uint32_t c, uint32_t d, uint32_t e, uint32_t f, uint32_t scale);  // 0x005f5000
  void InitInternal(IWindow* base, IWindow* modelWindow, uint32_t a3, uint32_t a4,
                    uint32_t b5, uint32_t b6, uint32_t a7, uint32_t a8);  // 0x005f3b20
  void RotateModel(uint32_t flags);       // 0x005f55e0
  void LoadModel();                       // 0x005f5b40
  void ShutDownModel();                   // 0x005f5df0
  void AddModelKey(const Key& key);       // 0x005f58f0

  cSwatch3DView m3DView;                  // +0x10
  Key mOriginalItemKey;                   // +0x40
  Key mModelKey;                          // +0x4c
  uint32_t mScaleParam;                   // +0x58
  AutoRefCount<IWindow> mBaseWindow;      // +0x5c
  AutoRefCount<IWindow> mModelWindow;     // +0x60
  float mActualViewportScale;             // +0x64
  float mActualAngle;                     // +0x68
  float mTargetAngle;                     // +0x6c
  float mTargetViewportScale;             // +0x70
  RectT mOriginalWindowArea;              // +0x74
  Point2D mActualViewportCenter;          // +0x84
  Point2D mTargetViewportCenter;          // +0x8c
  float mMaxViewportScaleFactor;          // +0x94
  float mSwatchRotation[9];               // +0x98
  bool mIsZooming;                        // +0xbc
  float mTargetWindowAlpha;               // +0xc0
  float mCurrentWindowAlpha;              // +0xc4
  uint32_t padc8;
  const wchar_t* mWindowMaterial;         // +0xcc
  uint32_t padd0;
  const wchar_t* mWindowMaterialParams;   // +0xd4
  float mTargetModelAlpha;                // +0xd8
  float mCurrentModelAlpha;               // +0xdc
  const wchar_t* mMaterial;               // +0xe0
  const wchar_t* mMaterialParams;         // +0xe4
  bool mLoadModelOnDemand;                // +0xe8
  bool mNeverLoadModel;                   // +0xe9
  bool mDisplay3DModel;                   // +0xea
  bool mBakedAsset;                       // +0xeb
  bool mMouseOverWindow;                  // +0xec
  cImageLayers* mpImageLayers;            // +0xf0
  uint32_t padf4;
  uint32_t mImageID;                      // +0xf8
  bool mImageOverlay;                     // +0xfc
  bool mImageSet;                         // +0xfd
  uint32_t pad100[6];
  AutoRefCount<cMWModel> mModel;          // +0x118
  uint32_t pad11c[17];
  bool mHasBeenFramed;                    // +0x160
  bool mModelLoaded;                      // +0x161
  bool mModelLoadStarted;                 // +0x162
  bool mIsModelBaked;                     // +0x163
  bool mCreatedCreature;                  // +0x164
  bool mUseStaticEffects;                 // +0x165
  bool mVisible;                          // +0x166
  bool mForceRotation;                    // +0x167
  bool mIgnoreFocusChange;                // +0x168
  bool mWantToRenderModel;                // +0x169
  bool mAllowRotation;                    // +0x16a
  bool mAllowTooltip;                     // +0x16b
  bool mUseEditorCameraController;        // +0x16c
  bool mCapturedMouseButtons[5];          // +0x16d
  uint32_t mCamera;                       // +0x174
  uint32_t mID;                           // +0x178
};

inline void cMWModel::Release() {
  if (mRefCount > 1)
    mRefCount--;
  else
    mpWorld->DestroyModel(this, (mFlags >> 31) & 1);
}
// ---------------------------------------------------------------------------------------------
struct cSwatchMessage {
  cSPSwatch* mpSwatch;  // +0x0
  uint32_t pad4;
  uint32_t mID;         // +0x8
  uint32_t padc;
};

class cSPPaletteSwatch : public cSPSwatch {
 public:
  bool IsMouseOutside();
  bool IsItemAvailable();
  void UpdateCostDisplay();     // 0x005f3400
  void UpdateCursor();          // 0x005f3600
  void OnRolloverEnd();
  void SetShowCost(bool show);      // 0x005f49a0
  void EndDrag();                   // 0x005f46c0

  AutoRefCount<cSPPaletteInfo> mInfo;     // +0x17c
  uint32_t pad180;
  bool mIsLocked;                         // +0x184
  uint32_t pad188;
  IWindow* mDragWindow;                   // +0x18c
  uint32_t pad190;
  AutoRefCount<IWindow> mCostWindow;      // +0x194
  bool mShowCost;                         // +0x198
  bool mDraggable;                        // +0x199
};


// ==================== slice s005f5080 ====================
// ---- helper decls ----
AutoRefCount<cMWModel>* copy_refs(AutoRefCount<cMWModel>* first, AutoRefCount<cMWModel>* last,
                                  AutoRefCount<cMWModel>* out);  // 0x5f4e10
void* cSPBoundingBox_AddBoundingBox(int, int, int);  // 0x0067cad0
void* FUN_006c10e0();                          // 0x006c10e0
void* FUN_0080db70();                          // 0x0080db70
void FUN_0080ea50(void* self);                 // 0x0080ea50
void FUN_008eb830(void* self, int v);          // 0x008eb830
void FUN_005f0380();                           // 0x005f0380
int  FUN_0080d7c0(int visible);                // 0x0080d7c0
void DoDestroyValues_ref(AutoRefCount<cMWModel>* first, AutoRefCount<cMWModel>* last);  // 0x5f3680
void* FUN_00807880(void* p, int, int);         // 0x00807880

class cRefCountedModel2 {
 public:
  PV(0) PV(1) PV(2)
  virtual cMWModel* MakeModel(uint32_t a, uint32_t b, int c);  // +0xc
};

struct KeyVec {
  Key* mpBegin;
  Key* mpEnd;
  Key* mpCapacity;
  void push_back(const Key& v);                 // 0x005f58f0
  void DoInsertValue(Key* pos, const Key& v);   // 0x4e3e10
  void clear() { mpEnd = mpBegin; }
};

struct RefVec {
  AutoRefCount<cMWModel>* mpBegin;
  AutoRefCount<cMWModel>* mpEnd;
  AutoRefCount<cMWModel>* mpCapacity;
  void clear();  // 0x005f5970
  void DoInsertValue(AutoRefCount<cMWModel>* pos, cMWModel** value);  // 0x423c40
};

class cSwatchWindow {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14)
  virtual void Vt3c(void* p);  // +0x3c
};
class cAnimWorld {
 public:
  void Release();
};

// @ 0x005F58F0
void cSPSwatch::AddModelKey(const Key& key) {
  Key* p = *(Key**)((char*)this + 0x14c);
  KeyVec& v = *(KeyVec*)((char*)this + 0x148);
  if (p < v.mpCapacity) {
    v.mpEnd = p + 1;
    if (p)
      *p = key;
  } else {
    v.DoInsertValue(p, key);
  }
}

// @ 0x005F58F0 (standalone on a KeyVec)
void KeyVec::push_back(const Key& v) {
  Key* p = mpEnd;
  if (p < mpCapacity) {
    mpEnd = p + 1;
    if (p)
      *p = v;
  } else {
    DoInsertValue(p, v);
  }
}

// @ 0x005F5970
void RefVec::clear() {
  AutoRefCount<cMWModel>* begin = mpBegin;
  AutoRefCount<cMWModel>* end = mpEnd;
  AutoRefCount<cMWModel>* p = copy_refs(end, end, begin);
  DoDestroyValues_ref(p, mpEnd);
  char* e = (char*)mpEnd;
  int n = (int)(e - (char*)begin);
  mpEnd = (AutoRefCount<cMWModel>*)(e + (-(n >> 2)) * 4);
}

// @ 0x005F59B0
cMWModel* cSwatch3DView::AddModel(uint32_t a, uint32_t b) {
  if (mLayeredObject) {
    void* box = cSPBoundingBox_AddBoundingBox(0, 0, 0);
    (void)box;
    cRefCountedModel2* mgr = (cRefCountedModel2*)FUN_006c10e0();
    cMWModel* m = mgr->MakeModel(a, b, 0x26);
    *(uint32_t*)((char*)m + 4) |= 0x2000;
    mLayeredObject->AddModel(m);
    FUN_0080d7c0(mVisible);
    return m;
  }
  if (mTexture) {
    cRefCountedModel2* mgr = (cRefCountedModel2*)FUN_0080db70();
    cMWModel* m = mgr->MakeModel(a, b, 0x22);
    *(uint32_t*)((char*)m + 4) |= 0x2000;
    ++*(uint32_t*)((char*)m + 0x40);
    AutoRefCount<cMWModel>* p = mModels.mpEnd;
    if (p < mModels.mpCapacity) {
      mModels.mpEnd = p + 1;
      if (p) {
        p->mpObject = m;
        ++*(uint32_t*)((char*)m + 0x40);
      }
    } else {
      ((RefVec*)&mModels)->DoInsertValue(p, &m);
    }
    if (m) {
      if (*(uint32_t*)((char*)m + 0x40) > 1) {
        --*(uint32_t*)((char*)m + 0x40);
        return m;
      }
      m->Release();
    }
    return m;
  }
  return 0;
}

// @ 0x005F5AA0
void cSwatch3DView::RemoveAllModels() {
  if (mLayeredObject == 0) {
    if (mWindow == 0)
      return;
    ((RefVec*)&mModels)->clear();
    if (mAnimWorld == 0)
      return;
    ((cSwatchWindow*)mWindow)->Vt3c(mAnimWorld);
  } else {
    FUN_0080ea50(mLayeredObject);
    FUN_008eb830(mLayeredObject, 0);
    if (mAnimWorld == 0)
      return;
    SwatchManager();
    FUN_005f0380();
  }
  if (mAnimWorld == 0)
    return;
  cAnimWorld* w = (cAnimWorld*)mAnimWorld;
  mAnimWorld = 0;
  w->Release();
}

// @ 0x005F5DF0
void cSPSwatch::ShutDownModel() {
  mModel = (cMWModel*)0;
  ((RefVec*)((char*)this + 0x11c))->clear();
  ((RefVec*)((char*)this + 0x130))->clear();
  ((RefVec*)((char*)this + 0x104))->clear();
  ((KeyVec*)((char*)this + 0x148))->clear();
  void* effect = *(void**)((char*)this + 0xf0);
  if (effect) {
    *(void**)((char*)this + 0xf0) = 0;
    ((cAnimWorld*)effect)->Release();
  }
  m3DView.RemoveAllModels();
  mCreatedCreature = false;
}

// @ 0x005F5080
void FUN_005f5080() { /* partial: 1375-byte update routine not reconstructed */ }

// @ 0x005F55E0
void cSPSwatch::RotateModel(uint32_t flags) { (void)flags; }

// @ 0x005F5930
void ShrinkTransformVector() { /* partial */ }

// @ 0x005F5B40
void cSPSwatch::LoadModel() { /* partial: 687-byte model load not reconstructed */ }

}  // namespace SP
