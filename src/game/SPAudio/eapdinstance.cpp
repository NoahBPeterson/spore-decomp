// src/game/SPAudio/eapdinstance.cpp -- migrated from slice(s) s00a65f90, s00a63dd0, s00a62ec0, s006860e0, s00684ee0, s00a68140, s00a64d70 by tools/migrate/rewrite.py
// Object file: SPAudio/eapdinstance.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Random/RandomLinearCongruential.h"
#include <intrin.h>
#include "EA/ResourceMan/DatabasePackedFile.h"
#include "EA/IO/FileStream.h"
#include "EA/IO/MemoryStream.h"
#include "EA/IO/SharedPointer.h"
#include "EA/Variant.h"
#include "EA/ArgScript/cArguments.h"
#include "EA/ResourceMan/KeyFilter.h"

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

// ---- items of slice s00684ee0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(_InterlockedExchangeAdd)
#pragma intrinsic(_InterlockedExchange)
void  EAFree(void* p); // 0x00f47380
struct cArguments {
  int NumArguments();            // 0x00837f30
  const char* operator[](int);   // 0x00837f20
};
struct S2 {
  bool FUN_006854b0(int param);
  void FUN_006854e0(int unused, int* param);
  void FUN_00685570(int unused, int* param);
  void FUN_006855a0(cArguments* pArgs);
  void FUN_006855f0();
  int* FUN_006859b0(int* pOut, int* pNode, int** pBucket);
  void* FUN_00685a60(void* src);
};
// ---- items of slice s00684ee0 end

// ---- items of slice s006860e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
static inline void** VT(void* p) { return *(void***)p; }
struct HashIter {
    void*  mpNode;      // +0x00
    void** mpBucket;    // +0x04
};
struct HashIterPair {
    HashIter first;     // +0x00
    uint8_t  second;    // +0x08
    uint8_t  pad[3];
};
struct Hashtable {
    char pad00[0x04];   // +0x00
    void** mpBucket;    // +0x04
    int    mnBucket;    // +0x08
    int    mnCount;     // +0x0c
    char pad10[0x08];   // +0x10..+0x17 (editor map is 0x18 bytes)
    void FreeNodes();                       // va 00685ed0
    HashIter find(const void* key);         // va 00685f30
    HashIter erase(HashIter i);             // va 006859b0
    HashIterPair insert(const void* value, const void* hint); // va 00685f90
};
static Hashtable* const gHashtable = (Hashtable*)0x0152b5f8;
// ---- items of slice s006860e0 end

// ---- items of slice s00a62ec0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Audio {
namespace Eapd {
struct PgSymbol {              // t_symbol: by-value pair (hash, name pointer)
    uint32_t    mHash;         // +0x00
    const char* mpName;        // +0x04
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern PgSymbol gFieldSymbol;        // 0x0167586c
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern PgSymbol gEmptySymbol;        // 0x01675874
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void*     canvas_getcurrent();                                       // 0x00a4a430
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void*     canvas_realizedollar2(void* out, void* glist);             // 0x00a4a5d0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
PgSymbol* GetGroupSymbol(PgSymbol* out);                             // 0x00a635d0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
PgSymbol  gFieldSymbol;         // 0x0167586c
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
PgSymbol  gEmptySymbol;         // 0x01675874
}
}
}
// ---- items of slice s00a62ec0 end

