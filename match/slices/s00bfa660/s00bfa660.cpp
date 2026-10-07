// SP::cSPSimulatorSpaceGame::FUN_00bfa660 (0x00bfa660, 2492 bytes): thiscall, ret 4.
// Target-city chooser for the space game: slot 0x458 (param 0) or 0x45c (param 1),
// each paired with a cSPTimer at +0x148 / +0x168.  Retail field offsets are used
// (the 2008 PDB layout differs).  Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

typedef void* P;

// ---- callees (thiscall unless noted) ----------------------------------------
struct Ext {
    P        GetPlayerCivilization();                        // 0xb25fb0 (ret 0)
    P        GetGameDataVector(P a, P b, P c, P d, P e);     // 0xb21340 (ret 0x14)
    P        GetCurrentTerrainSphere();                      // 0xf67d90 (ret 0)
    int      FUN_00c75420();                                 // 0xc75420 (ret 0)
    P        GetCivilization();                              // 0xbd9bf0 (ret 0)
    int      GetVehicleSpecialty();                          // 0xbd81d0 (ret 0)
    int      FUN_00bd8210();                                 // 0xbd8210 (ret 0)
    int      FUN_00bd9b70();                                 // 0xbd9b70 (ret 0)
    float    FUN_00bd7d00();                                 // 0xbd7d00 (ret 0)
    P        FUN_00fa0e00();                                 // 0xfa0e00 (ret 0; position vector)
    int      FUN_00be4000(P sim, int flag);                  // 0xbe4000 (ret 8)
    int      FUN_00bf0110(P city, int flag);                 // 0xbf0110 (ret 8)
    int      FUN_00beff90(P pos, int flag);                  // 0xbeff90 (ret 8)
    int      GetContinent(P pos);                            // 0xb88590 cPlanetModel (ret 4)
    float    DistanceBetweenPoints(int a, int b);            // 0xb81470 cPlanetModel (ret 8)
    float    FUN_00bf5b90(P city);                           // 0xbf5b90 (ret 4)
    float    FUN_00b7e4d0();                                 // 0xb7e4d0 (ret 0)
    int      FUN_00d00a70(int a, int b, int c);              // 0xd00a70 RelationshipManager (ret 0xc)
    float    FUN_00d00a10(int a, int b, int c);              // 0xd00a10 RelationshipManager (ret 0xc)
    int      SpaceTelemetry_Add(int flag);                   // 0xbf2100 (ret 4)
    float    FUN_00bf2170(int a, int b);                     // 0xbf2170 (ret 8)
    int      FUN_00bdb930(int a, int b);                     // 0xbdb930 (ret 8)
    void     FUN_00bddda0(int a, int b, int s0, int s1, int s2, int flag); // 0xbddda0 (ret 0x18)
    P        FUN_00bf9700(P s);                              // 0xbf9700 (ret 4; this = this+0x6c)
    void     Restart();                                      // 0xbc3130 cSPTimer::Restart (ret 0)
    uint64_t GetElapsedTime();                               // 0xbc3190 cSPTimer::GetElapsedTime (ret 0)
    uint32_t RandomUint32Uniform(uint32_t n);                // 0xa68fb0 (ret 4)
};

// ---- free functions (cdecl) -------------------------------------------------
P   NounManager();                                           // 0xb3d300
P   PlanetModel();                                           // 0xb3d350
P   RelationshipManager();                                   // 0xb3d2c0
int GetCurrentGameMode();                                    // 0xb5b800
P   FUN_00c9e6d0(int a, int b);                              // 0xc9e6d0
int Vector3_NotEqual(const float* a, const float* b);        // 0x41dd30

extern float DAT_0168c514[3];                                // zero vector, 0x168c514..1c
extern char  g_RandomLCG[];                                  // 0x1601760
static const float kF_156f89c = 3.14159274f;               // 0x156f89c (pi, verified in binary)

// Vtable call helpers: [vptr + off] with the object as ECX.
template <class R> inline R VC0(void* o, int off) {
    return ((R(__thiscall*)(void*))((*(void***)o)[off / 4]))(o);
}
template <class R, class A> inline R VC1(void* o, int off, A a) {
    return ((R(__thiscall*)(void*, A))((*(void***)o)[off / 4]))(o, a);
}
#define FLD(T, p, off) (*(T*)((char*)(p) + (off)))

