// =============================================================================================
//  Slice s00d7e290 (batch gold6) -- SP::cGameNoun behaviour-tree predicates.
//  Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
//
//   0x00d7e290 FUN_00d7e290   pick the creature's idle-animation target (range/stage gated)
//   0x00d7e340 FUN_00d7e340   "same species, both inside DAT_01582ec0 of a shared reference"
//   0x00d7e4e0 FUN_00d7e4e0   "my behaviour target is an approachable object" test
//   0x00d7e580 FUN_00d7e580   heading/goal distance report into the out record
//   0x00d7e6e0 FUN_00d7e6e0   face the creature towards this object (always succeeds)
//   0x00d7e860 FUN_00d7e860   attach a behaviour-tree node, report list ownership
//   0x00d7e910 FUN_00d7e910   "play a social animation" test
//   0x00d7e9d0 FUN_00d7e9d0   "my owner is in the 0x2d852f3 state" test
//   0x00d7ea20 FUN_00d7ea20   "my own action list still has spare slots" test
//   0x00d7ea70 FUN_00d7ea70   reset the speed holder on the owner when idle
//
//  All ten functions share the behaviour-tree calling shape: arg1 is the creature the predicate is
//  evaluated for, arg5 an "out" record, arg6 a result flag and arg8 a key source.  Their results are
//  returned in st0 (floats), al (bool) or nothing (void).
//
//  External callees are modelled with the cSelf trick: a helper class whose member functions stand in
//  for the retail routines that take their object in ecx.  MSVC __thiscall is callee-pops-args, which
//  is what the retail `ret N` epilogues of those routines do.  Virtual slots are reached through B<n>
//  vtable-view classes: B<n> carries n+1 virtual slots (offsets 0x00 .. 4n), so deriving from B<k-1>
//  and adding the called method places it at retail offset 4k.
// =============================================================================================
#include "types.h"
#include <math.h>

// ---- vtable leaders.  B<n> has n+1 virtual slots at +0x00 .. +4n --------------------------------
struct B00 { virtual void a00() {} };
struct B01 : B00 { virtual void a01() {} };
struct B02 : B01 { virtual void a02() {} };
struct B03 : B02 { virtual void a03() {} };
struct B04 : B03 { virtual void a04() {} };
struct B05 : B04 { virtual void a05() {} };
struct B06 : B05 { virtual void a06() {} };
struct B07 : B06 { virtual void a07() {} };
struct B08 : B07 { virtual void a08() {} };
struct B09 : B08 { virtual void a09() {} };
struct B10 : B09 { virtual void a10() {} };
struct B11 : B10 { virtual void a11() {} };
struct B12 : B11 { virtual void a12() {} };
struct B13 : B12 { virtual void a13() {} };
struct B14 : B13 { virtual void a14() {} };
struct B15 : B14 { virtual void a15() {} };
struct B16 : B15 { virtual void a16() {} };
struct B17 : B16 { virtual void a17() {} };
struct B18 : B17 { virtual void a18() {} };
struct B19 : B18 { virtual void a19() {} };
struct B20 : B19 { virtual void a20() {} };
struct B21 : B20 { virtual void a21() {} };
struct B22 : B21 { virtual void a22() {} };
struct B23 : B22 { virtual void a23() {} };
struct B24 : B23 { virtual void a24() {} };
struct B25 : B24 { virtual void a25() {} };
struct B26 : B25 { virtual void a26() {} };
struct B27 : B26 { virtual void a27() {} };
struct B28 : B27 { virtual void a28() {} };
struct B29 : B28 { virtual void a29() {} };
struct B30 : B29 { virtual void a30() {} };
struct B31 : B30 { virtual void a31() {} };
struct B32 : B31 { virtual void a32() {} };
struct B33 : B32 { virtual void a33() {} };
struct B34 : B33 { virtual void a34() {} };
struct B35 : B34 { virtual void a35() {} };
struct B36 : B35 { virtual void a36() {} };
struct B37 : B36 { virtual void a37() {} };
struct B38 : B37 { virtual void a38() {} };
struct B39 : B38 { virtual void a39() {} };
struct B40 : B39 { virtual void a40() {} };
struct B41 : B40 { virtual void a41() {} };
struct B42 : B41 { virtual void a42() {} };
struct B43 : B42 { virtual void a43() {} };
struct B44 : B43 { virtual void a44() {} };
struct B45 : B44 { virtual void a45() {} };

