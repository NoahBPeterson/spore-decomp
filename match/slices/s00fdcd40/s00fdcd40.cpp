// Slice s00fdade0 (batch gold6) -- SP::cAppModeSpace space/entry transition helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
//   0x00fdade0 cAppModeSpace::FUN_00fdade0              (SETI/ambush + first-contact bookkeeping)
//   0x00fdb0c0 FUN_00fdb0c0                             (nearest eradicator target position)
//   0x00fdb230 FUN_00fdb230                             (linked-list find-by-key)
//   0x00fdb330 cAppModeSpace::FUN_00fdb330              (enter/leave the UFO)
//   0x00fdb710 cAppModeSpace::Activate                  (install the space cheat commands)
//   0x00fdb9a0 cAppModeSpace::FUN_00fdb9a0              (place the current UFO model)
//   0x00fdba50 cAppModeSpace::TransitionFromCivToSpace  (park the UFO leaving a city planet)
//   0x00fdbc20 cAppModeSpace::CompleteTransitionFromEntryToNewGame
//
// Members of SP::cAppModeSpace are named at their retail offsets.  External callees are declared
// with the retail calling convention: a plain free function where the original pushes its args, or
// a method of the helper class below where the original passes the object in ecx.  Every callee
// carries its retail address so tools/difftest/resolve.py can bind it.
#include "types.h"
#include <math.h>

struct Vector3 { float x, y, z; };
struct Quaternion { float x, y, z, w; };
struct Filter8 { uint32_t id; uint16_t a; uint16_t b; };
struct IVec3 { int x, y, z; };

void* operator new[](unsigned int n, const char* pName, int flags, unsigned debugFlags, const char* file, int line);  // 0x00f473a0
void __cdecl operator_delete__(void* p);                                                                                         // 0x00f47380

// ---------------------------------------------------------------------------------------------
// Vtable leaders.  B<n> carries n+1 virtual slots (offsets 0x00 .. 4*n); deriving from B<k-1> and
// adding the called method places it at offset 4*k, the retail slot.  Concrete (empty) bodies so
// the body objects below can be embedded as sub-objects.
// ---------------------------------------------------------------------------------------------
struct B00 { virtual void a00() {} };
struct B01 : B00 { virtual void a01() {} };
struct B02 : B01 { virtual void a02() {} };
struct B03 : B02 { virtual void a03() {} };
struct B04 : B03 { virtual void a04() {} };
struct B05 : B04 { virtual void a05() {} };
struct B06 : B05 { virtual void a06() {} };
struct B07 : B06 { virtual void a07() {} };
struct B08 : B07 { virtual void a08() {} };
struct B09 : B08 { virtual void a09() {} };
struct B10 : B09 { virtual void a10() {} };
struct B11 : B10 { virtual void a11() {} };
struct B12 : B11 { virtual void a12() {} };
struct B13 : B12 { virtual void a13() {} };
struct B14 : B13 { virtual void a14() {} };
struct B15 : B14 { virtual void a15() {} };
struct B16 : B15 { virtual void a16() {} };
struct B17 : B16 { virtual void a17() {} };
struct B18 : B17 { virtual void a18() {} };
struct B19 : B18 { virtual void a19() {} };
struct B20 : B19 { virtual void a20() {} };
struct B21 : B20 { virtual void a21() {} };
struct B22 : B21 { virtual void a22() {} };
struct B23 : B22 { virtual void a23() {} };
struct B24 : B23 { virtual void a24() {} };
struct B25 : B24 { virtual void a25() {} };
struct B26 : B25 { virtual void a26() {} };
struct B27 : B26 { virtual void a27() {} };
struct B28 : B27 { virtual void a28() {} };
struct B29 : B28 { virtual void a29() {} };
struct B30 : B29 { virtual void a30() {} };
struct B31 : B30 { virtual void a31() {} };
struct B32 : B31 { virtual void a32() {} };
struct B33 : B32 { virtual void a33() {} };
struct B34 : B33 { virtual void a34() {} };
struct B35 : B34 { virtual void a35() {} };
struct B36 : B35 { virtual void a36() {} };
struct B37 : B36 { virtual void a37() {} };
struct B38 : B37 { virtual void a38() {} };
struct B39 : B38 { virtual void a39() {} };
struct B40 : B39 { virtual void a40() {} };
struct B41 : B40 { virtual void a41() {} };
struct B42 : B41 { virtual void a42() {} };
struct B43 : B42 { virtual void a43() {} };
struct B44 : B43 { virtual void a44() {} };
struct B45 : B44 { virtual void a45() {} };
struct B46 : B45 { virtual void a46() {} };
struct B47 : B46 { virtual void a47() {} };
struct B48 : B47 { virtual void a48() {} };
struct B49 : B48 { virtual void a49() {} };
struct B50 : B49 { virtual void a50() {} };
struct B51 : B50 { virtual void a51() {} };
struct B52 : B51 { virtual void a52() {} };
struct B53 : B52 { virtual void a53() {} };
struct B54 : B53 { virtual void a54() {} };
struct B55 : B54 { virtual void a55() {} };
struct B56 : B55 { virtual void a56() {} };
struct B57 : B56 { virtual void a57() {} };
struct B58 : B57 { virtual void a58() {} };
struct B59 : B58 { virtual void a59() {} };
struct B60 : B59 { virtual void a60() {} };
struct B61 : B60 { virtual void a61() {} };
struct B62 : B61 { virtual void a62() {} };
struct B63 : B62 { virtual void a63() {} };
struct B64 : B63 { virtual void a64() {} };
struct B65 : B64 { virtual void a65() {} };
struct B66 : B65 { virtual void a66() {} };
struct B67 : B66 { virtual void a67() {} };
struct B68 : B67 { virtual void a68() {} };
struct B69 : B68 { virtual void a69() {} };
struct B70 : B69 { virtual void a70() {} };
struct B71 : B70 { virtual void a71() {} };
struct B72 : B71 { virtual void a72() {} };
struct B73 : B72 { virtual void a73() {} };
struct B74 : B73 { virtual void a74() {} };
struct B75 : B74 { virtual void a75() {} };
struct B76 : B75 { virtual void a76() {} };
struct B77 : B76 { virtual void a77() {} };
struct B78 : B77 { virtual void a78() {} };
struct B79 : B78 { virtual void a79() {} };
struct B80 : B79 { virtual void a80() {} };
struct B81 : B80 { virtual void a81() {} };
struct B82 : B81 { virtual void a82() {} };
struct B83 : B82 { virtual void a83() {} };
struct B84 : B83 { virtual void a84() {} };
struct B85 : B84 { virtual void a85() {} };
struct B86 : B85 { virtual void a86() {} };
struct B87 : B86 { virtual void a87() {} };
struct B88 : B87 { virtual void a88() {} };
struct B89 : B88 { virtual void a89() {} };
struct B90 : B89 { virtual void a90() {} };
struct B91 : B90 { virtual void a91() {} };
struct B92 : B91 { virtual void a92() {} };
struct B93 : B92 { virtual void a93() {} };
struct B94 : B93 { virtual void a94() {} };
struct B95 : B94 { virtual void a95() {} };

