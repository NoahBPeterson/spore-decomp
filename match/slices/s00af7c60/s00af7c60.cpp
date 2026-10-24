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

// ---------------------------------------------------------------------------
// Surface-contact helpers (0x00af82e0 .. 0x00af8a10)
//
// The planet code keeps one proxy per tracked object: the proxy caches the
// surface point a sphere touch query landed on (0x00af8540), mirrors itself
// to a Havok entity listener (0x00af8840), and rebuilds itself from a contact
// record (0x00af8a10).  The queries themselves live in the surface collision
// module at 0x00b65xxx/0x00b66xxx.

struct __declspec(align(16)) Vector4 { float x, y, z, w; };

struct hkTransform { uint32_t mData[0x40 / 4]; };

// hkVector4 with the one transform helper the proxy uses.
struct hkVector4 : Vector4 {
    void setTransformedInversePos(const hkTransform* xf, const Vector4* pos);   // 0x010813d0
};

class D961;   // entity tracked by a proxy (also an hkEntity)

// 0x30-byte record used both as a surface-query result and as the proxy's
// "source" description (0x00af8a10 fills one and feeds it to 0x00af8920).
struct cContactRecord {
    uint32_t  mType;        // +0x00  source type, or the query's hit flag
    uint32_t  pad04[3];     // +0x04
    Vector4   mPoint;       // +0x10  hit point / source point
    Vector4*  mpPoint;      // +0x20  point storage (query result array)
    uint32_t  pad24;        // +0x24
    void*     mpOwner;      // +0x28
    D961*     mpEntity;     // +0x2c
};

// 0x20-byte input of the swept query (0x00af8a10).
struct SweepInput {
    Vector4 m_vec00;        // +0x00
    float   mRadius;        // +0x10
    float   m_f14;          // +0x14
    uint32_t pad18[2];      // +0x18
};

// Object with a vtable that hands out the entity behind a property id.
struct cContactOwner {
    void** mpVtbl;                                 // +0x00
    uint32_t pad04[3];                             // +0x04
    void* GetEntity(uint32_t id);                  // vtable slot 3
};

// Source object released by 0x00af84f0.
struct cProxySource {
    uint32_t mField0;       // +0x00
    uint32_t mField4;       // +0x04
    uint32_t mCount8;       // +0x08
};

// Holder reached through entity+0x58; the transform sits at +0x10.
struct cEntityHolder {
    uint32_t    pad00[4];   // +0x00
    hkTransform mTransform; // +0x10
};

// Entity behind a contact record (mangled as D961 in the retail PDB because
// it is one of Havok's SPM-side subclasses).
class D961 {
public:
    uint32_t  pad00[3];     // +0x00
    void*     mpField0c;    // +0x0c
    uint32_t  pad10[(0x58 - 0x10) / 4];
    cEntityHolder* mpHolder58;   // +0x58

    int* Find(int* out, int value);              // 0x00496140
    void AddEntityListener(void* listener);           // 0x01088c20
    void RemoveEntityListener(void* listener);        // 0x01088a20
};

// Surface queries (planet collision module).
void SurfaceHitQuery(const Vector4* pos, void* surface, cContactRecord* out);             // 0x00b665c0
void SurfaceRayQuery(const Vector4* from, void* surface, int kind, cContactRecord* out);  // 0x00b66ed0
void SurfaceSweepQuery(SweepInput* in, void* surface, void* shape, void* ctx, bool local,
                       cContactRecord* out, int zero);                                    // 0x00b669b0
Vector4* DirectionToPoint(Vector4* out, const Vector4* dir);                              // 0x00b65710

extern const float kContactEps;        // 0x0145c3e4 (== the sweep epsilon)
extern const float kDirectionEps;      // 0x013f11c8 (squared-length epsilon)
extern const float kDefaultPointX;     // 0x016e42d0
extern const float kDefaultPointY;     // 0x016e42d4
extern const float kDefaultPointZ;     // 0x016e42d8
extern const float kDefaultPointW;     // 0x016e42dc

