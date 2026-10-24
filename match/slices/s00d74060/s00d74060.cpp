// Slice s00d74060 -- SP::cTribeGameBehaviorFish::Action (0x00d74060, 5016 bytes).
//
// Per-tick AI for a tribe fish-gathering citizen.  It walks the tribe members whose
// behaviour is the "fish" objective and runs a 0x1a-state machine on the member's
// state record: go to the fishing spot, cast, wait for a bite, play the catch
// animation, stow the tool, return home, and repeat.
//
// Transliterated from the original disassembly + Ghidra decompilation.  The member
// iteration, every state case and the identified engine/creature calls are
// reproduced; deep creature sub-object navigation is done through the resolved
// sub-object offsets.  Byte-exactness is not attempted: the original interleaves
// several x87/SSE schedules and dead materialization pushes (e.g. the 2 register
// spill copies in front of every AgentFinished call) that are not reproduced here.
//
// Card: work/match/scratch_s00d74060_card.txt

#include "types.h"

typedef unsigned char u8;
typedef unsigned int  u32;
typedef long long     i64;

// ------------------------------------------------------------------ iteration

struct tSlotEntry { u32 mSlotInfo; void* mpData; };

struct AgentDeque {
    tSlotEntry** mpBlocks;                 // +0x00
};

struct AgentFilter {
    void* mpOwner;
    u8    mbFlag;
    AgentFilter(void* pOwner, bool flag) : mpOwner(pOwner), mbFlag(flag ? 1 : 0) {}
};

struct AgentIterator {
    AgentDeque* mpDeque;                   // +0x00
    u32         mIndex;                    // +0x04
    AgentDeque* mpEndDeque;                // +0x08
    u32         mEndIndex;                 // +0x0c
    AgentFilter mFilter;                   // +0x10

    AgentIterator(AgentDeque* pDeque, const AgentFilter& filter);   // 0x00abf010
    void Next();                                                    // 0x00abeb20
    bool IsDone() const
    {
        return (u32)mpDeque + mIndex == (u32)mpEndDeque + mEndIndex;
    }
    void* Get() const
    {
        return ((AgentDeque*)mpDeque)->mpBlocks[mIndex >> 7][mIndex & 0x7f].mpData;
    }
};

// cInteractionAgent object: virtual Cast at slot +0x08
struct AgentObj {
    virtual void v00();
    virtual void v04();
    virtual void* __thiscall Cast(int typeID);   // +0x08
};

// ------------------------------------------------------------------ engine

struct TimeMgr {
    i64 __thiscall Time();                              // 0x00b316c0
};
void* GameTimeManager();                                                // 0x00b3d380

struct FishInfoMap {
    u32 mData[7];
    int* __thiscall FindOrAdd(void** key);              // 0x00d73bc0
};

// cSPCreatureCitizen / cSPCreatureBase methods (ecx = creature)
struct Eng {
    void* __thiscall GetTribe();                                            // 0x00c22f50
    char  __thiscall HasSpecializedTool(int tool);                          // 0x00c236e0
    int   __thiscall GetToolEffect(int tool);                               // 0x00c235e0
    char  __thiscall IsLeader();                                            // 0x00c232d0
    char  __thiscall PutAwayToolExceptFor(int tool);                        // 0x00c22ca0
    char  __thiscall SetToolOnAnimEvent(int tool);                          // 0x00c263e0
    char  __thiscall AnimationFinished(int handle);                         // 0x00c123f0
    char  __thiscall AnimationFinished2(int handle);                        // 0x00c12400
    int   __thiscall PlayAnimation(int id, int blend, int handle);          // 0x00c12190
    int   __thiscall InterruptAnimation(int id, int blend, int handle);     // 0x00c12310
    int   __thiscall PlayAnimationWithTarget(int id, int target, int blend, int handle);     // 0x00c14940
    int   __thiscall InterruptAnimationWithTarget(int id, int target, int blend, int handle); // 0x00c149c0
    char  __thiscall WaitForAnimEventOrEnd(int ev, int* out, int minId, int handle, int b);  // 0x00c14ef0
    void  __thiscall MoveToPointAtSpeed(int mode, float* pos, float dist, float speed);       // 0x00c1c1d0
    void  __thiscall MoveToPointAndFacingAtSpeed(int mode, void* pos, void* facing, float dist, float speed); // 0x00c1c5c0
    void  __thiscall SetCurrentToolEffect(int effect, int blend);           // 0x00c24f40
    void  __thiscall PerformSocialAction(int target, int a);                // 0x00c23300
    void  __thiscall SetToolTarget(float x, float y, float z);              // 0x00c234a0
    void  __thiscall SetToolFacing(float x, float y, float z);              // 0x00c227f0
    void  __thiscall SetToolArg(int a);                                     // 0x00c22860
    int   __thiscall AnimHandle();                                          // 0x00c22820
    int   __thiscall ToolIndex();                                           // 0x00c22a70
    void* __thiscall FindSlotByKey(int key, int a);                         // 0x00c0f9b0
    void* __thiscall FindSlotByCombatant(int a, int b);                     // 0x00c0fa10
    float __thiscall GetSkill();                                            // 0x00c0b9c0
    void  __thiscall AddSkill(float delta);                                 // 0x00c0b9d0
    char  __thiscall HasTool();                                             // 0x00c0b780
    float __thiscall GetLuckRoll();                                         // 0x00c0e3a0
    char  __thiscall DoSpotCheck(int a, int b);                             // 0x00c25480
    void* __thiscall MakeEvent(void* a, void* b, void* c, int d, float e);  // 0x00c0bc00
};

