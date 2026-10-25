// src/game/SPGonzago/SPAppModeSpace.cpp -- migrated from slice(s) s00fe2ec0, s00fe1a20, s00fdf9f0, s00fdcd40, s00fdbd60, s00fdade0, s00fd9f70, s00fd90c0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPAppModeSpace.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cGonzagoSubsystem.h"
#include <math.h>
#include "SP/cGameNounManager.h"
#include "SP/cGonzagoTimer.h"
#include "SP/cLocalInputState.h"
#include "SP/cPlanetModel.h"
#include "SP/cPropertyList.h"
#include "SP/cCombatant.h"
#include "SP/cCommunity.h"
#include "SP/cEmpire.h"
#include "SP/cPlanet.h"
#include "SP/cPlanetRecord.h"
#include "SP/cRelationshipManager.h"
#include "SP/cTerrainSphere.h"

// unnamed retail callees and globals (address in the comment)
extern void* DAT_01654c05;

// ---- items of slice s00fd90c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
extern void* DAT_01654c05;
void* __cdecl  FUN_0067caa0();                       // SP::WindowManager
void* __cdecl  FUN_00b2f740();                       // returns char
void* __cdecl  FUN_00805180();                       // returns char
void* __cdecl  FUN_00b3d250();                       // SP::GameInputManager
void* __cdecl  FUN_00b3d2c0();                       // SP::RelationshipManager
void* __stdcall FUN_00b3d470(void*);                 // 0x00b3d470 -> void*
void* __cdecl  FUN_00b5b800();                       // SP::GetCurrentGameMode
int   __stdcall FUN_01021230(int);                   // 0x01021230
int   __stdcall FUN_01021230_0();                    // 0x01021230 (no-arg call site)
void  __cdecl  FUN_010213b0(int);                    // 0x010213b0
int   __cdecl  FUN_01021080();                       // GetUniverseContext
void* __cdecl  FUN_00d06400();                       // 0x00d06400
struct Ext {
    void* FUN_00fcd940(int);                  // 0x00fcd940 ctor helper
    void* FUN_00fd9680();                     // 0x00fd9680 ctor
    void* FUN_00fc7dd0(void*);                // 0x00fc7dd0 ctor
    void* FUN_00fc8080();                     // 0x00fc8080 ctor
    void* FUN_00fd95e0();                     // 0x00fd95e0 ctor
    void* FUN_00fcde80();                     // 0x00fcde80 ctor
    void* FUN_00fc7f30();                     // 0x00fc7f30 ctor
    void* FUN_011e64a0(int, void*);           // 0x011e64a0
    void  FUN_011ef880(void*);                // 0x011ef880
    void* FUN_00fd8c40(void*);                // 0x00fd8c40 cMovieCheat ctor
    void* FUN_00576650(void*);                // GetImageResource (0x00576650)
    void* FUN_00ae9390();                     // 0x00ae9390 -> char
    void  FUN_00e190c0(int);                  // 0x00e190c0
    void* FUN_00e18c70(void*);                // 0x00e18c70 -> char
    int   FUN_00bb9ae0();                     // 0x00bb9ae0
    void* FUN_00b1fdb0();                     // GetAvatar
    void  FUN_00d00a10(void*, int);           // returns float
    void* FUN_01040820();                     // returns float
    void* FUN_00c8b770();                     // cStar::GetSolarSystem
    void  FUN_00c86c70();                     // cSolarSystem::ActivateGraphics
    void  FUN_01034b90();                     // 0x01034b90
    void  FUN_00d06400();                     // 0x00d06400
    char  FUN_00d09660();                     // 0x00d09660 -> char
    void* FUN_01065e20();                     // 0x01065e20 -> char
    void  FUN_01067b60();                     // 0x01067b60
};
static inline Ext* E(void* p) { return (Ext*)p; }
static inline void** VTP(void* o) { return *(void***)o; }
struct AppMode {
    u8 raw[0x200];
    void f9c90(int a);
    char f9ce0(int a, int b);
    int  f9d00();
    void f9d30();
    void f9d90();
    void f9de0();
    void f9ea0(int key, int param3);
};
char f9e80(int a, int* p);   // free callback
// ---- items of slice s00fd90c0 end

// ---- items of slice s00fd9f70 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma warning(disable : 4100)
namespace SP {
class cGonzagoSubsystem_s00fd_9f70 {
public:
    virtual void Shutdown(int immediate);                // +0x00
    virtual void v04();                                  // +0x04
    virtual void Release();                              // +0x08
};
}
namespace SP {
class cAppModeSpace {
public:
    void OnMouseUp();
    void Deactivate();
    void ShutdownGonzagoSubsystem();
    void SetPlanetTimeOnFirstEntry();
    void Write();
    void FUN_00fda1f0();
    void FUN_00fda2e0();
    void FUN_00fda480();
    void FUN_00fda5e0();
    void FUN_00fda750();
    void FUN_00fda940();
    void FUN_00fda9f0();
    void FUN_00fdab40();
    void FUN_00fdabf0();

    uint8_t             pad000[0x180];                   // +0x000 .. +0x17f
    cGonzagoSubsystem_s00fd_9f70*  mpGonzagoSubsystem;              // +0x180
};
}
// ---- items of slice s00fd9f70 end

// ---- items of slice s00fdade0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* FUN_00b3d470();                                          // 0x00b3d470
extern float   DAT_01493e38;                 // 0x01493e38
extern float   DAT_015b41fc;                 // 0x015b41fc
extern float   DAT_015b4028;                 // 0x015b4028
extern float   DAT_015b402c;                 // 0x015b402c
extern float   DAT_015b4030;                 // 0x015b4030
extern float   DAT_01486110;                 // 0x01486110  (5.0f)
extern float   DAT_0145c464;                 // 0x0145c464  (0.4166666f)
extern void*   DAT_015fd928;                 // 0x015fd928  (cTestSystem singleton)
extern void*   DAT_015fd918;                 // 0x015fd918  (app property list)
extern void*   DAT_016d9938;                 // 0x016d9938
extern char    DAT_01493f48[];               // 0x01493f48  "SPG_SetiAmbush"
extern char    DAT_01493f2c[];               // 0x01493f2c  "SPG_FirstContact_Intercept"
extern char    DAT_0146f110[];               // 0x0146f110  "SPG_FirstAlliancePossible"
struct Vector3 { float x, y, z; };
struct Filter8 { uint32_t id; uint16_t a; uint16_t b; };
struct IVec3 { int x, y, z; };
void __cdecl operator_delete__(void* p);                                                                                         // 0x00f47380
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
struct V04   : B00 { virtual void Destroy() = 0; };                            // +0x04
struct V08   : B01 { virtual void Unlink() = 0; };                             // +0x08
struct V0c   : B02 { virtual void* Query(int ifaceId) = 0; };                  // +0x0c (1 int)
struct V0cW  : B02 { virtual void* Make(void* a, void* b, int c) = 0; };       // +0x0c (3 args)
struct V10   : B03 { virtual bool  IsDone() = 0; };                            // +0x10
struct V18b  : B05 { virtual bool  Probe(int kind) = 0; };                     // +0x18 (int -> bool)
struct V18pb : B05 { virtual bool  Pick(void* out) = 0; };                     // +0x18 (ptr -> bool)
struct V18p  : B05 { virtual void  Put(void* in) = 0; };                       // +0x18 (ptr)
struct V1c   : B06 { virtual void* Current() = 0; };                           // +0x1c
struct V2cp  : B10 { virtual void* GetPosition() = 0; };                       // +0x2c (position)
struct V2c3  : B10 { virtual bool  SetPortal(void* a, int b, int c) = 0; };    // +0x2c (3 args)
struct V38   : B13 { virtual void* Get14() = 0; };                             // +0x38
struct V40b  : B15 { virtual void  Place(void* a, int b, void* c) = 0; };      // +0x40 (3 args)
struct V4c   : B18 { virtual void  Assign2(void* a, void* b) = 0; };           // +0x4c
struct V50   : B19 { virtual void* GetModeManager() = 0; };                    // +0x50
struct V5c   : B22 { virtual void  SetSlot(void* a, int b) = 0; };             // +0x5c
struct V68   : B25 { virtual void  StopFX() = 0; };                            // +0x68
struct V16c  : B90 { virtual void  Attach(void* a, int b) = 0; };              // +0x16c
struct V3c   : B14 { virtual void  Set3c(Vector3* v) = 0; };                   // +0x3c (Vector3*)
struct cToolObj { uint32_t pad0[80]; void* mpObj; };                            // +0x140 object handle
struct cEmbd34 { uint32_t pad0[13]; uint32_t sub34; };                          // embedded sub-object at +0x34
struct cBC30   { uint32_t pad0[9];  float    m24; };                            // +0x24 float
struct cTestSys { uint32_t pad0[28]; void*   m70; };                            // +0x70 list sentinel
struct cBodyF : public B15 { virtual void SetPose(float) {} };                 // +0x40
struct cBody4 : public B10 { virtual void* DoPlace(int, int, int, int) { return this; } };  // +0x2c
struct cBodyQ : public B11 { virtual void* GetOrientation() { return 0; } };   // +0x30
extern Vector3 DAT_016d9944;                 // 0x016d9944 -- {0,0,0}; +4/+8 continue the vector
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
void* FUN_00b3d520();                                          // 0x00b3d520  GonzagoModelWorld
void* FUN_00b3d380();                                          // 0x00b3d380  game noun manager
void* FUN_00b3d240();                                          // 0x00b3d240
void* __stdcall FUN_00b3d3e0(int, int, int, int, int, int);    // 0x00b3d3e0  (6 dwords)
void* FUN_00b3d4d0(int id, void* buf, int n);                  // 0x00b3d4d0
void* FUN_0067cab0();                                          // 0x0067cab0  cheat manager (edit)
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
class cSPTimer_s00fd_ade0                                     // 0x18 bytes
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
namespace SP
{

class cAppModeSpace_s00fd_ade0
{
public:
    void FUN_00fdade0();                                  // 0x00fdade0
    bool FUN_00fdb330(int a, float f1, float f2);         // 0x00fdb330
    bool Activate();                                      // 0x00fdb710
    void FUN_00fdb9a0();                                  // 0x00fdb9a0
    void TransitionFromCivToSpace(int a, int b);          // 0x00fdba50
    void CompleteTransitionFromEntryToNewGame();          // 0x00fdbc20

    uint8_t   pad000[0x0a8];
    cSPTimer_s00fd_ade0  mTimerA8;                                   // +0x0a8  (entry timer)
    uint8_t   pad0c0[0x50];
    cSPTimer_s00fd_ade0  mSpaceTimer;                                // +0x110 (leave-space timer)
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
using SP::cAppModeSpace_s00fd_ade0;
// ---- items of slice s00fdade0 end

// ---- items of slice s00fdbd60 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef int intptr_t;
#define nullptr 0
struct Vec3 {
    float mX;
    float mY;
    float mZ;
};
class IRefCounted {
public:
    virtual void AddRef();                      // 0x00
    virtual void Release();                     // 0x04
    virtual void v08();
    virtual void* Query(const void* pType);     // 0x0c
    virtual void v10();
};
class cLocalInputState {
public:
    void OnMouseDown(int nButton, int nX, int nY, int nFlags);
    uint8_t mPad00[0x60];
};
class cSPUISpace : public IRefCounted {
public:
    void ToggleStarmapFilters(bool bShow);
};
class cSPModeStrategy : public IRefCounted {
public:
    virtual void Slot14();
    virtual void Slot18();
    virtual void Slot1c();
    virtual void Slot20();
    virtual void Slot24();
    virtual void Slot28();

    uint8_t mPad1c[0x04];               // 0x1c
    cSPUISpace* mpUISpace;              // 0x20
    uint8_t mPad24[0x08];               // 0x24
    void* mpPlanetView;                 // 0x2c
};
class cGonzagoSubsystemPart {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
};
class cGonzagoSubsystem : public cGonzagoSubsystemPart {
public:
    ~cGonzagoSubsystem();
    uint8_t mPad14[0x54];               // 0x14
};
class cIModeStrategy : public IRefCounted {
public:
    uint8_t mPad14[0x04];               // 0x14
};
class cIHandler : public IRefCounted {
public:
    uint8_t mPad14[0x04];               // 0x14
};
class cAppModeSpace_s00fd_bd60 : public cIModeStrategy, public cGonzagoSubsystem, public cIHandler {
public:
    cAppModeSpace_s00fd_bd60();
    ~cAppModeSpace_s00fd_bd60();

