// Slice s00c85a30: SP::cSolarSystem::InitComets (random comet generation for a solar system).
// Flags /O2 /MD /Gy /TP /arch:SSE /fp:fast (fsin/fcos inlined, SSE float math, no EH frame).
#include "types.h"
#include <math.h>

typedef unsigned int size_t;
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);  // 0x00f473a0
inline void* operator new(size_t, void* p) { return p; }

// ---- RNG and shared constants -------------------------------------------------------------------
namespace EA { namespace Random {
struct RandomLinearCongruential {
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
    void assign(const wchar_t* p)
    {
        const wchar_t* e = p;
        while (*e) ++e;
        assign(p, p + (e - p));
    }
};

// ---- objects -------------------------------------------------------------------------------------
struct cCelestialBody;
template <typename T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p) : mpObject(p) { mpObject->AddRef(); }
    AutoRefCount(const AutoRefCount& o) : mpObject(o.mpObject) { mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
};

struct cEllipticalOrbit {
    bool  mNullOrbit;                                            // +0x00
    float mPlaneNormal[3];                                       // +0x04
    float mEccentricity;                                         // +0x10
    float mPerihelion[3];                                        // +0x14
    float mPeriod;                                               // +0x20
    char  pad[0x78 - 0x24];
    void  Update();                                              // 0x00fe8450
};

struct cCelestialBody {
    virtual int AddRef();
    virtual int Release();
    char             pad0[0x34 - 4];
    int              mType;                                      // +0x34
    cEllipticalOrbit mOrbit;                                     // +0x38
    WString          mName;                                      // +0xb0 (0x38+0x78)
    char             pad1[0xc8 - 0xc0];
    float            mHitSphereSize;                             // +0xc8
    cCelestialBody(int type);                                    // 0x00bd6410
    void Setup();                                                // 0x00bd6300
};

struct cStar { int GetType(); };                                 // 0x00c8b550

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

struct cSolarSystem {
    char    pad0[0xc];
    cStar*  mpStar;                                              // +0x0c
    char    pad1[0x24 - 0x10];
    vector<AutoRefCount<cCelestialBody> > mCelestialBodies;      // +0x24
    void InitComets();
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
