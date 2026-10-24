// Slice s00da6880 -- 0x00da6880 .. 0x00da7760 (40 functions).
//
// SPGonzago behaviour-tree node callbacks that act on a cSPCreatureCitizen: the "hut in danger"
// deciders, the watch/clear stimulus helpers, the tribe danger/flee actives (TRIBE_FLEE_HUT,
// TRIBE_TOOL_REMOVED) and the nearby-creature/tool selectors.  Most nodes share the six-slot
// signature (citizen, a, b, flags, behaviour_stimuli*, out) and return float in st0.
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc)
#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

struct cSPCreatureCitizen;
struct cTribe;
struct behavior_stimuli;
struct cBehaviorTreeData;
struct cTool;

// ---------------------------------------------------------------------------
// engine helpers reached by the retail code (address in the comment)
// ---------------------------------------------------------------------------
void* __cdecl FUN_00d999d0(void* block);                        // 0x00d999d0 WatchMemoryBlock
void* __cdecl FUN_00d998d0(void* block, u32 key);               // 0x00d998d0
void* __cdecl FUN_00ac80d0(void* block, u32 key);               // 0x00ac80d0
void* __stdcall FUN_00b3d2c0(int a, int b, int c);                // 0x00b3d2c0 RelationshipManager
void* __stdcall FUN_00af13b0(void* c, int n, float* out);        // 0x00af13b0
void* __cdecl FUN_00b3d350(void* out, u32 v);                   // 0x00b3d350 PlanetModel
void  __cdecl FUN_00b81780(void* model);                        // 0x00b81780 MakeRandomWorldPosition

struct Obj50g {                                                  // FUN_00b3d480 result
    virtual void g00(); virtual void g04(); virtual void g08(); virtual void g0c();
    virtual void g10(); virtual void g14(); virtual void g18(); virtual void g1c();
    virtual void g20(); virtual void g24(); virtual void g28(); virtual void g2c();
    virtual void g30(); virtual void g34(); virtual void g38(); virtual void g3c();
    virtual void g40(); virtual void g44(); virtual void g48(); virtual void g4c();
    virtual void v50(void* p);                                   // +0x50
};
Obj50g* __cdecl FUN_00b3d480();                                  // 0x00b3d480

// ---------------------------------------------------------------------------
// creature sub-objects
// ---------------------------------------------------------------------------
struct VF8 {                                                     // 8 filler virtual slots
    virtual void f00(); virtual void f01(); virtual void f02(); virtual void f03();
    virtual void f04(); virtual void f05(); virtual void f06(); virtual void f07();
};
struct VF16 : VF8 {
    virtual void f08(); virtual void f09(); virtual void f10(); virtual void f11();
    virtual void f12(); virtual void f13(); virtual void f14(); virtual void f15();
};

// the citizen's own v-table: +0x20 id/slot, +0x2c state, +0x4c num, +0xc0 proximity check
struct Crt : VF8 {
    virtual int   v20();                                         // +0x20
    virtual void  d24(); virtual void d28();
    virtual char  v2c();                                         // +0x2c
    virtual void  d30(); virtual void d34(); virtual void d38(); virtual void d3c();
    virtual void  d40(); virtual void d44(); virtual void d48();
    virtual int   v4c();                                         // +0x4c
    virtual void  d50(); virtual void d54();
    virtual void  d58(); virtual void d5c(); virtual void d60(); virtual void d64();
    virtual void  d68(); virtual void d6c(); virtual void d70(); virtual void d74();
    virtual void  d78(); virtual void d7c(); virtual void d80(); virtual void d84();
    virtual void  d88(); virtual void d8c(); virtual void d90(); virtual void d94();
    virtual void  d98(); virtual void d9c(); virtual void da0(); virtual void da4();
    virtual void  da8(); virtual void dac(); virtual void db0(); virtual void db4();
    virtual void  db8(); virtual void dbc();
    virtual char  vc0(void*, float, float);                      // +0xc0
};

struct Sub58 {                                                   // embedded sub-object at citizen+0x58
    virtual void  s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void  s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual int   v20();                                         // +0x20
    virtual void  d24(); virtual void d28(); virtual void d2c(); virtual void d30();
    virtual void  v34();                                         // +0x34
};

