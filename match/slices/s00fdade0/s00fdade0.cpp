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
void* FUN_00b3d300(int id);                                    // 0x00b3d300  NounManager(id)
void* FUN_00b3d2a0(void* avatar);                              // 0x00b3d2a0
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
void* FUN_00b3d4d0(int id, void* buf, int n);                  // 0x00b3d4d0
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

    uint8_t   pad000[0x0a8];
    cSPTimer  mTimerA8;                                   // +0x0a8  (entry timer)
    uint8_t   pad0c0[0x50];
    cSPTimer  mSpaceTimer;                                // +0x110 (leave-space timer)
    float     mViewX;                                     // +0x128
    float     mViewY;                                     // +0x12c
    uint8_t   pad130[0x10];
    cVesselPtr mVessel140;                                // +0x140
    uint8_t   pad144[0x18];
    cSPSpaceGameState* mpSpaceState;                      // +0x15c
    uint8_t   pad160[0x9];
    bool      mFlag169;                                   // +0x169
    uint8_t   pad16a[0x12];
    void*     mpList17c;                                  // +0x17c (list sentinel)
    void*     mpList180;                                  // +0x180
    uint8_t   pad184[0x4];
    cObj188*  mpObj188;                                   // +0x188
    uint8_t   pad18c[0x2];
    bool      mFlag18e;                                   // +0x18e
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

// @ 0x00fdb230
void FUN_00fdb230(uint32_t** out, uint32_t* begin, uint32_t* end, const uint32_t* key)
{
    if (begin == end) {
        *out = begin;
        return;
    }
    while (begin != end) {
        if (begin[2] == key[0] && begin[3] == key[1] && begin[4] == key[2])
            break;
        begin = (uint32_t*)*begin;
    }
    *out = begin;
}

// @ 0x00fdb0c0
void FUN_00fdb0c0(Vector3* out)
{
    void* planet = FUN_01021260();
    void* eradicator = 0;
    if (planet == 0)
        goto L1f8;

    {
        void* other = 0;
        cVector* list = (cVector*)((cSelf*)FUN_00feb9f0())->FUN_00fedd50();
        void** begin = list->begin;
        int count = (int)(list->end - begin);
        int index = 0;
        if (count > 0) {
            do {
                if (eradicator != 0 || other != 0)
                    break;
                void* m = begin[index];
                if (((cSelf*)m)->FUN_00970b30() == planet) {
                    if (m != 0)
                        eradicator = ((V0c*)m)->Query(0x2f9998c);
                    else
                        eradicator = 0;
                    if (m != 0)
                        other = ((V0c*)m)->Query(0x437443d);
                }
                index++;
            } while (index < count);
        }

        void* inv = ((cSelf*)FUN_00ffbe50())->FUN_00a1ad60();
        Vector3 v = DAT_016d9944;
        void* targets = &((cPlayerInventory*)inv)->mDiseaseTargets;
        if (eradicator != 0) {
            ((cSelf*)eradicator)->FUN_00c50300(targets, &v);
        } else {
            if (other == 0)
                goto L1f8;
            ((cSelf*)other)->FUN_00c4cb90(targets, &v);
        }
        out->x = v.x;
        out->y = v.y;
        out->z = v.z;
        return;
    }

L1f8:
    out->x = DAT_016d9944.x;
    out->y = DAT_016d9944.y;
    out->z = DAT_016d9944.z;
}

