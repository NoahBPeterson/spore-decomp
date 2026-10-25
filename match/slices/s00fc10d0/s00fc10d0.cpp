// slice s00fc10d0 -- cTerrainSystem / terrain-step helpers (0x00fc10d0..0x00fc2040).
// Real PDB names: SP::cTerrainSystem::Init, SP::GetTerraformPlanetType,
// SP::cSetCloudTypeStep::Step.  Module flags /O2 /MD /Gy /TP.
#include "types.h"

extern float kTerraformRadiusT1, kTerraformRadiusT2, _kTerraformRadiusT3;
extern float kLavaThreshold;

void* __cdecl operator_new(int, const char*, int, int, int, int);   // 0x00f473a0
void  __cdecl operator_del(void*);                                  // 0x00f47380
void* __cdecl SP_TerrainEditor();                                   // 0x00f48a70
void* __cdecl SP_ModelManager();                                    // 0x0067dd80
char  __cdecl FUN_0075e620_dummy();
void  __cdecl FUN_00f67ff0_dummy();
void  __cdecl FUN_00f9ee90(int, int, int);
void  __cdecl FUN_00f699a0();
void  __cdecl FUN_00f9a610();
void  __cdecl FUN_00f9ef70(int);
void  __cdecl FUN_00f9eda0();
void  __cdecl FUN_00f96d40();
void* __cdecl FUN_0067dd50();                // 0x0067dd50 command/scheduler accessor
void  __cdecl FUN_00517240();
void* __cdecl FUN_006f43e0(int, int, int);   // 0x006f43e0 copy_intrusive(first, last, dest)
struct VecBase { void DestroyRange(int* first, int* last); };       // 0x0070f520
void  __fastcall FUN_0075e6d0(int, int, void*);
void* __cdecl memcpy(void*, const void*, unsigned int);   // 0x011e0744
void  __cdecl FUN_00f7be60();
void  __cdecl FUN_00f580f0();
void  __cdecl FUN_00f61a70();
void  __cdecl FUN_00f52b70(int, const char*);
void  __cdecl FUN_00f58230(int, void*);
void  __cdecl FUN_00aa7fa0(int, void*);
void  __cdecl SWARM_TerrainBrushAddCommands();     // 0x00f4ac10
void  __cdecl SWARM_TerrainScriptAddCommands();    // 0x00f94d00
void  __cdecl SWARM_TerrainDistributeCreate();     // 0x00f65320
void  __cdecl FUN_00f4b0c0(); void __cdecl FUN_00f49020(); void __cdecl FUN_00f95400();
void  __cdecl FUN_00f94cb0(); void __cdecl FUN_00f94dd0(); void __cdecl FUN_00f63d50();
void  __cdecl FUN_00f63170(); void __cdecl FUN_00fc5480(); void __cdecl FUN_00f4b690();

namespace SP {
class cDirectPropertyList {
public:
    virtual void v0();
    virtual void v1();
};
extern cDirectPropertyList* sAppProperties;
}

// Object types reached through the cTerrainSystem constructor / destructor.
struct VtblTwo { virtual void v0(); virtual void v1(); };
struct VtblFour { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); };
struct RefCounted { virtual void Release(int flag); int mRefCount; };
struct CountedHolder { int mPad0; RefCounted mRef; };

struct cTerrainSystem {
    int mVtable0;                      // +0x00
    int mVtable1;                      // +0x04
    int mField08;                      // +0x08
    VtblFour* mObj0c;                  // +0x0c
    CountedHolder* mObj10;             // +0x10 (RefCounted subobject at +0x04)
    VtblTwo* mObj14;                   // +0x14
    float mField18;                    // +0x18
    SP::cDirectPropertyList* mProps1c; // +0x1c
    int mTag20;                        // +0x20
    int mZero24;                       // +0x24
};

// Fixed-vector holder destroyed at 0x00fc1780.
struct FixedVectorHolder {
    int mVtable0;          // +0x00
    int mPad04[5];         // +0x04..+0x17
    int mVecBegin;         // +0x18
    int mVecEnd;           // +0x1c
    int mPad20[3];         // +0x20..+0x2b
    int mVec2Begin;        // +0x2c
};

// ---------------------------------------------------------------------------
// Types shared by the terrain step routines reconstructed below.
// ---------------------------------------------------------------------------

