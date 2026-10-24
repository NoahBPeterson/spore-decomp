// s00e9ed80: 0x00e9ed80 rebuilds a vector of surface sample points laid out in concentric rings
// (spacing mfRingStep) around a centre point, projected onto the planet surface.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (no /EHsc)
#include "types.h"
#include <math.h>
#include <new.h>

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};

// eastl::vector<Vector3> (begin, end, capacity end, allocator)
struct Vector3Vec {
    Vector3* mpBegin;
    Vector3* mpEnd;
    Vector3* mpCapacity;
    uint32_t mAllocator;
    Vector3* erase(Vector3* first, Vector3* last);               // 0x009e0480, thiscall ret 8
    void DoInsertValue(Vector3* pos, const Vector3& v);          // 0x00e9e620, thiscall ret 8
    void push_back(const Vector3& v)
    {
        if (mpEnd < mpCapacity) {
            ::new ((void*)mpEnd) Vector3(v);
            ++mpEnd;
        } else {
            DoInsertValue(mpEnd, v);
        }
    }
};

Vector3 normalized_safe(const Vector3& v);                       // 0x00449c20 (cdecl, sret)

class cPlanetModel {
public:
    void ProjectToSurface(Vector3* out, const Vector3* in);      // 0x00b81630, thiscall ret 8
};
cPlanetModel* PlanetModel();                                     // 0x00b3d350

class cViewer {
public:
    void GetCameraLocationInfo(Vector3* pPosition, Vector3* pDirection, Vector3* pUp, Vector3* pRight);   // 0x007c3d30
};
class cCameraManager {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6();
    virtual cViewer* GetViewer();                                // 0x1c
};
class cApp {
public:
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s0a(); virtual void s0b();
    virtual void s0c(); virtual void s0d(); virtual void s0e(); virtual void s0f();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13();
    virtual cCameraManager* GetCameraManager();                  // 0x50
};
cApp* App();                                                     // 0x0067dd10

extern const float kTwoPi;                                       // 0x016c69c0
extern const Vector3 kZeroVector;                                // 0x016c6964

struct SamplePoints {
    uint32_t pad0[0x9c / 4];
    Vector3 mCentre;            // 0x9c
    uint32_t pad1[(0xc4 - 0xa8) / 4];
    Vector3Vec mPoints;         // 0xc4
    uint32_t padD4[2];
    int mnPoints;               // 0xdc
    float mfRadius;             // 0xe0
    float mfRingStep;           // 0xe4
    void Rebuild();
};

static const float kEps = 1e-8f;

void SamplePoints::Rebuild()
{
    mPoints.erase(mPoints.mpBegin, mPoints.mpEnd);
    mnPoints = 0;
    cPlanetModel* pm = PlanetModel();
    if (!pm) return;
    cApp* app = App();
    if (!app) return;
    cCameraManager* cm = app->GetCameraManager();
    if (!cm) return;
    cViewer* viewer = cm->GetViewer();
    if (!viewer) return;

    Vector3 dir, up, right;
    viewer->GetCameraLocationInfo(0, &dir, &up, &right);
    float inv = 1.0f / sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z + kEps);
    dir = Vector3(dir.x * inv, dir.y * inv, dir.z * inv);
    inv = 1.0f / sqrtf(right.x * right.x + right.y * right.y + right.z * right.z + kEps);
    right = Vector3(right.x * inv, right.y * inv, right.z * inv);

    // Rotation axis: the direction from the planet centre to the sample centre.
    Vector3 axis;
    float len = sqrtf(mCentre.x * mCentre.x + mCentre.y * mCentre.y + mCentre.z * mCentre.z);
    if (len > 0.01f) {
        float k = 1.0f / len;
        axis = Vector3(mCentre.x * k, mCentre.y * k, mCentre.z * k);
    } else {
        axis = normalized_safe(up);
    }

    // First ring direction: axis x right, normalised.
    Vector3 c(axis.y * right.z - axis.z * right.y,
              axis.z * right.x - axis.x * right.z,
              axis.x * right.y - axis.y * right.x);
    float cinv = 1.0f / sqrtf(c.x * c.x + c.y * c.y + c.z * c.z + kEps);

    float ringsF = (float)ceil((double)(mfRadius / mfRingStep));
    float step = mfRadius / ringsF;
    int nRings = (int)ringsF;
    float radius = step;
    for (; nRings > 0; --nRings) {
        float angle = 0.0f;
        int n = (int)((1.0f / step) * kTwoPi * radius);
        float da = kTwoPi / (float)n;
        float vx = c.x * cinv * radius;
        float vy = c.y * cinv * radius;
        float vz = c.z * cinv * radius;
        for (; n > 0; --n) {
            float h = angle * 0.5f;
            float s = sinf(h);
            float w = cosf(h);
            float qx = s * axis.x, qy = s * axis.y, qz = s * axis.z;
            Vector3 p;
            p.x = mCentre.x + ((w * qy + qz * qx) * vz + (qy * qx - w * qz) * vy) * 2.0f
                  + (1.0f - (qz * qz + qy * qy) * 2.0f) * vx;
            p.y = mCentre.y + ((w * qz + qy * qx) * vx + (qz * qy - w * qx) * vz) * 2.0f
                  + (1.0f - (qz * qz + qx * qx) * 2.0f) * vy;
            p.z = mCentre.z + ((qz * qx - w * qy) * vx + (w * qx + qz * qy) * vy) * 2.0f
                  + (1.0f - (qx * qx + qy * qy) * 2.0f) * vz;
            Vector3 out;
            pm->ProjectToSurface(&out, &p);
            mPoints.push_back(out);
            ++mnPoints;
            angle += da;
        }
        radius += step;
    }
}

