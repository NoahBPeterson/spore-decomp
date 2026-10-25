// slice s005f2780 -- SP::cSPSwatch (the 3D model swatch window proc: HandleMessage, DoMessage,
// viewport/rotation updates, image layers, show/hide, capture helpers) and a palette-swatch
// subclass (cost display, cursor, rollover), plus eastl::vector<AutoRefCount<cMWModel>>::DoDestroyValues.
// Retail cSPSwatch is 0x17c bytes (mID at +0x178); fields after it belong to the subclass.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include <float.h>
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
  T** AsOutParam() {
    if (mpObject) {
      T* const p = mpObject;
      mpObject = 0;
      p->Release();
    }
    return &mpObject;
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
  float GetWidth() const { return right - left; }
  float GetHeight() const { return bottom - top; }
};

struct Vector3 { float x, y, z; };
struct Matrix3 { float m[9]; };

void FUN_00409930(void* transform);               // 0x00409930 (cSPTransform ctor)
void FUN_006baa70(void* transform, float angle);  // 0x006baa70 (cSPTransform::PreRotateY)

// cSPTransform: flags/version at +0, translation at +4, basis at +0x14 (0x38 bytes, which is exactly
// the frame the retail code reserves for it in both functions below).
struct cSPTransform {
  uint16_t mFlags;         // +0x0
  uint16_t mVersion;       // +0x2
  Vector3 mTranslation;    // +0x4
  uint32_t pad10;          // +0x10
  float mBasis[9];         // +0x14
  void Reset() { FUN_00409930(this); }                          // 0x00409930
  void PreRotateY(float angle) { FUN_006baa70(this, angle); }   // 0x006baa70
  void SetTranslation(const Vector3& t) { mFlags |= 4; mVersion++; mTranslation = t; }
};

// the editor bounding-box data a model property can carry
class cSPBoundingBoxData {
 public:
  cSPBoundingBoxData* Init(void* source);   // 0x00511140
};

// cSPBoundingBox: the min/max box the renderer frames a model with
struct BoundingBox {
  Vector3 mMin;  // +0x0
  Vector3 mMax;  // +0xc
  void SetFrom(const cSPBoundingBoxData* data);   // 0x00571d60
  void TransformBy(const cSPTransform* xf);       // 0x00409dd0
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
using EA::BoundingBox;
using EA::cSPBoundingBoxData;
using EA::cSPTransform;
using EA::Matrix3;
using EA::ResourceMan::Key;
using EA::Vector3;
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

class cSPPaletteItemRollover;
struct cSPPaletteInfo : public EA::RefCountTemplate<int> {
  cSPEditorEconomy* mEconomy;               // +0x8
  void* mTheme;                             // +0xc
  void* mCollectableItems;                  // +0x10
  cSPPaletteItemRollover* mRollover;        // +0x14
  uint32_t pad18[6];
  bool mUseModelKey;                        // +0x30 (padding byte)
  bool mUseModelKeyForCost;                 // +0x31
};

class cSPPaletteItemRollover { public:
  void Hide();  // 0x005ed6c0
};
class cSPSwatchManager {
 public:
  cSPPaletteItemRollover* GetSwatchRollover();  // 0x0113ae10
  class cICameraManager* GetCameraManager();    // 0x01137690
  void* CreateAnimatingCreature(uint32_t id, void* key);  // 0x005f0330
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
class cViewer;
class cModelProperty;
class cICameraManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual cViewer* GetActiveViewer();  // +0x1c
  PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
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
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23)
  virtual BoundingBox* GetBoundingBox(struct cMWModel* model);  // +0x60
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
struct cMWModel {
  cModelWorld* mpWorld;          // +0x0
  uint32_t mFlags;               // +0x4
  uint16_t mTransformFlags;      // +0x8 (bit1: basis dirty, bit2: position dirty)
  uint16_t mTransformVersion;    // +0xa
  Vector3 mTransformPosition;    // +0xc
  float mTransformScale;         // +0x18
  float mTransformBasis[9];      // +0x1c
  int mRefCount;                 // +0x40
  void AddRef() { mRefCount++; }
  void Release();
  char pad44[0x90 - 0x44];
  cModelProperty* mpPropertyList;  // +0x90
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
  void SetVisible(bool visible);  // 0x0080d7c0
  void AddModel(void* model);     // 0x0080fc50
  void Release();                 // 0x0080d5f0
  void Refresh();                 // 0x0080dc00
  void* GetBuffer();              // 0x0093b6c0 (rw::movie::BufferedWriter::GetBuffer)
};
class cSwatchTexture {
 public:
  void* GetTexture();      // 0x0080d610
  void* FUN_0080d5f0();    // 0x0080d5f0
};
class cSwatchRenderer {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4)
  // frame one model into the swatch: box, target buffer, camera id, scale, draw flags, window aspect
  virtual void RenderSwatch(const BoundingBox* box, void* buffer, uint32_t cameraID, float scale,
                            int flags, float aspect);  // +0x14
  PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14)
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28)
  PV(29) PV(30) PV(31) PV(32) PV(33)
  virtual void SetTexture(void* texture);  // +0x88
};

