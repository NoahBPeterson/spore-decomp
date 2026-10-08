// Slice s00af7c60: 0x00af7c60, SweepSphereVsTerrain.
//
// Sweeps a sphere (radius `radius`) from `pos` along `dir` for up to *dist, against the static
// objects found by the object manager along that capsule.  Each object has a type (+0x88, 0..4)
// and the caller's `mask` skips whole categories.  A candidate is tested as a bounding sphere
// first; if the caller asked for a refined test (`refine`) and the object has a collision mesh
// (type 3 with a mesh, or type 4 whose owner property 0x3EB2E21 says so) the mesh sweep
// (SweepSphereVsMesh, 0x00af5400) decides, otherwise the sphere hit is final.  Every accepted hit
// shortens *dist and is copied into `result`.  Returns true if anything was hit.
//
// Module flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast (no /EHsc: no SEH frame although the
// object list has a destructor).
#include "types.h"
#include <math.h>

struct Vector3 { float x, y, z; };

extern Vector3 gInvalidVec;   // 0x0167ae24 sentinel vector
extern const float kZero;     // 0x01485378 (0.0f, loaded from memory by the original)

// cSPTransform head (0x38 bytes); copy-ctor is out of line (0x0040CE80)
struct Transform {
    uint16_t mFlags;        // +0x00
    uint16_t mChangeCount;  // +0x02
    Vector3  mOffset;       // +0x04
    float    mScale;        // +0x10
    uint32_t pad14[(0x38 - 0x14) / 4];

    Transform(const Transform& other);                 // 0x0040CE80
    void SetScale(float scale) { mScale = scale; mChangeCount++; }
    void SetOffset(const Vector3& offset) { mOffset = offset; mFlags |= 4; mChangeCount++; }
};

Vector3* normalized_safe(Vector3* out, const Vector3* v);   // 0x00449c20 (cdecl)

struct IProps;
bool GetBoolProperty(IProps* props, uint32_t id, bool* out);  // 0x00407190 (cdecl)

void  operator delete[](void* p);                            // 0x00F47380

// Result record (0xF0 bytes) shared by the sweep functions (cSweepResult in slice s00c2b170).
struct cSweepResult {
    uint32_t mNounID;         // +0x00
    void*    mpObject;        // +0x04
    float    mSpeedFactor;    // +0x08
    int      mbHeadOn;        // +0x0c
    uint32_t pad10[4];        // +0x10
    void*    mpHitObject;     // +0x20
    uint32_t pad24;           // +0x24
    Vector3  mHitCenter;      // +0x28
    Vector3  mHitNormal;      // +0x34
    bool     mbFlag;          // +0x40
    uint8_t  pad41[3];
    float    mDist;           // +0x44
    Vector3  mHitPos;         // +0x48
    float    mRadius;         // +0x54
    uint32_t pad58[(0xF0 - 0x58) / 4];

    cSweepResult();                                // 0x00af4da0
    void Copy(const cSweepResult* src);            // 0x00af1910
};

// collision mesh (see slice s00c2b170)
struct cCollisionMesh {
    uint32_t pad00[0x3c / 4];
    float    mRadius;             // +0x3c
    Vector3  mCenter;             // +0x40
    Vector3* mpTrisBegin;         // +0x4c
    Vector3* mpTrisEnd;           // +0x50
    uint32_t GetNumVertices() const { return (uint32_t)(mpTrisEnd - mpTrisBegin); }
};

struct cOwnerObj { uint8_t pad[0x90]; IProps* mpProps; };   // +0x90 property list

// static world object
struct cSpatialObject {
    uint8_t   pad00[0x34];
    uint32_t  mFlags;       // +0x34
    Vector3   mCenter;      // +0x38
    float     mRadius;      // +0x44
    uint8_t   pad48[0x6c - 0x48];
    void*     mpMeshOwner;  // +0x6c
    cOwnerObj* mpOwner;     // +0x70
    uint8_t   pad74[0x88 - 0x74];
    int       mType;        // +0x88

    Transform* GetTransform();   // 0x00b73e70
};

// Fixed buffer of 64 object pointers; destructor frees the heap block if it grew.
struct ObjectList {
    cSpatialObject** mpBegin;
    cSpatialObject** mpEnd;
    cSpatialObject** mpCapacity;
    uint32_t         mAllocatorName;
    cSpatialObject** mpPoolBegin;
    int              mOverflow;
    cSpatialObject*  mBuffer[64];

    ObjectList()
    {
        mpBegin = mBuffer;
        mpEnd = mBuffer;
        mpCapacity = mBuffer + 64;
        mOverflow = 0;
    }
    ~ObjectList()
    {
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            operator delete[](mpBegin);
    }
    int size() const { return (int)(mpEnd - mpBegin); }
    cSpatialObject*& operator[](int i) { return mpBegin[i]; }
};

struct cObjectManager {
    // objects whose bounds touch the capsule start..end
    int GetObjectsInCapsule(const Vector3* start, const Vector3* end, float radius, ObjectList* out, int flags); // 0x00b7a4a0
    cCollisionMesh* GetCollisionMesh(cSpatialObject* obj);                                                       // 0x00b7c480
};
cObjectManager* ObjectManager();   // 0x00b3d3c0