// ---- single-slot interfaces (the named method sits at its retail vtable offset) ----
struct V04   : B00 { virtual void Destroy() = 0; };                            // +0x04
struct V08   : B01 { virtual void Unlink() = 0; };                             // +0x08
struct V0c   : B02 { virtual void* Query(int ifaceId) = 0; };                  // +0x0c (1 int)
struct V0ci  : B02 { virtual void  Reset(int v) = 0; };                        // +0x0c (1 int)
struct V0cW  : B02 { virtual void* Make(void* a, void* b, int c) = 0; };       // +0x0c (3 args)
struct V10   : B03 { virtual bool  IsDone() = 0; };                            // +0x10
struct V18b  : B05 { virtual bool  Probe(int kind) = 0; };                     // +0x18 (int -> bool)
struct V18v  : B05 { virtual void  Install(void* a, void* b, int c) = 0; };     // +0x18 (3 args)
struct V18pb : B05 { virtual bool  Pick(void* out) = 0; };                     // +0x18 (ptr -> bool)
struct V18p  : B05 { virtual void  Put(void* in) = 0; };                       // +0x18 (ptr)
struct V1c   : B06 { virtual void* Current() = 0; };                           // +0x1c
struct V2cp  : B10 { virtual void* GetPosition() = 0; };                       // +0x2c (position)
struct V2c3  : B10 { virtual bool  SetPortal(void* a, int b, int c) = 0; };    // +0x2c (3 args)
struct V2c4  : B10 { virtual void* DoPlace(int, int, int, int) = 0; };         // +0x2c (4 args, returns this)
struct V30   : B11 { virtual void* GetOrientation() = 0; };                    // +0x30
struct V38   : B13 { virtual void* Get14() = 0; };                             // +0x38
struct V40f  : B15 { virtual void  SetPose(float scale) = 0; };                // +0x40 (float)
struct V40b  : B15 { virtual void  Place(void* a, int b, void* c) = 0; };      // +0x40 (3 args)
struct V4c   : B18 { virtual void  Assign2(void* a, void* b) = 0; };           // +0x4c
struct V50   : B19 { virtual void* GetModeManager() = 0; };                    // +0x50
struct V5c   : B22 { virtual void  SetSlot(void* a, int b) = 0; };             // +0x5c
struct V68   : B25 { virtual void  StopFX() = 0; };                            // +0x68
struct V98   : B37 { virtual void  SetFx(int a, int b) = 0; };                 // +0x98
struct V16c  : B90 { virtual void  Attach(void* a, int b) = 0; };              // +0x16c
struct V3c   : B14 { virtual void  Set3c(Vector3* v) = 0; };                   // +0x3c (Vector3*)
struct cToolObj { uint32_t pad0[80]; void* mpObj; };                            // +0x140 object handle
struct cEmbd34 { uint32_t pad0[13]; uint32_t sub34; };                          // embedded sub-object at +0x34
struct cBC30   { uint32_t pad0[9];  float    m24; };                            // +0x24 float
struct cTestSys { uint32_t pad0[28]; void*   m70; };                            // +0x70 list sentinel

// additional single-slot interfaces used by the transition helpers
struct V04r  : B00 { virtual void  Release() = 0; };                           // +0x04
struct V1c2  : B06 { virtual bool  Test1c(void* a, int b) = 0; };              // +0x1c (2 args)
struct V20s  : B07 { virtual void  Add(void* a, int b) = 0; };                 // +0x20 (2 args)
struct V24   : B08 { virtual bool  GetProp(int id, void** out) = 0; };         // +0x24 (id, out)
struct V2cR  : B10 { virtual bool  GetProp3(int a, int b, void** out) = 0; };  // +0x2c (3 args)
struct V38b  : B13 { virtual void* Get38() = 0; };                             // +0x38
struct V3cq  : B14 { virtual bool  Test3c(void* a) = 0; };                     // +0x3c (1 arg)
struct V40p  : B15 { virtual void  X40(void* a) = 0; };                        // +0x40 (1 arg)
struct V48   : B17 { virtual void  OnEvent() = 0; };                           // +0x48
struct V4c2  : B18 { virtual bool  Test4c(void* a, int b) = 0; };              // +0x4c (2 args)
struct V170  : B91 { virtual void  Release2(void* a, int b) = 0; };            // +0x170
struct V10c  : B03 { virtual void  X10(int a, void* b) = 0; };                 // +0x10 (2 args)

struct cPropVal { uint16_t pad0[9]; uint16_t mKind; };                         // +0x12 property tag
struct cRefObj  { void* vftable; uint32_t m04; uint32_t pad08[14]; int mRef40; };  // ref-counted wrapper
struct cCandidate { uint32_t pad0[79]; void* p13c; };                          // +0x13c picked handle
struct cHostHdr { uint32_t pad0[2]; };                                         // object embedding the mode at +0x08
struct cUnitSlot { uint32_t pad00[0x40 / 4]; void* p40; };                     // +0x40 resident entity
struct cHolder { uint32_t pad00[0xc4 / 4]; void* pC4; };                       // +0xc4 resident entity
struct cWorm { uint32_t pad00[0x8c / 4]; void* p8c; };                         // +0x8c worm pointer
struct cD0     { uint32_t pad0[52]; uint32_t mD0; };                           // host +0xd0 state
struct c154    { uint32_t pad0[8];  void*    p20; };                           // +0x20 sub-object
struct cSimObj { uint32_t pad0[10]; uint8_t  mObj28; };                        // vtable object at +0x28
struct cSimPtr { uint32_t pad0[10]; void*    p28; };                           // pointer at +0x28
struct cM44    { uint32_t pad0[17]; uint32_t m44; };                           // +0x44 flag
struct c24     { uint32_t pad0[9];  void* p24; uint32_t pad28[1]; void* p2c; };  // effect roots
struct c28     { uint32_t pad0[33]; void* p84; };                              // +0x84 sub-object
struct cDet0   { uint32_t pad0[11]; uint32_t m2c; };                           // +0x2c mode state

struct Vec3Pad { uint32_t tag; float x, y, z; };                               // 16-byte padded vector
struct IdKey   { uint32_t a, b, c; };                                          // 12-byte mode key
struct cContainer {                                                            // noun-manager entity container
    uint32_t  pad0[4];                                                         // +0x00
    uint32_t* mBegin;                                                          // +0x10
    uint32_t* mEnd;                                                            // +0x14
    uint32_t  pad18;                                                           // +0x18
    uint32_t* mExtra;                                                          // +0x1c
};
struct cPtrVector {                                                            // 3-pointer vector (begin/end/cap)
    uint32_t* begin;                                                           // +0x00
    uint32_t* end;                                                             // +0x04
    uint32_t* cap;                                                             // +0x08
};

struct V50x   : B19 { virtual void  X50(int a) = 0; };                         // +0x50 (1 arg)
struct V18v4  : B05 { virtual void  Install4(int a, void* b, void* c, int d) = 0; };  // +0x18 (4 args)
struct V08a   : B01 { virtual void  Unlink2(void* a) = 0; };                   // +0x08 (1 arg)

union cFloPtr { float f; void* p; };

// ---- embedded vtable bodies (the object living at +0x34 of several game objects) ----
struct cBodyF : public B15 { virtual void SetPose(float) {} };                 // +0x40
struct cBody4 : public B10 { virtual void* DoPlace(int, int, int, int) { return this; } };  // +0x2c
struct cBodyQ : public B11 { virtual void* GetOrientation() { return 0; } };   // +0x30

