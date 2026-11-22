// src/game/SPAudio/eapdinstance.cpp -- migrated from slice(s) s00a65f90, s00a63dd0, s00a62ec0, s006860e0, s00684ee0, s00a68140, s00a64d70 by tools/migrate/rewrite.py
// Object file: SPAudio/eapdinstance.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

// addresses retail relocates here, named so the build relocates them too
extern "C" void FUN_00a647b0();
extern "C" void FUN_00a64820();
extern "C" void FUN_00a64870();

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

// Hand-kept views for the 0x00a64cf0/0x00a64ed0 rows (landed earlier from another slice).  They sit outside the
// slice block because rewrite.py drops an item that only other items use (cNodeEx18/cPair18 are used by cIter18 only).
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
extern PgSymbol gEmptySymbol;        // 0x0167589c
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern PgSymbol gEmptySymbol_s00a6_2ec0;        // 0x01675874
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
    unsigned    Erase(uint32_t* key);                  // 0x00a64be0
    void        DisposeArray2(void** arr, unsigned n); // 0x00a64c50
    void*       Insert(void* out, void* a, void* b);   // 0x00a64cf0
    void*       GetGroup(PgSymbol sym);                // 0x00a64cb0
};
// the destructor's view of ObjectHashMap: the buckets are disposed and their array handed back to the internal
// allocator at +0x1c, whose base vtable (0x1403934) is restored when the member is destroyed
struct ObjectHashMapAlloc {
    virtual void Slot0();
    virtual void Slot1();
    virtual void* Alloc(unsigned n);
    virtual void Free(void* p);
    uint32_t mCount;          // +0x04
    ~ObjectHashMapAlloc() {}
};
struct ObjectHashMapObj {
    void*       mpVtbl00;     // +0x00
    void*       mpBuckets04;  // +0x04
    unsigned    mNumBuckets08;// +0x08
    unsigned    mSize0c;      // +0x0c
    uint32_t    mField10;     // +0x10
    uint32_t    mField14;     // +0x14
    uint32_t    mField18;     // +0x18
    ObjectHashMapAlloc mAlloc;// +0x1c
    ~ObjectHashMapObj();
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
    void CopyFrom(const void* src);                                  // 0xa65ab0
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
    float      mfGrowthFactor;            // +0x14
    uint32_t   mnNextResize;              // +0x18
    FixedHashtableAllocator mAlloc;       // +0x1c

    Hashtable_s00a6_5f90* Construct(void* name);                                 // 0xa665f0
    void      Destruct();                                             // 0xa66550
    void      PatchMapInit(const char* name);                         // 0xa666e0
    void      InstanceMapInit(const char* name);                      // 0xa66260
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
// ---- items of slice s00a65f90 end

// ---- items of slice s00a64d70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" char g_1403934[];
extern "C" char g_1455648[];
extern "C" char g_1454fac[];
extern "C" char g_1455668[];
namespace EA {
namespace Audio {
namespace Eapd {
struct NamedAllocator_s00a6_4d70 {
    void*       mpVtbl;   // +0x00
    int         mA;       // +0x04
    const char* mpName;   // +0x08
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
class FixedPool_s00a6_4d70 {
public:
    NamedAllocator_s00a6_4d70 mInitAllocator;       // +0x00
    NamedAllocator_s00a6_4d70 mOverflowAllocator;   // +0x0c
    uint32_t  mnNodeSize;                // +0x18
    void*     mpPoolBegin;               // +0x1c
    void*     mpPoolEnd;                 // +0x20
    void*     mpHead;                    // +0x24
    uint32_t  mnCurrentSize;             // +0x28
    uint32_t  mnPeakSize;                // +0x2c

    bool  Init(uint32_t nodeSize, uint32_t count, void* a1, void* a2);  // 0xa53210
    void* AllocSize(uint32_t size);                                     // vtable slot 2
    void* AllocNode();                                                  // pool head pop
    void* AllocPooled();                                                // overflow vtbl[2](nodeSize)
    void  Free(void* node);                                             // pool push
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
class FixedHashtableAllocator_s00a6_4d70 : public FixedPool_s00a6_4d70 {
public:
    uint32_t mnBucketCount;              // +0x30
    void*    mpBucketBuffer;             // +0x34

