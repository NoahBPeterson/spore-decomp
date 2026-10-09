// Slice s00b57c40 (batch big0 / op1_big) — 0x00b57c40, 9746 bytes.
//
// SP::cGonzagoPhysics::UpdateHavok(unsigned int deltaMs)
//
// Identification: the old "rw::audio::core::Layer3Dec::Decode" caller-scored PDB
// candidate was wrong.  The body calls SP::PlanetModel / cPlanetModel::
// GetWaterHeight, hkWorld::stepDeltaTime, hkRigidBody::setMotionType, Havok
// overlap collectors and nSPCreatureAnim::creature_instance_data::HitBody, and it
// keeps two stack `spstl::sp_fixed_vector<SP::Havok::cGonzagoHavokObject,256>`
// (12-byte elements, 0xc00-byte inline buffers).  The dev PDB has exactly one
// function of that shape: SP::cGonzagoPhysics::UpdateHavok (10339 B, module
// SPGonzagoPhysicsHavok.obj).  Its only caller (0x00b4c5b9, the cGonzagoPhysics
// update) calls it when mPhysicsMode == 0 and the Havok world exists.
//
// Retail field offsets differ from the 2008 dev PDB (the entity vector is at
// +0x60 here, +0x34 in the dev layout), so the classes below use retail offsets.
// Callees without a recovered name keep their FUN_ address names.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (SSE scalar float math mixed with
// x87 sqrt; no EH frame although the fixed vectors and collectors have dtors, so
// the module is built without /EHsc).

#include "types.h"
#include <math.h>
#include <new>

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long index);

// ---------------------------------------------------------------------------
// Math
// ---------------------------------------------------------------------------

struct Vector3 {
    float x, y, z;
};

struct __declspec(align(16)) hkVector4 {
    float x, y, z, w;
};

struct Quat {
    float x, y, z, w;
};

namespace SP {
    Vector3 normalized_safe(const Vector3& v);       // 0x00449c20
}

// v rotated by the inverse (conjugate) of unit quaternion q (expanded form).
static inline Vector3 InvRotate(const Quat& q, const Vector3& d)
{
    float xw = -(q.x * q.w);
    float yw = q.y * q.w;
    float zw = -(q.z * q.w);
    float xx = -(q.x * q.x);
    float xy = q.y * q.x;
    float xz = q.z * q.x;
    float yy = -(q.y * q.y);
    float yz = q.z * q.y;
    float zz = -(q.z * q.z);
    Vector3 r;
    r.x = (((xy - zw) * d.y + (xz + -yw) * d.z) + (zz + yy) * d.x) * 2.0f + d.x;
    r.y = (((zz + xx) * d.y + (yz - xw) * d.z) + (xy + zw) * d.x) * 2.0f + d.y;
    r.z = (((yy + xx) * d.z + (yz + xw) * d.y) + (xz - -yw) * d.x) * 2.0f + d.z;
    return r;
}

// v rotated by unit quaternion q (expanded form).
static inline Vector3 Rotate(const Quat& q, const Vector3& v)
{
    float xw = q.x * q.w;
    float yw = q.y * q.w;
    float zw = q.z * q.w;
    float xx = -(q.x * q.x);
    float yy = -(q.y * q.y);
    float zz = -(q.z * q.z);
    float xy = q.y * q.x;
    float xz = q.z * q.x;
    float yz = q.z * q.y;
    Vector3 r;
    r.x = (((zz + yy) * v.x + (xz + yw) * v.z) + (xy - zw) * v.y) * 2.0f + v.x;
    r.y = (((zz + xx) * v.y + (xy + zw) * v.x) + (yz - xw) * v.z) * 2.0f + v.y;
    r.z = (((yy + xx) * v.z + (xz - yw) * v.x) + (yz + xw) * v.y) * 2.0f + v.z;
    return r;
}

// hkVector4::normalize3 with a zero-length check; w is scaled by the same factor.
static inline void NormalizeIfNotZero3(hkVector4& v)
{
    float len2 = (v.z * v.z + v.y * v.y) + v.x * v.x;
    float inv;
    if (len2 == 0.0f)
        inv = 0.0f;
    else
        inv = 1.0f / sqrtf(len2);
    v.x = inv * v.x;
    v.y = inv * v.y;
    v.z = inv * v.z;
    v.w = inv * v.w;
}

// eastl::max(a, b): (a < b) ? b : a
static inline const float& Max(const float& a, const float& b) { return (a < b) ? b : a; }
// eastl::min(a, b): (b < a) ? b : a
static inline const float& Min(const float& a, const float& b) { return (b < a) ? b : a; }

// ---------------------------------------------------------------------------
// Havok (3.1) pieces used here
// ---------------------------------------------------------------------------

struct hkBool { char m_bool; };

struct hkPropertyValue {
    uint32_t lo;          // getInt() / getPtr()
    uint32_t hi;
    hkPropertyValue() {}
    hkPropertyValue(int v) : lo((uint32_t)v), hi(0) {}
};

struct hkProperty {
    uint32_t m_key;
    uint32_t m_alignmentPadding;
    hkPropertyValue m_value;
};

class hkThreadMemory {
public:
    void deallocateChunk(void* p, int nbytes, int cls);       // 0x0107db10
    static unsigned long s_threadMemoryInstance;              // TLS slot (0x016e4174)
    static hkThreadMemory& getInstance() { return *(hkThreadMemory*)TlsGetValue(s_threadMemoryInstance); }
};

class hkRigidMotion {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24();
    virtual void applyPointImpulse(const hkVector4& imp, const hkVector4& p);   // +0x64
    virtual void v26(); virtual void v27();
    virtual void applyForce(float deltaTime, const hkVector4& force);           // +0x70

    float getMass() const;                                     // 0x01088270

    uint32_t pad04[(0x40 - 0x04) / 4];
    hkVector4 m_position;           // +0x40 (motion state transform translation)
    uint32_t pad50[(0x60 - 0x50) / 4];
    hkVector4 m_centerOfMass;       // +0x60
    uint32_t pad70[(0xd0 - 0x70) / 4];
    hkVector4 m_linearVelocity;     // +0xd0
    hkVector4 m_angularVelocity;    // +0xe0
};

class hkEntity;

