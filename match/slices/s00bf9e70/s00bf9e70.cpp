// Slice s00bf9e70: FUN_00bf9e70, per-civilization AI step that picks a target city of another
// civilization (score = relationship term * multipliers * distance falloff), then, for the
// closest owned city on the right continent, buys/places a unit (updates a budget float).
//
// Layouts are retail; the PDB's cCivilization offsets do not apply here.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /fp:fast (movss for locals, x87 for call results; no EH frame).
#include "types.h"

struct Vector3 { float x, y, z; };
struct Vec12 { uint32_t a, b, c; };

// EA::Random::RandomLinearCongruential (shared math RNG)
struct RandomLinearCongruential {
    uint32_t RandomUint32Uniform(uint32_t limit);   // 0x00a68fb0
};
extern RandomLinearCongruential sMathRandom;         // 0x01601760

extern Vector3 g_ZeroPosKey;                         // 0x0168c514 (3 floats)

struct SPTimer {
    unsigned __int64 GetElapsedTime();               // 0x00bc3190
    void Restart();                                  // 0x00bc3130
};

// Interface at city+0x34 (and city+0x120): position provider; vtable slots 0x2c / 0x58.
class SpatialObj {
public:
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual void s20(); virtual void s24(); virtual void s28();
    virtual const Vector3* GetPosition();            // 0x2c
    virtual void s30(); virtual void s34(); virtual void s38(); virtual void s3c();
    virtual void s40(); virtual void s44(); virtual void s48(); virtual void s4c();
    virtual void s50(); virtual void s54();
    virtual bool v58();                              // 0x58
};

class Civ;

class City {
public:
    virtual int AddRef();                            // 0x00
    virtual int Release();                           // 0x04
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual void v3c(); virtual void v40(); virtual void v44();
    virtual void v48();
    virtual int GetPoliticalID();                    // 0x4c
    uint32_t pad04[12];
    SpatialObj sub34;                                // +0x34 (vptr only used)
    uint32_t pad38[(0x120 - 0x38) / 4];
    SpatialObj sub120;                               // +0x120

    Civ*            GetOwner();                      // 0x00bfdf80
    int             bd81d0();                        // 0x00bd81d0
    int             bd8210();                        // 0x00bd8210
    const Vector3*  GetCenter();                     // 0x00fa0e00
    bool            bdb930(int a, int b);            // 0x00bdb930
    void            bddda0(int a, int b, Vec12 v, bool f);   // 0x00bddda0
};

struct Helper6c { uint8_t b[0x89 - 0x6c]; const Vec12* bf9700(int key); };   // 0x00bf9700

struct CityList { City** begin; City** end; City** cap; };
struct CivList  { Civ** begin; Civ** end; };

class Civ {
public:
    virtual int AddRef();
    virtual int Release();
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual void v3c(); virtual void v40(); virtual void v44();
    virtual void v48();
    virtual int GetPoliticalID();                    // 0x4c
    uint32_t pad04[(0x6c - 4) / 4];
    Helper6c helper;                                 // +0x6c
    bool     b89;
    bool     b8a;
    uint8_t  pad8b[7];
    bool     b92;
    uint8_t  pad93[0x9c - 0x93];
    CityList cities;                                 // +0x9c
    uint32_t pada8[(0xb0 - 0xa8) / 4];
    City**   list_b0;                                // +0xb0
    City**   list_b4;                                // +0xb4
    uint32_t padb8[(0x1a8 - 0xb8) / 4];
    SPTimer  timer;                                  // +0x1a8
    uint32_t pad1ac[(0x298 - 0x1ac) / 4];
    int      difficulty;                             // +0x298
    uint32_t pad29c[(0x464 - 0x29c) / 4];
    City*    target;                                 // +0x464
    uint32_t pad468;
    Civ*     civ46c;                                 // +0x46c
    uint32_t pad470[(0x4b0 - 0x470) / 4];
    float    budget;                                 // +0x4b0