struct StimTimer {                                               // sub-object with a stim timer
    char  mData[4];
    float GetTimer();                                            // 0x00cee380
    void* GetPtr330();                                           // 0x00cee330
    void* GetPtr340();                                           // 0x00cee340
};

struct CeeObj {                                                  // object returned by 0x00cee330
    char  mPad000[0x12c];
    u32   mState12c;                                             // +0x12c
};

struct Combatant {                                               // combat sub-object (+0x120 / +0x5a8)
    virtual void c00(); virtual void c04(); virtual void c08(); virtual void c0c();
    virtual void c10(); virtual void c14();
    virtual void v18(float, int, int, void*, int);               // +0x18
    virtual void c1c(); virtual void c20(); virtual void c24(); virtual void c28();
    virtual int  v2c(float);                                     // +0x2c
    int   GetDamageState();                                      // 0x008e7f80
    float GetHealthPct();                                        // 0x00bfc490
};

struct SpatC0 {                                                  // embedded sub-object at citizen+0xc0
    virtual void  p00(); virtual void p04(); virtual void p08(); virtual void p0c();
    virtual void  p10(); virtual void p14(); virtual void p18(); virtual void p1c();
    virtual void  p20(); virtual void p24(); virtual void p28(); virtual void p2c();
    virtual void  p30(); virtual void p34(); virtual void p38(); virtual void p3c();
    virtual void  p40(); virtual void p44(); virtual void p48(); virtual void p4c();
    virtual void  p50(); virtual void p54();
    virtual char  v58();                                         // +0x58
    virtual void  d5c(); virtual void d60(); virtual void d64(); virtual void d68();
    virtual void  d6c(); virtual void d70();
    virtual float v74(float);                                    // +0x74
    virtual void  d78(); virtual void d7c(); virtual void d80(); virtual void d84();
    virtual void  d88(); virtual void d8c(); virtual void d90(); virtual void d94();
    virtual void  d98(); virtual void d9c(); virtual void da0(); virtual void da4();
    virtual void  da8(); virtual void dac(); virtual void db0(); virtual void db4();
    virtual void  db8(); virtual void dbc(); virtual void dc0(); virtual void dc4();
    virtual void  dc8(); virtual void dcc(); virtual void dd0(); virtual void dd4();
    virtual void  dd8(); virtual void ddc(); virtual void de0(); virtual void de4();
    virtual void  de8(); virtual void dec(); virtual void df0(); virtual void df4();
    virtual char  vf8();                                         // +0xf8
    char  IsNearGoal();                                          // 0x00c42e20
    void* FUN_c41ec0();                                          // 0x00c41ec0
};

// the object a behaviour_stimuli::Play hands back (an animation record)
struct AnimPlayRes {
    char  mPad000[0xc];
    u32   mAnimId;                                               // +0xc
    u32   mAnim;                                                 // +0x10
};

struct behavior_stimuli {
    int   mStimulusID;                                           // +0x0
    void* mTarget;                                               // +0x4
    void* mValue;                                                // +0x8
    char  mPad0c[0x18 - 0xc];
    int   mF18;                                                  // +0x18

    void   ClearAll(u32 lo, u32 hi);                             // 0x00bc98f0
    AnimPlayRes* Play(u32 lo, u32 hi);                           // 0x00bc96a0
    void   PlayWith(u32 lo, u32 hi, float dur, void* target);    // 0x00bc97f0
    void   GetAny();                                             // 0x00d997e0
};

struct cBehaviorTreeData {
    char             mPad00[8];
    behavior_stimuli mStimuli;                                   // +0x08
    char             mPad1c[0x1c8 - 0x08 - sizeof(behavior_stimuli)];
    u32              mFlags1c8;                                  // +0x1c8
    char             mPad1cc[0x1d8 - 0x1cc];
    u32              mKey1d8;                                    // +0x1d8

    void PopFront();                                             // 0x00bcaf40
};

struct cTool {                                                   // a tool object (has a combatant)
    char      mPad000[0x120];
    Combatant mCombat;                                           // +0x120
};