// ---- small value types --------------------------------------------------------------------------
struct cVec3 { float x, y, z; };

// ---- globals ------------------------------------------------------------------------------------
extern float DAT_013ec4b8;
extern float DAT_013f08c0;
extern float DAT_01470f1c;
extern float DAT_01473c70;
extern float DAT_01486110;
extern float DAT_01485720;
extern float DAT_01572070;
extern float DAT_01582ec0;

// ---- tag ids passed to the engine's object lookups ----------------------------------------------
enum
{
    TAG_CREATURE_TARGET = 0x0ce9f6639,
    TAG_ANIM_TARGET     = 0x137e8e0,
    TAG_SOCIAL_ANIM     = 0x03a25119,
    TAG_ANIM_STATE      = 0x0915f7deb,
    TAG_INTERRUPT_ANIM  = 0x2481db0,
    TAG_LIST_STATE      = 0x2d852f3
};

struct cGameObj;                    // arg1 of every predicate; laid out below
struct cBehaviorMgr;                // the per-creature behaviour/stimuli block (cGameObj::mpB4c)
struct cHolder;                     // the per-creature speed holder (cGameObj::mpB54)

// ---- cSelf: stand-ins for the retail routines that take their object in ecx ---------------------
// Letting each of these be a member function of a cast target reproduces both the ecx setup and the
// callee-side argument cleanup of the originals.
struct cSelf
{
    // behaviour stimuli block helpers (ecx = &cBehaviorMgr::mStimuli)
    void*  FUN_00bc96a0(int a, int b);
    void   FUN_00bc98f0(int a, int b);
    void   FUN_00bc97f0(int a, int b, float c, void* d);

    // noun / object services
    cGameObj* FUN_00c04590();
    void*     FUN_00c6acc0();
    uint8_t   FUN_00c6ac40();
    void*     FUN_00ca71d0();
    cGameObj* FUN_00b1fdb0();
    void*     FUN_00b81630(void* a, void* b);

    // creature actions
    void    FUN_00c12310(int a, int b, void* c);
    void    FUN_00c1c5c0(int a, void* b);
    uint8_t FUN_00c0e0c0(int a);
    void    FUN_00c12190(int a, int b, int c);
    uint8_t FUN_00c42e20();
    uint8_t FUN_00c0b860(void* a);
    void    FUN_00c14750(int a);
    int     FUN_00c0f570();
    void*   FUN_00c0f780();
    void*   FUN_00c0f8a0(void* a);

    // out-record release helper (ecx = the record's first object)
    void FUN_00d997e0();
};

// ---- free (cdecl) engine entry points -----------------------------------------------------------
void*  FUN_00b3d300();                 // SP::NounManager()
void*  FUN_00b3d350();                 // noun manager accessor used by the goal conversion
void*  FUN_00d998f0(void* a);          // behaviour lookup by stimuli handle
void*  FUN_00d99a10(void* a);
void*  FUN_00d99470(void* a);
void*  FUN_00d999d0(void* a);
float  FUN_00d99a60(int a);            // heading-distance readback
void*  FUN_00ae6740(void* a);
void*  FUN_00d99420(void* a, uint32_t key);
void   FUN_00d996e0(void* a, void* b);
void*  FUN_00d2ec30(void* a);

