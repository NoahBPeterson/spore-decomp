// Slice s00c5c860 - SP::DoBuildingDamage (PDB candidate name): background space-combat damage
// applied to one planet's turrets, cities and the attacking UFO groups for a time step.
// Layout notes: retail offsets come from the disassembly; stub classes carry only what is read.
#include "types.h"

namespace SP {

struct Vec3 {
    float x, y, z;
    Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {}
};

struct PropertyList {
    virtual int AddRef();
    virtual int Release();
};
bool GetFloatProperty(PropertyList* list, uint32_t propertyID, float& result);   // 0x40cf10

struct PropertyManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyList** ppDst);   // +0x2c
};
PropertyManager* GetPropertyManager();   // 0x67de30

template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T** AsPPTypeParam()
    {
        if (mpObject) {
            T* p = mpObject;
            mpObject = 0;
            p->Release();
        }
        return &mpObject;
    }
};

struct cSPSpaceCombatTuning {
    int   GetWeaponLevel(Vec3 pos);                       // 0x102a360 (ret 0xc)
    float GetBackgroundTurretDPS(int level);              // 0x1029de0
    float GetBackgroundBomberDPS(int level);              // 0x1029d50
    float GetBackgroundFighterDPS(int level);             // 0x1029cc0
    float GetBackgroundUberTurretDPS();                   // 0x1029e70
    float GetTurretHealth(int level);                     // 0x102a780
    float GetUFOHealth(int type, int level);              // 0x102a630
    float GetCityCaptureFactor(int politicalID, int);     // 0x1029be0
};
cSPSpaceCombatTuning* GetSpaceCombatTuning();             // 0x1029940

struct cEmpire {
    float GetBackgroundFighterDPS();                      // 0xc31890
    float GetBackgroundBomberDPS();                       // 0xc318c0
    float GetBackgroundTurretDPS();                       // 0xc318f0
    float GetUFOHealth(int type);                         // 0xc31920
    float GetTurretHealth();                              // 0xc31960
};

struct cStarManager {
    cEmpire* GetEmpireByID(int id);                       // 0xba9370
};
cStarManager* StarManager();                              // 0xb3d2a0

struct cCivData {
    const Vec3& GetCities();                              // 0x5c65e0
};

struct cOwnerNoun {
    int GetAvatar();                                      // 0xb1fdb0 (field at +0x54)
};

struct SimpleVectorU {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    void DoInsertValue(uint32_t* pos, const uint32_t& v);     // 0x4558a0
    void push_back(const uint32_t& v)
    {
        if (mpEnd < mpCapacity) {
            uint32_t* p = mpEnd++;
            if (p)
                *p = v;
        }
        else
            DoInsertValue(mpEnd, v);
    }
};

struct cCity {
    uint8_t  pad00[0x24];
    int      mnCount;               // +0x24
    uint8_t  pad28[0xbc - 0x28];
    uint32_t mTurretKeyA;           // +0xbc
    uint32_t mTurretKeyB;           // +0xc0
    int      GetCount();                                  // 0xff35d0
    int      GetNumTurrets();                             // 0xff0760
    int      GetNumBuildings();                           // 0xff0870
    float    GetHealth();                                 // 0xb7e0a0
    int      GetOwnerID();                                // 0xa1ad10
    void     RemoveTurret();                              // 0xff07e0
    void     SetCount(int n);                             // 0x9879d0
};

struct cCityGroup {
    uint8_t  pad00[0x3c];
    cCity**  mpCitiesBegin;         // +0x3c
    cCity**  mpCitiesEnd;           // +0x40
    int      GetOwnerID();                                // 0xff0420
    int      CityCount() const { return (int)(mpCitiesEnd - mpCitiesBegin); }
};

struct BuildingRec {
    uint32_t id;                    // +0x00
    uint8_t  pad04[0x10];
    float    health;                // +0x14
    uint8_t  pad18[0x10];
    uint32_t flags;                 // +0x28
};

struct ForceElem {
    uint32_t pad00;
    int      type;                  // +4
    uint8_t  pad08[0x18];
};

struct cPlanetRecord {
    uint8_t  pad00[0x134];
    BuildingRec* mpRecBegin;        // +0x134
    BuildingRec* mpRecEnd;          // +0x138
    uint8_t  pad13c[0x148 - 0x13c];
    SimpleVectorU mDestroyedKeys;   // +0x148
    uint8_t  pad154[0x15c - 0x154];
    cCityGroup** mpGroupsBegin;     // +0x15c
    cCityGroup** mpGroupsEnd;       // +0x160
    cOwnerNoun* GetOwner();                               // 0xb8de30
    cCityGroup* GetGroup(int i);                          // 0xb8dec0
    bool        HasBuildingRec(uint32_t id);              // 0xb8e040
    void        RemoveBuildingRec(uint32_t id);           // 0xb8e7d0
    int RecCount() const { return (int)(mpRecEnd - mpRecBegin); }
    int GroupCount() const { return (int)(mpGroupsEnd - mpGroupsBegin); }
};

