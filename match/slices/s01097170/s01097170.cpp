// Havok 3.1.0 slice s01097170 (0x01097170..0x010981C0): hkFixedRigidMotion (accumulator, clone, getPositionAndVelocities),
// hkConstraintChainInstanceAction::getEntities, hkCachingShapePhantom, hkBreakableConstraintData and hkBoxMotion.
// Functionally equivalent portable source (not byte exact). 32-bit layout comments throughout.
// Float math: setPositionAndLinearCast (aabb expansion, path length with inline fsqrt),
// hkBreakableConstraintData::buildJacobian (impulse norm, velocity blend), hkBoxMotion::getInertiaLocal.
// Values the asm keeps on the x87 stack without storing are typed hkX87Real and marked "X87-PRECISION".
#include "s01097170.h"

// Raw array view (no destructor): the binary frees these buffers by hand.
template <typename T> struct hkArrayRaw { T* m_data; int m_size; int m_capacityAndFlags; };

// ---- supporting types -----------------------------------------------------------------------------------------------
class hkShape;
class hkWorld;
class hkCollisionDispatcher;
class hkContactMgr;
class hkEntity;
class hkCdPointCollector { public: virtual ~hkCdPointCollector() {} float m_earlyOutDistance; };           // 8 bytes
class hkCdBodyPairCollector { public: virtual ~hkCdBodyPairCollector() {} bool m_earlyOut; };               // 8 bytes (+4)

struct hkAabb { hkVector4 m_min; hkVector4 m_max; };
struct hkCdBody { hkShape* m_shape; hkUint32 m_shapeKey; void* m_motion; hkCdBody* m_parent; };    // 0x10
struct hkCollidable : public hkCdBody                                                              // 0x24
{
    int m_ownerOffset;                    // +0x10
    hkUint32 m_handleId;                  // +0x14
    int8_t m_handleType;                  // +0x18
    int8_t m_handleOwnerOffset;           // +0x19
    hkUint16 m_objectQualityType;         // +0x1a
    hkUint32 m_collisionFilterInfo;       // +0x1c
    float m_allowedPenetrationDepth;      // +0x20
};
struct hkLinkedCollidable : public hkCollidable { hkUint32 m_collisionEntries[3]; };                // 0x30

struct hkCollisionInput                                                                             // 0x10
{
    hkCollisionDispatcher* m_dispatcher;  // +0x00
    void* m_filter;                       // +0x04
    float m_tolerance;                    // +0x08
    bool m_createPredictiveAgents;        // +0x0c
};
struct hkCollisionAgentConfig { float m_iterativeLinearCastEarlyOutDistance; int m_iterativeLinearCastMaxIterations; };
struct hkCollisionQualityInfo { uint32_t m_data[15]; };                                            // 0x3c bytes
struct hkProcessCollisionInput : public hkCollisionInput                                           // 0x2c
{
    hkStepInfo m_stepInfo;                // +0x10
    hkCollisionAgentConfig* m_config;     // +0x20
    void* m_dynamicsInfo;                 // +0x24
    hkCollisionQualityInfo* m_collisionQualityInfo;   // +0x28
};
struct hkLinearCastCollisionInput : public hkCollisionInput                                        // 0x30
{
    hkVector4 m_path;                     // +0x10
    float m_maxExtraPenetration;          // +0x20
    float m_cachedPathLength;             // +0x24
    hkCollisionAgentConfig* m_config;     // +0x28
};
struct hkLinearCastInput                                                                            // 0x20
{
    hkVector4 m_to;                       // +0x00
    float m_maxExtraPenetration;          // +0x10
    float m_startPointTolerance;          // +0x14
};

class hkCollisionAgent
{
public:
    virtual void v0(); virtual void v1();
    virtual void getPenetrations(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput& in, hkCdBodyPairCollector& out);   // 2 (+8)
    virtual void getClosestPoints(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput& in, hkCdPointCollector& out);     // 3 (+0xc)
    virtual void linearCast(const hkCdBody& a, const hkCdBody& b, const hkLinearCastCollisionInput& in,
                            hkCdPointCollector& castOut, hkCdPointCollector* startOut);                                          // 4 (+0x10)
    virtual void v5();
    virtual void cleanup();                                                                                                      // 6 (+0x18)
    virtual void updateShapeCollectionFilter(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput& in);                   // 7 (+0x1c)
};
typedef hkCollisionAgent* (__cdecl *hkAgentCreateFunc)(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkContactMgr*);
struct hkAgentFuncs { hkAgentCreateFunc m_createFunc; uint32_t m_other[4]; };                       // 0x14 bytes
class hkCollisionDispatcher                                                                         // 32-bit offsets
{
public:
    uint32_t m_pad[0x190 / 4 - 1];                                                // +0x04..+0x18f
    uint8_t m_agent2Types[32][32];                                                // +0x190
    uint8_t m_agent2TypesPred[32][32];                                            // +0x590
    hkAgentFuncs m_agent2Func[64];                                                // +0x990
    uint8_t m_pad2[0x1a14 - 0x990 - 64 * 0x14];                                    // +0xe90..+0x1a13
    hkCollisionQualityInfo m_collisionQualityInfo[8];                             // +0x1a14
};

