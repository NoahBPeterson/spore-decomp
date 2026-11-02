// src/game/SPEditors/SPSwatchStrategies.cpp -- migrated from slice(s) s00f0cad0, s00ed1880, s00ed0b70, s00eceab0, s00ecda80, s005f4310, s005f5f20, s005f5080, s005f36d0, s005f2780, s005f16d0 by tools/migrate/rewrite.py
// Object file: SPEditors/SPSwatchStrategies.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPOLDPaletteItemUIDragAndBuy.h"
#include "EA/Swarm/cIEffectsWorld.h"
#include "SP/cSPCreatureAnimManager.h"
#include "EA/ArgScript/cIParser.h"
#include "EA/UTFWin/CustomWindow.h"
#include "SP/cSPCreatureAnimWorld.h"
#include "EA/ResourceMan/Key.h"
#include "EA/Variant.h"
#include "EA/Audio/FactoryBinarySampleData.h"
#include "EA/Audio/Sound.h"
#include "SP/cISPPaletteItemUI.h"
#include "SP/cDirectPropertyList.h"
#include "SP/cSPPaletteInfo.h"
#include "SP/cSPPaletteItem.h"
#include "SP/cSPPaletteItemUI.h"
#include "cSPUILayeredObject.h"
#include "cSPUILayout.h"
#include "cSPUIModelsAndEffectsRenderer.h"
#include "cSPUITooltipWinProc.h"
#include "SP/cString.h"
#include "SP/cSwatch3DView.h"
#include <new>
#include "EA/Messaging/AutoHandler.h"
#include "EA/Messaging/IHandler.h"
#include "EA/UTFWin/IWinProc.h"
#include "EA/UTFWin/IWindow.h"
#include "EA/UTFWin/WindowMgr.h"
#include "EA/UTFWin/Message.h"
#include "EA/Messaging/Server.h"
#include "SP/cICameraController.h"
#include "SP/cICameraManager.h"
#include "SP/cMWModel.h"
#include "SP/cModelWorld.h"
#include "SP/cSPEditorAppEconomy.h"
#include "SP/cSPPaletteItemRollover.h"
#include "SP/cSPSwatch.h"
#include <math.h>
#include "SP/cISPCreatureAnimWorld.h"
#include "SP/cPropertyManager.h"
#include "SP/cAnimatingCreature.h"
#include "cSPTransform.h"
#include "SP/cViewer.h"
#include "SP/cPropertyList.h"
#include "SP/cSPEditorEconomy.h"
#include "EA/Stopwatch.h"
#include <intrin.h>

// ---- items of slice s005f16d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void _pv##n();
class cWriter {
 public:
  int GetBuffer();
};
class cObj2 {
 public:
  int Get();
};
namespace SP {
class cSPSwatchPlanner {
 public:
  int m00;      // +0x00
  void* m04;    // +0x04
  int m08;      // +0x08
  int m0c;      // +0x0c
  char pad10[0x1c];
  void* m2c;    // +0x2c
  char pad30[0x64];
  float m94;    // +0x94
  char pad98[0x53];
  bool mEB;     // +0xeb
  char padEC[0x14];
  int m100;     // +0x100
  char pad104[0x5c];
  bool m160;    // +0x160
  char pad161[2];
  bool m163;    // +0x163
  char pad164[2];
  bool m166;    // +0x166
  char pad167[0x31];
  bool m198;    // +0x198

  int Check();
  void* Cast(uint32_t id);
  int CheckType();
  float GetDouble94();
  int Contains(const float* point);
  int GetBuffer();
};  // namespace SP
}
namespace SW {
template <typename T>
class ARC {  // EA::AutoRefCount with inline operator=
 public:
  T* mpObject;
  ARC() : mpObject(0) {}
  ARC& operator=(T* pObject) {
    if (pObject != mpObject) {
      T* const pTemp = mpObject;
      if (pObject) pObject->AddRef();
      mpObject = pObject;
      if (pTemp) pTemp->Release();
    }
    return *this;
  }
  T*& AsOutParam() {
    if (mpObject) {
      T* const p = mpObject;
      mpObject = 0;
      p->Release();
    }
    return mpObject;
  }
  T* operator->() const { return mpObject; }
};
}
namespace SW {
class IWinProc;
}
namespace SW {
struct UIMessage;
}
namespace SW {
template <typename T>
class ARCExt {  // EA::AutoRefCount<IWinText>: operator= stays out of line (0x00b5f950)
 public:
  T* mpObject;
  ARCExt& operator=(T* p);  // 0x00b5f950
};
}
namespace SW {
typedef ARCExt<IWinProc> ARCText;
}
namespace SW {
class IRC;
}
namespace SW {
struct Key {
  uint32_t mInstance, mType, mGroup;
};
}
namespace SW {
class IWindow {
 public:
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
  virtual const float* GetArea();  // +0x38
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
  PV(30)
  virtual void SetFlag(int flag, bool value);    // +0x7c
  virtual void SetCaption(const wchar_t* text);  // +0x80
  PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47)
  PV(48) PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58) PV(59) PV(60) PV(61) PV(62)
  PV(63) PV(64)
  virtual void AddWinProc(IWinProc* proc);  // +0x104
};
}
namespace SW {
class IWinProc {
 public:
  ~IWinProc() {}
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4)
  virtual bool HandleUIMessage(IWindow* window, const UIMessage* message);  // +0x14
};
}
namespace SW {
class cSPUILayout {
 public:
  PV(0)
  virtual int AddRef();
  virtual int Release();
  cSPUILayout();  // 0x00810000
  IWindow* FindWindowByID(uint32_t id, bool recursive);  // 0x008105b0
  bool Init(const Key* key, bool b, uint32_t id);  // 0x008120d0
  void SetParentWin(IWindow* parent, bool b, uint32_t id);  // 0x008121b0
  char pad[0x18 - 4];
};
}
namespace SW {
class Property {
 public:
  char pad[0x12];
  uint16_t mType;  // +0x12
  bool* GetBool();  // 0x0041e920
  int* GetInt();  // 0x0041e990
};
}
namespace SW {
class cPropertyList {
 public:
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual bool HasProperty(uint32_t id);                    // +0x1c
  PV(8)
  virtual bool GetProperty(uint32_t id, Property** result);  // +0x24
};
}
namespace SW {
class IPropertyManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, cPropertyList*& result);  // +0x2c
};
}
namespace SW {
IPropertyManager* PropertyManager();  // 0x0067de30
}
namespace SW {
class IHandler {
 public:
  virtual bool HandleMessage(uint32_t messageID, void* message);
};
}
namespace SW {
class IRC {
 public:
  virtual int AddRef();
  virtual int Release();
};
}
namespace SW {
class IPadBase {
 public:
  virtual void pa();
  int pad4;
};
}
namespace SW {
class cSPPaletteItem : public IPadBase, public IRC {
 public:
  Key mKey;    // +0xc
};
}
namespace SW {
class cISPPaletteItemUI {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual void OnRolloverBegin();  // +0x1c
  virtual void OnRolloverEnd();    // +0x20
  cSPPaletteItem* mPaletteItem;    // +0x4
  int mInterfaceID;                // +0x8
};
}
namespace SW {
struct UIMessage {
  IWindow* mpSource;  // +0x0
  uint32_t pad4;
  int mType;          // +0x8
  int mArg;           // +0xc
  uint32_t pad10, pad14;
  IWindow* mArg2;     // +0x18
};
}
namespace SW {
class RefCountVT {
 public:
  RefCountVT() : mRefCount(0) {}
  virtual ~RefCountVT() {}
  virtual int AddRef();
  virtual int Release();
  int mRefCount;
};
}
namespace SW {
class cSPPaletteItemUI : public cISPPaletteItemUI, public IWinProc, public RefCountVT {
 public:
  bool HandleUIMessage(IWindow* window, const UIMessage* message);  // 0x005c6d70
  void Init(cSPPaletteItem* info, IWindow* button, int a, void* b);  // 0x005c6ca0
  bool mIsRolledOver;     // +0x18
  ARC<IWindow> mWinRoot;  // +0x1c
};
}
namespace SW {
extern uint32_t g_ModelGroup;                                                   // 0x0151c614
}
namespace SW {
void FUN_005a8ed0(Key key, cPropertyList*& out);
}
namespace SW {
int RemapTypeId(int id);                                                       // 0x00432f10
}
namespace SW {
class cSPPaletteInfo {
 public:
  PV(0)
  virtual int AddRef();
  virtual int Release();
  char pad04[0xc];
  int m10;
  char pad14[4];
  uint16_t mSymbol;  // +0x18
};
}
namespace SW {
class cSwatchItemInfo {
 public:
  char pad[0xc];
  Key mModelKey;  // +0xc
  Key mImageKey;  // +0x18
  bool Check(int arg);  // 0x005c6630
};
}
namespace SW {
class cSPPaletteSwatch {  // 0x1c8 bytes, ctor 0x005f7380
 public:
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
  virtual void SetModelKey(const Key* k);  // +0x24
  PV(10) PV(11) PV(12) PV(13)
  virtual void SetShowCostV(bool b);       // +0x38
  cSPPaletteSwatch();  // 0x005f7380
  void Init(const Key* key, IWindow* w, int a, uint32_t id, cSwatchItemInfo* info, cSPPaletteInfo* pi, bool flag);  // 0x005f4310
  void SetShowCost(bool b);  // 0x005f49a0
  void FUN_005f2290(int a);  // 0x005f2290
  char padE[0x100 - 4];
  uint32_t m100;
};
}
namespace SW {
class cSPSwatchPlannerReal : public cSPPaletteItemUI, public IHandler {
 public:
  bool HandleUIMessage(IWindow* window, const UIMessage* message);
  void Init(cSwatchItemInfo* info, IWindow* parent, int a, cSPPaletteInfo* palInfo);
  IWindow* FindActiveButton();  // 0x005f14a0
  void SetImage(const Key* key);   // 0x005f1500
  void SetModelHelper();
  void FUN_005f10b0();
  void SetModel(cPropertyList*& out);
  ARC<cSPUILayout> mLayout;     // +0x24
  ARC<cSPPaletteSwatch> mSwatch;  // +0x28
  ARCText mLargeNewTooltip;     // +0x2c
  ARCText mNewTooltip;          // +0x30
  ARCText mEditTooltip;         // +0x34
  ARCText mLoadTooltip;         // +0x38
  uint32_t mModelType;          // +0x3c
  int mLockedLevel;             // +0x40
  bool mModelChosen;            // +0x44
  bool mShowCost;               // +0x45
  bool mFlag46;                 // +0x46
  bool mReadyForMessages;       // +0x47
  bool mHasModelKey;            // +0x48
  char pad49[3];
  Key mModelKey;                // +0x4c
  int mModelKind;               // +0x58
  char pad5c[8];
  ARC<cPropertyList> mPropList;  // +0x64
  ARC<cSPPaletteInfo> mInfo;     // +0x68
};
}
namespace SW {
struct Rect {
  int left, top, right, bottom;
};
}
namespace SW {
class IArgObj {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5)
  virtual void Set(IArgObj* o);  // +0x18
};
}
namespace SW {
class IRefObj {  // generic virtual-refcounted object: AddRef slot 0, Release slot 1
 public:
  virtual int AddRef();
  virtual int Release();
};
}
namespace SW {
class cSPUILayeredObject {  // AddRef slot 1, Release slot 2
 public:
  PV(0)
  virtual int AddRef();
  virtual int Release();
  void FUN_0080dda0(IRefObj* renderer, int a);  // 0x0080dda0
  void FUN_0080d7d0(int a);                     // 0x0080d7d0
  void FUN_0080d790(int a, int b);              // 0x0080d790
  void FUN_0080d7c0(int a);                     // 0x0080d7c0
};
}
namespace SW {
class cSPUIModelsAndEffectsRenderer {  // non-virtual AddRef/Release
 public:
  void AddRef();   // 0x0080df50
  void Release();  // 0x0080df80
  void FUN_0080fa00(uint32_t a, uint32_t b, int c);  // 0x0080fa00 (cSPUILayerManager)
  void FUN_0080d5c0(int a);                          // 0x0080d5c0
  int FUN_0080db70();                                // 0x0080db70
  IArgObj* FUN_0080db90();                           // 0x0080db90
  class cSwatchTarget* FUN_0080d5a0(class IWindowLike* w, int a, int b);  // 0x0080d5a0
};
}
namespace SW {
class cSwatchTarget {
 public:
  void FUN_0080f360();  // 0x0080f360
};
}
namespace SW {
class IWindowLike {  // the "CustomSwatchAnimWorld" window: AddRef slot 0, Release slot 1
 public:
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4) PV(5)
  virtual void SetArg(IArgObj* o);  // +0x18
  virtual void SetArgs(int a, int b, int c, int d, int e);  // +0x1c
};
}
namespace SW {
class IAnimWorldManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
  virtual IWindowLike* GetWorld(const wchar_t* name);  // +0x20
};
}
namespace SW {
class IEffectWorld {  // m28: AddRef slot 0, Release slot 1
 public:
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3)
  virtual void V10(char a);        // +0x10
  virtual void V14(int a);         // +0x14
  virtual void V18(int a, int b);  // +0x18
  PV(7) PV(8)
  virtual void V24();              // +0x24
  virtual void V28(int a);         // +0x28
  PV(11) PV(12) PV(13) PV(14) PV(15)
  virtual void V40();              // +0x40
  PV(17)
  virtual void V48(uint32_t id);   // +0x48
};
}
namespace SW {
class IFactory;
}
namespace SW {
class cBoundingBoxLike {
 public:
  PV(0)
  IFactory* GetFactory();  // 0x006c10e0
};
}
namespace SW {
cBoundingBoxLike* AddBoundingBox();  // 0x0067cad0
}
namespace SW {
cSPUIModelsAndEffectsRenderer* FUN_0080ed50();
}
namespace SW {
cSPUILayeredObject* FUN_0080f730(cBoundingBoxLike* b);  // thiscall in orig? see below
}
namespace SW {
class IFactory {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58) PV(59) PV(60) PV(61) PV(62) PV(63) PV(64) PV(65) PV(66) PV(67) PV(68) PV(69) PV(70) PV(71) PV(72) PV(73) PV(74) PV(75) PV(76) PV(77) PV(78) PV(79) PV(80)
  virtual int Make(int a);  // +0x144
};
}
namespace SW {
class cSwatch3DView {
 public:
  void Init(IRefObj* renderer, int a2, char a3, char a4);  // 0x005f24e0
  bool mVisible;                          // +0x0
  ARC<cSPUILayeredObject> mLayeredObject;  // +0x4
  char pad08[0x20 - 8];
  ARC<IWindowLike> mWindow;               // +0x20
  ARC<IRefObj> mRenderer;                 // +0x24
  ARC<IEffectWorld> mEffectWorld;         // +0x28
  ARC<cSPUIModelsAndEffectsRenderer> mModelRenderer;  // +0x2c
};
}
namespace SW {
IAnimWorldManager* GetAnimWorldManager();             // 0x0067cb20
}
namespace SW {
IEffectWorld* GetEffectWorld();                       // 0x0067ddc0
}
namespace SW {
class cUIViewport {
 public:
  void FUN_007c4010();  // 0x007c4010
  void FUN_007c4a60(const Rect* r);  // 0x007c4a60
  void FUN_007c4b50(float aspect);   // 0x007c4b50
};
}
namespace SW {
class cAppLike {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
  PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
  virtual cUIViewport* GetScreenRect(Rect* out);  // +0x58
};
}
namespace SW {
cAppLike* App();  // 0x0067dd10
}
// ---- items of slice s005f16d0 end

