// Shared stub declarations for slice s006a22a0 (SP::cPropertyList / cDirectPropertyList
// and the eastl::vector<pair<unsigned int,EA::Variant> > instantiations).
// Retail layouts; see match/slices/s006a11b0/s006a11b0.cpp for notes.
#pragma once
#include "types.h"

extern "C" long _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedExchange)

struct cSPColorRGB { float x, y, z; };
struct cSPColorRGBA { float x, y, z, w; };

namespace eastl {
struct allocator;
struct basic_string8;
struct basic_string16;
}  // namespace eastl

namespace SP {
class cString;
class cPropertyList;
}  // namespace SP

namespace EA {
namespace IO {
struct IStream;
}
namespace Allocator {
class ZoneObject {
public:
  virtual ~ZoneObject();
  static void* operator new(unsigned int n, const char* pName, int flags = 0,
                            unsigned int debugFlags = 0, const char* pFile = 0,
                            int line = 0);
  static void operator delete(void* p);
};
}  // namespace Allocator
namespace Thread {
template <class T> class AtomicInt {
public:
  AtomicInt(T x = 0) { SetValue(x); }
  void SetValue(T n) { _InterlockedExchange((long*)&mValue, n); }
  volatile T mValue;
};
}  // namespace Thread
namespace ResourceMan {
struct Key {
  uint32_t mInstance;
  uint32_t mType;
  uint32_t mGroup;
};
}  // namespace ResourceMan

struct Variant {
  Variant() : mFlags(0), mTypeId(0) {}
  Variant(const int& v);
  Variant(const float& v);
  Variant(const bool& v);
  Variant& operator=(const Variant& o);
  Variant& operator=(const ResourceMan::Key& k);
  void Destruct(int flags);
  ~Variant() {
    if (mFlags & 4) Destruct(0);
  }
  uint32_t mData[4];  // +0x0
  uint16_t mFlags;    // +0x10
  uint16_t mTypeId;   // +0x12
  void* GetString8();
  void* GetKey();
};
}  // namespace EA

void Memset32(void* dest, int value, int count);
void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags,
                     const char* file, int line);

struct VariantPair {
  unsigned int first;
  EA::Variant second;
};

namespace eastl {
VariantPair* lower_bound(VariantPair* first, VariantPair* last,
                         const unsigned int* key, unsigned char comp);
}

namespace SP {

class cResourceBase {
public:
  virtual int AddRef();
  virtual int Release();
  virtual ~cResourceBase();
  virtual void* Cast(unsigned int);
  virtual int GetReferenceCount();
  EA::Thread::AtomicInt<int> mRefCount;  // +0x04
  unsigned int mKeyInstance;             // +0x08
  unsigned int mKeyType;                 // +0x0c
  unsigned int mKeyGroup;                // +0x10
  void* mReleaseCallback;                // +0x14
  cResourceBase(const char* name);
  cResourceBase();
};

// eastl::vector_map<unsigned int,EA::Variant,...>; comparator lives at +0x14.
struct VariantMap {
  VariantPair* mpBegin;      // +0x00
  VariantPair* mpEnd;        // +0x04
  VariantPair* mpCapacity;   // +0x08
  unsigned int mAllocA;      // +0x0c
  unsigned int mAllocB;      // +0x10
  unsigned char mCompare;    // +0x14
  VariantMap() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  unsigned int erase(const unsigned int& key);
  VariantPair* insert(VariantPair* out, const VariantPair& value);
  VariantPair* InsertOrGet(const unsigned int& key, const EA::Variant& value);
  VariantPair* insert_pos(VariantPair* position, const VariantPair& value);
};

class cPropertyList : public cResourceBase {
public:
  virtual void SetProperty(unsigned int key, EA::Variant* value);  // 5
  virtual void RemoveProperty(unsigned int key);                    // 6
  virtual bool HasProperty(unsigned int key) const;                 // 7
  virtual bool GetPropertyA(unsigned int key, EA::Variant** out);   // 8
  virtual bool GetProperty(unsigned int key, EA::Variant** out) const;  // 9
  virtual EA::Variant* GetPropertyValue(unsigned int key) const;    // 10
  virtual void Copy(cPropertyList* src);                            // 11
  virtual void v12(cPropertyList* src);                            // 12
  virtual void DeepCopy(cPropertyList* src);                       // 13
  virtual void DeepAdd(cPropertyList* src);                        // 14
  virtual bool Read(EA::IO::IStream* stream);                      // 15
  virtual bool Write(EA::IO::IStream* stream) const;               // 16
  virtual unsigned int GetPropertyIDs(unsigned int* ids);          // 17
  virtual void Clear();                                            // 18

  VariantMap mPropertyMap;        // +0x18
  cPropertyList* mParent;         // +0x30
  unsigned int mModificationCount;  // +0x34

  cPropertyList(const char* name);
  cPropertyList();
  void SetParent(cPropertyList* parent);
  void ClearMapOnly();
};

class cDirectPropertyList : public cPropertyList {
public:
  unsigned int mNumDirectProps;   // +0x38
  int* mDirectProps;              // +0x3c
  EA::Variant mTempDirectVariant;  // +0x40

  virtual void SetProperty(unsigned int index, EA::Variant* value);         // 5
  virtual bool HasProperty(unsigned int index) const;                       // 7
  virtual bool GetPropertyA(unsigned int index, EA::Variant** out);         // 8
  virtual bool GetProperty(unsigned int index, EA::Variant** out) const;    // 9
  virtual EA::Variant* GetPropertyValue(unsigned int index) const;          // 10
  virtual void Copy(cPropertyList* src);                                    // 11
  virtual void Add(cPropertyList* src);                                     // 12
  virtual unsigned int GetPropertyIDs(unsigned int* ids);                   // 17
  virtual void Clear();                                                     // 18

  cDirectPropertyList(unsigned int count);
  virtual ~cDirectPropertyList();
  void SetBoolProperty(unsigned int index, bool value);
  void SetIntProperty(unsigned int index, int value);
  void SetFloatProperty(unsigned int index, float value);
  int GetIntProperty(unsigned int index) const;
  float GetFloatProperty(unsigned int index) const;
  bool GetDescription(unsigned int index) const;
};

}  // namespace SP

namespace eastl {
class pvector {
public:
  VariantPair* mpBegin;
  VariantPair* mpEnd;
  VariantPair* mpCapacity;
  unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
  unsigned int capacity() const { return (unsigned int)(mpCapacity - mpBegin); }
  pvector& operator=(const pvector& x);
  void resize(unsigned int n);
  VariantPair* erase(VariantPair* first, VariantPair* last);
  VariantPair* insert(VariantPair* position, const VariantPair& value);
  void DoInsertValue(VariantPair* position, const VariantPair& value);
  void DoInsertValues(VariantPair* position, unsigned int n, const VariantPair& value);
};
}  // namespace eastl
