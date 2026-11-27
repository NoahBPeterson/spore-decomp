// addresses retail relocates here, named so the build relocates them too
extern "C" void FUN_00692ca0();
extern "C" void FUN_00692fb0();
extern "C" void FUN_00c2e4e0();
extern "C" void FUN_00c7e9f0();
extern "C" void FUN_00cd44e0();
extern "C" char g_13ec47c[];
extern "C" char g_14669f8[];
extern "C" char g_147342c[];
extern "C" char g_1474f08[];
extern "C" char g_1474f14[];
extern "C" char g_1474f20[];
extern "C" char g_1474f28[];
extern "C" char g_1579c58[];
extern "C" char g_157c920[];
extern "C" char g_157c95c[];
extern "C" char g_157c998[];
extern "C" char g_157c9d4[];
extern "C" char g_157ca50[];
extern "C" char g_157d30c[];

#include <string.h>
#pragma intrinsic(strlen)
// src/game/SPGonzago/SPVehicle.cpp -- migrated from slice(s) s01355f90, s01354df0, s01351ae0, s00cb2f70, s00cb1110, s00cb02f0, s00caded0, s00cacf40, s00ca9820, s00ca8710, s00ca75e0, s00ca6630, s00ca5b10, s00ca4f90, s00ca46c0, s00ca3f20, s00ca3030, s00ca2210, s00ca1310, s00c9ffd0, s00c9de50, s00c9ef20 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPVehicle.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cVehicle.h"
#include "SP/cPlanetModel.h"
#include "SP/cSPTimer.h"
#include "SP/cInteractionAgent.h"

// unnamed retail callees and globals (address in the comment)
extern float  g_1485720;                               // 0x01485720 (1.0f)
extern float  g_13ec4b8;                               // 0x013ec4b8 (1e-08)
extern float  g_1485548;                               // 0x01485548 (1.5f)
extern float  g_1474a84;                               // 0x01474a84 (0.0375f)
extern float  g_157c70c;                               // 0x0157c70c
extern float  g_14749a8;                               // 0x014749a8 (FLT_MAX)
extern void*  g_1699ab8;                               // 0x01699ab8
extern char   g_1654c10, g_1654c04;                    // 0x01654c10 / 0x01654c04
extern void*  g_1474a70[];                             // 0x01474a70 table
extern void*  g_1474a5c[];                             // 0x01474a5c table
#include <math.h>
#include <intrin.h>
#include <xmmintrin.h>
#include "sse_helpers.h"
#include "SP/cAttachment.h"
#include "SP/cCivilization.h"
#include "SP/cCombatant.h"
#include "SP/cConfigManager.h"
#include "SP/cCreatureAbility.h"
#include "SP/cGameNounManager.h"
#include "SP/cLocomotiveObject.h"
#include "SP/cString.h"
#include "SP/cTribeTool.h"
#include "SP/cVarListSerializer.h"
#include <new>
#include "SP/cGameData.h"
#include "SP/cSpatialObject.h"
#include <float.h>
#include "SP/cActionCircle.h"
#include "SP/cCity.h"
#include <stddef.h>
#include "SP/cTribe.h"
#include "SP/cDataSerializationInfo.h"
#include "SP/cSPSpaceToolData.h"

extern float g_negmask;                                 // 0x013eb8b0 (0x80000000 sign mask)

// ---- items of slice s00c9ef20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float  g_1699b08, g_1699b0c, g_1699b10;         // 0x01699b08..
extern void*  g_16c7aa4;                               // 0x016c7aa4
extern void*  g_1474a50[];                             // 0x01474a50 table
extern void*  g_1474a44[];                             // 0x01474a44 table
typedef unsigned int   u32;
typedef unsigned char  u8;
typedef unsigned long long u64;
static inline char* vpt(void* o) { return *(char**)o; }
void* __stdcall SP_PlanetModel(int a);                 // 0x00b3d350 ret 4
void* __stdcall SP_PlanetModel0();                     // 0x00b3d350 no-arg
void* __stdcall SP_NounManager(int id);                // 0x00b3d300 ret 4
void* __cdecl   GetCurrentGameMode();                  // 0x00b5b800
void* __cdecl   FUN_00cf74c0();                        // 0x00cf74c0 returns manager
void* __cdecl   SP_ToolManager();                      // 0x00b3d390 ?ToolManager@@YAPAVcSPToolManager@@XZ (no args)
void* __cdecl   EAAllocate(int size, const char* name, int a, int b, int c, int d);
void* __cdecl   FUN_00c9e5d0();                        // 0x00c9e5d0
void* FUN_00c9efc0();                                  // 0x00c9efc0 no-arg cdecl getter (Vector24 singleton)
struct PlanetStub {
    float* FUN_00b81630(float* out, float* src);            // 0x00b81630
    float* DirectionToSurfacePosition(float* out, float* dir); // 0x00b815a0
    int    GetContinent(float* pos);                        // 0x00b88590
    float  FUN_00b7efe0();                                  // 0x00b7efe0
    float  GetWaterHeight();                                // 0x00b7e390
};
struct NounStub {
    int FUN_00b25f40();                                     // 0x00b25f40
};
struct FieldStub {
    void* FUN_00f3f950(void* arg);                          // 0x00f3f950
};
struct CivMgrStub_s00c9_ef20 {
    void FUN_00cf8d60(void* self, bool changed, u32 flags);  // 0x00cf8d60 ret 0xc
    u8   FUN_00cf7830(void* a);                             // 0x00cf7830 ret 4
};
struct ToolStub {
    u8 FUN_00bfc5d0();                                      // 0x00bfc5d0
};
struct XStub {
    u8 FUN_00c004c0(int a);                                 // 0x00c004c0 ret 4
};
struct SimSingletonStub {
    void* FUN_00dc7d70();                                   // 0x00dc7d70 ctor
    void  FUN_00dcc300(void* a);                            // 0x00dcc300 ret 4
};
struct RefStub {
    u8   FUN_0104bd50();                                    // 0x0104bd50 thiscall, ret 0 (bool in al)
};
struct ToolManagerStub {
    void FUN_0104fa90(void* e);                             // 0x0104fa90 ret 4
};
static inline RefStub* ToolSlot_00c9f250(char* self, int off)
{
    return *(RefStub**)(*(char**)(self + 0xc64) + off);
}
static inline RefStub* ExtraSlotTool_00c9f250(char* self)
{
    return *(RefStub**)(self + 0xb60);
}
struct CivMgrStub {
    void FUN_00cf8d60(void* self, u32 changed, u32 flags);  // 0x00cf8d60 ret 0xc
    u8   FUN_00cf7830(void* a);                             // 0x00cf7830 ret 4
};
struct Vector24Stub {
    void PushUnique(u32 id);
};
struct EffStub {
    void* FUN_00bc97f0(int a, int b, float c, int d);       // 0x00bc97f0 ret 0x10
};
struct VObjStub {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual u8   v24();
    virtual void v28();
    virtual u8   v2c();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3c();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual int  v4c();
    virtual u8   v50();
    virtual void v54();
    virtual u8   v58();
    virtual int  v5c(int a);
};
struct Vec3 {
    float x, y, z;
    Vec3& operator=(const Vec3& o) { x = o.x; y = o.y; z = o.z; return *this; }
    void SetFrom(const Vec3& o) { x = o.x; y = o.y; z = o.z; }
};
struct CStub_s00c9_ef20 {
    // ---- 00c9ef20
    u8 FUN_00c9ef20();  // 0x00c9ef20 (CStub::FUN_00c9ef20)
    // ---- 00c9ef60
    void FUN_00c9ef60(u32 ms);  // 0x00c9ef60 (CStub::FUN_00c9ef60)
    // ---- 00c9f1c0
    void* FUN_00c9f1c0();
    // ---- 00c9f1e0
    void* FUN_00c9f1e0();
    // ---- 00c9f250
    int FUN_00c9f250();
    // ---- 00c9f2d0
    void FUN_00c9f2d0(int a);
    // ---- 00c9f330
    float FUN_00c9f330();
    // ---- 00c9f380
    float FUN_00c9f380();
    // ---- 00c9f3d0
    void* FUN_00c9f3d0();
    // ---- 00c9f410
    u8 FUN_00c9f410();
    // ---- 00c9f490
    u8 FUN_00c9f490(void* a, void* b);  // 0x00c9f490 (CStub::FUN_00c9f490)
    // ---- 00c9f5c0
    void FUN_00c9f5c0();
    // ---- 00c9f650
    float* FUN_00c9f650(Vec3& out);
    // ---- 00c9f6c0
    void FUN_00c9f6c0();
    // ---- 00c9f750
    void FUN_00c9f750(char on);  // 0x00c9f750 (CStub::FUN_00c9f750)
    // ---- 00c9f7c0
    void FUN_00c9f7c0();  // 0x00c9f7c0 (CStub::FUN_00c9f7c0)
    // ---- 00c9fa30
    void FUN_00c9fa30(void* p);
    // ---- 00c9fa70
    void SetStance(u32 stance, char b);  // 0x00c9fa70 (CStub::SetStance)
    // ---- 00c9fb10
    int FUN_00c9fb10(void* p);  // 0x00c9fb10 (CStub::FUN_00c9fb10)
    // ---- 00c9fb40
    void FUN_00c9fb40(float a, int b, int c, float d, float e);  // 0x00c9fb40 (CStub::FUN_00c9fb40)
    // ---- 00c9fc60
    void FUN_00c9fc60(void* p);  // 0x00c9fc60 (CStub::FUN_00c9fc60)
    // ---- 00c9fd40
    void FUN_00c9fd40(void* p);  // 0x00c9fd40 (CStub::FUN_00c9fd40)
    // ---- 00c9fdc0
    float* FUN_00c9fdc0(Vec3& out);  // 0x00c9fdc0 (CStub::FUN_00c9fdc0)
    // ---- 00c9fe40
    u8 FUN_00c9fe40(void* p);  // 0x00c9fe40 (CStub::FUN_00c9fe40)
    // ---- 00c9fee0
    void* FUN_00c9fee0();  // 0x00c9fee0 (CStub::FUN_00c9fee0)
    // ---- 00c9ff40
    void FUN_00c9ff40(int a, float* out1, float* out2);  // 0x00c9ff40 (CStub::FUN_00c9ff40)
    // ---- external callees declared as members
    void  FUN_00c88670(void* p);                            // 0x00c88670 ret 4
    void  FUN_00c886d0(void* p);                            // 0x00c886d0 ret 4
    float* FUN_00d20610();                                  // 0x00d20610
    float FUN_00c9eb80();                                   // 0x00c9eb80

    char pad[4];
};
struct VStub {
    void FUN_00c3f160(void* a, float f);                    // 0x00c3f160 ret 8
};
struct IVehicleIface {
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
    virtual u8   v50();
};
struct IResIface {
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
    virtual u8   v2c();
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
virtual void v9c();
virtual void va0();
virtual void va4();
virtual void va8();
virtual void vac();
virtual void vb0();
virtual void vb4();
    virtual void* vb8(int id);
    virtual void vbc();
    virtual void vc0();
};
struct TimerStub {
    u8   IsRunning();                                       // 0x00feba90
    u64  GetElapsedTime();                                  // 0x00bc3190
    void Restart();                                         // 0x00bc3130
    void FUN_00ff0430(void* p);                             // 0x00ff0430 ret 4
};
struct CStub {
    // ---- 00c9ef20
    int FUN_00c9ef20();
    // ---- 00c9ef60
    void FUN_00c9ef60(u32 ms);
    // ---- 00c9f1c0  (free __fastcall, declared later)
    // ---- 00c9f1e0
    void* FUN_00c9f1e0();
    // ---- 00c9f250
    int FUN_00c9f250();
    // ---- 00c9f2d0
    void FUN_00c9f2d0(int a);
    // ---- 00c9f330
    float FUN_00c9f330();
    // ---- 00c9f380
    float FUN_00c9f380();
    // ---- 00c9f3d0
    void* FUN_00c9f3d0();
    // ---- 00c9f410
    u8 FUN_00c9f410();
    // ---- 00c9f490
    u8 FUN_00c9f490(void* a, void* b);
    // ---- 00c9f5c0
    void FUN_00c9f5c0();
    // ---- 00c9f650
    float* FUN_00c9f650(float* out);
    // ---- 00c9f6c0
    void FUN_00c9f6c0();
    // ---- 00c9f750
    void FUN_00c9f750(char on);
    // ---- 00c9f7c0
    void FUN_00c9f7c0();
    // ---- 00c9fa30
    void FUN_00c9fa30(void* p);
    // ---- 00c9fa70
    void SetStance(u32 stance, char b);
    // ---- 00c9fb10
    int FUN_00c9fb10(void* p);
    // ---- 00c9fb40
    void FUN_00c9fb40(float a, int b, int c, float d, float e);
    // ---- 00c9fc60
    void FUN_00c9fc60(void* p);
    // ---- 00c9fd40
    void FUN_00c9fd40(void* p);
    // ---- 00c9fdc0
    float* FUN_00c9fdc0(float* out);
    // ---- 00c9fe40
    u8 FUN_00c9fe40(void* p);
    // ---- 00c9fee0
    void* FUN_00c9fee0();
    // ---- 00c9ff40
    void FUN_00c9ff40(int a, float* out1, float* out2);
    // ---- external callees declared as members
    void  FUN_00c88670(void* p);                            // 0x00c88670 ret 4
    void  FUN_00c886d0(void* p);                            // 0x00c886d0 ret 4
    float* FUN_00d20610();                                  // 0x00d20610
    float FUN_00c9eb80();                                   // 0x00c9eb80

    char pad[4];
};
// ---- items of slice s00c9ef20 end

// ---- items of slice s00c9de50 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const uint8_t gModeFour;             // 0x01654c04
extern const uint8_t gModeFive;             // 0x01654c05
extern const uint8_t gModeTen;              // 0x01654c10
extern const uint8_t gNullObjectKey;        // 0x0137e8e0
extern const char kSerializerName[];        // 0x01a80d26
extern const uint32_t kSerializerKey;       // 0x0157cac8
extern const float kModeScaleA;             // 0x01474900
extern const float kModeScaleB;             // 0x01474904
extern const float kModeScaleC;             // 0x01474908
extern const float kModeScaleD;             // 0x0147490c
extern const float kExtraRadius;            // 0x013eb95c
extern const float kAreaScale;              // 0x013ec5b4
extern const float kTwo;                    // 0x01470f1c
extern const float kHalf;                   // 0x01471064
extern const float kRealOne;                // 0x01485720
extern const uint32_t kRadiusTable1[];      // 0x01474a28
extern const uint32_t kRadiusTable2[];      // 0x014749ec
struct cString {                                     // retail SP::cString (0x14 bytes)
    uint32_t d[5];
    cString();                                       // 006b5060
    cString(const cString& o);                       // 006b56f0
    ~cString();                                      // 006b5240
};
struct Float3 { float x, y, z; };
struct Vt05 {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
};
struct Vt10 {
virtual void w00();
virtual void w04();
virtual void w08();
virtual void w0c();
virtual void w10();
virtual void w14();
virtual void w18();
virtual void w1c();
virtual void w20();
virtual void w24();
};
struct Vt21 {
virtual void x00();
virtual void x04();
virtual void x08();
virtual void x0c();
virtual void x10();
virtual void x14();
virtual void x18();
virtual void x1c();
virtual void x20();
virtual void x24();
virtual void x28();
virtual void x2c();
virtual void x30();
virtual void x34();
virtual void x38();
virtual void x3c();
virtual void x40();
virtual void x44();
virtual void x48();
virtual void x4c();
    virtual void x50();
};
struct cVehicle;
struct cLoco : Vt10 {
    virtual void  v28();
    virtual int   Slot2c();                 // +0x2c
    virtual void  v30();
    virtual float Slot34();                 // +0x34
virtual void  v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void  v48();
virtual void v4c();
virtual void v50();
virtual void v54();
    virtual bool  Slot58();                 // +0x58

    void* Find(uint32_t id);                // 0x00c41d00
    bool  Write(void* ar);                  // 0x00c448a0
    void  SetValue(float v, int n);         // 0x00c9ece0
    void  SetProperty(float v, int n);      // 0x00c41d20
    void  FormatName(cString* out);         // 0x00c9e5a0
    bool  IsLocalPlayer();                  // 0x00c9e690
};
struct cCombatant : Vt21 {
    virtual float GetFraction();            // +0x58
    uint32_t pad04[(0x38 - 4) / 4];         // +0x04
    float    mValue;                        // +0x38

    void* Find(uint32_t id);                // 0x00bfc380
    bool  Write(void* ar);                  // 0x00bfc4a0
    float GetValue();                       // 0x00bfc490
};
struct cChild5d0 { uint32_t mWord; void* Find(uint32_t id); };   // 0x00abf740
struct cChild638 { uint32_t mWord; void* Find(uint32_t id); };   // 0x00ac0320
struct cChild650 { uint32_t mWord; void* Find(uint32_t id); };   // 0x00c7d050
struct cAttachmentChild {
    uint32_t pad00[(0x5f4) / 4];            // +0x000
    uint32_t mFlags;                        // +0x5f4 (attachment + 0x5fc)
    void Func(int a, int b, float c, int d);    // 0x00bc97f0
};
struct cAttachmentFlags {
    uint32_t pad00[(0x5fc - 0x08) / 4];     // +0x008
    uint32_t mFlags;                        // +0x5fc
};
struct cAttachment {
    uint32_t pad00[2];                      // +0x00
    union {
        cAttachmentChild mChild;            // +0x08
        cAttachmentFlags mFlagsView;        // +0x08
    };
};
struct cGameDataInner {
    uint32_t pad00[(0x1c8) / 4];            // +0x000
    uint32_t mBits;                         // +0x1c8
};
struct cArchiveStream : Vt05 {
    virtual void z14();
    virtual uint32_t GetHandle();           // +0x18
};
struct cArchive : Vt05 {
virtual void y14();
virtual void y18();
virtual void y1c();
    virtual cArchiveStream* Slot20();       // +0x20
};
struct cVarListSerializer {
    uint32_t mPad[(0xa14) / 4];             // +0x000 (retail object; contents not modelled)
    cVarListSerializer(void* owner, uint32_t key, const char* name);   // 0x00692f90
    bool Serialize(cArchive* ar);                                      // 0x00692900
};
struct cVehicle : Vt05 {
    virtual void* Slot14();                 // +0x14
virtual void  v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void  v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void  v38();
virtual void v3c();
virtual void v40();
virtual void v44();
    virtual void  v48();
    virtual int   Slot4c();                 // +0x4c
virtual void  v50();
virtual void v54();
virtual void v58();
    virtual const char* Slot5c();           // +0x5c

    uint32_t pad04[(0x34 - 0x04) / 4];      // +0x004
    cLoco    mLoco;                         // +0x034 (only the vptr is modelled)
    uint32_t pad38[(0xc4 - 0x38) / 4];      // +0x038
    uint32_t mPairIdA;                      // +0x0c4
    uint32_t mPairIdB;                      // +0x0c8
    uint32_t padCC[(0x508 - 0xcc) / 4];     // +0x0cc
    cCombatant mCombatant;                  // +0x508
    uint32_t pad544[(0x5d0 - 0x544) / 4];   // +0x544
    cChild5d0 mChild5d0;                    // +0x5d0
    uint32_t pad5d4[(0x5e8 - 0x5d4) / 4];   // +0x5d4
    cGameDataInner* mpField5e8;             // +0x5e8
    uint32_t pad5ec[(0x638 - 0x5ec) / 4];   // +0x5ec
    cChild638 mChild638;                    // +0x638
    uint32_t pad63c[(0x650 - 0x63c) / 4];   // +0x63c
    cChild650 mChild650;                    // +0x650
    uint32_t pad654[(0x774 - 0x654) / 4];   // +0x654
    uint32_t mField774;                     // +0x774
    uint32_t mField778;                     // +0x778
    uint32_t mField77c;                     // +0x77c
    uint32_t pad780[(0xaf0 - 0x780) / 4];   // +0x780
    cAttachment* mpFieldAF0;                // +0xaf0
    uint32_t mFieldAF4;                     // +0xaf4
    uint32_t mFieldAF8;                     // +0xaf8
    uint32_t padAfc[(0xb1c - 0xafc) / 4];   // +0xafc
    int      mFieldB1c;                     // +0xb1c
    uint32_t mFieldB20;                     // +0xb20
    uint32_t padB24[(0xb90 - 0xb24) / 4];   // +0xb24
    int      mFieldB90;                     // +0xb90
    uint8_t  padB94[0xbce - 0xb94];         // +0xb94
    uint8_t  mFieldBCE;                     // +0xbce
    uint8_t  padBcf[0xc3c - 0xbcf];         // +0xbcf
    Float3   mVecC3c;                       // +0xc3c
    float    mFieldC48;                     // +0xc48
    float    mFieldC4C;                     // +0xc4c
    uint32_t padC50[(0xd04 - 0xc50) / 4];   // +0xc50
    int      mFieldD04;                     // +0xd04
    uint32_t padD08[(0xd24 - 0xd08) / 4];   // +0xd08
    uint32_t mFieldD24;                     // +0xd24
    uint32_t mFieldD28;                     // +0xd28

    void*  BaseFind(uint32_t id);           // 0x00b18460
    bool   BaseWriteAsText(void* ar);       // 0x00bfc860
    char   BaseRemoveOwner();               // 0x00bfc3a0
    bool   BaseWrite(void* ar);             // 0x00b18590

    cVehicle* Find(uint32_t id);            // 0x00c9e610
    void UpdateDamageState();               // 0x00c9e700
    void WriteAsText(void* ar);             // 0x00c9e760
    bool RemoveOwner(int owner);            // 0x00c9e790
    float GetHealthFraction();              // 0x00c9e7c0
    void GetC3C(Float3* out, float* a, float* b);   // 0x00c9e8a0
    float GetFraction();                    // 0x00c9ec00
    bool CanOccupyTerrain(int data);        // 0x00c9e960
    bool Write(cArchive* ar);               // 0x00c9e9e0
    int  GetMode();                         // 0x00c9eaf0
    float GetModeRadius();                  // 0x00c9eb80
    float GetArea();                        // 0x00c9ec50
    void SetDrone(bool on);                 // 0x00c9ec80
    void SetJustEyeCandy(bool on);          // 0x00c9ecb0
    void SetTimer(int v);                   // 0x00c9ee30
    void ConsumeTimer();                    // 0x00c9ee50
    void PlaySomething();                   // 0x00c9eea0
    bool HasBit2000();                      // 0x00c9eed0
    bool IsFlying();                        // 0x00c9eef0
};
struct cConfigManager : Vt10 {
    virtual void v28();
    virtual void v2c();
    virtual uint32_t Slot30(uint32_t id);   // +0x30
};
struct cCivModeStrategy {
    bool HasCivTutorialOccurred(uint32_t id);   // 0x00cf7830
    void DoNext(uint32_t id, int flag);         // 0x00cfa990
};
struct cPlanetModel {
    uint32_t GetAverageRadius(int data);    // 0x00b7e840
    int      GetContinent(int data);        // 0x00b88590
};
struct cCivilization {
    uint32_t pad00[(0x430) / 4];            // +0x000
    uint8_t  mField430;                     // +0x430
    float    Func00bf2170(uint32_t a, uint32_t b);   // 0x00bf2170
};
struct cGameNounManager {
    int GetPlayerEmpireOrMinus1();          // 0x00b1f9d0
    cCivilization* GetPlayerCivilization(); // 0x00b25fb0
    cCivilization* Func00b25f40(int id);    // 0x00b25f40
};
cGameNounManager* NounManager();            // 0x00b3d300
cPlanetModel* PlanetModel();                // 0x00b3d350
cConfigManager* ConfigManager();            // 0x0067dd30
cCivModeStrategy* CivModeStrategyGet();     // 0x00cf74c0
void PropertyPairRead(const uint32_t* pair, float* outFirst, float* outSecond);  // 0x00eed0b0
void WriteUint32(uint32_t handle, uint32_t* pValue, int count, int flags);  // 0x0093aa70
// ---- items of slice s00c9de50 end

// ---- items of slice s00c9ffd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __stdcall FUN_00c9ff40(int, float*, float*);     // 0x00c9ff40
extern "C" void* __cdecl FUN_00eed0b0(void*, float*, float*);       // 0x00eed0b0 PropertyPairRead
extern "C" void* __cdecl SP_GetCurrentGameMode();                   // 0x00b5b800
extern "C" void* __cdecl SP_PlanetModel();                          // 0x00b3d350
extern "C" int   __cdecl SP_GetAverageRadius(void*, const void*);   // 0x00b7e840
extern "C" void* __cdecl SP_LayerManager();                         // 0x0067cb20
extern "C" void* __cdecl SP_PropertyManager();                      // 0x0067de30
extern "C" void  __fastcall FUN_00695b40(void*, void*, void*, const wchar_t*);// 0x00695b40
extern "C" void* __cdecl FUN_00c6f660(void*);                       // 0x00c6f660
extern "C" bool  __cdecl FUN_00c9f490(void*, void*);                // 0x00c9f490 (ret 8)
extern "C" void  __cdecl FUN_00b452f0(void*);                       // 0x00b452f0
extern "C" void  __cdecl FUN_00b4c600(void*, void*, float);         // 0x00b4c600
extern "C" char  __fastcall FUN_00feba90(void*);                    // 0x00feba90 IsRunning
extern "C" void* __cdecl FUN_00b3d310(void*, const void*, void*);   // 0x00b3d310
extern float g_0169a280;     // 2pi (runtime init)
extern float g_0169a288;     // quarter-sine scale
extern float g_0169a284;     // quarter step
extern float g_0157c908;     // cached vector (init -1.0f)
extern float g_0157c914;     // cached vector (init -1.0f)
extern const float g_13eb1bc;   // -1.0f
extern const float g_14749b0;   // 12582912.0f
extern const float g_1471064;   // 0.5f
extern const float g_1470f1c;   // 2.0f
extern const float g_157d284;   // 8.0f
extern const float g_140e87c;   // 0.6666667f
extern const float g_1477fbc;   // 200.0f
extern float g_01677840[];      // 16-entry (float,float) quarter-sine table
typedef void  (__thiscall* TFnV)(void*);
typedef void  (__thiscall* TFnVV)(void*, void*);
typedef void  (__thiscall* TFnVF)(void*, float);
typedef void  (__thiscall* TFnVII)(void*, int, int);
typedef void  (__thiscall* TFnVI)(void*, int);
typedef int   (__thiscall* TFnIII)(void*, int, int);
typedef int   (__thiscall* TFnIU)(void*, unsigned);
typedef void* (__thiscall* TFnP)(void*);
typedef void* (__thiscall* TFnPI)(void*, int);
typedef float*(__thiscall* TFnPF)(void*);
typedef float (__thiscall* TFnF)(void*);
typedef char  (__thiscall* TFnPUUP)(void*, unsigned, unsigned, void**);
typedef bool  (__thiscall* TFnPK)(void*, int);
#define VTFN(p, slot)  ((*(void***)(p))[slot])
struct IDummy {
    void __thiscall SetAttach(int);      // 0x00a04af0
    void __thiscall Rel();               // 0x00a05270
};
extern "C" bool  __cdecl SP_GetPropertyAsVector3(void*, uint32_t, void*); // 0x006a1110
extern "C" uint64_t __fastcall FUN_00bc3190(void*);                 // 0x00bc3190 GetElapsedTime
extern const float g_1485720_s00c9_ffd0;   // 1.0f
extern const float g_13ec4b8_s00c9_ffd0;   // 1e-08f
static void* g_01654c10 = (void*)0x01654c10;   // game-mode sentinel
#define REF_CALL(p, slot)  do { void* _p = (p); \
    if (_p) (*(TFnV)VTFN(_p, slot))(_p); } while(0)
#define IOREF_ADDREF(p)  REF_CALL(p, 0x18)
#define IOREF_RELEASE(p) REF_CALL(p, 0x19)
#define REF_ADDREF(p)   REF_CALL(p, 0)
struct Obj {
    char  pad00[0x34];
    void* vptr34;         // +0x34 subobject vptr
    char  pad38[0xc4 - 0x38];
    char  propC4[0x20];   // +0xc4 (PropertyPairRead source)
    char  pade4[0xb1c - 0xe4];
    int   mLocomotion;    // +0xb1c
    char  padb20[0xbc0 - 0xb20];
    void* mpArray;        // +0xbc0
    char  padbc4[0xd00 - 0xbc4];
    void* mpCreature;     // +0xd00 (cAnimatingCreature)
    char  padd04[0xd64 - 0xd04];
    int   f_d64, f_d68;   // +0xd64, +0xd68
    int   f_d6c, f_d70;   // +0xd6c, +0xd70
    int   f_d74, f_d78;   // +0xd74, +0xd78
    int   f_d7c, f_d80;   // +0xd7c, +0xd80
    int   f_d84, f_d88;   // +0xd84, +0xd88
    float f_d8c;          // +0xd8c
    float f_d90;          // +0xd90
    void* mpEA;           // +0xd94

    // ---- methods (in original address order) ----
    int   __thiscall GetAltTarget();
    bool  __thiscall BringGoalToAltitude(float* target);
    int   __thiscall GetArrayCount();
    int   __thiscall CreateInteract(int key);
    void  __thiscall ClearCreature();
    void  __thiscall ProcessEA();
    int   __thiscall TimerExpired();
};
struct RefOps {
    void* __thiscall CopyCtor(void* src);      // 0x00ca0900
    void* __thiscall AssignA(void* src);       // 0x00ca0940
    void* __thiscall AssignB(void* src);       // 0x00ca09a0
};
struct V3f_E18 { float x, y, z; };
struct E18 { void* p; V3f_E18 v; unsigned u0, u1; };
struct E16 { void* p; unsigned u0, u1; unsigned char b0; };
// ---- items of slice s00c9ffd0 end

// ---- items of slice s00ca1310 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gTwoPi;     // 0x0169a280
extern const float kHalfPi;   // 0x0157c724
extern const float kPi;       // 0x0157c728
struct Vec3_s00ca_1310 {
    float x, y, z;
};
struct PathRequest {
    Vec3_s00ca_1310  startPos;      // +0x00
    Vec3_s00ca_1310  endPos;        // +0x0c
    Vec3_s00ca_1310  startHeading;  // +0x18
    Vec3_s00ca_1310  endHeading;    // +0x24
    bool  startCW;       // +0x30
    bool  endCW;         // +0x31
    char  pad32[2];
    float radius;        // +0x34
    char  pad38[8];
    float c0x, c0y;      // +0x40 center of the start circle (in the tangent frame)
    float c1x, c1y;      // +0x48 center of the end circle
    float t0x, t0y;      // +0x50 tangent point on the start circle
    float t1x, t1y;      // +0x58 tangent point on the end circle
    float arc0;          // +0x60 arc length on the start circle
    float arc1;          // +0x64 arc length on the end circle
    float straight;      // +0x68 straight segment length
    float total;         // +0x6c
    float ang0;          // +0x70 start angle on the start circle
    float ang1;          // +0x74 start angle on the end circle
    float lineAng;       // +0x78 heading of the straight segment
    float lineAng2;      // +0x7c
    Vec3_s00ca_1310  side;          // +0x80 normal of the travel plane
    Vec3_s00ca_1310  dir;           // +0x8c unit vector from start to end
    Vec3_s00ca_1310  mid;           // +0x98 normalized bisector
};
float SignedAngle(const Vec3_s00ca_1310* a, const Vec3_s00ca_1310* b, const Vec3_s00ca_1310* axis);   // 0x006994a0 (cdecl)
static inline void WrapInline(float& x)
{
    while (gTwoPi < x) x -= gTwoPi;
    while (x < 0.0f) x += gTwoPi;
}
struct cPlanetModel_s00ca_1310 {
    void  FUN_00c9ff40(const void* pos, float* height, float* offset);
    void* FUN_00b7f190(void* out, const Vec3_s00ca_1310* pos);
};
struct SurfaceFrame {
    float m[4];
};
struct PathNode {
    Vec3_s00ca_1310  mPos;                 // +0x00
    char  mPad[0x30];           // +0x0c
};
struct PathSplineData {
    PathNode* mpBegin;          // +0x00
    PathNode* mpEnd;            // +0x04
    char      mPad08[0x0c];     // +0x08
    Vec3_s00ca_1310      mCenter;          // +0x14
    char      mPad20[0x24];     // +0x20
};
struct PathSegment {
    Vec3_s00ca_1310  mStartPos;            // +0x00
    char  mPad0c[0x24];         // +0x0c
    bool  mStartCW;             // +0x30
    bool  mEndCW;               // +0x31
    char  mPad32[2];            // +0x32
    float mRadius;              // +0x34
    char  mPad38[8];            // +0x38
    float mCenter40x;           // +0x40
    float mCenter40y;           // +0x44
    float mCenter48x;           // +0x48
    float mCenter48y;           // +0x4c
    float mCenter50x;           // +0x50
    float mCenter50y;           // +0x54
    char  mPad58[8];            // +0x58
    float mStartTime;           // +0x60
    float mMidFlag;             // +0x64
    float mMidDuration;         // +0x68
    float mEndTime;             // +0x6c
    float mPrePhase;            // +0x70
    char  mPad74[4];            // +0x74
    float mStraightAngle;       // +0x78
    float mMidPhase;            // +0x7c
    Vec3_s00ca_1310  mBasisU;              // +0x80
    Vec3_s00ca_1310  mBasisV;              // +0x8c
};
struct PathSolver {
    char mPad[0x10];                   // +0x00
    cPlanetModel_s00ca_1310* mPlanet;             // +0x10
    float WrapAngle(float a);          // 0x00ca11c0
    bool  Solve(PathRequest* p);       // 0x00ca1310
    void  FUN_00ca1c60(PathSplineData* p);                         // 0x00ca1c60
    void  FUN_00ca1dc0(PathSegment* seg, float t, Vec3_s00ca_1310* pos, Vec3_s00ca_1310* out); // 0x00ca1dc0
    Vec3_s00ca_1310* FUN_00ca1210(Vec3_s00ca_1310* out, const PathSegment* seg, float angle); // 0x00ca1210
};
cPlanetModel_s00ca_1310* FUN_00b3d350();                                                   // 0x00b3d350
void FUN_00a78ce0(float angle, float* outSin, float* outCos);                  // 0x00a78ce0
Vec3_s00ca_1310* FUN_0059aed0(Vec3_s00ca_1310* out, const Vec3_s00ca_1310* v, const void* orient);              // 0x0059aed0
bool FUN_0059ab70(const Vec3_s00ca_1310* v);                                              // 0x0059ab70
extern Vec3_s00ca_1310 kDefaultDir;   // 0x0169a28c
// ---- items of slice s00ca1310 end

// ---- items of slice s00ca2210 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl EAllocNew(int size, const char* file, int a, int b, int c, int d); // 0x00f473a0
#define SIM_MODE_ADDR ((void*)0x01654c10)
struct cVehicleState {
    char  mPad0000[0x5fc];
    int   mFlags;              // +0x5fc
};
struct cToolManager {
    void  FUN_00c421b0(void* p);   // 0x00c421b0
    void  FUN_00c43fe0(void* p);   // 0x00c43fe0
};
struct cFlyingLocomotion {
    cFlyingLocomotion* FUN_00caded0();   // 0x00caded0  (constructor)
};
struct cAllocPath {            // 0xd4 bytes
    void*  mVtbl;              // +0x00
    char   mPad04[4];
    void*  mVtbl8;             // +0x08
    int    mField0c;           // +0x0c
    void*  mOwner;             // +0x10
    int    mType;              // +0x14
    float  mVal18;             // +0x18
    char   mFlag1c;            // +0x1c
    char   mFlag1d;            // +0x1d
    char   mPad1e[0xd4 - 0x1e];
};
struct cAllocDriving {         // 0x10 bytes
    void*  mVtbl;              // +0x00
    char   mPad04[4];
    void*  mVtbl8;             // +0x08
    int    mField0c;           // +0x0c
};
struct cVehicle_s00ca_2210 {
    char            mPad00[0x34];
    cToolManager    mToolMgr;         // +0x34
    char            mPad35[0x21c - 0x35];
    float           m21c;             // +0x21c
    char            mPad220[0x224 - 0x220];
    int             m224;             // +0x224
    char            mPad228[0xaf0 - 0x228];
    cVehicleState*  mAf0;             // +0xaf0
    char            mPadAf4[0xb1c - 0xaf4];
    int             mB1c;             // +0xb1c
    char            mPadB20[0xd04 - 0xb20];
    int             mD04;             // +0xd04

    bool  FUN_00ca2210(void* p);            // 0x00ca2210
    bool  FUN_00ca2370(void);               // 0x00ca2370
    void  FUN_00ca28a0(void* p);            // 0x00ca28a0
    void  CreateDefaultTool(void);          // 0x00ca2ae0
    void  FUN_00ca2e80(void);               // 0x00ca2e80
};
// ---- items of slice s00ca2210 end