// ---- items of slice s005f2780 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV_s005f_2780(n) virtual void pv##n();
namespace EA {
template <typename T>
class AutoRefCount_s005f_2780 {
 public:
  T* mpObject;
  AutoRefCount_s005f_2780() : mpObject(0) {}
  AutoRefCount_s005f_2780(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  AutoRefCount_s005f_2780(const AutoRefCount_s005f_2780& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount_s005f_2780() { if (mpObject) mpObject->Release(); }
  AutoRefCount_s005f_2780& operator=(T* p) {
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
}
namespace EA {
template <typename T>
class RefCountTemplate_s005f_2780 {
 public:
  RefCountTemplate_s005f_2780() : mRefCount(0) {}
  virtual ~RefCountTemplate_s005f_2780() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace EA {
template <typename T>
class RefCountVTemplate_s005f_2780 {
 public:
  RefCountVTemplate_s005f_2780() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s005f_2780() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace EA {
namespace COM {
class IUnknown32_s005f_2780 {
 public:
  virtual int AddRef() = 0;
  virtual int Release() = 0;
  virtual void* Cast(uint32_t typeID) const = 0;
};  // namespace COM
}
}
namespace EA {
namespace ResourceMan {
struct Key_s005f_2780 {
  unsigned int mInstance, mType, mGroup;
  bool operator==(const Key_s005f_2780& b) const {
    return mInstance == b.mInstance && mType == b.mType && mGroup == b.mGroup;
  }
  Key_s005f_2780() : mInstance(0), mType(0), mGroup(0) {}
  Key_s005f_2780(unsigned int instance, unsigned int type, unsigned int group)
      : mInstance(instance), mType(type), mGroup(group) {}
};  // namespace ResourceMan
}
}
namespace EA {
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
}
namespace EA {
struct RectT_s005f_2780 {
  RectT_s005f_2780() {}
  float left, top, right, bottom;
  RectT_s005f_2780(const RectT_s005f_2780& r) : left(r.left), top(r.top), right(r.right), bottom(r.bottom) {}
  bool Contains(const Point2D& p) const {
    return p.x >= left && p.y >= top && p.x < right && p.y < bottom;
  }
};
}
namespace EA {
namespace UTFWin {
class IWinProc_s005f_2780;
}
}
namespace EA {
namespace UTFWin {
class IWindow_s005f_2780 : public COM::IUnknown32_s005f_2780 {
 public:
  PV_s005f_2780(3)
  virtual IWindow_s005f_2780* GetParent();                     // +0x10
  PV_s005f_2780(5) PV_s005f_2780(6) PV_s005f_2780(7) PV_s005f_2780(8) PV_s005f_2780(9)
  virtual uint32_t GetFlags();                      // +0x28
  PV_s005f_2780(11) PV_s005f_2780(12) PV_s005f_2780(13)
  virtual const RectT_s005f_2780& GetRealArea();               // +0x38
  PV_s005f_2780(15) PV_s005f_2780(16) PV_s005f_2780(17) PV_s005f_2780(18) PV_s005f_2780(19) PV_s005f_2780(20) PV_s005f_2780(21) PV_s005f_2780(22)
  virtual void SetShadeColor(uint32_t color);       // +0x5c
  PV_s005f_2780(24) PV_s005f_2780(25) PV_s005f_2780(26)
  virtual void SetArea(const RectT_s005f_2780& area);          // +0x6c
  PV_s005f_2780(28) PV_s005f_2780(29)
  virtual void SetCursorID(uint32_t id);            // +0x78
  virtual void SetFlag(int flag, bool value);       // +0x7c
  virtual void SetCaption(const wchar_t* caption);  // +0x80
  PV_s005f_2780(33) PV_s005f_2780(34) PV_s005f_2780(35) PV_s005f_2780(36) PV_s005f_2780(37) PV_s005f_2780(38) PV_s005f_2780(39) PV_s005f_2780(40) PV_s005f_2780(41)
  virtual int IsAnimationDone();                    // +0xa8
  PV_s005f_2780(43) PV_s005f_2780(44) PV_s005f_2780(45) PV_s005f_2780(46) PV_s005f_2780(47)
  virtual Point2D GlobalToLocal(Point2D p);         // +0xc0
  PV_s005f_2780(49) PV_s005f_2780(50) PV_s005f_2780(51) PV_s005f_2780(52) PV_s005f_2780(53) PV_s005f_2780(54) PV_s005f_2780(55) PV_s005f_2780(56) PV_s005f_2780(57) PV_s005f_2780(58)
  PV_s005f_2780(59) PV_s005f_2780(60) PV_s005f_2780(61) PV_s005f_2780(62) PV_s005f_2780(63) PV_s005f_2780(64)
  virtual void AddWinProc(IWinProc_s005f_2780* proc);     // +0x104
  virtual void RemoveWinProc(IWinProc_s005f_2780* proc);  // +0x108
};
}
}
namespace EA {
namespace UTFWin {
struct Message_s005f_2780 {
  uint32_t pad0[2];
  uint32_t mEventType;                         // +0x8
  union { uint32_t mParam0c; float mX; };      // +0xc
  union { uint32_t mParam10; float mY; };      // +0x10
  uint32_t mModifiers;                         // +0x14
  union { uint32_t mButton; IWindow_s005f_2780* mpWindow; struct cCursorData* mpCursorData; };
};
}
}
namespace EA {
namespace UTFWin {
struct cCursorData { uint32_t pad[6]; uint32_t mCursorID; };  // +0x18
}
}
namespace EA {
namespace UTFWin {
class IWinProc_s005f_2780 : public COM::IUnknown32_s005f_2780 {
 public:
  virtual void* CastInterface(uint32_t typeID);  // +0xc
  virtual bool DoMessage(IWindow_s005f_2780* window, const Message_s005f_2780& message) = 0;
};
}
}
namespace EA {
namespace Messaging {
class IHandler_s005f_2780 {
 public:
  virtual ~IHandler_s005f_2780() {}
  virtual bool HandleMessage(uint32_t messageID, void* message) = 0;
};
}
}
namespace EA {
namespace Messaging {
class Server_s005f_2780 {
 public:
  PV_s005f_2780(0) PV_s005f_2780(1) PV_s005f_2780(2) PV_s005f_2780(3) PV_s005f_2780(4)
  virtual void MessageSend(uint32_t messageID, void* message, IHandler_s005f_2780* handler);  // +0x14 0x008853b0
  PV_s005f_2780(6) PV_s005f_2780(7) PV_s005f_2780(8)
  virtual void AddHandler(IHandler_s005f_2780* handler, uint32_t messageID);  // +0x24
  PV_s005f_2780(10)
  virtual void RemoveHandler(IHandler_s005f_2780* handler, uint32_t messageID, int priority);  // +0x2c 0x00883aa0
};
}
}
namespace EA {
namespace Messaging {
void RemoveHandler(Server_s005f_2780* server, IHandler_s005f_2780* handler, const uint32_t* ids, uint32_t count,
                   int priority);  // 0x00571db0
}
}
using EA::AutoRefCount_s005f_2780;
using EA::ResourceMan::Key_s005f_2780;
using EA::UTFWin::IWindow_s005f_2780;
using EA::UTFWin::IWinProc_s005f_2780;
using EA::UTFWin::Message_s005f_2780;
using EA::Point2D;
using EA::RectT_s005f_2780;
namespace SP {
class cString_s005f_2780 {
 public:
  cString_s005f_2780();   // 0x006b5060
  ~cString_s005f_2780();  // 0x006b5240
  uint32_t pad[5];
};
}
namespace SP {
EA::Messaging::Server_s005f_2780* MessageServer();  // 0x0067dcc0
}
namespace SP {
class cSPEditorEconomy_s005f_2780 {
 public:
  PV_s005f_2780(0) PV_s005f_2780(1)
  virtual bool IsItemAvailable(const Key_s005f_2780* key);                   // +0x8
  virtual bool CanAfford(int currency, int cost);                 // +0xc
  virtual int GetItemStatus(const Key_s005f_2780* key, struct cItemCostInfo* info);  // +0x10
};
}
namespace SP {
struct cSPPaletteItemRollover_s005f_2780;
}
namespace SP {
struct cSPPaletteInfo_s005f_2780 : public EA::RefCountTemplate_s005f_2780<int> {
  cSPEditorEconomy_s005f_2780* mEconomy;               // +0x8
  void* mTheme;                             // +0xc
  void* mCollectableItems;                  // +0x10
  cSPPaletteItemRollover_s005f_2780* mRollover;        // +0x14
  uint32_t pad18[6];
  bool mUseModelKey;                        // +0x30 (padding byte)
  bool mUseModelKeyForCost;                 // +0x31
};
}
namespace SP {
struct cSPPaletteItemRollover_s005f_2780 {
  void Hide();  // 0x005ed6c0
};
}
namespace SP {
class cSPSwatchManager {
 public:
  cSPPaletteItemRollover_s005f_2780* GetSwatchRollover();  // 0x0113ae10
  class cICameraManager_s005f_2780* GetCameraManager();    // 0x01137690
};
}
namespace SP {
cSPSwatchManager* SwatchManager();  // 0x00401020
}
namespace SP {
class cICameraController_s005f_2780 {
 public:
  PV_s005f_2780(0) PV_s005f_2780(1) PV_s005f_2780(2) PV_s005f_2780(3) PV_s005f_2780(4) PV_s005f_2780(5) PV_s005f_2780(6) PV_s005f_2780(7) PV_s005f_2780(8)
  virtual void OnMouseEnter(bool inside);                              // +0x24
  virtual bool OnKeyDown(uint32_t key, uint32_t modifiers);            // +0x28
  virtual bool OnKeyUp(uint32_t key, uint32_t modifiers);              // +0x2c
  virtual bool OnMouseDown(uint32_t button, float x, float y, uint32_t modifiers);  // +0x30
  virtual bool OnMouseUp(uint32_t button, float x, float y, uint32_t modifiers);    // +0x34
  virtual bool OnMouseMove(float x, float y, uint32_t modifiers);                   // +0x38
  virtual bool OnMouseWheel(int wheel, float x, float y, uint32_t modifiers);       // +0x3c
};
}
namespace SP {
class cICamera {
 public:
  PV_s005f_2780(0) PV_s005f_2780(1) PV_s005f_2780(2)
  virtual cICameraController_s005f_2780* Cast(uint32_t typeID);  // +0xc
};
}
namespace SP {
class cICameraManager_s005f_2780 {
 public:
  PV_s005f_2780(0) PV_s005f_2780(1) PV_s005f_2780(2) PV_s005f_2780(3) PV_s005f_2780(4) PV_s005f_2780(5) PV_s005f_2780(6) PV_s005f_2780(7) PV_s005f_2780(8) PV_s005f_2780(9) PV_s005f_2780(10) PV_s005f_2780(11) PV_s005f_2780(12) PV_s005f_2780(13)
  virtual cICamera* GetActiveCamera();  // +0x38
};
}
namespace SP {
class IWindowManager {
 public:
  PV_s005f_2780(0)
  virtual IWindow_s005f_2780* GetMainWindow();                    // +0x4
  PV_s005f_2780(2) PV_s005f_2780(3) PV_s005f_2780(4) PV_s005f_2780(5) PV_s005f_2780(6) PV_s005f_2780(7) PV_s005f_2780(8) PV_s005f_2780(9) PV_s005f_2780(10) PV_s005f_2780(11) PV_s005f_2780(12) PV_s005f_2780(13) PV_s005f_2780(14)
  virtual Point2D GetMousePosition();                  // +0x3c
  PV_s005f_2780(16) PV_s005f_2780(17) PV_s005f_2780(18)
  virtual void SetFocus(int which, IWindow_s005f_2780* window);   // +0x4c
  PV_s005f_2780(20)
  virtual IWindow_s005f_2780* GetFocus(int which);                // +0x54
  virtual void SetCapture(int which, IWindow_s005f_2780* window); // +0x58
  virtual void ReleaseCapture(int which, IWindow_s005f_2780* window);  // +0x5c
};
}
namespace SP {
IWindowManager* WindowManager();  // 0x0067caa0
}
namespace SP {
class cInputManager {
 public:
  bool IsCapturing();                                // 0x006c1100
  void* GetCaptured();                               // 0x006c10e0
  bool SetCapture(IWindow_s005f_2780* window, void* object);    // 0x008045a0
};
}
namespace SP {
cInputManager* InputManager();  // 0x00804500
}
namespace SP {
class cRenderManager {
 public:
  void SetHighlight(IWindow_s005f_2780* window, bool a, bool b);  // 0x0080d710
};
}
namespace SP {
cRenderManager* RenderManager();  // 0x0067cad0
}
namespace SP {
bool IsKeyDown(int key);                     // 0x008d2fb0
}
namespace SP {
int GetAudioSystem();                        // 0x00435e90
}
namespace SP {
void PlayAudio(uint32_t id, int system);     // 0x00435ed0
}
namespace SP {
void GetWindowGlobalArea(RectT_s005f_2780* area, IWindow_s005f_2780* window);  // 0x00805fe0
}
namespace SP {
IWindow_s005f_2780* CreateCostWindow(IWindow_s005f_2780* parent);              // 0x00806370
}
namespace SP {
struct cImageInfo { uint32_t pad[7]; int mWidth; int mHeight; };  // +0x1c / +0x20
}
namespace SP {
cImageInfo* GetImageInfo(uint32_t imageID);              // 0x00458de0
}
namespace SP {
void SetWindowImageInfo(IWindow_s005f_2780* window, cImageInfo* image, int index);  // 0x008068d0
}
namespace SP {
extern const wchar_t* const kSwatchMaterialNormal;   // 0x0151c41c
}
namespace SP {
extern const wchar_t* const kSwatchMaterialCost;     // 0x0151c414
}
namespace SP {
extern const wchar_t* const kSwatchMaterialLocked;   // 0x0151c418
}
namespace SP {
extern const wchar_t* const kSwatchParamsBlink;      // 0x0151c420
}
namespace SP {
extern const wchar_t* const kSwatchParamsDefault;    // 0x0151c424
}
namespace SP {
extern uint32_t kSwatchEffectDefault;                // 0x0151c40c
}
namespace SP {
extern uint32_t kSwatchEffectCreature;               // 0x0151c410
}
namespace SP {
extern float kTwoPI;                                 // 0x0151c428
}
namespace SP {
struct cItemCostInfo {
  cItemCostInfo();  // 0x005a7810
  ~cItemCostInfo() {}
  cString_s005f_2780 mName;        // +0x0
  cString_s005f_2780 mText;        // +0x14
  uint32_t mColor;      // +0x28
  uint32_t mImageID;    // +0x2c
  uint32_t mCost;       // +0x30
};
}
namespace SP {
class cModelWorld_s005f_2780 {
 public:
  PV_s005f_2780(0) PV_s005f_2780(1) PV_s005f_2780(2) PV_s005f_2780(3) PV_s005f_2780(4) PV_s005f_2780(5) PV_s005f_2780(6) PV_s005f_2780(7) PV_s005f_2780(8) PV_s005f_2780(9) PV_s005f_2780(10) PV_s005f_2780(11) PV_s005f_2780(12) PV_s005f_2780(13) PV_s005f_2780(14)
  PV_s005f_2780(15) PV_s005f_2780(16) PV_s005f_2780(17) PV_s005f_2780(18) PV_s005f_2780(19) PV_s005f_2780(20) PV_s005f_2780(21) PV_s005f_2780(22) PV_s005f_2780(23) PV_s005f_2780(24)
  virtual int GetEffectCount(class cMWModel_s005f_2780* model);  // +0x64
  PV_s005f_2780(26) PV_s005f_2780(27)
  virtual void StartEffect(cMWModel_s005f_2780* model, uint32_t effectID, int a, float b, int index);  // +0x70
  PV_s005f_2780(29) PV_s005f_2780(30) PV_s005f_2780(31) PV_s005f_2780(32) PV_s005f_2780(33) PV_s005f_2780(34) PV_s005f_2780(35) PV_s005f_2780(36) PV_s005f_2780(37) PV_s005f_2780(38) PV_s005f_2780(39) PV_s005f_2780(40) PV_s005f_2780(41) PV_s005f_2780(42)
  PV_s005f_2780(43) PV_s005f_2780(44) PV_s005f_2780(45) PV_s005f_2780(46) PV_s005f_2780(47) PV_s005f_2780(48) PV_s005f_2780(49) PV_s005f_2780(50) PV_s005f_2780(51) PV_s005f_2780(52) PV_s005f_2780(53) PV_s005f_2780(54) PV_s005f_2780(55) PV_s005f_2780(56)
  PV_s005f_2780(57) PV_s005f_2780(58) PV_s005f_2780(59) PV_s005f_2780(60) PV_s005f_2780(61) PV_s005f_2780(62) PV_s005f_2780(63) PV_s005f_2780(64) PV_s005f_2780(65) PV_s005f_2780(66) PV_s005f_2780(67) PV_s005f_2780(68) PV_s005f_2780(69) PV_s005f_2780(70)
  PV_s005f_2780(71) PV_s005f_2780(72) PV_s005f_2780(73) PV_s005f_2780(74) PV_s005f_2780(75) PV_s005f_2780(76) PV_s005f_2780(77) PV_s005f_2780(78) PV_s005f_2780(79) PV_s005f_2780(80) PV_s005f_2780(81) PV_s005f_2780(82) PV_s005f_2780(83) PV_s005f_2780(84)
  PV_s005f_2780(85) PV_s005f_2780(86) PV_s005f_2780(87) PV_s005f_2780(88) PV_s005f_2780(89) PV_s005f_2780(90) PV_s005f_2780(91)
  virtual void DestroyModel(class cMWModel_s005f_2780* model, bool immediate);  // +0x170
};
}
namespace SP {
class cMWModel_s005f_2780 {
 public:
  cModelWorld_s005f_2780* mpWorld;  // +0x0
  uint32_t mFlags;       // +0x4
  uint32_t pad8[14];
  int mRefCount;         // +0x40
  void AddRef() { mRefCount++; }
  void Release();
};
}
namespace SP {
class cImageLayers {
 public:
  PV_s005f_2780(0) PV_s005f_2780(1)
  virtual uint32_t AddLayer(uint32_t imageID, int flags);  // +0x8
  virtual void SetLayerVisible(uint32_t layer, bool on);   // +0xc
  virtual void SetLayerScaled(uint32_t layer, bool on);    // +0x10
  PV_s005f_2780(5)
  virtual void Refresh(uint32_t layer);                    // +0x18
  PV_s005f_2780(7)
  virtual void SetLayerTiled(uint32_t layer, bool on);     // +0x20
  virtual void SetLayerAlpha(uint32_t layer, float alpha); // +0x24
  uint32_t pad4[0x18];
  bool mVisible;  // +0x64
};
}
namespace SP {
class cUILayeredObject { public: void SetVisible(bool visible); };  // 0x0080d7c0
}
namespace SP {
class cRefCountedModel2;
class cSwatchTexture {
 public:
  void* GetTexture();                              // 0x0080d610
  cRefCountedModel2* GetModelManager();            // 0x0080db70
  void FUN_0080dfc0();                             // 0x0080dfc0 (thiscall, no args)
  void FUN_0080df80();                             // 0x0080df80 (thiscall, no args)
};
}
namespace SP {
class cSwatchRenderer {
 public:
  PV_s005f_2780(0) PV_s005f_2780(1) PV_s005f_2780(2) PV_s005f_2780(3) PV_s005f_2780(4) PV_s005f_2780(5) PV_s005f_2780(6) PV_s005f_2780(7) PV_s005f_2780(8) PV_s005f_2780(9) PV_s005f_2780(10) PV_s005f_2780(11) PV_s005f_2780(12) PV_s005f_2780(13) PV_s005f_2780(14)
  PV_s005f_2780(15) PV_s005f_2780(16) PV_s005f_2780(17) PV_s005f_2780(18) PV_s005f_2780(19) PV_s005f_2780(20) PV_s005f_2780(21) PV_s005f_2780(22) PV_s005f_2780(23) PV_s005f_2780(24) PV_s005f_2780(25) PV_s005f_2780(26) PV_s005f_2780(27) PV_s005f_2780(28)
  PV_s005f_2780(29) PV_s005f_2780(30) PV_s005f_2780(31) PV_s005f_2780(32) PV_s005f_2780(33)
  virtual void SetTexture(void* texture);  // +0x88
};
}
namespace SP {
struct cSwatch3DView_s005f_2780 {
  bool mVisible;                        // +0x10
  cUILayeredObject* mLayeredObject;     // +0x14
  uint32_t pad18[7];
  cSwatchRenderer* mRenderer;           // +0x34
  uint32_t pad38;
  cSwatchTexture* mTexture;             // +0x3c
};
}
namespace SP {
struct cModelChangedMessage {
  uint32_t pad0[2];
  uint32_t mInstanceID;  // +0x8
  uint32_t pad0c;
  uint32_t mGroupID;     // +0x10
  uint32_t pad14;
  uint32_t mTypeID;      // +0x18
};
}
namespace SP {
class cSPSwatch_s005f_2780 : public IWinProc_s005f_2780, public EA::RefCountVTemplate_s005f_2780<int>, public EA::Messaging::IHandler_s005f_2780 {
 public:
  virtual int AddRef();
  virtual int Release();
  virtual void* Cast(uint32_t typeID) const;
  virtual void* CastInterface(uint32_t typeID);
  virtual bool DoMessage(IWindow_s005f_2780* window, const Message_s005f_2780& message);
  PV_s005f_2780(5) PV_s005f_2780(6) PV_s005f_2780(7) PV_s005f_2780(8) PV_s005f_2780(9) PV_s005f_2780(10) PV_s005f_2780(11) PV_s005f_2780(12)
  virtual IWindow_s005f_2780* GetWindow();                   // +0x34
  PV_s005f_2780(14) PV_s005f_2780(15)
  virtual void OnMouseDown();                     // +0x40
  virtual bool IsDragging();                      // +0x44
  virtual void OnMouseEnter();                    // +0x48
  virtual void OnMouseLeave();                    // +0x4c
  virtual void OnClick();                         // +0x50
  PV_s005f_2780(21)
  virtual float GetTargetZoom();                  // +0x58
  PV_s005f_2780(23) PV_s005f_2780(24)
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
  void UpdateSwatchPosition(uint32_t deltaTime);  // 0x005f2bf0 (SP::cSPSwatch::UpdateSwatchPosition)
  uint32_t SetImage(uint32_t imageID, bool overlay);
  void Show3DModel();  // 0x005f2e00 (SP::cSPSwatch::Show3DModel)
  void Hide3DModel();  // 0x005f2eb0 (SP::cSPSwatch::Hide3DModel)
  void StartModelEffects();
  bool IsAnimating();
  bool TakeCapture();
  void EndInteraction();  // 0x005f3040 (SP::cSPSwatch::EndInteraction)
  bool HasCapture();
  int IsBusy();
  void UpdateViewport(uint32_t deltaTime);

  cSwatch3DView_s005f_2780 m3DView;                  // +0x10
  Key_s005f_2780 mOriginalItemKey;                   // +0x40
  Key_s005f_2780 mModelKey;                          // +0x4c
  uint32_t mUnk58;                        // +0x58
  AutoRefCount_s005f_2780<IWindow_s005f_2780> mBaseWindow;      // +0x5c
  AutoRefCount_s005f_2780<IWindow_s005f_2780> mModelWindow;     // +0x60
  float mActualViewportScale;             // +0x64
  float mActualAngle;                     // +0x68
  float mTargetAngle;                     // +0x6c
  float mTargetViewportScale;             // +0x70
  RectT_s005f_2780 mOriginalWindowArea;              // +0x74
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
  AutoRefCount_s005f_2780<cMWModel_s005f_2780> mModel;          // +0x118
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
}
namespace SP {
inline void cMWModel_s005f_2780::Release() {
  if (mRefCount > 1)
    mRefCount--;
  else
    mpWorld->DestroyModel(this, (mFlags >> 31) & 1);
}
}
namespace SP {
inline void* SwatchInterface(cSPSwatch_s005f_2780* swatch) {
  return swatch ? swatch->CastInterface(0xee3f516e) : 0;
}
}
namespace SP {
struct cSwatchMessage {
  cSPSwatch_s005f_2780* mpSwatch;  // +0x0
  uint32_t pad4;
  uint32_t mID;         // +0x8
  uint32_t padc;
};
}
namespace SP {
class cSPPaletteSwatch_s005f_2780 : public cSPSwatch_s005f_2780 {
 public:
  bool IsMouseOutside();
  bool IsItemAvailable();
  void UpdateCostDisplay();
  void UpdateCursor();
  void OnRolloverEnd();

  AutoRefCount_s005f_2780<cSPPaletteInfo_s005f_2780> mInfo;     // +0x17c
  uint32_t pad180;
  bool mIsLocked;                         // +0x184
  uint32_t pad188;
  IWindow_s005f_2780* mDragWindow;                   // +0x18c
  uint32_t pad190;
  AutoRefCount_s005f_2780<IWindow_s005f_2780> mCostWindow;      // +0x194
  bool mShowCost;                         // +0x198
  bool mDraggable;                        // +0x199
};
}
template <> EA::AutoRefCount_s005f_2780<IWindow_s005f_2780>& EA::AutoRefCount_s005f_2780<IWindow_s005f_2780>::operator=(IWindow_s005f_2780* p);
namespace eastl {
template <typename T>
class vector_s005f_2780 {
 public:
  void DoDestroyValues(T* first, T* last);
};  // namespace eastl
}
template void eastl::vector_s005f_2780<AutoRefCount_s005f_2780<SP::cMWModel_s005f_2780> >::DoDestroyValues(AutoRefCount_s005f_2780<SP::cMWModel_s005f_2780>*,
                                                                           AutoRefCount_s005f_2780<SP::cMWModel_s005f_2780>*);
// ---- items of slice s005f2780 end

// ---- items of slice s005f36d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV_s005f_36d0(n) virtual void pv##n();
namespace EA {
template <typename T>
class AutoRefCount_s005f_36d0 {
 public:
  T* mpObject;
  AutoRefCount_s005f_36d0() : mpObject(0) {}
  AutoRefCount_s005f_36d0(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  AutoRefCount_s005f_36d0(const AutoRefCount_s005f_36d0& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount_s005f_36d0() { if (mpObject) mpObject->Release(); }
  AutoRefCount_s005f_36d0& operator=(T* p) {
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
}
namespace EA {
template <typename T>
class RefCountVTemplate_s005f_36d0 {
 public:
  RefCountVTemplate_s005f_36d0() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s005f_36d0() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace EA {
namespace COM {
class IUnknown32_s005f_36d0 {
 public:
  virtual int AddRef() = 0;
  virtual int Release() = 0;
  virtual void* Cast(uint32_t typeID) const = 0;
};  // namespace COM
}
}
namespace EA {
namespace ResourceMan {
struct Key_s005f_36d0 {
  unsigned int mInstance, mType, mGroup;
  bool operator==(const Key_s005f_36d0& b) const {
    return mInstance == b.mInstance && mType == b.mType && mGroup == b.mGroup;
  }
  Key_s005f_36d0() : mInstance(0), mType(0), mGroup(0) {}
  Key_s005f_36d0(unsigned int instance, unsigned int type, unsigned int group)
      : mInstance(instance), mType(type), mGroup(group) {}
};  // namespace ResourceMan
}
}
namespace EA {
struct Point2D_s005f_36d0 {
  float x, y;
  Point2D_s005f_36d0() {}
  Point2D_s005f_36d0(float ax, float ay) : x(ax), y(ay) {}
  Point2D_s005f_36d0(const Point2D_s005f_36d0& p) : x(p.x), y(p.y) {}
  Point2D_s005f_36d0& operator=(const Point2D_s005f_36d0& p) {
    x = p.x;
    y = p.y;
    return *this;
  }
};
}
namespace EA {
struct RectT_s005f_36d0 {
  RectT_s005f_36d0() {}
  float left, top, right, bottom;
  RectT_s005f_36d0(const RectT_s005f_36d0& r) : left(r.left), top(r.top), right(r.right), bottom(r.bottom) {}
  bool Contains(const Point2D_s005f_36d0& p) const {
    return p.x >= left && p.y >= top && p.x < right && p.y < bottom;
  }
};
}
namespace EA {
namespace UTFWin {
class IWinProc_s005f_36d0;
}
}
namespace EA {
namespace UTFWin {
class IWindow_s005f_36d0 : public COM::IUnknown32_s005f_36d0 {
 public:
  PV_s005f_36d0(3)
  virtual IWindow_s005f_36d0* GetParent();                     // +0x10
  PV_s005f_36d0(5) PV_s005f_36d0(6) PV_s005f_36d0(7) PV_s005f_36d0(8) PV_s005f_36d0(9)
  virtual uint32_t GetFlags();                      // +0x28
  PV_s005f_36d0(11) PV_s005f_36d0(12) PV_s005f_36d0(13)
  virtual const RectT_s005f_36d0& GetRealArea();               // +0x38
  PV_s005f_36d0(15) PV_s005f_36d0(16) PV_s005f_36d0(17) PV_s005f_36d0(18) PV_s005f_36d0(19) PV_s005f_36d0(20) PV_s005f_36d0(21) PV_s005f_36d0(22)
  virtual void SetShadeColor(uint32_t color);       // +0x5c
  PV_s005f_36d0(24) PV_s005f_36d0(25) PV_s005f_36d0(26)
  virtual void SetArea(const RectT_s005f_36d0& area);          // +0x6c
  PV_s005f_36d0(28) PV_s005f_36d0(29)
  virtual void SetCursorID(uint32_t id);            // +0x78
  virtual void SetFlag(int flag, bool value);       // +0x7c
  virtual void SetCaption(const wchar_t* caption);  // +0x80
  PV_s005f_36d0(33) PV_s005f_36d0(34) PV_s005f_36d0(35) PV_s005f_36d0(36) PV_s005f_36d0(37) PV_s005f_36d0(38) PV_s005f_36d0(39) PV_s005f_36d0(40) PV_s005f_36d0(41)
  virtual int IsAnimationDone();                    // +0xa8
  PV_s005f_36d0(43) PV_s005f_36d0(44) PV_s005f_36d0(45) PV_s005f_36d0(46) PV_s005f_36d0(47)
  virtual Point2D_s005f_36d0 GlobalToLocal(Point2D_s005f_36d0 p);         // +0xc0
  PV_s005f_36d0(49) PV_s005f_36d0(50) PV_s005f_36d0(51) PV_s005f_36d0(52) PV_s005f_36d0(53) PV_s005f_36d0(54) PV_s005f_36d0(55) PV_s005f_36d0(56) PV_s005f_36d0(57) PV_s005f_36d0(58)
  PV_s005f_36d0(59) PV_s005f_36d0(60) PV_s005f_36d0(61) PV_s005f_36d0(62) PV_s005f_36d0(63) PV_s005f_36d0(64)
  virtual void AddWinProc(IWinProc_s005f_36d0* proc);     // +0x104
  virtual void RemoveWinProc(IWinProc_s005f_36d0* proc);  // +0x108
};
}
}
namespace EA {
namespace UTFWin {
struct Message_s005f_36d0 {
  uint32_t pad0[2];
  uint32_t mEventType;                         // +0x8
  union { uint32_t mParam0c; float mX; };      // +0xc
  union { uint32_t mParam10; float mY; };      // +0x10
  uint32_t mModifiers;                         // +0x14
  union { uint32_t mButton; IWindow_s005f_36d0* mpWindow; struct cCursorData* mpCursorData; };
};
}
}
namespace EA {
namespace UTFWin {
class IWinProc_s005f_36d0 : public COM::IUnknown32_s005f_36d0 {
 public:
  virtual void* CastInterface(uint32_t typeID);  // +0xc
  virtual bool DoMessage(IWindow_s005f_36d0* window, const Message_s005f_36d0& message) = 0;
};
}
}
namespace EA {
namespace Messaging {
class IHandler_s005f_36d0 {
 public:
  virtual ~IHandler_s005f_36d0() {}
  virtual bool HandleMessage(uint32_t messageID, void* message) = 0;
};
}
}
namespace EA {
namespace Messaging {
class Server_s005f_36d0 {
 public:
  PV_s005f_36d0(0) PV_s005f_36d0(1) PV_s005f_36d0(2) PV_s005f_36d0(3) PV_s005f_36d0(4)
  virtual void MessageSend(uint32_t messageID, void* message, IHandler_s005f_36d0* handler);  // +0x14 0x008853b0
  PV_s005f_36d0(6) PV_s005f_36d0(7) PV_s005f_36d0(8)
  virtual void AddHandler(IHandler_s005f_36d0* handler, uint32_t messageID);  // +0x24
  PV_s005f_36d0(10)
  virtual void RemoveHandler(IHandler_s005f_36d0* handler, uint32_t messageID, int priority);  // +0x2c 0x00883aa0
};
}
}
namespace EA {
namespace Messaging {
void RemoveHandler(Server_s005f_36d0* server, IHandler_s005f_36d0* handler, const uint32_t* ids, uint32_t count,
                   int priority);  // 0x00571db0
}
}
using EA::AutoRefCount_s005f_36d0;
using EA::ResourceMan::Key_s005f_36d0;
using EA::UTFWin::IWindow_s005f_36d0;
using EA::UTFWin::IWinProc_s005f_36d0;
using EA::UTFWin::Message_s005f_36d0;
using EA::Point2D_s005f_36d0;
using EA::RectT_s005f_36d0;
namespace SP {
EA::Messaging::Server_s005f_36d0* MessageServer_s005f_36d0();  // 0x0067dcc0
}
namespace SP {
struct cSPPaletteItemRollover_s005f_36d0;
}
namespace SP {
struct cSPPaletteItemRollover_s005f_36d0 {
  void Hide();  // 0x005ed6c0
};
}
namespace SP {
class cSPSwatchManager_s005f_36d0 {
 public:
  cSPPaletteItemRollover_s005f_36d0* GetSwatchRollover();  // 0x0113ae10
  class cICameraManager_s005f_36d0* GetCameraManager();    // 0x01137690
  void* CreateAnimatingCreature(uint32_t id, void* key);  // 0x005f0330
};
}
namespace SP {
cSPSwatchManager_s005f_36d0* SwatchManager_s005f_36d0();  // 0x00401020
}
namespace SP {
class cICameraController_s005f_36d0 {
 public:
  PV_s005f_36d0(0) PV_s005f_36d0(1) PV_s005f_36d0(2) PV_s005f_36d0(3) PV_s005f_36d0(4) PV_s005f_36d0(5) PV_s005f_36d0(6) PV_s005f_36d0(7) PV_s005f_36d0(8)
  virtual void OnMouseEnter(bool inside);                              // +0x24
  virtual bool OnKeyDown(uint32_t key, uint32_t modifiers);            // +0x28
  virtual bool OnKeyUp(uint32_t key, uint32_t modifiers);              // +0x2c
  virtual bool OnMouseDown(uint32_t button, float x, float y, uint32_t modifiers);  // +0x30
  virtual bool OnMouseUp(uint32_t button, float x, float y, uint32_t modifiers);    // +0x34
  virtual bool OnMouseMove(float x, float y, uint32_t modifiers);                   // +0x38
  virtual bool OnMouseWheel(int wheel, float x, float y, uint32_t modifiers);       // +0x3c
};
}
namespace SP {
class cICamera_s005f_36d0 {
 public:
  PV_s005f_36d0(0) PV_s005f_36d0(1) PV_s005f_36d0(2)
  virtual cICameraController_s005f_36d0* Cast(uint32_t typeID);  // +0xc
};
}
namespace SP {
class cViewer_s005f_36d0;
}
namespace SP {
class cICameraManager_s005f_36d0 {
 public:
  PV_s005f_36d0(0) PV_s005f_36d0(1) PV_s005f_36d0(2) PV_s005f_36d0(3) PV_s005f_36d0(4) PV_s005f_36d0(5) PV_s005f_36d0(6)
  virtual cViewer_s005f_36d0* GetActiveViewer();  // +0x1c
  PV_s005f_36d0(8) PV_s005f_36d0(9) PV_s005f_36d0(10) PV_s005f_36d0(11) PV_s005f_36d0(12) PV_s005f_36d0(13)
  virtual cICamera_s005f_36d0* GetActiveCamera();  // +0x38
};
}
namespace SP {
class cInputManager_s005f_36d0 {
 public:
  bool IsCapturing();                                // 0x006c1100
  void* GetCaptured();                               // 0x006c10e0
  bool SetCapture(IWindow_s005f_36d0* window, void* object);    // 0x008045a0
};
}
namespace SP {
cInputManager_s005f_36d0* InputManager_s005f_36d0();  // 0x00804500
}
namespace SP {
class cModelWorld_s005f_36d0 {
 public:
  PV_s005f_36d0(0) PV_s005f_36d0(1) PV_s005f_36d0(2) PV_s005f_36d0(3) PV_s005f_36d0(4) PV_s005f_36d0(5) PV_s005f_36d0(6) PV_s005f_36d0(7) PV_s005f_36d0(8) PV_s005f_36d0(9) PV_s005f_36d0(10) PV_s005f_36d0(11) PV_s005f_36d0(12) PV_s005f_36d0(13) PV_s005f_36d0(14)
  PV_s005f_36d0(15) PV_s005f_36d0(16) PV_s005f_36d0(17) PV_s005f_36d0(18) PV_s005f_36d0(19) PV_s005f_36d0(20) PV_s005f_36d0(21) PV_s005f_36d0(22) PV_s005f_36d0(23) PV_s005f_36d0(24)
  virtual int GetEffectCount(class cMWModel_s005f_36d0* model);  // +0x64
  PV_s005f_36d0(26) PV_s005f_36d0(27)
  virtual void StartEffect(cMWModel_s005f_36d0* model, uint32_t effectID, int a, float b, int index);  // +0x70
  PV_s005f_36d0(29) PV_s005f_36d0(30) PV_s005f_36d0(31) PV_s005f_36d0(32) PV_s005f_36d0(33) PV_s005f_36d0(34) PV_s005f_36d0(35) PV_s005f_36d0(36) PV_s005f_36d0(37) PV_s005f_36d0(38) PV_s005f_36d0(39) PV_s005f_36d0(40) PV_s005f_36d0(41) PV_s005f_36d0(42)
  PV_s005f_36d0(43) PV_s005f_36d0(44) PV_s005f_36d0(45) PV_s005f_36d0(46) PV_s005f_36d0(47) PV_s005f_36d0(48) PV_s005f_36d0(49) PV_s005f_36d0(50) PV_s005f_36d0(51) PV_s005f_36d0(52) PV_s005f_36d0(53) PV_s005f_36d0(54) PV_s005f_36d0(55) PV_s005f_36d0(56)
  PV_s005f_36d0(57) PV_s005f_36d0(58) PV_s005f_36d0(59) PV_s005f_36d0(60) PV_s005f_36d0(61) PV_s005f_36d0(62) PV_s005f_36d0(63) PV_s005f_36d0(64) PV_s005f_36d0(65) PV_s005f_36d0(66) PV_s005f_36d0(67) PV_s005f_36d0(68) PV_s005f_36d0(69) PV_s005f_36d0(70)
  PV_s005f_36d0(71) PV_s005f_36d0(72) PV_s005f_36d0(73) PV_s005f_36d0(74) PV_s005f_36d0(75) PV_s005f_36d0(76) PV_s005f_36d0(77) PV_s005f_36d0(78) PV_s005f_36d0(79) PV_s005f_36d0(80) PV_s005f_36d0(81) PV_s005f_36d0(82) PV_s005f_36d0(83) PV_s005f_36d0(84)
  PV_s005f_36d0(85) PV_s005f_36d0(86) PV_s005f_36d0(87) PV_s005f_36d0(88) PV_s005f_36d0(89) PV_s005f_36d0(90) PV_s005f_36d0(91)
  virtual void DestroyModel(class cMWModel_s005f_36d0* model, bool immediate);  // +0x170
};
}
namespace SP {
class cMWModel_s005f_36d0 {
 public:
  cModelWorld_s005f_36d0* mpWorld;  // +0x0
  uint32_t mFlags;       // +0x4
  uint32_t pad8[14];
  int mRefCount;         // +0x40
  void AddRef() { mRefCount++; }
  void Release();
};
}
namespace SP {
class cImageLayers_s005f_36d0 {
 public:
  PV_s005f_36d0(0) PV_s005f_36d0(1)
  virtual uint32_t AddLayer(uint32_t imageID, int flags);  // +0x8
  virtual void SetLayerVisible(uint32_t layer, bool on);   // +0xc
  virtual void SetLayerScaled(uint32_t layer, bool on);    // +0x10
  PV_s005f_36d0(5)
  virtual void Refresh(uint32_t layer);                    // +0x18
  PV_s005f_36d0(7)
  virtual void SetLayerTiled(uint32_t layer, bool on);     // +0x20
  virtual void SetLayerAlpha(uint32_t layer, float alpha); // +0x24
  uint32_t pad4[0x18];
  bool mVisible;  // +0x64
};
}
namespace SP {
class cUILayeredObject_s005f_36d0 {
 public:
  void SetVisible(bool visible);  // 0x0080d7c0
  void AddModel(void* model);     // 0x0080fc50
  void Release();                 // 0x0080d5f0
  void Refresh();                 // 0x0080dc00
  void* GetBuffer();              // 0x0093b6c0 (rw::movie::BufferedWriter::GetBuffer)
};
}
namespace SP {
class cSwatchTexture_s005f_36d0 {
 public:
  void* GetTexture();      // 0x0080d610
  void* FUN_0080d5f0();    // 0x0080d5f0
};
}
namespace SP {
class cSwatchRenderer_s005f_36d0 {
 public:
  PV_s005f_36d0(0) PV_s005f_36d0(1) PV_s005f_36d0(2) PV_s005f_36d0(3) PV_s005f_36d0(4) PV_s005f_36d0(5) PV_s005f_36d0(6) PV_s005f_36d0(7) PV_s005f_36d0(8) PV_s005f_36d0(9) PV_s005f_36d0(10) PV_s005f_36d0(11) PV_s005f_36d0(12) PV_s005f_36d0(13) PV_s005f_36d0(14)
  PV_s005f_36d0(15) PV_s005f_36d0(16) PV_s005f_36d0(17) PV_s005f_36d0(18) PV_s005f_36d0(19) PV_s005f_36d0(20) PV_s005f_36d0(21) PV_s005f_36d0(22) PV_s005f_36d0(23) PV_s005f_36d0(24) PV_s005f_36d0(25) PV_s005f_36d0(26) PV_s005f_36d0(27) PV_s005f_36d0(28)
  PV_s005f_36d0(29) PV_s005f_36d0(30) PV_s005f_36d0(31) PV_s005f_36d0(32) PV_s005f_36d0(33)
  virtual void SetTexture(void* texture);  // +0x88
};
}
namespace SP {
struct cSwatch3DView_s005f_36d0 {
  bool mVisible;                        // +0x00
  cUILayeredObject_s005f_36d0* mLayeredObject;     // +0x04
  uint32_t pad08[5];                    // +0x08
  void* mAnimWorld;                     // +0x1c
  IWindow_s005f_36d0* mWindow;                     // +0x20
  cSwatchRenderer_s005f_36d0* mRenderer;           // +0x24
  void* mCamera;                        // +0x28
  cSwatchTexture_s005f_36d0* mTexture;             // +0x2c
  class cISPCreatureAnimWorld* AddCreature(uint32_t modelID, void* key, int type);  // 0x005f3930
  void RenderFrame(int time);                                                       // 0x005f3810
  void Init(IWindow_s005f_36d0* renderer, uint32_t a, uint32_t b, uint32_t c);                 // 0x005f24e0
};
}
namespace SP {
class cSPSwatch_s005f_36d0 : public IWinProc_s005f_36d0, public EA::RefCountVTemplate_s005f_36d0<int>, public EA::Messaging::IHandler_s005f_36d0 {
 public:
  virtual int AddRef();
  virtual int Release();
  virtual void* Cast(uint32_t typeID) const;
  virtual void* CastInterface(uint32_t typeID);
  virtual bool DoMessage(IWindow_s005f_36d0* window, const Message_s005f_36d0& message);
  PV_s005f_36d0(5) PV_s005f_36d0(6) PV_s005f_36d0(7) PV_s005f_36d0(8) PV_s005f_36d0(9) PV_s005f_36d0(10) PV_s005f_36d0(11) PV_s005f_36d0(12)
  virtual IWindow_s005f_36d0* GetWindow();                   // +0x34
  PV_s005f_36d0(14) PV_s005f_36d0(15)
  virtual void OnMouseDown();                     // +0x40
  virtual bool IsDragging();                      // +0x44
  virtual void OnMouseEnter();                    // +0x48
  virtual void OnMouseLeave();                    // +0x4c
  virtual void OnClick();                         // +0x50
  PV_s005f_36d0(21)
  virtual float GetTargetZoom();                  // +0x58
  PV_s005f_36d0(23) PV_s005f_36d0(24)
  virtual void ReloadModel();                     // +0x64
  virtual bool HandleMessage(uint32_t messageID, void* message);

  void SetModelKey(Key_s005f_36d0* key);             // 0x005f4080
  void FrameModel();                      // 0x005f3cf0
  void OnBakingIsDone();                  // 0x005f42d0
  void UpdateBakingTransform();           // 0x005f40b0
  void InitInternal(IWindow_s005f_36d0* base, IWindow_s005f_36d0* modelWindow, uint32_t a3, uint32_t a4,
                    bool b5, bool b6, uint32_t a7, uint32_t a8);  // 0x005f3b20

  bool IsCapturedBySelf() {
    cInputManager_s005f_36d0* input = InputManager_s005f_36d0();
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
  void UpdateSwatchPosition(uint32_t deltaTime);  // 0x005f2bf0 (SP::cSPSwatch::UpdateSwatchPosition)
  uint32_t SetImage(uint32_t imageID, bool overlay);
  void Show3DModel();  // 0x005f2e00 (SP::cSPSwatch::Show3DModel)
  void Hide3DModel();  // 0x005f2eb0 (SP::cSPSwatch::Hide3DModel)
  void StartModelEffects();
  bool IsAnimating();
  bool TakeCapture();
  void EndInteraction();  // 0x005f3040 (SP::cSPSwatch::EndInteraction)
  bool HasCapture();
  int IsBusy();
  void UpdateViewport(uint32_t deltaTime);

  cSwatch3DView_s005f_36d0 m3DView;                  // +0x10
  Key_s005f_36d0 mOriginalItemKey;                   // +0x40
  Key_s005f_36d0 mModelKey;                          // +0x4c
  uint32_t mUnk58;                        // +0x58
  AutoRefCount_s005f_36d0<IWindow_s005f_36d0> mBaseWindow;      // +0x5c
  AutoRefCount_s005f_36d0<IWindow_s005f_36d0> mModelWindow;     // +0x60
  float mActualViewportScale;             // +0x64
  float mActualAngle;                     // +0x68
  float mTargetAngle;                     // +0x6c
  float mTargetViewportScale;             // +0x70
  RectT_s005f_36d0 mOriginalWindowArea;              // +0x74
  Point2D_s005f_36d0 mActualViewportCenter;          // +0x84
  Point2D_s005f_36d0 mTargetViewportCenter;          // +0x8c
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
  cImageLayers_s005f_36d0* mpImageLayers;            // +0xf0
  uint32_t padf4;
  uint32_t mImageID;                      // +0xf8
  bool mImageOverlay;                     // +0xfc
  bool mImageSet;                         // +0xfd
  uint32_t pad100[6];
  AutoRefCount_s005f_36d0<cMWModel_s005f_36d0> mModel;          // +0x118
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
}
namespace SP {
inline void cMWModel_s005f_36d0::Release() {
  if (mRefCount > 1)
    mRefCount--;
  else
    mpWorld->DestroyModel(this, (mFlags >> 31) & 1);
}
}
namespace SP {
struct Vector3 { float x, y, z; };
}
namespace SP {
class cViewer_s005f_36d0 {
 public:
  void GetCameraLocationInfo(Vector3* out, int a, int b, int c);  // 0x007c3d30
};
}
namespace SP {
class cRefObject {
 public:
  void AddRef();   // 0x00a02c30
  void Release();  // 0x00a05270
};
}
namespace SP {
class cAnimWorld : public cRefObject {
 public:
  void SetLOD(int v);  // 0x00a04c80
};
}
namespace SP {
class cSwatchWindow {
 public:
  PV_s005f_36d0(0) PV_s005f_36d0(1) PV_s005f_36d0(2) PV_s005f_36d0(3) PV_s005f_36d0(4) PV_s005f_36d0(5) PV_s005f_36d0(6) PV_s005f_36d0(7) PV_s005f_36d0(8)
  virtual void Vt24(float t, void* buffer);  // +0x24
  PV_s005f_36d0(10) PV_s005f_36d0(11)
  virtual cRefObject* Vt30(uint32_t a, void* b, const void* c, const void* d, int e);  // +0x30
  PV_s005f_36d0(13) PV_s005f_36d0(14) PV_s005f_36d0(15)
  virtual void Vt40(cRefObject* a, void* b, int c);  // +0x40
};
}
namespace SP {
class cCameraVt {
 public:
  PV_s005f_36d0(0) PV_s005f_36d0(1) PV_s005f_36d0(2) PV_s005f_36d0(3) PV_s005f_36d0(4) PV_s005f_36d0(5) PV_s005f_36d0(6) PV_s005f_36d0(7) PV_s005f_36d0(8) PV_s005f_36d0(9) PV_s005f_36d0(10) PV_s005f_36d0(11) PV_s005f_36d0(12)
  PV_s005f_36d0(13) PV_s005f_36d0(14) PV_s005f_36d0(15) PV_s005f_36d0(16) PV_s005f_36d0(17) PV_s005f_36d0(18)
  virtual int GetType();  // +0x4c
};
}
namespace SP {
class cResourceManager {
 public:
  PV_s005f_36d0(0) PV_s005f_36d0(1) PV_s005f_36d0(2)
  virtual bool FindResource(uint32_t id, void** out, int, int, int, int);  // +0xc
};
}
namespace SP {
cResourceManager* ResourceGetManager();  // 0x0067dcd0
}
namespace SP {
class cPropertyManager_s005f_36d0 {
 public:
  PV_s005f_36d0(0) PV_s005f_36d0(1) PV_s005f_36d0(2) PV_s005f_36d0(3) PV_s005f_36d0(4) PV_s005f_36d0(5) PV_s005f_36d0(6) PV_s005f_36d0(7) PV_s005f_36d0(8) PV_s005f_36d0(9) PV_s005f_36d0(10)
  virtual bool GetConfigProperty(int config, uint32_t key, void** prop, bool* flag);  // +0x2c
};
}
namespace SP {
cPropertyManager_s005f_36d0* PropertyManager();               // 0x0067de30
}
namespace SP {
int GetConfigFromModelType(uint32_t id);           // 0x00432f10
}
namespace SP {
bool GetPropertyAsKey(void* prop, uint32_t key, Key_s005f_36d0* out);  // 0x006a1250
}
namespace SP {
bool GetFloatProperty(void* prop, uint32_t key, float* out);  // 0x0040cf10
}
namespace SP {
void* FUN_00a048a0();                              // 0x00a048a0
}
namespace SP {
void FUN_00409930(void* transform);                // 0x00409930 (cSPTransform ctor)
}
namespace SP {
void FUN_006baa70(uint32_t v);                     // 0x006baa70
}
namespace SP {
void Matrix3_Assign(void* dst, const void* src);   // 0x0041cb40
}
namespace SP {
extern uint32_t DAT_0151c614;
}
namespace SP {
extern uint32_t DAT_0151c568;
}
namespace SP {
extern uint32_t DAT_0151c5f8;
}
namespace SP {
extern float DAT_015f1ce4;
}
namespace SP {
extern float DAT_015f1ce8;
}
namespace SP {
extern float DAT_015f1cec;
}
namespace SP {
int FUN_00641770(void* self);          // 0x00641770
}
namespace SP {
void* FUN_00bb9ae0();                  // 0x00bb9ae0
}
namespace SP {
void FUN_008eb830(void* self, void* v);  // 0x008eb830
}
namespace SP {
struct cSPTransform { uint32_t pad[16]; };
}
namespace SP {
struct Matrix3 { float m[9]; };
}
namespace SP {
void* FUN_005766b0(int v);                                  // 0x005766b0
}
namespace SP {
bool cSPEditorPaintTheme_Apply(const Key_s005f_36d0* key, void* theme);  // 0x004badd0
}
namespace SP {
void* cSPBoundingBox_AddBoundingBox(int, int, int);         // 0x0067cad0
void* cSPBoundingBox_AddBoundingBox();                      // 0x0067cad0
}
namespace SP {
void* FUN_0046bfd0(void* out, int v);                       // 0x0046bfd0
}
namespace SP {
void* FUN_006c10e0();                                       // 0x006c10e0
}
namespace SP {
void FUN_004ad330();                                        // 0x004ad330
}
namespace SP {
void FUN_004a9ae0();                                        // 0x004a9ae0
}
// ---- items of slice s005f36d0 end

// ---- items of slice s005f5080 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV_s005f_5080(n) virtual void pv##n();
namespace EA {
template <typename T>
class AutoRefCount_s005f_5080 {
 public:
  T* mpObject;
  AutoRefCount_s005f_5080() : mpObject(0) {}
  AutoRefCount_s005f_5080(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  AutoRefCount_s005f_5080(const AutoRefCount_s005f_5080& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount_s005f_5080() { if (mpObject) mpObject->Release(); }
  AutoRefCount_s005f_5080& operator=(T* p) {
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
  AutoRefCount_s005f_5080& operator=(const AutoRefCount_s005f_5080& x) { return operator=(x.mpObject); }
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
}
namespace EA {
template <typename T>
class RefCountVTemplate_s005f_5080 {
 public:
  RefCountVTemplate_s005f_5080() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s005f_5080() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace EA {
namespace COM {
class IUnknown32_s005f_5080 {
 public:
  virtual int AddRef() = 0;
  virtual int Release() = 0;
  virtual void* Cast(uint32_t typeID) const = 0;
};  // namespace COM
}
}
namespace EA {
namespace ResourceMan {
struct Key_s005f_5080 {
  unsigned int mInstance, mType, mGroup;
  bool operator==(const Key_s005f_5080& b) const {
    return mInstance == b.mInstance && mType == b.mType && mGroup == b.mGroup;
  }
  Key_s005f_5080() : mInstance(0), mType(0), mGroup(0) {}
  Key_s005f_5080(unsigned int instance, unsigned int type, unsigned int group)
      : mInstance(instance), mType(type), mGroup(group) {}
};  // namespace ResourceMan
}
}
namespace EA {
struct Point2D_s005f_5080 {
  float x, y;
  Point2D_s005f_5080() {}
  Point2D_s005f_5080(float ax, float ay) : x(ax), y(ay) {}
  Point2D_s005f_5080(const Point2D_s005f_5080& p) : x(p.x), y(p.y) {}
  Point2D_s005f_5080& operator=(const Point2D_s005f_5080& p) {
    x = p.x;
    y = p.y;
    return *this;
  }
};
}
namespace EA {
struct RectT_s005f_5080 {
  RectT_s005f_5080() {}
  float left, top, right, bottom;
  RectT_s005f_5080(const RectT_s005f_5080& r) : left(r.left), top(r.top), right(r.right), bottom(r.bottom) {}
  bool Contains(const Point2D_s005f_5080& p) const {
    return p.x >= left && p.y >= top && p.x < right && p.y < bottom;
  }
};
}
namespace EA {
namespace UTFWin {
class IWinProc_s005f_5080;
}
}
namespace EA {
namespace UTFWin {
class IWindow_s005f_5080 : public COM::IUnknown32_s005f_5080 {
 public:
  PV_s005f_5080(3)
  virtual IWindow_s005f_5080* GetParent();                     // +0x10
  PV_s005f_5080(5) PV_s005f_5080(6) PV_s005f_5080(7) PV_s005f_5080(8) PV_s005f_5080(9)
  virtual uint32_t GetFlags();                      // +0x28
  PV_s005f_5080(11) PV_s005f_5080(12) PV_s005f_5080(13)
  virtual const RectT_s005f_5080& GetRealArea();               // +0x38
  PV_s005f_5080(15) PV_s005f_5080(16) PV_s005f_5080(17) PV_s005f_5080(18) PV_s005f_5080(19) PV_s005f_5080(20) PV_s005f_5080(21) PV_s005f_5080(22)
  virtual void SetShadeColor(uint32_t color);       // +0x5c
  PV_s005f_5080(24) PV_s005f_5080(25) PV_s005f_5080(26)
  virtual void SetArea(const RectT_s005f_5080& area);          // +0x6c
  PV_s005f_5080(28) PV_s005f_5080(29)
  virtual void SetCursorID(uint32_t id);            // +0x78
  virtual void SetFlag(int flag, bool value);       // +0x7c
  virtual void SetCaption(const wchar_t* caption);  // +0x80
  PV_s005f_5080(33) PV_s005f_5080(34) PV_s005f_5080(35) PV_s005f_5080(36) PV_s005f_5080(37) PV_s005f_5080(38) PV_s005f_5080(39) PV_s005f_5080(40) PV_s005f_5080(41)
  virtual int IsAnimationDone();                    // +0xa8
  PV_s005f_5080(43) PV_s005f_5080(44) PV_s005f_5080(45) PV_s005f_5080(46) PV_s005f_5080(47)
  virtual Point2D_s005f_5080 GlobalToLocal(Point2D_s005f_5080 p);         // +0xc0
  PV_s005f_5080(49) PV_s005f_5080(50) PV_s005f_5080(51) PV_s005f_5080(52) PV_s005f_5080(53) PV_s005f_5080(54) PV_s005f_5080(55) PV_s005f_5080(56) PV_s005f_5080(57) PV_s005f_5080(58)
  PV_s005f_5080(59) PV_s005f_5080(60) PV_s005f_5080(61) PV_s005f_5080(62) PV_s005f_5080(63) PV_s005f_5080(64)
  virtual void AddWinProc(IWinProc_s005f_5080* proc);     // +0x104
  virtual void RemoveWinProc(IWinProc_s005f_5080* proc);  // +0x108
};
}
}
namespace EA {
namespace UTFWin {
struct Message_s005f_5080 {
  uint32_t pad0[2];
  uint32_t mEventType;                         // +0x8
  union { uint32_t mParam0c; float mX; };      // +0xc
  union { uint32_t mParam10; float mY; };      // +0x10
  uint32_t mModifiers;                         // +0x14
  union { uint32_t mButton; IWindow_s005f_5080* mpWindow; struct cCursorData* mpCursorData; };
};
}
}
namespace EA {
namespace UTFWin {
class IWinProc_s005f_5080 : public COM::IUnknown32_s005f_5080 {
 public:
  virtual void* CastInterface(uint32_t typeID);  // +0xc
  virtual bool DoMessage(IWindow_s005f_5080* window, const Message_s005f_5080& message) = 0;
};
}
}
namespace EA {
namespace Messaging {
class IHandler_s005f_5080 {
 public:
  virtual ~IHandler_s005f_5080() {}
  virtual bool HandleMessage(uint32_t messageID, void* message) = 0;
};
}
}
using EA::AutoRefCount_s005f_5080;
using EA::ResourceMan::Key_s005f_5080;
using EA::UTFWin::IWindow_s005f_5080;
using EA::UTFWin::IWinProc_s005f_5080;
using EA::UTFWin::Message_s005f_5080;
using EA::Point2D_s005f_5080;
using EA::RectT_s005f_5080;
namespace SP {
class cSPSwatchManager_s005f_5080 {
 public:
  cSPPaletteItemRollover* GetSwatchRollover();  // 0x0113ae10
  class cICameraManager* GetCameraManager();    // 0x01137690
};
}
namespace SP {
class cInputManager_s005f_5080 {
 public:
  bool IsCapturing();                                // 0x006c1100
  void* GetCaptured();                               // 0x006c10e0
  bool SetCapture(IWindow_s005f_5080* window, void* object);    // 0x008045a0
};
}
namespace SP {
cInputManager_s005f_5080* InputManager_s005f_5080();  // 0x00804500
}
namespace SP {
class cModelWorld_s005f_5080 {
 public:
  PV_s005f_5080(0) PV_s005f_5080(1) PV_s005f_5080(2) PV_s005f_5080(3) PV_s005f_5080(4) PV_s005f_5080(5) PV_s005f_5080(6) PV_s005f_5080(7) PV_s005f_5080(8) PV_s005f_5080(9) PV_s005f_5080(10) PV_s005f_5080(11) PV_s005f_5080(12) PV_s005f_5080(13) PV_s005f_5080(14)
  PV_s005f_5080(15) PV_s005f_5080(16) PV_s005f_5080(17) PV_s005f_5080(18) PV_s005f_5080(19) PV_s005f_5080(20) PV_s005f_5080(21) PV_s005f_5080(22) PV_s005f_5080(23) PV_s005f_5080(24)
  virtual int GetEffectCount(class cMWModel_s005f_5080* model);  // +0x64
  PV_s005f_5080(26) PV_s005f_5080(27)
  virtual void StartEffect(cMWModel_s005f_5080* model, uint32_t effectID, int a, float b, int index);  // +0x70
  PV_s005f_5080(29) PV_s005f_5080(30) PV_s005f_5080(31) PV_s005f_5080(32) PV_s005f_5080(33) PV_s005f_5080(34) PV_s005f_5080(35) PV_s005f_5080(36) PV_s005f_5080(37) PV_s005f_5080(38) PV_s005f_5080(39) PV_s005f_5080(40) PV_s005f_5080(41) PV_s005f_5080(42)
  PV_s005f_5080(43) PV_s005f_5080(44) PV_s005f_5080(45) PV_s005f_5080(46) PV_s005f_5080(47) PV_s005f_5080(48) PV_s005f_5080(49) PV_s005f_5080(50) PV_s005f_5080(51) PV_s005f_5080(52) PV_s005f_5080(53) PV_s005f_5080(54) PV_s005f_5080(55) PV_s005f_5080(56)
  PV_s005f_5080(57) PV_s005f_5080(58) PV_s005f_5080(59) PV_s005f_5080(60) PV_s005f_5080(61) PV_s005f_5080(62) PV_s005f_5080(63) PV_s005f_5080(64) PV_s005f_5080(65) PV_s005f_5080(66) PV_s005f_5080(67) PV_s005f_5080(68) PV_s005f_5080(69) PV_s005f_5080(70)
  PV_s005f_5080(71) PV_s005f_5080(72) PV_s005f_5080(73) PV_s005f_5080(74) PV_s005f_5080(75) PV_s005f_5080(76) PV_s005f_5080(77) PV_s005f_5080(78) PV_s005f_5080(79) PV_s005f_5080(80) PV_s005f_5080(81) PV_s005f_5080(82) PV_s005f_5080(83) PV_s005f_5080(84)
  PV_s005f_5080(85) PV_s005f_5080(86) PV_s005f_5080(87) PV_s005f_5080(88) PV_s005f_5080(89) PV_s005f_5080(90) PV_s005f_5080(91)
  virtual void DestroyModel(class cMWModel_s005f_5080* model, bool immediate);  // +0x170
};
}
namespace SP {
class cMWModel_s005f_5080 {
 public:
  cModelWorld_s005f_5080* mpWorld;  // +0x0
  uint32_t mFlags;       // +0x4
  uint32_t pad8[14];
  int mRefCount;         // +0x40
  void AddRef() { mRefCount++; }
  void Release();
};
}
namespace SP {
class cImageLayers_s005f_5080 {
 public:
  PV_s005f_5080(0) PV_s005f_5080(1)
  virtual uint32_t AddLayer(uint32_t imageID, int flags);  // +0x8
  virtual void SetLayerVisible(uint32_t layer, bool on);   // +0xc
  virtual void SetLayerScaled(uint32_t layer, bool on);    // +0x10
  PV_s005f_5080(5)
  virtual void Refresh(uint32_t layer);                    // +0x18
  PV_s005f_5080(7)
  virtual void SetLayerTiled(uint32_t layer, bool on);     // +0x20
  virtual void SetLayerAlpha(uint32_t layer, float alpha); // +0x24
  uint32_t pad4[0x18];
  bool mVisible;  // +0x64
};
}
namespace SP {
class cUILayeredObject_s005f_5080 {
 public:
  void SetVisible(bool visible);   // 0x0080d7c0
  void RemoveModel(void* model);   // 0x0080e980
  void AddModel(void* model);      // 0x0080fc50
};
}
namespace SP {
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
};  // namespace eastl
}
}
namespace SP {
class cSwatchRenderer_s005f_5080 {
 public:
  PV_s005f_5080(0) PV_s005f_5080(1) PV_s005f_5080(2) PV_s005f_5080(3) PV_s005f_5080(4) PV_s005f_5080(5) PV_s005f_5080(6) PV_s005f_5080(7) PV_s005f_5080(8) PV_s005f_5080(9) PV_s005f_5080(10) PV_s005f_5080(11) PV_s005f_5080(12) PV_s005f_5080(13) PV_s005f_5080(14)
  PV_s005f_5080(15) PV_s005f_5080(16) PV_s005f_5080(17) PV_s005f_5080(18) PV_s005f_5080(19) PV_s005f_5080(20) PV_s005f_5080(21) PV_s005f_5080(22) PV_s005f_5080(23) PV_s005f_5080(24) PV_s005f_5080(25) PV_s005f_5080(26) PV_s005f_5080(27) PV_s005f_5080(28)
  PV_s005f_5080(29) PV_s005f_5080(30) PV_s005f_5080(31) PV_s005f_5080(32) PV_s005f_5080(33)
  virtual void SetTexture(void* texture);  // +0x88
};
}
namespace SP {
struct cSwatch3DView_s005f_5080 {
  bool mVisible;                                            // +0x00
  cUILayeredObject_s005f_5080* mLayeredObject;                         // +0x04
  eastl::vector<AutoRefCount_s005f_5080<cMWModel_s005f_5080> > mModels;           // +0x08
  uint32_t pad14;                                           // +0x14
  uint32_t pad18;                                           // +0x18
  void* mAnimWorld;                                         // +0x1c
  IWindow_s005f_5080* mWindow;                                         // +0x20
  cSwatchRenderer_s005f_5080* mRenderer;                               // +0x24
  uint32_t pad28;                                           // +0x28
  cSwatchTexture* mTexture;                                 // +0x2c
  void RemoveModel(cMWModel_s005f_5080* model);                        // 0x005f4eb0
  cMWModel_s005f_5080* AddModel(uint32_t a, uint32_t b);               // 0x005f59b0
  void RemoveAllModels();                                   // 0x005f5aa0
};
}
namespace SP {
class cSPSwatch_s005f_5080 : public IWinProc_s005f_5080, public EA::RefCountVTemplate_s005f_5080<int>, public EA::Messaging::IHandler_s005f_5080 {
 public:
  virtual int AddRef();
  virtual int Release();
  virtual void* Cast(uint32_t typeID) const;
  virtual void* CastInterface(uint32_t typeID);
  virtual bool DoMessage(IWindow_s005f_5080* window, const Message_s005f_5080& message);
  PV_s005f_5080(5) PV_s005f_5080(6) PV_s005f_5080(7) PV_s005f_5080(8)
  virtual void Vt24(void* key);                   // +0x24
  PV_s005f_5080(10) PV_s005f_5080(11) PV_s005f_5080(12)
  virtual IWindow_s005f_5080* GetWindow();                   // +0x34
  PV_s005f_5080(14) PV_s005f_5080(15)
  virtual void OnMouseDown();                     // +0x40
  virtual bool IsDragging();                      // +0x44
  virtual void OnMouseEnter();                    // +0x48
  virtual void OnMouseLeave();                    // +0x4c
  virtual void OnClick();                         // +0x50
  PV_s005f_5080(21)
  virtual float GetTargetZoom();                  // +0x58
  PV_s005f_5080(23) PV_s005f_5080(24)
  virtual void ReloadModel();                     // +0x64
  virtual bool HandleMessage(uint32_t messageID, void* message);

  bool IsCapturedBySelf() {
    cInputManager_s005f_5080* input = InputManager_s005f_5080();
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
  void UpdateSwatchPosition(uint32_t deltaTime);  // 0x005f2bf0 (SP::cSPSwatch::UpdateSwatchPosition)
  uint32_t SetImage(uint32_t imageID, bool overlay);
  void Show3DModel();  // 0x005f2e00 (SP::cSPSwatch::Show3DModel)
  void Hide3DModel();  // 0x005f2eb0 (SP::cSPSwatch::Hide3DModel)
  void StartModelEffects();
  bool IsAnimating();
  bool TakeCapture();
  void EndInteraction();  // 0x005f3040 (SP::cSPSwatch::EndInteraction)
  bool HasCapture();
  int IsBusy();
  void UpdateViewport(uint32_t deltaTime);

  void Init(Key_s005f_5080* key, uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t scale);   // 0x005f4f80
  void Init(Key_s005f_5080* key, void* a, void* b, uint32_t c, uint32_t d, uint32_t e, uint32_t f, uint32_t scale);  // 0x005f5000
  void InitInternal(IWindow_s005f_5080* base, IWindow_s005f_5080* modelWindow, uint32_t a3, uint32_t a4,
                    uint32_t b5, uint32_t b6, uint32_t a7, uint32_t a8);  // 0x005f3b20
  void RotateModel(uint32_t flags);       // 0x005f55e0
  void LoadModel();                       // 0x005f5b40
  void ShutDownModel();                   // 0x005f5df0
  void AddModelKey(const Key_s005f_5080& key);       // 0x005f58f0

  cSwatch3DView_s005f_5080 m3DView;                  // +0x10
  Key_s005f_5080 mOriginalItemKey;                   // +0x40
  Key_s005f_5080 mModelKey;                          // +0x4c
  uint32_t mScaleParam;                   // +0x58
  AutoRefCount_s005f_5080<IWindow_s005f_5080> mBaseWindow;      // +0x5c
  AutoRefCount_s005f_5080<IWindow_s005f_5080> mModelWindow;     // +0x60
  float mActualViewportScale;             // +0x64
  float mActualAngle;                     // +0x68
  float mTargetAngle;                     // +0x6c
  float mTargetViewportScale;             // +0x70
  RectT_s005f_5080 mOriginalWindowArea;              // +0x74
  Point2D_s005f_5080 mActualViewportCenter;          // +0x84
  Point2D_s005f_5080 mTargetViewportCenter;          // +0x8c
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
  cImageLayers_s005f_5080* mpImageLayers;            // +0xf0
  uint32_t padf4;
  uint32_t mImageID;                      // +0xf8
  bool mImageOverlay;                     // +0xfc
  bool mImageSet;                         // +0xfd
  uint32_t pad100[6];
  AutoRefCount_s005f_5080<cMWModel_s005f_5080> mModel;          // +0x118
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
}
namespace SP {
inline void cMWModel_s005f_5080::Release() {
  if (mRefCount > 1)
    mRefCount--;
  else
    mpWorld->DestroyModel(this, (mFlags >> 31) & 1);
}
}
namespace SP {
AutoRefCount_s005f_5080<cMWModel_s005f_5080>* copy_refs(AutoRefCount_s005f_5080<cMWModel_s005f_5080>* first, AutoRefCount_s005f_5080<cMWModel_s005f_5080>* last,
                                  AutoRefCount_s005f_5080<cMWModel_s005f_5080>* out);  // 0x5f4e10
}
namespace SP {
void* FUN_0080db70();                          // 0x0080db70
}
namespace SP {
void FUN_0080ea50(void* self);                 // 0x0080ea50
}
namespace SP {
void FUN_008eb830(void* self, int v);          // 0x008eb830
}
namespace SP {
void FUN_005f0380();                           // 0x005f0380
}
namespace SP {
int  FUN_0080d7c0(int visible);                // 0x0080d7c0
}
namespace SP {
void DoDestroyValues_ref(AutoRefCount_s005f_5080<cMWModel_s005f_5080>* first, AutoRefCount_s005f_5080<cMWModel_s005f_5080>* last);  // 0x5f3680
}
namespace SP {
class cRefCountedModel2 {
 public:
  PV_s005f_5080(0) PV_s005f_5080(1) PV_s005f_5080(2)
  virtual cMWModel_s005f_5080* MakeModel(uint32_t a, uint32_t b, int c);  // +0xc
};
class cSPBoundingBox {
 public:
  cRefCountedModel2* GetModelManager();  // 0x006c10e0
};
}
namespace SP {
struct KeyVec {
  Key_s005f_5080* mpBegin;
  Key_s005f_5080* mpEnd;
  Key_s005f_5080* mpCapacity;
  void push_back(const Key_s005f_5080& v);                 // 0x005f58f0
  void DoInsertValue(Key_s005f_5080* pos, const Key_s005f_5080& v);   // 0x4e3e10
  void clear() { mpEnd = mpBegin; }
};
}
namespace SP {
struct RefVec {
  AutoRefCount_s005f_5080<cMWModel_s005f_5080>* mpBegin;
  AutoRefCount_s005f_5080<cMWModel_s005f_5080>* mpEnd;
  AutoRefCount_s005f_5080<cMWModel_s005f_5080>* mpCapacity;
  void clear();  // 0x005f5970
  void DoDestroyValues(AutoRefCount_s005f_5080<cMWModel_s005f_5080>* first, AutoRefCount_s005f_5080<cMWModel_s005f_5080>* last);  // 0x5f3680
  void DoInsertValue(AutoRefCount_s005f_5080<cMWModel_s005f_5080>* pos, cMWModel_s005f_5080** value);  // 0x423c40
};
}
namespace SP {
class cSwatchWindow_s005f_5080 {
 public:
  PV_s005f_5080(0) PV_s005f_5080(1) PV_s005f_5080(2) PV_s005f_5080(3) PV_s005f_5080(4) PV_s005f_5080(5) PV_s005f_5080(6) PV_s005f_5080(7) PV_s005f_5080(8) PV_s005f_5080(9) PV_s005f_5080(10) PV_s005f_5080(11) PV_s005f_5080(12) PV_s005f_5080(13) PV_s005f_5080(14)
  virtual void Vt3c(void* p);  // +0x3c
};
}
namespace SP {
class cAnimWorld_s005f_5080 {
 public:
  void Release();
};
}
namespace SP {
void KeyVec::push_back(const Key_s005f_5080& v) {
  Key_s005f_5080* p = mpEnd;
  if (p < mpCapacity) {
    mpEnd = p + 1;
    if (p)
      *p = v;
  } else {
    DoInsertValue(p, v);
  }
}
}
// ---- items of slice s005f5080 end

// ---- items of slice s005f4310 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new(unsigned int n, const char* name, int flags, unsigned int debugFlags,
                   const char* file, int line);  // 0x00f473a0
#define PV_s005f_4310(n) virtual void pv##n();
namespace EA {
template <typename T>
class AutoRefCount_s005f_4310 {
 public:
  T* mpObject;
  AutoRefCount_s005f_4310() : mpObject(0) {}
  AutoRefCount_s005f_4310(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  AutoRefCount_s005f_4310(const AutoRefCount_s005f_4310& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount_s005f_4310() { if (mpObject) mpObject->Release(); }
  AutoRefCount_s005f_4310& operator=(T* p) {
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
  AutoRefCount_s005f_4310& operator=(const AutoRefCount_s005f_4310& x) { return operator=(x.mpObject); }
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
}
namespace EA {
template <typename T>
class RefCountTemplate_s005f_4310 {
 public:
  RefCountTemplate_s005f_4310() : mRefCount(0) {}
  virtual ~RefCountTemplate_s005f_4310() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace EA {
template <typename T>
class RefCountVTemplate_s005f_4310 {
 public:
  RefCountVTemplate_s005f_4310() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s005f_4310() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace EA {
namespace COM {
class IUnknown32_s005f_4310 {
 public:
  virtual int AddRef() = 0;
  virtual int Release() = 0;
  virtual void* Cast(uint32_t typeID) const = 0;
};  // namespace COM
}
}
namespace EA {
namespace ResourceMan {
struct Key_s005f_4310 { public:
  unsigned int mInstance, mType, mGroup;
  bool operator==(const Key_s005f_4310& b) const {
    return mInstance == b.mInstance && mType == b.mType && mGroup == b.mGroup;
  }
  Key_s005f_4310() : mInstance(0), mType(0), mGroup(0) {}
  Key_s005f_4310(unsigned int instance, unsigned int type, unsigned int group)
      : mInstance(instance), mType(type), mGroup(group) {}
};
}
}
namespace EA {
namespace ResourceMan {
typedef Key_s005f_4310 Key_s005f_4310;
}
}
namespace EA {
struct Point2D_s005f_4310 {
  float x, y;
  Point2D_s005f_4310() {}
  Point2D_s005f_4310(float ax, float ay) : x(ax), y(ay) {}
  Point2D_s005f_4310(const Point2D_s005f_4310& p) : x(p.x), y(p.y) {}
  Point2D_s005f_4310& operator=(const Point2D_s005f_4310& p) {
    x = p.x;
    y = p.y;
    return *this;
  }
};
}
namespace EA {
class RectT_s005f_4310 { public:
  RectT_s005f_4310() {}
  float left, top, right, bottom;
  RectT_s005f_4310(const RectT_s005f_4310& r) : left(r.left), top(r.top), right(r.right), bottom(r.bottom) {}
  bool Contains(const Point2D_s005f_4310& p) const {
    return p.x >= left && p.y >= top && p.x < right && p.y < bottom;
  }
};
}
namespace EA {
namespace UTFWin {
class IWinProc_s005f_4310;
}
}
namespace EA {
namespace UTFWin {
class IWindow_s005f_4310 : public COM::IUnknown32_s005f_4310 {
 public:
  PV_s005f_4310(3)
  virtual IWindow_s005f_4310* GetParent();                     // +0x10
  PV_s005f_4310(5) PV_s005f_4310(6) PV_s005f_4310(7) PV_s005f_4310(8) PV_s005f_4310(9)
  virtual uint32_t GetFlags();                      // +0x28
  PV_s005f_4310(11) PV_s005f_4310(12)
  virtual const RectT_s005f_4310& GetWindowArea();             // +0x34
  virtual const RectT_s005f_4310& GetRealArea();               // +0x38
  PV_s005f_4310(15) PV_s005f_4310(16) PV_s005f_4310(17) PV_s005f_4310(18) PV_s005f_4310(19) PV_s005f_4310(20) PV_s005f_4310(21) PV_s005f_4310(22)
  virtual void SetShadeColor(uint32_t color);       // +0x5c
  PV_s005f_4310(24) PV_s005f_4310(25) PV_s005f_4310(26)
  virtual void SetArea(const RectT_s005f_4310& area);          // +0x6c
  PV_s005f_4310(28) PV_s005f_4310(29)
  virtual void SetCursorID(uint32_t id);            // +0x78
  virtual void SetFlag(int flag, bool value);       // +0x7c
  virtual void SetCaption(const wchar_t* caption);  // +0x80
  PV_s005f_4310(33) PV_s005f_4310(34) PV_s005f_4310(35) PV_s005f_4310(36) PV_s005f_4310(37) PV_s005f_4310(38) PV_s005f_4310(39) PV_s005f_4310(40) PV_s005f_4310(41)
  virtual int IsAnimationDone();                    // +0xa8
  PV_s005f_4310(43) PV_s005f_4310(44) PV_s005f_4310(45) PV_s005f_4310(46) PV_s005f_4310(47)
  virtual Point2D_s005f_4310 GlobalToLocal(Point2D_s005f_4310 p);         // +0xc0
  PV_s005f_4310(49) PV_s005f_4310(50) PV_s005f_4310(51) PV_s005f_4310(52) PV_s005f_4310(53) PV_s005f_4310(54) PV_s005f_4310(55) PV_s005f_4310(56) PV_s005f_4310(57) PV_s005f_4310(58)
  virtual void AddChild(IWindow_s005f_4310* child);            // +0xec
  PV_s005f_4310(60) PV_s005f_4310(61) PV_s005f_4310(62) PV_s005f_4310(63) PV_s005f_4310(64)
  virtual void AddWinProc(IWinProc_s005f_4310* proc);     // +0x104
  virtual void RemoveWinProc(IWinProc_s005f_4310* proc);  // +0x108
};
}
}
namespace EA {
namespace UTFWin {
class Message_s005f_4310 { public:
  uint32_t pad0[2];
  uint32_t mEventType;                         // +0x8
  union { uint32_t mParam0c; float mX; };      // +0xc
  union { uint32_t mParam10; float mY; };      // +0x10
  uint32_t mModifiers;                         // +0x14
  union { uint32_t mButton; IWindow_s005f_4310* mpWindow; struct cCursorData* mpCursorData; };
};
}
}
namespace EA {
namespace UTFWin {
class IWinProc_s005f_4310 : public COM::IUnknown32_s005f_4310 {
 public:
  virtual void* CastInterface(uint32_t typeID);  // +0xc
  virtual bool DoMessage(IWindow_s005f_4310* window, const Message_s005f_4310& message) = 0;
};
}
}
namespace EA {
namespace Messaging {
class IHandler_s005f_4310 {
 public:
  virtual ~IHandler_s005f_4310() {}
  virtual bool HandleMessage(uint32_t messageID, void* message) = 0;
};
}
}
namespace EA {
namespace Messaging {
class Server_s005f_4310 {
 public:
  PV_s005f_4310(0) PV_s005f_4310(1) PV_s005f_4310(2) PV_s005f_4310(3) PV_s005f_4310(4)
  virtual void MessageSend(uint32_t messageID, void* message, IHandler_s005f_4310* handler);  // +0x14 0x008853b0
  PV_s005f_4310(6) PV_s005f_4310(7) PV_s005f_4310(8)
  virtual void AddHandler(IHandler_s005f_4310* handler, uint32_t messageID);  // +0x24
  PV_s005f_4310(10)
  virtual void RemoveHandler(IHandler_s005f_4310* handler, uint32_t messageID, int priority);  // +0x2c 0x00883aa0
};
}
}
namespace EA {
namespace Messaging {
void RemoveHandler(Server_s005f_4310* server, IHandler_s005f_4310* handler, const uint32_t* ids, uint32_t count,
                   int priority);  // 0x00571db0
}
}
using EA::AutoRefCount_s005f_4310;
using EA::ResourceMan::Key_s005f_4310;
using EA::UTFWin::IWindow_s005f_4310;
using EA::UTFWin::IWinProc_s005f_4310;
using EA::UTFWin::Message_s005f_4310;
namespace SPUIHelpers {
void SetWindowAlpha(IWindow_s005f_4310* window, float alpha);                // 0x00804fc0
}
using EA::Point2D_s005f_4310;
using EA::RectT_s005f_4310;
namespace SW {
class cUIViewport_s005f_4310;
}
namespace SW {
void SizeViewportToWindowAndRemainOnScreen(cUIViewport_s005f_4310* viewport, IWindow_s005f_4310* window, float scale,
                                           float x, float y);  // 0x005f2390
}
namespace SP {
 class cRenderManager_s005f_4310; 
}
class cCollectableItems_s005f_4310;
IWindow_s005f_4310* FUN_00807880(float* key, float x, float y, void* parent);  // 0x00807880
SP::cRenderManager_s005f_4310* AddBoundingBox(IWindow_s005f_4310* window, int a, int b);  // 0x0067cad0
class cSPPaletteItemRef {
 public:
  virtual int AddRef();   // +0x0
  virtual int Release();  // +0x4
};
class cSPPaletteItem_s005f_4310 {
 public:
  virtual int AddRef();                        // vtable pointer at +0x0
  virtual int Release();
  uint32_t pad4;                               // +0x4
  cSPPaletteItemRef mRef;                      // +0x8
  Key_s005f_4310 mKey;                                    // +0xc
  bool IsNew(cCollectableItems_s005f_4310* items) const;  // 0x005c6670
};
namespace EA {
class Stopwatch_s005f_4310 {
 public:
  void SetUnits(int units);  // 0x0093a1a0
  uint32_t pad[6];
};  // namespace EA
}
namespace SP {
class cString_s005f_4310 {
 public:
  cString_s005f_4310();   // 0x006b5060
  ~cString_s005f_4310();  // 0x006b5240
  uint32_t pad[5];
};
}
namespace SP {
EA::Messaging::Server_s005f_4310* MessageServer_s005f_4310();  // 0x0067dcc0
}
namespace SP {
class cSPEditorEconomy_s005f_4310 {
 public:
  PV_s005f_4310(0) PV_s005f_4310(1)
  virtual bool IsItemAvailable(const Key_s005f_4310* key);                   // +0x8
  virtual bool CanAfford(int currency, int cost);                 // +0xc
  virtual int GetItemStatus(const Key_s005f_4310* key, struct cItemCostInfo_s005f_4310* info);  // +0x10
  virtual bool FUN_v5(const Key_s005f_4310* key);                                    // +0x14
};
}
namespace SP {
class cSPPaletteItemRollover_s005f_4310;
}
namespace SP {
struct cSPPaletteInfo_s005f_4310 : public EA::RefCountTemplate_s005f_4310<int> {
  cSPEditorEconomy_s005f_4310* mEconomy;               // +0x8
  void* mTheme;                             // +0xc
  void* mCollectableItems;                  // +0x10
  cSPPaletteItemRollover_s005f_4310* mRollover;        // +0x14
  uint32_t mUnk18;                          // +0x18
  uint32_t mUnk1c;                          // +0x1c
  uint32_t mUnk20;                          // +0x20
  uint32_t mUnk24;                          // +0x24
  uint32_t mUnk28;                          // +0x28
  uint32_t mUnk2c;                          // +0x2c
  bool mUseModelKey;                        // +0x30 (padding byte)
  bool mUseModelKeyForCost;                 // +0x31
};
}
namespace SP {
class cSPPaletteItemRollover_s005f_4310 { public:
  PV_s005f_4310(0) PV_s005f_4310(1) PV_s005f_4310(2) PV_s005f_4310(3) PV_s005f_4310(4) PV_s005f_4310(5) PV_s005f_4310(6) PV_s005f_4310(7) PV_s005f_4310(8) PV_s005f_4310(9)
  virtual void Update(void* layout, const Key_s005f_4310* key, void* info);  // +0x28
  void Hide();                     // 0x005ed6c0
  void FUN_005ed320(int a);        // 0x005ed320
  void FUN_005ee480(void* layout, void* info, void* obj, int a);  // 0x005ee480
  void FUN_008283a0(float x, float y, float ox, float oy);        // 0x008283a0
};
}
namespace SP {
class cSPSwatchManager_s005f_4310 {
 public:
  cSPPaletteItemRollover_s005f_4310* GetSwatchRollover();  // 0x0113ae10
  class cICameraManager_s005f_4310* GetCameraManager();    // 0x01137690
};
}
namespace SP {
cSPSwatchManager_s005f_4310* SwatchManager_s005f_4310();  // 0x00401020
}
namespace SP {
class cICameraController_s005f_4310 {
 public:
  PV_s005f_4310(0) PV_s005f_4310(1) PV_s005f_4310(2) PV_s005f_4310(3) PV_s005f_4310(4) PV_s005f_4310(5) PV_s005f_4310(6) PV_s005f_4310(7) PV_s005f_4310(8)
  virtual void OnMouseEnter(bool inside);                              // +0x24
  virtual bool OnKeyDown(uint32_t key, uint32_t modifiers);            // +0x28
  virtual bool OnKeyUp(uint32_t key, uint32_t modifiers);              // +0x2c
  virtual bool OnMouseDown(uint32_t button, float x, float y, uint32_t modifiers);  // +0x30
  virtual bool OnMouseUp(uint32_t button, float x, float y, uint32_t modifiers);    // +0x34
  virtual bool OnMouseMove(float x, float y, uint32_t modifiers);                   // +0x38
  virtual bool OnMouseWheel(int wheel, float x, float y, uint32_t modifiers);       // +0x3c
};
}
namespace SP {
class cICamera_s005f_4310 {
 public:
  PV_s005f_4310(0) PV_s005f_4310(1) PV_s005f_4310(2)
  virtual cICameraController_s005f_4310* Cast(uint32_t typeID);  // +0xc
};
}
namespace SP {
class cICameraManager_s005f_4310 {
 public:
  PV_s005f_4310(0) PV_s005f_4310(1) PV_s005f_4310(2) PV_s005f_4310(3) PV_s005f_4310(4) PV_s005f_4310(5) PV_s005f_4310(6) PV_s005f_4310(7) PV_s005f_4310(8) PV_s005f_4310(9) PV_s005f_4310(10) PV_s005f_4310(11) PV_s005f_4310(12) PV_s005f_4310(13)
  virtual cICamera_s005f_4310* GetActiveCamera();  // +0x38
};
}
namespace SP {
class IWindowManager_s005f_4310 {
 public:
  PV_s005f_4310(0)
  virtual IWindow_s005f_4310* GetMainWindow();                    // +0x4
  PV_s005f_4310(2) PV_s005f_4310(3) PV_s005f_4310(4) PV_s005f_4310(5) PV_s005f_4310(6) PV_s005f_4310(7) PV_s005f_4310(8) PV_s005f_4310(9) PV_s005f_4310(10) PV_s005f_4310(11) PV_s005f_4310(12) PV_s005f_4310(13) PV_s005f_4310(14)
  virtual void GetMousePosition(Point2D_s005f_4310* out);         // +0x3c
  PV_s005f_4310(16) PV_s005f_4310(17) PV_s005f_4310(18)
  virtual void SetFocus(int which, IWindow_s005f_4310* window);   // +0x4c
  PV_s005f_4310(20)
  virtual IWindow_s005f_4310* GetFocus(int which);                // +0x54
  virtual void SetCapture(int which, IWindow_s005f_4310* window); // +0x58
  virtual void ReleaseCapture(int which, IWindow_s005f_4310* window);  // +0x5c
};
}
namespace SP {
IWindowManager_s005f_4310* WindowManager_s005f_4310();  // 0x0067caa0
}
namespace SP {
class cInputManager_s005f_4310 {
 public:
  bool IsCapturing();                                // 0x006c1100
  void* GetCaptured();                               // 0x006c10e0
  bool SetCapture(IWindow_s005f_4310* window, void* object);    // 0x008045a0
  void Dispose(bool force);                          // 0x00803bd0
};
}
namespace SP {
cInputManager_s005f_4310* InputManager_s005f_4310();  // 0x00804500
}
namespace SP {
class cRenderManager_s005f_4310 {
 public:
  void FUN_0080d710();  // 0x0080d710
};
}
namespace SP {
struct cItemCostInfo_s005f_4310 {
  cItemCostInfo_s005f_4310();  // 0x005a7810
  ~cItemCostInfo_s005f_4310() {}
  cString_s005f_4310 mName;        // +0x0
  cString_s005f_4310 mText;        // +0x14
  uint32_t mColor;      // +0x28
  uint32_t mImageID;    // +0x2c
  uint32_t mCost;       // +0x30
};
}
namespace SP {
class cModelWorld_s005f_4310 {
 public:
  PV_s005f_4310(0) PV_s005f_4310(1) PV_s005f_4310(2) PV_s005f_4310(3) PV_s005f_4310(4) PV_s005f_4310(5) PV_s005f_4310(6) PV_s005f_4310(7) PV_s005f_4310(8) PV_s005f_4310(9) PV_s005f_4310(10) PV_s005f_4310(11) PV_s005f_4310(12) PV_s005f_4310(13) PV_s005f_4310(14)
  PV_s005f_4310(15) PV_s005f_4310(16) PV_s005f_4310(17) PV_s005f_4310(18) PV_s005f_4310(19) PV_s005f_4310(20) PV_s005f_4310(21) PV_s005f_4310(22) PV_s005f_4310(23) PV_s005f_4310(24)
  virtual int GetEffectCount(struct cMWModel_s005f_4310* model);  // +0x64
  PV_s005f_4310(26) PV_s005f_4310(27)
  virtual void StartEffect(cMWModel_s005f_4310* model, uint32_t effectID, int a, float b, int index);  // +0x70
  PV_s005f_4310(29) PV_s005f_4310(30) PV_s005f_4310(31) PV_s005f_4310(32) PV_s005f_4310(33) PV_s005f_4310(34) PV_s005f_4310(35) PV_s005f_4310(36) PV_s005f_4310(37) PV_s005f_4310(38) PV_s005f_4310(39) PV_s005f_4310(40) PV_s005f_4310(41) PV_s005f_4310(42)
  PV_s005f_4310(43) PV_s005f_4310(44) PV_s005f_4310(45) PV_s005f_4310(46) PV_s005f_4310(47) PV_s005f_4310(48) PV_s005f_4310(49) PV_s005f_4310(50) PV_s005f_4310(51) PV_s005f_4310(52) PV_s005f_4310(53) PV_s005f_4310(54) PV_s005f_4310(55) PV_s005f_4310(56)
  PV_s005f_4310(57) PV_s005f_4310(58) PV_s005f_4310(59) PV_s005f_4310(60) PV_s005f_4310(61) PV_s005f_4310(62) PV_s005f_4310(63) PV_s005f_4310(64) PV_s005f_4310(65) PV_s005f_4310(66) PV_s005f_4310(67) PV_s005f_4310(68) PV_s005f_4310(69) PV_s005f_4310(70)
  PV_s005f_4310(71) PV_s005f_4310(72) PV_s005f_4310(73) PV_s005f_4310(74) PV_s005f_4310(75) PV_s005f_4310(76) PV_s005f_4310(77) PV_s005f_4310(78) PV_s005f_4310(79) PV_s005f_4310(80) PV_s005f_4310(81) PV_s005f_4310(82) PV_s005f_4310(83) PV_s005f_4310(84)
  PV_s005f_4310(85) PV_s005f_4310(86) PV_s005f_4310(87) PV_s005f_4310(88) PV_s005f_4310(89) PV_s005f_4310(90) PV_s005f_4310(91)
  virtual void DestroyModel(struct cMWModel_s005f_4310* model, bool immediate);  // +0x170
};
}
namespace SP {
struct cMWModel_s005f_4310 { private:
 public:
  cModelWorld_s005f_4310* mpWorld;  // +0x0
  uint32_t mFlags;       // +0x4
  uint32_t pad8[14];
  int mRefCount;         // +0x40
  void AddRef() { mRefCount++; }
  void Release();
};
}
namespace SP {
class cImageLayers_s005f_4310 {
 public:
  PV_s005f_4310(0) PV_s005f_4310(1)
  virtual uint32_t AddLayer(uint32_t imageID, int flags);  // +0x8
  virtual void SetLayerVisible(uint32_t layer, bool on);   // +0xc
  virtual void SetLayerScaled(uint32_t layer, bool on);    // +0x10
  PV_s005f_4310(5)
  virtual void Refresh(uint32_t layer);                    // +0x18
  PV_s005f_4310(7)
  virtual void SetLayerTiled(uint32_t layer, bool on);     // +0x20
  virtual void SetLayerAlpha(uint32_t layer, float alpha); // +0x24
  uint32_t pad4[0x18];
  bool mVisible;  // +0x64
};
}
namespace SP {
class cUILayeredObject_s005f_4310 {
 public:
  void SetVisible(bool visible);   // 0x0080d7c0
  void RemoveModel(void* model);   // 0x0080e980
  SW::cUIViewport_s005f_4310* FUN_0093b6c0(); // 0x0093b6c0
};
}
namespace SP {
class cSwatchTexture_s005f_4310 {
 public:
  void* GetTexture();                                            // 0x0080d610
  SW::cUIViewport_s005f_4310* FUN_0080d5f0();                               // 0x0080d5f0
};
}
namespace SP {
class cSwatchRenderer_s005f_4310 {
 public:
  PV_s005f_4310(0) PV_s005f_4310(1) PV_s005f_4310(2) PV_s005f_4310(3) PV_s005f_4310(4) PV_s005f_4310(5) PV_s005f_4310(6) PV_s005f_4310(7) PV_s005f_4310(8) PV_s005f_4310(9) PV_s005f_4310(10) PV_s005f_4310(11) PV_s005f_4310(12) PV_s005f_4310(13) PV_s005f_4310(14)
  PV_s005f_4310(15) PV_s005f_4310(16) PV_s005f_4310(17) PV_s005f_4310(18) PV_s005f_4310(19) PV_s005f_4310(20) PV_s005f_4310(21) PV_s005f_4310(22) PV_s005f_4310(23) PV_s005f_4310(24) PV_s005f_4310(25) PV_s005f_4310(26) PV_s005f_4310(27) PV_s005f_4310(28)
  PV_s005f_4310(29) PV_s005f_4310(30) PV_s005f_4310(31) PV_s005f_4310(32) PV_s005f_4310(33)
  virtual void SetTexture(void* texture);  // +0x88
};
}
namespace SP {
class cSwatch3DView_s005f_4310 { public:
  bool mVisible;                                            // +0x00
  cUILayeredObject_s005f_4310* mLayeredObject;                         // +0x04
  eastl::vector<AutoRefCount_s005f_4310<cMWModel_s005f_4310> > mModels;           // +0x08
  uint32_t pad14;                                           // +0x14
  uint32_t pad18[3];
  cSwatchRenderer_s005f_4310* mRenderer;                               // +0x24
  uint32_t pad28;
  cSwatchTexture_s005f_4310* mTexture;                                 // +0x2c
  void RemoveModel(cMWModel_s005f_4310* model);                        // 0x005f4eb0
};
}
namespace SP {
class cSPSwatch_s005f_4310 : public IWinProc_s005f_4310, public EA::RefCountVTemplate_s005f_4310<int>, public EA::Messaging::IHandler_s005f_4310 {
 public:
  virtual int AddRef();
  virtual int Release();
  virtual void* Cast(uint32_t typeID) const;
  virtual void* CastInterface(uint32_t typeID);
  virtual bool DoMessage(IWindow_s005f_4310* window, const Message_s005f_4310& message);
  PV_s005f_4310(5) PV_s005f_4310(6) PV_s005f_4310(7) PV_s005f_4310(8)
  virtual void Vt24(void* key);                   // +0x24
  PV_s005f_4310(10) PV_s005f_4310(11) PV_s005f_4310(12)
  virtual IWindow_s005f_4310* GetWindow();                   // +0x34
  PV_s005f_4310(14) PV_s005f_4310(15)
  virtual void OnMouseDown();                     // +0x40
  virtual bool IsDragging();                      // +0x44
  virtual void OnMouseEnter();                    // +0x48
  virtual void OnMouseLeave();                    // +0x4c
  virtual void OnClick();                         // +0x50
  PV_s005f_4310(21)
  virtual float GetTargetZoom();                  // +0x58
  PV_s005f_4310(23) PV_s005f_4310(24)
  virtual void ReloadModel();                     // +0x64
  virtual bool HandleMessage(uint32_t messageID, void* message);

  bool IsCapturedBySelf() {
    cInputManager_s005f_4310* input = InputManager_s005f_4310();
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

  void Init(Key_s005f_4310* key, uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t scale);   // 0x005f4f80
  void Init(Key_s005f_4310* key, void* a, void* b, uint32_t c, uint32_t d, uint32_t e, uint32_t f, uint32_t scale);  // 0x005f5000
  void InitInternal(IWindow_s005f_4310* base, IWindow_s005f_4310* modelWindow, uint32_t a3, uint32_t a4,
                    uint32_t b5, uint32_t b6, uint32_t a7, uint32_t a8);  // 0x005f3b20

  cSwatch3DView_s005f_4310 m3DView;                  // +0x10
  Key_s005f_4310 mOriginalItemKey;                   // +0x40
  Key_s005f_4310 mModelKey;                          // +0x4c
  uint32_t mScaleParam;                   // +0x58
  AutoRefCount_s005f_4310<IWindow_s005f_4310> mBaseWindow;      // +0x5c
  AutoRefCount_s005f_4310<IWindow_s005f_4310> mModelWindow;     // +0x60
  float mActualViewportScale;             // +0x64
  float mActualAngle;                     // +0x68
  float mTargetAngle;                     // +0x6c
  float mTargetViewportScale;             // +0x70
  RectT_s005f_4310 mOriginalWindowArea;              // +0x74
  Point2D_s005f_4310 mActualViewportCenter;          // +0x84
  Point2D_s005f_4310 mTargetViewportCenter;          // +0x8c
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
  cImageLayers_s005f_4310* mpImageLayers;            // +0xf0
  uint32_t padf4;
  uint32_t mImageID;                      // +0xf8
  bool mImageOverlay;                     // +0xfc
  bool mImageSet;                         // +0xfd
  uint32_t mInterfaceID;                  // +0x100
  uint32_t pad104[5];
  AutoRefCount_s005f_4310<cMWModel_s005f_4310> mModel;          // +0x118
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
}
namespace SP {
inline void cMWModel_s005f_4310::Release() {
  if (mRefCount > 1)
    mRefCount--;
  else
    mpWorld->DestroyModel(this, (mFlags >> 31) & 1);
}
}
namespace SP {
struct cSwatchMessage_s005f_4310 {
  cSPSwatch_s005f_4310* mpSwatch;  // +0x0
  uint32_t pad4;
  uint32_t mID;         // +0x8
  uint32_t padc;
};
}
namespace SP {
class cSPPaletteSwatch_s005f_4310 : public cSPSwatch_s005f_4310 {
 public:
  bool IsMouseOutside();
  bool IsItemAvailable();
  void UpdateCostDisplay();     // 0x005f3400
  void UpdateCursor();          // 0x005f3600
  void OnRolloverEnd();
  void SetShowCost(bool show);      // 0x005f49a0
  void EndDrag();                   // 0x005f46c0

  AutoRefCount_s005f_4310<cSPPaletteInfo_s005f_4310> mInfo;      // +0x17c
  AutoRefCount_s005f_4310<cSPPaletteItem_s005f_4310> mPaletteItem;  // +0x180
  bool mIsLocked;                          // +0x184
  float mBaseScale;                        // +0x188
  AutoRefCount_s005f_4310<IWindow_s005f_4310> mDragWindow;       // +0x18c
  uint32_t mUnk190;                        // +0x190
  AutoRefCount_s005f_4310<IWindow_s005f_4310> mCostWindow;       // +0x194
  bool mShowCost;                         // +0x198
  bool mDraggable;                        // +0x199
};
}
namespace SP {
class cSPEditorVehicleAbilities {
 public:
  cSPEditorVehicleAbilities(const Key_s005f_4310& key, uint32_t a, uint32_t b, uint32_t c, bool d);
  virtual void FUN_0059f060();  // +0x0
  virtual void FUN_0059f064();  // +0x4
  virtual void FUN_0059f068();  // +0x8
};
}
namespace SP {
namespace Audio {
class ISystemAT {
 public:
  PV_s005f_4310(0) PV_s005f_4310(1) PV_s005f_4310(2) PV_s005f_4310(3) PV_s005f_4310(4) PV_s005f_4310(5) PV_s005f_4310(6) PV_s005f_4310(7)
  virtual int FUN_00a206f0();  // +0x20
};
}
}
namespace SP {
namespace Audio {
ISystemAT* GetSystemAT();  // 0x00a206f0
}
}
namespace SP {
struct cSPPaletteDragMessage {
  uint32_t mUnk0;              // +0x00 (0x013f7e34)
  uint32_t mUnk4;              // +0x04 (0x013f7e30)
  uint32_t mUnk8;              // +0x08
  uint32_t mUnkC;              // +0x0c
  uint32_t mUnk10;             // +0x10
  Key_s005f_4310 mModelKey;               // +0x14
  cSPPaletteItemRef* mpRef;    // +0x20
  cSPPaletteItemRef* mpUnk24;  // +0x24
};
}
namespace SP {
class cSPOLDPaletteItemUIDragAndBuy_s005f_4310 : public cSPPaletteSwatch_s005f_4310 {
 public:
  void Init(Key_s005f_4310* key, void* a, void* b, uint32_t c, void* d, void* e, bool f);  // 005f4310 0x005f4310
  void OnLeftMouseDown();   // 005f4750
  void OnMouseDown();       // 005f49f0
  void OnMouseUp();         // 005f4b80

  uint32_t pad19c;                  // +0x19c
  EA::Stopwatch_s005f_4310 mStopwatch;         // +0x1a0
  AutoRefCount_s005f_4310<IWindow_s005f_4310> mLeftText;  // +0x1b8
  AutoRefCount_s005f_4310<IWindow_s005f_4310> mRightText; // +0x1bc
  Point2D_s005f_4310 mOriginalMousePosition;   // +0x1c0
};
}
namespace SP {
class cHandlerView {
 public:
  bool HandleMessage(uint32_t id, void* msg);  // 0x005f46f0
};
}
namespace SP {
struct Blob38 {
  unsigned short mFlags;             // +0x00
  unsigned short mModificationCount; // +0x02
  float mTranslation[3];             // +0x04
  float mScale;                      // +0x10
  float mRotation[9];                // +0x14
  Blob38& operator=(const Blob38& o);
};
}
namespace SP {
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
}
// ---- items of slice s005f4310 end

// ---- items of slice s005f5f20 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
void FUN_0080dda0(void* a, int b);   // 0x0080dda0
}
namespace SP {
void FUN_0080dfc0(void* a);          // 0x0080dfc0
}
#define PV_s005f_5f20(n) virtual void pv##n();
namespace EA {
template <typename T>
class AutoRefCount_s005f_5f20 {
 public:
  T* mpObject;
  AutoRefCount_s005f_5f20() : mpObject(0) {}
  AutoRefCount_s005f_5f20(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  AutoRefCount_s005f_5f20(const AutoRefCount_s005f_5f20& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount_s005f_5f20() { if (mpObject) mpObject->Release(); }
  AutoRefCount_s005f_5f20& operator=(T* p) {
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
  AutoRefCount_s005f_5f20& operator=(const AutoRefCount_s005f_5f20& x) { return operator=(x.mpObject); }
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
}
namespace EA {
template <typename T>
class RefCountVTemplate_s005f_5f20 {
 public:
  RefCountVTemplate_s005f_5f20() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s005f_5f20() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace EA {
namespace COM {
class IUnknown32_s005f_5f20 {
 public:
  virtual int AddRef() = 0;
  virtual int Release() = 0;
  virtual void* Cast(uint32_t typeID) const = 0;
};  // namespace COM
}
}
namespace EA {
namespace ResourceMan {
class Key_s005f_5f20 { public:
  unsigned int mInstance, mType, mGroup;
  bool operator==(const Key_s005f_5f20& b) const {
    return mInstance == b.mInstance && mType == b.mType && mGroup == b.mGroup;
  }
  Key_s005f_5f20() : mInstance(0), mType(0), mGroup(0) {}
  Key_s005f_5f20(unsigned int instance, unsigned int type, unsigned int group)
      : mInstance(instance), mType(type), mGroup(group) {}
};  // namespace ResourceMan
}
}
namespace EA {
struct Point2D_s005f_5f20 {
  float x, y;
  Point2D_s005f_5f20() {}
  Point2D_s005f_5f20(float ax, float ay) : x(ax), y(ay) {}
  Point2D_s005f_5f20(const Point2D_s005f_5f20& p) : x(p.x), y(p.y) {}
  Point2D_s005f_5f20& operator=(const Point2D_s005f_5f20& p) {
    x = p.x;
    y = p.y;
    return *this;
  }
};
}
namespace EA {
class RectT_s005f_5f20 { public:
  RectT_s005f_5f20() {}
  float left, top, right, bottom;
  RectT_s005f_5f20(const RectT_s005f_5f20& r) : left(r.left), top(r.top), right(r.right), bottom(r.bottom) {}
  bool Contains(const Point2D_s005f_5f20& p) const {
    return p.x >= left && p.y >= top && p.x < right && p.y < bottom;
  }
};
}
namespace EA {
namespace UTFWin {
class IWinProc_s005f_5f20;
}
}
namespace EA {
namespace UTFWin {
class IWindow_s005f_5f20 : public COM::IUnknown32_s005f_5f20 {
 public:
  PV_s005f_5f20(3)
  virtual IWindow_s005f_5f20* GetParent();                     // +0x10
  PV_s005f_5f20(5) PV_s005f_5f20(6) PV_s005f_5f20(7) PV_s005f_5f20(8) PV_s005f_5f20(9)
  virtual uint32_t GetFlags();                      // +0x28
  PV_s005f_5f20(11) PV_s005f_5f20(12) PV_s005f_5f20(13)
  virtual const RectT_s005f_5f20& GetRealArea();               // +0x38
  PV_s005f_5f20(15) PV_s005f_5f20(16) PV_s005f_5f20(17) PV_s005f_5f20(18) PV_s005f_5f20(19) PV_s005f_5f20(20) PV_s005f_5f20(21) PV_s005f_5f20(22)
  virtual void SetShadeColor(uint32_t color);       // +0x5c
  PV_s005f_5f20(24) PV_s005f_5f20(25) PV_s005f_5f20(26)
  virtual void SetArea(const RectT_s005f_5f20& area);          // +0x6c
  PV_s005f_5f20(28) PV_s005f_5f20(29)
  virtual void SetCursorID(uint32_t id);            // +0x78
  virtual void SetFlag(int flag, bool value);       // +0x7c
  virtual void SetCaption(const wchar_t* caption);  // +0x80
  PV_s005f_5f20(33) PV_s005f_5f20(34) PV_s005f_5f20(35) PV_s005f_5f20(36) PV_s005f_5f20(37) PV_s005f_5f20(38) PV_s005f_5f20(39) PV_s005f_5f20(40) PV_s005f_5f20(41)
  virtual int IsAnimationDone();                    // +0xa8
  PV_s005f_5f20(43) PV_s005f_5f20(44) PV_s005f_5f20(45) PV_s005f_5f20(46) PV_s005f_5f20(47)
  virtual Point2D_s005f_5f20 GlobalToLocal(Point2D_s005f_5f20 p);         // +0xc0
  PV_s005f_5f20(49) PV_s005f_5f20(50) PV_s005f_5f20(51) PV_s005f_5f20(52) PV_s005f_5f20(53) PV_s005f_5f20(54) PV_s005f_5f20(55) PV_s005f_5f20(56) PV_s005f_5f20(57) PV_s005f_5f20(58)
  PV_s005f_5f20(59) PV_s005f_5f20(60) PV_s005f_5f20(61) PV_s005f_5f20(62) PV_s005f_5f20(63) PV_s005f_5f20(64)
  virtual void AddWinProc(IWinProc_s005f_5f20* proc);     // +0x104
  virtual void RemoveWinProc(IWinProc_s005f_5f20* proc);  // +0x108
};
}
}
namespace EA {
namespace UTFWin {
class Message_s005f_5f20 { public:
  uint32_t pad0[2];
  uint32_t mEventType;                         // +0x8
  union { uint32_t mParam0c; float mX; };      // +0xc
  union { uint32_t mParam10; float mY; };      // +0x10
  uint32_t mModifiers;                         // +0x14
  union { uint32_t mButton; IWindow_s005f_5f20* mpWindow; struct cCursorData* mpCursorData; };
};
}
}
namespace EA {
namespace UTFWin {
class IWinProc_s005f_5f20 : public COM::IUnknown32_s005f_5f20 {
 public:
  virtual void* CastInterface(uint32_t typeID);  // +0xc
  virtual bool DoMessage(IWindow_s005f_5f20* window, const Message_s005f_5f20& message) = 0;
};
}
}
namespace EA {
namespace Messaging {
class IHandler_s005f_5f20 {
 public:
  virtual ~IHandler_s005f_5f20() {}
  virtual bool HandleMessage(uint32_t messageID, void* message) = 0;
};
}
}
using EA::AutoRefCount_s005f_5f20;
using EA::ResourceMan::Key_s005f_5f20;
using EA::UTFWin::IWindow_s005f_5f20;
using EA::UTFWin::IWinProc_s005f_5f20;
using EA::UTFWin::Message_s005f_5f20;
namespace SPUIHelpers {
void SetWindowImage(IWindow_s005f_5f20* window, const Key_s005f_5f20* key, int index);  // 0x00807bb0
}
using EA::Point2D_s005f_5f20;
using EA::RectT_s005f_5f20;
namespace SP {
class cSPSwatchManager_s005f_5f20 {
 public:
  cSPPaletteItemRollover* GetSwatchRollover();  // 0x0113ae10
  class cICameraManager* GetCameraManager();    // 0x01137690
};
}
namespace SP {
class cInputManager_s005f_5f20 {
 public:
  bool IsCapturing();                                // 0x006c1100
  void* GetCaptured();                               // 0x006c10e0
  bool SetCapture(IWindow_s005f_5f20* window, void* object);    // 0x008045a0
};
}
namespace SP {
cInputManager_s005f_5f20* InputManager_s005f_5f20();  // 0x00804500
}
namespace SP {
class cModelWorld_s005f_5f20 {
 public:
  PV_s005f_5f20(0) PV_s005f_5f20(1) PV_s005f_5f20(2) PV_s005f_5f20(3) PV_s005f_5f20(4) PV_s005f_5f20(5) PV_s005f_5f20(6) PV_s005f_5f20(7) PV_s005f_5f20(8) PV_s005f_5f20(9) PV_s005f_5f20(10) PV_s005f_5f20(11) PV_s005f_5f20(12) PV_s005f_5f20(13) PV_s005f_5f20(14)
  PV_s005f_5f20(15) PV_s005f_5f20(16) PV_s005f_5f20(17) PV_s005f_5f20(18) PV_s005f_5f20(19) PV_s005f_5f20(20) PV_s005f_5f20(21) PV_s005f_5f20(22) PV_s005f_5f20(23) PV_s005f_5f20(24)
  virtual int GetEffectCount(struct cMWModel_s005f_5f20* model);  // +0x64
  PV_s005f_5f20(26) PV_s005f_5f20(27)
  virtual void StartEffect(cMWModel_s005f_5f20* model, uint32_t effectID, int a, float b, int index);  // +0x70
  PV_s005f_5f20(29) PV_s005f_5f20(30) PV_s005f_5f20(31) PV_s005f_5f20(32) PV_s005f_5f20(33) PV_s005f_5f20(34) PV_s005f_5f20(35) PV_s005f_5f20(36) PV_s005f_5f20(37) PV_s005f_5f20(38) PV_s005f_5f20(39) PV_s005f_5f20(40) PV_s005f_5f20(41) PV_s005f_5f20(42)
  PV_s005f_5f20(43) PV_s005f_5f20(44) PV_s005f_5f20(45) PV_s005f_5f20(46) PV_s005f_5f20(47) PV_s005f_5f20(48) PV_s005f_5f20(49) PV_s005f_5f20(50) PV_s005f_5f20(51) PV_s005f_5f20(52) PV_s005f_5f20(53) PV_s005f_5f20(54) PV_s005f_5f20(55) PV_s005f_5f20(56)
  PV_s005f_5f20(57) PV_s005f_5f20(58) PV_s005f_5f20(59) PV_s005f_5f20(60) PV_s005f_5f20(61) PV_s005f_5f20(62) PV_s005f_5f20(63) PV_s005f_5f20(64) PV_s005f_5f20(65) PV_s005f_5f20(66) PV_s005f_5f20(67) PV_s005f_5f20(68) PV_s005f_5f20(69) PV_s005f_5f20(70)
  PV_s005f_5f20(71) PV_s005f_5f20(72) PV_s005f_5f20(73) PV_s005f_5f20(74) PV_s005f_5f20(75) PV_s005f_5f20(76) PV_s005f_5f20(77) PV_s005f_5f20(78) PV_s005f_5f20(79) PV_s005f_5f20(80) PV_s005f_5f20(81) PV_s005f_5f20(82) PV_s005f_5f20(83) PV_s005f_5f20(84)
  PV_s005f_5f20(85) PV_s005f_5f20(86) PV_s005f_5f20(87) PV_s005f_5f20(88) PV_s005f_5f20(89) PV_s005f_5f20(90) PV_s005f_5f20(91)
  virtual void DestroyModel(struct cMWModel_s005f_5f20* model, bool immediate);  // +0x170
};
}
namespace SP {
struct cMWModel_s005f_5f20 { private:
 public:
  cModelWorld_s005f_5f20* mpWorld;  // +0x0
  uint32_t mFlags;       // +0x4
  uint32_t pad8[14];
  int mRefCount;         // +0x40
  void AddRef() { mRefCount++; }
  void Release();
};
}
namespace SP {
class cImageLayers_s005f_5f20 {
 public:
  PV_s005f_5f20(0) PV_s005f_5f20(1)
  virtual uint32_t AddLayer(uint32_t imageID, int flags);  // +0x8
  virtual void SetLayerVisible(uint32_t layer, bool on);   // +0xc
  virtual void SetLayerScaled(uint32_t layer, bool on);    // +0x10
  PV_s005f_5f20(5)
  virtual void Refresh(uint32_t layer);                    // +0x18
  PV_s005f_5f20(7)
  virtual void SetLayerTiled(uint32_t layer, bool on);     // +0x20
  virtual void SetLayerAlpha(uint32_t layer, float alpha); // +0x24
  uint32_t pad4[0x18];
  bool mVisible;  // +0x64
};
}
namespace SP {
class cUILayeredObject_s005f_5f20 {
 public:
  void SetVisible(bool visible);   // 0x0080d7c0
  void RemoveModel(void* model);   // 0x0080e980
  void FUN_0080dda0(int a, int b); // 0x0080dda0 (thiscall, ret 8)
};
}
namespace SP {
class cSwatchTexture_s005f_5f20 {
 public:
  void* GetTexture();              // 0x0080d610
  void FUN_0080dfc0();             // 0x0080dfc0 (thiscall, no args)
  void FUN_0080df80();             // 0x0080df80 (thiscall, no args)
};
}
namespace SP {
class cBoundingBoxList {
 public:
  void FUN_0080f7c0(void* a);      // 0x0080f7c0 (thiscall, ret 4)
};
}
namespace SP {
namespace eastl {
template <typename T>
class vector_s005f_5f20 {
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
  ~vector_s005f_5f20() {
    DoDestroyValues(mpBegin, mpEnd);
    if (mpBegin && ((int*)mpBegin)[-1] != 0)
      do_deallocate(mpBegin);
  }
  void do_deallocate(T* p);
};  // namespace eastl
}
}
namespace SP {
class cSwatchRenderer_s005f_5f20 {
 public:
  PV_s005f_5f20(0) PV_s005f_5f20(1) PV_s005f_5f20(2) PV_s005f_5f20(3) PV_s005f_5f20(4) PV_s005f_5f20(5) PV_s005f_5f20(6) PV_s005f_5f20(7) PV_s005f_5f20(8) PV_s005f_5f20(9) PV_s005f_5f20(10) PV_s005f_5f20(11) PV_s005f_5f20(12) PV_s005f_5f20(13) PV_s005f_5f20(14)
  PV_s005f_5f20(15) PV_s005f_5f20(16) PV_s005f_5f20(17) PV_s005f_5f20(18) PV_s005f_5f20(19) PV_s005f_5f20(20) PV_s005f_5f20(21) PV_s005f_5f20(22) PV_s005f_5f20(23) PV_s005f_5f20(24) PV_s005f_5f20(25) PV_s005f_5f20(26) PV_s005f_5f20(27) PV_s005f_5f20(28)
  PV_s005f_5f20(29) PV_s005f_5f20(30) PV_s005f_5f20(31) PV_s005f_5f20(32) PV_s005f_5f20(33)
  virtual void SetTexture(void* texture);  // +0x88
};
}
namespace SP {
class cSwatch3DView_s005f_5f20 { public:
  bool mVisible;                                            // +0x00
  cUILayeredObject_s005f_5f20* mLayeredObject;                         // +0x04
  eastl::vector_s005f_5f20<AutoRefCount_s005f_5f20<cMWModel_s005f_5f20> > mModels;           // +0x08
  uint32_t pad14;                                           // +0x14
  uint32_t pad18;                                           // +0x18
  void* mAnimWorld;                                         // +0x1c
  IWindow_s005f_5f20* mWindow;                                         // +0x20
  cSwatchRenderer_s005f_5f20* mRenderer;                               // +0x24
  void* mCamera;                                            // +0x28
  cSwatchTexture_s005f_5f20* mTexture;                                 // +0x2c
  void RemoveModel(cMWModel_s005f_5f20* model);                        // 0x005f4eb0
  cMWModel_s005f_5f20* AddModel(uint32_t imageID, int flags);          // 0x005f59b0
  void RemoveAllModels();                                   // 0x005f5aa0
  void Shutdown();                                          // 0x005f67d0
  ~cSwatch3DView_s005f_5f20();                                         // 0x005f6b40
};
}
namespace SP {
class cSPSwatch_s005f_5f20 : public IWinProc_s005f_5f20, public EA::RefCountVTemplate_s005f_5f20<int>, public EA::Messaging::IHandler_s005f_5f20 {
 public:
  virtual int AddRef();
  virtual int Release();
  virtual void* Cast(uint32_t typeID) const;
  virtual void* CastInterface(uint32_t typeID);
  virtual bool DoMessage(IWindow_s005f_5f20* window, const Message_s005f_5f20& message);
  PV_s005f_5f20(5) PV_s005f_5f20(6) PV_s005f_5f20(7) PV_s005f_5f20(8)
  virtual void Vt24(void* key);                   // +0x24
  PV_s005f_5f20(10) PV_s005f_5f20(11) PV_s005f_5f20(12)
  virtual IWindow_s005f_5f20* GetWindow();                   // +0x34
  PV_s005f_5f20(14) PV_s005f_5f20(15)
  virtual void OnMouseDown();                     // +0x40
  virtual bool IsDragging();                      // +0x44
  virtual void OnMouseEnter();                    // +0x48
  virtual void OnMouseLeave();                    // +0x4c
  virtual void OnClick();                         // +0x50
  PV_s005f_5f20(21)
  virtual float GetTargetZoom();                  // +0x58
  PV_s005f_5f20(23) PV_s005f_5f20(24)
  virtual void ReloadModel();                     // +0x64
  virtual bool HandleMessage(uint32_t messageID, void* message);

  bool IsCapturedBySelf() {
    cInputManager_s005f_5f20* input = InputManager_s005f_5f20();
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
  void UpdateSwatchPosition(uint32_t deltaTime);  // 0x005f2bf0 (SP::cSPSwatch::UpdateSwatchPosition)
  uint32_t SetImage(uint32_t imageID, bool overlay);
  void Show3DModel();  // 0x005f2e00 (SP::cSPSwatch::Show3DModel)
  void Hide3DModel();  // 0x005f2eb0 (SP::cSPSwatch::Hide3DModel)
  void StartModelEffects();
  bool IsAnimating();
  bool TakeCapture();
  void EndInteraction();  // 0x005f3040 (SP::cSPSwatch::EndInteraction)
  bool HasCapture();
  int IsBusy();
  void UpdateViewport(uint32_t deltaTime);

  void Init(Key_s005f_5f20* key, uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t scale);   // 0x005f4f80
  void Init(Key_s005f_5f20* key, void* a, void* b, uint32_t c, uint32_t d, uint32_t e, uint32_t f, uint32_t scale);  // 0x005f5000
  cSPSwatch_s005f_5f20();                            // 0x005f6bd0
  void InitInternal(IWindow_s005f_5f20* base, IWindow_s005f_5f20* modelWindow, uint32_t a3, uint32_t a4,
                    uint32_t b5, uint32_t b6, uint32_t a7, uint32_t a8);  // 0x005f3b20
  void InitAdditionalModels();            // 0x005f6090
  void SetEditorCameraController(bool enable);  // 0x005f6500
  void SetModel(Key_s005f_5f20* key);                // 0x005f5f20
  void LoadModel(Key_s005f_5f20& key);               // 0x005f5b40
  void InitStaticEffects();               // 0x005f6260
  void OnModelLoad();                     // 0x005f69a0
  void ShutDownModel();                   // 0x005f5df0
  void Shutdown();                        // 0x005f68a0

  cSwatch3DView_s005f_5f20 m3DView;                  // +0x10
  Key_s005f_5f20 mOriginalItemKey;                   // +0x40
  Key_s005f_5f20 mModelKey;                          // +0x4c
  uint32_t mScaleParam;                   // +0x58
  AutoRefCount_s005f_5f20<IWindow_s005f_5f20> mBaseWindow;      // +0x5c
  AutoRefCount_s005f_5f20<IWindow_s005f_5f20> mModelWindow;     // +0x60
  float mActualViewportScale;             // +0x64
  float mActualAngle;                     // +0x68
  float mTargetAngle;                     // +0x6c
  float mTargetViewportScale;             // +0x70
  RectT_s005f_5f20 mOriginalWindowArea;              // +0x74
  Point2D_s005f_5f20 mActualViewportCenter;          // +0x84
  Point2D_s005f_5f20 mTargetViewportCenter;          // +0x8c
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
  cImageLayers_s005f_5f20* mpImageLayers;            // +0xf0
  uint32_t padf4;
  uint32_t mImageID;                      // +0xf8
  bool mImageOverlay;                     // +0xfc
  bool mImageSet;                         // +0xfd
  uint32_t pad100[6];
  AutoRefCount_s005f_5f20<cMWModel_s005f_5f20> mModel;          // +0x118
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
}
namespace SP {
inline void cMWModel_s005f_5f20::Release() {
  if (mRefCount > 1)
    mRefCount--;
  else
    mpWorld->DestroyModel(this, (mFlags >> 31) & 1);
}
}
namespace SP {
void FUN_0080df80(void* a);          // 0x0080df80 (free-form declaration used by the destructor)
}
namespace SP {
void FUN_005f0320();                 // 0x005f0320
}
namespace SP {
cBoundingBoxList* cSPBoundingBox_AddBoundingBox2();          // 0x0067cad0 (no-arg getter)
}
namespace SP {
cBoundingBoxList* cSPBoundingBox_AddBoundingBox2(void* a);   // 0x0067cad0 (same getter, argument ignored)
}
namespace SP {
bool  FUN_00401d90(const void* a);                          // 0x00401d90
}
namespace SP {
void* FUN_00401010();                                       // 0x00401010
}
namespace SP {
void* ResourceManGetManager();                              // 0x0067dcd0
}
namespace SP {
void  SetWindowAlpha(IWindow_s005f_5f20* w, float a);                  // 0x00804fc0
}
namespace SP {
uint32_t GetThumbnailCameraID(uint32_t a, uint32_t b);      // 0x005f36d0
}
namespace SP {
bool  GetPropertyAsVector3(void* list, uint32_t id, void* out);   // 0x006a1110
}
namespace SP {
void* Matrix33FromEulerXYZ(void* out, const void* euler);   // 0x00453920
}
namespace SP {
void  GetPropertyAsTransformArray(void* list, uint32_t id, void* a, void* b);  // 0x006a0c30
}
namespace SP {
void  FUN_006a0ae0(void* a, uint32_t b, void* c, void* d);  // 0x006a0ae0
}
namespace SP {
void  GetPropertyAsKeyInstance(void* list, uint32_t id, void* out);  // 0x006a12a0
}
namespace SP {
bool  GetPropertyAsKey(void* list, uint32_t id, void* out); // 0x006a1250
}
namespace SP {
void* GetPropertyT_int(void* list, uint32_t id, void* out); // 0x0040cf10
}
namespace SP {
bool  GetBoolProperty(void* list, uint32_t id, void* out);  // 0x00407190
}
namespace SP {
void* FUN_0093b6c0(void* a);                                // 0x0093b6c0
}
namespace SP {
void* FUN_0080d5f0(void* a);                                // 0x0080d5f0
}
namespace SP {
void* FUN_0080db90(void* a);                                // 0x0080db90
}
namespace SP {
void* FUN_0080dc50(void* a);                                // 0x0080dc50
}
namespace SP {
void* FUN_01137690(void* mgr);                              // 0x01137690
}
namespace SP {
void  FUN_010171e0(void* a, float f);                       // 0x010171e0
}
namespace SP {
void  FUN_005a2370(void* a);                                // 0x005a2370
}
namespace SP {
void* FUN_005a2000(void* a, bool b);                        // 0x005a2000
}
namespace SP {
void  FUN_0040ce80(void* dst, const void* src);             // 0x0040ce80
}
namespace SP {
void* FUN_005f4e10(void* a, void* b, void* c);              // 0x005f4e10
}
namespace SP {
void* FUN_00572790(void* a);                                // 0x00572790
}
namespace SP {
void* FUN_0067cad0_box(void* box);                          // 0x0067cad0
}
namespace SP {
void* FUN_00a16f40(void* self);                             // 0x00a16f40
}
namespace SP {
void  MatrixFromQuaternion(void* out, const void* quat);    // 0x00698650
}
namespace SP {
void  FUN_00537dc0(void* a, const void* b);                 // 0x00537dc0
}
namespace SP {
void  ComposeTransforms(void* a, const void* b);            // 0x0040ccb0
}
namespace SP {
struct SwatchMatrix3 { float m[9]; void Assign(const void* src); };  // 0x0041cb40
}
namespace SP {
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
}
namespace SP {
struct ModelPtrVec {
  cMWModel_s005f_5f20** mpBegin;
  cMWModel_s005f_5f20** mpEnd;
  cMWModel_s005f_5f20** mpCapacity;
};
}
namespace SP {
struct KeyVec_s005f_5f20 {
  Key_s005f_5f20* mpBegin;
  Key_s005f_5f20* mpEnd;
  Key_s005f_5f20* mpCapacity;
};
}
namespace SP {
class cRefVt {
 public:
  PV_s005f_5f20(0)
  virtual void Vt4();   // +0x04
  virtual void Vt8();   // +0x08
  PV_s005f_5f20(3) PV_s005f_5f20(4) PV_s005f_5f20(5) PV_s005f_5f20(6) PV_s005f_5f20(7)
  virtual void Vt20();  // +0x20
  PV_s005f_5f20(9) PV_s005f_5f20(10) PV_s005f_5f20(11) PV_s005f_5f20(12) PV_s005f_5f20(13) PV_s005f_5f20(14) PV_s005f_5f20(15) PV_s005f_5f20(16)
  virtual void Vt44();  // +0x44
  PV_s005f_5f20(18) PV_s005f_5f20(19) PV_s005f_5f20(20) PV_s005f_5f20(21) PV_s005f_5f20(22) PV_s005f_5f20(23) PV_s005f_5f20(24) PV_s005f_5f20(25) PV_s005f_5f20(26) PV_s005f_5f20(27) PV_s005f_5f20(28) PV_s005f_5f20(29) PV_s005f_5f20(30)
  PV_s005f_5f20(31) PV_s005f_5f20(32) PV_s005f_5f20(33)
  virtual void Vt88();  // +0x88
};
}
// ---- items of slice s005f5f20 end

// ---- items of slice s00ecda80 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_15abee4;      // DAT_015abee4
extern char vtbl_BakeSprites[];
extern char vtbl_cSPScenarioSwatchItemUI[];
extern char vtbl_PaintSystem[];
#define C2(p, off, a, b) ((void(__thiscall*)(void*, int, int))(((void**)(p))[(off) / 4]))(p, a, b)
#define K0(p, off)      ((int(__thiscall*)(void*))(((void**)(p))[(off) / 4]))(p)
#define VTB(p, off)     (*(void***)(p))[(off) / 4]
struct ColorStore     { void Set(float v); void FUN_007a4c80(int mode); void FUN_005f49a0(int mode); };  // 0x005f22f0 / 0x007a4c80 / 0x005f49a0
static inline ColorStore* __cdecl PaletteTarget(void* obj)
{
    return (ColorStore*)((int(__thiscall*)(void*, int))VTB(obj, 0xc))(obj, 0x3349c94);
}
bool __cdecl FUN_005f3060();
void __cdecl FUN_00805fe0(void* out, int a);
bool __cdecl FUN_00efc9c0();
void __cdecl FUN_005f4750();
void __cdecl FUN_00401020();
int* __cdecl FUN_0113ae10();
int* __cdecl SP_WindowManager();
void __cdecl cSPUIPropertyLayout_SetPositionAndOffset(void* self, float a, float b, float c, float d);
void __cdecl FUN_005f0ca0(void* a);
int* __fastcall FUN_01137690(void* self);   // 0x01137690
void* __fastcall FUN_005f33f0(void* self);  // 0x005f33f0
void __cdecl FUN_005f7380();
struct PaletteSwatch_ece140 {
    char  pad00[0x4c];
    void* mpTarget_4c;               // +0x4c  palette target object
    char  pad50[0x5c - 0x50];
    void* mpWindow_5c;               // +0x5c  preview window
    char  pad60[0x64 - 0x60];
    float mAmount_64;                // +0x64  amount (negative -> default)
    void SetMode(int mode);
};
struct Obj_ecdc70 { int FUN_00ecdc70(); };
// ---- items of slice s00ecda80 end

// ---- items of slice s00eceab0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define C1(p, off, a)   ((void(__thiscall*)(void*, int))((*(void***)(p))[(off) / 4]))(p, a)
int   __cdecl SP_PropertyManager();
// ---- items of slice s00eceab0 end

// ---- items of slice s00ed0b70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void*         g_16c7aa4;      // 0x016c7aa4
extern float         g_15abf5c;      // 0x015abf5c
extern float         g_13ec4d0;      // 0x013ec4d0 (100.0f)
void* __cdecl FUN_00401090(void*);                      // 0x00401090
int   __cdecl FUN_00c028b0(void*, int);                 // 0x00c028b0
float __cdecl FUN_004d12a0(int);                        // 0x004d12a0
void  __cdecl FUN_00881ae0(int, int, void*, int);       // 0x00881ae0
void  __cdecl FUN_00edf830(void*, float, int, int, void*, void*);   // 0x00edf830
void  __cdecl FUN_00eeea50(void*, void*);               // 0x00eeea50
void* __cdecl FUN_0067dcc0(void);                       // 0x0067dcc0
void  __fastcall FUN_00ece300(char*);                   // 0x00ece300
void* __stdcall FUN_00401020(void*);                    // 0x00401020
void  __fastcall FUN_005f7380(void*);                   // 0x005f7380
void* __cdecl EA_New(unsigned, const char*, int, int, const char*, int);  // 0x00f473a0
void  __cdecl EA_Free(void*);                           // 0x00f47380
void  __cdecl FUN_00805fe0(float*, int);                // 0x00805fe0
int   __cdecl FUN_005f3060_s00ed_0b70(void);                       // 0x005f3060
int   __cdecl FUN_00efc9c0_s00ed_0b70(void);                       // 0x00efc9c0
struct Fn005f22f0 {
    void fn(float);     // 0x005f22f0
};
struct Fn00ecf000 {
    void fn();          // 0x00ecf000
};
struct Fn00ecf940 {
    void fn();          // 0x00ecf940
};
struct Fn00ecf320 {
    void fn(int, int, int, int);    // 0x00ecf320
};
struct Fn00f3bcb0 {
    void* fn();         // 0x00f3bcb0
};
struct Fn004df550 {
    void* fn(void*);    // 0x004df550
};
typedef void* (__thiscall *FV_i)(void*, int);
typedef void  (__thiscall *FV_vi)(void*, int);
typedef void  (__thiscall *FV_vii)(void*, int, int);
struct ILayout {
    void* FindWindowByID(unsigned, int);   // 0x008105b0
};
struct Obj14C0 { void f(int*); };
struct ProfileSlot {            // the slot the profile manager's ids resolve to
    char          pad000[0x170];    // +0x000
    float         f170;         // +0x170
    unsigned char b174;         // +0x174
    unsigned char b175;         // +0x175
};
struct SpeciesProfile {         // what the 0x004df550 lookup hands back
    char  pad000[0x56c];        // +0x000
    float f56c;                 // +0x56c
    char  pad570[0xd4];         // +0x570
    float f644;                 // +0x644
};
struct Obj10B0 {
    char  pad00[0x28];      // +0x00
    void* cb28;             // +0x28  object asked for the window through vtable slot 3
    void  f(int, int, int, int);
};
struct Obj1550 {
    char  pad00[0x50];      // +0x00
    void* layout;           // +0x50  cSPUILayout
    char  pad54[0x14];      // +0x54
    char  b68;              // +0x68
};
struct Range3 {                 // three ids, or an array with an inline sentinel
    void* p0;               // +0x00
    void* p1;               // +0x04
    void* p2;               // +0x08
};
// ---- items of slice s00ed0b70 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
bool __fastcall FUN_00ed13e0(void* self, int dummy, int id, float scale);  // 0x00ed13e0 (stays in the slice: not this object's)
void FUN_00ed1030(void);  // 0x00ed1030 (stays in the slice: not this object's)

// ---- items of slice s00ed1880 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef void* (__thiscall* FV_v)(void*);
typedef void* (__thiscall* FV_i_s00ed_1880)(void*, int);
typedef void* (__thiscall* FV_ii)(void*, int, int);
typedef void* (__thiscall* FV_p)(void*, void*);
typedef void* (__thiscall* FV_fff)(void*, void*, void*);
void* __cdecl EAAllocate(unsigned size, const char* name, int, int, int, int);  // 0xf473a0
void* __cdecl FUN_005c66a0(void);                                  // 0x005c66a0
void* __cdecl FUN_005c64e0(void);                                  // 0x005c64e0
void* __cdecl FUN_005c6710(void*);                                 // 0x005c6710
void* __cdecl FUN_009512c0(void);                                  // 0x009512c0
void* __cdecl FUN_009512d0(int, int, const char*, void*);          // 0x009512d0
void* __cdecl FUN_00ed1250(void*);                                 // 0x00ed1250
void* __cdecl FUN_00ed1120(void*, void*, void*, int, int, int, int); // 0x00ed1120
void* __cdecl FUN_00ed0c30(void*);                                 // 0x00ed0c30
void* __cdecl FUN_0067dcc0(void*, void*, int);                     // 0x0067dcc0 SP::MessageServer
struct Container;
void* __cdecl FUN_004db620(void*, void*, void*, int);              // 0x004db620 Connector::Init
void* __cdecl FUN_005f2290(int);                                   // 0x005f2290
void* __cdecl FUN_005c6810(void*, int*, int, int);                 // 0x005c6810 cSPPaletteItem::Init
void* __cdecl FUN_00805070(int);                                   // 0x00805070 GetLayoutManager
void* __cdecl FUN_00810620(void*);                                 // 0x00810620 GetWorldMainWindow
void* __cdecl FUN_00962a10(void*);                                 // 0x00962a10 Window::Window
struct Entry {
    void* a;         // +0x00
    void* b;         // +0x04
    int   cat;       // +0x08
    int   page;      // +0x0c
    int   sub;       // +0x10
};
struct Container {
    char   pad00[8];
    int    f08;                 // +0x08
    int    pad0c;
    void*  hA;                  // +0x10  handle
    void*  hB;                  // +0x14  handle
    void*  hItemUI;             // +0x18  handle
    char   pad1c[4];
    char   conn[0x38 - 0x20];
    void*  hAvatarUI;           // +0x38
    int    pad3c;
    void*  hPaletteCatUI;       // +0x40  QueryInterface 0x52deed23
    int    pad44;
    char   f48;                 // +0x48  visible flag
    char   pad49[3];
    int    notifier;            // +0x4c
    char   pad50[8];
    int    callback;            // +0x58
    Entry* vec0;                // +0x5c
    Entry* vec0End;             // +0x60
    char   pad64[0x0c];
    Entry* vec1;                // +0x70
    Entry* vec1End;             // +0x74
};
// ---- items of slice s00ed1880 end

// @ 0x005f2180
namespace SP {
int cSPSwatchPlanner::Check()
{
  if (mEB != 0) {
    if (m166 != 0 && m160 != 0 && m163 != 0)
      return 1;
    return 0;
  }
  if (m166 != 0 && m160 != 0)
    return 1;
  return 0;
}
}  // namespace SP

// @ 0x005f21d0
namespace SW {
void cSPSwatchPlannerReal::SetModel(cPropertyList*& out)
{
  if (mModelKind == -1) {
    FUN_005a8ed0(mModelKey, out);
    return;
  }
  PropertyManager()->GetPropertyList(RemapTypeId(mModelKind), g_ModelGroup, out);
}
}  // namespace SW

// @ 0x005f22a0
void * SP::cSPOLDPaletteItemUIDragAndBuy::AsInterface(EA::COM::InterfaceId id)
{
  if (id == 0x3349c94)
    return this;
  if (id == 0xee3f516e)
    return this;
  if (id == 0x2f009dd0)
    return this;
  return id == 0x31e56741 ? this : 0;
}

// @ 0x005f22d0
namespace SP {
int cSPSwatchPlanner::CheckType()
{
  if (m198 != 0 && m100 == 0x71fa7d3f)
    return 1;
  return 0;
}
}  // namespace SP

// @ 0x005f2310
namespace SP {
float cSPSwatchPlanner::GetDouble94()
{
  return m94 + m94;
}
}  // namespace SP

// @ 0x005f2350
namespace SP {
int cSPSwatchPlanner::Contains(const float* point)
{
  const float* self = (const float*)this;
  return point[0] >= self[0] && point[1] >= self[1] && point[0] < self[2] && point[1] < self[3];
}
}  // namespace SP

// @ 0x005f2390
namespace SW {
void SizeViewportToWindowAndRemainOnScreen(cUIViewport* viewport, IWindow* window, float scale, float cx, float cy)
{
  if (viewport && window) {
    Rect screen;
    App()->GetScreenRect(&screen)->FUN_007c4010();
    const float* const area = window->GetArea();
    const float halfW = ((area[2] - area[0]) * scale) * 0.5f;
    const float halfH = ((area[3] - area[1]) * scale) * 0.5f;
    Rect r;
    r.left = (int)(cx - halfW);
    r.top = (int)(cy - halfH);
    r.right = (int)(cx + halfW);
    r.bottom = (int)(cy + halfH);
    if (r.left < screen.left) {
      const int d = screen.left - r.left;
      r.left = r.left + d;
      r.right = r.right + d;
    }
    if (r.right > screen.right) {
      const int d = screen.right - r.right;
      r.left = r.left + d;
      r.right = r.right + d;
    }
    if (r.top < screen.top) {
      const int d = screen.top - r.top;
      r.top = r.top + d;
      r.bottom = r.bottom + d;
    }
    if (r.bottom > screen.bottom) {
      const int d = screen.bottom - r.bottom;
      r.top = r.top + d;
      r.bottom = r.bottom + d;
    }
    viewport->FUN_007c4a60(&r);
    viewport->FUN_007c4b50(halfW / halfH);
  }
}
}  // namespace SW

// @ 0x005f24e0
namespace SW {
void cSwatch3DView::Init(IRefObj* renderer, int a2, char a3, char a4)
{
  mRenderer = renderer;
  if (a3) {
    mModelRenderer = FUN_0080ed50();
    int h = AddBoundingBox()->GetFactory()->Make(0);
    mModelRenderer->FUN_0080fa00(0x13567133, 0x13567133, h);
    mModelRenderer->FUN_0080d5c0(a2);
    const int ebp = mModelRenderer->FUN_0080db70();
    mWindow = GetAnimWorldManager()->GetWorld(L"CustomSwatchAnimWorld");
    IArgObj* const o = mModelRenderer->FUN_0080db90();
    if (o) o->Set(0);
    mWindow->SetArg(o);
    mWindow->SetArgs(ebp, 1, 1, 0, 0);
    IWindowLike* const w = mWindow.mpObject;
    mModelRenderer->FUN_0080d5a0(w, 0xe, 0)->FUN_0080f360();
    if (a4) {
      mEffectWorld = GetEffectWorld();
      if (mEffectWorld.mpObject) {
        mEffectWorld->V40();
        mEffectWorld->V24();
        mEffectWorld->V14(0x1d);
        mEffectWorld->V10(a3);
        mEffectWorld->V18(ebp, 0);
        mEffectWorld->V48(0x5e5252a);
        mEffectWorld->V28(1);
      }
    } else {
      mEffectWorld = 0;
    }
  } else {
    mLayeredObject = FUN_0080f730(AddBoundingBox());
    mLayeredObject->FUN_0080dda0(renderer, 0);
    mLayeredObject->FUN_0080d7d0(0);
    mLayeredObject->FUN_0080d790(a2, 0);
    mLayeredObject->FUN_0080d7c0(0);
  }
  mVisible = false;
}
}  // namespace SW

// @ 0x005f2740
namespace SP {
int cSPSwatchPlanner::GetBuffer()
{
  if (m04)
    return ((cWriter*)m04)->GetBuffer();
  if (m2c)
    return ((cObj2*)m2c)->Get();
  return 0;
}
}  // namespace SP

// @ 0x005f2780
namespace SP {
bool cSPSwatch_s005f_2780::HandleMessage(uint32_t messageID, void* message)
{
  if (messageID == 0x695e243) {
    const cModelChangedMessage* msg = (const cModelChangedMessage*)message;
    Key_s005f_2780 key;
    key.mInstance = msg->mInstanceID;
    key.mGroup = msg->mGroupID;
    key.mType = msg->mTypeID;
    if (key == mModelKey)
      ReloadModel();
  }
  return false;
}
}  // namespace SP

// @ 0x005f27c0
namespace SP {
bool cSPSwatch_s005f_2780::DoMessage(IWindow_s005f_2780* window, const Message_s005f_2780& message)
{
  if (mUseEditorCameraController && SwatchManager() && SwatchManager()->GetCameraManager() &&
      SwatchManager()->GetCameraManager()->GetActiveCamera()) {
    cICamera* camera = SwatchManager()->GetCameraManager()->GetActiveCamera();
    if (camera) {
      cICameraController_s005f_2780* controller = camera->Cast(0x29da727);
      if (controller) {
        switch (message.mEventType) {
          case 1:
            return controller->OnKeyDown(message.mParam10, message.mModifiers);
          case 2:
            return controller->OnKeyUp(message.mParam10, message.mModifiers);
          case 6:
            if (controller->OnMouseDown(message.mButton, message.mX, message.mY, message.mModifiers)) {
              WindowManager()->SetCapture(1, mBaseWindow);
              mCapturedMouseButtons[message.mButton - 1000] = true;
              return true;
            }
            break;
          case 7: {
            const uint32_t button = message.mButton - 1000;
            if (mCapturedMouseButtons[button]) {
              mCapturedMouseButtons[button] = false;
              if (!AnyMouseButtonCaptured())
                WindowManager()->ReleaseCapture(1, mBaseWindow);
            }
            return controller->OnMouseUp(message.mButton, message.mX, message.mY, message.mModifiers);
          }
          case 8:
            return controller->OnMouseMove(message.mX, message.mY, message.mModifiers);
          case 9:
            return controller->OnMouseWheel(message.mButton, message.mX, message.mY, message.mModifiers);
          case 10:
            controller->OnMouseEnter(message.mpWindow == mBaseWindow);
            break;
        }
      }
    }
  } else {
    switch (message.mEventType) {
      case 0x1b:
        if (!IsDragging() && message.mParam0c == 1 && message.mpWindow == mBaseWindow) {
          mMouseOverWindow = true;
          const bool left = IsKeyDown(1000);
          const bool right = IsKeyDown(0x3ea);
          const bool middle = IsKeyDown(0x3e9);
          if (!left && !right && !middle) {
            PlayAudio(0xbb58117e, GetAudioSystem());
            OnMouseEnter();
          }
        }
        break;
      case 6:
        if (message.mButton == 1000) {
          WindowManager()->SetFocus(0, WindowManager()->GetMainWindow());
          OnClick();
          return true;
        }
        break;
      case 0x7be2440:
        return true;
      case 1:
      case 2:
      case 5:
        WindowManager()->GetFocus(1);
        {
          const bool focused = WindowManager()->GetFocus(1) == window;
          return focused;
        }
      case 0x1c:
        if (!IsDragging() && message.mParam0c == 1 && message.mpWindow == mBaseWindow) {
          mMouseOverWindow = false;
          OnMouseLeave();
        }
        break;
      case 0x7be2444:
      case 0x7be2445:
        message.mpCursorData->mCursorID = 0x6493807;
        return true;
      case 0x7be2441:
        OnMouseDown();
        OnMouseLeave();
        return true;
    }
  }
  return false;
}
}  // namespace SP

// @ 0x005f2bf0
namespace SP {
void cSPSwatch_s005f_2780::UpdateSwatchPosition(uint32_t deltaTime)
{
  IWindow_s005f_2780* window = mModelWindow;
  const RectT_s005f_2780 area = window->GetRealArea();
  const Point2D center = window->GlobalToLocal(
      Point2D((area.right - area.left) * 0.5f, (area.bottom - area.top) * 0.5f));
  mTargetViewportCenter = center;
  if (mWantToRenderModel || mForceRotation) {
    float angle;
    if (mAllowRotation) {
      angle = fmodf(deltaTime * 0.0015f + mTargetAngle, kTwoPI);
      if (angle >= 3.1415927f)
        angle -= kTwoPI;
    } else
      angle = 0.0f;
    mTargetAngle = angle;
    mActualAngle = angle;
    mTargetViewportScale = GetTargetZoom();
  }
}
}  // namespace SP

// @ 0x005f2d00
namespace SP {
uint32_t cSPSwatch_s005f_2780::SetImage(uint32_t imageID, bool overlay)
{
  uint32_t layer = 0;
  if (imageID && mpImageLayers) {
    mImageID = imageID;
    mImageOverlay = overlay;
    if (overlay) {
      layer = mpImageLayers->AddLayer(imageID, 0);
      mpImageLayers->SetLayerVisible(layer, true);
      mpImageLayers->SetLayerScaled(layer, true);
      mpImageLayers->Refresh(layer);
      mpImageLayers->SetLayerTiled(layer, true);
      mpImageLayers->SetLayerAlpha(layer, -1.0f);
      mImageSet = true;
      return layer;
    } else {
      layer = mpImageLayers->AddLayer(imageID, 0);
      mpImageLayers->SetLayerVisible(layer, true);
      mpImageLayers->Refresh(layer);
      mImageSet = true;
      return layer;
    }
  }
  if (!mpImageLayers && overlay) {
    mImageID = imageID;
    mImageOverlay = overlay;
  }
  return layer;
}
}  // namespace SP

// @ 0x005f2e00
namespace SP {
void cSPSwatch_s005f_2780::Show3DModel()
{
  if (mBakedAsset ? (mVisible && mHasBeenFramed && mIsModelBaked) : (mVisible && mHasBeenFramed)) {
    if (mModelWindow)
      mTargetWindowAlpha = 0.0f;
    if (mModel)
      mTargetModelAlpha = 1.0f;
    if (m3DView.mLayeredObject)
      m3DView.mLayeredObject->SetVisible(true);
    if (m3DView.mTexture) {
      void* texture = m3DView.mTexture->GetTexture();
      m3DView.mRenderer->SetTexture(texture);
    }
    m3DView.mVisible = true;
  }
  if (mpImageLayers)
    mpImageLayers->mVisible = true;
}
}  // namespace SP

// @ 0x005f2eb0
namespace SP {
void cSPSwatch_s005f_2780::Hide3DModel()
{
  if (mModelWindow) {
    mTargetWindowAlpha = 1.0f;
    mTargetModelAlpha = 0.0f;
  }
  if (mpImageLayers)
    mpImageLayers->mVisible = false;
}
}  // namespace SP

// @ 0x005f2ee0
namespace SP {
void cSPSwatch_s005f_2780::StartModelEffects()
{
  if (mModel) {
    uint32_t effectID = kSwatchEffectDefault;
    if (mModelKey.mType == 0x2399be55)
      effectID = kSwatchEffectCreature;
    const int count = mModel->mpWorld->GetEffectCount(mModel);
    for (int i = 0; i < count; i++)
      mModel->mpWorld->StartEffect(mModel, effectID, 0, 0.0f, i);
  }
}
}  // namespace SP

// @ 0x005f2f50
namespace SP {
bool cSPSwatch_s005f_2780::IsAnimating()
{
  if (!mDisplay3DModel)
    return false;
  if (mUseEditorCameraController || mIsZooming || mForceRotation || mTargetAngle != 0.0f ||
      mTargetAngle != mActualAngle || mTargetViewportScale != 1.0f ||
      mTargetViewportScale != mActualViewportScale || !mModelWindow->IsAnimationDone())
    return true;
  return false;
}
}  // namespace SP

// @ 0x005f2fd0
namespace SP {
bool cSPSwatch_s005f_2780::TakeCapture()
{
  if (mBaseWindow && !IsCapturedBySelf()) {
    cInputManager* input = InputManager();
    void* self = CastInterface(0xee3f516e);
    return input->SetCapture(mBaseWindow, self);
  }
  return false;
}
}  // namespace SP

// @ 0x005f3040
namespace SP {
void cSPSwatch_s005f_2780::EndInteraction()
{
  if (mBaseWindow)
    mBaseWindow->SetArea(mOriginalWindowArea);
  mWantToRenderModel = false;
}
}  // namespace SP

// @ 0x005f3060
namespace SP {
bool cSPSwatch_s005f_2780::HasCapture()
{
  cInputManager* input = InputManager();
  if (input->IsCapturing() && SwatchInterface(this) == input->GetCaptured())
    return true;
  return false;
}
}  // namespace SP

// @ 0x005f30b0
namespace SP {
void cSPPaletteSwatch_s005f_2780::OnRolloverEnd()
{
  cSPPaletteItemRollover_s005f_2780* rollover = SwatchManager()->GetSwatchRollover();
  if (rollover && mAllowTooltip) {
    if (mInfo->mRollover)
      rollover = mInfo->mRollover;
    rollover->Hide();
  }
  RenderManager()->SetHighlight(GetWindow(), false, true);
  if (mCostWindow)
    RenderManager()->SetHighlight(mCostWindow, false, true);
  mWantToRenderModel = false;
  cSwatchMessage msg;
  msg.mID = 0x522f9ce;
  msg.mpSwatch = this;
  MessageServer()->MessageSend(msg.mID, &msg, 0);
}
}  // namespace SP

// @ 0x005f3150
namespace SP {
int cSPSwatch_s005f_2780::IsBusy()
{
  return IsAnimating() || HasCapture();
}
}  // namespace SP

// @ 0x005f31a0
namespace SP {
void cSPSwatch_s005f_2780::UpdateViewport(uint32_t deltaTime)
{
  if (HasCapture()) {
    mTargetViewportCenter = WindowManager()->GetMousePosition();
    mTargetViewportScale = GetTargetZoom();
  } else {
    IWindow_s005f_2780* window = mModelWindow;
    const RectT_s005f_2780 area = window->GetRealArea();
    const Point2D center = window->GlobalToLocal(
        Point2D((area.right - area.left) * 0.5f, (area.bottom - area.top) * 0.5f));
    mTargetViewportCenter = center;
    if (mWantToRenderModel) {
      float angle;
      if (mAllowRotation) {
        angle = fmodf(deltaTime * 0.0015f + mTargetAngle, kTwoPI);
        if (angle >= 3.1415927f)
          angle -= kTwoPI;
      } else
        angle = 0.0f;
      mTargetAngle = angle;
      mActualAngle = angle;
      mTargetViewportScale = GetTargetZoom();
      return;
    }
    mTargetViewportScale = 1.0f;
  }
  mTargetAngle = 0.0f;
}
}  // namespace SP

// @ 0x005f3320
namespace SP {
bool cSPPaletteSwatch_s005f_2780::IsMouseOutside()
{
  if (HasCapture()) {
    RectT_s005f_2780 area;
    GetWindowGlobalArea(&area, mDragWindow);
    if (!area.Contains(mActualViewportCenter))
      return true;
  }
  return false;
}
}  // namespace SP

// @ 0x005f33c0
namespace SP {
bool cSPPaletteSwatch_s005f_2780::IsItemAvailable()
{
  if (mInfo && mInfo->mEconomy)
    return mInfo->mEconomy->IsItemAvailable(mInfo->mUseModelKeyForCost ? &mModelKey : &mOriginalItemKey);
  return true;
}
}  // namespace SP

// @ 0x005f3400
namespace SP {
void cSPPaletteSwatch_s005f_2780::UpdateCostDisplay()
{
  mMaterialParams = kSwatchParamsDefault;
  bool showCost = false;
  if (mShowCost) {
    int status = 1;
    cItemCostInfo info;
    if (mInfo && mInfo->mEconomy)
      status = mInfo->mEconomy->GetItemStatus(mInfo->mUseModelKeyForCost ? &mModelKey : &mOriginalItemKey, &info);
    switch (status) {
      case 1:
        mMaterial = kSwatchMaterialNormal;
        break;
      case 6: {
        if (!mCostWindow) {
          mCostWindow = CreateCostWindow(mModelWindow->GetParent());
          mCostWindow->SetFlag(0x10, true);
          mCostWindow->SetFlag(1, false);
        }
        mMaterial = kSwatchMaterialCost;
        showCost = true;
        cImageInfo* image = GetImageInfo(info.mImageID);
        const float height = (float)image->mHeight;
        const float width = (float)image->mWidth;
        SetWindowImageInfo(mCostWindow, image, -1);
        const RectT_s005f_2780 base = mModelWindow->GetRealArea();
        RectT_s005f_2780 area;
        area.left = ((base.right - base.left) - width) * 0.5f + base.left;
        area.right = area.left + width;
        area.top = ((base.bottom - base.top) - height) * 0.5f + base.top;
        area.bottom = area.top + height;
        mCostWindow->SetArea(area);
        mCostWindow->SetShadeColor(info.mColor);
        break;
      }
      default:
        mMaterial = kSwatchMaterialLocked;
        mMaterialParams = kSwatchParamsBlink;
        break;
    }
  } else
    mMaterial = kSwatchMaterialNormal;
  if (mCostWindow)
    mCostWindow->SetFlag(1, showCost);
  mWindowMaterial = mMaterial;
  mWindowMaterialParams = mMaterialParams;
}
}  // namespace SP

// @ 0x005f3600
namespace SP {
void cSPPaletteSwatch_s005f_2780::UpdateCursor()
{
  uint32_t cursorID = 0;
  if (mDraggable) {
    if (IsCapturedBySelf())
      cursorID = 0x6493807;
    else if (mShowCost && !mIsLocked && IsItemAvailable())
      cursorID = 0x648fbf1;
    else
      cursorID = 0;
  }
  if (mBaseWindow)
    mBaseWindow->SetCursorID(cursorID);
}
}  // namespace SP

// @ 0x005f3680
namespace eastl {
template <typename T> void vector_s005f_2780<T>::DoDestroyValues(T* first, T* last)
{
  for (; first < last; ++first)
    first->~T();
}
}  // namespace eastl

// @ 0x005f36d0
namespace SP {
uint32_t GetThumbnailCameraID(uint32_t modelType, uint32_t unused)
{
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
    cPropertyManager_s005f_36d0* pm = PropertyManager();
    void* prop = 0;
    bool flag = false;
    pm->GetConfigProperty(config, DAT_0151c614, &prop, &flag);
    if (prop) {
      Key_s005f_36d0 k;
      k.mInstance = 0;
      k.mType = 0;
      k.mGroup = 0;
      if (GetPropertyAsKey(prop, flag ? 0xffedb73d : 0xb02d871c, &k))
        cameraID = k.mInstance;
    }
  }
  return cameraID;
}
}  // namespace SP

// @ 0x005f3810
namespace SP {
void cSwatch3DView_s005f_36d0::RenderFrame(int time)
{
  if (mWindow) {
    void* buffer;
    if (!mLayeredObject)
      buffer = mTexture ? mTexture->FUN_0080d5f0() : 0;
    else
      buffer = mLayeredObject->GetBuffer();
    float t = (float)time;
    if (time < 0)
      t += 4294967296.0f;
    ((cSwatchWindow*)mWindow)->Vt24(t * 0.001f, buffer);
  }
  if (mCamera) {
    if (((cCameraVt*)mCamera)->GetType() == 0x5e5252a) {
      cViewer_s005f_36d0* viewer = SwatchManager_s005f_36d0()->GetCameraManager()->GetActiveViewer();
      Vector3 loc;
      viewer->GetCameraLocationInfo(&loc, 0, 0, 0);
      const void* p;
      if (!mAnimWorld)
        p = &DAT_015f1ce4;
      else {
        Vector3* v = (Vector3*)FUN_00a048a0();
        loc = *v;
        p = &loc;
      }
      cCameraVt* cam = (cCameraVt*)mCamera;
      (void)p;
      (void)cam;
    }
  }
}
}  // namespace SP

// @ 0x005f3930
namespace SP {
cISPCreatureAnimWorld* cSwatch3DView_s005f_36d0::AddCreature(uint32_t modelID, void* key, int type)
{
  if (mLayeredObject) {
    cAnimWorld* newWorld = (cAnimWorld*)SwatchManager_s005f_36d0()->CreateAnimatingCreature(modelID, key);
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
        ->Vt30(modelID, key, &DAT_015f1ce4, &DAT_0151c5f8, 1);
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
}  // namespace SP

// @ 0x005f3b20
namespace SP {
void cSPSwatch_s005f_36d0::InitInternal(IWindow_s005f_36d0* base, IWindow_s005f_36d0* modelWindow, uint32_t a3, uint32_t a4, bool b5, bool b6, uint32_t a7, uint32_t a8)
{
  mIgnoreFocusChange = b5;
  mForceRotation = b6;
  *(uint32_t*)((char*)this + 0xf4) = a7;
  mBaseWindow = base;
  if (mBaseWindow)
    mBaseWindow->AddWinProc((IWinProc_s005f_36d0*)this);
  mModelWindow = modelWindow;
  EA::Messaging::Server_s005f_36d0* server = MessageServer_s005f_36d0();
  if (server)
    server->AddHandler((EA::Messaging::IHandler_s005f_36d0*)((char*)this + 0xc), 0x695e243);
  m3DView.Init(mModelWindow, a4, a3, a8);
  mUseStaticEffects = (a3 == 0);
  RectT_s005f_36d0 area = mBaseWindow->GetRealArea();
  mOriginalWindowArea = area;
  mWindowMaterial = kSwatchMaterialNormal;
  *(const wchar_t**)((char*)this + 0xc8) = kSwatchMaterialNormal;
  *(const wchar_t**)((char*)this + 0xd0) = mMaterialParams;
  *(const wchar_t**)((char*)this + 0xd4) = mMaterialParams;
  mTargetModelAlpha = 0.0f;
  mCurrentModelAlpha = 0.0f;
  mCamera = 0xff4641e7;
  RectT_s005f_36d0 winArea = mModelWindow->GetRealArea();
  Point2D_s005f_36d0 center = mModelWindow->GlobalToLocal(
      Point2D_s005f_36d0((winArea.right - winArea.left) * 0.5f, (winArea.bottom - winArea.top) * 0.5f));
  mTargetViewportCenter = center;
  mActualViewportCenter = center;
  mActualAngle = mTargetAngle;
  mActualViewportScale = mTargetViewportScale;
}
}  // namespace SP

// @ 0x005f3cf0
namespace SP {
void cSPSwatch_s005f_36d0::FrameModel()
{
  if (mUseEditorCameraController) {
    mHasBeenFramed = true;
    return;
  }
  void* frame;
  if (m3DView.mLayeredObject)
    frame = m3DView.mLayeredObject->GetBuffer();
  else if (m3DView.mTexture)
    frame = m3DView.mTexture->FUN_0080d5f0();
  else
    return;
  if (!frame)
    return;
  (void)frame;
  cMWModel_s005f_36d0* model = mModel;
  if (!model)
    return;
  bool hasTransforms = (*(void**)((char*)this + 0xf0) != 0);
  if (!hasTransforms) {
    cSPTransform t;
    FUN_00409930(&t);
    // box extents
    cMWModel_s005f_36d0* extra = *(cMWModel_s005f_36d0**)((char*)this + 0x110);
    (void)extra;
  }
  (void)model;
}
}  // namespace SP

// @ 0x005f4080
namespace SP {
void cSPSwatch_s005f_36d0::SetModelKey(Key_s005f_36d0* key)
{
  mModelKey = *key;
  mCamera = GetThumbnailCameraID(mModelKey.mType, 0);
}
}  // namespace SP

// @ 0x005f40b0
namespace SP {
void cSPSwatch_s005f_36d0::UpdateBakingTransform()
{
  if (!mUseEditorCameraController)
    return;
  if (*(void**)((char*)this + 0xf0) != 0)
    return;
  if (!mBakedAsset)
    return;
  if (!mModel)
    return;
  cMWModel_s005f_36d0* model = mModel;
  int p = *(int*)((char*)model + 0x90);
  float scale = 1.0f;
  if (p && GetFloatProperty((void*)p, 0xfba611, &scale) && scale > 0.0f) {
    *(uint16_t*)((char*)model + 0xa) += 1;
    *(float*)((char*)model + 0x18) = 1.0f / scale;
  }
  cSPTransform t;
  FUN_00409930(&t);
  FUN_006baa70(DAT_0151c568);
  Matrix3 mtx;
  Matrix3_Assign(&mtx, &t);
  *(uint16_t*)((char*)model + 8) |= 2;
  *(Matrix3*)((char*)model + 0x1c) = mtx;
  *(uint16_t*)((char*)model + 0xa) += 1;
  uint32_t v[3];
  v[0] = *(uint32_t*)&DAT_015f1ce4;
  v[1] = *(uint32_t*)&DAT_015f1ce8;
  v[2] = *(uint32_t*)&DAT_015f1cec;
  void* theme = FUN_005766b0(0);
  if (cSPEditorPaintTheme_Apply(&mModelKey, theme)) {
    cSPBoundingBox_AddBoundingBox(0, 0, 0);
    int* q = (int*)FUN_0046bfd0(0, 0);
    v[0] = q[0];
    v[1] = q[1];
    v[2] = q[2];
    FUN_006c10e0();
    FUN_004ad330();
  }
  *(uint16_t*)((char*)model + 8) |= 4;
  *(uint16_t*)((char*)model + 0xa) += 1;
  v[0] ^= 0x80000000;
  v[1] ^= 0x80000000;
  v[2] ^= 0x80000000;
  *(uint32_t*)((char*)model + 0xc) = v[0];
  *(uint32_t*)((char*)model + 0x10) = v[1];
  *(uint32_t*)((char*)model + 0x14) = v[2];
  FUN_004a9ae0();
}
}  // namespace SP

// @ 0x005f42d0
namespace SP {
void cSPSwatch_s005f_36d0::OnBakingIsDone()
{
  mIsModelBaked = true;
  if (mModelLoaded) {
    mModelLoaded = false;
    mModelLoadStarted = true;
  }
  mHasBeenFramed = false;
  if (mUseEditorCameraController)
    UpdateBakingTransform();
}
}  // namespace SP

// @ 0x005f4310
namespace SP {
void cSPOLDPaletteItemUIDragAndBuy_s005f_4310::Init(Key_s005f_4310* key, void* a, void* b, uint32_t c, void* d, void* e, bool f)
{
  InitInternal((IWindow_s005f_4310*)a, (IWindow_s005f_4310*)a, 0, 0, 0, 1, 0, 1);
  mOriginalItemKey = *key;
  if (key->mInstance != 0)
    Vt24(key);
  mDragWindow = (IWindow_s005f_4310*)b;
  mUnk190 = c;
  mPaletteItem = (cSPPaletteItem_s005f_4310*)d;
  mDraggable = f;
  mInfo = (cSPPaletteInfo_s005f_4310*)e;

  SW::cUIViewport_s005f_4310* viewport = 0;
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
      isNew = ((cSPPaletteItem_s005f_4310*)mPaletteItem)
                  ->IsNew((cCollectableItems_s005f_4310*)mInfo->mCollectableItems);
    bool available = isNew;
    if (mInfo->mEconomy != 0 && !available)
      available = mInfo->mEconomy->FUN_v5(&((cSPPaletteItem_s005f_4310*)mPaletteItem)->mKey);

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
          IWindow_s005f_4310* parent = mBaseWindow->GetParent();
          mLeftText->SetFlag(2, false);
          mLeftText->SetFlag(0x10, true);
          parent->AddChild(mLeftText);
          mRightText->SetFlag(2, false);
          mRightText->SetFlag(0x10, true);
          parent->AddChild(mRightText);
          RectT_s005f_4310 area = mBaseWindow->GetRealArea();
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
  EA::Messaging::Server_s005f_4310* server = MessageServer_s005f_4310();
  if (server != 0)
    server->AddHandler((EA::Messaging::IHandler_s005f_4310*)((char*)this + 0xc), 0x3150c27);
}
}  // namespace SP

// @ 0x005f46c0
namespace SP {
void cSPPaletteSwatch_s005f_4310::EndDrag()
{
  if (mBaseWindow)
    mBaseWindow->SetArea(mOriginalWindowArea);
  mWantToRenderModel = false;
  UpdateCursor();
}
}  // namespace SP

// @ 0x005f46f0
namespace SP {
bool cHandlerView::HandleMessage(uint32_t id, void* msg)
{
  if (id == 0x3150c27) {
    cSPPaletteSwatch_s005f_4310* self = (cSPPaletteSwatch_s005f_4310*)((char*)this - 0xc);
    self->UpdateCostDisplay();
    self->UpdateCursor();
    return false;
  }
  if (id == 0x695e243) {
    cModelChangedMessage* m = (cModelChangedMessage*)msg;
    cSPPaletteSwatch_s005f_4310* self = (cSPPaletteSwatch_s005f_4310*)((char*)this - 0xc);
    if (m->mInstanceID == self->mModelKey.mInstance && m->mTypeID == self->mModelKey.mType &&
        m->mGroupID == self->mModelKey.mGroup)
      self->ReloadModel();
  }
  return false;
}
}  // namespace SP

// @ 0x005f4750
namespace SP {
void cSPOLDPaletteItemUIDragAndBuy_s005f_4310::OnLeftMouseDown()
{
  bool available;
  cSPPaletteInfo_s005f_4310* info = mInfo;
  if (info != 0 && info->mEconomy != 0)
    available = info->mEconomy->IsItemAvailable(
        info->mUseModelKeyForCost ? &mModelKey : &mOriginalItemKey);
  else
    available = true;

  mAllowRotation = available && mShowCost && mInterfaceID == 0x71fa7d3f;
  mMaxViewportScaleFactor = mBaseScale * (available ? 1.0f : 0.75f);
  if (!mIsLocked && available)
    mWantToRenderModel = true;

  cSPPaletteItemRollover_s005f_4310* rollover = SwatchManager_s005f_4310()->GetSwatchRollover();
  if (rollover != 0 && mAllowTooltip) {
    cSPPaletteItemRollover_s005f_4310* rollover2 = mInfo->mRollover;
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
    RectT_s005f_4310 area = WindowManager_s005f_4310()->GetMainWindow()->GetWindowArea();
    rollover->FUN_008283a0(mActualViewportCenter.x, mActualViewportCenter.y,
                           (area.right - area.left) * 0.05f, (area.bottom - area.top) * 0.0f);
  }

  AddBoundingBox(GetWindow(), 1, 1)->FUN_0080d710();
  if (mCostWindow != 0)
    AddBoundingBox(mCostWindow, 1, 1)->FUN_0080d710();

  cSwatchMessage_s005f_4310 msg;
  msg.mpSwatch = this;
  msg.mID = 0x522f9cd;
  MessageServer_s005f_4310()->MessageSend(0x522f9cd, &msg, 0);
}
}  // namespace SP

// @ 0x005f49a0
namespace SP {
void cSPPaletteSwatch_s005f_4310::SetShowCost(bool show)
{
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
}  // namespace SP

// @ 0x005f49f0
namespace SP {
void cSPOLDPaletteItemUIDragAndBuy_s005f_4310::OnMouseDown()
{
  if (mIsLocked)
    return;
  if (mModelKey.mInstance == 0 && mModel == 0)
    return;

  bool take = false;
  cSPPaletteInfo_s005f_4310* info = mInfo;
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
    Point2D_s005f_4310 mousePos;
    WindowManager_s005f_4310()->GetMousePosition(&mousePos);
    mOriginalMousePosition = mousePos;
    cSPPaletteItemRollover_s005f_4310* rollover = SwatchManager_s005f_4310()->GetSwatchRollover();
    if (rollover != 0) {
      cSPPaletteItemRollover_s005f_4310* rollover2 = mInfo->mRollover;
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
}  // namespace SP

// @ 0x005f4b80
namespace SP {
void cSPOLDPaletteItemUIDragAndBuy_s005f_4310::OnMouseUp()
{
  if (IsCapturedBySelf())
    InputManager_s005f_4310()->Dispose(0);

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
  MessageServer_s005f_4310()->MessageSend(mUnk190, &msg, 0);
  mWantToRenderModel = false;
  RectT_s005f_4310 area = mModelWindow->GetRealArea();
  Point2D_s005f_4310 center = mModelWindow->GlobalToLocal(
      Point2D_s005f_4310((area.right - area.left) * 0.5f, (area.bottom - area.top) * 0.5f));
  mActualViewportCenter = center;
  mTargetViewportCenter = center;
  if (msg.mpUnk24 != 0)
    msg.mpUnk24->Release();
  if (msg.mpRef != 0)
    msg.mpRef->Release();
}
}  // namespace SP

// @ 0x005f4eb0
namespace SP {
void cSwatch3DView_s005f_4310::RemoveModel(cMWModel_s005f_4310* model)
{
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
}  // namespace SP

// @ 0x005f4f80
namespace SP {
void cSPSwatch_s005f_4310::Init(Key_s005f_4310* key, uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t scale)
{
  if (a != 0) {
    mScaleParam = scale;
    bool b8 = true;
    if (key->mType == 0x3d97a8e4)
      b8 = false;
    InitInternal((IWindow_s005f_4310*)a, (IWindow_s005f_4310*)a, 1, b, c, d, e, b8);
    mOriginalItemKey = *key;
    if (key->mInstance != 0)
      Vt24(key);
  }
}
}  // namespace SP

// @ 0x005f5000
namespace SP {
void cSPSwatch_s005f_4310::Init(Key_s005f_4310* key, void* a, void* b, uint32_t c, uint32_t d, uint32_t e, uint32_t f, uint32_t scale)
{
  if (a != 0 && b != 0) {
    mScaleParam = scale;
    bool b8 = true;
    if (key->mType == 0x3d97a8e4)
      b8 = false;
    InitInternal((IWindow_s005f_4310*)a, (IWindow_s005f_4310*)b, 1, c, d, e, f, b8);
    mOriginalItemKey = *key;
    if (key->mInstance != 0)
      Vt24(key);
  }
}
}  // namespace SP

// @ 0x005f5080
namespace SP {
void FUN_005f5080()
{ /* partial: 1375-byte update routine not reconstructed */ }
}  // namespace SP

// @ 0x005f55e0
namespace SP {
void cSPSwatch_s005f_5080::RotateModel(uint32_t flags)
{ (void)flags; }
}  // namespace SP

// @ 0x005f58f0
namespace SP {
void cSPSwatch_s005f_5080::AddModelKey(const Key_s005f_5080& key)
{
  Key_s005f_5080* p = *(Key_s005f_5080**)((char*)this + 0x14c);
  KeyVec& v = *(KeyVec*)((char*)this + 0x148);
  if (p < v.mpCapacity) {
    v.mpEnd = p + 1;
    if (p)
      *p = key;
  } else {
    v.DoInsertValue(p, key);
  }
}
}  // namespace SP

// @ 0x005f5930
namespace SP {
void ShrinkTransformVector()
{ /* partial */ }
}  // namespace SP

// @ 0x005f5970
namespace SP {
void RefVec::clear()
{
  AutoRefCount_s005f_5080<cMWModel_s005f_5080>* begin = mpBegin;
  AutoRefCount_s005f_5080<cMWModel_s005f_5080>* end = mpEnd;
  AutoRefCount_s005f_5080<cMWModel_s005f_5080>* p = copy_refs(end, end, begin);
  DoDestroyValues(p, mpEnd);
  char* e = (char*)mpEnd;
  int n = (int)(e - (char*)begin);
  mpEnd = (AutoRefCount_s005f_5080<cMWModel_s005f_5080>*)(e + (-(n >> 2)) * 4);
}
}  // namespace SP

// @ 0x005f59b0
namespace SP {
cMWModel_s005f_5080* cSwatch3DView_s005f_5080::AddModel(uint32_t a, uint32_t b)
{
  if (mLayeredObject) {
    void* box = cSPBoundingBox_AddBoundingBox();
    cRefCountedModel2* mgr = ((cSPBoundingBox*)box)->GetModelManager();
    cMWModel_s005f_5080* m = mgr->MakeModel(a, b, 0x26);
    m->mFlags |= 0x2000;
    mLayeredObject->AddModel(m);
    mLayeredObject->SetVisible(mVisible);
    return m;
  }
  if (mTexture) {
    cRefCountedModel2* mgr = mTexture->GetModelManager();
    cMWModel_s005f_5080* m = mgr->MakeModel(a, b, 0x22);
    m->mFlags |= 0x2000;
    ++m->mRefCount;
    AutoRefCount_s005f_5080<cMWModel_s005f_5080>* p = mModels.mpEnd;
    if (p < mModels.mpCapacity) {
      mModels.mpEnd = p + 1;
      if (p) {
        p->mpObject = m;
        ++m->mRefCount;
      }
    } else {
      ((RefVec*)&mModels)->DoInsertValue(p, &m);
    }
    if (m) {
      if (m->mRefCount > 1) {
        --m->mRefCount;
        return m;
      }
      m->Release();
    }
    return m;
  }
  return 0;
}
}  // namespace SP

// @ 0x005f5aa0
void SP::cSwatch3DView::RemoveAllModels()
{
  if (mLayeredObject.mpObject == 0) {
    if (mAnimWorld.mpObject == 0)
      return;
    ((RefVec*)&mModels)->clear();
    if (mAnimatingCreature.mpObject == 0)
      return;
    ((cSwatchWindow_s005f_5080*)mAnimWorld.mpObject)->Vt3c(mAnimatingCreature.mpObject);
  } else {
    FUN_0080ea50(mLayeredObject.mpObject);
    FUN_008eb830(mLayeredObject.mpObject, 0);
    if (mAnimatingCreature.mpObject == 0)
      return;
    SwatchManager();
    FUN_005f0380();
  }
  if (mAnimatingCreature.mpObject == 0)
    return;
  cAnimWorld_s005f_5080* w = (cAnimWorld_s005f_5080*)mAnimatingCreature.mpObject;
  mAnimatingCreature.mpObject = 0;
  w->Release();
}

// @ 0x005f5b40
void SP::cSPSwatch::LoadModel(EA::ResourceMan::Key & a1)
{ /* partial: 687-byte model load not reconstructed */ }

// @ 0x005f5df0
namespace SP {
void cSPSwatch_s005f_5080::ShutDownModel()
{
  mModel = (cMWModel_s005f_5080*)0;
  ((RefVec*)((char*)this + 0x11c))->clear();
  ((RefVec*)((char*)this + 0x130))->clear();
  ((RefVec*)((char*)this + 0x104))->clear();
  ((KeyVec*)((char*)this + 0x148))->clear();
  void* effect = *(void**)((char*)this + 0xf0);
  if (effect) {
    *(void**)((char*)this + 0xf0) = 0;
    ((cAnimWorld_s005f_5080*)effect)->Release();
  }
  m3DView.RemoveAllModels();
  mCreatedCreature = false;
}
}  // namespace SP

// @ 0x005f5f20
namespace SP {
void cSPSwatch_s005f_5f20::SetModel(Key_s005f_5f20* key)
{
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
    Key_s005f_5f20 res = *key;
    res.mType = 0x2f7d0004;
    void* rm = ResourceManGetManager();
    bool ok = ((bool(__thiscall*)(void*, Key_s005f_5f20*, int, int, int, int, int))
                   ((*(void***)rm)[0xc / 4]))(rm, &res, 0, 0, 0, 0, 0);
    if (ok && *(uint8_t*)(s + 0x16c) == 0)
      SPUIHelpers::SetWindowImage(*(IWindow_s005f_5f20**)(s + 0x60), &res, -1);
    bool noCam = (*(uint8_t*)(s + 0x16c) != 0);
    *(float*)(s + 0xc4) = 0.0f;
    *(float*)(s + 0xc0) = 1.0f;
    if (!noCam)
      SetWindowAlpha(*(IWindow_s005f_5f20**)(s + 0x60), 0.0f);
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
}  // namespace SP

// @ 0x005f6090
namespace SP {
void cSPSwatch_s005f_5f20::InitAdditionalModels()
{
  char* const s = (char*)this;
  ModelPtrVec* models = (ModelPtrVec*)(s + 0x104);
  uint32_t count = (uint32_t)(models->mpEnd - models->mpBegin);
  for (uint32_t i = 0; i < count; i++)
    m3DView.RemoveModel(models->mpBegin[i]);

  cMWModel_s005f_5f20** first = models->mpBegin;
  cMWModel_s005f_5f20** last = models->mpEnd;
  cMWModel_s005f_5f20** res = (cMWModel_s005f_5f20**)FUN_005f4e10(last, last, first);
  ((ThisCallExterns*)models)->FUN_005f3680(res, models->mpEnd);
  models->mpEnd -= (uint32_t)(last - first);

  KeyVec_s005f_5f20* keys = (KeyVec_s005f_5f20*)(s + 0x148);
  uint32_t n = (uint32_t)(keys->mpEnd - keys->mpBegin);
  if (n != 0) {
    for (uint32_t i = 0; i < (uint32_t)(keys->mpEnd - keys->mpBegin); i++) {
      Key_s005f_5f20* e = keys->mpBegin + i;
      if (e->mInstance == 0)
        continue;
      cMWModel_s005f_5f20* m = m3DView.AddModel(e->mInstance, e->mGroup);
      if (m == 0)
        continue;
      ++*(int*)((char*)m + 0x40);
      if (models->mpEnd < models->mpCapacity) {
        cMWModel_s005f_5f20** slot = models->mpEnd;
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
    Key_s005f_5f20* kfirst = keys->mpBegin;
    Key_s005f_5f20* klast = keys->mpEnd;
    Key_s005f_5f20* d = kfirst;
    for (Key_s005f_5f20* p = klast; p != klast; ++p, ++d)
      *d = *p;
    keys->mpEnd -= (uint32_t)(klast - kfirst);
  }
}
}  // namespace SP

// @ 0x005f6260
namespace SP {
void cSPSwatch_s005f_5f20::InitStaticEffects()
{
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
    m3DView.RemoveModel((cMWModel_s005f_5f20*)*(void**)(*(int*)(s + 0x11c) + i * 4));

  ((ThisCallExterns*)(s + 0x11c))->FUN_005f5970();
  ((ThisCallExterns*)(s + 0x130))->FUN_005f5930();

  uint32_t total = *(uint32_t*)&tr;
  for (uint32_t i = 0; i < total; i++) {
    char* e = (char*)tr + i * 0xc;
    if (*(void**)e == 0)
      continue;
    SwatchMatrix3 basis;
    basis.Assign((const void*)0x15f1e14);
    cMWModel_s005f_5f20* m = m3DView.AddModel(*(uint32_t*)e, *(int*)(e + 8));
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
      cMWModel_s005f_5f20** slot = vec->mpEnd;
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
}  // namespace SP

// @ 0x005f6500
void SP::cSPSwatch::SetEditorCameraController(bool enable)
{
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

        Key_s005f_5f20 km1;
        Key_s005f_5f20 km2;
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

// @ 0x005f67d0
namespace SP {
void cSwatch3DView_s005f_5f20::Shutdown()
{
  if (mCamera) {
    ((cRefVt*)mCamera)->Vt44();
    void* camera = mCamera;
    if (camera) {
      mCamera = 0;
      ((cRefVt*)camera)->Vt4();
    }
  }
  RemoveAllModels();
  if (mLayeredObject) {
    mLayeredObject->FUN_0080dda0(0, 0);
    if (cSPBoundingBox_AddBoundingBox2()) {
      cUILayeredObject_s005f_5f20* boxed = mLayeredObject;
      cBoundingBoxList* list = cSPBoundingBox_AddBoundingBox2(boxed);
      list->FUN_0080f7c0(boxed);
    }
    cUILayeredObject_s005f_5f20* layered = mLayeredObject;
    if (layered) {
      mLayeredObject = 0;
      ((cRefVt*)layered)->Vt8();
    }
  }
  if (mWindow) {
    ((cRefVt*)mWindow)->Vt20();
    IWindow_s005f_5f20* window = mWindow;
    if (window) {
      mWindow = 0;
      ((cRefVt*)window)->Vt4();
    }
  }
  if (mTexture) {
    ((cRefVt*)mRenderer)->Vt88();
    mTexture->FUN_0080dfc0();
    cSwatchTexture_s005f_5f20* texture = mTexture;
    if (texture) {
      mTexture = 0;
      texture->FUN_0080df80();
    }
  }
  if (mRenderer) {
    cSwatchRenderer_s005f_5f20* renderer = mRenderer;
    mRenderer = 0;
    ((cRefVt*)renderer)->Vt4();
  }
  mVisible = false;
}
}  // namespace SP

// @ 0x005f69a0
void SP::cSPSwatch::OnModelLoad()
{
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

// @ 0x005f6bd0
SP::cSPSwatch::cSPSwatch()
{
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

// @ 0x00ecdc70
int Obj_ecdc70::FUN_00ecdc70()
{
    int param_1 = (int)this;
    char c = FUN_005f3060();
    if (c) {
        char buf[8];
        FUN_00805fe0(buf, *(int*)(param_1 + 0x18c));
        float f = *(float*)(buf + 8);
        if (f < *(float*)(param_1 + 0x84)) {
            if (FUN_00efc9c0())
                return 1;
        }
    }
    return 0;
}

// @ 0x00ecdcc0
void __fastcall FUN_00ecdcc0(int param_1)
{
    FUN_005f4750();
    FUN_00401020();
    void* prop = (void*)FUN_0113ae10();
    void* cand = *(void**)(*(int*)(param_1 + 0x17c) + 0x14);
    if (cand && *(char*)(*(int*)(param_1 + 0x17c) + 0x31) != 0)
        prop = cand;
    if (prop && *(char*)(param_1 + 0x16b) != 0) {
        int* wm = SP_WindowManager();
        int* w = (int*)K0(wm, 4);
        float* r = (float*)K0(w, 0x34);
        cSPUIPropertyLayout_SetPositionAndOffset(prop, *(float*)(param_1 + 0x84),
            *(float*)(param_1 + 0x88), (r[2] - r[0]) * 0.09375f, (r[3] - r[1]) * -0.025f);
    }
}

// @ 0x00ecdf60
void FUN_00ecdf60_fn(void)
{
    int* p = (int*)operator new(0x1c8);
    if (p) {
        FUN_005f7380();
        p[0] = (int)vtbl_BakeSprites;
        p[1] = (int)vtbl_cSPScenarioSwatchItemUI;
        p[3] = (int)vtbl_PaintSystem;
        FUN_00401020();
        FUN_005f0ca0(p);
        return;
    }
    FUN_00401020();
    FUN_005f0ca0(0);
}

// @ 0x00ecdfc0
void __fastcall FUN_00ecdfc0(int param_1)
{
    void* obj = *(void**)(param_1 + 0x4c);
    if (obj != 0) {
        float f = *(float*)(param_1 + 0x64);
        if (f < 0.0f)
            f = g_15abee4;
        ColorStore* u = (ColorStore*)((int(__thiscall*)(void*, int))VTB(obj, 0xc))(obj, 0x3349c94);
        if (u != 0)
            u->Set(f);
    }
}

// @ 0x00ece140
void PaletteSwatch_ece140::SetMode(int mode)
{
    if (mpTarget_4c == 0)
        return;

    ColorStore* store = PaletteTarget(mpTarget_4c);
    store->FUN_007a4c80(mode);
    ((void(__thiscall*)(ColorStore*, int))VTB(store, 0x38))(store, mode);
    store->FUN_005f49a0(mode);

    if (mpWindow_5c != 0)
        C2(mpWindow_5c, 0x7c, mode != 0 ? 1 : 0, 0x1000);

    if (mpTarget_4c == 0)
        return;

    float f = mAmount_64;
    if (f < 0.0f)
        f = g_15abee4;

    store = PaletteTarget(mpTarget_4c);
    if (store != 0)
        store->Set(f);
}

// @ 0x00ece3b0
int FUN_00ece3b0(int* param_1)
{
    if (param_1 != 0) {
        int i = ((int(__thiscall*)(void*, int))VTB(param_1, 0xc))(param_1, 0x3349c94);
        if (i != 0) {
            int* p = (int*)FUN_01137690(FUN_005f33f0((void*)i));
            if (p != 0) {
                int j = ((int(__thiscall*)(void*, int))VTB(p, 0xc))(p, 0x722de52);
                if (j != 0)
                    return j;
            }
        }
    }
    return 0;
}

// @ 0x00eceab0
void FUN_00eceab0(int param_1, int param_2)
{
    // reference-counted palette-item assignment + property push; partial.
    int* cur = *(int**)(param_1 + 4);
    if ((int*)param_2 != cur) {
        if (param_2)
            ((void(__thiscall*)(void*))(((void**)(param_2))[1]))((void*)param_2);
        *(int*)(param_1 + 4) = param_2;
        if (cur)
            ((void(__thiscall*)(void*))(((void**)cur)[2]))(cur);
    }
    int* pm = (int*)SP_PropertyManager();
    C1(pm, 0x2c, 0);
}

// @ 0x00ed10b0
void Obj10B0::f(int a1, int a2, int a3, int a4)
{
    ((Fn00ecf320*)this)->fn(a1, a2, a3, a4);
    FUN_00ed1030();
    void* cb = cb28;
    void* w = 0;
    if (cb != 0)
        w = (void*)((FV_i)(*(void***)cb)[0xc / 4])(cb, 0x3349c94);
    ((Fn005f22f0*)w)->fn(g_15abf5c);
}

// @ 0x00ed1380
bool __fastcall FUN_00ed1380(void* self)
{
    if (FUN_005f3060_s00ed_0b70() == 0)
        return false;
    float bounds[2];
    FUN_00805fe0(bounds, *(int*)((char*)self + 0x18c));
    if ((*(float*)((char*)self + 0x84) <= bounds[1] && bounds[1] != *(float*)((char*)self + 0x84)) ||
        (*(float*)((char*)self + 0x88) <= bounds[0] && bounds[0] != *(float*)((char*)self + 0x88))) {
        if (FUN_00efc9c0_s00ed_0b70() != 0)
            return true;
    }
    return false;
}

// @ 0x00ed1460
void FUN_00ed1460(void)
{
    char* p = (char*)EA_New(0x1c8, "Editor", 0, 0, 0, 0);
    if (p != 0) {
        FUN_005f7380(p);
        *(void**)p = (void*)0x1489aa0;
        *(void**)(p + 4) = (void*)0x13f9ea4;
        *(void**)(p + 0xc) = (void*)0x1489590;
        void* q = FUN_00401020(p);
        FUN_005f0ca0(q);
    } else {
        void* q = FUN_00401020(0);
        FUN_005f0ca0(q);
    }
}

// @ 0x00ed14c0
void Obj14C0::f(int* param)
{
    int* p = *(int**)((char*)this + 0x4c);
    if (p != 0) {
        ((FV_i)(*(void***)p)[0x24 / 4])(p, (int)param);
        FUN_00ece300((char*)this);
    }
    *(int*)((char*)this + 0x18) = param[0];
    *(int*)((char*)this + 0x1c) = param[1];
    *(int*)((char*)this + 0x20) = param[2];
}

// @ 0x00ed1500
unsigned char FUN_00ed1500(void)
{
    return *(unsigned char*)(*(int*)(*(int*)((char*)g_16c7aa4 + 0x74) + 0x10) + 0x14c);
}

// @ 0x00ed1550
void __fastcall FUN_00ed1550(void* self)
{
    Obj1550* o = (Obj1550*)self;
    int* ids = (int*)((Fn00f3bcb0*)*(void**)((char*)g_16c7aa4 + 0x74))->fn();
    Range3 one;
    Range3 two;
    Range3 list;
    one.p0 = (void*)ids[0];
    one.p1 = (void*)ids[1];
    one.p2 = (void*)ids[2];
    two.p0 = (void*)ids[0];
    two.p1 = (void*)ids[1];
    two.p2 = (void*)ids[2];
    list.p0 = (void*)0x1667bac;
    list.p1 = (void*)0x1667bac;
    list.p2 = (void*)0x1667bae;
    FUN_00eeea50(&one, &list);
    ((FV_vi)(*(void***)self)[0x30 / 4])(self, (int)&one);
    ((FV_vii)(*(void***)self)[0x38 / 4])(self, (int)&one, 0);
    one.p1 = (void*)0x2f7d0004;
    ((FV_vii)(*(void***)self)[0x3c / 4])(self, (int)&one, 0);
    ((FV_vi)(*(void***)self)[0x40 / 4])(self, (int)list.p0);
    void* key = &two;
    void* prof = ((Fn004df550*)FUN_00401090(key))->fn(key);
    ((Fn00ecf000*)self)->fn();
    ((Fn00ecf940*)self)->fn();
    ProfileSlot* p = (ProfileSlot*)*(void**)((char*)*(void**)((char*)g_16c7aa4 + 0x74) + 0x10);
    unsigned char on = p->b175;
    void* w = ((ILayout*)o->layout)->FindWindowByID(0x770b540, 1);
    if (w != 0) {
        void* e = (void*)((FV_i)(*(void***)w)[0xc / 4])(w, 0x8ed27e7a);
        if (e != 0)
            ((FV_vii)(*(void***)e)[0x28 / 4])(e, 4, (int)on);
    }
    float f = -1.0f;
    int units = 0;
    if (prof != 0) {
        float v = FUN_004d12a0(FUN_00c028b0(prof, 1)) + ((SpeciesProfile*)prof)->f56c;
        int i = (int)v;
        if ((float)i < v)
            i++;
        units = i;
        f = (float)i * p->f170;
    }
    int n = (int)f;
    if ((float)n < f)
        n++;
    char text[0x20];
    FUN_00881ae0(n, n >> 31, text, 0x20);
    FUN_00edf830(((ILayout*)o->layout)->FindWindowByID(0x7c8b2a0, 1), p->f170, 0, p->b174,
                 (void*)0x7c8d5f4, text);
    if (prof != 0) {
        ((bool (__thiscall*)(void*, int, float))FUN_00ed13e0)(self, 0x18ac46e, g_13ec4d0);
        ((bool (__thiscall*)(void*, int, float))FUN_00ed13e0)(self, 0x73a95a0, g_13ec4d0);
        float v2 = ((SpeciesProfile*)prof)->f644;
        int j = (int)v2;
        if ((float)j < v2)
            j++;
        void* w2 = ((ILayout*)o->layout)->FindWindowByID(0x4d039a8, 1);
        if (w2 != 0) {
            FUN_00881ae0(units, units >> 31, text, 0x20);
            ((FV_vi)(*(void***)w2)[0x80 / 4])(w2, (int)text);
        }
        void* w3 = ((ILayout*)o->layout)->FindWindowByID(0x73a9570, 1);
        if (w3 != 0) {
            FUN_00881ae0(j, j >> 31, text, 0x20);
            ((FV_vi)(*(void***)w3)[0x80 / 4])(w3, (int)text);
        }
    }
    void* ms = FUN_0067dcc0();
    ((void (__thiscall*)(void*, int, int, int))(*(void***)ms)[0x14 / 4])(ms, (int)0x796d3a0, -2, 0);
    o->b68 = 1;
    unsigned count = (unsigned)((char*)list.p2 - (char*)list.p0) & 0xfffffffeu;
    if (count > 2 && list.p0 != 0)
        EA_Free(list.p0);
}

// @ 0x00ed1880
bool __fastcall FUN_00ed1880(Container* self, int* unused, void* arg)
{
    void*  mainWin;
    void*  item;
    void*  catDesc;
    void*  itemUI;
    void*  pageWin;
    void*  pageBase;
    float* r;
    float  w, h;

    // store arg into self->hB (slot 0 AddRef / slot 1 Release)
    {
        void* old = self->hB;
        if (arg != old) {
            if (arg != 0 && *(void***)arg != 0)
                ((FV_v)(*(void***)arg)[0])(arg);
            self->hB = arg;
            if (old != 0)
                ((FV_v)(*(void***)old)[4 / 4])(old);
        }
    }

    mainWin = FUN_00810620(FUN_00805070((int)0x8d0f4fb));
    if (self->hB == 0) {
        void* old = self->hB;
        if (mainWin != old) {
            if (mainWin != 0)
                ((FV_v)(*(void***)mainWin)[0])(mainWin);
            self->hB = mainWin;
            if (old != 0)
                ((FV_v)(*(void***)old)[4 / 4])(old);
        }
    }

    {
        void* alloc = EAAllocate(0x54, "Simulator/Scenario/AvatarPaletteItem", 0, 0, 0, 0);
        if (alloc == 0) {
            item = 0;
        } else {
            item = FUN_005c66a0();
            if (item != 0)
                ((FV_v)(*(void***)item)[4 / 4])(item);
        }
    }

    {
        int key[4];
        key[0] = (int)0xd8c67022;
        key[1] = (int)0x00b1b104;
        key[2] = (int)0xd87454e6;
        key[3] = 0;
        if (FUN_005c6810(item, key, 0, 0) == 0 || self->hB == 0) {
            FUN_005c6710(item);
            if (item != 0)
                ((FV_v)(*(void***)item)[8 / 4])(item);
            return false;
        }
    }

    itemUI = FUN_009512d0(0xa0, 8, "Scenario/AvatarPaletteItemUI", FUN_009512c0());
    if (itemUI != 0)
        itemUI = FUN_00ed1250(itemUI);
    else
        itemUI = 0;
    self->hItemUI = itemUI;
    ((FV_v)(*(void***)itemUI)[4 / 4])(itemUI);

    catDesc = EAAllocate(0x34, "Editor", 0, 0, 0, 0);
    if (catDesc == 0) {
        catDesc = 0;
    } else {
        catDesc = FUN_005c64e0();
        if (catDesc != 0)
            ((FV_v)(*(void***)catDesc)[4 / 4])(catDesc);
    }
    {
        void* p = *(void**)((char*)catDesc + 8);
        if (p != 0) {
            *(void**)((char*)catDesc + 8) = 0;
            int rc = *(int*)((char*)p + 4) - 1;
            *(int*)((char*)p + 4) = rc;
            if (rc == 0) {
                *(int*)((char*)p + 4) = 1;
                ((FV_v)(*(void***)p)[0])(p);
            }
        }
        p = *(void**)((char*)catDesc + 0x10);
        if (p != 0) {
            *(void**)((char*)catDesc + 0x10) = 0;
            ((FV_v)(*(void***)p)[4 / 4])(p);
        }
    }
    *(uint16_t*)((char*)catDesc + 0x18) = 0x268a;

    pageWin = FUN_009512d0(0x20c, 4, "Scenario/AvatarPaletteItemUI/page_win", FUN_009512c0());
    pageBase = 0;
    if (pageWin != 0) {
        void* created = FUN_00962a10(pageWin);
        if (created != 0)
            pageBase = (char*)created + 4;
    }

    {
        void** vt = *(void***)pageBase;
        void*  id = ((FV_v)(*(void***)self->hB)[0x38 / 4])(self->hB);
        ((FV_p)(vt[0x6c / 4]))(pageBase, id);
        ((FV_ii)(*(void***)pageBase)[0x7c / 4])(pageBase, 0x10, 1);
        ((FV_p)(*(void***)self->hB)[0xd8 / 4])(self->hB, pageBase);
    }

    {
        float box[4];
        box[0] = 0.0f;
        box[1] = 0.0f;
        box[2] = 100.0f;
        box[3] = 100.0f;
        ((FV_p)(*(void***)pageBase)[0x6c / 4])(pageBase, box);
    }

    r = (float*)((FV_v)(*(void***)pageBase)[0x38 / 4])(pageBase);
    w = r[0];
    h = r[2];
    {
        float* q = (float*)((FV_v)(*(void***)self->hB)[0x38 / 4])(self->hB);
        ((FV_ii)(*(void***)pageBase)[0x64 / 4])(pageBase, 0, 0);
    }

    {
        void* old = self->hB;
        if (pageBase != old) {
            ((FV_v)(*(void***)pageBase)[0])(pageBase);
            self->hB = pageBase;
            if (old != 0)
                ((FV_v)(*(void***)old)[4 / 4])(old);
        }
    }

    {
        void* qi;
        if (self->hItemUI == 0)
            qi = 0;
        else
            qi = ((FV_i_s00ed_1880)(*(void***)((char*)self->hItemUI + 8))[0xc / 4])(
                     (char*)self->hItemUI + 8, 0x722e9c1);
        ((FV_fff)(*(void***)((char*)qi + 0x24))[4 / 4])((char*)qi + 0x24, pageBase, pageBase);
    }

    FUN_005f2290(0);

    {
        void* qi;
        void* old;
        if (self->hItemUI == 0)
            qi = 0;
        else
            qi = ((FV_i_s00ed_1880)(*(void***)((char*)self->hItemUI + 8))[0xc / 4])(
                     (char*)self->hItemUI + 8, 0x722e9c1);
        old = *(void**)((char*)qi + 0x40);
        if (old != self->hA) {
            if (old != 0)
                ((FV_v)(*(void***)old)[0])(old);
            void* prev = self->hA;
            self->hA = old;
            if (prev != 0)
                ((FV_v)(*(void***)prev)[4 / 4])(prev);
        }
    }

    if (self->hA != 0) {
        ((FV_v)(*(void***)catDesc)[8 / 4])(catDesc);
        self->hAvatarUI = (void*)FUN_00ed1120(FUN_00ed0c30, 0, self, 0x14, 0, 2, 0);
        {
            void* ms = FUN_0067dcc0((char*)self + 8, (void*)0x15ac038, 2);
            FUN_004db620(ms, (char*)self + 8, (void*)0x15ac038, 2);
        }
        if (unused != 0)
            ((FV_v)(*(void***)unused)[8 / 4])(unused);
        return true;
    }

    {
        void* qi;
        if (self->hItemUI == 0)
            qi = 0;
        else
            qi = ((FV_i_s00ed_1880)(*(void***)((char*)self->hItemUI + 8))[0xc / 4])(
                     (char*)self->hItemUI + 8, 0x722e9c1);
        ((FV_v)(*(void***)((char*)qi + 0x24))[8 / 4])((char*)qi + 0x24);
    }
    ((FV_v)(*(void***)self->hItemUI)[8 / 4])(self->hItemUI);
    self->hItemUI = 0;
    ((FV_v)(*(void***)catDesc)[8 / 4])(catDesc);
    if (unused != 0)
        ((FV_v)(*(void***)unused)[8 / 4])(unused);
    return false;
}

// @ 0x00f0d3f0
float const SP::cSPSwatch::GetViewportMaxScale() const
{
    return 1.0f;
}