// ---- items of slice s00a63dd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Audio {
namespace Eapd {
struct AssetEntry {
    void*       mpLink0;      // +0x00
    void*       mpLink1;      // +0x04
    void*       mpField8;     // +0x08
    void*       mpFieldC;     // +0x0c
    int         mKind10;      // +0x10  1 = float, 2 = symbol/atom
    float       mFloat14;     // +0x14
    void*       mpField18;    // +0x18
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct IterHelper {
    void*       mpWord0;      // +0x00
    void*       mpWord1;      // +0x04
    void* MakeEntryIter(void* entry);   // 0x00a646f0
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct ObjectHashMap {
    void*       mpVtbl00;     // +0x00
    void*       mpBuckets04;  // +0x04  array of node pointers
    unsigned    mNumBuckets08;// +0x08
    unsigned    mSize0c;      // +0x0c
    uint32_t    mField10;     // +0x10
    uint32_t    mField14;     // +0x14
    uint32_t    mField18;     // +0x18
    void*       mpAlloc1c;    // +0x1c
    uint32_t    mCount20;     // +0x20
    void        Resize(unsigned newCount);             // 0x00a64ad0
    void        Dtor();                                // 0x00a64b70
    unsigned    Erase(uint32_t* key);                  // 0x00a64be0
    void        DisposeArray2(void** arr, unsigned n); // 0x00a64c50
    void*       Insert(void* out, void* a, void* b);   // 0x00a64cf0
    void*       GetGroup(PgSymbol sym);                // 0x00a64cb0
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct EapdAssetManager {
    void*       mpVtbl00;     // +0x00
    void*       mpAllocVtbl;  // +0x04
    void*       mpAllocator;  // +0x08
    void*       mpAlloc0c;    // +0x0c  allocator face used by +0xc calls
    void*       mpVtbl10;     // +0x10
    uint32_t    mField14;     // +0x14
    void*       mpField18;    // +0x18
    void*       mpField1c;    // +0x1c
    uint32_t    mField20;     // +0x20
    uint32_t    mField24;     // +0x24
    void*       mpFree28;     // +0x28
    uint32_t    mCounter2c;   // +0x2c
    uint32_t    mMax30;       // +0x30
    void*       mpMap34;      // +0x34
    void*       mpSent38;     // +0x38
    void*       mpHead3c;     // +0x3c
    void*       mpField40;    // +0x40
    void*       mpSent44;     // +0x44
    void*       mpSent48;     // +0x48
    void*       mpSent4c;     // +0x4c
    void*       mpSent50;     // +0x50
    uint8_t     mField54[0x74 - 0x54];

    bool        Load(const char* data, unsigned size, PgSymbol* out);          // 0x00a63dd0
    __declspec(noinline) void ReleaseEntryNode(AssetEntry* node);              // 0x00a64280
    bool        ReleaseNodeAt34(uint32_t key);                                 // 0x00a642f0
    void*       FreeSlot(void* a1, void* a2, void* a3);                        // 0x00a64390
    __declspec(noinline) AssetEntry* NewEntryNode(void* a1, void* a2);        // 0x00a643b0
    void*       AllocFromPool(void* a1);                                       // 0x00a64400
    void        DetachList(void* list, void* key);                             // 0x00a64510
    bool        FreeAll(void);                                                 // 0x00a64560
    void        RearrangeLists(void);                                          // 0x00a645c0
    void        ClearLists(void* a1);                                          // 0x00a646a0
    void        ResetAndClear(void);                                           // 0x00a64710
    bool        PushNode(void* node);                                          // 0x00a64730
    bool        RemoveNode(void* node);                                        // 0x00a64750
    bool        MakeFloatHandler(float f);                                     // 0x00a648a0
    bool        MakeSymbolHandler(const char* s);                              // 0x00a648f0
    bool        MakeListHandler(void);                                         // 0x00a64950
    void*       GetTwoWords(void* out);                                        // 0x00a649b0
    void*       RealizeDollar(void* out);                                      // 0x00a649d0
    void        DisposeArray(void** arr, unsigned n);                          // 0x00a64a50
    void        MakeFloatHandler2(uint8_t v);                                  // 0x00a64aa0
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void*   SystemGetAssetManager();                                  // 0x00a67ce0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
PgSymbol* gensym(PgSymbol* out, const char* s);                   // 0x00a675f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct HashFace { void* Find(void* out, void* key); };            // 0x00685f30 (thiscall)
}
}
}
extern "C" void* memset_f(void* d, int c, unsigned n);            // 0x011e073e
// ---- items of slice s00a63dd0 end

// ---- items of slice s00a65f90 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct NamedAllocator {
    void*       mpVtbl;   // +0x00
    int         mA;       // +0x04
    const char* mpName;   // +0x08
};
class FixedPool {
public:
    NamedAllocator mInitAllocator;       // +0x00
    NamedAllocator mOverflowAllocator;   // +0x0c
    uint32_t  mnNodeSize;                // +0x18
    void*     mpPoolBegin;               // +0x1c
    void*     mpPoolEnd;                 // +0x20
    void*     mpHead;                    // +0x24
    uint32_t  mnCurrentSize;             // +0x28
    uint32_t  mnPeakSize;                // +0x2c
    bool Init(uint32_t nodeSize, uint32_t count, void* a1, void* a2);   // 0xa53210
    ~FixedPool();                                                       // 0xa531b0
};
class FixedHashtableAllocator : public FixedPool {
public:
    uint32_t mnBucketCount;              // +0x30
    void*    mpBucketBuffer;             // +0x34
    bool InitTables(uint32_t a, uint32_t b, uint32_t c, uint32_t d); // 0xa669d0
    void DestroyAllocator();                                         // 0xa67d30
};
struct HashNode { uint32_t mKey; void* mValue; HashNode* mpNext; };
struct HashIter_s00a6_5f90 { HashNode* mpNode; HashNode** mpBucket; HashNode* mpEnd; };
class Hashtable_s00a6_5f90 {
public:
    uint32_t   mFunctors;                 // +0x00
    HashNode** mpBucketArray;             // +0x04
    uint32_t   mnBucketCount;             // +0x08
    uint32_t   mnElementCount;            // +0x0c
    float      mfMaxLoadFactor;           // +0x10
    uint32_t   mnGrowthFactor;            // +0x14
    uint32_t   mnNextResize;              // +0x18
    FixedHashtableAllocator mAlloc;       // +0x1c

