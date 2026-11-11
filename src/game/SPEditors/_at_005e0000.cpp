// src/game/SPEditors/_at_005e0000.cpp -- migrated from slice(s) s005ef440, s005ee480, s005ed750, s005ecf80, s005e5d40, s005e4db0, s005e16c0, s005e0930, s005dfbb0 by tools/migrate/rewrite.py
// Object file: SPEditors/_at_005e0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cAppModeEditorBase.h"
#include "SP/cPropertyList.h"
#include "SP/cSPEditorUI.h"
#include "cSPUILayout.h"
#include "SP/cString.h"
#include "EA/Variant.h"
#include "SP/cSPEditorVerbIconTray.h"
#include <math.h>
#include "SP/cPropertyManager.h"
#include "SP/cSPPalettePage.h"
#include "SP/cSPVerbTrayCollection.h"
#include <intrin.h>
#include <new>
#include "eastl/allocator.h"
#include "SP/cSPEditorVerbIconData.h"
#include "cSPUIPropertyLayout.h"
#include "EA/UTFWin/IWindow.h"
#include "SP/cSPPaletteItemRollover.h"
#include "EA/Messaging/AutoHandler.h"
#include "EA/Messaging/IHandler.h"
#include "EA/Stopwatch.h"
#include "SP/cISPPaletteItemUI.h"
#include "SP/cSPPaletteInfo.h"
#include "SP/cSPPaletteItem.h"
#include "SP/cSPPaletteItemUI.h"
#include "SP/cSPPaletteItemUIOneClickPaint.h"
#include "SP/cSPPaletteItemUISelectable.h"
#include "SP/cSPSwatch.h"
#include "SP/cCollectableItems.h"
#include "SP/cICameraManager.h"
#include "SP/cISPCreatureAnimWorld.h"
#include "hkBaseObject.h"
#include "hkBool.h"
#include "hkReferencedObject.h"

// ---- items of slice s005dfbb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct Key {
  uint32_t mInstance;
  uint32_t mType;
  uint32_t mGroup;
};
}
namespace SP {
class IWindow;
}
namespace SP {
class cSPUILayout {
 public:
  virtual void v0();
  virtual int AddRef();    // +0x04
  virtual int Release();   // +0x08
  cSPUILayout();                                         // 0x00810000
  ~cSPUILayout();                                        // 0x00811fe0
  bool IsVisible();                                      // 0x00810070
  bool Init(const Key& key, bool visible, uint32_t parentID);   // 0x008120d0
  bool SetParentWin(IWindow* parent, bool visible, uint32_t id);  // 0x008121b0
  IWindow* FindWindowByID(uint32_t id, bool recursive);   // 0x008105b0
  void Shutdown(bool destroyWindows);  // 0x00811ad0
  char mPad04[0x14];                   // +0x04 .. +0x17
};
}
namespace SP {
template <typename T>
class AutoRefCount {
 public:
  T* mpObject;
  AutoRefCount() : mpObject(0) {}
  AutoRefCount(T* p) : mpObject(p) { if (p) p->AddRef(); }
  AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount() { if (mpObject) mpObject->Release(); }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};
}
namespace SP {
void operator delete[](void* p);  // 0x00f47380
}
namespace SP {
template <class T>
class vector {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~vector() {
    T* last = mpEnd;
    T* first = mpBegin;
    for (; first < last; ++first) first->~T();
    if (mpBegin && ((int*)mpBegin)[-1] != 0) operator delete[](mpBegin);
  }
  int size() const { return (int)(mpEnd - mpBegin); }
  T& operator[](int i) { return mpBegin[i]; }
  T* begin() { return mpBegin; }
  T* end() { return mpEnd; }
  T* erase(T* first, T* last);  // 0x005c2170
  void grow(T* pos, const T* value);  // 0x005c8480
  void push_back(const T& value) {
    if (mpEnd < mpCapacity) {
      T* slot = mpEnd++;
      slot->mpObject = value.mpObject;
      if (slot->mpObject) slot->mpObject->AddRef();
    } else {
      grow(mpEnd, &value);
    }
  }
};
}
namespace SP {
class cRefCounted {
 public:
  cRefCounted() : mnRefCount(0) {}
  virtual ~cRefCounted() {}
  int mnRefCount;
};
}
namespace SP {
class cSPRolloverModelDataBase {
 public:
  virtual ~cSPRolloverModelDataBase() {}
};
}
namespace SP {
class cSPRolloverModelData : public cSPRolloverModelDataBase, public cRefCounted {
 public:
  cSPRolloverModelData(const Key& modelKey, const Key& itemKey, uint32_t layoutID,
                       uint32_t layoutGroup, uint32_t textID);  // 0x005e0370
  virtual ~cSPRolloverModelData();                              // 0x005e0440

  Key mModelKey;      // +0x0c
  Key mItemKey;       // +0x18
  Key mLayoutKey;     // +0x24
  Key mGroupKey;      // +0x30
  vector<AutoRefCount<cSPUILayout> > mItems;  // +0x3c
  uint32_t mUnk48;    // +0x48
  uint32_t mUnk4c;    // +0x4c
  uint32_t mUnk50;    // +0x50
  uint32_t mTextID;   // +0x54
};
}
#define PV(n) virtual void _pv##n();
namespace SP {
struct Rect {
  float x1, y1, x2, y2;
  Rect() {}
  Rect(const Rect& o) : x1(o.x1), y1(o.y1), x2(o.x2), y2(o.y2) {}
};
}
namespace SP {
class IWindow {
 public:
  virtual int AddRef();   // +0x00
  virtual int Release();  // +0x04
  PV(2)
  virtual IWindow* Cast(uint32_t typeID);  // +0x0c
  PV(4) PV(5) PV(6)
  virtual void SetVisible(bool visible);   // +0x1c
  PV(8) PV(9)
  virtual uint32_t GetFlags();             // +0x28
  PV(11) PV(12) PV(13)
  virtual Rect& GetArea();                 // +0x38
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26)
  virtual void SetLayoutArea(const Rect& area);  // +0x6c
  PV(28)
  virtual void SetSize(float w, float h);  // +0x74
  PV(30)
  virtual void SetFlag(int flag, bool value);  // +0x7c
  virtual void SetText(const wchar_t* text);   // +0x80
  PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43)
  PV(44) PV(45) PV(46) PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53)
  virtual void AddWindow(IWindow* child);      // +0xd8
  PV(55) PV(56) PV(57) PV(58) PV(59)
  virtual IWindow* FindWindowByID(uint32_t id, bool recursive);  // +0xf0
};
}
// ---- items of slice s005dfbb0 end

