// s00e7e7f0: SP::sExecuteCollisionResult (0x00e7e7f0), the dispatcher that applies one collision
// result record (type 1..0x15) to the two participating entities.
#include "types.h"
#include <math.h>

struct Vec3 { float x, y, z; };

struct Transform {
    uint32_t data[14];
    Transform();                      // 0x00409930
};

struct Entity {
    uint32_t id;                      // +0x00
    uint8_t flag4;                    // +0x04
    char pad5[0xb4 - 5];
    uint32_t u_b4;                    // +0xb4
    float mass;                       // +0xb8
    char padbc[0x108 - 0xbc];
    uint32_t u108;                    // +0x108
    char pad10c[0x111 - 0x10c];
    uint8_t b111;                     // +0x111
    uint8_t b112;                     // +0x112
    char pad113[0x144 - 0x113];
    int lastTime;                     // +0x144
    char pad148[0x170 - 0x148];
    uint32_t u170;                    // +0x170
    char pad174[0x178 - 0x174];
    uint8_t b178;                     // +0x178
    uint8_t b179;                     // +0x179
    uint8_t pad17a;
    uint8_t b17b;                     // +0x17b
    char pad17c[0x17f - 0x17c];
    uint8_t b17f;                     // +0x17f
    char pad180[0x18c - 0x180];
    uint32_t state;                   // +0x18c
    char pad190[0x1b0 - 0x190];
    uint32_t u1b0;                    // +0x1b0
    char pad1b4[0x1c4 - 0x1b4];
    float vel[3];                     // +0x1c4
    char pad1d0[0x370 - 0x1d0];
    void* p370;                       // +0x370
};

struct CollisionResult {
    uint32_t id0;                     // +0x00
    uint32_t id1;                     // +0x04
    int type;                         // +0x08
    uint32_t a3;                      // +0x0c
    uint32_t a4;                      // +0x10
    float f14;                        // +0x14
    float pos[3];                     // +0x18
    Vec3 normal;                      // +0x24
};

struct Registry {
    char pad[0x38];
    Entity* Get(uint32_t id);         // 0x00b72210
    Entity* GetOwner(uint32_t id);    // 0x00b721d0
};
struct Registry54 {
    Entity* GetOwner(uint32_t id);    // 0x00b721d0
};
struct CellGame {
    char pad0[0x1c];
    int  level;                       // +0x1c
    char pad20[0x74 - 0x20];
    int  time;                        // +0x74
};
struct Game {
    char pad0[0x8];
    float f08;                        // +0x08
    float fc;                         // +0x0c
    float f10;                        // +0x10
    float f14;                        // +0x14
    float f18;                        // +0x18
    Registry reg;                     // +0x1c
    Registry54 reg54;                 // +0x54
    char pad1[0x4104 - 0x55];
    void* grid;                       // +0x4104
    char pad4108[0x411c - 0x4108];
    uint32_t mField411c;              // +0x411c
    char pad4120[0x4128 - 0x4120];
    uint32_t field4128;               // +0x4128
    char pad412c[0x5190 - 0x412c];
    CellGame* cell;                   // +0x5190
    uint32_t mField5194;              // +0x5194
    char pad5198[0x51da - 0x5198];
    uint8_t b51da;                    // +0x51da
};
extern Game* g_016b3c04;              // 0x016b3c04