// ===========================================================================
//  gold7 slice functions (0x00e9f3d0 .. 0x00e9fbc0) -- members of the
//  ambience layer manager that owns the SamplePoints block above (the manager
//  *is* the SamplePoints: +0x9c is the ring centre, +0xc4 the sample vector,
//  +0xdc the point count, +0xe0/+0xe4 the radius and ring step, and the six
//  functions below reach the same fields plus the manager's tag vectors).
//  Same toolchain as the block above: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
// ===========================================================================

// 4-byte-element vector used by the tag/handler lists of the manager.  Its
// out-of-line inserter takes the iterator slot and the value by address.
template <class T> struct SPVec4
{
    T* mpBegin;                                          // +0x00
    T* mpEnd;                                            // +0x04
    T* mpCapacity;                                       // +0x08
    void DoInsertValue(T* pos, const T* pValue);         // 0x00ea9440 (ret 8)
    void resize(int n);                                  // 0x00eb0230 (ret 4)
    void push_back(const T v)
    {
        if (mpEnd < mpCapacity)
        {
            T* slot = mpEnd;
            mpEnd = slot + 1;
            if (slot != 0)
                *slot = v;
        }
        else
        {
            DoInsertValue(mpEnd, &v);
        }
    }
};

void* operator new(unsigned size, const char* tag, int a, int b, void* c, int d);   // 0x00f473a0
void operator delete[](void* p);                                                  // 0x00f47380
extern "C" void* memcpy(void* dst, const void* src, unsigned int n);              // 0x011e0744

// The tag pool: a global free list plus the fixed allocator that feeds it.
struct cSPVector3
{
    float x, y, z;
};
struct cAmbienceTag
{
    uint32_t    mFlags;                                  // +0x00 (free-list link while free)
    uint32_t    mType;                                   // +0x04
    cSPVector3  mPosition;                               // +0x08
    uint32_t    mInstanceId;                             // +0x14
};
extern cAmbienceTag* g_freeTags;                         // [0x016c6a04]
struct FixedAllocator
{
    bool AddCore(void* pCore, unsigned size);            // 0x00926650 (ret 8)
};
extern FixedAllocator g_tagAllocator;                    // [0x016c69f4]

// Static (non-dynamic) tag lookup tree keyed by uint id (manager +0x80).
// eastl rbtree node: 0x14-byte header, then the mapped cAmbienceTag* value.
struct TagNode
{
    uint32_t pad00[5];                                   // +0x00 (parent/child/colour)
    cAmbienceTag* mpValue;                               // +0x14
};
struct TagTree
{
    TagNode* mpAnchor;                                   // +0x00
    TagNode* mpEnd;                                      // +0x04
    void find(TagNode** pOut, const uint32_t* pKey);     // 0x00e5c780 (ret 8)
};

