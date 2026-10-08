// Slice s00bf9300: SP::cCivilization AI "choose a UFO and a target city" step (0x00bf9820, 1614 bytes).
// /O2 /arch:SSE module (movss/ucomiss for float loads and compares, x87 for the planet-distance math).
//
// For an AI civilization (this): keeps its target UFO (+0x468) when it is still valid; every 10 s it
// scores all UFOs (type 0x403df5c) by how close they are to the civ's capital city, penalised for the
// number of other civs already targeting that UFO, then scores the civ's cities by distance to the chosen
// UFO, and buys a vehicle from the best city if the civ can afford it. Finally stores the chosen UFO
// as the new target (AutoRefCount assignment) and restarts the timer.
#include "types.h"

struct Vec3
{
    float x, y, z;
    bool operator==(const Vec3& o) const { return x == o.x && y == o.y && z == o.z; }
    bool operator!=(const Vec3& o) const { return !(*this == o); }
};

// ---------------------------------------------------------------- stubs
class cSpatial
{
public:
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10();
    virtual const Vec3* GetPosition();          // +0x2c (plain ret: callers' pushed args are for other calls)
};

// UFO game data (type 0x403df5c): refcounted, spatial subobject at +0x34.
class cUFO
{
public:
    virtual void AddRef();                      // +0x00
    virtual void Release();                     // +0x04
    char pad4[0x34 - 4];
    cSpatial mSpatial;                          // +0x34
    int FUN_00bfdf80();                         // 0x00bfdf80 (thiscall, plain ret)
};

class cPlanetModel
{
public:
    int GetContinent(const Vec3* pos);                          // 0x00b88590 (ret 4)
    float DistanceBetweenPoints(const Vec3* a, const Vec3* b);  // 0x00b81470 (ret 8)
    float FUN_00b7e4d0();                                       // planet radius (x87 float)
};
cPlanetModel* PlanetModel();                    // 0x00b3d350

struct Bits3 { uint32_t a, b, c; };

// cCity (the civ's cities): spatial subobject at +0x120
class cCity
{
public:
    char pad0[0x120];
    cSpatial mSpatial;                          // +0x120
    int GetVehicleSpecialty();                  // 0x00bd81d0
    int FUN_00bd8210();                         // 0x00bd8210: continent of the city
    const Vec3* FUN_00fa0e00();                 // 0x00fa0e00: &this->field_0x32c
    char FUN_00bdb930(int spec, int flag);      // 0x00bdb930 (ret 8)
    void FUN_00bddda0(int spec, int flag, Bits3 pos, int mode);   // 0x00bddda0 (ret 0x18)
};

class cSPTimer
{
public:
    uint64_t GetElapsedTime();                  // 0x00bc3190
    void Restart();                             // 0x00bc3130
};

struct GameDataVector { uint32_t pad0; void** mpBegin; void** mpEnd; void** mpCap; };
struct PtrVector { void** mpBegin; void** mpEnd; };

void FUN_00cd7d10(); void FUN_00d3d420(); void FUN_00ae5ea0(); void FUN_00b1e500();
typedef void (*GameDataFn)();

class cCivilization;

class cGameNounManager
{
public:
    GameDataVector* GetGameDataVector(GameDataFn a, GameDataFn b, GameDataFn c, GameDataFn d,
                                      uint32_t type);   // 0x00b21340 (ret 0x14)
    cCivilization* GetPlayerCivilization();             // 0x00b25fb0
    PtrVector* FUN_00b25ca0();                          // 0x00b25ca0: civilizations list
    void* GetCurrentTerrainSphere();                    // 0x00f67d90 (cTerrainEditor)
};
cGameNounManager* NounManager();                        // 0x00b3d300
int FUN_00c75420(void* terrainSphere);                  // thiscall on the sphere: field +0x1248
uint32_t GetCurrentGameMode();                          // 0x00b5b800
int FUN_00c9e6d0(int spec, int flag);                   // cdecl

class cSPTerrainSphere
{
public:
    int FUN_00c75420();                                 // 0x00c75420
};

class cCivilizationHelper
{
public:
    Bits3* FUN_00bf9700(int v);                         // 0x00bf9700 (ret 4)
};

