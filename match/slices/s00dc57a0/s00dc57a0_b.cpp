// s00dc57a0 (2nd module): behaviour-tree "order / fire" callbacks and helpers.
// Covers the 18 VAs claimed for slice s00dc57a0:
//   00dc57a0 00dc5aa0 00dc5b50 00dc5bf0 00dc5c90 00dc5ce0 00dc5d40 00dc5fe0
//   00dc6070 00dc6140 00dc6160 00dc6250 00dc6300 00dc6370 00dc6420 00dc6530
//   00dc65b0 00dc6640
// Build flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

// ================================================================================
// Data globals referenced by the functions below
// ================================================================================
extern float   DAT_013eb1c0;    // 0x013eb1c0   1.2f
extern float   DAT_013eb960;    // 0x013eb960   0.01f
extern float   DAT_013ec4d0;    // 0x013ec4d0
extern float   DAT_013f1f04;    // 0x013f1f04   120.0f
extern float   DAT_013f9428;    // 0x013f9428   0.001f  (kept float)
extern float   DAT_0140c6e8;    // 0x0140c6e8   32.0f
extern float   DAT_01470f1c;    // 0x01470f1c   2.0f
extern float   DAT_01471064;    // 0x01471064   0.5f
extern float   DAT_0147c348;    // 0x0147c348   0.75f
extern float   DAT_0147c36c;    // 0x0147c36c   8.0f
extern float   DAT_0147c394;    // 0x0147c394   1.5f
extern float   DAT_01485378;    // 0x01485378   0.0f
extern float   DAT_01485720;    // 0x01485720   1.0f
extern float   DAT_01486110;    // 0x01486110   5.0f
extern float   DAT_01486114;    // 0x01486114   2.5f
extern float   DAT_0169fa68;    // 0x0169fa68
extern float   DAT_0169fa6c;    // 0x0169fa6c
extern float   DAT_0169fa70;    // 0x0169fa70
extern void*   DAT_0147c3fc[];  // 0x0147c3fc  sound-name table indexed by mFieldB20
extern void*   DAT_0168d824;    // 0x0168d824  lazy Simulator singleton
extern uint8_t DAT_0498da10;    // 0x0498da10

// 0x016c7aa4: engine root; [0x78] -> slot object, [0xb8] -> current entry index.
struct EngineSlot
{
    uint8_t pad000[0xb8];
    int32_t mIndex;             // +0xb8
};
struct EngineRoot
{
    uint8_t     pad000[0x78];
    EngineSlot* mpSlot;         // +0x78
};
extern EngineRoot* DAT_016c7aa4;    // 0x016c7aa4

// ================================================================================
// Layout primitives
// ================================================================================
struct Obj;
struct Vtbl;
struct Sub;

// Byte offsets of the virtual slots this slice actually calls.
enum
{
    kVt00 = 0x00 / 4, kVt04 = 0x04 / 4, kVt08 = 0x08 / 4, kVt0C = 0x0C / 4,
    kVt10 = 0x10 / 4, kVt18 = 0x18 / 4, kVt20 = 0x20 / 4, kVt2C = 0x2C / 4,
    kVt3C = 0x3C / 4, kVt4C = 0x4C / 4, kVt58 = 0x58 / 4, kVt5C = 0x5C / 4,
    kVt60 = 0x60 / 4, kVt64 = 0x64 / 4, kVt6C = 0x6C / 4, kVt74 = 0x74 / 4,
    kVtB8 = 0xB8 / 4, kVtBC = 0xBC / 4, kVtC0 = 0xC0 / 4, kVtC4 = 0xC4 / 4,
    kVtCC = 0xCC / 4, kVtE0 = 0xE0 / 4, kVtE4 = 0xE4 / 4, kVtE8 = 0xE8 / 4,
    kVtEC = 0xEC / 4
};

struct Vtbl
{
    void* mSlots[0x100];
};

struct Vec3f
{
    float x, y, z;
};

// Sub-object carriers embedded at +0x34 and +0x508 of the creature object.
struct Sub
{
    Vtbl* mpVtbl;               // +0x00

    float Cbfc400();            // FUN_00bfc400
    float Cbfc490();            // FUN_00bfc490
    void  Set38(float v);       // FUN_00f924e0   (writes [ecx+0x38])
};

