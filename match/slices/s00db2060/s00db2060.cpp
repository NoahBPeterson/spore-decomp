// Slice s00db2060 -- cSPCreatureBase "tribe repair" task cluster.
//
// The task context object (called `ctx` below) is a shared 0x28-byte record used by
// 00db21b0, 00db2410, 00db24c0, 00db2f10 and 00db2fa0:
//   +0x00 int   mState
//   +0x04 Ref   mTaskRefA     (engine ::Play()-derived handle)
//   +0x08 Ref   mTaskRefB
//   +0x0c Ref   mTaskRefC
//   +0x10 float mPosX / mPosY / mPosZ
//   +0x1c bool  mFlag1c       (task variant selector: A or B)
//   +0x1d bool  mFlag1d       (previous near-goal flag)
//   +0x20 int   mSpotIndex
//   +0x24 float mTimer
//
// Retail member offsets are read from the disassembly; the dev PDB layout differs,
// so objects are modelled locally with role-named members at retail offsets.

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned __int64 u64;

// ---------------------------------------------------------- indirect this-call
typedef void  (__thiscall *F0v)(void *);
typedef void  (__thiscall *F0v)(void *);
typedef void *(__thiscall *F0p)(void *);
typedef void  (__thiscall *F1i)(void *, int);
typedef void  (__thiscall *F1p)(void *, void *);
typedef void  (__thiscall *F1u)(void *, u32);
typedef void  (__thiscall *F3p)(void *, void *, void *, int);
typedef int   (__thiscall *F1i_r)(void *, u32);
typedef void *(__thiscall *F1u_p)(void *, u32);
typedef char  (__thiscall *F0c)(void *);
typedef float (__thiscall *F0f)(void *);

static inline void *VS(void *o, int off) { return *(void **)((char *)(*(void **)o) + off); }
static inline void *vc_p(void *o, int off) { return ((F0p)VS(o, off))(o); }
static inline void  vc_v(void *o, int off) { ((F0v)VS(o, off))(o); }
static inline void  vc_vu(void *o, int off, u32 a) { ((F1u)VS(o, off))(o, a); }

// --------------------------------------------------------------------- Ref
// The engine's intrusive ref-counted handle.  Copying an AutoRefCount calls AddRef
// (vtable slot 0); releasing calls Release (vtable slot 1, i.e. +4).

struct RefObj {
    void **mpVtbl; // +0x00
    void *AddRef();                 // slot 0
    void Release();                 // slot 1 (vtable +4)
};

static inline void RefStore(void **ppDst, void *pNew)
{
    void *pOld = *ppDst;
    if (pNew == pOld)
        return;
    if (pNew != 0)
        vc_v(pNew, 0);
    *ppDst = pNew;
    if (pOld != 0)
        vc_v(pOld, 4);
}

// ------------------------------------------------------------------- context

struct TaskCtx {
    int   mState;    // +0x00
    void *mpRefA;    // +0x04
    void *mpRefB;    // +0x08
    void *mpRefC;    // +0x0c
    float mPosX;     // +0x10
    float mPosY;     // +0x14
    float mPosZ;     // +0x18
    char  mFlag1c;   // +0x1c
    char  mFlag1d;   // +0x1d
    int   mSpotIndex;// +0x20
    float mTimer;    // +0x24
};

// --------------------------------------------------------------- extern decls

// ---- generic engine / manager entry points ---------------------------------
extern "C" void *SP__App();
extern "C" void *EA__Audio__GetSystemAT();
extern "C" void *FUN_00d998d0(void *pOwner, u32 key);
extern "C" void *SP__EffectsManager();
extern "C" void *FUN_00da6270(void *pTask, int code);
extern "C" void *FUN_00b3d440();
extern "C" void *FUN_00b3d350(void *pOut, const void *pIn);
extern "C" void *FUN_00d9b000();

extern "C" void  operator_delete_array(void *p);
extern "C" double fabs(double);
extern "C" float  sqrtf(float);
extern "C" void   memcpy_s(void *d, u32 dn, const void *s, u32 n);