// cTribe methods (ecx = tribe)
struct Tribe {
    int  __thiscall HotSpotGetClosest(void* pos);          // 0x00c8f040
    void __thiscall UpdateWater(float depth);              // 0x00c94b50
    char __thiscall WaterOkA();                            // 0x00c8e850
    char __thiscall WaterOkB();                            // 0x00c8e870
    void __thiscall FindSpot(int kind, int id);            // 0x00c98750
};

// cLocomotiveObject / cSpatialObject at creature+0xc0 (direct method)
struct Locomotive {
    char __thiscall IsNearGoal();                          // 0x00c42e20
};

// creature+0x34 sub-object
struct EngSub34 {
    void* __thiscall Handle();                             // 0x00cee330
    float __thiscall Radius();                             // 0x00cee380
};

struct EngLayout {                                         // ecx = layout manager
    char __thiscall LookupB(void* a, int b, int c);        // 0x00af0bd0
};

struct EngVec {                                            // ecx = temp from 0x00b3d2b0
    void __thiscall Add(float v, void* vec, int n);        // 0x00ac7ab0
    void __thiscall Add2(void* vec, void* a, int n);       // 0x00ac7d10
    void __thiscall Add3(int a, int* b);                   // 0x00ac7eb0
};

void* FUN_00b0d350();                                                          // 0x00b0d350
int   FUN_00d724f0(void* a);                                                   // 0x00d724f0
void  FUN_00da6270(void* a, int b);                                            // 0x00da6270
char  FUN_004232c0(float* a, void* b);                                         // 0x004232c0
float GetPropertyT_float(int owner, int key, float def);                       // 0x004e1c70
void  FUN_00c9af30(int spot, float* o1, void* o2, char* o3);                   // 0x00c9af30
void  FUN_00c9ae30(int spot, float delta);                                     // 0x00c9ae30
char  FUN_00c25480(int a, int b);                                              // 0x00c25480
void* FUN_00b3d2b0(float v, void* vec, int n);                                 // 0x00b3d2b0
void* FUN_00b3d2b0b(int v, int* vec);                                          // 0x00b3d2b0
void  FUN_00e398e0(float a, void* b);                                          // 0x00e398e0
void  FUN_00449c20(float* dst, float* src);                                    // 0x00449c20
char  FUN_00d727b0(void* a, void* b);                                          // 0x00d727b0
int   FUN_00d72770(void* a);                                                   // 0x00d72770
void  FUN_00d72720(void* a, int b);                                            // 0x00d72720
int   FUN_00dba630(void* a, int b);                                            // 0x00dba630
void* FUN_00af13b0(void* a, int b, int c);                                     // 0x00af13b0
void* FUN_00b3d350(void* a, void* b);                                          // 0x00b3d350
void  FUN_00b81630(void* a, void* b);                                          // 0x00b81630
void* FUN_00c94430_out(int a, int* out);                                       // 0x00c94430
void* FUN_00c94430_val(int a, int v);                                          // 0x00c94430
float FUN_00c420f0(void* a, float b, float c);                                 // 0x00c420f0

struct RLC {
    u32 __thiscall RandomUint32Uniform(int n);          // 0x00a68fb0
};

