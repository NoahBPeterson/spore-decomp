// s00d6ca50 - SP creature behaviour-state handlers (Activate / Tick / Deactivate).
//
// Every handler here is reachable only through the state table at
// .data:0x01583fb8 (records {uint32 key; fn Activate; fn Tick; fn Deactivate;}).
// The dispatcher passes the creature as the first stack argument, four unused
// context words in slots 2..5, the per-state behaviour object in slot 6 and
// (for MATING_CALL_Tick only) a frame delta in slot 7, so the whole family is
// __cdecl.
#include "types.h"

// ---------------------------------------------------------------------------
// generic vtable access
// ---------------------------------------------------------------------------
struct Vtbl { void* mSlots[0x120 / 4]; };

typedef void  (__thiscall *VFn_v)(void*);
typedef void* (__thiscall *VFn_p)(void*);
typedef char  (__thiscall *VFn_c)(void*);
typedef int   (__thiscall *VFn_i)(void*);
typedef float (__thiscall *VFn_f)(void*);
typedef void  (__thiscall *VFn_vi)(void*, int);
typedef void* (__thiscall *VFn_pi)(void*, int);
typedef char  (__thiscall *VFn_ci)(void*, int);
typedef void  (__thiscall *VFn_vii)(void*, int, int);
typedef void  (__thiscall *VFn_viii)(void*, int, int, int);
typedef float (__thiscall *VFn_fi)(void*, int);
typedef void* (__thiscall *VFn_pf)(void*, float*);
typedef void* (__thiscall *VFn_pii)(void*, int, int);

#define VSLOT(o, n) (((Vtbl*)*(void**)(o))->mSlots[(n) / 4])

// ---------------------------------------------------------------------------
// engine data
// ---------------------------------------------------------------------------
extern float DAT_01582e04;   // 0x01582e04  broken-path radius 1
extern float DAT_01582f8c;   // 0x01582f8c  broken-path radius 2

// ---------------------------------------------------------------------------
// free-function callees (call targets are relocation-masked by the checker)
// ---------------------------------------------------------------------------
extern void*        __cdecl   FUN_00b3d300();                                   // 0xb3d300 SP::NounManager
extern void*        __cdecl   FUN_00d51660(void* mate);                         // 0xd51660
extern void*        __cdecl   FUN_00d99980(void* stim);                         // 0xd99980 SP::GetAnimalFromStimulus
extern void*        __cdecl   FUN_00d40b40(int a);                              // 0xd40b40 SP::GetDesiredAvatarHerd
extern int          __cdecl   FUN_00435e90();                                   // 0x435e90 GetRecorderState
extern void         __cdecl   FUN_00571f80(int key, int state, float x, float y, float z); // 0x571f80 Start3dSoundByName
extern void*        __cdecl   FUN_0067dd80();                                   // 0x67dd80 SP::ModelManager
extern void*        __cdecl   FUN_0067dcc0();                                   // 0x67dcc0 MessageServer
extern void*        __stdcall FUN_00b3d310(void* a);                            // 0xb3d310
extern void*        __stdcall FUN_00b3d4d0(int key);                            // 0xb3d4d0 GetTriggerMgr

// ---------------------------------------------------------------------------
// thiscall member callees on the noun manager / helper objects
// ---------------------------------------------------------------------------
struct Engine {
    void*  FUN_00b1fdb0();              // 0xb1fdb0 cGameNounManager::GetAvatar
    void*  FUN_00b1f9c0();              // 0xb1f9c0 cSpaceInventoryItem::GetItemID
    void   FUN_00d4b180(int mate);      // 0xd4b180 cSPDramaManager::MatedWith
    void*  FUN_00c6cf10(void* pos, void* v, int z);  // 0xc6cf10 cHerd::AddEggInNest
    float* FUN_00c6acc0();              // 0xc6acc0 cNearNoun::GetPosition
    void   FUN_00b48770(int a);         // 0xb48770
    void   FUN_00b45410();              // 0xb45410
    void   FUN_00b453a0();              // 0xb453a0
    void   FUN_00ae09b0(void* target);  // 0xae09b0 cTriggerMgr::PostAction
    void   FUN_00bd0bcbc8(void* a, int b, int c);  // message-server slot 0x14
    void   FUN_00b5f950(void* p, int ref);         // 0xb5f950
};

