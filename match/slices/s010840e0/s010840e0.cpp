// Slice s010840e0: 0x010840E0, Havok 3.1.0 hkWorld::hkWorld(const hkWorldCinfo& info, unsigned int sdkVersion)
// (".\world\hkWorld.cpp"). The card's name SP::cSPEditorVerbIcon::InitializeSize is a wrong dev-PDB carry-over:
// the body builds every hkWorld subsystem and warns about a Havok version mismatch (0x765c).
// Flags: /O2 /MD /Gy /TP /GS- /fp:fast (x87 floats, no EH frame, no stack cookie for the 512-byte warning buffer;
// the hkRigidBodyCinfo local forces the 16-byte aligned frame).
//
// Member offsets follow the 2008 dev PDB layout of hkWorld (0x2f0 bytes), which the retail code matches.
// Names of classes without a PDB/havok_names entry are Claude-coined and marked "(coined)".
#include <stddef.h>
#include <math.h>
#include "types.h"

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int __stdcall InitializeCriticalSectionAndSpinCount(void* cs, unsigned long spin);

typedef float hkReal;
typedef uint16_t hkUint16;
typedef uint8_t hkUint8;
typedef int8_t hkInt8;

#define HK_REAL_EPSILON 1.192092896e-07f
#define HK_REAL_MAX 3.40282e+38f

enum
{
    HK_MEMORY_CLASS_BASE = 0x5,         // (coined: class of the 0x2c thread-memory request)
    HK_MEMORY_CLASS_CDINFO = 0xc,
    HK_MEMORY_CLASS_SIMULATION = 0x12,
    HK_MEMORY_CLASS_COLLIDE = 0x1c,
    HK_MEMORY_CLASS_BROAD_PHASE = 0x1e,
    HK_MEMORY_CLASS_CONTACT = 0x1f,
    HK_MEMORY_CLASS_AGENT = 0x24,
    HK_MEMORY_CLASS_ENTITY = 0x2a,
    HK_MEMORY_CLASS_WORLD_OPERATION = 0x2c,
    HK_MEMORY_CLASS_ISLAND = 0x2f,
};

class hkBool
{
public:
    hkBool() {}
    hkBool(bool b) { m_bool = (char)b; }
    operator bool() const { return m_bool != 0; }
    char m_bool;
};

// ---------------------------------------------------------------------------------------------- memory
// hkMemory::getInstance() (0x016e4178); vtable slot 4 = allocateChunk(nbytes, class), slot 6 is the refill
// of an empty thread-memory free-list row.
class hkMemory
{
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void* allocateChunk(int nbytes, int cls);
    virtual void v5();
    virtual void* onRowEmpty(int row, int cls);     // (coined)
    static hkMemory* s_instance;                    // 0x016e4178
};

extern unsigned long g_hkThreadMemoryTlsIndex;      // 0x016e4174

// Per-thread free lists, one row per 8-byte size class.
struct hkThreadMemory
{
    struct Elem { Elem* m_next; };
    uint32_t m_pad0[0xe];
    Elem*    m_freeListHead[17];    // +0x38
    int      m_freeListCount[17];   // +0x7c

    static hkThreadMemory* getInstance() { return (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTlsIndex); }
    static int constSizeToRow(int nbytes) { return (nbytes - 1) >> 3; }
    void* allocateChunkConstSize(int nbytes, int cls)
    {
        int row = constSizeToRow(nbytes);
        Elem* p = m_freeListHead[row];
        if (p)
        {
            m_freeListCount[row]--;
            m_freeListHead[row] = p->m_next;
            return p;
        }
        return hkMemory::s_instance->onRowEmpty(row, cls);
    }
};

class hkReferencedObject
{
public:
    hkReferencedObject() { m_referenceCount = 1; }
    virtual ~hkReferencedObject() {}

    void addReference()
    {
        if (m_memSizeAndFlags != 0)
            m_referenceCount++;
    }
    void removeReference()
    {
        if (m_memSizeAndFlags != 0)
        {
            m_referenceCount--;
            if (m_referenceCount == 0)
                delete this;
        }
    }
    void operator delete(void*) {}

    hkUint16 m_memSizeAndFlags;     // +0x4
    short    m_referenceCount;      // +0x6
};

// HK_DECLARE_CLASS_ALLOCATOR(cls): the size is stored into the new object, so cl drops the null check.
#define HK_DECLARE_CLASS_ALLOCATOR(CLS) \
    void* operator new(size_t nbytes) \
    { \
        hkReferencedObject* b = static_cast<hkReferencedObject*>(hkMemory::s_instance->allocateChunk((int)nbytes, CLS)); \
        b->m_memSizeAndFlags = (hkUint16)nbytes; \
        return b; \
    } \
    void operator delete(void*) {}

// HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(cls)
#define HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(CLS) \
    void* operator new(size_t nbytes) throw() { return hkMemory::s_instance->allocateChunk((int)nbytes, CLS); } \
    void operator delete(void*) {}

template <typename T>
struct hkArray
{
    T*  m_data;
    int m_size;
    int m_capacityAndFlags;

    hkArray() : m_data(0), m_size(0), m_capacityAndFlags((int)0x80000000) {}
    void pushBack(const T& t);
};

struct hkArrayUtil { static void _reserveMore(void* array, int elemSize); };     // 0x0107f530

template <typename T>
inline void hkArray<T>::pushBack(const T& t)
{
    if (m_size == (m_capacityAndFlags & 0x3fffffff))
        hkArrayUtil::_reserveMore(this, sizeof(T));
    m_data[m_size] = t;
    m_size++;
}

