// Slice s00fbf570 — SP::cTerrainStateMgr per-frame shader/lighting state update (retail layout).
// PDB candidate (caller-scored, unconfirmed): SP::cAppModeTerrainEditor::HandleSimulationUpdate.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"
#include <math.h>

#pragma warning(disable: 4035)
// EA math helpers, hand-written SSE in the original.
__forceinline int FloorToInt(float f)
{
    __asm {
        movss    xmm0, f
        cvtss2si eax, xmm0
        cvtsi2ss xmm1, eax
        mov      ecx, eax
        sub      ecx, 1
        ucomiss  xmm0, xmm1
        cmovb    eax, ecx
    }
}
#pragma warning(default: 4035)
__forceinline float Clamp(float value, float minValue, float maxValue)
{
    __asm {
        movss xmm0, value
        maxss xmm0, minValue
        minss xmm0, maxValue
        movss value, xmm0
    }
    return value;
}
__forceinline float Clamp01(float x)
{
    float one = 1.0f;
    __asm {
        xorps xmm0, xmm0
        maxss xmm0, x
        minss xmm0, one
        movss x, xmm0
    }
    return x;
}

struct Vector3 { float x, y, z; };
struct Vector2 { float x, y; };
struct Vector4 {
    float x, y, z, w;
    Vector4() {}
    Vector4(float ax, float ay, float az, float aw) : x(ax), y(ay), z(az), w(aw) {}
};
struct Matrix4 { float m[16]; };

inline float InvLength(const Vector3& v) { return 1.0f / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + 1e-8f); }

// ---- callees ---------------------------------------------------------------
struct cPropertyList { int GetModificationCount(); };    // 0x6237a0
struct cVersionedData {
    uint32_t pad00[12];
    cPropertyList* mpPropList;    // +0x30
    int mnVersion;                // +0x34
    int GetVersion() { return mnVersion + (mpPropList ? mpPropList->GetModificationCount() : 0); }
};

struct cTerrainMapSet {
    uint32_t pad00[13];
    float mRadius;                // +0x34
    float mMaxHeight;             // +0x38
    float mWaterHeight;           // +0x3c
    float mWaterDelta;            // +0x40
    float mBeachHeight;           // +0x44
    void SetTime(float t);        // 0xf924f0
};

struct cImage32 {
    uint32_t pad00[7];
    unsigned int mWidth;          // +0x1c
    uint32_t pad20[2];
    uint8_t* mpData;              // +0x28
};

struct cCamera { uint32_t pad00[12]; Vector3 mPosition; };   // +0x30

struct cCurve { uint32_t data[5]; };
float __cdecl EvalCurve(const cCurve* curve, float t);                        // 0xfb9870
Vector3 __cdecl EvalColorCurve(const cCurve* curve, float t);                 // 0xfb9950
float __cdecl GetAltitude(const Vector3* p);                                  // 0xfc2ab0

struct IGameMode;
struct IApp {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    virtual IGameMode* GetActiveMode();          // +0x38
};
namespace SP { IApp* __cdecl App(); }            // 0x67dd10
extern char g_GameModeEditor;                    // 0x1654c10

struct cTerrainEditor { bool IsActive(); };      // 0xf678a0
namespace SP { cTerrainEditor* __cdecl TerrainEditor(); }   // 0xf48a70
bool __cdecl IsWorldFlagSet(int flag);           // 0x685520

struct IRenderer {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4(); virtual void vb8();
    virtual void SetFogAmount(float f);          // +0xbc
    virtual void SetAtmosphereAmount(float f);   // +0xc0
};
IRenderer* __cdecl GetRenderer();                // 0x67de00

void __cdecl SetShaderConstant(int id, const void* data, int count);   // 0x777ae0

struct cLightingParams {      // 0x98 bytes
    float mSunIntensity;      // +0x00
    float mShadowIntensity;   // +0x04
    float mTimeOfDay;         // +0x08
    float mAtmosphereTop;     // +0x0c
    float mCameraHeight;      // +0x10
    Vector4 mScatter;         // +0x14
    Vector4 mSunDir;          // +0x24
    Vector4 mColor0;          // +0x34
    Vector4 mColor1;          // +0x44
    Vector4 mColor2;          // +0x54
    Vector4 mColorAlpha;      // +0x64
    Vector4 mColorScale;      // +0x74
    uint32_t pad84[4];
    float mExposure;          // +0x94
};
struct cLightBuffer { uint32_t data[17]; };

