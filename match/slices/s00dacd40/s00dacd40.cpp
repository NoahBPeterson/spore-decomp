// Slice s00dacd40 -- six cdecl entries of the citizen behavior set that the behavior descriptor table
// (0x01593be0, behavior id 0x5524115) groups together:
//
//   0x00dacd40  unnamed                        -- "domesticate" activates: cancels the tribe timer, drops
//                                                 the tool, marks the creature idle.
//   0x00dace20  SP::CHIEFTAIN_TOOL_INSPECT_Tick -- walks to the chieftain's tool and inspects it.
//   0x00dad0c0  SP::IDLE_VIGNETTE_Activate      -- claims a tribe slot and starts an idle vignette.
//   0x00dad260  unnamed                        -- idle vignette deactivate: releases the slot.
//   0x00dad320  unnamed                        -- idle vignette countdown; true while the vignette runs.
//   0x00dad390  SP::TRIBE_DOMESTICATE_Tick      -- nine-state domesticate-an-animal behavior.
//
// The runtime calls all six with the creature (and, for most, the behavior memory block) on the stack, so
// they are plain cdecl functions: the creature is the first argument and the memory block is the last.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (same SP behavior module as s00db4f60 / s00db5e80 / s00da2360).
#include "types.h"

namespace SP {

struct Vec3 { float x, y, z; Vec3() {} Vec3(float a, float b, float c) : x(a), y(b), z(c) {} };
struct Quat { float x, y, z, w; };

#define PV(n) virtual void pv##n();

class cSPCreatureCitizen;
class cTribe;

// Spatial / locomotive sub-object (creature+0xc0, tribe+0x120); own vtable.
struct Loco {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual const Vec3* GetPosition();                       // +0x2c
    PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16)
    virtual const Vec3* GetFacing();                         // +0x5c
    PV(18) PV(19) PV(1a) PV(1b) PV(1c)
    virtual float GetRadius();                               // +0x74
    PV(1e) PV(1f) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(2a) PV(2b) PV(2c) PV(2d) PV(2e) PV(2f) PV(30) PV(31) PV(32) PV(33) PV(34) PV(35)
    PV(36) PV(37) PV(38) PV(39) PV(3a)
    virtual void vfec();                                     // +0xec
    char pad00[0x50 - 0x04];                                 // to +0x50 (vptr is +0x00)
    unsigned mFlags50;                                       // +0x50
    bool IsNearGoal();                                       // 0xc42e20 (direct call, this = loco)
};

// Animation weight holder (creature+0x5a8); own vtable.
struct Obj5a8 {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d) PV(0e)
    PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
    virtual float GetFloat();                                // +0x58
    char pad00[0x80 - 0x04];                                 // to +0x80
    void FUN_00f924e0(float f);                              // 0xf924e0 (thiscall, float)
    void FUN_00bfc460(int a);                                // 0xbfc460 (thiscall, int)
};

// Animation state (creature+0xb54).
struct AnimState { char pad00[0x80]; float mWeight; };       // +0x80

// One 0x14-byte tribe slot in the array at tribe+0x294.
struct TribeSlot { Vec3 mPos; int mUnk0c; bool mbOccupied; };

// The object the tribe keeps for a tool type; the tool object itself lives at +0x34 (own vtable).
struct ToolObj {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual const Vec3* GetPosition();                       // +0x2c
    PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16)
    PV(17) PV(18) PV(19) PV(1a) PV(1b) PV(1c)
    virtual float GetRadius();                               // +0x74
};
struct TribeTool {
    char pad00[0x34];
    ToolObj mTool;                                           // +0x34
    char pad34[0x244 - 0x34 - sizeof(ToolObj)];
    int  mToolFlags;                                         // +0x244 (checked by FUN_00bf3a90)
};

// Single vignette definition (0x7b4 bytes) inside the vignette table.
struct VignetteDef {
    char pad00[4];
    int  mKey;                                               // +0x04
    char pad08[0x7b4 - 8];
};
struct VignetteRange { VignetteDef* mpBegin; VignetteDef* mpEnd; };

