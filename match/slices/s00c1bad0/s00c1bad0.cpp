// Slice s00c1bad0 -- SP::cSPCreatureBase locomotion / navigation cluster
// (0x00c1bad0 .. 0x00c1c9ef, 7 functions, navigation.cpp).
//
//   00c1bad0  cSPCreatureBase::FUN_00c1bad0      re-init one navigation goal from a
//                                                SpVector<cCurvePoint>& (this = goal, ret 4)
//   00c1bbd0  cSPCreatureBase::~body             vtable re-stamp + ~40 member releases
//   00c1c080  cSPCreatureBase::FUN_00c1c080      SetGoal-from-vector helper (ret 0x14)
//   00c1c1d0  cSPCreatureBase::MoveToPointAtSpeed
//   00c1c310  cSPCreatureBase::MoveToPointAtSpeedPathPlan
//   00c1c5c0  cSPCreatureBase::MoveToPointAndFacingAtSpeed
//   00c1c8e0  cSPCreatureBase::Shutdown
//
// The class layout follows the retail disassembly and the sibling slices s00c22010
// (cSPCreatureBase / cLocomotiveObject member split) and s00c1c9f0 (creature field map).
// cSPCreatureBase : cGameData(+0x000) cInteractionAgent(+0x034) cLocomotiveObject(+0x0c0)
//                   cCombatant(+0x5a8), own members from +0x5e8.
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <string.h>
#include <math.h>

#define PVN(n) virtual void pv##n();

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef          int   i32;
typedef float          f32;

struct Vec3 { f32 x, y, z; };

class cSPCreatureBase;
class cLocomotiveObject;
class cAnimatingCreature;

// ---- literals / globals referenced by the originals -----------------------------------------
extern const f32 _DivOneFifty;         // 0x013ec4b4
extern const f32 _BigFloat;            // 0x0146a32c
extern const f32 _Tolerance;           // 0x013ec4d0
extern const f32 _SmallTolerance;      // 0x013ef480
extern f32 g_DefaultGoalDir[3];        // 0x0168d910, 0x0168d914, 0x0168d918
extern f32 g_SpeedBonus;               // 0x0150c900

// ---- vtables --------------------------------------------------------------------------------
extern void* g_vtbl_cSPCreatureBase;   // 0x0146a5f0
extern void* g_vtbl_cGameData;         // 0x0146a5dc
extern void* g_vtbl_cInteractionAgent; // 0x0146a598
extern void* g_vtbl_cLocoSub;          // 0x0146a530
extern void* g_vtbl_cLocomotiveObject; // 0x0146a430
extern void* g_vtbl_cLocoSub2;         // 0x0146a424
extern void* g_vtbl_cSPCreatureBase2;  // 0x0146a408
extern void* g_vtbl_cCombatant;        // 0x0146a3a0
extern void* g_vtbl_cSub670;           // 0x0146a388

// =============================================================================================
// eastl containers used by this slice
// =============================================================================================
namespace eastl
{
struct allocator { int mFlags; };

template <typename T, typename Alloc = allocator>
class vector
{
public:
    T*   mpBegin;       // +0x000
    T*   mpEnd;         // +0x004
    T*   mpCap;         // +0x008
    Alloc mAlloc;       // +0x00c

    u32 size() const { return (u32)(mpEnd - mpBegin); }
};
} // namespace eastl

// A doubly-linked eastl::list sentinel (prev/next) as used at creature+0xf84.
struct ListHead { ListHead* mpNext; ListHead* mpPrev; };

// =============================================================================================
// SP::tNavigationWaypoint -- the 0x74-byte goal structure (Claude-coined name; layout from
// the disassembly of 00c1bad0 / 00c1c1d0 / 00c1c5c0).
// =============================================================================================
struct tNavigationWaypoint
{
    tNavigationWaypoint* mpNext;      // +0x00   (linked-list forward pointer / copied buffer)
    u8   mPad04[0x04];
    void* mpPathOwner;                // +0x08   (owner passed to the vector helper)
    u8   mPad0c[0x08];
    Vec3 mPos;                        // +0x14   (destination position)
    u8   mPad20[0x10];
    f32  mf30;                        // +0x30
    u8   mPad34[0x08];
    u8   mb3c;                        // +0x3c
    u8   mPad3d[0x13];
    f32  mf50;                        // +0x50
    f32  mf54;                        // +0x54
    f32  mf58;                        // +0x58
    u8   mb5c;                        // +0x5c   (accessible = initialized)
    u8   mPad5d[0x03];
    f32  mf60;                        // +0x60   (arrival radius)
    f32  mf64;                        // +0x64   (speed)
    f32  mf68;                        // +0x68   (facing tolerance)
    f32  mf6c;                        // +0x6c   (facing offset)
    void* mp70;                       // +0x70   (path-plan owner)
};