    void  Step();                                    // 0x00bf9e70
    int   bf7150();                                  // 0x00bf7150
    int   bf0c60(int a, int b, int c, int d);        // 0x00bf0c60
    float bf2170(int a, int b);                      // 0x00bf2170
    int   bf2100(int a);                             // 0x00bf2100
    bool  bf00a0(int a, int b);                      // 0x00bf00a0
    bool  beff90(const Vector3* p, int b);           // 0x00beff90
};

struct Sphere { int c75420(); };                     // 0x00c75420
struct RelMgr { bool ae2e20(int a, int b); float d00a10(int a, int b, int c); };   // 0x00ae2e20 / 0x00d00a10
struct PlanetMdl {
    int   GetContinent(const Vector3* p);            // 0x00b88590
    float DistanceBetweenPoints(const Vector3* a, const Vector3* b);   // 0x00b81470
    float b7e4d0();                                  // 0x00b7e4d0
};
struct NounMgr {
    Civ*      GetPlayerCivilization();               // 0x00b25fb0
    Sphere*   GetCurrentTerrainSphere();             // 0x00f67d90
    CivList*  GetCivs();                             // 0x00b25ca0
    CityList* GetCities();                           // 0x00ae6030
};
NounMgr*   NounManager();                            // 0x00b3d300
RelMgr*    RelationshipManager();                    // 0x00b3d2c0
PlanetMdl* PlanetModel();                            // 0x00b3d350
int        GetCurrentGameMode();                     // 0x00b5b800
int        c9e6d0(int a, int b);                     // 0x00c9e6d0 (cdecl)

__forceinline bool PosNotKey(const Vector3* p)
{
    return p->x != g_ZeroPosKey.x || p->y != g_ZeroPosKey.y || p->z != g_ZeroPosKey.z;
}

