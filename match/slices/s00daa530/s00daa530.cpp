// Slice s00daa530 -- SPGonzago behaviour-tree node callbacks acting on a
// cSPCreatureCitizen (0x00daa530 .. 0x00daafb0, 12 functions).
// Shared six/eight-argument node shape: (citizen, a, b, flags, behaviour_stimuli*,
// out[, extra, dt]); most return their result in st0.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <math.h>

#define PVN(n) virtual void pv##n();

struct Vec3 { float x, y, z; };

// ---- globals referenced by the originals ----------------------------------------------------
extern const float g_f13f0e84;    // 0x013f0e84   400.0f
extern const float g_f147c218;    // 0x0147c218   FLT_MAX
extern const float g_f13f9428;    // 0x013f9428   animation length scale
extern const unsigned int DAT_015d1164;  // 0x015d1164

// ---- behaviour stimulus record --------------------------------------------------------------
struct behavior_stimuli {
    int32_t  mStimulusID;        // +0x00
    void*    mTarget;            // +0x04
    void*    mValue;             // +0x08
    float    mF0c;               // +0x0c
    float    mF10;               // +0x10
    float    mF14;               // +0x14
    uint32_t mF18;               // +0x18
    void*    mF1c;               // +0x1c
    uint32_t mF20;               // +0x20

    void GetAny();               // 0x00d997e0 (thiscall)
};

// ---- wrapper for the dword cells of a compiled animation record -----------------------------
union AV { float f; uint32_t u; void* p; };

struct AnimPlayRes {
    char pad000[8];
    AV   mF08;                   // +0x08
    AV   mF0c;                   // +0x0c
    AV   mF10;                   // +0x10
    AV   mF14;                   // +0x14
    AV   mF18;                   // +0x18
};

// ---- stimuli manager embedded in the behaviour tree -----------------------------------------
// The block itself is 0x1c0 bytes of state operated on by the three methods below.
struct StimuliMgr {
    char  mPad[0x1c0];                                                 // +0x00

    AnimPlayRes* Play(uint32_t lo, uint32_t hi);                       // 0x00bc96a0
    void  ClearAll(uint32_t lo, uint32_t hi);                          // 0x00bc98f0
    void  PlayWith(uint32_t lo, uint32_t hi, float v, void* t);        // 0x00bc97f0
};

struct StimOwner { int32_t mId; };   // stimuli owner block at btree+0x1d0

struct cBehaviorTreeData {
    char        pad004[8];
    StimuliMgr  mStimuli;                        // +0x08
    char        pad010[0x1c8 - 0x10];
    uint32_t    mFlags1c8;                       // +0x1c8
    uint32_t    mFlags1cc;                       // +0x1cc   (0x80000 tested)
    StimOwner   mOwner1d0;                       // +0x1d0
    char        pad1d4[0x1d8 - 0x1d4];
    uint32_t    mKey1d8;                         // +0x1d8
    char        pad1dc[0x5fc - 0x1dc];
    uint32_t    mFlags5fc;                       // +0x5fc   (0x800000 tested)

    void* FirstPending();                        // 0x00bca2c0
    void  PopFront();                            // 0x00bcaf40
};

// ---- polymorphic view of the interaction sub-object (creature+0x58) -------------------------
struct Sub58 {
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6)
    virtual char    s1c();                       // +0x1c
    virtual void*   s20();                       // +0x20
    PVN(9)
    virtual void*   s28();                       // +0x28
};

// ---- polymorphic view of the spatial sub-object (creature+0xc0) -----------------------------
struct PosObj {
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9) PVN(10)
    virtual Vec3* v2c();                         // +0x2c
    PVN(12) PVN(13) PVN(14) PVN(15) PVN(16) PVN(17) PVN(18) PVN(19) PVN(20) PVN(21)
    virtual int32_t v58();                       // +0x58
    PVN(23) PVN(24) PVN(25) PVN(26) PVN(27) PVN(28)
    virtual float v74();                         // +0x74

    void* FUN_00c420d0();                        // 0x00c420d0 (non-virtual)
};

