// Slice s00d8d820 -- SP::LOUNGE_memory_block::JoinGroup (0x00d8d820) and
// SP::LOUNGE_Activate (0x00d8db70): bind a creature to a guard/lounge group and drive it.
//
// Flags /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc), same family as the sibling
// Simulator/UI slices.
//
// Contents:
//   d8d820  SP::LOUNGE_memory_block::JoinGroup -- run the order manager, then (when the
//           order source is exhausted) look up the species archetype scalar, compute a
//           radius from the locomotive slot 0x74, resolve the target position (a group
//           tag drives an order lookup or a nearby-noun position lookup), push the values
//           onto the group's text-run state, bind the callback and refresh the bound
//           game-data object, then pick a random facing speed and register the move.
//   d8db70  SP::LOUNGE_Activate -- set the only-guard flag, pick the guard/lounge group
//           through FindGuardOrLoungeGroup, join it and drive the creature to the block
//           position (facing variant when the group tag matches).
//
// Notes / decisions:
//  * ABI: the thiscall originals are reproduced as `__fastcall(T* self, void* edx, ...)`
//    free functions (ecx = self, edx scratch, remaining args on the stack, callee cleans).
//    External thiscall callees are reached through small struct types (ecx = the receiver)
//    or virtual interfaces whose declaration order equals the vtable order.
//  * Field offsets use named members on typed structs only (no raw-offset pointer casts).
//  * The heavy x87 in JoinGroup comes from `double` intermediates in the original (fild /
//    fmul / fsqrt / fld qword); the reconstruction keeps the same double/float split.
//
// Result (this session): no function is byte-exact (JoinGroup diffs 708/835, LOUNGE_Activate
// 258/324 - register-allocation and x87-scheduling differences dominate; the 5-round chk.py
// compile cap was reached). The equivalence gate ran once at the end: LOUNGE_Activate is WEAK
// (no mismatch), JoinGroup is FAIL (the random-LCG state at 0x01601760 ends different), so
// JoinGroup is recorded as approximate in partial.txt. See manifest.txt / nonmatching.txt /
// partial.txt. Every function below is a complete definition.
#include "types.h"
#include <math.h>
typedef unsigned int uint;
typedef unsigned int uintptr_t;

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8

struct float3 { float x, y, z; };

// ---------------------------------------------------------------------------------------------
// Interfaces / object layouts.
// ---------------------------------------------------------------------------------------------

// The locomotive sub-object at creature+0xc0; slots used by this slice.
struct Loco {
    PV8 PV2 PV                                   // 0x00..0x28
    virtual float3* Slot2c();                    // 0x2c  (current position)
    PV16 PV                                      // 0x30..0x70
    virtual float   Slot74();                    // 0x74  (radius / scalar)
};

// Ref-counted base with AddRef at slot 0 and Release at slot 4.
struct VtGrp {
    virtual void AddRef();                       // 0x00
    virtual void Release();                      // 0x04
};

// SP::LOUNGE_memory_block (the thiscall receiver).
struct LOUNGE_memory_block {
    int32_t mState;                              // +0x00
    float3  mMyPosition;                         // +0x04
    void*   mAnimHandle;                         // +0x10
    uint8_t mbOnlyGuard;                         // +0x14
};

// The group returned by FindGuardOrLoungeGroup / carried by the text-run iterator.
struct TextRunIterator;
struct LoungeGroup {
    uint8_t  pad00[8];
    uint32_t mTag;                               // +0x08
    uint8_t  pad0c[0x18 - 0x0c];
    int32_t  mInt18;                             // +0x18
    uint8_t  pad1c[0x1a0 - 0x1c];
    void*    mpRef;                              // +0x1a0 (ref-counted)
    uint8_t  pad1a4[0x224 - 0x1a4];
    void*    mpCallback;                         // +0x224
    void  FUN_00bc9bf0(int a, int b);            // 0x00bc9bf0
    void  FUN_00bc9b80(int a, const float3* v);  // 0x00bc9b80
    void  FUN_00bc9bc0(int a, float v);          // 0x00bc9bc0
    float FUN_00bc9bb0(int a);                   // 0x00bc9bb0
    void* FUN_00bc9b70(int a);                   // 0x00bc9b70
};
struct TextRunIterator {
    bool AtBegin();                              // 0x00bc9b50
};

