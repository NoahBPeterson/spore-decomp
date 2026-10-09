// Slice s00fa2a20 -- SP::cTerrainSphere::RefractionMapRender (0x00fa2a20, 3637 bytes).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: the two local fixed_vectors get no EH frame).
//
// Renders the underwater refraction map layer of a planet. The model worlds registered for
// refraction (field 0x8b0, {world, pass} pairs) are culled against the refraction frustum; every
// visible model that is (a) on the camera-facing side of the planet (the nearest point of its
// bounding sphere, seen from the planet centre, lies within a height-dependent cone around the
// camera) or (b) explicitly marked by property 0x4e5f251c, and whose bottom lies under the water
// surface (with a depth-dependent margin), is put into the "Terrain_UnderwaterGroup" render group.
// Models flagged with property 0xf8cec83b are instead collected and drawn afterwards, grouped by
// model world. Each world is drawn as a layer with only that group enabled, then the group bits are
// cleared again. Finally the extra refraction layers (field 0x8c4) are drawn.
#include "types.h"
#include <math.h>

void operator delete[](void* p);   // 0x00f47380 (Spore's global delete[])

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8
#define PV32 PV16 PV16
#define PV64 PV32 PV32

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    float Length() const { return sqrtf(x * x + y * y + z * z); }
    float Dot(const Vector3& v) const { return x * v.x + y * v.y + z * v.z; }
    // normalized with a small bias so that a zero vector stays finite
    Vector3 NormalizedSafe() const
    {
        float inv = 1.0f / sqrtf(x * x + y * y + z * z + 1e-8f);
        return Vector3(x * inv, y * inv, z * inv);
    }
};
inline Vector3 operator+(const Vector3& a, const Vector3& b) { return Vector3(a.x + b.x, a.y + b.y, a.z + b.z); }
inline Vector3 operator-(const Vector3& a, const Vector3& b) { return Vector3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline Vector3 operator*(const Vector3& a, float f) { return Vector3(a.x * f, a.y * f, a.z * f); }

struct Matrix3 {
    Vector3 row[3];
};
// row vector times matrix
inline Vector3 operator*(const Vector3& v, const Matrix3& m)
{
    return Vector3(m.row[2].x * v.z + m.row[1].x * v.y + v.x * m.row[0].x,
                   m.row[2].y * v.z + m.row[1].y * v.y + m.row[0].y * v.x,
                   m.row[2].z * v.z + m.row[1].z * v.y + m.row[0].z * v.x);
}

struct Transform {
    enum { kFlagScale = 1, kFlagRotation = 2, kFlagOffset = 4 };
    int16_t mnFlags;
    int16_t mnTransformCount;
    Vector3 mOffset;
    float mfScale;
    Matrix3 mRotation;

    __forceinline Vector3 TransformPoint(const Vector3& p) const
    {
        Vector3 r = p;
        if (mnFlags & kFlagRotation)
            r = p * mRotation;
        return Vector3(r.x * mfScale + mOffset.x, mOffset.y + r.y * mfScale, mOffset.z + r.z * mfScale);
    }
};

// Clamp to [0, 1] with the SSE min/max helper used throughout this module.
__forceinline float Saturate(float value)
{
    float maxValue = 1.0f;
    __asm {
        xorps xmm0, xmm0
        maxss xmm0, value
        minss xmm0, maxValue
        movss value, xmm0
    }
    return value;
}

namespace eastl {

template <int N>
struct bitset {
    uint32_t mWord[(N + 31) / 32];
    bitset() { for (int i = 0; i < (N + 31) / 32; i++) mWord[i] = 0; }
    void set(uint32_t i)
    {
        if (i < N)
            mWord[i >> 5] |= (uint32_t)1 << (i & 31);
    }
    void reset(uint32_t i)
    {
        if (i < N)
            mWord[i >> 5] &= ~((uint32_t)1 << (i & 31));
    }
};

template <class T> struct pair { T first; int second; };

extern "C" void* FUN_011e0744(void* dst, const void* src, unsigned n);   // memcpy thunk

// eastl::fixed_vector<T, N> (0x18-byte header, then the inline buffer)
template <class T, int N>
struct fixed_vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mOverflowAllocator;
    T* mpPoolBegin;
    uint32_t mBufferPad;
    T mBuffer[N];

    fixed_vector()
    {
        mpPoolBegin = mBuffer;
        mpBegin = mpEnd = mBuffer;
        mpCapacity = mBuffer + N;
    }
    ~fixed_vector()
    {
        if (mpBegin && mpBegin != mpPoolBegin)
            operator delete[](mpBegin);
    }
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T& operator[](uint32_t i) { return mpBegin[i]; }
    void reserve(uint32_t n);                       // 0x00c77b60 (out-of-line instance)
    T* erase(T* first, T* last)
    {
        FUN_011e0744(first, last, (unsigned)((char*)mpEnd - (char*)last));
        mpEnd -= (last - first);
        return first;
    }
    void clear() { erase(mpBegin, mpEnd); }
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
    void DoInsertValue(T* position, const T& value);   // 0x00eeee80 (out-of-line instance)
};

}  // namespace eastl

