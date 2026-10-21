// Slice s00fc2080 (batch gold3, slice 78).  Region 0x00fc2080-0x00fc2feb.
// SP terrain-terraform helpers: the radial distance/strength blend used by the
// terraform tool, the Simulator tuning update, and a handful of small config /
// refcount / raster-state accessors.
//
// 16 assigned VAs, 9 byte-exact.  Two manifest conventions are in play here and
// in the rest of this batch: slices 72-75, 78 and 79 list every assigned VA as a
// manifest row (the non-exact ones also appear in nonmatching.txt), while 76 and
// 77 list only the byte-exact functions and keep the rest in nonmatching.txt.
// This slice is of the first kind, so `run_all` here reports 16 functions and 9
// matches; the authoritative exact/total figures are in
// work/match/scratch_s79_final_summary.txt (batch total 96/202).
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
    float r = radius;
    r = (r > local[0]) ? r : local[0];
    r = (r < local[1]) ? r : local[1];

    float f = ((b - g_kLavaThreshold) * g_kLavaMaxCoverage) / (1.0f - g_kLavaThreshold);
    float v = (0.0f > f) ? 0.0f : f;

    return (v > r) ? v : r;
}

// @ 0xfc23b0
void UpdateTerrainTerraformTuning()
{
    PropListRef list;
    IPropManager* pm = SP::PropertyManager();
    Property* p;

    list.mpObject = 0;
    if (list.mpObject) {
        list.mpObject->Release();
        list.mpObject = 0;
    }
    pm->GetPropertyList(0xa6d1bc70u, 0x2ae0c7eu, &list.mpObject);

    if (!list.mpObject) return;
    if (list.mpObject->GetProperty(0x32a52a3u, p) && p->mnType == 0xd)
        g_kLavaThreshold = *p->GetValueFloat();

    if (!list.mpObject) return;
    if (list.mpObject->GetProperty(0x32a52a9u, p) && p->mnType == 0xd)
        g_kLavaMaxCoverage = *p->GetValueFloat();

    if (!list.mpObject) return;
    list.mpObject->GetProperty(0x32a54beu, p);

    if (!list.mpObject) return;
    if (list.mpObject->GetProperty(0x32a54beu, p) && p->mnType == 0xd)
        g_kTerraformRadiusT1 = *p->GetValueFloat();

    if (!list.mpObject) return;
    if (list.mpObject->GetProperty(0x32a5609u, p) && p->mnType == 0xd)
        g_kTerraformRadiusT2 = *p->GetValueFloat();

    if (!list.mpObject) return;
    if (list.mpObject->GetProperty(0x32a560au, p) && p->mnType == 0xd)
        g_kTerraformRadiusT3 = *p->GetValueFloat();

    if (!list.mpObject) return;
    if (list.mpObject->GetProperty(0x32a4b09u, p) && p->mnType == 0xd)
        g_kMinWaterPerfectScore = *p->GetValueFloat();

    if (!list.mpObject) return;
    if (list.mpObject->GetProperty(0x32a4b27u, p) && p->mnType == 0xd)
        g_kMinWaterRadius = *p->GetValueFloat();

    if (!list.mpObject) return;
    if (list.mpObject->GetProperty(0x333abe8u, p) && p->mnType == 0xd)
        g_kMinWaterIceThreshold = *p->GetValueFloat();

    if (!list.mpObject) return;
    if (list.mpObject->GetProperty(0x333af28u, p) && p->mnType == 0xd)
        g_kMinWaterIceVacuum = *p->GetValueFloat();

    if (!list.mpObject) return;
    if (list.mpObject->GetProperty(0x333ade9u, p) && p->mnType == 0xd)
        g_kMinWaterIceAtmosphere = *p->GetValueFloat();

    if (!list.mpObject) return;
    if (list.mpObject->GetProperty(0x333b2c0u, p) && p->mnType == 0xd)
        g_kMinWaterAtmosphere = *p->GetValueFloat();

    if (!list.mpObject) return;
    if (list.mpObject->GetProperty(0x333b6e5u, p) && p->mnType == 0xd)
        g_kMinWaterVacuumThreshold = *p->GetValueFloat();

    if (!list.mpObject) return;
    if (list.mpObject->GetProperty(0x3349823u, p) && p->mnType == 0xd)
        g_kMinWaterHeatLow = *p->GetValueFloat();

    if (!list.mpObject) return;
    if (list.mpObject->GetProperty(0x334982bu, p) && p->mnType == 0xd)
        g_kMinWaterHeatHigh = *p->GetValueFloat();

    if (!list.mpObject) return;
    if (list.mpObject->GetProperty(0x32a4b46u, p) && p->mnType == 0xd)
        g_kMaxWater = *p->GetValueFloat();

    if (!list.mpObject) return;
    if (list.mpObject->GetProperty(0x32a4b62u, p) && p->mnType == 0xd)
        g_kMaxWaterT2 = *p->GetValueFloat();

    if (list.mpObject)
        list.mpObject->Release();
}