extern bool __cdecl FUN_00e73140(Entity* a, Entity* b, uint32_t a3);                                // 0x00e73140
extern void __cdecl FUN_00e67100(uint32_t id, const float* pos, Vec3 n, float f, float dt);          // 0x00e67100
extern void __cdecl FUN_00e732d0(Entity* a, Entity* b, uint32_t a3, uint32_t a4, const Vec3* n);     // 0x00e732d0
extern bool __cdecl FUN_00e57460(Entity* a, Entity* b);                                              // 0x00e57460
extern void __cdecl FUN_00e70a90(Entity* a, uint32_t a3, int kind, const Vec3* n, float dt);         // 0x00e70a90
extern void __cdecl FUN_00e70b20(Entity* a, Entity* b, uint32_t a3, const Vec3* n, int kind, float dt);   // 0x00e70b20
extern void __cdecl FUN_00e777a0(Entity* a, Entity* b, uint32_t a3, const float* pos, const Vec3* n, float dt);   // 0x00e777a0 SP::sPoke_Start
extern void __cdecl FUN_00e72360(Entity* a, Entity* b, uint32_t a3, const float* pos, const Vec3* n, int one, float dt);   // 0x00e72360
extern void __cdecl FUN_00e7a7c0(Entity* a, Entity* b, const Vec3* n, int p3, int p1, float dt);     // 0x00e7a7c0
extern float __cdecl FUN_00e6d200(Entity* e, int zero, int eleven, uint32_t v);                      // 0x00e6d200
extern uint32_t __cdecl FUN_00e51ee0(int one, float f, uint32_t id0, uint32_t id1, uint32_t a3, int m1, int three, uint32_t u108,
                                     float z0, float z1, int a, int b, int c, int d, int e, int f2);   // 0x00e51ee0
extern void __cdecl FUN_00e57a10(Entity* e, uint32_t a3);                                            // 0x00e57a10
extern void __cdecl FUN_00e68000(Entity* e, uint32_t a3, Transform* t);                              // 0x00e68000
extern void __cdecl FUN_00e62380(Entity* e, uint32_t a3, Entity* o, Transform* t, float z);          // 0x00e62380
extern void __cdecl FUN_00e59200(void* p);                                                           // 0x00e59200
extern void __cdecl FUN_00e5f4d0(uint32_t id, float z, float f);                                     // 0x00e5f4d0 SP::sPull
extern void __cdecl FUN_00e7b5d0(Entity* a, Entity* b);                                              // 0x00e7b5d0
extern void __cdecl FUN_00e7db80();                                                                  // 0x00e7db80

// Callees with LTCG register conventions (extra register arguments in the comments). They are
// called from single __asm blocks so the register arguments are set exactly.
extern "C" void FUN_00e791a0(void);     // 0x00e791a0  eax = b, esi = a, stack: dt
extern "C" void FUN_00e7b630(void);     // 0x00e7b630  esi = a, stack: b
extern "C" void FUN_00e72910(void);     // 0x00e72910  esi = b, stack: a, a3; returns al
extern "C" void FUN_00e725c0(void);     // 0x00e725c0  esi = b, edi = a, stack: a3; returns al
extern "C" void FUN_00e727e0(void);     // 0x00e727e0  esi = b, edi = a, stack: a3; returns al
extern "C" void FUN_00e7b470(void);     // 0x00e7b470  eax = &normal, esi = a, stack: b, a3, &pos
extern "C" void FUN_00e7e020(void);     // 0x00e7e020  esi = b, stack: a, a3, 2; returns al
extern "C" void FUN_00e528d0(void);     // 0x00e528d0  eax = handle, stack: callback
extern "C" void FUN_00e528f0(void);     // 0x00e528f0  eax = handle, stack: idx, value

static inline void Finish(CollisionResult* r, float dt)
{
    FUN_00e67100(r->id0, r->pos, r->normal, r->f14, dt);
}

static inline void Negate(Vec3* out, const Vec3& n)
{
    out->x = -n.x;
    out->y = -n.y;
    out->z = -n.z;
}