// The vignette table manager singleton (0x00b3d4e0 -> 0x0167eb54).
struct VignetteMgr {
    VignetteRange* Find(unsigned key, int a);                // 0xbc7610 (ret 8)
    void* FUN_00bc3db0(int id);                              // 0xbc3db0 (ret 4)
    bool  FUN_00bc3df0(int id);                              // 0xbc3df0 (ret 4)
    bool  FUN_00bc4900(int id, cSPCreatureCitizen* c, int a);// 0xbc4900 (ret 0xc)
    void  FUN_00bc52a0(int id, cSPCreatureCitizen* c);       // 0xbc52a0 (ret 8)
    int   FUN_00bc65f0(const void* a, const Vec3* b, const Vec3* c);   // 0xbc65f0 (ret 0xc)
};

// The active-vignette list singleton (0x00bc9b00 -> 0x0168b56c).
struct VignetteList {
    void* FUN_00bcb0b0(unsigned key, int id, void* tag, const char* name);   // 0xbcb0b0 (ret 0x10)
};

// The vignette instance an activated vignette runs on.
struct VignetteNode {
    char  pad00[0x10];
    int   mState10;                                          // +0x10 (1 while the vignette is running)
    char  pad14[0x1a4 - 0x14];
    int   mSlot;                                             // +0x1a4 (claimed tribe slot)
    int   mHandle;                                           // +0x1a8 (handle inside the vignette table)
    float mTimer;                                            // +0x1ac (time left, in seconds)
};

// The creature's behavior environment (creature+0xb4c).
struct BehaviorEnv {
    char pad00[8];
    struct Sub {
        void FUN_00bc97b0();                                 // 0xbc97b0 (clears the agent's order deque)
        void FUN_00bc97f0(int a, int b, float c, cSPCreatureCitizen* d);   // 0xbc97f0
        char pad[0x1f0];
    } mSub;                                                  // +0x08
    char pad1f8[0x600 - 0x1f8];
    VignetteNode* mpVignette;                                // +0x600
    char pad604[0x60c - 0x604];
    void* mpOrderHead;                                       // +0x60c (first pending agent order)
    void  FUN_00bcb430();                                    // 0xbcb430 (drops the vignette)
    void  FUN_00bcb480(VignetteNode* node, cSPCreatureCitizen* c, int a, int b);  // 0xbcb480
    void* FirstPending();                                    // 0xbca2c0 (first pending agent order, or 0)
};

// The creature's corral (FUN_00c8fed0) with a vector-like member at +0x70.
struct CorralVector {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual const Vec3* GetPosition();                       // +0x2c
    PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16)
    virtual const Vec3* GetFacing(Vec3* out);                // +0x5c
    PV(18) PV(19) PV(1a) PV(1b) PV(1c)
    virtual float GetRadius();                               // +0x74
};
struct Corral { char pad00[0x70]; CorralVector mVec; };

class cTribe { public:
    char pad00[0x294];
    TribeSlot* mpSlotsBegin;                                 // +0x294
    TribeSlot* mpSlotsEnd;                                   // +0x298
    char pad29c[0x2c8 - 0x29c];
    float mTimer;                                            // +0x2c8
    char pad2cc[0x556 - 0x2cc];
    bool  mbFlag556;                                         // +0x556
    char pad557[0x19c4 - 0x557];
    Corral* mpCorral;                                        // +0x19c4

    TribeTool* GetToolOfType(int type);                      // 0xc8f6e0 (thiscall, ret 4)
    void       FUN_00c95cc0(cSPCreatureCitizen* c);          // 0xc95cc0 (thiscall, ret 4)
    Corral*    GetCorral();                                  // 0xc8fed0 (thiscall)
};

// The planet model singleton (0x00b3d350 -> 0x0167eaf8).
class cPlanetModel { public:
    void  DirectionToSurfacePosition(Vec3* out, const Vec3* in);      // 0xb815a0 (ret 8)
    Quat* BuildSurfaceOrientation(Quat* out, const Vec3* pos);        // 0xb7f190 (ret 8)
    void  MakeRandomWorldPosition(Vec3* out, float a, float b);       // 0xb81780
};

