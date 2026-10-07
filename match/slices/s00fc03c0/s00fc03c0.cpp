// Slice s00fc03c0 — SP::cTerrainStateMgr reset of the planet state parameters to their defaults,
// then reload of the planet/tuning property lists and the terrain editor's lighting overrides.
// Retail layout (see also match/slices/s00fbf570 for the same class).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

extern "C" void* FUN_011e0744(void* dst, const void* src, unsigned n);   // memcpy thunk, returns dst

struct Vector2 {
    float x, y;
    Vector2() {}
    Vector2(float ax, float ay) : x(ax), y(ay) {}
};
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};
struct Vector4 {
    float x, y, z, w;
    Vector4() {}
    Vector4(float ax, float ay, float az, float aw) : x(ax), y(ay), z(az), w(aw) {}
};
struct Matrix3 {
    float m[3][3];
    void Assign(const Matrix3& other);       // 0x41cb40
};
struct Matrix4 {
    float m[4][4];
    Matrix4()
    {
        m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
        m[1][0] = 0.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
        m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][3] = 0.0f;
        m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f;
        m[0][0] = 1.0f; m[1][1] = 1.0f; m[2][2] = 1.0f; m[3][3] = 1.0f;
    }
};

extern const Vector3 kVector3Zero;          // 0x16d6710
extern const Matrix3 kMatrix3Identity;      // 0x16d6db0

struct Transform {
    int16_t mnFlags;
    int16_t mnTransformCount;
    Vector3 mOffset;
    float mfScale;
    Matrix3 mRotation;

    Transform() : mnFlags(0), mnTransformCount(0), mOffset(kVector3Zero), mfScale(1.0f)
    {
        mRotation.Assign(kMatrix3Identity);
    }
    void SetRotationFromDirs(const Vector3& dir, const Vector3& up);   // 0x6bac90
    void ToMatrix4(Matrix4& out) const;                                 // 0x6b9440
};

// ---- property system --------------------------------------------------------
struct Property {
    uint32_t pad0[4];
    uint16_t pad10; uint16_t mnType;          // +0x12
    float* GetFloat();                        // 0x41ea70
};
struct cPropertyList {
    virtual void AddRef();
    virtual void Release();
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1c(); virtual void v20();
    virtual bool GetProperty(uint32_t id, Property** out);   // +0x24
};
struct cPropertyManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool GetPropertyList(uint32_t instance, uint32_t group, cPropertyList** out);   // +0x2c
};
namespace SP { cPropertyManager* PropertyManager(); }                          // 0x67de30
bool GetPropertyAsVector2(cPropertyList* list, uint32_t id, Vector2* out);   // 0x6a10c0

template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount& operator=(T* p)
    {
        if (p != mpObject) {
            T* const pTemp = mpObject;
            if (p)
                p->AddRef();
            mpObject = p;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    T** AsPointer()
    {
        *this = (T*)0;
        return &mpObject;
    }
};

// ---- other callees ------------------------------------------------------------
struct cTerrainMapSet {
    uint32_t pad00[13];
    float mRadius;                // +0x34
    float mMaxHeight;             // +0x38
    float mWaterHeight;           // +0x3c
    uint32_t pad40[2];
    float mMinCliffGradient;      // +0x48
    float mMaxCliffGradient;      // +0x4c
    void SetWaterHeight(float h);                 // 0xff03c0
    void SetMaxHeight(float h);                   // 0xf924e0
    void SetCliffGradients(float lo, float hi);   // 0xf92500
};

struct cTextureInstance {
    virtual void AddRef();
    virtual void Release();
    uint32_t pad04[6];
    float m1c;                    // +0x1c
};
extern cTextureInstance* g_pDefaultTerrainTexture;   // 0x16d6acc

struct cTerrainEditor {
    uint32_t pad000[0x1c8 / 4];
    cPropertyList* mpLightingProps;   // +0x1c8
};
namespace SP { cTerrainEditor* TerrainEditor(); }   // 0xf48a70
bool __cdecl IsWorldFlagSet(int flag);              // 0x685520

struct IVisualEffect {
    virtual void AddRef();
    virtual void Release();
};
struct IEffectsManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50();
    virtual IVisualEffect* GetEffect(uint32_t id);   // +0x54
};
namespace SP { IEffectsManager* EffectsManager(); }   // 0x67ddd0

// ---- EASTL vector pieces --------------------------------------------------------
struct VectorKey {                 // 12-byte elements, out-of-line erase
    Vector3* mpBegin;
    Vector3* mpEnd;
    Vector3* mpCapacity;
    uint32_t mAllocator;
    Vector3* erase(Vector3* first, Vector3* last);   // 0x50f740
    void clear() { erase(mpBegin, mpEnd); }
};
struct VectorU32 {                 // 4-byte elements, inline erase
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    uint32_t mAllocator;
    uint32_t* erase(uint32_t* first, uint32_t* last)
    {
        FUN_011e0744(first, last, (unsigned)((char*)mpEnd - (char*)last));
        mpEnd -= (last - first);
        return first;
    }
    void clear() { erase(mpBegin, mpEnd); }
};