class hkShape : public hkReferencedObject
{
public:
    virtual int getType() const;                                                  // 2 (+8)
    virtual void getAabb(const hkTransform& t, float tolerance, hkAabb& out) const;   // 3 (+0xc)
    int32_t m_userData;                                                           // +0x08
};

class hkStatisticsCollector
{
public:
    virtual void s0();
    virtual void beginObject(const char* name, int mode, const void* obj);                                     // 1 (+4)
    virtual void addArray(const char* name, int elemSize, const void* ptr, int usedBytes, int allocBytes);    // 2 (+8)
    virtual void addReferencedObject(const char* name, int mode, const void* obj);                             // 3 (+0xc)
    virtual void s4(); virtual void s5();
    virtual void endObject();                                                                                  // 6 (+0x18)
};

struct hkMultiThreadLockStub { hkUint32 m_threadId; int32_t m_lockCount; };
struct hkProperty { hkUint32 m_key; hkUint32 m_pad; hkUint32 m_value[2]; };

class hkWorld : public hkReferencedObject
{
public:
    uint32_t m_pad08[28];                                  // +0x08..+0x77 (32-bit layout)
    hkProcessCollisionInput* m_collisionInput;             // +0x78
};

class hkWorldObject : public hkReferencedObject
{
public:
    hkWorldObject(hkFinishLoadedObjectFlag);               // 0x010826E0
    void copyProperties(const hkWorldObject* other);       // 0x01087CA0
    hkWorld* m_world;                                      // +0x08
    void* m_userData;                                      // +0x0c
    const char* m_name;                                    // +0x10
    hkMultiThreadLockStub m_multithreadLock;               // +0x14
    hkLinkedCollidable m_collidable;                       // +0x1c
    hkArray<hkProperty> m_properties;                      // +0x4c
};

struct hkCollidableRemovedEvent { hkWorldObject* m_phantom; const hkCollidable* m_collidable; bool m_collidableWasAdded; };
class hkPhantomOverlapListener
{
public:
    virtual void v0();
    virtual void collidableRemovedCallback(const hkCollidableRemovedEvent& e);    // 1 (+4)
};
class hkPhantomListener;
struct hkAabbRef;

class hkPhantom : public hkWorldObject
{
public:
    hkPhantom(hkFinishLoadedObjectFlag f) : hkWorldObject(f) {}
    virtual ~hkPhantom();                                                         // 0x0108E550 (body)
    virtual void calcStatistics(hkStatisticsCollector* c) const;                  // 1
    virtual int v2_getType();                                                     // 2 (0x0108DC50)
    virtual void v3();                                                            // 3 (0x0108DB30)
    virtual void v4();                                                            // 4 (0x00DD3D10)
    virtual void v5();                                                            // 5 (0x0108DC20)
    virtual void addOverlappingCollidable(hkCollidable* c) = 0;                   // 6
    virtual hkBool isOverlappingCollidableAdded(hkCollidable* c) = 0;             // 7
    virtual void removeOverlappingCollidable(hkCollidable* c) = 0;                // 8
    virtual hkPhantom* clone() const = 0;                                         // 9
    virtual void updateShapeCollectionFilter();                                   // 10
    virtual void deallocateInternalArrays();                                      // 11 (0x0108E5E0)

    void updateBroadPhase(const hkAabb& aabb);                                    // 0x0108E680
    void calcContentStatistics(hkStatisticsCollector* c) const;                   // 0x0108E4E0
    int fireCollidableAdded(const hkCollidable* c);                               // 0x0108C0B0 (hkCollidableAccept; 0 == accept)
    void fireCollidableRemoved(const hkCollidable* c, hkBool collidableWasAdded); // 0x0108C100

    hkArray<hkPhantomOverlapListener*> m_overlapListeners;                        // +0x58
    hkArray<hkPhantomListener*> m_phantomListeners;                               // +0x64
};

class hkShapePhantom : public hkPhantom
{
public:
    hkShapePhantom(hkShape* shape, const hkMotionState& motionState);             // 0x0108DD40
    hkShapePhantom(hkFinishLoadedObjectFlag f) : hkPhantom(f) {}
    virtual void setPositionAndLinearCast(const hkVector4& position, const hkLinearCastInput& input,
                                          hkCdPointCollector& castCollector, hkCdPointCollector* startCollector) = 0;   // 12
    virtual void getClosestPoints(hkCdPointCollector& collector) = 0;             // 13
    virtual void getPenetrations(hkCdBodyPairCollector& collector) = 0;           // 14
    hkMotionState m_motionState;                                                  // +0x70
};

struct hkCollisionDetail { hkCollisionAgent* m_agent; hkCollidable* m_collidable; };   // 8 bytes

