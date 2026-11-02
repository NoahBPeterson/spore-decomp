// src/game/SPEditors/_at_005c0000.cpp -- migrated from slice(s) s005c9230, s005c6340, s005c53c0, s005c1d70, s005c0c00 by tools/migrate/rewrite.py
// Object file: SPEditors/_at_005c0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Messaging/AutoHandler.h"
#include "EA/Messaging/IHandler.h"
#include "EA/Messaging/IHandlerRC.h"
#include "EA/UTFWin/IWinProc.h"
#include "EA/UTFWin/IWindow.h"
#include "EA/Stopwatch.h"
#include "SP/cDirectPropertyList.h"
#include "SP/cISPPaletteItemUI.h"
#include "SP/cPropertyList.h"
#include "SP/cSPEditorPaintLikeThis.h"
#include "SP/cSPPaletteItem.h"
#include "SP/cSPPaletteItemUI.h"
#include "SP/cSPPaletteItemUIOneClickPaint.h"
#include "SP/cSPPaletteItemUISelectable.h"
#include "SP/cSPUIAssetBrowserCallback.h"
#include "cSPUILayout.h"
#include "cSPUITooltipWinProc.h"
#include "SP/cString.h"
#include <new>
#include "SP/cSPPaletteCategoryUI.h"
#include "EA/Variant.h"
#include "SP/cSPEditorColorPicker.h"
#include "SP/cSPEditorPageControls.h"
#include "SP/cSPPaletteCategory.h"
#include "SP/cSPPalettePage.h"
#include "SP/cSPPalettePageUI.h"
#include "SP/cSPPaletteSubCategoryUI.h"
#include "SP/cSPSwatch.h"
#include <string.h>
#include "EA/Messaging/Server.h"
#include "EA/ResourceMan/Key.h"
#include "SP/cSPPalette.h"
#include "SP/cSPPaletteItemRollover.h"
#include "cSPUIPropertyLayout.h"

// ---- items of slice s005c0c00 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void pv##n();
namespace EA {
namespace ResourceMan {
class Key_s005c_0c00 { public:
  unsigned int mInstance, mType, mGroup;
  Key_s005c_0c00() {}
  Key_s005c_0c00(unsigned int i, unsigned int t, unsigned int g) : mInstance(i), mType(t), mGroup(g) {}
};
}
}
namespace SP {
class cSPPaletteItem_s005c_0c00 {
 public:
  cSPPaletteItem_s005c_0c00();  // FUN_005c66a0
  PV(0)
  virtual int AddRef();
  virtual int Release();
  void Init(const EA::ResourceMan::Key_s005c_0c00* key, int a, int b);  // 0x005c6810 (SP::cSPPaletteItem::Init)
  void Shutdown();  // 0x005c6710 (SP::cSPPaletteItem::Shutdown)
  char pad04[4];
  struct Iface {
    PV(0) PV(1) PV(2)
    virtual void* Cast(uint32_t id);  // +0xc
  } mIface;  // +0x8
  char pad0c[0x54 - 0xc];
};
}
namespace SP {
class cSPPaletteCategory_s005c_0c00 { public:
  char pad[0xc];
  struct Page { char pad[0x5c]; uint32_t mCategory; }** mPagesBegin;  // +0xc
  Page** mPagesEnd;                                                  // +0x10
  char pad14[0x34 - 0x14];
  cSPPaletteItem_s005c_0c00** mItemsBegin;  // +0x34
  cSPPaletteItem_s005c_0c00** mItemsEnd;    // +0x38
  int CountPagesInCategory(uint32_t category);
  bool HasItem(cSPPaletteItem_s005c_0c00* item);
};
}
// ---- items of slice s005c0c00 end