// @ 0xfc2870
bool TerraPaint(float* a, float* b, float* normal, float* out)
{
    // t = a x b
    float t0 = a[1] * b[2] - a[2] * b[1];
    float t1 = a[0] * b[1] - a[1] * b[0];
    float t2 = a[2] * b[0] - a[0] * b[2];

    // r = t x normal, with the component pairing the original uses
    float r0 = normal[2] * t2 - normal[1] * t1;
    float r1 = normal[0] * t1 - normal[2] * t0;
    float r2 = normal[1] * t0 - normal[0] * t2;

    float len = (float)sqrt((double)(r2 * r2) + (double)(r1 * r1) + (double)(r0 * r0));
    float inv = (float)(1.0 / (double)len);

    out[0] = r0 * inv;
    out[1] = r1 * inv;
    out[2] = r2 * inv;

    // Blend the remaining three floats by the angle between the emitted
    // direction and a, relative to the angle between b and a.
    float d0 = out[0] * a[0] + out[1] * a[1] + out[2] * a[2];
    if (d0 > 1.0f) d0 = 1.0f;
    else if (d0 < 0.0f) d0 = 0.0f;

    float d1 = b[0] * a[0] + b[1] * a[1] + b[2] * a[2];
    if (d1 > 1.0f) d1 = 1.0f;
    else if (d1 < 0.0f) d1 = 0.0f;

    float t = (float)((double)acos((double)d0) / (double)acos((double)d1));

    out[3] = (b[3] - a[3]) * t + a[3];
    out[4] = a[4] + (b[4] - a[4]) * t;
    out[5] = (b[5] - a[5]) * t + a[5];
    return true;
}

// @ 0xfc2ab0
float TerraScatter(float* p)
{
    float v[6];
    SP::LightingManager()->GetDirection(v);

    // Two unit directions in the xy plane; the z components stay zero and are
    // kept explicit so the signed-zero behaviour matches the original.
    float inv1 = (float)(1.0 / sqrt((double)v[0] * (double)v[0]
                                    + (double)v[3] * (double)v[3] + 1e-8f));
    float a0 = inv1 * v[0];
    float a1 = inv1 * v[3];
    float z1 = inv1 * 0.0f;

    float inv2 = (float)(1.0 / sqrt((double)p[0] * (double)p[0]
                                    + (double)p[1] * (double)p[1] + 1e-8f));
    float b0 = inv2 * p[0];
    float b1 = p[1] * inv2;
    float z2 = inv2 * 0.0f;

    double x = ((double)b0 * z1 - (double)z2 * a1)
             + ((double)z2 * a0 - (double)b1 * z1) * 0.0
             + ((double)b1 * a1 - (double)b0 * a0);
    double y = (double)z2 * z1 + ((double)b1 * a0 + (double)b0 * a1);
    double ang = atan2(x, y);

    // Scale chain: (ang*0.31830987 + 1) * 12 * 60 * 60, kept in x87 in one
    // expression as the original does.
    return (float)(((ang * 0.31830987f) + 1.0f) * 12.0f * 60.0f * 60.0f);
}

// @ 0xfc2c70
void TerraSmooth(float* items, int* count, float* normal)
{
    unsigned char cls[16];
    float out[112];
    int n = *count;
    int kept = 0;
    bool allPos = true;
    bool allNeg = true;

    if (n <= 0) return;

    // Classify every item against the plane through `normal`.
    for (int i = 0; i < n; i++) {
        float* it = items + i * 7;
        bool pos = (it[0] * normal[0] + it[2] * normal[2]) + it[1] * normal[1] > 0.0f;
        cls[i] = pos;
        if (pos) allNeg = false; else allPos = false;
    }

    if (allPos) return;
    if (allNeg) {
        *count = 0;
        return;
    }

    // Keep the first item when it is on the positive side, then walk the
    // ring, painting one boundary item per sign change and copying every
    // positive run item after it.
    if (cls[0]) {
        for (int k = 0; k < 7; k++) out[k] = items[k];
        kept = 1;
    }

    float* dst = out + kept * 7;
    float* cur = items;
    unsigned char prev = cls[0];
    for (int i = 1; i <= n; i++) {
        int j = i % n;
        if (prev != cls[j]) {
            float tmp[7];
            if (prev)
                TerraPaint(cur, items + j * 7, normal, tmp);
            else
                TerraPaint(items + j * 7, cur, normal, tmp);
            kept++;
            for (int k = 0; k < 7; k++) *dst++ = tmp[k];
        }
        prev = cls[j];
        if (prev && i != n) {
            float* src = items + j * 7;
            kept++;
            for (int k = 0; k < 7; k++) *dst++ = src[k];
        }
        cur += 7;
    }

    *count = kept;
    TerraVectorInsert(items, out, (uint32_t)kept * 0x1c);
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