// small stack helper objects
struct ActionTarget {
    ActionTarget* FUN_00ad7a30(void* a, int b);   // 0xad7a30 ctor
    void          FUN_00ad7ad0();                 // 0xad7ad0 dtor
};

// space-inventory item container returned by cSpaceInventoryItem::GetItemID
struct Container { uint32_t* mBegin; uint32_t* mEnd; };

// ---------------------------------------------------------------------------
// behaviour stimuli (embedded at behaviour-tree + 8)
// ---------------------------------------------------------------------------
struct BehaviorStimuli {
    void* mPad;                             // keeps the member 4 bytes wide
    void  ClearAll(int mask, int flags);    // 0xbc98f0
    void* Play(int flags, int a);           // 0xbc96a0
};

struct BehaviorTree {
    uint8_t         mPad00[8];              // +0x000
    BehaviorStimuli mStimuli;               // +0x008
    uint8_t         mPad0c[0x1d8 - 0x0c];   // +0x00c
    uint32_t        mKey;                   // +0x1d8  state hash for this tree
};

// ---------------------------------------------------------------------------
// per-state behaviour objects
// ---------------------------------------------------------------------------
struct MatingCallState { uint32_t mMode; float mTime; float mThreshold; };
struct MateLeadState   { uint32_t mMode; uint32_t mPad04; uint8_t mFlag08; };
struct StateD3c0       { uint32_t mMode; uint32_t mPad04; uint8_t mFlag08; uint8_t mPad09[3]; uint32_t mField0c; };

struct AutoRefCount { void* mpObj; void operator=(void* p); };

struct BehaviorState {
    uint32_t     mMode;     // +0x00
    uint8_t      mFlag04;   // +0x04
    uint8_t      mPad05[3];
    AutoRefCount mEgg;      // +0x08
    void*        mpPrev;    // +0x0c
    int32_t      mAnim;     // +0x10
};

// object held by BehaviorState::mEgg (a behaviour-tree node wrapper)
struct StateNode {
    uint8_t  mPad0000[0x34];            // +0x0000
    uint8_t  mSub34;                    // +0x0034  embedded dispatchable sub-object
    uint8_t  mPad0035[0x84 - 0x35];     // +0x0035
    uint32_t mFlags84;                  // +0x0084
    uint8_t  mPad0088[0xa5 - 0x88];     // +0x0088
    uint8_t  mFlagA5;                   // +0x00a5
    uint8_t  mPad00a6[0x1f0 - 0xa6];    // +0x00a6
    int32_t  mField1f0;                 // +0x01f0
};

// ---------------------------------------------------------------------------
// object at creature + 0xc0 (locomotive object; vtable-dispatched)
// ---------------------------------------------------------------------------
struct Locomotive {
    Vtbl*   mpVtable;                   // +0x00
    uint8_t mPad04[0x60];               // methods only; layout is opaque
    void* FUN_00c41ec0();               // 0xc41ec0 GetGoal
    char  FUN_00c42e20();               // 0xc42e20 IsNearGoal
};

// ---------------------------------------------------------------------------
// creature (first stack argument of every handler)
// ---------------------------------------------------------------------------
// creature state bit-pool at +0xb58 (bits 4, 6 and 9 are read/written here)
struct CreatureFlags {
    uint32_t mBit0_3   : 4;
    uint32_t mBit4     : 1;
    uint32_t mBit5     : 1;
    uint32_t mBit6     : 1;
    uint32_t mBit7_8   : 2;
    uint32_t mBit9     : 1;
    uint32_t mBit10_31 : 22;
};

struct Creature {
    Vtbl*         mpVtable;             // +0x0000
    uint8_t       mPad0004[0xc0 - 0x04];
    Locomotive    mLoco;                // +0x00c0
    uint8_t       mPadLoco[0xb4c - 0xc0 - sizeof(Locomotive)];
    BehaviorTree* mpBehaviorTree;       // +0x0b4c
    uint32_t      mB50;                 // +0x0b50
    uint32_t      mB54;                 // +0x0b54
    CreatureFlags mFlags;               // +0x0b58  bit 4 / 6 / 9 state bits
    uint16_t      mB5c;                 // +0x0b5c
    uint8_t       mDead;                // +0x0b5e
    uint8_t       mB5f;                 // +0x0b5f

