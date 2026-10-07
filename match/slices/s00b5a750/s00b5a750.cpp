// Slice s00b5a750 -- static-collision rebuild of the planet's Havok world (0x00b5a750, 3553 bytes).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (no /EHsc: the hash-map / smart-pointer locals have no EH frame).
//
// Runs only when sRebuildBuildingBodies is set (and the terrain is not in water mode):
//  1. Every building / object of the city-building map gets a fixed rigid body: an existing body
//     (from the previous rebuild) is moved into sBuildingBodies, otherwise one is created from the
//     object's collision model (if the model-shape option is on and the object's model resource
//     allows it) or from a capsule / sphere sized by the object's height and radius, placed at the
//     object's transform.  Bodies of objects that no longer exist are removed from their world.
//  2. When the planet-object list is empty (or sRebuildPlanetBodies is set), every planet object
//     that has not been processed yet gets either a capsule phantom oriented on the planet surface
//     (trees / "phantom" objects) or a fixed rigid body made from its collision model.
#include "types.h"
#include <math.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8
#define PV32 PV16 PV16
#define CHECK_OFFSET(T, m, off) typedef char PVCAT(check_, __COUNTER__)[offsetof(T, m) == (off) ? 1 : -1]
#include <stddef.h>

// ---- math ----------------------------------------------------------------------------------------
struct Vector3 { float x, y, z; };
struct Quaternion { float x, y, z, w; };
struct Matrix3 {
    float m[3][3];
    Matrix3& Assign(const Matrix3& other);                                   // 0x0041cb40
};
__forceinline Vector3 operator*(const Vector3& v, const Matrix3& m)
{
    Vector3 r;
    r.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0];
    r.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1];
    r.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2];
    return r;
}
namespace rw { namespace math { namespace fpu {
Quaternion QuaternionFromMatrix33(const Matrix3& m, float tolerance);         // 0x00472b80
}}}
Quaternion QuaternionFromMatrix(const Matrix3& m);                            // 0x0046d660

struct cSPTransform {
    u16 mFlags;                        // 0x00
    u16 mPad;
    Vector3 mPosition;                 // 0x04
    float mScale;                      // 0x10
    Matrix3 mRotation;                 // 0x14
    cSPTransform(const cSPTransform& other);                                 // 0x0040ce80
    cSPTransform& operator=(const cSPTransform& other);                      // 0x00537dc0
};

// ---- Havok ---------------------------------------------------------------------------------------
struct __declspec(align(16)) hkVector4 {
    float x, y, z, w;
    void set(float ax, float ay, float az, float aw) { x = ax; y = ay; z = az; w = aw; }
};
struct __declspec(align(16)) hkQuaternion { hkVector4 m_vec; };
struct __declspec(align(16)) hkRotation {
    hkVector4 m_col0, m_col1, m_col2;
    void set(const hkQuaternion& q);                                         // 0x010824a0
};
struct __declspec(align(16)) hkTransform { hkRotation m_rotation; hkVector4 m_translation; };

class hkMemory {
public:
    PV4
    virtual void* allocateChunk(int nbytes, int cl);                         // 0x10
    static hkMemory* s_instance;                                             // 0x016e4178
    static hkMemory& getInstance() { return *s_instance; }
};

class hkReferencedObject {
public:
    virtual ~hkReferencedObject();                                           // 0x00 (scalar deleting)
    u16 m_memSizeAndFlags;                                                   // 0x04
    u16 m_referenceCount;                                                    // 0x06
    __forceinline void removeReference()
    {
        if (m_memSizeAndFlags != 0)
        {
            --m_referenceCount;
            if (m_referenceCount == 0)
                delete this;
        }
    }
};

