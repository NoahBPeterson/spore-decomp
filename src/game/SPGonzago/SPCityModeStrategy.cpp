// src/game/SPGonzago/SPCityModeStrategy.cpp -- migrated from slice(s) s00cfe160, s00cfd3a0, s00cfab90, s00cf9ba0, s00cf8d70, s00cf6df0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCityModeStrategy.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cCity.h"
#include "SP/cGameNounManager.h"
#include "SP/cSpeciesProfile.h"
#include "SP/cCameraManager.h"
#include "SP/cCivilization.h"
#include "SP/cConfigManager.h"
#include "SP/cGonzagoSubsystem.h"
#include "SP/cRelationshipManager.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void  *SP_NounManager();                         // 0x00b3d300
extern "C" void  *GetTriggerMgr();                          // 0x00b3d4d0
extern "C" void  *CheatManager();                           // 0x0067de20
extern "C" void  *SP_GetTerrainSphere();                    // 0x00f67d90 cTerrainEditor::GetCurrentTerrainSphere
extern "C" void  *GetPlayerCivilization(void *mgr);         // 0x00b25fb0
extern "C" bool   FUN_007cd9c0(void *o);                    // 0x007cd9c0
extern "C" bool   FUN_007cfac0(void *o);                    // 0x007cfac0
extern const float kDefaultTerrainA;   // 0x169ca8c
extern const float kDefaultTerrainB;   // 0x169ca88
extern const float kDefaultTerrainC;   // 0x169ca84
extern "C" void FUN_00bd91e0(void *city);      // 0x00bd91e0
extern "C" bool FUN_00c78420();                                 // 0x00c78420 (thiscall)
extern "C" bool FUN_00c77c50();                                 // 0x00c77c50 (thiscall)
extern "C" bool FUN_006a25a0();                                // 0x006a25a0 cDirectPropertyList::GetDescription (thiscall)
extern "C" void  *GameTimeManager();                            // 0x00b3d380
extern "C" void  *FUN_00b3d4f0();                               // 0x00b3d4f0
extern "C" void FUN_00b32250();          // 0x00b32250 DecPauseGate (thiscall)
extern "C" void   FUN_00e2f270();                               // 0x00e2f270
extern "C" void *GameInputManager();    // 0x00b3d250
extern "C" void  FUN_00697ab0();        // 0x00697ab0 cLocalInputState::OnMouseDown (thiscall)
extern "C" void  FUN_00697af0();        // 0x00697af0 cLocalInputState::OnMouseUp   (thiscall)
extern "C" void  FUN_00697b20();        // 0x00697b20 cLocalInputState::OnMouseWheel (thiscall)
extern "C" bool WriteUint32();          // 0x0093aa70 EA::IO::WriteUint32 (cdecl)
extern "C" bool ReadInt32();            // 0x0093a780 EA::IO::ReadInt32 (cdecl)
extern "C" void FUN_00befc00(void *stream, void *elem);   // 0x00befc00 write one record
extern "C" void FUN_00befbc0(void *stream, void *elem);   // 0x00befbc0 read one record
extern "C" void *AchievementsController();      // 0x00675250
extern "C" void  FUN_00676e90();                // 0x00676e90 Achievements::Controller::AutoTest (thiscall)
extern "C" void  FUN_00676710();                // 0x00676710 Achievements::Controller::AwardAchievement (thiscall)
extern "C" bool  FUN_00c772c0();                // 0x00c772c0 (thiscall)
extern "C" void  FUN_0067caf0();            // 0x0067caf0 (cdecl)
extern "C" void  FUN_0067aaf0();            // 0x0067aaf0 (thiscall)
extern "C" void  FUN_00b32220();            // 0x00b32220 IncPauseGate (thiscall)
extern "C" void *SP_ConfigManager();        // 0x0067dd30
extern "C" void *FUN_0067cac0();         // 0x0067cac0
extern "C" void  FUN_0067c8c0();         // 0x0067c8c0 (thiscall)

// ---- items of slice s00cf6df0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
typedef unsigned char  u8;
typedef int            i32;
extern "C" void  *SP_NounManager();                         // 0x00b3d300
extern "C" void  *GetTriggerMgr();                          // 0x00b3d4d0
extern "C" void  *CheatManager();                           // 0x0067de20
extern "C" void  *SP_GetTerrainSphere();                    // 0x00f67d90 cTerrainEditor::GetCurrentTerrainSphere
extern "C" i32    FUN_00c75420(void *o);                    // 0x00c75420
extern "C" void  *GetPlayerCivilization(void *mgr);         // 0x00b25fb0
extern "C" bool   FUN_007cd9c0(void *o);                    // 0x007cd9c0
extern "C" bool   FUN_007cfac0(void *o);                    // 0x007cfac0
struct cCivModeStrategy {
    void **m_vtbl;              // +0x00
    u8     m_pad04[0xb0];
    u32    m_fieldB4;           // +0xb4
    u8     m_padB8[0x58];
    void  *m_dialogue110;       // +0x110
    void  *m_dialogue114;       // +0x114
    u32    m_dialogue118;       // +0x118
    u32    m_dialogue11c;       // +0x11c

    void  ClearDialogue();      // 0x00cf7a30
    bool  IsNotCivEventA();     // 0x00cf7a40
    void  SetDialogueTimed(u32); // 0x00cf7a10
    bool  CanBuildSeaVehicles(); // 0x00cf75d0
    bool  CanBuildAirVehicles(); // 0x00cf7600
    void *AsInterface(u32 iid);  // 0x00cf7490
    bool  IsEitherDialogueIdle(); // 0x00cf7880
    void *FindBuildableVehicle(u32 arg); // 0x00cf7d40
    int   HasCivTutorialOccurred(u32 id); // 0x00cf7830
    void  OnMouseDown(u32 a, float x, float y, u32 b); // 0x00cf7380
    void  OnMouseMove(float x, float y, u32 a);        // 0x00cf73d0
    void  OnMouseUp(u32 a, float x, float y, u32 b);   // 0x00cf7420
    void  DoCVGCompletionAchievements();               // 0x00cf7630
};
extern const float kDefaultTerrainA;   // 0x169ca8c
extern const float kDefaultTerrainB;   // 0x169ca88
extern const float kDefaultTerrainC;   // 0x169ca84
extern "C" i32 FUN_00bd81d0(void *city);      // 0x00bd81d0 cCity::GetVehicleSpecialty
extern "C" void FUN_00bd91e0(void *city);      // 0x00bd91e0
struct Vec4Arr {
    void **m_begin;     // +0x00
    void **m_end;       // +0x04
};
struct SubObj {
    void **m_vtbl;      // +0x00
};
struct CivEventReq {
    u32 m_id;       // +0x00
    u32 m_pad04;    // +0x04
    u32 m_hash;     // +0x08 (0xaa9a8ed7)
};
extern "C" bool FUN_00c78420();                                 // 0x00c78420 (thiscall)
extern "C" bool FUN_00c77c50();                                 // 0x00c77c50 (thiscall)
extern "C" u32 FNVHash(const char *s, u32 seed, int flag);      // 0x00932e80
extern "C" bool FUN_006a25a0();                                // 0x006a25a0 cDirectPropertyList::GetDescription (thiscall)
extern u32 g_propList15fd918;                                   // 0x015fd918
extern "C" void  *GameTimeManager();                            // 0x00b3d380
extern "C" void  *FUN_00b3d4f0();                               // 0x00b3d4f0
extern "C" void   FUN_00b32250();                               // 0x00b32250
extern "C" void   FUN_00e2f270();                               // 0x00e2f270
extern "C" void *GameInputManager();    // 0x00b3d250
extern "C" void  FUN_00697ab0();        // 0x00697ab0 cLocalInputState::OnMouseDown (thiscall)
extern "C" void  FUN_00697af0();        // 0x00697af0 cLocalInputState::OnMouseUp   (thiscall)
extern "C" void  FUN_00697b20();        // 0x00697b20 cLocalInputState::OnMouseWheel (thiscall)
extern u8   g_serTable[];               // 0x168caf0 .. 0x168cb44 (stride 0x1c)
extern u32  g_serVersion;               // 0x145f8dc
extern "C" bool WriteUint32();          // 0x0093aa70 EA::IO::WriteUint32 (cdecl)
extern "C" bool ReadInt32();            // 0x0093a780 EA::IO::ReadInt32 (cdecl)
extern "C" void FUN_00befc00(void *stream, void *elem);   // 0x00befc00 write one record
extern "C" void FUN_00befbc0(void *stream, void *elem);   // 0x00befbc0 read one record
extern "C" void *AchievementsController();      // 0x00675250
extern "C" i32   FUN_00bf01f0();                // 0x00bf01f0 count_specialty_cities (thiscall)
extern "C" void  FUN_00676e90();                // 0x00676e90 Achievements::Controller::AutoTest (thiscall)
extern "C" void  FUN_00676710();                // 0x00676710 Achievements::Controller::AwardAchievement (thiscall)
extern "C" bool  FUN_00c772c0();                // 0x00c772c0 (thiscall)
extern "C" void  FUN_0067caf0();            // 0x0067caf0 (cdecl)
extern "C" void  FUN_0067aaf0();            // 0x0067aaf0 (thiscall)
extern "C" void  FUN_00b32220();            // 0x00b32220 IncPauseGate (thiscall)
extern "C" void *SP_ConfigManager();        // 0x0067dd30
struct V3 { float x, y, z; };
extern u32 g_1581b48, g_1581b4c, g_1581b50;
extern u8  g_1581bd0;
extern u32 g_1581bb4, g_1581bb8, g_1581bbc;
extern u32 g_1581bc0, g_1581bc4, g_1581bc8;
extern u8  g_1581bcc;
struct U3 { u32 x, y, z; };
extern "C" i32  FUN_00b320d0();          // 0x00b320d0 GetPauseGateCount (thiscall)
extern "C" void FUN_00b32250();          // 0x00b32250 DecPauseGate (thiscall)
extern "C" void *FUN_0067cac0();         // 0x0067cac0
extern "C" void  FUN_0067c8c0();         // 0x0067c8c0 (thiscall)
static void MarkCivEventId(u32 id)
{
    CivEventReq req;
    req.m_id = id;
    req.m_pad04 = 0;
    req.m_hash = 0xaa9a8ed7;
    void *sphere = ((void *(__thiscall *)(void *))SP_GetTerrainSphere)(SP_NounManager());
    if (sphere != 0) {
        ((bool (__thiscall *)(void *, CivEventReq *))FUN_00c78420)(sphere, &req);
    }
}
// ---- items of slice s00cf6df0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" i32    FUN_00c75420(void *o);                    // 0x00c75420
extern "C" i32 FUN_00bd81d0(void *city);      // 0x00bd81d0 cCity::GetVehicleSpecialty
extern "C" u32 FNVHash(const char *s, u32 seed, int flag);      // 0x00932e80
extern u32 g_propList15fd918;                                   // 0x015fd918
extern u8   g_serTable[];               // 0x168caf0 .. 0x168cb44 (stride 0x1c)
extern u32  g_serVersion;               // 0x145f8dc
extern "C" i32   FUN_00bf01f0();                // 0x00bf01f0 count_specialty_cities (thiscall)
extern u32 g_1581b48, g_1581b4c, g_1581b50;
extern u8  g_1581bd0;
extern u32 g_1581bb4, g_1581bb8, g_1581bbc;
extern u32 g_1581bc0, g_1581bc4, g_1581bc8;
extern u8  g_1581bcc;
extern "C" i32  FUN_00b320d0();          // 0x00b320d0 GetPauseGateCount (thiscall)

