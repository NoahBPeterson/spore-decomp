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
class EmbeddedState { public:
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
// SP property system (external; the same interfaces are used by other slices)
// ---------------------------------------------------------------------------
class Property {
public:
    float*   GetValueFloat();     // 0x41ea70  SP::GetPropertyAsFloat
    uint16_t pad[9];
    uint16_t mnType;              // +0x12  (0xd = float)
};

class PropertyList {
public:
    virtual int  AddRef();                                       // +0x00
    virtual int  Release();                                      // +0x04
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool GetProperty(uint32_t propertyID, Property*& result);   // +0x24
};

class IPropManager {
public:
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
    virtual void m4(); virtual void m5(); virtual void m6(); virtual void m7();
    virtual void m8(); virtual void m9(); virtual void m10();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID,
                                 PropertyList** out);            // +0x2c
};

namespace SP { IPropManager* PropertyManager(); }                // 0x0067de30

// Owning pointer used by the tuning loader. The release sites are explicit:
// the original function has no unwind table, so this must stay a plain struct.
struct PropListRef {
    PropertyList* mpObject;
};

// ---------------------------------------------------------------------------
// SP lighting manager (external)
// ---------------------------------------------------------------------------
class ILightingManager {
public:
    virtual void l0(); virtual void l1(); virtual void l2(); virtual void l3();
    virtual void l4(); virtual void l5(); virtual void l6(); virtual void l7();
    virtual void l8();
    virtual void GetDirection(float* out);   // +0x24 (only call site: 0xfc2ab0)
};

namespace SP { ILightingManager* LightingManager(); }             // 0x0067dd90

// Fixed-vector insert helper: copies `bytes` bytes of `src` into `dst`.
void TerraVectorInsert(void* dst, const void* src, uint32_t bytes);  // 0x11e0744

// ---------------------------------------------------------------------------
// free helpers
// ---------------------------------------------------------------------------
uint32_t TerraDistClass(float x, float y);                       // 0xfc2080
void     TerraBlend(float* out, float a, float b);               // 0xfc20e0
float    TerraStrengthPick(float a, float b, float radius);      // 0xfc2300
void     UpdateTerrainTerraformTuning();                         // 0xfc23b0
__declspec(noinline)
bool     TerraPaint(float* a, float* b, float* normal, float* out);   // 0xfc2870
float    TerraScatter(float* p);                                 // 0xfc2ab0
void     TerraSmooth(float* items, int* count, float* normal);   // 0xfc2c70
class SpTerraFill {
public:
    void Zero3(float* out, uint32_t tag);   // 0xfc2ec0
};

extern uint32_t g_terraBlendTable[];   // 0x149150c
extern void*    g_terraWeatherTable[]; // 0x149152c
extern int      g_terraRefVtbl0;       // 0x1491590
extern int      g_terraRefVtbl4;       // 0x149158c
extern int      g_gmeRefCountVtbl;     // 0x13ef094

// float tuning constants (in .data/.rdata; only the values matter for behaviour)
extern float g_kLavaThreshold;           // 0x15b1658  kLavaThreshold
extern float g_kLavaMaxCoverage;         // 0x15b165c  kLavaMaxCoverage
extern float g_kTerraformRadiusT1;       // 0x15b1660  kTerraformRadiusT1
extern float g_kTerraformRadiusT2;       // 0x15b1664  kTerraformRadiusT2
extern float g_kTerraformRadiusT3;       // 0x15b1668  kTerraformRadiusT3
extern float g_kMinWaterPerfectScore;    // 0x16d6f0c  kMinWaterWithPerfectScore
extern float g_kMinWaterRadius;          // 0x16d6f10  kMinWaterRadius
extern float g_kMinWaterIceThreshold;    // 0x16d6f14  kMinWaterIceThreshold
extern float g_kMinWaterIceVacuum;       // 0x16d6f18  kMinWaterIceVacuum
extern float g_kMinWaterIceAtmosphere;   // 0x16d6f1c  kMinWaterIceAtmosphere
extern float g_kMinWaterAtmosphere;      // 0x16d6f20  kMinWaterAtmosphere
extern float g_kMinWaterVacuumThreshold; // 0x16d6f24  kMinWaterVacuumThreshold
extern float g_kMinWaterHeatLow;         // 0x16d6f28  kMinWaterHeatThresholdLow
extern float g_kMinWaterHeatHigh;        // 0x16d6f2c  kMinWaterHeatThresholdHigh
extern float g_kMaxWater;                // 0x16d6f30  kMaxWater
extern float g_kMaxWaterT2;              // 0x16d6f34  kMaxWaterThreshold2
