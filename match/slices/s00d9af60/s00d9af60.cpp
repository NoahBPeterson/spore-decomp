// Slice s00d9af60 -- creature/social behaviour region (25 functions, 0x00d9af60-0x00d9bc70).
// Continuation of the object file of slice s00d99ff0 (0x00d99ff0-0x00d9af20):
// the SOCIAL_PROPOSE / SOCIAL_GOAL order drivers, the social-progress widget helpers and the
// creature-pointer ordering helpers (insertion sort, heap sift, min-of-three).
//
// Layout notes (retail): the social-progress sub-object sits at creature-display-strategy + 0x18
// and its widget pointer is at +0x20 (which is display-strategy + 0x38).  Compared with the 2008
// PDB, mFillRate/mDrainAmount live at +0x04/+0x08, the two state bytes at +0x0c/+0x0d, the timer
// flag at +0x14 and the two cached creature anim-handles at +0x18/+0x1c.
//
// Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

typedef unsigned int uint;

struct Vec3 { float x, y, z; };

struct Creature;                       // cSPCreatureBase / cSPCreatureCitizen
struct Loco;                           // cLocomotiveObject, addressed as creature + 0xc0

// ------------------------------------------------------------------ helpers
// nSPBehaviorTree::behavior_stimuli node returned by Play.
struct AnimHandle {
    char  pad0[0xc];
    int   mState;         // +0xc
    int   mId;            // +0x10
    int   mKind;          // +0x14
    float mValue;         // +0x18
    int   mExtra;         // +0x1c
};

// nSPBehaviorTree::behavior_stimuli at behaviour-tree-data + 8.
struct BehaviorStimuli {
    AnimHandle* Play(uint flags, uint a);                 // 0x00bc96a0 (ret 8)
    void        ClearAll(uint flags, uint a);             // 0x00bc98f0 (ret 8)
    void        SetStimulus(uint flags, uint a, float f);// 0x00bc97f0 (ret 0x10)
    void*       GetAny();                                 // 0x00d997e0 (ret)
};

// Creature behaviour-tree data at creature+0xb4c.
struct GoalTableEntry {               // at behaviour-tree-data + 0x1d0
    char pad0[8];
    int  mKey;                        // +0x08 (== 0x546e8804 when the table is live)
    int  mIndex;                      // +0x0c
};
struct BehaviorTreeData {
    char            pad0[0x8];
    BehaviorStimuli mStimuli;    // +0x08
    char            pad8[0x164 - 0x09];
    char            mTable[1];    // +0x164 (stride-0xac entries, field 0 read by 0x00d9b480)
    char            pad164[0x1d0 - 0x165];
    GoalTableEntry  mGoalTable;   // +0x1d0
};

// --------------------------------------------------------------- manager
struct BehaviorMgr;                       // cAgentOrderManager singleton
BehaviorMgr* FUN_00bc9b00();              // 0x00bc9b00 (0-arg getter)

struct BehaviorMgr {
    AnimHandle* FindNode(uint type, void* fn, void* blk);                          // 0x00bca620 (ret 0xc)
    AnimHandle* AddOrder(uint type, uint size, uint nounId, const char* name);     // 0x00bcb0b0 (ret 0x10)
    void        SetNode(AnimHandle* st, void* creature, void* res, void* fn);      // 0x00bcb480 (ret 0x10)
    void        Activate(int a, int b, void* c, float f, void* d, void* e);        // 0x00bca810 (ret 0x18)
    int         FindSlot(int a, int b, int c, int d);                              // 0x00bca0c0 (ret 0x10)
    Creature*   At(int idx);                                                       // 0x00bc9b10 (ret; [ecx+0x14]+idx)
    bool        IsEmpty();                                                         // 0x00bc9b50 (ret)
    char        pad0[0x1a4];
    int         mKey1a4;                                                           // +0x1a4
    int         mKey1a8;                                                           // +0x1a8
};

