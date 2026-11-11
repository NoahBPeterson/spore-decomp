// src/game/Havok/_at_010f0000.cpp -- migrated from slice(s) s010ff9e0, s010fdf80, s010fd4c0, s010fadd0, s010f7100, s010f3460, s010f25f0, s010f1350, s010ef580 by tools/migrate/rewrite.py
// Object file: Havok/_at_010f0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern uint32_t g_hkThreadMemoryTls;                    // 0x016e4174
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(uint32_t index);
#include <math.h>
#include <stddef.h>
#include <intrin.h>
#include <new>

// ---- items of slice s010ef580 begin (TODO(rewrite): local stubs, replace by canonical classes)
class hkThreadMemory
{
public:
    void deallocateChunk(void* chunk, uint32_t size, uint32_t alignment);
};
extern uint32_t g_hkThreadMemoryTls;                    // 0x016e4174
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(uint32_t index);
struct hkConvexPieceStreamData
{
    void*    mpVtable;      // +0x00
    uint32_t mPad04;
    void*    mpStream0;     // +0x08
    uint32_t mPad0c;
    int      mCount0;       // +0x10
    void*    mpStream1;     // +0x14
    uint32_t mPad18;
    int      mCount1;       // +0x1c
    void*    mpStream2;     // +0x20
    uint32_t mPad24;
    int      mCount2;       // +0x28
};
struct hkSolverInfo_s010e_f580
{
    struct Block8 { uint32_t mValue[8]; };

    uint32_t m00, m04, m08, m0c, m10;
    uint32_t m14, m18, m1c, m20, m24;
    uint32_t m28, m2c, m30, m34, m38;
    uint32_t m3c, m40, m44, m48, m4c;
    uint32_t m50, m54, m58, m5c, m60;
    Block8   m64, m84, ma4, mc4, me4, m104;
    uint32_t m124, m128, m12c, m130;

    hkSolverInfo_s010e_f580& operator=(const hkSolverInfo_s010e_f580& other);
};
class hkWorld_s010e_f580;
struct hkSimulationEntry
{
    float    mTime;         // +0x00
    uint8_t  mPad04[0x3c];
};
struct hkSimulation
{
    uint8_t  mPad00[0x18];
    hkSimulationEntry* mpEntries;   // +0x18
    int      mCount;                // +0x1c
};
class hkWorld_s010e_f580
{
public:
    uint8_t mPad00[8];
    hkSimulation* mpSimulation;     // +0x08
};
class hkContinuousSimulation
{
public:
    virtual void warpTime(hkWorld_s010e_f580* world, float deltaTime);
};
class hkEntity_s010e_f580
{
public:
    uint8_t  mPad00[0x58];
    void*    mpField58;     // +0x58
    uint8_t  mPad5c[0x9a - 0x5c];
    bool     mField9a;      // +0x9a
};
struct hkContactPoint_s010e_f580
{
    uint8_t  mPad00[0x10];
    uint32_t mField10, mField14, mField18, mField1c; // +0x10..+0x1c
};
struct hkToiEvent
{
    float    mTime;         // +0x00
    hkEntity_s010e_f580* mpBodyA;      // +0x04
    hkEntity_s010e_f580* mpBodyB;      // +0x08
    uint32_t mField0c;      // +0x0c
    uint32_t mField10;      // +0x10
    uint16_t mField14;      // +0x14
    uint8_t  mField16;      // +0x16
    uint16_t mPad17;        // +0x17
    uint32_t mField18;      // +0x18
    uint32_t mField1c;      // +0x1c
    hkContactPoint_s010e_f580 mContactPoint; // +0x20
    uint32_t mField30, mField34, mField38, mField3c; // +0x30..+0x3c
};
struct hkArrayEntity
{
    hkEntity_s010e_f580** mpData;      // +0x00
    int        mSize;       // +0x04
};
struct hkSolveParams
{
    uint32_t mField00, mField04, mField08, mField0c;
    float    mField10;
    float    mField14;
    uint32_t mField18;
    float    mField1c;
    float    mField20;
};
struct hkSolveOutput
{
    uint32_t mField0;       // +0x00
    float    mField4;       // +0x04
    float    mField8;       // +0x08
};
extern "C" void hkSolveSingleContact(const hkContactPoint_s010e_f580* cp, float time, const hkSolveParams* params,
                                     void* bodyA, void* bodyB, void* contactMgr, hkSolveOutput* output);
static void hkArrayAppend(hkArrayEntity& array, hkEntity_s010e_f580* entity)
{
    array.mpData[array.mSize] = entity;
    array.mSize++;
}
// ---- items of slice s010ef580 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" void hkSolveSingleContact(const hkContactPoint_s010e_f580* cp, float time, const hkSolveParams* params,
                                     void* bodyA, void* bodyB, void* contactMgr, hkSolveOutput* output);

// ---- items of slice s010f1350 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_hkMemory;                      // 0x016e4178
extern unsigned long g_hkMonitorStreamEndTls;   // 0x016e42a8
extern unsigned long g_hkMonitorStreamCurTls;   // 0x016e42a4
extern "C" __declspec(dllimport) int   __stdcall TlsSetValue(unsigned long, void*);
extern char vtable_Simulator_cCreatureAbility; // 0x013ef094 (the dtor's final vtable store)
void* FUN_01099cb0(int a, int b, int c);      // 0x01099cb0
void* FUN_0111ccf0();                         // 0x0111ccf0 hkDefaultToiResourceMgr ctor
void* FUN_0107db10(void* mem, int a, int b, int c);  // 0x0107db10 deallocateChunk
void FUN_0107f530(void* array, int elemSize);         // 0x0107f530 hkArray::grow
void* hkMemoryAlloc(int size, int align);     // hkMemory::s_instance vtable+0x10
extern unsigned long g_hkThreadMemoryTls_s010f_1350;     // 0x016e4174
struct hkMonitorStreamRecord
{
    const char* m_name;   // +0x00
    uint32_t m_time;      // +0x04 rdtsc low half
    uint32_t m_pad;       // +0x08
};
static __forceinline void HK_TIMER_SPLIT(const char* name)
{
    void* end = TlsGetValue(g_hkMonitorStreamEndTls);
    void* cur = TlsGetValue(g_hkMonitorStreamCurTls);
    if (cur < end) {
        hkMonitorStreamRecord* r = (hkMonitorStreamRecord*)TlsGetValue(g_hkMonitorStreamCurTls);
        r->m_name = name;
        r->m_time = (uint32_t)__rdtsc();
        TlsSetValue(g_hkMonitorStreamCurTls, (char*)r + sizeof(hkMonitorStreamRecord));
    }
}
struct AgentOutput;
struct AgentEntry;
struct ProcessCollisionInput;
void FUN_0120a260(float dt, void* motionState);           // 0x0120a260 backStepMotionState
struct hkRotation_s010f_1350;
void FUN_010fc180(AgentEntry* agent, ProcessCollisionInput* input, AgentOutput* output); // 0x010fc180 hkAgentNnMachine_processAgent
void FUN_010f0b00(int self, AgentEntry* agent, AgentOutput* output);   // 0x010f0b00 (thiscall)
struct AgentOutput
{
    void* mData;             // +0x00  points at mInline once initialised
    int mSize;               // +0x04
    int mCapacityAndFlags;   // +0x08
    char mPad0c[0x24];       // +0x0c
    char mInline[0x3004];    // +0x30  inline element storage (self-referenced by mData)
    union
    {
        float m3994;         // +0x3034 sentinel, compared with FLT_MAX
        int m3994Bits;
    };
    int mPad3038[2];         // +0x3038
    int m3998;               // +0x3040
};
struct hkpAgentNnTrack
{
    void** m_sectors;                  // +0x00
    int m_numSectors;                  // +0x04
    int m_sectorCapacityAndFlags;      // +0x08
    void* m_inlineSector;              // +0x0c  inline slot of hkInplaceArray<hkpAgentNnSector*,1>
    uint32_t m_bytesUsedInLastSector;  // +0x10
    uint16_t m_trackType;              // +0x14
    uint16_t m_sectorSize;             // +0x16  byte size of a full sector
};
struct AgentEntry
{
    char mPad00[3];     // +0x00
    uint8_t mSize;      // +0x03  stride to the next agent entry in the sector
    char mPad04[4];     // +0x04
    int8_t mState;      // +0x08  collision dispatcher state, indexes the job table
    char mPad09[7];     // +0x09
    void** mpOwner;     // +0x10  object whose vtable slot 5 is called back
    int mOwnerArg0;     // +0x14
    int mOwnerArg1;     // +0x18
};
struct ProcessCollisionInput
{
    int mTableBase;     // +0x00
    int mPad04[2];      // +0x04
    uint8_t mField0c;   // +0x0c
    char mPad0d[0x1b];  // +0x0d
    int mpJob;          // +0x28  selected job table entry
};
struct JobTableEntry
{
    char mPad00[0x10];   // +0x00
    uint8_t mKind;       // +0x10
};
struct HkMemory
{
    int mPad00;          // +0x00
    int mStopped;        // +0x04  set to 1 once the budget is exhausted
    int mTotal;          // +0x08
    int mPad0c[2];       // +0x0c
    int mUsedA;          // +0x14
    int mPad18[4];       // +0x18
    int mUsedB;          // +0x28
};
struct SimIsland
{
    char mPad00[0x4c];                  // +0x00
    hkpAgentNnTrack m_agentTrack;       // +0x4c
};
struct ContinuousSim {
    void* mVtable;              // +0x00
    char mPad04[2];             // +0x04
    unsigned short mField06;    // +0x06
    char mPad08[4];             // +0x08
    uint8_t mField0c;           // +0x0c
    char mPad0d[3];             // +0x0d
    int mOwner;                 // +0x10
    int mField14;               // +0x14
    void* mArrayData;           // +0x18  body-pointer array backing mCapacityAndFlags
    int mField1c;               // +0x1c
    int mCapacityAndFlags;      // +0x20  capacity in the low 30 bits, sign bit = allocated
    void* mResourceMgr;         // +0x24  hkDefaultToiResourceMgr
    int mField28;               // +0x28

    void resetEntities(int a, int b, int c);
    void collideIsland(SimIsland* island, ProcessCollisionInput* input);
    void processAgentCollide(AgentEntry* agent, ProcessCollisionInput* input, AgentOutput* output);
    void* scalarDelete(unsigned int flags);
    void destroy();             // 0x010f1a10
    void f0bb0(int a, int b);   // 0x010f0bb0
};
template <typename T> struct hkArray
{
    enum { CAPACITY_MASK = 0x3fffffff };
    T* m_data;                 // +0x00
    int m_size;                // +0x04
    int m_capacityAndFlags;    // +0x08
};
template <typename T> struct hkFixedArray { T* m_data; };
struct hkMotionState
{
    char m_transform[0x40];       // +0x00 hkTransform
    char m_sweptTransform[0x50];  // +0x40 hkSweptTransform
};
struct hkMotion_s010f_1350
{
    char mPad00[0x10];         // +0x00
    hkMotionState m_motionState; // +0x10
};
class hkConstraintInstance_s010f_1350;
struct hkConstraintInternal_s010f_1350
{
    hkConstraintInstance_s010f_1350* m_constraint;  // +0x00
    void* m_entities[2];                 // +0x04
    char mPad0c[0x10];                   // +0x0c
};
class hkConstraintInstance_s010f_1350
{
public:
    enum ConstraintPriority
    {
        CONSTRAINT_PRIORITY_INVALID = 0,
        CONSTRAINT_PRIORITY_PSI,
        CONSTRAINT_PRIORITY_TOI,
        CONSTRAINT_PRIORITY_TOI_HIGHER,
        CONSTRAINT_PRIORITY_TOI_FORCED,
        CONSTRAINT_PRIORITY_SIMULATION_CONTROL,
        CONSTRAINT_PRIORITY_MAX
    };

    char mPad00[0x18];                   // +0x00
    uint8_t m_priority;                  // +0x18
    char mPad19[0x0b];                   // +0x19
    hkConstraintInternal_s010f_1350* m_internal;    // +0x24
};
class hkEntity_s010f_1350
{
public:
    char mPad00[0x58];                                   // +0x00
    hkMotion_s010f_1350* m_motion;                                  // +0x58
    char mPad5c[0x14];                                   // +0x5c
    hkArray<hkConstraintInternal_s010f_1350> m_constraintsMaster;   // +0x70
    hkArray<hkConstraintInstance_s010f_1350*> m_constraintsSlave;   // +0x7c
    char mPad88[0x0c];                                   // +0x88
    uint16_t m_storageIndex;                             // +0x94
    char mPad96[3];                                      // +0x96
    bool m_fixed;                                        // +0x99
};
void FUN_010f0d60(hkEntity_s010f_1350* entity, int priority, void* input, float time, void* flags);
void FUN_01209c50(void* sweptTransform, float time, void* transform);
struct ConstraintObject;
struct SimObjectRef
{
    ConstraintObject* mObject;  // +0   points at an hkConstraintInstance-like object
    int mIndex;                 // +4   index passed to the velocity test
    int mPad8;                  // +8
};
struct EntityKind
{
    int mPad0[6];    // +0x00
    uint8_t mKind;   // +0x18 (compared with 4)
};
struct ConstraintSub
{
    int mPad0[8];   // +0x00
    int mField20;   // +0x20
    int mPad24[5];  // +0x24
    int mField38;   // +0x38
};
struct ConstraintObject
{
    int mPad0[3];           // +0x00
    ConstraintSub* mSub;    // +0x0c
};
struct SolverState
{
    int mPad0[2];   // +0x00
    int mField8;    // +0x08
};
struct ConstraintContext
{
    SolverState* mSolver;   // +0x00
    int mId;                // +0x04
    int mPad08;             // +0x08
    int mFlags;             // +0x0c
    int mPad10;             // +0x10
    int mParam;             // +0x14
};
struct SolveResult
{
    void* mObject;   // +0
    int mField1;     // +4
    int mField2;     // +8
};
struct ConstraintArray
{
    SimObjectRef* mData;   // +0
    int mSize;             // +4
};
struct ResultArray
{
    void* mData;           // +0
    int mSize;             // +4
    int mCapacityAndFlags; // +8
};
int FUN_010b1d70(int a, int b, int c, int d, int e, void* out);
int FUN_010f0e90(int a, SimObjectRef* ref, const void* buf, int d, int e);
struct FlagList
{
    char* mData;   // +0
};
struct hkRotation_s010f_1350
{
    float m_el[12];               // +0x00  three columns of four floats
    void set(const void* quat);   // 0x010824a0 hkRotation::set
};
struct MotionState
{
    char mPad00[0x10];              // +0x00
    hkRotation_s010f_1350 mRotation;           // +0x10
    union
    {
        float mDerived[4];          // +0x40  position after the rotation update
        int mDerivedBits[4];
    };
    union
    {
        float mStepDerived[4];      // +0x50  backstepped copy of mPosition
        int mStepDerivedBits[4];
    };
    union
    {
        float mPosition[4];         // +0x60  world position
        int mPositionBits[4];
    };
    union
    {
        float mStepPosition[4];     // +0x70  backstepped copy of mQuatSource
        int mStepPositionBits[4];
    };
    union
    {
        float mQuatSource[4];       // +0x80  quaternion fed to hkRotation::set
        int mQuatSourceBits[4];
    };
    float mAxis[4];                 // +0x90  axis the position increment is projected on
};
struct TimeStep
{
    int mPad0[6];      // +0x00
    float mEndTime;    // +0x18
};
struct Entity;
struct Island
{
    char mPad00[0x1c];      // +0x00
    TimeStep* mTimeStep;    // +0x1c
    char mPad20[0x1c];      // +0x20
    Entity** mBodies;       // +0x3c
    int mBodyCount;         // +0x40
};
struct Entity
{
    char mPad00[0x58];      // +0x00
    MotionState* mMotion;   // +0x58
};
// ---- items of slice s010f1350 end

// ---- items of slice s010f25f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef float hkReal;
static __forceinline void HK_TIMER_SPLIT_s010f_25f0(const char* name)
{
    void* end = TlsGetValue(g_hkMonitorStreamEndTls);
    void* cur = TlsGetValue(g_hkMonitorStreamCurTls);
    if (cur < end) {
        hkMonitorStreamRecord* r = (hkMonitorStreamRecord*)TlsGetValue(g_hkMonitorStreamCurTls);
        r->m_name = name;
        r->m_time = (uint32_t)__rdtsc();
        TlsSetValue(g_hkMonitorStreamCurTls, r + 1);
    }
}
extern unsigned long g_hkThreadMemoryTls_s010f_25f0;      // 0x016e4174
class hkThreadMemory_s010f_25f0 { public:
    virtual void vslot0();
    virtual void vslot1();
    virtual void vslot2();
    virtual void* onStackOverflow(int numBytes);         // +0x0c 0x0107dc10
    virtual void onStackUnderflow(void* p);               // +0x10 0x0107db90
    uint32_t pad04[7];        // +0x04 .. +0x1f
    char* m_stackCurrent;     // +0x20
    char* m_stackPrev;        // +0x24
    char* m_stackBase;        // +0x28
    char* m_stackEnd;         // +0x2c
    void deallocateChunk(void* p, int numBytes, int memoryClass);          // 0x0107DB10

    static __forceinline hkThreadMemory_s010f_25f0& getInstance() { return *(hkThreadMemory_s010f_25f0*)TlsGetValue(g_hkThreadMemoryTls_s010f_25f0); }
};
enum { HK_MEMORY_CLASS_ARRAY = 0x14 };
template <typename T> __forceinline T* hkAllocateStack(int n)
{
    hkThreadMemory_s010f_25f0& tm = hkThreadMemory_s010f_25f0::getInstance();
    int size = (n * (int)sizeof(T) + 0x10) & ~0xf;
    char* cur = tm.m_stackCurrent;
    char* next = cur + size;
    if ((uint32_t)next > (uint32_t)tm.m_stackEnd)
        return (T*)tm.onStackOverflow(size);
    tm.m_stackCurrent = next;
    return (T*)cur;
}
template <typename T> __forceinline void hkDeallocateStack(T* p)
{
    hkThreadMemory_s010f_25f0& tm = hkThreadMemory_s010f_25f0::getInstance();
    tm.m_stackCurrent = (char*)p;
    if ((char*)p == tm.m_stackBase)
        tm.onStackUnderflow(p);
}
struct hkArrayUtil {
    static void _reserveExactly(void* array, int newCapacity, int elemSize);   // 0x0107F4A0
};
template <typename T> class hkArray_s010f_25f0 { public:
    enum { CAPACITY_MASK = 0x3fffffff, DONT_DEALLOCATE_FLAG = 0x80000000 };
    T* m_data;
    int m_size;
    int m_capacityAndFlags;

    hkArray_s010f_25f0() : m_data(0), m_size(0), m_capacityAndFlags(DONT_DEALLOCATE_FLAG) {}
    hkArray_s010f_25f0(T* buffer, int size, int capacity) : m_data(buffer), m_size(size), m_capacityAndFlags(capacity | DONT_DEALLOCATE_FLAG) {}
    __forceinline ~hkArray_s010f_25f0() { releaseMemory(); }
    __forceinline void releaseMemory()
    {
        if ((m_capacityAndFlags & DONT_DEALLOCATE_FLAG) == 0)
            hkThreadMemory_s010f_25f0::getInstance().deallocateChunk(m_data, getCapacity() * sizeof(T), HK_MEMORY_CLASS_ARRAY);
    }
    int getSize() const { return m_size; }
    int getCapacity() const { return m_capacityAndFlags & CAPACITY_MASK; }
    T& operator[](int i) { return m_data[i]; }
    void clear() { m_size = 0; }
    __forceinline void pushBackUnchecked(const T& t) { m_data[m_size] = t; m_size++; }
    __forceinline void removeAt(int index) { m_data[index] = m_data[--m_size]; }
    __forceinline void reserve(int n)
    {
        if (getCapacity() < n) {
            int cap2 = 2 * getCapacity();
            int newSize = (n < cap2) ? cap2 : n;
            hkArrayUtil::_reserveExactly(this, newSize, sizeof(T));
        }
    }
    void insertAt(int index, const hkArray_s010f_25f0<T>& a);       // 0x010FBB80 (hkArray<T*> instance)
};
template <typename T, int N> class hkInplaceArray : public hkArray_s010f_25f0<T> { public:
    T m_storage[N];
    __forceinline hkInplaceArray() : hkArray_s010f_25f0<T>(m_storage, 0, N) {}
};
template <typename T> struct hkLocalArray : hkArray_s010f_25f0<T> {
    T* m_localMemory;
    __forceinline hkLocalArray(int capacity)
    {
        this->m_data = hkAllocateStack<T>(capacity);
        this->m_capacityAndFlags = capacity | hkArray_s010f_25f0<T>::DONT_DEALLOCATE_FLAG;
        m_localMemory = this->m_data;
    }
    __forceinline ~hkLocalArray() { hkDeallocateStack(m_localMemory); }
};
template <typename T> struct hkFixedArray_s010f_25f0 { T* m_data; T& operator[](int i) { return m_data[i]; } };
class hkBool_s010f_25f0 { public:
    char m_bool;
    operator bool() const { return m_bool != 0; }
};
struct hkStepInfo_s010f_25f0;
struct hkSolverInfo_s010f_25f0;
struct hkVelocityAccumulator;
struct hkConstraintInstance_s010f_25f0;
class hkSimulationIsland_s010f_25f0;
struct hkTransform_s010f_25f0;
struct hkSweptTransform;
struct hkCollidable_s010f_25f0;
class hkMotionState_s010f_25f0 { public:
    char m_transform[0x40];                          // +0x00 hkTransform
    char m_sweptTransform[0x50];                     // +0x40 hkSweptTransform
};
class hkMotion_s010f_25f0 { public:
    virtual void vslot0();
    virtual void vslot1();
    virtual int getType();                           // +0x08
    int pad04[3];
    hkMotionState_s010f_25f0 m_motionState;                     // +0x10
};
enum { HK_MOTION_FIXED = 6 };
class hkEntity_s010f_25f0 { public:
    char pad00[0x1c];
    char m_collidable[0x30];                         // +0x1c hkLinkedCollidable
    char pad4c[0x58 - 0x4c];
    hkMotion_s010f_25f0* m_motion;                              // +0x58
    hkSimulationIsland_s010f_25f0* m_simulationIsland;          // +0x5c
    char pad60[0x94 - 0x60];
    uint16_t m_storageIndex;                         // +0x94
    char pad96[0x99 - 0x96];
    bool m_fixed;                                    // +0x99
    char pad9a[0xa0 - 0x9a];
    void* m_contactPointConfirmedListeners;          // +0xa0 (array data; non-null = has listeners)
    const hkCollidable_s010f_25f0* getCollidable() const { return (const hkCollidable_s010f_25f0*)m_collidable; }
};
class hkSimulationIsland_s010f_25f0 { public:
    char pad00[0x3c];
    hkArray_s010f_25f0<hkEntity_s010f_25f0*> m_entities;                   // +0x3c
};
struct hkProcessCollisionInput_s010f_25f0;
class hkWorld_s010f_25f0 { public:
    char pad00[0x78];
    hkProcessCollisionInput_s010f_25f0* m_collisionInput;       // +0x78
    char pad7c[0xc0 - 0x7c];
    hkReal m_toiCollisionResponseRotateNormal;       // +0xc0
};
struct hkContactPoint_s010f_25f0;
class hkContactPointMaterial { public: void* m_userData; uint16_t m_friction; uint8_t m_restitution; uint8_t m_flags; };
struct hkToiEvent_s010f_25f0 {                                  // 0x40
    hkReal m_time;                                   // +0x00
    hkEntity_s010f_25f0* m_entities[2];                         // +0x04
    hkReal m_seperatingVelocity;                     // +0x0c
    hkContactPointMaterial m_material;               // +0x10
    void* m_contactMgr;                              // +0x18
    uint32_t pad1c;
    char m_contactPoint[0x20];                       // +0x20 hkContactPoint
};
struct hkToiResources {                              // 0x20
    int m_priority;                                  // +0x00 hkConstraintInstance::ConstraintPriority used for the expansion
    int m_maxNumActiveEntities;                      // +0x04
    int m_maxNumEntities;                            // +0x08
    int m_maxNumConstraints;                         // +0x0c
    int m_numToiSolverIterations;                    // +0x10
    int m_numForcedToiFinalSolverIterations;         // +0x14
    char* m_scratchpad;                              // +0x18
    int m_scratchpadSize;                            // +0x1c
};
struct hkConstraintSchemaInfo {                      // 12 bytes
    hkConstraintInstance_s010f_25f0* m_constraint;
    void* m_schema;
    hkReal m_allowedPenetrationDepth;
};
struct hkSchemaStream { void* m_begin; void* m_f04; void* m_current; void* m_f0c; };
struct hkConstraintSolverResources {
    hkStepInfo_s010f_25f0* m_stepInfo;                          // +0x00
    hkSolverInfo_s010f_25f0* m_solverInfo;                      // +0x04
    void* m_constraintQueryIn;                       // +0x08
    hkVelocityAccumulator* m_accumulators;           // +0x0c
    void* m_accumulatorsCurrent;                     // +0x10
    void* m_elemTemp;                                // +0x14
    void* m_elemTempCurrent;                         // +0x18
    void* m_solverResults;                           // +0x1c
    void* m_f20;                                     // +0x20
    hkSchemaStream m_schemas[2];                     // +0x24 (normal priority), +0x34 (TOI priority)
};
struct hkContactPointConfirmedEvent {                // 0x24
    const hkCollidable_s010f_25f0* m_collidableA;               // +0x00
    const hkCollidable_s010f_25f0* m_collidableB;               // +0x04
    hkEntity_s010f_25f0* m_callbackFiredFrom;                   // +0x08 (set by the fire functions)
    hkContactPoint_s010f_25f0* m_contactPoint;                  // +0x0c
    hkContactPointMaterial* m_contactPointMaterial;  // +0x10
    hkReal m_rotateNormal;                           // +0x14
    hkReal m_projectedVelocity;                      // +0x18
    int m_type;                                      // +0x1c (0 = TYPE_TOI)
    void* m_contactData;                             // +0x20
    hkContactPointConfirmedEvent(int type, const hkCollidable_s010f_25f0* a, const hkCollidable_s010f_25f0* b, void* data,
                                 hkContactPoint_s010f_25f0* cp, hkContactPointMaterial* cpm, hkReal rotateNormal, hkReal projectedVelocity)
        : m_collidableA(a), m_collidableB(b), m_contactPoint(cp), m_contactPointMaterial(cpm),
          m_rotateNormal(rotateNormal), m_projectedVelocity(projectedVelocity), m_type(type), m_contactData(data) {}
};
struct hkConstraintViolationInfo { hkConstraintInstance_s010f_25f0* m_constraint; void* m_contactPoint; void* m_contactPointProperties; };
enum hkToiResourceMgrResponse {
    HK_TOI_RESOURCE_MGR_RESPONSE_CONTINUE = 0,
    HK_TOI_RESOURCE_MGR_RESPONSE_DO_NOT_EXPAND_AND_CONTINUE = 1,
    HK_TOI_RESOURCE_MGR_RESPONSE_BACKSTEP = 2
};
struct hkToiResourceMgr {
    virtual void vslot0();
    virtual void vslot1();
    virtual void vslot2();
    virtual void vslot3();                           // +0x0c beginToiAndSetupResources
    virtual hkToiResourceMgrResponse cannotSolve(hkArray_s010f_25f0<hkConstraintViolationInfo>& violatedConstraints);   // +0x10
    virtual hkToiResourceMgrResponse resourcesDepleted();                                                   // +0x14
};
enum {
    HK_ENTITY_STATE_NOT_ACTIVE = 0,
    HK_ENTITY_STATE_TRANSFORM_UPDATED = 1,
    HK_ENTITY_STATE_ACTIVE = 2,
    HK_ENTITY_STATE_FROZEN = 8
};
struct hkWorldCallbackUtil {
    static void fireContactPointConfirmed(hkWorld_s010f_25f0* world, hkContactPointConfirmedEvent& event);              // 0x0109F0D0
};
struct hkEntityCallbackUtil {
    static void fireContactPointConfirmedInternal(hkEntity_s010f_25f0* entity, hkContactPointConfirmedEvent& event);    // 0x0109E850
};
struct hkSweptTransformUtil {
    static void lerp2(const hkSweptTransform& sweptTrans, hkReal t, hkTransform_s010f_25f0& transformOut);             // 0x01209C50
    static void backStepMotionState(hkReal time, hkMotionState_s010f_25f0& motionState);                               // 0x0120A260
};
struct hkConstraintSolverSetup {
    static void internalAddAccumulators(hkConstraintSolverResources& r, hkEntity_s010f_25f0** entities, int n);        // 0x010A4D10
    static hkBool_s010f_25f0 internalIsMemoryOkForNewAccumulators(hkConstraintSolverResources& r, hkEntity_s010f_25f0** entities, int n);   // 0x010A4DE0
    static void internalAddJacobianElements(hkConstraintSolverResources& r, hkConstraintInstance_s010f_25f0** constraints, int n,
                                            hkArray_s010f_25f0<hkConstraintSchemaInfo>& schemas);                     // 0x010A4E40
    static hkBool_s010f_25f0 internalIsMemoryOkForNewJacobianElements(hkConstraintSolverResources& r, hkConstraintInstance_s010f_25f0** c, int n);   // 0x010A4FB0
    static void oneStepIntegrate(const hkStepInfo_s010f_25f0& info, hkEntity_s010f_25f0** entities, int n, hkVelocityAccumulator* acc);   // 0x010A4CA0
    static void resetSolverBuffers(hkConstraintSolverResources& r, int flag);                               // 0x010A49E0
};
void hkSolver_solveJacobianSchemas(hkSolverInfo_s010f_25f0* info, void* schemas, hkVelocityAccumulator* accumulators,
                                   void* elemTemp, void* results);                                         // 0x010B48B0
