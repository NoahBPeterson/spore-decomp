// Slice s00c2b170: creature locomotion obstacle sweep callback (0x00c2b170, 5689 bytes).
// /O2 /arch:SSE module (movss/comiss scalar math, x87 for sqrt and float returns).
//
// __cdecl float CreatureObstacleSweep(ctx, pos, dir, dist, result)
// Passed by address (push 0xc2b170) from 0x00c2c9fa and 0x00c2ccd3 as a sweep callback.
// It sweeps the creature (radius ctx->mRadius) from `pos` along `dir` for `dist`, asks the
// Gonzago model world for the models along that capsule, classifies each owning game object
// by noun ID (rocks, plants, huts, nests, eggs, ornaments, buildings, other creatures, ...),
// and clips `dist` against every blocking one (sphere sweeps, per-triangle mesh sweeps for
// solid props and buildings, and a time-of-closest-approach test against moving creatures).
// After the object loop it also clips against terrain, water and (in space) the planet.
// Returns the clipped distance; `result` receives the blocking object and its data.
#include "types.h"
#include <math.h>

struct Vector3 { float x, y, z; };

// ---------------------------------------------------------------- noun IDs
enum {
    kGameSpace           = 0x01654c05,
    kScenarioMode        = 0x01654c10,
    kGameBundle          = 0x018c431c,
    kCityWalls           = 0x018c7c97,
    kGamePlant           = 0x018c84a9,
    kOrnament            = 0x018c88e4,
    kTribeTool           = 0x018c8f0c,
    kCreatureAnimal      = 0x018eb45e,
    kCreatureCitizen     = 0x018eb4b7,
    kTribeHut            = 0x01e4daae,
    kEgg                 = 0x02a034cd,
    kRock                = 0x02a8fb3f,
    kFruit               = 0x02c9cc91,
    kHitSphere           = 0x02e72cae,
    kInteractiveOrnament = 0x03a2511e,
    kTotemPole           = 0x055cf865,
    kTribeFoodMat        = 0x0629bafe,
    kBuildingScenario    = 0x070703b3,
    kPlaceableSound      = 0x074e0069,
    kPlaceableEffect     = 0x07b38ba7,
    kNest                = 0x52aa6122,
    kGameDataType        = 0x017f243b,   // cGameData::TYPE
    kSpatialObjectType   = 0x01186577,   // cSpatialObject::TYPE
};

// ---------------------------------------------------------------- engine types
struct BoundingBox { Vector3 mMin; Vector3 mMax; };
struct Transform { uint32_t data[0x38 / 4]; Transform(); };            // ctor 0x00409930

class cSpatialObject {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual uint32_t GetNounID();                                        // 0x20
    virtual void v24(); virtual void v28();
    virtual const Vector3& GetPosition();                                // 0x2c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44();
    virtual bool IsLocomotionEnabled();                                  // 0x48
    virtual void v4c(); virtual void v50(); virtual void v54();
    virtual bool IsMoving();                                             // 0x58
    virtual void v5c(); virtual void v60(); virtual void v64();
    virtual const BoundingBox& GetBoundingBox();                         // 0x68
    virtual void v6c();
    virtual float GetScale();                                            // 0x70
    virtual float GetBoundingRadius();                                   // 0x74
    virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8();
    virtual uint32_t GetModelKeyInstance();                              // 0xac
    virtual uint32_t GetModelKeyGroup();                                 // 0xb0
    virtual void vb4();
    virtual class cGameData* CastGameData(uint32_t type);                // 0xb8
    virtual void vbc(); virtual void vc0(); virtual void vc4();
    virtual float GetMaxSpeed();                                         // 0xc8

    void LocalToWorldTransform(Transform& dst);                          // 0x00c897e0

    uint32_t pad04[(0x50 - 0x04) / 4];
    uint32_t mFlags;              // +0x50 (0x190: hidden/destroyed/ghost)
    uint32_t pad54[(0x70 - 0x54) / 4];
    bool     mbCollidable;        // +0x70
    bool     mbIsStatic;          // +0x71
    uint8_t  pad72[3];
    bool     mbIsInWorld;         // +0x75
};

