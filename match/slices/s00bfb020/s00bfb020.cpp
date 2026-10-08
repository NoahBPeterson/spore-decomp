// SP::cSPSimulatorSpaceGame space-civ AI tick (0x00bfb020, 2246 bytes, __thiscall, no args).
//
// (1) Keeps one UFO ordered to harass the tracked city (+0x464) when we can afford it, or
//     clears the order when there is no tracked city;
// (2) once per minute (timer +0x188) picks the own city that has the most rival cities of the
//     same specialty around it, counts nearby rival cities and buys a type-2 vehicle (index
//     0/1/2) for it when the budget (+0x4b0) allows;
// (3) hands idle UFOs a (target, order) pair chosen by a random-weighted scan, and
// (4) sends still-idle UFOs toward the nearest own city when they are > 120 away from it.
// Retail field offsets are used. Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE.
#include "types.h"
#include <math.h>

struct Vec3 { float x, y, z; };
struct Key { uint32_t a, b, c; };

struct Pos {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10();
    virtual Vec3* GetPos();            // slot 11 (+0x2c)
};

struct Inter {
    struct Entity* target;             // +0x00
    char pad[0xc];
    int type;                          // +0x10
};

// A UFO or a city (the original code treats both through the same stub shape).
struct Entity {
    char pad00[0x34];
    Pos pos34;                         // +0x34
    char pad38[0x120 - 0x38];
    Pos pos120;                        // +0x120
    char pad124[0xb1c - 0x124];
    unsigned mId;                      // +0xb1c
    int mState;                        // +0xb20

    Inter* GetInter();                         // 0x00ca71d0
    bool CanTargetCity(Entity* c);             // 0x00c9fe40
    void Order(Entity* target, int type, int z); // 0x00cac000
    bool CanTarget(Entity* t);                 // 0x00ca8340
    void MoveTo(Vec3 p, int z);                // 0x00cac0e0
    float FUN_00bfdea0();                      // 0x00bfdea0 (ret 0)
    int GetVehicleSpecialty();                 // 0x00bd81d0
    bool FUN_00bd9260(Entity* other);          // 0x00bd9260 (ret 4)
    int FUN_00bd8210();                        // 0x00bd8210 (ret 0)
    Vec3* FUN_00fa0e00();                      // 0x00fa0e00 (ret 0; position)
    bool FUN_00bdb930(int a, int b);           // 0x00bdb930 (ret 8)
    void GetPoint(Vec3* out, unsigned id);     // 0x00bdca30 (ret 8)
    void FUN_00bddda0(int specialty, int index, Key key, bool spaceStage);   // 0x00bddda0 (ret 0x18)
};

struct Rel { float FUN_00ceee30(Entity* a, struct Game* g); };   // 0x00ceee30 (ret 8), object 0x169c254
extern Rel g_Rel;                      // 0x0169c254

struct Timer {
    uint32_t pad[8];
    unsigned long long GetElapsedTime();   // 0x00bc3190
    void Restart();                        // 0x00bc3130
};

struct Reg {
    uint32_t pad[12];
    Key* FUN_00bf9700(int type);           // 0x00bf9700 (ret 4)
};

struct PlanetMdl {
    float DistanceBetweenPoints(Vec3* a, Vec3* b);   // 0x00b81470 (ret 8)
    float GetRadius();                               // 0x00b7e4d0
    int GetContinent(Vec3* p);                       // 0x00b88590 (ret 4)
};
struct Rand { unsigned RandomUint32Uniform(unsigned n); };   // 0x00a68fb0
extern Rand sMathRandom;               // 0x01601760
extern Vec3 g_ZeroVec;                 // 0x0168c514
extern const float kRadiusScale;       // 0x0156f89c

struct Game;
struct PairVec { Game** begin; Game** end; };
struct NounMgr { PairVec* GetEmpires(); };         // 0x00b25ca0
NounMgr* NounManager();                            // 0x00b3d300
PlanetMdl* PlanetModel();                          // 0x00b3d350
int GetCurrentGameMode();                          // 0x00b5b800
int __cdecl FUN_00c9e6d0(int specialty, int index);    // 0x00c9e6d0: vehicle type of (specialty, index)