// @ 0x00fdade0
void cAppModeSpace::FUN_00fdade0()
{
    ((cSelf*)FUN_00feb9f0())->FUN_00fee0a0(3);

    void* nounMgr = FUN_01021240();
    bool isFive = (((cSelf*)nounMgr)->FUN_00bb9ae0() == 5);
    if (((cSelf*)nounMgr)->FUN_00bb9fb0() && !isFive) {
        int r = FUN_01041c50(DAT_01493f48, 0x5b1a673, 1);
        if (r == 0) {
            void* ev = FUN_00b3d3e0(0x1dbea1b6, 0x131a9f54, 0, 0, 1, 0);
            ((cSelf*)ev)->FUN_00dd8640();
        }
        ((cSelf*)FUN_01002bd0())->FUN_010097f0();
        ((cSelf*)nounMgr)->FUN_00bb9b30();
    }

    if (((cSelf*)nounMgr)->FUN_00bb9ae0() == 5) {
        void* avatar = ((cSelf*)nounMgr)->FUN_00b1fdb0();
        if (avatar != (void*)(uintptr_t)FUN_01021090()) {
            void* a1 = ((cSelf*)FUN_00b3d300(0xdab99813))->FUN_00f67d90();
            if (!((cSelf*)a1)->FUN_00c772c0()) {
                void* a2 = ((cSelf*)FUN_00b3d300(0x5f1f0bc))->FUN_00f67d90();
                ((cSelf*)a2)->FUN_00c77bf0();
                mpObj188->flag49 = 0;

                void* nm2 = FUN_01021240();
                void* av2 = ((cSelf*)nm2)->FUN_00b1fdb0();
                int   id  = ((cSelf*)FUN_00b3d2a0(av2))->FUN_00ba9370();
                cUfo* ufo = (cUfo*)FUN_0102ac50(8, (void*)(uintptr_t)id);

                float scale = DAT_01493e38;
                ufo->mB7b0 = (uint32_t)(uintptr_t)nm2;
                ufo->mB6b0 = 0;
                ufo->mPose694 = DAT_015b4028;
                ufo->mPose698 = DAT_015b402c;
                ufo->mPose69c = DAT_015b4030;
                ufo->mBody.SetPose(scale);

                ((cSelf*)FUN_01002bd0s(ufo))->FUN_01009a40();

                void* modeMgr = ((V1c*)((V50*)FUN_0067dd10())->GetModeManager())->Current();

                Vector3 loc;
                ((cSelf*)modeMgr)->FUN_007c3d30(0, &loc, 0, 0);

                Vector3* pos = (Vector3*)((V2cp*)FUN_01021260())->GetPosition();
                float s = DAT_015b41fc;
                Vector3 dest;
                dest.x = (s * loc.x) + pos->x;
                dest.y = (s * loc.y) + pos->y;
                dest.z = (s * loc.z) + pos->z;
                ((cSelf*)ufo)->FUN_00c3bfe0(&dest);
                ((cSelf*)ufo)->FUN_00c37e60();

                void* r = ((cSelf*)FUN_00ffbe50())->FUN_01001b60();
                uint8_t str[0x24];
                ((cSelf*)str)->FUN_00ad7a30(r ? (void*)&((cEmbd34*)r)->sub34 : 0);
                ((cSelf*)FUN_00b3d4d0(0xfbd1dba, str, 0))->FUN_00ae09b0();
                FUN_01041c50(DAT_01493f2c, 0xdab99813, 1);
                ((cSelf*)str)->FUN_00ad7ad0();
            }
        }
    }

    if (isFive) {
        void* avatar = ((cSelf*)nounMgr)->FUN_00b1fdb0();
        void* empire = (void*)(uintptr_t)FUN_01021090();
        if (avatar != empire) {
            void* rel = FUN_00b3d2c0(avatar, empire);
            if (!((cSelf*)rel)->FUN_00d01fb0()) {
                float f = ((cSelf*)FUN_00b3d2c0(avatar, empire, 0))->FUN_00d00a10();
                if (((cSelf*)FUN_010407c0f(f))->FUN_01040820() >= 1.0f)
                    FUN_01041c50(DAT_0146f110, 0xf317692a, 1);
            }
        }
    }
}

