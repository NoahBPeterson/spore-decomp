// Slice s006a11b0: SP::cPropertyList / SP::cDirectPropertyList and the
// SPPropertyHelpers.obj free "GetPropertyAsXxx" accessors. /O2 /MD /Gy /EHsc /TP.
//
// Class layouts use the RETAIL offsets. The 2008 dev-build PDB has an extra
// 0x20-byte mDescriptions member on cPropertyList that retail does not have,
// so all cDirectPropertyList members sit 0x20 lower here than the PDB shows.
#include "types.h"

extern "C" long _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedExchange)

namespace EA {
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
}  // namespace EA
void Memset32(void* dest, int value, int count);
void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags,
                     const char* file, int line);

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
}  // namespace EA

// ---------------------------------------------------------------------------
// Value types
// ---------------------------------------------------------------------------
struct cSPColorRGB { float x, y, z; };
struct cSPColorRGBA { float x, y, z, w; };

namespace EA {
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
  uint32_t mInstance;  // +0x0
  uint32_t mType;      // +0x4
  uint32_t mGroup;     // +0x8
};
}  // namespace ResourceMan

struct Variant {
  Variant() : mFlags(0), mTypeId(0) {}
  Variant(const int& v);
  Variant(const float& v);
  Variant(const bool& v);
  Variant& operator=(const Variant& o);
  Variant& operator=(const EA::ResourceMan::Key& k);
  void Destruct(int flags);
  ~Variant() {
    if (mFlags & 4) Destruct(0);
  }
  uint32_t mData[4];  // +0x0
  uint16_t mFlags;    // +0x10
  uint16_t mTypeId;   // +0x12
  cSPColorRGB* GetColorRGB();
  cSPColorRGBA* GetColorRGBA();
  EA::ResourceMan::Key* GetKey();
  SP::cString* GetText();
  eastl::basic_string8* GetString8();
  eastl::basic_string16* GetString16();
};
}  // namespace EA

namespace eastl {
struct allocator {};
struct basic_string8 {
  char* mpBegin;                // +0x0
  char* mpEnd;                  // +0x4
  char* mpCapacity;             // +0x8
  eastl::allocator mAllocator;  // +0xc
  void assign(const char* p, const char* e);
};
struct basic_string16 {
  wchar_t* mpBegin;             // +0x0
  wchar_t* mpEnd;               // +0x4
  wchar_t* mpCapacity;          // +0x8
  eastl::allocator mAllocator;  // +0xc
  void assign(const wchar_t* p, const wchar_t* e);
};
}  // namespace eastl

namespace SP {
class cString;
void cStringSet(const void* src, cString* out);
}  // namespace SP

struct VariantPair {  // size 0x18
  unsigned int first;  // +0x0
  EA::Variant second;  // +0x4
};

// eastl::vector<eastl::pair<unsigned int,EA::Variant>,eastl::allocator>
namespace eastl {
VariantPair* lower_bound(VariantPair* first, VariantPair* last,
                         const unsigned int* key, unsigned char comp);
}

// ---------------------------------------------------------------------------
// SP class hierarchy (retail layout)
// ---------------------------------------------------------------------------
namespace SP {

// Object/Resource base of cPropertyList: vtable + refcount + resource key.
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

  cResourceBase(const char* name)
      : mRefCount(0),
        mKeyInstance(0),
        mKeyType(0),
        mKeyGroup(0),
        mReleaseCallback(0) {}
};

template <class T> struct Vec {
  T* mpBegin;      // +0
  T* mpEnd;        // +4
  T* mpCapacity;   // +8
  Vec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
};

class cPropertyList : public cResourceBase {
public:
  // vtable slot indices (byte offset / 4).
  virtual void SetProperty(unsigned int key, EA::Variant* value);  // 5  (0x14)
  virtual void RemoveProperty(unsigned int key);                    // 6  (0x18)
  virtual void v7();                                               // 7  (0x1c)
  virtual bool GetPropertyA(unsigned int key, EA::Variant** out);  // 8  (0x20)
  virtual bool GetProperty(unsigned int key, EA::Variant** out) const;  // 9 (0x24)
  virtual EA::Variant* GetPropertyValue(unsigned int key);         // 10 (0x28)
  virtual void v11();                                              // 11 (0x2c)
  virtual void v12(cPropertyList* src);                            // 12 (0x30)
  virtual void DeepCopy(cPropertyList* src);                       // 13 (0x34)
  virtual void DeepAdd(cPropertyList* src);                        // 14 (0x38)
  virtual void v15();                                              // 15 (0x3c)
  virtual bool Write(EA::IO::IStream* stream) const;               // 16 (0x40)
  virtual void v17();                                              // 17 (0x44)
  virtual void Clear();                                            // 18 (0x48)

