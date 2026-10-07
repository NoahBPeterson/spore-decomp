// Slice s00ff6a50: civilization loader for the planet sim (0x00FF6A50, 2719 bytes).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (scalar SSE compares; no /EHsc: the string16 locals have
// no EH frame), the same as the neighbouring cSPSimPlanetHighLOD code (s00ff7530).
//
// What it does: for one SP::cCivData record (the planet save data of one civilization) it finds or
// creates the cCivilization noun for the civ's political ID, sets its name/colour/wealth/model keys,
// then rebuilds every saved city (cCityData) whose position is set: creates the cCity, restores its
// fields, and either lays the city out fresh (no saved buildings) or recreates the city hall data,
// every building noun and every ornament noun from the saved data, then posts a "city created"
// behavior message. Finally it recreates every saved vehicle (cVehicleData): a vehicle with a zero
// position becomes a message to the capital, the others become cVehicle nouns.
// Called once per civ from 0x00FF9A22 with ecx = arg 2 (`this` is not used).
// Names of FUN_ callees are descriptive (from what they store/return), not PDB names.
#include "types.h"

typedef unsigned short char16;

extern "C" long __cdecl _InterlockedExchange(volatile long* target, long value);
#pragma intrinsic(_InterlockedExchange)

void* operator new(unsigned int size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0
extern "C" void __cdecl operator_delete_arr(void* p);              // 0x00f47380 (operator delete[])
extern const char16 gEmptyString16[1];                              // 0x01667bac

// ---- math -----------------------------------------------------------------------------------
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    bool operator==(const Vector3& v) const { return x == v.x && y == v.y && z == v.z; }
    bool operator!=(const Vector3& v) const { return x != v.x || y != v.y || z != v.z; }
};
extern const Vector3 kZeroVector;                                  // 0x016db418
struct Quaternion { float x, y, z, w; };
struct ResourceKey { uint32_t instanceID, typeID, groupID; };
extern const ResourceKey kPlayerColorKey;                          // 0x01572b54

// ---- EASTL ------------------------------------------------------------------------------------
struct string16 {
    char16* mpBegin;
    char16* mpEnd;
    char16* mpCapacity;
    uint32_t mAllocator;
    string16() {
        mpBegin = mpEnd = (char16*)gEmptyString16;
        mpCapacity = mpBegin + 1;
    }
    ~string16() {
        if ((mpCapacity - mpBegin) > 1) {
            if (mpBegin)
                operator_delete_arr(mpBegin);
        }
    }
    bool empty() const { return mpBegin == mpEnd; }
    const char16* c_str() const { return mpBegin; }
    void assign(const char16* pBegin, const char16* pEnd);         // 0x00423650
    static unsigned int CharStrlen(const char16* p) {
        const char16* pCurrent = p;
        while (*pCurrent)
            ++pCurrent;
        return (unsigned int)(pCurrent - p);
    }
    string16& operator=(const string16& x) {
        if (&x != this)
            assign(x.mpBegin, x.mpEnd);
        return *this;
    }
    string16& operator=(const char16* p) {
        assign(p, p + CharStrlen(p));
        return *this;
    }
};

// eastl::vector with sp_vector_allocator (retail: 0x14 bytes).
template <typename T> struct sp_vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];
    bool empty() const { return mpBegin == mpEnd; }
    unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
    T& operator[](unsigned int n) { return mpBegin[n]; }
    const T& operator[](unsigned int n) const { return mpBegin[n]; }
};

template <typename T> inline const T& min_ref(const T& a, const T& b) { return (b < a) ? b : a; }

// ---- save data --------------------------------------------------------------------------------
struct cBuildingData {                   // 0x38
    Vector3 mPosition;                   // +00
    Quaternion mOrientation;             // +0c
    float mHealthPoints;                 // +1c
    int mDamageState;                    // +20
    bool mConnected;                     // +24
    bool mbUnk25;                        // +25
    uint16_t pad26;
    int mEffectiveness;                  // +28
    int mFreezeCount;                    // +2c
    int mSlot;                           // +30
    uint32_t mClassId;                   // +34
};

