// src/game/SPGonzago/SPCreatureMate.cpp -- migrated from slice(s) s00d6ca50 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCreatureMate.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "nSPBehaviorTree/behavior_stimuli.h"
#include "SP/cSPCreatureBase.h"
#include "SP/cLocomotiveObject.h"

// unnamed retail callees and globals (address in the comment)
extern float DAT_01582e04;   // 0x01582e04  broken-path radius 1
extern float DAT_01582f8c;   // 0x01582f8c  broken-path radius 2
extern void*        __cdecl   FUN_00b3d300();                                   // 0xb3d300 SP::NounManager
extern void*        __cdecl   FUN_00d51660(void* mate);                         // 0xd51660
extern void*        __cdecl   FUN_00d99980(void* stim);                         // 0xd99980 SP::GetAnimalFromStimulus
extern void*        __cdecl   FUN_00d40b40(int a);                              // 0xd40b40 SP::GetDesiredAvatarHerd

// ---- items of slice s00d6ca50 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vtbl { void* mSlots[0x120 / 4]; };
typedef void  (__thiscall *VFn_v)(void*);
typedef void* (__thiscall *VFn_p)(void*);
typedef char  (__thiscall *VFn_c)(void*);
typedef float (__thiscall *VFn_f)(void*);
typedef void  (__thiscall *VFn_viii)(void*, int, int, int);
typedef float (__thiscall *VFn_fi)(void*, int);
#define VSLOT(o, n) (((Vtbl*)*(void**)(o))->mSlots[(n) / 4])
extern float DAT_01582e04;   // 0x01582e04  broken-path radius 1
extern float DAT_01582f8c;   // 0x01582f8c  broken-path radius 2
extern void*        __cdecl   FUN_00b3d300();                                   // 0xb3d300 SP::NounManager
extern void*        __cdecl   FUN_00d51660(void* mate);                         // 0xd51660
extern void*        __cdecl   FUN_00d99980(void* stim);                         // 0xd99980 SP::GetAnimalFromStimulus
extern void*        __cdecl   FUN_00d40b40(int a);                              // 0xd40b40 SP::GetDesiredAvatarHerd
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
struct Container { uint32_t* mBegin; uint32_t* mEnd; };
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
struct Locomotive {
    Vtbl*   mpVtable;                   // +0x00
    uint8_t mPad04[0x60];               // methods only; layout is opaque
    void* FUN_00c41ec0();               // 0xc41ec0 GetGoal
    char  FUN_00c42e20();               // 0xc42e20 IsNearGoal
};
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
struct Herd {
    uint8_t mPad0000[0x160];
    void*   mpMember;                   // +0x160
};
// ---- items of slice s00d6ca50 end

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

// @ 0x00d6ccd0
void __cdecl FUN_00d6ccd0(void* c, int p2, int p3, int p4, int p5, void* state, int p7, float dt)
{
    (void)p2; (void)p3; (void)p4; (void)p5; (void)state; (void)dt;
    Creature* cr = (Creature*)c;
    cr->FUN_00c17350(0x9005e011, 0);
    ((VFn_viii)VSLOT(c, 0x84))(c, 0, 0, 0);
}

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

// @ 0x00d6cdb0
char __cdecl FUN_00d6cdb0(void* c, int p2, int p3, int p4, int p5, void* state, int p7, float dt)
{
    (void)p2; (void)p3; (void)p4; (void)p5; (void)state; (void)dt;
    ((Creature*)c)->FUN_00c12310(0xf14faa57, -1, 0);
    return 1;
}

// @ 0x00d6cdd0
void __cdecl FUN_00d6cdd0(void* c, int p2, int p3, int p4, int p5, void* state, int p7, float dt)
{
    (void)p2; (void)p3; (void)p4; (void)p5; (void)state; (void)dt;
    ((Creature*)c)->mpBehaviorTree->mStimuli.ClearAll(0, 0x1000000);
}

// @ 0x00d6cdf0
char __cdecl FUN_00d6cdf0(void* c, int p2, int p3, int p4, int p5, void* state, int p7, float dt)
{
    (void)p2; (void)p3; (void)p4; (void)p5; (void)state; (void)dt;
    return ((Creature*)c)->FUN_00c123f0(0xf14faa57) == 0;
}

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