// =============================================================================================
// the four base sub-objects of cSPCreatureBase, in compiler layout order
// =============================================================================================
class cGameData {
public:
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9)
    PVN(10) PVN(11)
    virtual void* vIdx12();      // 0x30   (the SpVector<cCurvePoint>* parent of a goal)
    virtual void  vIdx13(int);   // 0x34
    PVN(14) PVN(15) PVN(16) PVN(17) PVN(18) PVN(19) PVN(20)
    virtual void* vIdx21(int);   // 0x54
    virtual void  vIdx22(int);   // 0x58
    virtual void  vIdx23();      // 0x5c
    PVN(24) PVN(25) PVN(26) PVN(27) PVN(28) PVN(29) PVN(30) PVN(31) PVN(32)
    virtual void  vIdx33(void*); // 0x84
    PVN(34) PVN(35) PVN(36) PVN(37) PVN(38) PVN(39) PVN(40) PVN(41)
    virtual f32   GetTime(int);  // 0xa8
    PVN(43) PVN(44) PVN(45) PVN(46) PVN(47) PVN(48) PVN(49) PVN(50)
    virtual void* vIdx51();      // 0xcc
    virtual void  vIdx52();      // 0xd0
    PVN(53) PVN(54)
    virtual void  vIdx55(void*); // 0xdc
    PVN(56) PVN(57) PVN(58) PVN(59) PVN(60) PVN(61) PVN(62) PVN(63) PVN(64)
    virtual void  vIdx65();      // 0x104
    u8 mPad04[0x30];
};

class cInteractionAgent {
public:
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9)
    PVN(10) PVN(11)
    virtual void  ia30(void*);   // 0x30
    PVN(13)
    virtual f32   ia38(u32);     // 0x38
    u8 mPad04[0x8c - 4];
};

// ---- cLocomotiveObject (embedded at +0x0c0) --------------------------------------------------
class cLocomotiveObject {
public:
    virtual void* lo2c();                 // 0x2c  GetPosition -> Vec3*
    PVN(12) PVN(13) PVN(14) PVN(15)
    virtual void  lo40(u32);              // 0x40
    PVN(17) PVN(18) PVN(19) PVN(20)
    virtual void  lo54();                 // 0x54
    virtual void  lo58();                 // 0x58
    virtual void  lo5c();                 // 0x5c
    PVN(24) PVN(25) PVN(26) PVN(27) PVN(28) PVN(29)
    virtual f32   lo78(int, int);         // 0x78
    PVN(31) PVN(32) PVN(33) PVN(34)
    virtual void  lo8c();                 // 0x8c
    PVN(36)
    virtual bool  lo94();                 // 0x94
    PVN(38)
    virtual void  lo9c(void*);            // 0x9c
    PVN(40) PVN(41)
    virtual void  loa8();                 // 0xa8
    PVN(43) PVN(44) PVN(45) PVN(46) PVN(47) PVN(48) PVN(49) PVN(50) PVN(51)
    virtual void  lod0();                 // 0xd0
    virtual void  lod4(int, void*);       // 0xd4
    virtual void  lod8();                 // 0xd8
    virtual void  lodc(void*);            // 0xdc
    PVN(56) PVN(57) PVN(58) PVN(59) PVN(60) PVN(61)
    virtual void  lof8();                 // 0xf8

    u8   mPad04[0x54 - 0x04];
    tNavigationWaypoint* mpGoal;          // +0x054
    u8   mPad58[0x194 - 0x58];
    u32  mdw194;                          // +0x194
    u8   mPad198[0x2a0 - 0x198];
    f32  mf_2a0;                          // +0x2a0 (loco-relative 0x1e0; current speed)
    u8   mPad_2a4[0x2b0 - 0x2a4];
    void* mp_2b0;                         // +0x2b0 (loco-relative 0x1f0)
    u8   mPad_2b4[0x330 - 0x2b4];
    u32  mdw_330;                         // +0x330 (loco-relative 0x270)
    u8   mPad_334[0x4e8 - 0x334];

    void Shutdown();                      // 0x00c43f90
};

