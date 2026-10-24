// slice s005f2780 -- SP::cSPSwatch (the 3D model swatch window proc: HandleMessage, DoMessage,
// viewport/rotation updates, image layers, show/hide, capture helpers) and a palette-swatch
// subclass (cost display, cursor, rollover), plus eastl::vector<AutoRefCount<cMWModel>>::DoDestroyValues.
// Retail cSPSwatch is 0x17c bytes (mID at +0x178); fields after it belong to the subclass.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include <math.h>
#include <new>
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
class Key { public:
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

class RectT { public:
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
  PV(11) PV(12)
  virtual const RectT& GetWindowArea();             // +0x34
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
  virtual void AddChild(IWindow* child);            // +0xec
  PV(60) PV(61) PV(62) PV(63) PV(64)
  virtual void AddWinProc(IWinProc* proc);     // +0x104
  virtual void RemoveWinProc(IWinProc* proc);  // +0x108
};

class Message { public:
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

class AutoHandler { public:
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
void SetWindowAlpha(IWindow* window, float alpha);                // 0x00804fc0
}  // namespace SPUIHelpers


using EA::Point2D;
using EA::RectT;

namespace SW {
class cUIViewport;
void SizeViewportToWindowAndRemainOnScreen(cUIViewport* viewport, IWindow* window, float scale,
                                           float x, float y);  // 0x005f2390
}  // namespace SW
namespace UTFWinControls { class IWinText; }
namespace SP { class cRenderManager; }
class cCollectableItems;
IWindow* FUN_00807880(float* key, float x, float y, void* parent);  // 0x00807880
SP::cRenderManager* AddBoundingBox(IWindow* window, int a, int b);  // 0x0067cad0

// A ref-counted interface subobject living inside cSPPaletteItem at +0x8.
class cSPPaletteItemRef {
 public:
  virtual int AddRef();   // +0x0
  virtual int Release();  // +0x4
};

class cSPPaletteItem {
 public:
  virtual int AddRef();                        // vtable pointer at +0x0
  virtual int Release();
  uint32_t pad4;                               // +0x4
  cSPPaletteItemRef mRef;                      // +0x8
  Key mKey;                                    // +0xc
  bool IsNew(cCollectableItems* items) const;  // 0x005c6670
};

namespace EA {
class Stopwatch {
 public:
  void SetUnits(int units);  // 0x0093a1a0
  uint32_t pad[6];
};
}  // namespace EA

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
  virtual bool FUN_v5(const Key* key);                                    // +0x14
};

class cSPPaletteItemRollover;
struct cSPPaletteInfo : public EA::RefCountTemplate<int> {
  cSPEditorEconomy* mEconomy;               // +0x8
  void* mTheme;                             // +0xc
  void* mCollectableItems;                  // +0x10
  cSPPaletteItemRollover* mRollover;        // +0x14
  uint32_t mUnk18;                          // +0x18
  uint32_t mUnk1c;                          // +0x1c
  uint32_t mUnk20;                          // +0x20
  uint32_t mUnk24;                          // +0x24
  uint32_t mUnk28;                          // +0x28
  uint32_t mUnk2c;                          // +0x2c
  bool mUseModelKey;                        // +0x30 (padding byte)
  bool mUseModelKeyForCost;                 // +0x31
};

class cSPPaletteItemRollover { public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual void Update(void* layout, const Key* key, void* info);  // +0x28
  void Hide();                     // 0x005ed6c0
  void FUN_005ed320(int a);        // 0x005ed320
  void FUN_005ee480(void* layout, void* info, void* obj, int a);  // 0x005ee480
  void FUN_008283a0(float x, float y, float ox, float oy);        // 0x008283a0
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
  virtual void GetMousePosition(Point2D* out);         // +0x3c
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
  void Dispose(bool force);                          // 0x00803bd0
};
cInputManager* InputManager();  // 0x00804500

class cRenderManager {
 public:
  void FUN_0080d710();  // 0x0080d710
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
  virtual int GetEffectCount(struct cMWModel* model);  // +0x64
  PV(26) PV(27)
  virtual void StartEffect(cMWModel* model, uint32_t effectID, int a, float b, int index);  // +0x70
  PV(29) PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42)
  PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56)
  PV(57) PV(58) PV(59) PV(60) PV(61) PV(62) PV(63) PV(64) PV(65) PV(66) PV(67) PV(68) PV(69) PV(70)
  PV(71) PV(72) PV(73) PV(74) PV(75) PV(76) PV(77) PV(78) PV(79) PV(80) PV(81) PV(82) PV(83) PV(84)
  PV(85) PV(86) PV(87) PV(88) PV(89) PV(90) PV(91)
  virtual void DestroyModel(struct cMWModel* model, bool immediate);  // +0x170
};
struct cMWModel { private:
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
  SW::cUIViewport* FUN_0093b6c0(); // 0x0093b6c0
};
class cSwatchTexture {
 public:
  void* GetTexture();                                            // 0x0080d610
  SW::cUIViewport* FUN_0080d5f0();                               // 0x0080d5f0
};

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