// ---- items of slice s00cf8d70 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct cSPUIGlobalUI {
    void ShowOptionWindows(char show);                       // 0x00e042d0
};
}
namespace SP {
struct cCivUIRoot {
    uint32_t        mPad00[0x64 / 4];                        // +0x00 .. +0x63
    cSPUIGlobalUI*  mpGlobalUI;                              // +0x64
};
}
namespace SP {
struct cCivTrackRoot {
    uint32_t mPad00[0x80 / 4];                               // +0x00 .. +0x7f
    void*    mpTracked;                                      // +0x80
};
}
namespace SP {
struct cCivModeStrategy_s00cf_8d70 {
    uint32_t       mPad00[0xe8 / 4];                         // +0x00 .. +0xe7
    cCivTrackRoot* mpTrackRoot;                              // +0xe8
    cCivUIRoot*    mpUIRoot;                                 // +0xec

    void ShowOptionWindows();
    bool HasActiveTrack();
};
}
namespace SP {
struct cRangeOut {
    void*    mpFunc;                                         // +0x00
    uint32_t mArg;                                           // +0x04
};
}
namespace SP {
bool __cdecl FUN_00d09660(void* track);                      // 0x00d09660
}
namespace SP {
void __cdecl ForEachNode(cRangeOut* out, uint32_t* first, uint32_t* last,
                         void (__fastcall* fn)(void*), uint32_t extra);
}
// ---- items of slice s00cf8d70 end

// ---- items of slice s00cf9ba0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl SP_GetCurrentGameMode();          // 0x00b5b800
extern "C" void* __cdecl SP_GameTimeManager();             // 0x00b3d380
extern "C" void* __cdecl SP_EffectsManager();              // 0x0067ddd0
extern "C" void* __cdecl SP_PropertyManager();             // 0x0067de30
extern "C" void* __cdecl SP_BehaviorManager();             // 0x00b3d260
extern "C" void* __cdecl SP_PlanetModel();                 // 0x00b3d350
extern "C" void* __cdecl SP_TerraformingManager();         // 0x00b3d430
extern "C" void* __cdecl SP_GetGameTerrainCursor();        // 0x00b30d70
extern "C" void* __cdecl SP_GetCameraCtl();                // 0x00b3d280
extern "C" void* __cdecl SP_StarManager();                 // 0x00b3d2a0
extern "C" void* __cdecl SP_GameInputManager();            // 0x00b3d250
extern "C" void* __cdecl SP_00b3d3b0();                    // 0x00b3d3b0
extern "C" void* __cdecl SP_00b3d2b0();                    // 0x00b3d2b0
extern "C" void* __cdecl SP_0067ddc0();                    // 0x0067ddc0
extern "C" void* __cdecl SP_00c9efc0();                    // 0x00c9efc0
extern "C" void* __cdecl SP_01021260();                    // 0x01021260
extern "C" void* __cdecl SP_01021300();                    // 0x01021300
extern "C" void* __cdecl SP_EA_Messaging();                // 0x00883860
extern "C" void* __cdecl SP_0067cac0();                    // 0x0067cac0 (0 args)
extern "C" int   __cdecl FUN_00d004b0();                   // 0x00d004b0
extern "C" int   __cdecl FUN_00cf6e30();                   // 0x00cf6e30 (no arg)
extern "C" void* __cdecl FUN_00b18e00(void*);              // 0x00b18e00
extern "C" void* __stdcall FUN_00b3d4f0_1(int);            // 0x00b3d4f0 (1 arg, callee-cleans)
extern "C" int   __cdecl SP_01021230();                    // 0x01021230
extern "C" void  __cdecl FUN_00ba1c60(void*);              // 0x00ba1c60
extern "C" void  __cdecl FUN_00b6c280();                   // 0x00b6c280
extern "C" void  __cdecl FUN_01002ee0();                   // 0x01002ee0
extern "C" void* __cdecl FUN_00c30c80();                   // 0x00c30c80
extern "C" int   __cdecl SP_GetPropertyAsUint32(void*, unsigned, void**); // 0x004af210
extern "C" void  __cdecl FUN_00d1c610(int, int);           // 0x00d1c610 (obj, int)
extern "C" void  __cdecl FUN_00cfeac0();                   // 0x00cfeac0
extern "C" void  __cdecl FUN_00c9a080();                   // 0x00c9a080
extern "C" void  __cdecl operator_delete__(void*);         // 0x00f47380
extern "C" void* __cdecl SP_0067caf0(float,float,float,void*,int,float,float,float,int,int); // 0x0067caf0
extern "C" unsigned char DAT_0169d2bc;                       // 0x0169d2bc
extern "C" unsigned char DAT_0169d2cc;                       // 0x0169d2cc
extern "C" unsigned char DAT_015819b4;                       // 0x015819b4
extern "C" unsigned char DAT_01654c04;                       // 0x01654c04 game-mode tag
extern "C" unsigned char DAT_01667bac;                       // 0x01667bac
extern "C" unsigned char DAT_01667bae;                       // 0x01667bae
extern "C" unsigned char DAT_018c6de8;                       // 0x018c6de8
extern "C" unsigned char DAT_018c6d19;                       // 0x018c6d19
extern "C" unsigned char DAT_018c43e8;                       // 0x018c43e8
extern "C" unsigned char DAT_01581b54;                       // 0x01581b54
extern "C" unsigned char DAT_01581b58;                       // 0x01581b58
extern "C" unsigned char DAT_01581b5c;                       // 0x01581b5c
extern "C" unsigned char DAT_01581b78;                       // 0x01581b78
extern "C" unsigned char DAT_01581b7c;                       // 0x01581b7c
extern "C" unsigned char DAT_01581b80;                       // 0x01581b80
extern "C" unsigned char PTR_01581bd0;                       // 0x01581bd0
extern "C" unsigned char PTR_01581bd4;                       // 0x01581bd4
extern "C" void  __cdecl FUN_00401090();                      // 0x00401090
#define VTFN(p, slot)  ((*(void***)(p))[slot])
typedef void  (__thiscall* TFnV)(void*);
typedef void  (__thiscall* TFnVI)(void*, int);
typedef void  (__thiscall* TFnVII)(void*, int, int);
typedef void  (__thiscall* TFnPIV)(void*, int, void*);
typedef void* (__thiscall* TFnPUP)(void*, unsigned, int, void*);
typedef void* (__thiscall* TFnPU)(void*);
struct Civ;
struct Strat {
    char  __thiscall HasCivTutorialOccurred(int id);   // 0x00cf7830
    void  __thiscall MarkCivEventAsOccurred(int id);   // 0x00cf77f0
    int   __thiscall HasOccurred();                    // 0x00cf94b0
    void  __thiscall StartTechHint();                  // 0x00cf93b0
    int   __thiscall UpdateHintFlags();                // 0x00cfa120
    void  __thiscall CheckEvents();                    // 0x00cf9ba0
    void  __thiscall DoNext(int id, char rerun);       // 0x00cfa990
    void  __thiscall SignalCivEvent(int, float, float, int); // 0x00cfaab0 (ret 0x14)
    void  __thiscall PreGameModeTransition(int oldMode, int newMode); // 0x00cfa610 (ret 8)
    void* __thiscall GetLaunchMarker(int);             // 0x00cf7d40

    // Retail object layout (the dev PDB's cCivModeStrategy is the smaller
    // single-player variant, so names are by role).
    char  pad0[0x68];
    int   mCityInput;                                  // +0x68
    char  pad1[0x74];                                  // +0x6c
    int   miState_0xe0;                                // +0xe0
    void* mpEditor_0xe4;                               // +0xe4
    void* mpHintTarget_0xe8;                           // +0xe8
    void* mpSomething_0xec;                            // +0xec
    void* mpMode_0xf4;                                 // +0xf4 (result slot)
    char  pad2[0x0c];                                  // +0xf8
    void* mpUndo_0x104;                                // +0x104
    void* mpEditable_0x108;                            // +0x108
    void* mpPreloadA_0x10c;                            // +0x10c
    void* mpPreloadB_0x110;                            // +0x110
    char  pad3[0x0e];                                  // +0x114
    char  mbHintC_0x122;                               // +0x122
    char  mbHintB_0x123;                               // +0x123
    char  mbHintA_0x124;                               // +0x124
    char  mbHint0_0x125;                               // +0x125
    char  pad4[0x22];                                  // +0x126
    char  mbFirstCivEvent_0x148;                       // +0x148
};
struct Civ {
    int   __thiscall HasSpecialtyCity();        // 0x00bf0260  find_specialty_city
    int   __thiscall TechLevelRank();           // 0x00bf0f40
    int   __thiscall RefAtB0();                 // 0x00befab0
    void* __thiscall KeyLookup(int);            // 0x00bef980
    char  __thiscall HasFlag(void*);            // 0x00bef970
    void  __thiscall DoThing();                 // 0x00bdc4a0