// ---- items of slice s00ca3030 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float g_14853e0;   // 0x014853e0
extern const float g_1486114;   // 0x01486114
extern const float g_13ec4b4;   // 0x013ec4b4
#pragma intrinsic(sin, cos, sqrt)
struct Vector3 {
    float x, y, z;
};
namespace SP {
class cPlanetModel_s00ca_3030 {
public:
    int GetContinent(const Vector3* p);           // 0x00b88590 (thiscall)
    float GetRadius();                            // 0x00b7e4d0 (thiscall, returns float in st0)
    uint32_t GetTerrainFlags(const Vector3* p);   // 0x00b7e840 (thiscall, ret 4)
    void Project(Vector3* out, const Vector3* in);   // 0x00b81630 (thiscall, ret 8)
};
}
namespace SP {
cPlanetModel_s00ca_3030* PlanetModel_s00ca_3030();                      // 0x00b3d350 (cdecl)
}
using SP::cPlanetModel_s00ca_3030;
struct cSpatialObject_s00ca_3030 {
virtual void s00();
virtual void s01();
virtual void s02();
virtual void s03();
virtual void s04();
virtual void s05();
virtual void s06();
virtual void s07();
virtual void s08();
virtual void s09();
virtual void s10();
    virtual const Vector3* GetPosition();       // +0x2c  (slot 11)
    virtual void s12();                         // +0x30
    virtual float GetScale();                   // +0x34  (slot 13, returns float in st0)
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
    virtual bool GetFlag48();                   // +0x48  (slot 18)
    virtual void s19();                         // +0x4c
    virtual bool GetFlag50();                   // +0x50  (slot 20)
virtual void s21();
virtual void s22();
virtual void s23();
virtual void s24();
virtual void s25();
virtual void s26();
virtual void s27();
virtual void s28();
    virtual float GetRadius();                  // +0x74  (slot 29, returns float in st0)
virtual void s30();
virtual void s31();
virtual void s32();
virtual void s33();
virtual void s34();
virtual void s35();
virtual void s36();
virtual void s37();
virtual void s38();
virtual void s39();
virtual void s40();
virtual void s41();
    virtual void s42();                         // +0xa8
    virtual void* GetTransform();               // +0xac  (slot 43)
virtual void s44();
virtual void s45();
virtual void s46();
virtual void s47();
    virtual void s48();                         // +0xc0
    virtual void ApplyRadius(float r, int zero); // +0xc4  (slot 49)
virtual void s50();
virtual void s51();
virtual void s52();
virtual void s53();
    virtual void s54();                         // +0xd8
    virtual void SubmitGoal(const void* block); // +0xdc  (slot 55)
    void FUN_00ca3410(const Vector3* p, float a, float b, char useCam);   // 0x00ca3410
};
class cGameData_s00ca_3030;
class cGameDataSub {
public:
    cGameData_s00ca_3030& Owner();                          // enclosing object (one named cast)
    Vector3* GetGameDataOwner(Vector3* out);     // 0x00ca3030
    uint8_t pad500[0x500];
};
class cGameData_s00ca_3030 {
public:
    bool mBaseIsSpecial();                       // the base object's vtable slot +0x2c
    virtual void vBase();                        // gives cGameData its vptr at +0

    // +0x000 vtable
    uint8_t pad004[0x34 - 0x04];
    cSpatialObject_s00ca_3030 mSpatial;                     // +0x34
    uint8_t pad038[0xa0 - 0x38];
    uint8_t mCivMode;                            // +0xa0  (written by 0x00ca3350)
    uint8_t pad0a1[0xab - 0xa1];
    uint8_t mSpatialFlag;                        // +0xab  (read by 0x00ca31f0)
    uint8_t pad0ac[0xd0 - 0xac];
    // +0xd0: the property-owning sub-object; its +0x90 pointer is handed to
    // SP::GetPropertyAsTransformArray.
    uint8_t pad0d0[0x90];
    uint32_t mPropertyList;                      // +0x160
    uint8_t pad164[0x218 - 0x164];
    uint32_t mCameraScale;                       // +0x218 (multiplied by the mode scale)
    uint8_t pad21c[0x270 - 0x21c];
    uint32_t m270;                               // +0x270
    uint8_t pad274[0x2a4 - 0x274];
    uint32_t m2a4;                               // +0x2a4  (cleared by 0x00ca3410)
    uint8_t pad2a8[0x508 - 0x2a8];
    cGameDataSub mSub;                           // +0x508 (0x500 bytes)
    uint8_t pad_a08[0xaf0 - 0xa08];
    uint32_t mpFlagHolder;                       // +0xaf0
    uint32_t mReadValue;                         // +0xaf4
    uint8_t pad_af8[0xb20 - 0xaf8];
    uint32_t mSubFlag618;                        // +0xb20
    uint32_t mMode;                              // +0xb24
    uint8_t pad_b28[0xb68 - 0xb28];
    uint32_t mListBegin;                         // +0xb68
    uint32_t mListEnd;                           // +0xb6c
    uint8_t pad_b70[0xb80 - 0xb70];
    Vector3 mMarkerPos;                          // +0xb80
    uint8_t pad_b8c[0xc64 - 0xb8c];
    uint32_t mPointBegin;                        // +0xc64
    uint32_t mPointEnd;                          // +0xc68
    uint8_t pad_c6c[0xc78 - 0xc6c];
    uint32_t mPointIndex;                        // +0xc78

    void FUN_00ca31f0();                         // 0x00ca31f0
    void FUN_00ca3350(char enable);              // 0x00ca3350
    void FUN_00ca33b0(const Vector3* p);         // 0x00ca33b0
    uint8_t FUN_00ca3660(void* stream);          // 0x00ca3660
    void FUN_00c9fb40(float x, float y, float z, float zero, float radius);   // 0x00c9fb40
    void FUN_00c9f6c0();                         // 0x00c9f6c0
};
Vector3* GetGameDataOwner2(cGameData_s00ca_3030* self, Vector3* out);      // 0x00bfc8a0
inline bool cGameData_s00ca_3030::mBaseIsSpecial() {
    typedef char (__thiscall *Fn)(cGameData_s00ca_3030*);
    Fn fn = *(Fn*)((char*)*(void**)this + 0x2c);
    return fn(this) != 0;
}
inline cGameData_s00ca_3030& cSpatial_Owner(cSpatialObject_s00ca_3030* self) {
    return *(cGameData_s00ca_3030*)((char*)self - 0x34);
}
cGameData_s00ca_3030& cGameDataSub::Owner() {
    return *(cGameData_s00ca_3030*)((char*)this - 0x508);
}
extern const float g_1485720_s00ca_3030;   // 0x01485720  _HK_REAL_ONE
extern const float g_13ec4b8_s00ca_3030;   // 0x013ec4b8
extern const float g_14749a8_s00ca_3030;   // 0x014749a8
struct cWorldDesc { uint8_t mFlagAt20; };
cWorldDesc* FUN_00b3d370();                                     // 0x00b3d370
struct cCivModeStrategy_s00ca_3030 {
    uint8_t pad000[0x148];
    uint8_t mFlag148;                            // +0x148
    bool HasCivTutorialOccurred(uint32_t id);    // 0x00cf7830 (thiscall, ret 4)
};
bool HasCivTutorialOccurred(void* self, uint32_t id);           // 0x00cf7830
void FUN_00c9f6c0(cGameData_s00ca_3030* self);                             // 0x00c9f6c0
void TryCivModeTutorial();                                      // 0x00c9e5d0
void FUN_00c9fb40(cGameData_s00ca_3030* self, float x, float y, float z, float a, float b);  // 0x00c9fb40
void* FUN_00f3f950(void* a, void* b);                           // 0x00f3f950
bool GetPropertyAsTransformArray(uint32_t list, uint32_t name, void* out, uint32_t* count);  // 0x006a0c30
void Transform_Ctor(void* transform);                           // 0x00409930
void AssignTransformOps(void* transform, const void* src);      // 0x00537dc0
void LocalToWorldTransform(const void* self, void* out);        // 0x00c897e0
void FUN_0044d4f0(void* transform);                             // 0x0044d4f0
void FUN_00b7e3b0(void* self, Vector3* out, const Vector3* in); // 0x00b7e3b0
void MatOwner_SetB(void* self, const Vector3* p, const Vector3* q);   // 0x006ba840
Vector3* DirectionToSurfacePosition(cPlanetModel_s00ca_3030* pm, Vector3* out, const Vector3* in);  // 0x00b815a0
void cNavigationGoal_InitToward(void* goal, const Vector3* p, const Vector3* dir, float a, float b);  // 0x00ad2a50
struct cGroundLayer { void addInterpolated(const void* desc, float blend); };   // 0x00ac7680
bool ReadInt32(void* stream, int* value);                       // 0x0093a780
bool cGameData_Read(cGameData_s00ca_3030* self, void* stream);             // 0x00b18600
bool FUN_00bfc540(void* stream);                                // 0x00bfc540
bool FUN_00c43c10(void* self, void* stream);                    // 0x00c43c10
void cVarListSerializer_Ctor(void* self, cGameData_s00ca_3030* data, const void* schema, uint32_t id);  // 0x00692f90
bool cVarListSerializer_Read(void* self, void* stream);         // 0x00693e10
void FUN_00ca2e80(cGameData_s00ca_3030* self);                             // 0x00ca2e80
void FUN_00dc4b70(cGameData_s00ca_3030* self);                             // 0x00dc4b70
void FUN_00c9f7c0(cGameData_s00ca_3030* self);                             // 0x00c9f7c0
struct cSPTransform_s00ca_3030 {
    uint16_t mFlags;                    // +0x00
    uint16_t mModificationCount;        // +0x02
    uint16_t pad04;
    Vector3 mTranslation;               // +0x08
    float mScale;                       // +0x14
};
struct cNavGoalBlock {
    uint32_t* mpBuffer0;                // +0x00  (freed after submit)
    uint32_t mWord04;                   // +0x04
    uint32_t mWord08;                   // +0x08
    uint32_t mWord0c;                   // +0x0c
    uint32_t mWord10;                   // +0x10
    Vector3 mDirect;                    // +0x14
    uint32_t mWord20;                   // +0x20
    uint32_t mWord24;                   // +0x24
    uint32_t pad28[0x24 / 4];           // +0x28
    uint32_t mWord4c;                   // +0x4c
    uint32_t mWord50;                   // +0x50
    uint32_t mWord54;                   // +0x54
    uint32_t mWord58;                   // +0x58
    uint32_t mWord5c;                   // +0x5c
    uint32_t mWord60;                   // +0x60
    uint32_t mWord64;                   // +0x64
    uint32_t mWord68;                   // +0x68
    uint32_t mWord6c;                   // +0x6c
    uint32_t mWord70;                   // +0x70
    uint32_t* mpBuffer74;               // +0x74  (freed after submit)
};
// ---- items of slice s00ca3030 end

// ---- items of slice s00ca3f20 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cInterface {
    void* mpVtable;                                          // +0x00
};
struct cManaged {
    cInterface* mpInterface;                                 // +0x00
    uint32_t    mFlags04;                                    // +0x04
    uint32_t    mPad08[14];                                  // +0x08 .. +0x3f
    int32_t     mRefCount40;                                 // +0x40
};
struct cOwner {
    uint8_t   mPad00[0xd0];                                  // +0x00 .. +0xcf
    cManaged* mpManaged;                                     // +0xd0

    void Clear();
};
// ---- items of slice s00ca3f20 end

// ---- items of slice s00ca46c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_RateA;       // 0x0169a274 (base rate; x2 or x4)
extern float g_RateB;       // 0x0169a278
extern float g_RateC;       // 0x0169a27c
extern float g_TwoPiA;      // 0x0169a280
extern float g_PiA;         // 0x0157c728
extern float g_TwoPiB;      // 0x0157c710
extern float g_PiB;         // 0x01474998
struct Vector3_s00ca_46c0 {
    float x, y, z;
    Vector3_s00ca_46c0() {}
    Vector3_s00ca_46c0(float a, float b, float c) : x(a), y(b), z(c) {}
};
struct Quaternion { float x, y, z, w; };
extern Vector3_s00ca_46c0 g_AxisYaw;   // 0x0169a28c
extern Vector3_s00ca_46c0 g_AxisPitch; // 0x0169a298
extern Vector3_s00ca_46c0 g_AxisRoll;  // 0x0169a2a4
float __cdecl SignedAngle(const Vector3_s00ca_46c0* a, const Vector3_s00ca_46c0* b, const Vector3_s00ca_46c0* axis);   // 0x0069b760
float __cdecl ApproachAngle(float current, float target, float step);                 // 0x0069b840
Vector3_s00ca_46c0* __cdecl RotateByQuat(Vector3_s00ca_46c0* out, const Vector3_s00ca_46c0* v, const Quaternion* q);   // 0x0059aed0
Quaternion* __cdecl QuatMul(Quaternion* out, const Quaternion* a, const Quaternion* b); // 0x007dcb00
struct ICameraState {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
virtual void s10();
    virtual const Vector3_s00ca_46c0* GetPosition();                  // +0x2c
    virtual const Quaternion* GetOrientation();            // +0x30
virtual void s13();
virtual void s14();
    virtual void SetOrientation(const Quaternion* q);      // +0x3c
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
virtual void s22();
    virtual void GetUpReference(Vector3_s00ca_46c0* out);             // +0x5c
};
struct CameraOwner {
    uint32_t pad[13];
    ICameraState mState;   // +0x34
};
struct cCameraFollow {
    uint32_t pad[4];
    CameraOwner* mpOwner;  // +0x10
    int mMode;             // +0x14
    bool Step(const Vector3_s00ca_46c0* pTarget, float dt);
};
__forceinline float WrapSigned(float v)
{
    float r = (float)fmod((double)v, (double)g_TwoPiA);
    if (r > g_PiA)
        r -= g_TwoPiA;
    else if (-g_PiA > r)
        r += g_TwoPiA;
    return r;
}
__forceinline float WrapDelta(float v)
{
    float r = (float)fmod((double)v, (double)g_TwoPiB);
    if (r >= g_PiB)
        r -= g_TwoPiB;
    return r;
}
__forceinline void RotateAbout(Quaternion& cur, const Vector3_s00ca_46c0& axis, float angle)
{
    float s = (float)sin((double)(angle * 0.5f));
    float c = (float)cos((double)(angle * 0.5f));
    Quaternion q;
    q.x = s * axis.x;
    q.y = s * axis.y;
    q.z = s * axis.z;
    q.w = c;
    Quaternion out;
    cur = *QuatMul(&out, &cur, &q);
}
// ---- items of slice s00ca46c0 end