// ---------------------------------------------------------------------------------------------
// globals
// ---------------------------------------------------------------------------------------------
extern Vector3 DAT_016d9944;                 // 0x016d9944 -- {0,0,0}; +4/+8 continue the vector
extern float   DAT_01493e38;                 // 0x01493e38
extern float   DAT_015b41fc;                 // 0x015b41fc
extern float   DAT_015b4028;                 // 0x015b4028
extern float   DAT_015b402c;                 // 0x015b402c
extern float   DAT_015b4030;                 // 0x015b4030
extern float   DAT_0146138c;                 // 0x0146138c
extern float   DAT_01486110;                 // 0x01486110  (5.0f)
extern float   DAT_0145c464;                 // 0x0145c464  (0.4166666f)
extern void*   DAT_015b734c;                 // 0x015b734c  (rename string handle)
extern void*   DAT_015fd928;                 // 0x015fd928  (cTestSystem singleton)
extern void*   DAT_015fd918;                 // 0x015fd918  (app property list)
extern void*   DAT_016d9938;                 // 0x016d9938
extern char    DAT_01493f48[];               // 0x01493f48  "SPG_SetiAmbush"
extern char    DAT_01493f2c[];               // 0x01493f2c  "SPG_FirstContact_Intercept"
extern char    DAT_0146f110[];               // 0x0146f110  "SPG_FirstAlliancePossible"
extern char    DAT_013f09b4[];               // 0x013f09b4  "Simulator"

// ---------------------------------------------------------------------------------------------
// plain free functions (the original pushes every argument on the stack)
// ---------------------------------------------------------------------------------------------
void* FUN_00feb9f0();                                          // 0x00feb9f0  GetMissionManager
void* FUN_00ffbe50();                                          // 0x00ffbe50  GetUFOSimulator
void* FUN_01002bd0();                                          // 0x01002bd0  GetSimulator (no arg)
void* FUN_01002bd0s(void* who);                                // 0x01002bd0  GetSimulator (task arg)
void* FUN_01021240();                                          // 0x01021240  active-noun manager
void* FUN_01021260();                                          // 0x01021260  GetActivePlanet
void* FUN_01021300();                                          // 0x01021300  GetPlayerEmpire
int   FUN_01021090();                                          // 0x01021090  GetPlayerEmpireID
void* __stdcall FUN_00b3d300(int id);                          // 0x00b3d300  NounManager(id)
void* __stdcall FUN_00b3d2a0(void* avatar);                      // 0x00b3d2a0
void* FUN_00b3d2c0(void* a, void* b, ...);                     // 0x00b3d2c0  (2 or 3 args)
void* FUN_00b3d390(void* p);                                   // 0x00b3d390
void* FUN_00b3d470();                                          // 0x00b3d470
void* FUN_00b3d520();                                          // 0x00b3d520  GonzagoModelWorld
void* FUN_00b3d250();                                          // 0x00b3d250
void* FUN_00b3d380();                                          // 0x00b3d380  game noun manager
void* FUN_00b3d240();                                          // 0x00b3d240
void* FUN_00b3d3c0();                                          // 0x00b3d3c0
void* __stdcall FUN_00b3d3e0(int, int, int, int, int, int);    // 0x00b3d3e0  (6 dwords)
void* __stdcall FUN_00b3d3e0f(float, float);                   // 0x00b3d3e0  (2 floats)
void* __stdcall FUN_00b3d4d0(int id, void* buf, int n);        // 0x00b3d4d0
void* FUN_0067cab0();                                          // 0x0067cab0  cheat manager (edit)
void* FUN_0067de20();                                          // 0x0067de20  cheat manager (install)
void* FUN_0067dd10();                                          // 0x0067dd10  App()
void* FUN_0067ddd0();                                          // 0x0067ddd0  EffectsManager()
void* FUN_0067dd50();                                          // 0x0067dd50  UI manager
void* FUN_0102ac50(int kind, void* avatar);                    // 0x0102ac50  CreateUFOForSolarOrGalaxy
void* FUN_010407c0f(float v);                                  // 0x010407c0  (float form)
int   FUN_01041c50(char* name, int a, int b);                  // 0x01041c50
void* FUN_00401010();                                          // 0x00401010
void* FUN_00449c20(void* a, void* b);                          // 0x00449c20
void* FUN_006985b0(void* a, void* b);                          // 0x006985b0
void* FUN_0069b440(void* a, void* b, void* c);                 // 0x0069b440
void* FUN_00bc30b0();                                          // 0x00bc30b0
void* FUN_00b3d350(void* a, void* b);                          // 0x00b3d350

// ---- free functions used by the transition helpers ----
void* FUN_00b3d300();                                          // 0x00b3d300  (default noun manager)
void* FUN_00b3d360();                                          // 0x00b3d360
void* FUN_00b3d3d0();                                          // 0x00b3d3d0
void* FUN_00b3d230(int id);                                    // 0x00b3d230
void* FUN_0067dcc0();                                          // 0x0067dcc0  localization manager
void* FUN_0067de30();                                          // 0x0067de30  cheat manager (query)
void* FUN_00675250(int a, int b);                              // 0x00675250
int   FUN_006a17e0(int a, int b);                              // 0x006a17e0
float* FUN_0041ea70();                                         // 0x0041ea70  property float accessor
uint8_t* FUN_0041e920();                                       // 0x0041e920  property bool accessor
void* FUN_01021230();                                          // 0x01021230  GetNounManager
void  FUN_01022510(void* vec);                                 // 0x01022510  sort(vector)
void  FUN_00bdaa40(void** cursorRef, void* first, void* last, void* init, void* extra);  // 0x00bdaa40
void* FUN_010219b0(void* a, void* b);                          // 0x010219b0
void* __stdcall FUN_01046fc0(int a);                           // 0x01046fc0
void* FUN_01048e00();                                          // 0x01048e00
void* FUN_0100a7c0();                                          // 0x0100a7c0
void* FUN_00e98ac0(void* a);                                   // 0x00e98ac0
bool  FUN_00c8bb00(void* a);                                   // 0x00c8bb00
void* FUN_00ac86d0(int a);                                     // 0x00ac86d0
void* FUN_0105c3d0(void* a, void* b, float f);                 // 0x0105c3d0
void* FUN_00b3d280();                                          // 0x00b3d280
void* __stdcall FUN_01002bd0ii(int a, int b);                  // 0x01002bd0  (2 args)
void** FUN_00fdb230(void** out, uint32_t* begin, uint32_t* end, const uint32_t* key);  // 0x00fdb230
void  FUN_00fdb0c0(void* out);                                 // 0x00fdb0c0
void  FUN_00571db0(void* a, void* b, void* c, void* d, void* e);  // 0x00571db0
void  FUN_0057cc10(void* a, void* b, void* c, void* d);        // 0x0057cc10
void* FUN_00fdd200();                                          // 0x00fdd200
void* FUN_00b3d4d0();                                          // 0x00b3d4d0  (default context)
void* FUN_01014a80(int a, int b);                              // 0x01014a80  (ecx = global)