// 8-byte element of the per-state cycle vector: one 64-bit rdtsc counter.
typedef unsigned __int64 SStepCycles;

// Vector of 4-byte pointers; its tail is destroyed through the dispatch helper.
struct CPointerVector {
    void** mpBegin;                                                 // +0x00
    void** mpEnd;                                                   // +0x04
    void** mpCap;                                                   // +0x08

    void Init() {
        mpBegin = 0;
        mpEnd = 0;
        mpCap = 0;
    }

    // clear(): move (nothing) to the front, destroy the old tail, reset the end.
    void Clear() {
        void** first = (void**)FUN_006f43e0((int)mpEnd, (int)mpEnd, (int)mpBegin);
        ((VecBase*)this)->DestroyRange((int*)first, (int*)mpEnd);
        mpEnd = mpBegin;
    }
};

// Fixed-capacity vector of 8-byte counters: 12 entries at 0x00fc16b0, 16 at the
// two other constructors.
struct CStepCycleVector {
    SStepCycles* mpBegin;                                           // +0x00
    SStepCycles* mpEnd;                                             // +0x04
    SStepCycles* mpCap;                                             // +0x08

    void Init() {
        mpBegin = 0;
        mpEnd = 0;
        mpCap = 0;
    }

    void insert_n(SStepCycles* pos, unsigned int count, const SStepCycles* value);  // 0x00a6aaa0

    // eastl::vector::erase: shift the tail down over [first, last).
    void erase(SStepCycles* first, SStepCycles* last) {
        memcpy(first, last, (char*)mpEnd - (char*)last);
        mpEnd -= last - first;
    }

    // eastl::vector::resize: grow by copying `value`, shrink by erasing the tail.
    void Resize(unsigned int count, const SStepCycles& value) {
        int have = (int)(mpEnd - mpBegin);
        if (have < count)
            insert_n(mpEnd, count - have, &value);
        else
            erase(mpBegin + count, mpEnd);
    }
};

// cSetCloudTypeStep: the per-sphere build state machine driven by FUN_00fc10d0.
struct CCloudTypeStep {
    void* mpVtable;                                                 // +0x00
    unsigned char mDone;                                            // +0x04
    unsigned char mPad05[3];                                        // +0x05
    int mState;                                                     // +0x08
    int mField0c;                                                   // +0x0c
    float mField10;                                                 // +0x10
    int mField14;                                                   // +0x14
    CPointerVector mVec18;                                          // +0x18
    int mField24;                                                   // +0x24 (never touched here)
    int mField28;                                                   // +0x28 (never touched here)
    CStepCycleVector mCycles;                                       // +0x2c
    int mField38;                                                   // +0x38 (never touched here)
    int mField3c;                                                   // +0x3c (never touched here)
    int mField40;                                                   // +0x40
};

// Virtual interface of a terrain sphere; only slot +0xd8 is reached here.
struct CTerrainSphereVtbl {
    void* mpSlots[0x36];                                            // +0x000..+0x0d4
    char (__thiscall* mIsIdle)(void* self);                         // +0x0d8
};

// Terrain sphere object passed to the step routine.
struct CTerrainSphere {
    CTerrainSphereVtbl* mpVtable;                                   // +0x00
    void CollectTextures(int* value0, float* value1, float param);  // 0x00f9ee90
    void RebuildSurface();                                          // 0x00f9a610
    void SetParameter(float param);                                 // 0x00f9ef70
    void PrepareClouds();                                           // 0x00f9eda0
    void SetCloudType();                                            // 0x00f9a590
    void FinishStep();                                              // 0x00f96d40
};

// Terrain editor object as used by the step routine (cILayer subobject at +0x04).
struct CTerrainEditorSteps {
    void* mpVtable;                                                 // +0x00
    void* mpILayer;                                                 // +0x04
    bool UpdateCPUFromGPU(float param);                             // 0x00f6bd70
    bool QuadQueueEmpty();                                          // 0x00f699a0
};

// Scheduler object returned by FUN_0067dd50; only slot +0x78 is reached here.
struct CCommandSinkVtbl {
    void* mpSlots[0x1e];                                            // +0x000..+0x074
    void (__thiscall* mSubmit)(void* self, void* layer, int zero, void* request);  // +0x078
};
struct CCommandSink { CCommandSinkVtbl* mpVtable; };

