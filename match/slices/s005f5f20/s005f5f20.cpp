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
  void DoDestroyValues(T* first, T* last);
  ~vector() {
    DoDestroyValues(mpBegin, mpEnd);
    if (mpBegin && ((int*)mpBegin)[-1] != 0)
      do_deallocate(mpBegin);
  }
  void do_deallocate(T* p);
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
  void* mCamera;                                            // +0x28
  cSwatchTexture* mTexture;                                 // +0x2c
  void RemoveModel(cMWModel* model);                        // 0x005f4eb0
  cMWModel* AddModel(uint32_t imageID, int flags);          // 0x005f59b0
  void RemoveAllModels();                                   // 0x005f5aa0
  void Shutdown();                                          // 0x005f67d0
  ~cSwatch3DView();                                         // 0x005f6b40
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
  cSPSwatch();                            // 0x005f6bd0
  void InitInternal(IWindow* base, IWindow* modelWindow, uint32_t a3, uint32_t a4,
                    uint32_t b5, uint32_t b6, uint32_t a7, uint32_t a8);  // 0x005f3b20
  void InitAdditionalModels();            // 0x005f6090
  void SetEditorCameraController(bool enable);  // 0x005f6500
  void SetModel(Key* key);                // 0x005f5f20
  void LoadModel(Key& key);               // 0x005f5b40
  void InitStaticEffects();               // 0x005f6260
  void OnModelLoad();                     // 0x005f69a0
  void ShutDownModel();                   // 0x005f5df0
  void Shutdown();                        // 0x005f68a0

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
  void OnRolloverEnd2();            // 0x005f6ae0
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


// ==================== slice s005f5f20 ====================
void FUN_0080dda0(void* a, int b);   // 0x0080dda0
void FUN_0080f7c0(void* a);          // 0x0080f7c0
void FUN_0080dfc0(void* a);          // 0x0080dfc0
void FUN_0080df80(void* a);          // 0x0080df80
void FUN_005f0320();                 // 0x005f0320
void FUN_005ed6c0(void* a);          // 0x005ed6c0
void* FUN_00804500();                // 0x00804500
int  FUN_006c1100();                 // 0x006c1100
void* FUN_006c10e0();                // 0x006c10e0
void FUN_00803bd0(void* a);          // 0x00803bd0
void* FUN_0113ae10();                // 0x0113ae10
void* cSPBoundingBox_AddBoundingBox2(int, int, int);  // 0x0067cad0

// ---- extra externs used by the s005f5f20 targets ----
bool  FUN_00401d90(const void* a);                          // 0x00401d90
void* FUN_00401010();                                       // 0x00401010
void* ResourceManGetManager();                              // 0x0067dcd0
void  SetWindowAlpha(IWindow* w, float a);                  // 0x00804fc0
uint32_t GetThumbnailCameraID(uint32_t a, uint32_t b);      // 0x005f36d0
void* PropertyManager();                                    // 0x0067de30
bool  GetPropertyAsVector3(void* list, uint32_t id, void* out);   // 0x006a1110
void* Matrix33FromEulerXYZ(void* out, const void* euler);   // 0x00453920
void  GetPropertyAsTransformArray(void* list, uint32_t id, void* a, void* b);  // 0x006a0c30
void  FUN_006a0ae0(void* a, uint32_t b, void* c, void* d);  // 0x006a0ae0
void  GetPropertyAsKeyInstance(void* list, uint32_t id, void* out);  // 0x006a12a0
bool  GetPropertyAsKey(void* list, uint32_t id, void* out); // 0x006a1250
void* GetPropertyT_int(void* list, uint32_t id, void* out); // 0x0040cf10
bool  GetBoolProperty(void* list, uint32_t id, void* out);  // 0x00407190
void* FUN_0093b6c0(void* a);                                // 0x0093b6c0
void* FUN_0080d5f0(void* a);                                // 0x0080d5f0
void* FUN_0080db90(void* a);                                // 0x0080db90
void* FUN_0080dc50(void* a);                                // 0x0080dc50
void* FUN_01137690(void* mgr);                              // 0x01137690
void  FUN_010171e0(void* a, float f);                       // 0x010171e0
void  FUN_005a2370(void* a);                                // 0x005a2370
void* FUN_005a2000(void* a, bool b);                        // 0x005a2000
void  FUN_0040ce80(void* dst, const void* src);             // 0x0040ce80
void* FUN_005f4e10(void* a, void* b, void* c);              // 0x005f4e10
void* FUN_00572790(void* a);                                // 0x00572790
void* FUN_0067cad0_box(void* box);                          // 0x0067cad0
void* FUN_00a16f40(void* self);                             // 0x00a16f40
void  MatrixFromQuaternion(void* out, const void* quat);    // 0x00698650
void  FUN_00537dc0(void* a, const void* b);                 // 0x00537dc0
void  ComposeTransforms(void* a, const void* b);            // 0x0040ccb0