class hkCachingShapePhantom : public hkShapePhantom
{
public:
    HK_DECLARE_CLASS_ALLOCATOR_B(0x2e)
    hkCachingShapePhantom(hkFinishLoadedObjectFlag f) : hkShapePhantom(f) { m_collisionDetails.m_data = 0; m_collisionDetails.m_size = 0; m_collisionDetails.m_capacityAndFlags = (int)0x80000000; }
    hkCachingShapePhantom(hkShape* shape, const hkMotionState& ms) : hkShapePhantom(shape, ms) { m_collisionDetails.m_data = 0; m_collisionDetails.m_size = 0; m_collisionDetails.m_capacityAndFlags = (int)0x80000000; }   // inlined in clone (0x01097B20)
    virtual ~hkCachingShapePhantom();                                             // 0x01097ab0 (body)
    virtual void calcStatistics(hkStatisticsCollector* c) const;                  // 0x010979D0
    virtual void addOverlappingCollidable(hkCollidable* c);                       // 0x010978F0
    virtual hkBool isOverlappingCollidableAdded(hkCollidable* c);                 // 0x01097780
    virtual void removeOverlappingCollidable(hkCollidable* c);                    // 0x010977D0
    virtual hkPhantom* clone() const;                                             // 0x01097B20
    virtual void updateShapeCollectionFilter();                                   // 0x01097880
    virtual void deallocateInternalArrays();                                      // 0x01097C90
    virtual void setPositionAndLinearCast(const hkVector4& position, const hkLinearCastInput& input,
                                          hkCdPointCollector& castCollector, hkCdPointCollector* startCollector);   // 0x010973E0
    virtual void getClosestPoints(hkCdPointCollector& collector);                 // 0x01097690
    virtual void getPenetrations(hkCdBodyPairCollector& collector);               // 0x01097700

    hkArrayRaw<hkCollisionDetail> m_collisionDetails;                             // +0x120 (data, size, capacity|flags)
};

// ---- motions ----------------------------------------------------------------------------------------------------------
class hkVelocityAccumulator
{
public:
    hkUint8 m_type;                       // +0x00
    hkUint8 m_pad01[11];                  // +0x01
    hkUint8 m_flag0c;                     // +0x0c
    hkUint8 m_pad0d[3];                   // +0x0d
    hkVector4 m_linearVelocity;           // +0x10
    hkVector4 m_angularVelocity;          // +0x20
    hkVector4 m_rest[5];                  // +0x30..+0x7f
};

class hkKeyframedRigidMotion : public hkRigidMotion
{
public:
    hkKeyframedRigidMotion(const hkVector4& position, const hkQuaternion& rotation);   // 0x01095B60
    hkRigidMotion* m_savedMotion;         // +0xf0
    int32_t m_savedQualityTypeIndex;      // +0xf4
    uint32_t m_pad[2];                    // +0xf8
};

class hkFixedRigidMotion : public hkKeyframedRigidMotion
{
public:
    HK_DECLARE_CLASS_ALLOCATOR_B(0x2b)
    hkFixedRigidMotion(const hkVector4& position, const hkQuaternion& rotation) : hkKeyframedRigidMotion(position, rotation) {}   // 0x01097110
    virtual hkVelocityAccumulator* applyForcesAndBuildAccumulator(const hkStepInfo& stepInfo, hkVelocityAccumulator* acc);   // 0x01097170
    virtual hkMotion* clone() const;                                              // 0x010971F0
    virtual void getPositionAndVelocities(hkRigidMotion* out);                    // 0x01097280
};
extern const hkVector4 g_hkVector4Zero;              // 0x016E42D0
extern const hkQuaternion g_hkQuaternionIdentity;    // 0x015B9B20 (shared identity block)

class hkBoxMotion : public hkRigidMotion
{
public:
    hkBoxMotion(const hkVector4& position, const hkQuaternion& rotation);         // 0x01098140
    virtual void setMass(float m);                                                // 0x01098120
    virtual void getInertiaLocal(hkMatrix3& out) const;                           // 0x01098190
    hkVector4 m_inertiaAndMassInv;                                                // +0xf0
};

// ---- constraints ------------------------------------------------------------------------------------------------------
class hkConstraintOwner
{
public:
    virtual void v0(); virtual void v1();
    virtual void removeConstraintImmediately(void* constraintInstance);           // 2 (+8; name unverified)
};
struct hkConstraintInstance { uint32_t m_vptr; hkInt16 m_memSize; hkInt16 m_refCount; hkConstraintOwner* m_owner; };   // +0x08 owner
class hkEntity;
struct hkConstraintQueryIn                                                        // 0x48 bytes (32-bit)
{
    uint32_t m_pad[10];                   // +0x00..+0x27 (step info etc.)
    hkVelocityAccumulator* m_bodyA;       // +0x28
    hkVelocityAccumulator* m_bodyB;       // +0x2c
    uint32_t m_pad30[4];                  // +0x30..+0x3f
    hkConstraintInstance* m_constraintInstance;   // +0x40
    void* m_constraintRuntime;            // +0x44
};
struct hkConstraintQueryOut { uint32_t m_pad[2]; };
struct hkConstraintRuntimeInfo { int m_sizeOfExternalRuntime; int m_numSolverResults; };   // hkConstraintData::RuntimeInfo
struct hkBreakableConstraintEvent
{
    hkConstraintInstance* m_constraintInstance;       // +0x00
    class hkBreakableConstraintData* m_breakableConstraintData;   // +0x04
    float m_breakingImpulse;                          // +0x08
    bool m_removeConstraint;                          // +0x0c
};
class hkBreakableListener { public: virtual void constraintBrokenCallback(const hkBreakableConstraintEvent& e); };

