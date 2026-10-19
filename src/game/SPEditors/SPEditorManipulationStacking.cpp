// src/game/SPEditors/SPEditorManipulationStacking.cpp -- migrated from slice(s) s01082350 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorManipulationStacking.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" unsigned __int64 __rdtsc();
extern unsigned long g_hkThreadMemoryTlsIndex;       // 0x16e4174
#include <stddef.h>
#include <math.h>
#pragma intrinsic(__rdtsc)

// ---- items of slice s01082350 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef float hkReal;
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
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
struct hkReferencedObject_s0108_2350 {
    uint16_t m_memSizeAndFlags;
    uint16_t m_referenceCount;
    hkReferencedObject_s0108_2350() : m_referenceCount(1) {}
    virtual ~hkReferencedObject_s0108_2350() {}
    virtual void calcStatistics(struct hkStatisticsCollector* c) const {}
    void addReference() { if (m_memSizeAndFlags != 0) m_referenceCount = (uint16_t)(m_referenceCount + 1); }   // 0x01082590
    void removeReference() {
        if (m_memSizeAndFlags != 0) {
            m_referenceCount = (uint16_t)(m_referenceCount - 1);
            if (m_referenceCount == 0) delete this;
        }
    }
};
struct hkShape_s0108_2350 : hkReferencedObject_s0108_2350 {};
struct hkStatisticsCollector {
virtual void s0();
virtual void s1();
    virtual void addArray(const char* name, int elemSize, const void* ptr, int usedBytes, int allocatedBytes);   // +8
    virtual void addReferencedObject(const char* name, int a, const void* obj);                                    // +0xc
};
struct hkPropertyValue_s0108_2350 { uint32_t m_lo, m_hi; };       // 64-bit payload
struct hkProperty_s0108_2350 { uint32_t m_key; uint32_t m_alignmentPadding; hkPropertyValue_s0108_2350 m_value; };   // 0x10
struct hkTypedBroadPhaseHandle_s0108_2350 { uint32_t m_id; uint8_t m_type; int8_t m_ownerOffset; int16_t m_objectQualityType; uint32_t m_collisionFilterInfo; };  // 0xc
struct hkLinkedCollidable_s0108_2350 {                            // size 0x30
    hkShape_s0108_2350* m_shape;                                  // +0x00 (hkCdBody)
    uint32_t m_shapeKey;                               // +0x04
    void* m_motion;                                    // +0x08
    void* m_parent;                                    // +0x0c
    int m_ownerOffset;                                 // +0x10
    hkTypedBroadPhaseHandle_s0108_2350 m_broadPhaseHandle;        // +0x14
    float m_allowedPenetrationDepth;                   // +0x20
    hkArray<void*[2]> m_collisionEntries;              // +0x24  (8-byte entries)
};
struct hkMultiThreadLock_s0108_2350 { uint32_t m_threadId; int m_lockCount; };
class hkBool_s0108_2350
{
public:
    hkBool_s0108_2350(bool b) : m_bool(b ? 1 : 0) {}
    operator bool() const { return m_bool != 0; }
private:
    char m_bool;
};
struct hkWorldObject_s0108_2350 : hkReferencedObject_s0108_2350 {
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
struct hkEntity_s0108_2350; struct hkPhantom_s0108_2350; struct hkWorld_s0108_2350; struct hkSimulationIsland_s0108_2350;
struct hkBroadPhase; struct hkCollisionFilter_s0108_2350; struct hkProcessCollisionInput_s0108_2350; struct hkRayHitCollector;
struct hkCdPointCollector; struct hkCollidable; struct hkWorldRayCastInput; struct hkLinearCastInput_s0108_2350;
struct hkWorldMemoryWatchDog { char pad[8]; int m_memoryLimit; virtual void s0(); virtual void s1(); virtual void freeMemory(hkWorld_s0108_2350* w); };
struct hkWorldOperationQueue;
struct hkWorldDeletionListener_s0108_2350;
struct hkSimulation { virtual void s0(); virtual void s1(); virtual int stepDeltaTime(hkWorld_s0108_2350* w, hkReal physicsDeltaTime, hkReal frameDeltaTime); };
enum hkEntityActivation { HK_ENTITY_ACTIVATION_DO_NOT_ACTIVATE = 0, HK_ENTITY_ACTIVATION_DO_ACTIVATE = 1 };
struct hkWorldOperationBase { uint8_t m_type; void* m_object; int m_arg; };   // queued op record
struct hkWorld_s0108_2350 : hkReferencedObject_s0108_2350 {
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
struct hkMotion_s0108_2350 { char pad[0x10]; char m_motionState[1]; };    // hkMotionState starts at +0x10
struct hkEntity_s0108_2350 : hkWorldObject_s0108_2350 {
    hkMotion_s0108_2350* m_motion;                                // +0x58
    uint32_t pad5c[28];                                // +0x5c..0xcb
    uint32_t m_uid;                                    // +0xcc
};
struct hkPhantom_s0108_2350 : hkWorldObject_s0108_2350 {
    void firePhantomAdded();                           // 0x0108e370
    // hkPhantom virtual slots after the four hkWorldObject ones (used by hkWorld_updatePhantomOverlap, 0x01082910)
    virtual void slot5() = 0;
    virtual void addOverlappingCollidable(hkLinkedCollidable_s0108_2350* c) = 0;                          // slot 6 (+0x18)
    virtual hkBool_s0108_2350 isOverlappingCollidableAdded(const hkLinkedCollidable_s0108_2350* c) = 0;              // slot 7 (+0x1c)
    virtual void removeOverlappingCollidable(hkLinkedCollidable_s0108_2350* c) = 0;                       // slot 8 (+0x20)
};
struct hkWorldOperationQueue {
    void queueOperation(const hkWorldOperationBase& op);                // 0x109afe0
    void executeAllPending();                                           // 0x109b490
};
struct hkWorldLinearCaster {
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
struct hkSimulationIsland_s0108_2350 {
    uint32_t pad[3];
    int m_c;      // +0x0c
    int m_d;      // +0x10
    int m_a;      // +0x14
    int m_b;      // +0x18
};
struct hkCollidableCollidableFilter_s0108_2350
{
    virtual void s0();
    virtual hkBool_s0108_2350 isCollisionEnabled(const struct hkLinkedCollidable_s0108_2350& a, const struct hkLinkedCollidable_s0108_2350& b) const = 0;   // slot 1
};
struct hkShapeCollectionFilter_s0108_2350 {
    virtual void s0();
    virtual hkBool_s0108_2350 isCollisionEnabled(const void* a, const void* b, const void* bContainer, uint32_t bKey) const = 0;
};
struct hkRayShapeCollectionFilter_s0108_2350 {
    virtual void s0();
    virtual hkBool_s0108_2350 isCollisionEnabled(const void* input, const void* collection, uint32_t key) const = 0;
};
struct hkRayCollidableFilter_s0108_2350 {
    virtual void s0();
    virtual hkBool_s0108_2350 isCollisionEnabled(const void* input, const hkLinkedCollidable_s0108_2350& c) const = 0;
};
struct hkCollisionFilter_s0108_2350 : hkReferencedObject_s0108_2350, hkCollidableCollidableFilter_s0108_2350, hkShapeCollectionFilter_s0108_2350,
                           hkRayShapeCollectionFilter_s0108_2350, hkRayCollidableFilter_s0108_2350
{
    hkCollisionFilter_s0108_2350() {}
};
// ---- items of slice s01082350 end

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