// 0x2c-byte request descriptor filled in by FUN_00517240 (returns itself).
struct CCommandRequest {
    int mField00;      // +0x00
    int mField04;      // +0x04
    char mField08;     // +0x08
    char mPad09[3];    // +0x09
    int mField0c;      // +0x0c
    int mField10;      // +0x10
    int mField14;      // +0x14
    int mField18;      // +0x18
    int mField1c;      // +0x1c
    int mField20;      // +0x20
    int mField24;      // +0x24
    int mField28;      // +0x28
    void* Init();                                                   // 0x00517240
};

// Command-set descriptor copied onto the three static tables by FUN_00fc19a0.
struct CSwarmCommandSet {
    const char* mpName;     // +0x00 (null in all three tables)
    void* mpHandler0;       // +0x04
    void* mpHandler1;       // +0x08
    void* mpHandler2;       // +0x0c
    void* mpHandler3;       // +0x10
    int mField14;           // +0x14
    int mField18;           // +0x18
    int mField1c;           // +0x1c
};

// Pool object returned by FUN_00f48a90 (owns the quad buffer at +0x0c).
struct CQuadPool {
    void* mpOwner;          // +0x00
    int mPad04[2];          // +0x04..+0x0b
    void* mpBuffer;         // +0x0c
};

// Wrapper object allocated by cTerrainSystem::Init (0x00fc1c70), 0xc bytes.
struct CTerrainSphereWrapper {
    void* mpVtable0;        // +0x00
    void* mpVtable1;        // +0x04
    void* mField08;         // +0x08
};

struct CEffectsManagerVtbl {
    void* mpSlots[0x13];                                            // +0x00..+0x48
    void* (__thiscall* mGetEffects)(void* self, int id, int zero);  // +0x4c
    void (__thiscall* mShutdown)(void* self, int id);               // +0x50
};
struct CEffectsManager { CEffectsManagerVtbl* mpVtable; };

struct CEffectsObjectVtbl {
    void* mpSlots[3];                                               // +0x00..+0x08
    void (__thiscall* mSetMode)(void* self, int mode);              // +0x0c
};
struct CEffectsObject { CEffectsObjectVtbl* mpVtable; };

struct CModelManagerVtbl {
    void* mpSlots[5];                                               // +0x00..+0x10
    void* (__thiscall* mGetModel)(void* self, int id, int a, int b);  // +0x14
    void (__thiscall* mReleaseModel)(void* self, int id);           // +0x18
};
struct CModelManager { CModelManagerVtbl* mpVtable; };

struct CModelVtbl {
    void* mpSlots[0x4d];                                            // +0x000..+0x130
    void (__thiscall* mSetDetail)(void* self, int value);           // +0x134
    void* mPad138[4];                                               // +0x138..+0x144
    void (__thiscall* mAttachEffects)(void* self, void* effects);   // +0x148
    void* mPad14c[2];                                               // +0x14c..+0x150
    void (__thiscall* mSetOffset)(void* self, float value);         // +0x154
    void (__thiscall* mSetParam)(void* self, void* param, float value);  // +0x158
};
struct CModel { CModelVtbl* mpVtable; };

struct CAppVtbl {
    void* mpSlots[0x14];                                            // +0x00..+0x4c
    void* (__thiscall* mGetSubObject)(void* self);                  // +0x50
};
struct CApp { CAppVtbl* mpVtable; };

struct CAppSubVtbl {
    void* mpSlots[8];                                               // +0x00..+0x1c
    void (__thiscall* mRegister)(void* self, int id, void* callback);  // +0x20
};
struct CAppSub { CAppSubVtbl* mpVtable; };

// Virtual release with one integer argument (slot +0 of a two-slot interface).
struct VtblOneInt { virtual void v0(int flag); };

