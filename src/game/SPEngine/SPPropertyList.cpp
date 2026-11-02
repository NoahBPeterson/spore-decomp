// src/game/SPEngine/SPPropertyList.cpp -- migrated from slice(s) s00614050, s00613240, s00612270, s006a22a0, s006a11b0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPPropertyList.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cPropertyList.h"
#include "SP/cDirectPropertyList.h"
#include "EA/Variant.h"
#include "SP/cResourceBase.h"

// unnamed retail callees and globals (address in the comment)
extern "C" long _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedExchange)
#include "SP/cPropertyList.h"
#include "EA/IO/IStream.h"
#include "EA/ResourceMan/Key.h"
#include "EA/Variant.h"
#include "SP/cResourceBase.h"
#include "SP/cDirectPropertyList.h"
#include <new>
#include "EA/IO/FileStream.h"
#include <string.h>
#include "SP/FunctionalMatch/Constraint.h"
#include "SP/cPollinator.h"
#include <intrin.h>
#include "eastl/allocator.h"

// ---- items of slice s006a11b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
eastl::pair<unsigned int, EA::Variant>* lower_bound(eastl::pair<unsigned int, EA::Variant>* first, eastl::pair<unsigned int, EA::Variant>* last,
                         const unsigned int* key, unsigned char comp);  // 0x00612db0 (0x18-stride instance)
}
namespace EA {
namespace IO {
bool WriteUint32(IStream* stream, const void* pData, unsigned int count, int flags);  // namespace EA
}
}
namespace EA {
namespace Allocator {
class ZoneObject_s006a_11b0 {
public:
  virtual ~ZoneObject_s006a_11b0();
  static void* operator new(unsigned int n, const char* pName, int flags = 0,
                            unsigned int debugFlags = 0, const char* pFile = 0,
                            int line = 0);
  static void operator delete(void* p); // 0x00f47380
};  // namespace Allocator
}
}
void Memset32(void* dest, int value, int count);
void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags,
                     const char* file, int line);
namespace eastl {
class allocator_s006a_11b0;
}
namespace eastl {
struct basic_string8;
}
namespace eastl {
struct basic_string16;
}
namespace SP {
class cString_s006a_11b0;
}
namespace SP {
class cPropertyList_s006a_11b0;
}
namespace EA {
namespace IO {
struct IStream_s006a_11b0;  // namespace EA
}
}
struct cSPColorRGB_s006a_11b0 { float x, y, z; };
struct cSPColorRGBA_s006a_11b0 { float x, y, z, w; };
namespace EA {
namespace Thread {
template <class T> class AtomicInt_s006a_11b0 {
public:
  AtomicInt_s006a_11b0(T x = 0) { SetValue(x); }
  void SetValue(T n) { _InterlockedExchange((long*)&mValue, n); }
  volatile T mValue;
};  // namespace Thread
}
}
namespace EA {
namespace ResourceMan {
class Key_s006a_11b0 { public:
  uint32_t mInstance;  // +0x0
  uint32_t mType;      // +0x4
  uint32_t mGroup;     // +0x8
};  // namespace ResourceMan
}
}
namespace EA {
struct Variant_s006a_11b0 {
  Variant_s006a_11b0() : mFlags(0), mTypeId(0) {}
  Variant_s006a_11b0(const int& v);
  Variant_s006a_11b0(const float& v);
  Variant_s006a_11b0(const bool& v);
  Variant_s006a_11b0& operator=(const Variant_s006a_11b0& o);  // 0x00542b80
  void Destruct(int flags);  // 0x0093db80 (EA::Variant::Destruct)
  ~Variant_s006a_11b0() {
    if (mFlags & 4) Destruct(0);
  }
  uint32_t mData[4];  // +0x0
  uint16_t mFlags;    // +0x10
  uint16_t mTypeId;   // +0x12
  cSPColorRGB_s006a_11b0* GetColorRGB();  // 0x006a0fd0 (EA::Variant::GetColorRGB)
  cSPColorRGBA_s006a_11b0* GetColorRGBA();  // 0x006a1000 (EA::Variant::GetColorRGBA)
  EA::ResourceMan::Key_s006a_11b0* GetKey();  // 0x006a1030 (EA::Variant::GetKey)
  SP::cString_s006a_11b0* GetText();  // 0x006a1090 (EA::Variant::GetText)
  eastl::basic_string8* GetString8();  // 0x0060ebf0 (EA::Variant::GetString8)
  eastl::basic_string16* GetString16();  // 0x0068a4f0 (EA::Variant::GetString16)
};
}
EA::Variant_s006a_11b0& __fastcall VariantAssignCopy(EA::Variant_s006a_11b0* self, int reserved,
                                          const EA::Variant_s006a_11b0& o);  // 0x00542b80
namespace eastl {
class allocator_s006a_11b0 { public:};
}
namespace eastl {
struct basic_string8 {
  char* mpBegin;                // +0x0
  char* mpEnd;                  // +0x4
  char* mpCapacity;             // +0x8
  eastl::allocator_s006a_11b0 mAllocator;  // +0xc
  void assign(const char* p, const char* e);
};
}
namespace eastl {
struct basic_string16 {
  wchar_t* mpBegin;             // +0x0
  wchar_t* mpEnd;               // +0x4
  wchar_t* mpCapacity;          // +0x8
  eastl::allocator_s006a_11b0 mAllocator;  // +0xc
  void assign(const wchar_t* p, const wchar_t* e);
};
}
namespace SP {
class cString_s006a_11b0;
}
struct VariantPair {  // size 0x18
  unsigned int first;  // +0x0
  EA::Variant_s006a_11b0 second;  // +0x4
};
namespace eastl {
VariantPair* lower_bound(VariantPair* first, VariantPair* last,
                         const unsigned int* key, unsigned char comp);  // 0x00612db0 (0x18-stride instance)
}
namespace SP {
class cResourceBase_s006a_11b0 {
public:
  virtual int AddRef();  // 0x00432be0 (SP::cResourceBase::AddRef)
  virtual int Release();  // 0x00432b50 (SP::cResourceBase::Release)
  virtual ~cResourceBase_s006a_11b0();
  virtual void* Cast(unsigned int);
  virtual int GetReferenceCount();

  EA::Thread::AtomicInt_s006a_11b0<int> mRefCount;  // +0x04
  unsigned int mKeyInstance;             // +0x08
  unsigned int mKeyType;                 // +0x0c
  unsigned int mKeyGroup;                // +0x10
  void* mReleaseCallback;                // +0x14

  cResourceBase_s006a_11b0(const char* name)
      : mRefCount(0),
        mKeyInstance(0),
        mKeyType(0),
        mKeyGroup(0),
        mReleaseCallback(0) {}
};
}
namespace SP {
template <class T> struct Vec {
  T* mpBegin;      // +0
  T* mpEnd;        // +4
  T* mpCapacity;   // +8
  Vec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
};
}
namespace SP {
class cPropertyList_s006a_11b0 : public cResourceBase_s006a_11b0 {
public:
  // vtable slot indices (byte offset / 4).
  virtual void SetProperty(unsigned int key, EA::Variant_s006a_11b0* value);  // 5  (0x14) 0x006a2e20
  virtual void RemoveProperty(unsigned int key);                    // 6  (0x18) 0x006a2ef0
  virtual void v7();                                               // 7  (0x1c)
  virtual bool GetPropertyA(unsigned int key, EA::Variant_s006a_11b0** out);  // 8  (0x20)
  virtual bool GetProperty(unsigned int key, EA::Variant_s006a_11b0** out) const;  // 9 (0x24)
  virtual EA::Variant_s006a_11b0* GetPropertyValue(unsigned int key);         // 10 (0x28) 0x006a24d0
  virtual void v11();                                              // 11 (0x2c)
  virtual void v12(cPropertyList_s006a_11b0* src);                            // 12 (0x30)
  virtual void DeepCopy(cPropertyList_s006a_11b0* src);                       // 13 (0x34) 0x006a14d0
  virtual void DeepAdd(cPropertyList_s006a_11b0* src);                        // 14 (0x38) 0x006a1510
  virtual void v15();                                              // 15 (0x3c)
  virtual bool Write(EA::IO::IStream_s006a_11b0* stream) const;               // 16 (0x40) 0x006a1540
  virtual void v17();                                              // 17 (0x44)
  virtual void Clear();                                            // 18 (0x48) 0x006a2a80

  Vec<VariantPair> mPropertyMap;  // +0x18
  unsigned int mAlloc;            // +0x24
  unsigned int mLess;             // +0x28
  unsigned char mCompare;         // +0x2c
  cPropertyList_s006a_11b0* mParent;         // +0x30
  unsigned int mModificationCount;  // +0x34

  cPropertyList_s006a_11b0(const char* name);
  cPropertyList_s006a_11b0();
  void SetParent(cPropertyList_s006a_11b0* parent);
};
}
namespace SP {
class cDirectPropertyList_s006a_11b0 : public cPropertyList_s006a_11b0 {
public:
  unsigned int mNumDirectProps;  // +0x38
  int* mDirectProps;             // +0x3c
  EA::Variant_s006a_11b0 mTempDirectVariant;  // +0x40

  virtual bool GetPropertyA(unsigned int key, EA::Variant_s006a_11b0** out);  // 8 (0x20)
  virtual void Add(cPropertyList_s006a_11b0* src);                            // 12 (0x30) 0x006a1600

  cDirectPropertyList_s006a_11b0(unsigned int count);
  virtual ~cDirectPropertyList_s006a_11b0();
  void SetBoolProperty(unsigned int index, bool value);  // 0x0093a2e0 (SP::cDirectPropertyList::SetBoolProperty)
  void SetIntProperty(unsigned int index, int value);  // 0x006a1880 (SP::cDirectPropertyList::SetIntProperty)
  void SetFloatProperty(unsigned int index, float value);  // 0x006a1910 (SP::cDirectPropertyList::SetFloatProperty)
};
}
namespace EA {
namespace IO {
bool WriteUint32(IStream_s006a_11b0* stream, const void* pData, unsigned int count, int flags);  // namespace EA
}
}
bool WriteVariant(EA::IO::IStream_s006a_11b0* stream, EA::Variant_s006a_11b0* value, int flags);
VariantPair* __fastcall PairsRealloc(void* self, int reserved, unsigned int n,
                                     VariantPair* first, VariantPair* last);  // 0x006a1d80
void __fastcall PairsDestroy(void* self, int reserved, VariantPair* first,
                            VariantPair* last);  // 0x00685a30
VariantPair* UninitializedCopyPairs(VariantPair* first, VariantPair* last,
                                    VariantPair* dest);  // 0x00612b20
VariantPair* PairsUninitMoveStart(VariantPair** dest, VariantPair* first,
                                  VariantPair* last, VariantPair* out);
VariantPair* PairsFillN(VariantPair* dest, unsigned int n, const VariantPair& value);
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
};  // namespace eastl
}
// ---- items of slice s006a11b0 end

