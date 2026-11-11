// src/game/SPGonzago/SPAppModeSpace.cpp -- migrated from slice(s) s010414c0, s00fe2ab0, s00fe0570, s00fdeac0, s00fddba0, s00fe2ec0, s00fe1a20, s00fdf9f0, s00fdcd40, s00fdbd60, s00fdade0, s00fd9f70, s00fd90c0 by tools/migrate/rewrite.py
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
#include <string.h>
#include "SP/cIModelWorld.h"
#include "EA/ResourceMan/Key.h"
#include "SP/cCivData.h"
#include "SP/cMWModel.h"
#include "SP/cSolarSystem.h"
#include "SP/cStar.h"
#include "SP/cStarManager.h"
#include "SP/cTribeTool.h"
#include <intrin.h>
#include "SP/cSPGameDataUFO.h"
#define __PLACEMENT_NEW_INLINE   // the slices' own placement new/delete win over <new>'s (rewrite.py)
#include <new>
#include "SP/cSPEditorSpeciesManager.h"
#include "SP/cCity.h"
#include "SP/cPropertyManager.h"
inline void operator delete(void*, void*) {}   // placement delete (<new>'s is skipped, rewrite.py)

// unnamed retail callees and globals (address in the comment)
extern void* DAT_01654c05;

// ---- items of slice s00fd90c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
void* __cdecl  FUN_0067caa0();                       // SP::WindowManager
void* __cdecl  FUN_00b2f740();                       // returns char
void* __cdecl  FUN_00805180();                       // returns char
void* __cdecl  FUN_00b3d250();                       // SP::GameInputManager
void* __cdecl  FUN_00b3d2c0();                       // SP::RelationshipManager
void* __cdecl  FUN_00b3d4a0();                       // CommManager
void* __stdcall FUN_00b3d3f0(int);                   // 0x00b3d3f0 -> void*
void* __stdcall FUN_00b3d470(void*);                 // 0x00b3d470 -> void*
void* __cdecl  FUN_00b5b800();                       // SP::GetCurrentGameMode
int   __stdcall FUN_01021230(int);                   // 0x01021230
int   __stdcall FUN_01021230_0();                    // 0x01021230 (no-arg call site)
void  __cdecl  FUN_010213b0(int);                    // 0x010213b0
int   __cdecl  FUN_01021080();                       // GetUniverseContext
void* __cdecl  FUN_01021240();                       // SP::cSPMission::IsArchived
int   __cdecl  FUN_01021090();                       // GetPlayerEmpireID
void* __cdecl  FUN_010666a0();                       // 0x010666a0
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
class cSPSpaceGameState;
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
    void* FUN_01046fc0(void* arg);                       // 0x01046fc0
    bool FUN_00fda1f0(float x, float y, int button);
    bool FUN_00fda2e0(void* v);
    void FUN_00fda480();
    void FUN_00fda5e0();
    void FUN_00fda750();
    void FUN_00fda940();
    void FUN_00fda9f0();
    bool FUN_00fdab40(void* arg);
    void FUN_00fdabf0();
    uint8_t             pad000[0x158];                   // +0x000 .. +0x157
    bool                mFlag158;                        // +0x158
    uint8_t             pad159[0x3];                     // +0x159 .. +0x15b
    cSPSpaceGameState*  mpSpaceState;                    // +0x15c
    void*               mpObj160;                        // +0x160
    uint8_t             pad164[0x180 - 0x164];           // +0x164 .. +0x17f
    cGonzagoSubsystem_s00fd_9f70*  mpGonzagoSubsystem;              // +0x180
    uint8_t             pad184[0x9];                     // +0x184 .. +0x18c
    bool                mFlag18d;                        // +0x18d
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
extern float   DAT_01471064;                 // 0x01471064
extern char     DAT_013f09b4[];              // 0x013f09b4  "Simulator"
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
void* FUN_01021260();                                          // 0x01021260  GetActivePlanet
void* FUN_01021300();                                          // 0x01021300  GetPlayerEmpire
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
    bool      FUN_00b5ca60();        // 0x00b5ca60
    bool      FUN_00c37170();        // 0x00c37170
    void      FUN_01050bb0();        // 0x01050bb0
    bool      FUN_01046f30();        // 0x01046f30
    void      FUN_01003c60(float x, float y); // 0x01003c60
    bool      FUN_01017300(void* arg); // 0x01017300
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
    void  FUN_00bc2f00(float f, void* p);            // 0x00bc2f00 (2 stack args)
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
    void FUN_0100a960();                           // 0x0100a960
    void FUN_01009470(int a, void* b, int c);      // 0x01009470
    void FUN_010039c0(void* a);                    // 0x010039c0
    void FUN_01003620();                           // 0x01003620
    void FUN_01002be0();                           // 0x01002be0
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

    void InitSpaceGame();  // 0x00fdbd60 (cAppModeSpace::InitSpaceGame)
    void EnterSpaceGame();  // 0x00fdbee0 (cAppModeSpace::EnterSpaceGame)
    void ShutdownSPG();  // 0x00fdc150 (cAppModeSpace::ShutdownSPG)
    void LoadNewGamePlanet();  // 0x00fdc240 (cAppModeSpace::LoadNewGamePlanet)
    void TransitionFromLoadToPlanet();
    void TransitionFromEditorToPlanet();
    void TransitionToEntry();
    void PlanetOnMouseDown();
    void StopEditorPlay();
    bool OnMouseDown(int nButton, int nX, int nY, int nFlags);  // 0x00fdc520 (cAppModeSpace::OnMouseDown)

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
void UpdateGridCells(void* pCells, int nCount, float fRadius);
void UpdateGridOverlay(float fRadius, int nCount, void* pCells);
void DrawGridRing(int a);
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
void SetLoadedPlanet();
void InitPlanetView();
void* GetActivePlanet();
void* PlanetModel();
void* CreatePlanetView(int a, int b);
void SetPlanetViewPlanet(void* pView, int a, int b);
void SetPlanetModelView(int nView);
void EnablePlanetFeatures();
void RefreshPlanetUI();
void* CreateTransitionMessage();
void PostMessage(void* pMessage);
void RefreshModeUI();
void ResetTransitionTuning();
void ShowMissionLog();
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
    void  FUN_00bc2f00(float f, void* p);            // 0x00bc2f00 (2 stack args)
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

// ---- items of slice s00fddba0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern bool gViewFlagA;             // 0x016dd441
extern uint32_t g_cheatFlag;                                               // 0x015b732c
void operator delete[](void* p);                                                                                       // 0x00f47380
#define EASTL_ALLOCATOR_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
#define VIRT4(n) virtual void n##0(); virtual void n##1(); virtual void n##2(); virtual void n##3();
struct Quaternion { float x, y, z, w; };
extern const Vector3 kUpAxisY;      // 0x015b4028 (0, 1, 0)
extern const Vector3 kUpAxisZ;      // 0x015b4034 (0, 0, 1)
extern const Vector3 kFlyOutScale;  // 0x015b4204 (x = 10.0)
class cSpatialObject
{
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
    virtual const Vector3* GetPosition();                  // +0x2c
    virtual const Quaternion* GetOrientation();            // +0x30
};
class cPlanetInfo
{
public:
    bool IsHidden();                                       // 0x00b8d970 ((flags >> 8) & 1)
};
class cPlanet : public cSpatialObject
{
public:
    int GetKind();                                         // 0x00c70880 (0 and 1 are skipped)
    uint32_t pad04[(0x13c - 0x04) / 4];
    cPlanetInfo* mpInfo;                                   // +0x13c
};
class cSolarSystem
{
public:
    uint32_t pad00[0x10 / 4];
    cPlanet** mPlanetsBegin;                               // +0x10
    cPlanet** mPlanetsEnd;                                 // +0x14
};
class cStar
{
public:
    cSolarSystem* GetSolarSystem();                        // 0x00c8b770
    virtual int AddRef();
    virtual int Release();
};
class cSPGameDataUFO
{
public:
    void SetDestination(const Vector3* p);                 // 0x00c3bfe0
    void SetDestination(cPlanet* planet);                  // 0x00c3c190
    void PopToDestination();                               // 0x00c37e60

    uint32_t       pad00[0x34 / 4];
    cSpatialObject mSpatial;                               // +0x34
    uint32_t       pad38[(0x730 - 0x38) / 4];
    Quaternion     mOrientation;                           // +0x730
};
class cEffect
{
public:
    void Stop(int fast);                                   // 0x0106ab20 (ret 4)
};
class cSPSpaceGameState_s00fd_dba0                                    // object at cAppModeSpace +0x15c
{
public:
    void Reset();                                          // 0x0100a960
    void Update();                                         // 0x01003a50
    void ChaseFromPlanetToSolar();                         // 0x01007ed0
    uint32_t pad00[0x14 / 4];
    cEffect* mpActiveEffect;                               // +0x14
    uint32_t pad18[(0x50 - 0x18) / 4];
    uint32_t mFlags;                                       // +0x50
};
class cStarList { public: uint32_t pad00[0x2c / 4]; cStar** mBegin; cStar** mEnd; };   // vector at +0x2c
class cSpaceGame { public: uint32_t pad00[0x30 / 4]; cStarList* mpStars; };            // +0x30
class cSPSimulatorSpaceGame_s00fd_dba0
{
public:
    cSPGameDataUFO* GetPlayerInventory();                  // 0x00a1ad60
};
cStar* GetActiveStar();                                    // 0x01021230
cPlanet* GetActivePlanet_s00fd_dba0();                                // 0x01021260
void* GetActivePlanetRecord_s00fd_dba0();                             // 0x010212a0
cSPSimulatorSpaceGame_s00fd_dba0* GetUFOSimulator_s00fd_dba0();                  // 0x00ffbe50
cSpaceGame* SpaceGameGet_s00fd_dba0();                                // 0x01002bd0
class cHud
{
public:
    bool IsActive();                                       // 0x00a98020
    int GetMode();                                         // 0x00985e40
    void Show();                                           // 0x01016950
};
cHud* GetHud();                                            // 0x01015df0
class cCameraView
{
public:
    char pad00[0xb4];
    Vector3 mTarget;                                       // +0xb4
    char padc0[0x13d - 0xc0];
    bool mbFlag;                                           // +0x13d
};
class cHudCtl
{
public:
    void Apply(const Vector3* target, bool flag);          // 0x0101bb90 (ret 8)
};
class cModeObject
{
public:
virtual void m0();
virtual void m1();
virtual void m2();
    virtual void* Query(uint32_t typeID);                  // +0xc
};
class cModeManager
{
public:
VIRT4(a) VIRT4(b) VIRT4(c) virtual void c4();
virtual void c5();
    virtual cModeObject* GetCurrentMode();                 // +0x38
};
class cApp
{
public:
    VIRT4(a) VIRT4(b) VIRT4(c) VIRT4(d) VIRT4(e)
    virtual cModeManager* GetModeManager();                // +0x50
};
cApp* App_s00fd_dba0();                                               // 0x0067dd10
class cMessageServer
{
public:
VIRT4(a) virtual void v10();
virtual void v14();
    virtual void PostMessage(uint32_t id, int a, int b, int c);   // +0x18
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
    virtual void Notify(void* target, uint32_t id, int param);    // +0x2c (ret 0xc)
};
cMessageServer* MessageServer_s00fd_dba0();                           // 0x0067dcc0
class cPlanetModel_s00fd_dba0
{
public:
    void Refresh();                                        // 0x00b8c0f0
};
cPlanetModel_s00fd_dba0* PlanetModel_s00fd_dba0();                               // 0x00b3d350
class cTerrainSphere
{
public:
    void SetModel(uint32_t id);                            // 0x00c77bf0 (ret 4)
};
class cNounManager_s00fd_dba0
{
public:
    cTerrainSphere* GetCurrentTerrainSphere();             // 0x00f67d90
};
cNounManager_s00fd_dba0* NounManager_s00fd_dba0();                               // 0x00b3d300
class cEffectsMgr
{
public:
    void Play(uint32_t id);                                // 0x00b5cde0 (ret 4)
};
cEffectsMgr* GetEffectsMgr();                              // 0x00b3d230
class cPlanetRegistry
{
public:
    void Show(cPlanet* p);                                 // 0x00b7daf0 (ret 4)
};
cPlanetRegistry* GetPlanetRegistry();                      // 0x00b3d360
class cSPTimer
{
public:
    unsigned __int64 GetElapsedTime();                     // 0x00bc3190
};
class cAchievementsController
{
public:
    void AwardAchievement(uint32_t id);                    // 0x00676710 (ret 4)
};
cAchievementsController* GetAchievements();                // 0x00675250
struct cTuning
{
    int GetMaxBuildingsForT3Colony();                      // 0x01049ef0
};
cTuning* GetTerraformTuning();                             // 0x01049a10 (returns &global 0x016e0d04)
void GetTurretAndBuildingCounts(cStar* star, int* turrets, int* buildings);   // 0x00c70380 (cdecl)
struct cTutorialStep { uint32_t pad00[2]; uint32_t mID; };   // +8
class cTutorial
{
public:
    uint32_t pad00[0x4c / 4];
    cTutorialStep* mpCurrent;                              // +0x4c
    void Close(uint32_t id, int flag);                     // 0x0067c8c0 (ret 8)
};
cTutorial* GetTutorial();                                  // 0x0067cac0
class cPopup
{
public:
    void Refresh();                                        // 0x01065d20
};
cPopup* GetPopup();                                        // 0x010666a0
class cEmpire
{
public:
    int GetID();                                           // 0x00c30c80
    void* GetUFOKey();                                     // 0x00c326b0
};
cEmpire* GetPlayerEmpire_s00fd_dba0();                                // 0x01021300
class cHudEmpire
{
public:
    void Update(int id);                                   // 0x004df3e0 (ret 4)
};
cHudEmpire* GetHudEmpire();                                // 0x00401090
void NotifyActivePlanetRecord(void* record);               // 0x00fde230 (cdecl)
Vector3* RotateByQuaternion(Vector3* out, const Vector3* v, const Quaternion* q);   // 0x0059aed0 (cdecl)
Vector3* OrthogonalVector(Vector3* out, const Vector3* v);                          // 0x006985b0 (cdecl)
Quaternion* QuaternionFromFacingAndUp(Quaternion* out, const Vector3* facing, const Vector3* up);   // 0x0069b600 (cdecl)
class cMWModel;
struct cModelRef { cMWModel* p; };
cModelRef* copy_impl(cModelRef* first, cModelRef* last, cModelRef* dest);            // 0x005f4e10 (cdecl)
cStar*** uninitialized_copy_stars(cStar*** out, cStar** first, cStar** last, cStar** dest, int tag);   // 0x00829110 (cdecl)
struct ModelVector
{
    cModelRef* mpBegin;                                    // +0x144 in cAppModeSpace
    cModelRef* mpEnd;
    cModelRef* mpCapacity;
    void DoDestroyValues(cModelRef* first, cModelRef* last);   // 0x005f3680 (ret 8)
    cModelRef* erase(cModelRef* first, cModelRef* last)
    {
        cModelRef* itDest = copy_impl(last, mpEnd, first);
        DoDestroyValues(itDest, mpEnd);
        mpEnd -= (last - first);
        return first;
    }
    void clear() { erase(mpBegin, mpEnd); }
};
inline Quaternion QuatMul(const Quaternion& a, const Quaternion& b)
{
    float c0 = a.z * b.y - a.y * b.z;
    float c1 = b.z * a.x - a.z * b.x;
    float c2 = a.y * b.x - b.y * a.x;
    Quaternion r;
    r.x = (a.x * b.w + b.x * a.w) + c0;
    r.y = (a.y * b.w + b.y * a.w) + c1;
    r.z = (a.z * b.w + b.z * a.w) + c2;
    r.w = a.w * b.w - ((a.z * b.z + a.y * b.y) + a.x * b.x);
    return r;
}
class cModeBase { public: void* mpVtbl; };                         // interface sub-object at +0x04
class cAppModeSpace_s00fd_dba0
{
public:
    void TransitionFromPlanetToSolar(bool bUpdateEmpire);          // 0x00fde3e0
    bool Shutdown();                                               // 0x00fde180
    void ShutdownSPG();                                            // 0x00fdc150
    static void SetDefaultPickPriority();                          // 0x00fddba0

    char pad00[0x04];
    cModeBase mBase;                                               // +0x04 message-server target
    char pad08[0x144 - 0x08];
    ModelVector mModels;                                           // +0x144
    char pad150[0x15c - 0x150];
    cSPSpaceGameState_s00fd_dba0* mpSpaceGame;                                // +0x15c
    static cAppModeSpace_s00fd_dba0* sInstance;                               // 0x016d9938
};
struct PickPriority
{
    uint32_t mKey;          // interface id the picker looks for
    uint32_t mMode;         // pick mode it applies to
    int32_t  mPriority;     // lower runs first
    PickPriority(uint32_t key, uint32_t mode, int32_t priority)
        : mKey(key), mMode(mode), mPriority(priority) {}
};
struct PickPriorityVec
{
    PickPriority* mpBegin;
    PickPriority* mpEnd;
    PickPriority* mpCapacity;

    PickPriorityVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}

    void DoInsertValue(PickPriority* pos, const PickPriority& value);       // 0x00b535d0 (ret 8)

    void push_back(const PickPriority& value)
    {
        PickPriority* end = mpEnd;
        if (end < mpCapacity)
        {
            mpEnd = end + 1;
            if (end != 0)
                *end = value;
        }
        else
        {
            DoInsertValue(end, value);
        }
    }

    ~PickPriorityVec()
    {
        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
            operator delete[](mpBegin);
    }
};
class cPickPriorityMgr
{
public:
VIRT4(a) VIRT4(b) virtual void v20();
virtual void v24();
virtual void v28();
    virtual void SetList(PickPriorityVec* list, int mode);                 // +0x2c (ret 8)
};
cPickPriorityMgr* PickPriorityMgr();                                       // 0x00b3d240
void FUN_00e1dbd0();                                                       // 0x00e1dbd0
class cCheatManager
{
public:
VIRT4(a) virtual void v10();
virtual void v14();
virtual void v18();
    virtual void SetFlag(uint32_t flag);                                   // +0x1c (ret 4)
};
cCheatManager* CheatManager();                                             // 0x0067de20
inline cModeBase* GetModeBase(cAppModeSpace_s00fd_dba0* mode)
{
    return (mode != 0) ? &mode->mBase : 0;
}
class cObjectTemplateDB
{
public:
    VIRT4(a) VIRT4(b) VIRT4(c) VIRT4(d) VIRT4(e) VIRT4(f)
    virtual void Unregister(void* entry);                                  // +0x60 (ret 4)
};
cObjectTemplateDB* ObjectTemplateDB();                                     // 0x0067cb40
class cBioElemSort
{
public:
    void* Func_bb9b80();                                                   // 0x00bb9b80
    int   Func_bb9ae0();                                                   // 0x00bb9ae0
    int   GetAvatar();                                                     // 0x00b1fdb0
};
class cStarManager
{
public:
    cEmpire* GetEmpireByID(int id);                                        // 0x00ba9370 (ret 4)
};
cStarManager* StarManager();                                               // 0x00b3d2a0
struct PlanetTemplateRef { uint32_t mKey; uint32_t mField04; uint32_t mField08; };
struct PlanetTemplateVec { PlanetTemplateRef* mpBegin; PlanetTemplateRef* mpEnd; };
struct cPlanetRecord
{
    char pad00[0xd0];
    PlanetTemplateRef* mTemplatesBegin;                                    // +0xd0
    PlanetTemplateRef* mTemplatesEnd;                                      // +0xd4
    char padD8[0x15c - 0xd8];
    PlanetTemplateVec** mExtraBegin;                                       // +0x15c
    PlanetTemplateVec** mExtraEnd;                                         // +0x160
    cBioElemSort* SortBanners();                                           // 0x00b8de30
};
// ---- items of slice s00fddba0 end

// ---- items of slice s00fdeac0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t DAT_015b4050;                   // 0x015b4050
extern "C" void* FUN_0067de00();                // 0x0067de00
extern "C" void* FUN_0067dd40();                // 0x0067dd40
extern "C" void* MessageServerGet();            // 0x00883860 (EA::Messaging::GetServer)
typedef unsigned int size_t_;
void* operator new[](size_t_ n, const char* pName, int flags, unsigned debugFlags, const char* file, int line);  // 0x00f473a0
inline void* operator new(size_t_, void* p) { return p; }
struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
    bool operator==(const ResourceKey& b) const
    {
        return instanceID == b.instanceID && typeID == b.typeID && groupID == b.groupID;
    }
    bool operator!=(const ResourceKey& b) const { return !(*this == b); }
};
namespace eastl {
class allocator_s00fd_eac0 { public:
    void* allocate(size_t_ n) { return operator new[](n, "Simulator", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1); }
    void deallocate(void* p) { operator delete[](p); }
};
}
namespace eastl {
struct ListNodeBase_s00fd_eac0 {
    ListNodeBase_s00fd_eac0* mpNext;
    ListNodeBase_s00fd_eac0* mpPrev;
    void insert(ListNodeBase_s00fd_eac0* pNext)
    {
        mpNext = pNext;
        mpPrev = pNext->mpPrev;
        pNext->mpPrev->mpNext = this;
        pNext->mpPrev = this;
    }
};
}
namespace eastl {
template <typename T>
struct ListNode_s00fd_eac0 : public ListNodeBase_s00fd_eac0 {
    T mValue;
};
}
namespace eastl {
template <typename T>
struct ListIterator {
    ListNode_s00fd_eac0<T>* mpNode;
    ListIterator(ListNode_s00fd_eac0<T>* p) : mpNode(p) {}
    T& operator*() const { return mpNode->mValue; }
    ListIterator& operator++() { mpNode = (ListNode_s00fd_eac0<T>*)mpNode->mpNext; return *this; }
    bool operator==(const ListIterator& b) const { return mpNode == b.mpNode; }
    bool operator!=(const ListIterator& b) const { return mpNode != b.mpNode; }
};
}
namespace eastl {
template <typename T>
class list_s00fd_eac0 {
public:
    typedef ListNode_s00fd_eac0<T> node_type;
    typedef ListIterator<T> iterator;
    ListNodeBase_s00fd_eac0 mNode;
    allocator_s00fd_eac0 mAllocator;

    iterator begin() { return iterator((node_type*)mNode.mpNext); }
    iterator end() { return iterator((node_type*)&mNode); }

    void push_back(const T& value)
    {
        node_type* const pNode = DoCreateNode(value);
        pNode->insert(&mNode);
    }
    void clear()
    {
        DoClear();
        mNode.mpNext = &mNode;
        mNode.mpPrev = &mNode;
    }

