// Shared declarations for slice s00fc2080.
// SP (Simulator) terrain-terraform helpers: the radial distance/strength blend
// used by the terraform tool, plus a few small config / refcount accessors.
#pragma once
#include "types.h"
#include <math.h>

// ---------------------------------------------------------------------------
// rw::graphics::EmbeddedState (external, other translation units)
// ---------------------------------------------------------------------------
namespace rw { namespace graphics {
struct EmbeddedState {
    char     pad00[0x10];
    uint32_t mHardStateDirty;   // +0x10
    uint32_t D3D9GetTextureStageState(uint32_t stage);            // 0x11ee870
    void     SetRaster(uint32_t stage, uint32_t value);           // 0x11ee6b0
};
}}

using rw::graphics::EmbeddedState;

// A 16-byte RAII "raster state" record.
class RasterState {
public:
    EmbeddedState* mpState;   // +0x00
    uint32_t       mStage;    // +0x04
    uint32_t       mValue;    // +0x08
    uint32_t       mOld;      // +0x0c
    void          Assign(EmbeddedState* st, uint32_t stage, uint32_t value);  // 0xfc27e0
    RasterState*  Construct(EmbeddedState* st, uint32_t stage, uint32_t value); // 0xfc2c10
    void          Clear();                                                    // 0xfc2830
};

// ---------------------------------------------------------------------------
// SP terrain config (blend index / weather / terrain class)
// ---------------------------------------------------------------------------
class SpTerraConfig {
public:
    char     pad00[0x68];
    void*    mpWeather;      // +0x68
    char     pad6c[0x140 - 0x6c];
    uint32_t mTerraClass;    // +0x140
    char     pad144[0x148 - 0x144];
    uint32_t mBlendIndex;    // +0x148
    uint32_t mBlendPending;  // +0x14c
    void     SetBlendIndex(uint32_t idx);   // 0xfc2f10
    void     SetWeather(uint32_t idx);      // 0xfc2f30
    uint32_t GetTerraClass();               // 0xfc2f50
};

// ---------------------------------------------------------------------------
// SP terrain bounds (two 3-vector corners)
// ---------------------------------------------------------------------------
class SpTerraBounds {
public:
    char  pad00[0xc];
    float mA[3];    // +0x0c
    float mB[3];    // +0x18
    void  CopyCorners(uint32_t* out);   // 0xfc2ee0
};

// ---------------------------------------------------------------------------
// SP object owning two reference-counted sub-objects
// ---------------------------------------------------------------------------
struct GmeRefCount {
    void** mpVtbl;   // +0x00
    int    mRefs;    // +0x04
};

class SpTerraRefOwner {
public:
    void* mpVtbl0;   // +0x00
    void* mpVtbl4;   // +0x04
    char  pad08[0x30 - 0x08];
    void* mpRefA;    // +0x30
    void* mpRefB;    // +0x34
    ~SpTerraRefOwner();   // 0xfc2f90
};

// ---------------------------------------------------------------------------
// free helpers
// ---------------------------------------------------------------------------
uint32_t TerraDistClass(float x, float y);                       // 0xfc2080
void     TerraBlend(float* out, float a, float b);               // 0xfc20e0
float    TerraStrengthPick(float a, float b, float radius);      // 0xfc2300
bool     UpdateTerrainTerraformTuning();                         // 0xfc23b0
void     TerraPaint(float* out, void* a, void* b);               // 0xfc2870
void     TerraScatter(float* out, void* a, void* b);             // 0xfc2ab0
void     TerraSmooth(float* out, void* a, void* b);              // 0xfc2c70
class SpTerraFill {
public:
    void Zero3(float* out, uint32_t tag);   // 0xfc2ec0
};

extern uint32_t g_terraBlendTable[];   // 0x149150c
extern void*    g_terraWeatherTable[]; // 0x149152c
extern int      g_terraRefVtbl0;       // 0x1491590
extern int      g_terraRefVtbl4;       // 0x149158c
extern int      g_gmeRefCountVtbl;     // 0x13ef094

// float tuning constants (in .rdata; only the values matter for behaviour)
extern float g_kMinWaterPerfectScore;
extern float g_kMinWaterRadius;
extern float g_kMinWaterIceVacuum;
extern float g_kMinWaterIceAtmosphere;
extern float g_kMinWaterIceThreshold;
extern float g_kMinWaterHeatLow;
extern float g_kMinWaterHeatHigh;
extern float g_kMinWaterVacuumThreshold;
extern float g_kMinWaterAtmosphere;
extern float g_kMaxWaterT2;
extern float g_kMaxWater;
extern float g_kLavaThreshold;
extern float g_kLavaMaxCoverage;
