// src/game/SPEditors/SPEditorPaletteItem.cpp -- migrated from slice(s) s005c6340 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorPaletteItem.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Messaging/IHandler.h"
#include "EA/Messaging/IHandlerRC.h"
#include "EA/Messaging/Server.h"
#include "EA/ResourceMan/Key.h"
#include "EA/Variant.h"
#include "SP/cISPPaletteItemUI.h"
#include "SP/cPropertyList.h"
#include "SP/cSPPalette.h"
#include "SP/cSPPaletteItem.h"
#include "SP/cSPPaletteItemRollover.h"
#include "SP/cSPPaletteItemUI.h"
#include "SP/cSPPaletteItemUISelectable.h"
#include "cSPUIPropertyLayout.h"
#include <new>
#include "EA/AutoRefCount.h"

// ---- items of slice s005c6340 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
using EA::AutoRefCount_s005c_6340;
using EA::ResourceMan::Key_s005c_6340;
struct Property {
  char pad[0x12];
  unsigned short mType;  // +0x12
  int* GetInt();         // 0x0041e990
};
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
bool GetPropertyAsKey(cPropertyList_s005c_6340* list, uint32_t id, Key_s005c_6340* result);               // 0x006a1250
}
namespace SP {
bool GetBoolProperty(cPropertyList_s005c_6340* list, uint32_t id, bool* result);               // 0x00407190
}
namespace SP {
struct AppPropertiesData { char pad[0x118]; int mDebugBlock; };
}
namespace SP {
struct AppProperties { char pad[0x3c]; AppPropertiesData* mpData; };
}
namespace SP {
extern AppProperties* sAppProperties;  // 0x015fd918
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
// ---- items of slice s005c6340 end

// @ 0x005c6810
namespace SP {
bool cSPPaletteItem_s005c_6340::Init(const Key_s005c_6340& key, int index, uint32_t thumbnailGroup)
{
  mItemKey = key;
  mIndex = index;
  if (!mItemKey.mType)
    mItemKey.mType = 0xb1b104;
  mThumbnailKey = mItemKey;
  if (thumbnailGroup)
    mThumbnailKey.mGroup = thumbnailGroup;
  mThumbnailKey.mType = 0x2f7d0004;
  switch (mItemKey.mType) {
    case 0xb1b104: {
      if (sAppProperties->mpData->mDebugBlock && index < 0) {
        mItemType = kBlock;
        return true;
      }
      AutoRefCount_s005c_6340<cPropertyList_s005c_6340> list;
      if (PropertyManager()->GetPropertyList(mItemKey.mInstance, mItemKey.mGroup, list.AsPPTypeParam())) {
        if (!list)
          break;
        GetPropertyAsKeyInstance(list, 0x2196ad5, (uint32_t*)&mItemType);
        mPriority = 0;
        GetPropertyAsKeyInstance(list, 0x65f9e78, (uint32_t*)&mPriority);
        GetPropertyAsKey(list, 0x65f9e79, &mSwatchKey);
        mSwatchKey.mType = 0x510a95b;
        mSwatchKey.mGroup = 0x40464100;
        mSwatchColor = 0;
        GetPropertyAsKeyInstance(list, 0x65f9e7a, &mSwatchColor);
        GetPropertyAsKey(list, 0x65f9e7b, &mSwatchKey2);
        mSwatchKey2.mType = 0x510a95b;
        mSwatchKey2.mGroup = 0x40464100;
        mbHidden = false;
        GetBoolProperty(list, 0x6626a29, &mbHidden);
      }
      break;
    }
    case 0x2f7d0004:
      mItemType = kSwatch;
      mThumbnailKey = mItemKey;
      break;
    case 0x24682294:
    case 0x2399be55:
    case 0x2b978c46:
    case 0x476a98c7:
    case 0x3d97a8e4:
    case 0x438f6347:
    case 0xffffffff:
      mItemType = kBakedModel;
      break;
  }
  return mItemType != kItemTypeUnknown ? true : false;
}
}  // namespace SP
