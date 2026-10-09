// Havok 3.1.0 physics: hkQuaternion/hkRotation conversion, hkSolverInfo::setTauAndDamping,
// hkWorldObject (ctor/dtor/properties/statistics) and a block of hkWorld methods
// (addEntity/removeEntity/addPhantom/castRay/linearCast/stepDeltaTime, pending-op execution).
// Equivalent portable source, not byte-exact. x87 float semantics are documented per function.
#include <stddef.h>
#include <math.h>
#include "types.h"

// Pointer-sized stand-in for values the original keeps on the x87 stack in 80-bit extended
// precision without storing them to memory. If the game runs with the x87 precision control
// set to single (D3D9 default) this should be float; at extended it should be long double.
// X87-PRECISION: change here to experiment.
typedef double hkX87Real;

typedef float hkReal;

// ------------------------------------------------------------ base types
struct hkVector4 { float x, y, z, w; };
struct hkQuaternion { float m_vec[4]; void set(const struct hkRotation& r); };    // x y z w
struct hkRotation { float m_el[12]; void set(const hkQuaternion& q); };          // 3 columns of 4 floats (col*4+row)

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int __stdcall TlsSetValue(unsigned long, void*);
extern "C" unsigned __int64 __rdtsc();
#pragma intrinsic(__rdtsc)

enum { HK_ARRAY_FLAG_MASK = 0x3fffffff, HK_ARRAY_DONT_DEALLOCATE = (int)0x80000000 };
struct hkArrayUtil { static void _reserveMore(void* arr, int elemSize); };
struct hkThreadMemory { void deallocateChunk(void* p, int nbytes, int memClass); };
extern unsigned long g_hkThreadMemoryTlsIndex;       // 0x16e4174
static inline hkThreadMemory* getThreadMemory() { return (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTlsIndex); }

template <typename T>
struct hkArray {
    T* m_data; int m_size; int m_capacityAndFlags;
    void pushBack(const T& t) {
        if (m_size == (m_capacityAndFlags & HK_ARRAY_FLAG_MASK)) hkArrayUtil::_reserveMore(this, (int)sizeof(T));
        m_data[m_size] = t;
        m_size = m_size + 1;
    }
    void quickFree() {
        if (m_capacityAndFlags >= 0)
            getThreadMemory()->deallocateChunk(m_data, (m_capacityAndFlags & HK_ARRAY_FLAG_MASK) * (int)sizeof(T), 0x14);
    }
    int indexOf(const T& t) const {
        int i = 0;
        while (i < m_size) { if (m_data[i] == t) return i; ++i; }
        return -1;
    }
};

struct hkMemory {
    virtual void* allocateChunk(int nbytes, int memClass);
    virtual void s1(); virtual void s2(); virtual void s3();
    virtual void* allocateObject(int nbytes, int memClass);
    virtual void deallocateObject(void* p, int nbytes, int memClass);
    int m_pad[3];
    int m_stat14;   // +0x14 (read by the memory watchdog check)
    int m_pad2[3];
    int m_stat28;   // +0x28
};
extern hkMemory* g_hkMemory; // 0x016e4178

#define HK_CLASS_ALLOC(MEMCLASS) \
    static void* operator new(size_t sz) { void* p = g_hkMemory->allocateObject((int)sz, MEMCLASS); \
        *(uint16_t*)((char*)p + 4) = (uint16_t)sz; return p; } \
    static void operator delete(void* p) { g_hkMemory->deallocateObject(p, *(uint16_t*)((char*)p + 4), MEMCLASS); }

struct hkReferencedObject {
    uint16_t m_memSizeAndFlags;
    uint16_t m_referenceCount;
    hkReferencedObject() : m_referenceCount(1) {}
    virtual ~hkReferencedObject() {}
    virtual void calcStatistics(struct hkStatisticsCollector* c) const {}
    void addReference() { if (m_memSizeAndFlags != 0) m_referenceCount = (uint16_t)(m_referenceCount + 1); }   // 0x01082590
    void removeReference() {
        if (m_memSizeAndFlags != 0) {
            m_referenceCount = (uint16_t)(m_referenceCount - 1);
            if (m_referenceCount == 0) delete this;
        }
    }
};

