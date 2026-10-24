// Slice s00c85a30: SP::cSolarSystem::InitComets (random comet generation for a solar system).
// Flags /O2 /MD /Gy /TP /arch:SSE /fp:fast (fsin/fcos inlined, SSE float math, no EH frame).
#include "types.h"
#include <math.h>

typedef unsigned int size_t;
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);  // 0x00f473a0
inline void* operator new(size_t, void* p) { return p; }

// ---- RNG and shared constants -------------------------------------------------------------------
namespace EA { namespace Random {
class RandomLinearCongruential { public:
    uint32_t mnSeed;
    uint32_t RandomUint32Uniform(uint32_t nLimit);               // 0x00a68fb0
    double   RandomDoubleUniform();                              // 0x009360d0
};
} }
extern EA::Random::RandomLinearCongruential gRandom;            // 0x01601760
extern float kPi;                                          // 0x01579d48
extern float kTwoPi;                                       // 0x01694c6c
struct Vec3c { float x, y, z; };
extern Vec3c kAxisX;                                       // 0x01579d4c (1,0,0)
extern Vec3c kAxisZ;                                       // 0x01579d58 (0,0,1)

// ---- property access ----------------------------------------------------------------------------
struct Property {
    char     pad[0x12];
    unsigned short type;                                         // +0x12 (0xd = float)
    float*   GetFloat();                                         // 0x0041ea70
};
struct PropertyList {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool GetProperty(uint32_t id, Property** out);       // slot 9 (+0x24)
};
extern PropertyList** gStarProperties;                           // 0x01694c54
extern float gStarCache[13];                                     // 0x01579d10 (-1.0 = not yet computed)

bool  __cdecl IsGasType(int t);                                  // 0x00c8b450
float __cdecl GetGasValue(int t);                                // 0x00c84420
float __cdecl GetStarTemperature(int t);                         // 0x00c84310

// Cached per-star-type value; the non-gas branch is the inlined GetStarRadius body (0x00c84120).
__forceinline float CachedStarValue(int t)
{
    float* p = &gStarCache[t];
    if (*p < 0.0f) {
        float v;
        if (IsGasType(t)) {
            v = GetGasValue(t);
        } else {
            v = 30.0f;
            switch (t) {
            case 1: v = 300.0f; break;
            case 2: case 3: v = 100.0f; break;
            case 4: case 5: case 6: {
                Property* pr;
                PropertyList* pl = gStarProperties[t];
                if (pl && pl->GetProperty(0x383cd6f, &pr) && pr->type == 0xd)
                    v = *pr->GetFloat();
                break;
            }
            }
        }
        *p = v;
    }
    return *p;
}

// ---- strings -------------------------------------------------------------------------------------
namespace SP {
class cString {
public:
    cString(uint32_t tableID, uint32_t instanceID, int a);       // 0x006b5770
    ~cString();                                                  // 0x006b5240
    const wchar_t* GetText();                                    // 0x006b55c0
    uint32_t mData[5];
};
}
struct WString {
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; uint32_t mAlloc;
    void assign(const wchar_t* first, const wchar_t* last);      // 0x00423650
    void assign(const WString& o) { assign(o.mpBegin, o.mpEnd); }
    void assign(const wchar_t* p)
    {
        const wchar_t* e = p;
        while (*e) ++e;
        assign(p, p + (e - p));
    }
};

// ---- objects -------------------------------------------------------------------------------------
class cStarManager;
struct cStar;

// 0x00c8b550 family: cStar's accessors used while initialising the system.
struct cStar
{
    int      GetType();                          // 0x00c8b550
    bool     IsKnown();                          // 0x00c8b7e0 (name guessed)
    bool     HasComets();                        // 0x00c8b800 (name guessed)
    WString* GetName();                          // 0x00c8b540
    char     pad0[0x48];
    cStarManager* mpPlanetManager;               // +0x48
};
class cPlanet;
struct cBodyVisual;
struct cBodyEffect;
struct cSPVector3 { float x, y, z; };
struct cCelestialBody;
template <typename T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p) : mpObject(p) { mpObject->AddRef(); }
    AutoRefCount(const AutoRefCount& o) : mpObject(o.mpObject) { mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(T* p)
    {
        if (mpObject != p) {
            if (p) p->AddRef();
            T* pOld = mpObject;
            mpObject = p;
            if (pOld) pOld->Release();
        }
        return *this;
    }
};

struct cEllipticalOrbit {
    bool  mNullOrbit;                                            // +0x00
    float mPlaneNormal[3];                                       // +0x04
    float mEccentricity;                                         // +0x10
    float mPerihelion[3];                                        // +0x14
    float mPeriod;                                               // +0x20
    char  pad[0x68 - 0x24];
    void  Update();                                              // 0x00fe8450
};