// The creature's game-data object reached through FUN_00c04590.
struct GameData {
    virtual void AddRef();                                            // 0x00
    virtual void Release();                                           // 0x04
    uint8_t  pad04[0x88 - 0x04];
    void*    mp88;                                                    // +0x88
    uint8_t  pad8c[0xf0 - 0x8c];
    void*    mpF0;                                                    // +0xf0
    uint8_t  padf4[0x15c - 0xf4];
    int32_t  m15c;                                                    // +0x15c
    void*    mp160;                                                   // +0x160
    int   FUN_00c6b8e0(float dist, const float3* pos);                // 0x00c6b8e0
    float3* GetPosition();                                           // 0x00c6acc0
};

struct Archetype {
    uint8_t pad00[0x37c];
    float   m37c;                                // +0x37c
    float   m380;                                // +0x380
    float   m384;                                // +0x384
};

struct SpeciesMgr {
    Archetype* GetSpeciesArchetype(void* a, void* b);   // 0x004e0050
};

struct OrderMgr;
struct cSPCreatureBase {
    uint8_t   pad00[0xc0];
    Loco      mLoco;                             // +0xc0 (vptr only, 4 bytes)
    uint8_t   padC4[0xb4c - 0xc4];
    OrderMgr* mpOrder;                           // +0xb4c
    GameData* FUN_00c04590();                    // 0x00c04590
    Archetype* FUN_00c0c1a0();                   // 0x00c0c1a0
    void      MoveToPointAtSpeed(int a, const float3* pos, float b, float c);       // 0x00c1c1d0
    void      MoveToPointAndFacingAtSpeed(int a, const float3* pos, const float3* d,
                                          float b, float c);                        // 0x00c1c5c0
};

struct OrderMgr {
    void FUN_00bcb480(LoungeGroup* g, cSPCreatureBase* c, LOUNGE_memory_block* t, int z); // 0x00bcb480
    bool IsSourceAtEnd();                        // 0x00bca280
};
struct OrderMgr2 {
    void FUN_00bc97f0(int a, int b, float f, int c);    // 0x00bc97f0
};

// cPlanetModel returned by SP::PlanetModel (variadic so both arities in the original lower).
struct PlanetObj {
    void    MakeRandomWorldPosition(const float3* out, void* a, float b, float c);  // 0x00b81780
    float3* FUN_00b81630(const float3* a, const float3* b);                          // 0x00b81630
};

// Global random source at 0x01601760.
struct RandomLCG {
    double RandomDoubleUniform();                // 0x009360d0
};

// ---------------------------------------------------------------------------------------------
// External callees (undefined externs; only the call shape matters).
// ---------------------------------------------------------------------------------------------
void*  __cdecl FUN_00401090();                          // 0x00401090  (setting point lookup)
void*  __cdecl FUN_00d82040(void* creature, int onlyGuard); // 0x00d82040  FindGuardOrLoungeGroup
PlanetObj* __cdecl FUN_00b3d350(const float3* a, ...);  // 0x00b3d350  (variadic PlanetModel)
float  __cdecl FUN_00572a10(float lo, float hi);        // 0x00572a10  RandomFloatRange
float3* __cdecl FUN_00449c20(float3* out, const float3* in); // 0x00449c20  normalized_safe
void   __cdecl FUN_00d88c10();                         // callback stored at group+0x224

extern const float  gOneF_13f08e4;         // 0x013f08e4 (1.25f)
extern const double gOneD_13f1688;         // 0x013f1688 (1.0)
extern const double gSixtyD_140eb98;       // 0x0140eb98 (60.0)
extern const double gOneTwentyD_147c088;   // 0x0147c088 (120.0)
extern const float  gHalfF_1471064;        // 0x01471064 (0.5f)
extern RandomLCG    gRandomLCG_1601760;    // 0x01601760