// ---- data ----
extern void* DAT_016c7aa4;                 // 0x016c7aa4
extern void* DAT_016dc798;                 // 0x016dc798
extern uint32_t DAT_016d9950;                 // 0x016d9950  (mode key dwords)
extern uint32_t DAT_016d9954;                 // 0x016d9954
extern uint32_t DAT_016d9958;                 // 0x016d9958
extern float DAT_015b4200;                 // 0x015b4200
extern float DAT_015b4034;                 // 0x015b4034
extern float DAT_015b4038;                 // 0x015b4038
extern float DAT_015b403c;                 // 0x015b403c
extern float DAT_015b4040;                 // 0x015b4040
extern float DAT_01428874;                 // 0x01428874
extern float DAT_0142eae0;                 // 0x0142eae0

// ---------------------------------------------------------------------------------------------
// cSelf -- helper class whose methods stand in for the retail callees that receive their object in
// ecx.  Static casts of any pointer to cSelf* give the correct __thiscall codegen (MSVC rejects
// __thiscall on free functions).
// ---------------------------------------------------------------------------------------------
struct cSelf
{
    // ecx = this only
    int       FUN_00bb9ae0();        // 0x00bb9ae0
    bool      FUN_00bb9fb0();        // 0x00bb9fb0
    void      FUN_00bb9b30();        // 0x00bb9b30
    void*     FUN_00b1fdb0();        // 0x00b1fdb0  GetAvatar
    void*     FUN_00a1ad60();        // 0x00a1ad60  GetPlayerInventory
    void*     FUN_00fedd50();        // 0x00fedd50  GetMissionList
    void*     FUN_00970b30();        // 0x00970b30  GetTargetPlanet
    void*     FUN_010097f0();        // 0x010097f0  StartSetiAmbush
    void*     FUN_01001b60();        // 0x01001b60
    void*     FUN_00f67d90();        // 0x00f67d90
    bool      FUN_00c772c0();        // 0x00c772c0
    void*     FUN_00c77bf0();        // 0x00c77bf0
    void*     FUN_00c75740();        // 0x00c75740
    int       FUN_00ba9370();        // 0x00ba9370
    void      FUN_00c37e60();        // 0x00c37e60  PopToDestination
    void*     FUN_00ae09b0();        // 0x00ae09b0
    bool      FUN_00d01fb0();        // 0x00d01fb0
    float     FUN_00d00a10();        // 0x00d00a10
    float     FUN_01040820();        // 0x01040820
    void*     FUN_00ff3f00();        // 0x00ff3f00
    bool      FUN_0104bd50();        // 0x0104bd50
    void*     FUN_0104fa90();        // 0x0104fa90
    void*     FUN_0104f930();        // 0x0104f930
    long long FUN_0093a5e0();        // 0x0093a5e0  GetElapsedTime
    void      FUN_00571e80();        // 0x00571e80  Restart
    void      FUN_00bc30f0();        // 0x00bc30f0  Start
    void      FUN_00ffc030();        // 0x00ffc030
    bool      FUN_00801400();        // 0x00801400
    void      FUN_0083c800();        // 0x0083c800
    void*     FUN_00dd5a10();        // 0x00dd5a10
    void*     FUN_00b72870();        // 0x00b72870
    void*     FUN_00c30f90();        // 0x00c30f90
    void*     FUN_00b25c30();        // 0x00b25c30
    void*     FUN_00bd9b40();        // 0x00bd9b40
    void*     FUN_00b815a0();        // 0x00b815a0
    void      FUN_00434040();        // 0x00434040
    void*     FUN_01065af0();        // 0x01065af0
    void      FUN_00ad7ad0();        // 0x00ad7ad0
    void      FUN_00dd8640();        // 0x00dd8640
    void      FUN_01009a40();        // 0x01009a40

    // ecx = this plus pushed arguments
    void  FUN_00fee0a0(int v);                       // 0x00fee0a0  SetFilter
    void  FUN_007c3d30(int, void* loc, int, int);    // 0x007c3d30  GetCameraLocationInfo
    void  FUN_00c3bfe0(const Vector3* p);            // 0x00c3bfe0  SetDestination
    void  FUN_00ad7a30(void* arg);                   // 0x00ad7a30
    void  FUN_00ffc350(void* p);                     // 0x00ffc350
    void  FUN_008013d0(int v);                       // 0x008013d0
    void  FUN_00801950(void* p);                     // 0x00801950
    void  FUN_00801980(int v);                       // 0x00801980
    void  FUN_00478db0(void* model);                 // 0x00478db0
    void  FUN_00c37130(int v);                       // 0x00c37130
    void  FUN_00bd7f70(void* a, void* b);            // 0x00bd7f70
    void  FUN_00ad79d0(void* a, void* b);            // 0x00ad79d0
    void  FUN_00c3aa40(void* a, void* b);            // 0x00c3aa40
    void  FUN_00c3daa0(float f);                     // 0x00c3daa0
    void  FUN_00bc2f00(float f);                     // 0x00bc2f00
    void  FUN_00ff5ee0(void* a, void* b);            // 0x00ff5ee0
    void  FUN_00b32250(int id);                      // 0x00b32250
    bool  FUN_006a25a0(int id);                      // 0x006a25a0
    void  FUN_0102f660(Vector3* out);                // 0x0102f660
    void  FUN_00fda2e0(void* v);                     // 0x00fda2e0
    void  FUN_01017270(void* v);                     // 0x01017270
    void  FUN_00c4cb90(void* a, void* b);            // 0x00c4cb90
    void  FUN_00c50300(void* a, void* b);            // 0x00c50300

    // ---- additional callees for the transition helpers (ecx = this only) ----
    void*     FUN_00ba6f20();                        // 0x00ba6f20
    void*     FUN_00c7a160(void* a);                 // 0x00c7a160
    void      FUN_00c7ba90(void* a);                 // 0x00c7ba90
    void      FUN_00c7ad40(void* a);                 // 0x00c7ad40
    void      FUN_00c79fa0(void* a);                 // 0x00c79fa0
    void      FUN_00b7dec0();                        // 0x00b7dec0
    void*     FUN_00c8b770();                        // 0x00c8b770
    int       FUN_00c70880();                        // 0x00c70880
    int       FUN_00c70e00();                        // 0x00c70e00
    int       FUN_00c70fb0();                        // 0x00c70fb0
    bool      FUN_00b8d970();                        // 0x00b8d970
    bool      FUN_00c44c80();                        // 0x00c44c80
    int       FUN_01030e10();                        // 0x01030e10
    int       FUN_00970b30i();                       // 0x00970b30  (integer form)
    void      FUN_00bb5b70(void* a);                 // 0x00bb5b70
    bool      FUN_00bb9bd0();                        // 0x00bb9bd0
    bool      FUN_00d09660();                        // 0x00d09660
    void      FUN_00d100b0(int a, int b);            // 0x00d100b0
    void      FUN_00b11870(int a);                   // 0x00b11870
    void      FUN_00b0f720(float, float, float, float, float);  // 0x00b0f720
    void      FUN_00b12dd0(void* a, void* b, int c);  // 0x00b12dd0
    void      FUN_00b10340(float, float, float);     // 0x00b10340
    void      FUN_00b10540(float, float, float);     // 0x00b10540
    void      FUN_00c31c30(int a);                   // 0x00c31c30
    void*     FUN_00c326b0();                        // 0x00c326b0
    void      FUN_00c3c190(void* a);                 // 0x00c3c190
    float     FUN_00c3ae70();                        // 0x00c3ae70
    void      FUN_00c381e0(void* a);                 // 0x00c381e0
    void      FUN_00c37e6f();                        // 0x00c37e60
    void*     FUN_00b815a0i();                       // 0x00b815a0  (ptr form)
    void*     FUN_0101727f();                        // 0x01017270
    void      FUN_004e0880(int a);                   // 0x004e0880
    int       FUN_00801920();                        // 0x00801920
    void      FUN_00bbe910(void* a, void* b);        // 0x00bbe910
    void*     FUN_00bb1340();                        // 0x00bb1340
    void*     FUN_00bfc5f0();                        // 0x00bfc5f0
    void      FUN_00fe5430();                        // 0x00fe5430
    void      FUN_00b5cde0();                        // 0x00b5cde0
    void      FUN_00b5f950(void* a);                 // 0x00b5f950
    void      FUN_01017270x(void* a);                // 0x01017270
    void*     FUN_0104bd50i();                       // 0x0104bd50
    void      FUN_00b93c60(int count, void* extra);  // 0x00b93c60  (local vector build)
    void      FUN_00ad92d0();                        // 0x00ad92d0  (local vector dtor)
    void      FUN_01048e00x();                       // 0x01048e00
    int       FUN_0103ac40(void* a);                 // 0x0103ac40
    int       FUN_0103fba0(void* a, void* b);        // 0x0103fba0
    void      FUN_00dd8640i();                       // 0x00dd8640