// The object behind 0x00b3d310 (0x0167eae8).
struct PlanetObj {
    void FUN_00b453a0(Loco* loco);                           // 0xb453a0 (thiscall, ret 4)
};

struct ToolState {                                           // behavior memory block of CHIEFTAIN_TOOL_INSPECT
    int  mAnimId;                                            // +0x00 (running inspect animation)
    int  mState;                                             // +0x04 (0 walk, 1 inspect, 2 wait)
    int  mAnim;                                              // +0x08 (animation handle written by the helper)
    int  mToolType;                                          // +0x0c
    Vec3 mToolPos;                                           // +0x10
    int  mPad1c;                                             // +0x1c
};

struct VignetteMem {                                         // behavior memory block of IDLE_VIGNETTE_*
    int   mActive;                                           // +0x00 (vignette node, 0 until activated)
    char  pad04[4];
    int   mField08;                                          // +0x08
    int   mKey;                                              // +0x0c
    void* mSkip10;                                           // +0x10
    char  pad14[4];
    int   mVignetteIndex;                                    // +0x18
    int   mSlot;                                             // +0x1c
    unsigned mTableKey;                                      // +0x20
};

struct DomesticateState {                                    // behavior memory block of TRIBE_DOMESTICATE
    int mState;                                              // +0x00
    int mAnimId;                                             // +0x04
    int mAnimId2;                                            // +0x08
    int mNoun;                                               // +0x0c
};

#define PV(n) virtual void pv##n();

class cSPCreatureCitizen { public:
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d) PV(0e)
    PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(1a) PV(1b) PV(1c) PV(1d)
    PV(1e) PV(1f) PV(20) PV(21) PV(22) PV(23)
    virtual void vf90();                                     // +0x90
    char pad04[0xc0 - 0x04];                                 // to +0xc0 (vptr is +0x00)
    Loco mLoco;                                              // +0xc0
    char padc4[0x12f - 0xc0 - sizeof(Loco)];
    bool mbF12f;                                             // +0x12f
    char pad130[0x330 - 0x130];
    unsigned mFlags330;                                      // +0x330 (bit 0: movement finished)
    char pad334[0x5a8 - 0x334];
    Obj5a8    mObj5a8;                                       // +0x5a8
    char pad5ac[0xb20 - 0x5a8 - sizeof(Obj5a8)];
    void* mpSpecies;                                         // +0xb20
    char padb24[0xb4c - 0xb24];
    BehaviorEnv* mpEnv;                                      // +0xb4c
    char padb50[0xb54 - 0xb50];
    AnimState* mpAnim;                                       // +0xb54
    unsigned   mFlagsB58;                                    // +0xb58
    char padb5c[0xb5e - 0xb5c];
    bool       mbB5e;                                        // +0xb5e

    cTribe*  GetTribe();                                     // 0xc22f50
    void     FUN_00c14750(int a);                            // 0xc14750
    void     SetCurrentToolEffect(int effect, int a);        // 0xc24f40
    bool     AnimationFinished(unsigned id);                 // 0xc12400
    unsigned InterruptAnimation(unsigned id, int a, int b);  // 0xc12310
    unsigned PlayAnimation(unsigned id, int a, int b);       // 0xc12190
    unsigned PlayAnimationWithTarget(unsigned id, const Vec3* target, int a);               // 0xc14910
    unsigned PlayAnimationWithTarget2(unsigned id, const Vec3* target, int a, int b);       // 0xc14940
    unsigned InterruptAnimationWithTarget(unsigned id, const Vec3* target, int a, int b);   // 0xc149c0
    bool     WaitForAnimEventOrEnd(unsigned ev, int* out, int a, int b, int c);             // 0xc14ef0
    void     MoveToPointAtSpeed(int mode, const Vec3* p, float s0, float s1);                // 0xc1c1d0
    void     MoveToPointAndFacingAtSpeed(int mode, const Vec3* p, const Vec3* facing, float s0, float s1); // 0xc1c5c0
    bool     FUN_00c25480(int a, int b);                     // 0xc25480
    unsigned FUN_00c22820();                                 // 0xc22820
    void     TryJumpToTarget(int a, const Vec3* p, void* b, float c, int d);                // 0xc190e0
    void     d0c0(unsigned a, char b);                       // 0xc0d0c0 (CCB highlight)
};
#undef PV

