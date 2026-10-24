// Slice s010f1350: Havok hkContinuousSimulation continuous-collision routines.
// Flags: /O2 /MD /Gy /TP /arch:SSE
#include "types.h"

typedef unsigned int uint;

void* FUN_01099cb0(int a, int b, int c);      // 0x01099cb0
void* FUN_010f0bb0(void* self, int a, int b); // 0x010f0bb0
void* FUN_0111ccf0();                         // 0x0111ccf0 hkDefaultToiResourceMgr ctor
void* FUN_0107db10(void* mem, int a, int b, int c);  // 0x0107db10 deallocateChunk
void* TlsGetValue(void* idx);
void* hkMemoryAlloc(int size, int align);     // hkMemory::s_instance vtable+0x10
extern void* g_hkMemory;                      // 0x016e4178
extern void* g_hkThreadMemoryTls;             // 0x016e4174
extern void* g_13ef094;                       // vtable

// Continuous-solver entry points used by the hkLs_* helpers.
struct AgentOutput;
struct AgentEntry;
struct ProcessCollisionInput;
void FUN_0120a260(float dt, void* motionState);           // 0x0120a260 backStepMotionState
struct hkRotation;
void FUN_010fc180(AgentEntry* agent, ProcessCollisionInput* input, AgentOutput* output); // 0x010fc180 hkAgentNnMachine_processAgent
void FUN_010f0b00(int self, AgentEntry* agent, AgentOutput* output);   // 0x010f0b00 (thiscall)
extern int g_vtableSimulation1;               // 0x014a59d0
extern char vtable_Simulator_cCreatureAbility; // 0x013ef094 (the dtor's final vtable store)

// @ 0x010f19b0  hkContinuousSimulation ctor helper
void* FUN_010f19b0(void* self, int owner) {
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
    void collideIsland(int* island, void* input);
    void processAgentCollide(AgentEntry* agent, ProcessCollisionInput* input, AgentOutput* output);
    void* scalarDelete(unsigned int flags);
    void destroy();             // 0x010f1a10
    void f0bb0(int a, int b);   // 0x010f0bb0
};

// @ 0x010f1a10  hkContinuousSimulation dtor
void ContinuousSim::destroy() {
    mVtable = (void*)0x014a59d0;
    if (mResourceMgr) {
        void** vt = *(void***)mResourceMgr;
        ((void(__thiscall*)(void*,int))vt[0])(mResourceMgr, 1);
    }
    if (mCapacityAndFlags >= 0) {
        void* tm = TlsGetValue(g_hkThreadMemoryTls);
        FUN_0107db10(tm, (int)mArrayData,
                     (mCapacityAndFlags & 0x3fffffff) << 6, 0x14);
    }
    mVtable = &vtable_Simulator_cCreatureAbility;
}

// @ 0x010f1a60  hkContinuousSimulation::resetCollisionInformationForEntities
void ContinuousSim::resetEntities(int a, int b, int c) {
    FUN_01099cb0(a, b, c);
    f0bb0(a, b);
}

// @ 0x010f1350
void FUN_010f1350(void* input, int prio, float dt, void* entities, void* flags, void* a, void* b) {
    (void)input; (void)prio; (void)dt; (void)entities; (void)flags; (void)a; (void)b;
}

// @ 0x010f1690  hkLs_areConstraintsSatisfied
// Collects the constraints whose schema still needs the continuous solver to run.
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

// The constraint instance a SimObjectRef points at. It owns the schema sub-object
// at +0x0c whose vtable slot 3 reports the constraint kind.
struct ConstraintObject
{
    int mPad0[3];           // +0x00
    ConstraintSub* mSub;    // +0x0c
};

// Solver object: the velocity test is a free function but takes the solver's +0x08 field.
struct SolverState
{
    int mPad0[2];   // +0x00
    int mField8;    // +0x08
};

// Context threaded through the continuous-solver helpers.
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
void FUN_0107f530(void* array, int elemSize);

void FUN_010f1690(char* out, ConstraintContext* ctx, ConstraintArray* constraints, int param4, ResultArray* results) {
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

// The flag array is reached through a one-word holder, and only touched inside the loop.
struct FlagList
{
    char* mData;   // +0
};

struct hkRotation
{
    float m_el[12];               // +0x00  three columns of four floats
    void set(const void* quat);   // 0x010824a0 hkRotation::set
};

// Entity motion state: the rotation basis at +0x10, the backstepped and current
// position blocks at +0x50/+0x70 (copied from +0x60/+0x80), and the quaternion
// and axis the position increment is projected on at +0x80/+0x90.
struct MotionState
{
    char mPad00[0x10];              // +0x00
    hkRotation mRotation;           // +0x10
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

// Time step the backstep helper reads its end time from.
struct TimeStep
{
    int mPad0[6];      // +0x00
    float mEndTime;    // +0x18
};

// Continuous-solver island: the body-pointer array and its count, plus the time step.
struct Entity;

struct Island
{
    char mPad00[0x1c];      // +0x00
    TimeStep* mTimeStep;    // +0x1c
    char mPad20[0x1c];      // +0x20
    Entity** mBodies;       // +0x3c
    int mBodyCount;         // +0x40
};

// A solver body: its motion state lives at +0x58.
struct Entity
{
    char mPad00[0x58];      // +0x00
    MotionState* mMotion;   // +0x58
};

// @ 0x010f17f0
void FUN_010f17f0(int dtBits, Island* island, FlagList* flagList, ResultArray* out) {
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

// @ 0x010f18d0  hkContinuousSimulation::integrateMotionStates
void FUN_010f18d0(Island* island, FlagList* flagList) {
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


// @ 0x010f1a90
void ContinuousSim::collideIsland(int* island, void* input) {
    (void)island; (void)input;
}

// 0x010f1cc0 arguments: the agent record (arg1), the process-collision input (arg2) and
// the output accumulator (arg3). The agent's job table entry is selected from its
// state byte and the input's table base.
struct AgentEntry
{
    int mPad00[2];      // +0x00
    int8_t mState;      // +0x08
    char mPad09[3];     // +0x09
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

// One 0x3c-byte entry of the static agent job table.
struct JobTableEntry
{
    char mPad00[0x10];   // +0x00
    uint8_t mKind;       // +0x10
};

// hkMemory::s_instance: the per-thread budget the watchdog compares against.
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

// @ 0x010f1cc0
void ContinuousSim::processAgentCollide(AgentEntry* agent, ProcessCollisionInput* input, AgentOutput* output) {
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

// @ 0x010f1d80  hkContinuousSimulation scalar deleting dtor
void* ContinuousSim::scalarDelete(unsigned int flags) {
    destroy();
    if (flags & 1) {
        // operator delete(this)
    }
    return this;
}