struct cTribe : VF16 {                                            // +0x60 slot60, +0xac slotac
    virtual void  d40(); virtual void d44(); virtual void d48(); virtual void d4c();
    virtual void  d50(); virtual void d54(); virtual void d58(); virtual void d5c();
    virtual float v60();                                         // +0x60
    virtual void  d64(); virtual void d68(); virtual void d6c(); virtual void d70();
    virtual void  d74(); virtual void d78(); virtual void d7c(); virtual void d80();
    virtual void  d84(); virtual void d88(); virtual void d8c(); virtual void d90();
    virtual void  d94(); virtual void d98(); virtual void d9c(); virtual void da0();
    virtual void  da4(); virtual void da8();
    virtual cTool* vac();                                        // +0xac

    char      mPad004[0x120 - 4];                                // +0x04
    Combatant mCombat;                                           // +0x120
    char      mPad124[0x20c - 0x124];                            // +0x124
    StimTimer mTimer20c;                                         // +0x20c
    char      mPad210[0x556 - 0x210];                            // +0x210
    u8        mFlag556;                                          // +0x556

    cSPCreatureCitizen* GetChieftain();                          // 0x00c8fd30
    cTool*              GetToolOfType(int type);                 // 0x00c8f6e0
};

struct RelMgr {                                                  // FUN_00b3d2c0 result
    int FUN_d00a70();                                            // 0x00d00a70
};

struct cAgentOrderManager {
    int FindSlot(int a, int b, int c, int d);                    // 0x00bca0c0
};

struct LayoutMgr {
    char LookupB();                                               // 0x00af0bd0
};

// object returned by FUN_00d998d0 in 0x00da6f60 (has an animation-state virtual at +0x58)
struct ResAnim : VF8 {
    virtual void a20(); virtual void a24(); virtual void a28(); virtual void a2c();
    virtual void a30(); virtual void a34(); virtual void a38(); virtual void a3c();
    virtual void a40(); virtual void a44(); virtual void a48(); virtual void a4c();
    virtual void a50(); virtual void a54();
    virtual int  v58();                                          // +0x58
};

// ---------------------------------------------------------------------------
// the behaviour-tree's citizen object
// ---------------------------------------------------------------------------
struct cSPCreatureCitizen : Crt {
    char      mPad004[0x34 - 0x04];                              // +0x04
    StimTimer mTimer34;                                          // +0x34
    char      mPad038[0x58 - 0x38];                              // +0x38
    Sub58     mSub58;                                            // +0x58
    char      mPad05c[0xc0 - 0x5c];                              // +0x5c
    SpatC0    mSubC0;                                            // +0xc0
    char      mPad0c4[0x135 - 0xc4];                             // +0xc4
    u8        mFlag135;                                          // +0x135
    char      mPad136[0x330 - 0x136];                            // +0x136
    u8        mFlag330;                                          // +0x330
    char      mPad331[0x5a8 - 0x331];                            // +0x331
    Combatant mCombat;                                           // +0x5a8
    char      mPad5ac[0xb48 - 0x5ac];                            // +0x5ac
    cAgentOrderManager* mpOrders;                                // +0xb48
    cBehaviorTreeData*  mpBTree;                                 // +0xb4c
    char      mPadb50[0xb58 - 0xb50];
    u32       mFlagsB58;                                         // +0xb58
    char      mPadb5c[0xb5e - 0xb5c];
    u8        mbDead;                                            // +0xb5e

    cTribe* GetTribe();                                          // 0x00c22f50
    int     FUN_c22dc0();                                        // 0x00c22dc0
    float   FUN_c0b9c0();                                        // 0x00c0b9c0
    int     FUN_c0ee60();                                        // 0x00c0ee60
    char    FUN_bc9b50();                                        // 0x00bc9b50
    cSPCreatureCitizen* FUN_bc9b10();                            // 0x00bc9b10
    char    Proximity(void* t, float a, float b);                // 0x00c0d560
    u32     InterruptAnimation(u32 id, int a, int b);            // 0x00c12310
    void    PlayAnimation(u32 id, int a, int b);                 // 0x00c12190
    void    FUN_c14750(int a);                                   // 0x00c14750
    void    FUN_c279a0(int a);                                   // 0x00c279a0
    void    SetCurrentToolEffect(int a, int b);                  // 0x00c24f40
    void    ForceOrdersUpdate();                                 // 0x00c26450
    void    MoveToPointAtSpeed(int a, void* p, float b, float c);// 0x00c1c1d0
    char    AnimationFinished(u32 id);                           // 0x00c12400
};