// ------------------------------------------------------------- creature
// Only the members the slice touches are named; retail offsets are used.
struct Creature {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s0a(); virtual void s0b();
    virtual void s0c(); virtual void s0d(); virtual void s0e(); virtual void s0f();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13();
    virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
    virtual void s18(); virtual void s19(); virtual void s1a(); virtual void s1b();
    virtual void s1c(); virtual void s1d(); virtual void s1e(); virtual void s1f();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual void s28(); virtual void s29(); virtual void s2a(); virtual void s2b();
    virtual void s2c(); virtual void s2d(); virtual void s2e(); virtual void s2f();
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33();
    virtual void s34(); virtual void s35(); virtual void s36(); virtual void s37();
    virtual void s38(); virtual void s39(); virtual void s3a(); virtual void s3b();
    virtual void s3c(); virtual void s3d(); virtual void s3e(); virtual void s3f();
    virtual void s40();
    virtual void SetTarget(void* o, int a, int b);        // +0x84 (slot 0x84/4)
    virtual void* QueryObj(uint id);                      // +0x18c (slot 0x18c/4)
    char   pad4[0xc - 4];
    float  mX;                                            // +0x0c (compared by 0x00d9b4e0)
    char   pad10[0x34 - 0x10];
    int    mSub34;                                        // +0x34 (agent-order node key)
    char   pad38[0x1a4 - 0x38];
    int    mOrderKey1a4;                                  // +0x1a4
    int    mOrderKey1a8;                                  // +0x1a8 (compared by 0x00d9b2d0)
    char   pad1ac[0xb20 - 0x1ac];
    void*  mpAux;                                         // +0xb20
    char   padb24[0xb28 - 0xb24];
    char   mGroupData[0x20];                              // +0xb28
    BehaviorMgr* mpAgentOrders;                           // +0xb48
    BehaviorTreeData* mpBehaviorTreeData;                 // +0xb4c
    char   padb50[0xb54 - 0xb50];
    int    mpAnimating;                                   // +0xb54 (cAnimatingCreature*)
    uint   mFlagsB58;                                     // +0xb58

    Loco*  GetLoco();                                     // this + 0xc0
    uint   GetNounID();                                   // virtual +0x20
    int    GetSocialGoal();                               // 0x00c0e6a0
    int    GetTribe();                                    // 0x00c22f50 (citizen)
    bool   IsLeader();                                    // 0x00c232d0 (citizen)
    bool   IsAnimFinished(void* h);                       // 0x00c12400 (ret 0x1c)
    uint   InterruptAnim(uint a, int b, int c);           // 0x00c12310
    void   FUN_00c14750(bool v);                          // 0x00c14750
    int    FUN_00c0c1a0();                                // 0x00c0c1a0
};

struct Loco {
    char pad0[0xc0];
};

// Creature* query helpers
bool  Anim_QueryB(Creature* c, int id);                   // 0x00a02b70 (cAnimatingCreature::QueryB, [c+0xb54])
typedef bool (__thiscall *AnimGetProgressFn)(int self, int id, float* a, float* b); // virtual [anim+0x5c]

// call the animating-creature virtual at [*mpAnimating + 0x5c]
static bool Anim_GetProgress(Creature* c, int id, float* a, float* b)
{
    void* anim = (void*)c->mpAnimating;
    AnimGetProgressFn fn = *(AnimGetProgressFn*)(*(char**)anim + 0x5c);
    return fn((int)anim, id, a, b);
}

// -------------------------------------------------- social-progress class
struct cSPUISocialRainbow {
    void StartFill(int side, int seg, float minRate, float rate, float frac, uint color, int p); // 0x00e33ab0 (ret 0x1c)
};

// the widget's guarded getters (ecx = widget)
struct SocialWidget {
    bool  Check0(int a, int b);              // 0x00e31aa0 (ret 8)
    bool  IsBusy();                          // 0x00e31a90 (ret)
    float Get(int a);                        // 0x00e31a30 (ret 4)
    void  Set(int a, float f);               // 0x00e319d0 (ret 8)
    void  Fade(int a, float f, float g);     // 0x00e32460 (ret 0xc)
    void  Clear(int a);                      // 0x00e324f0 (ret 4)
    void  Reset();                           // 0x00e31c90 (ret)
    void  SetNode(int a);                    // 0x00e31cb0 (ret 4)
};

struct SocialValues {
    float mTotal;                       // +0x00
    float mFillRate;                    // +0x04
    float mDrainAmount;                 // +0x08
    bool  mbDrain;                      // +0x0c
    bool  mbFailed;                     // +0x0d
    char  pad0e[6];
    bool  mbTimerRunning;               // +0x14
    char  pad15[3];
    int   mHandle0;                     // +0x18 (behaviour node / anim handle)
    int   mHandle1;                     // +0x1c
    SocialWidget* mpWidget;             // +0x20 (cSPUISocialRainbow-ish UI object)

