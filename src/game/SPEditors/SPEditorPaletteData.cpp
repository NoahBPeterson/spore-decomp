// src/game/SPEditors/SPEditorPaletteData.cpp -- migrated from slice(s) s005c6340, s005c53c0 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorPaletteData.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPPalette.h"
#include "SP/cSPPaletteCategoryUI.h"
#include "EA/Messaging/AutoHandler.h"
#include "EA/Messaging/Server.h"
#include "EA/ResourceMan/Key.h"
#include "SP/cSPEditorColorPicker.h"
#include "SP/cSPEditorPageControls.h"
#include "SP/cSPEditorPaintLikeThis.h"
#include "SP/cSPPaletteCategory.h"
#include "SP/cSPPaletteItem.h"
#include "SP/cSPPalettePage.h"
#include "SP/cSPPaletteSubCategoryUI.h"
#include "SP/cSPSwatch.h"
#include "cSPUILayout.h"
#include "EA/Messaging/IHandler.h"
#include "EA/Messaging/IHandlerRC.h"
#include "EA/Variant.h"
#include "SP/cISPPaletteItemUI.h"
#include "SP/cPropertyList.h"
#include "SP/cSPPaletteItemRollover.h"
#include "SP/cSPPaletteItemUI.h"
#include "SP/cSPPaletteItemUISelectable.h"
#include "cSPUIPropertyLayout.h"
#include <new>

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
extern "C" void EASTL_allocator_deallocate(void* p);                       // 0x00f47380
#define PV(n) virtual void pv##n();
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
struct Key_s005c_6340 {
  unsigned int mInstance, mType, mGroup;
};
}
}
namespace EA {
namespace ResourceMan {
class IResourceFilter {
 public:
  virtual ~IResourceFilter() {}
  virtual bool IsValid(const Key_s005c_6340& key);
};
}
}
namespace EA {
namespace ResourceMan {
class StandardFileFilter : public IResourceFilter {
 public:
  StandardFileFilter(uint32_t instanceID, uint32_t groupID, uint32_t typeID, uint32_t subtypeID)
      : mInstanceID(instanceID), mGroupID(groupID), mTypeID(typeID), mSubtypeID(subtypeID) {}
  virtual bool IsValid(const Key_s005c_6340& key);
  uint32_t mInstanceID;
  uint32_t mGroupID;
  uint32_t mTypeID;
  uint32_t mSubtypeID;
};
}
}
using EA::AutoRefCount_s005c_6340;
using EA::ResourceMan::Key_s005c_6340;
namespace eastl {
template <typename T, int kAllocatorWords = 2>
class sp_vector {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  int mAllocator[kAllocatorWords];
  sp_vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~sp_vector() {
    if (mpBegin && ((int*)mpBegin)[-1] != 0)
      EASTL_allocator_deallocate(mpBegin);
  }
  T* begin() { return mpBegin; }
  T* end() { return mpEnd; }
};  // namespace eastl
}
struct Property {
  char pad[0x12];
  unsigned short mType;  // +0x12
  int* GetInt();         // 0x0041e990
};
namespace EA {
namespace ResourceMan {
class IResourceManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
  virtual int GetResourceKeyList(eastl::sp_vector<Key_s005c_6340>* keys, IResourceFilter* filter, int flags);  // +0x38
};
}
}
EA::ResourceMan::IResourceManager* ResourceManager();  // 0x008de1a0
namespace SP {
class cPropertyList_s005c_6340 {
 public:
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
  virtual bool GetProperty(uint32_t id, Property*& result);  // +0x24
};
}
namespace SP {
class IPropertyManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, cPropertyList_s005c_6340** result);  // +0x2c
};
}
namespace SP {
IPropertyManager* PropertyManager();                                                // 0x0067de30
}
namespace SP {
bool GetPropertyAsKeyInstance(cPropertyList_s005c_6340* list, uint32_t id, uint32_t* result);  // 0x006a12a0
}
namespace SP {
bool GetPropertyAsKeyGroup(cPropertyList_s005c_6340* list, uint32_t id, uint32_t* result);     // 0x006a12e0
}
namespace SP {
enum eModelType_s005c_6340 {};
}
namespace SP {
class cSPPaletteCategory_s005c_6340;
}
namespace SP {
class cSPPalette_s005c_6340 : public EA::RefCountVTemplate_s005c_6340<int>, public EA::COM::IUnknown32_s005c_6340 {
 public:
  eastl::sp_vector<AutoRefCount_s005c_6340<cSPPaletteCategory_s005c_6340>, 1> mCategories;  // +0xc
  unsigned int mLayoutInstanceID;     // +0x1c
  unsigned int mImageGroupID;         // +0x20
  unsigned int mOptionalImageGroupID; // +0x24
  int mStartupCategory;               // +0x28
  eModelType_s005c_6340 mModelType;              // +0x2c
  unsigned int mPaletteGroupID;       // +0x30
  unsigned int mParam34;              // +0x34
  int mThemeIndex;                    // +0x38
  unsigned int mParam3c;              // +0x3c