// Curves indexed by the sample radius / sample count (EA::Audio::ResponseCurve).
struct ResponseCurve
{
    uint8_t pad[0x364];                                  // +0x000 (fixed data array)
    float GetOutputValue(float x) const;                 // 0x00a1a110 (ret 4)
};

struct cAmbienceLayerManager;

// The handler interface the sample point / layer objects implement; only the
// slots the manager calls are named.
struct IHandler
{
    virtual void v00();                                  // +0x00 (activate)
    virtual void v04();                                  // +0x04 (release)
    virtual void v08();                                  // +0x08 (addref)
    virtual void v0c();                                  // +0x0c
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual float Test(void* p);                         // +0x20 (ret 4)
    virtual void v24();
    virtual void v28();
    virtual void Release();                              // +0x2c
};
typedef IHandler** IHandlerSlot;

class cAmbienceLayer : public IHandler
{
public:
    float x, y, z;                                       // +0x04 sampled position
    void FUN_00a355e0(const char* name);                 // 0x00a355e0 (ret 4)
    float FUN_00a34ed0();                                // 0x00a34ed0 (ret 0) -> distance
    void FUN_00ed4890(uint32_t hash);                    // 0x00ed4890 (ret 4)
    void UpdatePrimitives(float dt, uint32_t n);         // 0x00a34ee0 (ret 8)
    void FUN_00a35c00();                                 // 0x00a35c00 (ret 0)
    void FUN_00a35c40(IHandlerSlot pList, float t);      // 0x00a35c40 (ret 8)
    void Update();                                       // 0x00a35d20 (ret 0)
    bool Init();                                         // 0x00a36570 (ret 0)
};
cAmbienceLayer* __fastcall cAmbienceLayer_operatorNew(void* p);   // 0x00a35aa0

class cAmbienceLayerManager
{
public:
    uint8_t  pad00[0x28];                                // +0x00
    int32_t  mnCubeMapSize;                              // +0x28
    SPVec4<uint8_t*> mCubeMapFaces;                      // +0x2c
    uint8_t  pad38[0x54 - 0x38];                         // +0x38
    SPVec4<cAmbienceTag*> mAmbientViewTags;              // +0x54
    uint8_t  pad60[0x68 - 0x60];                         // +0x60
    SPVec4<cAmbienceTag*> mDynamicViewTags;              // +0x68 (end at 0x6c is the generation cursor)
    uint8_t  pad74[0x7c - 0x74];                         // +0x74
    cAmbienceTag**  mDynamicViewTagsIterator;            // +0x7c  (dynamic tag slot cursor)
    TagTree  mIdToTagMap;                                // +0x80
    uint8_t  pad88[0x9c - 0x88];                         // +0x88
    Vector3  mCentre;                                    // +0x9c  (ambient sphere centre)
    float    mfMaxLayerDistance;                         // +0xa8
    uint8_t  mbDirty;                                    // +0xac
    uint8_t  padad[0xb0 - 0xad];                         // +0xad
    SPVec4<cAmbienceLayer*> mLayers;                     // +0xb0
    uint8_t  padbc[0xc4 - 0xbc];                         // +0xbc
    Vector3Vec mSamplePoints;                            // +0xc4  (SamplePoints::mPoints)
    uint8_t  padd4[0xd8 - 0xd4];                         // +0xd4
    float    mfSampleRadius;                             // +0xd8
    int32_t  mnSamplePoints;                             // +0xdc
    float    mfRingRadius;                               // +0xe0
    float    mfRingStep;                                 // +0xe4
    uint32_t mModificationCount;                         // +0xe8
    ResponseCurve mCurveSampleRadius;                    // +0xec
    ResponseCurve mCurveDistanceBetween;                 // +0x450
    uint8_t  pad474[0x7cc - 0x7b4];                      // +0x7b4
    uint32_t mStateFlags;                                // +0x7cc  (bit0 busy, bit1 no planet, bit2 game mode)
    uint32_t mPhase;                                     // +0x7d0
    cSPVector3* mItSamplePts;                            // +0x7d4
    cSPVector3* mItSamplePtsEnd;                         // +0x7d8

