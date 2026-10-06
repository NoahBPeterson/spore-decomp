// slice s0070aed0: SP::cLightingManager::FillLightingStateFromConfig.
// Builds a cLightingConfig (retail layout, see ModAPI Graphics/cLightingConfig.h)
// from a property list: sky/point/directional lights, the SH probe coefficients
// (explicit coefficients, hemisphere env map, HDR cube map, atmosphere ZH,
// hemisphere colours, cone lights), ground bounce, and the fog/sun/night/cel/
// terrain scalars.  Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
// (no /GS cookie in the original; EH frame from the temporary cLightingConfig
// and the two resource AutoRefCounts).
#include "types.h"
#include <xmmintrin.h>
#include <math.h>
#include <string.h>

void EastlFree(void* p) throw();  // 0x00F47380

struct Vector2 { float x, y; };
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3& operator+=(const Vector3& o) {
        x += o.x;
        y += o.y;
        z += o.z;
        return *this;
    }
};
inline Vector3 operator*(const Vector3& v, float s) { return Vector3(v.x * s, v.y * s, v.z * s); }
struct ColorRGB {
    float r, g, b;
    ColorRGB() {}
    ColorRGB(const ColorRGB& o) : r(o.r), g(o.g), b(o.b) {}
};
struct PlainVector4 { float x, y, z, w; };

// rw::math::vpu::Vector4
struct Vector4 {
    __m128 v;
    Vector4() {}
    Vector4(float x, float y, float z, float w) { v = _mm_setr_ps(x, y, z, w); }
    Vector4(__m128 m) : v(m) {}
    Vector4& operator*=(float s) { v = _mm_mul_ps(v, _mm_set1_ps(s)); return *this; }
};
inline Vector4 operator*(float s, const Vector4& a) { return Vector4(_mm_mul_ps(_mm_set1_ps(s), a.v)); }

namespace EA {
namespace ResourceMan {
struct Key {
    uint32_t mInstance;  // +0x0
    uint32_t mType;      // +0x4
    uint32_t mGroup;     // +0x8
};
class IResource {
public:
    virtual int AddRef();
    virtual int Release();
};
class IResourceManager {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual bool GetResource(const Key& key, IResource** ppResource, int arg_8, void* pDBPF,
                             void* pFactory, const Key* pCacheName);  // 0x0c
};
IResourceManager* GetManager();  // 0x0067DCD0
}  // namespace ResourceMan

// EA::Variant / App::Property (retail): 16 bytes of data, flags, type id.
struct Variant {
    uint32_t mData[4];  // +0x0
    uint16_t mFlags;    // +0x10
    uint16_t mTypeId;   // +0x12

    void* GetStorage() {
        if (mFlags & 0x30) return *(void**)this;
        return mTypeId ? (void*)this : 0;
    }
    int GetCount() {
        if (mFlags & 0x30) return (int)mData[2];
        return mTypeId != 0;
    }
    const bool& GetBool();  // 0x0041E920
};
}  // namespace EA

// Out-of-line static defaults returned by the typed Variant accessors.
const Vector3& DefaultVector3();          // 0x006BB5E0
const ColorRGB& DefaultColorRGB();        // 0x006BB600
const EA::ResourceMan::Key& DefaultKey();  // 0x006BB640
extern float gDefaultFloat;               // 0x015D1168
extern const ColorRGB kColorWhite;        // 0x01629884

inline const float& AsFloat(EA::Variant* p) {
    if (p->mTypeId == 0xd || p->mTypeId == 0x10) return *(float*)p->GetStorage();
    return gDefaultFloat;
}
inline const Vector3& AsVector3(EA::Variant* p) {
    if (p->mTypeId == 0x31 || p->mTypeId == 0x10) return *(Vector3*)p->GetStorage();
    return DefaultVector3();
}
inline const ColorRGB& AsColorRGB(EA::Variant* p) {
    if (p->mTypeId == 0x32 || p->mTypeId == 0x10) return *(ColorRGB*)p->GetStorage();
    return DefaultColorRGB();
}
inline const EA::ResourceMan::Key& AsKey(EA::Variant* p) {
    if (p->mTypeId == 0x20 || p->mTypeId == 0x10) return *(EA::ResourceMan::Key*)p->GetStorage();
    return DefaultKey();
}