// ---- tribe ----------------------------------------------------------------------------------
struct Tribe {
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9) PVN(10)
    PVN(11) PVN(12) PVN(13) PVN(14) PVN(15) PVN(16) PVN(17) PVN(18) PVN(19) PVN(20)
    PVN(21) PVN(22) PVN(23)
    virtual float v60();                         // +0x60
    PVN(25) PVN(26) PVN(27) PVN(28) PVN(29) PVN(30) PVN(31) PVN(32) PVN(33) PVN(34)
    PVN(35)
    virtual void* v90();                         // +0x90
    char        pad004[0x120 - 0x04];
    PosObj      mObj120;                         // +0x120 (embedded)
    char        pad124[0x26c - 0x124];
    int32_t     mToolId26c;                      // +0x26c
};

// ---- creature -------------------------------------------------------------------------------
struct Creature {
    void**               mpVtbl;                 // +0x00
    char                 pad004[0x58 - 0x04];
    Sub58                mSub58;                 // +0x58
    char                 pad05c[0xc0 - 0x5c];
    PosObj               mC0;                    // +0xc0
    char                 padC4[0xb20 - 0xc4];
    int32_t              mIdB20;                 // +0xb20
    char                 padB24[0xb4c - 0xb24];
    cBehaviorTreeData*   mpB4C;                  // +0xb4c

    Tribe* GetTribe();                           // 0x00c22f50
    void   FUN_00c26450();                       // 0x00c26450
    int32_t FUN_00c12400(uint32_t id);           // 0x00c12400 AnimationFinished
    int32_t FUN_00c12190(uint32_t id, int32_t a, int32_t b);  // 0x00c12190 PlayAnimation
    int32_t FUN_00c22a70();                      // 0x00c22a70
    int32_t FUN_00c22dc0();                      // 0x00c22dc0
    char    FUN_00c0ba30();                      // 0x00c0ba30
    char    FUN_00c0b770();                      // 0x00c0b770
};

// ---- object returned by the tribe lookup (has a 0x34 sub-object) ----------------------------
struct Has5C {
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9) PVN(10)
    PVN(11) PVN(12) PVN(13) PVN(14) PVN(15) PVN(16) PVN(17) PVN(18) PVN(19) PVN(20)
    PVN(21) PVN(22)
    virtual void* v5c(uint32_t hash);            // +0x5c
};

struct Has34 {
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9) PVN(10)
    PVN(11) PVN(12)
    char  pad004[0x34 - 0x04];
    PosObj m34;                                  // +0x34
};

// ---- generic object with vtable slot 0xb8 ---------------------------------------------------
struct HasB8 {
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9) PVN(10)
    PVN(11) PVN(12) PVN(13) PVN(14) PVN(15) PVN(16) PVN(17) PVN(18) PVN(19) PVN(20)
    PVN(21) PVN(22) PVN(23) PVN(24) PVN(25) PVN(26) PVN(27) PVN(28) PVN(29) PVN(30)
    PVN(31) PVN(32) PVN(33) PVN(34) PVN(35) PVN(36) PVN(37) PVN(38) PVN(39) PVN(40)
    PVN(41) PVN(42) PVN(43) PVN(44) PVN(45)
    virtual Creature* v_b8(uint32_t hash);       // +0xb8
};

// ---- creature vtable view (own slot 0xb4) ---------------------------------------------------
struct CrtVt {
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9) PVN(10)
    PVN(11) PVN(12) PVN(13) PVN(14) PVN(15) PVN(16) PVN(17) PVN(18) PVN(19) PVN(20)
    PVN(21) PVN(22) PVN(23) PVN(24) PVN(25) PVN(26) PVN(27) PVN(28) PVN(29) PVN(30)
    PVN(31) PVN(32) PVN(33) PVN(34) PVN(35) PVN(36) PVN(37) PVN(38) PVN(39) PVN(40)
    PVN(41) PVN(42) PVN(43) PVN(44)
    virtual void* v45(uint32_t hash);            // +0xb4
};

