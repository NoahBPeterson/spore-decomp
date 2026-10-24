// Slice s00dabdf0 - Spore tribe "eat" behaviour state machine helpers.
// Flags: /O2 /Ob1 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"
#include <intrin.h>
#include <math.h>

typedef unsigned int   uint32;
typedef unsigned char  byte;

// ---------------------------------------------------------------- vtable calls
#define VT(o, off)  (*(void***)(o))[(off) / 4]

typedef void  (__thiscall *Fn_v) (void*);
typedef void* (__thiscall *Fn_p) (void*);
typedef int   (__thiscall *Fn_i) (void*);
typedef bool  (__thiscall *Fn_b) (void*);
typedef float (__thiscall *Fn_f) (void*);
typedef void* (__thiscall *Fn_p1)(void*, void*);
typedef void* (__thiscall *Fn_pi)(void*, int);
typedef float (__thiscall *Fn_f1)(void*, float);
typedef void* (__thiscall *Fn_ac)(void*);

struct Vec3
{
    float x, y, z;

    void FUN_00c8ef20();         // in-place normalize, this = vector
};

// ---------------------------------------------------------------- object models
struct Citizen;
struct CTribe;
struct CTool;
struct CBehaviour;
struct LayoutMgr;

struct CTool34                    // secondary object carried at +0x34
{
    void** mpVtbl;               // +0x00 of the subobject
};

struct CTool
{
    void**   mpVtbl;             // +0x00
    char     pad04[0x30];
    CTool34  m34;                // +0x34
    char     pad38[0x12c - 0x38];
    int      m12c;               // +0x12c
    char     pad130[0x21c - 0x130];
    int      m21c;               // +0x21c
};

struct CSelf34
{
    float FUN_00cee380();        // this = citizen + 0x34
};

struct CreatureBase              // primary base of Citizen, +0x00..+0xbf
{
    char     pad00[0x34];
    CSelf34  m34;                // +0x34
    char     pad38[0xc0 - 0x38];
};

struct C41Obj
{
    char pad00[0x5c];
    int  m5c;                    // +0x5c

    Vec3* FUN_00c423c0();        // this = object returned by FUN_00c41ec0
};

struct CLoco                     // secondary base of Citizen at +0xc0
{
    void**  mpVtbl;              // +0xc0 (absolute)
    char    pad04[0x50 - 0x04];
    int     m110;                // +0x110 (absolute)
    char    pad54[0x270 - 0x54];

    bool    IsNearGoal();
    C41Obj* FUN_00c41ec0();
};

struct CCombatant
{
    int  mDummy[2];

    void PartialRepair(float amount);
};

struct CB54Obj
{
    char  pad00[0x80];
    float mf80;                  // +0x80
};

struct CNeighborInfo
{
    char     pad00[0x10];
    unsigned mi10;               // +0x10
    char     pad14[0x1a4 - 0x14];
    unsigned mi1a4;              // +0x1a4
};

struct CB4CObj
{
    char           pad00[0x600];
    CNeighborInfo* mp600;        // +0x600
};

struct Citizen : CreatureBase, CLoco
{
    int        m330;             // +0x330
    char       pad334[0x5a8 - 0x334];
    CCombatant mCombat;          // +0x5a8
    char       pad5b0[0xb4c - 0x5b0];
    CB4CObj*   mpB4C;            // +0xb4c
    char       padB50[4];
    CB54Obj*   mpB54;            // +0xb54
    int        mB58;             // +0xb58

    CTribe* GetTribe();
    void    FUN_00c14750(int a);
    void    FUN_00c0ba10();
    bool    FUN_00c25480(int a, int b);
    void    MoveToPointAtSpeed(int mode, const Vec3* point, float s1, float s2);
    void    MoveToPointAndFacingAtSpeed(int mode, const Vec3* point,
                                        const Vec3* facing, float s1, float s2);
    int     FUN_00c22820();
    void    PlayAnimationWithTarget(unsigned anim, void* target, int a, int b);
    bool    WaitForAnimEventOrEnd(unsigned id, bool* out, int a, int b, int c);
    bool    AnimationFinished(int a);
    void    PlayAnimation(unsigned anim, int a, int b);
    int     FUN_00c22c40(int a);
    void    SetCurrentToolEffect(int a, int b);
    float   FUN_00c0b9c0();
    void    FUN_00c0b9d0(float f);
    bool    FUN_00c0b770();
};

struct CTribe120
{
    void** mpVtbl;               // +0x120 (absolute)
};