class hkShape : public hkReferencedObject {
public:
    void* operator new(size_t nbytes)
    {
        hkReferencedObject* b = (hkReferencedObject*)hkMemory::getInstance().allocateChunk((int)nbytes, 0x24);
        b->m_memSizeAndFlags = (u16)nbytes;
        return b;
    }
    void operator delete(void*) {}
};
class hkCapsuleShape : public hkShape {
public:
    hkCapsuleShape(const hkVector4& vertexA, const hkVector4& vertexB, float radius);   // 0x010c2730
    u8 pad[0x30 - 8];
};
class hkSphereShape : public hkShape {
public:
    hkSphereShape(float radius);                                             // 0x010c3770
    u8 pad[0x10 - 8];
};

class hkWorldObject : public hkReferencedObject {
public:
    void* m_world;                                                           // 0x08
    void* m_userData;                                                        // 0x0c
    void addProperty(u32 key, unsigned __int64 value);                       // 0x010825a0
    void removeReference();                                                  // 0x0109ae60 (out of line here)
};

class hkRigidBody : public hkWorldObject {
public:
    void setRotation(const hkQuaternion& q);                                 // 0x01087840
    void setPosition(const hkVector4& p);                                    // 0x01087820
    void setMotionType(int motionType, int activation, int collisionFilterUpdate);   // 0x01087520
};

class hkPhantom : public hkWorldObject {};
class hkSimpleShapePhantom : public hkPhantom {
public:
    void* operator new(size_t nbytes)
    {
        hkReferencedObject* b = (hkReferencedObject*)hkMemory::getInstance().allocateChunk((int)nbytes, 0x2e);
        b->m_memSizeAndFlags = (u16)nbytes;
        return b;
    }
    void operator delete(void*) {}
    hkSimpleShapePhantom(const hkShape* shape, const hkTransform& transform, u32 collisionFilterInfo);   // 0x0108c750
    u8 pad[0x130 - 0x10];
};

struct hkBool { char m_bool; };
class hkWorld {
public:
    hkRigidBody* addEntity(hkRigidBody* entity, int activation);             // 0x01082ee0
    hkBool removeEntity(hkRigidBody* entity);                                // 0x01083110
    hkPhantom* addPhantom(hkPhantom* phantom);                               // 0x01083320
};

struct hkRigidBodyCinfo {
    u32 m_collisionFilterInfo;                                               // 0x00
    hkShape* m_shape;                                                        // 0x04
    u8 pad08[0x9c - 8];
    float m_friction;                                                        // 0x9c
    float m_restitution;                                                     // 0xa0
    u8 pada4[0xb0 - 0xa4];
    u8 m_motionType;                                                         // 0xb0
    u8 padb1[0xc0 - 0xb1];
    hkRigidBodyCinfo();                                                      // 0x01087ed0
};

namespace SP { namespace Havok {
hkRigidBody* CreateRigidBody(hkRigidBodyCinfo* info);                        // 0x00b4d880
}}

// ---- properties ----------------------------------------------------------------------------------
struct Property {
    u8 pad[0x12];
    u16 mType;                                                               // 0x12
    bool* GetBool();                                                         // 0x0041e920
};
class PropertyList {
public:
    PV8 PV
    virtual bool GetProperty(u32 id, Property*& result);                     // 0x24
};
bool GetBoolProperty(PropertyList* list, u32 id, bool& value);               // 0x00407190
bool GetPropertyAsUint32(PropertyList* list, u32 id, u32& value);            // 0x004af210

// ---- models --------------------------------------------------------------------------------------
struct cModel { u8 pad[0x40]; int mRefCount; };                              // 0x40
struct cModelPtr {
    cModel* mpModel;
    cModelPtr() : mpModel(0) {}
    cModelPtr(cModel* p) : mpModel(p) { if (p) p->mRefCount++; }
    ~cModelPtr();                                                            // 0x005765e0
    cModelPtr& operator=(cModel* p);                                         // 0x00478db0
};
class cModelResource {
public:
    virtual void AddRef();                                                   // 0x00
    virtual void Release();                                                  // 0x04
    PV
    virtual cModel* Load(u32 key, u32 flags, int);                           // 0x0c
};
class cModelManager {
public:
    PV4 PV2 PV
    virtual cModelResource* GetResource(u32 id);                             // 0x1c
};
cModelManager* ModelManager();                                               // 0x0067dd80

