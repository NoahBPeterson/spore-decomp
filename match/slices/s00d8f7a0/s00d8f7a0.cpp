// Slice s00d8f7a0: SP creature-AI action activators -- the two "locating call"
// behaviour-tree actions, the "growl timer" action, and the noun-query helper
// they share (Simulator / creature-AI cluster).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
//
// These four routines are large and individually SSE/x87-scheduled; several of
// the engine classes they touch are defined outside the slice.  The bodies
// below are faithful structural reconstructions: every member read or written
// on cSPCreatureBase is named at its retail offset (unused gaps are explicit
// padding), dispatch into classes whose definition is not part of the slice
// goes through the retail vftable slot (raw slot dispatch is the accepted
// convention for an unknown vtable), and the remaining engine entry points are
// declared with their retail address.
#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed   int   i32;
typedef signed   short i16;

extern "C" double sqrt(double);
extern "C" void*  memcpy(void* dst, const void* src, u32 n);
extern "C" void   operator_delete_array(void* p);          // 0x00f47380

struct Vector3 { float x, y, z; };
struct Matrix3 { u32 m[9]; };

// ------------------------------------------------------------------ vftable
// Dispatch through vftable slot <byteOffset> of an object whose class is not
// known here; <byteOffset> is the retail slot index * 4.
#define VTSLOT(obj, off) ((*(void***)(obj))[(off) / 4])

typedef void     (__thiscall *Fn_void_v)(void*);
typedef void     (__thiscall *Fn_void_vp)(void*, void*);
typedef void     (__thiscall *Fn_void_ppp)(void*, void*, void*, void*);
typedef void     (__thiscall *Fn_void_iii)(void*, i32, i32, i32);
typedef i32      (__thiscall *Fn_i_v)(void*);
typedef i32      (__thiscall *Fn_i_vp)(void*, void*, u32);
typedef float    (__thiscall *Fn_f_v)(void*);
typedef Vector3* (__thiscall *Fn_v3_v)(void*);
typedef void*    (__thiscall *Fn_p_v)(void*);
typedef i32      (__thiscall *Fn_i_ff)(void*, float, float);

// ------------------------------------------------------------- engine types
struct cSPCreatureBase;                       // defined below

struct behavior_stimuli {                     // reached as nSPBehaviorTree + 0x08
    void ClearAll(i32 kind, i32 value);       // 0x00bc98f0
    i32  Play(i32 anim, i32 flags);           // 0x00bc96a0
};

struct nSPBehaviorTree {
    u8               m_pad00[0x08];
    behavior_stimuli m_stimuli;               // +0x08
};

struct cAgentOrderManager {                   // creature + 0xb48
    i32  Activate(i32 a, i32 b, void* sim, float f, void* p, void* sim2); // 0x00bca810
    void DeactivateSlot(i32 slot);                                        // 0x00bca040
};

struct cSpeciesProfile;                       // opaque

struct cGameNounManager {                     // SP::NounManager() (0x00b3d300)
    cSPCreatureBase* GetAvatar();                                         // 0x00b1fdb0
    i32* GetGameDataVector(void* a, void* b, void* c, void* d, void* id); // 0x00b21340
};

// A property slot returned by GetPropertyT (mPl used by Property_GetFloat).
struct Property {
    float* mpData;      // +0x00
    u8     m_pad04[0xc];
    u8     m_flags10;   // +0x10
    u8     m_pad11;
    u16    m_type12;    // +0x12
};

// --------------------------------------------------- SP::cCreatureModeStrategy
struct cCreatureModeStrategy {                // singleton @0x0169e294
    u8    m_pad00[0xb4];
    void* m_pPropOwner;                       // +0xb4  property-list owner
};