    bool  AnyActive();                                             // 0x00d9b010 (thiscall)
    void  SetDrainDelay(bool v);                                  // 0x00d9b040
    void  StartFillRight(float rate, float d);                     // 0x00d9b090
    void  StartFillLeft(float rate, float d);                      // 0x00d9b0d0
    void  Update(int a0, int a1, Creature* c0, Creature* c1);     // 0x00d9ba60 (thiscall, ret 0x10)
};

// --------------------------------------------------- creature display strat
struct cCreatureDisplayStrategy {
    char   pad00[0x14];
    int    mGoal14;               // +0x14 (== SocialValues.mHandle kind to match)
    int    mUnk18;                // +0x18
    int    mUnk1c;                // +0x1c
    char   pad20[0x24 - 0x20];
    char   mb24;                  // +0x24
    char   mb25;                  // +0x25
    char   pad26[0x38 - 0x26];
    SocialWidget* mpWidget38;     // +0x38 (same widget as SocialValues.mpWidget)
    char   mb40;                  // +0x40
    char   pad41[0x58 - 0x41];
    uint   mFlags58;              // +0x58

    int    Drain(Creature* c);    // 0x00d9b110 (thiscall, ret 4)
};

// ---------------------------------------------------- SOCIAL_PROPOSE block
struct SocialProposeBlock {
    int    mState;                                       // +0x00
    void*  mpTarget;                                     // +0x04
    char   pad8[0x34 - 0x8];
    int    mAux34;                                       // +0x34
    SocialWidget* mpWidget;                              // +0x38
    bool   mbAddAsPosse;                                 // +0x40
    char   pad44[0x58 - 0x44];
    uint   mFlags58;                                     // +0x58

    int RewardPlayer(Creature* c, uint param);           // 0x00d9bc70 (ret 8)
};

// ------------------------------------------------------------- globals
void*  SP_NounManager();                                  // 0x00b3d300
void*  NounMgr_GetAvatar(void* mgr);                      // 0x00b1fdb0
void*  SP_GetCurrentGameMode();                           // 0x00b5b800 (returns &DAT_01654c10)
void*  SP_MessageServer();                                // 0x00b5b800-ish; see 0x00da6270 family
void*  EA_Audio_GetSystemAT();                            // 0x00a206f0
void   FUN_00d39360(uint a, void* b);                     // 0x00d39360
void*  FUN_00d37cb0();                                    // 0x00d37cb0
void   FUN_00f1d430(Creature* c);                         // 0x00f1d430
void   FUN_00c77bf0(int a);                               // 0x00c77bf0
void   FUN_00c756a0(float f, int a);                      // 0x00c756a0
void*  Terrain_GetSphere();                               // 0x00f67d90 (ecx = NounManager())
void   SetGlobalProperty(uint key, float v);              // 0x005ca880
void   NotifyEvent(float f);                              // 0x00d2e8a0
void   NotifyEventFull(float f, int a);                   // 0x00d2e8a0 (2-arg form)
int    FUN_00d998d0(int handle, uint key);                // 0x00d998d0
int    FUN_00d99500(void* p);                             // 0x00d99500
int    FUN_00d994c0(void* p);                             // 0x00d994c0
void*  FUN_00d999d0(int handle);                          // 0x00d999d0 (WatchMemoryBlock)
void   FUN_00da6270(Creature* c, int state);              // 0x00da6270
void*  FUN_00b3d2b0(int a, void* b);                      // 0x00b3d2b0 (ret 8)
void   FUN_00ac7de0(void* p);                             // 0x00ac7de0 (thiscall)
void   GetAny_00d997e0(void* p);                          // 0x00d997e0
float  FUN_00c03440(int a);                               // 0x00c03440
float  FUN_00c04140(int a);                               // 0x00c04140
int    FUN_00c0c160();                                    // 0x00c0c160 (avatar/player accessor)
void*  FUN_00b3d4c0(void* a, void* b, void* c);           // 0x00b3d4c0 (ret)
AnimHandle* FUN_00ba3f90(void* a, void* b, void* c);      // 0x00ba3f90 (ret 0xc)
void        FUN_00ba48b0(void* a, void* b, void* c);      // 0x00ba48b0 (ret 0xc)