// ---- object with vtable slot 0x1c and a data member at +0x70 --------------------------------
struct Obj70 {
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6)
    virtual int32_t o1c();                       // +0x1c
    PVN(8) PVN(9) PVN(10) PVN(11) PVN(12) PVN(13) PVN(14) PVN(15) PVN(16) PVN(17)
    PVN(18) PVN(19) PVN(20) PVN(21) PVN(22) PVN(23) PVN(24) PVN(25) PVN(26) PVN(27)
    char    pad004[0x70 - 0x04];
    int32_t m70;                                 // +0x70
};

// ---- object with vtable slot 0x2c(byte) / +0x34 sub-object (00daaec0) -----------------------
struct TgtE {
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9) PVN(10)
    virtual char  e2c();                         // +0x2c
    PVN(12)
    char    pad004[0x34 - 0x04];
    PosObj m34;                                  // +0x34

    char FUN_00c38990(int32_t a);                // 0x00c38990
};

// ---- resource object (00daa9b0) -------------------------------------------------------------
struct ObjC {
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7)
    virtual void* v20();                         // +0x20

    char FUN_00c0c0e0();                         // 0x00c0c0e0
};

struct ResObj {
    PVN(0) PVN(1)
    virtual void* v08();                         // +0x08
    virtual void* v0c();                         // +0x0c
    PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9) PVN(10) PVN(11) PVN(12) PVN(13)
    PVN(14) PVN(15) PVN(16) PVN(17) PVN(18) PVN(19) PVN(20) PVN(21) PVN(22) PVN(23)
    virtual void v60();                          // +0x60
    virtual void v64();                          // +0x64
};

// ---- selector node (00daad10) ---------------------------------------------------------------
struct SelObj0 {
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9) PVN(10)
    virtual Vec3* v2c();                         // +0x2c
    PVN(12) PVN(13) PVN(14) PVN(15) PVN(16) PVN(17) PVN(18) PVN(19) PVN(20) PVN(21)
    PVN(22) PVN(23) PVN(24) PVN(25) PVN(26) PVN(27) PVN(28) PVN(29) PVN(30) PVN(31)
    PVN(32) PVN(33) PVN(34) PVN(35) PVN(36) PVN(37) PVN(38) PVN(39) PVN(40) PVN(41)
    PVN(42) PVN(43) PVN(44) PVN(45) PVN(46)
    virtual void mbc();                          // +0xbc
    virtual void mc0();                          // +0xc0
};

struct SelObj {
    char    pad000[0x1c];
    void**  mpBegin;                             // +0x1c
    void**  mpEnd;                               // +0x20
    char    pad024[0x18c - 0x24];
    void*   mpBest;                              // +0x18c
    char    pad190[0x194 - 0x190];
    float   mX;                                  // +0x194
    float   mY;                                  // +0x198
    float   mZ;                                  // +0x19c
};

// ---- node state records ---------------------------------------------------------------------
#pragma pack(push, 1)
struct PState { char pad00[0x2d]; uint32_t m2d; };              // 00daa530 arg8

struct StateAC {
    Obj70*   mpObj;          // +0x00
    int32_t  mPad04;         // +0x04
    uint8_t  mFlag08;        // +0x08
    char     mPad09[0x10 - 0x09];
    long long mVal10;        // +0x10  (used as two int32 halves)
};

struct StateF0 { int32_t m00; float m04; uint8_t mFlag08; };     // 00daadf0
struct StateEC { TgtE*   pObj; float mRadius2; };                // 00daaec0
struct State60 { int32_t m00; float m04; float m08; };           // 00daaf60
struct StateB0 { int32_t m00; float m04; float m08; };           // 00daafb0
#pragma pack(pop)

