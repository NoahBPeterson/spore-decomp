// s00da7780 - Spore SporeApp.exe slice (worker 18, batch gold6)
// Reconstructed from the frozen disassembly; free __cdecl functions (the object is
// passed on the stack for every VA except PickNewActivity, whose `this` is in ecx).

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef int            i32;
typedef float          f32;

struct Creature;
struct cTribe;
struct Strategy;
struct IdleBlock;

// ---------------------------------------------------------------------------
// small support types
// ---------------------------------------------------------------------------

struct PtrVec { Creature** mBegin; Creature** mEnd; };

struct AutoRefCount {
    u32  mPtr;
    void operator=(void* p);
};

// order record stored in the agent-order manager's record array (stride 0xac)
#pragma pack(push, 1)
struct OrderSub39 {
    u32          mField00;                 // +0x39 +0x00
    u8           pad_04[0xc];
    u8           mByte10;                  // +0x49 (sub +0x10)
    u8           pad_11[1];
    u16          mField12;                 // +0x4b (sub +0x12)
};
struct OrderRec {
    u32          mField00;                 // +0x00
    u8           pad_04[0x24];
    AutoRefCount mRef28;                   // +0x28
    u8           pad_2c[0xd];
    OrderSub39   mSub39;                   // +0x39
    u8           pad_4d[0x2b];
    u32          mField78;                 // +0x78
    u32          mField7c;                 // +0x7c
    u8           pad_80[0x2c];
};
#pragma pack(pop)

struct BehaviorStimuli {
    u32   mField00;                        // +0x00
    void* mField04;                        // +0x04
    u8    pad_08[0x38];
    u32 Play(u32 a, u32 flags);
    u32 ClearAll(u32 a, u32 flags);
    void GetAny();
};

struct AgentOrderManager {
    u8 pad_00[8];
    BehaviorStimuli mStimuli;              // +0x08
    u8 pad_48[0x118];
    OrderRec mRecs[1];                     // +0x160
    OrderRec* FirstPending();
    u32 FUN_00bc5040(u32 a);
    u32 FUN_00bc3db0(u32 a);
    u32 FUN_00bc3df0(u32 a);
};

struct SubObj58 {
    void* vptr;
    i32 V_2c() { return (*(i32 (__thiscall**)(void*))(*(char**)this + 0x2c))(this); }
};

struct Ret7780 {
    u8  pad_000[0x12c];
    i32 mField12c;
};

// embedded locomotive subobject, lives at creature+0x34
struct Locomotive {
    u8  pad_00[0x24];
    SubObj58 mSub58;                       // creature +0x58
    u8  pad_28[0x64];
    Ret7780* FUN_00cee330();
};

// polymorphic animation object returned by FUN_00d99a10 / FUN_00d998f0
struct AnimObj {
    void* V_8()        { return (*(void* (__thiscall**)(void*))(*(char**)this + 0x08))(this); }
    void* V_c()        { return (*(void* (__thiscall**)(void*))(*(char**)this + 0x0c))(this); }
    void* V_20()       { return (*(void* (__thiscall**)(void*))(*(char**)this + 0x20))(this); }
    f32*  V_2c()       { return (*(f32* (__thiscall**)(void*))(*(char**)this + 0x2c))(this); }
    void* V_5c(u32 a)  { return (*(void* (__thiscall**)(void*, u32))(*(char**)this + 0x5c))(this, a); }
};

// embedded polymorphic object at creature+0xc0
struct Obj0xc0 {
    void* vptr;                            // +0x00
    u8    pad_04[0x4c];
    u8    V_58()      { return (*(u8 (__thiscall**)(void*))(*(char**)this + 0x58))(this); }
    u8    V_f8()      { return (*(u8 (__thiscall**)(void*))(*(char**)this + 0xf8))(this); }
    void  V_ec()      { (*(void (__thiscall**)(void*))(*(char**)this + 0xec))(this); }
    void  V_54(u32 a) { (*(void (__thiscall**)(void*, u32))(*(char**)this + 0x54))(this, a); }
    void* V_2c()      { return (*(void* (__thiscall**)(void*))(*(char**)this + 0x2c))(this); }
    void  FUN_00c41d60(void* p);
    void  FUN_00c41d90(void* p);
};

