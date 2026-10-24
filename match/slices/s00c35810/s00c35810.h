// Shared declarations for slice s00c35810.
// SP::Simulator cGameBundle family (the space-stage object that owns a spatial
// object at +0x34 and an interaction target at +0x108), its ground-container
// sibling, and the small cEmpire/cGameBundle helpers around them.
// Layouts / addresses come from the annotated disassembly and the 2008 dev-build
// PDB names, cross-checked against siblings s00c368c0 / s00c035f0.
#pragma once
#include "types.h"

// ---------------------------------------------------------------------------
// Named globals (address-identity only; values live in the original image)
// ---------------------------------------------------------------------------
extern float g_Zero15812d0;      // 0x015812d0
extern float g_Zero15812d4;      // 0x015812d4
extern float g_Zero15812d8;      // 0x015812d8
extern float g_Zero15812dc;      // 0x015812dc
extern float g_Zero15812e0;      // 0x015812e0
extern float g_kThreeTenths;     // 0x013eb8c8   0.3
extern float g_kTwoHundredths;   // 0x013ef580   0.02
extern float g_kSixTenths;       // 0x013ec4b0   0.6
extern float g_kFive;            // 0x01486110   5.0
extern float g_kTen;             // 0x01473c70   10.0
extern float g_kTwentyFive;      // 0x013ebc5c   25.0
extern float g_kFifty;           // 0x013f1cac   50.0
extern float g_kOne;             // 0x01485720   1.0
extern float g_f168df38;         // 0x0168df38
extern float g_f168df3c;         // 0x0168df3c
extern float g_f168df40;         // 0x0168df40
extern float g_f1581338;         // 0x01581338
extern float g_f15812f4;         // 0x015812f4
extern float g_f15812f8;         // 0x015812f8
extern float g_f13ec4b8;         // 0x013ec4b8  (epsilon)
extern float g_f13ec5b4;         // 0x013ec5b4
extern void* g_p1a80d26;         // 0x01a80d26
extern void* g_p157a1f8;         // 0x0157a1f8
extern void* g_p1573038;         // 0x01573038
extern uint8_t g_p146b998[];     // 0x0146b998  vtbl cGameBundle
extern uint8_t g_p146b984[];     // 0x0146b984
extern uint8_t g_p146b8c0[];     // 0x0146b8c0
extern uint8_t g_p146b8a0[];     // 0x0146b8a0
extern uint8_t g_p146ba68[];     // 0x0146ba68
extern uint8_t g_p146ba58[];     // 0x0146ba58
extern uint8_t g_p146bac0[];     // 0x0146bac0
extern float g_f168df38;         // 0x0168df38
extern float g_f168df3c;         // 0x0168df3c
extern float g_f168df40;         // 0x0168df40
extern void* g_p15816b8;         // 0x015816b8
extern const wchar_t g_wcGameBundleContainer[];  // 0x0146b874
extern uint8_t g_p16dda8c[];     // 0x016dda8c  background-sim manager global
extern float g_f168df28;         // 0x0168df28
extern float g_f168df2c;         // 0x0168df2c
extern float g_f168df30;         // 0x0168df30
extern float g_quat168df04[];    // 0x0168df04  quaternion for Matrix3::Assign

