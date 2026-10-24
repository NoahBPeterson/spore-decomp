#include "types.h"

namespace SP {

struct Vec3 { float x, y, z; };
struct Quat { float x, y, z, w; };

class cSPCreatureBase;

struct LocoMoveParams;

// ---- vtable slot helpers ---------------------------------------------------------------------------
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV  virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

// ---- locomotion sub-object (own vtable, embedded at creature+0xc0) ---------------------------------
struct Loco {
    PV8 PV2 PV                                   // 0x00 .. 0x28
    virtual Vec3* GetPosition();                 // +0x2c
    virtual Quat* GetOrientation();              // +0x30
    PV4 PV                                       // 0x34 .. 0x44
    virtual bool IsOnView();                     // +0x48
    PV4                                          // 0x4c .. 0x58
    virtual Vec3* GetDirection(Vec3* out);       // +0x5c
    PV4 PV                                       // 0x60 .. 0x70
    virtual float GetFootprintRadius();          // +0x74
    PV8 PV8 PV4 PV2 PV2 PV                       // 0x78 .. 0xd8
    virtual void vDC(LocoMoveParams* p);         // +0xdc
    PV2 PV                                       // 0xe0 .. 0xe8
    virtual void vEC();                          // +0xec
};

// ---- target reference (result of cSPCreatureBase::GetTargetObj) ------------------------------------
struct ThreatOwner {
    PV8 PV2 PV                                   // 0x00 .. 0x28
    virtual Vec3* GetPosition();                 // +0x2c
};

struct TargetRef {
    PV PV
    virtual ThreatOwner* GetOwner();             // +0x08
};

// ---- the creature -----------------------------------------------------------------------------------
class cSPCreatureBase {
public:
    PV PV PV                                              // 0x00 .. 0x08
    virtual cSPCreatureBase* Cast(uint32_t type);         // +0x0c
    PV8 PV8 PV8 PV4 PV                                    // 0x10 .. 0x80
    virtual void SetTarget(void* obj, int a, int b);      // +0x84
    PV8 PV2 PV                                            // 0x88 .. 0xb0
    virtual void* GetObjectById(int id);                  // +0xb4
    PV PV                                                 // 0xb8 0xbc
    virtual bool CanReach(cSPCreatureBase* o, float a, float b);   // +0xc0

    uint32_t pad4[(0xc0 - 4) / 4];
    Loco mLoco;                                           // +0xc0
    uint32_t padc4[(0xb20 - (0xc0 + sizeof(Loco))) / 4];
    void* mGroup;                                         // +0xb20
    uint32_t padb24[(0xb4c - 0xb24) / 4];
    void* mBehav;                                         // +0xb4c
    uint32_t padb50[(0xb58 - 0xb50) / 4];
    uint32_t mFlags;                                      // +0xb58
    uint8_t mScared;                                      // +0xb5c
    uint8_t padb5d;
    uint8_t mDead;                                        // +0xb5e

    int  PlayAnimation(uint32_t id, int a, int b);        // 0x00c12190 (ret 12)
    int InterruptAnimation(uint32_t id, int a, int b);    // 0x00c12310 (ret 12)
    bool AnimationFinished2(int id);                      // 0x00c123f0 (ret 4)
    void PlayAnimationWithTarget(uint32_t id, ThreatOwner* a, int b, int c);   // 0x00c14940 (ret 16)
    bool Hover(int on);                                   // 0x00c13a30 (ret 4)
    void FUN_00c14750(int a);                             // ret 4
    void SetStealthed(int a, int b);                      // 0x00c1aed0 (ret 8)
    TargetRef* GetTargetObj();                            // 0x00c0ee60
    cSPCreatureBase* GetTargetAsCreature();               // 0x00c0ee70
    bool FUN_00c0c130();
    bool FUN_00c11480(const Vec3* p, float a, float b);           // ret 12
    bool FUN_00c0d560(cSPCreatureBase* t, float a, float b);      // ret 12
};

// ---- external symbols -------------------------------------------------------------------------------
struct RandomLCG {
    uint32_t RandomUint32Uniform(uint32_t limit);         // 0x00a68fb0 (ret 4)
};

extern RandomLCG sMathRandom;                             // 0x01601760

// ---- helpers ----------------------------------------------------------------------------------------
struct ScaredState {                                      // per-node behaviour state block
    int mState;        // +0x00
    float mTimer1;     // +0x04
    float mTimer2;     // +0x08
    float mTimer3;     // +0x0c
    float mTimer4;     // +0x10
    bool mB14;         // +0x14
    bool mB15;         // +0x15
    uint16_t pad16;
    int mFreakOut;     // +0x18
    float mTimer5;     // +0x1c
    Vec3 mVec;         // +0x20
    float mF2c;        // +0x2c
    int mAnim;         // +0x30
};
struct RefObj { uint32_t f0; void* f4; };
struct BehStim {                                          // creature->mBehav + 8
    void FUN_00bc97f0(uint32_t lo, uint32_t hi, float f, cSPCreatureBase* ref);   // ret 0x10
    void* PlayIdleAnimation(int a, int b);                // 0x00bc96a0 (ret 8)
};

// ---- property bag (0x0169e294 strategy -> +0xb4) ----------------------------------------------------
struct Property {
    void* mpData;        // +0x00 (array data, or the inline value itself)
    uint32_t pad04;
    int mnItemCount;     // +0x08
    uint32_t pad0c;
    uint16_t mnFlags;    // +0x10 (0x30 = array)
    uint16_t mnType;     // +0x12