// ------------------------------------------------------------ quaternion <-> rotation
// @ 0x01082350
// Original uses a private register convention (rotation in ECX, output quaternion on the stack,
// caller cleans). Largest-diagonal / trace method; every temporary stays in 80-bit x87 registers.
static void hkQuaternion_setFromRotation(const hkRotation* rot, hkQuaternion* out)
{
    const float* m = rot->m_el;
    float q[4];
    // X87-PRECISION: trace sum, sqrt and 0.5/root are kept unrounded on the FPU stack.
    hkX87Real trace = ((hkX87Real)m[5] + m[0]) + m[10];
    if (trace > 0.0f) {
        hkX87Real root = sqrt(trace + 1.0f);                // fsqrt (inline x87), operand is long double
        hkX87Real scale = 0.5f / root;                      // fdiv
        q[0] = (float)(((hkX87Real)m[6] - m[9]) * scale);   // [0x18]-[0x24]
        q[1] = (float)(((hkX87Real)m[8] - m[2]) * scale);   // [0x20]-[0x08]
        q[2] = (float)(((hkX87Real)m[1] - m[4]) * scale);   // [0x04]-[0x10]
        q[3] = (float)(root * 0.5f);
    } else {
        static const int nxt[3] = { 1, 2, 0 };
        int i = 0;
        if (m[5] > m[0]) i = 1;                      // fcomp: strict >, NaN -> false
        if (m[10] > m[i * 5]) i = 2;
        int j = nxt[i];
        int k = nxt[j];
        // X87-PRECISION: (m_ii - (m_kk + m_jj)) + 1 and the sqrt/scale stay in extended precision.
        hkX87Real root = sqrt(((hkX87Real)m[i * 5] - ((hkX87Real)m[k * 5] + m[j * 5])) + 1.0f);
        hkX87Real scale = 0.5f / root;
        q[i] = (float)(root * 0.5f);
        q[3] = (float)(((hkX87Real)m[k + 4 * j] - m[j + 4 * k]) * scale);
        q[j] = (float)(((hkX87Real)m[i + 4 * j] + m[j + 4 * i]) * scale);
        q[k] = (float)(((hkX87Real)m[i + 4 * k] + m[k + 4 * i]) * scale);
    }
    out->m_vec[0] = q[0];
    out->m_vec[1] = q[1];
    out->m_vec[2] = q[2];
    out->m_vec[3] = q[3];
}

// @ 0x01082490
void hkQuaternion::set(const hkRotation& r)
{
    hkQuaternion_setFromRotation(&r, this);
}

// @ 0x010824a0
void hkRotation::set(const hkQuaternion& q)
{
    const float* v = q.m_vec;
    // X87-PRECISION: 2x and 2y stay in 80-bit registers, as do the products wy and wz (never stored).
    hkX87Real x2 = (hkX87Real)v[0] + v[0];
    hkX87Real y2 = (hkX87Real)v[1] + v[1];
    float z2 = (float)((hkX87Real)v[2] + v[2]);     // stored to a float local ([esp+0x20])
    float xx = (float)(x2 * v[0]);
    float xy = (float)(y2 * v[0]);
    float xz = (float)(z2 * v[0]);
    float yy = (float)(y2 * v[1]);
    float yz = (float)(z2 * v[1]);
    float zz = (float)(z2 * v[2]);
    float wx = (float)(x2 * v[3]);
    hkX87Real wy = y2 * v[3];                       // kept on the FPU stack
    hkX87Real wz = (hkX87Real)z2 * v[3];            // kept on the FPU stack

    float* m = m_el;
    m[3] = 0.0f;
    m[0] = (float)(1.0f - ((hkX87Real)zz + yy));
    m[1] = (float)(xy + wz);
    m[2] = (float)(xz - wy);
    m[7] = 0.0f;
    m[4] = (float)(xy - wz);
    m[5] = (float)(1.0f - ((hkX87Real)zz + xx));
    m[6] = (float)((hkX87Real)wx + yz);
    m[11] = 0.0f;
    m[8] = (float)(wy + xz);
    m[9] = (float)((hkX87Real)yz - wx);
    m[10] = (float)(1.0f - ((hkX87Real)yy + xx));
}

// ------------------------------------------------------------ hkWorldObject
struct hkShape : hkReferencedObject {};
struct hkStatisticsCollector {
    virtual void s0(); virtual void s1();
    virtual void addArray(const char* name, int elemSize, const void* ptr, int usedBytes, int allocatedBytes);   // +8
    virtual void addReferencedObject(const char* name, int a, const void* obj);                                    // +0xc
};
struct hkPropertyValue { uint32_t m_lo, m_hi; };       // 64-bit payload
struct hkProperty { uint32_t m_key; uint32_t m_alignmentPadding; hkPropertyValue m_value; };   // 0x10
struct hkTypedBroadPhaseHandle { uint32_t m_id; uint8_t m_type; int8_t m_ownerOffset; int16_t m_objectQualityType; uint32_t m_collisionFilterInfo; };  // 0xc
struct hkLinkedCollidable {                            // size 0x30
    hkShape* m_shape;                                  // +0x00 (hkCdBody)
    uint32_t m_shapeKey;                               // +0x04
    void* m_motion;                                    // +0x08
    void* m_parent;                                    // +0x0c
    int m_ownerOffset;                                 // +0x10
    hkTypedBroadPhaseHandle m_broadPhaseHandle;        // +0x14
    float m_allowedPenetrationDepth;                   // +0x20
    hkArray<void*[2]> m_collisionEntries;              // +0x24  (8-byte entries)
};
struct hkMultiThreadLock { uint32_t m_threadId; int m_lockCount; };
class hkBool
{
public:
    hkBool(bool b) : m_bool(b ? 1 : 0) {}
    operator bool() const { return m_bool != 0; }
private:
    char m_bool;
};


struct hkWorldObject : hkReferencedObject {
    void* m_world;                                     // +0x08
    void* m_userData;                                  // +0x0c
    const char* m_name;                                // +0x10
    hkMultiThreadLock m_multithreadLock;               // +0x14
    hkLinkedCollidable m_collidable;                   // +0x1c
    hkArray<hkProperty> m_properties;                  // +0x4c