// ---- items of slice s006a22a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace IO {
struct IStream;
}
}
    void Memset32(...); // 0x0092cb00
namespace SP {
class cPropertyList_s006a_22a0;
}
namespace EA {
namespace IO {
struct IStream_s006a_22a0;
}
}
namespace EA {
namespace Allocator {
class ZoneObject_s006a_22a0 {
public:
  virtual ~ZoneObject_s006a_22a0();
  static void* operator new(unsigned int n, const char* pName, int flags = 0,
                            unsigned int debugFlags = 0, const char* pFile = 0,
                            int line = 0);
  static void operator delete(void* p); // 0x00f47380
};  // namespace Allocator
}
}
namespace EA {
namespace Thread {
template <class T> class AtomicInt_s006a_22a0 {
public:
  AtomicInt_s006a_22a0(T x = 0) { SetValue(x); }
  void SetValue(T n) { _InterlockedExchange((long*)&mValue, n); }
  volatile T mValue;
};  // namespace Thread
}
}
namespace EA {
namespace ResourceMan {
class Key_s006a_22a0 { public:
  uint32_t mInstance;
  uint32_t mType;
  uint32_t mGroup;
};  // namespace ResourceMan
}
}
namespace EA {
struct Variant_s006a_22a0 {
  Variant_s006a_22a0() : mFlags(0), mTypeId(0) {}
  Variant_s006a_22a0& operator=(const bool& v);   // 0x00422e20
  Variant_s006a_22a0& operator=(const int& v);    // 0x00422eb0
  Variant_s006a_22a0& operator=(const float& v);  // 0x00428060
  Variant_s006a_22a0& operator=(const Variant_s006a_22a0& o);
  Variant_s006a_22a0& operator=(const ResourceMan::Key_s006a_22a0& k);
  void Destruct(bool flags);           // 0x0093db80
  ~Variant_s006a_22a0() {
    if (mFlags & 4) Destruct(0);
  }
  uint32_t mData[4];  // +0x0
  uint16_t mFlags;    // +0x10
  uint16_t mTypeId;   // +0x12
  void* GetString8();  // 0x0060ebf0 (EA::Variant::GetString8)
  void* GetKey();  // 0x006a1030 (EA::Variant::GetKey)
};
}
void __fastcall VariantCopyAssign(EA::Variant_s006a_22a0* dst, int unused,
                                  const EA::Variant_s006a_22a0* src); // 0x00542b80
struct VariantPair_s006a_22a0 {
  unsigned int first;
  EA::Variant_s006a_22a0 second;
};
namespace eastl {
VariantPair_s006a_22a0* lower_bound_s006a_22a0(VariantPair_s006a_22a0* first, VariantPair_s006a_22a0* last,
                         const unsigned int* key, unsigned char comp);  // 0x00612db0 (0x18-stride instance)
}
namespace SP {
class cResourceBase_s006a_22a0 {
public:
  virtual int AddRef();  // 0x00432be0 (SP::cResourceBase::AddRef)
  virtual int Release();  // 0x00432b50 (SP::cResourceBase::Release)
  virtual ~cResourceBase_s006a_22a0();
  virtual void* Cast(unsigned int);
  virtual int GetReferenceCount();
  EA::Thread::AtomicInt_s006a_22a0<int> mRefCount;  // +0x04
  unsigned int mKeyInstance;             // +0x08
  unsigned int mKeyType;                 // +0x0c
  unsigned int mKeyGroup;                // +0x10
  void* mReleaseCallback;                // +0x14
  cResourceBase_s006a_22a0(const char* name);
  cResourceBase_s006a_22a0();
};
}
namespace SP {
struct VariantMap {
  VariantPair_s006a_22a0* mpBegin;      // +0x00
  VariantPair_s006a_22a0* mpEnd;        // +0x04
  VariantPair_s006a_22a0* mpCapacity;   // +0x08
  unsigned int mAllocA;      // +0x0c
  unsigned int mAllocB;      // +0x10
  unsigned char mCompare;    // +0x14
  VariantMap() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  unsigned int erase(const unsigned int& key);
  VariantPair_s006a_22a0* insert(VariantPair_s006a_22a0* out, const VariantPair_s006a_22a0& value);
  VariantPair_s006a_22a0* InsertOrGet(const unsigned int& key, const EA::Variant_s006a_22a0& value);
  VariantPair_s006a_22a0* insert_pos(VariantPair_s006a_22a0* position, const VariantPair_s006a_22a0& value);
  void ClearMapOnly();
};
}
namespace SP {
class cPropertyList_s006a_22a0 : public cResourceBase_s006a_22a0 {
public:
  virtual void SetProperty(unsigned int key, EA::Variant_s006a_22a0* value);  // 5 0x006a2e20
  virtual void RemoveProperty(unsigned int key);                    // 6 0x006a2ef0
  virtual bool HasProperty(unsigned int key) const;                 // 7 0x006a2470
  virtual bool GetPropertyA(unsigned int key, EA::Variant_s006a_22a0** out);   // 8
  virtual bool GetProperty(unsigned int key, EA::Variant_s006a_22a0** out) const;  // 9
  virtual EA::Variant_s006a_22a0* GetPropertyValue(unsigned int key) const;    // 10 0x006a24d0
  virtual void Copy(cPropertyList_s006a_22a0* src);                            // 11
  virtual void v12(cPropertyList_s006a_22a0* src);                            // 12
  virtual void DeepCopy(cPropertyList_s006a_22a0* src);                       // 13 0x006a14d0
  virtual void DeepAdd(cPropertyList_s006a_22a0* src);                        // 14 0x006a1510
  virtual bool Read(EA::IO::IStream_s006a_22a0* stream);                      // 15 0x006a2f60
  virtual bool Write(EA::IO::IStream_s006a_22a0* stream) const;               // 16 0x006a1540
  virtual unsigned int GetPropertyIDs(unsigned int* ids);          // 17 0x006a3070
  virtual void Clear();                                            // 18 0x006a2a80

  VariantMap mPropertyMap;        // +0x18
  cPropertyList_s006a_22a0* mParent;         // +0x30
  unsigned int mModificationCount;  // +0x34

  cPropertyList_s006a_22a0(const char* name);
  cPropertyList_s006a_22a0();
  void SetParent(cPropertyList_s006a_22a0* parent);
};
}
namespace SP {
class cDirectPropertyList_s006a_22a0 : public cPropertyList_s006a_22a0 {
public:
  unsigned int mNumDirectProps;   // +0x38
  int* mDirectProps;              // +0x3c
  EA::Variant_s006a_22a0 mTempDirectVariant;  // +0x40

  virtual void SetProperty(unsigned int index, EA::Variant_s006a_22a0* value);         // 5
  virtual bool HasProperty(unsigned int index) const;                       // 7 0x006a27d0
  virtual bool GetPropertyA(unsigned int index, EA::Variant_s006a_22a0** out);         // 8
  virtual bool GetProperty(unsigned int index, EA::Variant_s006a_22a0** out) const;    // 9
  EA::Variant_s006a_22a0 const& GetProperty(unsigned int key) const;
  virtual void Copy(cPropertyList_s006a_22a0* src);                                    // 11 0x006a2ad0
  virtual void Add(cPropertyList_s006a_22a0* src);                                     // 12 0x006a1600
  virtual unsigned int GetPropertyIDs(unsigned int* ids);                   // 17 0x006a3180
  virtual void Clear();                                                     // 18 0x006a2b20

