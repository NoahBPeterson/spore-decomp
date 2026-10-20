// Shared declarations for slice s00a63dd0.
// EA::Audio::Eapd (EA's embedded Pure Data) asset-manager tail: the asset-file
// loader, its intrusive helper nodes/lists, the shared-method holder objects and
// the EAPd object hash map.  Layouts / addresses from the original disassembly
// and the 2008 dev-build PDB symbol names.
#pragma once
#include "types.h"

namespace EA { namespace Audio { namespace Eapd {

struct t_class;

struct PgSymbol {              // t_symbol: by-value pair (hash, name pointer)
    uint32_t    mHash;         // +0x00
    const char* mpName;        // +0x04
};

struct EapdMapBase;

// --- the EAPd asset-manager entry node (size 0x1c) -------------------------
// Created by NewEntryNode (0xa643b0) for every asset the loader wants to keep;
// +0x00/+0x04 is the intrusive list link, +0x08/+0x0c the payload, +0x10 the
// kind tag, +0x14/+0x18 the two payload words.
struct AssetEntry {
    void*       mpLink0;      // +0x00
    void*       mpLink1;      // +0x04
    void*       mpField8;     // +0x08
    void*       mpFieldC;     // +0x0c
    int         mKind10;      // +0x10  1 = float, 2 = symbol/atom
    float       mFloat14;     // +0x14
    void*       mpField18;    // +0x18
};

// --- C3D-style object holder produced by 0xa64470 --------------------------
// size 0x54: allocator face at +0x0..+0x14, vtbls, then two empty intrusive
// lists with self-referential sentinels at +0x44 and +0x4c.
struct AssetSlot {
    void*       mpVtbl00;     // +0x00
    void*       mpField04;    // +0x04
    void*       mpAlloc08;    // +0x08
    void*       mpVtbl0c;     // +0x0c
    void*       mpVtbl10;     // +0x10
    void*       mpField14;    // +0x14
    void*       mpVtbl18;     // +0x18
    void*       mpVtbl1c;     // +0x1c
    void*       mpField20;    // +0x20
    void*       mpVtbl24;     // +0x24
    uint32_t    mField28;     // +0x28
    uint32_t    mCounter2c;   // +0x2c
    uint32_t    mMax30;       // +0x30
    void*       mpField34;    // +0x34
    void*       mpField38;    // +0x38
    void*       mpField3c;    // +0x3c
    void*       mpField40;    // +0x40
    void*       mpSent44;     // +0x44  self
    void*       mpSent48;     // +0x48  self
    void*       mpSent4c;     // +0x4c  self
    void*       mpSent50;     // +0x50  self
    AssetSlot* Ctor();        // 0x00a64470
    void        Free(void* node); // 0x00a644e0
};

// --- tiny two-word output helper used by the object iterators ---------------
struct IterHelper {
    void*       mpWord0;      // +0x00
    void*       mpWord1;      // +0x04
    void* MakeEntryIter(void* entry);   // 0x00a646f0
};

// --- hash map for EAPd objects (0xa64ad0 .. 0xa64cf0) ----------------------
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

// --- the EAPd asset manager (0x74 bytes) -- continued from slice s00a62ec0 --
// Only the fields touched by this slice are named.
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

// --- globals ---------------------------------------------------------------
extern void* gpAssetManagerGlobal;    // 0x016758d4  +0x240 -> the asset manager
extern uint32_t gTag15544b4;          // 0x015544b4
extern uint32_t gTag15544b8;          // 0x015544b8
extern uint32_t gTag15544bc;          // 0x015544bc
extern int      gDepth167545c;        // 0x0167545c  outlet recursion depth guard
extern void*    uThrowTarget;         // 0x013cc53c

// --- free functions defined in this slice ----------------------------------
void      SlotFree(AssetSlot* self, void* node);                  // 0x00a644e0 (AssetSlot::Free)
int       SendFloatToAll(void* atom);                             // 0x00a647b0
int       SendSymbolToAll(void* atom);                            // 0x00a64820
int       SendSymbolList(void* atom);                             // 0x00a64870
int       PauseCanvas(void* entry);                               // 0x00a64a10
void      ThrowHelper(void* self);                                // 0x00a646d0
// (0x00a64710 is EapdAssetManager::ResetAndClear, declared above)
// (0x00a64ad0..0x00a64cf0 are ObjectHashMap members, declared inside the struct)

// --- external helpers ------------------------------------------------------
void*   SystemGetAssetManager();                                  // 0x00a67ce0
PgSymbol* gensym(PgSymbol* out, const char* s);                   // 0x00a675f0
float   atom_getfloat(void* atom);                                // 0x00a46760
void*   atom_getsymbol(void* out, void* atom);                    // 0x00a46790
void    outlet_float_(void* obj, float f);                        // 0x00a49570
void*   outlet_symbol_(void* n);                                  // 0x00a49da0
void*   outlet_list_(void* s, void* a, void* b);                  // 0x00a49df0
void    canvas_pause_(void* canvas, float f);                     // 0x00a4a6e0
void*   canvas_realizedollar2(void* out, void* glist);            // 0x00a4a5d0
void*   HashFind(void* out, void* node, void* key);               // 0x00685f30
struct HashFace { void* Find(void* out, void* key); };            // 0x00685f30 (thiscall)
struct MapDestroyFace { void Destroy(void* node); };              // 0x00a63640 (thiscall)
struct RBTreeFindFace { void Find(void* out, const void* key); };  // 0x00e5c780 (thiscall)
struct AllocFace { void* DestroyHelper(unsigned size, void* a1, void* a2, void* a3); }; // 0x00a53210

extern "C" void* memcpy_f(void* d, const void* s, unsigned n);    // CRT memcpy
extern "C" void* memset_f(void* d, int c, unsigned n);            // 0x011e073e
extern "C" void  RBTreeInsert(void* node, void* parent, void* head, int side); // 0x009216a0
extern "C" void* RBTreeIncrement(void* node);                     // 0x00921580
extern "C" void* RBTreeDecrement(const void* node);               // 0x009215c0
extern "C" void  RBTreeErase(void* node, void* head);             // 0x00921880
extern "C" void  rbtree_find(void* out, const void* key, void* tree); // 0x00e5c780
extern "C" void  multimap_equal_range(void* out, const void* key, void* tree); // 0x00d4b450

// helpers defined in the sibling slice s00a62ec0
bool  InputParseSymbols(int kind, char** cursor, char* end, PgSymbol* out1,
                        PgSymbol* out2, int* out3, int* out4);     // 0x00a634a0
void  EapdMapDestroyAll(void* self, void* node);                  // 0x00a63640
bool  EapdMapEraseEvent(void* self, uint32_t key, PgSymbol* out); // 0x00a63860
bool  EapdMapFindEventSample(void* self, uint32_t key, int sym2, uint32_t a4,
                             uint32_t a5, uint32_t evKey, uint32_t* o1, uint32_t* o2); // 0x00a63900
void* EapdMapFindOrInsert18(void* self, void* out, uint32_t* key); // 0x00a63a50
void* EapdMapFindOrInsert28(void* self, void* out, uint32_t* key); // 0x00a63bf0
void* EapdMapBaseInit(void* self, void* allocator, void* a3, void* a4, void* a5); // 0x00a63c30

}}}