void hkConstraintSolverResources_noop();                                                                   // 0x00C2E4E0 (empty)
void hkLs_doSimpleCollisionResponse(hkWorld_s010f_25f0* world, const hkToiEvent_s010f_25f0& event, hkReal rotateNormal,
                                    hkArray_s010f_25f0<hkEntity_s010f_25f0*>& toBeActivated);                                    // 0x010F03D0
void hkLs_toiCheckValidityOfConstraints(hkConstraintSolverResources& r, hkProcessCollisionInput_s010f_25f0& input,
                                        hkArray_s010f_25f0<hkConstraintSchemaInfo>& schemas, int& firstNonActiveSchema,
                                        int priority, hkFixedArray_s010f_25f0<unsigned char>& flags,
                                        const hkArray_s010f_25f0<hkEntity_s010f_25f0*>& activeEntities, hkArray_s010f_25f0<hkEntity_s010f_25f0*>& toBeActivated);   // 0x010F0F90
void hkLs_toiActivateEntitiesAndCheckConstraints(hkProcessCollisionInput_s010f_25f0& input, int priority, hkReal time,
                                                 const hkArray_s010f_25f0<hkEntity_s010f_25f0*>& toBeActivated, hkFixedArray_s010f_25f0<unsigned char>& flags,
                                                 hkArray_s010f_25f0<hkEntity_s010f_25f0*>& newEntities, hkArray_s010f_25f0<hkConstraintInstance_s010f_25f0*>& newConstraints);   // 0x010F1350
void hkLs_backstepAndFreezeEntireIsland(hkReal time, hkSimulationIsland_s010f_25f0* island, hkFixedArray_s010f_25f0<unsigned char>& flags,
                                        hkArray_s010f_25f0<hkEntity_s010f_25f0*>& entitiesOut);                                  // 0x010F17F0
void hkLs_restoreTransformOnBodiesWithUpdatedTransform(hkSimulationIsland_s010f_25f0* island, hkFixedArray_s010f_25f0<unsigned char>& flags);   // 0x010F18D0
void hkLs_sortSchemasOfFixedEntitiesFirst(hkArray_s010f_25f0<hkConstraintSchemaInfo>& schemas, int& firstNonActiveSchema, int numNew);   // 0x010F0610
void hkLs_sortSchemasOfFrozenEntitiesFirst(hkArray_s010f_25f0<hkConstraintSchemaInfo>& schemas, int& firstNonActiveSchema,
                                           hkFixedArray_s010f_25f0<unsigned char>& flags);                            // 0x010F06D0
void hkLs_copyVelocitiesToAccumulators(hkConstraintSolverResources& r, hkArray_s010f_25f0<hkEntity_s010f_25f0*>& entities);      // 0x010F0790
hkBool_s010f_25f0 hkLs_areConstraintsSatisfied(hkConstraintSolverResources& r, hkArray_s010f_25f0<hkConstraintSchemaInfo>& schemas,
                                    hkProcessCollisionInput_s010f_25f0* input, hkArray_s010f_25f0<hkConstraintViolationInfo>* violatedOut);   // 0x010F1690
void hkLs_invalidateTimsOfEntity(hkEntity_s010f_25f0* entity, hkProcessCollisionInput_s010f_25f0* input);                        // 0x010A3890
static __forceinline void hkLs_invalidateTims(hkArray_s010f_25f0<hkEntity_s010f_25f0*>& entities, hkWorld_s010f_25f0* world)
{
    for (int i = 0; i < entities.getSize(); i++)
        hkLs_invalidateTimsOfEntity(entities[i], world->m_collisionInput);
}
// ---- items of slice s010f25f0 end

// ---- items of slice s010f3460 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float hkRealOne;      // 0x01485720 (1.0f)
extern bool g_hkSolverKeycodeValid;                                              // 0x016E5ABD
#ifndef _WIN64
#else
#endif
#define HK_REAL_MAX 3.40282e+38f      // 0x7f7fffee in this build (not FLT_MAX)
template <typename T> class hkArray_s010f_3460 { public: T* m_data; int32_t m_size; int32_t m_capacityAndFlags; };
struct hkMonitorStreamListRecord { const char* m_name; uint32_t m_time; uint32_t m_pad; const char* m_nameOfFirstSplit; };
static inline void hkMonitorStamp(const char* name)
{
    void* end = TlsGetValue(g_hkMonitorStreamEndTls);
    void* cur = TlsGetValue(g_hkMonitorStreamCurTls);
    if (cur < end) {
        hkMonitorStreamRecord* r = (hkMonitorStreamRecord*)TlsGetValue(g_hkMonitorStreamCurTls);
        r->m_name = name;
        r->m_time = (uint32_t)__rdtsc();
        TlsSetValue(g_hkMonitorStreamCurTls, r + 1);
    }
}
static inline void hkMonitorStampList(const char* listName, const char* firstSplit)
{
    void* end = TlsGetValue(g_hkMonitorStreamEndTls);
    void* cur = TlsGetValue(g_hkMonitorStreamCurTls);
    if (cur < end) {
        hkMonitorStreamListRecord* r = (hkMonitorStreamListRecord*)TlsGetValue(g_hkMonitorStreamCurTls);
        r->m_name = listName;
        r->m_nameOfFirstSplit = firstSplit;
        r->m_time = (uint32_t)__rdtsc();
        TlsSetValue(g_hkMonitorStreamCurTls, r + 1);
    }
}
class hkMemory { public:
    void** vftable;                    // +0x00
    int m_memoryState;                 // +0x04 (1 = MEMORY_STATE_OUT_OF_MEMORY)
    int m_criticalMemoryLimit;         // +0x08
    int m_referenceCount;              // +0x0c
    int m_sysAllocs0;                  // +0x10
    int m_sysAllocsSize;               // +0x14
    int m_stats8, m_stats0c, m_stats10, m_stats14;   // +0x18..+0x27
    int m_pageMemoryUsed;              // +0x28
};
extern hkMemory* g_hkMemoryInstance;           // 0x016e4178 (hkMemory::s_instance)
extern unsigned long g_hkThreadMemoryTls_s010f_3460;      // 0x016e4174
struct hkThreadMemoryRaw {
    void** vftable;           // +0x00
    char pad[0x1c];           // +0x04 .. +0x1f
    char* m_stackCurrent;     // +0x20
    char* m_stackPrev;        // +0x24
    char* m_stackBase;        // +0x28
    char* m_stackEnd;         // +0x2c
    void deallocateChunk(void* p, int numBytes, int memoryClass);          // 0x0107DB10
};
static inline hkThreadMemoryRaw* hkThreadMemoryGet() { return (hkThreadMemoryRaw*)TlsGetValue(g_hkThreadMemoryTls_s010f_3460); }
static inline char* hkAllocateStackChars(int n)
{
    hkThreadMemoryRaw* tm = hkThreadMemoryGet();
    int size = (n + 0x10) & ~0xf;
    char* cur = tm->m_stackCurrent;
    char* next = cur + size;
    if ((uint32_t)next > (uint32_t)tm->m_stackEnd)
        return (char*)((void* (__thiscall*)(hkThreadMemoryRaw*, int))((void**)tm->vftable)[3])(tm, size);
    tm->m_stackCurrent = next;
    return cur;
}
static inline void hkDeallocateStackChars(char* p)
{
    hkThreadMemoryRaw* tm = hkThreadMemoryGet();
    tm->m_stackCurrent = p;
    if (p == tm->m_stackBase)
        ((void(__thiscall*)(hkThreadMemoryRaw*, char*))((void**)tm->vftable)[4])(tm, p);
}
static inline void hkArrayDeallocate(void* data, int capacityAndFlags, int elemSize)
{
    if (capacityAndFlags >= 0)
        hkThreadMemoryGet()->deallocateChunk(data, (capacityAndFlags & 0x3fffffff) * elemSize, 0x14);
}
void hkString_memSet(void* dst, int value, int n);                       // 0x0107F470 (cdecl)
__declspec(align(16)) struct hkVector4 { float x, y, z, w; };
class hkStepInfo_s010f_3460 { public:
    float m_startTime;      // +0x0
    float m_endTime;        // +0x4
    float m_deltaTime;      // +0x8
    float m_invDeltaTime;   // +0xc
    hkStepInfo_s010f_3460() {}
    hkStepInfo_s010f_3460(float startTime, float endTime);                          // 0x01099430 (out of line)
};
struct hkSolverInfo_s010f_3460 {                    // 0x140 bytes
    float m_one;                         // +0x00
    float m_tau;                         // +0x04
    float m_damping;                     // +0x08
    float m_frictionTau;                 // +0x0c
    hkVector4 m_globalAccelerationPerSubStep;   // +0x10
    hkVector4 m_globalAccelerationPerStep;      // +0x20
    char pad30[0x54 - 0x30];
    float m_tauDivDamp;                  // +0x54
    float m_dampDivFrictionTau;          // +0x58
    float m_frictionTauDivDamp;          // +0x5c
    char pad60[0x124 - 0x60];
    float m_deltaTime;                   // +0x124
    float m_invDeltaTime;                // +0x128
    int m_numSteps;                      // +0x12c
    float m_invNumSteps;                 // +0x130
    char pad134[0x140 - 0x134];
    hkSolverInfo_s010f_3460& operator=(const hkSolverInfo_s010f_3460& other);                  // 0x010F0260 (out of line)
    void setTauAndDamping(float tau, float damping);                     // 0x01082890
};
struct hkConstraintSolverResources_s010f_3460 { char m_data[0x30]; };               // layout owned by hkConstraintSolverSetup
void hkConstraintSolverResources_destruct(hkConstraintSolverResources_s010f_3460*); // 0x00C2E4E0 (empty body, `ret`)
class hkConstraintQueryIn { public:
    float m_substepDeltaTime;            // +0x00
    float m_substepInvDeltaTime;         // +0x04
    float m_frameDeltaTime;              // +0x08
    float m_frameInvDeltaTime;           // +0x0c
    float m_virtualMassFactor;           // +0x10 (solverInfo.m_invNumSteps)
    float m_rhsFactor;                   // +0x14 (tauDivDamp * invDeltaTime)
    float m_dampingFactor;               // +0x18 (damping)
    float m_frictionRhsFactor;           // +0x1c (frictionTauDivDamp * invDeltaTime)
    void* m_resultsBegin;                // +0x20 (copied from the solver resources)
    int m_resultsSize;                   // +0x24
    char pad28[0x38 - 0x28];
    float m_tau;                         // +0x38
    float m_damping;                     // +0x3c
    char pad40[0x48 - 0x40];
};
struct hkConstraintSolverSetup_s010f_3460 {
    static void initializeSolverState(hkStepInfo_s010f_3460& stepInfo, hkSolverInfo_s010f_3460& solverInfo, hkConstraintQueryIn& queryIn,
                                      char* buffer, int bufferSize, hkConstraintSolverResources_s010f_3460& resources);   // 0x010A48F0
};
class hkContactPoint_s010f_3460 { public: hkVector4 m_position; hkVector4 m_separatingNormal; };      // 0x20
struct hkProcessCdPoint { hkContactPoint_s010f_3460 m_contact; uint16_t m_contactPointId; char pad[14]; };                   // 0x30
struct hkProcessCollisionOutput {                    // hkProcessCollisionData + m_potentialContacts, 0x3050
    hkProcessCdPoint* m_firstFreeContactPoint;       // +0x0000
    hkContactPoint_s010f_3460 m_toiContactPoint;                // +0x0010
    hkProcessCdPoint m_contactPoints[256];           // +0x0030
    float m_toiSeperatingVelocity;                   // +0x3030
    float m_toi;                                     // +0x3034
    hkContactPointMaterial m_toiMaterial;            // +0x3038
    void* m_potentialContacts;                       // +0x3040
    hkProcessCollisionOutput() {}
};
struct hkCollisionQualityInfo_s010f_3460 {                      // 0x3c
    char pad00[0x10];
    bool m_useContinuousPhysics;                     // +0x10
    char pad11[0x3c - 0x11];
};
class hkCollisionDispatcher_s010f_3460 { public:
    char pad[0x1a14];
    hkCollisionQualityInfo_s010f_3460 m_collisionQualityInfo[8];   // +0x1a14
};
struct hkProcessCollisionInput_s010f_3460 {
    hkCollisionDispatcher_s010f_3460* m_dispatcher;             // +0x00
    void* m_filter;                                  // +0x04
    float m_tolerance;                               // +0x08
    bool m_createPredictiveAgents;                   // +0x0c
    hkStepInfo_s010f_3460 m_stepInfo;                           // +0x10
    void* m_config;                                  // +0x20
    void* m_dynamicsInfo;                            // +0x24
    hkCollisionQualityInfo_s010f_3460* m_collisionQualityInfo;  // +0x28
};
class hkEntity_s010f_3460;
class hkSimulationIsland_s010f_3460;
class hkWorld_s010f_3460;
class hkContactMgr;
class hkLinkedCollidable_s010f_3460;
struct hkCollisionEntry { struct hkAgentNnEntry_s010f_3460* m_agentEntry; hkLinkedCollidable_s010f_3460* m_partner; };
class hkLinkedCollidable_s010f_3460 { public:                          // hkCollidable (0x24) + entries
    char pad00[0x10];
    int m_ownerOffset;                               // +0x10
    char pad14[0x24 - 0x14];
    hkArray_s010f_3460<hkCollisionEntry> m_collisionEntries;    // +0x24
    hkEntity_s010f_3460* getOwner() { return (hkEntity_s010f_3460*)((char*)this + m_ownerOffset); }
};
struct hkAgentNnEntry_s010f_3460 {
    uint8_t m_streamCommand, m_agentType, m_numContactPoints, m_size;   // +0x00
    uint32_t m_userData;                             // +0x04
    int8_t m_collisionQualityIndex;                  // +0x08
    char pad09[3];
    uint16_t m_agentIndexOnCollidable[2];            // +0x0c
    hkContactMgr* m_contactMgr;                      // +0x10
    hkLinkedCollidable_s010f_3460* m_collidable[2];             // +0x14
};
class hkContactMgr { public:
    virtual void vslot0();
    virtual void vslot1();
    virtual void vslot2();
    virtual void vslot3();
    virtual void vslot4();
    virtual void processContact(hkLinkedCollidable_s010f_3460& a, hkLinkedCollidable_s010f_3460& b, hkProcessCollisionInput_s010f_3460& input,
                                hkProcessCollisionOutput& output);     // +0x14
};
struct hkMotionState;
class hkMotion_s010f_3460 { public:
    virtual void vslot0();
    virtual void vslot1();
    virtual void vslot2();
    virtual void step(const hkStepInfo_s010f_3460& stepInfo);                      // +0x0c (hkRigidMotion::step, 0x01088570)
};
class hkEntity_s010f_3460 { public:
    char pad00[0x08];
    hkWorld_s010f_3460* m_world;                                // +0x08
    char pad0c[0x1c - 0x0c];
    hkLinkedCollidable_s010f_3460 m_collidable;                 // +0x1c
    char pad4c[0x58 - 0x4c];
    hkMotion_s010f_3460* m_motion;                              // +0x58
    hkSimulationIsland_s010f_3460* m_simulationIsland;          // +0x5c
    char pad60[0x94 - 0x60];
    uint16_t m_storageIndex;                         // +0x94
    char pad96[0x99 - 0x96];
    bool m_fixed;                                    // +0x99
    char pad9a[0x9c - 0x9a];
    hkArray_s010f_3460<void*> m_collisionListeners;             // +0x9c
};
class hkSimulationIsland_s010f_3460 { public:
    char pad00[0x3c];
    hkArray_s010f_3460<hkEntity_s010f_3460*> m_entities;                   // +0x3c (hkInplaceArray<hkEntity*,1>)
};
struct hkContactPointRemovedEvent {                  // 0x18
    uint16_t m_contactPointId;                       // +0x00
    hkContactPointMaterial* m_contactPointMaterial;  // +0x04
    hkEntity_s010f_3460* m_entityA;                             // +0x08
    hkEntity_s010f_3460* m_entityB;                             // +0x0c
    hkEntity_s010f_3460* m_callbackFiredFrom;                   // +0x10
    hkContactMgr* m_internalContactMgr;              // +0x14
};
struct hkToiEvent_s010f_3460 {                                  // 0x40
    float m_time;                                    // +0x00
    hkEntity_s010f_3460* m_entities[2];                         // +0x04
    float m_seperatingVelocity;                      // +0x0c
    hkContactPointMaterial m_material;               // +0x10
    hkContactMgr* m_contactMgr;                      // +0x18
    hkContactPoint_s010f_3460 m_contactPoint;                   // +0x20 (16-aligned: 4 bytes of padding at +0x1c)
};
struct hkToiResources_s010f_3460 {                              // 0x20
    int m_f00, m_f04, m_f08, m_f0c, m_f10, m_f14;
    char* m_solverBuffer;                            // +0x18
    int m_solverBufferSize;                          // +0x1c
    hkToiResources_s010f_3460() : m_f00(2), m_f04(1000), m_f08(1000), m_f0c(1000), m_f10(4), m_f14(4), m_solverBuffer(0), m_solverBufferSize(0) {}
};
struct hkToiResourceMgr_s010f_3460 {
    virtual void vslot0();
    virtual void vslot1();
    virtual void vslot2();
    // returns 1 when the TOI is rejected
    virtual int beginToiAndSetupResources(hkToiEvent_s010f_3460& event, hkArray_s010f_3460<hkToiEvent_s010f_3460>& toiEvents, hkToiResources_s010f_3460& resources);   // +0x0c
    virtual void vslot4();
    virtual void vslot5();
    virtual void cleanupResources(hkToiEvent_s010f_3460& event, hkArray_s010f_3460<hkToiEvent_s010f_3460>& toiEvents, hkToiResources_s010f_3460& resources);           // +0x18
};
typedef hkArray_s010f_3460<hkEntity_s010f_3460*> hkEntityArray;
struct hkWorldCallbackUtil_s010f_3460 {
    static void firePostCollideCallback(hkWorld_s010f_3460* world, const hkStepInfo_s010f_3460& stepInfo);                                 // 0x0109F6C0
    static void fireIslandPostCollideCallback(hkWorld_s010f_3460* world, hkSimulationIsland_s010f_3460* island, const hkStepInfo_s010f_3460& stepInfo); // 0x0109F7E0
    static void fireContactPointRemoved(hkWorld_s010f_3460* world, hkContactPointRemovedEvent& event);                           // 0x0109F160
};
struct hkEntityCallbackUtil_s010f_3460 {
    static void fireContactPointRemovedInternal(hkEntity_s010f_3460* entity, hkContactPointRemovedEvent& event);                 // 0x0109E8E0
};
class hkWorld_s010f_3460 { public:
    char pad0[0xc];
    float m_currentTime;                             // +0x0c
    char pad10[0x08];
    float m_timeOfNextPsi;                           // +0x18
    char pad1c[0x38 - 0x1c];
    hkArray_s010f_3460<hkSimulationIsland_s010f_3460*> m_activeSimulationIslands;    // +0x38
    char pad44[0x78 - 0x44];
    hkProcessCollisionInput_s010f_3460* m_collisionInput;       // +0x78
    char pad7c[0x88 - 0x7c];
    int m_pendingOperationsCount;                    // +0x88
    int m_lockCount;                                 // +0x8c
    char pad90[4];
    bool m_blockExecutingPendingOperations;          // +0x94
    char pad95[0x138 - 0x95];
    hkArray_s010f_3460<void*> m_worldPostCollideListeners;      // +0x138
    char pad144[0x150 - 0x144];
    hkArray_s010f_3460<void*> m_islandPostCollideListeners;     // +0x150
    char pad15c[0x170 - 0x15c];
    hkStepInfo_s010f_3460 m_dynamicsStepInfoStepInfo;           // +0x170 (hkWorldDynamicsStepInfo::m_stepInfo)
    hkSolverInfo_s010f_3460 m_dynamicsStepInfoSolverInfo;       // +0x180

    void queueOperation(const void* op);             // 0x010829D0
    void executePendingOperations();                 // 0x01082BF0
    void lockCriticalOperations() { ++m_lockCount; }
    void unlockAndAttemptToExecutePendingOperations()
    {
        if (--m_lockCount == 0 && m_pendingOperationsCount != 0 && !m_blockExecutingPendingOperations)
            executePendingOperations();
    }
};
struct hkQueuedReintegrateOperation {                // hkWorldOperation::ReintegrateAndRecollideEntities (0x14 bytes)
    uint8_t m_type;                                  // +0x00 (0x16)
    hkEntity_s010f_3460** m_entities;                           // +0x04
    int16_t m_numEntities;                           // +0x08
    char pad0a[0x14 - 0x0a];
};
void hkSweptTransformUtil_backStepMotionState(float time, hkMotionState& ms);   // 0x0120A260 (cdecl)
bool hkSolverCheckKeycode(int level);                                            // 0x010BFBE0 (cdecl)
struct hkToiResourceMgr_s010f_3460;
void hkLs_localizedSolveToi(const hkToiResources_s010f_3460& toiResources, hkConstraintSolverResources_s010f_3460& solverResources,
                            hkToiEvent_s010f_3460& event, hkToiResourceMgr_s010f_3460& mgr, hkWorld_s010f_3460* world,
                            hkEntityArray& entitiesOut, hkFixedArray<unsigned char>& flags);   // 0x010F25F0
void hkAgentNnMachine_processAgent(hkAgentNnEntry_s010f_3460* entry, hkProcessCollisionInput_s010f_3460& input,
                                   hkProcessCollisionOutput& output);            // 0x010FC180 (cdecl)
class hkContinuousSimulation_s010f_3460 {
public:
    virtual void vslot0();
    virtual void vslot1();
    virtual void vslot2();
    virtual void vslot3();
    virtual void vslot4();
    virtual void vslot5();
    virtual void vslot6();
    virtual void vslot7();
    virtual void vslot8();
    virtual void vslot9();
    virtual void vslot10();
    virtual void vslot11();
    virtual void resetCollisionInformationForEntities(hkEntity_s010f_3460** entities, int numEntities, hkWorld_s010f_3460* world);   // +0x30 (0x010F1A60)
    virtual void reintegrateAndRecollideEntities(hkEntity_s010f_3460** entities, int numEntities, hkWorld_s010f_3460* world);       // 0x010F3460