struct Game {
    char pad00[0x6c];
    Reg mReg;                          // +0x6c
    Entity** mCitiesBegin;             // +0x9c
    Entity** mCitiesEnd;               // +0xa0
    uint32_t pada4[3];
    Entity** mUfoBegin;                // +0xb0
    Entity** mUfoEnd;                  // +0xb4
    uint32_t padb8[52];
    Timer mTimer;                      // +0x188
    uint32_t pad1a8[175];
    Entity* mpTargetCity;              // +0x464
    uint32_t pad468[18];
    float mBudget;                     // +0x4b0

    void Tick();
    float GetMoney();                  // 0x00bef6d0 (ret 0)
    int SpaceTelemetry_Add(int flag);  // 0x00bf2100 (ret 4)
    float FUN_00bf2170(int specialty, int index);   // 0x00bf2170 (ret 8): vehicle cost
    __forceinline void Buy(Entity* city, int index, float cost);
};

__forceinline void Game::Buy(Entity* city, int index, float cost)
{
    int type = FUN_00c9e6d0(2, index);
    Key* pKey = mReg.FUN_00bf9700(type);
    bool inSpace = GetCurrentGameMode() == 0x1654c05;
    city->FUN_00bddda0(2, index, *pKey, inSpace);
    mBudget = mBudget - cost;
}