  Vec<VariantPair> mPropertyMap;  // +0x18
  unsigned int mAlloc;            // +0x24
  unsigned int mLess;             // +0x28
  unsigned char mCompare;         // +0x2c
  cPropertyList* mParent;         // +0x30
  unsigned int mModificationCount;  // +0x34

  cPropertyList(const char* name);
  cPropertyList();
  void SetParent(cPropertyList* parent);
};

class cDirectPropertyList : public cPropertyList {
public:
  unsigned int mNumDirectProps;  // +0x38
  int* mDirectProps;             // +0x3c
  EA::Variant mTempDirectVariant;  // +0x40

  virtual bool GetPropertyA(unsigned int key, EA::Variant** out);  // 8 (0x20)
  virtual void Add(cPropertyList* src);                            // 12 (0x30)

  cDirectPropertyList(unsigned int count);
  virtual ~cDirectPropertyList();
  void SetBoolProperty(unsigned int index, bool value);
  void SetIntProperty(unsigned int index, int value);
  void SetFloatProperty(unsigned int index, float value);
};



// ---------------------------------------------------------------------------
// cPropertyList methods
// ---------------------------------------------------------------------------
// @ 0x006A1B90
cPropertyList::cPropertyList(const char* name)
    : cResourceBase(name), mParent(0), mModificationCount(0) {}

// @ 0x006A1C40
cPropertyList::cPropertyList()
    : cResourceBase(0), mParent(0), mModificationCount(0) {}

// @ 0x006A1CA0
cDirectPropertyList::cDirectPropertyList(unsigned int count)
    : cPropertyList(), mNumDirectProps(0), mDirectProps(0) {
  if (count) {
    mNumDirectProps = count;
    mDirectProps = new ("App/cDirectPropertyList", 0, 0, 0, 0) int[count];
    Memset32(mDirectProps, 0, mNumDirectProps);
  }
}

// @ 0x006A14D0
void cPropertyList::DeepCopy(cPropertyList* src) {
  if (this == src) return;
  cPropertyList* old = mParent;
  if (old) {
    mParent = 0;
    old->Release();
  }
  Clear();
  DeepAdd(src);
}

// @ 0x006A1510
void cPropertyList::DeepAdd(cPropertyList* src) {
  if (src->mParent) DeepAdd(src->mParent);
  v12(src);
}

// @ 0x006A1DE0
bool cPropertyList::GetPropertyA(unsigned int key, EA::Variant** out) {
  VariantPair* end = mPropertyMap.mpEnd;
  VariantPair* it = eastl::lower_bound(mPropertyMap.mpBegin, end, &key, mCompare);
  if (it == end || key < it->first)
    it = end;
  else if (it == it + 1)
    it = end;
  if (it != end) {
    *out = &it->second;
    return true;
  }
  if (mParent) return mParent->GetPropertyA(key, out);
  return false;
}

// @ 0x006A1600
void cDirectPropertyList::Add(cPropertyList* src) {
  if (this == src) return;
  VariantPair* it = src->mPropertyMap.mpBegin;
  VariantPair* end = src->mPropertyMap.mpEnd;
  for (; it != end; ++it) {
    SetProperty(it->first, &it->second);
  }
  mModificationCount++;
}

// @ 0x006A1E50
bool cDirectPropertyList::GetPropertyA(unsigned int key, EA::Variant** out) {
  if (key < mNumDirectProps) {
    *out = GetPropertyValue(key);
    return true;
  }
  return cPropertyList::GetPropertyA(key, out);
}

}  // namespace SP