struct SwatchMatrix3 { float m[9]; void Assign(const void* src); };  // 0x0041cb40

// thiscall helpers reached through an explicit ecx (member-style call).
struct ThisCallExterns {
  void FUN_005f5080();                       // 0x005f5080
  void FUN_005f40b0();                       // 0x005f40b0
  void FUN_005f2ee0();                       // 0x005f2ee0
  void FUN_005f3cf0();                       // 0x005f3cf0
  void FUN_005f5970();                       // 0x005f5970
  void FUN_005f5930();                       // 0x005f5930
  int  FUN_005f2740();                       // 0x005f2740
  void FUN_005f58f0(const void* key);        // 0x005f58f0
  void FUN_005f4eb0(void* model);            // 0x005f4eb0
  void FUN_005f3680(void* a, void* b);       // 0x005f3680
  void FUN_00423c40(void* pos, void* value); // 0x00423c40
  void FUN_00423960(void* a, void* b);       // 0x00423960
};

// eastl::vector<AutoRefCount<cMWModel> > and eastl::vector<Key> (3-pointer form).
struct ModelPtrVec {
  cMWModel** mpBegin;
  cMWModel** mpEnd;
  cMWModel** mpCapacity;
};
struct KeyVec {
  Key* mpBegin;
  Key* mpEnd;
  Key* mpCapacity;
};

class cRefVt {
 public:
  PV(0)
  virtual void Vt4();   // +0x04
  virtual void Vt8();   // +0x08
  PV(3) PV(4) PV(5) PV(6) PV(7)
  virtual void Vt20();  // +0x20
  PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16)
  virtual void Vt44();  // +0x44
  PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
  PV(31) PV(32) PV(33)
  virtual void Vt88();  // +0x88
};
class cAnimWorld { public: void Release(); };

// @ 0x005F67D0
void cSwatch3DView::Shutdown() {
  if (mCamera) {
    ((cRefVt*)mCamera)->Vt44();
    if (mCamera) {
      mCamera = 0;
      ((cRefVt*)mCamera)->Vt4();
    }
  }
  RemoveAllModels();
  if (mLayeredObject) {
    FUN_0080dda0(0, 0);
    if (cSPBoundingBox_AddBoundingBox2(0, 0, 0)) {
      FUN_0080f7c0(mLayeredObject);
    }
    if (mLayeredObject) {
      mLayeredObject = 0;
      ((cRefVt*)mLayeredObject)->Vt8();
    }
  }
  if (mWindow) {
    ((cRefVt*)mWindow)->Vt20();
    if (mWindow) {
      mWindow = 0;
      ((cRefVt*)mWindow)->Vt4();
    }
  }
  if (mTexture) {
    ((cRefVt*)mRenderer)->Vt88();
    FUN_0080dfc0(mTexture);
    if (mTexture) {
      mTexture = 0;
      FUN_0080df80(mTexture);
    }
  }
  if (mRenderer) {
    mRenderer = 0;
    ((cRefVt*)mRenderer)->Vt4();
  }
  mVisible = false;
}

// @ 0x005F6B40
cSwatch3DView::~cSwatch3DView() {
  if (mRenderer)
    Shutdown();
  if (mTexture)
    FUN_0080df80(mTexture);
  if (mCamera)
    ((cRefVt*)mCamera)->Vt4();
  if (mRenderer)
    ((cRefVt*)mRenderer)->Vt4();
  if (mWindow)
    ((cRefVt*)mWindow)->Vt4();
  if (mAnimWorld)
    ((cAnimWorld*)mAnimWorld)->Release();
  mModels.~vector();
  if (mLayeredObject)
    ((cRefVt*)mLayeredObject)->Vt8();
}