    // ---- thiscall methods (this == creature) --------------------------------
    int   FUN_00c12190(int anim, int a, int b);      // 0xc12190 PlayAnimation
    void  FUN_00c12310(int anim, int a, int b);      // 0xc12310 InterruptAnimation
    char  FUN_00c123f0(int anim);                    // 0xc123f0 AnimationFinished
    char  FUN_00c12400(int anim);                    // 0xc12400 AnimationFinished
    char  FUN_00c14ef0(int ev, void* out, int a, int b, int c);  // 0xc14ef0 WaitForAnimEventOrEnd
    void  FUN_00c17350(int a, int b);                // 0xc17350
    void  FUN_00c1d460(int a, int b);                // 0xc1d460
    void  FUN_00c1aed0(int a, int b);                // 0xc1aed0 SetStealthed
    void  FUN_00c1ad10(int a);                       // 0xc1ad10 SetSprinting
    char  FUN_00c0e0c0(int a);                       // 0xc0e0c0
    int   FUN_00c02c70();                            // 0xc02c70
    void  FUN_00c02c20(int a);                       // 0xc02c20
    void* FUN_00c0ee90();                            // 0xc0ee90 ApplyCombatTarget
    void  FUN_00c0d1e0(int a);                       // 0xc0d1e0
    void  FUN_00c0d240();                            // 0xc0d240 IsAnimationQueuedOrCurrent
    void  FUN_00c14750(int a);                       // 0xc14750
    void* FUN_00c04590();                            // 0xc04590 Get
    void  FUN_00c1c1d0(int a, float* pos, float s1, float s2);               // 0xc1c1d0
    void  FUN_00c1c5c0(int a, float* pos, float* facing, float s, float a5); // 0xc1c5c0
};

// herd returned by GetDesiredAvatarHerd; the node layout is opaque here
struct Herd {
    uint8_t mPad0000[0x160];
    void*   mpMember;                   // +0x160
};

// ---------------------------------------------------------------------------
// 0x00d6ca50 - SP::MATING_CALL_Deactivate
// ---------------------------------------------------------------------------
// @ 0x00d6ca50
void __cdecl FUN_00d6ca50(void* c, int p2, int p3, int p4, int p5, void* state, int p7, float dt)
{
    (void)p2; (void)p3; (void)p4; (void)p5; (void)dt;
    Creature* cr = (Creature*)c;
    ((VFn_viii)VSLOT(c, 0x84))(c, 0, 0, 0);
    cr->FUN_00c17350(0xac5595f7, 0);
    cr->mpBehaviorTree->mStimuli.ClearAll(0x40, 0);
    if (cr->mDead == 0 && ((MatingCallState*)state)->mMode <= 1)
        cr->FUN_00c12190(0x4a0f550, 1, -1);
}

// ---------------------------------------------------------------------------
// 0x00d6cab0 - SP::MATING_CALL_Tick
// ---------------------------------------------------------------------------
// @ 0x00d6cab0
char __cdecl FUN_00d6cab0(void* c, int p2, int p3, int p4, int p5, void* state, int p7, float dt)
{
    (void)p2; (void)p3; (void)p4; (void)p5;
    Creature* cr = (Creature*)c;
    MatingCallState* st = (MatingCallState*)state;
    if (((Creature*)((Engine*)FUN_00b3d300())->FUN_00b1fdb0())->mDead != 0)
        return 0;

    switch (st->mMode) {
    case 0:
        cr->FUN_00c12310(0x4a0f53f, -1, 0);
        cr->FUN_00c12190(0x4a0f546, 1, -1);
        st->mMode = 1;
        break;
    case 1:
        if (cr->FUN_00c0e0c0(0x4a0f546) == 0)
            cr->FUN_00c12190(0x4a0f546, 1, -1);
        st->mTime += dt;
        if (st->mTime > st->mThreshold) {
            cr->FUN_00c12190(0x265d18d, 1, -1);
            st->mMode = 2;
            return 1;
        }
        break;
    case 2:
        if (cr->FUN_00c0e0c0(0x4a0f550) == 0)
            return 0;
        break;
    default:
        break;
    }
    return 1;
}

// ---------------------------------------------------------------------------
// 0x00d6cbc0 - SP::IN_HEAT_Activate
// ---------------------------------------------------------------------------
// @ 0x00d6cbc0
char __cdecl FUN_00d6cbc0(void* c, int p2, int p3, int p4, int p5, void* state, int p7, float dt)
{
    (void)p2; (void)p3; (void)p4; (void)p5; (void)state; (void)dt;
    void* avatar = ((Engine*)FUN_00b3d300())->FUN_00b1fdb0();
    if (avatar != 0)
        ((VFn_viii)VSLOT(c, 0x84))(c, (int)((char*)avatar + 0x5a8), 1, 0);
    ((Creature*)c)->FUN_00c1d460(0x9005e011, 0x9005e011);
    return 1;
}

