// Creature editor: cSPEditorManipulationTranslateCreature::DoOnMouseDown, an editor rollover cursor
// attachment, editor property-list helpers (collectables, functional-match params), cSpeciesSummarizer,
// and SP::cSPEditorNaming.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include <new>
#include <float.h>
#include <string.h>
#include "types.h"

void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380

#define PV(n) virtual void pv##n();

namespace rw { namespace math { namespace fpu {
template <typename T, int N>
class Vector3Template {
 public:
  T x, y, z;
  Vector3Template() {}
  Vector3Template(T ax, T ay, T az) : x(ax), y(ay), z(az) {}
};
template <typename T, int N>
inline Vector3Template<T, N> operator+(const Vector3Template<T, N>& a, const Vector3Template<T, N>& b) {
  return Vector3Template<T, N>(a.x + b.x, a.y + b.y, a.z + b.z);
}
template <typename T, int N>
inline Vector3Template<T, N> operator-(const Vector3Template<T, N>& a, const Vector3Template<T, N>& b) {
  return Vector3Template<T, N>(a.x - b.x, a.y - b.y, a.z - b.z);
}
template <typename T, int N>
inline Vector3Template<T, N> operator*(const Vector3Template<T, N>& a, T s) {
  return Vector3Template<T, N>(a.x * s, a.y * s, a.z * s);
}
template <typename T, int N>
inline T Dot(const Vector3Template<T, N>& a, const Vector3Template<T, N>& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}
}}}  // namespace rw::math::fpu

struct cSPVector3 : public rw::math::fpu::Vector3Template<float, 0> {
  typedef rw::math::fpu::Vector3Template<float, 0> base;
  cSPVector3() {}
  cSPVector3(float ax, float ay, float az) : base(ax, ay, az) {}
  cSPVector3(const cSPVector3& v) { x = v.x; y = v.y; z = v.z; }
  cSPVector3(const base& v) { x = v.x; y = v.y; z = v.z; }
  cSPVector3& operator=(const base& v) { x = v.x; y = v.y; z = v.z; return *this; }
  float Dot(const cSPVector3& o) const { return x * o.x + y * o.y + z * o.z; }
};


struct cSPMatrix3 { float m[9]; };

struct cSPBoundingBox {
  cSPVector3 mMin;  // +0x0
  cSPVector3 mMax;  // +0xc
  cSPBoundingBox(const cSPVector3& mn, const cSPVector3& mx) { mMin = mn; mMax = mx; }
};

namespace EA {
template <typename T>
class AutoRefCount {
 public:
  T* mpObject;
  AutoRefCount() : mpObject(0) {}
  AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount() { if (mpObject) mpObject->Release(); }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
  T*& AsOutParam() {
    if (mpObject) {
      T* const p = mpObject;
      mpObject = 0;
      p->Release();
    }
    return mpObject;
  }
};

template <typename T>
class RefCountVTemplate {
 public:
  virtual ~RefCountVTemplate() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};

// EA::Variant (size 0x14)
struct Variant {
  uint32_t mData[4];
  unsigned short mFlags;   // +0x10
  unsigned short mTypeId;  // +0x12
  Variant() : mFlags(0), mTypeId(0) {}
  ~Variant() {
    if (mFlags & 4)
      Destruct(0);
  }
  void Destruct(int);                                       // EA::Variant::Destruct
  Variant& operator=(const int& v);                         // Variant_SetU32 (0x00422eb0)
  void SetResourceKey(int a, int b, uint32_t v, int c, int d);  // FUN_0093dd80
};

namespace ResourceMan {
class Key {
 public:
  unsigned int mInstance;  // +0x0
  unsigned int mType;      // +0x4
  unsigned int mGroup;     // +0x8
};
class IResourceManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11)
  virtual class IRecord* GetDatabaseFor(const Key& key, int a, int b);  // +0x30 (name guessed)
};
IResourceManager* GetManager();
class IDatabase {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
  virtual uint32_t GetAccessFlags();  // +0x20 (name guessed)
};
}  // namespace ResourceMan
}  // namespace EA

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
  int size() const { return (int)(mpEnd - mpBegin); }
  T& operator[](int i) { return mpBegin[i]; }
  T* DoInsertValue(T* position, const T& value);
  void push_back(const T& value) {
    if (mpEnd < mpCapacity)
      ::new (mpEnd++) T(value);
    else
      DoInsertValue(mpEnd, value);
  }
};
}  // namespace eastl