// ---- per-creature sub-objects -------------------------------------------------------------------
struct cBehaviorMgr
{
    uint8_t  pad000[0x08];
    uint8_t  mStimuli;              // +0x008  idle/social animation stimulus block
    uint8_t  pad009[0x1d0 - 0x09];
    uint8_t  mLookup;               // +0x1d0  keyed lookup table root
    uint8_t  pad1d1[0x1d8 - 0x1d1];
    uint32_t mKind;                 // +0x1d8  behaviour-tree kind id
};

struct cHolder
{
    uint8_t pad000[0x80];
    float   mSpeed;                 // +0x080  movement speed driven by the root predicate
};

// ---- the "out" record written by the predicates -------------------------------------------------
struct cOutRec
{
    void*    mpCur;                 // +0x00  object the record used to hold (cleared on success)
    void*    mpNew;                 // +0x04  object produced by the predicate
    void*    mpAux;                 // +0x08  auxiliary handle of the produced object
    uint8_t  pad00c[0x18 - 0x0c];
    int32_t  m18;                   // +0x18  result scalar (flag or truncated distance)
    uint32_t m1c;                   // +0x1c  record kind
    uint32_t m20;                   // +0x20  record payload
};

// ---- key source passed as arg8 (a vector of keyed entries) --------------------------------------
// The retail code reads the key as an unaligned dword at +0x2d, so this record is packed.
#pragma pack(push, 1)
struct cKeySrc
{
    uint8_t  pad000[0x2d];
    uint32_t mKey;                  // +0x2d
};
#pragma pack(pop)

// ---- concrete polymorphic bodies embedded in cGameObj -------------------------------------------
struct cBodyC0 : public B28                                    // +0x0c0
{
    virtual float v74(void* a, float b) { (void)a; (void)b; return 0.0f; }
};

struct cBody5a8 : public B02                                   // +0x5a8
{
    virtual void* v0c() { return 0; }
};

// ---- the creature / game-noun object (arg1) -----------------------------------------------------
struct cGameObj
{
    uint8_t  pad000[0x40];
    int32_t  mListBegin040;         // +0x040  action list begin (byte address)
    int32_t  mListEnd044;           // +0x044  action list end (byte address)
    uint8_t  pad048[0x0c0 - 0x48];
    cBodyC0  mC0;                   // +0x0c0  creature sub-object (vptr first)
    uint8_t  pad0c4[0x135 - 0xc4];
    uint8_t  mFlag135;              // +0x135  "has a weapon/prop attached"
    uint8_t  pad136[0x15c - 0x136];
    int32_t  mAction15c;            // +0x15c  current action/animation state id
    uint8_t  pad160[0x164 - 0x160];
    void*    mpOwner164;            // +0x164  owning game object (back pointer)
    void*    mpLink168;             // +0x168  intrusive list link; == &mpLink168 when unlinked
    uint8_t  pad16c[0x5a8 - 0x16c];
    cBody5a8 m5a8;                  // +0x5a8  reported target sub-object (vptr first)
    uint8_t  pad5ac[0xb20 - 0x5ac];
    uint32_t mIdB20;                // +0xb20  unique object id
    uint8_t  padB24[0xb4c - 0xb24];
    cBehaviorMgr* mpB4c;            // +0xb4c
    uint8_t  padB50[0xb54 - 0xb50];
    cHolder* mpB54;                 // +0xb54
    uint8_t  padB58[0xb5e - 0xb58];
    uint8_t  mFlagB5e;              // +0xb5e  "movement locked"
    uint8_t  padB5f[0xb88 - 0xb5f];
    int32_t  mStageB88;             // +0xb88  development stage
    uint8_t  padB8c[0x1698 - 0xb8c];
    void*    mp1698;                // +0x1698  behaviour-tree root of this creature
};