struct hkCollidable {
    uint32_t pad00[4];
    int m_ownerOffset;              // +0x10
    uint32_t pad14;
    uint8_t m_broadPhaseType;       // +0x18 (1 = entity)
    hkEntity* getOwner() const { return (hkEntity*)((char*)this + m_ownerOffset); }
};

class cGameObjectBase;

class hkEntity {
public:
    uint32_t pad00[3];
    cGameObjectBase* m_userData;    // +0x0c
    uint32_t pad10[(0x4c - 0x10) / 4];
    hkProperty* m_properties;       // +0x4c (hkArray<hkProperty>)
    int m_numProperties;            // +0x50
    uint32_t pad54;
    hkRigidMotion* m_motion;        // +0x58
    uint32_t pad5c[(0x99 - 0x5c) / 4];
    uint8_t pad98;
    uint8_t m_fixedOrKeyframed;     // +0x99
    uint8_t m_keyframed;            // +0x9a

    hkPropertyValue getProperty(uint32_t key) const;           // 0x00496140
    hkPropertyValue editProperty(uint32_t key, hkPropertyValue v);  // 0x01082600
    hkBool isActive() const;                                   // 0x01088ac0
    void activate();                                           // 0x01088ae0
    void deactivate();                                         // 0x01088b10
    void setMotionType(int type, int activation, int filterUpdate);  // 0x01087520 (hkRigidBody)

    // hkWorldObject::getProperty, inlined form.
    hkPropertyValue findProperty(uint32_t key) const
    {
        for (int i = 0; i < m_numProperties; i++)
        {
            if (m_properties[i].m_key == key)
                return m_properties[i].m_value;
        }
        return hkPropertyValue(0);
    }
};
typedef hkEntity hkRigidBody;

// hkAllCdBodyPairCollector-like collector with an hkInplaceArray<hit,16>.
struct OverlapHit {
    uint32_t a, b;
    hkCollidable* m_collidable;     // +0x08
    uint32_t c;
};

class OverlapCollector {
public:
    virtual ~OverlapCollector()
    {
        if (m_capacityAndFlags >= 0)
            hkThreadMemory::getInstance().deallocateChunk(
                m_data, (m_capacityAndFlags & 0x3fffffff) * (int)sizeof(OverlapHit), 0x14);
    }
    virtual void addCdBodyPair(const void* a, const void* b);
    OverlapCollector() : m_earlyOut(0), m_data(m_storage), m_size(0), m_capacityAndFlags((int)0x80000010) {}
    void reset() { m_size = 0; m_earlyOut = 0; }

    uint8_t m_earlyOut;             // +0x04
    OverlapHit* m_data;             // +0x08
    int m_size;                     // +0x0c
    int m_capacityAndFlags;         // +0x10
    OverlapHit m_storage[16];       // +0x14
};

class hkPhantom {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13();
    virtual void getOverlaps(OverlapCollector& collector);    // +0x38
    uint32_t pad04[2];
    void* m_userData;               // +0x0c
};

class hkWorld {
public:
    int stepDeltaTime(float dt);                               // 0x01082a90
};

// ---------------------------------------------------------------------------
// Spore pieces
// ---------------------------------------------------------------------------

struct BBox { float minX, minY, minZ, maxX, maxY, maxZ; };

class cGameObjectBase {
public:
    virtual void v00(); virtual void v01(); virtual void v02();
    virtual cGameObjectBase* Cast(uint32_t id);               // +0x0c
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual uint32_t GetTypeID();                              // +0x20
    virtual void v09(); virtual void v10(); virtual void v11(); virtual void v12();
    virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
    virtual void v17();
    virtual bool IsAlive();                                    // +0x48
    virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22();
    virtual void v23(); virtual void v24(); virtual void v25();
    virtual const BBox* GetBoundingBox();                      // +0x68
    virtual void v27(); virtual void v28();
    virtual float GetRadius();                                 // +0x74
};

struct cGameData {
    uint32_t pad00[8];
    uint8_t mbIsDestroyed;          // +0x20
};

struct cCollisionInfo {             // SP::cCollisionInfo (0x70 bytes used here)
    uint32_t collisionType;         // +0x00
    float data[(0x68 - 0x04) / 4];
    cGameData* pGameDataA;          // +0x68
    cGameData* pGameDataB;          // +0x6c
    cCollisionInfo();                                          // 0x00b3d8c0
};

struct cHitTarget {                 // object found through the cast id 0xd0036e08
    uint32_t pad[0xb58 / 4];
    uint32_t mFlags;                // +0xb58 (bit 9 used)
};

class cSpatialObject {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10();
    virtual const Vector3& GetPosition();                      // +0x2c
    virtual const Quat& GetOrientation();                      // +0x30
    virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
    virtual void v17();
    virtual bool IsMoving();                                   // +0x48
    virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22();
    virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26();
    virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30();
    virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34();
    virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38();
    virtual void v39(); virtual void v40(); virtual void v41(); virtual void v42();
    virtual void v43(); virtual void v44(); virtual void v45();
    virtual void* Cast(uint32_t id);                           // +0xb8
    virtual void v47(); virtual void v48(); virtual void v49(); virtual void v50();
    virtual void v51();
    virtual float GetMaxAcceleration();                        // +0xd0
    virtual float GetMaxDeceleration();                        // +0xd4
    virtual void v54(); virtual void v55(); virtual void v56(); virtual void v57();
    virtual void v58(); virtual void v59(); virtual void v60(); virtual void v61();
    virtual bool IsOnPlanetSurface();                          // +0xf8

    float GetAltitude();                                       // 0x00c887c0

    uint32_t pad04[(0x50 - 0x04) / 4];
    uint32_t mFlags;                // +0x50 (bit0 dirty, bit12 ground contact)
    uint32_t pad54[(0x70 - 0x54) / 4];
    uint8_t pad70;
    uint8_t mbFixed;                // +0x71
    uint8_t pad72[3];
    uint8_t mbPhysicsEnabled;       // +0x75
    uint8_t pad76;
    uint8_t mbOnGround;             // +0x77
};

struct ForceEntry {
    Vector3 force;
    int type;                       // 1 = cancels velocity
};

class cLocomotiveObject : public cSpatialObject {
public:
    const Vector3& GetVelocity();                              // 0x00d20610
    void UpdateJump(uint32_t deltaMs);                         // 0x00c431a0
    void ApplyGravityDirection(const Vector3& g);              // 0x00c41d60