// ---------------------------------------------------------------- property lists
struct Property {
  union {
    bool mBool;
    int mInt32;
  };
  char pad04[0x12 - 4];
  unsigned short mType;  // +0x12
  int* GetInt();         // Property::GetInt (0x0041e990)
};

namespace App {
class PropertyList {
 public:
  virtual void AddRef();
  virtual void Release();
  PV(2) PV(3) PV(4)
  virtual void SetProperty(uint32_t id, const EA::Variant& value);   // +0x14
  virtual void RemoveProperty(uint32_t id);                         // +0x18
  PV(7) PV(8)
  virtual bool GetProperty(uint32_t id, Property*& result);         // +0x24
  virtual Property* GetPropertyObject(uint32_t id);                 // +0x28
  PV(11) PV(12)
  virtual void SetParent(PropertyList* parent);                     // +0x34
  PV(14) PV(15)
  PV(16)
  virtual void GetPropertyIDs(eastl::sp_vector<uint32_t>& out);     // +0x44
};
class IPropertyManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual bool HasPropertyList(uint32_t instanceID, uint32_t groupID);                         // +0x28
  virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyList*& result);  // +0x2c
};
}  // namespace App

namespace Editor {
class cPropertyList : public App::PropertyList {
 public:
  cPropertyList();
  char pad[0x38 - 4];
  void AddRef();
};
}

namespace SP {
App::IPropertyManager* PropertyManager();
bool GetPropertyAsKey(App::PropertyList* list, uint32_t id, EA::ResourceMan::Key* key);
bool GetPropertyKeys(App::PropertyList* list, uint32_t id, int* count, EA::ResourceMan::Key** keys);  // 0x006a0ae0
void SetPropertyKeys(App::PropertyList* list, uint32_t id, int count, EA::ResourceMan::Key* keys);    // 0x006a0ee0
bool HasProperty(App::PropertyList* list, uint32_t id, uint32_t value);                               // 0x006a1400
EA::ResourceMan::IDatabase* GetSaveArea(uint32_t id);
bool SaveResource(App::PropertyList* list, EA::ResourceMan::IDatabase* db, int flags);
class IObjectTemplateDB {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
  PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27)
  virtual void AddTemplate(const EA::ResourceMan::Key& key);        // +0x70
  virtual void InvalidateTemplate(const EA::ResourceMan::Key& key, int b);  // +0x74
};
IObjectTemplateDB* ObjectTemplateDB();

namespace FunctionalMatch {
enum eType { kTypeBool = 0 };
struct DeclareParam {
  unsigned int mParameter;  // +0x0
  eType mType;              // +0x4
  int mIntVal;              // +0x8
  DeclareParam(unsigned int parameter, bool value);
};
}
}  // namespace SP

static inline uint32_t PropListGroup(uint32_t group) { return (group & 0xffffe5ff) | 0xe500; }

// @ 0x005BF0A0
int HasEditorPropertyList(const EA::ResourceMan::Key& key) {
  App::IPropertyManager* pm = SP::PropertyManager();
  if (pm && pm->HasPropertyList(key.mInstance, PropListGroup(key.mGroup)))
    return 1;
  return 0;
}

// @ 0x005BF0E0
int GetEditorPropertyList(const EA::ResourceMan::Key& key, App::PropertyList*& result) {
  App::IPropertyManager* pm = SP::PropertyManager();
  if (pm && pm->GetPropertyList(key.mInstance, PropListGroup(key.mGroup), result))
    return 1;
  return 0;
}

// @ 0x005BF120
bool SaveEditorPropertyList(const EA::ResourceMan::Key& key, App::PropertyList* list, int flags, EA::ResourceMan::IDatabase* db) {
  uint32_t instance = key.mInstance;
  uint32_t group = PropListGroup(key.mGroup);
  if (!db)
    db = (EA::ResourceMan::IDatabase*)EA::ResourceMan::GetManager()->GetDatabaseFor(key, 0, 0);
  if (!db || !(db->GetAccessFlags() & 2))
    db = SP::GetSaveArea(0x11ac19c);
  if (db && list) {
    ((uint32_t*)list)[2] = instance;
    ((uint32_t*)list)[3] = 0xb1b104;
    ((uint32_t*)list)[4] = group;
    bool ok = SP::SaveResource(list, db, flags);
    if (ok) {
      SP::ObjectTemplateDB()->InvalidateTemplate(key, 0);
      SP::ObjectTemplateDB()->AddTemplate(key);
    }
    return ok;
  }
  return false;
}

