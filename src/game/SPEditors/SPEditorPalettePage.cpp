// src/game/SPEditors/SPEditorPalettePage.cpp -- migrated from slice(s) s005c85d0, s005c7500 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorPalettePage.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPPalettePage.h"
#include "EA/ResourceMan/Key.h"
#include "SP/cSPOLDPaletteItemUI.h"
#include "SP/cSPPalette.h"
#include "SP/cSPPaletteCategory.h"
#include "SP/cSPPaletteItem.h"
#include "SP/cSPSwatch.h"
#include "cSPUILayout.h"
#include "cSPUITooltipWinProc.h"
#include "SP/cString.h"
#include <new>
#include "EA/UTFWin/IWindow.h"
#include "SP/cSPPalettePageUI.h"
#include "SP/cPropertyList.h"
#include "EA/AutoRefCount.h"

// ---- items of slice s005c7500 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char* g_pEditor;  // 0x015fd918
void* operator new(unsigned int n, const char* name, int flags, unsigned int debugFlags,
                   const char* file, int line);
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
namespace eastl {
extern wchar_t gEmptyWString;  // 0x01667bac
}
namespace eastl {
class wstring {
 public:
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  wstring()
      : mpBegin(&gEmptyWString), mpEnd(&gEmptyWString), mpCapacity(&gEmptyWString + 1) {}
  ~wstring() { DeallocateSelf(); }
  void DeallocateSelf();  // 0x00933960
};
}
namespace EA {
template <class T>
const T& min(const T& a, const T& b) {
  return b < a ? b : a;
}
}
namespace EA {
namespace ResourceMan {
class IManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
  PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23)
  PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
  virtual void GetKeyName(const Key_s005c_7500& key, eastl::wstring* out);  // +0x7c
};
}
}
namespace EA {
namespace ResourceMan {
IManager* GetManager();  // 0x0067dcd0
}
}
class cPropertyList_s005c_7500 {
 public:
  virtual int AddRef();
  virtual int Release();
};
class IPropertyManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual void GetPropertyList(uint32_t instance, uint32_t group, cPropertyList_s005c_7500*& out);  // +0x2c
};
IPropertyManager* PropertyManager();  // 0x0067de30
bool GetPropertyAsKeyInstance(void* list, uint32_t id, uint32_t* out);              // 0x006a12a0
bool GetPropertyAsKeyArray(void* list, uint32_t id, uint32_t* count, void** data);  // 0x006a0ae0
bool GetPropertyAsIntArray(void* list, uint32_t id, uint32_t* count, void** data);  // 0x006a07d0
bool GetPropertyAsInt(void* list, uint32_t id, int* out);                           // 0x00410370
using EA::AutoRefCount_s005c_7500;
namespace SP {
class cSPPalettePage_s005c_7500;
}
namespace SP {
class cSPPaletteItem_s005c_7500;
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
extern float g_one;  // 0x01485720
}
namespace SP {
struct SwatchInfo {
  bool Has(uint64_t key);  // 0x00595110, ret 8
};
}
// ---- items of slice s005c7500 end

// ---- items of slice s005c85d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
class cSPPalettePage {
 public:
  bool CommonInit(int a, int b);
  bool Init(int a, int b, int c, int d, float e);
  void ProcessPagePart(int a, void* b, int c);
};
// ---- items of slice s005c85d0 end

// @ 0x005c7f50
namespace SP {
cSPPalettePage_s005c_7500::cSPPalettePage_s005c_7500()
: mLayoutInstanceID(0xd8006607),
      mField10(0),
      mFloat14(0.0f),
      mFloat18(0.0f),
      mFloat1c(0.0f),
      mFloat20(0.0f),
      mFloat24(0.0f),
      mFloat28(0.0f),
      mBool2c(false),
      mBool2d(false),
      mBool48(false),
      mBool49(false),
      mBool4a(false),
      mFloat4c(g_one),
      mnNumRows(0),
      mnNumColumns(0),
      mField58(0),
      mField5c(0),
      mCategoryKey0(-1),
      mCategoryKey1(0),
      mCategoryKey2(0),
      mField6c(0) {}
}  // namespace SP