struct cOrnamentData {                   // 0x34
    Vector3 mPosition;                   // +00
    Quaternion mOrientation;             // +0c
    float mHealthPoints;                 // +1c
    int mDamageState;                    // +20
    ResourceKey mModelKey;               // +24
    uint32_t mClassId;                   // +30
};

struct cVehicleData {                    // 0x14
    Vector3 mPosition;                   // +00
    int mLocomotion;                     // +0c
    int mPurpose;                        // +10
    const Vector3& GetPosition();        // 0x00572590
    int GetLocomotion();                 // 0x00fc7e50
    int GetPurpose();                    // 0x007f54d0
};

struct cCityData {
    uint32_t pad00[0x30 / 4];
    float mSpiceProduction;              // +30
    int mSize;                           // +34
    uint32_t pad38[(0x7c - 0x38) / 4];
    sp_vector<cBuildingData> mBuildings; // +7c
    sp_vector<cOrnamentData> mOrnaments; // +90
    uint32_t padA4[(0xb8 - 0xa4) / 4];
    int mLayout;                         // +b8
    int mFieldBC;                        // +bc
    int mFieldC0;                        // +c0

    const Vector3& GetPosition();        // 0x00572590
    const string16& GetName();           // 0x00ff0390
    const uint32_t& GetBuildingLinks();  // 0x00ff03a0
    int GetMaxSize();                    // 0x00ff35d0
    void SetMaxSize(int n);              // 0x009879d0
    float GetHappiness();                // 0x00b7e0a0
    int GetIncome();                     // 0x00a1ad10
    const Quaternion& GetOrientation();  // 0x008dc790
    uint8_t GetTurretLocations();        // 0x00ffc0c0
    void RestoreWalls(struct cCity* city, int planetType);      // 0x00ff2810
    void RestoreCityWalls(int size, int planetType);            // 0x00ff1da0
};

struct cCivData {
    sp_vector<ResourceKey> mModelKeys;   // +00
    int GetPoliticalID();                // 0x00ff0420
    int GetColorID();                    // 0x006c0200
    float GetWealth();                   // 0x00fd9410
    const sp_vector<cVehicleData*>& GetVehicles();  // 0x00830a50
    const sp_vector<cCityData*>& GetCities();       // 0x005c65e0
    const ResourceKey& GetResourceKey(const cBuildingData* data);  // 0x00ff0cd0
    void LoadModelKeys(void* dst);       // 0x00ff3540
    void DefaultModelKeys(void* dst);    // 0x00ff3190
};

// ---- nouns ------------------------------------------------------------------------------------
class cSpatial {
public:
    virtual void _v00(); virtual void _v04();
    virtual void SetOwner(uint32_t v);                       // 08
    virtual void _v0c(); virtual void _v10(); virtual void _v14(); virtual void _v18();
    virtual void _v1c(); virtual void _v20(); virtual void _v24(); virtual void _v28();
    virtual int GetModelID();                                // 2c
    virtual void _v30(); virtual void _v34();
    virtual void SetPosition(const Vector3& v);              // 38
    virtual void SetOrientation(const Quaternion& q);        // 3c
    virtual void _v40(); virtual void _v44(); virtual void _v48(); virtual void _v4c();
    virtual void _v50(); virtual void _v54(); virtual void _v58(); virtual void _v5c();
    virtual void _v60(); virtual void _v64(); virtual void _v68(); virtual void _v6c();
    virtual void _v70(); virtual void _v74(); virtual void _v78(); virtual void _v7c();
    virtual void _v80(); virtual void _v84(); virtual void _v88(); virtual void _v8c();
    virtual void _v90();
    virtual void SetModelKey(const ResourceKey& key);        // 94
};

class cGameData {
public:
    virtual int AddRef();                                    // 00
    virtual int Release();                                   // 04
    virtual void _v08();
    virtual void* Cast(uint32_t typeID);                     // 0c
};

struct cCombatant {
    void SetHealthPoints(float hp);      // 0x00f924e0
    void SetDamageState(int state);      // 0x00bfc460
};

template <typename T> inline T* object_cast(cGameData* p, uint32_t typeID)
{
    return p ? (T*)p->Cast(typeID) : 0;
}

struct cSPTimer { void Restart(); };     // 0x00bc3130

