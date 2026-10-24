// Havok 3.1.0 slice s0109b490: hkWorldOperationQueue::executeAllPending (0x0109b490), the dispatcher that
// replays the operations queued while the world was locked (".\world\util\hkWorldOperationQueue.cpp").
// Flags: /vc71 /O2 /MD /Gy /TP.
//
// Queue layout (retail): +0 hkArray<Op> m_pending, +0xc hkWorld* m_world, +0x10 hkArray<Op> m_criticalPending
// (sorted by island index and prepended to m_pending before executing), +0x1c flag, +0x20 critical section.
// Each Op is 0x14 bytes: byte type at +0, payload from +4. Type names marked "(coined)" are not from a symbol.
#include <stddef.h>
#include <math.h>
#include "types.h"

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern unsigned long g_hkThreadMemoryTlsIndex;       // 0x016e4174
extern float g_hkRealZero;                           // 0x01485378 (_HK_REAL_ZERO)
extern float g_hkRealOne;                            // 0x01485720 (_HK_REAL_ONE)

enum { HK_ARRAY_FLAG_MASK = 0x3fffffff, HK_ARRAY_DONT_DEALLOCATE = (int)0x80000000 };
enum { HK_MEMORY_CLASS_ARRAY = 0x14, HK_MEMORY_CLASS_UNKNOWN4 = 4, HK_MEMORY_CLASS_AABB = 0x24 };

class hkBool
{
public:
    hkBool() {}
    hkBool(bool b) { m_bool = (char)b; }
    operator bool() const { return m_bool != 0; }
    char m_bool;
};

class hkThreadMemory
{ public:
    void deallocateChunk(void* p, int nbytes, int memClass);     // 0x0107db10
    static hkThreadMemory* getInstance() { return (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTlsIndex); }
    char m_pad00[0x20];
    int  m_usedAt20;            // +0x20  bytes used in the current stack chunk
    char m_pad24[8];
    int  m_capacityAt2c;        // +0x2c  bytes available in the current stack chunk
};

// hkMemory::getInstance() (0x016e4178): vtable slot 5 = deallocateChunk.
class hkMemory
{
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void deallocateChunk(void* p, int nbytes, int memClass);
    static hkMemory* s_instance;                     // 0x016e4178
    int m_outOfMemory4;         // +0x04  set to 1 when an allocation failed
    int m_freeAt08;             // +0x08
    char m_pad0c[8];
    int m_usedAt14;             // +0x14
    char m_pad18[0x10];
    int m_allocatedAt28;        // +0x28
};

class hkReferencedObject
{
public:
    virtual ~hkReferencedObject() {}
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
    uint16_t m_memSizeAndFlags;     // +0x4
    short    m_referenceCount;      // +0x6
};

template <typename T>
class hkArray
{ public:
    T* m_data; int m_size; int m_capacityAndFlags;
    hkArray() {}
    hkArray(T* data, int size, int capacity) : m_data(data), m_size(size), m_capacityAndFlags(capacity | HK_ARRAY_DONT_DEALLOCATE) {}
    ~hkArray()
    {
        if (m_capacityAndFlags >= 0)
            hkThreadMemory::getInstance()->deallocateChunk(m_data, (m_capacityAndFlags & HK_ARRAY_FLAG_MASK) * (int)sizeof(T), HK_MEMORY_CLASS_ARRAY);
    }
    void swap(hkArray& o)
    {
        T* d = m_data; m_data = o.m_data; o.m_data = d;
        int s = m_size; m_size = o.m_size; o.m_size = s;
        int c = m_capacityAndFlags; m_capacityAndFlags = o.m_capacityAndFlags; o.m_capacityAndFlags = c;
    }
    T& operator[](int i) { return m_data[i]; }
    void insertAt(int i, const hkArray<T>& src);     // 0x0109aed0
};

template <typename T, int N>
class hkInplaceArray : public hkArray<T> { public:
    hkInplaceArray() : hkArray<T>(m_storage, 0, N) {}
    T m_storage[N];
};

__declspec(align(16)) struct hkVector4 { uint32_t m_q[4]; };
struct hkQuaternion;
struct hkAabb;
class hkShape : public hkReferencedObject { public:};
class hkWorld; class hkEntity; class hkPhantom; class hkRigidBody; class hkAction; class hkConstraintInstance;
class hkWorldOperationQueue;

