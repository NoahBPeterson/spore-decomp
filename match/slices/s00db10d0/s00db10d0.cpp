// Slice s00db10d0 -- SP::TRIBE_* behaviour activate/deactivate functions (retail).
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

#define PV(n) virtual void pv##n();

struct Vec3 { float x, y, z; Vec3() {} Vec3(float a, float b, float c) : x(a), y(b), z(c) {} };

// ------------------------------------------------------------------ generic interfaces
// Interface with the ref-count pair used all over this slice: vtable[0] = AddRef (naked bump),
// vtable[4] = Release.  Other slots are pure query/release entry points reached through the
// same slots on several concrete types.
struct IRef {
    virtual void AddRef();                             // 0x00
    virtual void Release();                            // 0x04
};

// Fat virtual surface used by the behaviour-state ref objects.  Indices = byte offset / 4.
struct VAny {
    virtual IRef* AddRef0();                           // 0x00
    virtual void  Rel4();                              // 0x04
    PV(2)
    virtual IRef* Query0c(uint32_t id);                // 0x0c
    PV(4)
    virtual IRef* Query14(uint32_t id);                // 0x14
    virtual void  AddRef18();                          // 0x18
    virtual void  Rel1c();                             // 0x1c
    PV(8) PV(9) PV(10)
    virtual void* Call2c();                            // 0x2c
    virtual void* Call30();                            // 0x30
    PV(13)
    virtual float Call38(int a);                       // 0x38
    PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22)
    virtual IRef* Query5c(uint32_t id);                // 0x5c
    PV(24) PV(25) PV(26) PV(27) PV(28)
    virtual float GetRadius();                         // 0x74
    PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39)
    PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49)
    PV(50) PV(51) PV(52) PV(53) PV(54)
    virtual void  CallDc(void* p);                     // 0xdc
    PV(56) PV(57) PV(58)
    virtual void  CallEc();                            // 0xec
};

// Object that exposes a spatial position via vtable+0x2c.
struct VSpatial {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual const Vec3* GetPosition();                 // +0x2c
    PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
    virtual bool vf58();                               // +0x58
    virtual const Vec3* GetOffset(Vec3* out);          // +0x5c
    PV(24) PV(25) PV(26) PV(27) PV(28)
    virtual float GetRadius();                         // +0x74
    PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39)    PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49)
    PV(50) PV(51) PV(52) PV(53) PV(54)
    virtual void vfDC(void* p);                        // +0xdc
    PV(56) PV(57) PV(58)
    virtual void vfEC();                               // +0xec
    int    __thiscall IsNearGoal();                    // 0x00c42e20
};
// 0xc0-byte type whose vtable is laid out like VSpatial (locomotive object).
struct VLoco : VSpatial { uint32_t pad[(0xc0 - sizeof(VSpatial)) / 4]; };

struct VCitizen;
// the "bundle" sub-object at Citizen+0x34
struct Bundle { uint32_t mDummy; char* __thiscall Get(); };   // 0x00cee330

struct Stimuli {                                       // nSPBehaviorTree behaviour stimuli, at Omgr+8
    void* __thiscall Play(unsigned id, int a);         // 0x00bc96a0
    void  __thiscall ClearAll(int a, int b);           // 0x00bc98f0
};

struct Citizen;
// Order manager at Citizen+0xb4c (cAgentOrderManager / nSPBehaviorTree holder).
struct OrderMgr {
    void  __thiscall FUN_00bcb430();                                   // 0x00bcb430
    void* __thiscall FindNode(int kind, void* fn, Citizen* c);         // 0x00bca620
    void* __thiscall Create(int kind, int n, int p, const char* name); // 0x00bcb0b0
    void  __thiscall FUN_00bcb480(void* order, Citizen* c, int a, int b);// 0x00bcb480
    void* __thiscall FirstPending();                                   // 0x00bca2c0
    Stimuli mStimuli;                                  // +8
};

struct GC { void* mp; };

struct Mgr {
    uint32_t pad[0x1c / 4];
    void*    mp1c;
    GC*  __thiscall GetContainer();                    // 0x00ac79d0
    void __thiscall FUN_00ac7de0(void* a, void* b);    // 0x00ac7de0
    void __thiscall FUN_00ac79e0(void* a, void* b);    // 0x00ac79e0
    void __thiscall FUN_00ac7ab0(float f, void* a, int b);  // 0x00ac7ab0
    void*    mp20[8];
};
Mgr* __cdecl Ctx();                                    // 0x00b3d2b0