// ---- items of slice s00ca4f90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kQuarterPi;   // 0x0157c720
extern const float kTwoPi;       // 0x0157c710
extern const float kPiB;         // 0x01474998
extern float gTurnRateScale;     // 0x0157c708 (1.0f)
extern float gPitchRate;           // 0x0169a278
extern float gRollRate;          // 0x0169a27c
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
struct Vector3_s00ca_4f90 {
    float x, y, z;
    Vector3_s00ca_4f90() {}
    Vector3_s00ca_4f90(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3_s00ca_4f90(const Vector3_s00ca_4f90& v) : x(v.x), y(v.y), z(v.z) {}
    Vector3_s00ca_4f90& operator=(const Vector3_s00ca_4f90& v) { x = v.x; y = v.y; z = v.z; return *this; }
    Vector3_s00ca_4f90 Cross(const Vector3_s00ca_4f90& b) const
    {
        return Vector3_s00ca_4f90(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
    }
    float Dot(const Vector3_s00ca_4f90& b) const { return x * b.x + y * b.y + z * b.z; }
};
struct Quaternion_s00ca_4f90 {
    float x, y, z, w;
    Quaternion_s00ca_4f90() {}
    Quaternion_s00ca_4f90(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
    Quaternion_s00ca_4f90(const Quaternion_s00ca_4f90& q) : x(q.x), y(q.y), z(q.z), w(q.w) {}

    Quaternion_s00ca_4f90 operator*(const Quaternion_s00ca_4f90& b) const
    {
        Vector3_s00ca_4f90 av(x, y, z);
        Vector3_s00ca_4f90 bv(b.x, b.y, b.z);
        Vector3_s00ca_4f90 c = av.Cross(bv);
        return Quaternion_s00ca_4f90(w * b.x + b.w * x + c.x,
                          w * b.y + b.w * y + c.y,
                          w * b.z + b.w * z + c.z,
                          w * b.w - av.Dot(bv));
    }
    __forceinline Quaternion_s00ca_4f90& operator*=(const Quaternion_s00ca_4f90& b)
    {
        Quaternion_s00ca_4f90 r = *this * b;
        x = r.x; y = r.y; z = r.z; w = r.w;
        return *this;
    }
    Quaternion_s00ca_4f90 Normalized() const
    {
        float inv = 1.0f / sqrtf(w * w + z * z + y * y + x * x);
        return Quaternion_s00ca_4f90(x * inv, y * inv, z * inv, w * inv);
    }
};
inline Quaternion_s00ca_4f90 AxisAngle(const Vector3_s00ca_4f90& axis, float angle)
{
    float h = angle * 0.5f;
    float s = sinf(h);
    float c = cosf(h);
    return Quaternion_s00ca_4f90(axis.x * s, axis.y * s, axis.z * s, c);
}
Vector3_s00ca_4f90 RotateByQuaternion(const Vector3_s00ca_4f90& v, const Quaternion_s00ca_4f90& q);                    // 0x0059aed0
float SignedAngleNormalized(const Vector3_s00ca_4f90& a, const Vector3_s00ca_4f90& b, const Vector3_s00ca_4f90& axis);  // 0x0069b760
float AngleStepToward(float a, float b, float maxStep);                               // 0x0069b840
extern const Vector3_s00ca_4f90 kAxisRoll;  // 0x0169a28c
extern const Vector3_s00ca_4f90 kAxisPitch;   // 0x0169a298 (also the reference heading)
extern const Vector3_s00ca_4f90 kAxisTurn; // 0x0169a2a4
struct ILocomotion {
    PV8 PV2 PV
    virtual const Vector3_s00ca_4f90& GetPosition();              // +0x2c
    virtual const Quaternion_s00ca_4f90& GetOrientation();        // +0x30
    PV2
    virtual void SetOrientation(const Quaternion_s00ca_4f90& q);  // +0x3c
    PV4 PV2 PV
    virtual Vector3_s00ca_4f90 GetFacing();                       // +0x5c
};
struct cLocomotionOwner {
    uint32_t pad00[0xd];
    ILocomotion mLocomotion;                         // +0x34
    uint8_t pad38[0xac4];
    bool mbAFC;                                      // +0xafc
    int GetMoveType();                               // 0x00c9eaf0
};
struct cPathLocomotion {
    uint32_t vtbl;
    uint32_t pad04[3];
    cLocomotionOwner* mpOwner;                       // +0x10
    uint32_t pad14[0xf];
    bool mbBankBefore;                               // +0x50
    bool mbBankAfter;                                // +0x51
    uint8_t pad52[0x2e];
    float mSpanStart;                                // +0x80
    float mBankAfter;                                // +0x84
    float mSpanLength;                               // +0x88
    uint32_t pad8c[0x11];
    float mT;                                        // +0xd0

    void Steer(Vector3_s00ca_4f90 dir, float dt, float speed, int accelSign);
};
static inline float WrapAngleMod(float a)
{
    float x = (float)fmod((double)a, (double)gTwoPi);
    if (x > kPi)
        x -= gTwoPi;
    else if (x < -kPi)
        x += gTwoPi;
    return x;
}
static inline float WrapAngle(float x)
{
    x = (float)fmod((double)x, (double)kTwoPi);
    if (kPiB <= x)
        x -= kTwoPi;
    return x;
}
static inline Vector3_s00ca_4f90 RejectFrom(const Vector3_s00ca_4f90& v, const Vector3_s00ca_4f90& n)
{
    float d = v.Dot(n);
    return Vector3_s00ca_4f90(v.x - d * n.x, v.y - n.y * d, v.z - n.z * d);
}
// ---- items of slice s00ca4f90 end

// ---- items of slice s00ca5b10 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3_s00ca_5b10 {
    float x, y, z;
    Vector3_s00ca_5b10() {}
    Vector3_s00ca_5b10(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3_s00ca_5b10(const Vector3_s00ca_5b10& v) : x(v.x), y(v.y), z(v.z) {}
    Vector3_s00ca_5b10& operator=(const Vector3_s00ca_5b10& v) { x = v.x; y = v.y; z = v.z; return *this; }
    Vector3_s00ca_5b10 Cross(const Vector3_s00ca_5b10& b) const
    {
        return Vector3_s00ca_5b10(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
    }
    float Dot(const Vector3_s00ca_5b10& b) const { return x * b.x + y * b.y + z * b.z; }
    Vector3_s00ca_5b10 operator+(const Vector3_s00ca_5b10& b) const { return Vector3_s00ca_5b10(x + b.x, y + b.y, z + b.z); }
};
inline Vector3_s00ca_5b10 operator*(float s, const Vector3_s00ca_5b10& v) { return Vector3_s00ca_5b10(s * v.x, s * v.y, s * v.z); }
struct Quaternion_s00ca_5b10 {
    float x, y, z, w;
    Quaternion_s00ca_5b10() {}
    Quaternion_s00ca_5b10(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
    Quaternion_s00ca_5b10(const Quaternion_s00ca_5b10& q) : x(q.x), y(q.y), z(q.z), w(q.w) {}

    Quaternion_s00ca_5b10 operator*(const Quaternion_s00ca_5b10& b) const
    {
        Vector3_s00ca_5b10 av(x, y, z);
        Vector3_s00ca_5b10 bv(b.x, b.y, b.z);
        Vector3_s00ca_5b10 v = w * bv + b.w * av + av.Cross(bv);
        return Quaternion_s00ca_5b10(v.x, v.y, v.z, w * b.w - av.Dot(bv));
    }
    __forceinline Quaternion_s00ca_5b10& operator*=(const Quaternion_s00ca_5b10& b)
    {
        Quaternion_s00ca_5b10 r = *this * b;
        x = r.x; y = r.y; z = r.z; w = r.w;
        return *this;
    }
    Quaternion_s00ca_5b10 Normalized() const
    {
        float inv = 1.0f / sqrtf(w * w + z * z + y * y + x * x);
        return Quaternion_s00ca_5b10(x * inv, y * inv, z * inv, w * inv);
    }
};
inline Quaternion_s00ca_5b10 AxisAngle_s00ca_5b10(const Vector3_s00ca_5b10& axis, float angle)
{
    float h = angle * 0.5f;
    float s = sinf(h);
    float c = cosf(h);
    return Quaternion_s00ca_5b10(axis.x * s, axis.y * s, axis.z * s, c);
}
Vector3_s00ca_5b10 RotateByQuaternion(const Vector3_s00ca_5b10& v, const Quaternion_s00ca_5b10& q);                    // 0x0059aed0
float SignedAngleNormalized(const Vector3_s00ca_5b10& a, const Vector3_s00ca_5b10& b, const Vector3_s00ca_5b10& axis);  // 0x0069b760
extern const Vector3_s00ca_5b10 kAxisRoll_s00ca_5b10;  // 0x0169a28c
extern const Vector3_s00ca_5b10 kAxisPitch_s00ca_5b10;   // 0x0169a298 (also the reference heading)
extern const Vector3_s00ca_5b10 kAxisTurn_s00ca_5b10; // 0x0169a2a4
struct ILocomotion_s00ca_5b10 {
    PV8 PV2 PV
    virtual const Vector3_s00ca_5b10& GetPosition();              // +0x2c
    virtual const Quaternion_s00ca_5b10& GetOrientation();        // +0x30
    PV2
    virtual void SetOrientation(const Quaternion_s00ca_5b10& q);  // +0x3c
    PV4 PV2 PV
    virtual Vector3_s00ca_5b10 GetFacing();                       // +0x5c
};
struct cLocomotionOwner_s00ca_5b10 {
    uint32_t pad00[0xd];
    ILocomotion_s00ca_5b10 mLocomotion;                         // +0x34
};
struct cPathLocomotion_s00ca_5b10 {
    uint32_t vtbl;
    uint32_t pad04[3];
    cLocomotionOwner_s00ca_5b10* mpOwner;                       // +0x10
    uint32_t pad14[3];
    uint32_t mPath[0xe];                             // +0x20
    uint32_t pad58[0x1e];
    float mT;                                        // +0xd0

    void Evaluate(void* path, float t, Vector3_s00ca_5b10* pos, Vector3_s00ca_5b10* dir);   // 0x00ca1dc0
    void Turn(Vector3_s00ca_5b10 dir, float dt);
};
static inline float WrapAngleMod_s00ca_5b10(float a)
{
    float x = (float)fmod((double)a, (double)gTwoPi);
    if (x > kPi)
        return x - gTwoPi;
    if (x < -kPi)
        return x + gTwoPi;
    return x;
}
static inline float WrapAngle_s00ca_5b10(float x)
{
    float r = (float)fmod((double)x, (double)kTwoPi);
    if (kPiB <= r)
        return r - kTwoPi;
    return r;
}
static inline Vector3_s00ca_5b10 RejectFrom_s00ca_5b10(const Vector3_s00ca_5b10& v, const Vector3_s00ca_5b10& n)
{
    float d = v.Dot(n);
    return Vector3_s00ca_5b10(v.x - d * n.x, v.y - n.y * d, v.z - n.z * d);
}
// ---- items of slice s00ca5b10 end

// ---- items of slice s00ca6630 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int __cdecl atexit(void (__cdecl*)(void));
extern float g_01699b08;        // 0x01699b08
extern float g_01699b0c;        // 0x01699b0c
extern float g_01699b10;        // 0x01699b10
extern float g_1400a58;         // 0x01400a58
extern unsigned int g_list_a_flags;     // 0x01699adc
extern int g_list_a_data[3];            // 0x01699ac8
extern int g_list_a_alt;                // 0x0169a104
extern unsigned int g_list_b_flags;     // 0x01699af8
extern void* g_list_b_cell;             // 0x01699ae0
extern void* g_list_b_zero;             // 0x01699af0
extern void* g_list_b_result;           // 0x01699af4
struct ExtObj {
    void __thiscall ClearCreature();                    // 0x00ca0430
    void __thiscall SetModelKey(void* key);             // 0x00c88810
    void __thiscall ResetModel();                       // 0x00ca42c0
    void __thiscall ResetCreature();                    // 0x00ca3f20
    void* __thiscall GetProfile(void* key);             // 0x004df550
    void __thiscall SetByte(unsigned char value);       // 0x00bfc470
    void __thiscall SetFlags(int, int, float, int);     // 0x00bc97f0
    void* __thiscall Get74(void* self);                 // 0x00f3f950
    void* __thiscall GetData();                         // 0x00b18530
    char __thiscall Test(int offset);                   // 0x00f25080
    void __thiscall SetA(void* value);                  // 0x00ca33b0
    void __thiscall KillEffect(void* value);            // not used directly
};
struct EastlString {
    void __thiscall Assign(const char* first, const char* last); // 0x00454cb0
};
void __cdecl FUN_013c4400(void);
void __cdecl FUN_013c4420(void);
void __cdecl FUN_00f47380(void*);                       // operator delete
void* __cdecl FUN_00401090(void);                       // editor species manager
void* __cdecl FUN_00a206f0(void);                       // EA::Audio::GetSystemAT
void* __cdecl FUN_00b5b800(void);                       // SP::GetCurrentGameMode
unsigned __cdecl FUN_00435e90(void);                    // GetRecorderState
void __cdecl FUN_00435ed0(void* space, unsigned value); // SP::cSPUISpace::KillSetiEffects
void __cdecl FUN_00421cf0(void* message);               // SlotMessage::Destruct
void __cdecl FUN_00d9a290(int a, void* b, void* c, void* d);
void* __cdecl FUN_00883860(void);                        // EA::Messaging::GetServer
char __cdecl FUN_00c9e8e0(int a, void* b);
struct Vec3_s00ca_6630 { float x, y, z; };
struct cActionCircle {
    struct tSlot {
        bool mOccupied;              // +0x00
        char _pad0[3];
        void* mpReservingNoun;       // +0x04
        unsigned int mReservingId;   // +0x08
        Vec3_s00ca_6630 mPos;                   // +0x0c
    };
    struct SlotVector {
        tSlot* mpBegin;              // +0x00
        tSlot* mpEnd;                // +0x04
        tSlot* mpCapacity;           // +0x08
        int mAllocator[2];           // +0x0c
    };

    char pad00[0x50];
    SlotVector mSlots;               // +0x50

    void __thiscall Construct();                                     // 0xafba10
    void __thiscall SetAtCenter(const Vec3_s00ca_6630* center, float radius,
                                const Vec3_s00ca_6630* facing, float altitude); // 0xaf9cf0
    void __thiscall SetSlotRadius(int index, float radius);          // 0xafef10
    void __thiscall Destroy();                                       // 0xafbad0
};
struct NounManager_s00ca_6630 {
    void* __thiscall FindNoun(unsigned int id);                      // 0xb25f40
};
struct NounContainer {
    void* mpBegin;                                                   // +0x00
    void* mpEnd;                                                     // +0x04
};
struct Noun {
    NounContainer* __thiscall GetContainer();                        // 0xbef6c0
};
struct cCity {
    Vec3_s00ca_6630* __thiscall GetVehicleSpawnPoint(Vec3_s00ca_6630* out, int kind);      // 0xbdca30
};
NounManager_s00ca_6630* __cdecl SP_NounManager();                               // 0xb3d300
void* __cdecl FUN_00ac9310(NounContainer* c, Vec3_s00ca_6630* pos, bool flag);  // 0xac9310
struct Timer {
    unsigned __int64 __thiscall GetElapsedTime();        // 0x00bc3190
    void __thiscall Restart();                           // 0x00bc3130
};
struct PlanetModel_s00ca_6630 {
    unsigned int __thiscall GetAverageRadius(Vec3_s00ca_6630* p);   // 0x00b7e840
};
PlanetModel_s00ca_6630* __cdecl GetPlanetModel();                   // 0x00b3d350
#define G_GAME_DATA      (*(int*)0x016c7aa4)
struct BlockList {
    char pad00[0xb34];
    unsigned* mpCur;        // +0xb34
    int* mpBlock;           // +0xb38
    unsigned* mpEnd;        // +0xb3c
    int* mpBlockPtr;        // +0xb40
    unsigned* mpLimit;      // +0xb44
};
struct ObjectAt508 {
    void** mpVtbl;          // +0x00
};
struct Object71d0 {
    char pad00[0x508];
    ObjectAt508 mObject;    // +0x508
    char pad50c[0xb68 - 0x50c];
    void* mpCur;            // +0xb68
    void* mpEnd;            // +0xb6c
};
struct StringOwner {
    char pad00[0xd14];
    char mString;           // +0xd14
    void __thiscall FUN_00ca7250(char* text);
};
struct ModelKey {
    char pad00[4];
    unsigned mMagic;        // +0x04
};
struct SpatialObject {
    char pad00[0xcd0];
    void* mpProfile;        // +0xcd0
    void __thiscall FUN_00ca7520(ModelKey* key);
};
struct Self6db0 {
    char pad00[0x18];
    void* mp18;             // +0x18
    char pad1c[0x34 - 0x1c];
    ObjectAt508 mSub34;     // +0x34
    char pad38[0x2a0 - 0x38];
    float m2a0;             // +0x2a0
    char pad2a4[0xaf0 - 0x2a4];
    int* mpAf0;             // +0xaf0
    char padAf4[0xafc - 0xaf4];
    unsigned char mAfC;     // +0xafc
    char padAfD[0xb00 - 0xafd];
    void* mpB00;            // +0xb00
};
struct MessageBasicRC5 {
    void* mpVtbl;           // +0x00
    volatile int mRefCount; // +0x04
    void* mData0;           // +0x08
    char pad0c[0x10 - 0x0c];
    unsigned mData1;        // +0x10
    char pad14[0x30 - 0x14];
    unsigned mId;           // +0x30
    char pad34[0x38 - 0x34];
    int mRCFlags;           // +0x38
    char pad3c[4];
};
struct Self6ff0 {
    char pad34[0x34];
    ObjectAt508 mSub34;     // +0x34
    char pad38[0xaf0 - 0x38];
    int* mpAf0;             // +0xaf0
    char padAf4[0xb20 - 0xaf4];
    int mB20;               // +0xb20
    char padB24[0xbcc - 0xb24];
    unsigned char mBcc;     // +0xbcc
    char padBcd[0xc88 - 0xbcd];
    Timer mTimer1;          // +0xc88
    char padC9c[0xca8 - 0xc9c];
    Timer mTimer2;          // +0xca8
    void __thiscall FUN_00ca6ff0(void* arg);
};
struct Self72a0 {
    char pad34[0x34];
    ObjectAt508 mSub34;     // +0x34
    char pad38[0x508 - 0x38];
    ObjectAt508 m508;       // +0x508
    char pad50c[0xb1c - 0x50c];
    int mB1c;               // +0xb1c
};
// ---- items of slice s00ca6630 end

// ---- items of slice s00ca75e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl FUN_00f473a0(uint32_t size, const char* name, int a, int b, int c, int d);  // 0x00f473a0 operator_new
extern "C" void  __cdecl FUN_0093a780(void* stream, void* out, int n, int b);                          // 0x0093a780 ReadInt32
extern "C" void  __cdecl FUN_0093aa70(void* stream, void* out, int n, int b);                          // 0x0093aa70 WriteUint32
extern "C" void* __cdecl FUN_0093c5a0(void* out, int value, int unused);                               // 0x0093c5a0 EA::ConvertToString16
extern "C" char  __cdecl FUN_00ac8050(void* archive, int key, void* elem);                             // 0x00ac8050 read list element
extern "C" void* __cdecl FUN_00b3d290(void* str, void* v);                                             // 0x00b3d290
extern "C" void* __cdecl FUN_01021300();                                                               // 0x01021300 SP::cSPLivingUniverse::GetPlayerEmpire
extern float g_01473c70;   // 0x01473c70
extern float g_013ef568;   // 0x013ef568
extern float g_01485720;   // 0x01485720  _HK_REAL_ONE
extern float g_01470f1c;   // 0x01470f1c
extern float g_013eb1bc;   // 0x013eb1bc
extern char  g_01654c04;   // 0x01654c04
extern char  g_01667bac;   // 0x01667bac  ?gEmptyString16@eastl@@3PA_WA
extern char  g_01667bad;   // 0x01667bad
extern char  g_01667bae;   // 0x01667bae
extern const wchar_t g_01565b2c[];  // 0x01565b2c
extern const wchar_t g_01565b40[];  // 0x01565b40
extern const wchar_t g_01565b54[];  // 0x01565b54
#define VF(obj, slot) (*(void**)((char*)*(void**)(obj) + (slot) * 4))
struct cSPVector3_s00ca_75e0 { float x, y, z; };
struct cSPVector4_s00ca_75e0 { float x, y, z, w; };
struct eWstring {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    void* mAllocator;
    void FUN_00423650(const wchar_t* first, const wchar_t* last);  // 0x00423650 eastl::wstring::assign
    void FUN_0056e2d0(const void* other);                          // 0x0056e2d0 eastl::wstring copy-ctor
    void FUN_00579a90(const wchar_t* p);                           // 0x00579a90 eastl::wstring::range_initialize
};
struct DeqIter {
    uint32_t*  mpCurrent;
    uint32_t*  mpBegin;
    uint32_t*  mpEnd;
    uint32_t** mpCurrentArrayPtr;
};
struct UIntDeque {
    uint32_t* mpPtrArray;      // +0x00
    uint32_t  mnPtrArraySize;  // +0x04
    DeqIter   mItBegin;        // +0x08
    DeqIter   mItEnd;          // +0x18
    uint32_t  mAllocator;      // +0x28

    void FUN_00996460();        // 0x00996460 deque::clear
    void FUN_0098b5e0();        // 0x0098b5e0 deque::~deque
    void FUN_01045370(const uint32_t* v);  // 0x01045370 deque::push_back slow path

    void push_back(const uint32_t& value) {
        uint32_t* cur = mItEnd.mpCurrent;
        uint32_t* nxt = cur + 1;
        if (nxt != mItEnd.mpEnd) {
            mItEnd.mpCurrent = nxt;
            if (cur) *cur = value;
        } else {
            FUN_01045370(&value);
        }
    }
};
struct cGonzagoTimer {
    void**  mpVtbl;        // +0x00
    uint8_t mData[0x1c];   // +0x04

    void FUN_00b63890();        // 0x00b63890 ctor
    void FUN_00b638b0();        // 0x00b638b0 dtor
    bool FUN_00feba90();        // 0x00feba90 IsRunning
    void FUN_00bc3130();        // 0x00bc3130 Restart
    void FUN_00bc3110();        // 0x00bc3110 Stop
};
struct Opaque {
    void FUN_00b18660();   // 0x00b18660 SP::cGameData::cGameData
    void FUN_00b184c0();   // 0x00b184c0 SP::cGameData::~cGameData
    void FUN_00c43860();   // 0x00c43860 ctor at +0x34
    void FUN_00c432e0();   // 0x00c432e0 dtor at +0x34
    void FUN_00bfd4e0();   // 0x00bfd4e0 SP::cCombatant::cCombatant
    void FUN_00bfcd00();   // 0x00bfcd00 dtor at +0x508
    void FUN_00abfe50();   // 0x00abfe50 ctor at +0x5d0
    void FUN_00abfec0();   // 0x00abfec0 dtor at +0x5d0
    void FUN_00ac03d0();   // 0x00ac03d0 SP::cInteractionTarget::cInteractionTarget
    void FUN_00ac0520();   // 0x00ac0520 dtor at +0x638
    void FUN_00c7d700();   // 0x00c7d700 ctor at +0x650
    void FUN_00c7d650();   // 0x00c7d650 dtor at +0x650
    void FUN_00ca75a0();   // 0x00ca75a0 dtor at +0xb68
    void FUN_00ca43e0();   // 0x00ca43e0 dtor at +0xc64
    void FUN_00ae6930();   // 0x00ae6930 dtor at +0xb8c
    void FUN_00ca09f0(int); // 0x00ca09f0 deque init at +0xb2c
};
struct OpaqueInit { void FUN_00ca09f0(int n); };
struct ContainerB68 { uint32_t m[5]; };  // size 0x14 (+0xb68)
struct ContainerC64 { uint32_t m[5]; };  // size 0x14 (+0xc64)
struct IntsB8C      { uint32_t m[3]; };  // size 0x0c (+0xb8c)
struct Base650 {
    void**  mpVtbl;        // +0x000
    uint8_t mRest[0x49c];  // +0x004
};
class cListArchive {
public:
    virtual void  v00(const wchar_t* name);  // +0x00 begin list
    virtual void  v04(const wchar_t* name);  // +0x04 end list
    virtual void  v08();                     // +0x08
    virtual void  v0c();                     // +0x0c
    virtual void  v10();                     // +0x10
    virtual void  v14();                     // +0x14
    virtual void* v18();                     // +0x18
    virtual void* v1c();                     // +0x1c
    virtual void* v20();                     // +0x20
    virtual void  v24();                     // +0x24
    virtual void  v28();                     // +0x28
    virtual void  v2c(void* v);              // +0x2c
};
struct cPlanetModel_s00ca_75e0 {
    uint8_t pad0[0x64];
    int32_t mI64;                            // +0x64
    void* FUN_00b88590(cSPVector3_s00ca_75e0* pos);     // 0x00b88590 GetContinent
};
struct cCity_s00ca_75e0 {
    cSPVector3_s00ca_75e0* FUN_00fa0e00();  // 0x00fa0e00 GetPositionPtr
    void*       FUN_00bd8210();  // 0x00bd8210 GetContinent
};
extern "C" cPlanetModel_s00ca_75e0* __cdecl FUN_00b3d350_s00ca_75e0();                                                       // 0x00b3d350 SP::PlanetModel
struct OrderMgr { void* FUN_00bcb2a0(); void FUN_00bcae90(); };  // 0x00bcb2a0 ctor / 0x00bcae90 dtor
struct RcObj    { void FUN_00ac65d0(); };                        // 0x00ac65d0
namespace Simulator {
class cVehicle_s00ca_75e0 {
public:
    // +0x000
    void** mpVtbl000;
    void** mpVtbl004;
    uint8_t mPad008[0x2c];
    void** mpVtbl034;          // +0x034 locomotor sub-object vptr
    uint8_t mPad038[0x50];
    int32_t mI088;             // +0x088
    uint8_t mPad08C[0x7c];
    void** mpVtbl108;          // +0x108
    uint8_t mPad10C[0xd0];
    cSPVector3_s00ca_75e0 mVec1DC;        // +0x1dc
    cSPVector3_s00ca_75e0 mVec1E8;        // +0x1e8
    float mF1F4;               // +0x1f4
    float mF1F8;               // +0x1f8
    uint8_t mPad1FC[0x1c];
    float mF218;               // +0x218
    uint8_t mPad21C[0x88];
    int32_t mI2A4;             // +0x2a4
    uint8_t mPad2A8[0x244];
    uint32_t mU4EC;            // +0x4ec
    uint8_t mPad4F0[0x18];
    void** mpVtbl508;          // +0x508
    uint8_t mPad50C[5];
    uint8_t mB511;             // +0x511
    uint8_t mPad512[0x2e];
    float mF540;               // +0x540
    uint8_t mPad544[0x8c];
    void** mpVtbl5D0;          // +0x5d0
    uint8_t mPad5D4[0x64];
    void** mpVtbl638;          // +0x638
    uint8_t mPad63C[0x14];
    Base650 mBase650;          // +0x650
    void* mPaf0;               // +0xaf0
    uint8_t mBaf4;             // +0xaf4
    uint8_t mPadAF5[3];
    uint32_t mUaf8;            // +0xaf8
    uint8_t mBafc;             // +0xafc
    uint8_t mPadAFD[3];
    uint32_t mUb00;            // +0xb00
    uint32_t mUb04;            // +0xb04
    int32_t mIb08;             // +0xb08
    float mFb0c;               // +0xb0c
    float mFb10;               // +0xb10
    float mFb14;               // +0xb14
    float mFb18;               // +0xb18
    int32_t mIb1c;             // +0xb1c
    uint32_t mUb20;            // +0xb20
    uint32_t mUb24;            // +0xb24
    uint32_t mUb28;            // +0xb28
    UIntDeque mEvents;         // +0xb2c
    float mFb58;               // +0xb58
    void* mPb5c;               // +0xb5c
    void* mPb60;               // +0xb60
    void* mPb64;               // +0xb64
    ContainerB68 mContainerB68; // +0xb68
    void* mPb7c;               // +0xb7c
    float mFb80;               // +0xb80
    float mFb84;               // +0xb84
    float mFb88;               // +0xb88
    IntsB8C mB8C;              // +0xb8c
    uint8_t mPadB98[8];
    cGonzagoTimer mTimerBA0;   // +0xba0
    void* mPbc0;               // +0xbc0
    int32_t mIbc4;             // +0xbc4
    uint32_t mUbc8;            // +0xbc8
    uint8_t mBcc[6];           // +0xbcc
    uint8_t mPadBD2[6];
    cGonzagoTimer mTimerBD8;   // +0xbd8
    cGonzagoTimer mTimerBF8;   // +0xbf8
    cGonzagoTimer mTimerC18;   // +0xc18
    uint32_t mUc38;            // +0xc38
    uint8_t mPadC3C[0xc];
    float mFc48;               // +0xc48
    float mFc4c;               // +0xc4c
    float mFc50;               // +0xc50
    float mFc54;               // +0xc54
    float mFc58;               // +0xc58
    float mFc5c;               // +0xc5c
    float mFc60;               // +0xc60
    ContainerC64 mContainerC64; // +0xc64
    uint32_t mUc78;            // +0xc78
    uint32_t mUc7c;            // +0xc7c
    uint32_t mUc80;            // +0xc80
    uint32_t mUc84;            // +0xc84
    cGonzagoTimer mTimerC88;   // +0xc88
    cGonzagoTimer mTimerCA8;   // +0xca8
    eWstring mName;            // +0xcc8
    cGonzagoTimer mTimerCD8;   // +0xcd8
    uint8_t mPadCF8[4];
    void* mPcfc;               // +0xcfc
    void* mPd00;               // +0xd00
    uint32_t mUd04;            // +0xd04
    uint32_t mUd08;            // +0xd08
    uint32_t mUd0c;            // +0xd0c
    uint8_t mBd10;             // +0xd10
    uint8_t mPadD11[3];
    eWstring mWd14;            // +0xd14
    uint32_t mUd24;            // +0xd24
    uint8_t mPadD28[4];
    float mFd2c;               // +0xd2c
    int32_t mId30;             // +0xd30
    cSPVector3_s00ca_75e0 mVecD34;        // +0xd34
    cSPVector3_s00ca_75e0 mVecD40;        // +0xd40
    cSPVector3_s00ca_75e0 mVecD4C;        // +0xd4c
    cSPVector3_s00ca_75e0 mVecD58;        // +0xd58
    uint32_t mUd64;            // +0xd64
    float mFd68;               // +0xd68
    uint32_t mUd6c;            // +0xd6c
    uint32_t mUd70;            // +0xd70
    uint32_t mUd74;            // +0xd74
    uint32_t mUd78;            // +0xd78
    uint32_t mUd7c;            // +0xd7c
    uint32_t mUd80;            // +0xd80
    uint32_t mUd84;            // +0xd84
    uint32_t mUd88;            // +0xd88
    float mFd8c;               // +0xd8c
    float mFd90;               // +0xd90
    void* mPd94;               // +0xd94

    cVehicle_s00ca_75e0();
    ~cVehicle_s00ca_75e0();

    void FUN_00ca72a0();
    void FUN_00ca80e0(uint32_t v);
    void ContinueAngryCrowdAttack(bool force);  // 0x00ca8120 (cVehicle::ContinueAngryCrowdAttack)
    void EndAngryCrowdAttack();  // 0x00ca8180 (cVehicle::EndAngryCrowdAttack)
    void FUN_00ca81d0(cSPVector3_s00ca_75e0* a, float b, float c, int d);
    bool FUN_00ca8340(cCity_s00ca_75e0* city);
};  // namespace Simulator
}
static void buildListName(eWstring* name, int key)
{
    if (key == 0) {
        eWstring tmp;
        tmp.mpBegin = 0;
        tmp.mpEnd = 0;
        tmp.mpCapacity = 0;
        tmp.FUN_00579a90(0);
        name->FUN_0056e2d0(&tmp);
        if (tmp.mpBegin
            && (int)(((char*)tmp.mpCapacity - (char*)tmp.mpBegin) & ~1u) > 2)
            FUN_00f47380(tmp.mpBegin);
    } else {
        eWstring tmp;
        FUN_0093c5a0(&tmp, key, -1);
        name->FUN_0056e2d0(&tmp);
        if (tmp.mpBegin
            && (int)(((char*)tmp.mpCapacity - (char*)tmp.mpBegin) & ~1u) > 2)
            FUN_00f47380(tmp.mpBegin);
    }
}
static void freeName(eWstring* name)
{
    if (name->mpBegin
        && (int)(((char*)name->mpCapacity - (char*)name->mpBegin) & ~1u) > 2)
        FUN_00f47380(name->mpBegin);
}
using Simulator::cVehicle_s00ca_75e0;
// ---- items of slice s00ca75e0 end

// ---- items of slice s00ca8710 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char* kLocomotionString[];    // 0x0157d2b0
extern const char* kPurposeString[];       // 0x0157d2bc
extern const char* kCargoTypeString[];     // 0x0157d29c
extern unsigned char DAT_01654c10;
inline float Clamp(float value, float minValue, float maxValue)
{
    value = value > minValue ? value : minValue;
    value = value < maxValue ? value : maxValue;
    return value;
}
template <typename T> inline const T& Min(const T& a, const T& b) { return (b < a) ? b : a; }
template <typename T> inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }
struct Vector3_s00ca_8710 {
    float x, y, z;
    Vector3_s00ca_8710() {}
    Vector3_s00ca_8710(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3_s00ca_8710(const Vector3_s00ca_8710& v) : x(v.x), y(v.y), z(v.z) {}
    Vector3_s00ca_8710 Cross(const Vector3_s00ca_8710& b) const
    {
        return Vector3_s00ca_8710(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
    }
};
struct Matrix3 { float m[9]; };
Matrix3 MakeMatrixRows(const Vector3_s00ca_8710& a, const Vector3_s00ca_8710& b, const Vector3_s00ca_8710& c);   // 0x00afa0c0 (rows c, a, b)
Quaternion QuaternionFromMatrix(const Matrix3& m);                              // 0x0046d660
Quaternion NormalizedQuaternion(const Quaternion& q);                           // 0x00c64ad0
struct cPlanetModel_s00ca_8710 {
    uint8_t pad00[0xf0];
    bool mbF0;                                                                  // +0xf0
    Vector3_s00ca_8710 GetSurfaceNormal(const Vector3_s00ca_8710& pos);                               // 0x00b7e3b0
    Quaternion BuildSurfaceOrientation(const Vector3_s00ca_8710& pos, const Vector3_s00ca_8710& dir); // 0x00b7f250
};
cPlanetModel_s00ca_8710* PlanetModel_s00ca_8710();                                                    // 0x00b3d350
extern const Vector3_s00ca_8710 kZeroVector;      // 0x01699b08
extern const Vector3_s00ca_8710 kDefaultFacing;   // 0x0169a28c
struct Waypoint { uint32_t data[15]; };  // 0x3c bytes
struct LocoGoal {
    Waypoint* mpBegin;         // +0x00 queued path waypoints
    Waypoint* mpEnd;           // +0x04
    uint32_t pad08[3];
    Waypoint mCurrent;         // +0x14
    Vector3_s00ca_8710 mFacing;           // +0x50
    int mMode;                 // +0x5c
    Waypoint* erase(Waypoint* it);   // 0x00b47520 (vector::erase)
};
struct ILocomotion_s00ca_8710 {
    PV8 PV2 PV
    virtual const Vector3_s00ca_8710& GetPosition();            // +0x2c
    PV2 PV
    virtual void SetOrientation(const Quaternion& q); // +0x3c
    PV4 PV2 PV
    virtual Vector3_s00ca_8710 GetFacing();                     // +0x5c
    PV PV PV PV PV                                   // +0x60 .. +0x70
    virtual float v74(float arg);                    // +0x74
    PV8 PV8 PV2 PV2                                  // +0x78 .. +0xc4
    virtual float GetMaxSpeed();                     // +0xc8
    PV                                               // +0xcc
    virtual float GetMaxAcceleration();              // +0xd0
    PV PV PV                                         // +0xd4 .. +0xdc
    virtual void vE0(int a, float t);                // +0xe0
    PV2                                              // +0xe4 .. +0xe8
    virtual void OnPathFailed();                     // +0xec
    LocoGoal* GetGoal();                             // 0x00c41ec0
    bool Forward(int a, float b, float c);           // 0x00ca9770
};
struct cLocomotionOwner_s00ca_8710 {
    uint32_t pad00[0xd];
    ILocomotion_s00ca_8710 mLocomotion;                         // +0x34
    uint32_t pad38[0x9b];
    uint32_t mFlags;                                 // +0x2a4
    uint8_t pad2a8[0x84c];
    bool mbStopped;                                  // +0xaf4
    uint8_t padaf5[7];
    bool mbAFC;                                      // +0xafc
    int GetMoveType();                               // 0x00c9eaf0
    void ExecutePath();                              // 0x00ca72a0
    void GetOrbit(const Vector3_s00ca_8710* pos, float* radius, float* other); // 0x00c9ff40
};
void StartPathMode1(LocoGoal* goal);                 // 0x00c9f130
struct LocoUpdateParams {
    Vector3_s00ca_8710 mVelocity;         // +0x00 (out)
    float mUnk0c;
    float mDeltaTime;          // +0x10
};
struct cPathLocomotion_s00ca_8710 {
    uint32_t vtbl;
    bool mbRestart;                                  // +0x04
    uint8_t pad05[0xb];
    cLocomotionOwner_s00ca_8710* mpOwner;                       // +0x10
    int mMode;                                       // +0x14
    float mSpeed;                                    // +0x18
    bool mbWaiting;                                  // +0x1c
    uint8_t pad1d[3];
    uint32_t mPath[0xe];                             // +0x20
    float mSpeedOffSpan;                             // +0x58
    float mSpeedOnSpan;                              // +0x5c
    uint32_t pad60[8];
    float mSpanStart;                                // +0x80
    uint32_t pad84;
    float mSpanLength;                               // +0x88
    float mPathEnd;                                  // +0x8c
    uint32_t pad90[0x10];
    float mT;                                        // +0xd0

    void StartPathMode2(LocoGoal* goal);                                        // 0x00ca1c60
    void Evaluate(void* path, float t, Vector3_s00ca_8710* pos, Vector3_s00ca_8710* dir);             // 0x00ca1dc0
    bool NextSegment();                                                         // 0x00ca2370
    bool ShouldStop(float dt);                                                  // 0x00ca28a0
    bool WaitAtWaypoint(Waypoint* wp, float dt);                                // 0x00ca46c0
    void Steer(Vector3_s00ca_8710 dir, float dt, float speed, int accelSign);              // 0x00ca4f90
    void Turn(Vector3_s00ca_8710 dir, float dt);                                           // 0x00ca5b10

    void Update(LocoUpdateParams* params);
};
struct EastlString_s00ca_8710 {
    EastlString_s00ca_8710* append_sprintf(const char* format, ...);
};
struct cSPTimer {
    uint8_t pad00[0x20];
    uint64_t GetElapsedTime();   // 0x00bc3190
    bool IsRunning();            // 0x00feba90
};
struct IntQueue {
    uint8_t pad00[0x18];
    int* mpEnd;                  // +0x18
    int* mpCapacityBegin;        // +0x1c
    int* mpCapacityEnd;          // +0x20

    void Grow(int* value);       // 0x01045370

    void push_back(int value)
    {
        int* next = mpEnd + 1;
        if (next != mpCapacityEnd) {
            int* slot = mpEnd;
            mpEnd = next;
            if (slot)
                *slot = value;
        } else {
            Grow(&value);
        }
    }
};
struct cVehicle_s00ca_8710 {
    uint8_t pad00[0x34];
    ILocomotion_s00ca_8710 mLocomotion;                             // +0x34
    uint8_t pad38[0x238];
    uint8_t mFlags;                                      // +0x270
    uint8_t pad271[0xac4 - 0x271];
    int32_t mSubtype;                                    // +0xac4
    uint8_t padac8[0xae8 - 0xac8];
    int32_t mLocomotionType;                             // +0xae8
    int32_t mPurpose;                                    // +0xaec
    uint8_t padf0[0xaf4 - 0xaf0];
    int32_t mCargoType;                                  // +0xaf4
    uint8_t padf8[0xb1c - 0xaf8];
    int32_t mGameMode;                                   // +0xb1c
    uint8_t padb20[0xb24 - 0xb20];
    float mCargoAmount;                                  // +0xb24
    uint8_t padb28[0xb2c - 0xb28];
    IntQueue mPathQueue;                                 // +0xb2c
    uint8_t padb50[0xb58 - 0xb50];
    const int* mpHostilesBegin;                          // +0xb58
    const int* mpHostilesEnd;                            // +0xb5c
    uint8_t padb60[0xbcc - 0xb60];
    bool mbCrowdTimerArmed;                              // +0xbcc
    uint8_t padbcd[0xbd1 - 0xbcd];
    bool mbPathWaitTimerArmed;                           // +0xbd1
    uint8_t padbd2[0xbd8 - 0xbd2];
    cSPTimer mTimerBD8;                                  // +0xbd8
    cSPTimer mTimerBF8;                                  // +0xbf8
    uint8_t padc18[0xc1c - 0xc18];
    float mPower;                                        // +0xc1c
    float mDefense;                                      // +0xc20
    float mSpeedValue;                                   // +0xc24
    uint8_t padc28[0xc88 - 0xc28];
    cSPTimer mTimerC88;                                  // +0xc88

    void GetDebugToolTip(EastlString_s00ca_8710* out);              // 0x00ca95c0
    void UpdateCrowdTimers();                            // 0x00ca96b0
    void MoveWithFlag(int a, float b, float c);          // 0x00ca97a0
    void Move(int a, float b, float c, int flag);        // 0x00ca81d0
    void EndAngryCrowdAttack();                          // 0x00ca8180
};
const wchar_t* ConvertToString16(wchar_t* buffer, const char* text, int length);  // 0x0093c5a0
struct WideString {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    WideString(const wchar_t* text);
    ~WideString();
    bool empty() const { return mpBegin == mpEnd; }
    const wchar_t* c_str() const { return mpBegin; }
};
struct DebugItem { uint8_t mData[0x10]; };
struct DebugRange { DebugItem* mpBegin; DebugItem* mpEnd; };
struct DebugListOwner {
    virtual void BeginList(const wchar_t* name);   // slot 0
    virtual void EndList(const wchar_t* name);     // slot 1
};
bool CheckDebugListItem(DebugListOwner* owner, int index, DebugItem* item);  // 0x00ac8050
struct RefCounted {
    PV8 PV8 PV8
    virtual void AddRef();    // +0x60
    virtual void Release();   // +0x64
};
struct Vec4 {
    float x, y, z, w;
    bool Closer(RefCounted* a, RefCounted* b) const;   // 0x00c9f490
};
void SortClosestBegin(RefCounted** slot, RefCounted** begin, Vec4 p);   // 0x00ca77b0
void SortClosestEnd(RefCounted** slot, RefCounted** begin, Vec4 p);     // 0x00ca7830
void InsertClosest(RefCounted** slot, int a, int count, int b, RefCounted* item, Vec4 p); // 0x00ca44f0
// ---- items of slice s00ca8710 end

// ---- items of slice s00ca9820 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma warning(disable : 4100)
class cRefObj16 {
public:
    virtual void v000();                                 // +0x00
    virtual void v004();                                 // +0x04
    virtual void Release();                              // +0x08
};
struct tSlot16 {
    cRefObj16* mpObj;                                    // +0x00
    uint8_t    pad004[0x0c];                             // +0x04 .. +0x0f
};
class cRefObj24 {
public:
    virtual void v000();                                 // +0x00
    virtual void Release();                              // +0x04
};
struct tSlot24 {
    cRefObj24* mpObj;                                    // +0x00
    uint8_t    pad004[0x14];                             // +0x04 .. +0x17
};
extern tSlot16* __cdecl FUN_00ca0e80(tSlot16* pLast, tSlot16* pEnd, tSlot16* pFirst); // 0x00ca0e80
extern tSlot24* __cdecl FUN_00ca0da0(tSlot24* pLast, tSlot24* pEnd, tSlot24* pFirst); // 0x00ca0da0
class cSlotVector16 {
public:
    tSlot16* Erase(tSlot16* pFirst, tSlot16* pLast);

    tSlot16* mpBegin;                                    // +0x00
    tSlot16* mpEnd;                                      // +0x04
    tSlot16* mpCapacity;                                 // +0x08
};
class cSlotVector24 {
public:
    tSlot24* Erase(tSlot24* pFirst, tSlot24* pLast);

    tSlot24* mpBegin;                                    // +0x00
    tSlot24* mpEnd;                                      // +0x04
    tSlot24* mpCapacity;                                 // +0x08
};
// ---- items of slice s00ca9820 end

// ---- items of slice s00cacf40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char kGameModeA;                                         // 0x01654c10
extern char kTypeTribes;                                        // 0x018c6de8
extern char kTypeTribes2;                                       // 0x018c43e8
extern char kCreatureType;                                      // 0x013f94d4
extern "C" void* __cdecl memset(void*, int, size_t);
extern const float kNormalizeEps;                                   // 0x013ec4b8
extern const float kPathOne;                                        // 0x013eb8a0
extern const float kPathTwo;                                        // 0x013eeda0
extern const float kSpawnRadiusBias;                                // 0x013ec4d0
struct Vec3_s00ca_cf40 { float x, y, z; };
#define VSLOT(o, off) ((*(void***)(o))[(off) / 4])
static __forceinline Vec3_s00ca_cf40* PosOf(void* o) { return ((Vec3_s00ca_cf40*(__thiscall*)(void*))VSLOT(o, 0x2c))(o); }
static __forceinline void SpAddRef(void* o) { ((void(__thiscall*)(void*))VSLOT(o, 0xbc))(o); }
static __forceinline void SpRelease(void* o) { ((void(__thiscall*)(void*))VSLOT(o, 0xc0))(o); }
static __forceinline void* SpCast(void* o, uint32_t id) { return ((void*(__thiscall*)(void*, uint32_t))VSLOT(o, 0xb8))(o, id); }
static __forceinline void CrAddRef(void* o) { ((void(__thiscall*)(void*))VSLOT(o, 0x60))(o); }
static __forceinline void CrRelease(void* o) { ((void(__thiscall*)(void*))VSLOT(o, 0x64))(o); }
static __forceinline void TrAddRef(void* o) { ((void(__thiscall*)(void*))VSLOT(o, 0x0))(o); }
static __forceinline void TrRelease(void* o) { ((void(__thiscall*)(void*))VSLOT(o, 0x4))(o); }
static __forceinline float DistXYZ(const Vec3_s00ca_cf40* a, const Vec3_s00ca_cf40* b)
{
    float dx = b->x - a->x;
    float dy = b->y - a->y;
    float dz = b->z - a->z;
    return sqrtf((dx * dx + dy * dy) + dz * dz);
}
static __forceinline float DistZYX(const Vec3_s00ca_cf40* a, const Vec3_s00ca_cf40* b)
{
    float dx = b->x - a->x;
    float dy = b->y - a->y;
    float dz = b->z - a->z;
    return sqrtf((dz * dz + dy * dy) + dx * dx);
}
struct SpList {                     // eastl::vector<AutoRefCount<spatial>> (4-byte elements)
    void** mBegin; void** mEnd; void** mCap;
    void DoInsertValue(void** pos, void** const& v);        // 0x00bab900
};
struct CrList {                     // eastl::vector<AutoRefCount<creature>>
    void** mBegin; void** mEnd; void** mCap;
    void DoInsertValue(void** pos, void** const& v);        // 0x00ae6ed0
};
void** __cdecl CopyPtrRange(void** first, void** last, void** dest);       // 0x00ae6880
static __forceinline void AddUnique(SpList* v, void* p)
{
    void** it = v->mBegin;
    void** end = v->mEnd;
    if (it != end) {
        do {
            if (*it == p) break;
            ++it;
        } while (it != end);
        if (it != end) return;
    }
    void* tmp = p;
    if (tmp) SpAddRef(tmp);
    if (v->mEnd < v->mCap) {
        void** slot = v->mEnd++;
        if (slot) {
            *slot = p;
            if (p) SpAddRef(p);
        }
    } else {
        v->DoInsertValue(v->mEnd, &tmp);
    }
    if (tmp) SpRelease(tmp);
}
struct PtrRange { void** mBegin; void** mEnd; };
struct GameDataVec { int pad0; PtrRange vec; };
typedef void (__cdecl *GameDataFn)();
struct NounMgr {
    GameDataVec* GetGameDataVector(GameDataFn a, GameDataFn b, GameDataFn c, GameDataFn d, void* type);  // 0x00b21340
};
NounMgr* NounManager_s00ca_cf40();                                         // 0x00b3d300
void __cdecl fnA();     // 0x00cd7d10
void __cdecl fnB();     // 0x00d3d420
void __cdecl fnC();     // 0x00ae72d0
void __cdecl fnD();     // 0x00b1e500
void __cdecl fnE();     // 0x00acdff0
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);
struct SimList { void** mBegin; void** mEnd; };
struct SimSingleton {
    char data[0x58];
    SimSingleton();                                             // 0x00dc7d70
    SimList* GetObjects();                                      // 0x00ad2800
};
extern SimSingleton* gSimSingleton;                             // 0x01699ab8
struct CivStrategy;
CivStrategy* GetCivStrategy();                                  // 0x00cf74c0
struct MemberVec { void** mBegin; void** mEnd; };
struct OwnerInfo { char pad[0x14]; float v14; };
struct Gauge {
virtual void g0();
virtual void g1();
virtual void g2();
virtual void g3();
    virtual int GetOwnerId();                                   // +0x10
    float GetBaseRange();                                       // 0x00bfc400
};
struct TribeInfo { char pad[0x25c]; float radius; };
struct Tribe {
    char pad[0x120];
    char spatial[1];                                            // +0x120 (position provider subobject)
    char pad2[0x354 - 0x121];
    void** mAgentsBegin;                                        // +0x354
    void** mAgentsEnd;                                          // +0x358
    MemberVec* GetMembers();                                    // 0x00c8e810
    void Attach(Gauge* g);                                      // 0x00be2390
    void Detach(Gauge* g);                                      // 0x00be2420
};
struct Tracker {
    void Update();                                              // 0x00c7dcb0
};
struct RelMgr {
    int Relation(int a, int b, int c);                          // 0x00d00a70
};
RelMgr* RelationshipManager();                                  // 0x00b3d2c0
struct CrHelper {
    bool Test();                                                // 0x00c0c0e0
};
struct Real {
    virtual void r0();
    char pad04[0x4c - 4];
    void FinalStep();                                           // 0x00cabe70
};
static __forceinline void PushCreature(CrList* v, void* c)
{
    void* tmp = c;
    CrAddRef(c);
    if (v->mEnd < v->mCap) {
        void** slot = v->mEnd++;
        if (slot) {
            *slot = c;
            CrAddRef(c);
        }
    } else {
        v->DoInsertValue(v->mEnd, &tmp);
    }
    if (tmp) CrRelease(tmp);
}
static __forceinline void* CastOrNull(void** slot, uint32_t id)
{
    void* o = *slot;
    return o ? SpCast(o, id) : 0;
}
struct Agent34 {
    virtual void a0();
    char pad04[0x26c - 4];
    float mSenseRange;                                          // +0x26c
    char pad270[8];
    SpList mNear;                                               // +0x278
    char pad284[0x4d4 - 0x284];
    Gauge mGauge;                                               // +0x4d4
    char pad4d8[0x61c - 0x4d8];
    Tracker mTracker;                                           // +0x61c
    char pad61d[0xab4 - 0x61d];
    float mOwnerValue;                                          // +0xab4
    char pad_ab8[0xb28 - 0xab8];
    Tribe* mNearest;                                            // +0xb28
    char padb2c[0xb58 - 0xb2c];
    CrList mCreatures;                                          // +0xb58

    void BaseUpdate();                                          // 0x00c42350
    Real* R() { return (Real*)((char*)this - 0x34); }
    void Update();
};
struct IRef2 {
    virtual void AddRef();
    virtual void Release();                                         // +4
};
struct SimSlot {
    void ResetSerializer();                                         // 0x00c2e4e0
    uint8_t pad00[0x100];                                           // sizeof == 0x100
};
struct SimPanel {
    SimSlot mSlotArray[8];                                          // +0x000
    IRef2*  mRefArray[8];                                           // +0x800
    void Shutdown();
};
struct NormCtx {
    float GetScale(const Vec3_s00ca_cf40& v);                                  // 0x00c9ffd0
};
struct SimTarget {
virtual void V00();
virtual void V01();
virtual void V02();
virtual void V03();
virtual void V04();
virtual void V05();
virtual void V06();
virtual void V07();
virtual void V08();
virtual void V09();
virtual void V10();
virtual void V11();
virtual void V12();
virtual void V13();
virtual void V14();
virtual void V15();
virtual void V16();
virtual void V17();
virtual void V18();
virtual void V19();
virtual void V20();
virtual void V21();
virtual void V22();
virtual void V23();
    virtual void AddRef();                                          // +0x60
    virtual void Release();                                         // +0x64
};
struct SimTargetVec {                   // eastl::vector<AutoRefCount<SimTarget>>
    SimTarget** mpBegin;                                            // +0x684
    SimTarget** mpEnd;                                              // +0x688
    SimTarget** mpEndOfStorage;                                     // +0x68c
    void PushBack(SimTarget* const& value);
    void Grow(SimTarget** pEnd, SimTarget* const& value);           // 0x00ae6ed0
};
void SimTargetVec::PushBack(SimTarget* const& value)
{
    SimTarget** pEnd = mpEnd;
    if (pEnd >= mpEndOfStorage) {
        Grow(pEnd, value);
        return;
    }
    mpEnd = pEnd + 1;
    if (!pEnd)
        return;
    *pEnd = value;
    if (value)
        value->AddRef();
}
struct SimObject {
    uint8_t pad00[0x684];
    SimTargetVec mTargets;                                          // +0x684
    void AddTarget(SimTarget* target);
};
struct SimSub {
virtual void V00();
virtual void V01();
virtual void V02();
virtual void V03();
virtual void V04();
virtual void V05();
virtual void V06();
virtual void V07();
virtual void V08();
virtual void V09();
virtual void V10();
    virtual Vec3_s00ca_cf40* GetPos();                                         // +0x2c
virtual void V12();
virtual void V13();
virtual void V14();
virtual void V15();
virtual void V16();
virtual void V17();
virtual void V18();
virtual void V19();
virtual void V20();
virtual void V21();
virtual void V22();
virtual void V23();
virtual void V24();
virtual void V25();
virtual void V26();
virtual void V27();
    virtual void V28();
    virtual float GetPathScale();                                   // +0x74
virtual void V30();
virtual void V31();
virtual void V32();
virtual void V33();
virtual void V34();
virtual void V35();
virtual void V36();
virtual void V37();
virtual void V38();
virtual void V39();
virtual void V40();
virtual void V41();
virtual void V42();
virtual void V43();
virtual void V44();
virtual void V45();
virtual void V46();
virtual void V47();
virtual void V48();
virtual void V49();
virtual void V50();
virtual void V51();
virtual void V52();
virtual void V53();
virtual void V54();
virtual void V55();
virtual void V56();
    virtual void SetDestination(const Vec3_s00ca_cf40& v, float radius);       // +0xe4
    void* CreateSpawn();                                            // 0x00c41ec0
};
struct SimObjA : NormCtx {
    uint8_t pad00[0x34];
    SimSub  mSub;                                                   // +0x34
    uint8_t pad38[0x2a4 - 0x38];
    uint32_t mFlags;                                                // +0x2a4
};
struct SimObjB {
    uint8_t pad00[0x14];
    Vec3_s00ca_cf40    mDir;                                                   // +0x14
    uint8_t pad20[0x50 - 0x20];
    Vec3_s00ca_cf40    mVel;                                                   // +0x50
    int32_t mMode;                                                  // +0x5c
    uint8_t pad60[0x68 - 0x60];
    float   mTimer;                                                 // +0x68
    float   mTimer2;                                                // +0x6c
};
struct SimStepProvider {
    uint8_t pad00[0x10];
    float mStep;                                                    // +0x10
};
Vec3_s00ca_cf40 normalized_safe(const Vec3_s00ca_cf40& v);                                // 0x00449c20
struct SimSpawnOut {
    Vec3_s00ca_cf40    mPos;                                                   // +0x00
    uint8_t pad0c[0x50 - 0x0c];
    Vec3_s00ca_cf40    mVel;                                                   // +0x50
    int32_t mKind;                                                  // +0x5c
    float   mScale;                                                 // +0x60
};
struct SimSpawnSrc {
    void**  mpBegin;                                                // +0x00
    void**  mpEnd;                                                  // +0x04
    uint8_t pad08[0x14 - 0x08];
    Vec3_s00ca_cf40    mVec;                                                   // +0x14
    float   mRadiusIn;                                              // +0x20
    uint8_t pad24[0x50 - 0x24];
    Vec3_s00ca_cf40    mVel;                                                   // +0x50
    int32_t mKind;                                                  // +0x5c
    float   mScale;                                                 // +0x60
};
// ---- items of slice s00cacf40 end

// ---- items of slice s00caded0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3_s00ca_ded0 {
    float x, y, z;
    Vector3_s00ca_ded0() {}
    Vector3_s00ca_ded0(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3_s00ca_ded0(const Vector3_s00ca_ded0& v) : x(v.x), y(v.y), z(v.z) {}
    float Dot(const Vector3_s00ca_ded0& b) const { return x * b.x + y * b.y + z * b.z; }
    float Length() const { return sqrtf(x * x + y * y + z * z); }
    Vector3_s00ca_ded0 Cross(const Vector3_s00ca_ded0& b) const
    {
        return Vector3_s00ca_ded0(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
    }
    Vector3_s00ca_ded0 Normalized() const
    {
        float inv = 1.0f / sqrtf(x * x + y * y + z * z + 1e-8f);
        return Vector3_s00ca_ded0(x * inv, y * inv, z * inv);
    }
};
inline Vector3_s00ca_ded0 operator*(const Vector3_s00ca_ded0& a, float s) { return Vector3_s00ca_ded0(a.x * s, a.y * s, a.z * s); }
extern Vector3_s00ca_ded0 kZeroVector_s00ca_ded0;         // 0x0169A37C (0, 0, 0)
struct cLocomotiveObject {
    uint32_t pad00[0x34 / 4];
};
struct cCreatureFlyer {
    uint32_t pad00[0x34 / 4];
    cLocomotiveObject mLocomotion;                    // +0x34
    float GetGroundRadius(const Vector3_s00ca_ded0& pos);                                  // 0x00C9FFD0
};
bool SweepTest(cLocomotiveObject* pObject, const Vector3_s00ca_ded0& from, const Vector3_s00ca_ded0& to,
               Vector3_s00ca_ded0* pHit, int flags);                                       // 0x00B53BC0
namespace Simulator {
class cFlyLocoPrimaryBase {
public:
    cFlyLocoPrimaryBase() {}
    virtual ~cFlyLocoPrimaryBase();
    int mUnk04;                                    // +0x04  (left uninitialised by the ctor)
};
}
namespace Simulator {
class RefCountVTemplateInt {                       // EA::RefCountVTemplate<int>
public:
    RefCountVTemplateInt() : mRefCount(0) {}
    virtual ~RefCountVTemplateInt();
    int mRefCount;                                 // +0x0c
};
}
namespace Simulator {
class cFlyingLocomotion_s00ca_ded0 : public cFlyLocoPrimaryBase, public RefCountVTemplateInt {
public:
    float   mUnk10;        // +0x10
    Vector3_s00ca_ded0 mUnk14;        // +0x14
    Vector3_s00ca_ded0 mUnk20;        // +0x20
    float   mUnk2c;        // +0x2c  (left uninitialised by the ctor)
    int     mUnk30;        // +0x30
    bool    mbAligned;     // +0x34
    float   mLift;         // +0x38

    cFlyingLocomotion_s00ca_ded0();
    virtual void Update();
};
}
// ---- items of slice s00caded0 end

// ---- items of slice s00cb02f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float kFlyAlignThreshold;            // 0x0157D33C (0.97)
extern float kFlyLiftRate;                  // 0x0157D338 (2.0)
extern float kPI;                           // 0x0157D2E8
extern float kTwoPI;                        // 0x0169A3F8
#pragma pack(push, 4)
struct Vector3_s00cb_02f0 {
    float x, y, z;
    Vector3_s00cb_02f0() {}
    Vector3_s00cb_02f0(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3_s00cb_02f0(const Vector3_s00cb_02f0& v) : x(v.x), y(v.y), z(v.z) {}
    float Length() const { return sqrtf(x * x + y * y + z * z); }
    float Dot(const Vector3_s00cb_02f0& b) const { return x * b.x + y * b.y + z * b.z; }
    Vector3_s00cb_02f0 Cross(const Vector3_s00cb_02f0& b) const
    {
        return Vector3_s00cb_02f0(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
    }
    Vector3_s00cb_02f0 Normalized() const
    {
        float inv = 1.0f / sqrtf(x * x + y * y + z * z + 1e-8f);
        return Vector3_s00cb_02f0(x * inv, y * inv, z * inv);
    }
    bool operator==(const Vector3_s00cb_02f0& b) const { return x == b.x && y == b.y && z == b.z; }
};
inline Vector3_s00cb_02f0 operator+(const Vector3_s00cb_02f0& a, const Vector3_s00cb_02f0& b) { return Vector3_s00cb_02f0(a.x + b.x, a.y + b.y, a.z + b.z); }
inline Vector3_s00cb_02f0 operator-(const Vector3_s00cb_02f0& a, const Vector3_s00cb_02f0& b) { return Vector3_s00cb_02f0(a.x - b.x, a.y - b.y, a.z - b.z); }
inline Vector3_s00cb_02f0 operator*(const Vector3_s00cb_02f0& a, float s) { return Vector3_s00cb_02f0(a.x * s, a.y * s, a.z * s); }
inline Vector3_s00cb_02f0 operator-(const Vector3_s00cb_02f0& a) { return Vector3_s00cb_02f0(-a.x, -a.y, -a.z); }
extern Vector3_s00cb_02f0 kZeroVector_s00cb_02f0;                 // 0x0169A37C
Vector3_s00cb_02f0 normalized_safe(const Vector3_s00cb_02f0& v);                                  // 0x00449C20
float SignedAngle(const Vector3_s00cb_02f0& from, const Vector3_s00cb_02f0& to, const Vector3_s00cb_02f0& axis); // 0x006994A0
struct cPlanetModel_s00cb_02f0 {
    Vector3_s00cb_02f0 IntersectRay(const Vector3_s00cb_02f0& origin, const Vector3_s00cb_02f0& dir);         // 0x00B82110
};
cPlanetModel_s00cb_02f0* PlanetModel_s00cb_02f0();                                                // 0x00B3D350
struct LocoWaypoint {
    Vector3_s00cb_02f0 mPosition;              // +0x00
    float mGoalStopDistance;        // +0x0C
    uint32_t pad10[11];
};
struct cLocomotionRequest {
    LocoWaypoint* mpBegin;          // +0x00
    LocoWaypoint* mpEnd;            // +0x04
    uint32_t pad08[3];
    LocoWaypoint mGoal;             // +0x14
    uint32_t pad50[3];
    int mMode;                      // +0x5C
    float mAcceptableStopDistance;  // +0x60
    float field_64;                 // +0x64
    float mLastDistance;            // +0x68
    float mStallTime;               // +0x6C
    void erase(LocoWaypoint* it);                                           // 0x00B47520
};
struct cCreatureFlyer_s00cb_02f0;
struct cLocomotiveObject_s00cb_02f0 {
    PV8 PV2 PV
    virtual const Vector3_s00cb_02f0* GetPosition();            // +0x2c
    PV8 PV2 PV
    virtual Vector3_s00cb_02f0 GetFacing();                     // +0x5c
    PV4 PV
    virtual float GetHoverHeight();                  // +0x74
    PV8 PV8
    virtual cCreatureFlyer_s00cb_02f0* Cast(uint32_t type);     // +0xb8
    PV8 PV4
    virtual void StopMovement();                     // +0xec
    cLocomotionRequest* GetRequest();                                       // 0x00C41EC0
    const Vector3_s00cb_02f0* GetVelocity();                                           // 0x00D20610
};
struct cCreatureFlyer_s00cb_02f0 {
    uint32_t pad00[0x34 / 4];
    cLocomotiveObject_s00cb_02f0 mLocomotion;                   // +0x34
    uint32_t pad38[(0x21C - 0x38) / 4];
    float mTurnRate;                                 // +0x21C
    float GetMaxSpeed();                                                    // 0x00C9F380
    float GetGroundRadius(const Vector3_s00cb_02f0& pos);                              // 0x00C9FFD0
};
Vector3_s00cb_02f0 ProjectToFlightSurface(const Vector3_s00cb_02f0& pos, cCreatureFlyer_s00cb_02f0* pFlyer);         // 0x00CAE0E0
Vector3_s00cb_02f0 AvoidSurface(const Vector3_s00cb_02f0& pos, cCreatureFlyer_s00cb_02f0* pFlyer);                   // 0x00CADB90
Vector3_s00cb_02f0 TurnTowards(const Vector3_s00cb_02f0& from, const Vector3_s00cb_02f0& to, float turnRate, float dt); // 0x00CADF50
bool SweepTest(cLocomotiveObject_s00cb_02f0* pObject, const Vector3_s00cb_02f0& from, const Vector3_s00cb_02f0& to, Vector3_s00cb_02f0* pHit, int flags); // 0x00B53BC0
struct LocoSteerParams {
    Vector3_s00cb_02f0 mVelocity;              // +0x00 (out)
    float mUnk0c;
    float mDeltaTime;               // +0x10
    cLocomotiveObject_s00cb_02f0* mpObject;    // +0x14
};
struct cFlyingLocomotion_s00cb_02f0 {
    void* vtable;
    bool mbReset;                   // +0x04
    uint8_t pad05[0x34 - 5];
    bool mbAligned;                 // +0x34
    float mLift;                    // +0x38

    void FlyTo(cCreatureFlyer_s00cb_02f0* pFlyer, const Vector3_s00cb_02f0& target, LocoSteerParams* params); // 0x00CAFE90
    void ApplyFacing(cCreatureFlyer_s00cb_02f0* pFlyer, const Vector3_s00cb_02f0& dir, float dt);             // 0x00CAF650
    void Update(LocoSteerParams* params);
};
// ---- items of slice s00cb02f0 end

// ---- items of slice s00cb1110 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(_ReadWriteBarrier)
void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
#define EASTL_ALLOCATOR_FILE \
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
struct TraceCache
{
    char mBytes[0x820];          // 8 * 0x100 hit records followed by 8 cached object pointers
};
struct Value                       // the hashtable value (0x824 bytes)
{
    unsigned   mKey;               // +0x000
    TraceCache mTrace;             // +0x004 .. +0x823

    Value(const Value& src);       // 0x00cb02a0
};
struct Node
{
    Value mValue;                  // +0x000 .. +0x823
    Node* mpNext;                  // +0x824
};
struct Iter                        // eastl hash iterator (8 bytes)
{
    Node*  mpNode;                 // +0x00
    Node** mpBucket;               // +0x04
};
struct InsertResult                // eastl insert() result (12 bytes)
{
    Node*  mpNode;                 // +0x00
    Node** mpBucket;               // +0x04
    bool   mInserted;              // +0x08
};
struct RehashResult                // prime_rehash_policy::RehashResult (8 bytes)
{
    bool     first;                // +0x00
    unsigned second;               // +0x04
};
struct RehashPolicy
{
    float    mfMaxLoadFactor;      // +0x00
    float    mfGrowthFactor;       // +0x04
    unsigned mnNextResize;         // +0x08

    // 0x00921440
    RehashResult GetRehashRequired(unsigned nBucketCount, unsigned nElementCount, unsigned nElementAdd);
};
struct Ht                          // global instance at 0x0157d30c
{
    void*        mField00;         // +0x00 (hash functor)
    Node**       mpBuckets;        // +0x04
    unsigned     mBucketCount;     // +0x08
    unsigned     mSize;            // +0x0c
    RehashPolicy mRehashPolicy;    // +0x10

    void Find(Iter* out, const unsigned* key);                            // 0x00cb00d0
    TraceCache* FindOrInsert(const unsigned* key);                        // 0x00c2b080
    void DoRehash(unsigned newBucketCount);                               // 0x00c29710

    Node* DoFindNode(Node* pNode, unsigned key)
    {
        for (; pNode; pNode = pNode->mpNext) {
            if (key == pNode->mValue.mKey)
                return pNode;
        }
        return 0;
    }

    Node* DoAllocateNode(const Value& value)
    {
        Node* const pNode = (Node*)operator new[](sizeof(Node), "Simulator", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1);
        if (pNode)
            ::new (&pNode->mValue) Value(value);
        pNode->mpNext = 0;
        return pNode;
    }

    InsertResult DoInsertValue(const Value& value, bool trueType);        // 0x00cb1110
};
void __cdecl FUN_00cadb50(TraceCache* cache);
// ---- items of slice s00cb1110 end

// ---- items of slice s00cb2f70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_157d340;
extern float g_169a37c;
extern float g_169a380;
extern float g_169a384;
extern float g_147510c;
struct VObj { void** vt; };
typedef void*  (__thiscall *FnVp1i)(void*, int);
typedef float* (__thiscall *FnVp0p)(void*);
typedef void   (__thiscall *FnVp1v)(void*, void*);
struct PathSlot;
struct LocoSub34 {
    void** vt;                              // +0x00
    PathSlot* __thiscall FUN_00c41ec0();    // 0x00c41ec0
};
struct RawLoco {
    void** vt;                              // +0x00
    char   pad04[0x1a0 - 0x04];
    float  mf1a0;                           // +0x1a0
    PathSlot* __thiscall FUN_00c41ec0();    // 0x00c41ec0
    bool   __thiscall IsNearGoal();         // 0x00c42e20
    unsigned char __thiscall FUN_00c41ed0(float a, float b); // 0x00c41ed0
};
struct SimWorld {
    char       pad00[0x34];
    LocoSub34  mSub;                        // +0x34
    char       pad38[0x21c - 0x38];
    float      mf21c;                       // +0x21c
    char       pad220[0x2a4 - 0x220];
    uint32_t   mFlags2a4;                   // +0x2a4
    char       pad2a8[0xb1c - 0x2a8];
    int        mB1c;                        // +0xb1c
    char       padB20[0xbcd - 0xb20];
    char       mbcd;                        // +0xbcd
    float __thiscall FUN_00c9ffd0(float* p); // 0x00c9ffd0
    float __thiscall FUN_00c9f380();        // 0x00c9f380
};
struct PathSlot {
    int   mBegin;                       // +0x00
    int   mEnd;                         // +0x04
    float mf08;                         // +0x08
    char  pad0c[0x14 - 0x0c];
    float mPos[3];                      // +0x14
    float mf20;                         // +0x20
    char  pad24[0x4c - 0x24];
    unsigned char mFlag4c;              // +0x4c
    char  pad4d[0x5c - 0x4d];
    int   mCount5c;                     // +0x5c
    char  pad60[0x68 - 0x60];
    float mf68;                         // +0x68
    float mf6c;                         // +0x6c
};
struct NavObj { char pad00[0x14]; RawLoco* mp14; };
struct LocoRequestLocal {
    void* mData;                            // +0x00
    void* __thiscall ctor();                // 0x00ac9850
};
struct LocoRequest {
    int   m00;                          // +0x00
    int   m04;                          // +0x04
    int   m08;                          // +0x08
    char  pad0c[0x14 - 0x0c];
    float mPos[3];                      // +0x14
    float mf20;                         // +0x20
    char  pad24[0x28 - 0x24];
    int   m28;                          // +0x28
    char  pad2c[0x50 - 0x2c];
    unsigned char m50;                  // +0x50
    char  pad51[0x54 - 0x51];
    float mf54;                         // +0x54
    float mf58;                         // +0x58
    float mf5c;                         // +0x5c
    int   m60;                          // +0x60
    float mf64;                         // +0x64
    char  pad68[0x6c - 0x68];
    float mf6c;                         // +0x6c
    float mf70;                         // +0x70
    int   m74;                          // +0x74
};
union FloatBytes4 { float f; unsigned char bytes[4]; };
PathSlot*  __cdecl FUN_00cb1210(SimWorld* world);                                  // 0x00cb1210
void       __cdecl FUN_00cadb50(void* u);                                          // 0x00cadb50
bool       __cdecl FUN_00cadc20(NavObj* obj, SimWorld* w, float* pos, PathSlot* p); // 0x00cadc20
void       __cdecl FUN_00cadd50(NavObj* obj, SimWorld* w, PathSlot* p, float f, float d); // 0x00cadd50
bool       __cdecl FUN_00cb2480(SimWorld* w, PathSlot* p, float* a, float* b, void** c);  // 0x00cb2480
uint32_t   __cdecl FUN_00cb2770(SimWorld* w, float* a, PathSlot* p, float* b, float* c,
                                float* d, void** e);                               // 0x00cb2770
void       __cdecl FUN_00b47520(void* p);                                          // 0x00b47520
void       __cdecl operator_delete_array(void* p);                                 // 0x00f47380
char* __cdecl PlanetModel_s00cb_2f70();                              // 0x00b3d350
void  __cdecl FUN_00cae280(NavObj* obj);                  // 0x00cae280
struct Sim34d0 {
    char pad00[4];
    char mb4;                                             // +0x04
    void __thiscall FUN_00cb34d0(NavObj* obj);
};
// ---- items of slice s00cb2f70 end

// ---- items of slice s01351ae0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void U_01352460_0_34();   // 0x00b1fbf0
extern void U_01352460_0_38();   // 0x00b1fbf0
struct PropDesc {
    const char* mName;   // +0x00
    u32 mHash;   // +0x04
    u32 mType;   // +0x08
    u32 mPad0C;   // +0x0c
    u32 mPad10;   // +0x10
    u32 mPad14;   // +0x14
    u32 mZero18;   // +0x18
    u32 mZero1C;   // +0x1c
    void* mDefault;   // +0x20
    void* mFn24;   // +0x24
    void* mFn28;   // +0x28
    void* mFn2C;   // +0x2c
    void* mFn30;   // +0x30
    void* mFn34;   // +0x34
    void* mFn38;   // +0x38
};
// ---- items of slice s01351ae0 end

// ---- items of slice s01354df0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct SimAttr {
    const char* mName;      // +0x00  attribute name
    const char* mDesc;      // +0x04  name token / hash
    int         mIndex;     // +0x08  table index
    int         mPad0;      // +0x0c  never assigned here
    int         mPad1;      // +0x10  never assigned here
    int         mPad2;      // +0x14  never assigned here
    int         mZero0;     // +0x18  zero
    int         mZero1;     // +0x1c  zero
    void*       mDefault;   // +0x20  Simulator::Attribute::DefaultOffset
    void*       mFn0;       // +0x24
    void*       mFn1;       // +0x28
    void*       mFn2;       // +0x2c
    void*       mFn3;       // +0x30
    void*       mFn4;       // +0x34
    void*       mFn5;       // +0x38
};
#define ATTRS  ((SimAttr*)0x0157b7d0)
// ---- items of slice s01354df0 end

// ---- items of slice s01355f90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void E607_1_24();   // 0x00aca060
extern void E607_1_28();   // 0x00bca960
extern void E607_1_2C();   // 0x00c2e4e0
extern void E607_1_30();   // 0x00692fb0
extern void E607_1_34();   // 0x00b6f550
extern void E607_1_38();   // 0x00ac8050
extern void E607_2_24();   // 0x00572810
extern void E607_2_28();   // 0x00572840
extern void E607_2_2C();   // 0x00692ff0
extern void E607_2_30();   // 0x00694ee0
extern void E607_2_34();   // 0x00b1fbf0
extern void E607_2_38();   // 0x0057cde0
extern void E607_3_24();   // 0x00b6e3a0
extern void E607_3_28();   // 0x00ac88c0
extern void E607_3_2C();   // 0x006930f0
extern void E607_3_30();   // 0x00695010
extern void E607_3_34();   // 0x00b1fbf0
extern void E607_3_38();   // 0x00acbba0
extern void E607_4_24();   // 0x00572810
extern void E607_4_28();   // 0x00572840
extern void E607_4_2C();   // 0x00693090
extern void E607_4_30();   // 0x00694f00
extern void E607_4_34();   // 0x00b1fbf0
extern void E607_4_38();   // 0x00675ca0
extern void E611_24();     // 0x00bceb00
extern void E611_28();     // 0x00bd1780
extern void E611_2C();     // 0x00c2e4e0
extern void E611_30();     // 0x00692fb0
extern void E611_34();     // 0x00c87090
extern void E611_38();     // 0x00ac8050
extern "C" int   __cdecl lib_atexit(void (__cdecl*)());   // 0x011e07ef
typedef int            s32;
typedef float          f32;
struct EntryB8 {
    u32 m00;          // +0x00
    u32 m04;          // +0x04
    u32 m08;          // +0x08
    u8  m0C[0x40];    // +0x0c
    u32 m4C;          // +0x4c
    u32 m50;          // +0x50
    u8  m54[0x38];    // +0x54
    u32 m8C;          // +0x8c
    f32 m90;          // +0x90
    f32 m94;          // +0x94
    u8  m98[0x08];    // +0x98
    u32 mA0;          // +0xa0
    u32 mA4;          // +0xa4
    u32 mA8;          // +0xa8
    u8  mAC[0x08];    // +0xac
    u32 mB4;          // +0xb4
};
// ---- items of slice s01355f90 end

// ---- items of slice s00ca4320 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cObjectInstanceInventoryItem;
struct cInventory
{
virtual void vpad0();
virtual void vpad1();
virtual void vpad2();
virtual void vpad3();
virtual void vpad4();
virtual void vpad5();
virtual void vpad6();
virtual void vpad7();
virtual void vpad8();
virtual void vpad9();
virtual void vpad10();
virtual void vpad11();
virtual void vpad12();
virtual void vpad13();
virtual void vpad14();
virtual void vpad15();
virtual void vpad16();
virtual void vpad17();
virtual void vpad18();
virtual void vpad19();
virtual void vpad20();
virtual void vpad21();
virtual void vpad22();
virtual void vpad23();
virtual void vpad24();
virtual void vpad25();
virtual void vpad26();
virtual void vpad27();
virtual void vpad28();
virtual void vpad29();
virtual void vpad30();
virtual void vpad31();
    virtual void AddItem(cObjectInstanceInventoryItem* item, int a, int b);   // +0x80
};
struct cObjectInstanceInventoryItem
{
    virtual void vpad0();                              // +0x00
    virtual void AddRef();                             // +0x04
    virtual void Func8();                              // +0x08
    cObjectInstanceInventoryItem* Construct();         // 0x00c6f3d0
    void SetOwner(void* owner);                        // 0x00c6f5e0
};
struct Stimuli
{
    void ClearAll(int mask, int flags);                // 0x00bc98f0
};
struct GameGlobalAt78
{
    void Func(void* owner, void* param);               // 0x00f1aff0
};
struct GameGlobal
{
    uint8_t m_pad0[0x78];                              // +0x00
    GameGlobalAt78* m_at78;                            // +0x78
};
extern GameGlobal* gpGameGlobal;                       // 0x016c7aa4
void* __cdecl operator_new(uint32_t size, const char* name,
                           int a, int b, int c, int d);   // 0x00f473a0
int GetCurrentGameMode_s00ca_4320();                              // 0x00b5b800
struct cVehicle_s00ca4320
{
    uint8_t m_pad0[0xaf0];                             // +0x0000
    void* mpAF0;                                       // +0x0af0
    uint8_t m_padAf4[0xd94 - 0xaf4];                   // +0x0af4
    cInventory* mpInventoryD94;                        // +0x0d94

    void ProcessEA();                                  // 0x00ca04a0
    bool FUN_00ca4320(void* param);
};
// ---- items of slice s00ca4320 end

// ---- items of slice s00ca4600 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV8_s00ca_4600 PV PV PV PV PV PV PV PV
struct RefCounted_s00ca_4600 {
    PV8_s00ca_4600 PV8_s00ca_4600 PV8_s00ca_4600
    virtual void AddRef();    // +0x60
    virtual void Release();   // +0x64
};
struct Vec4_s00ca_4600 {
    float x, y, z, w;
    Vec4_s00ca_4600(const Vec4_s00ca_4600& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
};
struct RefHolder {
    RefCounted_s00ca_4600* p;
    RefHolder(RefCounted_s00ca_4600* q) : p(q) { if (p) p->AddRef(); }
    RefHolder(const RefHolder& o) : p(o.p) {}
    ~RefHolder() { if (p) p->Release(); }
};
void InsertClosest(RefCounted_s00ca_4600** slot, int a, int count, int b, RefHolder item, Vec4_s00ca_4600 p); // 0x00ca44f0
// ---- items of slice s00ca4600 end

// @ 0x00c9e5d0
void TryCivModeTutorial()
{
    if (!ConfigManager()->Slot30((uint32_t)((const uint8_t*)0x04ea96cb)))
        return;
    cCivModeStrategy* pStrategy = CivModeStrategyGet();
    if (pStrategy->HasCivTutorialOccurred((uint32_t)((const uint8_t*)0x064e6678)))
        pStrategy->DoNext((uint32_t)((const uint8_t*)0x064e6679), 1);
}

// @ 0x00c9e610
cVehicle* cVehicle::Find(uint32_t id)
{
    if (id != (uint32_t)&gNullObjectKey) {
        cVehicle* pFound;
        if ((pFound = (cVehicle*)mLoco.Find(id)) != 0)
            return pFound;
        if ((pFound = (cVehicle*)BaseFind(id)) != 0)
            return pFound;
        if ((pFound = (cVehicle*)mCombatant.Find(id)) != 0)
            return pFound;
        if ((pFound = (cVehicle*)mChild650.Find(id)) != 0)
            return pFound;
        if ((pFound = (cVehicle*)mChild638.Find(id)) != 0)
            return pFound;
        return (cVehicle*)mChild5d0.Find(id);
    }
    return this;
}

// @ 0x00c9e690
bool cLoco::IsLocalPlayer()
{
    const uint8_t* pMode = (const uint8_t*)GetCurrentGameMode();
    if (pMode == &gModeTen)
        return false;
    int empire = NounManager()->GetPlayerEmpireOrMinus1();
    // mLoco sits at +0x34 of the complete vehicle object.
    cVehicle* pOwner = (cVehicle*)((char*)this - 0x34);
    return pOwner->Slot4c() == empire;
}

// @ 0x00c9e6d0
uint32_t RadiusTableValue(int a, int b)
{
    if (GetCurrentGameMode() == &gModeFive)
        return kRadiusTable1[b];
    return kRadiusTable2[a * 3 + b];
}

// @ 0x00c9e700
void cVehicle::UpdateDamageState()
{
    if (GetCurrentGameMode() != &gModeFour)
        return;
    if (!mLoco.Slot58())
        return;
    if (kModeScaleA >= mCombatant.GetValue()) {
        if (mCombatant.GetValue() > 0.0f)
            NounManager()->GetPlayerCivilization()->mField430 = 1;
    }
}

// @ 0x00c9e760
void cVehicle::WriteAsText(void* ar)
{
    BaseWriteAsText(ar);
    if (mField77c > 100)
        mField778 = mField774;
    mField77c = 0;
}

// @ 0x00c9e790
bool cVehicle::RemoveOwner(int owner)
{
    if (!Slot14())
        return false;
    return BaseRemoveOwner() ? true : false;
}

// @ 0x00c9e7c0
float cVehicle::GetHealthFraction()
{
    float value = mCombatant.mValue;
    float ratio = value / mCombatant.GetFraction();
    float lo = 0.0f;
    float hi = kRealOne;
    ratio = ratio > lo ? ratio : lo;
    ratio = ratio < hi ? ratio : hi;
    return NounManager()->Func00b25f40(Slot4c())->Func00bf2170(mFieldB20, mFieldB1c) * (ratio * kHalf);
}

// @ 0x00c9e8a0
void cVehicle::GetC3C(Float3* out, float* a, float* b)
{
    *out = mVecC3c;
    *a = mFieldC48;
    *b = mFieldC4C;
}

// @ 0x00c9e8e0
bool TerrainFlagForType(int type, int data)
{
    cPlanetModel* pModel = PlanetModel();
    switch (type) {
    case 0:
        return (int)(pModel->GetAverageRadius(data) & 0x98000000) == 0;
    case 1:
        return (int)(pModel->GetAverageRadius(data) & 0x58000000) == 0;
    case 2:
        return ((~(pModel->GetAverageRadius(data) >> 29)) & 1) != 0;
    }
    return true;
}

// @ 0x00c9e960
bool cVehicle::CanOccupyTerrain(int data)
{
    if (!TerrainFlagForType(mFieldB1c, data))
        return false;
    if (mFieldB1c == 2)
        return true;
    cPlanetModel* pModel = PlanetModel();
    int continent = pModel->GetContinent(mLoco.Slot2c());
    return continent == pModel->GetContinent(data);
}

// @ 0x00c9e9e0
bool cVehicle::Write(cArchive* ar)
{
    uint32_t value = (uint32_t)&gNullObjectKey;
    WriteUint32(ar->Slot20()->GetHandle(), &value, 1, 0);
    bool ok = BaseWrite(ar) && mCombatant.Write(ar) && mLoco.Write(ar);
    cVarListSerializer serializer(this, kSerializerKey, kSerializerName);
    return serializer.Serialize(ar) && ok;
}

// @ 0x00c9eaf0
int cVehicle::GetMode()
{
    if (mFieldD04 != 0)
        return 6;
    switch (mFieldB1c) {
    case 0: {
        uint8_t low = mFieldAF8;
        uint8_t inverted = ~low;
        return (inverted >> 2) & 1;
    }
    case 1:
        return 2;
    }
    if (mPairIdB == 0x476a98c7)
        return 7;
    if (mFieldAF8 & 1)
        return 4;
    int masked = (mFieldAF8 & 2) != 0;
    return 3 + masked * 2;
}

// @ 0x00c9eb60
float ModeRadiusScale()
{
    if (GetCurrentGameMode() == &gModeTen)
        return kModeScaleC;
    return kModeScaleB;
}

// @ 0x00c9eb80
float cVehicle::GetModeRadius()
{
    // the carrier type is read before each GetMode call in the retail code; the volatile access keeps
    // this load ordered in front of the call (GetMode may clobber ecx on some paths).
    int type = ((volatile const cVehicle*)this)->mFieldB1c;
    float radius;
    if (type == 2) {
        if (GetMode() == 7)
            return kModeScaleD;
        if (GetCurrentGameMode() == &gModeTen)
            radius = kModeScaleC;
        else
            radius = kModeScaleB;
        return radius;
    }
    if (GetMode() == 1)
        return kExtraRadius;
    return 0.0f;
}

// @ 0x00c9ec00
float cVehicle::GetFraction()
{
    float a, b;
    PropertyPairRead(&mPairIdA, &b, &a);
    return mLoco.Slot34() / (a - b);
}

// @ 0x00c9ec50
float cVehicle::GetArea()
{
    return (float)(mFieldB90 * mFieldB90) * kAreaScale;
}

// @ 0x00c9ec80
void cVehicle::SetDrone(bool on)
{
    mFieldBCE = (uint8_t)on;
    if (on)
        mpFieldAF0->mFlagsView.mFlags |= 0x40;
    else
        mpFieldAF0->mFlagsView.mFlags &= ~0x40u;
}

// @ 0x00c9ecb0
void cVehicle::SetJustEyeCandy(bool on)
{
    if (on)
        mpFieldAF0->mFlagsView.mFlags |= 0x80;
    else
        mpFieldAF0->mFlagsView.mFlags &= ~0x80u;
}

// @ 0x00c9ece0
void cLoco::SetValue(float v, int n)
{
    SetProperty(v, n);
}

// @ 0x00c9ed00
int WeaponClassFromHash(uint32_t hash)
{
    switch (hash) {
    case 0x9ad7d4aa: case 0xbc1041e6: case 0xc0b74287: case 0xf670aa43:
        return 0;
    case 0x8f963dcb: case 0xc15695da: case 0x1f2a25b6: case 0x2a5147a9:
        return 1;
    case 0x1a4e0708: case 0x98e03c0d: case 0x441cd3e6: case 0x2090a11b: case 0x449c040f:
        return 2;
    }
    return 0;
}

// @ 0x00c9ed80
int WeaponSlotFromHash(uint32_t hash)
{
    switch (hash) {
    case 0x8f963dcb: case 0x98e03c0d: case 0x441cd3e6: case 0x7d433fad:
        return 0;
    case 0xbc1041e6: case 0xc15695da: case 0x2090a11b:
        // the retail code resolves the game mode here; both outcomes are 0
        if (GetCurrentGameMode() == &gModeTen)
            return 0;
        return 0;
    case 0x9ad7d4aa: case 0x1f2a25b6: case 0x449c040f:
        return 1;
    case 0x1a4e0708: case 0xf670aa43: case 0x2a5147a9:
        return 2;
    case 0xc0b74287:
        return 3;
    }
    return 0;
}

// @ 0x00c9ee30
void cVehicle::SetTimer(int v)
{
    mFieldD28 = (uint32_t)v;
    mFieldD24 = (uint32_t)v;
}

// @ 0x00c9ee50
void cVehicle::ConsumeTimer()
{
    mFieldD24 = mFieldD28;
    mFieldD28 = 0;
}

// @ 0x00c9eea0
void cVehicle::PlaySomething()
{
    mpFieldAF0->mChild.Func(0x1000, 0, kTwo, 0);
}

// @ 0x00c9eed0
bool cVehicle::HasBit2000()
{
    unsigned __int64 bits = *(unsigned __int64*)&mpField5e8->mBits;   // 64-bit flag word at +0x1c8
    return (bits & 0x2000) != 0;
}

// @ 0x00c9eef0
bool cVehicle::IsFlying()
{
    switch (mFieldB1c) {
    case 0:
        return ((~(mFieldAF8 >> 2)) & 1) != 0;
    case 1:
        return true;
    case 2:
        return true;
    }
    return false;
}

// @ 0x00c9ef20
int CStub::FUN_00c9ef20()
{
    if (((TimerStub*)((char*)this + 0xcd8))->IsRunning()) {
        u64 t = ((TimerStub*)((char*)this + 0xcd8))->GetElapsedTime();
        if (t < (u64)*(u32*)((char*)this + 0xcf8))
            return 1;
    }
    return 0;
}

// @ 0x00c9ef60
void CStub::FUN_00c9ef60(u32 ms)
{
    if (((TimerStub*)((char*)this + 0xcd8))->IsRunning()) {
        u32 prev = *(u32*)((char*)this + 0xcf8);
        u64 t = ((TimerStub*)((char*)this + 0xcd8))->GetElapsedTime();
        if (t < (u64)prev) {
            *(u32*)((char*)this + 0xcf8) = prev + ms;
            return;
        }
    }
    *(u32*)((char*)this + 0xcf8) = ms;
    ((TimerStub*)((char*)this + 0xcd8))->Restart();
}

// @ 0x00c9f0a0
void* __cdecl FUN_00c9f0a0(void** src, void** end, void** dst)
{
    if (src != end) {
        do {
            if (dst != 0) {
                void* p = *src;
                *dst = p;
                if (p != 0)
                    (**(void(__thiscall**)(void*))(vpt(p) + 4))(p);
                dst[1] = src[1];
                dst[2] = src[2];
                *(char*)((char*)dst + 0xc) = *(char*)((char*)src + 0xc);
            }
            src += 4;
            dst += 4;
        } while (src != end);
    }
    return dst;
}

// Closest attempt, same size as retail. The first object's calls and both
// distances match, and `d2 > d1 ? 1 : 0` gives the two full-width epilogues.
// Left: the second position call keeps its slot in edx, and each kind check
// loads the vtable into eax instead of edx.

// @ 0x00c9f130
void __cdecl FUN_00c9f130(void* pv)
{
    int* p = (int*)pv;
    PlanetStub* pm = (PlanetStub*)SP_PlanetModel0();
    float tmp[3];
    int* r = (int*)pm->FUN_00b81630(tmp, (float*)((char*)p + 0x14));
    *(int*)((char*)p + 0x14) = r[0];
    *(int*)((char*)p + 0x18) = r[1];
    *(int*)((char*)p + 0x1c) = r[2];
    int n = (p[1] - p[0]) / 0x3c;
    if (n > 0) {
        int off = 0;
        do {
            int* q = (int*)(p[0] + off);
            int* r2 = (int*)pm->FUN_00b81630(tmp, (float*)q);
            q[0] = r2[0];
            q[1] = r2[1];
            q[2] = r2[2];
            off += 0x3c;
            --n;
        } while (n != 0);
    }
}

// @ 0x00c9f1c0
void* CStub_s00c9_ef20::FUN_00c9f1c0()
{
    void* f = *(void**)((char*)g_16c7aa4 + 0x74);
    return ((FieldStub*)f)->FUN_00f3f950(this);
}

// @ 0x00c9f250
int CStub_s00c9_ef20::FUN_00c9f250()
{
    char* self = (char*)this;
    int n = (*(int*)(self + 0xc68) - *(int*)(self + 0xc64)) >> 4;
    if (n > 0) {
        int off = 0;
        int cnt = n;
        do {
            if (ToolSlot_00c9f250(self, off)->FUN_0104bd50())
                ((ToolManagerStub*)SP_ToolManager())->FUN_0104fa90(ToolSlot_00c9f250(self, off));
            off += 0x10;
            --cnt;
        } while (cnt != 0);
    }
    if (*(RefStub**)(self + 0xb60) != 0 &&
        (*(RefStub**)(self + 0xb60))->FUN_0104bd50())
        ((ToolManagerStub*)SP_ToolManager())->FUN_0104fa90(ExtraSlotTool_00c9f250(self));
    return n;
}

// @ 0x00c9f2d0
void CStub_s00c9_ef20::FUN_00c9f2d0(int a)
{
    *(int*)((char*)this + 0xc80) -= a;
    if (!(*(int*)((char*)this + 0xc80) > 0)) {
        if (*(int*)((char*)this + 0xb20) != 1) {
            int r = FUN_00c9f250();
            ++*(int*)((char*)this + 0xc78);
            if (*(int*)((char*)this + 0xc78) >= r)
                *(int*)((char*)this + 0xc78) = 0;
        }
        *(int*)((char*)this + 0xc80) = *(int*)((char*)this + 0xc7c);
    }
    *(int*)((char*)this + 0xc84) += a;
}

// @ 0x00c9f330
float CStub_s00c9_ef20::FUN_00c9f330()
{
    float k = g_1485720;
    if (GetCurrentGameMode() == &g_1654c10) {
        void* f = *(void**)((char*)g_16c7aa4 + 0x74);
        int r = (int)((FieldStub*)f)->FUN_00f3f950(this);
        if (r != 0)
            k = *(float*)(r + 0x494);
    }
    return *(float*)((char*)this + 0xc5c) * k;
}

// @ 0x00c9f380
float CStub_s00c9_ef20::FUN_00c9f380()
{
    float k = g_1485720;
    if (GetCurrentGameMode() == &g_1654c10) {
        void* f = *(void**)((char*)g_16c7aa4 + 0x74);
        int r = (int)((FieldStub*)f)->FUN_00f3f950(this);
        if (r != 0)
            k = *(float*)(r + 0x490);
    }
    return *(float*)((char*)this + 0x218) * k;
}

// @ 0x00c9f3d0
void* CStub_s00c9_ef20::FUN_00c9f3d0()
{
    VObjStub* p = *(VObjStub**)((char*)this + 0xb5c);
    if (p != 0) {
        if (p->v2c()) {
            VObjStub* q = *(VObjStub**)((char*)this + 0xb5c);
            if (q != 0) {
                *(void**)((char*)this + 0xb5c) = 0;
                q->v04();
            }
        }
    }
    return *(void**)((char*)this + 0xb5c);
}

// @ 0x00c9f410
u8 CStub_s00c9_ef20::FUN_00c9f410()
{
    VObjStub* p = *(VObjStub**)((char*)this + 0xb5c);
    if (p != 0 && p->v2c()) {
        VObjStub* q = *(VObjStub**)((char*)this + 0xb5c);
        if (q != 0) {
            *(void**)((char*)this + 0xb5c) = 0;
            q->v04();
        }
    }
    VObjStub* r = *(VObjStub**)((char*)this + 0xb5c);
    if (r != 0) {
        int a = r->v4c();
        int b = ((VObjStub*)this)->v4c();
        if (a == b) {
            if (((XStub*)r)->FUN_00c004c0(0) || ((XStub*)r)->FUN_00c004c0(1))
                return 1;
        }
    }
    return 0;
}

// @ 0x00c9f490
u8 CStub::FUN_00c9f490(void* a, void* b)
{
    if (a == 0)
        return 0;
    if (b == 0)
        return 1;
    float* self = (float*)this;
    void* o1 = ((void*(__thiscall*)(void*))((void**)*(void***)a)[2])(a);
    float* p1 = (float*)(**(void*(__thiscall**)(void*))(vpt(o1) + 0x2c))(o1);
    float dx1 = self[0] - p1[0];
    float dy1 = self[1] - p1[1];
    float dz1 = self[2] - p1[2];
    float d1 = sqrtf(dx1 * dx1 + dy1 * dy1 + dz1 * dz1);
    void* o2 = ((void*(__thiscall*)(void*))((void**)*(void***)b)[2])(b);
    float* p2 = (float*)(**(void*(__thiscall**)(void*))(vpt(o2) + 0x2c))(o2);
    float dx2 = self[0] - p2[0];
    float dy2 = self[1] - p2[1];
    float dz2 = self[2] - p2[2];
    float d2 = sqrtf(dx2 * dx2 + dy2 * dy2 + dz2 * dz2);
    if (d1 < self[3]) {
        if ((**(int(__thiscall**)(void*, int))(vpt(a) + 0x5c))(a, 0x436f315) != 0 ||
            (**(int(__thiscall**)(void*, int))(vpt(a) + 0x5c))(a, 0x137e8e0) != 0)
            d1 = 0.0f;
    }
    if (d2 < self[3]) {
        if ((**(int(__thiscall**)(void*, int))(vpt(b) + 0x5c))(b, 0x436f315) != 0 ||
            (**(int(__thiscall**)(void*, int))(vpt(b) + 0x5c))(b, 0x137e8e0) != 0)
            d2 = 0.0f;
    }
    return d2 > d1 ? 1 : 0;
}

// @ 0x00c9f5c0
void CStub_s00c9_ef20::FUN_00c9f5c0()
{
    if (GetCurrentGameMode() != &g_1654c04)
        return;
    VObjStub* sub = (VObjStub*)((char*)this + 0x34);
    if (!sub->v58())
        return;
    u32 flags = 0;
    if (sub->v50())
        flags = 1;
    if (((ToolStub*)((char*)this + 0x508))->FUN_00bfc5d0() || sub->v24())
        flags |= 2;
    bool changed = flags != *(u32*)((char*)this + 0xc38);
    if (changed)
        *(u32*)((char*)this + 0xc38) = flags;
    ((CivMgrStub_s00c9_ef20*)FUN_00cf74c0())->FUN_00cf8d60(this, changed, flags);
}

// @ 0x00c9f650
float* CStub_s00c9_ef20::FUN_00c9f650(Vec3& out)
{
    int id = ((VObjStub*)this)->v4c();
    void* nm = SP_NounManager(id);
    int e = ((NounStub*)nm)->FUN_00b25f40();
    if (e != 0) {
        out.x = *(float*)(e + 0xc4);
        out.y = *(float*)(e + 0xc8);
        out.z = *(float*)(e + 0xcc);
        return (float*)&out;
    }
    out.x = g_1699b08;
    out.y = g_1699b0c;
    out.z = g_1699b10;
    return (float*)&out;
}

// @ 0x00c9f6c0
void CStub_s00c9_ef20::FUN_00c9f6c0()
{
    if (g_1699ab8 == 0) {
        void* p = EAAllocate(0x58, "Simulator/SimSingleton", 0, 0, 0, 0);
        g_1699ab8 = (p != 0) ? ((SimSingletonStub*)p)->FUN_00dc7d70() : 0;
    }
    int i1 = *(int*)((char*)this + 0xb1c);
    ((SimSingletonStub*)g_1699ab8)->FUN_00dcc300(g_1474a50[i1]);
    if (g_1699ab8 == 0) {
        void* p = EAAllocate(0x58, "Simulator/SimSingleton", 0, 0, 0, 0);
        g_1699ab8 = (p != 0) ? ((SimSingletonStub*)p)->FUN_00dc7d70() : 0;
    }
    int i2 = *(int*)((char*)this + 0xb20);
    ((SimSingletonStub*)g_1699ab8)->FUN_00dcc300(g_1474a44[i2]);
}

// @ 0x00c9f750
void CStub::FUN_00c9f750(char on)
{
    if (on != 0) {
        if (!((IVehicleIface*)this)->v50() && GetCurrentGameMode() == &g_1654c04) {
            int m = (int)FUN_00cf74c0();
            if (*(char*)(m + 0x148) != 0) {
                if (!((CivMgrStub*)FUN_00cf74c0())->FUN_00cf7830((void*)0x64e6678))
                    return;
            }
            ((CStub*)((char*)this - 0x34))->FUN_00c9f6c0();
            *((char*)this + 0x6c) = on;
            FUN_00c9e5d0();
            return;
        }
    }
    *((char*)this + 0x6c) = on;
}

// @ 0x00c9f7c0
void CStub::FUN_00c9f7c0()
{
    int p = *(int*)((char*)this + 0xb68);
    if (p == *(int*)((char*)this + 0xb6c))
        return;
    int kind = *(int*)(p + 0x10);
    EffStub* eff = (EffStub*)((char*)*(void**)((char*)this + 0xaf0) + 8);
    eff->FUN_00bc97f0(1, 0, g_14749a8, 0);
    switch (kind) {
    case 1: eff->FUN_00bc97f0(2, 0, g_14749a8, 0); return;
    case 2: eff->FUN_00bc97f0(4, 0, g_14749a8, 0); return;
    case 3: eff->FUN_00bc97f0(0x10, 0, g_14749a8, 0); return;
    case 4: eff->FUN_00bc97f0(0x20, 0, g_14749a8, 0); return;
    case 5: eff->FUN_00bc97f0(0x40, 0, g_14749a8, 0); return;
    case 6: eff->FUN_00bc97f0(0x80, 0, g_14749a8, 0); return;
    case 7: eff->FUN_00bc97f0(0x100, 0, g_14749a8, 0); return;
    case 8: eff->FUN_00bc97f0(0x200, 0, g_14749a8, 0); return;
    case 9: eff->FUN_00bc97f0(0x400, 0, g_14749a8, 0); return;
    case 10: {
        eff->FUN_00bc97f0(0x800, 0, g_14749a8, 0);
        void* r = eff->FUN_00bc97f0(0x800, 0, g_14749a8, 0);
        if (r != 0)
            *(int*)((char*)r + 0xc) = 0;
        return;
    }
    case 11: {
        eff->FUN_00bc97f0(0x800, 0, g_14749a8, 0);
        void* r = eff->FUN_00bc97f0(0x800, 0, g_14749a8, 0);
        if (r != 0)
            *(int*)((char*)r + 0xc) = 1;
        return;
    }
    case 12:
        eff->FUN_00bc97f0(0x4000, 0, g_14749a8, 0);
        return;
    }
}

// @ 0x00c9fa30
void CStub_s00c9_ef20::FUN_00c9fa30(void* p)
{
    if (p == 0)
        return;
    void** slot = *(void***)((char*)this + 0xb68);
    void* old = *slot;
    if (p == old)
        return;
    (**(void(__thiscall**)(void*))(vpt(p)))(p);
    *slot = p;
    if (old != 0)
        (**(void(__thiscall**)(void*))(vpt(old) + 4))(old);
}

// @ 0x00c9fa70
void CStub::SetStance(u32 stance, char b)
{
    *(u32*)((char*)this + 0xb24) = stance;
    *(u32*)((char*)*(void**)((char*)this + 0xaf0) + 0x5fc) &= 0xfffffcff;
    switch (*(u32*)((char*)this + 0xb24)) {
    case 1:
        *(u32*)((char*)*(void**)((char*)this + 0xaf0) + 0x5fc) |= 0x200;
        if (b == 0) {
            ((Vector24Stub*)FUN_00c9efc0())->PushUnique((u32)g_1474a70[*(int*)((char*)this + 0xb20)]);
            return;
        }
        break;
    case 0:
        *(u32*)((char*)*(void**)((char*)this + 0xaf0) + 0x5fc) |= 0x100;
        if (b == 0) {
            ((Vector24Stub*)FUN_00c9efc0())->PushUnique((u32)g_1474a5c[*(int*)((char*)this + 0xb20)]);
            return;
        }
        break;
    }
}

// @ 0x00c9fb10
int CStub::FUN_00c9fb10(void* p)
{
    if (*(int*)this == *(int*)p &&
        *(int*)((char*)this + 0x10) == *(int*)((char*)p + 0x10) &&
        *(int*)((char*)this + 0x14) == *(int*)((char*)p + 0x14))
        return 1;
    return 0;
}

// @ 0x00c9fb40
void CStub::FUN_00c9fb40(float a, int b, int c, float d, float e)
{
    float* v = (float*)((char*)this + 0xc3c);
    *(int*)v = *(int*)&a;
    *(int*)((char*)this + 0xc40) = b;
    *(int*)((char*)this + 0xc44) = c;
    float len = FUN_00c9eb80();
    if (len > 0.0f) {
        float x = v[0], y = v[1], z = v[2];
        float inv = 1.0f / sqrtf(z * z + (y * y + x * x) + g_13ec4b8);
        float out[3];
        PlanetStub* pm = (PlanetStub*)SP_PlanetModel0();
        float* sp = pm->DirectionToSurfacePosition(out, v);
        float nx = (x * inv) * len;
        float ny = (y * inv) * len;
        float nz = (z * inv) * len;
        v[0] = sp[0] + nx;
        v[1] = sp[1] + ny;
        v[2] = sp[2] + nz;
    }
    *(float*)((char*)this + 0xc48) = d;
    *(float*)((char*)this + 0xc4c) = e;
}

// @ 0x00c9fc60
void CStub::FUN_00c9fc60(void* p)
{
    FUN_00c88670(p);
    TimerStub* timer = *(TimerStub**)((char*)this + 0xcd8);
    if (timer != 0)
        timer->FUN_00ff0430(p);
    if (*(int*)((char*)this + 0xcc8) != 0) {
        float* vel = FUN_00d20610();
        float lo = g_1485720;
        float hi = g_1485548;
        float spd = sqrtf(vel[0] * vel[0] + vel[1] * vel[1] + vel[2] * vel[2]) * g_1474a84;
        spd = SseClamp(spd, lo, hi);
        volatile float factor = spd;
        float m = ((float(__thiscall*)(void*))((void**)*(void***)this)[0x70 / 4])(this);
        ((VStub*)*(void**)((char*)this + 0xcc8))->FUN_00c3f160(p, m * factor);
    }
    int q = *(int*)((char*)this + 0xccc);
    if (q != 0) {
        *(int*)(q + 4) = *(int*)p;
        *(int*)(q + 8) = *(int*)((char*)p + 4);
        *(int*)(q + 0xc) = *(int*)((char*)p + 8);
    }
}

// @ 0x00c9fd40
void CStub::FUN_00c9fd40(void* p)
{
    FUN_00c886d0(p);
    int e = *(int*)((char*)this + 0xccc);
    if (e == 0)
        return;
    float v[4];
    v[0] = *(float*)((char*)p + 4);
    v[1] = -*(float*)p;
    v[2] = *(float*)((char*)p + 0xc);
    v[3] = -*(float*)((char*)p + 8);
    *(u32*)(e + 0x10) = *(u32*)&v[0];
    *(u32*)(e + 0x14) = *(u32*)&v[1];
    *(u32*)(e + 0x18) = *(u32*)&v[2];
    *(u32*)(e + 0x1c) = *(u32*)&v[3];
}

// Closest attempt, 118 vs 121. The virtual call now keeps its target in edx,
// and the empty-path compare matches. The last element is reloaded into ecx
// and x is read at [ecx-0x3c]. cl still folds `p -= 1` away, so y and z stay
// at [ecx-0x38] and [ecx-0x34] instead of retail's `sub ecx, 0x3c` then [ecx+4]
// and [ecx+8].
struct Rec3C_s00c9_fdc0 {
    float x, y, z;
    char pad[0x30];
};

// @ 0x00c9fdc0
float* CStub::FUN_00c9fdc0(float* out)
{
    if (*(int*)((char*)this + 0x284) == 0) {
        float* p = ((float*(__thiscall*)(void*))((void**)*(void***)((char*)this + 0x34))[11])((char*)this + 0x34);
        out[0] = p[0];
        out[1] = p[1];
        out[2] = p[2];
        return out;
    }
    if (*(volatile int*)((char*)this + 0x228) == *(int*)((char*)this + 0x22c)) {
        out[0] = *(float*)((char*)this + 0x23c);
        out[1] = *(float*)((char*)this + 0x240);
        out[2] = *(float*)((char*)this + 0x244);
        return out;
    }
    Rec3C_s00c9_fdc0* p = *(Rec3C_s00c9_fdc0* volatile*)((char*)this + 0x22c);
    out[0] = (p - 1)->x;
    p -= 1;
    out[1] = p->y;
    out[2] = p->z;
    return out;
}

// Same-continent check gated by the mode at this+0xb1c. The continent table
// at planet+0x64 is re-read inside each case (no hoisted local), each case
// tail spells its own copy of the p position vcall, and the final compare is
// a `? 1 : 0` ternary: that one result temporary is what rotates the
// allocator onto retail's registers (this in ebx, continent index in edi,
// two vcall copies with swapped scratch pairs).

// @ 0x00c9fe40
u8 CStub::FUN_00c9fe40(void* p)
{
    PlanetStub* planet = (PlanetStub*)SP_PlanetModel0();
    if (planet == 0)
        return 0;
    float* pos = ((float*(__thiscall*)(void*))((void**)*(void***)((char*)this + 0x34))[11])((char*)this + 0x34);
    int c1 = planet->GetContinent(pos);
    switch (*(int*)((char*)this + 0xb1c)) {
    case 1:
        if (*(char*)(*(int*)((char*)planet + 0x64) + c1) != 0)
            return 1;
        {
            float* pos2 = ((float*(__thiscall*)(void*))((void**)*(void***)((char*)p + 0x34))[11])((char*)p + 0x34);
            return c1 == planet->GetContinent(pos2) ? 1 : 0;
        }
    case 0:
        if (*(char*)(*(int*)((char*)planet + 0x64) + c1) == 0) {
            return 1;
        } else {
            float* pos2 = ((float*(__thiscall*)(void*))((void**)*(void***)((char*)p + 0x34))[11])((char*)p + 0x34);
            return c1 == planet->GetContinent(pos2) ? 1 : 0;
        }
    case 2:
        return 0;
    default:
        return 0;
    }
}

// @ 0x00c9fee0
void* CStub::FUN_00c9fee0()
{
    if (*(void**)((char*)this + 0xb7c) != 0) {
        _ReadWriteBarrier();
        IResIface* q = (IResIface*)*(void**)((char*)this + 0xb7c);
        if (q != 0) {
            void* r = q->vb8(0x17f243b);
            if (r != 0 && ((IResIface*)r)->v2c()) {
                IResIface* s = (IResIface*)*(void**)((char*)this + 0xb7c);
                *(void**)((char*)this + 0xb7c) = 0;
                if (s != 0)
                    s->vc0();
            }
        }
    }
    return *(void**)((char*)this + 0xb7c);
}

// @ 0x00c9ff40
void CStub::FUN_00c9ff40(int a, float* out1, float* out2)
{
    PlanetStub* pm = (PlanetStub*)SP_PlanetModel(a);
    float f = pm->FUN_00b7efe0();
    if (*(int*)((char*)this + 0xb1c) == 2) {
        PlanetStub* pm2 = (PlanetStub*)SP_PlanetModel0();
        float wh = pm2->GetWaterHeight();
        float base = FUN_00c9eb80() + wh;
        *out1 = base;
        if (base - g_157c70c < f)
            *out1 = g_157c70c + f;
    } else {
        *out1 = FUN_00c9eb80() + f;
    }
    *out2 = *out1 - f;
}

// @ 0x00c9ffd0
float __fastcall FUN_00c9ffd0(float param_1)
{
    // The helper takes the float's bits as its first argument and two out slots (only the first
    // is read back, as the float result).
    int local_4;
    FUN_00c9ff40(*(int*)&param_1, &param_1, (float*)&local_4);
    return param_1;
}

// @ 0x00ca0040
int __thiscall Obj::GetAltTarget()
{
    Obj* o = this;
    if (o->f_d6c == 0 && o->f_d70 == 0) return o->f_d64;

    float a, b;
    FUN_00eed0b0(o->propC4, &a, &b);

    float dt = (*(TFnF)VTFN(&o->vptr34, 0x34 / 4))(&o->vptr34);

    float ratio = dt / (b - a);
    int iVar2 = o->f_d6c;
    if (iVar2 != 0 && ratio < o->f_d8c) {
        switch (o->mLocomotion) {
        case 0: if (o->f_d74) return o->f_d74; return iVar2;
        case 1: if (o->f_d7c) return o->f_d7c; return iVar2;
        case 2: if (o->f_d84) return o->f_d84; return iVar2;
        default: return iVar2;
        }
    }
    iVar2 = o->f_d70;
    if (iVar2 != 0 && o->f_d90 <= ratio && ratio != o->f_d90) {
        switch (o->mLocomotion) {
        case 0: if (o->f_d78) return o->f_d78; return iVar2;
        case 1: if (o->f_d80) return o->f_d80; return iVar2;
        case 2: if (o->f_d78 != 2) return o->f_d80; return iVar2;
        default: return iVar2;
        }
    }
    return o->f_d64;
}

// @ 0x00ca0170
bool __thiscall Obj::BringGoalToAltitude(float* target)
{
    Obj* o = this;
    if (o->mLocomotion == 2 && SP_GetCurrentGameMode() == g_01654c10) return false;

    SP_PlanetModel();
    float* pos = (*(TFnPF)VTFN(&o->vptr34, 0x2c / 4))(&o->vptr34);

    float dx = target[0] - pos[0];
    float dy = target[1] - pos[1];
    float dz = target[2] - pos[2];
    float dist = sqrtf((dz * dz + dy * dy) + dx * dx);
    if (dist > g_1477fbc) return true;

    float inv = g_1485720_s00c9_ffd0 / dist;
    float sx = inv * dx;
    float sy = dy * inv;
    float sz = dz * inv;

    pos = (*(TFnPF)VTFN(&o->vptr34, 0x2c / 4))(&o->vptr34);
    float px = pos[0] + sx;
    float py = pos[1] + sy;
    float pz = pos[2] + sz;

    int n = (int)(dist * g_140e87c);
    for (int i = 0; i < n; i++) {
        int mode = o->mLocomotion;
        void* pm = SP_PlanetModel();
        bool hit;
        if (mode == 0) {
            hit = (SP_GetAverageRadius(pm, &px) & 0x98000000) == 0;
        } else if (mode == 1) {
            hit = (SP_GetAverageRadius(pm, &px) & 0x58000000) == 0;
        } else {
            hit = (~(unsigned)SP_GetAverageRadius(pm, &px) >> 5) & 1;
        }
        if (hit) return true;
        px = px + sx;
        py = py + sy;
        pz = pz + sz;
    }
    return false;
}

// @ 0x00ca0340
int __thiscall Obj::TimerExpired()
{
    unsigned* self = (unsigned*)this;
    int* timer = (int*)((char*)self + 0x7d0);
    if (FUN_00feba90(timer)) {
        uint64_t t = FUN_00bc3190(timer);
        if (t < (uint64_t)self[0x7f0 / 4]) return 0xacf33281;
    }
    return 0;
}

// @ 0x00ca0380
int __thiscall Obj::GetArrayCount()
{
    void* a = this->mpArray;
    if (a) return (*(int*)((char*)a + 0x54) - *(int*)((char*)a + 0x50)) >> 2;
    return 0;
}

// 0x00ca03a0 (byte-exact lifted version: match/slices/s00ca03a0/s00ca03a0.cpp)
int __thiscall Obj::CreateInteract(int key)
{
    int result = 0;
    if (this->mpCreature != 0) {
        void* lm = SP_LayerManager();
        if ((*(TFnPK)VTFN(lm, 0x40 / 4))(lm, key)) {
            result = (*(TFnIII)VTFN(this->mpCreature, 2))(this->mpCreature, key, 0);
            (*(TFnVII)VTFN(this->mpCreature, 3))(this->mpCreature, result, 1);
            (*(TFnVI)VTFN(this->mpCreature, 6))(this->mpCreature, result);
            (*(TFnVII)VTFN(this->mpCreature, 0x10))(this->mpCreature, result, key);
            (*(TFnVII)VTFN(this->mpCreature, 0xf))(this->mpCreature, result, 0);
        }
    }
    return result;
}

// @ 0x00ca0430
void __thiscall Obj::ClearCreature()
{
    if (this->mpCreature == 0) return;
    void* p = (*(TFnP)VTFN(this->mpCreature, 0x1c))(this->mpCreature);
    if (!p) return;

    ((IDummy*)this->mpCreature)->SetAttach(0);
    void* q = (*(TFnP)VTFN(this->mpCreature, 0x1c))(this->mpCreature);
    (*(TFnVV)VTFN(q, 0xf))(q, this->mpCreature);

    if (this->mpCreature) {
        void* old = this->mpCreature;
        this->mpCreature = 0;
        ((IDummy*)old)->Rel();
    }

    (*(TFnVF)VTFN(&this->vptr34, 0x40 / 4))(&this->vptr34, 1.0f);
}

// @ 0x00ca04a0
void __thiscall Obj::ProcessEA()
{
    if (this->mpEA == 0) return;

    for (;;) {
        void* ea = this->mpEA;
        int idx = (*(TFnIII)VTFN(ea, 0x6c / 4))(ea, 8, 0);
        if (idx == -1) break;
        void* e = (*(TFnPI)VTFN(ea, 0x60 / 4))(ea, idx);
        if (!e) continue;

        void* pi = (void*)(*(TFnIU)VTFN((char*)e + 0xc, 3))((char*)e + 0xc, 0x73905ae);
        if (!pi) continue;

        REF_ADDREF(pi);
        (*(TFnVV)VTFN(this->mpEA, 0x78 / 4))(this->mpEA, pi);

        void* v = FUN_00c6f660(this);
        if (v) {
            void* r = (void*)(*(TFnIU)VTFN(v, 3))(v, 0x1186577);
            if (r) {
                void* s34 = &this->vptr34;
                float* pp = (*(TFnPF)VTFN(s34, 0x2c / 4))(s34);
                (*(TFnVV)VTFN(r, 0x38 / 4))(r, pp);
                float* qq = (*(TFnPF)VTFN(s34, 0x30 / 4))(s34);
                (*(TFnVV)VTFN(r, 0x3c / 4))(r, qq);
                *(uint8_t*)((char*)r + 0x71) = 0;

                float* pf = (*(TFnPF)VTFN(s34, 0x2c / 4))(s34);
                float inv = g_1485720_s00c9_ffd0 / sqrtf(((pf[0] * pf[0] + pf[1] * pf[1]) + pf[2] * pf[2]) + g_13ec4b8_s00c9_ffd0);

                float off1[3];
                (*(TFnVV)VTFN(s34, 0x5c / 4))(s34, off1);
                float off2[3];
                (*(TFnVV)VTFN(s34, 0x5c / 4))(s34, off2);

                float ex = off2[0] + off1[0];
                float ey = off2[1] + off1[1];
                float ez = off2[2] + off1[2];
                float inv2 = g_1485720_s00c9_ffd0 / sqrtf((ex * ex + (ey * ey + ez * ez)) + g_13ec4b8_s00c9_ffd0);
                float d[3];
                d[0] = (inv2 * ex) * g_157d284;
                d[1] = (ey * inv2) * g_157d284;
                d[2] = (ez * inv2) * g_157d284;

                void* blk = FUN_00b3d310(r, d, 0);
                FUN_00b452f0(blk);
                void* blk2 = FUN_00b3d310(s34, r, (void*)0x40000000);
                FUN_00b4c600(blk2, r, g_1470f1c);
            }
        }
        (*(TFnVV)VTFN(pi, 2))(pi, 0);
    }
}

// 0x00ca07f0 (byte-exact lifted version: match/slices/s00ca07f0/s00ca07f0.cpp)
bool __cdecl FUN_00ca07f0(void* unused, void** range)
{
    void** begin = (void**)range[0];
    void** end = (void**)range[1];
    for (; begin != end; begin++) {
        if (*begin) FUN_00695b40(range, *begin, (void*)0x1570858, L"cCombatant");
    }
    return true;
}

// @ 0x00ca0900
void* __thiscall RefOps::CopyCtor(void* src)
{
    unsigned* s = (unsigned*)src;
    unsigned* d = (unsigned*)this;
    d[0] = s[0];
    if (d[0]) (*(TFnV)VTFN((void*)d[0], 0))((void*)d[0]);
    *(float*)(d + 1) = *(float*)(s + 1);
    *(float*)(d + 2) = *(float*)(s + 2);
    *(float*)(d + 3) = *(float*)(s + 3);
    d[4] = s[4];
    d[5] = s[5];
    return this;
}

// @ 0x00ca0940
void* __thiscall RefOps::AssignA(void* src)
{
    unsigned* s = (unsigned*)src;
    unsigned* d = (unsigned*)this;
    void* old = (void*)d[0];
    void* nw = (void*)s[0];
    if (nw != old) {
        if (nw) (*(TFnV)VTFN(nw, 0))(nw);
        d[0] = (unsigned)nw;
        if (old) (*(TFnV)VTFN(old, 1))(old);
    }
    d[1] = s[1]; d[2] = s[2]; d[3] = s[3]; d[4] = s[4]; d[5] = s[5];
    return this;
}

// @ 0x00ca09a0
void* __thiscall RefOps::AssignB(void* src)
{
    unsigned* s = (unsigned*)src;
    unsigned* d = (unsigned*)this;
    void* old = (void*)d[0];
    void* nw = (void*)s[0];
    if (nw != old) {
        if (nw) (*(TFnV)VTFN(nw, 1))(nw);
        d[0] = (unsigned)nw;
        if (old) (*(TFnV)VTFN(old, 2))(old);
    }
    d[1] = s[1]; d[2] = s[2];
    *(uint8_t*)(d + 3) = (uint8_t)s[3];
    return this;
}

// @ 0x00ca0ad0
void __cdecl FUN_00ca0ad0(void** first, void** last)
{
    if (first == last) return;
    for (void** it = first + 1; it != last; it++) {
        void* val = *it;
        IOREF_ADDREF(val);
        void** hole = it;
        while (hole != first && FUN_00c9f490(hole[-1], val)) {
            void* moved = hole[-1];
            void* dst = *hole;
            if (moved != dst) {
                IOREF_ADDREF(moved);
                *hole = moved;
                IOREF_RELEASE(dst);
            }
            hole--;
        }
        void* dst = *hole;
        if (val != dst) {
            IOREF_ADDREF(val);
            *hole = val;
            IOREF_RELEASE(dst);
        }
        IOREF_RELEASE(val);
    }
}

// @ 0x00ca0ba0
void __cdecl FUN_00ca0ba0(void** first, void** last)
{
    for (; first != last; first++) {
        void* val = *first;
        IOREF_ADDREF(val);
        void** hole = first;
        bool cont = FUN_00c9f490(val, hole[-1]);
        while (cont) {
            void* moved = hole[-1];
            void* dst = *hole;
            if (moved != dst) {
                IOREF_ADDREF(moved);
                *hole = moved;
                IOREF_RELEASE(dst);
            }
            cont = FUN_00c9f490(val, hole[-2]);
            hole--;
        }
        void* dst = *hole;
        if (val != dst) {
            IOREF_ADDREF(val);
            *hole = val;
            IOREF_RELEASE(dst);
        }
        IOREF_RELEASE(val);
    }
}

// @ 0x00ca0cf0
E18* __cdecl FUN_00ca0cf0(E18* s, E18* last, E18* d)
{
    while (s != last) {
        if (d) {
            d->p = s->p;
            if (d->p) (*(TFnV)VTFN(d->p, 0))(d->p);
            d->v = s->v;
            d->u0 = s->u0;
            d->u1 = s->u1;
        }
        s++; d++;
    }
    return d;
}

// @ 0x00ca0da0
E18* __cdecl FUN_00ca0da0(E18* s, E18* last, E18* d)
{
    while (s != last) {
        void* nw = s->p;
        void* old = d->p;
        if (nw != old) {
            if (nw) (*(TFnV)VTFN(nw, 0))(nw);
            d->p = nw;
            if (old) (*(TFnV)VTFN(old, 1))(old);
        }
        d->v = s->v;
        d->u0 = s->u0;
        d->u1 = s->u1;
        s++; d++;
    }
    return d;
}

// @ 0x00ca0e10
E18* __cdecl FUN_00ca0e10(E18* first, E18* s, E18* d)
{
    while (s != first) {
        s--; d--;
        void* nw = s->p;
        void* old = d->p;
        if (nw != old) {
            if (nw) (*(TFnV)VTFN(nw, 0))(nw);
            d->p = nw;
            if (old) (*(TFnV)VTFN(old, 1))(old);
        }
        d->v = s->v;
        d->u0 = s->u0;
        d->u1 = s->u1;
    }
    return d;
}

// @ 0x00ca0e80
E16* __cdecl FUN_00ca0e80(E16* s, E16* last, E16* d)
{
    if (s != last) {
        do {
            void* nw = s->p;
            void* old = d->p;
            if (nw != old) {
                if (nw) (*(TFnV)VTFN(nw, 1))(nw);
                d->p = nw;
                if (old) (*(TFnV)VTFN(old, 2))(old);
            }
            d->u0 = s->u0;
            d->u1 = s->u1;
            d->b0 = s->b0;
            s++; d++;
        } while (s != last);
    }
    return d;
}

// @ 0x00ca0ef0
E16* __cdecl FUN_00ca0ef0(E16* first, E16* s, E16* d)
{
    if (s != first) {
        do {
            s--; d--;
            void* nw = s->p;
            void* old = d->p;
            if (nw != old) {
                if (nw) (*(TFnV)VTFN(nw, 1))(nw);
                d->p = nw;
                if (old) (*(TFnV)VTFN(old, 2))(old);
            }
            d->u0 = s->u0;
            d->u1 = s->u1;
            d->b0 = s->b0;
        } while (s != first);
    }
    return d;
}

// @ 0x00ca0f60
void __cdecl FUN_00ca0f60(void** heap, int top, void* val)
{
    while (top > 0) {
        int parent = (top - 1) >> 1;
        if (!FUN_00c9f490(heap[parent], val)) break;
        void* moved = heap[parent];
        void* dst = heap[top];
        if (moved != dst) {
            IOREF_ADDREF(moved);
            heap[top] = moved;
            IOREF_RELEASE(dst);
        }
        top = parent;
    }
    void* dst = heap[top];
    if (val != dst) {
        IOREF_ADDREF(val);
        heap[top] = val;
        IOREF_RELEASE(dst);
    }
    IOREF_RELEASE(val);
}

// @ 0x00ca1010
void __cdecl FUN_00ca1010(void** a, void** b)
{
    void* av = *a;
    IOREF_ADDREF(av);
    void* bv = *b;
    void* cur = *a;
    if (bv != cur) {
        IOREF_ADDREF(bv);
        *a = bv;
        IOREF_RELEASE(cur);
    }
    void* bv2 = *b;
    if (av != bv2) {
        IOREF_ADDREF(av);
        *b = av;
        IOREF_RELEASE(bv2);
    }
    IOREF_RELEASE(av);
}

// @ 0x00ca10a0
float* __cdecl FUN_00ca10a0()
{
    if (g_0157c908 == g_13eb1bc) {
        void* local = 0;
        void* pm = SP_PropertyManager();
        if (local) { void* t = local; local = 0; (*(TFnV)VTFN(t, 1))(t); }
        char ok = (*(TFnPUUP)VTFN(pm, 0x2c / 4))(pm, 0x4529f96f, 0x40646200, &local);
        if (ok) SP_GetPropertyAsVector3(local, 0x48f5b53, &g_0157c908);
        if (local) (*(TFnV)VTFN(local, 1))(local);
    }
    return &g_0157c908;
}

// @ 0x00ca1130
float* __cdecl FUN_00ca1130()
{
    if (g_0157c914 == g_13eb1bc) {
        void* local = 0;
        void* pm = SP_PropertyManager();
        if (local) { void* t = local; local = 0; (*(TFnV)VTFN(t, 1))(t); }
        char ok = (*(TFnPUUP)VTFN(pm, 0x2c / 4))(pm, 0x4529f96f, 0x40646200, &local);
        if (ok) SP_GetPropertyAsVector3(local, 0x48f5b54, &g_0157c914);
        if (local) (*(TFnV)VTFN(local, 1))(local);
    }
    return &g_0157c914;
}

// @ 0x00ca11c0
__declspec(noinline) float PathSolver::WrapAngle(float a)
{
    while (gTwoPi < a) a -= gTwoPi;
    while (a < 0.0f) a += gTwoPi;
    return a;
}

// @ 0x00ca1210
void __stdcall FUN_00ca1210(float* out, void* obj, float t)
{
    float f = g_0169a288 * t + g_14749b0;
    unsigned ecx = (unsigned&)f;
    unsigned j = (ecx & 0xf) * 2;
    float t0 = g_01677840[j];
    float t1 = g_01677840[j + 1];
    float tt = t - (float)(int)(ecx + 0xb4c00000) * g_0169a284;
    float* o = (float*)obj;
    float c0 = (t1 - (t0 * tt) * g_1471064) * tt + t0;
    float c1 = t1 - ((t1 * tt) * g_1471064 + t0) * tt;
    out[0] = o[0x80 / 4] * c1 + o[0x8c / 4] * c0;
    out[1] = o[0x84 / 4] * c1 + o[0x90 / 4] * c0;
    out[2] = o[0x88 / 4] * c1 + o[0x94 / 4] * c0;
}

// @ 0x00ca1310
bool PathSolver::Solve(PathRequest* p)
{
    if (p->startPos.x == p->endPos.x && p->startPos.y == p->endPos.y && p->startPos.z == p->endPos.z) {
        p->arc0 = 0.0f;
        p->straight = 0.0f;
        p->total = 0.0f;
        return true;
    }

    float ibx = 1.0f / sqrtf(((p->endPos.x * p->endPos.x + p->endPos.y * p->endPos.y) + p->endPos.z * p->endPos.z) + 1e-8f);
    float iax = 1.0f / sqrtf((p->startPos.x * p->startPos.x + (p->startPos.y * p->startPos.y + p->startPos.z * p->startPos.z)) + 1e-8f);
    Vec3_s00ca_1310 d;
    d.x = p->startPos.x * iax + p->endPos.x * ibx;
    d.z = p->startPos.z * iax + p->endPos.z * ibx;
    d.y = p->startPos.y * iax + p->endPos.y * ibx;
    float id = 1.0f / sqrtf((d.y * d.y + (d.z * d.z + d.x * d.x)) + 1e-8f);
    d.x = id * d.x;
    d.y = d.y * id;
    d.z = d.z * id;

    float t = (p->startHeading.x * d.x + p->startHeading.z * d.z) + p->startHeading.y * d.y;
    Vec3_s00ca_1310 u;
    float ux = p->startHeading.x - t * d.x;
    u.y = p->startHeading.y - d.y * t;
    u.z = p->startHeading.z - d.z * t;
    float iu = 1.0f / sqrtf((u.y * u.y + (u.z * u.z + ux * ux)) + 1e-8f);
    u.z = u.z * iu;
    u.y = u.y * iu;
    u.x = iu * ux;
    float dist = sqrtf((p->endPos.x - p->startPos.x) * (p->endPos.x - p->startPos.x) +
                       ((p->endPos.y - p->startPos.y) * (p->endPos.y - p->startPos.y) +
                        (p->endPos.z - p->startPos.z) * (p->endPos.z - p->startPos.z)));

    float t2 = (p->endHeading.x * d.x + p->endHeading.z * d.z) + p->endHeading.y * d.y;
    Vec3_s00ca_1310 v;
    float vx = p->endHeading.x - t2 * d.x;
    v.y = p->endHeading.y - d.y * t2;
    v.z = p->endHeading.z - d.z * t2;
    float iv = 1.0f / sqrtf((v.y * v.y + (v.z * v.z + vx * vx)) + 1e-8f);
    v.y = v.y * iv;
    v.z = v.z * iv;
    v.x = iv * vx;

    Vec3_s00ca_1310 dir;
    float idist = 1.0f / dist;
    dir.z = (p->endPos.z - p->startPos.z) * idist;
    dir.x = idist * (p->endPos.x - p->startPos.x);
    dir.y = (p->endPos.y - p->startPos.y) * idist;
    Vec3_s00ca_1310 n;
    n.x = dir.y * d.z - dir.z * d.y;
    n.y = dir.z * d.x - d.z * dir.x;
    n.z = d.y * dir.x - dir.y * d.x;

    float angU = SignedAngle(&n, &u, &d);
    float angV = SignedAngle(&n, &v, &d);
    p->side = n;
    p->dir = dir;
    p->mid = d;

    bool cwA = p->startCW;
    float ta, tb;
    if (cwA) ta = angU - kHalfPi; else ta = kHalfPi + angU;
    if (p->endCW) tb = angV - kHalfPi; else tb = kHalfPi + angV;
    WrapInline(ta);
    WrapInline(tb);

    float r = p->radius;
    float c0x = cosf(ta) * r;
    float c0y = sinf(ta) * r;
    float c1x = cosf(tb) * r;
    float c1y = sinf(tb) * r + dist;
    float dx = c1x - c0x;
    float dy = c1y - c0y;
    float seg = sqrtf(dx * dx + dy * dy);
    float ang = atan2f(dy, dx);
    WrapInline(ang);

    float arc0, arc1, ta2, h, tx0, ty0, tx1, ty1;
    if (cwA == p->endCW) {
        float off = kHalfPi;
        if (!cwA) off = -off;
        float hh = ang + off;
        WrapInline(hh);
        ta2 = ta + kPi;
        tx0 = cosf(hh) * r + c0x;
        ty0 = sinf(hh) * r + c0y;
        tx1 = tx0 + dx;
        ty1 = ty0 + dy;
        WrapInline(ta2);
        float a0 = cwA ? ta2 - hh : hh - ta2;
        WrapInline(a0);
        arc0 = a0 * r;
        float tbp = tb + kPi;
        WrapInline(tbp);
        float a1 = p->endCW ? hh - tbp : tbp - hh;
        WrapInline(a1);
        arc1 = a1 * r;
        h = hh;
    } else {
        float two = r * 2.0f;
        float dd = sqrtf((c0y - c1y) * (c0y - c1y) + (c0x - c1x) * (c0x - c1x));
        if (two > dd) return false;
        float ac = acosf(two / dd);
        float h0 = cwA ? ang + ac : ang - ac;
        float hh = WrapAngle(h0);
        h = WrapAngle(hh + kPi);
        tx0 = cosf(hh) * r + c0x;
        ty0 = sinf(hh) * r + c0y;
        tx1 = cosf(h) * r + c1x;
        ty1 = sinf(h) * r + c1y;
        float ey = ty1 - ty0;
        float ex = tx1 - tx0;
        ang = WrapAngle(atan2f(ey, ex));
        seg = sqrtf(ex * ex + ey * ey);
        ta2 = WrapAngle(ta + kPi);
        float a0 = cwA ? ta2 - hh : hh - ta2;
        arc0 = WrapAngle(a0) * r;
        float tbp = WrapAngle(tb + kPi);
        float a1 = p->endCW ? h - tbp : tbp - h;
        arc1 = WrapAngle(a1) * r;
    }
    p->c0x = c0x;
    p->c0y = c0y;
    p->arc1 = arc1;
    p->c1x = c1x;
    p->c1y = c1y;
    p->straight = seg;
    p->t0x = tx0;
    p->t0y = ty0;
    p->t1x = tx1;
    p->t1y = ty1;
    p->arc0 = arc0;
    p->total = (arc1 + arc0) + seg;
    p->ang0 = ta2;
    p->ang1 = tb;
    p->lineAng = ang;
    p->lineAng2 = h;
    return true;
}

// @ 0x00ca1c60
void PathSolver::FUN_00ca1c60(PathSplineData* p)
{
    PathSolver* self = this;
    FUN_00b3d350();
    Vec3_s00ca_1310* center = &p->mCenter;
    float height;
    float offset;
    self->mPlanet->FUN_00c9ff40(center, &height, &offset);

    float inv = 1.0f / sqrtf(((center->x * center->x + center->y * center->y) +
                              center->z * center->z) + 1e-8f);
    volatile float vinv = inv;
    volatile float tx = center->x * vinv;
    volatile float ty = center->y * vinv;
    volatile float tz = center->z * vinv;
    center->x = tx * height;
    center->y = ty * height;
    center->z = tz * height;

    int n = p->mpEnd - p->mpBegin;
    for (int i = 0; i < n; i++) {
        Vec3_s00ca_1310* node = (Vec3_s00ca_1310*)((char*)p->mpBegin + i * 0x3c);
        self->mPlanet->FUN_00c9ff40(node, &height, &offset);
        float ninv = 1.0f / sqrtf(((node->x * node->x + node->y * node->y) +
                                   node->z * node->z) + 1e-8f);
        node->x = (node->x * ninv) * height * offset;
        node->y = (node->y * ninv) * height * offset;
        node->z = (node->z * ninv) * height * offset;
    }
}

// @ 0x00ca1dc0
void PathSolver::FUN_00ca1dc0(PathSegment* seg, float t, Vec3_s00ca_1310* pos, Vec3_s00ca_1310* out)
{
    if (seg->mEndTime == 0.0f) {
        *pos = seg->mStartPos;
        SurfaceFrame frame;
        void* orient = FUN_00b3d350()->FUN_00b7f190(&frame, pos);
        Vec3_s00ca_1310 tmp;
        Vec3_s00ca_1310* v = FUN_0059aed0(&tmp, &kDefaultDir, orient);
        *out = *v;
        if (!FUN_0059ab70(out)) {
            *out = kDefaultDir;
        }
        return;
    }

    float tt = t;
    if (seg->mEndTime < tt)
        tt = seg->mEndTime;
    float start = seg->mStartTime;

    float cosv;
    float sinv;

    if (start <= tt) {
        if (tt < seg->mMidDuration + start || seg->mMidFlag == 0.0f) {
            float ang = seg->mStraightAngle;
            float dt = tt - start;
            FUN_00a78ce0(ang, &sinv, &cosv);
            float x = cosv * dt + seg->mCenter50x;
            float y = sinv * dt + seg->mCenter50y;
            cosv = x;
            sinv = y;
            t = ang;
        } else {
            bool cw = seg->mEndCW;
            float sign = cw ? -1.0f : 1.0f;
            float ang = WrapAngle((sign / seg->mRadius) *
                                  (tt - (seg->mMidDuration + start)) + seg->mMidPhase);
            FUN_00a78ce0(ang, &sinv, &cosv);
            float x = seg->mRadius * cosv + seg->mCenter48x;
            float y = seg->mRadius * sinv + seg->mCenter48y;
            cosv = x;
            sinv = y;
            if (!cw)
                ang = kHalfPi + ang;
            else
                ang = ang - kHalfPi;
            ang = WrapAngle(ang);
            t = ang;
        }
    } else {
        bool cw = seg->mStartCW;
        float sign = cw ? -1.0f : 1.0f;
        float ang = (sign / seg->mRadius) * tt + seg->mPrePhase;
        while (gTwoPi < ang)
            ang -= gTwoPi;
        while (ang < 0.0f)
            ang += gTwoPi;
        FUN_00a78ce0(ang, &sinv, &cosv);
        float x = seg->mRadius * cosv + seg->mCenter40x;
        float y = seg->mRadius * sinv + seg->mCenter40y;
        cosv = x;
        sinv = y;
        if (!cw)
            ang = kHalfPi + ang;
        else
            ang = ang - kHalfPi;
        while (gTwoPi < ang)
            ang -= gTwoPi;
        while (ang < 0.0f)
            ang += gTwoPi;
        t = ang;
    }

    Vec3_s00ca_1310 p;
    p.x = seg->mStartPos.x + seg->mBasisU.x * cosv + seg->mBasisV.x * sinv;
    p.y = seg->mStartPos.y + seg->mBasisU.y * cosv + seg->mBasisV.y * sinv;
    p.z = seg->mStartPos.z + seg->mBasisU.z * cosv + seg->mBasisV.z * sinv;
    *pos = p;

    float height;
    float offset;
    mPlanet->FUN_00c9ff40(pos, &height, &offset);
    float inv = 1.0f / sqrtf(((pos->x * pos->x + pos->y * pos->y) +
                              pos->z * pos->z) + 1e-8f);
    pos->x = (pos->x * inv) * height;
    pos->y = (pos->y * inv) * height;
    pos->z = (pos->z * inv) * height;

    Vec3_s00ca_1310 tmp;
    Vec3_s00ca_1310* v = FUN_00ca1210(&tmp, seg, t);
    *out = *v;
}

// @ 0x00ca2210
bool cVehicle_s00ca_2210::FUN_00ca2210(void* p)
{
    /* terrain-occupancy scan; not reconstructed */
    (void)p;
    return false;
}

// @ 0x00ca2370
bool cVehicle_s00ca_2210::FUN_00ca2370(void)
{
    /* navigation candidate search (large); not reconstructed */
    return false;
}

// @ 0x00ca28a0
void cVehicle_s00ca_2210::FUN_00ca28a0(void* p)
{
    /* ray / sphere probe; not reconstructed */
    (void)p;
}

// @ 0x00ca2ae0
void SP::cVehicle::CreateDefaultTool()
{
    /* tool selection (large); not reconstructed */
}

// @ 0x00ca2e80
void cVehicle_s00ca_2210::FUN_00ca2e80(void)
{
    void* gm = GetCurrentGameMode();
    bool  flag = (gm == SIM_MODE_ADDR);
    float f;

    switch (mB1c) {
    case 1:
        f = *(float*)0x0169a26c;
        m224 = 6;
        break;
    case 2:
        m224 = 5;
        mToolMgr.FUN_00c43fe0((void*)0x00b493e0);
        if (flag) {
            mAf0->mFlags |= 0x20;
            f = *(float*)0x0157c724;
        } else {
            mAf0->mFlags |= 0x20;
            f = *(float*)0x0169a274;
        }
        break;
    default:
        m224 = 7;
        f = mD04 ? *(float*)0x0169a270 : *(float*)0x0169a268;
        break;
    }

    if (flag) {
        m21c = (*(float*)0x0157c708) * f;
        if (mB1c == 2) {
            cFlyingLocomotion* q = (cFlyingLocomotion*)EAllocNew(0x3c, (const char*)0x01474adc, 0, 0, 0, 0);
            if (q != 0)
                mToolMgr.FUN_00c421b0(q->FUN_00caded0());
            else
                mToolMgr.FUN_00c421b0((void*)0);
            return;
        }
    } else {
        m21c = f;
        cAllocPath* p = (cAllocPath*)EAllocNew(0xd4, (const char*)0x01474ab8, 0, 0, 0, 0);
        if (p != 0) {
            p->mVtbl   = (void*)0x01474a88;
            p->mVtbl8  = (void*)0x01475114;
            p->mField0c = 0;
            p->mOwner  = this;
            p->mType   = mB1c;
            p->mVal18  = 0.0f;
            p->mFlag1c = 0;
            p->mFlag1d = 0;
            mToolMgr.FUN_00c421b0(p);
        } else {
            mToolMgr.FUN_00c421b0((void*)0);
        }
        return;
    }

    cAllocDriving* d = (cAllocDriving*)EAllocNew(0x10, (const char*)0x01474a98, 0, 0, 0, 0);
    if (d != 0) {
        d->mVtbl    = (void*)0x01474a34;
        d->mVtbl8   = (void*)0x01475114;
        d->mField0c = 0;
        mToolMgr.FUN_00c421b0(d);
    } else {
        mToolMgr.FUN_00c421b0((void*)0);
    }
}

// @ 0x00ca3030
Vector3* cGameDataSub::GetGameDataOwner(Vector3* out)
{
    cGameData_s00ca_3030& g = Owner();

    // The base object's own vtable slot +0x2c is consulted first, then the
    // +0x618 mode byte (0 or 1) and the empty point-array check; any of them
    // forwards to the (recursive) owner lookup.
    if (g.mBaseIsSpecial())
        return GetGameDataOwner(out);
    if (g.mSubFlag618 != 0 && g.mSubFlag618 != 1)
        return GetGameDataOwner(out);
    if (g.mPointBegin == g.mPointEnd)
        return GetGameDataOwner(out);

    // The point array is indexed by +0x770, clamped to its length.
    int count = (int)((char*)g.mPointEnd - (char*)g.mPointBegin) / 0x10;
    if (g.mPointIndex >= count)
        g.mPointIndex = 0;

    uint32_t prop = g.mPropertyList;          // base +0xd0's +0x90
    uint32_t start = 0;
    uint32_t array = 0;
    if (!GetPropertyAsTransformArray(prop, 0xf1fae963, &start, &array))
        return GetGameDataOwner2(&g, out);

    int elem = *(int*)(g.mPointBegin + g.mPointIndex * 0x10 + 4);
    if (elem >= (int)start)
        return GetGameDataOwner2(&g, out);

    const void* src = (const void*)(array + elem * 0x38);
    Vector3 v;
    v.x = *(float*)((const char*)src + 4);
    v.y = *(float*)((const char*)src + 8);
    v.z = *(float*)((const char*)src + 0xc);

    cSPTransform_s00ca_3030 transform;
    Transform_Ctor(&transform);

    cSpatialObject_s00ca_3030* sp = &g.mSpatial;
    void* t = sp->GetTransform();
    if (t != 0) {
        AssignTransformOps(&transform, (const char*)t + 8);
    } else {
        LocalToWorldTransform(sp, &transform);
        transform.mScale = sp->GetScale();
        transform.mModificationCount = (uint16_t)(transform.mModificationCount + 1);
    }

    FUN_0044d4f0(&v);
    out->x = v.x;
    out->y = v.y;
    out->z = v.z;
    return out;
}

// @ 0x00ca31f0
void cGameData_s00ca_3030::FUN_00ca31f0()
{
    cWorldDesc* wd = FUN_00b3d370();
    const Vector3* pos = mSpatial.GetPosition();
    if (wd->mFlagAt20 == 0 || pos == 0)
        return;
    uint32_t flags = *(uint32_t*)((char*)pos + 4);
    if (((flags >> 0xe) & 1) == 0)
        return;
    if (((flags >> 0x12) & 1) != 0)
        return;
    if (!mSpatial.GetFlag48())
        return;

    cSPTransform_s00ca_3030 transform;
    Transform_Ctor(&transform);

    const Vector3* p = mSpatial.GetPosition();
    Vector3 normal;
    FUN_00b7e3b0(SP::PlanetModel_s00ca_3030(), &normal, p);

    Vector3 zero;
    zero.x = 0.0f; zero.y = 0.0f; zero.z = 0.0f;
    Vector3 zAxis;
    zAxis.x = 0.0f; zAxis.y = 0.0f; zAxis.z = g_1485720_s00ca_3030;
    MatOwner_SetB(&transform, &zero, &zAxis);

    const Vector3* target;
    if (mSpatialFlag == 0) {
        Vector3 tmp;
        target = DirectionToSurfacePosition(SP::PlanetModel_s00ca_3030(), &tmp, mSpatial.GetPosition());
    } else {
        target = mSpatial.GetPosition();
    }
    Vector3 dst;
    dst.x = target->x; dst.y = target->y; dst.z = target->z;
    transform.mFlags |= 4;
    transform.mModificationCount = (uint16_t)(transform.mModificationCount + 1);
    transform.mTranslation = dst;
    transform.mModificationCount = (uint16_t)(transform.mModificationCount + 1);
    float radius = mSpatial.GetRadius() * g_1486114;
    ((cGroundLayer*)wd)->addInterpolated(&transform, radius);
}

// @ 0x00ca3350
void cGameData_s00ca_3030::FUN_00ca3350(char enable)
{
    cCivModeStrategy_s00ca_3030* civ = (cCivModeStrategy_s00ca_3030*)FUN_00cf74c0();
    if (civ->mFlag148 != 0) {
        if (!((cCivModeStrategy_s00ca_3030*)FUN_00cf74c0())->HasCivTutorialOccurred(0x64e6678))
            return;
    }
    if (enable != 0 && !mSpatial.GetFlag50())
        FUN_00c9f6c0();
    mCivMode = (uint8_t)enable;
    if (enable != 0)
        TryCivModeTutorial();
}

// @ 0x00ca33b0
void cGameData_s00ca_3030::FUN_00ca33b0(const Vector3* p)
{
    mMarkerPos = *p;
    float radius = mSpatial.GetRadius();
    FUN_00c9fb40(p->x, p->y, p->z, 0.0f, radius * g_14853e0);
}

// @ 0x00ca3410
void cSpatialObject_s00ca_3030::FUN_00ca3410(const Vector3* p, float a, float b, char useCam)
{
    cGameData_s00ca_3030& g = cSpatial_Owner(this);
    cNavGoalBlock block;
    unsigned flags = 0;
    if (useCam != 0) {
        const Vector3* c = GetPosition();
        float dx = p->x - c->x;
        float dy = p->y - c->y;
        float dz = p->z - c->z;
        float inv = 1.0f / sqrtf((dx * dx + (dz * dz + dy * dy)) + g_13ec4b8_s00ca_3030);
        Vector3 dir;
        dir.x = dx * inv;
        dir.y = dy * inv;
        dir.z = dz * inv;
        cNavigationGoal_InitToward(&block, p, &dir, a, b);
        flags |= 2;
    } else {
        block.mWord04 = 0;
        block.mWord08 = 0;
        block.mWord0c = 0;
        block.mWord10 = 0;
        block.mDirect.x = p->x;
        block.mDirect.y = p->y;
        block.mDirect.z = p->z;
        block.mWord20 = (uint32_t&)b;
        block.mWord24 = 0;
        block.mWord4c = 0;
        block.mWord50 = 0;
        block.mWord54 = 0;
        block.mWord58 = 0;
        block.mWord5c = 1;
        block.mWord60 = (uint32_t&)a;
        block.mWord64 = (uint32_t&)g_13ec4b4;
        block.mWord68 = (uint32_t&)g_14749a8_s00ca_3030;
        block.mWord6c = 0;
        block.mWord70 = 0;
        flags |= 1;
    }
    SubmitGoal(&block);
    if (flags & 2) {
        flags &= ~2u;
    } else {
        if (block.mpBuffer0 != 0)
            operator delete(block.mpBuffer0);
        if (block.mpBuffer74 != 0)
            operator delete(block.mpBuffer74);
    }
    float scale = g_1485720_s00ca_3030;
    void* mode = GetCurrentGameMode();
    if (mode == (void*)0x01654c10) {
        void* w = FUN_00f3f950((char*)this - 0x34, 0);
        if (w != 0)
            scale = *(float*)((char*)w + 0x490);
    }
    ApplyRadius(g.mCameraScale * scale, 0);
    g.m2a4 = 0;
}

// @ 0x00ca3660
uint8_t cGameData_s00ca_3030::FUN_00ca3660(void* stream)
{
    void* s1 = (*(void*(__thiscall**)(void*))*(void**)stream)(stream);
    void* s2 = (*(void*(__thiscall**)(void*))*(void**)s1)(s1);
    ReadInt32(s2, (int*)&mReadValue);
    uint8_t ok = 0;
    if (cGameData_Read(this, stream)) {
        if (FUN_00bfc540(stream)) {
            if (FUN_00c43c10(&mSpatial, stream))
                ok = 1;
        }
    }
    uint8_t serializer[0x14];
    cVarListSerializer_Ctor(serializer, this, 0, 0);
    uint8_t result = 0;
    if (cVarListSerializer_Read(serializer, stream) && ok)
        result = 1;
    FUN_00ca2e80(this);
    FUN_00dc4b70(this);
    *(uint32_t*)(mpFlagHolder + 0x5fc) &= 0xfffffcff;
    if (mMode == 0)
        *(uint32_t*)(mpFlagHolder + 0x5fc) |= 0x100;
    else if (mMode == 1)
        *(uint32_t*)(mpFlagHolder + 0x5fc) |= 0x200;
    if (mListBegin != mListEnd)
        FUN_00c9f7c0(this);
    return result;
}

// @ 0x00ca42c0
void cOwner::Clear()
{
    if (mpManaged) {
        cInterface* iface = mpManaged->mpInterface;
        ((void (__thiscall*)(cInterface*, cManaged*, int))
            ((void**)iface->mpVtable)[0x16c / 4])(iface, mpManaged, 0);
    }
    if (mpManaged) {
        cManaged* p = mpManaged;
        mpManaged = 0;
        if (p->mRefCount40 > 1) {
            --p->mRefCount40;
        } else {
            cInterface* iface = p->mpInterface;
            unsigned char flag = (unsigned char)((p->mFlags04 >> 31) & 1);
            ((void (__thiscall*)(cInterface*, cManaged*, unsigned char))
                ((void**)iface->mpVtable)[0x170 / 4])(iface, p, flag);
        }
    }
}

// @ 0x00ca4320
bool cVehicle_s00ca4320::FUN_00ca4320(void* param)
{
    if (mpInventoryD94 != 0) {
        ProcessEA();

        cObjectInstanceInventoryItem* item = (cObjectInstanceInventoryItem*)
            operator_new(0x80, "Simulator/cObjectInstanceInventoryItem", 0, 0, 0, 0);
        if (item != 0) {
            item = item->Construct();
            if (item != 0) {
                item->AddRef();
                item->SetOwner(param);
                mpInventoryD94->AddItem(item, 0, 1);

                if (GetCurrentGameMode_s00ca_4320() == 0x1654c10)
                    gpGameGlobal->m_at78->Func(this, param);
                item->Func8();
                return true;
            }
        }
    }

    ((Stimuli*)((char*)mpAF0 + 8))->ClearAll(0x8000, 0);
    return false;
}

// @ 0x00ca4600
void ShiftClosest(RefCounted_s00ca_4600** slot, int pos, Vec4_s00ca_4600 p)
{
    RefCounted_s00ca_4600** it = (RefCounted_s00ca_4600**)pos;

    RefCounted_s00ca_4600* item = it[-1];
    if (item)
        item->AddRef();

    RefCounted_s00ca_4600* current = *slot;
    RefCounted_s00ca_4600* old = it[-1];
    if (current != old) {
        if (current)
            current->AddRef();
        it[-1] = current;
        if (old)
            old->Release();
    }

    InsertClosest(slot, 0, (int)(it - slot) - 1, 0, RefHolder(item), p);
    if (item)
        item->Release();
}

// @ 0x00ca46c0
bool cCameraFollow::Step(const Vector3_s00ca_46c0* pTarget, float dt)
{
    const Vector3_s00ca_46c0* pPos = mpOwner->mState.GetPosition();
    float px = pPos->x, py = pPos->y, pz = pPos->z;
    float dy = pTarget->y - py;
    float dz = pTarget->z - pz;
    float dx = pTarget->x - px;
    float len = (float)sqrt((dy * dy + dz * dz) + dx * dx);
    if (len < 0.01)
        return true;
    float inv = 1.0f / len;
    Vector3_s00ca_46c0 dir;
    dir.x = inv * dx;
    dir.y = dy * inv;
    dir.z = dz * inv;

    Vector3_s00ca_46c0 look;
    mpOwner->mState.GetUpReference(&look);

    float ninv = 1.0f / (float)sqrt(((px * px + pz * pz) + py * py) + 1e-8f);
    Vector3_s00ca_46c0 up;
    up.x = ninv * px;
    up.y = py * ninv;
    up.z = pz * ninv;

    Vector3_s00ca_46c0 right;
    right.x = look.y * up.z - look.z * up.y;
    right.y = look.z * up.x - up.z * look.x;
    right.z = up.y * look.x - look.y * up.x;
    Vector3_s00ca_46c0 fwd;
    fwd.x = right.z * up.y - right.y * up.z;
    fwd.y = up.z * right.x - right.z * up.x;
    fwd.z = right.y * up.x - up.y * right.x;

    Vector3_s00ca_46c0 tmp;
    Vector3_s00ca_46c0 ref = *RotateByQuat(&tmp, &g_AxisPitch, mpOwner->mState.GetOrientation());

    float rate = mMode == 2 ? g_RateA * 2.0f : g_RateA * 4.0f;

    float a0 = WrapSigned(SignedAngle(&fwd, &look, &right));

    float rd = (ref.z * fwd.z + ref.y * fwd.y) + ref.x * fwd.x;
    ref.x = ref.x - rd * fwd.x;
    ref.y = ref.y - rd * fwd.y;
    ref.z = ref.z - rd * fwd.z;
    float a1 = WrapSigned(SignedAngle(&right, &ref, &fwd));

    float a2 = WrapSigned(SignedAngle(&fwd, &look, &up));

    float dd = (up.z * dir.z + up.y * dir.y) + up.x * dir.x;
    dir.x = dir.x - dd * up.x;
    dir.y = dir.y - dd * up.y;
    dir.z = dir.z - dd * up.z;
    float a3 = WrapSigned(SignedAngle(&fwd, &dir, &up));

    float d0 = WrapDelta(ApproachAngle(a0, 0.0f, g_RateB * dt) - a0);
    float d1 = WrapDelta(ApproachAngle(a1, 0.0f, g_RateC * dt) - a1);
    float d2 = WrapDelta(ApproachAngle(a2, a3, rate * dt) - a2);

    const Quaternion* pq = mpOwner->mState.GetOrientation();
    Quaternion q;
    q.x = pq->x; q.y = pq->y; q.z = pq->z; q.w = pq->w;
    if (d2 != 0.0f)
        RotateAbout(q, g_AxisRoll, d2);
    if (d0 != 0.0f)
        RotateAbout(q, g_AxisPitch, d0);
    if (d1 != 0.0f)
        RotateAbout(q, g_AxisYaw, d1);

    float qinv = 1.0f / (float)sqrt(((q.x * q.x + q.w * q.w) + q.z * q.z) + q.y * q.y);
    q.x = qinv * q.x;
    q.w = q.w * qinv;
    q.y = q.y * qinv;
    q.z = q.z * qinv;
    mpOwner->mState.SetOrientation(&q);
    return fabs(a2 - a3) < 0.1f;
}

// @ 0x00ca4f90
void cPathLocomotion::Steer(Vector3_s00ca_4f90 dir, float dt, float speed, int accelSign)
{
    Vector3_s00ca_4f90 facing = mpOwner->mLocomotion.GetFacing();
    const Vector3_s00ca_4f90& pos = mpOwner->mLocomotion.GetPosition();
    float inv = 1.0f / sqrtf(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z + 1e-8f);
    Vector3_s00ca_4f90 up(pos.x * inv, inv * pos.y, inv * pos.z);
    Vector3_s00ca_4f90 right = facing.Cross(up);
    Vector3_s00ca_4f90 forward = up.Cross(right);

    Vector3_s00ca_4f90 heading;
    heading = RotateByQuaternion(kAxisPitch, mpOwner->mLocomotion.GetOrientation());
    float pitch = WrapAngleMod(SignedAngleNormalized(forward, facing, right));
    float roll = WrapAngleMod(SignedAngleNormalized(right, RejectFrom(heading, forward), forward));
    float turn = SignedAngleNormalized(forward, RejectFrom(dir, up), up);

    bool before = mT < mSpanStart;
    bool after = mT > mSpanLength + mSpanStart && mBankAfter > 0.0f;
    float targetRoll = 0.0f;
    if (speed > 0.0f && (before || after) && mpOwner->GetMoveType() != 4) {
        bool bank = before ? mbBankBefore : mbBankAfter;
        targetRoll = kQuarterPi;
        if (!bank)
            targetRoll = -targetRoll;
    }

    float targetPitch = SignedAngleNormalized(forward, RejectFrom(dir, right), right);
    if (mpOwner->GetMoveType() == 5) {
        if (accelSign > 0)
            targetPitch -= kQuarterPi * 0.75f;
        else if (accelSign < 0)
            targetPitch += kQuarterPi * 0.1f;
    }

    float pitchStep = (mpOwner->mbAFC ? gTurnRateScale : 1.0f) * gPitchRate * dt;
    float rollRate = (mpOwner->mbAFC ? gTurnRateScale : 1.0f) * gRollRate;
    pitch = WrapAngle(AngleStepToward(pitch, targetPitch, pitchStep) - pitch);
    roll = WrapAngle(AngleStepToward(roll, targetRoll, rollRate * dt) - roll);

    Quaternion_s00ca_4f90 q = mpOwner->mLocomotion.GetOrientation();
    if (turn != 0.0f)
        q *= AxisAngle(kAxisTurn, turn);
    if (pitch != 0.0f)
        q *= AxisAngle(kAxisPitch, pitch);
    if (roll != 0.0f)
        q *= AxisAngle(kAxisRoll, roll);
    q = q.Normalized();
    mpOwner->mLocomotion.SetOrientation(q);
}

// @ 0x00ca5b10
void cPathLocomotion_s00ca_5b10::Turn(Vector3_s00ca_5b10 dir, float dt)
{
    static float sTurnRate = gTwoPi * 2.0f;   // 0x01699ac0 (guard 0x01699ac4)

    Vector3_s00ca_5b10 facing = mpOwner->mLocomotion.GetFacing();
    const Vector3_s00ca_5b10& pos = mpOwner->mLocomotion.GetPosition();
    float inv = 1.0f / sqrtf(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z + 1e-8f);
    Vector3_s00ca_5b10 up(pos.x * inv, inv * pos.y, inv * pos.z);
    Vector3_s00ca_5b10 right = facing.Cross(up);
    Vector3_s00ca_5b10 forward = up.Cross(right);

    Vector3_s00ca_5b10 heading;
    heading = RotateByQuaternion(kAxisPitch_s00ca_5b10, mpOwner->mLocomotion.GetOrientation());
    float pitch = WrapAngleMod_s00ca_5b10(SignedAngleNormalized(forward, facing, right));
    float roll = WrapAngleMod_s00ca_5b10(SignedAngleNormalized(right, RejectFrom_s00ca_5b10(heading, forward), forward));
    float turn = WrapAngleMod_s00ca_5b10(SignedAngleNormalized(forward, facing, up));

    Vector3_s00ca_5b10 pathPos, pathDir;
    Evaluate(mPath, mT + 16.0f, &pathPos, &pathDir);
    float targetTurn = WrapAngleMod_s00ca_5b10(SignedAngleNormalized(forward, RejectFrom_s00ca_5b10(pathDir, up), up));

    pitch = WrapAngle_s00ca_5b10(AngleStepToward(pitch, 0.0f, gPitchRate * dt) - pitch);
    roll = WrapAngle_s00ca_5b10(AngleStepToward(roll, 0.0f, gRollRate * dt) - roll);
    turn = WrapAngle_s00ca_5b10(AngleStepToward(turn, targetTurn, sTurnRate * dt) - turn);

    Quaternion_s00ca_5b10 q = mpOwner->mLocomotion.GetOrientation();
    if (turn != 0.0f)
        q *= AxisAngle_s00ca_5b10(kAxisTurn_s00ca_5b10, turn);
    if (pitch != 0.0f)
        q *= AxisAngle_s00ca_5b10(kAxisPitch_s00ca_5b10, pitch);
    if (roll != 0.0f)
        q *= AxisAngle_s00ca_5b10(kAxisRoll_s00ca_5b10, roll);
    q = q.Normalized();
    mpOwner->mLocomotion.SetOrientation(q);
}

// @ 0x00ca6db0
void __fastcall FUN_00ca6db0(Self6db0* self)
{
    int* game = (int*)G_GAME_DATA;
    int* settings = *(int**)((char*)game + 0x78);
    int count = *(int*)((char*)settings + 0xb8);

    ObjectAt508* sub = &self->mSub34;
    void* result = ((void* (__thiscall*)(ObjectAt508*))sub->mpVtbl[0x2c / 4])(sub);
    FUN_00d9a290(count, self->mp18, result, self->mpB00);

    char* status = (char*)((ExtObj*)(*(int**)((char*)game + 0x74)))->Get74(self);
    ((ExtObj*)((char*)self + 0x508))->SetByte((unsigned char)status[1]);

    count = *(int*)((char*)(*(int**)((char*)game + 0x78)) + 0xb8);
    if (count > 0) {
        char* data = (char*)((ExtObj*)self)->GetData();
        if (((ExtObj*)status)->Test(count * 0x4e0 - 0x4e0 + *(int*)(data + 0x70)))
            ((ExtObj*)((char*)self->mpAf0 + 8))->SetFlags(1, 0,
                                                         *(float*)0x014749a8, 0);
    }

    unsigned* flags = (unsigned*)((char*)self->mpAf0 + 0x5fc);
    *flags &= 0xffff83ff;
    switch (*(int*)(status + 0x4ac)) {
    case 1: *flags |= 0x2000; break;
    case 2: *flags |= 0x0800; break;
    case 3: *flags |= 0x1000; break;
    case 4: *flags |= 0x4000; break;
    case 5: *flags |= 0x0400; break;
    }

    ((void (__thiscall*)(ObjectAt508*))sub->mpVtbl[0xf4 / 4])(sub);
    self->m2a0 = *(float*)(status + 0x484);
    result = ((void* (__thiscall*)(ObjectAt508*))sub->mpVtbl[0x2c / 4])(sub);
    ((ExtObj*)self)->SetA(result);
    self->mAfC = 1;
}

// @ 0x00ca6f20
int* __fastcall FUN_00ca6f20(char* self)
{
    int zero = 0;

    if (*(int*)(self + 0x550) != zero) {
        int one = 1;
        if ((g_list_a_flags & one) == 0) {
            g_list_a_flags |= one;
            g_list_a_data[0] = zero;
            g_list_a_data[1] = zero;
            g_list_a_data[2] = zero;
            atexit(FUN_013c4400);
        }
        return g_list_a_data;
    }
    return &g_list_a_alt;
}

// @ 0x00ca6f70
unsigned __fastcall FUN_00ca6f70(BlockList* self)
{
    unsigned* cur = self->mpCur;
    if (cur == self->mpLimit)
        return 0;

    unsigned value = *cur;
    if (cur + 1 != self->mpEnd) {
        self->mpCur = cur + 1;
        return value;
    }

    if (self->mpBlock != 0)
        FUN_00f47380(self->mpBlock);

    int* next = self->mpBlockPtr + 1;
    self->mpBlockPtr = next;
    int block = *next;
    self->mpBlock = (int*)block;
    self->mpEnd = (unsigned*)(block + 0x100);
    self->mpCur = (unsigned*)block;
    return value;
}

// @ 0x00ca6ff0
void Self6ff0::FUN_00ca6ff0(void* arg)
{
    if (mTimer1.GetElapsedTime() > 1000) {
        MessageBasicRC5 msg;
        msg.mpVtbl = (void*)0x013eb90c;
        msg.mRefCount = 0;
        msg.mpVtbl = (void*)0x013eb844;
        msg.mRCFlags = 0;
        msg.mId = 0x354b9e8;
        msg.mData0 = this;
        msg.mData1 = 0xffff0000;

        void* server = FUN_00883860();
        ((void (__thiscall*)(void*, unsigned, MessageBasicRC5*, int))
         (*(void***)server)[0x14 / 4])(server, msg.mId, &msg, 0);

        mTimer1.Restart();
        mBcc = 1;
        FUN_00421cf0(&msg);
    }

    if (FUN_00b5b800() == (void*)0x01654c10) {
        if ((*(unsigned*)((char*)mpAf0 + 0x5fc) & 0x3000) == 0)
            return;
        if (mTimer2.GetElapsedTime() <= 10000)
            return;

        mTimer2.Restart();
        unsigned audio = 0;
        void* sys = FUN_00a206f0();
        if (sys)
            audio = ((unsigned (__thiscall*)(void*))(*(void***)sys)[0x20 / 4])(sys);
        FUN_00435ed0(((void**)0x01474b10)[mB20], audio);
        return;
    }

    char active = ((char (__thiscall*)(ObjectAt508*))
                   mSub34.mpVtbl[0x58 / 4])(&mSub34);
    if (!active)
        return;
    if (mTimer2.GetElapsedTime() <= 60000)
        return;

    mTimer2.Restart();
    if (arg != 0) {
        void* obj = ((void* (__thiscall*)(void*, void*))
                     (*(void***)arg)[0x5c / 4])(arg, (void*)0x0137e8e0);
        if (obj != 0 && *(int*)((char*)obj + 0xb20) == 1) {
            unsigned state = FUN_00435e90();
            FUN_00435ed0(((void**)0x01474b04)[mB20], state);
            return;
        }
    }

    unsigned audio = 0;
    void* sys = FUN_00a206f0();
    if (sys)
        audio = ((unsigned (__thiscall*)(void*))(*(void***)sys)[0x20 / 4])(sys);
    FUN_00435ed0(((void**)0x01474af8)[mB20], audio);
}

// @ 0x00ca71d0
void* __fastcall FUN_00ca71d0(Object71d0* self)
{
    int one = 1;
    if ((g_list_b_flags & one) == 0) {
        g_list_b_flags |= one;
        g_list_b_cell = 0;
        atexit(FUN_013c4420);
    }

    void* cur = self->mpCur;
    if (cur != self->mpEnd)
        return cur;

    void* old = g_list_b_cell;
    if (old != 0) {
        g_list_b_cell = 0;
        void** vtbl = *(void***)old;
        ((void (__thiscall*)(void*))vtbl[1])(old);
    }

    g_list_b_zero = 0;
    void* result = ((void* (__thiscall*)(void*))
                    (*(void***)((char*)self + 0x508))[4])((char*)self + 0x508);
    g_list_b_result = result;
    return &g_list_b_cell;
}

// @ 0x00ca7250
void StringOwner::FUN_00ca7250(char* text)
{
    if (text != 0) {
        char* end = text + strlen(text);
        ((EastlString*)&mString)->Assign(text, end);
    } else {
        ((EastlString*)&mString)->Assign((const char*)g_13ec47c,
                                         (const char*)g_13ec47c);
    }
}

// @ 0x00ca72a0
void __fastcall FUN_00ca72a0(Self72a0* self)
{
    ObjectAt508* sub = &self->mSub34;
    float* p = ((float* (__thiscall*)(ObjectAt508*))
                self->mSub34.mpVtbl[0x2c / 4])(sub);
    Vec3_s00ca_6630 here = { p[0], p[1], p[2] };

    if (FUN_00c9e8e0(self->mB1c, &here))
        return;

    cActionCircle circle;
    circle.Construct();

    Vec3_s00ca_6630 scratch;
    circle.SetAtCenter(&here, g_1400a58,
        ((Vec3_s00ca_6630* (__thiscall*)(ObjectAt508*, Vec3_s00ca_6630*))
         sub->mpVtbl[0x5c / 4])(sub, &scratch),
        0.0f);

    float radius = ((float (__thiscall*)(ObjectAt508*))
                    sub->mpVtbl[0x70 / 4])(sub);
    circle.SetSlotRadius(0, radius);

    int count = (int)(circle.mSlots.mpEnd - circle.mSlots.mpBegin);
    for (int i = 0; i < count; ++i) {
        Vec3_s00ca_6630& sp = circle.mSlots.mpBegin[i].mPos;
        scratch.x = sp.x;
        scratch.y = sp.y;
        scratch.z = sp.z;
        int kind = self->mB1c;
        unsigned int mask = GetPlanetModel()->GetAverageRadius(&scratch);
        bool ok = true;
        switch (kind) {
        case 0: ok = (mask & 0x98000000) == 0; break;
        case 1: ok = (mask & 0x58000000) == 0; break;
        case 2: ok = ((mask >> 29) & 1) == 0; break;
        default: break;
        }
        if (!ok)
            continue;
        ((void (__thiscall*)(ObjectAt508*, Vec3_s00ca_6630*))
         sub->mpVtbl[0x38 / 4])(sub, &scratch);
        circle.Destroy();
        return;
    }

    Noun* noun = (Noun*)SP_NounManager()->FindNoun(
        ((unsigned int (__thiscall*)(ObjectAt508*))
         self->m508.mpVtbl[0x10 / 4])(&self->m508));
    if (noun != 0) {
        NounContainer* container = noun->GetContainer();
        if (container->mpBegin != container->mpEnd) {
            bool flag = false;
            NounContainer* slots = noun->GetContainer();
            cCity* city = (cCity*)FUN_00ac9310(slots, &here, flag);
            here = *city->GetVehicleSpawnPoint(&scratch, self->mB1c);
            if (here.x != g_01699b08 ||
                here.y != g_01699b0c ||
                here.z != g_01699b10)
                ((void (__thiscall*)(ObjectAt508*, Vec3_s00ca_6630*))
                 sub->mpVtbl[0x38 / 4])(sub, &here);
        }
    }

    circle.Destroy();
}

// @ 0x00ca7520
void SpatialObject::FUN_00ca7520(ModelKey* key)
{
    switch (key->mMagic) {
    case 0x24682294:
    case 0x476a98c7:
        ((ExtObj*)((char*)this - 0x34))->ClearCreature();
        mpProfile = 0;
        ((ExtObj*)this)->SetModelKey(key);
        return;

    case 0x2b978c46: {
        void* profile = ((ExtObj*)FUN_00401090())->GetProfile(key);
        mpProfile = profile;
        if (profile == 0)
            return;
        SpatialObject* base = (SpatialObject*)((char*)this - 0x34);
        ((ExtObj*)base)->ClearCreature();
        ((ExtObj*)base)->ResetModel();
        ((ExtObj*)base)->ResetCreature();
        return;
    }
    }
}

// @ 0x00ca75e0
void* __cdecl FUN_00ca75e0(cListArchive* mgr, UIntDeque* q)
{
    q->FUN_00996460();
    uint32_t count;
    count = 0;
    void* s0 = mgr->v20();
    void* stream0 = ((cListArchive*)s0)->v18();
    FUN_0093a780(stream0, &count, 1, 0);
    for (uint32_t k = 0; k < count; ++k) {
        void* s1 = mgr->v20();
        void* stream1 = ((cListArchive*)s1)->v18();
        uint32_t v;
        FUN_0093a780(stream1, &v, 1, 0);
        q->push_back(v);
    }
    return mgr->v1c();
}

// @ 0x00ca7690
void __cdecl FUN_00ca7690(cListArchive* a, void** vec)
{
    uint32_t n = (uint32_t)(((char*)vec[1] - (char*)vec[0]) >> 2);
    void* s0 = a->v20();
    void* stream0 = ((cListArchive*)s0)->v18();
    FUN_0093aa70(stream0, &n, 1, 0);
    void** p = (void**)vec[0];
    void** e = (void**)vec[1];
    for (; p != e; ++p) {
        void* elem = *p;
        uint32_t r = 0;
        if (elem)
            r = ((uint32_t(__thiscall*)(void*, int))VF(elem, 0x5c / 4))(elem, 0x179c807);
        a->v2c((void*)r);
    }
    a->v1c();
}

struct RefObj_ca77 {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v0a();
    virtual void v0b();
    virtual void v0c();
    virtual void v0d();
    virtual void v0e();
    virtual void v0f();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void AddRef();     // +0x60
};
struct RefPtr_ca77 {
    RefObj_ca77* p;
    __forceinline RefPtr_ca77(const RefPtr_ca77& o) : p(o.p) { if (p) p->AddRef(); }
};
struct Vec4c_ca77 {
    float x, y, z, w;
    __forceinline Vec4c_ca77(const cSPVector4_s00ca_75e0& o) : x(o.x), y(o.y), z(o.z), w(o.w) {}
};
extern "C" void  __cdecl FUN_00ca44f0(void* begin, int i, int n, int i2, RefPtr_ca77 val, Vec4c_ca77 v);   // 0x00ca44f0 heap sift-down

// @ 0x00ca77b0
void __cdecl FUN_00ca77b0(char* begin, char* end, cSPVector4_s00ca_75e0 v)
{
    int n = (int)((end - begin) >> 2);
    if (n < 2)
        return;
    int i = ((n - 2) >> 1) + 1;
    do {
        --i;
        FUN_00ca44f0(begin, i, n, i, ((RefPtr_ca77*)begin)[i], v);
    } while (i != 0);
}

extern "C" void  __cdecl FUN_00ca4600(void* begin, void* end, Vec4c_ca77 v);                           // 0x00ca4600 heap pop

// @ 0x00ca7830
void __cdecl FUN_00ca7830(char* begin, char* end, cSPVector4_s00ca_75e0 v)
{
    void** first = (void**)begin;
    for (void** last = (void**)end; (last - first) > 1; --last)
        FUN_00ca4600(first, last, v);
}

// @ 0x00ca78a0
Simulator::cVehicle_s00ca_75e0::cVehicle_s00ca_75e0()
{
    ((Opaque*)&mpVtbl000)->FUN_00b18660();
    ((Opaque*)&mpVtbl034)->FUN_00c43860();
    ((Opaque*)&mpVtbl508)->FUN_00bfd4e0();
    ((Opaque*)&mpVtbl5D0)->FUN_00abfe50();
    ((Opaque*)&mpVtbl638)->FUN_00ac03d0();
    ((Opaque*)&mBase650)->FUN_00c7d700();

    mpVtbl508  = (void**)0x1474d60;
    mpVtbl034  = (void**)0x1474c60;
    mpVtbl000  = (void**)0x1474c08;
    mpVtbl004  = (void**)0x1474bf8;
    mpVtbl108  = (void**)0x1474bf0;
    mpVtbl5D0  = (void**)0x1474b88;
    mpVtbl638  = (void**)0x1474b6c;
    mBase650.mpVtbl = (void**)0x1474b54;

    mPaf0 = 0;
    mBaf4 = 0;
    mUaf8 = 0;
    mBafc = 0;
    mUb00 = 0;
    mUb04 = 0;
    mIb08 = 1;
    mFb0c = 0.0f;
    mFb10 = 0.0f;
    mFb14 = 0.0f;
    mFb18 = g_01473c70;
    mIb1c = 0;
    mUb20 = 0;
    mUb24 = 0;
    mUb28 = 0;

    ((OpaqueInit*)&mEvents)->FUN_00ca09f0(0);

    mFb58 = 0.0f;
    mPb5c = 0;
    mPb60 = 0;
    mPb64 = 0;
    mContainerB68.m[0] = 0;
    mContainerB68.m[1] = 0;
    mContainerB68.m[2] = 0;
    mPb7c = 0;
    mFb80 = g_01699b08;
    mFb84 = g_01699b0c;
    mFb88 = g_01699b10;
    mB8C.m[0] = 0;
    mB8C.m[1] = 0;
    mB8C.m[2] = 0;

    mTimerBA0.FUN_00b63890();
    mPbc0 = 0;
    mIbc4 = 1;
    mUbc8 = 0;
    mBcc[0] = 0; mBcc[1] = 0; mBcc[2] = 0;
    mBcc[3] = 0; mBcc[4] = 0; mBcc[5] = 0;

    mTimerBD8.FUN_00b63890();
    mTimerBF8.FUN_00b63890();
    mTimerC18.FUN_00b63890();

    mFc48 = 0.0f;
    mFc4c = 0.0f;
    mFc50 = g_013ef568;
    mFc54 = g_013ef568;
    mFc58 = g_013ef568;
    mUc38 = 0;
    mFc5c = g_01485720;
    mFc60 = g_01485720;
    mContainerC64.m[0] = 0;
    mContainerC64.m[1] = 0;
    mContainerC64.m[2] = 0;
    mUc78 = 0;
    mUc7c = 0x7d0;
    mUc80 = 0x7d0;
    mUc84 = 0;

    mTimerC88.FUN_00b63890();
    mTimerCA8.FUN_00b63890();

    mName.mpBegin = &g_01667bac;
    mName.mpEnd = &g_01667bac;
    mName.mpCapacity = &g_01667bae;

    mTimerCD8.FUN_00b63890();

    mPcfc = 0;
    mPd00 = 0;
    mUd04 = 0;
    mUd08 = 0;
    mUd0c = 0;
    mBd10 = 0;

    mWd14.mpBegin = &g_01667bac;
    mWd14.mpEnd = &g_01667bac;
    mWd14.mpCapacity = &g_01667bad;

    mUd24 = 0;
    mFd2c = 0.0f;
    mId30 = 3;
    mVecD34.x = g_01699b08; mVecD34.y = g_01699b0c; mVecD34.z = g_01699b10;
    mVecD40.x = g_01699b08; mVecD40.y = g_01699b0c; mVecD40.z = g_01699b10;
    mVecD4C.x = g_01699b08; mVecD4C.y = g_01699b0c; mVecD4C.z = g_01699b10;
    mVecD58.x = g_01699b08; mVecD58.y = g_01699b0c; mVecD58.z = g_01699b10;
    mUd64 = 0;
    mFd8c = 0.0f;
    mFd90 = 0.0f;
    mFd68 = g_01485720;
    mUd6c = 0; mUd70 = 0; mUd74 = 0; mUd78 = 0;
    mUd7c = 0; mUd80 = 0; mUd84 = 0; mUd88 = 0;
    mPd94 = 0;
    mF218 = g_01470f1c;
    mI088 = 7;
    mF540 = g_013eb1bc;

    void* p = FUN_00f473a0(0x670, "Simulator/cBehaviorTreeData", 0, 0, 0, 0);
    mPaf0 = p ? ((OrderMgr*)p)->FUN_00bcb2a0() : 0;

    mB511 = 1;

    const wchar_t* nm = L"UNINITIALIZED VEHICLE NAME";
    const wchar_t* nme = nm;
    while (*nme)
        ++nme;
    mName.FUN_00423650(nm, nme);
}

// @ 0x00ca7ef0
Simulator::cVehicle_s00ca_75e0::~cVehicle_s00ca_75e0()
{
    void* order = mPaf0;

    mpVtbl000 = (void**)0x1474c08;
    mpVtbl004 = (void**)0x1474bf8;
    mpVtbl034 = (void**)0x1474c60;
    mpVtbl108 = (void**)0x1474bf0;
    mpVtbl508 = (void**)0x1474d60;
    mpVtbl5D0 = (void**)0x1474b88;
    mpVtbl638 = (void**)0x1474b6c;
    mBase650.mpVtbl = (void**)0x1474b54;

    if (order) {
        ((OrderMgr*)order)->FUN_00bcae90();
        FUN_00f47380(order);
    }

    void* pD94 = mPd94;
    if (pD94)
        ((void(__thiscall*)(void*))VF(pD94, 1))(pD94);

    if (mWd14.mpBegin
        && (int)((char*)mWd14.mpCapacity - (char*)mWd14.mpBegin) > 1)
        FUN_00f47380(mWd14.mpBegin);

    if (mPd00)
        ((void(__thiscall*)(void*))VF((char*)mPd00, 0))(mPd00);  // SP::cAnimatingCreature::Release

    void* pCfc = mPcfc;
    if (pCfc)
        ((void(__thiscall*)(void*))VF(pCfc, 1))(pCfc);

    mTimerCD8.FUN_00b638b0();

    if (mName.mpBegin
        && (int)(((char*)mName.mpCapacity - (char*)mName.mpBegin) & ~1u) > 2)
        FUN_00f47380(mName.mpBegin);

    mTimerCA8.FUN_00b638b0();
    mTimerC88.FUN_00b638b0();
    ((Opaque*)&mContainerC64)->FUN_00ca43e0();
    mTimerC18.FUN_00b638b0();
    mTimerBF8.FUN_00b638b0();
    mTimerBD8.FUN_00b638b0();

    void* pBc0 = mPbc0;
    if (pBc0)
        ((void(__thiscall*)(void*))VF(pBc0, 1))(pBc0);

    mTimerBA0.FUN_00b638b0();
    ((Opaque*)&mB8C)->FUN_00ae6930();

    void* pB7c = mPb7c;
    if (pB7c)
        ((void(__thiscall*)(void*))VF(pB7c, 0xc0 / 4))(pB7c);

    ((Opaque*)&mContainerB68)->FUN_00ca75a0();

    if (mPb64)
        ((void(__thiscall*)(void*))VF(mPb64, 2))(mPb64);
    if (mPb60)
        ((void(__thiscall*)(void*))VF(mPb60, 2))(mPb60);
    if (mPb5c)
        ((void(__thiscall*)(void*))VF(mPb5c, 1))(mPb5c);

    mEvents.FUN_0098b5e0();
    ((Opaque*)&mBase650)->FUN_00c7d650();
    ((Opaque*)&mpVtbl638)->FUN_00ac0520();
    ((Opaque*)&mpVtbl5D0)->FUN_00abfec0();
    ((Opaque*)&mpVtbl508)->FUN_00bfcd00();
    ((Opaque*)&mpVtbl034)->FUN_00c432e0();

    ((Opaque*)&mpVtbl000)->FUN_00b184c0();
}

// @ 0x00ca80e0
void Simulator::cVehicle_s00ca_75e0::FUN_00ca80e0(uint32_t v)
{
    mEvents.push_back(v);
}

// @ 0x00ca8120
void Simulator::cVehicle_s00ca_75e0::ContinueAngryCrowdAttack(bool force)
{
    if (mTimerBF8.FUN_00feba90() || force) {
        mTimerBF8.FUN_00bc3130();
        mEvents.push_back(0x1a);
    }
}

// @ 0x00ca8180
void Simulator::cVehicle_s00ca_75e0::EndAngryCrowdAttack()
{
    mTimerBF8.FUN_00bc3110();
    mEvents.push_back(0x1b);
}

// @ 0x00ca81d0
void Simulator::cVehicle_s00ca_75e0::FUN_00ca81d0(cSPVector3_s00ca_75e0* a, float b, float c, int d)
{
    typedef cSPVector3_s00ca_75e0* (__thiscall *GetPosFn)(void*);
    FUN_00ca72a0();

    cSPVector3_s00ca_75e0* pos = ((GetPosFn)VF(&mpVtbl034, 0x2c / 4))(&mpVtbl034);
    mVec1DC = *pos;
    mVec1E8 = *a;
    mF1F4 = b;
    mF1F8 = c;
    mI2A4 = 4;
    mVecD34 = *a;

    void* p = ((void*(__thiscall*)(void*, uint32_t))VF(this, 0xc / 4))(this, 0x17f243b);
    if (p) {
        FUN_01021300();
        ((void(__thiscall*)(void*))VF(p, 0x4c / 4))(p);
    }

    const wchar_t* nm;
    switch (mIb1c) {
    case 1:  nm = g_01565b2c; break;
    case 2:  nm = g_01565b40; break;
    default: nm = g_01565b54; break;
    }

    if (d)
        ((void(__thiscall*)(void*, float, int))VF(&mpVtbl034, 0xc4 / 4))(&mpVtbl034, 0.0f, 0);

    typedef void* (__thiscall *Slot2CFn)(void*, const cSPVector3_s00ca_75e0*, float, float, void*, void*, int, uint32_t);
    void* r = ((Slot2CFn)VF(&mpVtbl034, 0x2c / 4))(
        &mpVtbl034, a, b, c, &mU4EC, &mpVtbl108, (mUbc8 == 1) ? 1 : 0, mUd24);

    void* r2 = FUN_00b3d290((void*)nm, r);
    ((RcObj*)r2)->FUN_00ac65d0();

    mUbc8 = 0;
    mTimerBA0.FUN_00bc3110();
}

// @ 0x00ca8340
bool Simulator::cVehicle_s00ca_75e0::FUN_00ca8340(cCity_s00ca_75e0* city)
{
    typedef cSPVector3_s00ca_75e0* (__thiscall *GetPosFn)(void*);

    cPlanetModel_s00ca_75e0* pm = FUN_00b3d350_s00ca_75e0();
    if (!pm)
        return false;

    cSPVector3_s00ca_75e0* pos = ((GetPosFn)VF(&mpVtbl034, 0x2c / 4))(&mpVtbl034);
    uint8_t* cont = (uint8_t*)pm->FUN_00b88590(pos);

    int mode = mIb1c;
    if (mode == 0) {
        if (cont[pm->mI64] == 0) {
            FUN_00ca72a0();
            pos = ((GetPosFn)VF(&mpVtbl034, 0x2c / 4))(&mpVtbl034);
            cont = (uint8_t*)pm->FUN_00b88590(pos);
        }
        return cont == city->FUN_00bd8210();
    }
    if (mode == 1) {
        if (cont[pm->mI64] != 0) {
            FUN_00ca72a0();
            pos = ((GetPosFn)VF(&mpVtbl034, 0x2c / 4))(&mpVtbl034);
            cont = (uint8_t*)pm->FUN_00b88590(pos);
        }
        cSPVector3_s00ca_75e0* cp = city->FUN_00fa0e00();
        if (cp->x == g_01699b08 && cp->y == g_01699b0c && cp->z == g_01699b10)
            return false;
        if (FUN_00b5b800() != &g_01654c04)
            return cont == pm->FUN_00b88590(city->FUN_00fa0e00());
        return true;
    }
    if (mode == 2)
        return true;
    return false;
}

// @ 0x00ca8470
bool __cdecl FUN_00ca8470(cListArchive* a, int key, UIntDeque* d)
{
    if (d->mItBegin.mpCurrent == d->mItEnd.mpCurrent)
        return true;

    eWstring name;
    buildListName(&name, key);
    const wchar_t* nm = (name.mpBegin == name.mpEnd) ? L"list" : (const wchar_t*)name.mpBegin;
    a->v00(nm);

    bool flag = true;
    uint32_t* cur = d->mItBegin.mpCurrent;
    uint32_t* blkEnd = d->mItBegin.mpEnd;
    uint32_t** blk = d->mItBegin.mpCurrentArrayPtr;
    uint32_t* end = d->mItEnd.mpCurrent;
    while (cur != end) {
        flag = (flag != 0);
        ++cur;
        if (cur == blkEnd) {
            ++blk;
            uint32_t* nb = *blk;
            cur = nb;
            blkEnd = nb + 64;
        }
    }

    a->v04(nm);
    freeName(&name);
    return flag;
}

// @ 0x00ca85c0
bool __cdecl FUN_00ca85c0(cListArchive* a, int key, void** v)
{
    if (v[0] == v[1])
        return true;

    eWstring name;
    buildListName(&name, key);
    const wchar_t* nm = (name.mpBegin == name.mpEnd) ? L"list" : (const wchar_t*)name.mpBegin;
    a->v00(nm);

    bool ok = true;
    char* p = (char*)v[0];
    char* e = (char*)v[1];
    for (; p != e; p += 0x18) {
        if (ok)
            ok = FUN_00ac8050(a, 0, p) != 0;
    }

    a->v04(nm);
    freeName(&name);
    return ok;
}

// @ 0x00ca8710
bool ValidateDebugList(DebugListOwner* owner, const char* name, DebugRange* range)
{
    bool ok = true;
    if (range->mpBegin != range->mpEnd) {
        wchar_t buffer[0x100];
        WideString converted(name ? ConvertToString16(buffer, name, -1) : L"");
        const wchar_t* displayName = converted.empty() ? L"list" : converted.c_str();
        owner->BeginList(displayName);
        for (DebugItem* it = range->mpBegin; it != range->mpEnd; ++it)
            ok = ok && CheckDebugListItem(owner, 0, it);
        owner->EndList(displayName);
    }
    return ok;
}

// @ 0x00ca89b0
void UpdateClosest(RefCounted** slot, RefCounted** begin, RefCounted** end, Vec4 p)
{
    SortClosestBegin(slot, begin, p);
    for (RefCounted** it = begin; it < end; ++it) {
        if (!p.Closer(*it, *slot))
            continue;
        RefCounted* item = *it;
        if (item)
            item->AddRef();
        RefCounted* current = *slot;
        if (current != item) {
            if (current)
                current->AddRef();
            *it = current;
            if (item)
                item->Release();
        }
        if (item)
            item->AddRef();
        InsertClosest(slot, 0, (int)(begin - slot), 0, item, p);
        if (item)
            item->Release();
    }
    SortClosestEnd(slot, begin, p);
}

// @ 0x00ca8b10
void cPathLocomotion_s00ca_8710::Update(LocoUpdateParams* params)
{
    LocoGoal* goal = mpOwner->mLocomotion.GetGoal();
    if (mMode == 1 && PlanetModel_s00ca_8710()->mbF0)
        return;

    if ((mpOwner->mFlags & 4) && mpOwner->mLocomotion.GetMaxSpeed() == 0.0f) {
        mpOwner->mbStopped = true;
        params->mVelocity = kZeroVector;
        return;
    }

    bool active = goal->mMode != 0;
    if (mbRestart) {
        mbWaiting = false;
        if (active) {
            if (mMode == 1)
                StartPathMode1(goal);
            else if (mMode == 2)
                StartPathMode2(goal);
            if (1.5258789e-05f > mSpeed &&
                (mpOwner->GetMoveType() == 5 || mpOwner->GetMoveType() == 1 || mpOwner->GetMoveType() == 6)) {
                mbWaiting = true;
            } else if (!NextSegment()) {
                mpOwner->mLocomotion.OnPathFailed();
                mpOwner->mFlags |= 8;
                active = false;
            }
        } else {
            mpOwner->ExecutePath();
        }
        mbRestart = false;
    }

    if (!active) {
        mSpeed = 0.0f;
        params->mVelocity = kZeroVector;
        mpOwner->mbStopped = active;
        if (mMode == 2) {
            Vector3_s00ca_8710 pos = mpOwner->mLocomotion.GetPosition();
            float len = sqrtf(pos.z * pos.z + pos.y * pos.y + pos.x * pos.x + 1e-8f);
            float inv = 1.0f / len;
            float nx = inv * pos.x;
            float ny = pos.y * inv;
            float nz = pos.z * inv;
            float radius, other;
            mpOwner->GetOrbit(&pos, &radius, &other);
            float invDt = 1.0f / params->mDeltaTime;
            params->mVelocity.x = (nx * radius - pos.x) * invDt;
            params->mVelocity.y = (ny * radius - pos.y) * invDt;
            params->mVelocity.z = (nz * radius - pos.z) * invDt;
            Vector3_s00ca_8710 n(nx, ny, nz);
            Vector3_s00ca_8710 a = mpOwner->mLocomotion.GetFacing().Cross(n);
            Vector3_s00ca_8710 b = n.Cross(a);
            float s = 1.0f / sqrtf(b.x * b.x + b.y * b.y + b.z * b.z + 1e-8f);
            Steer(Vector3_s00ca_8710(s * b.x, s * b.y, s * b.z), params->mDeltaTime, 0.0f, 0);
        }
        return;
    }

    if (mbWaiting) {
        if (!WaitAtWaypoint(&goal->mCurrent, params->mDeltaTime)) {
            params->mVelocity = kZeroVector;
            return;
        }
        mbWaiting = false;
        if (!NextSegment()) {
            mpOwner->mLocomotion.OnPathFailed();
            mpOwner->mFlags |= 8;
        }
    }

    float remaining = params->mDeltaTime;
    Vector3_s00ca_8710 pos = kZeroVector;
    Vector3_s00ca_8710 dir = kDefaultFacing;
    float accel = mpOwner->mLocomotion.GetMaxAcceleration();
    int accelSign = 0;
    float t = mT;
    float targetSpeed;
    if (mSpanStart > t || t > mSpanLength + mSpanStart)
        targetSpeed = mSpeedOffSpan;
    else
        targetSpeed = mSpeedOnSpan;

    if (goal->mpBegin == goal->mpEnd) {
        float distLeft = mPathEnd - t;
        float brakeDist;
        if (mpOwner->mbAFC)
            brakeDist = targetSpeed / accel * targetSpeed * 0.5f;
        else
            brakeDist = accel * 0.25f;
        if (brakeDist > distLeft) {
            float speed = Clamp(distLeft / brakeDist, 0.0f, 1.0f) * targetSpeed;
            if (!mpOwner->mbAFC) {
                float lo, hi;
                if (targetSpeed > 5.0f) {
                    lo = 5.0f;
                    hi = targetSpeed;
                } else {
                    lo = targetSpeed;
                    hi = 5.0f;
                }
                speed = Clamp(speed, lo, hi);
            }
            targetSpeed = speed;
        }
    }

    mpOwner->mbStopped = ShouldStop(params->mDeltaTime);
    if (mpOwner->mbStopped)
        targetSpeed = 0.0f;

    float speed = mSpeed;
    if (targetSpeed > speed) {
        float next = params->mDeltaTime * accel + speed;
        mSpeed = Min(next, targetSpeed);
        accelSign = 1;
    } else if (speed > targetSpeed) {
        float next = speed - params->mDeltaTime * accel;
        mSpeed = Max(next, targetSpeed);
        accelSign = -1;
    }

    while (remaining > 0.0f) {
        float end = mPathEnd;
        float nextT = params->mDeltaTime * mSpeed + mT;
        if (end > nextT) {
            Evaluate(mPath, nextT, &pos, &dir);
            mT = nextT;
            break;
        }
        remaining -= (end - mT) / mSpeedOnSpan;
        mT = end;
        Evaluate(mPath, end, &pos, &dir);
        if (goal->mpBegin == goal->mpEnd) {
            mpOwner->mLocomotion.OnPathFailed();
            break;
        }
        Waypoint* first = goal->mpBegin;
        goal->mCurrent = *first;
        goal->erase(first);
        if (!NextSegment()) {
            mpOwner->mLocomotion.OnPathFailed();
            break;
        }
    }

    const Vector3_s00ca_8710& cur = mpOwner->mLocomotion.GetPosition();
    float dt = params->mDeltaTime;
    float invDt = 1.0f / dt;
    Vector3_s00ca_8710 velocity(invDt * (pos.x - cur.x), invDt * (pos.y - cur.y), invDt * (pos.z - cur.z));
    params->mVelocity = velocity;

    switch (mMode) {
    case 0:
        if (mpOwner->GetMoveType() == 6) {
            mpOwner->mLocomotion.SetOrientation(PlanetModel_s00ca_8710()->BuildSurfaceOrientation(pos, dir));
            return;
        }
        if (mpOwner->GetMoveType() == 0) {
            Vector3_s00ca_8710 forward = dir;
            Vector3_s00ca_8710 up = PlanetModel_s00ca_8710()->GetSurfaceNormal(pos);
            Vector3_s00ca_8710 side = forward.Cross(up);
            forward = up.Cross(side);
            Quaternion q = QuaternionFromMatrix(MakeMatrixRows(forward, up, side));
            q = NormalizedQuaternion(q);
            mpOwner->mLocomotion.SetOrientation(q);
            return;
        }
        Turn(dir, dt);
        break;
    case 1:
        mpOwner->mLocomotion.SetOrientation(PlanetModel_s00ca_8710()->BuildSurfaceOrientation(pos, dir));
        return;
    case 2:
        Steer(dir, dt,
              sqrtf(velocity.x * velocity.x + velocity.y * velocity.y + velocity.z * velocity.z),
              accelSign);
        return;
    }
}

// @ 0x00ca95c0
void cVehicle_s00ca_8710::GetDebugToolTip(EastlString_s00ca_8710* out)
{
    out->append_sprintf("\n%s %s vehicle (subtype %x)",
                        kLocomotionString[mLocomotionType],
                        kPurposeString[mPurpose],
                        mSubtype);
    out->append_sprintf("\nPower: %.1f  Defense: %.1f  Speed: %.1f",
                        (double)mPower,
                        (double)mDefense,
                        (double)mSpeedValue);
    if (mPurpose != 0 && mCargoType != 0) {
        out->append_sprintf("\nCargo: %.1f %s",
                            (double)mCargoAmount,
                            kCargoTypeString[mCargoType]);
    }
    out->append_sprintf("\n%d hostile units detected", (int)(mpHostilesEnd - mpHostilesBegin));
    if (mFlags & 2)
        out->append_sprintf("\n==Goal Blocked==");
    if (mFlags & 4)
        out->append_sprintf("\n==Waiting for Path==");
}

// @ 0x00ca96b0
void cVehicle_s00ca_8710::UpdateCrowdTimers()
{
    if (mbCrowdTimerArmed) {
        if (mTimerC88.GetElapsedTime() > 0xc1c)
            mbCrowdTimerArmed = false;
    }
    if (mbPathWaitTimerArmed) {
        if (mTimerBD8.GetElapsedTime() > 0x9c4) {
            mbPathWaitTimerArmed = false;
            mPathQueue.push_back(0x19);
        }
    }
    if (mTimerBF8.IsRunning()) {
        if (mTimerBF8.GetElapsedTime() > 0x1388) {
            EndAngryCrowdAttack();
            return;
        }
    }
}

// @ 0x00ca9770
bool ILocomotion_s00ca_8710::Forward(int a, float b, float c)
{
    cVehicle_s00ca_8710* owner = (cVehicle_s00ca_8710*)((char*)this - 0x34);
    owner->Move(a, b, c, 1);
    return true;
}

// @ 0x00ca97a0
void cVehicle_s00ca_8710::MoveWithFlag(int a, float b, float c)
{
    if (mGameMode == 2 && GetCurrentGameMode() == &DAT_01654c10) {
        float t = mLocomotion.v74(0);
        t = mLocomotion.v74(t + c);
        mLocomotion.vE0(a, t + b);
    } else {
        Move(a, b, c, 0);
    }
}

// @ 0x00ca9820
void __cdecl FUN_00ca9820()
{
}

// @ 0x00ca9b00
tSlot24* __thiscall cSlotVector24::Erase(tSlot24* pFirst, tSlot24* pLast)
{    tSlot24* pOldEnd = mpEnd;
    tSlot24* pNewEnd = FUN_00ca0da0(pLast, pOldEnd, pFirst);
    tSlot24* pEnd = mpEnd;
    for (tSlot24* p = pNewEnd; p < pEnd; ++p) {
        if (p->mpObj)
            p->mpObj->Release();
    }
    mpEnd -= (int32_t)(pLast - pFirst);
    return pFirst;}

// @ 0x00ca9b70
void __cdecl FUN_00ca9b70()
{
}

// @ 0x00ca9cc0
tSlot16* __thiscall cSlotVector16::Erase(tSlot16* pFirst, tSlot16* pLast)
{    tSlot16* pOldEnd = mpEnd;
    tSlot16* pNewEnd = FUN_00ca0e80(pLast, pOldEnd, pFirst);
    tSlot16* pEnd = mpEnd;
    for (tSlot16* p = pNewEnd; p < pEnd; ++p) {
        if (p->mpObj)
            p->mpObj->Release();
    }
    mpEnd -= (int32_t)(pLast - pFirst);
    return pFirst;
}

// @ 0x00ca9d20
void __cdecl FUN_00ca9d20()
{
}

// @ 0x00ca9e90
void __cdecl FUN_00ca9e90()
{
}

// @ 0x00caa0c0
void __cdecl FUN_00caa0c0()
{
}

// @ 0x00caa1c0
void __cdecl FUN_00caa1c0()
{
}

// @ 0x00caa360
void SP::cVehicle::DestroyVehicle(bool a1, unsigned int a2)
{
}

// @ 0x00cacf40
void Agent34::Update()
{
    BaseUpdate();
    if (GetCurrentGameMode() == &kGameModeA) {
        OwnerInfo* info = ((OwnerInfo*(__thiscall*)(void*))VSLOT(this, 0x68))(this);
        mOwnerValue = info->v14;
        mTracker.Update();
    }
    float range;
    if (GetCurrentGameMode() != &kGameModeA)
        range = mGauge.GetBaseRange() + 60.0f;
    else
        range = mSenseRange;

    // 1. all other tribes
    PtrRange* gv = &NounManager_s00ca_cf40()->GetGameDataVector(fnA, fnB, fnC, fnD, &kTypeTribes)->vec;
    void** it = gv->mBegin;
    void** end = gv->mEnd;
    if (it != end) {
        do {
            void* t = *it;
            if (t != (void*)R()) {
                Vec3_s00ca_cf40* a = PosOf(this);
                char* sp = (char*)t + 0x34;
                Vec3_s00ca_cf40* b = PosOf(sp);
                if (DistXYZ(a, b) < range)
                    AddUnique(&mNear, sp);
            }
            ++it;
        } while (it != end);
    }

    // 2. the SimSingleton object list
    if (!gSimSingleton)
        gSimSingleton = new ("Simulator/SimSingleton", 0, 0, 0, 0) SimSingleton();
    SimList* sl = gSimSingleton->GetObjects();
    it = sl->mBegin;
    end = sl->mEnd;
    if (it != end) {
        do {
            Vec3_s00ca_cf40* a = PosOf(this);
            void* sp = *it;
            Vec3_s00ca_cf40* b = PosOf(sp);
            if (DistZYX(a, b) < range)
                AddUnique(&mNear, sp);
            ++it;
        } while (it != end);
    }

    // 3. nearest tribe and its members / agents
    if (GetCivStrategy()) {
        float bestDist = 3.40282346e+38f;
        Tribe* best = 0;
        PtrRange* gv2 = &NounManager_s00ca_cf40()->GetGameDataVector(fnA, fnB, fnE, fnD, &kTypeTribes2)->vec;
        int n = (int)(gv2->mEnd - gv2->mBegin);
        for (int i = 0; i < n; ++i) {
            Tribe* t = (Tribe*)gv2->mBegin[i];
            Vec3_s00ca_cf40* a = PosOf(this);
            Vec3_s00ca_cf40* b = PosOf(&t->spatial);
            float d = DistZYX(a, b);
            if (d < bestDist) {
                bestDist = d;
                if (t != best) {
                    TrAddRef(t);
                    Tribe* old = best;
                    best = t;
                    if (old) TrRelease(old);
                }
            }
            TribeInfo* ti = ((TribeInfo*(__thiscall*)(void*))VSLOT(t, 0x6c))(t);
            if (d - ti->radius < range) {
                MemberVec* mv = t->GetMembers();
                void** mp = mv->mBegin;
                void** me = mv->mEnd;
                if (mp != me) {
                    do {
                        Vec3_s00ca_cf40* a2 = PosOf(this);
                        char* sp = (char*)*mp + 0x34;
                        Vec3_s00ca_cf40* b2 = PosOf(sp);
                        if (DistZYX(a2, b2) < range)
                            AddUnique(&mNear, sp);
                        ++mp;
                    } while (mp != me);
                }
                void** ap = t->mAgentsBegin;
                void** ae = t->mAgentsEnd;
                if (ap != ae) {
                    do {
                        Vec3_s00ca_cf40* a2 = PosOf(this);
                        char* sp = (char*)*ap + 0x34;
                        Vec3_s00ca_cf40* b2 = PosOf(sp);
                        if (DistZYX(a2, b2) < range)
                            AddUnique(&mNear, sp);
                        ++ap;
                    } while (ap != ae);
                }
            }
        }
        if (best != mNearest) {
            if (mNearest)
                mNearest->Detach(R() ? &mGauge : 0);
            if (best)
                best->Attach(R() ? &mGauge : 0);
            Tribe* old = mNearest;
            if (best != old) {
                if (best) TrAddRef(best);
                mNearest = best;
                if (old) TrRelease(old);
            }
        }
        if (best) TrRelease(best);
    }

    // 4. rebuild the creature list from the near list
    {
        void** first = mCreatures.mBegin;
        void** last = mCreatures.mEnd;
        void** newEnd = CopyPtrRange(last, mCreatures.mEnd, first);
        void** cEnd = mCreatures.mEnd;
        for (void** p = newEnd; p < cEnd; ++p)
            if (*p) CrRelease(*p);
        mCreatures.mEnd -= (last - first);
    }
    int myId = mGauge.GetOwnerId();
    void** np = mNear.mBegin;
    void** ne = mNear.mEnd;
    if (np != ne) {
        do {
            void* item = *np;
            void* c;
            if (item && (c = SpCast(item, (uint32_t)&kCreatureType)) != 0) {
                void* q1 = CastOrNull(np, 0x4f176642);
                void* q2 = CastOrNull(np, 0x403df5f);
                void* q3 = CastOrNull(np, 0x116d858);
                void* q4 = CastOrNull(np, 0xb033b403);
                if (!q1 && !q2 && !q3 && !q4) {
                    bool add = false;
                    const void* mode = GetCurrentGameMode();
                    int (__thiscall *getOwner)(void*) = (int (__thiscall*)(void*))VSLOT(c, 0x10);
                    if (mode == &kGameModeA) {
                        add = getOwner(c) != myId;
                    } else {
                        int v = getOwner(c);
                        if (v == myId || v == -1) {
                            void* r = ((void*(__thiscall*)(void*, uint32_t))VSLOT(c, 0x5c))(c, 0xce9f6639);
                            if (r)
                                add = ((CrHelper*)r)->Test();
                        } else {
                            void* rel = ((void*(__thiscall*)(void*))VSLOT(c, 0xc))(c);
                            int a = ((int(__thiscall*)(void*))VSLOT(R(), 0x4c))(R());
                            int b = ((int(__thiscall*)(void*))VSLOT(rel, 0x4c))(rel);
                            add = RelationshipManager()->Relation(b, a, 1) <= 1;
                        }
                    }
                    if (add)
                        PushCreature(&mCreatures, c);
                }
            }
            ++np;
        } while (np != ne);
    }
    R()->FinalStep();
}

// @ 0x00cad7e0
void SimObject::AddTarget(SimTarget* target)
{
    SimTargetVec* vec = &mTargets;
    SimTarget** it = vec->mpBegin;
    SimTarget** end = vec->mpEnd;
    if (it != end) {
        do {
            if (*it == target)
                break;
            ++it;
        } while (it != end);
    }
    if (it != end)
        return;

    SimTarget* ref = target;
    if (ref)
        ref->AddRef();
    vec->PushBack(ref);
    if (ref)
        ref->Release();
}

// @ 0x00cadb00
void SimPanel::Shutdown()
{
    IRef2** p = &mRefArray[8];
    for (int i = 7; i >= 0; --i)
    {
        IRef2* r = *--p;
        if (r)
            r->Release();
    }
    SimSlot* q = &mSlotArray[8];
    for (int j = 7; j >= 0; --j)
        (--q)->ResetSerializer();
}

// @ 0x00cadb50
void SimPanelReset(SimPanel* panel)
{
    memset(panel, 0, 0x800);
    for (int i = 0; i < 8; ++i)
    {
        IRef2* r = panel->mRefArray[i];
        if (r)
        {
            panel->mRefArray[i] = 0;
            r->Release();
        }
    }
}

// @ 0x00cadb90
void ScaleNormalizedVec(Vec3_s00ca_cf40* out, const Vec3_s00ca_cf40* v, NormCtx* ctx)
{
    float scale = ctx->GetScale(*v);
    float inv = 1.0f / sqrtf(v->x * v->x + v->y * v->y + v->z * v->z + kNormalizeEps);
    Vec3_s00ca_cf40 dir;
    dir.x = v->x * inv;
    dir.y = v->y * inv;
    dir.z = v->z * inv;
    out->x = dir.x * scale;
    out->y = dir.y * scale;
    out->z = dir.z * scale;
}

// @ 0x00cadc20
bool SimTrySpawn(SimSpawnOut* out, SimObjA* self, const Vec3_s00ca_cf40* target, SimSpawnSrc* src)
{
    if (src->mpBegin != src->mpEnd)
        return true;

    float radiusIn = src->mRadiusIn;
    float radius = src->mRadiusIn + src->mScale + kSpawnRadiusBias;
    if (self->mFlags & 4)
        return true;

    float dx = src->mVec.x - target->x;
    float dy = src->mVec.y - target->y;
    float dz = src->mVec.z - target->z;
    if (dx * dx + dy * dy + dz * dz <= radius * radius)
        return true;

    out->mPos.x = 0.0f;
    out->mPos.y = 0.0f;
    out->mPos.z = 0.0f;

    self->mSub.SetDestination(src->mVec, radiusIn);
    SimSpawnOut* spawn = (SimSpawnOut*)self->mSub.CreateSpawn();
    spawn->mVel = src->mVel;
    spawn->mKind = src->mKind;
    spawn->mScale = src->mScale;
    return false;
}

// @ 0x00cadd50
void SimPathUpdate(SimStepProvider* step, SimObjA* a, SimObjB* b, bool armed, float dt)
{
    if (dt < b->mTimer && !(a->mFlags & 0xb))
    {
        b->mTimer2 = 0.0f;
        return;
    }
    b->mTimer2 += step->mStep;
    if (b->mTimer2 <= kPathOne)
        return;

    Vec3_s00ca_cf40 dir;
    ScaleNormalizedVec(&dir, &b->mDir, a);
    b->mDir = dir;
    if (b->mTimer2 <= kPathTwo)
        return;

    if (!armed || b->mMode != 3)
    {
        a->mFlags |= 1;
        return;
    }

    float k = a->mSub.GetPathScale();
    Vec3_s00ca_cf40 tmp;
    tmp.x = b->mVel.x * k + b->mDir.x;
    tmp.y = b->mVel.y * k + b->mDir.y;
    tmp.z = b->mVel.z * k + b->mDir.z;
    const Vec3_s00ca_cf40* pos = a->mSub.GetPos();
    tmp.x -= pos->x;
    tmp.y -= pos->y;
    tmp.z -= pos->z;
    b->mVel = normalized_safe(tmp);
    a->mFlags &= ~0xbu;
}

// @ 0x00caded0
Simulator::cFlyingLocomotion_s00ca_ded0::cFlyingLocomotion_s00ca_ded0()
: mUnk10(0.0f)
    , mUnk14(kZeroVector_s00ca_ded0)
    , mUnk20(kZeroVector_s00ca_ded0)
    , mUnk30(0)
    , mbAligned(false)
    , mLift(0.0f)
{
}

// @ 0x00cae0e0
Vector3_s00ca_ded0 ProjectToFlightSurface(const Vector3_s00ca_ded0& pos, cCreatureFlyer* pFlyer)
{
    float radius = pFlyer->GetGroundRadius(pos);
    Vector3_s00ca_ded0 dir = pos.Normalized();
    Vector3_s00ca_ded0 from = dir * (radius + 128.0f);
    Vector3_s00ca_ded0 to = dir * radius;
    Vector3_s00ca_ded0 hit;
    if (SweepTest(pFlyer ? &pFlyer->mLocomotion : 0, from, to, &hit, 1)) {
        float dist = hit.Length() + 5.0f;
        return dir * dist;
    }
    return to;
}

// @ 0x00cb02f0
void cFlyingLocomotion_s00cb_02f0::Update(LocoSteerParams* params)
{
    if (mbReset) {
        cCreatureFlyer_s00cb_02f0* pFlyer = params->mpObject ? params->mpObject->Cast(0x137E8E0) : 0;
        cLocomotionRequest* request = params->mpObject->GetRequest();
        if (request->mMode != 0) {
            int count = (int)(request->mpEnd - request->mpBegin);
            for (int i = 0; i < count; i++) {
                LocoWaypoint& point = request->mpBegin[i];
                point.mPosition = ProjectToFlightSurface(point.mPosition, pFlyer);
            }
            request->mGoal.mPosition = ProjectToFlightSurface(request->mGoal.mPosition, pFlyer);
        }
        request->mLastDistance = 0.0f;
        mbReset = false;
    }

    cCreatureFlyer_s00cb_02f0* pFlyer = params->mpObject ? params->mpObject->Cast(0x137E8E0) : 0;
    cLocomotiveObject_s00cb_02f0* loco = &pFlyer->mLocomotion;
    cLocomotionRequest* request = loco->GetRequest();
    if (request->mMode == 0) {
        Vector3_s00cb_02f0 target = ProjectToFlightSurface(*loco->GetPosition(), pFlyer);
        FlyTo(pFlyer, target, params);
        return;
    }

    Vector3_s00cb_02f0 pos = *loco->GetPosition();
    Vector3_s00cb_02f0 up = pos.Normalized();
    Vector3_s00cb_02f0 facing = loco->GetFacing();
    Vector3_s00cb_02f0 target = request->mGoal.mPosition;
    Vector3_s00cb_02f0 toTarget = target - pos;
    float dist = toTarget.Length();
    if (request->mGoal.mGoalStopDistance > dist ||
        (request->mStallTime > 0.5f && request->mAcceptableStopDistance > dist)) {
        mbAligned = false;
        if (request->mpBegin == request->mpEnd) {
            loco->StopMovement();
            FlyTo(pFlyer, target, params);
            return;
        }
        request->mGoal = *request->mpBegin;
        request->erase(request->mpBegin);
        target = request->mGoal.mPosition;
        request->mStallTime = 0.0f;
        dist = (target - pos).Length();
    }
    else {
        if (dist >= request->mLastDistance)
            request->mStallTime += params->mDeltaTime;
        else
            request->mStallTime = 0.0f;
        request->mLastDistance = dist;
    }

    toTarget = target - pos;
    Vector3_s00cb_02f0 dir = toTarget.Normalized();
    if (pos.Normalized().Dot(up) < 0.97f) {
        Vector3_s00cb_02f0 avoid = AvoidSurface(pos + dir * 16.0f, pFlyer);
        dir = (avoid - pos).Normalized();
        target = avoid;
    }

    float alignment = dir.Dot(up);
    if (!mbAligned && (alignment > kFlyAlignThreshold || alignment < -kFlyAlignThreshold))
        mbAligned = true;
    if (mbAligned) {
        FlyTo(pFlyer, target, params);
        return;
    }

    float hover = loco->GetHoverHeight();
    float lookAhead = Min(dist, pFlyer->GetMaxSpeed() * 2.0f + hover);
    float clearance = Min(dist, pFlyer->GetMaxSpeed() * 4.0f);
    float altitude = pos.Length() - Max(pFlyer->GetGroundRadius(pos), target.Length());

    Vector3_s00cb_02f0 lateral = (dir - up * dir.Dot(up)).Normalized();
    Vector3_s00cb_02f0 side = facing.Cross(up).Normalized();
    Vector3_s00cb_02f0 forward = (facing - up * facing.Dot(up)).Normalized();
    Vector3_s00cb_02f0 steer;
    if (forward.Dot(lateral) > 0.0f)
        steer = lateral;
    else if (side.Dot(lateral) < 0.0f)
        steer = -side;
    else
        steer = side;

    Vector3_s00cb_02f0 hitPos;
    float liftTarget = kFlyLiftRate;
    if (!SweepTest(loco, pos, pos + dir * lookAhead, &hitPos, 0)) {
        Vector3_s00cb_02f0 groundHit = PlanetModel_s00cb_02f0()->IntersectRay(pos, dir);
        if (groundHit == kZeroVector_s00cb_02f0 || (groundHit - pos).Length() >= clearance)
            liftTarget = 0.0f;
    }

    if (mLift > liftTarget) {
        mLift -= params->mDeltaTime;
        if (mLift < 0.0f)
            mLift = 0.0f;
    }
    else if (mLift < liftTarget) {
        mLift += params->mDeltaTime;
        if (mLift > liftTarget)
            mLift = liftTarget;
    }

    if (mLift > 0.0f) {
        steer = (steer + up * mLift).Normalized();
    }
    else if (altitude > 0.0f) {
        float descent = Min(altitude, 5.0f) * 0.2f;
        steer = normalized_safe(steer - up * descent);
    }

    steer = TurnTowards(facing, steer, pFlyer->mTurnRate, params->mDeltaTime);
    float speed = loco->GetVelocity()->Length();
    float maxSpeed = pFlyer->GetMaxSpeed();
    float desiredSpeed = maxSpeed;
    if (request->mpBegin == request->mpEnd && maxSpeed > dist)
        desiredSpeed = dist;
    float angle = fmodf(SignedAngle(facing, dir, up), kTwoPI);
    if (angle > kPI)
        angle -= kTwoPI;
    else if (angle < -kPI)
        angle += kTwoPI;
    float turnSpeed = pFlyer->mTurnRate / fabsf(angle) * dist;
    if (turnSpeed < maxSpeed)
        desiredSpeed = turnSpeed;
    float accel = maxSpeed * 0.5f;
    if (desiredSpeed > speed) {
        speed += accel * params->mDeltaTime;
        if (speed > desiredSpeed)
            speed = desiredSpeed;
    }
    else if (speed > desiredSpeed) {
        speed -= accel * params->mDeltaTime;
        if (speed < desiredSpeed)
            speed = desiredSpeed;
    }
    params->mVelocity = steer * speed;
    ApplyFacing(pFlyer, steer, params->mDeltaTime);
}
#pragma pack(pop)

// @ 0x00cb1210
TraceCache* FUN_00cb1210(unsigned key)
{
    Ht* const ht = (Ht*)g_157d30c;
    Iter it;

    ht->Find(&it, &key);
    Node* const pNode = it.mpNode;
    _ReadWriteBarrier();
    if (pNode == ht->mpBuckets[ht->mBucketCount]) {
        TraceCache* cache = ht->FindOrInsert(&key);
        FUN_00cadb50(cache);
        return cache;
    }
    return &pNode->mValue.mTrace;
}

// @ 0x00cb2f70
void __cdecl FUN_00cb2f70(NavObj* obj)
{
    RawLoco* raw = obj->mp14;
    SimWorld* world;
    if (raw == 0)
        world = 0;
    else
        world = (SimWorld*)((FnVp1i)((VObj*)raw)->vt[0xb8 / 4])(raw, 0x137e8e0);

    float* pos = ((FnVp0p)((VObj*)raw)->vt[0x2c / 4])(raw);
    float mtx[12];
    ((FnVp1v)((VObj*)&world->mSub)->vt[0x5c / 4])(&world->mSub, mtx);

    PathSlot* p = raw->FUN_00c41ec0();
    int hasRoute = p->mCount5c;
    bool nearGoal = raw->IsNearGoal();

    float dz = p->mPos[2] - pos[2];
    float dy = p->mPos[1] - pos[1];
    float dx = p->mPos[0] - pos[0];
    float dist2 = (dz * dz + dy * dy) + dx * dx;
    float dist = sqrtf(dist2);

    bool noPath = (raw->mf1a0 == 0.0f);
    bool flag = (raw->mf1a0 > g_157d340) || noPath;
    if (world->mbcd != 0
        || ((pos[0] == g_169a37c && pos[1] == g_169a380 && pos[2] == g_169a384)
            || (hasRoute == 0 || nearGoal))) {
        flag = false;
    }

    FloatBytes4 arg;
    arg.f = 1.0f;

    if (hasRoute != 0) {
        if (noPath) {
            void* u = FUN_00cb1210(world);
            FUN_00cadb50(u);
            world->mFlags2a4 &= 0xfffffff4u;
            if (!FUN_00cadc20(obj, world, pos, p))
                return;
        }

        float ratio = world->FUN_00c9f380() / world->mf21c;
        float sel = (ratio > 1.0f) ? ratio : 1.0f;
        arg.f = (p->mBegin == p->mEnd) ? p->mf20 : (sel * 2.0f);

        arg.bytes[0] = raw->FUN_00c41ed0(dist * dist, arg.f);
        FUN_00cadd50(obj, world, p, arg.f, dist);
        float inv;
        if ((dz > dist
             && (inv = 1.0f / sqrtf(dist2 + 1e-08f),
                 0.9f > (mtx[1] * (dz * inv) + mtx[2] * (dy * inv)
                         + (inv * dx) * mtx[0])))
            || arg.bytes[0] != 0) {
            float* e = (float*)p->mBegin;
            if (e == (float*)p->mEnd) {
                LocoSub34* sub = &world->mSub;
                LocoRequestLocal req;
                void* r = req.ctor();
                ((FnVp1v)((VObj*)sub)->vt[0xdc / 4])(sub, r);
                int* rp = (int*)req.mData;
                if (rp != 0 && rp[-1] != 0)
                    operator_delete_array(rp);
                flag = false;
            }
            else {
                if (p->mFlag4c & 1)
                    flag = true;
                float* dst = p->mPos;
                for (int i = 0; i < 0xf; ++i)
                    dst[i] = e[i];
                FUN_00b47520(e);
                float ndx = p->mPos[0] - pos[0];
                dist = sqrtf((p->mPos[1] - pos[1]) * (p->mPos[1] - pos[1])
                             + ((p->mPos[2] - pos[2]) * (p->mPos[2] - pos[2])
                                + ndx * ndx));
            }
        }
    }

    float f1c;
    if (!flag || noPath || !(p->mFlag4c & 1)) {
        arg.f = 1.0f;
        PathSlot* q = FUN_00cb1210(world);
        if (q->mEnd != 0 && q->mf08 < 1.0f)
            f1c = q->mf08;
    }
    else {
        flag = FUN_00cb2480(world, p, &dz, &f1c, (void**)&pos);
    }

    if (flag
        && FUN_00cb2770(world, &dz, p, &arg.f, &dist, &f1c, (void**)&pos) > 2) {
        raw->mf1a0 = 0.0f;
    }

    uint32_t flags = world->mFlags2a4;
    if (flags & 0xb) {
        LocoSub34* sub = &world->mSub;
        PathSlot* st = sub->FUN_00c41ec0();
        if (((flags & 2) == 0) || st->mf6c <= 2.0f) {
            if (st->mf6c <= 30.0f) {
                float* pp = ((FnVp0p)((VObj*)sub)->vt[0x2c / 4])(sub);
                LocoRequest req;
                req.m00 = 0;
                req.m04 = 0;
                req.m08 = 0;
                req.mPos[0] = pp[0];
                req.mPos[1] = pp[1];
                req.mPos[2] = pp[2];
                req.mf20 = 1.0f;
                req.m28 = 0;
                req.m50 = 0;
                req.mf54 = 0.0f;
                req.mf58 = 0.0f;
                req.mf5c = 0.0f;
                req.m60 = 1;
                req.mf64 = 2.0f;
                req.mf6c = g_147510c;
                req.mf70 = 0.0f;
                req.m74 = 0;
                ((FnVp1v)((VObj*)sub)->vt[0xdc / 4])(sub, &req);
                int* data = *(int**)&req;
                if (data != 0 && data[-1] != 0)
                    operator_delete_array(data);
            }
        }
        else {
            world->mFlags2a4 = flags & 0xfffffffdu;
        }
    }

    p->mf68 = dist;
}

// @ 0x00cb34d0
void Sim34d0::FUN_00cb34d0(NavObj* obj)
{
    SimWorld* world;
    if (obj->mp14 == 0)
        world = 0;
    else
        world = (SimWorld*)((FnVp1i)((VObj*)obj->mp14)->vt[0xb8 / 4])(obj->mp14, 0x137e8e0);

    char* pm;
    if (world->mB1c != 1 || (pm = PlanetModel_s00cb_2f70(), pm[0xf0] == 0)) {
        if (mb4 != 0) {
            PathSlot* p = obj->mp14->FUN_00c41ec0();
            if (p->mCount5c != 0) {
                int count = (int)(p->mEnd - p->mBegin) / 0x3c;
                if (count > 0) {
                    int off = 0;
                    do {
                        float* e = (float*)(p->mBegin + off);
                        float len = world->FUN_00c9ffd0(e);
                        float x = e[0], y = e[1], z = e[2];
                        float inv = 1.0f / sqrtf(((x * x + y * y) + z * z) + 1e-08f);
                        e[0] = (x * inv) * len;
                        e[1] = len * (y * inv);
                        e[2] = len * (z * inv);
                        off += 0x3c;
                    } while (--count != 0);
                }
                float* q = p->mPos;
                float len = world->FUN_00c9ffd0(q);
                float x = q[0], y = q[1], z = q[2];
                float inv = 1.0f / sqrtf(((x * x + y * y) + z * z) + 1e-08f);
                q[0] = (x * inv) * len;
                q[1] = (y * inv) * len;
                q[2] = (z * inv) * len;
            }
            mb4 = 0;
        }
        FUN_00cb2f70(obj);
        FUN_00cae280(obj);
    }
}

// @ 0x01352460
void FUN_01352460(void)
{
    PropDesc d;
    d.mName = (const char*)g_147342c;
    d.mHash = 0x603498b;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)FUN_00692ca0;
    d.mFn24 = (void*)FUN_00c7e9f0;
    d.mFn28 = (void*)FUN_00cd44e0;
    d.mFn2C = (void*)FUN_00c2e4e0;
    d.mFn30 = (void*)FUN_00692fb0;
    d.mFn34 = (void*)U_01352460_0_34;
    d.mFn38 = (void*)U_01352460_0_38;
    d.mType = 0x0;
    *(PropDesc*)g_1579c58 = d;
}

// @ 0x01354df0
void FUN_01354df0(void)
{
    void* const kDef  = (void*)0x00692ca0;  // Simulator::Attribute::DefaultOffset
    void* const kInit = (void*)0x00b1fbf0;  // UTFWin::Window::Initialize
    SimAttr a;

    a.mName    = (const char*)0x01473fb4;   // "mPos"
    a.mDesc    = (const char*)0x006a7f2f9;
    a.mZero0   = 0;
    a.mZero1   = 0;
    a.mDefault = kDef;
    a.mFn0     = (void*)0x00b6e3a0;
    a.mFn1     = (void*)0x00ac88c0;
    a.mFn2     = (void*)0x006930f0;
    a.mFn3     = (void*)0x00695010;
    a.mFn4     = kInit;
    a.mFn5     = (void*)0x00acbba0;
    a.mIndex   = 0;
    ATTRS[0] = a;

    a.mName    = (const char*)0x01473fa4;   // "mCurrentFood"
    a.mDesc    = (const char*)0x006a7f2fa;
    a.mZero0   = 0;
    a.mZero1   = 0;
    a.mDefault = kDef;
    a.mFn0     = (void*)0x00572810;
    a.mFn1     = (void*)0x00ac88f0;
    a.mFn2     = (void*)0x006930b0;
    a.mFn3     = (void*)0x00694fc0;
    a.mFn4     = kInit;
    a.mFn5     = (void*)0x00acbb80;
    a.mIndex   = 0xc;
    ATTRS[1] = a;

    a.mName    = (const char*)0x01473f98;   // "mMaxFood"
    a.mDesc    = (const char*)0x006a7f2fb;
    a.mZero0   = 0;
    a.mZero1   = 0;
    a.mDefault = kDef;
    a.mFn0     = (void*)0x00572810;
    a.mFn1     = (void*)0x00ac88f0;
    a.mFn2     = (void*)0x006930b0;
    a.mFn3     = (void*)0x00694fc0;
    a.mFn4     = kInit;
    a.mFn5     = (void*)0x00acbb80;
    a.mIndex   = 0x10;
    ATTRS[2] = a;

    a.mName    = (const char*)0x01473f88;   // "mResupplyRate"
    a.mDesc    = (const char*)0x006a7f2fc;
    a.mZero0   = 0;
    a.mZero1   = 0;
    a.mDefault = kDef;
    a.mFn0     = (void*)0x00572810;
    a.mFn1     = (void*)0x00ac88f0;
    a.mFn2     = (void*)0x006930b0;
    a.mFn3     = (void*)0x00694fc0;
    a.mFn4     = kInit;
    a.mFn5     = (void*)0x00acbb80;
    a.mIndex   = 0x14;
    ATTRS[3] = a;

    a.mName    = (const char*)0x01473f7c;   // "mCubeIndex"
    a.mDesc    = (const char*)0x006a7f2fd;
    a.mZero0   = 0;
    a.mZero1   = 0;
    a.mDefault = kDef;
    a.mFn0     = (void*)0x00c8ec20;
    a.mFn1     = (void*)0x00c8ec40;
    a.mFn2     = (void*)0x00c2e4e0;         // UTFWin::ILayoutElement::SetSerializer
    a.mFn3     = (void*)0x00692fb0;         // ?ClearBuffer@@YAXPAPAC@Z
    a.mFn4     = kInit;
    a.mFn5     = (void*)0x00ac8050;
    a.mIndex   = 0x18;
    ATTRS[4] = a;

    a.mName    = (const char*)0x01473f68;   // "mpFishingHitSphere"
    a.mDesc    = (const char*)0x006a7f2fe;
    a.mZero0   = 0;
    a.mZero1   = 0;
    a.mDefault = kDef;
    a.mFn0     = (void*)0x00bd0cb0;
    a.mFn1     = (void*)0x00bca960;         // cAgentOrderManager::ActivateOne
    a.mFn2     = (void*)0x00c2e4e0;
    a.mFn3     = (void*)0x00692fb0;         // ?ClearBuffer@@YAXPAPAC@Z
    a.mFn4     = (void*)0x00b6f550;
    a.mFn5     = (void*)0x00ac8050;
    a.mIndex   = 0x24;
    ATTRS[5] = a;

    a.mName    = (const char*)0x01473f54;   // "mpFishingHotSpot"
    a.mDesc    = (const char*)0x006a7f2ff;
    a.mZero0   = 0;
    a.mZero1   = 0;
    a.mDefault = kDef;
    a.mFn0     = (void*)0x00bed160;
    a.mFn1     = (void*)0x00bca960;
    a.mFn2     = (void*)0x00c2e4e0;
    a.mFn3     = (void*)0x00692fb0;         // ?ClearBuffer@@YAXPAPAC@Z
    a.mFn4     = (void*)0x00b6f550;
    a.mFn5     = (void*)0x00ac8050;
    a.mIndex   = 0x28;
    ATTRS[6] = a;

    a.mName    = (const char*)0x01473f48;   // "mStartTime"
    a.mDesc    = (const char*)0x006a7f419;
    a.mZero0   = 0;
    a.mZero1   = 0;
    a.mDefault = kDef;
    a.mFn0     = (void*)0x00aff840;
    a.mFn1     = (void*)0x00aff870;
    a.mFn2     = (void*)0x00692fd0;         // ?ParseInt64@@YAXPAPBDPA_J@Z
    a.mFn3     = (void*)0x00694ec0;
    a.mFn4     = kInit;
    a.mFn5     = (void*)0x00595a70;
    a.mIndex   = 0x30;
    ATTRS[7] = a;

    a.mName    = (const char*)0x01473f3c;   // "mbActive"
    a.mDesc    = (const char*)0x006a7f41a;
    a.mZero0   = 0;
    a.mZero1   = 0;
    a.mDefault = kDef;
    a.mFn0     = (void*)0x00ac8750;
    a.mFn1     = (void*)0x00ac8780;
    a.mFn2     = (void*)0x00693090;         // ?ParseULong@@YAXPAPBDPAK@Z
    a.mFn3     = (void*)0x00694fa0;
    a.mFn4     = kInit;
    a.mFn5     = (void*)0x0057ce00;
    a.mIndex   = 0x38;
    ATTRS[8] = a;

    a.mName    = (const char*)0x01473f2c;   // "mbReplenishing"
    a.mDesc    = (const char*)0x006a7f41b;
    a.mZero0   = 0;
    a.mZero1   = 0;
    a.mDefault = kDef;
    a.mFn0     = (void*)0x00ac8750;
    a.mFn1     = (void*)0x00ac8780;
    a.mFn2     = (void*)0x00693090;
    a.mFn3     = (void*)0x00694fa0;
    a.mFn4     = kInit;
    a.mFn5     = (void*)0x0057ce00;
    a.mIndex   = 0x39;
    ATTRS[9] = a;
}

// @ 0x01355f90
void FUN_01355f90(void)
{
    EntryB8* e = (EntryB8*)0x1695458;
    for (s32 i = 0x5f; i >= 0; --i) {
        f32 v = *(f32*)0x1473c70;
        e->m00 = 3;
        e->m04 = 0;
        e->m08 = 0xa;
        e->m50 = 0xb750af68;
        e->m8C = 0;
        e->m90 = v;
        e->m94 = v;
        memset(e->m0C, 0, 0x40);
        e->mA0 = 0;
        e->mA4 = 0;
        e->mA8 = 0;
        e->mB4 = 0;
        e->m4C = 0;
        memset(e->m54, 0, 0x38);
        ++e;
    }
    lib_atexit((void (__cdecl*)())0x13c42d0);
}

// @ 0x013579e0
void FUN_013579e0(void)
{
    u32 z = 0;
    *(u32*)0x169a118 = 0x4c0cd24;
    *(u32*)0x169a11c = z;
    *(u32*)0x169a120 = z;
    *(u32*)0x169a124 = 0x4c0cd27;
    *(u32*)0x169a128 = z;
    *(u32*)0x169a12c = z;
    *(u32*)0x169a130 = 0x4c0cd26;
    *(u32*)0x169a134 = z;
    *(u32*)0x169a138 = z;
    *(u32*)0x169a13c = 0x4c0cd21;
    *(u32*)0x169a140 = z;
    *(u32*)0x169a144 = z;
    *(u32*)0x169a148 = 0x4c0cd20;
    *(u32*)0x169a14c = z;
    *(u32*)0x169a150 = z;
    *(u32*)0x169a154 = 0x4c0cd23;
    *(u32*)0x169a158 = z;
    *(u32*)0x169a15c = z;
    *(u32*)0x169a160 = 0x4c0cd22;
    *(u32*)0x169a164 = z;
    *(u32*)0x169a168 = z;
    *(u32*)0x169a16c = 0x4c0cd2d;
    *(u32*)0x169a170 = z;
    *(u32*)0x169a174 = z;
    *(u32*)0x169a178 = 0x4c0cd2c;
    *(u32*)0x169a17c = z;
    *(u32*)0x169a180 = z;
    *(u32*)0x169a184 = 0x9f82ef9c;
    *(u32*)0x169a188 = z;
    *(u32*)0x169a18c = z;
    *(u32*)0x169a190 = 0x9f82ef9d;
    *(u32*)0x169a194 = z;
    *(u32*)0x169a198 = z;
    *(u32*)0x169a19c = 0x9f82ef9e;
    *(u32*)0x169a1a0 = z;
    *(u32*)0x169a1a4 = z;
}

// @ 0x01357ae0
void FUN_01357ae0(void)
{
    u32 z = 0;
    *(u32*)0x169a1a8 = 0xfe53e4ad;
    *(u32*)0x169a1ac = z;
    *(u32*)0x169a1b0 = z;
    *(u32*)0x169a1b4 = 0xfe53e4ae;
    *(u32*)0x169a1b8 = z;
    *(u32*)0x169a1bc = z;
    *(u32*)0x169a1c0 = 0xfe53e4af;
    *(u32*)0x169a1c4 = z;
    *(u32*)0x169a1c8 = z;
    *(u32*)0x169a1cc = 0xfe53e4a8;
    *(u32*)0x169a1d0 = z;
    *(u32*)0x169a1d4 = z;
    *(u32*)0x169a1d8 = 0xfe53e4a9;
    *(u32*)0x169a1dc = z;
    *(u32*)0x169a1e0 = z;
    *(u32*)0x169a1e4 = 0xfe53e4aa;
    *(u32*)0x169a1e8 = z;
    *(u32*)0x169a1ec = z;
    *(u32*)0x169a1f0 = 0xfe53e4ab;
    *(u32*)0x169a1f4 = z;
    *(u32*)0x169a1f8 = z;
    *(u32*)0x169a1fc = 0xfe53e4a4;
    *(u32*)0x169a200 = z;
    *(u32*)0x169a204 = z;
    *(u32*)0x169a208 = 0xfe53e4a5;
    *(u32*)0x169a20c = z;
    *(u32*)0x169a210 = z;
    *(u32*)0x169a214 = 0xff53e61c;
    *(u32*)0x169a218 = z;
    *(u32*)0x169a21c = z;
    *(u32*)0x169a220 = 0xff53e61b;
    *(u32*)0x169a224 = z;
    *(u32*)0x169a228 = z;
    *(u32*)0x169a22c = 0xff53e61a;
    *(u32*)0x169a230 = z;
    *(u32*)0x169a234 = z;
    *(u32*)0x169a238 = 0xff53e619;
    *(u32*)0x169a23c = z;
    *(u32*)0x169a240 = z;
    *(u32*)0x169a244 = 0xff53e618;
    *(u32*)0x169a248 = z;
    *(u32*)0x169a24c = z;
    *(u32*)0x169a250 = 0xff53e617;
    *(u32*)0x169a254 = z;
    *(u32*)0x169a258 = z;
    *(u32*)0x169a25c = 0xff53e616;
    *(u32*)0x169a260 = z;
    *(u32*)0x169a264 = z;
}

// @ 0x01357d00
void FUN_01357d00(void)
{
    PropDesc d;

    d.mName = (const char*)g_14669f8;
    d.mHash = 0x3b0990b;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)FUN_00692ca0;
    d.mFn24 = (void*)E607_1_24;
    d.mFn28 = (void*)E607_1_28;
    d.mFn2C = (void*)E607_1_2C;
    d.mFn30 = (void*)E607_1_30;
    d.mFn34 = (void*)E607_1_34;
    d.mFn38 = (void*)E607_1_38;
    d.mType = 0x0;
    *(PropDesc*)g_157c920 = d;

    d.mName = (const char*)g_1474f20;
    d.mHash = 0x3b0990c;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)FUN_00692ca0;
    d.mFn24 = (void*)E607_2_24;
    d.mFn28 = (void*)E607_2_28;
    d.mFn2C = (void*)E607_2_2C;
    d.mFn30 = (void*)E607_2_30;
    d.mFn34 = (void*)E607_2_34;
    d.mFn38 = (void*)E607_2_38;
    d.mType = 0x10;
    *(PropDesc*)g_157c95c = d;

    d.mName = (const char*)g_1474f14;
    d.mHash = 0x5135515;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)FUN_00692ca0;
    d.mFn24 = (void*)E607_3_24;
    d.mFn28 = (void*)E607_3_28;
    d.mFn2C = (void*)E607_3_2C;
    d.mFn30 = (void*)E607_3_30;
    d.mFn34 = (void*)E607_3_34;
    d.mFn38 = (void*)E607_3_38;
    d.mType = 0x4;
    *(PropDesc*)g_157c998 = d;

    d.mName = (const char*)g_1474f08;
    d.mHash = 0x3b0990e;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)FUN_00692ca0;
    d.mFn24 = (void*)E607_4_24;
    d.mFn28 = (void*)E607_4_28;
    d.mFn2C = (void*)E607_4_2C;
    d.mFn30 = (void*)E607_4_30;
    d.mFn34 = (void*)E607_4_34;
    d.mFn38 = (void*)E607_4_38;
    d.mType = 0x14;
    *(PropDesc*)g_157c9d4 = d;
}

// @ 0x01357eb0
void FUN_01357eb0(void)
{
    PropDesc d;

    d.mName = (const char*)g_1474f28;
    d.mHash = 0x4179882;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)FUN_00692ca0;
    d.mFn24 = (void*)E611_24;
    d.mFn28 = (void*)E611_28;
    d.mFn2C = (void*)E611_2C;
    d.mFn30 = (void*)E611_30;
    d.mFn34 = (void*)E611_34;
    d.mFn38 = (void*)E611_38;
    d.mType = 0x0;
    *(PropDesc*)g_157ca50 = d;
}