struct CTribe20c
{
    CTool* FUN_00cee330();       // this = tribe + 0x20c
};

struct CTribe
{
    char      pad00[0x120];
    CTribe120 m120;              // +0x120
    char      pad124[0x20c - 0x124];
    CTribe20c m20c;              // +0x20c
    char      pad210[0x260 - 0x210];
    CTool*    mp260;             // +0x260
    char      pad264[0x100];

    int   FUN_00c97ca0(int id, Citizen* c);
    int   FUN_00c97c40(int id, Citizen* c);
    void  FUN_00c97d40(int id, Citizen* c);
    void  FUN_00c979e0(Vec3* out, int id, Citizen* c);
    void  FUN_00c97b10(Vec3* out, int id, Citizen* c);
    Vec3* FUN_00c986d0(int id, int* out, Citizen* c);
};

struct CBehaviour
{
    bool FUN_00ac7ef0(Citizen* self, CTool* target);
    void FUN_00ac7d10(float f, int a, CTribe* tribe);
};

struct LayoutMgr
{
    bool FUN_00af0bd0();
};

struct CXY
{
    void FUN_00cc5170();
};

// state block used by the eat tick behaviour (00dabdf0)
struct EatTickState
{
    int    mi00;                 // +0x00
    int    mi04;                 // +0x04
    int    mi08;                 // +0x08
    CTool* mp0c;                 // +0x0c
    int    mi10;                 // +0x10
};

// state block used by the hive behaviour (00dac7e0)
struct HiveState
{
    int   mi00;                  // +0x00
    int   mi04;                  // +0x04
    int   mi08;                  // +0x08
    float mf0c;                  // +0x0c
    float mf10;                  // +0x10
};

// ---------------------------------------------------------------- externals
CBehaviour* FUN_00b3d2b0();                        // cdecl, no args
bool        FUN_00da6270(Citizen* self, int a);    // cdecl
CXY*        FUN_00cc8b10(Citizen* self);           // __stdcall
LayoutMgr*  FUN_00af13b0(Citizen* self, int a, int b); // __stdcall

extern "C" void* __stdcall FUN_00b3d310(CLoco* p);

extern float DAT_01572070;
extern float DAT_0157206c;
extern float DAT_01581298;
extern float DAT_015812a0;
extern float DAT_0158129c;
extern float DAT_01687a00;
extern float DAT_01485720;

// ---------------------------------------------------------------- math helper
Vec3 normalized_safe(const Vec3& v);               // struct return (hidden ptr)

// ---------------------------------------------------------------- 00dac580
struct C580Ref
{
    virtual void r00();
    virtual void r04();
};

struct C580Obj
{
    char    pad00[0x120];
    C580Ref* mp120;              // +0x120
};

struct C580
{
    char     pad00[4];
    void*    m04;                // +0x04
    char     pad08[0xc];
    C580Obj* mp14;               // +0x14

    void FUN_00dac580();
};

// @ 0x00dac580
void C580::FUN_00dac580()
{
    C580Obj* o = mp14;
    if (o != 0)
    {
        C580Ref* p = o->mp120;
        if (p == m04 && p != 0)
        {
            o->mp120 = 0;
            p->r04();
        }
    }

    C580Obj* o2 = mp14;
    if (o2 != 0)
    {
        mp14 = 0;
        ((C580Ref*)o2)->r04();
    }
}

// ---------------------------------------------------------------- 00dac5d0
struct C90
{
    char pad00[8];
    int  m08;                    // +0x08
};

struct C5d0Obj
{
    char  pad00[0x64];
    void* mp64;                  // +0x64
    char  pad68[0x90 - 0x68];
    C90*  mp90;                  // +0x90
};

struct C05Vt
{
    virtual void  a00();
    virtual void  a04();
    virtual void  a08();
    virtual void* a0c(int id);
};

struct C05Result
{
    char  pad00[0xb5e];
    byte  mb5e;                  // +0xb5e
    char  padB5f[0xb84 - 0xb5f];
    float mfB84;                 // +0xb84
};

// @ 0x00dac5d0
bool FUN_00dac5d0(C5d0Obj* p)
{
    if (p->mp64 != 0 && (p->mp90 == 0 || p->mp90->m08 != 0x2e81370))
    {
        _ReadWriteBarrier();
        if (p->mp64 != 0)
        {
            C05Result* r =
                (C05Result*)((C05Vt*)p->mp64)->a0c(0xd0036e08);
            if (r != 0 && r->mb5e != 0 && r->mfB84 > 0.0f)
                return 1;
        }
        return 0;
    }
    return 0;
}

