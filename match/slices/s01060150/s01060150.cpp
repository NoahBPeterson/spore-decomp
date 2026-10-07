// Slice s01060150 (batch op3_big) — 0x01060150, 3217 bytes.
//
// SP::cUFOLocomotion::ResolvePlanetaryCollisions(cSpaceToolUFO* pUFO, float)  (__thiscall, ret 8)
//
// The name comes from the dev PDB.  The UFO / tribe / city classes are declared with the retail
// offsets this function uses; callees without a recovered name keep their FUN_ address names.
// The second (float) argument is unused by the retail code.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (SSE scalar math, x87 sqrt and float returns;
// a fixed-capacity vector local with a dtor but no EH frame -> no /EHsc).

#include "types.h"

#pragma pack(push, 8)

extern "C" double __cdecl sqrt(double);
extern "C" double __cdecl fabs(double);
#pragma intrinsic(sqrt, fabs)
inline float sqrtf(float x) { return (float)sqrt((double)x); }
inline float fabsf(float x) { return (float)fabs((double)x); }

void __cdecl operator delete[](void* p);                             // 0x00f47380

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    Vector3& operator=(const Vector3& v) { x = v.x; y = v.y; z = v.z; return *this; }
    Vector3 operator+(const Vector3& b) const { return Vector3(x + b.x, y + b.y, z + b.z); }
    Vector3 operator-(const Vector3& b) const { return Vector3(x - b.x, y - b.y, z - b.z); }
    Vector3 operator*(float f) const { return Vector3(x * f, y * f, z * f); }
    Vector3 operator-() const { return Vector3(-x, -y, -z); }
    bool operator==(const Vector3& b) const { return x == b.x && y == b.y && z == b.z; }
    bool operator!=(const Vector3& b) const { return x != b.x || y != b.y || z != b.z; }
    float Dot(const Vector3& b) const { return x * b.x + y * b.y + z * b.z; }
    float SquaredLength() const { return x * x + y * y + z * z; }
    float Length() const { return sqrtf(x * x + y * y + z * z); }
    Vector3 Normalized() const { float inv = 1.0f / Length(); return Vector3(x * inv, y * inv, z * inv); }
};
extern const Vector3 kZeroVector;                                    // 0x016e2114

// Fixed-capacity vector with inline storage (heap-flag word right before the buffer).
template <class T, int N> struct fixed_vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mPad0c[2];
    uint32_t mnHeapFlag;
    T mBuffer[N];
    fixed_vector() : mpBegin(mBuffer), mpEnd(mBuffer), mpCapacity(mBuffer + N), mnHeapFlag(0) {}
    ~fixed_vector() { if (mpBegin && ((uint32_t*)mpBegin)[-1]) operator delete[](mpBegin); }
    T* begin() const { return mpBegin; }
    T* end() const { return mpEnd; }
};

template <class T> struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    T* begin() const { return mpBegin; }
    T* end() const { return mpEnd; }
};