// @ 0x00bfb020
void Game::Tick()
{
    Entity* u;
    Entity** end = mUfoEnd;
    Entity** it = mUfoBegin;
    if (mpTargetCity) {
        for (; it != end; ++it) {
            u = *it;
            if (u && u->mState == 2 && u->GetInter()->type == 0xb) {
                if (u->GetInter()->target == mpTargetCity)
                    goto checkTimer;
            }
        }
        for (it = mUfoBegin, end = mUfoEnd; it != end; ++it) {
            u = *it;
            if (u && u->mState == 2 && u->CanTargetCity(mpTargetCity) && u->GetInter()->type != 0xb) {
                int n = (int)(mCitiesEnd - mCitiesBegin) * 600 + 0x578;
                float nf = (float)n;
                if ((mpTargetCity->FUN_00bfdea0() + 1.0f) * 0.5f * nf <= GetMoney()) {
                    u->Order(mpTargetCity, 0xb, 0);
                    break;
                }
            }
        }
    } else {
        for (; it != end; ++it) {
            u = *it;
            if (u && u->mState == 2 && u->GetInter()->type == 0xb)
                u->Order(0, 0, 0);
        }
    }

checkTimer:
    if (mTimer.GetElapsedTime() > 60000ull) {
        if (SpaceTelemetry_Add(2) > 0) {
            PlanetMdl* pm = PlanetModel();
            Entity* best = 0;
            int bestScore = 0;
            Entity** cit = mCitiesBegin;
            Entity** cend = mCitiesEnd;
            for (; cit != cend; ++cit) {
                Entity* city = *cit;
                if (city->GetVehicleSpecialty() == 2) {
                    int score = sMathRandom.RandomUint32Uniform(100);
                    PairVec* emp = NounManager()->GetEmpires();
                    Game** e = emp->begin;
                    Game** eEnd = emp->end;
                    for (; e != eEnd; ++e) {
                        Game* g = *e;
                        if (g != this) {
                            Entity** c = g->mCitiesBegin;
                            Entity** ce = g->mCitiesEnd;
                            for (; c != ce; ++c) {
                                if (*c != city && (*c)->FUN_00bd9260(city))
                                    score += 10;
                            }
                        }
                    }
                    if (score > bestScore) {
                        best = city;
                        bestScore = score;
                    }
                }
            }
            if (best) {
                int same = 0;
                int contin = 0;
                int total = 0;
                PairVec* emp = NounManager()->GetEmpires();
                Game** eit = emp->begin;
                Game** eend = emp->end;
                for (; eit != eend; ++eit) {
                    Game* g = *eit;
                    if (g == this)
                        continue;
                    Entity** c = g->mCitiesBegin;
                    Entity** ce = g->mCitiesEnd;
                    for (; c != ce; ++c) {
                        Entity* c2 = *c;
                        if (c2->FUN_00bd9260(best) || g_Rel.FUN_00ceee30(c2, this) == 1.0f) {
                            if (c2->FUN_00bd8210() == best->FUN_00bd8210())
                                ++same;
                            Vec3* p1 = c2->FUN_00fa0e00();
                            if (p1->x != g_ZeroVec.x || p1->y != g_ZeroVec.y || p1->z != g_ZeroVec.z) {
                                Vec3* p2 = best->FUN_00fa0e00();
                                if (p2->x != g_ZeroVec.x || p2->y != g_ZeroVec.y || p2->z != g_ZeroVec.z) {
                                    int k1 = pm->GetContinent(c2->FUN_00fa0e00());
                                    int k2 = pm->GetContinent(best->FUN_00fa0e00());
                                    if (k1 == k2)
                                        ++contin;
                                }
                            }
                            ++total;
                        }
                    }
                }
                if (total > 0 && best->FUN_00bdb930(2, 2)) {
                    float cost = FUN_00bf2170(2, 2);
                    if (mBudget < cost)
                        goto restart;
                    Buy(best, 2, cost);
                } else if (contin > same && best->FUN_00bdb930(2, 1)) {
                    float cost = FUN_00bf2170(2, 1);
                    if (mBudget < cost)
                        goto restart;
                    Buy(best, 1, cost);
                } else if (same > 0 && best->FUN_00bdb930(2, 0)) {
                    float cost = FUN_00bf2170(2, 0);
                    if (mBudget < cost)
                        goto restart;
                    Buy(best, 0, cost);
                }
            }
        }
restart:
        mTimer.Restart();
    }

    // Idle UFOs: pick a (own city, rival city) pair to attack.
    {
        Entity** ue = mUfoEnd;
        for (Entity** ui = mUfoBegin; ui != ue; ++ui) {
            u = *ui;
            if (u && u->mState == 2 && u->GetInter()->type == 0) {
                Entity* bestA = 0;
                Entity* bestB = 0;
                int bestScore = 0;
                Entity** cit = mCitiesBegin;
                Entity** cend = mCitiesEnd;
                for (; cit != cend; ++cit) {
                    Entity* city = *cit;
                    if (u->CanTarget(city)) {
                        PairVec* emp = NounManager()->GetEmpires();
                        Game** eit = emp->begin;
                        Game** eend = emp->end;
                        for (; eit != eend; ++eit) {
                            Game* g = *eit;
                            if (g == this)
                                continue;
                            Entity** c = g->mCitiesBegin;
                            Entity** ce = g->mCitiesEnd;
                            for (; c != ce; ++c) {
                                Entity* c2 = *c;
                                if (u->CanTarget(c2)) {
                                    if (c2->FUN_00bd9260(city) || g_Rel.FUN_00ceee30(c2, this) == 1.0f) {
                                        int score = sMathRandom.RandomUint32Uniform(100);
                                        if (c2->FUN_00bd9260(city))
                                            score += 10;
                                        if (score > bestScore) {
                                            bestA = city;
                                            bestB = c2;
                                            bestScore = score;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                if (bestA && bestB) {
                    if (bestB->FUN_00bd9260(bestA))
                        u->Order(bestB, 5, 0);
                    else
                        u->Order(bestB, 9, 0);
                }
            }
        }
    }

    // Still-idle UFOs: fly toward the nearest own city when it is far away.
    {
        Entity** ue = mUfoEnd;
        for (Entity** ui = mUfoBegin; ui != ue; ++ui) {
            u = *ui;
            if (u && u->mState == 2 && u->GetInter()->type == 0) {
                int n = (int)(mCitiesEnd - mCitiesBegin);
                Entity* bestC = 0;
                float bestScore = 0.0f;
                for (int i = 0; i < n; ++i) {
                    Entity* c = mCitiesBegin[i];
                    if (u->CanTarget(c)) {
                        Vec3* pu = u->pos34.GetPos();
                        Vec3* pc = c->pos120.GetPos();
                        float d = PlanetModel()->DistanceBetweenPoints(pc, pu);
                        float score = (2.0f - d / (PlanetModel()->GetRadius() * kRadiusScale)) * 100.0f;
                        if (score > bestScore) {
                            bestC = c;
                            bestScore = score;
                        }
                    }
                }
                if (bestC) {
                    Vec3* pc = bestC->pos120.GetPos();
                    Vec3* pu = u->pos34.GetPos();
                    float dx = pu->x - pc->x;
                    float dy = pu->y - pc->y;
                    float dz = pu->z - pc->z;
                    float dist = (float)sqrt((dz * dz + dy * dy) + dx * dx);
                    if (120.0f < dist) {
                        Vec3 pt;
                        bestC->GetPoint(&pt, u->mId);
                        u->MoveTo(pt, 0);
                    }
                }
            }
        }
    }
}
