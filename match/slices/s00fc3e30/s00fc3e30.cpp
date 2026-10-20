// Slice s00fc3e30: SP::cWeatherManager weather-state / cloud-colour / terrain-sample methods
// (0x00fc3e30 .. 0x00fc4cc9).  Object file SPTerrain/SPWeatherManager.obj.
//
// 0x00fc3e30  pick one of five cloud colours from the temperature phase
// 0x00fc3f00  forward the weather on/off flag to the effects object
// 0x00fc3f30  advance the terraform state machine from the temperature phases
// 0x00fc42a0  rebuild the control maps (refreshes the two storm/atmo AutoRefCount globals)
// 0x00fc4380  sample a float from the terrain map in `dir`'s cube texel
// 0x00fc4540  sample a float texel into a colour (rgba, a = 1)
// 0x00fc4730  sample the magnitude of a vector texel
// 0x00fc4900  sample a vector texel
// 0x00fc4ae0  sample a vector texel (same as 0x00fc4900; two dead TerrainEditor() calls)
//
// Retail layout confirmed against the 0x00fc6640 constructor.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

// ------------------------------------------------------------------ globals
extern float g_weatherFloat_15b1714;   // 0x015b1714 (writable .data, 2.0f)

// Round-to-nearest float->int (cvtss2si, current MXCSR rounding); asm helper as in the original.
#pragma warning(push)
#pragma warning(disable : 4035)   // result returned in eax
inline int RoundToInt_s00fc_3e30(float f)
{
    __asm cvtss2si eax, f
}

// Truncating float->int (cvttss2si from the helper's stack slot); the twin of RoundToInt.
inline int TruncToInt_s00fc_3e30(float f)
{
    __asm cvttss2si eax, f
}
#pragma warning(pop)

// -------------------------------------------------------------- small types
struct Vec3    { float x, y, z; };
struct Vector4 { float x, y, z, w; };
struct ColorRGB_s00fc_3e30 { float r, g, b; };

// ------------------------------------------------------------------ maps
// Direction -> cube face + integer texel coordinates.
struct MapUV_s00fc_3e30 { int x, y, face; };

// cTerrainMap<T>: vtable, refcount, face size, mod count, then the texel vector.
struct cTerrainMapBase_s00fc_3e30 {
    void*    mpVtable;    // +0x00
    int      mRefCount;   // +0x04
    int      mFaceSize;   // +0x08
    uint32_t mModCount;   // +0x0c
};
template <class T> struct cTerrainMap_s00fc_3e30 : cTerrainMapBase_s00fc_3e30 {
    T* mpData;            // +0x10

    // Texel at `uv`; the caller has already clamped the coordinates to the face edge.
    __forceinline const T& GetCubeValue(const MapUV_s00fc_3e30& uv) const
    {
        return mpData[(mFaceSize * uv.face + uv.y) * mFaceSize + uv.x];
    }
};

// Texel coordinates of `v`'s cube face, scaled to `map`'s face size and clamped at the face edge.
template <class T>
static __forceinline MapUV_s00fc_3e30 DirToMapUV(const Vec3& v, const cTerrainMap_s00fc_3e30<T>* map)
{
    float x = v.x;
    float y = v.y;
    float z = v.z;
    float ax = fabsf(x);
    float ay = fabsf(y);
    float az = fabsf(z);
    int size = map->mFaceSize;
    float half = (float)size * 0.5f;
    MapUV_s00fc_3e30 r;
    if (az >= ax && az >= ay) {
        r.x = TruncToInt_s00fc_3e30((x / z + 1.0f) * half);
        r.y = TruncToInt_s00fc_3e30((y / az + 1.0f) * half);
        r.face = (z >= 0.0f) ? 0 : 1;
    } else if (ay >= ax) {
        r.x = TruncToInt_s00fc_3e30((z / y + 1.0f) * half);
        r.y = TruncToInt_s00fc_3e30((x / ay + 1.0f) * half);
        r.face = (y >= 0.0f) ? 4 : 5;
    } else {
        r.x = TruncToInt_s00fc_3e30((y / x + 1.0f) * half);
        r.y = TruncToInt_s00fc_3e30((z / ax + 1.0f) * half);
        r.face = (x >= 0.0f) ? 2 : 3;
    }
    if (r.x == size) r.x--;
    if (r.y == size) r.y--;
    return r;
}