// ---------------------------------------------------------------------------
// 0x00d6cc30 - SP::MATE_LEAD_Deactivate
// ---------------------------------------------------------------------------
// @ 0x00d6cc30
void __cdecl FUN_00d6cc30(void* c, int p2, int p3, int p4, int p5, void* state, int p7, float dt)
{
    (void)p2; (void)p3; (void)p4; (void)p5; (void)dt;
    Creature* cr = (Creature*)c;
    int mate = (int)cr->FUN_00c0ee90();
    if (mate != 0 && ((MateLeadState*)state)->mFlag08 != 0) {
        ((Engine*)FUN_00d51660((void*)mate))->FUN_00d4b180(mate);
    }
    ((VFn_viii)VSLOT(c, 0x84))(c, 0, 0, 0);
    cr->mFlags.mBit4 = 0;
    cr->mpBehaviorTree->mStimuli.ClearAll(8, 0);
    cr->FUN_00c17350(0x9005e011, 0);
    cr->mFlags.mBit6 = 0;
}

// ---------------------------------------------------------------------------
// 0x00d6cca0
// ---------------------------------------------------------------------------
// @ 0x00d6cca0
char __cdecl FUN_00d6cca0(void* c, int p2, int p3, int p4, int p5, void* state, int p7, float dt)
{
    (void)p2; (void)p3; (void)p4; (void)p5; (void)dt;
    Creature* cr = (Creature*)c;
    ((MatingCallState*)state)->mMode = 0;
    cr->FUN_00c1d460(0x9005e011, 0x9005e011);
    cr->FUN_00c1aed0(0, 0);
    return 1;
}

// ---------------------------------------------------------------------------
// 0x00d6ccd0
// ---------------------------------------------------------------------------
// @ 0x00d6ccd0
void __cdecl FUN_00d6ccd0(void* c, int p2, int p3, int p4, int p5, void* state, int p7, float dt)
{
    (void)p2; (void)p3; (void)p4; (void)p5; (void)state; (void)dt;
    Creature* cr = (Creature*)c;
    cr->FUN_00c17350(0x9005e011, 0);
    ((VFn_viii)VSLOT(c, 0x84))(c, 0, 0, 0);
}

// ---------------------------------------------------------------------------
// 0x00d6cd00 - SP::MATE_FOLLOW_Tick
// ---------------------------------------------------------------------------
// @ 0x00d6cd00
char __cdecl FUN_00d6cd00(void* c, int p2, int p3, int p4, int p5, void* state, int p7, float dt)
{
    (void)p2; (void)p3; (void)p4; (void)p5; (void)dt;
    Creature* cr = (Creature*)c;
    BehaviorState* st = (BehaviorState*)state;
    switch (st->mMode) {
    case 0: {
        void* stim = cr->mpBehaviorTree->mStimuli.Play(8, 0);
        if (stim == 0)
            return 0;
        Creature* animal = (Creature*)FUN_00d99980(stim);
        if (animal != 0 && animal->mpBehaviorTree->mKey == 0x2d852f0) {
            st->mMode = 1;
            ((VFn_viii)VSLOT(c, 0x84))(c, (int)animal + 0x5a8, 1, 0);
            cr->mpBehaviorTree->mStimuli.ClearAll(8, 0);
        }
        break;
    }
    case 1: {
        Creature* mate = (Creature*)cr->FUN_00c0ee90();
        if (mate == 0)
            return 0;
        if (mate->mpBehaviorTree->mKey != 0x2d852f0)
            return 0;
        break;
    }
    default:
        break;
    }
    return 1;
}

// ---------------------------------------------------------------------------
// 0x00d6cdb0 - SP::HATCH_Activate
// ---------------------------------------------------------------------------
// @ 0x00d6cdb0
char __cdecl FUN_00d6cdb0(void* c, int p2, int p3, int p4, int p5, void* state, int p7, float dt)
{
    (void)p2; (void)p3; (void)p4; (void)p5; (void)state; (void)dt;
    ((Creature*)c)->FUN_00c12310(0xf14faa57, -1, 0);
    return 1;
}