class cGameData {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual uint32_t GetNounID();                                        // 0x20
};

struct cLocomotionGoal {
    struct Waypoint { Vector3 mPos; uint32_t pad[(0x3c - 0xc) / 4]; };
    Waypoint* mpWaypoints;        // +0x00
    uint32_t  pad04[(0x14 - 0x04) / 4];
    Vector3   mTarget;            // +0x14
    uint32_t  pad20[(0x5c - 0x20) / 4];
    int       mGoalType;          // +0x5c (0 = none)
    uint32_t  GetNumWaypoints();                                         // 0x00ac15f0
};

class cLocomotiveObject : public cSpatialObject {
public:
    const Vector3& GetVelocity();                                        // 0x00d20610
    bool IsNearGoal();                                                   // 0x00c42e20
    cLocomotionGoal* GetGoal();                                          // 0x00c41ec0
};

class cRider {
public:
    virtual void v00(); virtual void v04();
    virtual cSpatialObject* GetObject();                                 // 0x08
};

class cCreatureBase {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual uint32_t GetNounID();                                        // 0x20

    int    GetAvoidanceLevel();                                          // 0x00c0c2f0
    cRider* GetRider();                                                  // 0x00c0ee60
    bool   IsPlayerControlled();                                         // 0x00c0c0e0

    uint32_t pad04[(0xc0 - 0x04) / 4];
    cLocomotiveObject mLocomotion;                                       // +0x0c0
    uint32_t padc4[(0x110 - 0xc4) / 4];
    uint32_t mFlags110;                                                  // +0x110
    uint8_t  pad114[0x137 - 0x114];
    bool     mbCheckTerrain;                                             // +0x137
    uint8_t  pad138[0xb20 - 0x138];
    void*    mpTribe;                                                    // +0xb20
    uint8_t  padb24[0xb58 - 0xb24];
    uint8_t  mFlagsB58;                                                  // +0xb58 (0x20 = small)
    uint8_t  padb59[0xb5e - 0xb59];
    bool     mbB5E;                                                      // +0xb5e
    uint8_t  padb5f[0xf90 - 0xb5f];
    bool     mbAlwaysAvoid;                                              // +0xf90
};

struct cOwner {
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual cSpatialObject* Cast(uint32_t type);                         // 0x0c
};

struct cModel {
    uint32_t pad00;
    uint32_t mFlags;              // +0x04 (bit 14: collidable)
    uint32_t pad08[(0x64 - 0x08) / 4];
    cOwner*  mpOwner;             // +0x64
};

// collision mesh as stored in a scenario building's model list (element size 0xc64)
struct cCollisionMesh {
    uint32_t pad00[0x3c / 4];
    float    mRadius;             // +0x3c
    Vector3  mCenter;             // +0x40
    Vector3* mpTrisBegin;         // +0x4c (eastl::vector<Vector3>)
    Vector3* mpTrisEnd;           // +0x50
    uint32_t pad54[(0xc64 - 0x54) / 4];
    uint32_t GetNumVertices() const { return (uint32_t)(mpTrisEnd - mpTrisBegin); }
};
struct cCollisionMeshList {
    cCollisionMesh* mpBegin;
    cCollisionMesh* mpEnd;
    int size() const { return (int)(mpEnd - mpBegin); }
};

struct cMeshManager { cCollisionMesh* GetCollisionMesh(uint32_t instance, uint32_t group); }; // 0x00b7c360
cMeshManager* MeshManager();                                                                   // 0x00b3d3c0
struct cPlanetModel { bool IsUnderWater(const Vector3& pos); };                                // 0x00b7e3e0
cPlanetModel* PlanetModel();                                                                   // 0x00b3d350
struct cTerrainInfo { uint32_t pad[0x20 / 4]; int mWaterMode; };                               // +0x20
cTerrainInfo* TerrainInfo();                                                                   // 0x00b3d310
uint32_t GetCurrentGameMode();                                                                 // 0x00b5b800

