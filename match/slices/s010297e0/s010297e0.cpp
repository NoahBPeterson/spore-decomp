// Slice s010297e0: SP::cSPSpaceCombatTuning loot/DPS getters plus space mission/UFO helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE
#include "types.h"
extern "C" float sqrtf(float);

typedef unsigned int uint;

// ---------------------------------------------------------------------------
// minimal class stubs (real names from the 2008 PDB where known)
// ---------------------------------------------------------------------------
struct cPropertyList;
struct IUnk { virtual int AddRef(); virtual int Release(); };   // +4 = Release

struct GetsFloat {
    virtual void q0(); virtual void q1(); virtual void q2(); virtual void q3();
    virtual void q4(); virtual void q5(); virtual void q6(); virtual void q7();
    virtual void q8();
    virtual bool GetProperty(uint id, void** out);       // +0x24
};
struct Prop {
    char pad[0x12];
    unsigned short type;
    float* GetFloat();   // 0x0041ea70
};
struct cPropertyList : GetsFloat {
};
struct PropertyMgr {
    virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03();
    virtual void m04(); virtual void m05(); virtual void m06(); virtual void m07();
    virtual void m08(); virtual void m09(); virtual void m10();
    virtual void Unregister(uint a, uint b, IUnk** slot);   // +0x2c
};

struct Obj4c {   // vtable slot +0x4c returns int
    virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3();
    virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7();
    virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11();
    virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15();
    virtual void a16(); virtual void a17(); virtual void a18();
    virtual int v4c();
};

struct Obj0c {   // vtable slot +0xc
    virtual void b0(); virtual void b1(); virtual void b2();
    virtual void* v0c(int id);
};

struct Obj10 {   // vtable slot +0x10 returns int
    virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3();
    virtual int v10();
};

struct Obj38 {   // vtable slot +0x38 returns int
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3();
    virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11();
    virtual void d12(); virtual void d13();
    virtual int v38();
};

struct Obj68 {   // vtable slot +0x68: bool(void*)
    virtual void e0(); virtual void e1(); virtual void e2(); virtual void e3();
    virtual void e4(); virtual void e5(); virtual void e6(); virtual void e7();
    virtual void e8(); virtual void e9(); virtual void e10(); virtual void e11();
    virtual void e12(); virtual void e13(); virtual void e14(); virtual void e15();
    virtual void e16(); virtual void e17(); virtual void e18(); virtual void e19();
    virtual void e20(); virtual void e21(); virtual void e22(); virtual void e23();
    virtual void e24(); virtual void e25();
    virtual bool v68(void* id);
};

// cSPSpaceCombatTuning: size 0xc, AutoRefCount<cPropertyList> at +8
struct cSPSpaceCombatTuning {
    char pad[8];
    cPropertyList* mPropList;
    int   GetAirRaidSirenTimeMS();
    float GetBackgroundFighterDPS(int index);
    float GetBackgroundBomberDPS(int index);
    float GetBackgroundTurretDPS(int index);
    float GetLootMinMoneyDrop(int index);
    float GetLootMaxMoneyDrop(int index);
    float GetLootCityMinMoneyDrop(int index);
    float GetLootCityMaxMoneyDrop(int index);
    float GetLootUFOMoneyChance(int type);
    float GetLootRaiderMoneyChance();        // 0x0102a090
    float GetLootBomberMoneyChance();        // 0x0102a040
    float GetLootThiefMoneyChance();         // 0x0102a180
    float GetLootDefenderMoneyChance();      // 0x0102a0e0
    float GetLootInterceptorMoneyChance();   // 0x0102a130
    int   GetWeaponLevel(float x, float y, float z);
    float GetUFOHealth(int type, int index);
    float GetTurretHealth(int index);
    float LootChanceA(int type);
    float LootChanceB(int type);
};

// cSPGameDataUFO forward
struct cSPGameDataUFO {
    void Init(int a, int b);
    void SetDesiredModel(void* model, bool flag);
};

// mission list vector
struct MissionVec { Obj4c** begin; Obj4c** end; Obj4c** cap; };
struct cSPMission  { Obj4c* GetTargetPlanet(); bool IsActive(); };
struct cSPMissionManager {
    MissionVec* GetMissionList();            // 0x00fedd50
};

