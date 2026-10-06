// Slice s00b39b70 — 0x00b39b70, 3962 bytes.
//
// Simulator view-class factory registration: creates one prototype view object per game-data
// noun type and stores it in a global ordered map (0x0167ea3c, uint32 key -> view pointer)
// through OrderedMapFindOrInsert (0x00f41aa0, slice s00f40d00).  Each entry is
//     gViewPrototypes[key] = new("Simulator/<class>", 0, 0, 0, 0) <class>();
// (cl evaluates the new-expression before operator[], like the original).  The classes whose
// ctor is inlined here (vptr store after the base ctor call) derive from cCreatureView
// (0x00e8bc80) or cSpatialObjectView (0x00e92af0; the card mislabels it as cFruitView's ctor,
// whose real address is 0x00b01870).  cTurretView additionally zeroes two members at +0x48/+0x4c.
// Two entries use the generic "Simulator" allocation name: cUFOGfx (0x00e993c0) and an
// unnamed 0x68-byte class whose ctor is 0x00e972e0.
//
// Flags: default /O2 /MD /Gy /EHsc /TP (no EH frame: the 6-arg operator new has no matching
// placement delete).
//
// @ 0x00b39b70

typedef unsigned int size_t;
typedef unsigned int uint32_t;

// EA global operator new (0x00f473a0)
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
#define SP_NEW(name) new(name, 0, 0, 0, 0)