struct ListNode {
  ListNode* mpNext;
  ListNode* mpPrev;
  uint32_t mGroup;
  uint32_t mInstance;
};

namespace Simulator {
class cCollectableItems {
 public:
  cCollectableItems();
  virtual void AddRef();
  virtual void Release();
  bool Load(uint32_t instance, uint32_t group, int flags);    // FUN_00599440
  struct ListNode* GetItemList();                              // FUN_005939a0
  bool IsRare(uint32_t group, uint32_t instance);             // FUN_00595190
  void AddItem(uint64_t item, int flags);                     // FUN_00596da0
  void FinishedLoading();                                     // FUN_005942e0
  char pad[0x6dac - 4];
};
uint64_t MakeItemID(uint32_t group, uint32_t instance);       // FUN_00593980
}

// @ 0x005BF1E0
bool LoadCollectableItems(App::PropertyList* list, Simulator::cCollectableItems** result) {
  bool ok = false;
  EA::ResourceMan::Key key;
  key.mInstance = 0;
  key.mType = 0;
  key.mGroup = 0;
  if (SP::GetPropertyAsKey(list, 0xc339d5c7, &key)) {
    EA::AutoRefCount<Simulator::cCollectableItems> items(new ("Editor/cCollectableItems", 0, 0, 0, 0) Simulator::cCollectableItems());
    if (items->Load(key.mGroup, key.mInstance, 0)) {
      EA::ResourceMan::Key* unlocked;
      EA::ResourceMan::Key* rare;
      int numUnlocked = 0;
      SP::GetPropertyKeys(list, 0xbeac70b6, &numUnlocked, &unlocked);
      int numRare = 0;
      SP::GetPropertyKeys(list, 0xc285e3db, &numRare, &rare);
      for (int i = 0; i < numUnlocked; i++)
      {
        uint64_t id = Simulator::MakeItemID(unlocked[i].mGroup, unlocked[i].mInstance);
        items->AddItem(id, 0);
      }
      items->FinishedLoading();
      for (int i = 0; i < numRare; i++)
      {
        uint64_t id = Simulator::MakeItemID(rare[i].mGroup, rare[i].mInstance);
        items->AddItem(id, 0);
      }
      *result = items;
      ok = true;
      items->AddRef();
    }
  }
  return ok;
}

// @ 0x005BF3A0
bool CopyEditorPropertyList(const EA::ResourceMan::Key& dst, const EA::ResourceMan::Key& src, App::PropertyList** result,
                            EA::ResourceMan::IDatabase* db) {
  bool ok = false;
  App::IPropertyManager* pm = SP::PropertyManager();
  EA::AutoRefCount<App::PropertyList> srcList;
  if (pm) {
    if (pm->GetPropertyList(src.mInstance, src.mGroup, srcList.mpObject)) {
      EA::AutoRefCount<Editor::cPropertyList> list(new ("Editor/cPropertyList", 0, 0, 0, 0) Editor::cPropertyList());
      list->SetParent(srcList);
      ok = SaveEditorPropertyList(dst, list, 0, db);
      if (ok && result) {
        *result = list;
        list->AddRef();
      }
    }
  }
  return ok;
}

// @ 0x005BF470
int AddToIntProperty(App::PropertyList* list, uint32_t id, int delta) {
  int value = 0;
  Property* prop;
  if (list && list->GetProperty(id, prop) && prop->mType == 9)
    value = *prop->GetInt();
  value += delta;
  EA::Variant v;
  v = value;
  list->SetProperty(id, v);
  return value;
}

// @ 0x005BF500
bool __stdcall GetBoolParams(const EA::ResourceMan::Key& key, eastl::sp_vector<SP::FunctionalMatch::DeclareParam>& params) {
  EA::AutoRefCount<App::PropertyList> list;
  App::IPropertyManager* pm = SP::PropertyManager();
  if (pm->GetPropertyList(key.mInstance, PropListGroup(key.mGroup), list.AsOutParam())) {
    eastl::sp_vector<uint32_t> ids;
    list->GetPropertyIDs(ids);
    int count = ids.size();
    for (int i = 0; i < count; i++) {
      uint32_t id = ids[i];
      Property* prop = list->GetPropertyObject(id);
      if (prop->mType == 1)
        params.push_back(SP::FunctionalMatch::DeclareParam(id, prop->mBool != 0));
    }
  }
  return true;
}