  cDirectPropertyList_s006a_22a0(unsigned int count);
  virtual ~cDirectPropertyList_s006a_22a0();
  void SetBoolProperty(unsigned int index, bool value);  // 0x0093a2e0 (SP::cDirectPropertyList::SetBoolProperty)
  void SetIntProperty(unsigned int index, int value);  // 0x006a1880 (SP::cDirectPropertyList::SetIntProperty)
  void SetFloatProperty(unsigned int index, float value);  // 0x006a1910 (SP::cDirectPropertyList::SetFloatProperty)
  int GetIntProperty(unsigned int index) const;  // 0x006a2660 (SP::cDirectPropertyList::GetIntProperty)
  float GetFloatProperty(unsigned int index) const;  // 0x006a2710 (SP::cDirectPropertyList::GetFloatProperty)
  bool GetDescription(unsigned int index) const;  // 0x006a25a0 (SP::cDirectPropertyList::GetDescription)
};
}
namespace eastl {
class pvector_s006a_22a0 {
public:
  VariantPair_s006a_22a0* mpBegin;
  VariantPair_s006a_22a0* mpEnd;
  VariantPair_s006a_22a0* mpCapacity;
  unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
  unsigned int capacity() const { return (unsigned int)(mpCapacity - mpBegin); }
  pvector_s006a_22a0& operator=(const pvector_s006a_22a0& x);
  void resize(unsigned int n);
  VariantPair_s006a_22a0* erase(VariantPair_s006a_22a0* first, VariantPair_s006a_22a0* last);
  VariantPair_s006a_22a0* insert(VariantPair_s006a_22a0* position, const VariantPair_s006a_22a0& value);  // 0x006a2940 (eastl::pvector::insert)
  void DoInsertValue(VariantPair_s006a_22a0* position, const VariantPair_s006a_22a0& value);  // 0x006a22a0 (eastl::pvector::DoInsertValue)
  void DoInsertValues(VariantPair_s006a_22a0* position, unsigned int n, const VariantPair_s006a_22a0& value);  // 0x006a2010 (eastl::pvector::DoInsertValues)
};  // namespace eastl
}
extern EA::Variant_s006a_22a0 g_sNullVariant;  // 0x016027d0
void* PropertyManager();            // 0x0067de30
typedef void* (__fastcall* PropertyLookup)(void* mgr, int unused, unsigned int key);
bool WriteVariant(EA::IO::IStream_s006a_22a0* stream, EA::Variant_s006a_22a0* value, int flags);  // 0x00694440
namespace EA {
namespace IO {
bool ReadInt32(IStream_s006a_22a0* stream, void* pData, unsigned int count, int flags);  // 0x0093a780
}
}
struct VariantBytes {
  unsigned int mData[4];   // +0x00
  unsigned short mFlags;   // +0x10
  unsigned short mTypeId;  // +0x12
};
struct VariantOps {
  void* ToStr(const void* src);    // 0x006a19b0
  void* ToInt(const void* src);    // 0x0060d990
  void* ToFloat(const void* src);  // 0x006a1a10
};
static const void* VariantData(const VariantBytes* v, unsigned short tA,
                               unsigned short tB, unsigned int emptyAddr) {
  unsigned short t = v->mTypeId;
  if (t == tA || t == tB) {
    if ((v->mFlags & 0x30) == 0)
      return (const void*)(-(unsigned)(t != 0) & (unsigned)(size_t)v);
    return *(const void**)(const void*)v;
  }
  return (const void*)(size_t)emptyAddr;
}
static VariantPair_s006a_22a0* PairsAllocate(unsigned int n) {
  if (n == 0) return 0;
  return new ("App/cDirectPropertyList", 0, 0, 0, 0) VariantPair_s006a_22a0[n];
}
void PairsCopyRange(VariantPair_s006a_22a0* first, VariantPair_s006a_22a0* last, VariantPair_s006a_22a0* dst);  // 0x00612b20
void __stdcall PairsDestroyRange(VariantPair_s006a_22a0* first, VariantPair_s006a_22a0* last);      // 0x00685a30
void PairsCopyBytes(void* dst, const void* src, unsigned int size);           // 0x011e0744
static void PairsDestroy_s006a_22a0(VariantPair_s006a_22a0* first, VariantPair_s006a_22a0* last) {
  PairsDestroyRange(first, last);
}
static void PairsCopy(VariantPair_s006a_22a0* dst, VariantPair_s006a_22a0* first, VariantPair_s006a_22a0* last) {
  PairsCopyRange(first, last, dst);
}
static void PairsMoveBack(VariantPair_s006a_22a0* dstEnd, VariantPair_s006a_22a0* first, VariantPair_s006a_22a0* last) {
  for (; last != first;) *--dstEnd = *--last;
}
struct UIntVector {
  unsigned int* mpBegin;     // +0x00
  unsigned int* mpEnd;       // +0x04
  unsigned int* mpCapacity;  // +0x08
  void resize(unsigned int n);                                            // 0x004cd3c0
  void DoInsertValue(unsigned int* position, const unsigned int& value);  // 0x004558a0
  void DoInsertValues(unsigned int* position, unsigned int n, const unsigned int& value);  // 0x004cea40
};
VariantPair_s006a_22a0* SP::VariantMap::insert_pos(VariantPair_s006a_22a0* position, const VariantPair_s006a_22a0& value) {
  if (position == mpEnd && mpEnd != mpCapacity) {
    *mpEnd = value;
    mpEnd = mpEnd + 1;
    return position;
  }
  // full reallocation
  unsigned int n = (unsigned int)(position - mpBegin);
  unsigned int cur = (unsigned int)(mpEnd - mpBegin);
  unsigned int newCap = cur ? cur * 2 : 1;
  VariantPair_s006a_22a0* p = PairsAllocate(newCap);
  PairsCopy(p, mpBegin, position);
  p[n] = value;
  PairsCopy(p + n + 1, position, mpEnd);
  PairsDestroy_s006a_22a0(mpBegin, mpEnd);
  if (mpBegin) EA::Allocator::ZoneObject_s006a_22a0::operator delete(mpBegin);
  mpBegin = p;
  mpEnd = p + cur + 1;
  mpCapacity = p + newCap;
  return p + n;
}
static VariantPair_s006a_22a0* ShrinkEnd(VariantPair_s006a_22a0* begin, VariantPair_s006a_22a0* end) {
  int diff = (int)((char*)end - (char*)begin);
  return (VariantPair_s006a_22a0*)((char*)end - diff / 0x18 * 0x18);
}
VariantPair_s006a_22a0* eastl::pvector_s006a_22a0::erase(VariantPair_s006a_22a0* first, VariantPair_s006a_22a0* last) {
  unsigned int n = (unsigned int)(last - first);
  PairsCopy(first, last, mpEnd);
  PairsDestroy_s006a_22a0(mpEnd - n, mpEnd);
  mpEnd = mpEnd - n;
  return first;
}
void eastl::pvector_s006a_22a0::DoInsertValues(VariantPair_s006a_22a0* position, unsigned int n,
                                    const VariantPair_s006a_22a0& value) {
  if (n == 0) return;
  unsigned int idx = (unsigned int)(position - mpBegin);
  unsigned int cur = size();
  VariantPair_s006a_22a0* p = PairsAllocate(cur + n);
  PairsCopy(p, mpBegin, position);
  for (unsigned int i = 0; i < n; ++i) p[idx + i] = value;
  PairsCopy(p + idx + n, position, mpEnd);
  PairsDestroy_s006a_22a0(mpBegin, mpEnd);
  if (mpBegin) EA::Allocator::ZoneObject_s006a_22a0::operator delete(mpBegin);
  mpBegin = p;
  mpEnd = p + cur + n;
  mpCapacity = p + cur + n;
}
static unsigned int* ShrinkUIntEnd(unsigned int* base, unsigned int* end) {
  int diff = (int)((char*)end - (char*)base);
  return (unsigned int*)((char*)end - (diff >> 2) * 4);
}
    void* operator new[](unsigned int, char*, int, unsigned int, char*, int); // 0x00f473a0
// ---- items of slice s006a22a0 end

// ---- items of slice s00612270 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl EASTL_allocator_allocate(uint32_t size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0
void __cdecl EASTL_allocator_deallocate(void* p);                                                                                  // 0x00f47380
#define EASTL_ALLOCATOR_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
namespace EA {
struct Variant_s0061_2270 {
    char mData[16];
    uint16_t mFlags;
    uint16_t mTypeId;
    Variant_s0061_2270& operator=(const Variant_s0061_2270& x);  // 0x00542b80
    void Destruct(int);                    // 0x0093db80
    Variant_s0061_2270() : mFlags(0), mTypeId(0) {}
    Variant_s0061_2270(const Variant_s0061_2270& x) : mFlags(0), mTypeId(0) { *this = x; }
    ~Variant_s0061_2270() {
        if (mFlags & 4) Destruct(0);
    }
};
}
namespace EA {
namespace IO {
struct IStream_s0061_2270;
}
}
namespace EA {
namespace IO {
bool WriteUint32(IStream_s0061_2270* pStream, const uint32_t* pData, uint32_t count, int endian);  // 0x0093aa70
}
}
namespace EA {
namespace IO {
bool WriteUint64(IStream_s0061_2270* pStream, const uint64_t* pData, uint32_t count, int endian);  // 0x0093ab10
}
}
namespace eastl {
template <class T1, class T2>
struct pair_s0061_2270 {
    T1 first;
    T2 second;
    pair_s0061_2270() : second() {}
    pair_s0061_2270(const pair_s0061_2270& x) : first(x.first), second(x.second) {}
    pair_s0061_2270& operator=(const pair_s0061_2270& x) {
        first = x.first;
        second = x.second;
        return *this;
    }
};
}
namespace eastl {
class fixed_vector_allocator { public:
    const char* mpName;
    void* mpPoolBegin;
    void deallocate(void* p) {
        if (p != mpPoolBegin) EASTL_allocator_deallocate(p);
    }
    void* allocate(size_t n) { return EASTL_allocator_allocate(n, "Editor", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1); }
};
}
typedef eastl::pair_s0061_2270<uint32_t, EA::Variant_s0061_2270> PropPair;
struct IRefObj {
    virtual int AddRef();
    virtual int Release();
};
struct Elem16 {
    uint32_t a;
    uint32_t b;
    IRefObj* p;
    uint32_t pad;
    Elem16(const Elem16& x) : a(x.a), b(x.b), p(x.p) {
        if (p) p->AddRef();
    }
    ~Elem16() {
        IRefObj* const pObj = p;
        if (pObj) pObj->Release();
    }
};
namespace eastl {
struct PropVector {
    PropPair* mpBegin;
    PropPair* mpEnd;
    PropPair* mpCapacity;
    fixed_vector_allocator mAllocator;
    void reserve(size_t n);                                             // 0x00613020
    PropPair* DoRealloc(size_t n, const PropPair* first, int tag);        // 0x00612ea0
    void DestructRangeV(PropPair* first, PropPair* last);                 // 0x00685a30
    void assign(const PropPair* first, const PropPair* last, int tag);  // 0x00613140
};  // namespace eastl
}
struct Elem16VectorD {
    Elem16* mpBegin;
    Elem16* mpEnd;
    ~Elem16VectorD() {
        Elem16* const pEnd = mpEnd;
        for (Elem16* p = mpBegin; p < pEnd; ++p) p->~Elem16();
        if (mpBegin) EASTL_allocator_deallocate(mpBegin);
    }
};
template struct eastl::pair_s0061_2270<uint32_t, EA::Variant_s0061_2270>;
struct cStreamWriter {
    EA::IO::IStream_s0061_2270* mpStream;
    int mEndian;
    bool mbOk;
    char pad[7];
    cStreamWriter(EA::IO::IStream_s0061_2270* pStream, bool bBigEndian);  // 0x006b4f60
    void Accumulate(bool bResult);                              // 0x006b4f90
    void WriteVariant(const EA::Variant_s0061_2270* v);                    // 0x006b4fa0
    ~cStreamWriter();                                           // 0x006b5000
};
struct RefCountBase {
    virtual ~RefCountBase() {}
    volatile long mRefCount;
    RefCountBase() { _InterlockedExchange(&mRefCount, 0); }
};
struct PropertyBagBase : public RefCountBase {
    uint32_t pad8, padC, pad10, pad14;
    uint32_t mField18;
    PropertyBagBase(uint32_t a) : pad8(0), padC(0), pad10(0), pad14(0), mField18(a) {}
};
struct cPropertyBag : public PropertyBagBase {
    uint32_t mField1C;
    PropPair* mpBegin;       // +0x20
    PropPair* mpEnd;         // +0x24
    PropPair* mpCapacity;    // +0x28
    uint32_t mAllocName;     // +0x2c
    void* mpPoolBegin;       // +0x30
    char pad34[4];
    char mFixedBuffer[0xf0]; // +0x38
    cPropertyBag(uint32_t a, uint32_t b);  // 0x00612f00
    virtual ~cPropertyBag() {}
};
struct cPropertyListWriter {
    bool Write(EA::IO::IStream_s0061_2270* pStream, const cPropertyBag* pBag);  // 0x00612ba0
    bool WriteResource(void* pObject, void* pStreamHolder, int unused, uint32_t typeId);  // 0x00612e50
};
struct IObjectLike {
virtual void v0();
virtual void v1();
virtual void v2();
    virtual cPropertyBag* Cast(uint32_t typeId);  // +0xc
};
struct IStreamHolder {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
    virtual EA::IO::IStream_s0061_2270* GetStream();  // +0x18
};
// ---- items of slice s00612270 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
__declspec(noinline) PropPair* DestructRange(PropPair* first, PropPair* last, PropPair* dest);  // 0x00612a90 (stays in the slice: not this object's)

