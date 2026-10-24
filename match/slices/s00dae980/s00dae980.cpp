// Slice s00dae980 -- SP behaviour-tree tribe/agent action nodes and the sparse
// per-agent slot container they use.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <math.h>

#define PV(n) virtual void v##n();

struct Vec3 { float x, y, z; };

struct PtrList { int* mpBegin; int* mpEnd; };

// generic refcounted interface object; vtable slot n lives at byte offset 4*n
struct GObj {
    virtual void Slot0();                    // 0x00
    virtual void Release();                  // 0x04
    PV(2) PV(3) PV(4)
    virtual void Slot5();                    // 0x14
    PV(6)
    virtual int32_t Slot7();                 // 0x1c
    PV(8) PV(9)
    virtual GObj* Slot10();                  // 0x28
    virtual Vec3* Slot11();                  // 0x2c
    PV(12)
    virtual void Slot13();                   // 0x34
    PV(14) PV(15) PV(16) PV(17) PV(18)
    virtual void* Slot19();                   // 0x4c
    PV(20) PV(21)
    virtual uint8_t Slot22();                // 0x58
    virtual GObj* Slot23(int);               // 0x5c
    virtual float Slot24f();                 // 0x60
    PV(25) PV(26) PV(27) PV(28)
    virtual float Slot29f();                 // 0x74
    PV(30) PV(31) PV(32)
    virtual void Slot33(void*, int, int);    // 0x84
    PV(34) PV(35)
    virtual PtrList* Slot36();               // 0x90
    PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44)
    virtual int32_t Slot45(int);             // 0xb4
    virtual GObj* Slot46(int);               // 0xb8
    PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56)
    PV(57) PV(58)
    virtual void Slot59();                   // 0xec

    void Func_c17350(int, int);
    PtrList* FUN_00c420d0();                 // 0x00c420d0 (thiscall, non-virtual)
    uint8_t  IsNearGoal();                   // 0x00c42e20 (thiscall, non-virtual)
};

// sub-object at cc+0x5a8 (a loco/attachment host whose slot 22 returns a float)
struct Sub5 {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
    virtual float Slot22f();                 // 0x58
};

// one 0x250-byte slot of the sparse agent table
struct VObj0 { virtual void Slot0(int); };   // slot 0 takes one argument here

struct Slot250 {
    int32_t mFlags;                          // +0x000
    VObj0   mObj;                            // +0x004
    char    pad008[0x250 - 0x008];
};

// the sparse agent-slot table: a pointer to the slot storage at +0
struct SlotTable {
    int* mpBase;                             // +0x000
    int  FUN_00daed20(int idx);
};

struct Holder {
    void* FirstPending();                    // 0x00bca2c0 (thiscall)
    char  pad000[0x600];
    void* mp600;                             // +0x600 (tribe behaviour-tree node state)
};

struct TribeObj;

// sub-object at cc+0x34 (interaction / command slot)
struct Sub34 {
    void* FUN_00cee330();                    // 0x00cee330 (thiscall)
};

// cSPCreatureBase / cSPCreatureCitizen
struct CC {
    GObj    base;                            // +0x000
    char    pad004[0x034 - 0x004];
    Sub34   m34;                             // +0x034
    char    pad038[0x058 - 0x038];
    GObj    m58;                             // +0x058
    char    pad05c[0x0c0 - 0x05c];
    GObj    mC0;                             // +0x0c0
    char    pad0c4[0x120 - 0x0c4];
    GObj    m120;                            // +0x120
    char    pad124[0x556 - 0x124];
    uint8_t m556;                            // +0x556
    char    pad557[0x5a8 - 0x557];
    uint8_t m5a8[0x5e0 - 0x5a8];
    float   m5e0;                            // +0x5e0
    char    pad5e4[0xb20 - 0x5e4];
    void*   mpB20;                           // +0xb20
    char    padB24[0xb4c - 0xb24];
    Holder* mpB4C;                           // +0xb4c
    char    padB50[0xb58 - 0xb50];
    uint32_t mFlagsB58;                      // +0xb58
    uint8_t mByteB5c;                        // +0xb5c
    uint8_t padB5d;
    uint8_t mByteB5e;                        // +0xb5e