struct ILightingManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24();
    virtual void SetSunLights(const Vector4* sunDir, int count, cLightBuffer* lights);   // +0x28
    virtual void SetParams(const cLightingParams* params);                              // +0x2c
};
namespace SP { ILightingManager* __cdecl LightingManager(); }   // 0x67dd90

struct cLightColor { float mAlpha; float mScaleA; float mScaleB; float pad; };

// ---- cTerrainStateMgr (retail offsets) -------------------------------------
struct cTerrainStateMgr {
    uint32_t pad000;
    cTerrainMapSet* mpMapSet;     // +0x004
    uint32_t pad008[4];
    float m018;                   // +0x018
    uint32_t pad01c[3];
    float m028;                   // +0x028
    float mTimeOfDay;             // +0x02c
    float mLatitude;              // +0x030
    Vector3 mSunDir;              // +0x034
    Matrix4 mSunMatrix;           // +0x040
    uint32_t pad080[13];
    Vector4 m0b4;                 // +0x0b4
    uint32_t pad0c4;
    Vector3 mColorA0;             // +0x0c8
    Vector3 mColorB0;             // +0x0d4
    Vector3 mColorA1;             // +0x0e0
    Vector3 mColorB1;             // +0x0ec
    Vector3 mColorA2;             // +0x0f8
    Vector3 mColorB2;             // +0x104
    Vector4 m110;                 // +0x110
    uint32_t pad120[2];
    cCurve mHeightCurve;          // +0x128
    float m13c, m140, m144, m148; // +0x13c
    float mShadowMin;             // +0x14c
    float mShadowMax;             // +0x150
    float mSunScale;              // +0x154
    uint32_t pad158[25];
    cCurve mSkyColorCurve;        // +0x1bc
    cCurve mSkyAmountCurve;       // +0x1d0
    uint32_t pad1e4;
    float m1e8;                   // +0x1e8
    uint32_t pad1ec[2];
    cImage32* mpSkyRamp;          // +0x1f4
    float mFogDistance;           // +0x1f8
    float mExposure;              // +0x1fc
    uint32_t pad200[25];
    bool mUseFixedSky;            // +0x264
    uint8_t pad265[3];
    uint32_t pad268[6];
    float mSkyBrightness;         // +0x280
    float mSkyRadius;             // +0x284
    float mTerrainScaleDist;      // +0x288
    uint32_t pad28c[48];
    Vector4 mOut34c;              // +0x34c
    Vector4 mOutColorA0;          // +0x35c
    Vector4 mOutColorA1;          // +0x36c
    Vector4 mOutColorA2;          // +0x37c
    Vector4 mOutColorB0;          // +0x38c
    Vector4 mOutColorB1;          // +0x39c
    Vector4 mOutColorB2;          // +0x3ac
    Vector4 mOut3bc;              // +0x3bc
    Vector4 mLightColor[3];       // +0x3cc
    cLightColor mLightScale[3];   // +0x3fc
    float mSky[4];                // +0x42c (b, g, r, a)
    float m43c, m440, m444, m448, m44c;   // +0x43c
    uint32_t pad450[3];
    Vector3 mCameraPos;           // +0x45c
    float mCameraPosW;            // +0x468
    Vector3 mOutSunDir;           // +0x46c
    float mOutSunDirW;            // +0x478
    Matrix4 mOutSunMatrix;        // +0x47c
    float mRadius;                // +0x4bc
    float mMaxHeight;             // +0x4c0
    float mAtmosphereHeight;      // +0x4c4
    float mAtmosphereFade;        // +0x4c8
    float mCameraDistance;        // +0x4cc
    float mCameraAltitude;        // +0x4d0
    float m4d4, m4d8;             // +0x4d4
    float m4dc, m4e0, m4e4, m4e8; // +0x4dc
    float mShadowIntensity;       // +0x4ec
    float mExposureOut;           // +0x4f0
    float mSunIntensity;          // +0x4f4
    uint32_t pad4f8;
    float mLatitudeOut;           // +0x4fc
    float mTimeOfDayInv;          // +0x500
    float m504;                   // +0x504
    uint32_t pad508[41];
    bool mbEnabled;               // +0x5ac
    uint8_t pad5ad[3];
    cVersionedData* mpPlanetData; // +0x5b0
    int mPlanetDataVersion;       // +0x5b4
    cVersionedData* mpTuning;     // +0x5b8
    int mTuningVersion;           // +0x5bc
    uint32_t pad5c0[2];
    Vector4 mLight[3];            // +0x5c8
    uint32_t pad5f8[8];
    float m618;                   // +0x618
    float mMapTime;               // +0x61c
    uint32_t pad620[103];
    bool mbUpdateSeasons;         // +0x7bc