class cSwatch3DView { public:
  bool mVisible;                                            // +0x00
  cUILayeredObject* mLayeredObject;                         // +0x04
  eastl::vector<AutoRefCount<cMWModel> > mModels;           // +0x08
  uint32_t pad14;                                           // +0x14
  uint32_t pad18[3];
  cSwatchRenderer* mRenderer;                               // +0x24
  uint32_t pad28;
  cSwatchTexture* mTexture;                                 // +0x2c
  void RemoveModel(cMWModel* model);                        // 0x005f4eb0
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
  uint32_t mInterfaceID;                  // +0x100
  uint32_t pad104[5];
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

  AutoRefCount<cSPPaletteInfo> mInfo;      // +0x17c
  AutoRefCount<cSPPaletteItem> mPaletteItem;  // +0x180
  bool mIsLocked;                          // +0x184
  float mBaseScale;                        // +0x188
  AutoRefCount<IWindow> mDragWindow;       // +0x18c
  uint32_t mUnk190;                        // +0x190
  AutoRefCount<IWindow> mCostWindow;       // +0x194
  bool mShowCost;                         // +0x198
  bool mDraggable;                        // +0x199
};

// ==================== slice s005f4310 ====================
struct Matrix33 { float m[9]; };
struct M3A { void Assign(const Matrix33* src); };                 // 0x0041cb40 (Matrix3::Assign)
void* Matrix33FromEulerXYZ_fpu(Matrix33* out, const void* euler);  // 0x00453920

// @ 0x005F46C0
void cSPPaletteSwatch::EndDrag() {
  if (mBaseWindow)
    mBaseWindow->SetArea(mOriginalWindowArea);
  mWantToRenderModel = false;
  UpdateCursor();
}

// @ 0x005F49A0
void cSPPaletteSwatch::SetShowCost(bool show) {
  mShowCost = show;
  if (show) {
    mBaseWindow->SetCursorID(0x648fbf1);
    UpdateCostDisplay();
    UpdateCursor();
  } else {
    mBaseWindow->SetCursorID(0);
    UpdateCostDisplay();
    UpdateCursor();
  }
}

// @ 0x005F4E10
AutoRefCount<SP::cMWModel>* copy_refs(AutoRefCount<SP::cMWModel>* first,
                                      AutoRefCount<SP::cMWModel>* last,
                                      AutoRefCount<SP::cMWModel>* out) {
  for (; first != last; ++first, ++out)
    *out = *first;
  return out;
}

// @ 0x005F4E80
Matrix33* Matrix3FromEulerXYZ(Matrix33* out, const void* euler) {
  Matrix33 tmp;
  Matrix33* p = (Matrix33*)Matrix33FromEulerXYZ_fpu(&tmp, euler);
  ((M3A*)out)->Assign(p);
  return out;
}

// @ 0x005F4EB0
void cSwatch3DView::RemoveModel(cMWModel* model) {
  if (mLayeredObject)
    mLayeredObject->RemoveModel(model);
  int n = mModels.size();
  for (int i = 0; i < n; ++i) {
    if (mModels[i] == model) {
      mModels[i] = mModels.back();
      mModels.pop_back();
      return;
    }
  }
}

// @ 0x005F4F80
void cSPSwatch::Init(Key* key, uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t scale) {
  if (a != 0) {
    mScaleParam = scale;
    bool b8 = true;
    if (key->mType == 0x3d97a8e4)
      b8 = false;
    InitInternal((IWindow*)a, (IWindow*)a, 1, b, c, d, e, b8);
    mOriginalItemKey = *key;
    if (key->mInstance != 0)
      Vt24(key);
  }
}

// @ 0x005F5000
void cSPSwatch::Init(Key* key, void* a, void* b, uint32_t c, uint32_t d, uint32_t e, uint32_t f,
                     uint32_t scale) {
  if (a != 0 && b != 0) {
    mScaleParam = scale;
    bool b8 = true;
    if (key->mType == 0x3d97a8e4)
      b8 = false;
    InitInternal((IWindow*)a, (IWindow*)b, 1, c, d, e, f, b8);
    mOriginalItemKey = *key;
    if (key->mInstance != 0)
      Vt24(key);
  }
}