// @ 0x00fdb330
bool cAppModeSpace::FUN_00fdb330(int a, float f1, float f2)
{
    (void)a;

    if (((V18b*)FUN_00b3d250())->Probe(0xcdcdcdcd)) {
        if (((cSelf*)FUN_0067cab0())->FUN_00801400()) {
            mViewX = f1;
            mViewY = f2;
            ((cSelf*)FUN_0067cab0())->FUN_008013d0(0);
            ((cSelf*)FUN_0067cab0())->FUN_00801950((void*)0x67f5c34);
            ((cSelf*)FUN_0067cab0())->FUN_00801980(1);
        }

        void* nm = FUN_00b3d380();
        if (!(((cNounMgr*)nm)->mFlags48 & 1)) {
            ((cSpaceSim*)FUN_00ffbe50())->mFlag55 = 1;
        }

        void* tool = ((cSelf*)mpSpaceState)->FUN_00a1ad60();
        tool = ((cSelf*)tool)->FUN_00ff3f00();
        if (tool != 0) {
            ((V04*)tool)->Destroy();
            if (((cSelf*)tool)->FUN_0104bd50()) {
                void* obj140 = ((cToolObj*)tool)->mpObj;
                bool skip = false;
                if (obj140 != 0) {
                    if (((V10*)obj140)->IsDone())
                        skip = true;
                }
                if (!skip)
                    ((cSelf*)FUN_00b3d390(tool))->FUN_0104fa90();
            }
        }

        void* nm2 = FUN_00b3d380();
        if (!(((cNounMgr*)nm2)->mFlags48 & 1)) {
            unsigned long long t = ((cSelf*)&mSpaceTimer)->FUN_0093a5e0();
            if (t > 0xfa) {
                void* inv = ((cSelf*)FUN_00ffbe50())->FUN_00a1ad60();
                void* placed = ((cPlayerInventory*)inv)->mBody.DoPlace(1, 0, 1, 0);
                ((cSelf*)FUN_00ffbe50())->FUN_00ffc350(placed);
            }
        }

        mSpaceTimer.lo = 0;
        mSpaceTimer.hi = 0;
        mSpaceTimer.lo2 = 0;
        mSpaceTimer.hi2 = 0;

        if (tool != 0)
            ((V08*)tool)->Unlink();      // tool vtable +0x8

        return true;
    }

    if (((V18b*)FUN_00b3d250())->Probe(0xcccccccc)) {
        if ((mSpaceTimer.lo | mSpaceTimer.hi) == 0 &&
            !(((cNounMgr*)FUN_00b3d380())->mFlags48 & 1)) {
        ((cSelf*)&mSpaceTimer)->FUN_00571e80();

        void* inv = ((cSelf*)FUN_00ffbe50())->FUN_00a1ad60();
        void* toolArg = (void*)&((cPlayerInventory*)inv)->mTool;

        uint8_t aux[0x30];
        ((cSelf*)aux)->FUN_00434040();
        ((V40b*)FUN_00b3d240())->Place(aux, 1, toolArg);
        ((cSelf*)FUN_00ffbe50())->FUN_00ffc350(aux);
        ((cSelf*)FUN_00ffbe50())->FUN_00ffc030();

        void* slot = 0;
        void* mgr = FUN_0067ddd0();
        if (((V2c3*)mgr)->SetPortal(&slot, 0, 0x384e54a4)) {
            uint8_t sA[0x28];
            uint8_t sB[0x40];
            uint8_t sC[0x50];
            ((cSelf*)sA)->FUN_00434040();
            FUN_00449c20(sB, sA);
            void* r1 = FUN_006985b0(sC, sB);
            FUN_00449c20(sB, r1);
            void* r2 = FUN_0069b440(sC, sB, sA);
            ((V18p*)r2)->Put(sA);
            if (slot != 0)
                ((V08*)FUN_0067ddd0())->Unlink();
        }

        void* modeMgr = ((V38*)((V50*)FUN_0067dd10())->GetModeManager())->Get14();
        if (modeMgr != 0) {
            void* q = ((V0c*)modeMgr)->Query(0x303154cd);
            if (q != 0)
                ((cSelf*)q)->FUN_01017270((void*)0);
        }
        if (slot != 0)
            ((V04*)slot)->Destroy();
        return true;
        }
    }

    if (((V18b*)FUN_00b3d250())->Probe(0xdddddddd)) {
        void* tool = ((cSelf*)mpSpaceState)->FUN_00a1ad60();
        tool = ((cSelf*)tool)->FUN_00ff3f00();
        if (tool == 0)
            return true;
        void* r = ((cSelf*)tool)->FUN_0104f930();
        if (r == 0)
            return true;
        Vector3 v = DAT_016d9944;
        ((V3c*)r)->Set3c(&v);
        ((cSelf*)this)->FUN_00fda2e0(&v);
        return true;
    }

    return false;
}

