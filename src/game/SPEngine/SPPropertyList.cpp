// src/game/SPEngine/SPPropertyList.cpp -- migrated from slice(s) s00612270, s006a22a0, s006a11b0 by tools/migrate/rewrite.py
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

// ---- items of slice s006a11b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Allocator {
class ZoneObject {
public:
  virtual ~ZoneObject();
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
struct allocator_s006a_11b0;
}
namespace eastl {
struct basic_string8;
}
namespace eastl {
struct basic_string16;
}
namespace SP {
class cString;
}
namespace SP {
class cPropertyList_s006a_11b0;
}
struct cSPColorRGB { float x, y, z; };
struct cSPColorRGBA { float x, y, z, w; };
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
struct Key_s006a_11b0 {
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
  Variant_s006a_11b0& operator=(const Variant_s006a_11b0& o);
  Variant_s006a_11b0& operator=(const EA::ResourceMan::Key_s006a_11b0& k);
  void Destruct(int flags);
  ~Variant_s006a_11b0() {
    if (mFlags & 4) Destruct(0);
  }
  uint32_t mData[4];  // +0x0
  uint16_t mFlags;    // +0x10
  uint16_t mTypeId;   // +0x12
  cSPColorRGB* GetColorRGB();
  cSPColorRGBA* GetColorRGBA();
  EA::ResourceMan::Key_s006a_11b0* GetKey();
  SP::cString* GetText();
  eastl::basic_string8* GetString8();
  eastl::basic_string16* GetString16();
};
}
namespace eastl {
struct allocator_s006a_11b0 {};
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
struct VariantPair {  // size 0x18
  unsigned int first;  // +0x0
  EA::Variant_s006a_11b0 second;  // +0x4
};
namespace eastl {
eastl::pair<unsigned int, EA::Variant>* lower_bound(eastl::pair<unsigned int, EA::Variant>* first, eastl::pair<unsigned int, EA::Variant>* last,
                         const unsigned int* key, unsigned char comp);  // 0x00612db0 (0x18-stride instance)
}
namespace SP {
class cResourceBase_s006a_11b0 {
public:
  virtual int AddRef();
  virtual int Release();
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
  virtual void SetProperty(unsigned int key, EA::Variant_s006a_11b0* value);  // 5  (0x14)
  virtual void RemoveProperty(unsigned int key);                    // 6  (0x18)
  virtual void v7();                                               // 7  (0x1c)
  virtual bool GetPropertyA(unsigned int key, EA::Variant_s006a_11b0** out);  // 8  (0x20)
  virtual bool GetProperty(unsigned int key, EA::Variant_s006a_11b0** out) const;  // 9 (0x24)
  virtual EA::Variant_s006a_11b0* GetPropertyValue(unsigned int key);         // 10 (0x28)
  virtual void v11();                                              // 11 (0x2c)
  virtual void v12(cPropertyList_s006a_11b0* src);                            // 12 (0x30)
  virtual void DeepCopy(cPropertyList_s006a_11b0* src);                       // 13 (0x34)
  virtual void DeepAdd(cPropertyList_s006a_11b0* src);                        // 14 (0x38)
  virtual void v15();                                              // 15 (0x3c)
  virtual bool Write(EA::IO::IStream* stream) const;               // 16 (0x40)
  virtual void v17();                                              // 17 (0x44)
  virtual void Clear();                                            // 18 (0x48)

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
namespace EA {
namespace IO {
bool WriteUint32(IStream* stream, const void* pData, unsigned int count, int flags);  // namespace EA
}
}
bool WriteVariant(EA::IO::IStream* stream, EA::Variant_s006a_11b0* value, int flags);
VariantPair* PairsRealloc(unsigned int n, VariantPair* first, VariantPair* last);
void PairsDestroy(VariantPair* first, VariantPair* last);
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
struct Key_s006a_22a0 {
  uint32_t mInstance;
  uint32_t mType;
  uint32_t mGroup;
};  // namespace ResourceMan
}
}
namespace EA {
struct Variant_s006a_22a0 {
  Variant_s006a_22a0() : mFlags(0), mTypeId(0) {}
  Variant_s006a_22a0(const int& v);
  Variant_s006a_22a0(const float& v);
  Variant_s006a_22a0(const bool& v);
  Variant_s006a_22a0& operator=(const Variant_s006a_22a0& o);
  Variant_s006a_22a0& operator=(const ResourceMan::Key_s006a_22a0& k);
  void Destruct(int flags);  // 0x0093db80 (EA::Variant::Destruct)
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
struct VariantPair_s006a_22a0 {
  unsigned int first;
  EA::Variant_s006a_22a0 second;
};
namespace eastl {
VariantPair_s006a_22a0* lower_bound(VariantPair_s006a_22a0* first, VariantPair_s006a_22a0* last,
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
  void ClearMapOnly();  // 0x006a28f0 (SP::cPropertyList::ClearMapOnly)
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
  EA::Variant_s006a_22a0 const& GetProperty(unsigned int key) const;                   // 0x006a2800
  virtual EA::Variant_s006a_22a0* GetPropertyValue(unsigned int index) const;          // 10
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
bool WriteVariant(EA::IO::IStream_s006a_22a0* stream, EA::Variant_s006a_22a0* value, int flags);
// PropertyManager vtable slot +0x50 (GetPropertyByID) is a thiscall member: `this` in ecx and the
// key on the stack, so it is declared as a __fastcall shim with one dummy stack argument.
typedef void* (__fastcall* PropertyLookup_s006a_22a0)(void* mgr, int unused, unsigned int key);
// EA::Variant's assignments (0x00542b80 copy, 0x00422e20/0x00422eb0/0x00428060 scalar) cannot carry
// an annotation (the overloads are ambiguous), so they are called through these annotated shims;
// `dst` arrives in ecx and the scalar overloads take a pointer to a temporary, matching the retail
// `operator=(const T&)` argument.
void __fastcall VariantCopyAssign_EA(EA::Variant* dst, int unused, const EA::Variant* src);  // 0x00542b80
void __fastcall VariantAssignBool_EA(EA::Variant* dst, int unused, const bool* src);   // 0x00422e20
void __fastcall VariantAssignInt_EA(EA::Variant* dst, int unused, const int* src);     // 0x00422eb0
void __fastcall VariantAssignFloat_EA(EA::Variant* dst, int unused, const float* src);  // 0x00428060
// The retail bulk pair helpers: 0x00612b20 copies [first,last) to dst (cdecl), 0x00685a30
// destroys [first,last) and pops its two arguments (stdcall), 0x011e0744 is the memcpy thunk.
void PairsCopyRange_s006a_22a0(VariantPair_s006a_22a0* first, VariantPair_s006a_22a0* last,
                               VariantPair_s006a_22a0* dst);  // 0x00612b20
void __stdcall PairsDestroyRange_s006a_22a0(VariantPair_s006a_22a0* first,
                                            VariantPair_s006a_22a0* last);  // 0x00685a30
void PairsCopyBytes_s006a_22a0(void* dst, const void* src, unsigned int size);  // 0x011e0744
// Address of the retail map-clear helper: it is a VariantMap method, so the map goes in ecx.
void __fastcall MapClearOnly_s006a_22a0(SP::VariantMap* map, int unused);  // 0x006a28f0
// eastl::vector<unsigned int> stub used by GetPropertyIDs (the retail argument is a vector).
struct UIntVector_s006a_22a0 {
  unsigned int* mpBegin;     // +0x00
  unsigned int* mpEnd;       // +0x04
  unsigned int* mpCapacity;  // +0x08
  void resize(unsigned int n);                                            // 0x004cd3c0
  void DoInsertValue(unsigned int* position, const unsigned int& value);  // 0x004558a0
  void DoInsertValues(unsigned int* position, unsigned int n, const unsigned int& value);  // 0x004cea40
};
namespace EA {
namespace IO {
bool ReadInt32(IStream_s006a_22a0* stream, void* pData, unsigned int count, int flags);
}
}
static VariantPair_s006a_22a0* PairsAllocate(unsigned int n) {
  if (n == 0) return 0;
  return new ("App/cDirectPropertyList", 0, 0, 0, 0) VariantPair_s006a_22a0[n];
}
static void PairsDestroy_s006a_22a0(VariantPair_s006a_22a0* first, VariantPair_s006a_22a0* last) {
  for (; first != last; ++first) first->~VariantPair_s006a_22a0();
}
static void PairsCopy(VariantPair_s006a_22a0* dst, VariantPair_s006a_22a0* first, VariantPair_s006a_22a0* last) {
  for (; first != last; ++first, ++dst) *dst = *first;
}
static void PairsMoveBack(VariantPair_s006a_22a0* dstEnd, VariantPair_s006a_22a0* first, VariantPair_s006a_22a0* last) {
  for (; last != first;) *--dstEnd = *--last;
}
// The clear paths shrink an end pointer by the whole elements of the signed byte distance; the pair
// map divides by truncation, the unsigned-int vector by a floor shift.
static VariantPair_s006a_22a0* ShrinkEnd(VariantPair_s006a_22a0* begin, VariantPair_s006a_22a0* end) {
  int diff = (int)((char*)end - (char*)begin);
  return (VariantPair_s006a_22a0*)((char*)end - diff / 0x18 * 0x18);
}
static unsigned int* ShrinkUIntEnd(unsigned int* base, unsigned int* end) {
  int diff = (int)((char*)end - (char*)base);
  return (unsigned int*)((char*)end - (diff >> 2) * 4);
}
static void MapPairsCopy(VariantPair_s006a_22a0* dst, VariantPair_s006a_22a0* first,
                         VariantPair_s006a_22a0* last) {
  PairsCopyRange_s006a_22a0(first, last, dst);
}
static void MapPairsDestroy(VariantPair_s006a_22a0* first, VariantPair_s006a_22a0* last) {
  PairsDestroyRange_s006a_22a0(first, last);
}
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
    void* operator new[](unsigned int, char*, int, unsigned int, char*, int); // 0x00f473a0
// ---- items of slice s006a22a0 end

// ---- items of slice s00612270 begin (TODO(rewrite): local stubs, replace by canonical classes)
void __cdecl EASTL_allocator_deallocate(void* p);                                                                                  // 0x00f47380
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
// ---- items of slice s00612270 end

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
bool SP::cPropertyList_s006a_11b0::Write(EA::IO::IStream* stream) const
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

// @ 0x006a1b90
SP::cPropertyList::cPropertyList(char const * name)

: SP::cResourceBase(), mParent(), mModificationCount(0) {}

// @ 0x006a1bd0
SP::cDirectPropertyList::~cDirectPropertyList()
{
  EA::Allocator::ZoneObject::operator delete(mDirectProps); // 0x00f47380
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
bool SP::cPropertyList::GetProperty(unsigned int key, EA::Variant ** out)
{
  eastl::pair<unsigned int, EA::Variant>* end = mPropertyMap.mpEnd;
  eastl::pair<unsigned int, EA::Variant>* it = eastl::lower_bound(mPropertyMap.mpBegin, end, &key, (*(unsigned char *)&mPropertyMap.mCompare));
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

// @ 0x006a2010
void eastl::pvector::DoInsertValues(VariantPair* position, unsigned int n, const VariantPair& value)
{
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
  VariantPair_s006a_22a0* it = eastl::lower_bound(mPropertyMap.mpBegin, end, &key, mPropertyMap.mCompare);
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
  VariantPair_s006a_22a0* it = eastl::lower_bound(mPropertyMap.mpBegin, end, &key, mPropertyMap.mCompare);
  if (it == end || key < it->first)
    it = end;
  else if (it == it + 1)
    it = end;
  if (it == end) return false;
  EA::Variant_s006a_22a0* v = &it->second;
  return v->mTypeId != 0;
}

// @ 0x006a2660
int SP::cDirectPropertyList::GetIntProperty(unsigned int index) const
{
  if (index < mNumDirectProps) return mDirectProps[index];
  EA::Variant* v = ((EA::Variant *)&GetProperty(index));
  return v->mFloat;
}

// @ 0x006a2710
float SP::cDirectPropertyList::GetFloatProperty(unsigned int index) const
{
  if (index < mNumDirectProps) return ((float*)mDirectProps)[index];
  EA::Variant* v = ((EA::Variant *)&GetProperty(index));
  return *(float*)&v->mFloat;
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
EA::Variant const & SP::cDirectPropertyList::GetProperty(unsigned int key) const
{
  if (key < mNumDirectProps) {
    EA::Variant* out = const_cast<EA::Variant*>(&mTempDirectVariant);
    void* mgr = PropertyManager();
    void* entry = (*(PropertyLookup_s006a_22a0*)(*(int*)mgr + 0x50))(mgr, 0, key);
    VariantCopyAssign_EA(out, 0, (const EA::Variant*)entry);
    if (!(out->mFlags & 0x10)) {
      // A variant that is not constructed from a raw pointer is rebuilt from the direct slot.
      if (out->mTypeId == EA::Variant::kTypeBool) {
        bool value = mDirectProps[key] != 0;
        VariantAssignBool_EA(out, 0, &value);
      } else if (out->mTypeId == EA::Variant::kTypeInt32) {
        int value = mDirectProps[key];
        VariantAssignInt_EA(out, 0, &value);
      } else if (out->mTypeId == EA::Variant::kTypeFloat) {
        float value = ((float*)mDirectProps)[key];
        VariantAssignFloat_EA(out, 0, &value);
      }
    }
    return mTempDirectVariant;
  }
  return cPropertyList::GetProperty(key);
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
void SP::cPropertyList_s006a_22a0::ClearMapOnly()
{
  // The retail helper is a VariantMap method (it takes the map itself in ecx), so this member form
  // works on the object as the map it was named after.
  VariantMap* map = (VariantMap*)(void*)this;
  MapPairsCopy(map->mpBegin, map->mpEnd, map->mpEnd);
  MapPairsDestroy(map->mpBegin, map->mpEnd);
  map->mpEnd = ShrinkEnd(map->mpBegin, map->mpEnd);
}

// @ 0x006a2940
VariantPair_s006a_22a0* eastl::pvector_s006a_22a0::insert(VariantPair_s006a_22a0* position, const VariantPair_s006a_22a0& value)
{
  // The append fast path is inlined here (the original only calls DoInsertValue when it has to
  // grow), and the result is indexed off the *new* begin.
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
  MapPairsCopy(map->mpBegin, map->mpEnd, map->mpEnd);
  MapPairsDestroy(map->mpBegin, map->mpEnd);
  map->mpEnd = ShrinkEnd(map->mpBegin, map->mpEnd);
  mModificationCount++;
}

// @ 0x006a2ad0
void SP::cDirectPropertyList_s006a_22a0::Copy(cPropertyList_s006a_22a0* src)
{
  if (this == src) return;
  MapClearOnly_s006a_22a0(&mPropertyMap, 0);
  VariantPair_s006a_22a0* it = src->mPropertyMap.mpBegin;
  VariantPair_s006a_22a0* end = src->mPropertyMap.mpEnd;
  for (; it != end; ++it) SetProperty(it->first, &it->second);
  SetParent(mParent);  // the original re-parents to its own (already current) parent
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
  VariantPair_s006a_22a0* it = eastl::lower_bound(mpBegin, end, &value.first, mCompare);
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
  VariantPair_s006a_22a0* it = eastl::lower_bound(mpBegin, end, &key, mCompare);
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
  int nCount = 0;
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
  while ((unsigned int)(mPropertyMap.mpEnd - mPropertyMap.mpBegin) < want) {
    VariantPair_s006a_22a0 v;
    mPropertyMap.insert_pos(mPropertyMap.mpEnd, v);
  }
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
  UIntVector_s006a_22a0* v = (UIntVector_s006a_22a0*)ids;
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
  UIntVector_s006a_22a0* v = (UIntVector_s006a_22a0*)ids;
  PairsCopyBytes_s006a_22a0(v->mpBegin, v->mpEnd, 0);
  v->mpEnd = ShrinkUIntEnd(v->mpBegin, v->mpEnd);
  void* mgr = PropertyManager();
  for (unsigned int i = 1; i < mNumDirectProps; i++) {
    void* entry = (*(PropertyLookup_s006a_22a0*)(*(int*)mgr + 0x50))(mgr, 0, i);
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
    PairsCopyBytes_s006a_22a0(dst, v->mpEnd, 0);
    v->mpEnd = ShrinkUIntEnd(dst, v->mpEnd);
  }
  unsigned int k = oldN;
  for (VariantPair_s006a_22a0* it = mPropertyMap.mpBegin; it != mPropertyMap.mpEnd; ++it) {
    v->mpBegin[k] = it->first;
    k++;
  }
  return (unsigned int)(size_t)mPropertyMap.mpEnd;
}