// ---------------------------------------------------------------------------
// 0x00d6cdd0 - SP::HATCH_Deactivate
// ---------------------------------------------------------------------------
// @ 0x00d6cdd0
void __cdecl FUN_00d6cdd0(void* c, int p2, int p3, int p4, int p5, void* state, int p7, float dt)
{
    (void)p2; (void)p3; (void)p4; (void)p5; (void)state; (void)dt;
    ((Creature*)c)->mpBehaviorTree->mStimuli.ClearAll(0, 0x1000000);
}

// ---------------------------------------------------------------------------
// 0x00d6cdf0 - SP::HATCH_Tick
// ---------------------------------------------------------------------------
// @ 0x00d6cdf0
char __cdecl FUN_00d6cdf0(void* c, int p2, int p3, int p4, int p5, void* state, int p7, float dt)
{
    (void)p2; (void)p3; (void)p4; (void)p5; (void)state; (void)dt;
    return ((Creature*)c)->FUN_00c123f0(0xf14faa57) == 0;
}

// ---------------------------------------------------------------------------
// 0x00d6d3c0
// ---------------------------------------------------------------------------
// @ 0x00d6d3c0
char __cdecl FUN_00d6d3c0(void* c, int p2, int p3, int p4, int p5, void* state, int p7, float dt)
{
    (void)p2; (void)p3; (void)p4; (void)p5; (void)dt;
    Creature* cr = (Creature*)c;
    StateD3c0* st = (StateD3c0*)state;
    st->mMode = 0;
    st->mFlag08 = 0;
    st->mField0c = 0;
    cr->mFlags.mBit4 = 1;
    cr->FUN_00c1d460(0x9005e011, 0x9005e011);
    ((VFn_viii)VSLOT(c, 0x84))(c, 0, 0, 0);
    cr->FUN_00c1aed0(0, 0);
    cr->FUN_00c1ad10(0);
    short b9 = cr->mFlags.mBit9;
    if (b9) {
        Container* list = (Container*)((Engine*)FUN_00b3d300())->FUN_00b1f9c0();
        uint32_t* it = list->mBegin;
        uint32_t* end = list->mEnd;
        for (; it != end; ++it)
            ((Creature*)*it)->FUN_00c1ad10(0);
    }
    return 1;
}

// ---------------------------------------------------------------------------
// 0x00d6d460
// ---------------------------------------------------------------------------
// @ 0x00d6d460
char __cdecl FUN_00d6d460(void* c, int p2, int p3, int p4, int p5, void* state, int p7, float dt)
{
    (void)p2; (void)p3; (void)p4; (void)p5; (void)dt;
    Creature* cr = (Creature*)c;
    BehaviorState* st = (BehaviorState*)state;
    if (st != 0) {
        st->mEgg.mpObj = 0;
        st->mpPrev = 0;
    }
    st->mFlag04 = 0;
    st->mAnim = 0;
    short b9 = cr->mFlags.mBit9;
    if (b9 != 0) {
        Herd* herd = (Herd*)FUN_00d40b40(1);
        if (herd != 0) {
            void* member = herd->mpMember;
            if (member != 0) {
                st->mMode = 0;
                void* sub = (char*)member + 0x34;
                float* pos = (float*)((VFn_p)VSLOT(sub, 0x2c))(sub);
                cr->FUN_00c1c1d0(2, pos, 0.1f, 1.0f);
                void* prev = st->mpPrev;
                if (member != prev) {
                    ((VFn_v)VSLOT(member, 0))(member);
                    st->mpPrev = member;
                    if (prev != 0)
                        ((VFn_v)VSLOT(prev, 4))(prev);
                }
            }
        }
        return 1;
    }
    st->mMode = 0;
    void* nearNoun = cr->FUN_00c04590();
    cr->FUN_00c1c1d0(2, ((Engine*)nearNoun)->FUN_00c6acc0(), 0.5f, 2.0f);
    return 1;
}

