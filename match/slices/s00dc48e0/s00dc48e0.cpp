// s00dc48e0 - vehicle order / attack behaviour helpers (SP::VehicleTree family).
#include "types.h"
#include <math.h>

// ---- data globals referenced by these functions --------------------------------
extern uint8_t DAT_015a2560;   // 0x015a2560
extern uint8_t DAT_015a25e8;   // 0x015a25e8
extern uint8_t DAT_01654c10;   // 0x01654c10
extern uint8_t DAT_0169fa30;   // 0x0169fa30
extern uint8_t DAT_0169fa31;   // 0x0169fa31
extern float   DAT_013eb1bc;   // 0x013eb1bc
extern float   DAT_013ec4b8;   // 0x013ec4b8
extern float   DAT_013ec4d0;   // 0x013ec4d0
extern float   DAT_013eecd8;   // 0x013eecd8
extern float   DAT_01470f1c;   // 0x01470f1c
extern float   DAT_01473c70;   // 0x01473c70
extern float   DAT_014763b0;   // 0x014763b0
extern float   DAT_0147c368;   // 0x0147c368
extern float   DAT_0147c36c;   // 0x0147c36c
extern float   DAT_0147c390;   // 0x0147c390
extern float   DAT_01485378;   // 0x01485378
extern float   DAT_01485720;   // 0x01485720
extern float   DAT_0169fa68;   // 0x0169fa68
extern float   DAT_0169fa6c;   // 0x0169fa6c
extern float   DAT_0169fa70;   // 0x0169fa70

struct Obj;

// ---- vtable plumbing -----------------------------------------------------------
typedef void          (__thiscall *VfnRaw)(void);
typedef void          (__thiscall *Vfn0)(void*);
typedef void*         (__thiscall *VfnP)(void*);
typedef unsigned int  (__thiscall *VfnR)(void*);
typedef unsigned char (__thiscall *VfnB)(void*);
typedef void          (__thiscall *VfnI)(void*, int);
typedef void*         (__thiscall *VfnPI)(void*, int);
typedef void          (__thiscall *VfnV)(void*, void*);
typedef void*         (__thiscall *VfnVV)(void*, void*, void*);
typedef void          (__thiscall *VfnF3)(void*, float*, float, float);

enum VtSlot {
    kVt00 = 0x00 / 4, kVt04 = 0x04 / 4, kVt08 = 0x08 / 4, kVt0C = 0x0c / 4,
    kVt10 = 0x10 / 4, kVt2C = 0x2c / 4, kVt50 = 0x50 / 4, kVt5C = 0x5c / 4,
    kVt60 = 0x60 / 4, kVt64 = 0x64 / 4, kVt6C = 0x6c / 4, kVtB8 = 0xb8 / 4,
    kVtC0 = 0xc0 / 4, kVtE8 = 0xe8 / 4, kVtEC = 0xec / 4
};

struct Vtbl { VfnRaw mSlots[0xf0 / 4]; };

// A generic engine object that starts with a vtable pointer (used for the objects
// embedded at Obj+0x34 / Obj+0x108 / Obj+0x120 / Obj+0x508).
struct Sub {
    Vtbl* mpVtbl;                 // +0x00
    char  IsNearGoal();           // 0xc42e20  SP::cLocomotiveObject::IsNearGoal
    char  Cbfc600();              // 0xbfc600
    float Cbfc400();              // 0xbfc400
    void* Cc41ec0();              // 0xc41ec0
    void* Cc421f0();              // 0xc421f0
};

// nSPBehaviorTree::behavior_stimuli
struct BehaviorTreeStim {
    void  ClearAll(int a, int b); // 0xbc98f0
    int   Play(int a, int b);     // 0xbc96a0
    void* GetAny();               // 0xd997e0
};

struct BehaviorTree {
    uint8_t         mPad00[8];                                    // +0x000
    BehaviorTreeStim mStimA;                                      // +0x008
    uint8_t         mPadA[0x1d0 - 0x008 - sizeof(BehaviorTreeStim)];
    BehaviorTreeStim mStimB;                                      // +0x1d0
    void Cb660(void* p);                                          // 0xbcb660
};

struct City        { float* GetPositionPtr(); };                  // 0xfa0e00
struct CivMode     { char   IsCivTriggerActive(); };              // 0xcf7a90

struct TriggerMgr {
    uint8_t mPad00[0x28];         // +0x00
    uint8_t mByte28;              // +0x28
    uint8_t mPad29[0x2c - 0x29];
    int     mState2c;             // +0x2c
};