    Hashtable_s00a6_5f90* Construct(void* name);                                 // 0xa665f0
    void      Destruct();                                             // 0xa66550
    void      ClearBuckets(HashNode** arr, uint32_t n);               // 0xa660e0
    HashIter_s00a6_5f90  erase(HashIter_s00a6_5f90 it);                                     // 0xa66cc0
    void      Rehash(uint32_t n);                                     // 0xa66b40
};
class InstanceManager {
public:
    void*          mpObj;                    // +0x00
    void*          mpVtbl4;                  // +0x04
    NamedAllocator mAllocA;                  // +0x08
    NamedAllocator mAllocB;                  // +0x14
    uint32_t       mField20;                 // +0x20
    uint32_t       mField24;                 // +0x24
    uint32_t       mField28;                 // +0x28
    uint32_t       mField2c;                 // +0x2c
    uint32_t       mField30;                 // +0x30
    uint32_t       mField34;                 // +0x34
    void*          mField38;                 // +0x38
    Hashtable_s00a6_5f90      mSymbols;                 // +0x3c  (PatchMap)
    Hashtable_s00a6_5f90      mBindings;                // +0x90  (InstanceMap)
    uint32_t       mCurId;                   // +0xe4
    uint32_t       mCurId2;                  // +0xe8

    bool      Init(uint32_t size, uint32_t a2, uint32_t a3);  // 0xa65f90
    bool      FlushAll();                                     // 0xa65fe0
    void*     InsertParam(void* out, uint32_t* key);          // 0xa66070
    uint32_t  AddInstance(uint32_t glist);                    // 0xa66300
    void      Construct(void* a, void* b);                    // 0xa66780
    ~InstanceManager();                                       // 0xa66670
};
struct CursorLink {
    void*       mpValue;   // +0x00  (record whose +8 field is an instance id)
    CursorLink* mpNext;    // +0x04  (intrusive link; == this when the list ends)
};
struct CursorValue {
    uint32_t mKey;     // +0x00
    uint32_t mValue;   // +0x04
};
struct CursorIter {
    void* mpNode;      // +0x00  (node, or the bucket-array sentinel)
    void* mpTable;     // +0x04
};
struct InsertResult {
    void*    mpNode;        // +0x00
    uint32_t mBucketIndex;  // +0x04
    uint8_t  mbInserted;    // +0x08
};
struct CursorTable {
    void*    mpAllocVtbl;    // +0x00
    void**   mpBucketArray;  // +0x04
    uint32_t mnBucketCount;  // +0x08
    CursorIter  FindNode(const void* value);                         // 0xdb4780 (thiscall)
    void        Insert(InsertResult* out, const CursorValue* v, bool bInsert);  // 0xa65ed0
    CursorValue* InsertIfAbsent(const CursorValue* value);           // 0xa66170
};
struct InstanceReleaser {
    void Remove(int id);                            // 0xa65cd0 (thiscall)
};
struct InstanceResetter {
    void Reset(uint32_t a, uint32_t b, uint32_t c, uint32_t d);   // 0xa655f0 (thiscall)
};
struct CursorNode {
    CursorNode* mpNext;   // +0x00
    CursorNode* mpPrev;   // +0x04
    uint32_t    mnId;     // +0x08  (instance id)
};
struct CursorListHead {
    CursorNode* mpNext;   // +0x00
    CursorNode* mpPrev;   // +0x04
};
class CursorRegistry {
public:
    void*       mpVtbl;      // +0x00
    void*       mpField4;    // +0x04
    char        pad08[0x34]; // +0x08 .. +0x3b
    CursorTable mCursors;    // +0x3c
    char        pad48[0x9c]; // +0x48 .. +0xe3
    uint32_t    mnCurId;     // +0xe4
    uint32_t    mnCurId2;    // +0xe8
    void RemoveAllFor(void* key, int unused);            // 0xa663e0
    void RemoveCurrentClass(CursorValue value);          // 0xa66410
};
void  PdPatchMapInit(void* self, const char* name);               // 0xa666e0
void  PdInstanceMapInit(void* self, const char* name);            // 0xa66260
void  PdClassResize(void* self, uint32_t a);                      // 0xa65ab0
// ---- items of slice s00a65f90 end

// @ 0x006859b0
int* S2::FUN_006859b0(int* pOut, int* pNode, int** pBucket)
{
  int iVar1 = pNode[3];
  pOut[1] = (int)pBucket;
  pOut[0] = iVar1;
  while (iVar1 == 0) {
    pOut[1] += 4;
    iVar1 = *(int*)pOut[1];
    pOut[0] = iVar1;
  }
  int* p = *pBucket;
  if (p != pNode) {
    int* q = (int*)p[3];
    while (q != pNode) {
      p = q;
      q = (int*)q[3];
    }
    p[3] = q[3];
    EAFree(pNode);
    *(int*)((char*)this + 0xc) -= 1;
    return pOut;
  }
  *pBucket = (int*)p[3];
  EAFree(pNode);
  *(int*)((char*)this + 0xc) -= 1;
  return pOut;
}

// @ 0x006861d0
extern "C" void EraseEntry(void* key)
{
    HashIter it = gHashtable->find(&key);
    if (it.mpNode != (void*)(*(int*)(*(int*)0x0152b5fc + *(int*)0x0152b600 * 4))) {
        void* p = *(void**)((char*)it.mpNode + 4);
        ((void (__thiscall*)(void*))VT(p)[0x24 / 4])(p);
        int* rc = (int*)((char*)it.mpNode + 8);
        *rc = *rc - 1;
        if (*rc == 0) {
            ((void (__thiscall*)(void*))VT(p)[8 / 4])(p);
            it = gHashtable->erase(it);
        }
    }
}

// @ 0x00a635d0
namespace EA { namespace Audio { namespace Eapd {
PgSymbol* GetGroupSymbol(PgSymbol* out)
{
    uint32_t    emptyH = gEmptySymbol.mHash;
    uint32_t    fieldH = gFieldSymbol.mHash;
    const char* emptyN = gEmptySymbol.mpName;
    out->mHash = emptyH;
    out->mpName = emptyN;
    if (emptyH != fieldH) {
        out->mHash = fieldH;
        out->mpName = gFieldSymbol.mpName;
        gFieldSymbol.mHash = emptyH;
        gFieldSymbol.mpName = emptyN;
        return out;
    }
    void* canvas = canvas_getcurrent();
    if (canvas != 0) {
        PgSymbol tmp;
        PgSymbol* r = (PgSymbol*)canvas_realizedollar2(&tmp, canvas);
        out->mHash = r->mHash;
        out->mpName = r->mpName;
    }
    return out;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a643b0
namespace EA { namespace Audio { namespace Eapd {
AssetEntry* EapdAssetManager::NewEntryNode(void* a1, void* a2)
{
    AssetEntry* n = (AssetEntry*)((void* (__thiscall*)(void*, unsigned))
        ((*(void***)((char*)this + 0xc))[2]))((char*)this + 0xc, 0x1c);
    if (n != 0) {
        n->mpLink1 = 0;
        n->mpLink0 = 0;
        n->mpFieldC = a1;
        n->mpField8 = a2;
        char* head = (char*)this + 0x4c;
        n->mpLink1 = *(void**)(head + 4);
        n->mpLink0 = head;
        *(void**)(head + 4) = n;
        *(void**)(*(void**)((char*)n + 4)) = n;
    }
    return n;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a64510
namespace EA { namespace Audio { namespace Eapd {
void EapdAssetManager::DetachList(void* key, void* list)
{
    char* head = (char*)list;
    char* cur = *(char**)head;
    if (cur != head) {
        do {
            char* node = cur;
            cur = *(char**)cur;
            if (*(void**)(node + 0xc) == key) {
                void* prev = *(void**)(node + 4);
                void* nx = *(void**)node;
                *(void**)prev = nx;
                *(void**)((char*)nx + 4) = prev;
                *(void**)node = 0;
                *(void**)(node + 4) = 0;
                char* alloc = (char*)this + 0xc;
                void** vtbl = *(void***)alloc;
                ((void (__thiscall*)(void*, void*))vtbl[3])(alloc, node);
            }
        } while (cur != head);
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a646a0
namespace EA { namespace Audio { namespace Eapd {
__declspec(noinline) void EapdAssetManager::ClearLists(void* a1)
{
    DetachList(a1, (char*)this + 0x44);
    DetachList(a1, (char*)this + 0x4c);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a646f0
namespace EA { namespace Audio { namespace Eapd {
void* IterHelper::MakeEntryIter(void* entry)
{
    void* self = this;
    *(void**)self = *(void**)((char*)entry + 0x34);
    *(void**)((char*)self + 4) = entry;
    return self;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a64710
namespace EA { namespace Audio { namespace Eapd {
__declspec(noinline) void EapdAssetManager::ResetAndClear()
{
    void* sys = SystemGetAssetManager();
    ((EapdAssetManager*)sys)->ClearLists(this);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a64730
namespace EA { namespace Audio { namespace Eapd {
bool EapdAssetManager::PushNode(void* node)
{
    bool ok = false;
    if (*(void**)((char*)node + 0x34) == *(void**)this) {
        *(void**)((char*)node + 0x40) = *(void**)((char*)this + 4);
        *(void**)((char*)this + 4) = node;
        ok = true;
    }
    return ok;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a64750
namespace EA { namespace Audio { namespace Eapd {
bool EapdAssetManager::RemoveNode(void* node)
{
    bool ok = false;
    if (node) {
        char* head = *(char**)((char*)this + 4);
        if (head == node) {
            *(void**)((char*)this + 4) = *(void**)(head + 0x40);
            ok = true;
        } else {
            char* cur = *(char**)(head + 0x40);
            if (cur) {
                char* prev = head;
                do {
                    if (cur == node) {
                        *(void**)(prev + 0x40) = *(void**)(cur + 0x40);
                        ok = true;
                        break;
                    }
                    prev = cur;
                    cur = *(char**)(cur + 0x40);
                } while (cur);
            }
        }
    }
    return ok;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a648a0
namespace EA { namespace Audio { namespace Eapd {
bool EapdAssetManager::MakeFloatHandler(float f)
{
    bool ok = false;
    if (*(int*)this == 0) {
        void* sys = SystemGetAssetManager();
        AssetEntry* e = ((EapdAssetManager*)sys)->NewEntryNode(this, (void*)0xa647b0);
        if (e) {
            e->mKind10 = 1;
            e->mFloat14 = f;
            ok = true;
        }
    }
    return ok;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a648f0
namespace EA { namespace Audio { namespace Eapd {
bool EapdAssetManager::MakeSymbolHandler(const char* s)
{
    bool ok = false;
    if (*(int*)this == 1) {
        PgSymbol sym;
        gensym(&sym, s);
        void* sys = SystemGetAssetManager();
        AssetEntry* e = ((EapdAssetManager*)sys)->NewEntryNode(this, (void*)0xa64820);
        if (e) {
            e->mKind10 = 2;
            *(unsigned*)&e->mFloat14 = sym.mHash;
            e->mpField18 = (void*)sym.mpName;
            ok = true;
        }
    }
    return ok;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a64950
namespace EA { namespace Audio { namespace Eapd {
bool EapdAssetManager::MakeListHandler(void)
{
    bool ok = false;
    if (*(int*)this == 2) {
        void* sys = SystemGetAssetManager();
        void* e = ((EapdAssetManager*)sys)->NewEntryNode(this, (void*)0xa64870);
        if (e)
            ok = true;
    }
    return ok;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a64a50
namespace EA { namespace Audio { namespace Eapd {
void EapdAssetManager::DisposeArray(void** arr, unsigned n)
{
    for (unsigned i = 0; i < n; ++i) {
        char* node = (char*)arr[i];
        if (node) {
            char* alloc = (char*)this + 0x1c;
            while (node) {
                char* cur = node;
                node = *(char**)(node + 0xc);
                void** vtbl = *(void***)alloc;
                ((void (__thiscall*)(void*, void*))vtbl[3])(alloc, cur);
            }
        }
        arr[i] = 0;
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a64ad0
namespace EA { namespace Audio { namespace Eapd {
void ObjectHashMap::Resize(unsigned newCount)
{
    unsigned oldCount = mNumBuckets08;
    unsigned* oldBuckets = (unsigned*)mpBuckets04;
    void* alloc = (char*)this + 0x1c;
    void** vtbl = *(void***)alloc;
    void* fn = vtbl[2];
    unsigned* nb = (unsigned*)((void* (__thiscall*)(void*, unsigned))fn)(alloc, newCount * 4 + 4);
    memset_f(nb, 0, newCount * 4);
    nb[newCount] = 0xffffffff;
    unsigned i = 0;
    unsigned* newb = nb;
    if (oldCount > 0) {
        do {
            unsigned* n = (unsigned*)oldBuckets[i];
            if (n) {
                unsigned* b = newb;
                do {
                    unsigned h = *n % newCount;
                    unsigned* next = (unsigned*)((char*)n + 0xc);
                    unsigned* node = n;
                    mpBuckets04 = 0;
                    oldBuckets[i] = (unsigned)*(unsigned**)((char*)n + 0xc);
                    node = n;
                    unsigned* slot = b + h;
                    *(unsigned**)((char*)n + 0xc) = (unsigned*)*slot;
                    *slot = (unsigned)n;
                    n = (unsigned*)oldBuckets[i];
                } while (n);
            }
            ++i;
        } while (i < oldCount);
    }
    if (oldCount > 1) {
        void** a2 = *(void***)((char*)this + 0x1c);
        void* f2 = a2[3];
        ((void (__thiscall*)(void*, void*))f2)((char*)this + 0x1c, oldBuckets);
    }
    mpBuckets04 = nb;
    mNumBuckets08 = newCount;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a64b70
namespace EA { namespace Audio { namespace Eapd {
void ObjectHashMap::Dtor()
{
    ((EapdAssetManager*)this)->DisposeArray((void**)mpBuckets04, mNumBuckets08);
    mSize0c = 0;
    if (mNumBuckets08 > 1) {
        void** a = *(void***)((char*)this + 0x1c);
        void* f = a[3];
        ((void (__thiscall*)(void*, void*))f)((char*)this + 0x1c, mpBuckets04);
    }
    *(void**)((char*)this + 0x1c) = (void*)0x1403934;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a64be0
namespace EA { namespace Audio { namespace Eapd {
unsigned ObjectHashMap::Erase(uint32_t* key)
{
    unsigned before = mSize0c;
    unsigned idx = *key % mNumBuckets08;
    unsigned** bucket = (unsigned**)((char*)mpBuckets04 + idx * 4);
    if (*bucket) {
        unsigned* cur = *bucket;
        while (*cur != *key) {
            bucket = (unsigned**)((char*)cur + 0xc);
            cur = *bucket;
            if (!cur)
                break;
        }
        while (*bucket) {
            unsigned* node = *bucket;
            if (*node != *key)
                break;
            *bucket = *(unsigned**)((char*)node + 0xc);
            void** a = *(void***)((char*)this + 0x1c);
            void* f = a[3];
            ((void (__thiscall*)(void*, void*))f)((char*)this + 0x1c, node);
            --mSize0c;
        }
    }
    return before - mSize0c;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a64c50
namespace EA { namespace Audio { namespace Eapd {
void ObjectHashMap::DisposeArray2(void** arr, unsigned n)
{
    for (unsigned i = 0; i < n; ++i) {
        char* node = (char*)arr[i];
        if (node) {
            char* alloc = (char*)this + 0x1c;
            while (node) {
                char* cur = node;
                node = *(char**)(node + 0xc);
                ((EapdAssetManager*)(cur + 4))->ResetAndClear();
                void** vtbl = *(void***)alloc;
                ((void (__thiscall*)(void*, void*))vtbl[3])(alloc, cur);
            }
        }
        arr[i] = 0;
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a64cb0
namespace EA { namespace Audio { namespace Eapd {
void* ObjectHashMap::GetGroup(PgSymbol sym)
{
    char* cont = (char*)this + 0xc;
    void* r = 0;
    void* found[2];
    ((HashFace*)cont)->Find(found, &sym);
    unsigned idx = *(unsigned*)(cont + 8);
    void** b = *(void***)(cont + 4);
    if (b[idx] != found[0])
        r = *(void**)((char*)found[0] + 8);
    return r;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a64cf0
namespace EA { namespace Audio { namespace Eapd {
void* ObjectHashMap::Insert(void* out, void* node, void* bucketPtr)
{
    void* first = *(void**)((char*)node + 0xc);
    *(void**)((char*)out + 4) = bucketPtr;
    *(void**)out = first;
    while (*(void**)out == 0) {
        void* p = (char*)*(void**)((char*)out + 4) + 4;
        *(void**)((char*)out + 4) = p;
        *(void**)out = *(void**)p;
    }
    void* c = *(void**)bucketPtr;
    if (c == node) {
        *(void**)bucketPtr = *(void**)((char*)c + 0xc);
    } else {
        void* a = *(void**)((char*)c + 0xc);
        while (a != node) {
            c = a;
            a = *(void**)((char*)c + 0xc);
        }
        *(void**)((char*)c + 0xc) = *(void**)((char*)a + 0xc);
    }
    ((EapdAssetManager*)((char*)node + 4))->ResetAndClear();
    void** a2 = *(void***)((char*)this + 0x1c);
    void* f = a2[3];
    ((void (__thiscall*)(void*, void*))f)((char*)this + 0x1c, node);
    --mSize0c;
    return out;
}
}}}  // namespace EA::Audio::Eapd

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

// @ 0x00a66300
uint32_t InstanceManager::AddInstance(uint32_t glist)
{
    uint32_t id = mCurId;
    mCurId2 = id;
    ++mCurId;
    void* a = &mAllocA;
    void* obj = ((void* (__thiscall*)(void*, uint32_t))(*(void***)a)[2])(a, 0x78);
    if (obj)
        (void)glist;
    return id;
}

// @ 0x00a663e0
void CursorRegistry::RemoveAllFor(void* key, int unused)
{
    CursorLink* node = (CursorLink*)mCursors.InsertIfAbsent((const CursorValue*)&key);
    while (node->mpNext != node)
        ((InstanceReleaser*)this)->Remove(*(int*)((char*)node->mpValue + 8));
    (void)unused;
}

// @ 0x00a66410
void CursorRegistry::RemoveCurrentClass(CursorValue value)
{
    uint32_t saved = mnCurId;
    CursorListHead local;
    local.mpNext = (CursorNode*)&local;
    local.mpPrev = (CursorNode*)&local;

    CursorListHead* head = (CursorListHead*)mCursors.InsertIfAbsent(&value);

    // Swap the per-key list with the local head, then repair both ends.
    CursorNode* hn = head->mpNext;
    CursorNode* hp = head->mpPrev;
    CursorNode* ln = local.mpNext;
    CursorNode* lp = local.mpPrev;
    head->mpNext = ln;
    head->mpPrev = lp;
    local.mpNext = hn;
    local.mpPrev = hp;

    if (local.mpNext == (CursorNode*)head) {
        local.mpNext = (CursorNode*)&local;
        local.mpPrev = (CursorNode*)&local;
    } else {
        local.mpPrev->mpNext = (CursorNode*)&local;
        local.mpNext->mpPrev = (CursorNode*)&local;
    }

    if (head->mpNext == (CursorNode*)&local) {
        head->mpNext = (CursorNode*)head;
        head->mpPrev = (CursorNode*)head;
    } else {
        head->mpPrev->mpNext = (CursorNode*)head;
        head->mpNext->mpPrev = (CursorNode*)head;
    }

    while (local.mpPrev != (CursorNode*)&local) {
        uint32_t id = local.mpNext->mnId;
        ((InstanceReleaser*)this)->Remove((int)id);
        mnCurId = id;
        mnCurId2 = 0xFFFFFFFFu;
        ((InstanceResetter*)this)->Reset(value.mKey, (uint32_t)value.mValue, 0, 0);
    }

    mnCurId = saved;
}

// @ 0x00a665f0
Hashtable_s00a6_5f90* Hashtable_s00a6_5f90::Construct(void* name)
{
    mnBucketCount = 0;
    mnElementCount = 0;
    mfMaxLoadFactor = 1.0f;
    mnGrowthFactor = 2;
    mnNextResize = 0;
    PdClassResize(&mAlloc, (uint32_t)name);
    mnElementCount = 0;
    mnNextResize = 0;
    mnBucketCount = 1;
    mpBucketArray = (HashNode**)0x154df28;
    return this;
}

// @ 0x00a66780
void InstanceManager::Construct(void* a, void* b)
{
    mpObj = a;
    mAllocA.mpVtbl = (void*)0x1454fac;
    mAllocA.mA = 0;
    mAllocA.mpName = "EAPd/InstanceManager";
    mAllocB.mpVtbl = (void*)0x1454fac;
    mAllocB.mA = 0;
    mAllocB.mpName = "EAPd/InstanceManager";
    mField20 = 0;
    mField24 = 0;
    mField28 = 0;
    mField2c = 0;
    mField30 = 0;
    mField34 = 0;
    mpVtbl4 = (void*)0x14556c0;
    mField38 = b;
    PdPatchMapInit((char*)this + 0x3c, "EAPd/PatchMap");
    PdInstanceMapInit((char*)this + 0x90, "EAPd/InstanceMap");
    mCurId = 0;
    mCurId2 = 0xffffffff;
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