// ---- items of slice s00613240 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memcpy(void*, const void*, size_t);
extern const float kDefaultFloat;  // 0x015d1168
extern const int kDefaultInt;      // 0x015d1160
namespace EA {
struct Variant_s0061_3240 {
    char mData[16];
    uint16_t mFlags;
    uint16_t mTypeId;
    Variant_s0061_3240& Assign(const Variant_s0061_3240& x);  // 0x00542b80 (copy-assign; named Assign to avoid the
                                        // 0x00478300 symbol collision on the same mangled name)
    void Destruct(int);                    // 0x0093db80
    Variant_s0061_3240() : mFlags(0), mTypeId(0) {}
    Variant_s0061_3240(const Variant_s0061_3240& x) : mFlags(0), mTypeId(0) { Assign(x); }
    ~Variant_s0061_3240() {
        if (mFlags & 4) Destruct(0);
    }
};
}
namespace EA {
namespace IO {
struct IStream_s0061_3240;
}
}
namespace EA {
namespace IO {
bool ReadInt32(IStream_s0061_3240* pStream, int32_t* pData, uint32_t count, int endian);    // 0x0093a780
}
}
namespace EA {
namespace IO {
bool ReadUint64(IStream_s0061_3240* pStream, uint64_t* pData, uint32_t count, int endian);  // 0x0093a800
}
}
namespace EA {
namespace Messaging {
void RemoveHandler(void* a, void* b, void* c, void* d, void* e);  // 0x00571db0
}
}
namespace eastl {
template <class T1, class T2>
struct pair_s0061_3240 {
    T1 first;
    T2 second;
    pair_s0061_3240() : second() {}
    pair_s0061_3240(const T1& a, const T2& b) : first(a), second(b) {}
    pair_s0061_3240(const pair_s0061_3240& x) : first(x.first), second(x.second) {}
    pair_s0061_3240& operator=(const pair_s0061_3240& x) {
        first = x.first;
        second.Assign(x.second);
        return *this;
    }
};
}
namespace eastl {
struct MapCompare {};  // empty comparator (1 byte member)
}
typedef eastl::pair_s0061_3240<uint32_t, EA::Variant_s0061_3240> PropPair_s0061_3240;
struct Elem16_s0061_3240 {  // pair<uint64, intrusive_ptr<IRefObj>> (16 bytes)
    uint32_t a;
    uint32_t b;
    IRefObj* p;
    uint32_t pad;
    Elem16_s0061_3240(const uint64_t& key, IRefObj* ptr) : a(((const uint32_t*)&key)[0]), b(((const uint32_t*)&key)[1]), p(ptr) {}
    Elem16_s0061_3240(const Elem16_s0061_3240& x) : a(x.a), b(x.b), p(x.p) {
        if (p) p->AddRef();
    }
    Elem16_s0061_3240& operator=(const Elem16_s0061_3240& x) {
        a = x.a;
        b = x.b;
        IRefObj* const pNew = x.p;
        if (pNew != p) {
            IRefObj* const pTemp = p;
            if (pNew) pNew->AddRef();
            p = pNew;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
    ~Elem16_s0061_3240() {
        IRefObj* const pObj = p;
        if (pObj) pObj->Release();
    }
};
void* operator new(size_t, const char*, int, int, const char*, int);
PropPair_s0061_3240* __cdecl UninitializedCopy(const PropPair_s0061_3240*, const PropPair_s0061_3240*, PropPair_s0061_3240*);   // 0x00612d50
PropPair_s0061_3240* __cdecl DestructRange_s0061_3240(PropPair_s0061_3240*, PropPair_s0061_3240*, PropPair_s0061_3240*);                   // 0x00612a90
PropPair_s0061_3240* __cdecl CopyPairs(const PropPair_s0061_3240*, const PropPair_s0061_3240*, PropPair_s0061_3240*);           // 0x00612b20
PropPair_s0061_3240* __cdecl CopyBackward(PropPair_s0061_3240*, PropPair_s0061_3240*, PropPair_s0061_3240*);                    // 0x00612b60
const PropPair_s0061_3240* __cdecl LowerBound(const PropPair_s0061_3240*, const PropPair_s0061_3240*, const uint32_t&, eastl::MapCompare);  // 0x00612db0
Elem16_s0061_3240* __cdecl CopyElem16(Elem16_s0061_3240*, Elem16_s0061_3240*, Elem16_s0061_3240*);                              // 0x007c7e10
const uint32_t* __cdecl LowerBoundSet(const uint32_t*, const uint32_t*, const uint32_t*, eastl::MapCompare);  // 0x00555a20
inline PropPair_s0061_3240* RelocatePairs(PropPair_s0061_3240* first, PropPair_s0061_3240* last, PropPair_s0061_3240* dest) {
    PropPair_s0061_3240* const pEnd = UninitializedCopy(first, last, dest);
    DestructRange_s0061_3240(first, last, dest);
    return pEnd;
}
namespace eastl {
struct PropVector_s0061_3240 {
    PropPair_s0061_3240* mpBegin;
    PropPair_s0061_3240* mpEnd;
    PropPair_s0061_3240* mpCapacity;
    fixed_vector_allocator mAllocator;

    PropPair_s0061_3240* DoAllocate(size_t n) { return n ? (PropPair_s0061_3240*)mAllocator.allocate(n * sizeof(PropPair_s0061_3240)) : 0; }
    void DoInsertValue(PropPair_s0061_3240* position, const PropPair_s0061_3240& value);   // 0x00613240
    PropPair_s0061_3240* insert(PropPair_s0061_3240* position, const PropPair_s0061_3240& value);     // 0x00613920
    void DestructRangeV(PropPair_s0061_3240* first, PropPair_s0061_3240* last);            // 0x00685a30
    void reserve(size_t n);                                          // 0x00613020 (other slice)
    PropPair_s0061_3240* erase(PropPair_s0061_3240* first, PropPair_s0061_3240* last) {
        PropPair_s0061_3240* const pNewEnd = CopyPairs(last, mpEnd, first);
        DestructRangeV(pNewEnd, mpEnd);
        mpEnd -= (last - first);
        return first;
    }
};  // namespace eastl
}
struct Elem16Vector {
    Elem16_s0061_3240* mpBegin;
    Elem16_s0061_3240* mpEnd;
    Elem16_s0061_3240* mpCapacity;
    eastl::fixed_vector_allocator mAllocator;
    eastl::MapCompare mCompare;  // +0x14

    Elem16Vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~Elem16Vector();
    Elem16_s0061_3240* DoAllocate(size_t n) { return n ? (Elem16_s0061_3240*)mAllocator.allocate(n * sizeof(Elem16_s0061_3240)) : 0; }
    void DoInsertValue(Elem16_s0061_3240* position, const Elem16_s0061_3240& value);       // 0x006133b0
    Elem16_s0061_3240* insert(Elem16_s0061_3240* position, const Elem16_s0061_3240& value);           // 0x006139a0
    Elem16_s0061_3240* insertHint(Elem16_s0061_3240* hint, const Elem16_s0061_3240& value);           // 0x00613bf0
    size_t erase(const uint64_t& key);                                // 0x00613b10
    Elem16_s0061_3240* eraseRange(Elem16_s0061_3240* first, Elem16_s0061_3240* last);                  // 0x006130e0
    IRefObj** FindOrInsert(const uint64_t& key);                     // 0x00613dd0
};
Elem16_s0061_3240* Elem16Vector::eraseRange(Elem16_s0061_3240* first, Elem16_s0061_3240* last) {
    Elem16_s0061_3240* const pNewEnd = CopyElem16(last, mpEnd, first);
    for (Elem16_s0061_3240* p = pNewEnd; p < mpEnd; ++p) p->~Elem16_s0061_3240();
    mpEnd -= (last - first);
    return first;
}
struct RefCountBase_s0061_3240 {
    virtual int AddRef();
    virtual int Release();
    virtual ~RefCountBase_s0061_3240() {}
    volatile long mRefCount;
    RefCountBase_s0061_3240() { _InterlockedExchange(&mRefCount, 0); }
};
struct PropertyBagBase_s0061_3240 : public RefCountBase_s0061_3240 {
    uint32_t pad8, padC, pad10, pad14;
    uint64_t mId;
    PropertyBagBase_s0061_3240(uint64_t id) : pad8(0), padC(0), pad10(0), pad14(0), mId(id) {}
};
struct PropMap {
    eastl::PropVector_s0061_3240 mVec;      // +0x00
    char pad14[4];
    char mBuffer[0xf0];          // +0x18
    eastl::MapCompare mCompare;  // +0x108

    PropMap() {
        mVec.mpBegin = mVec.mpEnd = (PropPair_s0061_3240*)(mVec.mAllocator.mpPoolBegin = mBuffer);
        mVec.mpCapacity = (PropPair_s0061_3240*)((char*)mVec.mpBegin + 0xf0);
    }
    EA::Variant_s0061_3240& operator[](const uint32_t& key);             // 0x00613d20
    PropPair_s0061_3240* insertHint(PropPair_s0061_3240* hint, const PropPair_s0061_3240& value);  // 0x00613b90
    ~PropMap() {
        mVec.DestructRangeV(mVec.mpBegin, mVec.mpEnd);
        if (mVec.mpBegin && mVec.mpBegin != mVec.mAllocator.mpPoolBegin) EASTL_allocator_deallocate(mVec.mpBegin);
    }
    const PropPair_s0061_3240* find(const uint32_t& key) const {
        const PropPair_s0061_3240* const itEnd = mVec.mpEnd;
        const PropPair_s0061_3240* it = LowerBound(mVec.mpBegin, itEnd, key, mCompare);
        if (it != itEnd && !(key < it->first)) return it;
        return itEnd;
    }
};
struct cPropertyBag_s0061_3240 : public PropertyBagBase_s0061_3240 {
    PropMap mMap;  // +0x20
    char pad12c[4];
    cPropertyBag_s0061_3240();  // 0x00613530
    bool GetFloat(uint32_t key, float* pOut);     // 0x006135d0
    bool GetInt32(uint32_t key, int32_t* pOut);   // 0x00613660
};
struct MsgHandle {
    void* a;
    void* b;
    void* c;
    void* d;
    void* e;
    MsgHandle() : a(0), b(0), c(0), d(0), e(0) {}
    ~MsgHandle() { Reset(); }
    void Reset() {
        if (a) {
            void* const pa = a;
            a = 0;
            EA::Messaging::RemoveHandler(pa, b, c, d, e);
        }
    }
};
struct FixedUIntSet {
    uint32_t* mpBegin;   // +0x1c
    uint32_t* mpEnd;     // +0x20
    uint32_t* mpCapacity;// +0x24
    const char* mpName;  // +0x28
    void* mpPoolBegin;   // +0x2c
    char pad[4];         // +0x30
    uint32_t mBuffer[20];// +0x34
    eastl::MapCompare mCompare;  // +0x84

    FixedUIntSet() {
        mpBegin = mpEnd = (uint32_t*)(mpPoolBegin = mBuffer);
        mpCapacity = mpBegin + 20;
    }
    void DoInsertValue(uint32_t* position, const uint32_t& value);  // 0x0060a600
    bool contains(uint32_t key) const {
        const uint32_t* const itEnd = mpEnd;
        const uint32_t* it = LowerBoundSet(mpBegin, itEnd, &key, mCompare);
        if (it == itEnd || key < *it) it = itEnd;
        else if (it == it + 1) it = itEnd;
        return it != itEnd;
    }
    __forceinline void insert(uint32_t key) {
        uint32_t* const pEnd = mpEnd;
        const uint32_t* it = LowerBoundSet(mpBegin, pEnd, &key, mCompare);
        if (it != pEnd && !(key < *it)) return;
        if (it == pEnd && pEnd != mpCapacity) {
            uint32_t* const p = mpEnd;
            mpEnd = p + 1;
            if (p) *p = key;      // the original skips the store when the (null) begin is the write slot
        } else {
            DoInsertValue((uint32_t*)it, key);
        }
    }
    void erase(uint32_t* pFirst, uint32_t* pLast) {
        memcpy(pFirst, pLast, (size_t)((char*)mpEnd - (char*)pLast));
        mpEnd -= (pLast - pFirst);
    }
    void clear() { erase(mpBegin, mpEnd); }
    ~FixedUIntSet() {
        if (mpBegin && mpBegin != mpPoolBegin) EASTL_allocator_deallocate(mpBegin);
    }
};
struct Elem16VectorD_s0061_3240 {
    Elem16_s0061_3240* mpBegin;
    Elem16_s0061_3240* mpEnd;
    ~Elem16VectorD_s0061_3240();  // 0x00612d10
};
inline Elem16Vector::~Elem16Vector() { ((Elem16VectorD_s0061_3240*)this)->~Elem16VectorD_s0061_3240(); }
struct cMessageBase {
    virtual ~cMessageBase() {}
};
struct cListenerSet : public cMessageBase {
    MsgHandle mHandle;       // +4
    uint32_t mField18;
    FixedUIntSet mSet;       // +0x1c
    Elem16Vector mListeners; // +0x88

    cListenerSet();                               // 0x00613790
    void DestroyBody();                           // 0x006137e0
    void Shutdown();                              // 0x00613a10
    bool HandleMessage(char* pMsg);               // 0x00613c60
    bool contains(uint32_t key);                  // 0x00613860
    void insertKey(uint32_t key);                 // 0x00613ab0
};
struct cStreamReader {
    EA::IO::IStream_s0061_3240* mpStream;
    int mEndian;
    bool mbOk;
    char pad[7];
    cStreamReader(EA::IO::IStream_s0061_3240* pStream, bool bBigEndian);  // 0x006b4f60
    void Accumulate(bool bResult);                              // 0x006b4f90
    void ReadVariant(EA::Variant_s0061_3240* v);                           // 0x006b4fd0
    ~cStreamReader();                                           // 0x006b5000
};
struct cPropertyReader {
    bool Read(EA::IO::IStream_s0061_3240* pStream, cPropertyBag_s0061_3240* pBag);
};
// ---- items of slice s00613240 end

// ---- items of slice s00614050 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int __cdecl wcscmp(const wchar_t*, const wchar_t*);
#pragma intrinsic(wcscmp)
typedef unsigned int size_type;
typedef unsigned __int64 u64;
void EASTL_free(void* p);
void* PollNew(unsigned size, const char* name, int a, int b, int c, int d);   // 0x00f473a0
void* operator new(unsigned size, const char* name, int a, int b, int c, int d);   // 0x00926020 (ZoneObject::operator new)
struct ResourceKey { uint32_t instanceID, typeID, groupID; };
struct IRefCounted {
    virtual int AddRef();
    virtual int Release();
    virtual int slot8();
    virtual void* Cast(uint32_t typeID);
};
template <typename T> struct RefPtrNI {   // AutoRefCount whose operator= stays out of line (0x00b5f950)
    T* p;
    RefPtrNI() : p(0) {}
    __declspec(noinline) RefPtrNI& operator=(T* o) {
        if (o != p) {
            T* t = p;
            if (o) o->AddRef();
            p = o;
            if (t) t->Release();
        }
        return *this;
    }
};
template <typename T> struct RefPtr {
    T* p;
    RefPtr() : p(0) {}
    RefPtr(T* o) : p(o) { if (p) p->AddRef(); }
    __declspec(noinline) RefPtr& operator=(const RefPtrNI<T>& x) { return operator=(x.p); }   // 0x00ac9480
    ~RefPtr() { if (p) p->Release(); }
    __forceinline RefPtr& operator=(T* o) {
        if (o != p) {
            T* t = p;
            if (o) o->AddRef();
            p = o;
            if (t) t->Release();
        }
        return *this;
    }
};
inline size_type CharStrlen(const wchar_t* s) {
    const wchar_t* p = s;
    while (*p) ++p;
    return (size_type)(p - s);
}
void* MemCopy(void* d, const void* s, size_type n);   // 0x011e0744 (memcpy thunk)
template <typename T> inline const T& emin(const T& a, const T& b) { return (b < a) ? b : a; }
struct string16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    int mAllocator;
    string16() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    string16(const string16& x) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(x.mpBegin, x.mpEnd); }
    static wchar_t* CharStringUninitializedCopy(const wchar_t* pFirst, const wchar_t* pLast, wchar_t* pResult) {
        MemCopy(pResult, pFirst, (pLast - pFirst) * 2);
        return pResult + (pLast - pFirst);
    }
    void RangeInitialize(const wchar_t* pBegin, const wchar_t* pEnd) {
        const size_type n = (size_type)(pEnd - pBegin);
        AllocateSelf(n + 1);
        mpEnd = CharStringUninitializedCopy(pBegin, pEnd, mpBegin);
        *mpEnd = 0;
    }
    ~string16() {
        if ((mpCapacity - mpBegin) > 1) {
            if (mpBegin) EASTL_free(mpBegin);
        }
    }
    void AllocateSelf(size_type n);                      // 0x00429760
    string16& erase(size_type position, size_type n);   // 0x004228e0
    size_type find_first_not_of(const wchar_t* p, size_type pos) const;   // 0x00579af0
    void resize(size_type n);                            // 0x00429520
    void append(const wchar_t* b, const wchar_t* e);     // 0x00429580
    void RangeInitialize(const wchar_t* p);              // 0x00579a90 (string(const wchar_t*))
    static int Compare(const wchar_t* a, const wchar_t* b, size_type n) {
        for (; n > 0; ++a, ++b, --n)
            if (*a != *b) return (*a < *b) ? -1 : 1;
        return 0;
    }
    __forceinline int compare(const wchar_t* p) const {
        const wchar_t* pEnd2 = p + CharStrlen(p);
        const int n1 = (int)(mpEnd - mpBegin);
        const int n2 = (int)(pEnd2 - p);
        const int nMin = emin(n1, n2);
        const int c = Compare(mpBegin, p, nMin);
        return c ? c : (n1 < n2 ? -1 : (n1 > n2 ? 1 : 0));
    }
    int compare(const string16& x) const;
    int compare_out(const wchar_t* p) const;   // out-of-line compare(const wchar_t*) at 0x00614950
};
int StringCompare(const wchar_t* b1, const wchar_t* e1, const wchar_t* b2, const wchar_t* e2);  // 0x005e9260
inline int string16::compare(const string16& x) const { return StringCompare(mpBegin, mpEnd, x.mpBegin, x.mpEnd); }
inline bool operator<(const string16& a, const string16& b) { return a.compare(b) < 0; }
struct IKeyFilter;
template <typename T> struct KeyVec { T* mpBegin; T* mpEnd; T* mpCapacity; };
struct IResourceManager {
    virtual ~IResourceManager();
    virtual bool Initialize();
    virtual bool Dispose();
    virtual bool GetResource(const ResourceKey* key, RefPtr<IRefCounted>* dst, void* a, void* b, void* c, void* d);  // 0x0c
    virtual bool GetResourceAsync();
    virtual bool GetLoadedResource(const ResourceKey* key, RefPtr<IRefCounted>* dst);                                 // 0x14
    virtual bool ReloadResource();
    virtual bool GetPrivateResource();
    virtual bool WriteResource(IRefCounted* res, void* data, void* db, void* factory, void* name);                    // 0x20
    virtual void SetTypeMapping();
    virtual int GetRecordTypesFromResourceType();
    virtual int GetTypeMapping();
    virtual int FindRecord();
    virtual int GetResourceKeyList();
    virtual int GetRecordKeyList(KeyVec<ResourceKey>* dst, IKeyFilter* filter, void* dbs);                            // 0x38
    virtual int GetRecordKeyList2();
    virtual bool RegisterChangeNotification();
    virtual bool RegisterFactory(bool add, struct IFactory* factory, int arg);                                            // 0x44
    virtual int FindFactory();
    virtual int GetFactoryList();
    virtual bool RegisterDatabase();
    virtual bool IsDatabaseRegistered();
    virtual int FindDatabase();
    virtual int GetDatabaseList();
    virtual void DoDatabaseChanged();
    virtual bool RegisterCache();
    virtual int FindCache();
    virtual bool CacheResource(IRefCounted* res, bool flag);                                                          // 0x6c
};
IResourceManager* GetManager();   // 0x0067dcd0 (EA::ResourceMan::GetManager)
struct IKeyFilter { virtual bool Accept(const ResourceKey*); };
struct cAssetDirectory {
    char pad[0];
    bool GetLocalKey(u64 id, ResourceKey* out);                 // 0x0054e460
    bool HasAsset(u64 id);                                      // 0x0054e740
    bool GetServerId(const ResourceKey* key, u64* out, bool b); // 0x0054e530
};
struct cPollinator {
    char pad[0x58];
    cAssetDirectory* mpAssetDirectory;
};
cPollinator* GetPollinator();   // 0x0067cb30
struct cPollenAssetData {
    char mData[0x130 - 0x20];
    void SetData(uint32_t a, uint32_t b, void* c);   // 0x00613140
};
struct cPollenAsset : IRefCounted {
    int mnRef;                      // +4
    ResourceKey mKey;               // +8
    int pad14;
    u64 mId;                        // +0x18
    u64 GetId() const { return mId; }
    cPollenAssetData mData;         // +0x20
    cPollenAsset(u64 id);           // 0x00612f00
    static void* operator new(size_t n, const char* name, int a, int b, int c, int d);   // 0x00f473a0
};
void* GetSaveArea(uint32_t id);    // SP::GetSaveArea 0x006b1f90
struct AssetEntry {
    u64 key;
    RefPtr<cPollenAsset> value;
    int pad;
};
struct AssetMap {
    AssetEntry* mpBegin;
    AssetEntry* mpEnd;
    char pad[0x14 - 8];
    bool mbFlag;                                   // +0x14 (== cache +0x9c)
    RefPtr<cPollenAsset>* operator_index(const u64& key);   // 0x00613dd0
    AssetEntry* find(const u64& key);
};
AssetEntry* lower_bound_asset(AssetEntry* b, AssetEntry* e, const u64* key, bool flag);   // 0x007c8160
struct AssetRange { AssetEntry* first; AssetEntry* second; };
inline AssetEntry* AssetMap::find(const u64& key) {
    AssetRange r;
    AssetEntry* const itEnd = mpEnd;
    AssetEntry* it = lower_bound_asset(mpBegin, itEnd, &key, mbFlag);
    if (it != itEnd && !(key < it->key)) {
        r.first = it;
        r.second = it + 1;
    } else {
        r.first = it;
        r.second = it;
    }
    return (r.first != r.second) ? r.first : itEnd;
}
struct IMessageServer {
virtual int slot00();
virtual int slot04();
virtual int slot08();
virtual int slot0c();
    virtual int slot10();
    virtual bool PostMessage(uint32_t id, void* data, int flag);   // 0x14
virtual int slot18();
virtual int slot1c();
virtual int slot20();
    virtual bool AddListener(void* listener, uint32_t id);          // 0x24
};
struct cAssetCache {
    void* vtbl;                     // +0
    IMessageServer* mpServer;       // +4
    cAssetCache* mpSelf;            // +8
    const uint32_t* mpMessages;     // +0xc
    int mnMessages;                 // +0x10
    int mnZero;                     // +0x14
    cPollinator* mpPollinator;      // +0x18
    char pad1c[0x88 - 0x1c];
    AssetMap mMap;                  // +0x88

