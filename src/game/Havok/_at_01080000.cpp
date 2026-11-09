// src/game/Havok/_at_01080000.cpp -- migrated from slice(s) s0108eb30, s0108e080, s0108b2f0, s0108a3f0, s010898f0, s01088960, s01084cf0, s01083400, s01082350, s010813d0 by tools/migrate/rewrite.py
// Object file: Havok/_at_01080000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <stddef.h>
#include <math.h>
#include <new>

// ---- items of slice s010813d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace hkMath
{
	template <typename T> T max2(T a, T b);
	template <> float max2<float>(float a, float b);
	float acos(float x);   // 0x01082160 (name guessed: clamped arc cosine)
}
// ---- items of slice s010813d0 end

// ---- items of slice s01082350 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int __stdcall TlsSetValue(unsigned long, void*);
extern "C" unsigned __int64 __rdtsc();
extern "C" void* _AddressOfReturnAddress(void);
extern unsigned long g_hkThreadMemoryTlsIndex;       // 0x16e4174
extern unsigned long g_hkTimerCur;     // 0x16e42a4  current write pointer (TLS)
extern unsigned long g_hkTimerEnd;     // 0x16e42a8  end of the stream (TLS)
#pragma intrinsic(__rdtsc)
#pragma intrinsic(_AddressOfReturnAddress)
typedef double hkX87Real;
typedef float hkReal;
class hkVector4_s0108_2350 { public: float x, y, z, w; };
class hkQuaternion_s0108_2350 {  // x y z w
    public: float m_vec[4];
    uint32_t set(const class hkRotation_s0108_2350& r);
    void toQuatImpl(const class hkRotation_s0108_2350& r);
};
class hkRotation_s0108_2350 {  // 3 columns of 4 floats (col*4+row)
    public: float m_el[12];
    void set(const hkQuaternion_s0108_2350& q);
    uint32_t toQuat() const;
};
enum { HK_ARRAY_FLAG_MASK = 0x3fffffff, HK_ARRAY_DONT_DEALLOCATE = (int)0x80000000 };
struct hkArrayUtil { static void _reserveMore(void* arr, int elemSize); };
class hkThreadMemory { public: void deallocateChunk(void* p, int nbytes, int memClass); };
static inline hkThreadMemory* getThreadMemory() { return (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTlsIndex); }
template <typename T>
class hkArray { public:
    T* m_data; int m_size; int m_capacityAndFlags;
    void pushBack(const T& t) {
        if (m_size == (m_capacityAndFlags & HK_ARRAY_FLAG_MASK)) hkArrayUtil::_reserveMore(this, (int)sizeof(T));
        m_data[m_size] = t;
        m_size = m_size + 1;
    }
    void quickFree() {
        if (m_capacityAndFlags & HK_ARRAY_DONT_DEALLOCATE)
            return;
        getThreadMemory()->deallocateChunk(m_data, (m_capacityAndFlags & HK_ARRAY_FLAG_MASK) * (int)sizeof(T), 0x14);
    }
    int indexOf(const T& t) const {
        int i = 0;
        while (i < m_size) { if (m_data[i] == t) return i; ++i; }
        return -1;
    }
};
class hkMemory { public:
    virtual void* allocateChunk(int nbytes, int memClass);
virtual void s1();
virtual void s2();
virtual void s3();
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
class hkReferencedObject_s0108_2350 { public:
    uint16_t m_memSizeAndFlags;
    uint16_t m_referenceCount;
    hkReferencedObject_s0108_2350() : m_referenceCount(1) {}
    virtual ~hkReferencedObject_s0108_2350() {}
    virtual void calcStatistics(class hkStatisticsCollector* c) const {}
    void addReference() { if (m_memSizeAndFlags != 0) m_referenceCount = (uint16_t)(m_referenceCount + 1); }   // 0x01082590
    void removeReference() {
        if (m_memSizeAndFlags != 0) {
            m_referenceCount = (uint16_t)(m_referenceCount - 1);
            if (m_referenceCount == 0) delete this;
        }
    }
};
__declspec(noinline) void hkQuaternion_s0108_2350::toQuatImpl(const hkRotation_s0108_2350& r)
{
    const float* m = r.m_el;
    float q[4];
    hkX87Real trace = ((hkX87Real)m[5] + m[0]) + m[10];
    if (trace > 0.0f) {
        hkX87Real root = sqrt(trace + 1.0f);
        hkX87Real scale = 0.5f / root;
        q[0] = (float)(((hkX87Real)m[6] - m[9]) * scale);
        q[1] = (float)(((hkX87Real)m[8] - m[2]) * scale);
        q[2] = (float)(((hkX87Real)m[1] - m[4]) * scale);
        q[3] = (float)(root * 0.5f);
    } else {
        static const int nxt[3] = { 1, 2, 0 };
        int i = 0;
        if (m[5] > m[0]) i = 1;
        if (m[10] > m[i * 5]) i = 2;
        int j = nxt[i];
        int k = nxt[j];
        hkX87Real root = sqrt(((hkX87Real)m[i * 5] - ((hkX87Real)m[k * 5] + m[j * 5])) + 1.0f);
        hkX87Real scale = 0.5f / root;
        q[i] = (float)(root * 0.5f);
        q[3] = (float)(((hkX87Real)m[k + 4 * j] - m[j + 4 * k]) * scale);
        q[j] = (float)(((hkX87Real)m[i + 4 * j] + m[j + 4 * i]) * scale);
        q[k] = (float)(((hkX87Real)m[i + 4 * k] + m[k + 4 * i]) * scale);
    }
    m_vec[0] = q[0];
    m_vec[1] = q[1];
    m_vec[2] = q[2];
    m_vec[3] = q[3];
}
class hkShape_s0108_2350 : public hkReferencedObject_s0108_2350 { public:};
class hkStatisticsCollector { public:
virtual void s0();
virtual void s1();
    virtual void addArray(const char* name, int elemSize, const void* ptr, int usedBytes, int allocatedBytes);   // +8
    virtual void addReferencedObject(const char* name, int a, const void* obj);                                    // +0xc
};
struct hkPropertyValue_s0108_2350 { uint32_t m_lo, m_hi; };       // 64-bit payload
class hkProperty_s0108_2350 { public: uint32_t m_key; uint32_t m_alignmentPadding; hkPropertyValue_s0108_2350 m_value; };   // 0x10
class hkTypedBroadPhaseHandle_s0108_2350 { public: uint32_t m_id; uint8_t m_type; int8_t m_ownerOffset; int16_t m_objectQualityType; uint32_t m_collisionFilterInfo; };  // 0xc
class hkLinkedCollidable_s0108_2350 { public:                            // size 0x30
    hkShape_s0108_2350* m_shape;                                  // +0x00 (hkCdBody)
    uint32_t m_shapeKey;                               // +0x04
    void* m_motion;                                    // +0x08
    void* m_parent;                                    // +0x0c
    int m_ownerOffset;                                 // +0x10
    hkTypedBroadPhaseHandle_s0108_2350 m_broadPhaseHandle;        // +0x14
    float m_allowedPenetrationDepth;                   // +0x20
    hkArray<void*[2]> m_collisionEntries;              // +0x24  (8-byte entries)
};
class hkMultiThreadLock_s0108_2350 { public: uint32_t m_threadId; int m_lockCount; };
class hkBool_s0108_2350
{
public:
    hkBool_s0108_2350(bool b) : m_bool(b ? 1 : 0) {}
    operator bool() const { return m_bool != 0; }
private:
    char m_bool;
};
class hkWorldObject_s0108_2350 : public hkReferencedObject_s0108_2350 { public:
    void* m_world;                                     // +0x08
    void* m_userData;                                  // +0x0c
    const char* m_name;                                // +0x10
    hkMultiThreadLock_s0108_2350 m_multithreadLock;               // +0x14
    hkLinkedCollidable_s0108_2350 m_collidable;                   // +0x1c
    hkArray<hkProperty_s0108_2350> m_properties;                  // +0x4c

    hkWorldObject_s0108_2350(const hkShape_s0108_2350* shape, int broadPhaseType);
    explicit hkWorldObject_s0108_2350(int finishLoadedFlag);      // hkFinishLoadedObjectFlag ctor
    ~hkWorldObject_s0108_2350();
    virtual void calcStatistics(hkStatisticsCollector* c) const;
    virtual void slot2() {}
    virtual void* getMotionState() = 0;
    virtual void slot4() = 0;

    void addProperty(uint32_t key, hkPropertyValue_s0108_2350 value);
    hkPropertyValue_s0108_2350 editProperty(uint32_t key, hkPropertyValue_s0108_2350 value);
};
struct hkSolverInfo_s0108_2350 {
    float m_one;                       // +0x00
    float m_tau;                       // +0x04
    float m_damping;                   // +0x08
    float m_frictionTau;               // +0x0c
    float pad10[8];                    // +0x10 .. +0x2f
    hkVector4_s0108_2350 m_integrateVelocityFactor;      // +0x30
    hkVector4_s0108_2350 m_invIntegrateVelocityFactor;   // +0x40
    float m_dampDivTau;                // +0x50
    float m_tauDivDamp;                // +0x54
    float m_dampDivFrictionTau;        // +0x58
    float m_frictionTauDivDamp;        // +0x5c
    void setTauAndDamping(hkReal tau, hkReal damping);
};
struct hkMultithreadConfig {
    int m_canCpuTakeSpuTasks;
    uint8_t m_splitConstraintSolvingJob;
    hkMultithreadConfig();
};
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
class hkEntity_s0108_2350; class hkPhantom_s0108_2350; class hkWorld_s0108_2350; class hkSimulationIsland_s0108_2350;
struct hkBroadPhase; class hkCollisionFilter_s0108_2350; struct hkProcessCollisionInput_s0108_2350; struct hkRayHitCollector;
struct hkCdPointCollector; struct hkCollidable; struct hkWorldRayCastInput; struct hkLinearCastInput_s0108_2350;
struct hkWorldMemoryWatchDog { char pad[8]; int m_memoryLimit; virtual void s0(); virtual void s1(); virtual void freeMemory(hkWorld_s0108_2350* w); };
struct hkWorldOperationQueue;
struct hkWorldDeletionListener_s0108_2350;
struct hkSimulation { virtual void s0(); virtual void s1(); virtual int stepDeltaTime(hkWorld_s0108_2350* w, hkReal physicsDeltaTime, hkReal frameDeltaTime); };
enum hkEntityActivation { HK_ENTITY_ACTIVATION_DO_NOT_ACTIVATE = 0, HK_ENTITY_ACTIVATION_DO_ACTIVATE = 1 };
struct hkWorldOperationBase { uint8_t m_type; void* m_object; int m_arg; };   // queued op record
struct hkWorldOperationPrefix { uint8_t m_type; void* m_object; };
class hkWorld_s0108_2350 : public hkReferencedObject_s0108_2350 { public:
    hkSimulation* m_simulation;                        // +0x08
    uint32_t pad0c[9];                                 // +0x0c..0x2f
    void* m_fixedIsland;                               // +0x30
    void* m_fixedRigidBody;                            // +0x34
    hkArray<hkSimulationIsland_s0108_2350*> m_activeSimulationIslands;     // +0x38
    uint32_t pad44[6];                                 // +0x44..0x5b
    void* m_maintenanceMgr;                            // +0x5c
    hkWorldMemoryWatchDog* m_memoryWatchDog;           // +0x60
    hkBroadPhase* m_broadPhase;                        // +0x64
    uint32_t pad68[4];                                 // +0x68..0x77
    hkProcessCollisionInput_s0108_2350* m_collisionInput;         // +0x78
    hkCollisionFilter_s0108_2350* m_collisionFilter;              // +0x7c
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
    hkArray<hkPhantom_s0108_2350*> m_phantoms;                    // +0xcc
    uint32_t padd8[12];                                // +0xd8..0x107
    hkArray<hkWorldDeletionListener_s0108_2350*> m_worldDeletionListeners;   // +0x108

    hkEntity_s0108_2350* addEntity(hkEntity_s0108_2350* entity, hkEntityActivation initialActivationState);
    uint8_t removeEntity(hkEntity_s0108_2350* entity);
    hkPhantom_s0108_2350* addPhantom(hkPhantom_s0108_2350* phantom);
    void castRay(const hkWorldRayCastInput& input, hkRayHitCollector& output) const;
    void linearCast(const hkCollidable* collA, const hkLinearCastInput_s0108_2350& input,
                    hkCdPointCollector& castCollector, hkCdPointCollector* startCollector) const;
    int stepDeltaTime(hkReal physicsDeltaTime);
    void executePendingOperations();
    void removeWorldDeletionListener(hkWorldDeletionListener_s0108_2350* l);
    int calcMaxIslandSizeEstimate() const;
};
class hkMotion_s0108_2350 { public: char pad[0x10]; char m_motionState[1]; };    // hkMotionState starts at +0x10
class hkEntity_s0108_2350 : public hkWorldObject_s0108_2350 { public:
    hkMotion_s0108_2350* m_motion;                                // +0x58
    uint32_t pad5c[28];                                // +0x5c..0xcb
    uint32_t m_uid;                                    // +0xcc
};
class hkPhantom_s0108_2350 : public hkWorldObject_s0108_2350 { public:
    void firePhantomAdded();                           // 0x0108e370
    // hkPhantom virtual slots after the four hkWorldObject ones (used by hkWorld_updatePhantomOverlap, 0x01082910)
    virtual void slot5() = 0;
    virtual void addOverlappingCollidable(hkLinkedCollidable_s0108_2350* c) = 0;                          // slot 6 (+0x18)
    virtual hkBool_s0108_2350 isOverlappingCollidableAdded(const hkLinkedCollidable_s0108_2350* c) = 0;              // slot 7 (+0x1c)
    virtual void removeOverlappingCollidable(hkLinkedCollidable_s0108_2350* c) = 0;                       // slot 8 (+0x20)
};
void hkSweptTransformUtil_setTimeInformation(float a, float b, hkMotion_s0108_2350* motionState);      // ?setTimeInformation@hkSweptTransformUtil@@YAXMMAAVhkMotionState@@@Z
struct hkWorldOperationUtil {
    static void addEntitySI(hkWorld_s0108_2350*, hkEntity_s0108_2350*, hkEntityActivation);   // 0x109fb70
    static void addEntityBP(hkWorld_s0108_2350*, hkEntity_s0108_2350*);                       // 0x10a0be0
    static void removeEntityBP(hkWorld_s0108_2350*, hkEntity_s0108_2350*);                    // 0x10a0e20
    static void removeEntitySI(hkWorld_s0108_2350*, hkEntity_s0108_2350*);                    // 0x10a03c0 (FUN_)
    static void addPhantomBP(hkWorld_s0108_2350*, hkPhantom_s0108_2350*);                     // 0x10a0d10
};
struct hkWorldCallbackUtil {
    static void fireEntityAdded(hkWorld_s0108_2350*, hkEntity_s0108_2350*);                   // 0x109ebc0
    static void fireEntityRemoved(hkWorld_s0108_2350*, hkEntity_s0108_2350*);                 // 0x109ec50
    static void firePhantomAdded(hkWorld_s0108_2350*, hkPhantom_s0108_2350*);                 // 0x109ed70
};
struct hkEntityCallbackUtil {
    static void fireEntityAdded(hkEntity_s0108_2350*);                             // 0x109e730
    static void fireEntityRemoved(hkEntity_s0108_2350*);                           // 0x109ea00
};
struct hkWorldOperationQueue {
    void queueOperation(const hkWorldOperationBase& op);                // 0x109afe0
    void queuePhantomOperation(const hkWorldOperationPrefix& op);       // 0x109afe0
    void executeAllPending();                                           // 0x109b490
};
void hkSimulation_removeEntity(hkSimulation* sim, hkEntity_s0108_2350* e);         // 0x10a08b0
void hkWorldObject_removeReference(hkWorldObject_s0108_2350* o);                   // 0x109ae60
struct hkWorldRayCaster {
    const void* vtbl_;
    uint32_t pad[15];
    void* m_a;                                          // +0x40 zeroed by the constructor
    void* m_b;                                          // +0x44 zeroed by the constructor
    hkWorldRayCaster() { m_a = 0; m_b = 0; }
    void castRay(hkBroadPhase& bp, const hkWorldRayCastInput& input, const hkCollisionFilter_s0108_2350* filter,
                 char* unused, hkRayHitCollector& collector);
    virtual void addBroadPhaseHandle() {}
};
struct hkNullContactMgr {
virtual void s0();
virtual void s1();
    virtual uint16_t addContactPoint(int a, int b, int c, int d);       // 0x010829e0
    virtual uint32_t processRequest(int a, int b, int c, int d, int e, int f, int g);  // 0x01082a00
};
class hkWorldLinearCaster { public:
    const void* vtbl_;
    uint32_t pad[15];
    float m_shapeInputTolerance;                        // +0x40 = 2^-23 (0x34000000)
    uint32_t pad2[3];
    virtual void addBroadPhaseHandle() {}
    void linearCast(const hkBroadPhase& bp, const hkCollidable* collA, const hkLinearCastInput_s0108_2350& input,
                    const void* filter, const hkProcessCollisionInput_s0108_2350* collisionInput, void* config,
                    hkCdPointCollector& castCollector, hkCdPointCollector* startCollector);
};
struct hkProcessCollisionInput_s0108_2350 { char pad[0x20]; void* m_config; };
class hkSimulationIsland_s0108_2350 { public:
    uint32_t pad[3];
    int m_c;      // +0x0c
    int m_d;      // +0x10
    int m_a;      // +0x14
    int m_b;      // +0x18
};
struct hkContactMgrFactory : hkReferencedObject_s0108_2350 { };
struct hkNullContactMgrFactory : hkContactMgrFactory {
    hkNullContactMgr* m_nullContactMgr_slot;                // embedded mgr (vptr) lives at +8
    uint16_t m_pad0c, m_type;
    HK_CLASS_ALLOC(4)
    virtual hkNullContactMgr* createContactMgr(int a, int b, int c);   // 0x01082ce0 returns this+8
    virtual ~hkNullContactMgrFactory() {}
    void* deletingDtor(unsigned flags);                     // 0x01082cf0 (scalar deleting destructor body)
};
class hkCollidableCollidableFilter_s0108_2350
{ public:
    virtual void s0();
    virtual hkBool_s0108_2350 isCollisionEnabled(const class hkLinkedCollidable_s0108_2350& a, const class hkLinkedCollidable_s0108_2350& b) const = 0;   // slot 1
};
class hkShapeCollectionFilter_s0108_2350 {
    public: virtual void s0();
    virtual hkBool_s0108_2350 isCollisionEnabled(const void* a, const void* b, const void* bContainer, uint32_t bKey) const = 0;
};
class hkRayShapeCollectionFilter_s0108_2350 {
    public: virtual void s0();
    virtual hkBool_s0108_2350 isCollisionEnabled(const void* input, const void* collection, uint32_t key) const = 0;
};
class hkRayCollidableFilter_s0108_2350 {
    public: virtual void s0();
    virtual hkBool_s0108_2350 isCollisionEnabled(const void* input, const hkLinkedCollidable_s0108_2350& c) const = 0;
};
class hkCollisionFilter_s0108_2350 : public hkReferencedObject_s0108_2350, public hkCollidableCollidableFilter_s0108_2350, public hkShapeCollectionFilter_s0108_2350, public hkRayShapeCollectionFilter_s0108_2350, public hkRayCollidableFilter_s0108_2350 { public:
    hkCollisionFilter_s0108_2350() {}
};
struct hkNullCollisionFilter : hkCollisionFilter_s0108_2350
{
    hkNullCollisionFilter();                                                                    // 0x01082D20
    virtual hkBool_s0108_2350 isCollisionEnabled(const hkLinkedCollidable_s0108_2350& a, const hkLinkedCollidable_s0108_2350& b) const;
};
class hkCollisionDispatcher_s0108_2350 { public: void registerContactMgrFactory(hkContactMgrFactory* f, int responseType); };   // 0x10ccbd0
hkContactMgrFactory* hkSimpleConstraintContactMgr_Factory_create(hkWorld_s0108_2350* w);       // 0x108d850 ctor
hkContactMgrFactory* hkReactiveContactMgr_Factory_create(hkWorld_s0108_2350* w);               // 0x109e6a0 ctor
// ---- items of slice s01082350 end

// ---- items of slice s01083400 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) void __stdcall DeleteCriticalSection(void* pCriticalSection);   // kernel32
typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned int   uint;
struct hkWorld_s0108_3400;
struct hkPendingOp {
    uchar mOpcode;                                            // +0x00
    uchar mPad01[3];                                          // +0x01
    void* mpPayload;                                          // +0x04
};
struct hkOpQueue {
    void* mpOps;                                              // +0x00
    int   mOpCount;                                           // +0x04
    uint  mOpCapacityAndFlags;                                // +0x08
    char  mPad0c[0x20 - 0x0c];                                // +0x0c
    void* mpChunk;                                            // +0x20
    void push(hkPendingOp* pOp);                              // 0x0109afe0
};
struct hkReferencedObject_s0108_3400 {
    virtual void vfDestroy(int bDeallocate);                  // +0x00  (delete this)
    ushort mMemSizeAndFlags;                                  // +0x04
    short  mReferenceCount;                                   // +0x06
    void removeReference()
    {
        if (mMemSizeAndFlags != 0 && --mReferenceCount == 0) {
            vfDestroy(1);
        }
    }
};
struct hkPhantom_s0108_3400 {
    virtual void vf0();
    virtual void vf1();
    virtual void vf2();
    virtual void vf3();
    virtual void vf4();
    virtual void vf5();
    virtual void vf6();
    virtual void vf7();
    virtual void vf8();
    virtual void vf9();
    virtual void vf10();
    virtual void vf11();                                      // +0x2c
    ushort mFlags;                                            // +0x04
    char  mPad06[2];                                          // +0x06
    int   m08;                                                // +0x08
    void  firePhantomRemoved();                               // 0x0108e300
    void  removeReference();                                  // 0x0109ae60
};
struct hkSimulationIsland_s0108_3400 : hkReferencedObject_s0108_3400 {
    char  mPad08[0x3c - 0x08];                                // +0x08
    void* mpEntities;                                         // +0x3c
    int   mEntityCount;                                       // +0x40
};
struct hkCollisionInput_s0108_3400 {
    char  mPad00[0x20];                                       // +0x00
    void* mpOwnedChunk;                                       // +0x20
};
struct hkEntity_s0108_3400 {
    char  mPad00[0x10];                                       // +0x00
    int   mActivateOffset;                                    // +0x10  offset of the activatable part
    char  mPad14[0x18 - 0x14];                                // +0x14
    char  mState;                                             // +0x18  1 == can be activated
    char  mPad1c[0x3c - 0x1c];                                // +0x1c
    void* mpEntities;                                         // +0x3c  (hkArray data of the owning island)
    int   mEntityCount;                                       // +0x40
    void  activate();                                         // 0x0108ae0
    void  removeReference();                                  // 0x0109ae60
};
struct hkAabb_s0108_3400 {
    float mMinX, mMinY, mMinZ, mPad0c;                        // +0x00
    float mMaxX, mMaxY, mMaxZ, mPad1c;                        // +0x10
};
void hkArrayUtil_reserveMore(void* pArray, int elementSize);  // 0x0107f530
template <class T>
struct hkArray_s0108_3400 {
    T*    mpData;                                             // +0x00
    int   mSize;                                              // +0x04
    uint  mCapacityAndFlags;                                  // +0x08
    void pushBack(T value)
    {
        if (mSize == (int)(mCapacityAndFlags & 0x3fffffff)) {
            hkArrayUtil_reserveMore(this, sizeof(T));
        }
        mpData[mSize] = value;
        ++mSize;
    }
    int indexOf(T value) const
    {
        for (int i = 0; i < mSize; ++i) {
            if (mpData[i] == value)
                return i;
        }
        return -1;
    }
    bool isDeallocatable() const
    {
        return !(mCapacityAndFlags & 0x80000000);
    }
    static bool isDeallocatable(uint capacityAndFlags)
    {
        return !(capacityAndFlags & 0x80000000);
    }
};
struct hkMemory_s0108_3400 {
    virtual void vf0();
    virtual void vf1();
    virtual void vf2();
    virtual void vf3();
    virtual void* allocate(int size, int align);              // +0x10
    virtual void  deallocate(void* p, int size, int align);   // +0x14
    virtual void  vf5();
    virtual void  deallocateBlock(void* p, int size, int align);   // +0x1c
};
extern hkMemory_s0108_3400* g_hkMemory_s0108_3400;                                  // 0x016e4178
void hkString_memCpy(void* dst, const void* src, int len);    // 0x0107f440
struct hkBroadPhaseQuery {
    virtual void vf0();
    virtual void vf1();
    virtual void vf2();
    virtual void vf3();
    virtual void vf4();
    virtual void vf5();
    virtual void vf6();
    virtual void vf7();
    virtual void vf8();
    virtual void vf9();
    virtual void vf10();
    virtual void query(const hkAabb_s0108_3400* pAabb, void* pArray);    // +0x2c
};
struct hkThreadMemory_s0108_3400 {
    char  mPad00[0x34];                                       // +0x00
    int   mMaxChunks;                                         // +0x34
    char  mPad38[0x4c - 0x38];                                // +0x38
    void* mpFreeList;                                         // +0x4c
    char  mPad50[0x90 - 0x50];                                // +0x50
    int   mNumChunks;                                         // +0x90
    void deallocateChunk(void* p, int bytes, int align);      // 0x0107db10
};
extern uint  g_hkThreadMemoryTls;                             // 0x016e4174
struct hkBroadPhaseEntry {
    void* mpOwner;                                            // +0x00
    uchar* mpRecord;                                          // +0x04
};
struct hkBpRecord {
    char  mPad00[0x05];                                       // +0x00
    signed char mEntityOffset;                                // +0x05
};
struct hkStatisticsCollector_s0108_3400 {
    virtual void vf0();
    virtual void beginObject(const char* pType, int indent, const void* pObject);        // +0x04
    virtual void addArray(const char* pName, int elemSize, const void* pData,
                          int usedBytes, int reservedBytes);                             // +0x08
    virtual void addValue(const char* pName, int size, const void* pValue);              // +0x0c
    virtual void beginSection(const char* pName);                                        // +0x10
    virtual void endSection();                                                           // +0x14
    virtual void endObject();                                                            // +0x18
};
struct hkWorld_s0108_3400 : hkReferencedObject_s0108_3400 {
    hkReferencedObject_s0108_3400* mpSimulation;                         // +0x08  "Simulation"
    char  mPad0c[0x30 - 0x0c];                                // +0x0c
    hkSimulationIsland_s0108_3400* mpFixedIsland;                        // +0x30  "Fixed"
    hkEntity_s0108_3400* mpFixedRigidBody;                               // +0x34
    hkArray_s0108_3400<hkSimulationIsland_s0108_3400*> mActive;                     // +0x38  "Active"
    hkArray_s0108_3400<hkSimulationIsland_s0108_3400*> mInactive;                   // +0x44  "Inactive"
    hkArray_s0108_3400<void*> mDirtyIslands;                             // +0x50  "DirtyIslPtr"
    hkReferencedObject_s0108_3400* mpMaintenanceMgr;                     // +0x5c  "MaintnceMgr"
    hkReferencedObject_s0108_3400* mpBroadPhaseDispatchBase;             // +0x60
    hkBroadPhaseQuery* mpBroadPhase;                          // +0x64  "Broadphase"
    void* mpBpDispatch68;                                     // +0x68  0x104 bytes
    void* mpBpDispatch6c;                                     // +0x6c
    void* mpBpDispatch70;                                     // +0x70
    void* mpBpDispatch74;                                     // +0x74
    hkCollisionInput_s0108_3400* mpCollisionInput;                       // +0x78  "CollInput", 0x2c bytes
    hkReferencedObject_s0108_3400* mpCollisionFilter;                    // +0x7c  "Filter"
    hkReferencedObject_s0108_3400* mpDispatcher;                         // +0x80  "Dispatcher"
    hkOpQueue* mpOpQueue;                                     // +0x84  "OpQueue", 0x40 bytes
    int   m88;                                                // +0x88
    int   m8c;                                                // +0x8c  world-lock counter
    int   m90;                                                // +0x90
    bool  m94;                                                // +0x94
    char  mPad95[0xac - 0x95];                                // +0x95
    void* mpCriticalSectionA;                                 // +0xac
    void* mpCriticalSectionB;                                 // +0xb0
    bool  mB4;                                                // +0xb4
    char  mPadB5[0xcc - 0xb5];                                // +0xb5
    hkArray_s0108_3400<hkPhantom_s0108_3400*> mPhantoms;                            // +0xcc  "PhantomPtrs"
    char  mPadD8[0xe4 - 0xd8];                                // +0xd8
    hkArray_s0108_3400<void*> mEntityListeners;                          // +0xe4  "EntLisPtr"
    hkArray_s0108_3400<void*> mPhantomListeners;                         // +0xf0  "PhantLisPtr"
    hkArray_s0108_3400<void*> mConstraintListeners;                      // +0xfc  "ConstrLisPtr"
    hkArray_s0108_3400<void*> mWorldDeletionListeners;                   // +0x108 "WldDelLisPtr"
    hkArray_s0108_3400<void*> mIslandActivationListeners;                // +0x114 "IslActLisPtr"
    hkArray_s0108_3400<void*> mPostSimulationListeners;                  // +0x120 "PstSimLisPtr"
    hkArray_s0108_3400<void*> mPostIntegrateListeners;                   // +0x12c "PstIntLisPtr"
    hkArray_s0108_3400<void*> mPostCollideListeners;                     // +0x138 "PstColLisPtr"
    hkArray_s0108_3400<void*> mListeners144;                             // +0x144
    hkArray_s0108_3400<void*> mListeners150;                             // +0x150
    hkArray_s0108_3400<void*> mCollisionListeners;                       // +0x15c "CollLisPtr"
    hkReferencedObject_s0108_3400* mp168;                                // +0x168