// @ 0x00fdb710
bool cAppModeSpace::Activate()
{
    ((cSelf*)&mTimerA8)->FUN_00bc30f0();

    void* cheat = FUN_0067de20();
    cCommand* c1;

    c1 = (cCommand*)operator new[](0x10, DAT_013f09b4, 0, 0, 0, 0);
    if (c1) { ((cSelf*)c1)->FUN_0083c800(); c1->vftable = (void*)0x1493e6c; }
    c1 = (cCommand*)operator new[](0x10, DAT_013f09b4, 0, 0, 0, 0);
    if (c1) { ((cSelf*)c1)->FUN_0083c800(); c1->vftable = (void*)0x1493e84; }
    c1 = (cCommand*)operator new[](0x10, DAT_013f09b4, 0, 0, 0, 0);
    if (c1) { ((cSelf*)c1)->FUN_0083c800(); c1->vftable = (void*)0x1493e9c; }
    c1 = (cCommand*)operator new[](0x10, DAT_013f09b4, 0, 0, 0, 0);
    if (c1) { ((cSelf*)c1)->FUN_0083c800(); c1->vftable = (void*)0x1493eb4; }
    c1 = (cCommand*)operator new[](0x10, DAT_013f09b4, 0, 0, 0, 0);
    if (c1) { ((cSelf*)c1)->FUN_0083c800(); c1->vftable = (void*)0x1493ecc; }
    c1 = (cCommand*)operator new[](0x14, DAT_013f09b4, 0, 0, 0, 0);
    if (c1) { ((cSelf*)c1)->FUN_0083c800(); c1->vftable = (void*)0x1493e3c; c1->flag10 = 1; }
    c1 = (cCommand*)operator new[](0x10, DAT_013f09b4, 0, 0, 0, 0);
    if (c1) { ((cSelf*)c1)->FUN_0083c800(); c1->vftable = (void*)0x1493ee4; }
    c1 = (cCommand*)operator new[](0x10, DAT_013f09b4, 0, 0, 0, 0);
    if (c1) { ((cSelf*)c1)->FUN_0083c800(); c1->vftable = (void*)0x1493efc; }

    ((V18v*)cheat)->Install(DAT_015b734c, c1, 0);

    ((cSelf*)FUN_00b3d3e0f(0.0f, DAT_0146138c))->FUN_00dd5a10();
    ((cSelf*)FUN_00b3d3c0())->FUN_00b72870();

    ((V98*)FUN_0067ddd0())->SetFx(0x11, 0);
    ((V98*)FUN_0067ddd0())->SetFx(0x12, 0);
    ((V98*)FUN_0067ddd0())->SetFx(0x14, 1);
    ((V98*)FUN_0067ddd0())->SetFx(0x13, 0);

    mFlag18f = 1;
    mFlag190 = 0;
    mFlag191 = 0;
    mFlag192 = 0;

    void* oA = FUN_00b3d470();
    if (oA != 0) {
        void* pA = ((cCheatRoot*)FUN_00b3d470())->pA4;
        if (pA != 0)
            ((V0ci*)pA)->Reset(0);
    }
    void* oB = FUN_00b3d470();
    if (oB != 0) {
        void* pB = ((cCheatRoot*)FUN_00b3d470())->p94;
        if (pB != 0)
            ((V0ci*)pB)->Reset(0);
    }
    return true;
}

// @ 0x00fdb9a0
void cAppModeSpace::FUN_00fdb9a0()
{
    void* world = FUN_00b3d520();
    IVec3 v = *(IVec3*)((cSelf*)FUN_01021300())->FUN_00c30f90();

    if (world == 0)
        return;
    if (v.x == 0)
        return;

    void* obj = FUN_00401010();
    Filter8 filter;
    filter.a = 0;
    filter.b = 4;
    filter.id = 0x2ea8fb98;
    ((V4c*)obj)->Assign2(&v, &filter);

    cVesselPtr* slot = &mVessel140;
    void* made = ((V0cW*)world)->Make((void*)(uintptr_t)v.x, (void*)(uintptr_t)v.z, 0);
    ((cSelf*)slot)->FUN_00478db0(made);

    void** p = slot->mpObj;
    if (p != 0)
        ((V16c*)(*p))->Attach(p, 0);
}