class cSwatch3DView { public:
  bool mVisible;                        // +0x00
  cUILayeredObject* mLayeredObject;     // +0x04
  uint32_t pad08[5];                    // +0x08
  void* mAnimWorld;                     // +0x1c
  IWindow* mWindow;                     // +0x20
  cSwatchRenderer* mRenderer;           // +0x24
  class cCameraVt* mCamera;             // +0x28
  cSwatchTexture* mTexture;             // +0x2c
  class cISPCreatureAnimWorld* AddCreature(uint32_t modelID, void* key, int type);  // 0x005f3930
  void RenderFrame(int time);                                                       // 0x005f3810
  void Init(IWindow* renderer, uint32_t a, uint32_t b, uint32_t c);                 // 0x005f24e0
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
  PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
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

  void SetModelKey(Key* key);             // 0x005f4080
  void FrameModel();                      // 0x005f3cf0
  void OnBakingIsDone();                  // 0x005f42d0
  void UpdateBakingTransform();           // 0x005f40b0
  void InitInternal(IWindow* base, IWindow* modelWindow, uint32_t a3, uint32_t a4,
                    bool b5, bool b6, uint32_t a7, uint32_t a8);  // 0x005f3b20

  bool IsCapturedBySelf() {
    cInputManager* input = InputManager();
    if (input->IsCapturing()) {
      void* self = CastInterface(0xee3f516e);
      if (self == input->GetCaptured())
        return true;
    }
    return false;
  }
  // the surface the 3D view renders into: the layered object's buffer, else the texture's
  __forceinline void* GetFrameBuffer() {
    if (m3DView.mLayeredObject)
      return m3DView.mLayeredObject->GetBuffer();
    if (m3DView.mTexture)
      return m3DView.mTexture->FUN_0080d5f0();
    return 0;
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

  cSwatch3DView m3DView;                  // +0x10
  Key mOriginalItemKey;                   // +0x40
  Key mModelKey;                          // +0x4c
  uint32_t mUnk58;                        // +0x58
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
  cMWModel* mModel;                       // +0x118 (owned elsewhere)
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

// ==================== slice s005f36d0 ====================
// ---- helper stubs (bodies are not linked; call targets are relocation-masked) ----
class cViewer {
 public:
  void GetCameraLocationInfo(Vector3* out, int a, int b, int c);  // 0x007c3d30
};
class cRefObject {
 public:
  void AddRef();   // 0x00a02c30
  void Release();  // 0x00a05270
};
class cAnimWorld : public cRefObject {
 public:
  Vector3* GetPosition();  // 0x00a048a0
  void SetLOD(int v);      // 0x00a04c80
};
class cSwatchWindow {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
  virtual void Vt24(float t, void* buffer);  // +0x24
  PV(10) PV(11)
  virtual cRefObject* Vt30(uint32_t a, void* b, const void* c, const void* d, int e);  // +0x30
  PV(13) PV(14) PV(15)
  virtual void Vt40(cRefObject* a, void* b, int c);  // +0x40
};
// The swatch camera: slots named from the two call sites only (a key argument and a Vector3 the
// renderer feeds the camera). Nothing in these two functions reveals more of the semantics.
class cCameraVt {
 public:
  PV(0) PV(1) PV(2)
  virtual void Apply();                                                     // +0x0c
  PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11)
  virtual void SetTargetKey(const void* key);                               // +0x30
  PV(13)
  virtual void SetTargetPosition(const Vector3* position, const void* key);  // +0x38
  virtual void GetCameraPosition(Vector3* position);                        // +0x3c
  PV(16) PV(17) PV(18)
  virtual int GetType();                                                    // +0x4c
};
class cResourceManager {
 public:
  PV(0) PV(1) PV(2)
  virtual bool FindResource(uint32_t id, void** out, int, int, int, int);  // +0xc
};
cResourceManager* ResourceGetManager();  // 0x0067dcd0

class cPropertyManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual bool GetConfigProperty(int config, uint32_t key, cModelProperty** prop,
                                 bool* flag = 0);  // +0x2c
};
cPropertyManager* PropertyManager();               // 0x0067de30
int GetConfigFromModelType(uint32_t id);           // 0x00432f10
bool GetPropertyAsKey(void* prop, uint32_t key, Key* out);  // 0x006a1250
bool GetFloatProperty(void* prop, uint32_t key, float* out);  // 0x0040cf10
cSwatchRenderer* GetSwatchRenderer();              // 0x0067ddb0
void Matrix3_Assign(Matrix3* dst, const float* src);  // 0x0041cb40
void* FUN_005f2320(void* property);                // 0x005f2320
void FUN_004ad330();                               // 0x004ad330