struct cCelestialBody {
    virtual int AddRef();
    virtual int Release();
    char             pad0[0x34 - 4];
    int              mType;                                      // +0x34
    cEllipticalOrbit mOrbit;                                     // +0x38 (0x68)
    cSPVector3       mPosition;                                  // +0xa0
    float            mRotationRate;                              // +0xac
    WString          mName;                                      // +0xb0
    cBodyVisual*     mpVisual;                                   // +0xc0
    cBodyEffect*     mpEffect;                                   // +0xc4
    float            mHitSphereSize;                             // +0xc8
    cCelestialBody(int type);                                    // 0x00bd6410
    void Setup();                                                // 0x00bd6300
    void SetBrightness(float value);                             // 0x00bd6590
};

template <typename T> struct vector {
    T* mpBegin; T* mpEnd; T* mpCapacity;
    void DoInsertValue(T* position, const T& value);             // 0x00aea5d0
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
};

struct cStar;

struct cSolarSystem {
    char    pad0[0xc];
    cStar*  mpStar;                                              // +0x0c
    vector<AutoRefCount<cPlanet> > mPlanets;                     // +0x10
    char    pad1[0x24 - 0x1c];
    vector<AutoRefCount<cCelestialBody> > mCelestialBodies;      // +0x24
    char    pad2[0x38 - 0x30];
    AutoRefCount<cCelestialBody> mStarBody;                      // +0x38
    void InitComets();
    static void InitTuning();                                    // 0x00c86640
    void InitStar(cStar* pStar);                                 // 0x00c86760
    void UpdateBodies(float value);                              // 0x00c86390
};

// result = clamp(rand * (hi - lo) + lo, lo, hi) evaluated in double
__forceinline double RandomRange(double lo, double hi)
{
    double v = gRandom.RandomDoubleUniform() * (hi - lo) + lo;
    if (v < hi) {
        if (v >= lo)
            return v;
        return lo;
    }
    return hi;
}

// @ 0x00c85a30
void cSolarSystem::InitComets()
{
    AutoRefCount<cCelestialBody>* it = mCelestialBodies.mpBegin;
    AutoRefCount<cCelestialBody>* end = mCelestialBodies.mpEnd;
    for (; it != end; ++it)
        if (it->mpObject->mType == 2)
            return;

    int nComets = (int)gRandom.RandomUint32Uniform(4) + 3;
    if (nComets > 0) do {
        cCelestialBody* pRaw = new("Simulator/cCelestialBody", 0, 0, 0, 0) cCelestialBody(2);
        cCelestialBody* body = pRaw;

        // orientation: tilt about X by a clamped angle, then spin about Z by a random angle
        float angle = (float)(gRandom.RandomDoubleUniform() * kTwoPi);
        double lim = kPi * 0.25f;
        double tilt = RandomRange(-lim, lim) * 0.5f;
        double st = sin(tilt);
        float q1x = kAxisX.x * st, q1y = kAxisX.y * st, q1z = kAxisX.z * st;
        float q1w = (float)cos(tilt);

        double half = 0.5f * angle;
        float sp = (float)sin(half);
        float ax = kAxisZ.x * sp, ay = kAxisZ.y * sp, az = kAxisZ.z * sp;
        float cp = (float)cos(half);

        // q = (ax,ay,az,cp) * (q1x,q1y,q1z,q1w)
        float cxv = ay * q1z - az * q1y;
        float cyv = az * q1x - q1z * ax;
        float czv = q1y * ax - ay * q1x;
        float qx = (cp * q1x + q1w * ax) + cxv;
        float qy = (cp * q1y + ay * q1w) + cyv;
        float qz = (cp * q1z + az * q1w) + czv;
        float qw = cp * q1w - ((ax * q1x + az * q1z) + ay * q1y);

        // radius range from the star type
        int type = mpStar->GetType();
        float r0 = CachedStarValue(type);
        float hiR = r0 + GetStarTemperature(type) * 85.0f;
        type = mpStar->GetType();
        float r1 = CachedStarValue(type);
        GetStarTemperature(type);
        float radius = (float)RandomRange(r1 + 15.0f, hiR);

        float xx = qx * qx, xy = qx * qy, xz = qx * qz;
        float yy = qy * qy, yz = qy * qz, zz = qz * qz;
        float wx = qw * qx, wy = qw * qy, wz = qw * qz;

        body->mOrbit.mNullOrbit = false;
        body->mOrbit.mPlaneNormal[0] = ((xy - wz) * kAxisZ.y + (wy + xz) * kAxisZ.z) * 2.0f + (1.0f - (zz + yy) * 2.0f) * kAxisZ.x;
        body->mOrbit.mPlaneNormal[1] = ((yz - wx) * kAxisZ.z + (wz + xy) * kAxisZ.x) * 2.0f + (1.0f - (zz + xx) * 2.0f) * kAxisZ.y;
        body->mOrbit.mPlaneNormal[2] = ((wx + yz) * kAxisZ.y + (xz - wy) * kAxisZ.x) * 2.0f + (1.0f - (yy + xx) * 2.0f) * kAxisZ.z;

        double e = RandomRange(0.3f, 0.7f);
        body->mOrbit.mEccentricity = (float)e;

        float px = ((xy - wz) * kAxisX.y + (wy + xz) * kAxisX.z) * 2.0f + (1.0f - (zz + yy) * 2.0f) * kAxisX.x;
        float py = ((yz - wx) * kAxisX.z + (wz + xy) * kAxisX.x) * 2.0f + (1.0f - (zz + xx) * 2.0f) * kAxisX.y;
        float pz = ((wx + yz) * kAxisX.y + (xz - wy) * kAxisX.x) * 2.0f + (1.0f - (yy + xx) * 2.0f) * kAxisX.z;
        float inv = 1.0f / sqrtf((px * px + (py * py + pz * pz)) + 1e-8f);
        body->mOrbit.mPerihelion[0] = (inv * px) * radius;
        body->mOrbit.mPerihelion[1] = (py * inv) * radius;
        body->mOrbit.mPerihelion[2] = (pz * inv) * radius;

        body->mOrbit.mPeriod = (float)RandomRange(300.0f, 900.0f);
        body->mOrbit.Update();
        body->Setup();

        {
            SP::cString name(0x2db6dad3, 0x3f5a128, 0);
            body->mName.assign(name.GetText());
        }
        body->mHitSphereSize = 2.0f;

        AutoRefCount<cCelestialBody> ref(body);
        mCelestialBodies.push_back(ref);
    } while (--nComets != 0);
}

