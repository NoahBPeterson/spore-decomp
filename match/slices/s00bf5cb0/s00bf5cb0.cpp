// Slice s00bf5cb0 -- per-update military vehicle tasking for a tribe-style AI (0x00bf5cb0, 4090 bytes).
//
// Walks the AI's own vehicles (state 0/1) and (1) re-checks allied targets of in-progress orders,
// (2) lets idle vehicles shoot hostiles that target our owner, (3) occasionally picks the nearest
// enemy vehicle to attack, (4) now and then sends vehicles at an empire's city when nobody
// is defending, (5) assigns up to 2 vehicles to each of the three tracked cities (+0x458/45c/464)
// and (6) sends idle vehicles toward the best-scoring owned target.
// Module flags: /O2 (x87 float math).
#include "types.h"
#include <math.h>
#include <float.h>

struct Vec3 { float x, y, z; };
struct Entity;

struct Pos {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10();
    virtual Vec3* GetPos();            // slot 11 (+0x2c)
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16();
    virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20();
    virtual Entity* GetOwnerObject();  // slot 21 (+0x54)
    virtual bool IsActive();           // slot 22 (+0x58)
};

struct Inter {
    Entity* target;
    char pad[0xc];
    int type;
};

struct Civ {
    char pad0[0x89];
    bool b89;
    bool b8a;
    char pad1[3];
    bool b8e;
    bool b8f;
};

struct Entity {
    virtual void s0(); virtual void s1(); virtual void s2();
    virtual Entity* Cast(unsigned id);        // slot 3
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8();
    virtual void s9(); virtual void s10();
    virtual bool IsDestroyed();               // slot 11
    virtual Entity* GetLinked();              // slot 12
    virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
    virtual void s18();
    virtual int GetPlayerID();                // slot 19
    virtual void s20(); virtual void s21(); virtual void s22();
    virtual Entity* Cast2(unsigned id);       // slot 23

    char pad04[0x34 - 4];
    Pos pos34;                                // +0x34
    char pad38[0xb0 - 0x34 - 4];
    Entity** vecBegin;                        // +0xb0 (sub-entity list)
    Entity** vecEnd;                          // +0xb4
    char padb8[0x120 - 0xb8];
    Pos pos120;                               // +0x120
    char pad124[0x508 - 0x124];
    Pos pos508;                               // +0x508
    char pad50c[0xb1c - 0x50c];
    unsigned mId;                             // +0xb1c
    int mState;                               // +0xb20

    Inter* GetInter();                        // 0xca71d0
    void Order(Entity* target, int type, int z);   // 0xcac000
    Entity** GetHostiles();                   // 0xc9e860 (vector begin/end at +0/+4)
    bool CanOccupyTerrain(Vec3* p);           // 0xc9e960
    bool CanReach();                          // 0xc9f410
    bool CanTarget(Entity* t);                // 0xca8340
    bool CanTargetCity(Entity* c);            // 0xc9fe40
    void SetCount(int n);                     // 0xc9ee30
    void MoveTo(Vec3 p, int z);               // 0xcac0e0
    Civ* GetCivilization();                   // 0xbd9bf0
    Civ* GetCivOf();                          // 0xbfdf80
    Entity* GetCityOf();                      // 0xbd84e0
    int GetCapacity();                        // 0xbd9b70
    float GetFactor();                        // 0xbd7d00
    int GetBase();                            // 0xbd8960
    void GetPoint(Vec3* out, unsigned id);    // 0xbdca30
};

struct RelMgr {
    int GetRelation(int a, int b, int c);     // 0xd00a70
    bool IsAllied(int a, int b);              // 0xae2e20
};

struct Timer {
    unsigned long long GetElapsedTime();      // 0xbc3190
    void Restart();                           // 0xbc3130
};

struct VecHolder { int pad; Entity** begin; Entity** end; };
struct PairVec { Entity** begin; Entity** end; };