// the (thiscall, ret 8) comparator on the loco sub-objects of two creature pointers
bool LocoLess(Loco* a, Loco* b);                          // 0x00ac0730

// The ordering helpers take the comparator as a hidden stack argument; the callers in this object
// file always pass the same one, so it is modelled directly.
typedef bool (*CmpFn)(Loco*, Loco*);
bool LocoLessStack(Loco* a, Loco* b);                     // 0x00ac0730

extern "C" {
extern float g_f0p5;          // 0x01471064 (0.5f)
extern float g_f1;            // 0x01485720 (1.0f)
extern float g_f0;            // 0x01485378 (0.0f)
extern float g_f5;            // 0x01486110 (5.0f)
extern float g_f2;            // 0x01582f24 (2.0f)
extern float g_f0p1;          // 0x01582f1c (0.1f)
extern float g_fltMax;        // 0x0147c190 (FLT_MAX)
extern char  kWildAnimalSocial[];   // 0x0147c198
extern char  kGiftInField[];        // 0x0147c1ac
extern void* g_p016c7aa4;           // 0x016c7aa4
extern void* g_p0169e294;           // 0x0169e294
}

// =================================================================== code

// @ 0x00d9af60
bool FUN_00d9af60(Creature* self, void* param2, uint* out)
{
    AnimHandle* h = self->mpBehaviorTreeData->mStimuli.Play(0x10000, 0);
    int r = (int)FUN_00d999d0((int)h);
    if (r == 0) return false;
    typedef void (__thiscall *LocoFn)(void*);
    void* loco = (void*)((char*)self + 0xc0);
    ((LocoFn)(*(void***)loco)[0xec / 4])(loco);
    typedef void (__thiscall *SetTargetFn)(Creature*, void*, int, int);
    ((SetTargetFn)(*(void***)self)[0x84 / 4])(self, (void*)(r + 0x5a8), 1, 0);
    uint v = (uint)self->InterruptAnim(0x6496897, -1, 0);
    *out = v;
    (void)param2;
    return true;
}

// @ 0x00d9afe0
void FUN_00d9afe0(Creature* self)
{
    self->mpBehaviorTreeData->mStimuli.ClearAll(0x10000, 0);
    typedef void (__thiscall *SetTargetFn)(Creature*, void*, int, int);
    ((SetTargetFn)(*(void***)self)[0x84 / 4])(self, 0, 0, 0);
}

// @ 0x00d9b010
bool SocialValues::AnyActive()
{
    return mpWidget->Check0(1, 1) || mpWidget->Check0(0, 1);
}

// @ 0x00d9b040
void SocialValues::SetDrainDelay(bool v)
{
    mbTimerRunning = v;
    mpWidget->Fade(1, 0.5f, 0.0f);
    mpWidget->Fade(0, 0.5f, 0.0f);
}

// @ 0x00d9b090
void SocialValues::StartFillRight(float rate, float d)
{
    float r = rate / mTotal;
    ((cSPUISocialRainbow*)mpWidget)->StartFill(0, 1, 0.0f, 0.0f, r, 0xff7bcc76, 1);
    mHandle0 = *(int*)&d;
}

// @ 0x00d9b0d0
void SocialValues::StartFillLeft(float rate, float d)
{
    float r = rate / mTotal;
    ((cSPUISocialRainbow*)mpWidget)->StartFill(1, 1, 0.0f, 0.0f, r, 0xff7bcc76, 1);
    mHandle1 = *(int*)&d;
}

// @ 0x00d9b110
int cCreatureDisplayStrategy::Drain(Creature* c)
{
    cCreatureDisplayStrategy* self = this;
    AnimHandle* h = c->mpBehaviorTreeData->mStimuli.Play(0x10000000, 0);
    if (h == 0) return -1;
    int st = h->mState;
    if (st == 2) {
        if (h->mKind == self->mGoal14) {
            self->mFlags58 |= 0xc;
        } else {
            self->mFlags58 = (self->mFlags58 & ~8u) | 4u;
        }
    } else if (st == 1) {
        self->mb40 = 0;
        if (self->mFlags58 & 1) {
            self->mpWidget38->Clear(0);
            self->mb24 = 0;
            self->mb25 = 0;
        }
        int slot = c->mpAgentOrders->FindSlot(2, 1, 0, 0);
        float f = h->mValue;
        if (slot != -1) f = g_f2 * f;
        SocialValues* vals = (SocialValues*)((char*)self + 0x18);
        if (h->mKind == self->mGoal14) {
            vals->StartFillLeft(f, (float)h->mExtra);
        } else {
            vals->StartFillLeft(g_f0p1 * h->mValue, (float)h->mExtra);
        }
        self->mFlags58 |= 2;
    }
    c->mpBehaviorTreeData->mStimuli.ClearAll(0x10000000, 0);
    return st;
}