struct Tribe;
struct Citizen {
    virtual void AddRef();
    virtual void Release();
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
    PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26)
    PV(27) PV(28) PV(29) PV(30) PV(31) PV(32)
    virtual void vf84(void* part, int a, int b);       // +0x84
    virtual void vf88();
    virtual void vf8c();
    virtual void vf90();
    uint32_t pad04[(0x34 - 4) / 4];
    Bundle   mBundle;                                  // +0x34
    uint32_t pad38[(0xc0 - 0x38) / 4];
    VLoco    mLoco;                                    // +0xc0
    uint32_t padc4[(0xb48 - 0xc4) / 4];
    void*    mpB48;                                    // +0xb48
    OrderMgr* mpOrderMgr;                              // +0xb4c
    Citizen* mpb50;                                    // +0xb50
    uint32_t padb54[1];
    uint8_t  mb58[6];                                  // +0xb58
    uint8_t  mb5e;                                     // +0xb5e
    uint32_t padb5f[(0xfc4 - 0xb5f) / 4];
    void*    mpFC4;                                    // +0xfc4
    void*    mpFC8;                                    // +0xfc8
    uint32_t padfcc[(0x1002 - 0xfcc) / 4];
    uint8_t  mb1002;                                   // +0x1002
    uint32_t pad1003[(0x1004 - 0x1003)];
    Vec3     m1004;                                    // +0x1004
    uint32_t pad1010[(0x1014 - 0x1010) / 4];
    int      m1014;                                    // +0x1014

    Tribe* __thiscall GetTribe();                      // 0x00c22f50
    void   __thiscall FUN_00c0d0c0(unsigned a, unsigned b);  // 0x00c0d0c0
    void   __thiscall InterruptAnimation(uint32_t a, int b, int c);  // 0x00c12310
    void   __thiscall FUN_00c14750(int a);             // 0x00c14750
    void   __thiscall FUN_00c26c80();                  // 0x00c26c80
    void*  __thiscall FUN_00c23750();                  // 0x00c23750
    void   __thiscall SetStealthed(int a, int b);      // 0x00c1aed0
    void   __thiscall SetSprinting(int a);             // 0x00c1ad10
    uint8_t __thiscall OrdersLocked();                 // 0x00c22850
    void   __thiscall SetOrdersLocked(char b);         // 0x00c22860
    void   __thiscall SetFacing(float x, float y, float z);  // 0x00c227f0
    void   __thiscall FUN_00c23300(void* bundle, int a);     // 0x00c23300
    void   __thiscall FUN_00c25f80();                  // 0x00c25f80
    int    __thiscall FUN_00c25480(int a, int b);      // 0x00c25480
    void   __thiscall ForceOrdersUpdate();             // 0x00c26450
    void   __thiscall MoveToPointAtSpeed(int a, void* p, float x, float y);  // 0x00c1c1d0
    void   __thiscall MoveToPointAndFacingAtSpeed(int a, void* p, void* r, int b, int c);  // 0x00c1c5c0
    void   __thiscall FUN_00c14990(uint32_t a, void* p, int b);     // 0x00c14990
    int    __thiscall WaitForAnimEventOrEnd(uint32_t a, void* out, int b, int c, int d);  // 0x00c14ef0
    void   __thiscall FUN_00c950f0(Citizen* c);        // 0x00c950f0
};

struct Tribe {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
    PV(14) PV(15)
    void* __thiscall GetToolOfType(int type);          // 0x00c8f6e0
    void  __thiscall FindSpot(int type, int id);       // 0x00c98750
    void  __thiscall ReleaseSpot(void* ref, int type);// 0x00c97d40
};