void GetItemKey(uint32_t group, uint32_t instance, uint32_t* outGroup, uint32_t* outInstance);  // FUN_00593960

// @ 0x005BF610
void SaveCollectableItems(App::PropertyList* list, Simulator::cCollectableItems* items) {
  EA::ResourceMan::Key key;
  key.mInstance = 0;
  key.mType = 0;
  key.mGroup = 0;
  if (SP::GetPropertyAsKey(list, 0xc339d5c7, &key)) {
    eastl::sp_vector<EA::ResourceMan::Key> unlocked;
    eastl::sp_vector<EA::ResourceMan::Key> rare;
    ListNode* head = items->GetItemList();
    for (ListNode* n = head->mpNext; n != head; n = n->mpNext) {
      uint32_t group = n->mGroup;
      uint32_t instance = n->mInstance;
      EA::ResourceMan::Key itemKey;
      itemKey.mInstance = 0;
      itemKey.mType = 0;
      itemKey.mGroup = 0;
      GetItemKey(group, instance, &itemKey.mGroup, &itemKey.mInstance);
      itemKey.mType = 0xb1b104;
      if (items->IsRare(group, instance))
        rare.push_back(itemKey);
      else
        unlocked.push_back(itemKey);
    }
    SP::SetPropertyKeys(list, 0xbeac70b6, unlocked.size(), unlocked.mpBegin);
    SP::SetPropertyKeys(list, 0xc285e3db, rare.size(), rare.mpBegin);
  }
}

// @ 0x005BF7C0
bool ConvertKeyProperty(App::PropertyList* list, uint32_t value) {
  bool result = false;
  if (!SP::HasProperty(list, 0x75ed3a1c, value)) {
    if (SP::HasProperty(list, 0x1cb70998, value)) {
      {
        EA::Variant v;
        v.SetResourceKey(0x13, 9, value, 0x10, 1);
        list->SetProperty(0x75ed3a1c, v);
      }
      list->RemoveProperty(0x1cb70998);
      result = true;
    }
  } else {
    result = true;
  }
  return result;
}

// @ 0x005BF860
void SetKeyProperty(App::PropertyList* list, uint32_t value) {
  EA::Variant v;
  v.SetResourceKey(0x13, 9, value, 0x10, 1);
  list->SetProperty(0x75ed3a1c, v);
}

bool IsReservedID(unsigned short id);  // FUN_004f56f0
struct cResourceFilter {
  // @ 0x005BF8C0
  bool IsValid(const EA::ResourceMan::Key& unused, const EA::ResourceMan::Key* key);
};
bool cResourceFilter::IsValid(const EA::ResourceMan::Key& unused, const EA::ResourceMan::Key* key) {
  if (key->mGroup == 5 && !IsReservedID(*(unsigned short*)((char*)key + 0x10)))
    return true;
  return false;
}

namespace SP {
class cSpeciesSummarizer {
 public:
  virtual uint32_t GetResType(int index);
};
// @ 0x005BF080
uint32_t cSpeciesSummarizer::GetResType(int index) {
  return index != 0 ? 0xffffffff : 0x2b978c46;
}
}  // namespace SP