enum hkEntityActivation { HK_ENTITY_ACTIVATION_DO_NOT_ACTIVATE = 0, HK_ENTITY_ACTIVATION_DO_ACTIVATE = 1 };

// Queued operation record.
struct Op
{
    Op() { m_type = 0; }
    uint8_t  m_type;           // +0
    uint8_t  m_b1, m_b2;       // +1, +2
    void*    m_a;              // +4
    union
    {
        void*    m_b;          // +8
        uint16_t m_count;
        struct { uint8_t m_x, m_y, m_z; } m_u;
        uint32_t m_w8;
    };
    uint32_t m_w0c;            // +0xc
    uint32_t m_w10;            // +0x10
    hkEntity* entity() const;
    hkEntity* entityB() const;
    hkRigidBody* body() const;
    hkPhantom* phantom() const;
    hkAction* action() const;
    hkConstraintInstance* constraint() const;
    hkShape* shape() const;
    hkEntity** entities() const;
    hkPhantom** phantoms() const;
};

enum OpType
{
    OP_ADD_ENTITY = 1, OP_REMOVE_ENTITY = 2, OP_UPDATE_ENTITY_BP = 3, OP_SET_RIGID_BODY_MOTION_TYPE = 4, OP_SET_SHAPE = 5,
    OP_ADD_ENTITY_BATCH = 6, OP_REMOVE_ENTITY_BATCH = 7, OP_ADD_CONSTRAINT = 8, OP_REMOVE_CONSTRAINT = 9,
    OP_ADD_ACTION = 10, OP_REMOVE_ACTION = 11, OP_MERGE_ISLANDS = 12, OP_ADD_PHANTOM = 13, OP_REMOVE_PHANTOM = 14,
    OP_ADD_PHANTOM_BATCH = 15, OP_REMOVE_PHANTOM_BATCH = 16, OP_UPDATE_PHANTOM_AABB = 17,
    OP_UPDATE_FILTER_ON_ENTITY = 18, OP_UPDATE_FILTER_ON_PHANTOM = 19, OP_UPDATE_FILTER_ON_WORLD = 20,
    OP_UPDATE_MOVED_BODY_INFO = 21, OP_RESET_COLLISION_INFO = 22, OP_SET_POSITION_AND_ROTATION = 23,
    OP_SET_LINEAR_VELOCITY = 24, OP_SET_ANGULAR_VELOCITY = 25, OP_APPLY_LINEAR_IMPULSE = 26,
    OP_APPLY_POINT_IMPULSE = 27, OP_APPLY_ANGULAR_IMPULSE = 28, OP_ACTIVATE_REGION = 31, OP_ACTIVATE_ENTITY = 32,
    OP_DEACTIVATE_ENTITY = 33, OP_SET_PHANTOM_SHAPE = 34
};

class hkWorldObject : public hkReferencedObject
{
public:
    virtual void woSlot1();
    virtual void setShape(hkShape* shape);                // slot 2
    void removeReference();                               // 0x0109ae60
    hkWorld* m_world;                                     // +8
};

class hkSimulationIsland;
class hkMotion
{
public:
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3(); virtual void m4(); virtual void m5();
    virtual void m6(); virtual void m7(); virtual void m8(); virtual void m9(); virtual void m10(); virtual void m11();
    virtual void m12(); virtual void m13(); virtual void m14(); virtual void m15(); virtual void m16(); virtual void m17();
    virtual void m18(); virtual void m19(); virtual void m20(); virtual void m21();
    virtual void setLinearVelocity(const hkVector4& v);                       // slot 22 (+0x58)
    virtual void setAngularVelocity(const hkVector4& v);                      // slot 23
    virtual void applyLinearImpulse(const hkVector4& v);                      // slot 24
    virtual void applyPointImpulse(const hkVector4& impulse, const hkVector4& point);   // slot 25
    virtual void applyAngularImpulse(const hkVector4& v);                     // slot 26
};