    bool AnimationFinished(int);             // 0x00c12400
    int32_t InterruptAnimation(int, int, int);// 0x00c12310
    void PlayAnimation(int, int, int);
    void Func_c14750(int);
    void RebuildCitizenOrderListDefault();   // 0x00c26c80
    int  FUN_00c22dc0();                     // 0x00c22dc0
    bool IsLeader();                         // 0x00c232d0
    TribeObj* GetTribe();                    // 0x00c22f50
    void MoveToPointAtSpeed(int, Vec3*, float, float);   // 0x00c1c1d0
};

// node state blocks passed as the 6th argument
struct State780 { GObj* mp0; };              // +0x00
struct State270 { GObj* mp0; GObj* mp4; };
struct S5 { char pad00[4]; uint8_t mb04; char pad05[0x0c - 0x05]; GObj* mp0c; };

// 5-dword out block written by the order scan
struct Out { int32_t f0, f4, f8, fC, f10; };

// behaviour-tree action payload (7th argument of the Activate nodes)
struct A6 {
    char     pad00[4];
    GObj*    mp4;                            // +0x04
    char     pad08[0x18 - 0x08];
    uint32_t m18;                            // +0x18
};

// handle + cached squared distance used by TRIBE_COWER
struct ActState { GObj* mp0; float mf4; };   // +0x00, +0x04

// entry of the sparse rehash table
struct HNode {
    uint32_t mKey;                           // +0x00
    char     pad04[0x10 - 0x04];
    HNode*   mpNext;                         // +0x10
};

// sparse hash table with a free-list for its bucket arrays
struct HTable2 {
    char      pad000[4];
    HNode**   mpBuckets;                     // +0x04
    uint32_t  mnBuckets;                     // +0x08
    char      pad00c[0x1c - 0x0c];
    HNode**   mp1c;                          // +0x1c (free list head)
    char      pad020[0x24 - 0x20];
    HNode**   mp24;                          // +0x24 (pool begin)
    HNode**   mp28;                          // +0x28 (pool end)
    char      pad02c[0x30 - 0x2c];
    HNode**   mp30;                          // +0x30 (static/inline buckets)

    HNode** FUN_00daed90(uint32_t n);        // 0x00daed90 (thiscall)
    void    FUN_00daee00(uint32_t n);        // rehash
};

void operator_delete_array(void*);           // 0x00f47380 (cdecl)
uint32_t FUN_00da6270(CC*, int);             // 0x00da6270 (cdecl)

// ===========================================================================
// @ 0x00daee00
// ===========================================================================
void HTable2::FUN_00daee00(uint32_t n)
{
    HNode** newbuckets = FUN_00daed90(n);
    uint32_t i = 0;
    if (mnBuckets != 0) {
        do {
            HNode* node = mpBuckets[i];
            while (node != 0) {
                uint32_t h = node->mKey % n;
                mpBuckets[i] = node->mpNext;
                node->mpNext = newbuckets[h];
                newbuckets[h] = node;
                node = mpBuckets[i];
            }
            ++i;
        } while (i < mnBuckets);
    }
    HNode** old = mpBuckets;
    if (mnBuckets > 1 && old != mp30) {
        if (old >= mp24 && old < mp28) {
            *(void**)old = mp1c;
            mp1c = old;
            mpBuckets = newbuckets;
            mnBuckets = n;
            return;
        }
        operator_delete_array(old);
    }
    mpBuckets = newbuckets;
    mnBuckets = n;
}

// ===========================================================================
// @ 0x00daed20
// ===========================================================================
int SlotTable::FUN_00daed20(int idx)
{
    int* base = mpBase;
    uint32_t* p = (uint32_t*)((char*)base + idx * 0x250);
    uint32_t u = *p;
    do {
        if (u >> 0x1e & 1)
            return 0x3fffffff;
        u = p[0x94];
        p += 0x94;
        ++idx;
    } while (u >> 0x1f & 1);
    return idx;
}

