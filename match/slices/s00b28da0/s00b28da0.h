// Shared declarations for slice s00b28da0.
// SP::Simulator save-game bootstrap helpers (batch gold7).  These are the
// functions that rebuild the simulator data vectors from a save, run the
// save-game bootstrap (00b28ec0) and the reload path (00b294c0).
// Layouts / addresses come from the annotated disassembly and the 2008
// dev-build PDB names, cross-checked against the sibling s00c368c0.
#pragma once
#include "types.h"

// ---------------------------------------------------------------------------
// Named globals (address-identity only; values live in the original image)
// ---------------------------------------------------------------------------
extern uint8_t g_vtblRefBaseA22[];      // 0x013eb90c  ??_7RefBaseA22@@6B@
extern uint8_t g_vtblRefBaseA22b[];     // 0x013eb844
extern uint8_t g_vtblITracerBase[];     // 0x013eb938  ??_7ITracerBase@Trace@EA@@6B@
extern uint8_t g_vtblContentValid[];    // 0x013ec458  vtbl_cContentValidationSummarizer
extern uint8_t g_vtblAddRef[];          // 0x0145faa8
extern uint8_t g_vtblAddRef2[];         // 0x0145fa98
extern uint8_t g_str145f924[];          // 0x0145f924  "Simulator/SimSingleton"
extern uint8_t g_str145ed5c[];          // 0x0145ed5c  "Simulator/NounDefinition"
extern uint8_t g_str13f09b4[];          // 0x013f09b4  "Simulator"
extern uint8_t g_wstrLtmp[];            // 0x0143e774  L".tmp"
extern uint8_t g_wstr1458e48[];         // 0x01458e48
extern uint8_t g_wstrDB96[];            // 0x0145897c
extern uint8_t g_defSaveName[];         // 0x0167df60  default saved-game filename (WStr)
extern uint8_t g_167df64[];             // 0x0167df64
extern uint8_t g_u__spo_015689a8[];     // 0x015689a8  L".spo"
extern uint8_t g_p167a60c[];            // 0x0167a60c  SimSingleton* singleton cache
extern uint8_t g_mode1654c00[];         // 0x01654c00
extern uint8_t g_mode1654c04[];         // 0x01654c04

// ---------------------------------------------------------------------------
// forward callees (address-identity only)
// ---------------------------------------------------------------------------
void   __cdecl FUN_00c710e0();                       // 0x00c710e0
void   __cdecl FUN_00c71100();                       // 0x00c71100
void   __cdecl FUN_00c710f0(void* p);                // 0x00c710f0
void   __cdecl FUN_00c710b0(void* p);                // 0x00c710b0

// the vector owner: the four c710xx helpers are thiscalls on it
struct C710Owner {
    void FUN_00c710e0();       // 0x00c710e0
    void FUN_00c71100();       // 0x00c71100
    void FUN_00c710f0(void* p);// 0x00c710f0
    void FUN_00c710b0(void* p);// 0x00c710b0
};

extern uint8_t g_18c6d19[];                          // 0x018c6d19
extern uint8_t g_18c816a[];                          // 0x018c816a

struct NounMgr {
    void* GetGameDataVector(void* a, void* b, void* c, void* d, void* e);
};
NounMgr* __cdecl NounManager();                      // 0x00b3d300

void*  __cdecl FUN_010212f0();                       // 0x010212f0
void*  __cdecl FUN_01021300();                       // 0x01021300  GetPlayerEmpire
void*  __cdecl FUN_01021370();                       // 0x01021370  GetPlayerHomePlanet
void*  __cdecl FUN_01021230();                       // 0x01021230
void*  __cdecl FUN_01021080();                       // 0x01021080  GetUniverseContext

struct C4F030Obj { void FUN_00d056c0(); };            // 0x00d056c0
struct StarMgr { C4F030Obj* FUN_00c4f030(uint32_t v); };
StarMgr* __cdecl StarManager();                      // 0x00b3d2a0

void*  __cdecl FUN_00f473a0(uint32_t size, const char* name, uint32_t a, uint32_t b, uint32_t c, uint32_t d);
void   __cdecl FUN_00f47380(void* p);

struct TribeData { TribeData* Ctor(uint32_t owner); };  // 0x00ff0610
void*      __cdecl FUN_00ff3360(uint32_t owner);     // 0x00ff3360
struct SimObjData { SimObjData* Ctor(uint32_t owner); }; // 0x00ff3360