class hkEntity : public hkWorldObject
{
public:
    char m_pad0c[0x58 - 0xc];
    hkMotion* m_motion;                                   // +0x58
    hkSimulationIsland* m_simulationIsland;               // +0x5c
    char m_pad60[0x99 - 0x60];
    hkBool m_fixed;                                       // +0x99
    void activate();                                      // 0x01088ae0
    void deactivate();                                    // 0x01088b10
};
class hkPhantom : public hkWorldObject
{
public:
    void updateBroadPhase(const hkAabb& aabb);            // 0x0108e680
};
class hkRigidBody : public hkEntity
{
public:
    void setMotionType(int motionType, int activation, int filterMode);              // 0x01087520
    void setPositionAndRotation(const hkVector4& pos, const hkQuaternion& rot);       // 0x01087860
    static void updateBroadphaseAndResetCollisionInformationOfWarpedBody(hkEntity* e);   // 0x01087750
};
class hkAction : public hkReferencedObject
{
public:
    virtual void aSlot1(); virtual void aSlot2();
    virtual void getEntities(hkArray<hkEntity*>& entitiesOut);                         // slot 3 (+0xc)
    hkWorld* m_world;                                     // +8
    void* m_island;                                       // +0xc
};
class hkConstraintInstance : public hkReferencedObject
{
public:
    void* m_owner;                                        // +8
    void* m_data;                                         // +0xc
    hkEntity* m_entities[2];                              // +0x10
};

class hkSimulation
{
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
    virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void resetCollisionInformationForEntities(hkEntity** entities, int numEntities, hkWorld* world);   // slot 10 (+0x28)
};

struct hkTime
{
    float m_start;                                        // +0
    float m_end;                                          // +4
    float m_delta;                                        // +8
    float m_invDelta;                                     // +0xc
    hkTime() {}
    hkTime(float start, float end) { set(start, end); }
    void set(float start, float end)
    {
        m_start = start;
        m_end = end;
        m_delta = end - start;
        m_invDelta = (m_delta == g_hkRealZero) ? 0.0f : g_hkRealOne / m_delta;
    }
};

// Virtual solver reached through hkWorld::m_solver (+0x5c): step() is vtable slot 3 (+0xc).
class hkSolver
{
public:
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void step(hkWorld* world, const hkTime* time);   // +0xc
};

class hkWorld : public hkReferencedObject
{
public:
    hkSimulation* m_simulation;                           // +0x8
    float m_stepTime0c;                                   // +0xc   time snapshot for the last step
    float m_currentTime;                                  // +0x10  simulation clock
    float m_prevTime;                                     // +0x14  start of the last step
    float m_endTime;                                      // +0x18  end of the last step
    char m_pad1c[0x5c - 0x1c];
    hkSolver* m_solver;                                   // +0x5c
    char m_pad60[0x9c - 0x60];
    int m_pendingOperationQueueCount;                     // +0x9c

    hkEntity* addEntity(hkEntity* entity, hkEntityActivation act);                   // 0x01082ee0
    hkBool removeEntity(hkEntity* entity);                                           // 0x01083110
    hkPhantom* addPhantom(hkPhantom* phantom);                                       // 0x01083320
    void removePhantom(hkPhantom* phantom);                                          // 0x01083400
    void activateRegion(const hkAabb& aabb);                                         // 0x01083ff0
    void updateCollisionFilterOnEntity(hkEntity* entity, int mode, int shapeMode);   // 0x01084fa0
    void updateCollisionFilterOnPhantom(hkPhantom* phantom, int shapeMode);          // 0x01084cf0
    void addEntityBatch(hkEntity* const* entities, int n, hkEntityActivation act);   // 0x01085490
    hkAction* addAction(hkAction* action);                                           // 0x01085e60
    void removeEntityBatch(hkEntity* const* entities, int n);                        // 0x01085a80
    void addPhantomBatch(hkPhantom* const* phantoms, int n);                         // 0x010861c0
    void removePhantomBatch(hkPhantom* const* phantoms, int n);                      // 0x01086500 (coined)
    hkConstraintInstance* addConstraint(hkConstraintInstance* c);                    // 0x01086da0
    hkBool removeConstraint(hkConstraintInstance* c);                                // 0x01086e90
    void removeAction(hkAction* action);                                             // 0x01086f40
    void updateCollisionFilterOnWorld(int updateMode, int shapeMode);                // 0x010869e0
    int calcMaxIslandSizeEstimate();                                                 // 0x01082ca0
};

struct hkWorldOperationUtil
{
    static void updateEntityBP(hkWorld* world, hkEntity* entity);                    // 0x010a0970
    static void mergeIslands(hkWorld* world, hkEntity* a, hkEntity* b);              // 0x010a1170 (coined)
};

hkBool opLess(const Op& a, const Op& b);                                             // 0x0109ae80
void quickSortRecursive(Op* data, int lo, int hi, hkBool (*less)(const Op&, const Op&));   // 0x01115a50