    uint32_t pad78[(0xf0 - 0x78) / 4];
    ForceEntry* mForcesBegin;       // +0xf0
    ForceEntry* mForcesEnd;         // +0xf4
    uint32_t padf8[(0x1f0 - 0xf8) / 4];
    int mMovementType;              // +0x1f0
    uint32_t pad1f4[(0x268 - 0x1f4) / 4];
    uint8_t mbJumping;              // +0x268
    uint8_t pad269[0x274 - 0x269];
    uint8_t mbInWater;              // +0x274

    void ClearForces()
    {
        // eastl::vector::erase(begin(), end())
        ForceEntry* first = mForcesBegin;
        ForceEntry* last = mForcesEnd;
        ForceEntry* d = first;
        for (ForceEntry* s = last; s != mForcesEnd; ++s, ++d)
            *d = *s;
        mForcesEnd -= (last - first);
    }
};

class SPCreatureProxy {
public:
    void SetEnabled(bool b);                                   // 0x00aef690
    void SetActive(bool b);                                    // 0x00aef750
    const hkVector4& GetGroundPlane();                         // 0x00aef400
    void ApplyForce(const hkVector4& f);                       // 0x00aef570
    void SetVelocity(const hkVector4& v);                      // 0x00aef3d0
    hkRigidBody* GetBody();                                    // 0x00aef2e0
    void Update(float dt);                                     // 0x00aefc80

    uint32_t pad00[0x34 / 4];
    uint8_t mbSwimming;             // +0x34
    uint8_t pad35[0xb0 - 0x35];
    float mMass;                    // +0xb0
    float mFriction;                // +0xb4
    uint32_t padb8;
    uint8_t mbApplyGravity;         // +0xbc
    uint8_t padbd[3];
    float mGravity;                 // +0xc0
    uint32_t padc4;
    uint8_t mbFlying;               // +0xc8
    uint8_t mbHovering;             // +0xc9
    uint8_t mbInWater;              // +0xca
    uint8_t padcb;
    int mGroundContacts;            // +0xcc
};

class cPlanetModel {
public:
    float GetGravity();                                        // 0x00b7e490
    float GetWaterHeight();                                    // 0x00b7e390
};

namespace SP {
    cPlanetModel* PlanetModel();                               // 0x00b3d350
    uint32_t GetCurrentGameMode();                             // 0x00b5b800
}

struct creature_body_static {
    uint32_t pad[0x138 / 4];
    float extents[3];               // +0x138
    uint32_t pad144[(0x150 - 0x144) / 4];
    uint8_t flags;                  // +0x150
};

struct creature_body_instance {     // 700 bytes
    creature_body_static* data;     // +0x00
    uint32_t pad04[3];
    Vector3 pos;                    // +0x10
    Quat rot;                       // +0x1c
    uint8_t rest[700 - 0x2c];
};

struct creature_static_data {
    uint32_t pad[0x370 / 4];
    float mAvgLegLength;            // +0x370
};

struct creature_instance_data {
    creature_static_data* static_data;     // +0x00
    uint32_t pad04[5];
    Vector3 requested_pos;                 // +0x18
    uint32_t pad24[(0x3c - 0x24) / 4];
    Quat requested_rot;                    // +0x3c
    uint32_t pad4c[(0x70 - 0x4c) / 4];
    float requested_scale;                 // +0x70
    uint32_t pad74[(0x2e4 - 0x74) / 4];
    creature_body_instance* bodiesBegin;   // +0x2e4
    creature_body_instance* bodiesEnd;     // +0x2e8

    void HitBody(unsigned idx, const Vector3& impulse, bool a, bool b, float scale);  // 0x009bb680
};

struct cCreatureAnimHolder {
    int GetLOD();                                              // 0x00a02bd0
    uint32_t pad[0x17c / 4];
    creature_instance_data* mpInstance;    // +0x17c
};

struct cCreatureObject {
    cCreatureAnimHolder* GetAnimatedCreature();                // 0x00c3e790
};

// ---- containers ------------------------------------------------------------

// eastl::hashtable (bucket array + count); nodes { key, value, next } or { value, next }.
template <typename N>
struct HashTable {
    N** mpBucketArray;
    uint32_t mnBucketCount;

    struct iterator {
        N* mpNode;
        N** mpBucket;
        void increment()
        {
            mpNode = mpNode->mpNext;
            while (mpNode == 0)
                mpNode = *++mpBucket;
        }
    };
    iterator begin()
    {
        iterator it;
        it.mpBucket = mpBucketArray;
        it.mpNode = *it.mpBucket;
        if (it.mpNode == 0)
        {
            ++it.mpBucket;
            while (*it.mpBucket == 0)
                ++it.mpBucket;
            it.mpNode = *it.mpBucket;
        }
        return it;
    }
    N* endNode() { return mpBucketArray[mnBucketCount]; }

    template <typename K>
    N* findNode(K key)
    {
        uint32_t n = (uint32_t)key % mnBucketCount;
        for (N* p = mpBucketArray[n]; p; p = p->mpNext)
            if (p->first == key)
                return p;
        return mpBucketArray[mnBucketCount];
    }
};

template <typename K, typename V>
struct MapNode {
    K first;
    V second;
    MapNode* mpNext;
};

template <typename K>
struct SetNode {
    K first;
    SetNode* mpNext;
};

// spstl::sp_fixed_vector<SP::Havok::cGonzagoHavokObject,256>
struct cGonzagoHavokObject {
    void* mpObject;                 // entity / spatial object
    void* mpBody;                   // SPCreatureProxy* or hkRigidBody*
    bool mbFlag;
};

struct GonzagoObjectVector {
    cGonzagoHavokObject* mpBegin;
    cGonzagoHavokObject* mpEnd;
    cGonzagoHavokObject* mpCapacity;
    uint32_t mAllocator;
    uint32_t mPadding;
    uint32_t mBufferHeader;         // 0 = inline buffer, nonzero = heap block
    cGonzagoHavokObject mBuffer[256];

    GonzagoObjectVector()
    {
        mpBegin = mBuffer;
        mpEnd = mBuffer;
        mpCapacity = mBuffer + 256;
        mBufferHeader = 0;
    }
    ~GonzagoObjectVector()
    {
        if (mpBegin && ((uint32_t*)mpBegin)[-1] != 0)
            operator delete[](mpBegin);
    }
    void DoInsertValue(cGonzagoHavokObject* pos, const cGonzagoHavokObject& v);  // 0x00b535d0
    void push_back(const cGonzagoHavokObject& v)
    {
        if (mpEnd < mpCapacity)
            ::new ((void*)mpEnd++) cGonzagoHavokObject(v);
        else
            DoInsertValue(mpEnd, v);
    }
};