// ===========================================================================================
// Batch 2: star/tuning initialisation of the solar system (00c86390, 00c86640, 00c86760).
// ===========================================================================================
struct cCelestialBody;

// Ref-counted planet handle: AddRef at slot 0xbc, Release at slot 0xc0.
class cPlanet
{
public:
    virtual void v000(); virtual void v004(); virtual void v008(); virtual void v00c();
    virtual void v010(); virtual void v014(); virtual void v018(); virtual void v01c();
    virtual void v020(); virtual void v024(); virtual void v028(); virtual void v02c();
    virtual void v030(); virtual void v034(); virtual void v038(); virtual void v03c();
    virtual void v040(); virtual void v044(); virtual void v048(); virtual void v04c();
    virtual void v050(); virtual void v054(); virtual void v058(); virtual void v05c();
    virtual void v060(); virtual void v064(); virtual void v068(); virtual void v06c();
    virtual void v070(); virtual void v074(); virtual void v078(); virtual void v07c();
    virtual void v080(); virtual void v084(); virtual void v088(); virtual void v08c();
    virtual void v090(); virtual void v094(); virtual void v098(); virtual void v09c();
    virtual void v0a0(); virtual void v0a4(); virtual void v0a8(); virtual void v0ac();
    virtual void v0b0(); virtual void v0b4(); virtual void v0b8();
    virtual void AddRef();                       // +0xbc
    virtual void Release();                      // +0xc0
    char    pad00[0x2c - 0x04];
    int32_t m_flags;                             // +0x2c
    float   GetValue(int index);                 // 0x00c70f90
};

// A single planet entry of a star (the manager stores cPlanet* by value).
struct cStarPlanet { cPlanet* mpPlanet; };

class cStarManager
{
public:
    cPlanet* GetOrActivatePlanet();              // 0x00bb59b0
};

// 0x00b3d2a0 (name from the PDB): resolves the manager for a planet record.
cStarManager* __cdecl SP_StarManager(cStarPlanet* pRecord, cPlanet** out);

// 0x00bb a790: the planet list of a star.
struct cPlanetVector
{
    cStarPlanet* mpBegin;
    cStarPlanet* mpEnd;
    cStarPlanet* mpCapacity;
};
cPlanetVector* __cdecl cStarManager_planets(cStarManager* pManager);   // 0x00bba790

// ---- star -------------------------------------------------------------------------------------
float __cdecl GetStarRotationRate(int type);     // 0x00c842a0