class hkWorldOperationQueue
{
public:
    hkArray<Op> m_pending;                                // +0
    hkWorld* m_world;                                     // +0xc
    hkArray<Op> m_criticalPending;                        // +0x10
    void executeAllPending();                             // 0x0109b490
};

inline hkEntity* Op::entity() const { return (hkEntity*)m_a; }
inline hkEntity* Op::entityB() const { return (hkEntity*)m_b; }
inline hkRigidBody* Op::body() const { return (hkRigidBody*)m_a; }
inline hkPhantom* Op::phantom() const { return (hkPhantom*)m_a; }
inline hkAction* Op::action() const { return (hkAction*)m_a; }
inline hkConstraintInstance* Op::constraint() const { return (hkConstraintInstance*)m_a; }
inline hkShape* Op::shape() const { return (hkShape*)m_b; }
inline hkEntity** Op::entities() const { return (hkEntity**)m_a; }
inline hkPhantom** Op::phantoms() const { return (hkPhantom**)m_a; }

static inline void freeBlock(void* p, int nbytes, int cls)
{
    hkMemory::s_instance->deallocateChunk(p, nbytes, cls);
}

// ---- asynchronous simulation ---------------------------------------------------------------------------
extern "C" __declspec(dllimport) int __stdcall TlsSetValue(unsigned long index, void* value);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void* cs);
extern unsigned long g_hkMonitorStreamCurrentTls;    // 0x016e42a4
extern unsigned long g_hkMonitorStreamEndTls;        // 0x016e42a8
extern const char hkMonitorTimerEndTag[];            // 0x0149cc34 ("Et")

// A 12-byte monitor-stream command: tag pointer + 32-bit tick stamp. begin/end advance the TLS write cursor.
struct hkMonitorCommand { const char* m_commandAndMonitor; uint32_t m_time0; uint32_t m_pad; };

#define HK_READ_TICKS(dst) { uint32_t ticks_; __asm { rdtsc } __asm { mov ticks_, eax } (dst) = ticks_; }
#define HK_TIMER_CMD(name) do { \
    void* hkEnd_ = TlsGetValue(g_hkMonitorStreamEndTls); \
    if (TlsGetValue(g_hkMonitorStreamCurrentTls) < hkEnd_) { \
        hkMonitorCommand* hkCmd_ = (hkMonitorCommand*)TlsGetValue(g_hkMonitorStreamCurrentTls); \
        hkCmd_->m_commandAndMonitor = (name); \
        HK_READ_TICKS(hkCmd_->m_time0) \
        TlsSetValue(g_hkMonitorStreamCurrentTls, hkCmd_ + 1); \
    } \
} while (0)

class hkStepInfo
{
public:
    hkStepInfo(float start, float end);               // 0x01099430
    float m_start;                                    // +0
    float m_end;                                      // +4
    float m_delta;                                    // +8
    float m_invDelta;                                 // +0xc
};

struct hkMultithreadConfig
{
    int m_numThreads;                                 // +0
    int m_maxNumThreads;                              // +4
};

struct hkCriticalSection
{
    char m_os[0x18];
    int  m_ownerThread;                               // +0x18
    int  m_recursionCount;                            // +0x1c
};

class hkAsynchronousSimulation : public hkReferencedObject
{
public:
    virtual void a0();
    virtual int executeStep(hkWorld* world, int mode, void* arg);          // slot 2 (+0x8)
    virtual int recoverFromStepFailure(hkWorld* world, int result);        // 0x0109be00
    virtual int stepDeltaTime(hkWorld* world, float deltaTime, float maxDeltaTime);   // 0x0109bed0
    void stepCollide(hkWorld* world, const hkTime* time);                 // 0x0109a200
    void postStep(hkWorld* world, const hkTime* time);                    // 0x01099690
    union
    {
        void* m_arg8;                                 // +0x8   payload handed to executeStep
        float m_f8;                                   // +0x8   max delta time for stepDeltaTime
    };
    unsigned char m_flagC;                            // +0xc   "snap time / reprocess" flag
};

class hkMultiThreadedSimulation : public hkAsynchronousSimulation
{
public:
    char m_pad10[0xb8 - 0x10];
    hkMultithreadConfig m_config;                     // +0xb8
    char m_padc0[0x150 - 0xc0];
    unsigned char m_flag150;                          // +0x150
    char m_pad151[0x154 - 0x151];
    unsigned char m_flag154;                          // +0x154
    char m_pad155[0x1c0 - 0x155];
    hkCriticalSection m_broadphaseLock;               // +0x1c0
    void leaveBroadphaseCriticalSection();            // 0x0109c310
    void getMultithreadConfig(hkMultithreadConfig& config);            // 0x0109c330
    void setMultithreadConfig(const hkMultithreadConfig& config);      // 0x0109c350
};