// ---------------------------------------------------------------- 00dac630
struct St630
{
    byte  mb0;                   // +0x00
    char  pad1[3];
    int   mi4;                   // +0x04
    int   mi8;                   // +0x08
};

// @ 0x00dac630
bool FUN_00dac630(Citizen* self, int a2, int a3, int a4, int a5, St630* st)
{
    st->mb0 = 0;
    st->mi4 = -1;

    self->FUN_00c14750(0);

    CTribe* t = self->GetTribe();
    CTool*  o = (CTool*)((Fn_ac)VT(t, 0xac))(t);
    CTool34* p = &o->m34;

    float sp = ((Fn_f)VT(p, 0x74))(p);

    float tmp[3];
    Vec3* dir = (Vec3*)((Fn_p1)VT(p, 0x5c))(p, tmp);

    float dx = dir->x * sp;
    float dy = dir->y * sp;
    float dz = dir->z * sp;

    Vec3* pos = (Vec3*)((Fn_p)VT(p, 0x2c))(p);

    Vec3 dst;
    dst.x = pos->x + dx;
    dst.y = pos->y + dy;
    dst.z = pos->z + dz;

    float f1 = ((Fn_f)VT(t, 0x60))(t);
    float f2 = ((Fn_f1)VT(t, 0x60))(t, f1);

    self->MoveToPointAtSpeed(2, &dst, f2, f1);

    st->mi8 = 0;
    return true;
}

// ---------------------------------------------------------------- 00dac730
struct St730
{
    byte  mb0;                   // +0x00
    char  pad1[3];
    int   mi4;                   // +0x04
};

struct Cb3d310Res
{
    void FUN_00b453a0();
    void FUN_00b45410();
};

// @ 0x00dac730
void FUN_00dac730(Citizen* self, int a2, int a3, int a4, int a5, St730* st)
{
    self->FUN_00c0ba10();

    self->mB58 &= 0xfffff7ff;
    self->mpB54->mf80 = DAT_01485720;

    if (st->mb0 != 0)
    {
        if (self->GetTribe() != 0)
        {
            CTribe* t = self->GetTribe();
            CTool* o = (CTool*)((Fn_ac)VT(t, 0xac))(t);
            if (o != 0)
            {
                CTribe* t2 = self->GetTribe();
                CTool* o2 = (CTool*)((Fn_ac)VT(t2, 0xac))(t2);
                int* q = &o2->m21c;
                (*q)--;
            }
        }
    }

    if (st->mi4 != -1)
    {
        self->GetTribe()->FUN_00c97d40(0xc, self);
    }

    self->m110 &= 0xffffff7f;

    CLoco&      loco = static_cast<CLoco&>(*self);
    Cb3d310Res* r    = (Cb3d310Res*)FUN_00b3d310(&loco);
    r->FUN_00b453a0();
    _ReadWriteBarrier();
}

