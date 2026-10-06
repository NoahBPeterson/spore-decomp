#include "types.h"
// Static registration slot: 15 dwords (0x3c bytes) built in a stack temp and copied (rep movsd) to a global.
struct Slot {
	const char* name;   // +0x00
	uint32_t hash;      // +0x04
	void* data;         // +0x08
	uint32_t unk0c[3];  // +0x0c..0x14 (never initialized in the original, copied as stack garbage)
	uint32_t zero18;    // +0x18
	uint32_t zero1c;    // +0x1c
	void (*f20)();
	void (*f24)();
	void (*f28)();
	void (*f2c)();
	void (*f30)();
	void (*f34)();
	uint32_t zero38;
};

extern "C" void F_00692fb0();
extern "C" void F_00693150();
extern "C" void F_00695080();
extern "C" void F_00ae3430();
extern "C" void F_00ae3450();
extern "C" void F_00b1fbf0();
extern "C" void F_00b5cb60();
extern "C" void F_00b5cb80();
extern "C" void F_00b5cba0();
extern "C" void F_00b5cbc0();
extern "C" void F_00b5cbe0();
extern "C" void F_00b5cc00();
extern "C" void F_00b5f1b0();
extern "C" void F_00c2e4e0();
extern "C" void F_011874d0();
extern char D_01686a30[];
extern char D_01686a34[];
extern char D_01686a38[];
extern char D_01686a3c[];
extern char D_01686a40[];
extern char D_01686a44[];
extern char D_01686a48[];
extern char D_01686a4c[];
extern char D_01686a50[];
extern char D_01686a54[];
extern char D_01686a58[];
extern char D_01686a5c[];
extern char D_01686a60[];
extern char D_01686a64[];
extern char D_01686a68[];
extern char D_01686a6c[];
extern char D_01686a70[];
extern char D_01686a74[];
extern char D_01686a78[];
extern char D_01686a7c[];
extern char D_01686a80[];
extern char D_01686a84[];
extern char D_01686a88[];
extern char D_01686a8c[];
extern char D_01686a90[];
extern char D_01686a94[];
extern char D_01686a98[];
extern char D_01686a9c[];
extern char D_01686aa0[];
extern char D_01686aa4[];
extern char D_01686aa8[];
extern char D_01686aac[];
extern char D_01686ab0[];
extern char D_01686ab4[];
extern char D_01686ab8[];
extern char D_01686abc[];
extern char D_01686ac0[];
extern char D_01686ac4[];
extern char D_01686ac8[];
extern char D_01686acc[];
extern char D_01686ad0[];
extern char D_01686ad4[];
extern char D_01686ad8[];
extern char D_01686adc[];
extern char D_01686ae0[];
extern char D_01686ae4[];
extern char D_01686ae8[];
extern char D_016870e4[];
extern char D_016870f0[];
extern Slot G_0156a118; // sPlanetKey
extern Slot G_0156a154; // sAvatarSpecies
extern Slot G_0156a190; // sGameViewManagerContainer
extern Slot G_0156a1cc; // sPlanetModelContainer
extern Slot G_0156a208; // sAnimalSpeciesManagerContainer
extern Slot G_0156a244; // sFruitManagerContainer
extern Slot G_0156a280; // sObstacleManagerContainer
extern Slot G_0156a2bc; // sPlantSpeciesManagerContainer
extern Slot G_0156a2f8; // sGameInputManagerContainer
extern Slot G_0156a334; // sAStarContainer
extern Slot G_0156a370; // sGameBehaviorManagerContainer
extern Slot G_0156a3ac; // sGameNounManagerContainer
extern Slot G_0156a3e8; // sBundleManagerContainer
extern Slot G_0156a424; // sStarManagerContainer
extern Slot G_0156a460; // sGonzagoPhysicsContainer
extern Slot G_0156a49c; // sGameModeManagerContainer
extern Slot G_0156a4d8; // sSimTickerContainer
extern Slot G_0156a514; // sGamePersistenceManagerContainer
extern Slot G_0156a550; // sToolManagerContainer
extern Slot G_0156a58c; // sCheatObjectManagerContainer
extern Slot G_0156a5c8; // sTerraformingManagerContainer
extern Slot G_0156a604; // sGamePlantManagerContainer
extern Slot G_0156a640; // sSpaceGfxContainer
extern Slot G_0156a67c; // sCommGraphicsManagerContainer
extern Slot G_0156a6b8; // sCommManagerContainer
extern Slot G_0156a6f4; // sLivingUniverseContainer
extern Slot G_0156a730; // sSpaceTradingContainer
extern Slot G_0156a76c; // sUIEventLogContainer
extern Slot G_0156a7a8; // sUITimelineContainer
extern Slot G_0156a7e4; // sCastingManagerContainer
extern Slot G_0156a820; // sSpeciesRelationshipManagerContainer
extern Slot G_0156a85c; // sPlanetImpostorManagerContainer
extern Slot G_0156a898; // sBlobShadowManagerContainer
extern Slot G_0156a8d4; // sCinematicManagerContainer
extern Slot G_0156a910; // sEventLogCommManagerContainer
extern Slot G_0156a94c; // sVignetteManagerContainer
extern Slot G_0156a988; // sNPCCityMusicManagerContainer
extern Slot G_0156a9c4; // sUIMissionLogContainer
extern Slot G_0156aa00; // sAssetDiscoveryManagerContainer
extern Slot G_0156aa3c; // sMissionCardPanelContainer
extern Slot G_0156aa78; // sNanoDroneManagerContainer
extern Slot G_0156aab4; // sScenarioVehicleTickerContainer
extern Slot G_0156aaf0; // sGameEditModeStrategyContainer
extern Slot G_0156ab2c; // sCreatureModeStrategyContainer
extern Slot G_0156ab68; // sTribeModeStrategyContainer
extern Slot G_0156aba4; // sCivModeStrategyContainer
extern Slot G_0156abe0; // sAppModeSpaceContainer
extern Slot G_0156ac1c; // sTelemetryContainer
extern Slot G_0156ac58; // sAppModeEditorBaseContainer