struct cSPTimer {
    u8 mData[0x20];
    void Restart();
};

struct cSub558 {
    u8 mData[0x10];
    void FUN_00cc7f90(u32 a);
};

struct cTribe {
    void* vptr;                            // +0x00
    u8  pad_004[0x268];
    i32 mField26c;                         // +0x26c
    cSPTimer mTimer270;                    // +0x270
    u8  pad_290[0x2c8];
    cSub558 mSub558;                       // +0x558
    void FindSpot(u32 a, u32 b);
    void FUN_00c950f0(Creature* p);
    void V_9c(Creature* p, u32 a) { (*(void (__thiscall**)(void*, Creature*, u32))(*(char**)this + 0x9c))(this, p, a); }
};

struct CCB;

struct Strategy {
    void* vptr;                            // +0x00
    void* V_6c_a()      { return (*(void* (__thiscall**)(void*))(*(char**)this + 0x6c))(this); }
    CCB*  V_6c_b(Creature* p) { return (*(CCB* (__thiscall**)(void*, Creature*))(*(char**)this + 0x6c))(this, p); }
};

struct TriggerMgr {
    void* vptr;                            // +0x00
    u8  pad_004[0x28];
    i32 mField2c;                          // +0x2c
    u8  FUN_00adb360(void* o);
    void goExit();
};

struct Manager0 {
    void* vptr;                            // +0x00
    void* FUN_00ac79d0();
    void  FUN_00ac7de0(void* q, void* c);
};

struct OrderMgr {
    void* vptr;                            // +0x00
    u32 FUN_00bc3db0(u32 a);
    u8 FUN_00bc3df0(u32 a);
    u32 FUN_00bc5040(u32 a);
};

struct Mgr310 {
    void* vptr;                            // +0x00
    void FUN_00b453a0();
    void FUN_00b45410();
};

struct CCB {
    void FUN_00ccbb60();
};

struct EventLog {
    void PostFeedbackEvent();
};

struct RandomLCG {
    u32 RandomUint32Uniform(u32 n);
};

// opaque helpers
struct Obj9cec0 { u8 pad_00[0x28]; i32 mField28; };
struct ObjR     { u8 pad_00[0x08]; i32 mField08; };

struct Elem250 {
    u32   mFlags;                          // +0x00
    void* mpObj;                           // +0x04
    u8    pad_08[0x248];
};

// idle-block layouts used by the callback wrappers
struct IdleBlock {
    i32 mField00;                          // +0x00
    i32 mField04;                          // +0x04
    i32 mField08;                          // +0x08
    i32 mField0c;                          // +0x0c
    f32 mField10;                          // +0x10
    Creature* mpCreature14;                // +0x14
    void PickNewActivity();
};

struct S24 { f32 mT00; u8 mByte04; u8 pad05[3]; i32 mField08; };
struct S19 { u8 pad0[4]; i32 mField04; u8 mByte08; };
struct S28 { u8 pad0[0x10]; i32 mField10; };
struct Out9 { f32 f0; f32 f4; f32 f8; f32 fc; u8 b10; u8 b11; };

// ---------------------------------------------------------------------------
// creature
// ---------------------------------------------------------------------------

struct Creature {
    void* vptr;                            // +0x000
    u8  pad_004[0x30];                     // 0x004..0x034
    Locomotive mLoco;                      // +0x034
    Obj0xc0 mObjC0;                        // +0x0c0
    u32 mFlags110;                         // +0x110
    u8  pad_114[0x1b];                     // 0x114..0x12f
    u8  mByte12f;                          // +0x12f
    u8  pad_130[0x7];                      // 0x130..0x137
    u8  mByte137;                          // +0x137
    u8  pad_138[0xa14];                    // 0x138..0xb4c
    AgentOrderManager* mpAgentOrders;      // +0xb4c
    u8  pad_b50[0xe];                      // 0xb50..0xb5e
    u8  mByte_b5e;                         // +0xb5e