class cGonzagoModelWorld {
public:
    PV2 PV
    virtual cModel* FindModelAt(float x, float z, int);                      // 0x0c
};
cGonzagoModelWorld* GonzagoModelWorld();                                     // 0x00b3d520

// collision-shape lookup for a model (result +0x0c = hkShape*)
struct cCollisionRequest {
    void* mpOwner;                                                           // 0x00
    float mA;                                                                // 0x04
    float mB;                                                                // 0x08
    u32 pad0c[3];
    bool mFlag;                                                              // 0x18
};
struct cCollisionShape { u8 pad[0xc]; hkShape* mpShape; };
cCollisionShape* GetCollisionShape(void* owner, float scale, cCollisionRequest* request);   // 0x00b54c40

// ---- game objects --------------------------------------------------------------------------------
struct cPlanetObjectData { u8 pad[8]; Vector3 mPosition; };                   // 0x08
struct cPlanetObject {
    u32 pad00;
    u32 mFlags;                                                              // 0x04
    cSPTransform mTransform;                                                 // 0x08
    u8 pad[0x6c - 0x08 - sizeof(cSPTransform)];
    float mRadius;                                                           // 0x6c
    u8 pad70[0x90 - 0x70];
    PropertyList* mpPropList;                                                // 0x90 (also the data with the position at +8)
};
CHECK_OFFSET(cPlanetObject, mRadius, 0x6c);
CHECK_OFFSET(cPlanetObject, mpPropList, 0x90);

class cCityObject {
public:
    PV8 PV2 PV
    virtual bool IsDestroyed();                                              // 0x2c
    u8 pad04[0x34 - 4];
    u8 mObjectFlags;                                                         // 0x34
    u8 pad35[0x38 - 0x35];
    Vector3 mPosition;                                                       // 0x38
    float mRadius;                                                           // 0x44
    u32 pad48;
    float mHeight;                                                           // 0x4c
    u8 pad50[0x60 - 0x50];
    u32 mID;                                                                 // 0x60
    u8 pad64[0x6c - 0x64];
    u32 mModelKey;                                                           // 0x6c
    u8 pad70[0x88 - 0x70];
    int mType;                                                               // 0x88

    cSPTransform* GetTransform();                                            // 0x00b73e70
};
CHECK_OFFSET(cCityObject, mHeight, 0x4c);
CHECK_OFFSET(cCityObject, mType, 0x88);

struct cModelInfo { u8 pad[4]; u32 mModelKey; u8 pad08[0x20 - 8]; u32 mFlags; };   // size 0x24
struct cModelInfoList { cModelInfo* mpBegin; cModelInfo* mpEnd; };
struct cModelInfoOwner { u8 pad[0x17c]; cModelInfoList mList; };
cModelInfoOwner* ModelInfoOwner();                                           // 0x00b3d3b0

// city-object map (node: key 8 bytes, value at +8, next at +0x10)
struct CityNode { u32 key[2]; cCityObject* mpObject; u32 pad; CityNode* mpNext; };
struct CityIterator {
    CityNode* mpNode;
    CityNode** mpBucket;
    void increment()
    {
        mpNode = mpNode->mpNext;
        while (mpNode == 0)
            mpNode = *++mpBucket;
    }
};
struct CityMap {
    u32 pad;
    CityNode** mpBucketArray;                                                // 0x04
    u32 mnBucketCount;                                                       // 0x08
    CityIterator begin();                                                    // 0x00594410
    CityNode* endNode() { return mpBucketArray[mnBucketCount]; }
};
class cCityObjects {
public:
    CityMap* GetObjectMap();                                                 // 0x00ad2800
    Vector3* SnapToSurface(const Vector3& position);                         // 0x00b74f40
};
cCityObjects* CityObjects();                                                 // 0x00b3d3c0