// ---- items of slice s005e0930 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kRealZero;                              // 0x01485378
struct RefObj {
    virtual void v0();
    virtual void v1();
    virtual void Release();     // +0x08
    void Shutdown(int);
};
struct BaseB { virtual void vb(); void ShutdownBase(); };
struct CShut : BaseB {
    char pad[0x50];
    RefObj* m54;                // +0x54
    void Shutdown();
};
struct BaseA { BaseA(); virtual void v0(); };
struct IBaseB { virtual void vb(); };
struct VerbTray : BaseA, IBaseB {
    char pad08[0x4c];      // +0x08..+0x53
    uint32_t z54[12];      // +0x54..+0x83
    char pad84[0xc];       // +0x84..+0x8f
    float f90[6];          // +0x90..+0xa4
    VerbTray();
};
namespace Math {
struct Rectangle {
    float x1, y1, x2, y2;
    Rectangle() {}
    Rectangle(const Rectangle& r) : x1(r.x1), y1(r.y1), x2(r.x2), y2(r.y2) {}
    Rectangle& operator=(const Rectangle& r) {
        x1 = r.x1; y1 = r.y1; x2 = r.x2; y2 = r.y2;
        return *this;
    }
    float Width() const { return x2 - x1; }
    float Height() const { return y2 - y1; }
};  // namespace Math
}
namespace eastl {
class sp_vector_allocator_s005e_0930 {
 public:
    uint32_t mData[2];
    sp_vector_allocator_s005e_0930() {}
};
}
namespace eastl {
template <typename T>
class vector_s005e_0930 {
 public:
    T* mpBegin;                       // +0x0
    T* mpEnd;                         // +0x4
    T* mpCapacity;                    // +0x8
    sp_vector_allocator_s005e_0930 mAllocator;   // +0xc
    vector_s005e_0930() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
    T& operator[](unsigned int i) { return mpBegin[i]; }
    T* erase(T* first, T* last) { (void)first; (void)last; return first; }
};
}
template <typename T>
class AutoRefCount_s005e_0930 {
 public:
    T* mpObject;
    AutoRefCount_s005e_0930() : mpObject(0) {}
    AutoRefCount_s005e_0930(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount_s005e_0930(const AutoRefCount_s005e_0930& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount_s005e_0930() { if (mpObject) mpObject->Release(); }
    AutoRefCount_s005e_0930& operator=(T* pObject) {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject) pObject->AddRef();
            mpObject = pObject;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
    T** AsOutParam() {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
struct ColorRGBA {
    ColorRGBA(const ColorRGBA& c) : mR(c.mR), mG(c.mG), mB(c.mB), mA(c.mA) {}
    float mR, mG, mB, mA;
};
namespace App {
struct Property {
    char pad[0x12];
    uint16_t mnType;  // +0x12
};  // namespace App
}
class cPropertyList {
 public:
    virtual int AddRef();
    virtual int Release();
virtual void q08();
virtual void q0c();
virtual void q10();
virtual void q14();
virtual void q18();
    virtual bool HasProperty(uint32_t id);                                 // +0x1c
    virtual void q20();
    virtual bool GetProperty(uint32_t id, App::Property*& result);          // +0x24
};
class IPropertyManager {
 public:
virtual void m00();
virtual void m04();
virtual void m08();
virtual void m0c();
virtual void m10();
virtual void m14();
virtual void m18();
virtual void m1c();
virtual void m20();
virtual void m24();
    virtual void m28();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, cPropertyList** out);  // +0x2c
};
IPropertyManager* PropertyManager();                                       // 0x0067de30
bool GetPropertyAsKeyInstance(cPropertyList* list, uint32_t id, uint32_t* value);  // 0x006a12a0
bool GetPropertyArrayKey(cPropertyList* list, uint32_t id, int* count, void** keys);  // 0x006a0ae0
class cString {
 public:
    cString();                        // 0x006b5060
    ~cString();                       // 0x006b5240
    const wchar_t* c_str() const;     // 0x006b55c0
    uint32_t mData[5];
};
bool GetPropertyAsText(cPropertyList* list, uint32_t id, cString& out);   // 0x006a1360
class IEditorWidget {
 public:
    virtual int AddRef();                                  // +0x00
    virtual int Release();                                 // +0x04
    virtual void w08();                                    // +0x08
    virtual void w0c();                                    // +0x0c
    virtual void w10();                                    // +0x10
    virtual void w14();                                    // +0x14
    virtual void w18();                                    // +0x18
    virtual void w1c();                                    // +0x1c
    virtual void w20();                                    // +0x20
    virtual void Update(uint32_t dt);                      // +0x24
    virtual void w28();                                    // +0x28
    virtual void w2c();                                    // +0x2c
    virtual IEditorWidget* GetWindow();                    // +0x30
    virtual void w34();                                    // +0x34
    virtual const Math::Rectangle& GetArea();              // +0x38
    virtual void w3c();                                    // +0x3c
    virtual void w40();                                    // +0x40
    virtual void w44();                                    // +0x44
    virtual void w48();                                    // +0x48
    virtual void w4c();                                    // +0x4c
    virtual void w50();                                    // +0x50
    virtual void w54();                                    // +0x54
    virtual void w58();                                    // +0x58
    virtual void SetColor(uint32_t color);                 // +0x5c
    virtual void w60();                                    // +0x60
    virtual void w64();                                    // +0x64
    virtual void w68();                                    // +0x68
    virtual void SetArea(const Math::Rectangle& area);     // +0x6c
    virtual void w70();                                    // +0x70
    virtual void w74();                                    // +0x74
    virtual void w78();                                    // +0x78
    virtual void SetEnabled(int flag, bool enabled);       // +0x7c
    void SetVerbIconList(void* list);                      // 0x005e8470
};
struct TrayData {
    char pad00[0x20];
    float mScale;        // +0x20
    char pad24[8];
    ColorRGBA mColor;    // +0x2c
};
class IVerbTray {
 public:
virtual void t00();
virtual void t04();
virtual void t08();
virtual void t0c();
virtual void t10();
virtual void t14();
virtual void t18();
virtual void t1c();
virtual void t20();
virtual void t24();
virtual void t28();
virtual void t2c();
    virtual IEditorWidget* GetWindow();                    // +0x30
    TrayData* GetData();                                   // 0x00a42730 (inlined getter)
    void SetVerbIconList(void* list);                      // 0x005e8470
    void SetMaxArea(const Math::Rectangle& area);          // 0x005e63b0
};
uint32_t ColorRGBAToU32(const ColorRGBA* color);           // 0x004580c0
struct ILegacyRef {
    virtual void l00();
    virtual void l04();
    virtual int Release();                                 // +0x08
};
class TrayPrimary {
 public:
    virtual int AddRef();                                  // +0x00
    virtual int Release();                                 // +0x04
    virtual void p08();                                    // +0x08
    virtual void* Cast(uint32_t type);                     // +0x0c
    virtual void p10();                                    // +0x10
    virtual void SetList(void* list);                      // +0x14
    virtual void Shutdown();                               // +0x18
    virtual void Update(uint32_t dt);                      // +0x1c
    virtual void p20();                                    // +0x20
    virtual void p24();                                    // +0x24
    virtual void Layout();                                 // +0x28
    virtual void p2c();                                    // +0x2c
};
class TrayRefCount {
 public:
    virtual void r00();                                    // +0x00
    virtual int AddRef();                                  // +0x04
    virtual int Release();                                 // +0x08
    virtual void r0c();                                    // +0x0c
    int mRefCount;
};
class TrayBase : public TrayPrimary, public TrayRefCount {
 public:
    ~TrayBase();                                           // 0x00605cb0
    eastl::vector_s005e_0930<IEditorWidget*> mVerbIcons;              // +0x0c
    AutoRefCount_s005e_0930<IEditorWidget> mWinParent;                // +0x20
    AutoRefCount_s005e_0930<IEditorWidget> mWinVerbTray;              // +0x24
    char mPad28[0x54 - 0x28];                              // +0x28..+0x53
};
class VehicleTray : public TrayBase {
 public:
    ~VehicleTray();                                        // 0x005e0d80
    void Update(uint32_t dt);                              // 0x005e0e80
    void SetList(void* list);                              // 0x005e1020
    virtual void Layout();                                 // 0x005e12c0
    void LayoutAbilities(IEditorWidget* window, int flag); // 0x005e0930

    AutoRefCount_s005e_0930<ILegacyRef> m54;                          // +0x54
    AutoRefCount_s005e_0930<IEditorWidget> m58;                       // +0x58
    AutoRefCount_s005e_0930<IEditorWidget> m5c;                       // +0x5c
    AutoRefCount_s005e_0930<IEditorWidget> m60;                       // +0x60
    AutoRefCount_s005e_0930<IEditorWidget> m64;                       // +0x64
    AutoRefCount_s005e_0930<IEditorWidget> m68;                       // +0x68
    AutoRefCount_s005e_0930<IEditorWidget> m6c;                       // +0x6c
    AutoRefCount_s005e_0930<IEditorWidget> m70;                       // +0x70
    AutoRefCount_s005e_0930<IEditorWidget> m74;                       // +0x74
    AutoRefCount_s005e_0930<IEditorWidget> m78;                       // +0x78
    AutoRefCount_s005e_0930<IEditorWidget> m7c;                       // +0x7c
    AutoRefCount_s005e_0930<IEditorWidget> m80;                       // +0x80
    IVerbTray* m84;                                        // +0x84
    IVerbTray* m88;                                        // +0x88
    IVerbTray* m8c;                                        // +0x8c
    float m90;                                             // +0x90
    float m94;                                             // +0x94
    float m98;                                             // +0x98
    float m9c;                                             // +0x9c
    float ma0;                                             // +0xa0
    float ma4;                                             // +0xa4
    Math::Rectangle mMaxArea;                              // +0xa8
    Math::Rectangle mGutters;                              // +0xb8
};
struct ResourceKey {
    uint32_t instanceID;   // +0x00
    uint32_t typeID;       // +0x04
    uint32_t groupID;      // +0x08
};
class IResource {
 public:
    virtual int AddRef();                  // +0x00
    virtual int Release();                 // +0x04
    virtual void r08();                    // +0x08
    virtual void* Cast(uint32_t type);     // +0x0c
};
namespace EA {
namespace ResourceMan {
class IResourceManager {
 public:
virtual void m00();
virtual void m04();
virtual void m08();
    virtual bool GetResource(const ResourceKey* key, IResource** out, uint32_t unk0,
                             uint32_t unk1, uint32_t unk2, uint32_t unk3);  // +0x0c
};
}
}
namespace EA {
namespace ResourceMan {
IResourceManager* GetManager();            // 0x0067dcd0
}
}
struct AbilityRecord {
    char pad00[0x18];
    float m18;             // +0x18
    char pad1c[8];         // +0x1c..+0x23
    uint32_t m24;          // +0x24
    char pad28[0x2c];      // +0x28..+0x53
    cString m54;           // +0x54
    char pad68[0x28];      // +0x68..+0x8f
    uint32_t m90;          // +0x90
    char pad94[0x20];      // +0x94..+0xb3
    ResourceKey mb4;       // +0xb4
};
void ApplyOwnerEntries(void** entries, void* owner);                               // 0x00433210
void CollectAbilityRecords(void* list, eastl::vector_s005e_0930<void*>* out, void** entries);  // 0x004e7610
class AbilityLayoutData {
 public:
    float LayoutLine(IEditorWidget* window, const ResourceKey* key, float startY,
                     uint32_t value, const ResourceKey* subKey, cString* text,
                     float number);                        // 0x005e04d0
    void LayoutAbilities(IEditorWidget* window, bool alt);  // 0x005e0930

    ResourceKey mVehicleKey;              // +0x0c
    ResourceKey mTypeKey;                 // +0x18
    ResourceKey mLineKey;                 // +0x24
    ResourceKey mRowKey;                  // +0x30
    eastl::vector_s005e_0930<void*> mPages;          // +0x3c
    char mPad4c[8];                       // +0x4c..+0x53
    uint32_t mAbilityPropId;              // +0x54
};
// ---- items of slice s005e0930 end

// ---- items of slice s005e16c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char kEditorAllocName[];   // "Editor" @ 0x013eb430
namespace EA {
namespace ResourceMan {
struct Key_s005e_16c0 {
    unsigned int mType;
    unsigned int mGroup;
    unsigned int mInstance;
};
}
}
namespace EA {
namespace UTFWin {
class IWindow_s005e_16c0 {
 public:
    virtual int AddRef();                       // +0x00
    virtual int Release();                      // +0x04
    PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    virtual void SetPage(IWindow_s005e_16c0* page, int b); // +0x28
    PV(11) PV(12) PV(13)
    virtual const float* GetArea();             // +0x38
    PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26)
    virtual void SetArea(const float* r);       // +0x6c
    PV(28) PV(29) PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39)
    PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49) PV(50) PV(51)
    PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58) PV(59)
    virtual IWindow_s005e_16c0* FindChild(unsigned int id, int b);   // +0xf0
};
}
}
namespace EA {
namespace UTFWin {
class IRefCounted2 {
 public:
    virtual int AddRef();                       // +0x00
    virtual void _s1();                         // +0x04
    virtual int Release();                      // +0x08
};
}
}
template <typename T>
class AutoRefCount_s005e_16c0 {
 public:
    T* mpObject;
    AutoRefCount_s005e_16c0() : mpObject(0) {}
    ~AutoRefCount_s005e_16c0() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    AutoRefCount_s005e_16c0& operator=(T* pObject) {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject) pObject->AddRef();
            mpObject = pObject;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
};
namespace SP {
struct cVerbIconInterpolationValue_s005e_16c0 {          // 0x1c bytes
    float mTargetValue;      // +0x00
    float mCurrentValue;     // +0x04
    float mElapsedTime;      // +0x08
    float mInitialValue;     // +0x0c
    float mDuration;         // +0x10
    float mOverShoot;        // +0x14
    float mDampenPercent;    // +0x18
    void Init(float a, float b, float c, float d, float e);  // 0x005e1c80 (SP::cVerbIconInterpolationValue::Init)
    int IsAtTarget();  // 0x005e1cd0 (SP::cVerbIconInterpolationValue::IsAtTarget)
    void Update(float dt);                   // @ 0x005e1d00
};
}
namespace SP {
struct cVerbIconMiddleInterpolationValue_s005e_16c0 {    // 0x20 bytes
    float mEndValue;         // +0x00
    float mMiddleValue;      // +0x04
    float mCurrentValue;     // +0x08
    float mElapsedTime;      // +0x0c
    float mInitialValue;     // +0x10
    float mMiddleStart;      // +0x14
    float mMiddleEnd;        // +0x18
    float mDuration;         // +0x1c
    void Update(float dt);                   // @ 0x005e1e90
};
}
namespace SP {
struct cVerbIconLinearInterpolationValue_s005e_16c0 {    // 0x14 bytes
    float mTargetValue;      // +0x00
    float mCurrentValue;     // +0x04
    float mElapsedTime;      // +0x08
    float mInitialValue;     // +0x0c
    float mDuration;         // +0x10
};
}
namespace SP {
struct cVerbIconOscillatingAlpha_s005e_16c0 {            // 0x18 bytes
    float mTargetValue;      // +0x00
    float mCurrentValue;     // +0x04
    float mElapsedTime;      // +0x08
    float mDuration;         // +0x0c
    float mSpeed;            // +0x10
    unsigned int mColor;     // +0x14
};
}
using SP::cVerbIconInterpolationValue_s005e_16c0;
using SP::cVerbIconMiddleInterpolationValue_s005e_16c0;
namespace EA {
namespace Trace {
class ITracerBase {
 public:
    ~ITracerBase() {}
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
};
}
}
namespace Simulator {
class cContentValidationSummarizer {
 public:
    ~cContentValidationSummarizer() {}
    virtual void v0();
    virtual void v1();
    int mRefCount;          // +0x08
};
}
namespace SP {
class cSPUILayout_s005e_16c0 {
 public:
    virtual int AddRef();
    virtual int Release();
    bool Init(const EA::ResourceMan::Key_s005e_16c0& key, bool b, unsigned int n);   // 0x008120d0
    bool SetParentWin(EA::UTFWin::IWindow_s005e_16c0* p, bool b, unsigned int n);    // 0x008121b0
    EA::UTFWin::IWindow_s005e_16c0* FindWindowByID(unsigned int id, bool b);         // 0x008105b0
};
}
namespace SP {
class cSPEditorVerbIconTray_s005e_16c0 : public EA::UTFWin::IWindow_s005e_16c0 {
 public:
    float GetHeight();                                                    // 0x005e6390
};
}
namespace SP {
class cSPEditorVerbIcon_s005e_16c0
    : public EA::Trace::ITracerBase, public Simulator::cContentValidationSummarizer {
 public:
    // ---- virtuals (slot 9 == +0x24, slot 18 == +0x48) ----
    virtual void LayoutInit(EA::ResourceMan::Key_s005e_16c0 key, int a, int b);      // +0x24 0x005e2470
    virtual void Slot10();                                                // +0x28
    virtual void Slot11();
    virtual void Slot12();
    virtual void SetLevel(float level);                                   // +0x34 0x005e2ec0
    virtual void Slot14();
    virtual void Slot15();
    virtual void Slot16();
    virtual void Slot17();
    virtual void SetVerbID(unsigned int id);                              // +0x48

    // ---- members ----
    AutoRefCount_s005e_16c0<EA::UTFWin::IRefCounted2> mWin0c;    // +0x0c
    AutoRefCount_s005e_16c0<EA::UTFWin::IWindow_s005e_16c0> mWinRoot;  // +0x10
    AutoRefCount_s005e_16c0<EA::UTFWin::IWindow_s005e_16c0> mWinIcon;  // +0x14
    AutoRefCount_s005e_16c0<EA::UTFWin::IWindow_s005e_16c0> mWinLevel; // +0x18
    AutoRefCount_s005e_16c0<EA::UTFWin::IWindow_s005e_16c0> mWinHighlight;      // +0x1c
    AutoRefCount_s005e_16c0<EA::UTFWin::IWindow_s005e_16c0> mWinShortcutText;   // +0x20
    AutoRefCount_s005e_16c0<EA::UTFWin::IWindow_s005e_16c0> mWin24;             // +0x24
    AutoRefCount_s005e_16c0<EA::UTFWin::IWindow_s005e_16c0> mWinFlashingGlow;   // +0x28
    AutoRefCount_s005e_16c0<EA::UTFWin::IWindow_s005e_16c0> mWinChargeDial;     // +0x2c
    AutoRefCount_s005e_16c0<EA::UTFWin::IWindow_s005e_16c0> mWinLevelPips[5];   // +0x30 .. +0x44
    AutoRefCount_s005e_16c0<EA::UTFWin::IWindow_s005e_16c0> mWin44;             // +0x44
    unsigned int mPad48[3];                      // +0x48
    unsigned int mPad54[3];                      // +0x54
    unsigned int mUnk60;                         // +0x60
    int mState;                                  // +0x64
    unsigned char mB68;                          // +0x68
    unsigned char mB69;
    unsigned char mB6a;
    unsigned char mB6b;
    unsigned char mB6c;
    unsigned char mB6d;
    unsigned char mB6e;
    unsigned char mB6f;
    unsigned char mB70;
    unsigned char mB71;
    unsigned char mB72;
    unsigned char mB73;
    unsigned char mPad74[0x1c];                  // +0x74 .. +0x8f
    float mF90;                                  // +0x90
    float mF94;                                  // +0x94
    cVerbIconLinearInterpolationValue_s005e_16c0 mCharge;   // +0x98
    cVerbIconInterpolationValue_s005e_16c0 mScaleX;         // +0xac
    cVerbIconInterpolationValue_s005e_16c0 mScaleY;         // +0xc8
    cVerbIconLinearInterpolationValue_s005e_16c0 mLevel;    // +0xe4
    cVerbIconInterpolationValue_s005e_16c0 mUpgradeScale;   // +0xf8
    cVerbIconMiddleInterpolationValue_s005e_16c0 mUpgradeHighlightFade;   // +0x114
    cVerbIconMiddleInterpolationValue_s005e_16c0 mIconAlpha;              // +0x134
    float mF154;                                 // +0x154
    cVerbIconOscillatingAlpha_s005e_16c0 mFlashAlpha;       // +0x158
    AutoRefCount_s005e_16c0<EA::UTFWin::IWindow_s005e_16c0> mIconData; // +0x170
    AutoRefCount_s005e_16c0<EA::UTFWin::IWindow_s005e_16c0> mRollover; // +0x174
    unsigned int mBaseTextColor;                 // +0x178
    AutoRefCount_s005e_16c0<EA::UTFWin::IWindow_s005e_16c0> mCollectionID;   // +0x17c
    float mAspectRatio;                          // +0x180

    cSPEditorVerbIcon_s005e_16c0();
    ~cSPEditorVerbIcon_s005e_16c0();
    void SetFlag(char b);                        // @ 0x005e1fa0
    void Reset(int verbId, char b, char c);      // @ 0x005e23b0
    void SetIcon(EA::UTFWin::IWindow_s005e_16c0* p, EA::ResourceMan::Key_s005e_16c0 key, int a, int b);  // @ 0x005e1b70
};
}
namespace SP {
class cSPPalettePage_s005e_16c0 : public cSPEditorVerbIconTray_s005e_16c0 {
 public:
    void SetParent(EA::UTFWin::IWindow_s005e_16c0* w, int b);      // +0x28 (slot 10)
};
}
namespace SP {
class cSPVerbTrayCollection_s005e_16c0 {
 public:
    void InitTraysBase(EA::ResourceMan::Key_s005e_16c0 key, const void* p, int n);   // 0x00605f90
    cSPPalettePage_s005e_16c0* GetPage(int index);                                   // 0x005c1ce0
    void InitTrays(EA::ResourceMan::Key_s005e_16c0 key, const void* p, int n);       // @ 0x005e16c0