// ---- globals ---------------------------------------------------------------

extern HashTable<MapNode<cLocomotiveObject*, SPCreatureProxy*> > g_CreatureProxies;  // 0x0167ed5c
extern HashTable<MapNode<cSpatialObject*, hkRigidBody*> > g_RigidBodies;             // 0x016801ac
extern HashTable<MapNode<void*, hkPhantom*> > g_TriggerPhantoms;                     // 0x01682a4c
extern HashTable<MapNode<cGameObjectBase*, hkPhantom*> > g_CreaturePhantoms;         // 0x016815fc
extern hkPhantom** g_ForcePhantomsBegin;   // 0x01569c00
extern hkPhantom** g_ForcePhantomsEnd;     // 0x01569c04

extern hkWorld* g_pHavokWorld;             // 0x0167ecd0
extern bool g_bFixedTimeStep;              // 0x0167ecd8
extern void* g_pHavokListener;             // 0x0167ecdc
extern bool g_bIcePlanet;                  // 0x0167eb74
extern Vector3 g_Vector3Zero;           // 0x0167ecf4
extern hkVector4 g_hkVector4Zero;             // 0x016e42d0

extern float g_MaxSpeedForIdle;            // 0x01569acc (75.0)
extern float g_MaxAltitudeForPhysics;      // 0x01569ac4 (75.0)
extern float g_MinAltitudeForPhysics;      // 0x01569ac8 (50.0)
extern float g_PhantomPushStrength;        // 0x01569ad8 (10.0)
extern float g_JumpPadSpeed;               // 0x01569adc (50.0)
extern float g_JumpPadPush;                // 0x01569ae0 (5.0)
extern float g_HitBodyScale;               // 0x01569ce4 (1.0)
extern float g_HitLinearScale;             // 0x01569ce8 (4.0)
extern float g_HitAngularBias;             // 0x01569cec (0.6)
extern float g_MaxHitImpulse;              // 0x01569cf0 (20.0)
extern float g_BodyExtentScale;            // 0x01569cf4 (0.5)
extern float g_HitRadiusScale;             // 0x01569cf8 (0.6)
extern float g_MinHitSpeedSq;              // 0x01569cfc (1e-5)

// ---- free functions --------------------------------------------------------

bool  FUN_0059ab70(const Vector3* v);                          // vector validity
void  FUN_00b537f0(cLocomotiveObject* e, SPCreatureProxy* p, bool a, bool b);
void  FUN_00b4b040(cLocomotiveObject* e, uint32_t deltaMs, bool farAway);
void  FUN_00b523e0(cSpatialObject* o, hkRigidBody* b);
bool  FUN_00b4ed50(float dt, void* object, void* entity, hkRigidBody* body, float waterHeight, float gravity);
void  FUN_00b65820(hkRigidBody* b, const hkVector4* v);
void  FUN_00f31220(cCollisionInfo* info);                      // collision message
void  FUN_00b3d3b0();
void  FUN_00b4dd70(cLocomotiveObject* e, SPCreatureProxy* p);
void  FUN_00b421b0(cLocomotiveObject* e, bool flag, const Vector3& pos, const Quat& rot);
void  FUN_00b52230(cSpatialObject* o, hkRigidBody* b);
void  FUN_00b4e1d0(void* key, hkPhantom* phantom);

struct cHavokListener { void Update(float dt); };              // 0x00b51d50

// ---------------------------------------------------------------------------
// SP::cGonzagoPhysics
// ---------------------------------------------------------------------------

class cGonzagoPhysics {
public:
    void UpdateHavok(uint32_t deltaMs);

    uint32_t pad00[0x26 / 4];
    uint8_t pad24[2];
    uint8_t mbForceKinematic;               // +0x26
    uint8_t pad27;
    uint8_t mbHitTargetOverride;            // +0x28
    uint8_t pad29[7];
    uint8_t mbSimulateObjects;              // +0x30
    uint8_t mbIgnoreGroundOrientation;      // +0x31
    uint8_t pad32[0x60 - 0x32];
    cLocomotiveObject** mEntitiesBegin;     // +0x60
    cLocomotiveObject** mEntitiesEnd;       // +0x64
    uint8_t pad68[0x480 - 0x68];
    HashTable<SetNode<cSpatialObject*> > mObjects;  // +0x480
    uint8_t pad488[0x14e8 - 0x488];
    float mLapseTime;                       // +0x14e8
    float mPrevLapseFrac;                   // +0x14ec
};

