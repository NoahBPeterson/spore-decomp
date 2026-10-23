// Slice s00ec2250 -- SP creature behaviours: pickup / object-action helpers.
// Module flags: /O2 /MD /Gy /TP /arch:SSE
#include "types.h"
#include <math.h>

// Virtual call through the receiver's vtable (vptr at object start).
#define VFN(p, off)     (((void**)*(void**)(p))[(off) / 4])
#define V0(p, off)      ((void(__thiscall*)(void*))VFN(p, off))(p)
#define VP0(p, off)     ((void*(__thiscall*)(void*))VFN(p, off))(p)
#define VC1(p, off, a)  ((char(__thiscall*)(void*, int))VFN(p, off))(p, (int)(a))

struct Vec3 { float x, y, z; };

// Per-behaviour cooldown timer (see slice s00ec1830).
struct PickupTimer {
    unsigned char active;   // +0x00
    float         time;     // +0x04
    void*         anim;     // +0x08
    unsigned char b0c;      // +0x0c
    unsigned char pad0d[3];
    float         f10;      // +0x10
    int           i14;      // +0x14
};

// State block of the jump-style behaviours (0x00ec28f0): waypoint list + timer.
struct JumpState {
    Vec3*         begin;    // +0x00
    Vec3*         end;      // +0x04
    int           pad08;
    int           f0c;
    int           f10;
    int           f14;      // index passed to FUN_00d99630
    unsigned char active;   // +0x18
    unsigned char pad19[3];
    float         time;     // +0x1c
    void*         anim;     // +0x20
    PickupTimer   timer;    // +0x24
};

// State block of the pickup-object behaviours (0x00ec2ce0/0x00ec2e30).
struct PickupState {
    int           f00;      // +0x00
    int           f04;      // +0x04
    int           f08;      // +0x08
    void*         anim;     // +0x0c
    unsigned char b10;      // +0x10
    unsigned char pad11[3];
};

struct MoveState {
    int           pad00[3];
    unsigned char b0c;      // +0x0c
    int           f10;      // +0x10
};

// ---------------------------------------------------------------- globals
extern const float k64;         // 0x0140f334  64.0f
extern const float k120;        // 0x013f1f04  120.0f
extern const float k2;          // 0x01470f1c  2.0f
extern const float k1e8;        // 0x013ec4b8  1e-8f
extern const float kFLTMax;     // 0x01488900  3.4028235e+38f
extern const float kZero;       // 0x01485378  0.0f
extern char*       g_16c7aa4;   // 0x016c7aa4

// ---------------------------------------------------------------- callees
float __cdecl ResourceScaledFloat(void* loco);  // 0x00eec820

void* __cdecl PlanetModel();                    // 0x00b3d350
void* __cdecl SP_NounManager();                 // 0x00b3d300

char  __cdecl FUN_00ec2130(void* c, PickupTimer* t, float dt);      // 0x00ec2130
char  __cdecl FUN_00d99630(void* a, void* b, Vec3* out, int n, int i);  // 0x00d99630
void* __cdecl FUN_00d998d0(void* h, unsigned int id);               // 0x00d998d0
void* __cdecl FUN_00d7cf90(void** ref);                             // 0x00d7cf90

// thiscall callees (ECX = object); declared as members so the call is direct.
struct CObj {
    void*        Get0();                                // 0x00c04590
    void*        Get();                                 // 0x00c04750
    void*        GetAvatar();                           // 0x00b1fdb0
    void*        Assign(void* src);                     // 0x00c70110
    void*        GetPosition();                         // 0x00c6acc0
    void*        Play(int a, int flags);                // 0x00bc96a0
    void         Stop(void* anim);                      // 0x00bc9770
    void         ClearAll(int a, int flags);            // 0x00bc98f0
    int          C0f4f0();                              // 0x00c0f4f0
    char         C0f5f0();                              // 0x00c0f5f0
    int          C0f8f0(void* o);                       // 0x00c0f8f0
    void         C15bd0(int a, int b);                  // 0x00c15bd0
    char         C13c60(void* o, int a);                // 0x00c13c60
    void         C14750(int a);                         // 0x00c14750
    char         IsNearGoal();                          // 0x00c42e20
    char         C42210(float r);                       // 0x00c42210
    char         AnimFinished(void* anim);              // 0x00c12400
    unsigned int Sub47d0();                             // 0x00c047d0
    void*        PlayAnimation(unsigned int id, int a, int b);   // 0x00c12190
    void         MoveToPoint(int mode, const Vec3* p, float a, float b);                      // 0x00c1c1d0
    void         MoveToPointAndFacing(int mode, const Vec3* p, const Vec3* f, float a, float b); // 0x00c1c5c0
    char         B7e3e0(Vec3* v);                       // 0x00b7e3e0
    void         F40d00(int id, int* vec);              // 0x00f40d00
    void         Dtor();                                // 0x00ae6970
    void*        MakeRandomWorldPosition(Vec3* out, const Vec3* origin, float a, float b);   // 0x00b81780
    Vec3*        DirectionToSurfacePosition(Vec3* a, Vec3* b);                               // 0x00b815a0
};
#define OBJ(p)  ((CObj*)(p))