namespace Simulator {

struct cView;

// eastl::vector_map<uint32_t, cView*>-like ordered map; operator[] = 0x00f41aa0
struct cViewPrototypeMap {
    cView*& operator[](const uint32_t& key);
};
extern cViewPrototypeMap gViewPrototypes;   // 0x0167ea3c

// Classes with out-of-line ctors: only the size matters (it is the operator new argument).
#define SIM_VIEW(Name, Size) struct Name { Name(); uint32_t mData[(Size) / 4]; }
SIM_VIEW(cNestView, 0x34);                                  // ctor 0x00e8ded0
SIM_VIEW(cEggView, 0x3c);                                   // ctor 0x00e8e050
SIM_VIEW(cFruitView, 0x38);                                 // ctor 0x00b01870
SIM_VIEW(cInteractableObjectView, 0x34);                    // ctor 0x00e8eab0
SIM_VIEW(cTribeView, 0x68);                                 // ctor 0x00e93b80
SIM_VIEW(cGamePlantView, 0x40);                             // ctor 0x00e8d0e0
SIM_VIEW(cTribeToolView, 0x70);                             // ctor 0x00e932a0
SIM_VIEW(cAnimalTrapView, 0x34);                            // ctor 0x00e8eb70
SIM_VIEW(cTribeFoodMatView, 0x34);                          // ctor 0x00e8ec10
SIM_VIEW(cTotemPoleView, 0x38);                             // ctor 0x00e8ead0
SIM_VIEW(cBuildingView, 0x88);                              // ctor 0x00e87b70
SIM_VIEW(cBundleView, 0x40);                                // ctor 0x00e8cc90
SIM_VIEW(cCityFeedbackView, 0x1c);                          // ctor 0x00e88ac0
SIM_VIEW(cCityWallsView, 0x3c);                             // ctor 0x00e88680
SIM_VIEW(cCulturalTargetView, 0x54);                        // ctor 0x00e89d60
SIM_VIEW(cCityTerritory, 0x48);                             // ctor 0x00e87d30
SIM_VIEW(cPlaceholderColonyEditorCursorAttachment, 0x34);   // ctor 0x00e90b50
SIM_VIEW(cPlanetaryArtifact, 0x34);                         // ctor 0x00e90d80
SIM_VIEW(cToolObject, 0x34);                                // ctor 0x00e90d00
SIM_VIEW(cVehicleView, 0xd0);                               // ctor 0x00e94b60
SIM_VIEW(cMineralView, 0x48);                               // ctor 0x00e8efd0
SIM_VIEW(cGfx_e972e0, 0x68);                                // ctor 0x00e972e0 (unnamed)
SIM_VIEW(cUFOGfx, 0xd8);                                    // ctor 0x00e993c0
SIM_VIEW(cSpaceDefenseMissileView, 0x3c);                   // ctor 0x00cc2c90
SIM_VIEW(cDefaultBeamProjectileView, 0x40);                 // ctor 0x00cc28c0
SIM_VIEW(cNanoDrone, 0x34);                                 // ctor 0x00c69820
SIM_VIEW(cGameTerrainCursorView, 0x40);                     // ctor 0x00e8d770
SIM_VIEW(cRotationRingView, 0x20);                          // ctor 0x00e91c10
SIM_VIEW(cRotationBallView, 0x1c);                          // ctor 0x00e915d0
SIM_VIEW(cCitySoundLoopView, 0x38);                         // ctor 0x00e88600
#undef SIM_VIEW

// Polymorphic bases of the classes whose ctors are inlined below.
struct cCreatureView {          // 0x1c, ctor 0x00e8bc80
    cCreatureView();
    virtual void Fn0();
    uint32_t mData[6];
};
struct cSpatialObjectView {     // 0x34, ctor 0x00e92af0
    cSpatialObjectView();
    virtual void Fn0();
    uint32_t mData[12];
};

struct cCreatureAnimalView : cCreatureView {        // 0x24, vftable 0x014605e4
    cCreatureAnimalView() {}
    virtual void Fn0();
    uint32_t mAnimal[2];
};

// Derived spatial-object views with an inline ctor (only the vftable differs).
#define SIM_SPATIAL(Name, Size) \
    struct Name : cSpatialObjectView { \
        Name() {} \
        virtual void Fn0(); \
        uint32_t mExtra[((Size) - 0x34) / 4]; \
    }
#define SIM_SPATIAL0(Name) \
    struct Name : cSpatialObjectView { \
        Name() {} \
        virtual void Fn0(); \
    }
SIM_SPATIAL0(cArtilleryProjectileView);       // 0x34, vftable 0x01460608
SIM_SPATIAL0(cOrnamentView);                  // 0x34, vftable 0x0146063c
SIM_SPATIAL0(cSolarHitSphereView);            // 0x34, vftable 0x01460920
SIM_SPATIAL0(cHitSphereView);                 // 0x34, vftable 0x01460670
SIM_SPATIAL0(cFlakProjectileView);            // 0x34, vftable 0x014606a4
SIM_SPATIAL0(cDeepSpaceProjectileView);       // 0x34, vftable 0x0146070c
SIM_SPATIAL0(cDefaultAoEAreaView);            // 0x34, vftable 0x01460740
SIM_SPATIAL0(cResourceProjectileView);        // 0x34, vftable 0x014607a8
SIM_SPATIAL(cDefaultToolProjectileView, 0x38);   // 0x38, vftable 0x014606d8
SIM_SPATIAL(cCulturalProjectileView, 0x38);      // 0x38, vftable 0x01460774
#undef SIM_SPATIAL
#undef SIM_SPATIAL0

struct cTurretView : cSpatialObjectView {           // 0x50, vftable 0x014608ec
    cTurretView() : mpTarget(0), mTargetTime(0) {}
    virtual void Fn0();
    uint32_t mTurret[5];
    uint32_t mpTarget;      // +0x48
    uint32_t mTargetTime;   // +0x4c
};

// 0x00b39b70
void RegisterViewPrototypes()
{
    gViewPrototypes[0xd0036e08] = (cView*)SP_NEW("Simulator/cCreatureAnimalView") cCreatureAnimalView();
    gViewPrototypes[0x4f176642] = (cView*)SP_NEW("Simulator/cCreatureView") cCreatureView();
    gViewPrototypes[0x01b92b27] = (cView*)SP_NEW("Simulator/cNestView") cNestView();
    gViewPrototypes[0x02a0349a] = (cView*)SP_NEW("Simulator/cEggView") cEggView();
    gViewPrototypes[0x02c9cc8e] = (cView*)SP_NEW("Simulator/cFruitView") cFruitView();
    gViewPrototypes[0x03a25119] = (cView*)SP_NEW("Simulator/cInteractableObjectView") cInteractableObjectView();
    gViewPrototypes[0x00ee02c7] = (cView*)SP_NEW("Simulator/cTribeView") cTribeView();
    gViewPrototypes[0xaeb336b4] = (cView*)SP_NEW("Simulator/cGamePlantView") cGamePlantView();
    gViewPrototypes[0x0116d858] = (cView*)SP_NEW("Simulator/cTribeToolView") cTribeToolView();
    gViewPrototypes[0x061494bd] = (cView*)SP_NEW("Simulator/cAnimalTrapView") cAnimalTrapView();
    gViewPrototypes[0x0629baec] = (cView*)SP_NEW("Simulator/cTribeFoodMatView") cTribeFoodMatView();
    gViewPrototypes[0x055cf8e3] = (cView*)SP_NEW("Simulator/cTotemPoleView") cTotemPoleView();
    gViewPrototypes[0x0e9cb8ba] = (cView*)SP_NEW("Simulator/cBuildingView") cBuildingView();
    gViewPrototypes[0x0ff10521] = (cView*)SP_NEW("Simulator/cBuildingView") cBuildingView();
    gViewPrototypes[0x0ecade42] = (cView*)SP_NEW("Simulator/cBuildingView") cBuildingView();
    gViewPrototypes[0x01a55e4d] = (cView*)SP_NEW("Simulator/cBuildingView") cBuildingView();
    gViewPrototypes[0x1007ae63] = (cView*)SP_NEW("Simulator/cBuildingView") cBuildingView();
    gViewPrototypes[0x070704db] = (cView*)SP_NEW("Simulator/cBuildingView") cBuildingView();
    gViewPrototypes[0x4ffcdeda] = (cView*)SP_NEW("Simulator/cBundleView") cBundleView();
    gViewPrototypes[0xee9b2232] = (cView*)SP_NEW("Simulator/cCityFeedbackView") cCityFeedbackView();
    gViewPrototypes[0x0ed7fc07] = (cView*)SP_NEW("Simulator/cCityWallsView") cCityWallsView();
    gViewPrototypes[0x0436f315] = (cView*)SP_NEW("Simulator/cTurretView") cTurretView();
    gViewPrototypes[0x03d5c477] = (cView*)SP_NEW("Simulator/cCulturalTargetView") cCulturalTargetView();
    gViewPrototypes[0x02450023] = (cView*)SP_NEW("Simulator/cCityTerritory") cCityTerritory();
    gViewPrototypes[0x02c5c935] = (cView*)SP_NEW("Simulator/cPlaceholderColonyEditorCursorAttachment") cPlaceholderColonyEditorCursorAttachment();
    gViewPrototypes[0x02dd8c33] = (cView*)SP_NEW("Simulator/cPlanetaryArtifact") cPlanetaryArtifact();
    gViewPrototypes[0x04e3faaf] = (cView*)SP_NEW("Simulator/cToolObject") cToolObject();
    gViewPrototypes[0x0137e8e0] = (cView*)SP_NEW("Simulator/cVehicleView") cVehicleView();
    gViewPrototypes[0x01428a48] = (cView*)SP_NEW("Simulator/cArtilleryProjectileView") cArtilleryProjectileView();
    gViewPrototypes[0x024270c8] = (cView*)SP_NEW("Simulator/cArtilleryProjectileView") cArtilleryProjectileView();
    gViewPrototypes[0x02a8fe3c] = (cView*)SP_NEW("Simulator/cInteractableObjectView") cInteractableObjectView();
    gViewPrototypes[0x0175cdc9] = (cView*)SP_NEW("Simulator/cOrnamentView") cOrnamentView();
    gViewPrototypes[0x0283d961] = (cView*)SP_NEW("Simulator/cOrnamentView") cOrnamentView();
    gViewPrototypes[0x032f9777] = (cView*)SP_NEW("Simulator/cSolarHitSphereView") cSolarHitSphereView();
    gViewPrototypes[0x02e71a5a] = (cView*)SP_NEW("Simulator/cHitSphereView") cHitSphereView();
    gViewPrototypes[0x0403df5f] = (cView*)SP_NEW("Simulator/cMineralView") cMineralView();
    gViewPrototypes[0x044462a6] = (cView*)SP_NEW("Simulator") cGfx_e972e0();
    gViewPrototypes[0xb033b403] = (cView*)SP_NEW("Simulator") cUFOGfx();
    gViewPrototypes[0x0240e3b7] = (cView*)SP_NEW("Simulator/cFlakProjectileView") cFlakProjectileView();
    gViewPrototypes[0x024270c4] = (cView*)SP_NEW("Simulator/cDefaultToolProjectileView") cDefaultToolProjectileView();
    gViewPrototypes[0x024270c6] = (cView*)SP_NEW("Simulator/cDeepSpaceProjectileView") cDeepSpaceProjectileView();
    gViewPrototypes[0x0244d3c0] = (cView*)SP_NEW("Simulator/cSpaceDefenseMissileView") cSpaceDefenseMissileView();
    gViewPrototypes[0x024630ce] = (cView*)SP_NEW("Simulator/cDefaultBeamProjectileView") cDefaultBeamProjectileView();
    gViewPrototypes[0x04167194] = (cView*)SP_NEW("Simulator/cDefaultAoEAreaView") cDefaultAoEAreaView();
    gViewPrototypes[0x04f76f08] = (cView*)SP_NEW("Simulator/cCulturalProjectileView") cCulturalProjectileView();
    gViewPrototypes[0x05776a28] = (cView*)SP_NEW("Simulator/cResourceProjectileView") cResourceProjectileView();
    gViewPrototypes[0x049cec5c] = (cView*)SP_NEW("Simulator/cSpaceDefenseMissileView") cSpaceDefenseMissileView();
    gViewPrototypes[0x06ef0ec9] = (cView*)SP_NEW("Simulator/cNanoDrone") cNanoDrone();
    gViewPrototypes[0x074e0069] = (cView*)SP_NEW("Simulator/cSpatialObjectView") cSpatialObjectView();
    gViewPrototypes[0x07b38ba7] = (cView*)SP_NEW("Simulator/cSpatialObjectView") cSpatialObjectView();
    gViewPrototypes[0x014a4edc] = (cView*)SP_NEW("Simulator/cGameTerrainCursorView") cGameTerrainCursorView();
    gViewPrototypes[0x02ee8eeb] = (cView*)SP_NEW("Simulator/cRotationRingView") cRotationRingView();
    gViewPrototypes[0x07292112] = (cView*)SP_NEW("Simulator/cRotationBallView") cRotationBallView();
    gViewPrototypes[0x07a309fb] = (cView*)SP_NEW("Simulator/cSpatialObjectView") cSpatialObjectView();
    gViewPrototypes[0x076c67df] = (cView*)SP_NEW("Simulator/cSpatialObjectView") cSpatialObjectView();
    gViewPrototypes[0x0771ad6a] = (cView*)SP_NEW("Simulator/cSpatialObjectView") cSpatialObjectView();
    gViewPrototypes[0x07a81824] = (cView*)SP_NEW("Simulator/cSpatialObjectView") cSpatialObjectView();
    gViewPrototypes[0x07abdd8d] = (cView*)SP_NEW("Simulator/cSpatialObjectView") cSpatialObjectView();
    gViewPrototypes[0x903c3ea3] = (cView*)SP_NEW("Simulator/cCitySoundLoopView") cCitySoundLoopView();
}

} // namespace Simulator