    unsigned char mPad00[0x20];                 // +0x00 .. +0x1f
    AutoRefCount_s005e_16c0<EA::UTFWin::IWindow_s005e_16c0> mWin20;   // +0x20
    unsigned char mPad24[0x30];                 // +0x24 .. +0x53
    AutoRefCount_s005e_16c0<cSPUILayout_s005e_16c0> mLayout;          // +0x54
    AutoRefCount_s005e_16c0<EA::UTFWin::IWindow_s005e_16c0> mWin58;   // +0x58
    AutoRefCount_s005e_16c0<EA::UTFWin::IWindow_s005e_16c0> mWin5c;   // +0x5c
    AutoRefCount_s005e_16c0<EA::UTFWin::IWindow_s005e_16c0> mWin60;   // +0x60
    AutoRefCount_s005e_16c0<EA::UTFWin::IWindow_s005e_16c0> mWin64;   // +0x64
    AutoRefCount_s005e_16c0<EA::UTFWin::IWindow_s005e_16c0> mWin68;   // +0x68
    AutoRefCount_s005e_16c0<EA::UTFWin::IWindow_s005e_16c0> mWin6c;   // +0x6c
    AutoRefCount_s005e_16c0<EA::UTFWin::IWindow_s005e_16c0> mWin70;   // +0x70
    AutoRefCount_s005e_16c0<EA::UTFWin::IWindow_s005e_16c0> mWin74;   // +0x74
    AutoRefCount_s005e_16c0<EA::UTFWin::IWindow_s005e_16c0> mWin78;   // +0x78
    AutoRefCount_s005e_16c0<EA::UTFWin::IWindow_s005e_16c0> mWin7c;   // +0x7c
    AutoRefCount_s005e_16c0<EA::UTFWin::IWindow_s005e_16c0> mWin80;   // +0x80
    AutoRefCount_s005e_16c0<cSPPalettePage_s005e_16c0> mPage84;       // +0x84
    AutoRefCount_s005e_16c0<cSPPalettePage_s005e_16c0> mPage88;       // +0x88
    AutoRefCount_s005e_16c0<cSPPalettePage_s005e_16c0> mPage8c;       // +0x8c
    unsigned char mPad90[0x18];                 // +0x90 .. +0xa7
    float mHeight;                              // +0xa8
    float mArea[4];                             // +0xac .. +0xb8
};
}
namespace SP {
class cPropertyManager_s005e_16c0 {
 public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual void GetProperty(int a, int b, void* out);      // +0x2c
};
}
namespace SP {
cPropertyManager_s005e_16c0* PropertyManager_s005e_16c0();            // 0x0067de30
}
namespace SP {
void GetPropertyAsKey(void* property, unsigned int id, EA::ResourceMan::Key_s005e_16c0* out);   // 0x006a1250
}
namespace SP {
void* operator_new(unsigned int size, const char* name, int a, int b, int c, int d); // 0x00f473a0
}
namespace SP {
cSPUILayout_s005e_16c0* cConnectionDialog_ctor(void* mem);                                        // 0x00810000
}
// ---- items of slice s005e16c0 end