struct cTerrainInfo { u8 pad[0x20]; int mWaterMode; };
cTerrainInfo* TerrainInfo();                                                 // 0x00b3d310

class cITerrainSphere {
public:
    PV32 PV8 PV4
    virtual int GetPlanetObjects(cPlanetObject**& objects);                  // 0xb0
};
class cPlanetModel {
public:
    u8 pad[0x24];
    cITerrainSphere* mpISphere;                                              // 0x24
    void BuildSurfaceOrientation(Quaternion& orientation, const cSPTransform& transform);   // 0x00b7f190
};
cPlanetModel* PlanetModel();                                                 // 0x00b3d350

// eastl::fixed_hash_map<uint32_t, hkRigidBody*, ...> (node: key, value, next)
struct BodyNode { u32 mKey; hkRigidBody* mpBody; BodyNode* mpNext; };
struct BodyIterator { BodyNode* mpNode; BodyNode** mpBucket; };
struct BodyMap {
    u32 pad00;
    BodyNode** mpBucketArray;                                                // 0x04
    u32 mnBucketCount;                                                       // 0x08
    u32 mnElementCount;                                                      // 0x0c
    u32 mRehashPolicy[3];                                                    // 0x10
    void* mpPoolHead;                                                        // 0x1c
    void* mpPoolNext;                                                        // 0x20
    void* mpPoolBegin;                                                       // 0x24
    void* mpPoolEnd;                                                         // 0x28
    u32 mnNodeSize;                                                          // 0x2c
    BodyNode** mpBucketBuffer;                                               // 0x30
    u8 mBuffers[0x1440 - 0x34];

    BodyMap(const BodyMap& other);                                           // 0x00b54640
    void DoFreeNodes(BodyNode** buckets, u32 n);                             // 0x00a1b6c0
    BodyIterator find(const u32& key);                                       // 0x00645ed0
    BodyIterator erase(BodyIterator it);                                     // 0x00b51640
    hkRigidBody*& operator[](const u32& key);                                // 0x00b54750
    BodyNode* endNode() { return mpBucketArray[mnBucketCount]; }
    void clear()
    {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
    }
    ~BodyMap()
    {
        clear();
        if (mnBucketCount > 1 && mpBucketArray != mpBucketBuffer)
        {
            if (mpBucketArray >= mpPoolBegin && mpBucketArray < mpPoolEnd)
            {
                *(void**)mpBucketArray = mpPoolHead;
                mpPoolHead = mpBucketArray;
            }
            else
                operator delete[](mpBucketArray);
        }
    }
};

// eastl::set<int> (processed planet-object indices)
struct IntNode { IntNode* mpNodeRight; IntNode* mpNodeLeft; IntNode* mpNodeParent; u32 mColor; int mValue; };
struct true_type_tag {};
struct InsertResult { IntNode* mpNode; bool mbInserted; };
struct IntSet {
    u32 pad;
    IntNode mAnchor;                                                         // 0x04 (root = mAnchor.mpNodeParent)
    InsertResult DoInsertValue(const int& value, true_type_tag);             // 0x00b54ab0
    InsertResult insert(const int& value) { return DoInsertValue(value, true_type_tag()); }
    IntNode* find(const int& key)
    {
        IntNode* pCurrent = mAnchor.mpNodeParent;
        IntNode* pRangeEnd = &mAnchor;
        while (pCurrent)
        {
            if (pCurrent->mValue < key)
                pCurrent = pCurrent->mpNodeRight;
            else
            {
                pRangeEnd = pCurrent;
                pCurrent = pCurrent->mpNodeLeft;
            }
        }
        if (pRangeEnd != &mAnchor && !(key < pRangeEnd->mValue))
            return pRangeEnd;
        return &mAnchor;
    }
};