namespace SP {
class cPropertyList {
public:
    virtual int AddRef();   // 0x00
    virtual int Release() throw();  // 0x04
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual bool GetPropertyA(uint32_t key, EA::Variant** out) const;
    virtual bool GetProperty(uint32_t key, EA::Variant** out) const;  // 0x24
};

bool GetPropertyAsColorRGB(const cPropertyList* list, uint32_t key, ColorRGB* out);  // 0x006A11B0
bool GetPropertyAsVector2(const cPropertyList* list, uint32_t key, Vector2* out);    // 0x006A10C0
bool GetPropertyAsVector4(const cPropertyList* list, uint32_t key, PlainVector4* out);  // 0x006A1160
bool GetPropertyArrayVector3(const cPropertyList* list, uint32_t key, int* count, Vector3** out);  // 0x006A0990
bool GetPropertyArrayColorRGB(const cPropertyList* list, uint32_t key, int* count, ColorRGB** out);  // 0x006A0A70
bool GetPropertyArrayVector4(const cPropertyList* list, uint32_t key, int* count, PlainVector4** out);  // 0x006A0A00

// SH helpers (SPSphericalHarmonics)
void RemoveNormalizationConstants(int numBands, Vector4* coeffs);  // 0x00783830
void ApplyNormalizationConstants(int numBands, Vector4* coeffs);   // 0x00783590
void FindSHCoeffsFromHemiEnvMap(EA::ResourceMan::IResource* res, int numCoeffs, Vector4* coeffs);  // 0x00783FB0
void FindSHCoeffsFromHDRCubeMap(EA::ResourceMan::IResource* res, int numBands, Vector4* coeffs);   // 0x00795EC0
void CalcAtmosphereZH(int count, const PlainVector4* phases, int numBands, float* zh);  // 0x00796420
void RotateZHToSH(const Vector3& dir, int numBands, const float* zh, Vector4* coeffs);  // 0x00794E60
void RotateZHToSHAdd(const Vector3& dir, int numBands, const Vector4& color, const float* zh,
                     Vector4* coeffs);  // 0x00794E80
void AddGroundBounce(int numBands, Vector4* coeffs, const Vector4& diffuse, const Vector4& specular);  // 0x00784420
void GetHemisphereZH(float* zh);           // 0x00783380
void GetConeZH(float cosAngle, float* zh);  // 0x007831D0
}  // namespace SP