    void removePhantom(hkPhantom_s0108_3400* pPhantom);                  // 0x01083400
    void addCollisionListener(void* p);                       // 0x010834f0
    void addWorldDeletionListener(void* p);                   // 0x01083530
    virtual void calcStatistics(hkStatisticsCollector_s0108_3400* pCollector) const;   // 0x01083570
    virtual ~hkWorld_s0108_3400();                                       // 0x010839e0
    void activateRegion(const hkAabb_s0108_3400& aabb);                  // 0x01083ff0
    void executePendingOperations();                          // 0x01082bf0
    void removeEntity(hkEntity_s0108_3400* pEntity);                     // 0x01083110
};
void hkWorldCallbackUtil_firePhantomRemoved(hkWorld_s0108_3400* pWorld, hkPhantom_s0108_3400* pPhantom);   // 0x0109ee00
void hkWorldOperationUtil_removePhantomBP(hkWorld_s0108_3400* pWorld, hkPhantom_s0108_3400* pPhantom);     // 0x010a0f20
void hkWorldOperationUtil_removeIslandFromDirtyList(hkWorld_s0108_3400* pWorld,
                                                    hkSimulationIsland_s0108_3400* pIsland);    // 0x0109fb40
void hkWorldFUN_0109f280(hkWorld_s0108_3400* pWorld);                                           // 0x0109f280
void hkWorldFUN_0109b420();                                                          // 0x0109b420
void hkWorldFUN_010cc3f0();                                                          // 0x010cc3f0
static __forceinline void releaseArray(void* pData, int sizeInBytes, uint capacityAndFlags)
{
    if ((capacityAndFlags & 0x80000000) == 0) {
        hkThreadMemory_s0108_3400* pThreadMemory = (hkThreadMemory_s0108_3400*)TlsGetValue(g_hkThreadMemoryTls);
        pThreadMemory->deallocateChunk(pData, sizeInBytes, 0x14);
    }
}
static __forceinline void releaseOpQueue(hkOpQueue* pQueue)
{
    if (pQueue == 0)
        return;
    hkWorldFUN_0109b420();
    hkThreadMemory_s0108_3400* pThreadMemory = (hkThreadMemory_s0108_3400*)TlsGetValue(g_hkThreadMemoryTls);
    if (pThreadMemory->mNumChunks < pThreadMemory->mMaxChunks) {
        ++pThreadMemory->mNumChunks;
        pQueue->mpOps = pThreadMemory->mpFreeList;            // freed block links as the next entry
        pThreadMemory->mpFreeList = pQueue;
    } else {
        g_hkMemory_s0108_3400->deallocateBlock(pQueue, 5, 0x2c);
    }
}
// ---- items of slice s01083400 end

// ---- items of slice s01084cf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern unsigned int g_hkMonitorStreamEndTls;      // 0x016e42a8
extern unsigned int g_hkMonitorStreamCurrentTls;  // 0x016e42a4
extern unsigned int g_hkThreadMemoryTls;          // 0x016e4174
typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef signed char    s8;
typedef unsigned long  u32d;    // DWORD (TLS index)
unsigned long long __cdecl rdtsc(void);
static inline void hkTimerBegin(const char* name, const char* section) {
    void* end = TlsGetValue(g_hkMonitorStreamEndTls);
    void* cur = TlsGetValue(g_hkMonitorStreamCurrentTls);
    if (cur < end) {
        u32* p = (u32*)TlsGetValue(g_hkMonitorStreamCurrentTls);
        p[0] = (u32)name;
        p[3] = (u32)section;
        p[1] = (u32)rdtsc();
        TlsSetValue(g_hkMonitorStreamCurrentTls, p + 4);
    }
}
static inline void hkTimerEnd(const char* name) {
    void* end = TlsGetValue(g_hkMonitorStreamEndTls);
    void* cur = TlsGetValue(g_hkMonitorStreamCurrentTls);
    if (cur < end) {
        u32* p = (u32*)TlsGetValue(g_hkMonitorStreamCurrentTls);
        p[0] = (u32)name;
        p[1] = (u32)rdtsc();
        TlsSetValue(g_hkMonitorStreamCurrentTls, p + 3);
    }
}
class hkThreadMemory_s0108_4cf0 {
public:
    virtual ~hkThreadMemory_s0108_4cf0();              // +0x00
    virtual void _v1();                     // +0x04
    virtual void _v2();                     // +0x08
    virtual void* allocateChunk(u32 size);  // +0x0c 0x0107daa0
    virtual void  freeStackAlloc(void* p);  // +0x10

    void deallocateChunk(void* p, u32 size, int align);   // 0x0107db10

    u8*   m_stackCurrent;   // 0x20
    u8*   m_stackMark;      // 0x24
    u8*   m_stackBase;      // 0x28
    u8*   m_stackLimit;     // 0x2c
};
static hkThreadMemory_s0108_4cf0* hkThreadMemoryInstance() {
    return (hkThreadMemory_s0108_4cf0*)TlsGetValue(g_hkThreadMemoryTls);
}
static void* hkStackAlloc(u32 bytes) {
    hkThreadMemory_s0108_4cf0* mem = hkThreadMemoryInstance();
    u32 need = (bytes + 0x10) & 0xfffffff0u;
    u8* cur = mem->m_stackCurrent;
    u8* end = cur + need;
    if ((u32)mem->m_stackLimit < (u32)end)
        return mem->allocateChunk(need);
    mem->m_stackCurrent = end;
    return cur;
}
static void hkStackRelease(void* p) {
    hkThreadMemory_s0108_4cf0* mem = hkThreadMemoryInstance();
    mem->m_stackCurrent = (u8*)p;
    if (p == mem->m_stackMark)
        mem->freeStackAlloc(p);
}
static void hkArrayFree(void* data, int caps, int elemSize) {
    if ((caps & 0x80000000) == 0)
        hkThreadMemoryInstance()->deallocateChunk(
            data, (u32)(caps & 0x3fffffff) * (u32)elemSize, 0x14);
}
class hkWorld_s0108_4cf0; class hkEntity_s0108_4cf0; class hkPhantom_s0108_4cf0; class hkSimulationIsland_s0108_4cf0;
class hkProcessCollisionInput_s0108_4cf0; class hkBroadPhase; class hkCollisionFilter_s0108_4cf0;
class hkWorldOperationQueue_s0108_4cf0 {
public:
    void queueOperation(void* op);                   // 0x0109afe0
};
void hkArrayUtil_reserveExact(void* arr, int newCap, int elemSize);   // 0x0107f4a0
void hkArrayUtil_reserveGrow(void* arr, int elemSize);                // 0x0107f530
void worldUpdatePhantomOverlap(hkCollisionFilter_s0108_4cf0* filter, void* agent);  // 0x01082910
void FUN_010cc410(int a, int b, int c);              // 0x010cc410
void FUN_010cc560(void* a, void* b);                 // 0x010cc560
void FUN_01082590(void);                             // 0x01082590
void FUN_01209b70(int a, int b, void* c);            // 0x01209b70
void FUN_010a2250(void* entity);                     // 0x010a2250
void FUN_010a39f0(void* entity);                     // 0x010a39f0
void FUN_010fb9c0(void* entity, void* input);        // 0x010fb9c0
void FUN_0109ebc0(void* world, void* entity);        // 0x0109ebc0
void FUN_0109e730(void* entity);                     // 0x0109e730
void* hkMemoryAllocate(u32 size, int align);         // hkMemory::allocate
class hkBroadPhaseHandle_s0108_4cf0 {
public:
    u32 m_id;              // 0x00
    u16 m_handleType;      // 0x04
    s8  m_ownerOffset;     // 0x05
    u8  m_pad06[2];        // 0x06
    u32 m_pad08;           // 0x08
    u32 m_pad0c;           // 0x0c
    void* owner() const { return (char*)this + m_ownerOffset; }
};
struct hkBroadPhaseHandlePair { hkBroadPhaseHandle_s0108_4cf0* m_a; hkBroadPhaseHandle_s0108_4cf0* m_b; };
struct hkCollidable_s0108_4cf0 {
    void*              m_shape;        // 0x00
    u32                m_shapeKey;     // 0x04
    void*              m_motion;       // 0x08
    void*              m_parent;       // 0x0c
    void*              m_owner;        // 0x10
    hkBroadPhaseHandle_s0108_4cf0 m_handle;       // 0x14
};
class hkReferencedObject_s0108_4cf0 {
public:
    virtual ~hkReferencedObject_s0108_4cf0();          // slot 0
    virtual void calcStatistics(void*);     // slot 1
    u16 m_memSizeAndFlags;                  // 0x04
    u16 m_referenceCount;                   // 0x06
};
class hkWorldObject_s0108_4cf0 : public hkReferencedObject_s0108_4cf0 {
public:
    virtual ~hkWorldObject_s0108_4cf0();                        // slot 0 (override)
    virtual void* setShape(void*);                   // slot 2
    virtual void* getMotionState();                  // slot 3
    void*        m_world;                            // 0x08
    void*        m_userData;                         // 0x0c
    char*        m_name;                             // 0x10
    u32          m_lockThreadId;                     // 0x14
    int          m_lockCount;                        // 0x18
    hkCollidable_s0108_4cf0 m_collidable;                       // 0x1c
};
struct hkCollisionEntry {
    void* m_objectA;       // 0x00
    void* m_objectB;       // 0x04
};
struct hkCollisionEntryTarget {
    u8  m_pad00[0x14];
    int m_handleA;         // 0x14
    int m_handleB;         // 0x18
};
class hkEntity_s0108_4cf0 : public hkWorldObject_s0108_4cf0 {
public:
    virtual ~hkEntity_s0108_4cf0();                             // slot 0 (override)
    virtual void deallocateInternalArrays();         // slot 4
    void** m_collisionEntriesData;                   // 0x40
    int    m_collisionEntriesSize;                   // 0x44
    int    m_collisionEntriesCaps;                   // 0x48
    u8     m_pad4c[0x58 - 0x4c];
    void*  m_motion;                                 // 0x58
    void*  m_simulationIsland;                       // 0x5c
    u8     m_pad60[0x99 - 0x60];
    u8     m_fixed;                                  // 0x99
    u8     m_pad9a[0xcc - 0x9a];
    u32    m_uid;                                    // 0xcc
};
class hkPhantom_s0108_4cf0 : public hkWorldObject_s0108_4cf0 {
public:
    virtual ~hkPhantom_s0108_4cf0();                            // slot 0 (override)
    virtual int  getType();                          // slot 4
    virtual void calcAabb(void*);                    // slot 5
    virtual void addOverlappingCollidable(void*);    // slot 6
    virtual int  isOverlappingCollidableAdded(void*);// slot 7
    virtual void removeOverlappingCollidable(void*); // slot 8
    virtual void* clone();                           // slot 9
    virtual void updateShapeCollectionFilter();      // slot 10
    virtual void deallocateInternalArrays();         // slot 11
};
class hkSimulationIsland_s0108_4cf0 {
public:
    u8                 m_pad00[0x3c];
    hkEntity_s0108_4cf0**         m_entities;                   // 0x3c
    int                m_entitiesSize;               // 0x40
    int                m_entitiesCaps;               // 0x44
};
class hkBroadPhase {
public:
    virtual ~hkBroadPhase();                                     // 0
    virtual void _v1();                                          // 1 (+0x04)
    virtual void _v2();                                          // 2 (+0x08)
    virtual void addEntityBatch(void*, void*, void*);            // 3 (+0x0c)
virtual void _v4();
virtual void _v5();
virtual void _v6();
virtual void _v7();
virtual void _v8();
virtual void _v9();
virtual void _v10();
virtual void _v11();
    virtual void queryAabb(void*, void*);                        // 12 (+0x30)
};
class hkCollidableCollidableFilter_s0108_4cf0 {
public:
    virtual ~hkCollidableCollidableFilter_s0108_4cf0();
    virtual char* isCollisionEnabled(void*, void*, void*);       // slot 1 (+0x04)
};
class hkCollisionFilter_s0108_4cf0 {
public:
    u32                        _pad00;
    u32                        _pad04;
    hkCollidableCollidableFilter_s0108_4cf0* m_collidableCollidableFilter;  // 0x08
};
struct hkProcessCollisionInput_s0108_4cf0 {
    u32   _pad00;
    u32   _pad04;
    float m_tolerance;                     // 0x08
};
enum hkUpdateCollectionFilterMode {
    HK_UPDATE_FILTER_ON_PHANTOM_UPDATE_OVERLAPS         = 0,
    HK_UPDATE_FILTER_ON_PHANTOM_UPDATE_SHAPE_COLLECTION = 1,
};
enum hkEntityActivation_s0108_4cf0 {
    HK_ENTITY_ACTIVATION_DO_ACTIVATE_s0108_4cf0            = 0,
    HK_ENTITY_ACTIVATION_DO_NOT_ACTIVATE_s0108_4cf0        = 1,
    HK_ENTITY_ACTIVATION_DO_NOT_ACTIVATE_OR_ADD = 2,
};
template <class T> struct hkArray_s0108_4cf0 {
    T*  m_data;              // +0x00
    int m_size;              // +0x04
    int m_capacityAndFlags;  // +0x08
};
class hkWorld_s0108_4cf0 {
public:
    void updateCollisionFilterOnPhantom(hkPhantom_s0108_4cf0* phantom, hkUpdateCollectionFilterMode mode);
    void addEntityBatch(hkEntity_s0108_4cf0 const* const* entities, int count, hkEntityActivation_s0108_4cf0 activation);
    void executePendingOperations();                 // 0x01082bf0
    hkSimulationIsland_s0108_4cf0* getSimulationIsland();       // 0x010a2810

    void* m_vtable;                                  // 0x00
    u32   m_memSizeAndFlags;                         // 0x04
    u16   m_referenceCount;                          // 0x08
    u16   m_pad0a;                                   // 0x0a
    u8    m_pad0c[0x38 - 0x0c];                      // 0x0c
    hkArray_s0108_4cf0<hkSimulationIsland_s0108_4cf0*> m_activeSimulationIslands;    // 0x38
    hkArray_s0108_4cf0<hkSimulationIsland_s0108_4cf0*> m_inactiveSimulationIslands;  // 0x44
    u8    m_pad50[0x64 - 0x50];                      // 0x50
    hkBroadPhase* m_broadPhase;                      // 0x64
    u8    m_pad68[0x78 - 0x68];                      // 0x68
    hkProcessCollisionInput_s0108_4cf0* m_collisionInput;       // 0x78
    hkCollisionFilter_s0108_4cf0* m_collisionFilter;            // 0x7c
    void* m_collisionDispatcher;                     // 0x80
    hkWorldOperationQueue_s0108_4cf0* m_pendingOperations;      // 0x84
    int   m_pendingOperationsCount;                  // 0x88
    int   m_lockCount;                               // 0x8c
    int   m_lockCountForPhantoms;                    // 0x90
    u8    m_blockExecutingPendingOperations;         // 0x94
    u8    m_pad95[0xb4 - 0x95];                      // 0x95
    u8    m_wantSimulationIslands;                   // 0xb4
    u8    m_pad_b5[0xc8 - 0xb5];                     // 0xb5
    u32   m_lastEntityUid;                           // 0xc8
    u8    m_pad_cc[0x2e4 - 0xcc];                    // 0xcc
    int   m_broadPhaseQuerySize;                     // 0x2e4
};
// ---- items of slice s01084cf0 end

// ---- items of slice s01088960 begin (TODO(rewrite): local stubs, replace by canonical classes)
template <typename T>
class hkArray_s0108_8960 { public:
    T* m_data; int m_size; int m_capacityAndFlags;
    void pushBack(const T& t) {
        if (m_size == (m_capacityAndFlags & HK_ARRAY_FLAG_MASK)) hkArrayUtil::_reserveMore(this, (int)sizeof(T));
        m_data[m_size] = t;
        m_size = m_size + 1;
    }
    int indexOf(const T& t) const {
        int i = 0;
        while (i < m_size) { if (m_data[i] == t) return i; ++i; }
        return -1;
    }
    // frees the buffer if owned (flag bit clear)
    void freeBuffer(int elemSize) {
        if (m_capacityAndFlags >= 0)
            getThreadMemory()->deallocateChunk(m_data, (m_capacityAndFlags & HK_ARRAY_FLAG_MASK) * elemSize, 0x14);
    }
    // hkArray::clearAndDeallocate (size must be 0)
    void clearAndDeallocate(int elemSize) {
        freeBuffer(elemSize);
        m_data = 0;
        m_size = 0;
        m_capacityAndFlags = (int)(((unsigned)m_capacityAndFlags & 0xc0000000u) | 0x80000000u);
    }
};
class hkVector4_s0108_8960 { public: float x, y, z, w; };
class hkReferencedObject_s0108_8960 { public:
    uint16_t m_memSizeAndFlags;
    uint16_t m_referenceCount;
    hkReferencedObject_s0108_8960() : m_referenceCount(1) {}
    virtual ~hkReferencedObject_s0108_8960() {}
    virtual void calcStatistics(class hkStatisticsCollector_s0108_8960* c) const {}
    void addReference() { if (m_memSizeAndFlags != 0) m_referenceCount = (uint16_t)(m_referenceCount + 1); }
    void removeReference() {
        if (m_memSizeAndFlags != 0) {
            m_referenceCount = (uint16_t)(m_referenceCount - 1);
            if (m_referenceCount == 0) delete this;
        }
    }
};
class hkStatisticsCollector_s0108_8960 { public:
    virtual void s0();
    virtual void beginObject(const char* name, int mode, const void* obj);                                     // +4
    virtual void addArray(const char* name, int elemSize, const void* ptr, int usedBytes, int allocBytes);    // +8
    virtual void addReferencedObject(const char* name, int mode, const void* obj);                             // +0xc
virtual void s4();
virtual void s5();
    virtual void endObject();                                                                                  // +0x18
};
class __declspec(align(16)) hkMotionState { public:
    char m_data[0xb0];
    hkMotionState& operator=(const hkMotionState& other);   // 0x010888C0
};
class hkMotion_s0108_8960 : public hkReferencedObject_s0108_8960 { public: int m_solverData; };
class hkRigidMotion : public hkMotion_s0108_8960 { public:
    hkMotionState m_motionState;          // +0x10
    float m_massInv;                      // +0xc0
    float m_particleMinInertiaDiagInv;    // +0xc4
    float m_linearDamping;                // +0xc8
    float m_angularDamping;               // +0xcc
    uint32_t m_linearVelocity[4];         // +0xd0 (copied as raw bits)
    uint32_t m_angularVelocity[4];        // +0xe0
    virtual void getMotionStateAndVelocities(hkMotion_s0108_8960* motionOut);
};
struct hkShape_s0108_8960;
class hkMultiThreadLock_s0108_8960 { public: uint32_t m_threadId; int m_lockCount; };
class hkLinkedCollidable_s0108_8960 { public:
    hkShape_s0108_8960* m_shape; uint32_t m_shapeKey; void* m_motion; void* m_parent; int m_ownerOffset;
    uint32_t m_handle[3]; float m_allowedPenetrationDepth;
    hkArray_s0108_8960<void*[2]> m_collisionEntries;       // +0x24 (8-byte entries)
};
class hkProperty_s0108_8960 { public: uint32_t m_key, m_pad, m_lo, m_hi; };
class hkWorldObject_s0108_8960 : public hkReferencedObject_s0108_8960 { public:
    void* m_world;                      // +0x08
    void* m_userData;                   // +0x0c
    const char* m_name;                 // +0x10
    hkMultiThreadLock_s0108_8960 m_multithreadLock;// +0x14
    hkLinkedCollidable_s0108_8960 m_collidable;    // +0x1c
    hkArray_s0108_8960<hkProperty_s0108_8960> m_properties;   // +0x4c
    hkWorldObject_s0108_8960(const hkShape_s0108_8960* shape, int broadPhaseType);      // 0x01082800
    virtual ~hkWorldObject_s0108_8960();                                     // 0x01082770
    virtual void calcStatistics(hkStatisticsCollector_s0108_8960* c) const;  // 0x01082660
    virtual void slot2() {}
    virtual void* getMotionState() = 0;
    virtual void slot4() = 0;
};
class hkSimulationIsland_s0108_8960 { public: char pad[0x28]; uint8_t m_active; };
class hkEntityDeactivator_s0108_8960 : public hkReferencedObject_s0108_8960 { public:};
class hkMaterial_s0108_8960 { public: uint8_t m_responseType; float m_friction; float m_restitution; };
struct hkEntityListener; struct hkCollisionListener; struct hkEntityActivationListener; struct hkAction_s0108_8960;
struct hkConstraintInternal_s0108_8960 { char pad[0x1c]; };
struct hkConstraintInstance_s0108_8960;
struct hkWorld_s0108_8960;
class hkBool_s0108_8960 { public: uint8_t b; };
struct hkMotionBase;
struct hkFinishLoadedObjectFlag {
    int m_finishing;
    hkFinishLoadedObjectFlag(int f) : m_finishing(f) {}
};
struct hkWorldOperationUtil_s0108_8960 {
    static void markIslandActive(hkWorld_s0108_8960* w, hkSimulationIsland_s0108_8960* i);     // 0x010a0130
    static void markIslandInactive(hkWorld_s0108_8960* w, hkSimulationIsland_s0108_8960* i);   // 0x010a00e0
};
struct hkEntityCallbackUtil_s0108_8960 { static void fireEntityDeleted(class hkEntity_s0108_8960* e); };    // 0x0109e790
class hkEntity_s0108_8960 : public hkWorldObject_s0108_8960 { public:
    hkMotionBase* m_motion;                              // +0x58
    hkSimulationIsland_s0108_8960* m_simulationIsland;              // +0x5c
    hkMaterial_s0108_8960 m_material;                               // +0x60
    hkEntityDeactivator_s0108_8960* m_deactivator;                  // +0x6c
    hkArray_s0108_8960<hkConstraintInternal_s0108_8960> m_constraintsMaster;   // +0x70 (0x1c-byte entries)
    hkArray_s0108_8960<hkConstraintInstance_s0108_8960*> m_constraintsSlave;   // +0x7c
    hkArray_s0108_8960<uint8_t> m_constraintRuntime;                // +0x88
    uint16_t m_storageIndex;                             // +0x94
    uint16_t m_processContactCallbackDelay;              // +0x96
    char m_autoRemoveLevel;                              // +0x98
    uint8_t m_fixed;                                     // +0x99
    uint8_t m_isFixedOrKeyframed;                        // +0x9a
    uint8_t m_internalCollideFlag;                       // +0x9b
    hkArray_s0108_8960<hkCollisionListener*> m_collisionListeners;  // +0x9c
    hkArray_s0108_8960<hkEntityActivationListener*> m_activationListeners;  // +0xa8
    hkArray_s0108_8960<hkEntityListener*> m_entityListeners;        // +0xb4
    hkArray_s0108_8960<hkAction_s0108_8960*> m_actions;                        // +0xc0
    uint32_t m_uid;                                      // +0xcc