// Proxy tracked by the planet surface code.
class cContactProxy {
public:
    void**    mpVtbl;         // +0x00
    uint32_t  pad04[3];       // +0x04
    Vector4   m_vec10;        // +0x10  current surface direction
    uint32_t  pad20[(0x48 - 0x20) / 4];
    uint8_t   m_b48;          // +0x48
    uint8_t   pad49[3];
    uint32_t  m_type4c;       // +0x4c
    Vector4   m_vec50;        // +0x50  closest surface point
    void*     m_listenerVtbl; // +0x60  embedded hkEntityListener
    uint32_t  pad64;
    D961*     mpEntity;       // +0x68
    hkVector4 m_vec70;        // +0x70  world position
    hkVector4 m_vec80;        // +0x80  local position
    uint32_t  pad90[(0x9c - 0x90) / 4];
    void*     mpCtx9c;        // +0x9c
    uint32_t  padA0[(0xa8 - 0xa0) / 4];
    float     m_fA8;          // +0xa8
    float     m_fAC;          // +0xac
    void*     mpB0;           // +0xb0
    void*     mpB4;           // +0xb4

    void  ReleaseSource(cProxySource* src);                              // 0x00af84f0
    void  UpdateClosestPoint();                                          // 0x00af8540
    void  SetEntity(void* owner, D961* entity, const Vector4* pos);       // 0x00af8840
    void  SetFromSource(cContactRecord* src);                            // 0x00af8920
    void  Update(bool useLocal, float extra);                            // 0x00af8a10
};

// Game-data view used by the noun sweep: the tracked object hangs off the
// noun's game data at +0x324 and exposes its position through the transform
// embedded at +0x34.
struct cGameDataTransform {
    void** mpVtbl;                             // +0x00
    const Vector3* GetPosition();              // vtable slot 0x2c/4
};
struct cGameDataObject {
    uint32_t pad00[0x34 / 4];
    cGameDataTransform mTransform;             // +0x34
    uint32_t pad38[(0x25c - 0x38) / 4];
    float    mRadius;                          // +0x25c
};
struct cNounGameData {
    uint32_t pad00[0x324 / 4];
    cGameDataObject* mpObject;                 // +0x324
};
struct cGameDataArray {
    uint32_t mCount;                           // +0x00
    void*    mpBegin;                          // +0x04
};
struct cGameNounManager {
    cGameDataArray* GetGameDataVector(void* f1, void* f2, void* f3, void* f4, void* f5);  // 0x00b21340
};
cGameNounManager* NounManager();                                            // 0x00b3d300
void* FindNounGameData(void* list, const Vector3* pos, int flag);           // 0x00ac9310

// @ 0x00af82e0
bool SweepSphereVsNoun(const Vector3* pos, const Vector3* dir, float scale,
                       cSweepResult* result, float* dist)
{
    if (*dist < 1.5258789e-05f)
        return false;

    bool bHit = false;
    cGameNounManager* mgr = NounManager();
    cGameDataArray* vec = mgr->GetGameDataVector((void*)0x00cd7d10, (void*)0x00d3d420,
                                                (void*)0x00acdff0, (void*)0x00b1e500,
                                                (void*)0x018c43e8);
    int flag = 0;
    cNounGameData* data = (cNounGameData*)FindNounGameData(&vec->mpBegin, pos, flag);
    if (data != 0)
    {
        cGameDataObject* obj = data->mpObject;
        cGameDataTransform* xf = &obj->mTransform;
        const Vector3* center =
            ((const Vector3* (__thiscall*)(cGameDataTransform*))xf->mpVtbl[0x2c / 4])(xf);
        float radius = obj->mRadius;

        Vector3 dirScaled;
        dirScaled.x = dir->x * *dist;
        dirScaled.y = dir->y * *dist;
        dirScaled.z = dir->z * *dist;

        float t;
        if (RaySphere(pos, &dirScaled, *dist * *dist, center, radius, &t) && t != 0.0f)
        {
            *dist = (*dist * t) * scale;

            result->mHitCenter = *center;
            result->mpHitObject = obj;
            result->pad24 = 0;
            result->mbFlag = false;
            result->mHitPos.x = pos->x + dir->x * *dist;
            result->mHitPos.y = pos->y + dir->y * *dist;
            result->mHitPos.z = pos->z + dir->z * *dist;
            result->mRadius = radius;
            result->mHitNormal = gInvalidVec;
            result->mNounID = 0;
            result->mpObject = 0;
            result->mSpeedFactor = 0;
            result->mbHeadOn = 0;
            result->pad10[0] = 0;
            result->pad10[1] = 0;
            result->pad10[2] = 0;
            result->pad10[3] = 0;
            bHit = true;
        }
    }
    return bHit;
}

