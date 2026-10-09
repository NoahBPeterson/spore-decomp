// Steering update for a locomotive creature (UpdateSteering-style per-frame function at 0xC2D220).
// Struct layouts are retail offsets (stubs); callees are masked relocations.
#include "types.h"
#include <string.h>
#include <math.h>
#include <float.h>

struct Vector3 { float x, y, z; };

inline bool TestBit(unsigned v, unsigned n) { return ((v >> n) & 1) != 0; }
#define LO ((Loco*)((char*)c + 0xc0))
#define F(T, p, off) (*(T*)((char*)(p) + (off)))

struct StEntry { uint32_t d[15]; };

// Navigation/steering state returned by Loco::GetState (0xC41EC0).
struct St {
    StEntry* begin;            // +0x00
    StEntry* end;              // +0x04
    uint32_t pad0[3];
    Vector3 pos;               // +0x14
    float f20;                 // +0x20
    uint32_t pad1[10];
    uint8_t flags4c;           // +0x4c
    uint8_t pad2[3];
    Vector3 dir;               // +0x50
    int mode;                  // +0x5c
    uint32_t pad3;
    float f64;                 // +0x64
    float f68;                 // +0x68
    uint32_t pad4;
    uint8_t flags70;           // +0x70
    void F47520(const StEntry* e);
};

struct Obj3 {
    virtual void pad0();
    virtual void pad1();
    virtual void pad2();
    virtual void pad3();
    virtual void pad4();
    virtual void pad5();
    virtual void pad6();
    virtual void pad7();
    virtual void pad8();
    virtual void pad9();
    virtual void pad10();
    virtual void pad11();
    virtual void pad12();
    virtual void pad13();
    virtual void pad14();
    virtual void pad15();
    virtual void pad16();
    virtual void pad17();
    virtual void pad18();
    virtual void pad19();
    virtual void pad20();
    virtual void pad21();
    virtual void pad22();
    virtual void pad23();
    virtual void pad24();
    virtual void pad25();
    virtual void pad26();
    virtual void pad27();
    virtual void pad28();
    virtual float V74();   // slot 29
};
struct Obj2 {
    virtual void pad0();
    virtual void pad1();
    virtual void pad2();
    virtual void pad3();
    virtual void pad4();
    virtual void pad5();
    virtual void pad6();
    virtual void pad7();
    virtual void pad8();
    virtual void pad9();
    virtual void pad10();
    virtual Vector3* GetPosition();   // slot 11
};
struct Obj1 {
    virtual void pad0();
    virtual void pad1();
    virtual Obj2* Get8();   // slot 2
};

// Locomotive object (vtable at +0); also embedded in the creature at +0xC0.
struct Loco {
    virtual void pad0();
    virtual void pad1();
    virtual void pad2();
    virtual void pad3();
    virtual void pad4();
    virtual void pad5();
    virtual void pad6();
    virtual void pad7();
    virtual void pad8();
    virtual void pad9();
    virtual void pad10();
    virtual Vector3* GetPosition();                // slot 11 (+0x2c)
    virtual void pad12();
    virtual void pad13();
    virtual void pad14();
    virtual void pad15();
    virtual void pad16();
    virtual void pad17();
    virtual void pad18();
    virtual void pad19();
    virtual void pad20();
    virtual void pad21();
    virtual void pad22();
    virtual Vector3* GetHeading(Vector3* out);     // slot 23 (+0x5c)
    virtual void pad24();
    virtual void pad25();
    virtual void pad26();
    virtual void pad27();
    virtual void pad28();
    virtual float GetRadius();                     // slot 29 (+0x74)
    virtual void pad30();
    virtual void pad31();
    virtual void pad32();
    virtual void pad33();
    virtual void pad34();
    virtual void pad35();
    virtual void pad36();
    virtual void pad37();
    virtual void pad38();
    virtual void pad39();
    virtual void pad40();
    virtual void pad41();
    virtual void pad42();
    virtual void pad43();
    virtual void pad44();
    virtual void pad45();
    virtual void* Query(unsigned id);              // slot 46 (+0xb8)
    virtual void pad47();
    virtual void pad48();
    virtual void* V_c4(float f, int i);              // slot 49 (+0xc4)
    virtual float GetDesiredSpeed();                 // slot 50 (+0xc8)
    virtual void pad51();
    virtual void pad52();
    virtual void pad53();
    virtual void pad54();
    virtual void V_dc(void* p);                      // slot 55 (+0xdc)
    Vector3* GetVelocity();   // 0xd20610
    bool IsNearGoal();   // 0xc42e20
    void UpdateSteeringForMovementStyle();   // 0xc44610
    St* GetState();                                  // 0xC41EC0
    bool Within(float a, float b);                   // 0xC41ED0
    float* F421f0();   // 0xc421f0
    void F44080(Vector3* out);   // 0xc44080
};