    explicit hkEntity_s0108_8960(const hkShape_s0108_8960* shape);
    hkEntity_s0108_8960(hkFinishLoadedObjectFlag flag);              // 0x01087D50
    ~hkEntity_s0108_8960();
    virtual void* getMotionState() { return 0; }
    virtual void slot4() {}
    virtual void calcStatistics(hkStatisticsCollector_s0108_8960* c) const;
    virtual void deallocateInternalArrays();
    void setDeactivator(hkEntityDeactivator_s0108_8960* d);
    void removeEntityListener(hkEntityListener* l);
    void removeCollisionListener(hkCollisionListener* l);
    hkBool_s0108_8960 isActive() const;
    void activate();
    void deactivate();
    void addEntityListener(hkEntityListener* l);
    void addCollisionListener(hkCollisionListener* l);
};
struct hkConstraintInfo { int m_maxSizeOfJacobians, m_sizeOfJacobians, m_sizeOfSchemas, m_numSolverResults; };
class hkGenericConstraintDataScheme { public:
    hkConstraintInfo m_info;                 // +0x00
    hkArray_s0108_8960<hkVector4_s0108_8960> m_data;               // +0x10
    hkArray_s0108_8960<int> m_commands;                 // +0x1c
    void* m_modifiers[3];                    // +0x28
    void* m_motors[3];                       // +0x34
};
class hkConstraintData_s0108_8960 : public hkReferencedObject_s0108_8960 { public: uint32_t m_userData; };  // +0x08
class hkGenericConstraintData : public hkConstraintData_s0108_8960 { public:
    hkGenericConstraintDataScheme m_scheme;  // +0x0c
    hkGenericConstraintDataScheme* getScheme();                          // 0x008DC790
    virtual void getConstraintInfo(hkConstraintInfo& out) const;
    struct RuntimeInfo { int m_sizeOfExternalRuntime; int m_numSolverResults; };
    virtual void getRuntimeInfo(hkBool_s0108_8960 wantRuntime, RuntimeInfo& infoOut) const;
};
static inline void copyVec4(hkVector4_s0108_8960* dst, const hkVector4_s0108_8960* src)
{
    // raw 32-bit copies (no x87 load/store, so signalling NaN payloads survive)
    const uint32_t* s = (const uint32_t*)src; uint32_t* d = (uint32_t*)dst;
    d[0] = s[0]; d[1] = s[1]; d[2] = s[2]; d[3] = s[3];
}
enum {
    CMD_END = 0, CMD_SET_PIVOT_A = 1, CMD_SET_PIVOT_B = 2, CMD_SET_LINEAR_DOF_WORLD = 5, CMD_CONSTRAIN_LINEAR_DOF = 6,
    CMD_SET_BASIS_A_BODY_FRAME = 10, CMD_SET_BASIS_B_BODY_FRAME = 11, CMD_CONSTRAIN_TO_ANGULAR_DOF = 12
};
class hkConstraintConstructionKit { public:
    hkGenericConstraintData* m_constraint;       // +0x00
    hkGenericConstraintDataScheme* m_scheme;     // +0x04
    int m_stiffnessReference;                    // +0x08
    int m_dampingReference;                      // +0x0c
    uint8_t m_linearDofSpecifiedA[3];            // +0x10
    uint8_t m_linearDofSpecifiedB[3];            // +0x13
    uint8_t m_angularBasisSpecifiedA;            // +0x16
    uint8_t m_angularBasisSpecifiedB;            // +0x17
    uint8_t m_pivotSpecifiedA;                   // +0x18
    uint8_t m_pivotSpecifiedB;                   // +0x19
    void begin(hkGenericConstraintData* data);
    int setLinearDofWorld(const hkVector4_s0108_8960& dof, int index);
    void constrainLinearDof(int index);
    void setAngularBasisABodyFrame();
    void setAngularBasisBBodyFrame();
    void constrainToAngularDof(int index);
    int setPivotA(const hkVector4_s0108_8960& pivot);
    int setPivotB(const hkVector4_s0108_8960& pivot);
    void end();
};
struct hk1dLinearBilateralConstraintInfo {
    uint32_t m_pivotA[4];            // copied raw from the parameter block
    uint32_t m_pivotB[4];
    uint32_t m_constrainedDofW[4];
};
struct hkConstraintQueryIn; struct hkConstraintQueryOut;
void hk1dLinearBilateralConstraintBuildJacobian(const hk1dLinearBilateralConstraintInfo* info,
                                                const hkConstraintQueryIn* in, hkConstraintQueryOut* out); // 0x010aa890
struct hkGenericConstraintParameters {
    uint32_t m_vec[4 * 2];           // +0x00: pivotA, pivotB (two hkVector4); further hkVector4 entries follow
    uint32_t m_more[0xb8 / 4 - 8];
    int m_numJacobians;              // +0xb8 (running count of built jacobians)
};
namespace hkMath {
 float atan2fApproximation(float y, float x);   // 0x0120adb0 (cdecl)
}
static const int s_mod3[5] = { 0, 1, 2, 0, 1 };                       // 0x015b9b80 (axis + 1, axis + 2 mod 3)
// ---- items of slice s01088960 end

// ---- items of slice s010898f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
class __declspec(align(16)) hkVector4_s0108_98f0 { public: float x, y, z, w; };
template <typename T> class hkArray_s0108_98f0 {
public:
    T*  m_data;
    int m_size;
    int m_capacityAndFlags;
};
struct hkConstraintInfo_s0108_98f0 {
    int m_maxSizeOfJacobians;
    int m_sizeOfJacobians;
    int m_sizeOfSchemas;
    int m_numSolverResults;
};
class hkGenericConstraintDataScheme_s0108_98f0 {
public:
    hkConstraintInfo_s0108_98f0    m_info;         // +0x00
    hkArray_s0108_98f0<hkVector4_s0108_98f0>  m_data;         // +0x10
    hkArray_s0108_98f0<int>        m_commands;     // +0x1c
    hkArray_s0108_98f0<void*>      m_modifiers;    // +0x28
    hkArray_s0108_98f0<void*>      m_motors;       // +0x34
};
class hkGenericConstraintDataParameters {
public:
    hkVector4_s0108_98f0   m_pivotAw;              // +0x00
    hkVector4_s0108_98f0   m_pivotBw;              // +0x10
    hkVector4_s0108_98f0   m_linearBasisW[3];      // +0x20
    hkVector4_s0108_98f0   m_angularBasisAw[3];    // +0x50
    hkVector4_s0108_98f0   m_angularBasisBw[3];    // +0x80
    const void* m_rbA;                  // +0xb0
    const void* m_rbB;                  // +0xb4
    int         m_currentResult;        // +0xb8
};
class hkConstraintQueryIn {
public:
    char        m_pad[0x44];
    const char* m_solverResults;        // +0x44
};
class hkConstraintQueryOut_s0108_98f0 {
public:
    void* m_constraintInternal;         // +0x00
};
class hkConstraintMotor {
public:
    virtual void unused0();
    virtual void unused1();
    virtual void update( void* jacobian, void* runtime );   // vtable slot 2
};
struct hk1dAngularBilateralInfo {
    hkVector4_s0108_98f0 m_axisA;                  // +0x00
    hkVector4_s0108_98f0 m_axisB;                  // +0x10
    hkVector4_s0108_98f0 m_axisW;                  // +0x20
};
struct hk1dLinearLimitInfo {
    hkVector4_s0108_98f0 m_pivotA;                 // +0x00
    hkVector4_s0108_98f0 m_pivotB;                 // +0x10
    hkVector4_s0108_98f0 m_dofW;                   // +0x20
    float     m_min;                    // +0x30
    float     m_max;                    // +0x34
};
struct hk1dAngularLimitInfo {
    hkVector4_s0108_98f0 m_axis;                   // +0x00
    float     m_min;                    // +0x10
    float     m_max;                    // +0x14
    float     m_angle;                  // +0x18
    float     m_tau;                    // +0x1c  (always 0.5f)
};
struct hk1dAngularFrictionInfo {
    const hkVector4_s0108_98f0* m_axis;            // +0x00
    const char*      m_solver;          // +0x04
    float            m_maxImpulse;      // +0x08
    int              m_useVelocity;     // +0x0c  (always 1)
};
struct hk1dLinearFrictionInfo {
    hkVector4_s0108_98f0   m_deltaPivot;           // +0x00
    hkVector4_s0108_98f0   m_dofW;                 // +0x10
    float       m_maxImpulse;           // +0x20
    const char* m_solver;               // +0x24
};
struct hk1dAngularMotorInfo {
    void*       m_constraintInternal;   // +0x00
    const hkConstraintQueryIn* m_in;    // +0x04
    const char* m_solver;               // +0x08
    const char* m_solver2;              // +0x0c
    int         m_unknown;              // +0x10
    float       m_targetAngle;          // +0x14
    char        m_scratch[24];          // +0x18
};
struct hk1dLinearMotorInfo {
    hkVector4_s0108_98f0   m_dofW;                 // +0x00
    void*       m_constraintInternal;   // +0x10
    const hkConstraintQueryIn* m_in;    // +0x14
    const char* m_solver;               // +0x18
    const char* m_solver2;              // +0x1c
    int         m_unknown;              // +0x20
    float       m_targetVelocity;       // +0x24
    char        m_scratch[36];          // +0x28
};
extern "C" void hk1dAngularBilateralConstraintBuildJacobian( const hk1dAngularBilateralInfo* info,
                                                            const hkConstraintQueryIn* in, hkConstraintQueryOut_s0108_98f0* out );
extern "C" void hk1dLinearLimitBuildJacobian( const hk1dLinearLimitInfo* info,
                                             const hkConstraintQueryIn* in, hkConstraintQueryOut_s0108_98f0* out );
extern "C" void hk1dAngularLimitBuildJacobian( const hk1dAngularLimitInfo* info,
                                              const hkConstraintQueryIn* in, hkConstraintQueryOut_s0108_98f0* out );
extern "C" void hk1dAngularFrictionBuildJacobian( const hk1dAngularFrictionInfo* info,
                                                 const hkConstraintQueryIn* in, hkConstraintQueryOut_s0108_98f0* out );
extern "C" void hk1dLinearFrictionBuildJacobian( const hk1dLinearFrictionInfo* info,
                                                const hkConstraintQueryIn* in, hkConstraintQueryOut_s0108_98f0* out );
extern "C" void hk1dAngularVelocityMotorBeginJacobian( const hkVector4_s0108_98f0* axisW, const hkConstraintQueryIn* in,
                                                      void* constraintInternal, void* infoOut );
extern "C" void hk1dAngularVelocityMotorCommitJacobian( const void* infoTail,
                                                       const hkConstraintQueryIn* in, float targetAngle );
extern "C" void hk1dLinearVelocityMotorBeginJacobian( const hkVector4_s0108_98f0* dofW, const hkVector4_s0108_98f0* pivotBw,
                                                     const hkConstraintQueryIn* in, void* constraintInternal,
                                                     void* infoOut );
extern "C" void hk1dLinearVelocityMotorCommitJacobian( const void* infoTail,
                                                      const hkConstraintQueryIn* in, hkConstraintQueryOut_s0108_98f0* out );
namespace hkInternalConstraintUtils {
    void calcRelativeAngle( const hkVector4_s0108_98f0& a, const hkVector4_s0108_98f0& b, const hkVector4_s0108_98f0& c,
                            const hkVector4_s0108_98f0& d, hkVector4_s0108_98f0& out, float& angle );
}
float __fastcall hkGenericConstraint_calcAngle( int axis, const hkVector4_s0108_98f0* rows );
class hkGenericConstraintData_s0108_98f0 {
protected:
    void constrainToAngularW ( int*& currentCommand, hkVector4_s0108_98f0*& currentData,
                               const hkGenericConstraintDataScheme_s0108_98f0& scheme,
                               hkGenericConstraintDataParameters& vars,
                               const hkConstraintQueryIn& in, hkConstraintQueryOut_s0108_98f0& out ) const;
    void constrainAllAngularW( int*& currentCommand, hkVector4_s0108_98f0*& currentData,
                               const hkGenericConstraintDataScheme_s0108_98f0& scheme,
                               hkGenericConstraintDataParameters& vars,
                               const hkConstraintQueryIn& in, hkConstraintQueryOut_s0108_98f0& out ) const;
    void setLinearLimitW     ( int*& currentCommand, hkVector4_s0108_98f0*& currentData,
                               const hkGenericConstraintDataScheme_s0108_98f0& scheme,
                               hkGenericConstraintDataParameters& vars,
                               const hkConstraintQueryIn& in, hkConstraintQueryOut_s0108_98f0& out ) const;
    void setAngularLimitW    ( int*& currentCommand, hkVector4_s0108_98f0*& currentData,
                               const hkGenericConstraintDataScheme_s0108_98f0& scheme,
                               hkGenericConstraintDataParameters& vars,
                               const hkConstraintQueryIn& in, hkConstraintQueryOut_s0108_98f0& out ) const;
    void setConeLimitW       ( int*& currentCommand, hkVector4_s0108_98f0*& currentData,
                               const hkGenericConstraintDataScheme_s0108_98f0& scheme,
                               hkGenericConstraintDataParameters& vars,
                               const hkConstraintQueryIn& in, hkConstraintQueryOut_s0108_98f0& out ) const;
    void setTwistLimitW      ( int*& currentCommand, hkVector4_s0108_98f0*& currentData,
                               const hkGenericConstraintDataScheme_s0108_98f0& scheme,
                               hkGenericConstraintDataParameters& vars,
                               const hkConstraintQueryIn& in, hkConstraintQueryOut_s0108_98f0& out ) const;
    void setAngularMotorW    ( int*& currentCommand, hkVector4_s0108_98f0*& currentData,
                               hkGenericConstraintDataScheme_s0108_98f0& scheme,
                               hkGenericConstraintDataParameters& vars,
                               const hkConstraintQueryIn& in, hkConstraintQueryOut_s0108_98f0& out ) const;
    void setLinearMotorW     ( int*& currentCommand, hkVector4_s0108_98f0*& currentData,
                               hkGenericConstraintDataScheme_s0108_98f0& scheme,
                               hkGenericConstraintDataParameters& vars,
                               const hkConstraintQueryIn& in, hkConstraintQueryOut_s0108_98f0& out ) const;
    void setAngularFrictionW ( int*& currentCommand, hkVector4_s0108_98f0*& currentData,
                               const hkGenericConstraintDataScheme_s0108_98f0& scheme,
                               hkGenericConstraintDataParameters& vars,
                               const hkConstraintQueryIn& in, hkConstraintQueryOut_s0108_98f0& out ) const;
    void setLinearFrictionW  ( int*& currentCommand, hkVector4_s0108_98f0*& currentData,
                               const hkGenericConstraintDataScheme_s0108_98f0& scheme,
                               hkGenericConstraintDataParameters& vars,
                               const hkConstraintQueryIn& in, hkConstraintQueryOut_s0108_98f0& out ) const;
};
// ---- items of slice s010898f0 end

// ---- items of slice s0108a3f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
class hkTransform_s0108_a3f0;
class __declspec(align(16)) hkVector4_s0108_a3f0 {
public:
    float x, y, z, w;
    void setZero() { x = y = z = w = 0.0f; }
    // Sets *this = t->m_rotation * v + t->m_translation.
    void setTransformedPos( const hkTransform_s0108_a3f0* t, const hkVector4_s0108_a3f0* v );   // 0x1081360
};
class hkMatrix3_s0108_a3f0 {
public:
    hkVector4_s0108_a3f0 m_col0;   // +0x00
    hkVector4_s0108_a3f0 m_col1;   // +0x10
    hkVector4_s0108_a3f0 m_col2;   // +0x20
    void setMul( const hkMatrix3_s0108_a3f0& a, const hkMatrix3_s0108_a3f0& b );
};
class hkRotation_s0108_a3f0 : public hkMatrix3_s0108_a3f0 {};
class hkTransform_s0108_a3f0 {
public:
    hkRotation_s0108_a3f0 m_rotation;   // +0x00
    hkVector4_s0108_a3f0  m_translation;// +0x30
};
class hkBool_s0108_a3f0 {
public:
    char m_bool;
    hkBool_s0108_a3f0() {}
    hkBool_s0108_a3f0( char b ) : m_bool( b ) {}
};
class hkBaseObject_s0108_a3f0 {
public:
    virtual ~hkBaseObject_s0108_a3f0() {}
};
class hkReferencedObject_s0108_a3f0 : public hkBaseObject_s0108_a3f0 {
public:
    unsigned short m_memSizeAndFlags;   // +0x04
    short          m_referenceCount;    // +0x06
    hkReferencedObject_s0108_a3f0() { m_referenceCount = 1; }
    void addReference() const;
    void removeReference() const;
};
class hkThreadMemory_s0108_a3f0 {
public:
    void deallocateChunk( void* p, int nbytes, int align );  // 0x0107db10 (hkThreadMemory::deallocateChunk)
    static hkThreadMemory_s0108_a3f0* getCurrent();
};
hkThreadMemory_s0108_a3f0* hkThreadMemory_s0108_a3f0::getCurrent()
{
    return (hkThreadMemory_s0108_a3f0*)TlsGetValue( g_hkThreadMemoryTls );
}
template <typename T> class hkArray_s0108_a3f0 {
public:
    T*  m_data;
    int m_size;
    int m_capacityAndFlags;
    hkArray_s0108_a3f0() { m_data = 0; m_size = 0; m_capacityAndFlags = 0x80000000; }
    ~hkArray_s0108_a3f0()
    {
        if ( ( m_capacityAndFlags & 0x80000000 ) == 0 )
            hkThreadMemory_s0108_a3f0::getCurrent()->deallocateChunk(
                m_data, ( m_capacityAndFlags & 0x3fffffff ) * (int)sizeof(T), 0x14 );
    }
};
struct hkConstraintInfo_s0108_a3f0 {
    int m_maxSizeOfJacobians;
    int m_sizeOfJacobians;
    int m_sizeOfSchemas;
    int m_numSolverResults;
};
class hkGenericConstraintDataScheme_s0108_a3f0 {
public:
    hkConstraintInfo_s0108_a3f0      m_info;        // +0x00
    hkArray_s0108_a3f0<hkVector4_s0108_a3f0>    m_data;        // +0x10
    hkArray_s0108_a3f0<int>          m_commands;    // +0x1c
    hkArray_s0108_a3f0<void*>        m_modifiers;   // +0x28
    hkArray_s0108_a3f0<void*>        m_motors;      // +0x34

    hkGenericConstraintDataScheme_s0108_a3f0();
};
hkGenericConstraintDataScheme_s0108_a3f0::hkGenericConstraintDataScheme_s0108_a3f0()
{
    m_info.m_maxSizeOfJacobians = 0;
    m_info.m_sizeOfJacobians = 0;
    m_info.m_sizeOfSchemas = 0;
    m_info.m_numSolverResults = 0;
}
class hkGenericConstraintDataParameters_s0108_a3f0 {
public:
    hkVector4_s0108_a3f0   m_pivotAw;               // +0x00
    hkVector4_s0108_a3f0   m_pivotBw;               // +0x10
    hkVector4_s0108_a3f0   m_linearBasisW[3];       // +0x20
    hkVector4_s0108_a3f0   m_angularBasisAw[3];     // +0x50
    hkVector4_s0108_a3f0   m_angularBasisBw[3];     // +0x80
    const void* m_rbA;                   // +0xb0
    const void* m_rbB;                   // +0xb4
    int         m_currentResult;         // +0xb8
};
class hkConstraintQueryIn_s0108_a3f0 {
public:
    char        m_pad00[0x18];
    hkReal      m_rhsFactor;             // +0x18
    char        m_pad1c[0x30 - 0x1c];
    const hkTransform_s0108_a3f0* m_transformA;     // +0x30
    const hkTransform_s0108_a3f0* m_transformB;     // +0x34
    char        m_pad38[0x44 - 0x38];
    const char* m_solverResults;         // +0x44
};
class hkConstraintQueryOut_s0108_a3f0 {
public:
    void* m_constraintInternal;          // +0x00
};
class hkConstraintData_s0108_a3f0 : public hkReferencedObject_s0108_a3f0 {
public:
    unsigned int m_userData;             // +0x08
    hkConstraintData_s0108_a3f0() { m_userData = 0; }
    virtual void buildJacobian( const hkConstraintQueryIn_s0108_a3f0& in, hkConstraintQueryOut_s0108_a3f0& out );
};
class hkGenericConstraintData_s0108_a3f0 : public hkConstraintData_s0108_a3f0 {
public:
    hkGenericConstraintDataScheme_s0108_a3f0 m_scheme;   // +0x0c

    hkGenericConstraintData_s0108_a3f0();
    virtual ~hkGenericConstraintData_s0108_a3f0();
    virtual void buildJacobian( const hkConstraintQueryIn_s0108_a3f0& in, hkConstraintQueryOut_s0108_a3f0& out );

private:
    void buildJacobianInternal( const hkGenericConstraintDataScheme_s0108_a3f0& scheme,
                                const hkConstraintQueryIn_s0108_a3f0& in, hkConstraintQueryOut_s0108_a3f0& out );

    // scheme command handlers (defined in slice s010898f0).
    void constrainToAngularW ( int*& cc, hkVector4_s0108_a3f0*& cd, const hkGenericConstraintDataScheme_s0108_a3f0& s,   // 0x10898f0
                               hkGenericConstraintDataParameters_s0108_a3f0& v,
                               const hkConstraintQueryIn_s0108_a3f0& in, hkConstraintQueryOut_s0108_a3f0& out ) const;
    void constrainAllAngularW( int*& cc, hkVector4_s0108_a3f0*& cd, const hkGenericConstraintDataScheme_s0108_a3f0& s,   // 0x1089a20
                               hkGenericConstraintDataParameters_s0108_a3f0& v,
                               const hkConstraintQueryIn_s0108_a3f0& in, hkConstraintQueryOut_s0108_a3f0& out ) const;
    void setLinearLimitW     ( int*& cc, hkVector4_s0108_a3f0*& cd, const hkGenericConstraintDataScheme_s0108_a3f0& s,   // 0x1089ba0
                               hkGenericConstraintDataParameters_s0108_a3f0& v,
                               const hkConstraintQueryIn_s0108_a3f0& in, hkConstraintQueryOut_s0108_a3f0& out ) const;
    void setAngularLimitW    ( int*& cc, hkVector4_s0108_a3f0*& cd, const hkGenericConstraintDataScheme_s0108_a3f0& s,   // 0x1089c60
                               hkGenericConstraintDataParameters_s0108_a3f0& v,
                               const hkConstraintQueryIn_s0108_a3f0& in, hkConstraintQueryOut_s0108_a3f0& out ) const;
    void setConeLimitW       ( int*& cc, hkVector4_s0108_a3f0*& cd, const hkGenericConstraintDataScheme_s0108_a3f0& s,   // 0x1089d70
                               hkGenericConstraintDataParameters_s0108_a3f0& v,
                               const hkConstraintQueryIn_s0108_a3f0& in, hkConstraintQueryOut_s0108_a3f0& out ) const;
    void setTwistLimitW      ( int*& cc, hkVector4_s0108_a3f0*& cd, const hkGenericConstraintDataScheme_s0108_a3f0& s,   // 0x1089f10
                               hkGenericConstraintDataParameters_s0108_a3f0& v,
                               const hkConstraintQueryIn_s0108_a3f0& in, hkConstraintQueryOut_s0108_a3f0& out ) const;
    void setAngularMotorW    ( int*& cc, hkVector4_s0108_a3f0*& cd, hkGenericConstraintDataScheme_s0108_a3f0& s,         // 0x1089fc0
                               hkGenericConstraintDataParameters_s0108_a3f0& v,
                               const hkConstraintQueryIn_s0108_a3f0& in, hkConstraintQueryOut_s0108_a3f0& out ) const;
    void setLinearMotorW     ( int*& cc, hkVector4_s0108_a3f0*& cd, hkGenericConstraintDataScheme_s0108_a3f0& s,         // 0x108a180
                               hkGenericConstraintDataParameters_s0108_a3f0& v,
                               const hkConstraintQueryIn_s0108_a3f0& in, hkConstraintQueryOut_s0108_a3f0& out ) const;
    void setAngularFrictionW ( int*& cc, hkVector4_s0108_a3f0*& cd, const hkGenericConstraintDataScheme_s0108_a3f0& s,   // 0x108a2b0
                               hkGenericConstraintDataParameters_s0108_a3f0& v,
                               const hkConstraintQueryIn_s0108_a3f0& in, hkConstraintQueryOut_s0108_a3f0& out ) const;
    void setLinearFrictionW  ( int*& cc, hkVector4_s0108_a3f0*& cd, const hkGenericConstraintDataScheme_s0108_a3f0& s,   // 0x108a330
                               hkGenericConstraintDataParameters_s0108_a3f0& v,
                               const hkConstraintQueryIn_s0108_a3f0& in, hkConstraintQueryOut_s0108_a3f0& out ) const;