    // ---- callees receiving their object in ecx, reached through a stored pointer ----
    void*     FUN_01003070();                        // 0x01003070
    void      FUN_01003160();                        // 0x01003160
    void      FUN_01003230();                        // 0x01003230
    void      FUN_01003620();                        // 0x01003620
    void      FUN_01003a50();                        // 0x01003a50
    void      FUN_010077e0();                        // 0x010077e0
    void      FUN_01009470(int a, void* b, int c);   // 0x01009470
    void      FUN_010039c0(void* a);                 // 0x010039c0
    void      FUN_01036620(int a);                   // 0x01036620
    void      FUN_00676e90();                        // 0x00676e90
    void      FUN_01014a80i(int a, int b);          // 0x01014a80
    void      FUN_006a17e0m(int a, int b);           // 0x006a17e0  (ecx = app property list)
    void      FUN_0101be60();                        // 0x0101be60
    void      FUN_0101bd10();                        // 0x0101bd10
    bool      FUN_0100a7c0m();                       // 0x0100a7c0
    void      FUN_00fdc980();                        // 0x00fdc980  (host object)
    void      FUN_00fdc9e0();                        // 0x00fdc9e0  (host object)
    void      FUN_00fda9f0();                        // 0x00fda9f0  (host object)
    void      FUN_00fdc150();                        // 0x00fdc150  (host object)
};

// ---------------------------------------------------------------------------------------------
// small layout helpers
// ---------------------------------------------------------------------------------------------
class cSPTimer                                     // 0x18 bytes
{
public:
    uint32_t lo;                                   // +0x00
    uint32_t hi;                                   // +0x04
    uint32_t lo2;                                  // +0x08
    uint32_t hi2;                                  // +0x0c
    uint32_t pad[2];                               // +0x10
};

class cSPSpaceGameState                           // object at cAppModeSpace +0x15c
{
public:
    uint32_t pad00[5];                             // +0x00
    void*    mpEffect;                             // +0x14
    uint32_t pad18[(0x50 - 0x18) / 4];
    uint32_t mFlags;                               // +0x50
};

struct cSpaceSim                                 // FUN_00ffbe50() result
{
    uint8_t pad00[0x55];
    uint8_t mFlag55;                               // +0x55
};

class cGPtr9938                                   // object behind DAT_016d9938
{
public:
    uint32_t pad00[0x160 / 4];
    void*    m160;                                 // +0x160
};

class cCheatRoot                                  // object behind FUN_00b3d470()
{
public:
    uint32_t pad00[0x94 / 4];
    void*    p94;                                  // +0x94
    uint32_t pad98[(0xa4 - 0x98) / 4];
    void*    pA4;                                  // +0xa4
};

struct cCommand                                   // operator new[]'d command objects
{
    void*    vftable;                              // +0x00
    uint32_t pad04[3];
    uint8_t  flag10;                               // +0x10
};

struct cListNode
{
    cListNode* pNext;                              // +0x00
    uint32_t   pad04;
    uint8_t    flag08;                             // +0x08
};

struct cVector
{
    void** begin;                                  // +0x00
    void** end;                                    // +0x04
};

class cObj188
{
public:
    uint8_t pad00[0x49];
    uint8_t flag49;                                // +0x49
};

class cPlayerInventory
{
public:
    uint32_t pad00[0x34 / 4];
    cBody4   mBody;                                // +0x34
    uint32_t pad38[(0x508 - 0x38) / 4];
    uint32_t mTool;                                // +0x508
    uint32_t pad50c[(0x718 - 0x50c) / 4];
    uint32_t mDiseaseTargets;                      // +0x718
};

struct cHall
{
    uint32_t pad00[0x34 / 4];
    cBodyQ   mBody;                                // +0x34
};

class cUfo                                         // object returned by FUN_0102ac50
{
public:
    uint32_t pad00[0x34 / 4];
    cBodyF   mBody;                                // +0x34
    uint32_t pad38[(0x694 - 0x38) / 4];
    float    mPose694;                             // +0x694
    float    mPose698;                             // +0x698
    float    mPose69c;                             // +0x69c
    uint32_t pad6a0[(0x6b0 - 0x6a0) / 4];
    uint32_t mB6b0;                                // +0x6b0
    uint32_t pad6b4[(0x7b0 - 0x6b4) / 4];
    uint32_t mB7b0;                                // +0x7b0
};

struct cVesselPtr                                  // cAppModeSpace +0x140
{
    void** mpObj;
};

struct cNounMgr
{
    uint32_t pad00[0x12];
    uint8_t  mFlags48;                             // +0x48
};

// ---------------------------------------------------------------------------------------------
// SP::cAppModeSpace
// ---------------------------------------------------------------------------------------------
namespace SP
{

class cAppModeSpace
{
public:
    void FUN_00fdade0();                                  // 0x00fdade0
    bool FUN_00fdb330(int a, float f1, float f2);         // 0x00fdb330
    bool Activate();                                      // 0x00fdb710
    void FUN_00fdb9a0();                                  // 0x00fdb9a0
    void TransitionFromCivToSpace(int a, int b);          // 0x00fdba50
    void CompleteTransitionFromEntryToNewGame();          // 0x00fdbc20
    bool Init(void* arg);                                 // 0x00fdcd40
    void PreGameModeTransition(int a1, void* a2);         // 0x00fdcee0
    void FUN_00fdd320(int a1, void* a2);                  // 0x00fdd320
    void TransitionFromPlanetToSolar(void* a1, int a2);   // 0x00fdd390
    void TransitionThroughWormhole();                     // 0x00fdd4f0
    void TransitionFromGalaxyToSolar();                   // 0x00fdd5a0