class hkConstraintData : public hkReferencedObject
{
public:
    virtual void v2();                                                            // 2 (0x00094DD0)
    virtual int getType() const;                                                  // 3 (0x01097D60 in the breakable vtable)
    virtual void getRuntimeInfo(hkBool wantRuntime, hkConstraintRuntimeInfo& infoOut) const;   // 4
    virtual void v5(); virtual void v6();
    virtual void buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out);       // 7 (+0x1c)
    virtual void v8();
};

class hkBreakableConstraintData : public hkConstraintData
{
public:
    HK_DECLARE_CLASS_ALLOCATOR_B(0x29)
    virtual ~hkBreakableConstraintData();                                         // 0x010980D0 (scalar deleting form)
    virtual void getRuntimeInfo(hkBool wantRuntime, hkConstraintRuntimeInfo& infoOut) const;   // 0x01097D40
    virtual void buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out);       // 0x01097D90
    hkConstraintData* m_constraintData;   // +0x0c
    hkUint16 m_childRuntimeSize;          // +0x10
    hkUint16 m_childNumSolverResults;     // +0x12
    void* m_world;                        // +0x14
    float m_solverResultLimit;            // +0x18
    bool m_removeWhenBroken;              // +0x1c
    bool m_revertBackVelocityOnBreak;     // +0x1d
    hkBreakableListener* m_listener;      // +0x20
};
struct hkBreakableConstraintRuntime       // 0x34 bytes, stored after the child's runtime
{
    bool m_isBroken;                      // +0x00
    float m_linearVelocityA[3];           // +0x04
    float m_linearVelocityB[3];           // +0x10
    float m_angularVelocityA[3];          // +0x1c
    float m_angularVelocityB[3];          // +0x28
};
void hkConstraintUtil_addNopSchema(const hkConstraintQueryIn& in, hkConstraintQueryOut& out, int a, int b);   // 0x010AA080 (cdecl)

class hkAction : public hkReferencedObject
{
public:
    virtual void v2(); virtual void getEntities(hkArray<hkEntity*>& out);         // 3
    void* m_world; void* m_island; hkUint32 m_userData; const char* m_name;       // +0x08..+0x17
};
struct hkConstraintChainInstance
{
    uint32_t m_pad[10];                                   // +0x00..+0x27
    hkArrayRaw<hkEntity*> m_chainedEntities;              // +0x28
    uint32_t m_pad34;                                     // +0x34 (m_action)
};
class hkConstraintChainInstanceAction : public hkAction
{
public:
    virtual void getEntities(hkArray<hkEntity*>& out);                            // 0x01097340
    hkConstraintChainInstance* m_constraintInstance;                              // +0x18
};

// Copy-assign of a pointer array as the binary does it (reserve exactly when too small, then copy dwords).
template <typename T>
static void hkArrayCopyAssign(hkArrayRaw<T>& dst, const hkArrayRaw<T>& src)
{
    if ((dst.m_capacityAndFlags & 0x3fffffff) < src.m_size)
    {
        if (dst.m_capacityAndFlags >= 0)
            hkThreadMemory::getInstance().deallocateChunk(dst.m_data, (dst.m_capacityAndFlags & 0x3fffffff) * (int)sizeof(T), HK_MEMORY_CLASS_ARRAY);
        dst.m_data = (T*)hkThreadMemory::getInstance().allocateChunk(src.m_size * (int)sizeof(T), HK_MEMORY_CLASS_ARRAY);
        dst.m_capacityAndFlags = (dst.m_capacityAndFlags & 0x40000000) | src.m_size;
    }
    dst.m_size = src.m_size;
    for (int i = 0; i < src.m_size; ++i)
        dst.m_data[i] = src.m_data[i];
}

// =====================================================================================================================
// hkFixedRigidMotion
// =====================================================================================================================

// @ 0x01097170
hkVelocityAccumulator* hkFixedRigidMotion::applyForcesAndBuildAccumulator(const hkStepInfo&, hkVelocityAccumulator* acc)
{
    acc->m_type = 1;
    acc->m_flag0c = 1;
    // every dword from +0x10 to +0x7c is cleared
    acc->m_linearVelocity.x = 0.0f; acc->m_linearVelocity.y = 0.0f; acc->m_linearVelocity.z = 0.0f; acc->m_linearVelocity.w = 0.0f;
    acc->m_angularVelocity.x = 0.0f; acc->m_angularVelocity.y = 0.0f; acc->m_angularVelocity.z = 0.0f; acc->m_angularVelocity.w = 0.0f;
    for (int i = 0; i < 5; ++i)
    {
        acc->m_rest[i].x = 0.0f; acc->m_rest[i].y = 0.0f; acc->m_rest[i].z = 0.0f; acc->m_rest[i].w = 0.0f;
    }
    return acc + 1;                        // next accumulator slot (0x80 bytes)
}