// @ 0x005F68A0
void cSPSwatch::Shutdown() {
  void* input = FUN_00804500();
  if (FUN_006c1100()) {
    void* self = this ? CastInterface(0xee3f516e) : 0;
    if (self == FUN_006c10e0()) {
      FUN_00804500();
      FUN_00803bd0(0);
    }
  }
  if (*(int**)((char*)this + 0x144)) {
    ((cRefVt*)*(int**)((char*)this + 0x144))->Vt4();
    if (*(int**)((char*)this + 0x144)) {
      *(int**)((char*)this + 0x144) = 0;
    }
  }
  ShutDownModel();
  m3DView.Shutdown();
  if (mUseEditorCameraController) {
    mUseEditorCameraController = false;
    SwatchManager();
    FUN_005f0320();
  }
  if (mBaseWindow) {
    mBaseWindow->RemoveWinProc((IWinProc*)this);
    mBaseWindow = 0;
  }
  if (mModelWindow) {
    mModelWindow = 0;
  }
  EA::Messaging::Server* server = MessageServer();
  if (server)
    server->RemoveHandler((EA::Messaging::IHandler*)((char*)this + 0xc), 0x695e243, 0xffffd8f1);
}

// @ 0x005F6AE0
void cSPPaletteSwatch::OnRolloverEnd2() {
  EA::Messaging::Server* server = MessageServer();
  if (server)
    server->RemoveHandler((EA::Messaging::IHandler*)((char*)this + 0xc), 0x3150c27, 0xffffd8f1);
  cSPPaletteItemRollover* rollover = (cSPPaletteItemRollover*)FUN_0113ae10();
  if (rollover) {
    cSPPaletteInfo* info = mInfo;
    cSPPaletteItemRollover* r = (info && info->mRollover) ? info->mRollover : rollover;
    FUN_005ed6c0(r);
  }
  ((cSPSwatch*)this)->Shutdown();
}

// @ 0x005F5F20
void cSPSwatch::SetModel(Key* key) {
  char* const s = (char*)this;
  if (mModelKey == *key)
    return;

  ShutDownModel();
  ((void(__thiscall*)(void*, void*))((*(void***)s)[0x28 / 4]))(s, key);
  *(uint8_t*)(s + 0x163) = 0;
  *(uint8_t*)(s + 0x161) = 0;
  *(uint8_t*)(s + 0x162) = 0;
  if (*(uint32_t*)(s + 0x60) != 0) {
    bool baked;
    if (!FUN_00401d90(key)) {
      void* mgr = FUN_00401010();
      if (((bool(__thiscall*)(void*, void*, int))((*(void***)mgr)[0x1c / 4]))(mgr, key, 1))
        baked = true;
      else
        baked = false;
    } else {
      baked = false;
    }
    Key res = *key;
    res.mType = 0x2f7d0004;
    void* rm = ResourceManGetManager();
    bool ok = ((bool(__thiscall*)(void*, Key*, int, int, int, int, int))
                   ((*(void***)rm)[0xc / 4]))(rm, &res, 0, 0, 0, 0, 0);
    if (ok && *(uint8_t*)(s + 0x16c) == 0)
      SPUIHelpers::SetWindowImage(*(IWindow**)(s + 0x60), &res, -1);
    bool noCam = (*(uint8_t*)(s + 0x16c) != 0);
    *(float*)(s + 0xc4) = 0.0f;
    *(float*)(s + 0xc0) = 1.0f;
    if (!noCam)
      SetWindowAlpha(*(IWindow**)(s + 0x60), 0.0f);
    if (baked)
      *(uint8_t*)(s + 0x163) = 1;
  }
  if (*(uint8_t*)(s + 0xe8) == 0 && *(uint8_t*)(s + 0xe9) == 0)
    LoadModel(mModelKey);
  uint32_t cam = GetThumbnailCameraID(*(uint32_t*)(s + 0x50), 0);
  *(uint8_t*)(s + 0x169) = 0;
  *(uint32_t*)(s + 0x174) = cam;
  *(uint8_t*)(s + 0x160) = 0;
}