// ---------------------------------------------------------------------------
// SP::GetPropertyAsXxx accessors
// ---------------------------------------------------------------------------
namespace SP {
bool GetPropertyAsColorRGB(const cPropertyList* list, unsigned int key, cSPColorRGB* out);
bool GetPropertyAsColorRGBA(const cPropertyList* list, unsigned int key, cSPColorRGBA* out);
bool GetPropertyAsKey(const cPropertyList* list, unsigned int key, EA::ResourceMan::Key* out);
bool GetPropertyAsKeyInstance(const cPropertyList* list, unsigned int key, unsigned int* out);
bool GetPropertyAsKeyGroup(const cPropertyList* list, unsigned int key, unsigned int* out);
bool GetPropertyAsKeyType(const cPropertyList* list, unsigned int key, unsigned int* out);
bool GetPropertyAsText(const cPropertyList* list, unsigned int key, cString* out);
bool GetPropertyAsString8(const cPropertyList* list, unsigned int key, eastl::basic_string8* out);
bool GetPropertyAsString16(const cPropertyList* list, unsigned int key, eastl::basic_string16* out);
bool GetPropertyAsChar8Ptr(const cPropertyList* list, unsigned int key, const char** out);
bool GetPropertyAsChar16Ptr(const cPropertyList* list, unsigned int key, const wchar_t** out);
}  // namespace SP

// @ 0x006A11B0
bool SP::GetPropertyAsColorRGB(const SP::cPropertyList* list, unsigned int key,
                               cSPColorRGB* out) {
  if (list == 0) return false;
  EA::Variant* prop;
  if (!list->GetProperty(key, &prop)) return false;
  if (prop->mTypeId == 0x32) {
    *out = *prop->GetColorRGB();
    return true;
  }
  return false;
}

// @ 0x006A1200
bool SP::GetPropertyAsColorRGBA(const SP::cPropertyList* list, unsigned int key,
                                cSPColorRGBA* out) {
  if (list == 0) return false;
  EA::Variant* prop;
  if (!list->GetProperty(key, &prop)) return false;
  if (prop->mTypeId == 0x34) {
    *out = *prop->GetColorRGBA();
    return true;
  }
  return false;
}

// @ 0x006A1250
bool SP::GetPropertyAsKey(const SP::cPropertyList* list, unsigned int key,
                          EA::ResourceMan::Key* out) {
  if (list == 0) return false;
  EA::Variant* prop;
  if (!list->GetProperty(key, &prop)) return false;
  if (prop->mTypeId == 0x20) {
    *out = *prop->GetKey();
    return true;
  }
  return false;
}

// @ 0x006A12A0
bool SP::GetPropertyAsKeyInstance(const SP::cPropertyList* list, unsigned int key,
                                  unsigned int* out) {
  if (list == 0) return false;
  EA::Variant* prop;
  if (!list->GetProperty(key, &prop)) return false;
  if (prop->mTypeId == 0x20) {
    *out = prop->GetKey()->mInstance;
    return true;
  }
  return false;
}

// @ 0x006A12E0
bool SP::GetPropertyAsKeyGroup(const SP::cPropertyList* list, unsigned int key,
                               unsigned int* out) {
  if (list == 0) return false;
  EA::Variant* prop;
  if (!list->GetProperty(key, &prop)) return false;
  if (prop->mTypeId == 0x20) {
    *out = prop->GetKey()->mGroup;
    return true;
  }
  return false;
}

// @ 0x006A1320
bool SP::GetPropertyAsKeyType(const SP::cPropertyList* list, unsigned int key,
                              unsigned int* out) {
  if (list == 0) return false;
  EA::Variant* prop;
  if (!list->GetProperty(key, &prop)) return false;
  if (prop->mTypeId == 0x20) {
    *out = prop->GetKey()->mType;
    return true;
  }
  return false;
}

// @ 0x006A1360
bool SP::GetPropertyAsText(const SP::cPropertyList* list, unsigned int key,
                           SP::cString* out) {
  if (list == 0) return false;
  EA::Variant* prop;
  if (!list->GetProperty(key, &prop)) return false;
  if (prop->mTypeId == 0x22) {
    cStringSet(prop->GetText(), out);
    return true;
  }
  return false;
}

