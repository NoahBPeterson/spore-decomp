// src/game/SPEngine/SPDirectories.cpp -- migrated from slice(s) s00687c20 by tools/migrate/rewrite.py
// Object file: SPEngine/SPDirectories.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ArgScript/cArguments.h"
#include <intrin.h>   // _ReadWriteBarrier (WStr stub)

// unnamed retail callees and globals (address in the comment)
extern wchar_t gEmptyWString[];                       // 0x1667bac shared empty string
extern "C" void EASTL_allocator_deallocate(void* p);  // 0xf47380
extern "C" void* memcpy(void*, const void*, unsigned);  // E8 call (non-dllimport thunk)
extern const char g_allocFile[];                      // 0x13ebb38 EASTL/allocator.h path

// ---- items of slice s00687c20 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new(unsigned int size, const char* pName, int flags, unsigned debugFlags,
                   const char* pFile, int line);      // 0xf473a0 EA 6-arg operator new
void operator delete(void* p, const char* pName, int flags, unsigned debugFlags,
                     const char* pFile, int line);    // matching placement delete (EH cleanup)
struct WStr {
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  void* mAllocUnused;   // stateless allocator member (never stored)

  WStr() : mpBegin(gEmptyWString), mpEnd(gEmptyWString), mpCapacity(gEmptyWString + 1) {}
  WStr(const wchar_t* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p); }
  WStr(const WStr& x) : mpBegin(0), mpEnd(0), mpCapacity(0) {
    _ReadWriteBarrier();
    RangeInitialize(x.mpBegin, x.mpEnd);
  }
  WStr(const wchar_t* pBegin, const wchar_t* pEnd)
      : mpBegin(0), mpEnd(0), mpCapacity(0) {
    _ReadWriteBarrier();
    RangeInitialize(pBegin, pEnd);
  }
  struct InlineTag { InlineTag() {} };
  // Same as the range ctor but with the allocation (EA operator new "App") expanded inline.
  __forceinline WStr(const wchar_t* pBegin, const wchar_t* pEnd, const InlineTag&)
      : mpBegin(0), mpEnd(0), mpCapacity(0) {
    const int n = (int)(pEnd - pBegin);
    const int cap = n + 1;
    if (cap > 1) {
      mpBegin = (wchar_t*)operator new(cap * 2, "App", 0, 0, g_allocFile, 0xd1);
      mpCapacity = mpBegin + cap;
    } else {
      mpBegin = gEmptyWString;
      mpCapacity = gEmptyWString + 1;
    }
    memcpy(mpBegin, pBegin, n * 2);
    mpEnd = mpBegin + n;
    *mpEnd = 0;
  }
  ~WStr() {
    if ((((char*)mpCapacity - (char*)mpBegin) & ~1) > 2 && mpBegin)
      EASTL_allocator_deallocate(mpBegin);
  }
  WStr& operator=(const WStr& x);                  // 0x5c3d90
  void Assign(const wchar_t* b, const wchar_t* e); // 0x423650
  void push_back(wchar_t c);                       // 0x4f6510
  void AllocateSelf(int n);                        // 0x429760
  void RangeInitialize(const wchar_t* p);          // 0x579a90
  void RangeInitialize(const wchar_t* pBegin, const wchar_t* pEnd) {
    const int n = (int)(pEnd - pBegin);
    AllocateSelf(n + 1);
    memcpy(mpBegin, pBegin, n * 2);
    mpEnd = mpBegin + n;
    *mpEnd = 0;
  }
};
struct PairUW {
  unsigned key;
  WStr str;
  PairUW(const unsigned* k, const WStr& src);
  PairUW(const PairUW& o);
  // the EASTL node type's allocator, and the placement form the node's constructor uses
  static void* operator new(unsigned int n) { return ::operator new(n); }
  static void* operator new(unsigned int n, void* p, int) { return p; }
  static void operator delete(void*, void*, int) {}
  static void* operator new(unsigned int n, const char* pName, int flags, unsigned debugFlags,
                            const char* pFile, int line) {
    return ::operator new(n, pName, flags, debugFlags, pFile, line);
  }
};
struct IterPair { void* first; void* second; };
struct DirMap {
  char pad0[4];
  void Find(void** out, const unsigned* key);   // 0xe5c780 (hidden out-ptr)
  WStr* OpBr(const unsigned* key);              // @ 0x688ad0
  IterPair Insert(void* pos, PairUW* p, const void* keyTag);  // 0x6889e0 (sret)
};
// ---- items of slice s00687c20 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern DirMap g_dirMap;                          // 0x152ba34

// @ 0x006886b0
namespace SP {
wchar_t const * GetDirFromID(unsigned int key)
{
  void* it;
  g_dirMap.Find(&it, &key);
  if (it != (char*)&g_dirMap + 4)
    return *(wchar_t**)((char*)it + 0x14);
  return 0;
}
}  // namespace SP

// @ 0x00688cb0
namespace SP {
wchar_t const * GetDataDir()
{
  unsigned key = 0xa02149;
  return g_dirMap.OpBr(&key)->mpBegin;
}
}  // namespace SP