// ray versus sphere: t in [0,1] along `dirScaled` (length^2 = lenSq)
bool RaySphere(const Vector3* origin, const Vector3* dirScaled, float lenSq, const Vector3* center,
               float radius, float* t);                                          // 0x00af16f0

bool SweepSphereVsMesh(cSweepResult* result, void* owner, const Vector3* pos, const Vector3* center,
                       Vector3* endPos, const Vector3* dir, float* dist, float scale,
                       Transform* xf, const Vector3* meshCenter, float meshRadius,
                       Vector3* tris, uint32_t numVerts, float radius, int flags,
                       cSweepResult* result2);                                    // 0x00af5400

// @ 0x00af7c60
bool SweepSphereVsTerrain(const Vector3* pos, const Vector3* dir, float radius, float scale,
                          uint32_t mask, bool refine, cSweepResult* result, float* dist)
{
    if (*dist < 1.5258789e-05f || mask == 0xFFFFFFFF)
        return false;

    bool bHit = false;
    cObjectManager* mgr = ObjectManager();
    cSweepResult hit;

    float ox = pos->x, oy = pos->y, oz = pos->z;
    float f = *dist;
    ObjectList list;
    float originLen = sqrtf(pos->x * pos->x + (pos->y * pos->y + pos->z * pos->z));
    Vector3 endPos;
    endPos.x = ox + f * dir->x;
    endPos.y = oy + f * dir->y;
    endPos.z = oz + f * dir->z;
    Vector3 end;
    end.x = pos->x + f * dir->x;
    end.y = pos->y + f * dir->y;
    end.z = pos->z + f * dir->z;
    int count = mgr->GetObjectsInCapsule(pos, &end, radius, &list, 0);

    for (int i = 0; i < count; i++) {
        cSpatialObject* obj = list[i];
        switch (obj->mType) {
        case 0:
            if (mask & 4) continue;
            break;
        case 1:
            if (mask & 2) continue;
            break;
        case 2:
            if (mask & 1) continue;
            break;
        case 3:
            if ((mask & 8) || (obj->mFlags & 1)) continue;
            break;
        case 4:
            if (mask & 8) continue;
            break;
        default:
            continue;
        }

        float objRadius = obj->mRadius;
        float s = *dist;
        float dx = dir->x, dy = dir->y, dz = dir->z;
        Vector3 dirScaled;
        dirScaled.x = dx * s;
        dirScaled.y = dy * s;
        dirScaled.z = dz * s;
        float t;
        if (!RaySphere(pos, &dirScaled, s * s, &obj->mCenter, objRadius + radius, &t) || t == kZero)
            continue;

        float d = (t * s) * scale;
        end.x = dx * d + pos->x;
        end.y = pos->y + dy * d;
        end.z = pos->z + dz * d;

        hit.mNounID = 0; hit.mpObject = 0; hit.mSpeedFactor = 0; hit.mbHeadOn = 0;
        hit.pad10[0] = 0; hit.pad10[1] = 0; hit.pad10[2] = 0; hit.pad10[3] = 0;
        hit.mpHitObject = obj;
        hit.pad24 = 0;
        hit.mHitCenter = obj->mCenter;
        hit.mHitNormal = gInvalidVec;
        hit.mbFlag = false;
        hit.mHitPos = end;
        hit.mRadius = objRadius + radius;

        bool big = objRadius > 10.0f || obj->mType == 4;
        bool useMesh = false;
        if (refine) {
            if (obj->mType == 3 && obj->mpMeshOwner != 0) {
                useMesh = true;
            } else if (obj->mType == 4 && obj->mpOwner != 0 &&
                       GetBoolProperty(obj->mpOwner->mpProps, 0x3EB2E21, &big) && big) {
                useMesh = true;
            }
        }

        if (!useMesh) {
            *dist = d;
            result->Copy(&hit);
        } else {
            cCollisionMesh* mesh = mgr->GetCollisionMesh(obj);
            if (mesh == 0) {
                *dist = d;
                result->Copy(&hit);
            } else {
                Transform xf(*obj->GetTransform());
                xf.SetScale(1.0f);
                Vector3 tmp;
                Vector3* n = normalized_safe(&tmp, &obj->mCenter);
                Vector3 center;
                center.y = n->y * originLen;
                center.x = n->x * originLen;
                center.z = n->z * originLen;
                xf.SetOffset(center);
                if (!SweepSphereVsMesh(result, obj, pos, &center, &endPos, dir, dist, scale, &xf,
                                       &mesh->mCenter, mesh->mRadius, mesh->mpTrisBegin,
                                       mesh->GetNumVertices(), radius, 0, 0))
                    continue;
            }
        }

        bHit = true;
        float cur = *dist;
        if (cur < 1.5258789e-05f)
            return true;
        endPos.x = pos->x + cur * dir->x;
        endPos.y = pos->y + cur * dir->y;
        endPos.z = pos->z + cur * dir->z;
    }
    return bHit;
}