// @ 0x00af84f0
void cContactProxy::ReleaseSource(cProxySource* src)
{
    if (src->mCount8 != 0)
    {
        ((void (__thiscall*)(void*, cProxySource*))mpVtbl[2])(this, src);
        ((void (__thiscall*)(void*, cProxySource*))mpVtbl[1])(this, src);
    }
}

// @ 0x00af8540
void cContactProxy::UpdateClosestPoint()
{
    Vector4* vec = &m_vec10;
    cContactRecord res;
    res.mpPoint = 0;
    res.pad24 = 0;
    res.mpOwner = 0;
    res.mpEntity = 0;

    SurfaceHitQuery(vec, mpB4, &res);
    if (res.mType != 0)
    {
        float resLenSq = res.mPoint.z * res.mPoint.z + res.mPoint.y * res.mPoint.y +
                         res.mPoint.x * res.mPoint.x;
        float curLenSq = vec->x * vec->x + vec->y * vec->y + vec->z * vec->z;
        if (resLenSq > curLenSq)
        {
            vec->x = res.mPoint.x;
            vec->y = res.mPoint.y;
            vec->z = res.mPoint.z;
            vec->w = res.mPoint.w;
        }
    }
}

// @ 0x00af8600
void ProjectBehindPlane(const Vector4* plane, const Vector4* p, Vector4* out)
{
    Vector4 v = *p;
    (void)v;
    float az = plane->z;
    float ay = plane->y;
    float ax = plane->x;
    float yz = ay * p->y + az * p->z;
    float dot = yz + ax * p->x;
    if (dot < 0.0f)
    {
        dot = -dot;
        float sx = ax * dot;
        float sy = ay * dot;
        float sz = az * dot;
        float sw = plane->w * dot;
        out->x = p->x + sx;
        out->y = p->y + sy;
        out->z = p->z + sz;
        out->w = p->w + sw;
    }
    else
    {
        out->w = 0.0f;
        out->z = 0.0f;
        out->y = 0.0f;
        out->x = 0.0f;
    }
}

// @ 0x00af86c0
void ProjectRayToSurface(const Vector4* from, const Vector4* to, void* surface, Vector4* out)
{
    Vector4 fromCopy;
    fromCopy.x = from->x;
    fromCopy.y = from->y;
    fromCopy.z = from->z;
    fromCopy.w = from->w;

    Vector4 dir;
    dir.x = to->x - from->x;
    dir.y = to->y - from->y;
    dir.z = to->z - from->z;
    dir.w = to->w - from->w;

    float lenSq = dir.x * dir.x + dir.y * dir.y + dir.z * dir.z;
    if (lenSq > 1.0e-06f)
    {
        float len = sqrtf(lenSq);
        float inv = 1.0f / len;
        dir.x *= inv;
        dir.y *= inv;
        dir.z *= inv;
        dir.w *= inv;

        cContactRecord res;
        res.mpPoint = 0;
        res.pad24 = 0;
        res.mpOwner = 0;
        res.mpEntity = 0;
        SurfaceRayQuery(&fromCopy, surface, 6, &res);
        if (res.mType != 0)
        {
            out->x = res.mPoint.x;
            out->y = res.mPoint.y;
            out->z = res.mPoint.z;
            out->w = res.mPoint.w;
            return;
        }
    }
    out->x = to->x;
    out->y = to->y;
    out->z = to->z;
    out->w = to->w;
}