// ---- order record (00daab90) -----------------------------------------------------------------
#pragma pack(push, 1)
struct OrderSub {                       // lives at record+0x39
    uint32_t* mObj;         // +0x00
    char      pad004[0x0c];
    uint8_t   mFlag;        // +0x10
    char      pad011[1];
    int16_t   mShort;       // +0x12
};

struct OrderRec {
    int32_t  mType;          // +0x00
    char     pad004[0x35];
    OrderSub mSub;           // +0x39
};
#pragma pack(pop)

// ---- engine helpers --------------------------------------------------------------------------
struct SimB {
    int32_t  FUN_00bc3db0(uint32_t id);                 // 0x00bc3db0
    int32_t* FUN_00bc7610(uint32_t a, uint32_t b);      // 0x00bc7610
};

struct RandomLCG {
    double RandomDoubleUniform();                       // 0x009360d0
};

struct CommCtx {
    float   FUN_00ce6900();                             // 0x00ce6900
    int32_t FUN_00ce6950();                             // 0x00ce6950
    int32_t FUN_005f33f0(float v);                      // 0x005f33f0
};

#define COMMCTX ((CommCtx*)0x1581208)

extern void*  __cdecl FUN_00d99420(void* owner, uint32_t v);   // 0x00d99420
extern void*  __cdecl FUN_00d996e0(void* a, void* b);          // 0x00d996e0
extern void*  __cdecl FUN_00d99500(void* a);                   // 0x00d99500
extern void*  __cdecl FUN_00d994c0(void* a);                   // 0x00d994c0
extern void*  __cdecl FUN_00d999d0(void* a);                   // 0x00d999d0 WatchMemoryBlock
extern void*  __cdecl FUN_00d99a10(void* a);                   // 0x00d99a10
extern void*  __cdecl FUN_00b3d4d0(void);                      // 0x00b3d4d0 GetTriggerMgr
extern SimB*  __cdecl FUN_00b3d4e0(void);                      // 0x00b3d4e0
extern long long __cdecl FUN_00da6090(uint32_t v);             // 0x00da6090
extern int32_t __cdecl FUN_00c9cec0(uint32_t v);               // 0x00c9cec0
extern "C" int32_t __fastcall FUN_00cee330(void* self);        // 0x00cee330 (this in ecx)
extern float  __cdecl FUN_00572a10(float lo, float hi);        // 0x00572a10 RandomFloatRange

// =============================================================================================

// @ 0x00daa530
float __cdecl FUN_00daa530(Creature* c, uint32_t, uint32_t, uint32_t,
                           behavior_stimuli* stim, uint8_t* out, uint32_t, PState* in20)
{
    if (stim != 0) stim->GetAny();
    *out = 1;
    void* uVar6 = FUN_00d99420(&c->mpB4C->mOwner1d0, in20->m2d);
    FUN_00d996e0(uVar6, stim);
    float fVar5 = (float)stim->mF18;

    Has34* pObj;
    Has5C* piVar4 = (Has5C*)stim->mTarget;
    if (piVar4 == 0) {
        pObj = 0;
    } else {
        pObj = (Has34*)piVar4->v5c(0xb033b403);
    }

    Vec3* pt = pObj->m34.v2c();
    float tx = pt->x;
    float ty = pt->y;
    float tz = pt->z;

    Vec3* pm = c->mC0.v2c();
    float dx = pm->x - tx;
    float dy = pm->y - ty;
    float dz = pm->z - tz;

    if (dz * dz + dy * dy + dx * dx < fVar5 * fVar5) return 1.0f;
    return 0.0f;
}