    hkWorldObject(const hkShape* shape, int broadPhaseType);
    explicit hkWorldObject(int finishLoadedFlag);      // hkFinishLoadedObjectFlag ctor
    ~hkWorldObject();
    virtual void calcStatistics(hkStatisticsCollector* c) const;
    virtual void slot2() {}
    virtual void* getMotionState() = 0;
    virtual void slot4() = 0;

    void addProperty(uint32_t key, hkPropertyValue value);
    hkPropertyValue editProperty(uint32_t key, hkPropertyValue value);
};

// @ 0x01082590 (addReference; see hkReferencedObject::addReference)

// @ 0x010825a0
void hkWorldObject::addProperty(uint32_t key, hkPropertyValue value)
{
    for (int i = 0; i < m_properties.m_size; ++i)
        if (m_properties.m_data[i].m_key == key) return;       // already present: nothing is added
    hkProperty p;
    p.m_key = key;
    p.m_value = value;
    m_properties.pushBack(p);                                  // m_alignmentPadding is not written
}

// @ 0x01082600
hkPropertyValue hkWorldObject::editProperty(uint32_t key, hkPropertyValue value)
{
    for (int i = 0; i < m_properties.m_size; ++i) {
        if (m_properties.m_data[i].m_key == key) {
            hkPropertyValue old = m_properties.m_data[i].m_value;
            m_properties.m_data[i].m_value = value;
            return old;
        }
    }
    hkPropertyValue none; none.m_lo = 0; none.m_hi = 0;
    return none;
}

// @ 0x01082660
void hkWorldObject::calcStatistics(hkStatisticsCollector* c) const
{
    c->addReferencedObject("Shape", 1, m_collidable.m_shape);
    if (m_collidable.m_collisionEntries.m_capacityAndFlags >= 0)
        c->addArray("CollAgtPtr", 8, m_collidable.m_collisionEntries.m_data,
                    m_collidable.m_collisionEntries.m_size << 3,
                    (m_collidable.m_collisionEntries.m_capacityAndFlags & HK_ARRAY_FLAG_MASK) << 3);
    if (m_properties.m_capacityAndFlags >= 0)
        c->addArray("Properties", 4, m_properties.m_data,
                    m_properties.m_size << 4,
                    (m_properties.m_capacityAndFlags & HK_ARRAY_FLAG_MASK) << 4);
}

// @ 0x010826e0
// hkWorldObject(hkFinishLoadedObjectFlag): fixes up the members that must not come from the file.
hkWorldObject::hkWorldObject(int finishLoadedFlag)
{
    m_multithreadLock.m_threadId = 0xffffffd1u;
    m_multithreadLock.m_lockCount = 0;
    m_collidable.m_broadPhaseHandle.m_id = 0;
    if (finishLoadedFlag)
        m_collidable.m_broadPhaseHandle.m_ownerOffset =
            (int8_t)(uint8_t)((uint8_t)(uintptr_t)&m_collidable - (uint8_t)(uintptr_t)&m_collidable.m_broadPhaseHandle);
    m_collidable.m_collisionEntries.m_data = 0;
    m_collidable.m_collisionEntries.m_size = 0;
    m_collidable.m_collisionEntries.m_capacityAndFlags = HK_ARRAY_DONT_DEALLOCATE;
    if (finishLoadedFlag)
        m_collidable.m_ownerOffset = (int)((char*)this - (char*)&m_collidable);
}

// @ 0x01082770
hkWorldObject::~hkWorldObject()
{
    if (m_collidable.m_shape != 0)
        m_collidable.m_shape->removeReference();
    m_properties.quickFree();
    m_collidable.m_collisionEntries.quickFree();
}

// @ 0x01082800
hkWorldObject::hkWorldObject(const hkShape* shape, int broadPhaseType)
{
    m_world = 0;
    m_userData = 0;
    m_name = 0;
    m_multithreadLock.m_threadId = 0xffffffd1u;
    m_multithreadLock.m_lockCount = 0;
    m_collidable.m_motion = 0;
    m_collidable.m_parent = 0;
    m_collidable.m_shapeKey = 0xffffffffu;
    m_collidable.m_ownerOffset = 0;
    m_collidable.m_shape = (hkShape*)shape;
    m_collidable.m_broadPhaseHandle.m_type = (uint8_t)broadPhaseType;
    m_collidable.m_broadPhaseHandle.m_id = 0;
    m_collidable.m_broadPhaseHandle.m_collisionFilterInfo = 0;
    m_collidable.m_broadPhaseHandle.m_ownerOffset =
        (int8_t)(uint8_t)((uint8_t)(uintptr_t)&m_collidable - (uint8_t)(uintptr_t)&m_collidable.m_broadPhaseHandle);
    m_collidable.m_collisionEntries.m_capacityAndFlags = HK_ARRAY_DONT_DEALLOCATE;
    m_collidable.m_collisionEntries.m_data = 0;
    m_collidable.m_collisionEntries.m_size = 0;
    m_properties.m_capacityAndFlags = HK_ARRAY_DONT_DEALLOCATE;
    m_properties.m_data = 0;
    m_properties.m_size = 0;
    m_collidable.m_ownerOffset = (int)((char*)this - (char*)&m_collidable);
    if (shape != 0)
        m_collidable.m_shape->addReference();
}