// Operation dispatcher records: type byte at +4, signed byte delta to the real object at +5, and a second
// signed delta at +0x10 from the real object to its vtable sub-object.
class hkDispatchable
{
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3();
    virtual void d4(); virtual void d5();
    virtual void dispatch(void* arg);                 // slot 6 (+0x18)
    virtual void d7();
    virtual void dispatchAlt(void* arg);              // slot 8 (+0x20)
    unsigned char m_type;                             // +4
    signed char   m_offset;                           // +5
    char m_pad6[0xa];
    int m_vtableDelta;                                // +0x10
};

static inline hkDispatchable* dispatchTarget(hkDispatchable* o)
{
    hkDispatchable* p = (hkDispatchable*)((char*)o + o->m_offset);
    return (hkDispatchable*)((char*)p + p->m_vtableDelta);
}

static inline void* dispatchArg(hkDispatchable* o)
{
    return (char*)o + o->m_offset;
}

struct hkWorldCallbackUtil
{
    static void firePostSimulationCallback(hkWorld* world, const hkStepInfo* stepInfo);   // 0x0109f5a0
};

void FUN_0109bda0(hkDispatchable** p);                // 0x0109bda0
void FUN_0109c240(hkDispatchable** p);                // 0x0109c240
void FUN_0109c2a0(hkDispatchable** p);                // 0x0109c2a0