inline void* operator new(size_t, void* p) { return p; }

namespace App {

struct Property {
    void* mpData;
    uint32_t pad04[3];
    uint16_t mnFlags;    // 0x10 (0x30: array / external storage)
    uint16_t mnType;     // 0x12 (1 = bool)
    void* GetStorage() { return (mnFlags & 0x30) ? mpData : this; }
    bool* GetBool();     // 0x0041e920
};

class PropertyList {
public:
    PV8 PV
    virtual bool GetProperty(uint32_t propertyID, Property*& result);   // 0x24
};

}  // namespace App

namespace SP {

class cViewer {
public:
    void GetCameraLocationInfo(Vector3* pPosition, Vector3* pDirection, Vector3* pUp, Vector3* pRight);   // 0x007c3d30
    uint32_t pad00[0xc0 / 4];
    uint32_t mFrustumData[1];    // 0xc0
};

struct cFrustumCull {
    void Set(const void* pViewerFrustum);           // 0x006ffe00
};

struct RenderStatistics;

class ILayer {
public:
    PV2 PV
    virtual void DrawLayer(int flags, int layerIndex, cViewer** ppViewers, RenderStatistics& stats);   // 0x0c
};

struct cModel {
    uint32_t pad00;
    uint32_t mFlags;                       // 0x04 (bit 14: visible)
    Transform mTransform;                  // 0x08
    eastl::bitset<64> mRenderGroups;       // 0x44
    uint32_t pad4c[(0x70 - 0x4c) / 4];
    Vector3 mBoundsMin;                    // 0x70
    Vector3 mBoundsMax;                    // 0x7c
    uint32_t pad88[2];
    App::PropertyList* mpPropList;         // 0x90

    bool IsVisible() const { return (mFlags >> 14) & 1; }
};

struct FilterSettings {
    uint32_t a, b, c, d, e;
    bool f, g;
    FilterSettings() : a(0), b(0), c(0), d(0), e(0), f(false), g(false) {}
};

typedef eastl::fixed_vector<cModel*, 16> ModelVector;

class IModelWorld {
public:
    PV16
    virtual bool FindModelsInFrustum(const cFrustumCull& frustum, ModelVector& result, FilterSettings& settings);   // 0x40
    PV32 PV16 PV4 PV2
    virtual void SetRenderGroups(const eastl::bitset<64>& groups1, const eastl::bitset<64>& groups2, int pass);   // 0x11c
    virtual void GetRenderGroups(eastl::bitset<64>& groups1, eastl::bitset<64>& groups2, int pass);               // 0x120
    PV4 PV
    virtual bool GetActive();               // 0x138
    virtual ILayer* AsLayer();              // 0x13c
};

class IModelManager {
public:
    PV8 PV2
    virtual uint32_t GetRenderGroupIndex(uint32_t groupID, const char* pName);   // 0x28
};
IModelManager* ModelManager();              // 0x0067dd80

class cRenderer {
public:
    void FlushTargets(int n);               // 0x007c3c50 (bit mask 1|2|4 -> 0x11f3d40)
};
extern cRenderer sRenderer;                 // 0x016ca0d8

struct cTerrainMapSet {
    uint32_t pad00[0x34 / 4];
    float mRadius;          // 0x34
    float mMaxHeight;       // 0x38
    float mWaterHeight;     // 0x3c
    float mWaterDelta;      // 0x40
    float GetHeightAt(const Vector3& pos);  // 0x00f927c0
};

// refraction culling tuning
extern float sRefractionHeightRange;        // 0x015b14e0 (200.0)
extern float sRefractionConeLow;            // 0x015b14dc (0.78)
extern float sRefractionConeHigh;           // 0x015b14d8 (0.99)
extern float sRefractionDepthStart;         // 0x015b14d4 (5.0)
extern float sRefractionDepthEnd;           // 0x015b14d0 (100.0)
extern float sRefractionDepthMargin;        // 0x015b14cc (5.0)
extern float sRefractionMarginBias;         // 0x016ca5a8
extern bool sRefractionNoMargin;            // 0x016ca5ac
extern bool sRefractionUseOrigin;           // 0x016ca5ad
extern bool sRefractionSkipConeTest;        // 0x016ca5ae
extern bool sRefractionSkipDepthTest;       // 0x016ca5a6

struct RefractionEntry {
    IModelWorld* mpWorld;
    int mPass;
    cModel* mpModel;
};

enum {
    kPropHideInRefraction  = 0xd4b5ed03,
    kPropAlwaysRefract     = 0x4e5f251c,
    kPropRefractSeparately = 0xf8cec83b,
};

inline bool IsBoolPropertySet(App::PropertyList* pList, uint32_t id)
{
    App::Property* pProp;
    return pList->GetProperty(id, pProp) && pProp->mnType == 1 && *(bool*)pProp->GetStorage();
}
inline bool HasBoolProperty(App::PropertyList* pList, uint32_t id)
{
    App::Property* pProp;
    return pList->GetProperty(id, pProp) && pProp->mnType == 1 && *pProp->GetBool();
}

// Separately drawn models are collected; all others join the underwater render group.
__forceinline void AddRefractionModel(eastl::fixed_vector<RefractionEntry, 16>& separate, IModelWorld* pWorld,
                                      int pass, cModel* pModel, uint32_t group)
{
    if (pModel->mpPropList && HasBoolProperty(pModel->mpPropList, kPropRefractSeparately))
    {
        RefractionEntry entry;
        entry.mpWorld = pWorld;
        entry.mPass = pass;
        entry.mpModel = pModel;
        separate.push_back(entry);
    }
    else
        pModel->mRenderGroups.set(group);
}

class cTerrainSphere {
public:
    void RefractionMapRender(cViewer* pViewer, RenderStatistics& stats);