// ---------------------------------------------------------------- behaviour state blocks
// EAT / related node state (FUN_00db10d0, FUN_00db1390, FUN_00db16d0).
struct StEat {
    int      m00;      // +0x00
    Citizen* mp04;     // +0x04
    int      m08;      // +0x08
    IRef*    mp0c;     // +0x0c
    IRef*    mp10;     // +0x10
    IRef*    mp14;     // +0x14
    IRef*    mp18;     // +0x18
    float    mf1c;     // +0x1c
    uint8_t  mb20;     // +0x20
    uint8_t  pad21[3];
    Vec3     vec24;    // +0x24
    int      m30;      // +0x30
    float    mf34;     // +0x34
};
// Same block but with a dword at +0x20 (FUN_00db16d0 reads it as an int).
struct StEatD {
    int      m00;      // +0x00
    Citizen* mp04;     // +0x04
    int      m08;      // +0x08
    IRef*    mp0c;     // +0x0c
    IRef*    mp10;     // +0x10
    IRef*    mp14;     // +0x14
    IRef*    mp18;     // +0x18
    float    mf1c;     // +0x1c
    int      m20;      // +0x20
    Vec3     vec24;    // +0x24
    int      m30;      // +0x30
    float    mf34;     // +0x34
};
// STATUS_ORDERS_CHANGED node state (FUN_00db1520).
struct StOrders {
    int      m00;      // +0x00
    float    mf04;     // +0x04
    float    mf08;     // +0x08
    IRef*    mp0c;     // +0x0c
    IRef*    mp10;     // +0x10
    Vec3     vec14;    // +0x14
};
// FUN_00db1d20 node state.
struct StTool {
    int      m00;      // +0x00
    void*    mp04;     // +0x04
    int      m08;      // +0x08
    int      m0cTool;  // +0x0c
    Vec3     vec10;    // +0x10
};
// DOMESTICATE node state (FUN_00db1e70).
struct StDom {
    int      m00;      // +0x00
    void*    mp04;     // +0x04
    int      m08;      // +0x08
    IRef*    mp0c;     // +0x0c
};

// Parameter object passed to the TRIBE_* activate functions (7th cdecl argument).
struct ParamObj {
    uint32_t    m0;                                    // +0x00
    VAny*       mp4;                                   // +0x04
    VAny*       mp8;                                   // +0x08
    uint32_t    padc;
    uint32_t    mp18;                                  // +0x18
};

// ---------------------------------------------------------------- free functions
int   __cdecl FUN_00d998d0(void* p, uint32_t id);      // 0x00d998d0
void* __cdecl FUN_00d99500(void* p);                   // 0x00d99500
void* __cdecl FUN_00d99980(void* p);                   // 0x00d99980
int   __cdecl FUN_00da6270(Citizen* c, int a);         // 0x00da6270
void  __cdecl FUN_00f47380(void* p);                   // 0x00f47380
float __cdecl FUN_00bc2240(void* a, float x, float y, float z);  // 0x00bc2240
void  __cdecl FUN_00bc2180(void* a);                   // 0x00bc2180
void* __cdecl FUN_005727b0(void* v);                   // 0x005727b0
void  __cdecl Variant_SetInt(void* v, void* p);        // 0x00427fd0
float __cdecl GetPropertyF(int holder, uint32_t id, float def);  // 0x004e1c70
void* __cdecl GetSetting9(int a, int b);               // 0x00401090
void* __cdecl GetSpeciesArchetype(void* p);            // 0x004e0050
void* __cdecl normalized_safe(Vec3* out, Vec3 d, float a, float b);  // 0x00449c20
void* __cdecl TribeModeInstance();                     // 0x00cd40b0

OrderMgr* __cdecl OrderManager();                      // 0x00bc9b00

extern const float k169f3b8, k169f3bc, k169f3c0;        // default facing
extern const float k1470f1c;
extern const float k13ec4b4;
extern const float k147c218;
extern const float k1485378;
extern const float k1473c70;
extern const float k13eb95c;
extern const float k1486110;
extern float       k157206c, k1572070;
extern float       k1581228;
extern void*       g_p1e1c;                            // 0x0158128c
extern const char  kDomesticate[];                     // 0x0147c260
extern float       k1485720;                           // 0x01485720