struct cCity;
class cBuilding {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2c();
    virtual void _v30(); virtual void _v34(); virtual void _v38(); virtual void _v3c();
    virtual void _v40(); virtual void _v44(); virtual void _v48(); virtual void _v4c();
    virtual void _v50();
    virtual void SetCity(cCity* city);                       // 54
    uint32_t pad04[(0x34 - 4) / 4];
    cSpatial mSpatial;                                       // +34
    uint32_t pad38[(0x120 - 0x38) / 4];
    cCombatant mCombatant;                                   // +120
    uint32_t pad124[(0x258 - 0x124) / 4];
    cSPTimer mTimer;                                         // +258
    uint32_t pad25C[(0x28c - 0x25c) / 4];
    int mEffectiveness;                                      // +28c

    void SetConnected(bool b);           // 0x00bcc6e0
    void SetUnk25(bool b);               // 0x00bcd550
    void SetFreezeCount(int n);          // 0x00bcc760
};

class cOrnament {
public:
    virtual void _v00();
    uint32_t pad04[(0x70 - 4) / 4];
    cSpatial mSpatial;                                       // +70
    void SetModel(uint32_t groupID, uint32_t politicalID, uint32_t instanceID);  // 0x00c6f770
};

struct cBuildingNet {
    void AddBuilding(cBuilding* b);      // 0x00afa030
};
struct cCityGrid {
    cBuildingNet* GetNet(int modelID);   // 0x00afad70
};

struct cCityState {
    uint32_t pad[0x350 / 4];
    bool mbRestored;                     // +350
    void SetActive(int b);               // 0x00becd70
};

struct cCity {
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2c();
    virtual void _v30(); virtual void _v34(); virtual void _v38(); virtual void _v3c();
    virtual void _v40(); virtual void _v44();
    virtual void SetPoliticalID(int id);                     // 48
    virtual void _v4c(); virtual void _v50(); virtual void _v54(); virtual void _v58();
    virtual void _v5c(); virtual void _v60(); virtual void _v64(); virtual void _v68();
    virtual cCityState* GetState();                          // 6c
    virtual void _v70(); virtual void _v74(); virtual void _v78(); virtual void _v7c();
    virtual void _v80(); virtual void _v84(); virtual void _v88();
    virtual void SetIsPlayer(bool b);                        // 8c
    uint32_t pad04[(0x34 - 4) / 4];
    cSpatial mOwner;                                         // +34
    uint32_t pad38[(0x120 - 0x38) / 4];
    cSpatial mSpatial;                                       // +120
    uint32_t pad124[(0x2e8 - 0x124) / 4];
    int mField2E8;                                           // +2e8
    int mField2EC;                                           // +2ec
    uint32_t pad2F0[(0x304 - 0x2f0) / 4];
    float mSpiceProduction;                                  // +304

    void SetCityData(cCityData* data);   // 0x00bd81e0
    void SetSize(int size, int b);       // 0x00be73d0
    void SetIncome(int income, float happiness);             // 0x00bd7d10
    int GetMaxSize();                    // 0x00bd8110
    void Layout(const Vector3* pos, float wealth, int turrets, int buildings, bool isPlayer, int a,
                int layout, int b, int c, int d);            // 0x00be8680
    void Initialize(int layout, int a, int b, int c);        // 0x00be7bf0
    void SetUnk(int a);                  // 0x00be32f0
    cBuilding* GetCityHall();            // 0x00bd9b40
    void AddBuilding(cBuilding* b, int a);                   // 0x00be1ef0
    cCityGrid* GetGrid();                // 0x00bd7f40
    void AddOrnament(cOrnament* o);      // 0x00be1e80
    void UpdateBuildings();              // 0x00bdbbb0
    void AddTurret(int slot);            // 0x00be3990
    void SetUnk2(int a);                 // 0x00c01e20
};

class cVehicle {
public:
    virtual int AddRef();                                    // 00
    virtual int Release();                                   // 04
    uint32_t pad04[(0x34 - 4) / 4];
    cSpatial mSpatial;                                       // +34
    uint32_t pad38[(0x5d0 - 0x38) / 4];
    uint32_t mBehavior;                                      // +5d0

    void Init(int locomotion, int purpose, ResourceKey key);  // 0x00ca6630
    void SetVehicleData(cVehicleData* data);                 // 0x00a110b0
    void SetCivData(cCivData* data);                         // 0x00c9eae0
    void SetJustEyeCandy(bool b);                            // 0x00c9ecb0
};