    // vtable dispatch helpers
    void  V_8c()      { (*(void (__thiscall**)(void*))(*(char**)this + 0x8c))(this); }
    void  V_84(u32 a, u32 b, u32 c) { (*(void (__thiscall**)(void*, u32, u32, u32))(*(char**)this + 0x84))(this, a, b, c); }
    void* V_b4(void* a) { return (*(void* (__thiscall**)(void*, void*))(*(char**)this + 0xb4))(this, a); }
    PtrVec* V_90()    { return (*(PtrVec* (__thiscall**)(void*))(*(char**)this + 0x90))(this); }

    // methods (extern)
    cTribe* GetTribe();
    Creature* FUN_00bc9b10();
    u32   FUN_00c0ee60();
    void  FUN_00c14750(i32 a);
    u8    FUN_00c0e0c0(u32 a);
    u32   PlayAnimation(u32 a, i32 b, i32 c);
    u32   InterruptAnimation(u32 a, i32 b, i32 c);
    u8    WaitForAnimEventOrEnd(u32 a, u32* out, u32 b, void* c, u32 d);
    u8    AnimationFinished(u32 a);
    u32   FUN_00c0b760();
    u8    FUN_00c0b770();
    void* FUN_00c22a70();
    void* FUN_00c22dc0();
    void* FUN_00c26120();
    u8    FUN_00c25480(void* a, u32 b);
    void  SetCurrentToolEffect(u32 a, i32 b);
    void  RebuildCitizenOrderListDefault();
    void  d0c0(u32 a, i32 b);
    void  ForceOrdersUpdate();
    u8    FUN_00c04710();
    void  FUN_00c0bf10(u32 a0, u32 a1, u32 a2, u32 a3, f32 f4, u32 a5, u32 a6, u32 a7, u32 a8, u32 a9, u32 a10);
};

// ---------------------------------------------------------------------------
// externs
// ---------------------------------------------------------------------------

extern f32 g_14007f4;
extern f32 g_1473c70;
extern f32 g_14853bc;
extern f32 g_1486110;
extern f32 g_1485720;
extern f32 g_13eb95c;
extern f32 g_14774d0;
extern u8  g_169f3b8;
extern i32 g_15d1164;
extern RandomLCG g_MathRandom;

void* FUN_00c9cec0(void* p);
void* FUN_00d99a10(u32 h);
void* FUN_00d998f0(void* p);
Strategy* FUN_00cd40b0();
Manager0* FUN_00b3d2b0();
OrderMgr* FUN_00b3d4e0();
TriggerMgr* FUN_00b3d4d0();
Mgr310* __stdcall FUN_00b3d310(void* o);
EventLog* __stdcall FUN_00b3d3e0(u32 a, u32 b, void* c, u32 d, u32 e, u32 f);

typedef void (__thiscall *ElemFn0)(void*, u32);

// ---------------------------------------------------------------------------
// 0x00da7780
// ---------------------------------------------------------------------------
// @ 0x00da7780
f32 FUN_00da7780(Creature* p)
{
    Ret7780* q = p->mLoco.FUN_00cee330();
    if (q == 0)
        return 0.0f;
    i32 v = q->mField12c;
    if (v == 3 || v == 0)
        return 0.0f;
    return 1.0f;
}

// @ 0x00da77b0
f32 FUN_00da77b0(Creature* p)
{
    Ret7780* q = p->mLoco.FUN_00cee330();
    if (q != 0 && q->mField12c != 2)
        return 1.0f;
    return 0.0f;
}

// @ 0x00da77d0
f32 FUN_00da77d0(Creature* p)
{
    OrderRec* q = p->mpAgentOrders->FirstPending();
    if (q != 0 && q->mField00 == 8)
        return 0.0f;
    return 1.0f;
}

// @ 0x00da77f0
bool FUN_00da77f0(Creature* p, i32, i32, i32, i32 mode)
{
    Ret7780* q = p->mLoco.FUN_00cee330();
    if (q != 0) {
        if (mode == 0) {
            void* c = FUN_00b3d2b0()->FUN_00ac79d0();
            FUN_00b3d2b0()->FUN_00ac7de0(q, c);
        } else if (mode == 1) {
            p->InterruptAnimation(0x4ffb325, -1, 0);
            return 1;
        }
    }
    return 0;
}