    uint32_t pad00[0x2c / 4];
    cTerrainMapSet* mpTerrainMapSet;                         // 0x2c
    uint32_t pad30[(0x8b0 - 0x30) / 4];
    eastl::pair<IModelWorld*>* mRefractionWorldsBegin;       // 0x8b0 (vector<pair<IModelWorld*, int>>)
    eastl::pair<IModelWorld*>* mRefractionWorldsEnd;         // 0x8b4
    uint32_t pad8b8[3];
    eastl::pair<ILayer*>* mRefractionLayersBegin;            // 0x8c4 (vector<pair<ILayer*, int>>)
    eastl::pair<ILayer*>* mRefractionLayersEnd;              // 0x8c8
    uint32_t pad8cc[(0x92c - 0x8cc) / 4];
    cFrustumCull mRefractionFrustum;                         // 0x92c
};

// @ 0x00fa2a20
void cTerrainSphere::RefractionMapRender(cViewer* pViewer, RenderStatistics& stats)
{
    uint32_t group = ModelManager()->GetRenderGroupIndex(0xb77980e9, "Terrain_UnderwaterGroup");

    Vector3 unusedPos;
    pViewer->GetCameraLocationInfo(&unusedPos, 0, 0, 0);
    cTerrainMapSet* pMaps = mpTerrainMapSet;
    float waterRadius = (pMaps->mWaterDelta + pMaps->mWaterHeight) * pMaps->mMaxHeight + pMaps->mRadius;
    FilterSettings filter;
    mRefractionFrustum.Set(pViewer->mFrustumData);

    Vector3 camPos, camDir, camUp, camRight;
    pViewer->GetCameraLocationInfo(&camPos, &camDir, &camUp, &camRight);
    Vector3 camUpOnSphere = camPos.NormalizedSafe();

    eastl::fixed_vector<RefractionEntry, 16> separate;
    ModelVector models;
    models.reserve(0x400);

    int numWorlds = (int)(mRefractionWorldsEnd - mRefractionWorldsBegin);
    for (int i = 0; i < numWorlds; i++)
    {
        IModelWorld* pWorld = mRefractionWorldsBegin[i].first;
        if (!pWorld || !pWorld->GetActive())
            continue;
        int pass = mRefractionWorldsBegin[i].second;

        models.clear();
        pWorld->FindModelsInFrustum(mRefractionFrustum, models, filter);

        int numModels = (int)models.size();
        for (int j = 0; j < numModels; j++)
        {
            cModel* pModel = models[j];
            if (!pModel->IsVisible())
                continue;
            if (pModel->mpPropList && IsBoolPropertySet(pModel->mpPropList, kPropHideInRefraction))
                continue;

            // camera-facing test on the nearest point of the bounding sphere
            Vector3 boundsMin = pModel->mTransform.TransformPoint(pModel->mBoundsMin);
            Vector3 boundsMax = pModel->mTransform.TransformPoint(pModel->mBoundsMax);
            Vector3 center((boundsMax.x + boundsMin.x) * 0.5f, (boundsMax.y + boundsMin.y) * 0.5f,
                           (boundsMax.z + boundsMin.z) * 0.5f);
            Vector3 extent = center - boundsMin;
            Vector3 toCamera = camPos - center;
            float radius = extent.Length();
            Vector3 nearest = toCamera.NormalizedSafe() * radius + center;
            float facing = nearest.NormalizedSafe().Dot(camUpOnSphere);

            float height = (camPos.Length() - pMaps->mRadius) / sRefractionHeightRange;
            if (height > 1.0f)
                height = 1.0f;
            else if (0.0f > height)
                height = 0.0f;
            float cone = (sRefractionConeHigh - sRefractionConeLow) * (1.0f - height) + sRefractionConeLow;
            if (cone > facing && !sRefractionSkipConeTest)
                continue;

            if (pModel->mpPropList && HasBoolProperty(pModel->mpPropList, kPropAlwaysRefract))
            {
                AddRefractionModel(separate, pWorld, pass, pModel, group);
                continue;
            }
            {
                // only models reaching below the water surface
                Vector3 bottom = pModel->mTransform.TransformPoint(Vector3(0.0f, 0.0f,
                    (pModel->mBoundsMin.z + pModel->mBoundsMax.z) * 0.5f - (pModel->mBoundsMax.z - pModel->mBoundsMin.z)));
                if (sRefractionUseOrigin)
                {
                    Vector3 origin = pModel->mTransform.mOffset;
                    bottom = origin;
                }
                float bottomRadius = bottom.Length();
                float depth = waterRadius - pMaps->GetHeightAt(pModel->mTransform.mOffset);
                if (0.0f > depth)
                    depth = 0.0f;
                float depthFactor = Saturate((depth - sRefractionDepthStart) / (sRefractionDepthStart - sRefractionDepthEnd));
                float margin = 0.0f;
                if (!sRefractionNoMargin)
                    margin = sRefractionDepthMargin * depthFactor + sRefractionMarginBias;
                if (!(waterRadius > margin + bottomRadius) && !sRefractionSkipDepthTest)
                    continue;
            }
            AddRefractionModel(separate, pWorld, pass, pModel, group);
        }

        // draw this world with only the underwater group enabled
        eastl::bitset<64> groups1;
        eastl::bitset<64> groups2;
        pWorld->GetRenderGroups(groups1, groups2, pass);
        groups1.set(group);
        pWorld->SetRenderGroups(groups1, groups2, pass);
        pWorld->AsLayer()->DrawLayer(pass | 0x1900, 0xd, &pViewer, stats);
        groups1.reset(group);
        pWorld->SetRenderGroups(groups1, groups2, pass);
        for (int j = 0; j < (int)models.size(); j++)
            models[j]->mRenderGroups.reset(group);
    }

    // models drawn separately, batched per model world
    if (separate.size() != 0)
    {
        IModelWorld* pCurrentWorld = 0;
        eastl::bitset<64> groups1;
        eastl::bitset<64> groups2;
        sRenderer.FlushTargets(6);
        int currentPass = 0;
        for (int k = 0; k < (int)separate.size(); k++)
            separate[k].mpModel->mRenderGroups.set(group);
        for (RefractionEntry* it = separate.begin(); it != separate.end(); ++it)
        {
            RefractionEntry entry = *it;
            if (entry.mpWorld != pCurrentWorld)
            {
                if (pCurrentWorld)
                {
                    pCurrentWorld->AsLayer()->DrawLayer(currentPass | 0x1900, 0xd, &pViewer, stats);
                    groups1.reset(group);
                    pCurrentWorld->SetRenderGroups(groups1, groups2, currentPass);
                }
                currentPass = entry.mPass;
                pCurrentWorld = entry.mpWorld;
                pCurrentWorld->GetRenderGroups(groups1, groups2, entry.mPass);
                groups1.set(group);
                pCurrentWorld->SetRenderGroups(groups1, groups2, entry.mPass);
            }
        }
        if (pCurrentWorld)
        {
            pCurrentWorld->AsLayer()->DrawLayer(currentPass | 0x1900, 0xd, &pViewer, stats);
            groups1.reset(group);
            pCurrentWorld->SetRenderGroups(groups1, groups2, currentPass);
        }
        for (int k = 0; k < (int)separate.size(); k++)
            separate[k].mpModel->mRenderGroups.reset(group);
    }

    int numLayers = (int)(mRefractionLayersEnd - mRefractionLayersBegin);
    for (int i = 0; i < numLayers; i++)
    {
        ILayer* pLayer = mRefractionLayersBegin[i].first;
        if (pLayer)
            pLayer->DrawLayer(mRefractionLayersBegin[i].second | 0x1900, 0xd, &pViewer, stats);
    }
}

}  // namespace SP
// --- equivalence checker address annotations
    void operator delete(void*); // 0x00f47380

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