    char pad04[0x18 - 0x04];
    hkArray_s010f_3460<hkToiEvent_s010f_3460> m_toiEvents;                 // +0x18 .. +0x23
    hkToiResourceMgr_s010f_3460* m_toiResourceMgr;              // +0x24

    void collideEntitiesBroadPhaseContinuous(hkEntity_s010f_3460** entities, int numEntities, hkWorld_s010f_3460* world, int flag);   // 0x010F1DF0
    void processAgentsOfEntities(hkEntity_s010f_3460** entities, int numEntities, hkProcessCollisionInput_s010f_3460* input,
                                 void (hkContinuousSimulation_s010f_3460::*cb)(hkAgentNnEntry_s010f_3460*, const hkProcessCollisionInput_s010f_3460&, hkProcessCollisionOutput&)); // 0x01099BE0
    void processAgentCollideContinuous(hkAgentNnEntry_s010f_3460* entry, const hkProcessCollisionInput_s010f_3460& input, hkProcessCollisionOutput& output); // 0x010F1CC0
    void collideIslandNarrowPhaseContinuous(hkSimulationIsland_s010f_3460* island, const hkProcessCollisionInput_s010f_3460& input);   // 0x010F1A90
    void addToiEvent(const hkProcessCollisionOutput& output, hkAgentNnEntry_s010f_3460& entry);                            // 0x010F0B00
    void collide(hkWorld_s010f_3460* world, const hkStepInfo_s010f_3460& stepInfo);                      // 0x010F3600
    void simulateToi(hkWorld_s010f_3460* world, hkToiEvent_s010f_3460& event, hkReal physicsDeltaTime);  // 0x010F3A40
};
// ---- items of slice s010f3460 end

// ---- items of slice s010f7100 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void FUN_0107f530(int *arr, int size);   /* hkArrayUtil::_reserveMore */
extern float DAT_015ba360;
extern float DAT_015ba364;
extern float DAT_015ba368;
extern float DAT_015ba36c;
typedef unsigned short ushort;
typedef unsigned int   uint;
typedef unsigned short undefined2;
typedef unsigned int   undefined4;
extern void FUN_010f6ea0(int a, int b, int c, int d, uint e, uint f,
                         int *g, int *h);
extern void FUN_010f7100(int param_1, int param_2, ushort *param_3, ushort param_4,
                         uint param_5, uint param_6, int *param_7, int *param_8);
extern void FUN_010f7480(int param_1, int param_2, short *param_3, ushort param_4,
                         uint param_5, uint param_6, int *param_7, int *param_8);
/* ------------------------------------------------------------------ */
/* ------------------------------------------------------------------ */

/* ------------------------------------------------------------------ */
struct hk3AxisSweep {
    void updateAabbs(undefined4 *param_2, float *param_3, int param_4,
                     int *param_5, int *param_6);
};
// ---- items of slice s010f7100 end

// ---- items of slice s010fadd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef uint32_t hkUint32;
typedef uint16_t hkUint16;
typedef hkUint16 BpInt;
extern unsigned long g_hkThreadMemoryTls_s010f_add0;           // 0x016e4174
class hkThreadMemory_s010f_add0
{
public:
	virtual void tm0();
	virtual void tm1();
	virtual void tm2();
	virtual void* onStackOverflow(int nbytes);   // 3 (+0xc) 0x0107dc10
	virtual void onStackUnderflow(void* p);      // 4 (+0x10) 0x0107db90

	void deallocateChunk(void* p, int nbytes, int cl);   // 0x0107db10

	static __forceinline hkThreadMemory_s010f_add0& getInstance() { return *(hkThreadMemory_s010f_add0*)TlsGetValue(g_hkThreadMemoryTls_s010f_add0); }

	__forceinline void* allocateStack(int nbytes)
	{
		int size = (nbytes + 0x10) & ~0xf;
		char* current = m_stackCurrent;
		char* next = current + size;
		if (next <= m_stackEnd)
		{
			m_stackCurrent = next;
			return current;
		}
		return onStackOverflow(size);  // 0x0107dc10 (hkThreadMemory::onStackOverflow)
	}
	__forceinline void deallocateStack(void* p)
	{
		m_stackCurrent = (char*)p;
		if ((char*)p == m_stackBase)
			onStackUnderflow(p);  // 0x0107db90 (hkThreadMemory::onStackUnderflow)
	}

	hkUint32 m_pad04[7];
	char* m_stackCurrent;   // +0x20
	char* m_stackPrev;      // +0x24
	char* m_stackBase;      // +0x28
	char* m_stackEnd;       // +0x2c
};
void hkArrayReserveExactly(void* arrayBase, int numElem, int elemSize);
template <typename T>
class hkArray_s010f_add0
{ public:
	enum { CAPACITY_MASK = 0x3fffffff };
	T* m_data;
	int m_size;
	int m_capacityAndFlags;

	hkArray_s010f_add0() : m_data(0), m_size(0), m_capacityAndFlags((int)0x80000000) {}
	hkArray_s010f_add0(T* buffer, int size, int capacity) : m_data(buffer), m_size(size), m_capacityAndFlags(capacity | (int)0x80000000) {}
	__forceinline ~hkArray_s010f_add0()
	{
		if (m_capacityAndFlags >= 0)
			hkThreadMemory_s010f_add0::getInstance().deallocateChunk(m_data, (m_capacityAndFlags & CAPACITY_MASK) * (int)sizeof(T), HK_MEMORY_CLASS_ARRAY);
	}
	int getSize() const { return m_size; }
	T* begin() { return m_data; }
	const T* begin() const { return m_data; }
	T& operator[](int i) { return m_data[i]; }
	const T& operator[](int i) const { return m_data[i]; }
	__forceinline void pushBackUnchecked(const T& t) { m_data[m_size] = t; m_size++; }
	// Inserts every element of src before index (0x010fbb80 for hkArray<hkClass*>).
	void insertAt(int index, const hkArray_s010f_add0<T>& src);
};
template <typename T>
struct hkLocalBuffer
{
	__forceinline explicit hkLocalBuffer(int n) { m_p = (T*)hkThreadMemory_s010f_add0::getInstance().allocateStack(n * (int)sizeof(T)); }
	__forceinline ~hkLocalBuffer() { hkThreadMemory_s010f_add0::getInstance().deallocateStack(m_p); }
	T* begin() { return m_p; }
	T* m_p;
};
__declspec(align(16)) struct hkVector4_s010f_add0
{
	hkReal x, y, z, w;
	__forceinline void setAdd4(const hkVector4_s010f_add0& a, const hkVector4_s010f_add0& b) { x = a.x + b.x; y = a.y + b.y; z = a.z + b.z; w = a.w + b.w; }
	__forceinline void mul4(const hkVector4_s010f_add0& a) { x *= a.x; y *= a.y; z *= a.z; w *= a.w; }
	__forceinline void setMin4(const hkVector4_s010f_add0& a, const hkVector4_s010f_add0& b)
	{
		x = (a.x < b.x) ? a.x : b.x;
		y = (a.y < b.y) ? a.y : b.y;
		z = (a.z < b.z) ? a.z : b.z;
		w = (a.w < b.w) ? a.w : b.w;
	}
	__forceinline void setMax4(const hkVector4_s010f_add0& a, const hkVector4_s010f_add0& b)
	{
		x = (a.x > b.x) ? a.x : b.x;
		y = (a.y > b.y) ? a.y : b.y;
		z = (a.z > b.z) ? a.z : b.z;
		w = (a.w > b.w) ? a.w : b.w;
	}
	__forceinline void setZero4() { x = 0.0f; y = 0.0f; z = 0.0f; w = 0.0f; }
};
class hkAabb_s010f_add0
{
public:
	hkVector4_s010f_add0 m_min;
	hkVector4_s010f_add0 m_max;
};
class hkBool_s010f_add0
{
public:
	hkBool_s010f_add0() {}
	hkBool_s010f_add0(bool b) : m_bool(b ? 1 : 0) {}
	operator bool() const { return m_bool != 0; }
private:
	char m_bool;
};
class hkBroadPhaseHandle_s010f_add0
{
public:
	hkUint32 m_id;   // +0 (index of the node)
};
class hkBroadPhaseHandlePair
{
public:
	hkBroadPhaseHandle_s010f_add0* m_a;
	hkBroadPhaseHandle_s010f_add0* m_b;
};
class hkReferencedObject_s010f_add0
{
public:
	virtual ~hkReferencedObject_s010f_add0();
	hkUint16 m_memSizeAndFlags;   // +4
	hkUint16 m_referenceCount;    // +6
};
class hkBroadPhase : public hkReferencedObject_s010f_add0
{
public:
	hkUint32 m_type;              // +8 (padding up to the aligned members at +0x10)
};
struct hkArrayUtil_s010f_add0
{
	static void _reserveExactly(void* arrayBase, int numElem, int elemSize);   // 0x0107f4a0
	// Shrinks the array into its inplace storage (or a smaller block) once its size halves.
	static void _reduce(void* arrayBase, int elemSize, void* inplaceStorage, int inplaceCapacity);   // 0x0107f5d0
};
class hkClass;
class hk3AxisSweep_s010f_add0 : public hkBroadPhase
{
public:
	struct hkBpEndPoint
	{
		BpInt m_value;       // +0 (bit 0 set = max endpoint)
		BpInt m_nodeIndex;   // +2
		bool operator<(const hkBpEndPoint& o) const { return m_value < o.m_value; }
	};
	struct hkBpNode
	{
		BpInt min_y;                       // +0
		BpInt min_z;                       // +2
		BpInt max_y;                       // +4
		BpInt max_z;                       // +6
		BpInt min_x;                       // +8
		BpInt max_x;                       // +a
		hkBroadPhaseHandle_s010f_add0* m_handle;      // +c (bit 0 set = marker)
	};
	struct hkBpMarker
	{
		BpInt m_nodeIndex;                         // +0
		BpInt m_value;                             // +2
		hkArray_s010f_add0<BpInt> m_overlappingObjects;       // +4
	};
	struct hkBpAxis
	{
		hkArray_s010f_add0<hkBpEndPoint> m_endPoints;
		// Merges the sorted batch of numNew new endpoints (at the end of the array) into the sorted old ones.
		void mergeBatch(hkBpNode* nodes, int oldNumEndPoints, int numNew, int axis, hkBpEndPoint* tmpBuffer);   // 0x010f4f50
		// Drops every endpoint of a removed node, given the per-node relocation table of removeObjectBatch.
		void removeBatch(hkBpNode* nodes, int axis, const hkArray_s010f_add0<int>& nodeRelocations);   // 0x010f5620
	};

	virtual void addObjectBatch(hkArray_s010f_add0<hkBroadPhaseHandle_s010f_add0*>& addObjectList, hkArray_s010f_add0<hkAabb_s010f_add0>& addAabbList,
	                            hkArray_s010f_add0<hkBroadPhaseHandlePair>& newPairs);
	virtual void removeObjectBatch(hkArray_s010f_add0<hkBroadPhaseHandle_s010f_add0*>& removeObjectList,
	                               hkArray_s010f_add0<hkBroadPhaseHandlePair>& newPairs);
	void queryBatchAabbSub(hkUint32* bitField, hkArray_s010f_add0<hkBroadPhaseHandlePair>& pairsOut, hkBool_s010f_add0 addPairs) const;   // 0x010f9ac0

	hkVector4_s010f_add0 m_offsetLow;              // +0x10
	hkVector4_s010f_add0 m_offsetHigh;             // +0x20
	hkVector4_s010f_add0 m_scale;                  // +0x30
	hkArray_s010f_add0<hkBpNode> m_nodes;          // +0x40
	hkBpAxis m_axis[3];                 // +0x4c
	int m_numMarkers;                   // +0x70
	int m_ld2NumMarkers;                // +0x74
	hkBpMarker* m_markers;              // +0x78
};
static __forceinline void hkToggleBit(hkUint32* bitField, int index)
{
	int word = index >> 5;
	int bit = index & 0x1f;
	bitField[word] ^= (1 << bit);
}
// ---- items of slice s010fadd0 end

// ---- items of slice s010fd4c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" unsigned __int64 __rdtsc();
extern unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4
extern const char g_hkTimerEndTag1[];               // 0x0149cc34
#pragma intrinsic(__rdtsc)
typedef int   hkInt32;
typedef unsigned short hkContactPointId;
class hkBool_s010f_d4c0 {
public:
    char m_bool;
    hkBool_s010f_d4c0() {}
    hkBool_s010f_d4c0(bool b) : m_bool(b ? 1 : 0) {}
    operator bool() const { return m_bool != 0; }
};
class __declspec(align(16)) hkVector4_s010f_d4c0 {
public:
    hkReal x, y, z, w;
};
class hkRotation_s010f_d4c0 {
public:
    hkVector4_s010f_d4c0 c0, c1, c2;
};
class hkTransform_s010f_d4c0 {
public:
    hkRotation_s010f_d4c0 m_rotation;
    hkVector4_s010f_d4c0  m_translation;
};
class hkShape_s010f_d4c0 {
public:
    virtual void v00(); virtual void v04(); virtual int getType() const; virtual void v0c();
    unsigned int m_pad[2];      // +0x4, +0x8
    float        m_radius;      // +0xc
};
class hkCdBody_s010f_d4c0 {
public:
    const hkShape_s010f_d4c0*     m_shape;     // +0x0
    unsigned int       m_shapeKey;  // +0x4
    const hkTransform_s010f_d4c0* m_motion;    // +0x8
    const hkCdBody_s010f_d4c0*    m_parent;    // +0xc
};
struct hkCollisionInput_s010f_d4c0 { private:
public:
    void*   m_dispatcher;             // +0x0
    void*   m_filter;                 // +0x4
    float   m_tolerance;              // +0x8
    hkBool_s010f_d4c0  m_createPredictiveAgents; // +0xc
};
struct hkProcessCdPoint_s010f_d4c0 {
    hkVector4_s010f_d4c0        m_position;         // +0x00
    hkVector4_s010f_d4c0        m_separatingNormal; // +0x10
    hkContactPointId m_contactPointId;   // +0x20
    unsigned short   m_pad22;            // +0x22
    unsigned int     m_pad24[3];         // +0x24
};
struct hkPendingContact {
    void*                m_entry;     // +0x0
    hkProcessCdPoint_s010f_d4c0**   m_contact;   // +0x4
    void*                m_agentData; // +0x8
};
struct hkProcessCollisionOutput_s010f_d4c0 {
    hkProcessCdPoint_s010f_d4c0* m_firstFreeContactPoint;   // +0x0
    unsigned int      m_pad[0xc0f];
    hkPendingContact* m_potentialContacts;       // +0x3040
};
struct hkCollisionInput_s010f_d4c0;
class hkContactMgr_s010f_d4c0 {
public:
    virtual void v00();
    virtual void v04();
    virtual hkContactPointId addContactPoint(const hkCdBody_s010f_d4c0& a, const hkCdBody_s010f_d4c0& b,
                                             const hkCollisionInput_s010f_d4c0& input, hkProcessCdPoint_s010f_d4c0& cp);  // +0x08
    virtual hkInt32 reserveContactPoints(hkInt32 n);                                               // +0x0c
    virtual void removeContactPoint(hkContactPointId id);                                          // +0x10
};
struct hkProcessCollisionInput_s010f_d4c0 { private:
public:
    void*       m_dispatcher;             // +0x0
    void*       m_filter;                 // +0x4
    float       m_tolerance;              // +0x8
    hkBool_s010f_d4c0      m_createPredictiveAgents; // +0xc
    float       m_stepInfo[4];            // +0x10
    void*       m_config;                 // +0x20
    void*       m_dynamicsInfo;           // +0x24
    const void* m_collisionQualityInfo;   // +0x28
};
struct hkAgent3ProcessInput {
    const hkCdBody_s010f_d4c0*                m_bodyA;      // +0x0
    const hkCdBody_s010f_d4c0*                m_bodyB;      // +0x4
    const hkProcessCollisionInput_s010f_d4c0* m_input;      // +0x8
    hkContactMgr_s010f_d4c0*                  m_contactMgr; // +0xc
    hkTransform_s010f_d4c0                    m_aTb;        // +0x10
    float                          m_distAtT1;   // +0x50
};
struct hkAgent3Input {
    const hkCdBody_s010f_d4c0*         m_bodyA;  // +0x0
    const hkCdBody_s010f_d4c0*         m_bodyB;  // +0x4
    const hkCollisionInput_s010f_d4c0* m_input;  // +0x8
    hkTransform_s010f_d4c0             m_aTb;    // +0xc
};
struct hkAgentEntry_s010f_d4c0 {
    unsigned char m_streamCommand;     // +0x0
    unsigned char m_agentType;         // +0x1
    unsigned char m_numContactPoints;  // +0x2
    unsigned char m_size;              // +0x3
    unsigned int  m_userData;          // +0x4
};
class hkCapsuleShape {
public:
    virtual void v00(); virtual void v04(); virtual int getType() const; virtual void v0c();
    unsigned int m_pad[2];      // +0x4, +0x8
    float        m_radius;      // +0xc
    hkVector4_s010f_d4c0    m_vertex[2];   // +0x10, +0x20
};
class hkTriangleShape {
public:
    virtual void v00(); virtual void v04(); virtual int getType() const; virtual void v0c();
    unsigned int m_pad[2];      // +0x4, +0x8
    float        m_radius;      // +0xc
    hkVector4_s010f_d4c0    m_vertex[3];   // +0x10, +0x20, +0x30
};
class hkBoxBoxManifold {
public:
    struct hkFeatureContactPoint {
        unsigned char    m_featureIdA;     // +0x0
        unsigned char    m_featureIdB;     // +0x1
        hkContactPointId m_contactPointId; // +0x2
    };
    hkFeatureContactPoint m_contactPoints[8];   // +0x00
    unsigned char  m_faceVertexFeatureCount;    // +0x20
    unsigned char  m_numPoints;                 // +0x21
    hkBool_s010f_d4c0         m_isComplete;                // +0x22
    hkBool_s010f_d4c0         m_manifoldNormalInitialized; // +0x23
    unsigned int   m_pad24[3];                  // +0x24
    hkVector4_s010f_d4c0      m_manifoldNormalA;           // +0x30
    hkVector4_s010f_d4c0      m_manifoldNormalB;           // +0x40

    void removePoint(int index);   // 0x010ec4a0
    void init();                   // 0x010ec500
};
class hkBoxBoxCollisionDetection {
public:
    const hkCdBody_s010f_d4c0*           m_bodyA;    // +0x00
    const hkCdBody_s010f_d4c0*           m_bodyB;    // +0x04
    const hkCollisionInput_s010f_d4c0*   m_env;      // +0x08
    hkContactMgr_s010f_d4c0*             m_contactMgr; // +0x0c
    hkProcessCollisionOutput_s010f_d4c0* m_result;   // +0x10
    const hkTransform_s010f_d4c0*        m_wTa;      // +0x14
    const hkTransform_s010f_d4c0*        m_wTb;      // +0x18
    unsigned int              m_pad1c;    // +0x1c
    hkRotation_s010f_d4c0                m_aRb;      // +0x20
    hkVector4_s010f_d4c0                 m_aTb;      // +0x50
    hkVector4_s010f_d4c0                 m_radiusA;  // +0x60
    hkVector4_s010f_d4c0                 m_radiusB;  // +0x70
    hkVector4_s010f_d4c0                 m_tolerance4;         // +0x80
    hkVector4_s010f_d4c0                 m_boundaryToleranceA; // +0x90
    hkVector4_s010f_d4c0                 m_boundaryToleranceB; // +0xa0
    hkReal                    m_tolerance;          // +0xb0
    unsigned int              m_padb4[3];
    hkVector4_s010f_d4c0                 m_dinA;     // +0xc0
    hkVector4_s010f_d4c0                 m_dinB;     // +0xd0

    void calcManifold(hkBoxBoxManifold& manifold) const;   // 0x0110b3a0
};
class hkBoxBoxManifold;
class hkCollisionDispatcher_s010f_d4c0 {
public:
    struct Agent3Funcs {
        void* (*m_createFunc)();
        void  (*m_destroyFunc)();
        void  (*m_cleanupFunc)();
        void  (*m_removePointFunc)();
        void  (*m_commitPotentialFunc)();
        void  (*m_createZombieFunc)();
        void  (*m_updateFilterFunc)();
        void  (*m_invalidateTimFunc)();
        void  (*m_warpTimeFunc)();
        void  (*m_sepNormalFunc)();
        void* (*m_processFunc)();
        hkBool_s010f_d4c0 m_isPredictive;
        hkBool_s010f_d4c0 m_ignoreSymmetricVersion;
    };
    hkInt32 registerAgent3(Agent3Funcs& funcs, int typeA, int typeB);   // 0x010cd4c0
};
extern "C" void     __cdecl hkCollideCapsuleUtilManifoldCapsVsTriangle(const hkVector4_s010f_d4c0* capSegment, float capRadius,
                                                                      const hkVector4_s010f_d4c0* triangle, float triRadius,
                                                                      const hkVector4_s010f_d4c0* scaleAndNormal,
                                                                      float extraRadius, int singleCheck,
                                                                      void* out);                          // 0x01107270
extern "C" void*    __cdecl hkCapsuleTriangleAgent3_create(const hkAgent3Input& input, hkAgentEntry_s010f_d4c0* entry,
                                                           void* agentData);                               // 0x010fd060
extern "C" void     __cdecl hkCapsuleTriangleAgent3_destroy(hkAgentEntry_s010f_d4c0* entry, void* agentData,
                                                            hkContactMgr_s010f_d4c0* mgr);                                // 0x010fd0e0
extern "C" void     __cdecl hkCapsuleTriangleAgent3_cleanup(hkAgentEntry_s010f_d4c0* entry, void* agentData);            // 0x010fd0a0
extern "C" void     __cdecl hkCapsuleTriangleAgent3_removePoint(hkAgentEntry_s010f_d4c0* entry, void* agentData,
                                                                hkContactPointId id);                          // 0x010fd010
extern "C" void     __cdecl hkCapsuleTriangleAgent3_commitPotential(hkAgentEntry_s010f_d4c0* entry, void* agentData,
                                                                    hkContactPointId id);                      // 0x010fd040
extern "C" void     __cdecl hkCapsuleTriangleAgent3_sepNormal(const hkAgent3Input& input, void* agentData,
                                                              hkVector4_s010f_d4c0& normal);                              // 0x010fd0f0
extern "C" void*    __cdecl hkBoxBoxAgent3_create(const hkAgent3Input& input, hkAgentEntry_s010f_d4c0* entry,
                                                  void* agentData);                                        // 0x010fdb50
extern "C" void*    __cdecl hkBoxBoxAgent3_destroy(hkAgentEntry_s010f_d4c0* entry, void* agentData, hkContactMgr_s010f_d4c0* mgr);   // 0x010fdb70
extern "C" void     __cdecl hkBoxBoxAgent3_removePoint(hkAgentEntry_s010f_d4c0* entry, void* agentData,
                                                       hkContactPointId id);                                   // 0x010fdae0
extern "C" void     __cdecl hkBoxBoxAgent3_commitPotential(hkAgentEntry_s010f_d4c0* entry, void* agentData,
                                                           hkContactPointId id);                               // 0x010fdb20
extern "C" void*    __cdecl hkBoxBoxAgent3_process(const hkAgent3ProcessInput& input, hkAgentEntry_s010f_d4c0* entry,
                                                   void* agentData, hkVector4_s010f_d4c0* separatingNormal,
                                                   hkProcessCollisionOutput_s010f_d4c0& result);                          // 0x010fdbe0
extern "C" void     __cdecl hkBoxBox_createZombie(hkAgentEntry_s010f_d4c0* entry, void* agentData, hkContactPointId id);  // 0x00c2e4e0
extern "C" void*    __cdecl hkPredGskCylinderAgent3_create(const hkAgent3Input& input, hkAgentEntry_s010f_d4c0* entry,
                                                           void* agentData);                               // 0x010fdf30
extern "C" void*    __cdecl hkGsk_cacheInit(const hkAgent3Input& input, hkAgentEntry_s010f_d4c0* entry, void* cache);      // 0x010ff820
#define HK_TIMER_CMD(name) do { \
    void* end_ = TlsGetValue(g_hkMonitorStreamEndTls); \
    if (TlsGetValue(g_hkMonitorStreamCurrentTls) < end_) { \
        unsigned int* c_ = (unsigned int*)TlsGetValue(g_hkMonitorStreamCurrentTls); \
        c_[0] = (unsigned int)(name); \
        c_[1] = (unsigned int)__rdtsc(); \
        TlsSetValue(g_hkMonitorStreamCurrentTls, c_ + 3); } } while (0)
// ---- items of slice s010fd4c0 end

// ---- items of slice s010fdf80 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char g_hkTimerEndTag0[];               // 0x0143cd94
typedef unsigned char  hkUchar;
typedef unsigned short hkUint16_s010f_df80;
typedef unsigned int   hkUint32_s010f_df80;
typedef signed char    hkInt8;
class hkRotation_s010f_df80 { public: float col0[4]; float col1[4]; float col2[4]; };
class __declspec(align(16)) hkVector4_s010f_df80
{
public:
    float x, y, z, w;
    void setRotatedDir(const hkRotation_s010f_df80& r, const hkVector4_s010f_df80& v);   // 0x010814a0 (out of line)
};
class hkTransform_s010f_df80 { public: float col0[4]; float col1[4]; float col2[4]; float trans[4]; };   // 0x40 bytes
class hkMemory_s010f_df80
{
public:
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
    virtual void* allocateChunk(int nbytes, int cls);
};
extern hkMemory_s010f_df80* g_hkMemoryInstance_s010f_df80;   // 0x016e4178
enum { HK_MEMORY_CLASS_SHAPE = 0x24 };
class hkReferencedObject_s010f_df80
{
public:
    virtual ~hkReferencedObject_s010f_df80();                 // slot 0: deleting dtor
    hkUint16_s010f_df80 m_memSizeAndFlags;                    // +0x4
    short    m_referenceCount;                     // +0x6

    // HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SHAPE)
    void* operator new(size_t nbytes)
    {
        hkReferencedObject_s010f_df80* b = static_cast<hkReferencedObject_s010f_df80*>(g_hkMemoryInstance_s010f_df80->allocateChunk((int)nbytes, HK_MEMORY_CLASS_SHAPE));
        b->m_memSizeAndFlags = (hkUint16_s010f_df80)nbytes;
        return b;
    }
    void removeReference()
    {
        if (m_memSizeAndFlags != 0)
        {
            --m_referenceCount;
            if (m_referenceCount == 0)
                delete this;
        }
    }
};
class hkShape_s010f_df80 : public hkReferencedObject_s010f_df80 { public:
    // vtable slot 10 (+0x28): hkConvexShape::getSupportingVertices
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
    virtual void getSupportingVertices(const hkUint16_s010f_df80* ids, int numIds, hkVector4_s010f_df80* out) const;
    hkUint32_s010f_df80 m_userData;    // +0x8
    float    m_radius;      // +0xc (hkConvexShape::m_radius)
};
class hkCylinderShape : public hkShape_s010f_df80 { public:
    float     m_cylRadius;          // +0x10
    hkVector4_s010f_df80 m_vertexA;            // +0x20
    hkVector4_s010f_df80 m_vertexB;            // +0x30
    hkVector4_s010f_df80 m_perpendicular1;     // +0x40
    hkVector4_s010f_df80 m_perpendicular2;     // +0x50
    float getCylinderRadius() const;   // 0x00a0ab60 (out of line)
};
class hkCapsuleShape_s010f_df80 : public hkShape_s010f_df80 { public:
    hkVector4_s010f_df80 m_vertexA;            // +0x10
    hkVector4_s010f_df80 m_vertexB;            // +0x20
    // Havok is built without C++ exceptions: no cleanup of the new-expression is emitted
    hkCapsuleShape_s010f_df80(const hkVector4_s010f_df80& vertexA, const hkVector4_s010f_df80& vertexB, float radius) throw();   // 0x010c2730
};
class hkCdBody_s010f_df80
{ public:
    const hkShape_s010f_df80*      m_shape;     // +0x0
    hkUint32_s010f_df80            m_shapeKey;  // +0x4
    const hkTransform_s010f_df80*  m_motion;    // +0x8
    const hkCdBody_s010f_df80*     m_parent;    // +0xc

    hkCdBody_s010f_df80() {}
    // hkCdBody(const hkCdBody* parent): child body sharing the parent's motion
    hkCdBody_s010f_df80(const hkCdBody_s010f_df80* parent) { m_parent = parent; m_motion = parent->m_motion; }
    void setShape(const hkShape_s010f_df80* shape, hkUint32_s010f_df80 key) { m_shapeKey = key; m_shape = shape; }
};
struct hkCollidableRoot : public hkCdBody_s010f_df80 { hkUint32_s010f_df80 m_pad[4]; float m_allowedPenetrationDepth; };
struct hkCollisionQualityInfo_s010f_df80
{
    float m_keepContact;         // +0x0
    float m_create4dContact;     // +0x4
    float m_createContact;       // +0x8
    float m_manifoldTimDistance; // +0xc
    char  m_useContinuousPhysics;// +0x10
    char  m_pad[3];
    float m_minSeparation;       // +0x14
    float m_minExtraSeparation;  // +0x18
    float m_minSafeDeltaTime;    // +0x1c
    float m_minAbsoluteSafeDeltaTime; // +0x20
    float m_toiSeparation;       // +0x24
    float m_toiExtraSeparation;  // +0x28
};
struct hkProcessCollisionInput_s010f_df80
{
    void*  m_dispatcher;         // +0x0
    void*  m_filter;             // +0x4
    float  m_tolerance;          // +0x8
    char   m_createPredictiveAgents;
    char   m_pad[3];
    float  m_stepInfo[4];        // +0x10
    void*  m_config;             // +0x20
    void*  m_dynamicsInfo;       // +0x24
    const hkCollisionQualityInfo_s010f_df80* m_collisionQualityInfo;   // +0x28
};
struct hkProcessCdPoint_s010f_df80;
struct hkAgentEntry_s010f_df80 { hkUchar m_streamCommand, m_agentType, m_numContactPoints, m_size; hkUint32_s010f_df80 m_userData; };
enum
{
    CYLINDER_A        = 1,
    CYLINDER_B        = 2,
    CAPSULE_MODE_A    = 4,   // CAPSULE_MODE_A << i for body i
    CAPSULE_MODE_B    = 8
};
class hkContactMgr_s010f_df80
{ public:
    virtual void v0();
    virtual void v1();
    virtual hkUint16_s010f_df80 addContactPoint(const hkCdBody_s010f_df80* a, const hkCdBody_s010f_df80* b, const hkProcessCollisionInput_s010f_df80* in, hkProcessCdPoint_s010f_df80* cp);   // +0x8
    virtual int      reserveContactPoints(int n);   // +0xc (returns 0 on success)
};
struct hkAgent3ProcessInput_s010f_df80
{
    const hkCdBody_s010f_df80* m_bodyA;                // +0x0
    const hkCdBody_s010f_df80* m_bodyB;                // +0x4
    const hkProcessCollisionInput_s010f_df80* m_input; // +0x8
    hkContactMgr_s010f_df80*   m_contactMgr;           // +0xc
    hkTransform_s010f_df80     m_aTb;                  // +0x10
    float           m_distAtT1;             // +0x50
};
struct hkAgent3Input;
struct hkProcessCdPoint_s010f_df80 { hkUint32_s010f_df80 m_data[12]; };   // 0x30 bytes; short id at +0x20
struct ContactRef { hkProcessCdPoint_s010f_df80* m_contact; hkAgentEntry_s010f_df80* m_entry; void* m_agentData; };
struct PotentialInfo
{
    ContactRef*        m_firstFreePotentialContact;     // +0x0
    hkProcessCdPoint_s010f_df80** m_firstFreeRepresentativeContact;// +0x4
};
struct hkProcessCollisionOutput_s010f_df80
{
    hkProcessCdPoint_s010f_df80* m_firstFreeContactPoint;  // +0x0
    hkUint32_s010f_df80 m_pad[0xc0f];
    PotentialInfo*    m_potentialContacts;      // +0x3040
};
struct hkGskCache
{
    hkUint32_s010f_df80 m_vertexPairs[2];  // hkUint16 m_vertices[4]: A's ids first (m_dimA of them), then B's
    hkInt8   m_dimA;          // +0x8
    hkInt8   m_dimB;          // +0x9
    hkUchar  m_maxDimA;       // +0xa
    hkUchar  m_gskFlags;      // +0xb
    // (stored as dwords so the stack copy below does not draw a /GS cookie, which the original lacks)
    hkUint16_s010f_df80* vertices() { return (hkUint16_s010f_df80*)m_vertexPairs; }
};
struct hkGskInfo
{
    const hkTransform_s010f_df80* m_aTb;
    const hkTransform_s010f_df80* m_transformA;
    const hkShape_s010f_df80*     m_shapeA;
    const hkShape_s010f_df80*     m_shapeB;
    float              m_tolerance;
};
#define HK_TIMER_CMD_s010f_df80(name) do { \
    void* end_ = TlsGetValue(g_hkMonitorStreamEndTls); \
    if (TlsGetValue(g_hkMonitorStreamCurrentTls) < end_) { \
        hkUint32_s010f_df80* c_ = (hkUint32_s010f_df80*)TlsGetValue(g_hkMonitorStreamCurrentTls); \
        c_[0] = (hkUint32_s010f_df80)(name); \
        c_[1] = (hkUint32_s010f_df80)__rdtsc(); \
        TlsSetValue(g_hkMonitorStreamCurrentTls, c_ + 3); } } while (0)
namespace hkPredGskAgent3
{
    void __cdecl sepNormal(const hkAgent3Input& input, void* agentData, hkVector4_s010f_df80& sepNormalOut);           // 0x010ff8c0
}
extern int      __cdecl hkGsk_closestPoints(hkGskInfo* info, void* cache, hkVector4_s010f_df80* sepNormal, hkVector4_s010f_df80* out);  // 0x0110fa20
extern void     __cdecl hkGskManifold_cleanup(hkUchar* manifold, hkContactMgr_s010f_df80* mgr);                                    // 0x0110fdd0
extern void     __cdecl hkGskManifold_removePoint(hkUchar* manifold, int idx);                                          // 0x0110fd70
extern void     __cdecl hkGskManifold_update(hkUchar* manifold, hkVector4_s010f_df80* verts, int numRemoved,
                                             hkProcessCollisionOutput_s010f_df80* out, hkContactMgr_s010f_df80* mgr);                         // 0x0110fe20
extern unsigned __cdecl hkGskManifold_numRemoved(hkUchar* manifold, void* cache);                                       // 0x01111330
extern int      __cdecl hkGsk_addPoint(hkUchar* manifold, const hkCdBody_s010f_df80* a, const hkCdBody_s010f_df80* b,
                                       const hkProcessCollisionInput_s010f_df80* in, void* cache, hkProcessCdPoint_s010f_df80* cp,
                                       hkProcessCdPoint_s010f_df80* start, hkContactMgr_s010f_df80* mgr, int flag);                           // 0x01111d90
extern void     __cdecl hkGsk_toi(const hkAgent3ProcessInput_s010f_df80* input, float minRadius, float t0, float t1,
                                  void* agentData, hkVector4_s010f_df80* sepNormal, hkProcessCollisionOutput_s010f_df80* out);                // 0x01112950
#define HK_XFORM_ONE(P) { \
        const float x = (P).x, y = (P).y, z = (P).z; \
        (P).x = (m10 * y + (m20 * z + m00 * x)) + tx; \
        (P).y = (m01 * x + (m11 * y + m21 * z)) + ty; \
        (P).z = (m02 * x + (m12 * y + m22 * z)) + tz; \
        (P).w = 0.0f; }
static __forceinline void transformPoints(const hkTransform_s010f_df80* t, hkVector4_s010f_df80* v, int n)
{
    const float m00 = t->col0[0], m01 = t->col0[1], m02 = t->col0[2];
    const float m10 = t->col1[0], m11 = t->col1[1], m12 = t->col1[2];
    const float m20 = t->col2[0], m21 = t->col2[1], m22 = t->col2[2];
    const float tx = t->trans[0], ty = t->trans[1], tz = t->trans[2];
    int i = 0;
    if (n >= 4)
    {
        int blocks = ((n - 4) >> 2) + 1;
        i = blocks * 4;
        hkVector4_s010f_df80* p = v;
        do {
            HK_XFORM_ONE(p[0]) HK_XFORM_ONE(p[1]) HK_XFORM_ONE(p[2]) HK_XFORM_ONE(p[3])
            p += 4;
        } while (--blocks);
    }
    for (; i < n; ++i)
        HK_XFORM_ONE(v[i])
}
static __forceinline void getPoints(const hkAgent3ProcessInput_s010f_df80* in, hkUchar* manifold, hkVector4_s010f_df80* verts, const hkVector4_s010f_df80* sepNormal)
{
    const hkCdBody_s010f_df80* bodyA = in->m_bodyA;
    const hkCdBody_s010f_df80* bodyB = in->m_bodyB;
    const hkShape_s010f_df80* shapeA = bodyA->m_shape;
    const hkShape_s010f_df80* shapeB = bodyB->m_shape;
    float info[8];
    info[0] = sepNormal->x; info[1] = sepNormal->y; info[2] = sepNormal->z; info[3] = sepNormal->w;
    info[4] = shapeA->m_radius;
    info[5] = shapeB->m_radius;
    info[6] = in->m_input->m_tolerance;
    float s = (info[5] + info[4]) + info[6];
    info[7] = s * s;
    (void)info;
    const int numPoints = manifold[2];
    if (numPoints)
    {
        const hkUint16_s010f_df80* idsA = (const hkUint16_s010f_df80*)(manifold + 4 + numPoints * 8);
        const int numA = manifold[0];
        shapeA->getSupportingVertices(idsA, numA, verts);
        transformPoints(bodyA->m_motion, verts, numA);
        const int numB = manifold[1];
        shapeB->getSupportingVertices(idsA + numA, numB, verts + numA);
        transformPoints(bodyB->m_motion, verts + numA, numB);
    }
}
static __forceinline void replaceCylindersByCapsules(const hkCdBody_s010f_df80** bodyPtr[2], const int capsuleMode[2],
                                                     const hkCdBody_s010f_df80* savedBodies[2], hkCdBody_s010f_df80 tmpBodies[2])
{
    for (int i = 0; i < 2; i++)
    {
        if (capsuleMode[i])
        {
            const hkCylinderShape* cyl = static_cast<const hkCylinderShape*>((*bodyPtr[i])->m_shape);
            const float convexRadius = cyl->m_radius;
            hkCapsuleShape_s010f_df80* capsule = new hkCapsuleShape_s010f_df80(cyl->m_vertexA, cyl->m_vertexB,
                                                         cyl->getCylinderRadius() + convexRadius + 0.002f);
            hkCdBody_s010f_df80* body = new (&tmpBodies[i]) hkCdBody_s010f_df80(*bodyPtr[i]);
            body->setShape(capsule, body->m_parent->m_shapeKey);
            savedBodies[i] = *bodyPtr[i];
            *bodyPtr[i] = body;
        }
        else
            savedBodies[i] = 0;
    }
}
static __forceinline hkUint16_s010f_df80 cylinderToCapsuleVertexId(hkUint16_s010f_df80 id)
{
    return (hkUint16_s010f_df80)((1 - (((hkUchar)id >> 7) & 1)) << 4);
}
// ---- items of slice s010fdf80 end

// ---- items of slice s010ff9e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned short hkUint16_s010f_f9e0;
typedef unsigned int   hkUint32_s010f_f9e0;
class __declspec(align(16)) hkVector4_s010f_f9e0 { public: float x, y, z, w; };
class hkTransform_s010f_f9e0 { public: float col0[4]; float col1[4]; float col2[4]; float trans[4]; };   // 0x40 bytes
class hkShape_s010f_f9e0
{ public:
    // vtable slot 10 (+0x28): hkConvexShape::getSupportingVertices
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
    virtual void getSupportingVertices(const hkUint16_s010f_f9e0* ids, int numIds, hkVector4_s010f_f9e0* out) const;
    float m_pad[2]; float m_radius;     // radius at +0xc (vptr, +4, +8, +0xc)
};
class hkCdBody_s010f_f9e0
{ public:
    const hkShape_s010f_f9e0*        m_shape;       // +0x0
    hkUint32_s010f_f9e0              m_shapeKey;    // +0x4
    const hkTransform_s010f_f9e0*    m_motion;      // +0x8
    const hkCdBody_s010f_f9e0*       m_parent;      // +0xc
    hkUint32_s010f_f9e0              m_pad[4];
    float                 m_allowedPenetrationDepth;   // +0x20 (on the root body)
};
struct hkCollisionQualityInfo_s010f_f9e0
{
    float m_keepContact;         // +0x0
    float m_create4dContact;     // +0x4
    float m_createContact;       // +0x8
    float m_manifoldTimDistance; // +0xc
    char  m_useContinuousPhysics;// +0x10
    char  m_pad[3];
    float m_minSeparation;       // +0x14
    float m_minExtraSeparation;  // +0x18
    float m_minSafeDeltaTime;    // +0x1c
    float m_minAbsoluteSafeDeltaTime; // +0x20
    float m_toiSeparation;       // +0x24
    float m_toiExtraSeparation;  // +0x28
};
struct hkProcessCollisionInput_s010f_f9e0
{
    void*  m_dispatcher;         // +0x0
    void*  m_filter;             // +0x4
    float  m_tolerance;          // +0x8
    char   m_createPredictiveAgents;
    char   m_pad[3];
    float  m_stepInfo[4];        // +0x10
    void*  m_config;             // +0x20
    void*  m_dynamicsInfo;       // +0x24
    const hkCollisionQualityInfo_s010f_f9e0* m_collisionQualityInfo;   // +0x28
};
struct hkProcessCdPoint_s010f_f9e0;
struct hkAgentEntry_s010f_f9e0 { hkUchar m_streamCommand, m_agentType, m_numContactPoints, m_size; hkUint32_s010f_f9e0 m_userData; };
class hkContactMgr_s010f_f9e0
{ public:
    virtual void v0();
    virtual void v1();
    virtual hkUint16_s010f_f9e0 addContactPoint(const hkCdBody_s010f_f9e0* a, const hkCdBody_s010f_f9e0* b, const hkProcessCollisionInput_s010f_f9e0* in, hkProcessCdPoint_s010f_f9e0* cp);   // +0x8
    virtual int      reserveContactPoints(int n);   // +0xc (returns 0 on success)
};
struct hkAgent3ProcessInput_s010f_f9e0
{
    const hkCdBody_s010f_f9e0* m_bodyA;                // +0x0
    const hkCdBody_s010f_f9e0* m_bodyB;                // +0x4
    const hkProcessCollisionInput_s010f_f9e0* m_input; // +0x8
    hkContactMgr_s010f_f9e0*   m_contactMgr;           // +0xc
    hkTransform_s010f_f9e0     m_aTb;                  // +0x10
    float           m_distAtT1;             // +0x50
};
struct hkProcessCdPoint_s010f_f9e0 { hkUint32_s010f_f9e0 m_data[12]; };   // 0x30 bytes; short id at +0x20
struct ContactRef_s010f_f9e0 { hkProcessCdPoint_s010f_f9e0* m_contact; hkAgentEntry_s010f_f9e0* m_entry; void* m_agentData; };
struct PotentialInfo_s010f_f9e0
{
    ContactRef_s010f_f9e0*        m_firstFreePotentialContact;     // +0x0
    hkProcessCdPoint_s010f_f9e0** m_firstFreeRepresentativeContact;// +0x4
};
struct hkProcessCollisionOutput_s010f_f9e0
{
    hkProcessCdPoint_s010f_f9e0* m_firstFreeContactPoint;  // +0x0
    hkUint32_s010f_f9e0 m_pad[0xc0f];
    PotentialInfo_s010f_f9e0*    m_potentialContacts;      // +0x3040
};
struct hkGskInfo_s010f_f9e0
{
    const hkTransform_s010f_f9e0* m_aTb;
    const hkTransform_s010f_f9e0* m_transformA;
    const hkShape_s010f_f9e0*     m_shapeA;
    const hkShape_s010f_f9e0*     m_shapeB;
    float              m_tolerance;
};
#define HK_TIMER_CMD_s010f_f9e0(name) do { \
    void* end_ = TlsGetValue(g_hkMonitorStreamEndTls); \
    if (TlsGetValue(g_hkMonitorStreamCurrentTls) < end_) { \
        hkUint32_s010f_f9e0* c_ = (hkUint32_s010f_f9e0*)TlsGetValue(g_hkMonitorStreamCurrentTls); \
        c_[0] = (hkUint32_s010f_f9e0)(name); \
        c_[1] = (hkUint32_s010f_f9e0)__rdtsc(); \
        TlsSetValue(g_hkMonitorStreamCurrentTls, c_ + 3); } } while (0)
extern int      __cdecl hkGsk_closestPoints(hkGskInfo_s010f_f9e0* info, void* agentData, hkVector4_s010f_f9e0* sepNormal, hkVector4_s010f_f9e0* out);   // 0x0110fa20
extern void     __cdecl hkGskManifold_cleanup(hkUchar* manifold, hkContactMgr_s010f_f9e0* mgr);                                    // 0x0110fdd0
extern void     __cdecl hkGskManifold_update(hkUchar* manifold, hkVector4_s010f_f9e0* verts, int numRemoved,
                                             hkProcessCollisionOutput_s010f_f9e0* out, hkContactMgr_s010f_f9e0* mgr);                         // 0x0110fe20
extern int      __cdecl hkGsk_addPoint(hkUchar* manifold, const hkCdBody_s010f_f9e0* a, const hkCdBody_s010f_f9e0* b,
                                       const hkProcessCollisionInput_s010f_f9e0* in, void* agentData, hkProcessCdPoint_s010f_f9e0* cp,
                                       hkProcessCdPoint_s010f_f9e0* start, hkContactMgr_s010f_f9e0* mgr, int flag);                           // 0x01111d90
extern void     __cdecl hkGsk_toi(const hkAgent3ProcessInput_s010f_f9e0* input, float minRadius, float t0, float t1,
                                  void* agentData, hkVector4_s010f_f9e0* sepNormal, hkProcessCollisionOutput_s010f_f9e0* out);                // 0x01112950
static __forceinline void transformPoints_s010f_f9e0(const hkTransform_s010f_f9e0* t, hkVector4_s010f_f9e0* v, int n)
{
    const float m00 = t->col0[0], m01 = t->col0[1], m02 = t->col0[2];
    const float m10 = t->col1[0], m11 = t->col1[1], m12 = t->col1[2];
    const float m20 = t->col2[0], m21 = t->col2[1], m22 = t->col2[2];
    const float tx = t->trans[0], ty = t->trans[1], tz = t->trans[2];
    int i = 0;
    if (n >= 4)
    {
        int blocks = ((n - 4) >> 2) + 1;
        i = blocks * 4;
        hkVector4_s010f_f9e0* p = v;
        do {
            HK_XFORM_ONE(p[0]) HK_XFORM_ONE(p[1]) HK_XFORM_ONE(p[2]) HK_XFORM_ONE(p[3])
            p += 4;
        } while (--blocks);
    }
    for (; i < n; ++i)
        HK_XFORM_ONE(v[i])
}
static __forceinline void getPoints_s010f_f9e0(const hkAgent3ProcessInput_s010f_f9e0* in, hkUchar* manifold, hkVector4_s010f_f9e0* verts, const hkVector4_s010f_f9e0* sepNormal)
{
    const hkCdBody_s010f_f9e0* bodyA = in->m_bodyA;
    const hkCdBody_s010f_f9e0* bodyB = in->m_bodyB;
    const hkShape_s010f_f9e0* shapeA = bodyA->m_shape;
    const hkShape_s010f_f9e0* shapeB = bodyB->m_shape;
    float info[8];
    info[0] = sepNormal->x; info[1] = sepNormal->y; info[2] = sepNormal->z; info[3] = sepNormal->w;
    info[4] = shapeA->m_radius;
    info[5] = shapeB->m_radius;
    info[6] = in->m_input->m_tolerance;
    float s = (info[5] + info[4]) + info[6];
    info[7] = s * s;
    (void)info;
    const int numPoints = manifold[2];
    if (numPoints)
    {
        const hkUint16_s010f_f9e0* idsA = (const hkUint16_s010f_f9e0*)(manifold + 4 + numPoints * 8);
        const int numA = manifold[0];
        shapeA->getSupportingVertices(idsA, numA, verts);
        transformPoints_s010f_f9e0(bodyA->m_motion, verts, numA);
        const int numB = manifold[1];
        shapeB->getSupportingVertices(idsA + numA, numB, verts + numA);
        transformPoints_s010f_f9e0(bodyB->m_motion, verts + numA, numB);
    }
}
// ---- items of slice s010ff9e0 end

// hkMoppCode::~hkMoppCode is in _at_010f0000_cleanup.cpp (VC7.1 companion).

// @ 0x010f01d0
void __fastcall hkConvexPieceStreamDataDestructor(hkConvexPieceStreamData* self)
{
    int count2 = *(volatile int*)&self->mCount2;
    if (count2 >= 0) {
        hkThreadMemory* memory = (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls);
        memory->deallocateChunk(self->mpStream2, ((uint32_t)self->mCount2 & 0x3fffffff) << 2, 0x14);
    }
    int count1 = *(volatile int*)&self->mCount1;
    if (count1 >= 0) {
        hkThreadMemory* memory = (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls);
        memory->deallocateChunk(self->mpStream1, ((uint32_t)self->mCount1 & 0x3fffffff) << 2, 0x14);
    }
    int count0 = *(volatile int*)&self->mCount0;
    if (count0 >= 0) {
        hkThreadMemory* memory = (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls);
        memory->deallocateChunk(self->mpStream0, ((uint32_t)self->mCount0 & 0x3fffffff) << 2, 0x14);
    }
    self->mpVtable = (void*)0x13ef094;
}

// @ 0x010f0260
hkSolverInfo_s010e_f580& hkSolverInfo_s010e_f580::operator=(const hkSolverInfo_s010e_f580& other)
{
    m00 = other.m00; m04 = other.m04; m08 = other.m08; m0c = other.m0c; m10 = other.m10;
    m14 = other.m14; m18 = other.m18; m1c = other.m1c; m20 = other.m20; m24 = other.m24;
    m28 = other.m28; m2c = other.m2c; m30 = other.m30; m34 = other.m34; m38 = other.m38;
    m3c = other.m3c; m40 = other.m40; m44 = other.m44; m48 = other.m48; m4c = other.m4c;
    m50 = other.m50; m54 = other.m54; m58 = other.m58; m5c = other.m5c; m60 = other.m60;
    m64 = other.m64;
    m84 = other.m84;
    ma4 = other.ma4;
    mc4 = other.mc4;
    me4 = other.me4;
    m104 = other.m104;
    m124 = other.m124; m128 = other.m128; m12c = other.m12c; m130 = other.m130;
    return *this;
}

// @ 0x010f03a0
void hkContinuousSimulation::warpTime(hkWorld_s010e_f580* world, float deltaTime)
{
    hkSimulation* simulation = world->mpSimulation;
    int count = *(volatile int*)&simulation->mCount;
    int index = 0;
    if (count > 0) {
        int offset = 0;
        do {
            hkSimulationEntry* entry = (hkSimulationEntry*)((uint8_t*)simulation->mpEntries + offset);
            entry->mTime = *(volatile float*)&deltaTime + entry->mTime;
            index++;
            offset += 0x40;
            count = *(volatile int*)&simulation->mCount;
        } while (count > index);
    }
}

