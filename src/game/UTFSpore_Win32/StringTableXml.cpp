// src/game/UTFSpore_Win32/StringTableXml.cpp -- migrated from slice(s) s0099a050, s00999110 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/StringTableXml.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Allocator/StackAllocator.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void  operator_delete(void*) throw();   // 0x00f47380
extern "C" void* operator_new(unsigned int, const char*, int, int, const char*, int);   // 0x00f473a0
extern "C" void* FUN_011e0744(void* dst, const void* src, unsigned n);   // memcpy thunk, returns dst
#include <intrin.h>
#include <string.h>
#include <new>
#include <wchar.h>
#pragma intrinsic(_InterlockedExchange)

// ---- items of slice s00999110 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl operator new(size_t, const char*, int, int, int, int);
typedef unsigned int uint;
extern "C" void  operator_delete(void*) throw();   // 0x00f47380
extern "C" void* operator_new(unsigned int, const char*, int, int, const char*, int);   // 0x00f473a0
#define VF(o, off, sig) ((sig)(*(void***)(o))[(off) / 4])
extern "C" void* FUN_011e0744(void* dst, const void* src, unsigned n);   // memcpy thunk, returns dst
struct Key { uint mInstance; uint mType; uint mGroup; };
struct IUnknown32 {
  virtual void AddRef();
  virtual void Release();
  virtual void v08();
  virtual void* Cast(uint type);
  virtual void v10();
  virtual void v14();
  virtual void v18();
  virtual void v1c();
  virtual void v20();
  virtual void v24();
  virtual void v28();
  virtual void v2c();
};
namespace EA { namespace Allocator {
class StackAllocator_s0092_8b00 {
public:
  bool __thiscall AllocateNewBlock(unsigned int) throw();
};
}}

struct StackAllocator {
  uint   mnDefaultBlockSize;         // +0x00
  void*  mpCurrentBlock;             // +0x04
  char*  mpCurrentBlockEnd;          // +0x08
  char*  mpCurrentObjectBegin;       // +0x0c
  char*  mpCurrentObjectEnd;         // +0x10
  void*  mpCoreAllocationFunction;   // +0x14
  void*  mpCoreFreeFunction;         // +0x18
  void*  mpCoreFunctionContext;      // +0x1c
  void*  mpTopBookmark;              // +0x20
  StackAllocator(int, int, int, int, int) throw();   // 0x00928cd0
  ~StackAllocator() { Reset(); }
  void __thiscall Reset() throw();                 // 0x928dc0
  void   Init(int, int, int, int, int) throw();   // 0x00928b00
  bool   AllocateNewBlock(uint) throw();   // 0x0082b0d0
  void* AllocInline(uint size) {
    if ((int)(mpCurrentBlockEnd - mpCurrentObjectBegin) - (int)size < 0) {
      if (!AllocateNewBlock(size)) return 0;
    }
    char* p = mpCurrentObjectBegin;
    mpCurrentObjectBegin = p + size;
    mpCurrentObjectEnd = p + size;
    return p;
  }
};
struct ResourceBase {
  virtual ~ResourceBase();
  volatile long mRefCount;   // +0x04
  Key mKey;                  // +0x08
  ResourceBase() {
    _InterlockedExchange(&mRefCount, 0);
    mKey.mInstance = 0; mKey.mType = 0; mKey.mGroup = 0;
  }
};
struct IntrusiveNode {
  void* mpNext;   // maps to StringTable+0x14
  void* mpPrev;   // maps to StringTable+0x18
  IntrusiveNode() { mpPrev = 0; mpNext = 0; }
};
struct StringTable : ResourceBase, IntrusiveNode {
  wchar_t* mpTableName;   // +0x1c
  Key mFirstKey;          // +0x20
  Key mLastKey;           // +0x2c
  __declspec(noinline) StringTable();
  ~StringTable();                                   // out of line at 0xa16a20
};
struct PtrVector {
  IUnknown32** mpBegin;   // +0x00
  IUnknown32** mpEnd;     // +0x04
  IUnknown32** mpCap;     // +0x08
  char alloc[4];          // +0x0c
  void resize(uint) throw();
};
struct StrVec {
  IUnknown32** mpStringBegin;  // +0x38
  IUnknown32** mpStringEnd;    // +0x3c
  IUnknown32** mpStringCap;    // +0x40
  char padString[8];           // +0x44
  StrVec() : mpStringBegin(0), mpStringEnd(0), mpStringCap(0) {}
  ~StrVec() { if (mpStringBegin != 0 && *(int*)((char*)mpStringBegin - 4) != 0) operator_delete(mpStringBegin); }
};
struct StringTableXml : StringTable {
  StrVec mStrings;
  StackAllocator mAllocator;   // +0x4c
  StringTableXml(const Key& k, const wchar_t* name);
  ~StringTableXml();
  wchar_t* StrDup(const wchar_t* src);
  void SetString(uint index, const wchar_t* str);
};
struct SpVec {                       // eastl::vector<T*, sp_vector_allocator>
  void** b; void** e; void** c; char alloc[4];
  void __thiscall DoInsertValue(void** pos, void** v);   // 0xa80dd0
  void __thiscall swap(SpVec* o);                        // 0x811a20
  void __thiscall insert_n(void** pos, uint n, void** value);   // 0x999dd0
  void push_back(void* v) {
    void** p = e;
    if (p < c) { e = p + 1; if (p) *p = v; }
    else DoInsertValue(p, &v);
  }
  void clear_all() {
    void** last = e; void** first = b;
    FUN_011e0744(first, last, (uint)((char*)e - (char*)last));
    e = e - (last - first);
  }
};
struct FactoryBase {
  virtual ~FactoryBase();
  FactoryBase() { _InterlockedExchange(&mRefCount, 0); }
  volatile long mRefCount;  // +0x04
};
struct ILoadSrc {
  virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
  virtual uint GetOffset();       // +0x10
  virtual uint GetBase();         // +0x14
};
struct LoadCallbackHolder {
  char pad[8];
  void* mpCallback;   // +0x08
  uint  mArg;         // +0x0c
  void Invoke(ILoadSrc* src, uint extra);
};
struct FactoryStringTableXml : FactoryBase {
  void* mErrorCallback;    // +0x08
  void* mpCallbackContext; // +0x0c
  FactoryStringTableXml();
};
struct FactoryStringTableXml2 : FactoryBase {
  void* mErrorCallback;    // +0x08
  void* mpCallbackContext; // +0x0c
  bool CreateResource(void* src, void** out, const wchar_t* name, uint a4);
};
// ---- items of slice s00999110 end