struct State
{
    uint8_t pad000[0x4b8];
    int32_t mState;             // +0x4b8
};

struct HitInfo                  // returned by FUN_006c0200
{
    uint8_t pad000[0x4];
    Vec3f   v4;                 // +0x04
    uint8_t pad010[0x18];
    int32_t mField28;           // +0x28  entry-array base
};

struct StimEntry                // 0x34-byte entries hanging off HitInfo::mField28
{
    float mField00;             // +0x00
    uint8_t pad004[0x30];
};

struct AnimCreat
{
    Vtbl* mpVtbl;               // +0x00
    void  Release();            // FUN_00a05270
};

struct BehaviorStim             // nSPBehaviorTree::behavior_stimuli (12 bytes)
{
    int32_t mStimulusID;        // +0x00
    Obj*    mpTarget;           // +0x04
    int32_t mField08;           // +0x08  (original clears this with an integer store)

    Obj* PlayIdleAnimation(int a, int b);   // FUN_00bc96a0
    void GetAny();                          // FUN_00d997e0
};

struct BehaviorTree
{
    Vtbl*        mpVtbl;        // +0x000
    uint8_t      pad004[0x4];
    BehaviorStim mStimA;        // +0x008
    uint8_t      pad014[0x1bc];
    BehaviorStim mStimB;        // +0x1D0
    uint8_t      pad1dc[0x40c];
    void*        mpField5e8;    // +0x5E8
    uint8_t      pad5ec[0x10];
    void*        mpField5fc;    // +0x5FC

    void Cb3d0();               // FUN_00bcb3d0
};

struct Noun
{
    uint8_t pad000[0x431];
    uint8_t mByte431;           // +0x431
};

struct NounMgr
{
    Noun* Find(unsigned int id);    // FUN_00b25f40
};

struct Spot                     // SP::PlanetModel
{
    Vtbl*  mpVtbl;              // +0x00
    Vec3f* DirectionToSurfacePosition(Vec3f* from, Vec3f* dir);  // FUN_00b815a0
};

struct AudioSys
{
    Vtbl* mpVtbl;               // +0x00
};

struct Alloc
{
    void* Ctor();               // FUN_00f30bc0
};

struct Simulator
{
    Obj* PickNearest(Obj* c, float a, float b);     // FUN_00f30cc0
};

struct GameTimeMgr
{
    uint64_t Now();             // FUN_00b316c0
};

struct Obj
{
    Vtbl*   mpVtbl;             // +0x000
    uint8_t mPad004[0x28];
    Obj*    mpField2c;          // +0x02C
    uint8_t mPad030[0x4];
    Sub     mSub34;             // +0x034
    uint8_t mPad038[0x18];
    int32_t mField50;           // +0x050
    int32_t mField54;           // +0x054
    uint8_t mPad058[0x44];
    AnimCreat* mpAnim9c;        // +0x09C
    uint8_t mPad0A0[0x4];
    Obj*    mpFieldA4;          // +0x0A4
    Obj*    mpFieldA8;          // +0x0A8
    uint8_t mByteAc;            // +0x0AC
    uint8_t mPad0AD[0x1F7];
    uint8_t mByte2a4;           // +0x2A4
    uint8_t mPad2A5[0x263];
    Sub     mSub508;            // +0x508
    uint8_t mPad50C[0x34];
    float   mF540;              // +0x540
    uint8_t mPad544[0x5AC];
    BehaviorTree* mpBehaviorTree;   // +0xAF0
    uint8_t mPadAF4[0xC];
    int32_t mFieldB00;          // +0xB00
    uint8_t mPadB04[0x1C];
    int32_t mFieldB20;          // +0xB20
    uint8_t mPadB24[0x58];
    Obj*    mpObjB7c;           // +0xB7C
    uint8_t mPadB80[0x4F];
    uint8_t mByteBcf;           // +0xBCF