#define Noun1(c)            OBJ(c)->Get0()
#define Noun(c)             OBJ(c)->Get()
#define Position(o)         OBJ(o)->GetPosition()
#define PlayAnim(h, a, fl)  OBJ(h)->Play(a, fl)
#define StopAnim(h, an)     OBJ(h)->Stop(an)
#define ClearStimuli(h,a,f) OBJ(h)->ClearAll(a, f)
#define FUN_00c0f4f0(c)     OBJ(c)->C0f4f0()
#define FUN_00c0f5f0(c)     OBJ(c)->C0f5f0()
#define FUN_00c0f8f0(c,o)   OBJ(c)->C0f8f0(o)
#define FUN_00c15bd0(c,a,b) OBJ(c)->C15bd0(a, b)
#define FUN_00c13c60(c,o,a) OBJ(c)->C13c60(o, a)
#define FUN_00c14750(c, a)  OBJ(c)->C14750(a)
#define IsNearGoal(l)       OBJ(l)->IsNearGoal()
#define FUN_00c42210(l, r)  OBJ(l)->C42210(r)
#define AnimFinished(c, a)  OBJ(c)->AnimFinished(a)
#define Sub47d0(c)          OBJ(c)->Sub47d0()
#define PlayAnimation(c,i,a,b) OBJ(c)->PlayAnimation(i, a, b)
#define MoveToPointAtSpeed(c,m,p,a,b) OBJ(c)->MoveToPoint(m, p, a, b)
#define MoveToPointAndFacingAtSpeed(c,m,p,f,a,b) OBJ(c)->MoveToPointAndFacing(m, p, f, a, b)
#define FUN_00b7e3e0(m, v)  OBJ(m)->B7e3e0(v)
#define FUN_00f40d00(m, i, v) OBJ(m)->F40d00(i, v)
#define VectorDtor(v)       OBJ(v)->Dtor()
#define DirectionToSurfacePosition(m,a,b) OBJ(m)->DirectionToSurfacePosition(a, b)
#define MakeRandomWorldPosition(m,o,g,a,b) OBJ(m)->MakeRandomWorldPosition(o, g, a, b)

#define LocoRadius(l)       ((float(__thiscall*)(void*))VFN(l, 0x74))(l)
#define LocoPosition(l)     ((Vec3*)((void*(__thiscall*)(void*))VFN(l, 0x2c))(l))
#define ReleaseAutoRef(o)   ((void(__thiscall*)(void*))VFN(o, 0xc0))(o)

// ---------------------------------------------------------------- 0x00ec2250
// @ 0x00ec2250
char FUN_00ec2250(void* c, int a2, int a3, int a4, int a5, PickupTimer* t, float f7, float dt)
{
    t->time += dt;
    if (t->active != 0) {
        if (t->anim == 0 || AnimFinished(c, t->anim) != 0) {
            Vec3 pos = *(Vec3*)Position(Noun1(c));
            float f = k64;
            void* q = ((void*(__thiscall*)(void*))0x006c0200)(c);
            if (q != 0) {
                pos = *(Vec3*)((char*)q + 4);
                f = *(float*)(*(int*)((char*)q + 0x28) +
                              *(int*)(*(int*)(g_16c7aa4 + 0x78) + 0xb8) * 0x34);
            }
            float lim = ResourceScaledFloat((char*)c + 0xc0);
            if (lim > f) {
                Vec3 target;
                MakeRandomWorldPosition(PlanetModel(), &target, &pos, 0.0f, lim);
                if (FUN_00b7e3e0(PlanetModel(), &target) == 0) {
                    t->active = 0;
                    t->time = kZero;
                    MoveToPointAtSpeed(c, 2, &target, 1.0f, 2.0f);
                    FUN_00c14750(c, 0);
                    return 1;
                }
            }
        }
        return 1;
    }
    if (IsNearGoal((char*)c + 0xc0) == 0 &&
        (*(unsigned char*)((char*)c + 0x330) & 1) == 0 &&
        t->time <= k120) {
        FUN_00ec2130(c, (PickupTimer*)((char*)t + 0xc), dt);
        return 1;
    }
    t->active = 1;
    switch (Sub47d0(c)) {
    case 1:
        t->anim = PlayAnimation(c, 0x7c7c136, 1, -1);
        return 1;
    case 4:
    case 5:
        t->anim = PlayAnimation(c, 0x7c7b779, 1, -1);
        return 1;
    default:
        t->anim = PlayAnimation(c, 0x7c7bb42, 1, -1);
        return 1;
    }
}