class cCombatant {
public:
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9)
    PVN(10) PVN(11) PVN(12) PVN(13) PVN(14) PVN(15) PVN(16) PVN(17) PVN(18)
    PVN(19) PVN(20) PVN(21) PVN(22) PVN(23) PVN(24) PVN(25) PVN(26)
    virtual void  co6c();                 // 0x6c
    PVN(28)
    virtual void  co74();                 // 0x74
    u8 mPad04[0x40 - 4];
};

// =============================================================================================
// SP::cSPCreatureBase
// =============================================================================================
class cSPCreatureBase : public cGameData, public cInteractionAgent,
                        public cLocomotiveObject, public cCombatant
{
public:
    // ---- helpers (thiscall) ----
    tNavigationWaypoint* FUN_00c1bad0(tNavigationWaypoint* pGoal, void* pPathOwner);  // 0x00c1bad0
    void  FUN_00c1bbd0();                                                    // 0x00c1bbd0
    void  FUN_00c1c080(u32 a, Vec3* pPos, Vec3* pDir, f32 f1, f32 f2);       // 0x00c1c080
    void  MoveToPointAtSpeed(void* pTarget, Vec3* pPos, f32 f0, f32 f1);     // 0x00c1c1d0
    void  MoveToPointAtSpeedPathPlan(void* pOwner, Vec3* pPos, f32 f0,
                                     u32 flags, char bPlan);                 // 0x00c1c310
    void  MoveToPointAndFacingAtSpeed(void* pOwner, Vec3* pPos, Vec3* pFacing,
                                      f32 f0, f32 f1);                       // 0x00c1c5c0
    void  Shutdown();                                                        // 0x00c1c8e0
    f32   FUN_00c0ce80(int a, int b);                                        // 0x00c0ce80
    void* FUN_00c41ec0();                                                    // 0x00c41ec0

    // ---- fields at absolute offsets >= 0x5e8 (the bases above already cover 0x000..0x5e7) ----
    u8   mPad_5e8[0xbb0 - 0x5e8];
    u8   mb_bb0;                       // +0xbb0
    u8   mPad_bb1[1];
    u8   mCurve[0x14];                 // +0xbc0  (SpVector<cCurvePoint>: begin/end/cap/alloc)
    Vec3 mLastGoalPos;                 // +0xbd4  (last accepted destination)
    u8   mPad_be0[0xbf4 - 0xbe0];
    tNavigationWaypoint* mpGoal_bf4;   // +0xbf4  (inline goal target)
    u8   mPad_bf8[0xf84 - 0xbf8];
    ListHead mRenderList;              // +0xf84  (eastl::list sentinel)
    u8   mPad_f8c[0xf98 - 0xf8c];
    void* mp_f98;                      // +0xf98
    void* mp_f9c;                      // +0xf9c
};

// ---- helpers used by the functions below ----------------------------------------------------
void  FUN_00c1b790(tNavigationWaypoint* pGoal, void* pSrc);          // 0x00c1b790
void  FUN_00b47520(void* p);                                          // 0x00b47520
void  FUN_00ac4570(void* pBegin, void* pEnd);                         // 0x00ac4570
void  FUN_00c0cff0(cSPCreatureBase* pCreature, u32 a, f32 f, void* pHint,
                   void* pOut, u32 flags);                            // 0x00c0cff0
void  FUN_00b3d290(void* pSearch, void* pCtx);                        // 0x00b3d290
void* FUN_00ac65d0(void* pSearch, void* pCtx, Vec3* pPos, u32 a, f32 f,
                   void* pHint, void* pOut, u32 flags, u32 b);        // 0x00ac65d0
void  FUN_00c7dba0(void* pSub);                                       // 0x00c7dba0
void  FUN_00bfc720(void* pSub);                                       // 0x00bfc720
void  FUN_00c144b0(void* pBegin, void* pEnd);                         // 0x00c144b0
void  FUN_00a24480(void* pBegin, void* pEnd);                         // 0x00a24480
void  DoNukeSubtree(void* pNode);                                     // rbtree nuke
void  FreeLooseBuffer(void* pBegin, void* pEnd, void** ppFreeList,
                      void* pPoolBegin, void* pPoolEnd);              // inline buffer free
