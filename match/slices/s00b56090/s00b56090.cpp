// Slice s00b56090 (batch op2_big) — 0x00b56090, 3915 bytes.
//
// SP::Havok::CreateHavokEntityForObject(cGameData*, cSpatialObject*, cLocomotiveObject*,
//                                       const cPhysicsNounTuning*)
//
// Identification: the dev PDB has exactly one function with this argument list in
// SPGonzagoPhysicsHavok.obj (2998 B there).  The body builds the Havok object for a
// simulator object: an optional "useGameplayPhantom" hkSimpleShapePhantom subclass,
// then (if "hasCollision") either a plain hkSimpleShapePhantom, a locomotive body plus
// its 0x150-byte "Simulator" controller, or a static/dynamic hkRigidBody; tutorial
// objects additionally get an hkAabbPhantom.  Each created object is registered in a
// global hash_map keyed by the cSpatialObject*.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (SSE scalar float math, x87 float returns,
// AutoRefCount local without an EH frame -> no /EHsc).  Same module family as
// slice s00b57c40 (cGonzagoPhysics::UpdateHavok).
//
// Callees without a recovered name keep their FUN_ address names.

#include "types.h"

#pragma pack(push, 8)

// ---------------------------------------------------------------------------
// Havok (only what this function needs)
// ---------------------------------------------------------------------------
typedef float hkReal;

class hkMemory {
public:
    virtual void _v0(); virtual void _v1(); virtual void _v2(); virtual void _v3();
    virtual void* allocateChunk(int nbytes, int cl);                 // 0x10
    virtual void deallocateChunk(void* p, int nbytes, int cl);       // 0x14
    static hkMemory* s_instance;                                     // 0x016E4178
    static hkMemory& getInstance() { return *s_instance; }
};

#define HK_DECLARE_CLASS_ALLOCATOR(CLS) \
    __forceinline void* operator new(unsigned int nbytes) { \
        hkReferencedObject* b = static_cast<hkReferencedObject*>(hkMemory::getInstance().allocateChunk(nbytes, CLS)); \
        b->m_memSizeAndFlags = (unsigned short)nbytes; \
        return b; } \
    void operator delete(void* p) { \
        hkReferencedObject* b = static_cast<hkReferencedObject*>(p); \
        hkMemory::getInstance().deallocateChunk(p, b->m_memSizeAndFlags, CLS); }

class hkBaseObject {
public:
    virtual ~hkBaseObject() {}
};

class hkReferencedObject : public hkBaseObject {
public:
    unsigned short m_memSizeAndFlags;           // +0x4
    short m_referenceCount;                     // +0x6
    // Havok's HK_FORCE_INLINE (contains `delete this`)
    __forceinline void removeReference()
    {
        if (m_memSizeAndFlags != 0) {
            --m_referenceCount;
            if (m_referenceCount == 0)
                delete this;
        }
    }
    int getReferenceCount() const { return m_referenceCount; }
};

class __declspec(align(16)) hkVector4 {
public:
    hkReal x, y, z, w;
    void set(hkReal a, hkReal b, hkReal c, hkReal d = 0.0f) { x = a; y = b; z = c; w = d; }
    void setZero4() { x = y = z = w = 0.0f; }
};

class hkQuaternion {
public:
    hkVector4 m_vec;
};

class hkMatrix3 {
public:
    hkVector4 m_col0, m_col1, m_col2;
    void setZero()
    {
        m_col0.x = 0.0f; m_col0.y = 0.0f; m_col0.z = 0.0f; m_col0.w = 0.0f;
        m_col1.x = 0.0f; m_col1.y = 0.0f; m_col1.z = 0.0f; m_col1.w = 0.0f;
        m_col2.x = 0.0f; m_col2.y = 0.0f; m_col2.z = 0.0f; m_col2.w = 0.0f;
    }
    void mul(hkReal scale);                                          // 0x01081BB0
    void operator=(const hkMatrix3& m);                             // 0x0044A8C0 (out of line)
};