// ------------------------------------------------- reference-counted objects
struct cEffect_s00fc_3e30;

struct AutoRefCount_s00fc_3e30 {
    cEffect_s00fc_3e30* mpObject;   // +0x00

    AutoRefCount_s00fc_3e30& operator=(cEffect_s00fc_3e30* p);
};

extern AutoRefCount_s00fc_3e30 g_autoRef_16d7150;   // 0x016d7150
extern AutoRefCount_s00fc_3e30 g_autoRef_16d714c;   // 0x016d714c

struct cEffect_s00fc_3e30 {
    virtual ~cEffect_s00fc_3e30();                // scalar deleting destructor at vtable +0x00
    int mRefCount;                                // +0x04

    void AddRef()  { ++mRefCount; }
    int Release()
    {
        int count = mRefCount - 1;
        mRefCount = mRefCount - 1;
        if (count)
            return count;
        mRefCount = 1;
        delete this;
        return 0;
    }
};

inline AutoRefCount_s00fc_3e30& AutoRefCount_s00fc_3e30::operator=(cEffect_s00fc_3e30* p)
{
    if (p != mpObject) {
        cEffect_s00fc_3e30* const pTemp = mpObject;
        if (p)
            p->AddRef();
        mpObject = p;
        if (pTemp)
            pTemp->Release();
    }
    return *this;
}

// ------------------------------------------------------------ helper objects
// Object at cWeatherManager +0xd8 whose vtable slot +0x98 toggles an effect id.
class cWeatherEffector_s00fc_3e30 {
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
    virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
    virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
    virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
    virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
    virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
    virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
    virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
    virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
    virtual void slot36(); virtual void slot37();
    virtual void SetEffect(int id, int enable);   // vtable +0x98
};

// The three non-virtual control-map processors behind cWeatherManager +0xe8.
class cControlMapA_s00fc_3e30 { public: void Process(void* map); };    // 0x00f87ea0
class cControlMapB_s00fc_3e30 { public: void Process(void* other); };  // 0x00f88360
class cControlMapC_s00fc_3e30 { public: void Process(void* other); };  // 0x00f88400

struct cControlMaps_s00fc_3e30 {
    uint32_t pad00[6];                       // +0x00 .. +0x17
    cControlMapC_s00fc_3e30* mp18;           // +0x18
    cControlMapA_s00fc_3e30* mp1c;           // +0x1c
    cControlMapB_s00fc_3e30* mp20;           // +0x20
};

struct cTerrainEditor_s00fc_3e30 {
    void GetCurrentTerrainSphere();   // 0x00f67d90 (dead in 0x00fc4ae0)
};
namespace SP {
cTerrainEditor_s00fc_3e30* TerrainEditor();   // 0x00f48a70 SP::TerrainEditor()
}

// ----------------------------------------------------------- the weather class
class cWeatherManager_s00fc_3e30 {
public:
    void GetCloudColor(ColorRGB_s00fc_3e30* out, float phase);        // 0x00fc3e30
    void SetWeatherOn(bool on);                                       // 0x00fc3f00
    void UpdateTerraformState();                                      // 0x00fc3f30
    void RebuildControlMaps(void* arg);                               // 0x00fc42a0
    float GetTerrainFloat(const Vec3& dir);                           // 0x00fc4380
    void  GetTerrainColor(Vector4& out, const Vec3& dir);             // 0x00fc4540
    float GetTerrainMagnitude(const Vec3& dir);                       // 0x00fc4730
    void  GetTerrainVector(Vec3& out, const Vec3& dir);               // 0x00fc4900
    void  GetTerrainVectorDead(Vec3& out, const Vec3& dir);           // 0x00fc4ae0

    template <class T> __forceinline cTerrainMap_s00fc_3e30<T>* GetTerrainMap()
    {
        return (cTerrainMap_s00fc_3e30<T>*)mpTerrainMap;
    }