// Singletons and free functions.
VignetteMgr*    FUN_00b3d4e0();                              // 0xb3d4e0 -> 0x0167eb54
VignetteList*   FUN_00bc9b00();                              // 0xbc9b00 -> 0x0168b56c
cPlanetModel*   PlanetModel();                               // 0xb3d350 -> 0x0167eaf8
PlanetObj*      FUN_00b3d310();                              // 0xb3d310 -> 0x0167eae8
Vec3*           normalized_safe(Vec3* out, const Vec3* in);  // 0x449c20
Vec3*           FUN_0059aed0(Vec3* out, const Quat* a, const Quat* b);   // 0x59aed0
void*           FUN_00d99500(int noun);                      // 0xd99500
void            FUN_00da61e0(cSPCreatureCitizen* c, int noun);// 0xda61e0
unsigned        FUN_00da6270(cSPCreatureCitizen* c, int noun);// 0xda6270
float*          FUN_00c986d0(cTribe* tribe, int toolType, int* out, cSPCreatureCitizen* c);  // 0xc986d0
void            FUN_00d9a4a0(Vec3* out, cSPCreatureCitizen* c, ToolObj* tool);                // 0xd9a4a0
unsigned        RandomUint32Uniform(unsigned n);             // 0xa68fb0 (thiscall on gMathRandom)
float           RandomFloatRange(float lo, float hi);        // 0x572a10
void*           FUN_00c41ec0(Loco* loco);                    // 0xc41ec0 -> loco+0x1f4
void*           FUN_00c423c0(void* p);                       // 0xc423c0

extern float gMinSpeed;                                      // 0x01572070 (0.4f)
extern float gMaxSpeed;                                      // 0x0157206c (0.6f)
extern float gFloatMax;                                      // 0x0142ef7c (FLT_MAX)

// =====================================================================
// @ 0x00dacd40
// =====================================================================
void FUN_00dacd40(cSPCreatureCitizen* c)
{
    Obj5a8* o = &c->mObj5a8;
    cTribe* tribe = c->GetTribe();
    if (!tribe->mbFlag556) {
        if (tribe->mTimer > 0.0f) {
            tribe->mTimer = 0.0f;
            o->FUN_00f924e0(o->GetFloat());
            o->FUN_00bfc460(0);
            c->vf90();
            tribe->FUN_00c95cc0(c);
        }
        c->mpEnv->mSub.FUN_00bc97b0();
        c->mFlagsB58 &= ~0x800u;
        c->mpAnim->mWeight = 1.0f;
        c->FUN_00c14750(1);
        c->mbF12f = true;
        FUN_00b3d310()->FUN_00b453a0(&c->mLoco);
        c->mLoco.mFlags50 &= ~0x80u;
        c->SetCurrentToolEffect(0x11, -1);
    }
}