// @ 0x010f03d0
void hkLs_doSimpleCollisionResponse(hkWorld_s010e_f580* world, const hkToiEvent& event, float time, hkArrayEntity& bodies)
{
    (void)world;
    hkEntity_s010e_f580* bodyA = event.mpBodyA;
    hkEntity_s010e_f580* bodyB = event.mpBodyB;

    hkSolveParams params;
    params.mField00 = event.mField30;
    params.mField04 = event.mField34;
    params.mField08 = event.mField38;
    params.mField0c = event.mField3c;
    params.mField10 = (float)event.mField14 * (1.0f / 256.0f);
    params.mField14 = (float)event.mField16 * (1.0f / 128.0f);
    params.mField18 = event.mField0c;
    params.mField1c = 0.1f;
    params.mField20 = time;

    hkSolveOutput output;
    hkSolveSingleContact(&event.mContactPoint, event.mTime, &params,
                         bodyA->mpField58, bodyB->mpField58, (void*)event.mField18, &output);

    if (output.mField4 >= 0.0f) {
        if (output.mField4 >= 0.0f && output.mField8 < 0.0f) {
            if (bodyB->mField9a)
                hkArrayAppend(bodies, bodyA);
            else
                hkArrayAppend(bodies, bodyB);
            return;
        }
        if (!bodyA->mField9a && (bodyB->mField9a || output.mField4 <= output.mField8))
            hkArrayAppend(bodies, bodyA);
        hkArrayAppend(bodies, bodyB);
        return;
    }

    if (output.mField8 >= 0.0f) {
        if (!bodyA->mField9a)
            hkArrayAppend(bodies, bodyA);
        else
            hkArrayAppend(bodies, bodyB);
        return;
    }

    if (!bodyA->mField9a)
        hkArrayAppend(bodies, bodyA);
    if (bodyB->mField9a)
        return;
    hkArrayAppend(bodies, bodyB);
}

// @ 0x010f1350
void FUN_010f1350(void* input, int priority, float time, hkArray<hkEntity_s010f_1350*>* toBeActivated, hkFixedArray<unsigned char>* flags, hkArray<hkEntity_s010f_1350*>* newEntities, hkArray<hkConstraintInstance_s010f_1350*>* newConstraints)
{
    if (toBeActivated->m_size <= 0)
        return;

    int i = 0;
    do {
        hkEntity_s010f_1350* entity = toBeActivated->m_data[i];
        unsigned char* state = &flags->m_data[entity->m_storageIndex];
        if (*state == 0) {
            *state = 1;
            FUN_01209c50(&entity->m_motion->m_motionState.m_sweptTransform, time,
                         &entity->m_motion->m_motionState.m_transform);
        }
        flags->m_data[entity->m_storageIndex] = 8;
        FUN_010f0d60(entity, priority, input, time, flags);

        // master constraints: the internal records are stored inline
        for (int m = 0; m < entity->m_constraintsMaster.m_size; m++) {
            hkConstraintInternal_s010f_1350* ci = &entity->m_constraintsMaster.m_data[m];
            if (priority > (int)ci->m_constraint->m_priority)
                continue;
            hkEntity_s010f_1350* other = (hkEntity_s010f_1350*)((unsigned int)ci->m_entities[0] ^
                                          (unsigned int)ci->m_entities[1] ^
                                          (unsigned int)entity);
            if (other->m_fixed) {
                if (newConstraints->m_size == (newConstraints->m_capacityAndFlags & hkArray<hkConstraintInstance_s010f_1350*>::CAPACITY_MASK))
                    FUN_0107f530(newConstraints, 4);
                newConstraints->m_data[newConstraints->m_size++] = ci->m_constraint;
                continue;
            }
            unsigned char* otherState = &flags->m_data[other->m_storageIndex];
            if (*otherState == 8)
                continue;
            if (newConstraints->m_size == (newConstraints->m_capacityAndFlags & hkArray<hkConstraintInstance_s010f_1350*>::CAPACITY_MASK))
                FUN_0107f530(newConstraints, 4);
            newConstraints->m_data[newConstraints->m_size++] = ci->m_constraint;
            if (*otherState >= 2)
                continue;
            if (newEntities->m_size == (newEntities->m_capacityAndFlags & hkArray<hkEntity_s010f_1350*>::CAPACITY_MASK))
                FUN_0107f530(newEntities, 4);
            newEntities->m_data[newEntities->m_size++] = other;
            if (*otherState == 0) {
                *otherState = 1;
                FUN_01209c50(&other->m_motion->m_motionState.m_sweptTransform, time,
                             &other->m_motion->m_motionState.m_transform);
            }
            *otherState = 2;
        }

        // slave constraints: the records are reached through the instance's internal pointer
        for (int s = 0; s < entity->m_constraintsSlave.m_size; s++) {
            hkConstraintInternal_s010f_1350* ci = entity->m_constraintsSlave.m_data[s]->m_internal;
            if (priority > (int)ci->m_constraint->m_priority)
                continue;
            hkEntity_s010f_1350* other = (hkEntity_s010f_1350*)((unsigned int)ci->m_entities[0] ^
                                          (unsigned int)ci->m_entities[1] ^
                                          (unsigned int)entity);
            if (other->m_fixed) {
                if (newConstraints->m_size == (newConstraints->m_capacityAndFlags & hkArray<hkConstraintInstance_s010f_1350*>::CAPACITY_MASK))
                    FUN_0107f530(newConstraints, 4);
                newConstraints->m_data[newConstraints->m_size++] = ci->m_constraint;
                continue;
            }
            unsigned char* otherState = &flags->m_data[other->m_storageIndex];
            if (*otherState == 8)
                continue;
            if (newConstraints->m_size == (newConstraints->m_capacityAndFlags & hkArray<hkConstraintInstance_s010f_1350*>::CAPACITY_MASK))
                FUN_0107f530(newConstraints, 4);
            newConstraints->m_data[newConstraints->m_size++] = ci->m_constraint;
            if (*otherState >= 2)
                continue;
            if (newEntities->m_size == (newEntities->m_capacityAndFlags & hkArray<hkEntity_s010f_1350*>::CAPACITY_MASK))
                FUN_0107f530(newEntities, 4);
            newEntities->m_data[newEntities->m_size++] = other;
            if (*otherState == 0) {
                *otherState = 1;
                FUN_01209c50(&other->m_motion->m_motionState.m_sweptTransform, time,
                             &other->m_motion->m_motionState.m_transform);
            }
            *otherState = 2;
        }

        i++;
    } while (i < toBeActivated->m_size);
}

// @ 0x010f1690
void FUN_010f1690(char* out, ConstraintContext* ctx, ConstraintArray* constraints, int param4, ResultArray* results)
{
    char ok = 1;
    if (constraints->mSize > 0) {
        int i = 0;
        do {
            SimObjectRef* ref = &constraints->mData[i];
            EntityKind* obj = (EntityKind*)ref->mObject;
            if (obj->mKind == 4) {
                char buf[0x400];
                int u = FUN_010b1d70(ctx->mId, ref->mIndex, ctx->mFlags, ctx->mParam, 0x100, buf);
                int found = FUN_010f0e90(ctx->mSolver->mField8, ref, buf, u, param4);
                if (found >= 0) {
                    if (results == 0) {
                        *out = 0;
                        return;
                    }
                    ok = 0;
                    if (results->mSize == (results->mCapacityAndFlags & 0x3fffffff))
                        FUN_0107f530(results, 0xc);
                    int n = results->mSize;
                    results->mSize = n + 1;
                    SolveResult* r = &((SolveResult*)results->mData)[n];
                    r->mObject = ref->mObject;
                    ConstraintSub* sub = ref->mObject->mSub;
                    void** vt = *(void***)sub;
                    int kind = ((int(__thiscall*)(ConstraintSub*))vt[3])(sub);
                    if (kind == 0xb) {
                        ConstraintSub* sub2 = ref->mObject->mSub;
                        r->mField1 = found * 0x20 + sub2->mField20;
                        r->mField2 = sub2->mField38 + found * 0x14;
                    } else {
                        r->mField1 = 0;
                        r->mField2 = 0;
                    }
                }
            }
            i++;
        } while (i < constraints->mSize);
    }
    *out = ok;
}

// @ 0x010f17f0
void FUN_010f17f0(int dtBits, Island* island, FlagList* flagList, ResultArray* out)
{
    float dt = *(float*)&dtBits;
    int i = 0;
    if (island->mBodyCount > 0) {
        do {
            Entity* body = island->mBodies[i];
            MotionState* m = body->mMotion;
            FUN_0120a260(dt, &m->mRotation);
            if (flagList->mData[i] != 8) {
                if (out->mSize == (out->mCapacityAndFlags & 0x3fffffff))
                    FUN_0107f530(out, 4);
                ((Entity**)out->mData)[out->mSize] = body;
                out->mSize = out->mSize + 1;
                flagList->mData[i] = 8;
            }
            m->mStepDerivedBits[0] = m->mPositionBits[0];
            m->mStepDerivedBits[1] = m->mPositionBits[1];
            m->mStepDerivedBits[2] = m->mPositionBits[2];
            m->mStepDerivedBits[3] = m->mPositionBits[3];
            m->mStepPositionBits[0] = m->mQuatSourceBits[0];
            m->mStepPositionBits[1] = m->mQuatSourceBits[1];
            m->mStepPositionBits[2] = m->mQuatSourceBits[2];
            m->mStepPositionBits[3] = m->mQuatSourceBits[3];
            m->mStepDerivedBits[3] = dtBits;
            i++;
            m->mPosition[3] = 1.0f / (island->mTimeStep->mEndTime - dt);
        } while (i < island->mBodyCount);
    }
}

// @ 0x010f18d0
void FUN_010f18d0(Island* island, FlagList* flagList)
{
    int i = 0;
    if (island->mBodyCount > 0) {
        do {
            if (flagList->mData[i] == 1 || flagList->mData[i] == 2) {
                MotionState* m = island->mBodies[i]->mMotion;
                m->mRotation.set(&m->mQuatSource[0]);
                float x = m->mAxis[0];
                float y = m->mAxis[1];
                float z = m->mAxis[2];
                float s0 = x * m->mRotation.m_el[0] + (y * m->mRotation.m_el[4] + z * m->mRotation.m_el[8]);
                float s1 = x * m->mRotation.m_el[1] + (y * m->mRotation.m_el[5] + z * m->mRotation.m_el[9]);
                float s2 = x * m->mRotation.m_el[2] + (y * m->mRotation.m_el[6] + z * m->mRotation.m_el[10]);
                m->mDerived[0] = m->mPosition[0] - s0;
                m->mDerived[1] = m->mPosition[1] - s1;
                m->mDerived[2] = m->mPosition[2] - s2;
                m->mDerivedBits[3] = m->mPositionBits[3];
            }
            i++;
        } while (i < island->mBodyCount);
    }
}

// @ 0x010f19b0
void* FUN_010f19b0(void* self, int owner)
{
    char* s = (char*)self;
    *(unsigned short*)(s + 6) = 1;
    *(char*)(s + 0xc) = 1;
    *(int*)(s) = 0x14a59d0;
    *(int*)(s + 0x18) = 0;
    *(int*)(s + 0x1c) = 0;
    *(int*)(s + 0x20) = 0x80000000;
    *(int*)(s + 0x14) = 0;
    *(int*)(s + 0x10) = owner;
    void* tm = g_hkMemory;
    void* alloc = hkMemoryAlloc(0xc, 0x12);
    *(unsigned short*)((char*)alloc + 4) = 0xc;
    void* mgr = FUN_0111ccf0();
    *(int*)(s + 0x28) = 0;
    *(int*)(s + 0x24) = (int)mgr;
    return self;
}

// @ 0x010f1a10
void ContinuousSim::destroy()
{
    mVtable = (void*)0x014a59d0;
    if (mResourceMgr) {
        void** vt = *(void***)mResourceMgr;
        ((void(__thiscall*)(void*,int))vt[0])(mResourceMgr, 1);
    }
    if (mCapacityAndFlags >= 0) {
        void* tm = TlsGetValue(g_hkThreadMemoryTls_s010f_1350);
        FUN_0107db10(tm, (int)mArrayData,
                     (mCapacityAndFlags & 0x3fffffff) << 6, 0x14);
    }
    mVtable = &vtable_Simulator_cCreatureAbility;
}

// @ 0x010f1a60
void ContinuousSim::resetEntities(int a, int b, int c)
{
    FUN_01099cb0(a, b, c);
    f0bb0(a, b);
}

// @ 0x010f1a90
void ContinuousSim::collideIsland(SimIsland* island, ProcessCollisionInput* input)
{
    HK_TIMER_SPLIT((const char*)0x014a1e64);
    hkpAgentNnTrack* track = &island->m_agentTrack;
    bool stopped = false;
    if (track->m_numSectors > 0) {
        for (int i = 0; i < track->m_numSectors && !stopped; i++) {
            AgentEntry* agent = (AgentEntry*)track->m_sectors[i];
            char* sectorEnd = (char*)agent +
                ((i + 1 == track->m_numSectors) ? track->m_bytesUsedInLastSector
                                                : track->m_sectorSize);
            while ((char*)agent < sectorEnd) {
                AgentOutput out;
                out.mData = out.mInline;
                out.m3994Bits = 0x7f7fffee;
                out.m3998 = 0;
                JobTableEntry* job = (JobTableEntry*)(agent->mState * 0x3c + 0x1a14 + input->mTableBase);
                input->mpJob = (int)job;
                input->mField0c = job->mKind;
                FUN_010fc180(agent, input, &out);
                HkMemory* mem = (HkMemory*)g_hkMemory;
                int used = mem->mUsedA + mem->mUsedB;
                if (mem->mTotal <= used)
                    mem->mStopped = 1;
                if (mem->mStopped == 1) {
                    stopped = true;
                    break;
                }
                if (out.mData != out.mInline) {
                    void** vt = *(void***)(agent->mpOwner);
                    ((void(__thiscall*)(void*, int, int, ProcessCollisionInput*, AgentOutput*))(vt[5]))(
                        agent->mpOwner, agent->mOwnerArg0, agent->mOwnerArg1, input, &out);
                }
                if (out.m3994 < 3.40282e+38f)
                    FUN_010f0b00((int)this, agent, &out);
                agent = (AgentEntry*)((char*)agent + agent->mSize);
            }
        }
    }
    HK_TIMER_SPLIT((const char*)0x0149cc34);
}

// @ 0x010f1cc0
void ContinuousSim::processAgentCollide(AgentEntry* agent, ProcessCollisionInput* input, AgentOutput* output)
{
    output->m3994Bits = 0x7f7fffee;  // +0x3034 sentinel (garbage float)
    output->m3998 = 0;               // +0x3040
    output->mData = output->mInline; // +0x00 -> +0x30
    JobTableEntry* job = (JobTableEntry*)(agent->mState * 0x3c + 0x1a14 + input->mTableBase);
    input->mpJob = (int)job;
    input->mField0c = job->mKind;
    FUN_010fc180(agent, input, output);
    HkMemory* mem = (HkMemory*)g_hkMemory;
    int used = mem->mUsedA + mem->mUsedB;
    if (mem->mTotal <= used)
        mem->mStopped = 1;
    if (mem->mStopped != 1) {
        if (output->mData != output->mInline) {
            void** vt = *(void***)(agent->mpOwner);
            ((void(__thiscall*)(void*, int, int, ProcessCollisionInput*, AgentOutput*))(vt[5]))(
                agent->mpOwner, agent->mOwnerArg0, agent->mOwnerArg1, input, output);
        }
        if (output->m3994 < 3.40282e+38f)
            FUN_010f0b00((int)this, agent, output);
    }
}

// @ 0x010f1d80
void* ContinuousSim::scalarDelete(unsigned int flags)
{
    mVtable = (void*)0x014a59d0;
    if (mResourceMgr) {
        void** vt = *(void***)mResourceMgr;
        ((void(__thiscall*)(void*, int))vt[0])(mResourceMgr, 1);
    }
    if (mCapacityAndFlags >= 0) {
        void* tm = TlsGetValue(g_hkThreadMemoryTls_s010f_1350);
        FUN_0107db10(tm, (int)mArrayData,
                     (mCapacityAndFlags & 0x3fffffff) << 6, 0x14);
    }
    mVtable = &vtable_Simulator_cCreatureAbility;
    if (flags & 1) {
        void* mem = g_hkMemory;
        void** vt = *(void***)mem;
        ((void(__thiscall*)(void*, void*, unsigned short, int))vt[5])(
            mem, this, *(unsigned short*)((char*)this + 4), 0x12);
    }
    return this;
}

// @ 0x010f25f0
void hkLs_localizedSolveToi(const hkToiResources& toiResources, hkConstraintSolverResources& solverResources, hkToiEvent_s010f_25f0& event, hkToiResourceMgr& toiResourceMgr, hkWorld_s010f_25f0* world, hkArray_s010f_25f0<hkEntity_s010f_25f0*>& entitiesOut, hkFixedArray_s010f_25f0<unsigned char>& entityState)
{
    // confirm the TOI contact point
    {
        hkContactPointConfirmedEvent cpEvent(0, event.m_entities[0]->getCollidable(), event.m_entities[1]->getCollidable(), 0,
                                             (hkContactPoint_s010f_25f0*)event.m_contactPoint, &event.m_material,
                                             world->m_toiCollisionResponseRotateNormal, event.m_seperatingVelocity);
        hkWorldCallbackUtil::fireContactPointConfirmed(world, cpEvent);
        if (event.m_entities[0]->m_contactPointConfirmedListeners)
            hkEntityCallbackUtil::fireContactPointConfirmedInternal(event.m_entities[0], cpEvent);
        if (event.m_entities[1]->m_contactPointConfirmedListeners)
            hkEntityCallbackUtil::fireContactPointConfirmedInternal(event.m_entities[1], cpEvent);
    }

    hkEntity_s010f_25f0* entityA = event.m_entities[0];
    hkEntity_s010f_25f0* entityB = event.m_entities[1];
    hkSimulationIsland_s010f_25f0* island = !entityA->m_fixed ? entityA->m_simulationIsland : entityB->m_simulationIsland;

    hkLocalArray<hkEntity_s010f_25f0*> activeEntities(island->m_entities.getSize());
    hkInplaceArray<hkConstraintSchemaInfo, 64> schemas;
    int firstNonActiveSchema = 0;

    HK_TIMER_SPLIT_s010f_25f0("St2BodyCollide");

    if (!entityA->m_fixed) {
        activeEntities.pushBackUnchecked(entityA);
        hkReal t = event.m_time;
        unsigned char& state = entityState[entityA->m_storageIndex];
        if (state == HK_ENTITY_STATE_NOT_ACTIVE) {
            state = HK_ENTITY_STATE_TRANSFORM_UPDATED;
            hkMotionState_s010f_25f0& ms = entityA->m_motion->m_motionState;
            hkSweptTransformUtil::lerp2(*(hkSweptTransform*)ms.m_sweptTransform, t, *(hkTransform_s010f_25f0*)ms.m_transform);
        }
        entityState[entityA->m_storageIndex] = HK_ENTITY_STATE_ACTIVE;
    }
    if (!entityB->m_fixed) {
        activeEntities.pushBackUnchecked(entityB);
        hkReal t = event.m_time;
        unsigned char& state = entityState[entityB->m_storageIndex];
        if (state == HK_ENTITY_STATE_NOT_ACTIVE) {
            state = HK_ENTITY_STATE_TRANSFORM_UPDATED;
            hkMotionState_s010f_25f0& ms = entityB->m_motion->m_motionState;
            hkSweptTransformUtil::lerp2(*(hkSweptTransform*)ms.m_sweptTransform, t, *(hkTransform_s010f_25f0*)ms.m_transform);
        }
        entityState[entityB->m_storageIndex] = HK_ENTITY_STATE_ACTIVE;
    }

    hkInplaceArray<hkEntity_s010f_25f0*, 64> toBeActivated;
    hkLs_doSimpleCollisionResponse(world, event, world->m_toiCollisionResponseRotateNormal, toBeActivated);
    hkEntity_s010f_25f0* touchedA = toBeActivated[0];
    hkEntity_s010f_25f0* touchedB = (toBeActivated.getSize() > 1) ? toBeActivated[1] : 0;

    hkConstraintSolverResources_noop();
    hkConstraintSolverSetup::internalAddAccumulators(solverResources, activeEntities.m_data, activeEntities.getSize());

    {
        hkInplaceArray<hkEntity_s010f_25f0*, 64> newEntities;
        hkInplaceArray<hkConstraintInstance_s010f_25f0*, 64> newConstraints;
        bool firstIteration = true;
        bool expand = true;

        for (int iterations = toiResources.m_numToiSolverIterations; iterations > 0; iterations--) {
            if (expand) {
                for (;;) {
                    HK_TIMER_SPLIT_s010f_25f0("StExpandSystem");
                    newConstraints.clear();
                    newEntities.clear();
                    int newFirstNonActiveSchema = firstNonActiveSchema;
                    if (!firstIteration) {
                        if (firstNonActiveSchema >= schemas.getSize()) {
                            expand = false;
                            break;
                        }
                        toBeActivated.clear();
                        hkLs_toiCheckValidityOfConstraints(solverResources, *world->m_collisionInput, schemas, newFirstNonActiveSchema,
                                                           toiResources.m_priority, entityState, activeEntities, toBeActivated);
                        if (toBeActivated.getSize() == 0)
                            break;
                    }

                    hkLs_toiActivateEntitiesAndCheckConstraints(*world->m_collisionInput, toiResources.m_priority, event.m_time,
                                                                toBeActivated, entityState, newEntities, newConstraints);

                    HK_TIMER_SPLIT_s010f_25f0("StbuildAcc+Jac");
                    if (!hkConstraintSolverSetup::internalIsMemoryOkForNewAccumulators(solverResources, newEntities.m_data, newEntities.getSize()) ||
                        !hkConstraintSolverSetup::internalIsMemoryOkForNewJacobianElements(solverResources, newConstraints.m_data, newConstraints.getSize()) ||
                        toiResources.m_maxNumConstraints < newConstraints.getSize() + schemas.getSize() ||
                        toiResources.m_maxNumActiveEntities < entitiesOut.getSize() + newEntities.getSize() + activeEntities.getSize() ||
                        toiResources.m_maxNumEntities < entitiesOut.getSize() + toBeActivated.getSize()) {
                        // undo the activation of this expansion step
                        for (int i = 0; i < toBeActivated.getSize(); i++)
                            entityState[toBeActivated[i]->m_storageIndex] = HK_ENTITY_STATE_ACTIVE;
                        for (int j = 0; j < newEntities.getSize(); j++)
                            entityState[newEntities[j]->m_storageIndex] = HK_ENTITY_STATE_TRANSFORM_UPDATED;

                        hkToiResourceMgrResponse response = toiResourceMgr.resourcesDepleted();
                        if (response == HK_TOI_RESOURCE_MGR_RESPONSE_DO_NOT_EXPAND_AND_CONTINUE) {
                            expand = false;
                        } else if (response == HK_TOI_RESOURCE_MGR_RESPONSE_BACKSTEP) {
                            HK_TIMER_SPLIT_s010f_25f0("StBackstep");
                            hkLs_backstepAndFreezeEntireIsland(event.m_time, island, entityState, entitiesOut);
                            HK_TIMER_SPLIT_s010f_25f0("StInvalidTIMs");
                            hkLs_invalidateTims(entitiesOut, world);
                            entitiesOut.clear();
                            return;
                        }
                        break;
                    }

                    hkConstraintSolverSetup::internalAddAccumulators(solverResources, newEntities.m_data, newEntities.getSize());
                    hkConstraintSolverSetup::internalAddJacobianElements(solverResources, newConstraints.m_data, newConstraints.getSize(), schemas);
                    firstNonActiveSchema = newFirstNonActiveSchema;

                    // drop the frozen entities from the active set
                    for (int i = 0; i < activeEntities.getSize(); i++) {
                        if (entityState[activeEntities[i]->m_storageIndex] == HK_ENTITY_STATE_FROZEN) {
                            activeEntities.removeAt(i);
                            i--;
                        }
                    }
                    entitiesOut.insertAt(entitiesOut.getSize(), toBeActivated);

                    activeEntities.reserve(activeEntities.getSize() + newEntities.getSize());
                    for (int k = 0; k < newEntities.getSize(); k++) {
                        if (newEntities[k]->m_motion->getType() != HK_MOTION_FIXED)
                            activeEntities.pushBackUnchecked(newEntities[k]);
                    }

                    hkLs_sortSchemasOfFixedEntitiesFirst(schemas, firstNonActiveSchema, newConstraints.getSize());
                    hkLs_sortSchemasOfFrozenEntitiesFirst(schemas, firstNonActiveSchema, entityState);
                    hkConstraintSolverSetup::resetSolverBuffers(solverResources, 1);

                    if (newConstraints.getSize() == 0 && newEntities.getSize() == 0)
                        break;
                    firstIteration = false;
                }
            }
            firstIteration = false;

            HK_TIMER_SPLIT_s010f_25f0("StSolver");
            if (solverResources.m_schemas[0].m_begin != solverResources.m_schemas[0].m_current)
                hkSolver_solveJacobianSchemas(solverResources.m_solverInfo, solverResources.m_schemas[0].m_begin,
                                              solverResources.m_accumulators, solverResources.m_elemTemp, solverResources.m_solverResults);
            if (solverResources.m_schemas[1].m_begin != solverResources.m_schemas[1].m_current)
                hkSolver_solveJacobianSchemas(solverResources.m_solverInfo, solverResources.m_schemas[1].m_begin,
                                              solverResources.m_accumulators, solverResources.m_elemTemp, solverResources.m_solverResults);
        }

        // solve the forced (TOI priority) constraints until they are satisfied
        HK_TIMER_SPLIT_s010f_25f0("StForcedConstr");
        if (solverResources.m_schemas[1].m_begin != solverResources.m_schemas[1].m_current) {
            hkLs_copyVelocitiesToAccumulators(solverResources, activeEntities);
            hkBool_s010f_25f0 ok = hkLs_areConstraintsSatisfied(solverResources, schemas, world->m_collisionInput, 0);
            if (!ok) {
                int n = toiResources.m_numForcedToiFinalSolverIterations;
                while (n-- != 0) {
                    hkSolver_solveJacobianSchemas(solverResources.m_solverInfo, solverResources.m_schemas[1].m_begin,
                                                  solverResources.m_accumulators, solverResources.m_elemTemp, solverResources.m_solverResults);
                    hkLs_copyVelocitiesToAccumulators(solverResources, activeEntities);
                    ok = hkLs_areConstraintsSatisfied(solverResources, schemas, world->m_collisionInput, 0);
                    if (ok)
                        break;
                }
                if (!ok) {
                    hkInplaceArray<hkConstraintViolationInfo, 32> violatedConstraints;
                    hkLs_areConstraintsSatisfied(solverResources, schemas, world->m_collisionInput, &violatedConstraints);
                    if (toiResourceMgr.cannotSolve(violatedConstraints) == HK_TOI_RESOURCE_MGR_RESPONSE_BACKSTEP) {
                        HK_TIMER_SPLIT_s010f_25f0("StBackstep");
                        hkLs_backstepAndFreezeEntireIsland(event.m_time, island, entityState, entitiesOut);
                        HK_TIMER_SPLIT_s010f_25f0("StInvalidTIMs");
                        hkLs_invalidateTims(entitiesOut, world);
                        entitiesOut.clear();
                        return;
                    }
                }
            }
        }

        // nothing else was touched: at least move the two bodies hit by the simple collision response
        if (entitiesOut.getSize() == 0) {
            entitiesOut.insertAt(0, hkArray_s010f_25f0<hkEntity_s010f_25f0*>(&touchedA, 1, 1));
            entityState[entitiesOut[0]->m_storageIndex] = HK_ENTITY_STATE_FROZEN;
            if (touchedB) {
                entitiesOut.insertAt(1, hkArray_s010f_25f0<hkEntity_s010f_25f0*>(&touchedB, 1, 1));
                entityState[entitiesOut[1]->m_storageIndex] = HK_ENTITY_STATE_FROZEN;
            }
        }

        HK_TIMER_SPLIT_s010f_25f0("StIntegMotions");
        for (int i = 0; i < entitiesOut.getSize(); i++)
            hkSweptTransformUtil::backStepMotionState(event.m_time, entitiesOut[i]->m_motion->m_motionState);
        hkConstraintSolverSetup::oneStepIntegrate(*solverResources.m_stepInfo, entitiesOut.m_data, entitiesOut.getSize(),
                                                  solverResources.m_accumulators);
        hkLs_restoreTransformOnBodiesWithUpdatedTransform(island, entityState);

        HK_TIMER_SPLIT_s010f_25f0("StInvalidTIMs");
        hkLs_invalidateTims(entitiesOut, world);
    }
}