struct ModelResult { cModel* mpModel; void* mpData; };
struct ModelFilter { uint32_t a, b, c, d, e; bool f, g; };

// static local eastl::fixed_vector<ModelResult, 16>
struct ModelResultVector {
    ModelResult* mpBegin;
    ModelResult* mpEnd;
    ModelResult* mpCapacity;
    uint32_t     mAllocatorName;
    ModelResult* mpPoolBegin;
    uint32_t     mOverflow;
    ModelResult  mBuffer[16];

    ModelResultVector()
    {
        mpPoolBegin = mBuffer;
        mpBegin = mpEnd = mBuffer;
        mpCapacity = mBuffer + 16;
    }
    ~ModelResultVector();
    ModelResult* erase(ModelResult* first, ModelResult* last);          // 0x00d018d0
    void clear() { erase(mpBegin, mpEnd); }
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    ModelResult& operator[](uint32_t i) { return mpBegin[i]; }
};

class cGonzagoModelWorld {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void GetModelsAlongCapsule(const Vector3& start, const Vector3& end,
                                       ModelResultVector& dst, ModelFilter& filter, float radius); // 0x30
};
cGonzagoModelWorld* GonzagoModelWorld();                                // 0x00b3d520

// game objects reached through the noun cast helper
struct cOrnament        { uint8_t pad[0x38]; int mType; uint8_t pad3c[0x228 - 0x3c]; int mKind; };
struct cEgg             { uint8_t pad[0x1f4]; struct cEggOwner* mpOwner; };
struct cEggOwner        { uint8_t pad[0xa4]; void* mpTribe; };
struct cNest            { void* GetTribe(); };                           // 0x00c6aa30
struct cInteractiveOrnament { uint8_t pad[0x108]; cCreatureBase* mpUser; };
struct cFoodMatState    { int IsEmpty(); };                              // 0x00c90460
struct cTribeFoodMat    { uint8_t pad[0x34]; cSpatialObject mSpatial; uint8_t padx[0x10c - 0x34 - sizeof(cSpatialObject)]; cFoodMatState* mpState; };
struct cBuilding        { cCollisionMeshList* GetCollisionMeshes(); };   // 0x00bd6180
struct cCreatureGroup   { void* pad; cCreatureBase* mpLeader; };

void*           GameDataCast(cGameData* obj, uint32_t noun);             // 0x00ac80d0
cCreatureBase*  GameDataToCreature(cGameData* obj);                      // 0x00f19200
cBuilding*      GameDataToBuilding(cGameData* obj);                      // 0x00c0c340
cCreatureGroup* GetCreatureGroup(cCreatureBase* creature);               // 0x00c2b110
bool            IsPointInSweepIgnoreZone(void* zone, const Vector3* pos);// 0x0041dd30

Vector3 normalized_safe(const Vector3& v);                               // 0x00449c20
float   Dot3(const Vector3& a, const Vector3& b);                        // 0x00455cc0
// time of closest approach of two moving spheres, and their distance at that time
float   TimeOfClosestApproach(const Vector3* posA, const Vector3* velA,
                              const Vector3* posB, const Vector3* velB); // 0x00c297d0
float   DistanceAtTime(const Vector3* posA, const Vector3* velA,
                       const Vector3* posB, const Vector3* velB, float t); // 0x00c29880

struct cSweepResult {
    uint32_t mNounID;             // +0x00
    cGameData* mpObject;          // +0x04
    float    mSpeedFactor;        // +0x08
    int      mbHeadOn;            // +0x0c
    uint32_t pad10[4];
    uint32_t mHitKind;            // +0x20
    uint32_t pad24[4];
    Vector3  mVelocity;           // +0x34
};

