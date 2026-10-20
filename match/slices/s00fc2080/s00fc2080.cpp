// Slice s00fc2080 (batch gold3, slice 78).  Region 0x00fc2080-0x00fc2feb.
// SP terrain-terraform helpers: the radial distance/strength blend used by the
// terraform tool, the Simulator tuning update, and a handful of small config /
// refcount / raster-state accessors.
#include "s00fc2080.h"

// ===========================================================================
// terraform distance / blend
// ===========================================================================

// @ 0xfc2080
uint32_t TerraDistClass(float x, float y)
{
    float r = (float)sqrt((double)((y - 0.5f) * (y - 0.5f) + (x - 0.5f) * (x - 0.5f)));
    if (r < 0.1f)
        return 3;
    if (r < 0.2f)
        return 2;
    if (r < 0.3f)
        return 1;
    return 0;
}

// @ 0xfc20e0
void TerraBlend(float* out, float a, float b)
{
    float fhi;
    float flo;
    float half = 0.5f;
    float d = (float)sqrt((double)((b - half) * (b - half) + (a - half) * (a - half)));
    float* pd = (half <= d) ? &half : &d;
    fhi = ((g_kMinWaterRadius - *pd) / g_kMinWaterRadius) * g_kMinWaterPerfectScore;
    flo = 0.0f;
    float* ph = (flo <= fhi) ? &fhi : &flo;
    flo = *ph;

    float ice = ((g_kMaxWater - a) * g_kMinWaterIceVacuum + g_kMinWaterIceAtmosphere * a) *
                ((g_kMinWaterIceThreshold - b) / g_kMinWaterIceThreshold);
    float zero = 0.0f;
    float* pi = (zero <= ice) ? &ice : &zero;
    ice = *pi;

    float heat = b;
    if (heat <= g_kMinWaterHeatLow) heat = g_kMinWaterHeatLow;
    if (g_kMinWaterHeatHigh <= heat) heat = g_kMinWaterHeatHigh;
    float h = (heat - g_kMinWaterHeatLow) / (g_kMinWaterHeatHigh - g_kMinWaterHeatLow);

    float vac = (g_kMaxWater - ((3.0f - h * 2.0f) * h) * h) *
                (((a - g_kMinWaterVacuumThreshold) * g_kMinWaterAtmosphere) /
                 (g_kMaxWater - g_kMinWaterVacuumThreshold));

    float* pm = (ice <= vac) ? &vac : &ice;
    float* pw = (*pm <= flo) ? &flo : pm;
    fhi = *pw;

    float t = a - g_kMaxWater;
    float rad = (g_kMaxWaterT2 - (b * b + t * t)) / (g_kMaxWaterT2 - 0.5f);
    float one = g_kMaxWater;
    float* pr = (rad <= one) ? &rad : &one;
    float r2 = g_kMaxWater * *pr;
    float* po = (r2 <= fhi) ? &fhi : &r2;
    out[1] = *po;
    out[0] = fhi;
}

// @ 0xfc2300
float TerraStrengthPick(float a, float b, float radius)
{
    float local[2];
    TerraBlend(local, a, b);
    float lo = local[0];
    float hi = local[1];
    float r = radius;
    if (r < lo) r = lo;
    if (hi < r) r = hi;

    float f = ((b - g_kLavaThreshold) * g_kLavaMaxCoverage) / (1.0f - g_kLavaThreshold);
    float v = 0.0f;
    if (f > 0.0f) v = f;

    return (v > r) ? v : r;
}

// @ 0xfc23b0
bool UpdateTerrainTerraformTuning()
{
    return false;
}

// @ 0xfc2870
void TerraPaint(float* out, void* a, void* b)
{
    (void)out; (void)a; (void)b;
}

// @ 0xfc2ab0
void TerraScatter(float* out, void* a, void* b)
{
    (void)out; (void)a; (void)b;
}

// @ 0xfc2c70
void TerraSmooth(float* out, void* a, void* b)
{
    (void)out; (void)a; (void)b;
}

// ===========================================================================
// raster state
// ===========================================================================

// @ 0xfc27e0
void RasterState::Assign(EmbeddedState* st, uint32_t stage, uint32_t value)
{
    if (st != 0 && (st->mHardStateDirty & (1u << stage)) != 0) {
        mpState = st;
        mStage = stage;
        mValue = value;
        mOld = st->D3D9GetTextureStageState(stage);
        st->SetRaster(stage, value);
    }
}

// @ 0xfc2c10
RasterState* RasterState::Construct(EmbeddedState* st, uint32_t stage, uint32_t value)
{
    mpState = 0;
    mStage = 0;
    mValue = 0;
    mOld = 0;
    if (st != 0 && (st->mHardStateDirty & (1u << stage)) != 0) {
        mpState = st;
        mStage = stage;
        mValue = value;
        mOld = st->D3D9GetTextureStageState(stage);
        st->SetRaster(stage, value);
    }
    return this;
}

// @ 0xfc2830
void RasterState::Clear()
{
    if (mpState != 0) {
        mpState->SetRaster(mStage, mOld);
        mpState = 0;
        mStage = 0;
        mValue = 0;
        mOld = 0;
    }
}

// ===========================================================================
// small config / bounds / refcount accessors
// ===========================================================================

// @ 0xfc2ec0
void SpTerraFill::Zero3(float* out, uint32_t tag)
{
    out[0] = 0.0f;
    out[1] = 0.0f;
    out[2] = 0.0f;
    (void)tag;
}

// @ 0xfc2ee0
void SpTerraBounds::CopyCorners(uint32_t* out)
{
    out[3] = ((uint32_t*)&mB)[0];
    out[4] = ((uint32_t*)&mB)[1];
    out[5] = ((uint32_t*)&mB)[2];
    out[0] = ((uint32_t*)&mA)[0];
    out[1] = ((uint32_t*)&mA)[1];
    out[2] = ((uint32_t*)&mA)[2];
}

// @ 0xfc2f10
void SpTerraConfig::SetBlendIndex(uint32_t idx)
{
    mBlendIndex = g_terraBlendTable[idx];
    mBlendPending = 0;
}

// @ 0xfc2f30
void SpTerraConfig::SetWeather(uint32_t idx)
{
    mpWeather = g_terraWeatherTable[idx];
}

// @ 0xfc2f50
uint32_t SpTerraConfig::GetTerraClass()
{
    uint32_t c = mTerraClass;
    uint32_t r = 1;
    if (c == 0 || c == 3 || c == 6)
        r = 0;
    else if (c == 2 || c == 5 || c == 8)
        r = 2;
    return r;
}

// @ 0xfc2f90
SpTerraRefOwner::~SpTerraRefOwner()
{
    mpVtbl0 = (void*)&g_terraRefVtbl0;
    mpVtbl4 = (void*)&g_terraRefVtbl4;
    GmeRefCount* p = (GmeRefCount*)mpRefB;
    if (p != 0) {
        int n = p->mRefs - 1;
        p->mRefs = n;
        if (n == 0) {
            p->mRefs = 1;
            ((void (__thiscall*)(GmeRefCount*, int))(*(void***)p)[0])(p, 1);
        }
    }
    p = (GmeRefCount*)mpRefA;
    if (p != 0) {
        int n = p->mRefs - 1;
        p->mRefs = n;
        if (n == 0) {
            p->mRefs = 1;
            ((void (__thiscall*)(GmeRefCount*, int))(*(void***)p)[0])(p, 1);
        }
    }
    mpVtbl4 = (void*)&g_gmeRefCountVtbl;
}