// ---------------------------------------------------------------------------
// Externals reached by the reconstructions below.
// ---------------------------------------------------------------------------
void* __cdecl FUN_0067dd80();                                    // SP::ModelManager
void* __cdecl EffectsManagerPtr();                               // 0x0067ddd0
void* __cdecl SP_App();                                          // 0x0067dd10
void  __cdecl FUN_00f63650(int, int*);                           // 0x00f63650
void  __cdecl FUN_00fc4eb0();                                    // mid-function label, passed as a handler
void  __cdecl FUN_00f52690();                                    // 0x00f52690
void  __cdecl FUN_00fc23b0();                                    // SP::UpdateTerrainTerraformTuning
void  __cdecl FUN_00fba330();                                    // SP::cTerrainStateMgr::StaticInit
void  __cdecl FUN_00c2e4e0();                                    // ReadText_00c2e4e0
void  __cdecl FUN_00f7be60();
void  __cdecl FUN_00f580f0();
void  __cdecl FUN_00f61a70();
void  __cdecl FUN_00f52b70(int, const char*);
void  __cdecl FUN_00f58230(int, void*);
void  __cdecl FUN_00aa7fa0(int, void*);
void* __cdecl FUN_00f48a60();                                    // 0x00f48a60 scope accessor
void* __cdecl FUN_00f48a90();                                    // 0x00f48a90 scope accessor
void* __cdecl FUN_00f939b0();                                    // 0x00f939b0
void* __cdecl FUN_00f95da0();                                    // 0x00f95da0
void* __cdecl FUN_00f6a930();                                    // 0x00f6a930
void  __cdecl FUN_00f48ab0(void*);                               // 0x00f48ab0
void  __cdecl FUN_00f48ac0(void*);                               // 0x00f48ac0
void  __cdecl FUN_00f48ad0(void*);                               // 0x00f48ad0
void  __cdecl FUN_00f48ae0(void*);                               // 0x00f48ae0
void  __cdecl FUN_00fa0360();                                    // 0x00fa0360
void  __cdecl FUN_00fc0fe0();                                    // SP::ResetTerrainGlobals
void  __cdecl FUN_0067cc50(void*);                               // 0x0067cc50
bool  __fastcall FUN_0075e620(float* value);                     // 0x0075e620 RenderStageReady, arg in ecx
void  __fastcall FUN_00fb7a60(void* self);                       // 0x00fb7a60 QuadReleaseVec
void  __fastcall FUN_00f6b840(void* self);                       // 0x00f6b840 QuadMgr::Destroy
void  __fastcall FUN_00f93c00(void* self);                       // 0x00f93c00
void  __fastcall FUN_00f940a0(void* self);                       // 0x00f940a0
void  __fastcall FUN_00f95d90(void* self);                       // 0x00f95d90
void  __fastcall FUN_00f96310(void* self);                       // 0x00f96310
void  __fastcall FUN_00f69a30(void* self);                       // 0x00f69a30 editor Init

extern "C" unsigned __int64 __rdtsc(void);
#pragma intrinsic(__rdtsc)

// Parameter block handed to the model's +0x158 slot.
#define TERRAIN_MODEL_PARAM_BLOCK ((void*)0x016d6e70)
// Handler label registered for the "writeForce" cheat command.
#define TERRAIN_WRITE_FORCE_HANDLER ((void*)0x00fc4eb0)

// Values copied into the three command-set descriptors (unnamed globals).
#define sTerrainBrushField18      (*(int*)0x015b0994)
#define sTerrainBrushField1c      (*(int*)0x015b0998)
#define sTerrainScriptField18     (*(int*)0x015b0fe4)
#define sTerrainScriptField1c     (*(int*)0x015b0fe8)
#define sTerrainDistributeField18 (*(int*)0x015b0c6c)
#define sTerrainDistributeField1c (*(int*)0x015b0c70)

// The three static command tables written by FUN_00fc19a0.
#define sTerrainBrushCommands      (*(CSwarmCommandSet*)0x016762b0)
#define sTerrainScriptCommands     (*(CSwarmCommandSet*)0x016762d0)
#define sTerrainDistributeCommands (*(CSwarmCommandSet*)0x016763f0)