// ===========================================================================
// @ 0x00daeea0
// ===========================================================================
void __stdcall FUN_00daeea0(Slot250* a, Slot250* b)
{
    for (; a < b; a = (Slot250*)((char*)a + 0x250)) {
        if ((((uint32_t)a->mFlags >> 31) & 1) == 0)
            a->mObj.Slot0(0);
    }
}

// ===========================================================================
// @ 0x00daf6b0
// ===========================================================================
void __cdecl FUN_00daf6b0(CC* self, int a1, int a2, int a3, int a4, void** p)
{
    self->Func_c14750(0);
    if (p != 0 && *p != 0)
        ((GObj*)*p)->Release();
}

// ===========================================================================
// @ 0x00daf7f0
// ===========================================================================
void __cdecl FUN_00daf7f0(CC* self, int a1, int a2, int a3, int a4, S5* a5)
{
    if (a5->mb04 != 0)
        self->PlayAnimation(0x2796b28, 1, -1);
    GObj* o = a5->mp0c;
    if (o != 0)
        o->Release();
}

// ===========================================================================
// @ 0x00daf780
// ===========================================================================
void __cdecl FUN_00daf780(CC* self, int a1, int a2, int a3, int a4, State780* a5)
{
    GObj* o = a5->mp0;
    if (o != 0)
        o->Func_c17350(0x562d214, 0);
    self->base.Slot33(0, 0, 0);
    self->mC0.Slot59();
    if (self->mByteB5e == 0)
        self->Func_c14750(0);
    GObj* o2 = a5->mp0;
    if (o2 != 0)
        o2->Release();
}

// ===========================================================================
// @ 0x00daf270
// ===========================================================================
void __cdecl FUN_00daf270(CC* self, int a1, int a2, int a3, int a4, State270* a5)
{
    if (a5->mp0 != 0) {
        GObj* p = self->m58.Slot10();
        if (p != 0) {
            int32_t x = a5->mp0->Slot7();
            if (p->Slot7() == x)
                self->m58.Slot13();
        }
    }
    GObj* p4 = a5->mp4;
    if (p4 != 0)
        p4->Slot5();
    if (a5->mp0 != 0)
        a5->mp0->Release();
}

// ===========================================================================
// @ 0x00daeca0
// ===========================================================================
uint8_t __cdecl FUN_00daeca0(CC* self, int a1, int a2, int a3, int a4, Out* a5)
{
    int* p = (int*)self->mpB4C->FirstPending();
    if (p != 0 && *p == 0x16) {
        char* q = (char*)p + 0x39;
        uint16_t s = *(uint16_t*)(q + 0x12);
        int32_t* src;
        if (s == 0x0a || s == 0x10) {
            if ((*(uint8_t*)(q + 0x10) & 0x30) != 0)
                src = *(int32_t**)q;
            else
                src = (int32_t*)(s ? q : 0);
        } else {
            src = (int32_t*)0x15d1164;
        }
        int32_t v = *src;
        a5->f0 = v;
        a5->f4 = 0;
        a5->f8 = 0;
        a5->fC = 0;
        a5->f10 = -1;
        return (uint8_t)(self->base.Slot45(v) != 0 ? 1 : 0);
    }
    return 0;
}

// ===========================================================================
// @ 0x00daf620
// ===========================================================================
bool __cdecl TRIBE_COWER_Activate(CC* self, int a1, int a2, int a3, int a4,
                                  ActState* a5, A6* a6)
{
    if (a5 != 0)
        a5->mp0 = 0;
    GObj* m = a6->mp4;
    GObj* o;
    if (m != 0)
        o = m->Slot23(0xb033b403);
    else
        o = 0;
    GObj* old = a5->mp0;
    if (o != old) {
        if (o != 0)
            o->Slot0();
        a5->mp0 = o;
        if (old != 0)
            old->Release();
    }
    float f = (float)a6->m18;
    a5->mf4 = f * f;
    self->InterruptAnimation(0x2481dce, -1, 0);
    return a5->mp0 != 0;
}