// ------------------------------------------------------------ solver info
struct hkSolverInfo {
    float m_one;                       // +0x00
    float m_tau;                       // +0x04
    float m_damping;                   // +0x08
    float m_frictionTau;               // +0x0c
    float pad10[16];                   // +0x10 .. +0x2f
    hkVector4 m_integrateVelocityFactor;      // +0x30
    hkVector4 m_invIntegrateVelocityFactor;   // +0x40
    float m_dampDivTau;                // +0x50
    float m_tauDivDamp;                // +0x54
    float m_dampDivFrictionTau;        // +0x58
    float m_frictionTauDivDamp;        // +0x5c
    void setTauAndDamping(hkReal tau, hkReal damping);
};

// @ 0x01082890
void hkSolverInfo::setTauAndDamping(hkReal tau, hkReal damping)
{
    // X87-PRECISION: frictionTau (tau*0.5), 1/damping and (1/damping)*tau are used again from the
    // FPU stack without being rounded to float first.
    hkX87Real frictionTauExt = (hkX87Real)tau * 0.5f;
    m_tau = tau;
    m_damping = damping;
    m_frictionTau = (float)frictionTauExt;
    m_dampDivTau = (float)((hkX87Real)damping / tau);
    m_dampDivFrictionTau = (float)((hkX87Real)damping / frictionTauExt);
    hkX87Real invDampExt = 1.0f / (hkX87Real)damping;
    float invDamp = (float)invDampExt;                          // stored back into the argument slot
    hkX87Real tauDivDampExt = invDampExt * tau;
    m_tauDivDamp = (float)tauDivDampExt;
    m_frictionTauDivDamp = (float)((hkX87Real)invDamp * frictionTauExt);
    float f = (float)tauDivDampExt;
    m_integrateVelocityFactor.x = f;
    m_integrateVelocityFactor.y = f;
    m_integrateVelocityFactor.z = f;
    m_integrateVelocityFactor.w = f;
    float g = m_dampDivTau;
    m_invIntegrateVelocityFactor.x = g;
    m_invIntegrateVelocityFactor.y = g;
    m_invIntegrateVelocityFactor.z = g;
    m_invIntegrateVelocityFactor.w = g;
}

// @ 0x01082900
struct hkMultithreadConfig {
    int m_canCpuTakeSpuTasks;
    uint8_t m_splitConstraintSolvingJob;
    hkMultithreadConfig();
};
hkMultithreadConfig::hkMultithreadConfig()
{
    m_splitConstraintSolvingJob = 0;
    m_canCpuTakeSpuTasks = 0;
}

// ------------------------------------------------------------ timers (hkMonitorStream)
extern unsigned long g_hkTimerCur;     // 0x16e42a4  current write pointer (TLS)
extern unsigned long g_hkTimerEnd;     // 0x16e42a8  end of the stream (TLS)
struct hkTimerEntry3 { const char* name; uint32_t time; uint32_t pad; };                       // 12 bytes on x86
struct hkTimerEntry4 { const char* name; uint32_t time; uint32_t pad; const char* name2; };    // 16 bytes on x86
static inline bool hkTimerHasRoom()
{
    uintptr_t end = (uintptr_t)TlsGetValue(g_hkTimerEnd);
    uintptr_t cur = (uintptr_t)TlsGetValue(g_hkTimerCur);
    return cur < end;
}
static inline void hkTimerSplit(const char* name)
{
    if (hkTimerHasRoom()) {
        hkTimerEntry3* p = (hkTimerEntry3*)TlsGetValue(g_hkTimerCur);
        p->name = name;
        p->time = (uint32_t)__rdtsc();
        TlsSetValue(g_hkTimerCur, p + 1);
    }
}
static inline void hkTimerBeginList(const char* name, const char* name2)
{
    if (hkTimerHasRoom()) {
        hkTimerEntry4* p = (hkTimerEntry4*)TlsGetValue(g_hkTimerCur);
        p->name = name;
        p->name2 = name2;
        p->time = (uint32_t)__rdtsc();
        TlsSetValue(g_hkTimerCur, p + 1);
    }
}

// ------------------------------------------------------------ hkWorld
struct hkEntity; struct hkPhantom; struct hkWorld; struct hkSimulationIsland;
struct hkBroadPhase; struct hkCollisionFilter; struct hkProcessCollisionInput; struct hkRayHitCollector;
struct hkCdPointCollector; struct hkCollidable; struct hkWorldRayCastInput; struct hkLinearCastInput;
struct hkWorldMemoryWatchDog { char pad[8]; int m_memoryLimit; virtual void s0(); virtual void s1(); virtual void freeMemory(hkWorld* w); };
struct hkWorldOperationQueue;
struct hkWorldDeletionListener;
struct hkSimulation { virtual void s0(); virtual void s1(); virtual int stepDeltaTime(hkWorld* w, hkReal physicsDeltaTime, hkReal frameDeltaTime); };