struct NounMgr {
    PairVec* GetEmpires();                    // 0xb25ca0
    int GetPlayerEmpireOrMinus1();            // 0xb1f9d0
    VecHolder* GetGameDataVector(void* a, void* b, void* c, void* d, unsigned int typeTag);  // 0xb21340
    struct Sphere* GetCurrentTerrainSphere(); // 0xf67d90
};
struct Sphere { int GetKind(); };             // 0xc75420
struct PlanetMdl {
    float DistanceBetweenPoints(Vec3* a, Vec3* b);   // 0xb81470
    float GetRadius();                        // 0xb7e4d0
};
struct Rand { unsigned RandomUint32Uniform(unsigned n); };  // 0xa68fb0
struct Seed { int GetValue(); };              // 0xac15e0

RelMgr* RelationshipManager();                // 0xb3d2c0
NounMgr* NounManager();                       // 0xb3d300
PlanetMdl* PlanetModel();                     // 0xb3d350
Seed* GetSeed();                              // 0xb3d290
bool IsValidFireTarget(Pos* mine, Pos* theirs);   // 0xdc4e20 (cdecl, anonymous namespace)
extern Rand sMathRandom;                      // 0x1601760
extern const float kRadiusScale;              // 0x156f89c
void FnA();   // 0xb1e500
void FnB();   // 0xacdff0
void FnC();   // 0xd3d420
void FnD();   // 0xcd7d10

struct TribeAI {
    virtual void t0(); virtual void t1(); virtual void t2(); virtual void t3(); virtual void t4();
    virtual void t5(); virtual void t6(); virtual void t7(); virtual void t8(); virtual void t9();
    virtual void t10(); virtual void t11(); virtual void t12(); virtual void t13(); virtual void t14();
    virtual void t15(); virtual void t16(); virtual void t17(); virtual void t18();
    virtual int GetPlayerID();                // slot 19
    char pad04[0x8a - 4];
    bool mFlag8a;
    char pad8b[0x92 - 0x8b];
    bool mFlag92;
    char pad93[0x9c - 0x93];
    Entity** mListBegin;                      // +0x9c
    Entity** mListEnd;                        // +0xa0
    char pada4[0xb0 - 0xa4];
    Entity** mVehBegin;                       // +0xb0
    Entity** mVehEnd;                         // +0xb4
    char padb8[0xe8 - 0xb8];
    Timer mTimer;                             // +0xe8
    char pad_e9[0x458 - 0xe9];
    Entity* mCityA;                           // +0x458
    Entity* mCityB;                           // +0x45c
    char pad460[4];
    Entity* mCityC;                           // +0x464 (field index 0x119)

    int GetLimit(int a);                      // 0xbf1fd0
    void Update();
};

static inline bool Active(Entity* v) { return v && (v->mState == 0 || v->mState == 1); }