struct PlanetModel {
    int    GetContinent();                                   // 0xb88590
    float* CalcSurface(void* a, void* b);                    // 0xb81630
    float* DirectionToSurfacePosition(float* a, float* b);   // 0xb815a0
    char   Cb7e3e0(float* v);                                // 0xb7e3e0
};

struct CityVisualizer { void RequestPosition(float* v, uint32_t k); }; // 0xbec2d0
struct Bec660         { void Run(float* v, void* o); };                // 0xbec660

struct StateObj  { uint8_t mPad00[0x4b8]; int mState; };   // +0x4b8
struct OrderInfo { uint8_t mPad00[0x10];  int mKind;  };   // +0x10
#pragma pack(push,1)
struct OrderInfo2{ uint8_t mPad00[0x2d];  int mValue; };   // +0x2d
#pragma pack(pop)
struct AnimCtx   { Obj* mpTarget; };                       // +0x00

struct Obj {
    Vtbl*  mpVtbl;                          // +0x000
    uint8_t mPad004[0x34 - 0x04];           // +0x004
    Sub    mSub34;                          // +0x034
    uint8_t mPad038[0x50 - 0x38];           // +0x038
    int    mField50;                        // +0x050
    uint8_t mPad054[0x5c - 0x54];           // +0x054
    int    mField5c;                        // +0x05C
    uint8_t mPad060[0x108 - 0x60];          // +0x060
    Sub    mSub108;                         // +0x108
    uint8_t mPad10c[0x120 - 0x10c];         // +0x10C
    Sub    mSub120;                         // +0x120
    uint8_t mPad124[0x224 - 0x124];         // +0x124
    float  mF224;                           // +0x224
    uint8_t mPad228[0x2a4 - 0x228];         // +0x228
    uint8_t mByte2a4;                       // +0x2A4
    uint8_t mPad2a5[0x508 - 0x2a5];         // +0x2A5
    Sub    mSub508;                         // +0x508
    uint8_t mPad50c[0xaf0 - 0x50c];         // +0x50C
    Obj*   mpBehaviorTree;                  // +0xAF0
    uint8_t mPadaf4[0xb1c - 0xaf4];         // +0xAF4
    int    mStateB1c;                       // +0xB1C
    uint8_t mPadb20[0xb7c - 0xb20];         // +0xB20
    Obj*   mpObjB7c;                        // +0xB7C
    uint8_t mPadb80[0xb8c - 0xb80];         // +0xB80
    Obj**  mpVecBeginB8c;                   // +0xB8C
    Obj**  mpVecEndB90;                     // +0xB90

    void*  Ca71d0();                        // 0xca71d0
    void   Ca7250(char* msg);               // 0xca7250
    void   Caa900();                        // 0xcaa900
    void*  C9f1c0();                        // 0xc9f1c0
    void   C6c0200();                       // 0x6c0200
    char   C9e960(float* p);                // 0xc9e960  SP::cVehicle::CanOccupyTerrain
    void*  C9fee0();                        // 0xc9fee0
    float* C9e880();                        // 0xc9e880
    void   C9fb40(float x, float y, float z, float a, float b); // 0xc9fb40
    void   Cabe70();                        // 0xcabe70
    float  C9eb80();                        // 0xc9eb80
    float* Cbd9480(float* out);             // 0xbd9480
    int    GetFileCount();                  // 0x8e7f80
};

struct KeyLookup {
    Obj*  mpObj;                    // +0x00
    void* Default(int key);         // 0xb18460
    void* Match2E9(int key);        // 0x00dc4c20
    void* Match3DF(int key);        // 0x00dc4c40
    void  Reset();                  // 0x00dc4c60
};

// ---- free functions ------------------------------------------------------------
extern void* SP_GetCivModeStrategy();            // 0xcf74c0
extern void* GetTriggerMgr();                    // 0xb3d4d0
extern void* SP_GetCurrentGameMode();            // 0xb5b800
extern void  SP_GridHasValidIndex(void* p);      // 0xbc8fa0
extern void* __stdcall SP_PlanetModel(void* a);  // 0xb3d350
extern void* FUN_00d99420(void* a, int b);       // 0xd99420
extern void  FUN_00d996e0(void* a, void* b);     // 0xd996e0

// ---- functions -----------------------------------------------------------------

// @ 0x00dc48e0
char FUN_00dc48e0(Obj* self)
{
    return self->mSub34.IsNearGoal() == 0;
}