// ---------------------------------------------------------------- 0x00ec28f0
// @ 0x00ec28f0
char FUN_00ec28f0(void* c, int a2, int a3, int a4, int a5, JumpState* t, float f7, float dt)
{
    t->time += dt;
    if (t->active == 0) {
        float r = LocoRadius((char*)c + 0xc0);
        if (FUN_00c42210((char*)c + 0xc0, r + r) == 0 &&
            (*(unsigned char*)((char*)c + 0x330) & 1) == 0 &&
            t->time <= k120) {
            FUN_00ec2130(c, (PickupTimer*)((char*)t + 0x24), dt);
            return 1;
        }
        int n = (int)(t->end - t->begin);
        Vec3 out;
        char ok = FUN_00d99630((char*)c + 0x164c, (char*)c + 0x1650, &out, n, t->f14);
        if (ok == 0) {
            ++*(int*)((char*)c + 0x1648);
            *(int*)((char*)c + 0x1650) = 1;
            *(int*)((char*)c + 0x164c) = 0;
            return ok;
        }
        t->active = 1;
        t->anim = 0;
    }
    else if (t->anim == 0) {
        t->active = 0;
        int idx = *(int*)((char*)c + 0x164c);
        Vec3 p = t->begin[idx];
        float r = LocoRadius((char*)c + 0xc0);
        MoveToPointAtSpeed(c, 2, &p, r, k2);
        FUN_00c14750(c, 1);
        t->time = kZero;
        return 1;
    }
    return 1;
}

// ---------------------------------------------------------------- 0x00ec2a70
// @ 0x00ec2a70
char FUN_00ec2a70(void* c, int a2, int a3, int a4, int a5, MoveState* t)
{
    V0((char*)c + 0xc0, 0xec);
    void* h = *(void**)((char*)c + 0xb4c);
    void* anim = PlayAnim((char*)h + 8, 0, 0x80000);
    if (anim == 0)
        return 0;
    Vec3 pos;
    pos.x = *(float*)((char*)anim + 0xc);
    pos.y = *(float*)((char*)anim + 0x10);
    pos.z = *(float*)((char*)anim + 0x14);
    t->f10 = *(int*)((char*)anim + 0x18);
    StopAnim((char*)h + 8, anim);
    Vec3 lp = *LocoPosition((char*)c + 0xc0);
    float dx = pos.x - lp.x;
    float dy = pos.y - lp.y;
    float dz = pos.z - lp.z;
    float inv = 1.0f / sqrtf(dy * dy + dz * dz + dx * dx + k1e8);
    Vec3 n;
    n.x = dx * inv;
    n.y = dy * inv;
    n.z = dz * inv;
    Vec3 q;
    q.x = n.x + lp.x;
    q.y = n.y + lp.y;
    q.z = n.z + lp.z;
    Vec3* r = DirectionToSurfacePosition(PlanetModel(), &n, &q);
    float ex = r->x - q.x;
    float ey = r->y - q.y;
    float ez = r->z - q.z;
    float inv2 = 1.0f / sqrtf(ez * ez + ey * ey + ex * ex + k1e8);
    Vec3 dir;
    dir.x = ex * inv2;
    dir.y = ey * inv2;
    dir.z = ez * inv2;
    MoveToPointAndFacingAtSpeed(c, 2, &q, &dir, 1.0f, k2);
    if (Noun(c) == 0 ||
        *(unsigned char*)((char*)Noun(c) + 0x4c8) != 0 ||
        *(int*)((char*)Noun(c) + 0x4b8) != 1)
        FUN_00c14750(c, 0);
    t->b0c = 1;
    return 1;
}

// ---------------------------------------------------------------- 0x00ec2ce0
// @ 0x00ec2ce0
char FUN_00ec2ce0(void* c, int a2, int a3, int a4, int a5, PickupState* t)
{
    if (t != 0)
        t->anim = 0;
    t->f00 = 0;
    t->f04 = -1;
    t->f08 = -1;
    t->b10 = 0;
    void* h = *(void**)((char*)c + 0xb4c);
    void* anim = PlayAnim((char*)h + 8, 0, 0x40000);
    if (anim == 0 || *(int*)((char*)anim + 0xc) != 4)
        return 0;
    if (FUN_00c0f4f0(c) == 0) {
        ClearStimuli((char*)h + 8, 0, 0x40000);
        return 0;
    }
    void* id = FUN_00d998d0(anim, 0x1186577);
    OBJ(&t->anim)->Assign(id);
    if (t->anim != 0 && FUN_00c0f8f0(c, t->anim) != -1)
        return 0;
    if (FUN_00c0f5f0(c) != 0) {
        FUN_00c15bd0(c, 0, 0);
        if (FUN_00c0f5f0(c) != 0)
            return 0;
    }
    if (*(float*)(*(int*)((char*)c + 0xb20) + 0x590) == kZero)
        t->b10 = 1;
    if (t->anim != 0) {
        if (FUN_00c13c60(c, t->anim, 0) == 0)
            return 0;
        int q = (int)FUN_00d7cf90(&t->anim);
        if (q != 0 && *(int*)(q + 0x108) != 0)
            return 0;
    }
    if (((char(__thiscall*)(void*))VFN((char*)c + 0xc0, 0xf8))((char*)c + 0xc0) == 0)
        FUN_00c14750(c, 1);
    ((void(__thiscall*)(void*, int, int, int))VFN(c, 0x84))(c, 0, 0, 0);
    return 1;
}