    void  InsertDynamicTag(cAmbienceTag*** pSlot, const cSPVector3* pPos, uint32_t id);  // @ 0x00e9f3d0
    void  GenerateDynamicAmbienceTags();                                                // @ 0x00e9f480
    void  Update(float dt);                                                             // @ 0x00e9f770
    bool  InsertTag(uint32_t key, float x, float y, float z, uint32_t id);              // @ 0x00e9f9c0
    bool  FUN_00e9faa0(const char* name);                                               // @ 0x00e9faa0
    void  ResetCubeMap();                                                               // @ 0x00e9fbc0
    void  DestroyCubeMap();                                                             // 0x00e9e350
    void  GenerateDynamicAmbienceTagsBegin();                                           // 0x00e9dd80
    void  RemoveDynamicTags();                                                          // 0x00e9ea40
    bool  FUN_00e9dd20(uint32_t hash);                                                  // 0x00e9dd20
    bool  FUN_00e9ed00(cAmbienceTag* tag);                                              // 0x00e9ed00
    void  SamplePointsRebuild();                                                        // 0x00e9ed80
    void  FUN_00e9e8f0(cAmbienceLayer** pos, cAmbienceLayer** pValue);                  // 0x00e9e8f0
};

// The effect-manager lookups in GenerateDynamicAmbienceTags.
struct IEff
{
    virtual void* Get(uint32_t name, int zero);          // +0x8c (ret 8)
};
IEff* EffectsManagerPtr();                               // 0x0067ddd0
struct IObject
{
    virtual void Slot0();
    virtual void v04();
    virtual void Slot8();
    virtual void SlotC();
    virtual void Slot10(); virtual void Slot14(); virtual void Slot18(); virtual void Slot1c();
    virtual float Test(void* p);                         // +0x20 (ret 4)
};

// Terrain map set: heights used to decide whether a sample is under water.
class cTerrainMapSet
{
public:
    uint8_t  pad00[0x34];                                // +0x00
    float    mfRadius;                                   // +0x34
    float    mfMaxHeight;                                // +0x38
    float    mfWaterHeight;                              // +0x3c
    float    mfWaterDelta;                               // +0x40
    float    mfBeachHeight;                              // +0x44
    float GetHeightAt(const cSPVector3* pSample);        // 0x00f927c0 (ret 4)
};

// A sample point produced by the planet surface walk (xyz + influence radius).
struct cTerrainSample
{
    uint8_t  pad00[0x38];                                // +0x00
    float    mfX;                                        // +0x38
    float    mfY;                                        // +0x3c
    float    mfZ;                                        // +0x40
    uint8_t  pad44[4];                                   // +0x44
    float    mfRadius;                                   // +0x48
};

class cPlanetSurface
{
public:
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual cTerrainMapSet* GetMap();                    // +0x0c (ret 0)
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual float Test(const cSPVector3* p);             // +0x20 (ret 4)
    bool FUN_00b7e3e0(const cSPVector3* pSample);        // 0x00b7e3e0 (ret 4)
};
struct PlanetModelT
{
    uint8_t  pad00[0x24];                                // +0x00
    cPlanetSurface* mpSurface;                           // +0x24
};
PlanetModelT* PlanetModelObj();                           // 0x00b3d350
uint32_t SP_GetCurrentGameMode();                        // 0x00b5b800

// Sample walk result: pointers plus an inline 256-entry buffer (eastl fixed vector).
struct SampleVec
{
    cTerrainSample** mpBegin;                            // +0x00
    cTerrainSample** mpEnd;                              // +0x04
    cTerrainSample** mpCapacity;                         // +0x08
    uint8_t          pad0c[8];                           // +0x0c
    uint32_t         mnGuard;                            // +0x14 (0 => inline buffer)
    cTerrainSample*  mBuffer[256];                       // +0x18
    SampleVec()
        : mpBegin(mBuffer), mpEnd(mBuffer), mpCapacity(mBuffer + 256), mnGuard(0) {}
    ~SampleVec()
    {
        if (mpBegin != 0 && ((uint32_t*)mpBegin)[-1] != 0)
            operator delete[](mpBegin);
    }
};
SampleVec* __stdcall FUN_00b3d3c0(Vector3* pCentre, SampleVec* pOut, int mode, float radius, int a, int b);  // 0x00b3d3c0
void __fastcall FUN_00b79c30(SampleVec* p);                // 0x00b79c30 (ecx arg)