    void InitSpaceGame();
    void EnterSpaceGame();
    void ShutdownSPG();
    void LoadNewGamePlanet();  // 0x00fdc240 (cAppModeSpace::LoadNewGamePlanet)
    void TransitionFromLoadToPlanet();
    void TransitionFromEditorToPlanet();
    void TransitionToEntry();
    void PlanetOnMouseDown();
    void StopEditorPlay();
    bool OnMouseDown(int nButton, int nX, int nY, int nFlags);

    void* mpStarMap;                    // 0x68
    void* mpUniverse;                   // 0x6c
    void* mpTerrain;                    // 0x70
    void* mpPlanetKeyData;              // 0x74
    int   mnPlanetContext;              // 0x78
    void* mpGonzagoWorld;               // 0x7c
    void* mpPlanetView;                 // 0x80
    void* mpStrategy;                   // 0x84
    uint8_t mbInitialized;              // 0x88
    uint8_t mPad89[0x03];               // 0x89
    uint8_t mPad8c[0x3c];               // 0x8c
    cLocalInputState mLocalInput;       // 0xc8
    int   mnDragStartX;                 // 0x128
    int   mnDragStartY;                 // 0x12c
    int   mnDragKind;                   // 0x130
    void* mpEmpire;                     // 0x134
    void* mpPlayer;                     // 0x138
    int   mnPlayerId;                   // 0x13c
    void* mpGonzagoAsset;               // 0x140
    uint8_t mPad144[0x14];              // 0x144
    uint8_t mbSpaceGameActive;          // 0x158
    uint8_t mPad159[0x03];              // 0x159
    cSPModeStrategy* mpGameMode;        // 0x15c
    void* mpHandler;                    // 0x160
    void* mpUISpace;                    // 0x164
    int   mnOldGameMode;                // 0x168
    void* mpEditor;                     // 0x16c
    uint8_t mPad170[0x1c];              // 0x170
    uint8_t mbEditorPlaying;            // 0x18c
    uint8_t mbFlag18d;                  // 0x18d
    uint8_t mbFlag18e;                  // 0x18e
    uint8_t mbFlag18f;                  // 0x18f
    uint8_t mbFlag190;                  // 0x190
    uint8_t mbFlag191;                  // 0x191
    uint8_t mbFlag192;                  // 0x192
    uint8_t mPad193;                    // 0x193
    void* mpListHead;                   // 0x194
};
class cGameNounManager {
public:
    void* GetAvatar(void* pTarget);
};
class cSPSimulatorPlayerUFO {
public:
    void* GetStarRecordUnderMouse();
    void InitForPlanet();
};
class cSPSimulatorSpaceGame {
public:
    void* GetPlayerInventory();
};
class cPlanetModel {
public:
    uint32_t GetPlanetKey();
};
class cStarMap {
public:
    void Init();
};
class cEffectsManager {
public:
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
    virtual void v34();
    virtual void v38();
    virtual void v3c();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4c();
    virtual void v50();
    virtual void v54();
    virtual void v58();
    virtual void v5c();
    virtual void v60();
    virtual void v64();
    virtual void v68();
    virtual void v6c();
    virtual void v70();
    virtual void v74();
    virtual void v78();
    virtual void v7c();
    virtual void v80();
    virtual void v84();
    virtual void v88();
    virtual void v8c();
    virtual void v90();
    virtual void v94();
    virtual void v98();
};
class cController {
public:
    void AwardAchievement(uint32_t nAchievement);
};
class cPropertyList {
public:
    virtual void v00();
    virtual void Release();
};
class cInventory {
public:
    virtual void v00();
    virtual void v04();
    virtual bool AddItem(void* pItem);
};
cEffectsManager* EffectsManager();
void* GonzagoModelWorld();
void ResetSpaceEffects();
void* StarMapManager();
void* NounManager();
void* GetTerrainSphere();
void* GetTerrainEditor();
void* AppTimer();
void SetGameMode(uint32_t nMode);
void SetTimeScale(uint32_t fScaleBits);
void SetGameSpeed(uint32_t nSpeed);
void SetPaused(bool bPaused);
void* SpaceGameGet();
void* MissionActive();
void LoadMissionTuning(uint32_t nKey);
void UnloadMissionTuning();
void RefreshSpaceUI();
void* GetPlayerInventory();
float GetMissionScore();
void SetUniverseView(int nView);
void InitializeUniverseContext(void* pContext);
void ResetUIState();
void ClearSelection(int nId);
void SelectModeSlot(int nSlot);
void ApplyNounChanges();
void* GetPlayerEmpire(void** ppEmpire);
void* LivingUniverseEmpire();
bool IsSpaceGameActive();
void GetEmpireItems(void* pEmpire, void** ppItems);
void* AchievementUnlocked(uint32_t nKey);
void* ControllerFromKey(uint32_t nKey);
bool ReadPropertyKey(void* pList, uint32_t nKey, void** ppOut);
void ShowItemPopup(void* pItem);
void ShutdownSpaceGame();
void ReleaseModeStrategy();
void ResetStarMap();
void ClearSpaceUI();
void UnregisterGameHandler();
void SetCursorMode(int nMode);
void ResetGridHighlight();
bool HandleMouseDown(int nButton, int nX, int nY, int nFlags);
void RefreshInputState();
bool IsDraggingNoun();
bool IsStarmapDragging();
void SelectStarRecord(void* pRecord);
void* GetPlayerController(void* pAvatar);
void AttachCamera(void* pCamera, void* pController);
bool IsCameraAttached(void* pCamera, void* pController);
void AttachSelection(void* pCamera, void* pController);
void ShowPlanetPanel(void* pRecord);
void* GetActivePlanet();
void* PlanetModel();
void* CreatePlanetView(int a, int b);
void SetPlanetViewPlanet(void* pView, int a, int b);
void SetPlanetModelView(int nView);
void EnablePlanetFeatures();
void RefreshPlanetUI();
void EnterPlanetMode();
void SelectSpaceUI();
void InitializePlanetContext();
void InitSelectionState();
extern uint32_t gSpaceModeSlot;
extern uint32_t gEditorModeSlot;
extern cAppModeSpace_s00fd_bd60* gSpaceAppMode;
// ---- items of slice s00fdbd60 end

// ---- items of slice s00fdcd40 begin (TODO(rewrite): local stubs, replace by canonical classes)
void  FUN_00fdb0c0(void* out);                                 // 0x00fdb0c0
void* FUN_00b3d4d0();                                          // 0x00b3d4d0  (default context)
extern char    DAT_013f09b4[];               // 0x013f09b4  "Simulator"
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
void* operator new[](unsigned int n, const char* pName, int flags, unsigned debugFlags, const char* file, int line);  // 0x00f473a0
struct B91 : B90 { virtual void a91() {} };
struct V0ci  : B02 { virtual void  Reset(int v) = 0; };                        // +0x0c (1 int)
struct V98   : B37 { virtual void  SetFx(int a, int b) = 0; };                 // +0x98
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
struct cPropVal { uint16_t pad0[9]; uint16_t mKind; };                         // +0x12 property tag
struct cRefObj  { void* vftable; uint32_t m04; uint32_t pad08[14]; int mRef40; };  // ref-counted wrapper
struct cCandidate { uint32_t pad0[79]; void* p13c; };                          // +0x13c picked handle
struct cHostHdr { uint32_t pad0[2]; };                                         // object embedding the mode at +0x08
struct cUnitSlot { uint32_t pad00[0x40 / 4]; void* p40; };                     // +0x40 resident entity
struct cHolder { uint32_t pad00[0xc4 / 4]; void* pC4; };                       // +0xc4 resident entity
struct cD0     { uint32_t pad0[52]; uint32_t mD0; };                           // host +0xd0 state
struct c154    { uint32_t pad0[8];  void*    p20; };                           // +0x20 sub-object
struct cSimObj { uint32_t pad0[10]; uint8_t  mObj28; };                        // vtable object at +0x28
struct cSimPtr { uint32_t pad0[10]; void*    p28; };                           // pointer at +0x28
struct cM44    { uint32_t pad0[17]; uint32_t m44; };                           // +0x44 flag
struct c24     { uint32_t pad0[9];  void* p24; uint32_t pad28[1]; void* p2c; };  // effect roots
struct c28     { uint32_t pad0[33]; void* p84; };                              // +0x84 sub-object
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
union cFloPtr { float f; void* p; };
void* FUN_0067de20();                                          // 0x0067de20  cheat manager (install)
void* FUN_00b3d300();                                          // 0x00b3d300  (default noun manager)
void* FUN_00b3d360();                                          // 0x00b3d360
void* FUN_00b3d3d0();                                          // 0x00b3d3d0
void* FUN_00b3d230(int id);                                    // 0x00b3d230
void* FUN_0067dcc0();                                          // 0x0067dcc0  localization manager
void* FUN_0067de30();                                          // 0x0067de30  cheat manager (query)
void* FUN_00675250(int a, int b);                              // 0x00675250
float* FUN_0041ea70();                                         // 0x0041ea70  property float accessor
uint8_t* FUN_0041e920();                                       // 0x0041e920  property bool accessor
void* FUN_01021230();                                          // 0x01021230  GetNounManager
void  FUN_01022510(void* vec);                                 // 0x01022510  sort(vector)
void  FUN_00bdaa40(void** cursorRef, void* first, void* last, void* init, void* extra);  // 0x00bdaa40
void* FUN_010219b0(void* a, void* b);                          // 0x010219b0
void* __stdcall FUN_01046fc0(int a);                           // 0x01046fc0
bool  FUN_00c8bb00(void* a);                                   // 0x00c8bb00
void* FUN_00ac86d0(int a);                                     // 0x00ac86d0
void* FUN_0105c3d0(void* a, void* b, float f);                 // 0x0105c3d0
void* FUN_00b3d280();                                          // 0x00b3d280
void* __stdcall FUN_01002bd0ii(int a, int b);                  // 0x01002bd0  (2 args)
void** FUN_00fdb230(void** out, uint32_t* begin, uint32_t* end, const uint32_t* key);  // 0x00fdb230
void  FUN_00571db0(void* a, void* b, void* c, void* d, void* e);  // 0x00571db0
void* FUN_00fdd200();                                          // 0x00fdd200
struct cSelf_s00fd_cd40
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
class cSPTimer_s00fd_cd40                                     // 0x18 bytes
{
public:
    uint32_t lo;                                   // +0x00
    uint32_t hi;                                   // +0x04
    uint32_t lo2;                                  // +0x08
    uint32_t hi2;                                  // +0x0c
    uint32_t pad[2];                               // +0x10
};
namespace SP
{

class cAppModeSpace_s00fd_cd40
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
    cSPTimer_s00fd_cd40  mTimerA8;                                   // +0x0a8  (entry timer)
    uint8_t   pad0c0[0x50];
    cSPTimer_s00fd_cd40  mSpaceTimer;                                // +0x110 (leave-space timer)
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
using SP::cAppModeSpace_s00fd_cd40;
// ---- items of slice s00fdcd40 end

// ---- items of slice s00fdf9f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* FUN_00b3d310();                                               // 0x00b3d310
extern "C" void* FUN_00b3d350();                                               // 0x00b3d350 PlanetModel
extern "C" void* FUN_00b3d430();                                               // 0x00b3d430 TerraformingManager
extern "C" void* FUN_00b25fb0();                                               // 0x00b25fb0 GetPlayerCivilization
extern "C" void  FUN_00b515e0();                                               // 0x00b515e0
extern "C" void  FUN_00b87bb0();                                               // 0x00b87bb0
extern "C" void  FUN_00b88420(...);                                            // 0x00b88420
extern "C" void  FUN_00b8d750(...);                                            // 0x00b8d750
extern "C" void  FUN_00b8de30(...);                                            // 0x00b8de30
extern "C" void  FUN_010219b0(...);                                            // 0x010219b0
extern "C" void  FUN_01066d60(...);                                            // 0x01066d60
extern "C" void* FUN_00c713c0();                                               // 0x00c713c0
extern "C" void* FUN_00a1c4e0(void*);                                          // 0x00a1c4e0
extern "C" void  FUN_00ff3540();                                               // 0x00ff3540
extern "C" void  FUN_00ff0940();                                               // 0x00ff0940
extern "C" void  FUN_00ffd390(...);                                            // 0x00ffd390
extern "C" void  FUN_01003690();                                               // 0x01003690
extern "C" void* FUN_00b21080();                                               // 0x00b21080
extern "C" void* FUN_00b236c0();                                               // 0x00b236c0
extern "C" void* FUN_00cd7d10();                                               // 0x00cd7d10
extern "C" void* FUN_00d3d420();                                               // 0x00d3d420
extern "C" void* FUN_00acdff0();                                               // 0x00acdff0
extern "C" void* FUN_00ae5ea0();                                               // 0x00ae5ea0
extern "C" void* FUN_00b1e500();                                               // 0x00b1e500
extern "C" void  FUN_0102f660_hook(void*);                                     // 0x0102f660
extern "C" void  FUN_00c75770_hook();                                          // 0x00c75770
typedef unsigned int   u32;
typedef int            i32;
typedef float          f32;
struct Vec3_s00fd_f9f0 { f32 x, y, z; };
namespace SP {
 class cAppModeSpace_s00fd_f9f0; 
}
class cTerraformingManager;
class cGameNounManager_s00fd_f9f0;
extern f32  DAT_013ec4d0;              // 0x013ec4d0  planet-grid scale
extern u8   DAT_018c43e8;              // 0x018c43e8
extern "C" void* FUN_00f473a0(u32 size, const char* tag, int a, int b, int c, int d); // 0x00f473a0 operator_new
extern "C" i32   FUN_01021230_s00fd_f9f0();                                               // 0x01021230
extern "C" void  FUN_00fdc340(Vec3_s00fd_f9f0 const* v, f32 scale);                       // 0x00fdc340 UpdateSpaceGrid
extern "C" void* FUN_00fdb280(void* begin, Vec3_s00fd_f9f0 const* v, u32 flags);          // 0x00fdb280
extern "C" void* FUN_00c713e0(u32);                                            // 0x00c713e0
extern "C" void  FUN_00c73b60(u32);                                            // 0x00c73b60
extern "C" void* FUN_00c71030(u32);                                            // 0x00c71030
extern "C" i32   FUN_00c710c0();                                               // 0x00c710c0
extern "C" i32   FUN_00c6ffc0(u32);                                            // 0x00c6ffc0
extern "C" i32   FUN_00c70bf0(u32);                                            // 0x00c70bf0
extern "C" i32   FUN_00c6ffa0();                                               // 0x00c6ffa0
extern "C" i32   FUN_00c73cf0(u32);                                            // 0x00c73cf0
extern "C" i32   FUN_00c73ff0(void*);                                          // 0x00c73ff0
extern "C" i32   FUN_00c74280(void*);                                          // 0x00c74280
extern "C" i32   FUN_00c70e00();                                               // 0x00c70e00
extern "C" i32   FUN_00fda750(void*);                                          // 0x00fda750
extern "C" u32   FUN_00b1e700();                                               // 0x00b1e700
extern "C" void  FUN_00fdba50(SP::cAppModeSpace_s00fd_f9f0*, i32, i32);                   // 0x00fdba50
class cRefObj_s00fd_f9f0 {
public:
    virtual void v00();                  // +0x00
    virtual void v04();                  // +0x04  AddRef
    virtual void v08();                  // +0x08  Release
};
class cResultObj {
public:
    virtual void r00();                  // +0x00
    virtual void r04();                  // +0x04
};
class cGridQuery {
public:
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void s20();
    virtual void s24();
    virtual void s28();
    virtual Vec3_s00fd_f9f0* s2c();                 // +0x2c  current position
};
class cGridQuery2 {
public:
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void s20();
    virtual void s24();
    virtual void s28();
    virtual Vec3_s00fd_f9f0* s2c();                 // +0x2c  current position
};
class cSpaceObj {
public:
    u8         mPad_000[0x120];
    cGridQuery mSub_120;                 // +0x120
};
class cSPSimPlanetHighLOD : public cRefObj_s00fd_f9f0 {
public:
    cSPSimPlanetHighLOD* FUN_00ff8970(); // 0x00ff8970 (build / install vtable)
    void ActivatePlanet(void* planet);   // 0x00ff9800
};
class cSimGame {
public:
    void FUN_01005130();                 // 0x01005130
    u8   mPad_000[0x54];
    cSPSimPlanetHighLOD* mp_54;          // +0x54
};
class cGameNounManager_s00fd_f9f0 {
public:
    void* FUN_00b21340(void* a, void* b, void* c, void* d, void* e);  // 0x00b21340 GetGameDataVector
};
struct cDataVec {
    u32    mUnk_00;                      // +0x00
    void** mpBegin;                      // +0x04
    void** mpEnd;                        // +0x08
};
class cPlayerInventory_s00fd_f9f0 {
public:
    u8          mPad_000[0x34];
    cGridQuery2 mSub_34;                 // +0x34
};
class cSPSimulatorSpaceGame_s00fd_f9f0 {
public:
    cPlayerInventory_s00fd_f9f0* GetPlayerInventory();   // 0x00a1ad60
};
class cTerraformingManager {
public:
    void FUN_00bbe740(void* planet);     // 0x00bbe740
    void FUN_00bc1450(void* planet);     // 0x00bc1450
};
namespace SP
{
class cAppModeSpace_s00fd_f9f0 {
public:
    void  FUN_00fdf9f0();
    void* FUN_00fdfb10();
    void  HandleMessage();  // 0x00fdfbc0 (cAppModeSpace::HandleMessage)
    void  FUN_00fe0160();