void Civ::Step()
{
    if (((unsigned)cities.end - (unsigned)cities.begin & 0xfffffffcU) == 0) return;
    City* first = *cities.begin;
    if (!first) return;
    if (b8a) return;

    Civ* player = NounManager()->GetPlayerCivilization();
    if (player) {
        if (NounManager()->GetCurrentTerrainSphere()->c75420() <= 0
            && player->bf7150() < this->bf7150()) {
            City* t = target;
            if (t) { target = 0; t->Release(); }
            timer.Restart();
            return;
        }
    }

    if (b92) {
        if (sMathRandom.RandomUint32Uniform(200) == 0
            && (int)(((unsigned)list_b4 - (unsigned)list_b0) & 0xfffffffcU) > 8)
            b92 = false;
    } else {
        if (sMathRandom.RandomUint32Uniform(300) == 0)
            b92 = true;
    }

    bool skipPick = false;
    if (target) {
        Civ* o = target->GetOwner();
        if (!o || target->GetOwner() == this) {
            // fall through to picking
        } else if (RelationshipManager()->ae2e20(this->GetPoliticalID(), target->GetPoliticalID())
                   || target->GetOwner()->b8a) {
            skipPick = true;
        }
    } else {
        skipPick = true;
    }
    if (skipPick) {
        unsigned __int64 el = timer.GetElapsedTime();
        if (el <= 20000) return;
    }

    City* best = 0;
    float bestScore = 0.0f;
    CityList* all = NounManager()->GetCities();
    City** it = all->begin;
    City** itEnd = all->end;
    for (; it != itEnd; ++it) {
        City* c = *it;
        if (!c->GetOwner()) continue;
        if (c->GetOwner() == this) continue;
        Civ* pl = NounManager()->GetPlayerCivilization();
        SpatialObj* cs = &c->sub34;
        if (cs->v58()) {
            if (!pl) continue;
            if (NounManager()->GetCurrentTerrainSphere()->c75420() <= 0
                && pl->bf7150() <= this->bf7150())
                continue;
        }
        if ((!b8a || c->GetOwner()->b89)
            && RelationshipManager()->ae2e20(this->GetPoliticalID(), c->GetPoliticalID())) {
        } else {
            if (b8a || !c->GetOwner()->b8a) continue;
        }

        if (difficulty < 1 || !bf00a0(PlanetModel()->GetContinent(cs->GetPosition()), -1)) {
            if (difficulty < 2) continue;
            if (!beff90(cs->GetPosition(), -1)) continue;
        }

        int n = 0;
        CivList* civs = NounManager()->GetCivs();
        Civ** ci = civs->begin;
        Civ** ciEnd = civs->end;
        for (; ci != ciEnd; ++ci) {
            Civ* o = *ci;
            if (o != this && o->target == c) n++;
        }
        if (n != 0) continue;

        float score = 100.0f - RelationshipManager()->d00a10(this->GetPoliticalID(), c->GetPoliticalID(), 1) * 10.0f;
        if (c->GetOwner()->b8a) score = score * 4.0f;
        if (c->GetOwner()->civ46c == this) score = score * 3.0f;
        if (c == target) score = score * 2.0f;
        City* f = first;
        float d = PlanetModel()->DistanceBetweenPoints(f->sub120.GetPosition(), cs->GetPosition());
        score = (2.0f - d / (PlanetModel()->b7e4d0() * 3.1415927f)) * score * 8.0f;
        if (NounManager()->GetCurrentTerrainSphere()->c75420() <= 0 && !c->GetOwner()->b89)
            score = score * 16.0f;
        if (score > bestScore) { best = c; bestScore = score; }
    }
    (void)first;

    if (best) {
        int count = (int)(cities.end - cities.begin);
        City* best2 = 0;
        float score2 = 0.0f;
        for (int i = 0; i < count; i++) {
            City* c = cities.begin[i];
            bool ok = false;
            if (difficulty >= 1 && c->bd8210() == PlanetModel()->GetContinent(best->sub34.GetPosition()))
                ok = true;
            else if (difficulty >= 2 && PosNotKey(c->GetCenter())
                     && PlanetModel()->GetContinent(c->GetCenter())
                        == PlanetModel()->GetContinent(best->sub34.GetPosition()))
                ok = true;
            if (!ok) continue;
            float d = PlanetModel()->DistanceBetweenPoints(c->sub120.GetPosition(), best->sub34.GetPosition());
            float v = (2.0f - d / (PlanetModel()->b7e4d0() * 3.1415927f)) * 100.0f;
            if (v > score2) { best2 = c; score2 = v; }
        }

        if (best2) {
            int flag;
            bool go = false;
            if (difficulty >= 2 && PosNotKey(best2->GetCenter())
                && PlanetModel()->GetContinent(best2->GetCenter())
                   == PlanetModel()->GetContinent(best->sub34.GetPosition())) {
                flag = 1;
                go = true;
            } else if (difficulty >= 1
                       && best2->bd8210() == PlanetModel()->GetContinent(best->sub34.GetPosition())) {
                flag = 0;
                go = true;
            }
            if (go) {
                int r = bf0c60(best2->bd81d0(), PlanetModel()->GetContinent(best->sub34.GetPosition()), flag, 0);
                if (r < (best2->bd81d0() != 2) + 1
                    && best2->bdb930(best2->bd81d0(), flag)) {
                    float cost = bf2170(best2->bd81d0(), flag);
                    if (!(budget < cost) && bf2100(best2->bd81d0()) > 0) {
                        int k = c9e6d0(best2->bd81d0(), flag);
                        const Vec12* p = helper.bf9700(k);
                        best2->bddda0(best2->bd81d0(), flag, *p, GetCurrentGameMode() == 0x1654c05);
                        budget = budget - cost;
                    }
                }
            }
        }
    }

    City* old = target;
    if (best != old) {
        if (best) best->AddRef();
        target = best;
        if (old) old->Release();
    }
    timer.Restart();
}