enum hkEntityActivation { HK_ENTITY_ACTIVATION_DO_NOT_ACTIVATE = 0, HK_ENTITY_ACTIVATION_DO_ACTIVATE = 1 };
struct hkWorldOperationBase { uint8_t m_type; void* m_object; int m_arg; };   // queued op record

struct hkWorld : hkReferencedObject {
    hkSimulation* m_simulation;                        // +0x08
    uint32_t pad0c[9];                                 // +0x0c..0x2f
    void* m_fixedIsland;                               // +0x30
    void* m_fixedRigidBody;                            // +0x34
    hkArray<hkSimulationIsland*> m_activeSimulationIslands;     // +0x38
    uint32_t pad44[6];                                 // +0x44..0x5b
    void* m_maintenanceMgr;                            // +0x5c
    hkWorldMemoryWatchDog* m_memoryWatchDog;           // +0x60
    hkBroadPhase* m_broadPhase;                        // +0x64
    uint32_t pad68[4];                                 // +0x68..0x77
    hkProcessCollisionInput* m_collisionInput;         // +0x78
    hkCollisionFilter* m_collisionFilter;              // +0x7c
    void* m_collisionDispatcher;                       // +0x80
    hkWorldOperationQueue* m_pendingOperations;        // +0x84
    int m_pendingOperationsCount;                      // +0x88
    int m_lockCount;                                   // +0x8c
    int m_lockCountForPhantoms;                        // +0x90
    uint8_t m_blockExecutingPendingOperations;         // +0x94
    uint8_t m_criticalOperationsAllowed;               // +0x95
    uint16_t pad96[23];                                // +0x96..0xc3
    int m_simulationType;                              // +0xc4
    uint32_t m_lastEntityUid;                          // +0xc8
    hkArray<hkPhantom*> m_phantoms;                    // +0xcc
    uint32_t padd8[12];                                // +0xd8..0x107
    hkArray<hkWorldDeletionListener*> m_worldDeletionListeners;   // +0x108

    hkEntity* addEntity(hkEntity* entity, hkEntityActivation initialActivationState);
    uint8_t removeEntity(hkEntity* entity);
    hkPhantom* addPhantom(hkPhantom* phantom);
    void castRay(const hkWorldRayCastInput& input, hkRayHitCollector& output) const;
    void linearCast(const hkCollidable* collA, const hkLinearCastInput& input,
                    hkCdPointCollector& castCollector, hkCdPointCollector* startCollector) const;
    int stepDeltaTime(hkReal physicsDeltaTime);
    void executePendingOperations();
    void removeWorldDeletionListener(hkWorldDeletionListener* l);
    int calcMaxIslandSizeEstimate() const;
};

// Entities/phantoms as far as these functions see them (hkWorldObject plus a few fields).
struct hkMotion { char pad[0x10]; char m_motionState[1]; };    // hkMotionState starts at +0x10
struct hkEntity : hkWorldObject {
    hkMotion* m_motion;                                // +0x58
    uint32_t pad5c[28];                                // +0x5c..0xcb
    uint32_t m_uid;                                    // +0xcc
};
struct hkPhantom : hkWorldObject {
    void firePhantomAdded();                           // 0x0108e370
    // hkPhantom virtual slots after the four hkWorldObject ones (used by hkWorld_updatePhantomOverlap, 0x01082910)
    virtual void slot5() = 0;
    virtual void addOverlappingCollidable(hkLinkedCollidable* c) = 0;                          // slot 6 (+0x18)
    virtual hkBool isOverlappingCollidableAdded(const hkLinkedCollidable* c) = 0;              // slot 7 (+0x1c)
    virtual void removeOverlappingCollidable(hkLinkedCollidable* c) = 0;                       // slot 8 (+0x20)
};

// External (identical-code) callees, from the real mangled names.
struct hkSweptTransformUtil { };
void hkSweptTransformUtil_setTimeInformation(float a, float b, hkMotion* motionState);      // ?setTimeInformation@hkSweptTransformUtil@@YAXMMAAVhkMotionState@@@Z
struct hkWorldOperationUtil {
    static void addEntitySI(hkWorld*, hkEntity*, hkEntityActivation);   // 0x109fb70
    static void addEntityBP(hkWorld*, hkEntity*);                       // 0x10a0be0
    static void removeEntityBP(hkWorld*, hkEntity*);                    // 0x10a0e20
    static void removeEntitySI(hkWorld*, hkEntity*);                    // 0x10a03c0 (FUN_)
    static void addPhantomBP(hkWorld*, hkPhantom*);                     // 0x10a0d10
};
struct hkWorldCallbackUtil {
    static void fireEntityAdded(hkWorld*, hkEntity*);                   // 0x109ebc0
    static void fireEntityRemoved(hkWorld*, hkEntity*);                 // 0x109ec50
    static void firePhantomAdded(hkWorld*, hkPhantom*);                 // 0x109ed70
};
struct hkEntityCallbackUtil {
    static void fireEntityAdded(hkEntity*);                             // 0x109e730
    static void fireEntityRemoved(hkEntity*);                           // 0x109ea00
};
struct hkWorldOperationQueue {
    void queueOperation(const hkWorldOperationBase& op);                // 0x109afe0
    void executeAllPending();                                           // 0x109b490
};
void hkSimulation_removeEntity(hkSimulation* sim, hkEntity* e);         // 0x10a08b0
void hkWorldObject_removeReference(hkWorldObject* o);                   // 0x109ae60