// @ 0x005F6090
void cSPSwatch::InitAdditionalModels() {
  char* const s = (char*)this;
  ModelPtrVec* models = (ModelPtrVec*)(s + 0x104);
  uint32_t count = (uint32_t)(models->mpEnd - models->mpBegin);
  for (uint32_t i = 0; i < count; i++)
    m3DView.RemoveModel(models->mpBegin[i]);

  cMWModel** first = models->mpBegin;
  cMWModel** last = models->mpEnd;
  cMWModel** res = (cMWModel**)FUN_005f4e10(last, last, first);
  ((ThisCallExterns*)models)->FUN_005f3680(res, models->mpEnd);
  models->mpEnd -= (uint32_t)(last - first);

  KeyVec* keys = (KeyVec*)(s + 0x148);
  uint32_t n = (uint32_t)(keys->mpEnd - keys->mpBegin);
  if (n != 0) {
    for (uint32_t i = 0; i < (uint32_t)(keys->mpEnd - keys->mpBegin); i++) {
      Key* e = keys->mpBegin + i;
      if (e->mInstance == 0)
        continue;
      cMWModel* m = m3DView.AddModel(e->mInstance, e->mGroup);
      if (m == 0)
        continue;
      ++*(int*)((char*)m + 0x40);
      if (models->mpEnd < models->mpCapacity) {
        cMWModel** slot = models->mpEnd;
        models->mpEnd = models->mpEnd + 1;
        if (slot) {
          *slot = m;
          ++*(int*)((char*)m + 0x40);
        }
      } else {
        ((ThisCallExterns*)models)->FUN_00423c40(models->mpEnd, &m);
      }
      if (m) {
        if (*(int*)((char*)m + 0x40) > 1)
          --*(int*)((char*)m + 0x40);
        else
          ((void(__thiscall*)(void*, int))((*(void***)m)[0x170 / 4]))(
              m, (*(uint32_t*)((char*)m + 4) >> 31) & 1);
      }
    }
  }

  // keys.clear() : eastl::vector::erase(begin(), end())
  {
    Key* kfirst = keys->mpBegin;
    Key* klast = keys->mpEnd;
    Key* d = kfirst;
    for (Key* p = klast; p != klast; ++p, ++d)
      *d = *p;
    keys->mpEnd -= (uint32_t)(klast - kfirst);
  }
}

// @ 0x005F6260
void cSPSwatch::InitStaticEffects() {
  char* const s = (char*)this;
  if (*(uint8_t*)(s + 0x165) == 0)
    return;
  void* model = *(void**)(s + 0x118);
  if (model == 0)
    return;
  void* list = *(void**)((char*)model + 0x90);
  if (list == 0)
    return;
  void** vt = *(void***)list;
  if (!((bool(__thiscall*)(void*, uint32_t))vt[0x1c / 4])(list, 0x2a907b6))
    return;
  model = *(void**)(s + 0x118);
  vt = *(void***)(*(void**)((char*)model + 0x90));
  if (!((bool(__thiscall*)(void*, uint32_t))vt[0x1c / 4])(
          *(void**)((char*)model + 0x90), 0x4ff954a))
    return;

  void* list2 = *(void**)((char*)(*(void**)(s + 0x118)) + 0x90);
  uint32_t cnt = 0;
  void* tr;
  GetPropertyAsTransformArray(list2, 0x2a907b6, &cnt, &tr);
  uint32_t cnt2 = 0;
  void* tr2;
  FUN_006a0ae0(list2, 0x4ff954a, &cnt2, &tr2);

  int n = (*(int*)(s + 0x120) - *(int*)(s + 0x11c)) >> 2;
  for (int i = 0; i < n; i++)
    m3DView.RemoveModel((cMWModel*)*(void**)(*(int*)(s + 0x11c) + i * 4));

  ((ThisCallExterns*)(s + 0x11c))->FUN_005f5970();
  ((ThisCallExterns*)(s + 0x130))->FUN_005f5930();

  uint32_t total = *(uint32_t*)&tr;
  for (uint32_t i = 0; i < total; i++) {
    char* e = (char*)tr + i * 0xc;
    if (*(void**)e == 0)
      continue;
    SwatchMatrix3 basis;
    basis.Assign((const void*)0x15f1e14);
    cMWModel* m = m3DView.AddModel(*(uint32_t*)e, *(int*)(e + 8));
    if (m)
      ++*(int*)((char*)m + 0x40);
    char* trs = (char*)tr2 + i * 0x38;
    SwatchMatrix3 rot;
    rot.Assign(trs + 0x14);
    SwatchMatrix3 local;
    local = rot;
    MatrixFromQuaternion(&local, (void*)(s + 0x30));
    float w = *(float*)(e + 0x10);
    for (int k = 0; k < 9; k++)
      basis.m[k] = local.m[k];
    basis.m[0] = w;
    basis.m[5] = 6;
    basis.m[6] = 3;
    FUN_00537dc0((char*)s + 0x24, (const void*)&basis);
    ComposeTransforms((char*)s + 0x24, (const void*)&local);
    ModelPtrVec* vec = (ModelPtrVec*)(s + 0x11c);
    if (vec->mpEnd < vec->mpCapacity) {
      cMWModel** slot = vec->mpEnd;
      vec->mpEnd = vec->mpEnd + 1;
      if (slot) {
        *slot = m;
        if (m)
          ++*(int*)((char*)m + 0x40);
      }
    } else {
      ((ThisCallExterns*)vec)->FUN_00423c40(vec->mpEnd, &m);
    }
    ModelPtrVec* tvec = (ModelPtrVec*)(s + 0x130);
    if (tvec->mpEnd < tvec->mpCapacity) {
      char* slot = (char*)tvec->mpEnd;
      tvec->mpEnd = tvec->mpEnd + 1;
      if (slot)
        FUN_0040ce80(slot, &local);
    } else {
      ((ThisCallExterns*)tvec)->FUN_00423960(tvec->mpEnd, &local);
    }
    if (m) {
      if (*(int*)((char*)m + 0x40) > 1)
        --*(int*)((char*)m + 0x40);
      else
        ((void(__thiscall*)(void*, int))((*(void***)m)[0x170 / 4]))(
            m, (*(uint32_t*)((char*)m + 4) >> 31) & 1);
    }
  }
}