// ---- thiscall entry points emulated with __fastcall.
// MSVC 2008 rejects `__thiscall` on free functions, so each callee takes a dummy
// register argument (edx) and its real `this` first: `f(this, dummy, args...)`
// lowers to `mov ecx,this; mov edx,dummy; call`, matching the original.
#define TCAL __fastcall

extern "C" void *TCAL SP__PlayIdleAnimation(void *pThis, int d, u32 a, u32 b);
extern "C" void  TCAL SP__InterruptAnimation(void *pThis, int d, u32 a, u32 b, u32 c);
extern "C" void  TCAL SP__PlayAnimation(void *pThis, int d, u32 a, u32 b, u32 c);
extern "C" void  TCAL SP__MoveToPointAtSpeed(void *pThis, int d, int a, void *pPos, float f1, float f2);
extern "C" void  TCAL SP__MoveToPointAndFacing(void *pThis, int d, int a, void *pPos,
                                               const void *pDir, float f1, float f2);
extern "C" char  TCAL SP__AnimationFinished(void *pThis, int d, int a);
extern "C" char  TCAL SP__IsNearGoal(void *pThis, int d);
extern "C" void *TCAL SP__CCM_e0c0(void *pThis, int d, int a);
extern "C" void  TCAL SP__CCB_cff0(void *pThis, int d, int a);
extern "C" void  TCAL SP__FUN_00c14750(void *pThis, int d, int a);
extern "C" char  TCAL SP__FUN_00c25480(void *pThis, int d, int a, int b);
extern "C" void *TCAL SP__FUN_00c41ec0(void *pThis, int d);
extern "C" void *TCAL SP__FUN_00c423c0(void *pThis, int d);
extern "C" float TCAL SP__FUN_00bfc490(void *pThis, int d);
extern "C" void  TCAL SP__FUN_00c9cf90(void *pThis, int d, int a);
extern "C" void  TCAL SP__FUN_00c9bef0(void *pThis, int d, int a);
extern "C" void *TCAL SP__FUN_00c986d0(void *pThis, int d, void *pOut, void *pB);
extern "C" void  TCAL SP__FindSpot(void *pThis, int d, int a, int b);
extern "C" void  TCAL SP__FUN_00f924e0(void *pThis, int d, float f);
extern "C" void *TCAL SP__FUN_00bca2c0(void *pThis, int d);
extern "C" void *TCAL SP__FUN_00b02b90(void *pThis, int d, int a);

static inline void *PlayIdleAnimation(void *p, u32 a, u32 b) { return SP__PlayIdleAnimation(p, 0, a, b); }
static inline void  InterruptAnimation(void *p, u32 a, u32 b, u32 c) { SP__InterruptAnimation(p, 0, a, b, c); }
static inline void  PlayAnimation(void *p, u32 a, u32 b, u32 c) { SP__PlayAnimation(p, 0, a, b, c); }
static inline void  MoveToPointAtSpeed(void *p, int a, void *q, float f1, float f2) { SP__MoveToPointAtSpeed(p, 0, a, q, f1, f2); }
static inline void  MoveToPointAndFacing(void *p, int a, void *q, const void *r, float f1, float f2) { SP__MoveToPointAndFacing(p, 0, a, q, r, f1, f2); }
static inline char  AnimationFinished(void *p, int a) { return SP__AnimationFinished(p, 0, a); }
static inline char  IsNearGoal(void *p) { return SP__IsNearGoal(p, 0); }
static inline void *CCM_e0c0(void *p, int a) { return SP__CCM_e0c0(p, 0, a); }
static inline void  CCB_cff0(void *p, int a) { SP__CCB_cff0(p, 0, a); }
static inline void  FUN_00c14750(void *p, int a) { SP__FUN_00c14750(p, 0, a); }
static inline char  FUN_00c25480(void *p, int a, int b) { return SP__FUN_00c25480(p, 0, a, b); }
static inline void *FUN_00c41ec0(void *p) { return SP__FUN_00c41ec0(p, 0); }
static inline void *FUN_00c423c0(void *p) { return SP__FUN_00c423c0(p, 0); }
static inline float FUN_00bfc490(void *p) { return SP__FUN_00bfc490(p, 0); }
static inline void  FUN_00c9cf90(void *p, int a) { SP__FUN_00c9cf90(p, 0, a); }
static inline void  FUN_00c9bef0(void *p, int a) { SP__FUN_00c9bef0(p, 0, a); }
static inline void *FUN_00c986d0(void *p, void *q, void *r) { return SP__FUN_00c986d0(p, 0, q, r); }
static inline void  FindSpot(void *p, int a, int b) { SP__FindSpot(p, 0, a, b); }
static inline void  FUN_00f924e0(void *p, float f) { SP__FUN_00f924e0(p, 0, f); }
static inline void *FUN_00bca2c0(void *p) { return SP__FUN_00bca2c0(p, 0); }
static inline void *FUN_00b02b90(void *p, int a) { return SP__FUN_00b02b90(p, 0, a); }