// @ 0x00d9b230
void __stdcall FUN_00d9b230(Creature* self, char* list, uint param)
{
    char* elem = list + 0x24;
    for (uint i = 0; i < *(uint*)(list + 0x18); ++i) {
        Creature* pc = *(Creature**)elem;
        if (pc != 0 && pc != self && *(char*)(elem - 4) != 0) {
            pc->mpBehaviorTreeData->mStimuli.SetStimulus(0x10000000, 0, g_f5);
            AnimHandle* h = pc->mpBehaviorTreeData->mStimuli.Play(0x10000000, 0);
            h->mState = 3;
            h->mId = param;
        }
        elem += 0xc;
    }
}

// @ 0x00d9b2d0
bool FUN_00d9b2d0(BehaviorMgr* mgr, int* pair)
{
    Creature* c0 = *(Creature**)pair;
    Creature* got = mgr->At(0);
    int t1 = got->GetTribe();
    int t2 = c0->GetTribe();
    if (t2 == t1) return pair[1] == mgr->mKey1a8;
    return false;
}

// @ 0x00d9b320
float FUN_00d9b320(Creature* self, int a, int b, int c, int d, void* stimuli, char* outFlag)
{
    AnimHandle* h = self->mpBehaviorTreeData->mStimuli.Play(0, 0x200);
    if (h == 0) return 0.0f;
    int f = FUN_00d998d0((int)h, 0x4ffcdeda);
    if (f == 0) return 0.0f;
    void* v = FUN_00b3d2b0(f, &self->mSub34);
    FUN_00ac7de0(v);
    if (stimuli) GetAny_00d997e0(stimuli);
    *(int*)((char*)stimuli + 8) = f;
    *(int*)((char*)stimuli + 0x18) = h->mState;
    *outFlag = 1;
    (void)a;(void)b;(void)c;(void)d;
    return 1.0f;
}

// @ 0x00d9b3a0
bool FUN_00d9b3a0(Creature* self)
{
    AnimHandle* h = self->mpBehaviorTreeData->mStimuli.Play(0x8000000, 0);
    if (h == 0) { FUN_00da6270(self, 0x14); return false; }
    int r = FUN_00d99500(FUN_00d999d0((int)h));
    if (r == 0) { FUN_00da6270(self, 0x14); return false; }
    int blk[2];
    blk[0] = (int)self; blk[1] = r;
    BehaviorMgr* mgr = FUN_00bc9b00();
    AnimHandle* node = mgr->FindNode(0x668e405, (void*)&FUN_00d9b2d0, blk);
    if (node == 0) {
        node = mgr->AddOrder(0x668e405, 0x20, 0x18eb4b7, kWildAnimalSocial);
        *(void**)((char*)node + 0x224) = (void*)0xdb4a20;
        *(int*)((char*)node + 0x1a4) = 0;
        *(int*)((char*)node + 0x1ac) = 0;
        *(int*)((char*)node + 0x1a8) = r;
    }
    mgr->SetNode(node, self, 0, 0);
    return true;
}

// @ 0x00d9b480
bool FUN_00d9b480(Creature* a, Creature* b)
{
    BehaviorTreeData* ta = a->mpBehaviorTreeData;
    BehaviorTreeData* tb = b->mpBehaviorTreeData;
    GoalTableEntry* ga = &ta->mGoalTable;
    GoalTableEntry* gb = &tb->mGoalTable;
    if (ga->mKey != 0x546e8804 || gb->mKey != 0x546e8804) return false;
    int ia = ga->mIndex;
    int ib = gb->mIndex;
    int va = *(int*)((char*)ta + 0x164 + ia * 0xac);
    int vb = *(int*)((char*)tb + 0x164 + ib * 0xac);
    return va < vb;
}