// @ 0x005F6500
void cSPSwatch::SetEditorCameraController(bool enable) {
  char* const s = (char*)this;
  void* propList = 0;
  if (!((bool(__thiscall*)(void*, void**))((*(void***)s)[0x78 / 4]))(s, &propList))
    goto release;

  {
    uint32_t* cam = (uint32_t*)(s + 0x174);
    *cam = 0;
    GetPropertyAsKeyInstance(propList, 0xb4a08d14, cam);

    void* ctrl;
    if (*(void**)(s + 0x14) != 0)
      ctrl = ((void*(__thiscall*)(void*))FUN_0093b6c0)(*(void**)(s + 0x14));
    else {
      void* tex = *(void**)(s + 0x3c);
      if (tex == 0)
        goto release;
      ctrl = ((void*(__thiscall*)(void*))FUN_0080d5f0)(tex);
    }
    if (ctrl == 0)
      goto release;
    if (*cam == 0)
      goto release;
    if (SwatchManager() == 0)
      goto release;

    {
      void* camMgr = SwatchManager()->GetCameraManager();
      if (camMgr == 0)
        goto release;

      int buf = ((ThisCallExterns*)(s + 0x10))->FUN_005f2740();
      void* sm = SwatchManager();
      ((void(__thiscall*)(void*, int))FUN_005f0320)(sm, buf);
      sm = SwatchManager();
      void* cmgr = FUN_01137690(sm);
      ((void(__thiscall*)(void*, uint32_t))((*(void***)cmgr)[0x34 / 4]))(cmgr, *cam);
      sm = SwatchManager();
      cmgr = FUN_01137690(sm);
      void* camera = ((void*(__thiscall*)(void*))((*(void***)cmgr)[0x38 / 4]))(cmgr);
      if (camera == 0)
        goto success;

      {
        float f = *(float*)0x13f9dd4;
        GetPropertyT_int(propList, 0x700db77d, &f);
        void* sm2 = SwatchManager();
        void* cm2 = FUN_01137690(sm2);
        void* cam2 = ((void*(__thiscall*)(void*))((*(void***)cm2)[0x38 / 4]))(cm2);
        void* c = FUN_00572790(cam2);
        FUN_010171e0(c, f);
        if (c)
          ((void(__thiscall*)(void*))((*(void***)c)[0x50 / 4]))(c);
        ((void(__thiscall*)(void*))FUN_005a2370)(c);
        bool b = false;
        GetBoolProperty(propList, 0x937e6619, &b);
        ((void(__thiscall*)(void*, bool))FUN_005a2000)(c, b);

        uint32_t box = 0;
        GetPropertyAsKeyInstance(propList, 0xb00db8c8, &box);
        if (box != 0) {
          void* r = FUN_0067cad0_box((void*)box);
          ((void(__thiscall*)(void*))FUN_0080dc50)(r);
        }

        Key km1;
        Key km2;
        if (GetPropertyAsKey(propList, 0x149c4d75, &km1)) {
          km1.mGroup = *(uint32_t*)0x151c630;
          ((ThisCallExterns*)s)->FUN_005f58f0(&km1);
        }
        if (GetPropertyAsKey(propList, 0x149c4d69, &km2)) {
          km2.mGroup = *(uint32_t*)0x151c630;
          ((ThisCallExterns*)s)->FUN_005f58f0(&km2);
        }
        ((void(__thiscall*)(void*))((*(void***)s)[0x7c / 4]))(s);
        InitAdditionalModels();

        uint32_t effect = 0;
        GetPropertyAsKeyInstance(propList, 0x35383c76, &effect);
        if (effect != 0) {
          void** slot = (void**)(s + 0x144);
          void* old = *slot;
          if (old != 0) {
            *slot = 0;
            ((void(__thiscall*)(void*))((*(void***)old)[4 / 4]))(old);
          }
          void* tex = *(void**)(s + 0x3c);
          void* texObj = (tex != 0) ? ((void*(__thiscall*)(void*))FUN_0080db90)(tex) : 0;
          void* pp = ((void*(__thiscall*)(void*))FUN_00a16f40)(s + 0x144);
          if (texObj)
            ((void(__thiscall*)(void*, uint32_t, int, void*))(
                ((void**)(*(void***)texObj))[2]))(texObj, effect, 0, pp);
          void* nv = *slot;
          if (nv != 0)
            ((void(__thiscall*)(void*, int))((*(void***)nv)[2]))(nv, 0);
        }
      }
    }
  }
success:
  *(uint32_t*)(s + 0x16d) = 0;
  *(uint8_t*)(s + 0x171) = 0;
  *(uint8_t*)(s + 0x16c) = enable ? 1 : 0;

release:
  if (propList)
    ((void(__thiscall*)(void*))((*(void***)propList)[4 / 4]))(propList);
}