class hkRotation : public hkMatrix3 {
public:
    void set(const hkQuaternion& q);                                 // 0x010824A0
};

class hkTransform {
public:
    hkRotation m_rotation;                      // +0x0
    hkVector4 m_translation;                    // +0x30
};

struct hkAabb {
    hkVector4 m_min;
    hkVector4 m_max;
};

// Retail layout: the float at +0 is the mass the caller copies into hkRigidBodyCinfo.
struct hkMassProperties {
    hkReal m_mass;                              // +0x0
    hkReal m_volume;                            // +0x4
    hkVector4 m_centerOfMass;                   // +0x10
    hkMatrix3 m_inertiaTensor;                  // +0x20
    hkMassProperties() : m_mass(0.0f), m_volume(0.0f)
    {
        m_centerOfMass.setZero4();
        m_inertiaTensor.setZero();
    }
};

class hkShape : public hkReferencedObject {
public:
    int m_userData;                             // +0x8
    virtual void _v4(); virtual void _v8();
    virtual void getAabb(const hkTransform& localToWorld, hkReal tolerance, hkAabb& out) const;  // vtable +0xc
};

#pragma pack(push, 8)
struct hkPropertyValue {
    uint64_t m_data;
    hkPropertyValue(int i) { m_data = i; }
    hkPropertyValue(void* p) { m_data = (uint32_t)p; }
};
#pragma pack(pop)

class hkWorldObject : public hkReferencedObject {
public:
    class hkWorld* m_world;                     // +0x8
    void* m_userData;                           // +0xc
    void addProperty(unsigned int key, hkPropertyValue value);       // 0x010825A0
    void removeReference();                                          // 0x0109AE60 (out of line)
};

struct hkRigidBodyCinfo {
    unsigned int m_collisionFilterInfo;         // +0x0
    hkShape* m_shape;                           // +0x4
    uint32_t pad08[2];
    hkVector4 m_position;                       // +0x10
    hkQuaternion m_rotation;                    // +0x20
    hkVector4 m_linearVelocity;                 // +0x30
    hkVector4 m_angularVelocity;                // +0x40
    hkMatrix3 m_inertiaTensor;                  // +0x50
    hkVector4 m_centerOfMass;                   // +0x80
    hkReal m_mass;                              // +0x90
    hkReal m_linearDamping;                     // +0x94
    hkReal m_angularDamping;                    // +0x98
    hkReal m_friction;                          // +0x9c
    hkReal m_restitution;                       // +0xa0
    hkReal m_maxLinearVelocity;                 // +0xa4
    hkReal m_maxAngularVelocity;                // +0xa8
    hkReal m_allowedPenetrationDepth;           // +0xac
    signed char m_motionType;                   // +0xb0
    signed char m_rigidBodyDeactivatorType;     // +0xb1
    signed char m_solverDeactivation;           // +0xb2
    signed char m_qualityType;                  // +0xb3
    signed char m_autoRemoveLevel;              // +0xb4
    hkRigidBodyCinfo();                                              // 0x01087ED0
};

class hkRigidBody : public hkWorldObject {
public:
    uint32_t pad10[(0x9a - 0x10) / 4];
    unsigned short pad98;
    bool m_9a;                                  // +0x9a
    void setMotionType(int newState, int preferredActivationState, int collisionFilterUpdateMode);  // 0x01087520
    void deactivate();                                               // 0x01088B10
};

class hkPhantom : public hkWorldObject {
public:
    void addPhantomOverlapListener(void* listener);                 // 0x0108E4A0
};

class hkAabbPhantom : public hkPhantom {
public:
    HK_DECLARE_CLASS_ALLOCATOR(0x2e)
    hkAabbPhantom(const hkAabb& aabb, unsigned int collisionFilterInfo);  // 0x0108DFE0
};