struct cSweepContext {
    cCreatureBase* mpCreature;    // +0x00
    uint32_t mIgnoreZone[6];      // +0x04
    float    mRadius;             // +0x1c
    bool     mbIgnoreObjects;     // +0x20
};

bool SweepSphereVsMesh(cSweepResult* result, void* owner, const Vector3* pos, const Vector3* center,
                       Vector3* endPos, const Vector3* dir, float* dist, float scale,
                       Transform* xf, const Vector3* meshCenter, float meshRadius,
                       Vector3* tris, uint32_t numVerts, float radius, int flags,
                       cSweepResult* result2);                                    // 0x00af5400
bool SweepSphereVsSphere(cSweepResult* result, cGameData* obj, const Vector3* pos,
                         const Vector3* center, const Vector3* dir, float* dist, float scale,
                         float radius, bool bDynamic, cSweepResult* result2);     // 0x00af17f0
void SweepSphereVsTerrain(const Vector3* pos, const Vector3* dir, float radius, float scale,
                          int flags, int mode, cSweepResult* result, float* dist); // 0x00af7c60
void SweepSphereVsWater(const Vector3* pos, const Vector3* dir, float radius, float scale,
                        float maxSlope, float height, cSweepResult* result, float* dist,
                        bool bUnderWater);                                         // 0x00af3e50
void SweepSphereVsPlanet(const Vector3* pos, const Vector3* dir, float scale,
                         cSweepResult* result, float* dist);                       // 0x00af82e0

extern float kNestAvoidRadius;            // 0x01582e94 (50.0)