    // real member functions whose ecx is this object
    Obj*       C9f3d0();                // FUN_00c9f3d0
    Obj*       C9fee0();                // FUN_00c9fee0
    Obj*       C9fff0();                // FUN_00c9fff0
    State*     C9f1c0();                // FUN_00c9f1c0
    Obj**      Ca71d0();                // FUN_00ca71d0
    HitInfo*   C9c0200();               // FUN_006c0200
    int32_t    GetFileCount();          // FUN_008e7f80
    Vec3f*     Cbd9480(Vec3f* out);     // FUN_00bd9480
    void       Apply(Vec3f v);          // FUN_00c9fb40
    void       Take(Vec3f* p);          // FUN_00ca97a0
    char       C9e940(Vec3f* p);        // FUN_00c9e940
    void       C4d00(void* v);          // FUN_00dc4d00
    void       Cdc6530();               // FUN_00dc6530
    void       Cdc65b0();               // FUN_00dc65b0
    bool       Cdc6420(void* a1);       // FUN_00dc6420
};

// --- outgoing "fire" descriptors used by the callbacks -------------------------
struct OutB50                  // 00dc5b50
{
    int32_t u0;                // +0x00  (cleared/stored with integer stores)
    Obj*  mTarget;             // +0x04
    float f2;                  // +0x08
};

struct OutBF0                  // 00dc5bf0
{
    int32_t i0;                // +0x00
    float   f4;                // +0x04
    Vec3f   v8;                // +0x08
    float   f14;               // +0x14
};

struct OutCE0                  // 00dc5ce0
{
    int32_t u0;                // +0x00  (stored with an integer 0; not read as float here)
    float   f4;                // +0x04
    float   f8;                // +0x08
    uint8_t bC;                // +0x0C
    uint8_t padD[0x3];
    float   f10;               // +0x10
    float   f14;               // +0x14
    float   f18;               // +0x18
};

struct Out6070                 // 00dc6070
{
    float f0;                  // +0x00
    Obj*  mTarget;             // +0x04
};

struct Out6140                 // 00dc6140
{
    int32_t i0;                // +0x00
    Obj*    mTarget;           // +0x04
};

struct Out6160                 // 00dc6160
{
    float f0;                  // +0x00
    Obj*  mTarget;             // +0x04
};

struct Ctx6070                 // 00dc6070 6th argument
{
    int32_t i0;                // +0x00
    Obj*    mpTarget;          // +0x04
};

struct PtrVec                  // 00dc6640
{
    void** mpBegin;            // +0x00
    void** mpEnd;              // +0x04
};

// ================================================================================
// Virtual-call shapes used by this slice
// ================================================================================
typedef void  (__thiscall *Vfn0)   (void*);
typedef char  (__thiscall *VfnC)   (void*);
typedef float (__thiscall *VfnF)   (void*);
typedef void* (__thiscall *VfnP)   (void*);
typedef void* (__thiscall *VfnPI)  (void*, void*);
typedef void* (__thiscall *VfnPU)  (void*, unsigned int);
typedef unsigned int (__thiscall *VfnU)(void*);
typedef float* (__thiscall *VfnFF) (void*, float, float);
typedef void  (__thiscall *VfnF1)  (void*, float);
typedef void  (__thiscall *VfnF2)  (void*, Vec3f*, float);
typedef void  (__thiscall *VfnF3)  (void*, Vec3f*, float, float);
typedef void  (__thiscall *VfnF3I) (void*, Vec3f*, float, float, int);
typedef float (__thiscall *VfnFI)  (void*, int);
typedef void  (__thiscall *VfnI1)  (void*, int);
typedef void* (__thiscall *VfnP2)  (void*, void*, int);
typedef void  (__thiscall *VfnV2)  (void*, void*, int);
typedef void  (__thiscall *VfnP3)  (void*, void*, void*, void*);

// ================================================================================
// Free function prototype table
// ================================================================================
void   FUN_00dc4ed0(float* a, float* b, Obj* self, Obj* other);
char   FUN_00dc4e20(void* a, Obj* b);
void   FUN_00dc4610(Obj* self);
void   FUN_00dc6430(Obj* o, Vec3f* pos, float d, float a, float b, float c);
char   FUN_00dc5bc0(Obj* self);
Obj*   FUN_00b3d240();
float  FUN_00f264b0(void* p);
void*  FUN_00f473a0(unsigned int size, const char* name, int a, int b, int c, int d);
void   FUN_00bc86e0(double t, void* vtbl, Obj* self, void* stimB,
                    void* a4, void* a5);