// ---------------------------------------------------------------------------
// 0x00d6d1d0 - SP::BROKEN_Tick
// ---------------------------------------------------------------------------
// @ 0x00d6d1d0
char __cdecl FUN_00d6d1d0(void* c, int p2, int p3, int p4, int p5, void* state, int p7, float dt)
{
    (void)p2; (void)p3; (void)p5; (void)state; (void)dt;
    Creature* cr = (Creature*)c;
    short b4 = cr->mFlags.mBit4;
    if (b4 == 0)
        return 0;

    Creature* avatar = (Creature*)((Engine*)FUN_00b3d300())->FUN_00b1fdb0();
    if (avatar->mDead != 0)
        return 0;

    Locomotive* avLoco = &avatar->mLoco;
    float* p = (float*)((VFn_p)VSLOT(avLoco, 0x2c))(avLoco);
    float pos[3];
    pos[0] = p[0];
    pos[1] = p[1];
    pos[2] = p[2];
    float radius = DAT_01582e04;

    if ((p4 & 0x4000) != 0) {
        void* nearNoun = cr->FUN_00c04590();
        float* q = ((Engine*)nearNoun)->FUN_00c6acc0();
        float* p2f = (float*)((VFn_p)VSLOT(avLoco, 0x2c))(avLoco);
        float dx = p2f[0] - q[0];
        float dy = p2f[1] - q[1];
        float dz = p2f[2] - q[2];
        if (dx * dx + dy * dy + dz * dz > DAT_01582f8c * DAT_01582f8c) {
            pos[0] = q[0];
            pos[1] = q[1];
            pos[2] = q[2];
            radius = DAT_01582f8c;
        }
    }

    Locomotive* loco = &cr->mLoco;
    void* goal = loco->FUN_00c41ec0();
    bool doMove = (*(int*)((char*)goal + 0x5c) == 0);
    if (!doMove) {
        float dx = *(float*)((char*)goal + 0x14) - pos[0];
        float dy = *(float*)((char*)goal + 0x18) - pos[1];
        float dz = *(float*)((char*)goal + 0x1c) - pos[2];
        if (dx * dx + dy * dy + dz * dz > radius * radius)
            doMove = true;
    }
    if (doMove) {
        cr->FUN_00c14750(0);
        float s = ((VFn_f)VSLOT(loco, 0x70))(loco);
        float s6 = s * 6.0f;
        float s3 = ((VFn_fi)VSLOT(loco, 0x70))(loco, s6) * 3.0f;
        cr->FUN_00c1c1d0(2, pos, s3, s6);
    }

    if (loco->FUN_00c42e20()) {
        if (((VFn_c)VSLOT(loco, 0x48))(loco)) {
            if (cr->FUN_00c0e0c0(0x915f7deb) == 0)
                cr->FUN_00c12190(0x915f7deb, 1, -1);
        }
    }
    return 1;
}

// ---------------------------------------------------------------------------
// 0x00d6d530
// ---------------------------------------------------------------------------
// @ 0x00d6d530
void __cdecl FUN_00d6d530(void* c, int p2, int p3, int p4, int p5, void* state, int p7, float dt)
{
    (void)p2; (void)p3; (void)p4; (void)dt;
    Creature* cr = (Creature*)c;
    BehaviorState* st = (BehaviorState*)state;
    if (p5 == 1 && st->mEgg.mpObj != 0)
        ((StateNode*)st->mEgg.mpObj)->mField1f0 = 0x7fffffff;
    if (st->mEgg.mpObj != 0) {
        ((StateNode*)st->mEgg.mpObj)->mFlagA5 = 0;
        void* sub = (char*)st->mEgg.mpObj + 0x34;
        ((Engine*)FUN_00b3d310(sub))->FUN_00b453a0();
    }
    cr->FUN_00c0d240();
    ((VFn_viii)VSLOT(c, 0x84))(c, 0, 0, 0);
    if (st->mpPrev != 0)
        ((VFn_v)VSLOT(st->mpPrev, 4))(st->mpPrev);
    if (st->mEgg.mpObj != 0)
        ((VFn_v)VSLOT(st->mEgg.mpObj, 4))(st->mEgg.mpObj);
}