struct BodyVector {
    hkRigidBody** mpBegin;
    hkRigidBody** mpEnd;
    bool empty() const { return mpBegin == mpEnd; }
    void push_back(hkRigidBody* const& value);                               // 0x0062dee0
};
struct PhantomVector {
    void push_back(hkSimpleShapePhantom* const& value);                      // 0x00c072f0
};

// ---- this module's globals -----------------------------------------------------------------------
extern bool sRebuildBuildingBodies;      // 0x0167ece0
extern bool sRebuildPlanetBodies;        // 0x0167ecdb
extern bool sUseModelCollision;          // 0x0167ecda
extern hkWorld* sWorld;                  // 0x0167ecd0
extern Vector3 sZeroVector;              // 0x0167ecf4
extern BodyMap sBuildingBodies;          // 0x01683e98
extern BodyVector sPlanetBodies;         // 0x01569b68
extern PhantomVector sPlanetPhantoms;    // 0x01569c00
extern IntSet sProcessedPlanetObjects;   // 0x01686738
extern float sCollisionScaleA;           // 0x01569b0c
extern float sCollisionScaleB;           // 0x01569b10
extern u32 sModelLoadFlags;              // 0x01569b54
extern u32 sHutModelLoadFlags;           // 0x01569b64
extern float sPhantomHeight;             // 0x01569ad0
extern float sPhantomRadius;             // 0x01569ad4
extern float sTreePhantomExtraHeight;    // 0x01569ae4

