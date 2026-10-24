// Decompiled slice s00b20fb0 -- SP::cGameNounManager noun/game-data plumbing.
// Reconstructed from the shipped binary; helper addresses noted per call.
#include <intrin.h>
#include "types.h"

void* operator new(unsigned int size, const char* pName, int flags, unsigned debugFlags,
                   const char* file, int line);
void* operator new[](unsigned int size, const char* pName, int flags, unsigned debugFlags,
                     const char* file, int line);
void  operator delete[](void* p);
void  operator delete(void* p);

// ---------------------------------------------------------------------------
// shared shapes
// ---------------------------------------------------------------------------
typedef void (__thiscall* FnVoid0)(void*);
typedef void (__thiscall* FnVoidI)(void*, int);

namespace SP {

// The noun manager owns a single "primary" noun plus the noun collection and
// the per-scenario game-data vector map.
struct cGameNounManager {
  uint8_t mUnused00[0x74];
  void*   mPrimaryNoun;                                   // +0x74

  void* CreateNoun(int id);                               // 0x00b20c60
  void  FUN_00b20fb0();                                   // 0x00b20fb0
};

}  // namespace SP

// A tGameDataVectorT handle: header byte + three pointer-sized fields.
struct tGameDataVectorT {
  uint8_t  mOwnsBuffer;                                   // +0x00
  uint8_t  mUnused01[3];
  void*    mField04;                                      // +0x04
  void*    mField08;                                      // +0x08
  void*    mField0c;                                      // +0x0c
  uint32_t mField10;                                      // +0x10
  uint32_t mField14;                                      // +0x14
};

// ---------------------------------------------------------------------------
// @ 0x00b20fb0
// Builds (once) the manager's primary noun and immediately runs its
// post-create slot 0x28 with argument 0.
void SP::cGameNounManager::FUN_00b20fb0()
{
  if (mPrimaryNoun == 0) {
    void* noun = CreateNoun(0x2c21781);
    void* old  = mPrimaryNoun;
    if (noun != old) {
      if (noun)
        ((FnVoid0)(((void**)*(void**)noun)[0]))(noun);
      mPrimaryNoun = noun;
      if (old)
        ((FnVoid0)(((void**)*(void**)old)[1]))(old);
    }
    ((FnVoidI)(((void**)*(void**)mPrimaryNoun)[0x28 / 4]))(mPrimaryNoun, 0);
  }
}

// ---------------------------------------------------------------------------
// @ 0x00b21080
// Allocates and initialises a tGameDataVectorT handle (owner flag set, buffer
// and read/write cursors cleared).
tGameDataVectorT* FUN_00b21080()
{
  tGameDataVectorT* p =
      (tGameDataVectorT*)operator new(0x18, "Simulator/tGameDataVectorT", 0, 0, 0, 0);
  if (p) {
    p->mOwnsBuffer = 1;
    p->mField04 = 0;
    p->mField08 = 0;
    p->mField0c = 0;
    return p;
  }
  return 0;
}

// ---------------------------------------------------------------------------
// clsid -> name map: a global eastl rbtree keyed by int whose nodes carry the
// mapped value in their user field at +0x14.
struct MapNode {
  uint8_t mUnused00[0x14];
  void*   mValue;                                         // +0x14
};

struct MapIterator {
  MapNode* mpNode;                                        // +0x00
  MapIterator();
  MapIterator(const MapIterator&);
};

struct cClsidMap {
  uint32_t  mUnused00;                                    // +0x00
  MapNode   mEnd;                                         // +0x04
  MapIterator find(const int& key);                       // 0x00e39fb0
};

extern cClsidMap g_clsidMap;                              // 0x0156854c
extern void*     g_clsidNameSlot;                         // 0x01568584

void FUN_00b21060(char* dst, const char* fmt, int value); // 0x00b21060

// @ 0x00b21490
// Looks a CLSID up in the global clsid->name tree, falling back to a formatted
// "clsid 0x%08x" string when there is no entry.
char* FUN_00b21490(int clsid)
{
  MapIterator it = g_clsidMap.find(clsid);
  if (it.mpNode != &g_clsidMap.mEnd)
    return (char*)it.mpNode->mValue;
  FUN_00b21060((char*)&g_clsidNameSlot, "clsid 0x%08x", clsid);
  return (char*)g_clsidNameSlot;
}

// ---------------------------------------------------------------------------
// A 64-bit-keyed eastl hashtable.  Buckets live at +0x04, the bucket count at
// +0x08; values are stored in the node starting at +0x08.
struct Ht64Node {
  uint64_t mKey;                                          // +0x00
  void*    mValue;                                        // +0x08
};