struct cForceList {
    ForceElem* mpBegin;             // +0
    ForceElem* mpEnd;               // +4
};

struct cBattle {
    uint8_t    pad00[0x13c];
    cPlanetRecord* mpPlanet;        // +0x13c
    void FUN_00c711e0(cCity* city);                       // 0xc711e0
};

extern uint32_t kPlaceUberTurretID;                       // 0x16922ac

bool    FUN_00fe3b10(cBattle* b);                         // cdecl
void*   FUN_0107bcb0();                                   // 0x107bcb0 (global getter)
cPlanetRecord* GetPlayerHomePlanet();                  // 0x1021370
int     FUN_00c702f0(cPlanetRecord* p);                   // cdecl
bool    FUN_01029a10(int politicalID, cPlanetRecord* p);  // cdecl
float   FUN_00bd7fb0(int, int);                           // cdecl
void    FUN_00be9b20(cPlanetRecord* p, int zero, cCity* city, int groupOwner, float amount);   // cdecl
ForceElem* EraseCopy(ForceElem* srcBegin, ForceElem* srcEnd, ForceElem* dst);   // 0xc5b450 cdecl

struct cGameDataStub {
    int GetGameDataOwner();                               // 0x967e70 (field at +0x2c)
};

// @ 0x00c5c860
void DoBuildingDamage(cForceList* pForces, cBattle* pBattle, int attackerID, int* pnType4, int* pnType2,
                      int unused, float* pTurretLeft, float* pForceLeft, bool* pbHaveRec, uint32_t dtMs)
{
    if (FUN_00fe3b10(pBattle))
        return;

    cPlanetRecord* planet = pBattle->mpPlanet;
    int avatarID = planet->GetOwner()->GetAvatar();
    cCivData* civ = (cCivData*)planet->GetOwner();
    if (avatarID == attackerID)
        return;

    if (planet == GetPlayerHomePlanet()) {
        int owner = ((cGameDataStub*)FUN_0107bcb0())->GetGameDataOwner();
        if (FUN_00c702f0(planet) < owner)
            return;
    }

    cSPSpaceCombatTuning* tuning = GetSpaceCombatTuning();
    cEmpire* attacker = StarManager()->GetEmpireByID(attackerID);
    cEmpire* avatar = StarManager()->GetEmpireByID(avatarID);
    int level = tuning->GetWeaponLevel(civ->GetCities());

    float turretDPS = avatar ? avatar->GetBackgroundTurretDPS() : tuning->GetBackgroundTurretDPS(level);
    float bomberDPS, fighterDPS;
    if (attacker) {
        bomberDPS = attacker->GetBackgroundBomberDPS();
        fighterDPS = attacker->GetBackgroundFighterDPS();
    }
    else {
        bomberDPS = tuning->GetBackgroundBomberDPS(level);
        fighterDPS = tuning->GetBackgroundFighterDPS(level);
    }
    float uberDPS = tuning->GetBackgroundUberTurretDPS();
    float turretHealth = avatar ? avatar->GetTurretHealth() : tuning->GetTurretHealth(level);
    float ufoHealth4, ufoHealth2;
    if (attacker) {
        ufoHealth4 = attacker->GetUFOHealth(4);
        ufoHealth2 = attacker->GetUFOHealth(2);
    }
    else {
        ufoHealth4 = tuning->GetUFOHealth(4, level);
        ufoHealth2 = tuning->GetUFOHealth(2, level);
    }

    AutoRefCount<PropertyList> props;
    GetPropertyManager()->GetPropertyList(0xa4c2f6bd, 0, props.AsPPTypeParam());
    float buildingHealth = 10.0f;
    float cityHealth = 10.0f;
    GetFloatProperty(props.mpObject, 0x7d566743, cityHealth);
    GetFloatProperty(props.mpObject, 0x17efa840, buildingHealth);

    int quot = *pnType2;
    int n = 1;
    int hasType4 = 0;
    if (*pnType4 != 0) {
        quot = *pnType2 / *pnType4;
        n = *pnType4;
        hasType4 = 1;
    }
    float dtSec = (float)dtMs * 0.001f;
    float acc = 0.0f;
    float damage = *pTurretLeft / (float)n + dtSec * ((float)quot * fighterDPS + (float)hasType4 * bomberDPS);
    *pTurretLeft = 0.0f;

    bool bPlayerSide = FUN_01029a10(attackerID, planet);

    if (*pbHaveRec && n > 0) {
        int nRec = planet->RecCount();
        if (nRec > 0) {
            BuildingRec* rec = planet->mpRecBegin;
            for (int i = 0; i < nRec; ++i, ++rec) {
                if ((rec->flags & 1) && rec->id != kPlaceUberTurretID) {
                    float h = rec->health - damage;
                    rec->health = h;
                    if (!(0.0f < h)) {
                        planet->RemoveBuildingRec(rec->id);
                        *pbHaveRec = false;
                    }
                    --n;
                    break;
                }
            }
        }
    }

    int iGroup = 0;
    if (planet->GroupCount() > 0) {
        do {
            if (n <= 0)
                goto done_cities;
            cCityGroup* group = planet->GetGroup(iGroup);
            bool emptied = false;
            int groupOwner = group->GetOwnerID();
            int iCity = 0;
            if (group->CityCount() > 0) {
                while (n > 0) {
                    cCity* city = group->mpCitiesBegin[iCity];
                    bool destroyed = false;
                    int cityCount = city->GetCount();
                    int nTurrets = city->GetNumTurrets();
                    int nBuildings = city->GetNumBuildings();
                    float health = city->GetHealth();
                    int owner = city->GetOwnerID();
                    if (bPlayerSide && owner == attackerID && !(health < 100.0f)) {
                        ++iCity;
                    }
                    else {
                        acc = (float)nTurrets * turretDPS * dtSec + acc;
                        float rem = damage;
                        while (rem > 0.0f) {
                            if (nTurrets > 0 && rem >= turretHealth) {
                                city->RemoveTurret();
                                rem = rem - turretHealth;
                            }
                            else if (nBuildings > 1 && rem >= buildingHealth) {
                                city->SetCount(cityCount - 1);
                                if (bPlayerSide)
                                    FUN_00be9b20(planet, 0, city, groupOwner, FUN_00bd7fb0(attackerID, 0));
                                rem = rem - buildingHealth;
                            }
                            else if (nBuildings == 1) {
                                if (bPlayerSide) {
                                    FUN_00be9b20(planet, 0, city, groupOwner,
                                                 tuning->GetCityCaptureFactor(attackerID, 0) * rem);
                                    break;
                                }
                                if (rem >= cityHealth) {
                                    uint32_t k = city->mTurretKeyA;
                                    if (k)
                                        planet->mDestroyedKeys.push_back(k);
                                    k = city->mTurretKeyB;
                                    if (k)
                                        planet->mDestroyedKeys.push_back(k);
                                    if (group->CityCount() == 1)
                                        emptied = true;
                                    pBattle->FUN_00c711e0(city);
                                    *pTurretLeft = (rem - cityHealth) + *pTurretLeft;
                                    destroyed = true;
                                    break;
                                }
                                *pTurretLeft = *pTurretLeft + rem;
                                break;
                            }
                            else {
                                *pTurretLeft = *pTurretLeft + rem;
                                break;
                            }
                        }
                        --n;
                        if (!destroyed)
                            ++iCity;
                    }
                    if (!(iCity < group->CityCount()))
                        break;
                }
                if (emptied)
                    continue;
            }
            ++iGroup;
        } while (iGroup < planet->GroupCount());
    }
    if (n > 0)
        *pTurretLeft = (float)n * damage + *pTurretLeft;

done_cities:
    int hasUber = 0;
    if (pBattle->mpPlanet && pBattle->mpPlanet->HasBuildingRec(kPlaceUberTurretID))
        hasUber = 1;
    float total = (float)hasUber * uberDPS * dtSec + acc + *pForceLeft;
    *pForceLeft = 0.0f;

    ForceElem* it = pForces->mpBegin;
    while (it != pForces->mpEnd && it->type != 2)
        ++it;
    if (*pnType2 > 0) {
        while (*pnType2 > 0 && total >= ufoHealth2 && it != pForces->mpEnd) {
            if (it->type == 2) {
                if (it + 1 < pForces->mpEnd)
                    EraseCopy(it + 1, pForces->mpEnd, it);
                --pForces->mpEnd;
                --*pnType2;
                total -= ufoHealth2;
            }
            else
                it = pForces->mpEnd;
        }
    }
    if (!(*pnType2 > 0)) {
        it = pForces->mpBegin;
        if (it != pForces->mpEnd && it->type != 4)
            it = pForces->mpEnd;
        while (*pnType4 > 0 && total >= ufoHealth4 && it != pForces->mpEnd) {
            if (it->type == 4) {
                if (it + 1 < pForces->mpEnd)
                    EraseCopy(it + 1, pForces->mpEnd, it);
                --pForces->mpEnd;
                --*pnType4;
                total -= ufoHealth4;
            }
            else
                it = pForces->mpEnd;
        }
    }
    *pForceLeft = total;
}

} // namespace SP
