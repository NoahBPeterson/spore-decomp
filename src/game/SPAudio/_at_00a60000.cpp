// src/game/SPAudio/_at_00a60000.cpp -- migrated from slice(s) s00a65f90, s00a63dd0, s00a62ec0, s00a60ef0, s00a5fff0 by tools/migrate/rewrite.py
// Object file: SPAudio/_at_00a60000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s00a60ef0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   uint;
typedef unsigned char  byte;
namespace Eapd {
struct t_symbol {                 // by-value pair
    uint        mHash;            // +0x00
    const char* mpName;           // +0x04
};
}
namespace Eapd {
struct t_class;                   // opaque
}
namespace Eapd {
struct t_atom { uint a; uint b; };        // 8 bytes
}
namespace Eapd {
struct t_glist;                   // opaque canvas
}
namespace Eapd {
struct t_inlet;                   // opaque
}
namespace Eapd {
struct t_outlet;                  // opaque
}
namespace Eapd {
struct TX {                       // generic object with the common tail
    uint   mGobj[0x28 / 4];       // +0x00
    void*  mpA28;                 // +0x28
    void*  mpB2c;                 // +0x2c
    int    mC30;                  // +0x30
    int    mD34;                  // +0x34
    void*  mpE38;                 // +0x38
    int    mF3c;                  // +0x3c
};
}
namespace Eapd {
t_class* gpInletClass;            // 0x0167582c
}
namespace Eapd {
t_class* gpMenuClass;             // 0x01675834
}
namespace Eapd {
t_class* gpTableClass;            // 0x01675838
}
namespace Eapd {
t_class* gpRandWeightedClass;     // 0x0167583c
}
namespace Eapd {
t_symbol gEmptySymbol;            // 0x0167589c
}
namespace Eapd {
t_symbol gFloatSymbol;            // 0x016758c4
}
namespace Eapd {
t_symbol gAnythingSymbol;         // 0x016758cc
}
namespace Eapd {
t_symbol sHashA;                  // 0x01675848
}
namespace Eapd {
t_symbol sRandWeighted;           // 0x01675854
}
namespace Eapd {
uint     gOutletCount;            // 0x0167545c
}
namespace Eapd {
const float kfOne    = 1.0f;      // 0x01485720
}
namespace Eapd {
void*     pd_new(t_class* c);                                         // 0x00a49390
}
namespace Eapd {
void*     outlet_new(void* owner, t_symbol s);                        // 0x00a49d30
}
namespace Eapd {
void*     canvas_getcurrent();                                        // 0x00a4a430
}
namespace Eapd {
t_inlet*  canvas_addinlet(t_glist* g, void* owner, t_symbol s);          // 0x00a4e030
}
namespace Eapd {
void      outlet_float(t_outlet* o, float f);                         // 0x00a49570
}
namespace Eapd {
void      outlet_symbol(t_outlet* o, t_symbol s);                     // 0x00a49df0
}
namespace Eapd {
void*     atom_vectorgensym(t_symbol* out, int argc, t_atom* argv);   // 0x00a46830
}
namespace Eapd {
int       atom_getint_at(int idx, int argc, t_atom* argv);            // 0x00a46920
}
namespace Eapd {
void      inlet_setempty(t_inlet* i, t_symbol s);                     // 0x00a49720
}
namespace Eapd {
void      outlet_setempty(t_outlet* o, t_symbol s);                   // 0x00a49d10
}
namespace Eapd {
void*     getbytes(int n, const char* kind);                          // 0x00a49610
}
namespace Eapd {
void      freebytes(void* p, int n);                                  // 0x00a49650
}
namespace Eapd {
bool      pd_bind(void* x, t_symbol name);                            // 0x00a67620
}
namespace Eapd {
void*     EapdBindRemove(t_symbol s);                                 // 0x00a671d0
}
namespace Eapd {
void      sys_vgui(uint a, uint b, uint c);                           // 0x00a671b0
}
namespace Eapd {
void*     pd_findbyclass(t_symbol name, t_symbol s2, t_class* c);     // 0x00a671f0
}
namespace Eapd {
void      DoInsertValue(void* vec, void* val, int off);               // 0x011e0744
}
namespace Eapd {
void      SetSeed(void* rng, uint seed);                              // 0x00936090
}
namespace Eapd {
uint      GetRandomSeed();                                            // 0x00a5eca0
}
namespace Eapd {
void* vinlet_new(void* a1, void* a2, int argc, t_atom* argv);          // 0x00a613c0
}
namespace Eapd {
void* menu_new(int argc, t_atom* argv);                               // 0x00a618c0
}
namespace Eapd {
void  menu_free(TX* x);                                               // 0x00a619c0
}
namespace Eapd {
int   menu_float(TX* x, float f);                                     // 0x00a619e0
}
namespace Eapd {
bool  menu_list(TX* x, t_symbol s, int argc, t_atom* argv);           // 0x00a61ad0
}
namespace Eapd {
bool  menu_append(TX* x, t_symbol s, int argc, t_atom* argv);         // 0x00a61b10
}
namespace Eapd {
void  menu_clear(TX* x);                                              // 0x00a61b50
}
namespace Eapd {
void* table_new(void* a, void* b, int argc, t_atom* argv);            // 0x00a61c20
}
namespace Eapd {
void  table_free(void* x);                                            // 0x00a61e50
}
namespace Eapd {
void  table_select(void* x, float f);                                 // 0x00a61ec0
}
namespace Eapd {
void  table_float(void* x, float f);                                  // 0x00a61ee0
}
// ---- items of slice s00a60ef0 end

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
struct XThisInstance {
    uint32_t    mGobj[0x28 / 4];  // +0x00
    void*       mpInstance;       // +0x28
    uint32_t    pad2c[0xc];       // +0x2c .. +0x5b (12 dwords)
    uint8_t     mbInstanceFlag;   // +0x5c
    bool        StoreFlag(uint8_t flag);   // 0x00a633e0
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct EapdMapBase {
    void*       mpvtable;      // +0x00
    void*       mpAllocVtbl;   // +0x04
    void*       mpAllocator;   // +0x08
    const char* mpName;        // +0x0c
    uint8_t     mbFlag10;      // +0x10
    void*       mpSentinel18;  // +0x14  self-referential list sentinel
    void*       mpHead;        // +0x18
    void*       mpSize;        // +0x1c
    uint8_t     mbFlag20;      // +0x20
    void*       mpCount;       // +0x24
    void*       mpVtbl28;      // +0x28
    void*       mpOwner2c;     // +0x2c
    const char* mpKind30;      // +0x30

    void* Init(void* allocator, void* a3, void* a4, void* a5);   // 0x00a63c30
    ~EapdMapBase();                                              // 0x00a63b40
    void  DestroyAll(void* node);                                // 0x00a63640
    bool  ClearAll();                                            // 0x00a63b90
    bool  EraseEvent(uint32_t key, PgSymbol* out);               // 0x00a63860
    bool  HasKeyEvent(uint32_t key);                             // 0x00a63680
    bool  HasKeyField(uint32_t key, int arg);                    // 0x00a636b0
    void* Insert28(void** out, void* hint, uint32_t* key, char isEnd);   // 0x00a636e0
    void  Insert1c(uint32_t* val, void* hint, uint32_t* key, char isEnd); // 0x00a63770
    void  Insert18(uint32_t* val, void* hint, uint32_t* key, char isEnd); // 0x00a637f0
    void* FindOrInsert18(void** out, uint32_t* key);             // 0x00a63a50
    void* FindOrInsert28(void** out, uint32_t* key);             // 0x00a63bf0
    bool  FindEventSample(uint32_t a0, uint32_t key, int sym2, uint32_t a4, uint32_t a5,
                          uint32_t evKey, uint32_t* out1, uint32_t* out2); // 0x00a63900
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct EapdAssetManager : EapdMapBase {
    void*       mpBmSentinel34; // +0x34
    void*       mpBmHead;       // +0x38
    void*       mpBmSize;       // +0x3c
    uint8_t     mbBmFlag40;     // +0x40
    void*       mpBmCount;      // +0x44
    void*       mpBmVtbl;       // +0x48
    void*       mpBmOwner;      // +0x4c
    const char* mpBmKind;       // +0x50
    void*       mpRmSentinel54; // +0x54
    void*       mpRmHead;       // +0x58
    void*       mpRmSize;       // +0x5c
    uint8_t     mbRmFlag60;     // +0x60
    void*       mpRmCount;      // +0x64
    void*       mpRmVtbl;       // +0x68
    void*       mpRmOwner;      // +0x6c
    const char* mpRmKind;       // +0x70

    void* Init(void* allocator);     // 0x00a63c90
    ~EapdAssetManager();             // 0x00a63d20
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern PgSymbol gEventSymbol;        // 0x01675864
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
extern PgSymbol gEmptySymbol_s00a6_2ec0;        // 0x01675874
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern PgSymbol gGrandSymbol;        // 0x0167587c
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern PgSymbol gGrpSymbol;          // 0x01675884
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern PgSymbol gSymbolSymbol;       // 0x01675894
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern uint32_t gFieldKind;          // 0x015544ac
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
PgSymbol* gensym(PgSymbol* out, const char* s);                       // 0x00a675f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct ParamSink { void SetParam(bool f); };                       // 0x00a649f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  busy_float(XThisInstance* x, float f);                         // 0x00a63310
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool  __fastcall InputParseSymbols(int kind, char** cursor, char* end, PgSymbol* out1,
                                   PgSymbol* out2, int* out3, int* out4);  // 0x00a634a0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern "C" char* strchr_f(const char* s, int c);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern "C" void* memcpy_f(void* d, const void* s, unsigned n);
}
}
}
extern "C" void  RBTreeInsert(void* node, void* parent, void* head, int side); // 0x009216a0
extern "C" void* RBTreeIncrement(void* node);                        // 0x00921580
extern "C" void* RBTreeDecrement(const void* node);                  // 0x009215c0
extern "C" void  RBTreeErase(void* node, void* head);                // 0x00921880
namespace EA {
namespace Audio {
namespace Eapd {
struct RbTreeView { void* find(void* out, const void* key); };     // 0x00e5c780
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct RbMapView  { void  equal_range(void* out, const void* key); }; // 0x00d4b450
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern "C" void* __cdecl memcpy_f(void*, const void*, unsigned);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
PgSymbol  gEventSymbol;         // 0x01675864
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
PgSymbol  gEmptySymbol_s00a6_2ec0;         // 0x01675874
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
PgSymbol  gGrandSymbol;         // 0x0167587c
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
PgSymbol  gGrpSymbol;           // 0x01675884
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
PgSymbol  gSymbolSymbol;        // 0x01675894
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
uint32_t  gFieldKind;           // 0x015544ac
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
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct EapdAssetManager_s00a6_3dd0 {
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
extern uint32_t gTag15544b4;          // 0x015544b4
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern int      gDepth167545c;        // 0x0167545c  outlet recursion depth guard
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern void*    uThrowTarget;         // 0x013cc53c
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int       SendFloatToAll(void* atom);                             // 0x00a647b0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int       SendSymbolToAll(void* atom);                            // 0x00a64820
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int       SendSymbolList(void* atom);                             // 0x00a64870
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int       PauseCanvas(void* entry);                               // 0x00a64a10
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void      ThrowHelper(void* self);                                // 0x00a646d0
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
float   atom_getfloat(void* atom);                                // 0x00a46760
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void*   atom_getsymbol(void* out, void* atom);                    // 0x00a46790
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void    outlet_float_(void* obj, float f);                        // 0x00a49570
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void*   outlet_symbol_(void* n);                                  // 0x00a49da0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void*   outlet_list_(void* s, void* a, void* b);                  // 0x00a49df0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void    canvas_pause_(void* canvas, float f);                     // 0x00a4a6e0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void*   canvas_realizedollar2(void* out, void* glist);            // 0x00a4a5d0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct MapDestroyFace { void Destroy(void* node); };              // 0x00a63640 (thiscall)
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct RBTreeFindFace { void Find(void* out, const void* key); };  // 0x00e5c780 (thiscall)
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct AllocFace { void* DestroyHelper(unsigned size, void* a1, void* a2, void* a3); }; // 0x00a53210
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern uint32_t gAssetMagic;       // 0x015544a8
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern uint32_t gFieldKind_s00a6_3dd0;        // 0x015544ac
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern PgSymbol gEmptySymbol_s00a6_3dd0;      // 0x01675874
}
}
}
// ---- items of slice s00a63dd0 end

// ---- items of slice s00a65f90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) int __cdecl tolower(int c);
extern void* const vtbl_EAPd_SystemOverflow;
namespace EA {
namespace Audio {
namespace Eapd {
struct t_symbol_s00a6_5f90 {
    uint32_t    mHash;    // +0x00
    const char* mpName;   // +0x04
};
}  // namespace EA::Audio::Eapd
}
}
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
HashFind HashTableFind(Hashtable* self, const uint32_t* key);         // 0xa3b2c0
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
    bool  FindSym(uint32_t key, EA::Audio::Eapd::t_symbol_s00a6_5f90* out);                  // 0xa66de0
    bool  Unbind(uint32_t key, void* value);                     // 0xa66e30
    void* BindX(uint32_t key, uint32_t b);                       // 0xa66ec0
    void* FindByClass(uint32_t key, void* a2, void* a3);         // 0xa66f10
    void  SendBang(uint32_t key, uint32_t a2);                   // 0xa66f70
    void  SendFloat(uint32_t key, uint32_t a2, float f);         // 0xa66fd0
    void  SendSymbol(uint32_t key, void* a2, void* a3);          // 0xa67040
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
uint32_t EapdHashString(const char* s);                           // 0xa66970
void  PdInletRelease(void* self, void* a, void* b, void* c);      // 0xa65db0
void  PdOutletInit(void* self, void* a, void* b, void* c);        // 0xa65e40
void  PdSymRelease(void* self, uint32_t a);                       // 0xa65cd0
void  PdPatchInsert(void* out, void* a, void* b);                 // 0xa65bb0
void  HashtableDtor90(void* self);                                // 0xa538e0
// ---- items of slice s00a65f90 end

// @ 0x00a604a0
namespace EA { namespace Audio { namespace Eapd {
void function_inrange(char* x, float a, float b)
{
    if (x == 0)
        return;
    if (a != b) {
        if (b < a) {
            float t = a;
            a = b;
            b = t;
        }
        *(float*)(x + 0x2c) = a;
        *(float*)(x + 0x30) = b - a;
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a604e0
namespace EA { namespace Audio { namespace Eapd {
void function_outrange(char* x, float a, float b)
{
    if (x == 0)
        return;
    if (a != b) {
        if (b < a) {
            float t = a;
            a = b;
            b = t;
        }
        *(float*)(x + 0x34) = a;
        *(float*)(x + 0x38) = b - a;
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a613c0
namespace Eapd {
void* vinlet_new(void* a1, void* a2, int argc, t_atom* argv)
{
    (void)a1; (void)a2;
    TX* x = (TX*)pd_new(gpInletClass);
    if (x != 0) {
        void* cur = canvas_getcurrent();
        *(void**)((char*)x + 0x28) = cur;
        *(void**)((char*)x + 0x2c) = canvas_addinlet((t_glist*)cur, x, gEmptySymbol);
        void* out = outlet_new(x, gEmptySymbol);
        if (argc != 0) {
            t_symbol s;
            atom_vectorgensym(&s, argc, argv);
            inlet_setempty((t_inlet*)*(void**)((char*)x + 0x2c), s);
            outlet_setempty((t_outlet*)out, s);
        }
    }
    return x;
}
}  // namespace Eapd

// @ 0x00a61460
namespace Eapd {
void inlet_float_all(TX* x, float f)
{
    void* out = *(void**)((char*)x + 0xc);
    int n = ++gOutletCount;
    if (n < 1000) {
        void** p = (void**)*(void**)((char*)out + 8);
        while (p != 0) {
            outlet_float((t_outlet*)p[1], f);
            p = (void**)*p;
        }
    }
    gOutletCount--;
}
}  // namespace Eapd

// @ 0x00a618c0
namespace Eapd {
void* menu_new(int argc, t_atom* argv)
{
    TX* x = 0;
    int count = 0x20;
    if (argc > 1) {
        if (atom_getint_at(0, argc, argv) != 1)
            return 0;
        if (*(int*)((char*)argv + 0x18) != 1)
            return 0;
        count = (int)*(float*)((char*)argv + 0x1c);
        argc -= 3;
        argv = (t_atom*)((char*)argv + 0x24);
        if (count < 1)
            count = 0x20;
    }
    void* buf = getbytes(count * 0xc, "EAPd/t_menu_atoms");
    if (buf != 0) {
        x = (TX*)pd_new(gpMenuClass);
        if (x != 0) {
            *(void**)((char*)x + 0x28) = outlet_new(x, gAnythingSymbol);
            if (*(void**)((char*)x + 0x28) != 0) {
                *(void**)((char*)x + 0x2c) = outlet_new(x, gFloatSymbol);
                if (*(void**)((char*)x + 0x2c) != 0) {
                    *(int*)((char*)x + 0x30) = argc;
                    *(int*)((char*)x + 0x34) = count;
                    *(void**)((char*)x + 0x38) = buf;
                    int off = 0;
                    while (argc > 0) {
                        char* dst = (char*)*(void**)((char*)x + 0x38) + off;
                        *(uint*)(dst + 0) = *(uint*)((char*)argv + off + 0);
                        *(uint*)(dst + 4) = *(uint*)((char*)argv + off + 4);
                        *(uint*)(dst + 8) = *(uint*)((char*)argv + off + 8);
                        off += 0xc;
                        argc--;
                    }
                }
            }
        }
    }
    return x;
}
}  // namespace Eapd

// @ 0x00a619c0
namespace Eapd {
void menu_free(TX* x)
{
    freebytes(*(void**)((char*)x + 0x38), *(int*)((char*)x + 0x34) * 0xc);
}
}  // namespace Eapd

// @ 0x00a619e0
namespace Eapd {
int menu_float(TX* x, float f)
{
    int idx = (int)f;
    byte ok = 0;
    if (idx < 0)
        return ok;
    if (*(int*)((char*)x + 0x30) <= idx)
        return ok;
    void** o = (void**)*(void**)((char*)x + 0x2c);
    gOutletCount++;
    if (gOutletCount < 1000) {
        while (o != 0) {
            outlet_float((t_outlet*)o[1], (float)idx);
            o = (void**)*o;
        }
    }
    gOutletCount--;
    char* e = (char*)(*(int*)((char*)x + 0x38) + idx * 0xc);
    if (*(int*)e == 1) {
        float v = *(float*)(e + 4);
        void** s = (void**)*(void**)((char*)x + 0x28);
        gOutletCount++;
        if (gOutletCount < 1000) {
            while (s != 0) {
                outlet_float((t_outlet*)s[1], v);
                s = (void**)*s;
            }
        }
        gOutletCount--;
        return 1;
    }
    outlet_symbol((t_outlet*)*(void**)((char*)x + 0x28), *(t_symbol*)(e + 4));
    return 1;
}
}  // namespace Eapd

// @ 0x00a61ad0
namespace Eapd {
bool menu_list(TX* x, t_symbol s, int argc, t_atom* argv)
{
    bool ok = false;
    if (*(int*)((char*)x + 0x34) > argc) {
        DoInsertValue(*(void**)((char*)x + 0x38), argv, argc * 0xc);
        *(int*)((char*)x + 0x30) = argc;
        ok = true;
    }
    return ok;
}
}  // namespace Eapd

// @ 0x00a61b10
namespace Eapd {
bool menu_append(TX* x, t_symbol s, int argc, t_atom* argv)
{
    bool ok = false;
    if (argc == 1) {
        if (*(int*)((char*)x + 0x30) != *(int*)((char*)x + 0x34)) {
            int n = *(int*)((char*)x + 0x30);
            char* dst = (char*)(*(int*)((char*)x + 0x38) + n * 0xc);
            *(uint*)(dst + 0) = *(uint*)((char*)argv + 0);
            *(uint*)(dst + 4) = *(uint*)((char*)argv + 4);
            *(uint*)(dst + 8) = *(uint*)((char*)argv + 8);
            (*(int*)((char*)x + 0x30))++;
            ok = true;
        }
    }
    return ok;
}
}  // namespace Eapd

// @ 0x00a61b50
namespace Eapd {
void menu_clear(TX* x)
{
    *(int*)((char*)x + 0x30) = 0;
}
}  // namespace Eapd

// @ 0x00a61c20
namespace Eapd {
void* table_new(void* a1, void* a2, int argc, t_atom* argv)
{
    if (argc > 3)
        return 0;
    bool randW = (a1 == (void*)sRandWeighted.mHash);
    t_symbol sym7 = gEmptySymbol;
    int val1 = 1;
    int val2 = 1;
    t_symbol symC = gEmptySymbol;
    if (argc > 0) {
        if (*(int*)argv == 2) {
            sym7 = *(t_symbol*)((char*)argv + 8);
            symC = *(t_symbol*)((char*)argv + 4);
        }
        int k = (*(int*)argv == 2) ? 1 : 0;
        if (k < argc) {
            int* e = (int*)((char*)argv + k * 0xc);
            if (*e == 1) {
                float f = *(float*)((char*)argv + k * 0xc + 4);
                k++;
                if (f < kfOne)
                    f = kfOne;
                val1 = (int)f;
            }
            if (k < argc) {
                e = (int*)((char*)argv + k * 0xc);
                if (*e == 1) {
                    float f = *(float*)((char*)argv + k * 0xc + 4);
                    k++;
                    if (f < kfOne)
                        f = kfOne;
                    val2 = (int)f;
                }
                if (k < argc)
                    return 0;
            }
        }
    }
    if (sym7.mHash != gEmptySymbol.mHash) {
        if (pd_findbyclass(sym7, symC, gpTableClass) != 0)
            return 0;
    }
    if (val1 > val2)
        return 0;
    void* buf = getbytes(val2 * 0xc, "EAPd/t_table_atoms");
    if (buf == 0)
        return 0;
    char* p = (char*)buf;
    for (int i = val2; i > 0; i--) {
        *(int*)p = 1;
        *(float*)(p + 4) = 0.0f;
        p += 0xc;
    }
    t_class* cls = randW ? gpRandWeightedClass : gpTableClass;
    TX* x = (TX*)pd_new(cls);
    if (x == 0) {
        freebytes(buf, val2 * 4);
        return x;
    }
    if (outlet_new(x, gFloatSymbol) == 0) {
        freebytes(buf, val2 * 4);
        return x;
    }
    *(t_symbol*)((char*)x + 0x28) = sym7;
    *(t_symbol*)((char*)x + 0x2c) = symC;
    *(int*)((char*)x + 0x30) = val1;
    *(int*)((char*)x + 0x34) = val2;
    *(void**)((char*)x + 0x38) = buf;
    if (randW)
        SetSeed((char*)x + 0x3c, GetRandomSeed());
    if (sym7.mHash != gEmptySymbol.mHash)
        pd_bind(x, *(t_symbol*)((char*)x + 0x28));
    void* r = EapdBindRemove(sHashA);
    if (r != 0)
        sys_vgui((uint)r, sHashA.mHash, (uint)sHashA.mpName);
    pd_bind(x, sHashA);
    return x;
}
}  // namespace Eapd

// @ 0x00a61e50
namespace Eapd {
void table_free(TX* x)
{
    if (*(uint*)((char*)x + 0x28) != gEmptySymbol.mHash)
        sys_vgui((uint)x, *(uint*)((char*)x + 0x28), *(uint*)((char*)x + 0x2c));
    void* r = EapdBindRemove(sHashA);
    if (r == x)
        sys_vgui((uint)x, sHashA.mHash, (uint)sHashA.mpName);
    int n = *(int*)((char*)x + 0x34);
    void* buf = *(void**)((char*)x + 0x38);
    freebytes(buf, n * 4);
}
}  // namespace Eapd

// @ 0x00a61ec0
namespace Eapd {
void table_select(TX* x, float f)
{
    int i = (int)f;
    if (1 <= i && *(int*)((char*)x + 0x34) >= i)
        *(int*)((char*)x + 0x30) = i;
}
}  // namespace Eapd

// @ 0x00a61ee0
namespace Eapd {
void table_float(TX* x, float f)
{
    int i = (int)f;
    if (i < 0)
        return;
    if (i >= *(int*)((char*)x + 0x30))
        return;
    float v = *(float*)(*(int*)((char*)x + 0x38) + i * 0xc + 4);
    void* out = *(void**)((char*)x + 0xc);
    int n = ++gOutletCount;
    if (n < 1000) {
        void** p = (void**)*(void**)((char*)out + 8);
        while (p != 0) {
            outlet_float((t_outlet*)p[1], v);
            p = (void**)*p;
        }
    }
    gOutletCount--;
}
}  // namespace Eapd

// @ 0x00a63310
namespace EA { namespace Audio { namespace Eapd {
void busy_float(XThisInstance* x, float f)
{
    ((ParamSink*)x->mpInstance)->SetParam(f != 0.0f);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a633e0
namespace EA { namespace Audio { namespace Eapd {
bool XThisInstance::StoreFlag(uint8_t flag)
{
    PgSymbol s;
    mbInstanceFlag = flag;
    gEventSymbol = *gensym(&s, "--current--");
    gGrpSymbol   = *gensym(&s, "grp");
    gGrandSymbol = *gensym(&s, "snr");
    gFieldSymbol = *gensym(&s, "sns");
    gEmptySymbol_s00a6_2ec0 = gSymbolSymbol;
    return true;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a634a0
namespace EA { namespace Audio { namespace Eapd {
bool __fastcall InputParseSymbols(int kind, char** cursor, char* end, char** out1, PgSymbol* out2, int* out3, int* out4)
{
    char buf[0x18];
    char* text;
    if (kind == (int)gFieldKind) {
        memcpy_f(buf, *cursor, 0x19);
        *strchr_f(buf, 0x20) = 0;
        *cursor += 0x19;
        text = buf;
    } else if (kind == 2) {
        if (*cursor == end)
            return false;
        while (**cursor != 0) {
            ++*cursor;
            if (*cursor == end)
                break;
        }
        if (*cursor == end)
            return false;
        ++*cursor;
        text = *cursor;
    } else if (kind == 3) {
        text = *cursor + 4 + *(int*)*cursor;
        *cursor = text;
    } else {
        return false;
    }
    if (text == 0)
        return false;
    *gensym((PgSymbol*)buf, text);
    if (out1)
        *out1 = *(char**)((char*)buf + 4);
    *out2 = *gensym((PgSymbol*)buf, 0);
    if (kind == 3) {
        *out2 = *gensym((PgSymbol*)buf, *cursor);
        *cursor += 4;
    } else {
        *out2 = gSymbolSymbol;
    }
    *out3 = *(int*)*cursor;
    *cursor += 4;
    *out4 = (int)*cursor;
    *cursor += *out3;
    return true;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a63640
namespace EA { namespace Audio { namespace Eapd {
void EapdMapBase::DestroyAll(void* node)
{
    if (node == 0)
        return;
    void* next;
    do {
        DestroyAll(*(void**)node);
        next = *(void**)((char*)node + 4);
        void* alloc = (char*)this + 0x18;
        ((void (__thiscall*)(void*, void*))(*(void***)alloc)[3])(alloc, node);
        node = next;
    } while (next != 0);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a63680
namespace EA { namespace Audio { namespace Eapd {
bool EapdMapBase::HasKeyEvent(uint32_t key)
{
    void* found;
    void* n = ((RbTreeView*)((char*)this + 0x34))->find(&found, &key);
    return (char*)this + 0x38 == *(void**)n;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a636b0
namespace EA { namespace Audio { namespace Eapd {
bool EapdMapBase::HasKeyField(uint32_t key, int arg)
{
    void* found;
    void* n = ((RbTreeView*)((char*)this + 0x10))->find(&found, &key);
    (void)arg;
    return (char*)this + 0x14 != *(void**)n;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a636e0
namespace EA { namespace Audio { namespace Eapd {
void* EapdMapBase::Insert28(void** out, void* hint, uint32_t* key, char isEnd)
{
    int side;
    if (isEnd == 0 && hint != (char*)this + 4 && *key >= *(uint32_t*)((char*)hint + 0x10))
        side = 1;
    else
        side = 0;
    void* alloc = (char*)this + 0x18;
    void* node = ((void* (__thiscall*)(void*, unsigned))(*(void***)alloc)[2])(alloc, 0x28);
    if ((char*)node + 0x10 != 0) {
        uint32_t* d = (uint32_t*)((char*)node + 0x10);
        d[0] = key[0]; d[1] = key[1]; d[2] = key[2];
        d[3] = key[3]; d[4] = key[4]; d[5] = key[5];
    }
    RBTreeInsert(node, hint, (char*)this + 4, side);
    void** o = out;
    ++*(int*)((char*)this + 0x14);
    *o = node;
    return o;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a63770
namespace EA { namespace Audio { namespace Eapd {
void EapdMapBase::Insert1c(uint32_t* val, void* hint, uint32_t* key, char isEnd)
{
    int side;
    if (isEnd == 0 && hint != (char*)this + 4 && *key >= *(uint32_t*)((char*)hint + 0x10))
        side = 1;
    else
        side = 0;
    void* alloc = (char*)this + 0x18;
    void* node = ((void* (__thiscall*)(void*, unsigned))(*(void***)alloc)[2])(alloc, 0x1c);
    if ((char*)node + 0x10 != 0) {
        uint32_t* d = (uint32_t*)((char*)node + 0x10);
        d[0] = key[0]; d[1] = key[1]; d[2] = key[2];
    }
    RBTreeInsert(node, hint, (char*)this + 4, side);
    uint32_t* v = val;
    ++*(int*)((char*)this + 0x14);
    *v = (uint32_t)node;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a637f0
namespace EA { namespace Audio { namespace Eapd {
void EapdMapBase::Insert18(uint32_t* val, void* hint, uint32_t* key, char isEnd)
{
    int side;
    if (isEnd == 0 && hint != (char*)this + 4 && *key >= *(uint32_t*)((char*)hint + 0x10))
        side = 1;
    else
        side = 0;
    void* alloc = (char*)this + 0x18;
    void* node = ((void* (__thiscall*)(void*, unsigned))(*(void***)alloc)[2])(alloc, 0x18);
    if ((char*)node + 0x10 != 0) {
        uint32_t* d = (uint32_t*)((char*)node + 0x10);
        d[0] = key[0]; d[1] = key[1];
    }
    RBTreeInsert(node, hint, (char*)this + 4, side);
    ++*(int*)((char*)this + 0x14);
    *val = (uint32_t)node;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a63860
namespace EA { namespace Audio { namespace Eapd {
bool EapdMapBase::EraseEvent(uint32_t key, PgSymbol* out)
{
    bool ret = false;
    void* found;
    ((RbTreeView*)((char*)this + 0x34))->find(&found, &key);
    if ((char*)this + 0x38 != found) {
        uint32_t* ev = *(uint32_t**)((char*)found + 0x14);
        if (out) {
            out->mHash = ev[2];
            out->mpName = (const char*)ev[3];
        }
        void* f2;
        ((RbTreeView*)((char*)this + 0x10))->find(&f2, ev + 2);
        if ((char*)this + 0x14 != f2) {
            --*(int*)((char*)this + 0x24);
            (void)RBTreeIncrement(f2);
            RBTreeErase(f2, (char*)this + 0x14);
            void* alloc = (char*)this + 0x28;
            ((void (__thiscall*)(void*, void*))(*(void***)alloc)[3])(alloc, f2);
        }
        ((void (__thiscall*)(void*, uint32_t))(*(void***)this)[4])(this, key);
        ret = true;
    }
    return ret;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a63900
namespace EA { namespace Audio { namespace Eapd {
bool EapdMapBase::FindEventSample(uint32_t a0, uint32_t key, int sym2, uint32_t a4, uint32_t a5, uint32_t evKey, uint32_t* out1, uint32_t* out2)
{
    if (evKey == gEventSymbol.mHash && key == gSymbolSymbol.mHash) {
        key = a4;
        sym2 = (int)a5;
    }
    void* found;
    ((RbTreeView*)((char*)this + 0x10))->find(&found, &key);
    if ((char*)this + 0x14 == found)
        return false;
    uint32_t* node = *(uint32_t**)((char*)found + 0x18);
    void* range[2];
    ((RbMapView*)((char*)node + 0x10))->equal_range(range, &sym2);
    uint32_t* it = (uint32_t*)range[0];
    uint32_t* end = (uint32_t*)range[1];
    if (it == end)
        return false;
    while (it[6] != evKey) {
        it = (uint32_t*)RBTreeIncrement(it);
        if (it == end)
            return false;
    }
    *out1 = it[9];
    *out2 = it[8];
    ++*node;
    return true;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a63a50
namespace EA { namespace Audio { namespace Eapd {
void* EapdMapBase::FindOrInsert18(void** out, uint32_t* key)
{
    char* head = (char*)this + 4;
    char* parent = head;
    char cmp = 1;
    uint32_t* cur = *(uint32_t**)((char*)this + 0xc);
    if (cur) {
        do {
            parent = (char*)cur;
            cmp = (*key < cur[4]);
            cur = cmp ? *(uint32_t**)((char*)cur + 4) : *(uint32_t**)cur;
        } while (cur);
    }
    char* hint = parent;
    if (cmp) {
        if (parent == *(char**)((char*)this + 8)) {
            Insert18((uint32_t*)out, hint, key, 0);
            return out;
        }
        hint = (char*)RBTreeDecrement(parent);
    }
    if (*(uint32_t*)(hint + 0x10) < *key) {
        int side = !(parent == head || *key < *(uint32_t*)(parent + 0x10));
        void* alloc = *(void**)((char*)this + 0x18);
        void* node = ((void* (__thiscall*)(void*, unsigned))(*(void***)alloc)[2])(alloc, 0x18);
        if ((char*)node + 0x10 != 0) {
            uint32_t* d = (uint32_t*)((char*)node + 0x10);
            d[0] = key[0]; d[1] = key[1];
        }
        RBTreeInsert(node, parent, head, side);
        ++*(int*)((char*)this + 0x14);
        *(void**)out = node;
        ((uint8_t*)out)[4] = 1;
        return out;
    }
    *(char**)out = hint;
    ((uint8_t*)out)[4] = 0;
    return out;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a63b40
namespace EA { namespace Audio { namespace Eapd {
EapdMapBase::~EapdMapBase()
{
    DestroyAll(*(void**)((char*)this + 0xc));
    *(void**)((char*)this + 0x18) = (void*)0x1403934;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a63b90
namespace EA { namespace Audio { namespace Eapd {
bool EapdMapBase::ClearAll()
{
    bool ok = true;
    while (*(void**)((char*)this + 0x24) != 0)
        EraseEvent(*(uint32_t*)(*(uint32_t*)(*(uint32_t*)((char*)this + 0x18) + 0x18) + 4), 0);
    if (*(void**)((char*)this + 0x48) != 0) {
        ok = false;
        do {
            uint32_t* p = (uint32_t*)(*(uint32_t*)(*(uint32_t*)((char*)this + 0x3c) + 0x14));
            *p = 1;
            ((void (__thiscall*)(void*, uint32_t))(*(void***)this)[4])(this, p[1]);
        } while (*(void**)((char*)this + 0x48) != 0);
    }
    return ok;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a63bf0
namespace EA { namespace Audio { namespace Eapd {
void* EapdMapBase::FindOrInsert28(void** out, uint32_t* key)
{
    char* parent = (char*)this + 4;
    uint32_t* cur = *(uint32_t**)((char*)this + 0xc);
    if (cur) {
        do {
            parent = (char*)cur;
            cur = (*key < cur[4]) ? *(uint32_t**)((char*)cur + 4) : *(uint32_t**)cur;
        } while (cur);
    }
    Insert28(out, parent, key, 0);
    return out;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a63c30
namespace EA { namespace Audio { namespace Eapd {
void* EapdMapBase::Init(void* allocator, void* a3, void* a4, void* a5)
{
    mpAllocVtbl = a3;
    mpAllocator = a4;
    mpName = (const char*)a5;
    void* vtbl = *(void**)((char*)allocator + 4);
    *(void**)((char*)this) = 0;
    *(uint8_t*)((char*)this + 0x10) = 0;
    *(void**)((char*)this + 0x18) = 0;
    *(void**)((char*)this + 0x1c) = 0;
    void* sentinel = (char*)this + 0x14;
    *(void**)((char*)this + 0x20) = 0;
    mpOwner2c = vtbl;
    mpVtbl28 = (void*)0x1454fac;
    mpKind30 = "EAPd/map";
    *(void**)((char*)this + 0x14) = sentinel;
    *(void**)((char*)this + 0x18) = sentinel;
    *(void**)((char*)this + 0x1c) = 0;
    *(uint8_t*)((char*)this + 0x20) = 0;
    *(void**)((char*)this + 0x24) = 0;
    return this;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a63c90
namespace EA { namespace Audio { namespace Eapd {
void* EapdAssetManager::Init(void* allocator)
{
    void* vtbl = *(void**)((char*)allocator + 4);
    mpvtable = (void*)0x1455618;
    mpAllocVtbl = (void*)0x1454fac;
    mpAllocator = vtbl;
    mpName = "EAPd/AssetManager";
    void* bmSentinel = (char*)this + 0x14;
    *(uint8_t*)((char*)this + 0x10) = 0;
    *(void**)((char*)this + 0x18) = 0;
    *(void**)((char*)this + 0x1c) = 0;
    *(void**)((char*)this + 0x20) = 0;
    mpOwner2c = vtbl;
    mpVtbl28 = (void*)0x1454fac;
    mpKind30 = "EAPd/BinaryMap";
    *(void**)((char*)this + 0x14) = bmSentinel;
    *(void**)((char*)this + 0x18) = bmSentinel;
    *(void**)((char*)this + 0x1c) = 0;
    *(uint8_t*)((char*)this + 0x20) = 0;
    *(void**)((char*)this + 0x24) = 0;
    void* bmVtbl2 = *(void**)((char*)allocator + 4);
    *(void**)((char*)this + 0x3c) = 0;
    *(void**)((char*)this + 0x40) = 0;
    *(void**)((char*)this + 0x44) = 0;
    void* rmSentinel = (char*)this + 0x38;
    *(void**)((char*)this + 0x50) = bmVtbl2;
    *(void**)((char*)this + 0x4c) = (void*)0x1454fac;
    *(void**)((char*)this + 0x54) = (void*)"EAPd/ReleaseMap";
    *(void**)((char*)this + 0x38) = rmSentinel;
    *(void**)((char*)this + 0x3c) = rmSentinel;
    *(void**)((char*)this + 0x40) = 0;
    *(uint8_t*)((char*)this + 0x44) = 0;
    *(void**)((char*)this + 0x48) = 0;
    *(void**)((char*)this + 0x58) = 0;
    *(uint8_t*)((char*)this + 0x5c) = 0;
    return this;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a63d20
namespace EA { namespace Audio { namespace Eapd {
EapdAssetManager::~EapdAssetManager()
{
    mpvtable = (void*)0x1455618;
    ((EapdMapBase*)((char*)this + 0x20))->DestroyAll(*(void**)((char*)this + 0x40));
    *(void**)((char*)this + 0x4c) = (void*)0x1403934;
    ((EapdMapBase*)this)->DestroyAll(*(void**)((char*)this + 0x1c));
    *(void**)((char*)this + 0x2c) = (void*)0x1403934;
    mpAllocVtbl = (void*)0x1403934;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a63dd0
namespace EA { namespace Audio { namespace Eapd {
bool EapdAssetManager_s00a6_3dd0::Load(const char* data, unsigned size, PgSymbol* out)
{
    out->mHash = gEmptySymbol_s00a6_3dd0.mHash;
    out->mpName = gEmptySymbol_s00a6_3dd0.mpName;
    if (data == 0 || size <= 0x17)
        return false;

    const uint32_t* hdr = (const uint32_t*)data;
    if (hdr[0] != gAssetMagic || hdr[2] != 2)
        return false;
    uint32_t kind = hdr[1];
    if (kind != gFieldKind_s00a6_3dd0 && kind != 2 && kind != 3)
        return false;
    if (hdr[4] == 0)
        return false;

    const char* cursor = data + 0x18;
    const char* end = data + size;
    PgSymbol first, second;
    int count1 = 0, count2 = 0;
    if (!InputParseSymbols((int)kind, (char**)&cursor, (char*)end,
                           &first, &second, &count1, &count2))
        return false;

    out->mHash = first.mHash;
    out->mpName = first.mpName;

    // Asset records: hdr[4] maps followed by hdr[5] event records.  The real
    // loader interns each symbol pair into the manager's two maps and the
    // per-asset rb-tree; the slices' map helpers are not callable without the
    // full allocator/bootstrap state, so parse the records and keep the same
    // cursor/termination behavior.
    for (uint32_t i = 0; i < hdr[4]; ++i) {
        if (!InputParseSymbols((int)kind, (char**)&cursor, (char*)end,
                               &first, &second, &count1, &count2))
            return false;
    }
    for (uint32_t i = 0; i < hdr[5]; ++i) {
        if (!InputParseSymbols((int)kind, (char**)&cursor, (char*)end,
                               &first, &second, &count1, &count2))
            return false;
    }
    return true;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a64280
namespace EA { namespace Audio { namespace Eapd {
void EapdAssetManager_s00a6_3dd0::ReleaseEntryNode(AssetEntry* node)
{
    char* inner = (char*)node + 0x10;
    ((MapDestroyFace*)inner)->Destroy(*(void**)(inner + 0xc));
    *(void**)(inner + 0x18) = (void*)0x1403934;
    void** vtbl = *(void***)this;
    ((void (__thiscall*)(void*, void*))vtbl[3])(this, node);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a642f0
namespace EA { namespace Audio { namespace Eapd {
bool EapdAssetManager_s00a6_3dd0::ReleaseNodeAt34(uint32_t key)
{
    bool ok = false;
    char* tree = (char*)this + 0x34;
    void* found;
    ((RBTreeFindFace*)tree)->Find(&found, &key);
    char* val = (char*)found;
    if ((char*)this + 0x38 != val) {
        int* ref = *(int**)(val + 0x14);
        --*ref;
        if (*ref == 0) {
            char* cur = *(char**)((char*)this + 0x3c);
            while (cur != (char*)this + 0x38) {
                if (*(void**)(cur + 0x14) == ref) {
                    --*(int*)(tree + 0x14);
                    void* nx = RBTreeIncrement(cur);
                    RBTreeErase(cur, tree + 4);
                    void** alloc = *(void***)(tree + 0x18);
                    ((void (__thiscall*)(void*, void*))alloc[3])(tree + 0x18, cur);
                    cur = (char*)nx;
                } else {
                    cur = (char*)RBTreeIncrement(cur);
                }
            }
            ((EapdAssetManager_s00a6_3dd0*)((char*)this + 4))->ReleaseEntryNode((AssetEntry*)ref);
        }
        ok = true;
    }
    return ok;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a64390
namespace EA { namespace Audio { namespace Eapd {
void* EapdAssetManager_s00a6_3dd0::FreeSlot(void* a1, void* a2, void* a3)
{
    return ((AllocFace*)((char*)this + 0x10))->DestroyHelper(0x1c, a1, a2, a3);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a64400
namespace EA { namespace Audio { namespace Eapd {
void* EapdAssetManager_s00a6_3dd0::AllocFromPool(void* a1)
{
    (void)a1;
    void* n = *(void**)((char*)this + 0x28);
    if (n) {
        *(void**)((char*)this + 0x28) = *(void**)n;
    } else {
        n = ((void* (__thiscall*)(void*, unsigned))
             ((*(void***)((char*)this + 0x10))[2]))((char*)this + 0x10,
                                                     *(unsigned*)((char*)this + 0x1c));
    }
    if (n) {
        ++*(int*)((char*)this + 0x2c);
        unsigned c = *(unsigned*)((char*)this + 0x2c);
        if (c > *(unsigned*)((char*)this + 0x30))
            *(unsigned*)((char*)this + 0x30) = c;
    }
    return n;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a64470
namespace EA { namespace Audio { namespace Eapd {
AssetSlot* AssetSlot::Ctor()
{
    char* s = (char*)this;
    *(void**)(s + 8) = (void*)gTag15544b4;
    *(void**)(s + 0) = (void*)0x1454fac;
    *(void**)(s + 4) = 0;
    *(void**)(s + 0x14) = 0;
    *(void**)(s + 0x10) = (void*)0x1454fac;
    *(void**)(s + 0x18) = (void*)0x145562c;
    *(void**)(s + 0x20) = 0;
    *(void**)(s + 0x1c) = (void*)0x1454fac;
    *(void**)(s + 0x24) = (void*)0x145562c;
    *(void**)(s + 0x28) = 0;
    *(void**)(s + 0x2c) = 0;
    *(void**)(s + 0x30) = 0;
    *(void**)(s + 0x34) = 0;
    *(void**)(s + 0x38) = 0;
    *(void**)(s + 0x3c) = 0;
    *(void**)(s + 0xc) = (void*)0x14556c0;
    *(void**)(s + 0x40) = 0;
    *(void**)(s + 0x48) = s + 0x44;
    *(void**)(s + 0x44) = s + 0x44;
    *(void**)(s + 0x50) = s + 0x4c;
    *(void**)(s + 0x4c) = s + 0x4c;
    return this;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a644e0
namespace EA { namespace Audio { namespace Eapd {
void AssetSlot::Free(void* node)
{
    char* n = (char*)node;
    void* prev = *(void**)(n + 4);
    void* next = *(void**)n;
    *(void**)prev = next;
    *(void**)((char*)next + 4) = prev;
    *(void**)n = 0;
    *(void**)(n + 4) = 0;
    char* alloc = (char*)this + 0xc;
    void** vtbl = *(void***)alloc;
    ((void (__thiscall*)(void*, void*))vtbl[3])(alloc, node);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a64560
namespace EA { namespace Audio { namespace Eapd {
bool EapdAssetManager_s00a6_3dd0::FreeAll()
{
    char* sent = (char*)this + 0x4c;
    char* cur = *(char**)sent;
    char seen = 0;
    if (cur != sent) {
        char* alloc = (char*)this + 0xc;
        seen = 1;
        do {
            char* next = *(char**)cur;
            char* prev = *(char**)(cur + 4);
            *(char**)prev = next;
            *(char**)(next + 4) = prev;
            *(void**)cur = 0;
            *(void**)(cur + 4) = 0;
            void** vtbl = *(void***)alloc;
            ((void (__thiscall*)(void*, void*))vtbl[3])(alloc, cur);
            cur = next;
        } while (cur != sent);
    }
    return !seen;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a645c0
namespace EA { namespace Audio { namespace Eapd {
void EapdAssetManager_s00a6_3dd0::RearrangeLists()
{
    char* a44 = (char*)this + 0x44;
    char* a4c = (char*)this + 0x4c;
    void* d4c = *(void**)a4c;
    void* d44 = *(void**)a44;
    void* e4c = *(void**)(a4c + 4);
    void* e44 = *(void**)(a44 + 4);
    *(void**)a44 = d4c;
    *(void**)(a44 + 4) = e4c;
    *(void**)a4c = d44;
    *(void**)(a4c + 4) = e44;

    if (*(void**)a44 == a4c) {
        *(void**)(a44 + 4) = a44;
        *(void**)a44 = a44;
    } else {
        void* p = *(void**)(a44 + 4);
        *(void**)p = a44;
        void* q = *(void**)a44;
        *(void**)((char*)q + 4) = a44;
    }
    if (*(void**)a4c == a44) {
        *(void**)(a4c + 4) = a4c;
        *(void**)a4c = a4c;
    } else {
        void* p = *(void**)(a4c + 4);
        *(void**)p = a4c;
        void* q = *(void**)a4c;
        *(void**)((char*)q + 4) = a4c;
    }

    void* cur = *(void**)a44;
    while (cur != a44) {
        void* next = *(void**)cur;
        int r = ((int (__thiscall*)(void*))*(void**)((char*)cur + 8))(cur);
        if (r == 0) {
            void* v = *(void**)((char*)cur + 4);
            *(void**)v = next;
            *(void**)((char*)next + 4) = v;
            *(void**)cur = 0;
            *(void**)((char*)cur + 4) = 0;
            char* alloc = (char*)this + 0xc;
            void** vtbl = *(void***)alloc;
            ((void (__thiscall*)(void*, void*))vtbl[3])(alloc, cur);
        } else {
            void* link = (char*)cur + 4;
            void* tail = *(void**)(a4c + 4);
            *(void**)link = tail;
            *(void**)cur = a4c;
            *(void**)(a4c + 4) = cur;
            *(void**)tail = cur;
        }
        cur = next;
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a646d0
namespace EA { namespace Audio { namespace Eapd {
void ThrowHelper(void* p)
{
    (void)p;
    ((void (__cdecl*)(void*))uThrowTarget)((void*)0x13f5b98);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a647b0
namespace EA { namespace Audio { namespace Eapd {
int SendFloatToAll(void* atom)
{
    char* a = (char*)atom;
    char* base = *(char**)(a + 0xc);
    float f = atom_getfloat(a + 0x10);
    void* n = *(void**)(base + 4);
    while (n) {
        void* c = *(void**)((char*)n + 0x28);
        ++gDepth167545c;
        if (gDepth167545c < 1000) {
            void* e = *(void**)((char*)c + 8);
            while (e) {
                outlet_float_(*(void**)((char*)e + 4), f);
                e = *(void**)e;
            }
        }
        --gDepth167545c;
        n = *(void**)((char*)n + 0x40);
    }
    return 0;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a64820
namespace EA { namespace Audio { namespace Eapd {
int SendSymbolToAll(void* atom)
{
    char* a = (char*)atom;
    char* base = *(char**)(a + 0xc);
    PgSymbol sym;
    atom_getsymbol(&sym, a + 0x10);
    void* n = *(void**)(base + 4);
    while (n) {
        void* c = *(void**)((char*)n + 0x28);
        outlet_list_(c, (void*)sym.mHash, (void*)sym.mpName);
        n = *(void**)((char*)n + 0x40);
    }
    return 0;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a64870
namespace EA { namespace Audio { namespace Eapd {
int SendSymbolList(void* atom)
{
    void* n = *(void**)((char*)(*(void**)((char*)atom + 0xc)) + 4);
    while (n) {
        outlet_symbol_(*(void**)((char*)n + 0x28));
        n = *(void**)((char*)n + 0x40);
    }
    return 0;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a649b0
namespace EA { namespace Audio { namespace Eapd {
void* EapdAssetManager_s00a6_3dd0::GetTwoWords(void* out)
{
    char* p = *(char**)((char*)this + 0x70);
    void* a = *(void**)(p + 0x64);
    void* b = *(void**)(p + 0x68);
    *(void**)out = a;
    *(void**)((char*)out + 4) = b;
    return out;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a649d0
namespace EA { namespace Audio { namespace Eapd {
void* EapdAssetManager_s00a6_3dd0::RealizeDollar(void* out)
{
    void* g = *(void**)((char*)this + 0x70);
    canvas_realizedollar2(out, g);
    return out;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a64a10
namespace EA { namespace Audio { namespace Eapd {
int PauseCanvas(void* entry)
{
    float f = *(float*)((char*)entry + 0x14);
    void* c = *(void**)((char*)entry + 0xc);
    canvas_pause_(*(void**)((char*)c + 0x70), f);
    return 0;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a64aa0
namespace EA { namespace Audio { namespace Eapd {
void EapdAssetManager_s00a6_3dd0::MakeFloatHandler2(uint8_t v)
{
    void* sys = SystemGetAssetManager();
    AssetEntry* e = ((EapdAssetManager_s00a6_3dd0*)sys)->NewEntryNode((void*)this, (void*)0xa64a10);
    e->mKind10 = 1;
    e->mFloat14 = (float)v;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a65f90
bool InstanceManager::Init(uint32_t size, uint32_t a2, uint32_t a3)
{
    ((FixedPool*)((char*)this + 8))->Init(0x78, size, (void*)a2, (void*)a3);
    PdInletRelease((char*)this + 0x3c, (void*)size, (void*)a2, (void*)a3);
    PdOutletInit((char*)this + 0x90, (void*)size, (void*)a2, (void*)a3);
    return true;
}

// @ 0x00a65fe0
bool InstanceManager::FlushAll()
{
    Hashtable& h = mBindings;
    HashNode* node = *h.mpBucketArray;
    if (!node) {
        HashNode** b = h.mpBucketArray + 1;
        while (!*b)
            ++b;
        node = *b;
    }
    while (node != h.mpBucketArray[h.mnBucketCount]) {
        PdSymRelease(this, node->mKey);
        node = *h.mpBucketArray;
        if (!node) {
            HashNode** b = h.mpBucketArray + 1;
            while (!*b)
                ++b;
            node = *b;
        }
    }
    return true;
}

// @ 0x00a66070
void* InstanceManager::InsertParam(void* out, uint32_t* key)
{
    Hashtable& h = mBindings;
    HashFind it = HashTableFind(&h, key);
    if (it.mpNode == h.mpBucketArray[h.mnBucketCount]) {
        uint32_t local[6];
        local[0] = *key;
        local[1] = 0;
        local[2] = 0;
        local[3] = 0;
        local[4] = 0;
        local[5] = 0;
        PdPatchInsert(&it, local, (void*)0);
    }
    (void)out;
    return (char*)it.mpNode + 4;
}

// @ 0x00a660e0
void Hashtable::ClearBuckets(HashNode** arr, uint32_t n)
{
    for (uint32_t i = 0; i < n; ++i) {
        HashNode* node = arr[i];
        while (node) {
            HashNode* next = node->mpNext;
            HashNode* chain = (HashNode*)node->mValue;
            while (chain != (HashNode*)((char*)node + 8)) {
                HashNode* c2 = (HashNode*)chain->mKey;
                *(void**)((char*)chain + 4) = 0;
                *(void**)chain = 0;
                chain = c2;
            }
            *(void**)((char*)node + 0xc) = 0;
            *(void**)((char*)node + 8) = 0;
            if (node != (HashNode*)mAlloc.mpBucketBuffer) {
                --mAlloc.mnCurrentSize;
                if ((uint8_t*)node < (uint8_t*)mAlloc.mpPoolBegin ||
                    (uint8_t*)node >= (uint8_t*)mAlloc.mpPoolEnd) {
                    void* a = &mAlloc.mOverflowAllocator;
                    ((void (__thiscall*)(void*, void*))(*(void***)a)[3])(a, node);
                } else {
                    *(void**)node = mAlloc.mpHead;
                    mAlloc.mpHead = node;
                }
            }
            node = next;
        }
        arr[i] = 0;
    }
}

// @ 0x00a66170
CursorValue* CursorTable::InsertIfAbsent(const CursorValue* value)
{
    CursorIter it = FindNode(value);
    if (it.mpNode != mpBucketArray[mnBucketCount])
        return (CursorValue*)((char*)it.mpNode + 8);
    CursorValue pair = *value;
    InsertResult res;
    Insert(&res, &pair, false);
    return (CursorValue*)((char*)res.mpNode + 8);
}

// @ 0x00a66550
void Hashtable::Destruct()
{
    ClearBuckets(mpBucketArray, mnBucketCount);
    HashNode* p = (HashNode*)mpBucketArray;
    mnElementCount = 0;
    if (mnBucketCount > 1 && p != (HashNode*)mAlloc.mpBucketBuffer) {
        --mAlloc.mnCurrentSize;
        if ((uint8_t*)p < (uint8_t*)mAlloc.mpPoolBegin ||
            (uint8_t*)p >= (uint8_t*)mAlloc.mpPoolEnd) {
            void* v = &mAlloc.mOverflowAllocator;
            ((void (__thiscall*)(void*, void*))(*(void***)v)[3])(v, p);
        } else {
            *(void**)p = mAlloc.mpHead;
            mAlloc.mpHead = p;
        }
    }
    mAlloc.DestroyAllocator();
}

// @ 0x00a66670
InstanceManager::~InstanceManager()
{
    HashtableDtor90((char*)this + 0x90);
    mSymbols.Destruct();
    mField38 = (void*)0x1403934;
    ((FixedPool*)((char*)this + 8))->~FixedPool();
}

// @ 0x00a66830
EapdSystemOverflow::~EapdSystemOverflow()
{
    mpVtbl = (void*)&vtbl_EAPd_SystemOverflow;
    if (mpArena) {
        void* a = &mpAlloc;
        ((void (__thiscall*)(void*, void*))(*(void***)a)[3])(a, mpArena);
    }
    mField10 = 0x1403934;
    mpAlloc = (void*)0x1403934;
    mpVtbl = (void*)0x1403934;
}

// @ 0x00a66900
void* EapdSystemOverflow::Alloc(uint32_t n)
{
    char* cur = (char*)mpCursor;
    void* r = cur;
    if ((uint32_t)cur + n <= (uint32_t)mpLimit)
        mpCursor = cur + n;
    else
        r = ((void* (__thiscall*)(void*, uint32_t))(*(void***)((char*)this + 0x10))[2])((char*)this + 0x10, n);
    if (r)
        mUsed += n;
    return r;
}

// @ 0x00a66930
void EapdSystemOverflow::Free(void* p)
{
    if ((uint32_t)p >= (uint32_t)mpArena && (uint32_t)p < (uint32_t)mpLimit)
        return;
    void* a = (char*)this + 0x10;
    ((void (__thiscall*)(void*, void*))(*(void***)a)[3])(a, p);
}

// @ 0x00a66970
uint32_t EapdHashString(const char* s)
{
    uint32_t h = 0x811c9dc5;
    uint32_t c = (uint8_t)*s;
    while (c != 0) {
        ++s;
        h = h * 0x1000193 ^ (uint32_t)tolower((int)c);
        c = (uint8_t)*s;
    }
    return h;
}

// @ 0x00a669b0
uint32_t SymbolManager::HashCall(uint32_t a)
{
    return mHashFunction((const char*)a);
}
