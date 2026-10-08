// SP::cGroupMovement::UpdateGoals-style behavior-tree tick (0xda0780): the creature samples a ring of points
// around itself and walks to the one most directly away from its target that is not blocked by an obstacle.
//   bool Tick(Creature* c, void* a2, void* a3, void* a4, void* a5, State* st)
#include "types.h"
#include <math.h>
#include <new>

struct Vec3 { float x, y, z; };
struct Mat3 { float m[9]; };

// 1/|d| with a small bias (x87 fsqrt path); d lives in memory.
inline float InvLength(const Vec3& d)
{
    return 1.0f / (float)sqrt(d.x * d.x + d.z * d.z + d.y * d.y + 1e-8f);
}

#pragma warning(disable:4035)
// EA math FloorToInt: hand-written SSE asm (round, then step down if the rounded value is above f).
__forceinline int FloorToInt(float f)
{
    __asm {
        movss    xmm0, f
        cvtss2si eax, xmm0
        cvtsi2ss xmm1, eax
        mov      ecx, eax
        sub      ecx, 1
        ucomiss  xmm0, xmm1
        cmovb    eax, ecx
    }
}

// Spatial object with its own vtable (the creature embeds one at +0xc0). Virtual calls are made through the vtable
// by slot index (the original's call sequence is `mov eax,[ecx]; mov edx,[eax+N]; call edx`).
struct SpObj {
    void** vt;
    char pad04[0x77 - 4];
    char mOnPlanet;                             // +0x77
    Vec3* GetPosition() { return ((Vec3*(__thiscall*)(SpObj*))vt[11])(this); }               // +0x2c
    void* GetOrientation() { return ((void*(__thiscall*)(SpObj*))vt[12])(this); }            // +0x30
    float GetRadius() { return ((float(__thiscall*)(SpObj*))vt[29])(this); }                 // +0x74
    void* QueryInterface(unsigned id) { return ((void*(__thiscall*)(SpObj*, unsigned))vt[46])(this, id); }  // +0xb8
    bool IsNearGoal();                          // 0xc42e20
};

// Obstacle record as read from the first query (position at +0x38, radius at +0x44).
struct Obstacle {
    char pad00[0x38];
    Vec3 pos;
    float radius;
};

// eastl::vector<T, sp_vector_allocator> with 16 inline slots; the allocator keeps an element-count cookie word
// in front of the buffer (0 for the inline buffer, so it is never freed).
template<class T> struct InlineVec16 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t allocPad[2];
    uint32_t cookie;
    T buf[16];
    InlineVec16() { mpBegin = buf; mpEnd = buf; mpCapacity = buf + 16; cookie = 0; }
    ~InlineVec16()
    {
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            operator delete[](mpBegin);
    }
};

// eastl::vector<EA::AutoRefCount<SP::cSpatialObject>, sp_vector_allocator>; the dtor releases and is out of line.
struct ObjVec16 : InlineVec16<SpObj*> {
    ~ObjVec16();                                // 0xad92d0
};

struct Creature {
    char pad00[0xc0];
    SpObj loco;                                 // +0xc0
    char pad01[0x330 - 0xc0 - sizeof(SpObj)];
    uint8_t flags330;
    void MoveToPointAtSpeed(int mode, const Vec3* p, float speed, float f);   // 0xc1c1d0
};

struct PlanetModelT {
    float GetWaterHeight();                                 // 0xb7e390
    Vec3* ToSurface(Vec3* out, const Vec3* p);             // 0xb81630
};
struct ObjectQuery {                                        // FUN_00b3d3c0() result
    void FUN_00b79c30(const Vec3* pos, InlineVec16<Obstacle*>* out, int mask, float radius, int a, int b);
};
struct ObjVec16;
struct SpatialQuery {                                       // FUN_00b3d240() result
    void** vt;
    void QueryObjects(const Vec3* pos, float radius, ObjVec16* out, int a, bool (__cdecl* filter)(void*), int b)   // slot 18 (+0x48)
    {
        ((void(__thiscall*)(SpatialQuery*, const Vec3*, float, ObjVec16*, int, bool (__cdecl*)(void*), int))vt[18])(this, pos, radius, out, a, filter, b);
    }
};

PlanetModelT* __cdecl PlanetModel();                        // 0xb3d350
ObjectQuery* __cdecl FUN_00b3d3c0();
SpatialQuery* __cdecl FUN_00b3d240();
void __cdecl Matrix3FromQuaternion(Mat3* out, const void* q);   // 0x59c190
void* __cdecl FUN_00d99470(void* c);
// 0xd9a960: object filter for the second query. It is an anonymous callback (no function start in the analysis
// image, so the equivalence tester cannot resolve a symbol for it); referenced by address.
typedef bool (__cdecl* ObjectFilterFn)(void*);
#define OBJECT_FILTER_00D9A960 ((ObjectFilterFn)0x00d9a960)

extern float g_0169f378;                                    // 2*pi
extern Vec3 g_0169f37c;                                     // ring basis U
extern Vec3 g_0169f388;                                     // ring basis V

struct State {
    Creature* target;
    int pad04[4];
    int state;                                              // +0x14
};

template<class T> inline const T& min_(const T& a, const T& b) { return (a < b) ? a : b; }