// ===========================================================================
// @ 0x00daf6e0
// ===========================================================================
uint8_t __cdecl FUN_00daf6e0(CC* self, int a1, int a2, int a3, int a4,
                             GObj** a5, A6* a6)
{
    if (a5 != 0)
        *a5 = 0;
    GObj* m = a6->mp4;
    GObj* o;
    if (m != 0)
        o = m->Slot23(0xce9f6639);
    else
        o = 0;
    GObj* old = *a5;
    if (o != old) {
        if (o != 0)
            o->Slot0();
        *a5 = o;
        if (old != 0)
            old->Release();
    }
    if (*a5 != 0) {
        self->RebuildCitizenOrderListDefault();
        GObj* q = *a5;
        void* arg = (q != 0) ? (void*)((char*)q + 0x5a8) : 0;
        self->base.Slot33(arg, 1, 4);
        return 1;
    }
    return (uint8_t)FUN_00da6270(self, 5);
}

// ===========================================================================
// interface objects used by the large tribe behaviour-tree nodes
// ===========================================================================
struct RefHolder { char pad0[4]; void Assign(void*); };    // 0x00b5f950 (thiscall)

struct NodeState980 {
    char      pad000[0x1a4];
    int32_t   mMode;                                       // +0x1a4
    RefHolder mpRef1a8;                                    // +0x1a8
    uint8_t   mFlag1ac;                                    // +0x1ac
    uint8_t   FUN_00a75010();                              // 0x00a75010 (thiscall)
};

struct RelMgr {
    float CalculateRelationshipAbsolute(void*, void*);
    void  FUN_00d00780(float);
    void  RecordEvent(void*, void*);
};

struct NounMgrX {
    int   GetPlayerEmpireOrMinus1();
    void* SetGameDataOwner2();
};

struct StimuliMgr {
    int  PlayIdleAnimation(int, int);        // 0x00bc96a0
    void FUN_00bc97f0(int, int, float, void*);
};

struct RandObj {
    uint32_t Next(uint32_t);                 // 0x00a68fb0
};

struct Container {
    void* getContainer();
    void  FUN_00ac7de0(void*, void*);
};

struct TribeObj : GObj {
    char    pad004[0x120 - 0x004];
    GObj    m120;                                          // +0x120
    char    pad124[0x2cc - 0x124];
    float   m2cc;                                          // +0x2cc
    char    pad2d0[0x556 - 0x2d0];
    uint8_t m556;                                          // +0x556
};

struct StateFlee { int32_t mMode; float mTimer; uint8_t mFlag8; };

RelMgr*   RelationshipManager();                           // 0x00b3d2c0 (cdecl)
NounMgrX* NounManager();                                   // 0x00b3d300 (cdecl)
void*     NounByTag(int, float);                           // 0x00b3d300 with args
void*     FUN_00b3d2b0();                                  // 0x00b3d2b0 (cdecl)
void      FUN_00da63e0(void*, void*);                      // 0x00da63e0 (cdecl)
void*     FUN_00d99470(void*);                             // 0x00d99470 (cdecl)
void      FUN_00d997e0(void*);                             // 0x00d997e0 (cdecl)
float     GetPropertyT(int, int, float);                   // 0x004e1c70 (cdecl)
Vec3*     normalized_safe(Vec3*, Vec3*);                   // 0x00449c20 (cdecl)
Vec3*     FUN_0059aed0(Vec3*, Vec3*, Vec3*);               // 0x0059aed0 (cdecl)
float     RandomFloatRange(float, float);                  // 0x00572a10 (cdecl)
Vec3*     MakeRandomWorldPosition(Vec3*, void*, float, float);   // 0x00b81780
Vec3*     DirectionToSurfacePosition(Vec3*, Vec3*);        // 0x00b815a0
void      FUN_00b3d350();                                  // 0x00b3d350 (PlanetModel)

extern float    g_147c218, g_1581368, g_1581378, g_1485378;
extern float    g_1486110, g_169f3b8, g_169f3bc, g_169f3c0;
extern float    g_13eecd8, g_1470f1c;
extern uint32_t g_1581288;
extern uint8_t  g_1581374;

#define RAND_1601760 ((RandObj*)0x1601760)