// ---------------------------------------------------------------------------
// retail read-only constants / tables (address in the comment)
// ---------------------------------------------------------------------------
extern const float g_f147c218;          // 0x0147c218
extern const float g_f147c21c;          // 0x0147c21c
extern const float g_f1473c70;          // 0x0147c21c-family duration (20.0f)
extern const float g_f13ec4d0;          // 0x013ec4d0 (100.0f)
extern const float g_f13eecd8;          // 0x013eecd8 (20.0f)
extern const float g_f1486110;          // 0x01486110 (5.0f)
extern const float g_f1485378;          // 0x01485378 (0.0f)
extern const float g_f1485720;          // 0x01485720 (1.0f)
extern const float g_f1687a0c;          // 0x01687a0c
extern const float g_f1687a10;          // 0x01687a10
extern const float g_f1687a14;          // 0x01687a14
extern const u32   g_a147c220[10];      // 0x0147c220 tool-type table
extern const float g_f169f408;          // 0x0169f408

// ---------------------------------------------------------------------------
// implementation
// ---------------------------------------------------------------------------

// @ 0x00da6880
float __cdecl FUN_00da6880(cSPCreatureCitizen* c, u32 a, u32 b, u8 flags, behavior_stimuli* stim, u8* out)
{
    cSPCreatureCitizen* ch = c->GetTribe()->GetChieftain();
    if (ch != 0) {
        AnimPlayRes* play = ch->mpBTree->mStimuli.Play(0, 0x80);
        if (play != 0) {
            cSPCreatureCitizen* s = (cSPCreatureCitizen*)FUN_00d999d0(play);
            if (s != 0 && s->mbDead == 0) {
                if (s->v20() == 0x18eb45e || s->mSubC0.v58() != 0) {
                    if (stim != 0)
                        stim->GetAny();
                    stim->mTarget = &s->mCombat;
                    stim->mF18 = 7;
                    *out = 1;
                    return 1.0f;
                }
            }
        }
    }
    return 0.0f;
}

// @ 0x00da6920
float __cdecl FUN_00da6920(cSPCreatureCitizen* c, u32 a, u32 b, u8 flags)
{
    if ((flags & 2) != 0) {
        c->GetTribe();
        AnimPlayRes* p = c->mpBTree->mStimuli.Play(0, 0x24000);
        if (p != 0) {
            cSPCreatureCitizen* q = (cSPCreatureCitizen*)FUN_00d998d0(p, 0xce9f6639);
            if (q != 0 && q->mFlag135 != 0) {
                AnimPlayRes* r = q->mpBTree->mStimuli.Play(0x200000, 0);
                if (r != 0) {
                    if (FUN_00d998d0(r, 0xee02c7) != 0)
                        return 1.0f;
                }
            }
        }
    }
    return 0.0f;
}

// @ 0x00da69e0
float __cdecl FUN_00da69e0(cSPCreatureCitizen* c, u32 a, u32 b, u8 flags)
{
    if ((flags & 2) != 0) {
        c->GetTribe();
        AnimPlayRes* p = c->mpBTree->mStimuli.Play(0, 0x20000);
        if (p != 0) {
            cSPCreatureCitizen* q = (cSPCreatureCitizen*)FUN_00d998d0(p, 0xce9f6639);
            if (q != 0 && q->mFlag135 != 0) {
                if (q->v20() == 0x18eb45e)
                    return 1.0f;
                AnimPlayRes* r = q->mpBTree->mStimuli.Play(0x200000, 0);
                if (r != 0)
                    return 1.0f;
            }
        }
    }
    return 0.0f;
}