// @ 0x00d9b4e0
int FUN_00d9b4e0(Creature** a, Creature** b)
{
    Creature* ca = a[0];
    Creature* cb = b[0];
    float fa = ca->mX;
    float fb = cb->mX;
    if (fb > fa) return -1;
    if (fa > fb) return 1;
    return 0;
}

// @ 0x00d9b510
void FUN_00d9b510(Creature* self, int a, int b, int c2, int d, void* flag)
{
    if (self->IsLeader() && *(char*)((char*)flag + 8) == 0) {
        int* ms = (int*)SP_MessageServer();
        typedef void (__thiscall *MsgFn)(int*, uint, int, int);
        ((MsgFn)(*(void***)ms)[0x14 / 4])(ms, 0x445f729, 0, 0);
    }
    self->mpBehaviorTreeData->mStimuli.ClearAll(0x800000, 0);
    (void)a;(void)b;(void)c2;(void)d;
}

// @ 0x00d9b560
bool FUN_00d9b560(Creature* self, int a, int b, int c2, int d, void* flag)
{
    if (self->IsAnimFinished(*(void**)((char*)flag + 4))) {
        if (self->IsLeader()) {
            *(char*)((char*)flag + 8) = 1;
            int* ms = (int*)SP_MessageServer();
            typedef void (__thiscall *MsgFn)(int*, uint, int, int);
            ((MsgFn)(*(void***)ms)[0x14 / 4])(ms, 0x445f729, 0, 0);
        }
        return false;
    }
    return true;
}

// @ 0x00d9b5b0
bool FUN_00d9b5b0(int a, int b, int c, int d, int e, int* out, int* in)
{
    out[0] = in[6];
    out[1] = in[7];
    long long v;
    if (in[8] != 0) v = 1i64 << in[8];
    else v = 0;
    *(long long*)(out + 6) = v;
    int* p = in + 3;
    struct Triple { int a, b, c; };
    Triple* t = (Triple*)p;
    out[2] = t->a;
    out[3] = t->b;
    out[4] = t->c;
    out[5] = 0;
    (void)a;(void)b;(void)c;(void)d;(void)e;
    return true;
}

// @ 0x00d9b610
void FUN_00d9b610(Creature* self, int a, int b, int c2, int d, void* p)
{
    typedef bool (__thiscall *LocoFn)(void*);
    void* loco = (void*)((char*)self + 0xc0);
    bool r = ((LocoFn)(*(void***)loco)[0xf8 / 4])(loco);
    self->FUN_00c14750(!r);
    int x = *(int*)((char*)p + 0x18);
    int y = *(int*)((char*)p + 0x1c);
    int z = x | y;
    if (z != 0) {
        self->mpBehaviorTreeData->mStimuli.ClearAll(x, y);
    }
    (void)a;(void)b;(void)c2;(void)d;
}

// @ 0x00d9b660
bool FUN_00d9b660(Creature* self)
{
    AnimHandle* h = self->mpBehaviorTreeData->mStimuli.Play(0x1000, 0);
    if (h == 0) { FUN_00da6270(self, 0x15); return false; }
    int r = FUN_00d994c0(FUN_00d999d0((int)h));
    if (r == 0) { FUN_00da6270(self, 0x15); return false; }
    int blk[2];
    blk[0] = (int)self; blk[1] = r;
    BehaviorMgr* mgr = FUN_00bc9b00();
    AnimHandle* node = mgr->FindNode(0x156bb1c6, (void*)&FUN_00d9b2d0, blk);
    if (node == 0) {
        node = mgr->AddOrder(0x156bb1c6, 0x20, 0x18eb4b7, kGiftInField);
        *(void**)((char*)node + 0x224) = (void*)0xdb4a20;
        *(int*)((char*)node + 0x1a4) = 0;
        *(int*)((char*)node + 0x1ac) = 0;
        *(int*)((char*)node + 0x1a8) = r;
        *(int*)((char*)node + 0x1b0) = 0;
    }
    mgr->SetNode(node, self, 0, 0);
    mgr->Activate(1, 2, self, g_fltMax, 0, 0);
    return true;
}