struct Ht64Iter {
  Ht64Node* mpNode;                                       // +0x00
  void*     mpTable;                                      // +0x04
  Ht64Iter();
  Ht64Iter(const Ht64Iter&);
};

// The lookup key is a two-word value; the hashtable hashes it verbatim.
struct HtKey {
  uint32_t mLow;                                          // +0x00
  uint32_t mHigh;                                         // +0x04
};

struct Ht64 {
  uint32_t   mUnused00;                                   // +0x00
  Ht64Node** mpBuckets;                                   // +0x04
  uint32_t   mBucketCount;                                // +0x08
  Ht64Iter find(const uint64_t& key);                     // 0x00b207f0
};

struct Ht64Owner {
  uint8_t mUnused00[0x20];
  Ht64    mTable;                                         // +0x20
  void*   FUN_00b21000(int p2, int p3);
};

// @ 0x00b21000
// Two-word-keyed hashtable lookup: returns a pointer just past the node's key,
// or null when the key is absent.
void* Ht64Owner::FUN_00b21000(int p2, int p3)
{
  uint64_t key = (uint64_t)p2 | ((uint64_t)p3 << 32);
  Ht64& table = mTable;
  Ht64Iter it = table.find(key);
  if (it.mpNode != table.mpBuckets[table.mBucketCount])
    return (char*)it.mpNode + 8;
  return 0;
}

// ---------------------------------------------------------------------------
// A uint-keyed hashtable whose entries carry a callable and a next pointer.
typedef uint32_t (__cdecl* HtStrProc)();
typedef void (__cdecl* HtStrAction)();

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

// @ 0x00b21180
// Scalar-deleting destructor for the string-hashtable owner: releases the
// bucket array, resets the vtable, and optionally frees the object.
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

// @ 0x00b21140
// Looks a two-word key up and invokes the entry's callable when it exists.
uint32_t HtStrOwner::FUN_00b21140(uint64_t key)
{
  StrHt& table = mTable;
  HtStrIter it = table.find(key);
  if (it.mpNode != table.mpBuckets[table.mBucketCount])
    return (*(HtStrProc*)&it.mpNode->mValue)();
  return 0;
}

// @ 0x00b210d0
// Copies up to maxCount entry keys out of the table into dst, skipping empty
// buckets and stopping at the end sentinel.
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

// ---------------------------------------------------------------------------
// A doubly-linked segment whose anchor doubles as the list anchor: every
// element stores a back-pointer to its owner anchor in its third word.
struct ListNode {
  void* mField00;                                         // +0x00
  void* mField04;                                         // +0x04
  void* mField08;                                         // +0x08
};

struct ListSeg {
  uint8_t mUnused00[4];
  void*   mField04;                                       // +0x04  anchor.next
  void*   mField08;                                       // +0x08  anchor.prev
  void*   mField0c;                                       // +0x0c  last element
  uint8_t mUnused10[4];
  void*   mField14;                                       // +0x14
  void    FUN_00b21da0(ListSeg* other);
};

// @ 0x00b21da0
// Swaps two linked segments (and their trailing scalars), repairing the
// anchor back-pointers of the moved elements.
void ListSeg::FUN_00b21da0(ListSeg* other)
{
  void* t = mField14;
  mField14 = other->mField14;
  other->mField14 = t;
  if (mField0c != 0) {
    if (other->mField0c != 0) {
      void* a = mField04; mField04 = other->mField04; other->mField04 = a;
      void* b = mField08; mField08 = other->mField08; other->mField08 = b;
      void* c = mField0c; mField0c = other->mField0c; other->mField0c = c;
      ((ListNode*)mField0c)->mField08 = &mField04;
      ((ListNode*)other->mField0c)->mField08 = &other->mField04;
      return;
    }
    if (mField0c != 0) {
      other->mField04 = mField04;
      other->mField08 = mField08;
      void* c = mField0c;
      other->mField0c = c;
      ((ListNode*)c)->mField08 = &other->mField04;
      mField0c = 0;
      mField04 = &mField04;
      mField08 = &mField04;
      return;
    }
  }
  if (other->mField0c != 0) {
    mField04 = other->mField04;
    mField08 = other->mField08;
    void* c = other->mField0c;
    mField0c = c;
    ((ListNode*)c)->mField08 = &mField04;
    other->mField04 = &other->mField04;
    other->mField0c = 0;
    other->mField08 = &other->mField04;
  }
}