    u8        mPad_000[0x24];
    u8        mb_24;                     // +0x24 transition-data initialised flag
    u8        mPad_025[0x15c - 0x25];
    cSimGame* mp_15c;                    // +0x15c
};
} // namespace SP
using SP::cAppModeSpace_s00fd_f9f0;
// ---- items of slice s00fdf9f0 end

// ---- items of slice s00fe1a20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char g_vecBuf[2];     // 0x1667bac
extern bool g_falseConst;    // 0x13ec47c
struct BoolVec {
    char* b;
    char* e;
    char* cap;
    void __thiscall Construct(const bool* v);   // 0x57cc10
    void Destroy() { if (cap - b > 1 && b) operator_delete__(b); }
};
void __cdecl BoolVec_DoInsertValue(void* pos, const void* value, int n);  // 0x11e0744 (vector<bool,fixed_vector_allocator>::DoInsertValue)
struct IGameInputManager {
    virtual void v0() {}
    virtual void v1() {}
    virtual void v2() {}
    virtual void v3() {}
    virtual void SetTriggerConfig(const char* name, int a, int b) = 0;  // +0x10
    virtual void v5() {}
    virtual void v6() {}
    virtual void v7() {}
    virtual void InstallStateMachine(void* sm, int a, int b) = 0;       // +0x20
};
struct ILocale {
    virtual void v0() {}
    virtual void v1() {}
    virtual void v2() {}
    virtual void v3() {}
    virtual void v4() {}
    virtual const void* GetLanguage() = 0;   // +0x14
};
IGameInputManager* __cdecl GameInputManager();   // 0xb3d250
ILocale* __cdecl GetLocaleManager();             // 0x67de40
bool __cdecl LanguageEquals(const void* str, const wchar_t* lit);  // 0x6ab760 (basic_string == wchar_t*)
void __cdecl DeclareMenuCommands();              // 0xd08930 (cCommunityEditor)
struct StateMachineBuilder {
    void __thiscall Init(void* tree);                       // 0xb198d0
    void __thiscall AddStateName(int idx, const char* s);   // 0xb1c080
    void __thiscall SetMachineName(const char* s);          // 0xb1b410
    void __thiscall AddTransition(int, int, int, int, unsigned, int, unsigned, int, int, int, BoolVec*, int); // 0xb1c8d0
};
struct CommandBase {
    void __thiscall Destroy();                // 0x83c750 EA::ArgScript::cCommandBase::~cCommandBase
};
struct NodeTree {
    void __thiscall Destroy(uint32_t root);   // 0xe4b990
};
struct BuilderCleanup {
    void __thiscall Destroy(uint32_t x);      // 0xb1b830
};
// ---- items of slice s00fe1a20 end

// ---- items of slice s00fe2ec0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;
struct Vector3_s00fe_2ec0 { float x, y, z; Vector3_s00fe_2ec0() {} };
struct Matrix3 { float m[9]; Matrix3() {} };
struct Transform {
    uint16 mnFlags;
    uint16 mnTransformCount;
    Vector3_s00fe_2ec0 mOffset;
    float mfScale;
    Matrix3 mRotation;
    Transform();
    void SetOffset(const Vector3_s00fe_2ec0& v) { mnFlags |= 4; mnTransformCount++; mOffset = v; }
    void SetRotation(const Matrix3& m) { mRotation = m; mnFlags |= 2; mnTransformCount++; }
};
namespace SP {
Vector3_s00fe_2ec0 normalized_safe(const Vector3_s00fe_2ec0& v);
}
namespace SP {
Vector3_s00fe_2ec0 OrthogonalVector(const Vector3_s00fe_2ec0& v);
}
namespace SP {
Matrix3 Matrix3FromFacingAndUp(const Vector3_s00fe_2ec0& facing, const Vector3_s00fe_2ec0& up);
}
struct ResKey {
    uint32 a, b, c;
    ResKey() : a(0), b(0), c(0) {}
};
struct SpaceMsg {
    uint32 pad0[2];
    uint32 p8;
    uint32 pad1;
    uint32 p10;
    uint32 pad2;
    uint32 p18;
};
struct KeyTriple {
    uint32 a, b, c;
    KeyTriple() {}
    KeyTriple(uint32 x, uint32 y, uint32 z) : a(x), b(y), c(z) {}
};
struct cGameDataVt {
    virtual void v00();
    virtual void v04();
    virtual cGameDataVt* GetSelf();        // +8
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
    virtual uint32 GetID();                 // +0x2c
};
struct cCombatantLike : cGameDataVt {};
struct cCombatant_s00fe_2ec0 : cCombatantLike {
    int GetDamageState();                   // 0x8e7f80
};
struct Ivfn58 {
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
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
    virtual bool IsDestroyed();             // +0x58
};
struct cCommunity_s00fe_2ec0 {
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
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
    virtual uint32 GetOwnerID();            // +0x4c
    char pad[0x11c];
    Ivfn58 m120;                            // +0x120
    void Reaction();                        // 0xbdbf10
};
struct cBuildingLike {
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
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
virtual void v70();
virtual void v74();
virtual void v78();
virtual void v7c();
    virtual void v80();
    virtual cCommunity_s00fe_2ec0* GetCommunity();     // +0x84
};
struct cCreatureLike {
    cCommunity_s00fe_2ec0* GetCommunity();             // 0xbce5c0
};
struct cEnemyLike {
    char pad[0x714];
    int mState;                             // +0x714
};
struct cInvSub34 {
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
    virtual Vector3_s00fe_2ec0* GetDestination();      // +0x2c
};
struct cInvBase0 {
    virtual void v00();
    char pad04[0x30];
    cInvSub34 m34;                          // +0x34
    char pad38[0x508 - 0x38];
};
struct cPlayerInventory_s00fe_2ec0 : cInvBase0, cCombatantLike {};
struct cSpaceSim_s00fe_2ec0 {
    cPlayerInventory_s00fe_2ec0* GetPlayerInventory(); // 0xa1ad60
    void SetPlanetDestination(Vector3_s00fe_2ec0* pos, int a, int b, int c, int d); // 0xffc350
    void OnWarp();                          // 0xffc030
};
struct cEmpire_s00fe_2ec0 {
    char pad[0x84];
    uint32 mPoliticalID;                    // +0x84
    bool IsDestroyed();                     // 0xc30910
    void Fn930();                           // 0xc30930
    void Fn9b0(int);                        // 0xc309b0
    bool HasContact();                      // 0xc31c60
    bool IsAlly();                          // 0xc308b0
    struct cPlanetRecord_s00fe_2ec0* GetHomePlanet();  // 0xc31730
    void SetSpecies(void* profile);         // 0xc33690
};
struct cPlanetRecord_s00fe_2ec0 {
    void* GetCommContext();                 // 0xce6950
};
struct cPlanet_s00fe_2ec0 {
    char pad[0x13c];
    cPlanetRecord_s00fe_2ec0* mRecord;                 // +0x13c
    cEmpire_s00fe_2ec0* GetOwner();                    // 0xc71e30
    void Fn430(int, int);                   // 0xc71430
};
struct cTerrainSphere_s00fe_2ec0 {
    void PlayMusic(uint32 id);              // 0xc77bf0
    bool HasMusic(uint32 id);               // 0xc772c0
};
struct cNounManager {
    cTerrainSphere_s00fe_2ec0* GetCurrentTerrainSphere(); // 0xf67d90
    void* GetFn2c0();                       // 0xace2c0
};
struct cRelationshipManager_s00fe_2ec0 {
    bool IsAtWar(cEmpire_s00fe_2ec0* e, int b);        // 0xd01ff0
    float GetEvent(uint32 a, uint32 b, uint32 ev); // 0xd01b80
    float RecordEvent(uint32 a, uint32 b, uint32 ev, float f); // 0xd06240
};
struct cEventLog {
    void PostFeedbackEvent(uint32 a, uint32 b, int c, int d, int e, int f); // 0xdd8640
};
struct cTribeLike {
    void Fn5430(int, int);                  // 0xfe5430
};
struct cGameNounManager_s00fe_2ec0 {
    char pad[0x50];
    uint32 mbFlag0 : 1;                     // +0x50 bitfield
    uint32 mbSpaceMission : 1;
    uint32 mbFlag2 : 1;
    uint32 mbFlag3 : 1;
    uint32 mbTutorialMission : 1;
    cTribeLike* GetPlayerTribe();           // 0xbfc5f0
    void Fn3480();                          // 0x1003480
};
struct cSpeciesManager {
    void* GetProfile(const KeyTriple& key); // 0x4df550
};
struct IMessageServer {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
    virtual void PostMSG(uint32 id, int a, int b, int c); // +0x18
};
struct IGameInputManager_s00fe_2ec0 {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
    virtual void Reset();                   // +0x1c
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
    virtual void v30();
    virtual int GetMode();                  // +0x34
    virtual void SetMode(int m);            // +0x38
};
struct IPosSource {
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
virtual void v34();
virtual void v38();
virtual void v3c();
    virtual void GetPosition(Vector3_s00fe_2ec0& out, int a, cCombatantLike* who); // +0x40
};
struct IVisualEffect {
    virtual void v00();
    virtual int Release();                  // +4
    virtual void Start(int);                // +8
virtual void v0c();
virtual void v10();
virtual void v14();
    virtual void SetTransform(const Transform& t); // +0x18
};
template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    T** AsPPTypeParam();                    // 0xa16f40
};
struct IEffectsManager {
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
    virtual bool CreateVisualEffect(uint32 id, int flags, IVisualEffect** out); // +0x2c
};
struct cCameraController {
    void Fn270(int);                        // 0x1017270
};
struct ICameraManager {
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
virtual void v34();
    virtual void* GetActiveCameraController(); // +0x38
};
struct IApp {
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
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
    virtual ICameraManager* GetCameraManager(); // +0x50
};
struct IConfigManager {
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
    virtual void* GetPropertyList(uint32 id); // +0x30
};
struct cA98 { bool IsBusy(); };            // 0xa98020
struct cDD4 { void Fn(); };                 // 0xadda70
struct cGameTimeManager { char pad[0x48]; uint8 mFlags; };
struct cUniverseContext;
struct cWarSystem { void Update(); };       // 0x100d9f0
extern cWarSystem* g_WarSystem;             // 0x16dc798
namespace SP {
cSpaceSim_s00fe_2ec0* GetUFOSimulator();               // 0xffbe50
}
namespace SP {
void* GetCurrentGameMode();                 // 0xb5b800
}
namespace SP {
IGameInputManager_s00fe_2ec0* GameInputManager_s00fe_2ec0();      // 0xb3d250
}
namespace SP {
IPosSource* PosSource();                    // 0xb3d240
}
namespace SP {
cRelationshipManager_s00fe_2ec0* RelationshipManager();// 0xb3d2c0
}
namespace SP {
cNounManager* NounManager_s00fe_2ec0();                // 0xb3d300
}
namespace SP {
cEventLog* EventLog();                      // 0xb3d3e0
}
namespace SP {
cGameTimeManager* GameTimeManager();        // 0xb3d380
}
namespace SP {
cDD4* Fn4d0();                              // 0xb3d4d0
}
namespace SP {
IMessageServer* MessageServer();            // 0x67dcc0
}
namespace SP {
IEffectsManager* EffectsManager_s00fe_2ec0();          // 0x67ddd0
}
namespace SP {
IApp* App();                                // 0x67dd10
}
namespace SP {
IConfigManager* ConfigManager();            // 0x67dd30
}
namespace SP {
cSpeciesManager* SpeciesManager();          // 0x401090
}
namespace SP {
cA98* Fn5df0();                             // 0x1015df0
}
namespace SP {
cPlanet_s00fe_2ec0* GetActivePlanet_s00fe_2ec0();                 // 0x1021260
}
namespace SP {
cPlanetRecord_s00fe_2ec0* GetActivePlanetRecord();     // 0x10212a0
}
namespace SP {
cEmpire_s00fe_2ec0* GetPlayerEmpire();                 // 0x1021300
}
namespace SP {
uint32 GetPlayerEmpireID();                 // 0x1021090
}
namespace SP {
cPlanetRecord_s00fe_2ec0* GetPlayerHomePlanet();       // 0x1021370
}
namespace SP {
cUniverseContext* GetUniverseContext();     // 0x1021080
}
namespace SP {
cCreatureLike* AsCreature(cCombatant_s00fe_2ec0* c);   // 0xbcd430
}
namespace SP {
cBuildingLike* AsBuilding(cCombatant_s00fe_2ec0* c);   // 0xc5b430
}
namespace SP {
cEnemyLike* AsEnemy(cCombatant_s00fe_2ec0* c);         // 0xae3370
}
namespace SP {
bool IsBlockadeOwner(cPlanet_s00fe_2ec0* p);           // 0x102c600
}
namespace SP {
bool CheckEnemyDeath(cEnemyLike* e, cPlayerInventory_s00fe_2ec0* inv, int b); // 0x102aa50
}
namespace SP {
cCommunity_s00fe_2ec0* FindCommunity(void* a, uint32 id); // 0xac9dd0
}
namespace SP {
void DoCommunityReaction(cCommunity_s00fe_2ec0* c, float f, uint32 id); // 0xff5270
}
namespace SP {
void* GetCreatureFromStimulus(uint32 s);    // 0xc032a0
}
namespace SP {
void ScanBuilding(void* c);                 // 0x1058680
}
namespace SP {
struct cScannable { KeyTriple GetKey(); }; // 0xc3e1e0
}
namespace SP {
cScannable* FindScannable(uint32 s);        // 0xfd9e60
}
namespace SP {
void ScanObject(const KeyTriple& key);               // 0x10534c0
}
namespace SP {
void EndBanMode(int);                       // 0xdd1840
}
namespace SP {
void ToggleBanningContent(int);             // 0xdd17f0
}
namespace SP {
void EndPlanetMode(int);                    // 0xe09a50
}
namespace SP {
void StartPlanetMode(int);                  // 0xe099d0
}
namespace SP {
void CommEvent(uint32 id, cEmpire_s00fe_2ec0* e, const ResKey& a, const ResKey& b, void* ctx, int c, const ResKey& d, const ResKey& f); // 0xe39ab0
}
namespace SP {
cCameraController* AsPlanetCamera(void* c); // 0xc37590
}
uint32 SPIDFromName(const char* name);      // 0x571cf0
void SetGlobalProperty(uint32 id, float f); // 0x5ca880
namespace EA {
class Stopwatch_s00fe_2ec0 { public:
    uint64 mnStartTime;
    uint64 mnTotalElapsedTime;
    uint32 mnUnits;
    float mfCoefficient;
    void Restart();                         // 0x571e80
    uint64 GetElapsedTime() const;          // 0x93a5e0
    void Reset() { mnStartTime = 0; mnTotalElapsedTime = 0; }
};
}
struct ListNode { ListNode* mpNext; ListNode* mpPrev; };
struct ListIter {
    ListNode* mpNode;
    ListIter(ListNode* p) : mpNode(p) {}
    ListIter(const ListIter& x) : mpNode(x.mpNode) {}
};
struct KeyList {
    ListNode mNode;
    ListIter begin() { return ListIter(mNode.mpNext); }
    ListIter end() { return ListIter(&mNode); }
    bool empty() const { return mNode.mpNext == &mNode; }
    ListIter erase(ListIter it);            // 0xfdc4b0
};
ListIter FindKey(ListIter first, ListIter last, const KeyTriple& value); // 0xfdb230
struct cIModeStrategy_s00fe_2ec0 { virtual void ms00(); };
struct IHandler_s00fe_2ec0 { virtual bool HandleMessage(uint32 messageID, void* msg); };
namespace SP {
class cAppModeSpace_s00fe_2ec0 : public cIModeStrategy_s00fe_2ec0, public IHandler_s00fe_2ec0 {
public:
    virtual bool HandleMessage(uint32 messageID, void* msg);  // 0x00fdfbc0 (SP::cAppModeSpace::HandleMessage)
    void OnNewGame();                       // 0xfd9d30
    void OnLoadGame();                      // 0xfd9d90
    void Fn9de0();                          // 0xfd9de0
    void Fnabf0();                          // 0xfdabf0
    void Fnade0();                          // 0xfdade0
    void SetDefaultPickPriority();          // 0xfddba0
    void Fndfa0();                          // 0xfddfa0
    void HandleMessage2();                  // 0xfdfbc0
    void LoadStateMachine(void* props);     // 0xfe1a20