// ===========================================================================
// @ 0x00db10d0
// SP::TRIBE_EAT_Activate
// ===========================================================================
int __cdecl FUN_00db10d0(Citizen* c, int, int, int, int aa, StEat* st, ParamObj* prm)
{
    if (st != 0) {
        st->mp0c = 0;
        st->mp10 = 0;
        st->mp14 = 0;
        st->mp18 = 0;
    }
    st->m08 = 0;
    st->m30 = -1;
    st->mf1c = 0.0f;
    st->mf34 = 0.0f;

    int anim = (int)c->mpOrderMgr->mStimuli.Play(0x100000, 0);
    if (prm != 0) {
        IRef* o = (prm->mp8 != 0) ? prm->mp8->Query0c(0x4ffcdeda) : 0;
        IRef* old = st->mp14;
        if (o != old) {
            if (o) o->AddRef();
            st->mp14 = o;
            if (old) old->Release();
        }
    } else if (anim != 0) {
        IRef* o = (IRef*)FUN_00d998d0((void*)anim, 0x4ffcdeda);
        IRef* old = st->mp14;
        if (o != old) {
            if (o) o->AddRef();
            st->mp14 = o;
            if (old) old->Release();
        }
        if (*(Tribe**)(anim + 0xc) == c->GetTribe())
            aa &= 8;
    }

    if (st->mp14 != 0) {
        VAny* mr = (VAny*)st->mp0c;
        int got = mr ? (int)mr->Query14(0x135b1e8) : 0;
        if (got != (int)Ctx()->GetContainer() && st->mp0c != 0) {
            if (((VAny*)st->mp0c)->Query14(0x4f396a66) != 0)
                goto lab1279;
        }
        {
            const Vec3* p = ((VSpatial*)((char*)st->mp14 + 0x34))->GetPosition();
            st->vec24 = *p;
        }
        {
            IRef* o = *(IRef**)((char*)st->mp14 + 0x128);
            IRef* old = st->mp0c;
            if (o != old) {
                if (o) ((VAny*)o)->AddRef18();
                st->mp0c = o;
                if (old) ((VAny*)old)->Rel1c();
            }
        }
        {
            char* v = (char*)st->mp14;
            if (*(int*)(v + 0x12c) == 5) {
                Citizen* prev = *(Citizen**)(v + 0x120);
                if (prev != c) {
                    ((VAny*)c)->AddRef0();
                    *(Citizen**)(v + 0x120) = c;
                    if (prev) ((VAny*)prev)->Rel4();
                }
            }
        }
        goto lab12bc;
    }

lab1279:
    if (c->mBundle.Get() != 0)
        goto lab12bc;
    {
        IRef* o = (IRef*)Ctx()->GetContainer();
        IRef* old = st->mp0c;
        if (o != old) {
            if (o) ((VAny*)o)->AddRef18();
            st->mp0c = o;
            if (old) ((VAny*)old)->Rel1c();
        }
    }

lab12bc:
    if (aa & 2) {
        c->SetStealthed(1, 0);
        if (c->FUN_00c23750() != 0) {
            const Vec3* p = c->mLoco.GetPosition();
            if (st->mf34 == 0.0f)
                st->mf34 = FUN_00bc2240(*(void**)((char*)TribeModeInstance() + 0x1c8), p->x, p->y, p->z);
        }
    }
    st->mp04 = c;
    st->mb20 = 0;
    st->m00 = 0;
    if (c->mBundle.Get() != 0) {
        if (aa & 2) {
            void* b = c->mBundle.Get();
            if (*(int*)((char*)b + 0x12c) != 7) {
                Ctx()->FUN_00ac7de0(Ctx()->GetContainer(), b);
                return 1;
            }
        }
        st->m00 = 9;
    }
    return 1;
}

// ===========================================================================
// @ 0x00db1390
// ===========================================================================
void __cdecl FUN_00db1390(Citizen* c, int, int, int ea, int, StEat* st)
{
    void* bundle = c->mBundle.Get();
    if (c->OrdersLocked() == 0) {
        c->SetFacing(k169f3b8, k169f3bc, k169f3c0);
        c->SetOrdersLocked(1);
        if (bundle == 0)
            goto lab142d;
        c->FUN_00c23300(bundle, -1);
    }
    if (bundle != 0 && *(float*)((char*)bundle + 0x134) == k1485378)
        Ctx()->FUN_00ac79e0(c != 0 ? c->mBundle.Get() : 0, c != 0 ? (char*)c + 0x34 : 0);

lab142d:
    if (ea & 2) {
        c->SetStealthed(0, 0);
        c->SetSprinting(0);
        FUN_00bc2180(*(void**)((char*)TribeModeInstance() + 0x1c8));
        st->mf34 = 0.0f;
    }
    if (st->mp18 != 0 && st->m30 != -1)
        c->GetTribe()->FindSpot(0xd, st->m30);
    if (c->GetTribe() != 0)
        c->GetTribe()->ReleaseSpot(c, 0xd);
    c->FUN_00c25f80();
    {
        VAny* o = (VAny*)st->mp14;
        if (o != 0) {
            Citizen* p120 = *(Citizen**)((char*)o + 0x120);
            if (p120 == st->mp04 && p120 != 0) {
                *(void**)((char*)o + 0x120) = 0;
                ((IRef*)p120)->Release();
            }
        }
    }
    if (st->mp14 != 0) {
        IRef* p = st->mp14;
        st->mp14 = 0;
        p->Release();
    }
    if (st->mp18) st->mp18->Release();
    if (st->mp14) st->mp14->Release();
    if (st->mp10) st->mp10->Release();
    if (st->mp0c) ((VAny*)st->mp0c)->Rel1c();
}

