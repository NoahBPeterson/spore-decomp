// flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
// gold7 batch, worker 5 / slice s00dcd720: three companions of the committed
// SP::VehicleTree::ConvertCityOrder_Tick (0x00dcdac0).
//
//   0x00dcd720  SP::FindNearestReachableCommodity(cVehicle* self, bool weighted)
//                 two-pass scan of the game-data vector for the nearest vehicle on the same
//                 continent; the first pass also requires the political id to match (or be -1).
//                 When `weighted`, the distance is divided by (phaseRatio^2 * 4 + 1) and, for a
//                 known political id whose empire exists, multiplied by 4 (and 2 more when the
//                 empire's +0x8a byte is clear).
//   0x00dcd930  SP::VehicleTree::ConvertCityOrder_Activate(self, ..., State* st)
//                 validate the current cultural target / city, then (re)issue the culture-convert
//                 group order and record it in the state.
//   0x00dce330  FUN_00dce330(cVehicle* self)
//                 once near the goal either nudge toward the nearest reachable commodity or fire
//                 at a random community member; otherwise attempt a repark.
//
// Type model shared with the committed ConvertCityOrder_Tick source in s00dcd720.cpp.
#include "types.h"

extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)

#define PV(n) virtual void pad##n();

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    Vector3 operator-(const Vector3& v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
    float Length() const { return (float)sqrt(x * x + y * y + z * z); }
};

// Spatial object interface (embedded in vehicles at +0x34, in cultural targets at +0x100).
struct cSpatialObject {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual const Vector3& GetPosition();                          // +0x2c
    PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
    virtual bool Vf58();                                           // +0x58
    PV(17) PV(18) PV(19) PV(1a) PV(1b) PV(1c) PV(1d) PV(1e) PV(1f)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(2a) PV(2b) PV(2c) PV(2d)
    virtual void* IsType(uint32_t typeID);                         // +0xb8
    PV(2f) PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39)
    virtual void FlyToPoint(const Vector3& p, float a, float b);   // +0xe8
    bool FUN_00c42210(float f);                                    // 0x00c42210
    bool IsNearGoal();                                             // 0x00c42e20
};
// The political/game-data base shared by vehicles (+0x508), units (+0x120), buildings (+0x588) and
// cultural targets (+0x38).
struct cGameData {
    PV(00) PV(01)
    virtual cSpatialObject* GetSpatial();                          // +0x08
    PV(03)
    virtual uint32_t GetOwnerID();                                 // +0x10
    PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11) PV(12) PV(13)
    virtual void SetAttackTarget(cGameData* target);               // +0x50
    float GetRange();                                              // 0x00bfc400
    bool FUN_00bfc600();                                           // 0x00bfc600
};

// Unit-like object (tribe member / result of casting a target): game data base at +0x120.
struct cEntityBase {
    virtual void AddRef();
    PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07)
    virtual uint32_t GetTypeID();                                  // +0x20
    uint32_t dpad04[(0x120 - 4) / 4];
};
struct cEntity : cEntityBase, cGameData {
    uint32_t pad124[(0x290 - 0x120 - sizeof(cGameData)) / 4];
    int mf290;                                                     // +0x290
    uint32_t pad294;
    int mf298;                                                     // +0x298
    int mf29c;                                                     // +0x29c
    bool FUN_00bd3280(void* vehicle);                              // 0x00bd3280
};

// Building-like object with game data at +0x588 (elements of the city's list).
struct cBuildingBase {
    virtual void AddRef();
    uint32_t dpad04[(0x588 - 4) / 4];
};
struct cBuilding : cBuildingBase, cGameData {
    bool FUN_00bd3550(void* vehicle);                              // 0x00bd3550
};

struct cCulturalConvertCityOrder {
    virtual void AddRef();
    virtual void Release();                                        // +0x04
    PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual bool IsDone();                                         // +0x2c
    void FUN_00dc8c50(void* vehicle);                              // 0x00dc8c50
    void FUN_00dc8c00(void* vehicle);                              // 0x00dc8c00
    void FUN_00dcc350(void* vehicle);                              // 0x00dcc350
};
struct OrderRef {                                                  // EA::AutoRefCount<cCulturalConvertCityOrder>
    cCulturalConvertCityOrder* mpObject;
    OrderRef& operator=(cCulturalConvertCityOrder* p);             // 0x00b5f950
};

struct cGameDataObj {
    PV(00) PV(01) PV(02)
    virtual void* Cast(uint32_t typeID);                           // +0x0c
};