// @ 0x00e7e7f0  SP::sExecuteCollisionResult
void __cdecl sExecuteCollisionResult(CollisionResult* r, float dt)
{
    Entity* a = g_016b3c04->reg.Get(r->id0);
    Entity* b = g_016b3c04->reg.Get(r->id1);
    uint32_t a3 = r->a3;
    char ok;
    Vec3 neg;
    switch (r->type) {
    case 1:
        break;
    case 2: {
        Entity* m = (a->mass > b->mass) ? b : a;
        float k = m->mass;
        float nx = r->normal.x, ny = r->normal.y, nz = r->normal.z;
        a->vel[0] = a->vel[0] - (nx * 3.0f) * k;
        a->vel[1] = a->vel[1] - (ny * 3.0f) * k;
        a->vel[2] = a->vel[2] - (nz * 3.0f) * k;
        b->vel[1] = (r->normal.y * 3.0f) * k + b->vel[1];
        b->vel[2] = (r->normal.z * 3.0f) * k + b->vel[2];
        b->vel[0] = b->vel[0] + (r->normal.x * 3.0f) * k;
        break;
    }
    case 3:
        __asm {
            push dt
            mov eax, b
            mov esi, a
            call FUN_00e791a0
            add esp, 4
        }
        break;
    case 4:
        FUN_00e70b20(a, b, a3, &r->normal, 0x1a, dt);
        break;
    case 5:
        FUN_00e70b20(a, b, a3, &r->normal, 0x1b, dt);
        break;
    case 6:
        FUN_00e777a0(a, b, a3, r->pos, &r->normal, dt);
        break;
    case 7: {
        const float* pos = r->pos;
        const Vec3* nrm = &r->normal;
        __asm {
            push pos
            push a3
            push b
            mov eax, nrm
            mov esi, a
            call FUN_00e7b470
            add esp, 0xc
        }
        break;
    }
    case 8:
        FUN_00e72360(a, b, a3, r->pos, &r->normal, 1, dt);
        break;
    case 9: {
        if (b->b179) {
            return;
        }
        if (b->b111 != 1 && !b->b17b && !a->b178 && !FUN_00e57460(a, b)) {
            Entity* o = g_016b3c04->reg.Get(a->id);
            float len = FUN_00e6d200(o, 0, 0xb, o->u1b0);
            float f3 = 0.33333334f * len;
            uint32_t h = FUN_00e51ee0(1, len, a->id, b->id, a3, -1, 3, b->u108, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0);
            void (__cdecl* cb)() = FUN_00e7db80;
            __asm {
                mov eax, h
                push cb
                call FUN_00e528d0
                add esp, 4
            }
            __asm {
                push f3
                push 0
                mov eax, h
                call FUN_00e528f0
                add esp, 8
            }
            uint32_t idB = b->id;
            Entity* ea = g_016b3c04->reg.GetOwner(a->id);
            if (!ea) {
                return;
            }
            if (ea->b112) {
                return;
            }
            switch (ea->state) {
            case 0: case 1: case 2: case 3:
            case 0x12: case 0x13: case 0x14: case 0x15: case 0x16:
            case 0x18: case 0x19: case 0x1a: case 0x1b: case 0x1d:
            case 0x28: case 0x30: case 0x32: case 0x33:
                ea->state = 0xb;
                FUN_00e57a10(ea, a3);
                break;
            default:
                break;
            }
            Entity* eb = g_016b3c04->reg.GetOwner(idB);
            if (!eb) {
                return;
            }
            ea->b178 = 1;
            eb->b179 = 1;
            eb->b17f = 1;
            Transform t;
            FUN_00e68000(ea, a3, &t);
            if (f3 > 0.0f) {
                if (eb->p370) {
                    FUN_00e59200(eb->p370);
                }
                eb->flag4 = 1;
                FUN_00e5f4d0(eb->id, 0.0f, f3);
                ea->u170 = idB;
                return;
            }
            eb->flag4 = 1;
            FUN_00e62380(ea, a3, eb, &t, 0.0f);
            return;
        }
        break;
    }
    case 10: {
        __asm {
            push 2
            push a3
            push a
            mov esi, b
            call FUN_00e7e020
            add esp, 0xc
            mov ok, al
        }
        if (ok) {
            return;
        }
        break;
    }
    case 11:
        __asm {
            push a3
            push a
            mov esi, b
            call FUN_00e72910
            add esp, 8
            mov ok, al
        }
        if (ok) {
            return;
        }
        break;
    case 12:
        __asm {
            push a3
            mov esi, b
            mov edi, a
            call FUN_00e727e0
            add esp, 4
            mov ok, al
        }
        if (ok) {
            return;
        }
        break;
    case 13:
        __asm {
            push a3
            mov esi, b
            mov edi, a
            call FUN_00e725c0
            add esp, 4
            mov ok, al
        }
        if (ok) {
            return;
        }
        break;
    case 14:
        if (!FUN_00e57460(a, b)) {
            FUN_00e70a90(a, a3, 0x25, &r->normal, dt);
            Negate(&neg, r->normal);
            FUN_00e70a90(b, r->a4, 0x25, &neg, dt);
        }
        break;
    case 15:
        if (!FUN_00e57460(a, b)) {
            FUN_00e70a90(a, a3, 0x26, &r->normal, dt);
            Negate(&neg, r->normal);
            FUN_00e70a90(b, r->a4, 0x26, &neg, dt);
        }
        break;
    case 16:
        if (!FUN_00e57460(a, b)) {
            FUN_00e70a90(a, a3, 0x27, &r->normal, dt);
            Negate(&neg, r->normal);
            FUN_00e70a90(b, r->a4, 0x27, &neg, dt);
        }
        break;
    case 17: {
        int now = g_016b3c04->cell->time;
        if (b->lastTime + 2000 >= now) {
            return;
        }
        b->lastTime = now;
        Negate(&neg, r->normal);
        FUN_00e7a7c0(a, b, &neg, 3, 1, dt);
        return;
    }
    case 18:
        __asm {
            push b
            mov esi, a
            call FUN_00e7b630
            add esp, 4
        }
        break;
    case 19:
        FUN_00e7b5d0(a, b);
        return;
    case 20:
        FUN_00e732d0(a, b, a3, r->a4, &r->normal);
        break;
    case 21:
        if (FUN_00e73140(a, b, a3)) {
            return;
        }
        break;
    default:
        return;
    }
    Finish(r, dt);
}