// @ 0x0109b490
void hkWorldOperationQueue::executeAllPending()
{
    if (m_criticalPending.m_size != 0)
    {
        if (m_criticalPending.m_size > 1)
            quickSortRecursive(m_criticalPending.m_data, 0, m_criticalPending.m_size - 1, opLess);
        m_pending.insertAt(0, m_criticalPending);
        m_criticalPending.m_size = 0;
    }

    hkInplaceArray<Op, 16> ops;
    ops.swap(m_pending);
    m_world->m_pendingOperationQueueCount++;

    for (int i = 0; i < ops.m_size; i++)
    {
        Op* op = &ops.m_data[i];
        switch (op->m_type)
        {
        case OP_ADD_ENTITY:
            if (op->entity()->m_world == 0)
                m_world->addEntity(op->entity(), (hkEntityActivation)op->m_w8);
            op->entity()->hkReferencedObject::removeReference();
            break;
        case OP_REMOVE_ENTITY:
            if (op->entity()->m_world == m_world)
                m_world->removeEntity(op->entity());
            op->entity()->hkReferencedObject::removeReference();
            break;
        case OP_SET_RIGID_BODY_MOTION_TYPE:
            op->body()->setMotionType(op->m_u.m_x, op->m_u.m_y, op->m_u.m_z);
            op->entity()->hkReferencedObject::removeReference();
            break;
        case OP_SET_SHAPE:
            op->entity()->setShape(op->shape());
            op->entity()->hkReferencedObject::removeReference();
            op->shape()->removeReference();
            break;
        case OP_ADD_ENTITY_BATCH:
            m_world->addEntityBatch(op->entities(), op->m_count, (hkEntityActivation)op->m_u.m_z);
            {
                hkEntity** it = op->entities();
                hkEntity** const end = it + op->m_count;
                for (; it < end; ++it)
                    (*it)->hkReferencedObject::removeReference();
            }
            freeBlock(op->m_a, op->m_count * 4, HK_MEMORY_CLASS_UNKNOWN4);
            break;
        case OP_REMOVE_ENTITY_BATCH:
            m_world->removeEntityBatch(op->entities(), op->m_count);
            {
                hkEntity** it = op->entities();
                hkEntity** const end = it + op->m_count;
                for (; it < end; ++it)
                    (*it)->hkReferencedObject::removeReference();
            }
            freeBlock(op->m_a, op->m_count * 4, HK_MEMORY_CLASS_UNKNOWN4);
            break;
        case OP_ADD_CONSTRAINT:
            if (op->constraint()->m_owner == 0 && op->constraint()->m_entities[0]->m_world == m_world &&
                op->constraint()->m_entities[1]->m_world == m_world)
                m_world->addConstraint(op->constraint());
            op->constraint()->removeReference();
            break;
        case OP_REMOVE_CONSTRAINT:
            if (op->constraint()->m_owner != 0)
                m_world->removeConstraint(op->constraint());
            op->constraint()->removeReference();
            break;
        case OP_ADD_ACTION:
            if (op->action()->m_world == 0)
            {
                hkArray<hkEntity*> entities(0, 0, 0);
                op->action()->getEntities(entities);
                int j = 0;
                for (; j < entities.m_size; j++)
                    if (entities.m_data[j]->m_world != m_world)
                        break;
                if (j == entities.m_size)
                    m_world->addAction(op->action());
            }
            op->action()->removeReference();
            break;
        case OP_REMOVE_ACTION:
            if (op->action()->m_island != 0)
                m_world->removeAction(op->action());
            op->action()->removeReference();
            break;
        case OP_MERGE_ISLANDS:
            if (op->entity()->m_world == m_world && op->entityB()->m_world == m_world && !op->entity()->m_fixed &&
                !op->entityB()->m_fixed && op->entity()->m_simulationIsland != op->entityB()->m_simulationIsland)
                hkWorldOperationUtil::mergeIslands(op->entity()->m_world, op->entity(), op->entityB());
            op->entity()->hkReferencedObject::removeReference();
            op->entityB()->hkReferencedObject::removeReference();
            break;
        case OP_ADD_PHANTOM:
            if (op->phantom()->m_world == 0)
                m_world->addPhantom(op->phantom());
            op->phantom()->hkReferencedObject::removeReference();
            break;
        case OP_REMOVE_PHANTOM:
            if (op->phantom()->m_world == m_world)
                m_world->removePhantom(op->phantom());
            op->phantom()->hkReferencedObject::removeReference();
            break;
        case OP_ADD_PHANTOM_BATCH:
            m_world->addPhantomBatch(op->phantoms(), op->m_count);
            {
                hkPhantom** it = op->phantoms();
                hkPhantom** const end = it + op->m_count;
                for (; it < end; ++it)
                    (*it)->hkReferencedObject::removeReference();
            }
            freeBlock(op->m_a, op->m_count * 4, HK_MEMORY_CLASS_UNKNOWN4);
            break;
        case OP_REMOVE_PHANTOM_BATCH:
            m_world->removePhantomBatch(op->phantoms(), op->m_count);
            {
                hkPhantom** it = op->phantoms();
                hkPhantom** const end = it + op->m_count;
                for (; it < end; ++it)
                    (*it)->hkReferencedObject::removeReference();
            }
            freeBlock(op->m_a, op->m_count * 4, HK_MEMORY_CLASS_UNKNOWN4);
            break;
        case OP_UPDATE_ENTITY_BP:
            if (op->entity()->m_world == m_world)
                hkWorldOperationUtil::updateEntityBP(m_world, op->entity());
            op->entity()->hkWorldObject::removeReference();
            break;
        case OP_UPDATE_PHANTOM_AABB:
            if (op->phantom()->m_world == m_world)
                op->phantom()->updateBroadPhase(*(hkAabb*)op->m_b);
            op->phantom()->hkReferencedObject::removeReference();
            freeBlock(op->m_b, 0x20, HK_MEMORY_CLASS_AABB);
            break;
        case OP_UPDATE_FILTER_ON_ENTITY:
            if (op->entity()->m_world == m_world)
                m_world->updateCollisionFilterOnEntity(op->entity(), op->m_u.m_x, op->m_u.m_y);
            op->entity()->hkReferencedObject::removeReference();
            break;
        case OP_UPDATE_FILTER_ON_PHANTOM:
            if (op->phantom()->m_world == m_world)
                m_world->updateCollisionFilterOnPhantom(op->phantom(), op->m_u.m_x);
            op->phantom()->hkReferencedObject::removeReference();
            break;
        case OP_UPDATE_FILTER_ON_WORLD:
            m_world->updateCollisionFilterOnWorld(op->m_b1, op->m_b2);
            break;
        case OP_UPDATE_MOVED_BODY_INFO:
            hkRigidBody::updateBroadphaseAndResetCollisionInformationOfWarpedBody(op->entity());
            op->entity()->hkReferencedObject::removeReference();
            break;
        case OP_SET_POSITION_AND_ROTATION:
            op->body()->setPositionAndRotation(*(hkVector4*)op->m_b, *(hkQuaternion*)((char*)op->m_b + 0x10));
            freeBlock(op->m_b, 0x20, HK_MEMORY_CLASS_UNKNOWN4);
            op->entity()->hkReferencedObject::removeReference();
            break;
        case OP_SET_LINEAR_VELOCITY:
        {
            hkVector4 v;
            v.m_q[0] = op->m_w8; v.m_q[1] = op->m_w0c; v.m_q[2] = op->m_w10; v.m_q[3] = 0;
            op->entity()->activate();
            op->entity()->m_motion->setLinearVelocity(v);
            op->entity()->hkReferencedObject::removeReference();
            break;
        }
        case OP_SET_ANGULAR_VELOCITY:
        {
            hkVector4 v;
            v.m_q[0] = op->m_w8; v.m_q[1] = op->m_w0c; v.m_q[2] = op->m_w10; v.m_q[3] = 0;
            op->entity()->activate();
            op->entity()->m_motion->setAngularVelocity(v);
            op->entity()->hkReferencedObject::removeReference();
            break;
        }
        case OP_APPLY_LINEAR_IMPULSE:
        {
            hkVector4 v;
            v.m_q[0] = op->m_w8; v.m_q[1] = op->m_w0c; v.m_q[2] = op->m_w10; v.m_q[3] = 0;
            op->entity()->activate();
            op->entity()->m_motion->applyLinearImpulse(v);
            op->entity()->hkReferencedObject::removeReference();
            break;
        }
        case OP_APPLY_POINT_IMPULSE:
            op->entity()->activate();
            op->entity()->m_motion->applyPointImpulse(((hkVector4*)op->m_b)[1], ((hkVector4*)op->m_b)[0]);
            freeBlock(op->m_b, 0x20, HK_MEMORY_CLASS_UNKNOWN4);
            op->entity()->hkReferencedObject::removeReference();
            break;
        case OP_APPLY_ANGULAR_IMPULSE:
        {
            hkVector4 v;
            v.m_q[0] = op->m_w8; v.m_q[1] = op->m_w0c; v.m_q[2] = op->m_w10; v.m_q[3] = 0;
            op->entity()->activate();
            op->entity()->m_motion->applyAngularImpulse(v);
            op->entity()->hkReferencedObject::removeReference();
            break;
        }
        case OP_ACTIVATE_REGION:
            m_world->activateRegion(*(hkAabb*)op->m_a);
            freeBlock(op->m_a, 0x20, HK_MEMORY_CLASS_UNKNOWN4);
            break;
        case OP_ACTIVATE_ENTITY:
            op->entity()->activate();
            op->entity()->hkReferencedObject::removeReference();
            break;
        case OP_DEACTIVATE_ENTITY:
            if (op->entity()->m_world == m_world)
                op->entity()->deactivate();
            op->entity()->hkReferencedObject::removeReference();
            break;
        case OP_RESET_COLLISION_INFO:
            m_world->m_simulation->resetCollisionInformationForEntities(op->entities(), op->m_count, m_world);
            {
                hkEntity** it = op->entities();
                hkEntity** const end = it + op->m_count;
                for (; it < end; ++it)
                    (*it)->hkReferencedObject::removeReference();
            }
            freeBlock(op->m_a, op->m_count * 4, HK_MEMORY_CLASS_UNKNOWN4);
            break;
        case OP_SET_PHANTOM_SHAPE:
            op->phantom()->setShape(op->shape());
            op->phantom()->hkReferencedObject::removeReference();
            break;
        default:
            break;
        }
        if (m_pending.m_size != 0)
            executeAllPending();
    }

    ops.swap(m_pending);
    m_pending.m_size = 0;
    m_world->m_pendingOperationQueueCount--;
}