    char  padC[0x40];                           // +0x00
    int   miField_0x40;                         // +0x40 (id copied to empire)
    char  pad0[0x298 - 0x44];
    int   miNumCityLevels_0x298;                // +0x298 (tech-level gate)
    int   mPad_0x29c_cityLevel;                 // +0x29c (copied from city)
    char  pad1[0x1ac];                          // +0x2a0
    void* mpCity_0x44c;                         // +0x44c
    char  pad2[0x6c];                           // +0x450
    int   miHintThreshold_0x4bc;                // +0x4bc
};
struct City {
    int   __thiscall GetSpecialty();            // 0x00bd81d0
    void  __thiscall Rebuild();                 // 0x00bd91e0
    char  pad0[0x29c];
    int   miState_0x29c;                        // +0x29c
};
struct Noun {
    Civ*  __thiscall GetPlayerCivilization();        // 0x00b25fb0
    void  __thiscall RemoveNounsOfType(int);         // 0x00b22650
    void* __thiscall GetCurrentTerrainSphere();      // 0x00f67d90
    void  __thiscall PreShutdown();                  // 0x00b25ee0
    void  __thiscall PostShutdown();                 // 0x00b25fe0
    void  __thiscall ProcessPending();               // 0x00b22960
};
struct GTM {
    void  __thiscall IncPauseGate(int);              // 0x00b32220
    void  __thiscall DecPauseGate(int);              // 0x00b32250
};
struct Cfg {
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
virtual void v10();
virtual void v11();
    virtual int  GetFlag(unsigned int);          // slot 0x30
};
struct HintObj {
    void  __thiscall Hint(int);                      // 0x00b706a0
    void  __thiscall HintClear(int);                 // 0x00b707a0
};
struct Sphere {
    char  __thiscall Query(int);                     // 0x00c772c0
};
struct TriggerMgr {
    int  __thiscall PostAction(int id, void* target, int a);           // 0x00ae09b0
    void __thiscall PostTrigger(const char* name, int a, int b,
                                int c, int d, int e);                  // 0x00ae0930
};
struct ActionTarget {
    ActionTarget(void*);                       // 0x00ad7a30
    ~ActionTarget();                           // 0x00ad7ad0
    int pad0;
    int pad1;
};
struct DayStats {
    char pad0[0xac];
    int  miCountAC;                            // +0xac
    int  miCountB0;                            // +0xb0
    void __thiscall SysGui();                  // 0x00c2e4e0
};
struct Msg5 {
    void*   mpVtbl;                            // +0x00
    int     miRef;                             // +0x04
    int     mPad[10];                          // +0x08
    unsigned int mData2;                       // +0x30
    int     mPad2;
    unsigned int mData3;                       // +0x38
    void __thiscall Destruct();                // 0x00421cf0
};
struct MsgServer {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
    virtual void v04();
    virtual void Post(unsigned, void*, int);
};
struct CamCtl {
    void __thiscall LookAt(void* a, void* b, int c);   // 0x00b12dd0
    void __thiscall F1(float, float, float);           // 0x00b10340
    void __thiscall F2(float, float, float);           // 0x00b10540
};
struct SecBase {
virtual void s00();
virtual void s01();
virtual void s02();
virtual void s03();
virtual void s04();
virtual void s05();
    virtual void SetKey(int, void*);                   // slot 0x18
};
struct Universe {
    void* __thiscall GetPlanet(int, int);              // 0x00c713e0
    void  __thiscall Erase9(int);                      // 0x00c71560
    void  __thiscall EraseKeyBC();                     // 0x00c73310
    void  __thiscall EraseKeyD0();                     // 0x00c73330
};
struct PropMgr {
virtual void p00();
virtual void p01();
virtual void p02();
virtual void p03();
virtual void p04();
virtual void p05();
virtual void p06();
virtual void p07();
virtual void p08();
virtual void p09();
virtual void p10();
    virtual char Test(void*);                          // slot 0x2c
};
struct StarMgr {
    void* __thiscall Find(void* planet, int zero);      // 0x00bb5990
};
struct BehaviorMgr {
virtual void b00();
virtual void b01();
virtual void b02();
virtual void b03();
virtual void b04();
virtual void b05();
virtual void b06();
virtual void b07();
virtual void b08();
virtual void b09();
virtual void b10();
virtual void b11();
    virtual void Clear();                              // slot 0x30
};
struct SpeciesProfile {
    void __thiscall GetUiName(void*);                  // 0x004da330
};
struct ModeSub {
virtual void m00();
virtual void m01();
virtual void m02();
    void __thiscall Fn0ed0();                          // 0x00cf0ed0
};
struct CommunityEditor {
    char __thiscall IsActive();                        // 0x00d09660
    int  __thiscall GetResult();                       // 0x00d09670
    void __thiscall Deactivate(int, int);              // 0x00d100b0
};
struct C20 {
    void __thiscall Clear();                           // 0x007b1950
};
struct EditObj {
    int   __thiscall Active();                         // 0x00c8b370 (0 args)
    void* __thiscall Lookup(unsigned int, void**);     // 0x00c8b370 (key, out)
};
struct PM {
    void __thiscall SetPlanet(void*);                  // 0x00b8d8a0
};
struct HintTarget {
    void __thiscall Reset(int);                        // 0x00ce8ee0
    void __thiscall Prep();                            // 0x00ce97e0
};
struct Preload {
    void __thiscall Free();                            // 0x007cfc60
};
struct RTree {
    void* __thiscall Find(unsigned int* key, void** out); // 0x00e5c780
};
struct VehicleTree {
    void __thiscall Fn7540();                          // 0x00dc7540
};
struct Sub4 {
    void __thiscall Fn86d0();                          // 0x00cf86d0
};
struct InputState {
    void __thiscall OnMouseWheel(int, float, float, int); // 0x00697b40
};
struct WStr {
    unsigned short* mpBegin;
    unsigned short* mpEnd;
    unsigned short* mpCapacity;
    void __thiscall Assign(void*);                     // 0x00b6f380
    void __thiscall Append(const unsigned short*);     // 0x005c3d90
};
struct UIHints {
    void __thiscall Show(int);                    // 0x0067c830
    void __thiscall Show2(int, int);              // 0x0067c8c0
    void __thiscall Apply();                      // 0x0067aaf0
};
struct SubObj_s00cf_9ba0 {
    int  __thiscall Rel();                        // 0x00e2f270
};
struct GameInput {
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
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
    virtual void Signal(int, float, float, int);  // slot 0x60
};
static int CivFlag(void* civ, int key) {
    Civ* c = (Civ*)civ;
    return c->HasFlag(c->KeyLookup(key));
}
extern "C" TriggerMgr* __cdecl GetTriggerMgr_s00cf_9ba0();               // 0x00b3d4d0
extern "C" Noun* __cdecl SP_NounManager1(int);                // 0x00b3d300 (with arg)
extern "C" DayStats* __cdecl FUN_00b26930();                  // 0x00b26930
// ---- items of slice s00cf9ba0 end

// ---- items of slice s00cfab90 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct tVecData {
    int     m00;         // +0x00
    void*   mItems[2];   // +0x04  begin, +0x08  end
};
struct cGameNounManager {
    tVecData* GetGameDataVector(void* a, void* b, void* c, void* d, void* e);  // 0x00b21340
    void*     CreateNoun(void* id);                                            // 0x00b20c60
};
struct cCivModeStrategy_s00cf_ab90 {
    void* GetNumberedCity(int index);    // 0x00cfb610
};
void* NounManager();   // 0x00b3d300
// ---- items of slice s00cfab90 end

// ---- items of slice s00cfd3a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
enum {
    kGameCiv = 0x1654C04,
    kGameCivNoTutorial = 0x1654C05
};
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
};
struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};
struct ISpatialObject {
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
    virtual const Vector3& GetPosition();                       // +0x2c
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
    virtual void* GetModel();                                   // +0xac
};
struct cCityHall {
    uint32_t pad0[13];
    ISpatialObject mSpatial;               // +0x34
};
struct cCity_s00cf_d3a0 {
    void* vftable;
    uint32_t pad04[0x120 / 4 - 1];
    ISpatialObject mSpatial;               // +0x120
    cCityHall* GetCityHall();              // 0x00bd9b40
    void GetCameraSetup(Vector3& pos, float& distance);   // 0x00bd7f70
};
struct cSpeciesProfile_s00cf_d3a0 {
    uint32_t pad0[0x504 / 4];
    uint32_t mEffectAnchor;                // +0x504
};
struct cTribeList {
    int* mpBegin;
    int* mpEnd;
    bool empty() const { return mpBegin == mpEnd; }
};
struct cCivFlagsTarget {
    uint8_t pad0[0x2e0];
    bool mbFlag0;                          // +0x2e0
    bool mbFlag1;                          // +0x2e1
    bool mbFlag2;                          // +0x2e2
    bool mbFlag3;                          // +0x2e3
    bool mbFlag4;                          // +0x2e4
    bool mbFlag5;                          // +0x2e5
    bool mbFlag6;                          // +0x2e6
    void FUN_be88d0(void* p);              // 0x00be88d0
    void FUN_bd7e40();                     // 0x00bd7e40
    void FUN_bd9060(struct cCivilization_s00cf_d3a0* civ);   // 0x00bd9060
    void FUN_bd9140(struct cCivilization_s00cf_d3a0* civ);   // 0x00bd9140
    void FUN_bd7ea0();                     // 0x00bd7ea0
    void FUN_bdb0b0();                     // 0x00bdb0b0
    void FUN_be4b30(struct cCivilization_s00cf_d3a0* civ);   // 0x00be4b30
};
struct cCivilization_s00cf_d3a0 {
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
    virtual void* GetFocus(int a, int b);  // +0x4c
    uint32_t pad04[(0x44c - 4) / 4];
    cCivFlagsTarget* mpFlagsTarget;        // +0x44c
    cTribeList* GetTribes();               // 0x00bef6c0
    cSpeciesProfile_s00cf_d3a0* GetProfile();         // 0x00bef950
    int GetTool(uint32_t id);              // 0x00bef980
    bool HasTool(int tool);                // 0x00bef970
};
struct cGameNounManager_s00cf_d3a0 {
    void* GetCurrentTerrainSphere();       // 0x00f67d90
    cCity_s00cf_d3a0* GetPlayerCity();                // 0x00b25c30
    cCivilization_s00cf_d3a0* GetPlayerCivilization();   // 0x00b25fb0
};
cGameNounManager_s00cf_d3a0* NounManager_s00cf_d3a0();           // 0x00b3d300
uint32_t GetCurrentGameMode();             // 0x00b5b800
struct cTerrainSphereHelper { void SetSpecies(const ResourceKey* key); };   // 0x00cf6dc0
struct cGonzagoModelWorld {
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
virtual void v9c();
virtual void va0();
virtual void va4();
virtual void va8();
virtual void vac();
    virtual void vb0();
    virtual void SetModelVisible(void* model, int visible);     // +0xb4
    virtual void SetModelLOD(void* model, float distance);      // +0xb8
virtual void vbc();
virtual void vc0();
virtual void vc4();
    virtual void SetModelEffect(void* model, uint32_t id, float* value, int a, int b);   // +0xc8
};
cGonzagoModelWorld* GonzagoModelWorld();   // 0x00b3d520
struct cCameraManager_s00cf_d3a0 {
    uint8_t pad0[0x364];
    bool mbLocked;                         // +0x364
};
cCameraManager_s00cf_d3a0* CameraManager();           // 0x00b3d280
struct cGameInputManager {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual void SetHandler(void* handler, int a, int b);       // +0x20
    uint8_t pad04[0x110 - 4];
    int mLockCount;                        // +0x110
};
cGameInputManager* GameInputManager_s00cf_d3a0();     // 0x00b3d250
struct cGameTimeManager {
    void IncPauseGate(uint32_t reason);    // 0x00b32220
};
cGameTimeManager* GameTimeManager_s00cf_d3a0();       // 0x00b3d380
__forceinline void PauseForHint()
{
    cGameTimeManager* timeManager = GameTimeManager_s00cf_d3a0();
    timeManager->IncPauseGate(0x4bf38a7);
}
struct cPreloadParams {
    uint32_t mTypeID;
    uint16_t mPriority;
    uint16_t mFlags;
};
struct cResourceManager {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
    virtual bool IsLoaded(const ResourceKey* key);               // +0x18
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
    virtual void Preload(const ResourceKey* key, const cPreloadParams* params);   // +0x4c
};
cResourceManager* ResourceManager();       // 0x00401010
struct cKeyVector {                        // eastl::vector<ResourceKey, sp_vector_allocator>
    ResourceKey* mpBegin;
    ResourceKey* mpEnd;
    ResourceKey* mpCapacity;
    uint32_t mAllocator[2];
    int size() const { return (int)(mpEnd - mpBegin); }
};
struct cEventLog { void FUN_dd6d70(); };   // 0x00dd6d70
cEventLog* EventLog();                     // 0x00b3d3e0
struct cCameraMessage {
    uint32_t data[8];
    float mDistance;                       // +0x20
    uint32_t pad24[3];
    cCameraMessage(void* target);          // 0x00ad7a30
    cCameraMessage(const Vector3& pos, void* from);   // 0x00ad79d0
    ~cCameraMessage();                     // 0x00ad7ad0
    void* GetTarget();                     // 0x00ad7b70
};
void* MakeCameraTarget(void* p);           // 0x00b18e00
void* FindNearestReachableCommodity(void* target, int a);   // 0x00dcd720
struct cMessageManager {
    void PostMessage(uint32_t id, void* msg, int a);     // 0x00ae09b0
    void PostString(const char* name, int a, int b, int c, int d, int e);   // 0x00ae0930
    uint32_t GetTransitionID(const char* name);          // 0x00ad7db0
};
cMessageManager* MessageManager();         // 0x00b3d4d0
struct IMessageServer {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
    virtual void Post(uint32_t id, int a, int b);                 // +0x14
    virtual void PostDelayed(uint32_t id, void* msg, int a, int b);   // +0x18
};
IMessageServer* MessageServer();           // 0x0067dcc0
struct cConfigManager_s00cf_d3a0 {
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
    virtual uint32_t GetConfig(uint32_t id);                    // +0x30
};
cConfigManager_s00cf_d3a0* ConfigManager();           // 0x0067dd30
struct cMissionHooks { void FUN_b27170(); };   // 0x00b27170
cMissionHooks* MissionHooks();             // 0x00b3d340
struct cTutorialSystem {
    void StartModeTutorial(int a, uint32_t mode, int b);  // 0x00e3e350
};
cTutorialSystem* TutorialSystem();         // 0x00b3d410
struct cCivUIResult {
    uint32_t pad0[3];
    uint8_t* mpData;                       // +0x0c
    void FUN_7eb820(int a);                // 0x007eb820
};
struct cCivUI {
    cCivUIResult* ShowPanel(int id, Vector3 pos);   // 0x00ae37c0
    void FUN_ae5930();                     // 0x00ae5930
    void FUN_ae3b30(int a, int b);         // 0x00ae3b30
    void UpdateMinimapCityIcon(uint32_t a);   // 0x00ae4ec0
    void FUN_ae59a0();                     // 0x00ae59a0
};
cCivUI* CivUI();                           // 0x00b26930
struct cHintData;
struct cHintManager {
    void ShowHint(Vector3 pos, cHintData* data, int a, float ox, float oy, float oz, int b, int c);   // 0x0067aaf0
};
cHintManager* GetHintManager();            // 0x0067caf0
struct cHintsB { void Set(uint32_t id, uint32_t* anchor); };   // 0x0060d860
cHintsB* GetHintsB();                      // 0x0067cb30
struct cAchievementsController {
    void Trigger(uint32_t id, int a, int b);   // 0x00676ed0
};
cAchievementsController* AchievementsController_s00cf_d3a0();   // 0x00675250
struct cMissionLog { void FUN_e2f270(int a); };   // 0x00e2f270
cMissionLog* MissionLog();                 // 0x00b3d4f0
struct cSimulator {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
    virtual void SetEnabled(int a, int b);                      // +0x10
};
cSimulator* FUN_00bd83e0();
struct cTerrainCursor {
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
    virtual void Refresh();                                     // +0x64
};
cTerrainCursor* GetGameTerrainCursor();    // 0x00b30d70
float GetElapsedSeconds();                 // 0x00805080
struct cHintGlobal { void FUN_cfa3b0(); }; // 0x00cfa3b0
extern Vector3 kHintPosSea;                // 0x01581b60
extern Vector3 kHintPosA;                  // 0x01581b18
extern Vector3 kHintPosB;                  // 0x01581b24
extern Vector3 kHintPosC;                  // 0x01581b30
extern cHintData kHintDataA;               // 0x01581bcc
extern cHintData kHintDataSea;             // 0x01581bd0
extern cHintData kHintDataC;               // 0x01581bd8
extern cHintGlobal kHintGlobal;            // 0x01581bdc
struct cEditorResult {
virtual void v00();
virtual void v04();
    virtual void Release();                // +0x08
    uint32_t mEditorID;                    // +0x0c
    uint32_t pad10;
    uint32_t mExitReason;                  // +0x14
    ResourceKey mSpeciesKey;               // +0x18
    uint32_t pad24[8];
    bool mbCancelled;                      // +0x44
};
struct cEditorResultPtr {                  // AutoRefCount<cEditorResult>
    cEditorResult* mpObject;
    cEditorResultPtr& operator=(cEditorResult* p);   // 0x00572620
};
struct cMessage {
    void* vftable;
    uint32_t pad04;
    union { uint32_t mParam0; float mfParam0; cCity_s00cf_d3a0* mpCity; };   // +0x08
    uint32_t pad0c;
    void* mpParam1;                        // +0x10
    uint32_t pad14;
    float mfParam2;                        // +0x18
    uint32_t pad1c;
    float mfParam3;                        // +0x20
    uint32_t pad24;
    float mfParam4;                        // +0x28
};
struct cCityInputStrategy {
    uint32_t pad0;
    uint8_t mHandler[4];                   // +0x04 (input handler subobject)
    void SetMode(uint32_t mode);           // 0x00cf4c00
};
struct cCityDisplayStrategy {
    void OnCityMessage(uint32_t a);        // 0x00ce8de0
};
struct cCivModeStrategyRaw {
    uint8_t pad0[0xe8];
    struct { uint8_t pad[0x134]; bool mbFlag; }* mpInputStrategy;   // +0xe8
};
extern cCivModeStrategyRaw* gCivModeStrategy;   // 0x0169d2c8
namespace SP {
class cGonzagoSubsystem_s00cf_d3a0 { public:
    virtual void s00();
    uint32_t pad04[8];
};
}
namespace SP {
struct IMessageListener {
    virtual bool HandleMessage(uint32_t messageID, void* message);
};
}
namespace SP {
class cCivModeStrategy_s00cf_d3a0 : public cGonzagoSubsystem_s00cf_d3a0, public IMessageListener { public:
    bool mbReturningFromEditor;            // +0x28
    uint8_t pad29[3];
    uint32_t pad2c[10];
    cKeyVector mOptionalBakedItems;        // +0x54
    uint32_t pad68[32];
    cCityInputStrategy* mpInputStrategy;   // +0xe8
    cCityDisplayStrategy* mpDisplayStrategy;  // +0xec
    uint32_t padf0[4];
    cEditorResultPtr mEditorResult;        // +0x100
    uint32_t pad104[7];
    bool mbTutorialPending;                // +0x120
    bool mbTutorialRequested;              // +0x121
    uint8_t pad122[0x148 - 0x122];
    bool mbIntroPending;                   // +0x148

