// Slice s00d342d0 -- SP::cCreatureModeInputStrategy::UpdateCreaturePickBoxes (0x00d342d0, 3260 bytes).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: the fixed_vector locals have no EH frame).
//
// Rebuilds the creature-mode pick boxes (mCreatureHitBoxes, a pool of cMWModels):
//  * resets every hit-box model (empty bounding box, identity transform, no owner, hidden);
//  * collects the objects around the avatar (radius 20, cone filter 0x00d9a9c0) that can be
//    picked: living animals that are visible / not player-owned, tribe tools in a usable state
//    (when the avatar has a tribe) and buildings in state 2; sorts them by distance;
//  * walks the sorted list and assigns one hit-box per object: animals get their bounding box
//    scaled up with speed and camera distance (skipped when behind the camera plane, or too close
//    in adventures), tools a fixed box and buildings their own box (at most 3 of each);
//    each box takes the object's position/orientation and the object as owner.
// Model layout from ModAPI Graphics/Model.h; Transform from ModAPI Transform.h.
#include "types.h"
#include <stddef.h>

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8
#define CHECK_OFFSET(T, m, off) typedef char PVCAT(check_, __COUNTER__)[offsetof(T, m) == (off) ? 1 : -1]

#include <math.h>

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& v) { x = v.x; y = v.y; z = v.z; }
    float Dot(const Vector3& v) const { return x * v.x + y * v.y + z * v.z; }
    float Length() const { return sqrtf(x * x + y * y + z * z); }
};
inline Vector3 operator+(const Vector3& a, const Vector3& b) { return Vector3(a.x + b.x, a.y + b.y, a.z + b.z); }
inline Vector3 operator-(const Vector3& a, const Vector3& b) { return Vector3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline Vector3 operator*(const Vector3& a, float f) { return Vector3(a.x * f, a.y * f, a.z * f); }
inline Vector3 operator*(float f, const Vector3& a) { return Vector3(f * a.x, f * a.y, f * a.z); }
// Math::Vector3::Normalized-style safe normalize (1/sqrt(len^2 + 1e-8)).
inline Vector3 normalized_safe(const Vector3& v)
{
    float inv = 1.0f / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + 1e-8f);
    return Vector3(v.x * inv, v.y * inv, v.z * inv);
}

struct Matrix3 { float m[9]; };
struct Quaternion { float x, y, z, w; };

struct BoundingBox {
    Vector3 mMin;
    Vector3 mMax;
    BoundingBox() {}
    BoundingBox& operator=(const BoundingBox& b)
    {
        mMax = b.mMax;
        mMin = b.mMin;
        return *this;
    }
    // Scales the box about its center.
    void Scale(float s)
    {
        Vector3 c = (mMin + mMax) * 0.5f;
        mMin = s * (mMin - c) + c;
        mMax = s * (mMax - c) + c;
    }
};

extern Vector3 sZeroVector;          // 0x0169e17c Vector3::ZERO
extern Matrix3 sIdentityMatrix3;     // 0x0169e1cc Matrix3::IDENTITY

namespace SP {
Matrix3* Matrix3FromQuaternion(Matrix3* dst, const Quaternion* q);   // 0x0059c190
}

// Tunables of this module (writable .data floats).
extern float sPickBoxMaxScale;        // 0x01582bd8 (2.0)
extern float sPickBoxMinCameraDist;   // 0x01582bdc (10.0)
extern float sPickBoxMaxCameraDist;   // 0x01582be0 (100.0)
extern float sPickBoxMinSpeed;        // 0x01582be4 (3.0)
extern float sPickBoxMaxSpeed;        // 0x01582be8 (5.0)
extern float sPickBoxConeCos;         // 0x01582bec (0.95)
extern float sPickBoxMaxSize;         // 0x01582bf0 (4.0)
extern float sPickBoxMinAdventureDist;   // 0x01582bf4 (20.0)
extern BoundingBox sTribeToolPickBox; // 0x01582ce8 (-0.35,-0.7,-0.35)-(0.35,0.2,0.35)

extern char sGameModeAdventure;       // 0x01654c10
void* GetCurrentGameMode();           // 0x00b5b800

enum {
    kGameDataType     = 0x017f243b,
    kSpatialObjectType = 0x01186577,
    kNounCreatureAnimal = 0x018eb45e,
    kNounTribeTool    = 0x02c9cc91,
    kNounBuilding     = 0x03a2511e,
    kPickBoxModelType = 0x02e72cae,
};