namespace SP {

// Spatial-object interface embedded in game objects (GetPosition at +0x2c).
class cSpatialObject {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20(); virtual void _v24(); virtual void _v28();
    virtual const Vector3& GetPosition();                            // +0x2c
    virtual void _v30(); virtual void _v34(); virtual void _v38(); virtual void _v3c();
    virtual void _v40(); virtual void _v44(); virtual void _v48(); virtual void _v4c();
    virtual void _v50(); virtual void _v54(); virtual void _v58(); virtual void _v5c();
    virtual void _v60(); virtual void _v64();
    virtual const struct cBoundingInfo* GetBoundingInfo();           // +0x68
};
struct cBoundingInfo {
    uint32_t pad[0x14 / 4];
    float mfRadius;                             // +0x14
};

// Objects returned by the spatial query (flag byte at +0x34).
struct cQueryObject {
    uint32_t pad[0x34 / 4];
    uint8_t mFlags;                             // +0x34
};

class cMotionController {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14();
    virtual void Apply(float value, int a, int b, const Vector3* pDir, int c);  // +0x18
};

class cSpaceToolUFO {
public:
    uint32_t pad00[0x34 / 4];
    cSpatialObject mSpatial;                    // +0x34
    uint32_t pad38[(0x508 - 0x38) / 4];
    cMotionController mMotion;                  // +0x508
    uint32_t pad50c[(0x718 - 0x50c) / 4];
    Vector3 mPosition;                          // +0x718
    float GetRadius();                                               // 0x00c3be10
};

// Building / member objects tested against the UFO (state flags at +0x84 or +0xc0).
struct cBuilding {
    uint32_t pad00[0x34 / 4];
    cSpatialObject mSpatial;                    // +0x34
    uint32_t pad38[(0x84 - 0x38) / 4];
    uint32_t mFlags;                            // +0x84
    uint32_t pad88[(0x258 - 0x88) / 4];
    float mfInnerRadius;                        // +0x258
    float mfOuterRadius;                        // +0x25c
    bool IsActive() const { return !(mFlags & 0x10) || (mFlags & 0x20); }
};
struct cHandheldItem {
    uint32_t pad00[0x70 / 4];
    cSpatialObject mSpatial;                    // +0x70
    uint32_t pad74[(0xc0 - 0x74) / 4];
    uint32_t mFlags;                            // +0xc0
    bool IsActive() const { return !(mFlags & 0x10) || (mFlags & 0x20); }
};

class cCommunity {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2c();
    virtual void _v30(); virtual void _v34(); virtual void _v38(); virtual void _v3c();
    virtual void _v40(); virtual void _v44(); virtual void _v48(); virtual void _v4c();
    virtual void _v50(); virtual void _v54(); virtual void _v58(); virtual void _v5c();
    virtual void _v60(); virtual void _v64(); virtual void _v68();
    virtual cBuilding* GetTribeHut();                                // +0x6c
    virtual void _v70(); virtual void _v74(); virtual void _v78(); virtual void _v7c();
    virtual void _v80(); virtual void _v84(); virtual void _v88(); virtual void _v8c();
    virtual void _v90(); virtual void _v94(); virtual void _v98(); virtual void _v9c();
    virtual void _va0(); virtual void _va4(); virtual void _va8();
    virtual cBuilding* GetCityHall();                                // +0xac
    virtual void _vb0(); virtual void _vb4(); virtual void _vb8();
    virtual const vector<cBuilding*>* GetBuildings();                // +0xbc

    uint32_t pad04[(0x120 - 0x4) / 4];
    cSpatialObject mSpatial;                    // +0x120