    virtual bool HandleMessage(uint32_t messageID, void* message);  // 0x00cfd3a0 (SP::cCivModeStrategy::HandleMessage)

    void NotifyDataDestroyed(void* p);     // 0x00cf8860
    void FUN_cfd220(void* p);              // 0x00cfd220
    void FinishMaxLoad();                  // 0x00cfb660
    void SendVehicleToCommodity();         // 0x00cf9ba0
    bool StartTechLevelUpgradeHintIfAppropriate();   // 0x00cfa0c0
    bool FUN_cf78d0();                     // 0x00cf78d0
    bool CanBuildSeaVehicles();            // 0x00cf75d0
    void FUN_cf8e00();                     // 0x00cf8e00
    void FUN_cf7520();                     // 0x00cf7520
    void FUN_cfa120();                     // 0x00cfa120
    void ShowIntro();                      // 0x00cf7ad0
    void* GetCameraTarget(int a);          // 0x00cf7d40
};
}
// ---- items of slice s00cfd3a0 end

// ---- items of slice s00cfe160 begin
#pragma warning(disable : 4100)
// ---- items of slice s00cfe160 end

// @ 0x00cf7360
void ShutdownGonzagoSubsystem()
{
    void *cm = CheatManager();
    void **vtbl = *(void ***)cm;
    typedef void (__thiscall *ExecFn)(void *self, const char *cmd);
    ((ExecFn)vtbl[0x1c / 4])(cm, "globalthermonuclearwar");
}

// @ 0x00cf7380
void cCivModeStrategy::OnMouseDown(u32 a, float x, float y, u32 b)
{
    typedef void (__thiscall *LISFn)(void *self, u32 a, float x, float y, u32 b);
    ((LISFn)FUN_00697ab0)((u8 *)this + 0x68, a, x, y, b);
    void *gim = GameInputManager();
    typedef void (__thiscall *GimFn)(void *self, u32 a, float x, float y, u32 b);
    ((GimFn)(*(void ***)gim)[0x54 / 4])(gim, a, x, y, b);
}

// @ 0x00cf73d0
void cCivModeStrategy::OnMouseMove(float x, float y, u32 a)
{
    typedef void (__thiscall *LISFn)(void *self, float x, float y, u32 a);
    ((LISFn)FUN_00697b20)((u8 *)this + 0x68, x, y, a);
    void *gim = GameInputManager();
    typedef void (__thiscall *GimFn)(void *self, float x, float y, u32 a);
    ((GimFn)(*(void ***)gim)[0x5c / 4])(gim, x, y, a);
}

// @ 0x00cf7420
void cCivModeStrategy::OnMouseUp(u32 a, float x, float y, u32 b)
{
    typedef void (__thiscall *LISFn)(void *self, u32 a, float x, float y, u32 b);
    ((LISFn)FUN_00697af0)((u8 *)this + 0x68, a, x, y, b);
    void *gim = GameInputManager();
    typedef void (__thiscall *GimFn)(void *self, u32 a, float x, float y, u32 b);
    ((GimFn)(*(void ***)gim)[0x58 / 4])(gim, a, x, y, b);
}

// @ 0x00cf7490
void *cCivModeStrategy::AsInterface(u32 iid)
{
    if (iid == 0x0116d389) {
        return this;
    }
    if (iid == 0x2f009dd0 && this != 0) {
        return (u8 *)this + 0x20;
    }
    return 0;
}

// @ 0x00cf7520
void FUN_00cf7520()
{
    ((void (__thiscall *)(void *, u32))FUN_00b32220)(GameTimeManager(), 0x4bf38a7);
    typedef void (__thiscall *StepFn)(void *self);
    V3 f = { -1.0f, -1.0f, 0.0f };
    U3 g1 = { g_1581bb4, g_1581bb8, g_1581bbc };
    ((StepFn)FUN_0067aaf0)(((void *(__cdecl *)(U3, void *, int, V3, int, int))FUN_0067caf0)(
        g1, &g_1581bcc, 0, f, 0, 0));
    U3 g2 = { g_1581bc0, g_1581bc4, g_1581bc8 };
    ((StepFn)FUN_0067aaf0)(((void *(__cdecl *)(U3, void *, int, V3, int, int))FUN_0067caf0)(
        g2, &g_1581bd0, 0, f, 0, 0));
}

// @ 0x00cf75d0
bool cCivModeStrategy::CanBuildSeaVehicles()
{
    void *civ = ((void *(__thiscall *)(void *))GetPlayerCivilization)(SP_NounManager());
    if (civ != 0) {
        return *(i32 *)((u8 *)civ + 0x298) >= 4;
    }
    return false;
}

// @ 0x00cf7600
bool cCivModeStrategy::CanBuildAirVehicles()
{
    void *civ = ((void *(__thiscall *)(void *))GetPlayerCivilization)(SP_NounManager());
    if (civ != 0) {
        return *(i32 *)((u8 *)civ + 0x298) >= 3;
    }
    return false;
}

// @ 0x00cf7630
void cCivModeStrategy::DoCVGCompletionAchievements()
{
    void *civ = ((void *(__thiscall *)(void *))GetPlayerCivilization)(SP_NounManager());
    void *ctrl = AchievementsController();
    typedef i32  (__thiscall *CountFn)(void *self, int idx, int flag);
    typedef void (__thiscall *AutoTestFn)(void *self, u32 hash, i32 count);
    typedef void (__thiscall *AwardFn)(void *self, u32 hash);
    ((AutoTestFn)FUN_00676e90)(ctrl, 0x256ed7f6, ((CountFn)FUN_00bf01f0)(civ, 0, 0));
    ((AutoTestFn)FUN_00676e90)(ctrl, 0x78d05a36, ((CountFn)FUN_00bf01f0)(civ, 1, 0));
    ((AutoTestFn)FUN_00676e90)(ctrl, 0xc15fda9b, ((CountFn)FUN_00bf01f0)(civ, 2, 0));
    ((AutoTestFn)FUN_00676e90)(ctrl, 0xb2352dc5, 1);
    void *sphere = ((void *(__thiscall *)(void *))SP_GetTerrainSphere)(SP_NounManager());
    if (*(u32 *)((u8 *)sphere + 0x128c) < 0x36ee80) {
        ((AwardFn)FUN_00676710)(ctrl, 0x6a5c80e9);
    }
    u32 kHash = 0x5dd433e;
    if (!((bool (__thiscall *)(void *, u32))FUN_00c772c0)(
            ((void *(__thiscall *)(void *))SP_GetTerrainSphere)(SP_NounManager()), kHash)) {
        ((AwardFn)FUN_00676710)(ctrl, 0x9d649052);
    }
    void *sphere3 = ((void *(__thiscall *)(void *))SP_GetTerrainSphere)(SP_NounManager());
    if (((i32 (__thiscall *)(void *))FUN_00c75420)(sphere3) == 2) {
        ((AwardFn)FUN_00676710)(ctrl, 0xa7b1c920);
    }
}