// @ 0x010f3460
void hkContinuousSimulation_s010f_3460::reintegrateAndRecollideEntities(hkEntity_s010f_3460** entities, int numEntities, hkWorld_s010f_3460* world)
{
    if (world->m_lockCount != 0) {
        hkQueuedReintegrateOperation op;
        op.m_type = 0x16;
        op.m_entities = entities;
        op.m_numEntities = (int16_t)numEntities;
        world->queueOperation(&op);
        return;
    }
    world->lockCriticalOperations();

    hkStepInfo_s010f_3460& collisionStepInfo = world->m_collisionInput->m_stepInfo;
    const hkStepInfo_s010f_3460 oldStepInfo = collisionStepInfo;
    const hkStepInfo_s010f_3460 stepInfo(world->m_currentTime, world->m_timeOfNextPsi);
    collisionStepInfo = stepInfo;

    for (int i = 0; i < numEntities; ++i) {
        hkEntity_s010f_3460* entity = entities[i];
        hkSweptTransformUtil_backStepMotionState(world->m_currentTime, *(hkMotionState*)((char*)entity->m_motion + 0x10));
        entity->m_motion->step(stepInfo);
    }

    collideEntitiesBroadPhaseContinuous(entities, numEntities, world, 0);
    resetCollisionInformationForEntities(entities, numEntities, world);
    processAgentsOfEntities(entities, numEntities, world->m_collisionInput, &hkContinuousSimulation_s010f_3460::processAgentCollideContinuous);

    world->unlockAndAttemptToExecutePendingOperations();
    world->m_collisionInput->m_stepInfo = oldStepInfo;
}

// @ 0x010f3600
void hkContinuousSimulation_s010f_3460::collide(hkWorld_s010f_3460* world, const hkStepInfo_s010f_3460& stepInfo)
{
    hkMonitorStamp("TtCollide");

    world->m_dynamicsStepInfoStepInfo = stepInfo;
    world->m_collisionInput->m_stepInfo = stepInfo;
    world->m_dynamicsStepInfoSolverInfo.m_deltaTime = world->m_dynamicsStepInfoSolverInfo.m_invNumSteps * stepInfo.m_deltaTime;
    world->m_dynamicsStepInfoSolverInfo.m_invDeltaTime = (float)world->m_dynamicsStepInfoSolverInfo.m_numSteps * stepInfo.m_invDeltaTime;

    world->lockCriticalOperations();

    // broad phase: refresh every active island's entities
    for (int i = 0; i < world->m_activeSimulationIslands.m_size; ++i) {
        hkSimulationIsland_s010f_3460* island = world->m_activeSimulationIslands.m_data[i];
        collideEntitiesBroadPhaseContinuous(island->m_entities.m_data, island->m_entities.m_size, world, 0);
        if (g_hkMemoryInstance->m_memoryState == 1) {
            world->unlockAndAttemptToExecutePendingOperations();
            hkMonitorStamp("Et");
            return;
        }
    }
    world->unlockAndAttemptToExecutePendingOperations();

    // narrow phase
    world->lockCriticalOperations();
    for (int i = 0; i < world->m_activeSimulationIslands.m_size; ++i) {
        hkSimulationIsland_s010f_3460* island = world->m_activeSimulationIslands.m_data[i];
        collideIslandNarrowPhaseContinuous(island, *world->m_collisionInput);
        if (g_hkMemoryInstance->m_memoryState == 1) {
            world->unlockAndAttemptToExecutePendingOperations();
            hkMonitorStamp("Et");
            return;
        }
        if (world->m_islandPostCollideListeners.m_size != 0) {
            hkMonitorStamp("TtIslandPostCollideCb");
            hkWorldCallbackUtil_s010f_3460::fireIslandPostCollideCallback(world, island, stepInfo);
            hkMonitorStamp("Et");
        }
    }
    world->unlockAndAttemptToExecutePendingOperations();

    if (world->m_worldPostCollideListeners.m_size != 0) {
        hkMonitorStamp("TtPostCollideCB");
        hkWorldCallbackUtil_s010f_3460::firePostCollideCallback(world, stepInfo);
        hkMonitorStamp("Et");
    }
    hkMonitorStamp("Et");
}

// @ 0x010f3a40
void hkContinuousSimulation_s010f_3460::simulateToi(hkWorld_s010f_3460* world, hkToiEvent_s010f_3460& event, hkReal physicsDeltaTime)
{
    if (!g_hkSolverKeycodeValid) {
        g_hkSolverKeycodeValid = hkSolverCheckKeycode(3);
        if (!g_hkSolverKeycodeValid)
            return;
    }

    hkToiResources_s010f_3460 toiResources;
    if (m_toiResourceMgr->beginToiAndSetupResources(event, m_toiEvents, toiResources) == 1)
        return;

    world->lockCriticalOperations();

    // step info from the TOI time to the end of the PSI
    hkConstraintQueryIn queryIn;
    queryIn.m_resultsBegin = 0;
    queryIn.m_resultsSize = 0;
    hkStepInfo_s010f_3460 stepInfo;
    stepInfo.m_startTime = event.m_time;
    stepInfo.m_endTime = world->m_timeOfNextPsi;
    stepInfo.m_deltaTime = stepInfo.m_endTime - stepInfo.m_startTime;
    stepInfo.m_invDeltaTime = hkRealOne / stepInfo.m_deltaTime;

    // single-step solver info derived from the world's
    hkSolverInfo_s010f_3460 solverInfo;
    solverInfo = world->m_dynamicsStepInfoSolverInfo;
    solverInfo.m_deltaTime = physicsDeltaTime;
    solverInfo.m_invDeltaTime = hkRealOne / physicsDeltaTime;
    solverInfo.m_numSteps = 1;
    solverInfo.m_invNumSteps = 1.0f;
    solverInfo.m_globalAccelerationPerSubStep.x = 0.0f; solverInfo.m_globalAccelerationPerSubStep.y = 0.0f;
    solverInfo.m_globalAccelerationPerSubStep.z = 0.0f; solverInfo.m_globalAccelerationPerSubStep.w = 0.0f;
    solverInfo.m_globalAccelerationPerStep.x = 0.0f; solverInfo.m_globalAccelerationPerStep.y = 0.0f;
    solverInfo.m_globalAccelerationPerStep.z = 0.0f; solverInfo.m_globalAccelerationPerStep.w = 0.0f;
    solverInfo.setTauAndDamping(0.5f, 1.4f);

    queryIn.m_substepDeltaTime = solverInfo.m_deltaTime;
    queryIn.m_substepInvDeltaTime = solverInfo.m_invDeltaTime;
    queryIn.m_frameDeltaTime = stepInfo.m_deltaTime;
    queryIn.m_frameInvDeltaTime = stepInfo.m_invDeltaTime;
    queryIn.m_virtualMassFactor = solverInfo.m_invNumSteps;
    queryIn.m_rhsFactor = solverInfo.m_tauDivDamp * solverInfo.m_invDeltaTime;
    queryIn.m_dampingFactor = solverInfo.m_damping;
    queryIn.m_frictionRhsFactor = solverInfo.m_frictionTauDivDamp * solverInfo.m_invDeltaTime;
    queryIn.m_tau = solverInfo.m_tau;
    queryIn.m_damping = solverInfo.m_damping;

    hkConstraintSolverResources_s010f_3460 solverResources;
    hkConstraintSolverSetup_s010f_3460::initializeSolverState(stepInfo, solverInfo, queryIn,
                                                   toiResources.m_solverBuffer, toiResources.m_solverBufferSize, solverResources);
    queryIn.m_resultsBegin = *(void**)(solverResources.m_data + 0x24);
    queryIn.m_resultsSize = *(int*)(solverResources.m_data + 0x2c);

    hkMonitorStampList("LtTOI", "SolveToi");

    // the island of the (first) non-fixed entity of the event
    hkSimulationIsland_s010f_3460* island = event.m_entities[0]->m_fixed ? event.m_entities[1]->m_simulationIsland
                                                              : event.m_entities[0]->m_simulationIsland;
    const int numIslandEntities = island->m_entities.m_size;
    char* flags = hkAllocateStackChars(numIslandEntities);
    hkString_memSet(flags, 0, numIslandEntities);

    // solve; collects the entities moved to the TOI and flags (value 8) those of this island
    hkFixedArray<unsigned char> flagArray;
    flagArray.m_data = (unsigned char*)flags;
    hkEntity_s010f_3460* inplaceStorage[64];
    hkEntityArray involved;
    involved.m_data = inplaceStorage;
    involved.m_size = 0;
    involved.m_capacityAndFlags = 0x80000040;
    hkLs_localizedSolveToi(toiResources, solverResources, event, *m_toiResourceMgr, world, involved, flagArray);
    hkConstraintSolverResources_destruct(&solverResources);

    // drop the queued TOI events of the entities that were just solved
    hkMonitorStamp("StEvtCleanup");
    for (int i = m_toiEvents.m_size - 1; i >= 0; --i) {
        hkToiEvent_s010f_3460& e = m_toiEvents.m_data[i];
        if ((e.m_entities[0]->m_simulationIsland == island && flags[e.m_entities[0]->m_storageIndex] == 8)
            || (e.m_entities[1]->m_simulationIsland == island && flags[e.m_entities[1]->m_storageIndex] == 8)) {
            hkContactPointRemovedEvent removed;
            removed.m_contactPointId = 0xffff;
            removed.m_contactPointMaterial = &e.m_material;
            removed.m_entityA = e.m_entities[0];
            removed.m_entityB = e.m_entities[1];
            removed.m_internalContactMgr = e.m_contactMgr;
            hkWorldCallbackUtil_s010f_3460::fireContactPointRemoved(e.m_entities[0]->m_world, removed);
            if (e.m_entities[0]->m_collisionListeners.m_size != 0)
                hkEntityCallbackUtil_s010f_3460::fireContactPointRemovedInternal(e.m_entities[0], removed);
            if (e.m_entities[1]->m_collisionListeners.m_size != 0)
                hkEntityCallbackUtil_s010f_3460::fireContactPointRemovedInternal(e.m_entities[1], removed);
            // removeAt(i): move the last element into the hole
            --m_toiEvents.m_size;
            m_toiEvents.m_data[i] = m_toiEvents.m_data[m_toiEvents.m_size];
        }
    }

    // recollide everything that moved
    hkMonitorStamp("StCollide");
    const hkStepInfo_s010f_3460 collideStepInfo(event.m_time, world->m_timeOfNextPsi);
    hkProcessCollisionInput_s010f_3460* input = world->m_collisionInput;
    input->m_stepInfo = collideStepInfo;

    hkEntity_s010f_3460** const movedEntities = involved.m_data;
    const int numMoved = involved.m_size;
    if (numMoved != 0) {
        collideEntitiesBroadPhaseContinuous(movedEntities, numMoved, world, 0);
        if (g_hkMemoryInstance->m_memoryState != 1) {
            hkSimulationIsland_s010f_3460* const movedIsland = movedEntities[0]->m_simulationIsland;
            const int numMovedIslandEntities = movedIsland->m_entities.m_size;
            char* touched = hkAllocateStackChars(numMovedIslandEntities);
            int touchedCapacityAndFlags = numMovedIslandEntities | 0x80000000;
            hkString_memSet(touched, 0, numMovedIslandEntities);

            hkProcessCollisionOutput output;
            output.m_toi = HK_REAL_MAX;

            bool outOfMemory = false;
            for (int i = 0; i < numMoved && !outOfMemory; ++i) {
                hkEntity_s010f_3460* entity = movedEntities[i];
                touched[entity->m_storageIndex] = 1;
                for (int j = 0; j < entity->m_collidable.m_collisionEntries.m_size; ++j) {
                    hkCollisionEntry& ce = entity->m_collidable.m_collisionEntries.m_data[j];
                    hkEntity_s010f_3460* partner = ce.m_partner->getOwner();
                    if (partner->m_simulationIsland == movedIsland && touched[partner->m_storageIndex] != 0)
                        continue;
                    hkAgentNnEntry_s010f_3460* agent = ce.m_agentEntry;

                    output.m_firstFreeContactPoint = output.m_contactPoints;
                    output.m_toi = HK_REAL_MAX;
                    output.m_potentialContacts = 0;
                    input->m_collisionQualityInfo = &input->m_dispatcher->m_collisionQualityInfo[agent->m_collisionQualityIndex];
                    input->m_createPredictiveAgents = input->m_collisionQualityInfo->m_useContinuousPhysics;

                    hkAgentNnMachine_processAgent(agent, *input, output);

                    // out-of-memory watchdog
                    {
                        hkMemory* mem = g_hkMemoryInstance;
                        int used = mem->m_pageMemoryUsed + mem->m_sysAllocsSize;
                        if (mem->m_criticalMemoryLimit <= used || (mem->m_criticalMemoryLimit - used) == 0)
                            mem->m_memoryState = 1;
                    }
                    if (g_hkMemoryInstance->m_memoryState == 1) {
                        outOfMemory = true;
                        break;
                    }
                    if (output.m_firstFreeContactPoint != output.m_contactPoints)
                        agent->m_contactMgr->processContact(*agent->m_collidable[0], *agent->m_collidable[1], *input, output);
                    if (output.m_toi < HK_REAL_MAX)
                        addToiEvent(output, *agent);
                }
            }

            hkDeallocateStackChars(touched);
            hkArrayDeallocate(touched, touchedCapacityAndFlags, 1);
        }
    }

    hkArrayDeallocate(involved.m_data, involved.m_capacityAndFlags, sizeof(hkEntity_s010f_3460*));
    hkDeallocateStackChars(flags);

    m_toiResourceMgr->cleanupResources(event, m_toiEvents, toiResources);
    world->unlockAndAttemptToExecutePendingOperations();
    hkMonitorStamp("lt");
}

// @ 0x010f7100
void FUN_010f7100(int param_1, int param_2, ushort *param_3, ushort param_4, uint param_5, uint param_6, int *param_7, int *param_8)
{
    undefined4 *puVar1;
    undefined4 *puVar2;
    ushort *puVar3;
    ushort uVar4;
    ushort uVar5;
    ushort uVar6;
    ushort *puVar7;
    ushort uVar8;
    uint uVar9;
    short sVar10;
    undefined2 *puVar11;
    short *psVar12;

    uVar8 = *param_3;
    uVar9 = (uint)uVar8;
    uVar4 = *(ushort *)(*(int *)(param_1 + 0x58) + -4 + uVar9 * 4);
    puVar3 = (ushort *)(*(int *)(param_1 + 0x58) + uVar9 * 4);
    while (param_5 < uVar4) {
        puVar11 = (undefined2 *)((uint)puVar3[-1] * 0x10 + param_2);
        *puVar3 = uVar4;
        puVar3[1] = puVar3[-1];
        if ((uVar4 & 1) == 0) {
            *puVar11 = (short)uVar9;
        }
        else {
            uVar8 = param_3[3];
            uVar4 = param_3[5];
            uVar5 = param_3[4];
            uVar6 = param_3[1];
            puVar11[2] = (short)uVar9;
            if (-1 < (short)(uVar4 - puVar11[4] | uVar8 - puVar11[1] | puVar11[5] - uVar5 |
                             puVar11[3] - uVar6)) {
                if (param_7[1] == (param_7[2] & 0x3fffffffU)) {
                    FUN_0107f530(param_7, 8);
                }
                puVar1 = (undefined4 *)(*param_7 + param_7[1] * 8);
                param_7[1] = param_7[1] + 1;
                *puVar1 = *(undefined4 *)(param_3 + 6);
                puVar1[1] = *(undefined4 *)(puVar11 + 6);
            }
        }
        puVar3[-1] = param_4;
        uVar9 = uVar9 - 1;
        uVar8 = (ushort)uVar9;
        uVar4 = puVar3[-4];
        puVar3 = puVar3 + -2;
    }
    *param_3 = uVar8;
    *puVar3 = (ushort)param_5;
    puVar1 = (undefined4 *)(*(int *)(param_1 + 0x58) + (uint)param_3[2] * 4);
    sVar10 = 0;
    uVar8 = *(ushort *)(puVar1 + 1);
    while (uVar8 < param_6) {
        sVar10 = sVar10 + 1;
        *puVar1 = puVar1[1];
        psVar12 = (short *)((uint)*(ushort *)((int)puVar1 + 6) * 0x10 + param_2);
        *(ushort *)((int)puVar1 + 6) = param_4;
        if ((uVar8 & 1) == 0) {
            uVar8 = param_3[3];
            uVar4 = param_3[5];
            uVar5 = param_3[4];
            uVar6 = param_3[1];
            *psVar12 = *psVar12 + -1;
            if (-1 < (short)(uVar4 - psVar12[4] | uVar8 - psVar12[1] | psVar12[5] - uVar5 |
                             psVar12[3] - uVar6)) {
                if (param_7[1] == (param_7[2] & 0x3fffffffU)) {
                    FUN_0107f530(param_7, 8);
                }
                puVar2 = (undefined4 *)(*param_7 + param_7[1] * 8);
                param_7[1] = param_7[1] + 1;
                *puVar2 = *(undefined4 *)(param_3 + 6);
                puVar2[1] = *(undefined4 *)(psVar12 + 6);
            }
        }
        else {
            psVar12[2] = psVar12[2] + -1;
        }
        uVar8 = *(ushort *)(puVar1 + 2);
        puVar1 = puVar1 + 1;
    }
    param_3[2] = param_3[2] + sVar10;
    puVar1 = (undefined4 *)(*(int *)(param_1 + 0x58) + (uint)param_3[2] * 4);
    sVar10 = 0;
    uVar8 = *(ushort *)(puVar1 + -1);
    while (param_6 < uVar8) {
        sVar10 = sVar10 + -1;
        psVar12 = (short *)((uint)*(ushort *)((int)puVar1 + -2) * 0x10 + param_2);
        *puVar1 = puVar1[-1];
        *(ushort *)((int)puVar1 + -2) = param_4;
        if ((uVar8 & 1) == 0) {
            uVar8 = param_3[3];
            uVar4 = param_3[5];
            uVar5 = param_3[4];
            uVar6 = param_3[1];
            *psVar12 = *psVar12 + 1;
            if (-1 < (short)(uVar4 - psVar12[4] | uVar8 - psVar12[1] | psVar12[5] - uVar5 |
                             psVar12[3] - uVar6)) {
                if (param_8[1] == (param_8[2] & 0x3fffffffU)) {
                    FUN_0107f530(param_8, 8);
                }
                puVar2 = (undefined4 *)(*param_8 + param_8[1] * 8);
                param_8[1] = param_8[1] + 1;
                *puVar2 = *(undefined4 *)(param_3 + 6);
                puVar2[1] = *(undefined4 *)(psVar12 + 6);
            }
        }
        else {
            psVar12[2] = psVar12[2] + 1;
        }
        uVar8 = *(ushort *)(puVar1 + -2);
        puVar1 = puVar1 + -1;
    }
    param_3[2] = param_3[2] + sVar10;
    *(short *)puVar1 = (short)param_6;
    puVar3 = (ushort *)(*(int *)(param_1 + 0x58) + (uint)*param_3 * 4);
    uVar9 = (uint)puVar3[2];
    sVar10 = 0;
    if (param_5 <= uVar9) {
        *param_3 = *param_3;
        *puVar3 = (ushort)param_5;
        return;
    }
    do {
        puVar7 = puVar3 + 2;
        psVar12 = (short *)((uint)puVar3[3] * 0x10 + param_2);
        sVar10 = sVar10 + 1;
        *(undefined4 *)puVar3 = *(undefined4 *)puVar7;
        puVar3[3] = param_4;
        if ((uVar9 & 1) == 0) {
            *psVar12 = *psVar12 + -1;
        }
        else {
            uVar8 = param_3[3];
            uVar4 = param_3[5];
            uVar5 = param_3[4];
            uVar6 = param_3[1];
            psVar12[2] = psVar12[2] + -1;
            if (-1 < (short)(uVar4 - psVar12[4] | uVar8 - psVar12[1] | psVar12[5] - uVar5 |
                             psVar12[3] - uVar6)) {
                if (param_8[1] == (param_8[2] & 0x3fffffffU)) {
                    FUN_0107f530(param_8, 8);
                }
                puVar1 = (undefined4 *)(*param_8 + param_8[1] * 8);
                param_8[1] = param_8[1] + 1;
                *puVar1 = *(undefined4 *)(param_3 + 6);
                puVar1[1] = *(undefined4 *)(psVar12 + 6);
            }
        }
        uVar9 = (uint)puVar3[4];
        puVar3 = puVar7;
    } while (uVar9 < param_5);
    *param_3 = *param_3 + sVar10;
    *puVar7 = (ushort)param_5;
}