// ---- the owner/link pair embedded at +0x164 of every object -------------------------------------
// Retail reaches the pair through an embedded record (+0x164/+0x168) rather than as two loose
// members of cGameObj; modelling it as a view keeps MSVC from folding both loads into one
// 0x164(reg) memory operand.
struct cOwnerLink
{
    cGameObj* mpOwner;              // +0x00  owning game object
    void*     mpLink;               // +0x04  intrusive link; == its own address while unlinked
};

struct cGameObjB
{
    uint32_t  pad000[0x59];         // +0x000 .. +0x163
    cOwnerLink mOwnerLink;          // +0x164  (same bytes as cGameObj::mpOwner164)
};

static __inline bool ProbeSelfLinked(cGameObj* list)
{
    return list->mpLink168 != (void*)&list->mpLink168;
}

// ---- object produced by the slot-0x08 accessor --------------------------------------------------
struct cSlotObj
{
    uint8_t pad000[0x77];
    uint8_t mHasGoal;               // +0x077  non-zero = the goal slot is already resolved
};

// ---- object descriptor returned by the slot-0x5c lookup followed by FUN_00ca71d0 ---------------
struct cTargetInfo
{
    void*   mpObj;                  // +0x00  described object
    uint8_t pad004[0x10 - 0x04];
    int32_t mKind;                  // +0x10  descriptor kind (1 = approachable object)
};

// ---- vtable views: each adds its method at the retail slot offset -------------------------------
struct cVtV08  : B01 { virtual cSlotObj* v08() { return 0; } };                       // +0x08
struct cVtV0c  : B02 { virtual void* v0c() { return 0; } };                           // +0x0c
struct cVtV2cP : B10 { virtual cVec3* v2c() { return 0; } };                          // +0x2c (0 args)
struct cVtV2c1 : B10 { virtual int v2c(float a) { (void)a; return 0; } };             // +0x2c (1 arg)
struct cVtV2c3 : B10 { virtual cVec3* v2c(cVec3* a, float b, float c)
                       { (void)a; (void)b; (void)c; return 0; } };                    // +0x2c (3 args)
struct cVtV2cB : B10 { virtual uint8_t v2c() { return 0; } };                         // +0x2c (bool)
struct cVtV5c  : B22 { virtual cGameObj* v5c(int a) { (void)a; return 0; } };         // +0x5c (id)
struct cVtV5cV : B22 { virtual cVec3* v5c(cVec3* a) { (void)a; return 0; } };         // +0x5c (vec)
struct cVtV74I : B28 { virtual float v74(int a) { (void)a; return 0.0f; } };          // +0x74 (1 arg)
struct cVtV74B : B28 { virtual float v74(void* a, float b)
                       { (void)a; (void)b; return 0.0f; } };                          // +0x74 (2 args)
struct cVtV74F : B28 { virtual float v74() { return 0.0f; } };                        // +0x74 (0 args)
struct cVtVb8  : B45 { virtual void* vb8(int a) { (void)a; return 0; } };             // +0xb8

// =================================================================================================
// @ 0x00d7e290
float FUN_00d7e290(cGameObj* a1, void* a2, void* a3, void* a4, cOutRec* a5, uint8_t* a6,
                   void* a7, cKeySrc* a8)
{
    void* slot = ((cSelf*)&a1->mpB4c->mStimuli)->FUN_00bc96a0(0x400, 0);

    cGameObj* found = (cGameObj*)FUN_00d998f0(FUN_00d99a10(slot));
    if (found != 0)
    {
        cGameObj* cur = ((cVtV5c*)found)->v5c(TAG_CREATURE_TARGET);
        if (cur != 0)
        {
            int32_t stage = a1->mStageB88;
            if (stage >= 5 || stage >= cur->mStageB88)
                return 0.0f;
        }

        ((cSelf*)&a1->mpB4c->mStimuli)->FUN_00bc98f0(0x400, 0);
        if (a5 != 0)
            ((cSelf*)a5)->FUN_00d997e0();
        *a6 = 1;
        a5->mpNew = found;
        return 1.0f;
    }

    ((cSelf*)&a1->mpB4c->mStimuli)->FUN_00bc98f0(0x400, 0);
    return 0.0f;
}