// ---------------------------------------------------------------------------
// external callees / globals (address comments feed the equivalence resolver)
// ---------------------------------------------------------------------------
void* PropertyManager();                                    // 0x0067de30
void* StarManager();                                        // 0x00b3d2a0
void* RelationshipManager();                                // 0x00b3d2c0
void* NounManager();                                        // 0x00b3d300
void* GetPlanetModel();                                     // 0x00b3d350
void* SpaceGameGet();                                       // 0x01002bd0
void* GetUFOSimulator();                                    // 0x00ffbe50
int   GetCurrentGameMode();                                 // 0x00b5b800
void* GetMissionManager();                                  // 0x00feb9f0
void* GetPlayerEmpire();                                    // 0x01021300
void* GetPlayerHomePlanet();                                // 0x01021370
void* GetUniverseContext();                                 // 0x01021080
void* IsArchived();                                         // 0x01021240
struct GameNounMgr {
    void* GetAvatar();                                      // 0x00b1fdb0
};
void  GetPropertyAsFloatArray(cPropertyList* list, uint id, int* count, float** out);  // 0x006a08b0
void  GetPropertyAsVector3(cPropertyList* list, uint id, void* out);                    // 0x006a1110
float* PropertyGetFloat(Prop* p);                           // 0x0041ea70
void  CreateMinimapIcon(void* ufo, void* param);            // 0x01042080
void  BuildSurfaceOrientationFwd(void* out, void* in);      // 0x00b81720

struct TerrainSphere {
    float Clamp(unsigned id);   // 0x00c75c30
};
struct NounMgrObj {
    TerrainSphere* GetCurrentTerrainSphere();   // 0x00f67d90
};

extern float g_100;        // 0x013ec4d0
extern float g_0;          // 0x01485378
extern float g_1;          // 0x01485720
extern float g_1_1;        // 0x013ef54c
extern float g_13ec5b4;    // 0x013ec5b4
extern float g_15b7504;    // 0x015b7504
extern cPropertyList* g_15b7518;   // 0x015b7518
extern float g_v0, g_v1, g_v2;     // 0x015b74d0, 0x015b74d4, 0x015b74d8

// property ids kept as extern storage (dynamic keys)
extern unsigned k_autoblaster;       // 0x016de624
extern unsigned k_autoblaster2;      // 0x016de630
extern unsigned k_autoblaster3;      // 0x016de63c
extern float g_16de114;              // 0x016de114
extern float g_16de118;              // 0x016de118
extern float g_16de11c;              // 0x016de11c
extern float g_13eb1bc;              // 0x013eb1bc
extern float g_140f7ac;              // 0x0140f7ac

// ---------------------------------------------------------------------------
// helpers
// ---------------------------------------------------------------------------
template<class T> inline const T& tmin(const T& a, const T& b) { return a < b ? a : b; }
template<class T> inline const T& tmax(const T& a, const T& b) { return a < b ? b : a; }

// ===========================================================================
// @ 0x010297e0
// ===========================================================================
struct C010297e0 {
    char pad[8];
    IUnk* mRef;
    void f();
};
void C010297e0::f() {
    PropertyMgr* pm = (PropertyMgr*)PropertyManager();
    IUnk* old = mRef;
    if (old) {
        mRef = 0;
        old->Release();
    }
    pm->Unregister(0x7436b54a, 0x2ae0c7e, &mRef);
}

// ===========================================================================
// @ 0x01029950
// ===========================================================================
struct cStarManager {
    int    m_885c90();                       // 0x00885c90
    Obj4c* GetEmpireByID(int id);            // 0x00ba9370
};
struct cRelationshipManager {
    bool RecordEvent(Obj4c* a, Obj4c* b);    // 0x00d01f50
};
struct cEmpire { bool IsHostileToPlayer(); };   // 0x00c309e0
struct Inventory;
struct SpaceGame {
    Inventory* GetPlayerInventory();   // 0x00a1ad60
};

struct Planet {
    Obj4c base;                              // vptr @0
    char pad0[0x220 - 4];
    float f220;                              // +0x220
    char pad1[0x544 - 0x224];
    void* f544;                              // +0x544
    char pad2[0x6c8 - 0x548];
    struct Creature* f6c8;                   // +0x6c8
    char pad3[0x714 - 0x6cc];
    int f714;                                // +0x714
    char pad4[0x748 - 0x718];
    float f748;                              // +0x748
};