    bool  InitBuckets(uint32_t a, uint32_t b, uint32_t c);   // 0xa53360
    bool  InitBucketsEx(uint32_t size, uint32_t a1, uint32_t a2); // 0xa656b0
    bool  InitPool(uint32_t a, uint32_t b, uint32_t c);      // legacy
    void* AllocNode();                                       // pop a pooled node
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
class PoolFreeView {
public:
    uint32_t  mPad00;     // +0x00
    FixedPool_s00a6_4d70 mPool;      // +0x04
    void FreeNode(void* node);   // 0xa65800
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct HashNode16 {
    uint32_t mKey;        // +0x00
    uint32_t mV1;         // +0x04
    uint32_t mV2;         // +0x08
    HashNode16* mpNext;   // +0x0c
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct InsertResult_s00a6_4d70 {
    void*    mpNode;        // +0x00
    void*    mpBucket;      // +0x04
    uint8_t  mbInserted;    // +0x08
    uint8_t  pad09[3];
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
class Hashtable_s00a6_4d70 {
public:
    uint8_t    pad00[0x04];               // +0x00
    HashNode16** mpBucketArray;           // +0x04
    uint32_t   mnBucketCount;             // +0x08
    uint32_t   mnElementCount;            // +0x0c
    float      mfMaxLoadFactor;           // +0x10
    uint32_t   mnGrowthFactor;            // +0x14
    uint32_t   mnNextResize;              // +0x18
    // The small table embeds only a 12-byte allocator face (vtable, field,
    // name) at +0x1c; the table itself is 0x28 bytes.  The 0x30-byte FixedPool
    // is only used by the big tables.
    NamedAllocator_s00a6_4d70 mPool;                 // +0x1c

    __declspec(noinline) Hashtable_s00a6_4d70* Construct(const void* nameSlot);   // 0xa64f80
    __declspec(noinline) Hashtable_s00a6_4d70* InitNamed(void* nameSlot, const char* name); // 0xa65180
    __declspec(noinline) void Dispose();                        // 0xa65000
    void       Finalize();                                      // 0xa64b70
    void       BaseDtor();                                      // 0xa651e0
    void       Insert(InsertResult_s00a6_4d70* out, const HashNode16* pair,
                      const uint32_t* pKey);                    // 0xa64d70
    uint32_t   Erase(uint32_t* key);                            // 0xa64be0
    void       DisposeArray2(void** arr, uint32_t n);           // 0xa64c50
    void       ResizeBuckets(uint32_t newCount);                // 0xa64ad0
    void       FindNode(HashNode16** out, const uint32_t* key);// 0x685f30
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct HashPolicy {
    float      mfMaxLoad;    // +0x00
    uint32_t   mnGrow;       // +0x04
    uint32_t   mnNextResize; // +0x08
    // 0x921440: pick the next bucket count (out[0]=changed flag, out[1]=count)
    void NextBucketCount(uint32_t* out, uint32_t bucketCount,
                         uint32_t elementCount, uint32_t force);   // 0x921440
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct HashNode20 {
    uint32_t mKey;        // +0x00
    uint32_t mV1;         // +0x04
    uint32_t mV2;         // +0x08
    uint32_t mV3;         // +0x0c
    HashNode20* mpNext;   // +0x10
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
class HashtableBig {
public:
    uint8_t    pad00[0x04];               // +0x00
    HashNode20** mpBucketArray;           // +0x04
    uint32_t   mnBucketCount;             // +0x08
    uint32_t   mnElementCount;            // +0x0c
    float      mfMaxLoadFactor;           // +0x10
    uint32_t   mnGrowthFactor;            // +0x14
    uint32_t   mnNextResize;              // +0x18
    FixedHashtableAllocator_s00a6_4d70 mAlloc;       // +0x1c

    void*  AllocBuckets(uint32_t n);                             // 0xa65830
    void*  AllocBuckets20(uint32_t n);                           // 0xa65960
    void*  Find(void** out, const uint32_t* key);                // 0xa3b2c0
    void*  Rehash16(uint32_t newCount);                          // 0xa658b0
    void*  Rehash20(uint32_t newCount);                          // 0xa659e0
    void*  EraseFn(void* out, void* node, void** bucket);        // 0xa65b10
    void*  AllocNode(const void* value);                         // 0xa65c70
    bool   InitPool10(uint32_t a, uint32_t b, uint32_t c);       // 0xa65db0
    bool   InitPool20(uint32_t a, uint32_t b, uint32_t c);       // 0xa65e40
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
class GroupMap {
public:
    void*      mpVtbl;     // +0x00
    GroupMap*  mpSelf;     // +0x04
    uint32_t   mField08;   // +0x08
    uint32_t   mField0c;   // +0x0c
    Hashtable_s00a6_4d70  mGroups;    // +0x10

    __declspec(noinline) GroupMap* GroupMapCtor(void* nameSlot);   // 0xa654a0
    void       DisposeInner();                               // 0xa651e0
    GroupMap*  ScalarDtor(uint32_t flags);                   // 0xa65500
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct VtblOwner { void* DispatchSlot2(void* arg, void* unused); };
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct Copyable38 {
    uint32_t mW[14];        // +0x00 .. +0x37
    Copyable38* CopyCtor(const Copyable38* src);
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
class Instance {
public:
    void*      mpVtbl;       // +0x00
    uint32_t   mField04;     // +0x04
    const char* mpClassName; // +0x08
    Hashtable_s00a6_4d70  mGroups;      // +0x0c  the Instance/Group table
    GroupMap   mGroupMap;    // +0x34
    uint32_t   mField6c;     // +0x6c
    void*      mpCanvas;     // +0x70
    uint8_t    mField74;     // +0x74  (original writes a single byte here)
    uint8_t    mPad75[3];    // +0x75

    Instance*  InstanceCtor(void* sys, void* a3, void* a4);   // 0xa65560
    void       Destroy();                                     // 0xa65230
    void*      CreateGroup(uint32_t* sym, void* a3, void* a4, uint32_t a5); // 0xa65360
    void       FreeGroup(uint32_t key, uint32_t unused, void* group); // 0xa65470
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
class InstanceManager_s00a6_4d70 {
public:
    void*      mpVtbl;       // +0x00
    uint32_t   mField04;     // +0x04
    void*      mpAlloc08;    // +0x08
    uint32_t   mField0c;     // +0x0c
    float      mfMaxLoad10;  // +0x10
    uint32_t   mnGrow14;     // +0x14
    uint32_t   mnNextResize18; // +0x18
    uint8_t    pad1c[0x3c - 0x1c];
    HashtableBig mSymbols;   // +0x3c  (PatchMap)
    HashtableBig mBindings;  // +0x90  (InstanceMap)
    uint32_t   mCurId;       // +0xe4
    uint32_t   mCurId2;      // +0xe8

    __declspec(noinline) uint32_t CreateCanvas(void* a2, void* a3, uint32_t a4, uint32_t a5); // 0xa655f0
    bool       CanvasOrId(void* a2, void* a3, uint32_t* out); // 0xa657a0
    bool       RemoveInstance(uint32_t id);                   // 0xa65cd0
    void*      FindInstance(uint32_t id);                     // 0xa65d60
};
}
}
}
class AnyGroup {
public:
    void*    mpSamples;   // +0x00  the group's sample list
    uint32_t mField04;    // +0x04
    uint32_t mField08;    // +0x08
    void*    mpVtbl0c;    // +0x0c  vtable face of the trailing sub-object

    bool Init(uint32_t* sym, void* a3, void* a4, uint32_t a5);  // 0xa52ff0
    void Destroy();                                             // 0xa52af0
};
class GroupHelp {
public:
    void* Init(void* owner);    // 0xa52f70
};
uint32_t FUN_00921340(uint32_t n);                                   // 0x00921340
uint32_t MakeFloatHandler(void* self, float f);                      // 0xa648a0
uint32_t PushNode(void* self);                                       // 0xa64730
void*    MakeEntryIter(void* self);                                  // 0xa646f0
void     ResetAndClear(void* self);                                  // 0xa64710
void  pd_free(void* p);                                              // 0xa493d0
void* Eapd_GetOwnerA();                                              // 0xa67ce0
class EapdOwner {
public:
    void ClearLists(void* instance);    // 0xa646a0
};
class SymbolDispatchSlot {
public:
    uint32_t   mField00;    // +0x00
    EA::Audio::Eapd::Hashtable_s00a6_4d70* mpMap;       // +0x04   the small symbol table
    uint32_t   mField08;    // +0x08
    void*      mpTarget;    // +0x0c   interface with a vtable

    uint32_t Dispatch(uint32_t sym, float f);   // 0xa64e60
};
class GroupAdder {
public:
    uint32_t mField00;      // +0x00
    EA::Audio::Eapd::Hashtable_s00a6_4d70* mpMap;       // +0x04   the small symbol table
    void*    mpListener;    // +0x08   notified via vtbl[1]

    uint32_t AddGroup(void* group);     // 0xa65070
};
void* EA::Audio::Eapd::FixedPool_s00a6_4d70::AllocSize(uint32_t size)
{
    typedef void* (__thiscall* Fn)(void*, uint32_t);
    return ((Fn)(*(void***)this)[2])(this, size);
}
void* EA::Audio::Eapd::FixedPool_s00a6_4d70::AllocPooled()
{
    typedef void* (__thiscall* Fn)(void*, uint32_t);
    return ((Fn)(*(void***)&mOverflowAllocator)[2])(&mOverflowAllocator, mnNodeSize);
}
void* EA::Audio::Eapd::HashtableBig::Rehash16(uint32_t newCount)
{
    void** newBuckets = (void**)AllocBuckets(newCount);
    uint32_t i = 0;
    if (mnBucketCount > i)
    {
        do
        {
            void* node = mpBucketArray[i];
            while (node)
            {
                uint32_t h = *(uint32_t*)node % newCount;
                EA::Audio::Eapd::HashNode20* next = *(EA::Audio::Eapd::HashNode20**)((char*)node + 0x10);
                mpBucketArray[i] = next;
                *(void**)((char*)node + 0x10) = newBuckets[h];
                newBuckets[h] = node;
                node = mpBucketArray[i];
            }
            ++i;
        } while (i < mnBucketCount);
    }
    void** old = (void**)mpBucketArray;
    if (mnBucketCount > 1 && old != (void**)mAlloc.mpBucketBuffer)
    {
        --mAlloc.mnCurrentSize;
        if (old >= (void**)mAlloc.mpPoolBegin && old < (void**)mAlloc.mpPoolEnd)
        {
            *old = mAlloc.mpHead;
            mAlloc.mpHead = old;
        }
        else
        {
            typedef void (__thiscall* Fn)(void*, void*);
            ((Fn)(*(void***)&mAlloc.mOverflowAllocator)[3])(&mAlloc.mOverflowAllocator, old);
        }
    }
    mpBucketArray = (EA::Audio::Eapd::HashNode20**)newBuckets;
    mnBucketCount = newCount;
    /* retail returns the OLD bucket array (the value left in eax by the free
       path), not the freshly allocated one */
    return old;
}

// ===========================================================================
// HashtableBig::Rehash20 -- same, nodes whose next-link lives at +0x14
// ===========================================================================
void* EA::Audio::Eapd::HashtableBig::Rehash20(uint32_t newCount)
{
    void** newBuckets = (void**)AllocBuckets20(newCount);
    uint32_t i = 0;
    void** old = (void**)mpBucketArray;
    if (mnBucketCount > 1 && old != (void**)mAlloc.mpBucketBuffer)
    {
        --mAlloc.mnCurrentSize;
        if (old >= (void**)mAlloc.mpPoolBegin && old < (void**)mAlloc.mpPoolEnd)
        {
            *old = mAlloc.mpHead;
            mAlloc.mpHead = old;
        }
        else
        {
            typedef void (__thiscall* Fn)(void*, void*);
            ((Fn)(*(void***)&mAlloc.mOverflowAllocator)[3])(&mAlloc.mOverflowAllocator, old);
        }
    }
    mpBucketArray = (EA::Audio::Eapd::HashNode20**)newBuckets;
    mnBucketCount = newCount;
    /* retail returns the OLD bucket array (the value left in eax by the free
       path), not the freshly allocated one */
    return old;
}

// ===========================================================================
// HashtableBig::InitPool10 -- init the node pool, seed the table, set the load
// factor and rehash if the initial count is still too small (PatchMap shape)
// ===========================================================================

// ===========================================================================
// HashtableBig::InitPool20 -- same, InstanceMap shape
// ===========================================================================

// ===========================================================================
// SymbolDispatchSlot::Dispatch -- forward to the interface, then look the
// symbol up and hand it to the table's float handler
// ===========================================================================
// ===========================================================================
// GroupAdder::AddGroup -- insert the group's symbol, then notify the listener
// ===========================================================================

// ===========================================================================
// GroupMap::~GroupMap (scalar deleting)
// ===========================================================================
// ===========================================================================
// FixedHashtableAllocator::InitBucketsEx -- size the bucket buffer from the
// element count and hand a new buffer to the overflow allocator
// ===========================================================================

// ===========================================================================
// Hashtable::Construct -- initialise the fields the small table ctor owns
// ===========================================================================
// The allocator InitNamed builds on the stack: its destructor (resetting the vtable) covers the Construct call.
// Out-of-line entry points as other objects see them (bodies not visible to this caller).
struct HashtableCalls_a65180 {
    EA::Audio::Eapd::Hashtable_s00a6_4d70* Construct(const void* nameSlot);                 // 0xa64f80
    EA::Audio::Eapd::Hashtable_s00a6_4d70* InitNamed(void* nameSlot, const char* name);    // 0xa65180
};
struct NamedAllocTemp_a65180 {
    void*       mpVtbl;   // +0x00
    int         mA;       // +0x04
    const char* mpName;   // +0x08
    NamedAllocTemp_a65180(const NamedAllocTemp_a65180& o, const char* name) : mpVtbl((void*)&g_1454fac), mA(o.mA), mpName(name) {}
    ~NamedAllocTemp_a65180() { mpVtbl = (void*)g_1403934; }
};

EA::Audio::Eapd::Hashtable_s00a6_4d70* EA::Audio::Eapd::Hashtable_s00a6_4d70::Construct(const void* nameSlot)
{
    const uint32_t* slot = (const uint32_t*)nameSlot;
    mnElementCount   = 0;
    mfMaxLoadFactor  = 1.0f;
    /* +0x14 is the growth factor, a float in the original (retail stores
       2.0f with movss, not a plain integer 2) */
    *(float*)&mnGrowthFactor = 2.0f;
    mnNextResize     = 0;
    mPool.mpVtbl = (void*)&g_1454fac;
    mPool.mA     = slot[1];
    mPool.mpName = (const char*)slot[2];
    mnBucketCount    = 1;
    mpBucketArray    = (EA::Audio::Eapd::HashNode16**)0x154df28;  // static empty-bucket sentinel
    return this;
}

// ===========================================================================
// Hashtable::InitNamed -- build a name slot and construct the table
// ===========================================================================
// ===========================================================================
// Hashtable::Dispose -- release the bucket array and reset the allocator face
// ===========================================================================
// Destruction view of Hashtable (0x00a65000; callers reach it as Hashtable::Dispose): the bucket nodes are freed, then
// the array through the allocator member, whose own destructor resets its vtable.
struct HashPoolVt_a65000 {
    void* s0; void* s1; void* s2;
    void (__thiscall* Free)(void* self, void* p);   // +0xc
};
struct HashPool_a65000 {
    HashPoolVt_a65000* vt;
    uint32_t mA;
    const char* mpName;
    void Free(void* p) { vt->Free(this, p); }
    ~HashPool_a65000() { vt = (HashPoolVt_a65000*)g_1403934; }
};
struct HashtableDtorView_a65000 {
    uint32_t pad0;
    void** mpBucketArray;     // +0x04
    uint32_t mnBucketCount;   // +0x08
    uint32_t mnElementCount;  // +0x0c
    uint32_t pad10[3];
    HashPool_a65000 mPool;    // +0x1c
    void DoFreeBuckets(void** buckets, uint32_t n);   // 0x00a64c50
    ~HashtableDtorView_a65000();
};

// ===========================================================================
// Hashtable::Insert -- find-or-insert one {key,v1,v2} triple
// ===========================================================================

// ===========================================================================
// Hashtable::Erase -- key-erase shared with the ObjectHashMap (0xa64be0)
// ===========================================================================

// ===========================================================================
// GroupMap::~GroupMap (base destructor) -- tear down the GroupMap's inner
// table at this+0x10 and install the base vtable.  The old duplicate
// `Hashtable::BaseDtor` definition that shared this address (and compiled to
// Dispose() on `this`) was removed: retail disposes this+0x10.
// ===========================================================================
// Destruction view of GroupMap (0x00a651e0, GroupMap::DisposeInner): the table member is destroyed, then the base
// resets the vtable.
struct GroupMapBase_a651e0 {
    void*      mpVtbl;     // +0x00
    void*      mpSelf;     // +0x04
    uint32_t   mField08;   // +0x08
    uint32_t   mField0c;   // +0x0c
    GroupMapBase_a651e0() : mpSelf((char*)this + 0x10), mField08(0), mField0c(0) {}
    ~GroupMapBase_a651e0() { mpVtbl = (void*)g_1455648; }
};
struct GroupMapDtorView_a651e0 : GroupMapBase_a651e0 {
    HashtableDtorView_a65000 mGroups;   // +0x10
    ~GroupMapDtorView_a651e0();
};

// GroupMap's deleting destructor (0x00a65500, GroupMap::ScalarDtor) with the destructor inlined.
void OperatorDeleteNothrow_a65500(void* p) throw();   // 0xf47380
struct GroupMapDelView_a65500 : GroupMapBase_a651e0 {
    HashtableDtorView_a65000 mGroups;   // +0x10
    GroupMapDelView_a65500* ScalarDtor(uint32_t flags);
};

// ===========================================================================
// Instance::~Instance
// ===========================================================================
// @ 0x00a65230
// ===========================================================================
// Instance::~Instance -- free the canvas, destroy every group in the
// Instance/Group table, run the owner ClearLists pass, dispose the GroupMap and
// the two embedded tables, and finally re-stamp the object's vtable.
// ===========================================================================

// ===========================================================================
// Instance::CreateGroup -- find the symbol, and when it is absent allocate a
// 0x20-byte group, initialise it (failing soft if Init returns false) and
// insert {symbol, a3, group} into the Instance/Group table.
// ===========================================================================

void* EA::Audio::Eapd::Instance::CreateGroup(uint32_t* sym, void* a3, void* a4, uint32_t a5)
{
    void* group = 0;
    EA::Audio::Eapd::HashNode16* foundNode = 0;
    /* The original keys the table on the caller's 4-byte symbol token (it hands
       `find` the address of its own argument slot), not on the pointee. */
    uint32_t key = (uint32_t)sym;
    mGroups.FindNode(&foundNode, &key);
    /* sentinel == foundNode means the symbol is absent -> build a group */
    if (mGroups.mpBucketArray[mGroups.mnBucketCount] != foundNode)
        return group;

    typedef void* (__thiscall* AllocFn)(void*, uint32_t);
    void* block = ((AllocFn)(*(void***)this)[2])(this, 0x20);
    if (block)
        group = ((GroupHelp*)block)->Init(this);
    else
        group = 0;
    if (group == 0)
        return group;

    EA::Audio::Eapd::HashNode16 pair;
    pair.mKey = key;
    pair.mV1  = (uint32_t)a3;
    pair.mV2  = (uint32_t)group;
    pair.mpNext = 0;
    EA::Audio::Eapd::InsertResult_s00a6_4d70 res;
    mGroups.Insert(&res, &pair, 0);
    return group;
}

// ===========================================================================
// Instance::FreeGroup -- erase the key, destroy and free the group record
// ===========================================================================

// ===========================================================================
// GroupMap::GroupMapCtor
// ===========================================================================
// Construction view of GroupMap (0x00a654a0, GroupMap::GroupMapCtor).
struct GroupMapCtorView_a654a0 : GroupMapBase_a651e0 {
    EA::Audio::Eapd::Hashtable_s00a6_4d70 mGroups;   // +0x10
    GroupMapCtorView_a654a0(void* nameSlot);
};

// ===========================================================================
// Instance ctor -- install the vtables, name the Instance/Group table, build
// the GroupMap wrapper, then stash the two caller pointers.
// ===========================================================================

// ===========================================================================
// InstanceManager::CanvasOrId -- create a canvas, hand back its id
// ===========================================================================

// ===========================================================================
// InstanceManager::RemoveInstance -- find the binding, unlink the node from the
// map's intrusive iterator list, erase it (fixing the pool free list), then
// destroy and free the Instance.  Returns true when something was removed.
// ===========================================================================

// ===========================================================================
// InstanceManager::FindInstance
// ===========================================================================

// ===========================================================================
// InstanceManager::CreateCanvas  -- build a canvas for a {name,id} pair via the
// canvas interface (vtable slot 3), register the filename symbols, then tell
// the interface we are done (slot 4).  Returns the canvas id (0 on failure).
// ===========================================================================

// ---- items of slice s00a64d70 end

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
    PgSymbol    empty = gEmptySymbol;
    uint32_t    fieldH = gEmptySymbol_s00a6_2ec0.mHash;
    out->mHash = empty.mHash;
    out->mpName = empty.mpName;
    if (empty.mHash != fieldH) {
        out->mHash = fieldH;
        const char* fieldN = gEmptySymbol_s00a6_2ec0.mpName;
        _ReadWriteBarrier();
        gEmptySymbol_s00a6_2ec0.mHash = empty.mHash;
        out->mpName = fieldN;
        gEmptySymbol_s00a6_2ec0.mpName = empty.mpName;
        return out;
    }
    void* canvas = canvas_getcurrent();
    if (canvas != 0) {
        PgSymbol tmp;
        PgSymbol* r = (PgSymbol*)canvas_realizedollar2(&tmp, canvas);
        PgSymbol v;
        v.mHash = r->mHash;
        v.mpName = r->mpName;
        *out = v;
    }
    return out;
}
}}}  // namespace EA::Audio::Eapd

struct EapdNodeAlloc_a643b0 { virtual void v0(); virtual void v1(); virtual void* Alloc(unsigned size); };

// @ 0x00a643b0
namespace EA { namespace Audio { namespace Eapd {
AssetEntry* EapdAssetManager::NewEntryNode(void* a1, void* a2)
{
    AssetEntry* n = (AssetEntry*)((EapdNodeAlloc_a643b0*)((char*)this + 0xc))->Alloc(0x1c);
    if (n != 0) {
        *(void* volatile*)&n->mpLink1 = 0;
        n->mpLink0 = 0;
        *(void* volatile*)&n->mpFieldC = a1;
        n->mpField8 = a2;
        char* head = (char*)this + 0x4c;
        n->mpLink1 = *(void**)(head + 4);
        n->mpLink0 = head;
        *(void**)(head + 4) = n;
        *(void**)(*(void**)((char*)n + 4)) = n;
        return n;
    }
    return 0;
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
        AssetEntry* e = ((EapdAssetManager*)sys)->NewEntryNode(this, (void*)FUN_00a647b0);
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
        AssetEntry* e = ((EapdAssetManager*)sys)->NewEntryNode(this, (void*)FUN_00a64820);
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
        void* e = ((EapdAssetManager*)sys)->NewEntryNode(this, (void*)FUN_00a64870);
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
struct ObjectHashNode;
void ObjectHashMap::Resize(unsigned newCount)
{
    ObjectHashMapAlloc* alloc = &((ObjectHashMapObj*)this)->mAlloc;
    ObjectHashNode** nb = (ObjectHashNode**)alloc->Alloc(newCount * 4 + 4);
    memset_f(nb, 0, newCount * 4);
    nb[newCount] = (ObjectHashNode*)0xffffffff;
    for (unsigned i = 0; i < mNumBuckets08; ++i) {
        ObjectHashNode* n;
        while ((n = ((ObjectHashNode**)mpBuckets04)[i]) != 0) {
            unsigned h = *(unsigned*)n % newCount;
            ((ObjectHashNode**)mpBuckets04)[i] = *(ObjectHashNode**)((char*)n + 0xc);
            *(ObjectHashNode**)((char*)n + 0xc) = nb[h];
            nb[h] = n;
        }
    }
    if (mNumBuckets08 > 1)
        alloc->Free(mpBuckets04);
    mNumBuckets08 = newCount;
    mpBuckets04 = nb;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a64b70
namespace EA { namespace Audio { namespace Eapd {
ObjectHashMapObj::~ObjectHashMapObj()
{
    ((EapdAssetManager*)this)->DisposeArray((void**)mpBuckets04, mNumBuckets08);
    mSize0c = 0;
    if (mNumBuckets08 > 1)
        mAlloc.Free(mpBuckets04);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a64be0
namespace EA { namespace Audio { namespace Eapd {
struct ObjectHashNode { uint32_t mKey; uint32_t m04; uint32_t m08; ObjectHashNode* mpNext; };
unsigned ObjectHashMap::Erase(uint32_t* key)
{
    unsigned before = mSize0c;
    ObjectHashNode** bucket = (ObjectHashNode**)mpBuckets04 + *key % mNumBuckets08;
    if (*bucket) {
        uint32_t k = *key;
        do {
            if (k == (*bucket)->mKey)
                break;
            bucket = &(*bucket)->mpNext;
        } while (*bucket);
        while (*bucket) {
            ObjectHashNode* node = *bucket;
            if (*key != node->mKey)
                break;
            *bucket = node->mpNext;
            ((ObjectHashMapObj*)this)->mAlloc.Free(node);
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

// @ 0x00a64d70
void EA::Audio::Eapd::Hashtable_s00a6_4d70::Insert(EA::Audio::Eapd::InsertResult_s00a6_4d70* out, const EA::Audio::Eapd::HashNode16* pair, const uint32_t* pKey)
{
    (void)pKey;
    uint32_t key = pair->mKey;
    EA::Audio::Eapd::HashNode16* node = *(&mpBucketArray[key % mnBucketCount]);
    EA::Audio::Eapd::HashNode16** bucket = &mpBucketArray[key % mnBucketCount];
    while (node)
    {
        if (key == node->mKey)
        {
            out->mpNode   = node;
            out->mbInserted = 0;
            out->mpBucket = bucket;
            return;
        }
        node = node->mpNext;
    }

    uint32_t local[2];
    ((EA::Audio::Eapd::HashPolicy*)&mfMaxLoadFactor)->NextBucketCount(local, mnBucketCount, mnElementCount, 1);
    typedef void* (__thiscall* AllocFn)(void*, uint32_t);
    EA::Audio::Eapd::HashNode16* fresh = (EA::Audio::Eapd::HashNode16*)((AllocFn)(*(void***)&mPool)[2])(&mPool, 0x10);
    if (fresh)
    {
        fresh->mKey = pair->mKey;
        fresh->mV1  = pair->mV1;
        fresh->mV2  = pair->mV2;
    }
    fresh->mpNext = 0;

    /* NextBucketCount writes the "changed" flag as a single byte (retail tests
       it with `cmp byte ptr [..]`), then the new count in the next dword */
    if (((uint8_t*)local)[0])
    {
        ResizeBuckets(local[1]);
        bucket = &mpBucketArray[key % local[1]];
    }

    fresh->mpNext = *bucket;
    *bucket = fresh;
    ++mnElementCount;

    out->mpNode   = fresh;
    out->mbInserted = 1;
    out->mpBucket = bucket;
}

// @ 0x00a64e60
uint32_t SymbolDispatchSlot::Dispatch(uint32_t sym, float f)
{
    uint8_t found = 0;
    if (mpTarget)
    {
        typedef void (__thiscall* Fn)(void*, uint32_t, float);
        ((Fn)(*(void***)mpTarget)[2])(mpTarget, sym, f);
    }
    EA::Audio::Eapd::HashNode16* local[2];
    mpMap->FindNode(local, &sym);
    if (mpMap->mpBucketArray[mpMap->mnBucketCount] == local[0])
        return found;
    /* the float handler is a member (thiscall): `this` = local[0]+4 in ecx */
    typedef uint32_t (__thiscall* FloatFn)(void*, float);
    return ((FloatFn)MakeFloatHandler)((char*)local[0] + 4, f);
}

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

// @ 0x00a65000
HashtableDtorView_a65000::~HashtableDtorView_a65000()
{
    DoFreeBuckets(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
    if (mnBucketCount > 1)
        mPool.Free(mpBucketArray);
}

// @ 0x00a65070
uint32_t GroupAdder::AddGroup(void* group)
{
    uint32_t key = *(uint32_t*)((char*)group + 0x2c);
    EA::Audio::Eapd::Hashtable_s00a6_4d70* map = mpMap;
    EA::Audio::Eapd::HashNode16* local[2];
    map->FindNode(local, &key);
    if (map->mpBucketArray[map->mnBucketCount] == (EA::Audio::Eapd::HashNode16*)local[0])
    {
        /* 0xa646f0 is IterHelper::MakeEntryIter(entry): this = a stack
           IterHelper, entry = group; it[0] = *(group+0x34), it[1] = group. */
        typedef void* (__thiscall* MakeIterFn)(void*, void*);
        uint32_t entry[2];
        ((MakeIterFn)MakeEntryIter)(entry, group);
        /* retail fills mKey, mV1 = it[0] and mV2 = it[1] (it leaves mpNext
           unused: Insert only copies the three leading words) */
        EA::Audio::Eapd::HashNode16 pair;
        pair.mKey   = key;
        pair.mV1    = entry[0];
        pair.mV2    = entry[1];
        pair.mpNext = 0;
        EA::Audio::Eapd::InsertResult_s00a6_4d70 res;
        map->Insert(&res, &pair, 0);
        /* 0xa64710 is a thiscall taking the argument in ecx */
        typedef void (__thiscall* ResetFn)(void*);
        ((ResetFn)ResetAndClear)(&res);
        ((ResetFn)ResetAndClear)(&local);
        if (mpListener)
        {
            typedef void (__thiscall* Fn)(void*, void*, uint32_t, void*);
            ((Fn)(*(void***)mpListener)[1])(mpListener,
                *(void**)((char*)group + 0x34), key, *(void**)((char*)group + 0x30));
        }
        return 1;
    }
    /* 0xa64730 is EapdAssetManager::PushNode(node), called with this = the
       found node's value word (local[0]+4) */
    typedef uint32_t (__thiscall* PushFn)(void*, void*);
    return ((PushFn)PushNode)((char*)local[0] + 4, group);
}

// @ 0x00a65180
EA::Audio::Eapd::Hashtable_s00a6_4d70* EA::Audio::Eapd::Hashtable_s00a6_4d70::InitNamed(void* nameSlot, const char* name)
{
    const uint32_t* src = (const uint32_t*)nameSlot;
    NamedAllocTemp_a65180 slot(*(const NamedAllocTemp_a65180*)src, name);
    ((HashtableCalls_a65180*)this)->Construct(&slot);
    return this;
}

// @ 0x00a651e0
GroupMapDtorView_a651e0::~GroupMapDtorView_a651e0()
{
}

// @ 0x00a65230
void EA::Audio::Eapd::Instance::Destroy()
{
    pd_free(mpCanvas);                          // 0xa493d0

    /* walk every group in mGroups and destroy/free it */
    EA::Audio::Eapd::HashNode16** bucket = mGroups.mpBucketArray;
    EA::Audio::Eapd::HashNode16* node = *bucket;
    if (node == 0) {
        while (*++bucket == 0) { }
        node = *bucket;
    }
    if (mGroups.mpBucketArray[mGroups.mnBucketCount] != node) {
        do {
            EA::Audio::Eapd::HashNode16* cur = node;
            node = cur->mpNext;
            if (node == 0) {
                while (*++bucket == 0) { }
                node = *bucket;
            }
            AnyGroup* group = (AnyGroup*)cur->mV2;
            void* samples = group->mpSamples;            // group->+0x00
            if (samples != 0) {
                /* the allocator sub-object begins at group+0x0c: its vtable is
                   the pointer stored there and `this` is the address itself */
                typedef void (__thiscall* Fn)(void*, void*);
                ((Fn)(*(void***)&group->mpVtbl0c)[3])((void*)&group->mpVtbl0c, samples);
            }
            group->mpVtbl0c = (void*)g_1403934;
            typedef void (__thiscall* FreeFn)(void*, void*);
            ((FreeFn)(*(void***)this)[3])(this, group);
        } while (mGroups.mpBucketArray[mGroups.mnBucketCount] != node);
    }

    void* owner = Eapd_GetOwnerA();             // 0xa67ce0
    ((EapdOwner*)owner)->ClearLists(this);      // 0xa646a0

    mGroupMap.mGroups.Dispose();                // 0xa65000
    mGroupMap.mpVtbl = (void*)g_1455648;        // 0x01455648
    mGroups.Finalize();                         // 0xa64b70
    mpVtbl = (void*)g_1403934;                  // 0x01403934
}

// @ 0x00a65470
void EA::Audio::Eapd::Instance::FreeGroup(uint32_t key, uint32_t unused, void* group)
{
    (void)unused;
    mGroups.Erase(&key);
    ((AnyGroup*)group)->Destroy();
    typedef void (__thiscall* Fn)(void*, void*);
    ((Fn)(*(void***)this)[3])(this, group);
}

// @ 0x00a654a0
GroupMapCtorView_a654a0::GroupMapCtorView_a654a0(void* nameSlot)
{
    mpVtbl = (void*)g_1455668;
    ((HashtableCalls_a65180*)&mGroups)->InitNamed(nameSlot, "EAPd/InputManager");
}

// @ 0x00a65500
GroupMapDelView_a65500* GroupMapDelView_a65500::ScalarDtor(uint32_t flags)
{
    this->~GroupMapDelView_a65500();
    if (flags & 1)
        OperatorDeleteNothrow_a65500(this);
    return this;
}

// @ 0x00a65560
EA::Audio::Eapd::Instance* EA::Audio::Eapd::Instance::InstanceCtor(void* sys, void* a3, void* a4)
{
    mpVtbl       = (void*)&g_1454fac;
    mField04     = *(uint32_t*)((char*)sys + 4);
    mpClassName  = "EAPd/Instance";     // 0x014556ac
    mGroups.InitNamed(sys, "EAPd/GroupMap");   // 0x0145569c
    mGroupMap.GroupMapCtor(sys);
    mField6c = (uint32_t)a4;
    mpCanvas = a3;
    mField74 = 1;
    return this;
}

// @ 0x00a656b0
bool EA::Audio::Eapd::FixedHashtableAllocator_s00a6_4d70::InitBucketsEx(uint32_t size, uint32_t a1, uint32_t a2)
{
    if (mpBucketBuffer)
    {
        typedef void (__thiscall* Fn)(void*, void*);
        ((Fn)(*(void***)this)[3])(this, mpBucketBuffer);
        mpBucketBuffer = 0;
    }
    uint32_t n = (uint32_t)(uint64_t)((float)size * 1.3333334f);
    mnBucketCount = n;
    if (n < 3)
        mnBucketCount = 3;
    else
        mnBucketCount = FUN_00921340(n) + 1;
    uint32_t want = mnBucketCount * 4;
    if (want == 0x14)
        return Init(0x14, size + 1, (void*)a1, (void*)a2);
    if (Init(0x14, size, (void*)a1, (void*)a2))
    {
        typedef void* (__thiscall* Fn)(void*, uint32_t);
        void* buf = ((Fn)(*(void***)this)[2])(this, mnBucketCount * 4);
        mpBucketBuffer = buf;
        return buf != 0;
    }
    return false;
}

// @ 0x00a657a0
bool EA::Audio::Eapd::InstanceManager_s00a6_4d70::CanvasOrId(void* a2, void* a3, uint32_t* out)
{
    mCurId2 = 0xffffffff;
    CreateCanvas(a2, a3, 0, 0);
    *out = mCurId2;
    mCurId2 = 0xffffffff;
    return *out != 0xffffffff;
}

// @ 0x00a657f0
void* EA::Audio::Eapd::VtblOwner::DispatchSlot2(void* arg, void* unused)
{
    (void)unused;
    typedef void* (__thiscall* Fn)(void*, void*);
    Fn fn = (Fn)(*(void***)this)[2];
    return fn(this, arg);
}

// @ 0x00a65800
void EA::Audio::Eapd::PoolFreeView::FreeNode(void* node)
{
    EA::Audio::Eapd::FixedPool_s00a6_4d70* pool = &mPool;
    --pool->mnCurrentSize;
    if (node >= pool->mpPoolBegin && node < pool->mpPoolEnd)
    {
        *(void**)node = pool->mpHead;
        pool->mpHead = node;
        return;
    }
    typedef void (__thiscall* Fn)(void*, void*);
    ((Fn)(*(void***)&pool->mOverflowAllocator)[3])(&pool->mOverflowAllocator, node);
}

// @ 0x00a65ab0
EA::Audio::Eapd::Copyable38* EA::Audio::Eapd::Copyable38::CopyCtor(const EA::Audio::Eapd::Copyable38* src)
{
    uint32_t* d = mW;
    const uint32_t* s = src->mW;
    d[0]  = (int)g_1454fac;      // own vtable
    d[1]  = s[1];
    d[2]  = s[2];
    d[3]  = (int)g_1454fac;      // nested holder's vtable
    d[4]  = s[4];
    d[5]  = s[5];
    d[6]  = s[6];
    d[7]  = s[7];
    d[8]  = s[8];
    d[9]  = s[9];
    d[10] = s[10];
    d[11] = s[11];
    d[12] = s[12];
    d[13] = s[13];
    return this;
}

// @ 0x00a65b10
void* EA::Audio::Eapd::HashtableBig::EraseFn(void* out, void* node, void** bucket)
{
    EA::Audio::Eapd::HashNode20* n = (EA::Audio::Eapd::HashNode20*)node;          // edx
    uint32_t* o = (uint32_t*)out;               // esi
    void** b = bucket;                          // ebx (never advanced)
    EA::Audio::Eapd::HashNode20* next = *(EA::Audio::Eapd::HashNode20**)((char*)n + 0x14);
    o[1] = (uint32_t)b;
    o[0] = (uint32_t)next;
    /* if the next-link is null, advance the stored bucket cursor to the next
       non-empty slot (the original bumps o->bucket, not the ebx copy) */
    while (next == 0) {
        o[1] += 4;
        next = *(EA::Audio::Eapd::HashNode20**)o[1];
        o[0] = (uint32_t)next;
    }
    /* unlink `node` from its chain: walk the +0x14 links to its predecessor */
    EA::Audio::Eapd::HashNode20* p = *(EA::Audio::Eapd::HashNode20**)b;
    if (p == n) {
        *(EA::Audio::Eapd::HashNode20**)b = *(EA::Audio::Eapd::HashNode20**)((char*)p + 0x14);
    } else {
        EA::Audio::Eapd::HashNode20* c = p;
        EA::Audio::Eapd::HashNode20* e = *(EA::Audio::Eapd::HashNode20**)((char*)c + 0x14);
        while (e != n) {
            c = e;
            e = *(EA::Audio::Eapd::HashNode20**)((char*)e + 0x14);
        }
        *(EA::Audio::Eapd::HashNode20**)((char*)c + 0x14) = *(EA::Audio::Eapd::HashNode20**)((char*)e + 0x14);
    }
    uint32_t minus1 = 0xffffffffu;
    if ((uint32_t*)n != *(uint32_t**)((char*)this + 0x50)) {
        *(uint32_t*)((char*)this + 0x44) += minus1;
        if ((void*)n >= *(void**)((char*)this + 0x38) &&
            (void*)n <  *(void**)((char*)this + 0x3c)) {
            *(uint32_t*)((char*)n) = *(uint32_t*)((char*)this + 0x40);
            *(void**)((char*)this + 0x40) = n;
            *(uint32_t*)((char*)this + 0x0c) += minus1;
            return o;
        }
        typedef void (__thiscall* Fn)(void*, void*);
        ((Fn)(*(void***)((char*)this + 0x28))[3])((char*)this + 0x28, n);
    }
    *(uint32_t*)((char*)this + 0x0c) += minus1;
    return o;
}

// @ 0x00a65c70
void* EA::Audio::Eapd::HashtableBig::AllocNode(const void* value)
{
    void* node = mAlloc.mpHead;
    if (node)
        mAlloc.mpHead = *(void**)node;
    else
        node = mAlloc.AllocPooled();
    if (node)
    {
        uint32_t cur = ++mAlloc.mnCurrentSize;
        if (cur > mAlloc.mnPeakSize)
            mAlloc.mnPeakSize = cur;
        *(uint32_t*)node = *(const uint32_t*)value;
        *(uint32_t*)((char*)node + 4) = *(const uint32_t*)((const char*)value + 4);
        void** link = (void**)((char*)node + 8);
        link[1] = link;
        *link = link;
    }
    *(uint32_t*)((char*)node + 0x10) = 0;
    return node;
}

// @ 0x00a65cd0
bool EA::Audio::Eapd::InstanceManager_s00a6_4d70::RemoveInstance(uint32_t id)
{
    /* InstanceMap iterator node: +4 = prev link, +8 = next link, +0x10 = value */
    void* iter[2];                       // {node, bucket}
    mBindings.Find(iter, &id);
    void* raw = iter[0];
    if (raw == (void*)mBindings.mpBucketArray[mBindings.mnBucketCount])
        return false;

    uint32_t* node = (uint32_t*)raw;
    uint32_t* next = *(uint32_t**)((char*)node + 8);
    uint32_t* prev = *(uint32_t**)((char*)node + 4);
    void* instance = *(void**)((char*)node + 0x10);
    *next = (uint32_t)prev;
    *(uint32_t**)((char*)prev + 4) = next;
    *(uint32_t*)((char*)node + 4) = 0;
    *(uint32_t*)((char*)node + 8) = 0;

    mBindings.EraseFn(iter, raw, (void**)iter[1]);

    ((EA::Audio::Eapd::Instance*)instance)->Destroy();
    typedef void (__thiscall* FreeFn)(void*, void*);
    ((FreeFn)(*(void***)((char*)this + 4))[3])((char*)this + 4, instance);
    return true;
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
    mfGrowthFactor = 2.0f;
    mnNextResize = 0;
    mAlloc.CopyFrom(name);
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
    mSymbols.PatchMapInit("EAPd/PatchMap");
    mBindings.InstanceMapInit("EAPd/InstanceMap");
    mCurId = 0;
    mCurId2 = 0xffffffff;
}

// @ 0x00a68670
bool GroupOwnerL::Op1(unsigned a, unsigned b)
{
    bool r = false;
    if (mListener) {
        _ReadWriteBarrier();
        mListener->OnA(a, b);
    }
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
