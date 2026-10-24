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

struct ConstraintVector;
struct Tri;

class cCivilizationHelper
{
public:
    uint32_t m_pad00;                                   // +0x00
    uint32_t m_sentinel[6];                             // +0x04 (rbtree links + node pool)
    void Find(void** out, int* key);                    // 0x00e39fb0
    void FUN_00bf9300(int key);                         // 0x00bf9300
    Bits3* FUN_00bf3cb0(int* key);                      // 0x00bf3cb0
    Bits3* FUN_00bf9700(int v);                         // 0x00bf9700 (ret 4)
    void FUN_00bf30b0(int key, Tri* out);               // 0x00bf30b0
    void FUN_00bf8ff0(ConstraintVector* vec, int key, Bits3* out); // 0x00bf8ff0
};

// the civilization (AI "space game" state), retail layout: only the used fields.
class cCivilization
{
public:
    char pad0[0x6c];
    cCivilizationHelper mHelper;                        // +0x6c
    char pad6c[0x89 - 0x6c - sizeof(cCivilizationHelper)];
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
    void FUN_00bf9790();                                // 0x00bf9790
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

uint32_t g_168cb60;  // 0x0168cb60
uint32_t g_168cb54;  // 0x0168cb54
uint32_t g_168cb58;  // 0x0168cb58
uint32_t g_168cb5c;  // 0x0168cb5c

// @ 0x00bf9700
Bits3* cCivilizationHelper::FUN_00bf9700(int v)
{
    if ((g_168cb60 & 1) == 0) {
        g_168cb60 |= 1;
        g_168cb54 = 0;
        g_168cb58 = 0;
        g_168cb5c = 0;
    }

    void* found;
    Find(&found, &v);
    if (found != (char*)this + 4)
        return (Bits3*)((char*)found + 0x14);

    FUN_00bf9300(v);
    return FUN_00bf3cb0(&v);
}

// @ 0x00bf9790
void cCivilization::FUN_00bf9790()
{
    Bits3* p = mHelper.FUN_00bf9700(0x4e3f7777);
    if (p->a == 0 && p->b == 0 && p->c == 0)
        mHelper.FUN_00bf9300(0x4e3f7777);

    p = mHelper.FUN_00bf9700(0x47c10953);
    if (p->a == 0 && p->b == 0 && p->c == 0)
        mHelper.FUN_00bf9300(0x47c10953);

    p = mHelper.FUN_00bf9700(0x72c49181);
    if (p->a == 0 && p->b == 0 && p->c == 0)
        mHelper.FUN_00bf9300(0x72c49181);
}

// ---------------------------------------------------------------- FunctionalMatch
struct Tri { int a, b, c; };

namespace eastl
{
struct allocator { uint32_t mName; uint32_t mFlags; };
struct sp_vector_allocator : allocator {};

template <class T, class A>
struct vector
{
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    A mAllocator;

    vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~vector() {}
    void push_back(const T& value) {
        if (mpEnd < mpCapacity) {
            *mpEnd = value;
            ++mpEnd;
        }
    }
    void resize(uint32_t count) { (void)count; }
};
}

namespace SP { namespace FunctionalMatch
{
enum eType {
    kInteger = 48342877,
    kFloat = 48343039,
    kTerminal = 48343507,
    kNotEqual = 0xcba453f7
};
enum EqualConstraint { kEquals = 0 };
enum RangeConstraint { kBetween = 0 };

struct Constraint
{
    uint32_t mParameter;
    int mType;
    union {
        struct { int mMin; int mMax; } mIntVal;
        struct { float mMin; float mMax; } mFloatVal;
    };
    eastl::vector<Constraint, eastl::sp_vector_allocator> mConstraints;

    Constraint() : mParameter(0), mType(kTerminal) {}
    Constraint(uint32_t param, RangeConstraint, float minVal, float maxVal)
        : mParameter(param), mType(kFloat)
    {
        mFloatVal.mMin = minVal;
        mFloatVal.mMax = maxVal;
    }
    Constraint(uint32_t param, EqualConstraint, int value)
        : mParameter(param), mType(kInteger)
    {
        mIntVal.mMin = value;
        mIntVal.mMax = value + 1;
    }
};
}}

class ConstraintVector : public eastl::vector<SP::FunctionalMatch::Constraint, eastl::sp_vector_allocator>
{
public:
    void Add(const SP::FunctionalMatch::Constraint& c) { push_back(c); }
    void Resize(uint32_t n) { resize(n); }
};

// ---------------------------------------------------------------- property manager
struct Property
{
    char pad0[0x12];
    uint16_t mnType;             // +0x12
    float* GetFloat();           // 0x0041ea70
};

class PropertyList
{
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08();
    virtual bool GetProperty(uint32_t propertyID, Property*& result);  // +0x24
};

class IPropertyManager
{
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyList** out); // +0x30
};

