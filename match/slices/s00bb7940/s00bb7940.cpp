// Slice s00bb7940 -- cGalaxyGameEntryUIStateMachine::PickRandomAsset (PDB candidate).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include <new>
#include "types.h"

extern "C" void EASTL_allocator_deallocate(void* p);   // operator_delete__ at 0xf47380

namespace EA {
template <typename T>
class AutoRefCount {
 public:
  T* mpObject;
  AutoRefCount() : mpObject(0) {}
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

namespace ResourceMan {
struct Key {
  uint32_t mInstance;
  uint32_t mType;
  uint32_t mGroup;
};
class IRecord {
 public:
  virtual void AddRef();
  virtual void Release();
  virtual void pv2();
  virtual int QueryInterface(uint32_t typeId);   // +0x0c
};
class IResourceManager {
 public:
  virtual void pv0(); virtual void pv1(); virtual void pv2();
  virtual bool GetResource(const Key& key, IRecord** ppRecord, int a, int b, int c, int d);   // +0x0c
};
IResourceManager* GetManager();   // 0x0067dcd0
}
namespace Random {
struct RandomLinearCongruential {
  uint32_t mSeed;
  uint32_t RandomUint32Uniform(uint32_t n);   // 0x00a68fb0
};
}
}
using EA::ResourceMan::Key;

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
  T* DoInsertValue(T* position, const T& value);   // 0x004e3e10
  void push_back(const T& value) {
    if (mpEnd < mpCapacity)
      ::new (mpEnd++) T(value);
    else
      DoInsertValue(mpEnd, value);
  }
};
}

// ---------------------------------------------------------------- constraints
struct ConstraintVec;
struct IntRange { int mMin; int mMax; };
struct FloatRange { float mMin; float mMax; };
struct Constraint;
struct ConstraintVec {
  Constraint* mpBegin;
  Constraint* mpEnd;
  Constraint* mpCapacity;
  int mAllocator[2];
  ConstraintVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ConstraintVec(const ConstraintVec&);                         // 0x004e38d0
  void DoDestroyValues(Constraint* first, Constraint* last);   // 0x004e39a0
  void DoInsertValue(Constraint* pos, const Constraint& v);    // 0x004e39d0
  ~ConstraintVec() {
    DoDestroyValues(mpBegin, mpEnd);
    if (mpBegin && ((int*)mpBegin)[-1] != 0)
      EASTL_allocator_deallocate(mpBegin);
  }
  inline void push_back(const Constraint& v);
};
struct Constraint {   // retail layout, 0x24 bytes
  uint32_t mParameter;
  int mType;
  union {
    IntRange mIntVal;
    FloatRange mFloatVal;
  };
  ConstraintVec mTail;
  Constraint(uint32_t property, uint32_t op, uint32_t value);   // 0x00558960
  Constraint(uint32_t property, int op, uint32_t value);        // 0x00558a20
};
inline void ConstraintVec::push_back(const Constraint& v) {
  if (mpEnd < mpCapacity)
    ::new (mpEnd++) Constraint(v);
  else
    DoInsertValue(mpEnd, v);
}

// ---------------------------------------------------------------- game objects
class PropList {
 public:
  virtual void AddRef();
  virtual void Release();
  bool GetFloat(uint32_t id, float* out);   // 0x006135d0
};
class PropListMgr {
 public:
  bool GetPropList(const Key* key, PropList** out, int flags);   // 0x006138b0
};
struct PropMgrOwner {
  char pad[0x5c];
  PropListMgr* mpMgr;
};
PropMgrOwner* GetPropMgrOwner();   // 0x0067cb30