    node_type* DoCreateNode(const T& value)
    {
        node_type* const pNode = (node_type*)mAllocator.allocate(sizeof(node_type));
        ::new(&pNode->mValue) T(value);
        return pNode;
    }
    void DoClear()
    {
        node_type* p = (node_type*)mNode.mpNext;
        while (p != (node_type*)&mNode) {
            node_type* const pTemp = p;
            p = (node_type*)p->mpNext;
            mAllocator.deallocate(pTemp);
        }
    }
};
}
namespace eastl {
template <typename InputIterator, typename T>
inline InputIterator find(InputIterator first, InputIterator last, const T& value)
{
    while ((first != last) && !(*first == value))
        ++first;
    return first;
}
}
namespace eastl {
struct rbtree_node_base_s00fd_eac0 {
    rbtree_node_base_s00fd_eac0* mpNodeRight;
    rbtree_node_base_s00fd_eac0* mpNodeLeft;
    rbtree_node_base_s00fd_eac0* mpNodeParent;
    char mColor;
};
}
struct cKeyMap {
    uint32_t mCompare;
    eastl::rbtree_node_base_s00fd_eac0 mAnchor;            // +0x04
    uint32_t mnSize;                            // +0x14
    cKeyMap();                                  // 0x00bf2c60
    ~cKeyMap() { DoNukeSubtree(mAnchor.mpNodeParent); }
    void DoNukeSubtree(eastl::rbtree_node_base_s00fd_eac0* pNode)   // out of line at 0x009a9600
    {
        while (pNode) {
            DoNukeSubtree(pNode->mpNodeRight);
            eastl::rbtree_node_base_s00fd_eac0* const pNodeLeft = pNode->mpNodeLeft;
            operator delete[](pNode);
            pNode = pNodeLeft;
        }
    }
    uint32_t Find(uint32_t key);                // 0x00bf9700
    void Insert(uint32_t key, uint32_t value);  // 0x00bf4a60
};
struct cMWModel_s00fd_eac0;
struct IModelWorldOwner {
virtual void v000();
virtual void v004();
virtual void v008();
virtual void v00c();
virtual void v010();
virtual void v014();
virtual void v018();
virtual void v01c();
virtual void v020();
virtual void v024();
virtual void v028();
virtual void v02c();
virtual void v030();
virtual void v034();
virtual void v038();
virtual void v03c();
virtual void v040();
virtual void v044();
virtual void v048();
virtual void v04c();
virtual void v050();
virtual void v054();
virtual void v058();
virtual void v05c();
virtual void v060();
virtual void v064();
virtual void v068();
virtual void v06c();
virtual void v070();
virtual void v074();
virtual void v078();
virtual void v07c();
virtual void v080();
virtual void v084();
virtual void v088();
virtual void v08c();
virtual void v090();
virtual void v094();
virtual void v098();
virtual void v09c();
virtual void v0a0();
virtual void v0a4();
virtual void v0a8();
virtual void v0ac();
virtual void v0b0();
virtual void v0b4();
virtual void v0b8();
virtual void v0bc();
virtual void v0c0();
virtual void v0c4();
virtual void v0c8();
virtual void v0cc();
virtual void v0d0();
virtual void v0d4();
virtual void v0d8();
virtual void v0dc();
virtual void v0e0();
virtual void v0e4();
virtual void v0e8();
virtual void v0ec();
virtual void v0f0();
virtual void v0f4();
virtual void v0f8();
virtual void v0fc();
virtual void v100();
virtual void v104();
virtual void v108();
virtual void v10c();
virtual void v110();
virtual void v114();
virtual void v118();
virtual void v11c();
virtual void v120();
virtual void v124();
virtual void v128();
virtual void v12c();
virtual void v130();
virtual void v134();
virtual void v138();
virtual void v13c();
virtual void v140();
virtual void v144();
virtual void v148();
virtual void v14c();
virtual void v150();
virtual void v154();
virtual void v158();
virtual void v15c();
virtual void v160();
virtual void v164();
virtual void v168();
    virtual void SetModelVisible(cMWModel_s00fd_eac0* model, bool visible);   // +0x16c
    virtual void DestroyModel(cMWModel_s00fd_eac0* model, bool owned);        // +0x170
};
struct cMWModel_s00fd_eac0 {
    IModelWorldOwner* mpWorld;                  // +0x00
    uint32_t mFlagBits : 31;                    // +0x04
    uint32_t mbOwned : 1;
    uint32_t pad08[14];
    int mnRefCount;                             // +0x40
    void AddRef() { mnRefCount++; }
    void Release()
    {
        if (mnRefCount > 1)
            --mnRefCount;
        else
            mpWorld->DestroyModel(this, mbOwned);
    }
};
template <class T>
struct AutoRefCount_s00fd_eac0 {
    T* mpObject;
    AutoRefCount_s00fd_eac0(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount_s00fd_eac0(const AutoRefCount_s00fd_eac0& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount_s00fd_eac0() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
typedef AutoRefCount_s00fd_eac0<cMWModel_s00fd_eac0> ModelPtr;
struct copy_impl_ModelPtr {
    static ModelPtr* do_copy(ModelPtr* first, ModelPtr* last, ModelPtr* result);   // 0x005f4e10
};
struct ModelVector_s00fd_eac0 {
    ModelPtr* mpBegin;
    ModelPtr* mpEnd;
    ModelPtr* mpCapacity;
    uint32_t mAllocator;

    void DoDestroyValues(ModelPtr* first, ModelPtr* last);       // 0x005f3680
    void DoInsertValue(ModelPtr* position, const ModelPtr& value);   // 0x00423c40

    ModelPtr* erase(ModelPtr* first, ModelPtr* last)
    {
        ModelPtr* const position = copy_impl_ModelPtr::do_copy(last, mpEnd, first);
        DoDestroyValues(position, mpEnd);
        mpEnd -= (last - first);
        return first;
    }
    void clear() { erase(mpBegin, mpEnd); }
    void push_back(const ModelPtr& value)
    {
        if (mpEnd < mpCapacity)
            ::new(mpEnd++) ModelPtr(value);
        else
            DoInsertValue(mpEnd, value);
    }
};
struct IModelWorld {
virtual void v00();
virtual void v04();
virtual void v08();
    virtual cMWModel_s00fd_eac0* LoadModel(uint32_t instanceID, uint32_t groupID, int flags);   // +0x0c
};
IModelWorld* GonzagoModelWorld_s00fd_eac0();               // 0x00b3d520
struct cPlantSpecies {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
    virtual const ResourceKey* GetModelKey();   // +0x18
};
struct cPlantSpeciesManager {
    cPlantSpecies* GetSpeciesFromID(const ResourceKey& id);   // 0x00b90410
};
cPlantSpeciesManager* PlantSpeciesManager();    // 0x00b3d420
struct BakeParameters {
    uint32_t mTag;
    int16_t mFlag;
    int16_t mPriority;
    BakeParameters(int16_t flag, int16_t priority, uint32_t tag)
    {
        mFlag = flag;
        mPriority = priority;
        mTag = tag;
    }
};
struct IBakeManager {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
    virtual bool IsBaked(const ResourceKey& nameKey, bool param);          // +0x1c
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
    virtual bool Cancel(uint32_t tag);                                      // +0x40
virtual void v44();
virtual void v48();
    virtual bool BakeModel(const ResourceKey& nameKey, const BakeParameters& params);   // +0x4c
};
IBakeManager* BakeManager();                    // 0x00401010
struct cCivData_s00fd_eac0;
struct cPlanetRecord_s00fd_eac0 {
    uint32_t pad00[0xbc / 4];
    ResourceKey* mPlantsBegin;                  // +0xbc  vector<ResourceKey>
    ResourceKey* mPlantsEnd;                    // +0xc0
    uint32_t size() const { return (uint32_t)(mPlantsEnd - mPlantsBegin); }
    void* GetTransitionData();                  // 0x00b8d9b0
    cCivData_s00fd_eac0* GetOwnerCiv();                    // 0x00b8de30
};
struct ITransitionTarget {
    void Enter();                               // 0x010727e0
};
ITransitionTarget* GetTransitionTarget(int a, int b);   // 0x010666a0
struct cBioProtector { const ResourceKey* GetKey(); };   // 0x00bb9b80
struct cStarRecordRef {
    uint32_t GetCommContext();                  // 0x00ce6950
    cBioProtector* GetBioProtector();           // 0x00b8de30
};
struct cPlanetItem {
    ResourceKey* mKeysBegin;                    // +0x00 vector<ResourceKey>
    ResourceKey* mKeysEnd;                      // +0x04
    int GetOwnerID();                           // 0x00ff0420
    void ApplyKeyMap(const cKeyMap& map);       // 0x00ff3190
    void SetActive(bool active);                // 0x00c37130
    char pad08[0x508 - 0x08];
    void* mpInterface508;                       // +0x508
};
struct PlanetItemVector {
    cPlanetItem** mpBegin;
    cPlanetItem** mpEnd;
    bool empty() const { return mpBegin == mpEnd; }
    int size() const { return (int)(mpEnd - mpBegin); }
};
struct cPlanet_s00fd_eac0 {
    uint32_t pad00[0x13c / 4];
    cStarRecordRef* mpStarRecord;               // +0x13c
    int GetPlanetType();                        // 0x00c70e00
    int GetPlanetKind();                        // 0x00c70880
    PlanetItemVector& GetItems();               // 0x00c71000
    cPlanetItem* GetItem(int index);            // 0x00c71030
    const ResourceKey* GetPlanetKey();          // 0x00c713e0
    void SetPlanetKey(const ResourceKey* key);  // 0x00c713c0
    bool IsHomePlanet();                        // 0x00c73250
};
struct cEmpire_s00fd_eac0;
namespace cSPLivingUniverse {
cPlanet_s00fd_eac0* GetActivePlanet_s00fd_eac0();                     // 0x01021260
}
namespace cSPLivingUniverse {
cPlanetRecord_s00fd_eac0* GetActivePlanetRecord();         // 0x010212a0
}
namespace cSPLivingUniverse {
cEmpire_s00fd_eac0* GetPlayerEmpire();                     // 0x01021300
}
void UniverseUpdateActive();                    // 0x01021230
struct cMission {
    cPlanetRecord_s00fd_eac0* GetTargetRecord(int which);  // 0x00bbaa60
    int GetState();                             // 0x00bb9ae0
    uint32_t GetEmpireID();                     // 0x00b1fdb0
};
cMission* ActiveMission();                      // 0x01021240
struct cHomePlanet {
    const ResourceKey* GetBannerKey();          // 0x00b8e090
};
struct cEmpire_s00fd_eac0 {
    cKeyMap GetKeyMap();                        // 0x00c352f0
    const ResourceKey* GetUFOKey();             // 0x00c326b0
    const ResourceKey* GetCityKey();            // 0x00c30f90
    cHomePlanet* GetHomePlanet();               // 0x00c31730
};
struct cStarManager_s00fd_eac0 {
    cMission* GetCurrentMission();              // 0x00ba70a0
    cEmpire_s00fd_eac0* GetEmpireByID(uint32_t id);        // 0x00ba9370
};
cStarManager_s00fd_eac0* StarManager_s00fd_eac0();                    // 0x00b3d2a0
struct cGameNounManager_s00fd_eac0 {
    int GetPlayerEmpireID();                    // 0x00b1f9d0
    void* GetGameDataVector(void*, void*, void*, void*, uint32_t);   // 0x00b21340 (ret 0x14)
};   // 0x00b3d300
cGameNounManager_s00fd_eac0* NounManager_s00fd_eac0();                // 0x00b3d300
struct AchievementsCtl { void AutoTest(uint32_t id, int value); };   // 0x00676e90
AchievementsCtl* AchievementsController();      // 0x00675250
struct cSPSimulatorSpaceGame_s00fd_eac0 { void FillKeyMap(cKeyMap& map); };   // 0x0102f5a0
struct cSPUISpace_s00fd_eac0 { void ShowBakeTimeSplash(); };   // 0x01065ab0
struct cSpaceUI {
    uint32_t pad00[5];
    cSPUISpace_s00fd_eac0* mpUISpace;                      // +0x14
    uint32_t pad18[14];
    uint32_t mFlags;                            // +0x50
    void DestroyNPC_UFOs(char, char, int);      // 0x01009470
    void FUN_01003230();                        // 0x01003230
    void FUN_010039c0(void* star);              // 0x010039c0
};
struct cPropertyList_s00fd_eac0 {
    virtual void v00();
    virtual void Release();                     // +0x04
    bool GetBool(uint32_t id);                  // 0x006a25a0
};
extern cPropertyList_s00fd_eac0* sAppProperties;           // 0x015fd918
bool GetPropertyAsKey(cPropertyList_s00fd_eac0* list_s00fd_eac0, uint32_t id, ResourceKey* dst);   // 0x006a1250
struct PropertyListPtr {
    cPropertyList_s00fd_eac0* mpObject;
    PropertyListPtr() : mpObject(0) {}
    ~PropertyListPtr() { if (mpObject) mpObject->Release(); }
    // COM-style out-parameter access: releases the current object first.
    cPropertyList_s00fd_eac0** operator&()
    {
        if (mpObject) {
            cPropertyList_s00fd_eac0* const p = mpObject;
            mpObject = 0;
            p->Release();
        }
        return &mpObject;
    }
    operator cPropertyList_s00fd_eac0*() const { return mpObject; }
};
struct IPropertyManager {
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
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, cPropertyList_s00fd_eac0** dst);   // +0x2c
};
IPropertyManager* PropertyManager();            // 0x0067de30
struct cPlanetModel_s00fd_eac0 {
    uint32_t pad00[9];
    void* mpISphere;                            // +0x24
    void Generate(const ResourceKey* key, int flags);   // 0x00b8d750
    const ResourceKey* GetPlanetKey();          // 0x00b7e380
};
cPlanetModel_s00fd_eac0* PlanetModel_s00fd_eac0();                    // 0x00b3d350
struct IMessageServer_s00fd_eac0 {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
    virtual void PostMSG(uint32_t id, void* data, void* sender);   // +0x14
};
IMessageServer_s00fd_eac0* MessageServer_s00fd_eac0();                // 0x0067dcc0
struct cPlanetVisits {
    int GetVisitCount(const ResourceKey* key);  // 0x0103ac40
    void SetVisitCount(const ResourceKey* key, int count);   // 0x0103fba0
};
cPlanetVisits* PlanetVisits();                  // 0x00b3d3d0
struct cSPUIEventLog {
    void PostFeedbackEvent(uint32_t a, uint32_t b, int c, int d, int e, int f);   // 0x00dd8640
};
cSPUIEventLog* EventLog_s00fd_eac0();                      // 0x00b3d3e0
struct cGameTimeManager_s00fd_eac0 { void IncPauseGate(uint32_t id); };   // 0x00b32220
cGameTimeManager_s00fd_eac0* GameTimeManager_s00fd_eac0();            // 0x00b3d380
struct cSPUILayoutCollection { void Show(); };  // 0x00801360
cSPUILayoutCollection* LayoutCollection();      // 0x0067cab0
struct cGameInputManager { uint32_t pad[0x110 / 4]; int mInputLock; };   // +0x110
cGameInputManager* GameInputManager_s00fd_eac0();          // 0x00b3d250
struct cTribeTool_s00fd_eac0 { void Refresh(uint32_t a, int b); };   // 0x00fe5430
struct cSpaceGameData { cTribeTool_s00fd_eac0* GetTool(); };   // 0x00bfc5f0
cSpaceGameData* SpaceGameGet_s00fd_eac0();                 // 0x01002bd0
struct cGonzagoTransition { void Begin(); };    // 0x00b7dec0
cGonzagoTransition* GonzagoTransition();        // 0x00b3d360
struct IRenderer {
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
    virtual bool IsLayerEnabled(int layer, bool flag);   // +0x60
};
IRenderer* Renderer();                          // 0x0067dd50
extern const ResourceKey kDefaultKey;           // 0x016d9950
struct KeyVector {
    ResourceKey* mpBegin;                       // +0x00
    ResourceKey* mpEnd;                         // +0x04
    ResourceKey* mpCapacity;                    // +0x08
    void DoInsertValue(ResourceKey* position, const ResourceKey& value);   // 0x004e3e10 (ret 8)
    void push_back(const ResourceKey& value)
    {
        if (mpEnd < mpCapacity)
            *mpEnd++ = value;
        else
            DoInsertValue(mpEnd, value);
    }
};
struct TransitionParams {
    void*       mpTargetData;                   // +0x00
    uint32_t    mTypeHash;                      // +0x04
    uint32_t    mField08;                       // +0x08
    uint32_t    pad0c[3];                       // +0x0c
    ResourceKey mEmpireKey;                     // +0x18
    uint32_t    mField24;                       // +0x24
    uint32_t    mField28;                       // +0x28
    uint32_t    mField2c;                       // +0x2c
    KeyVector   mKeys;                          // +0x30
};
TransitionParams* ResetTransitionParams();      // 0x00ef19f0
template <class T> struct PtrVec {
    T** mpBegin;
    T** mpEnd;
    T** mpCapacity;
};
template <class T> struct VecOut {
    uint32_t mPad00;
    PtrVec<T> mVec;                             // +0x04
};
struct cSolarSystem_s00fd_eac0 {
    void ActivateGraphics(int on);              // 0x00c86c70
};
struct cStar_s00fd_eac0 {
    cSolarSystem_s00fd_eac0* GetSolarSystem();             // 0x00c8b770
};
struct cCivData_s00fd_eac0 {
    const Vector3* GetCities();                 // 0x005c65e0
};
struct RenderMgr {
    char  pad00[0x6c];
    void* mpInterface6c;                        // +0x6c
    void FUN_01034810();                        // 0x01034810
    void Setup(int a, int kind);                // 0x01034950
    void FUN_01036590(void* planet);            // 0x01036590
    void UpdateSpaceColor(Vector3 color);       // 0x01036940
};
RenderMgr* GetRenderMgr();                      // 0x00b3d470
struct IdVector {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
};
struct cTutorialManager {
    IdVector* GetTargetEmpires();               // 0x010662c0
};
cTutorialManager* TutorialManager();            // 0x010666a0
struct cTutorialSystem {
    void StartModeTutorial(int a, uint32_t mode, int b);   // 0x00e3e350 (ret 0xc)
};
cTutorialSystem* TutorialSystem();              // 0x00b3d410
cStar_s00fd_eac0* FUN_01021230_s00fd_eac0();                          // 0x01021230 (active star)
void  FUN_01021740(void* planet);               // 0x01021740
void  FUN_01021960(int mode);                   // 0x01021960
extern "C" void* App_s00fd_eac0();                         // 0x0067dd10
#define VTP_s00fd_eac0(p)          (*(void***)(p))
#define VCP0(p,off)     (((void*(__thiscall*)(void*))             VTP_s00fd_eac0(p)[(off)/4])((void*)(p)))
#define VCB0(p,off)     (((bool(__thiscall*)(void*))             VTP_s00fd_eac0(p)[(off)/4])((void*)(p)))
#define VC1(p,off,a)    (((int (__thiscall*)(void*,int))          VTP_s00fd_eac0(p)[(off)/4])((void*)(p),(int)(a)))
#define VC2(p,off,a,b)  (((int (__thiscall*)(void*,int,int))      VTP_s00fd_eac0(p)[(off)/4])((void*)(p),(int)(a),(int)(b)))
struct PlanetLeaveMessage {
    void*    mpVtbl;                            // +0x00
    long     mRef;                              // +0x04
    void*    mpRecord;                          // +0x08
    uint32_t mField0c;                          // +0x0c
    uint32_t mField10;                          // +0x10
    uint32_t mField14;                          // +0x14
    uint32_t mField18;                          // +0x18
    uint32_t pad1c[5];                          // +0x1c
    uint32_t mField30;                          // +0x30
    uint32_t pad34;                             // +0x34
    uint32_t mField38;                          // +0x38
    uint32_t pad3c;                             // +0x3c
    void Destruct();                            // 0x00421cf0
};
struct Editor {
    char     pad00[0x74];
    void*    mpMgr;                             // +0x74
    char     pad78[0xb8 - 0x78];
    uint32_t mFieldB8;                          // +0xb8
    char     padBC[0xc4 - 0xbc];
    uint32_t mFieldC4;                          // +0xc4
    char     padC8[0xd4 - 0xc8];
    void*    mpCtl;                             // +0xd4
};
extern Editor* DAT_016c7aa4_s00fd_eac0;                    // 0x016c7aa4
namespace SP {
class cAppModeSpace_s00fd_eac0 { public:
    uint32_t pad000[0x144 / 4];
    ModelVector_s00fd_eac0 mPlantModels;                   // +0x144
    uint32_t pad154[2];
    cSpaceUI* mpSpaceUI;                        // +0x15c
    cSPSimulatorSpaceGame_s00fd_eac0* mSimulatorSpaceGame; // +0x160
    uint32_t mElapsedBakeTimeForTransitionMS;   // +0x164
    bool mBackgroundMapGenerationEnded;         // +0x168
    bool mBakingForPlanetEntryEnded;            // +0x169
    bool mDisabledRenderLayersForBaking;        // +0x16a
    uint32_t mLastBakedTag;                     // +0x16c
    eastl::list_s00fd_eac0<ResourceKey> mNeedsBakingForTransition;   // +0x170
    eastl::list_s00fd_eac0<bool> mOldRenderLayerStates;    // +0x17c
    char pad188[0x194 - 0x188];
    uint32_t mField194;                         // +0x194

    void TransitionFromSolarToPlanet();  // 0x00fdeac0 (SP::cAppModeSpace::TransitionFromSolarToPlanet)
    void OnPlanetRecordReady();                 // 0x00fdf5b0
    void EnterPlanetTransition();               // 0x00fdf5f0
    void ExitPlanetTransition();                // 0x00fdf8e0
    void TransitionFromPlanetToSolar(bool);     // 0x00fde3e0
    void AwardSpaceAchievements();              // 0x00fdbf90
};  // namespace SP
}
// ---- items of slice s00fdeac0 end

// ---- items of slice s00fe0570 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_slotMsgVtbl0;                                  // 0x013eb90c
extern void* g_slotMsgVtbl1;                                  // 0x013eb844
extern char kInterstellarDrive[];                             // 0x016d99a0
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
struct ResourceKey_s00fe_0570 {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};
struct ZeroKey : public ResourceKey_s00fe_0570 {
    ZeroKey() { instanceID = 0; typeID = 0; groupID = 0; }
};
void* operator new[](unsigned int n, const char* pName, int flags, unsigned int debugFlags, const char* pFile, int line);  // 0x00f473a0
namespace eastl {
struct ListNodeBase_s00fe_0570 {
    ListNodeBase_s00fe_0570* mpNext;
    ListNodeBase_s00fe_0570* mpPrev;
};
}
namespace eastl {
template <typename T>
struct ListNode_s00fe_0570 : public ListNodeBase_s00fe_0570 {
    T mValue;
};
}
namespace eastl {
template <typename T>
class list_s00fe_0570 { public:
    typedef ListNode_s00fe_0570<T> node_type;
    ListNodeBase_s00fe_0570 mNode;
    uint32_t mAllocator;

    void push_back(const T& value)
    {
        node_type* pNode = (node_type*)(new ("Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 209) char[sizeof(node_type)]);
        ::new ((void*)&pNode->mValue) T(value);
        pNode->mpNext = &mNode;
        pNode->mpPrev = mNode.mpPrev;
        mNode.mpPrev->mpNext = pNode;
        mNode.mpPrev = pNode;
    }
};
}
struct KeyNode {
    KeyNode* mpRight;
    KeyNode* mpLeft;
    KeyNode* mpParent;
    uint32_t mColor;
    uint32_t mKey;
    ResourceKey_s00fe_0570 mValue;
};
struct KeyMap {
    uint32_t mAllocator;     // +0x00
    KeyNode* mpAnchorRight;  // +0x04
    KeyNode* mpAnchorLeft;   // +0x08
    KeyNode* mpRoot;         // +0x0c
    uint8_t mColor;          // +0x10
    uint32_t mnSize;         // +0x14

    KeyMap();                                               // 0x00bf2c60
    void Set(uint32_t key, const ResourceKey_s00fe_0570& value);       // 0x00bf4a60  map[key] = value
    void Insert(uint32_t key);                              // 0x00bf9300  default-insert
    ResourceKey_s00fe_0570* Get(uint32_t key);                         // 0x00bf9700  find-or-insert, returns &value

    void DoNukeSubtree(KeyNode* pNode)
    {
        while (pNode) {
            DoNukeSubtree(pNode->mpRight);
            KeyNode* pLeft = pNode->mpLeft;
            operator delete[](pNode);
            pNode = pLeft;
        }
    }
    ~KeyMap() { DoNukeSubtree(mpRoot); }
};
struct cObjectTemplateDB_s00fe_0570 {
    PV8 PV8 PV4 PV2
    virtual void Register(const ResourceKey_s00fe_0570* key, int flag);  // +0x58
};
cObjectTemplateDB_s00fe_0570* ObjectTemplateDB_s00fe_0570();                        // 0x0067cb40
struct cTerrainSphere_s00fe_0570 {
    uint32_t pad00[0x1150 / 4];
    ResourceKey_s00fe_0570 mKey1150;                                     // +0x1150
    uint32_t pad115c[3];
    ResourceKey_s00fe_0570 mKey1168;                                     // +0x1168
};
struct cGameNounManager_s00fe_0570 {
    cTerrainSphere_s00fe_0570* GetCurrentTerrainSphere();                // 0x00f67d90
    void ProcessPending();                                    // 0x00b22960
};
cGameNounManager_s00fe_0570* NounManager_s00fe_0570();                              // 0x00b3d300
struct cModelEntity {
    void StoreModelKeys(const KeyMap* keys);                  // 0x00ff3190
};
struct cPlanetRecord_s00fe_0570 {
    uint32_t pad00[0x15c / 4];
    cModelEntity** mpEntitiesBegin;                           // +0x15c
    cModelEntity** mpEntitiesEnd;                             // +0x160
    uint32_t GetCommContext();                                // 0x00ce6950
    int GetEntry();                                           // 0x00b8dab0
    cModelEntity* GetEntity(int index);                       // 0x00b8dec0
};
cPlanetRecord_s00fe_0570* GetPlayerHomePlanet_s00fe_0570();                         // 0x01021370
void RegisterHomePlanet(cPlanetRecord_s00fe_0570* home, int entry);      // 0x00b96f40 (cdecl)
struct cEmpire_s00fe_0570 {
    char* GetData();                                          // 0x00c30c80
};
cEmpire_s00fe_0570* GetPlayerEmpire_s00fe_0570();                                   // 0x01021300
void* Unused_b3d460();                                        // 0x00b3d460
struct IBox {
    PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV4
    virtual void SetWorldBounds(const Vector3* box, float a, float b);  // +0x150
};
IBox* GonzagoModelWorld_s00fe_0570();                                    // 0x00b3d520
struct BakeParam {
    uint32_t mContext;
    uint16_t mA;
    uint16_t mB;
};
struct cPropertyList_s00fe_0570 {
    int GetIntProperty(uint32_t id);                          // 0x006a2660
};
extern cPropertyList_s00fe_0570* sAppProperties_s00fe_0570;                         // 0x015fd918
struct cPlanetModel_s00fe_0570 {
    float GetMinAltitude();                                   // 0x00b7e4d0
};
cPlanetModel_s00fe_0570* PlanetModel_s00fe_0570();                                  // 0x00b3d350
struct cCameraSettings {
    float GetRadiusFactor();                                  // 0x00a0ab60
};
cCameraSettings* CameraSettings();                            // 0x00c37360
struct cTimeOfDay {
    void GetSunPosition(Vector3* out);                        // 0x00bc2c00
};
cTimeOfDay* TimeOfDayInstance();                              // 0x00bc30b0
struct cPlayerUFO {
    void SetAltitude(float altitude);                         // 0x00c3daa0
    void PopToDestination();                                  // 0x00c37e60
    float GetFloat();                                         // 0x00c3ae70
    void ApplyKey(const ResourceKey_s00fe_0570* key);                    // 0x00c381e0
};
struct cSimThing {
    void Notify(uint32_t id);                                 // 0x00b5cde0
};
cSimThing* SimSystem();                                       // 0x00b3d230
struct cSPUISpace_s00fe_0570 {
    void ShowBakeTimeSplash();                                // 0x01065ab0
};
struct cNamed40 {
    void SetName(const void* name);                           // 0x00ff4840
};
struct cSPSimulatorSpaceGame_s00fe_0570 {
    uint32_t pad00[0x14 / 4];
    cSPUISpace_s00fe_0570* mpUI;                                         // +0x14
    uint32_t pad18[(0x40 - 0x18) / 4];
    cNamed40* mpField40;                                      // +0x40
    uint32_t pad44[(0x50 - 0x44) / 4];
    uint32_t mFlags;                                          // +0x50
    void StepA();                                             // 0x01003490
    void StepB();                                             // 0x01003a50
    void StepC();                                             // 0x01003690
};
struct cSPSimulatorPlayerUFO_s00fe_0570 {
    cPlayerUFO* GetPlayerUFO();                               // 0x00a1ad60
    void InitForPlanet();                                     // 0x00ffd390
    void SetPlanetDestination(Vector3* pos, bool a, bool b, bool c, bool d);  // 0x00ffc350
};
cSPSimulatorPlayerUFO_s00fe_0570* SpaceGame();                           // 0x00ffbe50
struct cPlanet_s00fe_0570 {
    void Refresh1();    // 0x00c73ff0
    void Refresh2();    // 0x00c74280
    void Refresh3(int a);  // 0x00c73cf0
    void Restart();     // 0x00c6ffa0
};
cPlanet_s00fe_0570* GetActivePlanet_s00fe_0570();                                   // 0x01021260
struct SlotMessage {
    void* vptr;           // +0x00
    long mRef;            // +0x04
    uint32_t pad08[2];
    uint32_t mTarget;     // +0x10
    uint32_t pad14[7];
    uint32_t mData30;     // +0x30
    uint32_t pad34;
    uint32_t mData38;     // +0x38
    uint32_t pad3c;

    SlotMessage()
    {
        mData30 = 0;
        vptr = &g_slotMsgVtbl0;
        _InterlockedExchange(&mRef, 0);
        vptr = &g_slotMsgVtbl1;
        mData38 = 0;
    }
    void Destruct();                                          // 0x00421cf0
    ~SlotMessage() { Destruct(); }
};
struct IMessageServer_s00fe_0570 {
    PV4 PV
    virtual void Post(uint32_t id, SlotMessage* msg, int flag);  // +0x14
};
IMessageServer_s00fe_0570* MessageServer_s00fe_0570();                              // 0x0067dcc0
struct IInputManager {
    PV8 PV8 PV8
    virtual bool IsControlActive(int control, int flag);      // +0x60
};
IInputManager* InputManager();                                // 0x0067dd50
struct cGameTimeManager_s00fe_0570 {
    void IncPauseGate(uint32_t id);                           // 0x00b32220
};
cGameTimeManager_s00fe_0570* GameTimeManager_s00fe_0570();                          // 0x00b3d380
int MissionIndexFromFloat(float f);                           // 0x01021240 (cdecl)
void MakeKeyFromIndex(ResourceKey_s00fe_0570* out, int index);           // 0x0105c5d0 (cdecl)
class cAppModeSpace_s00fe_0570 {
public:
    uint32_t pad000[0x7c / 4];
    ResourceKey_s00fe_0570 mUFOKey;                                      // +0x7c
    uint32_t pad88[(0x15c - 0x88) / 4];
    cSPSimulatorSpaceGame_s00fe_0570* mpSimulatorSpaceGame;              // +0x15c
    uint32_t pad160;
    uint32_t mElapsedBakeTimeForTransitionMS;                 // +0x164
    uint8_t pad168;
    bool mbBakeStarted;                                       // +0x169
    bool mBakingForPlanetEntryEnded;                          // +0x16a
    uint8_t pad16b;
    uint32_t mCommContext;                                    // +0x16c
    eastl::list_s00fe_0570<ResourceKey_s00fe_0570> mNeedsBakingForTransition;       // +0x170
    eastl::list_s00fe_0570<bool> mInputFlags;                            // +0x17c
    uint8_t pad188[0x18e - 0x188];
    bool mbTutorial;                                          // +0x18e

    void LoadNewGamePlanet();                                 // 0x00fdc240
    void AddBakeKey(const BakeParam* p, const ResourceKey_s00fe_0570* key);  // 0x00fdd320
    void SetPlanetTimeOnFirstEntry();                         // 0x00fda530
    void Func_fda750();                                       // 0x00fda750
    void Func_fdf9f0();                                       // 0x00fdf9f0

    void InitSpaceMode();  // 0x00fe0570 (cAppModeSpace::InitSpaceMode)
};
// ---- items of slice s00fe0570 end

// ---- items of slice s00fe2ab0 begin (TODO(rewrite): local stubs, replace by canonical classes)
enum eGameModeTag {
    kModeCiv     = 0x1654c04,   // civilization
    kModeSpace   = 0x1654c05,   // space
    kModeTribe   = 0x1654c06,   // tribe
    kModeColony  = 0x1654c08,   // colony
    kModeEditor  = 0xdbdba1,    // editor
    kModePlanetView = 0x1654c10,  // planet/space view (no pre-entry hook)
    kModeUnknown = 0x2ccd1d2,   // unknown / cancelled transition (-1 shares this arm)
};
enum eRecordType {
    kTypeCreature = 0x66787bc,  // creature/species record
    kTypePlanetA  = 0x7ce1750,  // planet record
    kTypePlanetB  = 0x7ce3cb0,  // planet record (alternate class)
};
struct Key {
    uint32_t mTypeID;           // +0x00
    uint32_t mGroupID;          // +0x04
    uint32_t mInstanceID;       // +0x08
    Key() : mTypeID(0), mGroupID(0), mInstanceID(0) {}
};
struct ISubsystem;                                   // cAppModeSpace +4 (cGonzagoSubsystem)
struct IMessageServer_s00fe_2ab0 {
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
    virtual void s10();
    virtual void PostMSG(uint32_t id, int32_t a, int32_t b);                   // +0x14
virtual void s18();
virtual void s1c();
    virtual void s20();
    virtual void AddListener(ISubsystem* handler, uint32_t id);                // +0x24
};
class AutoHandler {
 public:
    __forceinline void AddHandler(IMessageServer_s00fe_2ab0* server, ISubsystem* handler, const uint32_t* ids, uint32_t count)
    {
        mpServer = server;
        mpHandler = handler;
        mpIdArray = ids;
        mnIdArrayCount = count;
        mnPriority = 0;
        if (mpServer && mpHandler) {
            for (uint32_t i = 0; i < count; ++i)
                mpServer->AddListener(mpHandler, mpIdArray[i]);
        }
    }

    IMessageServer_s00fe_2ab0* mpServer;          // +0x00
    ISubsystem* mpHandler;             // +0x04
    const uint32_t* mpIdArray;         // +0x08
    uint32_t mnIdArrayCount;           // +0x0c
    int32_t mnPriority;                // +0x10
};
struct ISubsystem {
    virtual int AddRef();                                                      // +0x00
    virtual bool HandleMessage(uint32_t messageID, void* pMsg);                // +0x04
    virtual int Release();                                                     // +0x08
virtual void s0c();
virtual void s10();
virtual void s14();
    virtual void PostGameModeTransition(int32_t oldMode, int32_t newMode);     // +0x18
    void Fn_00ac8cd0(void* p, int32_t a);                                      // 0xac8cd0
};
struct IEffectsManager_s00fe_2ab0 {
virtual void e00();
virtual void e04();
virtual void e08();
virtual void e0c();
virtual void e10();
virtual void e14();
virtual void e18();
virtual void e1c();
virtual void e20();
virtual void e24();
virtual void e28();
virtual void e2c();
virtual void e30();
virtual void e34();
virtual void e38();
virtual void e3c();
virtual void e40();
virtual void e44();
virtual void e48();
virtual void e4c();
virtual void e50();
virtual void e54();
virtual void e58();
virtual void e5c();
virtual void e60();
virtual void e64();
virtual void e68();
virtual void e6c();
virtual void e70();
virtual void e74();
virtual void e78();
virtual void e7c();
virtual void e80();
virtual void e84();
virtual void e88();
virtual void e8c();
virtual void e90();
virtual void e94();
    virtual void Preload(uint32_t id, bool bWarm);                             // +0x98
};
struct IConfigManager_s00fe_2ab0 {
virtual void c00();
virtual void c04();
virtual void c08();
virtual void c0c();
virtual void c10();
virtual void c14();
virtual void c18();
virtual void c1c();
virtual void c20();
virtual void c24();
virtual void c28();
virtual void c2c();
    virtual void* GetPropertyList(uint32_t id);                                // +0x30
};
struct IGameInputManager_s00fe_2ab0 {
virtual void g00();
virtual void g04();
virtual void g08();
virtual void g0c();
virtual void g10();
virtual void g14();
virtual void g18();
virtual void g1c();
virtual void g20();
virtual void g24();
virtual void g28();
virtual void g2c();
virtual void g30();
virtual void g34();
    virtual void SetMode(int32_t mode);                                        // +0x38
};
struct ICurMgr {
    bool FindLocal(uint32_t id);                                               // 0x801bb0
};
struct IEventLog {
    void ClearEvents();                                                        // 0xdd6d70
};
struct ISpaceModeManager {
    bool IsReady();                                                            // 0xe36fa0
    void SetPendingMode(int32_t a, int32_t b);                                 // 0xe3e350
};
struct IMgr230 {
    void Fn_00b5cde0(uint32_t id);                                             // 0xb5cde0
};
struct IMgr320 {
    void Fn_00b1dfc0();                                                        // 0xb1dfc0
};
struct cSpaceEffect {
    void Fn_010727e0(int32_t a, int32_t b);                                    // 0x10727e0
};
struct cSpaceUI_s00fe_2ab0 {
    char pad00[0x204];
    int32_t mnState;                           // +0x204
};
struct cSelection {
    virtual void v00();                        // +0x00
    virtual void v04();                        // +0x04
    virtual int Release();                     // +0x08
    char pad04[0x0c - 0x04];
    uint32_t mnType;                           // +0x0c
    char pad10[0x18 - 0x10];
    Key mKey;                                  // +0x18
    char pad24[0x44 - 0x24];
    bool mbHandled;                            // +0x44
};
struct cSpaceGameState {
    char pad00[0x14];
    cSpaceEffect* mpEffect;                    // +0x14
    char pad18[0x20 - 0x18];
    cSpaceUI_s00fe_2ab0* mpUI;                            // +0x20
    cSelection* mpSelection;                   // +0x24
    void Fn_010030c0();                        // 0x10030c0
};
struct PtrVector {
    void** mpBegin;                            // +0x00
    void** mpEnd;                              // +0x04
};
struct ICivilization {
    void Fn_00bebdd0(const Key& key);                                          // 0xbebdd0
};
struct cGameNounManager_s00fe_2ab0 {
    ICivilization* GetPlayerCivilization();                                    // 0xb25fb0
    PtrVector* Fn_00ace2c0();                                                  // 0xace2c0
};
struct IEmpire {
    void Fn_00c30fa0();                                                        // 0xc30fa0
};
struct ISpeciesManager {
    void SetAvatarSpecies(const Key& key);                                     // 0x4df310
};
namespace SP {
struct cTestSystem {
    struct ListNode { ListNode* mpNext; ListNode* mpPrev; };
    char pad00[0x70];
    ListNode mTests;                           // +0x70
    bool IsTestingInProgress() const { return mTests.mpNext != &mTests; }
};
}
namespace SP {
struct cAppProperties {
    char pad00[0x00];
    void SetBoolProperty(uint32_t id, bool bValue);                            // 0x6a17e0
};
}
namespace SP {
extern cTestSystem* sTestSystem;               // 0x15fd928
}
namespace SP {
extern cAppProperties* sAppProperties_s00fe_2ab0;         // 0x15fd918
}
namespace SP {
extern const uint32_t kHandlerIDs[];           // 0x1494170 20 message ids
}
namespace SP {
ISubsystem* __cdecl Subsystem1();              // 0xb3d460
}
namespace SP {
ISubsystem* __cdecl Subsystem2();              // 0xb3d480
}
namespace SP {
ISubsystem* __cdecl StarManager_s00fe_2ab0();             // 0xb3d2a0
}
namespace SP {
ISpaceModeManager* __cdecl SpaceModeManager(); // 0xb3d410
}
namespace SP {
IMgr230* __cdecl Fn_00b3d230();                // 0xb3d230
}
namespace SP {
IMgr320* __cdecl Fn_00b3d320();                // 0xb3d320
}
namespace SP {
cGameNounManager_s00fe_2ab0* __cdecl NounManager_s00fe_2ab0();       // 0xb3d300
}
namespace SP {
IEventLog* __cdecl EventLog_s00fe_2ab0();                 // 0xb3d3e0
}
namespace SP {
IGameInputManager_s00fe_2ab0* __cdecl GameInputManager_s00fe_2ab0(); // 0xb3d250
}
namespace SP {
IEffectsManager_s00fe_2ab0* __cdecl EffectsManager_s00fe_2ab0();     // 0x67ddd0
}
namespace SP {
IMessageServer_s00fe_2ab0* __cdecl MessageServer_s00fe_2ab0();       // 0x67dcc0
}
namespace SP {
IConfigManager_s00fe_2ab0* __cdecl ConfigManager_s00fe_2ab0();       // 0x67dd30
}
namespace SP {
ICurMgr* __cdecl CurMgr();                     // 0x67cab0
}
namespace SP {
bool __cdecl IsWorldLayoutFlagSet(int32_t flag);          // 0x685520
}
namespace SP {
void __cdecl Fn_00bf55d0();                    // 0xbf55d0
}
namespace SP {
void __cdecl Fn_00ba5650(const Key* key, int32_t a);       // 0xba5650
}
namespace SP {
void __cdecl Fn_00ba5bc0(void* p);             // 0xba5bc0
}
namespace SP {
IEmpire* __cdecl GetPlayerEmpire(int32_t index);           // 0x1021300
}
namespace SP {
IEmpire* __cdecl GetPlayerEmpire(const Key& key);          // 0x1021300
}
namespace SP {
ISpeciesManager* __cdecl SpeciesManager_s00fe_2ab0();     // 0x401090
}
namespace SP {
void __cdecl CommEvent(uint32_t id, void* p, const Key& a, const Key& b,
                       void* ctx, int32_t c, const Key& d, const Key& f); // 0xe39ab0
}
class cModeTransition {
 public:
virtual void t00();
virtual void t04();
virtual void t08();
virtual void t0c();
virtual void t10();
virtual void t14();
virtual void t18();
virtual void t1c();
    virtual int32_t GetPostModeTransitionState();                              // +0x20
virtual void t24();
virtual void t28();
virtual void t2c();
virtual void t30();
virtual void t34();
virtual void t38();
virtual void t3c();
    virtual void t40();
    virtual void BeginPostGameModeTransition(int32_t newMode);                 // +0x44
    virtual void t48();
    virtual void EndPostGameModeTransition();                                  // +0x4c

    void PostGameModeTransition(int32_t oldMode, int32_t newMode);             // 0xfe2ab0
};
struct IModeStrategy {
    virtual void m00();                        // +0x00
};
class cAppModeSpace_s00fe_2ab0 : public IModeStrategy, public ISubsystem, public cModeTransition {
 public:
    void TransitionFromEditorToPlanet();       // 0xfdc800
    void Fn_00fdb9a0();                        // 0xfdb9a0
    void SetDefaultPickPriority();             // 0xfddba0
    void LoadStateMachine(void* pProperties);   // 0xfe1a20

    char pad0c[0x8c - 0x0c];
    AutoHandler mAutoHandler;                  // +0x8c
    char pad_a0[0x131 - 0xa0];
    bool mbFlag131;                            // +0x131
    char pad132[0x15c - 0x132];
    cSpaceGameState* mpSpaceState;             // +0x15c
    char pad160[0x18e - 0x160];
    bool mbFlag18e;                            // +0x18e
    bool mbFlag18f;                            // +0x18f
    bool mbFlag190;                            // +0x190
    bool mbFlag191;                            // +0x191
    bool mbFlag192;                            // +0x192
};
// ---- items of slice s00fe2ab0 end

// ---- items of slice s010414c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct VtblTable { void* mSlots[0x100]; };
typedef void* (__thiscall *VfnP)(void*);
void* __cdecl App_s0104_14c0();                                                                  // 0x0067dd10
void* __cdecl GetUFOSimulator_s0104_14c0();                                                      // 0x00ffbe50
void* __cdecl CommManager();                                                           // 0x00b3d4a0
void* __cdecl GameTimeManager_s0104_14c0();                                                       // 0x00b3d380
void* __stdcall NounManagerArg(uint32_t id);                                           // 0x00b3d300 (callee pops)
bool  __cdecl FUN_01068350(void* self);                                                // 0x01068350
bool  __cdecl FUN_00ff3bf0(void* self);                                                // 0x00ff3bf0
struct TerrainSphere {
    bool IsInTerrainSphere(void* arg);   // 0x00c772c0 (callee pops the argument)
    bool HasFlagOrInsert(void* arg);     // 0x00c77bf0
};
struct TerrainEditor {
    void* GetCurrentTerrainSphere();
};
struct CommScreen {
    bool IsActive();
};
struct GameTimeMgr {
    uint8_t mPad00[0x48];
    uint8_t mFlags48;
};
struct GameObj74 {
    void* mPad00;
    VtblTable* mpVtbl;             // not used: methods called directly
    bool FUN_01068350();
    bool FUN_00ff3bf0();
};
struct UFOSim {
    void* GetPlayerInventory();
};
struct UFOData {
    int AddRef();
};
struct Inventory {
    uint8_t mPad00[0x74c];
    uint8_t mFlag74C;              // +0x74c
    bool CanEnterPlanetContext();
    bool FUN_00ff3bf0();
};
typedef bool (__thiscall *VfnBUI)(void* self, uint32_t arg);
inline bool InvHasWormhole(Inventory* inv)
{
    return ((VfnBUI)(*(void***)inv)[0x74 / 4])(inv, 0x16dfbc4);
}
typedef int (__thiscall *VfnIUI)(void* self, uint32_t arg);
inline bool InTerrainSphere(uint32_t id)
{
    TerrainSphere* sphere =
        (TerrainSphere*)((TerrainEditor*)NounManagerArg(id))->GetCurrentTerrainSphere();
    return sphere->IsInTerrainSphere((void*)id);
}
// ---- items of slice s010414c0 end

// ---- items of slice s00fe0570_g7 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
struct ListNodeBase_s00fe_0570__g7 {
    ListNodeBase_s00fe_0570__g7* mpNext;
    ListNodeBase_s00fe_0570__g7* mpPrev;
};
}
namespace eastl {
template <typename T>
struct ListNode_s00fe_0570__g7 : public ListNodeBase_s00fe_0570__g7 {
    T mValue;
};
}
namespace eastl {
template <typename T>
class list_s00fe_0570__g7 { public:
    typedef ListNode_s00fe_0570__g7<T> node_type;
    ListNodeBase_s00fe_0570__g7 mNode;
    uint32_t mAllocator;

    void clear()
    {
        node_type* pNode = (node_type*)mNode.mpNext;
        while (pNode != (node_type*)&mNode) {
            node_type* pCur = pNode;
            pNode = (node_type*)pNode->mpNext;
            operator delete[](pCur);
        }
        mNode.mpNext = &mNode;
        mNode.mpPrev = &mNode;
    }
};
}
struct IMessageServer_s00fe_0570__g7 {
    PV4 PV
    virtual void Post(uint32_t id, SlotMessage* msg, int flag);  // +0x14
    virtual void PostEx(uint32_t id, int a, int b, int c);       // +0x18
};
IMessageServer_s00fe_0570__g7* MessageServer_s00fe_0570__g7();                              // 0x0067dcc0
struct cSPUISpace_s00fe_0570__g7 {
    void ShowBakeTimeSplash();                                // 0x01065af0
};
struct cStar;
struct cSPSimulatorSpaceGame_s00fe_0570__g7 {
    uint32_t pad00[0x14 / 4];
    cSPUISpace_s00fe_0570__g7* mpUI;                                         // +0x14
    uint32_t pad18[(0x40 - 0x18) / 4];
    void* mpField40;                                          // +0x40
    uint32_t pad44[(0x50 - 0x44) / 4];
    uint32_t mFlags;                                          // +0x50

    void DestroyNPC_UFOs(char a, char b, int c);              // 0x01009470
    void FUN_010039c0(cStar* star);                           // 0x010039c0
    void StepC();                                             // 0x01003690
    void ChaseFromSolarToPlanet();                            // 0x01007bf0
};
struct cSPSimulatorPlayerUFO_s00fe_0570__g7 {
    void InitForPlanet();                                     // 0x00ffd390
};
cSPSimulatorPlayerUFO_s00fe_0570__g7* GetUFOSimulator_s00fe_0570__g7();                     // 0x00ffbe50
struct cPlanet_s00fe_0570__g7;
cPlanet_s00fe_0570__g7* GetActivePlanet_s00fe_0570__g7();                                   // 0x01021260
struct cTerrainSphere_s00fe_0570__g7 {
    void FUN_00c77bf0(uint32_t flag);                         // 0x00c77bf0
};
struct cGameNounManager_s00fe_0570__g7 {
    cTerrainSphere_s00fe_0570__g7* GetCurrentTerrainSphere();                // [this+0x74]
    void ProcessPending();                                    // 0x00b22960
};
cGameNounManager_s00fe_0570__g7* NounManager_s00fe_0570__g7();                              // 0x00b3d300
struct cPlanetModel_s00fe_0570__g7 {
    uint32_t pad00[0x24 / 4];
    uint32_t mField24;                                        // +0x24
    void FUN_00b8d750(int value);                             // 0x00b8d750
    int GetPlanetKey();                                       // 0x00b7e380
    void Refresh();                                           // 0x00b88420
};
cPlanetModel_s00fe_0570__g7* PlanetModel_s00fe_0570__g7();                                  // 0x00b3d350
struct cPlanet_s00fe_0570__g7 {
    int FUN_00c713e0(int flag);                               // 0x00c713e0
    void FUN_00c713c0(int key);                               // 0x00c713c0
};
struct cThingB3D360 {
    void FUN_00b7dec0();                                      // 0x00b7dec0
};
cThingB3D360* FUN_00b3d360_s00fe_0570__g7();                                 // 0x00b3d360
struct cThingB3D310 {
    void FUN_00b515e0();                                      // 0x00b515e0
};
cThingB3D310* FUN_00b3d310_s00fe_0570__g7();                                 // 0x00b3d310
class cAppModeSpace_s00fe_0570__g7 {
public:
    uint32_t pad000[0x15c / 4];
    cSPSimulatorSpaceGame_s00fe_0570__g7* mpSimulatorSpaceGame;              // +0x15c
    uint32_t pad160;
    uint32_t mElapsedBakeTimeForTransitionMS;                 // +0x164
    uint8_t pad168;
    bool mbBakeStarted;                                       // +0x169
    bool mBakingForPlanetEntryEnded;                          // +0x16a
    uint8_t pad16b;
    uint32_t mCommContext;                                    // +0x16c
    uint8_t pad170[0x17c - 0x170];
    eastl::list_s00fe_0570__g7<bool> mInputFlags;                            // +0x17c

    void SetPlanetTimeOnFirstEntry();                         // 0x00fda530
    void FUN_00fdf9f0();                                      // 0x00fdf9f0

    void CompleteTransitionFromSolarToPlanet();  // 0x00fe0c60 (cAppModeSpace::CompleteTransitionFromSolarToPlanet)
    void FUN_00fe0e10();
};
// ---- items of slice s00fe0570_g7 end

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

// @ 0x00fd9de0
void AppMode::f9de0()
{
    void* m = FUN_01021240();
    char* es = (char*)m;
    int t = E(es)->FUN_00bb9ae0();
    if (t != 5) return;
    void* av = E(es)->FUN_00b1fdb0();
    int eid = FUN_01021090();
    if (av == (void*)eid) return;
    int eid2 = FUN_01021090();
    void* av2 = E(es)->FUN_00b1fdb0();
    void* rm = FUN_00b3d2c0();
    float f = ((float(__thiscall*)(void*, void*, int))VTP(rm)[0x00 + 0]) (rm, av2, eid2);
    (void)f;
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

// @ 0x00fd9ea0
void AppMode::f9ea0(int key, int param3)
{
    char* s = (char*)this;
    if (*(int*)(s + 0x15c) != 0 && *(int*)(*(int*)(s + 0x15c) + 0x20) != 0) {
        char c = (char)(int)E((void*)*(int*)(*(int*)(s + 0x15c) + 0x20))->FUN_00d09660();
        if (c) goto done;
    }
    if (key == 0x4c) {
        if (param3 != 0) goto done;
        void* cm = FUN_00b3d4a0();
        char c = (char)(int)E(cm)->FUN_00ae9390();
        if (c) goto done;
        void* t = FUN_00b3d3f0(-0xe);
        E(t)->FUN_00e190c0(-0xe);
    } else if (key == 0x52) {
        if (param3 != 0) goto done;
        void* cm = FUN_00b3d4a0();
        char c = (char)(int)E(cm)->FUN_00ae9390();
        if (c) goto done;
        void* t = FUN_00b3d3f0(-0xd);
        E(t)->FUN_00e190c0(-0xd);
    } else if (key == 0x59) {
        void* x = FUN_010666a0();
        char c = (char)(int)E(x)->FUN_01065e20();
        if (!c) {
            void* y = FUN_010666a0();
            E(y)->FUN_01067b60();
        }
    }
done:
    void* t2 = FUN_00b3d3f0(0);
    char c2 = (char)(int)E(t2)->FUN_00e18c70(0);
    if (c2) return;
    void* gi = FUN_00b3d250();
    char c3 = ((char(__thiscall*)(void*, int, int))VTP(gi)[0x44 / 4])(gi, key, param3);
    if (c3) return;
    gi = FUN_00b3d250();
    ((void(__thiscall*)(void*, int, int))VTP(gi)[0x4c / 4])(gi, key, param3);
}

// @ 0x00fd9f70
namespace SP {
void __thiscall cAppModeSpace::OnMouseUp()
{
}
}  // namespace SP

// @ 0x00fda1f0
void* __cdecl FUN_00b3d250();                        // 0x00b3d250 (input manager)
struct MouseInputState { void OnMouseDown(float x, float y, int button); };  // 0x00697b20
struct V5cMouse : B22 { virtual bool OnMouseMove(float x, float y, int button) = 0; };
namespace SP {
bool __thiscall cAppModeSpace::FUN_00fda1f0(float x, float y, int button)
{
    float oldX = *(float*)((char*)this + 0xf4);
    float oldY = *(float*)((char*)this + 0xf8);
    ((MouseInputState*)((char*)this + 0xc8))->OnMouseDown(x, y, button);
    bool result = ((V5cMouse*)FUN_00b3d250())->OnMouseMove(x, y, button);

    int context = FUN_01021080();
    if (context != 0) {
        if ((unsigned int)(context - 1) > 1)
            goto done;
        if (!*(bool*)((char*)this + 0xed) && !*(bool*)((char*)this + 0xee))
            goto done;
    } else {
        if (!((V18b*)FUN_00b3d250())->Probe(0xcdcdcdcd))
            goto done;
    }
    ((cSelf*)mpSpaceState)->FUN_01003c60(oldX - x, oldY - y);

done:
    *(bool*)((char*)this + 0x130) = true;
    return result;
}
}  // namespace SP

// @ 0x00fda2e0
void* __cdecl FUN_00b3d230();                        // 0x00b3d230
void* __stdcall FUN_00b3d390(void* a, void* b, int c); // 0x00b3d390
namespace SP {
bool __thiscall cAppModeSpace::FUN_00fda2e0(void* v)
{
    if (((cSPSpaceGameState*)mpSpaceState)->mpEffect == 0)
        return false;
    if (((cNounMgr*)FUN_00b3d380())->mFlags48 & 1)
        return false;
    if (((cSelf*)FUN_00b3d230())->FUN_00b5ca60())
        return true;
    if (!((cSelf*)((cSelf*)FUN_00ffbe50())->FUN_00a1ad60())->FUN_00c37170())
        return true;

    void* tool = ((cSelf*)mpSpaceState)->FUN_00a1ad60();
    tool = ((cSelf*)tool)->FUN_00ff3f00();
    if (tool != 0) {
        if (((cSelf*)tool)->FUN_0104f930() != 0) {
            ((uint32_t*)tool)[0x170 / 4] = 0;
            ((cSelf*)FUN_00b3d390(tool, v, 1))->FUN_01050bb0();
            mFlag18d = true;
            ((cSPSpaceGameState*)mpSpaceState)->FUN_01002be0();
        }
    }
    return true;
}
}  // namespace SP

// @ 0x00fda390
void* __cdecl FUN_00b3d450();                       // 0x00b3d450
void* __cdecl FUN_00b3d470();                       // 0x00b3d470 (entry manager)
void  __fastcall FUN_00b6c280(void* pObject);       // 0x00b6c280
void  __fastcall FUN_00c2e4e0(void* pObject);       // 0x00c2e4e0
void  __fastcall FUN_00bc3110(void* pTimer);        // 0x00bc3110 (stopwatch stop)
extern void* DAT_015b7328;                          // 0x015b7328
extern void* DAT_015b732c;                          // 0x015b732c
extern void* DAT_015b7334;                          // 0x015b7334
extern void* DAT_015b7338;                          // 0x015b7338
extern void* DAT_015b733c;                          // 0x015b733c
extern void* DAT_015b7340;                          // 0x015b7340
extern void* DAT_015b7344;                          // 0x015b7344
extern void* DAT_015b7348;                          // 0x015b7348
extern void* DAT_015b734c;                          // 0x015b734c
void* __cdecl FUN_0067de20();                       // 0x0067de20  cheat manager
struct V1cArg : B06 { virtual void Push(void* p) = 0; };   // +0x1c (1 arg)
namespace SP {
void __thiscall cAppModeSpace::Deactivate()
{
    FUN_00b6c280(this);
    FUN_00c2e4e0(FUN_00b3d450());

    void** ppA = (void**)((char*)FUN_00b3d470() + 0xa4);
    ((V0ci*)*ppA)->Reset(2);
    void** ppB = (void**)((char*)FUN_00b3d470() + 0x94);
    ((V0ci*)*ppB)->Reset(2);

    ((V50x*)FUN_0067dd50())->X50(0x17);

    void* pCheat = FUN_0067de20();
    ((V1cArg*)pCheat)->Push(DAT_015b7328);
    ((V1cArg*)pCheat)->Push(DAT_015b733c);
    ((V1cArg*)pCheat)->Push(DAT_015b7340);
    ((V1cArg*)pCheat)->Push(DAT_015b7344);
    ((V1cArg*)pCheat)->Push(DAT_015b7334);
    ((V1cArg*)pCheat)->Push(DAT_015b7338);
    ((V1cArg*)pCheat)->Push(DAT_015b7348);
    ((V1cArg*)pCheat)->Push(DAT_015b734c);

    FUN_00bc3110((char*)this + 0xa8);
}
}  // namespace SP

// @ 0x00fda480
extern "C" void* __cdecl operator_new(unsigned int nSize, const char* pTag, int nA, int nB, const char* pFile, int nLine); // 0x00f473a0
void* __fastcall FUN_00feacd0(void* pObject);       // 0x00feacd0 (ctor)
void  __fastcall FUN_00b6f4c0(void* pObject);       // 0x00b6f4c0
void  __cdecl    FUN_00c86640();                    // 0x00c86640
namespace SP {
void __thiscall cAppModeSpace::FUN_00fda480()
{
    void* pMem = operator_new(0xa28, DAT_013f09b4, 0, 0, 0, 0);
    cGonzagoSubsystem_s00fd_9f70* pNew;
    if (pMem != 0)
        pNew = (cGonzagoSubsystem_s00fd_9f70*)FUN_00feacd0(pMem);
    else
        pNew = 0;
    cGonzagoSubsystem_s00fd_9f70* pOld = mpGonzagoSubsystem;
    if (pNew != pOld) {
        if (pNew != 0)
            pNew->v04();
        mpGonzagoSubsystem = pNew;
        if (pOld != 0)
            pOld->Release();
    }
    FUN_00b6f4c0(mpGonzagoSubsystem);
    FUN_00c86640();
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
extern char  DAT_016dd440;                              // 0x016dd440
extern char  DAT_016dd3ff;                              // 0x016dd3ff
extern float DAT_01471064;                              // 0x01471064
namespace SP {
void __thiscall cAppModeSpace::SetPlanetTimeOnFirstEntry()
{
    void* modeMgr = ((V38*)((V50*)FUN_0067dd10())->GetModeManager())->Get14();
    if (modeMgr == 0)
        return;
    void* view = ((V0c*)modeMgr)->Query(0x303154cd);
    if (view == 0)
        return;
    if (!DAT_016dd440) {
        if (!DAT_016dd3ff)
            return;
    } else {
        if (!DAT_016dd3ff && cSPLivingUniverse::GetActivePlanet_s00fd_eac0()->IsHomePlanet())
            return;
    }
    cPlayerInventory* pInv = (cPlayerInventory*)((cSelf*)FUN_00ffbe50())->FUN_00a1ad60();
    V2cp* pBody = (V2cp*)&pInv->mBody;
    float f = ((cBC30*)FUN_00bc30b0())->m24;
    void* pos = pBody->GetPosition();
    ((cSelf*)FUN_00bc30b0())->FUN_00bc2f00(f * DAT_01471064, pos);
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
void* __cdecl FUN_01002bd0();                        // 0x01002bd0
void* __fastcall FUN_0102f710(void* pObject);        // 0x0102f710 (ctor)
struct V0c0 : B02 { virtual void v0c(); };           // +0x0c (no args)
namespace SP {
void __thiscall cAppModeSpace::FUN_00fda940()
{
    mFlag158 = true;

    cSPSpaceGameState* pNew = (cSPSpaceGameState*)FUN_01002bd0();
    cSPSpaceGameState* pOld = mpSpaceState;
    if (pNew != pOld) {
        if (pNew != 0)
            ((V04*)pNew)->Destroy();
        mpSpaceState = pNew;
        if (pOld != 0)
            ((V08*)pOld)->Unlink();
    }

    if (mpObj160 == 0) {
        void* pMem = operator_new(0x168, DAT_013f09b4, 0, 0, 0, 0);
        void* pNew2;
        if (pMem != 0)
            pNew2 = FUN_0102f710(pMem);
        else
            pNew2 = 0;
        void* pOld2 = mpObj160;
        if (pNew2 != pOld2) {
            if (pNew2 != 0)
                ((V08*)pNew2)->Unlink();
            mpObj160 = pNew2;
            if (pOld2 != 0)
                ((V0c0*)pOld2)->v0c();
        }
    }
}
}  // namespace SP

// @ 0x00fda9f0
namespace SP {
void __thiscall cAppModeSpace::FUN_00fda9f0()
{
    if (mpSpaceState != 0) {
        switch (FUN_01021080()) {
        case -1:
            return;
        case 0:
            ((cSPSpaceGameState*)mpSpaceState)->FUN_0100a960();
            break;
        case 1:
            ((cSPSpaceGameState*)mpSpaceState)->FUN_01009470(0, 0, 1);
            {
                cSPSpaceGameState* ss = (cSPSpaceGameState*)mpSpaceState;
                ss->FUN_010039c0(FUN_01021230());
            }
            break;
        case 2:
            ((cSPSpaceGameState*)mpSpaceState)->FUN_01009470(0, 0, 1);
            ((cSPSpaceGameState*)mpSpaceState)->FUN_01003620();
            break;
        }
    }
    FUN_01021960(-1);
    FUN_010219b0(0, 0);
}
}  // namespace SP

// @ 0x00fdaa90
namespace SP {
void __thiscall cAppModeSpace::Write()
{
}
}  // namespace SP

// @ 0x00fdab40
struct S4_s00fd_ab40   { uint32_t a; };
struct S8_s00fd_ab40   { S4_s00fd_ab40 a, b; };
struct S10_s00fd_ab40  { S8_s00fd_ab40 a, b; };
struct S20_s00fd_ab40  { S10_s00fd_ab40 a, b; };
struct S40_s00fd_ab40  { S20_s00fd_ab40 a, b; };
struct S80_s00fd_ab40  { S40_s00fd_ab40 a, b; };
struct S100_s00fd_ab40 { S80_s00fd_ab40 a, b; };
struct S200_s00fd_ab40 { S100_s00fd_ab40 a, b; };
struct S400_s00fd_ab40 { S200_s00fd_ab40 a, b; };
struct S800_s00fd_ab40 { S400_s00fd_ab40 a, b; };
struct Sa00_s00fd_ab40 { S800_s00fd_ab40 a; S200_s00fd_ab40 b; };
struct Sa14_s00fd_ab40 { Sa00_s00fd_ab40 a; S10_s00fd_ab40 b; S4_s00fd_ab40 c; };
struct V40q_s00fd_ab40 : B15 { virtual void* Get40(void* a); };  // +0x40 (1 arg -> ptr)
class cBigFrame_s00fd_ab40
{
public:
    cBigFrame_s00fd_ab40(void* a, void* b, void* c);  // 0x00692f90 (ctor)
    bool Test(void* arg);                             // 0x00693e10
    Sa14_s00fd_ab40 body;
};
namespace SP {
bool __thiscall cAppModeSpace::FUN_00fdab40(void* arg)
{
    void* p = FUN_01046fc0(arg);
    bool b = ((cSelf*)p)->FUN_01046f30();

    void* modeMgr = ((V50*)FUN_0067dd10())->GetModeManager();
    void* q = ((V40q_s00fd_ab40*)modeMgr)->Get40((void*)0x1103192);
    if (q != 0) {
        void* r = ((V0c*)q)->Query(0x303154cc);
        if (r != 0)
            b = b & ((cSelf*)r)->FUN_01017300(arg);
    }

    cBigFrame_s00fd_ab40 frame((char*)this - 8, (void*)0x15b4148, (void*)0x1a80d26);
    bool ok = frame.Test(arg);
    return ok && b;
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

// @ 0x00fdc340
void UpdateSpaceGrid(cAppModeSpace_s00fd_bd60* pMode, float fRadius, const Vec3* pCenter)
{
    void* pGrid = GetTerrainSphere();
    UpdateGridCells(pGrid, 0, fRadius);

    int nCount = 0;
    void* pCells = nullptr;
    if (nCount > 0) {
        for (int i = 0; i < nCount; ++i) {
            void* pCell = ((void**)pCells)[i];
            (void)pCell;
            bool bInside = true;
            float fDx = pCenter->mX - 0.0f;
            float fDy = pCenter->mY - 0.0f;
            float fDz = pCenter->mZ - 0.0f;
            if (bInside) {
                ResetGridHighlight();
                if (fDx * fDx + fDy * fDy + fDz * fDz < fRadius * fRadius)
                    DrawGridRing(0);
            }
        }
    }

    void* pOverlay = nullptr;
    UpdateGridOverlay(fRadius, 0, pOverlay);
    int nRings = 0;
    for (int i = 0; i < nRings; ++i)
        DrawGridRing(1);
    if (pOverlay != nullptr)
        operator_delete__(pOverlay);
    (void)pMode;
}

// @ 0x00fdc490
void cAppModeSpace_s00fd_bd60::StopEditorPlay()
{
    if (mbEditorPlaying != 0) {
        mbEditorPlaying = 0;
        RefreshModeUI();
    }
}

// @ 0x00fdc4b0
int* UnlinkListNode(int* pOut, int** ppNode)
{
    int* pNode = *ppNode;
    int* pNext = *(int**)((uint8_t*)pNode + 4);
    *(int*)pNext[1] = *pNext;
    *(int*)(*pNext + 4) = pNext[1];
    operator_delete__(pNext);
    *pOut = (int)(intptr_t)pNode;
    return pOut;
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

// @ 0x00fdc710
void cAppModeSpace_s00fd_bd60::TransitionFromLoadToPlanet()
{
    InitSpaceGame();
    void* pPlanet = GetActivePlanet();
    InitializePlanetContext();

    cPlanetModel* pModel = (cPlanetModel*)PlanetModel();
    if (pModel != nullptr) {
        uint32_t nKey = pModel->GetPlanetKey();
        (void)nKey;
        SetLoadedPlanet();
    }
    (void)pPlanet;

    SetPlanetModelView(0);
    RefreshPlanetUI();
    InitPlanetView();

    cSPSimulatorPlayerUFO* pUFO = (cSPSimulatorPlayerUFO*)SpaceGameGet();
    pUFO->InitForPlanet();

    void* pMessage = CreateTransitionMessage();
    PostMessage(pMessage);
    RefreshModeUI();
    ResetTransitionTuning();

    ResetUIState();
    ClearSelection(-1);
    NounManager();
    ApplyNounChanges();
}

// @ 0x00fdc800
void cAppModeSpace_s00fd_bd60::TransitionFromEditorToPlanet()
{
    InitSelectionState();
    void* pContext = GetActivePlanet();
    if (pContext == nullptr) {
        InitializePlanetContext();

        cPlanetModel* pModel = (cPlanetModel*)PlanetModel();
        if (pModel == nullptr) {
            void* pView = CreatePlanetView(1, 1);
            SetPlanetViewPlanet(pView, 1, 0);
        } else {
            uint32_t nKey = pModel->GetPlanetKey();
            (void)nKey;
            SetLoadedPlanet();
        }

        SetPlanetModelView(0);
        RefreshPlanetUI();
        InitPlanetView();

        void* pMessage = CreateTransitionMessage();
        PostMessage(pMessage);
        RefreshModeUI();
        ResetTransitionTuning();

        ResetUIState();
        ClearSelection(-1);
        NounManager();
        ApplyNounChanges();

        uint32_t nSlot = gSpaceModeSlot;
        void* pGameMode = mpGameMode->mpPlanetView;
        if (*(int*)((uint8_t*)pGameMode + 0x204) == 1)
            nSlot = 0xebb801;
        else
            nSlot = 0x1103193;
        (void)nSlot;
        SetGameSpeed(0xebb801);
        UnloadMissionTuning();
    } else {
        SetPaused(false);
        UnloadMissionTuning();
        SetUniverseView(0);

        if (mnPlanetContext == 1) {
            ShowMissionLog();
            return;
        }
        if (mnPlanetContext == 2) {
            mpGameMode->mpUISpace->ToggleStarmapFilters(true);
            StarMapManager();
            return;
        }
    }
}

// @ 0x00fdc980
void cAppModeSpace_s00fd_bd60::TransitionToEntry()
{
    if (mpGameMode != nullptr) {
        ShutdownSpaceGame();
        PlanetModel();
        RefreshPlanetUI();
        ShutdownSPG();
    }

    cEffectsManager* pEffects = EffectsManager();
    pEffects->v54();
    void* pEntry = nullptr;
    if (pEntry != nullptr) {
        (void)pEntry;
        cPropertyList* pList = (cPropertyList*)pEntry;
        (void)pList;
        operator_delete__(pEntry);
    }
}

// @ 0x00fdc9e0
void cAppModeSpace_s00fd_bd60::PlanetOnMouseDown()
{
    ((SP::cAppModeSpace*)this)->FUN_00fda9f0();
    PlanetModel_s00fd_dba0()->Refresh();
    ShutdownSPG();
}

// @ 0x00fdca00
cAppModeSpace_s00fd_bd60::cAppModeSpace_s00fd_bd60()
{
    mpStarMap = nullptr;
    mpUniverse = nullptr;
    mpTerrain = nullptr;
    mpPlanetKeyData = nullptr;
    mnPlanetContext = 0;
    mpGonzagoWorld = nullptr;
    mpPlanetView = nullptr;
    mpStrategy = nullptr;
    mbInitialized = 0;
    mnDragStartX = 0;
    mnDragStartY = 0;
    mnDragKind = 0;
    mpEmpire = nullptr;
    mpPlayer = nullptr;
    mnPlayerId = 0;
    mpGonzagoAsset = nullptr;
    mbSpaceGameActive = 0;
    mpGameMode = nullptr;
    mpHandler = nullptr;
    mpUISpace = nullptr;
    mnOldGameMode = 0;
    mpEditor = nullptr;
    mbEditorPlaying = 0;
    mbFlag18d = 0;
    mbFlag18e = 0;
    mbFlag18f = 0;
    mbFlag190 = 0;
    mbFlag191 = 0;
    mbFlag192 = 0;
    mpListHead = nullptr;

    mpListHead = this;
    gSpaceAppMode = this;
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

// @ 0x00fddba0
void cAppModeSpace_s00fd_dba0::SetDefaultPickPriority()
{
    PickPriorityVec list;
    list.push_back(PickPriority(0xb033b403, 1, 10));
    list.push_back(PickPriority(0x137e8e0, 1, 10));
    list.push_back(PickPriority(0xb033b403, 2, 20));
    list.push_back(PickPriority(0x137e8e0, 2, 20));
    list.push_back(PickPriority(0xe9cb8ba, 2, 40));
    list.push_back(PickPriority(0x436f315, 0, 30));
    list.push_back(PickPriority(0xe9cb8ba, 0, 30));
    list.push_back(PickPriority(0x175cdc9, 0, 30));
    list.push_back(PickPriority(0xce9f6639, 0, 30));
    list.push_back(PickPriority(0x3275872, 1, 100));
    list.push_back(PickPriority(0x44462a6, 1, 100));
    list.push_back(PickPriority(0x38cfb68, 0, 100));
    list.push_back(PickPriority(0x3275872, 2, 110));
    list.push_back(PickPriority(0x44462a6, 2, 110));
    PickPriorityMgr()->SetList(&list, 0);
}

// @ 0x00fddfa0
void FUN_00fddfa0()
{
    PickPriorityVec list;
    list.push_back(PickPriority(0xb033b403, 1, 10));
    list.push_back(PickPriority(0x137e8e0, 1, 10));
    list.push_back(PickPriority(0xb033b403, 2, 20));
    list.push_back(PickPriority(0x137e8e0, 2, 20));
    list.push_back(PickPriority(0xe9cb8ba, 1, 30));
    list.push_back(PickPriority(0xce9f6639, 0, 30));
    PickPriorityMgr()->SetList(&list, 0);
}

// @ 0x00fde180
bool cAppModeSpace_s00fd_dba0::Shutdown()
{
    FUN_00e1dbd0();
    mModels.clear();

    cMessageServer* server = MessageServer_s00fd_dba0();
    if (server != 0)
    {
        server->Notify(GetModeBase(this), 0x1a0219e, 0xffffd8f1);
        server->Notify(GetModeBase(this), 0x3795725, 0xffffd8f1);
    }
    CheatManager()->SetFlag(g_cheatFlag);
    ShutdownSPG();
    return true;
}

// @ 0x00fde230
void NotifyActivePlanetRecord(void* record_)
{
    cPlanetRecord* record = (cPlanetRecord*)record_;

    int count = (int)(record->mTemplatesEnd - record->mTemplatesBegin);
    for (int i = 0; i < count; i++)
        ObjectTemplateDB()->Unregister(&record->mTemplatesBegin[i]);

    cBioElemSort* sort = record->SortBanners();

    void* key = sort->Func_bb9b80();
    if (*(int*)key != 0)
        ObjectTemplateDB()->Unregister(key);

    if (sort->Func_bb9ae0() == 5)
    {
        cEmpire* empire = StarManager()->GetEmpireByID(sort->GetAvatar());
        if (empire != 0)
            ObjectTemplateDB()->Unregister(empire->GetUFOKey());
    }

    int n = (int)(record->mExtraEnd - record->mExtraBegin);
    PlanetTemplateVec** buf = 0;
    if (n != 0)
        buf = (PlanetTemplateVec**)operator new[](n * 4, "Simulator", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1);
    memcpy(buf, record->mExtraBegin, n * 4);

    int copied = n;
    for (int i = 0; i < copied; i++)
    {
        PlanetTemplateVec* v = buf[i];
        int m = (int)(v->mpEnd - v->mpBegin);
        for (int j = 0; j < m; j++)
        {
            PlanetTemplateRef* e = &v->mpBegin[j];
            if (e->mKey != 0 && e->mKey != 0xffffffff)
                ObjectTemplateDB()->Unregister(e);
        }
    }

    if (buf != 0 && ((int*)buf)[-1] != 0)
        operator delete[](buf);
}

// @ 0x00fde3e0
void cAppModeSpace_s00fd_dba0::TransitionFromPlanetToSolar(bool bUpdateEmpire)
{
    mpSpaceGame->mFlags |= 1;
    mModels.clear();

    cStar* star = GetActiveStar();
    cPlanet* planet = GetActivePlanet_s00fd_dba0();
    cSPGameDataUFO* ufo = GetUFOSimulator_s00fd_dba0()->GetPlayerInventory();

    cHud* hud = GetHud();
    if (hud && (hud->IsActive() || hud->GetMode() == 2))
        hud->Show();

    cModeObject* mode = App_s00fd_dba0()->GetModeManager()->GetCurrentMode();
    cCameraView* view = 0;
    bool viewFlagA;
    bool viewFlagB;
    if (mode && (view = (cCameraView*)mode->Query(0x303154cd)) != 0)
    {
        viewFlagA = gViewFlagA;
        viewFlagB = view->mbFlag;
    }
    else
    {
        view = 0;
        viewFlagA = false;
        viewFlagB = false;
    }

    const Vector3* src;
    Vector3 viewTarget;
    if (view == 0)
        src = &kUpAxisY;
    else
    {
        viewTarget.x = view->mTarget.x;
        viewTarget.y = view->mTarget.y;
        viewTarget.z = view->mTarget.z;
        src = &viewTarget;
    }
    Vector3 camTarget;
    camTarget.x = src->x; camTarget.y = src->y; camTarget.z = src->z;

    const Vector3* ufoSrc = ufo->mSpatial.GetPosition();
    Vector3 ufoPos;
    ufoPos.x = ufoSrc->x; ufoPos.y = ufoSrc->y; ufoPos.z = ufoSrc->z;

    mpSpaceGame->Reset();
    PlanetModel_s00fd_dba0()->Refresh();
    NounManager_s00fd_dba0()->GetCurrentTerrainSphere()->SetModel(0x574ac66);
    GetEffectsMgr()->Play(0x1103192);

    if (viewFlagA)
    {
        const Quaternion* planetOri = planet->GetOrientation();
        Vector3 rotated;
        Vector3* p = RotateByQuaternion(&rotated, &ufoPos, planetOri);
        float x = p->x, y = p->y, z = p->z;
        float inv = 1.0f / (float)sqrt(x * x + z * z + y * y);
        float offX = (inv * x) * kFlyOutScale.x;
        float offY = (y * inv) * kFlyOutScale.x;
        float offZ = (z * inv) * kFlyOutScale.x;
        const Vector3* pos = planet->GetPosition();
        Vector3 dest;
        dest.x = pos->x + offX;
        dest.y = pos->y + offY;
        dest.z = pos->z + offZ;
        ufo->SetDestination(&dest);

        const Quaternion* a = planet->GetOrientation();
        const Quaternion* b = ufo->mSpatial.GetOrientation();
        ufo->mOrientation = QuatMul(*a, *b);
        ufo->PopToDestination();
        ufo->SetDestination(planet);
    }
    else
    {
        ufo->SetDestination(planet);
        Vector3 facing;
        Quaternion q;
        Quaternion* r = QuaternionFromFacingAndUp(&q, OrthogonalVector(&facing, &kUpAxisZ), &kUpAxisZ);
        ufo->mOrientation = *r;
        ufo->PopToDestination();
    }

    mpSpaceGame->Update();
    mpSpaceGame->ChaseFromPlanetToSolar();

    cModeObject* mode2 = App_s00fd_dba0()->GetModeManager()->GetCurrentMode();
    if (mode2)
    {
        cHudCtl* ctl = (cHudCtl*)mode2->Query(0x303154cc);
        if (ctl)
            ctl->Apply(&camTarget, viewFlagB);
    }

    if (mpSpaceGame->mpActiveEffect)
        mpSpaceGame->mpActiveEffect->Stop(0);

    cSolarSystem* ss = star->GetSolarSystem();
    if (ss)
    {
        int n = (int)(ss->mPlanetsEnd - ss->mPlanetsBegin);
        for (int i = 0; i < n; i++)
        {
            cPlanet* p = ss->mPlanetsBegin[i];
            int kind = p->GetKind();
            if (kind != 0 && kind != 1 && p != GetActivePlanet_s00fd_dba0() && !p->mpInfo->IsHidden())
                GetPlanetRegistry()->Show(p);
        }
    }

    unsigned __int64 elapsed = ((cSPTimer*)((char*)sInstance + 0xa8))->GetElapsedTime();
    if (elapsed > 144000000)
        GetAchievements()->AwardAchievement(0x256184b1);

    cStarList* list = SpaceGameGet_s00fd_dba0()->mpStars;
    int count = (int)(list->mEnd - list->mBegin);
    cStar** buf;
    if (count != 0)
        buf = (cStar**)operator new[](count * 4, "Simulator", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1);
    else
        buf = 0;
    cStar** bufEnd;
    uninitialized_copy_stars(&bufEnd, list->mBegin, list->mEnd, buf, bUpdateEmpire);

    if ((unsigned)(bufEnd - buf) >= 10)
    {
        int full = 0;
        for (cStar** it = buf; it != bufEnd; ++it)
        {
            int turrets = 0, buildings = 0;
            GetTurretAndBuildingCounts(*it, &turrets, &buildings);
            if (turrets + buildings >= GetTerraformTuning()->GetMaxBuildingsForT3Colony() * 3)
                full++;
        }
        if (full >= 10)
            GetAchievements()->AwardAchievement(0xfbe4dc0d);
    }

    cTutorial* tut = GetTutorial();
    if (tut->mpCurrent && tut->mpCurrent->mID == 0xf98be0b8)
    {
        tut->Close(0xf98be0b8, 1);
        GetPopup()->Refresh();
    }

    if (bUpdateEmpire)
        GetHudEmpire()->Update(GetPlayerEmpire_s00fd_dba0()->GetID());

    NotifyActivePlanetRecord(GetActivePlanetRecord_s00fd_dba0());
    mpSpaceGame->mFlags &= 0xfffffffe;
    MessageServer_s00fd_dba0()->PostMessage(0x5e37a2c, 0, 0, 0);

    for (cStar** it = buf; it < bufEnd; ++it)
        if (*it)
            (*it)->Release();
    if (buf && ((int*)buf)[-1] != 0)
        operator delete[](buf);
}

// @ 0x00fdeac0
namespace SP {
void cAppModeSpace_s00fd_eac0::TransitionFromSolarToPlanet()
{
    cPlanet_s00fd_eac0* planet = cSPLivingUniverse::GetActivePlanet_s00fd_eac0();
    cPlanetRecord_s00fd_eac0* record = cSPLivingUniverse::GetActivePlanetRecord();
    GonzagoTransition()->Begin();
    mDisabledRenderLayersForBaking = true;
    mBakingForPlanetEntryEnded = false;
    mElapsedBakeTimeForTransitionMS = 0;

    mPlantModels.clear();
    for (uint32_t i = 0; i < record->size(); i++) {
        cPlantSpecies* species = PlantSpeciesManager()->GetSpeciesFromID(record->mPlantsBegin[i]);
        IModelWorld* world = GonzagoModelWorld_s00fd_eac0();
        ModelPtr model = world->LoadModel(species->GetModelKey()->instanceID,
                                          (species->GetModelKey()->groupID & 0xffff62ff) | 0x6200, 0);
        if (model) {
            mPlantModels.push_back(model);
            model->mpWorld->SetModelVisible(model, false);
        }
    }

    uint32_t tag = planet->mpStarRecord->GetCommContext();
    if (tag != mLastBakedTag)
        BakeManager()->Cancel(mLastBakedTag);
    BakeManager()->Cancel(0x609b763);
    if (planet->GetPlanetType() > 1) {
        const ResourceKey* key = planet->mpStarRecord->GetBioProtector()->GetKey();
        if (!BakeManager()->IsBaked(*key, false)) {
            BakeParameters params(0, 4, tag);
            BakeManager()->BakeModel(*key, params);
        }
    }
    mLastBakedTag = tag;

    if (ActiveMission() == StarManager_s00fd_eac0()->GetCurrentMission()) {
        if (ActiveMission()->GetTargetRecord(0) == cSPLivingUniverse::GetActivePlanetRecord())
            AchievementsController()->AutoTest(0x7d4eb7d3, 1);
    }

    {
    cKeyMap keyMap;
    cPlanet_s00fd_eac0* activePlanet = cSPLivingUniverse::GetActivePlanet_s00fd_eac0();
    if (activePlanet && !activePlanet->GetItems().empty()) {
        int count = activePlanet->GetItems().size();
        for (int i = 0; i < count; i++) {
            cPlanetItem* item = activePlanet->GetItem(i);
            int ownerID = item->GetOwnerID();
            if (ownerID < 0 && ownerID != NounManager_s00fd_eac0()->GetPlayerEmpireID())
                item->ApplyKeyMap(StarManager_s00fd_eac0()->GetEmpireByID(ownerID)->GetKeyMap());

            if (item->mKeysBegin[0].instanceID == 0 || item->mKeysBegin[0].instanceID == 0xffffffff) {
                mSimulatorSpaceGame->FillKeyMap(keyMap);
                if (activePlanet->GetPlanetType() == 4) {
                    uint32_t v = keyMap.Find(0x2090a11b);
                    keyMap.Insert(0x441cd3e6, v);
                    keyMap.Insert(0x449c040f, v);
                    keyMap.Insert(0x1a4e0708, v);
                    v = keyMap.Find(0xbc1041e6);
                    keyMap.Insert(0x7d433fad, v);
                    keyMap.Insert(0x9ad7d4aa, v);
                    keyMap.Insert(0xf670aa43, v);
                    v = keyMap.Find(0xc15695da);
                    keyMap.Insert(0x8f963dcb, v);
                    keyMap.Insert(0x1f2a25b6, v);
                    keyMap.Insert(0x2a5147a9, v);
                }
                for (int j = 0; j < count; j++)
                    activePlanet->GetItem(j)->ApplyKeyMap(keyMap);
            }

            BakeParameters params(0, 1, tag);
            if (ActiveMission()->GetState() == 5) {
                const ResourceKey* ufoKey = StarManager_s00fd_eac0()->GetEmpireByID(ActiveMission()->GetEmpireID())->GetUFOKey();
                if (!BakeManager()->IsBaked(*ufoKey, false)) {
                    mNeedsBakingForTransition.push_back(*ufoKey);
                    BakeManager()->BakeModel(*ufoKey, params);
                }
            }

            params.mPriority = 2;
            int numKeys = (int)(item->mKeysEnd - item->mKeysBegin);
            for (int k = 0; k < numKeys; k++) {
                const ResourceKey& key = item->mKeysBegin[k];
                if (key.instanceID != 0 && key.instanceID != 0xffffffff) {
                    if (!BakeManager()->IsBaked(key, false)) {
                        if (eastl::find(mNeedsBakingForTransition.begin(), mNeedsBakingForTransition.end(), key) ==
                            mNeedsBakingForTransition.end()) {
                            mNeedsBakingForTransition.push_back(key);
                            mDisabledRenderLayersForBaking = false;
                            BakeManager()->BakeModel(key, params);
                        }
                    }
                }
            }
        }
    }

    if (!sAppProperties->GetBool(0x7ae23adf)) {
        mNeedsBakingForTransition.clear();
        mDisabledRenderLayersForBaking = true;
    } else if (!mDisabledRenderLayersForBaking) {
        if (mpSpaceUI->mpUISpace)
            mpSpaceUI->mpUISpace->ShowBakeTimeSplash();
        for (int layer = 0; layer < 28; layer++)
            mOldRenderLayerStates.push_back(Renderer()->IsLayerEnabled(layer, true));
        mBakingForPlanetEntryEnded = true;
    }
    }

    cPlanet_s00fd_eac0* targetPlanet = cSPLivingUniverse::GetActivePlanet_s00fd_eac0();
    UniverseUpdateActive();
    cPlanetModel_s00fd_eac0* planetModel = PlanetModel_s00fd_eac0();
    if (planetModel->mpISphere == 0)
        planetModel->Generate(targetPlanet->GetPlanetKey(), 0);
    else
        targetPlanet->SetPlanetKey(planetModel->GetPlanetKey());
    MessageServer_s00fd_eac0()->PostMSG(0x279a5da, 0, 0);
    mpSpaceUI->mFlags |= 2;

    cPlanetVisits* visits = PlanetVisits();
    ResourceKey visitKey = kDefaultKey;
    PropertyListPtr propList;
    ResourceKey planetType = {0, 0, 0};
    PropertyManager()->GetPropertyList(planet->GetPlanetKey()->instanceID, planet->GetPlanetKey()->groupID, &propList);
    if (propList)
        GetPropertyAsKey(propList, 0xb2cccb, &planetType);
    switch (planetType.instanceID) {
    case 0x0d019b5b: case 0x5c80e783: case 0xa1867950: case 0xaa61bc5b:
        visitKey.instanceID = 0xae15a0ca; break;
    case 0x1e5569aa: case 0x80f548aa:
        visitKey.instanceID = 0xdb0c25ed; break;
    case 0x34bf26cf: case 0x1c901fcf: case 0x2f88ce28: case 0x332eab13: case 0x4c0e0747:
        visitKey.instanceID = 0xae15a0cc; break;
    case 0x51f60469: case 0x60e56c7a: case 0xf1c64be5: case 0xff0cf57a:
        visitKey.instanceID = 0xae15a0cb; break;
    case 0x06be74d1: case 0xa4e5fdd1:
        visitKey.instanceID = 0xae15a0c7; break;
    case 0x329977f9: case 0x49668fda: case 0x98eeb4f9: case 0xafbbccda:
        visitKey.instanceID = 0xae15a0c8; break;
    case 0x3c5bdade: case 0x73f48a76: case 0xead9ff1a:
        visitKey.instanceID = 0xae15a0cd; break;
    case 0x655cf1e1: case 0xbdf0e303: case 0x7d8bf8e1: case 0xd61fea03:
        visitKey.instanceID = 0xae15a0cf; break;
    case 0x2f860299: case 0xcce62399:
        visitKey.instanceID = 0xae15a0c9; break;
    case 0x532534be: case 0xf08555be: case 0xfbec2af8:
        visitKey.instanceID = 0xae15a0c6; break;
    }
    if (visitKey != kDefaultKey) {
        if (!planet->IsHomePlanet())
            SpaceGameGet_s00fd_eac0()->GetTool()->Refresh(0x18, 1);
        if (visits->GetVisitCount(&visitKey) != 1) {
            visits->SetVisitCount(&visitKey, 1);
            EventLog_s00fd_eac0()->PostFeedbackEvent(0xd7775835, 0x131a9f54, 0, 0, 1, 0);
        }
    }

    GameTimeManager_s00fd_eac0()->IncPauseGate(0x4bf38a7);
    LayoutCollection()->Show();
    GameInputManager_s00fd_eac0()->mInputLock++;
}
}  // namespace SP

// @ 0x00fdf5b0
namespace SP {
void cAppModeSpace_s00fd_eac0::OnPlanetRecordReady()
{
    cSPLivingUniverse::GetActivePlanet_s00fd_eac0();
    cPlanetRecord_s00fd_eac0* record = cSPLivingUniverse::GetActivePlanetRecord();
    if (record->GetTransitionData()) {
        ITransitionTarget* target = GetTransitionTarget(0, 0);
        void (ITransitionTarget::*enter)() = &ITransitionTarget::Enter;
        (target->*enter)();
    } else {
        TransitionFromSolarToPlanet();
    }
}
}  // namespace SP

// @ 0x00fdf5f0
namespace SP {
void cAppModeSpace_s00fd_eac0::EnterPlanetTransition()
{
    cPlanet_s00fd_eac0* planet = cSPLivingUniverse::GetActivePlanet_s00fd_eac0();
    cPlanetRecord_s00fd_eac0* record = cSPLivingUniverse::GetActivePlanetRecord();
    GonzagoTransition()->Begin();

    void* transitionData = record->GetTransitionData();
    if (!transitionData) {
        TransitionFromSolarToPlanet();
        return;
    }

    void* app = App_s00fd_eac0();
    void* appObject = VCP0(app, 0x50);
    VC1(appObject, 0x34, 0);

    TransitionParams* params = ResetTransitionParams();
    params->mpTargetData = transitionData;
    params->mTypeHash = 0x366a930d;
    params->mField08 = DAT_015b4050;
    params->mEmpireKey = *cSPLivingUniverse::GetPlayerEmpire()->GetCityKey();
    params->mField24 = 2;
    params->mField28 = 2;

    IdVector* targets = TutorialManager()->GetTargetEmpires();
    int numTargets = (int)(targets->mpEnd - targets->mpBegin);
    for (int i = 0; i < numTargets; i++) {
        cEmpire_s00fd_eac0* empire = StarManager_s00fd_eac0()->GetEmpireByID(targets->mpBegin[i]);
        if (empire) {
            cHomePlanet* home = empire->GetHomePlanet();
            if (home)
                params->mKeys.push_back(*home->GetBannerKey());
        }
    }

    mpSpaceUI->DestroyNPC_UFOs(1, 1, 0);
    mpSpaceUI->FUN_010039c0(FUN_01021230_s00fd_eac0());

    VecOut<cPlanetItem>* items = (VecOut<cPlanetItem>*)NounManager_s00fd_eac0()->GetGameDataVector(
        (void*)0xcd7d10, (void*)0xd3d420, (void*)0xad48b0, (void*)0xb1e500, 0x18ebadc);
    int numItems = (int)(items->mVec.mpEnd - items->mVec.mpBegin);
    for (int i = 0; i < numItems; i++) {
        cPlanetItem* item = items->mVec.mpBegin[i];
        item->SetActive(false);
        VC1(&item->mpInterface508, 0x50, 0);
    }

    void* obj = FUN_0067de00();
    VC1(obj, 0xe0, 0);
    obj = FUN_0067ddd0();
    VC2(obj, 0x98, 0x14, 1);
    obj = FUN_0067dd40();
    VC1(obj, 0x100, 1);
    obj = FUN_0067dd40();
    VC1(obj, 0x108, 0);

    RenderMgr* renderMgr = GetRenderMgr();
    void* iface = renderMgr->mpInterface6c;
    if (iface && !VCB0(iface, 0x10))
        VC1(iface, 0x08, 0);

    FUN_01021960(0);
    renderMgr->FUN_01034810();
    renderMgr->Setup(1, planet->GetPlanetKind());

    cSolarSystem_s00fd_eac0* solar = FUN_01021230_s00fd_eac0()->GetSolarSystem();
    if (solar)
        solar->ActivateGraphics(1);

    renderMgr->FUN_01036590(planet);
    GetRenderMgr()->UpdateSpaceColor(*record->GetOwnerCiv()->GetCities());
    FUN_01021740(planet);

    mField194 = 0xa;
    TutorialSystem()->StartModeTutorial(1, 0x1654c10, 1);
}
}  // namespace SP

// @ 0x00fdf8e0
namespace SP {
void cAppModeSpace_s00fd_eac0::ExitPlanetTransition()
{
    void* transitionMgr = FUN_00b3d310();
    VC1(transitionMgr, 0x14, 0x1654c05);
    mpSpaceUI->FUN_01003230();
    TransitionFromPlanetToSolar(true);

    Editor* editor = DAT_016c7aa4_s00fd_eac0;
    if (editor) {
        uint32_t* pField = &editor->mFieldB8;
        if (pField) {
            PlanetLeaveMessage msg;
            msg.mField30 = 0;
            msg.mpVtbl = (void*)0x013eb90c;
            _InterlockedExchange(&msg.mRef, 0);
            msg.mpVtbl = (void*)0x013eb844;
            msg.mField38 = 0;
            msg.mpRecord = cSPLivingUniverse::GetActivePlanetRecord();
            msg.mField10 = editor->mFieldB8;
            msg.mField18 = (editor->mFieldC4 == 5) ? 1 : 0;
            IMessageServer_s00fd_eac0* server = (IMessageServer_s00fd_eac0*)MessageServerGet();
            server->PostMSG(0x43f2592, &msg, 0);
            msg.Destruct();
        }
        AwardSpaceAchievements();
    }

    VecOut<cPlanetItem>* items = (VecOut<cPlanetItem>*)NounManager_s00fd_eac0()->GetGameDataVector(
        (void*)0xcd7d10, (void*)0xd3d420, (void*)0xad48b0, (void*)0xb1e500, 0x18ebadc);
    int numItems = (int)(items->mVec.mpEnd - items->mVec.mpBegin);
    for (int i = 0; i < numItems; i++)
        items->mVec.mpBegin[i]->SetActive(true);
}
}  // namespace SP

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

// @ 0x00fe0570
void cAppModeSpace_s00fe_0570::InitSpaceMode()
{
    cObjectTemplateDB_s00fe_0570* db = ObjectTemplateDB_s00fe_0570();
    cTerrainSphere_s00fe_0570* s1 = NounManager_s00fe_0570()->GetCurrentTerrainSphere();
    db->Register(&s1->mKey1168, 1);
    db = ObjectTemplateDB_s00fe_0570();
    cTerrainSphere_s00fe_0570* s2 = NounManager_s00fe_0570()->GetCurrentTerrainSphere();
    db->Register(&s2->mKey1150, 1);

    cPlanetRecord_s00fe_0570* home = GetPlayerHomePlanet_s00fe_0570();
    mBakingForPlanetEntryEnded = true;
    mbBakeStarted = false;
    mElapsedBakeTimeForTransitionMS = 0;
    uint32_t context = home->GetCommContext();
    mCommContext = context;
    RegisterHomePlanet(home, home->GetEntry());

    KeyMap keys;
    keys.Set(0x99e92f05, NounManager_s00fe_0570()->GetCurrentTerrainSphere()->mKey1150);
    keys.Insert(0x4e3f7777);
    keys.Insert(0x47c10953);
    keys.Insert(0x72c49181);
    keys.Insert(0x2090a11b);
    keys.Insert(0xbc1041e6);
    keys.Insert(0xc15695da);
    keys.Set(0x7d433fad, ZeroKey());
    keys.Set(0xf670aa43, ZeroKey());
    keys.Set(0x9ad7d4aa, ZeroKey());
    keys.Set(0x8f963dcb, ZeroKey());
    keys.Set(0x2a5147a9, ZeroKey());
    keys.Set(0x1f2a25b6, ZeroKey());
    keys.Set(0x441cd3e6, ZeroKey());
    keys.Set(0x1a4e0708, ZeroKey());
    keys.Set(0x449c040f, ZeroKey());

    if (home && home->mpEntitiesBegin != home->mpEntitiesEnd) {
        int n = (int)(home->mpEntitiesEnd - home->mpEntitiesBegin);
        for (int i = 0; i < n; i++) {
            cModelEntity* entity = home->GetEntity(i);
            entity->StoreModelKeys(&keys);
        }
    }

    BakeParam param;
    param.mA = 0;
    param.mB = 2;
    param.mContext = context;
    AddBakeKey(&param, keys.Get(0x99e92f05));
    AddBakeKey(&param, keys.Get(0x4e3f7777));
    AddBakeKey(&param, keys.Get(0x47c10953));
    AddBakeKey(&param, keys.Get(0x72c49181));
    AddBakeKey(&param, keys.Get(0x2090a11b));
    AddBakeKey(&param, keys.Get(0xbc1041e6));
    AddBakeKey(&param, keys.Get(0xc15695da));
    AddBakeKey(&param, &NounManager_s00fe_0570()->GetCurrentTerrainSphere()->mKey1168);
    Unused_b3d460();
    AddBakeKey(&param, (const ResourceKey_s00fe_0570*)(GetPlayerEmpire_s00fe_0570()->GetData() + 0x504));

    Vector3 box[2];
    box[0].x = -1500.0f;
    box[0].y = -1500.0f;
    box[0].z = -500.0f;
    box[1].x = 1500.0f;
    box[1].y = 1500.0f;
    box[1].z = 500.0f;
    GonzagoModelWorld_s00fe_0570()->SetWorldBounds(box, 0.0f, 1.0e10f);

    cTerrainSphere_s00fe_0570* sphere = NounManager_s00fe_0570()->GetCurrentTerrainSphere();
    const ResourceKey_s00fe_0570* ufoKey = &sphere->mKey1168;
    mUFOKey.instanceID = ufoKey->instanceID;
    mUFOKey.typeID = ufoKey->typeID;
    mUFOKey.groupID = ufoKey->groupID;
    Func_fda750();

    int startMode = sAppProperties_s00fe_0570->GetIntProperty(0x1c29572);
    cPlayerUFO* ufo = SpaceGame()->GetPlayerUFO();
    switch (startMode) {
    case 0: {
        LoadNewGamePlanet();
        MessageServer_s00fe_0570()->Post(0x279a5da, 0, 0);
        mpSimulatorSpaceGame->StepC();
        cSPSimulatorPlayerUFO_s00fe_0570* game = SpaceGame();
        game->InitForPlanet();
        ufo = game->GetPlayerUFO();
        float half = CameraSettings()->GetRadiusFactor() * 0.5f;
        ufo->SetAltitude(PlanetModel_s00fe_0570()->GetMinAltitude() + half);
        Vector3 pos;
        TimeOfDayInstance()->GetSunPosition(&pos);
        game->SetPlanetDestination(&pos, false, true, false, false);
        game->GetPlayerUFO()->PopToDestination();
        SetPlanetTimeOnFirstEntry();
        Func_fdf9f0();
        SlotMessage msg;
        msg.mTarget = (uint32_t)GetActivePlanet_s00fe_0570();
        MessageServer_s00fe_0570()->Post(0x248975f, &msg, 0);
        break;
    }
    case 1:
        SimSystem()->Notify(0x1103192);
        mpSimulatorSpaceGame->StepB();
        break;
    case 2: {
        mpSimulatorSpaceGame->mpField40->SetName(kInterstellarDrive);
        SimSystem()->Notify(0x1103192);
        mpSimulatorSpaceGame->StepA();
        ResourceKey_s00fe_0570 key;
        MakeKeyFromIndex(&key, MissionIndexFromFloat(ufo->GetFloat()));
        ufo->ApplyKey(&key);
        break;
    }
    }

    NounManager_s00fe_0570()->ProcessPending();
    cPlanet_s00fe_0570* planet = GetActivePlanet_s00fe_0570();
    planet->Refresh1();
    planet->Refresh2();
    planet->Refresh3(0);
    planet->Restart();

    if (!mBakingForPlanetEntryEnded) {
        if (!mbTutorial && mpSimulatorSpaceGame->mpUI)
            mpSimulatorSpaceGame->mpUI->ShowBakeTimeSplash();
        GameTimeManager_s00fe_0570()->IncPauseGate(0x4bf38a7);
        for (int i = 0; i <= 0x1b; i++) {
            bool value = InputManager()->IsControlActive(i, 1) & 1;
            mInputFlags.push_back(value);
        }
        mbBakeStarted = true;
    }
    mpSimulatorSpaceGame->mFlags |= 0x10;
}

// @ 0x00fe0e10
void cAppModeSpace_s00fe_0570__g7::FUN_00fe0e10()
{
    FUN_00b3d360_s00fe_0570__g7()->FUN_00b7dec0();
    cPlanet_s00fe_0570__g7* planet = GetActivePlanet_s00fe_0570__g7();
    FUN_01021230();
    cPlanetModel_s00fe_0570__g7* model = PlanetModel_s00fe_0570__g7();
    if (model->mField24 == 0)
        model->FUN_00b8d750(planet->FUN_00c713e0(1));
    else
        planet->FUN_00c713c0(model->GetPlanetKey());
    FUN_00b3d310_s00fe_0570__g7()->FUN_00b515e0();
    model->Refresh();
    GetUFOSimulator_s00fe_0570__g7()->InitForPlanet();
    MessageServer_s00fe_0570__g7()->Post(0x279a5da, 0, 0);
    mpSimulatorSpaceGame->StepC();

    SlotMessage msg;
    msg.mTarget = (uint32_t)GetActivePlanet_s00fe_0570__g7();
    FUN_00fdf9f0();
    FUN_010213b0(-1);
    NounManager_s00fe_0570__g7()->ProcessPending();
    MessageServer_s00fe_0570__g7()->Post(0x248975f, &msg, 0);
    MessageServer_s00fe_0570__g7()->PostEx(0x5e37a53, 0, 0, 0);
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

// @ 0x00fe2ab0
void cModeTransition::PostGameModeTransition(int32_t oldMode, int32_t newMode)
{
    if (GetPostModeTransitionState() == newMode)
        return;

    BeginPostGameModeTransition(newMode);

    cAppModeSpace_s00fe_2ab0* space = static_cast<cAppModeSpace_s00fe_2ab0*>(this);

    if (!(SP::sTestSystem && SP::sTestSystem->IsTestingInProgress())) {
        if (newMode == kModeSpace && oldMode != kModeEditor && oldMode != kModePlanetView) {
            if (space->mbFlag18e) {
                if (SP::SpaceModeManager()->IsReady()) {
                    space->mbFlag18f = true;
                    space->mbFlag190 = false;
                    space->mbFlag191 = false;
                    space->mbFlag192 = false;
                    goto transitioned;
                }
            }
            SP::SpaceModeManager()->SetPendingMode(0, kModeSpace);
        }
    }
transitioned:
    SP::Subsystem1()->PostGameModeTransition(oldMode, newMode);
    SP::Subsystem2()->PostGameModeTransition(oldMode, newMode);

    if (newMode == kModeSpace) {
        SP::EffectsManager_s00fe_2ab0()->Preload(0xc, true);
        space->mAutoHandler.AddHandler(SP::MessageServer_s00fe_2ab0(), static_cast<ISubsystem*>(space),
                                       SP::kHandlerIDs, 20);
        space->LoadStateMachine(SP::ConfigManager_s00fe_2ab0()->GetPropertyList(0x679b880));

        switch (oldMode) {
        case kModeTribe:
            SP::Fn_00b3d230()->Fn_00b5cde0(0x1103193);
            space->mpSpaceState->Fn_010030c0();
            break;

        case -1:
        case kModeUnknown:
            SP::Fn_00bf55d0();
            break;

        case kModeEditor: {
            space->TransitionFromEditorToPlanet();
            cSelection* selection = space->mpSpaceState->mpSelection;
            if (selection) {
                switch (selection->mnType) {
                case kTypeCreature:
                    if (!selection->mbHandled) {
                        SP::SpeciesManager_s00fe_2ab0()->SetAvatarSpecies(selection->mKey);
                        ICivilization* civ = SP::NounManager_s00fe_2ab0()->GetPlayerCivilization();
                        if (civ)
                            civ->Fn_00bebdd0(selection->mKey);
                        space->Fn_00fdb9a0();
                        PtrVector* list = SP::NounManager_s00fe_2ab0()->Fn_00ace2c0();
                        for (void** it = list->mpBegin; it != list->mpEnd; ++it)
                            SP::Subsystem2()->Fn_00ac8cd0(*it, 0);
                        Key key1, key2, key3, key4;
                        SP::CommEvent(0x9fd41912, 0, key4, key3, 0, 0, key2, key1);
                        SP::Fn_00ba5bc0(SP::GetPlayerEmpire(7));
                    }
                    break;

                case kTypePlanetA:
                case kTypePlanetB:
                    if (!selection->mbHandled) {
                        SP::GetPlayerEmpire(selection->mKey)->Fn_00c30fa0();
                        SP::Fn_00ba5650(&selection->mKey, 8);
                    }
                    space->mpSpaceState->mpEffect->Fn_010727e0(1, selection->mnType);
                    break;
                }
                space->mpSpaceState->mpSelection = 0;
                selection->Release();
            }
            SP::Fn_00b3d320()->Fn_00b1dfc0();
            if (space->mpSpaceState->mpUI->mnState == 1) {
                SP::MessageServer_s00fe_2ab0()->PostMSG(0x71d4dfc9, 0, 0);
                SP::GameInputManager_s00fe_2ab0()->SetMode(3);
            }
            break;
        }

        case kModeColony:
            SP::StarManager_s00fe_2ab0()->PostGameModeTransition(kModeColony, kModeSpace);
            break;
        }

        SP::CurMgr()->FindLocal(0x1002);
        SP::sAppProperties_s00fe_2ab0->SetBoolProperty(0x28, true);
        space->Fn_00fdb9a0();
        if (oldMode == kModeCiv || oldMode == kModeUnknown)
            SP::EventLog_s00fe_2ab0()->ClearEvents();
        space->SetDefaultPickPriority();
        space->mbFlag131 = SP::IsWorldLayoutFlagSet(2);
    }

    EndPostGameModeTransition();
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

// @ 0x010422e0
bool __cdecl TransitionFromSolarToGalaxy()
{
    void* app = App_s0104_14c0();
    void* mode = ((VfnP)(*(void***)app)[0x50 / 4])(app);
    void* obj = ((VfnP)(*(void***)mode)[0x38 / 4])(mode);
    int advanceID = obj != 0 ? ((VfnIUI)(*(void***)obj)[0xc / 4])(obj, 0x303154cc) : 0;

    Inventory* inv = (Inventory*)((UFOSim*)GetUFOSimulator_s0104_14c0())->GetPlayerInventory();
    bool canEnter = (inv->mFlag74C != 0 && inv->CanEnterPlanetContext()) ||
                    (((UFOData*)FUN_01021240())->AddRef() == 2 &&
                     InvHasWormhole((Inventory*)((UFOSim*)SpaceGameGet())->GetPlayerInventory())) ||
                    (((UFOData*)FUN_01021240())->AddRef() == 1 && !InTerrainSphere(0x681c28e));

    if (advanceID != 0 && canEnter &&
        !((CommScreen*)CommManager())->IsActive() &&
        (((GameTimeMgr*)GameTimeManager_s0104_14c0())->mFlags48 & 1) == 0 &&
        !((GameObj74*)FUN_010666a0())->FUN_01068350())
        return true;
    return false;
}