// @ 0x010f7480
void FUN_010f7480(int param_1, int param_2, short *param_3, ushort param_4, uint param_5, uint param_6, int *param_7, int *param_8)
{
    undefined4 *puVar1;
    undefined4 *puVar2;
    ushort *puVar3;
    ushort uVar4;
    short sVar5;
    short sVar6;
    short sVar7;
    short sVar8;
    ushort *puVar9;
    ushort uVar10;
    uint uVar11;
    short sVar12;
    short *psVar13;

    uVar10 = param_3[1];
    uVar11 = (uint)uVar10;
    uVar4 = *(ushort *)(*(int *)(param_1 + 100) + -4 + uVar11 * 4);
    puVar3 = (ushort *)(*(int *)(param_1 + 100) + uVar11 * 4);
    while (param_5 < uVar4) {
        psVar13 = (short *)((uint)puVar3[-1] * 0x10 + param_2);
        *puVar3 = uVar4;
        puVar3[1] = puVar3[-1];
        if ((uVar4 & 1) == 0) {
            psVar13[1] = (short)uVar11;
        }
        else {
            sVar12 = param_3[4];
            sVar5 = param_3[5];
            sVar6 = *param_3;
            sVar7 = param_3[2];
            psVar13[3] = (short)uVar11;
            if (-1 < (short)(sVar5 - psVar13[4] | psVar13[5] - sVar12 | psVar13[2] - sVar6 |
                             sVar7 - *psVar13)) {
                if (param_7[1] == (param_7[2] & 0x3fffffffU)) {
                    FUN_0107f530(param_7, 8);
                }
                puVar1 = (undefined4 *)(*param_7 + param_7[1] * 8);
                param_7[1] = param_7[1] + 1;
                *puVar1 = *(undefined4 *)(param_3 + 6);
                puVar1[1] = *(undefined4 *)(psVar13 + 6);
            }
        }
        puVar3[-1] = param_4;
        uVar11 = uVar11 - 1;
        uVar10 = (ushort)uVar11;
        uVar4 = puVar3[-4];
        puVar3 = puVar3 + -2;
    }
    param_3[1] = uVar10;
    *puVar3 = (ushort)param_5;
    puVar1 = (undefined4 *)(*(int *)(param_1 + 100) + (uint)(ushort)param_3[3] * 4);
    sVar12 = 0;
    uVar10 = *(ushort *)(puVar1 + 1);
    while (uVar10 < param_6) {
        sVar12 = sVar12 + 1;
        *puVar1 = puVar1[1];
        psVar13 = (short *)((uint)*(ushort *)((int)puVar1 + 6) * 0x10 + param_2);
        *(ushort *)((int)puVar1 + 6) = param_4;
        if ((uVar10 & 1) == 0) {
            sVar5 = param_3[4];
            sVar6 = param_3[5];
            sVar7 = *param_3;
            sVar8 = param_3[2];
            psVar13[1] = psVar13[1] + -1;
            if (-1 < (short)(sVar6 - psVar13[4] | psVar13[5] - sVar5 | psVar13[2] - sVar7 |
                             sVar8 - *psVar13)) {
                if (param_7[1] == (param_7[2] & 0x3fffffffU)) {
                    FUN_0107f530(param_7, 8);
                }
                puVar2 = (undefined4 *)(*param_7 + param_7[1] * 8);
                param_7[1] = param_7[1] + 1;
                *puVar2 = *(undefined4 *)(param_3 + 6);
                puVar2[1] = *(undefined4 *)(psVar13 + 6);
            }
        }
        else {
            psVar13[3] = psVar13[3] + -1;
        }
        uVar10 = *(ushort *)(puVar1 + 2);
        puVar1 = puVar1 + 1;
    }
    param_3[3] = param_3[3] + sVar12;
    puVar1 = (undefined4 *)(*(int *)(param_1 + 100) + (uint)(ushort)param_3[3] * 4);
    sVar12 = 0;
    uVar10 = *(ushort *)(puVar1 + -1);
    while (param_6 < uVar10) {
        sVar12 = sVar12 + -1;
        psVar13 = (short *)((uint)*(ushort *)((int)puVar1 + -2) * 0x10 + param_2);
        *puVar1 = puVar1[-1];
        *(ushort *)((int)puVar1 + -2) = param_4;
        if ((uVar10 & 1) == 0) {
            sVar5 = param_3[4];
            sVar6 = param_3[5];
            sVar7 = *param_3;
            sVar8 = param_3[2];
            psVar13[1] = psVar13[1] + 1;
            if (-1 < (short)(sVar6 - psVar13[4] | psVar13[5] - sVar5 | psVar13[2] - sVar7 |
                             sVar8 - *psVar13)) {
                if (param_8[1] == (param_8[2] & 0x3fffffffU)) {
                    FUN_0107f530(param_8, 8);
                }
                puVar2 = (undefined4 *)(*param_8 + param_8[1] * 8);
                param_8[1] = param_8[1] + 1;
                *puVar2 = *(undefined4 *)(param_3 + 6);
                puVar2[1] = *(undefined4 *)(psVar13 + 6);
            }
        }
        else {
            psVar13[3] = psVar13[3] + 1;
        }
        uVar10 = *(ushort *)(puVar1 + -2);
        puVar1 = puVar1 + -1;
    }
    param_3[3] = param_3[3] + sVar12;
    *(short *)puVar1 = (short)param_6;
    puVar3 = (ushort *)(*(int *)(param_1 + 100) + (uint)(ushort)param_3[1] * 4);
    uVar11 = (uint)puVar3[2];
    sVar12 = 0;
    if (param_5 <= uVar11) {
        param_3[1] = param_3[1];
        *puVar3 = (ushort)param_5;
        return;
    }
    do {
        puVar9 = puVar3 + 2;
        psVar13 = (short *)((uint)puVar3[3] * 0x10 + param_2);
        sVar12 = sVar12 + 1;
        *(undefined4 *)puVar3 = *(undefined4 *)puVar9;
        puVar3[3] = param_4;
        if ((uVar11 & 1) == 0) {
            psVar13[1] = psVar13[1] + -1;
        }
        else {
            sVar5 = param_3[4];
            sVar6 = param_3[5];
            sVar7 = param_3[2];
            sVar8 = *param_3;
            psVar13[3] = psVar13[3] + -1;
            if (-1 < (short)(sVar6 - psVar13[4] | psVar13[5] - sVar5 | sVar7 - *psVar13 |
                             psVar13[2] - sVar8)) {
                if (param_8[1] == (param_8[2] & 0x3fffffffU)) {
                    FUN_0107f530(param_8, 8);
                }
                puVar1 = (undefined4 *)(*param_8 + param_8[1] * 8);
                param_8[1] = param_8[1] + 1;
                *puVar1 = *(undefined4 *)(param_3 + 6);
                puVar1[1] = *(undefined4 *)(psVar13 + 6);
            }
        }
        uVar11 = (uint)puVar3[4];
        puVar3 = puVar9;
    } while (uVar11 < param_5);
    param_3[1] = param_3[1] + sVar12;
    *puVar9 = (ushort)param_5;
}

// @ 0x010f7800
void hk3AxisSweep::updateAabbs(undefined4 *param_2, float *param_3, int param_4, int *param_5, int *param_6)
{
    int param_1 = (int)this;
    undefined4 *local_78;
    float local_70;
    float local_6c;
    float local_68;
    float local_64;
    float local_60;
    float local_5c;
    float local_58;
    float local_54;
    ushort kMinX;
    ushort kMinY;
    ushort kMinZ;
    ushort kMaxX;
    ushort kMaxY;
    ushort kMaxZ;
    int iVar1;
    int iVar2;
    int iVar4;

    local_78 = param_2;
    if (param_2 < param_2 + param_4) {
        do {
            local_70 = (param_3[0] + *(float *)(param_1 + 0x10)) * *(float *)(param_1 + 0x30);
            local_6c = (param_3[1] + *(float *)(param_1 + 0x14)) * *(float *)(param_1 + 0x34);
            local_68 = (param_3[2] + *(float *)(param_1 + 0x18)) * *(float *)(param_1 + 0x38);
            local_64 = (param_3[3] + *(float *)(param_1 + 0x1c)) * *(float *)(param_1 + 0x3c);
            if (DAT_015ba360 <= local_70) {
                local_70 = DAT_015ba360;
            }
            if (DAT_015ba364 <= local_6c) {
                local_6c = DAT_015ba364;
            }
            if (DAT_015ba368 <= local_68) {
                local_68 = DAT_015ba368;
            }
            if (DAT_015ba36c <= local_64) {
                local_64 = DAT_015ba36c;
            }
            if (local_70 <= 0.0f) {
                local_70 = 0.0f;
            }
            if (local_6c <= 0.0f) {
                local_6c = 0.0f;
            }
            if (local_68 <= 0.0f) {
                local_68 = 0.0f;
            }
            if (local_64 <= 0.0f) {
                local_64 = 0.0f;
            }
            local_70 = local_70 + 65536.0f;
            kMinX = (ushort)(*(uint *)&local_70 >> 7);
            local_6c = local_6c + 65536.0f;
            kMinY = (ushort)(*(uint *)&local_6c >> 7);
            local_68 = local_68 + 65536.0f;
            kMinZ = (ushort)(*(uint *)&local_68 >> 7);
            local_64 = local_64 + 65536.0f;
            local_60 = (param_3[4] + *(float *)(param_1 + 0x20)) * *(float *)(param_1 + 0x30);
            local_5c = (param_3[5] + *(float *)(param_1 + 0x24)) * *(float *)(param_1 + 0x34);
            local_58 = (param_3[6] + *(float *)(param_1 + 0x28)) * *(float *)(param_1 + 0x38);
            local_54 = (param_3[7] + *(float *)(param_1 + 0x2c)) * *(float *)(param_1 + 0x3c);
            if (DAT_015ba360 <= local_60) {
                local_60 = DAT_015ba360;
            }
            if (DAT_015ba364 <= local_5c) {
                local_5c = DAT_015ba364;
            }
            if (DAT_015ba368 <= local_58) {
                local_58 = DAT_015ba368;
            }
            if (DAT_015ba36c <= local_54) {
                local_54 = DAT_015ba36c;
            }
            if (local_60 <= 0.0f) {
                local_60 = 0.0f;
            }
            if (local_5c <= 0.0f) {
                local_5c = 0.0f;
            }
            if (local_58 <= 0.0f) {
                local_58 = 0.0f;
            }
            if (local_54 <= 0.0f) {
                local_54 = 0.0f;
            }
            local_60 = local_60 + 65536.0f;
            kMaxX = (ushort)(*(uint *)&local_60 >> 7);
            local_5c = local_5c + 65536.0f;
            kMaxY = (ushort)(*(uint *)&local_5c >> 7);
            local_58 = local_58 + 65536.0f;
            kMaxZ = (ushort)(*(uint *)&local_58 >> 7);
            local_54 = local_54 + 65536.0f;
            iVar1 = *(int *)(param_1 + 0x40);
            iVar2 = *(int *)*local_78;
            iVar4 = iVar2 * 0x10 + iVar1;
            FUN_010f6ea0(param_1, iVar1, iVar4, iVar2,
                         (uint)kMinX & 0xfffe, (uint)kMaxX & 0xffff | 1,
                         param_5, param_6);
            FUN_010f7100(param_1, iVar1, (ushort *)iVar4, (ushort)iVar2,
                         (uint)kMinY & 0xfffe, (uint)kMaxY & 0xffff | 1,
                         param_5, param_6);
            FUN_010f7480(param_1, iVar1, (short *)iVar4, (ushort)iVar2,
                         (uint)kMinZ & 0xfffe, (uint)kMaxZ & 0xffff | 1,
                         param_5, param_6);
            param_3 = param_3 + 8;
            local_78 = local_78 + 1;
        } while (local_78 < param_2 + param_4);
    }
}

// @ 0x010fb590
void hk3AxisSweep_s010f_add0::removeObjectBatch(hkArray_s010f_add0<hkBroadPhaseHandle_s010f_add0*>& removeObjectList, hkArray_s010f_add0<hkBroadPhaseHandlePair>& newPairs)
{
	const int numNodes = m_nodes.getSize();
	const int numRemove = removeObjectList.getSize();

	// find every overlap the removed objects are still part of (bitfield with one bit per removed node)
	{
		hkLocalBuffer<hkUint32> bitFieldBuffer((numNodes >> 5) + 8);
		hkUint32* bitField = bitFieldBuffer.begin();
		{
			hkUint32* p = bitField;
			for (int i = (numNodes >> 3) >> 4; i >= 0; i--)
			{
				hkUint32* q = p;
				p += 4;
				q[0] = 0;
				q[1] = 0;
				q[2] = 0;
				q[3] = 0;
			}
		}
		for (int i = 0; i < numRemove; i++)
			hkToggleBit(bitField, removeObjectList[i]->m_id);
		queryBatchAabbSub(bitField, newPairs, false);
	}

	// mark the removed nodes with the address of a stack sentinel and clear their handle ids
	int removedSentinel = 0;
	for (int i = 0; i < numRemove; i++)
	{
		hkBroadPhaseHandle_s010f_add0* handle = removeObjectList[i];
		m_nodes[handle->m_id].m_handle = (hkBroadPhaseHandle_s010f_add0*)&removedSentinel;
		handle->m_id = 0;
	}
	hkBroadPhaseHandle_s010f_add0* const sentinel = (hkBroadPhaseHandle_s010f_add0*)&removedSentinel;

	// compact the node array from both ends, recording where every node went
	int* relocationRaw = (int*)hkThreadMemory_s010f_add0::getInstance().allocateStack(numNodes * (int)sizeof(int));
	hkArray_s010f_add0<int> relocations(relocationRaw, numNodes, numNodes);

	int numKept = 0;
	int lastNode = m_nodes.getSize() - 1;
	while (numKept <= lastNode)
	{
		if (m_nodes[lastNode].m_handle == sentinel)
		{
			relocations[lastNode] = -1;
			lastNode--;
			continue;
		}
		if (m_nodes[numKept].m_handle == sentinel)
		{
			m_nodes[numKept] = m_nodes[lastNode];
			relocations[lastNode] = numKept;
			relocations[numKept] = -1;
			hkBroadPhaseHandle_s010f_add0* handle = m_nodes[numKept].m_handle;
			const hkUint32 handleBits = (hkUint32)handle;
			if ((handleBits & 1) == 0)
				handle->m_id = (hkUint32)numKept;
			else
				m_markers[handleBits >> 1].m_nodeIndex = BpInt(numKept);
		}
		else
		{
			relocations[numKept] = numKept;
		}
		numKept++;
	}

	const int newNumNodes = lastNode + 1;
	int capacity = m_nodes.m_capacityAndFlags & hkArray_s010f_add0<hkBpNode>::CAPACITY_MASK;
	if (capacity < newNumNodes)
	{
		int newCapacity = capacity * 2;
		if (newNumNodes >= newCapacity)
			newCapacity = newNumNodes;
		hkArrayUtil_s010f_add0::_reserveExactly(&m_nodes, newCapacity, (int)sizeof(hkBpNode));
	}
	m_nodes.m_size = newNumNodes;
	hkBpNode* nodes = m_nodes.begin();

	for (int axis = 0; axis < 3; axis++)
		m_axis[axis].removeBatch(nodes, axis, relocations);

	// the marker nodes store their y/z endpoint positions in max_y/max_z: shift them by the removed endpoints
	if (m_numMarkers)
	{
		const int numRemovedEndPoints = numRemove * 2;
		for (int i = 0; i < m_numMarkers; i++)
		{
			hkBpNode& markerNode = m_nodes[m_markers[i].m_nodeIndex];
			markerNode.max_y = BpInt(markerNode.max_y - numRemovedEndPoints);
			markerNode.max_z = BpInt(markerNode.max_z - numRemovedEndPoints);
			hkArray_s010f_add0<BpInt>& overlaps = m_markers[i].m_overlappingObjects;
			for (int k = 0; k < overlaps.getSize(); k++)
				overlaps[k] = BpInt(relocations[overlaps[k]]);
		}
	}

	hkThreadMemory_s010f_add0::getInstance().deallocateStack(relocationRaw);
}

// @ 0x010fbb80
template <> void hkArray_s010f_add0<hkClass*>::insertAt(int index, const hkArray_s010f_add0<hkClass*>& src)
{
	const int numToInsert = src.m_size;
	const int newSize = m_size + numToInsert;
	int capacity = m_capacityAndFlags & CAPACITY_MASK;
	if (capacity < newSize)
	{
		int newCapacity = capacity * 2;
		if (newSize >= newCapacity)
			newCapacity = newSize;
		hkArrayReserveExactly(this, newCapacity, (int)sizeof(hkClass*));
	}
	const int numToMove = m_size - index;
	for (int i = numToMove - 1; i >= 0; i--)
		m_data[index + numToInsert + i] = m_data[index + i];
	for (int i = numToInsert - 1; i >= 0; i--)
		m_data[index + i] = src.m_data[i];
	m_size = newSize;
}

// @ 0x010fd4c0
void* __cdecl hkCapsuleTriangleAgent3_process(const hkAgent3ProcessInput& input, hkAgentEntry_s010f_d4c0* entry, void* agentData, hkVector4_s010f_d4c0* separatingNormal, hkProcessCollisionOutput_s010f_d4c0& result)
{
    HK_TIMER_CMD("TtCapsTri3");

    const hkCdBody_s010f_d4c0* bodyA = input.m_bodyA;
    const hkCdBody_s010f_d4c0* bodyB = input.m_bodyB;
    const hkCapsuleShape*  capsule  = (const hkCapsuleShape*)bodyA->m_shape;
    const hkTriangleShape* triangle = (const hkTriangleShape*)bodyB->m_shape;
    const hkTransform_s010f_d4c0* wTa = bodyA->m_motion;
    const hkTransform_s010f_d4c0* wTb = bodyB->m_motion;

    // capsule segment endpoints in world space
    hkVector4_s010f_d4c0 capSegment[2];
    capSegment[0].x = wTa->m_rotation.c0.x * capsule->m_vertex[0].x
                    + (wTa->m_rotation.c0.y * capsule->m_vertex[0].y
                       + wTa->m_rotation.c0.z * capsule->m_vertex[0].z) + wTa->m_translation.x;
    capSegment[0].y = wTa->m_rotation.c1.x * capsule->m_vertex[0].x
                    + (wTa->m_rotation.c1.y * capsule->m_vertex[0].y
                       + wTa->m_rotation.c1.z * capsule->m_vertex[0].z) + wTa->m_translation.y;
    capSegment[0].z = wTa->m_rotation.c2.x * capsule->m_vertex[0].x
                    + (wTa->m_rotation.c2.y * capsule->m_vertex[0].y
                       + wTa->m_rotation.c2.z * capsule->m_vertex[0].z) + wTa->m_translation.z;
    capSegment[0].w = 0.0f;
    capSegment[1].x = wTa->m_rotation.c0.x * capsule->m_vertex[1].x
                    + (wTa->m_rotation.c0.y * capsule->m_vertex[1].y
                       + wTa->m_rotation.c0.z * capsule->m_vertex[1].z) + wTa->m_translation.x;
    capSegment[1].y = wTa->m_rotation.c1.x * capsule->m_vertex[1].x
                    + (wTa->m_rotation.c1.y * capsule->m_vertex[1].y
                       + wTa->m_rotation.c1.z * capsule->m_vertex[1].z) + wTa->m_translation.y;
    capSegment[1].z = wTa->m_rotation.c2.x * capsule->m_vertex[1].x
                    + (wTa->m_rotation.c2.y * capsule->m_vertex[1].y
                       + wTa->m_rotation.c2.z * capsule->m_vertex[1].z) + wTa->m_translation.z;
    capSegment[1].w = 0.0f;

    // triangle vertices in world space
    hkVector4_s010f_d4c0 tri[3];
    tri[0].x = wTb->m_rotation.c0.x * triangle->m_vertex[0].x
             + (wTb->m_rotation.c0.y * triangle->m_vertex[0].y
                + wTb->m_rotation.c0.z * triangle->m_vertex[0].z) + wTb->m_translation.x;
    tri[0].y = wTb->m_rotation.c1.x * triangle->m_vertex[0].x
             + (wTb->m_rotation.c1.y * triangle->m_vertex[0].y
                + wTb->m_rotation.c1.z * triangle->m_vertex[0].z) + wTb->m_translation.y;
    tri[0].z = wTb->m_rotation.c2.x * triangle->m_vertex[0].x
             + (wTb->m_rotation.c2.y * triangle->m_vertex[0].y
                + wTb->m_rotation.c2.z * triangle->m_vertex[0].z) + wTb->m_translation.z;
    tri[0].w = 0.0f;
    tri[1].x = wTb->m_rotation.c0.x * triangle->m_vertex[1].x
             + (wTb->m_rotation.c0.y * triangle->m_vertex[1].y
                + wTb->m_rotation.c0.z * triangle->m_vertex[1].z) + wTb->m_translation.x;
    tri[1].y = wTb->m_rotation.c1.x * triangle->m_vertex[1].x
             + (wTb->m_rotation.c1.y * triangle->m_vertex[1].y
                + wTb->m_rotation.c1.z * triangle->m_vertex[1].z) + wTb->m_translation.y;
    tri[1].z = wTb->m_rotation.c2.x * triangle->m_vertex[1].x
             + (wTb->m_rotation.c2.y * triangle->m_vertex[1].y
                + wTb->m_rotation.c2.z * triangle->m_vertex[1].z) + wTb->m_translation.z;
    tri[1].w = 0.0f;
    tri[2].x = wTb->m_rotation.c0.x * triangle->m_vertex[2].x
             + (wTb->m_rotation.c0.y * triangle->m_vertex[2].y
                + wTb->m_rotation.c0.z * triangle->m_vertex[2].z) + wTb->m_translation.x;
    tri[2].y = wTb->m_rotation.c1.x * triangle->m_vertex[2].x
             + (wTb->m_rotation.c1.y * triangle->m_vertex[2].y
                + wTb->m_rotation.c1.z * triangle->m_vertex[2].z) + wTb->m_translation.y;
    tri[2].z = wTb->m_rotation.c2.x * triangle->m_vertex[2].x
             + (wTb->m_rotation.c2.y * triangle->m_vertex[2].y
                + wTb->m_rotation.c2.z * triangle->m_vertex[2].z) + wTb->m_translation.z;
    tri[2].w = 0.0f;

    // 3 contact points, 0x20 bytes each (position, separating normal)
    hkProcessCdPoint_s010f_d4c0 points[3];
    hkCollideCapsuleUtilManifoldCapsVsTriangle(capSegment, capsule->m_radius, tri, triangle->m_radius,
                                               &input.m_aTb.m_rotation.c2, 0x7f7fffee, 1, points);

    // pick the deepest of the first two contacts as the separating normal
    int numPoints = 0;
    if (points[0].m_separatingNormal.w <= points[1].m_separatingNormal.w)
    {
        separatingNormal->x = points[1].m_separatingNormal.x;
        separatingNormal->y = points[1].m_separatingNormal.y;
        separatingNormal->z = points[1].m_separatingNormal.z;
        separatingNormal->w = points[1].m_separatingNormal.w;
        numPoints = 1;
    }
    else
    {
        separatingNormal->x = points[0].m_separatingNormal.x;
        separatingNormal->y = points[0].m_separatingNormal.y;
        separatingNormal->z = points[0].m_separatingNormal.z;
        separatingNormal->w = points[0].m_separatingNormal.w;
    }

    hkContactPointId ids[3];
    ids[0] = ((const hkContactPointId*)agentData)[0];
    ids[1] = ((const hkContactPointId*)agentData)[1];
    ids[2] = ((const hkContactPointId*)agentData)[2];

    hkContactMgr_s010f_d4c0* contactMgr = input.m_contactMgr;
    const float tolerance = input.m_input->m_tolerance;

    for (int i = 0; i < 3; ++i)
    {
        hkProcessCdPoint_s010f_d4c0* cp = &points[i];
        if (tolerance <= cp->m_separatingNormal.w)
        {
            // point is too far away: drop the cached one
            if (ids[i] != 0xffff)
                contactMgr->removeContactPoint(ids[i]);
            ids[i] = 0xffff;
            continue;
        }

        hkContactPointId id = ids[i];
        if (id == 0xffff)
        {
            if (result.m_potentialContacts)
            {
                if (contactMgr->reserveContactPoints(1) != 0)
                {
                    ids[i] = 0xffff;
                    continue;
                }
                hkPendingContact* pending = result.m_potentialContacts;
                result.m_potentialContacts = pending + 1;
                hkProcessCdPoint_s010f_d4c0* resume = result.m_firstFreeContactPoint;
                pending->m_entry     = entry;
                pending->m_contact   = &resume;
                pending->m_agentData = agentData;
                id = 0xffff;
            }
            else
            {
                id = contactMgr->addContactPoint(*bodyA, *bodyB, *(const hkCollisionInput_s010f_d4c0*)input.m_input, *cp);
                if (id == 0xffff)
                {
                    ids[i] = 0xffff;
                    continue;
                }
            }
        }

        hkProcessCdPoint_s010f_d4c0* out = result.m_firstFreeContactPoint;
        result.m_firstFreeContactPoint = out + 1;
        out->m_position         = cp->m_position;
        out->m_separatingNormal = cp->m_separatingNormal;
        out->m_contactPointId   = id;

        if (i == numPoints && result.m_potentialContacts)
        {
            *result.m_potentialContacts->m_contact = out;
            result.m_potentialContacts = (hkPendingContact*)((char*)result.m_potentialContacts + 4);
        }
        ids[i] = id;
    }

    ((hkContactPointId*)agentData)[0] = ids[0];
    ((hkContactPointId*)agentData)[1] = ids[1];
    ((hkContactPointId*)agentData)[2] = ids[2];
    entry->m_numContactPoints = (unsigned char)numPoints;

    HK_TIMER_CMD(g_hkTimerEndTag1);
    return (char*)agentData + 0x20;
}

// @ 0x010fda70
void __cdecl hkCapsuleTriangleAgent3_register(hkCollisionDispatcher_s010f_d4c0* dispatcher)
{
    const int typeA = 8;
    const int typeB = 6;
    hkCollisionDispatcher_s010f_d4c0::Agent3Funcs funcs;
    funcs.m_createFunc          = (void* (*)())&hkCapsuleTriangleAgent3_create;
    funcs.m_destroyFunc         = (void (*)())&hkCapsuleTriangleAgent3_destroy;
    funcs.m_cleanupFunc         = (void (*)())&hkCapsuleTriangleAgent3_cleanup;
    funcs.m_removePointFunc     = (void (*)())&hkCapsuleTriangleAgent3_removePoint;
    funcs.m_commitPotentialFunc = (void (*)())&hkCapsuleTriangleAgent3_commitPotential;
    funcs.m_createZombieFunc    = (void (*)())&hkBoxBox_createZombie;
    funcs.m_updateFilterFunc    = 0;
    funcs.m_invalidateTimFunc   = 0;
    funcs.m_warpTimeFunc        = 0;
    funcs.m_sepNormalFunc       = (void (*)())&hkCapsuleTriangleAgent3_sepNormal;
    funcs.m_processFunc         = (void* (*)())&hkCapsuleTriangleAgent3_process;
    funcs.m_isPredictive        = hkBool_s010f_d4c0(false);
    funcs.m_ignoreSymmetricVersion = hkBool_s010f_d4c0(false);
    dispatcher->registerAgent3(funcs, typeA, typeB);
}

// @ 0x010fdae0
void __cdecl hkBoxBoxAgent3_removePoint(hkAgentEntry_s010f_d4c0* entry, void* agentData, hkContactPointId id)
{
    hkBoxBoxManifold* manifold = (hkBoxBoxManifold*)agentData;
    int n = manifold->m_numPoints;
    for (int i = 0; i < n; ++i)
    {
        if (manifold->m_contactPoints[i].m_contactPointId == id)
        {
            manifold->removePoint(i);
            entry->m_numContactPoints = (unsigned char)(entry->m_numContactPoints - 1);
            return;
        }
    }
}

// @ 0x010fdb20
void __cdecl hkBoxBoxAgent3_commitPotential(hkAgentEntry_s010f_d4c0* entry, void* agentData, hkContactPointId id)
{
    (void)entry;
    hkBoxBoxManifold* manifold = (hkBoxBoxManifold*)agentData;
    const int n = manifold->m_numPoints;
    for (int i = 0; i < n; ++i)
    {
        if (manifold->m_contactPoints[i].m_contactPointId == 0xffff)
        {
            manifold->m_contactPoints[i].m_contactPointId = id;
            break;
        }
    }
}

// @ 0x010fdb50
void* __cdecl hkBoxBoxAgent3_create(const hkAgent3Input& input, hkAgentEntry_s010f_d4c0* entry, void* agentData)
{
    hkBoxBoxManifold* manifold = (hkBoxBoxManifold*)agentData;
    if (manifold)
        manifold->init();
    return (char*)manifold + 0x50;
}

// @ 0x010fdb70
void* __cdecl hkBoxBoxAgent3_destroy(hkAgentEntry_s010f_d4c0* entry, void* agentData, hkContactMgr_s010f_d4c0* mgr)
{
    hkBoxBoxManifold* manifold = (hkBoxBoxManifold*)agentData;
    for (unsigned int i = 0; i < manifold->m_numPoints; ++i)
    {
        hkContactPointId id = manifold->m_contactPoints[i].m_contactPointId;
        if (id != 0xffff)
            mgr->removeContactPoint(id);
    }
    manifold->m_numPoints = 0;
    entry->m_numContactPoints = 0;
    return (char*)manifold + 0x50;
}