// @ 0x00dabdf0
bool FUN_00dabdf0(Citizen* self, int a2, int a3, int a4, int a5,
                  EatTickState* st)
{
    CBehaviour* beh = FUN_00b3d2b0();
    CTool* target = st->mp0c;

    if (target == 0 ||
        ((Fn_b)VT(target, 0x2c))(target) ||
        !beh->FUN_00ac7ef0(self, target))
    {
        CTribe* t = self->GetTribe();
        CTool* tool = t->m20c.FUN_00cee330();
        if (tool == 0)
            return FUN_00da6270(self, 0);

        CTool* old = st->mp0c;
        if (tool != old)
        {
            ((Fn_v)VT(tool, 0))(tool);
            st->mp0c = tool;
            if (old != 0)
                ((Fn_v)VT(old, 4))(old);
        }
        target = tool;
    }

    if (!beh->FUN_00ac7ef0(self, target))
        return FUN_00da6270(self, 0);

    switch (st->mi08)
    {
    case 0:
        if (self->m34.FUN_00cee380() > 0.0f)
        {
            self->FUN_00c14750(0);
            st->mi08 = 3;
            return true;
        }
        self->FUN_00c25480(0, 1);
        ((Fn_v)VT(&static_cast<CLoco&>(*self), 0xec))(&static_cast<CLoco&>(*self));
        st->mi08 = 4;
        return true;

    case 1:
        if (!self->FUN_00c25480(0, 0))
            break;
        if (!static_cast<CLoco&>(*self).IsNearGoal())
            break;
        {
            int u = self->FUN_00c22820();
            self->PlayAnimationWithTarget(0x2796b31, &target->m34, -1, u);
            st->mi08 = 2;
            return true;
        }

    case 2:
        {
            bool flag = false;
            if (self->WaitForAnimEventOrEnd(0xbfa50b5a, &flag, -1, 0, 1))
            {
                int id  = target->m12c;
                int eff = self->FUN_00c22c40(id);
                self->SetCurrentToolEffect(eff, -1);
                st->mi08 = 3;
                return true;
            }
        }
        break;

    case 3:
        if (self->AnimationFinished(0))
        {
            int u = self->FUN_00c22820();
            self->PlayAnimation(0x2796b38, 1, u);
            int id  = target->m12c;
            int eff = self->FUN_00c22c40(id);
            self->SetCurrentToolEffect(eff, -1);
            st->mi08 = 6;
            return true;
        }
        break;

    case 4:
        {
            CTribe* t = self->GetTribe();
            Vec3 vec;
            t->FUN_00c979e0(&vec, 0xd, self);

            CLoco* loco = static_cast<CLoco*>(self);
            C41Obj* obj = loco->FUN_00c41ec0();
            bool far = true;
            if (obj->m5c != 0)
            {
                Vec3* pp = obj->FUN_00c423c0();
                Vec3  d;
                d.x = pp->x - vec.x;
                d.y = pp->y - vec.y;
                d.z = pp->z - vec.z;
                float dist2 = d.x * d.x + d.y * d.y + d.z * d.z;
                far = DAT_01572070 < dist2;
            }
            if (far)
            {
                float sc = ((Fn_f)VT(loco, 0x74))(loco);
                self->MoveToPointAtSpeed(2, &vec, sc * 3.0f, sc * 4.0f);
            }

            self->FUN_00c25480(0, 0);

            if (loco->IsNearGoal())
            {
                self->mpB4C->mp600->mi1a4++;

                int v = t->FUN_00c97ca0(0xd, self);
                st->mi00 = v;

                Vec3 vec2;
                t->FUN_00c97b10(&vec2, 0xd, self);

                CTool* tool = self->GetTribe()->mp260;
                Vec3*  cam  = (Vec3*)((Fn_p)VT(&tool->m34, 0x2c))(&tool->m34);

                Vec3 dir;
                dir.x = cam->x - vec2.x;
                dir.y = cam->y - vec2.y;
                dir.z = cam->z - vec2.z;
                Vec3 n = normalized_safe(dir);

                self->MoveToPointAndFacingAtSpeed(2, &vec2, &n,
                                                  DAT_01572070, DAT_0157206c);
                st->mi08 = 5;
                return true;
            }
        }
        break;

    case 5:
        {
            self->FUN_00c25480(0, 0);

            CTribe* t = self->GetTribe();
            bool changed = false;

            int v = t->FUN_00c97c40(0xd, self);
            if (v != st->mi00)
            {
                st->mi00 = v;
                changed = true;
            }

            CNeighborInfo* nb = self->mpB4C->mp600;

            if (st->mi00 == 0)
            {
                if (changed)
                    goto movement;

                if ((nb->mi10 >> 1) <= nb->mi1a4 &&
                    static_cast<CLoco&>(*self).IsNearGoal())
                {
                    Vec3* pt = t->FUN_00c986d0(0xd, &st->mi10, self);
                    if (st->mi10 < 0)
                        return true;

                    st->mi00 = -1;
                    t->FUN_00c97d40(0xd, self);

                    CTool* tool = self->GetTribe()->mp260;
                    Vec3*  cam  = (Vec3*)((Fn_p)VT(&tool->m34, 0x2c))(&tool->m34);

                    Vec3 dir;
                    dir.x = pt->x - cam->x;
                    dir.y = pt->y - cam->y;
                    dir.z = pt->z - cam->z;
                    Vec3 n = normalized_safe(dir);

                    Vec3 neg;
                    neg.x = -n.x;
                    neg.y = -n.y;
                    neg.z = -n.z;

                    self->MoveToPointAndFacingAtSpeed(2, pt, &neg,
                                                      DAT_01572070, DAT_0157206c);
                    st->mi08 = 1;
                    return true;
                }
            }
            else if (changed)
            {
                goto movement;
            }

            if (st->mi00 == 0 && (self->m330 & 1) != 0)
            {
                st->mi00 = -1;
                t->FUN_00c97d40(0xd, self);
                st->mi08 = 0;
                return true;
            }
            break;

        movement:
            {
                CTribe* t2 = self->GetTribe();
                Vec3 vec;
                t2->FUN_00c97b10(&vec, 0xd, self);

                CTool* tool = t2->mp260;
                Vec3*  cam  = (Vec3*)((Fn_p)VT(&tool->m34, 0x2c))(&tool->m34);

                Vec3 dir;
                dir.x = cam->x - vec.x;
                dir.y = cam->y - vec.y;
                dir.z = cam->z - vec.z;
                Vec3 n = normalized_safe(dir);

                self->MoveToPointAndFacingAtSpeed(2, &vec, &n,
                                                  DAT_01572070, DAT_0157206c);
                return true;
            }
        }

    case 6:
        if (self->AnimationFinished(0))
        {
            CTribe* t = self->GetTribe();
            beh->FUN_00ac7d10(DAT_01581298, 0, t);
            self->mCombat.PartialRepair(DAT_015812a0 * DAT_01581298);

            float f = self->FUN_00c0b9c0();
            self->FUN_00c0b9d0(DAT_0158129c * DAT_01581298 + f);

            st->mi08 = (st->mi10 >= 0) ? 1 : 0;
            self->SetCurrentToolEffect(0, -1);
        }

        if ((st->mi04 & 0xff) == 0)
        {
            float f = self->FUN_00c0b9c0();
            if (DAT_01687a00 <= f)
            {
                if (!self->FUN_00c0b770())
                    FUN_00cc8b10(self)->FUN_00cc5170();

                CTribe* t = self->GetTribe();
                Vec3*  p = (Vec3*)((Fn_p)VT(&t->m120, 0x2c))(&t->m120);
                self->MoveToPointAtSpeed(2, p, 7.5f, 10.0f);
                st->mi08 = 7;
                return true;
            }
        }
        else
        {
            if (self->FUN_00c0b770())
                self->FUN_00c0b9d0(DAT_01687a00);

            LayoutMgr* mgr = FUN_00af13b0(self, 1, 0);
            if (mgr->FUN_00af0bd0())
                return true;

            if (!self->FUN_00c0b770())
                FUN_00cc8b10(self)->FUN_00cc5170();

            CTribe* t = self->GetTribe();
            Vec3*  p = (Vec3*)((Fn_p)VT(&t->m120, 0x2c))(&t->m120);
            self->MoveToPointAtSpeed(2, p, 7.5f, 10.0f);
            st->mi08 = 7;
            return true;
        }
        break;

    case 7:
        if (static_cast<CLoco&>(*self).IsNearGoal() || (self->m330 & 1) != 0)
            return FUN_00da6270(self, 0);
        break;
    }

    return true;
}