// @ 0x01082990
struct hkWorldRayCaster {
    const void* vtbl_;
    uint32_t pad[15];
    void* m_a;                                          // +0x40 zeroed by the constructor
    void* m_b;                                          // +0x44 zeroed by the constructor
    hkWorldRayCaster() { m_a = 0; m_b = 0; }
    void castRay(hkBroadPhase& bp, const hkWorldRayCastInput& input, const hkCollisionFilter* filter,
                 char* unused, hkRayHitCollector& collector);
    virtual void addBroadPhaseHandle() {}
};
void hkWorld::castRay(const hkWorldRayCastInput& input, hkRayHitCollector& output) const
{
    hkWorldRayCaster caster;
    caster.castRay(*m_broadPhase, input, m_collisionFilter, 0, output);
}

// @ 0x010829e0
// hkNullContactMgr: returns an invalid/zero contact point id for every request (4 stack args).
struct hkNullContactMgr {
    virtual void s0(); virtual void s1();
    virtual uint16_t addContactPoint(int a, int b, int c, int d);       // 0x010829e0
    virtual uint8_t processRequest(int a, int b, int c, int d, int e, int f, int g);   // 0x01082a00
};
uint16_t hkNullContactMgr::addContactPoint(int, int, int, int) { return 0; }

// @ 0x01082a00
uint8_t hkNullContactMgr::processRequest(int, int, int, int, int, int, int) { return 1; }

// @ 0x01082a40
// hkWorld::removeWorldDeletionListener: the original (assert compiled out) writes data[-1] when
// the listener is not registered; the same write is kept (idx == -1).
void hkWorld::removeWorldDeletionListener(hkWorldDeletionListener* l)
{
    int idx = m_worldDeletionListeners.indexOf(l);
    m_worldDeletionListeners.m_data[idx] = 0;
}

// @ 0x01082a90
int hkWorld::stepDeltaTime(hkReal physicsDeltaTime)
{
    int result = m_simulation->stepDeltaTime(this, physicsDeltaTime, physicsDeltaTime);
    if (result == 0) {
        hkWorldMemoryWatchDog* wd = m_memoryWatchDog;
        if (wd != 0 && g_hkMemory->m_stat28 + g_hkMemory->m_stat14 > wd->m_memoryLimit) {
            hkTimerSplit("TtWatchDog:FreeMem");
            wd->freeMemory(this);
            hkTimerSplit("Et");        // end marker (shared "Et" string at 0x149cc34)
        }
    }
    return result;
}

// @ 0x01082b90
struct hkWorldLinearCaster {
    const void* vtbl_;
    uint32_t pad[15];
    float m_shapeInputTolerance;                        // +0x40 = 2^-23 (0x34000000)
    uint32_t pad2[3];
    virtual void addBroadPhaseHandle() {}
    void linearCast(const hkBroadPhase& bp, const hkCollidable* collA, const hkLinearCastInput& input,
                    const void* filter, const hkProcessCollisionInput* collisionInput, void* config,
                    hkCdPointCollector& castCollector, hkCdPointCollector* startCollector);
};
struct hkProcessCollisionInput { char pad[0x20]; void* m_config; };
void hkWorld::linearCast(const hkCollidable* collA, const hkLinearCastInput& input,
                         hkCdPointCollector& castCollector, hkCdPointCollector* startCollector) const
{
    hkWorldLinearCaster caster;
    caster.m_shapeInputTolerance = 1.1920929e-007f;     // 0x1.0p-23f
    // hkCollisionFilter derives from hkCollidableCollidableFilter as its second base (+8)
    const void* filter = m_collisionFilter ? (const void*)((const char*)m_collisionFilter + 8) : 0;
    caster.linearCast(*m_broadPhase, collA, input, filter, m_collisionInput, m_collisionInput->m_config,
                      castCollector, startCollector);
}

// @ 0x01082bf0
void hkWorld::executePendingOperations()
{
    hkTimerSplit("TtPendingOps");
    hkWorldOperationQueue* q = m_pendingOperations;
    m_pendingOperationsCount = 0;
    q->executeAllPending();
    hkTimerSplit("Et");
}

// @ 0x01082ca0
// Largest per-island size estimate over the active simulation islands (visited back to front).
struct hkSimulationIsland {
    uint32_t pad[3];
    int m_c;      // +0x0c
    int m_d;      // +0x10
    int m_a;      // +0x14
    int m_b;      // +0x18
};
int hkWorld::calcMaxIslandSizeEstimate() const
{
    int maxSize = 0;
    for (int i = m_activeSimulationIslands.m_size - 1; i >= 0; --i) {
        const hkSimulationIsland* isl = m_activeSimulationIslands.m_data[i];
        int v = ((isl->m_a + isl->m_b * 4 + 0x9c) + isl->m_d) + isl->m_c;
        if (!(maxSize > v)) maxSize = v;
    }
    return maxSize;
}