// the model an editor paint-theme lookup resolves to, and the intrusive handle that owns it
class cSPEditorModel {
 public:
  bool SetWorld(void* world);   // 0x004ae260
};
struct cEditorModelRef {        // EA::AutoRefCountR<SP::cRefCountedResource>: handle prefixed to the model
 public:
  cSPEditorModel* mpObject;                 // +0x0
  cEditorModelRef() : mpObject(0) {}
  ~cEditorModelRef();                       // 0x004a9ae0
  cEditorModelRef* Reset();                 // 0x005766b0
};

Vector3* FUN_0046bfd0(Vector3* out, cSPEditorModel* model);   // 0x0046bfd0 (returns out)
void* FUN_006c10e0(void* owner);                              // 0x006c10e0
void* cSPBoundingBox_AddBoundingBox(int a, int b, int c);     // 0x0067cad0
bool cSPEditorPaintTheme_Apply(const Key* key, cEditorModelRef* model, int flags);  // 0x004badd0

// the property object hanging off cMWModel::+0x90
class cModelProperty {
 public:
  PV(0)
  virtual int Release();                                   // +0x4
  PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual bool HasProperty(uint32_t propertyID);           // +0x1c
  PV(8) PV(9)
  virtual void* GetProperty(uint32_t propertyID);          // +0x28
};

extern uint32_t DAT_0151c614;
extern uint32_t DAT_0151c590;
extern uint32_t DAT_0151c5f8;
extern float kSwatchRotationAngle;  // 0x0151c568
extern float kSwatchLayeredScale;   // 0x0151c700
extern Vector3 gSwatchZeroVector;   // 0x015f1ce4 (0,0,0)