class hkSimpleShapePhantom : public hkPhantom {
public:
    HK_DECLARE_CLASS_ALLOCATOR(0x2e)
    hkSimpleShapePhantom(const hkShape* shape, const hkTransform& transform, unsigned int collisionFilterInfo);  // 0x0108C750
};

class hkWorld : public hkReferencedObject {
public:
    hkPhantom* addPhantom(hkPhantom* phantom);                       // 0x01083320
    void addEntity(hkRigidBody* entity, int activation);             // 0x01082EE0
    void FUN_01084fa0(hkRigidBody* body, int a, int b);              // 0x01084FA0
};

// ---------------------------------------------------------------------------
// Spore / EA
// ---------------------------------------------------------------------------
void* operator new(unsigned int n, const char* pName, int flags, unsigned int debugFlags, const char* pFile, int line);

namespace EA { namespace Hash {
    uint32_t FNV1_String8(const char* s, uint32_t seed, int charCase);  // 0x00932E80
} }

struct Vector3 { float x, y, z; };
struct BoundingBox { Vector3 lower, upper; };

namespace App {
class PropertyList {
public:
    virtual int AddRef();
    virtual int Release();
};
}

namespace EA {
template <class T> class AutoRefCount {
public:
    T* mpObject;
    AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    operator T*() const { return mpObject; }
};
}

bool GetBoolProperty(const App::PropertyList* pList, uint32_t id, bool& out);            // 0x00407190
bool GetBoolPropertyDefault(const App::PropertyList* pList, uint32_t id, bool def);      // 0x0064F350
int GetIntPropertyDefault(const App::PropertyList* pList, uint32_t id, int def);         // 0x004E1C30
float GetFloatPropertyDefault(const App::PropertyList* pList, uint32_t id, float def);   // 0x004E1C70
uint32_t GetKeyPropertyDefault(const App::PropertyList* pList, uint32_t id, uint32_t def); // 0x00AC8FA0

namespace SP {

class cPlanetModel {
public:
    float FUN_00b7e490();                                            // 0x00B7E490
};
cPlanetModel* PlanetModel();                                         // 0x00B3D350
void* GetCurrentGameMode();                                          // 0x00B5B800

class cGameData;
struct cPhysicsNounTuning;

class cSpatialObject {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20(); virtual void _v24(); virtual void _v28();
    virtual const Vector3& GetPosition();                            // +0x2c
    virtual const hkQuaternion& GetOrientation();                    // +0x30
    virtual void _v34(); virtual void _v38(); virtual void _v3c(); virtual void _v40();
    virtual void _v44(); virtual void _v48(); virtual void _v4c(); virtual void _v50();
    virtual void _v54(); virtual void _v58(); virtual void _v5c(); virtual void _v60();
    virtual void _v64();
    virtual const BoundingBox& GetLocalExtents();                    // +0x68
    virtual BoundingBox GetWorldExtents();                           // +0x6c
    virtual void _v70(); virtual void _v74(); virtual void _v78(); virtual void _v7c();
    virtual void _v80(); virtual void _v84(); virtual void _v88(); virtual void _v8c();
    virtual void _v90(); virtual void _v94(); virtual void _v98(); virtual void _v9c();
    virtual void _va0(); virtual void _va4(); virtual void _va8(); virtual void _vac();
    virtual void _vb0(); virtual void _vb4();
    virtual void* Cast(uint32_t type);                               // +0xb8