// ===========================================================================
// @ 0x00dae980
// ===========================================================================
uint8_t __cdecl FUN_00dae980(CC* self, int a1, int a2, int a3, int a4, int* a5)
{
    NodeState980* st = (NodeState980*)self->mpB4C->mp600;
    if (st->FUN_00a75010() != 0)
        return 0;

    if (self->IsLeader() && self->mC0.Slot22() != 0) {
        int32_t mode = st->mMode;
        if (mode == 0) {
            a5[1] = self->InterruptAnimation(0xb4eab72c, -1, 0);
            st->mMode = 1;
            return 1;
        }
        if (mode == 1) {
            if (self->AnimationFinished(a5[1])) {
                st->mMode = 2;
                return 1;
            }
            return 1;
        }
        if (mode == 2) {
            ((StimuliMgr*)((char*)self->mpB4C + 8))->FUN_00bc97f0(0, 0x20, g_147c218, 0);
            return FUN_00da6270(self, 0x16);
        }
        return 1;
    }

    switch (*a5) {
    case 0:
        if (self->mC0.Slot22() == 0 && st->mFlag1ac == 0) {
            st->mFlag1ac = 1;
            int empire = NounManager()->GetPlayerEmpireOrMinus1();
            void* o1 = self->base.Slot19();
            float f1 = RelationshipManager()->CalculateRelationshipAbsolute(o1, (void*)(uint32_t)empire);
            RelationshipManager()->FUN_00d00780(f1);
            float d = g_1581368 - f1;
            if (d > 0.0f) {
                NounByTag(0x530cf07, d);
                int e2 = NounManager()->GetPlayerEmpireOrMinus1();
                void* o2 = self->base.Slot19();
                RelationshipManager()->RecordEvent(o2, (void*)(uint32_t)e2);
            }
            st->mpRef1a8.Assign(self->GetTribe());
            if (g_1581374 != 0) {
                TribeObj* tr = self->GetTribe();
                tr->m2cc = g_1581378;
                TribeObj* pt = (TribeObj*)NounManager()->SetGameDataOwner2();
                PtrList* l1 = self->GetTribe()->Slot36();
                for (int* p = l1->mpBegin; p != l1->mpEnd; ++p) {
                    CC* o = (CC*)*p;
                    FUN_00da63e0(o, pt);
                    ((StimuliMgr*)((char*)o->mpB4C + 8))->FUN_00bc97f0(0, 0x400000, g_1486110, pt);
                }
                PtrList* l2 = pt->Slot36();
                for (int* p = l2->mpBegin; p != l2->mpEnd; ++p) {
                    CC* o = (CC*)*p;
                    FUN_00da63e0(o, self->GetTribe());
                    ((StimuliMgr*)((char*)o->mpB4C + 8))->FUN_00bc97f0(0, 0x400000, g_1486110, self->GetTribe());
                }
            }
        }
        a5[1] = self->InterruptAnimation(0x54eacd7d, -1, 0);
        *a5 = 1;
        return 1;
    case 1:
        if (self->AnimationFinished(a5[1])) {
            a5[1] = self->InterruptAnimation(0x57e0105, -1, 0);
            *a5 = 2;
            return 1;
        }
        return 1;
    case 2:
        if (self->AnimationFinished(a5[1]))
            return 0;
        return 1;
    }
    return 1;
}