// @ 0x00da0780
bool __cdecl Tick_Avoid(Creature* c, void* a2, void* a3, void* a4, void* a5, State* st)
{
    if (!FUN_00d99470(st->target))
        return false;
    switch (st->state) {
    case 0: {
        SpObj* loco = &c->loco;
        loco->GetPosition();
        const int kMaxSamples = 6;
        float radA = loco->GetRadius();
        float radB = loco->GetRadius() + 0.25f;
        float ringRadius = radA + radB;
        int n = FloorToInt(g_0169f378 / (2.0f * asinf(radB / ringRadius)));
        int samples = min_(n, kMaxSamples);
        float step = g_0169f378 / (float)samples;

        PlanetModelT* pm = PlanetModel();
        Vec3* pos = loco->GetPosition();
        Mat3 rot;
        Matrix3FromQuaternion(&rot, loco->GetOrientation());
        float water = pm->GetWaterHeight();
        float water2 = water * water;
        bool aboveWater = (pos->x * pos->x + pos->y * pos->y + pos->z * pos->z) > water2;

        float queryRadius = 2.0f * radB + radA;
        InlineVec16<Obstacle*> obstacles;
        FUN_00b3d3c0()->FUN_00b79c30(pos, &obstacles, 0x1f, queryRadius, 0, 0);
        ObjVec16 objects;
        FUN_00b3d240()->QueryObjects(pos, queryRadius, &objects, 0, OBJECT_FILTER_00D9A960, 1);

        // Direction away from the target.
        Vec3* tp = st->target->loco.GetPosition();
        Vec3 away;
        {
            Vec3 d;
            d.x = pos->x - tp->x;
            d.y = pos->y - tp->y;
            d.z = pos->z - tp->z;
            float inv = InvLength(d);
            away.x = inv * d.x;
            away.y = d.y * inv;
            away.z = d.z * inv;
        }

        Vec3 bestFree = *pos;      // best clear point
        Vec3 bestHit = *pos;       // best point that lands on an object with interface 0xce9f6639
        float freeScore = -1.0f;
        float hitScore = -1.0f;

        Vec3 ring[6];    // the original also fills this scratch array (never read)
        float ang = 0.0f;
        for (int i = 0; i < samples; ++i) {
            float s = sinf(ang);
            float co = cosf(ang);
            Vec3 q;
            q.x = (s * g_0169f37c.x + co * g_0169f388.x) * ringRadius;
            q.y = (s * g_0169f37c.y + co * g_0169f388.y) * ringRadius;
            q.z = (s * g_0169f37c.z + co * g_0169f388.z) * ringRadius;
            ring[i] = q;
            Vec3 p;
            p.x = rot.m[0] * q.x + rot.m[3] * q.y + rot.m[6] * q.z + pos->x;
            p.y = rot.m[1] * q.x + rot.m[4] * q.y + rot.m[7] * q.z + pos->y;
            p.z = rot.m[2] * q.x + rot.m[5] * q.y + rot.m[8] * q.z + pos->z;
            Vec3 S;
            pm->ToSurface(&S, &p);
            if (aboveWater && water2 > S.x * S.x + S.y * S.y + S.z * S.z)
                goto next;
            for (Obstacle** it = obstacles.mpBegin; it != obstacles.mpEnd; ++it) {
                Obstacle* o = *it;
                float r = o->radius + radB;
                float ez = S.z - o->pos.z;
                float ey = S.y - o->pos.y;
                float ex = S.x - o->pos.x;
                if (r * r > (ez * ez + ey * ey) + ex * ex)
                    goto next;
            }
            for (SpObj** it = objects.mpBegin; it != objects.mpEnd; ++it) {
                SpObj* o = *it;
                if (o == &c->loco)
                    continue;
                float rad = o->GetRadius();
                Vec3 tmp;
                Vec3* op = o->GetPosition();
                if (o->mOnPlanet == 0)
                    op = pm->ToSurface(&tmp, op);
                float ex = S.x - op->x;
                float ez = S.z - op->z;
                float ey = S.y - op->y;
                float rr2 = rad + radB;
                if (rr2 * rr2 > (ex * ex + ez * ez) + ey * ey) {
                    if (o->QueryInterface(0xce9f6639)) {
                        Vec3 d;
                        d.x = S.x - pos->x;
                        d.z = S.z - pos->z;
                        d.y = S.y - pos->y;
                        float inv = InvLength(d);
                        float score = (inv * d.x) * away.x + (d.z * inv) * away.z + (d.y * inv) * away.y;
                        if (score > hitScore) {
                            hitScore = score;
                            bestHit = S;
                        }
                    }
                    goto next;
                }
            }
            {
                Vec3 d;
                d.x = S.x - pos->x;
                d.z = S.z - pos->z;
                d.y = S.y - pos->y;
                float inv = InvLength(d);
                float score = (inv * d.x) * away.x + (d.z * inv) * away.z + (d.y * inv) * away.y;
                if (score > freeScore) {
                    freeScore = score;
                    bestFree = S;
                }
            }
        next:
            ang += step;
        }
        if (bestFree.x == pos->x && bestFree.y == pos->y && bestFree.z == pos->z)
            bestFree = bestHit;
        c->MoveToPointAtSpeed(2, &bestFree, 1.0f, 2.0f);
        st->state = 1;
        return true;
    }
    case 1:
        if (!c->loco.IsNearGoal()) {
            if (!(c->flags330 & 1))
                return true;
        }
        return false;
    default:
        return false;
    }
}