// ===========================================================================
// 0x00fc10d0 -- cSetCloudTypeStep::Step (12-state terrain-sphere builder)
// ===========================================================================
// @ 0x00fc10d0
char __fastcall FUN_00fc10d0(CCloudTypeStep* step, int dummy, CTerrainSphere* sphere, float param) {
    (void)dummy;
    if (step->mDone)
        return 1;

    CTerrainEditorSteps* editor = (CTerrainEditorSteps*)SP_TerrainEditor();
    unsigned __int64 start = __rdtsc();
    bool advance = true;

    switch (step->mState) {
    case 0:
        if (!sphere->mpVtable->mIsIdle(sphere))
            advance = false;
        break;
    case 1:
        sphere->CollectTextures(&step->mField0c, &step->mField10, param);
        break;
    case 2: {
        void* layer = editor ? editor->mpILayer : 0;
        CCommandSink* sink = (CCommandSink*)FUN_0067dd50();
        CCommandRequest request;
        void* requestPtr = request.Init();
        sink->mpVtable->mSubmit(sink, layer, 0, requestPtr);
        break;
    }
    case 3:
    case 6:
        if (!editor->QuadQueueEmpty())
            advance = false;
        break;
    case 4:
        editor->UpdateCPUFromGPU(param);
        sphere->RebuildSurface();
        break;
    case 5:
        sphere->SetParameter(param);
        break;
    case 7: {
        void* layer = editor ? editor->mpILayer : 0;
        CCommandSink* sink = (CCommandSink*)FUN_0067dd50();
        CCommandRequest request;
        void* requestPtr = request.Init();
        sink->mpVtable->mSubmit(sink, layer, 0, requestPtr);
        break;
    }
    case 8:
        editor->UpdateCPUFromGPU(param);
        sphere->RebuildSurface();
        break;
    case 9:
        sphere->PrepareClouds();
        break;
    case 10:
        sphere->SetCloudType();
        break;
    case 11:
        sphere->FinishStep();
        step->mDone = 1;
        break;
    }

    step->mCycles.mpBegin[step->mState] += __rdtsc() - start;
    if (step->mDone)
        ++step->mField40;
    if (advance)
        ++step->mState;
    return step->mDone;
}

// ===========================================================================
// 0x00fc16b0 / 0x00fc17e0 / 0x00fc18c0 -- cSetCloudTypeStep constructors
// (12-state and 16-state variants; the cycle vector is sized to the state count)
// ===========================================================================
// @ 0x00fc16b0
CCloudTypeStep* __fastcall FUN_00fc16b0(CCloudTypeStep* step) {
    step->mVec18.Init();
    step->mCycles.Init();
    step->mField40 = 0;
    step->mpVtable = (void*)0x1491270;
    step->mCycles.Resize(12, 0);
    step->mDone = 0;
    step->mState = 0;
    step->mField0c = 0;
    step->mField10 = 0.0f;
    step->mField14 = 0;
    step->mVec18.Clear();
    return step;
}

// @ 0x00fc17e0
CCloudTypeStep* __fastcall FUN_00fc17e0(CCloudTypeStep* step) {
    step->mVec18.Init();
    step->mCycles.Init();
    step->mField40 = 0;
    step->mpVtable = (void*)0x149127c;
    step->mCycles.Resize(16, 0);
    step->mDone = 0;
    step->mState = 0;
    step->mField0c = 0;
    step->mField10 = 0.0f;
    step->mField14 = 0;
    step->mVec18.Clear();
    return step;
}

// @ 0x00fc18c0
CCloudTypeStep* __fastcall FUN_00fc18c0(CCloudTypeStep* step) {
    step->mVec18.Init();
    step->mCycles.Init();
    step->mField40 = 0;
    step->mpVtable = (void*)0x1491288;
    step->mCycles.Resize(16, 0);
    step->mDone = 0;
    step->mState = 0;
    step->mField0c = 0;
    step->mField10 = 0.0f;
    step->mField14 = 0;
    step->mVec18.Clear();
    return step;
}

// ===========================================================================
// 0x00fc1780 -- destructor of the fixed-vector holder
// ===========================================================================
// @ 0x00fc1780
int __fastcall FUN_00fc1780(int p, int dummy, char del) {
    FixedVectorHolder* h = (FixedVectorHolder*)p;
    (void)dummy;
    h->mVtable0 = 0x1490b80;
    int v = h->mVec2Begin;
    if (v && *(int*)(v - 4)) operator_del((void*)v);
    ((VecBase*)&h->mVecBegin)->DestroyRange((int*)h->mVecBegin, (int*)h->mVecEnd);
    v = h->mVecBegin;
    if (v && *(int*)(v - 4)) operator_del((void*)v);
    if (del & 1) operator_del((void*)p);
    return p;
}