    uint32_t pad04[(0x50 - 0x4) / 4];
    uint32_t mFlags;                            // +0x50
    uint32_t mMaterialType;                     // +0x54
    uint32_t mMaterialTypeOverride;             // +0x58
    uint32_t pad5c[(0x70 - 0x5c) / 4];
    bool mbIsTangible;                          // +0x70
    bool mbFixed;                               // +0x71
    bool mbIsBeingEdited;                       // +0x72
    bool mbModelChanged;                        // +0x73
    bool mbTransformDirty;                      // +0x74
    bool mbEnabled;                             // +0x75
    bool mbInView;                              // +0x76
    bool mbSupported;                           // +0x77
    uint32_t pad78[(0xa4 - 0x78) / 4];
    bool field_A4;                              // +0xa4
    bool field_A5;                              // +0xa5
    bool mbKeepPinnedToPlanet;                  // +0xa6
    bool field_A7;                              // +0xa7
    uint32_t padA8[3];
    float field_B4;                             // +0xb4
};

class cLocomotiveObject : public cSpatialObject {
public:
    const Vector3& GetVelocity();                                    // 0x00D20610
};

class cGonzagoPhysics {
public:
    uint32_t pad00[0x24 / 4];
    bool field_24;                              // +0x24
    bool field_25;                              // +0x25
    bool mbAllowInstantaneousAngleVelocityChange;  // +0x26
    bool field_27;                              // +0x27
    void FUN_00b3e810(cSpatialObject* pObject);                      // 0x00B3E810
};
cGonzagoPhysics* GetGonzagoPhysics();                                // 0x00B3D310

// Locomotive Havok controller ("Simulator" heap, 0x150 bytes).
class cHavokLocomotiveController {
public:
    uint32_t pad00[0x20 / 4];
    bool field_20;                              // +0x20
    float field_24;                             // +0x24
    bool field_28;                              // +0x28
    int field_2c;                               // +0x2c
    uint32_t pad30[(0xc0 - 0x30) / 4];
    float field_c0;                             // +0xc0
    float field_c4;                             // +0xc4
    uint32_t padc8[(0x118 - 0xc8) / 4];
    float field_118;                            // +0x118
    uint32_t pad11c[3];
    float field_128;                            // +0x128
    float field_12c;                            // +0x12c
    uint32_t pad130[(0x150 - 0x130) / 4];
    cHavokLocomotiveController(hkRigidBody* body);                   // 0x00AEFB80
    void SetPosition(const hkVector4& pos);                          // 0x00AEF7E0
    void SetOrientation(const hkQuaternion& q, bool b);              // 0x00AEF530
    void FUN_00aef750(bool b);                                       // 0x00AEF750
    void AddToWorld(hkWorld* world, cPlanetModel* planet);           // 0x00AEF8C0
};

// Spore's gameplay phantom (hkSimpleShapePhantom subclass, 0x140 bytes)
class cGameplayPhantom : public hkSimpleShapePhantom {
public:
    uint32_t pad130[4];
    cGameplayPhantom(const hkShape* shape, const hkTransform& transform, unsigned int collisionFilterInfo);  // 0x00B4D820
};

namespace Havok {

App::PropertyList* GetPhysicsPropList(void* pGameData, const cPhysicsNounTuning* pTuning);   // 0x00B41EE0
hkShape* CreateShape(cSpatialObject* pObject, App::PropertyList* pProps, hkMassProperties* pMassProps,
                     int filterType, int* pLayer, bool bGameplayPhantom);                    // 0x00B55020
void SetupRigidBodyInfo(hkRigidBodyCinfo* pInfo, hkMassProperties* pMassProps, App::PropertyList* pProps);  // 0x00B4FC80
hkRigidBody* CreateRigidBody(hkRigidBodyCinfo* pInfo);                                       // 0x00B4D880
void FUN_00b4d7a0(hkRigidBody* body, float mass, bool b);                                    // 0x00B4D7A0
void FUN_00b523e0(cSpatialObject* pObject, hkRigidBody* body);                               // 0x00B523E0
void FUN_00b55680(cSpatialObject* pObject, hkRigidBody* body, int a);                        // 0x00B55680
void FUN_00b54000(cSpatialObject* pObject, hkAabbPhantom* phantom);                          // 0x00B54000
int FUN_00ae66f0(cSpatialObject* pObject);                                                   // 0x00AE66F0

void CreateHavokEntityForObject(cGameData* pGameData, cSpatialObject* pObject,
                                cLocomotiveObject* pLocomotive, const cPhysicsNounTuning* pTuning);

}  // namespace Havok
}  // namespace SP