// ===========================================================================
// @ 0x00daeee0
// ===========================================================================
long double __cdecl FUN_00daeee0(CC* self, int a1, int a2, int a3, void* a4, uint8_t* a5)
{
    if (self->FUN_00c22dc0() != 9)
        return 0.0;

    uint32_t count = (uint32_t)self->base.Slot19();
    Vec3* pos = self->mC0.Slot11();
    void* best = 0;
    float prop = GetPropertyT((int)g_1581288, 0x9c37dc, g_13eecd8);
    float fMax = prop * prop;

    PtrList* list = self->mC0.FUN_00c420d0();
    for (int* p = list->mpBegin; p != list->mpEnd; ++p) {
        CC* c = (CC*)*p;
        GObj* o = (c != 0) ? c->base.Slot46(0xce9f6639) : 0;
        CC* cand = (CC*)FUN_00d99470(o);
        if (cand == 0)
            continue;
        if ((uint32_t)cand->base.Slot19() != count)
            continue;
        float f9 = ((Sub5*)&cand->m5a8)->Slot22f();
        if (!(cand->m5e0 < f9))
            continue;
        Vec3* cp = cand->mC0.Slot11();
        float dx = pos->x - cp->x;
        float dy = pos->y - cp->y;
        float dz = pos->z - cp->z;
        float dist = dx * dx + dy * dy + dz * dz;
        if (!(dist < fMax))
            continue;
        fMax = dist;
        best = cand;
    }
    if (best == 0)
        return 0.0;
    if (a4 != 0)
        FUN_00d997e0(a4);
    ((int*)a4)[1] = (int)(uint32_t)((char*)best + 0x5a8);
    *a5 = 1;
    return 1.0;
}

// ===========================================================================
// @ 0x00daf2e0
// ===========================================================================
uint8_t __cdecl FUN_00daf2e0(CC* self, int a1, int a2, int a3, int a4,
                             StateFlee* a5, int a6, float dt)
{
    if (a5->mTimer > 7.0f)
        return 0;
    a5->mTimer = a5->mTimer + dt;

    switch (a5->mMode) {
    case 0: {
        int iVar2 = ((StimuliMgr*)((char*)self->mpB4C + 8))->PlayIdleAnimation(0, 0x8000);
        int id;
        if (iVar2 != 0 && *(int*)(iVar2 + 0xc) == 0x5f0abb4) {
            id = 0x5f0abb4;
        } else if (a4 == 1) {
            id = (int)RAND_1601760->Next(3) + 0x2481dc8;
        } else {
            id = 0x2c38d92;
        }
        self->InterruptAnimation(id, -1, 0);

        TribeObj* tribe = self->GetTribe();
        float radius = tribe->Slot24f();
        Vec3 wpos;
        if (tribe->m556 == 0) {
            float ang = self->mC0.Slot29f() + radius;
            MakeRandomWorldPosition(&wpos, tribe->m120.Slot11(), radius, ang);
        } else {
            Vec3* pfVar4 = self->mC0.Slot11();
            Vec3* pfVar5 = tribe->m120.Slot11();
            Vec3 dir;
            dir.x = pfVar4->x - pfVar5->x;
            dir.y = pfVar4->y - pfVar5->y;
            dir.z = pfVar4->z - pfVar5->z;
            Vec3 nrm;
            normalized_safe(&nrm, &dir);

            float ang = RandomFloatRange(-1.4f, 1.4f);
            Vec3 axis;
            normalized_safe(&axis, pfVar4);

            float s = (float)sin((double)ang * 0.5);
            float c = (float)cos((double)ang * 0.5);

            Vec3 quat[2];                    // {nrm*s, c}
            quat[0].x = nrm.x * s;
            quat[0].y = nrm.y * s;
            quat[0].z = nrm.z * s;
            quat[1].x = c;

            Vec3 rot;
            FUN_0059aed0(&rot, &nrm, (Vec3*)quat);
            (void)axis;

            Vec3 dirpos;
            dirpos.x = pfVar4->x + rot.x * radius;
            dirpos.y = pfVar4->y + rot.y * radius;
            dirpos.z = pfVar4->z + rot.z * radius;
            DirectionToSurfacePosition(&wpos, &dirpos);
        }
        self->MoveToPointAtSpeed(3, &wpos, 1.0f, g_1470f1c);

        void* cont = self->m34.FUN_00cee330();
        if (cont != 0) {
            Container* g = (Container*)FUN_00b3d2b0();
            void* holder = g->getContainer();
            Container* g2 = (Container*)FUN_00b3d2b0();
            g2->FUN_00ac7de0(cont, holder);
        }
        a5->mMode = 1;
        break;
    }
    case 1:
        if (self->mC0.IsNearGoal() != 0) {
            if (a5->mFlag8 == 0)
                return 0;
            a5->mMode = 0;
            return 1;
        }
        break;
    }
    return 1;
}