    void LoadAll();                                      // 0x00614050
    void AddAsset(u64 id, const void* data);             // 0x00614280
    bool RemoveAsset(u64 id);                            // 0x006144c0
    bool Fn613c60(cPollenAsset* a);                      // 0x00613c60
    bool Fn613e50(uint32_t a, cPollenAsset* b);          // 0x00613e50
    void Fn613ab0(uint32_t a);                           // 0x00613ab0
    bool ReadRecord(void* rec, struct cPollenAsset* obj, uint32_t unused, uint32_t type);   // 0x00614560
    void Init(cPollinator* pollinator);                  // 0x006145d0
    bool HandleMessage(uint32_t id, void* msg);          // 0x006146c0
};
struct IRecord {
virtual int slot00();
virtual int slot04();
virtual int slot08();
virtual int slot0c();
    virtual const ResourceKey* GetKey();    // 0x10
    virtual int slot14();
    virtual uint32_t GetSize();             // 0x18
};
struct IFactory { virtual void slot0(); virtual int AddRef(); virtual int Release(); };
void cAssetCache::AddAsset(u64 id, const void* data)
{
    cPollenAsset* a;
    RefPtrNI<cPollenAsset> e;
    AssetEntry* it = mMap.find(id);
    if (it != mMap.mpEnd) {
        a = it->value.p;
        if (!a) return;
        a->AddRef();
    } else {
        ResourceKey lk = { 0, 0, 0 };
        if (!GetPollinator()->mpAssetDirectory->GetLocalKey(id, &lk)) return;
        if (!GetPollinator()->mpAssetDirectory->HasAsset(id)) {
            if (!GetManager()->GetResource(&lk, 0, 0, 0, 0, 0)) return;
        }
        ResourceKey key = { lk.instanceID, 0xfd60f0c1, lk.groupID };
        RefPtr<IRefCounted> res;
        IResourceManager* mgr = GetManager();
        res = 0;
        if (mgr->GetLoadedResource(&key, &res)) {
            if (res.p)
                e = (cPollenAsset*)res.p->Cast(0xaaff1cde);
            else
                e = 0;
            a = e.p;
        } else {
            e = new ("Pollinator", 0, 0, 0, 0) cPollenAsset(id);
            a = e.p;
            a->mKey = key;
            RefPtr<cPollenAsset>* slot = mMap.operator_index(id);
            *slot = e;
        }
    }
    if (a) {
        a->mData.SetData(((uint32_t*)data)[0], ((uint32_t*)data)[1], (void*)data);
        void* area = GetSaveArea(0x11ac19d);
        GetManager()->WriteResource(a, 0, area, 0, 0);
        GetManager()->CacheResource(a, true);
        a->Release();
    }
}
// ---- items of slice s00614050 end

