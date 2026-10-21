// Shared declarations for slice s00a65f90.
// EA::Audio::Eapd (EA's embedded Pure Data) SymbolManager / InstanceManager family.
// Layouts and addresses come from the original disassembly and the 2008 dev-build PDB
// symbol names.  The SymbolManager / Hashtable / FixedPool shapes are the same ones
// already recovered for slice s00a670b0 (this slice is the head of that family).
#pragma once
#include "types.h"

namespace EA { namespace Audio { namespace Eapd {

struct t_symbol {
    uint32_t    mHash;    // +0x00
    const char* mpName;   // +0x04
};

}}}  // namespace EA::Audio::Eapd

using namespace EA::Audio::Eapd;

// ---------------------------------------------------------------------------
// NamedAllocator / FixedPool / FixedHashtableAllocator
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

// ---------------------------------------------------------------------------
// EASTL hashtable as used by SymbolManager (bucket array + intrusive nodes)
// ---------------------------------------------------------------------------
struct HashNode { uint32_t mKey; void* mValue; HashNode* mpNext; };
struct HashIter { HashNode* mpNode; HashNode** mpBucket; HashNode* mpEnd; };
struct HashFind { HashNode* mpNode; HashNode** mpBucket; };

class Hashtable {
public:
    uint32_t   mFunctors;                 // +0x00
    HashNode** mpBucketArray;             // +0x04
    uint32_t   mnBucketCount;             // +0x08
    uint32_t   mnElementCount;            // +0x0c
    float      mfMaxLoadFactor;           // +0x10
    uint32_t   mnGrowthFactor;            // +0x14
    uint32_t   mnNextResize;              // +0x18
    FixedHashtableAllocator mAlloc;       // +0x1c

    Hashtable* Construct(void* name);                                 // 0xa665f0
    void      Destruct();                                             // 0xa66550
    void      ClearBuckets(HashNode** arr, uint32_t n);               // 0xa660e0
    HashIter  erase(HashIter it);                                     // 0xa66cc0
    void      Rehash(uint32_t n);                                     // 0xa66b40
};

// the EASTL hashtable lookup helpers live in other translation units
HashFind HashTableFind(Hashtable* self, const uint32_t* key);         // 0xa3b2c0
HashIter HashTableEqualRange(Hashtable* self, const uint32_t* key);   // 0x9a6dd0

// ---------------------------------------------------------------------------
// SymbolManager (size 0xd8)
// ---------------------------------------------------------------------------
class SymbolManager {
public:
    void*          mpVtbl;                   // +0x00
    NamedAllocator mAllocA;                  // +0x04
    NamedAllocator mAllocB;                  // +0x10
    char           pad1c[0x10];              // +0x1c
    Hashtable      mSymbols;                 // +0x2c
    Hashtable      mBindings;                // +0x80
    uint32_t     (__cdecl *mHashFunction)(const char*);  // +0xd4
    void* Hash(const char* s);                                   // 0xa66970 (free fn EapdHashString)
    uint32_t HashCall(uint32_t a);                               // 0xa669b0
    void  ClearClasses();                                        // 0xa66d60
    bool  FindSym(uint32_t key, t_symbol* out);                  // 0xa66de0
    bool  Unbind(uint32_t key, void* value);                     // 0xa66e30
    void* BindX(uint32_t key, uint32_t b);                       // 0xa66ec0
    void* FindByClass(uint32_t key, void* a2, void* a3);         // 0xa66f10
    void  SendBang(uint32_t key, uint32_t a2);                   // 0xa66f70
    void  SendFloat(uint32_t key, uint32_t a2, float f);         // 0xa66fd0
    void  SendSymbol(uint32_t key, void* a2, void* a3);          // 0xa67040
};

// ---------------------------------------------------------------------------
// InstanceManager (size 0xec): "EAPd/InstanceManager" with the PatchMap (at
// +0x3c) and InstanceMap (at +0x90) hashes and a 0x78-byte-node FixedPool at +8.
// ---------------------------------------------------------------------------
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
    Hashtable      mSymbols;                 // +0x3c  (PatchMap)
    Hashtable      mBindings;                // +0x90  (InstanceMap)
    uint32_t       mCurId;                   // +0xe4
    uint32_t       mCurId2;                  // +0xe8

    bool      Init(uint32_t size, uint32_t a2, uint32_t a3);  // 0xa65f90
    bool      FlushAll();                                     // 0xa65fe0
    void*     InsertParam(void* out, uint32_t* key);          // 0xa66070
    uint32_t  AddInstance(uint32_t glist);                    // 0xa66300
    void      Construct(void* a, void* b);                    // 0xa66780
    ~InstanceManager();                                       // 0xa66670
};