// ------------------------------------------------------------ contact manager factories
struct hkContactMgrFactory : hkReferencedObject { };
struct hkNullContactMgrFactory : hkContactMgrFactory {
    hkNullContactMgr* m_nullContactMgr_slot;                // embedded mgr (vptr) lives at +8
    uint16_t m_pad0c, m_type;
    HK_CLASS_ALLOC(4)
    virtual hkNullContactMgr* createContactMgr(int a, int b, int c);   // 0x01082ce0 returns this+8
    virtual ~hkNullContactMgrFactory() {}
};
// @ 0x01082ce0
hkNullContactMgr* hkNullContactMgrFactory::createContactMgr(int, int, int)
{
    return (hkNullContactMgr*)&m_nullContactMgr_slot;
}

// @ 0x01082cf0
void hkNullContactMgrFactory_deletingDtor(hkNullContactMgrFactory* self, unsigned flags)
{
    delete self;
}

// @ 0x01082d20
// hkNullCollisionFilter: hkCollisionFilter is hkReferencedObject plus four filter interfaces (collidable pair
// at +8, shape collection at +0xc, ray shape collection at +0x10, ray collidable at +0x14), 0x18 bytes in all.
// The constructor stores the interface vtables of the abstract bases (0x013EF82C / 0x013EF824, dead stores the
// compiler left in) and then the hkNullCollisionFilter ones: 0x0149DBA0 (hkReferencedObject part) and
// 0x0149DB98 / 0x0149DB90 / 0x0149DB88 / 0x0149DB80 for the four interfaces (slot 0 of each is a shared
// destructor-like stub, slot 1 is isCollisionEnabled, which the null filter answers with "true").
// Named from those vtables: the same layout is used by hkWorld::setCollisionFilter(null) (slice s010869e0).
struct hkCollidableCollidableFilter
{
    virtual void s0();
    virtual hkBool isCollisionEnabled(const struct hkLinkedCollidable& a, const struct hkLinkedCollidable& b) const = 0;   // slot 1
};
struct hkShapeCollectionFilter { virtual void s0(); virtual hkBool isCollisionEnabled(const void* a, const void* b, const void* bContainer, uint32_t bKey) const = 0; };
struct hkRayShapeCollectionFilter { virtual void s0(); virtual hkBool isCollisionEnabled(const void* input, const void* collection, uint32_t key) const = 0; };
struct hkRayCollidableFilter { virtual void s0(); virtual hkBool isCollisionEnabled(const void* input, const hkLinkedCollidable& c) const = 0; };
struct hkCollisionFilter : hkReferencedObject, hkCollidableCollidableFilter, hkShapeCollectionFilter,
                           hkRayShapeCollectionFilter, hkRayCollidableFilter
{
    hkCollisionFilter() {}
};
struct hkNullCollisionFilter : hkCollisionFilter
{
    hkNullCollisionFilter();                                                                    // 0x01082D20
    virtual hkBool isCollisionEnabled(const hkLinkedCollidable& a, const hkLinkedCollidable& b) const;
};
hkNullCollisionFilter::hkNullCollisionFilter() {}    // m_referenceCount = 1 comes from the hkReferencedObject base constructor

// @ 0x01082910
// Custom register convention (whole-program optimisation): this = EDI (the phantom), the other collidable = ESI,
// the collision filter is the single stack argument (caller pops it). Called from hkWorld::updateCollisionFilterOnPhantom.
// It makes the phantom's overlap bookkeeping agree with the filter: add the pair when the filter now allows it and the
// phantom does not know the collidable yet, remove it in the opposite case, and mirror the change on the other side
// when that collidable belongs to a phantom (broad phase handle type 2).
void hkWorld_updatePhantomOverlap(hkPhantom* phantom, hkLinkedCollidable* other, const hkCollisionFilter* filter)
{
    hkBool added = phantom->isOverlappingCollidableAdded(other);
    // the filter call goes through the hkCollidableCollidableFilter sub-object (filter + 8), slot 1
    hkBool enabled = static_cast<const hkCollidableCollidableFilter*>(filter)->isCollisionEnabled(phantom->m_collidable, *other);
    if (enabled)
    {
        if (!added)
        {
            phantom->addOverlappingCollidable(other);
            if (other->m_broadPhaseHandle.m_type == 2)
            {
                hkPhantom* otherPhantom = (hkPhantom*)((char*)other + other->m_ownerOffset);   // hkCollidable::getOwner
                otherPhantom->addOverlappingCollidable(&phantom->m_collidable);
            }
        }
    }
    else if (added)
    {
        phantom->removeOverlappingCollidable(other);
        if (other->m_broadPhaseHandle.m_type == 2)
        {
            hkPhantom* otherPhantom = (hkPhantom*)((char*)other + other->m_ownerOffset);
            otherPhantom->removeOverlappingCollidable(&phantom->m_collidable);
        }
    }
}