// @ 0x00da7850
void FUN_00da7850(Creature* p, i32, i32, i32, i32 mode)
{
    if (p->mLoco.FUN_00cee330() != 0 && mode == 1) {
        void* c = FUN_00b3d2b0()->FUN_00ac79d0();
        FUN_00b3d2b0()->FUN_00ac7de0(p->mLoco.FUN_00cee330(), c);
    }
}

// @ 0x00da7890
bool FUN_00da7890(Creature* p)
{
    Ret7780* q = p->mLoco.FUN_00cee330();
    if (q != 0) {
        u32 local = 0xffffffffu;
        if (p->WaitForAnimEventOrEnd(0xbfa50b5a, &local, 0x4ffb325, 0, 1) != 0)
            FUN_00b3d2b0()->FUN_00ac7de0(q, FUN_00b3d2b0()->FUN_00ac79d0());
    }
    return p->FUN_00c0e0c0(0x4ffb325);
}

// @ 0x00da7900
bool FUN_00da7900(Creature* p, i32, i32, i32, i32, u32* out)
{
    u32 anim = p->mpAgentOrders->mStimuli.Play(0, 0x4000000);
    if (anim != 0) {
        *out = p->PlayAnimation(0x5f73e48, 1, -1);
        return 1;
    }
    return 0;
}

// @ 0x00da7940
void FUN_00da7940(Creature* p)
{
    p->FUN_00c14750(0);
    p->mpAgentOrders->mStimuli.ClearAll(0, 0x4000000);
}

// @ 0x00da7970
bool FUN_00da7970(Creature* p, i32, i32, i32, i32, Out9* out)
{
    void* sub = (p != 0) ? (void*)&p->mObjC0 : 0;
    FUN_00b3d310(sub)->FUN_00b45410();
    p->V_8c();
    p->mByte12f = 0;
    if (p->GetTribe() != 0)
        p->GetTribe()->FUN_00c950f0(p);
    p->mObjC0.V_ec();
    p->mObjC0.V_54(0);
    p->mObjC0.FUN_00c41d60(&g_169f3b8);
    p->mObjC0.FUN_00c41d90(&g_169f3b8);
    if (p->mObjC0.V_58() != 0) {
        Strategy* st = FUN_00cd40b0();
        if (st != 0 && st->V_6c_a() != 0)
            st->V_6c_b(p)->FUN_00ccbb60();
    }
    out->f0 = (p->mObjC0.V_58() != 0) ? g_14853bc : g_14007f4;
    f32 c = g_13eb95c;
    out->f4 = c;
    out->f8 = c;
    out->fc = g_1485720;
    out->b10 = 0;
    out->b11 = 0;
    if (p->FUN_00c0b760() == 0 && p->mObjC0.V_58() != 0)
        FUN_00b3d3e0(0xee0e963f, 0x182cd6ce, p->mObjC0.V_2c(), 0, 1, 0)->PostFeedbackEvent();
    if (p->GetTribe() != 0)
        p->GetTribe()->V_9c(p, 0);
    return 1;
}

// @ 0x00da7af0
bool FUN_00da7af0(Creature* p)
{
    if (p->mByte_b5e == 0) {
        Obj0xc0* o = &p->mObjC0;
        if (FUN_00b3d4d0()->FUN_00adb360(o) == 0) {
            o->V_ec();
            p->FUN_00c14750(0);
        }
    }
    return 1;
}

// @ 0x00da7b40
bool FUN_00da7b40()
{
    return FUN_00b3d4d0()->mField2c == 2;
}

// @ 0x00da7b60
void FUN_00da7b60(Creature* p)
{
    if (p->mByte_b5e == 0) {
        p->mObjC0.V_ec();
        p->FUN_00c14750(0);
    }
}

// @ 0x00da7b90
bool FUN_00da7b90(Creature* p)
{
    u32 f = p->mFlags110;
    if ((f & 0x100) != 0) {
        if (p->FUN_00c0e0c0(0x48601c0) == 0)
            p->PlayAnimation(0x48601c0, 1, -1);
        return 1;
    }
    if (p->mByte137 == 0 && (f & 0x1000) == 0) {
        if (p->FUN_00c0e0c0(0x493840c) == 0)
            p->PlayAnimation(0x493840c, 1, -1);
        return 1;
    }
    p->FUN_00c0bf10(0, 0x10000, 0, 0x10000, g_1486110, 0, 0, 0, 0, 0, 0);
    return 0;
}