struct __declspec(align(16)) hkVector4 { float x, y, z, w; };

static inline hkReal length3(const hkVector4& v)
{
    float x = v.x;
    float y = v.y;
    float z = v.z;
    return sqrtf(x * x + y * y + z * z);
}

// ---------------------------------------------------------------------------------------------- errors
class hkOstream
{
public:
    hkOstream(void* buffer, int bufferSize, hkBool isString);   // 0x0107ef80
    virtual ~hkOstream();                                       // 0x0107efd0
    hkOstream& operator<<(const char* s);                       // 0x0107ee30
    hkOstream& operator<<(int i);                               // 0x0107ee80
    hkOstream& operator<<(unsigned int u);                      // 0x0107eed0
    uint32_t m_writer;
};

class hkError
{
public:
    enum Message { MESSAGE_REPORT, MESSAGE_WARNING, MESSAGE_ASSERT, MESSAGE_ERROR };
    virtual void v0();
    virtual void v1();
    virtual int  message(int type, int id, const char* description, const char* file, int line);
    virtual void setEnabled(int id, hkBool enabled);
    static hkError* s_instance;     // 0x016e4184
};

// ---------------------------------------------------------------------------------------------- cinfo
struct hkAabb { hkVector4 m_min; hkVector4 m_max; };
class hkCollisionFilter;
class hkWorldMemoryWatchDog;

struct hkWorldCinfo                         // 0xa0 (Spore's Havok reflection data)
{
    enum SimulationType
    {
        SIMULATION_TYPE_INVALID, SIMULATION_TYPE_DISCRETE, SIMULATION_TYPE_ASYNCHRONOUS, SIMULATION_TYPE_HALFSTEP,
        SIMULATION_TYPE_CONTINUOUS, SIMULATION_TYPE_CONTINUOUS_HALFSTEP, SIMULATION_TYPE_CONTINUOUS_ONE_THIRD_STEP,
        SIMULATION_TYPE_BACKSTEP_SIMPLE, SIMULATION_TYPE_BACKSTEP_NON_PENETRATING, SIMULATION_TYPE_MULTITHREADED
    };
    enum ContactPointGeneration { CONTACT_POINT_ACCEPT_ALWAYS, CONTACT_POINT_REJECT_DUBIOUS, CONTACT_POINT_REJECT_MANY };
    enum BroadPhaseBorderBehaviour { BROADPHASE_BORDER_ASSERT, BROADPHASE_BORDER_FIX_ENTITY, BROADPHASE_BORDER_REMOVE_ENTITY, BROADPHASE_BORDER_DO_NOTHING };

    uint32_t   m_vtbl;                                  // +0x00 hkReferencedObject
    uint32_t   m_memSizeAndRefCount;                    // +0x04
    uint32_t   m_pad8[2];
    hkVector4  m_gravity;                               // +0x10
    int        m_broadPhaseQuerySize;                   // +0x20
    hkReal     m_contactRestingVelocity;                // +0x24
    hkInt8     m_broadPhaseBorderBehaviour;             // +0x28
    hkInt8     m_pad29[7];
    hkAabb     m_broadPhaseWorldAabb;                   // +0x30
    hkReal     m_collisionTolerance;                    // +0x50
    hkCollisionFilter* m_collisionFilter;               // +0x54
    hkReal     m_expectedMaxLinearVelocity;             // +0x58
    hkReal     m_expectedMinPsiDeltaTime;               // +0x5c
    hkWorldMemoryWatchDog* m_memoryWatchDog;            // +0x60
    int        m_broadPhaseNumMarkers;                  // +0x64
    hkInt8     m_contactPointGeneration;                // +0x68
    hkInt8     m_pad69[3];
    hkReal     m_solverTau;                             // +0x6c
    hkReal     m_solverDamp;                            // +0x70
    int        m_solverIterations;                      // +0x74
    uint32_t   m_unusedPadding;                         // +0x78
    hkReal     m_iterativeLinearCastEarlyOutDistance;   // +0x7c
    int        m_iterativeLinearCastMaxIterations;      // +0x80
    hkReal     m_highFrequencyDeactivationPeriod;       // +0x84
    hkReal     m_lowFrequencyDeactivationPeriod;        // +0x88
    hkBool     m_shouldActivateOnRigidBodyTransformChange;  // +0x8c
    hkInt8     m_pad8d[3];
    hkReal     m_toiCollisionResponseRotateNormal;      // +0x90
    hkBool     m_enableDeactivation;                    // +0x94
    hkInt8     m_simulationType;                        // +0x95 (hkEnum<SimulationType, hkInt8>)
    hkBool     m_enableSimulationIslands;               // +0x96
    hkBool     m_processActionsInSingleThread;          // +0x97
    hkBool     m_synchronizeFrameAndPhysicsTime;        // +0x98
};

// ---------------------------------------------------------------------------------------------- solver info
struct hkStepInfo { hkReal m_startTime, m_endTime, m_deltaTime, m_invDeltaTime; };