// @ 0x005F69A0
void cSPSwatch::OnModelLoad() {
  char* const s = (char*)this;
  *(uint8_t*)(s + 0x161) = 1;
  *(uint8_t*)(s + 0x162) = 0;
  *(float*)(s + 0xdc) = 0.0f;
  ((ThisCallExterns*)s)->FUN_005f5080();

  void* list = 0;
  void* pm = PropertyManager();
  if (list) {
    list = 0;
    ((void(__thiscall*)(void*))((*(void***)list)[4 / 4]))(list);
  }
  bool ok = ((bool(__thiscall*)(void*, uint32_t, uint32_t, void**))
                 ((*(void***)pm)[0x2c / 4]))(pm, *(uint32_t*)(s + 0x4c),
                                             *(uint32_t*)(s + 0x54), &list);
  if (!ok)
    goto release;

  {
    float vec[3];
    if (GetPropertyAsVector3(list, 0x72a87cc2, vec)) {
      SwatchMatrix3 tmp;
      float mat[9];
      const float d2r = *(float*)0x13f9d60;
      vec[0] *= d2r;
      vec[1] *= d2r;
      vec[2] *= d2r;
      Matrix33FromEulerXYZ(mat, vec);
      tmp.Assign(mat);
      for (int i = 0; i < 9; i++)
        ((float*)(s + 0x98))[i] = tmp.m[i];
    }
  }
  if (*(uint8_t*)(s + 0x163)) {
    if (*(uint8_t*)(s + 0x16c))
      ((ThisCallExterns*)s)->FUN_005f40b0();
    InitStaticEffects();
    ((ThisCallExterns*)s)->FUN_005f2ee0();
  }
  if (*(uint8_t*)(s + 0x160) == 0)
    ((ThisCallExterns*)s)->FUN_005f3cf0();

release:
  if (list)
    ((void(__thiscall*)(void*))((*(void***)list)[4 / 4]))(list);
}