// ------------------------------------------------------------ cSPCreatureBase
struct cSPCreatureBase {
    void*  m_vftable;                          // +0x000
    u8     m_pad004[0xc0 - 0x004];
    void*  m_spatial_vftable;                  // +0x0c0  embedded spatial object
    u8     m_pad0c4[0x5a8 - 0x0c4];
    u8     m_contact5a8[0x8];                  // +0x5a8  (arg of FUN_00bfc430)
    u8     m_pad5b0[0xb20 - 0x5b0];
    void*  m_pB20;                             // +0xb20
    u8     m_padB24[0xb28 - 0xb24];
    u8     m_subB28[0x20];                     // +0xb28  (arg of FUN_00b3d4c0)
    cAgentOrderManager* m_pOrderMgr;           // +0xb48
    nSPBehaviorTree*    m_pBehaviorTree;       // +0xb4c
    void*  m_pB54;                             // +0xb54  owner; +0x17c is a list head
    u32    m_flagsB58;                         // +0xb58
    u8     m_padB5c[0xb5e - 0xb5c];
    u8     m_flagB5E;                          // +0xb5e
    u8     m_padB5f[0xe8c - 0xb5f];
    i32    m_combatActiveE8C;                  // +0xe8c
    i32    m_combatNextE90;                    // +0xe90
    float  m_combatStrikeE94;                  // +0xe94
    u32*   m_bitsBeginE98;                     // +0xe98  eastl bit vector
    u32*   m_bitsEndE9C;                       // +0xe9c
    u32*   m_bitsCapEA0;                       // +0xea0
    u8     m_padEA4[0x140c - 0xea4];
    void** m_iterBegin140C;                    // +0x140c
    void** m_iterEnd1410;                      // +0x1410

    i32  CanGrowl();                           // 0x00c0c0e0  (?Flag388@C@@QAE_NXZ)
};

// ------------------------------------------------------- engine entry points
void  FUN_00c0cff0(cSPCreatureBase* self, i32 v);   // 0x00c0cff0  ?cff0@CCB@@QAEXH@Z
void  FUN_00c14750(cSPCreatureBase* self, i32 v);   // 0x00c14750
void  FUN_00bfc430(void* contact, i32 v);           // 0x00bfc430
cGameNounManager* SP_NounManager();                 // 0x00b3d300
cSPCreatureBase*  SP_GetTargetAsCreature(cSPCreatureBase* self); // 0x00c0ee70
cSpeciesProfile*  SP_GetSpeciesProfile(cSPCreatureBase* self);   // 0x00c0bbd0
double SP_GetTime();                                // 0x00c0e480  (static)
i32   SP_EvalContextTargetQuery(void* dst, i32 a, void* node, void* q, i32 b, i32 c); // 0x009b2340
float SP_GetPropertyTFloat(void* obj, u32 hash, float def);  // 0x004e1c70
i32   SP_GetAnimalFromStimulus(i32 stimulus);       // 0x00d99980
float FUN_00d38a30(i32 which, void* p);             // 0x00d38a30
i32   FUN_00d99470(u32 v);                          // 0x00d99470
i32   SP_Proximity(cSPCreatureBase* self, float a, float b, void* p); // 0x00c0d560
float FUN_00d38d80_spare(i32);                      // 0x00d38d80 (see header note)
void  FUN_009360d0(u32 self);                       // 0x009360d0
void  SP_InterruptAnimationWithTarget(cSPCreatureBase* self, u32 anim, void* p, i32 a, i32 b); // 0x00c149c0
i32   FUN_00b3d4c0(void* slot, void* a, void* b);   // 0x00b3d4c0
i32   FUN_00ba3f90(void* p);                        // 0x00ba3f90
void* FUN_00c04590(cSPCreatureBase* self);          // 0x00c04590
void* FUN_00c6acc0(cSPCreatureBase* self);          // 0x00c6acc0
void* FUN_00c0c1a0(cSPCreatureBase* self);          // 0x00c0c1a0
i32   FUN_00c03520(void* item);                     // 0x00c03520
void  FUN_00b3d870();                               // 0x00b3d870
void* FUN_00c9d9e0();                               // 0x00c9d9e0
void* FUN_00d99a10(i32 stimulus);                   // 0x00d99a10
void  SP_AutoRefCountCtor(void* self, void* obj);   // 0x00572660
void  FUN_00e1c7f0(void* container, void* out);     // 0x00e1c7f0
// SP_ReleaseRef releases a reference through vtable slot +4 (see helper below).