struct cIdHolder { int mID; };
struct cTextHolder { void SetText(const string16& s); };     // 0x00b6f380

struct cCivilization {
    uint32_t pad00[0x3c / 4];
    cTextHolder mName;                   // +3c
    int mField40;                        // +40
    uint32_t pad44[(0x6c - 0x44) / 4];
    uint32_t mModelKeys;                 // +6c
    uint32_t pad70[(0x98 - 0x70) / 4];
    float mWealth;                       // +98

    void Init(int politicalID, bool isPlayer, int colorID, int a);  // 0x00bf8170
    void SetWealth(float w, int a);      // 0x00befd80
    void SetColor(const ResourceKey* key);                   // 0x00bef8f0
    void SetTribeData(void* data);       // 0x00bebdd0
    void AddCity(cCity* city);           // 0x00bf4370
    const sp_vector<cCity*>* GetCities();  // 0x00bef6c0
    void AddVehicle(cVehicle* v);        // 0x00bf5630
    const ResourceKey& GetModelTypeKey(uint32_t id);         // 0x00bf9770
};

struct cGameNounManager {
    cCivilization* GetCivilization(int politicalID);         // 0x00b25f40
    cGameData* CreateNoun(uint32_t classID);                 // 0x00b20c60
};

struct cSpeciesProfile { void GetUiName(string16& name); };  // 0x004da330
struct cTribeInfo { uint32_t pad[4]; int mID; };

struct cPlanet {
    uint32_t pad00[0x13c / 4];
    int mType;                           // +13c
    cTribeInfo* GetTribe();              // 0x00c71e30
    cSpeciesProfile* GetSpecies();       // 0x00c70860
    int GetTechLevel();                  // 0x00c70e00
};

struct cStarManager { int GetPlayerPoliticalID(); };         // 0x00885c90
struct cPlanetModel { Vector3 DirectionToSurfacePosition(const Vector3& dir); };  // 0x00b815a0
struct cLocaleManager { string16 GetText(uint32_t id); };   // 0x005ecf80

class IMessageServer {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14();
    virtual void PostMessage(uint32_t messageID, void* msg, int a, int b);  // 18
};
class IBehaviorManager {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2c();
    virtual void _v30(); virtual void _v34();
    virtual void Register(uint32_t* behavior);               // 38
};

cGameNounManager* NounManager();                             // 0x00b3d300
cStarManager* StarManager();                                 // 0x00b3d2a0
cPlanetModel* PlanetModel();                                 // 0x00b3d350
IMessageServer* MessageServer();                             // 0x0067dcc0
IBehaviorManager* BehaviorManager();                         // 0x00b3d260
int GetPlayerEmpireID();                                     // 0x01021090
cPlanet* GetActivePlanet();                                  // 0x01021260
cLocaleManager* LocaleManager();                             // 0x004010a0
const ResourceKey* GetColorKey(int colorID);                 // 0x00b6f0c0
cCity* CreateCity(const Vector3* pos, const char16* name);   // 0x00bd9d70
void GetCityLimits(int maxSize, int* a, int* b, int* c, int* d, int* e);  // 0x00ff5330
int GetTurretCount(int maxSize);                             // 0x00ff53f0

// ---- behavior message (vtable 0x013eb844, base UI::BehaviorMessage 0x013eb90c) ----------------
class cBehaviorMessage {
public:
    virtual void _v00();
    volatile long mnRefCount;            // +04
    cBehaviorMessage() { _InterlockedExchange(&mnRefCount, 0); }
};
struct cMessageHeader {
    void* mpData0;                       // +08
    uint32_t pad0C;
    void* mpData1;                       // +10
    uint32_t pad14;
    void* mpData2;                       // +18
    uint32_t pad1C[5];
    uint32_t mMessageID;                 // +30
    uint32_t field_34;
    cMessageHeader(uint32_t id) : mMessageID(id) {}
};
class cSimMessage : public cMessageHeader, public cBehaviorMessage {
public:
    void* mpExtra;                       // +38
    uint32_t field_3C;
    cSimMessage() : cMessageHeader(0), mpExtra(0) {}
    virtual void _v00();
};