// @ 0x00dc4900
char FUN_00dc4900(void* a0, void* a1, void* a2, void* a3, void* a4, int* pOut)
{
    if (pOut)
        *pOut = 1;
    return 1;
}

// @ 0x00dc4920
char FUN_00dc4920(Obj* self)
{
    return self->mSub508.Cbfc600() != 0;
}

// @ 0x00dc4940
char FUN_00dc4940(Obj* self)
{
    OrderInfo* info = (OrderInfo*)self->Ca71d0();
    if (info->mKind == 0xc) {
        ((VfnI)self->mSub508.mpVtbl->mSlots[kVt50])(&self->mSub508, 0);
        ((Vfn0)self->mSub34.mpVtbl->mSlots[kVtEC])(&self->mSub34);
        return 1;
    }
    self->Ca7250((char*)"(51) MTP: bad orders");
    self->Caa900();
    return 0;
}

// @ 0x00dc4990
char FUN_00dc4990(Obj* self)
{
    CivMode* mode = (CivMode*)SP_GetCivModeStrategy();
    if (mode->IsCivTriggerActive())
        return 1;
    self->Caa900();
    return 0;
}

// @ 0x00dc49b0
float FUN_00dc49b0(Obj* self)
{
    StateObj* o = (StateObj*)self->C9f1c0();
    if (o->mState == 3)
        return 1.0f;
    return 0.0f;
}

// @ 0x00dc49d0
void FUN_00dc49d0(Obj* self)
{
    ((Vfn0)self->mSub34.mpVtbl->mSlots[kVtEC])(&self->mSub34);
}

// @ 0x00dc49f0
char FUN_00dc49f0(Obj* self)
{
    self->C6c0200();
    ((Vfn0)self->mSub34.mpVtbl->mSlots[kVtEC])(&self->mSub34);
    return 1;
}

// @ 0x00dc4a10
char FUN_00dc4a10(void* a0, void* a1, void* a2, void* a3, void* a4, float* pOut)
{
    if (pOut)
        *pOut = DAT_01470f1c;
    return 1;
}

// @ 0x00dc4a30
void FUN_00dc4a30(Obj* self)
{
    BehaviorTree* bt = (BehaviorTree*)self->mpBehaviorTree;
    bt->mStimA.ClearAll(0x10000, 0);
    ((Vfn0)self->mSub34.mpVtbl->mSlots[kVtEC])(&self->mSub34);
}

// @ 0x00dc4a60
float FUN_00dc4a60(Obj* self, void* a1, void* a2, void* a3, BehaviorTreeStim* a4,
                   uint8_t* a5, void* a6, OrderInfo2* a7)
{
    if (a4)
        a4->GetAny();
    *a5 = 1;
    int v = a7->mValue;
    BehaviorTree* bt = (BehaviorTree*)self->mpBehaviorTree;
    void* r = FUN_00d99420(&bt->mStimB, v);
    FUN_00d996e0(r, a4);
    return 1.0f;
}

// @ 0x00dc4ab0
float FUN_00dc4ab0(void* a0, void* a1, void* a2, uint32_t a3)
{
    if (a3 & 0x400)
        return 0.0f;
    return 1.0f;
}

// @ 0x00dc4ac0
char FUN_00dc4ac0(Obj* self)
{
    ((Vfn0)self->mSub34.mpVtbl->mSlots[kVtEC])(&self->mSub34);
    return 1;
}

// @ 0x00dc4ae0
char FUN_00dc4ae0(Obj* self)
{
    BehaviorTree* bt = (BehaviorTree*)self->mpBehaviorTree;
    return bt->mStimA.Play(0x8000, 0) != 0;
}

// @ 0x00dc4b00
float FUN_00dc4b00(void)
{
    TriggerMgr* t = (TriggerMgr*)GetTriggerMgr();
    if (t->mState2c == 2 && t->mByte28 == 0)
        return 1.0f;
    return 0.0f;
}

// @ 0x00dc4b20
char FUN_00dc4b20(Obj* self)
{
    ((Vfn0)self->mSub34.mpVtbl->mSlots[kVtEC])(&self->mSub34);
    ((VfnI)self->mSub508.mpVtbl->mSlots[kVt50])(&self->mSub508, 0);
    return 1;
}

// @ 0x00dc4b50
char FUN_00dc4b50(void)
{
    TriggerMgr* t = (TriggerMgr*)GetTriggerMgr();
    if (t->mState2c == 2 && t->mByte28 == 0)
        return 1;
    return 0;
}