void  FUN_00c7d650();                                                 // 0x00c7d650
void  FUN_00bfcd00();                                                 // 0x00bfcd00
void  FUN_00ac0520();                                                 // 0x00ac0520
void  FUN_00c432e0();                                                 // 0x00c432e0
void  FUN_00abfec0();                                                 // 0x00abfec0
void  FUN_00cee7a0();                                                 // 0x00cee7a0
void  FUN_00b184c0();                                                 // 0x00b184c0
void  FUN_00bc9fa0(void* p);                                          // 0x00bc9fa0
void  FUN_00bcae90(void* p);                                          // 0x00bcae90
void  cGonzagoTimer_Destroy(void* p);                                 // cGonzagoTimer::~cGonzagoTimer
void  cAnimatingCreature_Release(void* p);                            // 0x00a05270
void  EASTL_deallocate(void* p);                                      // 0x00f47380

// Small inline vtable-slot call helpers (keep the source readable).
static inline void* VFn(void* pObj, u32 slot)
{
    return *(void**)((u8*)*(void**)pObj + slot);
}
static inline u8* VCall(void* pObj, u32 slot)
{
    return (u8*)(*(void*(__thiscall**)(void*))VFn(pObj, slot))(pObj);
}
static inline void VCall0(void* pObj, u32 slot)
{
    (*(void(__thiscall**)(void*))VFn(pObj, slot))(pObj);
}

// =============================================================================================
// 00c1bad0  FUN_00c1bad0  -- re-init one navigation goal from a curve-path owner.
// `this` is the 0x74-byte goal; the SpVector<cCurvePoint>* arrives as the first stack arg;
// returns `this` in eax (thiscall ret 4).
// =============================================================================================
// @ 0x00c1bad0
tNavigationWaypoint* cSPCreatureBase::FUN_00c1bad0(tNavigationWaypoint* pGoal, void* pPathOwner)
{
    pGoal->mpNext   = 0;                   // +0x00
    pGoal->mPos.x   = 0.0f;                // +0x14
    pGoal->mPos.y   = 0.0f;                // +0x18
    pGoal->mPos.z   = 0.0f;                // +0x1c
    pGoal->mf50     = 0.0f;                // +0x50
    pGoal->mf54     = 0.0f;                // +0x54
    pGoal->mf58     = 0.0f;                // +0x58
    pGoal->mf60     = 1.0f;                // +0x60
    pGoal->mf64     = _DivOneFifty;        // +0x64
    pGoal->mf68     = 1.0f;                // +0x68
    pGoal->mf6c     = 0.0f;                // +0x6c
    pGoal->mp70     = (void*)pPathOwner;   // +0x70
    pGoal->mb3c     = 0;                   // +0x3c
    pGoal->mb5c     = 0;                   // +0x5c

    if (*(void**)pPathOwner != *(void**)((u8*)pPathOwner + 4))   // begin != end
    {
        FUN_00c1b790(pGoal, pPathOwner);
        tNavigationWaypoint* pSrc = pGoal->mpNext;
        pGoal->mb5c = 1;
        u32* pDst = (u32*)((u8*)pGoal + 0x14);
        u32* pS   = (u32*)pSrc;
        for (int i = 0; i < 0xf; ++i)
            pDst[i] = pS[i];
        FUN_00b47520(pSrc);
        return pGoal;
    }
    pGoal->mb5c   = 0;
    pGoal->mPos.x = 0.0f;
    pGoal->mPos.y = 0.0f;
    pGoal->mPos.z = 0.0f;
    return pGoal;
}

