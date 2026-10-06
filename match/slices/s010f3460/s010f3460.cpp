// Decompiled source for bfs3 slice 44: hkContinuousSimulation continuous
// collision entry points.  These are large dispatchers; implemented as
// compilable behaviorally-incomplete skeletons (see partial.txt).
#include "types.h"

#define VFN(p, slot) (((void**)*(void**)p)[(slot)/4])

struct hkEntity;
struct hkWorld;
struct hkStepInfo {};
struct hkToiEvent {};
struct hkAgentNnEntry;
struct hkProcessCollisionInput;
struct hkProcessCollisionOutput;

void FUN_010829d0(void* cmd);
void FUN_010f1df0(hkEntity** entities, int n, hkWorld* w, int flag);
void FUN_01099be0(hkEntity** entities, int n, void* entry, void* fn);
void hkWorld_executePendingOperations(hkWorld* w);      // 0x01082bf0
void hkSweptTransformUtil_backStepMotionState(float dt, void* motionState); // 0x0120a260
void FUN_010f1cc0(void*, const void*, void*);           // processAgentCollideContinuous
void* TlsGetValue(unsigned long);
void TlsSetValue(unsigned long, void*);
extern unsigned long g_tls1;
extern unsigned long g_tls2;

// hkWorld fields touched by this slice.
struct hkWorld {
    char pad[0x0c];
    float mStepStart;      // +0x0c
    char pad10[0x08];
    float mStepEnd;        // +0x18
    char pad1c[0x5c];
    void* mContinuousSim;  // +0x78
    char pad7c[0x0c];
    int mField88;          // +0x88
    int mField8c;          // +0x8c
    char pad90[4];
    bool mField94;         // +0x94
};

// The step data at hkWorld::mContinuousSim (+0x10 .. +0x1c).
struct hkContinuousStep {
    float mStart;          // +0x10
    float mEnd;            // +0x14
    float mDelta;          // +0x18
    float mInvDelta;       // +0x1c
};

class hkContinuousSimulation {
public:
    void* mpVtbl;          // +0x00

    void reintegrateAndRecollideEntities(hkEntity** entities, int n, hkWorld* w); // 0x010f3460
    void collide(hkWorld* w, const hkStepInfo& step);                             // 0x010f3600
    void simulateToi(hkWorld* w, hkToiEvent& event, float dt);                    // 0x010f3a40
};

// @ 0x010f3460
void hkContinuousSimulation::reintegrateAndRecollideEntities(hkEntity** entities, int n, hkWorld* w)
{
    if (w->mField8c == 0) {
        hkContinuousStep* cs = (hkContinuousStep*)w->mContinuousSim;
        float start = w->mStepEnd;
        float end = w->mStepStart;
        w->mField8c = 1;
        float s0 = cs->mStart;
        float s1 = cs->mEnd;
        float delta = end - start;
        float invDelta = (delta == 0.0f) ? 0.0f : 1.0f / delta;
        cs->mStart = start;
        cs->mEnd = end;
        cs->mDelta = delta;
        cs->mInvDelta = invDelta;
        for (int i = 0; i < n; ++i) {
            hkEntity* e = entities[i];
            hkSweptTransformUtil_backStepMotionState(start, (char*)e + 0x58 + 0x10);
            ((void(__thiscall*)(void*, void*))VFN((char*)e + 0x58, 0xc))((char*)e + 0x58, 0);
        }
        FUN_010f1df0(entities, n, w, 0);
        ((void(__thiscall*)(void*, hkEntity**, int, hkWorld*))VFN(this, 0x30))(this, entities, n, w);
        FUN_01099be0(entities, n, w->mContinuousSim, (void*)0x010f1cc0);
        if (--w->mField8c == 0 && w->mField88 != 0 && !w->mField94)
            hkWorld_executePendingOperations(w);
        (void)s0; (void)s1;
    } else {
        char cmd[0x14];
        *(char*)(cmd + 0) = 0x16;
        *(void**)(cmd + 4) = entities;
        *(int*)(cmd + 0xc) = n;
        FUN_010829d0(cmd);
    }
}

// @ 0x010f3600
void hkContinuousSimulation::collide(hkWorld* w, const hkStepInfo& step)
{
    (void)w; (void)step;
    TlsGetValue(g_tls1);
    TlsGetValue(g_tls2);
}

// @ 0x010f3a40
void hkContinuousSimulation::simulateToi(hkWorld* w, hkToiEvent& event, float dt)
{
    (void)w; (void)event; (void)dt;
}