// ---------------------------------------------------------------- creature translate manipulator
namespace SP {
class cSPEditorBlock {
 public:
  virtual void v0();
  virtual void AddRef();
  virtual void Release();
  char pad04[0x48 - 4];
  cSPVector3 mPosition;                 // +0x48
  cSPVector3 mHistoryPosition;          // +0x54
  cSPMatrix3 mOrientation;              // +0x60
  cSPMatrix3 mHistoryOrientation;       // +0x84
  cSPMatrix3 mBaseOrientation;          // +0xa8
  cSPMatrix3 mHistoryBaseOrientation;   // +0xcc
};

class cSPEditorModel {
 public:
  void SetUsingSymmetry(bool b);         // FUN_004adc20
  bool IsUsingSymmetry();                // FUN_004adc40
  int GetNumBlocks();                    // FUN_004accf0
  cSPEditorBlock* GetBlock(int index);   // FUN_004accb0
};

class cSPEditorSpine {
 public:
  void Rebuild(bool a, bool b);  // FUN_005d1600
};

class cSPEditorLimbStructure {
 public:
  cSPEditorLimbStructure();                                   // FUN_00488850
  void Init(cSPEditorBlock* limbRoot, int a, int b);          // FUN_004891a0
  char pad[0x54];
};

namespace EditorUtils {
void GetAllLimbs(cSPEditorBlock* root, eastl::sp_vector<cSPEditorBlock*>& limbs, int flags);
}

class BlockPositionMap {
 public:
  cSPVector3& operator[](cSPEditorBlock* const& key);  // FUN_005bded0
  char pad[0x1c];
};

class cSPEditorManipulationObject {
 public:
  virtual ~cSPEditorManipulationObject() {}
  bool mChangedObject;         // +0x4
  bool mUseDeadZone;           // +0x5
  bool mMovedOutsideDeadZone;  // +0x6
  float mDeadZoneSize;         // +0x8
  float mInitialX;             // +0xc
  float mInitialY;             // +0x10
};

class cSPEditorManipulationTranslateCreature : public cSPEditorManipulationObject, public EA::RefCountVTemplate<int> {
 public:
  cSPEditorModel* mModel;                                  // +0x1c (AutoRefCount)
  cSPEditorSpine* mSpine;                                  // +0x20 (AutoRefCount)
  eastl::sp_vector<cSPEditorLimbStructure*> mLimbs;        // +0x24
  bool mModelUsingSymmetry;                                // +0x38
  cSPVector3 mOriginalPlanarPosition;                      // +0x3c
  BlockPositionMap mOriginalPositions;                     // +0x48
  cSPBoundingBox mCurrModelBounds;                         // +0x64

  cSPVector3 PickPlaneOfSymmetry(float x, float y, bool b);
  void CalcBoundsForMovement(const cSPVector3& delta, cSPBoundingBox& bounds, cSPBoundingBox& limits, bool b);  // FUN_005bdf70
  bool DoOnMouseDown(int button, float x, float y, int modifiers);
};

// @ 0x005BEAF0
bool cSPEditorManipulationTranslateCreature::DoOnMouseDown(int button, float x, float y, int modifiers) {
  if (mModel) {
    mModelUsingSymmetry = mModel->IsUsingSymmetry();
    mModel->SetUsingSymmetry(false);
    int numBlocks = mModel->GetNumBlocks();
    for (int i = 0; i < numBlocks; i++) {
      EA::AutoRefCount<cSPEditorBlock> block(mModel->GetBlock(i));
      block->mHistoryPosition = block->mPosition;
      block->mHistoryOrientation = block->mOrientation;
      block->mHistoryBaseOrientation = block->mBaseOrientation;
      cSPEditorBlock* key = block;
      mOriginalPositions[key] = block->mPosition;
    }
    if (numBlocks > 0) {
      eastl::sp_vector<cSPEditorBlock*> limbs;
      EditorUtils::GetAllLimbs(mModel->GetBlock(0), limbs, 0);
      int numLimbs = limbs.size();
      for (int i = 0; i < numLimbs; i++) {
        cSPEditorLimbStructure* limb = new ("Editor", 0, 0, 0, 0) cSPEditorLimbStructure();
        limb->Init(limbs[i], 0, 0);
        mLimbs.push_back(limb);
      }
    }
    if (mSpine)
      mSpine->Rebuild(false, true);
    mOriginalPlanarPosition = PickPlaneOfSymmetry(x, y, false);
    cSPBoundingBox limits(cSPVector3(FLT_MAX, FLT_MAX, FLT_MAX), cSPVector3(-FLT_MAX, -FLT_MAX, -FLT_MAX));
    CalcBoundsForMovement(cSPVector3(0.0f, 0.0f, 0.0f), mCurrModelBounds, limits, false);
  }
  return false;
}
}  // namespace SP

// ---------------------------------------------------------------- editor rollover cursor attachment
class IDrawable {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual void SetHighlight(int a);                             // +0x1c
};
class IWindow {
 public:
  PV(0) PV(1) PV(2)
  virtual IDrawable* Cast(uint32_t typeID);                     // +0xc
  virtual IWindow* GetParent();                                 // +0x10
  PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual uint32_t GetFlags();                                  // +0x28
  PV(11) PV(12) PV(13)
  virtual void Revalidate();                                    // +0x38
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
  virtual void SetFlag(int flag, bool value);                   // +0x7c
  virtual void SetCaption(const wchar_t* text);                 // +0x80
  PV(33) PV(34) PV(35)
  virtual void Refresh();                                       // +0x90
};

