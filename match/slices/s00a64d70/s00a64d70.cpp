// Slice s00a64d70 (batch hk2, slice 4). Region 0x00a64ed0-0x00a64f74.
// Audio (EA::Audio::Eapd) owner: remove an entry from its group map, notify the listener when the group
// is empty, then erase the map node. Callees: hashtable::find (0x685f30), erase (0xa64cf0),
// pair list remove (0xa64750), list-empty test (0xa647a0).
#include "types.h"

struct cEntry18 {                  // param object: key at +0x2c, +0x30, +0x34, list link at +0x40
  uint8_t   pad0[0x2c];
  uint32_t  mKey;                  // +0x2c
  uint32_t  mA;                    // +0x30
  uint32_t  mB;                    // +0x34
  uint8_t   pad1[0x40 - 0x38];
  cEntry18* mNext;                 // +0x40
};

struct cPair18 {                   // hashtable value pair<Symbol const, Group*> at node+4
  uint32_t  mKey;                  // +0x00
  cEntry18* mHead;                 // +0x04 list head
  bool RemoveEntry(cEntry18* p);   // 0x00a64750 thiscall, ret 4
  bool IsEmpty() const;            // 0x00a647a0 thiscall, no stack args
};

struct cNodeEx18 {
  cNodeEx18* next;                 // +0x00
  cPair18    value;                // +0x04
};

struct cIter18 {                   // hashtable_iterator: node + bucket
  cNodeEx18*  node;
  cNodeEx18** bucket;
};

struct cTable18 {                  // EASTL hashtable as used here
  uint32_t    pad0;
  cNodeEx18** mBuckets;            // +0x04
  uint32_t    mBucketCount;        // +0x08
  cIter18 find(const uint32_t& key);   // 0x00685f30 thiscall, sret, ret 8
  cIter18 erase(cIter18 it);           // 0x00a64cf0 thiscall, sret, ret 0xc
};

struct cEapdOwner18 {
  uint32_t    pad0;
  cTable18*   mTable;              // +0x04
  void*       mListener;           // +0x08 (vtbl slot 2 = notify(a, key, b))

  bool RemoveGroupEntry(cEntry18* p);   // 0x00a64ed0 thiscall, ret 4
};

// @ 0x00a64ed0
bool cEapdOwner18::RemoveGroupEntry(cEntry18* p) {
  cTable18* t = mTable;
  uint32_t key = p->mKey;
  cIter18 it = t->find(key);
  if (t->mBuckets[t->mBucketCount] == it.node) return false;
  bool r = it.node->value.RemoveEntry(p);
  if (it.node->value.IsEmpty()) {
    if (mListener) {
      void* obj = mListener;
      ((void (__thiscall*)(void*, uint32_t, uint32_t, uint32_t))((*(void***)obj)[2]))(obj, p->mB, key, p->mA);
    }
    cIter18 dummy = mTable->erase(it);
    (void)dummy;
  }
  return r;
}