    // Linear-DOF builder helpers (defined in slice s01088960).
    void buildLinearDof( int*& cc, hkVector4_s0108_a3f0*& cd, const hkGenericConstraintDataScheme_s0108_a3f0& s,   // 0x10897d0
                         hkGenericConstraintDataParameters_s0108_a3f0& v,
                         const hkConstraintQueryIn_s0108_a3f0& in, hkConstraintQueryOut_s0108_a3f0& out ) const;
    void buildLinearBasisWorld( int*& cc, hkVector4_s0108_a3f0*& cd, const hkGenericConstraintDataScheme_s0108_a3f0& s,   // 0x1089700
                         hkGenericConstraintDataParameters_s0108_a3f0& v,
                         const hkConstraintQueryIn_s0108_a3f0& in, hkConstraintQueryOut_s0108_a3f0& out ) const;
};
extern "C" void hkBeginConstraints( const hkConstraintQueryIn_s0108_a3f0* in, hkConstraintQueryOut_s0108_a3f0* out,
        int numResults, int extra );                                               // 0x10aa080
extern "C" void hkReplacePreviousRhs( float value, const hkConstraintQueryIn_s0108_a3f0* in,
        hkConstraintQueryOut_s0108_a3f0* out, int count );                               // 0x10aa050
extern "C" void hkMatrix3_setIdentity( hkMatrix3_s0108_a3f0* m );                             // 0x48daf0
extern "C" hkBool_s0108_a3f0 hkMath_equal( float a, float b, float eps );                     // 0x1080e40
typedef void  (*ModifierFn)( hkGenericConstraintDataParameters_s0108_a3f0*, int );
typedef float (*ModifierFloatFn)( hkGenericConstraintDataParameters_s0108_a3f0*, int );
class hkEntity_s0108_a3f0 : public hkReferencedObject_s0108_a3f0 {
public:
    void* m_world;          // +0x08
};
class hkAction_s0108_a3f0 : public hkReferencedObject_s0108_a3f0 {};
class hkWorldObject_s0108_a3f0 : public hkReferencedObject_s0108_a3f0 {
public:
    void removeReference();                                  // 0x109ae60
};
class hkWorld_s0108_a3f0;
class hkConstraintInstance_s0108_a3f0 : public hkReferencedObject_s0108_a3f0 {
public:
    hkConstraintInstance_s0108_a3f0( int wantRuntime );
    virtual ~hkConstraintInstance_s0108_a3f0();

    void*   m_owner;        // +0x08
    void*   m_data;         // +0x0c
    void*   m_entities[2];  // +0x10
    char    m_priority;     // +0x18
    char    m_wantRuntime;  // +0x19
    char*   m_name;         // +0x1c
    int     m_userData;     // +0x20
    char    m_pad24[4];
};
class hkWorld_s0108_a3f0 {
public:
    void removeActionImmediately( hkAction_s0108_a3f0* action );         // 0x1086030
    void executePendingOperations();                         // 0x1082bf0
    char m_pad00[0x88];
    int  m_pending;                                          // +0x88
    int  m_refCount;                                         // +0x8c
    char m_pad90[4];
    char m_flag94;                                           // +0x94
};
class hkConstraintChainInstance;
class hkMemory_s0108_a3f0 {
public:
    virtual void memoryUnused0();
    virtual void memoryUnused1();
    virtual void memoryUnused2();
    virtual void memoryUnused3();
    virtual void* allocate( int numBytes, int align );       // +0x10
    static hkMemory_s0108_a3f0* s_instance;                             // 0x16e4178
};
class hkConstraintChainInstanceAction : public hkAction_s0108_a3f0 {
public:
    hkConstraintChainInstanceAction( hkConstraintChainInstance* instance );

    unsigned int m_pad08[4];                                 // +0x08 .. +0x17
    hkConstraintChainInstance* m_chainInstance;              // +0x18
};
class hkConstraintChainInstance : public hkConstraintInstance_s0108_a3f0 {
public:
    hkArray_s0108_a3f0<void*> m_chainedEntities;    // +0x28
    hkAction_s0108_a3f0*      m_action;             // +0x34

    hkConstraintChainInstance( void* data );
    virtual ~hkConstraintChainInstance();
    virtual void entityRemovedCallback( hkEntity_s0108_a3f0* entity );
    void addEntity( void* entity );
};
hkConstraintChainInstanceAction::hkConstraintChainInstanceAction( hkConstraintChainInstance* instance )
{
    m_memSizeAndFlags = 0x1c;
    m_pad08[ 0 ] = 0;
    m_pad08[ 1 ] = 0;
    m_pad08[ 2 ] = 0;
    m_pad08[ 3 ] = 0;
    m_chainInstance = instance;
}
extern "C" void hkWorldOperationUtil_removeConstraintImmediately( hkWorld_s0108_a3f0* world,
        hkConstraintChainInstance* instance, int force );           // 0x109fa10
class hkLimitedHingeConstraintData : public hkConstraintData_s0108_a3f0 {
public:
    hkReal  m_minAngle;              // +0x0c
    hkReal  m_maxAngle;              // +0x10
    hkReal  m_maxFrictionTorque;     // +0x14
    hkReal  m_angularLimitsTauFactor;// +0x18
    char    m_pad1c[4];

    struct ConstraintBasisA {
        hkVector4_s0108_a3f0 m_pivot;           // object +0x20
        hkVector4_s0108_a3f0 m_axle;            // object +0x30
        hkVector4_s0108_a3f0 m_perpToAxle1;     // object +0x40
        hkVector4_s0108_a3f0 m_perpToAxle2;     // object +0x50
    } m_basisA;                      // +0x20

    struct ConstraintBasisB {
        hkVector4_s0108_a3f0 m_pivot;           // object +0x60
        hkVector4_s0108_a3f0 m_axle;            // object +0x70
        hkVector4_s0108_a3f0 m_perp2FreeAxis;   // object +0x80
    } m_basisB;                      // +0x60

    hkLimitedHingeConstraintData();
    virtual ~hkLimitedHingeConstraintData();
    void setInBodySpace( const hkVector4_s0108_a3f0& pivotA, const hkVector4_s0108_a3f0& pivotB,
                         const hkVector4_s0108_a3f0& axleA, const hkVector4_s0108_a3f0& axleB,
                         const hkVector4_s0108_a3f0& referenceA, const hkVector4_s0108_a3f0& referenceB );
    virtual hkBool_s0108_a3f0 isValid() const;
};
static __forceinline void hkVector4_normalize3( hkVector4_s0108_a3f0& v )
{
    float len2 = v.x * v.x + v.y * v.y + v.z * v.z;
    float inv;
    if ( len2 == 0.0f )
        inv = 0.0f;
    else
        inv = 1.0f / sqrtf( len2 );
    v.x *= inv;
    v.y *= inv;
    v.z *= inv;
    v.w *= inv;
}
// ---- items of slice s0108a3f0 end

// ---- items of slice s0108b2f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
class __declspec(align(16)) hkVector4_s0108_b2f0
{
public:
	float x, y, z, w;
	__forceinline hkVector4_s0108_b2f0& operator=(const hkVector4_s0108_b2f0& o) { x = o.x; y = o.y; z = o.z; w = o.w; return *this; }
	__forceinline void addTranslation(const hkVector4_s0108_b2f0& t) { x = x + t.x; y = y + t.y; z = z + t.z; w = t.w; }
};
class hkMatrix3_s0108_b2f0
{
public:
	hkVector4_s0108_b2f0 m_col[3];
};
class hkRotation_s0108_b2f0 : public hkMatrix3_s0108_b2f0 {};
class hkTransform_s0108_b2f0
{
public:
	hkRotation_s0108_b2f0 m_rotation;     // +0x00
	hkVector4_s0108_b2f0 m_translation;   // +0x30
};
class hkConstraintQueryIn_s0108_b2f0
{
public:
	float m_substepDeltaTime;            // +0x00
	float m_substepInvDeltaTime;         // +0x04
	float m_frameDeltaTime;              // +0x08
	float m_frameInvDeltaTime;           // +0x0c
	float m_virtualMassFactor;           // +0x10
	float m_rhsFactor;                   // +0x14
	float m_dampingFactor;               // +0x18
	float m_frictionRhsFactor;           // +0x1c
	void* m_accumulatorBufferRoot;       // +0x20
	void* m_jacobianBufferRoot;          // +0x24
	void* m_bodyA;                       // +0x28
	void* m_bodyB;                       // +0x2c
	hkTransform_s0108_b2f0* m_transformA;           // +0x30
	hkTransform_s0108_b2f0* m_transformB;           // +0x34
	float m_tau;                         // +0x38
	float m_damping;                     // +0x3c
	void* m_constraintInstance;          // +0x40
	void* m_constraintRuntime;           // +0x44
};
class hkConstraintQueryOut_s0108_b2f0
{
public:
	void* m_jacobians;              // +0x00
	int32_t m_numSolverResults;     // +0x04
	int32_t m_numSolverElemTemps;   // +0x08
};
class hkBaseRef
{
public:
	uint16_t m_memSizeAndFlags;         // +0x04
	uint16_t m_referenceCount;          // +0x06

	// The size-and-flags word is written by the allocator before construction.
	hkBaseRef() : m_referenceCount(1) {}
	virtual ~hkBaseRef() {}
	void addReference();                                                    // 0x01082590
	// Inlined by retail inside ~hkConstraintInstance.
	void removeReference()
	{
		if (m_memSizeAndFlags) {
			if (--m_referenceCount == 0)
				delete this;
		}
	}
};
class hkConstraintData_s0108_b2f0 : public hkBaseRef
{
public:
	uint32_t m_userData;                // +0x08

	hkConstraintData_s0108_b2f0() : m_userData(0) {}
	virtual ~hkConstraintData_s0108_b2f0() {}
};
struct hkConstraintInfo_s0108_b2f0 {                                            // 0x10 bytes
	int32_t m_maxSizeOfSchema;          // +0x00
	int32_t m_sizeOfSchemas;            // +0x04
	int32_t m_numSolverResults;         // +0x08
	int32_t m_numSolverElemTemps;       // +0x0c
};
struct hkConstraintRuntimeInfo {                                     // 0x08 bytes
	int32_t m_numSolverResults;         // +0x00
	int32_t m_numSolverElemTemps;       // +0x04
};
struct hkBallSocketConstraintInfo {                                  // 0x20 bytes
	hkVector4_s0108_b2f0 m_pivotA;                 // +0x00
	hkVector4_s0108_b2f0 m_pivotB;                 // +0x10
};
class hkThreadMemory_s0108_b2f0
{
public:
	void deallocateChunk(void* data, int numBytes, int alignment);      // 0x0107db10
};
extern unsigned long  g_hkThreadMemoryTls_s0108_b2f0;          // 0x016e4174
struct hkBallSocketChainArray {
	hkBallSocketConstraintInfo* m_data;          // +0x00
	int32_t m_size;                              // +0x04
	int32_t m_capacityAndFlags;                  // +0x08
};
class hkMemory_s0108_b2f0
{
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
	virtual void v10();
	virtual void deallocate(void* block, int size, int memoryClass);   // slot 5 (+0x14)
};
extern hkMemory_s0108_b2f0*      g_hkMemoryInstance;           // 0x016e4178
class hkBallSocketChainData : public hkConstraintData_s0108_b2f0
{
public:
	hkBallSocketChainArray m_chain;              // +0x0c
	hkReal m_tau;                                // +0x18
	hkReal m_damping;                            // +0x1c
	hkReal m_maxImpulse;                         // +0x20
	hkReal m_maxFriction;                        // +0x24

	hkBallSocketChainData();

	virtual ~hkBallSocketChainData();
	virtual void getConstraintInfo(hkConstraintInfo_s0108_b2f0& info) const;
	virtual void getRuntimeInfo(bool allow, hkConstraintRuntimeInfo& info) const;
	void addConstraint(const hkVector4_s0108_b2f0& pivotA, const hkVector4_s0108_b2f0& pivotB);
	virtual void buildJacobian(const hkConstraintQueryIn_s0108_b2f0& in, hkConstraintQueryOut_s0108_b2f0& out);
};
hkBallSocketChainData::~hkBallSocketChainData()
{
	// hkArray<hkBallSocketConstraintInfo>::deallocate()
	if (m_chain.m_capacityAndFlags < 0)
		return;
	// hkThreadMemory::getInstance()
	hkThreadMemory_s0108_b2f0* pThreadMemory = (hkThreadMemory_s0108_b2f0*)TlsGetValue(g_hkThreadMemoryTls_s0108_b2f0);
	pThreadMemory->deallocateChunk(m_chain.m_data,
	                               (uint32_t)(m_chain.m_capacityAndFlags & 0x3fffffff) * 0x20u, 0x14);
}
class hkWorld_s0108_b2f0;
struct hkCollidable_s0108_b2f0;
struct hkMotion_s0108_b2f0
{
	uint8_t     pad00[0x08];
	int32_t     m_solverBodyIndex;      // +0x08
	uint8_t     pad0c[0x04];
	hkTransform_s0108_b2f0 m_transform;            // +0x10
};
class hkEntity_s0108_b2f0 : public hkBaseRef                  // hkWorldObject
{
public:
	hkWorld_s0108_b2f0* m_world;                   // +0x08
	uint8_t  pad0c[0x4c];
	hkMotion_s0108_b2f0* m_motion;                 // +0x58
	void removeReference();                                         // 0x0109ae60
};
struct hkWorld_s0108_b2f0
{
	uint8_t   pad00[0x34];
	hkEntity_s0108_b2f0* m_fixedBody;              // +0x34
};
struct hkConstraintRuntime
{
	uint8_t pad00[0x10];
	uint8_t m_priority;                 // +0x10
};
class hkConstraintInstance_s0108_b2f0 : public hkBaseRef
{
public:
	enum ConstraintPriority
	{
		CONSTRAINT_PRIORITY_INVALID = 0,
		CONSTRAINT_PRIORITY_PSI,
		CONSTRAINT_PRIORITY_ENTITY
	};

	hkWorld_s0108_b2f0*             m_world;       // +0x08
	hkConstraintData_s0108_b2f0*    m_constraintData;  // +0x0c
	hkEntity_s0108_b2f0*            m_entityA;     // +0x10
	hkEntity_s0108_b2f0*            m_entityB;     // +0x14
	uint8_t              m_priority;    // +0x18
	uint8_t              m_wantRuntime; // +0x19
	uint8_t              pad1a[2];      // +0x1a
	uint32_t             m_dynamics;    // +0x1c
	uint32_t             m_field20;     // +0x20
	hkConstraintRuntime* m_runtime;     // +0x24
	hkEntity_s0108_b2f0**           m_chainEntities;   // +0x28 (ball-socket chains only)
	int32_t              m_numChainEntities; // +0x2c

	hkConstraintInstance_s0108_b2f0(hkEntity_s0108_b2f0* entityA, hkEntity_s0108_b2f0* entityB,
	                     hkConstraintData_s0108_b2f0* data, ConstraintPriority priority);
	hkConstraintInstance_s0108_b2f0(ConstraintPriority priority);
	virtual ~hkConstraintInstance_s0108_b2f0();
	void setPriority(ConstraintPriority priority);
	virtual void entityRemovedCallback(hkEntity_s0108_b2f0* entity);
	void fixNullEntities();
};
class hkPhantom_s0108_b2f0;
struct hkCollidableAddedEvent
{
	hkPhantom_s0108_b2f0*          m_phantom;      // +0x00
	const hkCollidable_s0108_b2f0* m_collidable;   // +0x04
	int32_t             m_accept;       // +0x08
};
struct hkCollidableRemovedEvent
{
	hkPhantom_s0108_b2f0*          m_phantom;      // +0x00
	const hkCollidable_s0108_b2f0* m_collidable;   // +0x04
	bool                m_removed;      // +0x08
};
class hkPhantomListener_s0108_b2f0
{
public:
	virtual void collidableAdded(const hkCollidableAddedEvent& event);
	virtual void collidableRemoved(const hkCollidableRemovedEvent& event);
};
class hkPhantom_s0108_b2f0
{
public:
	uint8_t             pad00[0x58];
	hkPhantomListener_s0108_b2f0** m_listeners;    // +0x58
	int32_t             m_numListeners; // +0x5c

	int32_t fireCollidableAdded(const hkCollidable_s0108_b2f0* collidable);
	void    fireCollidableRemoved(const hkCollidable_s0108_b2f0* collidable, bool removed);
};
// ---- items of slice s0108b2f0 end

// ---- items of slice s0108e080 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern unsigned long g_hkThreadMemoryTls_s0108_e080;   // 0x016e4174
class hkThreadMemory_s0108_e080 { public:
    void* m_vtable;                     // +0x00
    char  m_pad04[0x1c];                // +0x04
    int   m_stackCurrent;               // +0x20
    int   m_stackEnd;                   // +0x2c
    char  m_pad30[0x84];                // +0x30
    int   m_rowHead[0x11];              // +0xb4
    // 0x0107daa0
    void* allocateChunk(int size, int memClass);  // 0x0107daa0 (hkThreadMemory::allocateChunk)
    // 0x0107db10
    void  deallocateChunk(void* p, int size, int memClass);  // 0x0107db10 (hkThreadMemory::deallocateChunk)
};
class hkVector4_s0108_e080 { public: float m_x, m_y, m_z, m_w; };
class hkAabb_s0108_e080 { public: hkVector4_s0108_e080 m_min, m_max; };
template<class T> class hkArray_s0108_e080 { public:
    T*      m_data;                 // +0x00
    int32_t m_size;                 // +0x04
    int32_t m_capacityAndFlags;     // +0x08
};
class hkReferencedObject_s0108_e080 { public:
    uint16_t m_memSizeAndFlags;     // +0x04
    int16_t  m_referenceCount;      // +0x06
    virtual ~hkReferencedObject_s0108_e080();
    void setVtable(const void* vt) { *(const void**)this = vt; }
};
class hkMemory_s0108_e080 { public:
    virtual ~hkMemory_s0108_e080();
    virtual void vslot1();
    virtual void vslot2();
    virtual void vslot3();
    // slot 4 (+0x10): allocate
    virtual void* allocate(int nbytes, int memoryClass);
    // slot 5 (+0x14): deallocate
    virtual void deallocate(void* p, int nbytes, int memoryClass);
};
extern hkMemory_s0108_e080* hkMemory_instance;      // 0x016e4178
class hkStatisticsCollector_s0108_e080 { public:
    virtual ~hkStatisticsCollector_s0108_e080();
    virtual void beginObject(const char* name, int flags, const void* obj);                              // +4
    // +8
    virtual void addArray(const char* name, int memClass, const void* data, int used, int allocated);
    virtual void vslot3();
    virtual void endObjectava();                                                                          // +0x10
    virtual void endObject();                                                                             // +0x14
};
struct hkShape_s0108_e080;
struct hkWorld_s0108_e080;
class hkPhantom_s0108_e080;
struct hkWorldObjectMember { void calcStatistics(hkStatisticsCollector_s0108_e080* c) const; };
void hkWorldObject_copyProperties(void* self, const void* other);
class hkPhantom_s0108_e080 : public hkReferencedObject_s0108_e080 { public:
    hkWorld_s0108_e080* m_world;                       // +0x08
    uint32_t m_pad0c[4];                    // +0x0c
    hkShape_s0108_e080* m_shape;                       // +0x1c
    uint32_t m_pad20;                       // +0x20
    void*    m_motionState;                 // +0x24
    uint32_t m_pad28[1];                    // +0x28
    int32_t  m_ownerOffset;                 // +0x2c
    uint8_t  m_pad30[0x58 - 0x30];          // +0x30
    hkArray_s0108_e080<void*> m_overlapListeners;      // +0x58
    hkArray_s0108_e080<void*> m_phantomListeners;      // +0x64

    // 0x0108e680
    void updateBroadPhase(const hkAabb_s0108_e080& aabb);
    // 0x0108e370
    void firePhantomAdded();
    // 0x0108e300
    void firePhantomRemoved();
    // 0x0108e3e0
    void firePhantomShapeSet();
    // 0x0108e5e0
    virtual void deallocateInternalArrays();
    // 0x0108e450  hkArray<void*>::removeAtValue, inlined against m_overlapListeners
    void overlapRemoveAtValue(void* value);
    // 0x0108e4a0  hkArray<void*>::pushBack, inlined against m_overlapListeners
    void overlapPushBack(void* value);
    // 0x0108e2c0  hkArray<void*>::removeNulls, inlined against m_overlapListeners
    void overlapRemoveNulls();
};
class hkAabbPhantom : public hkPhantom_s0108_e080 { public:
    hkAabb_s0108_e080 m_aabb;                              // +0x70
    hkArray_s0108_e080<void*> m_overlappingCollidables;    // +0x90

    // 0x0108dfe0
    hkAabbPhantom(const hkAabb_s0108_e080& aabb, uint32_t collisionFilterInfo);
    // 0x0108e080
    virtual hkPhantom_s0108_e080* clone() const;
    // 0x0108e1d0
    virtual void deallocateInternalArrays();
    // 0x0108e250
    virtual void* scalarDeletingDestructor(unsigned int flags);
    // 0x0108e4e0
    virtual void calcStatistics(hkStatisticsCollector_s0108_e080* c) const;
};
class hkPhantomListener_s0108_e080 { public:
    virtual void vslot0();
    virtual void phantomAdded(const hkPhantom_s0108_e080* p);        // +0x04
    virtual void phantomRemoved(const hkPhantom_s0108_e080* p);      // +0x08
    virtual void phantomShapeSet(const hkPhantom_s0108_e080* p);     // +0x0c
    virtual void vslot4();                                // +0x10
};
struct hkPlacement { char dummy; };
struct hkConstraintRuntimeInfo_s0108_e080 {
    int32_t m_sizeOfThis;      // +0x00
    int32_t m_sizeOfAll;       // +0x04
};
typedef unsigned char chkHkBool;
class hkBool_s0108_e080 { public: unsigned char m_bool; };
struct hkWheelConstraintData {
    float m_ref[8];     // +0x00 .. +0x20 (m_ref[0..7] at +0x00, second vec at +0x20)
    float m_axisA[4];   // +0x40
    float m_axisB[4];   // +0x50
    float m_axisC[4];   // +0x60
    float m_axisD[4];   // +0x70
    float m_vecE[4];    // +0x80
    float m_min;        // +0x90
    float m_max;        // +0x94
    char m_pad98[4];    // +0x98