void   __cdecl FUN_00cd7d10();
void   __cdecl FUN_00d3d420();
void   __cdecl FUN_00accbb0();
void   __cdecl FUN_00acdff0();
void   __cdecl FUN_00b1e500();
void   __cdecl FUN_00b21080();
void   __cdecl FUN_00b236c0();
void   __cdecl FUN_00b211e0(void* a, void* b);
void   __cdecl FUN_00b268a0(uint32_t a);
void*  __cdecl FUN_00b3d230();

void*  __cdecl MessageServer();                      // 0x0067dcc0
void*  __cdecl GetSetting9();                        // 0x00401090
void*  __cdecl FUN_004df420();                       // 0x004df420

uint32_t __cdecl GetCurrentGameMode();               // 0x00b5b800

void   __cdecl FUN_00ae9790();
uint8_t __cdecl FUN_00baad00();                      // 0x00baad00
void   __cdecl FUN_00baecc0(uint32_t a, uint32_t b);
void*  __cdecl FUN_00bb3750();
void   __cdecl FUN_00bb59b0(void* planet, void* key);
void   __cdecl FUN_00bb4ba0();
void   __cdecl FUN_00bb66f0();
void*  __cdecl FUN_00bb9950();
void   __cdecl FUN_00bb9ad0(uint32_t a);
void   __cdecl FUN_00bb9b00(uint32_t a, uint32_t b);
void*  __cdecl FUN_00c30c60();
void   __cdecl FUN_00c8b570(void* a);
void   __cdecl FUN_00c8b590(uint32_t a);
void*  __cdecl FUN_00ecdba0();
void   __cdecl FUN_00e5c4d0(void* a);

void*  __cdecl PathJoin(void* out, const void* a, const void* b); // 0x0057cba0
void*  __cdecl PathPick(void* out, void* a, void* b); // 0x00688f00

void   __cdecl FUN_00692ea0();
void   __cdecl FUN_00693900();
void   __cdecl FUN_00693d60(void* a, void* b, void* c, void* d);
void*  __cdecl FUN_00675250(void* a);
void   __cdecl FUN_006755c0(void* a);
void*  __cdecl FUN_006891f0(void* a, void* b);
void   __cdecl FUN_006b2350();
void   __cdecl FUN_006b4840();
void   __cdecl FUN_00421cf0(void* a);

void   __cdecl FUN_00ae5930(void* a);
void*  __cdecl FUN_00ae5c30(void* self);

void   __cdecl FUN_006a1c40(void* self);
void*  __cdecl FUN_0067de30();
uint8_t __cdecl FUN_00b282e0(void* self);
uint8_t __cdecl FUN_00b28750(void* self);

struct PlanetModelC { void* GetPlanetKey(); };        // 0x00b7e380
PlanetModelC* __cdecl PlanetModel();                 // 0x00b3d350

void   __cdecl FUN_00b28da0(void* a);
void   __fastcall FUN_00b28ec0(void* self, void* dummy, const void* name, uint8_t flag);
uint8_t __fastcall FUN_00b294c0(void* self, void* dummy, const void* name, uint8_t flag);

// extra callees / globals used by the save-bootstrap and reload paths
extern uint8_t g_18c43e8[];                          // 0x018c43e8
extern uint8_t g_word1897c18[];                      // 0x01897c18
extern uint8_t g_singleton167a60c[];                 // 0x0167a60c  (SimSingleton*)
extern uint8_t g_defName167df60[];                   // 0x0167df60  (eastl wstring)
extern uint8_t g_defNameEnd167df64[];                // 0x0167df64
extern uint8_t g_u__spo_15689a8[];                   // 0x015689a8