// ---- items of slice s005c1d70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* EASTL_memmove(void* dst, const void* src, unsigned int n);  // 0x011e0744 (static memmove)
namespace EA {
template <typename T>
class AutoRefCount_s005c_1d70 {
 public:
  T* mpObject;
  AutoRefCount_s005c_1d70() : mpObject(0) {}
  AutoRefCount_s005c_1d70(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  AutoRefCount_s005c_1d70(const AutoRefCount_s005c_1d70& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount_s005c_1d70() { if (mpObject) mpObject->Release(); }
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
class RefCountVTemplate_s005c_1d70 {
 public:
  RefCountVTemplate_s005c_1d70() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s005c_1d70() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace EA {
namespace COM {
class IUnknown32_s005c_1d70 {
 public:
  ~IUnknown32_s005c_1d70() {}
  virtual int AddRef();
  virtual int Release();
};
}
}
namespace EA {
namespace ResourceMan {
class Key_s005c_1d70 { public:
  unsigned int mInstance, mType, mGroup;
  Key_s005c_1d70() {}
  Key_s005c_1d70(unsigned int i, unsigned int t, unsigned int g) : mInstance(i), mType(t), mGroup(g) {}
};
}
}
namespace eastl {
template <typename T>
class sp_vector {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  int mAllocator[2];
  sp_vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~sp_vector() {
    if (mpBegin && ((int*)mpBegin)[-1] != 0)
      EASTL_allocator_deallocate(mpBegin);
  }
  unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
  T* begin() { return mpBegin; }
  T* end() { return mpEnd; }
  T& operator[](unsigned int i) { return mpBegin[i]; }
  T* DoInsertValue(T* position, const T& value);
  void push_back(const T& value) {
    if (mpEnd < mpCapacity)
      ::new (mpEnd++) T(value);
    else
      DoInsertValue(mpEnd, value);
  }
  T* insert(T* position, const T& value);
  T* erase(T* first, T* last) {  // trivially copyable T
    EASTL_memmove(first, last, (unsigned int)((char*)mpEnd - (char*)last));
    mpEnd -= (last - first);
    return first;
  }
  void clear() { erase(mpBegin, mpEnd); }
};
}
namespace eastl {
template <typename T>
class sp_ref_vector : public sp_vector<EA::AutoRefCount_s005c_1d70<T> > {
 public:
  typedef EA::AutoRefCount_s005c_1d70<T> value_type;
  ~sp_ref_vector();  // FUN_005c7f10 (out of line)
  value_type* erase(value_type* first, value_type* last);
  void clear() { erase(this->mpBegin, this->mpEnd); }
};
}
namespace SP {
class cString_s005c_1d70 {
 public:
  cString_s005c_1d70();
  ~cString_s005c_1d70();
  const wchar_t* GetText();  // 0x006b55c0
  char pad[0x14];
};
}
namespace SP {
class cSPPalettePage_s005c_1d70 {
 public:
  PV(0)
  virtual int AddRef();
  virtual int Release();
  void Shutdown();  // FUN_005c7ed0
  char pad04[0x58 - 4];
  uint32_t mSequenceNumber;  // +0x58
  uint32_t mPackID;          // +0x5c
  uint32_t mRegionFilter;    // +0x60
};
}
namespace SP {
class cSPPaletteCategory_s005c_1d70 : public EA::RefCountVTemplate_s005c_1d70<int>, public EA::COM::IUnknown32_s005c_1d70 {
 public:
  eastl::sp_ref_vector<cSPPalettePage_s005c_1d70> mPages;                  // +0xc
  eastl::sp_vector<unsigned int> mPacks;                         // +0x20
  eastl::sp_ref_vector<cSPPaletteCategory_s005c_1d70> mSubCategories;       // +0x34
  unsigned int mLayoutInstanceID;                                // +0x48
  unsigned int mSequenceNumber;                                  // +0x4c
  bool mPaintByNumber;                                           // +0x50
  unsigned int mRegionFilter;                                    // +0x54
  unsigned int mSkinPaintIndex;                                  // +0x58
  cString_s005c_1d70 mCategoryName;                                         // +0x5c
  bool mHasMultiImageButton;                                     // +0x70
  unsigned int mCategoryId;                                      // +0x74
  unsigned int mParentCategory;                                  // +0x78
  EA::ResourceMan::Key_s005c_1d70 mButtonImageKey;                          // +0x7c
  EA::ResourceMan::Key_s005c_1d70* mpButtonImageKeys;                       // +0x88
  bool mIsSubCategory;                                           // +0x8c

  cSPPaletteCategory_s005c_1d70();
  ~cSPPaletteCategory_s005c_1d70();
  virtual int AddRef();
  virtual int Release();
  cSPPaletteCategory_s005c_1d70* FindSubCategory(uint32_t categoryID);
  bool Init(const EA::ResourceMan::Key_s005c_1d70& key, unsigned int layoutInstanceID);  // 0x005c1e20 (SP::cSPPaletteCategory::Init)
  void Shutdown();
  void AddSubCategory(cSPPaletteCategory_s005c_1d70* category);
  void AddPage(cSPPalettePage_s005c_1d70* page);
  unsigned int GetNumPages() { return mPages.size(); }
  cSPPalettePage_s005c_1d70* GetPage(int index);           // FUN_005c1ce0
  int CountPagesInCategory(uint32_t packID);    // FUN_005c1d10
};
}
// ---- items of slice s005c1d70 end

// ---- items of slice s005c53c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
class cSPPaletteCategory_s005c_53c0;
}
namespace SP {
class cSPPalettePage_s005c_53c0;
}
namespace SP {
class cSPPaletteItem_s005c_53c0;
}
namespace SP {
struct Key {
  uint32_t mInstance;
  uint32_t mType;
  uint32_t mGroup;
};
}
namespace SP {
class cSPPaletteItem_s005c_53c0 {
 public:
  virtual void v0();
  virtual int AddRef();
  virtual int Release();
  char pad4[8];
  Key mItemKey;  // +0xc
  uint32_t mThumbKey_Inst;   // +0x18
  uint32_t mThumbKey_Type;   // +0x1c
  uint32_t mThumbKey_Group;  // +0x20
  char pad24[0x24];
  int mRegion;  // +0x48
  char pad4c[8];
  cSPPaletteItem_s005c_53c0();  // 0x005c66a0
  void Init(Key* key, int region, uint32_t thumbGroup);  // 0x005c6810
};
}
namespace SP {
class cSPPalettePage_s005c_53c0 {
 public:
  virtual void v0();
  virtual int AddRef();
  virtual int Release();
  char pad4[0x58];
  int m5c;       // +0x5c
  uint32_t m60;  // +0x60
  Key mCategoryKey;  // +0x64
  cSPPaletteItem_s005c_53c0** mItemsBegin;  // +0x70
  cSPPaletteItem_s005c_53c0** mItemsEnd;    // +0x74
  char pad78[0xc];
  cSPPalettePage_s005c_53c0();  // 0x005c7f50
  bool Init(Key* key, uint32_t a, uint32_t b, uint32_t c, uint32_t d);  // 0x005c8ad0
  cSPPaletteItem_s005c_53c0* GetItem(int i);                                        // 0x005c7f00
};
}
namespace SP {
class cSPPaletteCategory_s005c_53c0 {
 public:
  virtual void v0();
  virtual int AddRef();
  virtual int Release();
  char pad4[0x8];
  cSPPalettePage_s005c_53c0** mPagesBegin;  // +0xc
  cSPPalettePage_s005c_53c0** mPagesEnd;    // +0x10
  char pad14[0x20];
  cSPPaletteCategory_s005c_53c0** mSubBegin;  // +0x34
  cSPPaletteCategory_s005c_53c0** mSubEnd;    // +0x38
  char pad3c[0xc];
  uint32_t mRegionFilter;  // +0x48
  uint32_t mSortKey;       // +0x4c
  char pad50[4];
  uint32_t mNameLocal;  // +0x54
  uint32_t mNameSrc;    // +0x58
  char pad5c[0x18];
  int mId;  // +0x74
  char pad78[0x18];
  cSPPaletteCategory_s005c_53c0();                                       // 0x005c2020
  void Init(Key* key, uint32_t group);                        // 0x005c1e20
  void Shutdown();                                            // 0x005c2230
  cSPPaletteCategory_s005c_53c0* FindSubCategory(int id);                // 0x005c1d70
  bool HasSubCategory(cSPPaletteCategory_s005c_53c0* c);                 // 0x005c1d40
  void AddSubCategory(cSPPaletteCategory_s005c_53c0* c);                 // 0x005c22b0
  void AddPage(cSPPalettePage_s005c_53c0* p);                            // 0x005c2390
  cSPPalettePage_s005c_53c0* GetPage(int i);                             // 0x005c1ce0
};
}
namespace SP {
class RefCountVTemplate {
 public:
  RefCountVTemplate() { mRefCount = 0; }
  virtual ~RefCountVTemplate() {}
  virtual int AddRef();             // 0x005454f0
  virtual int Release();            // 0x00453540
  virtual int GetReferenceCount();  // 0x004535b0
  int mRefCount;
};
}
namespace SP {
class IUnknown32 {
 public:
  virtual int AddRef() = 0;
  virtual int Release() = 0;
  virtual ~IUnknown32() {}
};
}
namespace SP {
struct CatVector {
  cSPPaletteCategory_s005c_53c0** mBegin;
  cSPPaletteCategory_s005c_53c0** mEnd;
  cSPPaletteCategory_s005c_53c0** mCap;
  CatVector() : mBegin(0), mEnd(0), mCap(0) {}
  ~CatVector();  // 0x005c7f10, out of line
  void InsertAux(cSPPaletteCategory_s005c_53c0** pos, cSPPaletteCategory_s005c_53c0** val);  // 0x005c8480
};
}
namespace SP {
class cSPPalette_s005c_53c0 : public RefCountVTemplate, public IUnknown32 {
 public:
  CatVector mCats;  // +0xc, eastl::vector<AutoRefCount<cSPPaletteCategory>>
  char pad18[8];
  uint32_t m20;  // +0x20
  uint32_t m24;  // +0x24
  uint32_t m28;  // +0x28
  uint32_t m2c;  // +0x2c
  uint32_t m30;  // +0x30
  uint32_t m34;  // +0x34
  int m38;       // +0x38
  int m3c;       // +0x3c

  cSPPalette_s005c_53c0();
  ~cSPPalette_s005c_53c0();
  virtual int AddRef();   // 0x00804910
  virtual int Release();  // 0x00834200
  void ShutdownChildren();                                   // 0x005c5c20
  __declspec(noinline) int CountItems(cSPPalettePage_s005c_53c0* page, int* pOut);           // 0x005c5c50
  __declspec(noinline) bool AllItemsListed(cSPPalettePage_s005c_53c0* page, cSPPaletteCategory_s005c_53c0* cat);  // 0x005c5cc0
  __declspec(noinline) cSPPaletteCategory_s005c_53c0* FindCategory(int id);                  // 0x005c5df0
  __declspec(noinline) void AddCategory(cSPPaletteCategory_s005c_53c0* cat);                 // 0x005c5f00
  void LoadDefinitionPart(Key* key);                         // 0x005c6010
};
}
// ---- items of slice s005c53c0 end

// ---- items of slice s005c6340 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
template <typename T>
class AutoRefCount_s005c_6340 {
 public:
  T* mpObject;
  AutoRefCount_s005c_6340() : mpObject(0) {}
  AutoRefCount_s005c_6340(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount_s005c_6340() { if (mpObject) mpObject->Release(); }
  AutoRefCount_s005c_6340& operator=(T* p) {
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
  T** AsPPTypeParam();  // 0x00a16f40 (out of line)
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};
}
namespace EA {
template <typename T>
class RefCountVTemplate_s005c_6340 {
 public:
  RefCountVTemplate_s005c_6340() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s005c_6340() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace EA {
namespace COM {
class IUnknown32_s005c_6340 {
 public:
  ~IUnknown32_s005c_6340() {}
  virtual int AddRef() = 0;
  virtual int Release() = 0;
  virtual void* Cast(uint32_t typeID) const = 0;
};  // namespace COM
}
}
namespace EA {
namespace ResourceMan {
class Key_s005c_6340 { public:
  unsigned int mInstance, mType, mGroup;
};
}
}
namespace EA {
class RectT_s005c_6340 { public:
  float left, top, right, bottom;
  RectT_s005c_6340(const RectT_s005c_6340& r) : left(r.left), top(r.top), right(r.right), bottom(r.bottom) {}
};
}
namespace EA {
namespace UTFWin {
class IWinProc_s005c_6340;
}
}
namespace EA {
namespace UTFWin {
class IWindow_s005c_6340 : public COM::IUnknown32_s005c_6340 {
 public:
  PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
  virtual const RectT_s005c_6340& GetRealArea();  // +0x34
  virtual const RectT_s005c_6340& GetArea();      // +0x38
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27)
  PV(28) PV(29) PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40)
  PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53)
  PV(54) PV(55) PV(56) PV(57) PV(58) PV(59) PV(60) PV(61) PV(62) PV(63) PV(64)
  virtual void AddWinProc(IWinProc_s005c_6340* proc);     // +0x104
  virtual void RemoveWinProc(IWinProc_s005c_6340* proc);  // +0x108
};
}
}
namespace EA {
namespace UTFWin {
class Message_s005c_6340 { public:
  uint32_t pad0[2];
  int mEventType;   // +0x8
  int mParam0c;     // +0xc
  uint32_t pad10[2];
  int mButton;      // +0x18
};
}
}
namespace EA {
namespace UTFWin {
class IWinProc_s005c_6340 : public COM::IUnknown32_s005c_6340 {
 public:
  virtual int GetEventFlags();
  virtual bool DoMessage(IWindow_s005c_6340* window, const Message_s005c_6340& message) = 0;
};
}
}
namespace EA {
namespace Messaging {
class IHandler_s005c_6340 {
 public:
  virtual bool HandleMessage(uint32_t messageID, void* message) = 0;
};
}
}
namespace EA {
namespace Messaging {
class IHandlerRC_s005c_6340 : public IHandler_s005c_6340 {
 public:
  virtual int AddRef() = 0;
  virtual int Release() = 0;
};
}
}
namespace EA {
namespace Messaging {
class IMessageServer {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void MessageSend(uint32_t messageID, void* message, IHandler_s005c_6340* handler);       // +0x14
  PV(6) PV(7)
  virtual void AddHandler(IHandlerRC_s005c_6340* handler, uint32_t messageID);                     // +0x20
  PV(9) PV(10)
  virtual void RemoveHandler(IHandlerRC_s005c_6340* handler, uint32_t messageID, int priority);    // +0x2c
};
}
}
using EA::AutoRefCount_s005c_6340;
using EA::ResourceMan::Key_s005c_6340;
using EA::UTFWin::IWindow_s005c_6340;
using EA::UTFWin::IWinProc_s005c_6340;
using EA::UTFWin::Message_s005c_6340;
using EA::RectT_s005c_6340;
namespace SP {
EA::Messaging::IMessageServer* MessageServer();                                     // 0x0067dcc0
}
namespace SP {
class cSPPaletteItem_s005c_6340 : public EA::RefCountVTemplate_s005c_6340<int>, public EA::COM::IUnknown32_s005c_6340 {
 public:
  enum eItemType {
    kItemTypeUnknown = -1,
    kBlock = 0xa2e50993,
    kBakedModel = 0x674ab27,
    kSwatch = 0x2c7c0887,
  };
  Key_s005c_6340 mItemKey;          // +0xc
  Key_s005c_6340 mThumbnailKey;     // +0x18
  eItemType mItemType;   // +0x24
  int mPriority;         // +0x28
  Key_s005c_6340 mSwatchKey;        // +0x2c
  uint32_t mSwatchColor; // +0x38
  Key_s005c_6340 mSwatchKey2;       // +0x3c
  int mIndex;            // +0x48
  bool mbHidden;         // +0x4c
  AutoRefCount_s005c_6340<EA::COM::IUnknown32_s005c_6340> mpData;  // +0x50

  virtual int AddRef();
  virtual int Release();
  bool Init(const Key_s005c_6340& key, int index, uint32_t thumbnailGroup);  // 0x005c6810 (SP::cSPPaletteItem::Init)
  void Shutdown();  // 0x005c6710 (SP::cSPPaletteItem::Shutdown)
};
}
namespace SP {
struct cTargetInner {
  PV(0) PV(1) PV(2)
  virtual void* Cast(uint32_t typeID);  // +0xc
};
}
namespace SP {
struct cItemTarget {
  uint32_t pad[2];
  cTargetInner mInner;  // +0x8
};
}
namespace SP {
class cISPPaletteItemUI_s005c_6340 {
 public:
  enum eItemUIInterfaceID { kItemUIUnknown = -1 };
  cISPPaletteItemUI_s005c_6340() : mInterfaceID(kItemUIUnknown) {}
  virtual ~cISPPaletteItemUI_s005c_6340() {}
  virtual void Init(cSPPaletteItem_s005c_6340* item, IWindow_s005c_6340* window, int a, int b) = 0;  // +0x4
  virtual void Shutdown() = 0;                                              // +0x8
  PV(3)
  virtual struct cItemTarget* GetTarget();                                  // +0x10
  PV(5) PV(6)
  virtual void OnRollover() = 0;                                            // +0x1c
  virtual void OffRollover() = 0;                                           // +0x20
  virtual void OnMouseDown();                                               // +0x24
  virtual void OnMouseUp();                                                 // +0x28
  PV(11) PV(12) PV(13) PV(14)
  virtual void Select();                                                    // +0x3c
  virtual void Deselect();                                                  // +0x40

  AutoRefCount_s005c_6340<cSPPaletteItem_s005c_6340> mPaletteItem;  // +0x4
  eItemUIInterfaceID mInterfaceID;            // +0x8
};
}
namespace SP {
class cSPPaletteItemUI_s005c_6340 : public cISPPaletteItemUI_s005c_6340, public IWinProc_s005c_6340, public EA::RefCountVTemplate_s005c_6340<int> {
 public:
  cSPPaletteItemUI_s005c_6340();
  ~cSPPaletteItemUI_s005c_6340();
  virtual void Init(cSPPaletteItem_s005c_6340* item, IWindow_s005c_6340* window, int a, int b);  // 0x005c6ca0 (SP::cSPPaletteItemUI::Init)
  virtual void Shutdown();  // 0x005c6d20 (SP::cSPPaletteItemUI::Shutdown)
  virtual void OnRollover();  // 0x005c6f00 (SP::cSPPaletteItemUI::OnRollover)
  virtual void OffRollover();  // 0x005c6f40 (SP::cSPPaletteItemUI::OffRollover)
  void Trigger();  // 0x005c73d0 (SP::cSPPaletteItemUI::Trigger)
  virtual int AddRef();
  virtual int Release();
  virtual void* Cast(uint32_t typeID) const;
  virtual bool DoMessage(IWindow_s005c_6340* window, const Message_s005c_6340& message);  // 0x005c6d70 (SP::cSPPaletteItemUI::DoMessage)

  bool mIsRolledOver;               // +0x18
  AutoRefCount_s005c_6340<IWindow_s005c_6340> mWinRoot;   // +0x1c
};
}
namespace SP {
class cSPPaletteItemUISelectable_s005c_6340 : public cSPPaletteItemUI_s005c_6340, public EA::Messaging::IHandlerRC_s005c_6340 {
 public:
  cSPPaletteItemUISelectable_s005c_6340();
  virtual void Init(cSPPaletteItem_s005c_6340* item, IWindow_s005c_6340* window, int a, int b, uint32_t selectionGroup);  // 0x005c6f80 (SP::cSPPaletteItemUISelectable::Init)
  virtual void Shutdown();  // 0x005c6fd0 (SP::cSPPaletteItemUISelectable::Shutdown)
  virtual void* Cast(uint32_t typeID) const;
  virtual void SetIsSelected(bool selected);
  virtual bool HandleMessage(uint32_t messageID, void* message);
  virtual int AddRef();
  virtual int Release();

  bool mSelected;             // +0x24
  uint32_t mSelectionGroup;   // +0x28
};
}
namespace SP {
class cPaletteWidget {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void Refresh();             // +0x14
  PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
  virtual void SetVisible(bool v);    // +0x34
  void Show();
};
}
// ---- items of slice s005c6340 end

// ---- items of slice s005c9230 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kRealOne;   // 0x01485720  _HK_REAL_ONE
extern const float kScrollRate;   // 0x013eb960
extern float kMinRatio;           // 0x013f9428
extern float kHalf;               // 0x01471064
extern void* gPaletteImages[6];   // 0x01516838 .. 0x0151688c
namespace EA {
template <typename T>
class AutoRefCount_s005c_9230 {
 public:
  T* mpObject;
  AutoRefCount_s005c_9230() : mpObject(0) {}
  AutoRefCount_s005c_9230(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount_s005c_9230() { if (mpObject) mpObject->Release(); }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};  // namespace EA
}
using EA::AutoRefCount_s005c_9230;
namespace EA {
namespace UTFWin {
class IUnknown32_s005c_9230 {
 public:
  virtual int AddRef();   // +0
  virtual int Release();  // +4
};
}
}
namespace EA {
namespace UTFWin {
class IWindow_s005c_9230 : public IUnknown32_s005c_9230 {
 public:
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
  PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24)
  PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
  virtual void SetFlag(int flag, int value);  // +0x7c
};
}
}
using EA::UTFWin::IWindow_s005c_9230;
namespace eastl {
template <typename T>
class sp_trivial_vector {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  int mAllocator[2];
  sp_trivial_vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~sp_trivial_vector() {
    if (mpBegin && ((int*)mpBegin)[-1] != 0)
      EASTL_allocator_deallocate(mpBegin);
  }
};
}
namespace eastl {
template <typename T>
class sp_ref_vector_s005c_9230 {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  int mAllocator[2];
  sp_ref_vector_s005c_9230() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~sp_ref_vector_s005c_9230();
  unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
  T& operator[](unsigned int i) { return mpBegin[i]; }
};
}
template <typename Fn>
static Fn vslot(void* object, unsigned int n) {
  return (Fn)(*(void**)((char*)(*(void**)object) + n));
}
class cB0 { public: virtual ~cB0() {} PV(1) PV(2) };
class cB1 { public: virtual ~cB1() {} PV(1) PV(2) };
class cB2 {
 public:
  cB2() : mFieldc(0) {}
  virtual ~cB2() {}
  PV(1) PV(2)
  int mFieldc;
};
struct FeedDescriptor {
  char pad0[0x74];
  int mFeedId;      // +0x74
};
class cFeedCategory {
 public:
  char pad0[0x6c];
  FeedDescriptor* mpFeedData;  // +0x6c  points at the feed descriptor
};
class cUIMissionCard : public cB0, public cB1, public cB2 {
 public:
  cUIMissionCard();
  virtual ~cUIMissionCard();

  AutoRefCount_s005c_9230<IWindow_s005c_9230> mWindow;            // +0x10
  int mSelectedIndex;                       // +0x14
  float mFloat18;                           // +0x18
  float mFloat1c;                           // +0x1c
  char pad20[0x10];                         // +0x20
  eastl::sp_trivial_vector<int> mVec30;     // +0x30  item UI objects (void*)
  eastl::sp_trivial_vector<int> mVec44;     // +0x44
  eastl::sp_trivial_vector<int> mVec58;     // +0x58
  eastl::sp_ref_vector_s005c_9230<AutoRefCount_s005c_9230<cFeedCategory> > mVec6c;  // +0x6c
  eastl::sp_trivial_vector<int> mVec80;     // +0x80  per-entry fade weights (float)

  void SetWindowFlag(int value);   // 0x005c9810
  cFeedCategory* GetCurrent();     // 0x005c9830
  bool DoMessage(int messageType, void* message);   // 0x005c9dd0
};
class cSPPaletteCategoryUI;
class cSPPaletteSubCategoryUI {
 public:
  char pad0[0x14];
  int   mSelectedIndex;         // +0x14   index of the highlighted entry
  float mStep;                  // +0x18   per-slot offset step
  float mClipHeight;            // +0x1c   denominator for the scroll ratio
  float mTopHidden;             // +0x20
  float mTopVisible;            // +0x24
  float mBottomVisible;         // +0x28
  float mBottomHidden;          // +0x2c
  eastl::sp_trivial_vector<void*> mVec30;    // +0x30  item UI objects
  eastl::sp_trivial_vector<void*> mVec44;    // +0x44  icon handles
  eastl::sp_trivial_vector<void*> mVec58;    // +0x58  window objects
  eastl::sp_trivial_vector<void*> mVec6c;    // +0x6c
  eastl::sp_trivial_vector<float> mVec80;    // +0x80  fade weights

  void Update(unsigned int deltaMs);
};
void FUN_00806c60(float* out, void* frame);                            // 0x00806c60
void FUN_00806ca0(void* window, float x, float y);                     // 0x00806ca0
void FUN_00808190(void* window, float a, float b);                     // 0x00808190
float __cdecl GetAlpha(void* window);                                  // 0x00805040
void __cdecl SetWindowAlpha(void* window, float alpha);                // 0x00804fc0
void __cdecl SetWindowImage(void* window, void* image, int flags);     // 0x00807bb0
void cSPPaletteCategoryUI_Update(cSPPaletteCategoryUI* self, unsigned int dt);  // 0x005c28b0
void cSPPaletteCategoryUI_SetVisibility(cSPPaletteCategoryUI* self, bool visible); // 0x005c2960
// ---- items of slice s005c9230 end

// @ 0x005c1d10
namespace SP {
int cSPPaletteCategory_s005c_0c00::CountPagesInCategory(uint32_t category)
{
  int n = (int)(mPagesEnd - mPagesBegin);
  int count = 0;
  for (int i = 0; i < n; i++) {
    if (mPagesBegin[i]->mCategory == category)
      count++;
  }
  return count;
}
}  // namespace SP

// @ 0x005c1d70
namespace SP {
cSPPaletteCategory_s005c_1d70* cSPPaletteCategory_s005c_1d70::FindSubCategory(uint32_t categoryID)
{
  for (unsigned int i = 0; i < mSubCategories.size(); i++) {
    EA::AutoRefCount_s005c_1d70<cSPPaletteCategory_s005c_1d70>& sub = mSubCategories[i];
    if (sub->mCategoryId == categoryID)
      return sub;
    cSPPaletteCategory_s005c_1d70* found = sub->FindSubCategory(categoryID);
    if (found)
      return found;
  }
  return 0;
}
}  // namespace SP

// @ 0x005c5c20
namespace SP {
void cSPPalette_s005c_53c0::ShutdownChildren()
{
  int count = (int)(mCats.mEnd - mCats.mBegin);
  for (int i = 0; i < count; i++)
    mCats.mBegin[i]->Shutdown();
}
}  // namespace SP

// @ 0x005c6ab0
namespace SP {
void cPaletteWidget::Show()
{
  SetVisible(true);
  Refresh();
}
}  // namespace SP

// @ 0x005c6ad0
namespace SP {
void cSPPaletteItemUISelectable_s005c_6340::SetIsSelected(bool selected)
{
  if (selected) {
    MessageServer()->MessageSend(0x47a9a20, this, 0);
  } else if (mSelected) {
    mSelected = false;
    Deselect();
  }
}
}  // namespace SP

// @ 0x005c9810
void cUIMissionCard::SetWindowFlag(int value)
{
  if (mWindow)
    mWindow->SetFlag(1, value);
}

// @ 0x005c9830
cFeedCategory* cUIMissionCard::GetCurrent()
{
  int index = mSelectedIndex;
  if (index >= 0 && index < (int)mVec6c.size())
    return mVec6c[index];
  return 0;
}

// @ 0x005c98a0
void cSPPaletteSubCategoryUI::Update(unsigned int deltaMs)
{
  // delta = clamp((float)deltaMs * 0.01f, 0.0f, 1.0f)
  float delta = (float)(int)deltaMs * kScrollRate;
  if (delta < 0.0f)
    delta = 0.0f;
  if (delta > kRealOne)
    delta = kRealOne;

  if ((((char*)mVec58.mpEnd - (char*)mVec58.mpBegin) ^
       ((char*)mVec30.mpEnd - (char*)mVec30.mpBegin)) & ~3u) {
    // Array sizes disagree: nothing to animate.
  } else {
    // Pass 1: slide each entry toward its slot, then move it to the lerped point.
    const int count = (int)(mVec30.mpEnd - mVec30.mpBegin);
    for (int i = 0; i < count; ++i) {
      float target;
      if (mSelectedIndex < i)
        target = (mBottomHidden - mTopVisible) - (float)(count - i) * mStep;
      else
        target = (float)i * mStep;

      void* const item = mVec30.mpBegin[i];
      typedef void* (__thiscall *GetObjFn)(void*);
      void* const obj = vslot<GetObjFn>(item, 0x10)(item);

      float point[2];
      FUN_00806c60(point, obj);
      const float x = point[0] - point[0] * delta;
      const float y = point[1] + (target - point[1]) * delta;

      void* const obj2 = vslot<GetObjFn>(item, 0x10)(item);
      typedef void (__thiscall *SetPosFn)(void*, float, float);
      vslot<SetPosFn>(obj2, 0x64)(obj2, x, y);
    }

    // Pass 2: stretch each window between the current and next entry, then fade it.
    const int wcount = (int)(mVec58.mpEnd - mVec58.mpBegin);
    for (int i = 0; i < wcount; ++i) {
      typedef void* (__thiscall *GetObjFn)(void*);
      typedef void* (__thiscall *GetBoxFn)(void*);
      void* const item = mVec30.mpBegin[i];
      void* const obj = vslot<GetObjFn>(item, 0x10)(item);
      const float top = *(float*)((char*)vslot<GetBoxFn>(obj, 0x38)(obj) + 0xc);
      const float mid = mBottomVisible - mTopHidden;

      float bottom;
      if (i == (int)(mVec30.mpEnd - mVec30.mpBegin) - 1) {
        bottom = mBottomHidden - mTopVisible;
      } else {
        void* const nitem = mVec30.mpBegin[i + 1];
        void* const nobj = vslot<GetObjFn>(nitem, 0x10)(nitem);
        bottom = *(float*)((char*)vslot<GetBoxFn>(nobj, 0x38)(nobj) + 4);
      }

      void* const window = mVec58.mpBegin[i];
      FUN_00806ca0(window, mid * kHalf, (bottom + top) * kHalf);

      float ratio = (bottom - top) / mClipHeight;
      if (ratio == 0.0f)
        ratio = kMinRatio;
      FUN_00808190(window, kRealOne, ratio);

      float alpha = GetAlpha(window);
      float weight = mVec80.mpBegin[i];
      if (weight != kRealOne)
        weight = (weight - alpha) * delta * kHalf + alpha;
      SetWindowAlpha(window, weight);
      cSPPaletteCategoryUI_SetVisibility((cSPPaletteCategoryUI*)mVec6c.mpBegin[i],
                                         ratio > kScrollRate);
    }
  }

  // Refresh every category UI.
  const int ccount = (int)(mVec6c.mpEnd - mVec6c.mpBegin);
  for (int i = 0; i < ccount; ++i)
    cSPPaletteCategoryUI_Update((cSPPaletteCategoryUI*)mVec6c.mpBegin[i], deltaMs);

  // Pick each entry's icon from its state flags and push it to the window.
  const int icount = (int)(mVec30.mpEnd - mVec30.mpBegin);
  for (int i = 0; i < icount; ++i) {
    void* const item = mVec30.mpBegin[i];
    typedef unsigned (__thiscall *GetFlagsFn)(void*);
    const unsigned flags = vslot<GetFlagsFn>(item, 0x20)(item);
    void* image;
    if (flags & 4) {
      if (flags & 2)
        image = gPaletteImages[4];
      else if (flags & 8)
        image = gPaletteImages[3];
      else
        image = gPaletteImages[2];
    } else {
      if (flags & 2)
        image = gPaletteImages[1];
      else if (flags & 8)
        image = gPaletteImages[0];
      else
        image = gPaletteImages[2];
    }
    SetWindowImage(mVec44.mpBegin[i], image, -1);
  }
}

// @ 0x005c9c70
cUIMissionCard::cUIMissionCard()
: mSelectedIndex(0), mFloat18(0.0f), mFloat1c(0.0f) {}

// @ 0x005c9d10
cUIMissionCard::~cUIMissionCard()
{}