// @ 0x006A13B0
bool SP::GetPropertyAsString8(const SP::cPropertyList* list, unsigned int key,
                              eastl::basic_string8* out) {
  if (list == 0) return false;
  EA::Variant* prop;
  if (!list->GetProperty(key, &prop)) return false;
  if (prop->mTypeId == 0x12) {
    eastl::basic_string8* src = prop->GetString8();
    if (src != out) {
      out->assign(src->mpBegin, src->mpEnd);
    }
    return true;
  }
  return false;
}

// @ 0x006A1400
bool SP::GetPropertyAsString16(const SP::cPropertyList* list, unsigned int key,
                               eastl::basic_string16* out) {
  if (list == 0) return false;
  EA::Variant* prop;
  if (!list->GetProperty(key, &prop)) return false;
  if (prop->mTypeId == 0x13) {
    eastl::basic_string16* src = prop->GetString16();
    if (src != out) {
      out->assign(src->mpBegin, src->mpEnd);
    }
    return true;
  }
  return false;
}

// @ 0x006A1450
bool SP::GetPropertyAsChar8Ptr(const SP::cPropertyList* list, unsigned int key,
                               const char** out) {
  if (list == 0) return false;
  EA::Variant* prop;
  if (!list->GetProperty(key, &prop)) return false;
  if (prop->mTypeId == 0x12) {
    *out = prop->GetString8()->mpBegin;
    return true;
  }
  return false;
}

// @ 0x006A1490
bool SP::GetPropertyAsChar16Ptr(const SP::cPropertyList* list, unsigned int key,
                                const wchar_t** out) {
  if (list == 0) return false;
  EA::Variant* prop;
  if (!list->GetProperty(key, &prop)) return false;
  if (prop->mTypeId == 0x13) {
    *out = prop->GetString16()->mpBegin;
    return true;
  }
  return false;
}

// ---------------------------------------------------------------------------
// IO helpers used by cPropertyList::Write
// ---------------------------------------------------------------------------
namespace EA {
namespace IO {
bool WriteUint32(IStream* stream, const void* pData, unsigned int count, int flags);
}
}  // namespace EA
bool WriteVariant(EA::IO::IStream* stream, EA::Variant* value, int flags);
VariantPair* PairsRealloc(unsigned int n, VariantPair* first, VariantPair* last);
void PairsDestroy(VariantPair* first, VariantPair* last);
VariantPair* PairsUninitMoveStart(VariantPair** dest, VariantPair* first,
                                  VariantPair* last, VariantPair* out);
VariantPair* PairsFillN(VariantPair* dest, unsigned int n, const VariantPair& value);

// @ 0x006A1540
bool SP::cPropertyList::Write(EA::IO::IStream* stream) const {
  int nCount = (int)(mPropertyMap.mpEnd - mPropertyMap.mpBegin);
  bool bResult = EA::IO::WriteUint32(stream, &nCount, 1, 0);
  int nLoop = (int)(mPropertyMap.mpEnd - mPropertyMap.mpBegin);
  for (int i = 0; i < nLoop; ++i) {
    if (bResult) {
      unsigned int key = mPropertyMap.mpBegin[i].first;
      bResult = EA::IO::WriteUint32(stream, &key, 1, 0);
      if (bResult)
        bResult = WriteVariant(stream, &mPropertyMap.mpBegin[i].second, 0) ? true
                                                                           : false;
    }
  }
  return bResult;
}

// @ 0x006A1710
void SP::cPropertyList::SetParent(SP::cPropertyList* parent) {
  if (parent != mParent) {
    if (parent) parent->AddRef();
    SP::cPropertyList* old = mParent;
    mParent = parent;
    if (old) old->Release();
  }
  if (parent == 0) {
    RemoveProperty(0xb2cccb);
  } else {
    EA::Variant v;
    v = *(EA::ResourceMan::Key*)&parent->mKeyInstance;
    SetProperty(0xb2cccb, &v);
  }
}

// @ 0x006A17E0
void SP::cDirectPropertyList::SetBoolProperty(unsigned int index, bool value) {
  if (index < mNumDirectProps) {
    mDirectProps[index] = value;
    return;
  }
  EA::Variant v(value);
  SetProperty(index, &v);
}

// @ 0x006A1880
void SP::cDirectPropertyList::SetIntProperty(unsigned int index, int value) {
  if (index < mNumDirectProps) {
    mDirectProps[index] = value;
    return;
  }
  EA::Variant v(value);
  SetProperty(index, &v);
}