// ---- star tuning properties (0x01694c54) ------------------------------------------------------
class PropertyObject
{
public:
    virtual void f0();
    virtual void Release();                      // +0x04
};

struct RefPtrProperty
{
    PropertyObject* mpObject;
    void release()
    {
        PropertyObject* p = mpObject;
        if (p) {
            mpObject = 0;
            p->Release();
        }
    }
};

struct StarPropertyVector                            // EA vector<RefPtr<Property>> @ 0x01694c54
{
    RefPtrProperty* mpBegin;                         // 0x01694c54
    RefPtrProperty* mpEnd;                           // 0x01694c58
    RefPtrProperty* mpCapacity;                      // 0x01694c5c

    void DoInsertValues(RefPtrProperty* position, int count, const RefPtrProperty& value);  // 0x0042aeb0
    void erase(RefPtrProperty* first, RefPtrProperty* last);                               // 0x00533500
    void resize(uint32_t n)
    {
        uint32_t count = (uint32_t)(mpEnd - mpBegin);
        if (n > count) {
            RefPtrProperty empty = { 0 };
            DoInsertValues(mpEnd, (int)(n - count), empty);
        } else {
            erase(mpBegin + n, mpEnd);
        }
    }
};

class PropertyManager
{
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual void GetProperty(uint32_t propertyId, uint32_t tableId, RefPtrProperty* out);  // +0x2c
};

PropertyManager* __cdecl SP_PropertyManager();   // 0x0067de30

extern StarPropertyVector gStarPropertySlots;    // 0x01694c54 (same block as gStarProperties)
extern RefPtrProperty     gDefaultStarProperty;  // 0x01694c68

// @ 0x00c86640
void cSolarSystem::InitTuning()
{
    PropertyManager* pManager = SP_PropertyManager();
    if (gStarPropertySlots.mpBegin == gStarPropertySlots.mpEnd) {
        gStarPropertySlots.resize(13);
        gStarPropertySlots.mpBegin[4].release();
        pManager->GetProperty(0x4c66e1e4, 0x74d2735b, &gStarPropertySlots.mpBegin[4]);
        gStarPropertySlots.mpBegin[5].release();
        pManager->GetProperty(0x4c66e1ec, 0x74d2735b, &gStarPropertySlots.mpBegin[5]);
        gStarPropertySlots.mpBegin[6].release();
        pManager->GetProperty(0x4c66e1ee, 0x74d2735b, &gStarPropertySlots.mpBegin[6]);
    }
    if (!gDefaultStarProperty.mpObject)
        pManager->GetProperty(0x1106d054, 0x2ae0c7e, &gDefaultStarProperty);
}

// ---- 00c86390: per-body visual update ----------------------------------------------------------
struct cSPMatrix3 { void Assign(const void* pSource); };          // 0x0041cb40
class cViewer
{
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    void GetCameraLocationInfo(cSPVector3* pos, void*, void*, void*);   // 0x007c3d30
};
void* __cdecl SP_App();                                            // 0x0067dd10
void* __cdecl SP_App_GetViewer(void* pApp);                        // SP::App vtable +0x50
void* __cdecl SP_LivingUniverse_Context();                         // 0x01021080
void* __cdecl FUN_01021260();                                      // 0x01021260
float __cdecl FUN_01034630(int a, float b, int c);                 // 0x01034630
void __cdecl UpdateCometVisuals(void* pSystem, float value);       // 0x00c85380

// cCelestialBody::SetBrightness (0x00bd6590); the +0xc0 helper (an orbit) has a 3-float colour
// and a matrix sink, +0xc4 an interactable effect.
struct cBodyVisual
{
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual bool IsVisible();                                      // +0x10
    virtual void SetColor(const void* pColor);                     // +0x18
    virtual void SetMatrix(const cSPMatrix3* pMatrix);             // +0x20
};

struct cBodyEffect
{
    void SetEffect(float size, const cSPVector3* pPosition);       // 0x00c3f160
};

extern float gBodyColorR, gBodyColorG, gBodyColorB;                // 0x01694c94/98/9c
extern cSPMatrix3 gBodyOrientation;                                // 0x01694c70
extern const float kOne;                                           // 0x01485720