// Global data referenced by the routines (addresses are the retail ones).
extern "C" cCreatureModeStrategy* _spInstance_cCreatureModeStrategy = 0;  // 0x0169e294
extern "C" float  DAT_015d9c6c = 0.0f;
extern "C" float  DAT_01473c70 = 0.0f;
extern "C" float  DAT_0147c034 = 0.0f;
extern "C" u32    DAT_01582f00 = 0;
extern "C" u32    DAT_01582f04 = 0;
extern "C" float  DAT_0169f03c = 0.0f;
extern "C" float  DAT_0169f040 = 0.0f;
extern "C" float  DAT_0169f044 = 0.0f;
extern "C" u32    DAT_018c6d19 = 0;

// ===========================================================================
// Small helpers
// ===========================================================================
static Vector3* Spatial_Position(void* spatial) { return ((Fn_v3_v)VTSLOT(spatial, 0x2c))(spatial); }
static float    Spatial_Radius  (void* spatial) { return ((Fn_f_v )VTSLOT(spatial, 0x74))(spatial); }

// The eastl vector buffer allocated by a spatial slot keeps its ref-count in
// the dword immediately preceding the data pointer; delete[] if it hit zero.
static void SpReleaseVectorBuffer(void* pBuffer)
{
    if (pBuffer != 0 && ((i32*)pBuffer)[-1] == 0)
        operator_delete_array(pBuffer);
}

// Drops an AutoRefCount-style reference: dispatch into vtable slot +4.
static void SP_ReleaseRef(void* p)
{
    if (p != 0)
        ((Fn_void_v)VTSLOT(p, 4))(p);
}

static float Property_GetFloat(Property* p)
{
    u16 t = p->m_type12;
    if (t == 0x0d || t == 0x10) {
        if (p->m_flags10 & 0x30)
            return *p->mpData;
        return *(float*)(t != 0 ? (void*)p : 0);
    }
    return DAT_015d9c6c;
}