// =============================================================================================
// 00c1bbd0  FUN_00c1bbd0  -- the cSPCreatureBase destructor body (this in ecx).
// =============================================================================================
// @ 0x00c1bbd0
void cSPCreatureBase::FUN_00c1bbd0()
{
    *(void**)((u8*)this + 0x000) = &g_vtbl_cSPCreatureBase;
    *(void**)((u8*)this + 0x004) = &g_vtbl_cGameData;
    *(void**)((u8*)this + 0x034) = &g_vtbl_cInteractionAgent;
    *(void**)((u8*)this + 0x058) = &g_vtbl_cLocoSub;
    *(void**)((u8*)this + 0x0c0) = &g_vtbl_cLocomotiveObject;
    *(void**)((u8*)this + 0x194) = &g_vtbl_cLocoSub2;
    *(void**)((u8*)this + 0x590) = &g_vtbl_cSPCreatureBase2;
    *(void**)((u8*)this + 0x5a8) = &g_vtbl_cCombatant;
    *(void**)((u8*)this + 0x670) = &g_vtbl_cSub670;

    void* p = *(void**)((u8*)this + 0xb48);          // +0x2d2 dwords
    if (p)
    {
        FUN_00bc9fa0(p);
        EASTL_deallocate(p);
    }

    p = *(void**)((u8*)this + 0xb4c);                // +0x2d3 dwords
    if (p)
    {
        FUN_00bcae90(p);
        EASTL_deallocate(p);
    }

    FUN_00ac4570(*(void**)((u8*)this + 0xf88), *(void**)((u8*)this + 0xf84));

    // Three 0x20-byte repetition records at +0xf90 / +0xfb0 / +0xfd0, each owning
    // two AutoRefs and one slot-0x64 object.
    for (int i = 0; i < 3; ++i)
    {
        u8* rec = (u8*)this + 0xf90 + i * 0x20;
        void** ppHead = (void**)(rec + 0x00);
        void** ppA    = (void**)((u8*)rec - 0x04);
        void** ppB    = (void**)(rec + 0x18);
        void** ppC    = (void**)((u8*)rec - 0x08);

        *ppHead = 0;
        if (*ppA)
        {
            VCall(*ppA, 0x0c);
            if (*ppA)
            {
                *ppA = 0;
                VCall0(*ppA, 0x04);
            }
        }
        if (*ppB)
        {
            VCall(*ppB, 0x0c);
            if (*ppB)
            {
                *ppB = 0;
                VCall0(*ppB, 0x04);
            }
        }
        if (*ppC)
        {
            *ppC = 0;
            VCall0(*ppC, 0x64);
        }
        if (*ppB)
            VCall0(*ppB, 0x04);
        if (*ppA)
            VCall0(*ppA, 0x04);
        if (*ppC)
            VCall0(*ppC, 0x64);
    }

    p = *(void**)((u8*)this + 0xf90 + 0x360);        // +0x3a6 dwords
    if (p && *(int*)((u8*)p - 4) != 0)
        EASTL_deallocate(p);

    p = *(void**)((u8*)this + 0x15b8);               // +0x39f dwords
    if (p)
        VCall0(p, 0x64);

    FUN_00c144b0(*(void**)((u8*)this + 0x1640), *(void**)((u8*)this + 0x1644));
    p = *(void**)((u8*)this + 0x1640);               // +0x390 dwords
    if (p && *(int*)((u8*)p - 4) != 0)
        EASTL_deallocate(p);

    p = *(void**)((u8*)this + 0x15e0);               // +0x389 dwords
    if (p && *(int*)((u8*)p - 4) != 0)
        EASTL_deallocate(p);

    DoNukeSubtree(*(void**)((u8*)this + 0x1a10));    // +0x385 dwords (rbtree root)

    FUN_00a24480(*(void**)((u8*)this + 0x2b78), *(void**)((u8*)this + 0x2b7c));
    FreeLooseBuffer(*(void**)((u8*)this + 0x2b78), *(void**)((u8*)this + 0x2b7c),
                    (void**)((u8*)this + 0x2bb4),
                    *(void**)((u8*)this + 0x2b98), *(void**)((u8*)this + 0x2b9c));

    FUN_00a24480(*(void**)((u8*)this + 0x2698), *(void**)((u8*)this + 0x269c));
    FreeLooseBuffer(*(void**)((u8*)this + 0x2698), *(void**)((u8*)this + 0x269c),
                    (void**)((u8*)this + 0x26d4),
                    *(void**)((u8*)this + 0x26b8), *(void**)((u8*)this + 0x26bc));

    p = *(void**)((u8*)this + 0xc28);                // +0x30a dwords
    if (p && *(int*)((u8*)p - 4) != 0)
        EASTL_deallocate(p);

    p = *(void**)((u8*)this + 0xbc0);                // +0x2f0 dwords
    if (p && *(int*)((u8*)p - 4) != 0)
        EASTL_deallocate(p);

    cGonzagoTimer_Destroy((u8*)this + 0xb90);        // +0x2e4 dwords

    p = *(void**)((u8*)this + 0xb54);                // +0x2d5 dwords (animating creature)
    if (p)
        cAnimatingCreature_Release(p);

    p = *(void**)((u8*)this + 0xb50);                // +0x2d4 dwords
    if (p)
        VCall0(p, 0x04);

    p = *(void**)((u8*)this + 0xb38);                // +0x2ce dwords
    if (((i32)((u8*)*(void**)((u8*)this + 0xb40) - (u8*)p) >> 1) * 2 > 2 && p)
        EASTL_deallocate(p);

    FUN_00c7d650();
    FUN_00bfcd00();
    FUN_00ac0520();
    FUN_00c432e0();
    FUN_00abfec0();
    FUN_00cee7a0();
    FUN_00b184c0();
}