// @ 0x00cf7710
bool FUN_00cf7710(void *stream)
{
    u32 version = 3;
    void *o1 = ((void *(__thiscall *)(void *))(*(void ***)stream)[0x20 / 4])(stream);
    void *o2 = ((void *(__thiscall *)(void *))(*(void ***)o1)[0x18 / 4])(o1);
    ((bool (__cdecl *)(void *, u32 *, int, int))WriteUint32)(o2, &version, 1, 0);
    u8 *p = g_serTable;
    while (p < (u8 *)0x168cb44) {
        FUN_00befc00(stream, p);
        p += 0x1c;
    }
    return true;
}

// @ 0x00cf7770
bool FUN_00cf7770(void *stream)
{
    if (g_serVersion < 0x1c0007) {
        return true;
    }
    u32 version = 0;
    void *o1 = ((void *(__thiscall *)(void *))(*(void ***)stream)[0x20 / 4])(stream);
    void *o2 = ((void *(__thiscall *)(void *))(*(void ***)o1)[0x18 / 4])(o1);
    ((bool (__cdecl *)(void *, u32 *, int, int))ReadInt32)(o2, &version, 1, 0);
    if (version != 3) {
        return false;
    }
    u8 *p = g_serTable;
    while (p < (u8 *)0x168cb44) {
        FUN_00befbc0(stream, p);
        p += 0x1c;
    }
    return true;
}

// @ 0x00cf77f0
void __stdcall MarkCivEventAsOccurred(u32 id)
{
    CivEventReq req;
    req.m_id = id;
    req.m_pad04 = 0;
    req.m_hash = 0xaa9a8ed7;
    void *sphere = ((void *(__thiscall *)(void *))SP_GetTerrainSphere)(SP_NounManager());
    if (sphere != 0) {
        ((bool (__thiscall *)(void *, CivEventReq *))FUN_00c78420)(sphere, &req);
    }
}

// @ 0x00cf7830
int cCivModeStrategy::HasCivTutorialOccurred(u32 id)
{
    CivEventReq req;
    req.m_id = id;
    req.m_pad04 = 0;
    req.m_hash = 0xaa9a8ed7;
    void *sphere = ((void *(__thiscall *)(void *))SP_GetTerrainSphere)(SP_NounManager());
    if (sphere != 0) {
        if (((bool (__thiscall *)(void *, CivEventReq *))FUN_00c77c50)(sphere, &req)) {
            return 1;
        }
    }
    return 0;
}

// @ 0x00cf7880
bool cCivModeStrategy::IsEitherDialogueIdle()
{
    if (!((bool (__thiscall *)(void *))FUN_007cd9c0)(m_dialogue110)
        && !((bool (__thiscall *)(void *))FUN_007cfac0)(m_dialogue110)) {
        return false;
    }
    if (((bool (__thiscall *)(void *))FUN_007cd9c0)(m_dialogue114)
        || ((bool (__thiscall *)(void *))FUN_007cfac0)(m_dialogue114)) {
        return true;
    }
    return false;
}

// @ 0x00cf78d0
bool IsCityVehicleSpecialtyMismatch()
{
    void *civ = ((void *(__thiscall *)(void *))GetPlayerCivilization)(SP_NounManager());
    void *city = *(void **)((u8 *)civ + 0x44c);
    i32 spec = ((i32 (__thiscall *)(void *))FUN_00bd81d0)(city);
    i32 cur = *(i32 *)((u8 *)city + 0x29c);
    if ((cur == 0 && spec != 0)
        || (cur == 1 && spec != cur)
        || (cur == 2 && spec != cur)) {
        FUN_00bd91e0(city);
        return true;
    }
    return false;
}

// @ 0x00cf7920
void FUN_00cf7920()
{
    CivEventReq req;
    req.m_id = 0x6307841;
    req.m_pad04 = 0;
    req.m_hash = 0xaa9a8ed7;
    void *sphere = ((void *(__thiscall *)(void *))SP_GetTerrainSphere)(SP_NounManager());
    if (sphere != 0) {
        if (((bool (__thiscall *)(void *, CivEventReq *))FUN_00c77c50)(sphere, &req)) {
            return;
        }
    }
    req.m_id = 0x6307841;
    req.m_pad04 = 0;
    req.m_hash = 0xaa9a8ed7;
    void *sphere2 = ((void *(__thiscall *)(void *))SP_GetTerrainSphere)(SP_NounManager());
    if (sphere2 != 0) {
        ((bool (__thiscall *)(void *, CivEventReq *))FUN_00c78420)(sphere2, &req);
    }
    void *cfg = SP_ConfigManager();
    u32 v = ((u32 (__thiscall *)(void *, u32))(*(void ***)cfg)[0x30 / 4])(cfg, 0x4ea96cb);
    if (v == 0) {
        return;
    }
    {
        typedef void (__thiscall *IncFn)(void *self, u32 hash);
        ((IncFn)FUN_00b32220)(GameTimeManager(), 0x4bf38a7);
    }
    typedef void (__thiscall *StepFn)(void *self);
    ((StepFn)FUN_0067aaf0)(((void *(__cdecl *)(u32, u32, u32, void *, int, int, int, int))FUN_0067caf0)(
        g_1581b48, g_1581b4c, g_1581b50, &g_1581bd0, 0xbf800000, 0xbf800000, 0, 0));
}

// @ 0x00cf7a10
void cCivModeStrategy::SetDialogueTimed(u32 id)
{
    m_dialogue11c = 0xfa;
    m_dialogue118 = id;
}

// @ 0x00cf7a30
void cCivModeStrategy::ClearDialogue()
{
    m_dialogue11c = 0;
    m_dialogue118 = 0;
}

// @ 0x00cf7a40
bool cCivModeStrategy::IsNotCivEventA()
{
    return m_fieldB4 != 10;
}

// @ 0x00cf7a50
float GetTerrainEditModeHeight()
{
    void *sphere = ((void *(__thiscall *)(void *))SP_GetTerrainSphere)(SP_NounManager());
    i32 mode = ((i32 (__thiscall *)(void *))FUN_00c75420)(sphere);
    switch (mode) {
    case 0: return kDefaultTerrainC;
    case 2: return kDefaultTerrainA;
    }
    return kDefaultTerrainB;
}

// @ 0x00cf7a90
bool IsCivTriggerActive()
{
    i32 kind = *(i32 *)((u8 *)GetTriggerMgr() + 0x2c);
    if (kind != 1 && kind != 2) {
        return false;
    }
    if (*(u32 *)((u8 *)GetTriggerMgr() + 0x148) != 0x5fdca7a2) {
        if (*(u32 *)((u8 *)GetTriggerMgr() + 0x148) != 0xb1ea776a) {
            return false;
        }
    }
    return true;
}

// @ 0x00cf7ad0
void __fastcall FUN_00cf7ad0(void *self, void * /*edx*/)
{
    *(u8 *)((u8 *)self + 0x148) = 0;
    if (((i32 (__thiscall *)(void *, u32))FUN_00b320d0)(GameTimeManager(), 0x64beb65) > 0) {
        do {
            ((void (__thiscall *)(void *, u32))FUN_00b32250)(GameTimeManager(), 0x64beb65);
        } while (((i32 (__thiscall *)(void *, u32))FUN_00b320d0)(GameTimeManager(), 0x64beb65) > 0);
    }
    while (*(u32 *)((u8 *)FUN_00b3d4f0() + 0x54) != 0) {
        typedef void (__thiscall *StepFn)(void *self, int v);
        ((StepFn)FUN_00e2f270)(FUN_00b3d4f0(), 0);
    }
    MarkCivEventId(0x64e6666);
    MarkCivEventId(0x64e666f);
    MarkCivEventId(0x64e6671);
    MarkCivEventId(0x64e6673);
    MarkCivEventId(0x64e6674);
    MarkCivEventId(0x64e6676);
    MarkCivEventId(0x64e6678);
    MarkCivEventId(0x64e6679);
    void *list = (void *)g_propList15fd918;
    typedef bool (__thiscall *GetDescFn)(void *self, u32 hash);
    u32 h;
    if (((GetDescFn)FUN_006a25a0)(list, 0x61b67b6)) {
        h = FNVHash("CVG-CamRotate-MAC", 0x811c9dc5, 1);
    } else {
        h = FNVHash("CVG-CamRotate", 0x811c9dc5, 1);
    }
    ((void (__thiscall *)(void *, u32))FUN_0067c8c0)(((void *(__cdecl *)(u32, int))FUN_0067cac0)(h, 1), 0);
    ((void (__thiscall *)(void *, u32))FUN_0067c8c0)(((void *(__cdecl *)(u32, int))FUN_0067cac0)(0x5f011813, 1), 0);
    ((void (__thiscall *)(void *, u32))FUN_0067c8c0)(((void *(__cdecl *)(u32, int))FUN_0067cac0)(0xdb5f195a, 1), 0);
    ((void (__thiscall *)(void *, u32))FUN_0067c8c0)(((void *(__cdecl *)(u32, int))FUN_0067cac0)(0x90382acc, 1), 0);
}

// @ 0x00cf7d40
void *cCivModeStrategy::FindBuildableVehicle(u32 arg)
{
    void *civ = ((void *(__thiscall *)(void *))GetPlayerCivilization)(SP_NounManager());
    Vec4Arr *vec = (Vec4Arr *)((u8 *)civ + 0xb0);
    u32 count = (u32)(vec->m_end - vec->m_begin);
    u32 i = 0;
    if (count != 0) {
        u8 bl = (u8)arg;
        for (; i < count; i++) {
            void *elem = vec->m_begin[i];
            if (*(u32 *)((u8 *)elem + 0xb1c) != 0) continue;
            if (bl == 0) break;
            SubObj *sub = (SubObj *)((u8 *)elem + 0x34);
            if (((u8 (__thiscall *)(SubObj *))sub->m_vtbl[0x50 / 4])(sub) == 1) break;
        }
    }
    u32 n = (u32)(vec->m_end - vec->m_begin);
    if (i >= n) {
        return 0;
    }
    return vec->m_begin[i];
}

// @ 0x00cf8e00
namespace SP {
void cCivModeStrategy_s00cf_8d70::ShowOptionWindows()
{
    mpUIRoot->mpGlobalUI->ShowOptionWindows(1);
}
}  // namespace SP

// @ 0x00cf94b0
namespace SP {
bool cCivModeStrategy_s00cf_8d70::HasActiveTrack()
{
    if (mpTrackRoot && mpTrackRoot->mpTracked) {
        if (FUN_00d09660(mpTrackRoot->mpTracked))
            return true;
    }
    return false;
}
}  // namespace SP

