// src/game/UTFSpore_Win32/EASymbolUtil.cpp -- migrated from slice(s) s00b20fb0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EASymbolUtil.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cGameNounManager.h"
#include <intrin.h>

// ---- items of slice s00b20fb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void  operator delete[](void* p);
void  operator delete(void* p);
typedef uint32_t (__cdecl* HtStrProc)();
struct HtStrNode {
  uint32_t   mKey;                                        // +0x00
  void*      mValue;                                      // +0x04
  HtStrNode* mpNext;                                      // +0x08
};
struct HtStrIter {
  HtStrNode* mpNode;                                      // +0x00
  void*      mpTable;                                     // +0x04
  HtStrIter();
  HtStrIter(const HtStrIter&);
};
struct StrHt {
  uint32_t    mUnused00;                                  // +0x00
  HtStrNode** mpBuckets;                                  // +0x04
  uint32_t    mBucketCount;                               // +0x08
  uint32_t    mSize;                                      // +0x0c
  void DoFreeBuckets(HtStrNode** pBegin, uint32_t count); // 0x00693230
  HtStrIter find(const uint64_t& key);                    // 0x00645ed0
};
struct HtStrOwner {
  void*    mpVtable;                                      // +0x00
  uint8_t  mUnused04[0x0c];
  StrHt    mTable;                                        // +0x10
  HtStrOwner* FUN_00b21180(uint8_t flags);
  uint32_t    FUN_00b21140(uint64_t key);
  void        FUN_00b210d0(uint32_t* dst, uint32_t maxCount);
};
// ---- items of slice s00b20fb0 end

// @ 0x00b210d0
void HtStrOwner::FUN_00b210d0(uint32_t* dst, uint32_t maxCount)
{
  HtStrNode** bucket = mTable.mpBuckets;
  HtStrNode* node = *bucket;
  uint32_t i = 0;
  if (node == 0) {
    do {
      ++bucket;
      node = *bucket;
    } while (node == 0);
  }
  if (maxCount != 0) {
    do {
      if (node == mTable.mpBuckets[mTable.mBucketCount])
        break;
      dst[i] = node->mKey;
      ++i;
      node = node->mpNext;
      while (node == 0) {
        ++bucket;
        node = *bucket;
      }
    } while (i < maxCount);
  }
}

// @ 0x00b21140
uint32_t HtStrOwner::FUN_00b21140(uint64_t key)
{
  StrHt& table = mTable;
  HtStrIter it = table.find(key);
  if (it.mpNode != table.mpBuckets[table.mBucketCount])
    return (*(HtStrProc*)&it.mpNode->mValue)();
  return 0;
}

// @ 0x00b21180
HtStrOwner* HtStrOwner::FUN_00b21180(uint8_t flags)
{
  StrHt& table = mTable;
  mpVtable = (void*)0x0145ed3c;
  table.DoFreeBuckets(table.mpBuckets, table.mBucketCount);
  table.mSize = 0;
  if (table.mBucketCount > 1)
    operator delete[](table.mpBuckets);
  mpVtable = (void*)0x01403934;
  if (flags & 1)
    operator delete[](this);
  return this;
}