// ---------------------------------------------------------------------------
// Collision-pair setup (00e7f140) and the cell-game rollover tick (00e7f5a0).
// ---------------------------------------------------------------------------
struct Handle {
    uint32_t mValue;                  // resource handle, ref-counted through +0xc
};

struct TriggerMgr {
    char pad00[0x2c];
    int  mMode;                       // +0x2c
};

struct GfxObject {
    void FUN_00e02e80();              // 0x00e02e80 (thiscall, no args)
};

struct CellGfx {
    char       pad00[0x48];
    float      rect[2];               // +0x48 screen rect
    char       pad50[0x98 - 0x50];
    GfxObject* mpObject;              // +0x98
    char       pad9c[0x936 - 0x9c];
    uint8_t    b936;                  // +0x936
};
extern CellGfx* g_016b3c0c;           // 0x016b3c0c gspCellGfx

void __fastcall FUN_00743b50(Handle* h);                    // 0x00743b50 VecClear
Entity* __cdecl FUN_00e4cc40(uint32_t resource, Handle* out); // 0x00e4cc40 ResourceGetFromHandle
void __fastcall FUN_00e82130(Handle* h);                    // 0x00e82130 release handle
void __cdecl FUN_00e73dd0(CollisionResult* r, Entity* a, Entity* b,
                          Entity* ea, Entity* eb);          // 0x00e73dd0
void __cdecl FUN_00e7e130(float f, int a, int b);           // 0x00e7e130
bool __cdecl FUN_00e7f550();                                // 0x00e7f550
TriggerMgr* __cdecl FUN_00b3d4d0();                         // 0x00b3d4d0 GetTriggerMgr
bool __cdecl FUN_00e00ac0();                                // 0x00e00ac0
void __cdecl toggle(int control, bool value);               // 0x00e53660