// @ 0x00cf94e0
namespace SP {
void __cdecl ForEachNode(cRangeOut* out, uint32_t* first, uint32_t* last, void (__fastcall* fn)(void*), uint32_t extra)
{
    for (; first != last; ++first)
        fn((void*)(*first + extra));
    out->mpFunc = (void*)fn;
    out->mArg = extra;
}
}  // namespace SP

// @ 0x00cf9ba0
void Strat::CheckEvents()
{
    if ((void*)SP_GetCurrentGameMode() != (void*)0x01654c04)
        return;
    HintObj* obj = (HintObj*)FUN_00d004b0();
    if (obj == 0)
        return;
    if (((Cfg*)SP_ConfigManager())->GetFlag(0x4ea96cb) == 0)
        return;
    if (this->HasOccurred())
        return;

    if (!this->HasCivTutorialOccurred(0x64e666f)) {
        if (!this->HasCivTutorialOccurred(0x64e6666)) {
            this->mbFirstCivEvent_0x148 = 1;
            this->MarkCivEventAsOccurred(0x64e6666);
            GTM* gtm = (GTM*)SP_GameTimeManager();
            gtm->IncPauseGate(0x64beb65);
        }
        ((UIHints*)SP_0067cac0())->Show(FUN_00cf6e30());
        return;
    }
    if (!this->HasCivTutorialOccurred(0x64e6673)) {
        if (!this->HasCivTutorialOccurred(0x64e6671)) {
            this->MarkCivEventAsOccurred(0x64e6671);
            GTM* gtm = (GTM*)SP_GameTimeManager();
            gtm->IncPauseGate(0x64beb65);
        }
        ((UIHints*)SP_0067cac0())->Show(0x5f011813);
        return;
    }
    if (!this->HasCivTutorialOccurred(0x64e6676)) {
        if (!this->HasCivTutorialOccurred(0x64e6674)) {
            this->MarkCivEventAsOccurred(0x64e6674);
            GTM* gtm = (GTM*)SP_GameTimeManager();
            gtm->IncPauseGate(0x64beb65);
        }
        ((UIHints*)SP_0067cac0())->Show(0xdb5f195a);
        return;
    }
    if (!this->HasCivTutorialOccurred(0x64e6679)) {
        if (!this->HasCivTutorialOccurred(0x64e6678)) {
            this->MarkCivEventAsOccurred(0x64e6678);
            GTM* gtm = (GTM*)SP_GameTimeManager();
            gtm->IncPauseGate(0x64beb65);
        }
        ((UIHints*)SP_0067cac0())->Show(0x90382acc);
        return;
    }
    if (!this->HasCivTutorialOccurred(0x65cbcb4)) {
        this->MarkCivEventAsOccurred(0x65cbcb4);
        this->mbFirstCivEvent_0x148 = 0;
        void* marker = this->GetLaunchMarker(0);
        if (marker == 0)
            return;
        {
            ActionTarget target(FUN_00b18e00(marker));
            GetTriggerMgr_s00cf_9ba0()->PostAction(0x9e430ff6, &target, 0);
            GetTriggerMgr_s00cf_9ba0()->PostTrigger("CVG_SendVehicleToCommodity", 1, 0, 0, 0, 0);
        }
        return;
    }
    if (!this->HasCivTutorialOccurred(0x308f4ce8)) {
        obj->Hint(0x308f4ce8);
        if (!this->HasCivTutorialOccurred(0x6302c60)) {
            this->MarkCivEventAsOccurred(0x6302c60);
            GTM* gtm = (GTM*)SP_GameTimeManager();
            gtm->IncPauseGate(0x4bf38a7);
            V3 v = { *(float*)&DAT_01581b78, *(float*)&DAT_01581b7c, *(float*)&DAT_01581b80 };
            ((UIHints*)SP_0067caf0(v.x, v.y, v.z, &PTR_01581bd4, 0,
                                   -1.0f, -1.0f, 0.0f, 0, 0))->Apply();
        }
        return;
    }
    if (!this->HasCivTutorialOccurred(0x34646619)) {
        obj->Hint(0x34646619);
        if (!this->HasCivTutorialOccurred(0x654da12)) {
            this->MarkCivEventAsOccurred(0x654da12);
            ((Noun*)SP_NounManager1(1))->GetPlayerCivilization()->DoThing();
        }
        if (!this->HasCivTutorialOccurred(0x65509c9)) {
            this->MarkCivEventAsOccurred(0x65509c9);
            GTM* gtm = (GTM*)SP_GameTimeManager();
            gtm->IncPauseGate(0x4bf38a7);
            V3 v = { *(float*)&DAT_01581b54, *(float*)&DAT_01581b58, *(float*)&DAT_01581b5c };
            ((UIHints*)SP_0067caf0(v.x, v.y, v.z, &PTR_01581bd0, 0,
                                   -1.0f, -1.0f, 0.0f, 0, 0))->Apply();
        }
        return;
    }
    if (!this->HasCivTutorialOccurred(0xbb7368ed)) {
        obj->Hint(0xbb7368ed);
        return;
    }
    if (!this->HasCivTutorialOccurred(0x6d3814ed)) {
        Civ* civ = ((Noun*)SP_NounManager1(1))->GetPlayerCivilization();
        if (civ->HasSpecialtyCity() > 0) {
            obj->Hint(0x6d3814ed);
            return;
        }
    }
    if (!this->HasCivTutorialOccurred(0xced8b9d4)) {
        Civ* civ = ((Noun*)SP_NounManager1(2))->GetPlayerCivilization();
        if (civ->HasSpecialtyCity() > 0) {
            obj->Hint(0xced8b9d4);
            return;
        }
    }
    int diff = FUN_00b26930()->miCountAC - FUN_00b26930()->miCountB0;
    int rank = ((Noun*)SP_NounManager())->GetPlayerCivilization()->TechLevelRank();
    switch (rank) {
    case 0:
        if (!this->HasCivTutorialOccurred(0xe9b77b0b)) {
            if (diff < 2)
                return;
            obj->Hint(0xe9b77b0b);
            return;
        }
        break;
    case 1:
        if (!this->HasCivTutorialOccurred(0x92a23f21)) {
            if (diff < 2)
                return;
            obj->Hint(0x92a23f21);
            return;
        }
        break;
    case 2:
        if (!this->HasCivTutorialOccurred(0x9a2cac7f)) {
            if (diff < 2)
                return;
            obj->Hint(0x9a2cac7f);
            return;
        }
        break;
    default:
        return;
    }
    if (!this->HasCivTutorialOccurred(0x3120767d))
        obj->Hint(0x3120767d);
}

// @ 0x00cfa0c0
char __fastcall FUN_00cfa0c0(void* self)
{
    char result = 0;
    Sphere* terrain = (Sphere*)((Noun*)SP_NounManager())->GetCurrentTerrainSphere();
    Civ* civ = ((Noun*)SP_NounManager())->GetPlayerCivilization();
    bool canUpgrade = false;
    if (civ != 0)
        canUpgrade = civ->miNumCityLevels_0x298 >= 3;
    if (canUpgrade) {
        if (terrain->Query(0x50a2e65) == 0) {
            ((Strat*)self)->StartTechHint();
            result = 1;
        }
    }
    return result;
}

// @ 0x00cfa120
int __fastcall FUN_00cfa120(void* self)
{
    Noun* nm = (Noun*)SP_NounManager();
    Civ* civ = nm->GetPlayerCivilization();
    int thr = *(int*)((char*)civ + 0x4bc);
    if (civ->RefAtB0() <= thr)
        return 0;

    int* local = 0;
    int* eff = (int*)SP_EffectsManager();
    if (local) {
        int* t = local;
        local = 0;
        ((TFnV)VTFN(t, 1))(t);
    }
    (*(TFnPUP)VTFN(eff, 0x2c / 4))(eff, 0x9abfe031, 0, (void*)&local);    if (local) {
        int* lp = local;
        ((TFnVI)VTFN(lp, 2))(lp, 0);
    }
    char result = 1;
    if (*(int*)((char*)*(void**)((char*)self + 0xec) + 0x64) != 0) {
        if (CivFlag(civ, 0x36213c6a) || CivFlag(civ, 0x81299805) || CivFlag(civ, 0xfc716a94)) {
            *(char*)((char*)self + 0x125) = 1;
        } else if (CivFlag(civ, 0x008226d0) || CivFlag(civ, 0xfd05ab6d) || CivFlag(civ, 0x08a91f1e)) {
            *(char*)((char*)self + 0x124) = 1;
        } else if (CivFlag(civ, 0x2cdbd6a1) || CivFlag(civ, 0x4a78672c) || CivFlag(civ, 0x3221e759)) {
            *(char*)((char*)self + 0x123) = 1;
        } else if (CivFlag(civ, 0x0756d422) || CivFlag(civ, 0x045cdf1a) || CivFlag(civ, 0xc0617b2f)) {
            *(char*)((char*)self + 0x122) = 1;
        }
    }
    if (local) {
        int* lp = local;
        ((TFnV)VTFN(lp, 1))(lp);
    }
    return result;
}

// @ 0x00cfa360
void __cdecl FUN_00cfa360()
{
    GTM* gtm = (GTM*)SP_GameTimeManager();
    gtm->DecPauseGate(0x4bf38a7);
    Cfg* cfg = (Cfg*)SP_ConfigManager();
    if (cfg->GetFlag(0x4ea96cb) != 0) {
        ((Strat*)*(void**)0x0169d2c8)->CheckEvents();
        return;
    }
    void* sm = FUN_00b3d4f0_1(0);
    ((SubObj_s00cf_9ba0*)sm)->Rel();
}

// @ 0x00cfa3b0
void __cdecl FUN_00cfa3b0()
{
    GTM* gtm = (GTM*)SP_GameTimeManager();
    gtm->DecPauseGate(0x4bf38a7);
    Civ* civ = ((Noun*)SP_NounManager())->GetPlayerCivilization();
    City* city = (City*)civ->mpCity_0x44c;
    int spec = city->GetSpecialty();
    int state = city->miState_0x29c;
    bool keep = (state != 0 || spec == 0) && (state != 1 || spec == 1) &&
                (state != 2 || spec == 2);
    if (keep) {
        ((Strat*)*(void**)0x0169d2c8)->UpdateHintFlags();
        return;
    }
    city->Rebuild();
}