// =============================================================================================
// 00c1c080  FUN_00c1c080 -- SetGoal-from-a-navigation-waypoint (this = creature, ret 0x14).
// =============================================================================================
// @ 0x00c1c080
void cSPCreatureBase::FUN_00c1c080(u32 a, Vec3* pPos, Vec3* pDir, f32 f1, f32 f2)
{
    tNavigationWaypoint goal;
    goal.mPos    = *pDir;                  // +0x14 destination orientation
    goal.mPad0c[0] = 0;                    // clear the racy tail dwords
    goal.mf50    = 0.0f;
    goal.mf54    = 0.0f;
    goal.mf58    = 0.0f;
    goal.mf60    = f2;                     // +0x60
    goal.mf64    = _BigFloat;              // +0x64
    goal.mf68    = 4.0f;                   // +0x68 literal (local_10)
    goal.mf6c    = _DivOneFifty;           // +0x6c (local_c)
    goal.mb5c    = 0;
    goal.mf30    = 0.0f;
    goal.mpNext  = 0;
    goal.mpPathOwner = 0;

    // loco slot 0xdc: set goal / recompute path with the local waypoint.
    (*(void(__thiscall**)(void*, void*))((u8*)*(void**)((u8*)this + 0xc0) + 0xdc))
        ((u8*)this + 0xc0, &goal);

    mp_f98 = (void*)a;

    f32 t;
    if (mb_bb0 == 0)
        t = FUN_00c0ce80(1, 0);
    else
        t = FUN_00c0ce80(2, 1) + g_SpeedBonus;
    mf_2a0 = t;
    mdw_330 = 0;

    FUN_00ac4570(mCurve, *(void**)(mCurve + 4));       // erase the whole curve span

    if (goal.mpNext && *(int*)((u8*)goal.mpNext - 4) != 0)
        EASTL_deallocate(goal.mpNext);
}

// =============================================================================================
// 00c1c1d0  SP::cSPCreatureBase::MoveToPointAtSpeed (this = creature, ret 0x10).
// =============================================================================================
// @ 0x00c1c1d0
void cSPCreatureBase::MoveToPointAtSpeed(void* pTarget, Vec3* pPos, f32 f0, f32 f1)
{
    tNavigationWaypoint goal;
    goal.mPos    = *pPos;                  // +0x14
    goal.mf50    = 0.0f;
    goal.mf54    = 0.0f;
    goal.mf58    = 0.0f;
    goal.mf60    = f1;                     // +0x60
    goal.mf64    = f0;                     // +0x64
    goal.mf68    = _DivOneFifty;           // +0x68
    goal.mf6c    = 1.0f;                   // +0x6c
    goal.mb5c    = 0;
    goal.mf30    = 0.0f;
    goal.mpNext  = 0;
    goal.mpPathOwner = 0;

    (*(void(__thiscall**)(void*, void*))((u8*)*(void**)((u8*)this + 0xc0) + 0xdc))
        ((u8*)this + 0xc0, &goal);

    if (goal.mpNext && *(int*)((u8*)goal.mpNext - 4) != 0)
        EASTL_deallocate(goal.mpNext);

    mp_f98 = pTarget;

    f32 t;
    if (mb_bb0 == 0)
        t = FUN_00c0ce80(1, 0);
    else
        t = FUN_00c0ce80(2, 1) + g_SpeedBonus;
    mf_2a0 = t;
    mdw_330 = 0;

    FUN_00ac4570(mCurve, *(void**)(mCurve + 4));
}