// ---- cTerrainStateMgr (retail offsets) -------------------------------------
struct cTerrainStateMgr {
    uint32_t pad000;
    cTerrainMapSet* mpMapSet;     // +0x004
    float m008;                   // +0x008
    float m00c;                   // +0x00c
    float m010;                   // +0x010
    float m014;                   // +0x014
    float m018;                   // +0x018
    float mMaxAltLow;             // +0x01c
    float mMaxAltMid;             // +0x020
    float mMaxAltHigh;            // +0x024
    float m028;                   // +0x028
    float mTimeOfDay;             // +0x02c
    float mLatitude;              // +0x030
    Vector3 mSunDir;              // +0x034
    Matrix4 mSunMatrix;           // +0x040
    int m080;                     // +0x080
    Vector2 mLightRange[6];       // +0x084
    Vector4 m0b4;                 // +0x0b4
    uint32_t pad0c4;
    Vector3 mColorA0;             // +0x0c8
    Vector3 mColorB0;             // +0x0d4
    Vector3 mColorA1;             // +0x0e0
    Vector3 mColorB1;             // +0x0ec
    Vector3 mColorA2;             // +0x0f8
    Vector3 mColorB2;             // +0x104
    Vector4 m110;                 // +0x110
    float m120, m124;             // +0x120
    uint32_t pad128[5];
    float m13c, m140, m144, m148; // +0x13c
    float m14c;                   // +0x14c
    float m150;                   // +0x150
    float m154;                   // +0x154
    uint32_t pad158[36];
    float m1e8;                   // +0x1e8
    float m1ec;                   // +0x1ec
    float m1f0;                   // +0x1f0
    uint32_t pad1f4;
    float m1f8;                   // +0x1f8
    float m1fc;                   // +0x1fc
    float m200;                   // +0x200
    float m204;                   // +0x204
    float m208;                   // +0x208
    uint32_t pad20c[4];
    Vector3 m21c;                 // +0x21c
    Vector3 m228;                 // +0x228
    Vector3 m234;                 // +0x234
    Vector3 m240;                 // +0x240
    Vector3 m24c;                 // +0x24c
    Vector3 m258;                 // +0x258
    bool m264;                    // +0x264
    uint8_t pad265[3];
    Vector3 m268;                 // +0x268
    Vector3 m274;                 // +0x274
    uint32_t pad280[6];
    VectorU32 mVec298;            // +0x298
    uint32_t pad2a8;
    VectorKey mVec2ac;            // +0x2ac
    uint32_t pad2bc;
    float m2c0[13];               // +0x2c0
    uint32_t pad2f4[21];
    AutoRefCount<cTextureInstance> mpTexture;   // +0x348
    uint32_t pad34c[64];
    float mAmbient;               // +0x44c
    float m450;                   // +0x450
    float mMinCliffGradient;      // +0x454
    float mMaxCliffGradient;      // +0x458
    uint32_t pad45c[40];
    Vector4 m4fc;                 // +0x4fc
    uint32_t pad50c[41];
    AutoRefCount<cPropertyList> mpPlanetProps;   // +0x5b0
    uint32_t pad5b4;
    AutoRefCount<cPropertyList> mpTuningProps;   // +0x5b8
    uint32_t pad5bc[15];
    AutoRefCount<IVisualEffect> mpEffect;        // +0x5f8

    void Initialize();                 // 0xfbe7d0
    void ApplyTuning();                // 0xfb8ae0
    void UpdateWater();                // 0xfbdb10
    float ComputeAmbient();            // 0xfb88d0
    void UpdateSeasonsNow();           // 0xfbbc00

    void Reset(bool updateNow);
};