namespace SP {
class IObjectTemplateDB {
 public:
  virtual void pv0(); virtual void pv1(); virtual void pv2(); virtual void pv3();
  virtual void pv4(); virtual void pv5(); virtual void pv6(); virtual void pv7();
  virtual void pv8(); virtual void pv9(); virtual void pv10();
  virtual bool FindTemplates(eastl::sp_vector<Key>* out, ConstraintVec* constraints);   // +0x2c
  virtual void pv12(); virtual void pv13(); virtual void pv14(); virtual void pv15();
  virtual void pv16(); virtual void pv17(); virtual void pv18(); virtual void pv19();
  virtual void pv20(); virtual void pv21();
  virtual void Prefetch(const Key& key, bool b);   // +0x58
  virtual void pv23(); virtual void pv24(); virtual void pv25(); virtual void pv26();
  virtual void pv27(); virtual void pv28();
  virtual void InvalidateTemplate(const Key& key, int b);   // +0x74
};
IObjectTemplateDB* ObjectTemplateDB();   // 0x0067cb40
}

struct SomeCache {
  char pad[0x1c];
  struct Sub* mpSub;
};
struct Sub {
  bool Touch(Key* key, int a, int b);   // 0x00ec5a60
};
extern SomeCache* gSomeCache;           // [0x16c7aa4]
extern uint32_t gAssetGroup;            // [0x156c5f4]
extern EA::Random::RandomLinearCongruential sRandom;   // 0x1601760

// ===========================================================================
// @ 0x00bb7940
bool __stdcall PickRandomAsset(uint32_t* pInstance, bool bRepeat)
{
  if (*pInstance == 0 && !bRepeat)
    return false;
  bool bDone = false;
  Key key;
  do {
    if (*pInstance != 0) {
      EA::AutoRefCount<EA::ResourceMan::IRecord> rec;
      key.mInstance = *pInstance;
      key.mType = 0x366a930d;
      key.mGroup = gAssetGroup;
      EA::ResourceMan::IResourceManager* mgr = EA::ResourceMan::GetManager();
      mgr->GetResource(key, &rec.AsOutParam(), 0, 0, 0, 0);
      if (rec && rec->QueryInterface(0xe742574a)) {
        bDone = true;
      } else {
        SP::ObjectTemplateDB()->InvalidateTemplate(key, 0);
        *pInstance = 0;
      }
    }
    if (*pInstance == 0) {
      ConstraintVec constraints;
      constraints.push_back(Constraint(0x2dd90af, 0u, 0x366a930d));
      constraints.push_back(Constraint(0x2dc9d1e, 0, 0x27818fe6));
      constraints.push_back(Constraint(0x5a3584a7, 0u, 0));
      constraints.push_back(Constraint(0x3cc89b1, 0, 0x913b23be));
      eastl::sp_vector<Key> results;
      if (SP::ObjectTemplateDB()->FindTemplates(&results, &constraints)) {
        eastl::sp_vector<Key> buckets[4];
        Key pick;
        pick.mInstance = 0;
        pick.mType = 0;
        pick.mGroup = 0;
        for (uint32_t i = 0; i < (uint32_t)results.size(); i++) {
          Key* pKey = &results[i];
          EA::AutoRefCount<PropList> list;
          float f = 0.0f;
          PropListMgr* plm = GetPropMgrOwner()->mpMgr;
          if (plm->GetPropList(pKey, &list.mpObject, 0) &&
              list->GetFloat(0x190e18aa, &f)) {
            if (f < -2.0f)
              buckets[3].push_back(*pKey);
            else if (f < 2.0f)
              buckets[1].push_back(*pKey);
            else
              buckets[0].push_back(*pKey);
          } else {
            buckets[2].push_back(*pKey);
          }
        }
        for (uint32_t b = 0; b < 4; b++) {
          if (buckets[b].mpBegin != buckets[b].mpEnd) {
            int idx;
            if ((uint32_t)buckets[b].size() > 1)
              idx = sRandom.RandomUint32Uniform((uint32_t)buckets[b].size());
            else
              idx = 0;
            pick = buckets[b][idx];
            break;
          }
        }
        if (pick.mInstance != 0) {
          SP::ObjectTemplateDB()->Prefetch(pick, true);
          *pInstance = pick.mInstance;
          gSomeCache->mpSub->Touch(&pick, 0, 1);
        }
      }
      if (*pInstance == 0)
        break;
    }
    if (bDone)
      break;
  } while (true);
  return *pInstance != 0;
}