struct Sub15b8 {
    void F9ce740(float f);   // 0x9ce740
};

struct Anim {
    virtual void pad0();
    virtual void pad1();
    virtual void pad2();
    virtual void pad3();
    virtual void pad4();
    virtual void pad5();
    virtual void pad6();
    virtual void pad7();
    virtual void pad8();
    virtual void pad9();
    virtual void pad10();
    virtual void pad11();
    virtual void pad12();
    virtual void pad13();
    virtual void pad14();
    virtual void pad15();
    virtual void pad16();
    virtual void pad17();
    virtual void pad18();
    virtual void pad19();
    virtual void pad20();
    virtual void pad21();
    virtual void Q58(int* out, int a, int b, void** p);   // slot 22 (+0x58)
    virtual bool Q5c(void* p, float* den, float* num);    // slot 23 (+0x5c)
    bool IsOrientStartAnim(int id);   // 0xa02710
};

struct Creature {
    virtual void pad0();
    virtual void pad1();
    virtual void pad2();
    virtual void pad3();
    virtual void pad4();
    virtual void pad5();
    virtual void pad6();
    virtual void pad7();
    virtual unsigned GetType();    // slot 8 (+0x20)
    int GetStyle();                      // 0xC0C2F0
    Obj1* F0ee60();                      // 0xC0EE60
    Vector3* F290d0(Vector3* out, St* st, ...);   // 0xC290D0
};

struct Ctx {
    Vector3 out;     // +0x00
    uint32_t pad[1];
    float f10;       // +0x10
    Loco* obj;       // +0x14
};

struct Info2b110 { uint32_t pad[1]; int f4; float f8; };
struct Info532b0 { uint32_t pad[0x33]; int fcc; };
void operator delete[](void* p);   // 0x00f47380
struct ArrObj {
    void* p;
    uint32_t rest[0x1c];
    ArrObj();   // 0xac9850
    ~ArrObj() { if (p && ((int*)p)[-1] != 0) operator delete[](p); }
};

extern uint8_t g_169e381, g_169e37e, g_169e37f;
extern float g_169e384, g_169e388, g_169e38c, g_169e390;
extern Vector3 g_168dd78;