// @ 0x00da6aa0
float __cdecl FUN_00da6aa0(cSPCreatureCitizen* c, u32 a, u32 b, u8 flags, behavior_stimuli* stim, u8* out)
{
    c->GetTribe();
    AnimPlayRes* play = c->mpBTree->mStimuli.Play(0, 0x20000);
    if (play != 0) {
        cSPCreatureCitizen* s = (cSPCreatureCitizen*)FUN_00d999d0(play);
        if (s != 0 && s->mbDead == 0) {
            if (stim != 0)
                stim->GetAny();
            stim->mTarget = &s->mCombat;
            *out = 1;
            return 1.0f;
        }
    }
    return 0.0f;
}

// @ 0x00da6b10
u8 __cdecl FUN_00da6b10(cSPCreatureCitizen* a, cSPCreatureCitizen* b)
{
    bool set = false;
    int id1 = a->v4c();
    int id2 = b->v4c();
    if (id1 == id2)
        return set;
    if (b->mpOrders->FindSlot(0, 2, 0, 0) != -1 ||
        b->mpOrders->FindSlot(1, 2, 0, 0) != -1 ||
        b->mpBTree->mKey1d8 == 0xd59a3b60)
        set = true;
    u32 v = ((RelMgr*)FUN_00b3d2c0(id1, id2, 1))->FUN_d00a70();
    if (set || v > 1)
        return 0;
    return 1;
}

// @ 0x00da6bb0
float __cdecl FUN_00da6bb0(cSPCreatureCitizen* c)
{
    cSPCreatureCitizen* s = (cSPCreatureCitizen*)FUN_00d999d0(c->mpBTree->mStimuli.Play(0, 0x4000));
    if (s != 0) {
        if (s->v2c() == 0 && s->mFlag135 != 0 && s->mbDead == 0) {
            if (c->Proximity(s, 1.0f, 0.0f) != 0 || c->vc0(s, 1.0f, 0.0f) != 0) {
                void* r = FUN_00ac80d0(s, 0x18eb45e);
                if (r != 0) {
                    c->mpBTree->mStimuli.PlayWith(0x8000, 0, g_f147c218, r);
                    return 0.0f;
                }
                void* r2 = FUN_00ac80d0(s, 0x18eb4b7);
                if (r2 != 0)
                    c->mpBTree->mStimuli.PlayWith(0x400, 0, g_f147c218, r2);
            }
        }
    }
    return 0.0f;
}

// @ 0x00da6cb0
float __cdecl FUN_00da6cb0(cSPCreatureCitizen* c)
{
    if (c->FUN_c0b9c0() < g_f147c21c)
        return 0.0f;
    return c->mCombat.GetHealthPct() * g_f13ec4d0 < g_f1687a14 ? 1.0f : 0.0f;
}

// @ 0x00da6d10
float __cdecl FUN_00da6d10(cSPCreatureCitizen* c)
{
    if (c->FUN_c0b9c0() < g_f147c21c)
        return 0.0f;
    return c->mCombat.GetHealthPct() * g_f13ec4d0 < g_f1687a10 ? 1.0f : 0.0f;
}

// @ 0x00da6d70
float __cdecl FUN_00da6d70(cSPCreatureCitizen* c)
{
    if (c->GetTribe()->mTimer20c.GetTimer() > 0.0f ||
        c->mTimer34.GetTimer() > 0.0f) {
        if (c->FUN_c0b9c0() < g_f1687a14 && c->mpBTree->mKey1d8 != 0x461300f)
            return 1.0f;
    }
    return 0.0f;
}

// @ 0x00da6de0
float __cdecl FUN_00da6de0(cSPCreatureCitizen* c)
{
    if (c->GetTribe()->mTimer20c.GetTimer() > 0.0f ||
        c->mTimer34.GetTimer() > 0.0f) {
        if (c->FUN_c0b9c0() < g_f1687a10 && c->mpBTree->mKey1d8 != 0x461300f)
            return 1.0f;
    }
    return 0.0f;
}