struct hkSolverInfo                         // 0x140 (dev PDB)
{
    enum { DEACTIVATION_CLASSES_END = 6 };
    struct DeactivationInfo                 // 0x20
    {
        hkReal m_linearVelocityThresholdInv;
        hkReal m_angularVelocityThresholdInv;
        hkReal m_slowObjectVelocityMultiplier;
        hkReal m_relativeSleepVelocityThreshold;
        int m_stepsToDeactivate;           // (unsigned in the 2008 PDB; converted with a signed _ftol2 here)
        unsigned int m_padding[3];
    };
    hkReal    m_one;                        // +0x00
    hkReal    m_tau;
    hkReal    m_damping;
    hkReal    m_frictionTau;
    hkVector4 m_globalAccelerationPerSubStep;
    hkVector4 m_globalAccelerationPerStep;
    hkVector4 m_integrateVelocityFactor;
    hkVector4 m_invIntegrateVelocityFactor;
    hkReal    m_dampDivTau;
    hkReal    m_tauDivDamp;
    hkReal    m_dampDivFrictionTau;
    hkReal    m_frictionTauDivDamp;
    hkReal    m_contactRestingVelocity;     // +0x60
    DeactivationInfo m_deactivationInfo[DEACTIVATION_CLASSES_END];  // +0x64
    hkReal    m_deltaTime;                  // +0x124
    hkReal    m_invDeltaTime;               // +0x128
    int       m_numSteps;                   // +0x12c
    hkReal    m_invNumSteps;                // +0x130

    void setTauAndDamping(hkReal tau, hkReal damping);      // 0x01082890
};

struct hkWorldDynamicsStepInfo { hkStepInfo m_stepInfo; hkSolverInfo m_solverInfo; };

// ---------------------------------------------------------------------------------------------- collide
class hkWorld;
class hkContactMgrFactory : public hkReferencedObject {};
class hkCollisionAgent;

struct hkCollisionQualityInfo { uint32_t m_data[8]; };

class hkCollisionDispatcher : public hkReferencedObject
{
public:
    HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_AGENT)
    typedef void* (*CreateFunc)(void*, void*, void*, void*);
    struct InitCollisionQualityInfo         // 0x1c (dev PDB)
    {
        hkReal   m_gravityLength;
        hkReal   m_collisionTolerance;
        hkReal   m_minDeltaTime;
        hkReal   m_maxLinearVelocity;
        hkUint16 m_defaultConstraintPriority;
        hkUint16 m_toiConstraintPriority;
        hkUint16 m_toiHigherConstraintPriority;
        hkUint16 m_toiForcedConstraintPriority;
        hkBool   m_wantContinuousCollisionDetection;
        hkBool   m_enableNegativeManifoldTims;
        hkBool   m_enableNegativeToleranceToCreateNon4dContacts;
    };
    hkCollisionDispatcher(CreateFunc defaultCreationFunction, hkContactMgrFactory* defaultContactMgrFactory);  // 0x010cd700
    void initCollisionQualityInfo(InitCollisionQualityInfo& input);    // 0x010cd030
    void registerContactMgrFactory(hkContactMgrFactory* factory, int responseType);  // 0x010ccbd0

    hkCollisionQualityInfo* getCollisionQualityInfo(int index) { return &m_collisionQualityInfo[index]; }

    uint32_t m_data8[(0x1a50 - 8) / 4];
    hkCollisionQualityInfo m_collisionQualityInfo[(0x1c28 - 0x1a50) / 0x20];  // +0x1a50
    uint32_t m_tail[(0x1c28 - 0x1a50) % 0x20 / 4];
};

void* hkNullAgent_createNullAgent(void*, void*, void*, void*);    // 0x010cd8d0

class hkSimpleConstraintContactMgrFactory : public hkContactMgrFactory     // hkSimpleConstraintContactMgr::Factory
{
public:
    HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_CONTACT)
    hkSimpleConstraintContactMgrFactory(hkWorld* world);   // 0x0108d850
    hkWorld* m_world;
};

class hkReactiveContactMgrFactory : public hkContactMgrFactory   // hkReactiveContactMgr::Factory (coined)
{
public:
    HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_CONTACT)
    hkReactiveContactMgrFactory(hkWorld* world);           // 0x0109e6a0
    hkWorld* m_world;
};

// hkNullContactMgrFactory (0x10 bytes): a factory that is also the (shared) null contact manager it hands out
class hkContactMgr : public hkReferencedObject {};
class hkNullContactMgrFactory : public hkContactMgrFactory, public hkContactMgr
{
public:
    HK_DECLARE_CLASS_ALLOCATOR(4)
    hkNullContactMgrFactory() {}
    virtual void* createContactMgr();
};

class hkCollidableCollidableFilter { public: virtual ~hkCollidableCollidableFilter() {} };
class hkShapeCollectionFilter { public: virtual ~hkShapeCollectionFilter() {} };
class hkRayShapeCollectionFilter { public: virtual ~hkRayShapeCollectionFilter() {} };
class hkRayCollidableFilter { public: virtual ~hkRayCollidableFilter() {} };

class hkCollisionFilter : public hkReferencedObject, public hkCollidableCollidableFilter, public hkShapeCollectionFilter,
                          public hkRayShapeCollectionFilter, public hkRayCollidableFilter
{
};

class hkNullCollisionFilter : public hkCollisionFilter       // 0x18
{
public:
    HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_AGENT)
    hkNullCollisionFilter() {}
};

struct hkCollisionAgentConfig               // 0x8
{
    HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_COLLIDE)
    hkReal m_iterativeLinearCastEarlyOutDistance;
    int    m_iterativeLinearCastMaxIterations;
    hkCollisionAgentConfig() : m_iterativeLinearCastEarlyOutDistance(0.01f), m_iterativeLinearCastMaxIterations(20) {}
};