// @ 0x00d9b770 -- insertion sort of creature pointers using the loco comparator
void FUN_00d9b770(Creature** first, Creature** last)
{
    if (first == last) return;
    for (Creature** cur = first + 1; cur != last; ++cur) {
        Creature* val = *cur;
        Creature** hole = cur;
        Creature** scan = cur;
        while (scan != first) {
            Creature** prev = scan - 1;
            Loco* pa = *prev ? (Loco*)((char*)*prev + 0xc0) : 0;
            Loco* pb = val   ? (Loco*)((char*)val   + 0xc0) : 0;
            if (!LocoLess(pb, pa)) break;
            *hole = *prev;
            hole = prev;
            scan = prev;
        }
        *hole = val;
    }
}

// @ 0x00d9b7f0
char* FUN_00d9b7f0(char* first, char* last, char* out)
{
    while (first != last) {
        unsigned f = *(unsigned*)first;
        unsigned bit = f >> 31;
        if (bit == 0) {
            typedef void (__thiscall *RelFn)(void*, int);
            void* obj = first + 4;
            ((RelFn)(*(void***)obj)[0])(obj, 0);
        }
        first += 0x210;
        out += 0x210;
    }
    return out;
}

// @ 0x00d9b840 -- minimal element of {a, b, c} under the loco comparator
Creature** FUN_00d9b840(Creature** a, Creature** b, Creature** c)
{
    Loco* la = *a ? (Loco*)((char*)*a + 0xc0) : 0;
    Loco* lb = *b ? (Loco*)((char*)*b + 0xc0) : 0;
    Loco* lc = *c ? (Loco*)((char*)*c + 0xc0) : 0;
    if (LocoLess(la, lb)) {
        if (LocoLess(lb, lc)) return a;
        if (LocoLess(lc, la)) return c;
        return b;
    } else {
        if (LocoLess(lc, lb)) return b;
        if (LocoLess(la, lc)) return c;
        return a;
    }
}

// @ 0x00d9b950 -- push-heap sift-up of a 0x20-byte element
void FUN_00d9b950(char* base, int hole, int parent)
{
    char tmp[0x20];
    while (parent > hole) {
        int p = (parent - 1) >> 1;
        char* pElem = base + p * 0x20;
        // copy the candidate into the temporary, then compare (comparator is the stack functor)
        *(int*)tmp = p;   // placeholder slot; array of 8 dwords copied below
        if (!LocoLessStack(*(Loco**)pElem, *(Loco**)tmp)) break;
        char* dst = base + parent * 0x20;
        int* dp = (int*)dst; int* sp = (int*)pElem;
        for (int i = 0; i < 8; ++i) dp[i] = sp[i];
        parent = p;
    }
    char* dst = base + parent * 0x20;
    int* dp = (int*)dst; int* sp = (int*)tmp;
    for (int i = 0; i < 8; ++i) dp[i] = sp[i];
}

// @ 0x00d9b9b0 -- push-heap sift-up of creature pointers (index-based)
void FUN_00d9b9b0(Creature** base, int hole, int parent, Creature* val)
{
    if (parent <= hole) {
        base[parent] = val;
        return;
    }
    for (;;) {
        int p = (parent - 1) >> 1;
        Loco* lval  = val ? (Loco*)((char*)val + 0xc0) : 0;
        Creature* pv = base[p];
        Loco* lpv = pv ? (Loco*)((char*)pv + 0xc0) : 0;
        if (!LocoLess(lpv, lval)) break;
        base[parent] = pv;
        parent = p;
        if (parent <= hole) break;
    }
    base[parent] = val;
}

// @ 0x00d9ba30
bool FUN_00d9ba30(BehaviorMgr* self, uint v)
{
    if (!self->IsEmpty() && self->mKey1a4 == (int)v) return true;
    return false;
}