    const vector<cBuilding*>* GetMembers();                          // 0x00c8e810
    const vector<cHandheldItem*>* FUN_00bd8130();                    // 0x00bd8130
};

struct cGameDataVector {
    void** mpBegin;
    void** mpEnd;
    void** begin() const { return mpBegin; }
    void** end() const { return mpEnd; }
};
struct cGameDataList {
    uint32_t pad00;
    cGameDataVector mData;                      // +0x4
};
typedef void (*tGameDataFn)();
class cGameNounManager {
public:
    cGameDataList* GetGameDataVector(tGameDataFn a, tGameDataFn b, tGameDataFn c, tGameDataFn d,
                                     const void* pType);             // 0x00b21340
};
cGameNounManager* NounManager();                                     // 0x00b3d300
void FUN_00cd7d10(); void FUN_00d3d420(); void FUN_00b1e500();       // GameData template helpers
void FUN_00ad48b0(); void FUN_00accbb0(); void FUN_00acdff0(); void FUN_00ae72d0();
extern const char g_18ebadc[];                                       // 0x018ebadc (UFO type)
extern const char g_18c6d19[];                                       // 0x018c6d19 (city type)
extern const char g_18c43e8[];                                       // 0x018c43e8 (tribe type)
extern const char g_18c6de8[];                                       // 0x018c6de8

class cPlanetModel {
public:
    float GetRadiusAt(const Vector3& pos);                           // 0x00b7ef70
    Vector3 RayCast(const Vector3& origin, const Vector3& dir);      // 0x00b82060
    Vector3 GetNormal(const Vector3& pos);                           // 0x00b7e3b0
    Vector3 ProjectToSurface(const Vector3& pos);                    // 0x00b81630
};
cPlanetModel* PlanetModel();                                         // 0x00b3d350

class cUFOTuning {
public:
    float GetMinAltitude();                                          // 0x00fb7ba0
    float GetBounceStrength();                                       // 0x0097ef00
};
cUFOTuning* FUN_00c37360();                                          // 0x00c37360

class cSpatialIndex {
public:
    void FindObjects(const Vector3& pos, float radius, int flags,
                     fixed_vector<cQueryObject*, 256>& results);     // 0x00b7a1d0
};
cSpatialIndex* FUN_00b3d3c0();                                       // 0x00b3d3c0

struct cTribeTuning {
    uint32_t pad[2];
    float mfRadius;                             // +0x8
};
cTribeTuning* FUN_00bcebc0();                                        // 0x00bcebc0

class cPlanetRecord {
public:
    int GetTechLevel();                                              // 0x00b8dab0
};
class cSPLivingUniverse {
public:
    static cPlanetRecord* GetActivePlanetRecord();                   // 0x010212a0
};

class cPropertyList {
public:
    bool GetBool(uint32_t id);                                       // 0x006a25a0
};
extern cPropertyList* sAppProperties;                                // 0x015fd918

class cUFOLocomotion {
public:
    void ResolvePlanetaryCollisions(cSpaceToolUFO* pUFO, float dt);
    void ApplyPush(cSpaceToolUFO* pUFO, const Vector3& push, const Vector3& dir, int reason);  // 0x0105c9d0
    void CollideWithObject(cSpaceToolUFO* pUFO, cQueryObject* pObject);                      // 0x0105dc60
    void CollideWithSpatial(cSpaceToolUFO* pUFO, cSpatialObject* pObject, int reason);      // 0x0105d790
};

static const float kMinPushLengthSq = 1.5258789e-05f;               // 0x0149bfc0
static const float kMaxDistance = 3.402823466e+38F;                    // 0x0149bfbc

void cUFOLocomotion::ResolvePlanetaryCollisions(cSpaceToolUFO* pUFO, float)
{
    cPlanetModel* pPlanetModel = PlanetModel();
    Vector3& pos = pUFO->mPosition;
    float planetRadius = pPlanetModel->GetRadiusAt(pos);
    float minAltitude = FUN_00c37360()->GetMinAltitude();
    float ufoRadius = pUFO->GetRadius();

    if (pos.Length() <= ufoRadius + planetRadius) {
        Vector3 center = pUFO->mSpatial.GetPosition();
        Vector3 up = pos.Normalized();
        Vector3 toUFO = pos - center;
        Vector3 pushDir;
        float lenSq = toUFO.SquaredLength();
        if (lenSq > kMinPushLengthSq)
            pushDir = toUFO * (1.0f / sqrtf(lenSq));
        else
            pushDir = -up;
        Vector3 dir = pushDir;
        Vector3 origin = center - up * ufoRadius - dir * (ufoRadius * 2.0f);
        Vector3 hit = PlanetModel()->RayCast(origin, dir);
        if (hit != kZeroVector) {
            Vector3 normal = PlanetModel()->GetNormal(hit);
            ApplyPush(pUFO, kZeroVector, normal, 1);
            pos = normal * ufoRadius + hit;
            pUFO->mMotion.Apply(FUN_00c37360()->GetBounceStrength(), 0, 8, &dir, 0);
        } else {
            Vector3 offset = pos.Normalized() * ufoRadius;
            pos = PlanetModel()->ProjectToSurface(pos) + offset;
        }
    }

    fixed_vector<cQueryObject*, 256> objects;
    FUN_00b3d3c0()->FindObjects(pos, ufoRadius, 0x19, objects);
    for (cQueryObject** it = objects.begin(); it != objects.end(); ++it) {
        if (!((*it)->mFlags & 1))
            CollideWithObject(pUFO, *it);
    }

    if (sAppProperties->GetBool(0x149a7260)) {
        const cGameDataVector& ufos = NounManager()->GetGameDataVector(
            FUN_00cd7d10, FUN_00d3d420, FUN_00ad48b0, FUN_00b1e500, g_18ebadc)->mData;
        for (void** it = ufos.begin(); it != ufos.end(); ++it) {
            cSpaceToolUFO* pOther = (cSpaceToolUFO*)*it;
            if (pOther == pUFO)
                continue;
            float dist = (pos - pOther->mSpatial.GetPosition()).Length();
            float minDist = pOther->GetRadius() + ufoRadius;
            if (dist < minDist) {
                float depth = minDist - dist;
                Vector3 away = pos - pOther->mSpatial.GetPosition();
                ApplyPush(pUFO, away * depth, away, 10);
            }
        }
    }

    int techLevel = cSPLivingUniverse::GetActivePlanetRecord()->GetTechLevel();
    if (techLevel >= 2) {
        float range = ufoRadius + 10.0f;
        if (minAltitude < range && pos.Length() - planetRadius < range) {
            float bestDistSq = kMaxDistance;
            cCommunity* pClosest = 0;
            const cGameDataVector& cities = NounManager()->GetGameDataVector(
                FUN_00cd7d10, FUN_00d3d420, FUN_00accbb0, FUN_00b1e500, g_18c6d19)->mData;
            for (void** it = cities.begin(); it != cities.end(); ++it) {
                cCommunity* pCity = (cCommunity*)*it;
                float distSq = (pCity->mSpatial.GetPosition() - pos).SquaredLength();
                if (distSq < bestDistSq) {
                    bestDistSq = distSq;
                    pClosest = pCity;
                }
            }
            if (pClosest) {
                cBuilding* pHall = pClosest->GetCityHall();
                if (pHall->IsActive())
                    CollideWithSpatial(pUFO, &pHall->mSpatial, 4);
                const vector<cBuilding*>* pBuildings = pClosest->GetBuildings();
                for (cBuilding** it = pBuildings->begin(); it != pBuildings->end(); ++it) {
                    if ((*it)->IsActive())
                        CollideWithSpatial(pUFO, &(*it)->mSpatial, 5);
                }
            }
        }
    }

    if (techLevel >= 3) {
        float range = FUN_00bcebc0()->mfRadius + ufoRadius;
        if (minAltitude < range && pos.Length() - planetRadius < range) {
            float bestDistSq = kMaxDistance;
            cCommunity* pClosest = 0;
            const cGameDataVector& tribes = NounManager()->GetGameDataVector(
                FUN_00cd7d10, FUN_00d3d420, FUN_00acdff0, FUN_00b1e500, g_18c43e8)->mData;
            for (void** it = tribes.begin(); it != tribes.end(); ++it) {
                cCommunity* pTribe = (cCommunity*)*it;
                float distSq = (pTribe->mSpatial.GetPosition() - pos).SquaredLength();
                if (distSq < bestDistSq) {
                    bestDistSq = distSq;
                    pClosest = pTribe;
                }
            }
            if (pClosest) {
                cBuilding* pHut = pClosest->GetTribeHut();
                if (pHut->IsActive()) {
                    float hutHeight = pHut->mSpatial.GetBoundingInfo()->mfRadius;
                    float altitude = pos.Length() - planetRadius;
                    if (altitude < hutHeight) {
                        float innerRadius = pHut->mfInnerRadius;
                        float outerRadius = pHut->mfOuterRadius;
                        float midRadius = (outerRadius + innerRadius) * 0.5f;
                        const Vector3& tribePos = pClosest->mSpatial.GetPosition();
                        Vector3 tribeUp = pClosest->mSpatial.GetPosition().Normalized();
                        Vector3 offset = pos - tribePos;
                        Vector3 radial = offset - tribeUp * offset.Dot(tribeUp);
                        float radialLenSq = radial.SquaredLength();
                        float radialLen = sqrtf(radialLenSq);
                        if (fabsf(radialLen - midRadius) < (outerRadius - midRadius) + ufoRadius) {
                            bool bOutside;
                            float sideDepth;
                            if (radialLen > midRadius) {
                                bOutside = true;
                                sideDepth = outerRadius - radialLen;
                            } else {
                                bOutside = false;
                                sideDepth = radialLen - innerRadius;
                            }
                            float topDepth = hutHeight - altitude;
                            if (sideDepth > topDepth) {
                                Vector3 up = pos.Normalized();
                                ApplyPush(pUFO, up * topDepth, up, 6);
                            } else {
                                Vector3 side = radial * (1.0f / sqrtf(radialLenSq + 1e-08f));
                                if (!bOutside)
                                    side = -side;
                                ApplyPush(pUFO, side * sideDepth, side, 6);
                            }
                        }
                    }
                }
                const vector<cBuilding*>* pMembers = pClosest->GetMembers();
                for (cBuilding** it = pMembers->begin(); it != pMembers->end(); ++it) {
                    if ((*it)->IsActive())
                        CollideWithSpatial(pUFO, &(*it)->mSpatial, 7);
                }
                const vector<cHandheldItem*>* pItems = pClosest->FUN_00bd8130();
                for (cHandheldItem** it = pItems->begin(); it != pItems->end(); ++it) {
                    if ((*it)->IsActive())
                        CollideWithSpatial(pUFO, &(*it)->mSpatial, 8);
                }
            }
        }

        if (sAppProperties->GetBool(0x149a7260)) {
            const cGameDataVector& items = NounManager()->GetGameDataVector(
                FUN_00cd7d10, FUN_00d3d420, FUN_00ae72d0, FUN_00b1e500, g_18c6de8)->mData;
            for (void** it = items.begin(); it != items.end(); ++it) {
                cBuilding* pItem = (cBuilding*)*it;
                if (pItem->IsActive())
                    CollideWithSpatial(pUFO, &pItem->mSpatial, 9);
            }
        }
    }
}

}  // namespace SP

#pragma pack(pop)