// @ 0x00daa640
float __cdecl FUN_00daa640(Creature* c, uint32_t, uint32_t, uint32_t,
                           behavior_stimuli* stim, uint8_t* out)
{
    void* puVar2 = c->mC0.FUN_00c420d0();
    HasB8** piVar5 = (HasB8**)(*(void**)puVar2);
    HasB8** piVar1 = (HasB8**)(*((void**)puVar2 + 1));
    for (;;) {
        if (piVar5 == piVar1) return 0.0f;
        if (*piVar5 != 0) {
            Creature* iVar3 = (*piVar5)->v_b8(0xce9f6639);
            if (iVar3 != 0) {
                Creature* iVar4 = (Creature*)FUN_00d99500(iVar3);
                if (iVar4 == 0) {
                    iVar3 = (Creature*)FUN_00d994c0(iVar3);
                    if (iVar3 != 0 && c->mIdB20 != iVar3->mIdB20 &&
                        iVar3->mpB4C->mStimuli.Play(0x1000, 0) != 0) {
                        if (stim != 0) stim->GetAny();
                        stim->mTarget = (char*)iVar3 + 0x5a8;
                        *out = 1;
                        return 1.0f;
                    }
                } else if ((iVar4->mpB4C->mFlags5fc & 0x800000) != 0) {
                    if (stim != 0) stim->GetAny();
                    stim->mTarget = (char*)iVar4 + 0x5a8;
                    *out = 1;
                    return 1.0f;
                }
            }
        }
        piVar5++;
    }
}

// @ 0x00daa740
float __cdecl FUN_00daa740(Creature* c)
{
    AnimPlayRes* iVar4 = c->mpB4C->mStimuli.Play(0x2000000, 0);
    void* uVar5 = FUN_00d999d0(iVar4);
    Creature* iVar6 = (Creature*)FUN_00d994c0(uVar5);
    if (iVar6 != 0 && iVar6 != c) {
        int32_t iVar2 = (int32_t)c->mpB4C->mKey1d8;
        int32_t iVar3 = (int32_t)iVar6->mpB4C->mKey1d8;
        if (((iVar2 != 0x461300f && iVar2 != 0x4623e0c) ||
             (iVar3 != 0x461300f && iVar3 != 0x4623e0c)) &&
            (iVar2 != 0x4611758 || iVar3 != 0x4611758)) {
            float fVar9  = iVar4->mF0c.f;
            float fVar1  = iVar4->mF18.f;
            float fVar10 = iVar4->mF10.f;
            float fVar11 = iVar4->mF14.f;
            Vec3* pfVar7 = c->mC0.v2c();
            fVar9  -= pfVar7->x;
            fVar10 -= pfVar7->y;
            fVar11 -= pfVar7->z;
            fVar1 = c->mC0.v74() + fVar1;
            if ((fVar11 * fVar11 + fVar10 * fVar10) + fVar9 * fVar9 < fVar1 * fVar1)
                return 1.0f;
        }
    }
    c->mpB4C->mStimuli.ClearAll(0x2000000, 0);
    return 0.0f;
}

// @ 0x00daa8c0
float __cdecl FUN_00daa8c0(Creature* c, uint32_t, uint32_t, uint32_t,
                           behavior_stimuli* stim, uint8_t* out)
{
    Tribe* psiVar4 = c->GetTribe();
    int32_t* piVar5 = (int32_t*)FUN_00b3d4d0();
    if (piVar5[0x2c / 4] == 1) return 0.0f;

    AnimPlayRes* piVar8 = c->mpB4C->mStimuli.Play(0, 0x40);
    void* pvVar1 = piVar8->mF14.p;
    uint32_t uVar2 = piVar8->mF0c.u;
    uint32_t uVar5 = piVar8->mF10.u;

    if (pvVar1 == (void*)0x7dcc4e7e) {
        char cVar3 = c->FUN_00c0b770();
        if (cVar3 != 0 && psiVar4->mToolId26c == -1) return 0.0f;
    }
    c->mpB4C->mStimuli.ClearAll(0, 0x40);

    int32_t iVar4 = psiVar4->mToolId26c;
    if (iVar4 != -1) {
        iVar4 = FUN_00b3d4e0()->FUN_00bc3db0(iVar4);
        if (iVar4 == 0) return 0.0f;
    }
    int32_t* piVar6 = FUN_00b3d4e0()->FUN_00bc7610((uint32_t)pvVar1, 0);
    if (uVar2 <= (uint32_t)((piVar6[1] - piVar6[0]) / 0x7b4)) {
        if (stim != 0) stim->GetAny();
        stim->mF1c = pvVar1;
        stim->mF18 = (uVar5 << 0x10) | (uVar2 & 0xffff);
        *out = 1;
        return 1.0f;
    }
    return 0.0f;
}

