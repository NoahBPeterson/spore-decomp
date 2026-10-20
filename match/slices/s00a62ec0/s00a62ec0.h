// Shared declarations for slice s00a62ec0.
// EA::Audio::Eapd (EA's embedded Pure Data) "x_input" / "x_thisinstance" wrapper family plus
// the EASTL rbtree/multimap helpers and the EAPd map / asset-manager constructor + destructor
// classes that live alongside them.  Layouts and addresses are taken from the original
// disassembly and the 2008 dev-build PDB symbol names.
#pragma once
#include "types.h"

namespace EA { namespace Audio { namespace Eapd {

struct t_class;

struct PgSymbol {              // t_symbol: by-value pair (hash, name pointer)
    uint32_t    mHash;         // +0x00
    const char* mpName;        // +0x04
};

// --- the "input" object (class size 0x44) ----------------------------------
struct XInput {
    uint32_t    mGobj[10];     // +0x00  t_gobj/t_text header
    void*       mpOutlet;      // +0x28  outlet_new result
    void*       mpParam1;      // +0x2c
    void*       mpParam2;      // +0x30
    void*       mpParam3;      // +0x34
    uint8_t     mbPaused;      // +0x38
    void*       mpIface;       // +0x3c  instance interface (vtbl +0x1c = Notify)
};

// --- the "thisinstance" object (class size 0x2c) ---------------------------
struct XThisInstance {
    uint32_t    mGobj[0x28 / 4];  // +0x00
    void*       mpInstance;       // +0x28
    uint32_t    pad2c[0xc];       // +0x2c .. +0x5b (12 dwords)
    uint8_t     mbInstanceFlag;   // +0x5c
    bool        StoreFlag(uint8_t flag);   // 0x00a633e0
};

// --- the EAPd/map family ---------------------------------------------------
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

// "EAPd/AssetManager" owns a BinaryMap and a ReleaseMap.
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

// --- globals ---------------------------------------------------------------
extern t_class* gpInputClass;        // 0x0167585c
extern t_class* gpInstanceClass;     // 0x01675860
extern PgSymbol gEventSymbol;        // 0x01675864
extern PgSymbol gFieldSymbol;        // 0x0167586c
extern PgSymbol gEmptySymbol;        // 0x01675874
extern PgSymbol gGrandSymbol;        // 0x0167587c
extern PgSymbol gGrpSymbol;          // 0x01675884
extern PgSymbol gSymbolSymbol;       // 0x01675894
extern PgSymbol gBangSymbol;         // 0x016758b4
extern PgSymbol gFloatSymbol;        // 0x016758c4
extern PgSymbol gBangSym2;           // 0x016758b8
extern PgSymbol gFloatSym2;          // 0x016758c8
extern PgSymbol gSymbolSym2;         // 0x01675898
extern uint32_t gFieldKind;          // 0x015544ac

// --- external helpers ------------------------------------------------------
PgSymbol* gensym(PgSymbol* out, const char* s);                       // 0x00a675f0
t_class*  class_new7(PgSymbol name, int size, void* freemethod, void* newmethod,
                     int a1, int a2, int a3);                         // 0x00a48ea0
bool      class_addcreator(void* fn, PgSymbol name, int mkArg, int a); // 0x00a48e00
bool      class_addmethod1(t_class* c, void* fn, PgSymbol name, int a1, int a2); // 0x00a48a80
void*     pd_new(t_class* c);                                        // 0x00a49390
void      pd_free(void* x);                                          // 0x00a493d0
void*     outlet_new(void* owner, PgSymbol s, PgSymbol s2);          // 0x00a49d30
void*     canvas_getcurrentinstance();                               // 0x00a4a450
void*     canvas_getcurrent();                                       // 0x00a4a430
void*     canvas_realizedollar2(void* out, void* glist);             // 0x00a4a5d0
struct ParamSink { void SetParam(bool f); };                       // 0x00a649f0
void*     InputCreate(int kind, PgSymbol sym, PgSymbol sym2,
                      void* a, void* b);                             // 0x00a67cf0
void*     InstanceCreate(void* inst, int kind, PgSymbol sym, PgSymbol sym2,
                         void* a, void* b);                          // 0x00ff5b80

// methods defined in this slice
void* __stdcall x_input_new_reg(void* iface, PgSymbol sym, PgSymbol sym2,
                                void* p4, void* p5);                 // 0x00a62ec0
void  input_bang(XInput* x);                                         // 0x00a62f30
void* input_new_float_local(void* a, void* b);                       // 0x00a62f40
void* input_new_symbol(void* a, void* b);                            // 0x00a62f80
void* input_new_bang_local(void* a, void* b);                        // 0x00a62fc0
void* input_new_globalfloat(void* a, void* b);                       // 0x00a63000
void* input_new_globalsymbol(void* a, void* b);                      // 0x00a63030
void* input_new_globalevent(void* a, void* b);                       // 0x00a63060
void  pause_float(XInput* x, float f);                               // 0x00a63090
bool  x_input_setup();                                               // 0x00a630c0
void* instance_new();                                                // 0x00a632e0
void  busy_float(XThisInstance* x, float f);                         // 0x00a63310
bool  x_thisinstance_setup();                                        // 0x00a63350
bool  __fastcall InputParseSymbols(int kind, char** cursor, char* end, PgSymbol* out1,
                                   PgSymbol* out2, int* out3, int* out4);  // 0x00a634a0
PgSymbol* GetGroupSymbol(PgSymbol* out);                             // 0x00a635d0

extern "C" char* strchr_f(const char* s, int c);
extern "C" void* memcpy_f(void* d, const void* s, unsigned n);
extern "C" void  RBTreeInsert(void* node, void* parent, void* head, int side); // 0x009216a0
extern "C" void* RBTreeIncrement(void* node);                        // 0x00921580
extern "C" void* RBTreeDecrement(const void* node);                  // 0x009215c0
extern "C" void  RBTreeErase(void* node, void* head);                // 0x00921880
struct RbTreeView { void* find(void* out, const void* key); };     // 0x00e5c780
struct RbMapView  { void  equal_range(void* out, const void* key); }; // 0x00d4b450

}}}