// ---- items of slice s005e4db0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
namespace eastl {
union EmptyString {
  uint32_t mUint32;
  wchar_t mEmpty16[1];
};
}
namespace eastl {
extern EmptyString gEmptyString;
}
namespace eastl {
class allocator_s005e_4db0 { public:
  allocator_s005e_4db0() {}
};
}
namespace eastl {
class wstring {
 public:
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  allocator_s005e_4db0 mAllocator;
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
  void assign(const wchar_t* b, const wchar_t* e);
  ~wstring() { DeallocateSelf(); }
};
}
void WStr_Format(eastl::wstring* out, const wchar_t* format, ...);
class cString_s005e_4db0 {
 public:
  cString_s005e_4db0();
  cString_s005e_4db0(uint32_t a, uint32_t b, const wchar_t* c);
  ~cString_s005e_4db0();
  const wchar_t* GetText() const;
  uint32_t mData[5];
};
namespace EA {
template <typename T>
class RefCountVTemplate_s005e_4db0 {
 public:
  RefCountVTemplate_s005e_4db0() : mRefCount(0) {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace EA {
namespace COM {
class IUnknown32_s005e_4db0 {
 public:
  virtual int AddRef();
  virtual int Release();
};  // namespace COM
}
}
namespace SP {
struct cPropertyList_s005e_4db0;
}
namespace SP {
struct cStringStorage {
  uint32_t mData[5];
};
}
namespace SP {
struct wstringStorage {
  void* mpBegin;
  void* mpEnd;
  void* mpCapacity;
  uint32_t mPad;  // empty allocator + padding (sizeof(eastl::wstring) == 0x10)
};
}
namespace SP {
class cSPEditorVerbIconData_s005e_4db0 : public EA::COM::IUnknown32_s005e_4db0, public EA::RefCountVTemplate_s005e_4db0<int> {
 public:
  cSPEditorVerbIconData_s005e_4db0();
  virtual ~cSPEditorVerbIconData_s005e_4db0();
  PV(2) PV(3) PV(4) PV(5)
  virtual void _pv6(int level);
  PV(7)
  bool mUseDescription;  // +0x0c
  bool mShowLevel;       // +0x0d
  bool mShowHotKey;      // +0x0e
  bool mShowZeroLevel;   // +0x0f
  bool mField10;         // +0x10
  bool mField11;         // +0x11
  short mPad12;          // +0x12
  int mField14;          // +0x14
  float mMaxLevel;       // +0x18
  float mType;           // +0x1c
  uint32_t mPad20;       // +0x20
  int mField24;          // +0x24
  int mField28;          // +0x28
  float mVec2c[4];       // +0x2c..0x3b
  int mField3c;          // +0x3c
  int mField40;          // +0x40
  int mField44;          // +0x44
  int mField48;          // +0x48
  bool mField4c;         // +0x4c
  bool mField4d;         // +0x4d
  short mPad4e;          // +0x4e
  int mField50;          // +0x50
  cStringStorage mName;         // +0x54..0x67
  wstringStorage mHotKeyString;  // +0x68..0x77
  uint32_t mHotKeyID;    // +0x78
  int mField7c;          // +0x7c
  int mField80;          // +0x80
  uint32_t mPad84;       // +0x84
  uint32_t mPad88;       // +0x88
  uint32_t mPad8c;       // +0x8c
  int mField90;          // +0x90
  int mField94;          // +0x94
  int mField98;          // +0x98
  int mField9c;          // +0x9c
  int mFieldA0;          // +0xa0
  int mFieldA4;          // +0xa4
  int mFieldA8;          // +0xa8
  int mFieldAc;          // +0xac
  int mFieldB0;          // +0xb0
  int mFieldB4;          // +0xb4
  int mFieldB8;          // +0xb8
  int mFieldBc;          // +0xbc
  cPropertyList_s005e_4db0* mConfig;  // +0xc0
  void Init(cPropertyList_s005e_4db0* config);  // 0x005e5470 (SP::cSPEditorVerbIconData::Init)
  void SetHotKey(uint32_t key);  // 0x005e5c00 (SP::cSPEditorVerbIconData::SetHotKey)
  eastl::wstring GetIconName(bool withLevel);
};
}
namespace SP {
struct cPropertyList_s005e_4db0 {
  virtual void AddRef();                                // +0x00
  virtual void Release();                               // +0x04
  virtual void v08();                                   // +0x08
  virtual void v0c();                                   // +0x0c
  virtual void v10();                                   // +0x10
  virtual void v14();                                   // +0x14
  virtual void v18();                                   // +0x18
  virtual bool HasProperty(unsigned id);                // +0x1c 0x006a2470
  virtual void v20();                                   // +0x20
  virtual bool QueryProperty(unsigned id, void** out);  // +0x24
};
}
// ---- items of slice s005e4db0 end

// ---- items of slice s005e5d40 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
inline unsigned int CharStrlen(const wchar_t* p) {
  const wchar_t* pCurrent = p;
  while (*pCurrent)
    ++pCurrent;
  return (unsigned int)(pCurrent - p);
}
}
namespace eastl {
class allocator_s005e_5d40 { public:
  allocator_s005e_5d40() {}
};
}
namespace eastl {
class wstring_s005e_5d40 {
 public:
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  allocator_s005e_5d40 mAllocator;

  wstring_s005e_5d40() { AllocateSelf(); }
  wstring_s005e_5d40(const wchar_t* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p); }
  wstring_s005e_5d40(const wstring_s005e_5d40& x);
  ~wstring_s005e_5d40() { DeallocateSelf(); }
  wstring_s005e_5d40& operator=(const wchar_t* p) { return assign(p, p + CharStrlen(p)); }
  wstring_s005e_5d40& assign(const wchar_t* pBegin, const wchar_t* pEnd);
  void RangeInitialize(const wchar_t* p);
  void AllocateSelf() {
    mpBegin = gEmptyString.mEmpty16;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + 1;
  }
  void DeallocateSelf() {
    if ((mpCapacity - mpBegin) > 1)
      DoFree(mpBegin);
  }
  void DoFree(wchar_t* p) {
    if (p)
      EASTL_allocator_deallocate(p);
  }
};
}
namespace SP {
class cString_s005e_5d40 {
 public:
  cString_s005e_5d40();
  ~cString_s005e_5d40();
  const wchar_t* c_str() const;  // 0x006b5240 (SP::cString::c_str)
  uint32_t mData[5];
};
}
namespace SP {
class cPropertyList_s005e_5d40 {
 public:
  PV(0)
  virtual int Release();                 // +0x04
  PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual bool HasProperty(uint32_t id);  // +0x1c 0x006a2470
};
}
namespace SP {
bool GetPropertyAsText(cPropertyList_s005e_5d40* list, uint32_t id, cString_s005e_5d40& out);
}
namespace SP {
class cSPEditorVerbIconData_s005e_5d40 {
 public:
  PV(0)
  virtual int Release();  // +0x04
  char pad04[0xbc];
  cPropertyList_s005e_5d40* mpPropList;  // +0xc0

  eastl::wstring_s005e_5d40 GetIconDescription();
};
}
// ---- items of slice s005e5d40 end

// ---- items of slice s005ecf80 begin (TODO(rewrite): local stubs, replace by canonical classes)
class cRenderTarget {
 public:
  void Render();
};
void* __stdcall AddBoundingBox(void* box, int arg, int flag);
namespace SP {
class cSPPaletteItemRollover_s005e_cf80 {
 public:
  char pad00[0x0c];
  uint32_t pad0c[4];
  int mField1c;                 // +0x1c
  int mField20;                 // +0x20
  uint32_t pad24[(0x78 - 0x24) / 4];
  void* mWinPrice;              // +0x78
  void* mWinVerbIcons;          // +0x7c
  void* mWinAbilityLines;       // +0x80
  void* mWinName;               // +0x84
  void* mWinHeader;             // +0x88
  char  pad8c[4];
  void* mInfo;                  // +0x90
  void* mAbilities;             // +0x94
  int   mInitFlags;             // +0x98  (three flag bytes packed)
  void* mField9c;               // +0x9c
  void* mIconImageGroup;        // +0xa0
  int   mFieldA4;               // +0xa4
  int   mFieldA8;               // +0xa8
  int   mFieldAc;               // +0xac
  int   mFieldB0;               // +0xb0
  int   mFieldB4;               // +0xb4
  bool  mFieldB8;               // +0xb8
  bool  mFieldB9;               // +0xb9
  char  padBa[2];
  float mFieldBc;               // +0xbc
  float mFieldC0;               // +0xc0

  cSPPaletteItemRollover_s005e_cf80(bool flag);
  void* ScalarDeletingDtor(unsigned int flags);

  void AddBox(int arg);
  int* GetAreaPair(int* out);
  void ResetRollover();
  uint8_t Init();  // 0x005ed420 (SP::cSPPaletteItemRollover::Init)
  void Destroy();
};  // namespace SP
}
// ---- items of slice s005ecf80 end

// ---- items of slice s005ed750 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace Math {
struct Rectangle_s005e_d750 {
    float x1, y1, x2, y2;
};  // namespace Math
}
namespace eastl {
template <typename T>
inline const T& max(const T& a, const T& b) { return (a < b) ? b : a; }
}
namespace eastl {
extern wchar_t gEmptyString16[1];  // 0x01667bac
}
namespace eastl {
class string16_s005e_d750 {   // eastl::basic_string<wchar_t>
 public:
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    const char* mpName;
    string16_s005e_d750() : mpBegin(gEmptyString16), mpEnd(gEmptyString16), mpCapacity(gEmptyString16 + 1) {}
    ~string16_s005e_d750() { DeallocateSelf(); }
    void DeallocateSelf();  // 0x00933960
};
}
namespace EA {
namespace UTFWin {
class IWindow_s005e_d750 {
 public:
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
    virtual IWindow_s005e_d750* GetParent();                               // +0x10
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
    virtual uint32_t GetFlags();                                // +0x28
virtual void v0b();
virtual void v0c();
virtual void v0d();
    virtual const Math::Rectangle_s005e_d750& GetRealArea();               // +0x38 (ModAPI GetRealArea)
virtual void v0f();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
    virtual void SetShadeColor(uint32_t color);                 // +0x5c
virtual void v18();
virtual void v19();
virtual void v1a();
    virtual void SetLayoutArea(const Math::Rectangle_s005e_d750& area);    // +0x6c
    virtual void SetLayoutLocation(float x, float y);           // +0x70
    virtual void SetLayoutSize(float w, float h);               // +0x74
    virtual void v1e();
    virtual void SetFlag(uint32_t flag, bool value);            // +0x7c
    virtual void SetCaption(const wchar_t* caption);            // +0x80
virtual void v21();
virtual void v22();
virtual void v23();
    virtual int Invalidate();                                   // +0x90
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v2a();
virtual void v2b();
virtual void v2c();
virtual void v2d();
virtual void v2e();
virtual void v2f();
virtual void v30();
virtual void v31();
virtual void v32();
virtual void v33();
virtual void v34();
virtual void v35();
virtual void v36();
virtual void v37();
virtual void v38();
    virtual void v39();
    virtual void BringToFront(IWindow_s005e_d750* window);                 // +0xe8
};  // namespace EA::UTFWin
}
}
using EA::UTFWin::IWindow_s005e_d750;
enum { kWinFlagVisible = 1 };
class ITextControl {
 public:
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
    virtual void SetAutoSize(int value);                                      // +0x14
virtual void v06();
virtual void v07();
    virtual bool FitArea(Math::Rectangle_s005e_d750* area, int a, int b);                // +0x20
};
ITextControl* CastToTextControl(IWindow_s005e_d750* window);   // 0x005994b0
struct ResourceKey_s005e_d750 {
    uint32_t instance, type, group;
};
class PropertyList {
 public:
    virtual void v00();
    virtual int Release();   // +0x4
};
class IPropManager {
 public:
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v0a();
    virtual bool GetPropertyList(uint32_t instance, uint32_t group, PropertyList** ppOut);  // +0x2c
};
namespace SP {
IPropManager* PropertyManager_s005e_d750();   // 0x0067de30
}
namespace SP {
class cString_s005e_d750 {   // retail size 0x14
 public:
    uint32_t mData[5];
    cString_s005e_d750();                  // 0x006b5060
    ~cString_s005e_d750();                 // 0x006b5240
    const wchar_t* GetText();   // 0x006b55c0
};
}
namespace SP {
bool GetPropertyAsText(PropertyList* list, uint32_t id, cString_s005e_d750* out);          // 0x006a1360
}
namespace SP {
bool GetPropertyAsKeyInstance(PropertyList* list, uint32_t id, uint32_t* out);  // 0x006a12a0
}
bool TryGetUIntProperty(PropertyList* list, uint32_t id, int* out);   // 0x00410370
struct ImageInfo {
    uint32_t pad[7];
    int mWidth;    // +0x1c
    int mHeight;   // +0x20
};
class cSPUILayout_s005e_d750 {
 public:
    uint32_t mData[3];
};
namespace SPUIHelpers {
ImageInfo* GetImageFromId(uint32_t instanceId);                              // 0x00458de0
}
namespace SPUIHelpers {
ImageInfo* GetImageFromLayout(cSPUILayout_s005e_d750* layout, uint32_t imageKey);       // 0x008061c0
}
namespace SPUIHelpers {
void SetDrawableImage(IWindow_s005e_d750* window, ImageInfo* image, int index);         // 0x008068d0
}
namespace SPUIHelpers {
void AutoSizeWindowForText(IWindow_s005e_d750* window, bool width, bool height);        // 0x00806e40
}
namespace SPUIHelpers {
void AnchorWindowToWindow(IWindow_s005e_d750* w, IWindow_s005e_d750* anchor, uint32_t flags, IWindow_s005e_d750* ref);  // 0x00807340
}
namespace EA {
namespace Locale {
int SetMoneyString(double value, wchar_t* buf, int bufSize, const wchar_t* format, const wchar_t* symbol);  // 0x008822e0
}
}
struct ItemStatus {
    SP::cString_s005e_d750 mReason;       // +0x00
    SP::cString_s005e_d750 mReason2;      // +0x14
    uint32_t mColor;           // +0x28
    uint32_t mImageKey;        // +0x2c
    bool mbUseSymbol;          // +0x30
    ItemStatus();              // 0x005a7810
};
class IItemStatusProvider {
 public:
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
    virtual int GetStatus(const ResourceKey_s005e_d750& key, ItemStatus* status);   // +0x10
};
class IAbilityProvider {
 public:
virtual void v00();
virtual void v01();
    virtual int Release();                                  // +0x08
    virtual void SetupWindow(IWindow_s005e_d750* window, bool locked); // +0x0c
    virtual int GetCount();                                 // +0x10
};
struct AbilityProviderPtr {
    IAbilityProvider* mpObject;
    AbilityProviderPtr& operator=(IAbilityProvider* p);    // 0x00572620
    __forceinline void reset()
    {
        if (mpObject) {
            IAbilityProvider* p = mpObject;
            mpObject = 0;
            p->Release();
        }
    }
};
struct PropertyListPtr {
    PropertyList* mpObject;
    PropertyListPtr() : mpObject(0) {}
    ~PropertyListPtr()
    {
        if (mpObject)
            mpObject->Release();
    }
    PropertyList** AsPPTypeParam()
    {
        if (mpObject) {
            PropertyList* p = mpObject;
            mpObject = 0;
            p->Release();
        }
        return &mpObject;
    }
};
class cSPUIPropertyLayout_s005e_d750 {
 public:
    uint32_t mHeader[3];          // +0x00 (IWinProc, RefCount)
    cSPUILayout_s005e_d750 mLayout;          // +0x0c
    uint32_t mBase[0x60 / 4];     // +0x18 .. +0x78
    void SetFlag(int flag);               // 0x00828020
    void ForceVisibleLocation();          // 0x00828110
};
namespace SP {
class cSPPaletteItemRollover_s005e_d750 : public cSPUIPropertyLayout_s005e_d750 {
 public:
    IWindow_s005e_d750* mWinRoot;                 // +0x78
    IWindow_s005e_d750* mWinBackgroundStandard;   // +0x7c
    IWindow_s005e_d750* mWinBackgroundNoFunds;    // +0x80
    IWindow_s005e_d750* mWinBackgroundLocked;     // +0x84
    IWindow_s005e_d750* mWinPrice;                // +0x88
    IWindow_s005e_d750* mWinVerbIcons;            // +0x8c
    IWindow_s005e_d750* mWinAbilityLines;         // +0x90
    IWindow_s005e_d750* mWinName;                 // +0x94
    IWindow_s005e_d750* mWinIcon;                 // +0x98
    IWindow_s005e_d750* mWinHeader;               // +0x9c
    IWindow_s005e_d750* mWinErrorGroup;           // +0xa0
    IWindow_s005e_d750* mWinErrorIcon;            // +0xa4
    IWindow_s005e_d750* mWinErrorSymbol;          // +0xa8
    IWindow_s005e_d750* mWinErrorReason;          // +0xac
    void* mInfo;                       // +0xb0
    AbilityProviderPtr mAbilities;     // +0xb4
    bool mNeedToInit;                  // +0xb8
    bool mShowAbilities;               // +0xb9