// ---------------------------------------------------------------------------
// eastl::hash_map<cSpatialObject*, T*> (find / operator[] are shared out-of-line instances)
// ---------------------------------------------------------------------------
namespace eastl {
template <class V> struct hash_node {
    V mValue;
    hash_node* mpNext;
};

struct hashtable_iterator_base {
    void* mpNode;
    void** mpBucket;
    hashtable_iterator_base(void** pBucket) : mpNode(*pBucket), mpBucket(pBucket) {}
    hashtable_iterator_base(const hashtable_iterator_base& x) : mpNode(x.mpNode), mpBucket(x.mpBucket) {}
};
inline bool operator==(const hashtable_iterator_base& a, const hashtable_iterator_base& b) { return a.mpNode == b.mpNode; }
inline bool operator!=(const hashtable_iterator_base& a, const hashtable_iterator_base& b) { return a.mpNode != b.mpNode; }

template <typename K, typename V> class hash_map {
public:
    typedef hashtable_iterator_base iterator;
    uint32_t mRehashBase;
    void** mpBucketArray;                       // +0x4
    uint32_t mnBucketCount;                     // +0x8
    uint32_t mnElementCount;                    // +0xc
    iterator find(const K& k);                                       // 0x00645ED0
    V& operator[](const K& k);                                       // 0x00B54750
    iterator end() { return iterator(mpBucketArray + mnBucketCount); }
};
}

// ---------------------------------------------------------------------------
// Globals
// ---------------------------------------------------------------------------
extern char g_kGameModeAdventure;                                    // 0x01654C10
extern hkWorld* g_pHavokWorld;                                       // 0x0167ECD0
extern bool g_bHavokActivateAll;                                     // 0x0167ECD9
extern eastl::hash_map<SP::cSpatialObject*, hkRigidBody*> g_HavokRigidBodies;            // 0x016801A8
extern eastl::hash_map<SP::cSpatialObject*, hkSimpleShapePhantom*> g_HavokShapePhantoms; // 0x016815F8
extern eastl::hash_map<SP::cSpatialObject*, hkSimpleShapePhantom*> g_HavokGameplayPhantoms; // 0x01682A48
extern eastl::hash_map<SP::cSpatialObject*, hkAabbPhantom*> g_HavokAabbPhantoms;         // 0x016852E8
extern eastl::hash_map<SP::cSpatialObject*, SP::cHavokLocomotiveController*> g_HavokControllers;  // 0x0167ED58
extern float g_kMaxLinearVelocity;                                   // 0x01569AA8
extern float g_kMaxAngularVelocity;                                  // 0x01569AAC
extern float g_kGravity;                                             // 0x01569AA4
extern float g_kMaxScale;                                            // 0x015695F8
extern float g_kInertiaScale;                                        // 0x01569B08
extern float g_kStepHeightRatio;                                     // 0x01569CE0
extern float g_kDefaultSlope;                                        // 0x01567258
extern float g_kAabbTolerance;                                       // 0x01569AB4
extern bool g_bTrackAabbPhantoms;                                    // 0x01569AB8
extern char g_PhantomOverlapListener;                                // 0x01569CD8

#pragma pack(pop)

using namespace SP;