// @ 0x00c2b170
float CreatureObstacleSweep(cSweepContext* ctx, const Vector3* pos, const Vector3* dir,
                            float dist, cSweepResult* result)
{
    cCreatureBase* creature = ctx->mpCreature;
    result->mHitKind = 0;
    if (dist < 1.5258789e-05f)
        return dist;

    if (GetCurrentGameMode() != kScenarioMode)
    {
        int level = creature->GetAvoidanceLevel();
        if (level == 0 && !creature->mLocomotion.IsMoving())
            return dist;
        if (!creature->mbAlwaysAvoid && level < 2)
            return dist;
    }

    cCreatureBase* animal = 0;
    if (creature && creature->GetNounID() == kCreatureAnimal)
        animal = creature;
    if (creature)
        creature->GetNounID();          // unused cast

    cRider* rider = creature->GetRider();
    cSpatialObject* riderObject = rider ? rider->GetObject() : 0;

    cLocomotiveObject* loco = &creature->mLocomotion;
    loco->GetVelocity();

    float radius = ctx->mRadius;
    Vector3 endPos;
    endPos.x = dir->x * dist + pos->x;
    endPos.y = pos->y + dir->y * dist;
    endPos.z = pos->z + dir->z * dist;
    float distSq = dist * dist;
    bool bIgnoreObjects = ctx->mbIgnoreObjects;
    Vector3 hitPos = endPos;
    float curDist = dist;

    bool bPlayer = creature->IsPlayerControlled();
    void* tribe = creature->mpTribe;
    float maxSpeed = loco->GetMaxSpeed();
    Vector3 velocity;
    velocity.x = dir->x * maxSpeed;
    velocity.y = dir->y * maxSpeed;
    velocity.z = dir->z * maxSpeed;
    Vector3 ourVelocity = velocity;

    PlanetModel();
    static ModelResultVector sModels;
    static uint32_t sNumModels;
    static Vector3 sNoVelocity;
    sModels.clear();

    ModelFilter filter;
    filter.a = 0; filter.b = 0; filter.c = 0; filter.d = 0; filter.e = 0;
    filter.f = false; filter.g = false;

    cGonzagoModelWorld* world = GonzagoModelWorld();
    Vector3 segEnd;
    if (dist > 100.0f) {
        segEnd.x = dir->x * 100.0f + pos->x;
        segEnd.y = pos->y + dir->y * 100.0f;
        segEnd.z = pos->z + dir->z * 100.0f;
    } else {
        segEnd = endPos;
    }
    Vector3 queryEnd = segEnd;
    world->GetModelsAlongCapsule(*pos, queryEnd, sModels, filter, radius);

    sNumModels = sModels.size();
    for (uint32_t i = 0; i < sNumModels; i++)
    {
        cModel* model = sModels[i].mpModel;
        if (((model->mFlags >> 14) & 1) == 0)
            continue;
        if (model->mpOwner == 0)
            continue;
        cOwner* owner = model->mpOwner;
        if (!owner)
            continue;
        cSpatialObject* obj = owner->Cast(kSpatialObjectType);
        if (!obj || !obj->mbCollidable || !obj->mbIsInWorld || (obj->mFlags & 0x190))
            continue;

        bool bDynamic = !obj->mbIsStatic;
        bool bUseMesh = false;
        float radiusScale = 1.0f;
        const Vector3* objPos = &obj->GetPosition();
        Vector3 hitVelocity = sNoVelocity;
        cGameData* gameObj = obj->CastGameData(kGameDataType);
        uint32_t noun = gameObj->GetNounID();
        float overrideRadius;
        Vector3 predicted;

        switch (noun)
        {
        case kRock:
            if (!obj->mbIsStatic) {
                if (obj->GetBoundingRadius() <= 0.3f)
                    continue;
                radiusScale = 0.5f;
            }
            goto use_bounds;

        case kTribeTool:
            bUseMesh = true;
            goto use_bounds;

        case kGamePlant:
        case kGameBundle:
        case kCityWalls:
        case kFruit:
        case kHitSphere:
        case kPlaceableEffect:
        case kPlaceableSound:
            continue;

        case kOrnament:
        {
            cOrnament* ornament = (cOrnament*)GameDataCast(gameObj, noun);
            if (ornament->mKind == 1) {
                if (ornament->mType == 0xb || ornament->mType == 0xf)
                    goto use_bounds;
                continue;
            }
            if (ornament->mKind != 0x5d97f762)
                continue;
            bUseMesh = true;
            goto use_bounds;
        }

        case kTribeHut:
        {
            float dx = endPos.x - objPos->x;
            float dy = endPos.y - objPos->y;
            float dz = endPos.z - objPos->z;
            if (1.5258789e-05f > dz * dz + dy * dy + dx * dx)
                continue;
            bUseMesh = true;
            goto use_bounds;
        }

        case kEgg:
        {
            if (bIgnoreObjects || bPlayer)
                continue;
            cEgg* egg = (cEgg*)GameDataCast(gameObj, noun);
            if (egg->mpOwner && egg->mpOwner->mpTribe == tribe) {
                radiusScale = 2.0f;
                goto use_bounds;
            }
            overrideRadius = kNestAvoidRadius;
            goto use_override;
        }

        case kInteractiveOrnament:
        {
            if (bPlayer) {
                if (GetCurrentGameMode() != kScenarioMode)
                    continue;
                float ourScale = creature->mLocomotion.GetScale();
                if (ourScale / obj->GetScale() <= 0.1f)
                    continue;
            }
            if (!obj->mbIsStatic)
                continue;
            cInteractiveOrnament* orn = (cInteractiveOrnament*)GameDataCast(gameObj, kInteractiveOrnament);
            if (orn && orn->mpUser == creature)
                continue;
            bUseMesh = true;
            goto use_bounds;
        }

        case kTotemPole:
            bUseMesh = true;
            goto use_bounds;

        case kTribeFoodMat:
        {
            cTribeFoodMat* mat = (cTribeFoodMat*)GameDataCast(gameObj, kTribeFoodMat);
            if (mat->mpState->IsEmpty() != 0)
                goto use_bounds;
            cSpatialObject* matSpatial = &mat->mSpatial;
            float matRadius = matSpatial->GetBoundingRadius();
            const Vector3& matPos = matSpatial->GetPosition();
            float dx = endPos.x - matPos.x;
            float dy = endPos.y - matPos.y;
            float dz = endPos.z - matPos.z;
            if (matRadius * matRadius > dz * dz + dy * dy + dx * dx)
                continue;
            overrideRadius = matRadius;
            goto use_override;
        }

        case kNest:
        {
            if (bIgnoreObjects || bPlayer)
                continue;
            cNest* nest = (cNest*)GameDataCast(gameObj, noun);
            if (nest->GetTribe() == tribe)
                continue;
            float dx = endPos.x - objPos->x;
            float dy = endPos.y - objPos->y;
            float dz = endPos.z - objPos->z;
            float r = kNestAvoidRadius + radius;
            if (r * r > dz * dz + dy * dy + dx * dx)
                continue;
            if (!animal)
                goto use_bounds;
            overrideRadius = kNestAvoidRadius;
            goto use_override;
        }

        case kBuildingScenario:
        {
            if (creature->IsPlayerControlled()) {
                bUseMesh = true;
                goto use_bounds;
            }
            cBuilding* building = GameDataToBuilding(gameObj);
            if (!building)
                goto use_bounds;
            cCollisionMeshList* meshes = building->GetCollisionMeshes();
            int numMeshes = meshes->size();
            Transform xf;
            obj->LocalToWorldTransform(xf);
            for (int m = 0; m < numMeshes; m++)
            {
                cCollisionMesh* mesh = &meshes->mpBegin[m];
                if (SweepSphereVsMesh(result, mesh, pos, &mesh->mCenter, &hitPos, dir, &curDist, 1.0f,
                                      &xf, &mesh->mCenter, mesh->mRadius, mesh->mpTrisBegin,
                                      mesh->GetNumVertices(), radius, 0, result))
                {
                    result->mVelocity = hitVelocity;
                    result->mNounID = 0;
                    if (1.5258789e-05f > curDist) {
                        curDist = 0.0f;
                        distSq = 0.0f;
                        goto use_bounds;
                    }
                    distSq = curDist * curDist;
                    hitPos.x = pos->x + dir->x * curDist;
                    hitPos.y = pos->y + dir->y * curDist;
                    hitPos.z = pos->z + dir->z * curDist;
                }
            }
            if (1.5258789e-05f > curDist)
                goto use_bounds;
            continue;
        }

        case kCreatureAnimal:
        case kCreatureCitizen:
        {
            if (obj == &creature->mLocomotion || obj == riderObject)
                continue;
            cCreatureBase* other = GameDataToCreature(gameObj);
            if (bPlayer || other->mbB5E) {
                if (!other->IsPlayerControlled())
                    continue;
            }
            if (IsPointInSweepIgnoreZone(ctx->mIgnoreZone, pos)) {
                if (other->mLocomotion.GetGoal()->mGoalType != 0)
                    continue;
            }

            // only creatures ahead of us
            if (0.0f >= (objPos->x - pos->x) * dir->x + dir->z * (objPos->z - pos->z)
                        + dir->y * (objPos->y - pos->y))
                continue;

            float otherRadius = obj->GetBoundingRadius();
            radiusScale = 0.9f;
            if (creature->GetNounID() == kCreatureAnimal && noun == kCreatureAnimal)
                radiusScale = 0.5f;
            if (other->mFlagsB58 & 0x20)
                radiusScale = 0.5f;
            float ourScale = (creature->mFlagsB58 & 0x20) ? 0.5f : 1.0f;
            float combined = otherRadius * radiusScale + ourScale * radius;

            // ray vs. sphere over [0, dist]
            Vector3 v;
            v.x = dir->x * curDist;
            v.y = dir->y * curDist;
            v.z = dir->z * curDist;
            float rx = pos->x - objPos->x;
            float ry = pos->y - objPos->y;
            float rz = pos->z - objPos->z;
            float b = rz * v.z + ry * v.y + rx * v.x;
            float c = rz * rz + ry * ry + rx * rx - combined * combined;
            float disc = b * b - c * distSq;
            float t;
            if (!(0.0f > c))
            {
                if (0.0f > disc)
                    continue;
                float root = sqrtf(disc);
                if (0.0f > root - b)
                    continue;
                if (-b - root > distSq)
                    continue;
            }

            float slowTime = 0.0f;
            switch (other->GetAvoidanceLevel()) {
            case 0: slowTime = 4.0f; break;
            case 1: slowTime = 2.0f; break;
            case 2: slowTime = 1.0f; break;
            }

            cLocomotiveObject* otherLoco = &other->mLocomotion;
            Vector3 otherVel = otherLoco->GetVelocity();
            t = TimeOfClosestApproach(pos, &ourVelocity, objPos, &otherVel);
            if (1.5258789e-05f >= t)
                continue;
            if (t > 4.0f)
                continue;
            if (t > slowTime) {
                if (otherVel.z * otherVel.z + otherVel.y * otherVel.y + otherVel.x * otherVel.x > 1.5258789e-05f)
                    continue;
            }
            if (DistanceAtTime(pos, &ourVelocity, objPos, &otherVel, t) > combined)
                continue;
            if (GetCreatureGroup(other)->mpLeader == creature)
                continue;

            bool bOtherMoving =
                otherVel.z * otherVel.z + otherVel.y * otherVel.y + otherVel.x * otherVel.x > 1.5258789e-05f;
            bool bSameWay = false;
            if (bOtherMoving && Dot3(normalized_safe(otherVel), *dir) > 0.7f) {
                bSameWay = true;
            }
            else
            {
                bSameWay = false;
                cLocomotionGoal* goal = otherLoco->GetGoal();
                if (goal->mGoalType == 0 || otherLoco->IsNearGoal())
                    goto predict;

                // heading toward the first few waypoints
                Vector3 objPosCopy = *objPos;
                Vector3 heading;
                heading.x = goal->mTarget.x - objPosCopy.x;
                heading.y = goal->mTarget.y - objPosCopy.y;
                heading.z = goal->mTarget.z - objPosCopy.z;
                const uint32_t kMaxWaypoints = 3;
                uint32_t numWaypoints = goal->GetNumWaypoints();
                uint32_t n = (kMaxWaypoints < numWaypoints) ? kMaxWaypoints : numWaypoints;
                const cLocomotionGoal::Waypoint* wp = goal->mpWaypoints;
                for (; n != 0; n--, wp++) {
                    heading.x = wp->mPos.x - objPosCopy.x + heading.x;
                    heading.y = wp->mPos.y - objPosCopy.y + heading.y;
                    heading.z = wp->mPos.z - objPosCopy.z + heading.z;
                }
                heading = normalized_safe(heading);
                if (!(heading.x * dir->x + heading.z * dir->z + heading.y * dir->y > 0.7f))
                    goto predict;
                if (!bOtherMoving) {
                    float otherSpeed = otherLoco->GetMaxSpeed();
                    otherVel.x = heading.x * otherSpeed;
                    otherVel.y = heading.y * otherSpeed;
                    otherVel.z = heading.z * otherSpeed;
                }
            }

            {
                // would slowing down to 50% / 10% avoid the collision?
                float speedFactors[2];
                speedFactors[0] = 0.5f;
                speedFactors[1] = 0.1f;
                for (int k = 0; k < 2; k++)
                {
                    float f = speedFactors[k];
                    Vector3 slowVel;
                    slowVel.x = velocity.x * f;
                    slowVel.y = velocity.y * f;
                    slowVel.z = velocity.z * f;
                    float t2 = TimeOfClosestApproach(pos, &slowVel, objPos, &otherVel);
                    if (1.5258789e-05f >= t2 || t2 > 4.0f || t2 > slowTime
                        || DistanceAtTime(pos, &slowVel, objPos, &otherVel, t2) > combined)
                    {
                        result->mpObject = gameObj;
                        result->mSpeedFactor = f;
                        result->mbHeadOn = !bSameWay;
                        goto next;
                    }
                }
            }

        predict:
            {
                // treat the other creature as a sphere at its predicted position; the
                // radius override is the closest-approach time (as in the original)
                Vector3 n = normalized_safe(otherVel);
                predicted.x = objPos->x + n.x * t;
                predicted.y = objPos->y + n.y * t;
                predicted.z = objPos->z + n.z * t;
                hitVelocity = otherVel;
                objPos = &predicted;
                overrideRadius = t;
                goto use_override;
            }
        }

        default:
            goto use_bounds;
        }

    use_override:
        if (overrideRadius != 0.0f)
            goto have_radius;
    use_bounds:
        overrideRadius = obj->GetBoundingRadius();
    have_radius:
        {
            float scaledRadius = overrideRadius * radiusScale;
            float sweepRadius = scaledRadius + radius;
            bool bHit;
            if (bUseMesh && obj->mbIsStatic)
            {
                Transform xf;
                obj->LocalToWorldTransform(xf);
                cCollisionMesh* mesh = MeshManager()->GetCollisionMesh(obj->GetModelKeyInstance(),
                                                                       obj->GetModelKeyGroup());
                if (!mesh)
                    continue;
                if (mesh->GetNumVertices() < 3)
                    continue;
                bHit = SweepSphereVsMesh(result, gameObj, pos, objPos, &hitPos, dir, &curDist, 1.0f,
                                         &xf, &mesh->mCenter, scaledRadius, mesh->mpTrisBegin,
                                         mesh->GetNumVertices(), radius, 0, result);
            }
            else
            {
                bHit = SweepSphereVsSphere(result, gameObj, pos, objPos, dir, &curDist, 1.0f,
                                           sweepRadius, bDynamic, result);
            }
            if (!bHit)
                continue;
            result->mNounID = noun;
            result->mVelocity = hitVelocity;
            if (1.5258789e-05f > curDist) {
                curDist = 0.0f;
                goto done;
            }
            distSq = curDist * curDist;
            hitPos.x = pos->x + dir->x * curDist;
            hitPos.y = pos->y + dir->y * curDist;
            hitPos.z = pos->z + dir->z * curDist;
        }
    next:
        ;
    }
done:

    // terrain
    int terrainFlags = 0;
    if (!loco->IsLocomotionEnabled())
        terrainFlags = 7;
    else if (bPlayer) {
        uint32_t mode = GetCurrentGameMode();
        terrainFlags = (mode == 0x01654c04 || mode == kGameSpace) ? 7 : 1;
    }
    if (curDist > 0.25f)
        SweepSphereVsTerrain(pos, dir, radius, 1.0f, terrainFlags, 1, result, &curDist);

    // water
    if (creature->mbCheckTerrain && !(creature->mFlags110 & 0x1000))
    {
        const BoundingBox& box = loco->GetBoundingBox();
        float height = box.mMax.z - box.mMin.z;
        if (bPlayer && rider)
        {
            const Vector3& riderPos = rider->GetObject()->GetPosition();
            float dx = riderPos.x - pos->x;
            float dy = riderPos.y - pos->y;
            float dz = riderPos.z - pos->z;
            height += sqrtf(dz * dz + dy * dy + dx * dx);
        }
        float depthScale = (TerrainInfo()->mWaterMode == 0) ? 1.0f : 10.0f;
        bool bUnderWater = PlanetModel()->IsUnderWater(hitPos);
        if (curDist > 0.25f)
            SweepSphereVsWater(pos, dir, radius, 2.0f, 45.0f, depthScale + height, result, &curDist,
                               bUnderWater);
    }

    // planet surface (space stage)
    if (bIgnoreObjects && GetCurrentGameMode() == kGameSpace && curDist > 0.25f)
        SweepSphereVsPlanet(pos, dir, 1.0f, result, &curDist);

    return curDist;
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