    void* GetItems()
    {
        if (mnFlags & 0x30)
            return mpData;
        else if (mnType != 0)
            return this;
        return 0;
    }
};

class cPropertyList {
public:
    PV8 PV
    virtual bool GetProperty(uint32_t id, Property*& result);    // +0x24
};

struct CreatureModeStrategy {
    uint32_t padb4[0xb4 / 4];
    cPropertyList* mProps;                                // +0xb4
};

// ---- general IObject (vtable slot +0x5c = interface cast) -------------------------------------------
class IObject {
public:
    PV8 PV8 PV4 PV2 PV
    virtual void* v5c(uint32_t type);                     // +0x5c
};

// ---- argument block for Loco::vDC -------------------------------------------------------------------
struct BlockHeader { uint32_t mUsed; };                    // lives immediately before a heap block
struct LocoMoveParams {
    void* mpResult;      // +0x00
    void* mp04;          // +0x04
    void* mp08;          // +0x08
    uint32_t pad0c;      // +0x0c
    uint32_t pad10;      // +0x10
    Vec3 mPos;           // +0x14
    float f20;           // +0x20
    uint32_t pad24;      // +0x24
    uint32_t pad28[9];   // +0x28 .. +0x4b
    uint8_t b4c;         // +0x4c
    uint8_t pad4d;       // +0x4d
    uint16_t pad4e;      // +0x4e
    float f50;           // +0x50
    float f54;           // +0x54
    float f58;           // +0x58
    uint32_t f5c;        // +0x5c
    float f60;           // +0x60
    float f64;           // +0x64
    float f68;           // +0x68
    float f6c;           // +0x6c
    uint32_t f70;        // +0x70
};

extern CreatureModeStrategy* gCreatureModeStrategy;       // 0x0169e294
extern float DAT_015d9c6c;                                // 0x015d9c6c
extern float DAT_013ec4b4;                                // 0x013ec4b4
extern float DAT_0147bc40;                                // 0x0147bc40

TargetRef* FUN_00d998f0(void* x);                         // 0x00d998f0 (cdecl)
float FUN_00d99ac0(Loco* loco, ThreatOwner* owner, int flag);   // 0x00d99ac0 (cdecl)
float FUN_00d38a30(int which, cSPCreatureBase* c);        // 0x00d38a30 (cdecl)
void* FUN_00d998d0(void* idle, int type);                 // 0x00d998d0 (cdecl)
cSPCreatureBase* FUN_00d99470(cSPCreatureBase* c);        // 0x00d99470 (cdecl)
void operator delete(void* p);                            // 0x00f47380 (cdecl)
extern Vec3 DAT_0169ed0c;                                 // 0x0169ed0c

// ---- slice functions --------------------------------------------------------------------------------
// @ 0x00d6aa30
uint32_t FreakOut(cSPCreatureBase* p, char b)
{
    if (b) {
        p->PlayAnimation(0x65e5226, 1, -1);
        return 0x65e5226;
    }
    p->InterruptAnimation(0x9238f939, -1, 0);
    p->PlayAnimation(0xf238f946, 1, -1);
    return 0xf238f946;
}

// @ 0x00d6aa80
void FUN_00d6aa80(cSPCreatureBase* p)
{
    p->SetTarget(0, 0, 0);
    p->Hover(0);
    if (!p->mDead)
        p->InterruptAnimation(0x2481de5, -1, 0);
}

// @ 0x00d6aac0
void FUN_00d6aac0(cSPCreatureBase* p)
{
    p->SetTarget(0, 0, 0);
    p->Hover(0);
    if (!p->mDead)
        p->FUN_00c14750(1);
}

// @ 0x00d6ab00
void PlayScaredAnimation(cSPCreatureBase* p, ThreatOwner* param_2, int* slot)
{
    if (*slot == 0 || p->AnimationFinished2(*slot)) {
        int id;
        do {
            id = sMathRandom.RandomUint32Uniform(3) + 0x40e01e0;
        } while (id == *slot);
        p->PlayAnimationWithTarget(id, param_2, -1, -1);
        *slot = id;
    }
}

// @ 0x00d6ab50
bool FUN_00d6ab50(cSPCreatureBase* p, int a1, int a2, int a3, int a4,
                  ScaredState* st, RefObj* o)
{
    st->mState = 0;
    st->mTimer1 = 2.0f;
    TargetRef* obj = FUN_00d998f0(o->f4);
    if (obj) {
        p->mLoco.vEC();
        p->SetTarget(obj, 1, 0);
        p->SetStealthed(0, 0);
        PlayScaredAnimation(p, obj->GetOwner(), (int*)st);
        return true;
    }
    return false;
}

// @ 0x00d6abe0
bool FUN_00d6abe0(cSPCreatureBase* p, int a1, int a2, int a3, int a4,
                  ScaredState* st, int a6, float dt)
{
    TargetRef* obj = FUN_00d998f0(p->GetTargetObj());
    if (!obj)
        return false;
    cSPCreatureBase* tgt = p->GetTargetAsCreature();
    if (tgt != 0 && tgt->FUN_00c0c130()) {
        ((BehStim*)((char*)p->mBehav + 8))->FUN_00bc97f0(0x1000000, 0, 10.0f, tgt);
        return false;
    }
    st->mTimer1 = st->mTimer1 - dt;
    if (!(st->mTimer1 < 0.0f))
        return true;
    st->mTimer1 = 2.0f;
    Loco* loco = &p->mLoco;
    loco->GetPosition();
    Vec3* ownerPos = obj->GetOwner()->GetPosition();
    float f2 = FUN_00d99ac0(loco, obj->GetOwner(), 1);
    float f9 = FUN_00d38a30(1, p);
    float f10 = FUN_00d38a30(2, p);
    bool ok;
    if (tgt != 0)
        ok = p->FUN_00c0d560(tgt, f9, f2) || p->CanReach(tgt, f10, f2);
    else
        ok = p->FUN_00c11480(ownerPos, f2, f10);
    if (!ok)
        return false;
    PlayScaredAnimation(p, obj->GetOwner(), (int*)st);
    return true;
}
// @ 0x00d6ad60
bool FUN_00d6ad60(cSPCreatureBase* p, int a2, int a3, unsigned a4, unsigned char a5,
                  ScaredState* st, RefObj* o)
{
    st->mTimer1 = 5.0f;
    st->mTimer2 = 0.0f;
    st->mTimer3 = 0.0f;
    st->mState = 1;
    st->mTimer4 = 1.1f;
    st->mB14 = false;
    st->mB15 = false;
    st->mFreakOut = 0;

    Property* prop;
    float f;
    cPropertyList* props = gCreatureModeStrategy->mProps;
    if (props != 0 && props->GetProperty(0x82fb1acc, prop)) {
        const float* pData;
        if (prop->mnType == 0xd || prop->mnType == 0x10) {
            if (prop->mnFlags & 0x30)
                pData = *(const float**)prop;
            else
                pData = prop->mnType ? (const float*)prop : 0;
        } else {
            pData = &DAT_015d9c6c;
        }
        f = *pData;
    } else {
        f = 5.0f;
    }
    st->mTimer5 = f;

    st->mVec = DAT_0169ed0c;
    st->mF2c = 0.0f;
    st->mAnim = 0;

    if (a5 & 1) {
        st->mAnim = p->InterruptAnimation(0x5f0abb5, -1, 0);
        st->mState = 0;
    } else if (a4 & 0x2000000) {
        st->mAnim = p->InterruptAnimation(0x65e535c, -1, 0);
        st->mState = 0;
    } else {
        if (((BehStim*)((char*)p->mBehav + 8))->PlayIdleAnimation(0, 0x100)) {
            st->mAnim = p->InterruptAnimation(0x5f0abb5, -1, 0);
            st->mState = 0;
        }
    }

    IObject* found = 0;
    if (o != 0)
        found = (IObject*)o->f4;
    if (found == 0) {
        void* r = ((BehStim*)((char*)p->mBehav + 8))->PlayIdleAnimation(0, 0x40);
        if (r != 0)
            found = (IObject*)FUN_00d998d0(r, 0x13f94d4);
        if (found == 0) {
            void* r2 = ((BehStim*)((char*)p->mBehav + 8))->PlayIdleAnimation(0, 2);
            if (r2 != 0)
                found = (IObject*)FUN_00d998d0(r2, 0x13f94d4);
            if (found == 0)
                return false;
        }
    }
    IObject* sub = (IObject*)found->v5c(0xce9f6639);
    if (sub != 0) {
        if (FUN_00d99470((cSPCreatureBase*)sub) == 0)
            return false;
    } else {
        st->mTimer1 = 1.0f;
    }

    p->SetTarget(found, 0, 0);

    LocoMoveParams s;
    s.mpResult = 0;
    s.mp04 = 0;
    s.mp08 = 0;
    s.mPos.x = DAT_0169ed0c.x;
    s.mPos.y = DAT_0169ed0c.y;
    s.mPos.z = DAT_0169ed0c.z;
    s.f20 = 1.0f;
    s.pad24 = 0;
    s.b4c = 0;
    s.f50 = 0.0f;
    s.f54 = 0.0f;
    s.f58 = 0.0f;
    s.f5c = 0;
    s.f60 = 2.0f;
    s.f64 = DAT_013ec4b4;
    s.f68 = DAT_0147bc40;
    s.f6c = 0.0f;
    s.f70 = 0;
    p->mLoco.vDC(&s);
    if (s.mpResult != 0 && ((BlockHeader*)s.mpResult)[-1].mUsed != 0)
        operator delete(s.mpResult);
    p->SetStealthed(0, 0);
    return true;
}

}  // namespace SP