// @ 0x005F36D0
uint32_t GetThumbnailCameraID(uint32_t modelType, uint32_t unused) {
  if (modelType == 0)
    return 0xff4641e7;
  uint32_t id = 0xffffffff;
  switch (modelType) {
    case 0x2399be55: id = 0x99e92f05; break;
    case 0x24682294: id = 0x7d433fad; break;
    case 0x2b978c46: id = 0x9ea3031a; break;
    case 0x2f4e681b: return 0xff4641e7;
    case 0x3d97a8e4: id = 0xdfad9f51; break;
    case 0x438f6347: id = 0xbcd73e89; break;
    case 0x476a98c7: id = 0x98e03c0d; break;
    case 0xb1b104: return 0xff4641e7;
    case 0xe6bce5: return 0xff4641e7;
  }
  uint32_t cameraID = 0xff4641e7;
  int config = GetConfigFromModelType(id);
  if (config != -1) {
    cPropertyManager* pm = PropertyManager();
    cModelProperty* prop = 0;
    bool flag = false;
    pm->GetConfigProperty(config, DAT_0151c614, &prop, &flag);
    if (prop) {
      Key k;
      k.mInstance = 0;
      k.mType = 0;
      k.mGroup = 0;
      if (GetPropertyAsKey(prop, flag ? 0xffedb73d : 0xb02d871c, &k))
        cameraID = k.mInstance;
    }
  }
  return cameraID;
}

// @ 0x005F4080
void cSPSwatch::SetModelKey(Key* key) {
  mModelKey = *key;
  mCamera = GetThumbnailCameraID(mModelKey.mType, 0);
}

// @ 0x005F42D0
void cSPSwatch::OnBakingIsDone() {
  mIsModelBaked = true;
  if (mModelLoaded) {
    mModelLoaded = false;
    mModelLoadStarted = true;
  }
  mHasBeenFramed = false;
  if (mUseEditorCameraController)
    UpdateBakingTransform();
}

// @ 0x005F3810
void cSwatch3DView::RenderFrame(int time) {
  cSwatchWindow* window = (cSwatchWindow*)mWindow;
  if (window) {
    void* buffer;
    if (mLayeredObject)
      buffer = mLayeredObject->GetBuffer();
    else if (mTexture)
      buffer = mTexture->FUN_0080d5f0();
    else
      buffer = 0;
    float t = (float)time;
    if (time < 0)
      t += 4294967296.0f;
    window->Vt24(t * 0.001f, buffer);
  }
  if (!mCamera)
    return;
  if (mCamera->GetType() != 0x5e5252a)
    return;
  Vector3 cameraPosition;
  SwatchManager()->GetCameraManager()->GetActiveViewer()->GetCameraLocationInfo(
      &cameraPosition, 0, 0, 0);
  if (mAnimWorld) {
    Vector3* position = ((cAnimWorld*)mAnimWorld)->GetPosition();
    Vector3 target;
    target.x = position->x;
    target.y = position->y;
    target.z = position->z;
    mCamera->SetTargetPosition(&target, &DAT_0151c590);
  } else {
    mCamera->SetTargetPosition(&gSwatchZeroVector, &DAT_0151c590);
  }
  mCamera->GetCameraPosition(&cameraPosition);
  mCamera->SetTargetKey(&DAT_0151c590);
  mCamera->Apply();
}

int FUN_00641770(void* self);          // 0x00641770
void* FUN_00bb9ae0();                  // 0x00bb9ae0
void FUN_008eb830(void* self, void* v);  // 0x008eb830

