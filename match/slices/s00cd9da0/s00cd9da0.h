// Declarations for slice s00cd9da0 (tribe-mode global game setup + SP::cTribeModeStrategy).
// Callees are external (relocated) in the original; PDB names where known.
#pragma once
#include "types.h"

struct cMotiveTuning;
struct cGameData;
struct cTerrainSphere;
struct cTribeModeStrategy;

// --- externals reached by the two functions ---------------------------------
void  cMotiveTuning_Init(cMotiveTuning* t, int hash);           // 0x00B71480
float FUN_00ce68f0(int a);                                      // 0x00CE68F0
void* GameTimeManager();                                        // 0x00B3D380
void  FUN_00b316d0();                                           // 0x00B316D0
void* GameInputManager();                                       // 0x00B3D250
void* FUN_0067de40();                                           // 0x0067DE40
int   FUN_006ab760(void* /*IMultiLanguage*/, const wchar_t*);   // 0x006AB760
unsigned FNVHash(const char*, unsigned);                        // 0x00932E80
void* FUN_0067ddc0();                                           // 0x0067DDC0
void* GonzagoModelWorld();                                      // 0x00B3D520
void* ModelManager();                                           // 0x0067DD80
void* FUN_0067de00(int);                                        // 0x0067DE00
void* FUN_00b3d230(int);                                        // 0x00B3D230
void  FUN_00b5cde0();                                           // 0x00B5CDE0
void* GetCameraCtl();                                           // 0x00B3D280
void* PlanetModel();                                            // 0x00B3D350
void  FUN_00b81720();                                           // 0x00B81720
void* NounManager();                                            // 0x00B3D300
void* SetGameDataOwner2();                                      // 0x00BFC5F0
void  FUN_00b146a0(void* a, int b, int c, void* d);             // 0x00B146A0
void  FUN_00b10760(void* cam, float a, float b, float c);       // 0x00B10760
void  FUN_00b11870(void* a, int b);                             // 0x00B11870
void  FUN_00b84a60(void* out, int n);                           // 0x00B84A60
void* GetCurrentTerrainSphere();                                // 0x00F67D90
void  FUN_00a1ad10(void* a);                                    // 0x00A1AD10
int   GetPropertyAsUint32Array(void* a, unsigned b, void* c, void* d, void* e); // 0x006A0840
void  FUN_00ff03b0(void* a, int b);                             // 0x00FF03B0
void  FUN_00c79f00(void* a, int b, int c);                      // 0x00C79F00

extern unsigned gTribeMotiveTable;                              // 0x01581208
extern uint32_t gTribeConfigName;                               // 0x0167EA54
extern float    gTribeF0;                                       // 0x01581280
extern uint32_t gTribePropId;                                   // 0x01581288

// --- SP::cTribeModeStrategy -------------------------------------------------
class cTribeModeStrategy {
public:
    uint32_t pad_00[0xe8/4];                                    // 0x000..0x0e8
    uint32_t mPosseInfos[0x74/4];                               // 0x0e8..0x15c
    uint32_t pad_15c[0x1490/4 - 0x15c/4];                       // 0x15c..0x1490

    void UpgradePlayerTribe();                                  // 0x00CDA370
};

void FUN_00cd9da0();                                            // 0x00CD9DA0