// =================================================================================================
// @ 0x00d7e340
float FUN_00d7e340(cGameObj* a1, void* a2, void* a3, void* a4, cOutRec* a5, uint8_t* a6,
                   void* a7, cKeySrc* a8)
{
    cGameObj* av = ((cSelf*)FUN_00b3d300())->FUN_00b1fdb0();
    if (av != 0)
    {
        cGameObj* idAv = ((cSelf*)av)->FUN_00c04590();
        if (idAv == ((cSelf*)a1)->FUN_00c04590())
        {
            void* slot = ((cSelf*)&av->mpB4c->mStimuli)->FUN_00bc96a0(0x400, 0);
            if (slot != 0)
            {
                float radius2 = DAT_01582ec0 * DAT_01582ec0;
                cVec3* ref = (cVec3*)((cSelf*)((cSelf*)av)->FUN_00c04590())->FUN_00c6acc0();

                cVec3* p1 = ((cVtV2cP*)&a1->mC0)->v2c();
                float d1x = p1->x - ref->x;
                float d1y = p1->y - ref->y;
                float d1z = p1->z - ref->z;

                cVec3* p2 = ((cVtV2cP*)&av->mC0)->v2c();
                float d2x = p2->x - ref->x;
                float d2y = p2->y - ref->y;
                float d2z = p2->z - ref->z;

                if (radius2 > d2x * d2x + d2y * d2y + d2z * d2z)   // avatar inside the radius
                {
                    if (radius2 > d1x * d1x + d1y * d1y + d1z * d1z)   // and so are we
                    {
                        cGameObj* target = (cGameObj*)FUN_00d99470(FUN_00d999d0(slot));
                        if (target != 0)
                        {
                            if (target->mIdB20 != a1->mIdB20)
                            {
                                if (a5 != 0)
                                    ((cSelf*)a5)->FUN_00d997e0();
                                *a6 = 1;
                                a5->mpNew = &target->m5a8;
                                return 1.0f;
                            }
                        }
                    }
                }
            }
        }
    }
    return 0.0f;
}

// =================================================================================================
// @ 0x00d7e4e0
float FUN_00d7e4e0(cGameObj* a1, void* a2, void* a3, void* a4, cOutRec* a5, uint8_t* a6,
                   void* a7, cKeySrc* a8)
{
    cGameObj* found = (cGameObj*)FUN_00d998f0(a1->mp1698);
    if (found != 0)
    {
        void* r = ((cVtV5c*)found)->v5c(TAG_ANIM_TARGET);
        if (r != 0)
        {
            cTargetInfo* info = (cTargetInfo*)((cSelf*)r)->FUN_00ca71d0();
            if (info->mKind == 1)
            {
                cGameObj* obj = (cGameObj*)info->mpObj;
                if (obj != 0)
                {
                    if (((cVtV2cB*)obj)->v2c() == 0)
                    {
                        if (obj != ((cVtV0c*)&a1->m5a8)->v0c())
                        {
                            if (a5 != 0)
                                ((cSelf*)a5)->FUN_00d997e0();
                            *a6 = 1;
                            a5->mpNew = FUN_00ae6740(info->mpObj);
                            return 1.0f;
                        }
                    }
                }
            }
        }
    }
    return 0.0f;
}