// ---------------------------------------------------------------- 0x00ec2e30
// @ 0x00ec2e30
void FUN_00ec2e30(void* c, int a2, int a3, int a4, int a5, PickupState* t)
{
    void* h = *(void**)((char*)c + 0xb4c);
    void* anim = PlayAnim((char*)h + 8, 0, 0x40000);
    if (anim != 0 && *(int*)((char*)anim + 0xc) == 4) {
        if (FUN_00d998d0(anim, 0x1186577) == t->anim)
            StopAnim((char*)h + 8, anim);
    }
    if (t->anim != 0 && FUN_00c0f8f0(c, t->anim) == -1) {
        int q = (int)((void*(__thiscall*)(void*, int))VFN(t->anim, 0xb8))(t->anim, 0x398420d);
        if (q != 0 && *(int*)(q + 0x108) == (int)c) {
            void* linked = *(void**)(q + 0x108);
            *(int*)(q + 0x108) = 0;
            if (linked != 0)
                ((void(__thiscall*)(void*))VFN(linked, 4))(linked);
        }
    }
    if (t->anim != 0) {
        void* a = t->anim;
        t->anim = 0;
        ReleaseAutoRef(a);
    }
    FUN_00c14750(c, 0);
    if (t->anim != 0)
        ReleaseAutoRef(t->anim);
}

// ---------------------------------------------------------------- 0x00ec2f10
// @ 0x00ec2f10
void FUN_00ec2f10(void* c, int a2, int a3, int a4, int a5, PickupTimer* t)
{
    if (t != 0) {
        void* a = t->anim;
        if (a != 0)
            ReleaseAutoRef(a);
    }
}

// ---------------------------------------------------------------- 0x00ec2f30
// @ 0x00ec2f30
void* FUN_00ec2f30(void* c)
{
    void* noun = Noun(c);
    int id = *(int*)((char*)noun + 0x4c4);
    if (*(char*)((char*)noun + 0x4c8) != 0) {
        if (*(int*)((char*)c + 0x698) == 8) {
            void* av = OBJ(SP_NounManager())->GetAvatar();
            if (av != 0)
                return (char*)av + 0xc0;
            return 0;
        }
        else if (*(int*)((char*)c + 0x698) == 2) {
            id = *(int*)((char*)c + 0x69c);
        }
        else {
            return 0;
        }
    }
    else if (id == -1) {
        return 0;
    }

    void* vec[3];
    vec[0] = 0;
    vec[1] = 0;
    vec[2] = 0;
    FUN_00f40d00(*(void**)(g_16c7aa4 + 0x74), id, (int*)vec);
    if (vec[0] == vec[1]) {
        VectorDtor(vec);
        return 0;
    }
    const Vec3* cp = LocoPosition((char*)c + 0xc0);
    Vec3 p;
    p.x = cp->x;
    p.y = cp->y;
    p.z = cp->z;
    int count = (int)((int*)vec[1] - (int*)vec[0]);
    void* best = 0;
    float bestD = kFLTMax;
    for (int i = 0; i < count; i++) {
        void* obj = ((void**)vec[0])[i];
        if (obj == 0)
            continue;
        void* q = (void*)((int(__thiscall*)(void*, int))VFN(obj, 0xc))(obj, 0x1186577);
        if (q == 0)
            continue;
        const Vec3* wp = LocoPosition(q);
        float dx = wp->x - p.x;
        float dy = wp->y - p.y;
        float dz = wp->z - p.z;
        float d = dz * dz + dy * dy + dx * dx;
        if (d < bestD) {
            best = q;
            bestD = d;
        }
    }
    VectorDtor(vec);
    return best;
}

// ---------------------------------------------------------------- 0x00ec30b0
// @ 0x00ec30b0
float FUN_00ec30b0(void* c)
{
    if (*(int*)((char*)Noun(c) + 0x4b8) == 5) {
        if (FUN_00ec2f30(c) != 0)
            return 1.0f;
    }
    return 0.0f;
}
