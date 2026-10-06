// slice s00b24740 -- one function at 0x00b24740.
//
// 0x00b24740 registers the Simulator noun classes (5.3 KB, 109 entries): for each
// class it calls Simulator::RegisterNounType(nounID, typeID, "cName") (0x00b23e60,
// address confirmed by Spore-ModAPI's RegisterNounType = 0xB23E40 in the 2017 build)
// and then stores the class's create function into this object's
// eastl::hash_map<uint32_t, NounCreateFunction> (at +0x10) via the out-of-line
// hash_map::operator[] (0x00b474c0).  This is the shape of ModAPI's
// Simulator::NounCreateMap (an App::ISPClassFactory with a classMap member).
// The create functions (0x00b1e550 ...) are `new("Simulator/cX") cX()` thunks.
//
// Flags: /O2 /MD /Gy /EHsc /TP

typedef unsigned int uint32_t;

namespace Simulator {

class cGameData;
typedef cGameData* (*NounCreateFunction)();

void RegisterNounType(uint32_t nounID, uint32_t typeID, const char* name);

// Create thunks, one per noun class (masked relocations).
cGameData* Create_cCheatObject();  // 0xb1e550
cGameData* Create_cMissionFetch();  // 0xb1e580
cGameData* Create_cMissionHappinessEvent();  // 0xb1fc30
cGameData* Create_cMissionMakeAlly();  // 0xb1e5b0
cGameData* Create_cRaidPlunderEvent();  // 0xb1e5e0
cGameData* Create_cRaidEvent();  // 0xb1e610
cGameData* Create_cMissionColonize();  // 0xb1e640
cGameData* Create_cMissionEradicate();  // 0xb1e670
cGameData* Create_cMissionExplore();  // 0xb1e6a0
cGameData* Create_cMissionWar();  // 0xb1e6d0
cGameData* Create_cMissionScan();  // 0xb1e700
cGameData* Create_cMissionTerraform();  // 0xb1e730
cGameData* Create_cMissionTrade();  // 0xb1e760
cGameData* Create_cMissionTradeRoute();  // 0xb1e790
cGameData* Create_cMissionMultiDelivery();  // 0xb1e7c0
cGameData* Create_cMissionBiosphere();  // 0xb1e7f0
cGameData* Create_cGenericPressureEvent();  // 0xb1e820
cGameData* Create_cMissionMultiStep();  // 0xb1e870
cGameData* Create_cMissionBalance();  // 0xb1e8a0
cGameData* Create_cMissionFindAliens();  // 0xb1e8d0
cGameData* Create_cMissionFlight101();  // 0xb1e900
cGameData* Create_cMissionUseTool();  // 0xb1e930
cGameData* Create_cMissionStory201();  // 0xb1e960
cGameData* Create_cMissionChangeArchetype();  // 0xb1e990
cGameData* Create_cMissionTrackBadge();  // 0xb1e9c0
cGameData* Create_cMissionAdventure();  // 0xb1e9f0
cGameData* Create_cPlayer();  // 0xb1ea20
cGameData* Create_cMilitaryAttackCityOrder();  // 0xb23740
cGameData* Create_cCulturalConvertCityOrder();  // 0xb23770
cGameData* Create_cGameTerrainCursor();  // 0xb1ea50
cGameData* Create_cBuildingCityHall();  // 0xb1ea80
cGameData* Create_cBuildingIndustry();  // 0xb1eab0
cGameData* Create_cBuildingHouse();  // 0xb1eae0
cGameData* Create_cBuildingEntertainment();  // 0xb1eb10
cGameData* Create_cBuildingScenario();  // 0xb1eb40
cGameData* Create_cTurret();  // 0xb1eb70
cGameData* Create_cCelestialBody();  // 0xb1eba0
cGameData* Create_cGameBundle();  // 0xb1ebd0
cGameData* Create_cCulturalTarget();  // 0xb1ec00
cGameData* Create_cCity();  // 0xb1ec30
cGameData* Create_cGameBundleGroundContainer();  // 0xb1ec60
cGameData* Create_cVehicle();  // 0xb1ec90
cGameData* Create_cVehicleGroupOrder();  // 0xb23180
cGameData* Create_cCityWalls();  // 0xb1ecc0
cGameData* Create_cCityTerritory();  // 0xb1ecf0
cGameData* Create_cPlaceholderColonyEditorCursorAttachment();  // 0xb1ed20
cGameData* Create_cPlanetaryArtifact();  // 0xb1ed50
cGameData* Create_cToolObject();  // 0xb1ed80
cGameData* Create_cCivilization();  // 0xb1edb0
cGameData* Create_cCreatureAnimal();  // 0xb1ede0
cGameData* Create_cCreatureCitizen();  // 0xb1ee10
cGameData* Create_cObstacle();  // 0xb1ee40
cGameData* Create_cGamePlant();  // 0xb1ee70
cGameData* Create_cFruit();  // 0xb1eea0
cGameData* Create_cFruitGroup();  // 0xb1eed0
cGameData* Create_cNest();  // 0xb1ef00
cGameData* Create_cHerd();  // 0xb1ef30
cGameData* Create_cEgg();  // 0xb1ef60
cGameData* Create_cInteractiveOrnament();  // 0xb1ef90
cGameData* Create_cGameplayMarker();  // 0xb1efc0
cGameData* Create_cOrnament();  // 0xb1eff0
cGameData* Create_cAnimalTrap();  // 0xb1f020
cGameData* Create_cTotemPole();  // 0xb1f050
cGameData* Create_cTribeFoodMat();  // 0xb1f080
cGameData* Create_cRock();  // 0xb1f0b0
cGameData* Create_cCommodityNode();  // 0xb1f0e0
cGameData* Create_cMovableDestructibleOrnament();  // 0xb1f110
cGameData* Create_cSolarHitSphere();  // 0xb1f140
cGameData* Create_cHitSphere();  // 0xb1f170
cGameData* Create_cInterCityRoad();  // 0xb1f1a0
cGameData* Create_cTribe();  // 0xb1f1d0
cGameData* Create_cTribeTool();  // 0xb1f200
cGameData* Create_cSpear();  // 0xb20660
cGameData* Create_cArtilleryProjectile();  // 0xb1f230
cGameData* Create_cFlakProjectile();  // 0xb1f260
cGameData* Create_cDefaultToolProjectile();  // 0xb1f290
cGameData* Create_cDeepSpaceProjectile();  // 0xb1f2c0
cGameData* Create_cSpaceDefenseMissile();  // 0xb1f2f0
cGameData* Create_cDefaultBeamProjectile();  // 0xb1f320
cGameData* Create_cDefaultAoEArea();  // 0xb1f350
cGameData* Create_cCulturalProjectile();  // 0xb1f380
cGameData* Create_cResourceProjectile();  // 0xb1f3b0
cGameData* Create_cICBM();  // 0xb1f3e0
cGameData* Create_cSoundLoopObject();  // 0xb1f410
cGameData* Create_cRotationRing();  // 0xb1f440
cGameData* Create_cRotationBall();  // 0xb1f470
cGameData* Create_cMorphHandle();  // 0xb1f4a0
cGameData* Create_cTargetMorphHandle();  // 0xb1f4d0
cGameData* Create_cArrowMorphHandle();  // 0xb1f500
cGameData* Create_cSimpleRotationRing();  // 0xb1f530
cGameData* Create_cSimpleRotationBall();  // 0xb1f560
cGameData* Create_cPlanet();  // 0xb1f590
cGameData* Create_cVisiblePlanet();  // 0xb1f5d0
cGameData* Create_cStar();  // 0xb1f610
cGameData* Create_cSolarSystem();  // 0xb1f640
cGameData* Create_cSimPlanetLowLOD();  // 0xb1f670
cGameData* Create_cEmpire();  // 0xb1f6a0
cGameData* Create_cSpaceInventory();  // 0xb1f6d0
cGameData* Create_cPlayerInventory();  // 0xb1f700
cGameData* Create_cGameDataUFO();  // 0xb1f730
cGameData* Create_cTribeHut();  // 0xb1f760
cGameData* Create_cTribePlanner();  // 0xb1f790
cGameData* Create_cCreatureSpeciesMission();  // 0xb1f7c0
cGameData* Create_cCreatureTutorialMission();  // 0xb1f7f0
cGameData* Create_cTribeToTribeMission();  // 0xb1f820
cGameData* Create_cFindMission();  // 0xb1f850
cGameData* Create_cNanoDrone();  // 0xb1f880
cGameData* Create_cPlaceableSound();  // 0xb1f8b0
cGameData* Create_cPlaceableEffect();  // 0xb1f8e0

} // namespace Simulator