// the civilization (AI "space game" state), retail layout: only the used fields.
class cCivilization
{
public:
    char pad0[0x6c];
    cCivilizationHelper mHelper;                        // +0x6c
    char pad6c[0x89 - 0x6c - 1];
    bool mFlag89;                                       // +0x89
    bool mFlag8a;                                       // +0x8a
    char pad8b[0x93 - 0x8b];
    bool mFlag93;                                       // +0x93
    char pad94[0x98 - 0x94];
    float mBudget;                                      // +0x98
    cCity** mCitiesBegin;                               // +0x9c
    cCity** mCitiesEnd;                                 // +0xa0
    char pada4[0x1c8 - 0xa4];
    cSPTimer mTimer;                                    // +0x1c8
    char pad1c9[0x298 - 0x1c8 - 1];
    int mLevel;                                         // +0x298
    char pad29c[0x468 - 0x29c];
    cUFO* mTargetUFO;                                   // +0x468
    char pad46c[0x4ac - 0x46c];
    float mBonusA;                                      // +0x4ac
    float mBonusB;                                      // +0x4b0

    void FUN_00bf9820();                                // 0x00bf9820
    int FUN_00bf7150();                                 // 0x00bf7150
    char FUN_00bf00a0(int continent, int flag);         // 0x00bf00a0 (ret 8)
    char FUN_00beff90(const Vec3* pos, int flag);       // 0x00beff90 (ret 8)
    int FUN_00bf0c60(int spec, int continent, int flag, int zero);   // 0x00bf0c60 (ret 0x10)
    float FUN_00bf2170(int spec, int flag);             // 0x00bf2170 (ret 8): price
    int SpaceTelemetry_Add(int spec);                   // 0x00bf2100 (ret 4)
    void SpendMoney(float amount);                      // 0x00bef710 (ret 4)
};

extern Vec3 g_invalidPos;                               // 0x0168c514
extern float g_radiusScale;                             // 0x0156f89c