void   Start3dSoundByName(void* name, void* sys, float x, float y, float z);
AudioSys* EA_Audio_GetSystemAT();       // FUN_00a206f0
NounMgr*  SP_NounManager();             // FUN_00b3d300
Spot*     SP_PlanetModel();             // FUN_00b3d350
GameTimeMgr* SP_GameTimeManager();      // FUN_00b3d380

// ================================================================================
// 00dc57a0
// ================================================================================
// @ 0x00dc57a0
char FUN_00dc57a0(Obj* self, void* a1, void* a2, void* a3, void* a4,
                  float* pAccum, void* a6, float a7)
{
    Obj* o = self->C9f3d0();
    if (!o)
        return 1;
    if (((VfnC)o->mpVtbl->mSlots[kVt2C])(o))
        return 1;

    Sub* s = &self->mSub508;
    if (!(((VfnF)s->mpVtbl->mSlots[kVt58])(s) > self->mF540))
        return 1;

    unsigned int b = ((VfnU)s->mpVtbl->mSlots[kVt10])(s);
    if (((VfnU)o->mpVtbl->mSlots[kVt4C])(o) != b)
        return 1;

    Sub*   s34 = &self->mSub34;
    Vec3f* p5  = (Vec3f*)((VfnP)s34->mpVtbl->mSlots[kVt2C])(s34);

    Vec3f  tmp;
    Vec3f* p6 = o->Cbd9480(&tmp);

    float dz = p6->z - p5->z;
    float dy = p6->y - p5->y;
    float dx = p6->x - p5->x;
    float dist = sqrtf((dz * dz + dy * dy) + dx * dx);
    if (dist <= DAT_013f1f04)
    {
        float val = ((float)((VfnF)s->mpVtbl->mSlots[kVt58])(s) * a7)
                    * DAT_013eb960 + self->mF540;
        if ((float)((VfnF)s->mpVtbl->mSlots[kVt58])(s) < val)
        {
            val = (float)((VfnF)s->mpVtbl->mSlots[kVt58])(s);
            SP_NounManager()->Find(
                ((VfnU)s->mpVtbl->mSlots[kVt10])(s))->mByte431 = 1;
        }
        s->Set38(val);

        if (self->mByteBcf && s->Cbfc490() > DAT_0147c348)
            self->mByteBcf = 0;

        if (0.0f >= *pAccum)
        {
            Obj* a = FUN_00b3d240();

            Vec3f  pair[2];
            Vec3f* m = (Vec3f*)((VfnPI)s34->mpVtbl->mSlots[kVt6C])(s34, pair);

            Vec3f mid;
            mid.x = (m[1].x + m[0].x) * DAT_01471064;
            mid.y = (m[1].y + m[0].y) * DAT_01471064;
            mid.z = (m[1].z + m[0].z) * DAT_01471064;

            Vec3f  w;
            Vec3f* wp = (Vec3f*)((VfnPI)s34->mpVtbl->mSlots[kVt5C])(s34, &w);
            ((VfnP3)a->mpVtbl->mSlots[kVt60])(a, &DAT_0498da10, &mid, wp);

            float v = *pAccum;
            do
            {
                v = v + DAT_0147c394;
            } while (0.0f >= v);
            *pAccum = v;
        }
        *pAccum = *pAccum - a7;
    }
    return 1;
}

// ================================================================================
// 00dc5aa0
// ================================================================================
// @ 0x00dc5aa0
char FUN_00dc5aa0(Obj* self)
{
    Obj* o = self->C9fff0();
    if (!o)
        return 0;
    if (((VfnC)o->mpVtbl->mSlots[kVt2C])(o))
        return 0;

    Obj* t = self->C9fee0();
    if (!t)
        return 0;

    float a = DAT_0147c36c;
    float b = self->mSub508.Cbfc400() - DAT_01485720;
    FUN_00dc4ed0(&a, &b, self, t);

    Vec3f* p = (Vec3f*)((VfnFF)t->mpVtbl->mSlots[kVt2C])(t, a, b);
    self->Apply(*p);
    return 1;
}