// @ 0x00da7c30
void FUN_00da7c30(Creature* p)
{
    if (p->mByte_b5e == 0)
        p->FUN_00c14750(0);
}

// @ 0x00da7c50
void FUN_00da7c50(Creature* p, i32, i32, i32, i32, IdleBlock* s)
{
    if (s->mField0c != 0 && s->mField08 != -1)
        p->GetTribe()->FindSpot(s->mField0c, s->mField08);
    if (p->mByte_b5e == 0) {
        p->mObjC0.V_ec();
        u8 b = (p->mObjC0.V_f8() == 0);
        p->FUN_00c14750(b);
    }
}

// @ 0x00da7cc0
void IdleBlock::PickNewActivity()
{
    Creature* c = mpCreature14;
    i32 a = 0;
    i32 b;
    if (c->FUN_00c0b770() != 0) {
        b = g_MathRandom.RandomUint32Uniform(3) + 0x2c39001;
        a = g_MathRandom.RandomUint32Uniform(2) + 2;
        if (c->FUN_00c22a70() != 0) {
            void* t = c->FUN_00c22dc0();
            if (t != 0) {
                Obj9cec0* u = (Obj9cec0*)FUN_00c9cec0(t);
                if (u->mField28 != 0) {
                    b = u->mField28;
                    a = 1;
                }
            }
        }
    } else {
        b = g_MathRandom.RandomUint32Uniform(5) + 0x2fc3661;
    }
    mField00 = 1;
    mField08 = b;
    mField0c = a;
    mpCreature14->PlayAnimation(b, 1, -1);
    mField10 = (mpCreature14->mObjC0.V_58() != 0) ? g_14007f4 : g_1473c70;
}

// @ 0x00da7d90
bool FUN_00da7d90(Creature* p, i32, i32, i32, i32, IdleBlock* s)
{
    s->mpCreature14 = p;
    s->mField00 = 0;
    s->mField04 = -1;
    s->mField08 = -1;
    s->mField0c = 0;
    p->d0c0(6, 1);
    return 1;
}

// @ 0x00da7dc0
void FUN_00da7dc0(Creature* p, i32, i32, i32, i32, IdleBlock* s)
{
    p->d0c0(6, 0);
    u8 b = (p->mObjC0.V_f8() == 0);
    p->FUN_00c14750(b);
    if (s->mField04 != -1) {
        cTribe* t = s->mpCreature14->GetTribe();
        t->mSub558.FUN_00cc7f90(s->mField04);
        s->mField04 = -1;
    }
}

// @ 0x00da7e20
bool FUN_00da7e20(Creature* p, Creature* q)
{
    Creature* a = p->FUN_00bc9b10();
    i32 iVar2 = (i32)a->GetTribe();
    i32 iVar3 = (i32)q->GetTribe();
    if (iVar3 == iVar2) {
        iVar2 = a->FUN_00c0ee60();
        iVar3 = q->FUN_00c0ee60();
        if (iVar3 == iVar2)
            return 1;
    }
    return 0;
}

// @ 0x00da7e70
bool FUN_00da7e70(Creature* p, i32, i32, i32, i32, S19* s)
{
    if (p->mpAgentOrders->mStimuli.Play(0, 0x10000) == 0)
        return 0;
    if (s->mByte08 != 0) {
        if (p->AnimationFinished(s->mField04) != 0) {
            p->mpAgentOrders->mStimuli.ClearAll(0, 0x10000);
            return 0;
        }
    } else {
        if (p->FUN_00c0e0c0(0x2481e14) == 0)
            p->PlayAnimation(0x2481e14, 1, -1);
    }
    return 1;
}

// @ 0x00da7ef0
void FUN_00da7ef0(Creature* p)
{
    p->FUN_00c14750(0);
    p->ForceOrdersUpdate();
}

// @ 0x00da7f10
void FUN_00da7f10(Creature* p)
{
    p->V_84(0, 0, 0);
    p->FUN_00c14750(0);
    p->ForceOrdersUpdate();
}