namespace SP {

class cGameData;

class cSpatialObject {
public:
    PV8 PV2 PV                                         // 0x00-0x28
    virtual const Vector3& GetPosition();              // 0x2c
    virtual const Quaternion& GetOrientation();        // 0x30
    PV4 PV
    virtual bool IsVisible();                          // 0x48
    PV2 PV
    virtual bool IsPlayerOwned();                      // 0x58
    PV2 PV
    virtual const BoundingBox& GetBoundingBox();       // 0x68
    PV16 PV2 PV
    virtual cGameData* Cast(uint32_t type);            // 0xb8
    virtual int AddRef();                              // 0xbc
    virtual int Release();                             // 0xc0
};

class cLocomotiveObject : public cSpatialObject {
public:
    const Vector3& GetVelocity();                      // 0x00d20610
};

// EA::AutoRefCount<cSpatialObject>
struct cSpatialObjectPtr {
    cSpatialObject* mpObject;
    cSpatialObjectPtr(cSpatialObject* p) : mpObject(p) { if (p) p->AddRef(); }
    cSpatialObjectPtr(cLocomotiveObject* p);          // 0x00ad72e0 (out of line)
    ~cSpatialObjectPtr() { if (mpObject) mpObject->Release(); }
    cSpatialObject* get() const { return mpObject; }
};

inline void destruct(cSpatialObjectPtr* first, cSpatialObjectPtr* last)
{
    for (; first < last; ++first)
        first->~cSpatialObjectPtr();
}

// eastl::vector<cSpatialObjectPtr, sp_vector_allocator>
struct SpatialObjectVector {
    cSpatialObjectPtr* mpBegin;
    cSpatialObjectPtr* mpEnd;
    cSpatialObjectPtr* mpCapacity;
    ~SpatialObjectVector()
    {
        destruct(mpBegin, mpEnd);
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            operator delete[](mpBegin);
    }
    void push_back(const cSpatialObjectPtr& value);    // 0x00afc470
    cSpatialObjectPtr* begin() { return mpBegin; }
    cSpatialObjectPtr* end() { return mpEnd; }
    size_t size() const { return (size_t)(mpEnd - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
    cSpatialObjectPtr& operator[](size_t i) { return mpBegin[i]; }
};
// eastl::fixed_vector<cSpatialObjectPtr, 128>
struct FixedSpatialObjectVector : SpatialObjectVector {
    uint32_t mOverflowAllocator[2];
    uint32_t mNodeCount;
    cSpatialObject* mBuffer[128];
    FixedSpatialObjectVector()
    {
        mNodeCount = 0;
        mpBegin = (cSpatialObjectPtr*)mBuffer;
        mpEnd = (cSpatialObjectPtr*)mBuffer;
        mpCapacity = (cSpatialObjectPtr*)mBuffer + 128;
    }
};

// Sort functor: nearest to mPosition first.
struct SpatialObjectDistanceLess {
    Vector3 mPosition;
    SpatialObjectDistanceLess(const Vector3& p) : mPosition(p) {}
};
void sort(cSpatialObjectPtr* first, cSpatialObjectPtr* last, SpatialObjectDistanceLess compare);   // 0x00c7dac0

typedef bool (*ObjectFilter)(cSpatialObject* obj, void* context);
bool ConeFilter(cSpatialObject* obj, void* context);                     // 0x00d9a9c0

class cGameDataBase {
public:
    PV2 PV
    virtual cSpatialObject* CastSpatial(uint32_t type);   // 0x0c
};

class cPlanetObjectSource {
public:
    PV8 PV4
    virtual cGameDataBase* GetPlanetObject();             // 0x30
    PV2
    virtual Vector3 GetCenter(int);                       // 0x3c
    PV2
    virtual bool GetObjectsInRadius(const Vector3& center, float radius, SpatialObjectVector& dst,
                                    bool b, ObjectFilter filter, void* context);   // 0x48
};
cPlanetObjectSource* PlanetObjectSource();                // 0x00b3d240

class cGameData {
public:
    virtual int AddRef();                                 // 0x00
    virtual int Release();                                // 0x04
    PV4 PV2
    virtual uint32_t GetNounID();                         // 0x20
};

// EA::AutoRefCount<cGameData> (Graphics::Model::mpOwner)
struct cGameDataPtr {
    cGameData* mpObject;
    cGameDataPtr& operator=(cGameData* pObject)
    {
        if (pObject != mpObject) {
            cGameData* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
};

struct cTribe { uint32_t pad[0x60c / 4]; int mToolCount; };   // 0x60c

class cCreatureAnimal : public cGameData {
public:
    uint32_t pad004[(0xc0 - 4) / 4];
    cLocomotiveObject mLocomotive;      // 0xc0
    uint32_t pad0c4[(0x134 - 0xc4) / 4];
    uint8_t pad134;
    bool mbIsAlive;                     // 0x135
    uint8_t pad136[0xb20 - 0x136];
    cTribe* mpTribe;                    // 0xb20
    uint8_t padb24[0xb5e - 0xb24];
    bool mbIsSelected;                  // 0xb5e

    bool HasTribeTools();               // 0x00c0b7a0: mpTribe->mToolCount != 0
};

// Tribe tool / building: cGameData with a spatial object at +0x34.
class cPickableObject : public cGameData {
public:
    uint32_t pad004[(0x34 - 4) / 4];
    cSpatialObject mSpatial;            // 0x34
};
class cTribeTool : public cPickableObject {
public:
    uint32_t pad038[(0x16c - 0x38) / 4];
    int mState;                         // 0x16c
};
class cBuilding : public cPickableObject {
public:
    uint32_t pad038[(0x110 - 0x38) / 4];
    int mState;                         // 0x110
};

class cGameNounManager {
public:
    cCreatureAnimal* GetAvatar();       // 0x00b1fdb0
};
cGameNounManager* NounManager();        // 0x00b3d300

class cViewer {
public:
    void GetCameraLocationInfo(Vector3* pPosition, Vector3* pDirection, Vector3* pUp, Vector3* pRight);   // 0x007c3d30
};
class cCameraManager {
public:
    PV4 PV2 PV
    virtual cViewer* GetViewer();       // 0x1c
};
class cApp {
public:
    PV16 PV4
    virtual cCameraManager* GetCameraManager();   // 0x50
};
cApp* App();                            // 0x0067dd10

class cMWModel;
class IModelWorld {
public:
    PV16 PV16 PV16 PV16 PV16 PV8 PV2 PV
    virtual void UpdateModel(cMWModel* model, bool b);   // 0x16c
};

struct Transform {
    uint16_t mFlags;            // 0x00
    uint16_t mnChanges;         // 0x02
    Vector3 mOffset;            // 0x04
    float mScale;               // 0x10
    Matrix3 mRotation;          // 0x14
};

class cMWModel {
public:
    IModelWorld* mpWorld;       // 0x00
    uint32_t mFlags;            // 0x04
    Transform mTransform;       // 0x08
    uint32_t pad40[(0x60 - 0x40) / 4];
    uint32_t mType;             // 0x60
    cGameDataPtr mpOwner;       // 0x64
    uint32_t pad68;
    float mDefaultBoundingRadius;   // 0x6c
    BoundingBox mDefaultBBox;   // 0x70
};
CHECK_OFFSET(cMWModel, mDefaultBBox, 0x70);

// EA::AutoRefCount<cMWModel>
struct cMWModelPtr {
    cMWModel* mpObject;
    cMWModel* get() const { return mpObject; }
};

class cCreatureModeInputStrategy {
public:
    uint32_t pad00[0x58 / 4];
    cMWModelPtr* mCreatureHitBoxesBegin;   // 0x58
    cMWModelPtr* mCreatureHitBoxesEnd;     // 0x5c

    void UpdateCreaturePickBoxes();
};

void cCreatureModeInputStrategy::UpdateCreaturePickBoxes()
{
    size_t numHitBoxes = mCreatureHitBoxesEnd - mCreatureHitBoxesBegin;
    for (size_t i = 0; i < numHitBoxes; i++) {
        cMWModel* model = mCreatureHitBoxesBegin[i].get();
        if (model) {
            model->mDefaultBBox.mMin = sZeroVector;
            model->mDefaultBBox.mMax = sZeroVector;
            model->mDefaultBoundingRadius = 0.0f;
            model->mType = 0;
            model->mTransform.mRotation = sIdentityMatrix3;
            model->mTransform.mScale = 1.0f;
            model->mTransform.mOffset = sZeroVector;
            model->mTransform.mFlags = 0;
            model->mTransform.mnChanges = 0;
            model->mpOwner = 0;
            model->mFlags &= ~1;
        }
    }

    bool isAdventure = GetCurrentGameMode() == &sGameModeAdventure;
    Vector3 center(sZeroVector);
    if (isAdventure) {
        cGameDataBase* planet = PlanetObjectSource()->GetPlanetObject();
        cSpatialObject* spatial;
        if (planet && (spatial = planet->CastSpatial(kSpatialObjectType)) != 0)
            center = spatial->GetPosition();
        else
            center = PlanetObjectSource()->GetCenter(1);
    } else {
        center = PlanetObjectSource()->GetCenter(1);
    }

    FixedSpatialObjectVector objects;
    cCreatureAnimal* avatar = NounManager()->GetAvatar();
    if (avatar) {
        FixedSpatialObjectVector nearby;
        if (PlanetObjectSource()->GetObjectsInRadius(center, 20.0f, nearby, false, ConeFilter, avatar)) {
            for (cSpatialObjectPtr* it = nearby.begin(); it != nearby.end(); ++it) {
                cSpatialObject* object = it->get();
                if (!object)
                    continue;
                cGameData* data = object->Cast(kGameDataType);
                if (!data)
                    continue;
                if (data->GetNounID() == kNounCreatureAnimal) {
                    cCreatureAnimal* creature = (cCreatureAnimal*)data;
                    if (creature->mbIsAlive && creature->mLocomotive.IsVisible() &&
                        !creature->mLocomotive.IsPlayerOwned() && !creature->mbIsSelected) {
                        cSpatialObjectPtr p(&creature->mLocomotive);
                        objects.push_back(p);
                    }
                    continue;
                }
                if (data->GetNounID() == kNounTribeTool) {
                    if (!avatar->HasTribeTools())
                        continue;
                    int state = ((cTribeTool*)data)->mState;
                    if (state != 2 && state != 1)
                        continue;
                } else if (data->GetNounID() == kNounBuilding) {
                    if (((cBuilding*)data)->mState != 2)
                        continue;
                } else {
                    continue;
                }
                cSpatialObjectPtr p(&((cPickableObject*)data)->mSpatial);
                objects.push_back(p);
            }
            sort(objects.begin(), objects.end(), SpatialObjectDistanceLess(center));
        }
    }

    if (objects.empty())
        return;

    cViewer* viewer = App()->GetCameraManager()->GetViewer();
    Vector3 cameraPos(sZeroVector);
    Vector3 cameraDir(sZeroVector);
    if (viewer)
        viewer->GetCameraLocationInfo(&cameraPos, &cameraDir, 0, 0);

    const Vector3& avatarPos = avatar->mLocomotive.GetPosition();
    Vector3 up = normalized_safe(avatarPos);
    Vector3 toCamera = cameraPos - avatarPos;
    toCamera = toCamera - up * toCamera.Dot(up);
    Vector3 cameraFlat = normalized_safe(toCamera);

    size_t numObjects = objects.size();
    size_t numBoxes = mCreatureHitBoxesEnd - mCreatureHitBoxesBegin;
    int numTools = 0;
    int numBuildings = 0;
    size_t objectIndex = 0;
    size_t boxIndex = 0;
    while (objectIndex < numObjects && boxIndex < numBoxes) {
        cSpatialObject* object = objects[objectIndex++].get();
        if (!object)
            continue;
        cGameData* data = object->Cast(kGameDataType);
        if (!data)
            continue;

        BoundingBox box;
        if (data->GetNounID() == kNounCreatureAnimal) {
            cLocomotiveObject* loco = &((cCreatureAnimal*)data)->mLocomotive;
            float speedFactor = 0.0f;
            float distFactor = 0.0f;
            const Vector3& pos = loco->GetPosition();
            Vector3 fromCamera = cameraPos - pos;
            Vector3 fromAvatar = pos - avatarPos;
            float cameraDist = fromCamera.Length();
            if (isAdventure && fromAvatar.Length() < sPickBoxMinAdventureDist)
                continue;
            Vector3 flat = fromAvatar - up * fromAvatar.Dot(up);
            if (!(normalized_safe(flat).Dot(cameraFlat) < sPickBoxConeCos))
                continue;
            float speed = loco->GetVelocity().Length();
            if (speed > sPickBoxMinSpeed)
                speedFactor = (speed - sPickBoxMinSpeed) / (sPickBoxMaxSpeed - sPickBoxMinSpeed);
            if (cameraDist > sPickBoxMinCameraDist)
                distFactor = (cameraDist - sPickBoxMinCameraDist) / (sPickBoxMaxCameraDist - sPickBoxMinSpeed);
            float scale = (distFactor + speedFactor) * 0.5f * (sPickBoxMaxScale - 1.0f) + 1.0f;
            box = loco->GetBoundingBox();
            float s = ((box.mMax - box.mMin).Length() * scale < sPickBoxMaxSize) ? scale : 1.0f;
            box.Scale(s);
            if (!(s >= 1.0f))
                continue;
        } else if (data->GetNounID() == kNounTribeTool) {
            if (numTools++ >= 3)
                continue;
            box = sTribeToolPickBox;
        } else if (data->GetNounID() == kNounBuilding) {
            if (numBuildings++ >= 3)
                continue;
            box = object->GetBoundingBox();
        } else {
            continue;
        }

        cMWModel* model = mCreatureHitBoxesBegin[boxIndex++].get();
        if (!model)
            continue;
        model->mDefaultBBox = box;
        model->mDefaultBoundingRadius = (box.mMax - box.mMin).Length();
        model->mTransform.mOffset = object->GetPosition();
        model->mTransform.mFlags |= 4;
        model->mTransform.mnChanges++;
        Matrix3 rotation;
        model->mTransform.mRotation = *Matrix3FromQuaternion(&rotation, &object->GetOrientation());
        model->mTransform.mFlags |= 2;
        model->mTransform.mnChanges++;
        model->mpOwner = data;
        model->mType = kPickBoxModelType;
        model->mFlags |= 1;
        model->mpWorld->UpdateModel(model, true);
    }
}

}  // namespace SP