extern "C" double __cdecl sqrt(double);

// ------------------------------------------------------------------ globals

extern float DAT_01572070;    // 0x01572070
extern float DAT_0157206c;    // 0x0157206c
extern float DAT_01687a14;    // 0x01687a14
extern float DAT_01687a10;    // 0x01687a10
extern float DAT_0169eee0;    // 0x0169eee0
extern float DAT_0169eee4;    // 0x0169eee4
extern float DAT_0169eee8;    // 0x0169eee8
extern int   DAT_0169ef34;    // 0x0169ef34
extern int   DAT_0169ef38;    // 0x0169ef38
extern int   DAT_0169ef3c;    // 0x0169ef3c
extern int   DAT_0158128c;    // 0x0158128c
extern int   DAT_015841a8;    // 0x015841a8
extern int   DAT_015841ac;    // 0x015841ac
extern float DAT_01581298;    // 0x01581298
extern float DAT_0158129c;    // 0x0158129c
extern float DAT_015812a0;    // 0x015812a0
extern char  DAT_0167ec50;    // 0x0167ec50
extern char  cRandomGlobal;   // 0x01601760

// ------------------------------------------------------------------ behaviour

class cTribeGameBehaviorFish {
public:
    char mPad[0x2c];
    AgentDeque mAgentList;                          // +0x2c

    __declspec(noinline) int __thiscall Action();   // 0x00d74060
};

#define I32(p, o) (*(int*)((char*)(p) + (o)))
#define U32(p, o) (*(u32*)((char*)(p) + (o)))
#define F32(p, o) (*(float*)((char*)(p) + (o)))
#define B8(p, o)  (*(u8*)((char*)(p) + (o)))
#define I64(p, o) (*(i64*)((char*)(p) + (o)))
#define VTSLOT(p, off) ((*(void***)(p))[(off) / 4])

// virtual functor with 0 args
#define VC0(rt, p, off)          ((rt(__thiscall*)(void*))VTSLOT(p, off))((void*)(p))
// virtual functor with a single float arg
#define VCF(rt, p, off, a)       ((rt(__thiscall*)(void*, float))VTSLOT(p, off))((void*)(p), (float)(a))
// virtual functor with a single int arg
#define VCI(rt, p, off, a)       ((rt(__thiscall*)(void*, int))VTSLOT(p, off))((void*)(p), (int)(a))
// virtual functor (dir, float, float)
#define VC3(rt, p, off, d, a, b) ((rt(__thiscall*)(void*, void*, float, float))VTSLOT(p, off))((void*)(p), (void*)(d), (float)(a), (float)(b))

static float Bits(int b) { return *(float*)&b; }

#define CITIZEN   ((Eng*)pcVar4)
#define SPATIAL   ((void*)((char*)pcVar4 + 0xc0))
#define SUB34     ((EngSub34*)((char*)pcVar4 + 0x34))