struct LARGE_INTEGER_T { __int64 QuadPart; };
extern "C" int __stdcall QueryPerformanceCounter_(LARGE_INTEGER_T* p);   // kernel32

struct EAStopwatch
{
    uint8_t pad00[0x18];                                 // +0x00
    LARGE_INTEGER_T mDeadline;                           // +0x18 (QPC deadline)
    void ctor(int units, bool b);
    void SetTimeLimit(uint32_t limit, bool b);           // 0x0093a480 (ret 8)
    void Restart();                                      // 0x00571e80 (ret 0)
    void Destroy();                                      // 0x0093a2e0 (ret 0)
};
uint32_t FNVHash(const char* s, uint32_t seed, int mode);  // 0x00932e80 (cdecl)

// ------------------------------------------------------------------ 0x00e9f3d0
// Appends a dynamically generated tag to the manager's dynamic view tags: when
// the caller's cursor is at the vector end, a tag is popped from the global
// free list (or the fixed allocator is asked for another core) and pushed, the
// cursor is then left pointing at the new element and advanced past it while
// the tag's flags/id/position are filled in.
// A tag from the global free list, growing the pool when it is empty.
static __forceinline cAmbienceTag* AcquireTag()
{
    cAmbienceTag* tag = g_freeTags;
    while (tag == 0)
    {
        if (!g_tagAllocator.AddCore(0, 0))
        {
            tag = 0;
            break;
        }
        tag = g_freeTags;
    }
    if (tag != 0)
    {
        g_freeTags = (cAmbienceTag*)tag->mFlags;
        tag->mFlags = 0;
        tag->mType = 0;
        tag->mInstanceId = 0;
    }
    return tag;
}

// @ 0x00e9f3d0
void cAmbienceLayerManager::InsertDynamicTag(cAmbienceTag*** pSlot, const cSPVector3* pPos, uint32_t id)
{
    if (*pSlot == mDynamicViewTags.mpEnd)
    {
        mDynamicViewTags.push_back(AcquireTag());
        *pSlot = mDynamicViewTags.mpEnd - 1;
    }
    cAmbienceTag* tag = *(cAmbienceTag**)*pSlot;
    tag->mFlags |= 1;
    *pSlot += 1;
    tag->mPosition = *pPos;
    tag->mType = id;
}

// ------------------------------------------------------------------ 0x00e9f480
// Walks the planet surface's sample points, turning each sample into dynamic
// ambience tags for the layers that overlap it.  Uses a stopwatch to bound the
// work and drops one "changed" tag when the walk finished.
// @ 0x00e9f480
void cAmbienceLayerManager::GenerateDynamicAmbienceTags()
{
    EAStopwatch stopwatch;
    stopwatch.ctor(3, 0);
    stopwatch.SetTimeLimit(500, 1);

    PlanetModelT* pModel = PlanetModelObj();
    if (!pModel)
        return;
    cPlanetSurface* pSurface = PlanetModelObj()->mpSurface;
    if (!pSurface)
    {
        if (mItSamplePts == mItSamplePtsEnd)
            mPhase = 2;
        return;
    }

    IObject* pObj = (IObject*)EffectsManagerPtr()->Get(0x2c9c762, 0);
    if (pObj)
        pObj->Slot0();
    cAmbienceLayer* pLayerProxy = (cAmbienceLayer*)EffectsManagerPtr()->Get(0x1c8a626, 0);
    if (pLayerProxy)
        pLayerProxy->v00();

    SampleVec samples;
    FUN_00b79c30(FUN_00b3d3c0(&mCentre, &samples, 7, mfRingRadius, 0, 0));
    unsigned nSamples = (unsigned)(samples.mpEnd - samples.mpBegin);

    for (; mItSamplePts != mItSamplePtsEnd; ++mItSamplePts)
    {
        LARGE_INTEGER_T now;
        QueryPerformanceCounter_(&now);
        __int64 remaining = stopwatch.mDeadline.QuadPart - now.QuadPart;
        if (remaining < 0)
            break;

        if (pSurface->FUN_00b7e3e0(mItSamplePts))
        {
            InsertDynamicTag(&mDynamicViewTagsIterator, mItSamplePts, 0x9e3c3dfa);
        }
        else
        {
            cTerrainMapSet* pMap = pSurface->GetMap();
            float height = (pMap->mfBeachHeight + pMap->mfWaterHeight) * pMap->mfMaxHeight
                         + pMap->mfRadius;
            float terrainH = pSurface->GetMap()->GetHeightAt(mItSamplePts);
            if (terrainH < height)
                InsertDynamicTag(&mDynamicViewTagsIterator, mItSamplePts, 0x9a1731dc);
        }
        for (unsigned i = 0; i < nSamples; ++i)
        {
            cTerrainSample* p = samples.mpBegin[i];
            float dz = p->mfZ - mItSamplePts->z;
            float dy = p->mfY - mItSamplePts->y;
            float dx = p->mfX - mItSamplePts->x;
            if (p->mfRadius * p->mfRadius > dz * dz + dy * dy + dx * dx)
                InsertDynamicTag(&mDynamicViewTagsIterator, mItSamplePts, 0x6d5c48c);
        }
        if (pObj != 0 && pSurface->Test(mItSamplePts) == 1.0f
            && pObj->Test(mItSamplePts) == 1.0f)
            InsertDynamicTag(&mDynamicViewTagsIterator, mItSamplePts, 0xfd3d2ed9);
    }

    InsertDynamicTag(&mDynamicViewTagsIterator, (const cSPVector3*)&mCentre, 0x76822486);
    if (pLayerProxy)
        pLayerProxy->v04();
    if (pObj)
        pObj->v04();
    if (mItSamplePts == mItSamplePtsEnd)
        mPhase = 2;
}