// @ 0x00daa9b0
float __cdecl FUN_00daa9b0(Creature* c, uint32_t, uint32_t, uint32_t,
                           behavior_stimuli* stim, uint8_t* out)
{
    AnimPlayRes* iVar4 = c->mpB4C->mStimuli.Play(0, 0x80000);
    float uVar1 = iVar4->mF08.f;
    ResObj* piVar5 = (ResObj*)FUN_00d99a10(iVar4);
    if (piVar5 != 0) piVar5->v60();
    c->mpB4C->mStimuli.ClearAll(0, 0x80000);
    if (piVar5 == 0) return 0.0f;

    if (stim != 0) stim->GetAny();
    *out = 1;
    stim->mF18 = 0x2cc62c6;

    ObjC* piVar6 = (ObjC*)piVar5->v0c();
    if (piVar6 != 0) {
        if (piVar6->v20() == (void*)0x18eb45e && piVar6->FUN_00c0c0e0() != 0)
            stim->mF18 = 0x65e6623;
    }
    stim->mF1c = (void*)3;
    stim->mF20 = 0x33;

    PosObj* piVar7 = (PosObj*)piVar5->v08();
    Vec3* puVar8 = piVar7->v2c();
    stim->mF0c = puVar8->x;
    stim->mF10 = puVar8->y;
    stim->mF14 = puVar8->z;

    void* piVar9 = c->GetTribe()->v90();
    Creature** ppc = (Creature**)(*(void**)piVar9);
    Creature** ppEnd = (Creature**)(*((void**)piVar9 + 1));
    for (; ppc != ppEnd; ppc++) {
        Creature* pcVar2 = *ppc;
        if (pcVar2 != c) {
            Vec3* pfVar10 = pcVar2->mC0.v2c();
            float fVar12 = pfVar10->x - stim->mF0c;
            float fVar13 = pfVar10->y - stim->mF10;
            float fVar14 = pfVar10->z - stim->mF14;
            if ((fVar12 * fVar12 + fVar13 * fVar13) + fVar14 * fVar14 < 400.0f &&
                (pcVar2->mpB4C->mFlags1cc & 0x80000) == 0) {
                void* uVar11 = piVar5->v0c();
                c->mpB4C->mStimuli.PlayWith(0, 0x80000, uVar1, uVar11);
            }
        }
    }
    piVar5->v64();
    return 1.0f;
}

// @ 0x00daab90
float __cdecl FUN_00daab90(Creature* c)
{
    OrderRec* piVar2 = (OrderRec*)c->mpB4C->FirstPending();
    if (piVar2 != 0 && piVar2->mType == 0x16) {
        OrderSub* pSub = &piVar2->mSub;
        int16_t sVar1 = pSub->mShort;
        uint32_t* puVar3;
        if (sVar1 == 10 || sVar1 == 0x10) {
            if ((pSub->mFlag & 0x30) == 0)
                puVar3 = (uint32_t*)(-(int32_t)(sVar1 != 0) & (int32_t)(intptr_t)pSub);
            else
                puVar3 = pSub->mObj;
        } else {
            puVar3 = (uint32_t*)&DAT_015d1164;
        }
        int32_t iVar4 = (int32_t)((CrtVt*)c)->v45(*puVar3);
        if (iVar4 != 0 && *(int32_t*)(iVar4 + 8) == 0x37) return 1.0f;
    }
    return 0.0f;
}