unsigned GetCurrentGameMode();   // 0xb5b800
void F2a190(Ctx* ctx, Creature* c);   // 0xc2a190
void F28290(Creature* c, Vector3* p, float* dist);   // 0xc28290
Info532b0* F0b532b0(Loco* l);   // 0xb532b0
char F28870(Ctx* ctx, Creature* c, Vector3* pos, St* st);   // 0xc28870
Info2b110* F2b110(Creature* c);   // 0xc2b110
void F0cadb50(Info2b110* p);   // 0xcadb50
void F289b0(Ctx* ctx, Creature* c, St* st, bool nearFlag, float dist);   // 0xc289b0
char F2c7b0(Creature* c, St* st, Vector3* heading, float* scale, const int& style);   // 0xc2c7b0
void F2cac0(Creature* c, Vector3* heading, St* st, bool* nearFlag, float* dist, float* scale, const int& style);   // 0xc2cac0
char F283d0(Ctx* ctx, Creature* c);   // 0xc283d0
void F28700(Ctx* ctx, Creature* c, St* st, Vector3* heading, float dist, float st20, float* speed);   // 0xc28700
float F29b10(Creature* c, Vector3* heading, Vector3* goal, float f10, float speed, float turn, int flag);   // 0xc29b10
float F29d80(Vector3* heading, float f10, float speed, float turn);   // 0xc29d80
char F28b40(Ctx* ctx, Creature* c, Vector3* dir, char f7c);   // 0xc28b40
void F29940(Creature* c);   // 0xc29940
void normalized_safe(Vector3* out, const Vector3* in);   // 0x449c20
char F41dd30(const Vector3* v, const Vector3* ref);   // 0x41dd30
Vector3* Vector3_Normalize(Vector3* out, const Vector3* in);   // 0x436ce0