// @ 0x00dac7e0
bool FUN_00dac7e0(Citizen* self, int a2, int a3, int a4, int a5, HiveState* st)
{
    switch (st->mi08)
    {
    case 0:
        if (static_cast<CLoco&>(*self).IsNearGoal())
            st->mi08 = 1;
        break;

    case 1:
        {
            CTribe* t = self->GetTribe();
            Vec3 vec;
            t->FUN_00c979e0(&vec, 0xc, self);

            CLoco* loco = static_cast<CLoco*>(self);
            C41Obj* obj = loco->FUN_00c41ec0();
            bool far = true;
            if (obj->m5c != 0)
            {
                Vec3* pp = obj->FUN_00c423c0();
                Vec3  d;
                d.x = pp->x - vec.x;
                d.y = pp->y - vec.y;
                d.z = pp->z - vec.z;
                float dist2 = d.x * d.x + d.y * d.y + d.z * d.z;
                far = DAT_01572070 < dist2;
            }
            if (far)
            {
                float sc = ((Fn_f)VT(loco, 0x74))(loco);
                self->MoveToPointAtSpeed(2, &vec, sc * 4.0f, sc * 6.0f);
            }

            if (loco->IsNearGoal())
            {
                st->mi04 = t->FUN_00c97ca0(0xc, self);
                st->mi08 = 2;
                return true;
            }
        }
        break;

    case 2:
        {
            CTribe* t = self->GetTribe();
            CLoco*  loco = static_cast<CLoco*>(self);

            int  v = t->FUN_00c97c40(0xc, self);
            bool changed = (v != st->mi04);
            if (changed)
                st->mi04 = v;

            if (st->mi04 == 0)
            {
                if (changed)
                    goto movement;

                if (loco->IsNearGoal() || (self->m330 & 1) != 0)
                {
                    st->mi04 = -1;
                    t->FUN_00c97d40(0xc, self);
                    st->mi08 = 3;
                    return true;
                }
            }
            else if (changed)
            {
                goto movement;
            }
            break;

        movement:
            {
                CTribe* t2 = self->GetTribe();
                float s = ((Fn_f)VT(loco, 0x74))(loco);

                Vec3 vec;
                t2->FUN_00c97b10(&vec, 0xc, self);
                self->MoveToPointAtSpeed(2, &vec, s + DAT_01572070, s + s);
                return true;
            }
        }

    case 3:
        {
            CLoco* loco = static_cast<CLoco*>(self);
            if (!loco->IsNearGoal())
                break;

            CLoco* lp = self ? static_cast<CLoco*>(self) : 0;
            Cb3d310Res* r = (Cb3d310Res*)FUN_00b3d310(lp);
            r->FUN_00b45410();

            self->m110 |= 0x80;

            CTribe* t = self->GetTribe();
            CTool* tool = (CTool*)((Fn_ac)VT(t, 0xac))(t);
            Vec3*  p = (Vec3*)((Fn_p)VT(&tool->m34, 0x2c))(&tool->m34);
            self->MoveToPointAtSpeed(2, p, DAT_01572070, DAT_0157206c);
            st->mi08 = 4;

            t = self->GetTribe();
            tool = (CTool*)((Fn_ac)VT(t, 0xac))(t);
            Vec3* toolp = (Vec3*)((Fn_p)VT(&tool->m34, 0x2c))(&tool->m34);
            Vec3* locop = (Vec3*)((Fn_p)VT(loco, 0x2c))(loco);

            float dx = toolp->x - locop->x;
            float dy = toolp->y - locop->y;
            float dz = toolp->z - locop->z;
            st->mf0c = sqrtf(dx * dx + dy * dy + dz * dz);

            t = self->GetTribe();
            tool = (CTool*)((Fn_ac)VT(t, 0xac))(t);
            float sc = ((Fn_f)VT(&tool->m34, 0x74))(&tool->m34);
            float d  = (st->mf0c - sc) + 1.0f;

            st->mf10 = 1.0f / ((d <= 1.0f) ? 1.0f : d);
            return true;
        }

    case 4:
        {
            CLoco* loco = static_cast<CLoco*>(self);

            if (loco->IsNearGoal())
            {
                st->mi08 = 5;
                ((Fn_v)VT(loco, 0xec))(loco);

                CTribe* t = self->GetTribe();
                CTool* tool = (CTool*)((Fn_ac)VT(t, 0xac))(t);
                int* q = &tool->m21c;
                (*q)++;

                st->mi00 = 1;
                st->mi08 = 5;
            }

            CTribe* t = self->GetTribe();
            CTool* tool = (CTool*)((Fn_ac)VT(t, 0xac))(t);
            Vec3* toolp = (Vec3*)((Fn_p)VT(&tool->m34, 0x2c))(&tool->m34);
            Vec3* locop = (Vec3*)((Fn_p)VT(loco, 0x2c))(loco);

            float dx = locop->x - toolp->x;
            float dy = locop->y - toolp->y;
            float dz = locop->z - toolp->z;
            float d  = (st->mf0c - sqrtf(dx * dx + dy * dy + dz * dz)) * st->mf10;

            float a = (d >= 1.0f) ? 1.0f : d;
            float r = 1.0f - a;
            if (r >= 1.0f)
                r = 1.0f;

            self->mB58 |= 0x800;
            self->mpB54->mf80 = r;
            return true;
        }

    case 5:
        {
            LayoutMgr* mgr = FUN_00af13b0(self, 2, 0);
            if (!mgr->FUN_00af0bd0())
            {
                st->mi00 = 0;

                CTribe* t = self->GetTribe();
                CTool* tool = (CTool*)((Fn_ac)VT(t, 0xac))(t);
                int* q = &tool->m21c;
                (*q)--;

                CLoco* loco = static_cast<CLoco*>(self);
                float s = ((Fn_f)VT(loco, 0x74))(loco);

                Vec3 v;
                Vec3* r = (Vec3*)((Fn_p1)VT(t, 0xac))(t, &v);
                r->FUN_00c8ef20();

                self->MoveToPointAtSpeed(2, &v, s + s, s + s);
                st->mi08 = 6;
                return true;
            }
        }
        break;

    case 6:
        if (static_cast<CLoco&>(*self).IsNearGoal())
            return FUN_00da6270(self, 6);
        break;
    }

    return true;
}