extern "C" float FUN_0104bdb0(void);
extern "C" void *FUN_00c9d9e0();

// ---- serialize / planet helpers --------------------------------------------
extern "C" void *SP__PlanetModel(void *pOut, const void *pIn);
extern "C" void *SP__cPlanetModel__MakeRandomWorldPosition(void *pThis, void *a, void *b, float f1, float f2);
extern "C" void  cNavigationGoal__InitAt(void *pThis, void *pSrc);
extern "C" void  FUN_007a41a0(void *pThis);
extern "C" void *normalized_safe(void *pOut, const void *pIn);
extern "C" void  FUN_00ad29d0(void *pThis, void *pSrc);

// ------------------------------------------------------------------ functions

// @ 0x00db2060
char FUN_00db2060(void *pCreature, TaskCtx *pCtx)
{
    void *pAnimMgr = (char *)*(void **)((char *)pCreature + 0xb4c) + 8;
    void *pPlay = PlayIdleAnimation(pAnimMgr, 0x10000, 0);
    if (pPlay == 0)
        return 0;

    char isVariantA = (*(int *)((char *)pPlay + 0xc) == 1);
    pCtx->mFlag1c = isVariantA;
    u32 animA = *(u32 *)((char *)pPlay + 0x14);
    pCtx->mState = animA;
    pCtx->mState = *(int *)((char *)pPlay + 0x18);

    u32 chosen;
    if (isVariantA != 0) {
        InterruptAnimation(pCreature, animA, 0xffffffff, 0);
        chosen = *(u32 *)((char *)pPlay + 0x18);
    } else {
        chosen = 0x2481e14;
    }
    PlayAnimation(pCreature, chosen, 1, 0xffffffff);

    char buf[0x74];
    *(float *)(buf + 0x54) = *(float *)0x0169f3b8;
    *(float *)(buf + 0x58) = *(float *)0x0169f3bc;
    *(float *)(buf + 0x5c) = *(float *)0x0169f3c0;
    *(float *)(buf + 0x60) = 1.0f;
    *(float *)(buf + 0x24) = *(float *)0x0169f414;
    *(float *)(buf + 0x28) = *(float *)0x0169f418;
    *(float *)(buf + 0x2c) = *(float *)0x0169f41c;
    *(float *)(buf + 0x30) = *(float *)0x0169f420;
    *(float *)(buf + 0x34) = *(float *)0x0169f424;
    *(float *)(buf + 0x38) = *(float *)0x0169f428;
    *(float *)(buf + 0x10) = *(float *)0x1470f1c;
    *(float *)(buf + 0x6c) = *(float *)0x13ec4b4;
    *(float *)(buf + 0x40) = *(float *)0x0169f42c;
    *(float *)(buf + 0x44) = *(float *)0x0169f430;
    *(float *)(buf + 0x48) = *(float *)0x0169f434;
    *(u32 *)(buf + 0x0c) = 0;
    *(u32 *)(buf + 0x14) = 0;
    *(u32 *)(buf + 0x18) = 0;
    *(u32 *)(buf + 0x34) = 0;
    buf[0x5c] = 0;
    *(float *)(buf + 0x60) = 0.0f;
    *(float *)(buf + 0x64) = 0.0f;
    *(float *)(buf + 0x68) = 0.0f;
    *(u32 *)(buf + 0x6c) = 0;
    *(float *)(buf + 0x78) = *(float *)0x147c218;
    *(float *)(buf + 0x7c) = 0.0f;
    *(u32 *)(buf + 0x80) = 0;

    void *pSys = VS((char *)pCreature + 0xc0, 0xdc);
    ((F1p)pSys)((char *)pCreature + 0xc0, buf);

    void *pArr = *(void **)(buf + 0x0c);
    if (pArr != 0 && *(int *)((char *)pArr - 4) != 0)
        operator_delete_array(pArr);
    return 1;
}