// =====================================================================
// @ 0x00dace20  SP::CHIEFTAIN_TOOL_INSPECT_Tick
// =====================================================================
bool CHIEFTAIN_TOOL_INSPECT_Tick(cSPCreatureCitizen* c, int, int, int, int, ToolState* mem)
{
    cTribe* tribe = c->GetTribe();
    TribeTool* tool = tribe->GetToolOfType(mem->mToolType);
    if (!tool)
        return false;
    if (tool->mToolFlags > 0)
        return false;

    const Vec3* p = tool->mTool.GetPosition();
    float dx = p->x - mem->mToolPos.x;
    float dy = p->y - mem->mToolPos.y;
    float dz = p->z - mem->mToolPos.z;
    if (dx * dx + dy * dy + dz * dz > 1.0f)
        return false;

    switch (mem->mState) {
    case 0: {
        mem->mState = 1;
        float radius = tool->mTool.GetRadius() + c->mLoco.GetRadius();
        float* target = FUN_00c986d0(tribe, mem->mToolType, &mem->mAnim, c);
        if (mem->mAnim < 0)
            return false;
        const Vec3* tpos = tool->mTool.GetPosition();
        Vec3 diff;
        diff.x = target[0] - tpos->x;
        diff.y = target[1] - tpos->y;
        diff.z = target[2] - tpos->z;
        Vec3 dir;
        normalized_safe(&dir, &diff);
        float dist = radius + 0.1f;
        Vec3 goal(dir.x * dist, dir.y * dist, dir.z * dist);
        const Vec3* base = tool->mTool.GetPosition();
        Vec3 dest(base->x + goal.x, base->y + goal.y, base->z + goal.z);
        Vec3 facing(-dir.x, -dir.y, -dir.z);
        c->MoveToPointAndFacingAtSpeed(2, &dest, &facing, gMinSpeed, gMaxSpeed);
        break;
    }
    case 1:
        if (c->mLoco.IsNearGoal()) {
            unsigned anim = 0x4c70750 + RandomUint32Uniform(3);
            Vec3 out;
            FUN_00d9a4a0(&out, c, &tool->mTool);
            mem->mAnimId = c->PlayAnimationWithTarget(anim, &out, -1);
            mem->mState = 2;
            return true;
        }
        break;
    case 2:
        if (c->AnimationFinished(mem->mAnimId))
            return false;
        break;
    }
    return true;
}

// =====================================================================
// @ 0x00dad0c0  SP::IDLE_VIGNETTE_Activate
// =====================================================================
bool IDLE_VIGNETTE_Activate(cSPCreatureCitizen* c, int, int, int, int, int, VignetteMem* mem)
{
    c->mLoco.vfec();
    VignetteNode* node = (VignetteNode*)mem->mActive;
    if (!node) {
        cTribe* tribe = c->GetTribe();
        unsigned slot = (unsigned)mem->mSlot;
        if (slot >= (unsigned)((tribe->mpSlotsEnd - tribe->mpSlotsBegin) / 5))
            return false;
        TribeSlot* s = &tribe->mpSlotsBegin[slot];
        s->mbOccupied = true;

        Vec3 surf;
        PlanetModel()->DirectionToSurfacePosition(&surf, &s->mPos);

        VignetteRange* range = FUN_00b3d4e0()->Find(mem->mTableKey, 0);
        VignetteDef* def = (VignetteDef*)((char*)range->mpBegin + mem->mVignetteIndex * 0x7b4);

        node = (VignetteNode*)FUN_00bc9b00()->FUN_00bcb0b0(0x55241ec, def->mKey, (void*)0x18eb4b7, "IdleVignette");
        int* fields = &node->mSlot;
        if (fields) {
            node->mSlot = -1;
            node->mHandle = -1;
        }

        Quat q;
        PlanetModel()->BuildSurfaceOrientation(&q, &surf);
        Vec3 dir;
        FUN_0059aed0(&dir, (const Quat*)0x169f408, &q);
        node->mHandle = FUN_00b3d4e0()->FUN_00bc65f0(def, &dir, &surf);
        node->mTimer = 20.0f;
        node->mSlot = slot;
    }
    c->mpEnv->FUN_00bcb480(node, c, 0, 0);
    bool ok = FUN_00b3d4e0()->FUN_00bc4900(node->mHandle, c, 0);
    c->d0c0(6, ok);
    return ok;
}

// =====================================================================
// @ 0x00dad260
// =====================================================================
void FUN_00dad260(cSPCreatureCitizen* c)
{
    VignetteNode* node = c->mpEnv->mpVignette;
    if (node) {
        FUN_00b3d4e0()->FUN_00bc52a0(node->mHandle, c);
        if (node->mState10 == 1) {
            cTribe* tribe = c->GetTribe();
            unsigned slot = (unsigned)node->mSlot;
            if (slot < (unsigned)(tribe->mpSlotsEnd - tribe->mpSlotsBegin))
                tribe->mpSlotsBegin[slot].mbOccupied = false;
            node->mSlot = 0;
        }
    }
    c->mLoco.vfec();
    c->FUN_00c14750(1);
    c->mpEnv->FUN_00bcb430();
    c->d0c0(6, 0);
}

