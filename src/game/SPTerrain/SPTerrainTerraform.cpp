// src/game/SPTerrain/SPTerrainTerraform.cpp -- migrated from slice(s) s00fc2080, s00fc10d0 by tools/migrate/rewrite.py
// Object file: SPTerrain/SPTerrainTerraform.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>
#include "rw/graphics/EmbeddedState.h"

// unnamed retail callees and globals that name local stubs (address in the comment)
extern float kLavaThreshold;

// ---- items of slice s00fc2080 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_kLavaThreshold;           // 0x15b1658  kLavaThreshold
extern float g_kLavaMaxCoverage;         // 0x15b165c  kLavaMaxCoverage
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
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
    virtual bool GetProperty(uint32_t propertyID, Property*& result);   // +0x24
};
class IPropManager {
public:
virtual void m0();
virtual void m1();
virtual void m2();
virtual void m3();
virtual void m4();
virtual void m5();
virtual void m6();
virtual void m7();
virtual void m8();
virtual void m9();
virtual void m10();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID,
                                 PropertyList** out);            // +0x2c
};
namespace SP {
 IPropManager* PropertyManager();   // 0x0067de30
}
struct PropListRef {
    PropertyList* mpObject;
};
uint32_t TerraDistClass(float x, float y);                       // 0xfc2080
void     TerraBlend(float* out, float a, float b);               // 0xfc20e0
float    TerraStrengthPick(float a, float b, float radius);      // 0xfc2300
extern float g_kTerraformRadiusT1;       // 0x15b1660  kTerraformRadiusT1
extern float g_kTerraformRadiusT2;       // 0x15b1664  kTerraformRadiusT2
extern float g_kTerraformRadiusT3;       // 0x15b1668  kTerraformRadiusT3
// ---- items of slice s00fc2080 end

// @ 0x00fc1fd0
namespace SP {
unsigned int GetTerraformPlanetType(float f)
{
    if (f < 0.1f) return 2;
    if (f >= 0.1f && f < 0.4f) return 3;
    if (f >= 0.4f && f < 0.6f) return 1;
    if (f < 0.6f || kLavaThreshold <= f) return 4;
    return 5;
}
}  // namespace SP

// The original computes the whole falloff in x87 and takes the root with an inline fsqrt.
// cl only inlines sqrt under /fp:fast, which this module's flags do not use, so do the root
// with x87 directly (double keeps enough precision that the float result matches).
static inline double SqrtX87(double v)
{
    __asm fld v
    __asm fsqrt
    __asm fstp v
    return v;
}

// @ 0x00fc2040
float __cdecl FUN_00fc2040(float x, float y)
{
    double dx = (double)x - 0.5;
    double dy = (double)y - 0.5;
    float f = (float)(1.0 - SqrtX87(dy * dy + dx * dx) * (double)1.4142135f);
    float r = 0.0f;
    if (0.0f <= f) r = f;
    return r;
}

// @ 0x00fc2080
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

// @ 0x00fc20e0
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

// @ 0x00fc2300
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

// @ 0x00fc23b0
namespace SP {
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
}  // namespace SP
