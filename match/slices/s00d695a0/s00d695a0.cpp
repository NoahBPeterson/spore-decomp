// Slice s00d695a0: SP::TRIBE_FIGHT_Enter-style state initialiser (0x00d695a0).
// /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
//
// Shares the creature layout and the per-node state record with the sibling
// behaviour slice s00d697a0 (SP::TRIBE_FIGHT_Tick).  The record is 0x38 bytes:
//   +0x00 mTarget, +0x04 mId, +0x08 mSlot, +0x0c mStratHandle,
//   +0x10 mTimer0, +0x14 mTimer1, +0x18 mTimer2, +0x1c mAttackTimer,
//   +0x20 mAttackReset, +0x24 mB24, +0x25 mB25, +0x26 mNoRetarget,
//   +0x28 mEventAnim, +0x2c mAnim, +0x30 mHintArg, +0x34 mRef.
#include "types.h"

struct Vec3 { float x, y, z; };

struct Loco {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21();
    virtual bool IsMovingFast();                       // +0x58
    virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26();
    virtual void s27(); virtual void s28();
    virtual float GetRadius();                         // +0x74
};

struct RefCounted {
    virtual void AddRef0();                            // +0x00
    virtual void Release4();                           // +0x04
};

struct Obj {
    virtual void v00(); virtual void v04();
    virtual Obj* GetOwner();                           // +0x08
    virtual void* GetHandle();                         // +0x0c
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual int  GetTypeID();                          // +0x20
    virtual void v24(); virtual void v28();
    virtual Vec3* GetPosition();                       // +0x2c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void AddRef60();                           // +0x60
    virtual void Release64();                          // +0x64
};

struct Citizen {                                       // tribe creature sub-interface
    int GetTribe();                                    // 0x00c22f50
};

struct BehStim {                                       // behaviour tree stimuli at +8
    int Play(uint32_t a, uint32_t flags);              // 0x00bc96a0
};

struct Behav {
    uint32_t pad0[2];
};

struct HandleList {                                    // creature+0x34
    uint32_t pad00;
    void**   mpBegin;                                  // +0x04
    void**   mpEnd;                                    // +0x08
    void* FUN_00cee330();                              // 0x00cee330 (first handle or 0)
};

struct WorldManager {                                  // returned by 0x00b3d480
    void FUN_00acd2d0(void* obj);                      // 0x00acd2d0, thiscall ret 4
};

struct Container {                                     // returned by 0x00b3d2b0
    void*      FUN_00ac79d0();                         // 0x00ac79d0 ([+0x1c]+0x34)
    void       FUN_00ac7de0(void* obj, void* container);  // thiscall, ret 8
};

struct cSPCreatureBase {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
    virtual void s32();
    virtual void SetTarget(Obj* o, int a, int b);      // +0x84
    virtual void s34(); virtual void s35(); virtual void s36(); virtual void s37();
    virtual void s38(); virtual void s39(); virtual void s40(); virtual void s41();
    virtual void s42(); virtual void s43(); virtual void s44();
    virtual Obj* GetObjectById(int id);                // +0xb4
    virtual void s46(); virtual void s47();
    virtual bool CanReach(Obj* o, float a, float b);   // +0xc0

    uint32_t pad04[(0xc0 - 4) / 4];
    Loco     mLoco;                                    // +0xc0
    uint32_t padc4[(0xb4c - 0xc4) / 4];
    Behav*   mBehav;                                   // +0xb4c
    uint32_t padb50[(0xb58 - 0xb50) / 4];
    uint32_t mFlags;                                   // +0xb58

    bool FUN_00c232b0();                               // 0x00c232b0 (m1010 != 0)
    void FUN_00c0b970(float v);                        // 0x00c0b970 (mBB8 = v)
    void SetStealthed(int a, int b);                   // 0x00c1aed0
    void SetSprinting(int a);                          // 0x00c1ad10
};

struct RefSlot { void* mp; };

struct FightState {
    int      mTarget;      // +0x00
    int      mId;          // +0x04
    int      mSlot;        // +0x08
    int      mStratHandle; // +0x0c
    float    mTimer0;      // +0x10
    float    mTimer1;      // +0x14
    float    mTimer2;      // +0x18
    float    mAttackTimer; // +0x1c
    float    mAttackReset; // +0x20
    bool     mB24;         // +0x24
    bool     mB25;         // +0x25
    bool     mNoRetarget;  // +0x26
    int      mEventAnim;   // +0x28
    int      mAnim;        // +0x2c
    void*    mHintArg;     // +0x30 (refcounted tribe)
    RefSlot  mRef;         // +0x34
};