// @ 0x00da7f40
void FUN_00da7f40(Creature* p)
{
    if (p->mByte_b5e != 0)
        return;
    p->d0c0(6, 0);
    p->V_84(0, 0, 0);
    u8 b = (p->mObjC0.V_f8() == 0);
    p->FUN_00c14750(b);
    p->ForceOrdersUpdate();
}

// @ 0x00da7fa0
bool FUN_00da7fa0(Creature* p)
{
    p->mpAgentOrders->mStimuli.ClearAll(0, 0x10);
    return false;
}

// @ 0x00da7fc0
bool FUN_00da7fc0(Creature* p, i32, i32, i32, i32 mode, S24* s, i32, f32 dt)
{
    if (mode == 1) {
        i32 t = FUN_00b3d4d0()->mField2c;
        if (t != 1 && t != 2)
            return 0;
    }
    p->GetTribe();
    if (s->mField08 != -1) {
        OrderMgr* m = FUN_00b3d4e0();
        if (m->FUN_00bc3db0(s->mField08) != 0) {
            s->mT00 -= dt;
            if (s->mT00 < 0.0f)
                return 0;
        }
        s->mByte04 = 1;
        return m->FUN_00bc3df0(s->mField08) == 0;
    }
    return 0;
}

// @ 0x00da8050
void FUN_00da8050(Creature* p, i32, i32, i32, i32 mode, S24* s)
{
    cTribe* t = p->GetTribe();
    if (s->mField08 != -1) {
        if (t->mField26c == s->mField08) {
            t->mField26c = -1;
            if (s->mByte04 != 0)
                t->mTimer270.Restart();
        }
        FUN_00b3d4e0()->FUN_00bc5040(s->mField08);
        if (mode == 1 && FUN_00b3d4d0()->mField2c == 2)
            FUN_00b3d4d0()->goExit();
    }
    p->mObjC0.V_ec();
    p->FUN_00c14750(1);
    Mgr310* m = FUN_00b3d310(&p->mObjC0);
    m->FUN_00b453a0();
}

// @ 0x00da80f0
bool FUN_00da80f0(Creature* p, Creature* q)
{
    Creature* a = p->FUN_00bc9b10();
    if (a->GetTribe() == q->GetTribe())
        return true;
    return false;
}

// @ 0x00da8120
void FUN_00da8120(Creature* p, i32, i32, i32, i32, S28* s)
{
    if (s->mField10 != -1) {
        p->SetCurrentToolEffect(0, s->mField10);
        p->RebuildCitizenOrderListDefault();
    }
}

// @ 0x00da8150
bool GrowUp(Creature* p, i32, i32, i32, i32, u32* out)
{
    *out = p->InterruptAnimation(0x3a79244, -1, 0);
    p->mpAgentOrders->mStimuli.ClearAll(0, 0x200);
    return 1;
}

// @ 0x00da8190
f32 FUN_00da8190(Creature* p)
{
    i32 a = (i32)p->FUN_00c22a70();
    i32 b = (i32)p->FUN_00c26120();
    if (a != b)
        return 1.0f;
    return 0.0f;
}

// @ 0x00da81c0
bool FUN_00da81c0(Creature* p)
{
    return p->FUN_00c25480(p->FUN_00c26120(), 0) == 0;
}

// @ 0x00da81f0
u32 FUN_00da81f0(Creature* p)
{
    u32 h = p->mpAgentOrders->mStimuli.Play(0, 0x80);
    i32 v = p->mpAgentOrders->mRecs[0].mField78;
    bool b = false;
    if (v == 0x462854e)
        b = p->mpAgentOrders->mRecs[p->mpAgentOrders->mRecs[0].mField7c].mField00 >= 4;
    if (h == 0 && !b && v != 0x5218bb3 && v != 0x562c0fb)
        return 1;
    return 0;
}

// @ 0x00da82a0
Elem250* FUN_00da82a0(Elem250* first, Elem250* last, Elem250* dst)
{
    if (first != last) {
        Elem250* p = first;
        Elem250* d = dst;
        do {
            if (((u8)(p->mFlags >> 31) & 1) == 0) {
                ElemFn0 fn = *(ElemFn0*)p->mpObj;
                fn(&p->mpObj, 0);
            }
            ++p;
            ++d;
        } while (p != last);
        dst = d;
    }
    return dst;
}