// @ 0x00d74060  SP::cTribeGameBehaviorFish::Action
int cTribeGameBehaviorFish::Action()
{
    char* self = (char*)this;

    AgentIterator it(&mAgentList, AgentFilter(this, false));
    if (it.IsDone())
        return 1;

    i64 timeNow = ((TimeMgr*)GameTimeManager())->Time();
    I32(self, 0xa8) = (int)timeNow;
    I32(self, 0xac) = (int)(timeNow >> 32);

    if (it.IsDone())
        return 1;

    do {
        void* pAgentRaw = it.Get();
        if (pAgentRaw) {
            void* pcVar4 = ((AgentObj*)pAgentRaw)->Cast(0x4f176642);
            if (pcVar4) {
                float  pfS = 0.0f;
                float* pfStack_118 = 0;
                float  fStack_114 = 0.0f;
                int    vOut = 0;
                char   cOut = 0;
                int    bias = 0;
                u32    uVar6 = 0;
                void*  iv = 0;
                int*   pRec = 0;
                float  fDir[3] = { 0.0f, 0.0f, 0.0f };
                float  fPnt[3] = { 0.0f, 0.0f, 0.0f };
                float  fNeg[3] = { 0.0f, 0.0f, 0.0f };
                int    bufA[3] = { 0, 0, 0 };
                int    bufB[3] = { 0, 0, 0 };

                pfStack_118 = (float*)((char*)pcVar4 + 0x58);
                pRec = ((FishInfoMap*)(self + 0x74))->FindOrAdd((void**)&pfStack_118);
                pfStack_118 = (float*)(void*)CITIZEN->GetTribe();
                VC0(void, pfStack_118, 0xac);

                // per-record idle/tool timers
                if (pRec[0] == 0xc || pRec[0] == 10 || pRec[0] == 8) {
                    i64 last = I64(pRec, 0x10);
                    if ((double)last != 0.0) {
                        i64 dt = timeNow - last;
                        F32(pRec, 0x18) =
                            (float)((double)dt * (double)F32(pRec, 0x1c) * 0.001) + F32(pRec, 0x18);
                    }
                    I64(pRec, 0x10) = timeNow;
                }

                uVar6 = CITIZEN->HasSpecializedTool(8) ? 1u : 0u;
                if (CITIZEN->HasSpecializedTool(8))
                    fStack_114 = GetPropertyT_float(DAT_0158128c, (int)0xfceeb952u, 2.0f);
                else
                    fStack_114 = GetPropertyT_float(DAT_0158128c, (int)0xe4dd8a7cu, 1.0f);
                bias = CITIZEN->IsLeader() ? 0x20 : 0;

                switch (pRec[0]) {
                case 0: {
                    void* u = FUN_00b0d350();
                    if (FUN_00d724f0(u) == 0) {
                        FUN_00da6270(pcVar4, 1);
                        ((void(__thiscall*)(void*, AgentIterator))(*(void***)this)[0x11])(this, it);
                    } else if (CITIZEN->PutAwayToolExceptFor(8) == 0) {
                        if (CITIZEN->AnimationFinished(0)) {
                            iv = SUB34->Handle();
                            if (iv == 0) { pRec[0] = 6; B8(pRec, 0x29) = 0; }
                            else         { B8(pRec, 0x29) = 1; pRec[0] = 1; }
                        }
                    } else {
                        CITIZEN->SetToolOnAnimEvent(8);
                    }
                    break; }

                case 1: {
                    if (FUN_004232c0((float*)(self + 0xb0), &DAT_0169eee0) == 0) {
                        float d  = VC0(float, SPATIAL, 0x74) + 10.0f;
                        float d2 = VC0(float, SPATIAL, 0x74);
                        CITIZEN->MoveToPointAtSpeed(2, (float*)(self + 0xb0), d, d2 + d);
                        pRec[0] = 2;
                    } else {
                        FUN_00da6270(pcVar4, 1);
                        ((void(__thiscall*)(void*, AgentIterator))(*(void***)this)[0x11])(this, it);
                    }
                    break; }

                case 2:
                    if (((Locomotive*)SPATIAL)->IsNearGoal())
                        pRec[0] = 3;
                    break;

                case 3: {
                    if (FUN_004232c0((float*)(self + 0xb0), &DAT_0169eee0) != 0) {
                        FUN_00da6270(pcVar4, 1);
                        ((void(__thiscall*)(void*, AgentIterator))(*(void***)this)[0x11])(this, it);
                        break;
                    }
                    iv = FUN_00c94430_out((int)(size_t)(*(void**)(self + 0xc0)), &vOut);
                    iv = VCI(void*, SPATIAL, 0x2c, iv);
                    if (FUN_00d727b0((float*)(self + 0xb0), iv) == 0) {
                        FUN_00da6270(pcVar4, 1);
                        ((void(__thiscall*)(void*, AgentIterator))(*(void***)this)[0x11])(this, it);
                        break;
                    }
                    iv = FUN_00c94430_val((int)(size_t)(*(void**)(self + 0xc0)), vOut);
                    int* p = (int*)FUN_00d72770(iv);
                    pRec[1] = vOut;
                    fStack_114 = VC0(float, SPATIAL, 0x74);
                    {
                        float dx = F32(p, 4)  - F32(p, 0x10);
                        float dy = F32(p, 8)  - F32(p, 0x14);
                        float dz = F32(p, 0xc) - F32(p, 0x18);
                        float len = (float)sqrt((double)dx * dx
                                             + ((double)dy * dy + (double)dz * dz));
                        float inv = 1.0f / (len + 1.5258789e-05f);
                        float nx = dx * inv, ny = dy * inv, nz = dz * inv;
                        float t  = (fStack_114 - DAT_01572070) + len;
                        fPnt[0] = F32(p, 0x10) + nx * t;
                        fPnt[1] = F32(p, 0x14) + ny * t;
                        fPnt[2] = F32(p, 0x18) + nz * t;
                        FUN_00b3d350(fDir, fPnt);
                        FUN_00b81630(fDir, fPnt);
                        fNeg[0] = -nx; fNeg[1] = -ny; fNeg[2] = -nz;
                        CITIZEN->MoveToPointAndFacingAtSpeed(2, fDir, fNeg,
                                                            DAT_01572070, DAT_0157206c);
                    }
                    pRec[0] = 4;
                    break; }

                case 4:
                    if (((Locomotive*)SPATIAL)->IsNearGoal())
                        pRec[0] = 5;
                    break;

                case 5: {
                    if (!((Locomotive*)SPATIAL)->IsNearGoal())
                        break;
                    VC0(void, SPATIAL, 0xec);
                    int key = CITIZEN->AnimHandle();
                    void* slot = CITIZEN->FindSlotByKey(key, 0);
                    if (SUB34->Handle() == 0) {
                        void* r = FUN_00b3d2b0(0.0f, (char*)pcVar4 + 0x34, 3);
                        ((EngVec*)r)->Add(0.0f, (char*)pcVar4 + 0x34, 3);
                    }
                    if (B8(slot, 0x18) == 0) {
                        fDir[0] = Bits(DAT_0169ef34 ^ (int)0x80000000u);
                        fDir[1] = Bits(DAT_0169ef38 ^ (int)0x80000000u);
                        fDir[2] = Bits(DAT_0169ef3c ^ (int)0x80000000u);
                    } else {
                        fDir[0] = Bits(DAT_0169ef34);
                        fDir[1] = Bits(DAT_0169ef38);
                        fDir[2] = Bits(DAT_0169ef3c);
                    }
                    CITIZEN->SetToolTarget(fDir[0], fDir[1], fDir[2]);
                    iv = VCF(void*, SPATIAL, 0x2c, 40.0f);
                    int spot = ((Tribe*)pfStack_118)->HotSpotGetClosest(iv);
                    pRec[2] = spot; pRec[7] = 0; pRec[4] = 0; pRec[5] = 0;
                    if (spot != -1) {
                        int gpkey = CITIZEN->HasSpecializedTool(8)
                                        ? (int)0x5f956f3cu : (int)0x1c079d85u;
                        pRec[7] = (int)GetPropertyT_float(DAT_0158128c, gpkey, 0.07f);
                    }
                    pRec[0] = (B8(pRec, 0x29) == 0) * 2 + 6;
                    break; }

                case 6: {
                    if (CITIZEN->HasSpecializedTool(8)) {
                        int eff = CITIZEN->GetToolEffect(8);
                        if (CITIZEN->ToolIndex() != eff)
                            CITIZEN->InterruptAnimation(0x2c39200, CITIZEN->AnimHandle(), 0);
                    }
                    pRec[0] = 7;
                    break; }

                case 7: {
                    if (CITIZEN->PutAwayToolExceptFor(8) == 0)
                        pRec[0] = (B8(pRec, 0x29) != 0 ? 7 : 0) + 1;
                    else
                        CITIZEN->SetToolOnAnimEvent(8);
                    break; }

                case 8: {
                    int h = CITIZEN->AnimHandle();
                    pRec[9] = CITIZEN->PlayAnimation((int)uVar6 + 0x2c39210 + bias, 1, h);
                    pRec[0] = 9;
                    break; }

                case 9: {
                    if (!CITIZEN->AnimationFinished(pRec[9]))
                        break;
                    float a = GetPropertyT_float(DAT_0158128c, (int)0x69943cd, 1.2f);
                    float b = GetPropertyT_float(DAT_0158128c, (int)0xbca45f07u, 3.9f);
                    F32(self, 0xa0) = FUN_00c420f0(&DAT_0167ec50, a, b);
                    int h = CITIZEN->AnimHandle();
                    pRec[9] = CITIZEN->PlayAnimation((int)uVar6 + 0x2c39215 + bias, 1, h);
                    pRec[0] = 10;
                    break; }

                case 10: {
                    if (!(F32(self, 0xa0) < CITIZEN->GetLuckRoll()))
                        break;
                    int h = CITIZEN->AnimHandle();
                    pRec[9] = CITIZEN->PlayAnimation((int)uVar6 + 0x2c3921a + bias, 1, h);
                    pfS = 0.0f;
                    FUN_00c9af30(pRec[2], &pfS, fDir, &cOut);
                    if (F32(pRec, 0x18) <= 1.0f || pfS <= fStack_114 || cOut != 0) {
                        int h2 = CITIZEN->AnimHandle();
                        pRec[9] = CITIZEN->PlayAnimation(bias + 0x2c39223, 0, h2);
                        pRec[0] = 0xd;
                    } else {
                        FUN_00c9ae30(pRec[2], -fStack_114);
                        F32(pRec, 0x18) = F32(pRec, 0x18) - fStack_114;
                        pRec[0] = 0xb;
                    }
                    break; }

                case 0xb: {
                    vOut = -1;
                    if (!CITIZEN->WaitForAnimEventOrEnd(DAT_015841a8, &vOut, 0, pRec[9], 1))
                        break;
                    CITIZEN->SetCurrentToolEffect(CITIZEN->HasTool() ? 5 : 6, -1);
                    u32 rnd = ((RLC*)&cRandomGlobal)->RandomUint32Uniform(3);
                    int h = CITIZEN->AnimHandle();
                    CITIZEN->PlayAnimation((int)rnd + 0x2c39220 + bias, 1, h);
                    int ti = CITIZEN->ToolIndex();
                    int h2 = CITIZEN->AnimHandle();
                    int id = (ti == 4) ? 0x2c39225 : (bias + 0x2c39224);
                    pRec[9] = CITIZEN->PlayAnimation(id, 0, h2);
                    pRec[0] = 0xc;
                    break; }

                case 0xc: {
                    vOut = -1;
                    if (!CITIZEN->WaitForAnimEventOrEnd(DAT_015841ac, &vOut, 0, pRec[9], 1))
                        break;
                    SUB34->Handle();
                    fStack_114 = SUB34->Radius() + fStack_114;
                    {
                        float lim = VCI(float, (char*)pcVar4 + 0x34, 0x38, 3);
                        if (lim < fStack_114)
                            fStack_114 = lim;
                    }
                    {
                        float d = SUB34->Radius();
                        if (0.0f < fStack_114 - d) {
                            float dd = fStack_114 - d;
                            void* r = FUN_00b3d2b0(dd, (char*)pcVar4 + 0x34, 3);
                            ((EngVec*)r)->Add(dd, (char*)pcVar4 + 0x34, 3);
                        }
                    }
                    B8(self, 0x99) = 1;
                    if (CITIZEN->HasSpecializedTool(8) == 0) {
                        CITIZEN->SetCurrentToolEffect(0, -1);
                        pRec[0] = 0xd;
                    } else {
                        CITIZEN->SetCurrentToolEffect(4, -1);
                        pRec[0] = 0xd;
                    }
                    break; }

                case 0xd: {
                    if (!CITIZEN->AnimationFinished(pRec[9]))
                        break;
                    if (!(CITIZEN->GetSkill() >= DAT_01687a14))
                        break;
                    char ok = 1;
                    if (B8(pRec, 0x28) != 0) {
                        void* lm = FUN_00af13b0(pcVar4, 5, 0);
                        ok = ((EngLayout*)lm)->LookupB(pcVar4, 5, 0);
                    }
                    cOut = 0;
                    pfS = 0.0f;
                    FUN_00c9af30(pRec[2], &pfS, fDir, &cOut);
                    if (cOut != 1) {
                        float a = SUB34->Radius();
                        float b = VCI(float, (char*)pcVar4 + 0x34, 0x38, 3);
                        if (b > a && ok) {
                            pRec[0] = 8;
                            break;
                        }
                    }
                    pRec[0] = 0xe;
                    break; }

                case 0xe: {
                    iv = SUB34->Handle();
                    if (iv == 0 || F32(iv, 0x134) == 0.0f) {
                        FUN_00da6270(pcVar4, 1);
                        ((void(__thiscall*)(void*, AgentIterator))(*(void***)this)[0x11])(this, it);
                        break;
                    }
                    {
                        float* p1 = (float*)VC0(void*, SPATIAL, 0x2c);
                        float* p2 = (float*)VC0(void*, (char*)iv + 0x34, 0x2c);
                        fDir[0] = p2[0] - p1[0];
                        fDir[1] = p2[1] - p1[1];
                        fDir[2] = p2[2] - p1[2];
                        FUN_00449c20(fPnt, fDir);
                        void* u = VC3(void*, SPATIAL, 0x2c, fPnt, DAT_01572070, DAT_0157206c);
                        CITIZEN->MoveToPointAndFacingAtSpeed(2, u, fPnt, DAT_01572070, DAT_0157206c);
                    }
                    pRec[0] = 0xf;
                    break; }

                case 0xf: {
                    if (*(void**)((char*)pcVar4 + 0xfc8) == *(void**)((char*)pcVar4 + 0xfc4)) {
                        if (CITIZEN->DoSpotCheck(0, 0) == 0)
                            break;
                    }
                    if (!((Locomotive*)SPATIAL)->IsNearGoal())
                        break;
                    iv = SUB34->Handle();
                    pRec[9] = CITIZEN->PlayAnimationWithTarget(
                                  0x2796b30,
                                  iv ? (int)((char*)iv + 0x34) : 0,
                                  -1,
                                  (int)(size_t)(*(void**)((char*)pcVar4 + 0xfc8)));
                    pRec[0] = 0x10;
                    break; }

                case 0x10: {
                    vOut = -1;
                    if (!CITIZEN->WaitForAnimEventOrEnd(DAT_015841a8, &vOut, 0x2796b30, pRec[9], 1))
                        break;
                    CITIZEN->SetToolFacing(DAT_0169eee0, DAT_0169eee4, DAT_0169eee8);
                    iv = SUB34->Handle();
                    CITIZEN->SetToolArg(1);
                    CITIZEN->PerformSocialAction((int)(size_t)iv, -1);
                    pRec[0] = 0x11;
                    break; }

                case 0x11: {
                    if (!CITIZEN->AnimationFinished2(pRec[9]))
                        break;
                    FUN_00d72720(*(void**)(self + 0xc0), pRec[1]);
                    pRec[1] = -1;
                    iv = SUB34->Handle();
                    if (iv == 0) {
                        FUN_00da6270(pcVar4, 1);
                        ((void(__thiscall*)(void*, AgentIterator))(*(void***)this)[0x11])(this, it);
                    } else {
                        pRec[0] = 0x12;
                    }
                    break; }

                case 0x12: {
                    int r = FUN_00dba630(pcVar4, 0xd);
                    pRec[8] = r;
                    if (r != -1)
                        pRec[0] = 0x13;
                    break; }

                case 0x13: {
                    if (!((Locomotive*)SPATIAL)->IsNearGoal())
                        break;
                    iv = SUB34->Handle();
                    if (iv == 0) {
                        FUN_00da6270(pcVar4, 1);
                        ((void(__thiscall*)(void*, AgentIterator))(*(void***)this)[0x11])(this, it);
                        break;
                    }
                    void* target = *(void**)((char*)pcVar4 + 0xfc8);
                    void* slot = CITIZEN->FindSlotByCombatant((int)((char*)iv + 0x34), 0);
                    if (slot)
                        target = *(void**)slot;
                    void* at = *(void**)((char*)pfStack_118 + 0x260);
                    at = at ? (char*)at + 0x34 : 0;
                    pRec[9] = CITIZEN->InterruptAnimationWithTarget(
                                  0x4ffb325, (int)(size_t)at, -1, (int)(size_t)target);
                    pRec[0] = 0x14;
                    break; }

                case 0x14: {
                    vOut = -1;
                    if (!CITIZEN->WaitForAnimEventOrEnd(DAT_015841a8, &vOut, 0x4ffb325, pRec[9], 1))
                        break;
                    pfS = 0.0f;
                    iv = SUB34->Handle();
                    if (iv != 0) {
                        if (VC0(char, (char*)pfStack_118 + 0x120, 0x58)) {
                            int m = I32(iv, 0x12c);
                            if (m == 0 || m == 3) {
                                pfS = Bits((int)0xb4784a89u);
                                if (((Tribe*)pfStack_118)->WaterOkA()) {
                                    if (!((Tribe*)pfStack_118)->WaterOkB())
                                        pfS = Bits((int)0x45f966abu);
                                }
                                void* ev = CITIZEN->MakeEvent(
                                    bufA, bufB,
                                    *(void**)((char*)pfStack_118 + 0x234),
                                    0, (float)(i64)F32(iv, 0x134));
                                FUN_00e398e0(pfS, ev);
                            }
                            ((Tribe*)pfStack_118)->UpdateWater(F32(iv, 0x134));
                            F32(self, 0x94) = F32(self, 0x94) + F32(iv, 0x134);
                            void* r = FUN_00b3d2b0b((int)(size_t)iv,
                                                    (int*)((char*)pfStack_118 + 0x20c));
                            ((EngVec*)r)->Add3((int)(size_t)iv,
                                               (int*)((char*)pfStack_118 + 0x20c));
                        }
                    }
                    if (pRec[8] >= 0)
                        ((Tribe*)pfStack_118)->FindSpot(0xd, pRec[8]);
                    cOut = 0;
                    pfS = 0.0f;
                    FUN_00c9af30(pRec[2], &pfS, fDir, &cOut);
                    if (cOut != 0) {
                        FUN_00da6270(pcVar4, 1);
                        ((void(__thiscall*)(void*, AgentIterator))(*(void***)this)[0x11])(this, it);
                        break;
                    }
                    if (!VC0(char, SPATIAL, 0x58)) {
                        FUN_00da6270(pcVar4, 1);
                        ((void(__thiscall*)(void*, AgentIterator))(*(void***)this)[0x11])(this, it);
                        break;
                    }
                    if (B8(pRec, 0x28) != 0) {
                        void* lm = FUN_00af13b0(pcVar4, 5, 0);
                        if (((EngLayout*)lm)->LookupB(pcVar4, 5, 0) == 0) {
                            FUN_00da6270(pcVar4, 1);
                            ((void(__thiscall*)(void*, AgentIterator))(*(void***)this)[0x11])(this, it);
                            break;
                        }
                    }
                    pRec[0] = 0;
                    break; }

                case 0x15: {
                    if (!(CITIZEN->GetSkill() <= DAT_01687a14))
                        goto CASE15_SPOT;
                    if (!(0.01f < SUB34->Radius()))
                        goto CASE15_SPOT;
                    iv = SUB34->Handle();
                    if (iv == 0) {
                        CITIZEN->InterruptAnimation(0x2796b31, CITIZEN->AnimHandle(), 0);
                    } else {
                        CITIZEN->InterruptAnimationWithTarget(
                            0x2796b31, (int)((char*)iv + 0x34), -1, CITIZEN->AnimHandle());
                    }
                    pRec[0] = 0x16;
                    break;
                CASE15_SPOT:
                    cOut = 0;
                    pfS = 0.0f;
                    FUN_00c9af30(pRec[2], &pfS, fDir, &cOut);
                    if (CITIZEN->GetSkill() < DAT_01687a10 || cOut != 0) {
                        pRec[0] = 0xe;
                    } else {
                        pRec[0] = 6;
                        B8(pRec, 0x29) = 1;
                    }
                    break; }

                case 0x16: {
                    vOut = -1;
                    if (!CITIZEN->WaitForAnimEventOrEnd(DAT_015841a8, &vOut, -1, 0, 1))
                        break;
                    {
                        float a = SUB34->Radius();
                        float b = DAT_01581298;
                        float m = (b <= a) ? b : a;
                        void* r = FUN_00b3d2b0(m, (char*)pcVar4 + 0x34, 0);
                        ((EngVec*)r)->Add2((char*)pcVar4 + 0x34, 0, 3);
                    }
                    if (SUB34->Handle() == 0) {
                        void* r = FUN_00b3d2b0(0.0f, (char*)pcVar4 + 0x34, 3);
                        ((EngVec*)r)->Add(0.0f, (char*)pcVar4 + 0x34, 3);
                    }
                    CITIZEN->SetCurrentToolEffect(CITIZEN->HasTool() ? 8 : 10, -1);
                    pRec[0] = 0x18;
                    break; }

                case 0x18: {
                    if (!CITIZEN->AnimationFinished(0))
                        break;
                    pRec[0] = 0x19;
                    CITIZEN->PlayAnimation(0x2796b38, 1, CITIZEN->AnimHandle());
                    break; }

                case 0x19: {
                    if (!CITIZEN->AnimationFinished(0))
                        break;
                    CITIZEN->AddSkill(DAT_0158129c * DAT_01581298 + CITIZEN->GetSkill());
                    ((EngSub34*)((char*)pcVar4 + 0x5a8))->Radius();
                    F32(self, 0x94) = DAT_015812a0 * DAT_01581298;
                    pRec[0] = 0x15;
                    CITIZEN->SetCurrentToolEffect(0, -1);
                    break; }
                }
            }
        }
        it.Next();
    } while (!it.IsDone());

    return 1;
}