// ------------------------------------------------------------------ 0x00e9f770
// Per-frame update: refreshes the "no planet"/"game mode" flags, advances the
// manager's phase machine (restart sample points, generate tags, remove tags)
// and then updates every ambience layer with the frame time.
// @ 0x00e9f770
void cAmbienceLayerManager::Update(float dt)
{
    if (mStateFlags & 8)
        return;
    if (mCentre.x != kZeroVector.x || mCentre.y != kZeroVector.y || mCentre.z != kZeroVector.z)
    {
        if (PlanetModelObj() == 0 || PlanetModelObj()->mpSurface == 0)
            mStateFlags |= 2;
        else
            mStateFlags &= ~2u;
        if (SP_GetCurrentGameMode() == 0xffffffffu || SP_GetCurrentGameMode() == 0x2ccd1d2
            || SP_GetCurrentGameMode() == 0xdbdba1)
            mStateFlags |= 4;
        else
            mStateFlags &= ~4u;

        EAStopwatch stopwatch;
        stopwatch.ctor(3, 0);
        stopwatch.Restart();

        if (mStateFlags == 0)
        {
            switch (mPhase)
            {
            case 0:
            {
                float a = mCurveSampleRadius.GetOutputValue(mfSampleRadius);
                float b = mCurveDistanceBetween.GetOutputValue(mfSampleRadius);
                if (mbDirty != 0 || a != mfRingRadius || b != mfRingStep)
                {
                    mfRingRadius = a;
                    mfRingStep = b;
                    SamplePointsRebuild();
                    GenerateDynamicAmbienceTagsBegin();
                    mPhase = 1;
                }
                break;
            }
            case 1:
                GenerateDynamicAmbienceTags();
                break;
            case 2:
                if (mbDirty != 0)
                    RemoveDynamicTags();
                mPhase = 0;
                break;
            }
        }
        else
        {
            mPhase = 0;
        }
        ++mModificationCount;
        for (int i = 0; i < (int)(mLayers.mpEnd - mLayers.mpBegin); ++i)
        {
            cAmbienceLayer* pLayer = mLayers.mpBegin[i];
            pLayer->UpdatePrimitives(dt, mModificationCount);
            if (mPhase != 1)
            {
                pLayer->FUN_00a35c00();
                if (mAmbientViewTags.mpBegin != mAmbientViewTags.mpEnd)
                    pLayer->FUN_00a35c40((IHandlerSlot)&mAmbientViewTags, dt);
                if (mDynamicViewTags.mpBegin != mDynamicViewTags.mpEnd)
                    pLayer->FUN_00a35c40((IHandlerSlot)&mDynamicViewTags, dt);
                pLayer->Update();
            }
        }
        stopwatch.Destroy();
        mbDirty = 0;
    }
}