// @ 0x010fdbe0
void* __cdecl hkBoxBoxAgent3_process(const hkAgent3ProcessInput& input, hkAgentEntry_s010f_d4c0* entry, void* agentData, hkVector4_s010f_d4c0* separatingNormal, hkProcessCollisionOutput_s010f_d4c0& result)
{
    (void)separatingNormal;
    HK_TIMER_CMD("TtBoxBox3");

    const hkCdBody_s010f_d4c0* bodyA = input.m_bodyA;
    const hkCdBody_s010f_d4c0* bodyB = input.m_bodyB;
    const hkShape_s010f_d4c0*  shapeA = bodyA->m_shape;
    const hkShape_s010f_d4c0*  shapeB = bodyB->m_shape;

    hkBoxBoxCollisionDetection cd;
    cd.m_bodyA = bodyA;
    cd.m_bodyB = bodyB;
    cd.m_env = (const hkCollisionInput_s010f_d4c0*)input.m_input;
    cd.m_contactMgr = input.m_contactMgr;
    cd.m_result = &result;
    cd.m_wTa = bodyA->m_motion;
    cd.m_wTb = bodyB->m_motion;

    // bounding radii of both boxes in the same frame
    hkVector4_s010f_d4c0 radiusA, radiusB;
    radiusA.x = shapeA->m_radius + bodyA->m_motion->m_translation.x;
    radiusA.y = shapeA->m_radius + bodyA->m_motion->m_translation.y;
    radiusA.z = shapeA->m_radius + bodyA->m_motion->m_translation.z;
    radiusA.w = shapeA->m_radius + bodyA->m_motion->m_translation.w;
    radiusB.x = shapeB->m_radius + bodyB->m_motion->m_translation.x;
    radiusB.y = shapeB->m_radius + bodyB->m_motion->m_translation.y;
    radiusB.z = shapeB->m_radius + bodyB->m_motion->m_translation.z;
    radiusB.w = shapeB->m_radius + bodyB->m_motion->m_translation.w;
    (void)radiusB;

    cd.m_tolerance = 0.01f;

    hkBoxBoxManifold* manifold = (hkBoxBoxManifold*)agentData;
    cd.calcManifold(*manifold);

    entry->m_numContactPoints = manifold->m_numPoints;

    HK_TIMER_CMD(g_hkTimerEndTag1);
    return (char*)manifold + 0x50;
}

// @ 0x010fdec0
void __cdecl hkBoxBoxAgent3_register(hkCollisionDispatcher_s010f_d4c0* dispatcher)
{
    hkCollisionDispatcher_s010f_d4c0::Agent3Funcs funcs;
    funcs.m_createFunc          = (void* (*)())&hkBoxBoxAgent3_create;
    funcs.m_destroyFunc         = (void (*)())&hkBoxBoxAgent3_destroy;
    funcs.m_cleanupFunc         = 0;
    funcs.m_removePointFunc     = (void (*)())&hkBoxBoxAgent3_removePoint;
    funcs.m_commitPotentialFunc = (void (*)())&hkBoxBoxAgent3_commitPotential;
    funcs.m_createZombieFunc    = (void (*)())&hkBoxBox_createZombie;
    funcs.m_updateFilterFunc    = 0;
    funcs.m_invalidateTimFunc   = 0;
    funcs.m_warpTimeFunc        = 0;
    funcs.m_sepNormalFunc       = 0;
    funcs.m_processFunc         = (void* (*)())&hkBoxBoxAgent3_process;
    funcs.m_isPredictive        = hkBool_s010f_d4c0(false);
    funcs.m_ignoreSymmetricVersion = hkBool_s010f_d4c0(false);
    dispatcher->registerAgent3(funcs, 7, 7);
}

// @ 0x010fdf30
void* __cdecl hkPredGskCylinderAgent3_create(const hkAgent3Input& input, hkAgentEntry_s010f_d4c0* entry, void* agentData)
{
    ((unsigned int*)entry)[1] = 0;
    if (((const hkShape_s010f_d4c0*)input.m_bodyA->m_shape)->getType() == 5)
        ((unsigned int*)entry)[1] |= 1;
    if (((const hkShape_s010f_d4c0*)input.m_bodyB->m_shape)->getType() == 5)
        ((unsigned int*)entry)[1] |= 2;
    return hkGsk_cacheInit(input, entry, agentData);
}

// @ 0x010fdf80
void* __cdecl process(const hkAgent3ProcessInput_s010f_df80& input, hkAgentEntry_s010f_df80* entry, void* agentData, hkVector4_s010f_df80* separatingNormal, hkProcessCollisionOutput_s010f_df80& result)
{
    HK_TIMER_CMD_s010f_df80("TtPredGskf3");
    {
        void* end_ = TlsGetValue(g_hkMonitorStreamEndTls);
        if (TlsGetValue(g_hkMonitorStreamCurrentTls) < end_) {
            hkUint32_s010f_df80* c_ = (hkUint32_s010f_df80*)TlsGetValue(g_hkMonitorStreamCurrentTls);
            c_[0] = (hkUint32_s010f_df80)"Ltintern";
            c_[3] = (hkUint32_s010f_df80)"init";
            c_[1] = (hkUint32_s010f_df80)__rdtsc();
            TlsSetValue(g_hkMonitorStreamCurrentTls, c_ + 4);
        }
    }

    float dist = input.m_distAtT1;
    const hkCdBody_s010f_df80** bodyPtr[2];
    bodyPtr[1] = const_cast<const hkCdBody_s010f_df80**>(&input.m_bodyB);
    const hkUint32_s010f_df80 flags = entry->m_userData;
    int isCylinder[2];
    isCylinder[0] = flags & CYLINDER_A;
    isCylinder[1] = flags & CYLINDER_B;
    int capsuleMode[2];
    capsuleMode[1] = flags & CAPSULE_MODE_B;
    const hkCdBody_s010f_df80* savedBodies[2];
    savedBodies[0] = 0;
    savedBodies[1] = 0;
    capsuleMode[0] = flags & CAPSULE_MODE_A;
    hkUchar* const manifold = (hkUchar*)agentData + 0xc;
    bodyPtr[0] = const_cast<const hkCdBody_s010f_df80**>(&input.m_bodyA);

    hkVector4_s010f_df80 sepNormal;
    hkPredGskAgent3::sepNormal(reinterpret_cast<const hkAgent3Input&>(input), agentData, sepNormal);

    hkGskCache cacheCopy;   // shares its stack slot with the axis vector below in the binary
    hkCdBody_s010f_df80 tmpBodies[2];
    hkVector4_s010f_df80 sepOut;
    hkVector4_s010f_df80 verts[16];

    // ---- cylinder <-> capsule switching (hysteresis on |axis . separatingNormal|) ----
    for (int i = 0; i < 2; i++)
    {
        if (!isCylinder[i])
            continue;
        const hkCdBody_s010f_df80* body = *bodyPtr[i];
        const hkCylinderShape* cyl = static_cast<const hkCylinderShape*>(body->m_shape);
        hkVector4_s010f_df80 axis;
        axis.x = cyl->m_vertexB.x - cyl->m_vertexA.x;
        axis.y = cyl->m_vertexB.y - cyl->m_vertexA.y;
        axis.z = cyl->m_vertexB.z - cyl->m_vertexA.z;
        const float aw = cyl->m_vertexB.w - cyl->m_vertexA.w;
        const float len2 = axis.x * axis.x + axis.y * axis.y + axis.z * axis.z;
        const float invLen = (len2 == 0.0f) ? 0.0f : 1.0f / sqrtf(len2);
        axis.x *= invLen;
        axis.y *= invLen;
        axis.z *= invLen;
        axis.w = aw * invLen;
        axis.setRotatedDir(*reinterpret_cast<const hkRotation_s010f_df80*>(body->m_motion), axis);
        const float cosAngle = fabsf(sepNormal.x * axis.x + sepNormal.z * axis.z + sepNormal.y * axis.y);

        if (capsuleMode[i])
        {
            if (cosAngle > 0.17f)
            {
                capsuleMode[i] = 0;
                entry->m_userData &= ~(CAPSULE_MODE_A << i);
                hkGskManifold_cleanup(manifold, input.m_contactMgr);
                entry->m_numContactPoints = manifold[2];
                *(hkUint32_s010f_df80*)manifold = 0;
            }
        }
        else if (cosAngle < 0.085f)
        {
            capsuleMode[i] = 1;
            entry->m_userData |= (CAPSULE_MODE_A << i);
            hkGskManifold_cleanup(manifold, input.m_contactMgr);
            entry->m_numContactPoints = manifold[2];
            *(hkUint32_s010f_df80*)manifold = 0;
        }
    }

    const hkCollisionQualityInfo_s010f_df80* quality = input.m_input->m_collisionQualityInfo;

    if (quality->m_useContinuousPhysics)
    {
        const hkCdBody_s010f_df80* a = input.m_bodyA;
        while (a->m_parent) a = a->m_parent;
        const hkCdBody_s010f_df80* b = input.m_bodyB;
        while (b->m_parent) b = b->m_parent;
        float minRadius = static_cast<const hkCollidableRoot*>(b)->m_allowedPenetrationDepth;
        if (static_cast<const hkCollidableRoot*>(a)->m_allowedPenetrationDepth < minRadius)
            minRadius = static_cast<const hkCollidableRoot*>(a)->m_allowedPenetrationDepth;

        float t0 = minRadius * quality->m_minExtraSeparation + separatingNormal->w;
        float t0b = minRadius * quality->m_minSeparation;
        if (t0b < t0) t0 = t0b;
        if (dist < t0)
        {
            float t1 = minRadius * quality->m_toiExtraSeparation + separatingNormal->w;
            float t1b = minRadius * quality->m_toiSeparation;
            if (t1b < t1) t1 = t1b;
            HK_TIMER_CMD_s010f_df80("Sttoi");
            hkGsk_toi(&input, minRadius, t0, t1, agentData, separatingNormal, &result);
            goto process_gsk;
        }
    }

    if (quality->m_manifoldTimDistance < dist)
    {
        // far enough apart: only refresh the existing manifold points
        separatingNormal->w = dist;
        if (manifold[2])
        {
            HK_TIMER_CMD_s010f_df80("StgetPoints");
            replaceCylindersByCapsules(bodyPtr, capsuleMode, savedBodies, tmpBodies);
            getPoints(&input, manifold, verts, separatingNormal);
            hkGskManifold_update(manifold, verts, 0, &result, input.m_contactMgr);
            if (manifold[2] && result.m_potentialContacts)
            {
                *(hkUint32_s010f_df80*)result.m_potentialContacts->m_firstFreeRepresentativeContact =
                    (hkUint32_s010f_df80)((char*)result.m_firstFreeContactPoint - manifold[2] * 0x30);
                result.m_potentialContacts->m_firstFreeRepresentativeContact =
                    (hkProcessCdPoint_s010f_df80**)((char*)result.m_potentialContacts->m_firstFreeRepresentativeContact + 4);
            }
        }
        goto restore_bodies;
    }

process_gsk:
    HK_TIMER_CMD_s010f_df80("Stprocess");
    replaceCylindersByCapsules(bodyPtr, capsuleMode, savedBodies, tmpBodies);
    {
        // The GSK routines see a cache whose cylinder vertex ids are converted to capsule ids.
        hkGskCache* cache = (hkGskCache*)agentData;
        if (capsuleMode[0] || capsuleMode[1])
        {
            cache = &cacheCopy;
            cacheCopy = *(const hkGskCache*)agentData;
            if (capsuleMode[0])
            {
                cacheCopy.vertices()[0] = cylinderToCapsuleVertexId(cacheCopy.vertices()[0]);
                if (cacheCopy.m_dimA > 1)
                {
                    // cylinder edge/face -> the capsule's segment; B's vertex moves down one slot
                    cacheCopy.vertices()[0] = 16;
                    cacheCopy.vertices()[1] = 0;
                    if (cacheCopy.m_dimA == 3)
                    {
                        cacheCopy.m_dimA = 2;
                        cacheCopy.vertices()[2] = cacheCopy.vertices()[3];
                    }
                }
            }
            if (capsuleMode[1])
            {
                hkUint16_s010f_df80& v = cacheCopy.vertices()[cacheCopy.m_dimA];
                v = cylinderToCapsuleVertexId(v);
                if (cacheCopy.m_dimB > 1)
                {
                    cacheCopy.vertices()[cacheCopy.m_dimA] = 16;
                    cacheCopy.vertices()[cacheCopy.m_dimA + 1] = 0;
                    if (cacheCopy.m_dimB == 3)
                        cacheCopy.m_dimB = 2;
                }
            }
        }

        {
            hkGskInfo info;
            info.m_aTb        = &input.m_aTb;
            info.m_transformA = input.m_bodyA->m_motion;
            info.m_shapeA     = input.m_bodyA->m_shape;
            info.m_shapeB     = input.m_bodyB->m_shape;
            info.m_tolerance  = input.m_input->m_tolerance;
            int gsk = hkGsk_closestPoints(&info, cache, separatingNormal, &sepOut);
            if (gsk == 1)
            {
                if (manifold[2])
                    hkGskManifold_cleanup(manifold, input.m_contactMgr);
                goto restore_normal;
            }
        }

        const int numRemoved = (int)(hkGskManifold_numRemoved(manifold, cache) & 0xff);
        hkProcessCdPoint_s010f_df80* const start = result.m_firstFreeContactPoint;
        if (numRemoved < (int)manifold[2])
        {
            getPoints(&input, manifold, verts, separatingNormal);
            hkGskManifold_update(manifold, verts, numRemoved, &result, input.m_contactMgr);
        }

        hkProcessCdPoint_s010f_df80* cp = result.m_firstFreeContactPoint;
        {
            hkVector4_s010f_df80* d = (hkVector4_s010f_df80*)cp;
            d[0] = sepOut;
            d[1] = *separatingNormal;
        }

        if (numRemoved == 0)
        {
            const hkCollisionQualityInfo_s010f_df80* q = input.m_input->m_collisionQualityInfo;
            float thresh = ((int)cache->m_dimB + (int)cache->m_dimA == 4) ? q->m_create4dContact : q->m_createContact;
            if (separatingNormal->w < thresh)
            {
                int r = hkGsk_addPoint(manifold, input.m_bodyA, input.m_bodyB, input.m_input, cache, cp, start,
                                       input.m_contactMgr, 1);
                if (r == 4)
                {
                    short* cpId = (short*)((char*)cp + 0x20);
                    if (*cpId == -1)
                    {
                        bool remove = false;
                        if (result.m_potentialContacts)
                        {
                            if (input.m_contactMgr->reserveContactPoints(1) == 0)
                            {
                                ContactRef* ref = result.m_potentialContacts->m_firstFreePotentialContact;
                                result.m_potentialContacts->m_firstFreePotentialContact = ref + 1;
                                ref->m_entry = entry;
                                ref->m_contact = cp;
                                ref->m_agentData = agentData;
                                result.m_firstFreeContactPoint = (hkProcessCdPoint_s010f_df80*)((char*)result.m_firstFreeContactPoint + 0x30);
                            }
                            else
                                remove = true;
                        }
                        else
                        {
                            hkUint16_s010f_df80 id = input.m_contactMgr->addContactPoint(input.m_bodyA, input.m_bodyB, input.m_input, cp);
                            *cpId = (short)id;
                            if (id == 0xffff)
                                remove = true;
                            else
                            {
                                *(hkUint16_s010f_df80*)(manifold + 6) = id;
                                result.m_firstFreeContactPoint = (hkProcessCdPoint_s010f_df80*)((char*)result.m_firstFreeContactPoint + 0x30);
                            }
                        }
                        if (remove)
                        {
                            hkGskManifold_removePoint(manifold, 0);
                            cp = start;
                        }
                    }
                    else
                        result.m_firstFreeContactPoint = (hkProcessCdPoint_s010f_df80*)((char*)result.m_firstFreeContactPoint + 0x30);
                }
                else if (r == 5)
                    cp = start;
                else if (r == 6)
                {
                    result.m_firstFreeContactPoint = (hkProcessCdPoint_s010f_df80*)((char*)result.m_firstFreeContactPoint - 0x30);
                    cp = start;
                }
                else
                    cp = start + r;
            }
        }
        else
        {
            *(hkUint16_s010f_df80*)((char*)cp + 0x20) = *(hkUint16_s010f_df80*)(manifold + 6);
            result.m_firstFreeContactPoint = (hkProcessCdPoint_s010f_df80*)((char*)result.m_firstFreeContactPoint + 0x30);
        }

        if (result.m_potentialContacts && cp < result.m_firstFreeContactPoint)
        {
            *result.m_potentialContacts->m_firstFreeRepresentativeContact = cp;
            result.m_potentialContacts->m_firstFreeRepresentativeContact =
                (hkProcessCdPoint_s010f_df80**)((char*)result.m_potentialContacts->m_firstFreeRepresentativeContact + 4);
        }
    }

restore_normal:
    *separatingNormal = sepNormal;

restore_bodies:
    for (int i = 0; i < 2; i++)
    {
        if (savedBodies[i])
        {
            const hkCdBody_s010f_df80** slot = bodyPtr[i];
            const_cast<hkShape_s010f_df80*>((*slot)->m_shape)->removeReference();
            *slot = savedBodies[i];
        }
    }

    entry->m_numContactPoints = manifold[2];
    HK_TIMER_CMD_s010f_df80(g_hkTimerEndTag0);
    HK_TIMER_CMD_s010f_df80(g_hkTimerEndTag1);
    return (char*)agentData + ((((manifold[0] + manifold[2] * 4 + manifold[1]) * 2) + 0x1f) & 0xfffffff0);
}

// @ 0x010ff9e0
void* __cdecl process(const hkAgent3ProcessInput_s010f_f9e0& input, hkAgentEntry_s010f_f9e0* entry, void* agentData, hkVector4_s010f_f9e0* separatingNormal, hkProcessCollisionOutput_s010f_f9e0& result)
{
    HK_TIMER_CMD_s010f_f9e0("TtPredGskf3");
    {
        void* end_ = TlsGetValue(g_hkMonitorStreamEndTls);
        if (TlsGetValue(g_hkMonitorStreamCurrentTls) < end_) {
            hkUint32_s010f_f9e0* c_ = (hkUint32_s010f_f9e0*)TlsGetValue(g_hkMonitorStreamCurrentTls);
            c_[0] = (hkUint32_s010f_f9e0)"Ltintern";
            c_[3] = (hkUint32_s010f_f9e0)"init";
            c_[1] = (hkUint32_s010f_f9e0)__rdtsc();
            TlsSetValue(g_hkMonitorStreamCurrentTls, c_ + 4);
        }
    }

    hkUchar* const manifold = (hkUchar*)agentData + 0xc;
    const hkCollisionQualityInfo_s010f_f9e0* quality = input.m_input->m_collisionQualityInfo;
    float dist = input.m_distAtT1;
    hkVector4_s010f_f9e0 sepOut;
    hkVector4_s010f_f9e0 verts[16];

    if (quality->m_useContinuousPhysics)
    {
        const hkCdBody_s010f_f9e0* a = input.m_bodyA;
        while (a->m_parent) a = a->m_parent;
        const hkCdBody_s010f_f9e0* b = input.m_bodyB;
        while (b->m_parent) b = b->m_parent;
        float minRadius = b->m_allowedPenetrationDepth;
        if (a->m_allowedPenetrationDepth < minRadius) minRadius = a->m_allowedPenetrationDepth;

        float t0 = minRadius * quality->m_minExtraSeparation + separatingNormal->w;
        float t0b = minRadius * quality->m_minSeparation;
        if (t0b < t0) t0 = t0b;
        if (dist < t0)
        {
            float t1 = minRadius * quality->m_toiExtraSeparation + separatingNormal->w;
            float t1b = minRadius * quality->m_toiSeparation;
            if (t1b < t1) t1 = t1b;
            HK_TIMER_CMD_s010f_f9e0("Sttoi");
            hkGsk_toi(&input, minRadius, t0, t1, agentData, separatingNormal, &result);
            goto process_gsk;
        }
    }

    if (quality->m_manifoldTimDistance < dist)
    {
        separatingNormal->w = dist;
        if (manifold[2])
        {
            HK_TIMER_CMD_s010f_f9e0("StgetPoints");
            getPoints_s010f_f9e0(&input, manifold, (hkVector4_s010f_f9e0*)verts, separatingNormal);
            hkGskManifold_update(manifold, verts, 0, &result, input.m_contactMgr);
            if (manifold[2] && result.m_potentialContacts)
            {
                *(hkUint32_s010f_f9e0*)result.m_potentialContacts->m_firstFreeRepresentativeContact =
                    (hkUint32_s010f_f9e0)((char*)result.m_firstFreeContactPoint - manifold[2] * 0x30);
                result.m_potentialContacts->m_firstFreeRepresentativeContact =
                    (hkProcessCdPoint_s010f_f9e0**)((char*)result.m_potentialContacts->m_firstFreeRepresentativeContact + 4);
            }
        }
        goto finish;
    }

process_gsk:
    HK_TIMER_CMD_s010f_f9e0("Stprocess");
    {
        hkGskInfo_s010f_f9e0 info;
        info.m_aTb        = &input.m_aTb;
        info.m_transformA = input.m_bodyA->m_motion;
        info.m_shapeA     = input.m_bodyA->m_shape;
        info.m_shapeB     = input.m_bodyB->m_shape;
        info.m_tolerance  = input.m_input->m_tolerance;
        int gsk = hkGsk_closestPoints(&info, agentData, separatingNormal, &sepOut);
        if (gsk == 1)
        {
            if (manifold[2])
                hkGskManifold_cleanup(manifold, input.m_contactMgr);
            goto finish;
        }
    }

    {
        const int numRemoved = (int)(hkGskManifold_numRemoved(manifold, agentData) & 0xff);
        hkProcessCdPoint_s010f_f9e0* const start = result.m_firstFreeContactPoint;
        if (numRemoved < (int)manifold[2])
        {
            getPoints_s010f_f9e0(&input, manifold, (hkVector4_s010f_f9e0*)verts, separatingNormal);
            hkGskManifold_update(manifold, verts, numRemoved, &result, input.m_contactMgr);
        }

        hkProcessCdPoint_s010f_f9e0* cp = result.m_firstFreeContactPoint;
        {
            hkVector4_s010f_f9e0* d = (hkVector4_s010f_f9e0*)cp;
            d[0] = sepOut;
            d[1] = *separatingNormal;
        }

        if (numRemoved == 0)
        {
            const hkCollisionQualityInfo_s010f_f9e0* q = input.m_input->m_collisionQualityInfo;
            float thresh = ((int)(signed char)((hkUchar*)agentData)[9] + (int)(signed char)((hkUchar*)agentData)[8] == 4)
                           ? q->m_create4dContact : q->m_createContact;
            if (separatingNormal->w < thresh)
            {
                int r = hkGsk_addPoint(manifold, input.m_bodyA, input.m_bodyB, input.m_input, agentData, cp, start,
                                       input.m_contactMgr, 1);
                if (r == 4)
                {
                    short* cpId = (short*)((char*)cp + 0x20);
                    if (*cpId == -1)
                    {
                        bool remove = false;
                        if (result.m_potentialContacts && entry)
                        {
                            if (input.m_contactMgr->reserveContactPoints(1) == 0)
                            {
                                ContactRef_s010f_f9e0* ref = result.m_potentialContacts->m_firstFreePotentialContact;
                                result.m_potentialContacts->m_firstFreePotentialContact = ref + 1;
                                ref->m_entry = entry;
                                ref->m_contact = cp;
                                ref->m_agentData = agentData;
                                result.m_firstFreeContactPoint = (hkProcessCdPoint_s010f_f9e0*)((char*)result.m_firstFreeContactPoint + 0x30);
                            }
                            else
                                remove = true;
                        }
                        else
                        {
                            hkUint16_s010f_f9e0 id = input.m_contactMgr->addContactPoint(input.m_bodyA, input.m_bodyB, input.m_input, cp);
                            *cpId = (short)id;
                            if (id == 0xffff)
                                remove = true;
                            else
                            {
                                *(hkUint16_s010f_f9e0*)(manifold + 6) = id;
                                result.m_firstFreeContactPoint = (hkProcessCdPoint_s010f_f9e0*)((char*)result.m_firstFreeContactPoint + 0x30);
                            }
                        }
                        if (remove)
                        {
                            hkGskManifold_removePoint(manifold, 0);
                            cp = start;
                        }
                    }
                    else
                        result.m_firstFreeContactPoint = (hkProcessCdPoint_s010f_f9e0*)((char*)result.m_firstFreeContactPoint + 0x30);
                }
                else if (r == 5)
                    cp = start;
                else if (r == 6)
                {
                    result.m_firstFreeContactPoint = (hkProcessCdPoint_s010f_f9e0*)((char*)result.m_firstFreeContactPoint - 0x30);
                    cp = start;
                }
                else
                    cp = start + r;
            }
        }
        else
        {
            *(hkUint16_s010f_f9e0*)((char*)cp + 0x20) = *(hkUint16_s010f_f9e0*)(manifold + 6);
            result.m_firstFreeContactPoint = (hkProcessCdPoint_s010f_f9e0*)((char*)result.m_firstFreeContactPoint + 0x30);
        }

        if (result.m_potentialContacts && cp < result.m_firstFreeContactPoint)
        {
            *result.m_potentialContacts->m_firstFreeRepresentativeContact = cp;
            result.m_potentialContacts->m_firstFreeRepresentativeContact =
                (hkProcessCdPoint_s010f_f9e0**)((char*)result.m_potentialContacts->m_firstFreeRepresentativeContact + 4);
        }
    }

finish:
    entry->m_numContactPoints = manifold[2];
    HK_TIMER_CMD_s010f_f9e0(g_hkTimerEndTag0);
    HK_TIMER_CMD_s010f_f9e0(g_hkTimerEndTag1);
    return (char*)agentData + ((((manifold[0] + manifold[2] * 4 + manifold[1]) * 2) + 0x1f) & 0xfffffff0);
}