// ===========================================================================
// 0x00fc19a0 -- SWARM_TerrainAddCommands: fills the three command tables and
// registers the terrain command sets
// ===========================================================================
// @ 0x00fc19a0
bool __stdcall FUN_00fc19a0(int unused) {
    (void)unused;
    CSwarmCommandSet desc;

    // Brush commands.
    desc.mpName = 0;
    desc.mpHandler0 = (void*)SWARM_TerrainBrushAddCommands;
    desc.mpHandler1 = (void*)FUN_00f4b690;
    desc.mpHandler2 = (void*)FUN_00f4b0c0;
    desc.mpHandler3 = (void*)FUN_00f49020;
    desc.mField14 = 0;
    desc.mField18 = sTerrainBrushField18;
    desc.mField1c = sTerrainBrushField1c;
    sTerrainBrushCommands = desc;

    // Script commands.
    desc.mpName = 0;
    desc.mpHandler0 = (void*)SWARM_TerrainScriptAddCommands;
    desc.mpHandler1 = (void*)FUN_00f95400;
    desc.mpHandler2 = (void*)FUN_00f94cb0;
    desc.mpHandler3 = (void*)FUN_00f94dd0;
    desc.mField14 = 0;
    desc.mField18 = sTerrainScriptField18;
    desc.mField1c = sTerrainScriptField1c;
    sTerrainScriptCommands = desc;

    // Distribute commands.
    desc.mpName = 0;
    desc.mpHandler0 = (void*)FUN_00f63650;
    desc.mpHandler1 = (void*)SWARM_TerrainDistributeCreate;
    desc.mpHandler2 = (void*)FUN_00f63d50;
    desc.mpHandler3 = (void*)FUN_00f63170;
    desc.mField14 = 0;
    desc.mField18 = sTerrainDistributeField18;
    desc.mField1c = sTerrainDistributeField1c;
    sTerrainDistributeCommands = desc;

    FUN_00f7be60();
    FUN_00f580f0();
    FUN_00f61a70();
    FUN_00f52b70(3, "coriolis");
    FUN_00f58230(3, (void*)FUN_00fc5480);
    FUN_00aa7fa0(6, TERRAIN_WRITE_FORCE_HANDLER);
    return 1;
}

// ===========================================================================
// 0x00fc1ad0 -- zero vector helper (returns 0.0f; __stdcall, 5 args)
// ===========================================================================
float __stdcall FUN_00fc1ad0(int a, int b, int c, int d, int e) {
    (void)a; (void)b; (void)c; (void)d; (void)e;
    return 0.0f;
}

// ===========================================================================
// 0x00fc1ae0 -- cTerrainSystem destructor
// ===========================================================================
// @ 0x00fc1ae0
void __fastcall FUN_00fc1ae0(int* p) {
    cTerrainSystem* s = (cTerrainSystem*)p;
    s->mVtable0 = 0x1491318;
    s->mVtable1 = 0x1491314;
    if (s->mProps1c) s->mProps1c->v1();
    if (s->mObj14) s->mObj14->v1();
    if (s->mObj10) {
        RefCounted* rc = &s->mObj10->mRef;
        int n = rc->mRefCount - 1;
        rc->mRefCount = n;
        if (n == 0) {
            rc->mRefCount = 1;
            rc->Release(1);
        }
    }
    if (s->mObj0c) s->mObj0c->v3();
    s->mVtable0 = 0x13eb938;
    s->mVtable1 = 0x13ef094;
}

// ===========================================================================
// 0x00fc1b60 -- zero a vector field (__stdcall, 5 args)
// ===========================================================================
// @ 0x00fc1b60
void __stdcall FUN_00fc1b60(float* out, int a, int b, int c, int d) {
    (void)a; (void)b; (void)c; (void)d;
    out[0] = 0.0f; out[1] = 0.0f; out[2] = 0.0f;
}

// ===========================================================================
// 0x00fc1ba0 -- release the terrain model
// ===========================================================================
// @ 0x00fc1ba0
void __fastcall FUN_00fc1ba0(int self) {
    if (FUN_0075e620_dummy()) {
        if (SP_ModelManager()) {
            int* m = (int*)SP_ModelManager();
            int* r = (int*)(*(int(__cdecl**)(void*, int))(*(void**)((char*)*(void**)m + 0x1c)))(m, 0x3fbae24);
            (*(void(__cdecl**)(void*, int))(*(void**)((char*)*(void**)r + 0x154)))(r, *(int*)(self + 0x18));
        }
    }
    if (*(int*)(self + 0xc) != 0) FUN_00f67ff0_dummy();
}