// @ 0x00da6e50
float __cdecl FUN_00da6e50(cSPCreatureCitizen* c)
{
    float r;
    if (c->GetTribe()->mTimer20c.GetTimer() == 0.0f &&
        c->mTimer34.GetTimer() == 0.0f &&
        c->FUN_c0b9c0() < g_f1687a0c)
        r = 1.0f;
    else
        r = 0.0f;
    return r;
}

// @ 0x00da6ed0
float __cdecl FUN_00da6ed0(cSPCreatureCitizen* c, u32 a, u32 b, u8 flags, behavior_stimuli* stim, u8* out)
{
    float v = 0.0f;
    if ((flags & 1) == 0) {
        if (c->GetTribe()->mTimer20c.GetTimer() > 0.0f ||
            c->mTimer34.GetTimer() > 0.0f) {
            LayoutMgr* mgr = (LayoutMgr*)FUN_00af13b0(c, 1, &v);
            if (mgr->LookupB() != 0) {
                c->GetTribe();
                if (stim != 0)
                    stim->GetAny();
                stim->mF18 = 1;
                *out = 1;
                return 1.0f;
            }
        }
    }
    return 0.0f;
}

// @ 0x00da6f60
float __cdecl FUN_00da6f60(cSPCreatureCitizen* c)
{
    AnimPlayRes* play = c->mpBTree->mStimuli.Play(0x40, 0);
    ResAnim* r = (ResAnim*)FUN_00d998d0(play, 0x116d858);
    float res;
    if (r->v58() == 1 || r->v58() == 2 || r->v58() == 3)
        res = 1.0f;
    else
        res = 0.0f;
    return res;
}

// @ 0x00da6fe0
float __cdecl FUN_00da6fe0(cSPCreatureCitizen* c, u32 a, u32 b, u8 flags, behavior_stimuli* stim, u8* out)
{
    AnimPlayRes* play = c->mpBTree->mStimuli.Play(0, 0x80);
    cSPCreatureCitizen* s = (cSPCreatureCitizen*)FUN_00d999d0(play);
    if (s != 0 && s->mbDead == 0) {
        if (c->mCombat.GetHealthPct() * g_f13ec4d0 < g_f1687a10) {
            if (stim != 0)
                stim->GetAny();
            stim->mTarget = &s->mCombat;
            *out = 1;
            return 1.0f;
        }
    }
    return 0.0f;
}

// @ 0x00da7060
float __cdecl FUN_00da7060(cSPCreatureCitizen* c, u32 a, u32 b, u8 flags, behavior_stimuli* stim, u8* out)
{
    AnimPlayRes* play = c->mpBTree->mStimuli.Play(0, 0x80);
    cSPCreatureCitizen* s = (cSPCreatureCitizen*)FUN_00d999d0(play);
    if (s != 0 && s->mbDead == 0) {
        if (stim != 0)
            stim->GetAny();
        stim->mTarget = &s->mCombat;
        *out = 1;
        return 1.0f;
    }
    return 0.0f;
}

// @ 0x00da70c0
float __cdecl FUN_00da70c0(void* a)
{
    FUN_00b3d480()->v50(a);
    return 0.0f;
}

// @ 0x00da70e0
float __cdecl FUN_00da70e0(cSPCreatureCitizen* c)
{
    c->mpBTree->mStimuli.ClearAll(0, 0x800000);
    int v = c->FUN_c22dc0();
    if (v == 0 || v == 0xb)
        return 0.0f;
    cTool* tool = c->GetTribe()->GetToolOfType(v);
    if (tool != 0 && tool->mCombat.GetDamageState() != 2)
        return 0.0f;
    return 1.0f;
}

// @ 0x00da7140
u8 __cdecl FUN_00da7140(cSPCreatureCitizen* a, cSPCreatureCitizen* b)
{
    if (a->FUN_bc9b50() == 0) {
        cSPCreatureCitizen* x = a->FUN_bc9b10();
        if (x->GetTribe() == b->GetTribe())
            return 1;
    }
    return 0;
}

