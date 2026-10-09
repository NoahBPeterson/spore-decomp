// Locomotive sweep test: moves a sphere of radius ctx->radius along origin + dir * t, queries the model
// world for nearby objects, classifies each by its type id (a switch over resource ids), and runs the
// swept-sphere / mesh tests against the ones that matter. Returns the remaining travel distance.
#include "types.h"
#include <math.h>

struct Vec3 { float x, y, z; };

#define AT(T, p, off) (*(T*)((char*)(p) + (off)))
#define VT(p) (*(void***)(p))

// ---- stub classes for the callees (addresses are masked relocations) ----
struct Goal {
    float* mpPoints;          // +0x00: array of 0x3c-byte records, xyz first
    char pad04[0x10];
    Vec3 target;              // +0x14
    char pad20[0x3c];
    int mActive;              // +0x5c
    unsigned Count();         // FUN_00ac15f0
};

struct Loco {                 // SP::cLocomotiveObject sub-object (at owner + 0x34)
    Vec3* GetVelocity();      // 0xd20610
    Goal* GetGoal();          // 0xc41ec0
    bool IsNearGoal();        // 0xc42e20
};

struct Transform {
    char d[0x3c];
    Transform();   // 0x409930
};

struct Mesh {
    char pad00[0x40];
    char data40[0xc];
    Vec3* mpBegin;            // +0x4c
    Vec3* mpEnd;              // +0x50
};
struct MeshRef {
    Mesh* GetMesh();   // 0xb7c360
};

struct Obj {                  // spatial object seen through the entity's component
    void LocalToWorldTransform(Transform* xf);     // 0xc897e0
};

struct Creature {
    bool Check();   // 0xc0c0e0
};
struct Flag10c {
    int Check();   // 0xc90460
};

struct Hit { void* first; void* second; };

struct HitVec {               // fixed-capacity vector of 16 hits
    Hit* mpBegin;
    Hit* mpEnd;
    Hit* mpCapacity;
    int pad0c;
    Hit* mpFixed;
    int pad14;
    Hit buf[16];
    HitVec() { mpBegin = buf; mpEnd = buf; mpCapacity = buf + 16; mpFixed = buf; }
    void erase(Hit* first, Hit* last);             // 0xd018d0
};

struct Filter { int a, b, c, d, e; char f, g; };

struct Ctx {
    void* self;
    char sub[0x18];
    float radius;
};

struct SweepOut {
    int type;
    void* hitObj;
    float hitFrac;
    int hitFlag;
    char pad10[0x10];
    int count20;
    char pad24[0x10];
    Vec3 hitVec;
};

void* __cdecl GonzagoModelWorld();
Vec3* __cdecl normalized_safe(Vec3* out, const Vec3* in);
float __cdecl Dot3(const Vec3* a, const Vec3* b);
float __cdecl FUN_00c297d0(const Vec3* origin, const Vec3* vel, const Vec3* pos, const Vec3* velV);
float __cdecl FUN_00c29880(const Vec3* origin, const Vec3* vel, const Vec3* pos, const Vec3* velV, float r);
bool __cdecl FUN_0041dd30(void* sub, const Vec3* origin);
void* __cdecl FUN_00ae6760(void* o);
void* __cdecl FUN_00cb1210(void* o);
void* __cdecl FUN_00ac80d0(void* o, unsigned id);
void* __cdecl FUN_00f19200(void* o);
void* __stdcall FUN_00b3d3c0(void* o);
bool __cdecl FUN_00af5400(SweepOut* out, void* other, const Vec3* origin, const Vec3* pos, const Vec3* seg,
                          const Vec3* dir, float* t, float one, Transform* xf, void* meshData, float rad,
                          Vec3* tris, unsigned nTris, float radius, int zero, SweepOut* out2);
bool __cdecl FUN_00af17f0(SweepOut* out, void* other, const Vec3* origin, const Vec3* pos, const Vec3* dir,
                          float* t, float one, float rr, int flag, SweepOut* out2);
void __cdecl FUN_00af7c60(const Vec3* origin, const Vec3* dir, float radius, float one, int a, int b,
                          SweepOut* out, float* t);
void __cdecl FUN_00af3e50(const Vec3* origin, const Vec3* dir, float radius, float a, float b, float c,
                          SweepOut* out, float* t, int zero);
void __cdecl FUN_00af4870(const Vec3* origin, const Vec3* dir, float radius, float a, SweepOut* out, float* t);