bool FUN_01029950(Planet* p);

// ===========================================================================
// @ 0x010299c0
// ===========================================================================
struct Inventory {
    Obj68 base;
    bool HasItem(const void* key);           // 0x00ff3bb0
};
int FUN_010299c0() {
    Inventory* inv = ((SpaceGame*)SpaceGameGet())->GetPlayerInventory();
    return inv->HasItem(&k_autoblaster) || inv->HasItem(&k_autoblaster2) ||
           inv->HasItem(&k_autoblaster3);
}

// ===========================================================================
// @ 0x01029a10
// ===========================================================================
bool FUN_01029a10(int empireId, int planetId) {
    if (GetCurrentGameMode() == 0x1654c05) {
        if (empireId == -1) return false;
        if (empireId == ((cStarManager*)StarManager())->m_885c90()) return false;
        if (((cStarManager*)StarManager())->GetEmpireByID(empireId) == 0) return false;
        if (planetId == (int)GetPlayerHomePlanet()) return false;
    }
    return true;
}

// ===========================================================================
// @ 0x01029a60
// ===========================================================================
struct CreatureBase {
    int PlayIdleAnimation(int a, int b);   // 0x00bc96a0
};
struct Creature { char pad[8]; CreatureBase base; };
struct UFOInv { char pad[0x508]; Obj10 f508; };
bool FUN_01029a60(Planet* p, bool b) {
    bool r;
    if (p->f714 == 6) {
        r = b;
    } else {
        cEmpire* emp = (cEmpire*)((cStarManager*)StarManager())->GetEmpireByID(p->base.v4c());
        if (emp == 0 || emp->IsHostileToPlayer()) r = 1;
        else r = 0;
    }
    UFOInv* inv = (UFOInv*)((SpaceGame*)GetUFOSimulator())->GetPlayerInventory();
    if (r == 0) {
        int cur = (int)p->f544;
        if (cur == inv->f508.v10()) r = 1;
    }
    Creature* c = p->f6c8;
    if (c && c->base.PlayIdleAnimation(0x10, 0)) return false;
    return r;
}

// ===========================================================================
// @ 0x01029af0
// ===========================================================================
int cSPSpaceCombatTuning::GetAirRaidSirenTimeMS() {
    float v = 0.0f;
    cPropertyList* pl = mPropList;
    if (pl) {
        Prop* p;
        if (pl->GetProperty(0x289453d, (void**)&p) && p->type == 0xd)
            v = *p->GetFloat();
    }
    return (int)(v * g_13ec5b4);
}

// ===========================================================================
// @ 0x01029cc0
// ===========================================================================
float cSPSpaceCombatTuning::GetBackgroundFighterDPS(int index) {
    float result = 1.0f;
    float* arr = 0;
    int count = 0;
    GetPropertyAsFloatArray(g_15b7518, 0x56b734f, &count, &arr);
    if (count > 0)
        result = arr[tmax(0, tmin(index, count - 1))];
    return result;
}

// ===========================================================================
// @ 0x01029d50
// ===========================================================================
float cSPSpaceCombatTuning::GetBackgroundBomberDPS(int index) {
    float result = 1.0f;
    float* arr = 0;
    int count = 0;
    GetPropertyAsFloatArray(g_15b7518, 0x56b7354, &count, &arr);
    if (count > 0)
        result = arr[tmax(0, tmin(index, count - 1))];
    return result;
}

// ===========================================================================
// @ 0x01029de0
// ===========================================================================
float cSPSpaceCombatTuning::GetBackgroundTurretDPS(int index) {
    float result = 1.0f;
    float* arr = 0;
    int count = 0;
    GetPropertyAsFloatArray(g_15b7518, 0x56b7358, &count, &arr);
    if (count > 0)
        result = arr[tmax(0, tmin(index, count - 1))];
    return result;
}

// ===========================================================================
// @ 0x01029f60
// ===========================================================================
float cSPSpaceCombatTuning::GetLootMinMoneyDrop(int index) {
    if (mPropList) {
        float* arr = 0;
        int count = 0;
        GetPropertyAsFloatArray(mPropList, 0x5d23ad7, &count, &arr);
        if (count > 0)
            return arr[tmin(count - 1, index)];
    }
    return 0.0f;
}