// @ 0x006A1910
void SP::cDirectPropertyList::SetFloatProperty(unsigned int index, float value) {
  if (index < mNumDirectProps) {
    ((float*)mDirectProps)[index] = value;
    return;
  }
  EA::Variant v(value);
  SetProperty(index, &v);
}

// @ 0x006A1BD0
SP::cDirectPropertyList::~cDirectPropertyList() {
  EA::Allocator::ZoneObject::operator delete(mDirectProps);
}

// ---------------------------------------------------------------------------
// eastl::vector<eastl::pair<unsigned int,EA::Variant> > helpers
// ---------------------------------------------------------------------------
// @ 0x006A1A70
VariantPair* PairsUninitMoveStart(VariantPair** dest, VariantPair* first,
                                  VariantPair* last, VariantPair* out) {
  *dest = out;
  for (; first != last; ++first) {
    VariantPair* d = *dest;
    if (d) {
      d->first = first->first;
      d->second.mFlags = 0;
      d->second.mTypeId = 0;
      d->second = first->second;
    }
    *dest = *dest + 1;
  }
  return *dest;
}

// @ 0x006A1B00
VariantPair* PairsFillN(VariantPair* dest, unsigned int n, const VariantPair& value) {
  for (; n != 0; --n, ++dest) {
    if (dest) {
      dest->first = value.first;
      dest->second.mFlags = 0;
      dest->second.mTypeId = 0;
      dest->second = value.second;
    }
  }
  return dest;
}

namespace eastl {
class pvector {
public:
  VariantPair* mpBegin;
  VariantPair* mpEnd;
  VariantPair* mpCapacity;

  unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
  unsigned int capacity() const { return (unsigned int)(mpCapacity - mpBegin); }

  pvector& operator=(const pvector& x);
  void DoInsertValues(VariantPair* position, unsigned int n, const VariantPair& value);
};
}  // namespace eastl

// @ 0x006A1E80
eastl::pvector& eastl::pvector::operator=(const eastl::pvector& x) {
  if (this == &x) return *this;

  const unsigned int n = x.size();
  const unsigned int cur = size();

  if (n > capacity()) {
    VariantPair* p = PairsRealloc(n, x.mpBegin, x.mpEnd);
    PairsDestroy(mpBegin, mpEnd);
    if (mpBegin) EA::Allocator::ZoneObject::operator delete(mpBegin);
    mpCapacity = p + n;
    mpBegin = p;
    mpEnd = p + n;
    return *this;
  }

  if (cur < n) {
    for (unsigned int i = 0; i < cur; ++i)
      mpBegin[i] = x.mpBegin[i];
    VariantPair* dest = mpEnd;
    PairsUninitMoveStart(&dest, x.mpBegin + cur, x.mpEnd, mpEnd);
    mpEnd = mpBegin + n;
    return *this;
  }

  for (unsigned int i = 0; i < n; ++i)
    mpBegin[i] = x.mpBegin[i];
  PairsDestroy(mpBegin + n, mpEnd);
  mpEnd = mpBegin + n;
  return *this;
}

// @ 0x006A2010
void eastl::pvector::DoInsertValues(VariantPair* position, unsigned int n,
                                    const VariantPair& value) {
  if (n == 0) return;

  const unsigned int idx = (unsigned int)(position - mpBegin);
  const unsigned int cur = size();

  // Complete (reallocating) insertion: build the new sequence in a fresh buffer.
  const unsigned int newCap = cur + n;
  VariantPair* p = PairsRealloc(newCap, mpBegin, mpEnd);
  VariantPair* dest = p;
  PairsUninitMoveStart(&dest, mpBegin, mpBegin + idx, p);
  PairsFillN(p + idx, n, value);
  VariantPair* dest2 = p + idx + n;
  PairsUninitMoveStart(&dest2, mpBegin + idx, mpEnd, p + idx + n);
  PairsDestroy(mpBegin, mpEnd);
  if (mpBegin) EA::Allocator::ZoneObject::operator delete(mpBegin);
  mpBegin = p;
  mpEnd = p + cur + n;
  mpCapacity = p + newCap;
}