struct cPlanetSimHost {
    void LoadCivilization(cCivData* civ, cPlanetSimHost* host);
    uint32_t pad[0x504 / 4];
    uint32_t mTribeData;                 // +504
};

void cPlanetSimHost::LoadCivilization(cCivData* civ, cPlanetSimHost* host)
{
    cGameNounManager* nounManager = NounManager();
    int politicalID = civ->GetPoliticalID();
    int playerID = GetPlayerEmpireID();
    if (nounManager == 0)
        return;

    cPlanet* planet = GetActivePlanet();
    cTribeInfo* tribe = planet->GetTribe();
    cCivilization* civilization = nounManager->GetCivilization(politicalID);
    if (civilization == 0) {
        civilization = object_cast<cCivilization>(nounManager->CreateNoun(0x18c816a), 0x901f1362);
        civilization->Init(politicalID, politicalID == playerID, civ->GetColorID(), 0);
        if (tribe)
            civilization->mField40 = tribe->mID;
        string16 name;
        planet->GetSpecies()->GetUiName(name);
        civilization->mName.SetText(name);
        civilization->SetWealth(civ->GetWealth(), 0);
    }
    if (civilization == 0)
        return;

    uint32_t instance = civ->mModelKeys.mpBegin->instanceID;
    if (instance != 0 && instance != 0xffffffff)
        civ->LoadModelKeys(&civilization->mModelKeys);
    else
        civ->DefaultModelKeys(&civilization->mModelKeys);

    int starPlayerID = StarManager()->GetPlayerPoliticalID();
    if (civ->GetPoliticalID() == starPlayerID)
        civilization->SetColor(&kPlayerColorKey);
    else
        civilization->SetColor(GetColorKey(civ->GetColorID()));
    civilization->SetTribeData(&host->mTribeData);
    GetActivePlanet();

    int cityCount = (int)civ->GetCities().size();
    for (int i = 0; i < cityCount; i++) {
        cCityData* data = civ->GetCities()[i];
        const Vector3& pos = data->GetPosition();
        if (pos != kZeroVector) {
            string16 cityName;
            if (data->GetName().empty())
                cityName = LocaleManager()->GetText(0x58f4c251).c_str();
            else
                cityName = data->GetName();

            cCity* city = CreateCity(&pos, cityName.c_str());
            city->mOwner.SetOwner(data->GetBuildingLinks());
            city->mField2E8 = data->mFieldBC;
            city->mField2EC = data->mFieldC0;
            city->SetPoliticalID(politicalID);
            city->SetCityData(data);
            city->mSpiceProduction = data->mSpiceProduction;
            city->SetSize(data->mSize, 0);
            city->SetIncome(data->GetIncome(), data->GetHappiness());
            civilization->AddCity(city);

            if (data->mBuildings.empty()) {
                int a = 0, b = 0, c = 0, d = 0, e = 0;
                int cityMax = city->GetMaxSize();
                int dataMax = data->GetMaxSize();
                data->SetMaxSize(min_ref(cityMax, dataMax));
                GetCityLimits(data->GetMaxSize(), &a, &b, &c, &d, &e);
                int turrets = GetTurretCount(data->GetMaxSize());
                city->Layout(&pos, civilization->mWealth, turrets, d + c + b, politicalID == playerID, e,
                             data->mLayout, 0, 0, 1);
                data->RestoreWalls(city, planet->mType);
            } else {
                city->mSpatial.SetPosition(PlanetModel()->DirectionToSurfacePosition(pos));
                city->mSpatial.SetOrientation(data->GetOrientation());
                city->Initialize(data->mLayout, 0, 0, 1);
                city->GetState()->mbRestored = true;
                city->SetIsPlayer(politicalID == playerID);
                data->RestoreCityWalls(city->GetMaxSize(), planet->mType);
                city->SetUnk(0);
                city->GetCityHall()->SetCity(city);

                for (unsigned int j = 0; j < data->mBuildings.size(); j++) {
                    cBuildingData* bd = &data->mBuildings[j];
                    if (bd->mClassId == 0x18ea1eb) {
                        cBuilding* hall = city->GetCityHall();
                        hall->mSpatial.SetPosition(bd->mPosition);
                        hall->mSpatial.SetOrientation(bd->mOrientation);
                        hall->mSpatial.SetModelKey(civ->GetResourceKey(bd));
                        hall->mCombatant.SetHealthPoints(bd->mHealthPoints);
                        hall->mCombatant.SetDamageState(bd->mDamageState);
                        hall->SetConnected(bd->mConnected);
                        hall->mEffectiveness = bd->mEffectiveness;
                        hall->SetFreezeCount(bd->mFreezeCount);
                    } else {
                        cBuilding* building = (cBuilding*)NounManager()->CreateNoun(bd->mClassId);
                        if (building) {
                            building->SetCity(city);
                            building->mSpatial.SetPosition(bd->mPosition);
                            building->mSpatial.SetOrientation(bd->mOrientation);
                            building->mSpatial.SetModelKey(civ->GetResourceKey(bd));
                            building->mCombatant.SetHealthPoints(bd->mHealthPoints);
                            building->mCombatant.SetDamageState(bd->mDamageState);
                            building->SetConnected(bd->mConnected);
                            building->SetUnk25(bd->mbUnk25);
                            building->mEffectiveness = bd->mEffectiveness;
                            building->SetFreezeCount(bd->mFreezeCount);
                            city->AddBuilding(building, 1);
                            cBuildingNet* net = city->GetGrid()->GetNet(building->mSpatial.GetModelID());
                            if (net)
                                net->AddBuilding(building);
                            if (bd->mDamageState == 2)
                                building->mTimer.Restart();
                        }
                    }
                }

                for (unsigned int j = 0; j < data->mOrnaments.size(); j++) {
                    cOrnamentData* od = &data->mOrnaments[j];
                    cOrnament* ornament = (cOrnament*)NounManager()->CreateNoun(od->mClassId);
                    if (ornament) {
                        ornament->SetModel(0x2ae5ba7, civ->GetPoliticalID(), od->mModelKey.instanceID);
                        ornament->mSpatial.SetPosition(od->mPosition);
                        ornament->mSpatial.SetOrientation(od->mOrientation);
                        city->AddOrnament(ornament);
                    }
                }

                city->UpdateBuildings();
                uint8_t turrets = data->GetTurretLocations();
                for (int t = 0; t < 8; t++) {
                    if (turrets & (1 << t))
                        city->AddTurret(t);
                }
            }

            city->GetState()->SetActive(1);
            city->SetUnk2(0);
            cSimMessage* msg = new ("Simulator", 0, 0, 0, 0) cSimMessage();
            msg->mpData0 = city;
            MessageServer()->PostMessage(0x56e50f1, msg, 0, 0);
        }
    }

    const sp_vector<cVehicleData*>& vehicles = civ->GetVehicles();
    int vehicleCount = (int)vehicles.size();
    for (int i = 0; i < vehicleCount; i++) {
        cVehicleData* vd = vehicles[i];
        Vector3 pos = vd->GetPosition();
        if (pos == kZeroVector) {
            cSimMessage* msg = new ("Simulator", 0, 0, 0, 0) cSimMessage();
            msg->mpData0 = civilization->GetCities()->mpBegin[0];
            msg->mpData1 = vd;
            msg->mpData2 = civ;
            MessageServer()->PostMessage(0x5416d55, msg, 0, 0);
        } else {
            cVehicle* vehicle = object_cast<cVehicle>(nounManager->CreateNoun(0x18c6de8), 0x137e8e0);
            if (vehicle)
                vehicle->AddRef();
            civilization->AddVehicle(vehicle);
            uint32_t modelType = 0xffffffff;
            switch (vd->GetLocomotion()) {
            case 0: modelType = 0xbc1041e6; break;
            case 1: modelType = 0xc15695da; break;
            case 2: modelType = 0x2090a11b; break;
            }
            vehicle->Init(vd->GetLocomotion(), vd->GetPurpose(), civilization->GetModelTypeKey(modelType));
            vehicle->SetVehicleData(vd);
            vehicle->SetCivData(civ);
            vehicle->mSpatial.SetPosition(pos);
            if (planet->GetTechLevel() == 5)
                vehicle->SetJustEyeCandy(true);
            BehaviorManager()->Register(&vehicle->mBehavior);
            vehicle->Release();
        }
    }
}