// @ 0x00db21b0
char FUN_00db21b0(void *pCreature, u32 a2, u32 a3, u32 a4, u32 a5, TaskCtx *pCtx,
                  void *pTask, u32 a8, u32 a9)
{
    (void)a2; (void)a3; (void)a4; (void)a5; (void)a8; (void)a9;
    if (pCtx != 0) {
        pCtx->mpRefA = 0;
        pCtx->mpRefB = 0;
        pCtx->mpRefC = 0;
    }

    void *pAnimMgr = (char *)*(void **)((char *)pCreature + 0xb4c) + 8;
    void *pPlay = PlayIdleAnimation(pAnimMgr, 0x1000000, 0);
    void *pRef1 = pPlay;
    pCtx->mState = 1;

    RefStore(&pCtx->mpRefB, FUN_00d998d0(pPlay, 0x116d858));
    RefStore(&pCtx->mpRefA, FUN_00d998d0(pPlay, 0xee02c7));
    void *pRef3 = FUN_00d998d0(pPlay, 0x4f396a66);

    if (pTask != 0) {
        void *pOwner = *(void **)((char *)pTask + 8);
        if (pOwner == 0)
            RefStore(&pCtx->mpRefB, 0);
        else
            RefStore(&pCtx->mpRefB, ((F1u_p)VS(pOwner, 0xc))(pOwner, 0x116d858));

        pOwner = *(void **)((char *)pTask + 8);
        if (pOwner == 0)
            RefStore(&pCtx->mpRefA, 0);
        else
            RefStore(&pCtx->mpRefA, ((F1u_p)VS(pOwner, 0xc))(pOwner, 0xee02c7));
    }

    if (pCtx->mpRefB == 0 && pCtx->mpRefA == 0 && pRef3 != 0) {
        void *pWin = vc_p(pRef3, 0xac);
        RefStore(&pCtx->mpRefA, pWin);
    }

    void *pUse;
    if (pCtx->mpRefB != 0) {
        RefStore(&pCtx->mpRefC, FUN_00c9d9e0());
        pCtx->mFlag1c = 1;
        pUse = (pCtx->mpRefB != 0) ? (char *)pCtx->mpRefB + 0x120 : 0;
    } else {
        pCtx->mFlag1c = 0;
        if (pCtx->mpRefA == 0)
            return 0;
        void *pOuter = ((F0p)VS(pCtx->mpRefA, 0x58))(pCtx->mpRefA);
        RefStore(&pCtx->mpRefC, pOuter);
        pUse = (pCtx->mpRefA != 0) ? (char *)pCtx->mpRefA + 0x120 : 0;
    }

    ((F3p)VS(pCreature, 0x84))(pCreature, pUse, (void *)1, (int)3);

    void *pPos = ((F0p)VS((char *)pUse + 0x34, 0x2c))((char *)pUse + 0x34);
    pCtx->mPosX = *(float *)pPos;
    pCtx->mPosY = *(float *)((char *)pPos + 4);
    pCtx->mPosZ = *(float *)((char *)pPos + 8);
    pCtx->mSpotIndex = -1;
    pCtx->mTimer = 0.0f;
    pCtx->mFlag1d = 0;
    return 1;
}