    uint8_t   pad000[4];                                  // +0x000
    uint8_t   mSub04[0x80];                               // +0x004 embedded event-target sub-object
    void*     mp84;                                       // +0x084
    void*     mp88;                                       // +0x088
    void*     mp8c;                                       // +0x08c
    void*     mp90;                                       // +0x090
    void*     mp94;                                       // +0x094
    uint8_t   pad98[0x10];
    cSPTimer  mTimerA8;                                   // +0x0a8  (entry timer)
    uint8_t   pad0c0[0x50];
    cSPTimer  mSpaceTimer;                                // +0x110 (leave-space timer)
    float     mViewX;                                     // +0x128
    float     mViewY;                                     // +0x12c
    uint8_t   pad130[0x4];
    void*     mpVessel134;                                // +0x134
    union cFloPtr m138;                                   // +0x138
    union cFloPtr m13c;                                   // +0x13c
    cVesselPtr mVessel140;                                // +0x140
    uint8_t   mObj144;                                    // +0x144 (embedded object)
    uint8_t   pad145[0xf];
    void*     mpSpace154;                                 // +0x154
    uint8_t   pad158[0x4];
    cSPSpaceGameState* mpSpaceState;                      // +0x15c
    uint8_t   pad160[0x9];
    bool      mFlag169;                                   // +0x169
    bool      mFlag16a;                                   // +0x16a
    uint8_t   pad16b[0x5];
    void*     mpList170;                                  // +0x170 (list sentinel)
    uint8_t   pad174[0x8];
    void*     mpList17c;                                  // +0x17c (list sentinel)
    void*     mpList180;                                  // +0x180
    uint8_t   pad184[0x4];
    cObj188*  mpObj188;                                   // +0x188
    uint8_t   pad18c[0x2];
    uint8_t   mFlag18e;                                   // +0x18e
    bool      mFlag18f;                                   // +0x18f
    bool      mFlag190;                                   // +0x190
    bool      mFlag191;                                   // +0x191
    bool      mFlag192;                                   // +0x192
};

} // namespace SP

using SP::cAppModeSpace;

// ---------------------------------------------------------------------------------------------
// implementations
// ---------------------------------------------------------------------------------------------

// @ 0x00fdcd40
bool cAppModeSpace::Init(void* arg)
{
    void* loc = FUN_0067dcc0();
    if (loc != 0) {
        ((V20s*)loc)->Add(this ? (void*)mSub04 : 0, 0x1a0219e);
        ((V20s*)loc)->Add(this ? (void*)mSub04 : 0, 0x3795725);
    }

    void* overlay = ((V50*)arg)->GetModeManager();
    ((V20s*)overlay)->Add((void*)0x14a5b6e, 0x101a9a0);
    overlay = ((V50*)arg)->GetModeManager();
    ((V20s*)overlay)->Add((void*)0x1103194, 0x101ae70);

    void* cmd = operator new[](0x10, DAT_013f09b4, 0, 0, 0, 0);
    if (cmd != 0) {
        ((cSelf*)cmd)->FUN_0083c800();
        *(void**)cmd = (void*)0x1493e54;
    }

    FUN_0067de20();
    void* props = FUN_0067de30();

    void** pvessel = &mpVessel134;
    void* old = *pvessel;
    if (old != 0) {
        *pvessel = 0;
        ((V04*)old)->Destroy();
    }
    ((V2cR*)props)->GetProp3(0x272ddeda, 0x2ae0c7e, (void**)pvessel);

    int kind = 0xd;
    if (*pvessel != 0) {
        void* val;
        if (((V24*)*pvessel)->GetProp(0x2e5710a, &val))
            if (((cPropVal*)val)->mKind == kind)
                m138.f = *FUN_0041ea70();
    }
    if (*pvessel != 0) {
        void* val;
        if (((V24*)*pvessel)->GetProp(0x2e57110, &val))
            if (((cPropVal*)val)->mKind == kind)
                m13c.f = *FUN_0041ea70();
    }

    if (DAT_015fd918 != 0) {
        void* val;
        if (((V24*)DAT_015fd918)->GetProp(0x64a44a8, &val))
            if (((cPropVal*)val)->mKind == 1)
                mFlag18e = *FUN_0041e920();
    }

    ((cSelf*)&mObj144)->FUN_004e0880(9);
    return true;
}

// @ 0x00fdcee0
void cAppModeSpace::PreGameModeTransition(int a1, void* a2)
{
    int msg = (int)(intptr_t)a2;

    if ((int)(intptr_t)((V1c*)this)->Current() == msg)
        return;
    ((V40p*)this)->X40(a2);

    if (a1 != 0x1654c05) {
        if (a1 == 0x1654c10) {
            void* host = DAT_016c7aa4;
            if (host != 0 && ((cD0*)host)->mD0 == 2 && msg == 0x2ccd1d2) {
                ((cSelf*)mpSpace154)->FUN_01003230();
                ((cSelf*)((cHostHdr*)this - 1))->FUN_00fdc980();
            }
        }
        ((V48*)this)->OnEvent();
        return;
    }

    void* fx = FUN_0067ddd0();
    ((V98*)fx)->SetFx(0xc, 0);

    void* o = m138.p;
    if (o != 0) {
        m138.p = 0;
        int rc = ((cRefObj*)o)->mRef40;
        if (rc > 1)
            ((cRefObj*)o)->mRef40 = rc - 1;
        else
            ((V170*)o)->Release2(o, (int)((((cRefObj*)o)->m04 >> 31) & 1));
    }

    ((cSelf*)DAT_015fd918)->FUN_006a17e0m(0x28, 0);

    switch (msg) {
    case 0x1654c06: {
        ((cSelf*)mpSpace154)->FUN_01003070();
        void* e = FUN_00b3d280();
        if (e != 0) {
            ((cSelf*)e)->FUN_00b11870(0x5c1c6351);
            float f = DAT_01428874;
            ((cSelf*)e)->FUN_00b0f720(f, f, f, f, f);
            Vec3Pad v;
            v.tag = 0; v.x = 0.0f; v.y = 0.0f; v.z = 0.0f;
            ((cSelf*)e)->FUN_00b12dd0(&v, &DAT_015b4040, 1);
            ((cSelf*)e)->FUN_00b10340(0.0f, 0.0f, DAT_0142eae0);
            ((cSelf*)e)->FUN_00b10540(0.0f, 0.0f, DAT_0142eae0);
        }
        break;
    }
    case 0xdbdba1: {
        ((cSelf*)mpSpace154)->FUN_01003070();
        void* edi = ((c154*)mpSpace154)->p20;
        if (edi != 0 && ((cSelf*)edi)->FUN_00d09660()) {
            void* g = FUN_01002bd0();
            if (((cSimPtr*)g)->p28 != 0) {
                void* r = ((cUnitSlot*)edi)->p40;
                if (r != 0) {
                    void* t = FUN_00ac86d0((int)(intptr_t)r);
                    if (t != 0) {
                        void* h = ((cSelf*)t)->FUN_00bd9b40();
                        void* g2 = FUN_01002bd0();
                        ((cSelf*)&((cSimObj*)g2)->mObj28)->FUN_00b5f950(h);
                    }
                }
            }
            ((cSelf*)edi)->FUN_00d100b0(1, 1);
        }
        break;
    }
    case -1:
        ((cSelf*)((cHostHdr*)this - 1))->FUN_00fdc9e0();
        break;
    case 0x1654c08:
        ((cSelf*)((cHostHdr*)this - 1))->FUN_00fda9f0();
        ((cSelf*)((cHostHdr*)this - 1))->FUN_00fdc150();
        break;
    case 0x1654c10: {
        ((cSelf*)mpSpace154)->FUN_01003160();
        if (((cHolder*)FUN_00b3d470())->pC4 != 0) {
            void* alive = ((cHolder*)FUN_00b3d470())->pC4;
            ((V0ci*)alive)->Reset(1);
            void* root = FUN_00b3d470();
            void* obj = ((cHolder*)root)->pC4;
            if (obj != 0) {
                ((cHolder*)root)->pC4 = 0;
                ((V04*)obj)->Destroy();
            }
        }
        break;
    }
    default:
        ((cSelf*)((cHostHdr*)this - 1))->FUN_00fdc980();
        break;
    }

    if (mp84 != 0) {
        void* a = mp84;
        void* b = mp88;
        void* c = mp8c;
        void* d = mp90;
        void* e2 = mp94;
        mp84 = 0;
        FUN_00571db0(a, b, c, d, e2);
    }

    if (msg == -1 || msg == 0x2ccd1d2) {
        void* m = FUN_00b3d230(0xebb801);
        ((cSelf*)m)->FUN_00b5cde0();
    }
    ((cSelf*)FUN_00b3d360())->FUN_00b7dec0();
    ((V48*)this)->OnEvent();
}