// @ 0x00cfa410
void __cdecl FUN_00cfa410()
{
    void* cam = SP_GetCameraCtl();
    if (cam != 0) {
        ((CamCtl*)cam)->LookAt(&DAT_0169d2cc, &DAT_015819b4, 1);
        ((CamCtl*)cam)->F1(0.0f, 0.0f, 0.0f);
        ((CamCtl*)cam)->F2(0.0f, 0.0f, 0.0f);
    }
    DAT_0169d2bc = 1;
    FUN_00401090();
    EditObj* obj = (EditObj*)SP_01021230();
    void* holder = 0;
    if (obj == 0)
        return;
    if (obj->Active() == 0)
        goto cleanup;
    {
        PropMgr* props = (PropMgr*)SP_PropertyManager();
        if (holder != 0) {
            void* old = holder;
            holder = 0;
            ((TFnV)VTFN(old, 1))(old);
        }
        void* key = obj->Lookup(0xe38475d9, &holder);
        if (props->Test(key) == 0)
            goto cleanup;
        Universe* uni = (Universe*)SP_01021260();
        void* planet = uni->GetPlanet(1, 1);
        ((PM*)SP_PlanetModel())->SetPlanet(planet);
        void* marker = 0;
        if (SP_GetPropertyAsUint32(holder, 0xe01c9c03, &marker) && marker != 0) {
            FUN_00d1c610((int)marker, 0);
        } else {
            uni->Erase9(-9);
            uni->EraseKeyBC();
            uni->EraseKeyD0();
            ((StarMgr*)SP_StarManager())->Find(uni, 0);
        }
        void* pm = SP_PlanetModel();
        ((SecBase*)((char*)pm + 4))->SetKey(0x2ccd1d2, &DAT_01654c04);
        void* tfm = SP_TerraformingManager();
        ((TFnPIV)VTFN(tfm, 6))(tfm, 0x2ccd1d2, &DAT_01654c04);
        void* x = SP_00b3d3b0();
        ((TFnPIV)VTFN((char*)x + 4, 6))((char*)x + 4, 0x2ccd1d2, &DAT_01654c04);
        FUN_00ba1c60(&DAT_01654c04);
        ((Noun*)SP_NounManager())->ProcessPending();
        DAT_0169d2bc = 0;
        {
            Msg5 msg;
            msg.mData2 = 0x1c3d2e0;
            msg.mpVtbl = (void*)0x13eb90c;
            msg.miRef = 0;
            msg.mpVtbl = (void*)0x13eb844;
            msg.mData3 = 0;
            ((MsgServer*)SP_EA_Messaging())->Post(msg.mData2, (void*)&msg, 0);
            msg.Destruct();
        }
    }
cleanup:
    if (holder != 0) {
        void* old = holder;
        holder = 0;
        ((TFnV)VTFN(old, 1))(old);
    }
}

// @ 0x00cfa610
void Strat::PreGameModeTransition(int oldMode, int newMode)
{
    if (((TFnPU)VTFN(this, 0x1c / 4))(this) == (void*)newMode)
        return;
    ((TFnVI)VTFN(this, 0x40 / 4))(this, newMode);

    if ((void*)oldMode != (void*)0x01654c04) {
        if ((void*)newMode == (void*)0x01654c04 && (void*)oldMode != (void*)0x00dbdba1)
            FUN_01002ee0();
        ((TFnV)VTFN(this, 0x48 / 4))(this);
        return;
    }

    void* eff = SP_EffectsManager();
    ((TFnVII)VTFN(eff, 0x98 / 4))(eff, 0xb, 0);
    FUN_00b6c280();
    this->miState_0xe0 = -1;

    if ((void*)newMode == (void*)0x01654c08) {
        void* p = SP_00b3d2b0();
        ((TFnV)VTFN(p, 0x5c / 4))(p);
        ((DayStats*)FUN_00b26930())->SysGui();    } else if ((void*)newMode == (void*)0x01654c06 || (void*)newMode == (void*)0x00dbdba1) {
        goto afterTeardown;
    }

    if (this->mpEditable_0x108) {
        ((C20*)this->mpEditable_0x108)->Clear();
        if (this->mpEditable_0x108) {
            void* p = this->mpEditable_0x108;
            this->mpEditable_0x108 = 0;
            ((TFnV)VTFN(p, 1))(p);
        }
    }
    ((Preload*)this->mpPreloadA_0x10c)->Free();
    ((Preload*)this->mpPreloadB_0x110)->Free();
    FUN_00cfeac0();
    ((BehaviorMgr*)SP_BehaviorManager())->Clear();
    ((VehicleTree*)SP_00c9efc0())->Fn7540();
    ((Sub4*)((char*)this - 4))->Fn86d0();

afterTeardown:
    if ((void*)newMode == (void*)0x01654c05) {
        void* cur = SP_GetGameTerrainCursor();
        ((TFnVI)VTFN(cur, 0x58 / 4))(cur, 0);
        ((Noun*)SP_NounManager())->RemoveNounsOfType((int)&DAT_018c6de8);
        ((Noun*)SP_NounManager())->RemoveNounsOfType((int)&DAT_018c6d19);
        void* empire = SP_01021300();
        Civ* civ = ((Noun*)SP_NounManager())->GetPlayerCivilization();
        *(int*)((char*)empire + 0x10) = civ->miField_0x40;
        WStr name;
        name.mpBegin = name.mpEnd = (unsigned short*)&DAT_01667bac;
        name.mpCapacity = (unsigned short*)&DAT_01667bae;
        ((SpeciesProfile*)FUN_00c30c80())->GetUiName(&name);
        ((WStr*)((char*)empire + 0xc))->Assign(&name);
        unsigned int key = 2;
        void* out = 0;
        void* node = ((RTree*)((char*)empire + 0x14))->Find(&key, &out);
        ((WStr*)((char*)empire + 0x3c))->Append(*(const unsigned short**)((char*)*(void**)node + 0x14));
        if ((((char*)name.mpCapacity - (char*)name.mpBegin) & ~1) > 2 && name.mpBegin)
            operator_delete__(name.mpBegin);
    } else if ((void*)newMode == (void*)0x01654c08 || newMode == -1 ||
               (void*)newMode == (void*)0x02ccd1d2) {
        ((Noun*)SP_NounManager())->RemoveNounsOfType((int)&DAT_018c6de8);
        ((Noun*)SP_NounManager())->RemoveNounsOfType((int)&DAT_018c6d19);
        ((Noun*)SP_NounManager())->RemoveNounsOfType((int)&DAT_018c43e8);
        void* nm = SP_NounManager();
        ((Noun*)nm)->PreShutdown();
        FUN_00c9a080();
        ((Noun*)SP_NounManager())->PostShutdown();
    }

    void* editor = this->mpEditor_0xe4;
    if (editor) {
        if ((void*)newMode == (void*)0x00dbdba1) {
            CommunityEditor* ce = *(CommunityEditor**)((char*)editor + 0x80);
            if (ce != 0 && ce->IsActive() != 0) {
                this->mpMode_0xf4 = (void*)ce->GetResult();
                ce->Deactivate(1, 1);
            }
            ((ModeSub*)editor)->Fn0ed0();
        } else {
            ((TFnV)VTFN(editor, 8 / 4))(editor);
        }
    }

    ((HintTarget*)this->mpHintTarget_0xe8)->Reset(0);
    if ((void*)newMode != (void*)0x00dbdba1) {
        void* hint = this->mpHintTarget_0xe8;
        if (hint) {
            ((HintTarget*)hint)->Prep();
            if (this->mpHintTarget_0xe8) {
                void* h = this->mpHintTarget_0xe8;
                ((TFnVI)VTFN(h, 0))(h, 1);
            }
            this->mpHintTarget_0xe8 = 0;
        }
        if (this->mpUndo_0x104) {
            void* u = this->mpUndo_0x104;
            ((TFnV)VTFN(u, 0x24 / 4))(u);
            if (this->mpUndo_0x104) {
                u = this->mpUndo_0x104;
                this->mpUndo_0x104 = 0;
                ((TFnV)VTFN(u, 2))(u);
            }
        }
    }

    void* mgr = SP_0067ddc0();
    if (mgr) {
        ((TFnVI)VTFN(mgr, 0x28 / 4))(mgr, 0);
        ((TFnV)VTFN(mgr, 0x24 / 4))(mgr);
    }
    ((BehaviorMgr*)SP_BehaviorManager())->Clear();
    ((TFnV)VTFN(this, 0x48 / 4))(this);
}

// @ 0x00cfa990
void Strat::DoNext(int id, char rerun)
{
    if ((void*)SP_GetCurrentGameMode() != (void*)0x01654c04)
        return;
    Strat* s = this;
    if (s->HasCivTutorialOccurred(id))
        return;
    HintObj* obj = (HintObj*)FUN_00d004b0();
    if (obj == 0)
        return;

    switch (id) {
    case 0x64e666f: {
        ((UIHints*)SP_0067cac0())->Show2(FUN_00cf6e30(), 1);
        GTM* gtm = (GTM*)SP_GameTimeManager();
        gtm->DecPauseGate(0x64beb65);
        break;
    }
    case 0x64e6673: {
        ((UIHints*)SP_0067cac0())->Show2(0x5f011813, 1);
        GTM* gtm = (GTM*)SP_GameTimeManager();
        gtm->DecPauseGate(0x64beb65);
        break;
    }
    case 0x64e6676: {
        ((UIHints*)SP_0067cac0())->Show2(0xdb5f195a, 1);
        GTM* gtm = (GTM*)SP_GameTimeManager();
        gtm->DecPauseGate(0x64beb65);
        break;
    }
    case 0x64e6679: {
        ((UIHints*)SP_0067cac0())->Show2(0x90382acc, 1);
        GTM* gtm = (GTM*)SP_GameTimeManager();
        gtm->DecPauseGate(0x64beb65);
        break;
    }
    case 0x64e667d: {
        ((UIHints*)SP_0067cac0())->Show2(0x178f5417, 1);
        GTM* gtm = (GTM*)SP_GameTimeManager();
        gtm->DecPauseGate(0x64beb65);
        ((SubObj_s00cf_9ba0*)FUN_00b3d4f0_1(0))->Rel();
        break;
    }
    default:
        obj->Hint(id);
        obj->HintClear(id);
        break;
    }
    s->MarkCivEventAsOccurred(id);
    if (rerun)
        this->CheckEvents();
}

// @ 0x00cfaab0
void Strat::SignalCivEvent(int a, float b, float c, int d)
{
    ((InputState*)((char*)this + 0x68))->OnMouseWheel(a, b, c, d);
    void* e = *(void**)((char*)this + 0xe8);
    if (e != 0) {
        if (((CommunityEditor*)*(void**)((char*)e + 0x80))->IsActive() == 0) {
            Strat* s = this;
            if (s->HasCivTutorialOccurred(0x64e6674)) {
                if ((void*)SP_GetCurrentGameMode() == (void*)0x01654c04) {
                    if (!s->HasCivTutorialOccurred(0x64e6676)) {
                        if (FUN_00d004b0() != 0) {
                            ((UIHints*)SP_0067cac0())->Show2(0xdb5f195a, 1);
                            GTM* gtm = (GTM*)SP_GameTimeManager();
                            gtm->DecPauseGate(0x64beb65);
                            s->MarkCivEventAsOccurred(0x64e6676);
                            s->CheckEvents();
                        }
                    }
                }
            }
        }
    }
    void* gim = SP_GameInputManager();
    ((GameInput*)gim)->Signal(a, b, c, d);
}

// @ 0x00cfb610
void* cCivModeStrategy_s00cf_ab90::GetNumberedCity(int index)
{
    cGameNounManager* nm = (cGameNounManager*)NounManager();
    tVecData* v = nm->GetGameDataVector((void*)0x00cd7d10, (void*)0x00d3d420,
                                        (void*)0x00acdff0, (void*)0x00b1e500,
                                        (void*)0x018c43e8);
    void** items = (void**)&v->mItems[0];
    if (index < (void**)items[1] - (void**)items[0])
        return ((void**)items[0])[index];
    return 0;
}