// =====================================================================
// @ 0x00dad320
// =====================================================================
bool FUN_00dad320(cSPCreatureCitizen* c, int, int, int, int, int, int, float dt)
{
    VignetteNode* node = c->mpEnv->mpVignette;
    if (node->mHandle == -1)
        return false;
    VignetteMgr* mgr = FUN_00b3d4e0();
    if (mgr->FUN_00bc3db0(node->mHandle)) {
        node->mTimer = node->mTimer - dt;
        if (node->mTimer < 0.0f)
            return false;
    }
    return !mgr->FUN_00bc3df0(node->mHandle);
}

// =====================================================================
// @ 0x00dad390  SP::TRIBE_DOMESTICATE_Tick
// =====================================================================
unsigned TRIBE_DOMESTICATE_Tick(cSPCreatureCitizen* c, int, int, int, int, DomesticateState* mem)
{
    cSPCreatureCitizen* animal = (cSPCreatureCitizen*)FUN_00d99500(mem->mNoun);
    if (!animal)
        return FUN_00da6270(c, 0x19);

    switch (mem->mState) {
    case 0: {
        c->mpEnv->mSub.FUN_00bc97f0(4, 0, gFloatMax, c);
        c->FUN_00c14750(1);
        animal->mLoco.vfec();
        float radius = animal->mLoco.GetRadius() + c->mLoco.GetRadius();
        const Vec3* p = animal->mLoco.GetPosition();
        c->MoveToPointAtSpeed(2, p, radius + gMinSpeed, radius + gMaxSpeed);
        mem->mState = 1;
        return 1;
    }
    case 1: {
        if (!c->mLoco.IsNearGoal())
            return 1;
        const Vec3* here = c->mLoco.GetPosition();
        const Vec3* there = animal->mLoco.GetPosition();
        Vec3 diff(there->x - here->x, there->y - here->y, there->z - here->z);
        Vec3 dir;
        normalized_safe(&dir, &diff);
        Vec3 neg(-dir.x, -dir.y, -dir.z);
        c->MoveToPointAndFacingAtSpeed(2, c->mLoco.GetPosition(), &dir, 1.0f, 2.0f);
        animal->MoveToPointAndFacingAtSpeed(2, animal->mLoco.GetPosition(), &neg, 1.0f, 2.0f);
        c->FUN_00c14750(1);
        mem->mState = 2;
        return 1;
    }
    case 2: {
        if (!c->mLoco.IsNearGoal() || !animal->mLoco.IsNearGoal())
            return 1;
        mem->mAnimId = c->PlayAnimation(0x5654d97, 1, c->FUN_00c22820());
        mem->mAnimId2 = animal->InterruptAnimation(0x5bace5e, -1, 0);
        mem->mState = 3;
        return 1;
    }
    case 3: {
        int ev = -1;
        if (!c->WaitForAnimEventOrEnd(0x7d7502fc, &ev, 0, mem->mAnimId, 1))
            return 1;
        c->SetCurrentToolEffect(0xc, ev);
        mem->mAnimId = c->PlayAnimationWithTarget2(0x5654df6, animal->mLoco.GetPosition(), -1, -1);
        mem->mState = 4;
        return 1;
    }
    case 4: {
        if (!c->AnimationFinished(mem->mAnimId))
            return 1;
        mem->mAnimId = c->PlayAnimationWithTarget2(0x5654df7, animal->mLoco.GetPosition(), -1, -1);
        mem->mState = 5;
        int* pending = (int*)c->mpEnv->FirstPending();
        if (pending && *pending == 0x19)
            *(unsigned*)((char*)pending + 0x39) = (unsigned)mem;
        return 1;
    }
    case 5: {
        if (!c->FUN_00c25480(0xc, 0) || !c->AnimationFinished(mem->mAnimId))
            return 1;
        c->GetTribe();
        Corral* corral = c->GetTribe()->GetCorral();
        CorralVector* vec = &corral->mVec;
        const Vec3* apos = animal->mLoco.GetPosition();
        float radius = animal->mLoco.GetRadius() + vec->GetRadius() + 1.5f;
        Vec3 fbuf;
        const Vec3* facing = vec->GetFacing(&fbuf);
        Vec3 scaled(facing->x * radius, facing->y * radius, facing->z * radius);
        const Vec3* vpos = vec->GetPosition();
        Vec3 target(vpos->x - scaled.x, vpos->y - scaled.y, vpos->z - scaled.z);
        Vec3 surf;
        PlanetModel()->DirectionToSurfacePosition(&surf, &target);
        animal->MoveToPointAndFacingAtSpeed(2, &surf, vec->GetFacing(&fbuf), 1.0f, 2.0f);
        if (((unsigned*)c->mpSpecies)[0x544 / 4] < ((unsigned*)animal->mpSpecies)[0x544 / 4])
            c->d0c0(6, 1);
        mem->mAnimId = c->InterruptAnimationWithTarget(0x5654df8, vec->GetFacing(&fbuf), -1, -1);
        mem->mState = 6;
        (void)apos;
        return 1;
    }
    case 6: {
        const Vec3* self = c->mLoco.GetPosition();
        float radius = animal->mLoco.GetRadius() + c->mLoco.GetRadius();
        void* goal = FUN_00c41ec0(&c->mLoco);
        if (*(int*)((char*)goal + 0x5c)) {
            const Vec3* mine = c->mLoco.GetPosition();
            const Vec3* theirs = (const Vec3*)FUN_00c423c0(goal);
            float dx = theirs->x - mine->x;
            float dy = theirs->y - mine->y;
            float dz = theirs->z - mine->z;
            float d = radius + 2.0f;
            if (d * d < dx * dx + dy * dy + dz * dz)
                goto near;
        }
        {
            float r = -(RandomFloatRange(0.0f, 1.0f) + radius);
            const Vec3* facing = c->mLoco.GetFacing();
            Vec3 off(facing->x * r, facing->y * r, facing->z * r);
            const Vec3* p = c->mLoco.GetPosition();
            Vec3 target(p->x + off.x, p->y + off.y, p->z + off.z);
            Vec3 surf;
            PlanetModel()->DirectionToSurfacePosition(&surf, &target);
            c->MoveToPointAtSpeed(2, &surf, 1.0f, 2.0f);
        }
    near:
        if (!(animal->mLoco.IsNearGoal() || (animal->mFlags330 & 1))
            || !(c->mLoco.IsNearGoal() || (c->mFlags330 & 1)))
            return 1;
        c->GetTribe();
        CorralVector* vec = &c->GetTribe()->GetCorral()->mVec;
        float d2 = vec->GetRadius() - c->mLoco.GetRadius() * 2.0f;
        float keep = d2 > 0.0f ? d2 : 0.0f;
        Vec3 rnd;
        PlanetModel()->MakeRandomWorldPosition(&rnd, keep, 0.0f);
        animal->TryJumpToTarget(0, &rnd, (void*)0x169f3b8, 0.0f, 1);
        animal->MoveToPointAtSpeed(2, &rnd, 1.0f, 2.0f);
        animal->d0c0(6, 0);
        c->MoveToPointAtSpeed(2, self, 1.0f, 2.0f);
        mem->mAnimId = c->PlayAnimation(0x5654df9, 1, -1);
        mem->mState = 7;
        FUN_00da61e0(c, 0x19);
        return 1;
    }
    case 7: {
        if (!c->AnimationFinished(mem->mAnimId))
            return 1;
        mem->mAnimId = c->PlayAnimation(0x5654df4, 1, -1);
        mem->mState = 8;
        return 1;
    }
    case 8: {
        int ev = -1;
        if (!c->WaitForAnimEventOrEnd(0xbfa50b5a, &ev, 0, mem->mAnimId, 1))
            return 1;
        mem->mState = 0;
        return FUN_00da6270(c, 0x19);
    }
    }
    return 1;
}

} // namespace SP