// ===========================================================================
// @ 0x00db1520
// SP::STATUS_ORDERS_CHANGED_Activate
// ===========================================================================
int __cdecl FUN_00db1520(Citizen* c, int, int, int, int, StOrders* st, ParamObj* prm)
{
    IRef* x = 0;
    if (st != 0) {
        st->mp0c = 0;
        st->mp10 = 0;
    }
    if (prm->mp4 != 0)
        x = prm->mp4->Query5c(0xd0036e08);
    {
        IRef* old = st->mp0c;
        if (x != old) {
            if (x) x->AddRef();
            st->mp0c = x;
            if (old) old->Release();
        }
    }
    if (prm->mp8 != 0)
        x = prm->mp8->Query0c(0x2a0349a);
    else
        x = 0;
    {
        IRef* old = st->mp10;
        if (x != old) {
            if (x) x->AddRef();
            st->mp10 = x;
            if (old) old->Release();
        }
    }
    st->mf04 = (st->mp0c != 0 && ((Citizen*)((char*)st->mp0c))->mpb50 != 0) ? k1485720 : 0.0f;
    st->m00 = 0;
    void* f84 = 0;
    if (st->mp10 == 0) {
        const Vec3* p = ((VLoco*)((char*)st->mp0c + 0xc0))->GetPosition();
        st->vec14 = *p;
        if (st->mp0c != 0)
            f84 = (char*)st->mp0c + 0x5a8;
    } else {
        const Vec3* p = ((VSpatial*)((char*)st->mp10 + 0x34))->GetPosition();
        st->vec14 = *p;
        if (st->mp10 != 0)
            f84 = (char*)st->mp10 + 0x120;
    }
    c->vf84(f84, 0, 0);

    st->mf08 = 0.0f;
    {
        char* o = (char*)st->mp10;
        if (o != 0) {
            void* p1f4 = *(void**)(o + 0x1f4);
            st->mf08 = *(float*)(*(int*)((char*)p1f4 + 0xa4) + 0x570);
            void* a = *(void**)((char*)p1f4 + 0x88);
            void* b = *(void**)((char*)p1f4 + 0xf0);
            void* sp = GetSpeciesArchetype(GetSetting9((int)a, (int)b));
            if (sp != 0)
                st->mf08 = *(float*)((char*)sp + 0x368);
        }
    }
    c->mpOrderMgr->mStimuli.ClearAll(0x4000000, 0);
    return (st->mp0c != 0 || st->mp10 != 0) ? 1 : 0;
}

// ===========================================================================
// @ 0x00db16d0
// ===========================================================================
void __cdecl FUN_00db16d0(Citizen* c, int, int, int, int, StEatD* st)
{
    {
        Citizen* o = (Citizen*)st->mp0c;
        if (o != 0 && o->mpb50 == c && o->mpb50 != 0) {
            Citizen* p = o->mpb50;
            o->mpb50 = 0;
            p->Release();
        }
    }
    {
        char* o = (char*)st->mp10;
        if (o != 0 && *(Citizen**)(o + 0x21c) == c && *(Citizen**)(o + 0x21c) != 0) {
            Citizen* p = *(Citizen**)(o + 0x21c);
            *(void**)(o + 0x21c) = 0;
            p->Release();
        }
    }
    c->GetTribe()->FindSpot(0xd, st->m20);
    c->GetTribe()->ReleaseSpot(c, 0xd);
    c->vf84(0, 0, 0);
    if (st->mp10) st->mp10->Release();
    if (st->mp0c) st->mp0c->Release();
}