static inline bool IsZeroVec(const float* v) {
    return v[0] == DAT_0168c514[0] && v[1] == DAT_0168c514[1] && v[2] == DAT_0168c514[2];
}

struct cSPSimulatorSpaceGame {
    void FUN_00bfa660(int param_2);
};

// cSPSimulatorSpaceGame::FUN_00bfa660 @ 0x00bfa660
void cSPSimulatorSpaceGame::FUN_00bfa660(int param_2) {
    P self = (P)this;
    P player, cur, city, bestA, bestB, sph, gv, o;
    int r, cnt, i, bl, mode, sim, c1, c2, pd, td, a, b, cid, tid;
    bool flag = false;
    float sc, scoreA, scoreB, fv, dist, f, m;

    // ---- entry checks ----
    if (FLD(uint8_t, self, 0x8a)) return;
    player = ((Ext*)NounManager())->GetPlayerCivilization();
    if (player) {
        if (FLD(uint8_t, player, 0x8d) == 0) return;
        if (FLD(P, self, 0x460) == 0) {
            sph = ((Ext*)NounManager())->GetCurrentTerrainSphere();
            r = ((Ext*)sph)->FUN_00c75420();
            if (r <= 1) {
                pd = (FLD(int, player, 0xa0) - FLD(int, player, 0x9c)) & ~3;
                td = (FLD(int, self, 0xa0) - FLD(int, self, 0x9c)) & ~3;
                if (pd < td) {
                    sph = ((Ext*)NounManager())->GetCurrentTerrainSphere();
                    r = ((Ext*)sph)->FUN_00c75420();
                    if (r <= 0 || FLD(int, player, 0x4d0) < 2) {
                        o = FLD(P, self, 0x458);
                        if (o) { FLD(P, self, 0x458) = 0; VC0<void>(o, 4); }
                        ((Ext*)((char*)self + 0x148))->Restart();
                        o = FLD(P, self, 0x45c);
                        if (o) { FLD(P, self, 0x45c) = 0; VC0<void>(o, 4); }
                        ((Ext*)((char*)self + 0x168))->Restart();
                        return;
                    }
                }
            }
        }
    }

    // ---- is the occupant of the selected slot still the right city? ----
    cur = (param_2 == 0) ? FLD(P, self, 0x458) : FLD(P, self, 0x45c);
    if (cur) {
        a = VC0<int>(cur, 0x4c);
        b = VC0<int>(self, 0x4c);
        if (a == b) {
            flag = true;
        } else {
            cid = VC0<int>(cur, 0x4c);
            tid = VC0<int>(self, 0x4c);
            r = ((Ext*)RelationshipManager())->FUN_00d00a70(tid, cid, 1);
            if (r > 1 && FLD(uint8_t, ((Ext*)cur)->GetCivilization(), 0x8a) == 0) flag = true;
        }
    }
    bestA = FLD(P, self, 0x460);
    if (bestA != 0) {
        if (param_2 == 0) {
            if (FLD(P, self, 0x458) != bestA) flag = true;
        } else {
            if (FLD(P, self, 0x45c) != bestA) flag = true;
        }
    }
    if (flag) {
        if (param_2 == 0) {
            o = FLD(P, self, 0x458);
            if (o) { FLD(P, self, 0x458) = 0; VC0<void>(o, 4); }
        } else {
            o = FLD(P, self, 0x45c);
            if (o) { FLD(P, self, 0x45c) = 0; VC0<void>(o, 4); }
        }
        goto LPick;
    }

    // ---- elapsed-time gate ----
    {
        uint64_t el = (param_2 == 0) ? ((Ext*)((char*)self + 0x148))->GetElapsedTime()
                                     : ((Ext*)((char*)self + 0x168))->GetElapsedTime();
        uint32_t hi = (uint32_t)(el >> 32), lo = (uint32_t)el;
        if (hi == 0) {
            if (param_2 == 0) { if (lo <= 0x9c40) return; }
            else              { if (lo <= 0xc350) return; }
        }
    }

    // ---- LPick: first pass over the game-data city list ----
LPick:
    bestA = FLD(P, self, 0x460);
    scoreA = 0.0f;
    if (bestA != 0) goto LSecond;
    gv = ((Ext*)NounManager())->GetGameDataVector(
        (P)0xcd7d10, (P)0xd3d420, (P)0xacdff0, (P)0xb1e500, (P)0x18c43e8);
    cnt = (FLD(int, gv, 8) - FLD(int, gv, 4)) >> 2;
    for (i = 0; i < cnt; i++) {
        city = ((P*)FLD(P, gv, 4))[i];
        if (VC0<uint8_t>(city, 0x2c)) continue;
        if (((Ext*)city)->GetCivilization() == self) continue;
        if (VC0<uint8_t>((char*)city + 0x120, 0x58)) {
            if (player == 0) continue;
            sph = ((Ext*)NounManager())->GetCurrentTerrainSphere();
            r = ((Ext*)sph)->FUN_00c75420();
            if (r <= 0) {
                pd = (FLD(int, player, 0xa0) - FLD(int, player, 0x9c)) & ~3;
                td = (FLD(int, self, 0xa0) - FLD(int, self, 0x9c)) & ~3;
                if (pd <= td) continue;
            }
        }
        cid = VC0<int>(city, 0x4c);
        tid = VC0<int>(self, 0x4c);
        r = ((Ext*)RelationshipManager())->FUN_00d00a70(tid, cid, 1);
        if (r > 1 && FLD(uint8_t, ((Ext*)city)->GetCivilization(), 0x8a) == 0) continue;

        sim = FLD(int, self, 0x298);
        bl = (sim >= 3);
        if (sim >= 2) {
            P pos = ((Ext*)city)->FUN_00fa0e00();
            if (((Ext*)self)->FUN_00beff90(pos, param_2)) bl = 1;
        }
        if (FLD(int, self, 0x298) >= 1) {
            if (((Ext*)self)->FUN_00bf0110(city, param_2)) goto LScore;
        }
        if (!bl) continue;
    LScore:
        if (!((Ext*)city)->FUN_00be4000(self, 1)) {
            if (((Ext*)city)->FUN_00be4000(self, 0)) continue;
        }
        {
            int t1 = ((Ext*)g_RandomLCG)->RandomUint32Uniform(0x32);
            int t2 = ((Ext*)g_RandomLCG)->RandomUint32Uniform(0x32);
            sc = (float)(t2 + t1 + 0x32);
            if (param_2 == 0) {
                int u = ((Ext*)city)->FUN_00bd9b70();
                sc = (float)(10 - u) * 20.0f + sc;
            } else if (param_2 == 1) {
                f = ((Ext*)city)->FUN_00bd7d00();
                sc = (100.0f - f) * 4.0f + sc;
            }
            int r1 = VC1<int>(city, 0x4c, 1);
            tid = VC0<int>(self, 0x4c);
            dist = ((Ext*)RelationshipManager())->FUN_00d00a10(tid, r1, 1);
            sc = sc - dist * 10.0f;
            if (FLD(uint8_t, ((Ext*)city)->GetCivilization(), 0x8a)) sc = sc * 10.0f;
            if (((Ext*)self)->FUN_00bf0110(city, param_2)) sc = sc * 6.0f;
            P pos = ((Ext*)city)->FUN_00fa0e00();
            if (Vector3_NotEqual((const float*)pos, DAT_0168c514)) sc = sc * 4.0f;
            if (FLD(P, ((Ext*)city)->GetCivilization(), 0x46c) == self) sc = sc * 3.0f;
            P slot = (param_2 == 0) ? FLD(P, self, 0x458) : FLD(P, self, 0x45c);
            if (city == slot) sc = sc * 2.0f;
            dist = ((Ext*)self)->FUN_00bf5b90(city);
            float x = ((Ext*)PlanetModel())->FUN_00b7e4d0();
            sc = (2.0f - dist / (x * kF_156f89c)) * sc;
            sc = sc * 8.0f;
            sph = ((Ext*)NounManager())->GetCurrentTerrainSphere();
            r = ((Ext*)sph)->FUN_00c75420();
            if (r <= 0 && FLD(uint8_t, ((Ext*)city)->GetCivilization(), 0x89) == 0) sc = sc * 16.0f;
            if (sc > scoreA) { bestA = city; scoreA = sc; }
        }
    }
    if (bestA == 0) goto LStore;

    // ---- LSecond: second pass over this->[0x9c..0xa0) for city B ----
LSecond:
    cnt = (FLD(int, self, 0xa0) - FLD(int, self, 0x9c)) >> 2;
    bestB = 0;
    scoreB = 0.0f;
    if (cnt <= 0) goto LStore;
    for (i = 0; i < cnt; i++) {
        city = ((P*)FLD(P, self, 0x9c))[i];
        if (VC0<uint8_t>(city, 0x2c)) continue;
        if (((Ext*)city)->GetVehicleSpecialty() != param_2) continue;
        sim = FLD(int, self, 0x298);
        bl = (sim >= 3);
        if (sim >= 2) {
            P pos = ((Ext*)city)->FUN_00fa0e00();
            if (!IsZeroVec((const float*)pos)) {
                P pa = ((Ext*)bestA)->FUN_00fa0e00();
                if (!IsZeroVec((const float*)pa)) {
                    c1 = ((Ext*)PlanetModel())->GetContinent(((Ext*)city)->FUN_00fa0e00());
                    c2 = ((Ext*)PlanetModel())->GetContinent(pa);
                    if (c1 == c2) bl = 1;
                }
            }
        }
        if (sim >= 1 && ((Ext*)city)->FUN_00bd8210() == ((Ext*)bestA)->FUN_00bd8210()) goto LDist;
        if (!bl) continue;
    LDist:
        {
            int a1 = VC0<int>((char*)bestA + 0x120, 0x2c);
            int a2 = VC0<int>((char*)city + 0x120, 0x2c);
            dist = ((Ext*)PlanetModel())->DistanceBetweenPoints(a2, a1);
            float x = ((Ext*)PlanetModel())->FUN_00b7e4d0();
            fv = (2.0f - dist / (x * kF_156f89c)) * 100.0f;
            if (fv > scoreB) { bestB = city; scoreB = fv; }
        }
    }
    if (bestB == 0) goto LStore;

    // ---- mode from the sim-level / continent / vehicle-type checks on B vs A ----
    sim = FLD(int, self, 0x298);
    if (sim >= 3) {
        mode = 2;
    } else {
        mode = -1;
        if (sim >= 2) {
            P pb = ((Ext*)bestB)->FUN_00fa0e00();
            if (!IsZeroVec((const float*)pb)) {
                P pa = ((Ext*)bestA)->FUN_00fa0e00();
                if (!IsZeroVec((const float*)pa)) {
                    c1 = ((Ext*)PlanetModel())->GetContinent(pb);
                    c2 = ((Ext*)PlanetModel())->GetContinent(pa);
                    if (c1 == c2) mode = 1;
                }
            }
        }
        if (mode < 0) {
            if (sim < 1) goto LStore;
            if (((Ext*)bestB)->FUN_00bd8210() != ((Ext*)bestA)->FUN_00bd8210()) goto LStore;
            mode = 0;
        }
    }

    // ---- apply the chosen mode to city B ----
    if (((Ext*)bestB)->FUN_00bdb930(param_2, mode) == 0) goto LStore;
    f = ((Ext*)self)->FUN_00bf2170(param_2, mode);
    m = FLD(float, self, 0x4b0);
    if (m < f) goto LStore;
    do {
        if (((Ext*)self)->SpaceTelemetry_Add(param_2) <= 0) goto LStore;
        {
            P g = (P)FUN_00c9e6d0(param_2, mode);
            P ed = ((Ext*)((char*)self + 0x6c))->FUN_00bf9700(g);
            int isG = (GetCurrentGameMode() == 0x1654c05) ? 1 : 0;
            ((Ext*)bestB)->FUN_00bddda0(param_2, mode, FLD(int, ed, 0), FLD(int, ed, 4),
                                        FLD(int, ed, 8), isG);
        }
        m = FLD(float, self, 0x4b0) - f;
        FLD(float, self, 0x4b0) = m;
    } while (m >= f);

    // ---- LStore: install bestA in the slot and restart the timer ----
LStore:
    if (param_2 == 0) {
        o = FLD(P, self, 0x458);
        if (bestA != o) {
            if (bestA) VC0<void>(bestA, 0);
            FLD(P, self, 0x458) = bestA;
            if (o) VC0<void>(o, 4);
        }
        ((Ext*)((char*)self + 0x148))->Restart();
    } else {
        o = FLD(P, self, 0x45c);
        if (bestA != o) {
            if (bestA) VC0<void>(bestA, 0);
            FLD(P, self, 0x45c) = bestA;
            if (o) VC0<void>(o, 4);
        }
        ((Ext*)((char*)self + 0x168))->Restart();
    }
}