struct hkProcessCollisionInput              // 0x2c (dev PDB)
{
    HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_COLLIDE)
    hkCollisionDispatcher*   m_dispatcher;      // +0x00
    hkShapeCollectionFilter* m_filter;          // +0x04
    hkReal                   m_tolerance;       // +0x08
    hkBool                   m_createPredictiveAgents;   // +0x0c
    hkStepInfo               m_stepInfo;        // +0x10
    hkCollisionAgentConfig*  m_config;          // +0x20
    void*                    m_dynamicsInfo;    // +0x24
    hkCollisionQualityInfo*  m_collisionQualityInfo;     // +0x28
};

// ---------------------------------------------------------------------------------------------- broad phase
class hkBroadPhase;
extern hkBroadPhase* (*hkBroadPhase_s_createSweepAndPruneBroadPhaseFunction)(const hkVector4& worldMin, const hkVector4& worldMax, int numMarkers);  // 0x015ba370

class hkBroadPhaseListener : public hkReferencedObject {};

class hkTypedBroadPhaseDispatcher
{
public:
    HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_AGENT)
    hkTypedBroadPhaseDispatcher();          // 0x010cc4c0
    virtual ~hkTypedBroadPhaseDispatcher();
    hkBroadPhaseListener* m_broadPhaseListeners[8][8];      // +0x04
};

enum { BROAD_PHASE_INVALID, BROAD_PHASE_ENTITY, BROAD_PHASE_PHANTOM, BROAD_PHASE_BORDER };

class hkPhantomBroadPhaseListener : public hkBroadPhaseListener
{
public:
    HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BROAD_PHASE)
    hkPhantomBroadPhaseListener() {}
    virtual void addCollisionPair();
};

class hkEntityEntityBroadPhaseListener : public hkBroadPhaseListener
{
public:
    HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BROAD_PHASE)
    hkEntityEntityBroadPhaseListener(hkWorld* world);       // 0x010a3760
    hkWorld* m_world;
};

class hkBroadPhaseBorderListener : public hkBroadPhaseListener
{
public:
    HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BROAD_PHASE)
    hkBroadPhaseBorderListener() {}
    virtual void addCollisionPair();
};

class hkBroadPhaseBorder : public hkReferencedObject
{
public:
    HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_CDINFO)
    hkBroadPhaseBorder(hkWorld* world, hkWorldCinfo::BroadPhaseBorderBehaviour type);   // 0x010a2db0
    uint32_t m_data[10];
};

// ---------------------------------------------------------------------------------------------- simulation
class hkSimulation : public hkReferencedObject          // 0xc
{
public:
    HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SIMULATION)
    hkSimulation() {}
    virtual void step();
    hkWorld* m_world;                       // +0x08
};

class hkAsynchronousSimulation : public hkSimulation    // 0x10 (coined)
{
public:
    hkAsynchronousSimulation() { m_synchronizeFrameAndPhysicsTime = true; }
    virtual void step();
    hkBool m_synchronizeFrameAndPhysicsTime;    // +0x0c
};

class hkHalfstepSimulation : public hkAsynchronousSimulation   // 0x14
{
public:
    hkHalfstepSimulation();                 // 0x010a32a0
    uint32_t m_pad10;
};

class hkContinuousSimulation : public hkAsynchronousSimulation  // 0x2c
{
public:
    hkContinuousSimulation(int toiType);    // 0x010f19b0 (argument name coined)
    uint32_t m_data[7];
};

class hkBackstepSimulation : public hkContinuousSimulation     // 0x30
{
public:
    enum BackstepMode { SIMPLE, NON_PENETRATING };
    hkBackstepSimulation(BackstepMode mode) : hkContinuousSimulation(1) { m_backsteppingMode = mode; }
    virtual void step();
    BackstepMode m_backsteppingMode;        // +0x2c
};

class hkMultiThreadedSimulation : public hkContinuousSimulation // 0x240
{
public:
    hkMultiThreadedSimulation(hkWorld* world);  // 0x0109c940
    uint32_t m_data2[0x85];
};

class hkCriticalSection                     // 0x20 (dev PDB)
{
public:
    HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SIMULATION)
    hkCriticalSection(int spinCount) { InitializeCriticalSectionAndSpinCount(&m_section, spinCount); }
    uint32_t m_section[6];
    uint64_t m_currentThread;
};

class hkMultiThreadLock                     // 0x8 (dev PDB)
{
public:
    hkMultiThreadLock() : m_threadId(0xffffffd1), m_lockCount(0) {}
    void disableChecks();                   // 0x0109c230 (name from 6.x)
    unsigned int m_threadId;
    int          m_lockCount;
};

// ---------------------------------------------------------------------------------------------- world objects
class hkWorldOperationQueue
{
public:
    void* operator new(size_t nbytes) throw()
    {
        return hkThreadMemory::getInstance()->allocateChunkConstSize((int)nbytes, HK_MEMORY_CLASS_WORLD_OPERATION);
    }
    void operator delete(void*) {}
    hkWorldOperationQueue(hkWorld* world);  // 0x0109b3e0
    uint32_t m_data[11];
};

class hkSimulationIsland : public hkReferencedObject   // 0x74
{
public:
    HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_ISLAND)
    hkSimulationIsland(hkWorld* world);     // 0x010a2810
    uint32_t m_pad8[6];
    hkUint16 m_storageIndex;                // +0x20
    hkUint16 m_dirtyListIndex;              // +0x22
    hkUint8  m_highFrequencyDeactivationCounter;
    hkUint8  m_lowFrequencyDeactivationCounter;
    hkBool   m_splitCheckRequested;
    hkBool   m_actionListCleanupNeeded;
    hkBool   m_active;                      // +0x28
    hkBool   m_isInActiveIslandsArray;      // +0x29
    hkUint8  m_pad2a[0x74 - 0x2a];
};