// @ 0x00fdd200
void* FUN_00fdd200()
{
    void* mgr = FUN_01021230();
    if (mgr == 0)
        return 0;

    cContainer* cont = (cContainer*)((cSelf*)mgr)->FUN_00c8b770();

    cPtrVector local;
    ((cSelf*)&local)->FUN_00b93c60((int)(cont->mEnd - cont->mBegin), (void*)&cont->mExtra);

    void* cursor;   // pre-call value is dead; retail passes the untouched slot as arg5
    FUN_00bdaa40((void**)&cursor, cont->mBegin, cont->mEnd, local.begin, cursor);
    local.end = (uint32_t*)cursor;

    if (local.begin != local.end)
        FUN_01022510(&local);

    void* best = 0;
    uint32_t* it = local.begin;
    uint32_t* endp = local.end;
    while (it != endp) {
        void* e = (void*)*it;
        if (((cSelf*)e)->FUN_00c70880() != 0) {
            if (!((cSelf*)((cCandidate*)e)->p13c)->FUN_00b8d970()) {
                if (((cSelf*)e)->FUN_00c70e00() == 5 ||
                    ((cSelf*)e)->FUN_00c70e00() == 4 ||
                    ((cSelf*)e)->FUN_00c70e00() == 2) {
                    best = e;
                    break;
                }
                if (best == 0 || ((cSelf*)e)->FUN_00c70fb0() > ((cSelf*)best)->FUN_00c70fb0())
                    best = e;
            }
        }
        ++it;
    }

    if (best == 0) {
        ((cSelf*)&local)->FUN_00ad92d0();
        return 0;
    }
    void* r = ((cCandidate*)best)->p13c;
    ((cSelf*)&local)->FUN_00ad92d0();
    return r;
}

// @ 0x00fdd320
void cAppModeSpace::FUN_00fdd320(int a1, void* a2)
{
    void* obj = FUN_00401010();
    if (((V1c2*)obj)->Test1c(a2, 0))
        return;

    void** r = FUN_00fdb230((void**)&a2, (uint32_t*)mpList170, (uint32_t*)&mpList170, (const uint32_t*)a2);
    if (*(void**)r != (void*)&mpList170)
        return;

    ((cSelf*)&mpList170)->FUN_00bbe910(&mpList170, a2);
    mFlag16a = false;

    void* obj2 = FUN_00401010();
    ((V4c2*)obj2)->Test4c(a2, a1);
}

// @ 0x00fdd390
void cAppModeSpace::TransitionFromPlanetToSolar(void* a1, int a2)
{
    ((cSelf*)FUN_00b3d360())->FUN_00b7dec0();
    void* nm = ((cSelf*)FUN_00b3d300())->FUN_00f67d90();

    if (FUN_00c8bb00(FUN_01021240()))
        ((cSelf*)nm)->FUN_00c7ba90(FUN_01021240());
    if (FUN_00c8bb00(a1))
        ((cSelf*)nm)->FUN_00c7ad40(a1);

    ((cM44*)FUN_01021230())->m44 = 1;

    ((cSelf*)mpSpaceState)->FUN_01009470(0, (void*)(intptr_t)a2, 0);
    ((cSelf*)mpSpaceState)->FUN_010039c0(FUN_01021230());
    FUN_010219b0(a1, (void*)0);
    ((cSelf*)FUN_01046fc0((int)(intptr_t)a1))->FUN_01048e00x();

    void* r = FUN_00fdd200();
    if (r != 0)
        FUN_010219b0(FUN_01021240(), r);

    void* planet = FUN_01021260();
    ((cSelf*)mpSpaceState)->FUN_01003a50();
    ((cSelf*)((cSelf*)FUN_00b3d300((int)(intptr_t)a1))->FUN_00f67d90())->FUN_00c79fa0(a1);

    void* e = ((V38b*)((V50*)FUN_0067dd10())->GetModeManager())->Get38();
    if (e != 0) {
        void* tag = ((V0c*)e)->Query(0x303154cc);
        if (tag != 0)
            ((cSelf*)tag)->FUN_0101be60();
    }

    void* inv = ((cSelf*)FUN_00ffbe50())->FUN_00a1ad60();
    if (planet != 0) {
        ((cSelf*)inv)->FUN_00c3c190(planet);
        float f = ((cSelf*)inv)->FUN_00c3ae70();
        Vector3 v;
        void* res = FUN_0105c3d0(&v, planet, f);
        ((cSelf*)inv)->FUN_00c381e0(res);
    }
}

// @ 0x00fdd4f0
void cAppModeSpace::TransitionThroughWormhole()
{
    void* g = FUN_01021240();
    void* v = ((cSelf*)FUN_00b3d2a0(g))->FUN_00ba6f20();
    if (v == 0)
        return;

    ((cSPSpaceGameState*)mpSpaceState)->mFlags |= 0x20;

    void* nm = ((cSelf*)FUN_00b3d300())->FUN_00f67d90();
    ((cSelf*)nm)->FUN_00c7a160(g);

    TransitionFromPlanetToSolar(v, 1);

    void* fx = FUN_0067ddd0();
    cWorm* worm = (cWorm*)FUN_00b3d470();
    void* o = worm->p8c;
    void** slot = &worm->p8c;
    if (o != 0) {
        *slot = 0;
        ((V04*)o)->Destroy();
    }
    if (((V2cR*)fx)->GetProp3(0xa641232e, 0, slot)) {
        void** slot2 = &((cWorm*)FUN_00b3d470())->p8c;
        void* q = *slot2;
        ((V08a*)q)->Unlink2((void*)0);
    }
}

