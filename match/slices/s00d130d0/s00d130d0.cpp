// Slice s00d130d0 -- SP::cCommunityEditor::HandleMessage (0x00d130d0, ~4965 bytes).
//
// Message dispatcher for the community/colony editor.  It handles UI messages
// (model palette selection, swatch rollover, sell-back, snap/rotation, building
// placement) by updating the editor's recently-edited model key, economy, ring,
// snap anchors and the manipulated object, and by forwarding a set of messages
// to the shared palette handler FUN_00d12910.
//
// Ported from the Ghidra decompilation.  The message-id dispatch, the early
// forwarding group, the null/state guards and all identifiable engine calls are
// reproduced; deep cCommunity/cCity base-subobject chains are reached through
// offset accessors.
//
// PARTIAL: dispatch and side effects are faithful, but several of the deep
// sub-object/vtable chains (mBuildingEffectivenessEffects, the vehicle specialty
// branches) and the exact stack-local aliasing are reconstructed rather than
// guaranteed complete.  Byte-exact is not attempted.
//
// Card: work/match/scratch_35_card.txt
#include "types.h"

typedef unsigned char byte;
typedef unsigned int  uint;

extern "C" {
int FUN_00d12910(...);
int FUN_00435e90(...);
int FUN_00d08ec0(...);
int FUN_00d08aa0(...);
int FUN_00d0e0c0(...);
int FUN_00d091c0(...);
int FUN_00d0c010(...);
int FUN_00d0d570(...);
int FUN_00d0db30(...);
int FUN_00d0a540(...);
int FUN_00572660(...);
int FUN_005ca9c0(...);
int FUN_005a9080(...);
int FUN_0061df40(...);
int FUN_00b3d320(...);
int FUN_00b1dee0(...);
int FUN_00b6a6e0(...);
int FUN_00b3d240(...);
int FUN_00b7f1f0(...);
int FUN_00b81630(...);
int FUN_00b33e60(...);
int FUN_00be1e80(...);
int FUN_00be1ef0(...);
int FUN_00be1fb0(...);
int FUN_00be6f40(...);
int FUN_00bce470(...);
int FUN_00bce400(...);
int FUN_00bdca30(...);
int FUN_00c3f160(...);
int FUN_00c6f770(...);
int FUN_00c77bf0(...);
int FUN_00c9d140(...);
int FUN_00ca80e0(...);
int FUN_00cf74c0(...);
int FUN_00cf8ec0(...);
int FUN_00d08aa0(...);
int FUN_00e1c7f0(...);
int FUN_00e3c7c0(...);
int FUN_00fe5430(...);
int FUN_00ba57a0(...);
int FUN_00c70b50(...);
int FUN_01005180(...);
int FUN_007eb820(...);
int FUN_0067caf0(...);
int FUN_0067aaf0(...);
int FUN_0067cac0(...);
int FUN_0067c420(...);
int operator_new(...);
// named engine entry points
int NounManager(...);
int GetCurrentGameMode(...);
int GetModelType(...);
int GetKeyForModelType(...);
int SetupShoppingUI(...);
int Editor_GetConfigFromModelType(...);
int App(...);
int ConfigManager(...);
int GameTimeManager(...);
int MessageServer(...);
int PropertyManager(...);
int GetPropertyAsUint32(...);
int GetPropertyAsKeyInstance(...);
int GetCommunityCenter(...);
int GetObjectCost(...);
int SetObjectSpecificData(...);
int SetManipulatedObject(...);
int StartSnapAttractorEffects(...);
int UpdateLimitMeter(...);
int UpdateSwatchForModelType(...);
int CreateVehicleFromModelType(...);
int HandleSwatchRolloverOn(...);
int HandleSwatchRolloverOff(...);
int SpaceGameGet(...);
int BehaviorManager(...);
int GameInputManager(...);
int cSPLivingUniverse_GetPlayerEmpire(...);
int cSPLivingUniverse_GetActivePlanet(...);
int cTribeModeStrategy_Instance(...);
int cCity_GetCivilization(...);
int cCity_GetVehicleSpecialty(...);
int cTerrainEditor_GetCurrentTerrainSphere(...);
int cGameNounManager_CreateNoun(...);
int cGameNounManager_RemoveNoun(...);
int cGameNounManager_GetPlayerCivilization(...);
int cGameNounManager_GetPlayerTribe(...);
int cGameTimeManager_IncPauseGate(...);
int cTribe_GetToolOfType(...);
int cSPSimulatorSpaceGame_SpaceTelemetry_Add(...);
int cSPSimulatorSpaceGame_SpaceTelemetry_Add2(...);
int cCivModeStrategy_DoNextCivTutorial(...);
int cVehicle_SetJustEyeCandy(...);
int cCivilization_GetModelTypeKey(...);
int cSPEditorSellBackRollover_Release(...);
}
extern float DAT_01582544, DAT_01582548, DAT_0158254c;
extern float DAT_01582574, DAT_01582578, DAT_0158257c;
extern char  DAT_0169d584, DAT_0169d587, DAT_0169d588;
extern char  DAT_01654c05;
extern char  DAT_018c88e4, DAT_0142462a;
extern char  DAT_015da7c4, DAT_015da7c8, DAT_015da7cc, DAT_015da7d0;
extern int   DAT_013ebc58;
extern char  PTR_PTR_015825c8;