namespace SP {

// ---------------------------------------------------------------------------
// @ 0x00d8f7a0  SP::LOCATING_CALL_Activate
// ---------------------------------------------------------------------------
void LOCATING_CALL_Activate(cSPCreatureBase* pCreature)
{
    // Query descriptor handed to the creature's spatial slot 0xdc; its first
    // field is an eastl vector buffer allocated by the callee.
    struct QueryArgs {
        void* mpBuffer;              // +0x00
        u8    m_pad04[0x74 - 4];
    } args;

    void* spatial = (void*)&pCreature->m_spatial_vftable;
    ((Fn_void_vp)VTSLOT(spatial, 0xdc))(spatial, &args);
    SpReleaseVectorBuffer(args.mpBuffer);

    FUN_00c0cff0(pCreature, 0);
    FUN_00c14750(pCreature, 0);
    pCreature->m_pBehaviorTree->m_stimuli.ClearAll(0x10, 0);
    pCreature->m_pBehaviorTree->m_stimuli.ClearAll(2, 0);
    pCreature->m_flagsB58 &= 0xffffdfff;
    FUN_00bfc430(pCreature->m_contact5a8, 0);

    pCreature->m_combatActiveE8C = -1;
    pCreature->m_combatNextE90   = -1;
    pCreature->m_combatStrikeE94 = 0.0f;

    // eastl::vector<bool>::erase over [begin,end): the memcpy of 0 bytes is a
    // no-op and the end pointer is reset onto the begin pointer.
    memcpy(pCreature->m_bitsBeginE98, pCreature->m_bitsEndE9C, 0);
    pCreature->m_bitsEndE9C = pCreature->m_bitsBeginE98;

    cSPCreatureBase* pTarget = SP_GetTargetAsCreature(pCreature);
    if (pTarget != 0 && pTarget->m_flagB5E != 0)
        ((Fn_void_iii)VTSLOT(pCreature, 0x84))(pCreature, 0, 0, 0);
}

// ---------------------------------------------------------------------------
// The order descriptor produced by the locating actions.
// ---------------------------------------------------------------------------
struct LocatingAction {
    u32   m_flags00;        // +0x00
    i32   m_target04;       // +0x04  -1, or the creature resolved by the query
    float m_time08;         // +0x08
    u32   m_key0c;          // +0x0c  0x4ec6cd85
    void* mpRef10;          // +0x10  released through vtable slot +4
    void* mpAnimal14;       // +0x14
    i32   m_orderSlot18;    // +0x18
    u8    m_flag1c;         // +0x1c
    u8    m_pad1d[3];
    float m_dist20;         // +0x20
};

// ---------------------------------------------------------------------------
// @ 0x00d8fbe0  SP::LOCATING_CALL_RESPOND_Activate
// ---------------------------------------------------------------------------
i32 LOCATING_CALL_RESPOND_Activate(cSPCreatureBase* pCreature, i32 a1, i32 a2,
                                   cSPCreatureBase* pContext, LocatingAction* pOut)
{
    if (pOut != 0)
        pOut->mpRef10 = 0;
    pOut->m_target04 = -1;

    if (pCreature->m_pB54 != 0) {
        // "mout" context-target query.
        struct ContextQuery { u32 m_d0; u32 m_tag; u32 m_d8; u32 m_dc; } q;
        cSPCreatureBase* pSelf = pCreature;
        q.m_d0  = 0;
        q.m_tag = 0x74756f6d;           // 'm','o','u','t'
        q.m_d8  = 0;
        q.m_dc  = 0;
        void* node = *(void**)((u8*)pCreature->m_pB54 + 0x17c);
        node = *(void**)node;
        if (SP_EvalContextTargetQuery(&pSelf, 1, node, &q, 0, 0) != 0)
            pOut->m_target04 = (i32)pContext;
    }

    if (pOut->m_target04 == -1)
        return 0;

    void* pPropOwner = 0;
    if (_spInstance_cCreatureModeStrategy != 0)
        pPropOwner = _spInstance_cCreatureModeStrategy->m_pPropOwner;
    pOut->m_dist20 = SP_GetPropertyTFloat(pPropOwner, 0x996644a3, 3.0f);

    pOut->m_orderSlot18 = pCreature->m_pOrderMgr->Activate(0, 1, pCreature, 0.0f, 0, 0);

    if (pOut->mpRef10 != 0)
        SP_ReleaseRef(pOut->mpRef10);
    pOut->mpRef10 = 0;
    pOut->m_flag1c = 0;

    {
        cSPCreatureBase* pAvatar = SP_NounManager()->GetAvatar();
        i32 sameSpecies = 0;
        if (pAvatar != 0 && SP_GetSpeciesProfile(pAvatar) == SP_GetSpeciesProfile(pCreature))
            sameSpecies = 1;
        if (sameSpecies || a1 == 1)
            pOut->m_flag1c = 1;
    }

    pOut->m_time08  = (float)SP_GetTime();
    pOut->m_flags00 = 0;
    pOut->m_key0c   = 0x4ec6cd85;

    {
        i32 stimulus = pCreature->m_pBehaviorTree->m_stimuli.Play(0x800, 0);
        cSPCreatureBase* pAnimal = (cSPCreatureBase*)SP_GetAnimalFromStimulus(stimulus);
        if (pAnimal != 0) {
            pOut->mpAnimal14 = pAnimal;
            u8* inner = (u8*)pAnimal->m_pBehaviorTree;
            if (inner != 0 && *(u32*)(inner + 0x1d8) == 0x2d852ed) {
                u8* vec = inner + *(i32*)(inner + 0x1dc) * 0xac + 0x160;
                u32* begin = *(u32**)(vec + 0x24);
                u32* end   = *(u32**)(vec + 0x28);
                u32  cap   = *(u32*)(vec + 0x20);
                if ((u32)(end - begin) < cap) {
                    void* tmp = 0;
                    SP_AutoRefCountCtor(&tmp, pCreature);
                    FUN_00e1c7f0(vec + 0x24, &tmp);
                    if (tmp != 0)
                        SP_ReleaseRef(tmp);
                } else if (((pCreature->m_flagsB58 >> 4) & 1) == 0) {
                    goto out;
                }
                *(double*)(vec + 0x38) = SP_GetTime();
                pOut->m_flag1c = 1;
            }
        }
    }
out:
    return pOut->m_flag1c & 0xff;
}

// ---------------------------------------------------------------------------
// The growl-timer action descriptor and its input pair.
// ---------------------------------------------------------------------------
struct GrowlTimer {
    float m_out00;         // +0x00  returned countdown (seconds)
    float m_wait04;        // +0x04  countdown populated from the property list
    void* m_pObj08;        // +0x08  tracked object (AutoRefCount slot)
    u8    m_flag0c;        // +0x0c
    u8    m_flag0d;        // +0x0d
    u8    m_flag0e;        // +0x0e
    u8    m_pad0f;
    i32   m_target10;      // +0x10
};

struct GrowlInput {
    u8     m_pad00[0x04];
    void*  m_pA04;         // +0x04
    void*  m_pB08;         // +0x08
    u8     m_pad0c[0x18 - 0xc];
    i32    m_v18;          // +0x18
};

// ---------------------------------------------------------------------------
// @ 0x00d8fdf0  SP::GROWL_TIMER_Activate
// ---------------------------------------------------------------------------
i32 GROWL_TIMER_Activate(cSPCreatureBase* pSelf, i32 a1, i32 a2, i32 a3,
                         GrowlTimer* pTimer, GrowlInput* pInput, float* pfOut)
{
    if (pTimer != 0)
        pTimer->m_pObj08 = 0;

    // Countdown seed read out of the creature-mode strategy property list.
    float seed = 10.0f;
    if (_spInstance_cCreatureModeStrategy != 0 &&
        _spInstance_cCreatureModeStrategy->m_pPropOwner != 0) {
        Property* pProp = 0;
        void* owner = _spInstance_cCreatureModeStrategy->m_pPropOwner;
        if (((Fn_i_vp)VTSLOT(owner, 0x24))(owner, &pProp, 0x6848e35e))
            seed = Property_GetFloat(pProp);
    }

    pTimer->m_wait04   = seed;
    pTimer->m_flag0c   = 0;
    pTimer->m_flag0d   = 0;
    pTimer->m_target10 = 0;

    // Optional target identifiers from the input pair.
    i32 idA = 0;
    void* pB = 0;
    if (pInput != 0) {
        if (pInput->m_pA04 != 0)
            idA = ((Fn_i_v)(VTSLOT(pInput->m_pA04, 0x5c)))(pInput->m_pA04);
        if (pInput->m_pB08 != 0)
            pB = ((Fn_p_v)(VTSLOT(pInput->m_pB08, 0xc)))  (pInput->m_pB08);
    }

    // Swap the tracked object.
    {
        void* pOld = pTimer->m_pObj08;
        if (pB != pOld) {
            if (pB != 0)
                ((Fn_void_v)VTSLOT(pB, 0xbc))(pB);
            pTimer->m_pObj08 = pB;
            if (pOld != 0)
                ((Fn_void_v)VTSLOT(pOld, 0xc0))(pOld);
        }
    }

    pTimer->m_flag0e = (u8)(pInput != 0 && pInput->m_v18 == 1);

    float f1 = FUN_00d38a30(1, pSelf);
    float f2 = FUN_00d38a30(2, pSelf);
    (void)f1; (void)f2;

    if (FUN_00d99470((u32)idA) == 0)
        return 0;

    // Distance between the two creatures' positions minus their radii.
    Vector3* pA = Spatial_Position((void*)&pSelf->m_spatial_vftable);
    Vector3* pB2 = Spatial_Position((void*)pB);
    float dx = pB2->x - pA->x;
    float dy = pB2->y - pA->y;
    float dz = pB2->z - pA->z;
    float dist = (float)sqrt((double)(dx * dx + dy * dy + dz * dz));
    float range = dist - (Spatial_Radius((void*)&pSelf->m_spatial_vftable) +
                          Spatial_Radius((void*)pB));
    if (range < 0.0f)
        range = 0.0f;

    if (!SP_Proximity(pSelf, f1, range, pB)) {
        if (!((Fn_i_ff)VTSLOT(pSelf, 0xc0))(pSelf, f2, range))
            return 0;
    }

    // Size query on the target's behaviour-tree payload ("tMineState").
    {
        u8* inner = (u8*)pSelf->m_pBehaviorTree;
        if (inner != 0 && *(u32*)(inner + 0x1d8) == 0x2d852ed) {
            u8* vec = inner + *(i32*)(inner + 0x1dc) * 0xac + 0x160;
            u32* begin = *(u32**)(vec + 0x44);
            u32* end   = *(u32**)(vec + 0x48);
            u32  cap   = *(u32*)(vec + 0x40);
            if ((u32)(end - begin) >= cap)
                return 0;

            void* tmp = 0;
            SP_AutoRefCountCtor(&tmp, pSelf);
            FUN_00e1c7f0(vec + 0x44, &tmp);
            if (tmp != 0)
                SP_ReleaseRef(tmp);
            pTimer->m_flag0c = 1;

            float thresh = SP_GetPropertyTFloat(_spInstance_cCreatureModeStrategy->m_pPropOwner,
                                                0xd5f935bc, 0.0f);
            if (!pSelf->CanGrowl() && FUN_00d38a30(2, pSelf) < thresh)
                pTimer->m_flag0d = 1;
        }
    }

    ((Fn_void_iii)VTSLOT(pSelf, 0x84))(pSelf, (i32)((u8*)pSelf + 0x5a8), 1, 0);
    SP_InterruptAnimationWithTarget(pSelf, 0x2481dfc, pB, -1, -1);

    {
        struct XformArgs { void* mpBuffer; u8 m_pad[0x74 - 4]; } xa;
        void* spatial = (void*)&pSelf->m_spatial_vftable;
        ((Fn_void_vp)VTSLOT(spatial, 0xdc))(spatial, &xa);
        SpReleaseVectorBuffer(xa.mpBuffer);
    }

    cSPCreatureBase* pTarget = SP_GetTargetAsCreature(pSelf);
    if (pSelf == 0 && pTarget != 0) {
        FUN_00b3d4c0((u8*)pTarget + 0xb28, pTarget, 0);
        if (FUN_00ba3f90((u8*)pTarget + 0xb28) == 5)
            *pfOut = (float)DAT_01582f04;
        else
            *pfOut = (float)DAT_01582f00;

        void* gd = FUN_00c04590(pSelf);
        if (*(i32*)((u8*)gd + 0x164) == 0 && *(void**)((u8*)gd + 0x168) != (void*)((u8*)gd + 0x168) &&
            !(*pfOut > 1.5258789e-05f)) {
            if (DAT_01582f00 == 0)
                *pfOut = 5.0f;
            else
                *pfOut = (float)DAT_01582f00;
        }
    } else {
        *pfOut = (float)(i32)pSelf;
    }

    return SP_GetTargetAsCreature(pSelf) != 0;
}

// ---------------------------------------------------------------------------
// A creature-like query result returned by the delta/web iterators.
// ---------------------------------------------------------------------------
struct cGrowlTarget {
    void* m_vftable;          // +0x000
    u8    m_pad004[0x10 - 0x4];
    void* m_pObserver10;      // +0x010
    u8    m_pad14[0x120 - 0x14];
    void* m_pSpatial120;      // +0x120
};

// ---------------------------------------------------------------------------
// @ 0x00d90320  SP:Creature_GrowlTargetInRange  (symbol unnamed in retail)
// ---------------------------------------------------------------------------
i32 Creature_GrowlTargetInRange(cSPCreatureBase* pSelf, float range)
{
    i32* pVec = SP_NounManager()->GetGameDataVector(
                    (void*)FUN_00c03520, (void*)FUN_00b3d870, (void*)FUN_00c9d9e0,
                    (void*)FUN_00c03520, (void*)&DAT_018c6d19);
    if (pVec[1] == pVec[2])
        return 0;

    Vector3* pSelfPos = Spatial_Position((void*)&pSelf->m_spatial_vftable);
    void** itEnd   = pSelf->m_iterEnd1410;
    void** itBegin = pSelf->m_iterBegin140C;
    if (itBegin == itEnd)
        return 0;

    if (FUN_00c03520(*itBegin) == 0)
        FUN_00b3d870();
    if (itBegin == itEnd)
        return 0;

    for (;;) {
        void* pItem = *itBegin;
        cGrowlTarget* pTarget = (cGrowlTarget*)*(void**)((u8*)pItem + 0x10);
        if (pTarget != 0) {
            void* id = ((Fn_v3_v)VTSLOT(pTarget, 0x20))(pTarget);
            cGrowlTarget* pResolved;
            if (id == (void*)0x018c8f0c)
                pResolved = (cGrowlTarget*)FUN_00c9d9e0();
            else if (id == (void*)0x1e4daae)
                pResolved = (cGrowlTarget*)((Fn_v3_v)VTSLOT(pTarget, 0x20))(pTarget);
            else
                goto advance;

            if (pResolved != 0) {
                Vector3* pPos = Spatial_Position(pResolved->m_pSpatial120);
                float dx = pSelfPos->x - pPos->x;
                float dy = pSelfPos->y - pPos->y;
                float dz = pSelfPos->z - pPos->z;
                float r  = Spatial_Radius(pResolved->m_pSpatial120);
                if (dx * dx + dy * dy + dz * dz < r * r) {
                    i32 stim = pSelf->m_pBehaviorTree->m_stimuli.Play(0, 0x4000);
                    void* pAnim = FUN_00d99a10(stim);
                    if (pAnim != 0) {
                        void* a = ((Fn_p_v)VTSLOT(pAnim, 0xc))(pAnim);
                        i32 b = ((Fn_i_v)VTSLOT(a, 0x4c))(a);
                        i32 c = ((Fn_i_v)VTSLOT(pTarget, 0x4c))(pTarget);
                        if (b == c)
                            break;
                    }
                    void* pOwner = FUN_00c04590(pSelf);
                    if (pOwner != 0) {
                        Vector3* q1 = Spatial_Position(pResolved->m_pSpatial120);
                        Vector3* q2 = (Vector3*)FUN_00c6acc0(pSelf);
                        float ex = q2->x - q1->x;
                        float ey = q2->y - q1->y;
                        float ez = q2->z - q1->z;
                        float lim = Spatial_Radius(pResolved->m_pSpatial120);
                        void* pm = FUN_00c0c1a0(pSelf);
                        float scale;
                        if (pm == 0)
                            scale = 1.25f;
                        else
                            scale = *(float*)((u8*)pm + 900);
                        if (!pSelf->CanGrowl()) {
                            float lim2 = (float)sqrt((double)((float)(*(i32*)((u8*)FUN_00c04590(pSelf) + 0xf4) *
                                                                 (lim * scale)) * (lim * scale)));
                            if (ex * ex + ey * ey + ez * ez > (lim + lim2) * (lim + lim2))
                                ;
                        }
                        if (ex * ex + ey * ey + ez * ez <= (lim + 0.0f) * (lim + 0.0f))
                            return 0;
                    }
                    return 1;
                }
            }
        }
    advance:
        do {
            itBegin++;
            if (itBegin == itEnd)
                return 0;
        } while (FUN_00c03520(*itBegin) == 0);
        if (itBegin == itEnd)
            return 0;
    }
    return 0;
}

}  // namespace SP