// @ 0x00da82f0
f32 FUN_00da82f0(Creature* p, i32 v)
{
    i32 n = 0;
    PtrVec* vec = p->V_90();
    Creature** it = vec->mBegin;
    Creature** end = vec->mEnd;
    if (it != end) {
        do {
            n += ((*it)->mpAgentOrders->mRecs[0].mField78 == v);
            ++it;
        } while (it != end);
    }
    i32 cnt = (i32)(vec->mEnd - vec->mBegin);
    return (f32)n / (f32)(u32)cnt;
}

// @ 0x00da8370
bool FUN_00da8370(Creature* p, i32 v, void* a)
{
    if (p != 0) {
        OrderRec* q = p->mpAgentOrders->FirstPending();
        if (q != 0 && q->mField00 == (u32)v) {
            q->mRef28.operator=(a);
            return 1;
        }
    }
    return 0;
}

// @ 0x00da83b0
f32 FUN_00da83b0(Creature* p, i32 v)
{
    i32 n = 0;
    PtrVec* vec = p->V_90();
    Creature** it = vec->mBegin;
    Creature** end = vec->mEnd;
    if (it != end) {
        do {
            Creature* c = *it;
            i32 r = c->mLoco.mSub58.V_2c();
            n += (r == v);
            ++it;
        } while (it != end);
    }
    i32 cnt = (i32)(vec->mEnd - vec->mBegin);
    return (f32)n / (f32)(u32)cnt;
}

// @ 0x00da8430
f32 FUN_00da8430(Creature* p)
{
    u32 h = p->mpAgentOrders->mStimuli.Play(0, 0x4000000);
    if (h != 0) {
        AnimObj* a = (AnimObj*)FUN_00d99a10(h);
        if (a != 0) {
            if (a->V_8() != 0) {
                AnimObj* b = (AnimObj*)a->V_8();
                f32* f1 = b->V_2c();
                f32* f2 = (f32*)p->mObjC0.V_2c();
                f32 dx = f2[0] - f1[0];
                f32 dy = f2[1] - f1[1];
                f32 dz = f2[2] - f1[2];
                f32 d2 = dx * dx;
                d2 = d2 + dy * dy;
                d2 = d2 + dz * dz;
                if (d2 < g_14774d0)
                    return 1.0f;
            }
        }
    }
    return 0.0f;
}

// @ 0x00da84f0
long double FUN_00da84f0(Creature* p)
{
    OrderRec* q = p->mpAgentOrders->FirstPending();
    if (q == 0 || q->mField00 != 0x16)
        return 0;
    OrderSub39* r = &q->mSub39;
    u16 s = r->mField12;
    i32* src;
    if (s == 10 || s == 0x10) {
        if ((r->mByte10 & 0x30) != 0)
            src = (i32*)r->mField00;
        else
            src = (s != 0) ? (i32*)r : (i32*)0;
    } else {
        src = &g_15d1164;
    }
    ObjR* o = (ObjR*)p->V_b4((void*)*src);
    if (o != 0 && o->mField08 == 0x39)
        return g_1485720;
    return 0.0f;
}

// @ 0x00da8580
f32 FUN_00da8580(Creature* p, i32, i32, i32, BehaviorStimuli* s, u8* out)
{
    AnimObj* a = (AnimObj*)FUN_00d99a10(p->mpAgentOrders->mStimuli.Play(0x8000, 0));
    if (a != 0) {
        AnimObj* b = (AnimObj*)FUN_00d998f0(a);
        if (b != 0) {
            void* c = b->V_5c(0xd0036e08);
            AnimObj* d = (AnimObj*)b->V_c();
            if (d->V_20() != (void*)0x2a034cd) {
                if (c != 0 && ((Creature*)c)->FUN_00c04710() != 0)
                    goto clear;
                if (s != 0)
                    s->GetAny();
                s->mField04 = b;
                *out = 1;
                return 1.0f;
            }
        }
    }
clear:
    p->mpAgentOrders->mStimuli.ClearAll(0x8000, 0);
    return 0.0f;
}