void   __cdecl FUN_00c8b570v(void* a);
void   __cdecl FUN_00c8b590v(uint32_t a);
void   __cdecl FUN_00bb3750v();
void*  __cdecl FUN_01021230v();
void*  __cdecl FUN_01021370v();
void   __cdecl FUN_00f47380v(void* p);
uint8_t __cdecl FUN_00b282e0v(void* self);
uint8_t __cdecl FUN_00b28750v(void* self);
void   __cdecl FUN_00bb4ba0v();
void   __cdecl FUN_00bb66f0v();
void*  __cdecl FUN_00bb9950v();
void   __cdecl FUN_00bb9ad0v(uint32_t a);
void   __cdecl FUN_00bb9b00v(uint32_t a, uint32_t b);
void   __cdecl FUN_00baecc0v(uint32_t a, uint32_t b);
void   __cdecl FUN_00ae9790v();
void   __cdecl FUN_00b268a0v(uint32_t a);
void*  __cdecl FUN_00b3d230v();
void*  __cdecl FUN_00b211e0v(void* a, void* b);
void   __cdecl FUN_00692ea0v();
void   __cdecl FUN_00693900v();
void*  __cdecl FUN_00693d60v(uint32_t a, uint32_t b, uint32_t c, void* d);
void*  __cdecl FUN_00675250v(void* a);
void   __cdecl FUN_006755c0v(void* a);
void*  __cdecl FUN_006891f0v(void* a, void* b);
void   __cdecl FUN_006b2350v();
void   __cdecl FUN_006b4840v();
void   __cdecl FUN_00421cf0v(void* a);
void*  __cdecl FUN_00ae5c30v(void* self);
void   __cdecl FUN_00ae5930v(void* a);
void*  __cdecl FUN_006a1c40v(void* self);
void*  __cdecl FUN_0067de30v();
void   __cdecl FUN_00e5c4d0v(void* a);
void*  __cdecl FUN_00ecdba0v();
uint8_t __cdecl FUN_00baad00v();
void*  __cdecl MessageServerv();
void*  __cdecl GetSetting9v();
void*  __cdecl FUN_004df420v(void* a);
void*  __cdecl FUN_00c30c60v();
void*  __cdecl PathJoinv(void* out, const void* a, const void* b);   // 0x0057cba0
void*  __cdecl PathPickv(void* out, void* a, void* b);               // 0x00688f00
void   __fastcall FUN_00b28ec0v(void* self, void* dummy, const void* name, uint8_t flag);
uint8_t __fastcall FUN_00b294c0v(void* self, void* dummy, const void* name, uint8_t flag);

// eastl wstring (three pointers; assign + range_initialize are out of line)
struct EWStr {
    uint32_t* mBegin;
    uint32_t* mEnd;
    uint32_t* mCap;
    void assign(uint32_t* first, uint32_t* last);   // 0x00423650
    void range_initialize(const wchar_t* str);      // 0x00579a90
};

// cPropertyList (0x38 bytes; ctor at 0x006a1c40)
struct PropertyList {
    virtual uint32_t v00();
    virtual void     v04();
    virtual void     v08();
    virtual void     v0c();
    virtual void     v10();
    virtual void     v14();
    virtual void     v18();
    virtual void     v1c();
    virtual void     v20();
    virtual void     v24();
    virtual void     v28();
    virtual void     v2c(uint32_t a);
};

// PropertyManager: slot 0x34 is Add(propList, keyA, keyB)
struct PropMgr {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2c();
    virtual void v30();
    virtual void v34(void* propList, uint32_t keyA, uint32_t keyB);
};

// PlanetModel: +0x24 is an interface whose slots 0x80/0x84/0x08 are used.
struct PlanetModelIface {
    virtual void     v00();
    virtual void     v04();
    virtual void     v08();
    virtual void     v0c();
    virtual void     v10();
    virtual void     v14();
    virtual void     v18();
    virtual void     v1c();
    virtual void     v20();
    virtual void     v24();
    virtual void     v28();
    virtual void     v2c();
    virtual void     v30();
    virtual void     v34();
    virtual void     v38();
    virtual void     v3c();
    virtual void     v40();
    virtual void     v44();
    virtual void     v48();
    virtual void     v4c();
    virtual void     v50();
    virtual void     v54();
    virtual void     v58();
    virtual void     v5c();
    virtual void     v60();
    virtual void     v64();
    virtual void     v68();
    virtual void     v6c();
    virtual void     v70();
    virtual void     v74();
    virtual void     v78();
    virtual void     v7c();
    virtual void     v80();
    virtual uint32_t v84();
};

struct PlanetModelObj {
    uint32_t pad00[9];
    PlanetModelIface* mp24;   // +0x24
};
PlanetModelObj* __cdecl PlanetModelV();              // 0x00b3d350

// AutoRefCount object (the +0x44 byte is the "dirty" flag)
struct AutoRefPlate { uint8_t pad00[0x44]; uint8_t mDirty; };

// ---------------------------------------------------------------------------
// eastl string view (three pointers; assign/range_initialize are out of line)
// ---------------------------------------------------------------------------
struct WStr {
    uint32_t* mBegin;   // +0x00
    uint32_t* mEnd;     // +0x04
    uint32_t* mCap;     // +0x08
    void assign(uint32_t* first, uint32_t* last);        // 0x00423650
    void range_initialize(const wchar_t* str);           // 0x00579a90
};

// ---------------------------------------------------------------------------
// small pointer-vector view used by the data-vector walks
// ---------------------------------------------------------------------------
struct GDVec {
    uint32_t  pad00;
    uint32_t* mBegin;   // +0x004
    uint32_t* mEnd;     // +0x008
};