// @ 0x00b5a750
void RebuildStaticCollision()
{
    if (!sRebuildBuildingBodies)
        return;
    sRebuildBuildingBodies = false;
    if (TerrainInfo()->mWaterMode != 0)
        return;

    BodyMap oldBodies(sBuildingBodies);
    sBuildingBodies.clear();

    hkRigidBodyCinfo info;
    info.m_restitution = 0.0f;
    info.m_friction = 0.1f;
    info.m_motionType = 7;
    info.m_shape = 0;
    info.m_collisionFilterInfo = 7;

    cModelInfoList* modelInfos = &ModelInfoOwner()->mList;
    cCityObjects* cityObjects = CityObjects();
    CityMap* objectMap = cityObjects->GetObjectMap();
    CityIterator it = objectMap->begin();
    CityNode* end = objectMap->endNode();
    for (; it.mpNode != end; it.increment())
    {
        cCityObject* object = it.mpNode->mpObject;
        if (object->IsDestroyed())
            continue;
        if (object->mType == 3 && (object->mObjectFlags & 1))
            continue;
        if (object->mType == 4)
            continue;

        u32* key = &object->mID;
        BodyIterator found = oldBodies.find(*key);
        if (found.mpNode != oldBodies.endNode())
        {
            sBuildingBodies[*key] = found.mpNode->mpBody;
            oldBodies.erase(found);
            continue;
        }

        float height = object->mHeight;
        hkShape* shape = 0;
        cSPTransform* transform = object->GetTransform();
        Vector3 up = { 0.0f, 0.0f, height * 0.5f };
        Vector3 offset = up * transform->mRotation;
        if (sUseModelCollision && object->mType == 3 && object->mModelKey != 0)
        {
            cModelInfo* modelInfo = modelInfos->mpBegin;
            for (; modelInfo != modelInfos->mpEnd; modelInfo++)
                if (modelInfo->mModelKey == object->mModelKey)
                    break;
            if (modelInfo != modelInfos->mpEnd && !((modelInfo->mFlags >> 1) & 1))
            {
                cModelResource* resource = ModelManager()->GetResource(0xeb9968);
                if (resource)
                    resource->AddRef();
                u32 flags;
                if (object->mType == 3)
                    flags = sHutModelLoadFlags;
                else
                    flags = (sModelLoadFlags & 0xffff62ff) | 0x6200;
                {
                    cModelPtr model(resource->Load(object->mModelKey, flags, 0));
                    cCollisionRequest request;
                    request.mpOwner = model.mpModel;
                    request.mA = sCollisionScaleA;
                    request.mB = sCollisionScaleB;
                    request.mFlag = false;
                    cCollisionShape* collision = GetCollisionShape(model.mpModel, object->GetTransform()->mScale, &request);
                    if (collision && collision->mpShape)
                    {
                        shape = collision->mpShape;
                        offset = sZeroVector;
                    }
                }
                resource->Release();
                if (shape)
                    goto haveShape;
            }
        }
        {
            float halfHeight = object->mHeight * 0.5f;
            if (halfHeight > object->mRadius)
            {
                float d = halfHeight - object->mRadius;
                Vector3 top = { sZeroVector.x, sZeroVector.y, d };
                Vector3 bottom = { sZeroVector.x, sZeroVector.y, -d };
                hkVector4 vertexB;
                vertexB.set(bottom.x, bottom.y, bottom.z, 0.0f);
                hkVector4 vertexA;
                vertexA.set(top.x, top.y, top.z, 0.0f);
                shape = new hkCapsuleShape(vertexA, vertexB, object->mRadius);
            }
            else
                shape = new hkSphereShape(object->mRadius);
        }
    haveShape:
        info.m_shape = shape;
        hkRigidBody* body = SP::Havok::CreateRigidBody(&info);
        shape->removeReference();

        Quaternion q = rw::math::fpu::QuaternionFromMatrix33(transform->mRotation, 0.0f);
        float invLength = (float)(1.0 / sqrt((double)q.w * q.w + (double)q.z * q.z + (double)q.y * q.y + (double)q.x * q.x));
        hkQuaternion rotation;
        rotation.m_vec.set(invLength * q.x, invLength * q.y, invLength * q.z, invLength * q.w);
        body->setRotation(rotation);
        hkVector4 position;
        position.set(object->mPosition.x + offset.x, object->mPosition.y + offset.y,
                     object->mPosition.z + offset.z, 0.0f);
        body->setPosition(position);
        body->m_userData = object;
        body->addProperty(0, 2);
        body->addProperty(1, (u32)&object);
        body->addProperty(5, (__int64)((object->mType == 3) + 10));
        body->setMotionType(7, 1, 0);
        sWorld->addEntity(body, 1);
        sBuildingBodies[object->mID] = body;
        body->removeReference();
    }

    if (sPlanetBodies.empty() || sRebuildPlanetBodies)
    {
        sRebuildPlanetBodies = false;
        cPlanetModel* planet = PlanetModel();
        ModelManager()->GetResource(0x3fbae24);
        cPlanetObject** planetObjects;
        int count;
        if (planet && planet->mpISphere)
            count = planet->mpISphere->GetPlanetObjects(planetObjects);
        else
            count = 0;
        for (int i = 0; i < count; i++)
        {
            if (sProcessedPlanetObjects.find(i) != &sProcessedPlanetObjects.mAnchor)
                continue;
            cPlanetObject* planetObject = planetObjects[i];
            if (!planetObject)
            {
                sProcessedPlanetObjects.insert(i);
                continue;
            }
            if (!((planetObject->mFlags >> 14) & 1))
            {
                sRebuildBuildingBodies = true;
                sRebuildPlanetBodies = true;
                continue;
            }

            Vector3 position = ((cPlanetObjectData*)planetObject->mpPropList)->mPosition;
            cModelPtr found;
            Vector3* snapped = cityObjects->SnapToSurface(position);
            if (snapped)
            {
                position = *snapped;
                found = GonzagoModelWorld()->FindModelAt(position.x, position.z, 0);
                cPlanetObject* foundObject = (cPlanetObject*)found.mpModel;
                if (!foundObject)
                {
                    sProcessedPlanetObjects.insert(i);
                    continue;
                }
                if (!((foundObject->mFlags >> 14) & 1) || ((foundObject->mFlags >> 18) & 1))
                {
                    sRebuildBuildingBodies = true;
                    sRebuildPlanetBodies = true;
                    continue;
                }
                foundObject->mTransform = planetObject->mTransform;
                planetObject = foundObject;
            }

            sProcessedPlanetObjects.insert(i);
            {
                Property* prop;
                if (planetObject->mpPropList && planetObject->mpPropList->GetProperty(0x37575e5, prop) &&
                    prop->mType == 1 && !*prop->GetBool())
                    continue;
            }

            cSPTransform transform(planetObject->mTransform);
            float phantomHeight = sPhantomHeight;
            float phantomRadius = sPhantomRadius;
            bool bPhantom = false;
            GetBoolProperty(planetObject->mpPropList, 0x3f6d22a, bPhantom);
            u32 objectType = 0;
            if (GetPropertyAsUint32(planetObject->mpPropList, 0x4ce873a, objectType) && objectType == 0x4fc5ab9d)
            {
                phantomRadius = planetObject->mRadius;
                phantomHeight = phantomRadius + sTreePhantomExtraHeight;
            }
            else if (!bPhantom)
            {
                // fixed rigid body from the object's collision model
                cCollisionRequest request;
                request.mpOwner = planetObject;
                request.mA = sCollisionScaleA;
                request.mB = sCollisionScaleB;
                request.mFlag = false;
                cCollisionShape* collision = GetCollisionShape(planetObject, planetObject->mTransform.mScale, &request);
                if (!collision)
                    continue;
                hkShape* shape = collision->mpShape;
                if (!shape)
                    continue;
                info.m_shape = shape;
                hkRigidBody* body = SP::Havok::CreateRigidBody(&info);
                shape->removeReference();
                Matrix3 rotation;
                rotation.Assign(transform.mRotation);
                Quaternion q = QuaternionFromMatrix(rotation);
                hkQuaternion hq;
                hq.m_vec.set(q.x, q.y, q.z, q.w);
                body->setRotation(hq);
                hkVector4 bodyPosition;
                bodyPosition.set(transform.mPosition.x, transform.mPosition.y, transform.mPosition.z, 0.0f);
                body->setPosition(bodyPosition);
                body->m_userData = 0;
                body->addProperty(0, 2);
                body->addProperty(1, 0);
                body->addProperty(5, 0xb);
                body->setMotionType(7, 1, 0);
                sWorld->addEntity(body, 1);
                body->removeReference();
                sPlanetBodies.push_back(body);
                continue;
            }

            // capsule phantom standing on the planet surface
            Quaternion orientation;
            planet->BuildSurfaceOrientation(orientation, transform);
            hkVector4 base;
            base.set(0.0f, 0.0f, 0.0f, 0.0f);
            hkVector4 top;
            top.set(0.0f, 0.0f, phantomHeight, 0.0f);
            hkShape* capsule = new hkCapsuleShape(base, top, phantomRadius);
            hkQuaternion hq;
            hq.m_vec.set(orientation.x, orientation.y, orientation.z, orientation.w);
            hkTransform phantomTransform;
            phantomTransform.m_translation.set(transform.mPosition.x, transform.mPosition.y, transform.mPosition.z, 0.0f);
            phantomTransform.m_rotation.set(hq);
            hkSimpleShapePhantom* phantom = new hkSimpleShapePhantom(capsule, phantomTransform, 10);
            phantom->m_userData = planetObject;
            phantom->addProperty(0, 4);
            sWorld->addPhantom(phantom);
            phantom->removeReference();
            capsule->removeReference();
            sPlanetPhantoms.push_back(phantom);
        }
    }

    // bodies of objects that are gone
    {
        BodyNode** bucket = oldBodies.mpBucketArray;
        BodyNode* node = *bucket;
        while (node == 0)
            node = *++bucket;
        BodyNode* endNode = oldBodies.mpBucketArray[oldBodies.mnBucketCount];
        while (node != endNode)
        {
            if (node->mpBody)
                ((hkWorld*)node->mpBody->m_world)->removeEntity(node->mpBody);
            node->mpBody = 0;
            node = node->mpNext;
            while (node == 0)
                node = *++bucket;
        }
    }
}