// @ 0x00fdba50
void cAppModeSpace::TransitionFromCivToSpace(int a, int b)
{
    void* inv = ((cSelf*)FUN_00ffbe50())->FUN_00a1ad60();

    if (inv != 0) {
        ((cSelf*)inv)->FUN_00c37130(0);

        cHall* hall = 0;
        void* city = ((cSelf*)FUN_00b3d300(0))->FUN_00b25c30();
        if (city != 0) {
            void* h = ((cSelf*)city)->FUN_00bd9b40();
            if (h != 0)
                hall = (cHall*)&((cEmbd34*)h)->sub34;
        }

        ((cSelf*)hall)->FUN_00ad7a30(0);
        uint8_t buf1[0x24];
        ((cSelf*)FUN_00b3d4d0(0x6ce68a32, buf1, 0))->FUN_00ae09b0();

        float fVec[4];
        uint8_t buf3[0x0c];
        ((cSelf*)city)->FUN_00bd7f70(&fVec[0], &fVec[1]);
        float* dir = (float*)((cSelf*)FUN_00b3d350(buf3, 0))->FUN_00b815a0();
        fVec[0] = dir[0];
        fVec[1] = dir[1];
        fVec[2] = dir[2];

        void* orient = ((cBodyQ*)&((cEmbd34*)hall)->sub34)->GetOrientation();
        ((cSelf*)fVec)->FUN_00ad79d0(orient, 0);

        uint8_t buf2[0x24];
        ((cSelf*)FUN_00b3d4d0(0xb3393b83, buf2, 0))->FUN_00ae09b0();
        ((V68*)hall)->StopFX();
        ((cSelf*)inv)->FUN_00c3aa40(fVec, orient);
        float sq = sqrtf((fVec[0] * fVec[0]) + (fVec[1] * fVec[1]) + (fVec[2] * fVec[2]));
        ((cSelf*)inv)->FUN_00c3daa0(sq + DAT_01486110);
        ((cSelf*)buf2)->FUN_00ad7ad0();
        ((cSelf*)buf1)->FUN_00ad7ad0();
    }

    if (DAT_015fd928 != 0) {
        cTestSys* ts = (cTestSys*)DAT_015fd928;
        if (ts->m70 != (void*)&ts->m70) {
            ((cSelf*)inv)->FUN_00c37130(1);
            return;
        }
    }

    void* avatar = ((cSelf*)mpSpaceState)->FUN_00b1fdb0();
    if (avatar != 0) {
        float f = ((cBC30*)FUN_00bc30b0())->m24 * DAT_0145c464;
        ((cSelf*)FUN_00bc30b0())->FUN_00bc2f00(f);
        ((cSelf*)avatar)->FUN_00ff5ee0((void*)(uintptr_t)a, (void*)(uintptr_t)b);
    }
}

// @ 0x00fdbc20
void cAppModeSpace::CompleteTransitionFromEntryToNewGame()
{
    if (mFlag169) {
        ((cSelf*)FUN_00b3d380())->FUN_00b32250(0x4bf38a7);

        void* sentinel = &mpList17c;
        cListNode* node = (cListNode*)mpList17c;
        int i = 0;
        do {
            if (node->flag08) {
                void* ui = FUN_0067dd50();
                ((V5c*)ui)->SetSlot((void*)(uintptr_t)i, 1);
            }
            node = node->pNext;
            i++;
        } while (i <= 0x1b);

        cListNode* n = (cListNode*)mpList17c;
        while (n != (cListNode*)sentinel) {
            cListNode* next = n->pNext;
            operator_delete__(n);
            n = next;
        }
        mpList17c = sentinel;
        mpList180 = sentinel;
        mFlag169 = 0;
    }

    if (((cSelf*)DAT_015fd918)->FUN_006a25a0(0x7ae23adf)) {
        if (!mFlag18e) {
            void* effect = mpSpaceState->mpEffect;
            if (effect != 0)
                ((cSelf*)effect)->FUN_01065af0();
        }
    }

    Vector3 v;
    v.x = 0; v.y = 0; v.z = 0;
    ((cSelf*)((cGPtr9938*)DAT_016d9938)->m160)->FUN_0102f660(&v);

    void* noun = FUN_00b3d300((int)(uintptr_t)&v);
    void* mid = ((cSelf*)noun)->FUN_00f67d90();
    ((cSelf*)mid)->FUN_00c75740();

    void* obj = FUN_00401010();
    if (!((V18pb*)obj)->Pick(&v)) {
        Filter8 filter;
        filter.id = 0;
        filter.a = 0;
        filter.b = 4;
        ((V4c*)FUN_00401010())->Assign2(&v, &filter);
    }

    mpSpaceState->mFlags &= 0xffffffef;
}