namespace EA {
template <class T> class AutoRefCount {
public:
    AutoRefCount() : mpObject(0) {}
    __forceinline ~AutoRefCount() {
        if (mpObject) mpObject->Release();
    }
    AutoRefCount& operator=(T* p) {
        if (p != mpObject) {
            T* const pTemp = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
    T** AsPPTypeParam() {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
    T* get() const { return mpObject; }
    T* mpObject;
};
}  // namespace EA

namespace eastl {
template <class T> inline const T& min(const T& a, const T& b) { return (b < a) ? b : a; }
}

template <class T> struct SpVector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];
    __forceinline ~SpVector() {
        if (mpBegin && ((int*)mpBegin)[-1] != 0) EastlFree(mpBegin);
    }
    int size() const { return (int)(mpEnd - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
};

struct LightFlags {
    uint32_t mWord;
    void set(uint32_t i) {
        if (i < 7) mWord |= ((uint32_t)1 << (i & 31));
    }
};

namespace SP {
struct cLight {
    ColorRGB mColor;   // +0x0
    float mStrength;   // +0xc
    Vector3 mDir;      // +0x10
};

class cLightingConfig {
public:
    cLightingConfig();                                       // 0x00706DD0
    cLightingConfig& operator=(const cLightingConfig& other);  // 0x007089A0
    ~cLightingConfig() {}

    EA::AutoRefCount<cPropertyList> mpPropList;  // +0x00
    LightFlags mFlags;                           // +0x04
    cLight mLights[4];                           // +0x08
    ColorRGB mPointLightColor;                   // +0x78
    float mPointLightStrength;                   // +0x84
    float mPointLightRadius;                     // +0x88
    Vector3 mPointLightPos;                      // +0x8c
    ColorRGB mSkylight;                          // +0x98
    bool mbCameraSpaceLighting;                  // +0xa4
    SpVector<Vector4> mSHObjects;                // +0xa8
    SpVector<Vector4> mSHCoeffs;                 // +0xbc
    float mPlanetAtmosphere;                     // +0xd0
    float mBounceDiffCos;                        // +0xd4
    float mBounceSpec;                           // +0xd8
    float field_DC;                              // +0xdc
    float field_E0;                              // +0xe0
    PlainVector4 mColourPhaseAdd[3];             // +0xe4
    float mSunStart;                             // +0x114
    float mSunInvRange;                          // +0x118
    float mNightStart;                           // +0x11c
    float mNightInvRange;                        // +0x120
    Vector2 field_124;                           // +0x124
    Vector2 mCelRange;                           // +0x12c
    bool mTerrainLightEnabled;                   // +0x134
    float mTerrainLightStrength;                 // +0x138
    float mTerrainLightSize;                     // +0x13c
    float mTerrainLightHeightDropoff;            // +0x140
};

class cLightingManager {
public:
    void FillLightingStateFromConfig(cPropertyList* props, cLightingConfig* config);
    void AddSHCoeffs(cLightingConfig* config, Vector4* coeffs, int numBands, cPropertyList* props,
                     uint32_t scaleKey);  // 0x00709CF0

    uint32_t pad[4];      // +0x00
    int mNumSHBands;      // +0x10
    int mNumSHCoeffs;     // +0x14
};
}  // namespace SP

using namespace SP;

inline bool GetFloatProperty(const cPropertyList* props, uint32_t key, float* out) {
    EA::Variant* prop;
    if (props->GetProperty(key, &prop) && prop->mTypeId == 0xd) {
        *out = *(float*)prop->GetStorage();
        return true;
    }
    return false;
}

inline float Dot(const Vector3& a, const Vector3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

inline Vector3 Normalize(const Vector3& v) {
    float lenSq = Dot(v, v) + 1e-8f;
    float len = sqrtf(lenSq);
    float inv = 1.0f / len;
    return Vector3(v.x * inv, inv * v.y, inv * v.z);
}

// @ 0x0070aed0
void cLightingManager::FillLightingStateFromConfig(cPropertyList* props, cLightingConfig* config)
{
    EA::Variant* prop;
    Vector4 coeffs[49];

    *config = cLightingConfig();
    config->mpPropList = props;

    if (props) {
        EA::Variant* camProp;
        if (props->GetProperty(0x100eac6, &camProp) && camProp->mTypeId == 1)
            config->mbCameraSpaceLighting = camProp->GetBool();
    }

    // skylight colour and strength
    if (props->GetProperty(0x100eab6, &prop)) {
        config->mSkylight = AsColorRGB(prop);
        if (props->GetProperty(0x100eab7, &prop)) {
            float s = AsFloat(prop);
            float r = config->mSkylight.r * s;
            float g = config->mSkylight.g * s;
            float b = config->mSkylight.b * s;
            config->mSkylight.r = r;
            config->mSkylight.g = g;
            config->mSkylight.b = b;
        }
        config->mFlags.set(4);
    }

    // point light
    if (props->GetProperty(0x100eac7, &prop)) {
        config->mFlags.set(5);
        config->mPointLightPos = AsVector3(prop);
    }
    if (props->GetProperty(0x100eac8, &prop)) {
        const Vector3& c = AsVector3(prop);
        float r = c.x, g = c.y, b = c.z;
        config->mPointLightColor.r = r;
        config->mPointLightColor.g = g;
        config->mPointLightColor.b = b;
    }
    if (props->GetProperty(0x100eac9, &prop))
        config->mPointLightStrength = AsFloat(prop);
    if (props->GetProperty(0x100eaca, &prop))
        config->mPointLightRadius = AsFloat(prop);

    // directional lights: (dir, colour, strength) keys per light
    cLight* light = config->mLights;
    uint32_t i = 0;
    for (uint32_t key = 0x100eab9; (int)key < 0x100eac5; key += 3) {
        if (props->GetProperty(key - 1, &prop)) {
            config->mFlags.set(i);
            light->mDir = Normalize(AsVector3(prop));
        }
        if (props->GetProperty(key, &prop))
            light->mColor = AsColorRGB(prop);
        if (props->GetProperty(key + 1, &prop))
            light->mStrength = AsFloat(prop);
        ++i;
        ++light;
    }

    // explicit SH coefficients
    int count;
    ColorRGB* shColors;
    if (GetPropertyArrayColorRGB(props, 0x100eac5, &count, &shColors)) {
        memset(coeffs, 0, sizeof(coeffs));
        int n = eastl::min(count, mNumSHCoeffs);
        for (int j = 0; j < n; ++j)
            coeffs[j] = Vector4(shColors[j].r, shColors[j].g, shColors[j].b, 1.0f);
        RemoveNormalizationConstants(mNumSHBands, coeffs);
        AddSHCoeffs(config, coeffs, mNumSHBands, props, 0x56784b9);
    }

    // hemisphere environment map
    if (props->GetProperty(0x100eacb, &prop)) {
        const EA::ResourceMan::Key& srcKey = AsKey(prop);
        EA::ResourceMan::Key key = srcKey;
        key.mType = 0x3e421ed;
        EA::AutoRefCount<EA::ResourceMan::IResource> res;
        if (EA::ResourceMan::GetManager()->GetResource(srcKey, res.AsPPTypeParam(), 0, 0, 0, &key) ||
            EA::ResourceMan::GetManager()->GetResource(key, res.AsPPTypeParam(), 0, 0, 0, 0)) {
            FindSHCoeffsFromHemiEnvMap(res.get(), mNumSHCoeffs, coeffs);
            AddSHCoeffs(config, coeffs, mNumSHBands, props, 0x56784c9);
        }
    }

    // HDR cube map
    if (props->GetProperty(0x477d61d, &prop)) {
        const EA::ResourceMan::Key& srcKey = AsKey(prop);
        EA::AutoRefCount<EA::ResourceMan::IResource> res;
        EA::ResourceMan::Key key = srcKey;
        key.mType = 0x3e421ef;
        if (EA::ResourceMan::GetManager()->GetResource(srcKey, res.AsPPTypeParam(), 0, 0, 0, &key) ||
            EA::ResourceMan::GetManager()->GetResource(key, res.AsPPTypeParam(), 0, 0, 0, 0)) {
            FindSHCoeffsFromHDRCubeMap(res.get(), mNumSHBands, coeffs);
            for (int j = 0; j < mNumSHCoeffs; ++j)
                coeffs[j] *= 256.0f;
            AddSHCoeffs(config, coeffs, mNumSHBands, props, 0x56784d9);
        }
    }

    // atmosphere phases
    if (props->GetProperty(0x100eacd, &prop) && prop->mTypeId == 0x33 && (prop->mFlags & 0x10)) {
        float zh[31];
        int n = prop->GetCount();
        CalcAtmosphereZH(n, (const PlainVector4*)prop->GetStorage(), mNumSHBands, zh);
        float k = (float)(1.0 / sqrt(3.0));
        Vector3 dir(k, k, k);
        RotateZHToSH(dir, mNumSHBands, zh, coeffs);
        AddSHCoeffs(config, coeffs, mNumSHBands, props, 0x56784e9);
    }

    // hemisphere colours (upper, optional lower)
    Vector3* hemi;
    if (GetPropertyArrayVector3(props, 0x566caea, &count, &hemi) && count > 0) {
        float zh[7];
        GetHemisphereZH(zh);
        memset(coeffs, 0, sizeof(coeffs));
        int j;
        for (j = 0; j < mNumSHBands; ++j) {
            float c = zh[j];
            *(Vector3*)&coeffs[(j + 1) * j] += hemi[0] * c;
        }
        for (j = 0; j < mNumSHBands; ++j) {
            if (j & 1) zh[j] = -zh[j];
        }
        if (count == 1) {
            for (j = 0; j < mNumSHBands; ++j) {
                float c = zh[j];
                *(Vector3*)&coeffs[(j + 1) * j] += Vector3(c, c, c);
            }
        } else {
            for (j = 0; j < mNumSHBands; ++j) {
                float c = zh[j];
                float* d = (float*)&coeffs[(j + 1) * j];
                d[0] += c * hemi[1].x;
                d[1] += hemi[1].y * c;
                d[2] += hemi[1].z * c;
            }
        }
        AddSHCoeffs(config, coeffs, mNumSHBands, props, 0x56784f9);
    }

    // cone lights: pairs of (colour.rgb + intensity, direction + cos angle)
    PlainVector4* cones;
    if (GetPropertyArrayVector4(props, 0x566cae9, &count, &cones)) {
        count &= ~1;
        memset(coeffs, 0, sizeof(coeffs));
        Vector4 zero(0.0f, 0.0f, 0.0f, 0.0f);
        for (int j = 0; j < count; j += 2) {
            Vector4 tmp(cones[j].x, cones[j].y, cones[j].z, cones[j].w);
            ((float*)&tmp)[3] = ((float*)&zero)[0];
            Vector4 color = tmp;
            Vector3 dir;
            dir.x = cones[j + 1].x;
            dir.y = cones[j + 1].y;
            dir.z = cones[j + 1].z;
            float intensity = cones[j].w;
            float zh[7];
            GetConeZH(cones[j + 1].w, zh);
            RotateZHToSHAdd(dir, mNumSHBands, intensity * color, zh, coeffs);
        }
        AddSHCoeffs(config, coeffs, mNumSHBands, props, 0x5678419);
    }

    // ground bounce
    if (!config->mSHCoeffs.empty()) {
        ColorRGB diffuse;
        if (GetPropertyAsColorRGB(props, 0x100eace, &diffuse)) {
            ColorRGB specular = kColorWhite;
            GetPropertyAsColorRGB(props, 0x100eacf, &specular);
            AddGroundBounce(mNumSHBands, config->mSHCoeffs.mpBegin,
                            Vector4(diffuse.r, diffuse.g, diffuse.b, 1.0f),
                            Vector4(specular.r, specular.g, specular.b, 1.0f));
        }
    }
    if (!config->mSHCoeffs.empty())
        ApplyNormalizationConstants(mNumSHBands, config->mSHCoeffs.mpBegin);

    GetFloatProperty(props, 0x2478ed7, &config->mPlanetAtmosphere);
    float angle = 1.0f;
    GetFloatProperty(props, 0x64dab03, &angle);
    config->mBounceDiffCos = cosf(angle * 0.017453292f);
    GetFloatProperty(props, 0x696cb45, &config->mBounceSpec);
    GetFloatProperty(props, 0x2478eda, &config->field_DC);
    GetFloatProperty(props, 0x2478edb, &config->field_E0);
    GetPropertyAsVector4(props, 0x2478edc, &config->mColourPhaseAdd[0]);
    GetPropertyAsVector4(props, 0x2478edd, &config->mColourPhaseAdd[1]);
    GetPropertyAsVector4(props, 0x2478ede, &config->mColourPhaseAdd[2]);
    GetFloatProperty(props, 0x2478edf, &config->mSunStart);
    {
        EA::Variant* p;
        if (props->GetProperty(0x2478ee0, &p) && p->mTypeId == 0xd)
            config->mSunInvRange = 1.0f / (*(float*)p->GetStorage() + 1e-6f);
    }
    GetFloatProperty(props, 0x2478ee1, &config->mNightStart);
    {
        EA::Variant* p;
        if (props->GetProperty(0x2478ee2, &p) && p->mTypeId == 0xd)
            config->mNightInvRange = 1.0f / (*(float*)p->GetStorage() + 1e-6f);
    }
    GetPropertyAsVector2(props, 0x49b94d5, &config->field_124);
    GetPropertyAsVector2(props, 0x49b94d6, &config->mCelRange);
    {
        EA::Variant* p;
        if (props->GetProperty(0x4adacd8, &p) && p->mTypeId == 1)
            config->mTerrainLightEnabled = *(bool*)p->GetStorage();
    }
    GetFloatProperty(props, 0x4adacd9, &config->mTerrainLightStrength);
    GetFloatProperty(props, 0x4adacda, &config->mTerrainLightSize);
    GetFloatProperty(props, 0x4adacdb, &config->mTerrainLightHeightDropoff);

    // global SH intensity scale
    if (props->GetProperty(0x100eac4, &prop)) {
        float scale = AsFloat(prop);
        int n = config->mSHCoeffs.size();
        for (int j = 0; j < n; ++j)
            config->mSHCoeffs.mpBegin[j] = scale * config->mSHCoeffs.mpBegin[j];
    }
}