// @ 0x00dc4b70
void FUN_00dc4b70(Obj* self)
{
    void* mode = SP_GetCurrentGameMode();
    if (mode != &DAT_01654c10) {
        if (DAT_0169fa31 == 0) {
            SP_GridHasValidIndex(&DAT_015a2560);
            DAT_0169fa31 = 1;
        }
        ((BehaviorTree*)self->mpBehaviorTree)->Cb660(&DAT_015a2560);
    } else {
        if (DAT_0169fa30 == 0) {
            SP_GridHasValidIndex(&DAT_015a25e8);
            DAT_0169fa30 = 1;
        }
        ((BehaviorTree*)self->mpBehaviorTree)->Cb660(&DAT_015a25e8);
    }
}

// @ 0x00dc4c20
void* KeyLookup::Match2E9(int key)
{
    if (key == 0x2e9ae69 || key == 0x2e98ab4)
        return this;
    return Default(key);
}

// @ 0x00dc4c40
void* KeyLookup::Match3DF(int key)
{
    if (key == 0x3df2cb9 || key == 0x2e98ab4)
        return this;
    return Default(key);
}

// @ 0x00dc4c60
void KeyLookup::Reset()
{
    Obj* p = mpObj;
    mpObj = 0;
    if (p)
        ((Vfn0)p->mpVtbl->mSlots[kVt04])(p);
}

// @ 0x00dc4d40
char FUN_00dc4d40(Obj* self, Obj* ctx)
{
    switch (self->mStateB1c) {
    case 0: {
        void* a = (void*)((VfnP)self->mSub34.mpVtbl->mSlots[kVt2C])(&self->mSub34);
        PlanetModel* pm1 = (PlanetModel*)SP_PlanetModel(a);
        int c1 = pm1->GetContinent();
        void* b = (void*)((VfnP)ctx->mSub120.mpVtbl->mSlots[kVt2C])(&ctx->mSub120);
        PlanetModel* pm2 = (PlanetModel*)SP_PlanetModel(b);
        int c2 = pm2->GetContinent();
        return c1 == c2;
    }
    case 1: {
        float* p = ((City*)ctx)->GetPositionPtr();
        float v[3];
        v[0] = p[0];
        v[1] = p[1];
        v[2] = p[2];
        if (v[0] != DAT_0169fa68 || v[1] != DAT_0169fa6c || v[2] != DAT_0169fa70)
            return self->C9e960(v);
        return 0;
    }
    case 2:
        return 1;
    }
    return 0;
}

// @ 0x00dc4e20
char IsValidFireTarget(Obj* ctx, Obj* target)
{
    if (!target)
        return 0;
    Obj* r = (Obj*)((VfnPI)target->mpVtbl->mSlots[kVt5C])(target, 0x17f243b);
    if (r && ((VfnB)r->mpVtbl->mSlots[kVt2C])(r))
        return 0;
    if (target->GetFileCount() == 2)
        return 0;
    unsigned int a = ((VfnR)ctx->mpVtbl->mSlots[kVt10])(ctx);
    unsigned int b = ((VfnR)target->mpVtbl->mSlots[kVt10])(target);
    if (b == a) {
        unsigned int a2 = ((VfnR)ctx->mpVtbl->mSlots[kVt10])(ctx);
        if (a2 != (unsigned int)-1)
            return 0;
    }
    Obj* h = (Obj*)((VfnPI)target->mpVtbl->mSlots[kVt5C])(target, 0x403df5f);
    if (!h)
        return 1;
    unsigned int hv = ((VfnR)h->mSub108.mpVtbl->mSlots[kVt10])(&h->mSub108);
    if (hv == (unsigned int)-1)
        return 0;
    if (h->mF224 >= DAT_013ec4d0)
        return 0;
    return 1;
}

// @ 0x00dc4ed0
void* FUN_00dc4ed0(float* pMin, float* pRange, Obj* self, Obj* other)
{
    int state = self->mStateB1c;
    uint8_t flag = 0;
    Obj* r = 0;
    if (other) {
        r = (Obj*)((VfnPI)other->mpVtbl->mSlots[kVtB8])(other, 0x137e8e0);
        if (r && r->mStateB1c == 2)
            flag = 1;
    }
    if ((state == 2) != (flag != 0)) {
        Obj* c = (state == 2) ? self : r;
        float f = c->C9eb80();
        if (f < *pRange) {
            double base = *pRange;
            float g = (float)sqrt(base * base - (double)f * (double)f);
            *pRange = g;
            if (g < *pMin)
                *pMin = g;
            return pRange;
        }
        *pRange = DAT_01473c70;
        *pMin = 0.0f;
        return pMin;
    }
    return r;
}