// @ 0x00db2410
void FUN_00db2410(void *pCreature, u32 a2, u32 a3, u32 a4, u32 a5, TaskCtx *pCtx)
{
    (void)a2; (void)a3; (void)a4; (void)a5;
    FUN_00c14750(pCreature, 0);
    ((F3p)VS(pCreature, 0x84))(pCreature, 0, 0, 0);

    if (pCtx->mState == 5) {
        if (pCtx->mFlag1c)
            FUN_00c9cf90(pCtx->mpRefB, 0);
        else
            FUN_00c9bef0(pCtx->mpRefA, 0);
    }

    if (pCtx->mSpotIndex >= 0) {
        if (pCtx->mFlag1c) {
            u32 id = (u32)((F0p)VS(pCtx->mpRefB, 0x58))(pCtx->mpRefB);
            FindSpot(pCtx->mpRefC, id, pCtx->mSpotIndex);
        } else {
            FindSpot(pCtx->mpRefC, 0xc, pCtx->mSpotIndex);
        }
    }

    if (pCtx->mpRefC != 0)
        vc_v(pCtx->mpRefC, 4);
    if (pCtx->mpRefB != 0)
        vc_v(pCtx->mpRefB, 4);
    if (pCtx->mpRefA != 0)
        vc_v(pCtx->mpRefA, 4);
}