// ================================================================================
// 00dc5b50
// ================================================================================
// @ 0x00dc5b50
char FUN_00dc5b50(Obj* self, void* a1, void* a2, void* a3, void* a4, OutB50* out)
{
    if (out)
    {
        out->u0 = 0;
        out->mTarget = 0;
        out->f2 = 0.0f;
    }

    Obj* t = *self->Ca71d0();
    Obj* r = t ? (Obj*)((VfnPI)t->mpVtbl->mSlots[kVt0C])(t, (void*)0x403df5f)
               : 0;

    Obj* old = out->mTarget;
    if (r != old)
    {
        if (r)
            ((Vfn0)r->mpVtbl->mSlots[kVt00])(r);
        out->mTarget = r;
        if (old)
            ((Vfn0)old->mpVtbl->mSlots[kVt04])(old);
    }
    out->u0 = 0;
    return 1;
}

// Helper inside 00dc5b50's extent (unreferenced block, no marker).
char FUN_00dc5bc0(Obj* self)
{
    Obj* p = self->mpObjB7c;
    if (p)
    {
        self->mpObjB7c = 0;
        ((Vfn0)p->mpVtbl->mSlots[kVtC0])(p);
    }
    return 1;
}

// ================================================================================
// 00dc5bf0
// ================================================================================
// @ 0x00dc5bf0
char FUN_00dc5bf0(Obj* self, void* a1, void* a2, void* a3, void* a4, OutBF0* out)
{
    if (out)
    {
        out->i0 = 0;
        out->f4 = 0.0f;
    }

    HitInfo* h = self->C9c0200();
    if (h)
    {
        out->v8 = h->v4;

        int idx = DAT_016c7aa4->mpSlot->mIndex;
        out->f14 = ((StimEntry*)h->mField28)[idx].mField00;
    }
    else
    {
        Vec3f* p = (Vec3f*)((VfnP)self->mSub34.mpVtbl->mSlots[kVt2C])(&self->mSub34);
        out->v8 = *p;
    }

    ((Vfn0)self->mSub34.mpVtbl->mSlots[kVtEC])(&self->mSub34);
    return 1;
}

// ================================================================================
// 00dc5c90
// ================================================================================
// @ 0x00dc5c90
float FUN_00dc5c90(Obj* self)
{
    int idx = DAT_016c7aa4->mpSlot->mIndex;
    if (self->C9f1c0()->mState == 4)
        return 1.0f;
    if (self->C9f1c0()->mState == 6 && self->mFieldB00 <= idx)
        return 1.0f;
    return 0.0f;
}

// ================================================================================
// 00dc5ce0
// ================================================================================
// @ 0x00dc5ce0
char FUN_00dc5ce0(Obj* self, void* a1, void* a2, void* a3, void* a4, OutCE0* out)
{
    if (out)
    {
        out->f4  = DAT_01470f1c;
        out->u0  = 0;
        out->f8  = 0.0f;
        out->bC  = 1;
        out->f10 = DAT_0169fa68;
        out->f14 = DAT_0169fa6c;
        out->f18 = DAT_0169fa70;
    }
    return 1;
}