struct cCity;
struct cVehicle;
struct BuildingVector;
struct EntityVector;
struct cCulturalTargetBase {
    virtual void AddRef();
    virtual void Release();                                        // +0x04
    PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual bool IsDestroyed();                                    // +0x2c
    uint32_t dpad04[(0x38 - 4) / 4];
};
struct cCulturalTarget : cCulturalTargetBase {
    cGameData mGameData;                                           // +0x38
    uint32_t pad3c[(0x100 - 0x38 - sizeof(cGameData)) / 4];
    cSpatialObject mSpatial;                                       // +0x100
    uint32_t pad104[(0x1d8 - 0x100 - sizeof(cSpatialObject)) / 4];
    int mf1d8;                                                     // +0x1d8
    uint32_t mf1dc;                                                // +0x1dc

    cCity* FUN_00bd84e0();                                         // 0x00bd84e0 (the target's city)
    cCulturalTarget* FUN_00bd8d70(cVehicle* v);                    // 0x00bd8d70
};
cCulturalTarget* __cdecl FUN_00bd8420(void* info);                 // 0x00bd8420

struct Civilization {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d) PV(0e) PV(0f)
    PV(10) PV(11) PV(12)
    virtual uint32_t GetPoliticalID();                             // +0x4c
};

struct cCity {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual bool IsDestroyed();                                    // +0x2c
    Civilization* GetCivilization();                               // 0x00bd9bf0
    bool FUN_00bd7e20();                                           // 0x00bd7e20
    EntityVector* GetMembers();                                    // 0x00c8e810 (cTribe)
    void FUN_00be5700(BuildingVector* out);                        // 0x00be5700
    cCulturalTarget* FUN_00bd8d70(cVehicle* v);                    // 0x00bd8d70
};

struct EntityVector { cEntity** mpBegin; cEntity** mpEnd; };
struct BuildingVector {                                            // fixed eastl::vector<AutoRefCount<cBuilding>>
    cBuilding** mpBegin;
    cBuilding** mpEnd;
    cBuilding** mpCapacity;
    uint32_t mAllocPad;
    cBuilding** mpFixedBuffer;                                     // +0x10
    uint32_t mCookie;
    cBuilding* mBuffer[32];
    BuildingVector()
    {
        mpBegin = mBuffer;
        mpEnd = mBuffer;
        mpCapacity = mBuffer + 32;
        mpFixedBuffer = mBuffer;
    }
    ~BuildingVector();                                             // 0x008e2b20
};

struct cVehicleVector;

struct cEmpire {
    int FUN_00bf0d10(cEntity* e);                                  // 0x00bf0d10
    cVehicleVector* FUN_00bef6c0();                                // 0x00bef6c0
    uint32_t pad04[(0x8a - 4) / 4];
    uint8_t mFlag8a;                                               // +0x8a
};

struct Info {                                                      // FUN_00ca71d0 result
    cGameDataObj* mpObject;
    uint32_t dpad04[3];
    int mKind;                                                     // +0x10
};

struct cVehicleTicker {
    void* GetGroupOrder(Info* info);                               // 0x00dcd430
};
cVehicleTicker* __cdecl FUN_00c9efc0();                            // 0x00c9efc0 (ticker singleton)
cCulturalConvertCityOrder* __cdecl FUN_00dc4c80(void* groupOrder); // 0x00dc4c80 (interface_cast)

// The game-data vector returned by cGameNounManager::GetGameDataVector: begin/end at +4/+8.
struct cGameDataVector {
    uint32_t mPad0;
    cVehicle** mpBegin;                                            // +0x04
    cVehicle** mpEnd;                                              // +0x08
};
struct cGameNounManager {
    cGameDataVector* GetGameDataVector(void* a, void* b, void* c, void* d, void* e);   // 0x00b21340
};
struct cNounManager {
    cEmpire* GetEmpire(uint32_t politicalID);                      // 0x00b25f40
    cGameDataVector* GetGameDataVector(void* a, void* b, void* c, void* d, void* e);   // 0x00b21340
};
cNounManager* __cdecl NounManager();                               // 0x00b3d300

struct cPlanetModel {
    int GetContinent(const Vector3& pos);                          // 0x00b88590
    float DistanceBetweenPoints(const Vector3& a, const Vector3& b);   // 0x00b81470
};
cPlanetModel* __cdecl PlanetModel();                               // 0x00b3d350