// ---- items of slice s0099a050 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace StringMan {
struct FactoryStringTableXml_s0099_a050 {
    bool ReadResource(int param_2, int* param_3, unsigned param_4, int param_5);  // 0x99a050
};  // namespace StringMan
}
}
// ---- items of slice s0099a050 end

// @ 0x00999b20
wchar_t* StringTableXml::StrDup(const wchar_t* src)
{
  if (src == 0) return 0;
  const wchar_t* p = src;
  do { } while (*p++);
  uint bytes = ((uint)(p - (src + 1)) * 2 + 9) & 0xfffffff8;
  StackAllocator* a = &mAllocator;
  if ((int)(a->mpCurrentBlockEnd - a->mpCurrentObjectBegin) - (int)bytes < 0) {
    if (!((EA::Allocator::StackAllocator_s0092_8b00*)a)->AllocateNewBlock(bytes))
      return 0;
  }
  wchar_t* d = (wchar_t*)a->mpCurrentObjectBegin;
  a->mpCurrentObjectBegin = (char*)d + bytes;
  a->mpCurrentObjectEnd = (char*)d + bytes;
  wchar_t* result = d;
  while ((*d++ = *src++) != 0) {}
  return result;
}

// @ 0x00999ba0
int __stdcall FUN_00999ba0(uint* types, uint count)
{
  if (count > 0) *types = 0xcf6c21b8;
  return 1;
}

// @ 0x00999bc0
void LoadCallbackHolder::Invoke(ILoadSrc* src, uint extra)
{
  if (mpCallback != 0) {
    // four cdecl arguments, evaluated right to left: mArg is pushed before GetBase is called
    ((void (__cdecl*)(uint, uint, uint, uint))mpCallback)(extra, src->GetOffset(), src->GetBase(), mArg);
  }
}

// @ 0x00999c20
FactoryStringTableXml::FactoryStringTableXml()
{ mErrorCallback = 0; mpCallbackContext = 0; }