// ===========================================================================
// @ 0x01029fd0
// ===========================================================================
float cSPSpaceCombatTuning::GetLootMaxMoneyDrop(int index) {
    if (mPropList) {
        float* arr = 0;
        int count = 0;
        GetPropertyAsFloatArray(mPropList, 0x5d23ae0, &count, &arr);
        if (count > 0)
            return arr[tmin(count - 1, index)];
    }
    return 0.0f;
}

// ===========================================================================
// @ 0x0102a1d0
// ===========================================================================
float cSPSpaceCombatTuning::GetLootUFOMoneyChance(int type) {
    switch (type) {
    case 4: return GetLootBomberMoneyChance();
    case 2: return GetLootRaiderMoneyChance();
    case 6: return GetLootDefenderMoneyChance();
    case 8: return GetLootInterceptorMoneyChance();
    case 5: return GetLootThiefMoneyChance();
    default: return 0.0f;
    }
}

// ===========================================================================
// @ 0x0102a230
// ===========================================================================
float cSPSpaceCombatTuning::GetLootCityMinMoneyDrop(int index) {
    if (mPropList) {
        float* arr = 0;
        int count = 0;
        GetPropertyAsFloatArray(mPropList, 0x5d282ce, &count, &arr);
        if (count > 0)
            return arr[tmin(count - 1, index)];
    }
    return 0.0f;
}

// ===========================================================================
// @ 0x0102a2a0
// ===========================================================================
float cSPSpaceCombatTuning::GetLootCityMaxMoneyDrop(int index) {
    if (mPropList) {
        float* arr = 0;
        int count = 0;
        GetPropertyAsFloatArray(mPropList, 0x5d282d4, &count, &arr);
        if (count > 0)
            return arr[tmin(count - 1, index)];
    }
    return 0.0f;
}

// ===========================================================================
// @ 0x0102a360
// ===========================================================================
int cSPSpaceCombatTuning::GetWeaponLevel(float x, float y, float z) {
    float* arr = 0;
    int count = 0;
    GetPropertyAsFloatArray(mPropList, 0x578e8dc, &count, &arr);
    float dist = sqrtf(y * y + x * x + z * z);
    int n = 0;
    while (count > 0) {
        count = count - 1;
        if (arr[count] > dist) ++n;
    }
    return n;
}

// ===========================================================================
// @ 0x0102a3e0
// ===========================================================================
struct Vec3 { float x, y, z; };
struct Vec3Holder {
    char pad[8];
    cPropertyList* mPropList;
    Vec3* f();
};
Vec3* Vec3Holder::f() {
    static Vec3 v = { g_v0, g_v1, g_v2 };
    if (mPropList)
        GetPropertyAsVector3(mPropList, 0x5f89281, &v);
    return &v;
}

// ===========================================================================
// @ 0x0102a630
// ===========================================================================
float cSPSpaceCombatTuning::GetUFOHealth(int type, int index) {
    float* arr = 0;
    int count = 0;
    unsigned keys[12] = {
        0x33b0a8d, 0x578ce0c, 0x33b0a8d, 0x5d67a3a,
        0x33b0a90, 0x398f85c, 0x5d67a28, 0x33b0a8d,
        0x5d67a34, 0x33b0a8d, 0x33b0a8d, 0x640f84a
    };
    GetPropertyAsFloatArray(g_15b7518, keys[type], &count, &arr);
    if (count < 1) return g_100;
    int idx = tmin(index, count - 1);
    float mult = 1.0f;
    switch (type) {
    case 1: case 2: case 4: case 5: case 6: case 7: case 8: case 9:
        if (NounManager() && ((NounMgrObj*)NounManager())->GetCurrentTerrainSphere())
            mult = ((NounMgrObj*)NounManager())->GetCurrentTerrainSphere()->Clamp(0xbd68b7c6);
        break;
    case 3:
        mult = ((NounMgrObj*)NounManager())->GetCurrentTerrainSphere()->Clamp(0x17e57dec);
        break;
    }
    return mult * arr[idx];
}

// ===========================================================================
// @ 0x0102a780
// ===========================================================================
float cSPSpaceCombatTuning::GetTurretHealth(int index) {
    float* arr = 0;
    int count = 0;
    GetPropertyAsFloatArray(g_15b7518, 0x57e2cff, &count, &arr);
    if (count > 0)
        return arr[tmin(count - 1, index)];
    return g_100;
}