    void Initialize();                                          // 0xfbe7d0
    void ApplyTuning();                                         // 0xfb8ae0
    float UpdateSeasons(float v);                               // 0xfbd8b0
    float ComputeAmbient();                                     // 0xfb88d0
    void SetCloudCover(float t, int flags);                     // 0xfbc770
    void ComputeSunLight(Vector2* out, float altitude, int a);  // 0xfb9610
    float GetSunAngleFactor(float altitude);                    // 0xfb9740
    void UpdateWater();                                         // 0xfbdc60
    void BuildSunLights(cLightBuffer* out, int flags);          // 0xfbc290

    __forceinline void SetLight(int i)
    {
        float s = mLightScale[i].mScaleB * mLightScale[i].mScaleA;
        mLight[i].x = s * mLightColor[i].x;
        mLight[i].y = mLightColor[i].y * s;
        mLight[i].z = mLightColor[i].z * s;
        mLight[i].w = mLightColor[i].w * s;
        mLight[i].w = mLightScale[i].mAlpha;
    }

    void Update(cCamera* camera, int unused, int lightArg);
};

// @ 0x00fbf570
void cTerrainStateMgr::Update(cCamera* camera, int unused, int lightArg)
{
    if (!mbEnabled)
        return;

    if (mPlanetDataVersion != mpPlanetData->GetVersion()) {
        Initialize();
        mPlanetDataVersion = mpPlanetData->GetVersion();
    }
    if (IsWorldFlagSet(2)) {
        if (mTuningVersion != mpTuning->GetVersion()) {
            ApplyTuning();
            mTuningVersion = mpTuning->GetVersion();
        }
    }

    mLatitudeOut = mLatitude;
    mTimeOfDayInv = 1.0f - mTimeOfDay;
    if (mbUpdateSeasons)
        UpdateSeasons(m018);
    m504 = m028;
    m44c = ComputeAmbient();
    m618 = 0.0f;
    mpMapSet->SetTime(mMapTime);

    Vector3 camPos;
    camPos.x = 0.0f;
    camPos.y = 500.0f;
    camPos.z = 0.0f;
    if (camera)
        camPos = camera->mPosition;

    cTerrainMapSet* mapSet = mpMapSet;
    float radius = mapSet->mRadius;
    float maxHeight = mapSet->mMaxHeight;
    float waterLevel = (mapSet->mWaterDelta + mapSet->mWaterHeight) * mapSet->mMaxHeight;
    float beachLevel = (mapSet->mBeachHeight + mapSet->mWaterHeight) * mapSet->mMaxHeight;
    float distance = sqrtf(camPos.y * camPos.y + (camPos.z * camPos.z + camPos.x * camPos.x));
    if (SP::TerrainEditor()->IsActive())
        distance = 1000.0f;

    if (!mUseFixedSky && SP::App()->GetActiveMode() != (IGameMode*)&g_GameModeEditor) {
        cImage32* ramp = mpSkyRamp;
        int idx = FloorToInt((float)(ramp->mWidth - 1) * mLatitude);
        const uint8_t* px = ramp->mpData + idx * 4;
        mSky[2] = px[0] * (1.0f / 255.0f);
        mSky[1] = px[1] * (1.0f / 255.0f);
        mSky[0] = px[2] * (1.0f / 255.0f);
        mSky[3] = px[3] * (1.0f / 255.0f);
    } else {
        mSky[0] = mSkyBrightness;
        mSky[1] = mSkyRadius;
        mSky[3] = 1.0f;
        mSky[2] = mTerrainScaleDist;
    }
    m43c = 0.0f;
    m440 = m1e8;
    m444 = beachLevel;
    m448 = waterLevel;

    float altitude = distance - radius;
    float fog = Clamp(altitude / mFogDistance, 0.0f, 1.0f);
    SetCloudCover(fog * 0.6f + 0.39f, 0);
    float atmosphere = EvalCurve(&mHeightCurve, 1.0f - mTimeOfDay) * mpMapSet->mMaxHeight;

    mCameraPos = camPos;
    mCameraPosW = 1.0f;
    mOutSunDir = mSunDir;
    mOutSunDirW = 0.0f;
    mOutSunMatrix = mSunMatrix;
    mAtmosphereHeight = atmosphere;
    mRadius = radius;
    mMaxHeight = maxHeight;
    float fade = Clamp01(altitude / (atmosphere + 1e-6f));
    mAtmosphereFade = ((1.0f - fade) + 1.0f) * 0.5f;
    mCameraDistance = distance;
    mCameraAltitude = altitude;
    m4d4 = 0.0f;
    m4d8 = 0.0f;
    m4dc = m13c;
    m4e0 = m140;
    m4e4 = m148;
    m4e8 = m144;

    mOutColorA0 = Vector4(mColorA0.x, mColorA0.y, mColorA0.z, 0.0f);
    mOutColorA1 = Vector4(mColorA1.x, mColorA1.y, mColorA1.z, 0.0f);
    mOutColorA2 = Vector4(mColorA2.x, mColorA2.y, mColorA2.z, 0.0f);
    mOutColorB0 = Vector4(mColorB0.x, mColorB0.y, mColorB0.z, 0.0f);
    mOutColorB1 = Vector4(mColorB1.x, mColorB1.y, mColorB1.z, 0.0f);
    mOutColorB2 = Vector4(mColorB2.x, mColorB2.y, mColorB2.z, 0.0f);
    mOut3bc = m110;
    mOut34c = m0b4;

    Vector2 sun;
    ComputeSunLight(&sun, altitude, lightArg);
    float angleFactor = GetSunAngleFactor(GetAltitude(&camPos));
    float dayFraction = 1.0f - mTimeOfDay;
    Vector3 skyColor = EvalColorCurve(&mSkyColorCurve, dayFraction);
    float skyAmount = EvalCurve(&mSkyAmountCurve, altitude);

    mShadowIntensity = -((((mShadowMax - mShadowMin) * dayFraction + mShadowMin) * sun.y) * mAtmosphereFade * skyColor.y);
    mExposureOut = mExposure;
    mSunIntensity = mSunScale * sun.x + skyAmount * angleFactor + skyColor.x * skyAmount;
    if (mSunIntensity < 0.0f)
        mSunIntensity = 0.0f;

    float invSun = InvLength(mSunDir);
    float invCam = InvLength(camPos);
    float sunDot = (invCam * camPos.x) * (invSun * mSunDir.x)
                 + (invCam * camPos.z) * (invSun * mSunDir.z)
                 + (invCam * camPos.y) * (invSun * mSunDir.y);

    float daylight = Clamp(altitude / atmosphere, 0.0f, 1.0f);
    float fogAmount = daylight;
    GetRenderer()->SetAtmosphereAmount(daylight);
    if (sunDot < 0.0f)
        fogAmount = fabsf(sunDot) + daylight;
    GetRenderer()->SetFogAmount(Clamp(fogAmount, 0.0f, 1.0f));

    UpdateWater();

    static Vector4 sSunDir;
    sSunDir.x = mSunDir.x;
    sSunDir.y = mSunDir.y;
    sSunDir.z = mSunDir.z;
    sSunDir.w = cosf(mOut3bc.z * 0.017453292f);
    SetShaderConstant(0x24b, &sSunDir, 1);
    SetShaderConstant(0x23d, &mLatitudeOut, 1);
    SetShaderConstant(0x252, &mSunMatrix, 1);

    ILightingManager* lm = SP::LightingManager();
    if (lm) {
        SetLight(0);
        SetLight(1);
        SetLight(2);
        cLightBuffer lights;
        BuildSunLights(&lights, 0);
        lm->SetSunLights(&sSunDir, 3, &lights);

        cLightingParams params;
        params.mExposure = mExposure;
        params.mShadowIntensity = mShadowIntensity;
        params.mSunIntensity = mSunIntensity;
        params.mTimeOfDay = 1.0f - mTimeOfDay;
        params.mAtmosphereTop = mAtmosphereHeight + mRadius;
        params.mCameraHeight = distance - (atmosphere + radius);
        params.mScatter = Vector4(0.43f, 0.49f, 1.0f, 1.0f);
        params.mSunDir = sSunDir;
        params.mColor0 = mLightColor[0];
        params.mColor1 = mLightColor[1];
        params.mColor2 = mLightColor[2];
        params.mColorAlpha = Vector4(mLightScale[0].mAlpha, mLightScale[1].mAlpha, mLightScale[2].mAlpha, 0.0f);
        params.mColorScale.x = mLightScale[0].mScaleB * mLightScale[0].mScaleA * 10.0f;
        params.mColorScale.y = mLightScale[1].mScaleB * mLightScale[1].mScaleA * 10.0f;
        params.mColorScale.z = mLightScale[2].mScaleB * mLightScale[2].mScaleA * 10.0f;
        params.mColorScale.w = 0.0f;
        lm->SetParams(&params);
    }
}