// @ 0x00612ba0
bool cPropertyListWriter::Write(EA::IO::IStream_s0061_2270* pStream, const cPropertyBag* pBag)
{
    cStreamWriter w(pStream, true);
    uint32_t version = 3;
    if (w.mbOk) w.Accumulate(EA::IO::WriteUint32(w.mpStream, &version, 1, w.mEndian));
    uint64_t id = *(const uint64_t*)&pBag->mField18;
    if (w.mbOk) w.Accumulate(EA::IO::WriteUint64(w.mpStream, &id, 1, w.mEndian));
    uint32_t count = (uint32_t)(pBag->mpEnd - pBag->mpBegin);
    if (w.mbOk) w.Accumulate(EA::IO::WriteUint32(w.mpStream, &count, 1, w.mEndian));
    for (const PropPair* it = pBag->mpBegin; it != pBag->mpEnd; ++it) {
        PropPair tmp;
        tmp = *it;
        if (w.mbOk) w.Accumulate(EA::IO::WriteUint32(w.mpStream, &tmp.first, 1, w.mEndian));
        w.WriteVariant(&tmp.second);
    }
    return w.mbOk;
}

// @ 0x00612d10
void DestroyElem16VectorD(Elem16VectorD* v)
{ v->~Elem16VectorD(); }

// @ 0x00612d50
__declspec(noinline) PropPair* UninitializedCopy(const PropPair* first, const PropPair* last, PropPair* dest)
{
    for (; first != last; ++first, ++dest) ::new (dest) PropPair(*first);
    return dest;
}

// @ 0x00612db0
const PropPair* LowerBound(const PropPair* first, const PropPair* last, const uint32_t& value)
{
    int length = (int)(last - first);
    while (length > 0) {
        const int half = length >> 1;
        const PropPair* const middle = first + half;
        if (middle->first < value) {
            first = middle;
            ++first;
            length = length - half - 1;
        } else {
            length = half;
        }
    }
    return first;
}

// @ 0x00612e50
bool cPropertyListWriter::WriteResource(void* pObject, void* pStreamHolder, int, uint32_t typeId)
{
    IObjectLike* pObj = (IObjectLike*)pObject;
    if (typeId == 0xfd60f0c1 && pObj) {
        cPropertyBag* pBag = pObj->Cast(0xaaff1cde);
        if (pBag) {
            if (Write(((IStreamHolder*)pStreamHolder)->GetStream(), pBag)) return true;
        }
    }
    return false;
}

// @ 0x00613020
void eastl::PropVector::reserve(size_t n)
{
    if (n > (size_t)(mpCapacity - mpBegin)) {
        PropPair* const pNewData = n ? (PropPair*)mAllocator.allocate(n * sizeof(PropPair)) : 0;
        PropPair* const pOldEnd = mpEnd;
        PropPair* const pOldBegin = mpBegin;
        UninitializedCopy(pOldBegin, pOldEnd, pNewData);
        DestructRange(pOldBegin, pOldEnd, pNewData);
        if (mpBegin) mAllocator.deallocate(mpBegin);
        mpEnd = pNewData + (mpEnd - mpBegin);
        mpBegin = pNewData;
        mpCapacity = pNewData + n;
    }
}

// @ 0x00613240
void eastl::PropVector_s0061_3240::DoInsertValue(PropPair_s0061_3240* position, const PropPair_s0061_3240& value)
{
    if (mpEnd != mpCapacity) {
        const PropPair_s0061_3240* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd)) ++pValue;
        ::new (mpEnd) PropPair_s0061_3240(*(mpEnd - 1));
        CopyBackward(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
    } else {
        const size_t nPrevSize = (size_t)(mpEnd - mpBegin);
        const size_t nNewSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
        PropPair_s0061_3240* const pNewData = DoAllocate(nNewSize);
        PropPair_s0061_3240* pNewEnd = RelocatePairs(mpBegin, position, pNewData);
        ::new (pNewEnd) PropPair_s0061_3240(value);
        ++pNewEnd;
        pNewEnd = RelocatePairs(position, mpEnd, pNewEnd);
        if (mpBegin && mpBegin != mAllocator.mpPoolBegin) EASTL_allocator_deallocate(mpBegin);
        mpEnd = pNewEnd;
        mpBegin = pNewData;
        mpCapacity = pNewData + nNewSize;
    }
}

// @ 0x006135d0
bool cPropertyBag_s0061_3240::GetFloat(uint32_t key, float* pOut)
{
    const PropPair_s0061_3240* const itEnd = mMap.mVec.mpEnd;
    const PropPair_s0061_3240* it = LowerBound(mMap.mVec.mpBegin, itEnd, key, mMap.mCompare);
    if (it == itEnd || key < it->first) it = itEnd;
    else if (it == it + 1) it = itEnd;
    if (it != itEnd) {
        if (pOut) {
            const EA::Variant_s0061_3240& v = it->second;
            if (v.mTypeId == 0xd || v.mTypeId == 0x10) {
                if (v.mFlags & 0x30)
                    *pOut = **(float**)v.mData;
                else
                    *pOut = *(const float*)(v.mTypeId ? (const void*)v.mData : 0);
            } else {
                *pOut = kDefaultFloat;
            }
        }
        return true;
    }
    return false;
}

// @ 0x00613660
bool cPropertyBag_s0061_3240::GetInt32(uint32_t key, int32_t* pOut)
{
    const PropPair_s0061_3240* const itEnd = mMap.mVec.mpEnd;
    const PropPair_s0061_3240* it = LowerBound(mMap.mVec.mpBegin, itEnd, key, mMap.mCompare);
    if (it == itEnd || key < it->first) it = itEnd;
    else if (it == it + 1) it = itEnd;
    if (it != itEnd) {
        if (pOut) {
            const EA::Variant_s0061_3240& v = it->second;
            if (v.mTypeId == 9 || v.mTypeId == 0x10) {
                if (v.mFlags & 0x30)
                    *pOut = **(int**)v.mData;
                else
                    *pOut = *(const int*)(v.mTypeId ? (const void*)v.mData : 0);
            } else {
                *pOut = kDefaultInt;
            }
        }
        return true;
    }
    return false;
}

// @ 0x006137e0
void cListenerSet::DestroyBody()
{
    mListeners.~Elem16Vector();
    mSet.~FixedUIntSet();
    mHandle.~MsgHandle();
    this->cMessageBase::~cMessageBase();
}

// @ 0x00613d20
EA::Variant_s0061_3240& PropMap::operator[](const uint32_t& key)
{
    const PropPair_s0061_3240* const itEnd = mVec.mpEnd;
    const PropPair_s0061_3240* it = LowerBound(mVec.mpBegin, itEnd, key, mCompare);
    if (it == itEnd || key < it->first) {
        it = insertHint((PropPair_s0061_3240*)it, PropPair_s0061_3240(key, EA::Variant_s0061_3240()));
    }
    return ((PropPair_s0061_3240*)it)->second;
}