// ---------------------------------------------------------------------------
// cSPOLDPaletteItemUIDragAndBuy -- a palette-swatch subclass with drag/buy UI.
// ---------------------------------------------------------------------------
// Short-lived "vehicle abilities" drag object built by OnLeftMouseDown.
class cSPEditorVehicleAbilities {
 public:
  cSPEditorVehicleAbilities(const Key& key, uint32_t a, uint32_t b, uint32_t c, bool d);
  virtual void FUN_0059f060();  // +0x0
  virtual void FUN_0059f064();  // +0x4
  virtual void FUN_0059f068();  // +0x8
};

namespace Audio {
class ISystemAT {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
  virtual int FUN_00a206f0();  // +0x20
};
ISystemAT* GetSystemAT();  // 0x00a206f0
}  // namespace Audio

// Payload message built on the stack by OnMouseUp.
struct cSPPaletteDragMessage {
  uint32_t mUnk0;              // +0x00 (0x013f7e34)
  uint32_t mUnk4;              // +0x04 (0x013f7e30)
  uint32_t mUnk8;              // +0x08
  uint32_t mUnkC;              // +0x0c
  uint32_t mUnk10;             // +0x10
  Key mModelKey;               // +0x14
  cSPPaletteItemRef* mpRef;    // +0x20
  cSPPaletteItemRef* mpUnk24;  // +0x24
};

class cSPOLDPaletteItemUIDragAndBuy : public cSPPaletteSwatch {
 public:
  void Init(Key* key, void* a, void* b, uint32_t c, void* d, void* e, bool f);  // 005f4310
  void OnLeftMouseDown();   // 005f4750
  void OnMouseDown();       // 005f49f0
  void OnMouseUp();         // 005f4b80

  uint32_t pad19c;                  // +0x19c
  EA::Stopwatch mStopwatch;         // +0x1a0
  AutoRefCount<IWindow> mLeftText;  // +0x1b8
  AutoRefCount<IWindow> mRightText; // +0x1bc
  Point2D mOriginalMousePosition;   // +0x1c0
};

// The HandleMessage override's vtable slot lives on the IHandler subobject (+0xc).
class cHandlerView {
 public:
  bool HandleMessage(uint32_t id, void* msg);  // 0x005f46f0
};

// @ 0x005F4310
void cSPOLDPaletteItemUIDragAndBuy::Init(Key* key, void* a, void* b, uint32_t c, void* d, void* e,
                                         bool f) {
  InitInternal((IWindow*)a, (IWindow*)a, 0, 0, 0, 1, 0, 1);
  mOriginalItemKey = *key;
  if (key->mInstance != 0)
    Vt24(key);
  mDragWindow = (IWindow*)b;
  mUnk190 = c;
  mPaletteItem = (cSPPaletteItem*)d;
  mDraggable = f;
  mInfo = (cSPPaletteInfo*)e;

  SW::cUIViewport* viewport = 0;
  if (m3DView.mLayeredObject != 0)
    viewport = m3DView.mLayeredObject->FUN_0093b6c0();
  else if (m3DView.mTexture != 0)
    viewport = m3DView.mTexture->FUN_0080d5f0();
  if (viewport != 0)
    SW::SizeViewportToWindowAndRemainOnScreen(viewport, mModelWindow, mTargetViewportScale,
                                              mActualViewportCenter.x, mActualViewportCenter.y);

  if (mInfo != 0) {
    mDisplay3DModel = mInfo->mUseModelKey;
    if (mInfo->mUnk1c != 0) {
      mCamera = mInfo->mUnk1c;
      mHasBeenFramed = false;
    }

    bool isNew = false;
    if (mInfo->mCollectableItems != 0)
      isNew = ((cSPPaletteItem*)mPaletteItem)
                  ->IsNew((cCollectableItems*)mInfo->mCollectableItems);
    bool available = isNew;
    if (mInfo->mEconomy != 0 && !available)
      available = mInfo->mEconomy->FUN_v5(&((cSPPaletteItem*)mPaletteItem)->mKey);

    if (mPaletteItem != 0 && available && mBaseWindow != 0) {
      uint32_t leftKey[3];
      leftKey[0] = 0x1249ff0f;
      leftKey[1] = 0x2f7d0004;
      leftKey[2] = 0x100d976e;
      mLeftText = FUN_00807880((float*)leftKey, 0.0f, 0.0f, mBaseWindow->GetParent());
      if (mLeftText != 0) {
        uint32_t rightKey[3];
        rightKey[0] = 0x3cf13a01;
        rightKey[1] = 0x2f7d0004;
        rightKey[2] = 0x11c0bde;
        mRightText = FUN_00807880((float*)rightKey, 0.0f, 0.0f, mBaseWindow->GetParent());
        if (mRightText != 0) {
          IWindow* parent = mBaseWindow->GetParent();
          mLeftText->SetFlag(2, false);
          mLeftText->SetFlag(0x10, true);
          parent->AddChild(mLeftText);
          mRightText->SetFlag(2, false);
          mRightText->SetFlag(0x10, true);
          parent->AddChild(mRightText);
          RectT area = mBaseWindow->GetRealArea();
          mLeftText->SetArea(area);
          mRightText->SetArea(area);
          SPUIHelpers::SetWindowAlpha(mBaseWindow, 0.0f);
          SPUIHelpers::SetWindowAlpha(mLeftText, 0.0f);
          mStopwatch.SetUnits(4);
          mIsLocked = true;
        }
      }
    }
  }

  UpdateCostDisplay();
  UpdateCursor();
  EA::Messaging::Server* server = MessageServer();
  if (server != 0)
    server->AddHandler((EA::Messaging::IHandler*)((char*)this + 0xc), 0x3150c27);
}