// @ 0x0109BDA0
void FUN_0109bda0(hkDispatchable** p)
{
    if (p[0]->m_type == 2)
    {
        void* arg = dispatchArg(p[1]);
        dispatchTarget(p[0])->dispatch(arg);
    }
    if (p[1]->m_type != 2)
        return;
    return dispatchTarget(p[1])->dispatch(dispatchArg(p[0]));
}

// @ 0x0109C240
void FUN_0109c240(hkDispatchable** p)
{
    if (p[0]->m_type == 2)
    {
        void* arg = dispatchArg(p[1]);
        dispatchTarget(p[0])->dispatchAlt(arg);
    }
    if (p[1]->m_type == 2)
    {
        void* arg = dispatchArg(p[0]);
        dispatchTarget(p[1])->dispatchAlt(arg);
    }
}

// @ 0x0109C2A0
void FUN_0109c2a0(hkDispatchable** p)
{
    if (p[0]->m_type == 3)
    {
        if (p[1]->m_type == 3)
            return;
        dispatchTarget(p[0])->dispatch(dispatchArg(p[1]));
    }
    if (p[1]->m_type == 3)
        dispatchTarget(p[1])->dispatch(dispatchArg(p[0]));
}

// @ 0x0109C310
void hkMultiThreadedSimulation::leaveBroadphaseCriticalSection()
{
    hkCriticalSection* cs = &m_broadphaseLock;
    cs->m_ownerThread = -1;
    cs->m_recursionCount = -1;
    LeaveCriticalSection(cs);
}

