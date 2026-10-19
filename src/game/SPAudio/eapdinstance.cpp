// src/game/SPAudio/eapdinstance.cpp -- migrated from slice(s) s00a68140, s00a64d70 by tools/migrate/rewrite.py
// Object file: SPAudio/eapdinstance.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Random/RandomLinearCongruential.h"
#include <intrin.h>

// ---- items of slice s00a64d70 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
// ---- items of slice s00a64d70 end

// ---- items of slice s00a68140 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct GEntry {                            // object passed in: key at +0x2c
    char pad0[0x2c];
    unsigned mKey;                         // +0x2c
    unsigned mA;                           // +0x30
    unsigned mB;                           // +0x34
    char pad1[0x40 - 0x38];
    GEntry* mNext;                         // +0x40
};
struct GPair {                             // pair<Symbol const, Group*> at node+4
    unsigned mKey;
    GEntry*  mHead;
    bool RemoveEntry(GEntry* p);           // 0x00a64750 thiscall ret 4
    bool IsEmpty() const;                  // 0x00a647a0
    bool OpA(unsigned x);                  // 0x00a648f0 thiscall ret 4
    bool OpB();                            // 0x00a64950 thiscall
};
struct GNode { GNode* next; GPair value; };
struct GIter { GNode* node; GNode** bucket; };
struct GTable {
    unsigned pad0;
    GNode** mBuckets;                      // +0x04
    unsigned mBucketCount;                 // +0x08
    GIter find(const unsigned& key);       // 0x00685f30 thiscall sret ret 8
    GIter erase(GIter it);                 // 0x00a68430 thiscall sret ret 0xc
};
class GListener {
public:
    virtual void v0();
    virtual void OnA(unsigned a, unsigned b);                  // +4
    virtual void OnB(unsigned a, unsigned b, unsigned c);      // +8
    virtual void OnC(unsigned a);                              // +0xc
};
class GroupOwnerL {                        // listener at +0xc
public:
    unsigned   pad0;
    GTable*    mTable;                     // +0x04
    unsigned   pad8;
    GListener* mListener;                  // +0x0c
    bool Op1(unsigned a, unsigned b);      // va 0xa68670
    bool Op2(unsigned a);                  // va 0xa686e0
};
class GroupOwner {                         // listener at +0x08
public:
    unsigned   pad0;
    GTable*    mTable;                     // +0x04
    GListener* mListener;                  // +0x08
    bool RemoveGroupEntry(GEntry* p);      // va 0xa68740
};
struct Group {                             // value pair second: {key, head}, 8 bytes
    unsigned x;                            // +0x00
    GEntry*  head;                         // +0x04
    Group(GEntry* p);                      // 0x00a646f0 thiscall ret 4: x = p->0x34, head = p
    Group(const Group& g) : x(g.x), head(g.head) {}
    ~Group();                              // 0x00a64710
};
struct GroupPair {                         // pair<Symbol const, Group>
    unsigned key;
    Group    grp;
    GroupPair(unsigned k, const Group& g) : key(k), grp(g) {}
};
struct InsResult { GNode* node; GNode** bucket; bool ok; };
struct GPair2 { bool Push(GEntry* p); };   // 0x00a64730 thiscall ret 4 (this = node+4)
struct GNode2 { GNode2* next; GPair2 value; };
struct GIter2 { GNode2* node; GNode2** bucket; };
struct GTable3 {
    unsigned pad0;
    GNode2** mBuckets;                     // +0x04
    unsigned mBucketCount;                 // +0x08
    GIter2 find(const unsigned& key);      // 0x00685f30
    InsResult insert(const GroupPair& v, bool force);   // 0x00a684e0
};
class GListener2 {
public:
    virtual void v0();
    virtual void OnAdd(unsigned a, unsigned b, unsigned c);    // +4
};
class GroupOwner2 {
public:
    unsigned   pad0;
    GTable3*   mTable;                     // +0x04
    GListener2* mListener;                 // +0x08
    bool AddEntry(GEntry* p);              // va 0xa68990
};
// ---- items of slice s00a68140 end

// @ 0x00a64ed0
bool cEapdOwner18::RemoveGroupEntry(cEntry18* p)
{
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

// @ 0x00a68670
bool GroupOwnerL::Op1(unsigned a, unsigned b)
{
    bool r = false;
    if (mListener)
        mListener->OnA(a, b);
    GTable* t = mTable;
    GIter it = t->find(a);
    if (t->mBuckets[t->mBucketCount] != it.node)
        r = it.node->value.OpA(b);
    return r;
}

// @ 0x00a686e0
bool GroupOwnerL::Op2(unsigned a)
{
    bool r = false;
    if (mListener)
        mListener->OnC(a);
    GTable* t = mTable;
    GIter it = t->find(a);
    if (t->mBuckets[t->mBucketCount] != it.node)
        r = it.node->value.OpB();
    return r;
}

// @ 0x00a68740
bool GroupOwner::RemoveGroupEntry(GEntry* p)
{
    GTable* t = mTable;
    unsigned key = p->mKey;
    GIter it = t->find(key);
    GNode* node = it.node;
    if (t->mBuckets[t->mBucketCount] == node)
        return false;
    bool r = node->value.RemoveEntry(p);
    if (node->value.IsEmpty()) {
        if (mListener)
            mListener->OnB(p->mB, key, p->mA);
        it = mTable->erase(it);
    }
    return r;
}

// @ 0x00a68990
bool GroupOwner2::AddEntry(GEntry* p)
{
    unsigned key = p->mKey;
    GTable3* t = mTable;
    GIter2 it = t->find(key);
    if (t->mBuckets[t->mBucketCount] != it.node)
        return it.node->value.Push(p);
    {
        Group g(p);
        GroupPair v(key, g);
        t->insert(v, false);
    }
    if (mListener)
        mListener->OnAdd(p->mB, key, p->mA);
    return true;
}