// ===========================================================================
// @ 0x00db1790
// ===========================================================================
int __cdecl FUN_00db1790(Citizen* c, float lim, int, int, int, StEat* st)
{
    int anim = (int)c->mpOrderMgr->mStimuli.Play(0x80000, 0);
    VAny* o = (VAny*)FUN_00d998d0((void*)anim, 0x175cdc9);
    if (o->Call2c() != 0)
        return FUN_00da6270(c, 0xd);
    float thresh = GetPropertyF((int)g_p1e1c, 0xd2078a9b, k1473c70);
    VAny* tool = (VAny*)o->Call30();
    if (tool == 0)
        return FUN_00da6270(c, 0xd);
    char* t = (char*)tool->Query0c(0x4f396a66);
    if (t == 0)
        return FUN_00da6270(c, 0xd);
    if (lim > *(float*)(t + 0x2c0))
        return FUN_00da6270(c, 0xd);

    switch (st->m00) {
    case 0: {
        if (c->mpFC4 == c->mpFC8)
            c->FUN_00c25480(0, 0);
        VAny* r1 = (VAny*)((char*)o + 0x70);
        float v0 = r1->GetRadius() + c->mLoco.GetRadius();
        const Vec3* p = ((VSpatial*)((char*)o + 0x70))->GetPosition();
        c->MoveToPointAtSpeed(2, (void*)p, v0 + k1572070, v0 + k157206c);
        st->m00 = 1;
        return 1;
    }
    case 1: {
        if (c->mpFC4 == c->mpFC8)
            c->FUN_00c25480(0, 0);
        if (!c->mLoco.IsNearGoal())
            break;
        const Vec3* pa = c->mLoco.GetPosition();
        const Vec3* pb = ((VSpatial*)((char*)o + 0x70))->GetPosition();
        Vec3 d(pb->x - pa->x, pb->y - pa->y, pb->z - pa->z);
        Vec3 out;
        Vec3* r = (Vec3*)normalized_safe(&out, d, 1.0f, 2.0f);
        c->MoveToPointAndFacingAtSpeed(2, (void*)c->mLoco.GetPosition(), r, 0x3f800000, 0x40000000);
        st->m00 = 2;
        return 1;
    }
    case 2: {
        if (c->mpFC4 != c->mpFC8) {
            if (c->FUN_00c25480(0, 0) == 0)
                break;
        } else if (c->FUN_00c25480(0, 0) == 0)
            break;
        if (!c->mLoco.IsNearGoal())
            break;
        int arg = (int)c->mpFC8;
        const Vec3* p = ((VSpatial*)((char*)o + 0x70))->GetPosition();
        c->FUN_00c14990(0x2796b30, (void*)p, arg);
        st->m00 = 4;
        return 1;
    }
    case 4: {
        float ev;
        if (!c->WaitForAnimEventOrEnd(0xbfa50b5a, &ev, -1, 0, 1))
            break;
        float a = ((VAny*)&c->mLoco)->Call38(4);
        float b = *(float*)(t + 0x2c0);        float use = (b > a) ? b : a;
        *(float*)(t + 0x2c0) = *(float*)(t + 0x2c0) - use;
        Ctx()->FUN_00ac7ab0(use, (void*)&c->mLoco, 4);
        st->m00 = 5;
        break;
    }
    default:
        break;
    }
    return 1;
}

// ===========================================================================
// @ 0x00db1c10
// SP::TRIBE_HELD_PANIC_Activate
// ===========================================================================
struct Loc74 {
    int   m00, m04, m08;
    uint32_t pad0c;
    float f10, f14, f18, f1c, f20;
    uint32_t pad24;
    uint32_t pad28[9];
    uint8_t b4c;
    uint8_t pad4d[3];
    float f50, f54, f58, f5c;
    float f60, f64, f68, f6c;
    uint32_t i70;
};
static void InitLoc74(Loc74* loc)
{
    loc->m00 = 0; loc->m04 = 0; loc->m08 = 0;
    loc->pad0c = 0;
    loc->f10 = k169f3b8; loc->f18 = k169f3bc; loc->f1c = k169f3c0;
    loc->f20 = k1485720;
    loc->pad24 = 0;
    loc->b4c = 0;
    loc->f50 = 0.0f; loc->f54 = 0.0f; loc->f58 = 0.0f; loc->f5c = 0.0f;
    loc->f60 = k1470f1c; loc->f64 = k13ec4b4; loc->f68 = k147c218; loc->f6c = 0.0f; loc->i70 = 0;
}