// @ 0x00daac00
uint8_t __cdecl FUN_00daac00(Creature* c, uint32_t, uint32_t, uint32_t, uint32_t, StateAC* out)
{
    if (out->mpObj != 0) {
        if (c->mSub58.s1c() != 0) {
            Obj70* pB = (Obj70*)c->mSub58.s28();
            Obj70* pS = (Obj70*)c->mSub58.s20();
            if (pB != 0) {
                if (pB->o1c() == out->mpObj->o1c() && pB->m70 != 0) return 1;
            }
            if (pS != 0) {
                if (pS->o1c() == out->mpObj->o1c() && pS->m70 != 0) return 1;
            }
        }
    }

    int32_t lVal10Lo = (int32_t)out->mVal10;
    int32_t lVal10Hi = (int32_t)(out->mVal10 >> 32);
    out->mFlag08 = 1;
    int32_t* puVar9 = (int32_t*)c->mpB4C->FirstPending();
    long long r = 0;
    if (puVar9 != 0) r = FUN_00da6090((uint32_t)*puVar9);
    if (puVar9 == 0 || r != out->mVal10) {
        c->mpB4C->mStimuli.ClearAll(lVal10Lo, lVal10Hi);
    } else {
        c->mpB4C->PopFront();
        c->mpB4C->mStimuli.ClearAll(0x1d3fbffa, 0x8124080);
    }
    c->FUN_00c26450();
    return 0;
}

// @ 0x00daad10
uint32_t __fastcall FUN_00daad10(SelObj* p)
{
    float local = g_f147c218;
    void** piVar1 = p->mpEnd;
    void** piVar5 = p->mpBegin;
    for (; piVar5 != piVar1; piVar5++) {
        SelObj0* piVar2 = (SelObj0*)*piVar5;
        Vec3* pfVar4 = piVar2->v2c();
        float dx = p->mX - pfVar4->x;
        float dy = p->mY - pfVar4->y;
        float dz = p->mZ - pfVar4->z;
        float d2 = (dz * dz + dy * dy) + dx * dx;
        if (d2 < local) {
            SelObj0* piVar3 = (SelObj0*)p->mpBest;
            local = d2;
            if (piVar2 != piVar3) {
                piVar2->mbc();
                p->mpBest = piVar2;
                if (piVar3 != 0) piVar3->mc0();
            }
        }
    }
    return (uint32_t)(uintptr_t)p->mpBest;
}

// @ 0x00daadf0
uint32_t __cdecl FUN_00daadf0(Creature* c, uint32_t, uint32_t, uint32_t, uint32_t, StateF0* out)
{
    out->m00 = 0;
    out->m04 = 0.0f;
    Tribe* piVar1 = c->GetTribe();
    float fVar4 = piVar1->v60();
    c->mpB4C->mStimuli.ClearAll(0x200000, 0);
    Vec3* pfVar2 = piVar1->mObj120.v2c();
    Vec3* pfVar3 = c->mC0.v2c();
    float dy = pfVar3->y - pfVar2->y;
    float dz = pfVar3->z - pfVar2->z;
    float dx = pfVar3->x - pfVar2->x;
    if ((dx * dx + dy * dy) + dz * dz < fVar4 * fVar4) {
        out->mFlag08 = 1;
        return 1;
    }
    out->mFlag08 = 0;
    return 1;
}

// @ 0x00daaec0
uint32_t __cdecl FUN_00daaec0(Creature* c, uint32_t, uint32_t, uint32_t, uint32_t, StateEC* out)
{
    if ((char)out->pObj->e2c() != 0) return 0;
    if ((char)out->pObj->FUN_00c38990(1) != 0) return 0;
    Vec3* pfVar2 = out->pObj->m34.v2c();
    Vec3* pfVar3 = c->mC0.v2c();
    float dy = pfVar3->y - pfVar2->y;
    float dz = pfVar3->z - pfVar2->z;
    float dx = pfVar3->x - pfVar2->x;
    if ((dx * dx + dy * dy) + dz * dz < out->mRadius2) return 1;
    return 0;
}