// @ 0x00db24c0
char SP__TRIBE_REPAIR_Tick(void *pCreature, TaskCtx *pCtx, float dt)
{
    if (pCtx->mpRefB == 0 && pCtx->mpRefA == 0) {
        FUN_00da6270(pCreature, 0x18);
        return 1;
    }
    float f0c = (float)(int)*(u32 *)&dt;
    (void)f0c;
    pCtx->mTimer = pCtx->mTimer - dt;

    float tPosX, tPosY, tPosZ, tRadius;
    void *pActive;

    if (pCtx->mFlag1c) {
        void *pObj = pCtx->mpRefB;
        void *pPos = ((F0p)VS((char *)pObj + 0x34, 0x2c))((char *)pObj + 0x34);
        tPosX = *(float *)pPos;
        tPosY = *(float *)((char *)pPos + 4);
        tPosZ = *(float *)((char *)pPos + 8);
        tRadius = ((float (__thiscall *)(void *))VS((char *)pObj + 0x34, 0x74))((char *)pObj + 0x34);
        pActive = (pObj != 0) ? ((F0p)VS(pObj, 0x58))(pObj) : 0;
    } else {
        void *pObj = pCtx->mpRefA;
        void *pPos = ((F0p)VS((char *)pObj + 0x34, 0x2c))((char *)pObj + 0x34);
        tPosX = *(float *)pPos;
        tPosY = *(float *)((char *)pPos + 4);
        tPosZ = *(float *)((char *)pPos + 8);
        tRadius = ((float (__thiscall *)(void *))VS((char *)pObj + 0x34, 0x74))((char *)pObj + 0x34);
        pActive = (pObj != 0) ? (char *)pObj + 0x120 : 0;
    }

    float dx = tPosX - pCtx->mPosX;
    float dy = tPosY - pCtx->mPosY;
    float dz = tPosZ - pCtx->mPosZ;
    if (dx * dx + dy * dy + dz * dz > 1.0f)
        return 0;

    float someRadius = FUN_00bfc490(pActive);
    char bl = (FUN_0104bdb0() <= someRadius);
    void *pLoco = (char *)pCreature + 0xc0;
    float locoR = ((float (__thiscall *)(void *))VS(pLoco, 0x74))(pLoco);
    float reach = (locoR + tRadius) + 12.0f;
    float reachSq = reach * reach;

    switch (pCtx->mState - 1) {
    case 0: {
        FUN_00c25480(pCreature, (!bl) + 0x13, 0);
        void *pInfo = FUN_00c41ec0((char *)pCreature + 0xc0);
        char doMove = (*(int *)((char *)pInfo + 0x5c) == 0);
        if (!doMove) {
            float *pAim = (float *)FUN_00c423c0(pInfo);
            float ax = pAim[0] - tPosX;
            float ay = pAim[1] - tPosY;
            float az = pAim[2] - tPosZ;
            if (ax * ax + ay * ay + az * az > *(float *)0x1572070)
                doMove = 1;
        }
        if (doMove) {
            float spd1 = *(float *)0x1470f1c;
            MoveToPointAtSpeed(pCreature, 2, (void *)&tPosX, 1.0f, spd1);
        }
        void *pPos2 = ((F0p)VS(pLoco, 0x2c))(pLoco);
        float bx = *(float *)pPos2 - tPosX;
        float by = *(float *)((char *)pPos2 + 4) - tPosY;
        float bz = *(float *)((char *)pPos2 + 8) - tPosZ;
        if (bx * bx + by * by + bz * bz < reachSq)
            pCtx->mState = 2;
        break;
    }
    case 1: {
        FUN_00c25480(pCreature, (!bl) + 0x13, 0);
        float *pSpot = (float *)FUN_00c986d0(pActive, &pCtx->mSpotIndex, pCreature);
        if (pCtx->mSpotIndex < 0) {
            FUN_00da6270(pCreature, 0x18);
            return 1;
        }
        float locoR2 = ((float (__thiscall *)(void *))VS(pLoco, 0x74))(pLoco);
        float aimDist = (locoR2 + tRadius) + 0.1f;
        float dirX = pSpot[0] - tPosX;
        float dirY = pSpot[1] - tPosY;
        float dirZ = pSpot[2] - tPosZ;
        float nrm[3];
        normalized_safe(nrm, &dirX);
        float goalX = nrm[0] * aimDist + tPosX;
        float goalY = nrm[1] * aimDist + tPosY;
        float goalZ = nrm[2] * aimDist + tPosZ;
        float faceX = -nrm[0];
        float faceY = -nrm[1];
        float faceZ = -nrm[2];
        float p1 = *(float *)0x157206c;
        float p2 = *(float *)0x1572070;
        MoveToPointAndFacing(pCreature, 2, &goalX, &faceX, p2, p1);
        pCtx->mState = 3;
        return 1;
    }
    case 2: {
        char ok = FUN_00c25480(pCreature, (!bl) + 0x13, 0);
        if (ok) {
            pCtx->mFlag1d = bl;
            if (IsNearGoal(pLoco)
                && AnimationFinished(pCreature, 0)
                && !CCM_e0c0(pCreature, 0x562bd84)
                && !CCM_e0c0(pCreature, 0x563e05c)) {
                ((F0v)VS(pLoco, 0xec))(pLoco);
                if (pCtx->mFlag1d)
                    PlayAnimation(pCreature, 0x563e05c, 1, 0xffffffff);
                else {
                    PlayAnimation(pCreature, 0x562bd7f, 1, 0xffffffff);
                    PlayAnimation(pCreature, 0x562bd84, 1, 0xffffffff);
                }
                if (pCtx->mFlag1c)
                    FUN_00c9cf90(pCtx->mpRefB, 1);
                else
                    FUN_00c9bef0(pCtx->mpRefA, 1);
                pCtx->mState = 5;
                return 1;
            }
        }
        break;
    }
    case 3: {
        if (AnimationFinished(pCreature, 0)) {
            float locoR3 = ((float (__thiscall *)(void *))VS(pLoco, 0x74))(pLoco);
            float spawnDist = (locoR3 + tRadius) + 4.0f;
            ((F3p)VS(pCreature, 0x84))(pCreature, 0, 0, 0);
            float distIn[4];
            distIn[0] = 1.0f;
            distIn[1] = spawnDist + 2.0f;
            distIn[2] = 1.0f;
            distIn[3] = 2.0f;
            float rotOut[3];
            float rotIn[3];
            rotIn[0] = 0.0f;
            rotIn[1] = 0.0f;
            rotIn[2] = 0.0f;
            void *pModel = FUN_00b3d350(rotOut, rotIn);
            void *pWorld = SP__cPlanetModel__MakeRandomWorldPosition(pModel, rotOut, rotIn,
                                                                     distIn[1], 2.0f);
            char navGoal[0x80];
            cNavigationGoal__InitAt(navGoal, pWorld);
            void *pGoal = ((F0p)VS(pLoco, 0xdc))(pLoco);
            FUN_007a41a0(navGoal);
            CCB_cff0(pCreature, 2);
            FindSpot(pActive, pCtx->mSpotIndex, 0);
            pCtx->mSpotIndex = -1;
            FUN_00da6270(pCreature, 0x18);
            return 1;
        }
        break;
    }
    case 4: {
        if (pCtx->mFlag1d && !CCM_e0c0(pCreature, 0x563e05c))
            PlayAnimation(pCreature, 0x563e05c, 1, 0xffffffff);
        if (bl != pCtx->mFlag1d) {
            if (pCtx->mFlag1c)
                FUN_00c9cf90(pCtx->mpRefB, 0);
            else
                FUN_00c9bef0(pCtx->mpRefA, 0);
            if (!pCtx->mFlag1d)
                PlayAnimation(pCreature, 0x562bd89, 1, 0xffffffff);
            pCtx->mState = 3;
        }
        float f = FUN_00bfc490(pActive);
        if (f != 1.0f && pActive && *(float *)((char *)pActive + 0x38) > 0.0f) {
            float a = ((float (__thiscall *)(void *))VS(pActive, 0x58))(pActive);
            float b = *(float *)((char *)pActive + 0x38);
            float c = ((float (__thiscall *)(void *))VS(pActive, 0x58))(pActive);
            float v = (c * *(float *)0x1581284) * dt + b;
            float *pMin = (a <= v) ? &a : &v;
            FUN_00f924e0(pActive, *pMin);
            return 1;
        }
        if (pCtx->mFlag1c)
            FUN_00c9cf90(pCtx->mpRefB, 0);
        else
            FUN_00c9bef0(pCtx->mpRefA, 0);
        pCtx->mState = 4;
        return 1;
    }
    }
    return 1;
}