struct cVehicleBase {
    virtual void AddRef();
    virtual void Release();                                        // +0x04
    PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual bool IsDestroyed();                                    // +0x2c
    PV(0c) PV(0d) PV(0e) PV(0f)
    PV(10) PV(11) PV(12)
    virtual uint32_t GetPoliticalID();                             // +0x4c
    uint32_t dpad04[(0x34 - 4) / 4];
    cSpatialObject mLoco;                                          // +0x34
    uint32_t pad38[(0x2a4 - 0x38) / 4];
    uint32_t mFlags2a4;                                            // +0x2a4
    uint32_t pad2a8[(0x508 - 0x2a8) / 4];
};
struct cVehicle : cVehicleBase, cGameData {                        // game data base at +0x508
    uint32_t pad50c[(0xb20 - 0x508 - sizeof(cGameData)) / 4];
    int mState;                                                    // +0xb20

    void FUN_00caa900();                                           // 0x00caa900 (finish the order)
    void FUN_00ca7250(const char* msg);                            // 0x00ca7250 (log)
    Info* FUN_00ca71d0();                                          // 0x00ca71d0
    cSpatialObject* GetTarget();                                   // 0x00c9fee0
    cCity* FUN_00c9f3d0();                                         // 0x00c9f3d0
    void FUN_00dc4d00(cSpatialObject* s);                          // 0x00dc4d00
    void FUN_00c9fa30(cCulturalTarget* t);                         // 0x00c9fa30
    float GetPhaseRatio();                                         // 0x00bfdea0 (cCommunity phase ratio)
    bool FUN_00ca8340(cVehicle* v);                                // 0x00ca8340
    void FUN_00cacbe0();                                           // 0x00cacbe0
    void FUN_00c9fb40(Vector3 p, float a, float b);                // 0x00c9fb40
};
cEntity* __cdecl FUN_00dc4ca0(cSpatialObject* target);             // 0x00dc4ca0
bool __cdecl IsValidFireTarget(cGameData* mine, cGameData* theirs);   // 0x00dc4e20 (anonymous namespace)
cGameData* __cdecl FUN_00dc69a0(cVehicle* v, Civilization* civ, int a, int b, int c);   // 0x00dc69a0

// 0x00dcd930 helpers.
void  FUN_00dcc610(cVehicle* v);                                   // 0x00dcc610
void  AttemptRepark(cVehicle* v);                                  // 0x00dc9430
void  FUN_00dc5050(cVehicle* a, cVehicle* b);                      // 0x00dc5050
struct cVehicleVector { cVehicle** mpBegin; cVehicle** mpEnd; };
float __cdecl RandomDoubleUniform();                               // 0x009360d0 (cRandomGlobal::RandomDouble)
uint32_t __cdecl RandomUint32Uniform(uint32_t n);                  // 0x00a68fb0
struct cRandomGlobal {
    float RandomDouble();                                          // 0x009360d0
    uint32_t RandomUint32Uniform(uint32_t n);                      // 0x00a68fb0
};
#define Random() ((cRandomGlobal*)0x01601760)

struct State {
    uint32_t mPoliticalID;
    OrderRef mOrder;                                               // +4
};