// =============================================================================================
// 00c1c310  SP::cSPCreatureBase::MoveToPointAtSpeedPathPlan
// this = creature (ecx); args (owner, Vec3* pPos, f0, u32 flags, char bPlan); ret 0x14.
// =============================================================================================
// @ 0x00c1c310
void cSPCreatureBase::MoveToPointAtSpeedPathPlan(void* pOwner, Vec3* pPos, f32 f0,
                                                 u32 flags, char bPlan)
{
    u8* pCurve = mCurve;                               // SpVector<cCurvePoint>
    tNavigationWaypoint* pGoal = mpGoal_bf4;

    if (!bPlan)
        goto clear;

    if (*(void**)pCurve == *(void**)(pCurve + 4))
        goto clear;

    {
        Vec3* pCur = (Vec3*)VCall((u8*)this + 0xc0, 0x2c);
        f32 dy = pCur->y - mLastGoalPos.y;
        f32 dx = pCur->x - mLastGoalPos.x;
        f32 dz = pCur->z - mLastGoalPos.z;
        f32 d2 = (dy * dy + dx * dx) + dz * dz;
        if (_Tolerance <= d2)
            goto clear;

        Vec3* pLast = (Vec3*)((u8*)*(void**)(pCurve + 4) - 0x3c);
        f32 gy = pLast->y - pPos->y;
        f32 gx = pLast->x - pPos->x;
        f32 gz = pLast->z - pPos->z;
        f32 g2 = (gy * gy + gx * gx) + gz * gz;
        if (_Tolerance <= g2)
            goto clear;

        // Accept the new destination: move the tail curve point, update the goal speed,
        // clear the 0x4 path-plan bit and re-issue the goal.
        Vec3* pTail = (Vec3*)((u8*)*(void**)(pCurve + 4) - 0x3c);
        *pTail = *pPos;
        *(f32*)((u8*)*(void**)(pCurve + 4) - 0x30) = f0;
        mdw_330 &= 0xfffffffb;

        tNavigationWaypoint local;
        FUN_00c1bad0(&local, pCurve);
        (*(void(__thiscall**)(void*, void*))((u8*)*(void**)((u8*)this + 0xc0) + 0xdc))
            ((u8*)this + 0xc0, &local);
        if (local.mpNext && *(int*)((u8*)local.mpNext - 4) != 0)
            EASTL_deallocate(local.mpNext);

        void* pR = FUN_00c41ec0();
        *(f32*)((u8*)pR + 0x20) = f0;
        pR = FUN_00c41ec0();
        *(f32*)((u8*)pR + 0x60) = (f32)flags;

        FUN_00c0cff0(this, flags, f0, &local, pGoal, 4);
        return;
    }

clear:
    FUN_00ac4570(*(void**)pCurve, *(void**)(pCurve + 4));
    {
        Vec3* pCur = (Vec3*)VCall((u8*)this + 0xc0, 0x2c);
        mLastGoalPos = *pCur;
    }
    FUN_00c41ec0();

    pGoal->mf50 = 0.0f;                                // +0x50
    pGoal->mPos = *pPos;                               // +0x14
    pGoal->mf60 = f0;                                  // +0x60
    pGoal->mf54 = 0.0f;
    pGoal->mf58 = (f32)flags;                          // +0x58
    pGoal->mb5c = 0;

    mp_f9c = pOwner;
    mdw_330 = 4;

    u32 searchId = (u32)VCall((u8*)this + 0xc0, 0x58);
    void* pCtx = FUN_00ac65d0(this, pPos, pPos, 0, f0,
                              mCurve, (void*)mpGoal_bf4, searchId & 0xff, 0);
    void* pSearch = (void*)((u8*)this + 0x194);
    FUN_00b3d290((void*)0x01565b68, pCtx);
    FUN_00ac65d0(pSearch, pCtx, pPos, 0, f0, mCurve, (void*)mpGoal_bf4,
                 searchId & 0xff, 0);
}