// @ 0x00cfd3a0
namespace SP {
bool cCivModeStrategy_s00cf_d3a0::HandleMessage(uint32_t messageID, void* message)
{
    cMessage* msg = (cMessage*)message;
    switch (messageID) {
    case 0x1a0219e: {
        void* p = msg->mpParam1;
        if (p) {
            switch (msg->mParam0) {
            case 1:
                GetCurrentGameMode();
                return false;
            case 3:
                FUN_cfd220(p);
                return false;
            case 4:
                NotifyDataDestroyed(p);
                return false;
            }
        }
        break;
    }

    case 0x164b4eb: {
        cCivilization_s00cf_d3a0* civ = NounManager_s00cf_d3a0()->GetPlayerCivilization();
        if (civ && civ->GetTribes()->empty()) {
            if (GetCurrentGameMode() == kGameCivNoTutorial)
                break;
            if (msg) {
                MessageServer()->PostDelayed(0x6130eb9, 0, 0, 0);
                cCity_s00cf_d3a0* city = msg->mpCity;
                cCityHall* hall = city->GetCityHall();
                cCameraMessage target(hall ? &hall->mSpatial : 0);
                float distance;
                Vector3 pos;
                city->GetCameraSetup(pos, distance);
                cCameraMessage locator(pos, target.GetTarget());
                locator.mDistance = distance;
                MessageManager()->PostMessage(0x115fa309, &target, 0);
                MessageManager()->PostMessage(0x1ad5e415, &locator, 0);
                MessageManager()->PostString("CVG_Lose", 1, 0, 0, 0, 0);
                CivUI()->ShowPanel(9, city->mSpatial.GetPosition());
                GetHintsB()->Set(0x5ab74e7a, &NounManager_s00cf_d3a0()->GetPlayerCivilization()->GetProfile()->mEffectAnchor);
            }
            AchievementsController_s00cf_d3a0()->Trigger(0xd456d958, 8, 1);
            return false;
        }
        cCityDisplayStrategy* display = mpDisplayStrategy;
        if (display) {
            display->OnCityMessage(msg->mParam0);
            return false;
        }
        break;
    }

    case 0x30c11c7: {
        cEditorResult* result = (cEditorResult*)message;
        if (!result)
            break;
        if (result->mEditorID == 0x66787bb) {
            mEditorResult = result->mbCancelled ? 0 : result;
            return false;
        }
        if (result->mEditorID != 0x116d51d)
            break;
        if (mbReturningFromEditor) {
            if (result->mExitReason == 0x98e03c0d) {
                mEditorResult = result->mbCancelled ? 0 : result;
                if (!result->mbCancelled) {
                    ((cTerrainSphereHelper*)NounManager_s00cf_d3a0()->GetCurrentTerrainSphere())->SetSpecies(&result->mSpeciesKey);
                    TutorialSystem()->StartModeTutorial(1, kGameCivNoTutorial, 1);
                    if (mbTutorialPending)
                        mbTutorialRequested = true;
                }
            }
            return true;
        }
        mEditorResult = result->mbCancelled ? 0 : result;
        return false;
    }

    case 0x5356bb5: {
        float start = msg->mfParam0;
        if (1.5f > GetElapsedSeconds() - start) {
            MessageServer()->PostDelayed(0x5356bb5, msg, 0, 0);
            return false;
        }
        FinishMaxLoad();
        return false;
    }

    case 0x44f1189: {
        if (GetCurrentGameMode() != kGameCiv)
            break;
        uint32_t id = msg->mParam0;
        if (id == MessageManager()->GetTransitionID("TRG2CVG_CivStart")) {
            if (!NounManager_s00cf_d3a0()->GetPlayerCity())
                CivUI()->FUN_ae5930();
            cGonzagoModelWorld* world = GonzagoModelWorld();
            ISpatialObject* hall = &NounManager_s00cf_d3a0()->GetPlayerCity()->GetCityHall()->mSpatial;
            world->SetModelVisible(hall->GetModel(), -1);
            world->SetModelLOD(hall->GetModel(), -1.0f);
            float value = 1.0f;
            world->SetModelEffect(hall->GetModel(), 0x13, &value, 1, 0);
            for (int i = 0; i < mOptionalBakedItems.size(); i++) {
                ResourceKey key = mOptionalBakedItems.mpBegin[i];
                if (key.instanceID != 0 && !ResourceManager()->IsLoaded(&key)) {
                    cPreloadParams params;
                    params.mTypeID = 0x2ea8fb98;
                    params.mPriority = 0;
                    params.mFlags = 2;
                    ResourceManager()->Preload(&key, &params);
                }
            }
            MessageServer()->PostDelayed(0x6270d2f, 0, 0, 0);
            return true;
        }
        if (id == MessageManager()->GetTransitionID("CVG_SendVehicleToCommodity")) {
            SendVehicleToCommodity();
            return false;
        }
        if (id == MessageManager()->GetTransitionID("CVG_PRE_NewCityAppears")) {
            if (ConfigManager()->GetConfig(0x4ea96cb) > 0) {
                cCivilization_s00cf_d3a0* civ = NounManager_s00cf_d3a0()->GetPlayerCivilization();
                if (civ->HasTool(civ->GetTool(0x756d422)) || civ->HasTool(civ->GetTool(0x45cdf1a)) ||
                    civ->HasTool(civ->GetTool(0xc0617b2f))) {
                    PauseForHint();
                    GetHintManager()->ShowHint(kHintPosSea, &kHintDataSea, 0, -1.0f, -1.0f, 0.0f, 0, 0);
                    return false;
                }
            }
            break;
        }
        if (id == MessageManager()->GetTransitionID("CVG_Capture") ||
            id == MessageManager()->GetTransitionID("CVG_Capture_Nuked")) {
            cCivilization_s00cf_d3a0* civ = NounManager_s00cf_d3a0()->GetPlayerCivilization();
            cCivFlagsTarget* target = civ->mpFlagsTarget;
            if (target->mbFlag0)
                target->FUN_be88d0(civ->GetFocus(0, 0));
            if (StartTechLevelUpgradeHintIfAppropriate() || FUN_cf78d0())
                return true;
            if (CanBuildSeaVehicles()) {
                FUN_cf8e00();
                FUN_cf7520();
                return true;
            }
            FUN_cfa120();
            return true;
        }
        if (id != MessageManager()->GetTransitionID("CVG_UnlockSea") &&
            id != MessageManager()->GetTransitionID("CVG_UnlockAir")) {
            if (id == MessageManager()->GetTransitionID("CVG_UnlockUFO")) {
                gCivModeStrategy->mpInputStrategy->mbFlag = true;
                PauseForHint();
                GameInputManager_s00cf_d3a0()->mLockCount++;
                cCameraManager_s00cf_d3a0* camera = CameraManager();
                if (camera)
                    camera->mbLocked = false;
                MessageServer()->Post(0x445f729, 0, 0);
                GetGameTerrainCursor()->Refresh();
                return false;
            }
            if (id == MessageManager()->GetTransitionID("CVG_Lose")) {
                MissionHooks()->FUN_b27170();
                EventLog()->FUN_dd6d70();
                PauseForHint();
                return false;
            }
            break;
        }
        PauseForHint();
        kHintGlobal.FUN_cfa3b0();
        return false;
    }

    case 0x53836de: {
        uint32_t id = msg->mParam0;
        bool flag = msg->mpParam1 != 0;
        Vector3 pos(msg->mfParam2, msg->mfParam3, msg->mfParam4);
        if (!id) {
            CivUI()->ShowPanel(0xb, pos);
            return false;
        }
        cCivUIResult* panel = CivUI()->ShowPanel(flag ? 0xc : 0xd, pos);
        panel->FUN_7eb820(10);
        *(uint32_t*)(panel->mpData + 0x24) = id;
        return false;
    }

    case 0x56cfe69: {
        void* commodity = FindNearestReachableCommodity(((cCivModeStrategy_s00cf_d3a0*)gCivModeStrategy)->GetCameraTarget(0), 0);
        if (!commodity)
            break;
        cCameraMessage target(MakeCameraTarget(commodity));
        MessageManager()->PostMessage(0x9b464f84, &target, 0);
        return false;
    }

    case 0x5668f43:
        CivUI()->FUN_ae3b30(0, 0);
        return false;

    case 0x5badd9f:
        CivUI()->UpdateMinimapCityIcon(msg->mParam0);
        return false;

    case 0x5bff9c8:
        CivUI()->FUN_ae59a0();
        return false;

    case 0x5dbc31e: {
        cCivilization_s00cf_d3a0* civ = NounManager_s00cf_d3a0()->GetPlayerCivilization();
        cCivFlagsTarget* target = civ->mpFlagsTarget;
        if (target && target->mbFlag0) {
            target->FUN_be88d0(civ->GetFocus(0, 0));
            return false;
        }
        break;
    }

    case 0x5dfb77f: {
        cCivilization_s00cf_d3a0* civ = NounManager_s00cf_d3a0()->GetPlayerCivilization();
        cCivFlagsTarget* target = civ->mpFlagsTarget;
        if (target && target->mbFlag2) {
            target->FUN_be4b30(civ);
            return false;
        }
        break;
    }

    case 0x5dfb3c8: {
        cCivFlagsTarget* target = NounManager_s00cf_d3a0()->GetPlayerCivilization()->mpFlagsTarget;
        if (target && target->mbFlag1) {
            target->FUN_bd7e40();
            return false;
        }
        break;
    }

    case 0x5dfb782: {
        cCivilization_s00cf_d3a0* civ = NounManager_s00cf_d3a0()->GetPlayerCivilization();
        cCivFlagsTarget* target = civ->mpFlagsTarget;
        if (target && target->mbFlag3) {
            target->FUN_bd9060(civ);
            return false;
        }
        break;
    }

    case 0x5f4d02a: {
        cCivilization_s00cf_d3a0* civ = NounManager_s00cf_d3a0()->GetPlayerCivilization();
        cCivFlagsTarget* target = civ->mpFlagsTarget;
        if (target && target->mbFlag5) {
            target->FUN_bd9140(civ);
            return false;
        }
        break;
    }

    case 0x5dfb786: {
        if (GetCurrentGameMode() != kGameCiv)
            break;
        cCivFlagsTarget* target = NounManager_s00cf_d3a0()->GetPlayerCivilization()->mpFlagsTarget;
        if (target && target->mbFlag4) {
            target->FUN_bd7ea0();
            return false;
        }
        break;
    }

    case 0x604bf01: {
        cCivFlagsTarget* target = NounManager_s00cf_d3a0()->GetPlayerCivilization()->mpFlagsTarget;
        if (target && target->mbFlag6) {
            target->FUN_bdb0b0();
            return false;
        }
        break;
    }

    case 0x66e0e11:
        FUN_00bd83e0()->SetEnabled(1, 0);
        return false;

    case 0x6270d2f:
        if (ConfigManager()->GetConfig(0x4ea96cb) > 0) {
            PauseForHint();
            GetHintManager()->ShowHint(kHintPosA, &kHintDataA, 0, -1.0f, -1.0f, 0.0f, 0, 0);
            GetHintManager()->ShowHint(kHintPosB, &kHintDataA, 0, -1.0f, -1.0f, 0.0f, 0, 0);
            GetHintManager()->ShowHint(kHintPosC, &kHintDataC, 0, -1.0f, -1.0f, 0.0f, 0, 0);
            MissionLog()->FUN_e2f270(1);
            return false;
        }
        break;

    case 0x670eccd:
        if (ConfigManager()->GetConfig(0x4ea96cb) == 0 && mbIntroPending) {
            ShowIntro();
            return false;
        }
        break;

    case 0x679c40d:
        if (GetCurrentGameMode() == kGameCiv) {
            mpInputStrategy->SetMode(ConfigManager()->GetConfig(0x679b873));
            GameInputManager_s00cf_d3a0()->SetHandler(mpInputStrategy->mHandler, 0, 0);
        }
        break;
    }
    return false;
}
}  // namespace SP

// @ 0x00cfe160
void __cdecl FUN_00cfe160()
{
}

// @ 0x00cfe5b0
void __cdecl FUN_00cfe5b0()
{
}