// ------------------------------------------------------------------ 0x00e9f9c0
// Inserts a tag for the given id unless the manager already has a live tag for
// it; reuses a tag from the global free list.
// @ 0x00e9f9c0
bool cAmbienceLayerManager::InsertTag(uint32_t key, float x, float y, float z, uint32_t id)
{
    TagNode* pNode;
    mIdToTagMap.find(&pNode, &key);
    if (pNode != mIdToTagMap.mpEnd && pNode->mpValue != 0)
        return false;

    cAmbienceTag* tag = AcquireTag();
    if (!tag)
        return false;

    cSPVector3 pos;
    pos.x = x;
    pos.y = y;
    pos.z = z;
    tag->mPosition = pos;
    tag->mType = id;
    tag->mInstanceId = key;
    return FUN_00e9ed00(tag);
}

// ------------------------------------------------------------------ 0x00e9faa0
// Creates an ambience layer for the given name and appends it to the layer
// list, keeping +0xa8 at the maximum layer distance seen.
// @ 0x00e9faa0
bool cAmbienceLayerManager::FUN_00e9faa0(const char* name)
{
    uint32_t hash = FNVHash(name, 0x811c9dc5, 1);
    if (FUN_00e9dd20(hash))
        return false;

    cAmbienceLayer* pLayer = 0;
    void* pMem = operator new(0x298, "Audio", 0, 0, 0, 0);
    if (pMem != 0)
        pLayer = cAmbienceLayer_operatorNew(pMem);
    if (pLayer != 0)
        pLayer->v08();
    pLayer->FUN_00a355e0(name);
    pLayer->FUN_00ed4890(hash);
    if (!pLayer->Init())
    {
        if (pLayer != 0)
            pLayer->v0c();
        return false;
    }
    if (mLayers.mpEnd < mLayers.mpCapacity)
    {
        cAmbienceLayer** slot = mLayers.mpEnd;
        mLayers.mpEnd = slot + 1;
        if (slot != 0)
        {
            *slot = pLayer;
            if (pLayer != 0)
                pLayer->v08();
        }
    }
    else
    {
        FUN_00e9e8f0(mLayers.mpEnd, &pLayer);
    }
    float distance = pLayer->FUN_00a34ed0();
    if (mfMaxLayerDistance < distance)
        mfMaxLayerDistance = distance;
    if (pLayer != 0)
        pLayer->v0c();
    return true;
}

// A 100-entry scratch pointer vector kept per cube-map face.
struct PtrVec100
{
    void** mpBegin;                                      // +0x00
    void** mpEnd;                                        // +0x04
    void** mpCapacity;                                   // +0x08
};
extern char g_eastlAllocator;                            // 0x013ebb38

// ------------------------------------------------------------------ 0x00e9fbc0
// Rebuilds the ambience layer cube map: one 100-entry scratch vector per cube
// face.
// @ 0x00e9fbc0
void cAmbienceLayerManager::ResetCubeMap()
{
    DestroyCubeMap();
    int nFaces = mnCubeMapSize * mnCubeMapSize * 6;
    mCubeMapFaces.resize(nFaces);
    for (int i = 0; i < nFaces; ++i)
    {
        PtrVec100* pList = (PtrVec100*)operator new(0x14, "Audio", 0, 0, 0, 0);
        if (pList != 0)
        {
            pList->mpBegin = 0;
            pList->mpEnd = 0;
            pList->mpCapacity = 0;
        }
        else
        {
            pList = 0;
        }
        if ((uint32_t)(pList->mpCapacity - pList->mpBegin) < 100)
        {
            void** pNew = (void**)operator new(400, "Simulator", 0, 0, &g_eastlAllocator, 0xd1);
            memcpy(pNew, pList->mpBegin, (char*)pList->mpEnd - (char*)pList->mpBegin);
            if (pList->mpBegin != 0)
                operator delete[](pList->mpBegin);
            void** pOldBegin = pList->mpBegin;
            pList->mpBegin = pNew;
            pList->mpEnd = pNew + (pList->mpEnd - pOldBegin);
            pList->mpCapacity = pNew + 100;
        }
        mCubeMapFaces.mpBegin[i] = (uint8_t*)pList;
    }
}