// @ 0x010971f0
hkMotion* hkFixedRigidMotion::clone() const
{
    hkFixedRigidMotion* c = new hkFixedRigidMotion(g_hkVector4Zero, g_hkQuaternionIdentity);   // class 0x2b, size 0x100
    // everything after the 8-byte object header is copied (0xf8 bytes in the 32-bit binary)
    c->m_solverData = m_solverData;
    memcpy(&c->m_motionState, &m_motionState, sizeof(hkMotionState));
    c->m_massInv = m_massInv;
    c->m_particleMinInertiaDiagInv = m_particleMinInertiaDiagInv;
    c->m_linearDamping = m_linearDamping;
    c->m_angularDamping = m_angularDamping;
    memcpy(&c->m_linearVelocity, &m_linearVelocity, sizeof(hkVector4));
    memcpy(&c->m_angularVelocity, &m_angularVelocity, sizeof(hkVector4));
    c->m_savedMotion = m_savedMotion;
    c->m_savedQualityTypeIndex = m_savedQualityTypeIndex;
    c->m_pad[0] = m_pad[0];
    c->m_pad[1] = m_pad[1];
    if (c->m_savedMotion != 0)
        c->m_savedMotion = static_cast<hkRigidMotion*>(c->m_savedMotion->clone());
    return c;
}

// @ 0x01097280
void hkFixedRigidMotion::getPositionAndVelocities(hkRigidMotion* out)
{
    out->m_motionState = m_motionState;
    out->m_linearVelocity.w = 0.0f; out->m_linearVelocity.z = 0.0f; out->m_linearVelocity.y = 0.0f; out->m_linearVelocity.x = 0.0f;
    out->m_angularVelocity.w = 0.0f; out->m_angularVelocity.z = 0.0f; out->m_angularVelocity.y = 0.0f; out->m_angularVelocity.x = 0.0f;
}

// @ 0x01097340
void hkConstraintChainInstanceAction::getEntities(hkArray<hkEntity*>& out)
{
    hkArrayCopyAssign(*reinterpret_cast<hkArrayRaw<hkEntity*>*>(&out), m_constraintInstance->m_chainedEntities);
}

// =====================================================================================================================
// hkCachingShapePhantom
// =====================================================================================================================

// @ 0x010973e0
void hkCachingShapePhantom::setPositionAndLinearCast(const hkVector4& position, const hkLinearCastInput& input,
                                                     hkCdPointCollector& castCollector, hkCdPointCollector* startCollector)
{
    // the phantom's transform translation is moved to the start position
    memcpy(&m_motionState.m_transform.m[12], &position, sizeof(hkVector4));

    hkProcessCollisionInput* ci = m_world->m_collisionInput;
    hkAabb aabb;
    // X87-PRECISION: (tolerance * 0.5) is added to startPointTolerance without an intermediate store
    float expand = (float)((hkX87Real)ci->m_tolerance * 0.5f + input.m_startPointTolerance);
    m_collidable.m_shape->getAabb(m_motionState.m_transform, expand, aabb);

    // path = to - from, stored to float slots
    float dx = input.m_to.x - position.x;
    float dy = input.m_to.y - position.y;
    float dz = input.m_to.z - position.z;
    float dw = input.m_to.w - position.w;

    // lo = min(d, 0), hi = max(d, 0) (NaN keeps d)
    float lox = (0.0f < dx) ? 0.0f : dx;
    float loy = (0.0f < dy) ? 0.0f : dy;
    float loz = (0.0f < dz) ? 0.0f : dz;
    float low = (0.0f < dw) ? 0.0f : dw;
    float hix = (0.0f > dx) ? 0.0f : dx;
    float hiy = (0.0f > dy) ? 0.0f : dy;
    float hiz = (0.0f > dz) ? 0.0f : dz;
    float hiw = (0.0f > dw) ? 0.0f : dw;
    aabb.m_min.x = lox + aabb.m_min.x;
    aabb.m_min.y = aabb.m_min.y + loy;
    aabb.m_min.z = aabb.m_min.z + loz;
    aabb.m_min.w = aabb.m_min.w + low;
    aabb.m_max.x = aabb.m_max.x + hix;
    aabb.m_max.y = aabb.m_max.y + hiy;
    aabb.m_max.z = aabb.m_max.z + hiz;
    aabb.m_max.w = aabb.m_max.w + hiw;
    updateBroadPhase(aabb);

    // linear cast input for the agents
    hkLinearCastCollisionInput lc;
    lc.m_dispatcher = ci->m_dispatcher;
    lc.m_filter = ci->m_filter;
    lc.m_tolerance = input.m_startPointTolerance;          // overwrites the copied tolerance
    lc.m_createPredictiveAgents = ci->m_createPredictiveAgents;
    lc.m_path.x = dx; lc.m_path.y = dy; lc.m_path.z = dz; lc.m_path.w = dw;
    lc.m_maxExtraPenetration = input.m_maxExtraPenetration;
    // X87-PRECISION: the sum of squares is not stored before the inline fsqrt
    lc.m_cachedPathLength = (float)hkX87Sqrt(((hkX87Real)dz * dz + (hkX87Real)dy * dy) + (hkX87Real)dx * dx);
    lc.m_config = ci->m_config;

    for (int i = m_collisionDetails.m_size - 1; i >= 0; --i)
        m_collisionDetails.m_data[i].m_agent->linearCast(m_collidable, *m_collisionDetails.m_data[i].m_collidable, lc, castCollector, startCollector);
}