// @ 0x005F46F0 (this is the IHandler subobject at +0xc)
bool cHandlerView::HandleMessage(uint32_t id, void* msg) {
  if (id == 0x3150c27) {
    cSPPaletteSwatch* self = (cSPPaletteSwatch*)((char*)this - 0xc);
    self->UpdateCostDisplay();
    self->UpdateCursor();
    return false;
  }
  if (id == 0x695e243) {
    cModelChangedMessage* m = (cModelChangedMessage*)msg;
    cSPPaletteSwatch* self = (cSPPaletteSwatch*)((char*)this - 0xc);
    if (m->mInstanceID == self->mModelKey.mInstance && m->mTypeID == self->mModelKey.mType &&
        m->mGroupID == self->mModelKey.mGroup)
      self->ReloadModel();
  }
  return false;
}

// @ 0x005F4750
void cSPOLDPaletteItemUIDragAndBuy::OnLeftMouseDown() {
  bool available;
  cSPPaletteInfo* info = mInfo;
  if (info != 0 && info->mEconomy != 0)
    available = info->mEconomy->IsItemAvailable(
        info->mUseModelKeyForCost ? &mModelKey : &mOriginalItemKey);
  else
    available = true;

  mAllowRotation = available && mShowCost && mInterfaceID == 0x71fa7d3f;
  mMaxViewportScaleFactor = mBaseScale * (available ? 1.0f : 0.75f);
  if (!mIsLocked && available)
    mWantToRenderModel = true;

  cSPPaletteItemRollover* rollover = SwatchManager()->GetSwatchRollover();
  if (rollover != 0 && mAllowTooltip) {
    cSPPaletteItemRollover* rollover2 = mInfo->mRollover;
    if (rollover2 != 0 && mInfo->mUseModelKeyForCost) {
      rollover2->Update(mPaletteItem, &mModelKey, mInfo);
      rollover = rollover2;
    } else {
      void* mem = operator new(0x64, "Editor", 0, 0, 0, 0);
      cSPEditorVehicleAbilities* obj = 0;
      if (mem != 0) {
        obj = new (mem) cSPEditorVehicleAbilities(mPaletteItem->mKey, mInfo->mUnk2c, 0x14880158,
                                                  0, true);
        if (obj != 0)
          obj->FUN_0059f064();
      }
      rollover->FUN_005ee480(mPaletteItem, mInfo, obj, 1);
      if (obj != 0)
        obj->FUN_0059f068();
    }
    rollover->FUN_005ed320(2);
    RectT area = WindowManager()->GetMainWindow()->GetWindowArea();
    rollover->FUN_008283a0(mActualViewportCenter.x, mActualViewportCenter.y,
                           (area.right - area.left) * 0.05f, (area.bottom - area.top) * 0.0f);
  }

  AddBoundingBox(GetWindow(), 1, 1)->FUN_0080d710();
  if (mCostWindow != 0)
    AddBoundingBox(mCostWindow, 1, 1)->FUN_0080d710();

  cSwatchMessage msg;
  msg.mpSwatch = this;
  msg.mID = 0x522f9cd;
  MessageServer()->MessageSend(0x522f9cd, &msg, 0);
}