    uint32_t pad00[3];                    // +0x00
    void*    mpField0C;                   // +0x0c
    uint32_t pad10[9];                    // +0x10 .. +0x33
    void*    mpTerrainMap;                // +0x34
    uint32_t mLowAtmoEffectID;            // +0x38
    uint32_t mMidAtmoEffectID;            // +0x3c
    uint32_t mHighAtmoEffectID;           // +0x40
    uint32_t mCurrentAmbientID;           // +0x44
    uint32_t mLoopBoxAtmoEffectID;        // +0x48
    uint32_t mLoopBoxGroundEffectID;      // +0x4c
    uint32_t mCurrentStormLoopboxID;      // +0x50
    uint32_t mColdStormLoopboxID;         // +0x54
    uint32_t mWarmStormLoopboxID;         // +0x58
    uint32_t mHotStormLoopboxID;          // +0x5c
    uint32_t mIceAmbientEffectID;         // +0x60
    uint32_t mColdAmbientEffectID;        // +0x64
    uint32_t mAmbientLoopboxID;           // +0x68
    uint32_t mHotAmbientEffectID;         // +0x6c
    uint32_t mLavaAmbientEffectID;        // +0x70
    uint32_t mCurrentStormEffectID;       // +0x74
    uint32_t mColdStormEffectID;          // +0x78
    uint32_t mWarmStormEffectID;          // +0x7c
    uint32_t mHotStormEffectID;           // +0x80
    uint32_t mCurrentLocalStormEffectID;  // +0x84
    uint32_t mColdLocalStormEffectID;     // +0x88
    uint32_t mWarmLocalStormEffectID;     // +0x8c
    uint32_t mHotLocalStormEffectID;      // +0x90
    uint32_t mField94;                    // +0x94
    uint32_t mRainRampMS;                 // +0x98
    float    mRainDarkness;               // +0x9c
    uint32_t mFieldA0;                    // +0xa0
    uint32_t mEvaporationEffectID;        // +0xa4
    uint32_t mFreezeEffectID;             // +0xa8
    uint8_t  mFieldAC;                    // +0xac
    uint8_t  mEffectsStarted;             // +0xad
    uint16_t padAE;                       // +0xae
    uint32_t mFieldB0;                    // +0xb0
    uint32_t padB4[9];                    // +0xb4 .. +0xd7
    cWeatherEffector_s00fc_3e30* mpEffector;   // +0xd8
    uint32_t padDC[3];                    // +0xdc .. +0xe7
    cControlMaps_s00fc_3e30* mpControlMaps;    // +0xe8
    float    mPreviousTempPhase;          // +0xec
    float    mCurrentTempPhase;           // +0xf0
    uint32_t padF4[3];                    // +0xf4 .. +0xff
    ColorRGB_s00fc_3e30 mIceCloudColor;   // +0x100
    ColorRGB_s00fc_3e30 mColdCloudColor;  // +0x10c
    ColorRGB_s00fc_3e30 mWarmCloudColor;  // +0x118
    ColorRGB_s00fc_3e30 mHotCloudColor;   // +0x124
    ColorRGB_s00fc_3e30 mLavaCloudColor;  // +0x130
    int      mPreviousState13C;           // +0x13c
    int      mCurrentState140;            // +0x140
    uint32_t pad144[3];                   // +0x144 .. +0x14f
    int      mPreviousTerraformState;     // +0x150
    int      mCurrentTerraformState;      // +0x154
    uint32_t pad158[2];                   // +0x158, +0x15c
    int      mCurrentMaxNumStorms;        // +0x160
    cControlMapC_s00fc_3e30* mpField164;  // +0x164
    uint32_t pad168;                      // +0x168
    uint8_t  mField16C;                   // +0x16c
    uint8_t  mControlMapsInited;          // +0x16d
    uint8_t  pad16E[0x2e];                // +0x16e .. +0x19b
    int      mMaxNumStorms;               // +0x19c
};