// @ 0x00da7180
float __cdecl FUN_00da7180(cSPCreatureCitizen* c, u32 a, u32 b, u8 flags, behavior_stimuli* stim, u8* out)
{
    if ((flags & 1) == 0) {
        cTribe* t = c->GetTribe();
        if (t != 0) {
            cTool* tool = t->vac();
            if (tool != 0) {
                if (tool->mCombat.GetDamageState() != 2 &&
                    tool->mCombat.GetHealthPct() < 1.0f) {
                    if (stim != 0)
                        stim->GetAny();
                    stim->mValue = tool;
                    *out = 1;
                    return 1.0f;
                }
            }
            for (u32 i = 0; i < 0x28; i += 4) {
                cTool* tl = t->GetToolOfType(g_a147c220[i >> 2]);
                if (tl != 0) {
                    if (tl->mCombat.GetDamageState() != 2 &&
                        tl->mCombat.GetHealthPct() < 1.0f) {
                        if (stim != 0)
                            stim->GetAny();
                        stim->mValue = tl;
                        *out = 1;
                        return 1.0f;
                    }
                }
            }
        }
    }
    return 0.0f;
}

// @ 0x00da7270
u8 __cdecl FUN_00da7270(cSPCreatureCitizen* c)
{
    AnimPlayRes* play = c->mpBTree->mStimuli.Play(1, 0);
    if (play == 0 || play->mAnimId == 1)
        c->mSub58.v34();
    c->mpBTree->mStimuli.ClearAll(1, 0);
    return 0;
}

// @ 0x00da72c0
u8 __cdecl FUN_00da72c0(cSPCreatureCitizen* c)
{
    c->mpBTree->mStimuli.ClearAll(0x4000, 0);
    return 0;
}

// @ 0x00da72e0
unsigned __cdecl FUN_00da72e0(cSPCreatureCitizen* c)
{
    return c->mSub58.v20() != 0;
}

// @ 0x00da7300
u8 __cdecl FUN_00da7300(cSPCreatureCitizen* c)
{
    return c->mSub58.v20() != 0;
}

// @ 0x00da7320
void __cdecl FUN_00da7320(cSPCreatureCitizen* c)
{
    c->mSub58.v34();
}

// @ 0x00da7330
void __cdecl FUN_00da7330(cSPCreatureCitizen* c)
{
    c->FUN_c14750(0);
}

// @ 0x00da7340
struct MoveGoal {                                                // FUN_00c41ec0() result (flags word at +0x70)
    char mPad0[0x70];
    u32 mFlags70;                                                // +0x70
};

u8 __cdecl FUN_00da7340(cSPCreatureCitizen* c)
{
    cTribe* t = c->GetTribe();
    float f10 = t->v60();
    float f9 = c->mSubC0.v74(f10);
    int v = t->mCombat.v2c(f9);
    char buf[12];
    void* pm = FUN_00b3d350(buf, v);
    FUN_00b81780(pm);
    c->InterruptAnimation(0x2c38d92, -1, 0);
    float d = c->mSubC0.v74(f10);
    c->MoveToPointAtSpeed(3, buf, d, d + d);
    MoveGoal* l = (MoveGoal*)c->mSubC0.FUN_c41ec0();
    l->mFlags70 |= 2;
    return 1;
}

// @ 0x00da73e0
u32 __cdecl FUN_00da73e0(cSPCreatureCitizen* c)
{
    u32 r;
    if (c->mSubC0.IsNearGoal() != 0 || (c->mFlag330 & 1) != 0)
        r = 0;
    else
        r = 1;
    return r;
}

// @ 0x00da7410
void __cdecl FUN_00da7410(cSPCreatureCitizen* c)
{
    c->mpBTree->mStimuli.PlayWith(0, 0x8000, g_f1473c70, 0);
    c->FUN_c14750(0);
}

// @ 0x00da7450
u8 __cdecl FUN_00da7450(cSPCreatureCitizen* c, u32 a, u32 b, u8 flags, behavior_stimuli* stim, float* out)
{
    *out = g_f13eecd8;
    return 1;
}

// @ 0x00da7470
u8 __cdecl FUN_00da7470(cSPCreatureCitizen* c, u32 a, u32 b, u8 flags, void* p5, float* out, float unused7, float delta)
{
    cTribe* t = c->GetTribe();
    if (t != 0 && t->mFlag556 != 0) {
        float n = *out - delta;
        *out = n;
        if (n < 0.0f) {
            c->mCombat.v18(g_f147c218, -1, 2, (void*)&g_f169f408, 0);
            return 0;
        }
    }
    return 1;
}