// The 0x88-byte descriptor filled in by FUN_00db2c00: a 0x24-byte direction/scale
// block at +0x24, a flags/count word pair at +0x50, a position at +0x54, then a
// 0x24-byte copy of the source object's +0x20 block at +0x64.
struct EffectBlock {
    u32   mPad00[9];   // +0x00
    float mMat0;       // +0x24
    float mMat1;       // +0x28
    float mMat2;       // +0x2c
    float mMat3;       // +0x30
    float mMat4;       // +0x34
    float mMat5;       // +0x38
    float mMat6;       // +0x3c
    float mMat7;       // +0x40
    float mMat8;       // +0x44
    float mMat9;       // +0x48
    u32   mPad4c;      // +0x4c
    u16   mFlags;      // +0x50
    u16   mCount;      // +0x52
    float mPosX;       // +0x54
    float mPosY;       // +0x58
    float mPosZ;       // +0x5c
    float mOne;        // +0x60
    u32   mBody[9];    // +0x64
};

// @ 0x00db2c00
void FUN_00db2c00(void *pThis)
{
    void **pIt = *(void ***)((char *)pThis + 0x14);
    void **pEnd = *(void ***)((char *)pThis + 0x18);
    if (pIt == pEnd)
        return;

    do {
        void *pObj = *pIt;
        u32 key = *(u32 *)((char *)pObj + 0x58);
        u32 effectId = 0;
        if (key == 0x29c388a)
            effectId = *(u32 *)0x0159d564;
        else if (key == 0x3a8be428)
            effectId = *(u32 *)0x0159d568;
        else if (key == 0x6d60a1cc)
            effectId = *(u32 *)0x0159d56c;

        void *pRef = 0;
        void *pMgr = SP__EffectsManager();
        char ok = ((char (__thiscall *)(void *, u32, int, void **))VS(pMgr, 0x2c))(pMgr, effectId, 0, &pRef);
        if (ok) {
            EffectBlock blk;
            blk.mPosX = *(float *)0x0169f438;
            blk.mPosY = *(float *)0x0169f43c;
            blk.mPosZ = *(float *)0x0169f440;
            blk.mOne = 1.0f;
            blk.mMat0 = *(float *)0x0169f414;
            blk.mMat1 = *(float *)0x0169f418;
            blk.mMat2 = *(float *)0x0169f41c;
            blk.mMat3 = *(float *)0x0169f420;
            blk.mMat4 = *(float *)0x0169f424;
            blk.mMat5 = *(float *)0x0169f428;
            blk.mMat6 = *(float *)0x0169f42c;
            blk.mMat7 = *(float *)0x0169f430;
            blk.mMat8 = *(float *)0x0169f434;
            blk.mCount = 0;
            blk.mFlags = 0;
            blk.mMat9 = *(float *)0x0169f438;
            blk.mPad4c = *(u32 *)0x0169f43c;

            float base[3];
            FUN_00b02b90(base, 0);

            float px = *(float *)((char *)pObj + 0x10);
            float py = *(float *)((char *)pObj + 0x14);
            float pz = *(float *)((char *)pObj + 0x18);
            float dx = px - base[0];
            float dy = py - base[1];
            float dz = pz - base[2];
            float dist = sqrtf(dz * dz + dy * dy + dx * dx);
            float invLen = 1.0f / sqrtf(px * px + py * py + pz * pz + 1e-08f);
            float fx = px + (px * invLen) * dist;
            float fy = py + (py * invLen) * dist;
            float fz = pz + (pz * invLen) * dist;

            blk.mPosX = fx;
            blk.mPosY = fy;
            blk.mPosZ = fz;
            for (int k = 0; k < 9; k++)
                blk.mBody[k] = *(u32 *)((char *)pObj + 0x20 + k * 4);
            blk.mCount += 2;
            blk.mFlags |= 4;
            blk.mFlags |= 2;
            blk.mPosX = fx;
            blk.mPosY = fy;
            blk.mPosZ = fz;
            ((F1p)VS(pRef, 0x18))(pRef, &blk.mFlags);
            ((F1u)VS(pRef, 8))(pRef, 0);
        }
        if (pRef != 0)
            vc_v(pRef, 4);
        pIt++;
    } while (pIt != *(void ***)((char *)pThis + 0x18));
}