// ================================================================================
// 00dc5d40
// ================================================================================
// @ 0x00dc5d40
char FUN_00dc5d40(Obj* self, void* a1, void* a2, void* a3, void* a4,
                  float* pAccum, void* a6, float delta)
{
    Obj* a = self->mpBehaviorTree->mStimA.PlayIdleAnimation(0x10000, 0);
    if (!a)
        return 0;
    if (self->C9f1c0()->mState == 1)
        return 0;

    Obj* t = a->mpField2c
           ? (Obj*)((VfnPI)a->mpField2c->mpVtbl->mSlots[kVt0C])(a->mpField2c,
                                                               (void*)0x13f94d4)
           : 0;
    if (t->GetFileCount() == 2)
        return 0;

    Obj*   gt  = (Obj*)((VfnP)t->mpVtbl->mSlots[kVt08])(t);
    Vec3f* pp  = (Vec3f*)((VfnP)gt->mpVtbl->mSlots[kVt2C])(gt);

    Sub*   s34 = &self->mSub34;
    Vec3f* q   = (Vec3f*)((VfnP)s34->mpVtbl->mSlots[kVt2C])(s34);

    float dx = q->x - pp->x;
    float dy = q->y - pp->y;
    float dz = q->z - pp->z;
    float dist = sqrtf((dz * dz + dy * dy) + dx * dx);

    float lim = FUN_00f264b0((void*)((VfnP)t->mpVtbl->mSlots[kVt0C])(t));
    if (lim == 0.0f)
        lim = FUN_00f264b0(self);
    lim = lim * DAT_013eb1c0;
    if (dist > lim)
        return 0;

    *pAccum = *pAccum + delta;
    if (*pAccum > DAT_01470f1c)
    {
        *pAccum = 0.0f;

        float inv = DAT_01485720 / dist;
        Vec3f dir;
        dir.x = inv * dx;
        dir.y = dy * inv;
        dir.z = inv * dz;

        float step  = ((VfnF)s34->mpVtbl->mSlots[kVtCC])(s34) * DAT_01486114;
        Vec3f mv;
        mv.x = dir.x * step;
        mv.y = dir.y * step;
        mv.z = dir.z * step;

        Vec3f* p = (Vec3f*)((VfnP)s34->mpVtbl->mSlots[kVt2C])(s34);
        Vec3f  dst;
        dst.x = p->x + mv.x;
        dst.y = p->y + mv.y;
        dst.z = p->z + mv.z;

        Vec3f* r = SP_PlanetModel()->DirectionToSurfacePosition(&mv, &dst);
        dst = *r;

        if (self->C9e940(&dst))
        {
            ((VfnF3I)s34->mpVtbl->mSlots[kVtE0])(s34, &dst, 1.0f,
                                                 DAT_01470f1c, 0);
            return 1;
        }

        Obj* g2 = (Obj*)((VfnFF)gt->mpVtbl->mSlots[kVt2C])(gt, lim,
                                                           lim + DAT_0140c6e8);
        self->Take((Vec3f*)g2);
    }
    return 1;
}

// ================================================================================
// 00dc5fe0
// ================================================================================
// @ 0x00dc5fe0
float FUN_00dc5fe0(Obj* self, void* a1, void* a2, void* a3,
                   BehaviorStim* stim, uint8_t* pFlag)
{
    Obj* c = self ? (Obj*)&self->mSub508 : 0;

    if (!DAT_0168d824)
    {
        void* p = FUN_00f473a0(0x24, "Simulator/SimSingleton", 0, 0, 0, 0);
        DAT_0168d824 = p ? ((Alloc*)p)->Ctor() : 0;
    }

    Simulator* sim = (Simulator*)DAT_0168d824;
    Obj* hit = sim->PickNearest(c, 0.0f, 0.0f);
    if (hit)
    {
        if (stim)
            stim->GetAny();
        *pFlag = 1;
        stim->mpTarget = hit;
        stim->mField08 = 0;
        stim->mStimulusID = 0;
        return 1.0f;
    }
    return 0.0f;
}

// ================================================================================
// 00dc6070
// ================================================================================
// @ 0x00dc6070
char FUN_00dc6070(Obj* self, void* a1, void* a2, void* a3, void* a4,
                  Out6070* out, Ctx6070* ctx, void* a7)
{
    if (out)
        out->mTarget = 0;

    Obj* c = self ? (Obj*)&self->mSub508 : 0;
    if (!FUN_00dc4e20(c, ctx->mpTarget))
        return 0;

    out->f0 = DAT_01486110;

    Obj* p = ctx->mpTarget;
    if (p != out->mTarget)
    {
        Obj* old = out->mTarget;
        if (p)
            ((Vfn0)p->mpVtbl->mSlots[kVt60])(p);
        out->mTarget = p;
        if (old)
            ((Vfn0)old->mpVtbl->mSlots[kVt64])(old);
    }

    Sub*   s34 = &self->mSub34;
    Vec3f* v   = (Vec3f*)((VfnP)s34->mpVtbl->mSlots[kVt2C])(s34);

    AudioSys* sys = EA_Audio_GetSystemAT();
    void* h = sys ? (void*)((VfnP)sys->mpVtbl->mSlots[kVt20])(sys) : 0;

    Start3dSoundByName(DAT_0147c3fc[self->mFieldB20], h, v->x, v->y, v->z);
    return 1;
}

// ================================================================================
// 00dc6140
// ================================================================================
// @ 0x00dc6140
void FUN_00dc6140(Obj* self, void* a1, void* a2, void* a3, void* a4, Out6140* out)
{
    if (!out)
        return;
    Obj* p = out->mTarget;
    if (!p)
        return;
    ((Vfn0)p->mpVtbl->mSlots[kVt64])(p);
}