// @ 0x00daaf60
uint8_t __cdecl FUN_00daaf60(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, State60* out)
{
    out->m04 = 0.0f;
    double fVar1 = ((RandomLCG*)0x1601760)->RandomDoubleUniform();
    double fVar2 = 1.0;
    if (fVar1 < 1.0 && (fVar2 = fVar1, fVar1 < 0.0)) {
        out->m00 = 0;
        out->m08 = 0.0;
        return 1;
    }
    out->m00 = 0;
    out->m08 = (float)fVar2;
    return 1;
}

// @ 0x00daafb0
uint8_t __cdecl FUN_00daafb0(Creature* c, uint32_t, uint32_t, uint32_t, uint32_t,
                             StateB0* out, uint32_t, float dt)
{
    c->mpB4C->mStimuli.Play(0, 0x20);
    out->m04 += dt;

    Tribe* piVar13 = c->GetTribe();
    Vec3* pfVar11 = piVar13->mObj120.v2c();
    Vec3* pfVar12 = c->mC0.v2c();
    Vec3 dv;
    dv.x = pfVar12->x - pfVar11->x;
    dv.y = pfVar12->y - pfVar11->y;
    dv.z = pfVar12->z - pfVar11->z;
    float fVar16 = c->GetTribe()->v60();
    float dist2 = (dv.z * dv.z + dv.x * dv.x) + dv.y * dv.y;

    uint8_t bVar8;
    char cVar9;
    if (dist2 >= fVar16 * fVar16) {
        bVar8 = 0;
        cVar9 = c->FUN_00c0ba30();
        if (cVar9 != 0) goto LAB_00dab0af;
        cVar9 = (char)c->mC0.v58();
        if (cVar9 != 0) goto LAB_00dab0dd;
    } else {
        bVar8 = 1;
    }
LAB_00dab0af:
    if (out->m04 > COMMCTX->FUN_00ce6900()) return 0;
    if (bVar8 != 0 && (char)FUN_00cee330((char*)c + 0x34) != 0) return 0;
LAB_00dab0dd:
    if (out->m00 != 0 && c->FUN_00c12400((uint32_t)out->m00) == 0) {
    } else {
        out->m08 -= dt;
    }
LAB_00dab0ff:
    if (out->m08 >= 0.0f) return 1;
    {
        int32_t iVar10 = COMMCTX->FUN_00ce6950();
        float f1 = (float)iVar10 * g_f13f9428;
        int32_t iVar12 = COMMCTX->FUN_005f33f0(f1);
        out->m08 = FUN_00572a10((float)iVar12 * g_f13f9428, f1);
    }
    {
        int32_t iVar10 = 0x27844ad;
        if (c->FUN_00c22a70() == 0) {
            if ((char)FUN_00cee330((char*)c + 0x34) != 0) iVar10 = 0x5f0f5c8;
        } else {
            int32_t iVar14 = c->FUN_00c22dc0();
            if (iVar14 != 0) {
                iVar14 = FUN_00c9cec0((uint32_t)iVar14);
                iVar10 = *(int32_t*)(iVar14 + 0x28);
                if (iVar10 != 0) {
                    if (*(int32_t*)(iVar14 + 0x2c) != 0) {
                        double dd = ((RandomLCG*)0x1601760)->RandomDoubleUniform();
                        if (dd <= 0.5) iVar10 = *(int32_t*)(iVar14 + 0x2c);
                        else iVar10 = *(int32_t*)(iVar14 + 0x28);
                        goto LAB_00dab1c8;
                    }
                    goto LAB_00dab1c8;
                }
                iVar10 = 0x27844ad;
                if (*(int32_t*)(iVar14 + 0x2c) != 0) iVar10 = *(int32_t*)(iVar14 + 0x2c);
            }
        }
LAB_00dab1c8:
        iVar10 = c->FUN_00c12190((uint32_t)iVar10, 1, 0xffffffff);
        out->m00 = iVar10;
        return 1;
    }
}