// @ 0x00e7f140
void __cdecl FUN_00e7f140(Entity* a, Entity* b, float dt)
{
    if (a->id == b->id)
        return;

    Entity* pa = a;
    Entity* pb = b;

    FUN_00743b50((Handle*)&a);
    Entity* ea = FUN_00e4cc40(pa->u108, (Handle*)&a);

    FUN_00743b50((Handle*)&b);
    Entity* eb = FUN_00e4cc40(pb->u108, (Handle*)&b);

    if (ea->u_b4 != 0 && eb->u_b4 != 0) {
        CollisionResult r;
        r.id0 = 0;
        r.id1 = 0;
        r.type = 0;
        r.a3 = 0;
        r.a4 = 0;
        r.f14 = 0.0f;

        FUN_00e73dd0(&r, pa, pb, ea, eb);
        FUN_00e73dd0(&r, pb, pa, eb, ea);

        if (r.type != 0 && r.type != 0x16)
            sExecuteCollisionResult(&r, dt);
    }

    FUN_00e82130((Handle*)&b);
    FUN_00e82130((Handle*)&a);
}

// @ 0x00e7f5a0
void __cdecl FUN_00e7f5a0()
{
    Entity* e = g_016b3c04->reg54.GetOwner(g_016b3c04->mField5194);
    g_016b3c04->mField5194 = 0;

    if (e != 0) {
        FUN_00e7e130(0.0f, 1, 0);
        FUN_00e7f550();
        return;
    }

    TriggerMgr* tm = FUN_00b3d4d0();
    if (tm->mMode == 1 || tm->mMode == 2)
        return;

    CellGfx* gfx = g_016b3c0c;
    if (gfx->b936 != 0)
        return;

    gfx->mpObject->FUN_00e02e80();
    toggle(2, FUN_00e00ac0());
}

// ---------------------------------------------------------------------------
// Collision-pair sweep (00e7f260), the per-frame cell-game update (00e7f3a0)
// and the rollover chain (00e7f550).
// ---------------------------------------------------------------------------

extern uint32_t __cdecl FUN_00bbb110(void* grid);                    // 0x00bbb110 StarGridCount
extern void*    __cdecl FUN_00bbbe20(void* grid, uint32_t* cursor);  // 0x00bbbe20 StarGridNextFree
extern void     __cdecl FUN_00e654d0();                              // 0x00e654d0
extern "C" void FUN_00e6d790();                                      // 0x00e6d790  esi = e, edi = out vec, stack: out radius

// Plain-C view of 0x00e6d790 (real ABI: ESI = entity, EDI = Vec3 out, radius pointer on the stack).
void __cdecl EntityPosRadius(Entity* e, Vec3* outPos, float* outRadius);

// @ 0x00e7f260
void __cdecl FUN_00e7f260(float dt)
{
    uint32_t count = FUN_00bbb110(g_016b3c04->grid);
    uint32_t* p = (uint32_t*)FUN_00bbbe20(g_016b3c04->grid, &count);

    while (p != 0) {
        Entity* a = g_016b3c04->reg.GetOwner(p[0]);
        if (a != 0) {
            Entity* b = g_016b3c04->reg.GetOwner(p[1]);
            if (b != 0) {
                Vec3 pa, pb;
                float ra, rb;
                // 0x00e6d790 takes the entity in ESI and the position output in EDI (register ABI); called
                // through a plain-C view, so these two call sites differ from the original's
                EntityPosRadius(a, &pa, &ra);
                EntityPosRadius(b, &pb, &rb);
                float dx = pa.x - pb.x;
                float dy = pa.y - pb.y;
                float dz = pa.z - pb.z;
                float s = rb + ra;
                if (dx * dx + dy * dy + dz * dz < s * s)
                    FUN_00e7f140(a, b, dt);
            }
        }
        p = (uint32_t*)FUN_00bbbe20(g_016b3c04->grid, &count);
    }

    FUN_00e654d0();
}

// @ 0x00e7f550
bool __cdecl FUN_00e7f550()
{
    uint32_t id = g_016b3c04->mField5194;
    Entity* e = g_016b3c04->reg54.GetOwner(id);
    g_016b3c04->mField5194 = 0;

    if (e != 0) {
        FUN_00e7e130(0.0f, 1, 0);
        FUN_00e7f550();
    }

    return e != 0;
}