// ================================================================================
// 00dc6160
// ================================================================================
// @ 0x00dc6160
char FUN_00dc6160(Obj* self, void* a1, void* a2, void* a3, void* a4,
                  Out6160* out, void* a6, float delta)
{
    out->f0 = out->f0 - delta;

    Obj* c = self ? (Obj*)&self->mSub508 : 0;
    if (!FUN_00dc4e20(c, out->mTarget))
        return 0;

    Obj* t = 0;
    if (out->mTarget)
        t = (Obj*)((VfnPI)out->mTarget->mpVtbl->mSlots[kVt5C])(out->mTarget,
                                                               (void*)0x1186577);
    if (t)
    {
        Sub*   s34 = &self->mSub34;
        Vec3f* p1  = (Vec3f*)((VfnP)s34->mpVtbl->mSlots[kVt2C])(s34);
        Vec3f* p2  = (Vec3f*)((VfnP)t->mpVtbl->mSlots[kVt2C])(t);

        float dz = p2->z - p1->z;
        float dy = p2->y - p1->y;
        float dx = p2->x - p1->x;
        out->f0 = sqrtf((dz * dz + dy * dy) + dx * dx);

        float lim = FUN_00f264b0(self);
        if (lim < out->f0)
        {
            Obj* q = self->mpObjB7c;
            if (q)
            {
                self->mpObjB7c = 0;
                ((Vfn0)q->mpVtbl->mSlots[kVtC0])(q);
            }
            return 0;
        }
    }

    if (out->f0 < 0.0f)
    {
        self->C4d00((void*)t);
        return 0;
    }
    return 1;
}

// ================================================================================
// 00dc6250
// ================================================================================
// @ 0x00dc6250
float FUN_00dc6250(Obj* self, void* a1, void* a2, void* a3, void* a4, void* a5)
{
    Obj* c = self ? (Obj*)&self->mSub508 : 0;

    if (!DAT_0168d824)
    {
        void* p = FUN_00f473a0(0x24, "Simulator/SimSingleton", 0, 0, 0, 0);
        DAT_0168d824 = p ? ((Alloc*)p)->Ctor() : 0;
    }

    Simulator* sim = (Simulator*)DAT_0168d824;
    Obj* hit = sim->PickNearest(c, 0.0f, 0.0f);
    if (hit)
    {
        Obj* p = (Obj*)((VfnP)hit->mpVtbl->mSlots[kVt08])(hit);
        Obj* old = self->mpObjB7c;
        if (p != old)
        {
            if (p)
                ((Vfn0)p->mpVtbl->mSlots[kVtBC])(p);
            self->mpObjB7c = p;
            if (old)
                ((Vfn0)old->mpVtbl->mSlots[kVtC0])(old);
        }

        FUN_00dc4610(self);
        return 1.0f;
    }
    return 0.0f;
}

// ================================================================================
// 00dc6300
// ================================================================================
// @ 0x00dc6300
float FUN_00dc6300(Obj* self)
{
    Obj* h = self->mpBehaviorTree->mStimA.PlayIdleAnimation(0x10000, 0);
    if (h)
    {
        Obj* src = h->mpField2c;
        Obj* t = src ? (Obj*)((VfnPI)src->mpVtbl->mSlots[kVt0C])(src, (void*)0x13f94d4)
                     : 0;
        if (FUN_00dc4e20(&self->mSub508, t))
        {
            Vtbl* vt = t->mpVtbl;
            Obj*  g  = (Obj*)((VfnP)vt->mSlots[kVt08])(t);
            self->C4d00((void*)g);
            FUN_00dc4610(self);
            return 1.0f;
        }
    }
    return 0.0f;
}

// ================================================================================
// 00dc6370
// ================================================================================
// @ 0x00dc6370
void FUN_00dc6370(Obj* self)
{
    if (self && self->mpBehaviorTree && self->mpBehaviorTree->mpVtbl &&
        SP_GameTimeManager())
    {
        double t = (double)SP_GameTimeManager()->Now() * DAT_013f9428;
        FUN_00bc86e0(t, self->mpBehaviorTree->mpVtbl, self,
                     &self->mpBehaviorTree->mStimB,
                     self->mpBehaviorTree->mpField5e8,
                     self->mpBehaviorTree->mpField5fc);
        self->mpBehaviorTree->Cb3d0();
    }
}