// @ 0x005F6BD0
cSPSwatch::cSPSwatch() {
  char* const s = (char*)this;
  *(uint8_t*)(s + 0x10) = 0;
  *(uint32_t*)(s + 0x14) = 0;
  *(uint32_t*)(s + 0x18) = 0;
  *(uint32_t*)(s + 0x1c) = 0;
  *(uint32_t*)(s + 0x20) = 0;
  *(uint32_t*)(s + 0x2c) = 0;
  *(uint32_t*)(s + 0x30) = 0;
  *(uint32_t*)(s + 0x34) = 0;
  *(uint32_t*)(s + 0x38) = 0;
  *(uint32_t*)(s + 0x3c) = 0;
  *(uint32_t*)(s + 0x40) = 0;
  *(uint32_t*)(s + 0x44) = 0;
  *(uint32_t*)(s + 0x48) = 0;
  *(uint32_t*)(s + 0x4c) = 0;
  *(uint32_t*)(s + 0x50) = 0;
  *(uint32_t*)(s + 0x54) = 0;
  ((SwatchMatrix3*)(s + 0x98))->Assign((const void*)0x15f1e14);
  *(float*)(s + 0x64) = 1.0f;
  *(float*)(s + 0x68) = 0.0f;
  *(float*)(s + 0x6c) = 0.0f;
  *(float*)(s + 0x70) = 1.0f;
  *(float*)(s + 0x94) = 1.0f;
  const uint32_t def = *(const uint32_t*)0x151c424;
  *(uint32_t*)(s + 0xd0) = def;
  *(uint32_t*)(s + 0xd4) = def;
  *(uint32_t*)(s + 0xe4) = def;
  *(float*)(s + 0xc0) = 1.0f;
  *(float*)(s + 0xc4) = 1.0f;
  *(uint8_t*)(s + 0xbc) = 0;
  *(float*)(s + 0xd8) = 0.0f;
  *(float*)(s + 0xdc) = 0.0f;
  *(uint8_t*)(s + 0xe9) = 0;
  *(uint8_t*)(s + 0xeb) = 0;
  *(uint8_t*)(s + 0xec) = 0;
  *(uint32_t*)(s + 0xc8) = 0xffffffff;
  *(uint32_t*)(s + 0xcc) = 0xffffffff;
  *(uint32_t*)(s + 0xe0) = 0xffffffff;
  *(uint8_t*)(s + 0xe8) = 1;
  *(uint8_t*)(s + 0xea) = 1;
  *(uint32_t*)(s + 0xf0) = 0;
  *(uint32_t*)(s + 0xf4) = 2;
  *(uint32_t*)(s + 0xf8) = 0;
  *(uint8_t*)(s + 0xfc) = 1;
  *(uint8_t*)(s + 0xfd) = 0;
  *(uint32_t*)(s + 0x100) = 0x71fa7d3f;
  *(uint32_t*)(s + 0x104) = 0;
  *(uint32_t*)(s + 0x108) = 0;
  *(uint32_t*)(s + 0x10c) = 0;
  *(uint32_t*)(s + 0x118) = 0;
  *(uint32_t*)(s + 0x11c) = 0;
  *(uint32_t*)(s + 0x120) = 0;
  *(uint32_t*)(s + 0x124) = 0;
  *(uint32_t*)(s + 0x130) = 0;
  *(uint32_t*)(s + 0x134) = 0;
  *(uint32_t*)(s + 0x138) = 0;
  *(uint32_t*)(s + 0x144) = 0;
  *(uint32_t*)(s + 0x148) = 0;
  *(uint32_t*)(s + 0x14c) = 0;
  *(uint32_t*)(s + 0x150) = 0;
  *(float*)(s + 0x15c) = 0.0f;
  *(uint8_t*)(s + 0x160) = 0;
  *(uint8_t*)(s + 0x165) = 1;
  *(uint8_t*)(s + 0x166) = 1;
  *(uint8_t*)(s + 0x16a) = 1;
  *(uint8_t*)(s + 0x16b) = 1;
  *(uint8_t*)(s + 0x161) = 0;
  *(uint8_t*)(s + 0x162) = 0;
  *(uint8_t*)(s + 0x163) = 0;
  *(uint8_t*)(s + 0x164) = 0;
  *(uint8_t*)(s + 0x167) = 0;
  *(uint8_t*)(s + 0x169) = 0;
  *(uint8_t*)(s + 0x16c) = 0;
  *(uint32_t*)(s + 0x174) = 0;
  *(uint32_t*)(s + 0x178) = 0;
}

}  // namespace SP