IPropertyManager* PropertyManager();  // 0x0067de30

// ---------------------------------------------------------------- object template DB
class cObjectTemplateDB
{
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v1a(); virtual void v1b();
    virtual void v1c(); virtual void v1d(); virtual void v1e(); virtual void v1f();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v2a(); virtual void v2b();
    virtual void v2c(); virtual void v2d(); virtual void v2e(); virtual void v2f();
    virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33();
    virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37();
    virtual void v38();
    virtual void FindTriangles(Bits3* out, int count, Tri* tri, Bits3* pos);  // +0x3c
    virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
    virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
    virtual void v48(); virtual void v49(); virtual void v4a(); virtual void v4b();
    virtual void v4c(); virtual void v4d(); virtual void v4e(); virtual void v4f();
    virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53();
    virtual void v54(); virtual void v55(); virtual void v56(); virtual void v57();
    virtual void SetPosition(Bits3* pos, int count);  // +0x58
};

cObjectTemplateDB* ObjectTemplateDB();  // 0x0067cb40
void FUN_00c75570(cSPTerrainSphere* sphere); // 0x00c75570

// @ 0x00bf9300
void cCivilizationHelper::FUN_00bf9300(int key)
{
    cObjectTemplateDB* db = ObjectTemplateDB();
    if (NounManager()->GetCurrentTerrainSphere() != 0)
        NounManager()->GetCurrentTerrainSphere();

    if (db == 0)
        return;

    ConstraintVector constraints;
    float radius = 0.1f;
    PropertyList* pList = 0;
    Property* pProperty = 0;

    PropertyManager()->GetPropertyList(0xcc271289, 0x6087cb6, &pList);
    if (pList != 0 &&
        pList->GetProperty(0x6087cb6, pProperty) &&
        pProperty->mnType == 0xd) {
        float* value = pProperty->GetFloat();
        if (value != 0)
            radius = *value;
    }

    Bits3 position;
    position.a = 0;
    position.b = 0;
    position.c = 0;
    Tri triangle;
    triangle.a = 0;
    triangle.b = 0;
    triangle.c = 0;

    if (key == 0x99e92f05 || key == 0x4e3f7777 ||
        key == 0x47c10953 || key == 0x72c49181) {
        constraints.Add(SP::FunctionalMatch::Constraint(
            key, SP::FunctionalMatch::kBetween, radius, 3.4028234e38f));
    } else if (key == 0x2090a11b || key == (int)0xbc1041e6u ||
               key == (int)0xc15695dau) {
        FUN_00bf8ff0(&constraints, key, &position);
    } else {
        constraints.Add(SP::FunctionalMatch::Constraint(
            key, SP::FunctionalMatch::kBetween, 1.75f, 4.2f));
        constraints.Add(SP::FunctionalMatch::Constraint(
            key, SP::FunctionalMatch::kBetween, 0.0f, 3.4028234e38f));
        constraints.Add(SP::FunctionalMatch::Constraint(
            key, SP::FunctionalMatch::kEquals, 0));
        FUN_00bf30b0(key, &triangle);
        db->FindTriangles(&position, 1, &triangle, &position);
        db->SetPosition(&position, 1);
    }

    Bits3* result = FUN_00bf3cb0(&key);
    result->a = position.a;
    result->b = position.b;
    result->c = position.c;
}

void cCivilizationHelper::FUN_00bf30b0(int key, Tri* out)
{
    int mapped = -1;
    switch (key) {
    case 0x441cd3e6:
    case 0x8f963dcb:
        mapped = 0x7d433fad;
        break;
    case 0x1f2a25b6:
    case 0x449c040f:
        mapped = 0x9ad7d4aa;
        break;
    case 0x1a4e0708:
    case 0x2a5147a9:
        mapped = 0xf670aa43;
        break;
    case 0x4e3f7777:
    case 0x47c10953:
    case 0x72c49181:
        mapped = 0x99e92f05;
        break;
    }

    void* node = 0;
    Find(&node, &mapped);
    if (node != (char*)this + 4) {
        Bits3* value = FUN_00bf3cb0(&mapped);
        out->a = value->a;
        out->b = value->b;
        out->c = value->c;
        return;
    }
    out->a = -1;
    out->b = -1;
    out->c = -1;
}

void cCivilizationHelper::FUN_00bf8ff0(ConstraintVector* vec, int key, Bits3* out)
{
    Bits3* value = FUN_00bf3cb0(&key);
    value->a = out->a;
    value->b = out->b;
    value->c = out->c;
    vec->Add(SP::FunctionalMatch::Constraint(
        key, SP::FunctionalMatch::kEquals, 0));
}