// ================================================================================
// 00dc6420
// ================================================================================
// @ 0x00dc6420
bool Obj::Cdc6420(void* a1)
{
    return mField50 != mField54;
}

// Second real function that follows 00dc6420's `ret 4` (no marker).
void FUN_00dc6430(Obj* o, Vec3f* pos, float d, float a, float b, float c)
{
    if (!o)
        return;

    Obj* r = (Obj*)((VfnPI)o->mpVtbl->mSlots[kVtB8])(o, (void*)0x137e8e0);
    if (!r)
        return;
    if (r->mByte2a4 & 4)
        return;

    Sub* s34 = &r->mSub34;
    if (d > DAT_01485378)
    {
        ((VfnF3)s34->mpVtbl->mSlots[kVtE8])(s34, pos, d, a);
    }
    else
    {
        Vec3f* p = (Vec3f*)((VfnP)s34->mpVtbl->mSlots[kVt2C])(s34);
        float dx = p->x - pos->x;
        float dy = p->y - pos->y;
        float dz = p->z - pos->z;
        float dist = sqrtf((dz * dz + dy * dy) + dx * dx);
        if (dist > DAT_013ec4d0)
            ((VfnF3I)s34->mpVtbl->mSlots[kVtE0])(s34, pos, 1.0f,
                                                 DAT_01470f1c, 0);
        else
            ((VfnF2)s34->mpVtbl->mSlots[kVtE4])(s34, pos, 1.0f);
    }

    float v = ((VfnFI)s34->mpVtbl->mSlots[kVtCC])(s34, 0) * c;
    ((VfnF1)s34->mpVtbl->mSlots[kVtC4])(s34, v);
}

// ================================================================================
// 00dc6530
// ================================================================================
// @ 0x00dc6530
void Obj::Cdc6530()
{
    if (mpAnim9c)
    {
        Obj* mgr = FUN_00b3d240();
        AnimCreat* h = (AnimCreat*)((VfnP)mgr->mpVtbl->mSlots[kVt74])(mgr);
        ((VfnPI)h->mpVtbl->mSlots[kVt3C])(h, mpAnim9c);

        AnimCreat* q = mpAnim9c;
        if (q)
        {
            mpAnim9c = 0;
            q->Release();
        }
    }

    if (mpFieldA4)
    {
        ((VfnI1)mpFieldA4->mpVtbl->mSlots[kVt0C])(mpFieldA4, 0);
        Obj* old = mpFieldA4;
        mpFieldA4 = 0;
        if (old)
            ((Vfn0)old->mpVtbl->mSlots[kVt04])(old);
    }
}

// ================================================================================
// 00dc65b0
// ================================================================================
// @ 0x00dc65b0
void Obj::Cdc65b0()
{
    if (mByteAc)
        return;
    mByteAc = 1;

    AnimCreat* p = mpAnim9c;
    void* h = (void*)((VfnP2)p->mpVtbl->mSlots[kVt08])(p, (void*)0x64be2be, 0);
    mpFieldA8 = (Obj*)h;
    ((VfnV2)mpAnim9c->mpVtbl->mSlots[kVt0C])(mpAnim9c, h, 1);
    ((VfnPI)mpAnim9c->mpVtbl->mSlots[kVt18])(mpAnim9c, mpFieldA8);

    if (mpFieldA4)
    {
        ((VfnI1)mpFieldA4->mpVtbl->mSlots[kVt0C])(mpFieldA4, 0);
        Obj* old = mpFieldA4;
        mpFieldA4 = 0;
        if (old)
            ((Vfn0)old->mpVtbl->mSlots[kVt04])(old);
    }
}

// ================================================================================
// 00dc6640  SP::IsFormationMember
// ================================================================================
// @ 0x00dc6640
bool FUN_00dc6640(PtrVec* v, Obj** pSelf)
{
    void** end = v->mpEnd;
    void** it  = v->mpBegin;

    if (it != end)
    {
        do
        {
            Obj*  s      = *pSelf;
            void* target = s ? (void*)&s->mSub34 : 0;
            if (*it == target)
                break;
        } while (++it != end);
    }
    return it != end;
}