// @ 0x005F3930
cISPCreatureAnimWorld* cSwatch3DView::AddCreature(uint32_t modelID, void* key, int type) {
  if (mLayeredObject) {
    cAnimWorld* newWorld = (cAnimWorld*)SwatchManager()->CreateAnimatingCreature(modelID, key);
    cAnimWorld* old = (cAnimWorld*)mAnimWorld;
    if (newWorld != old) {
      if (newWorld)
        newWorld->AddRef();
      mAnimWorld = newWorld;
      if (old)
        old->Release();
    }
    mLayeredObject->AddModel(*(void**)((char*)mAnimWorld + 0x180));
    mLayeredObject->SetVisible(mVisible);
    if (FUN_00641770(mLayeredObject) == 0) {
      void* v = FUN_00bb9ae0();
      FUN_008eb830(mLayeredObject, v);
    }
    ((uint32_t*)mAnimWorld)[0x68 / 4] &= 0xfffffffd;
    ((uint32_t*)mAnimWorld)[0x6c / 4] &= 0xfffffffd;
    ((uint32_t*)mAnimWorld)[0x70 / 4] &= 0xfffffffd;
  }
  if (mWindow) {
    cAnimWorld* newWorld = (cAnimWorld*)((cSwatchWindow*)mWindow)
        ->Vt30(modelID, key, &gSwatchZeroVector, &DAT_0151c5f8, 1);
    cAnimWorld* old = (cAnimWorld*)mAnimWorld;
    if (newWorld != old) {
      if (newWorld)
        newWorld->AddRef();
      mAnimWorld = newWorld;
      if (old)
        old->Release();
    }
    ((cSwatchWindow*)mWindow)->Vt40((cRefObject*)mAnimWorld, key, 1);
  }
  if (!mAnimWorld)
    return 0;
  *((char*)mAnimWorld + 0x64) = 0;
  int finalType = type;
  if (type == -1) {
    cResourceManager* mgr = ResourceGetManager();
    int* res = 0;
    if (mgr->FindResource(modelID, (void**)&res, 0, 0, 0, 0))
      finalType = res[6];
    if (res)
      ((cRefObject*)res)->Release();
  }
  switch (finalType) {
    case 0x9ea3031a: ((cAnimWorld*)mAnimWorld)->SetLOD(0); break;
    case 0x372e2c04: ((cAnimWorld*)mAnimWorld)->SetLOD(5); break;
    case 0xccc35c46:
    case 0x4178b8e8:
    case 0x65672ade: ((cAnimWorld*)mAnimWorld)->SetLOD(6); break;
  }
  return (cISPCreatureAnimWorld*)mAnimWorld;
}

// @ 0x005F3CF0
void cSPSwatch::FrameModel() {
  if (mUseEditorCameraController) {
    mHasBeenFramed = true;
    return;
  }
  if (!GetFrameBuffer())
    return;
  bool hasLayers;                          // +0x13: the model is drawn over image layers
  AutoRefCount<cModelProperty> prop;       // +0x14: the model key's config property
  Vector3 translation;                     // +0x18: offset applied to the model transform
  float aspect;                            // +0x24
  float scale;                             // +0x28
  BoundingBox box;                         // +0x2c
  cSPBoundingBoxData data;                 // +0x44
  cSPTransform xf;                         // +0x5c

  // the model's box: the editor's stored box property when the model has one, else its world box
  box.mMin.x = FLT_MAX;
  box.mMin.y = FLT_MAX;
  box.mMin.z = FLT_MAX;
  box.mMax.x = -FLT_MAX;
  box.mMax.y = -FLT_MAX;
  box.mMax.z = -FLT_MAX;

  cMWModel* model = mModel;
  cModelProperty* props = model->mpPropertyList;
  if (props && props->HasProperty(0x1cbb2f62)) {
    box.SetFrom(data.Init(FUN_005f2320(props->GetProperty(0x1cbb2f62))));
  } else {
    BoundingBox* worldBox = model->mpWorld->GetBoundingBox(model);
    box.mMax = worldBox->mMax;
    box.mMin = worldBox->mMin;
  }

  hasLayers = mpImageLayers != 0;
  translation = gSwatchZeroVector;
  if (!hasLayers) {
    xf.Reset();
    Vector3 negated;
    negated.x = -((box.mMax.x + box.mMin.x) * 0.5f);
    negated.y = -((box.mMax.y + box.mMin.y) * 0.5f);
    negated.z = -((box.mMax.z + box.mMin.z) * 0.5f);
    xf.SetTranslation(negated);
    box.TransformBy(&xf);
    translation = negated;
  }

  scale = 1.2f;
  if (PropertyManager()->GetConfigProperty(mModelKey.mInstance, mModelKey.mGroup, prop.AsOutParam()) &&
      prop->HasProperty(0x5cd5de9))
    GetFloatProperty(prop.mpObject, 0x5cd5de9, &scale);
  else if (mpImageLayers)
    scale = kSwatchLayeredScale;

  aspect = mBaseWindow->GetRealArea().GetWidth() / mBaseWindow->GetRealArea().GetHeight();
  int flags = hasLayers ? 0 : 6;
  GetSwatchRenderer()->RenderSwatch(&box, GetFrameBuffer(), mCamera, scale, flags, aspect);

  if (!hasLayers) {
    model->mTransformFlags |= 4;
    model->mTransformVersion++;
    model->mTransformPosition = translation;
  }
  mHasBeenFramed = true;
}

