// src/game/UTFSpore_Win32/StringTable.cpp -- migrated from slice(s) s00999110 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/StringTable.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Allocator/StackAllocator.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void  operator_delete(void*) throw();   // 0x00f47380
extern void FUN_00620230(void*);
#include <intrin.h>
#include <string.h>
#include <new>
#pragma intrinsic(_InterlockedExchange)

// ---- items of slice s00999110 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl operator new(size_t, const char*, int, int, int, int);
typedef unsigned int uint;
extern "C" void  operator_delete(void*) throw();   // 0x00f47380
extern void FUN_00620230(void*);
struct Key { uint mInstance; uint mType; uint mGroup; };
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
struct IntrusiveListHead { void* mpNext; void* mpPrev; };
struct UIStringMan {
  virtual ~UIStringMan();
  int    mField04;         // +0x04
  void*  mpArg;            // +0x08
  IntrusiveListHead mList; // +0x0c
  UIStringMan(void* arg);
  __declspec(noinline) void ClearList();
};
struct S99890Finder { char c[4]; unsigned* __thiscall find(void* tmp, unsigned* key); };   // 0xa23ef0
struct S99890 {
  char pad0[4];             // +0x00
  S99890Finder finder;      // +0x04
  unsigned** mpArray;       // +0x08
  uint mIndex;              // +0x0c
  bool f(unsigned* key);
};
struct KeyFilter { virtual ~KeyFilter() {} };
struct HashSetU32 {                 // eastl::hash_set<uint> (nodes of 8 bytes)
  char alloc[4];
  void** mpBucketArray;             // +0x04 (in filter)
  uint  mnBucketCount;
  uint  mnElementCount;
  float mfMaxLoad, mfGrowth;
  uint  mnNextResize;
  void __thiscall DoFreeNodes(void** array, uint count) throw();         // 0x6b6570
  void* __thiscall DoInsertValue(void* out, const uint* v, char flag);   // 0x6758a0
  __forceinline ~HashSetU32() {
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
    if (mnBucketCount > 1) operator_delete(mpBucketArray);
  }
};
struct StringTableFilter : KeyFilter {
  HashSetU32 mTypes;   // +0x04
  __forceinline ~StringTableFilter() {}
  StringTableFilter() {
    mTypes.mnBucketCount = 1;
    mTypes.mpBucketArray = (void**)0x154df28;
    mTypes.mnElementCount = 0;
    mTypes.mfMaxLoad = 1.0f;
    mTypes.mfGrowth = 2.0f;
    mTypes.mnNextResize = 0;
  }
};
// ---- items of slice s00999110 end

// @ 0x009997e0
StringTable::StringTable()
{
  mpTableName = 0;
  mFirstKey.mInstance = 0; mFirstKey.mType = 0; mFirstKey.mGroup = 0;
  mLastKey.mInstance = 0; mLastKey.mType = 0; mLastKey.mGroup = 0;
}

// @ 0x00999820
UIStringMan::UIStringMan(void* arg)
: mpArg(arg), mField04(0) {
  mList.mpPrev = &mList;
  mList.mpNext = &mList;
}

// @ 0x00999850
UIStringMan::~UIStringMan()
{
  ClearList();
  FUN_00620230(&mList);
}

// @ 0x00999890
bool S99890::f(unsigned* key)
{
  S99890Finder* fp = &finder;
  unsigned* elem = mpArray[mIndex];
  unsigned tmp[2];
  unsigned* found = fp->find(tmp, key + 1);
  return *found != (unsigned)elem;
}

// @ 0x009998d0
static void* g_filterVtableAnchor()
{ return new StringTableFilter; }