// ===========================================================================
// @ 0x0102a840
// ===========================================================================
float cSPSpaceCombatTuning::LootChanceA(int type) {
    float v = 1.0f;
    uint id = 0;
    switch (type) {
    case 3:  id = 0x6259d65; break;
    case 6:  id = 0x6259d76; break;
    case 8:  id = 0x6259d7e; break;
    case 2:  id = 0x6259d90; break;
    case 1:  id = 0x6259d99; break;
    case 11: id = 0x6259da2; break;
    }
    cPropertyList* pl = mPropList;
    if (pl) {
        Prop* p;
        if (pl->GetProperty(id, (void**)&p) && p->type == 0xd)
            v = *p->GetFloat();
    }
    return v;
}

// ===========================================================================
// @ 0x0102a8f0
// ===========================================================================
float cSPSpaceCombatTuning::LootChanceB(int type) {
    float v = 1.0f;
    uint id = 0;
    switch (type) {
    case 3:  id = 0x6259dc1; break;
    case 6:  id = 0x6259e0b; break;
    case 8:  id = 0x6259e11; break;
    case 2:  id = 0x6259e17; break;
    case 1:  id = 0x6259e1c; break;
    case 11: id = 0x6259e22; break;
    case 4:  id = 0x6270bf8; break;
    }
    cPropertyList* pl = mPropList;
    if (pl) {
        Prop* p;
        if (pl->GetProperty(id, (void**)&p) && p->type == 0xd)
            v = *p->GetFloat();
    }
    return v;
}

// ===========================================================================
// @ 0x0102aa50
// ===========================================================================
struct Obj2c {   // vtable slot +0x2c: bool()
    virtual void z0(); virtual void z1(); virtual void z2(); virtual void z3();
    virtual void z4(); virtual void z5(); virtual void z6(); virtual void z7();
    virtual void z8(); virtual void z9(); virtual void z10();
    virtual bool pred();
};
bool FUN_01029a60(Planet* p, bool b);
bool FUN_0102aa50(Planet* a, Planet* b, bool c) {
    if (a && ((Obj2c*)a)->pred()) return false;
    if (b && ((Obj2c*)b)->pred()) return false;
    int bType = b->f714;
    int aType = a->f714;
    int bId = b->base.v4c();
    int aId = a->base.v4c();
    switch (bType) {
    case 0: case 3:
        if (aType == 0) return false;
        if (aType == 3) return false;
        if (FUN_01029a60(a, c)) return true;
        if (aType != 8) return false;
        if (GetUniverseContext() != 0) return false;
        if (((GameNounMgr*)IsArchived())->GetAvatar() != (void*)a->base.v4c()) return false;
        return c != 0;
    case 1:
        if (aType != 2 && aType != 4 && aType != 5 && aType != 8) return false;
        if (a->f6c8 == 0) return true;
        if (a->f6c8->base.PlayIdleAnimation(8, 0) != 0) return false;
        return true;
    case 2: case 4: case 5:
        if (b->f6c8->base.PlayIdleAnimation(0x10, 0) == 0 &&
            (aType == 0 || aType == 3) && FUN_01029a60(b, c))
            return true;
        if (aType != 6) return false;
        return bId != aId;
    case 6:
        if ((aType == 2 || aType == 4 || aType == 5) && bId != aId) {
            if (a->f6c8 == 0) return true;
            if (a->f6c8->base.PlayIdleAnimation(8, 0) == 0) return true;
        }
        if (aType != 0 && aType != 3) return false;
        return FUN_01029a60(b, c);
    case 8:
        if (aType != 0 && aType != 3) return false;
        return FUN_01029a60(b, c);
    case 11:
        if (aType == 0 || aType == 3) return true;
        return false;
    default:
        return false;
    }
}

// ===========================================================================
// @ 0x0102ac50
// ===========================================================================
struct NounMgr { Obj0c* CreateNoun(int id); };
void* SP_CreateUFOForSolarOrGalaxy(int arg1, int arg2) {
    Obj0c* n = ((NounMgr*)NounManager())->CreateNoun(0x18ebadc);
    cSPGameDataUFO* d;
    if (n) d = (cSPGameDataUFO*)n->v0c(0xb033b403);
    else d = 0;
    d->Init(arg1, arg2);
    return d;
}