class __declspec(align(16)) hkRigidBodyCinfo   // 0xc0
{
public:
    hkRigidBodyCinfo();                     // 0x01087ed0
    uint32_t m_pad0[0x24];
    hkReal   m_mass;                        // +0x90
    uint32_t m_pad94[7];
    hkInt8   m_motionType;                  // +0xb0
    hkInt8   m_padb1[15];
};

class hkWorldObject : public hkReferencedObject
{
public:
    void removeReference();                 // 0x0109ae60
};
class hkEntity : public hkWorldObject {};
class hkRigidBody : public hkEntity
{
public:
    HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_ENTITY)
    hkRigidBody(const hkRigidBodyCinfo& info);  // 0x010878b0
    uint32_t m_data[(0xd0 - 8) / 4];
};
enum hkEntityActivation { HK_ENTITY_ACTIVATION_DO_NOT_ACTIVATE, HK_ENTITY_ACTIVATION_DO_ACTIVATE };
enum { MOTION_FIXED = 7 };

class hkWorldMaintenanceMgr : public hkReferencedObject
{
public:
    virtual void init(hkWorld* world);
};
class hkDefaultWorldMaintenanceMgr : public hkWorldMaintenanceMgr
{
public:
    HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SIMULATION)
    hkDefaultWorldMaintenanceMgr();         // 0x010a2910
    uint32_t m_pad8[2];
};

class hkWorldMemoryWatchDog : public hkReferencedObject {};
class hkPhantom;

// ---------------------------------------------------------------------------------------------- hkWorld
class hkWorld : public hkReferencedObject   // 0x2f0 (dev PDB)
{
public:
    hkWorld(const hkWorldCinfo& info, unsigned int sdkVersion);
    hkEntity* addEntity(hkEntity* entity, hkEntityActivation initialActivationState);   // 0x01082ee0

    hkSimulation*                     m_simulation;                 // +0x08
    hkReal                            m_currentTime;                // +0x0c
    hkReal                            m_timeOfNextFrame;            // +0x10 (dev name)
    hkReal                            m_timeOfLastPsi;              // +0x14
    hkReal                            m_timeOfNextPsi;              // +0x18
    uint32_t                          m_pad1c;
    hkVector4                         m_gravity;                    // +0x20
    hkSimulationIsland*               m_fixedIsland;                // +0x30
    hkRigidBody*                      m_fixedRigidBody;             // +0x34
    hkArray<hkSimulationIsland*>      m_activeSimulationIslands;    // +0x38
    hkArray<hkSimulationIsland*>      m_inactiveSimulationIslands;  // +0x44
    hkArray<hkSimulationIsland*>      m_dirtySimulationIslands;     // +0x50
    hkWorldMaintenanceMgr*            m_maintenanceMgr;             // +0x5c
    hkWorldMemoryWatchDog*            m_memoryWatchDog;             // +0x60
    hkBroadPhase*                     m_broadPhase;                 // +0x64
    hkTypedBroadPhaseDispatcher*      m_broadPhaseDispatcher;       // +0x68
    hkPhantomBroadPhaseListener*      m_phantomBroadPhaseListener;  // +0x6c
    hkEntityEntityBroadPhaseListener* m_entityEntityBroadPhaseListener;   // +0x70
    hkBroadPhaseBorderListener*       m_broadPhaseBorderListener;   // +0x74
    hkProcessCollisionInput*          m_collisionInput;             // +0x78
    hkCollisionFilter*                m_collisionFilter;            // +0x7c
    hkCollisionDispatcher*            m_collisionDispatcher;        // +0x80
    hkWorldOperationQueue*            m_pendingOperations;          // +0x84
    int                               m_pendingOperationsCount;     // +0x88
    int                               m_lockCount;                  // +0x8c
    int                               m_lockCountForPhantoms;       // +0x90
    hkBool                            m_blockExecutingPendingOperations;  // +0x94
    hkBool                            m_criticalOperationsAllowed;  // +0x95
    void*                             m_pendingOperationQueues;     // +0x98
    int                               m_pendingOperationQueueCount; // +0x9c
    hkMultiThreadLock                 m_multiThreadLock;            // +0xa0
    hkBool                            m_processActionsInSingleThread;     // +0xa8
    hkCriticalSection*                m_modifyConstraintCriticalSection;  // +0xac
    hkCriticalSection*                m_worldLock;                  // +0xb0
    hkBool                            m_wantSimulationIslands;      // +0xb4
    hkBool                            m_wantDeactivation;           // +0xb5
    hkBool                            m_shouldActivateOnRigidBodyTransformChange;   // +0xb6
    hkReal                            m_highFrequencyDeactivationPeriod;  // +0xb8
    hkReal                            m_lowFrequencyDeactivationPeriod;   // +0xbc
    hkReal                            m_toiCollisionResponseRotateNormal; // +0xc0
    int                               m_simulationType;             // +0xc4 (hkWorldCinfo::SimulationType)
    unsigned int                      m_lastEntityUid;              // +0xc8
    hkArray<hkPhantom*>               m_phantoms;                   // +0xcc
    hkArray<void*>                    m_actionListeners;            // +0xd8
    hkArray<void*>                    m_entityListeners;            // +0xe4
    hkArray<void*>                    m_phantomListeners;           // +0xf0
    hkArray<void*>                    m_constraintListeners;        // +0xfc
    hkArray<void*>                    m_worldDeletionListeners;     // +0x108
    hkArray<void*>                    m_islandActivationListeners;  // +0x114
    hkArray<void*>                    m_worldPostSimulationListeners;     // +0x120
    hkArray<void*>                    m_worldPostIntegrateListeners;      // +0x12c
    hkArray<void*>                    m_worldPostCollideListeners;  // +0x138
    hkArray<void*>                    m_islandPostIntegrateListeners;     // +0x144
    hkArray<void*>                    m_islandPostCollideListeners; // +0x150
    hkArray<void*>                    m_collisionListeners;         // +0x15c
    hkBroadPhaseBorder*               m_broadPhaseBorder;           // +0x168
    uint32_t                          m_pad16c;
    hkWorldDynamicsStepInfo           m_dynamicsStepInfo;           // +0x170
    hkVector4                         m_broadPhaseExtents[2];       // +0x2c0
    int                               m_broadPhaseNumMarkers;       // +0x2e0
    int                               m_broadPhaseQuerySize;        // +0x2e4
    int                               m_broadPhaseUpdateSize;       // +0x2e8
    hkInt8                            m_contactPointGeneration;     // +0x2ec
};