// @ 0x0109C330
void hkMultiThreadedSimulation::getMultithreadConfig(hkMultithreadConfig& config)
{
    config.m_numThreads = m_config.m_numThreads;
    config.m_maxNumThreads = m_config.m_maxNumThreads;
}

// @ 0x0109C350
void hkMultiThreadedSimulation::setMultithreadConfig(const hkMultithreadConfig& config)
{
    m_config.m_numThreads = config.m_numThreads;
    m_config.m_maxNumThreads = config.m_maxNumThreads;
    unsigned char v;
    if (config.m_numThreads == 1)
        v = 2;
    else
        v = 3;
    m_flag150 = v;
    m_flag154 = v;
}

// @ 0x0109BE00
int hkAsynchronousSimulation::recoverFromStepFailure(hkWorld* world, int result)
{
    if (result == 1)
        return executeStep(world, 0, m_arg8);

    hkTime time(world->m_prevTime, world->m_endTime);

    world->updateCollisionFilterOnWorld(0, 1);
    if (hkMemory::s_instance->m_outOfMemory4 == 1)
        return 2;
    stepCollide(world, &time);
    if (hkMemory::s_instance->m_outOfMemory4 == 1)
        return 2;
    return executeStep(world, 0, m_arg8);
}

// @ 0x0109BED0
int hkAsynchronousSimulation::stepDeltaTime(hkWorld* world, float deltaTime, float maxDeltaTime)
{
    HK_TIMER_CMD("TtSimulate");

    m_f8 = maxDeltaTime;
    float newTime = deltaTime + world->m_currentTime;
    world->m_currentTime = newTime;
    if (world->m_endTime < newTime)
    {
        do
        {
            if (m_flagC != 0 &&
                fabsf(world->m_currentTime - world->m_endTime) < maxDeltaTime * 0.01f &&
                deltaTime / maxDeltaTime > 0.1f)
            {
                world->m_currentTime = world->m_endTime;
            }

            int estimate = world->calcMaxIslandSizeEstimate();
            hkThreadMemory* threadMemory = hkThreadMemory::getInstance();
            int& used = threadMemory->m_usedAt20;
            if (estimate > threadMemory->m_capacityAt2c - used - 0x10)
            {
                int total = hkMemory::s_instance->m_allocatedAt28 + hkMemory::s_instance->m_usedAt14;
                int available = (hkMemory::s_instance->m_freeAt08 > total)
                              ? hkMemory::s_instance->m_freeAt08 - total : 0;
                if (estimate > available)
                {
                    hkMemory::s_instance->m_outOfMemory4 = 1;
                    HK_TIMER_CMD(hkMonitorTimerEndTag);
                    return 1;
                }
            }

            world->m_prevTime = world->m_endTime;
            world->m_endTime = maxDeltaTime + world->m_endTime;

            const hkTime& time = hkTime(world->m_prevTime, world->m_endTime);

            world->m_solver->step(world, &time);
            world->m_stepTime0c = world->m_prevTime;
            postStep(world, &time);
            stepCollide(world, &time);

            if (hkMemory::s_instance->m_outOfMemory4 == 1)
            {
                HK_TIMER_CMD(hkMonitorTimerEndTag);
                return 2;
            }
        } while (world->m_endTime < world->m_currentTime);
    }

    world->m_stepTime0c = world->m_currentTime;
    HK_TIMER_CMD("TtPostSimulateCb");
    hkWorldCallbackUtil::firePostSimulationCallback(
        world, &hkStepInfo(world->m_currentTime - deltaTime, world->m_currentTime));
    HK_TIMER_CMD(hkMonitorTimerEndTag);
    HK_TIMER_CMD(hkMonitorTimerEndTag);
    return 0;
}