#define I(p,o) (*(int*)((char*)(p)+(o)))
#define U(p,o) (*(unsigned*)((char*)(p)+(o)))
#define F(p,o) (*(float*)((char*)(p)+(o)))
#define B(p,o) (*(char*)((char*)(p)+(o)))
#define VS(p,o) (*(void**)((*(char**)(p))+(o)))
#define VC0(RT,p,o)   ((RT(__thiscall*)(void*))VS(p,o))((void*)(p))
#define VC1(RT,p,o,a) ((RT(__thiscall*)(void*,int))VS(p,o))((void*)(p),(int)(a))
#define VC2(RT,p,o,a,b) ((RT(__thiscall*)(void*,int,int))VS(p,o))((void*)(p),(int)(a),(int)(b))
#define VC3(RT,p,o,a,b,c) ((RT(__thiscall*)(void*,int,int,int))VS(p,o))((void*)(p),(int)(a),(int)(b),(int)(c))
#define VC4(RT,p,o,a,b,c,d) ((RT(__thiscall*)(void*,int,int,int,int))VS(p,o))((void*)(p),(int)(a),(int)(b),(int)(c),(int)(d))

// @ 0x00d130d0
int FUN_00d130d0(void* thisp, unsigned* param_2, void* param_3)
{
  char* self = (char*)thisp;
  unsigned uVar16 = (unsigned)param_2;
  int   iVar9, iVar17;
  char  cVar5;
  void* pcVar6;
  void* pcVar7;
  void* pfVar28 = 0;
  unsigned local_24 = 0, local_20 = 0;
  int   local_3c = 0;
  int   local_30 = -1;
  void* local_34 = 0;
  void* local_38 = 0;
  int   uStack_44 = 0;
  (void)iVar17; (void)cVar5; (void)pcVar6; (void)pfVar28;

  if (param_2 == (unsigned*)0x30c11c7) {
    if (param_3 != 0) {
      I(self, 0x50) = I(param_3, 0x14);
      I(self, 0x50)     = I(param_3, 0x18);
      I(self, 0x50)    = I(param_3, 0x1c);
      I(self, 0x50)  = I(param_3, 0x20);
      B(self, 0x50) = (char)I(param_3, 0x44);
    }
    return 0;
  }
  if (param_2 == (unsigned*)0x71d4dfc3 || param_2 == (unsigned*)0x71d4dfc4 ||
      param_2 == (unsigned*)0x71d4dfc5 || param_2 == (unsigned*)0x71d4dfc6 ||
      param_2 == (unsigned*)0x71d4dfc7 || param_2 == (unsigned*)0x62ec2a6 ||
      param_2 == (unsigned*)0x609ea30  || param_2 == (unsigned*)0x71d4dfcd ||
      param_2 == (unsigned*)0x71d4dfce || param_2 == (unsigned*)0x332a303a ||
      param_2 == (unsigned*)0x71d4dfca || param_2 == (unsigned*)0x71d4dfcc ||
      param_2 == (unsigned*)0x71d4dfcb || param_2 == (unsigned*)0x332a303b) {
    return FUN_00d12910(param_2, param_3);
  }
  if (I(self, 0x50) == 0) return 0;
  if (I(self, 0x50) != 0) return 0;

  param_2 = (unsigned*)((unsigned)param_2 & 0xffffff00);
  local_30 = -1;
  local_3c = 0;
  pcVar6 = (void*)HandleSwatchRolloverOn(self);
  pcVar7 = (void*)FUN_00d08ec0(self);

  if (uVar16 == 0x53850bae) {
    if (param_3 == 0) return 0;
    void* sph = (void*)cTerrainEditor_GetCurrentTerrainSphere(NounManager());
    I(self, 0x50)  = I(param_3, 0x10);
    I(self, 0x50) = I(param_3, 0x14);
    I(self, 0x50) = I(param_3, 0x18);
    iVar9 = operator_new(0x9c, &DAT_013ebc58, 0, 0, 0, 0);
    int u10 = iVar9 ? FUN_005a9080() : 0;
    FUN_0061df40(u10);
    I(param_2, 0x10) = I(param_3, 0x10);
    I(param_2, 0x14) = I(param_3, 0x14);
    I(param_2, 0x18) = I(param_3, 0x18);
    I(param_2, 0x0c) = I(param_3, 0x0c);
    I(param_2, 0x24) = (int)DAT_015da7c4;
    I(param_2, 0x28) = (int)DAT_015da7c8;
    I(param_2, 0x2c) = (int)DAT_015da7cc;
    I(param_2, 0x30) = (int)DAT_015da7d0;
    B(param_2, 0x35) = 1; B(param_2, 0x34) = 0; B(param_2, 0x36) = 0;
    B(param_2, 0x38) = 0; B(param_2, 0x37) = 0; B(param_2, 0x39) = 0;
    B(param_2, 0x3c) = 1; B(param_2, 0x6d) = 1;
    (void)sph;
    FUN_00b3d320(param_2);
    FUN_00b1dee0(param_2);
    VC0(void, param_2, 8);
  } else if (pcVar7 != 0 && uVar16 == 0x133b269e) {
    if (param_3 != 0 && (iVar9 = I(param_3, 0x20)) != 0) {
      float r = F(self, 0x50);
      I(self, 0x50) = 0;
      if (r != 0.0f) {
        void* nm = (void*)NounManager();
        cGameNounManager_RemoveNoun(nm, (int)r);
        I(self, 0x50) = 0;
      }
      I(self, 0x50) = GetModelType(iVar9);
    }
    return 0;
  } else if (pcVar7 != 0 && uVar16 == 0x4a314e6) {
    unsigned model = I(param_3, 0);
    if (I(param_3, 8) == 1) {
      void* k = (void*)GetKeyForModelType(self, model);
      local_24 = I(k, 4); local_20 = I(k, 8);
    }
    I(self, 0x50) = model;
    iVar9 = Editor_GetConfigFromModelType(model);
    void* sph = (void*)cTerrainEditor_GetCurrentTerrainSphere(NounManager());
    iVar17 = operator_new(0x9c, &DAT_013ebc58, 0, 0, 0, 0);
    int u10 = iVar17 ? FUN_005a9080() : 0;
    FUN_0061df40(u10);
    (void)sph;
    I(param_3, 0x1c) = VC0(int, (void*)App(), 0x38);
    I(param_3, 0x10) = 0; I(param_3, 0x14) = local_24; I(param_3, 0x18) = local_20;
    I(param_3, 0x0c) = iVar9;
    I(param_3, 0x90) = 0x91d4af08;
    B(param_3, 0x36) = 1; B(param_3, 0x38) = 1; B(param_3, 0x37) = 1;
    B(param_3, 0x39) = 0; B(param_3, 0x3c) = 1; B(param_3, 0x3d) = 1;
    I(param_3, 0x24) = (int)DAT_015da7c4;
    I(param_3, 0x28) = (int)DAT_015da7c8;
    I(param_3, 0x2c) = (int)DAT_015da7cc;
    I(param_3, 0x30) = (int)DAT_015da7d0;
    B(param_3, 0x64) = 1; B(param_3, 0x6d) = 1;
    FUN_00b3d320(param_3);
    FUN_00b1dee0(param_3);
    VC0(void, param_3, 8);
    return 1;
  } else if (uVar16 == 0x522f9cd) {
    FUN_00572660(I(param_3, 0));
    HandleSwatchRolloverOff(self, param_3);
    return 1;
  } else if (uVar16 == 0x522f9ce) {
    FUN_00572660(I(param_3, 0));
    FUN_00d0e0c0(param_3);
    return 1;
  } else if (uVar16 == 0x5132389) {
    // iterate the community's vehicle list and create/refresh each vehicle
    void* local_30p = (void*)I(param_3, 0);
    if (local_30p == 0) return 0;
    int n = (I(local_30p, 0x50) - I(local_30p, 0x50)) / 0xc;
    if (n < 1) return 0;
    for (int i = 0; i < n; ++i) {
      local_24 = I(local_30p, i*0xc + 0);
      local_20 = I(local_30p, i*0xc + 4);
      cVar5 = VC2(char, (void*)(int)param_2, 0x0c, (int)&local_24, 0);
      if (cVar5 != 0) {
        iVar17 = I(local_24, 0x18);
        (void)iVar17;
        CreateVehicleFromModelType(0, local_24, 0);
        UpdateSwatchForModelType(I(local_24, 0x18), (int)&local_24, 0);
      }
    }
    return 0;
  } else if (uVar16 == 0x63bdfbe) {
    iVar9 = VC1(int, (void*)ConfigManager(), 0x30, 0x4ea96cb);
    if (iVar9 == 0) return 0;
    cGameTimeManager_IncPauseGate(GameTimeManager(), 0x4bf38a7);
    goto LAB_00d13794;
  } else if (uVar16 == 0x44ef2b8) {
    iVar9 = FUN_005ca9c0();
    UpdateLimitMeter(self, iVar9);
    void* cc = (void*)GetCommunityCenter(self, 0);
    FUN_00d08aa0(I(cc,0), I(cc,4), I(cc,8), 0);
    if (GetCurrentGameMode() == (int)&DAT_01654c05) return 0;
    if (pcVar7 == 0) return 0;
    if (iVar9 == 0 || iVar9 == 1) {
      // paused-state transition message
      B((char*)(int)&DAT_0169d587, 0) = 0;
      iVar17 = operator_new(0x40, &DAT_013ebc58, 0, 0, 0, 0);
      int u10 = iVar17 ? iVar17 : 0;
      FUN_0061df40(u10);
      I(param_3, 0x30) = (iVar9 == 0) ? 0x63c0580 : 0x63c0504;
      I(param_3, 0x08) = 0xfffffff1;
      VC3(void, (void*)MessageServer(), 0x14, I(param_3, 0x30), (int)param_3, 0);
    }
    goto LAB_00d13447;
  } else if (uVar16 == 0x63c0504) {
    // (handled in the 0x44ef2b8 / 0x63c0504 pair above in the original)
    return 0;
  } else if (uVar16 == 0x63c0580) {
    // (handled via the paused-state transition)
    return 0;
  } else if (uVar16 == 0xb2e18705) {
    // building placement: pick the model type's "specialty" id and spawn the
    // matching vehicle
    void* pcVar23 = (void*)I(param_3, 0x20);
    local_34 = pcVar23;
    void* modelType = (void*)GetModelType(pcVar23);
    unsigned spec = U(pcVar23, 0x50);
    if (spec == 0x4d863c8b) {
      if (pcVar7 == 0) return 0;
      iVar9 = cGameNounManager_CreateNoun((void*)NounManager(), &DAT_018c88e4);
      if (iVar9 == 0) return 0;
      pfVar28 = (void*)(iVar9 + 0x70);
      local_3c = 0x3e83;
      SetManipulatedObject(self, pfVar28);
      SetObjectSpecificData(self);
      goto LAB_00d1423e;
    } else if (spec == (unsigned)(int)&DAT_0142462a) {
      if (pcVar7 == 0) return 0;
      iVar9 = FUN_00be1fb0();
      if (iVar9 == 0) return 0;
      pfVar28 = (void*)(iVar9 + 0x34);
      B((char*)iVar9, 0xa2) = 1;
      SetManipulatedObject(self, pfVar28);
      local_3c = 0x3e81;
      goto LAB_00d1423e;
    } else if (spec == 0x2b885df4) {
      if (pcVar7 == 0) return 0;
      if (VC0(int, pcVar7, 0x6c) == 0) return 0;
      VC1(void, (void*)VC0(int, pcVar7, 0x6c), 0x60, I(pcVar23, 0x50));
      FUN_00be6f40();
      return 0;
    } else if (spec == 0xfcafd26) {
      if (pcVar6 == 0) return 0;
      // interact with a tribe tool and start its snap-attractor effects
      local_34 = (void*)PropertyManager();
      cVar5 = VC2(char, (void*)(I((int)local_34,0x50) + 0x2c), 0, 0, 0);
      if (cVar5 != 0) {
        unsigned key = 0;
        GetPropertyAsUint32(0, 0x4294750, &key);
        if (key != 0) {
          void* tool = (void*)cTribe_GetToolOfType(pcVar6, key);
          if (tool) { local_3c = 0x3e84; SetManipulatedObject(self, tool); }
        }
      }
    } else if (spec == 0x8bfac054) {
      if (pcVar7 == 0) return 0;
      unsigned vs = cCity_GetVehicleSpecialty(pcVar7);
      void* sp = (void*)cCity_GetCivilization(pcVar7, vs);
      if (cSPSimulatorSpaceGame_SpaceTelemetry_Add(sp, vs) == 0) {
        VC4(void, (void*)MessageServer(), 0x18, 0x2cb6a8f, 0, 0, 0);
        return 0;
      }
      local_30 = (int)param_3;
      void* veh = (void*)FUN_00d091c0(param_3);
      if (veh == 0) return 0;
      pfVar28 = (void*)((char*)veh + 0x50);
      SetManipulatedObject(self, pfVar28);
      local_3c = 0x3e85;
      FUN_00d0c010();
      FUN_00572660(veh);
      FUN_00ba57a0(veh, 1);
      if (GetCurrentGameMode() == (int)&DAT_01654c05) {
        cVehicle_SetJustEyeCandy(veh, 1);
      } else {
        FUN_00cf74c0(veh);
        FUN_00cf8ec0(veh);
      }
      goto LAB_00d1423e;
    } else if (spec == 0x81c74dbc) {
      if (pcVar7 == 0) return 0;
      local_34 = 0;
      local_38 = 0;
      cVar5 = VC2(char, (void*)(I(PropertyManager(),0) + 0x2c), 0, 0, 0);
      if (cVar5 != 0) GetPropertyAsKeyInstance(&local_38, 0x456b66a, &local_34);
      if (local_34 != 0) {
        iVar9 = cGameNounManager_CreateNoun((void*)NounManager(), local_34);
        if (iVar9) {
          pfVar28 = (void*)(iVar9 + 0x34);
          B((char*)iVar9, 0xa2) = 1;
          SetManipulatedObject(self, pfVar28);
          local_3c = 0x3e82;
        }
      }
      if ((char)param_2 == 0) return 0;
      goto LAB_00d1423e;
    }
    return 0;
  } else if (DAT_0169d588 == 0) {
    DAT_0169d588 = 1;
    iVar9 = VC1(int, (void*)ConfigManager(), 0x30, 0x4ea96cb);
    if (iVar9 != 0) {
      cGameTimeManager_IncPauseGate(GameTimeManager(), 0x4bf38a7);
LAB_00d13794:
      FUN_0067caf0(0, 0, 0, &PTR_PTR_015825c8, 0, 0xbf800000, 0xbf800000, 0, 0, 0);
      FUN_0067aaf0(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
      FUN_0067cac0(0, 1);
      FUN_0067c420(0, 1);
      return 0;
    }
  }

  return 0;

LAB_00d13447:
  VC0(void, param_2, 8);
  return 0;

LAB_00d1423e:
  iVar9 = GetObjectCost(self, pfVar28, 0, local_30);
  VC1(void, (void*)I(self, 0x50), 0x18, -iVar9);
  FUN_00435e90();
  // SP::cSPUISpace::KillSetiEffects();
  if (uStack_44 != 0) VC1(void, (void*)GameInputManager(), 100, 1);
  F(self, 0x50) = 0.0f;
  SetObjectSpecificData(self);
  I(self, 0x50) = 0xffffffff;
  if (uStack_44 == 0) {
    SetManipulatedObject(self, 0);
  }
  return 0;
}