class cSPUILayout {
 public:
  IWindow* FindWindowByID(uint32_t id, bool recursive);
  void SetParentWin(IWindow* parent, bool b, uint32_t id);
  char pad[0xc];
};

class cSPUIPropertyLayout {
 public:
  virtual void AddRef();
  PV(1) PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual void Hide();                                      // +0x1c
};
struct cSPUIPropertyLayoutRefCount {
  virtual void rc0();
  int mRefCount;
};
struct cISPUICursorAttachment {
  virtual void ca0();
};
class cSPUICursorAttachmentLayoutBase : public cSPUIPropertyLayout, public cSPUIPropertyLayoutRefCount {
 public:
  cSPUILayout mLayout;                                      // +0xc
  char pad18[0x78 - 0x18];
};
class cSPUICursorAttachmentLayout : public cSPUICursorAttachmentLayoutBase, public cISPUICursorAttachment {
 public:
  cSPUICursorAttachmentLayout();                            // FUN_00801280
  bool Init();                                              // UI::CursorAttachment::Initialize (0x00828250)
  void SetLayoutName(const wchar_t* name, uint32_t group);  // FUN_00827fc0
  char pad7c[4];
};

class cSPEditorRolloverAttachment : public cSPUICursorAttachmentLayout {
 public:
  IWindow* mpRootWindow;   // +0x80
  IWindow* mpBackground;   // +0x84
  IWindow* mpTitle;        // +0x88
  IWindow* mpDescription;  // +0x8c
  bool mbHidden;           // +0x90

  cSPEditorRolloverAttachment();
  virtual void Hide();
  virtual void rc0();
  virtual void ca0();
  bool Initialize();
  void Show();
  bool IsVisible();
  void SetText(const wchar_t* text);
};

// @ 0x005BED80
cSPEditorRolloverAttachment::cSPEditorRolloverAttachment() {
  mpRootWindow = 0;
  mpBackground = 0;
  mpTitle = 0;
  mpDescription = 0;
  mbHidden = true;
  SetLayoutName(L"RolloverEditorMessage", 0x40464100);
}

// @ 0x005BEDF0
bool cSPEditorRolloverAttachment::Initialize() {
  bool ok = Init();
  if (ok) {
    mpRootWindow = mLayout.FindWindowByID(0, true);
    if (mpRootWindow) {
      mpBackground = mLayout.FindWindowByID(0x125f2c4f, true);
      mpTitle = mLayout.FindWindowByID(0x70524f6b, true);
      mpDescription = mLayout.FindWindowByID(0xb25f2df9, true);
    }
    mbHidden = false;
  }
  return ok;
}

// @ 0x005BEE80
void cSPEditorRolloverAttachment::Show() {
  if (!mbHidden && mpRootWindow)
    mpRootWindow->SetFlag(1, false);
}

// @ 0x005BEEB0
bool cSPEditorRolloverAttachment::IsVisible() {
  if (!mbHidden && mpRootWindow)
    return mpRootWindow->GetFlags() & 1;
  return false;
}

template <typename T>
inline IDrawable* object_cast(T* p) { return p ? p->Cast(0xf15f4bd) : 0; }

// @ 0x005BEF50
void cSPEditorRolloverAttachment::SetText(const wchar_t* text) {
  if (mbHidden)
    Hide();
  if (mpRootWindow && mpBackground && mpTitle && mpDescription) {
    mpTitle->SetCaption(text);
    mpDescription->SetCaption(text);
    object_cast(mpTitle)->SetHighlight(0);
    object_cast(mpDescription)->SetHighlight(0);
    mpTitle->Revalidate();
    mpRootWindow->Revalidate();
    mpBackground->Revalidate();
    mpBackground->SetFlag(1, true);
    mpTitle->Refresh();
    mpDescription->Refresh();
    mpRootWindow->SetFlag(1, true);
  }
}