// ===========================================================================
// 0x00fc1c00 -- cTerrainSystem constructor
// ===========================================================================
// @ 0x00fc1c00
int* __fastcall FUN_00fc1c00(int* p) {
    cTerrainSystem* s = (cTerrainSystem*)p;
    SP::cDirectPropertyList* props;
    s->mVtable1 = 0x13ef094;
    s->mField08 = 0;
    s->mVtable0 = 0x1491318;
    s->mVtable1 = 0x1491314;
    s->mObj0c = 0;
    s->mObj10 = 0;
    s->mObj14 = 0;
    props = SP::sAppProperties;
    s->mField18 = 0.0f;
    s->mProps1c = props;
    if (props) props->v0();
    s->mTag20 = 0x26b7d69;
    s->mZero24 = 0;
    if (props) FUN_0075e6d0((int)&s->mField18, 0, props);
    return p;
}

// ===========================================================================
// 0x00fc1c70 -- SP::cTerrainSystem::Init: builds the visual model, the editor
// and the sphere wrapper for the terrain system
// ===========================================================================
// @ 0x00fc1c70
int __fastcall FUN_00fc1c70(cTerrainSystem* sys, int dummy, int unused) {
    (void)dummy; (void)unused;

    CEffectsManager* effectsMgr = (CEffectsManager*)EffectsManagerPtr();
    CEffectsObject* effects =
        (CEffectsObject*)effectsMgr->mpVtable->mGetEffects(effectsMgr, 0x3fbae24, 0);
    effects->mpVtable->mSetMode(effects, 2);

    CModelManager* modelMgr = (CModelManager*)SP_ModelManager();
    CModel* model = (CModel*)modelMgr->mpVtable->mGetModel(modelMgr, 0x3fbae24, 0, 0);
    model->mpVtable->mAttachEffects(model, effects);
    model->mpVtable->mSetDetail(model, 0);

    FUN_0075e620(&sys->mField18);
    model->mpVtable->mSetOffset(model, sys->mField18);
    model->mpVtable->mSetParam(model, TERRAIN_MODEL_PARAM_BLOCK, 500.0f);

    FUN_00fc23b0();                                  // SP::UpdateTerrainTerraformTuning

    CApp* app = (CApp*)SP_App();
    CAppSub* appSub = (CAppSub*)app->mpVtable->mGetSubObject(app);
    appSub->mpVtable->mRegister(appSub, 0x5309d37, (void*)FUN_00f52690);

    void* resource = FUN_00f95da0();
    FUN_00f96310(resource);
    FUN_00f48ad0(resource);

    VtblFour* oldEditor = sys->mObj0c;
    VtblFour* editor = (VtblFour*)FUN_00f6a930();
    if (editor != oldEditor) {
        if (editor)
            editor->v2();                            // add reference
        sys->mObj0c = editor;
        if (oldEditor)
            oldEditor->v3();                         // release old
    }
    FUN_00f69a30(sys->mObj0c);                       // editor Init
    FUN_00f48ab0(sys->mObj0c);

    void* quadMgr = FUN_00f939b0();
    FUN_00f940a0(quadMgr);
    FUN_00f48ad0(quadMgr);

    VtblTwo* oldWrapper = sys->mObj14;
    CTerrainSphereWrapper* wrapper = (CTerrainSphereWrapper*)operator_new(
        0xc, "Terrain/TerrainSphereWrapper/cTerrainSphereWrapper", 0, 0, 0, 0);
    if (wrapper) {
        wrapper->mpVtable1 = (void*)0x13ef094;       // base interface, replaced just below
        wrapper->mField08 = 0;
        wrapper->mpVtable0 = (void*)0x1491338;
        wrapper->mpVtable1 = (void*)0x14188c0;
    }
    if ((VtblTwo*)wrapper != oldWrapper) {
        if (wrapper)
            ((VtblTwo*)wrapper)->v0();               // add reference
        sys->mObj14 = (VtblTwo*)wrapper;
        if (oldWrapper)
            oldWrapper->v1();                        // release old
    }
    FUN_0067cc50(sys->mObj14);

    FUN_00fba330();                                  // SP::cTerrainStateMgr::StaticInit
    FUN_00c2e4e0();                                  // ReadText
    return 1;
}