// @ 0x01097690
void hkCachingShapePhantom::getClosestPoints(hkCdPointCollector& collector)
{
    const hkCollisionInput input = *m_world->m_collisionInput;      // 16-byte copy
    for (int i = m_collisionDetails.m_size - 1; i >= 0; --i)
        m_collisionDetails.m_data[i].m_agent->getClosestPoints(m_collidable, *m_collisionDetails.m_data[i].m_collidable, input, collector);
}

// @ 0x01097700
void hkCachingShapePhantom::getPenetrations(hkCdBodyPairCollector& collector)
{
    const hkCollisionInput input = *m_world->m_collisionInput;
    int i = m_collisionDetails.m_size;
    do
    {
        --i;
        if (i < 0)
            return;
        m_collisionDetails.m_data[i].m_agent->getPenetrations(m_collidable, *m_collisionDetails.m_data[i].m_collidable, input, collector);
    } while (!collector.m_earlyOut);
}

// @ 0x01097780
hkBool hkCachingShapePhantom::isOverlappingCollidableAdded(hkCollidable* c)
{
    for (int i = 0; i < m_collisionDetails.m_size; ++i)
    {
        if (m_collisionDetails.m_data[i].m_collidable == c)
            return true;
    }
    return false;
}

// @ 0x010977d0
void hkCachingShapePhantom::removeOverlappingCollidable(hkCollidable* c)
{
    if (c->m_shape != 0)
    {
        for (int i = m_collisionDetails.m_size - 1; i >= 0; --i)
        {
            if (m_collisionDetails.m_data[i].m_collidable == c)
            {
                fireCollidableRemoved(c, true);
                hkCollisionAgent* agent = m_collisionDetails.m_data[i].m_agent;
                if (agent != 0)
                    agent->cleanup();
                int last = m_collisionDetails.m_size - 1;
                m_collisionDetails.m_size = last;
                m_collisionDetails.m_data[i] = m_collisionDetails.m_data[last];       // swap-remove
                return;
            }
        }
        // not found: tell the overlap listeners that the collidable was never added
        hkCollidableRemovedEvent ev;
        ev.m_phantom = this;
        ev.m_collidable = c;
        ev.m_collidableWasAdded = false;
        for (int j = m_overlapListeners.m_size - 1; j >= 0; --j)
        {
            hkPhantomOverlapListener* l = m_overlapListeners.m_data[j];
            if (l != 0)
                l->collidableRemovedCallback(ev);
        }
    }
}

// @ 0x01097880
void hkCachingShapePhantom::updateShapeCollectionFilter()
{
    const hkCollisionInput input = *m_world->m_collisionInput;
    for (int i = 0; i < m_collisionDetails.m_size; ++i)
        m_collisionDetails.m_data[i].m_agent->updateShapeCollectionFilter(m_collidable, *m_collisionDetails.m_data[i].m_collidable, input);
}

// @ 0x010978f0
void hkCachingShapePhantom::addOverlappingCollidable(hkCollidable* c)
{
    if (c->m_shape != 0)
    {
        if (fireCollidableAdded(c) == 0)
        {
            if (m_collisionDetails.m_size == (m_collisionDetails.m_capacityAndFlags & 0x3fffffff))
                hkArrayUtil::_reserveMore(&m_collisionDetails, (int)sizeof(hkCollisionDetail));
            hkCollisionDetail* slot = &m_collisionDetails.m_data[m_collisionDetails.m_size];
            m_collisionDetails.m_size = m_collisionDetails.m_size + 1;

            hkProcessCollisionInput input = *m_world->m_collisionInput;    // 0x2c bytes (rep movsd)
            input.m_collisionQualityInfo = &input.m_dispatcher->m_collisionQualityInfo[1];   // dispatcher + 0x1a50
            input.m_createPredictiveAgents = false;

            int typeA = m_collidable.m_shape->getType();
            int typeB = c->m_shape->getType();
            const uint8_t (*table)[32] = input.m_createPredictiveAgents ? input.m_dispatcher->m_agent2TypesPred
                                                                         : input.m_dispatcher->m_agent2Types;
            int agentIndex = table[typeA][typeB];
            hkAgentCreateFunc create = input.m_dispatcher->m_agent2Func[agentIndex].m_createFunc;
            hkCollisionAgent* agent = create(m_collidable, *c, input, 0);
            slot->m_agent = agent;
            slot->m_collidable = c;
        }
    }
}

// @ 0x010979d0
void hkCachingShapePhantom::calcStatistics(hkStatisticsCollector* c) const
{
    c->beginObject("CachngPhantm", 2, this);
    calcContentStatistics(c);
    if (m_collisionDetails.m_capacityAndFlags >= 0)
        c->addArray("AgentPtr", 8, m_collisionDetails.m_data, m_collisionDetails.m_size * 8,
                    (m_collisionDetails.m_capacityAndFlags & 0x3fffffff) << 3);
    for (int i = 0; i < m_collisionDetails.m_size; ++i)
        c->addReferencedObject("Agent", 8, m_collisionDetails.m_data[i].m_agent);
    c->endObject();
}

// @ 0x01097a60  (separate function in the same card: finish-loaded-object hook of hkCachingShapePhantom)
void finishLoadedObject_hkCachingShapePhantom(void* p)
{
    if (p != 0)
    {
        hkFinishLoadedObjectFlag flag; flag.m_finishing = 1;
        new (p) hkCachingShapePhantom(flag);
    }
}