// @ 0x00fc3e30
void cWeatherManager_s00fc_3e30::GetCloudColor(ColorRGB_s00fc_3e30* out, float phase)
{
    if (phase < 0.1f) {
        out->r = mIceCloudColor.r;
        out->g = mIceCloudColor.g;
        out->b = mIceCloudColor.b;
        return;
    }
    if (phase < 0.29f) {
        out->r = mColdCloudColor.r;
        out->g = mColdCloudColor.g;
        out->b = mColdCloudColor.b;
        return;
    }
    if (phase < 0.65f) {
        out->r = mWarmCloudColor.r;
        out->g = mWarmCloudColor.g;
        out->b = mWarmCloudColor.b;
        return;
    }
    if (phase < 0.95f) {
        out->r = mHotCloudColor.r;
        out->g = mHotCloudColor.g;
        out->b = mHotCloudColor.b;
        return;
    }
    out->r = mLavaCloudColor.r;
    out->g = mLavaCloudColor.g;
    out->b = mLavaCloudColor.b;
}

// An object at cWeatherManager +0x0c whose vtable slot +0x0c sets an on/off state.
class cOnOffTarget_s00fc_3e30 {
public:
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual void v0c(int state);   // vtable +0x0c
};

// @ 0x00fc3f00
void cWeatherManager_s00fc_3e30::SetWeatherOn(bool on)
{
    cOnOffTarget_s00fc_3e30* target = (cOnOffTarget_s00fc_3e30*)mpField0C;
    if (!target)
        return;
    if (on)
        target->v0c(0);
    else
        target->v0c(2);
}

// @ 0x00fc3f30
void cWeatherManager_s00fc_3e30::UpdateTerraformState()
{
    mPreviousState13C = mCurrentState140;

    if (mFieldB0 == 2) {
        float scaledPhase = mCurrentTempPhase * g_weatherFloat_15b1714;
        mCurrentMaxNumStorms = RoundToInt_s00fc_3e30(scaledPhase * (float)mMaxNumStorms);
    } else {
        mCurrentMaxNumStorms = 0;
    }

    int atmoBand = (mCurrentTempPhase > 0.66f) ? 2 : ((mCurrentTempPhase > 0.33f) ? 1 : 0);
    int tempBand = (mPreviousTempPhase > 0.66f) ? 2 : ((mPreviousTempPhase > 0.33f) ? 1 : 0);
    mCurrentState140 = tempBand + atmoBand * 3;
    mPreviousTerraformState = mCurrentTerraformState;

    int storm;
    if (mPreviousTempPhase < 0.1f) {
        mCurrentAmbientID = mIceAmbientEffectID;
        mCurrentLocalStormEffectID = mColdLocalStormEffectID;
        mCurrentStormLoopboxID = mColdStormLoopboxID;
        mCurrentTerraformState = 0;
        mCurrentStormEffectID = mColdStormEffectID;
        mpEffector->SetEffect(0x17, 1);
        mpEffector->SetEffect(0x18, 0);
        mpEffector->SetEffect(0x19, 0);
        mpEffector->SetEffect(0x1a, 0);
        mpEffector->SetEffect(0x1b, 0);
        return;
    } else if (mPreviousTempPhase < 0.29f) {
        mCurrentAmbientID = mColdAmbientEffectID;
        mCurrentStormEffectID = mWarmStormEffectID;
        mCurrentStormLoopboxID = mWarmStormLoopboxID;
        mCurrentTerraformState = 1;
        mCurrentLocalStormEffectID = mWarmLocalStormEffectID;
        mpEffector->SetEffect(0x17, 0);
        mpEffector->SetEffect(0x18, 1);
        mpEffector->SetEffect(0x19, 0);
        mpEffector->SetEffect(0x1a, 0);
        storm = 0;
    } else if (mPreviousTempPhase < 0.65f) {
        mCurrentAmbientID = mAmbientLoopboxID;
        mCurrentTerraformState = 2;
        mCurrentStormLoopboxID = mWarmStormLoopboxID;
        mCurrentLocalStormEffectID = mWarmLocalStormEffectID;
        mCurrentStormEffectID = mWarmStormEffectID;
        mpEffector->SetEffect(0x17, 0);
        mpEffector->SetEffect(0x18, 0);
        mpEffector->SetEffect(0x19, 1);
        mpEffector->SetEffect(0x1a, 0);
        storm = 0;
    } else {
        mCurrentStormEffectID = mHotStormEffectID;
        mCurrentLocalStormEffectID = mHotLocalStormEffectID;
        if (mPreviousTempPhase < 0.95f) {
            mCurrentAmbientID = mHotAmbientEffectID;
            mCurrentStormLoopboxID = mHotStormLoopboxID;
            mCurrentTerraformState = 3;
            mpEffector->SetEffect(0x17, 0);
            mpEffector->SetEffect(0x18, 0);
            mpEffector->SetEffect(0x19, 0);
            mpEffector->SetEffect(0x1a, 1);
            storm = 0;
        } else {
            mCurrentAmbientID = mLavaAmbientEffectID;
            mCurrentStormLoopboxID = mHotStormLoopboxID;
            mCurrentTerraformState = 4;
            mpEffector->SetEffect(0x17, 0);
            mpEffector->SetEffect(0x18, 0);
            mpEffector->SetEffect(0x19, 0);
            mpEffector->SetEffect(0x1a, 0);
            storm = 1;
        }
    }
    mpEffector->SetEffect(0x1b, storm);
}