// @ 0x00613e50
bool cPropertyReader::Read(EA::IO::IStream_s0061_3240* pStream, cPropertyBag_s0061_3240* pBag)
{
    cStreamReader r(pStream, true);
    int32_t version = 0;
    if (r.mbOk) r.Accumulate(EA::IO::ReadInt32(r.mpStream, &version, 1, r.mEndian));
    if (!r.mbOk || (uint32_t)version < 3) return false;
    if (r.mbOk) r.Accumulate(EA::IO::ReadUint64(r.mpStream, &pBag->mId, 1, r.mEndian));
    int32_t count = 0;
    if (r.mbOk) r.Accumulate(EA::IO::ReadInt32(r.mpStream, &count, 1, r.mEndian));
    if (!r.mbOk) return false;
    pBag->mMap.mVec.reserve((size_t)count);
    for (uint32_t i = 0; i < (uint32_t)count; ++i) {
        uint32_t key = 0;
        EA::Variant_s0061_3240 v;
        *(int*)v.mData = 0;
        v.mTypeId = 9;
        v.mFlags = 0;
        if (r.mbOk) r.Accumulate(EA::IO::ReadInt32(r.mpStream, (int32_t*)&key, 1, r.mEndian));
        r.ReadVariant(&v);
        if (!r.mbOk) goto fail;
        pBag->mMap[key].Assign(v);
    }
    if (r.mbOk) return true;
fail:
    pBag->mMap.mVec.erase(pBag->mMap.mVec.mpBegin, pBag->mMap.mVec.mpEnd);
    return false;
}

// @ 0x00614280
inline void* cPollenAsset::operator new(size_t n, const char* name, int a, int b, int c, int d)
{
    return PollNew((unsigned)n, name, a, b, c, d);
}

// @ 0x00614560
bool cAssetCache::ReadRecord(void* rec, cPollenAsset* obj, uint32_t unused, uint32_t type)
{
    if (type == 0xfd60f0c1 && obj) {
        cPollenAsset* a = (cPollenAsset*)obj->Cast(0xaaff1cde);
        if (a) {
            IRecord* r = (IRecord*)rec;
            if (Fn613e50(r->GetSize(), a)) {
                const ResourceKey* k = r->GetKey();
                obj->mKey = *k;
                return true;
            }
        }
    }
    return false;
}

// @ 0x006a14d0
void SP::cPropertyList::DeepCopy(SP::cPropertyList * src)
{
  if (this == src) return;
  cPropertyList* old = mParent.mpObject;
  if (old) {
    mParent.mpObject = 0;
    old->Release();
  }
  ClearProperties();
  DeepAdd(src);
}

// @ 0x006a1510
void SP::cPropertyList::DeepAdd(SP::cPropertyList * src)
{
  if (src->mParent.mpObject) DeepAdd(src->mParent.mpObject);
  Add(src);
}