namespace eastl {
// Only operator[] is used here; it is out of line in the original (0x00b474c0).
template <class K, class V>
struct hash_map {
    V& operator[](const K& key);
    uint32_t mData[8];
};
}

namespace Simulator {

class NounCreateMap {
public:
    // Claude-coined name for 0x00b24740 (registration of every built-in noun).
    void RegisterNounClasses();

    inline NounCreateFunction& operator[](uint32_t key) { return classMap[key]; }

protected:
    uint32_t mFactoryBase[4];                                    // +0x00 ISPClassFactory part
    eastl::hash_map<uint32_t, NounCreateFunction> classMap;     // +0x10
};

#define REGISTER_NOUN(noun, type, cls) \
    RegisterNounType(noun, type, #cls); \
    (*this)[noun] = &Create_##cls;

// @ 0x00b24740
void NounCreateMap::RegisterNounClasses()
{
    REGISTER_NOUN(0x2a37e35, 0x2a37e34, cCheatObject);
    REGISTER_NOUN(0x2afd284, 0x2afd27e, cMissionFetch);
    REGISTER_NOUN(0x4f3bde9, 0x4f3bde8, cMissionHappinessEvent);
    REGISTER_NOUN(0x4f77499, 0x4f77498, cMissionMakeAlly);
    REGISTER_NOUN(0x397bff3, 0x397bff2, cRaidPlunderEvent);
    REGISTER_NOUN(0x3960c0e, 0x3960c0a, cRaidEvent);
    REGISTER_NOUN(0x2ba2a0e, 0x2ba2a01, cMissionColonize);
    REGISTER_NOUN(0x2f99994, 0x2f9998c, cMissionEradicate);
    REGISTER_NOUN(0x32a12f1, 0x32a12f0, cMissionExplore);
    REGISTER_NOUN(0x330fc49, 0x330fc43, cMissionWar);
    REGISTER_NOUN(0x347092d, 0x3470926, cMissionScan);
    REGISTER_NOUN(0x35988f4, 0x35988ee, cMissionTerraform);
    REGISTER_NOUN(0x2adedff, 0x2aeefff, cMissionTrade);
    REGISTER_NOUN(0x447092d, 0x4470926, cMissionTradeRoute);
    REGISTER_NOUN(0x35ed8f6, 0x35ed8f0, cMissionMultiDelivery);
    REGISTER_NOUN(0x437444b, 0x437443d, cMissionBiosphere);
    REGISTER_NOUN(0x317afcc, 0x317afcb, cGenericPressureEvent);
    REGISTER_NOUN(0x4222283, 0x422227c, cMissionMultiStep);
    REGISTER_NOUN(0x347092e, 0x3470927, cMissionBalance);
    REGISTER_NOUN(0x347092f, 0x3470928, cMissionFindAliens);
    REGISTER_NOUN(0x4222284, 0x422227d, cMissionFlight101);
    REGISTER_NOUN(0x2adedee, 0x2aeeeee, cMissionUseTool);
    REGISTER_NOUN(0x4222285, 0x422227e, cMissionStory201);
    REGISTER_NOUN(0x4622285, 0x462227e, cMissionChangeArchetype);
    REGISTER_NOUN(0x4633285, 0x463327e, cMissionTrackBadge);
    REGISTER_NOUN(0x46332a5, 0x463329e, cMissionAdventure);
    REGISTER_NOUN(0x2c21781, 0x2c216ed, cPlayer);
    REGISTER_NOUN(0x2e9ae6c, 0x2e9ae69, cMilitaryAttackCityOrder);
    REGISTER_NOUN(0x3df2cc5, 0x3df2cb9, cCulturalConvertCityOrder);
    REGISTER_NOUN(0x18c40bc, 0x14a4edc, cGameTerrainCursor);
    REGISTER_NOUN(0x18ea1eb, 0x1007ae63, cBuildingCityHall);
    REGISTER_NOUN(0x18ea2cc, 0xecade42, cBuildingIndustry);
    REGISTER_NOUN(0x18eb106, 0xff10521, cBuildingHouse);
    REGISTER_NOUN(0x1a56aba, 0x1a55e4d, cBuildingEntertainment);
    REGISTER_NOUN(0x70703b3, 0x70704db, cBuildingScenario);
    REGISTER_NOUN(0x436f342, 0x436f315, cTurret);
    REGISTER_NOUN(0x38cfb6b, 0x38cfb68, cCelestialBody);
    REGISTER_NOUN(0x18c431c, 0x4ffcdeda, cGameBundle);
    REGISTER_NOUN(0x3d5c325, 0x3d5c477, cCulturalTarget);
    REGISTER_NOUN(0x18c43e8, 0xee9b2232, cCity);
    REGISTER_NOUN(0x1906183, 0xeef202b7, cGameBundleGroundContainer);
    REGISTER_NOUN(0x18c6de8, 0x137e8e0, cVehicle);
    REGISTER_NOUN(0x2e98ab7, 0x2e98ab4, cVehicleGroupOrder);
    REGISTER_NOUN(0x18c7c97, 0xed7fc07, cCityWalls);
    REGISTER_NOUN(0x244fb08, 0x2450023, cCityTerritory);
    REGISTER_NOUN(0x2c5c93a, 0x2c5c935, cPlaceholderColonyEditorCursorAttachment);
    REGISTER_NOUN(0x2dd8c42, 0x2dd8c33, cPlanetaryArtifact);
    REGISTER_NOUN(0x4e3fab5, 0x4e3faaf, cToolObject);
    REGISTER_NOUN(0x18c816a, 0x901f1362, cCivilization);
    REGISTER_NOUN(0x18eb45e, 0xd0036e08, cCreatureAnimal);
    REGISTER_NOUN(0x18eb4b7, 0x4f176642, cCreatureCitizen);
    REGISTER_NOUN(0x3ed8573, 0x3ed590d, cObstacle);
    REGISTER_NOUN(0x18c84a9, 0xaeb336b4, cGamePlant);
    REGISTER_NOUN(0x2c9cc91, 0x2c9cc8e, cFruit);
    REGISTER_NOUN(0x2e96892, 0x2e9688e, cFruitGroup);
    REGISTER_NOUN(0x52aa6122, 0x1b92b27, cNest);
    REGISTER_NOUN(0x1be418e, 0x52aa6117, cHerd);
    REGISTER_NOUN(0x2a034cd, 0x2a0349a, cEgg);
    REGISTER_NOUN(0x3a2511e, 0x3a25119, cInteractiveOrnament);
    REGISTER_NOUN(0x36be27e, 0x36be278, cGameplayMarker);
    REGISTER_NOUN(0x18c88e4, 0x175cdc9, cOrnament);
    REGISTER_NOUN(0x61494be, 0x61494bd, cAnimalTrap);
    REGISTER_NOUN(0x55cf865, 0x55cf8e3, cTotemPole);
    REGISTER_NOUN(0x629bafe, 0x629baec, cTribeFoodMat);
    REGISTER_NOUN(0x2a8fb3f, 0x2a8fe3c, cRock);
    REGISTER_NOUN(0x403df5c, 0x403df5f, cCommodityNode);
    REGISTER_NOUN(0x283ddb1, 0x283d961, cMovableDestructibleOrnament);
    REGISTER_NOUN(0x32f9778, 0x32f9777, cSolarHitSphere);
    REGISTER_NOUN(0x2e72cae, 0x2e71a5a, cHitSphere);
    REGISTER_NOUN(0x2b8a4e7, 0x2bca14b, cInterCityRoad);
    REGISTER_NOUN(0x18c6d19, 0x4f396a66, cTribe);
    REGISTER_NOUN(0x18c8f0c, 0x116d858, cTribeTool);
    REGISTER_NOUN(0x24270c9, 0x24270c8, cSpear);
    REGISTER_NOUN(0x18c9380, 0x1428a48, cArtilleryProjectile);
    REGISTER_NOUN(0x240e3bf, 0x240e3b7, cFlakProjectile);
    REGISTER_NOUN(0x24270c5, 0x24270c4, cDefaultToolProjectile);
    REGISTER_NOUN(0x24270c7, 0x24270c6, cDeepSpaceProjectile);
    REGISTER_NOUN(0x244d3c8, 0x244d3c0, cSpaceDefenseMissile);
    REGISTER_NOUN(0x24630d7, 0x24630ce, cDefaultBeamProjectile);
    REGISTER_NOUN(0x4167186, 0x4167194, cDefaultAoEArea);
    REGISTER_NOUN(0x4f76f0d, 0x4f76f08, cCulturalProjectile);
    REGISTER_NOUN(0x5776a2c, 0x5776a28, cResourceProjectile);
    REGISTER_NOUN(0x49cec61, 0x49cec5c, cICBM);
    REGISTER_NOUN(0x18eb641, 0x903c3ea3, cSoundLoopObject);
    REGISTER_NOUN(0x2ee8ce8, 0x2ee8eeb, cRotationRing);
    REGISTER_NOUN(0x7292112, 0x7292112, cRotationBall);
    REGISTER_NOUN(0x7a30a12, 0x7a309fb, cMorphHandle);
    REGISTER_NOUN(0x76f6e64, 0x76c67df, cTargetMorphHandle);
    REGISTER_NOUN(0x771ad6f, 0x771ad6a, cArrowMorphHandle);
    REGISTER_NOUN(0x7a81829, 0x7a81824, cSimpleRotationRing);
    REGISTER_NOUN(0x7abdd91, 0x7abdd8d, cSimpleRotationBall);
    REGISTER_NOUN(0x3275728, 0x3275872, cPlanet);
    REGISTER_NOUN(0x44462a6, 0x44462a6, cVisiblePlanet);
    REGISTER_NOUN(0x355c93a, 0x355c8df, cStar);
    REGISTER_NOUN(0x38cf94c, 0x38cf949, cSolarSystem);
    REGISTER_NOUN(0x3572e72, 0x3572e6c, cSimPlanetLowLOD);
    REGISTER_NOUN(0x18eb9d2, 0x1805e75, cEmpire);
    REGISTER_NOUN(0x21ffa3f, 0xb075dec5, cSpaceInventory);
    REGISTER_NOUN(0x2265fdc, 0x9073163b, cPlayerInventory);
    REGISTER_NOUN(0x18ebadc, 0xb033b403, cGameDataUFO);
    REGISTER_NOUN(0x1e4daae, 0xee02c7, cTribeHut);
    REGISTER_NOUN(0x3098af98, 0x9098aeb2, cTribePlanner);
    REGISTER_NOUN(0x1406a572, 0x7406a570, cCreatureSpeciesMission);
    REGISTER_NOUN(0x34066dba, 0xd4066db3, cCreatureTutorialMission);
    REGISTER_NOUN(0x5436411a, 0x34364118, cTribeToTribeMission);
    REGISTER_NOUN(0x14d9597f, 0x14d9597c, cFindMission);
    REGISTER_NOUN(0x6ef0f11, 0x6ef0ec9, cNanoDrone);
    REGISTER_NOUN(0x74e0069, 0x74e0069, cPlaceableSound);
    REGISTER_NOUN(0x7b38ba7, 0x7b38ba7, cPlaceableEffect);
}

#undef REGISTER_NOUN

} // namespace Simulator