extern float g_16b3dd0;                    // 0x016b3dd0 360.0f
extern int   g_1483c34[];                  // 0x01483c34 level threshold table (stride 7 dwords)
extern int   g_1483c14[];                  // 0x01483c14 level value table
extern int   g_1483e60;                    // 0x01483e60 special level row

extern void __cdecl FUN_00e5ff70(float dt);            // 0x00e5ff70
extern void __cdecl FUN_00e73e50(float dt);            // 0x00e73e50
extern "C" void __cdecl FUN_00e50810();                // 0x00e50810 (rect passed in esi)
extern "C" void __cdecl FUN_00e59ee0(float dt);        // 0x00e59ee0 SP::sUpdateFluidParticles
extern void __cdecl FUN_00e7d370(int key, void* grid, int zero); // 0x00e7d370
extern void __cdecl FUN_00e87000();                    // 0x00e87000
extern void __cdecl thunk_FUN_00bbb2e0(void* grid);    // 0x00bbbdf0 StarGridMeasure
extern void __cdecl FUN_00e52ae0(float dt);            // 0x00e52ae0
extern void __cdecl FUN_00e59e80();                    // 0x00e59e80
extern void __cdecl FUN_00e7e7a0(float dt);            // 0x00e7e7a0
extern void __cdecl FUN_00e7c8c0(float dt);            // 0x00e7c8c0 SP_sUpdateCells
extern void __cdecl FUN_00e5af30();                    // 0x00e5af30
extern void __cdecl FUN_00e7ad70(float dt);            // 0x00e7ad70
extern void __cdecl FUN_00e5d5b0(float dt);            // 0x00e5d5b0 pickup
extern void __cdecl FUN_00e78d10();                    // 0x00e78d10
extern void __cdecl FUN_00e697e0(float dt);            // 0x00e697e0 HUD

// @ 0x00e7f3a0  SP::sUpdateGame
namespace SP {
void __cdecl sUpdateGame(float dt);
}

void __cdecl SP::sUpdateGame(float dt)
{
    g_016b3c04->reg.GetOwner(g_016b3c04->mField411c);
    g_016b3c04->b51da = 0;
    FUN_00e5ff70(dt);

    float* period = &g_016b3c04->f14;
    if (*period == 0.0f) {
        g_016b3c04->f08 = g_016b3c04->fc;
    } else {
        float* phase = &g_016b3c04->f18;
        *phase = *phase + dt;
        if (*period < *phase) {
            do {
                *phase = *phase - *period;
            } while (*period < *phase);
        }
        g_016b3c04->f08 = (float)(sin((double)(*phase / *period) * 360.0) * g_016b3c04->f10
                                  + g_016b3c04->fc);
    }

    FUN_00e73e50(dt);

    __asm {
        mov esi, dword ptr [g_016b3c0c]
        add esi, 0x48
        call FUN_00e50810
    }

    FUN_00e59ee0(dt);

    int level = g_016b3c04->cell->level;
    int* row;
    if (level == 1000) {
        row = &g_1483e60;
    } else {
        int i = 0;
        if (level >= 0) {
            int* p = g_1483c34;
            do { p += 7; ++i; } while (level >= *p);
        }
        row = &g_1483c14[i * 7];
    }
    FUN_00e7d370(*row, &g_016b3c04->field4128, 0);
    FUN_00e87000();
    thunk_FUN_00bbb2e0(g_016b3c04->grid);

    FUN_00e52ae0(dt);
    FUN_00e59e80();
    FUN_00e7e7a0(dt);
    FUN_00e7c8c0(dt);
    FUN_00e5af30();
    FUN_00e7ad70(dt);
    FUN_00e7f260(dt);
    FUN_00e5d5b0(dt);
    FUN_00e78d10();
    FUN_00e697e0(dt);
}