// =============================================================================================
// 00c1c5c0  SP::cSPCreatureBase::MoveToPointAndFacingAtSpeed (this = creature, ret 0x14).
// =============================================================================================
// @ 0x00c1c5c0
void cSPCreatureBase::MoveToPointAndFacingAtSpeed(void* pOwner, Vec3* pPos, Vec3* pFacing,
                                                  f32 f0, f32 f1)
{
    Vec3 facing = *pFacing;

    Vec3* pCur = (Vec3*)VCall((u8*)this + 0xc0, 0x2c);

    if (mp_2b0 == 0 &&
        !(pCur->x == g_DefaultGoalDir[0] && pCur->y == g_DefaultGoalDir[1] &&
          pCur->z == g_DefaultGoalDir[2]))
    {
        // Project the requested facing onto the plane orthogonal to pPos.
        f32 inv = 1.0f / (f32)sqrt((double)((pPos->x * pPos->x + pPos->y * pPos->y)
                                             + pPos->z * pPos->z));
        f32 dot = (pFacing->y * (pPos->y * inv) + pFacing->x * (pPos->x * inv))
                  + pFacing->z * (pPos->z * inv);
        facing.x = pFacing->x - (pPos->x * inv) * dot;
        facing.y = pFacing->y - (pPos->y * inv) * dot;
        facing.z = pFacing->z - (pPos->z * inv) * dot;

        if (facing.x != g_DefaultGoalDir[0] || facing.y != g_DefaultGoalDir[1] ||
            facing.z != g_DefaultGoalDir[2])
        {
            f32 len = (f32)sqrt((double)(facing.x * facing.x
                                         + (facing.y * facing.y + facing.z * facing.z)));
            f32 n = 1.0f / len;
            facing.x *= n;
            facing.y *= n;
            facing.z *= n;
        }
    }

    tNavigationWaypoint goal;
    goal.mPos  = *pPos;                    // +0x14
    goal.mf50  = f0;                       // +0x50
    goal.mf30  = facing.x;                 // (rotation slot used as facing)
    goal.mPad34[0] = 0;
    goal.mf54  = facing.y;
    goal.mf58  = facing.z;
    goal.mf60  = 0.0f;                     // +0x60
    goal.mf64  = _SmallTolerance;          // +0x64
    goal.mf68  = 0.0f;                     // +0x68
    goal.mf6c  = 0.0f;                     // +0x6c
    goal.mb5c  = 0;
    goal.mb3c  = 3;
    goal.mpNext  = 0;
    goal.mpPathOwner = 0;

    (*(void(__thiscall**)(void*, void*))((u8*)*(void**)((u8*)this + 0xc0) + 0xdc))
        ((u8*)this + 0xc0, &goal);

    if (goal.mpNext && *(int*)((u8*)goal.mpNext - 4) != 0)
        EASTL_deallocate(goal.mpNext);

    mp_f98 = pOwner;

    f32 t;
    if (mb_bb0 == 0)
        t = FUN_00c0ce80(1, 0);
    else
        t = FUN_00c0ce80(2, 1) + g_SpeedBonus;
    mf_2a0 = t;
    mdw_330 = 0;

    FUN_00ac4570(mCurve, *(void**)(mCurve + 4));
}

// =============================================================================================
// 00c1c8e0  SP::cSPCreatureBase::Shutdown (this in ecx, ret 0).
// =============================================================================================
// @ 0x00c1c8e0
void cSPCreatureBase::Shutdown()
{
    VCall0(this, 0xc4);

    ((cLocomotiveObject*)((u8*)this + 0xc0))->Shutdown();
    FUN_00c7dba0((u8*)this + 0x670);

    void* pAnim = *(void**)((u8*)this + 0xb54);
    if (pAnim && *(void**)pAnim)
    {
        if ((i32)VCall(pAnim, 0x70))
        {
            typedef void (__thiscall* fn_set)(void*, void*);
            (*(fn_set)((u8*)*(void**)pAnim + 0x70))(pAnim, (void*)0);
            void* pInner = (void*)VCall(pAnim, 0x70);
            (*(void(__thiscall**)(void*, void*))((u8*)*(void**)pInner + 0x3c))(pInner, pAnim);
            if (pAnim)
            {
                *(void**)((u8*)this + 0xb54) = 0;
                cAnimatingCreature_Release(pAnim);
            }
        }
    }

    FUN_00bfc720((u8*)this + 0x5a8);

    void* pSub = *(void**)((u8*)this + 0x2c);
    if (pSub)
    {
        *(void**)((u8*)this + 0x2c) = 0;
        VCall0(pSub, 0x04);
    }

    // eastl vector compact: memmove(begin, end, begin), then shrink end.
    u8* pBegin = *(u8**)((u8*)this + 0xc28);
    u8* pEnd   = *(u8**)((u8*)this + 0xc2c);
    memmove(pBegin, pEnd, (u32)(pEnd - pBegin));
    *(u8**)((u8*)this + 0xc2c) += ((i32)(pBegin - pEnd) >> 4) * 16;

    // Walk the render list at +0xf84; first reset each entry, then delete each node.
    u8* pSentinel = (u8*)this + 0xf84;
    u8* pNode = *(u8**)pSentinel;
    while (pNode != pSentinel)
    {
        void* pObj = *(void**)(pNode + 8);
        VCall(pObj, 0x0c);
        pNode = *(u8**)pNode;
    }

    pNode = *(u8**)pSentinel;
    while (pNode != pSentinel)
    {
        u8* pNext = *(u8**)pNode;
        void* pObj = *(void**)(pNode + 8);
        if (pObj)
            VCall0(pObj, 0x04);
        EASTL_deallocate(pNode);
        pNode = pNext;
    }
    *(u8**)(pSentinel + 4) = pSentinel;
    *(u8**)pSentinel = pSentinel;
}