// ===========================================================================
// @ 0x0102acb0
// ===========================================================================
struct PlanetModel {
    char pad[0x24];
    void* mpSphere;
    void GetPosition(Vec3* out);                        // 0x00b81720
    void* BuildSurfaceOrientation(void* out, Vec3* in); // 0x00b7f190
};
void* SP_CreateUFO(int arg1, int* arg2, Vec3* arg3) {
    Obj0c* n = ((NounMgr*)NounManager())->CreateNoun(0x18ebadc);
    cSPGameDataUFO* d;
    if (n) d = (cSPGameDataUFO*)n->v0c(0xb033b403);
    else d = 0;
    void* emp = 0;
    if (*arg2 != -1) {
        extern void* GetEmpireByIDThunk(void* mgr, int id);
        emp = GetEmpireByIDThunk(StarManager(), *arg2);
    }
    d->Init(arg1, (int)emp);
    bool flag;
    Vec3 tmp;
    if (arg3 == 0) {
        if (arg1 == 0) return d;
        tmp.x = -18057132.0f;
        tmp.y = 60056.777f;
        tmp.z = g_15b7504;
        arg3 = &tmp;
        flag = true;
    } else {
        flag = arg1 != 1;
    }
    d->SetDesiredModel(arg3, flag);
    if (arg1 != 0) {
        PlanetModel* pm = (PlanetModel*)GetPlanetModel();
        if (pm && pm->mpSphere) {
            Vec3 p;
            pm->GetPosition(&p);
            Vec3 scaled;
            scaled.x = p.x * 1.1f;
            scaled.y = p.y * 1.1f;
            scaled.z = p.z * 1.1f;
            char orient[16];
            void* orientPtr = pm->BuildSurfaceOrientation(orient, &p);
            extern void FunC3aa40(void* v, void* o);   // 0x00c3aa40
            FunC3aa40(&scaled, orientPtr);
        }
        if (GetCurrentGameMode() == 0x1654c05) {
            extern void* Fun10666a0();   // 0x010666a0
            void* x = Fun10666a0();
            extern void* Fun1067e60();   // 0x01067e60
            void* y = Fun1067e60();
            CreateMinimapIcon(d, y);
            (void)x;
        }
    }
    return d;
}

// ===========================================================================
// @ 0x0102adf0
// ===========================================================================
bool FUN_0102adf0(Obj4c* planet) {
    MissionVec* list = ((cSPMissionManager*)GetMissionManager())->GetMissionList();
    int n = list->end - list->begin;
    for (int i = 0; i < n; ++i) {
        cSPMission* m = (cSPMission*)list->begin[i];
        if ((Obj4c*)m->GetTargetPlanet() == planet) {
            Obj38* o = (Obj38*)m;
            if (o->v38() == 0x397bff2 || o->v38() == 0x3960c0a)
                return m->IsActive();
        }
    }
    return false;
}

// ===========================================================================
// @ 0x0102ae60
// ===========================================================================
bool FUN_0102ae60(Obj4c* planet) {
    MissionVec* list = ((cSPMissionManager*)GetMissionManager())->GetMissionList();
    int n = list->end - list->begin;
    for (int i = 0; i < n; ++i) {
        cSPMission* m = (cSPMission*)list->begin[i];
        if ((Obj4c*)m->GetTargetPlanet() == planet) {
            if (((Obj38*)m)->v38() == 0x3960c0a) return m->IsActive();
        }
    }
    return false;
}

// ===========================================================================
struct DistObj {
    char pad[0x148];
    float f148;
    char pad2[0x1cc - 0x14c];
    float f1cc;
    float Dist() { return f1cc * f148; }   // 0x0104be30
};
// @ 0x0102aec0
bool FUN_0102aec0(DistObj* self, Vec3* a, Vec3* b) {
    float d = self->Dist();
    if (d == g_13eb1bc) d = g_140f7ac;
    else d = self->Dist();
    if ((g_16de114 != b->x || g_16de118 != b->y || g_16de11c != b->z) &&
        sqrtf((b->x - a->x) * (b->x - a->x) +
              (b->y - a->y) * (b->y - a->y) +
              (b->z - a->z) * (b->z - a->z)) > d)
        return true;
    return false;
}