struct BehaviorArg {       // the node's argument record
    uint32_t pad00;
    Obj*     mpTarget;     // +0x04
    uint32_t pad08;
    uint32_t pad0c;
    uint32_t pad10;
    uint32_t pad14;
    int      m18;          // +0x18
};

// ---- callees -------------------------------------------------------------
void  FindGroup(cSPCreatureBase* c);                       // 0x00d67700
WorldManager* FUN_00b3d480();                              // 0x00b3d480 (global getter)
Container* FUN_00b3d2b0();                                 // 0x00b3d2b0 (global getter)
float FUN_004df2d0(const void* tuning);                    // 0x004df2d0 RandomInRange
float GetPropertyT_float(int props, uint32_t hash, float def);   // 0x004e1c70

extern float DAT_0147bc0c;
extern float DAT_01473c70;      // 10.0f
extern int   DAT_01581288;      // game property set
extern char  DAT_01581254[];    // RandomInRange constant

static HandleList* HandleListAt(cSPCreatureBase* self)
{
    return (HandleList*)((uint8_t*)self + 0x34);
}

// ---------------------------------------------------------------------------
// @ 0x00d695a0
bool FUN_00d695a0(cSPCreatureBase* self, int, int, int, int,
                  FightState* st, BehaviorArg* arg)
{
    if (st != 0) {
        st->mTimer0 = 0.0f;
        st->mTimer1 = 0.0f;
        st->mTimer2 = 0.0f;
        const float kFill = DAT_0147bc0c;
        st->mTarget = -1;
        st->mId = 10;
        st->mSlot = -1;
        st->mStratHandle = 0;
        st->mAttackTimer = kFill;
        st->mAttackReset = kFill;
        st->mB24 = false;
        st->mB25 = false;
        st->mNoRetarget = false;
        st->mEventAnim = 0;
        st->mAnim = 0;
        st->mHintArg = 0;
        st->mRef.mp = 0;
    }

    st->mNoRetarget = self->FUN_00c232b0();
    self->FUN_00c0b970(0.0f);

    Obj* target = arg->mpTarget;
    if (target != 0) {
        Obj* old = (Obj*)st->mRef.mp;
        if (target != old) {
            target->AddRef60();
            st->mRef.mp = target;
            if (old != 0)
                old->Release64();
        }

        self->SetTarget(target, 1, 1);

        if (self->mLoco.IsMovingFast()) {
            FUN_00b3d480()->FUN_00acd2d0(target->GetHandle());
        }

        FindGroup(self);

        int anim = ((BehStim*)((char*)self->mBehav + 8))->Play(0, 0x80);
        if (anim == 0) {
            self->SetStealthed(1, 0);
            st->mB25 = false;
        } else {
            st->mB25 = true;
        }

        st->mTimer2 = FUN_004df2d0(DAT_01581254) + 1.0f;


        float v = GetPropertyT_float(DAT_01581288, 0xf4425721, DAT_01473c70);
        st->mAttackReset = v;
        st->mAttackTimer = v;

        if (arg->m18 != 0)
            st->mId = arg->m18;

        Obj* pCitizen = (Obj*)target->GetHandle();
        if (pCitizen != 0 && pCitizen->GetTypeID() == 0x18eb4b7) {
            void* tribe = (void*)((Citizen*)pCitizen)->GetTribe();
            void* oldTribe = st->mHintArg;
            if (tribe != oldTribe) {
                if (tribe != 0)
                    ((RefCounted*)tribe)->AddRef0();
                st->mHintArg = tribe;
                if (oldTribe != 0)
                    ((RefCounted*)oldTribe)->Release4();
            }
        }

        self->mFlags |= 0x2000;
        self->SetSprinting(1);

        void* pObj = HandleListAt(self)->FUN_00cee330();
        if (pObj != 0) {
            Container* pContainer = FUN_00b3d2b0();
            FUN_00b3d2b0()->FUN_00ac7de0(pObj, pContainer->FUN_00ac79d0());
        }
    }

    return target != 0;
}