// ---------------------------------------------------------------- SP::cSPEditorNaming
namespace SP {
class cISPEditorNameProvider;
struct NameMessage {
  cISPEditorNameProvider* mpProvider;  // +0x0
  uint32_t pad4;
  const wchar_t* mpText;               // +0x8
};
struct MouseMessage {
  uint32_t pad0[2];
  struct Msg {
    uint32_t pad0[2];
    int mType;      // +0x8
    int mId;        // +0xc
    char mButton;   // +0x10
    char pad11[3];
    int mX;         // +0x14
    int mY;         // +0x18
  }* mpMsg;  // +0x8
};
bool IsMouseCaptured();  // FUN_008053b0
void ScreenToWindow(float x, float y, float* outX, float* outY);  // FUN_00804f80
class IWindowManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16)
  virtual IWindow* PickWindow(const float* point);  // +0x44
};
IWindowManager* WindowManager();

struct cSPEditorNamingWinProc {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual void SetExpanded(bool expanded);  // +0x1c
};
class cSPEditorNaming : public cSPEditorNamingWinProc {
 public:
  struct IHandlerRC {
    virtual bool HandleMessage(uint32_t messageID, void* message);
  };
  // the IHandlerRC base sits at +0x4
  struct Handler : public IHandlerRC {
    bool HandleMessage(uint32_t messageID, void* message);
    char pad04[8];
    bool mIsExpanded;                        // +0xc (full +0x10)
    bool mAllowNameEdit;                     // +0xd
    char pad0e[2];
    void* mNameGuard;                        // +0x10
    cSPUILayout* mLayout;                    // +0x14 (full +0x18)
    cISPEditorNameProvider* mpDataProvider;  // +0x18 (full +0x1c)
  } mHandler;                                // +0x4
  uint32_t mNameType;                        // +0x20
  struct WString { wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; int mAllocator; } mNamePrompt;  // +0x24
  IWindow* mOriginalParent;                  // +0x34

  void SetDisplayText(const wchar_t* text);
  void ResetParentWin();
};

// @ 0x005BF950
void cSPEditorNaming::SetDisplayText(const wchar_t* text) {
  IWindow* window = mHandler.mLayout->FindWindowByID(0xd0e6d04b, true);
  if (window) {
    if (wcslen(text) == 0)
      window->SetCaption(mNamePrompt.mpBegin);
    else
      window->SetCaption(text);
  }
  window = mHandler.mLayout->FindWindowByID(0xc7ceb1bd, true);
  if (window)
    window->SetCaption(text);
}

// @ 0x005BF9D0
bool cSPEditorNaming::Handler::HandleMessage(uint32_t messageID, void* message) {
  switch (messageID) {
    case 0x73127e6:
      if (((NameMessage*)message)->mpProvider == mpDataProvider) {
        IWindow* window = mLayout->FindWindowByID(0x5415e48, true);
        if (window)
          window->SetCaption(((NameMessage*)message)->mpText);
        return true;
      }
      break;
    case 0x1ee1001:
      if (mIsExpanded) {
        MouseMessage::Msg* msg = ((MouseMessage*)message)->mpMsg;
        if (msg->mType == 5 && msg->mId == 0x3e8 && msg->mButton == 1 && !IsMouseCaptured()) {
          float px, py;
          ScreenToWindow((float)msg->mX, (float)msg->mY, &px, &py);
          float pt[2];
          pt[0] = px;
          pt[1] = py;
          IWindow* picked = WindowManager()->PickWindow(pt);
          IWindow* root = mLayout->FindWindowByID(0x272eb68e, true);
          IWindow* w = picked;
          if (picked != root) {
            for (;;) {
              if (!w) {
                ((cSPEditorNaming*)((char*)this - 4))->SetExpanded(false);
                break;
              }
              w = w->GetParent();
              if (w == root)
                return true;
            }
          }
          return true;
        }
      }
      break;
    case 0x14418c3f:
      if (((NameMessage*)message)->mpProvider == mpDataProvider) {
        IWindow* window = mLayout->FindWindowByID(0xaddc11ef, true);
        if (window)
          window->SetCaption(((NameMessage*)message)->mpText);
        return true;
      }
      break;
    case 0x7aa519dc:
      if (((NameMessage*)message)->mpProvider == mpDataProvider) {
        ((cSPEditorNaming*)((char*)this - 4))->SetDisplayText(((NameMessage*)message)->mpText);
        return true;
      }
      break;
  }
  return false;
}

// @ 0x005BFB70
void cSPEditorNaming::ResetParentWin() {
  mHandler.mLayout->SetParentWin(mOriginalParent, true, 0x5b598fa);
}
}  // namespace SP