void cTerrainStateMgr::Reset(bool updateNow)
{
    m010 = 0.0f;
    m018 = 0.5f;
    m014 = 1.0f;
    mpMapSet->SetWaterHeight(0.0f);

    mVec2ac.clear();
    mVec298.clear();

    m268 = kVector3Zero;
    m274 = kVector3Zero;
    mColorA0 = Vector3(1.0f, 1.0f, 1.0f);
    m264 = false;
    m2c0[0] = 1.0f;
    m2c0[1] = 1.0f;
    m2c0[2] = 1.0f;
    m2c0[3] = 1.0f;
    m2c0[4] = 1.0f;
    m2c0[5] = 1.0f;
    m2c0[6] = 1.0f;
    m2c0[7] = 1.0f;
    m2c0[8] = 1.0f;
    m2c0[9] = 1.0f;
    m2c0[10] = 1.0f;
    m2c0[11] = 1.0f;
    m2c0[12] = 0.1f;
    m028 = 1.0f;
    m008 = 0.5f;
    m00c = 0.5f;
    mTimeOfDay = 0.5f;
    mColorB0 = Vector3(0.3f, 0.3f, 0.3f);
    mColorA1 = Vector3(1.0f, 0.8f, 0.8f);
    mColorB1 = Vector3(0.3f, 0.1f, 0.1f);
    mColorA2 = Vector3(0.8f, 1.0f, 0.8f);
    mColorB2 = Vector3(0.1f, 0.3f, 0.1f);
    m110 = Vector4(50.0f, 70.0f, 50.0f, 70.0f);
    m0b4 = Vector4(0.6f, 0.6f, 2.0f, 0.0f);
    mSunDir = Vector3(0.0f, 1.0f, 0.0f);
    mSunMatrix = Matrix4();
    mLightRange[0] = Vector2(0.1f, 0.3f);
    mLightRange[1] = Vector2(0.3f, 0.7f);
    mLightRange[2] = Vector2(0.7f, 1.0f);
    mLightRange[3] = Vector2(0.0f, 0.3f);
    mLightRange[4] = Vector2(0.3f, 0.7f);
    mLightRange[5] = Vector2(0.7f, 1.0f);
    m080 = 0;
    mLatitude = 0.5f;

    Transform xform;
    xform.SetRotationFromDirs(mSunDir, Vector3(0.0f, 0.0f, 1.0f));
    xform.ToMatrix4(mSunMatrix);

    m4fc = Vector4(0.5f, 0.5f, 0.5f, 0.5f);
    m13c = -1.0f;
    m140 = 1.0f;
    m144 = 5.0f;
    m148 = 67.0f;
    m14c = 0.01f;
    m150 = 0.01f;
    m154 = 100.0f;
    m1e8 = 25.0f;
    m1ec = 20.0f;
    m1f0 = 8.0f;
    m1f8 = 300.0f;
    m1fc = 1.35f;
    m200 = 0.95f;
    m204 = 1.0f;
    m208 = 1.0f;
    m21c = Vector3(0.01f, 0.01f, 0.01f);
    m228 = Vector3(1.0f, 1.0f, 1.0f);
    m234 = Vector3(0.4f, 0.5f, 0.7f);
    m240 = Vector3(0.15f, 0.15f, 0.18f);
    m24c = Vector3(-0.045f, -0.045f, -0.045f);
    m258 = Vector3(0.1f, 0.1f, 0.1f);
    float minGradient;   // never initialized in the original: reads the stale 0.1f temp slot
    float maxGradient;
    m120 = 0.5f;
    m124 = 0.5f;

    SP::PropertyManager()->GetPropertyList(0xd985994c, 0x243ad2b, mpPlanetProps.AsPointer());
    Initialize();
    if (IsWorldFlagSet(2)) {
        SP::PropertyManager()->GetPropertyList(0x1726fe2, 0x243ad2b, mpTuningProps.AsPointer());
        ApplyTuning();
    }

    mpTexture = g_pDefaultTerrainTexture;
    if (mpTexture.mpObject)
        mpTexture.mpObject->m1c = m1ec;

    cPropertyList* list = SP::TerrainEditor()->mpLightingProps;
    if (list)
        list->AddRef();
    GetPropertyAsVector2(list, 0x328a103, &mLightRange[0]);
    GetPropertyAsVector2(list, 0x328a10c, &mLightRange[1]);
    GetPropertyAsVector2(list, 0x328a115, &mLightRange[2]);
    GetPropertyAsVector2(list, 0x328a11d, &mLightRange[3]);
    GetPropertyAsVector2(list, 0x328a125, &mLightRange[4]);
    GetPropertyAsVector2(list, 0x328a12f, &mLightRange[5]);

    if (list) {
        Property* prop;
        if (list->GetProperty(0x21126c2, &prop) && prop->mnType == 0xd)
            mMaxAltLow = *prop->GetFloat();
        if (list->GetProperty(0x21126ce, &prop) && prop->mnType == 0xd)
            mMaxAltMid = *prop->GetFloat();
        if (list->GetProperty(0x21126e3, &prop) && prop->mnType == 0xd)
            mMaxAltHigh = *prop->GetFloat();
        if (list->GetProperty(0x228d235, &prop) && prop->mnType == 0xd)
            minGradient = *prop->GetFloat();
        if (list->GetProperty(0x228d23f, &prop) && prop->mnType == 0xd)
            maxGradient = *prop->GetFloat();
    }
    mpMapSet->SetCliffGradients(minGradient, maxGradient);

    float t = mpMapSet->mRadius * 0.002f;
    float maxAlt;
    if (t >= 1.0f)
        maxAlt = (mMaxAltHigh - mMaxAltMid) * (t - 1.0f) + mMaxAltMid;
    else
        maxAlt = (mMaxAltMid - mMaxAltLow) * t + mMaxAltLow;
    mpMapSet->SetMaxHeight(maxAlt);

    UpdateWater();
    mAmbient = ComputeAmbient();
    m450 = 0.0f;
    mMinCliffGradient = mpMapSet->mMinCliffGradient;
    mMaxCliffGradient = mpMapSet->mMaxCliffGradient;
    if (updateNow)
        UpdateSeasonsNow();

    if (SP::EffectsManager()->GetEffect(0x23541242))
        mpEffect = SP::EffectsManager()->GetEffect(0x23541242);

    if (list)
        list->Release();
}