// @ 0x00af8840
void cContactProxy::SetEntity(void* owner, D961* entity, const Vector4* pos)
{
    D961* old = mpEntity;
    if (old != entity)
    {
        if (old != 0)
        {
            int buf[2];
            int* found = old->Find(buf, 0);
            if (*found == 3)
            {
                cContactOwner* holder = (cContactOwner*)old->mpField0c;
                void* obj = holder != 0
                    ? ((void* (__thiscall*)(cContactOwner*, uint32_t))holder->mpVtbl[3])(
                          holder, 0x01186577)
                    : 0;
                ((void (__thiscall*)(void*, void*))(*(void***)obj)[2])(obj, this);
            }
            mpEntity->RemoveEntityListener(&m_listenerVtbl);
        }
        mpEntity = entity;
        if (entity != 0)
        {
            m_type4c = 3;
            entity->AddEntityListener(&m_listenerVtbl);
            ((void (__thiscall*)(void*, void*))(*(void***)owner)[1])(owner, this);
        }
    }

    if (mpEntity != 0)
    {
        m_vec70.setTransformedInversePos(&mpEntity->mpHolder58->mTransform, pos);
        return;
    }
    m_vec80.w = 0.0f;
    m_vec80.z = 0.0f;
    m_vec80.y = 0.0f;
    m_vec80.x = 0.0f;
    m_vec70.w = 0.0f;
    m_vec70.z = 0.0f;
    m_vec70.y = 0.0f;
    m_vec70.x = 0.0f;
}

// @ 0x00af8920
void cContactProxy::SetFromSource(cContactRecord* src)
{
    Vector4 tmp;
    Vector4* vec;

    if (src->mType != 0)
    {
        vec = &m_vec10;
        m_type4c = src->mType;
        vec->x = src->mPoint.x;
        vec->y = src->mPoint.y;
        vec->z = src->mPoint.z;
        vec->w = src->mPoint.w;

        Vector4* p = src->mpPoint;
        if (p == 0)
            p = DirectionToPoint(&tmp, vec);
        m_vec50.x = p->x;
        m_vec50.y = p->y;
        m_vec50.z = p->z;
        m_vec50.w = p->w;
        m_b48 = 0;

        if (src->mType == 3)
        {
            cContactOwner* holder = (cContactOwner*)src->mpOwner;
            void* owner = holder != 0
                ? ((void* (__thiscall*)(cContactOwner*, uint32_t))holder->mpVtbl[3])(
                      holder, 0x01186577)
                : 0;
            SetEntity(owner, src->mpEntity, vec);
        }
    }
    else
    {
        m_type4c = 0;
        Vector4* p = DirectionToPoint(&tmp, &m_vec10);
        m_vec50.x = p->x;
        m_vec50.y = p->y;
        m_vec50.z = p->z;
        m_vec50.w = p->w;
        m_b48 = 0;
    }
}

// @ 0x00af8a10
void cContactProxy::Update(bool useLocal, float extra)
{
    Vector4 buf;
    SweepInput in;
    cContactRecord out;

    out.mpPoint = 0;
    out.pad24 = 0;
    out.mpOwner = 0;
    out.mpEntity = 0;

    Vector4 dir;
    if (useLocal)
    {
        dir.x = m_vec10.x;
        dir.y = m_vec10.y;
        dir.z = m_vec10.z;
        dir.w = m_vec10.w;
    }
    else
    {
        SurfaceHitQuery(&m_vec10, mpB4, &out);
        dir.x = out.mPoint.x;
        dir.y = out.mPoint.y;
        dir.z = out.mPoint.z;
        dir.w = out.mPoint.w;
        out.mPoint.x = kDefaultPointX;
        out.mPoint.y = kDefaultPointY;
        out.mPoint.z = kDefaultPointZ;
        out.mType = 0;
        out.mPoint.w = kDefaultPointW;
        out.pad24 = 0;
        out.mpOwner = 0;
        out.mpEntity = 0;
    }

    in.m_vec00.x = dir.x;
    in.m_vec00.y = dir.y;
    in.m_vec00.z = dir.z;
    in.m_vec00.w = dir.w;
    in.mRadius = m_fA8 + extra;
    in.m_f14 = m_fAC;
    out.mpPoint = &buf;

    SurfaceSweepQuery(&in, mpB4, mpB0, &mpCtx9c, !useLocal, &out, 0);
    SetFromSource(&out);
}