// @ 0x00db2f10
char FUN_00db2f10(void *pObj, u32 a2, u32 a3, u32 a4, u32 a5, TaskCtx *pCtx)
{
    (void)a2; (void)a3; (void)a4; (void)a5;
    if (pCtx != 0)
        pCtx->mpRefC = 0;

    void *pOrder = FUN_00bca2c0(*(void **)((char *)pObj + 0xb4c));
    if (pOrder == 0)
        return 0;
    if (*(int *)pOrder != 0x16)
        return 0;

    char *pData = (char *)pOrder + 0x39;
    u16 kind = *(u16 *)(pData + 0x12);
    void *pKeyObj;
    if (kind == 0xa || kind == 0x10) {
        if (pData[0x10] & 0x30)
            pKeyObj = *(void **)pData;
        else
            pKeyObj = (kind != 0) ? (void *)pData : 0;
    } else {
        pKeyObj = (void *)0x015d1164;
    }

    u32 key = *(u32 *)pKeyObj;
    pCtx->mState = key;
    pCtx->mpRefA = 0;
    pCtx->mpRefB = 0;

    int found = ((F1i_r)VS(pObj, 0xb4))(pObj, key);
    return (char)(found != 0);
}

// @ 0x00db2fa0
void FUN_00db2fa0(TaskCtx *p1, u32 a2, u32 a3, u32 a4, u32 a5, TaskCtx *pCtx)
{
    (void)p1; (void)a2; (void)a3; (void)a4; (void)a5;
    if (pCtx->mpRefC != 0) {
        void *p = pCtx->mpRefC;
        pCtx->mpRefC = 0;
        vc_v(p, 4);
    }
    if (pCtx != 0 && pCtx->mpRefC != 0)
        vc_v(pCtx->mpRefC, 4);
}