// =================================================================================================
// @ 0x00d7e580
float FUN_00d7e580(cGameObj* a1, void* a2, void* a3, void* a4, cOutRec* a5, uint8_t* a6,
                   void* a7, cKeySrc* a8)
{
    cGameObj* found = (cGameObj*)FUN_00d998f0(a1->mp1698);
    if (found != 0)
    {
        cSlotObj* v = ((cVtV08*)found)->v08();

        void* goal;
        if (v->mHasGoal != 0)
        {
            goal = (void*)((cVtV2cP*)v)->v2c();
        }
        else
        {
            uint32_t local = 0;
            void* q = (void*)((cVtV2cP*)v)->v2c();
            goal = ((cSelf*)FUN_00b3d350())->FUN_00b81630(&local, q);
        }

        cSlotObj* v2 = ((cVtV08*)found)->v08();
        float fv = ((cVtV74I*)v2)->v74(1);
        float fa = ((cVtV74B*)&a1->mC0)->v74(goal, fv);
        int32_t h = ((cVtV2c1*)&a1->mC0)->v2c(fa);
        if (FUN_00d99a60(h) > DAT_01572070 * 2.0f + DAT_013f08c0)
        {
            if (a5 != 0)
                ((cSelf*)a5)->FUN_00d997e0();

            a5->mpAux = (void*)((cVtV0c*)found)->v0c();

            cSlotObj* v3 = ((cVtV08*)found)->v08();

            // Accumulated left-to-right straight out of the v74 calls, exactly as retail's x87 does.
            a5->m18 = (int32_t)(((cVtV74F*)&a1->mC0)->v74() +
                                ((cVtV74F*)v3)->v74() + DAT_01486110);
            a5->m1c = 3;
            a5->m20 = 0;
            *a6 = 1;
            return 1.0f;
        }
    }
    return 0.0f;
}

// =================================================================================================
// @ 0x00d7e6e0
bool FUN_00d7e6e0(cGameObj* a1, void* a2, void* a3, void* a4, cOutRec* a5, uint8_t* a6,
                  void* a7, cKeySrc* a8)
{
    cGameObj* found = (cGameObj*)FUN_00d998f0(a1->mp1698);
    if (found != 0)
    {
        cSlotObj* node = ((cVtV08*)found)->v08();

        cVec3* pa = ((cVtV2cP*)&a1->mC0)->v2c();
        cVec3* pb = ((cVtV2cP*)node)->v2c();

        cVec3 dif;
        dif.x = pb->x - pa->x;
        dif.y = pb->y - pa->y;
        dif.z = pb->z - pa->z;

        float inv = 1.0f / sqrtf(dif.x * dif.x + dif.y * dif.y + dif.z * dif.z + DAT_013ec4b8);

        cVec3 nrm;
        nrm.x = dif.x * inv;
        nrm.y = dif.y * inv;
        nrm.z = dif.z * inv;

        cVec3* fwd = ((cVtV5cV*)&a1->mC0)->v5c(&dif);
        if (fwd->x * nrm.x + fwd->y * nrm.y + fwd->z * nrm.z < 0.0f)
        {
            ((cSelf*)a1)->FUN_00c12310(TAG_INTERRUPT_ANIM, -1, 0);
            cVec3* pt = ((cVtV2c3*)&a1->mC0)->v2c(&nrm, 1.0f, DAT_01470f1c);
            ((cSelf*)a1)->FUN_00c1c5c0(2, pt);
        }
    }

    if (((cSelf*)&a1->mC0)->FUN_00c42e20())
        if (!((cSelf*)a1)->FUN_00c0e0c0(TAG_ANIM_STATE))
            ((cSelf*)a1)->FUN_00c12190(TAG_ANIM_STATE, 1, -1);

    return true;
}

// =================================================================================================
// @ 0x00d7e860
float FUN_00d7e860(cGameObj* a1, void* a2, void* a3, void* a4, cOutRec* a5, uint8_t* a6,
                   void* a7, cKeySrc* a8)
{
    if (a5 != 0)
        ((cSelf*)a5)->FUN_00d997e0();
    *a6 = 1;

    void* e = FUN_00d99420(&a1->mpB4c->mLookup, a8->mKey);
    FUN_00d996e0(e, a5);

    cOwnerLink* link = &((cGameObjB*)((cSelf*)a1)->FUN_00c04590())->mOwnerLink;
    a5->m18 = (int32_t)(a1 == link->mpOwner &&
                        ProbeSelfLinked(((cSelf*)a1)->FUN_00c04590()));

    void* r = a5->mpNew;
    cGameObj* cur = r != 0 ? ((cVtV5c*)r)->v5c(TAG_CREATURE_TARGET) : 0;
    cGameObj* x = (cGameObj*)FUN_00d99470(cur);
    if (x != 0 && ((cSelf*)a1)->FUN_00c0b860(x))
        return 1.0f;
    return 0.0f;
}