    // 0x0108e940
    virtual void getRuntimeInfo(chkHkBool valid, hkConstraintRuntimeInfo_s0108_e080* info) const;
    // 0x0108e970
    virtual hkBool_s0108_e080 isValid() const;
    virtual ~hkWheelConstraintData() {}
};
// ---- items of slice s0108e080 end

// ---- items of slice s0108eb30 begin (TODO(rewrite): local stubs, replace by canonical classes)
class hkRotation_s0108_eb30;
class hkTransform_s0108_eb30;
__declspec(align(16)) class hkVector4
{
public:
	float x, y, z, w;
	__forceinline void addTranslation(const hkVector4& t) { x = x + t.x; y = y + t.y; z = z + t.z; w = t.w; }
	void setRotatedDir(const hkRotation_s0108_eb30& r, const hkVector4& v);         // 0x010814a0
	void setRotatedInverseDir(const hkRotation_s0108_eb30& r, const hkVector4& v);  // 0x01081440
	void setTransformedPos(const hkTransform_s0108_eb30& t, const hkVector4& p);    // 0x01081360
	void setMul(const hkVector4& a, const hkVector4& b);                 // 0x01082210
	void normalize();                                                    // 0x010821a0
};
class hkMatrix3_s0108_eb30
{
public:
	hkVector4 m_col[3];
};
class hkRotation_s0108_eb30 : public hkMatrix3_s0108_eb30
{
public:
	void set(const hkVector4& q);                                        // 0x010824a0
};
class hkTransform_s0108_eb30
{
public:
	hkRotation_s0108_eb30 m_rotation;     // +0x00
	hkVector4 m_translation;   // +0x30
};
__forceinline void setRotatedDir(hkVector4& d, const hkRotation_s0108_eb30& r, const hkVector4& v)
{
	const float vx = v.x, vy = v.y, vz = v.z;
	d.x = (vz * r.m_col[2].x + vy * r.m_col[1].x) + vx * r.m_col[0].x;
	d.y = (vz * r.m_col[2].y + vy * r.m_col[1].y) + vx * r.m_col[0].y;
	d.z = (vz * r.m_col[2].z + vy * r.m_col[1].z) + vx * r.m_col[0].z;
	d.w = 0.0f;
}
class hkSolverResults
{ public:
	hkReal m_impulseApplied;        // +0
	hkReal m_internalSolverData;    // +4
};
class hkConstraintQueryIn_s0108_eb30
{
public:
	float m_substepDeltaTime;            // +0x00
	float m_substepInvDeltaTime;         // +0x04
	float m_frameDeltaTime;              // +0x08
	float m_frameInvDeltaTime;           // +0x0c
	float m_virtualMassFactor;           // +0x10
	float m_rhsFactor;                   // +0x14
	float m_dampingFactor;               // +0x18
	float m_frictionRhsFactor;           // +0x1c
	void* m_accumulatorBufferRoot;       // +0x20
	void* m_jacobianBufferRoot;          // +0x24
	void* m_bodyA;                       // +0x28
	void* m_bodyB;                       // +0x2c
	hkTransform_s0108_eb30* m_transformA;           // +0x30
	hkTransform_s0108_eb30* m_transformB;           // +0x34
	float m_tau;                         // +0x38
	float m_damping;                     // +0x3c
	void* m_constraintInstance;          // +0x40
	void* m_constraintRuntime;           // +0x44
};
class hkConstraintQueryOut_s0108_eb30
{
public:
	void* m_jacobians;          // +0
	void* m_jacobianSchemas;    // +4
};
class hkConstraintData_s0108_eb30
{
public:
	virtual ~hkConstraintData_s0108_eb30();
	int m_memSizeAndFlags_userData[2];  // +0x04
};
class hkMemory_s0108_eb30
{
public:
	virtual void* allocate(int nbytes, int cl);                       // 0
	virtual void  deallocate(void* p);                                // 1
	virtual void* alignedAllocate(int alignment, int nbytes, int cl); // 2
	virtual void  alignedDeallocate(void* p);                         // 3
	virtual void* allocateChunk(int nbytes, int cl);                  // 4
	virtual void  deallocateChunk(void* p, int nbytes, int cl);       // 5
	static hkMemory_s0108_eb30* s_instance;                                      // 0x016e4178
};
hkMemory_s0108_eb30* hkMemory_s0108_eb30::s_instance;
class hkBool_s0108_eb30
{
public:
	hkBool_s0108_eb30() {}
	hkBool_s0108_eb30(bool b) : m_bool(b ? 1 : 0) {}
	unsigned char m_bool;
};
class hkConstraintMotorInput
{
public:
	float m_virtualMass;             // +0x00
	hkConstraintQueryIn_s0108_eb30* m_stepInfo; // +0x04
	hkSolverResults m_lastResults;   // +0x08
	float m_deltaTarget;             // +0x10
	float m_positionError;           // +0x14
};
class hkConstraintMotorOutput
{
public:
	float m_targetPosition;          // +0x00
	float m_targetVelocity;          // +0x04
	float m_minForce;                // +0x08
	float m_maxForce;                // +0x0c
	float m_tau;                     // +0x10
	float m_damping;                 // +0x14
};
class hkConstraintMotor_s0108_eb30
{
public:
	virtual ~hkConstraintMotor_s0108_eb30();
	virtual hkConstraintMotor_s0108_eb30* clone() const;
	virtual void calcMotorData(const hkConstraintMotorInput& in, hkConstraintMotorOutput& out);
	short m_memSizeAndFlags;         // +0x04
	short m_referenceCount;          // +0x06
};
class hkLimitedForceConstraintMotor : public hkConstraintMotor_s0108_eb30
{
public:
	float m_minForce;                // +0x08
	float m_maxForce;                // +0x0c
};
class hkVelocityConstraintMotor : public hkLimitedForceConstraintMotor
{
public:
	float m_tau;                     // +0x10
	float m_velocityTarget;          // +0x14
	bool m_useVelocityTargetFromConstraintTargets;  // +0x18
	virtual void calcMotorData(const hkConstraintMotorInput& in, hkConstraintMotorOutput& out);
	virtual hkConstraintMotor_s0108_eb30* clone() const;
};
struct hkConstraintInfo_s0108_eb30
{
	int m_numSolverResults;    // +0x00
	int m_sizeOfSchema;        // +0x04
	int m_sizeOfRuntime;       // +0x08
	int m_numSolverResults2;   // +0x0c
};
struct RuntimeInfo
{
	int m_size;                // +0x00
	int m_numSolverResults;    // +0x04
};
class hkStiffSpringConstraintData : public hkConstraintData_s0108_eb30
{
public:
	hkReal m_springLength;   // +0x0c
	hkVector4 m_pivotInA;    // +0x10
	hkVector4 m_pivotInB;    // +0x20
	virtual hkBool_s0108_eb30 isValid() const;
	virtual void buildJacobian(const hkConstraintQueryIn_s0108_eb30& in, hkConstraintQueryOut_s0108_eb30& out);
	virtual void getRuntimeInfo(hkBool_s0108_eb30 wantRuntime, RuntimeInfo& info) const;
};
class hkStiffSpringChainData : public hkConstraintData_s0108_eb30
{
public:
	void* m_infosData;       // +0x0c
	int m_infosSize;         // +0x10
	int m_infosCapacity;     // +0x14
	hkReal m_tau;            // +0x18
	hkReal m_damping;        // +0x1c
	hkReal m_cfm;            // +0x20
	virtual void getConstraintInfo(hkConstraintInfo_s0108_eb30& info) const;
	virtual void getRuntimeInfo(hkBool_s0108_eb30 wantRuntime, RuntimeInfo& info) const;
};
// ---- items of slice s0108eb30 end

// @ 0x01081500
template <> float hkMath::max2<float>(float a, float b)
{
	return (a > b) ? a : b;    // fcomp / test ah,0x41 / jne: unordered and equal return b
}

// @ 0x01082350
uint32_t hkRotation_s0108_2350::toQuat() const
{
    // Custom ABI: the original takes `out` on the stack but the callee does not pop it (`ret`),
    // so the declaration is argument-less and the first stack slot is read explicitly.
    hkQuaternion_s0108_2350* out = *(hkQuaternion_s0108_2350**)((char*)_AddressOfReturnAddress() + 4);
    const float* m = m_el;
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
    return *(const uint32_t*)&q[2];
}

// @ 0x01082490
uint32_t hkQuaternion_s0108_2350::set(const hkRotation_s0108_2350& r)
{
    toQuatImpl(r);
    return *(uint32_t*)&m_vec[2];
}

// @ 0x010824a0
void hkRotation_s0108_2350::set(const hkQuaternion_s0108_2350& q)
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

// @ 0x010825a0
void hkWorldObject_s0108_2350::addProperty(uint32_t key, hkPropertyValue_s0108_2350 value)
{
    for (int i = 0; i < m_properties.m_size; ++i)
        if (m_properties.m_data[i].m_key == key) return;       // already present: nothing is added
    if (m_properties.m_size == (m_properties.m_capacityAndFlags & HK_ARRAY_FLAG_MASK))
        hkArrayUtil::_reserveMore(&m_properties, sizeof(hkProperty_s0108_2350));
    hkProperty_s0108_2350* e = &m_properties.m_data[m_properties.m_size];
    ++m_properties.m_size;
    e->m_value = value;                                         // m_alignmentPadding is not written
    e->m_key = key;
}

// @ 0x01082600
hkPropertyValue_s0108_2350 hkWorldObject_s0108_2350::editProperty(uint32_t key, hkPropertyValue_s0108_2350 value)
{
    for (int i = 0; i < m_properties.m_size; ++i) {
        if (m_properties.m_data[i].m_key == key) {
            hkPropertyValue_s0108_2350 old = m_properties.m_data[i].m_value;
            m_properties.m_data[i].m_value = value;
            return old;
        }
    }
    hkPropertyValue_s0108_2350 none; none.m_lo = 0; none.m_hi = 0;
    return none;
}

// @ 0x01082660
void hkWorldObject_s0108_2350::calcStatistics(hkStatisticsCollector* c) const
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
hkWorldObject_s0108_2350::hkWorldObject_s0108_2350(int finishLoadedFlag)
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
hkWorldObject_s0108_2350::~hkWorldObject_s0108_2350()
{
    if (m_collidable.m_shape != 0)
        m_collidable.m_shape->removeReference();
    m_properties.quickFree();
    m_collidable.m_collisionEntries.quickFree();
}

// @ 0x01082800
hkWorldObject_s0108_2350::hkWorldObject_s0108_2350(const hkShape_s0108_2350* shape, int broadPhaseType)
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
    m_collidable.m_shape = (hkShape_s0108_2350*)shape;
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

// @ 0x01082890
void hkSolverInfo_s0108_2350::setTauAndDamping(hkReal tau, hkReal damping)
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
    volatile float invDamp = (float)invDampExt;                // rounded store, as the original's fst [esp+8]
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
hkMultithreadConfig::hkMultithreadConfig()
{
    m_splitConstraintSolvingJob = 0;
    m_canCpuTakeSpuTasks = 0;
}

// @ 0x01082910
void hkWorld_updatePhantomOverlap(hkPhantom_s0108_2350* phantom, hkLinkedCollidable_s0108_2350* other, const hkCollisionFilter_s0108_2350* filter)
{
    hkBool_s0108_2350 added = phantom->isOverlappingCollidableAdded(other);
    // the filter call goes through the hkCollidableCollidableFilter sub-object (filter + 8), slot 1
    hkBool_s0108_2350 enabled = static_cast<const hkCollidableCollidableFilter_s0108_2350*>(filter)->isCollisionEnabled(phantom->m_collidable, *other);
    if (enabled)
    {
        if (!added)
        {
            phantom->addOverlappingCollidable(other);
            if (other->m_broadPhaseHandle.m_type == 2)
            {
                hkPhantom_s0108_2350* otherPhantom = (hkPhantom_s0108_2350*)((char*)other + other->m_ownerOffset);   // hkCollidable::getOwner
                otherPhantom->addOverlappingCollidable(&phantom->m_collidable);
            }
        }
    }
    else if (added)
    {
        phantom->removeOverlappingCollidable(other);
        if (other->m_broadPhaseHandle.m_type == 2)
        {
            hkPhantom_s0108_2350* otherPhantom = (hkPhantom_s0108_2350*)((char*)other + other->m_ownerOffset);
            otherPhantom->removeOverlappingCollidable(&phantom->m_collidable);
        }
    }
}

// @ 0x01082990
void hkWorld_s0108_2350::castRay(const hkWorldRayCastInput& input, hkRayHitCollector& output) const
{
    hkWorldRayCaster caster;
    caster.castRay(*m_broadPhase, input, m_collisionFilter, 0, output);
}

// @ 0x010829e0
uint16_t hkNullContactMgr::addContactPoint(int, int, int, int)
{ return 0; }

// @ 0x01082a00
uint32_t hkNullContactMgr::processRequest(int, int, int, int, int, int, int)
{ return 1; }

// @ 0x01082a40
void hkWorld_s0108_2350::removeWorldDeletionListener(hkWorldDeletionListener_s0108_2350* l)
{
    int idx = m_worldDeletionListeners.indexOf(l);
    m_worldDeletionListeners.m_data[idx] = 0;
}

// @ 0x01082a90
int hkWorld_s0108_2350::stepDeltaTime(hkReal physicsDeltaTime)
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
void hkWorld_s0108_2350::linearCast(const hkCollidable* collA, const hkLinearCastInput_s0108_2350& input, hkCdPointCollector& castCollector, hkCdPointCollector* startCollector) const
{
    hkWorldLinearCaster caster;
    caster.m_shapeInputTolerance = 1.1920929e-007f;     // 0x1.0p-23f
    // hkCollisionFilter derives from hkCollidableCollidableFilter as its second base (+8)
    const void* filter = m_collisionFilter ? (const void*)((const char*)m_collisionFilter + 8) : 0;
    caster.linearCast(*m_broadPhase, collA, input, filter, m_collisionInput, m_collisionInput->m_config,
                      castCollector, startCollector);
}

// @ 0x01082bf0
void hkWorld_s0108_2350::executePendingOperations()
{
    hkTimerSplit("TtPendingOps");
    hkWorldOperationQueue* q = m_pendingOperations;
    m_pendingOperationsCount = 0;
    q->executeAllPending();
    hkTimerSplit("Et");
}

// @ 0x01082ca0
int hkWorld_s0108_2350::calcMaxIslandSizeEstimate() const
{
    int maxSize = 0;
    for (int i = m_activeSimulationIslands.m_size - 1; i >= 0; --i) {
        const hkSimulationIsland_s0108_2350* isl = m_activeSimulationIslands.m_data[i];
        int v = ((isl->m_a + isl->m_b * 4 + 0x9c) + isl->m_d) + isl->m_c;
        if (!(maxSize > v)) maxSize = v;
    }
    return maxSize;
}

// @ 0x01082ce0
hkNullContactMgr* hkNullContactMgrFactory::createContactMgr(int, int, int)
{
    return (hkNullContactMgr*)&m_nullContactMgr_slot;
}

// @ 0x01082cf0
void* hkNullContactMgrFactory::deletingDtor(unsigned flags)
{
    // The scalar deleting destructor first installs the two original vtables (this object and
    // the embedded null contact manager at +8), then frees through g_hkMemory when bit 0 is set.
    *(void**)&m_nullContactMgr_slot = (void*)0x013ef094u;
    *(void**)this = (void*)0x013ef094u;
    if (flags & 1)
        hkNullContactMgrFactory::operator delete(this);
    return this;
}

// @ 0x01082d20
hkNullCollisionFilter::hkNullCollisionFilter()
{}

// @ 0x01082df0
void hkWorld_registerContactMgrFactories(hkWorld_s0108_2350* world, hkCollisionDispatcher_s0108_2350* d)
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
hkEntity_s0108_2350* hkWorld_s0108_2350::addEntity(hkEntity_s0108_2350* entity, hkEntityActivation initialActivationState)
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
    hkSweptTransformUtil_setTimeInformation(0.0f, 0.0f, (hkMotion_s0108_2350*)((char*)entity->m_motion + 0x10));
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
uint8_t hkWorld_s0108_2350::removeEntity(hkEntity_s0108_2350* entity)
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
hkPhantom_s0108_2350* hkWorld_s0108_2350::addPhantom(hkPhantom_s0108_2350* phantom)
{
    if (m_lockCountForPhantoms + m_lockCount != 0) {
        hkWorldOperationPrefix op;
        op.m_type = 0xd;
        op.m_object = phantom;
        m_pendingOperations->queuePhantomOperation(op);
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

// @ 0x01083400
void hkWorld_s0108_3400::removePhantom(hkPhantom_s0108_3400* pPhantom)
{
    if (m8c + m90 != 0) {
        hkPendingOp op;
        op.mOpcode = 0xe;
        op.mpPayload = pPhantom;
        mpOpQueue->push(&op);
        return;
    }
    ++m8c;
    hkWorldCallbackUtil_firePhantomRemoved(this, pPhantom);
    pPhantom->firePhantomRemoved();
    hkWorldOperationUtil_removePhantomBP(this, pPhantom);
    int nIndex = mPhantoms.indexOf(pPhantom);
    int nLast = mPhantoms.mSize - 1;
    mPhantoms.mSize = nLast;
    mPhantoms.mpData[nIndex] = mPhantoms.mpData[nLast];
    pPhantom->m08 = 0;
    if (pPhantom->mFlags == 0)
        pPhantom->vf11();
    pPhantom->removeReference();
    --m8c;
    if (m8c == 0) {
        if (m88 != 0 && !m94)
            executePendingOperations();
    }
}

// @ 0x010834f0
void hkWorld_s0108_3400::addCollisionListener(void* p)
{
    mCollisionListeners.pushBack(p);
}

// @ 0x01083530
void hkWorld_s0108_3400::addWorldDeletionListener(void* p)
{
    mWorldDeletionListeners.pushBack(p);
}

// @ 0x01083570
void hkWorld_s0108_3400::calcStatistics(hkStatisticsCollector_s0108_3400* pCollector) const
{
    pCollector->beginObject("hkWorld", 2, this);
    for (int i = mActive.mSize - 1; i >= 0; --i)
        pCollector->addValue("Active", 8, mActive.mpData[i]);
    for (int i = mInactive.mSize - 1; i >= 0; --i)
        pCollector->addValue("Inactive", 8, mInactive.mpData[i]);
    pCollector->addValue("Fixed", 8, mpFixedIsland);
    if (!(mPhantoms.mCapacityAndFlags & 0x80000000))
        pCollector->addArray("PhantomPtrs", 4, mPhantoms.mpData, mPhantoms.mSize << 2,
                             (int)(mPhantoms.mCapacityAndFlags & 0x3fffffff) << 2);
    for (int i = 0; i < mPhantoms.mSize; ++i)
        pCollector->addValue("Phantoms", 2, mPhantoms.mpData[i]);
    pCollector->beginSection("Internal");
    pCollector->addValue("Simulation", 4, mpSimulation);
    if (!(mDirtyIslands.mCapacityAndFlags & 0x80000000))
        pCollector->addArray("DirtyIslPtr", 8, mDirtyIslands.mpData, mDirtyIslands.mSize << 2,
                             (int)(mDirtyIslands.mCapacityAndFlags & 0x3fffffff) << 2);
    pCollector->addValue("MaintnceMgr", 4, mpMaintenanceMgr);
    pCollector->addArray("OpQueue", 4, mpOpQueue, 0x40, 0);
    pCollector->beginSection("OpQueue");
    if ((mpOpQueue->mOpCapacityAndFlags & 0x80000000) == 0)
        pCollector->addArray("Operations", 8, mpOpQueue->mpOps, mpOpQueue->mOpCount * 0x14,
                             (int)(mpOpQueue->mOpCapacityAndFlags & 0x3fffffff) * 0x14);
    pCollector->endSection();
    pCollector->beginSection("Collide");
    pCollector->addValue("Broadphase", 4, mpBroadPhase);
    pCollector->addArray("BpDispatch", 4, mpBpDispatch68, 0x104, 0);
    pCollector->addArray("BpDispatch", 4, mpBpDispatch6c, 0xc, 0);
    pCollector->addArray("BpDispatch", 4, mpBpDispatch70, 8, 0);
    pCollector->addArray("BpDispatch", 4, mpBpDispatch74, 8, 0);
    pCollector->addArray("CollInput", 4, mpCollisionInput, 0x2c, 0);
    pCollector->addValue("Filter", 1, mpCollisionFilter);
    pCollector->addValue("Dispatcher", 4, mpDispatcher);
    pCollector->endSection();
    pCollector->endSection();
    pCollector->beginSection("Listeners");
    if (!(mEntityListeners.mCapacityAndFlags & 0x80000000))
        pCollector->addArray("EntLisPtr", 4, mEntityListeners.mpData, mEntityListeners.mSize << 2,
                             (int)(mEntityListeners.mCapacityAndFlags & 0x3fffffff) << 2);
    if (!(mPhantomListeners.mCapacityAndFlags & 0x80000000))
        pCollector->addArray("PhantLisPtr", 4, mPhantomListeners.mpData, mPhantomListeners.mSize << 2,
                             (int)(mPhantomListeners.mCapacityAndFlags & 0x3fffffff) << 2);
    if (!(mConstraintListeners.mCapacityAndFlags & 0x80000000))
        pCollector->addArray("ConstrLisPtr", 4, mConstraintListeners.mpData,
                             mConstraintListeners.mSize << 2,
                             (int)(mConstraintListeners.mCapacityAndFlags & 0x3fffffff) << 2);
    if (!(mWorldDeletionListeners.mCapacityAndFlags & 0x80000000))
        pCollector->addArray("WldDelLisPtr", 4, mWorldDeletionListeners.mpData,
                             mWorldDeletionListeners.mSize << 2,
                             (int)(mWorldDeletionListeners.mCapacityAndFlags & 0x3fffffff) << 2);
    if (!(mIslandActivationListeners.mCapacityAndFlags & 0x80000000))
        pCollector->addArray("IslActLisPtr", 4, mIslandActivationListeners.mpData,
                             mIslandActivationListeners.mSize << 2,
                             (int)(mIslandActivationListeners.mCapacityAndFlags & 0x3fffffff) << 2);
    if (!(mPostSimulationListeners.mCapacityAndFlags & 0x80000000))
        pCollector->addArray("PstSimLisPtr", 4, mPostSimulationListeners.mpData,
                             mPostSimulationListeners.mSize << 2,
                             (int)(mPostSimulationListeners.mCapacityAndFlags & 0x3fffffff) << 2);
    if (!(mPostIntegrateListeners.mCapacityAndFlags & 0x80000000))
        pCollector->addArray("PstIntLisPtr", 4, mPostIntegrateListeners.mpData,
                             mPostIntegrateListeners.mSize << 2,
                             (int)(mPostIntegrateListeners.mCapacityAndFlags & 0x3fffffff) << 2);
    if (!(mPostCollideListeners.mCapacityAndFlags & 0x80000000))
        pCollector->addArray("PstColLisPtr", 4, mPostCollideListeners.mpData,
                             mPostCollideListeners.mSize << 2,
                             (int)(mPostCollideListeners.mCapacityAndFlags & 0x3fffffff) << 2);
    if (!(mListeners144.mCapacityAndFlags & 0x80000000))
        pCollector->addArray("PstIntLisPtr", 4, mListeners144.mpData, mListeners144.mSize << 2,
                             (int)(mListeners144.mCapacityAndFlags & 0x3fffffff) << 2);
    if (!(mCollisionListeners.mCapacityAndFlags & 0x80000000))
        pCollector->addArray("CollLisPtr", 4, mCollisionListeners.mpData,
                             mCollisionListeners.mSize << 2,
                             (int)(mCollisionListeners.mCapacityAndFlags & 0x3fffffff) << 2);
    pCollector->endSection();
    pCollector->endObject();
}

// @ 0x010839e0
hkWorld_s0108_3400::~hkWorld_s0108_3400()
{
    mpMaintenanceMgr->removeReference();
    if (mpCriticalSectionA != 0) {
        DeleteCriticalSection(mpCriticalSectionA);
        g_hkMemory_s0108_3400->deallocate(mpCriticalSectionA, 0x20, 0x12);
        mpCriticalSectionA = 0;
    }
    mpMaintenanceMgr = 0;
    if (mpCriticalSectionB != 0) {
        DeleteCriticalSection(mpCriticalSectionB);
        g_hkMemory_s0108_3400->deallocate(mpCriticalSectionB, 0x20, 0x12);
        mpCriticalSectionB = 0;
    }
    if (mpBroadPhaseDispatchBase != 0) {
        mpBroadPhaseDispatchBase->removeReference();
        mpBroadPhaseDispatchBase = 0;
    }
    while (mPhantoms.mSize > 0)
        removePhantom(mPhantoms.mpData[0]);
    while (mActive.mSize > 0 && mActive.mpData[0]->mEntityCount != 0)
        removeEntity((hkEntity_s0108_3400*)mActive.mpData[0]->mpEntities);
    while (mInactive.mSize > 0)
        removeEntity((hkEntity_s0108_3400*)mInactive.mpData[0]->mpEntities);
    if (!mB4) {
        hkSimulationIsland_s0108_3400* pLastIsland = mActive.mpData[mActive.mSize - 1];
        hkWorldOperationUtil_removeIslandFromDirtyList(this, pLastIsland);
        if (pLastIsland != 0)
            pLastIsland->vfDestroy(1);
        --mActive.mSize;
    }
    removeEntity(mpFixedRigidBody);
    mpFixedRigidBody = 0;
    while (mpFixedIsland->mEntityCount > 0)
        removeEntity((hkEntity_s0108_3400*)mpFixedIsland->mpEntities);
    hkWorldOperationUtil_removeIslandFromDirtyList(this, mpFixedIsland);
    if (mpFixedIsland != 0)
        mpFixedIsland->vfDestroy(1);
    mpFixedIsland = 0;
    hkWorldFUN_0109f280(this);
    ((hkReferencedObject_s0108_3400*)mpBroadPhase)->removeReference();
    mpBroadPhase = 0;
    mpDispatcher->removeReference();
    mpDispatcher = 0;
    if (mpBpDispatch68 != 0) {
        hkWorldFUN_010cc3f0();
        g_hkMemory_s0108_3400->deallocate(mpBpDispatch68, 0x104, 0x24);
    }
    if (mp168 != 0)
        mp168->removeReference();
    if (mpBpDispatch6c != 0)
        ((hkReferencedObject_s0108_3400*)mpBpDispatch6c)->vfDestroy(1);
    if (mpBpDispatch70 != 0)
        ((hkReferencedObject_s0108_3400*)mpBpDispatch70)->vfDestroy(1);
    if (mpBpDispatch74 != 0)
        ((hkReferencedObject_s0108_3400*)mpBpDispatch74)->vfDestroy(1);
    mpCollisionFilter->removeReference();
    g_hkMemory_s0108_3400->deallocate(mpCollisionInput->mpOwnedChunk, 8, 0x1c);
    g_hkMemory_s0108_3400->deallocate(mpCollisionInput, 0x2c, 0x1c);
    mpSimulation->removeReference();
    releaseOpQueue(mpOpQueue);
    releaseArray(mCollisionListeners.mpData, mCollisionListeners.mSize << 2,
                 mCollisionListeners.mCapacityAndFlags);
    releaseArray(mListeners150.mpData, mListeners150.mSize << 2, mListeners150.mCapacityAndFlags);
    releaseArray(mListeners144.mpData, mListeners144.mSize << 2, mListeners144.mCapacityAndFlags);
    releaseArray(mPostCollideListeners.mpData, mPostCollideListeners.mSize << 2,
                 mPostCollideListeners.mCapacityAndFlags);
    releaseArray(mPostIntegrateListeners.mpData, mPostIntegrateListeners.mSize << 2,
                 mPostIntegrateListeners.mCapacityAndFlags);
    releaseArray(mPostSimulationListeners.mpData, mPostSimulationListeners.mSize << 2,
                 mPostSimulationListeners.mCapacityAndFlags);
    releaseArray(mIslandActivationListeners.mpData, mIslandActivationListeners.mSize << 2,
                 mIslandActivationListeners.mCapacityAndFlags);
    releaseArray(mWorldDeletionListeners.mpData, mWorldDeletionListeners.mSize << 2,
                 mWorldDeletionListeners.mCapacityAndFlags);
    releaseArray(mConstraintListeners.mpData, mConstraintListeners.mSize << 2,
                 mConstraintListeners.mCapacityAndFlags);
    releaseArray(mPhantomListeners.mpData, mPhantomListeners.mSize << 2,
                 mPhantomListeners.mCapacityAndFlags);
    releaseArray(mEntityListeners.mpData, mEntityListeners.mSize << 2,
                 mEntityListeners.mCapacityAndFlags);
    releaseArray(mPhantoms.mpData, mPhantoms.mSize << 2, mPhantoms.mCapacityAndFlags);
    releaseArray(mDirtyIslands.mpData, mDirtyIslands.mSize << 2, mDirtyIslands.mCapacityAndFlags);
    releaseArray(mInactive.mpData, mInactive.mSize << 2, mInactive.mCapacityAndFlags);
    releaseArray(mActive.mpData, mActive.mSize << 2, mActive.mCapacityAndFlags);
}

// @ 0x01083ff0
void hkWorld_s0108_3400::activateRegion(const hkAabb_s0108_3400& aabb)
{
    if (m8c != 0) {
        hkPendingOp op;
        op.mOpcode = 0x1f;
        op.mpPayload = g_hkMemory_s0108_3400->allocate(0x20, 4);
        hkString_memCpy(op.mpPayload, &aabb, 0x20);
        mpOpQueue->push(&op);
        return;
    }
    hkArray_s0108_3400<hkBroadPhaseEntry> result;
    result.mpData = 0;
    result.mSize = 0;
    result.mCapacityAndFlags = 0x80000000;
    mpBroadPhase->query(&aabb, &result);
    if (result.mSize > 0) {
        int i = 0;
        do {
            uchar* pRecord = result.mpData[i].mpRecord;
            hkEntity_s0108_3400* pEntity = (hkEntity_s0108_3400*)(pRecord + ((hkBpRecord*)pRecord)->mEntityOffset);
            if (pEntity->mState == 1) {
                hkEntity_s0108_3400* pActivated = (hkEntity_s0108_3400*)((char*)pEntity + pEntity->mActivateOffset);
                if (pActivated)
                    pActivated->activate();
            }
        } while (++i < result.mSize);
    }
    if (result.mCapacityAndFlags >= 0) {
        hkThreadMemory_s0108_3400* pThreadMemory = (hkThreadMemory_s0108_3400*)TlsGetValue(g_hkThreadMemoryTls);
        pThreadMemory->deallocateChunk(result.mpData, (result.mCapacityAndFlags & 0x3fffffff) * 8, 0x14);
    }
}

// @ 0x01084cf0
void hkWorld_s0108_4cf0::updateCollisionFilterOnPhantom(hkPhantom_s0108_4cf0* phantom, hkUpdateCollectionFilterMode mode)
{
    if (m_lockCount != 0) {
        // Defer: queue a filter-update operation onto the pending-operation list.
        struct Op { u8 m_type; u8 m_pad[3]; hkPhantom_s0108_4cf0* m_phantom; u8 m_mode; };
        Op op;
        op.m_type = 0x13;
        op.m_phantom = phantom;
        op.m_mode = (u8)mode;
        m_pendingOperations->queueOperation(&op);
        return;
    }
    m_lockCount = 1;
    hkTimerBegin("LtUpdateFilterOnPhantom", "broadphase");

    u32 n = (u32)m_broadPhaseQuerySize;
    hkArray_s0108_4cf0<hkBroadPhaseHandlePair> overlaps;
    overlaps.m_size = 0;
    overlaps.m_capacityAndFlags = 0x80000000;
    overlaps.m_data = (hkBroadPhaseHandlePair*)hkStackAlloc(n * 8);
    overlaps.m_capacityAndFlags = (int)(n | 0x80000000u);

    hkBroadPhaseHandle_s0108_4cf0* handle = &phantom->m_collidable.m_handle;
    m_broadPhase->queryAabb(handle, &overlaps);

    hkTimerEnd("StUpdateOverlaps");
    for (int i = 0; i < overlaps.m_size; i++) {
        if (overlaps.m_data[i].m_b != handle)
            worldUpdatePhantomOverlap(m_collisionFilter, overlaps.m_data[i].m_b->owner());
    }

    if (mode != 0) {
        hkTimerEnd("StcollectionFilter");
        phantom->updateShapeCollectionFilter();
    }

    if (--m_lockCount == 0 && m_pendingOperationsCount != 0 &&
        m_blockExecutingPendingOperations == 0)
        executePendingOperations();

    hkTimerEnd("\x01");                       // frame boundary (0x143cd94)
    hkStackRelease(overlaps.m_data);
    hkArrayFree(overlaps.m_data, overlaps.m_capacityAndFlags, 8);
}

// @ 0x01084fa0
void updateCollisionFilterOnEntity( hkWorld_s0108_4cf0* world, hkEntity_s0108_4cf0* entity, hkEntityActivation_s0108_4cf0 activation, u8 collectionMode)
{
    if (world->m_lockCount != 0) {
        struct Op { u8 m_type; u8 m_pad[3]; hkEntity_s0108_4cf0* m_entity; u8 m_activation; u8 m_collection; };
        Op op;
        op.m_type = 0x12;
        op.m_entity = entity;
        op.m_activation = (u8)activation;
        op.m_collection = collectionMode;
        world->m_pendingOperations->queueOperation(&op);
        return;
    }
    hkTimerBegin("LtUpdateFilterOnEntity", "init");
    world->m_lockCount += 1;

    hkBroadPhaseHandlePair overlapBuf[128];           // in-frame 1 KB scratch array
    hkArray_s0108_4cf0<hkBroadPhaseHandlePair> overlaps;
    overlaps.m_data = overlapBuf;
    overlaps.m_size = 0;
    overlaps.m_capacityAndFlags = 0x80000080;

    if (activation == 0) {
        hkTimerEnd("Stbroadphase");
        world->m_broadPhase->queryAabb(&entity->m_collidable.m_handle, &overlaps);
        hkTimerEnd("Stphantom");

        // Drop pairs whose owner is a phantom (broadphase type 2); the rest have their
        // frozen collision filter refreshed, splicing removed entries out of the array.
        for (int i = 0; i < overlaps.m_size; i++) {
            char* owner = (char*)overlaps.m_data[i].m_b->owner();
            if (owner[0x18] == 2) {
                int* collidable = (int*)(owner + *(int*)(owner + 0x10));
                worldUpdatePhantomOverlap(world->m_collisionFilter, owner);
                if (collectionMode != 0)
                    (*(void(**)(void))(*collidable + 0x28))();
                overlaps.m_size -= 1;
                overlaps.m_data[i] = overlaps.m_data[overlaps.m_size];
                i -= 1;
            }
        }

        // Collect this entity's own frozen-collision handles into a pair array and
        // pass it through the phantom-overlap resolver.
        hkBroadPhaseHandlePair pairBuf[128];          // in-frame 1 KB scratch array
        hkArray_s0108_4cf0<hkBroadPhaseHandlePair> pairs;
        pairs.m_data = pairBuf;
        pairs.m_size = 0;
        pairs.m_capacityAndFlags = 0x80000080;
        hkCollisionEntry* entries = (hkCollisionEntry*)entity->m_collisionEntriesData;
        for (int i = 0; i < entity->m_collisionEntriesSize; i++) {
            if ((u32)pairs.m_size == ((u32)pairs.m_capacityAndFlags & 0x3fffffffu))
                hkArrayUtil_reserveGrow(&pairs.m_data, 8);
            int slot = pairs.m_size;
            pairs.m_size += 1;
            hkCollisionEntryTarget* t = (hkCollisionEntryTarget*)entries[i].m_objectA;
            pairs.m_data[slot].m_a = (hkBroadPhaseHandle_s0108_4cf0*)(t->m_handleA + 0x14);
            pairs.m_data[slot].m_b = (hkBroadPhaseHandle_s0108_4cf0*)(t->m_handleB + 0x14);
        }
        FUN_010cc560(&pairs, &overlaps);
        hkArrayFree(pairs.m_data, pairs.m_capacityAndFlags, 8);
    }

    hkTimerEnd("StcheckAgts");
    u32 handleType16 = (u32)*(u16*)((char*)entity + 0x36);
    hkCollisionEntry* entries = (hkCollisionEntry*)entity->m_collisionEntriesData;
    for (int i = 0; i < entity->m_collisionEntriesSize; i++) {
        char* ok = world->m_collisionFilter->m_collidableCollidableFilter->isCollisionEnabled(
                        (char*)&overlaps + 3, (char*)entity + 0x1c, entries[i].m_objectB);
        if (*ok == 0 ||
            *(char*)((u32)*(u16*)((char*)entries[i].m_objectB + 0x1a) + handleType16 * 8 + 0x19d4 +
                     *(int*)((char*)world + 0x80)) == 0) {
            FUN_010a39f0(entries[i].m_objectA);
            i -= 1;
            *(u8*)(*(int*)((char*)entity + 0x5c) + 0x26) = 1;
        } else if (collectionMode == 1) {
            FUN_010fb9c0(entries[i].m_objectA, world->m_collisionInput);
        }
    }

    if (0 < overlaps.m_size) {
        hkTimerEnd("StaddAgts");
        int filter = (world->m_collisionFilter == 0) ? 0 : (int)world->m_collisionFilter + 8;
        FUN_010cc410((int)overlaps.m_data, overlaps.m_size, filter);
    }

    if (--world->m_lockCount == 0 && world->m_pendingOperationsCount != 0 &&
        world->m_blockExecutingPendingOperations == 0)
        world->executePendingOperations();
    hkArrayFree(overlaps.m_data, overlaps.m_capacityAndFlags, 8);
    hkTimerEnd("\x01");                       // frame boundary (0x143cd94)
}

// @ 0x01085490
void hkWorld_s0108_4cf0::addEntityBatch(hkEntity_s0108_4cf0 const* const* entities, int count, hkEntityActivation_s0108_4cf0 activation)
{
    if (count == 0)
        return;
    if (m_lockCount != 0) {
        // Defer: queue an AddEntityBatch operation onto the pending-operation list.
        struct Op { u8 m_type; u8 m_pad[3]; const hkEntity_s0108_4cf0* const* m_entities;
                    u16 m_count; u8 m_activation; };
        Op op;
        op.m_type = 6;
        op.m_entities = entities;
        op.m_count = (u16)count;
        op.m_activation = (u8)activation;
        m_pendingOperations->queueOperation(&op);
        return;
    }
    hkTimerBegin("LtAddEntities", "init");
    m_lockCount += 1;

    // Scratch A: the broadphase handles handed to the broadphase (4 bytes each).
    hkArray_s0108_4cf0<hkBroadPhaseHandle_s0108_4cf0*> handles;
    handles.m_size = 0;
    handles.m_capacityAndFlags = 0x80000000;
    void* handlesMem = hkStackAlloc((u32)count * 4);
    handles.m_data = (hkBroadPhaseHandle_s0108_4cf0**)handlesMem;
    handles.m_capacityAndFlags = count | 0x80000000;

    // Scratch B: the per-entity AABBs (0x20 bytes each).
    hkArray_s0108_4cf0<u8> aabbs;
    aabbs.m_size = 0;
    aabbs.m_capacityAndFlags = 0x80000000;
    void* aabbsMem = hkStackAlloc((u32)count * 0x20);
    aabbs.m_data = (u8*)aabbsMem;
    aabbs.m_capacityAndFlags = count | 0x80000000;

    hkSimulationIsland_s0108_4cf0* island = 0;
    int anyActive = 0;
    if (m_wantSimulationIslands == 0) {
        // Pre-size the fixed island's entity array so the new entities fit.
        hkSimulationIsland_s0108_4cf0* fixed = *m_activeSimulationIslands.m_data;
        int need = fixed->m_entitiesSize + count;
        if ((fixed->m_entitiesCaps & 0x3fffffff) < need) {
            int cap = (fixed->m_entitiesCaps & 0x3fffffff) * 2;
            if (need < cap) need = cap;
            hkArrayUtil_reserveExact(&fixed->m_entities, need, 4);
        }
    } else {
        island = (hkSimulationIsland_s0108_4cf0*)hkMemoryAllocate(0x74, 0x2f);
        *(u16*)((char*)island + 4) = 0x74;
        island = getSimulationIsland();
        if (activation == 1) {
            *(u16*)((char*)island + 0x20) = (u16)m_activeSimulationIslands.m_size;
            *(u8*)((char*)island + 0x26) = 1;
            *(u8*)((char*)island + 0x29) = 1;
            *(u8*)((char*)island + 0x28) = 1;
        } else {
            *(u16*)((char*)island + 0x20) = (u16)m_inactiveSimulationIslands.m_size;
            *(u8*)((char*)island + 0x26) = 1;
            *(u8*)((char*)island + 0x29) = 0;
            *(u8*)((char*)island + 0x28) = 0;
        }
    }

    float tolerance = m_collisionInput->m_tolerance;
    for (int i = 0; i < count; i++) {
        hkEntity_s0108_4cf0* e = (hkEntity_s0108_4cf0*)entities[i];
        u32 uid = ++m_lastEntityUid;
        e->m_uid = uid;
        FUN_01082590();
        if (e->m_collidable.m_motion == 0)
            e->m_collidable.m_motion = e->getMotionState();
        FUN_01209b70(0, 0, (char*)e->m_motion + 0x10);
        e->m_world = this;
        if (e->m_fixed == 0)
            anyActive = 1;
        FUN_010a2250(e);
        if (e->m_collidable.m_owner != 0) {
            int aabbSlot = aabbs.m_size * 0x20;
            aabbs.m_size += 1;
            (*(void(**)(void*, float, u8*))(*(int*)e->m_collidable.m_owner + 0xc))
                (e->m_collidable.m_motion, tolerance * 0.5f, aabbs.m_data + aabbSlot);
            handles.m_data[handles.m_size] = &e->m_collidable.m_handle;
            handles.m_size += 1;
        }
    }

    if (m_wantSimulationIslands != 0) {
        if (anyActive) {
            hkArray_s0108_4cf0<hkSimulationIsland_s0108_4cf0*>* arr =
                (activation != 1) ? &m_inactiveSimulationIslands : &m_activeSimulationIslands;
            if (arr->m_size == (arr->m_capacityAndFlags & 0x3fffffff))
                hkArrayUtil_reserveGrow(arr, 4);
            arr->m_data[arr->m_size] = island;
            arr->m_size += 1;
        } else {
            (*(void(**)(int))*(int*)island)(1);
        }
    }

    // Scratch C: the broadphase handle list the broadphase fills in.
    u32 qn = (u32)m_broadPhaseQuerySize;
    hkArray_s0108_4cf0<hkBroadPhaseHandle_s0108_4cf0*> outHandles;
    outHandles.m_size = 0;
    outHandles.m_capacityAndFlags = 0x80000000;
    outHandles.m_data = (hkBroadPhaseHandle_s0108_4cf0**)hkStackAlloc(qn * 8);
    outHandles.m_capacityAndFlags = (int)(qn | 0x80000000u);

    hkTimerEnd("StBroadphase");
    m_broadPhase->addEntityBatch(&handles, &aabbs, &outHandles);

    hkTimerEnd("StCreateAgents");
    int filter = (m_collisionFilter == 0) ? 0 : (int)m_collisionFilter + 8;
    FUN_010cc410(handles.m_size, handles.m_capacityAndFlags, filter);

    hkTimerEnd("StAddedCb");
    for (int i = 0; i < outHandles.m_size; i++) {
        void* h = outHandles.m_data[i];
        FUN_0109ebc0(this, h);
        FUN_0109e730(h);
    }

    if (--m_lockCount == 0 && m_pendingOperationsCount != 0 &&
        m_blockExecutingPendingOperations == 0)
        executePendingOperations();

    hkTimerEnd("\x01");                       // frame boundary (0x143cd94)
    hkStackRelease(outHandles.m_data);
    hkArrayFree(outHandles.m_data, outHandles.m_capacityAndFlags, 8);
    hkStackRelease(aabbsMem);
    hkArrayFree(aabbsMem, aabbs.m_capacityAndFlags, 0x20);
    hkStackRelease(handlesMem);
    hkArrayFree(handlesMem, handles.m_capacityAndFlags, 4);
}

// @ 0x01088960
void hkRigidMotion::getMotionStateAndVelocities(hkMotion_s0108_8960* motionOut)
{
    hkRigidMotion* out = static_cast<hkRigidMotion*>(motionOut);
    out->m_motionState = m_motionState;
    out->m_linearVelocity[0] = m_linearVelocity[0];
    out->m_linearVelocity[1] = m_linearVelocity[1];
    out->m_linearVelocity[2] = m_linearVelocity[2];
    out->m_linearVelocity[3] = m_linearVelocity[3];
    out->m_angularVelocity[0] = m_angularVelocity[0];
    out->m_angularVelocity[1] = m_angularVelocity[1];
    out->m_angularVelocity[2] = m_angularVelocity[2];
    out->m_angularVelocity[3] = m_angularVelocity[3];
}

// @ 0x010889e0
void hkEntity_s0108_8960::setDeactivator(hkEntityDeactivator_s0108_8960* d)
{
    if (d != 0) d->addReference();
    if (m_deactivator != 0) m_deactivator->removeReference();
    m_deactivator = d;
}

// @ 0x01088a20
void hkEntity_s0108_8960::removeEntityListener(hkEntityListener* l)
{
    int i = m_entityListeners.indexOf(l);
    m_entityListeners.m_data[i] = 0;
}

// @ 0x01088a70
void hkEntity_s0108_8960::removeCollisionListener(hkCollisionListener* l)
{
    int i = m_collisionListeners.indexOf(l);
    m_collisionListeners.m_data[i] = 0;
}

// @ 0x01088ac0
hkBool_s0108_8960 hkEntity_s0108_8960::isActive() const
{
    hkBool_s0108_8960 r;
    if (m_simulationIsland == 0) { r.b = 0; return r; }
    r.b = m_simulationIsland->m_active;
    return r;
}

// @ 0x01088ae0
void hkEntity_s0108_8960::activate()
{
    if (m_simulationIsland != 0 && m_simulationIsland->m_active != 0) return;
    if (m_fixed != 0) return;
    if (m_world != 0)
        hkWorldOperationUtil_s0108_8960::markIslandActive((hkWorld_s0108_8960*)m_world, m_simulationIsland);
}

// @ 0x01088b10
void hkEntity_s0108_8960::deactivate()
{
    if (m_simulationIsland != 0 && m_simulationIsland->m_active != 0)
        hkWorldOperationUtil_s0108_8960::markIslandInactive((hkWorld_s0108_8960*)m_world, m_simulationIsland);
}

// @ 0x01088b30
void hkEntity_s0108_8960::calcStatistics(hkStatisticsCollector_s0108_8960* c) const
{
    c->beginObject("Entity", 2, this);
    hkWorldObject_s0108_8960::calcStatistics(c);
    c->addReferencedObject("Motion", 4, m_motion);
    c->addReferencedObject("Deactivator", 4, m_deactivator);
    if (-1 < m_collisionListeners.m_capacityAndFlags)
        c->addArray("CollisionListnr", 4, m_collisionListeners.m_data,
                    m_collisionListeners.m_size << 2, m_collisionListeners.m_capacityAndFlags << 2);
    if (-1 < m_activationListeners.m_capacityAndFlags)
        c->addArray("ActLstnrPtrs", 4, m_activationListeners.m_data,
                    m_activationListeners.m_size << 2, m_activationListeners.m_capacityAndFlags << 2);
    if (-1 < m_entityListeners.m_capacityAndFlags)
        c->addArray("ListenerPtrs.", 4, m_entityListeners.m_data,
                    m_entityListeners.m_size << 2, m_entityListeners.m_capacityAndFlags << 2);
    c->endObject();
}

// @ 0x01088c20
void hkEntity_s0108_8960::addEntityListener(hkEntityListener* l)
{
    int i = 0;
    if (0 < m_entityListeners.m_size) {
        hkEntityListener** p = m_entityListeners.m_data;
        do {
            if (*p == 0) {
                if (-1 < i) { m_entityListeners.m_data[i] = l; return; }
                break;
            }
            ++i; ++p;
        } while (i < m_entityListeners.m_size);
    }
    m_entityListeners.pushBack(l);
}

// @ 0x01088c90
void hkEntity_s0108_8960::addCollisionListener(hkCollisionListener* l)
{
    int i = 0;
    if (0 < m_collisionListeners.m_size) {
        hkCollisionListener** p = m_collisionListeners.m_data;
        do {
            if (*p == 0) {
                if (-1 < i) { m_collisionListeners.m_data[i] = l; return; }
                break;
            }
            ++i; ++p;
        } while (i < m_collisionListeners.m_size);
    }
    m_collisionListeners.pushBack(l);
}

// @ 0x01088d00
hkEntity_s0108_8960* hkEntity_delete(hkEntity_s0108_8960* e)
{
    if (e != 0)
        return new (e) hkEntity_s0108_8960(hkFinishLoadedObjectFlag(1));
    return (hkEntity_s0108_8960*)1;
}

// @ 0x01088d20
hkEntity_s0108_8960::hkEntity_s0108_8960(const hkShape_s0108_8960* shape)
: hkWorldObject_s0108_8960(shape, 1 /* BROAD_PHASE_ENTITY */)
{
    m_material.m_friction = 0.5f;                 // 0x3f000000
    m_material.m_restitution = 0.4f;              // 0x3ecccccd
    m_constraintsMaster.m_data = 0; m_constraintsMaster.m_size = 0; m_constraintsMaster.m_capacityAndFlags = HK_ARRAY_DONT_DEALLOCATE;
    m_constraintsSlave.m_data = 0;  m_constraintsSlave.m_size = 0;  m_constraintsSlave.m_capacityAndFlags = HK_ARRAY_DONT_DEALLOCATE;
    m_constraintRuntime.m_data = 0; m_constraintRuntime.m_size = 0; m_constraintRuntime.m_capacityAndFlags = HK_ARRAY_DONT_DEALLOCATE;
    m_collisionListeners.m_data = 0; m_collisionListeners.m_size = 0; m_collisionListeners.m_capacityAndFlags = HK_ARRAY_DONT_DEALLOCATE;
    m_activationListeners.m_data = 0; m_activationListeners.m_size = 0; m_activationListeners.m_capacityAndFlags = HK_ARRAY_DONT_DEALLOCATE;
    m_entityListeners.m_data = 0; m_entityListeners.m_size = 0; m_entityListeners.m_capacityAndFlags = HK_ARRAY_DONT_DEALLOCATE;
    m_actions.m_data = 0; m_actions.m_size = 0; m_actions.m_capacityAndFlags = HK_ARRAY_DONT_DEALLOCATE;
    m_simulationIsland = 0;
    m_deactivator = 0;
    m_storageIndex = 0xffff;
    m_uid = 0xffffffffu;
}

// @ 0x01088de0
hkEntity_s0108_8960::~hkEntity_s0108_8960()
{
    hkEntityCallbackUtil_s0108_8960::fireEntityDeleted(this);
    if (m_deactivator != 0) m_deactivator->removeReference();
    m_actions.freeBuffer(4);
    m_entityListeners.freeBuffer(4);
    m_activationListeners.freeBuffer(4);
    m_collisionListeners.freeBuffer(4);
    m_constraintRuntime.freeBuffer(1);
    m_constraintsSlave.freeBuffer(4);
    m_constraintsMaster.freeBuffer(0x1c);
}

// @ 0x01088f70
void hkEntity_s0108_8960::deallocateInternalArrays()
{
    if (m_collidable.m_collisionEntries.m_size == 0)
        m_collidable.m_collisionEntries.clearAndDeallocate(8);
    if (m_constraintsMaster.m_size == 0)
        m_constraintsMaster.clearAndDeallocate(0x1c);
    if (m_constraintsSlave.m_size == 0)
        m_constraintsSlave.clearAndDeallocate(4);
    if (m_constraintRuntime.m_size == 0)
        m_constraintRuntime.clearAndDeallocate(1);

    // listener arrays: only released when every slot is empty
    int i = 0;
    for (; i < m_collisionListeners.m_size; ++i)
        if (m_collisionListeners.m_data[i] != 0) goto L_act;
    m_collisionListeners.clearAndDeallocate(4);
L_act:
    for (i = 0; i < m_activationListeners.m_size; ++i)
        if (m_activationListeners.m_data[i] != 0) goto L_ent;
    m_activationListeners.clearAndDeallocate(4);
L_ent:
    for (i = 0; i < m_entityListeners.m_size; ++i)
        if (m_entityListeners.m_data[i] != 0) goto L_act2;
    m_entityListeners.clearAndDeallocate(4);
L_act2:
    for (i = 0; i < m_actions.m_size; ++i)
        if (m_actions.m_data[i] != 0) return;
    m_actions.clearAndDeallocate(4);
}

// @ 0x01089280
void hkConstraintConstructionKit::begin(hkGenericConstraintData* data)
{
    m_scheme = data->getScheme();                // FUN_008dc790: lea eax,[ecx+0xc]
    m_constraint = data;
    m_stiffnessReference = 0;
    m_dampingReference = 0;
    m_linearDofSpecifiedA[0] = 0; m_linearDofSpecifiedA[1] = 0; m_linearDofSpecifiedA[2] = 0;
    m_linearDofSpecifiedB[0] = 0; m_linearDofSpecifiedB[1] = 0; m_linearDofSpecifiedB[2] = 0;
    m_pivotSpecifiedA = 0;
    m_pivotSpecifiedB = 0;
    m_angularBasisSpecifiedA = 0;
    m_angularBasisSpecifiedB = 0;
}

// @ 0x010892c0
int hkConstraintConstructionKit::setLinearDofWorld(const hkVector4_s0108_8960& dof, int index)
{
    m_scheme->m_commands.pushBack(CMD_SET_LINEAR_DOF_WORLD);
    m_scheme->m_commands.pushBack(index);
    int dataIndex = m_scheme->m_data.m_size;
    hkVector4_s0108_8960 v; copyVec4(&v, &dof);
    m_scheme->m_data.pushBack(v);
    m_linearDofSpecifiedA[index] = 1;
    m_linearDofSpecifiedB[index] = 1;
    return dataIndex;
}

// @ 0x01089390
void hkConstraintConstructionKit::constrainLinearDof(int index)
{
    m_scheme->m_commands.pushBack(CMD_CONSTRAIN_LINEAR_DOF);
    m_scheme->m_commands.pushBack(index);
    hkConstraintInfo& info = m_scheme->m_info;
    info.m_sizeOfSchemas += 4;
    info.m_sizeOfJacobians += 0x30;
    info.m_numSolverResults += 1;
}

// @ 0x01089420
void hkConstraintConstructionKit::setAngularBasisABodyFrame()
{
    m_scheme->m_commands.pushBack(CMD_SET_BASIS_A_BODY_FRAME);
    m_angularBasisSpecifiedA = 1;
}

// @ 0x01089460
void hkConstraintConstructionKit::setAngularBasisBBodyFrame()
{
    m_scheme->m_commands.pushBack(CMD_SET_BASIS_B_BODY_FRAME);
    m_angularBasisSpecifiedB = 1;
}

// @ 0x010894a0
void hkConstraintConstructionKit::constrainToAngularDof(int index)
{
    m_scheme->m_commands.pushBack(CMD_CONSTRAIN_TO_ANGULAR_DOF);
    m_scheme->m_commands.pushBack(index);
    hkConstraintInfo* info = &m_scheme->m_info;
    info->m_sizeOfSchemas += 4;
    info->m_sizeOfJacobians += 0x20;
    info->m_numSolverResults += 1;
    info = &m_scheme->m_info;
    info->m_sizeOfJacobians += 0x20;
    info->m_sizeOfSchemas += 4;
    info->m_numSolverResults += 1;
}

// @ 0x01089550
int hkConstraintConstructionKit::setPivotA(const hkVector4_s0108_8960& pivot)
{
    m_scheme->m_commands.pushBack(CMD_SET_PIVOT_A);
    int dataIndex = m_scheme->m_data.m_size;
    hkVector4_s0108_8960 v; copyVec4(&v, &pivot);
    m_scheme->m_data.pushBack(v);
    m_pivotSpecifiedA = 1;
    return dataIndex;
}

// @ 0x010895e0
int hkConstraintConstructionKit::setPivotB(const hkVector4_s0108_8960& pivot)
{
    m_scheme->m_commands.pushBack(CMD_SET_PIVOT_B);
    int dataIndex = m_scheme->m_data.m_size;
    hkVector4_s0108_8960 v; copyVec4(&v, &pivot);
    m_scheme->m_data.pushBack(v);
    m_pivotSpecifiedB = 1;
    return dataIndex;
}

// @ 0x01089670
void hkConstraintConstructionKit::end()
{
    m_scheme->m_commands.pushBack(CMD_END);
}

// @ 0x010896b0
void hkGenericConstraintData::getConstraintInfo(hkConstraintInfo& out) const
{
    out.m_maxSizeOfJacobians = 0; out.m_sizeOfJacobians = 0; out.m_sizeOfSchemas = 0; out.m_numSolverResults = 0;
    out.m_maxSizeOfJacobians = m_scheme.m_info.m_maxSizeOfJacobians;
    out.m_sizeOfJacobians = m_scheme.m_info.m_sizeOfJacobians;
    out.m_sizeOfSchemas = m_scheme.m_info.m_sizeOfSchemas;
    out.m_numSolverResults = m_scheme.m_info.m_numSolverResults;
}

// @ 0x010896e0
void hkGenericConstraintData::getRuntimeInfo(hkBool_s0108_8960, RuntimeInfo& infoOut) const
{
    int n = m_scheme.m_info.m_numSolverResults;
    infoOut.m_numSolverResults = n;
    infoOut.m_sizeOfExternalRuntime = n << 3;
}

// @ 0x01089700
void __stdcall hkGenericConstraint_buildLinearBasisWorld(int, int, int, hkGenericConstraintParameters* p, const hkConstraintQueryIn* in, hkConstraintQueryOut* out)
{
    hk1dLinearBilateralConstraintInfo info;
    for (int i = 0; i < 4; ++i) { info.m_pivotA[i] = p->m_vec[i]; info.m_pivotB[i] = p->m_vec[4 + i]; }
    info.m_constrainedDofW[3] = 0;
    info.m_constrainedDofW[2] = 0;
    info.m_constrainedDofW[1] = 0;
    info.m_constrainedDofW[0] = 0x3f800000;            // 1.0f
    hk1dLinearBilateralConstraintBuildJacobian(&info, in, out);
    info.m_constrainedDofW[0] = 0;
    info.m_constrainedDofW[1] = 0x3f800000;
    hk1dLinearBilateralConstraintBuildJacobian(&info, in, out);
    info.m_constrainedDofW[1] = 0;
    info.m_constrainedDofW[2] = 0x3f800000;
    hk1dLinearBilateralConstraintBuildJacobian(&info, in, out);
    p->m_numJacobians = p->m_numJacobians + 3;
}

// @ 0x010897d0
void __stdcall hkGenericConstraint_buildLinearDof(int** commands, int, int, hkGenericConstraintParameters* p, const hkConstraintQueryIn* in, hkConstraintQueryOut* out)
{
    *commands += 1;
    int idx = **commands;
    const uint32_t* dof = (const uint32_t*)p + (idx + 2) * 4;
    hk1dLinearBilateralConstraintInfo info;
    info.m_constrainedDofW[0] = dof[0]; info.m_constrainedDofW[1] = dof[1];
    info.m_constrainedDofW[2] = dof[2]; info.m_constrainedDofW[3] = dof[3];
    for (int i = 0; i < 4; ++i) { info.m_pivotA[i] = p->m_vec[i]; info.m_pivotB[i] = p->m_vec[4 + i]; }
    hk1dLinearBilateralConstraintBuildJacobian(&info, in, out);
    p->m_numJacobians = p->m_numJacobians + 1;
}

// @ 0x01089870
float hkGenericConstraint_calcAngle(int axis, const hkVector4_s0108_8960* rows)
{
    int a = s_mod3[axis + 1];
    int b = s_mod3[axis + 2];
    const hkVector4_s0108_8960& w = rows[a + 5];
    const hkVector4_s0108_8960& v1 = rows[b + 8];
    const hkVector4_s0108_8960& v2 = rows[a + 8];
    // X87-PRECISION: each dot product accumulates ((z*z' + y*y') + x*x') in extended precision and is
    // rounded to float only once, when stored to the stack slot before the call.
    float d1 = (float)((((hkX87Real)v1.z * w.z) + ((hkX87Real)v1.y * w.y)) + ((hkX87Real)v1.x * w.x));
    float d2 = (float)((((hkX87Real)v2.z * w.z) + ((hkX87Real)v2.y * w.y)) + ((hkX87Real)v2.x * w.x));
    return hkMath::atan2fApproximation(d1, d2);
}

// @ 0x010898f0
void hkGenericConstraintData_s0108_98f0::constrainToAngularW( int*& currentCommand, hkVector4_s0108_98f0*& currentData, const hkGenericConstraintDataScheme_s0108_98f0& scheme, hkGenericConstraintDataParameters& vars, const hkConstraintQueryIn& in, hkConstraintQueryOut_s0108_98f0& out ) const
{
    const int axis = *++currentCommand;

    hk1dAngularBilateralInfo info;
    info.m_axisB = vars.m_angularBasisAw[ s_mod3[axis + 1] ];
    info.m_axisA = vars.m_angularBasisAw[ s_mod3[axis + 2] ];
    info.m_axisW = vars.m_angularBasisBw[ axis ];
    hk1dAngularBilateralConstraintBuildJacobian( &info, &in, &out );

    hkVector4_s0108_98f0 negB;
    negB.x = -info.m_axisB.x;
    negB.y = -info.m_axisB.y;
    negB.z = -info.m_axisB.z;
    negB.w = -info.m_axisB.w;
    info.m_axisB = info.m_axisA;
    info.m_axisA = negB;
    hk1dAngularBilateralConstraintBuildJacobian( &info, &in, &out );

    vars.m_currentResult += 2;
}

// @ 0x01089a20
void hkGenericConstraintData_s0108_98f0::constrainAllAngularW( int*& currentCommand, hkVector4_s0108_98f0*& currentData, const hkGenericConstraintDataScheme_s0108_98f0& scheme, hkGenericConstraintDataParameters& vars, const hkConstraintQueryIn& in, hkConstraintQueryOut_s0108_98f0& out ) const
{
    hk1dAngularBilateralInfo info;

    info.m_axisA = vars.m_angularBasisAw[0];
    info.m_axisW = vars.m_angularBasisBw[1];
    info.m_axisB = vars.m_angularBasisAw[2];
    hk1dAngularBilateralConstraintBuildJacobian( &info, &in, &out );

    info.m_axisA = vars.m_angularBasisAw[1];
    info.m_axisW = vars.m_angularBasisBw[2];
    info.m_axisB = vars.m_angularBasisAw[0];
    hk1dAngularBilateralConstraintBuildJacobian( &info, &in, &out );

    info.m_axisA = vars.m_angularBasisAw[2];
    info.m_axisW = vars.m_angularBasisBw[0];
    info.m_axisB = vars.m_angularBasisAw[1];
    hk1dAngularBilateralConstraintBuildJacobian( &info, &in, &out );

    vars.m_currentResult += 3;
}

// @ 0x01089ba0
void hkGenericConstraintData_s0108_98f0::setLinearLimitW( int*& currentCommand, hkVector4_s0108_98f0*& currentData, const hkGenericConstraintDataScheme_s0108_98f0& scheme, hkGenericConstraintDataParameters& vars, const hkConstraintQueryIn& in, hkConstraintQueryOut_s0108_98f0& out ) const
{
    const int dof = *++currentCommand;

    hk1dLinearLimitInfo info;
    info.m_dofW   = vars.m_linearBasisW[ dof ];
    info.m_pivotA = vars.m_pivotAw;
    info.m_pivotB = vars.m_pivotBw;

    const hkVector4_s0108_98f0* limits = currentData++;
    info.m_min = limits->x;
    info.m_max = limits->y;

    hk1dLinearLimitBuildJacobian( &info, &in, &out );
    vars.m_currentResult += 1;
}

// @ 0x01089c60
void hkGenericConstraintData_s0108_98f0::setAngularLimitW( int*& currentCommand, hkVector4_s0108_98f0*& currentData, const hkGenericConstraintDataScheme_s0108_98f0& scheme, hkGenericConstraintDataParameters& vars, const hkConstraintQueryIn& in, hkConstraintQueryOut_s0108_98f0& out ) const
{
    const int axis = *++currentCommand;

    hk1dAngularLimitInfo info;
    info.m_tau   = 0.5f;
    info.m_axis  = vars.m_angularBasisAw[ axis ];

    info.m_angle = hkGenericConstraint_calcAngle( axis, (const hkVector4_s0108_98f0*)&vars );

    hkVector4_s0108_98f0* limits = currentData++;
    info.m_min = limits->x;
    info.m_max = limits->y;

    if ( info.m_angle < 0.0f && limits->z > 0.0f && 3.1415927f < limits->z - info.m_angle )
    {
        info.m_angle = info.m_angle + 6.2831855f;
    }
    if ( info.m_angle > 0.0f && limits->z < 0.0f && 3.1415927f < info.m_angle - limits->z )
    {
        info.m_angle = info.m_angle - 6.2831855f;
    }
    limits->z = info.m_angle;

    hk1dAngularLimitBuildJacobian( &info, &in, &out );
    vars.m_currentResult += 1;
}

// @ 0x01089d70
void hkGenericConstraintData_s0108_98f0::setConeLimitW( int*& currentCommand, hkVector4_s0108_98f0*& currentData, const hkGenericConstraintDataScheme_s0108_98f0& scheme, hkGenericConstraintDataParameters& vars, const hkConstraintQueryIn& in, hkConstraintQueryOut_s0108_98f0& out ) const
{
    const int axis = *++currentCommand;

    const float* aw = (const float*)&vars.m_angularBasisAw[ axis ];
    const float fVar2 = aw[0];
    const float fVar3 = aw[1];
    const float fVar4 = aw[2];
    const float* bw = (const float*)&vars.m_angularBasisBw[ axis ];
    const float fVar5 = bw[0];
    const float fVar6 = bw[1];
    const float fVar7 = bw[2];

    hk1dAngularLimitInfo info;
    info.m_tau = 0.5f;
    info.m_axis.x = fVar7 * fVar3 - fVar6 * fVar4;
    info.m_axis.y = fVar4 * fVar5 - fVar7 * fVar2;
    info.m_axis.z = fVar6 * fVar2 - fVar3 * fVar5;

    float fVar9 = info.m_axis.x * info.m_axis.x
                + ( info.m_axis.y * info.m_axis.y + info.m_axis.z * info.m_axis.z );
    if ( 1.1920929e-07f <= fVar9 )
    {
        float fVar1;
        if ( fVar9 == 0.0f ) fVar1 = 0.0f;
        else                 fVar1 = 1.0f / sqrtf( fVar9 );

        info.m_axis.x = fVar1 * info.m_axis.x;

        hkVector4_s0108_98f0* data = currentData++;
        info.m_axis.y = info.m_axis.y * fVar1;
        info.m_axis.z = info.m_axis.z * fVar1;
        info.m_axis.w = fVar1 * 0.0f;

        info.m_angle = fVar5 * fVar2 + ( fVar6 * fVar3 + fVar4 * fVar7 );
        info.m_min = data->x;
        info.m_max = data->y;

        hk1dAngularLimitBuildJacobian( &info, &in, &out );
        vars.m_currentResult += 1;
    }
}

// @ 0x01089f10
void hkGenericConstraintData_s0108_98f0::setTwistLimitW( int*& currentCommand, hkVector4_s0108_98f0*& currentData, const hkGenericConstraintDataScheme_s0108_98f0& scheme, hkGenericConstraintDataParameters& vars, const hkConstraintQueryIn& in, hkConstraintQueryOut_s0108_98f0& out ) const
{
    const int axisA = *++currentCommand;
    const int axisB = *++currentCommand;

    hk1dAngularLimitInfo info;
    info.m_tau = 0.5f;

    hkInternalConstraintUtils::calcRelativeAngle( vars.m_angularBasisAw[ axisA ],
                                                 vars.m_angularBasisBw[ axisA ],
                                                 vars.m_angularBasisAw[ axisB ],
                                                 vars.m_angularBasisBw[ axisB ],
                                                 info.m_axis, info.m_angle );

    hkVector4_s0108_98f0* limits = currentData++;
    info.m_min = limits->x;
    info.m_max = limits->y;

    hk1dAngularLimitBuildJacobian( &info, &in, &out );
    vars.m_currentResult += 1;
}

// @ 0x01089fc0
void hkGenericConstraintData_s0108_98f0::setAngularMotorW( int*& currentCommand, hkVector4_s0108_98f0*& currentData, hkGenericConstraintDataScheme_s0108_98f0& scheme, hkGenericConstraintDataParameters& vars, const hkConstraintQueryIn& in, hkConstraintQueryOut_s0108_98f0& out ) const
{
    const int axis = *++currentCommand;
    const char* solverResults = in.m_solverResults;

    hkVector4_s0108_98f0* data = currentData++;
    const int   turns       = *(const int*)&data->z;
    const float targetAngle = data->y;
    const int   motorIndex  = (int)data->z;

    hkConstraintMotor* motor = (hkConstraintMotor*)scheme.m_motors.m_data[ motorIndex ];

    const float* aw  = (const float*)&vars.m_angularBasisAw[ s_mod3[axis + 1] ];
    const float* bwY = (const float*)&vars.m_angularBasisBw[ s_mod3[axis + 2] ];
    const float* bwX = (const float*)&vars.m_angularBasisBw[ s_mod3[axis + 1] ];

    // Angle between the two constrained body axes, relative to the reference axis.
    float angle = hkMath::atan2fApproximation(
            -( bwY[0] * aw[0] + ( bwY[1] * aw[1] + bwY[2] * aw[2] ) ),
            -( bwX[0] * aw[0] + ( bwX[1] * aw[1] + bwX[2] * aw[2] ) ) );
    angle = angle + 3.1415927f;

    int newTurns = turns;
    if ( -3.1415927f <= angle - targetAngle )
    {
        if ( 3.1415927f < angle - targetAngle ) newTurns = (int)( (float)turns - 1.0f );
    }
    else
    {
        newTurns = (int)( (float)turns + 1.0f );
    }

    data->y = angle;
    *(int*)&data->z = newTurns;
    data->w = 0.0f;

    if ( motor != 0 )
    {
        hk1dAngularMotorInfo info;
        info.m_solver  = 0;
        info.m_solver2 = 0;

        hk1dAngularVelocityMotorBeginJacobian( &vars.m_angularBasisAw[ axis ], &in, out.m_constraintInternal,
                                               &info );
        info.m_in      = &in;
        info.m_solver  = solverResults + vars.m_currentResult * 8;
        info.m_solver2 = solverResults + 4 + vars.m_currentResult * 8;
        info.m_targetAngle = -( (float)newTurns * 6.2831855f + angle );
        info.m_unknown = 0;

        motor->update( &info, info.m_scratch );
        hk1dAngularVelocityMotorCommitJacobian( &info.m_unknown, &in, angle );
    }
    vars.m_currentResult += 1;
}

// @ 0x0108a180
void hkGenericConstraintData_s0108_98f0::setLinearMotorW( int*& currentCommand, hkVector4_s0108_98f0*& currentData, hkGenericConstraintDataScheme_s0108_98f0& scheme, hkGenericConstraintDataParameters& vars, const hkConstraintQueryIn& in, hkConstraintQueryOut_s0108_98f0& out ) const
{
    const int dof = *++currentCommand;
    const char* solverResults = in.m_solverResults;

    const hkVector4_s0108_98f0* data = currentData++;
    const int motorIndex = (int)data->y;

    hkConstraintMotor* motor = (hkConstraintMotor*)scheme.m_motors.m_data[ motorIndex ];

    hk1dLinearMotorInfo info;
    info.m_dofW = vars.m_linearBasisW[ dof ];

    const float fVar4 = info.m_dofW.x * ( vars.m_pivotAw.x - vars.m_pivotBw.x );
    const float fVar6 = info.m_dofW.y * ( vars.m_pivotAw.y - vars.m_pivotBw.y );
    const float fVar5 = info.m_dofW.z * ( vars.m_pivotAw.z - vars.m_pivotBw.z );

    if ( motor != 0 )
    {
        info.m_solver  = 0;
        info.m_solver2 = 0;

        hk1dLinearVelocityMotorBeginJacobian( &info.m_dofW, &vars.m_pivotBw, &in, out.m_constraintInternal,
                                              &info.m_constraintInternal );
        info.m_targetVelocity = -( fVar4 + ( fVar6 + fVar5 ) );
        info.m_solver  = solverResults + vars.m_currentResult * 8;
        info.m_solver2 = solverResults + 4 + vars.m_currentResult * 8;
        info.m_unknown = 0;
        info.m_in      = &in;

        motor->update( &info.m_constraintInternal, info.m_scratch );
        hk1dLinearVelocityMotorCommitJacobian( &info.m_unknown, &in, &out );
    }
    vars.m_currentResult += 1;
}

// @ 0x0108a2b0
void hkGenericConstraintData_s0108_98f0::setAngularFrictionW( int*& currentCommand, hkVector4_s0108_98f0*& currentData, const hkGenericConstraintDataScheme_s0108_98f0& scheme, hkGenericConstraintDataParameters& vars, const hkConstraintQueryIn& in, hkConstraintQueryOut_s0108_98f0& out ) const
{
    const int axis = *++currentCommand;

    hk1dAngularFrictionInfo info;
    info.m_solver     = in.m_solverResults;
    info.m_axis       = &vars.m_angularBasisAw[ axis ];
    info.m_maxImpulse = currentData++->x;
    info.m_solver     = info.m_solver + vars.m_currentResult * 8;
    info.m_useVelocity = 1;

    hk1dAngularFrictionBuildJacobian( &info, &in, &out );
    vars.m_currentResult += 1;
}

// @ 0x0108a330
void hkGenericConstraintData_s0108_98f0::setLinearFrictionW( int*& currentCommand, hkVector4_s0108_98f0*& currentData, const hkGenericConstraintDataScheme_s0108_98f0& scheme, hkGenericConstraintDataParameters& vars, const hkConstraintQueryIn& in, hkConstraintQueryOut_s0108_98f0& out ) const
{
    const int dof = *++currentCommand;

    hk1dLinearFrictionInfo info;
    info.m_solver     = in.m_solverResults;
    info.m_deltaPivot.x = vars.m_pivotAw.x - vars.m_pivotBw.x;
    info.m_dofW = vars.m_linearBasisW[ dof ];
    info.m_deltaPivot.y = vars.m_pivotAw.y - vars.m_pivotBw.y;
    info.m_deltaPivot.z = vars.m_pivotAw.z - vars.m_pivotBw.z;
    info.m_deltaPivot.w = vars.m_pivotAw.w - vars.m_pivotBw.w;
    info.m_maxImpulse = currentData++->x;
    info.m_solver     = info.m_solver + vars.m_currentResult * 8;
    hk1dLinearFrictionBuildJacobian( &info, &in, &out );
    vars.m_currentResult += 1;
}

// @ 0x0108a3f0
void hkGenericConstraintData_s0108_a3f0::buildJacobianInternal( const hkGenericConstraintDataScheme_s0108_a3f0& scheme, const hkConstraintQueryIn_s0108_a3f0& in, hkConstraintQueryOut_s0108_a3f0& out )
{
    hkConstraintQueryIn_s0108_a3f0 inCopy = in;
    hkGenericConstraintDataParameters_s0108_a3f0 vars;

    int*       currentCommand = scheme.m_commands.m_data;
    hkVector4_s0108_a3f0* currentData    = scheme.m_data.m_data;
    void**     currentModifier = (void**)scheme.m_modifiers.m_data;
    float      strength = 0.0f;

    for ( ;; ) {
        switch ( *currentCommand ) {
        case 0:
            return;
        case 1:
            vars.m_pivotAw.setTransformedPos( inCopy.m_transformA, currentData );
            ++currentData;
            ++currentCommand;
            break;
        case 2:
            vars.m_pivotBw.setTransformedPos( inCopy.m_transformB, currentData );
            ++currentData;
            ++currentCommand;
            break;
        case 3:
        case 4: {
            const hkMatrix3_s0108_a3f0* base = ( *currentCommand == 3 ) ? (const hkMatrix3_s0108_a3f0*)inCopy.m_transformA
                                                             : (const hkMatrix3_s0108_a3f0*)inCopy.m_transformB;
            const int idx = currentCommand[ 1 ];
            const hkVector4_s0108_a3f0 v = *currentData;
            hkVector4_s0108_a3f0& t = vars.m_linearBasisW[ idx ];
            t.x = v.x * base->m_col0.x + v.y * base->m_col1.x + v.z * base->m_col2.x;
            t.y = v.x * base->m_col0.y + v.y * base->m_col1.y + v.z * base->m_col2.y;
            t.z = v.x * base->m_col0.z + v.y * base->m_col1.z + v.z * base->m_col2.z;
            t.w = 0.0f;
            ++currentData;
            currentCommand += 2;
            break;
        }
        case 5: {
            const int idx = currentCommand[ 1 ];
            vars.m_linearBasisW[ idx ] = *currentData;
            ++currentData;
            currentCommand += 2;
            break;
        }
        case 6:
            buildLinearDof( currentCommand, currentData, scheme, vars, inCopy, out );
            ++currentCommand;
            break;
        case 7:
            buildLinearBasisWorld( currentCommand, currentData, scheme, vars, inCopy, out );
            ++currentCommand;
            break;
        case 8:
            ((hkMatrix3_s0108_a3f0*)&vars.m_linearBasisW[0])->setMul( *(const hkMatrix3_s0108_a3f0*)inCopy.m_transformA,
                                                           *(const hkMatrix3_s0108_a3f0*)currentData );
            currentData += 3;
            ++currentCommand;
            break;
        case 9:
            ((hkMatrix3_s0108_a3f0*)&vars.m_linearBasisW[0])->setMul( *(const hkMatrix3_s0108_a3f0*)inCopy.m_transformB,
                                                           *(const hkMatrix3_s0108_a3f0*)currentData );
            currentData += 3;
            ++currentCommand;
            break;
        case 10:
            hkMatrix3_setIdentity( (hkMatrix3_s0108_a3f0*)&vars.m_angularBasisAw[0] );
            ++currentCommand;
            break;
        case 11:
            hkMatrix3_setIdentity( (hkMatrix3_s0108_a3f0*)&vars.m_angularBasisBw[0] );
            ++currentCommand;
            break;
        case 12:
            constrainToAngularW( currentCommand, currentData, scheme, vars, inCopy, out );
            ++currentCommand;
            break;
        case 13:
            constrainAllAngularW( currentCommand, currentData, scheme, vars, inCopy, out );
            ++currentCommand;
            break;
        case 14:
            setAngularMotorW( currentCommand, currentData,
                              const_cast<hkGenericConstraintDataScheme_s0108_a3f0&>(scheme), vars, inCopy, out );
            ++currentCommand;
            break;
        case 15:
            setLinearMotorW( currentCommand, currentData,
                             const_cast<hkGenericConstraintDataScheme_s0108_a3f0&>(scheme), vars, inCopy, out );
            ++currentCommand;
            break;
        case 16:
            setLinearLimitW( currentCommand, currentData, scheme, vars, inCopy, out );
            ++currentCommand;
            break;
        case 17:
            setAngularLimitW( currentCommand, currentData, scheme, vars, inCopy, out );
            ++currentCommand;
            break;
        case 18:
            setConeLimitW( currentCommand, currentData, scheme, vars, inCopy, out );
            ++currentCommand;
            break;
        case 19:
            setTwistLimitW( currentCommand, currentData, scheme, vars, inCopy, out );
            ++currentCommand;
            break;
        case 20:
            setAngularFrictionW( currentCommand, currentData, scheme, vars, inCopy, out );
            ++currentCommand;
            break;
        case 21:
            setLinearFrictionW( currentCommand, currentData, scheme, vars, inCopy, out );
            ++currentCommand;
            break;
        case 22:
            strength = strength * currentData->x;
            ++currentData;
            ++currentCommand;
            break;
        case 23:
            strength = inCopy.m_rhsFactor;
            ++currentCommand;
            break;
        case 24:
            ( *(ModifierFn)*currentModifier )( &vars, currentCommand[ 1 ] );
            currentCommand += 2;
            ++currentModifier;
            break;
        case 25: {
            const float f = ( *(ModifierFloatFn)*currentModifier )( &vars, currentCommand[ 1 ] );
            hkReplacePreviousRhs( f, &inCopy, &out, 1 );
            currentCommand += 2;
            ++currentModifier;
            break;
        }
        default:
            ++currentCommand;
            break;
        }
    }
}

// @ 0x0108aa40
hkGenericConstraintData_s0108_a3f0::hkGenericConstraintData_s0108_a3f0()
{
    m_scheme.m_info.m_sizeOfSchemas = 24;
}

// @ 0x0108aaa0
hkGenericConstraintData_s0108_a3f0::~hkGenericConstraintData_s0108_a3f0()
{
    for ( int i = 0; i < m_scheme.m_motors.m_size; ++i ) {
        hkReferencedObject_s0108_a3f0* motor = (hkReferencedObject_s0108_a3f0*)m_scheme.m_motors.m_data[ i ];
        if ( motor->m_memSizeAndFlags != 0 ) {
            if ( --motor->m_referenceCount == 0 )
                delete motor;
        }
    }
}

// @ 0x0108aaf0
void hkGenericConstraintData_s0108_a3f0::buildJacobian( const hkConstraintQueryIn_s0108_a3f0& in, hkConstraintQueryOut_s0108_a3f0& out )
{
    hkBeginConstraints( &in, &out, (int)(size_t)in.m_solverResults, 8 );
    buildJacobianInternal( m_scheme, in, out );
}

// @ 0x0108aba0
void hkConstraintChainInstance::entityRemovedCallback( hkEntity_s0108_a3f0* entity )
{
    hkWorld_s0108_a3f0* world = (hkWorld_s0108_a3f0*)entity->m_world;
    world->m_refCount++;
    world->removeActionImmediately( m_action );
    hkWorldOperationUtil_removeConstraintImmediately( world, this, 1 );
    if ( --world->m_refCount == 0 && world->m_pending != 0 && world->m_flag94 == 0 )
        world->executePendingOperations();
}

// @ 0x0108ac30
void hkConstraintChainInstance::addEntity( void* entity )
{
    hkReferencedObject_s0108_a3f0* ref = (hkReferencedObject_s0108_a3f0*)entity;
    const int size = m_chainedEntities.m_size;
    if ( size < 2 && m_entities[ size ] == 0 ) {
        m_entities[ size ] = entity;
        ref->addReference();
    }
    hkArray_s0108_a3f0<void*>& chain = m_chainedEntities;
    if ( chain.m_size == ( chain.m_capacityAndFlags & 0x3fffffff ) )
        hkArrayUtil_reserveMore( &chain, 4 );
    chain.m_data[ chain.m_size ] = entity;
    ++chain.m_size;
    ref->addReference();
}

// @ 0x0108acb0
hkConstraintChainInstance::hkConstraintChainInstance( void* data )
: hkConstraintInstance_s0108_a3f0( 1 )
{
    m_data = data;
    if ( *(unsigned short*)( (char*)data + 4 ) != 0 )
        ++*(short*)( (char*)data + 6 );
    m_entities[ 0 ] = 0;
    m_entities[ 1 ] = 0;

    void* mem = hkMemory_s0108_a3f0::s_instance->allocate( 0x1c, 0x26 );
    hkConstraintChainInstanceAction* action =
        new (mem) hkConstraintChainInstanceAction( this );
    m_action = action;
}

// @ 0x0108ad30
hkConstraintChainInstance::~hkConstraintChainInstance()
{
    for ( int i = 0; i < m_chainedEntities.m_size; ++i )
        ( (hkWorldObject_s0108_a3f0*)m_chainedEntities.m_data[ i ] )->removeReference();

    hkAction_s0108_a3f0* action = m_action;
    if ( action->m_memSizeAndFlags != 0 ) {
        if ( --action->m_referenceCount == 0 )
            delete action;
    }
}

// @ 0x0108aec0
void hkLimitedHingeConstraintData::setInBodySpace( const hkVector4_s0108_a3f0& pivotA, const hkVector4_s0108_a3f0& pivotB, const hkVector4_s0108_a3f0& axleA, const hkVector4_s0108_a3f0& axleB, const hkVector4_s0108_a3f0& referenceA, const hkVector4_s0108_a3f0& referenceB )
{
    m_basisA.m_pivot = pivotA;
    m_basisB.m_pivot = pivotB;
    m_basisA.m_axle  = axleA;
    m_basisB.m_axle  = axleB;

    hkVector4_normalize3( m_basisA.m_axle );
    hkVector4_normalize3( m_basisB.m_axle );

    m_basisA.m_perpToAxle2 = referenceA;
    hkVector4_normalize3( m_basisA.m_perpToAxle2 );
    m_basisA.m_perpToAxle1.w = 0.0f;
    m_basisA.m_perpToAxle1.x = m_basisA.m_axle.z * m_basisA.m_perpToAxle2.y
                             - m_basisA.m_perpToAxle2.z * m_basisA.m_axle.y;
    m_basisA.m_perpToAxle1.y = m_basisA.m_perpToAxle2.z * m_basisA.m_axle.x
                             - m_basisA.m_axle.z * m_basisA.m_perpToAxle2.x;
    m_basisA.m_perpToAxle1.z = m_basisA.m_axle.y * m_basisA.m_perpToAxle2.x
                             - m_basisA.m_axle.x * m_basisA.m_perpToAxle2.y;

    m_basisB.m_perp2FreeAxis = referenceB;
    hkVector4_normalize3( m_basisB.m_perp2FreeAxis );
}

// @ 0x0108b150
hkBool_s0108_a3f0 hkLimitedHingeConstraintData::isValid() const
{
    const float eps  = 1.0e-5f;
    const float fmax = 6.2831855f;

    float dotA = m_basisA.m_perpToAxle2.x * m_basisA.m_perpToAxle1.x
               + m_basisA.m_perpToAxle2.y * m_basisA.m_perpToAxle1.y
               + m_basisA.m_perpToAxle2.z * m_basisA.m_perpToAxle1.z;
    if ( fabsf( dotA ) >= eps )
        goto fail;

    float dotB = m_basisB.m_perp2FreeAxis.x * m_basisB.m_axle.x
               + m_basisB.m_perp2FreeAxis.y * m_basisB.m_axle.y
               + m_basisB.m_perp2FreeAxis.z * m_basisB.m_axle.z;
    if ( fabsf( dotB ) >= eps )
        goto fail;

    if ( fabsf( m_basisA.m_perpToAxle1.x * m_basisA.m_perpToAxle1.x
              + m_basisA.m_perpToAxle1.y * m_basisA.m_perpToAxle1.y
              + m_basisA.m_perpToAxle1.z * m_basisA.m_perpToAxle1.z - 1.0f ) >= eps )
        goto fail;

    if ( fabsf( m_basisA.m_perpToAxle2.x * m_basisA.m_perpToAxle2.x
              + m_basisA.m_perpToAxle2.y * m_basisA.m_perpToAxle2.y
              + m_basisA.m_perpToAxle2.z * m_basisA.m_perpToAxle2.z - 1.0f ) >= eps )
        goto fail;

    if ( fabsf( m_basisB.m_axle.x * m_basisB.m_axle.x
              + m_basisB.m_axle.y * m_basisB.m_axle.y
              + m_basisB.m_axle.z * m_basisB.m_axle.z - 1.0f ) >= eps )
        goto fail;

    {
        float len2 = m_basisA.m_axle.x * m_basisA.m_axle.x
                   + m_basisA.m_axle.y * m_basisA.m_axle.y
                   + m_basisA.m_axle.z * m_basisA.m_axle.z;
        if ( hkMath_equal( len2, 1.0f, 1.0e-5f ).m_bool == 0 )
            goto fail;
    }

    {
        float span;
        if ( ( m_minAngle < 0.0f ) == ( m_minAngle == 0.0f )
          || ( m_maxAngle < 0.0f ) == ( m_maxAngle == 0.0f ) )
            span = m_maxAngle - m_minAngle;
        else
            span = fabsf( m_minAngle ) + m_maxAngle;
        if ( span <= fmax )
            return hkBool_s0108_a3f0( (char)1 );
    }

fail:
    return hkBool_s0108_a3f0( (char)0 );
}

// @ 0x0108b9f0
void hkBallSocketChainData::getConstraintInfo(hkConstraintInfo_s0108_b2f0& info) const
{
	info.m_maxSizeOfSchema = 0;
	info.m_sizeOfSchemas = 0;
	info.m_numSolverResults = 0x18;
	info.m_numSolverElemTemps = 0;

	const int32_t n = m_chain.m_size;
	info.m_numSolverResults = n * 4 + 0x2c;
	info.m_sizeOfSchemas = n * 0x130 + 0x10;
	info.m_numSolverElemTemps = n * 3;
}

// @ 0x0108ba30
void hkBallSocketChainData::getRuntimeInfo(bool allow, hkConstraintRuntimeInfo& info) const
{
	if (allow) {
		info.m_numSolverElemTemps = m_chain.m_size * 3;
		info.m_numSolverResults = info.m_numSolverElemTemps * 8;
	} else {
		info.m_numSolverElemTemps = 0;
		info.m_numSolverResults = 0;
	}
}

// @ 0x0108ba70
void hkBallSocketChainData::addConstraint(const hkVector4_s0108_b2f0& pivotA, const hkVector4_s0108_b2f0& pivotB)
{
	hkBallSocketChainArray* pChain = &m_chain;
	if (pChain->m_size == (pChain->m_capacityAndFlags & 0x3fffffff))
		hkArrayUtil_reserveMore(pChain, 0x20);

	hkBallSocketConstraintInfo* pSlot = &pChain->m_data[pChain->m_size];
	++pChain->m_size;
	pSlot->m_pivotA = pivotA;
	pSlot->m_pivotB = pivotB;
}

// @ 0x0108bb00
hkBallSocketChainData::hkBallSocketChainData()
{
	m_chain.m_data = 0;
	m_chain.m_size = 0;
	m_chain.m_capacityAndFlags = 0x80000000;
	m_tau = 0.6f;
	m_damping = 1.0f;
	m_maxImpulse = 1.1920929e-8f;
	m_maxFriction = 0.1f;
}

// @ 0x0108bb40
void operator delete(void* block)
{
		hkBallSocketChainData* pData = (hkBallSocketChainData*)block;
		g_hkMemoryInstance->deallocate(block, pData->m_memSizeAndFlags, 0x29);
	}

// @ 0x0108bec0
hkConstraintInstance_s0108_b2f0::~hkConstraintInstance_s0108_b2f0()
{
	if (m_entityA)
		m_entityA->removeReference();
	if (m_entityB)
		m_entityB->removeReference();
	if (m_constraintData)
		m_constraintData->removeReference();
}

// @ 0x0108bf10
hkConstraintInstance_s0108_b2f0::hkConstraintInstance_s0108_b2f0(hkEntity_s0108_b2f0* entityA, hkEntity_s0108_b2f0* entityB, hkConstraintData_s0108_b2f0* data, ConstraintPriority priority)
{
	m_world = 0;
	m_constraintData = data;
	m_priority = (uint8_t)priority;
	m_wantRuntime = 0;
	m_dynamics = 0;
	m_field20 = 0;
	m_runtime = 0;
	m_entityA = entityA;
	m_entityB = entityB;
	m_entityA->addReference();
	if (m_entityB)
		m_entityB->addReference();
	if (m_constraintData->m_memSizeAndFlags)
		++m_constraintData->m_referenceCount;
}

// @ 0x0108bf80
hkConstraintInstance_s0108_b2f0::hkConstraintInstance_s0108_b2f0(ConstraintPriority priority)
{
	m_world = 0;
	m_priority = (uint8_t)priority;
	m_wantRuntime = 0;
	m_dynamics = 0;
	m_field20 = 0;
	m_runtime = 0;
}

// @ 0x0108bfb0
void hkConstraintInstance_s0108_b2f0::setPriority(ConstraintPriority priority)
{
	m_priority = (uint8_t)priority;
	if (m_runtime)
		m_runtime->m_priority = (uint8_t)priority;
}

// @ 0x0108bff0
void hkConstraintInstance_s0108_b2f0::fixNullEntities()
{
	hkEntity_s0108_b2f0** pEntity = &m_entityA;
	for (int i = 2; i != 0; --i) {
		hkEntity_s0108_b2f0* cur = *pEntity;
		if (!cur) {
			hkEntity_s0108_b2f0* other = (hkEntity_s0108_b2f0*)((uint32_t)m_entityA ^ (uint32_t)m_entityB
			                              ^ (uint32_t)cur);
			if (other) {
				hkWorld_s0108_b2f0* world = other->m_world;
				if (world) {
					*pEntity = world->m_fixedBody;
					(*pEntity)->addReference();
				}
			}
		}
		++pEntity;
	}
}

// @ 0x0108c0b0
int32_t hkPhantom_s0108_b2f0::fireCollidableAdded(const hkCollidable_s0108_b2f0* collidable)
{
	hkCollidableAddedEvent event;
	event.m_phantom = this;
	event.m_collidable = collidable;
	event.m_accept = 0;

	for (int i = m_numListeners - 1; i >= 0; --i) {
		hkPhantomListener_s0108_b2f0* pListener = m_listeners[i];
		if (pListener)
			pListener->collidableAdded(event);
	}
	return event.m_accept;
}

// @ 0x0108c100
void hkPhantom_s0108_b2f0::fireCollidableRemoved(const hkCollidable_s0108_b2f0* collidable, bool removed)
{
	hkCollidableRemovedEvent event;
	event.m_collidable = collidable;
	event.m_phantom = this;
	event.m_removed = removed;

	for (int i = m_numListeners - 1; i >= 0; --i) {
		hkPhantomListener_s0108_b2f0* pListener = m_listeners[i];
		if (pListener)
			pListener->collidableRemoved(event);
	}
}

// @ 0x0108e080
hkPhantom_s0108_e080* hkAabbPhantom::clone() const
{
    hkMemory_s0108_e080* mem = hkMemory_instance;
    hkAabbPhantom* obj = (hkAabbPhantom*)mem->allocate(0xa0, 0x2e);
    obj->m_memSizeAndFlags = 0xa0;

    hkAabbPhantom* e = (hkAabbPhantom*)::new ((hkPlacement*)obj) hkAabbPhantom(
        *(const hkAabb_s0108_e080*)((const char*)this + 0x70),
        *(const uint32_t*)((const char*)this + 0x38));

    // ---- m_overlapListeners (+0x58) ----
    if ((e->m_overlapListeners.m_capacityAndFlags & 0x3fffffff) < m_overlapListeners.m_size) {
        if (e->m_overlapListeners.m_capacityAndFlags >= 0) {
            void* tls = TlsGetValue(g_hkThreadMemoryTls_s0108_e080);
            ((hkThreadMemory_s0108_e080*)tls)->deallocateChunk(e->m_overlapListeners.m_data,
                                           (e->m_overlapListeners.m_capacityAndFlags & 0x3fffffff) << 2, 0x14);
        }
        void* tls = TlsGetValue(g_hkThreadMemoryTls_s0108_e080);
        e->m_overlapListeners.m_data = (void**)((hkThreadMemory_s0108_e080*)tls)->allocateChunk(m_overlapListeners.m_size << 2, 0x14);
        e->m_overlapListeners.m_capacityAndFlags =
            (e->m_overlapListeners.m_capacityAndFlags & 0x40000000) | m_overlapListeners.m_size;
    }
    e->m_overlapListeners.m_size = m_overlapListeners.m_size;
    for (int i = 0; i < m_overlapListeners.m_size; ++i)
        e->m_overlapListeners.m_data[i] = m_overlapListeners.m_data[i];

    // ---- m_phantomListeners (+0x64) ----
    if ((e->m_phantomListeners.m_capacityAndFlags & 0x3fffffff) < m_phantomListeners.m_size) {
        if (e->m_phantomListeners.m_capacityAndFlags >= 0) {
            void* tls = TlsGetValue(g_hkThreadMemoryTls_s0108_e080);
            ((hkThreadMemory_s0108_e080*)tls)->deallocateChunk(e->m_phantomListeners.m_data,
                                           (e->m_phantomListeners.m_capacityAndFlags & 0x3fffffff) << 2, 0x14);
        }
        void* tls = TlsGetValue(g_hkThreadMemoryTls_s0108_e080);
        e->m_phantomListeners.m_data = (void**)((hkThreadMemory_s0108_e080*)tls)->allocateChunk(m_phantomListeners.m_size << 2, 0x14);
        e->m_phantomListeners.m_capacityAndFlags =
            (e->m_phantomListeners.m_capacityAndFlags & 0x40000000) | m_phantomListeners.m_size;
    }
    e->m_phantomListeners.m_size = m_phantomListeners.m_size;
    for (int i = 0; i < m_phantomListeners.m_size; ++i)
        e->m_phantomListeners.m_data[i] = m_phantomListeners.m_data[i];

    hkWorldObject_copyProperties(e, this);
    return e;
}

// @ 0x0108e1d0
void hkAabbPhantom::deallocateInternalArrays()
{
    if (m_overlappingCollidables.m_size == 0) {
        if (m_overlappingCollidables.m_capacityAndFlags >= 0) {
            void* tls = TlsGetValue(g_hkThreadMemoryTls_s0108_e080);
            ((hkThreadMemory_s0108_e080*)tls)->deallocateChunk(m_overlappingCollidables.m_data,
                                           (m_overlappingCollidables.m_capacityAndFlags & 0x3fffffff) << 2, 0x14);
        }
        m_overlappingCollidables.m_data = 0;
        m_overlappingCollidables.m_size = 0;
        m_overlappingCollidables.m_capacityAndFlags =
            (int32_t)((m_overlappingCollidables.m_capacityAndFlags & 0xc0000000u) | 0x80000000u);
    }
    hkPhantom_s0108_e080::deallocateInternalArrays();
}

// @ 0x0108e250
void* hkAabbPhantom::scalarDeletingDestructor(unsigned int flags)
{
    setVtable((void*)0x0149e51c);
    if (m_overlappingCollidables.m_capacityAndFlags >= 0) {
        void* tls = TlsGetValue(g_hkThreadMemoryTls_s0108_e080);
        ((hkThreadMemory_s0108_e080*)tls)->deallocateChunk(m_overlappingCollidables.m_data,
                                       (m_overlappingCollidables.m_capacityAndFlags & 0x3fffffff) << 2, 0x14);
    }
    this->~hkAabbPhantom();
    if (flags & 1) {
        hkMemory_s0108_e080* mem = hkMemory_instance;
        mem->deallocate(this, m_memSizeAndFlags, 0x2e);
    }
    return this;
}

// @ 0x0108e2c0
void hkPhantom_s0108_e080::overlapRemoveNulls()
{
    for (int i = m_overlapListeners.m_size - 1; i >= 0; --i) {
        if (m_overlapListeners.m_data[i] == 0) {
            int n = --m_overlapListeners.m_size;
            for (int j = i; j < n; ++j)
                m_overlapListeners.m_data[j] = m_overlapListeners.m_data[j + 1];
        }
    }
}

// @ 0x0108e300
void hkPhantom_s0108_e080::firePhantomRemoved()
{
    for (int i = m_phantomListeners.m_size - 1; i >= 0; --i) {
        void* l = m_phantomListeners.m_data[i];
        if (l != 0)
            ((hkPhantomListener_s0108_e080*)l)->phantomRemoved(this);
    }
    for (int i = m_phantomListeners.m_size - 1; i >= 0; --i) {
        if (m_phantomListeners.m_data[i] == 0) {
            int n = --m_phantomListeners.m_size;
            for (int j = i; j < n; ++j, n = m_phantomListeners.m_size)
                m_phantomListeners.m_data[j] = m_phantomListeners.m_data[j + 1];
        }
    }
}

// @ 0x0108e370
void hkPhantom_s0108_e080::firePhantomAdded()
{
    for (int i = m_phantomListeners.m_size - 1; i >= 0; --i) {
        void* l = m_phantomListeners.m_data[i];
        if (l != 0)
            ((hkPhantomListener_s0108_e080*)l)->phantomAdded(this);
    }
    for (int i = m_phantomListeners.m_size - 1; i >= 0; --i) {
        if (m_phantomListeners.m_data[i] == 0) {
            int n = --m_phantomListeners.m_size;
            for (int j = i; j < n; ++j, n = m_phantomListeners.m_size)
                m_phantomListeners.m_data[j] = m_phantomListeners.m_data[j + 1];
        }
    }
}

// @ 0x0108e3e0
void hkPhantom_s0108_e080::firePhantomShapeSet()
{
    for (int i = m_phantomListeners.m_size - 1; i >= 0; --i) {
        void* l = m_phantomListeners.m_data[i];
        if (l != 0)
            ((hkPhantomListener_s0108_e080*)l)->phantomShapeSet(this);
    }
    for (int i = m_phantomListeners.m_size - 1; i >= 0; --i) {
        if (m_phantomListeners.m_data[i] == 0) {
            int n = --m_phantomListeners.m_size;
            for (int j = i; j < n; ++j, n = m_phantomListeners.m_size)
                m_phantomListeners.m_data[j] = m_phantomListeners.m_data[j + 1];
        }
    }
}

// @ 0x0108e450
void hkPhantom_s0108_e080::overlapRemoveAtValue(void* value)
{
    int idx = 0;
    if (m_overlapListeners.m_size > 0) {
        void** q = m_overlapListeners.m_data;
        do {
            if (*q == value)
                goto found;
            ++idx;
            ++q;
        } while (idx < m_overlapListeners.m_size);
    }
    idx = -1;
found:
    {
        int n = --m_overlapListeners.m_size;
        if (idx < n) {
            for (int j = idx; j < n; ++j)
                m_overlapListeners.m_data[j] = m_overlapListeners.m_data[j + 1];
        }
    }
}

// @ 0x0108e4a0
void hkPhantom_s0108_e080::overlapPushBack(void* value)
{
    hkArray_s0108_e080<void*>* a = &m_overlapListeners;
    if (a->m_size == (a->m_capacityAndFlags & 0x3fffffff))
        hkArrayUtil_reserveMore(a, 4);
    a->m_data[a->m_size] = value;
    ++a->m_size;
}

// @ 0x0108e4e0
void hkAabbPhantom::calcStatistics(hkStatisticsCollector_s0108_e080* c) const
{
    ((const hkWorldObjectMember*)this)->calcStatistics(c);
    if (m_overlapListeners.m_capacityAndFlags >= 0)
        c->addArray("OvrlapLisPtr", 4, m_overlapListeners.m_data,
                    m_overlapListeners.m_size << 2,
                    (m_overlapListeners.m_capacityAndFlags & 0x3fffffff) << 2);
    if (m_phantomListeners.m_capacityAndFlags >= 0)
        c->addArray("PhantmLisPtr", 4, m_phantomListeners.m_data,
                    m_phantomListeners.m_size << 2,
                    (m_phantomListeners.m_capacityAndFlags & 0x3fffffff) << 2);
}

// @ 0x0108e5e0
void hkPhantom_s0108_e080::deallocateInternalArrays()
{
    if (m_overlapListeners.m_size == 0) {
        if (m_overlapListeners.m_capacityAndFlags >= 0) {
            void* tls = TlsGetValue(g_hkThreadMemoryTls_s0108_e080);
            ((hkThreadMemory_s0108_e080*)tls)->deallocateChunk(m_overlapListeners.m_data,
                                           (m_overlapListeners.m_capacityAndFlags & 0x3fffffff) << 2, 0x14);
        }
        int cap = (int32_t)((m_overlapListeners.m_capacityAndFlags & 0xc0000000u) | 0x80000000u);
        m_overlapListeners.m_data = 0;
        m_overlapListeners.m_size = 0;
        m_overlapListeners.m_capacityAndFlags = cap;
    }
    if (m_phantomListeners.m_size == 0) {
        if (m_phantomListeners.m_capacityAndFlags >= 0) {
            void* tls = TlsGetValue(g_hkThreadMemoryTls_s0108_e080);
            ((hkThreadMemory_s0108_e080*)tls)->deallocateChunk(m_phantomListeners.m_data,
                                           (m_phantomListeners.m_capacityAndFlags & 0x3fffffff) << 2, 0x14);
        }
        int cap = (int32_t)((m_phantomListeners.m_capacityAndFlags & 0xc0000000u) | 0x80000000u);
        m_phantomListeners.m_data = 0;
        m_phantomListeners.m_size = 0;
        m_phantomListeners.m_capacityAndFlags = cap;
    }
}

// @ 0x0108e940
void hkWheelConstraintData::getRuntimeInfo(chkHkBool valid, hkConstraintRuntimeInfo_s0108_e080* info) const
{
    if ((int)valid) {
        info->m_sizeOfAll  = 6;
        info->m_sizeOfThis = 0x30;
        return;
    }
    info->m_sizeOfAll  = 0;
    info->m_sizeOfThis = 0;
}

// @ 0x0108f320
void hkVelocityConstraintMotor::calcMotorData(const hkConstraintMotorInput& in, hkConstraintMotorOutput& out)
{
	if (m_useVelocityTargetFromConstraintTargets)
		out.m_targetVelocity = (in.m_positionError + in.m_deltaTarget) * in.m_stepInfo->m_frameInvDeltaTime;
	else
		out.m_targetVelocity = m_velocityTarget;

	out.m_targetPosition = in.m_lastResults.m_internalSolverData;
	out.m_tau = m_tau;
	out.m_damping = m_tau;
	out.m_minForce = m_maxForce;
	out.m_maxForce = m_minForce;
}

// @ 0x0108f390
hkConstraintMotor_s0108_eb30* hkVelocityConstraintMotor::clone() const
{
	hkVelocityConstraintMotor* p = (hkVelocityConstraintMotor*)hkMemory_s0108_eb30::s_instance->allocateChunk(0x1c, 0x29);
	*(const void**)p = (const void*)0x014a1808;
	p->m_memSizeAndFlags = 0x1c;
	p->m_referenceCount = 1;
	p->m_minForce = m_minForce;
	p->m_maxForce = m_maxForce;
	*(const void**)p = (const void*)0x014a181c;
	p->m_tau = m_tau;
	p->m_velocityTarget = m_velocityTarget;
	p->m_useVelocityTargetFromConstraintTargets = m_useVelocityTargetFromConstraintTargets;
	return p;
}

// @ 0x0108f8d0
void hkStiffSpringConstraintData::getRuntimeInfo(hkBool_s0108_eb30 wantRuntime, RuntimeInfo& info) const
{
	if (wantRuntime.m_bool) {
		info.m_numSolverResults = 1;
		info.m_size = 8;
	} else {
		info.m_numSolverResults = 0;
		info.m_size = 0;
	}
}

// @ 0x0108f900
hkBool_s0108_eb30 hkStiffSpringConstraintData::isValid() const
{
	hkBool_s0108_eb30 result;
	if (m_springLength <= 0.0f) {
		result.m_bool = 0;
		return result;
	}
	result.m_bool = 1;
	return result;
}

// @ 0x0108fae0
void hkStiffSpringChainData::getRuntimeInfo(hkBool_s0108_eb30 wantRuntime, RuntimeInfo& info) const
{
	if (wantRuntime.m_bool) {
		int n = m_infosSize;
		info.m_numSolverResults = n;
		info.m_size = n * 8;
	} else {
		info.m_numSolverResults = 0;
		info.m_size = 0;
	}
}