// ===========================================================================
// 0x00fc1e40 -- cTerrainSystem shutdown: tears down the pool, the editor, the
// sphere wrapper and the manager registrations
// ===========================================================================
// @ 0x00fc1e40
int __fastcall FUN_00fc1e40(cTerrainSystem* sys) {
    if (FUN_00f48a90()) {
        FUN_00fb7a60(FUN_00f48a90());                // QuadReleaseVec
        CQuadPool* pool = (CQuadPool*)FUN_00f48a90();
        if (pool) {
            if (pool->mpBuffer && *(int*)((char*)pool->mpBuffer - 4) != 0)
                operator_del(pool->mpBuffer);
            if (pool->mpOwner)
                ((VtblTwo*)pool->mpOwner)->v1();
            operator_del(pool);
        }
        FUN_00f48ae0(0);
    }

    FUN_00fa0360();
    FUN_00fc0fe0();                                  // SP::ResetTerrainGlobals

    if (sys->mObj10) {
        FUN_00f48ad0(0);
        CountedHolder* holder = sys->mObj10;
        FUN_00f93c00(holder);
        sys->mObj10 = 0;
        RefCounted* ref = &holder->mRef;
        int count = --ref->mRefCount;
        if (count == 0) {
            ref->mRefCount = 1;
            ref->Release(1);
        }
    }

    if (sys->mObj14) {
        FUN_0067cc50(0);
        VtblTwo* wrapper = sys->mObj14;
        if (wrapper) {
            sys->mObj14 = 0;
            wrapper->v1();
        }
    }

    if (sys->mObj0c) {
        FUN_00f48ab0(0);
        VtblFour* editor = sys->mObj0c;
        FUN_00f6b840(editor);                        // QuadMgr::Destroy
        if (sys->mObj0c) {
            sys->mObj0c = 0;
            editor->v3();
        }
    }

    if (FUN_00f48a60()) {
        FUN_00f95d90(FUN_00f48a60());
        void* scope = FUN_00f48a60();
        if (scope)
            ((VtblOneInt*)scope)->v0(1);
        FUN_00f48ac0(0);
    }

    CModelManager* modelMgr = (CModelManager*)SP_ModelManager();
    if (modelMgr)
        modelMgr->mpVtable->mReleaseModel(modelMgr, 0x3fbae24);

    CEffectsManager* effectsMgr = (CEffectsManager*)EffectsManagerPtr();
    if (effectsMgr)
        effectsMgr->mpVtable->mShutdown(effectsMgr, 0x3fbae24);

    return 1;
}

// ===========================================================================
// 0x00fc1fa0 -- pick a terraform radius by level
// ===========================================================================
float __cdecl FUN_00fc1fa0(int level) {
    switch (level) {
        case 1: return kTerraformRadiusT1;
        case 2: return kTerraformRadiusT2;
        case 3: return _kTerraformRadiusT3;
    }
    return kTerraformRadiusT1;
}

// ===========================================================================
// 0x00fc1fd0 -- SP::GetTerraformPlanetType
// ===========================================================================
// @ 0x00fc1fd0
int __cdecl FUN_00fc1fd0(float f) {
    if (f < 0.1f) return 2;
    if (f >= 0.1f && f < 0.4f) return 3;
    if (f >= 0.4f && f < 0.6f) return 1;
    if (f < 0.6f || kLavaThreshold <= f) return 4;
    return 5;
}

// ===========================================================================
// 0x00fc2040 -- radial falloff factor
// ===========================================================================
// The original computes the whole falloff in x87 and takes the root with an inline fsqrt.
// cl only inlines sqrt under /fp:fast, which this module's flags do not use, so do the root
// with x87 directly (double keeps enough precision that the float result matches).
static inline double SqrtX87(double v) {
    __asm fld v
    __asm fsqrt
    __asm fstp v
    return v;
}
// @ 0x00fc2040
float __cdecl FUN_00fc2040(float x, float y) {
    double dx = (double)x - 0.5;
    double dy = (double)y - 0.5;
    float f = (float)(1.0 - SqrtX87(dy * dy + dx * dx) * (double)1.4142135f);
    float r = 0.0f;
    if (0.0f <= f) r = f;
    return r;
}

// --- small helpers referenced above (declared late for the reconstructions) ---