// ---------------------------------------------------------------------------
// 0x00d6ce10 - SP::LAY_EGG_Tick
// ---------------------------------------------------------------------------
// @ 0x00d6ce10
char __cdecl FUN_00d6ce10(void* c, int p2, int p3, int p4, int p5, void* state, int p7, float dt)
{
    (void)p2; (void)p3; (void)p5; (void)dt;
    Creature* cr = (Creature*)c;
    BehaviorState* st = (BehaviorState*)state;

    if (cr->FUN_00c02c70() <= 0 && st->mFlag04 == 0)
        return 0;

    Locomotive* loco = &cr->mLoco;

    switch (st->mMode) {
    case 0:
        if (loco->FUN_00c42e20()) {
            st->mMode = 1;
            st->mAnim = cr->FUN_00c12190(0x5e3e754, 1, -1);
            cr->FUN_00c12190(0x5e3e75b, 0, -1);
        }
        break;

    case 1:
        if (st->mFlag04 != 0) {
            if (cr->FUN_00c12400(st->mAnim) != 0) {
                float speed = ((VFn_f)VSLOT(loco, 0x74))(loco) + 1.0f;
                float dir[3];
                ((VFn_pf)VSLOT(loco, 0x5c))(loco, dir);
                float* cur = (float*)((VFn_p)VSLOT(loco, 0x2c))(loco);
                float target[3];
                target[0] = cur[0] + dir[0] * speed;
                target[1] = cur[1] + dir[1] * speed;
                target[2] = cur[2] + dir[2] * speed;
                float facing[3];
                ((VFn_pf)VSLOT(loco, 0x5c))(loco, facing);
                cr->FUN_00c1c5c0(2, target, facing, 0.5f, 1.0f);
                void* eggSub = (char*)st->mEgg.mpObj + 0x34;
                cr->FUN_00c0d1e0((int)((VFn_p)VSLOT(eggSub, 0x2c))(eggSub));
                st->mAnim = cr->FUN_00c12190(0x5e3e75f, 0, -1);
                st->mMode = 2;
                return 1;
            }
        } else {
            float out[6];
            char r = cr->FUN_00c14ef0(0x58113b7b, out, -1, 0, 1);
            st->mFlag04 = r;
            if (r != 0 || cr->FUN_00c12400(st->mAnim) != 0) {
                int count;
                short b9v = cr->mFlags.mBit9;
                if (b9v) {
                    count = 0;
                } else {
                    int n = cr->FUN_00c02c70() - 1;
                    count = (n > 0) ? n : 0;
                }
                cr->FUN_00c02c20(count);

                short flag9 = cr->mFlags.mBit9;
                void* v = ((VFn_pii)VSLOT(loco, 0x30))(loco, flag9, 6);
                st->mEgg = ((Engine*)cr->FUN_00c04590())->FUN_00c6cf10(
                    (float*)((VFn_p)VSLOT(loco, 0x2c))(loco), v, 0);

                void* mm = FUN_0067dd80();
                void* res = ((VFn_pi)VSLOT(mm, 0x1c))(mm, 0xeb9968);
                if (res != 0)
                    ((VFn_v)VSLOT(res, 0))(res);

                ((StateNode*)st->mEgg.mpObj)->mFlags84 |= 8;
                void* nodeSub = (char*)st->mEgg.mpObj + 0x34;
                ((VFn_vi)VSLOT(nodeSub, 0xa0))(nodeSub, (int)res);
                ((Engine*)FUN_00b3d310(st->mEgg.mpObj))->FUN_00b48770(1);
                void* sub34 = (st->mEgg.mpObj != 0) ? (char*)st->mEgg.mpObj + 0x34 : 0;
                ((Engine*)FUN_00b3d310(sub34))->FUN_00b45410();

                short b9b = cr->mFlags.mBit9;
                if (b9b) {
                    void* actSub = (st->mEgg.mpObj != 0) ? (char*)st->mEgg.mpObj + 0x34 : 0;
                    ActionTarget target_;
                    ActionTarget* pat = target_.FUN_00ad7a30(actSub, 0);
                    ((Engine*)FUN_00b3d4d0(0x28930a2c))->FUN_00ae09b0(pat);
                    target_.FUN_00ad7ad0();
                    void* ms = FUN_0067dcc0();
                    ((VFn_viii)VSLOT(ms, 0x14))(ms, 0x445f729, 0, 0);
                }

                if ((p4 & 0x100000) != 0) {
                    float* sp = (float*)((VFn_p)VSLOT(loco, 0x2c))(loco);
                    int rec = FUN_00435e90();
                    FUN_00571f80(0xbd0bcbc8, rec, sp[0], sp[1], sp[2]);
                }

                if (res != 0)
                    ((VFn_v)VSLOT(res, 4))(res);
            }
        }
        break;

    case 2:
        if (cr->FUN_00c12400(st->mAnim) != 0)
            return 0;
        break;

    default:
        break;
    }
    return 1;
}