// @ 0x00c86390
void cSolarSystem::UpdateBodies(float value)
{
    AutoRefCount<cCelestialBody>* it = mCelestialBodies.mpBegin;
    AutoRefCount<cCelestialBody>* end = mCelestialBodies.mpEnd;
    if (it != end) {
        do {
            cCelestialBody* pBody = it->mpObject;
            pBody->SetBrightness(value);

            float bright = kOne;
            if (pBody->mType == 0) {
                cSPVector3 cameraPos;
                if (SP_LivingUniverse_Context() == (void*)1) {
                    void* pApp = SP_App();
                    cViewer* pViewer = (cViewer*)SP_App_GetViewer(pApp);
                    pViewer->GetCameraLocationInfo(&cameraPos, 0, 0, 0);
                } else {
                    cSPVector3* pPos = (cSPVector3*)FUN_01021260();
                    cameraPos = *pPos;
                }
                float dx = cameraPos.x - pBody->mPosition.x;
                float dy = cameraPos.y - pBody->mPosition.y;
                float dz = cameraPos.z - pBody->mPosition.z;
                bright = FUN_01034630(3, sqrtf(dx * dx + dy * dy + dz * dz), 0);
            }

            cBodyVisual* pVisual = pBody->mpVisual;
            if (pVisual && pVisual->IsVisible()) {
                struct { uint16_t flags; uint16_t index; float r, g, b; float alpha; } color;
                color.flags = 0;
                color.index = 0;
                color.r = gBodyColorR;
                color.g = gBodyColorG;
                color.b = gBodyColorB;
                color.alpha = kOne;

                cSPMatrix3 matrix;
                matrix.Assign(&gBodyOrientation);
                pVisual->SetMatrix(&matrix);
                ++color.index;
                color.alpha = bright;
                pVisual->SetColor(&color);
            }

            cBodyEffect* pEffect = pBody->mpEffect;
            if (pEffect)
                pEffect->SetEffect(pBody->mHitSphereSize * bright, &pBody->mPosition);

            ++it;
        } while (it != end);
    }
    UpdateCometVisuals(this, value);
}

// ---- 00c86760: initialise the system for one star ---------------------------------------------
float __cdecl GetStarRadius(int type);                             // 0x00c84120
void  __cdecl InitStarBodyHelper(void* pSystem);                   // 0x00c85540
void  __cdecl FUN_00c70f90(void* pObject, int value);              // 0x00c70f90
cPlanet* __cdecl FUN_00bab900(cPlanet** slot, cPlanet** value);    // 0x00bab900

extern cSPVector3 gSunPosition;                                    // 0x01694c10/14/18

// @ 0x00c86760
void cSolarSystem::InitStar(cStar* pStar)
{
    mpStar = pStar;
    if (pStar->IsKnown()) {
        InitStarBodyHelper(this);
    } else {
        if (!mStarBody.mpObject) {
            cCelestialBody* pRaw = new("Simulator/cCelestialBody", 0, 0, 0, 0) cCelestialBody(0);
            mStarBody = pRaw;
            mCelestialBodies.push_back(AutoRefCount<cCelestialBody>(pRaw));
        }
        cCelestialBody* pBody = mStarBody.mpObject;
        pBody->mOrbit.mNullOrbit = true;
        pBody->mPosition = gSunPosition;
        pBody->mRotationRate = GetStarRotationRate(pStar->GetType());
        pBody->mName.assign(*pStar->GetName());
        pBody->mHitSphereSize = GetStarRadius(pStar->GetType());
    }

    if (pStar->HasComets())
        InitComets();

    int type = pStar->GetType();
    if (gStarCache[type] < 0.0f)
        gStarCache[type] = IsGasType(type) ? GetGasValue(type) : GetStarRadius(type);
    float hiRadius = gStarCache[type] + GetStarTemperature(type) * 85.0f;

    type = pStar->GetType();
    if (gStarCache[type] < 0.0f)
        gStarCache[type] = IsGasType(type) ? GetGasValue(type) : GetStarRadius(type);
    float loRadius = gStarCache[type] + GetStarTemperature(type) * 15.0f;

    cPlanetVector* pPlanets = cStarManager_planets(pStar->mpPlanetManager);
    const int numPlanets = (int)(pPlanets->mpEnd - pPlanets->mpBegin);
    for (int i = 0; i < numPlanets; ++i) {
        cPlanet* pPlanet = 0;
        cStarManager* pManager = SP_StarManager(&pPlanets->mpBegin[i], &pPlanet);
        pManager->GetOrActivatePlanet();

        if (pPlanet) {
            mPlanets.push_back(AutoRefCount<cPlanet>(pPlanet));
        }

        float size = pPlanet ? pPlanet->GetValue(1) : 0.0f;
        if (size > loRadius && !(pPlanet->m_flags & 1))
            pPlanet->m_flags |= 0x1000;
        if (size > hiRadius && !(pPlanet->m_flags & 1))
            pPlanet->m_flags |= 0x2000;

        if (pPlanet)
            pPlanet->Release();
    }
}