// @ 0x00da74e0
void __cdecl FUN_00da74e0(cSPCreatureCitizen* c)
{
    char v = c->mSubC0.vf8();
    c->FUN_c14750(v == 0);
    if ((c->mpBTree->mFlags1c8 & 0x2000000) == 0)
        c->mpBTree->mStimuli.ClearAll(0, 0x20);
}

// @ 0x00da7530
u32 __cdecl FUN_00da7530(cSPCreatureCitizen* c, u32 a, u32 b, u8 flags, void* p5, float* out, float unused7, float delta)
{
    AnimPlayRes* play = c->mpBTree->mStimuli.Play(0, 8);
    if (play != 0) {
        *out = g_f1486110;
        c->InterruptAnimation(play->mAnimId, -1, 0);
        c->PlayAnimation(play->mAnim, 1, -1);
        c->mpBTree->mStimuli.ClearAll(0, 8);
    }
    float n = *out - delta;
    *out = n;
    return n > 0.0f;
}

// @ 0x00da75c0
void __cdecl FUN_00da75c0(cSPCreatureCitizen* c)
{
    if (c->mbDead == 0 && c->mFlag135 != 0)
        c->FUN_c14750(0);
}

// @ 0x00da75e0
u8 __cdecl FUN_00da75e0(cSPCreatureCitizen* a, cSPCreatureCitizen* b)
{
    if (a->FUN_bc9b50() == 0) {
        cSPCreatureCitizen* x = a->FUN_bc9b10();
        if (b != 0 && x != 0) {
            cTribe* tb = b->GetTribe();
            cTribe* tx = x->GetTribe();
            int cb = b->FUN_c0ee60();
            int cx = x->FUN_c0ee60();
            if (tx == tb && cb == cx)
                return 1;
        }
    }
    return 0;
}

// @ 0x00da7640
u8 __cdecl FUN_00da7640(cSPCreatureCitizen* c, u32 a, u32 b, u8 flags, void* p5, u32* out)
{
    c->mpBTree->PopFront();
    c->mpBTree->mStimuli.ClearAll(0x1d3fbffa, 0x81240a0);
    c->ForceOrdersUpdate();
    *out = c->InterruptAnimation(0x575f108, -1, 0);
    c->FUN_c279a0(0);
    c->SetCurrentToolEffect(0, -1);
    return 1;
}

// @ 0x00da76a0
u8 __cdecl FUN_00da76a0(cSPCreatureCitizen* c, u32 a, u32 b, u8 flags, void* p5, u32* out)
{
    if (*out != 0) {
        if (c->AnimationFinished(*out) == 0)
            return 1;
    }
    return 0;
}

// @ 0x00da76c0
float __cdecl FUN_00da76c0(cSPCreatureCitizen* c, u32 a, u32 b, u8 flags, behavior_stimuli* stim, u8* out)
{
    cTribe* t = c->GetTribe();
    if (t != 0) {
        void* p = t->mTimer20c.GetPtr340();
        if (p != 0) {
            if (stim != 0)
                stim->GetAny();
            stim->mValue = p;
            *out = 1;
            return 1.0f;
        }
    }
    return 0.0f;
}

// @ 0x00da7710
u8 __cdecl FUN_00da7710(cSPCreatureCitizen* c)
{
    c->mFlagsB58 |= 0x8000;
    return 1;
}

// @ 0x00da7730
void __cdecl FUN_00da7730(cSPCreatureCitizen* c)
{
    c->mFlagsB58 &= 0xffff7fff;
    c->mpBTree->mStimuli.ClearAll(0, 2);
}

// @ 0x00da7760
float __cdecl FUN_00da7760(cSPCreatureCitizen* c)
{
    CeeObj* p = (CeeObj*)c->mTimer34.GetPtr330();
    if (p != 0 && p->mState12c != 1)
        return 1.0f;
    return 0.0f;
}