// Slice s0137bcc0 -- dynamic initializer for SP::FIELDS_DT_CELL_GLOBALS
// (the ?FIELDS_DT_CELL_GLOBALS@SP@@3PAUcFieldDef@1@A table of SP::cFieldDef).
// The source is the real global aggregate below; cl 2008 lowers it to the
// compiler-generated `??__E` initializer at 0x0137bcc0.
#include "types.h"

// Non-inlinable accessors used by the table initializers (they live in another
// translation unit; the compiler emits a call for every field value they wrap).
extern int Conv(int);
extern int ConvF(float);
extern uint32_t sHash(const char*);

// Type description / enum-table globals referenced by the table.
extern int g_dtCellType;      // 0x016ad3d0
extern int g_vcTypeDef;       // VC type-def marker (elem "startCell")
extern int g_dtEffectMap;     // DT_EFFECTMAP
extern int g_dtBackgroundMap; // DT_BACKGROUNDMAP
extern int g_dtLookAlgorithm; // DT_LOOK_ALGORITHM
extern int g_enumGameMode;    // 0x01482bf0
extern int g_enumControlMethod;
extern int g_enumEditorMethod;
extern int g_enumTutorialMethod;
extern int g_enumEndingMethod;
extern int g_enumEyeMethod;

namespace SP {

struct cFieldDef {
    const char* name;             // +0x00
    int         hash_name;        // +0x04
    int         variable_offset;  // +0x08
    int         variable_aux_offset; // +0x0c
    int         type;             // +0x10
    int         type_aux;         // +0x14
    int         argument_index;   // +0x18
    int         default_value;    // +0x1c
    int         field_flags;      // +0x20
    int         enum_table;       // +0x24
};

#define OBJ  Conv(3), Conv((int)&g_dtCellType), 0, Conv(0), 4, 0
#define FLT(v) Conv(2), Conv(0), 0, ConvF(v), 6, 0

// @ 0x0137bcc0
cFieldDef FIELDS_DT_CELL_GLOBALS[] = {
    /* 0*/ { "world_1", sHash("world_1"), 4, 0, OBJ },
    /* 1*/ { "worldBackground_1", sHash("worldBackground_1"), 0x18, 0, OBJ },
    /* 2*/ { "world_2", sHash("world_2"), 8, 0, OBJ },
    /* 3*/ { "worldBackground_2", sHash("worldBackground_2"), 0x1c, 0, OBJ },
    /* 4*/ { "world_3", sHash("world_3"), 0xc, 0, OBJ },
    /* 5*/ { "worldBackground_3", sHash("worldBackground_3"), 0x20, 0, OBJ },
    /* 6*/ { "world_4", sHash("world_4"), 0x10, 0, OBJ },
    /* 7*/ { "worldBackground_4", sHash("worldBackground_4"), 0x24, 0, OBJ },
    /* 8*/ { "world_5", sHash("world_5"), 0x14, 0, OBJ },
    /* 9*/ { "worldBackground_5", sHash("worldBackground_5"), 0x28, 0, OBJ },
    /*10*/ { "worldRandom", sHash("worldRandom"), 0x2c, 0, OBJ },
    /*11*/ { "worldRandomBg", sHash("worldRandomBg"), 0x30, 0, OBJ },
    /*12*/ { "startingCellKey", sHash("startingCellKey"), 0x38, 0x38, Conv(7), Conv(0), 0, Conv(0), 6, 0 },
    /*13*/ { "startCell", sHash("startCell"), 0x34, 0, Conv(3), Conv((int)&g_vcTypeDef), 0, Conv(0), 4, 0 },
    /*14*/ { "effectMapEntry", sHash("effectMapEntry"), 0x3c, 0, Conv(3), Conv((int)&g_dtEffectMap), 0, Conv(0), 4, 0 },
    /*15*/ { "backgroundMapEntry", sHash("backgroundMapEntry"), 0x40, 0, Conv(3), Conv((int)&g_dtBackgroundMap), 0, Conv(0), 4, 0 },
    /*16*/ { "flowMultiplier", sHash("flowMultiplier"), 0x44, 0, FLT(25.0f) },
    /*17*/ { "npcSpeedMultiplier", sHash("npcSpeedMultiplier"), 0x48, 0, FLT(1.0f) },
    /*18*/ { "npcTurnSpeedMultiplier_Jet", sHash("npcTurnSpeedMultiplier_Jet"), 0x4c, 0, FLT(1.0f) },
    /*19*/ { "npcTurnSpeedMultiplier_Flagella", sHash("npcTurnSpeedMultiplier_Flagella"), 0x50, 0, FLT(1.0f) },
    /*20*/ { "npcTurnSpeedMultiplier_Cilia", sHash("npcTurnSpeedMultiplier_Cilia"), 0x54, 0, FLT(1.0f) },
    /*21*/ { "densityRock", sHash("densityRock"), 0x58, 0, FLT(100.0f) },
    /*22*/ { "densitySolid", sHash("densitySolid"), 0x5c, 0, FLT(10.0f) },
    /*23*/ { "densityLiquid", sHash("densityLiquid"), 0x60, 0, FLT(1.0f) },
    /*24*/ { "densityAir", sHash("densityAir"), 0x64, 0, FLT(0.1f) },
    /*25*/ { "backgroundDistance", sHash("backgroundDistance"), 0x68, 0, FLT(10.0f) },
    /*26*/ { "minDragCollisionSpeed", sHash("minDragCollisionSpeed"), 0x6c, 0, FLT(0.1f) },
    /*27*/ { "minImpactCollisionSpeed", sHash("minImpactCollisionSpeed"), 0x70, 0, FLT(1.0f) },
    /*28*/ { "ciliaSpeedAsJet", sHash("ciliaSpeedAsJet"), 0x74, 0, FLT(1.0f) },
    /*29*/ { "flagellaSpeedAsJet", sHash("flagellaSpeedAsJet"), 0x78, 0, FLT(1.0f) },
    /*30*/ { "flagellaSpeedAsCilia", sHash("flagellaSpeedAsCilia"), 0x7c, 0, FLT(1.0f) },
    /*31*/ { "ciliaSpeedAsFlagella", sHash("ciliaSpeedAsFlagella"), 0x80, 0, FLT(1.0f) },
    /*32*/ { "keyLookAlgorithm", sHash("keyLookAlgorithm"), 0x84, 0, Conv(3), Conv((int)&g_dtLookAlgorithm), 0, Conv(0), 4, 0 },
    /*33*/ { "beachDistance", sHash("beachDistance"), 0x88, 0, FLT(20.0f) },
    /*34*/ { "finishLineDistance", sHash("finishLineDistance"), 0x8c, 0, FLT(20.0f) },
    /*35*/ { "noPartSpeed", sHash("noPartSpeed"), 0x90, 0, FLT(1.0f) },
    /*36*/ { "flagellaRampMinFactor", sHash("flagellaRampMinFactor"), 0x94, 0, FLT(0.5f) },
    /*37*/ { "flagellaRampTime", sHash("flagellaRampTime"), 0x98, 0, FLT(2.0f) },
    /*38*/ { "flagellaRampResetAngle", sHash("flagellaRampResetAngle"), 0x9c, 0, FLT(30.0f) },
    /*39*/ { "flagellaTurnSpeedRampStart", sHash("flagellaTurnSpeedRampStart"), 0xa0, 0, FLT(1.0f) },
    /*40*/ { "flagellaTurnSpeedRampEnd", sHash("flagellaTurnSpeedRampEnd"), 0xa4, 0, FLT(2.0f) },
    /*41*/ { "flagellaTurnSpeedMin", sHash("flagellaTurnSpeedMin"), 0xa8, 0, FLT(3.0f) },
    /*42*/ { "flagellaTurnSpeedMax", sHash("flagellaTurnSpeedMax"), 0xac, 0, FLT(10.0f) },
    /*43*/ { "ciliaTurnSpeed", sHash("ciliaTurnSpeed"), 0xb0, 0, FLT(0.75f) },
    /*44*/ { "jetTurnSpeed", sHash("jetTurnSpeed"), 0xb4, 0, FLT(3.0f) },
    /*45*/ { "startLevelNoCreatureRadius", sHash("startLevelNoCreatureRadius"), 0xb8, 0, FLT(10.0f) },
    /*46*/ { "startLevelNoAnythingRadius", sHash("startLevelNoAnythingRadius"), 0xbc, 0, FLT(3.0f) },
    /*47*/ { "numHighLOD_FG", sHash("numHighLOD_FG"), 0xc0, 0, Conv(1), Conv(0), 0, Conv(10), 6, 0 },
    /*48*/ { "numHighLOD_BG", sHash("numHighLOD_BG"), 0xc4, 0, Conv(1), Conv(0), 0, Conv(2), 6, 0 },
    /*49*/ { "percentAnimalFood", sHash("percentAnimalFood"), 0xc8, 0, FLT(0.35f) },
    /*50*/ { "percentPlantFood", sHash("percentPlantFood"), 0xcc, 0, FLT(0.35f) },
    /*51*/ { "gameMode", sHash("gameMode"), 0, 0, Conv(5), Conv(0), 0, Conv(0), 6, (int)&g_enumGameMode },
    /*52*/ { "controlMethod", sHash("controlMethod"), 0xd4, 0, Conv(5), Conv(0), 0, Conv(0), 6, (int)&g_enumControlMethod },
    /*53*/ { "editorMethod", sHash("editorMethod"), 0xd8, 0, Conv(5), Conv(0), 0, Conv(0), 6, (int)&g_enumEditorMethod },
    /*54*/ { "tutorialMethod", sHash("tutorialMethod"), 0xdc, 0, Conv(5), Conv(0), 0, Conv(0), 6, (int)&g_enumTutorialMethod },
    /*55*/ { "endingMethod", sHash("endingMethod"), 0xe0, 0, Conv(5), Conv(0), 0, Conv(0), 6, (int)&g_enumEndingMethod },
    /*56*/ { "eyeMethod", sHash("eyeMethod"), 0xe4, 0, Conv(5), Conv(0), 0, Conv(0), 6, (int)&g_enumEyeMethod },
    /*57*/ { "timeToGoldyCinematic", sHash("timeToGoldyCinematic"), 0xe8, 0, FLT(15.0f) },
    /*58*/ { "missionTime", sHash("missionTime"), 0xec, 0, FLT(10.0f) },
    /*59*/ { "missionResetTime", sHash("missionResetTime"), 0xf0, 0, FLT(3.0f) },
    /*60*/ { "escapeMinDistance", sHash("escapeMinDistance"), 0xf4, 0, FLT(8.0f) },
    /*61*/ { "escapeMaxDistance", sHash("escapeMaxDistance"), 0xf8, 0, FLT(20.0f) },
    /*62*/ { "escapeDelayMedium", sHash("escapeDelayMedium"), 0xfc, 0, FLT(20.0f) },
    /*63*/ { "escapeTimerHard", sHash("escapeTimerHard"), 0x100, 0, FLT(20.0f) },
    /*64*/ { "nonAnimatingJetMovementFactor", sHash("nonAnimatingJetMovementFactor"), 0x108, 0, FLT(10.0f) },
    /*65*/ { "nonAnimatingCiliaMovementFactor", sHash("nonAnimatingCiliaMovementFactor"), 0x104, 0, FLT(10.0f) },
    /*66*/ { "mateTriggerDistance", sHash("mateTriggerDistance"), 0x10c, 0, FLT(4.0f) },
    /*67*/ { "mateSpawnDistance", sHash("mateSpawnDistance"), 0x110, 0, FLT(1.0f) },
    /*68*/ { 0, sHash(0), -1, 0, Conv(0), Conv(0), 0, Conv(0), 0, 0 },
};

} // namespace SP