// @ 0x00fc42a0
void cWeatherManager_s00fc_3e30::RebuildControlMaps(void* arg)
{
    if (!mEffectsStarted)
        return;

    void* procThis = mpControlMaps->mp1c;
    mpControlMaps->mp1c->Process(arg);

    cControlMapB_s00fc_3e30* blend = mpControlMaps->mp20;
    cControlMapC_s00fc_3e30* copy = (cControlMapC_s00fc_3e30*)mpControlMaps->mp18;
    blend->Process(procThis);

    g_autoRef_16d7150 = (cEffect_s00fc_3e30*)blend;
    g_autoRef_16d714c = (cEffect_s00fc_3e30*)copy;
    mpField164->Process(copy);

    mControlMapsInited = 1;
}

// @ 0x00fc4380
float cWeatherManager_s00fc_3e30::GetTerrainFloat(const Vec3& dir)
{
    MapUV_s00fc_3e30 uv = DirToMapUV(dir, GetTerrainMap<float>());
    return GetTerrainMap<float>()->GetCubeValue(uv);
}

// @ 0x00fc4540
void cWeatherManager_s00fc_3e30::GetTerrainColor(Vector4& out, const Vec3& dir)
{
    MapUV_s00fc_3e30 uv = DirToMapUV(dir, GetTerrainMap<float>());
    float value = GetTerrainMap<float>()->GetCubeValue(uv);
    out.x = value;
    out.y = value;
    out.z = value;
    out.w = 1.0f;
}

// @ 0x00fc4730
float cWeatherManager_s00fc_3e30::GetTerrainMagnitude(const Vec3& dir)
{
    MapUV_s00fc_3e30 uv = DirToMapUV(dir, GetTerrainMap<Vec3>());
    const Vec3& texel = GetTerrainMap<Vec3>()->GetCubeValue(uv);
    float dx = texel.x * texel.x;
    float dy = texel.y * texel.y;
    float dz = texel.z * texel.z;
    return sqrtf(dy + (dz + dx));
}

// @ 0x00fc4900
void cWeatherManager_s00fc_3e30::GetTerrainVector(Vec3& out, const Vec3& dir)
{
    MapUV_s00fc_3e30 uv = DirToMapUV(dir, GetTerrainMap<Vec3>());
    const Vec3& texel = GetTerrainMap<Vec3>()->GetCubeValue(uv);
    Vector4 t;
    t.x = texel.x;
    t.y = texel.y;
    t.z = texel.z;
    t.w = 1.0f;
    out.x = t.x;
    out.y = t.y;
    out.z = t.z;
}

// @ 0x00fc4ae0
void cWeatherManager_s00fc_3e30::GetTerrainVectorDead(Vec3& out, const Vec3& dir)
{
    SP::TerrainEditor()->GetCurrentTerrainSphere();
    MapUV_s00fc_3e30 uv = DirToMapUV(dir, GetTerrainMap<Vec3>());
    const Vec3& texel = GetTerrainMap<Vec3>()->GetCubeValue(uv);
    Vector4 t;
    t.x = texel.x;
    t.y = texel.y;
    t.z = texel.z;
    t.w = 1.0f;
    out.x = t.x;
    out.y = t.y;
    out.z = t.z;
}