// @ 0x00fdd5a0
void cAppModeSpace::TransitionFromGalaxyToSolar()
{
    void* inv = ((cSelf*)FUN_00ffbe50())->FUN_00a1ad60();
    void* anm = FUN_01021240();
    FUN_01021230();

    ((cSPSpaceGameState*)mpSpaceState)->mFlags |= 8u;

    ((cSelf*)((cSelf*)FUN_00b3d300(0x574ac69))->FUN_00f67d90())->FUN_00c77bf0();

    ((V50x*)FUN_0067dd50())->X50(0x17);

    ((cSelf*)mpSpaceState)->FUN_01003620();
    ((cSelf*)mpSpaceState)->FUN_01003a50();
    ((cSelf*)mpSpaceState)->FUN_01009470(1, (void*)1, 0);
    ((cSelf*)mpSpaceState)->FUN_010077e0();

    if (((cSelf*)anm)->FUN_00bb9ae0() == 5) {
        void* ship = ((cSelf*)FUN_00b3d2a0(anm))->FUN_00bb1340();
        if (ship != 0) {
            ((cSelf*)ship)->FUN_00c31c30(1);
            ((cSelf*)DAT_016dc798)->FUN_01014a80i((int)(intptr_t)((c28*)ship)->p84, 3);
            void* av = ((cSelf*)anm)->FUN_00b1fdb0();
            if (av != (void*)(intptr_t)FUN_01021090()) {
                void* o = ((cSelf*)ship)->FUN_00c326b0();
                if (!((V1c2*)FUN_00401010())->Test1c(o, 0)) {
                    if (!((V3cq*)FUN_00401010())->Test3c(o)) {
                        Filter8 key;
                        key.id = 0; key.a = 0; key.b = 1;
                        ((V4c2*)FUN_00401010())->Test4c(o, (int)(intptr_t)&key);
                    }
                }
            }
        }
    }

    Vector3 v0;
    v0.x = 0.0f; v0.y = 0.0f; v0.z = 0.0f;
    ((cSelf*)FUN_00b3d2a0(anm))->FUN_00bb5b70(&v0);

    void* planet = FUN_01021260();
    if (planet == 0) {
        void* r = FUN_00fdd200();
        if (r != 0)
            FUN_010219b0(FUN_01021240(), r);
        planet = FUN_01021260();
    }

    ((cSelf*)inv)->FUN_00c3bfe0(&DAT_016d9944);

    float k = DAT_015b4200;
    Vector3 sv;
    sv.x = DAT_015b4034 * k;
    sv.y = DAT_015b4038 * k;
    sv.z = DAT_015b403c * k;
    ((cSelf*)inv)->FUN_00c381e0(&sv);
    ((cSelf*)inv)->FUN_00c37e6f();

    if (planet != 0)
        ((cSelf*)inv)->FUN_00c3c190(FUN_01021260());

    void* t = ((c24*)FUN_00b3d470())->p24;
    if (((V10*)t)->IsDone())
        ((V0ci*)((c24*)FUN_00b3d470())->p24)->Reset(1);
    void* u = ((c24*)FUN_00b3d470())->p2c;
    if (((V10*)u)->IsDone())
        ((V0ci*)((c24*)FUN_00b3d470())->p2c)->Reset(1);

    void* reg = FUN_00b3d3d0();

    IdKey key;
    key.a = DAT_016d9950;
    key.b = DAT_016d9954;
    key.c = DAT_016d9958;

    switch (((cSelf*)anm)->FUN_00801920() - 1) {
    case 0:  key.a = 0x7658db58; break;
    case 1:  key.a = 0x7658db59; break;
    case 2:  key.a = 0x7658db5a; break;
    case 3:  key.a = 0x7658db5b; break;
    case 4:  key.a = 0x7658db5c; break;
    case 5:  key.a = 0x7658db5d; break;
    case 6:  key.a = 0x7658db5e; break;
    case 7:  key.a = 0x7658db5f; break;
    case 8:  key.a = 0x7658db60; break;
    case 9:  key.a = 0x7658db61; break;
    case 10: key.a = 0x7658db62; break;
    case 11: key.a = 0x7658db63; break;
    default: key.a = 0x7658db5c; break;
    }

    if (key.a != DAT_016d9950 || key.b != DAT_016d9954 || key.c != DAT_016d9958) {
        if (!((cSelf*)anm)->FUN_00bb9bd0()) {
            void* x = FUN_01002bd0ii(0x15, 1);
            void* y = ((cSelf*)x)->FUN_00bfc5f0();
            ((cSelf*)y)->FUN_00fe5430();
        }
        if (((cSelf*)reg)->FUN_0103ac40(&key) != 1) {
            IdKey key2 = key;
            ((cSelf*)reg)->FUN_0103fba0(&key2, (void*)(intptr_t)1);
            void* g = FUN_00b3d3e0(0x8ab22514, 0x131a9f54, 0, 0, 1, 0);
            ((cSelf*)g)->FUN_00dd8640i();
        }
    }

    ((cSelf*)((cSelf*)FUN_00b3d300((int)(intptr_t)anm))->FUN_00f67d90())->FUN_00c79fa0(anm);

    if (((cSelf*)anm)->FUN_00801920() == 1) {
        void* g = FUN_00675250(0xf88c1342, 1);
        ((cSelf*)g)->FUN_00676e90();
    }

    void* fx = ((cSPSpaceGameState*)mpSpaceState)->mpEffect;
    if (fx != 0)
        ((cSelf*)fx)->FUN_01036620(0);

    void* e = ((V38b*)((V50*)FUN_0067dd10())->GetModeManager())->Get38();
    if (e != 0) {
        void* tag = ((V0c*)e)->Query(0x303154cc);
        if (tag != 0)
            ((cSelf*)tag)->FUN_0101bd10();
    }

    ((cSPSpaceGameState*)mpSpaceState)->mFlags &= ~8u;

    ((V18v4*)FUN_0067dcc0())->Install4(0x5e37a44, (void*)0, (void*)0, 0);

    ((cSelf*)&v0)->FUN_00ad92d0();
}

// @ 0x00fdda10
void FUN_00fdda10(cVector* list, int id1, int id2, void* arg4, void* arg5)
{
    void* st = FUN_00b3d4d0();
    uint32_t mode = ((cDet0*)st)->m2c;
    if (mode == 1 || mode == 2)
        return;

    void* nm = ((cSelf*)FUN_00b3d300((int)(intptr_t)arg5))->FUN_00f67d90();
    if (((cSelf*)nm)->FUN_00c772c0())
        return;

    uint32_t* it = (uint32_t*)list->begin;
    uint32_t* endp = (uint32_t*)list->end;
    while (it != endp) {
        void* e = (void*)*it;
        if (((cSelf*)e)->FUN_01030e10() == id1 &&
            ((cSelf*)e)->FUN_00970b30i() == id2 &&
            ((cSelf*)e)->FUN_00c44c80()) {
            Vec3Pad v;
            v.tag = 0; v.x = 0.0f; v.y = 0.0f; v.z = 0.0f;
            FUN_0057cc10(&v, arg4, (void*)0, arg5);
            if (((cSelf*)FUN_01002bd0())->FUN_0100a7c0m()) {
                bool keep = false;
                if (e != 0 && ((V0c*)e)->Query(0x2f9998c) != 0)
                    keep = true;
                else if (FUN_00e98ac0(e) != 0)
                    keep = true;
                if (keep) {
                    uint32_t pos[4];
                    FUN_00fdb0c0(&pos[0]);
                    uint32_t pa = 0, pb = 0, pc = 0;
                    ((cSelf*)&pc)->FUN_00ad79d0(&pa, &pb);
                    uint32_t buf[4];
                    buf[0] = 0; buf[1] = 0;
                    ((cSelf*)FUN_00b3d4d0(0x9eb74bbc, &buf[0], 0))->FUN_00ae09b0();
                    ((cSelf*)&buf[0])->FUN_00ad7ad0();
                }
            }
        }
        ++it;
    }
}