// @ 0x00bf9820  FUN_00bf9820
void cCivilization::FUN_00bf9820()
{
    if (!(((char*)mCitiesEnd - (char*)mCitiesBegin) & 0xfffffffc))
        return;
    cCity* capital = *mCitiesBegin;
    if (!capital)
        return;

    cCivilization* player = NounManager()->GetPlayerCivilization();
    if (player)
    {
        cSPTerrainSphere* sphere = (cSPTerrainSphere*)NounManager()->GetCurrentTerrainSphere();
        if (sphere->FUN_00c75420() <= 0)
        {
            int a = player->FUN_00bf7150();
            if (a <= FUN_00bf7150())
            {
                if (mTargetUFO)
                {
                    cUFO* old = mTargetUFO;
                    mTargetUFO = 0;
                    old->Release();
                }
                mTimer.Restart();
                return;
            }
        }
    }

    if (!mTargetUFO || !mTargetUFO->FUN_00bfdf80())
    {
        if (!mFlag93)
        {
            if (mTimer.GetElapsedTime() <= 10000)
                return;
        }
    }

    mFlag93 = false;
    cUFO* best = 0;
    float bestScore = 0.0f;
    GameDataVector* ufos = NounManager()->GetGameDataVector(
        FUN_00cd7d10, FUN_00d3d420, FUN_00ae5ea0, FUN_00b1e500, 0x403df5c);
    void** it = ufos->mpBegin;
    void** end = ufos->mpEnd;
    for (; it != end; ++it)
    {
        cUFO* u = (cUFO*)*it;
        if (u->FUN_00bfdf80())
            continue;
        bool candidate = false;
        if (mLevel >= 1)
        {
            if (FUN_00bf00a0(PlanetModel()->GetContinent(u->mSpatial.GetPosition()), -1))
                candidate = true;
        }
        if (!candidate)
        {
            if (mLevel < 2)
                continue;
            if (!FUN_00beff90(u->mSpatial.GetPosition(), -1))
                continue;
        }
        int count = 0;
        PtrVector* civs = NounManager()->FUN_00b25ca0();
        void** cit = civs->mpBegin;
        void** cend = civs->mpEnd;
        if (cit != cend)
        {
            for (; cit != cend; ++cit)
            {
                cCivilization* other = (cCivilization*)*cit;
                if (other != this && other->mTargetUFO == u)
                {
                    if (other->mFlag8a)
                        count += 1;
                    else
                        count += 2;
                }
            }
            if (count >= 3)
                continue;
        }
        float w = 100.0f;
        if (u == mTargetUFO)
            w = 200.0f;
        const Vec3* uPos = u->mSpatial.GetPosition();
        const Vec3* capPos = capital->mSpatial.GetPosition();
        float dist = PlanetModel()->DistanceBetweenPoints(capPos, uPos);
        float radius = PlanetModel()->FUN_00b7e4d0();
        float score = (((2.0f - dist / (radius * g_radiusScale)) * w) * 8.0f) / (count + 1);
        if (score > bestScore)
        {
            best = u;
            bestScore = score;
        }
    }

    if (best)
    {
        int nCities = (int)(mCitiesEnd - mCitiesBegin);
        cCity* bestCity = 0;
        bestScore = 0.0f;
        for (int i = 0; i < nCities; ++i)
        {
            cCity* city = mCitiesBegin[i];
            bool ok = false;
            if (mLevel >= 1)
            {
                if (city->FUN_00bd8210() == PlanetModel()->GetContinent(best->mSpatial.GetPosition()))
                    ok = true;
            }
            if (!ok)
            {
                if (mLevel < 2)
                    continue;
                const Vec3* p = city->FUN_00fa0e00();
                if (*p == g_invalidPos)
                    continue;
                int cu = PlanetModel()->GetContinent(best->mSpatial.GetPosition());
                if (PlanetModel()->GetContinent(city->FUN_00fa0e00()) != cu)
                    continue;
            }
            const Vec3* uPos = best->mSpatial.GetPosition();
            const Vec3* cPos = city->mSpatial.GetPosition();
            float dist = PlanetModel()->DistanceBetweenPoints(cPos, uPos);
            float radius = PlanetModel()->FUN_00b7e4d0();
            float score = (2.0f - dist / (radius * g_radiusScale)) * 100.0f;
            if (score > bestScore)
            {
                bestCity = city;
                bestScore = score;
            }
        }

        if (bestCity)
        {
            int flag;
            bool go = false;
            if (mLevel >= 2)
            {
                const Vec3* p = bestCity->FUN_00fa0e00();
                if (!(*p == g_invalidPos))
                {
                    int cu = PlanetModel()->GetContinent(best->mSpatial.GetPosition());
                    if (PlanetModel()->GetContinent(bestCity->FUN_00fa0e00()) == cu)
                    {
                        flag = 1;
                        go = true;
                    }
                }
            }
            if (!go)
            {
                if (mLevel >= 1)
                {
                    int cu = PlanetModel()->GetContinent(best->mSpatial.GetPosition());
                    if (bestCity->FUN_00bd8210() == cu)
                    {
                        flag = 0;
                        go = true;
                    }
                }
            }
            if (go)
            {
                const Vec3* pos = best->mSpatial.GetPosition();
                int cont = PlanetModel()->GetContinent(pos);
                if (!FUN_00bf0c60(bestCity->GetVehicleSpecialty(), cont, flag, 0))
                {
                    if (bestCity->FUN_00bdb930(bestCity->GetVehicleSpecialty(), flag))
                    {
                        float price = FUN_00bf2170(bestCity->GetVehicleSpecialty(), flag);
                        float budget = mBudget;
                        if (!mFlag89)
                            budget = (mBonusA + budget) + mBonusB;
                        if (price <= budget)
                        {
                            if (SpaceTelemetry_Add(bestCity->GetVehicleSpecialty()) > 0)
                            {
                                Bits3* bits = mHelper.FUN_00bf9700(FUN_00c9e6d0(bestCity->GetVehicleSpecialty(), flag));
                                bool special = GetCurrentGameMode() == 0x1654c05;
                                bestCity->FUN_00bddda0(bestCity->GetVehicleSpecialty(), flag, *bits, special);
                                SpendMoney(price);
                            }
                        }
                    }
                }
            }
        }
    }

    cUFO* old = mTargetUFO;
    if (best != old)
    {
        if (best)
            best->AddRef();
        mTargetUFO = best;
        if (old)
            old->Release();
    }
    mTimer.Restart();
}