// @ 0x005c7ff0
namespace SP {
void cSPPalettePage_s005c_7500::ProcessPagePart(const EA::ResourceMan::Key_s005c_7500& pageName, const EA::ResourceMan::Key_s005c_7500& moduleName, uint32_t thumbnailGroupID)
{
  AutoRefCount_s005c_7500<cPropertyList_s005c_7500> propList;
  PropertyManager()->GetPropertyList(moduleName.mInstance, moduleName.mGroup,
                                     propList.AsOutParam());
  if (propList.mpObject == 0)
    return;

  uint32_t keyInst;
  if (!GetPropertyAsKeyInstance(propList.mpObject, 0x1f7d3cf3, &keyInst)) {
    eastl::wstring name;
    EA::ResourceMan::GetManager()->GetKeyName(moduleName, &name);
  }
  if (keyInst != pageName.mInstance)
    return;

  uint32_t keyCount = 0;
  uint32_t rowCount = 0;
  uint32_t colCount = 0;
  void* keyData = 0;
  void* rowData = 0;
  void* colData = 0;
  int propInt = 0;

  GetPropertyAsKeyArray(propList.mpObject, 0xeeead734, &keyCount, &keyData);
  GetPropertyAsIntArray(propList.mpObject, 0xf8e99c4f, &rowCount, &rowData);
  GetPropertyAsIntArray(propList.mpObject, 0x22c47931, &colCount, &colData);
  if (*(int*)(*(char**)(g_pEditor + 0x3c) + 0x118) != 0)
    GetPropertyAsInt(propList.mpObject, 0x5383435, &propInt);

  if (keyCount != rowCount) {
    eastl::wstring name;
    EA::ResourceMan::GetManager()->GetKeyName(moduleName, &name);
    keyCount = EA::min(keyCount, rowCount);
  }
  if (keyCount != colCount) {
    eastl::wstring name;
    EA::ResourceMan::GetManager()->GetKeyName(moduleName, &name);
    keyCount = EA::min(keyCount, colCount);
  }

  for (int i = 0; i < (int)keyCount; i++) {
    int row = ((int*)rowData)[i];
    int col = ((int*)colData)[i];
    if (row < 0 || row >= mnNumRows) {
      eastl::wstring name;
      EA::ResourceMan::GetManager()->GetKeyName(moduleName, &name);
      continue;
    }
    if (col < 0 || col >= mnNumColumns) {
      eastl::wstring name;
      EA::ResourceMan::GetManager()->GetKeyName(moduleName, &name);
      continue;
    }
    int index = mnNumRows * col + row;
    cSPPaletteItem_s005c_7500* oldItem = mItems.mpBegin[index].mpObject;
    if (oldItem != 0) {
      oldItem->AddRef();
      if (oldItem->mIndex >= propInt) {
        if (oldItem->mIndex == propInt) {
          eastl::wstring name;
          EA::ResourceMan::GetManager()->GetKeyName(moduleName, &name);
        }
        oldItem->Release();
        continue;
      }
    }
    {
      AutoRefCount_s005c_7500<cSPPaletteItem_s005c_7500> item(new ("Editor", 0, 0, 0, 0) cSPPaletteItem_s005c_7500());
      if (item.mpObject != 0) {
        if (item->Init(((const EA::ResourceMan::Key_s005c_7500*)keyData)[i], propInt,
                       thumbnailGroupID))
          mItems.mpBegin[index] = item;
        else {
          eastl::wstring name;
          EA::ResourceMan::GetManager()->GetKeyName(moduleName, &name);
        }
      }
    }
    if (oldItem != 0)
      oldItem->Release();
  }
}
}  // namespace SP

// @ 0x005c85d0
bool cSPPalettePage::CommonInit(int a, int b)
{
  (void)a;
  (void)b;
  return false;
}

// @ 0x005c8ad0
bool cSPPalettePage::Init(int a, int b, int c, int d, float e)
{
  (void)a;
  (void)b;
  (void)c;
  (void)d;
  (void)e;
  return false;
}
