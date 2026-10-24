// Shared declarations for slice s00a64d70.
// EA::Audio::Eapd (EA's embedded Pure Data): the Instance / InstanceManager
// family, the two intrusive hashtables they are built on (the small 0x28-byte
// "GroupMap" table with node next-links at +0x0c, and the 0x5c-byte
// "PatchMap"/"InstanceMap" tables whose nodes link at +0x10 / +0x14) plus the
// fixed-node-pool allocator they rehash into.
// Layouts / addresses come from the original disassembly and the 2008 dev-build
// PDB symbol names, cross-checked against siblings s00a63dd0 / s00a65f90.
#pragma once
#include "types.h"

namespace EA { namespace Audio { namespace Eapd {

// ---------------------------------------------------------------------------
// NamedAllocator / FixedPool (the node pool embedded in a Hashtable at +0x1c)
// ---------------------------------------------------------------------------
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

    bool  Init(uint32_t nodeSize, uint32_t count, void* a1, void* a2);  // 0xa53210
    void* AllocSize(uint32_t size);                                     // vtable slot 2
    void* AllocNode();                                                  // pool head pop
    void* AllocPooled();                                                // overflow vtbl[2](nodeSize)
    void  Free(void* node);                                             // pool push
};

// the fixed-node-pool hashtable allocator with its own bucket buffer
class FixedHashtableAllocator : public FixedPool {
public:
    uint32_t mnBucketCount;              // +0x30
    void*    mpBucketBuffer;             // +0x34

    bool  InitBuckets(uint32_t a, uint32_t b, uint32_t c);   // 0xa53360
    bool  InitBucketsEx(uint32_t size, uint32_t a1, uint32_t a2); // 0xa656b0
    bool  InitPool(uint32_t a, uint32_t b, uint32_t c);      // legacy
    void* AllocNode();                                       // pop a pooled node
};

// Standalone pool-node free helper (0xa65800): the pool lives at +0x04 of this
// view; the node goes back to the pool free list, or to the overflow allocator.
class PoolFreeView {
public:
    uint32_t  mPad00;     // +0x00
    FixedPool mPool;      // +0x04
    void FreeNode(void* node);   // 0xa65800
};

// ---------------------------------------------------------------------------
// The small EAPd hashtable (0x28 bytes): bucket array + intrusive nodes
// {key, v1, v2, next@0x0c} = 0x10 bytes + embedded node pool at +0x1c.
// ---------------------------------------------------------------------------
struct HashNode16 {
    uint32_t mKey;        // +0x00
    uint32_t mV1;         // +0x04
    uint32_t mV2;         // +0x08
    HashNode16* mpNext;   // +0x0c
};

// the insert-result triplet the EastlHashtable-style Insert fills
struct InsertResult {
    void*    mpNode;        // +0x00
    void*    mpBucket;      // +0x04
    uint8_t  mbInserted;    // +0x08
    uint8_t  pad09[3];
};

class Hashtable {
public:
    uint8_t    pad00[0x04];               // +0x00
    HashNode16** mpBucketArray;           // +0x04
    uint32_t   mnBucketCount;             // +0x08
    uint32_t   mnElementCount;            // +0x0c
    float      mfMaxLoadFactor;           // +0x10
    uint32_t   mnGrowthFactor;            // +0x14
    uint32_t   mnNextResize;              // +0x18
    FixedPool  mPool;                     // +0x1c

    __declspec(noinline) Hashtable* Construct(const void* nameSlot);   // 0xa64f80
    __declspec(noinline) Hashtable* InitNamed(void* nameSlot, const char* name); // 0xa65180
    __declspec(noinline) void Dispose();                        // 0xa65000
    void       BaseDtor();                                      // 0xa651e0
    void       Insert(InsertResult* out, const HashNode16* pair,
                      const uint32_t* pKey);                    // 0xa64d70
    uint32_t   Erase(uint32_t* key);                            // 0xa64be0
    void       DisposeArray2(void** arr, uint32_t n);           // 0xa64c50
    void       ResizeBuckets(uint32_t newCount);                // 0xa64ad0
    void       FindNode(HashNode16** out, const uint32_t* key);// 0x685f30
};

// the load-factor/growth triple the table hands to the rehash-policy helper
struct HashPolicy {
    float      mfMaxLoad;    // +0x00
    uint32_t   mnGrow;       // +0x04
    uint32_t   mnNextResize; // +0x08
    // 0x921440: pick the next bucket count (out[0]=changed flag, out[1]=count)
    void NextBucketCount(uint32_t* out, uint32_t bucketCount,
                         uint32_t elementCount, uint32_t force);   // 0x921440
};

// ---------------------------------------------------------------------------
// The 0x5c-byte hashtable variant used for the PatchMap / InstanceMap; nodes
// link at +0x10 (PatchMap) or +0x14 (InstanceMap).
// ---------------------------------------------------------------------------
struct HashNode20 {
    uint32_t mKey;        // +0x00
    uint32_t mV1;         // +0x04
    uint32_t mV2;         // +0x08
    uint32_t mV3;         // +0x0c
    HashNode20* mpNext;   // +0x10
};

class HashtableBig {
public:
    uint8_t    pad00[0x04];               // +0x00
    HashNode20** mpBucketArray;           // +0x04
    uint32_t   mnBucketCount;             // +0x08
    uint32_t   mnElementCount;            // +0x0c
    float      mfMaxLoadFactor;           // +0x10
    uint32_t   mnGrowthFactor;            // +0x14
    uint32_t   mnNextResize;              // +0x18
    FixedHashtableAllocator mAlloc;       // +0x1c

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

// ---------------------------------------------------------------------------
// GroupMap: vtable + self-pointer block, with a Hashtable at +0x10 (0x38 total)
// ---------------------------------------------------------------------------
class GroupMap {
public:
    void*      mpVtbl;     // +0x00
    GroupMap*  mpSelf;     // +0x04
    uint32_t   mField08;   // +0x08
    uint32_t   mField0c;   // +0x0c
    Hashtable  mGroups;    // +0x10