// @ 0x01097ab0
hkCachingShapePhantom::~hkCachingShapePhantom()
{
    for (int i = m_collisionDetails.m_size - 1; i >= 0; --i)
        m_collisionDetails.m_data[i].m_agent->cleanup();        // no null check here (unlike removeOverlappingCollidable)
    m_collisionDetails.m_size = 0;
    if (m_collisionDetails.m_capacityAndFlags >= 0)
        hkThreadMemory::getInstance().deallocateChunk(m_collisionDetails.m_data,
            (m_collisionDetails.m_capacityAndFlags & 0x3fffffff) * (int)sizeof(hkCollisionDetail), HK_MEMORY_CLASS_ARRAY);
    // ~hkPhantom() (0x0108E550) runs next (tail jump in the binary)
}

// @ 0x01097b20
hkPhantom* hkCachingShapePhantom::clone() const
{
    hkCachingShapePhantom* c = new hkCachingShapePhantom(m_collidable.m_shape, m_motionState);   // class 0x2e, size 0x130
    c->m_collidable.m_collisionFilterInfo = m_collidable.m_collisionFilterInfo;
    hkArrayCopyAssign(*reinterpret_cast<hkArrayRaw<hkPhantomOverlapListener*>*>(&c->m_overlapListeners),
                      *reinterpret_cast<const hkArrayRaw<hkPhantomOverlapListener*>*>(&m_overlapListeners));
    hkArrayCopyAssign(*reinterpret_cast<hkArrayRaw<hkPhantomListener*>*>(&c->m_phantomListeners),
                      *reinterpret_cast<const hkArrayRaw<hkPhantomListener*>*>(&m_phantomListeners));
    c->copyProperties(this);
    return c;
}

// @ 0x01097c90
void hkCachingShapePhantom::deallocateInternalArrays()
{
    if (m_collisionDetails.m_size == 0)
    {
        if (m_collisionDetails.m_capacityAndFlags >= 0)
            hkThreadMemory::getInstance().deallocateChunk(m_collisionDetails.m_data,
                (m_collisionDetails.m_capacityAndFlags & 0x3fffffff) * (int)sizeof(hkCollisionDetail), HK_MEMORY_CLASS_ARRAY);
        m_collisionDetails.m_data = 0;
        m_collisionDetails.m_size = 0;
        m_collisionDetails.m_capacityAndFlags = (int)(((unsigned)m_collisionDetails.m_capacityAndFlags & 0xc0000000u) | 0x80000000u);
    }
    hkShapePhantom::deallocateInternalArrays();      // tail jump through the 0x0108DB40 thunk
}

// =====================================================================================================================
// hkBreakableConstraintData
// =====================================================================================================================

// @ 0x01097d40
void hkBreakableConstraintData::getRuntimeInfo(hkBool, hkConstraintRuntimeInfo& infoOut) const
{
    infoOut.m_numSolverResults = m_childNumSolverResults;
    infoOut.m_sizeOfExternalRuntime = m_childRuntimeSize + (int)sizeof(hkBreakableConstraintRuntime);   // + 0x34
}