    char pad08[0x110 - 0x8];
    EA::Stopwatch_s00fe_2ec0 mWarpTimer;               // +0x110
    char pad128[0x15c - 0x128];
    cGameNounManager_s00fe_2ec0* mpGameNounManager;    // +0x15c
    char pad160[0x16a - 0x160];
    bool mbMissionsDone;                    // +0x16a
    char pad16b[0x170 - 0x16b];
    KeyList mMissions;                      // +0x170
    char pad178[0x18c - 0x178];
    bool mbPendingPlanet;                   // +0x18c
};
}
// ---- items of slice s00fe2ec0 end

// @ 0x00fd9c90
void AppMode::f9c90(int a)
{
    (void)a;
    char c = (char)(int)FUN_00b2f740();
    void* wm = FUN_0067caa0();
    int iv = ((int(__thiscall*)(void*))VTP(wm)[0x84 / 4])(wm);
    char flag = iv != 0;
    char c2 = (char)(int)FUN_00805180();
    if (c2 && !c && !flag) return;
    void* gi = FUN_00b3d250();
    ((void(__thiscall*)(void*, int))VTP(gi)[0x48 / 4])(gi, a);
}

// @ 0x00fd9ce0
char AppMode::f9ce0(int a, int b)
{
    (void)a; (void)b;
    unsigned u = (unsigned)FUN_01021080();
    if (u <= 2u) {
        void* gi = FUN_00b3d250();
        return ((char(__thiscall*)(void*, int, int))VTP(gi)[0x50 / 4])(gi, a, b);
    }
    return 0;
}

// @ 0x00fd9d00
int AppMode::f9d00()
{
    void* gi = FUN_00b3d250();
    int r = ((int(__thiscall*)(void*))VTP(gi)[0x34 / 4])(gi);
    if (r == 1) return 1;
    gi = FUN_00b3d250();
    r = ((int(__thiscall*)(void*))VTP(gi)[0x34 / 4])(gi);
    if (r == 2) return 1;
    return 0;
}

// @ 0x00fd9d30
void AppMode::f9d30()
{
    void* gm = FUN_00b5b800();
    if (gm != &DAT_01654c05) return;
    int u = FUN_01021080();
    if (u == 1) {
        void* star = (void*)FUN_01021230(0);
        void* ss = (void*)E(star)->FUN_00c8b770();
        E(ss)->FUN_00c86c70();
        void* rm = FUN_00b3d2c0();
        E(rm)->FUN_00d06400();
        return;
    }
    u = FUN_01021080();
    if (u == 2) FUN_010213b0(-1);
    void* rm = FUN_00b3d2c0();
    E(rm)->FUN_00d06400();
}

// @ 0x00fd9d90
void AppMode::f9d90()
{
    void* gm = FUN_00b5b800();
    if (gm != &DAT_01654c05) return;
    int u = FUN_01021080();
    if (u == 1) {
        void* star = (void*)FUN_01021230(1);
        void* ss = (void*)E(star)->FUN_00c8b770();
        E(ss)->FUN_00c86c70();
        void* x = (void*)FUN_01021230_0();
        void* y = FUN_00b3d470(x);
        E(y)->FUN_01034b90();
        return;
    }
    u = FUN_01021080();
    if (u == 2) FUN_010213b0(2);
}

// @ 0x00fd9e80
char f9e80(int a, int* p)
{
    if (*p != 0) {
        void* q = (void*)*p;
        ((void(__thiscall*)(void*, int))VTP((char*)q + 8)[0x1c / 4])((char*)q + 8, a);
    }
    return 1;
}

// @ 0x00fd9f70
namespace SP {
void __thiscall cAppModeSpace::OnMouseUp()
{
}
}  // namespace SP

// @ 0x00fda1f0
namespace SP {
void __thiscall cAppModeSpace::FUN_00fda1f0()
{
}
}  // namespace SP

// @ 0x00fda2e0
namespace SP {
void __thiscall cAppModeSpace::FUN_00fda2e0()
{
}
}  // namespace SP

// @ 0x00fda390
namespace SP {
void __thiscall cAppModeSpace::Deactivate()
{
}
}  // namespace SP

// @ 0x00fda480
namespace SP {
void __thiscall cAppModeSpace::FUN_00fda480()
{
}
}  // namespace SP

// @ 0x00fda4f0
namespace SP {
void __thiscall cAppModeSpace::ShutdownGonzagoSubsystem()
{
    if (mpGonzagoSubsystem)
        mpGonzagoSubsystem->Shutdown(1);
    cGonzagoSubsystem_s00fd_9f70* pSubsystem = mpGonzagoSubsystem;
    if (pSubsystem) {
        mpGonzagoSubsystem = 0;
        pSubsystem->Release();
    }
}
}  // namespace SP

// @ 0x00fda530
namespace SP {
void __thiscall cAppModeSpace::SetPlanetTimeOnFirstEntry()
{
}
}  // namespace SP

// @ 0x00fda5e0
namespace SP {
void __thiscall cAppModeSpace::FUN_00fda5e0()
{
}
}  // namespace SP

// @ 0x00fda750
namespace SP {
void __thiscall cAppModeSpace::FUN_00fda750()
{
}
}  // namespace SP

// @ 0x00fda940
namespace SP {
void __thiscall cAppModeSpace::FUN_00fda940()
{
}
}  // namespace SP

// @ 0x00fda9f0
namespace SP {
void __thiscall cAppModeSpace::FUN_00fda9f0()
{
}
}  // namespace SP

// @ 0x00fdaa90
namespace SP {
void __thiscall cAppModeSpace::Write()
{
}
}  // namespace SP

// @ 0x00fdab40
namespace SP {
void __thiscall cAppModeSpace::FUN_00fdab40()
{
}
}  // namespace SP

// @ 0x00fdabf0
namespace SP {
void __thiscall cAppModeSpace::FUN_00fdabf0()
{
}
}  // namespace SP

// @ 0x00fdade0
void cAppModeSpace_s00fd_ade0::FUN_00fdade0()
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

// @ 0x00fdb330
bool cAppModeSpace_s00fd_ade0::FUN_00fdb330(int a, float f1, float f2)
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

// @ 0x00fdb9a0
void cAppModeSpace_s00fd_ade0::FUN_00fdb9a0()
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
void cAppModeSpace_s00fd_ade0::TransitionFromCivToSpace(int a, int b)
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
void cAppModeSpace_s00fd_ade0::CompleteTransitionFromEntryToNewGame()
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

// @ 0x00fdbd60
void cAppModeSpace_s00fd_bd60::InitSpaceGame()
{
    EffectsManager()->v98();
    ResetSpaceEffects();

    Vec3 bounds;
    bounds.mX = -1500.0f;
    bounds.mY = -1500.0f;
    bounds.mZ = -500.0f;
    Vec3 other;
    other.mX = 1500.0f;
    other.mY = 1500.0f;
    other.mZ = 500.0f;
    (void)other;

    cGonzagoSubsystemPart* pWorld = (cGonzagoSubsystemPart*)GonzagoModelWorld();
    (void)pWorld;

    cStarMap* pStarMap = (cStarMap*)StarMapManager();
    pStarMap->Init();

    mpGameMode->Slot24();

    void* pUniverse = AppTimer();
    InitializeUniverseContext(pUniverse);

    void* pTerrain = GetTerrainSphere();
    void* pEditor = GetTerrainEditor();
    (void)pEditor;

    void* pState = nullptr;
    if (pState == nullptr) {
        void* pSphere = GetTerrainSphere();
        (void)pSphere;
        pState = GetTerrainEditor();
    }

    void* pTimer = AppTimer();
    if (!HandleMouseDown(0, (int)(intptr_t)pState, 0, 0)) {
        SetTimeScale(0x40000000);
        SetGameSpeed(0x40000);
    }

    mbSpaceGameActive = 1;
}

// @ 0x00fdbee0
void cAppModeSpace_s00fd_bd60::EnterSpaceGame()
{
    InitSpaceGame();
    LoadMissionTuning(0x1103192);
    UnloadMissionTuning();

    cSPSimulatorSpaceGame* pSpaceGame = (cSPSimulatorSpaceGame*)SpaceGameGet();
    void* pInventory = pSpaceGame->GetPlayerInventory();
    float fScore = GetMissionScore();
    (void)pInventory;
    (void)fScore;

    void* pMission = MissionActive();
    RefreshSpaceUI();
    (void)pMission;

    cSPUISpace* pSpaceUI = mpGameMode->mpUISpace;
    if (pSpaceUI != nullptr) {
        SetUniverseView(0);
        pSpaceUI->ToggleStarmapFilters(true);
    }
    ResetUIState();
    ClearSelection(-1);
    ClearSelection(2);
    NounManager();
    ApplyNounChanges();
}

// @ 0x00fdbf90
void AwardSpaceAchievements()
{
    void* pEmpire = nullptr;
    GetPlayerEmpire(&pEmpire);

    void* pUniverse = LivingUniverseEmpire();
    if (!IsSpaceGameActive()) {
        if (pEmpire != nullptr)
            ((cPropertyList*)pEmpire)->Release();
        return;
    }
    (void)pUniverse;

    void* pItems = nullptr;
    GetEmpireItems(pEmpire, &pItems);
    if (pItems != nullptr) {
        cPropertyList** ppItem = (cPropertyList**)pItems;
        while (ppItem != nullptr) {
            uint32_t nItemId = 0;
            uint32_t nItemKind = 0;
            GetTerrainSphere();
            (void)nItemId;
            (void)nItemKind;

            cPropertyList* pItem = nullptr;
            void* pPropertyManager = nullptr;
            (void)pPropertyManager;
            if (ReadPropertyKey(pItem, 0xccc6b976u, (void**)&pItem)) {
                uint32_t nKey = (uint32_t)(intptr_t)pItem;
                cController* pController = (cController*)ControllerFromKey(nKey);
                if (!AchievementUnlocked(nKey))
                    pController->AwardAchievement(nKey);

                uint32_t nItemKey = 0;
                if (ReadPropertyKey(pItem, 0x6b1e3e7bu, (void**)&nItemKey)) {
                    cSPSimulatorSpaceGame* pSpaceGame = (cSPSimulatorSpaceGame*)SpaceGameGet();
                    cInventory* pInventory = (cInventory*)pSpaceGame->GetPlayerInventory();
                    if (!pInventory->AddItem(&nItemKey))
                        ShowItemPopup(&nItemKey);
                }
            }
            if (pItem != nullptr)
                pItem->Release();
            ppItem = nullptr;
        }
        if (pItems != nullptr)
            ((cPropertyList*)pItems)->Release();
    }
    if (pEmpire != nullptr)
        ((cPropertyList*)pEmpire)->Release();
}

// @ 0x00fdc150
void cAppModeSpace_s00fd_bd60::ShutdownSPG()
{
    if (mbSpaceGameActive == 0)
        return;

    ShutdownSpaceGame();
    mbSpaceGameActive = 0;

    void* pGonzago = mpGonzagoAsset;
    if (pGonzago != nullptr) {
        mpGonzagoAsset = nullptr;
        ((cPropertyList*)pGonzago)->Release();
    }

    ResetStarMap();
    StarMapManager();
    ResetStarMap();

    void* pHandler = mpHandler;
    if (pHandler != nullptr) {
        mpHandler = nullptr;
        ((cPropertyList*)pHandler)->Release();
    }

    if (mpGameMode != nullptr) {
        ClearSpaceUI();
        cSPModeStrategy* pMode = mpGameMode;
        if (pMode != nullptr) {
            mpGameMode = nullptr;
            pMode->Release();
        }
    }

    SetCursorMode(mnOldGameMode);
    SetCursorMode(0x609b763);
    UnregisterGameHandler();
    ResetGridHighlight();
}

// @ 0x00fdc240
void cAppModeSpace_s00fd_bd60::LoadNewGamePlanet()
{
    InitializePlanetContext();
    void* pPlanet = GetActivePlanet();
    cPlanetModel* pModel = (cPlanetModel*)PlanetModel();

    cPropertyList* pDefinition = nullptr;
    bool bHasDefinition = ReadPropertyKey(pDefinition, 0xe38475d9u, (void**)&pDefinition);
    if (bHasDefinition) {
        void* pView = CreatePlanetView(1, 1);
        pModel = (cPlanetModel*)pView;
        SetPlanetViewPlanet(pView, 1, 1);
        SetPlanetModelView(-9);
        EnablePlanetFeatures();
        RefreshPlanetUI();
        SetPaused(false);
        (void)pModel;
        InitSelectionState();

        if (pDefinition != nullptr) {
            void* pData = nullptr;
            if (ReadPropertyKey(pDefinition, 0xa274d68bu, &pData))
                SelectStarRecord(pData);
        }
        if (pDefinition != nullptr)
            pDefinition->Release();
    } else {
        if (pDefinition != nullptr)
            pDefinition->Release();
    }
    (void)pPlanet;
}

// @ 0x00fdc520
bool cAppModeSpace_s00fd_bd60::OnMouseDown(int nButton, int nX, int nY, int nFlags)
{
    mLocalInput.OnMouseDown(nButton, nX, nY, nFlags);
    bool bHandled = HandleMouseDown(nButton, nX, nY, nFlags);
    RefreshInputState();

    if (IsDraggingNoun())
        return bHandled;

    if (mpGameMode != nullptr && mpGameMode->mpPlanetView != nullptr) {
        if (IsStarmapDragging())
            return bHandled;
    }

    void* pContext = GetActivePlanet();
    if (pContext == nullptr) {
        StopEditorPlay();
        return bHandled;
    }

    if (nButton == 1000) {
        if (mnPlanetContext == 2) {
            cSPSimulatorPlayerUFO* pUFO = (cSPSimulatorPlayerUFO*)SpaceGameGet();
            void* pRecord = pUFO->GetStarRecordUnderMouse();
            if (pRecord != nullptr) {
                cGameNounManager* pNouns = (cGameNounManager*)NounManager();
                void* pAvatar = pNouns->GetAvatar(pRecord);
                SetPaused(false);
                void* pController = GetPlayerController(pAvatar);
                void* pCamera = *(void**)pAvatar;
                AttachCamera(pCamera, pController);
                (void)pCamera;
                if (IsCameraAttached(pCamera, pController)) {
                    AttachSelection(pCamera, pController);
                    return false;
                }
            }
            void* pOther = MissionActive();
            if (pRecord != nullptr && pOther != pRecord) {
                SelectStarRecord(pRecord);
                ShowPlanetPanel(pRecord);
                return true;
            }
        }
    } else if (nButton == 0x3e9 || nButton == 0x3eau) {
        mnDragStartX = nX;
        mnDragStartY = nY;
        SetGameMode(0);
        SelectModeSlot(0);
        SetGameMode(gSpaceModeSlot);
        SelectSpaceUI();
        SetGameMode(gEditorModeSlot);
        EnterPlanetMode();
    }
    return true;
}

// @ 0x00fdcba0
cAppModeSpace_s00fd_bd60::~cAppModeSpace_s00fd_bd60()
{
    gSpaceAppMode = nullptr;

    if (mpGameMode != nullptr) {
        ReleaseModeStrategy();
        mpGameMode->Release();
    }

    void* pNode = mpListHead;
    while (pNode != mpListHead) {
        void* pNext = *(void**)pNode;
        operator_delete__(pNode);
        pNode = pNext;
    }

    if (mpUISpace != nullptr)
        ((cPropertyList*)mpUISpace)->Release();

    if (mpHandler != nullptr)
        ((cPropertyList*)mpHandler)->Release();

    if (mpGameMode != nullptr)
        ((cPropertyList*)mpGameMode)->Release();

    if (mpGonzagoAsset != nullptr)
        ((cPropertyList*)mpGonzagoAsset)->Release();

    if (mpEmpire != nullptr)
        ((cPropertyList*)mpEmpire)->Release();
}

// @ 0x00fdcd40
bool cAppModeSpace_s00fd_cd40::Init(void* arg)
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
        ((cSelf_s00fd_cd40*)cmd)->FUN_0083c800();
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