// ---------------------------------------------------------------------------
// forward-declared callees (bodies live in sibling slices / other TUs)
// ---------------------------------------------------------------------------
void* __stdcall FUN_00695b40(void* a, void* b, const wchar_t* name); // 0x00695b40
uint32_t __cdecl FUN_00bba790();                     // 0x00bba790
uint32_t __cdecl FUN_01021090();                     // 0x01021090 (GetPlayerEmpireID)
void*   __cdecl FUN_0067dcc0();                      // 0x0067dcc0 (MessageServer)
uint32_t __cdecl FUN_00b3d2a0();                     // 0x00b3d2a0 (StarManager)
uint32_t __cdecl FUN_00b3d2b0();                     // 0x00b3d2b0
uint32_t __cdecl FUN_00b3d300();                     // 0x00b3d300 (NounManager)
uint32_t __cdecl FUN_00ac8730(void* p);              // 0x00ac8730
uint32_t __cdecl FUN_00baf630(uint32_t a);           // 0x00baf630
uint32_t __cdecl FUN_00ba5bc0(void* a, uint32_t b);  // 0x00ba5bc0
uint32_t __cdecl FUN_00c70150(void* obj, void* emp, uint32_t c); // 0x00c70150
uint32_t __cdecl FUN_00c34ee0(void* a, uint32_t b);  // 0x00c34ee0
uint32_t __cdecl FUN_00ce6950(void* self);           // 0x00ce6950
void     __cdecl FUN_00ac0450(void* p);              // 0x00ac0450
void     __cdecl FUN_00ac0520(void* p);              // 0x00ac0520
void     __cdecl FUN_00c8b2e0(void* p);              // 0x00c8b2e0
void     __cdecl FUN_00cee7e0(void* p);              // 0x00cee7e0
void     __cdecl FUN_00cee630(void* p);              // 0x00cee630
uint32_t __cdecl FUN_00cee3d0(void* p);              // 0x00cee3d0
uint32_t __cdecl FUN_00cee440(void* p);              // 0x00cee440
uint32_t __cdecl FUN_00cee2c0(void* obj, void* a, uint32_t b, float c, float d, int e); // 0x00cee2c0
uint32_t __cdecl FUN_00c0b7c0(void* p, void* q);     // 0x00c0b7c0
uint32_t __cdecl FUN_00c316c0(void* self, void* planet); // 0x00c316c0
void     __cdecl FUN_00c8a420(void* p);              // 0x00c8a420
void     __cdecl FUN_00b184c0(void* p);              // 0x00b184c0
uint32_t __stdcall FUN_00b3d350(uint32_t a, uint32_t b); // 0x00b3d350 (PlanetModel)
uint32_t __cdecl FUN_00b815a0();                     // 0x00b815a0
uint32_t __cdecl FUN_00b18550(void* p);              // 0x00b18550
void     __cdecl FUN_00b18420(void* p, uint32_t a);  // 0x00b18420
uint32_t __cdecl FUN_00b18590(void* p, uint32_t a);  // 0x00b18590
uint32_t __cdecl FUN_00b18600(void* p, uint32_t a);  // 0x00b18600
void     __cdecl FUN_00b18660(void* p);              // 0x00b18660
uint32_t __cdecl FUN_00c88a90(void* p, uint32_t a);  // 0x00c88a90
uint32_t __cdecl FUN_00c88b00(void* p, uint32_t a);  // 0x00c88b00
void     __cdecl FUN_00c89630(void* p);              // 0x00c89630
void     __cdecl FUN_00ac03d0(void* p);              // 0x00ac03d0
uint32_t __cdecl FUN_00c884a0(void* p, float f);     // 0x00c884a0
uint32_t __cdecl FUN_00b8de30(void* p);              // 0x00b8de30 (SortBanners)
void     __cdecl FUN_00692f90(void* self, void* a, void* b, uint32_t c); // 0x00692f90 (cVarListSerializer ctor)
void     __cdecl FUN_00692900(void* self, uint32_t stream);  // 0x00692900 Serialize
void     __cdecl FUN_00693e10(void* self, uint32_t stream);  // 0x00693e10 Read
uint32_t __cdecl FUN_00695960(void* self, uint32_t vec);     // 0x00695960 GetFields
uint32_t __cdecl FUN_0093aa70(void* stream, void* v, uint32_t n, int f); // 0x0093aa70 WriteUint32
uint32_t __cdecl FUN_0093a780(void* stream, void* v, uint32_t n, int f); // 0x0093a780 ReadInt32
void*    __cdecl FUN_00f473a0(uint32_t size, const char* tag, uint32_t a, uint32_t b, uint32_t c, uint32_t d); // 0x00f473a0 operator new
void     __cdecl FUN_01021ab0(void* glb, void* obj);  // 0x01021ab0 (thiscall on global)
void*    __cdecl FUN_0067ddd0();                      // 0x0067ddd0 (EffectsManagerPtr)
void     __cdecl FUN_00c36300(void* self);            // 0x00c36300

// ---------------------------------------------------------------------------
// cEmpire -- the player/AI empire object manipulated by the cEmpire helpers.
// ---------------------------------------------------------------------------
class cEmpire {
public:
    uint8_t  pad00[0x70];
    uint32_t* mAlliesBegin;   // +0x70
    uint32_t* mAlliesEnd;     // +0x74
    uint8_t  pad78[0x84 - 0x78];
    uint32_t mEmpireId;       // +0x84
    uint32_t* mStarsBegin;    // +0x88
    uint32_t* mStarsEnd;      // +0x8c
    uint8_t  pad90[0xb0 - 0x90];
    uint32_t mFieldB0;        // +0xb0
    uint32_t mCommContext;    // +0xb4

    uint32_t Remove(void* planet);   // 0x00c35810
};

// ---------------------------------------------------------------------------
// cGameBundle -- SP::Simulator space-stage bundle.
//   +0x00 vtable, +0x04 vtable2, +0x34 cSpatialObject, +0x108 cInteractionTarget
// ---------------------------------------------------------------------------
class cGameBundle {
public:
    void*    mpVtbl;       // +0x00
    void*    mpVtbl2;      // +0x04
    uint8_t  pad08[0x2c - 0x08];
    void*    mpOwner;      // +0x2c  (owned object with vtbl[1] dtor)
    uint8_t  pad30[0x34 - 0x30];
    uint8_t  mSpatial[0x108 - 0x34];   // cSpatialObject at +0x34
    uint8_t  mInteract[0x120 - 0x108]; // cInteractionTarget at +0x108
    void*    mpField120;   // +0x120
    uint8_t  mField124;    // +0x124
    uint8_t  pad125[3];
    void*    mpField128;   // +0x128
    uint32_t mField12c;    // +0x12c
    uint32_t mField130;    // +0x130
    float    mField134;    // +0x134
    uint8_t  mField138;    // +0x138