int __cdecl FUN_00db1c10(Citizen* c, int, int, int, int, StEat* st)
{
    c->InterruptAnimation(0x48601c0, -1, 0);
    Loc74 loc;
    InitLoc74(&loc);
    c->mLoco.vfDC(&loc);
    {
        void* p = *(void**)&loc;
        if (p != 0 && *(int*)((char*)p - 4) != 0)
            FUN_00f47380(p);
    }
    c->mpOrderMgr->mStimuli.ClearAll(0x1d3fbffa, 0x81240a0);
    c->ForceOrdersUpdate();
    (void)st;
    return 1;
}

// ===========================================================================
// @ 0x00db1d20
// ===========================================================================
char __cdecl FUN_00db1d20(Citizen* c, int, int, int, int, StTool* st, ParamObj* ctx)
{
    st->m00 = 0;
    st->m08 = -1;
    st->m0cTool = (int)ctx->mp18;
    st->mp04 = 0;
    Loc74 loc;
    InitLoc74(&loc);
    c->mLoco.vfDC(&loc);
    {
        void* p = *(void**)&loc;
        if (p != 0 && *(int*)((char*)p - 4) != 0)
            FUN_00f47380(p);
    }
    c->FUN_00c26c80();
    void* tool = c->GetTribe()->GetToolOfType(st->m0cTool);
    if (tool == 0)
        return 0;
    const Vec3* v = ((VSpatial*)((char*)tool + 0x34))->GetPosition();
    st->vec10 = *v;
    return 1;
}

// ===========================================================================
// @ 0x00db1e70
// SP::TRIBE_DOMESTICATE_Activate
// ===========================================================================
char __cdecl FUN_00db1e70(Citizen* c, int, int, int, int, StDom* st)
{
    if (st != 0) st->mp0c = 0;
    int anim = (int)c->mpOrderMgr->mStimuli.Play(0, 0x100000);
    void* o = FUN_00d99980((void*)anim);
    void* animal = FUN_00d99500(o);
    if (animal == 0)
        return (char)FUN_00da6270(c, 0x19);
    st->m00 = 0;
    c->vf84((char*)animal + 0x5a8, 1, 2);
    void* task = OrderManager()->FindNode(0x5656480, (void*)0xda7e20, c);
    if (task != 0)
        return (char)FUN_00da6270(c, 0x19);
    {
        IRef* old = st->mp0c;
        if ((IRef*)animal != old) {
            ((IRef*)animal)->AddRef();
            st->mp0c = (IRef*)animal;
            if (old) old->Release();
        }
    }
    st->m08 = 0;
    st->mp04 = 0;
    void* order = OrderManager()->Create(0x5656480, 1, 0x18eb4b7, kDomesticate);
    OrderManager()->FUN_00bcb480(order, c, 0, 0);
    c->mLoco.vfEC();
    void* pend = OrderManager()->FirstPending();
    if (pend != 0 && *(int*)pend == 0x19) {
        if (*(uint16_t*)((char*)pend + 0x4b) == 0xa) {
            st->m00 = *(int*)FUN_005727b0((char*)pend + 0x39);
            return 1;
        }
        Variant_SetInt((char*)pend + 0x39, st);
    }
    return 1;
}

// ===========================================================================
// @ 0x00db1fb0
// SP::TRIBE_DOMESTICATE_Deactivate
// ===========================================================================
void __cdecl FUN_00db1fb0(Citizen* c, int, int, int, int, StDom* st)
{
    Citizen* o = (Citizen*)st->mp0c;
    if (FUN_00d99500(o) != 0) {
        ((OrderMgr*)o->mpOrderMgr)->mStimuli.ClearAll(4, 0);
        o->FUN_00c0d0c0(6, 0);
    }
    c->mpOrderMgr->FUN_00bcb430();
    if (c->mb5e == 0) {
        c->mLoco.vfEC();
        if (st->m00 != 0) {
            c->InterruptAnimation(0x5654df4, -1, 0);
            c->FUN_00c14750(0);
        }
    }
    c->vf84(0, 0, 0);
    if (st->mp0c) st->mp0c->Release();
}