  virtual int AddRef();
  virtual int Release();
  bool Init(const Key_s005c_6340& key, unsigned int param3c, unsigned int param34, unsigned int imageGroupID,
            unsigned int optionalImageGroupID, int startupCategory, eModelType_s005c_6340 modelType);
  void LoadDefinitionPart(const Key_s005c_6340& key);  // 0x005c6010
};
}
namespace SP {
inline bool GetIntProperty(cPropertyList_s005c_6340* list, uint32_t id, int& value) {
  Property* prop;
  if (list->GetProperty(id, prop) && prop->mType == 9) {
    value = *prop->GetInt();
    return true;
  }
  return false;
}
}
// ---- items of slice s005c6340 end

// @ 0x005c5e90
namespace SP {
cSPPalette_s005c_53c0::~cSPPalette_s005c_53c0()
{
  ShutdownChildren();
}
}  // namespace SP

// @ 0x005c5f00
namespace SP {
void cSPPalette_s005c_53c0::AddCategory(cSPPaletteCategory_s005c_53c0* cat)
{
  if (!cat)
    return;
  uint32_t key = cat->mSortKey;
  cSPPaletteCategory_s005c_53c0** end = mCats.mEnd;
  for (cSPPaletteCategory_s005c_53c0** it = mCats.mBegin; it != end; ++it) {
    cSPPaletteCategory_s005c_53c0* cur = *it;
    if (cur)
      cur->AddRef();
    if (cur->mSortKey > key) {
      cSPPaletteCategory_s005c_53c0* tmp = cat;
      cat->AddRef();
      CatVector* v = &mCats;
      if (it == v->mEnd && v->mEnd != v->mCap) {
        cSPPaletteCategory_s005c_53c0** slot = v->mEnd++;
        if (slot) {
          *slot = cat;
          cat->AddRef();
        }
      } else {
        v->InsertAux(it, &tmp);
      }
      if (tmp)
        tmp->Release();
      cur->Release();
      return;
    }
    cur->Release();
  }
  CatVector* v = &mCats;
  cSPPaletteCategory_s005c_53c0* tmp = cat;
  cat->AddRef();
  if (v->mEnd < v->mCap) {
    cSPPaletteCategory_s005c_53c0** slot = v->mEnd++;
    if (slot) {
      *slot = cat;
      cat->AddRef();
    }
  } else {
    v->InsertAux(v->mEnd, &tmp);
    cat = tmp;
  }
  if (cat)
    cat->Release();
}
}  // namespace SP

// @ 0x005c6340
namespace SP {
bool cSPPalette_s005c_6340::Init(const Key_s005c_6340& key, unsigned int param3c, unsigned int param34, unsigned int imageGroupID, unsigned int optionalImageGroupID, int startupCategory, eModelType_s005c_6340 modelType)
{
  mParam3c = param3c;
  AutoRefCount_s005c_6340<cPropertyList_s005c_6340> list;
  IPropertyManager* pm = PropertyManager();
  pm->GetPropertyList(key.mInstance, key.mGroup, &list.AsOutParam());
  if (list) {
    GetIntProperty(list, 0x332b28b, mThemeIndex);
    GetPropertyAsKeyGroup(list, 0x2233661, &mPaletteGroupID);
    mParam34 = param34;
    if (imageGroupID)
      mImageGroupID = imageGroupID;
    else
      GetPropertyAsKeyInstance(list, 0xc46ec042, &mImageGroupID);
    mOptionalImageGroupID = optionalImageGroupID;
    mStartupCategory = startupCategory;
    mModelType = modelType;
    EA::ResourceMan::IResourceManager* rm = ResourceManager();
    eastl::sp_vector<Key_s005c_6340> keys;
    EA::ResourceMan::StandardFileFilter filter(0xffffffff, (uint8_t)key.mInstance | 0x406b6b00, 0xb1b104,
                                               0xffffffff);
    rm->GetResourceKeyList(&keys, &filter, 0);
    Key_s005c_6340* const end = keys.end();
    for (Key_s005c_6340* it = keys.begin(); it != end; ++it) {
      Key_s005c_6340 partKey = *it;
      LoadDefinitionPart(partKey);
    }
    return true;
  }
  return false;
}
}  // namespace SP