// @ 0xC2D220
void __stdcall F00c2d220(Ctx* ctx)
{
    Creature* c = ctx->obj ? (Creature*)ctx->obj->Query(0xce9f6639) : 0;
    Creature* cc = c;
    if (!c || c->GetType() != 0x18eb45e)
        cc = 0;

    uint8_t flagA = F(uint8_t, c, 0x137);
    bool flagB = (F(unsigned, c, 0x110) & 0x1000) == 0x1000;
    St* st = ctx->obj->GetState();
    bool isMode = GetCurrentGameMode() == 0x1654c10;

    if (!flagA) {
        if (!flagB) {
            F2a190(ctx, c); // 0x00c2a190
            return;
        }
        if (TestBit(F(unsigned, c, 0xb58), 9) && st->mode == 0 && !g_169e381) {
            Vector3* v = LO->GetVelocity();
            ctx->out = *v;
            return;
        }
    }

    ctx->obj->GetVelocity();
    int style = c->GetStyle();
    Vector3* pp = ctx->obj->GetPosition();
    Vector3 pos;
    pos.x = pp->x; pos.y = pp->y; pos.z = pp->z;
    float inv = 1.0f / (float)sqrt(pos.x * pos.x + pos.z * pos.z + pos.y * pos.y + 1e-8f);
    Vector3 up;
    up.x = inv * pos.x; up.y = inv * pos.y; up.z = inv * pos.z;
    Vector3 heading;
    ctx->obj->GetHeading(&heading);
    float speed = ctx->obj->GetDesiredSpeed();
    float turn = F(float, ctx->obj, 0x1e8);
    float st20 = st->f20;
    bool isMode0 = st->mode == 0;
    float dist;
    if (isMode0) {
        dist = 0.0f;
    } else {
        float dx = pos.x - st->pos.x;
        float dy = pos.y - st->pos.y;
        float dz = pos.z - st->pos.z;
        dist = (float)sqrt(dx * dx + dz * dz + dy * dy);
    }
    bool arrived;
    bool near_;
    if (ctx->obj->IsNearGoal() && !(st->flags70 & 4)) near_ = true; else near_ = false;
    arrived = near_;
    bool f13;
    if (st->mode == 3 || F(uint8_t, c, 0xb5c)) f13 = false; else f13 = true;
    float scale = 1.0f;
    F(uint8_t, F(char*, F(Anim*, c, 0xb54), 0x17c), 0x168c) = 1;
    Info532b0* x532 = F0b532b0(LO);
    bool f7c;
    if (flagA && x532 && x532->fcc == 3) f7c = true; else f7c = false;
    if (!isMode0)
        F28290(c, &st->pos, &dist);
    ((Sub15b8*)(F(char*, F(Anim*, c, 0xb54), 0x17c) + 0x15b8))->F9ce740(0.0f);
    if (F(unsigned, c, 0x330) & 4) {
        ctx->out.x = 0.0f; ctx->out.y = 0.0f; ctx->out.z = 0.0f;
        return;
    }
    if (arrived) {
        F(unsigned, c, 0x330) &= 0xfffffff4;
        goto L71a;
    }
    if (st->mode == 0)
        goto L71a;

    {
        bool f12 = F(float, ctx->obj, 0x1a0) != 0.0f;
        near_ = ctx->obj->Within(dist * dist, st20);
        if (f12) {
            F0cadb50(F2b110(c));
            F(unsigned, c, 0x330) &= 0xfffffff4;
            if (!F28870(ctx, c, &pos, st))
                return;
        }
        arrived = f12;
        if (!f12) {
            float lim;
            switch (style) {
            case 0: lim = 2.0f; break;
            case 1: lim = 1.0f; break;
            case 2: lim = 0.5f; break;
            default: lim = FLT_MAX; break;
            }
            float cur = F(float, ctx->obj, 0x1a0);
            if (cur > lim) {
                arrived = true;
                F(float, ctx->obj, 0x1a0) = cur - lim;
            }
        } else {
            if (style >= 0 && style <= 1)
                arrived = F(uint8_t, c, 0xf90) != 0;
        }
        F289b0(ctx, c, st, near_, dist);
        if (near_) {
            StEntry* b = st->begin;
            if (b == st->end) {
                arrived = false;
                if (st->mode != 3 && st->mode != 2)
                    speed = 0.0f;
                goto L66c;
            }
            if (st->flags4c & 1)
                arrived = true;
            memcpy(&st->pos, b, sizeof(StEntry));
            st->F47520(b);
            F28290(c, &st->pos, &dist);
            near_ = false;
        }
        if (!arrived)
            goto L66c;
        if (TestBit(F(unsigned, c, 0xb58), 9)) {
            if (g_169e381 || g_169e37e || isMode) {
                arrived = false;
                goto L66c;
            }
        }
        if (f12)
            goto L66c;
        if (!(st->flags4c & 1))
            goto L66c;
        arrived = F2c7b0(c, st, &heading, &scale, style) != 0;
        goto L693;
    L66c:
        {
            Info2b110* r = F2b110(c);
            if (r->f4 != 0 && 1.0f > r->f8)
                scale = r->f8;
        }
    L693:
        if (arrived)
            F2cac0(c, &heading, st, &near_, &dist, &scale, style);
        if (F283d0(ctx, c))
            return;
        if (!near_ && style > 0 && st->mode != 2 && !(st->flags70 & 1))
            F28700(ctx, c, st, &heading, dist, st20, &speed);
        st->f68 = dist;
    }

L71a:
    Vector3 dir;
    Vector3 goal;
    Vector3 tmp;
    float retSpeed;
    bool reached;
    ctx->obj->UpdateSteeringForMovementStyle();
    ctx->obj->F44080(&dir);
    {
        float len = (float)sqrt(dir.y * dir.y + dir.z * dir.z + dir.x * dir.x);
        if (len >= 1.5258789e-05f) {
            if (len > 1.0f || len < 1.0f) {
                float s = 1.0f / len;
                dir.x = s * dir.x;
                dir.y = s * dir.y;
                dir.z = s * dir.z;
            }
        } else {
            dir.x = heading.x; dir.y = heading.y; dir.z = heading.z;
        }
    }
    uint8_t bit9 = (uint8_t)TestBit(F(unsigned, c, 0xb58), 9);
    if (st->mode == 0) {
        speed = 0.0f;
        goto L9d9;
    }
    if (speed > 0.0f && (!near_ || !f13) && cc && F(uint8_t, cc, 0xf90)) {
        void* animPtr = 0;
        int animId;
        F(Anim*, cc, 0xb54)->Q58(&animId, 0, 0, &animPtr);
        if (F(Anim*, cc, 0xb54)->IsOrientStartAnim(animId)) {
            float num = 0.0f;
            float den = 0.0f;
            if (!F(Anim*, cc, 0xb54)->Q5c(animPtr, &den, &num)) {
                turn = 0.0f;
                speed = 0.0f;
            } else {
                float t = num / den;
                t = (t > 0.0f) ? t : 0.0f;
                t = (t < 1.0f) ? t : 1.0f;
                speed = t * speed;
                turn = t * turn;
            }
        }
    }
L9d9:
    float maxDist;
    {
        float cap = 20.0f;
        float* p = LO->F421f0() + 3;
        const float* m = (cap > *p) ? &cap : p;
        maxDist = *m;
    }
    reached = false;
    if (st->mode == 4) {
        Vector3* p = LO->GetPosition();
        goal.x = p->x + st->dir.x;
        goal.y = p->y + st->dir.y;
        goal.z = p->z + st->dir.z;
    } else if (F(uint8_t, c, 0xb5c) && c->F0ee60()) {
        if (!isMode) {
            Obj2* o2 = c->F0ee60()->Get8();
            Vector3* p2 = o2->GetPosition();
            Vector3* mp = LO->GetPosition();
            goal.x = mp->x - p2->x;
            goal.y = mp->y - p2->y;
            goal.z = mp->z - p2->z;
            Obj3* o3 = (Obj3*)c->F0ee60()->Get8();
            float r1 = o3->V74();
            float r0 = LO->GetRadius();
            float d = maxDist - (r0 + r1);
            float t = (0.0f > d) ? 0.0f : d;
            if (t * t <= goal.x * goal.x + goal.z * goal.z + goal.y * goal.y)
                goto Lbaa;
        }
        {
            Vector3* gp = c->F0ee60()->Get8()->GetPosition();
            goal = *gp;
            reached = true;
        }
    } else {
    Lbaa:
        if (near_) {
            float r = LO->GetRadius();
            goal.x = st->pos.x + dir.x * r;
            goal.y = st->pos.y + r * dir.y;
            goal.z = st->pos.z + r * dir.z;
        } else if (F(uint8_t, F(char*, F(Anim*, c, 0xb54), 0x17c), 0x2d5)) {
            Vector3* r = c->F290d0(&tmp, st);
            goal.x = r->x + pos.x;
            goal.y = r->y + pos.y;
            goal.z = r->z + pos.z;
        } else {
            st20 = LO->GetRadius() + st20;
            if (st->begin != st->end && !(dist > st20)) {
                Vector3* b = (Vector3*)st->begin;
                tmp.x = b->x - st->pos.x;
                tmp.y = b->y - st->pos.y;
                tmp.z = b->z - st->pos.z;
                normalized_safe(&goal, &tmp);
                float t = dist / st20;
                float s = (t * t) * 3.0f - ((t * t) * t) * 2.0f;
                float s1 = 1.0f - s;
                goal.x = (s * dir.x + pos.x) + goal.x * s1;
                goal.y = (s * dir.y + pos.y) + goal.y * s1;
                goal.z = (s * dir.z + pos.z) + goal.z * s1;
            } else {
                goal.x = dir.x + pos.x;
                goal.y = dir.y + pos.y;
                goal.z = dir.z + pos.z;
            }
        }
    }

    if (!bit9) {
        if (!F(uint8_t, F(char*, F(Anim*, c, 0xb54), 0x17c), 0x2d5))
            retSpeed = F29b10(c, &heading, &goal, ctx->f10, speed, turn, 0);
        else
            retSpeed = F29d80(&heading, ctx->f10, speed, turn);
    } else {
        retSpeed = speed;
        if (cc) {
            bool ok = true;
            if (reached && !g_169e37e) {
                if (!cc->F0ee60() || !F(uint8_t, cc, 0xb5c))
                    ok = false;
            }
            if (ok) {
                if (g_169e381 && g_169e37f && !reached) {
                    float dot = heading.x * g_169e388 + heading.y * g_169e38c + heading.z * g_169e390;
                    if (dot > 0.0f) {
                        goal.x = pos.x + g_169e388;
                        goal.y = g_169e38c + pos.y;
                        goal.z = pos.z + g_169e390;
                    } else {
                        goal.x = pos.x - g_169e388;
                        goal.y = pos.y - g_169e38c;
                        goal.z = pos.z - g_169e390;
                    }
                }
                retSpeed = F29b10(c, &heading, &goal, ctx->f10, speed, turn, bit9);
            }
        }
    }

    if (retSpeed > 0.0f || (bit9 && g_169e384 > 0.0f)) {
        if (!bit9 || !g_169e381) {
            ctx->out.x = dir.x * speed;
            ctx->out.y = dir.y * speed;
            ctx->out.z = dir.z * speed;
        } else if (GetCurrentGameMode() == 0x1654c05) {
            const float* m = (speed > g_169e384) ? &g_169e384 : &speed;
            ctx->out.x = *m * dir.x;
            ctx->out.y = *m * dir.y;
            ctx->out.z = *m * dir.z;
        } else {
            ctx->out.x = g_169e388 * g_169e384;
            ctx->out.y = g_169e38c * g_169e384;
            ctx->out.z = g_169e390 * g_169e384;
        }
    } else {
        ctx->out.y = 0.0f;
        ctx->out.z = 0.0f;
        ctx->out.x = 0.0f;
    }

    if (!F28b40(ctx, c, &dir, f7c))
        return;
    F29940(c);
    if (near_) {
        bool doReset = f13;
        if (!doReset) {
            tmp.x = goal.x - st->pos.x;
            tmp.y = goal.y - st->pos.y;
            tmp.z = goal.z - st->pos.z;
            normalized_safe(&goal, &tmp);
            float dot = up.x * goal.x + goal.z * up.z + goal.y * up.y;
            tmp.x = goal.x - up.x * dot;
            tmp.y = goal.y - dot * up.y;
            tmp.z = goal.z - dot * up.z;
            if (F41dd30(&tmp, &g_168dd78)) {
                Vector3* r = Vector3_Normalize(&heading, &tmp);
                goal = *r;
            }
            Vector3 hd;
            Vector3* h = ctx->obj->GetHeading(&hd);
            float dot2 = h->y * goal.y + h->z * goal.z + h->x * goal.x;
            doReset = dot2 > st->f64;
            if (!doReset) {
                Vector3* sp = &ctx->obj->GetState()->pos;
                sp->x = pos.x; sp->y = pos.y; sp->z = pos.z;
                if (F(int, ctx->obj, 0x1f0) == 0 && F41dd30(&pos, &g_168dd78)) {
                    float d3 = st->dir.z * up.z + st->dir.y * up.y + up.x * st->dir.x;
                    tmp.x = st->dir.x - up.x * d3;
                    tmp.y = st->dir.y - d3 * up.y;
                    tmp.z = st->dir.z - d3 * up.z;
                    if (F41dd30(&tmp, &g_168dd78)) {
                        Vector3* r = Vector3_Normalize(&heading, &tmp);
                        st->dir.x = r->x; st->dir.y = r->y; st->dir.z = r->z;
                    }
                }
            }
        }
        if (doReset) {
            Loco* o = ctx->obj;
            {
                ArrObj a;
                o->V_dc(&a);
            }
            ctx->obj->V_c4(0.0f, 1);
        }
        ctx->out.z = 0.0f;
        ctx->out.y = 0.0f;
        ctx->out.x = 0.0f;
    }
    if (1.0f > scale) {
        ctx->out.x = ctx->out.x * scale;
        ctx->out.y = scale * ctx->out.y;
        ctx->out.z = ctx->out.z * scale;
    }
}
// --- equivalence checker address annotations
    void F0b532b0(...); // 0x00b532b0
    void F2a190(...); // 0x00c2a190
    void GetCurrentGameMode(...); // 0x00b5b800

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct Loco {
    void IsNearGoal(); // 0x00c42e20
    void GetVelocity(); // 0x00d20610
};
}