// @ 0x005F40B0
void cSPSwatch::UpdateBakingTransform() {
  if (!mUseEditorCameraController)
    return;
  if (mpImageLayers)
    return;
  if (!mBakedAsset)
    return;
  cMWModel* model = mModel;
  if (!model)
    return;

  float scale = 1.0f;
  cSPEditorModel* paintModel;
  Vector3 offset;
  Matrix3 basis;
  cSPTransform xf;

  // bake scale: the model shrinks by the inverse of its configured bake scale
  cModelProperty* props = model->mpPropertyList;
  if (props && GetFloatProperty(props, 0xfba611, &scale) && scale > 0.0f) {
    model->mTransformVersion++;
    model->mTransformScale = 1.0f / scale;
  }

  // the bake is rendered from the fixed swatch rotation, not the on-screen one
  xf.Reset();
  xf.PreRotateY(kSwatchRotationAngle);
  Matrix3_Assign(&basis, xf.mBasis);
  model->mTransformFlags |= 2;
  for (int i = 0; i < 9; i++)
    model->mTransformBasis[i] = basis.m[i];
  model->mTransformVersion++;

  // the paint theme's model sits at the origin unless a box was built for it
  offset = gSwatchZeroVector;
  cEditorModelRef paintInfo;
  if (cSPEditorPaintTheme_Apply(&mModelKey, paintInfo.Reset(), 0)) {
    void* box = cSPBoundingBox_AddBoundingBox(0, 0, 0);
    paintModel = paintInfo.mpObject;
    paintModel->SetWorld(FUN_006c10e0(box));
    offset = *FUN_0046bfd0(&offset, paintModel);
    FUN_004ad330();
  }

  model->mTransformFlags |= 4;
  model->mTransformVersion++;
  model->mTransformPosition.x = -offset.x;
  model->mTransformPosition.y = -offset.y;
  model->mTransformPosition.z = -offset.z;
}

extern const wchar_t* const kSwatchMaterialNormal;  // 0x0151c41c

// @ 0x005F3B20
void cSPSwatch::InitInternal(IWindow* base, IWindow* modelWindow, uint32_t a3, uint32_t a4,
                             bool b5, bool b6, uint32_t a7, uint32_t a8) {
  mIgnoreFocusChange = b5;
  mForceRotation = b6;
  *(uint32_t*)((char*)this + 0xf4) = a7;
  mBaseWindow = base;
  if (mBaseWindow)
    mBaseWindow->AddWinProc((IWinProc*)this);
  mModelWindow = modelWindow;
  EA::Messaging::Server* server = MessageServer();
  if (server)
    server->AddHandler((EA::Messaging::IHandler*)((char*)this + 0xc), 0x695e243);
  m3DView.Init(mModelWindow, a4, a3, a8);
  mUseStaticEffects = (a3 == 0);
  RectT area = mBaseWindow->GetRealArea();
  mOriginalWindowArea = area;
  mWindowMaterial = kSwatchMaterialNormal;
  *(const wchar_t**)((char*)this + 0xc8) = kSwatchMaterialNormal;
  *(const wchar_t**)((char*)this + 0xd0) = mMaterialParams;
  *(const wchar_t**)((char*)this + 0xd4) = mMaterialParams;
  mTargetModelAlpha = 0.0f;
  mCurrentModelAlpha = 0.0f;
  mCamera = 0xff4641e7;
  RectT winArea = mModelWindow->GetRealArea();
  Point2D center = mModelWindow->GlobalToLocal(
      Point2D((winArea.right - winArea.left) * 0.5f, (winArea.bottom - winArea.top) * 0.5f));
  mTargetViewportCenter = center;
  mActualViewportCenter = center;
  mActualAngle = mTargetAngle;
  mActualViewportScale = mTargetViewportScale;
}

}  // namespace SP
