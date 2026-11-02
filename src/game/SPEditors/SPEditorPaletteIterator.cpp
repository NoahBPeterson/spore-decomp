// src/game/SPEditors/SPEditorPaletteIterator.cpp -- migrated from slice(s) s005c7500 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorPaletteIterator.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ResourceMan/Key.h"
#include "SP/cPropertyList.h"
#include "SP/cSPOLDPaletteItemUI.h"
#include "SP/cSPPalette.h"
#include "SP/cSPPaletteCategory.h"
#include "SP/cSPPaletteItem.h"
#include "SP/cSPPalettePage.h"
#include "SP/cSPSwatch.h"
#include "cSPUILayout.h"
#include "cSPUITooltipWinProc.h"
#include "SP/cString.h"
#include <new>

// ---- items of slice s005c7500 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void pv##n();
namespace EA {
template <typename T>
class AutoRefCount_s005c_7500 {
 public:
  T* mpObject;
  AutoRefCount_s005c_7500() : mpObject(0) {}
  AutoRefCount_s005c_7500(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  AutoRefCount_s005c_7500(const AutoRefCount_s005c_7500& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount_s005c_7500() { if (mpObject) mpObject->Release(); }
  AutoRefCount_s005c_7500& operator=(T* p) {
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
  AutoRefCount_s005c_7500& operator=(const AutoRefCount_s005c_7500& x);  // 0x005766e0 (out of line)
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
class RefCountVTemplate_s005c_7500 {
 public:
  RefCountVTemplate_s005c_7500() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s005c_7500() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace EA {
namespace COM {
class IUnknown32_s005c_7500 {
 public:
  ~IUnknown32_s005c_7500() {}
  virtual int AddRef();
  virtual int Release();
};  // namespace COM
}
}
namespace EA {
namespace ResourceMan {
class Key_s005c_7500 {
 public:
  unsigned int mInstance, mType, mGroup;
  Key_s005c_7500() {}
  Key_s005c_7500(unsigned int i, unsigned int t, unsigned int g) : mInstance(i), mType(t), mGroup(g) {}
};  // namespace ResourceMan
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
  ~sp_vector() {}
  T* begin() { return mpBegin; }
  T* end() { return mpEnd; }
};
}
namespace eastl {
template <typename T>
class sp_vector0 {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  sp_vector0() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~sp_vector0();
  T* begin() { return mpBegin; }
  T* end() { return mpEnd; }
};
}
using EA::AutoRefCount_s005c_7500;
namespace SP {
class cSPPalettePage_s005c_7500;
}
namespace SP {
class cSPPaletteItem_s005c_7500;
}
namespace SP {
class cSPPaletteCategory_s005c_7500 {
 public:
  PV(0)
  virtual int AddRef();
  virtual int Release();
  char pad04[8];                                            // +4
  eastl::sp_vector<AutoRefCount_s005c_7500<cSPPalettePage_s005c_7500> > mPages;   // +0xc
  eastl::sp_vector<unsigned int> mPacks;                    // +0x20
  eastl::sp_vector<AutoRefCount_s005c_7500<cSPPaletteCategory_s005c_7500> > mSubCategories;  // +0x34
  cSPPaletteCategory_s005c_7500* GetSubCategory(int index);  // 0x005cae30
  cSPPalettePage_s005c_7500* GetPage(int index);             // 0x005c1ce0
};
}
namespace SP {
class cSPPalette_s005c_7500 {
 public:
  PV(0)
  virtual int AddRef();
  virtual int Release();
  char pad04[8];                                             // +4
  eastl::sp_vector<AutoRefCount_s005c_7500<cSPPaletteCategory_s005c_7500> > mCategories;  // +0xc
  cSPPaletteCategory_s005c_7500* GetCategory(int index);  // 0x005c5de0
};
}
namespace SP {
class cSPPaletteItem_s005c_7500 : public EA::RefCountVTemplate_s005c_7500<int>, public EA::COM::IUnknown32_s005c_7500 {
 public:
  using EA::RefCountVTemplate_s005c_7500<int>::AddRef;
  using EA::RefCountVTemplate_s005c_7500<int>::Release;
  cSPPaletteItem_s005c_7500();  // 0x005c66a0
  bool Init(const EA::ResourceMan::Key_s005c_7500& key, int index, uint32_t thumbnailGroupID);  // 0x005c6810
  enum eItemType {
    kItemTypeUnknown = -1,
    kBlock = 0xa2e50993,
    kBakedModel = 0x674ab27,
    kSwatch = 0x2c7c0887,
  };
  EA::ResourceMan::Key_s005c_7500 mItemKey;          // +0xc
  EA::ResourceMan::Key_s005c_7500 mThumbnailKey;     // +0x18
  eItemType mItemType;                    // +0x24
  int mPriority;                          // +0x28
  EA::ResourceMan::Key_s005c_7500 mSwatchKey;        // +0x2c
  uint32_t mSwatchColor;                  // +0x38
  EA::ResourceMan::Key_s005c_7500 mSwatchKey2;       // +0x3c
  int mIndex;                             // +0x48
  bool mbHidden;                          // +0x4c
  AutoRefCount_s005c_7500<EA::COM::IUnknown32_s005c_7500> mpData;  // +0x50
  void Shutdown();                        // 0x005c6710
  // Out-of-line trivial accessors / checks called by cSPOLDPaletteItemUI::Init.
  int GetPriority();                      // 0x00641770: return [this+0x28]
  EA::ResourceMan::Key_s005c_7500* GetPlanetKey();   // 0x00b7e380: return &[this+0x2c]
  uint32_t GetSwatchColor();              // 0x00a1ad10: return [this+0x38]
  EA::ResourceMan::Key_s005c_7500* GetCities();      // 0x005c65e0: return &[this+0x3c]
  bool IsHidden();                        // 0x005c6620: return mbHidden
  bool CheckInfo(struct SwatchInfo* info);  // 0x005c65f0, ret 4
};
}
namespace SP {
class cSPPalettePage_s005c_7500 : public EA::RefCountVTemplate_s005c_7500<int>, public EA::COM::IUnknown32_s005c_7500 {
 public:
  cSPPalettePage_s005c_7500();
  virtual ~cSPPalettePage_s005c_7500();
  void Shutdown();  // 0x005c7ed0
  int GetItemIndex(int itemIndex);  // 0x005c7f00
  void ProcessPagePart(const EA::ResourceMan::Key_s005c_7500& pageName,
                       const EA::ResourceMan::Key_s005c_7500& moduleName,
                       uint32_t thumbnailGroupID);  // 0x005c7ff0

  uint32_t mLayoutInstanceID;  // +0xc
  int mField10;                // +0x10
  float mFloat14;              // +0x14
  float mFloat18;              // +0x18
  float mFloat1c;              // +0x1c
  float mFloat20;              // +0x20
  float mFloat24;              // +0x24
  float mFloat28;              // +0x28
  bool mBool2c;                // +0x2c
  bool mBool2d;                // +0x2d
  char pad2e[0x48 - 0x2e];
  bool mBool48;  // +0x48
  bool mBool49;  // +0x49
  bool mBool4a;  // +0x4a
  char pad4b;
  float mFloat4c;              // +0x4c
  int mnNumRows;               // +0x50
  int mnNumColumns;            // +0x54
  uint32_t mField58;           // +0x58
  int mField5c;                // +0x5c
  int mCategoryKey0;           // +0x60
  int mCategoryKey1;           // +0x64
  int mCategoryKey2;           // +0x68
  int mField6c;                // +0x6c
  eastl::sp_vector0<AutoRefCount_s005c_7500<cSPPaletteItem_s005c_7500> > mItems;  // +0x70
};
}
namespace SP {
class cSPPaletteCursor : public EA::RefCountVTemplate_s005c_7500<int>, public EA::COM::IUnknown32_s005c_7500 {
 public:
  cSPPaletteCursor();
  void SetPalette(cSPPalette_s005c_7500* palette);
  bool Advance();
  int Current(void* out1, int* out2, int* out3, int* out4);
  int Next(void* a, int* b, int* c, int* d);
  int Reset(void* a, int* b, int* c, int* d);

  AutoRefCount_s005c_7500<cSPPalette_s005c_7500> mPalette;  // +0xc
  int mCategoryIndex;                 // +0x10
  int mSubCategoryIndex;              // +0x14
  int mPageIndex;                     // +0x18
  int mItemIndex;                     // +0x1c
};
}
namespace SP {
struct SwatchInfo {
  bool Has(uint64_t key);  // 0x00595110, ret 8
};
}
// ---- items of slice s005c7500 end

// @ 0x005c7b80
namespace SP {
cSPPaletteCursor::cSPPaletteCursor()
: mPalette(0), mCategoryIndex(0), mSubCategoryIndex(0), mPageIndex(0), mItemIndex(0) {}
}  // namespace SP