// @ 0xbf5cb0
void TribeAI::Update()
{
    // 1. re-check orders aimed at allied / non-hostile targets
    for (Entity** it = mVehBegin; it != mVehEnd; ++it) {
        Entity* v = *it;
        if (!Active(v)) continue;
        bool go = false;
        if (v->GetInter()->type == 1) {
            Entity* t = v->GetInter()->target;
            if (!t) continue;
            Entity* c = t->Cast(0x403df5f);
            if (!c) continue;
            int other = c->GetPlayerID();
            int self = GetPlayerID();
            if (RelationshipManager()->GetRelation(self, other, 1) < 2) continue;
            if (!c->GetCivOf()) continue;
            if (c->GetCivOf()->b8a == 0) v->Order(0, 0, 0);
            continue;
        }
        if (v->GetInter()->type == 2) {
            if (v->GetInter()->target) go = true;
        }
        if (!go) {
            if (v->GetInter()->type != 3) continue;
            if (!v->GetInter()->target) continue;
        }
        Entity* t = v->GetInter()->target;
        if (t) {
            Entity* city = t->Cast(0xee9b2232);
            if (city) {
                if (!city->IsDestroyed()) {
                    int other = city->GetPlayerID();
                    int self = GetPlayerID();
                    if (RelationshipManager()->GetRelation(self, other, 1) >= 2) {
                        if (city->GetCivilization()->b8a == 0) v->Order(0, 0, 0);
                    }
                }
            }
        }
        Entity* t2 = v->GetInter()->target;
        if (!t2) continue;
        Entity* u = t2->Cast(0x3d5c477);
        if (!u) continue;
        Entity* o = u->GetLinked();
        if (!o) continue;
        if (!o->Cast(0xee9b2232)) continue;
        Entity* o2 = u->GetLinked();
        Entity* c3 = o2 ? o2->Cast(0xee9b2232) : 0;
        if (c3->IsDestroyed()) continue;
        Entity* cc = u->GetCityOf();
        int aid = cc->GetPlayerID();
        int self = GetPlayerID();
        if (RelationshipManager()->IsAllied(self, aid)) continue;
        if (u->GetCityOf()->GetCivilization()->b8a == 0) v->Order(0, 0, 0);
    }

    // 2. idle vehicles: fire at hostiles that target our owner
    for (Entity** it = mVehBegin; it != mVehEnd; ++it) {
        Entity* v = *it;
        if (!Active(v)) continue;
        if (v->GetInter()->type != 0) continue;
        Entity** h = v->GetHostiles();
        Entity** hb = (Entity**)((int*)h)[0];
        Entity** he = (Entity**)((int*)h)[1];
        for (Entity** p = hb; p != he; ++p) {
            Entity* e = *p;
            if (!e) continue;
            Entity* ev = e->Cast2(0x137e8e0);
            if (!ev) continue;
            Entity* tgt = ev->pos508.GetOwnerObject();
            if (!tgt) continue;
            Entity* owner = tgt->Cast2(0x17f243b);
            if (!owner) continue;
            if (owner->GetPlayerID() == GetPlayerID() && IsValidFireTarget(&v->pos508, &ev->pos508)) {
                v->Order(ev, 1, 0);
                break;
            }
        }
    }

    // 3. occasionally pick the nearest enemy vehicle to attack
    bool lucky = sMathRandom.RandomUint32Uniform(20) == 0;
    for (Entity** it = mVehBegin; it != mVehEnd; ++it) {
        Entity* v = *it;
        if (!Active(v)) continue;
        if (v->GetInter()->type != 0) continue;
        if (!lucky && !v->CanReach()) continue;
        Entity* best = 0;
        float bestD = FLT_MAX;
        PairVec* empires = NounManager()->GetEmpires();
        for (Entity** pe = empires->begin; pe != empires->end; ++pe) {
            Entity* emp = *pe;
            for (Entity** q = emp->vecBegin; q != emp->vecEnd; ++q) {
                Entity* e = *q;
                if (!e) continue;
                Entity* tgt = e->pos508.GetOwnerObject();
                if (!tgt) continue;
                Entity* owner = tgt->Cast2(0x17f243b);
                if (!owner) continue;
                if (owner->GetPlayerID() != GetPlayerID()) continue;
                if (!IsValidFireTarget(&v->pos508, &e->pos508)) continue;
                if (!v->CanOccupyTerrain(e->pos34.GetPos())) continue;
                Vec3* a = e->pos34.GetPos();
                Vec3* b = v->pos34.GetPos();
                float dx = b->x - a->x, dy = b->y - a->y, dz = b->z - a->z;
                float d = sqrtf(dz * dz + dy * dy + dx * dx);
                if (d < bestD) { best = e; bestD = d; }
            }
        }
        if (best) {
            v->Order(best, 1, 0);
            break;
        }
    }

    // 4. now and then send a vehicle to a city of the player's empire if nothing is defending
    if (!mFlag8a) {
        if (sMathRandom.RandomUint32Uniform(3) == 0) {
            unsigned long long el = mTimer.GetElapsedTime();
            if (el > 120000) {
                int pe = NounManager()->GetPlayerEmpireOrMinus1();
                int self = GetPlayerID();
                if (RelationshipManager()->GetRelation(self, pe, 1) <= 1) {
                    bool defended = false;
                    int idle = 0;
                    for (Entity** it = mVehBegin; it != mVehEnd; ++it) {
                        Entity* v = *it;
                        if (!Active(v)) continue;
                        if (v->GetInter()->type == 0) ++idle;
                        if (v->GetInter()->type != 2 && v->GetInter()->type != 3) continue;
                        Entity* t = v->GetInter()->target;
                        if (t) {
                            Entity* c = t->Cast(0xee9b2232);
                            if (c) {
                                if (c->pos120.IsActive()) defended = true;
                            }
                        }
                        Entity* t2 = v->GetInter()->target;
                        if (t2) {
                            Entity* u = t2->Cast(0x3d5c477);
                            if (u) {
                                Entity* o = u->GetLinked();
                                if (o) {
                                    if (o->Cast(0xee9b2232)) {
                                        Entity* o2 = u->GetLinked();
                                        Entity* c3 = o2 ? o2->Cast(0xee9b2232) : 0;
                                        if (c3->pos120.IsActive()) defended = true;
                                    }
                                }
                            }
                        }
                    }
                    if (!defended && idle > 0) {
                        Entity* best = 0;
                        int bestR = 0;
                        VecHolder* gd = NounManager()->GetGameDataVector((void*)FnD, (void*)FnC, (void*)FnB, (void*)FnA, 0x18c43e8);
                        int n = gd->end - gd->begin;
                        if (n > 0) {
                            for (int i = 0; i < n; ++i) {
                                Entity* e = gd->begin[i];
                                if (e->pos120.IsActive()) {
                                    int r = (int)sMathRandom.RandomUint32Uniform(100);
                                    if (bestR < r + 1) { best = e; bestR = r + 1; }
                                }
                            }
                            if (best) {
                                for (Entity** it = mVehBegin; it != mVehEnd; ++it) {
                                    Entity* v = *it;
                                    if (!Active(v)) continue;
                                    if (!v->CanTarget(best)) continue;
                                    if (v->GetInter()->type != 0) continue;
                                    mTimer.Restart();
                                    v->Order(best, (v->mState != 0) + 2, 0);
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // 5. city C: keep two idle vehicles on it
    if (mCityC) {
        bool skip = false;
        if (mCityA) {
            if (!mFlag92) skip = true;
            else if (mCityC->GetCivOf()->b8a == 0) {
                if (mCityA->GetCivilization()->b8a != 0) skip = true;
            }
        }
        if (!skip) {
            int n = 0;
            bool done = false;
            if (mVehBegin != mVehEnd) {
                for (Entity** it = mVehBegin; it != mVehEnd; ++it) {
                    Entity* v = *it;
                    if (!Active(v)) continue;
                    if (v->GetInter()->type == 1) {
                        if (v->GetInter()->target == mCityC) ++n;
                    }
                }
                if (n > 1) done = true;
            }
            if (!done) {
                for (Entity** it = mVehBegin; it != mVehEnd; ++it) {
                    Entity* v = *it;
                    if (!Active(v)) continue;
                    if (!v->CanTargetCity(mCityC)) continue;
                    if (v->GetInter()->type != 0) continue;
                    v->Order(mCityC, 1, 0);
                    ++n;
                    if (n == 2) break;
                }
            }
        }
    } else {
        for (Entity** it = mVehBegin; it != mVehEnd; ++it) {
            Entity* v = *it;
            if (!Active(v)) continue;
            if (v->GetInter()->type != 1) continue;
            Entity* t = v->GetInter()->target;
            if (!t) continue;
            if (t->Cast(0x403df5f)) v->Order(0, 0, 0);
        }
    }

    // 6. city A
    if (mCityA) {
        int cntA = 0, cntB = 0;
        for (Entity** it = mVehBegin; it != mVehEnd; ++it) {
            Entity* v = *it;
            if (!v || v->mState != 0) continue;
            if (!v->CanTarget(mCityA)) continue;
            if (v->GetInter()->type == 0) ++cntA;
            else if (!mFlag92) {
                if (v->GetInter()->type == 1) {
                    Entity* t = v->GetInter()->target;
                    if (t && t->Cast(0x403df5f)) ++cntA;
                }
            }
            if (v->GetInter()->type == 2) {
                if (v->GetInter()->target == mCityA) ++cntB;
            }
        }
        int size = (int)(mListEnd - mListBegin);
        int x = GetLimit(0) - size;
        int lim = mCityA->GetCapacity() + 3;
        x = (x < lim) ? x : lim;
        int k = NounManager()->GetCurrentTerrainSphere()->GetKind();
        int vmax = (k == 1) ? 0xb : (k == 2) ? 0xf : 6;
        int y = vmax - 1;
        x = (y < x) ? y : x;
        int r = GetSeed()->GetValue();
        bool assign;
        if (cntA + cntB < x) {
            assign = false;
            if (mCityA->GetCivilization()->b89 != 0) {
                if (mCityA->GetCivilization()->b8e == 0) assign = true;
            }
        } else {
            assign = true;
        }
        if (assign && cntB < vmax) {
            for (Entity** it = mVehBegin; it != mVehEnd; ++it) {
                Entity* v = *it;
                if (!v || v->mState != 0) continue;
                if (!v->CanTarget(mCityA)) continue;
                bool ok = false;
                if (v->GetInter()->type == 0) ok = true;
                else if (!mFlag92) {
                    if (v->GetInter()->type == 1) {
                        Entity* t = v->GetInter()->target;
                        if (t && t->Cast(0x403df5f)) ok = true;
                    }
                }
                if (ok) {
                    v->Order(mCityA, 2, 0);
                    v->SetCount(r);
                }
            }
        }
    }

    // 7. city B
    if (mCityB) {
        int cntA = 0, cntB = 0;
        for (Entity** it = mVehBegin; it != mVehEnd; ++it) {
            Entity* v = *it;
            if (!v || v->mState != 1) continue;
            if (!v->CanTarget(mCityB)) continue;
            if (v->GetInter()->type == 0) ++cntA;
            if (v->GetInter()->type == 3) {
                bool match = false;
                Entity* t = v->GetInter()->target;
                if (t) {
                    Entity* u = t->Cast(0x3d5c477);
                    if (u) {
                        Entity* o = u->GetLinked();
                        if (o && o->Cast(0xee9b2232)) {
                            Entity* o2 = u->GetLinked();
                            Entity* c3 = o2 ? o2->Cast(0xee9b2232) : 0;
                            if (c3 == mCityB) match = true;
                        }
                    }
                }
                if (!match) match = (v->GetInter()->target == mCityB);
                if (match) ++cntB;
            }
        }
        int size = (int)(mListEnd - mListBegin);
        int x = GetLimit(1) - size;
        int ft = (int)mCityB->GetFactor();
        int base = mCityB->GetBase();
        int lim = (base + ft) / 0x29 + 2;
        x = (x < lim) ? x : lim;
        int k = NounManager()->GetCurrentTerrainSphere()->GetKind();
        int vmax = (k == 1) ? 0xb : (k == 2) ? 0xf : 6;
        int y = vmax - 1;
        x = (y < x) ? y : x;
        int r = GetSeed()->GetValue();
        bool skip = false;
        if (cntA + cntB < x) {
            if (mCityB->GetCivilization()->b89 == 0) skip = true;
            else if (mCityB->GetCivilization()->b8f != 0) skip = true;
        }
        if (!skip && cntB < vmax) {
            for (Entity** it = mVehBegin; it != mVehEnd; ++it) {
                Entity* v = *it;
                if (!v || v->mState != 1) continue;
                if (!v->CanTarget(mCityB)) continue;
                if (v->GetInter()->type != 0) continue;
                v->Order(mCityB, 3, 0);
                v->SetCount(r);
            }
        }
    }

    // 8. idle vehicles: head for the best-scoring target in the list
    for (Entity** it = mVehBegin; it != mVehEnd; ++it) {
        Entity* v = *it;
        if (!Active(v)) continue;
        if (v->GetInter()->type != 0) continue;
        int n = (int)(mListEnd - mListBegin);
        Entity* best = 0;
        float bestScore = 0.0f;
        for (int i = 0; i < n; ++i) {
            Entity* o = mListBegin[i];
            if (!v->CanTarget(o)) continue;
            Vec3* pv = v->pos34.GetPos();
            Vec3* po = o->pos120.GetPos();
            float dist = PlanetModel()->DistanceBetweenPoints(po, pv);
            float score = (2.0f - dist / (PlanetModel()->GetRadius() * kRadiusScale)) * 100.0f;
            if (bestScore < score) { best = o; bestScore = score; }
        }
        if (best) {
            Vec3* a = best->pos120.GetPos();
            Vec3* b = v->pos34.GetPos();
            float dx = b->x - a->x, dy = b->y - a->y, dz = b->z - a->z;
            float d = sqrtf(dz * dz + dy * dy + dx * dx);
            if (120.0f < d) {
                Vec3 p;
                best->GetPoint(&p, v->mId);
                v->MoveTo(p, 0);
            }
        }
    }
}
// --- equivalence checker address annotations
    void FnB(...); // 0x00acdff0
    void FnC(...); // 0x00d3d420
    void FnD(...); // 0x00cd7d10

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