    cGameBundle* Ctor();                                   // 0xc35dc0
    void  Dtor();                                          // 0xc35f70
    void  Write(uint32_t s);                               // 0xc35c60
    void  Read(uint32_t s);                                // 0xc35cb0
    uint32_t GetFieldValues(uint32_t s);                   // 0xc35e70
    void  Reset128And2c();                                 // 0xc35fe0
    void  Set12c134(uint32_t a, float f);                  // 0xc35b20
    uint32_t ComputeState();                               // 0xc35b60
    bool  IsState0Or4();                                   // 0xc35d20
    bool  IsState234();                                    // 0xc35d40
    void* CastTo(uint32_t key);                            // 0xc35ad0
};

// ---------------------------------------------------------------------------
// cGameBundleGroundContainer -- the ground-stage sibling (0x60 bytes).
// ---------------------------------------------------------------------------
class cGameBundleGroundContainer {
public:
    void*    mpVtbl;       // +0x00
    void*    mpVtbl2;      // +0x04
    uint8_t  pad08[0x2c - 0x08];
    void*    mpOwner2c;    // +0x2c  (owned object with vtbl[1] dtor)
    uint8_t  pad30[0x34 - 0x30];
    uint8_t  mSpatial[0x58 - 0x34]; // embedded object at +0x34
    float    mField58;     // +0x58
    void*    mpField5c;    // +0x5c

    cGameBundleGroundContainer* Ctor();                    // 0xc36510
    void*  CastTo(uint32_t key);                           // 0xc36560
    void   Init(uint32_t obj);                             // 0xc365a0
    void   Dtor2c();                                       // 0xc36690
    bool   Write(void* stream);                            // 0xc366c0
    bool   Read(void* stream);                             // 0xc36740
};

// a tiny view used by 0xc36870: object with an owned +0x64 thing
class cGameObj64 {
public:
    uint8_t pad00[0x64];
    void*   mpField64;     // +0x64
};

bool     __cdecl FUN_00c36870(cGameObj64* self, void* b);   // 0xc36870
void     __cdecl FUN_00c360f0(void* self);                 // 0xc360f0
bool     __cdecl FUN_00c364e0(void* a, void* b);          // 0xc364e0
void*    __stdcall FUN_00c365e0(void* param1, void* param2); // 0xc365e0

// ---------------------------------------------------------------------------
// base sub-object views (thiscall base ctors/dtors and helpers)
// ---------------------------------------------------------------------------
struct BaseGameData {                                   // SP::cGameData at +0
    void  Ctor();                                       // 0xb18660
    void  Dtor();                                       // 0xb184c0
    void  Write(uint32_t s);                            // 0xb18590
    void  Read(uint32_t s);                             // 0xb18600
    uint32_t WriteAsText(uint32_t s);                   // 0xb18420
    void  GetFieldValues(uint32_t s);                   // 0xb18550
};
struct BaseSpatial {                                    // SP::cSpatialObject at +0x34
    void  Ctor();                                       // 0xc89630
    void  Dtor();                                       // 0xc8a420
    void  Write(uint32_t s);                            // 0xc88a90
    void  Read(uint32_t s);                             // 0xc88b00
    void  Exit();                                       // 0xc8b2e0
    void  SetFloat(float f);                            // 0xc884a0
};
struct BaseInteract {                                   // SP::cInteractionTarget at +0x108
    void  Ctor();                                       // 0xac03d0
    void  Dtor();                                       // 0xac0450
    void  Reset();                                      // 0xac0520
};
struct GroundBase {                                     // embedded at ground +0x34
    void  Ctor();                                       // 0xcee630
    void  Dtor();                                       // 0xcee7e0
    bool  WriteObj(uint32_t stream);                    // 0xcee3d0
    bool  ReadObj(uint32_t stream);                     // 0xcee440
    uint32_t SetObj(uint32_t obj);                      // 0xcee250
    uint32_t InitObj(uint32_t obj, uint32_t a, float b, float c, int d); // 0xcee2c0
    float* GetDir();                                    // slot 11 (+0x2c)
    float* GetPos();                                    // slot 12 (+0x30)
    void   SetDir(const float* v);                      // slot 14 (+0x38)
    float  GetScalar();                                 // slot 13 (+0x34)
};