// @ 0x00dc4f90
char FUN_00dc4f90(Obj* self)
{
    Obj* t = ((AnimCtx*)self->Ca71d0())->mpTarget;
    if (t) {
        Obj* target = (Obj*)((VfnPI)t->mpVtbl->mSlots[kVt0C])(t, 0x13f94d4);
        if (target) {
            Obj* ctx = self ? (Obj*)&self->mSub508 : 0;
            if (IsValidFireTarget(ctx, target)) {
                if (((VfnB)self->mSub34.mpVtbl->mSlots[kVt50])(&self->mSub34)) {
                    Obj* d = (Obj*)((VfnP)target->mpVtbl->mSlots[kVt08])(target);
                    d->mField50 |= 0x800;
                }
                return 1;
            }
            self->Ca7250((char*)"(2) Invalid target.");
            self->Caa900();
            return 0;
        }
    }
    self->Ca7250((char*)"(1) No target.");
    self->Caa900();
    return 0;
}

// @ 0x00dc5030
char FUN_00dc5030(Obj* self, void* a1, void* a2, void* a3, void* a4, Obj** a5)
{
    Obj* o = *a5;
    if (((VfnB)o->mpVtbl->mSlots[kVt2C])(o)) {
        self->Caa900();
        return 0;
    }
    return 1;
}

// @ 0x00dc5050
void FUN_00dc5050(Obj* self, Obj* ctx)
{
    float v[3];
    int state = self->mStateB1c;
    if (state == 1) {
        float* p = ((City*)ctx)->GetPositionPtr();
        v[0] = p[0];
        v[1] = p[1];
        v[2] = p[2];
        if (v[0] == DAT_0169fa68 && v[1] == DAT_0169fa6c && v[2] == DAT_0169fa70)
            return;
        ((VfnF3)self->mSub34.mpVtbl->mSlots[kVtE8])(&self->mSub34, v, DAT_0147c368, DAT_0147c36c);
    } else {
        void* o = (void*)((VfnPI)self->mSub34.mpVtbl->mSlots[kVt2C])(&self->mSub34, state);
        void* r = (void*)((VfnVV)ctx->mpVtbl->mSlots[kVt6C])(ctx, v, o);
        ((Bec660*)r)->Run(v, o);
        if (v[0] == DAT_0169fa68 && v[1] == DAT_0169fa6c && v[2] == DAT_0169fa70)
            return;
        ((VfnF3)self->mSub34.mpVtbl->mSlots[kVtE8])(&self->mSub34, v, DAT_0147c368, DAT_0147c36c);
    }
    self->C9fb40(v[0], v[1], v[2], DAT_0147c368, DAT_0147c36c);
}

// @ 0x00dc51c0
void FUN_00dc51c0(Obj* self, Obj* ctx)
{
    float start[3];
    float dir[3];
    float tmp[3];
    if (self->mStateB1c == 1) {
        float* p = ((City*)ctx)->GetPositionPtr();
        start[0] = p[0];
        start[1] = p[1];
        start[2] = p[2];
        if (start[0] == DAT_0169fa68 && start[1] == DAT_0169fa6c && start[2] == DAT_0169fa70)
            return;
        float step = DAT_013eecd8;
        for (;;) {
            float* a = self->Cbd9480(tmp);
            float dx = start[0] - a[0];
            float dy = start[1] - a[1];
            float dz = start[2] - a[2];
            float len = sqrtf((dx * dx + dy * dy + dz * dz) + DAT_013ec4b8);
            float inv = DAT_01485720 / len;
            dir[0] = start[0] + inv * dx * step;
            dir[1] = start[1] + inv * dy * step;
            dir[2] = start[2] + inv * dz * step;
            PlanetModel* pm = (PlanetModel*)SP_PlanetModel(dir);
            float* q = pm->CalcSurface(dir, dir);
            dir[0] = q[0];
            dir[1] = q[1];
            dir[2] = q[2];
            step -= DAT_01470f1c;
            pm = (PlanetModel*)SP_PlanetModel(dir);
            if (pm->Cb7e3e0(dir))
                break;
            if (!(step > DAT_01485378))
                break;
        }
    } else {
        void* r = (void*)((VfnVV)ctx->mpVtbl->mSlots[kVt6C])(ctx, dir, (void*)5);
        ((CityVisualizer*)r)->RequestPosition(dir, 5);
        float* a = self->Cbd9480(tmp);
        float dx = dir[0] - a[0];
        float dy = dir[1] - a[1];
        float dz = dir[2] - a[2];
        float inv = DAT_01485720 / sqrtf(dx * dx + dy * dy + dz * dz);
        dir[0] = dir[0] + inv * dx * DAT_013eecd8;
        dir[1] = dir[1] + inv * dy * DAT_013eecd8;
        dir[2] = dir[2] + inv * dz * DAT_013eecd8;
        PlanetModel* pm = (PlanetModel*)SP_PlanetModel(dir);
        float* q = pm->DirectionToSurfacePosition(dir, dir);
        dir[0] = q[0];
        dir[1] = q[1];
        dir[2] = q[2];
    }
    ((VfnF3)self->mSub34.mpVtbl->mSlots[kVtE8])(&self->mSub34, dir, DAT_0147c368, DAT_0147c36c);
    self->C9fb40(dir[0], dir[1], dir[2], DAT_0147c368, DAT_0147c36c);
}