    GroupMap*  GroupMapCtor(void* nameSlot);                 // 0xa654a0
    void       DisposeInner();                               // 0xa651e0
    GroupMap*  ScalarDtor(uint32_t flags);                   // 0xa65500
};

// ---------------------------------------------------------------------------
// vtable-only holder used for the tiny dispatch wrapper 0xa657f0
// ---------------------------------------------------------------------------
struct VtblOwner { void* DispatchSlot2(void* arg, void* unused); };

// flat 0x38-byte copy constructor target
struct Copyable38 {
    uint32_t mW[14];        // +0x00 .. +0x37
    Copyable38* CopyCtor(const Copyable38* src);
};

// ---------------------------------------------------------------------------
// Group record (0x20) and its helper holder
// ---------------------------------------------------------------------------
struct Symbol { uint32_t mHash; const char* mpName; };
struct VectorOfSymbol { Symbol* mpBegin; Symbol* mpEnd; void* mpAlloc; };

// ---------------------------------------------------------------------------
// Instance (0x78 bytes)
// ---------------------------------------------------------------------------
class Instance {
public:
    void*      mpVtbl;       // +0x00
    uint32_t   mField04;     // +0x04
    const char* mpClassName; // +0x08
    Hashtable  mGroups;      // +0x0c  the Instance/Group table
    GroupMap   mGroupMap;    // +0x34
    uint32_t   mField6c;     // +0x6c
    void*      mpCanvas;     // +0x70
    uint32_t   mField74;     // +0x74

    Instance*  InstanceCtor(void* sys, void* a3, void* a4);   // 0xa65560
    void       Destroy();                                     // 0xa65230
    void*      CreateGroup(uint32_t* sym, void* a3, void* a4, uint32_t a5); // 0xa65360
    void       FreeGroup(uint32_t key, uint32_t unused, void* group); // 0xa65470
};

// ---------------------------------------------------------------------------
// InstanceManager (0xec): the PatchMap at +0x3c, the InstanceMap at +0x90,
// the canvas id at +0xe8.
// ---------------------------------------------------------------------------
class InstanceManager {
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
}}}  // namespace EA::Audio::Eapd

using namespace EA::Audio::Eapd;

// ---------------------------------------------------------------------------
// the group record (a junk pointer the free helper turns into a destroyed
// object); 0xa52af0 is a thiscall taking the group in ecx.
// ---------------------------------------------------------------------------
class AnyGroup {
public:
    void Destroy();     // 0xa52af0
};

// ---- external helpers (bodies live in other slices / other TUs) -------------
uint32_t FUN_009213c0(uint32_t n);                                   // 0x009213c0
uint32_t FUN_00921340(uint32_t n);                                   // 0x00921340

// external helpers reached by the Symbol-dispatch / AddGroup paths; symbols are
// irrelevant to scoring (cmpdis normalises them) but the call shapes matter.
uint32_t MakeFloatHandler(void* self, float f);                      // 0xa648a0
uint32_t PushNode(void* self);                                       // 0xa64730
void*    MakeEntryIter(void* self);                                  // 0xa646f0
void     ResetAndClear(void* self);                                  // 0xa64710
void    HashtableFind(void* map, void** out, const void* key);       // 0x685f30
void    OperatorDelete(void* p);                                     // 0xf47380

// ---------------------------------------------------------------------------
// SymbolDispatchSlot (0xa64e60): a small object holding a pointer to an
// interface (vtable object at +0x0c) and to an eastl symbol table at +0x04.
// Dispatch forwards one {symbol,float} pair to the interface and then to the
// table's float handler.
// ---------------------------------------------------------------------------
class SymbolDispatchSlot {
public:
    uint32_t   mField00;    // +0x00
    Hashtable* mpMap;       // +0x04   the small symbol table
    uint32_t   mField08;    // +0x08
    void*      mpTarget;    // +0x0c   interface with a vtable

    uint32_t Dispatch(uint32_t sym, float f);   // 0xa64e60
};

// ---------------------------------------------------------------------------
// GroupAdder (0xa65070): add {symbol,group} to an eastl symbol table and, when
// the group is new and a listener is installed, notify it.
// ---------------------------------------------------------------------------
class GroupAdder {
public:
    uint32_t mField00;      // +0x00
    Hashtable* mpMap;       // +0x04   the small symbol table
    void*    mpListener;    // +0x08   notified via vtbl[1]

    uint32_t AddGroup(void* group);     // 0xa65070
};