    ((cSelf_s00fd_cd40*)&mObj144)->FUN_004e0880(9);
    return true;
}

// @ 0x00fdcee0
void cAppModeSpace_s00fd_cd40::PreGameModeTransition(int a1, void* a2)
{
    int msg = (int)(intptr_t)a2;

    if ((int)(intptr_t)((V1c*)this)->Current() == msg)
        return;
    ((V40p*)this)->X40(a2);

    if (a1 != 0x1654c05) {
        if (a1 == 0x1654c10) {
            void* host = DAT_016c7aa4;
            if (host != 0 && ((cD0*)host)->mD0 == 2 && msg == 0x2ccd1d2) {
                ((cSelf_s00fd_cd40*)mpSpace154)->FUN_01003230();
                ((cSelf_s00fd_cd40*)((cHostHdr*)this - 1))->FUN_00fdc980();
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

    ((cSelf_s00fd_cd40*)DAT_015fd918)->FUN_006a17e0m(0x28, 0);

    switch (msg) {
    case 0x1654c06: {
        ((cSelf_s00fd_cd40*)mpSpace154)->FUN_01003070();
        void* e = FUN_00b3d280();
        if (e != 0) {
            ((cSelf_s00fd_cd40*)e)->FUN_00b11870(0x5c1c6351);
            float f = DAT_01428874;
            ((cSelf_s00fd_cd40*)e)->FUN_00b0f720(f, f, f, f, f);
            Vec3Pad v;
            v.tag = 0; v.x = 0.0f; v.y = 0.0f; v.z = 0.0f;
            ((cSelf_s00fd_cd40*)e)->FUN_00b12dd0(&v, &DAT_015b4040, 1);
            ((cSelf_s00fd_cd40*)e)->FUN_00b10340(0.0f, 0.0f, DAT_0142eae0);
            ((cSelf_s00fd_cd40*)e)->FUN_00b10540(0.0f, 0.0f, DAT_0142eae0);
        }
        break;
    }
    case 0xdbdba1: {
        ((cSelf_s00fd_cd40*)mpSpace154)->FUN_01003070();
        void* edi = ((c154*)mpSpace154)->p20;
        if (edi != 0 && ((cSelf_s00fd_cd40*)edi)->FUN_00d09660()) {
            void* g = FUN_01002bd0();
            if (((cSimPtr*)g)->p28 != 0) {
                void* r = ((cUnitSlot*)edi)->p40;
                if (r != 0) {
                    void* t = FUN_00ac86d0((int)(intptr_t)r);
                    if (t != 0) {
                        void* h = ((cSelf_s00fd_cd40*)t)->FUN_00bd9b40();
                        void* g2 = FUN_01002bd0();
                        ((cSelf_s00fd_cd40*)&((cSimObj*)g2)->mObj28)->FUN_00b5f950(h);
                    }
                }
            }
            ((cSelf_s00fd_cd40*)edi)->FUN_00d100b0(1, 1);
        }
        break;
    }
    case -1:
        ((cSelf_s00fd_cd40*)((cHostHdr*)this - 1))->FUN_00fdc9e0();
        break;
    case 0x1654c08:
        ((cSelf_s00fd_cd40*)((cHostHdr*)this - 1))->FUN_00fda9f0();
        ((cSelf_s00fd_cd40*)((cHostHdr*)this - 1))->FUN_00fdc150();
        break;
    case 0x1654c10: {
        ((cSelf_s00fd_cd40*)mpSpace154)->FUN_01003160();
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
        ((cSelf_s00fd_cd40*)((cHostHdr*)this - 1))->FUN_00fdc980();
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
        ((cSelf_s00fd_cd40*)m)->FUN_00b5cde0();
    }
    ((cSelf_s00fd_cd40*)FUN_00b3d360())->FUN_00b7dec0();
    ((V48*)this)->OnEvent();
}

// @ 0x00fdd200
void* FUN_00fdd200()
{
    void* mgr = FUN_01021230();
    if (mgr == 0)
        return 0;

    cContainer* cont = (cContainer*)((cSelf_s00fd_cd40*)mgr)->FUN_00c8b770();

    cPtrVector local;
    ((cSelf_s00fd_cd40*)&local)->FUN_00b93c60((int)(cont->mEnd - cont->mBegin), (void*)&cont->mExtra);

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
        if (((cSelf_s00fd_cd40*)e)->FUN_00c70880() != 0) {
            if (!((cSelf_s00fd_cd40*)((cCandidate*)e)->p13c)->FUN_00b8d970()) {
                if (((cSelf_s00fd_cd40*)e)->FUN_00c70e00() == 5 ||
                    ((cSelf_s00fd_cd40*)e)->FUN_00c70e00() == 4 ||
                    ((cSelf_s00fd_cd40*)e)->FUN_00c70e00() == 2) {
                    best = e;
                    break;
                }
                if (best == 0 || ((cSelf_s00fd_cd40*)e)->FUN_00c70fb0() > ((cSelf_s00fd_cd40*)best)->FUN_00c70fb0())
                    best = e;
            }
        }
        ++it;
    }

    if (best == 0) {
        ((cSelf_s00fd_cd40*)&local)->FUN_00ad92d0();
        return 0;
    }
    void* r = ((cCandidate*)best)->p13c;
    ((cSelf_s00fd_cd40*)&local)->FUN_00ad92d0();
    return r;
}

// @ 0x00fdd320
void cAppModeSpace_s00fd_cd40::FUN_00fdd320(int a1, void* a2)
{
    void* obj = FUN_00401010();
    if (((V1c2*)obj)->Test1c(a2, 0))
        return;

    void** r = FUN_00fdb230((void**)&a2, (uint32_t*)mpList170, (uint32_t*)&mpList170, (const uint32_t*)a2);
    if (*(void**)r != (void*)&mpList170)
        return;

    ((cSelf_s00fd_cd40*)&mpList170)->FUN_00bbe910(&mpList170, a2);
    mFlag16a = false;

    void* obj2 = FUN_00401010();
    ((V4c2*)obj2)->Test4c(a2, a1);
}

// @ 0x00fdd390
void cAppModeSpace_s00fd_cd40::TransitionFromPlanetToSolar(void* a1, int a2)
{
    ((cSelf_s00fd_cd40*)FUN_00b3d360())->FUN_00b7dec0();
    void* nm = ((cSelf_s00fd_cd40*)FUN_00b3d300())->FUN_00f67d90();

    if (FUN_00c8bb00(FUN_01021240()))
        ((cSelf_s00fd_cd40*)nm)->FUN_00c7ba90(FUN_01021240());
    if (FUN_00c8bb00(a1))
        ((cSelf_s00fd_cd40*)nm)->FUN_00c7ad40(a1);

    ((cM44*)FUN_01021230())->m44 = 1;

    ((cSelf_s00fd_cd40*)mpSpaceState)->FUN_01009470(0, (void*)(intptr_t)a2, 0);
    ((cSelf_s00fd_cd40*)mpSpaceState)->FUN_010039c0(FUN_01021230());
    FUN_010219b0(a1, (void*)0);
    ((cSelf_s00fd_cd40*)FUN_01046fc0((int)(intptr_t)a1))->FUN_01048e00x();

    void* r = FUN_00fdd200();
    if (r != 0)
        FUN_010219b0(FUN_01021240(), r);

    void* planet = FUN_01021260();
    ((cSelf_s00fd_cd40*)mpSpaceState)->FUN_01003a50();
    ((cSelf_s00fd_cd40*)((cSelf_s00fd_cd40*)FUN_00b3d300((int)(intptr_t)a1))->FUN_00f67d90())->FUN_00c79fa0(a1);

    void* e = ((V38b*)((V50*)FUN_0067dd10())->GetModeManager())->Get38();
    if (e != 0) {
        void* tag = ((V0c*)e)->Query(0x303154cc);
        if (tag != 0)
            ((cSelf_s00fd_cd40*)tag)->FUN_0101be60();
    }

    void* inv = ((cSelf_s00fd_cd40*)FUN_00ffbe50())->FUN_00a1ad60();
    if (planet != 0) {
        ((cSelf_s00fd_cd40*)inv)->FUN_00c3c190(planet);
        float f = ((cSelf_s00fd_cd40*)inv)->FUN_00c3ae70();
        Vector3 v;
        void* res = FUN_0105c3d0(&v, planet, f);
        ((cSelf_s00fd_cd40*)inv)->FUN_00c381e0(res);
    }
}

// @ 0x00fdd5a0
void cAppModeSpace_s00fd_cd40::TransitionFromGalaxyToSolar()
{
    void* inv = ((cSelf_s00fd_cd40*)FUN_00ffbe50())->FUN_00a1ad60();
    void* anm = FUN_01021240();
    FUN_01021230();

    ((cSPSpaceGameState*)mpSpaceState)->mFlags |= 8u;

    ((cSelf_s00fd_cd40*)((cSelf_s00fd_cd40*)FUN_00b3d300(0x574ac69))->FUN_00f67d90())->FUN_00c77bf0();

    ((V50x*)FUN_0067dd50())->X50(0x17);

    ((cSelf_s00fd_cd40*)mpSpaceState)->FUN_01003620();
    ((cSelf_s00fd_cd40*)mpSpaceState)->FUN_01003a50();
    ((cSelf_s00fd_cd40*)mpSpaceState)->FUN_01009470(1, (void*)1, 0);
    ((cSelf_s00fd_cd40*)mpSpaceState)->FUN_010077e0();

    if (((cSelf_s00fd_cd40*)anm)->FUN_00bb9ae0() == 5) {
        void* ship = ((cSelf_s00fd_cd40*)FUN_00b3d2a0(anm))->FUN_00bb1340();
        if (ship != 0) {
            ((cSelf_s00fd_cd40*)ship)->FUN_00c31c30(1);
            ((cSelf_s00fd_cd40*)DAT_016dc798)->FUN_01014a80i((int)(intptr_t)((c28*)ship)->p84, 3);
            void* av = ((cSelf_s00fd_cd40*)anm)->FUN_00b1fdb0();
            if (av != (void*)(intptr_t)FUN_01021090()) {
                void* o = ((cSelf_s00fd_cd40*)ship)->FUN_00c326b0();
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
    ((cSelf_s00fd_cd40*)FUN_00b3d2a0(anm))->FUN_00bb5b70(&v0);

    void* planet = FUN_01021260();
    if (planet == 0) {
        void* r = FUN_00fdd200();
        if (r != 0)
            FUN_010219b0(FUN_01021240(), r);
        planet = FUN_01021260();
    }

    ((cSelf_s00fd_cd40*)inv)->FUN_00c3bfe0(&DAT_016d9944);

    float k = DAT_015b4200;
    Vector3 sv;
    sv.x = DAT_015b4034 * k;
    sv.y = DAT_015b4038 * k;
    sv.z = DAT_015b403c * k;
    ((cSelf_s00fd_cd40*)inv)->FUN_00c381e0(&sv);
    ((cSelf_s00fd_cd40*)inv)->FUN_00c37e6f();

    if (planet != 0)
        ((cSelf_s00fd_cd40*)inv)->FUN_00c3c190(FUN_01021260());

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

    switch (((cSelf_s00fd_cd40*)anm)->FUN_00801920() - 1) {
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
        if (!((cSelf_s00fd_cd40*)anm)->FUN_00bb9bd0()) {
            void* x = FUN_01002bd0ii(0x15, 1);
            void* y = ((cSelf_s00fd_cd40*)x)->FUN_00bfc5f0();
            ((cSelf_s00fd_cd40*)y)->FUN_00fe5430();
        }
        if (((cSelf_s00fd_cd40*)reg)->FUN_0103ac40(&key) != 1) {
            IdKey key2 = key;
            ((cSelf_s00fd_cd40*)reg)->FUN_0103fba0(&key2, (void*)(intptr_t)1);
            void* g = FUN_00b3d3e0(0x8ab22514, 0x131a9f54, 0, 0, 1, 0);
            ((cSelf_s00fd_cd40*)g)->FUN_00dd8640i();
        }
    }

    ((cSelf_s00fd_cd40*)((cSelf_s00fd_cd40*)FUN_00b3d300((int)(intptr_t)anm))->FUN_00f67d90())->FUN_00c79fa0(anm);

    if (((cSelf_s00fd_cd40*)anm)->FUN_00801920() == 1) {
        void* g = FUN_00675250(0xf88c1342, 1);
        ((cSelf_s00fd_cd40*)g)->FUN_00676e90();
    }

    void* fx = ((cSPSpaceGameState*)mpSpaceState)->mpEffect;
    if (fx != 0)
        ((cSelf_s00fd_cd40*)fx)->FUN_01036620(0);

    void* e = ((V38b*)((V50*)FUN_0067dd10())->GetModeManager())->Get38();
    if (e != 0) {
        void* tag = ((V0c*)e)->Query(0x303154cc);
        if (tag != 0)
            ((cSelf_s00fd_cd40*)tag)->FUN_0101bd10();
    }

    ((cSPSpaceGameState*)mpSpaceState)->mFlags &= ~8u;

    ((V18v4*)FUN_0067dcc0())->Install4(0x5e37a44, (void*)0, (void*)0, 0);

    ((cSelf_s00fd_cd40*)&v0)->FUN_00ad92d0();
}

// @ 0x00fdf9f0
void cAppModeSpace_s00fd_f9f0::FUN_00fdf9f0()
{
    if (mp_15c->mp_54 == 0) {
        cSPSimPlanetHighLOD* p = (cSPSimPlanetHighLOD*)FUN_00f473a0(0x1e8, "Simulator", 0, 0, 0, 0);
        cSPSimPlanetHighLOD* np = (p != 0) ? p->FUN_00ff8970() : 0;

        cSPSimPlanetHighLOD** slot = &mp_15c->mp_54;
        cSPSimPlanetHighLOD* old = *slot;
        if (np != old) {
            if (np != 0)
                np->v04();
            *slot = np;
            if (old != 0)
                old->v08();
        }
    }

    void* planet = FUN_01021260();
    mp_15c->FUN_01005130();
    mp_15c->mp_54->ActivatePlanet(planet);
    ((cTerraformingManager*)FUN_00b3d430())->FUN_00bbe740(planet);
    ((cTerraformingManager*)FUN_00b3d430())->FUN_00bc1450(planet);

    cGameNounManager_s00fd_f9f0* nm = (cGameNounManager_s00fd_f9f0*)FUN_00b3d300();
    cDataVec* dv = (cDataVec*)nm->FUN_00b21340((void*)FUN_00cd7d10, (void*)FUN_00d3d420,
                                               (void*)FUN_00acdff0, (void*)FUN_00b1e500, &DAT_018c43e8);
    void*** pB = &dv->mpBegin;
    for (u32 i = 0; i < (u32)(pB[1] - pB[0]); ++i) {
        cSpaceObj* o = (cSpaceObj*)pB[0][i];
        FUN_00fdc340(o->mSub_120.s2c(), DAT_013ec4d0);
    }
}

// @ 0x00fdfb10
void* cAppModeSpace_s00fd_f9f0::FUN_00fdfb10()
{
    cGameNounManager_s00fd_f9f0* nm = (cGameNounManager_s00fd_f9f0*)FUN_00b3d300();
    void* dvp = nm->FUN_00b21340((void*)FUN_00cd7d10, (void*)FUN_00d3d420,
                                 (void*)FUN_00ae5ea0, (void*)FUN_00b1e500, (void*)0x0403df5c);

    cSPSimulatorSpaceGame_s00fd_f9f0* sim = (cSPSimulatorSpaceGame_s00fd_f9f0*)FUN_00ffbe50();
    cPlayerInventory_s00fd_f9f0* inv = sim->GetPlayerInventory();
    Vec3_s00fd_f9f0* src = inv->mSub_34.s2c();

    Vec3_s00fd_f9f0 v;
    v.x = src->x;
    v.y = src->y;
    v.z = src->z;

    u32 flag;
    *(u8*)&flag = 0;

    cResultObj* r = (cResultObj*)FUN_00fdb280((void*)((char*)dvp + 4), &v, flag);
    if (r != 0) {
        r->r00();
        r->r04();
        return (void*)((char*)r + 0x34);
    }
    return 0;
}

// @ 0x00fe0160
void cAppModeSpace_s00fd_f9f0::FUN_00fe0160()
{
    void* planet = FUN_01021260();
    if (planet != 0)
        FUN_0102f660_hook(planet);

    cGameNounManager_s00fd_f9f0* nm = (cGameNounManager_s00fd_f9f0*)FUN_00b3d300();
    nm->FUN_00b21340((void*)FUN_00b21080, (void*)FUN_00d3d420,
                     (void*)FUN_00b236c0, (void*)FUN_00b1e500, (void*)0x018c816a);

    FUN_01021230_s00fd_f9f0();
    void* pmodel = FUN_00b3d350();
    if (*(u32*)((char*)pmodel + 0x24) == 0) {
        FUN_00b8d750(FUN_00c713e0(1));
    } else {
        FUN_00b8d750(FUN_00c713c0());
    }

    FUN_00b515e0();
    FUN_00b88420(FUN_00b3d310());
    FUN_00ffd390(FUN_00ffbe50());

    FUN_01003690();
    FUN_00fdf9f0();

    mb_24 = 1;

    FUN_00fda750(this);
    FUN_00b8de30((void*)planet);
    FUN_010219b0();
    FUN_01066d60(FUN_00c70e00());

    FUN_00c73b60(0);
    for (i32 i = 0; i < FUN_00c710c0(); ++i) {
        void* node = FUN_00c71030((u32)i);
        if ((i32)FUN_00a1c4e0(node) == (i32)FUN_00b1e700()) {
            void* node2 = FUN_00c71030((u32)i);
            FUN_00ff0940();
            FUN_00b25fb0();
            (void)node2;
            FUN_00c71030((u32)i);
            FUN_00ff3540();
        }
    }
    FUN_00c6ffc0(0);
    FUN_00c70bf0(0);
    FUN_00c6ffa0();

    FUN_00c73ff0(this);
    FUN_00c74280(this);
    FUN_00c73cf0(0);
    FUN_00b87bb0();

    FUN_00c75770_hook();
    FUN_00fdba50(this, 1, 1);
    FUN_00401010();
}

// @ 0x00fe1a20
void __stdcall cAppModeSpace_LoadStateMachine(int mode)
{
    if (mode == 1)
        GameInputManager()->SetTriggerConfig("TriggerConfigSpaceFlight", 0, 1);
    else
        GameInputManager()->SetTriggerConfig("TriggerConfigSpaceGame", 0, 1);

    const char* wasd = "TriggerConfigWASD";
    if (LanguageEquals(GetLocaleManager()->GetLanguage(), L"fr-fr"))
        wasd = "TriggerConfigWASD_fr-fr";
    GameInputManager()->SetTriggerConfig(wasd, 0, 0);

    DeclareMenuCommands();

    uint32_t f[0x68 / 4];
    f[0x34 / 4] = 0;
    f[0x34 / 4] = (uint32_t)&f[0x34 / 4];
    f[0x38 / 4] = (uint32_t)&f[0x34 / 4];
    f[0x3c / 4] = 0;
    f[0x40 / 4] = 0;
    f[0x44 / 4] = 0;
    f[0x50 / 4] = (uint32_t)&f[0x50 / 4];
    f[0x54 / 4] = (uint32_t)&f[0x50 / 4];
    f[0x58 / 4] = 0;
    f[0x5c / 4] = 0;
    f[0x60 / 4] = 0;

    StateMachineBuilder& sm = *(StateMachineBuilder*)&f[0x1c / 4];
    sm.Init(&f[0x30 / 4]);
    sm.AddStateName(0, "Space: normal");
    sm.AddStateName(1, "Space: banning content");
    sm.AddStateName(2, "Space: inpsecting content");
    sm.SetMachineName("UIMachineCommunityEditor");

    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 1, 0x3ff, 0x3e8, 0x1007ae63, 1, 0x33cabf0, 0, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 4, 0x40, 0x1b, -1, 0, 0x33cabf3, 0, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 9, 0x3ff, 0x37ab944, -1, 0, 0x71d4dfc9, 0, 3, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(3, 9, 0x3ff, 0x3e86, -1, 0, 0, 0, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 4, 0, 8, -1, 0, 0x2e81d88, 0x29a, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 4, 1, 9, -1, 0, 0x62b45c3, 0, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 4, 0, 9, -1, 0, 0x62b45bb, 0, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 5, 0, 0x11, -1, 0, 0x62b4605, 1, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 4, 0, 0x11, -1, 0, 0x62b4605, 2, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 4, 0, 0xdb, -1, 0, 0x62bfa72, 0, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 4, 0, 0xdd, -1, 0, 0x62bfa41, 0, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 4, 0, 0x31, -1, 0, 0x6274486, 0, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 4, 0, 0x32, -1, 0, 0x6274486, 1, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 4, 0, 0x33, -1, 0, 0x6274486, 2, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 4, 0, 0x34, -1, 0, 0x6274486, 3, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 4, 0, 0x35, -1, 0, 0x6274486, 4, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 4, 0, 0x36, -1, 0, 0x6274486, 5, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 4, 0, 0x37, -1, 0, 0x6274486, 6, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 4, 0, 0x38, -1, 0, 0x6274486, 7, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 4, 0, 0x39, -1, 0, 0x6274486, 8, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 4, 0, 0x30, -1, 0, 0x6274486, 9, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 4, 0, 0x4f, -1, 0, 0x33b7638, 1, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 5, 0, 0x4f, -1, 0, 0x33b7638, 0, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 1, 0, 0x3e8, 0xb033b403, 0, 0x3056566, 0x29a, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 1, 0, 0x3e8, 0x436f315, 2, 0x4dd13d1, 0, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 1, 0, 0x3e8, 0xd0036e08, 2, 0x5417b45, 0, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 1, 0, 0x3e8, 0x137e8e0, 2, 0x54a7806, 0, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 1, 0, 0x3e8, 0x244d3c0, 0, 0x57df7e0, 0, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = g_vecBuf; v.cap = g_vecBuf + 1; BoolVec_DoInsertValue(g_vecBuf, &g_falseConst, 0); v.e = g_vecBuf; *v.e = 0;
        sm.AddTransition(0, 1, 0x3ff, 0x3e8, 0x3275872, 0, 0x22d38ee, 0x29a, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = 0; v.e = 0; v.cap = 0; v.Construct(&g_falseConst);
        sm.AddTransition(0, 1, 0x3ff, 0x3ea, 0x3275872, 0, 0x22d38ee, 0x29a, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = 0; v.e = 0; v.cap = 0; v.Construct(&g_falseConst);
        sm.AddTransition(0, 1, 0x3ff, 0x3e8, 0x38cfb68, 0, 0x589c84b, 0x29a, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = 0; v.e = 0; v.cap = 0; v.Construct(&g_falseConst);
        sm.AddTransition(0, 1, 0x3ff, 0x3ea, 0x38cfb68, 0, 0x589c84b, 0x29a, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = 0; v.e = 0; v.cap = 0; v.Construct(&g_falseConst);
        sm.AddTransition(0, 1, 0, 0x3e8, 0, 0, 0x3065e0f, 0x29a, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = 0; v.e = 0; v.cap = 0; v.Construct(&g_falseConst);
        sm.AddTransition(1, 1, 0x3ff, 0x3e8, -1, 0, 0x44ebe3f, -1, 1, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = 0; v.e = 0; v.cap = 0; v.Construct(&g_falseConst);
        sm.AddTransition(1, 6, 0x3ff, -1, -1, 0, 0x456b08c, -1, 1, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = 0; v.e = 0; v.cap = 0; v.Construct(&g_falseConst);
        sm.AddTransition(1, 4, 0x3ff, 0x1b, -1, 0, 0x44ecd59, 0, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = 0; v.e = 0; v.cap = 0; v.Construct(&g_falseConst);
        sm.AddTransition(2, 1, 0x3ff, 0x3e8, -1, 0, 0x62656dd, -1, 2, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = 0; v.e = 0; v.cap = 0; v.Construct(&g_falseConst);
        sm.AddTransition(2, 6, 0x3ff, -1, -1, 0, 0x62656de, -1, 2, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = 0; v.e = 0; v.cap = 0; v.Construct(&g_falseConst);
        sm.AddTransition(2, 4, 0x3ff, 0x1b, -1, 0, 0x62656df, 0, 0, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = 0; v.e = 0; v.cap = 0; v.Construct(&g_falseConst);
        sm.AddTransition(0, 6, 0x3ff, -1, 0xce9f6639, 0, 0x534052c, -1, -2, 0, &v, 0);
        v.Destroy();
    }
    {
        BoolVec v; v.b = 0; v.e = 0; v.cap = 0; v.Construct(&g_falseConst);
        sm.AddTransition(0, 6, 0x3ff, -1, 0, 0, 0x534052c, -1, -2, 0, &v, 0);
        v.Destroy();
    }

    GameInputManager()->InstallStateMachine(&f[0x1c / 4], 0, 0);
    ((CommandBase*)&f[0x14 / 4])->Destroy();
    ((NodeTree*)&f[0x44 / 4])->Destroy(f[0x50 / 4]);
    ((BuilderCleanup*)&f[0x28 / 4])->Destroy(f[0x34 / 4]);
}

// @ 0x00fe2ec0
namespace SP {
bool cAppModeSpace_s00fe_2ec0::HandleMessage(uint32 messageID, void* pMsg)
{
    SpaceMsg* msg = (SpaceMsg*)pMsg;
    switch (messageID) {
    case 0x1a0219e:
        switch (msg->p8) {
        case 1: OnNewGame(); break;
        case 6: OnLoadGame(); break;
        }
        return false;

    case 0x1622184: {
        cCombatant_s00fe_2ec0* combatant = (cCombatant_s00fe_2ec0*)msg->p8;
        cCombatantLike* attacker = (cCombatantLike*)msg->p10;
        if (combatant->GetDamageState() != 2)
            return true;
        cCreatureLike* creature = AsCreature(combatant);
        cBuildingLike* building = AsBuilding(combatant);
        if (attacker == GetUFOSimulator()->GetPlayerInventory() && (creature || building)) {
            cEmpire_s00fe_2ec0* owner = GetActivePlanet_s00fe_2ec0()->GetOwner();
            if (owner) {
                if (owner == GetPlayerEmpire())
                    EventLog()->PostFeedbackEvent(0xc88d9222, 0x131a9f54, 0, 0, 1, 0);
                else if (RelationshipManager()->IsAtWar(owner, 0))
                    EventLog()->PostFeedbackEvent(0x8c5cb303, 0x131a9f54, 0, 0, 1, 0);
            }
            cCommunity_s00fe_2ec0* community;
            if (building)
                community = building->GetCommunity();
            else if (creature)
                community = creature->GetCommunity();
            else
                return true;
            if (community && !community->m120.IsDestroyed()) {
                community->Reaction();
                float f = RelationshipManager()->RecordEvent(community->GetOwnerID(), GetPlayerEmpireID(), 0x526e53c, 1.0f);
                DoCommunityReaction(community, f, combatant->GetSelf()->GetID());
            }
            return true;
        }
        cEnemyLike* enemy = AsEnemy(combatant);
        if (attacker == GetUFOSimulator()->GetPlayerInventory() && enemy) {
            if (CheckEnemyDeath(enemy, GetUFOSimulator()->GetPlayerInventory(), IsBlockadeOwner(GetActivePlanet_s00fe_2ec0())))
                SetGlobalProperty(SPIDFromName("spg_war_enemy_death"), 1.0f);
        }
        cPlayerInventory_s00fe_2ec0* inv = GetUFOSimulator()->GetPlayerInventory();
        if (attacker == inv && enemy && enemy->mState == 6) {
            cCommunity_s00fe_2ec0* community = FindCommunity(NounManager_s00fe_2ec0()->GetFn2c0(), inv->GetSelf()->GetID());
            if (community && !community->m120.IsDestroyed())
                community->Reaction();
        }
        return true;
    }

    case 0x3795725: {
        cEmpire_s00fe_2ec0* empire = GetPlayerEmpire();
        void* mode = GetCurrentGameMode();
        if (!empire || mode == (void*)0x1654c10)
            return false;
        empire->SetSpecies(SpeciesManager()->GetProfile(KeyTriple(msg->p10, msg->p8, msg->p18)));
        MessageServer()->PostMSG(0x490d429, 0, 0, 0);
        return false;
    }

    case 0x3ac86b5: {
        cEmpire_s00fe_2ec0* empire = (cEmpire_s00fe_2ec0*)msg->p10;
        cEmpire_s00fe_2ec0* player = GetPlayerEmpire();
        uint8* extra = (uint8*)msg->p18;
        if (extra && extra[0x30])
            return false;
        if (empire && !empire->IsDestroyed()) {
            empire->Fn930();
            empire->Fn9b0(0);
            if (empire != player) {
                NounManager_s00fe_2ec0()->GetCurrentTerrainSphere()->PlayMusic(0x5f1f0cb);
                cRelationshipManager_s00fe_2ec0* rm = RelationshipManager();
                uint32 a = empire->mPoliticalID;
                if (rm->GetEvent(a, player->mPoliticalID, 0x5b6cf09) == 0.0f && rm->GetEvent(a, player->mPoliticalID, 0x5f62736) == 0.0f)
                    rm->RecordEvent(a, player->mPoliticalID, 0x5b6cf09, 1.0f);
                cGameNounManager_s00fe_2ec0* gnm = mpGameNounManager;
                if (gnm) {
                    cTribeLike* tribe = gnm->GetPlayerTribe();
                    if (tribe) {
                        tribe->Fn5430(4, 1);
                        cPlanetRecord_s00fe_2ec0* planet = GetActivePlanetRecord();
                        if (!planet)
                            planet = empire->GetHomePlanet();
                        if (empire->HasContact()) {
                            uint32 id = 0xaff54daa;
                            if (empire->IsAlly())
                                id = 0xf31ed5f3;
                            CommEvent(id, empire, ResKey(), ResKey(), planet->GetCommContext(), 0, ResKey(), ResKey());
                        }
                    }
                }
            }
        }
        if (empire == player) {
            cPlanet_s00fe_2ec0* planet = GetActivePlanet_s00fe_2ec0();
            cPlanetRecord_s00fe_2ec0* rec;
            if (planet && (rec = planet->mRecord) != GetPlayerHomePlanet())
                planet->Fn430(4, 1);
            g_WarSystem->Update();
        }
        cTerrainSphere_s00fe_2ec0* sphere = NounManager_s00fe_2ec0()->GetCurrentTerrainSphere();
        if (sphere && sphere->HasMusic(0x4ac8010))
            sphere->PlayMusic((empire != player) + 0x61f1455);
        return false;
    }

    case 0x3ec1631:
        if (msg) {
            uint32 stim = msg->p8;
            void* creature = GetCreatureFromStimulus(stim);
            if (creature) {
                ScanBuilding(creature);
                return true;
            }
            cScannable* s = FindScannable(stim);
            if (s) {
                ScanObject(s->GetKey());
            }
        }
        return true;

    case 0x452e0ca:
        if (GetCurrentGameMode() != (void*)0x1654c05)
            return false;
        if (Fn5df0()->IsBusy())
            return false;
        SetDefaultPickPriority();
        GameInputManager_s00fe_2ec0()->SetMode(0);
        EndBanMode(1);
        return false;

    case 0x44eaa93: {
        if (GetCurrentGameMode() != (void*)0x1654c05)
            return false;
        if (Fn5df0()->IsBusy())
            return false;
        IGameInputManager_s00fe_2ec0* gim = GameInputManager_s00fe_2ec0();
        switch (gim->GetMode()) {
        case 0:
            mpGameNounManager->Fn3480();
            Fndfa0();
            gim->SetMode(1);
            ToggleBanningContent(1);
            break;
        case 1:
            SetDefaultPickPriority();
            gim->SetMode(0);
            EndBanMode(1);
            break;
        }
        return false;
    }

    case 0x5e37a2c:
        Fn9de0();
        return false;

    case 0x5e37a3b:
        Fnabf0();
        return false;

    case 0x5e37a44:
        if (GetActivePlanetRecord())
            mbPendingPlanet = true;
        else
            Fnade0();
        return false;

    case 0x5e37a53:
        HandleMessage2();
        return false;

    case 0x6148657: {
        if (GameTimeManager()->mFlags & 1)
            return false;
        if (GetUniverseContext())
            return false;
        mWarpTimer.Restart();
        Vector3_s00fe_2ec0 pos;
        PosSource()->GetPosition(pos, 1, GetUFOSimulator()->GetPlayerInventory());
        GetUFOSimulator()->SetPlanetDestination(&pos, 0, 1, 0, 0);
        GetUFOSimulator()->OnWarp();
        AutoRefCount<IVisualEffect> effect;
        if (EffectsManager_s00fe_2ec0()->CreateVisualEffect(0x384e54a4, 0, effect.AsPPTypeParam())) {
            Transform xf;
            xf.SetOffset(pos);
            const Vector3_s00fe_2ec0& up = normalized_safe(pos);
            const Vector3_s00fe_2ec0& facing = normalized_safe(OrthogonalVector(up));
            xf.SetRotation(Matrix3FromFacingAndUp(facing, up));
            effect->SetTransform(xf);
            effect->Start(0);
        }
        cCameraController* cam = AsPlanetCamera(App()->GetCameraManager()->GetActiveCameraController());
        if (cam)
            cam->Fn270(0);
        return false;
    }

    case 0x6148658:
        if (GetUniverseContext())
            return false;
        if (!(GameTimeManager()->mFlags & 1)) {
            if (mWarpTimer.GetElapsedTime() > 250)
                GetUFOSimulator()->SetPlanetDestination(GetUFOSimulator()->GetPlayerInventory()->m34.GetDestination(), 1, 0, 1, 0);
        }
        mWarpTimer.Reset();
        return false;

    case 0x620222b: {
        if (GetCurrentGameMode() != (void*)0x1654c05)
            return false;
        if (Fn5df0()->IsBusy())
            return false;
        IGameInputManager_s00fe_2ec0* gim = GameInputManager_s00fe_2ec0();
        switch (gim->GetMode()) {
        case 0:
            mpGameNounManager->Fn3480();
            Fndfa0();
            gim->SetMode(2);
            StartPlanetMode(1);
            break;
        case 2:
            SetDefaultPickPriority();
            gim->SetMode(0);
            EndPlanetMode(1);
            break;
        }
        return false;
    }

    case 0x620271c:
        if (GetCurrentGameMode() != (void*)0x1654c05)
            return false;
        if (Fn5df0()->IsBusy())
            return false;
        SetDefaultPickPriority();
        GameInputManager_s00fe_2ec0()->SetMode(0);
        EndPlanetMode(1);
        return false;

    case 0x667af52:
        Fn4d0()->Fn();
        return false;

    case 0x679c40d:
        if (GetCurrentGameMode() != (void*)0x1654c05)
            return false;
        LoadStateMachine(ConfigManager()->GetPropertyList(0x679b880));
        return false;

    case 0x695e243:
        if (mpGameNounManager->mbSpaceMission || mpGameNounManager->mbTutorialMission) {
            KeyTriple key;
            key.a = msg->p8;
            key.b = msg->p18;
            key.c = msg->p10;
            ListIter it = FindKey(mMissions.begin(), mMissions.end(), key);
            if (it.mpNode != &mMissions.mNode)
                mMissions.erase(it);
            if (mMissions.empty())
                mbMissionsDone = true;
        }
        return true;

    case 0x71d4dfc8:
    case 0x71d4dfc9:
        GameInputManager_s00fe_2ec0()->Reset();
        return false;
    }
    return false;
}
}  // namespace SP