// =================================================================================================
// @ 0x00d7e910
float FUN_00d7e910(cGameObj* a1, void* a2, void* a3, void* a4, cOutRec* a5, uint8_t* a6,
                   void* a7, cKeySrc* a8)
{
    void* slot = ((cSelf*)&a1->mpB4c->mStimuli)->FUN_00bc96a0(0, 0x8000);
    if (slot != 0)
        return 1.0f;

    cGameObj* o = ((cSelf*)a1)->FUN_00c04590();
    if (o->mAction15c == 3 || o->mAction15c == 4)
    {
        if (((cSelf*)a1)->FUN_00c0f570() > 0)
        {
            void* e = ((cSelf*)a1)->FUN_00c0f8a0(((cSelf*)a1)->FUN_00c0f780());
            if (e != 0)
            {
                void* r = ((cVtVb8*)e)->vb8(TAG_SOCIAL_ANIM);
                if (r == 0)
                {
                    r = FUN_00d2ec30(e);
                    if (r == 0)
                        return 0.0f;
                    if (o->mAction15c != 4)
                        return 0.0f;
                }
                ((cSelf*)&a1->mpB4c->mStimuli)->FUN_00bc97f0(0, 0x8000, DAT_01473c70, r);
                return 1.0f;
            }
        }
    }
    return 0.0f;
}

// =================================================================================================
// @ 0x00d7e9d0
float FUN_00d7e9d0(cGameObj* a1, void* a2, void* a3, void* a4, cOutRec* a5, uint8_t* a6,
                   void* a7, cKeySrc* a8)
{
    cOwnerLink* link = &((cGameObjB*)((cSelf*)a1)->FUN_00c04590())->mOwnerLink;
    cGameObj* o = (cGameObj*)link->mpOwner;
    if (o != 0)
    {
        if (o->mpB4c->mKind == TAG_LIST_STATE)
        {
            if (a5 != 0)
                ((cSelf*)a5)->FUN_00d997e0();
            *a6 = 1;
            a5->mpCur = 0;
            return 1.0f;
        }
    }
    return 0.0f;
}

// =================================================================================================
// @ 0x00d7ea20
float FUN_00d7ea20(cGameObj* a1, void* a2, void* a3, void* a4, cOutRec* a5, uint8_t* a6,
                   void* a7, cKeySrc* a8)
{
    cGameObj* o = ((cSelf*)a1)->FUN_00c04590();

    if ((uint32_t)((o->mListEnd044 - o->mListBegin040) >> 2) > 1u)
    {
        if (((cSelf*)o)->FUN_00c6ac40())
        {
            if (a5 != 0)
                ((cSelf*)a5)->FUN_00d997e0();
            *a6 = 1;
            a5->mpCur = 0;
            return 1.0f;
        }
    }
    return 0.0f;
}

// =================================================================================================
// @ 0x00d7ea70
void FUN_00d7ea70(cGameObj* a1, void* a2, void* a3, void* a4, cOutRec* a5, uint8_t* a6,
                  void* a7, cKeySrc* a8)
{
    if (a1->mFlagB5e == 0 && a1->mFlag135 != 0)
        ((cSelf*)a1)->FUN_00c14750(0);

    cHolder* holder = a1->mpB54;
    if (holder != 0)
        holder->mSpeed = DAT_01485720;
}