// @ 0x00b57c40
void cGonzagoPhysics::UpdateHavok(uint32_t deltaMs)
{
    float dt = (float)deltaMs * 0.001f;
    float invDt = 1.0f / dt;
    cPlanetModel* planet = SP::PlanetModel();

    GonzagoObjectVector objects;    // rigid bodies of simulated spatial objects
    GonzagoObjectVector entities;   // creature proxies of locomotive objects

    float gravity = planet->GetGravity();
    float waterHeight = planet->GetWaterHeight();
    float waterHeightSq = waterHeight * waterHeight;

    // ---- 1. creatures / locomotive objects ---------------------------------
    for (cLocomotiveObject** it = mEntitiesBegin; it != mEntitiesEnd; ++it)
    {
        cLocomotiveObject* entity = *it;
        MapNode<cLocomotiveObject*, SPCreatureProxy*>* node = g_CreatureProxies.findNode(entity);
        SPCreatureProxy* proxy =
            (node == g_CreatureProxies.endNode()) ? 0 : node->second;

        cHitTarget* target = entity ? (cHitTarget*)entity->Cast(0xd0036e08) : 0;
        if (proxy)
        {
            void* other = entity ? entity->Cast(0x137e8e0) : 0;
            proxy->SetEnabled((target && ((target->mFlags >> 9) & 1) && mbHitTargetOverride) || other);
        }

        if (!entity->mbPhysicsEnabled)
        {
            if (proxy)
                proxy->SetActive(false);
            continue;
        }

        bool onSurface = entity->IsOnPlanetSurface();
        bool jumping = entity->mbJumping != 0;

        if (proxy)
        {
            if (entity->mbFixed)
                goto fixed;

            if (mbForceKinematic ||
                (entity->IsMoving() && entity->GetAltitude() < g_MaxSpeedForIdle))
            {
                Vector3 oldVel = entity->GetVelocity();
                entity->GetPosition();

                if (onSurface)
                {
                    if (jumping)
                    {
                        entity->UpdateJump(deltaMs);
                        jumping = entity->mbJumping != 0;
                        if (entity->mFlags & 1)
                        {
                            entity->mFlags &= ~1u;
                            FUN_00b537f0(entity, proxy, false, false);
                        }
                    }
                }
                else if (entity->mbOnGround)
                {
                    entity->ApplyGravityDirection(g_Vector3Zero);
                }

                proxy->mGravity = gravity;
                proxy->SetActive(true);
                proxy->mbFlying = 0;
                proxy->mbHovering = 0;
                proxy->mbApplyGravity = 1;
                proxy->mGroundContacts = entity->mbOnGround != 0;
                proxy->mbInWater = entity->mbInWater;

                bool ignoreGround = mbIgnoreGroundOrientation != 0;
                const Vector3& pos = entity->GetPosition();
                float px = pos.x;
                float inv = 1.0f / sqrtf(((px * px + pos.y * pos.y) + pos.z * pos.z) + 1e-8f);
                Vector3 up;
                up.x = inv * px;
                up.y = inv * pos.y;
                up.z = inv * pos.z;

                switch (entity->mMovementType)
                {
                case 4:
                    ignoreGround = true;
                    proxy->mGroundContacts = 0;
                    proxy->mbFlying = 1;
                    break;
                case 5:
                    proxy->mbApplyGravity = 0;
                    ignoreGround = true;
                    proxy->mGroundContacts = 0;
                    proxy->mbFlying = 1;
                    break;
                case 6:
                    proxy->mbHovering = 1;
                    proxy->mGroundContacts = 0;
                    proxy->mbFlying = 1;
                    break;
                }

                if (!jumping)
                {
                    proxy->mFriction = 1.0f;
                }
                else
                {
                    Vector3 newVel = entity->GetVelocity();
                    Vector3 accel;
                    accel.x = (newVel.x - oldVel.x) * invDt;
                    accel.y = (newVel.y - oldVel.y) * invDt;
                    accel.z = (newVel.z - oldVel.z) * invDt;
                    Vector3 accelDir = accel;
                    bool speedingUp =
                        (accel.z * oldVel.z + accel.y * oldVel.y) + oldVel.x * accel.x > 0.0f;
                    Vector3 vel = newVel;

                    if (!ignoreGround)
                    {
                        float mag = sqrtf((accel.z * accel.z + accel.y * accel.y) + accel.x * accel.x);
                        if (speedingUp)
                        {
                            if (mag > entity->GetMaxAcceleration())
                            {
                                float lim = entity->GetMaxAcceleration();
                                const Vector3 n = SP::normalized_safe(accelDir);
                                accelDir.x = n.x * lim;
                                accelDir.y = n.y * lim;
                                accelDir.z = n.z * lim;
                                vel.x = oldVel.x + accelDir.x * dt;
                                vel.y = accelDir.y * dt + oldVel.y;
                                vel.z = accelDir.z * dt + oldVel.z;
                            }
                        }
                        else
                        {
                            if (mag > entity->GetMaxDeceleration())
                            {
                                float lim = entity->GetMaxDeceleration();
                                const Vector3 n = SP::normalized_safe(accelDir);
                                accelDir.x = n.x * lim;
                                accelDir.y = n.y * lim;
                                accelDir.z = n.z * lim;
                                vel.x = oldVel.x + accelDir.x * dt;
                                vel.y = accelDir.y * dt + oldVel.y;
                                vel.z = accelDir.z * dt + oldVel.z;
                            }
                        }
                    }

                    // remove the vertical (up) component of the new velocity
                    float d = (vel.z * up.z + vel.y * up.y) + vel.x * up.x;
                    Vector3 tangent;
                    tangent.x = vel.x - d * up.x;
                    tangent.y = vel.y - up.y * d;
                    tangent.z = vel.z - up.z * d;

                    if (proxy->mGroundContacts <= 0 && (entity->mFlags & 0x1000) &&
                        (target || proxy->mbHovering))
                    {
                        const hkVector4& plane = proxy->GetGroundPlane();
                        float pw = plane.w;
                        float dd = -((plane.z * up.z + plane.y * up.y) + plane.x * up.x);
                        float k = proxy->mMass;
                        hkVector4 f;
                        f.x = k * (tangent.x - (dd * up.x + plane.x));
                        f.y = (tangent.y - (up.y * dd + plane.y)) * k;
                        f.z = (tangent.z - (up.z * dd + plane.z)) * k;
                        f.w = -(dd * 0.0f + pw) * k;
                        if (proxy->mbHovering && proxy->mbSwimming)
                        {
                            f.x = f.x * 0.3f;
                            f.y = f.y * 0.3f;
                            f.z = f.z * 0.3f;
                            f.w = f.w * 0.3f;
                        }
                        proxy->ApplyForce(f);
                    }
                    else if (!proxy->mbInWater)
                    {
                        hkVector4 v;
                        v.x = vel.x;
                        v.y = vel.y;
                        v.z = vel.z;
                        v.w = 0.0f;
                        proxy->SetVelocity(v);
                        proxy->mFriction = 0.0f;
                    }
                }

                // accumulated external forces
                if (entity->mForcesBegin != entity->mForcesEnd)
                {
                    ForceEntry* end = entity->mForcesEnd;
                    Vector3 sum = g_Vector3Zero;
                    bool cancelVelocity = false;
                    for (ForceEntry* f = entity->mForcesBegin; f != end; ++f)
                    {
                        if (f->type == 1)
                            cancelVelocity = true;
                        sum.x = f->force.x + sum.x;
                        sum.y = f->force.y + sum.y;
                        sum.z = f->force.z + sum.z;
                    }
                    entity->ClearForces();
                    if (!FUN_0059ab70(&sum))
                        sum = g_Vector3Zero;
                    if (cancelVelocity)
                    {
                        proxy->SetVelocity(g_hkVector4Zero);
                        proxy->mbApplyGravity = 0;
                    }
                    float k = proxy->mMass;
                    hkVector4 f;
                    f.x = sum.x * k;
                    f.y = sum.y * k;
                    f.z = sum.z * k;
                    f.w = 0.0f;
                    proxy->ApplyForce(f);
                }

                cGonzagoHavokObject rec;
                rec.mpObject = entity;
                rec.mpBody = proxy;
                rec.mbFlag = false;
                entities.push_back(rec);
                continue;
            }
        }

        // not physically simulated this frame
        if (entity->mbFixed)
        {
fixed:
            if (!proxy)
                continue;
        }
        else
        {
            if (proxy)
                proxy->SetActive(false);
            if (mbSimulateObjects)
            {
                const Vector3& p = entity->GetPosition();
                if ((p.x * p.x + p.y * p.y) + p.z * p.z > waterHeightSq)
                    FUN_00b4b040(entity, deltaMs, true);
                else
                    FUN_00b4b040(entity, deltaMs, false);
            }
            else
            {
                FUN_00b4b040(entity, deltaMs, false);
            }
        }
        if (entity->mFlags & 1)
        {
            entity->mFlags &= ~1u;
            FUN_00b537f0(entity, proxy, true, true);
        }
    }

    // ---- 2. simulated spatial objects (rigid bodies) -----------------------
    {
        HashTable<SetNode<cSpatialObject*> >::iterator it = mObjects.begin();
        SetNode<cSpatialObject*>* end = mObjects.endNode();
        for (; it.mpNode != end; it.increment())
        {
            cSpatialObject* obj = it.mpNode->first;
            if (!obj->mbPhysicsEnabled)
                continue;

            MapNode<cSpatialObject*, hkRigidBody*>* node = g_RigidBodies.findNode(obj);
            if (node == g_RigidBodies.endNode())
                continue;
            hkRigidBody* body = node->second;
            if (!body)
                continue;

            float altitude = obj->GetAltitude();
            if (obj->mbFixed || (!mbForceKinematic && altitude > g_MaxAltitudeForPhysics))
            {
                // far away / fixed: keyframed
                if (!body->m_keyframed)
                {
                    body->setMotionType(7, 1, 0);
                    if (!obj->mbFixed)
                        body->editProperty(7, hkPropertyValue(1));
                }
                if (obj->mFlags & 1)
                {
                    obj->mFlags &= ~1u;
                    FUN_00b523e0(obj, body);
                }
            }
            else
            {
                if (body->m_keyframed && altitude < g_MinAltitudeForPhysics)
                {
                    if (body->getProperty(7).lo != 0)
                    {
                        body->editProperty(7, hkPropertyValue(0));
                        body->setMotionType(1, 1, 0);
                    }
                    else
                    {
                        body->setMotionType(1, 0, 0);
                    }
                }
                if (obj->mFlags & 1)
                {
                    bool active = body->isActive().m_bool != 0;
                    FUN_00b523e0(obj, body);
                    obj->mFlags &= ~1u;
                    if (!mbForceKinematic || !active)
                        body->deactivate();
                }
                if (mbSimulateObjects && body->isActive().m_bool)
                {
                    cGonzagoHavokObject rec;
                    rec.mpObject = obj;
                    rec.mpBody = body;
                    rec.mbFlag = false;
                    objects.push_back(rec);
                }
            }
        }
    }

    // ---- 3. time step ------------------------------------------------------
    float stepDt;
    int steps;
    if (g_bFixedTimeStep)
    {
        mLapseTime = (mLapseTime - dt) * 0.85f + dt;
        if (mLapseTime > 0.06666667f)
            mLapseTime = 0.06666667f;
        stepDt = mLapseTime;
        steps = 1;
    }
    else
    {
        mLapseTime = dt + mLapseTime;
        if (mLapseTime > 0.06666667f)
            mLapseTime = 0.06666667f;
        float lapse = mLapseTime;
        float frac = lapse * 62.499996f;
        if (fabsf(frac - mPrevLapseFrac) > 0.5f)
            mPrevLapseFrac = frac;
        float n = (float)floor(mPrevLapseFrac + 0.5f);
        float one = 1.0f;
        const float& count = Max(one, n);
        stepDt = lapse / count;
        steps = (int)count;
    }

    for (int step = steps; step > 0; --step)
    {
        if (mbSimulateObjects)
        {
            // gravity on rigid bodies
            for (cGonzagoHavokObject* o = objects.mpBegin; o != objects.mpEnd; ++o)
            {
                hkRigidBody* body = (hkRigidBody*)o->mpBody;
                cSpatialObject* obj = (cSpatialObject*)o->mpObject;
                hkVector4 g = body->m_motion->m_position;
                NormalizeIfNotZero3(g);
                float s = body->m_motion->getMass() * gravity;
                g.x = s * g.x;
                g.y = s * g.y;
                g.z = s * g.z;
                g.w = s * g.w;
                body->activate();
                body->m_motion->applyForce(stepDt, g);
                if (!g_bIcePlanet)
                    o->mbFlag = FUN_00b4ed50(stepDt, obj, 0, body, waterHeight, gravity);
                else
                    o->mbFlag = false;
            }

            // force phantoms push overlapping bodies towards/away from their centre
            {
                OverlapCollector collector;
                for (hkPhantom** pp = g_ForcePhantomsBegin; pp != g_ForcePhantomsEnd; ++pp)
                {
                    hkPhantom* phantom = *pp;
                    collector.reset();
                    phantom->getOverlaps(collector);
                    OverlapHit* hitEnd = collector.m_data + collector.m_size;
                    for (OverlapHit* hit = collector.m_data; hit != hitEnd; ++hit)
                    {
                        hkCollidable* coll = hit->m_collidable;
                        if (coll->m_broadPhaseType != 1)
                            continue;
                        hkRigidBody* body = (hkRigidBody*)coll->getOwner();
                        if (!body)
                            continue;
                        if (body->m_fixedOrKeyframed)
                            continue;
                        if (!body->isActive().m_bool)
                            continue;

                        const float* c = (const float*)((char*)phantom->m_userData + 0xc);
                        hkVector4 center;
                        center.x = c[0];
                        center.y = c[1];
                        center.z = c[2];
                        center.w = 0.0f;
                        hkVector4 dir = center;
                        NormalizeIfNotZero3(dir);

                        if (body->findProperty(4).lo != 0)
                        {
                            // jump pad: launch along the phantom axis, then push out
                            hkRigidMotion* m = body->m_motion;
                            float f = m->getMass() * stepDt;
                            dir.x = f * (g_JumpPadSpeed * dir.x - m->m_linearVelocity.x);
                            dir.y = f * (g_JumpPadSpeed * dir.y - m->m_linearVelocity.y);
                            dir.z = f * (g_JumpPadSpeed * dir.z - m->m_linearVelocity.z);
                            dir.w = f * (g_JumpPadSpeed * dir.w - m->m_linearVelocity.w);
                            FUN_00b65820(body, &dir);

                            hkVector4 out = body->m_motion->m_position;
                            out.x = out.x - center.x;
                            out.y = out.y - center.y;
                            out.z = out.z - center.z;
                            out.w = out.w - center.w;
                            NormalizeIfNotZero3(out);
                            float k = f * g_JumpPadPush;
                            out.x = k * out.x;
                            out.y = k * out.y;
                            out.z = k * out.z;
                            out.w = k * out.w;
                            FUN_00b65820(body, &out);

                            cGameObjectBase* user = body->m_userData;
                            if (user && user->GetTypeID() == 0x18eb45e)
                            {
                                *(int*)((char*)user + 0x2b0) = 3;
                                *((char*)user + 0x137) = 0;
                            }
                        }
                        else
                        {
                            hkRigidMotion* m = body->m_motion;
                            float f = m->getMass() * stepDt;
                            dir.x = f * (g_PhantomPushStrength * dir.x - m->m_linearVelocity.x);
                            dir.y = f * (g_PhantomPushStrength * dir.y - m->m_linearVelocity.y);
                            dir.z = f * (g_PhantomPushStrength * dir.z - m->m_linearVelocity.z);
                            dir.w = f * (g_PhantomPushStrength * dir.w - m->m_linearVelocity.w);
                            body->activate();
                            body->m_motion->applyPointImpulse(dir, center);
                        }
                    }
                }
            }

            // trigger phantoms: collision messages for game objects inside them
            if (SP::GetCurrentGameMode() == 0x1654c10)
            {
                HashTable<MapNode<void*, hkPhantom*> >::iterator it = g_TriggerPhantoms.begin();
                MapNode<void*, hkPhantom*>* end = g_TriggerPhantoms.endNode();
                OverlapCollector collector;
                for (; it.mpNode != end; it.increment())
                {
                    hkPhantom* phantom = it.mpNode->second;
                    collector.reset();
                    phantom->getOverlaps(collector);
                    OverlapHit* hitEnd = collector.m_data + collector.m_size;
                    for (OverlapHit* hit = collector.m_data; hit != hitEnd; ++hit)
                    {
                        hkCollidable* coll = hit->m_collidable;
                        cCollisionInfo info;
                        cGameData* a = (cGameData*)phantom->m_userData;
                        info.collisionType = 3;
                        info.pGameDataA = a;
                        hkEntity* owner = coll->getOwner();
                        cGameData* b = 0;
                        if (owner->findProperty(0).lo == 3)
                            b = (cGameData*)owner->m_userData;
                        info.pGameDataB = b;
                        if (a && b && a != b && !a->mbIsDestroyed && !b->mbIsDestroyed)
                            FUN_00f31220(&info);
                    }
                }
            }

            // creature proxies
            for (cGonzagoHavokObject* o = entities.mpBegin; o != entities.mpEnd; ++o)
            {
                cLocomotiveObject* entity = (cLocomotiveObject*)o->mpObject;
                SPCreatureProxy* proxy = (SPCreatureProxy*)o->mpBody;
                if (!g_bIcePlanet)
                    o->mbFlag = FUN_00b4ed50(stepDt, entity, entity, proxy->GetBody(),
                                             waterHeight, gravity);
                else
                    o->mbFlag = false;
                proxy->Update(stepDt);
                entity->mbOnGround = proxy->mGroundContacts > 0;
                entity->mbInWater = proxy->mbInWater;
            }
        }

        g_pHavokWorld->stepDeltaTime(stepDt);
        ((cHavokListener*)g_pHavokListener)->Update(stepDt);
        if (!g_bFixedTimeStep)
            mLapseTime = mLapseTime - stepDt;
    }

    FUN_00b3d3b0();

    // ---- 4. moving rigid bodies hit creature body parts --------------------
    {
        OverlapCollector collector;
        HashTable<MapNode<cGameObjectBase*, hkPhantom*> >::iterator it = g_CreaturePhantoms.begin();
        MapNode<cGameObjectBase*, hkPhantom*>* end = g_CreaturePhantoms.endNode();
        for (; it.mpNode != end; it.increment())
        {
            cGameObjectBase* creature = it.mpNode->first;
            hkPhantom* phantom = it.mpNode->second;
            cGameObjectBase* user = (cGameObjectBase*)phantom->m_userData;
            cCreatureObject* cobj =
                (user && user->GetTypeID() == 0x18c84a9) ? (cCreatureObject*)user : 0;
            cCreatureAnimHolder* anim = cobj->GetAnimatedCreature();
            if (anim->GetLOD() < 2)
                continue;

            collector.reset();
            phantom->getOverlaps(collector);
            OverlapHit* hitEnd = collector.m_data + collector.m_size;
            for (OverlapHit* hit = collector.m_data; hit != hitEnd; ++hit)
            {
                hkCollidable* coll = hit->m_collidable;
                if (coll->m_broadPhaseType != 1)
                    continue;
                hkRigidBody* body = (hkRigidBody*)coll->getOwner();
                if (!body)
                    continue;

                hkRigidMotion* m = body->m_motion;
                float linSpeedSq = (m->m_linearVelocity.x * m->m_linearVelocity.x +
                                    m->m_linearVelocity.y * m->m_linearVelocity.y) +
                                   m->m_linearVelocity.z * m->m_linearVelocity.z;
                float angSpeedSq = (m->m_angularVelocity.x * m->m_angularVelocity.x +
                                    m->m_angularVelocity.y * m->m_angularVelocity.y) +
                                   m->m_angularVelocity.z * m->m_angularVelocity.z;
                if (body->m_fixedOrKeyframed)
                    continue;
                if (!body->isActive().m_bool)
                    continue;
                if (!(linSpeedSq > g_MinHitSpeedSq || angSpeedSq > g_MinHitSpeedSq))
                    continue;

                cGameObjectBase* gobj = body->m_userData ? body->m_userData->Cast(0x1186577) : 0;
                if (!gobj->IsAlive())
                    continue;
                const BBox* bb = gobj->GetBoundingBox();
                float objHeight = bb->maxZ - bb->minZ;
                const BBox* cb = creature->GetBoundingBox();
                if ((cb->maxZ - cb->minZ) * 0.375f > objHeight)
                    continue;

                creature_instance_data* cid = anim->mpInstance;
                float legLength = cid->static_data->mAvgLegLength * cid->requested_scale;
                Vector3 com;
                com.x = m->m_centerOfMass.x;
                com.y = m->m_centerOfMass.y;
                com.z = m->m_centerOfMass.z;
                Vector3 rel;
                rel.x = com.x - cid->requested_pos.x;
                rel.y = com.y - cid->requested_pos.y;
                rel.z = com.z - cid->requested_pos.z;
                Vector3 local = InvRotate(cid->requested_rot, rel);
                float radius = gobj->GetRadius() * g_HitRadiusScale;

                unsigned count = (unsigned)(cid->bodiesEnd - cid->bodiesBegin);
                creature_body_instance* part = cid->bodiesBegin;
                for (unsigned i = 0; i < count; i++, part++)
                {
                    creature_body_static* bd = part->data;
                    if (bd->flags & 0xb)
                        continue;
                    float s = cid->requested_scale * g_BodyExtentScale;
                    Vector3 ext;
                    ext.x = bd->extents[0] * s;
                    ext.y = bd->extents[1] * s;
                    ext.z = bd->extents[2] * s;
                    float extLen = sqrtf((ext.y * ext.y + ext.z * ext.z) + ext.x * ext.x);
                    Vector3 d;
                    d.x = local.x - part->pos.x;
                    d.y = local.y - part->pos.y;
                    d.z = local.z - part->pos.z;
                    float r = extLen + radius;
                    if (!(r * r > (d.z * d.z + d.y * d.y) + d.x * d.x))
                        continue;

                    // squared distance from the body-part box
                    Vector3 p = InvRotate(part->rot, d);
                    float dist = 0.0f;
                    if (p.x < -ext.x)
                        dist = (p.x - -ext.x) * (p.x - -ext.x);
                    else if (p.x > ext.x)
                        dist = (p.x - ext.x) * (p.x - ext.x);
                    if (p.y < -ext.y)
                        dist = (p.y - -ext.y) * (p.y - -ext.y) + dist;
                    else if (p.y > ext.y)
                        dist = (p.y - ext.y) * (p.y - ext.y) + dist;
                    if (p.z < -ext.z)
                        dist = (p.z - -ext.z) * (p.z - -ext.z) + dist;
                    else if (p.z > ext.z)
                        dist = (p.z - ext.z) * (p.z - ext.z) + dist;
                    if (radius * radius < dist)
                        continue;

                    // direction from the object to the body part (world space)
                    Vector3 wp = Rotate(cid->requested_rot, part->pos);
                    Vector3 dir;
                    dir.x = (wp.x + cid->requested_pos.x) - com.x;
                    dir.y = (cid->requested_pos.y + wp.y) - com.y;
                    dir.z = (cid->requested_pos.z + wp.z) - com.z;
                    float len = sqrtf((dir.x * dir.x + dir.y * dir.y) + dir.z * dir.z);
                    if (len != 0.0f)
                    {
                        float inv = 1.0f / len;
                        dir.x = inv * dir.x;
                        dir.y = inv * dir.y;
                        dir.z = inv * dir.z;
                    }

                    float invExt = 1.0f / extLen;
                    const hkVector4& w = m->m_angularVelocity;
                    float angSpeed = sqrtf((w.y * w.y + w.z * w.z) + w.x * w.x);
                    float mag = ((angSpeed * 0.5f + g_HitAngularBias) * invExt) * legLength;
                    mag = Min(mag, g_MaxHitImpulse);
                    Vector3 imp;
                    imp.x = mag * dir.x;
                    imp.y = mag * dir.y;
                    imp.z = mag * dir.z;

                    if (linSpeedSq > g_MinHitSpeedSq)
                    {
                        float linSpeed = sqrtf(linSpeedSq);
                        float il = 1.0f / linSpeed;
                        Vector3 vdir;
                        vdir.x = il * m->m_linearVelocity.x;
                        vdir.y = m->m_linearVelocity.y * il;
                        vdir.z = m->m_linearVelocity.z * il;
                        if ((vdir.x * dir.x + vdir.z * dir.z) + vdir.y * dir.y > -0.2f)
                        {
                            float lm = ((invExt * linSpeed) * legLength) * g_HitLinearScale;
                            lm = Min(lm, g_MaxHitImpulse);
                            imp.x = vdir.x * lm + imp.x;
                            imp.y = vdir.y * lm + imp.y;
                            imp.z = vdir.z * lm + imp.z;
                        }
                    }

                    imp.x = imp.x * dt;
                    imp.y = imp.y * dt;
                    imp.z = imp.z * dt;
                    cid->HitBody(i, imp, false, true, g_HitBodyScale);
                    break;
                }
            }
        }
    }

    // ---- 5. write results back ---------------------------------------------
    for (cGonzagoHavokObject* o = entities.mpBegin; o != entities.mpEnd; ++o)
    {
        cLocomotiveObject* entity = (cLocomotiveObject*)o->mpObject;
        FUN_00b4dd70(entity, (SPCreatureProxy*)o->mpBody);
        entity->mFlags &= ~1u;
        FUN_00b421b0(entity, o->mbFlag, entity->GetPosition(), entity->GetOrientation());
    }
    for (cGonzagoHavokObject* o = objects.mpBegin; o != objects.mpEnd; ++o)
    {
        cSpatialObject* obj = (cSpatialObject*)o->mpObject;
        FUN_00b52230(obj, (hkRigidBody*)o->mpBody);
        obj->mFlags &= ~1u;
    }
    {
        HashTable<MapNode<void*, hkPhantom*> >::iterator it = g_TriggerPhantoms.begin();
        MapNode<void*, hkPhantom*>* end = g_TriggerPhantoms.endNode();
        for (; it.mpNode != end; it.increment())
            FUN_00b4e1d0(it.mpNode->first, it.mpNode->second);
    }
}
// --- equivalence checker address annotations
    void operator delete[](void*); // 0x00f47380

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