// @ 0x005F49F0
void cSPOLDPaletteItemUIDragAndBuy::OnMouseDown() {
  if (mIsLocked)
    return;
  if (mModelKey.mInstance == 0 && mModel == 0)
    return;

  bool take = false;
  cSPPaletteInfo* info = mInfo;
  if (info != 0 && info->mEconomy != 0) {
    int status = info->mEconomy->GetItemStatus(
        info->mUseModelKeyForCost ? &mModelKey : &mOriginalItemKey, 0);
    if (status == 2) {
      if (!mShowCost)
        return;
      if (mIsLocked)
        return;
      PlayAudio(0x4fc39619, GetAudioSystem());
      return;
    }
    if (status == 3) {
      PlayAudio(0xdc91625a, GetAudioSystem());
      return;
    }
    if (status != 1)
      return;
    take = true;
  } else {
    take = true;
  }
  if (!take)
    return;

  TakeCapture();

  if (mShowCost && mInterfaceID == 0x71fa7d3f) {
    Audio::ISystemAT* audio = Audio::GetSystemAT();
    int sound = 0;
    if (audio != 0)
      sound = audio->FUN_00a206f0();
    PlayAudio(0xe5469985, sound);
    UpdateCursor();
    Point2D mousePos;
    WindowManager()->GetMousePosition(&mousePos);
    mOriginalMousePosition = mousePos;
    cSPPaletteItemRollover* rollover = SwatchManager()->GetSwatchRollover();
    if (rollover != 0) {
      cSPPaletteItemRollover* rollover2 = mInfo->mRollover;
      if (rollover2 != 0)
        rollover = rollover2;
      rollover->Hide();
    }
    AddBoundingBox(GetWindow(), 0, 1)->FUN_0080d710();
    if (mCostWindow != 0)
      AddBoundingBox(mCostWindow, 0, 1)->FUN_0080d710();
    return;
  }

  if (mInterfaceID == 0x5e71ab9b)
    pv24();
}

// @ 0x005F4B80
void cSPOLDPaletteItemUIDragAndBuy::OnMouseUp() {
  if (IsCapturedBySelf())
    InputManager()->Dispose(0);

  cSPPaletteDragMessage msg;
  msg.mUnk0 = 0x13f7e34;
  msg.mUnk4 = 0x13f7e30;
  msg.mUnk8 = 0;
  msg.mUnkC = mUnk190;
  msg.mUnk10 = 0;
  msg.mModelKey = mModelKey;
  msg.mpRef = 0;
  msg.mpUnk24 = 0;
  if (mPaletteItem != 0) {
    cSPPaletteItemRef* ref = &mPaletteItem->mRef;
    if (ref != 0) {
      ref->AddRef();
      msg.mpRef = ref;
    }
  }
  MessageServer()->MessageSend(mUnk190, &msg, 0);
  mWantToRenderModel = false;
  RectT area = mModelWindow->GetRealArea();
  Point2D center = mModelWindow->GlobalToLocal(
      Point2D((area.right - area.left) * 0.5f, (area.bottom - area.top) * 0.5f));
  mActualViewportCenter = center;
  mTargetViewportCenter = center;
  if (msg.mpUnk24 != 0)
    msg.mpUnk24->Release();
  if (msg.mpRef != 0)
    msg.mpRef->Release();
}

// The 0x38-byte record is a cSPTransform-shaped type; its memberwise copy assignment keeps
// MSVC from collapsing the loop into a block move.
struct Blob38 {
  unsigned short mFlags;             // +0x00
  unsigned short mModificationCount; // +0x02
  float mTranslation[3];             // +0x04
  float mScale;                      // +0x10
  float mRotation[9];                // +0x14
  Blob38& operator=(const Blob38& o);
};

inline Blob38& Blob38::operator=(const Blob38& o) {
  mFlags = o.mFlags;
  mModificationCount = o.mModificationCount;
  for (int i = 0; i < 3; ++i)
    mTranslation[i] = o.mTranslation[i];
  mScale = o.mScale;
  for (int i = 0; i < 9; ++i)
    mRotation[i] = o.mRotation[i];
  return *this;
}

// @ 0x005F4D00 -- element-wise copy of 0x38-byte records (returns the end pointer).
Blob38* copy_blob38(Blob38* first, Blob38* last, Blob38* out) {
  for (; first != last; ++first, ++out)
    if (out != 0)
      *out = *first;
  return out;
}

}  // namespace SP