// @ 0x0131ea90
void E649()
{
	Slot t;
	t.name = "sPlanetKey"; t.hash = 0x56e4a8b; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00ae3430; t.f28 = F_00ae3450; t.f2c = F_00693150; t.f30 = F_00695080; t.f34 = F_00b1fbf0; t.zero38 = 0;
	t.data = D_016870e4;
	G_0156a118 = t;
	t.name = "sAvatarSpecies"; t.hash = 0x56e4a9b; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00ae3430; t.f28 = F_00ae3450; t.f2c = F_00693150; t.f30 = F_00695080; t.f34 = F_00b1fbf0; t.zero38 = 0;
	t.data = D_016870f0;
	G_0156a154 = t;
	t.name = "sGameViewManagerContainer"; t.hash = 0x56e361d; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686ae8;
	G_0156a190 = t;
	t.name = "sPlanetModelContainer"; t.hash = 0x56e361f; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686ae4;
	G_0156a1cc = t;
	t.name = "sAnimalSpeciesManagerContainer"; t.hash = 0x56e3621; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686ae0;
	G_0156a208 = t;
	t.name = "sFruitManagerContainer"; t.hash = 0x56e3622; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686adc;
	G_0156a244 = t;
	t.name = "sObstacleManagerContainer"; t.hash = 0x56e3624; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686ad8;
	G_0156a280 = t;
	t.name = "sPlantSpeciesManagerContainer"; t.hash = 0x56e3626; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686ad4;
	G_0156a2bc = t;
	t.name = "sGameInputManagerContainer"; t.hash = 0x56e3628; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686ad0;
	G_0156a2f8 = t;
	t.name = "sAStarContainer"; t.hash = 0x56e3629; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686acc;
	G_0156a334 = t;
	t.name = "sGameBehaviorManagerContainer"; t.hash = 0x56e362b; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686ac8;
	G_0156a370 = t;
	t.name = "sGameNounManagerContainer"; t.hash = 0x56e362c; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686ac4;
	G_0156a3ac = t;
	t.name = "sBundleManagerContainer"; t.hash = 0x56e362d; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686ac0;
	G_0156a3e8 = t;
	t.name = "sStarManagerContainer"; t.hash = 0x56e362f; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686abc;
	G_0156a424 = t;
	t.name = "sGonzagoPhysicsContainer"; t.hash = 0x56e3630; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686ab8;
	G_0156a460 = t;
	t.name = "sGameModeManagerContainer"; t.hash = 0x56e3631; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686ab4;
	G_0156a49c = t;
	t.name = "sSimTickerContainer"; t.hash = 0x56e3633; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686ab0;
	G_0156a4d8 = t;
	t.name = "sGamePersistenceManagerContainer"; t.hash = 0x56e3635; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686aac;
	G_0156a514 = t;
	t.name = "sToolManagerContainer"; t.hash = 0x56e3636; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686aa8;
	G_0156a550 = t;
	t.name = "sCheatObjectManagerContainer"; t.hash = 0x56e3637; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686aa4;
	G_0156a58c = t;
	t.name = "sTerraformingManagerContainer"; t.hash = 0x56e3639; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686aa0;
	G_0156a5c8 = t;
	t.name = "sGamePlantManagerContainer"; t.hash = 0x56e363a; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686a9c;
	G_0156a604 = t;
	t.name = "sSpaceGfxContainer"; t.hash = 0x56e363c; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686a98;
	G_0156a640 = t;
	t.name = "sCommGraphicsManagerContainer"; t.hash = 0x56e363d; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686a94;
	G_0156a67c = t;
	t.name = "sCommManagerContainer"; t.hash = 0x56e363f; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686a90;
	G_0156a6b8 = t;
	t.name = "sLivingUniverseContainer"; t.hash = 0x56e3641; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686a8c;
	G_0156a6f4 = t;
	t.name = "sSpaceTradingContainer"; t.hash = 0x56e3642; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686a88;
	G_0156a730 = t;
	t.name = "sUIEventLogContainer"; t.hash = 0x56e3644; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686a84;
	G_0156a76c = t;
	t.name = "sUITimelineContainer"; t.hash = 0x56e3649; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686a7c;
	G_0156a7a8 = t;
	t.name = "sCastingManagerContainer"; t.hash = 0x56e364c; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686a78;
	G_0156a7e4 = t;
	t.name = "sSpeciesRelationshipManagerContainer"; t.hash = 0x56e364d; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686a74;
	G_0156a820 = t;
	t.name = "sPlanetImpostorManagerContainer"; t.hash = 0x56e3651; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686a70;
	G_0156a85c = t;
	t.name = "sBlobShadowManagerContainer"; t.hash = 0x56e3652; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686a6c;
	G_0156a898 = t;
	t.name = "sCinematicManagerContainer"; t.hash = 0x56e3654; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686a68;
	G_0156a8d4 = t;
	t.name = "sEventLogCommManagerContainer"; t.hash = 0x56e3655; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686a64;
	G_0156a910 = t;
	t.name = "sVignetteManagerContainer"; t.hash = 0x56e3656; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686a60;
	G_0156a94c = t;
	t.name = "sNPCCityMusicManagerContainer"; t.hash = 0x56e3658; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686a5c;
	G_0156a988 = t;
	t.name = "sUIMissionLogContainer"; t.hash = 0x56e3659; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686a80;
	G_0156a9c4 = t;
	t.name = "sAssetDiscoveryManagerContainer"; t.hash = 0x74e1ab86; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686a58;
	G_0156aa00 = t;
	t.name = "sMissionCardPanelContainer"; t.hash = 0x34f5669b; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686a54;
	G_0156aa3c = t;
	t.name = "sNanoDroneManagerContainer"; t.hash = 0x6ef44f2; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686a50;
	G_0156aa78 = t;
	t.name = "sScenarioVehicleTickerContainer"; t.hash = 0x6fd969a; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686a4c;
	G_0156aab4 = t;
	t.name = "sGameEditModeStrategyContainer"; t.hash = 0x56e37ca; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686a48;
	G_0156aaf0 = t;
	t.name = "sCreatureModeStrategyContainer"; t.hash = 0x56e37d4; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686a44;
	G_0156ab2c = t;
	t.name = "sTribeModeStrategyContainer"; t.hash = 0x56e37dd; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686a40;
	G_0156ab68 = t;
	t.name = "sCivModeStrategyContainer"; t.hash = 0x56e37e7; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686a3c;
	G_0156aba4 = t;
	t.name = "sAppModeSpaceContainer"; t.hash = 0x56e37ee; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cb60; t.f28 = F_00b5cb80; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b5f1b0; t.zero38 = 0;
	t.data = D_01686a38;
	G_0156abe0 = t;
	t.name = "sTelemetryContainer"; t.hash = 0x56e4605; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cba0; t.f28 = F_00b5cbc0; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b1fbf0; t.zero38 = 0;
	t.data = D_01686a34;
	G_0156ac1c = t;
	t.name = "sAppModeEditorBaseContainer"; t.hash = 0x56e46cc; t.zero18 = 0; t.zero1c = 0;
	t.f20 = F_011874d0; t.f24 = F_00b5cbe0; t.f28 = F_00b5cc00; t.f2c = F_00c2e4e0; t.f30 = F_00692fb0; t.f34 = F_00b1fbf0; t.zero38 = 0;
	t.data = D_01686a30;
	G_0156ac58 = t;
}