typedef void* (__thiscall* FnPtr1)(void*, unsigned);
typedef Vec3* (__thiscall* FnVec0)(void*);
typedef float (__thiscall* FnF0)(void*);
typedef void* (__thiscall* FnP1)(void*, void*);
typedef void* (__thiscall* FnP0)(void*);
typedef unsigned (__thiscall* FnU0)(void*);
typedef int (__thiscall* FnI0)(void*);
typedef void (__thiscall* FnWorld)(void*, const Vec3*, Vec3*, HitVec*, Filter*, float);

// @ 0x00cb1270
float __cdecl SweepTick(Ctx* ctx, const Vec3* origin, const Vec3* dir, float t, SweepOut* out)
{
    out->count20 = 0;
    void* self = ctx->self;
    if (t < 1.5258789e-05f)
        return t;

    Loco* loco = (Loco*)((char*)self + 0x34);
    loco->GetVelocity();
    float R = ctx->radius;
    Vec3 end0;
    end0.x = dir->x * t + origin->x;
    end0.y = t * dir->y + origin->y;
    end0.z = t * dir->z + origin->z;
    float t2 = t * t;
    float speed = ((FnF0)VT(loco)[50])(loco);
    unsigned flags = AT(unsigned, AT(void*, self, 0xaf0), 0x5fc);
    Vec3 vel;
    vel.x = dir->x * speed;
    vel.y = speed * dir->y;
    vel.z = speed * dir->z;

    static HitVec sHits;
    static int sCount;
    static Vec3 sZero;

    sHits.erase(sHits.mpBegin, sHits.mpEnd);
    Filter filter;
    filter.a = 0; filter.b = 0; filter.c = 0; filter.d = 0; filter.e = 0;
    filter.f = 0; filter.g = 2;
    void* world = GonzagoModelWorld();
    Vec3 seg;
    if (t > 100.0f) {
        seg.x = dir->x * 100.0f + origin->x;
        seg.y = dir->y * 100.0f + origin->y;
        seg.z = dir->z * 100.0f + origin->z;
    } else {
        seg = end0;
    }
    Vec3 seg2 = seg;
    ((FnWorld)VT(world)[12])(world, origin, &seg2, &sHits, &filter, R);

    sCount = (int)(sHits.mpEnd - sHits.mpBegin);

    unsigned i = 0;
    if (sCount != 0) {
        do {
            void* ent = sHits.mpBegin[i].first;
            void* comp;
            Obj* obj;
            float scale, rad;
            bool noB71, flag13, moving, flagB;
            Vec3 hitVec, velV, hp, tmp1, tmp2, tmp3, acc;
            const Vec3* pos;
            unsigned type;
            void* other;
            float r1d, rr;

            if (!((AT(unsigned, ent, 4) >> 14) & 1)) goto next;
            if (AT(void*, ent, 0x64) == 0) goto next;
            comp = AT(void*, ent, 0x64);
            if (comp == 0) goto next;
            obj = (Obj*)((FnPtr1)VT(comp)[3])(comp, 0x1186577);
            if (obj == 0 || AT(char, obj, 0x70) == 0) goto next;
            if (AT(char, obj, 0x75) == 0) goto next;
            if (AT(unsigned, obj, 0x50) & 0x190) goto next;

            scale = 1.0f;
            noB71 = AT(char, obj, 0x71) == 0;
            flag13 = false;
            rad = 0.0f;
            pos = ((FnVec0)VT(obj)[11])(obj);
            hitVec = sZero;
            other = ((FnPtr1)VT(obj)[46])(obj, 0x17f243b);
            type = ((FnU0)VT(other)[8])(other);
            r1d = 0.0f;
            rr = 0.0f;
            moving = false;
            flagB = false;

            switch (type) {
            case 0x18c431c:
            case 0x18c84a9:
            case 0x18c7c97:
            case 0x2a034cd:
            case 0x2c9cc91:
            case 0x2e72cae:
            case 0x74e0069:
            case 0x7b38ba7:
            case 0x52aa6122:
                goto next;

            case 0x18c6de8: {
                void* other2 = FUN_00ae6760(other);
                if (self == other2) goto next;
                if (FUN_0041dd30(ctx->sub, origin)) {
                    if (((Loco*)((char*)other2 + 0x34))->GetGoal()->mActive != 0) goto next;
                }
                if (!(0.0f < (pos->z - origin->z) * dir->z + (pos->y - origin->y) * dir->y +
                                 (pos->x - origin->x) * dir->x))
                    goto next;
                rad = ((FnF0)VT(obj)[29])(obj);
                rr = rad * 0.9f + R;
                scale = 0.9f;
                {
                    float ax = dir->x * t, ay = t * dir->y, az = t * dir->z;
                    float dx = origin->x - pos->x, dz = origin->z - pos->z, dy = origin->y - pos->y;
                    float b = dx * ax + dz * az + dy * ay;
                    float c = dz * dz + dy * dy + dx * dx - rr * rr;
                    float disc = b * b - c * t2;
                    if (!(c < 0.0f)) {
                        if (disc < 0.0f) goto next;
                        float s = (float)sqrt(disc);
                        if (0.0f > s - b) goto next;
                        if (-b - s > t2) goto next;
                    }
                }
                {
                    Loco* loco2 = (Loco*)((char*)other2 + 0x34);
                    Vec3* v = loco2->GetVelocity();
                    velV = *v;
                    r1d = FUN_00c297d0(origin, &vel, pos, &velV);
                    if (1.5258789e-05f >= r1d || r1d > 10.0f) goto next;
                    if (FUN_00c29880(origin, &vel, pos, &velV, r1d) > rr) goto next;
                    if (AT(void*, FUN_00cb1210(other2), 4) == self) goto next;
                    moving = (velV.z * velV.z + velV.y * velV.y) + velV.x * velV.x > 1.5258789e-05f;
                    flagB = false;
                    if (moving) {
                        if (Dot3(normalized_safe(&tmp1, &velV), dir) > 0.7f) {
                            flagB = true;
                            goto sweepA;
                        }
                        flagB = false;
                    }
                    {
                        Goal* g = loco2->GetGoal();
                        if (g->mActive != 0 && !loco2->IsNearGoal()) {
                            float sx = pos->x, sy = pos->y, sz = pos->z;
                            acc.x = g->target.x - sx;
                            acc.y = g->target.y - sy;
                            acc.z = g->target.z - sz;
                            unsigned n = g->Count();
                            unsigned m = n > 3 ? 3 : n;
                            for (unsigned k = 0; k < m; ++k) {
                                float* e = (float*)((char*)g->mpPoints + k * 0x3c);
                                acc.x = (e[0] - sx) + acc.x;
                                acc.y = (e[1] - sy) + acc.y;
                                acc.z = (e[2] - sz) + acc.z;
                            }
                            Vec3* nv = normalized_safe(&tmp2, &acc);
                            acc = *nv;
                            if (0.7f < (acc.z * dir->z + acc.y * dir->y) + acc.x * dir->x) {
                                if (!moving) {
                                    float sp = ((FnF0)VT(loco2)[50])(loco2);
                                    velV.x = acc.x * sp;
                                    velV.y = acc.y * sp;
                                    velV.z = acc.z * sp;
                                }
                                flagB = false;
                                goto sweepA;
                            }
                        }
                    }
                    goto postSweep;
                sweepA:
                    {
                        float fracs[2];
                        fracs[0] = 0.5f;
                        fracs[1] = 0.1f;
                        for (int k = 0; k < 2; ++k) {
                            float f = fracs[k];
                            Vec3 sc;
                            sc.x = vel.x * f;
                            sc.y = vel.y * f;
                            sc.z = vel.z * f;
                            float rl = FUN_00c297d0(origin, &sc, pos, &velV);
                            if (1.5258789e-05f >= rl || rl > 10.0f) {
                                out->hitObj = other;
                                out->hitFrac = f;
                                out->hitFlag = !flagB;
                                goto next;
                            }
                            if (FUN_00c29880(origin, &sc, pos, &velV, rl) > rr) {
                                out->hitObj = other;
                                out->hitFrac = f;
                                out->hitFlag = !flagB;
                                goto next;
                            }
                        }
                    }
                postSweep:
                    {
                        Vec3* nv = normalized_safe(&tmp3, &velV);
                        hp.x = nv->x * r1d + pos->x;
                        hp.y = nv->y * r1d + pos->y;
                        hp.z = nv->z * r1d + pos->z;
                        pos = &hp;
                        hitVec = velV;
                    }
                }
                break;
            }

            case 0x18c88e4: {
                void* o = FUN_00ac80d0(other, 0x18c88e4);
                unsigned k = AT(unsigned, o, 0x228);
                if (k != 0x2ae5ba7 && k != 0x5d97f762) goto next;
                flag13 = true;
                break;
            }
            case 0x18c8f0c:
            case 0x18ea1eb:
            case 0x18ea2cc:
            case 0x18eb106:
            case 0x1a56aba:
            case 0x55cf865:
            case 0x70703b3:
                flag13 = true;
                break;
            case 0x18eb45e:
            case 0x18eb4b7: {
                Creature* c = (Creature*)FUN_00f19200(other);
                if (AT(char, c, 0xb5e) != 0 && !c->Check()) goto next;
                if (flags & 0x1000) goto next;
                if (flags & 0x4400) {
                    int a = ((FnI0)VT(c)[19])(c);
                    int b = ((FnI0)VT(self)[19])(self);
                    if (b != a) goto next;
                }
                flag13 = true;
                break;
            }
            case 0x1e4daae: {
                float dz = end0.z - pos->z, dy = end0.y - pos->y, dx = end0.x - pos->x;
                if (1.5258789e-05f > dz * dz + dy * dy + dx * dx) goto next;
                flag13 = true;
                break;
            }
            case 0x2a8fb3f:
                if (noB71) {
                    if (0.3f >= ((FnF0)VT(obj)[29])(obj)) goto next;
                    scale = 0.5f;
                }
                break;
            case 0x3a2511e:
                if (noB71) goto next;
                flag13 = true;
                break;
            case 0x629bafe: {
                void* o = FUN_00ac80d0(other, 0x629bafe);
                if (((Flag10c*)AT(void*, o, 0x10c))->Check() == 0) {
                    void* sub = (char*)o + 0x34;
                    float r = ((FnF0)VT(sub)[29])(sub);
                    const Vec3* sp = ((FnVec0)VT(sub)[11])(sub);
                    float dz = end0.z - sp->z, dy = end0.y - sp->y, dx = end0.x - sp->x;
                    if (r * r > dz * dz + dy * dy + dx * dx) goto next;
                }
                break;
            }
            default:
                break;
            }

            // common tail
            out->type = type;
            if (rad == 0.0f)
                rad = ((FnF0)VT(obj)[29])(obj);
            rad = rad * scale;
            {
                float rr2 = rad + R;
                bool ok;
                if (flag13 && !noB71) {
                    Transform xf;
                    obj->LocalToWorldTransform(&xf);
                    void* a = ((FnP0)VT(obj)[44])(obj);
                    void* b = ((FnP1)VT(obj)[43])(obj, a);
                    Mesh* mesh = ((MeshRef*)FUN_00b3d3c0(b))->GetMesh();
                    if (mesh == 0) goto next;
                    if ((unsigned)(mesh->mpEnd - mesh->mpBegin) < 3) goto next;
                    ok = FUN_00af5400(out, other, origin, pos, &end0, dir, &t, 1.0f, &xf, mesh->data40,
                                      rad, mesh->mpBegin, (unsigned)(mesh->mpEnd - mesh->mpBegin), R, 0, out);
                } else {
                    ok = FUN_00af17f0(out, other, origin, pos, dir, &t, 1.0f, rr2, noB71, out);
                }
                if (!ok) goto next;
            }
            out->hitVec = hitVec;
            if (1.5258789e-05f > t) {
                t = 0.0f;
                break;
            }
            t2 = t * t;
            end0.x = dir->x * t + origin->x;
            end0.y = t * dir->y + origin->y;
            end0.z = t * dir->z + origin->z;
        next:
            ++i;
        } while (i < (unsigned)sCount);
    }

    int mode = AT(int, self, 0xb1c);
    if (mode == 0) {
        if (t > 0.25f)
            FUN_00af7c60(origin, dir, R, 1.0f, 1, 1, out, &t);
        if (AT(char, self, 0xab) != 0) {
            float* v = (float*)((FnP0)VT(loco)[26])(loco);
            if (t > 0.25f) {
                FUN_00af3e50(origin, dir, R, 2.0f, 45.0f, (v[5] - v[2]) + 10.0f, out, &t, 0);
                return t;
            }
        }
    } else if (mode == 1) {
        FUN_00af4870(origin, dir, R, 2.0f, out, &t);
    }
    return t;
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct MeshRef {
    void GetMesh(); // 0x00b7c360
};
struct Flag10c {
    void Check(); // 0x00c90460
};
}