// @ 0x00999c50
StringTableXml::StringTableXml(const Key& k, const wchar_t* name)
: mAllocator(0, -1, 0, 0, 0) {
  mFirstKey.mInstance = k.mInstance;
  mFirstKey.mType = k.mType;
  mFirstKey.mGroup = k.mGroup;
  mFirstKey.mType = 0x4f72d78a;
  mAllocator.Init(0, 0, 0, 0, 0);
  mpTableName = StrDup(name);
  mAllocator.AllocateNewBlock(0);
}

// @ 0x00999ce0
StringTableXml::~StringTableXml()
{
  mAllocator.Reset();
}

// @ 0x00999d30
bool FactoryStringTableXml2::CreateResource(void* src, void** out, const wchar_t* name, uint a4)
{
  StringTableXml* t = new("UTFWin/StringTableXml", 0, 0, 0, 0)
    StringTableXml(*VF(src, 0x10, Key*(__thiscall*)(void*))(src), name);
  VF(t, 0, void(__thiscall*)(void*))(t);
  char ok = VF(this, 0x24, char(__thiscall*)(void*, void*, void*, const wchar_t*, uint))(this, src, t, name, a4);
  if (ok) {
    t->mLastKey = t->mFirstKey;
    t->mLastKey.mInstance += (uint)(t->mStrings.mpStringEnd - t->mStrings.mpStringBegin);
    *out = t;
    return true;
  }
  VF(t, 4, void(__thiscall*)(void*))(t);
  return false;
}

// @ 0x00999dd0
void SpVec::insert_n(void** position, uint n, void** value)
{
  if ((uint)(c - e) >= n) {
    if (n > 0) {
      void* temp = *value;
      void** oldEnd = e;
      uint nExtra = (uint)(oldEnd - position);
      if (n < nExtra) {
        void** first = oldEnd - n;
        FUN_011e0744(oldEnd, first, (uint)((char*)oldEnd - (char*)first));
        e = e + n;
        memmove((char*)oldEnd - ((char*)first - (char*)position), position, (uint)((char*)first - (char*)position));
        void** stop = position + n;
        if (position != stop) {
          do { *position++ = temp; } while (position != stop);
        }
      } else {
        uint k = n - nExtra;
        void** q = oldEnd;
        for (uint i = k; i != 0; i--)
          *q++ = temp;
        e = e + k;
        FUN_011e0744(e, position, (uint)((char*)oldEnd - (char*)position));
        e = e + nExtra;
        if (position != oldEnd) {
          do { *position++ = temp; } while (position != oldEnd);
        }
      }
    }
  } else {
    uint oldSize = (uint)(e - b);
    uint grow = oldSize * 2;
    if (oldSize == 0)
      grow = 1;
    uint newCap = oldSize + n;
    if (newCap < grow)
      newCap = grow;
    void** nb = 0;
    if (newCap != 0)
      nb = (void**)operator_new(newCap * 4, "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    uint pre = (uint)((char*)position - (char*)b);
    void** d = (void**)FUN_011e0744(nb, b, pre);
    d = (void**)((char*)d + (pre >> 2) * 4);
    void* temp = *value;
    void** f = d;
    for (uint i = n; i != 0; i--)
      *f++ = temp;
    d = d + n;
    uint post = (uint)((char*)e - (char*)position);
    void** r = (void**)FUN_011e0744(d, position, post);
    void** newEnd = (void**)((char*)r + (post >> 2) * 4);
    if (b != 0 && ((int*)b)[-1] != 0)
      operator_delete(b);
    b = nb;
    e = newEnd;
    c = nb + newCap;
  }
}

// @ 0x0099a010
void StringTableXml::SetString(uint index, const wchar_t* str)
{
  if ((uint)(mStrings.mpStringEnd - mStrings.mpStringBegin) < index + 1)
    ((PtrVector*)&mStrings.mpStringBegin)->resize(index + 1);
  wchar_t** dst = (wchar_t**)(mStrings.mpStringBegin + index);
  *dst = StrDup(str);
}

// @ 0x0099a050
bool EA::StringMan::FactoryStringTableXml_s0099_a050::ReadResource(int, int*, unsigned, int)
{
    return 0;
}