namespace SP { namespace VehicleTree {

// @ 0x00dcd720
cVehicle* FindNearestReachableCommodity(cVehicle* self, bool weighted)
{
    if (self == 0)
        return 0;

    const Vector3& selfPos = self->mLoco.GetPosition();

    cGameDataVector* vec = NounManager()->GetGameDataVector(
        (void*)0x00cd7d10, (void*)0x00d3d420, (void*)0x00ae5ea0, (void*)0x00b1e500, (void*)0x0403df5c);
    cVehicle*** pp = &vec->mpBegin;

    uint32_t myID = self->GetPoliticalID();
    cEmpire* empire = NounManager()->GetEmpire(myID);
    if (empire == 0 || *pp == pp[1])
        return 0;

    float bestDist = 3.402823466e+38F;
    cPlanetModel* planet = PlanetModel();
    if (planet == 0)
        return 0;

    int myCont = planet->GetContinent(selfPos);
    uint32_t ownerID = self->GetPoliticalID();
    int candID = -1;
    int n = (int)(pp[1] - *pp);

    cVehicle* best = 0;
    int pass = 0;
    do {
        if (n != 0) {
            for (int i = 0; i < n; ++i) {
                cVehicle* v = (*pp)[i];
                Vector3 vp = v->mLoco.GetPosition();
                if (planet->GetContinent(vp) == myCont) {
                    if (pass != 0
                        || ((candID = (int)v->GetPoliticalID()) == -1)
                        || candID == (int)ownerID) {
                        float d = planet->DistanceBetweenPoints(vp, selfPos);
                        if (weighted) {
                            float ratio = v->GetPhaseRatio();
                            d = d / (ratio * ratio * 4.0f + 1.0f);
                            if (candID != -1) {
                                cEmpire* e = NounManager()->GetEmpire(candID);
                                if (e != 0) {
                                    d = d * 4.0f;
                                    if (e->mFlag8a == 0)
                                        d = d * 2.0f;
                                }
                            }
                        }
                        if (d < bestDist) {
                            best = v;
                            bestDist = d;
                        }
                    }
                }
            }
            if (best != 0)
                return best;
        }
        ++pass;
        if (pass >= 2)
            return best;
    } while (true);
}

// @ 0x00dcd930
bool ConvertCityOrder_Activate(cVehicle* self, int, int, int, int, State* st)
{
    if (st != 0)
        st->mOrder.mpObject = 0;

    Info* info = self->FUN_00ca71d0();
    if (info->mKind != 3)
        goto done;

    {
        cCulturalTarget* other = info->mpObject
            ? (cCulturalTarget*)info->mpObject->Cast(0xee9b2232) : 0;
        cCulturalTarget* ct = 0;
        if (info->mpObject)
            ct = (cCulturalTarget*)info->mpObject->Cast(0x3d5c477);

        bool bOtherAlive = false;
        if (other != 0) {
            bOtherAlive = true;
            if (other->IsDestroyed())
                bOtherAlive = false;
        }

        if (bOtherAlive) {
            ct = other->FUN_00bd8d70(self);
            if (ct == 0) {
                self->FUN_00ca7250("(4) No culture target");
                self->FUN_00caa900();
                return false;
            }
            self->FUN_00c9fa30(ct);
        } else if (ct == 0 || ct->IsDestroyed()) {
            self->FUN_00ca7250("(6) Invalid city or culture target");
            self->FUN_00caa900();
            return false;
        }

        uint32_t ctID = ct->mf1dc;
        uint32_t ownerID = self->GetOwnerID();
        if (ctID != (uint32_t)-1 && ctID != ownerID) {
            self->FUN_00ca7250("(5) Culture target same political ID");
            self->FUN_00caa900();
            return false;
        }

        void* groupOrder = FUN_00c9efc0()->GetGroupOrder(info);
        if (groupOrder != 0) {
            cCulturalConvertCityOrder* ord =
                (cCulturalConvertCityOrder*)((cGameDataObj*)groupOrder)->Cast(0x3df2cb9);
            if (ord != 0 && !ord->IsDone()) {
                st->mPoliticalID = ct->mGameData.GetOwnerID();
                ord->FUN_00dc8c00(self);
                ord->FUN_00dcc350(self);
                st->mOrder = ord;
                self->FUN_00dc4d00(&ct->mSpatial);
                self->SetAttackTarget(&ct->mGameData);
            }
        }
    }

done:
    FUN_00dcc610(self);
    return true;
}

}}  // namespace SP::VehicleTree

// @ 0x00dce330
bool FUN_00dce330(cVehicle* self)
{
    if (self->mLoco.IsNearGoal()) {
        uint32_t id = self->GetPoliticalID();
        cEmpire* empire = NounManager()->GetEmpire(id);
        if (empire == 0)
            return true;

        cVehicleVector* vec = empire->FUN_00bef6c0();
        if ((uint32_t)(vec->mpEnd - vec->mpBegin) > 1 || Random()->RandomDouble() < 0.5f) {
            cVehicle* pick = vec->mpBegin[Random()->RandomUint32Uniform((uint32_t)(vec->mpEnd - vec->mpBegin))];
            if ((cVehicle*)self->FUN_00c9f3d0() != pick && self->FUN_00ca8340(pick) && !pick->IsDestroyed()) {
                FUN_00dc5050(self, pick);
                return true;
            }
            return true;
        }

        {
            cVehicle* v = SP::VehicleTree::FindNearestReachableCommodity(self, true);
            if (v == 0)
                return true;
            Vector3 vp = v->mLoco.GetPosition();
            self->FUN_00c9fb40(vp, 12.0f, 48.0f);
            self->mLoco.FlyToPoint(vp, 12.0f, 24.0f);
            return true;
        }
    }

    if (self->mFlags2a4 & 2) {
        AttemptRepark(self);
        return true;
    }
    if (self->mFlags2a4 & 4)
        self->FUN_00cacbe0();
    return true;
}