void SP::Havok::CreateHavokEntityForObject(cGameData* pGameData, cSpatialObject* pObject,
                                           cLocomotiveObject* pLocomotive, const cPhysicsNounTuning* pTuning)
{
    cGonzagoPhysics* pPhysics = GetGonzagoPhysics();
    bool bIsAdventure = GetCurrentGameMode() == &g_kGameModeAdventure;

    if (g_HavokRigidBodies.find(pObject) != g_HavokRigidBodies.end())
        return;
    if (!pObject->mbEnabled)
        return;
    if (!pObject->mbIsTangible)
        return;

    EA::AutoRefCount<App::PropertyList> pProps(GetPhysicsPropList(pObject->Cast(0x17f243b), pTuning));

    bool bIsPhantom = false;
    GetBoolProperty(pProps, 0xfce2ced5, bIsPhantom);

    const BoundingBox& extents = pObject->GetLocalExtents();
    Vector3 size;
    size.x = extents.upper.x - extents.lower.x;
    size.y = extents.upper.y - extents.lower.y;
    size.z = extents.upper.z - extents.lower.z;

    hkTransform transform;
    int filterType = 0;
    if (pLocomotive)
        filterType = 2;

    static uint32_t kUseGameplayPhantom = EA::Hash::FNV1_String8("useGameplayPhantom", 0x811c9dc5, 1);
    bool bUseGameplayPhantom = GetBoolPropertyDefault(pProps, kUseGameplayPhantom, false);
    if (bUseGameplayPhantom && bIsAdventure &&
        g_HavokGameplayPhantoms.find(pObject) == g_HavokGameplayPhantoms.end())
    {
        hkMassProperties massProps;
        int layer;
        hkShape* pShape = CreateShape(pObject, pProps, &massProps, 0, &layer, true);
        if (!pShape)
            return;

        hkQuaternion orientation = pObject->GetOrientation();
        const BoundingBox& box = pObject->GetWorldExtents();
        transform.m_translation.set((box.lower.x + box.upper.x) * 0.5f,
                                    (box.upper.y + box.lower.y) * 0.5f,
                                    (box.upper.z + box.lower.z) * 0.5f, 0.0f);
        transform.m_rotation.set(orientation);

        cGameplayPhantom* pPhantom = new cGameplayPhantom(pShape, transform, 10);
        pShape->removeReference();
        pPhantom->m_userData = pGameData;
        pPhantom->addProperty(0, 3);
        pPhantom->addProperty(6, layer == 2);
        g_HavokGameplayPhantoms[pObject] = pPhantom;
        g_pHavokWorld->addPhantom(pPhantom);
        bool bLastRef = pPhantom->getReferenceCount() == 1;
        pPhantom->removeReference();
        if (bLastRef)
            return;
    }

    static uint32_t kHasCollision = EA::Hash::FNV1_String8("hasCollision", 0x811c9dc5, 1);
    if (!GetBoolPropertyDefault(pProps, kHasCollision, true))
        return;

    hkMassProperties massProps;
    int layer;
    hkShape* pShape = CreateShape(pObject, pProps, &massProps, filterType, &layer, false);
    if (!pShape)
        return;

    bool bKeepActive = GetBoolPropertyDefault(pProps, 0x5b1530ff, false);
    bool bTutorial = GetBoolPropertyDefault(pProps, 0x3300820b, false);
    int tutorialType = GetIntPropertyDefault(pProps, 0x87f3291f, 0);
    uint32_t material = pObject->mMaterialTypeOverride;
    if (!material)
        material = pObject->mMaterialType;
    pObject->mMaterialType = GetKeyPropertyDefault(pProps, 0x93336c12, material);

    hkRigidBody* pBody;
    if (pLocomotive && !bIsPhantom)
    {
        hkRigidBodyCinfo info;
        info.m_shape = pShape;
        const Vector3& pos = pLocomotive->GetPosition();
        info.m_position.set(pos.x, pos.y, pos.z, 0.0f);
        const Vector3& vel = pLocomotive->GetVelocity();
        info.m_linearVelocity.set(vel.x, vel.y, vel.z, 0.0f);
        info.m_linearDamping = 10.0f;
        info.m_angularDamping = 10.0f;
        info.m_restitution = 0.1f;
        info.m_motionType = 1;
        info.m_collisionFilterInfo = 2;
        info.m_friction = 0.0f;
        info.m_mass = massProps.m_mass;
        info.m_inertiaTensor = massProps.m_inertiaTensor;
        info.m_centerOfMass = massProps.m_centerOfMass;
        info.m_maxLinearVelocity = g_kMaxLinearVelocity;
        info.m_maxAngularVelocity = g_kMaxAngularVelocity;
        if (bIsAdventure)
            info.m_qualityType = 6;
        SetupRigidBodyInfo(&info, &massProps, pProps);

        float scale = GetFloatPropertyDefault(pProps, 0x5c74d18b, 1.0f);
        float maxScale = g_kMaxScale * 0.9f;
        float s;
        if (scale < 0.1f)
            s = 0.1f;
        else if (scale > maxScale)
            s = maxScale;
        else
            s = scale;
        info.m_mass = s * info.m_mass;
        info.m_inertiaTensor.mul(s * g_kInertiaScale);

        if (pPhysics->mbAllowInstantaneousAngleVelocityChange)
            info.m_rigidBodyDeactivatorType = 1;
        if (bTutorial)
        {
            switch (tutorialType)
            {
            case 0: info.m_collisionFilterInfo = 9; break;
            case 1: info.m_collisionFilterInfo = 8; break;
            }
            pObject->mFlags |= 0x2000;
        }

        pBody = CreateRigidBody(&info);
        pBody->m_userData = pGameData;
        pBody->addProperty(6, layer == 2);
        pBody->addProperty(0, 3);
        pBody->addProperty(1, pGameData);
        pBody->addProperty(7, 0);
        pBody->addProperty(9, bUseGameplayPhantom);
        FUN_00b4d7a0(pBody, massProps.m_mass, bKeepActive);

        cHavokLocomotiveController* pController = new("Simulator", 0, 0, 0, 0) cHavokLocomotiveController(pBody);
        pBody->removeReference();
        pController->field_118 = size.z * 0.3f;
        pController->field_128 = size.z * 0.5f;
        pController->field_12c = -(g_kGravity * g_kMaxLinearVelocity * 2.0f);
        pController->SetPosition(info.m_position);
        hkQuaternion orientation = pLocomotive->GetOrientation();
        pController->SetOrientation(orientation, true);
        pController->field_20 = pPhysics->field_27;
        pController->FUN_00aef750(pPhysics->mbAllowInstantaneousAngleVelocityChange);
        pController->field_c0 = PlanetModel()->FUN_00b7e490();
        pController->field_c4 = g_kMaxLinearVelocity;
        pController->field_24 = GetFloatPropertyDefault(pProps, 0xc270ba07, g_kDefaultSlope);
        if (FUN_00ae66f0(pObject))
        {
            float limit = size.z * g_kStepHeightRatio;
            if (size.x > limit || size.y > limit)
                pController->field_24 = 0.0f;
        }
        pController->field_28 = GetBoolPropertyDefault(pProps, 0x2265da65, true);
        pController->field_2c = GetIntPropertyDefault(pProps, 0xe6ab7b3e, 0);
        pBody->addProperty(4, pController);
        g_HavokControllers[pObject] = pController;
        pController->AddToWorld(g_pHavokWorld, PlanetModel());
        if (pObject->mbSupported)
            pPhysics->FUN_00b3e810(pObject);
    }
    else if (bIsPhantom)
    {
        hkQuaternion orientation = pObject->GetOrientation();
        const BoundingBox& box = pObject->GetWorldExtents();
        transform.m_translation.set((box.lower.x + box.upper.x) * 0.5f,
                                    (box.upper.y + box.lower.y) * 0.5f,
                                    (box.upper.z + box.lower.z) * 0.5f, 0.0f);
        transform.m_rotation.set(orientation);

        hkSimpleShapePhantom* pPhantom = new hkSimpleShapePhantom(pShape, transform, 10);
        pPhantom->m_userData = pGameData;
        pPhantom->addProperty(0, 3);
        g_pHavokWorld->addPhantom(pPhantom);
        pPhantom->removeReference();
        pShape->removeReference();
        g_HavokShapePhantoms[pObject] = pPhantom;
        return;
    }
    else
    {
        hkRigidBodyCinfo info;
        info.m_motionType = 1;
        info.m_inertiaTensor = massProps.m_inertiaTensor;
        info.m_centerOfMass = massProps.m_centerOfMass;
        info.m_mass = massProps.m_mass;
        info.m_angularDamping = 0.3f;
        info.m_linearDamping = 0.3f;
        info.m_friction = 0.3f;
        info.m_maxLinearVelocity = g_kMaxLinearVelocity;
        info.m_collisionFilterInfo = 4;
        info.m_restitution = 0.1f;
        info.m_shape = pShape;
        info.m_maxAngularVelocity = g_kMaxAngularVelocity;
        SetupRigidBodyInfo(&info, &massProps, pProps);

        float scale = GetFloatPropertyDefault(pProps, 0x5c74d18b, 1.0f);
        info.m_mass = scale * info.m_mass;
        info.m_inertiaTensor.mul(scale);

        if (bTutorial)
        {
            switch (tutorialType)
            {
            case 0: info.m_collisionFilterInfo = 9; break;
            case 1: info.m_collisionFilterInfo = 8; break;
            }
            pObject->mFlags |= 0x2000;
        }
        if (pObject->mFlags & 0x80)
            info.m_collisionFilterInfo = 5;

        pBody = CreateRigidBody(&info);
        pShape->removeReference();
        pBody->m_userData = pGameData;
        pBody->addProperty(6, layer == 2);
        pBody->addProperty(0, 3);
        pBody->addProperty(1, pGameData);
        pBody->addProperty(7, 0);
        FUN_00b4d7a0(pBody, massProps.m_mass, bKeepActive);
        FUN_00b523e0(pObject, pBody);
        g_HavokRigidBodies[pObject] = pBody;
        if (pObject->mbFixed)
            pBody->setMotionType(7, 1, 0);

        bool bActivate = g_bHavokActivateAll;
        if (!bActivate && !pBody->m_9a && pObject->field_A7 && pObject->field_B4 > 0.0f)
            bActivate = true;
        g_pHavokWorld->addEntity(pBody, bActivate ? 1 : 0);
        bool bLastRef = pBody->getReferenceCount() == 1;
        pBody->removeReference();
        if (!bLastRef)
        {
            g_pHavokWorld->FUN_01084fa0(pBody, 0, 0);
            if (pObject->mbSupported)
                FUN_00b55680(pObject, pBody, 0);
            if (!bActivate)
                pBody->deactivate();
        }
    }

    if (bTutorial)
    {
        hkQuaternion orientation = pObject->GetOrientation();
        const BoundingBox& box = pObject->GetWorldExtents();
        transform.m_translation.set((box.upper.x + box.lower.x) * 0.5f,
                                    (box.upper.y + box.lower.y) * 0.5f,
                                    (box.upper.z + box.lower.z) * 0.5f, 0.0f);
        transform.m_rotation.set(orientation);
        hkAabb aabb;
        pShape->getAabb(transform, g_kAabbTolerance, aabb);

        hkAabbPhantom* pAabbPhantom = new hkAabbPhantom(aabb, 0xb);
        pAabbPhantom->m_userData = pBody;
        pAabbPhantom->addProperty(0, 5);
        pAabbPhantom->addPhantomOverlapListener(&g_PhantomOverlapListener);
        g_pHavokWorld->addPhantom(pAabbPhantom);
        pAabbPhantom->removeReference();
        g_HavokAabbPhantoms[pObject] = pAabbPhantom;
        if (g_bTrackAabbPhantoms)
            FUN_00b54000(pObject, pAabbPhantom);
    }
}