// @ 0x01097d90
void hkBreakableConstraintData::buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out)
{
    int numResults = m_childNumSolverResults;
    char* runtimeBase = (char*)in.m_constraintRuntime;
    hkBreakableConstraintRuntime* rt = (hkBreakableConstraintRuntime*)(runtimeBase + m_childRuntimeSize);
    float* results = (float*)runtimeBase;              // child solver results: one 8-byte entry each, impulse first

    bool tail = true;           // true: run the "constraint is broken" tail
    if (!rt->m_isBroken)
    {
        // sum of squared impulses, accumulated sequentially on the x87 stack
        hkX87Real sum = 0.0;                           // X87-PRECISION
        for (int i = 0; i < numResults; ++i)
        {
            hkX87Real x = results[i * 2];
            sum = sum + x * x;
        }
        float sumF = (float)sum;                       // stored copy ([esp+0x14])
        hkX87Real limitSq = (hkX87Real)m_solverResultLimit * m_solverResultLimit;
        if (sum > limitSq)                             // fcompp; not for <= or NaN
        {
            rt->m_isBroken = true;
            if (m_listener != 0)
            {
                hkBreakableConstraintEvent ev;
                ev.m_constraintInstance = in.m_constraintInstance;
                ev.m_breakableConstraintData = this;
                ev.m_breakingImpulse = (float)hkX87Sqrt(sum);
                ev.m_removeConstraint = m_removeWhenBroken;
                m_listener->constraintBrokenCallback(ev);
                sum = sumF;                            // reloaded from the float slot after the call
            }
            if (m_revertBackVelocityOnBreak)
            {
                // blend the body velocities back towards the saved ones by limit / |impulse|
                hkX87Real f = (hkX87Real)m_solverResultLimit / hkX87Sqrt(sum);   // fsqrt, fdivr
                hkX87Real g = 1.0 - f;                                           // X87-PRECISION
                float gF = (float)g;                                             // float copy used for B angular y/z/w
                hkVelocityAccumulator* a = in.m_bodyA;
                hkVelocityAccumulator* b = in.m_bodyB;
                const float* sLinA = rt->m_linearVelocityA;
                const float* sLinB = rt->m_linearVelocityB;
                const float* sAngA = rt->m_angularVelocityA;
                const float* sAngB = rt->m_angularVelocityB;
                // body A linear velocity
                a->m_linearVelocity.x = (float)((hkX87Real)sLinA[0] * g + f * a->m_linearVelocity.x);
                a->m_linearVelocity.y = (float)((hkX87Real)sLinA[1] * g + f * a->m_linearVelocity.y);
                a->m_linearVelocity.z = (float)((hkX87Real)sLinA[2] * g + f * a->m_linearVelocity.z);
                a->m_linearVelocity.w = (float)(f * a->m_linearVelocity.w + g * 0.0f);
                // body B linear velocity
                b->m_linearVelocity.x = (float)((hkX87Real)sLinB[0] * g + f * b->m_linearVelocity.x);
                b->m_linearVelocity.y = (float)((hkX87Real)sLinB[1] * g + f * b->m_linearVelocity.y);
                b->m_linearVelocity.z = (float)((hkX87Real)sLinB[2] * g + f * b->m_linearVelocity.z);
                b->m_linearVelocity.w = (float)(f * b->m_linearVelocity.w + g * 0.0f);
                // body A angular velocity (the x87 loads of saved x are the float values)
                a->m_angularVelocity.x = (float)(g * (hkX87Real)sAngA[0] + f * a->m_angularVelocity.x);
                a->m_angularVelocity.y = (float)((hkX87Real)sAngA[1] * g + f * a->m_angularVelocity.y);
                a->m_angularVelocity.z = (float)((hkX87Real)sAngA[2] * g + f * a->m_angularVelocity.z);
                a->m_angularVelocity.w = (float)(f * a->m_angularVelocity.w + g * 0.0f);
                // body B angular velocity: x with the register g, y/z/w with the stored float copy of g
                b->m_angularVelocity.x = (float)(g * (hkX87Real)sAngB[0] + f * b->m_angularVelocity.x);
                b->m_angularVelocity.y = (float)((hkX87Real)sAngB[1] * gF + f * b->m_angularVelocity.y);
                b->m_angularVelocity.z = (float)((hkX87Real)sAngB[2] * gF + f * b->m_angularVelocity.z);
                b->m_angularVelocity.w = (float)(f * b->m_angularVelocity.w + (hkX87Real)gF * 0.0f);
            }
        }
        if (!rt->m_isBroken)
        {
            // not broken: remember the current velocities and let the child build its jacobians
            memcpy(rt->m_linearVelocityA, &in.m_bodyA->m_linearVelocity, 3 * sizeof(float));
            memcpy(rt->m_linearVelocityB, &in.m_bodyB->m_linearVelocity, 3 * sizeof(float));
            memcpy(rt->m_angularVelocityA, &in.m_bodyA->m_angularVelocity, 3 * sizeof(float));
            memcpy(rt->m_angularVelocityB, &in.m_bodyB->m_angularVelocity, 3 * sizeof(float));
            m_constraintData->buildJacobian(in, out);
            tail = false;
        }
    }
    if (tail)
    {
        hkConstraintUtil_addNopSchema(in, out, 0, 8);
        if (m_removeWhenBroken)
            in.m_constraintInstance->m_owner->removeConstraintImmediately(in.m_constraintInstance);
    }
    for (int i = 0; i < numResults; ++i)
        results[i * 2] = 0.0f;                          // dword stores of 0 (impulses reset)
}

// @ 0x010980d0
hkBreakableConstraintData::~hkBreakableConstraintData()
{
    if (m_constraintData != 0)
        m_constraintData->removeReference();
    // scalar deleting form: (flag & 1) -> hkMemory::deallocateChunk(this, memSize, 0x29)
}

// =====================================================================================================================
// hkBoxMotion
// =====================================================================================================================

// @ 0x01098120
void hkBoxMotion::setMass(float m)
{
    setMassInv(1.0f / m);
}

// @ 0x01098140
hkBoxMotion::hkBoxMotion(const hkVector4& position, const hkQuaternion& rotation)
    : hkRigidMotion(position, rotation)
{
    m_inertiaAndMassInv.x = 1.0f;
    m_inertiaAndMassInv.y = 1.0f;
    m_inertiaAndMassInv.z = 1.0f;
    m_inertiaAndMassInv.w = 1.0f;
    m_particleMinInertiaDiagInv = -1.0f;
}

// @ 0x01098190
void hkBoxMotion::getInertiaLocal(hkMatrix3& out) const
{
    float ix = 1.0f / m_inertiaAndMassInv.x;
    float iy = 1.0f / m_inertiaAndMassInv.y;
    float iz = 1.0f / m_inertiaAndMassInv.z;
    float* m = &out.m_col[0].x;
    for (int i = 0; i < 12; ++i)
        m[i] = 0.0f;
    out.m_col[0].x = ix;
    out.m_col[1].y = iy;
    out.m_col[2].z = iz;
}
// --- equivalence checker address annotations
    extern unsigned int g_hkThreadMemoryTls; // 0x016e4174

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