// @ 0x00d9ba60
void SocialValues::Update(int a0, int a1, Creature* c0, Creature* c1)
{
    if (mpWidget->IsBusy()) return;
    if (mbTimerRunning) return;
    if (mbFailed) return;
    if (mbDrain) return;
    float v0 = mpWidget->Get(0);
    float v1 = mpWidget->Get(1);

    if (c0 != 0 && mHandle0 != 0) {
        float r;
        if (!Anim_QueryB(c0, mHandle0)) {
            r = g_f1;
        } else {
            float pa = 0.0f, pb = 0.0f;
            if (!Anim_GetProgress(c0, mHandle0, &pb, &pa)) {
                r = 0.0f;
            } else {
                float q = pa / pb;
                r = (q > g_f1) ? g_f1 : q;
            }
        }
        mpWidget->Set(0, r);
    }
    if (c1 != 0 && mHandle1 != 0) {
        float r;
        if (!Anim_QueryB(c1, mHandle1)) {
            r = g_f1;
        } else {
            float pa = 0.0f, pb = 0.0f;
            if (!Anim_GetProgress(c1, mHandle1, &pa, &pb)) {
                r = 0.0f;
            } else {
                float q = pa / pb;
                r = (q > g_f1) ? g_f1 : q;
            }
        }
        mpWidget->Set(1, r);
    }
    if (mpWidget->Check0(0, 0) && c0 != 0) SetGlobalProperty(0xd02c025e, v0);
    if (mpWidget->Check0(1, 0) && c0 != 0) SetGlobalProperty(0xeb1b600f, v1);
    (void)a0; (void)a1;
    return;
}

// @ 0x00d9bc70
int SocialProposeBlock::RewardPlayer(Creature* c, uint param)
{
    int result = -1;
    void* nounMgr = SP_NounManager();
    FUN_00c77bf0((int)nounMgr);
    void* avatar = NounMgr_GetAvatar(SP_NounManager());

    Creature* target;
    if (c == 0) {
        target = 0;
    } else {
        target = (Creature*)c->QueryObj(0xd0036e08);
    }

    void* group = (char*)c + 0xb28;
    AnimHandle* node = FUN_00ba3f90(FUN_00b3d4c0(group, c, (void*)param), c, (void*)param);
    int goal = c->GetSocialGoal();
    if (goal != 0) {
        int m;
        switch ((int)node) {
            case 1:  m = 0xf37db906; break;
            case 2:
            case 5:  m = 0xd37db8f6; break;
            case 3:  m = 0x538bf747; break;
            default: m = 0x738bf75b; break;
        }
        result = m;
        if (goal == 4) mFlags58 |= 0x10;
        FUN_00ba48b0(FUN_00b3d4c0(group, c, (void*)3), (void*)3, c);
        if (goal != 4) {
            float t = mpWidget->Get(1) - 0.5f;
            float frac = (t >= 0.0f) ? t : 0.0f;
            int av = c->FUN_00c0c1a0();
            float dist = FUN_00c03440(*(int*)(av + 0x330)) * *(float*)(av + 0x328) * frac;
            float total = FUN_00c04140(1) + dist;
            NotifyEventFull(total, 1);
            FUN_00c756a0(total, 1);
            int msg[4];
            msg[0] = (int)avatar;
            msg[1] = (int)target;
            msg[2] = 0;
            FUN_00d39360(0x60b4123, msg);
        }
    }
    *(uint*)((char*)c + 0xb58) |= 0x80;
    void* p = FUN_00d37cb0();
    if (p) {
        int* ip = (int*)FUN_00d37cb0();
        typedef void (__thiscall *Fn)(int*, int);
        ((Fn)(*(void***)ip)[0x28 / 4])(ip, 0);
    }
    if (SP_GetCurrentGameMode() == (void*)0x1654c10) {
        int* gd = (int*)g_p016c7aa4;
        FUN_00f1d430((Creature*)*(int*)((char*)gd + 0x78));
    }
    int* audio = (int*)EA_Audio_GetSystemAT();
    if (audio) {
        typedef void (__thiscall *AudioFn)(int*, int);
        ((AudioFn)(*(void***)audio)[0x38 / 4])(audio, 0x3cdd1a9);
        typedef void (__thiscall *AudioFn2)(int*, int, int);
        ((AudioFn2)(*(void***)audio)[0x40 / 4])(audio, 0x34753a7, 0x8da68d69);
        typedef void (__thiscall *AudioFn3)(int*, int, float);
        ((AudioFn3)(*(void***)audio)[0x3c / 4])(audio, 0x34753aa, g_f1);
        typedef void (__thiscall *AudioFn4)(int*);
        ((AudioFn4)(*(void***)audio)[0x58 / 4])(audio);
    }
    mpWidget->Reset();
    int n = (int)FUN_00ba3f90(FUN_00b3d4c0(group, c, (void*)param), c, (void*)param);
    mpWidget->SetNode(n);
    return result;
}