    void Show(const ResourceKey_s005e_d750& key, IAbilityProvider* abilities, IItemStatusProvider* statusProvider,
              wchar_t currencySymbol, bool locked, bool queryStatus);
};  // namespace SP
}
// ---- items of slice s005ed750 end

// ---- items of slice s005ee480 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
template <typename T>
class AutoRefCount_s005e_e480 {
 public:
  T* mpObject;
  AutoRefCount_s005e_e480() : mpObject(0) {}
  AutoRefCount_s005e_e480(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount_s005e_e480() { if (mpObject) mpObject->Release(); }
  AutoRefCount_s005e_e480& operator=(T* p) {
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
class RefCountVTemplate_s005e_e480 {
 public:
  RefCountVTemplate_s005e_e480() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s005e_e480() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace EA {
namespace COM {
class IUnknown32_s005e_e480 {
 public:
  ~IUnknown32_s005e_e480() {}
  virtual int AddRef() = 0;
  virtual int Release() = 0;
  virtual void* Cast(uint32_t typeID) const = 0;
};  // namespace COM
}
}
namespace EA {
namespace ResourceMan {
class Key_s005e_e480 { public:
  unsigned int mInstance, mType, mGroup;
  Key_s005e_e480() {}
  Key_s005e_e480(unsigned int instance, unsigned int type, unsigned int group) {
    mType = type;
    mGroup = group;
    mInstance = instance;
  }
};  // namespace ResourceMan
}
}
using EA::AutoRefCount_s005e_e480;
using EA::ResourceMan::Key_s005e_e480;
class cSPUIPropertyLayout_s005e_e480;
namespace SP {
class cSPEditorEconomy_s005e_e480;
}
namespace SP {
class cCollectableItems_s005e_e480;
}
namespace SP {
struct cSPPaletteInfo_s005e_e480 {
  virtual ~cSPPaletteInfo_s005e_e480();
  virtual int AddRef();
  virtual int Release();
  int mRefCount;                            // +0x4
  cSPEditorEconomy_s005e_e480* mEconomy;               // +0x8
  uint32_t mPad0c;
  cCollectableItems_s005e_e480* mCollectableItems;     // +0x10
  uint32_t mPad14;
  wchar_t mCurrencyChar;                    // +0x18
  uint32_t mPad1c[4];
  uint32_t mModelType;                      // +0x2c
};
}
namespace SP {
class cSPPaletteItem_s005e_e480 : public EA::RefCountVTemplate_s005e_e480<int>, public EA::COM::IUnknown32_s005e_e480 {
 public:
  virtual int AddRef();
  virtual int Release();
  bool IsUnlocked(cCollectableItems_s005e_e480* items);   // 0x005c6630
  bool IsNew(cCollectableItems_s005e_e480* items);        // 0x005c6670
  Key_s005e_e480 mItemKey;          // +0xc
  Key_s005e_e480 mThumbnailKey;     // +0x18
};
}
namespace SP {
class cSPEditorVehicleAbilities {
 public:
  cSPEditorVehicleAbilities(Key_s005e_e480 key, uint32_t modelType, uint32_t layoutID, uint32_t textID, bool b);  // 0x0059f030
  virtual ~cSPEditorVehicleAbilities();
  virtual int AddRef();
  virtual int Release();
  uint32_t mData[24];
};
}
class cSPUIPropertyLayout_s005e_e480 {
 public:
  void SetItem(SP::cSPPaletteItem_s005e_e480* item, SP::cSPPaletteInfo_s005e_e480* info, SP::cSPEditorVehicleAbilities* content,
               bool show);
  void SetContents(const Key_s005e_e480* key, SP::cSPEditorVehicleAbilities* content, SP::cSPEditorEconomy_s005e_e480* economy,
                   wchar_t currency, bool unlocked, bool show);    // 0x005ed750
  void SetMode(int mode);                                           // 0x005ed320
  void SetPositionAndOffset(float x, float y, float dx, float dy);  // 0x008283a0
  char pad[0xb0];
  AutoRefCount_s005e_e480<SP::cSPPaletteInfo_s005e_e480> mpPaletteInfo;  // +0xb0
};
// ---- items of slice s005ee480 end

// ---- items of slice s005ef440 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV_s005e_f440(n) virtual void pv##n();
typedef unsigned int hkUint32;
typedef unsigned short hkUint16;
class hkBool_s005e_f440 {
 public:
  hkBool_s005e_f440(bool b) : m_bool(b) {}
  operator bool() const { return m_bool != 0; }
  char m_bool;
};
class hkMemory {
 public:
  PV_s005e_f440(0) PV_s005e_f440(1) PV_s005e_f440(2) PV_s005e_f440(3) PV_s005e_f440(4)
  virtual void deallocateChunk(void* p, int nbytes, int cl);  // +0x14
  static hkMemory* s_instance;  // 0x016e4178
  static hkMemory& getInstance() { return *s_instance; }
};
class hkBaseObject_s005e_f440 {
 public:
  virtual ~hkBaseObject_s005e_f440() {}
};
class hkReferencedObject_s005e_f440 : public hkBaseObject_s005e_f440 {
 public:
  hkReferencedObject_s005e_f440() : m_referenceCount(1) {}
  void operator delete(void* p) {
    hkReferencedObject_s005e_f440* b = static_cast<hkReferencedObject_s005e_f440*>(p);
    hkMemory::getInstance().deallocateChunk(p, b->m_memSizeAndFlags, 0x24);
  }
  hkUint16 m_memSizeAndFlags;  // +0x4
  hkUint16 m_referenceCount;   // +0x6
};
struct hkpCollidable;
struct hkpCdBody {
  const struct hkpShape* m_shape;  // +0x0
  hkUint32 m_shapeKey;             // +0x4
  const void* m_motion;            // +0x8
  const hkpCdBody* m_parent;       // +0xc
  const hkpCdBody* getParent() const { return m_parent; }
  const hkpShape* getShape() const { return m_shape; }
  hkUint32 getShapeKey() const { return m_shapeKey; }
};
struct hkpCollidable : public hkpCdBody {
  uint32_t pad10[3];
  hkUint32 m_collisionFilterInfo;  // +0x1c
  hkUint32 getCollisionFilterInfo() const { return m_collisionFilterInfo; }
};
inline const hkpCollidable* getRootCollidable(const hkpCdBody* body) {
  while (body->getParent())
    body = body->getParent();
  return static_cast<const hkpCollidable*>(body);
}
class hkpShapeContainer {
 public:
  PV_s005e_f440(0) PV_s005e_f440(1) PV_s005e_f440(2) PV_s005e_f440(3) PV_s005e_f440(4) PV_s005e_f440(5) PV_s005e_f440(6) PV_s005e_f440(7) PV_s005e_f440(8) PV_s005e_f440(9) PV_s005e_f440(10)
  virtual hkUint32 getCollisionFilterInfo(hkUint32 key) const;  // +0x2c
};
struct hkpShape {
  PV_s005e_f440(0) PV_s005e_f440(1)
  virtual int getType() const;  // +0x8
  PV_s005e_f440(3) PV_s005e_f440(4) PV_s005e_f440(5) PV_s005e_f440(6) PV_s005e_f440(7) PV_s005e_f440(8) PV_s005e_f440(9) PV_s005e_f440(10)
  virtual hkUint32 getCollisionFilterInfo(hkUint32 key) const;  // +0x2c (hkpShapeCollection)
  uint32_t pad4[2];
  const hkpShape* m_child;  // +0xc (hkpBvTreeShape container)
};
struct hkpCollisionDispatcher {
  uint32_t pad[0x43];
  hkUint32 m_hasAlternateType[1];  // +0x10c
  hkBool_s005e_f440 hasAlternateType(int type, int alternateType) const {
    return hkBool_s005e_f440(((m_hasAlternateType[type] >> alternateType) & 1) != 0);
  }
};
struct hkpCollisionInput {
  hkpCollisionDispatcher* m_dispatcher;  // +0x0
};
struct hkpShapeRayCastInput {
  uint32_t pad[8];
  hkUint32 m_filterInfo;  // +0x20
};
struct hkpWorldRayCastInput;
class hkpCollidableCollidableFilter {
 public:
  virtual ~hkpCollidableCollidableFilter() {}
  virtual hkBool_s005e_f440 isCollisionEnabled(const hkpCollidable& a, const hkpCollidable& b) const = 0;
};
class hkpShapeCollectionFilter {
 public:
  virtual ~hkpShapeCollectionFilter() {}
  virtual hkBool_s005e_f440 isCollisionEnabled(const hkpCollisionInput& input, const hkpCdBody& a,
                                    const hkpCdBody& b, const hkpShapeContainer& bContainer,
                                    hkUint32 bKey) const = 0;
};
class hkpRayShapeCollectionFilter {
 public:
  virtual ~hkpRayShapeCollectionFilter() {}
  virtual hkBool_s005e_f440 isCollisionEnabled(const hkpShapeRayCastInput& aInput,
                                    const hkpShapeContainer& bContainer, hkUint32 bKey) const = 0;
};
class hkpRayCollidableFilter {
 public:
  virtual ~hkpRayCollidableFilter() {}
  virtual hkBool_s005e_f440 isCollisionEnabled(const hkpWorldRayCastInput& a, const hkpCollidable& collidableB) const = 0;
};
class hkCollisionFilter_s005e_f440 : public hkReferencedObject_s005e_f440,
                          public hkpCollidableCollidableFilter,
                          public hkpShapeCollectionFilter,
                          public hkpRayShapeCollectionFilter,
                          public hkpRayCollidableFilter {
 public:
};
namespace SP {
class SPSpineCollisionFilter : public hkCollisionFilter_s005e_f440 {
 public:
  SPSpineCollisionFilter();
  virtual ~SPSpineCollisionFilter();
  virtual hkBool_s005e_f440 isCollisionEnabled(const hkpCollidable& a, const hkpCollidable& b) const;
  virtual hkBool_s005e_f440 isCollisionEnabled(const hkpCollisionInput& input, const hkpCdBody& a,
                                    const hkpCdBody& b, const hkpShapeContainer& bContainer,
                                    hkUint32 bKey) const;
  virtual hkBool_s005e_f440 isCollisionEnabled(const hkpShapeRayCastInput& aInput,
                                    const hkpShapeContainer& bContainer, hkUint32 bKey) const;
  virtual hkBool_s005e_f440 isCollisionEnabled(const hkpWorldRayCastInput& a, const hkpCollidable& collidableB) const;
  hkBool_s005e_f440 isCollisionEnabled(hkUint32 infoA, hkUint32 infoB) const;
  void enableCollisionsBetween(int layerA, int layerB);
  void disableCollisionsUsingBitfield(hkUint32 layerBitsA, hkUint32 layerBitsB);

  int m_nextFreeSystemGroup;             // +0x18
  hkUint32 m_collisionLookupTable[32];   // +0x1c
};  // namespace SP
}
// ---- items of slice s005ef440 end

// @ 0x005e0370
SP::cSPRolloverModelData::cSPRolloverModelData(const Key& modelKey, const Key& itemKey, uint32_t layoutID, uint32_t layoutGroup, uint32_t textID)
: mModelKey(), mItemKey(), mLayoutKey(), mGroupKey(), mItems(), mTextID(0)
{
  mModelKey = modelKey;
  mItemKey = itemKey;
  mLayoutKey.mInstance = layoutID;
  mLayoutKey.mType = 0x510a95b;
  mLayoutKey.mGroup = 0x40464100;
  mGroupKey.mInstance = layoutGroup;
  mGroupKey.mType = 0x510a95b;
  mGroupKey.mGroup = 0x40464100;
  mTextID = textID;
  if (mTextID == 0) mTextID = 0x4ecf38a;
}

// @ 0x005e0440
SP::cSPRolloverModelData::~cSPRolloverModelData()
{
  int count = mItems.size();
  for (int i = 0; i < count; i++)
    mItems[i]->Shutdown(true);
  vector<AutoRefCount<cSPUILayout> >& items = mItems;
  items.erase(items.begin(), items.end());
  mTextID = 0;
}

// @ 0x005e0930
void AbilityLayoutData::LayoutAbilities(IEditorWidget* window, bool alt)
{
    (void)alt;
    float total = 0.0f;

    mPages.erase(mPages.mpBegin, mPages.mpEnd);

    AutoRefCount_s005e_0930<cPropertyList> typeList;
    PropertyManager()->GetPropertyList(mTypeKey.instanceID, mTypeKey.groupID,
                                       typeList.AsOutParam());

    mPages.erase(mPages.mpBegin, mPages.mpEnd);

    int count = 0;
    void* keys = 0;
    if (GetPropertyArrayKey(typeList, mAbilityPropId, &count, &keys) && count > 0) {
        for (int i = 0; i < count; i++) {
            const uint32_t* entry = (const uint32_t*)keys + i * 3;
            AutoRefCount_s005e_0930<cPropertyList> abilityList;
            if (PropertyManager()->GetPropertyList(entry[0], 0x1b68db4,
                                                   abilityList.AsOutParam())) {
                uint32_t subKey = 0;
                if (abilityList->HasProperty(0x626efe0))
                    GetPropertyAsKeyInstance(abilityList, 0x626efe0, &subKey);
                cString text;
                GetPropertyAsText(abilityList, 0x1b7c544, text);
                ResourceKey nullKey = { 0, 0, 0 };
                total += LayoutLine(window, &mLineKey, total, subKey, &nullKey, &text, -1.0f);
            }
        }
    }

    EA::ResourceMan::IResourceManager* manager = EA::ResourceMan::GetManager();
    if (mVehicleKey.instanceID) {
        AutoRefCount_s005e_0930<IResource> resource;
        if (manager->GetResource(&mVehicleKey, resource.AsOutParam(), 0, 0, 0, 0)) {
            AutoRefCount_s005e_0930<IResource> owner;
            owner = (IResource*)resource->Cast(0x3c609f8);
            void* entries[3] = { 0, 0, 0 };
            ApplyOwnerEntries(entries, (void*)owner.mpObject);
            eastl::vector_s005e_0930<void*> records;
            CollectAbilityRecords(*(void**)((char*)owner.mpObject + 0x18), &records, entries);
            for (unsigned int i = 0; i < records.size(); i++) {
                AbilityRecord* record = (AbilityRecord*)records[i];
                if (record && record->m24 != 0x66904205)
                    total += LayoutLine(window, &mRowKey, total, record->m90, &record->mb4,
                                        &record->m54, record->m18);
            }
        }
    }

    Math::Rectangle area = window->GetArea();
    area.y1 += total;
    window->SetArea(area);
}

// @ 0x005e0cf0
VerbTray::VerbTray()
{
    z54[0] = 0; z54[1] = 0; z54[2] = 0; z54[3] = 0; z54[4] = 0; z54[5] = 0;
    z54[6] = 0; z54[7] = 0; z54[8] = 0; z54[9] = 0; z54[10] = 0; z54[11] = 0;
    f90[0] = 0.0f; f90[1] = 0.0f; f90[2] = 0.0f;
    f90[3] = 0.0f; f90[4] = 0.0f; f90[5] = 0.0f;
}

// @ 0x005e0d80
VehicleTray::~VehicleTray()
{
}

// @ 0x005e0e50
void CShut::Shutdown()
{
    ShutdownBase();
    if (m54) {
        m54->Shutdown(1);
        RefObj* p = m54;
        if (p) {
            m54 = 0;
            p->Release();
        }
    }
}

// @ 0x005e0e80
void VehicleTray::Update(uint32_t dt)
{
    float seconds = (float)dt * 0.001f;
    int count = (int)mVerbIcons.size();
    for (int i = 0; i < count; i++)
        mVerbIcons[i]->Update(dt);

    if (m9c != m90) {
        float value = (m9c - m90) * seconds * 6.5f + m90;
        m90 = value;
        if (fabsf(value - m9c) < 0.001f)
            m90 = m9c;
    }
    if (ma0 != m94) {
        float value = (ma0 - m94) * seconds * 6.5f + m94;
        m94 = value;
        if (fabsf(value - ma0) < 0.001f)
            m94 = ma0;
    }
    if (ma4 != m98) {
        float value = (ma4 - m98) * seconds * 6.5f + m98;
        m98 = value;
        if (fabsf(value - ma4) < 0.001f)
            m98 = ma4;
    }
    Layout();
}

// @ 0x005e1020
void VehicleTray::SetList(void* list)
{
    if (list) {
        int count = (int)mVerbIcons.size();
        for (int i = 0; i < count; i++)
            mVerbIcons[i]->SetVerbIconList(list);

        if (m84->GetData() && m88->GetData() && m8c->GetData()) {
            m9c = m84->GetData()->mScale * 0.01f;
            ma0 = m88->GetData()->mScale * 0.01f;
            ma4 = m8c->GetData()->mScale * 0.01f;

            bool enabled0 = m84->GetData()->mScale == kRealZero;
            bool enabled1 = m88->GetData()->mScale == kRealZero;
            bool enabled2 = m8c->GetData()->mScale == kRealZero;

            ColorRGBA color0 = m84->GetData()->mColor;
            ColorRGBA color1 = m88->GetData()->mColor;
            ColorRGBA color2 = m8c->GetData()->mColor;

            m6c->SetColor(ColorRGBAToU32(&color0));
            m70->SetColor(ColorRGBAToU32(&color1));
            m74->SetColor(ColorRGBAToU32(&color2));
            m78->SetEnabled(1, enabled0);
            m7c->SetEnabled(1, enabled1);
            m80->SetEnabled(1, enabled2);
        }
        Layout();
    }
}

// @ 0x005e12c0
void VehicleTray::Layout()
{
    float origin = mMaxArea.x1;
    float range = (mGutters.x1 - mMaxArea.x2) - origin * 3.0f;
    float level0 = m98 * range + origin;
    float level1 = m90 * range + origin;
    float level2 = m94 * range + origin;
    float centerX = mMaxArea.y2;

    Math::Rectangle r0 = m68->GetArea();
    r0.y1 = r0.y2 - level0;
    m68->SetArea(r0);

    Math::Rectangle r1 = m64->GetArea();
    r1.y1 = r1.y2 - level0 - level1;
    m64->SetArea(r1);

    Math::Rectangle r2 = m60->GetArea();
    r2.y1 = r2.y2 - level0 - level1 - level2;
    m60->SetArea(r2);

    float bottom = r2.y1;
    float top = r1.y1;
    IVerbTray* tray = m84;
    {
        IEditorWidget* window = tray->GetWindow();
        Math::Rectangle area = window->GetArea();
        float width = area.x2 - area.x1;
        float height = area.y2 - area.y1;
        area.y1 = (top - bottom) * 0.5f + bottom - height * 0.5f;
        area.y2 = area.y1 + height;
        area.x1 = centerX - width * 0.5f;
        area.x2 = area.x1 + width;
        tray->SetMaxArea(area);
    }

    bottom = r1.y1;
    top = r0.y1;
    tray = m88;
    {
        IEditorWidget* window = tray->GetWindow();
        Math::Rectangle area = window->GetArea();
        float width = area.x2 - area.x1;
        float height = area.y2 - area.y1;
        area.y1 = (top - bottom) * 0.5f + bottom - height * 0.5f;
        area.y2 = area.y1 + height;
        area.x1 = centerX - width * 0.5f;
        area.x2 = area.x1 + width;
        tray->SetMaxArea(area);
    }

    bottom = r0.y1;
    top = r0.y2;
    tray = m8c;
    {
        IEditorWidget* window = tray->GetWindow();
        Math::Rectangle area = window->GetArea();
        float width = area.x2 - area.x1;
        float height = area.y2 - area.y1;
        area.y1 = (top - bottom) * 0.5f + bottom - height * 0.5f;
        area.y2 = area.y1 + height;
        area.x1 = centerX - width * 0.5f;
        area.x2 = area.x1 + width;
        tray->SetMaxArea(area);
    }
}

// @ 0x005e16c0
void SP::cSPVerbTrayCollection_s005e_16c0::InitTrays(EA::ResourceMan::Key_s005e_16c0 key, const void* p, int n)
{
    InitTraysBase(key, p, n);

    void* temp = 0;
    cPropertyManager_s005e_16c0* pm = PropertyManager_s005e_16c0();
    pm->GetProperty(key.mType, key.mInstance, &temp);

    EA::ResourceMan::Key_s005e_16c0 layoutKey;
    GetPropertyAsKey(temp, 0x6309cac, &layoutKey);
    layoutKey.mGroup = 0x510a95b;
    layoutKey.mInstance = 0x40464100;

    void* mem = operator_new(0x18, kEditorAllocName, 0, 0, 0, 0);
    if (mem != 0)
        mLayout = cConnectionDialog_ctor(mem);
    else
        mLayout = 0;

    mLayout->Init(layoutKey, true, 0x5b598fa);
    mLayout->SetParentWin(mWin20.mpObject, true, 0x5b598fa);

    mWin58 = mLayout->FindWindowByID(0x6309146, true);
    mWin5c = mLayout->FindWindowByID(0x6309b56, true);
    mWin60 = mLayout->FindWindowByID(0x63090b9, true);
    mWin64 = mLayout->FindWindowByID(0x63090db, true);
    mWin68 = mLayout->FindWindowByID(0x63090ef, true);
    mWin6c = mLayout->FindWindowByID(0x6381b56, true);
    mWin70 = mLayout->FindWindowByID(0x6381b57, true);
    mWin74 = mLayout->FindWindowByID(0x6381b58, true);
    mWin78 = mLayout->FindWindowByID(0x6381d5d, true);
    mWin7c = mLayout->FindWindowByID(0x6381d5e, true);
    mWin80 = mLayout->FindWindowByID(0x6381d5f, true);

    const float* area = mWin60.mpObject->GetArea();
    mArea[0] = area[0];
    mArea[1] = area[1];
    mArea[2] = area[2];
    mArea[3] = area[3];

    const float* a20 = mWin20.mpObject->GetArea();
    float x20 = a20[0];
    float x2_20 = a20[2];
    const float* a58 = mWin58.mpObject->GetArea();
    float r[4];
    r[0] = a58[2] - a58[0];
    r[1] = 0.0f;
    r[2] = x2_20 - x20;
    r[3] = a58[3] - a58[1];
    r[0] = r[2] - r[0];
    mWin58.mpObject->SetArea(r);

    mPage84 = (cSPPalettePage_s005e_16c0*)0;
    cSPPalettePage_s005e_16c0* page0 = GetPage(0);
    mWin5c.mpObject->SetPage(page0, 0);
    mPage84 = GetPage(1);
    mWin58.mpObject->SetPage(mPage84.mpObject, 0);
    mPage88 = GetPage(2);
    mWin58.mpObject->SetPage(mPage88.mpObject, 0);
    mPage8c = GetPage(3);
    mWin58.mpObject->SetPage(mPage8c.mpObject, 0);

    mHeight = mPage84.mpObject->GetHeight() - 10.0f;

    if (temp != 0)
        ((EA::UTFWin::IWindow_s005e_16c0*)temp)->Release();
}

// @ 0x005e1b70
namespace SP {
void SP::cSPEditorVerbIcon_s005e_16c0::SetIcon(EA::UTFWin::IWindow_s005e_16c0* p, EA::ResourceMan::Key_s005e_16c0 key, int a, int b)
{
    mWinShortcutText = p;
    if (mWin24.mpObject == 0) {
        mWin24 = mWinShortcutText->FindChild(0x3ed7919, 1);
        if (mWin24.mpObject == 0)
            mWin24 = mWinShortcutText.mpObject;
    }
    mCharge.mCurrentValue = 0.0f;
    mF90 = 0.0f;
    mCharge.mElapsedTime = 0.0f;
    mF94 = 0.0f;
    mCharge.mInitialValue = 0.0f;
    mCharge.mTargetValue = 0.0f;
    LayoutInit(key, a, b);
    Slot10();
}
}  // namespace SP

// @ 0x005e5c80
namespace SP {
eastl::wstring cSPEditorVerbIconData_s005e_4db0::GetIconName(bool withLevel)
{
  eastl::wstring result;
  cString_s005e_4db0 label(0xd1726890, 0x4ace6b0, L"Level");
  if (!withLevel) {
    const wchar_t* text = ((cString_s005e_4db0*)&mName)->GetText();
    const wchar_t* end = text;
    while (*end)
      ++end;
    result.assign(text, end);
  } else {
    WStr_Format(&result, L"%ls - %ls %d", label.GetText(), ((cString_s005e_4db0*)&mName)->GetText(),
                (int)mMaxLevel);
  }
  return result;
}
}  // namespace SP

// @ 0x005e5d40
namespace SP {
eastl::wstring_s005e_5d40 cSPEditorVerbIconData_s005e_5d40::GetIconDescription()
{
  if (mpPropList->HasProperty(0x3249a320)) {
    cString_s005e_5d40 text;
    GetPropertyAsText(mpPropList, 0x3249a320, text);
    eastl::wstring_s005e_5d40 result(text.c_str());
    return result;
  }
  return eastl::wstring_s005e_5d40();
}
}  // namespace SP

// @ 0x005ed320
namespace SP {
void cSPPaletteItemRollover_s005e_cf80::AddBox(int arg)
{
  void* box = mWinPrice;
  void* target = AddBoundingBox(box, arg, 1);
  ((cRenderTarget*)target)->Render();
}
}  // namespace SP

// @ 0x005ed340
namespace SP {
int* cSPPaletteItemRollover_s005e_cf80::GetAreaPair(int* __restrict out)
{
  out[0] = mField1c;
  out[1] = mField20;
  return out;
}
}  // namespace SP

// @ 0x005ed750
namespace SP {
void cSPPaletteItemRollover_s005e_d750::Show(const ResourceKey_s005e_d750& key, IAbilityProvider* abilities, IItemStatusProvider* statusProvider, wchar_t currencySymbol, bool locked, bool queryStatus)
{
    PropertyListPtr propList;
    PropertyManager_s005e_d750()->GetPropertyList(key.instance, key.group, propList.AsPPTypeParam());
    if (!propList.mpObject)
        return;
    if (!mWinRoot || !mWinBackgroundNoFunds || !mWinBackgroundLocked || !mWinBackgroundStandard ||
        !mWinPrice || !mWinAbilityLines || !mWinName || !mWinHeader || !mWinErrorGroup ||
        !mWinErrorIcon || !mWinErrorReason)
        return;

    int price = 0;
    TryGetUIntProperty(propList.mpObject, 0x2166464, &price);

    ItemStatus status;
    int state = 1;
    if (statusProvider && queryStatus)
        state = statusProvider->GetStatus(key, &status);
    bool bAvailable = (state == 1);
    if (status.mColor != 0xffff0000)
        bAvailable = true;
    bool bLocked = locked || state == 7;

    eastl::string16_s005e_d750 unused;
    const wchar_t* name = L"";
    cString_s005e_d750 nameText;
    if (GetPropertyAsText(propList.mpObject, 0x8f6fc401, &nameText))
        name = nameText.GetText();
    mWinName->SetCaption(name);

    uint32_t iconId = 0;
    GetPropertyAsKeyInstance(propList.mpObject, 0x666b54e, &iconId);
    if (iconId == 0 || mWinIcon) {
        ImageInfo* image = 0;
        if (iconId != 0)
            image = SPUIHelpers::GetImageFromId(iconId);
        if (image) {
            mWinIcon->SetFlag(kWinFlagVisible, true);
            SPUIHelpers::SetDrawableImage(mWinIcon, image, -1);
            if (mWinName)
                mWinName->SetLayoutLocation(mWinIcon->GetRealArea().x2 + 4.0f, mWinName->GetRealArea().y1);
        } else if (mWinIcon) {
            mWinIcon->SetFlag(kWinFlagVisible, false);
            if (mWinName) {
                const Math::Rectangle_s005e_d750& iconArea = mWinIcon->GetRealArea();
                mWinName->SetLayoutLocation(iconArea.x1, mWinName->GetRealArea().y1);
            }
        }
    }

    wchar_t priceText[0x28];
    priceText[0] = 0;
    if (price != 0) {
        wchar_t symbol[2];
        symbol[0] = currencySymbol;
        symbol[1] = 0;
        EA::Locale::SetMoneyString((double)price, priceText, 0x28, L"%-F%-p", symbol);
    }
    bool bShowPrice = !bLocked && state != 6 && price > 0;
    mWinPrice->SetCaption(priceText);
    mWinPrice->SetFlag(kWinFlagVisible, bShowPrice);
    mWinPrice->SetShadeColor(bAvailable ? 0xffffffff : 0xffff0000);
    mWinBackgroundStandard->SetFlag(kWinFlagVisible, bAvailable && !bLocked);
    mWinBackgroundNoFunds->SetFlag(kWinFlagVisible, !bAvailable && !bLocked);
    mWinBackgroundLocked->SetFlag(kWinFlagVisible, bLocked);
    mWinPrice->Invalidate();

    float errorWidth = 0.0f;
    if (state == 1 || state == 7) {
        mWinErrorGroup->SetFlag(kWinFlagVisible, false);
    } else {
        mWinErrorGroup->SetFlag(kWinFlagVisible, true);
        mWinErrorReason->SetCaption(status.mReason.GetText());
        mWinErrorReason->SetShadeColor(status.mColor);
        mWinErrorIcon->SetShadeColor(status.mColor);
        mWinErrorSymbol->SetShadeColor(status.mColor);
        float left;
        float right;
        bool showSymbol;
        if (status.mbUseSymbol) {
            wchar_t symbol[2];
            symbol[0] = currencySymbol;
            symbol[1] = 0;
            mWinErrorSymbol->SetCaption(symbol);
            CastToTextControl(mWinErrorSymbol)->SetAutoSize(0);
            left = mWinErrorSymbol->GetRealArea().x1;
            right = mWinErrorSymbol->GetRealArea().x2 + 5.0f;
            mWinErrorIcon->SetFlag(kWinFlagVisible, false);
            showSymbol = true;
        } else {
            ImageInfo* image = SPUIHelpers::GetImageFromLayout(&mLayout, status.mImageKey);
            if (image) {
                mWinErrorIcon->SetLayoutSize((float)image->mWidth, (float)image->mHeight);
                SPUIHelpers::SetDrawableImage(mWinErrorIcon, image, -1);
                left = mWinErrorIcon->GetRealArea().x1;
                right = mWinErrorIcon->GetRealArea().x2 + 5.0f;
            } else {
                left = 0.0f;
                right = 0.0f;
            }
            mWinErrorIcon->SetFlag(kWinFlagVisible, image != 0);
            showSymbol = false;
        }
        mWinErrorSymbol->SetFlag(kWinFlagVisible, showSymbol);
        errorWidth = right - left;
        Math::Rectangle_s005e_d750 area = mWinErrorReason->GetRealArea();
        area.x1 = right;
        mWinErrorReason->SetLayoutArea(area);
        if (CastToTextControl(mWinErrorReason)->FitArea(&area, 0, 1))
            errorWidth = area.x2 - left;
    }

    float headerTop = mWinHeader->GetRealArea().y1;
    CastToTextControl(mWinName)->SetAutoSize(0);
    Math::Rectangle_s005e_d750 nameArea = mWinName->GetRealArea();
    float nameWidth = nameArea.x2 - nameArea.x1;
    float nameHeight = nameArea.y2 - nameArea.y1;
    if (bShowPrice)
        SPUIHelpers::AutoSizeWindowForText(mWinPrice, true, false);
    Math::Rectangle_s005e_d750 priceArea = mWinPrice->GetRealArea();
    float priceHeight = priceArea.y2 - priceArea.y1;
    float rowHeight = eastl::max(eastl::max(priceHeight, nameHeight), 24.0f) + 4.0f;
    nameArea.y1 = (rowHeight - nameHeight) * 0.5f;
    nameArea.y2 = nameArea.y1 + nameHeight;
    priceArea.y1 = (rowHeight - priceHeight) * 0.5f;
    priceArea.y2 = priceArea.y1 + priceHeight;
    mWinPrice->SetLayoutArea(priceArea);
    Math::Rectangle_s005e_d750 headerArea = mWinHeader->GetRealArea();
    headerArea.y1 = headerTop;
    headerArea.y2 = rowHeight + headerTop;
    mWinHeader->SetLayoutArea(headerArea);
    nameArea.x2 = nameArea.x1 + nameWidth;
    mWinName->SetLayoutArea(nameArea);

    float width = nameWidth;
    if (mWinIcon && (mWinIcon->GetFlags() & kWinFlagVisible)) {
        const Math::Rectangle_s005e_d750& iconArea = mWinIcon->GetRealArea();
        width = (iconArea.x2 - iconArea.x1) + nameWidth + 4.0f;
    }
    const Math::Rectangle_s005e_d750& hdr = mWinHeader->GetRealArea();
    float bottom = (hdr.y2 - hdr.y1) + headerTop;
    mWinRoot->SetLayoutSize(width, nameArea.y2 - nameArea.y1);
    if (bShowPrice)
        SPUIHelpers::AnchorWindowToWindow(mWinName, mWinPrice, 0x600, mWinPrice);

    const Math::Rectangle_s005e_d750& hdr2 = mWinHeader->GetRealArea();
    float headerWidth = hdr2.x2 - hdr2.x1;
    float total = width + 20.0f;
    if (bShowPrice) {
        const Math::Rectangle_s005e_d750& pa = mWinPrice->GetRealArea();
        total = (pa.x2 - pa.x1) + total + 20.0f;
    }
    if (errorWidth + 20.0f > total)
        total = errorWidth + 20.0f;
    if (180.0f > total) {
        float d = 180.0f - total;
        total = 180.0f;
        if (20.0f > d)
            total = (20.0f - d) + 180.0f;
    }
    const Math::Rectangle_s005e_d750& ra = mWinRoot->GetRealArea();
    total = (ra.x2 - ra.x1) + (total - headerWidth);
    if (1.0f > total)
        total = 1.0f;
    mWinRoot->SetLayoutSize(total, nameArea.y2 - nameArea.y1);

    const Math::Rectangle_s005e_d750& hdr3 = mWinHeader->GetRealArea();
    headerWidth = hdr3.x2 - hdr3.x1;
    float finalWidth = total;
    if (mWinErrorGroup->GetFlags() & kWinFlagVisible) {
        mWinErrorGroup->SetLayoutLocation(mWinErrorGroup->GetRealArea().x1, bottom);
        const Math::Rectangle_s005e_d750& er = mWinErrorReason->GetRealArea();
        bottom = (er.y2 - er.y1) + (bottom + 4.0f);
    }

    mAbilities.reset();
    if (mShowAbilities && mWinAbilityLines) {
        const Math::Rectangle_s005e_d750& al = mWinAbilityLines->GetRealArea();
        mWinAbilityLines->SetLayoutSize(headerWidth, al.y2 - al.y1);
        mAbilities = abilities;
        mAbilities.mpObject->SetupWindow(mWinAbilityLines, bLocked);
    }
    bool showAbilities;
    if (mAbilities.mpObject && mAbilities.mpObject->GetCount() > 0) {
        bottom += 4.0f;
        Math::Rectangle_s005e_d750 area = mWinAbilityLines->GetRealArea();
        float y2 = (area.y2 - area.y1) + bottom;
        area.y1 = bottom;
        area.y2 = y2;
        mWinAbilityLines->SetLayoutArea(area);
        bottom = y2;
        float linesWidth = (area.x2 - area.x1) + 20.0f;
        const Math::Rectangle_s005e_d750& hdr4 = mWinHeader->GetRealArea();
        if (linesWidth > hdr4.x2 - hdr4.x1) {
            const Math::Rectangle_s005e_d750& hdr5 = mWinHeader->GetRealArea();
            finalWidth = (linesWidth - (hdr5.x2 - hdr5.x1)) + total;
        }
        showAbilities = true;
    } else {
        showAbilities = false;
    }
    mWinAbilityLines->SetFlag(kWinFlagVisible, showAbilities);
    mWinRoot->SetLayoutSize(finalWidth, ((bottom - headerTop) - 2.0f) - 2.0f);
    SetFlag(1);
    IWindow_s005e_d750* parent = mWinRoot->GetParent();
    if (parent)
        parent->BringToFront(mWinRoot);
    ForceVisibleLocation();
}
}  // namespace SP

// @ 0x005ee480
void cSPUIPropertyLayout_s005e_e480::SetItem(SP::cSPPaletteItem_s005e_e480* item, SP::cSPPaletteInfo_s005e_e480* info, SP::cSPEditorVehicleAbilities* content, bool show)
{
  if (item && info) {
    mpPaletteInfo = info;
    SP::cSPPaletteInfo_s005e_e480* const pInfo = mpPaletteInfo;
    SP::cCollectableItems_s005e_e480* const pItems = pInfo->mCollectableItems;
    SP::cSPEditorEconomy_s005e_e480* const pEconomy = pInfo->mEconomy;
    SetContents(&item->mItemKey, content, pEconomy, pInfo->mCurrencyChar, item->IsUnlocked(pItems), show);
  }
}

// @ 0x005efd40
namespace SP {
SPSpineCollisionFilter::~SPSpineCollisionFilter()
{}
}  // namespace SP

// @ 0x005efd70
namespace SP {
int AddTwo(int x)
{ return x + 2; }
}  // namespace SP

// @ 0x005efd80
namespace SP {
hkBool_s005e_f440 SPSpineCollisionFilter::isCollisionEnabled(hkUint32 infoA, hkUint32 infoB) const
{
  hkUint32 zeroIfSameSystemGroup = (infoA ^ infoB) & 0xffff0000;
  if (zeroIfSameSystemGroup == 0 && (infoA & 0xffff0000) != 0) {
    int idA = (infoA >> 5) & 0x1f;
    int idB = (infoB >> 5) & 0x1f;
    int dontCollideA = (infoA >> 10) & 0x1f;
    int dontCollideB = (infoB >> 10) & 0x1f;
    int d = idA - idB;
    if (d < 0)
      d = -d;
    if (d > dontCollideA && d > dontCollideB)
      return true;
    return false;
  }
  hkUint32 f = 0x1f;
  hkUint32 layerBitsA = m_collisionLookupTable[infoA & f];
  hkUint32 layerBitsB = hkUint32(1 << (infoB & f));
  return 0 != (layerBitsA & layerBitsB);
}
}  // namespace SP

// @ 0x005efe30
namespace SP {
hkBool_s005e_f440 SPSpineCollisionFilter::isCollisionEnabled(const hkpCollisionInput& input, const hkpCdBody& a, const hkpCdBody& b, const hkpShapeContainer& bContainer, hkUint32 bKey) const
{
  hkUint32 infoB = bContainer.getCollisionFilterInfo(bKey);
  hkUint32 infoA;
  if (a.getShapeKey() == 0xffffffff) {
    infoA = getRootCollidable(&a)->getCollisionFilterInfo();
  } else {
    const hkpCdBody* parent = a.getParent();
    do {
      int shapeType = parent->getShape()->getType();
      if (input.m_dispatcher->hasAlternateType(shapeType, 2)) {
        infoA = parent->getShape()->getCollisionFilterInfo(a.getShapeKey());
        goto done;
      }
      if (input.m_dispatcher->hasAlternateType(shapeType, 3)) {
        infoA = parent->getShape()->m_child->getCollisionFilterInfo(a.getShapeKey());
        goto done;
      }
      if (input.m_dispatcher->hasAlternateType(shapeType, 11)) {
        infoA = getRootCollidable(&a)->getCollisionFilterInfo();
        goto done;
      }
      parent = parent->getParent();
    } while (parent);
    infoA = 0;
  }
done:
  return isCollisionEnabled(infoA, infoB);
}
}  // namespace SP

// @ 0x005eff00
namespace SP {
hkBool_s005e_f440 SPSpineCollisionFilter::isCollisionEnabled(const hkpShapeRayCastInput& aInput, const hkpShapeContainer& bContainer, hkUint32 bKey) const
{
  hkUint32 infoB = bContainer.getCollisionFilterInfo(bKey);
  return isCollisionEnabled(aInput.m_filterInfo, infoB);
}
}  // namespace SP

// @ 0x005eff70
namespace SP {
void SPSpineCollisionFilter::enableCollisionsBetween(int layerA, int layerB)
{
  m_collisionLookupTable[layerA] |= hkUint32(1 << layerB);
  m_collisionLookupTable[layerB] |= hkUint32(1 << layerA);
}
}  // namespace SP

// @ 0x005effa0
namespace SP {
void SPSpineCollisionFilter::disableCollisionsUsingBitfield(hkUint32 layerBitsA, hkUint32 layerBitsB)
{
  for (int i = 0; i < 32; i++) {
    int b = 1 << i;
    if (b & layerBitsA)
      m_collisionLookupTable[i] &= ~layerBitsB;
    if (b & layerBitsB)
      m_collisionLookupTable[i] &= ~layerBitsA;
  }
}
}  // namespace SP

// @ 0x005effe0
namespace SP {
SPSpineCollisionFilter::SPSpineCollisionFilter()
{
  for (int i = 0; i < 32; i++)
    m_collisionLookupTable[i] = 0xffffffff;
  m_nextFreeSystemGroup = 0;
}
}  // namespace SP