// ------------------------------------------------------------ register the default contact managers
// @ 0x01082df0
// Register the default contact manager factories (simple constraint, reactive, null) with a
// collision dispatcher. Original takes the world in EAX (private convention) and the dispatcher
// on the stack.
struct hkCollisionDispatcher { void registerContactMgrFactory(hkContactMgrFactory* f, int responseType); };   // 0x10ccbd0
hkContactMgrFactory* hkSimpleConstraintContactMgr_Factory_create(hkWorld* w);       // 0x108d850 ctor
hkContactMgrFactory* hkReactiveContactMgr_Factory_create(hkWorld* w);               // 0x109e6a0 ctor
void hkWorld_registerContactMgrFactories(hkWorld* world, hkCollisionDispatcher* d)
{
    hkContactMgrFactory* simple = hkSimpleConstraintContactMgr_Factory_create(world);
    hkContactMgrFactory* reactive = hkReactiveContactMgr_Factory_create(world);
    hkNullContactMgrFactory* nullF = new hkNullContactMgrFactory();
    nullF->m_type = 1;
    d->registerContactMgrFactory(simple, 1);
    d->registerContactMgrFactory(reactive, 2);
    d->registerContactMgrFactory(nullF, 3);
    simple->removeReference();
    reactive->removeReference();
    nullF->removeReference();
}

// @ 0x01082ee0
hkEntity* hkWorld::addEntity(hkEntity* entity, hkEntityActivation initialActivationState)
{
    if (m_lockCount != 0) {
        hkWorldOperationBase op;
        op.m_type = 1;
        op.m_object = entity;
        op.m_arg = (int)initialActivationState;
        m_pendingOperations->queueOperation(op);
        return 0;
    }
    hkTimerBeginList("LtAddEntity", "Island");
    if (entity->m_collidable.m_motion == 0)
        entity->m_collidable.m_motion = entity->getMotionState();
    hkSweptTransformUtil_setTimeInformation(0.0f, 0.0f, (hkMotion*)((char*)entity->m_motion + 0x10));
    ++m_lastEntityUid;
    m_criticalOperationsAllowed = 0;
    entity->m_uid = m_lastEntityUid;
    entity->addReference();
    hkWorldOperationUtil::addEntitySI(this, entity, initialActivationState);
    m_criticalOperationsAllowed = 1;
    m_lockCount = m_lockCount + 1;
    hkTimerSplit("StBroadphase");
    hkWorldOperationUtil::addEntityBP(this, entity);
    hkTimerSplit("StCallbacks");
    hkWorldCallbackUtil::fireEntityAdded(this, entity);
    hkEntityCallbackUtil::fireEntityAdded(entity);
    m_lockCount = m_lockCount - 1;
    if (m_lockCount == 0 && m_pendingOperationsCount != 0 && m_blockExecutingPendingOperations == 0)
        executePendingOperations();
    hkTimerSplit("lt");      // list end marker (0x143cd94)
    return entity;
}

// @ 0x01083110
uint8_t hkWorld::removeEntity(hkEntity* entity)
{
    if (m_lockCount != 0) {
        hkWorldOperationBase op;
        op.m_type = 2;
        op.m_object = entity;
        m_pendingOperations->queueOperation(op);
        return 0;
    }
    m_lockCount = 1;
    hkTimerBeginList("LtRemEntity", "Broadphase");
    hkWorldOperationUtil::removeEntityBP(this, entity);
    if (m_simulationType >= 4)
        hkSimulation_removeEntity(m_simulation, entity);
    hkTimerSplit("StCallbacks");
    hkWorldCallbackUtil::fireEntityRemoved(this, entity);
    hkEntityCallbackUtil::fireEntityRemoved(entity);
    m_criticalOperationsAllowed = 0;
    hkTimerSplit("StIsland");
    hkWorldOperationUtil::removeEntitySI(this, entity);
    if (entity->m_memSizeAndFlags == 0)
        entity->slot4();
    hkWorldObject_removeReference(entity);
    m_criticalOperationsAllowed = 1;
    m_lockCount = m_lockCount - 1;
    if (m_lockCount == 0 && m_pendingOperationsCount != 0 && m_blockExecutingPendingOperations == 0)
        executePendingOperations();
    hkTimerSplit("lt");      // list end marker (0x143cd94)
    return 1;
}

// @ 0x01083320
hkPhantom* hkWorld::addPhantom(hkPhantom* phantom)
{
    if (m_lockCountForPhantoms + m_lockCount != 0) {
        hkWorldOperationBase op;
        op.m_type = 0xd;
        op.m_object = phantom;
        m_pendingOperations->queueOperation(op);
        return 0;
    }
    m_lockCount = m_lockCount + 1;
    if (phantom->m_collidable.m_motion == 0)
        phantom->m_collidable.m_motion = phantom->getMotionState();
    phantom->m_world = this;
    phantom->addReference();
    m_phantoms.pushBack(phantom);
    hkWorldOperationUtil::addPhantomBP(this, phantom);
    hkWorldCallbackUtil::firePhantomAdded(this, phantom);
    phantom->firePhantomAdded();
    m_lockCount = m_lockCount - 1;
    if (m_lockCount == 0 && m_pendingOperationsCount != 0 && m_blockExecutingPendingOperations == 0)
        executePendingOperations();
    return phantom;
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct hkCollisionDispatcher {
    void registerContactMgrFactory(void*, int); // 0x010ccbd0
};
}