// @ 0x006a1540
bool SP::cPropertyList_s006a_11b0::Write(EA::IO::IStream_s006a_11b0* stream) const
{
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

// @ 0x006a1600
void SP::cDirectPropertyList::Add(SP::cPropertyList * src)
{
  if (this == src) return;
  eastl::pair<unsigned int, EA::Variant>* it = src->mPropertyMap.mpBegin;
  eastl::pair<unsigned int, EA::Variant>* end = src->mPropertyMap.mpEnd;
  for (; it != end; ++it) {
    SetProperty(it->first, it->second);
  }
  mModificationCount++;
}

// @ 0x006a1a70
VariantPair* PairsUninitMoveStart(VariantPair** dest, VariantPair* first, VariantPair* last, VariantPair* out)
{
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

// @ 0x006a1b00
VariantPair* PairsFillN(VariantPair* dest, unsigned int n, const VariantPair& value)
{
  uint32_t result = 0xffffffffu;
  for (; n != 0; --n, ++dest) {
    if (dest) {
      dest->first = value.first;
      dest->second.mFlags = 0;
      dest->second.mTypeId = 0;
      VariantAssignCopy(&dest->second, 0, value.second);
      result = (uint32_t)&dest->second;
    }
  }
  return (VariantPair*)result;
}

// @ 0x006a1b90
SP::cPropertyList::cPropertyList(char const * name)

: SP::cResourceBase(), mParent(), mModificationCount(0) {}

// @ 0x006a1bd0
SP::cDirectPropertyList_s006a_11b0::~cDirectPropertyList_s006a_11b0()
{
  EA::Allocator::ZoneObject_s006a_11b0::operator delete(mDirectProps); // 0x00f47380
}

// @ 0x006a1c40
SP::cPropertyList::cPropertyList()

: SP::cResourceBase(), mParent(), mModificationCount(0) {}

// @ 0x006a1ca0
SP::cDirectPropertyList::cDirectPropertyList(int count)

: SP::cPropertyList(), mNumDirectProps(0), mDirectProps(0) {
  if (count) {
    mNumDirectProps = count;
    mDirectProps = new ("App/cDirectPropertyList", 0, 0, 0, 0) int[count];
    Memset32(mDirectProps, 0, mNumDirectProps);
  }
}

// @ 0x006a1de0
namespace SP {
bool cPropertyList_s006a_11b0::GetPropertyA(unsigned int key, EA::Variant_s006a_11b0** out)
{
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
}  // namespace SP

// @ 0x006a1e50
bool SP::cDirectPropertyList::GetProperty(unsigned int key, EA::Variant ** out)
{
  if (key < mNumDirectProps) {
    *out = ((EA::Variant *)&GetProperty(key));
    return true;
  }
  return cPropertyList::GetProperty(key, out);
}

// @ 0x006a1e80
eastl::pvector& eastl::pvector::operator=(const eastl::pvector& x)
{
  if (this == &x) return *this;

  const unsigned int n = x.size();

  if (n > capacity()) {
    VariantPair* p = PairsRealloc(this, 0, n, x.mpBegin, x.mpEnd);
    PairsDestroy(this, 0, mpBegin, mpEnd);
    if (mpBegin) EA::Allocator::ZoneObject_s006a_11b0::operator delete(mpBegin);
    mpCapacity = p + n;
    mpBegin = p;
    mpEnd = p + n;
    return *this;
  }

  const unsigned int cur = size();
  if (n > cur) {
    UninitializedCopyPairs(x.mpBegin, x.mpBegin + cur, mpBegin);
    VariantPair* dest = mpEnd;
    PairsUninitMoveStart(&dest, x.mpBegin + cur, x.mpEnd, mpEnd);
    mpEnd = mpBegin + n;
    return *this;
  }

  UninitializedCopyPairs(x.mpBegin, x.mpEnd, mpBegin);
  PairsDestroy(this, 0, mpBegin + n, mpEnd);
  mpEnd = mpBegin + n;
  return *this;
}

// @ 0x006a2010
void eastl::pvector::DoInsertValues(VariantPair* position, unsigned int n, const VariantPair& value)
{
  if (n == 0) return;

  const unsigned int idx = (unsigned int)(position - mpBegin);
  const unsigned int cur = size();

  // Complete (reallocating) insertion: build the new sequence in a fresh buffer.
  const unsigned int newCap = cur + n;
  VariantPair* p = PairsRealloc(this, 0, newCap, mpBegin, mpEnd);
  VariantPair* dest = p;
  PairsUninitMoveStart(&dest, mpBegin, mpBegin + idx, p);
  PairsFillN(p + idx, n, value);
  VariantPair* dest2 = p + idx + n;
  PairsUninitMoveStart(&dest2, mpBegin + idx, mpEnd, p + idx + n);
  PairsDestroy(this, 0, mpBegin, mpEnd);
  if (mpBegin) EA::Allocator::ZoneObject_s006a_11b0::operator delete(mpBegin);
  mpBegin = p;
  mpEnd = p + cur + n;
  mpCapacity = p + newCap;
}

// @ 0x006a22a0
void eastl::pvector_s006a_22a0::DoInsertValue(VariantPair_s006a_22a0* position, const VariantPair_s006a_22a0& value)
{
  if (mpEnd != mpCapacity) {
    PairsMoveBack(mpEnd + 1, position, mpEnd);
    *position = value;
    mpEnd = mpEnd + 1;
    return;
  }
  unsigned int n = (unsigned int)(position - mpBegin);
  unsigned int cur = (unsigned int)(mpEnd - mpBegin);
  unsigned int newCap = cur ? cur * 2 : 1;
  VariantPair_s006a_22a0* p = PairsAllocate(newCap);
  PairsCopy(p, mpBegin, position);
  p[n] = value;
  PairsCopy(p + n + 1, position, mpEnd);
  PairsDestroy_s006a_22a0(mpBegin, mpEnd);
  if (mpBegin) EA::Allocator::ZoneObject_s006a_22a0::operator delete(mpBegin);
  mpBegin = p;
  mpEnd = p + cur + 1;
  mpCapacity = p + newCap;
}

// @ 0x006a2470
bool SP::cPropertyList::HasProperty(unsigned int key) const
{
  eastl::pair<unsigned int,EA::Variant>* end = mPropertyMap.mpEnd;
  eastl::pair<unsigned int,EA::Variant>* it = eastl::lower_bound(mPropertyMap.mpBegin, end, &key, (*(unsigned char *)&mPropertyMap.mCompare));
  if (it == end || key < it->first)
    it = end;
  else if (it == it + 1)
    it = end;
  if (it != end) return true;
  if (mParent.mpObject) return mParent.mpObject->HasProperty(key);
  return false;
}

// @ 0x006a24d0
EA::Variant_s006a_22a0* SP::cPropertyList_s006a_22a0::GetPropertyValue(unsigned int key) const
{
  VariantPair_s006a_22a0* end = mPropertyMap.mpEnd;
  VariantPair_s006a_22a0* it = eastl::lower_bound_s006a_22a0(mPropertyMap.mpBegin, end, &key, mPropertyMap.mCompare);
  if (it == end || key < it->first)
    it = end;
  else if (it == it + 1)
    it = end;
  if (it != end) return &it->second;
  if (mParent) return mParent->GetPropertyValue(key);
  return &g_sNullVariant;
}

// @ 0x006a2530
bool SP::cPropertyList::GetProperty(unsigned int key, EA::Variant const ** out) const
{
  eastl::pair<unsigned int,EA::Variant>* end = mPropertyMap.mpEnd;
  eastl::pair<unsigned int,EA::Variant>* it = eastl::lower_bound(mPropertyMap.mpBegin, end, &key, (*(unsigned char *)&mPropertyMap.mCompare));
  if (it == end || key < it->first)
    it = end;
  else if (it == it + 1)
    it = end;
  if (it != end) {
    *out = &it->second;
    return true;
  }
  if (mParent.mpObject) return mParent.mpObject->GetProperty(key, out);
  return false;
}

// @ 0x006a25a0
bool SP::cDirectPropertyList_s006a_22a0::GetDescription(unsigned int key) const
{
  if (key < mNumDirectProps) return mDirectProps[key] != 0;
  VariantPair_s006a_22a0* end = mPropertyMap.mpEnd;
  VariantPair_s006a_22a0* it = eastl::lower_bound_s006a_22a0(mPropertyMap.mpBegin, end, &key, mPropertyMap.mCompare);
  if (it == end || key < it->first)
    it = end;
  else if (it == it + 1)
    it = end;
  if (it == end) return false;
  VariantBytes v;
  const VariantBytes* rv = (const VariantBytes*)((VariantOps*)&v)->ToStr(&it->second);
  const void* p = VariantData(rv, 1, 0x10, 0x15d115d);
  bool res = *(const bool*)p;
  if (v.mFlags & 4) ((EA::Variant_s006a_22a0*)&v)->Destruct(0);
  return res;
}

// @ 0x006a2660
int SP::cDirectPropertyList::GetIntProperty(unsigned int index) const
{
  if (index < mNumDirectProps) return mDirectProps[index];
  eastl::pair<unsigned int,EA::Variant>* end = mPropertyMap.mpEnd;
  eastl::pair<unsigned int,EA::Variant>* it = eastl::lower_bound(mPropertyMap.mpBegin, end, &index, (*(unsigned char *)&mPropertyMap.mCompare));
  if (it == end || index < it->first)
    it = end;
  else if (it == it + 1)
    it = end;
  if (it == end) return 0;
  VariantBytes v;
  const VariantBytes* rv = (const VariantBytes*)((VariantOps*)&v)->ToInt(&it->second);
  const void* p = VariantData(rv, 9, 0x10, 0x15d1160);
  int r = *(const int*)p;
  if (v.mFlags & 4) ((EA::Variant*)&v)->Destruct(0);
  return r;
}

// @ 0x006a2710
float SP::cDirectPropertyList::GetFloatProperty(unsigned int index) const
{
  if (index < mNumDirectProps) return ((float*)mDirectProps)[index];
  eastl::pair<unsigned int,EA::Variant>* end = mPropertyMap.mpEnd;
  eastl::pair<unsigned int,EA::Variant>* it = eastl::lower_bound(mPropertyMap.mpBegin, end, &index, (*(unsigned char *)&mPropertyMap.mCompare));
  if (it == end || index < it->first)
    it = end;
  else if (it == it + 1)
    it = end;
  if (it == end) return 0.0f;
  VariantBytes v;
  const VariantBytes* rv = (const VariantBytes*)((VariantOps*)&v)->ToFloat(&it->second);
  const void* p = VariantData(rv, 0xd, 0x10, 0x15d1168);
  float r = *(const float*)p;
  if (v.mFlags & 4) ((EA::Variant*)&v)->Destruct(0);
  return r;
}

// @ 0x006a27d0
bool SP::cDirectPropertyList::HasProperty(unsigned int key) const
{
  if (key != 0 && key < mNumDirectProps) return true;
  // The original keeps the inherited lookup as a real call (never a tail call) and returns a
  // full-width 0/1 (`mov eax,1` / `xor eax,eax`), not just a normalized `al`; widening the
  // callee's bool through a volatile int reproduces that.
  volatile int bInherited = cPropertyList::HasProperty(key);
  return bInherited != 0;
}

// @ 0x006a2800
EA::Variant_s006a_22a0 const& SP::cDirectPropertyList_s006a_22a0::GetProperty(unsigned int key) const
{
  if (key < mNumDirectProps) {
    EA::Variant_s006a_22a0* out = const_cast<EA::Variant_s006a_22a0*>(&mTempDirectVariant);
    void* mgr = PropertyManager();
    void* entry = (*(PropertyLookup*)(*(int*)mgr + 0x50))(mgr, 0, key);
    VariantCopyAssign(out, 0, (EA::Variant_s006a_22a0*)entry);
    if (!(out->mFlags & 0x10)) {
      if (out->mTypeId == 1)
        *out = (bool)(mDirectProps[key] != 0);
      else if (out->mTypeId == 9)
        *out = mDirectProps[key];
      else if (out->mTypeId == 0xd)
        *out = ((float*)mDirectProps)[key];
    }
    return mTempDirectVariant;
  }
  return *cPropertyList_s006a_22a0::GetPropertyValue(key);
}

// @ 0x006a28c0
bool SP::cDirectPropertyList::GetProperty(unsigned int key, EA::Variant const ** out) const
{
  if (key < mNumDirectProps) {
    *out = ((EA::Variant *)&GetProperty(key));
    return true;
  }
  return cPropertyList::GetProperty(key, out);
}

// @ 0x006a28f0
void SP::VariantMap::ClearMapOnly()
{
  PairsCopy(mpBegin, mpEnd, mpEnd);
  PairsDestroy_s006a_22a0(mpBegin, mpEnd);
  mpEnd = ShrinkEnd(mpBegin, mpEnd);
}

// @ 0x006a2940
VariantPair_s006a_22a0* eastl::pvector_s006a_22a0::insert(VariantPair_s006a_22a0* position, const VariantPair_s006a_22a0& value)
{
  VariantPair_s006a_22a0* beg = mpBegin;
  unsigned int idx = (unsigned int)(position - beg);
  if (position == mpEnd && mpEnd != mpCapacity) {
    VariantPair_s006a_22a0* e = mpEnd;
    mpEnd = e + 1;
    if (e) {
      e->first = value.first;
      e->second = value.second;
    }
  } else {
    DoInsertValue(position, value);
  }
  return mpBegin + idx;
}

// @ 0x006a2a80
void SP::cPropertyList_s006a_22a0::Clear()
{
  VariantMap* map = &mPropertyMap;
  PairsCopy(map->mpBegin, map->mpEnd, map->mpEnd);
  PairsDestroy_s006a_22a0(map->mpBegin, map->mpEnd);
  map->mpEnd = ShrinkEnd(map->mpBegin, map->mpEnd);
  mModificationCount++;
}

// @ 0x006a2ad0
void SP::cDirectPropertyList_s006a_22a0::Copy(cPropertyList_s006a_22a0* src)
{
  if (this == src) return;
  mPropertyMap.ClearMapOnly();
  VariantPair_s006a_22a0* it = src->mPropertyMap.mpBegin;
  VariantPair_s006a_22a0* end = src->mPropertyMap.mpEnd;
  for (; it != end; ++it) SetProperty(it->first, &it->second);
  SetParent(mParent);
}

// @ 0x006a2b20
void SP::cDirectPropertyList_s006a_22a0::Clear()
{
  Memset32(mDirectProps, 0, mNumDirectProps); // 0x0092cb00
  PairsDestroy_s006a_22a0(mPropertyMap.mpBegin, mPropertyMap.mpEnd);
  mPropertyMap.mpEnd = mPropertyMap.mpBegin;
}

// @ 0x006a2c50
VariantPair_s006a_22a0* SP::VariantMap::insert(VariantPair_s006a_22a0* out, const VariantPair_s006a_22a0& value)
{
  VariantPair_s006a_22a0* end = mpEnd;
  VariantPair_s006a_22a0* it = eastl::lower_bound_s006a_22a0(mpBegin, end, &value.first, mCompare);
  if (it == end || value.first < it->first)
    it = end;
  else if (it == it + 1)
    it = end;
  if (it != end) {
    out[0] = *it;
    ((unsigned char*)out)[4] = 0;
    return out;
  }
  *out = *insert_pos(it, value);
  ((unsigned char*)out)[4] = 1;
  return out;
}

// @ 0x006a2cb0
unsigned int SP::VariantMap::erase(const unsigned int& key)
{
  VariantPair_s006a_22a0* end = mpEnd;
  VariantPair_s006a_22a0* it = eastl::lower_bound_s006a_22a0(mpBegin, end, &key, mCompare);
  if (it == end || key < it->first)
    it = end;
  else if (it == it + 1)
    it = end;
  if (it == end) return 0;
  if (it + 1 < end) PairsCopy(it, it + 1, end);
  mpEnd = mpEnd - 1;
  mpEnd->~VariantPair_s006a_22a0();
  return 1;
}

// @ 0x006a2ef0
void SP::cPropertyList::RemoveProperty(unsigned int key)
{
  mPropertyMap.erase(key);
  mModificationCount++;
}

// @ 0x006a2f60
bool SP::cPropertyList_s006a_22a0::Read(EA::IO::IStream_s006a_22a0* stream)
{
  int nCount;
  bool bResult = EA::IO::ReadInt32(stream, &nCount, 1, 0);
  if (bResult && nCount < 0) {
    int key[3] = {0, 0, 0};
    bResult = EA::IO::ReadInt32(stream, key, 3, 0);
    void* mgr = PropertyManager();
    if (mParent) {
      cPropertyList_s006a_22a0* old = mParent;
      mParent = 0;
      old->Release();
    }
    (*(void(**)(void*, int, int, void**))(*(int*)mgr + 0x2c))(mgr, key[0], key[2],
                                                             (void**)&mParent);
  }
  unsigned int want = (unsigned int)nCount & 0x7fffffff;
  ((eastl::pvector_s006a_22a0*)&mPropertyMap)->resize(want);
  for (VariantPair_s006a_22a0* it = mPropertyMap.mpBegin; it != mPropertyMap.mpEnd; ++it) {
    if (!bResult) break;
    bResult = EA::IO::ReadInt32(stream, &it->first, 1, 0);
    if (bResult) bResult = WriteVariant(stream, &it->second, 0) != 0;
  }
  return bResult;
}

// @ 0x006a3070
unsigned int SP::cPropertyList_s006a_22a0::GetPropertyIDs(unsigned int* ids)
{
  UIntVector* v = (UIntVector*)ids;
  unsigned int n = (unsigned int)(mPropertyMap.mpEnd - mPropertyMap.mpBegin);
  v->resize(n);
  unsigned int i = 0;
  for (VariantPair_s006a_22a0* it = mPropertyMap.mpBegin; it != mPropertyMap.mpEnd; ++it) {
    v->mpBegin[i] = it->first;
    i++;
  }
  return (unsigned int)(size_t)mPropertyMap.mpEnd;
}

// @ 0x006a3180
unsigned int SP::cDirectPropertyList_s006a_22a0::GetPropertyIDs(unsigned int* ids)
{
  UIntVector* v = (UIntVector*)ids;
  PairsCopyBytes(v->mpBegin, v->mpEnd, 0);
  v->mpEnd = ShrinkUIntEnd(v->mpBegin, v->mpEnd);
  void* mgr = PropertyManager();
  for (unsigned int i = 1; i < mNumDirectProps; i++) {
    void* entry = (*(PropertyLookup*)(*(int*)mgr + 0x50))(mgr, 0, i);
    if (*(short*)((char*)entry + 0x12) != 0) {
      unsigned int* e = v->mpEnd;
      if (e < v->mpCapacity) {
        v->mpEnd = e + 1;
        if (e) *e = i;
      } else {
        v->DoInsertValue(e, i);
      }
    }
  }
  unsigned int mapN = (unsigned int)(mPropertyMap.mpEnd - mPropertyMap.mpBegin);
  unsigned int oldN = (unsigned int)(v->mpEnd - v->mpBegin);
  unsigned int total = oldN + mapN;
  if (total > oldN) {
    unsigned int zero = 0;
    v->DoInsertValues(v->mpEnd, total - oldN, zero);
  } else {
    unsigned int* dst = v->mpBegin + total;
    PairsCopyBytes(dst, v->mpEnd, 0);
    v->mpEnd = ShrinkUIntEnd(dst, v->mpEnd);
  }
  unsigned int k = oldN;
  for (VariantPair_s006a_22a0* it = mPropertyMap.mpBegin; it != mPropertyMap.mpEnd; ++it) {
    v->mpBegin[k] = it->first;
    k++;
  }
  return (unsigned int)(size_t)mPropertyMap.mpEnd;
}