// ---------------------------------------------------------------------------------------------
// @ 0x00d8d820
// ---------------------------------------------------------------------------------------------
bool __fastcall FUN_00d8d820(LOUNGE_memory_block* self, void* edx,
                             cSPCreatureBase* creature, LoungeGroup* group)
{
    (void)edx;
    OrderMgr* om = creature->mpOrder;
    om->FUN_00bcb480(group, creature, self, 0);
    if (om->IsSourceAtEnd()) {
        GameData* gd = creature->FUN_00c04590();
        void* v6 = gd->mpF0;
        GameData* gd2 = creature->FUN_00c04590();
        void* v14 = gd2->mp88;
        SpeciesMgr* sm = (SpeciesMgr*)FUN_00401090();
        Archetype* arch = sm->GetSpeciesArchetype(v14, v6);
        if (arch == 0)
            arch = creature->FUN_00c0c1a0();
        float scale = arch ? arch->m384 : gOneF_13f08e4;
        Loco* loco = &creature->mLoco;
        float localZ = 0.0f;
        float rf = loco->Slot74() * scale;
        float dist = sqrtf((float)group->mInt18 * rf * rf);
        float3 pos = *loco->Slot2c();
        GameData* gd3 = creature->FUN_00c04590();
        float3 p2;
        int indx;
        if (group->mTag == 0x4472a59) {
            p2 = *loco->Slot2c();
            indx = gd3->FUN_00c6b8e0(dist, &p2);
            if (indx == -1)
                return false;
        } else {
            p2 = *gd3->GetPosition();
            void* g160 = gd3->mp160;
            indx = -1;
            if (g160 != 0) {
                float a1 = loco->Slot74();
                float a2 = ((Loco*)((char*)g160 + 0x34))->Slot74();
                localZ = a2 + a1;
                float rf1 = loco->Slot74() * scale;
                dist = sqrtf(localZ * localZ + (float)group->mInt18 * rf1 * rf1);
            }
        }
        group->FUN_00bc9bf0(3, indx);
        group->FUN_00bc9b80(0, &p2);
        group->FUN_00bc9bc0(4, dist);
        group->FUN_00bc9bc0(5, localZ);
        group->mpCallback = (void*)&FUN_00d88c10;
        GameData* gd4 = creature->FUN_00c04590();
        void* old = group->mpRef;
        if (gd4 != old) {
            if (gd4) gd4->AddRef();
            group->mpRef = gd4;
            if (old) ((VtGrp*)old)->Release();
        }
    }
    float f4 = group->FUN_00bc9bb0(4);
    float f5 = group->FUN_00bc9bb0(5);
    void* u = group->FUN_00bc9b70(0);
    float total = f4 + f5;
    float3 tmp;
    PlanetObj* pm = FUN_00b3d350(&tmp, u, f4, total);
    pm->MakeRandomWorldPosition(&tmp, u, f4, total);
    GameData* gd5 = creature->FUN_00c04590();
    if (gd5->m15c == 8) {
        float3 a, b;
        PlanetObj* pm2 = FUN_00b3d350(&a, &b);
        float3* v = pm2->FUN_00b81630(&a, &b);
        self->mMyPosition.x = v->x;
        self->mMyPosition.y = v->y;
        self->mMyPosition.z = v->z;
    } else {
        self->mMyPosition.x = tmp.x;
        self->mMyPosition.y = tmp.y;
        self->mMyPosition.z = tmp.z;
    }
    self->mState = 0;
    Archetype* alt2 = creature->FUN_00c0c1a0();
    float f;
    if (alt2 == 0) {
        double rnd = gRandomLCG_1601760.RandomDoubleUniform();
        double v = (rnd + gOneD_13f1688) * gSixtyD_140eb98;
        if (v >= gOneTwentyD_147c088)
            f = (float)gOneTwentyD_147c088;
        else if (v >= gSixtyD_140eb98)
            f = (float)v;
        else
            f = (float)gSixtyD_140eb98;
    } else {
        f = FUN_00572a10(alt2->m37c, alt2->m380);
    }
    ((OrderMgr2*)((char*)om + 8))->FUN_00bc97f0(0x40000000, 0, f, 0);
    return true;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d8db70
// ---------------------------------------------------------------------------------------------
bool __cdecl FUN_00d8db70(void* p1, void* p2, void* p3, void* p4,
                          int onlyGuard, LOUNGE_memory_block* block, void** iter)
{
    (void)p2; (void)p3; (void)p4;
    void* g = *iter;
    block->mbOnlyGuard = (onlyGuard != 0);
    if (!(g != 0 && !((TextRunIterator*)g)->AtBegin()))
        g = FUN_00d82040(p1, block->mbOnlyGuard);
    if (g != 0) {
        if (FUN_00d8d820(block, 0, (cSPCreatureBase*)p1, (LoungeGroup*)g)) {
            block->mAnimHandle = 0;
            cSPCreatureBase* cr = (cSPCreatureBase*)p1;
            Loco* loco = &cr->mLoco;
            if (((LoungeGroup*)g)->mTag == 0x4472a59) {
                GameData* gd = cr->FUN_00c04590();
                float3 p = *gd->GetPosition();
                float3 d;
                d.x = block->mMyPosition.x - p.x;
                d.y = block->mMyPosition.y - p.y;
                d.z = block->mMyPosition.z - p.z;
                float r = loco->Slot74();
                float speed = r * gHalfF_1471064;
                float3 out;
                float3* n = FUN_00449c20(&out, &d);
                cr->MoveToPointAndFacingAtSpeed(2, &block->mMyPosition, n, speed, r);
                return true;
            }
            float r = loco->Slot74();
            float speed = r * gHalfF_1471064;
            cr->MoveToPointAtSpeed(2, &block->mMyPosition, speed, r);
            return true;
        }
    }
    return false;
}