// ---------------------------------------------------------------------------
// EapdRec: the EAPd patch/instance record (readers at 0xa66c60 / 0xa66c90)
// ---------------------------------------------------------------------------
class EapdRec {
public:
    char     pad00[0x28];
    uint32_t m28;                        // +0x28
    char     pad2c[0x70 - 0x2c];
    uint32_t m70;                        // +0x70
    uint32_t m74;                        // +0x74
    char     pad78[0xc4 - 0x78];
    uint32_t mC4;                        // +0xc4
    uint32_t mC8;                        // +0xc8
    void GetC4(uint32_t* a, uint32_t* b, uint32_t* c);   // 0xa66c60
    void GetC8(uint32_t* a, uint32_t* b, uint32_t* c);   // 0xa66c90
};

// ---------------------------------------------------------------------------
// EapdSystemOverflow: bounded arena (vtable +0x00, allocator at +0x04,
// arena at +0x1c, limit +0x20, cursor +0x24, used +0x28).
// ---------------------------------------------------------------------------
class EapdSystemOverflow {
public:
    void*    mpVtbl;      // +0x00
    void*    mpAlloc;     // +0x04
    uint32_t mField08;    // +0x08
    uint32_t mField0c;    // +0x0c
    uint32_t mField10;    // +0x10
    uint32_t mField14;    // +0x14
    uint32_t mField18;    // +0x18
    void*    mpArena;     // +0x1c
    void*    mpLimit;     // +0x20
    void*    mpCursor;    // +0x24
    uint32_t mUsed;       // +0x28
    uint32_t mField2c;    // +0x2c

    ~EapdSystemOverflow();                                                  // 0xa66830
    bool  Init(uint32_t size, uint32_t a3, uint32_t a4);                    // 0xa66890
    void* Alloc(uint32_t n);                                                // 0xa66900
    void  Free(void* p);                                                    // 0xa66930
};

// ---------------------------------------------------------------------------
// CursorRegistry (0xa663e0): the owner class of 0xa663e0 is not identified in
// the PDB, but its layout is visible in the code: an eastl hashtable of cursor
// records at +0x3c (find instantiated at 0xdb4780) and the instance map at
// +0x90 that 0xa65cd0 operates on (it passes its own `this` there).
// ---------------------------------------------------------------------------
struct CursorLink {
    void*       mpValue;   // +0x00  (record whose +8 field is an instance id)
    CursorLink* mpNext;    // +0x04  (intrusive link; == this when the list ends)
};

// value_type of the +0x3c hashtable: pair<unsigned const, ImageCursor>; the
// record itself is 8 bytes and the inserted node exposes it at node+8.
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

// Record linked into a per-key cursor list.  The intrusive list node is the
// first member, so the element address is the node address and +8 is the id
// that 0xa663e0 / 0xa66410 hand to InstanceReleaser::Remove.
struct CursorNode {
    CursorNode* mpNext;   // +0x00
    CursorNode* mpPrev;   // +0x04
    uint32_t    mnId;     // +0x08  (instance id)
};

// List head stored inside each hashtable node at node+8 (that is the pointer
// InsertIfAbsent returns) and mirrored on the stack for the splice in 0xa66410.
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

// ---------------------------------------------------------------------------
// external helpers used in this slice
// ---------------------------------------------------------------------------
uint32_t EapdHashString(const char* s);                           // 0xa66970
void  PdInletRelease(void* self, void* a, void* b, void* c);      // 0xa65db0
void  PdOutletInit(void* self, void* a, void* b, void* c);        // 0xa65e40
void  PdSymRelease(void* self, uint32_t a);                       // 0xa65cd0
void  PdPatchMapInit(void* self, const char* name);               // 0xa666e0
void  PdInstanceMapInit(void* self, const char* name);            // 0xa66260
void  PdClassResize(void* self, uint32_t a);                      // 0xa65ab0
void  PdPatchInsert(void* out, void* a, void* b);                 // 0xa65bb0
uint32_t EapdPrimeBelow(uint32_t n);                              // 0x921340
void  OutletBang(void* atom);                                     // 0xa49560
void  OutletFloat(void* atom, float f);                           // 0xa49570
void  OutletSymbol(void* atom, void* name);                       // 0xa49590
void  HashtableDtor90(void* self);                                // 0xa538e0
void  EapdClearBucketsRaw(Hashtable* self, HashNode** arr, uint32_t n);  // 0xa66bf0
void  EapdGetC4(void* self, uint32_t* a, uint32_t* b, uint32_t* c);      // 0xa66c60
void  EapdGetC8(void* self, uint32_t* a, uint32_t* b, uint32_t* c);      // 0xa66c90
extern "C" __declspec(dllimport) int __cdecl tolower(int c);

extern void* const vtbl_EAPd_SystemOverflow;