// Registers the simple-constraint, reactive and null contact manager factories (0x01082df0). A static
// helper of hkWorld.cpp: the original passes the world in EAX, so it is defined here (same TU) and kept
// out of line.
static __declspec(noinline) void hkWorld_registerContactMgrFactories(hkWorld* world, hkCollisionDispatcher* dis)
{
    hkContactMgrFactory* simple = new hkSimpleConstraintContactMgrFactory(world);
    hkContactMgrFactory* reactive = new hkReactiveContactMgrFactory(world);
    hkNullContactMgrFactory* nullFactory = new hkNullContactMgrFactory();
    dis->registerContactMgrFactory(simple, 1);
    dis->registerContactMgrFactory(reactive, 2);
    dis->registerContactMgrFactory(nullFactory, 3);
    simple->removeReference();
    reactive->removeReference();
    static_cast<hkContactMgrFactory*>(nullFactory)->removeReference();
}

// @ 0x010840e0
hkWorld::hkWorld(const hkWorldCinfo& info, unsigned int sdkVersion)
{
    m_timeOfNextFrame = 0.0f;
    m_timeOfLastPsi = 0.0f;
    m_timeOfNextPsi = 0.0f;
    m_lastEntityUid = 0xffffffff;

    m_pendingOperations = new hkWorldOperationQueue(this);
    m_pendingOperationQueues = 0;
    m_pendingOperationsCount = 0;
    m_lockCount = 0;
    m_lockCountForPhantoms = 0;
    m_blockExecutingPendingOperations = false;
    m_criticalOperationsAllowed = true;
    m_pendingOperationQueueCount = 1;
    m_modifyConstraintCriticalSection = 0;
    m_worldLock = 0;

    if (sdkVersion != 0x765c)
    {
        char buf[512];
        hkOstream ostr(buf, sizeof(buf), true);
        ostr << "** Havok libs built with version [" << 0x765c << "], used with code built with [" << sdkVersion << "]. **";
        hkError::s_instance->message(3, 0x53c94b42, buf, ".\\world\\hkWorld.cpp", 0x8c8);
    }

    m_simulationType = hkWorldCinfo::SIMULATION_TYPE_INVALID;
    m_simulation = 0;
    m_gravity = info.m_gravity;
    m_shouldActivateOnRigidBodyTransformChange = info.m_shouldActivateOnRigidBodyTransformChange;
    m_toiCollisionResponseRotateNormal = info.m_toiCollisionResponseRotateNormal;
    m_highFrequencyDeactivationPeriod = info.m_highFrequencyDeactivationPeriod;
    m_lowFrequencyDeactivationPeriod = info.m_lowFrequencyDeactivationPeriod;

    // solver
    {
        hkSolverInfo& si = m_dynamicsStepInfo.m_solverInfo;
        si.m_one = 1.0f;
        si.setTauAndDamping(info.m_solverTau, info.m_solverDamp);
        si.m_contactRestingVelocity = info.m_contactRestingVelocity;
        si.m_numSteps = info.m_solverIterations;
        si.m_invNumSteps = 1.0f / info.m_solverIterations;

        hkReal gravLen = length3(info.m_gravity);
        if (gravLen == 0.0f)
            gravLen = 9.81f;
        const hkReal angGravity = 0.1f * gravLen;

        for (int i = 0; i < hkSolverInfo::DEACTIVATION_CLASSES_END; i++)
        {
            hkReal relVelocityThres;
            hkReal relSleepVelocityThres;
            hkReal deactivationTime;
            switch (i)
            {
            case 0:
            case 1:
                relVelocityThres = HK_REAL_EPSILON;
                relSleepVelocityThres = 0.0f;
                deactivationTime = 1000.0f;
                break;
            case 2:
                relVelocityThres = 0.01f;
                relSleepVelocityThres = 0.08f;
                deactivationTime = 0.1f;
                break;
            case 3:
                relVelocityThres = 0.017f;
                relSleepVelocityThres = 0.2f;
                deactivationTime = 0.1f;
                break;
            case 4:
                relVelocityThres = 0.02f;
                relSleepVelocityThres = 0.3f;
                deactivationTime = 0.1f;
                break;
            default:
                relVelocityThres = 0.025f;
                relSleepVelocityThres = 0.4f;
                deactivationTime = 0.05f;
                break;
            }
            hkSolverInfo::DeactivationInfo& di = si.m_deactivationInfo[i];
            di.m_stepsToDeactivate = (int)(hkReal(si.m_numSteps) * deactivationTime / 0.016f);
            hkReal linearThres = relVelocityThres * gravLen;
            di.m_linearVelocityThresholdInv = 1.0f / linearThres;
            di.m_slowObjectVelocityMultiplier = 1.0f - relSleepVelocityThres * di.m_linearVelocityThresholdInv * gravLen * si.m_invNumSteps * 0.016f;
            di.m_angularVelocityThresholdInv = 1.0f / (linearThres * angGravity);
            if (relSleepVelocityThres > 0.0f)
                di.m_relativeSleepVelocityThreshold = si.m_invNumSteps / relSleepVelocityThres * 0.016f;
            else
                di.m_relativeSleepVelocityThreshold = HK_REAL_MAX / 16.0f;
        }
    }

    m_memoryWatchDog = info.m_memoryWatchDog;
    if (m_memoryWatchDog)
        m_memoryWatchDog->addReference();

    m_wantSimulationIslands = info.m_enableSimulationIslands;
    m_wantDeactivation = info.m_enableDeactivation;
    if (!m_wantSimulationIslands && m_wantDeactivation)
        m_wantDeactivation = false;
    m_processActionsInSingleThread = info.m_processActionsInSingleThread;

    // broad phase
    m_broadPhaseExtents[0] = info.m_broadPhaseWorldAabb.m_min;
    m_broadPhaseExtents[1] = info.m_broadPhaseWorldAabb.m_max;
    m_broadPhaseNumMarkers = info.m_broadPhaseNumMarkers;
    m_broadPhase = hkBroadPhase_s_createSweepAndPruneBroadPhaseFunction(m_broadPhaseExtents[0], m_broadPhaseExtents[1], info.m_broadPhaseNumMarkers);
    m_broadPhaseQuerySize = info.m_broadPhaseQuerySize;
    m_broadPhaseUpdateSize = m_broadPhaseQuerySize / 2;

    m_broadPhaseDispatcher = new hkTypedBroadPhaseDispatcher();
    m_phantomBroadPhaseListener = new hkPhantomBroadPhaseListener();
    m_entityEntityBroadPhaseListener = new hkEntityEntityBroadPhaseListener(this);
    m_broadPhaseBorderListener = new hkBroadPhaseBorderListener();

    m_broadPhaseDispatcher->m_broadPhaseListeners[BROAD_PHASE_ENTITY][BROAD_PHASE_PHANTOM] = m_phantomBroadPhaseListener;
    m_broadPhaseDispatcher->m_broadPhaseListeners[BROAD_PHASE_PHANTOM][BROAD_PHASE_INVALID] = m_phantomBroadPhaseListener;
    m_broadPhaseDispatcher->m_broadPhaseListeners[BROAD_PHASE_PHANTOM][BROAD_PHASE_ENTITY] = m_phantomBroadPhaseListener;
    m_broadPhaseDispatcher->m_broadPhaseListeners[BROAD_PHASE_ENTITY][BROAD_PHASE_INVALID] = m_entityEntityBroadPhaseListener;
    m_broadPhaseDispatcher->m_broadPhaseListeners[BROAD_PHASE_ENTITY][BROAD_PHASE_BORDER] = m_broadPhaseBorderListener;
    m_broadPhaseDispatcher->m_broadPhaseListeners[BROAD_PHASE_BORDER][BROAD_PHASE_INVALID] = m_broadPhaseBorderListener;
    m_broadPhaseDispatcher->m_broadPhaseListeners[BROAD_PHASE_PHANTOM][BROAD_PHASE_PHANTOM] = m_broadPhaseBorderListener;
    m_broadPhaseDispatcher->m_broadPhaseListeners[BROAD_PHASE_BORDER][BROAD_PHASE_ENTITY] = m_broadPhaseBorderListener;
    m_broadPhaseDispatcher->m_broadPhaseListeners[BROAD_PHASE_BORDER][BROAD_PHASE_PHANTOM] = m_broadPhaseBorderListener;

    // collision dispatcher, filter and input
    {
        hkContactMgrFactory* defaultCmFactory = new hkSimpleConstraintContactMgrFactory(this);
        m_collisionDispatcher = new hkCollisionDispatcher(hkNullAgent_createNullAgent, defaultCmFactory);
        defaultCmFactory->removeReference();
    }

    if (info.m_collisionFilter == 0)
    {
        m_collisionFilter = new hkNullCollisionFilter();
    }
    else
    {
        m_collisionFilter = info.m_collisionFilter;
        m_collisionFilter->addReference();
    }

    m_collisionInput = new hkProcessCollisionInput;
    hkProcessCollisionInput* input = m_collisionInput;
    input->m_dispatcher = m_collisionDispatcher;
    input->m_tolerance = info.m_collisionTolerance;
    input->m_filter = m_collisionFilter;
    input->m_config = new hkCollisionAgentConfig();
    m_contactPointGeneration = info.m_contactPointGeneration;
    input->m_config->m_iterativeLinearCastEarlyOutDistance = info.m_iterativeLinearCastEarlyOutDistance;
    input->m_config->m_iterativeLinearCastMaxIterations = info.m_iterativeLinearCastMaxIterations;
    input->m_createPredictiveAgents = false;
    input->m_collisionQualityInfo = input->m_dispatcher->getCollisionQualityInfo(0);

    hkWorld_registerContactMgrFactories(this, m_collisionDispatcher);

    // simulation
    if ((info.m_simulationType != (hkInt8)m_simulationType) != false)
    {
        if (m_simulation)
            delete m_simulation;
        m_simulationType = info.m_simulationType;
        switch (m_simulationType)
        {
        case hkWorldCinfo::SIMULATION_TYPE_DISCRETE:
            m_simulation = new hkSimulation();
            break;
        case hkWorldCinfo::SIMULATION_TYPE_ASYNCHRONOUS:
            m_simulation = new hkAsynchronousSimulation();
            break;
        case hkWorldCinfo::SIMULATION_TYPE_HALFSTEP:
            m_simulation = new hkHalfstepSimulation();
            break;
        case hkWorldCinfo::SIMULATION_TYPE_CONTINUOUS_HALFSTEP:
            m_simulation = new hkContinuousSimulation(1);
            break;
        case hkWorldCinfo::SIMULATION_TYPE_CONTINUOUS_ONE_THIRD_STEP:
            m_simulation = new hkContinuousSimulation(2);
            break;
        case hkWorldCinfo::SIMULATION_TYPE_BACKSTEP_SIMPLE:
            m_simulation = new hkBackstepSimulation(hkBackstepSimulation::SIMPLE);
            break;
        case hkWorldCinfo::SIMULATION_TYPE_BACKSTEP_NON_PENETRATING:
            m_simulation = new hkBackstepSimulation(hkBackstepSimulation::NON_PENETRATING);
            break;
        case hkWorldCinfo::SIMULATION_TYPE_MULTITHREADED:
            m_modifyConstraintCriticalSection = new hkCriticalSection(4000);
            m_simulation = new hkMultiThreadedSimulation(this);
            break;
        default:
            // unknown type: fall back to continuous (the cinfo is patched with a 32-bit store)
            m_simulationType = hkWorldCinfo::SIMULATION_TYPE_CONTINUOUS;
            *(int*)&const_cast<hkWorldCinfo&>(info).m_simulationType = hkWorldCinfo::SIMULATION_TYPE_CONTINUOUS;
            // fall through
        case hkWorldCinfo::SIMULATION_TYPE_CONTINUOUS:
            m_simulation = new hkContinuousSimulation(0);
            break;
        }
        m_worldLock = new hkCriticalSection(4000);
        if (m_simulationType >= hkWorldCinfo::SIMULATION_TYPE_ASYNCHRONOUS)
            static_cast<hkAsynchronousSimulation*>(m_simulation)->m_synchronizeFrameAndPhysicsTime = info.m_synchronizeFrameAndPhysicsTime;
    }

    // collision quality
    {
        hkReal gravLen = length3(m_gravity);
        if (gravLen == 0.0f)
            gravLen = 9.81f;
        hkCollisionDispatcher::InitCollisionQualityInfo qi;
        qi.m_gravityLength = gravLen;
        qi.m_collisionTolerance = m_collisionInput->m_tolerance;
        qi.m_minDeltaTime = info.m_expectedMinPsiDeltaTime;
        qi.m_maxLinearVelocity = info.m_expectedMaxLinearVelocity;
        qi.m_wantContinuousCollisionDetection = info.m_simulationType >= hkWorldCinfo::SIMULATION_TYPE_CONTINUOUS;
        qi.m_enableNegativeManifoldTims = info.m_contactPointGeneration == hkWorldCinfo::CONTACT_POINT_REJECT_MANY;
        qi.m_enableNegativeToleranceToCreateNon4dContacts = info.m_contactPointGeneration >= hkWorldCinfo::CONTACT_POINT_REJECT_DUBIOUS;
        qi.m_defaultConstraintPriority = 1;
        qi.m_toiConstraintPriority = 2;
        qi.m_toiHigherConstraintPriority = 3;
        qi.m_toiForcedConstraintPriority = 4;
        m_collisionDispatcher->initCollisionQualityInfo(qi);
        m_collisionInput->m_collisionQualityInfo = m_collisionDispatcher->getCollisionQualityInfo(0);
    }

    // islands
    m_fixedIsland = new hkSimulationIsland(this);
    m_fixedIsland->m_storageIndex = 0xffff;
    m_fixedIsland->m_active = false;
    m_fixedIsland->m_isInActiveIslandsArray = false;

    if (!m_wantSimulationIslands)
    {
        hkSimulationIsland* activeIsland = new hkSimulationIsland(this);
        m_activeSimulationIslands.pushBack(activeIsland);
        activeIsland->m_storageIndex = 0;
    }

    // fixed rigid body
    {
        hkRigidBodyCinfo rbci;
        rbci.m_motionType = MOTION_FIXED;
        rbci.m_mass = 0.0f;
        hkError::s_instance->setEnabled(0x7cdcd39f, false);
        m_fixedRigidBody = new hkRigidBody(rbci);
        hkError::s_instance->setEnabled(0x7cdcd39f, true);
        addEntity(m_fixedRigidBody, HK_ENTITY_ACTIVATION_DO_ACTIVATE);
        m_fixedRigidBody->removeReference();
    }

    m_dynamicsStepInfo.m_stepInfo.m_deltaTime = 0.0f;
    m_collisionInput->m_dynamicsInfo = &m_dynamicsStepInfo;

    if (info.m_broadPhaseBorderBehaviour != hkWorldCinfo::BROADPHASE_BORDER_DO_NOTHING)
        m_broadPhaseBorder = new hkBroadPhaseBorder(this, (hkWorldCinfo::BroadPhaseBorderBehaviour)info.m_broadPhaseBorderBehaviour);
    else
        m_broadPhaseBorder = 0;

    m_maintenanceMgr = new hkDefaultWorldMaintenanceMgr();
    m_maintenanceMgr->init(this);

    if (info.m_simulationType != hkWorldCinfo::SIMULATION_TYPE_MULTITHREADED)
        m_multiThreadLock.disableChecks();
}