// @ 0x00dc54e0
float FUN_00dc54e0(Obj* self)
{
    Obj* o = (Obj*)self->C9fee0();
    if (!o)
        return 0.0f;
    Obj* r = (Obj*)((VfnPI)o->mpVtbl->mSlots[kVtB8])(o, 0x17f243b);
    if (r && ((VfnB)r->mpVtbl->mSlots[kVt2C])(r))
        return 0.0f;
    if ((self->mByte2a4 & 6) != 0)
        return 0.0f;
    float* p1 = (float*)((VfnP)o->mpVtbl->mSlots[kVt2C])(o);
    float x1 = p1[0];
    float y1 = p1[1];
    float z1 = p1[2];
    float* p2 = (float*)((VfnP)self->mSub34.mpVtbl->mSlots[kVt2C])(&self->mSub34);
    float dx = p2[0] - x1;
    float dy = p2[1] - y1;
    float dz = p2[2] - z1;
    float dist = sqrtf(dx * dx + (dy * dy + dz * dz));
    float lim = ((Sub*)&self->mSub508)->Cbfc400();
    Obj* h = (Obj*)self->mSub34.Cc41ec0();
    float d;
    if (h->mField5c == 0) {
        d = DAT_013eb1bc;
    } else {
        float* c = (float*)self->mSub34.Cc421f0();
        float ex = c[0] - x1;
        float ey = c[1] - y1;
        float ez = c[2] - z1;
        d = sqrtf(ez * ez + ey * ey + ex * ex);
    }
    if ((lim < dist && (lim < d || d == DAT_013eb1bc)) ||
        (dist < DAT_014763b0 && (d < DAT_014763b0 || d == DAT_013eb1bc)))
        return 1.0f;
    return 0.0f;
}

// @ 0x00dc5670
char FUN_00dc5670(Obj* self, void* a1, void* a2, uint32_t flags)
{
    Obj* o = (Obj*)self->C9fee0();
    if (!o)
        return 0;
    Obj* target = (Obj*)((VfnPI)o->mpVtbl->mSlots[kVtB8])(o, 0x13f94d4);
    if (!target)
        return 0;
    Obj* ctx = self ? (Obj*)&self->mSub508 : 0;
    if (!IsValidFireTarget(ctx, target))
        return 0;
    Obj* d = (Obj*)((VfnP)target->mpVtbl->mSlots[kVt08])(target);
    float* p = (float*)((VfnP)d->mpVtbl->mSlots[kVt2C])(d);
    float* q = self->C9e880();
    float dx = q[0] - p[0];
    float dy = q[1] - p[1];
    float dz = q[2] - p[2];
    float dist = sqrtf(dz * dz + (dy * dy + dx * dx));
    float extra = (flags & 0x100) ? DAT_0147c390 : 0.0f;
    float lim = ((Sub*)&self->mSub508)->Cbfc400() + extra;
    if (lim <= dist)
        return 0;
    ((VfnV)self->mSub508.mpVtbl->mSlots[kVt50])(&self->mSub508, target);
    return 1;
}

// @ 0x00dc5760
void FUN_00dc5760(Obj* self)
{
    Obj* p = self->mpObjB7c;
    if (p) {
        self->mpObjB7c = 0;
        ((Vfn0)p->mpVtbl->mSlots[kVtC0])(p);
    }
    ((VfnI)self->mSub508.mpVtbl->mSlots[kVt50])(&self->mSub508, 0);
    self->Cabe70();
}