// slice s00dca100: SP::VehicleTree::EstablishTradeRouteOrder_Tick (0x00dca100).
// Behavior-tree callback of a trade vehicle (space/civ stage): state 0 drives toward the destination city,
// state 1 waits at the city (timer mem->mTime) and then establishes the route: fires the
// "trade route established" sound/feedback and civ-mode strategy events, or fails with
// "(NN) TR: ..." diagnostics.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"

#define PV(n) virtual void pad##n();

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};
struct Vector4 {
    float x, y, z, w;
};

// Spatial-object interface (vehicle +0x34 / city +0x120).
struct cSpatialObject {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual const Vector3& GetPosition();                          // +0x2c
    PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
    virtual bool IsPlayerControlled();                             // +0x58
    virtual Vector3 GetVelocity();                                 // +0x5c

    bool IsNearGoal();                                             // 0x00c42e20
    bool Fc42210(float f);                                         // 0x00c42210
};

struct cSPTimer {
    void Restart();                                                // 0x00bc3130
    uint64_t GetElapsedTime();                                     // 0x00bc3190
};

struct cCivilization {
    char    pad[0xc4];
    Vector3 mPos;                                                  // +0xc4
};

struct cCity;
struct cCivNoun {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09)
    PV(0a) PV(0b) PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11) PV(12)
    virtual int Vf4c();                                            // +0x4c
    char     pad0[0x104];
    cSPTimer mTimer108;                                            // +0x108
    char     pad10c[0x128 - 0x10c];
    cSPTimer mTimer128;                                            // +0x128
    char     pad12c[0x434 - 0x129];
    uint32_t mState434;                                            // +0x434
    int      mField438;                                            // +0x438
    cCivilization* GetPosHolder();                                 // placeholder
    bool Fbef7e0();                                                // 0x00bef7e0 (mState434 <= 4)
    void Fbf0330(cCity* city);                                     // 0x00bf0330
    void Fbef8c0();                                                // 0x00bef8c0 (mTimer108.Restart)
    Vector3 mPosC4();                                              // placeholder
    float Fbf0640();                                               // 0x00bf0640
    float Fbf06d0();                                               // 0x00bf06d0
    float GetMoney();                                              // 0x00bef6d0
    void  SpendMoney(float amount);                                // 0x00bef710
    void  FcivicRadiusAccum(float f, int n);                       // 0x00befd80
};
struct cCivNounPos {            // the +0xc4 position of a noun
    char    pad[0xc4];
    Vector3 mPos;
};

struct cCity {
    virtual void pad0(); virtual void pad1(); virtual void pad2();
    virtual cCity* Cast(uint32_t typeID);                          // +0x0c
    PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual bool IsDestroyed();                                    // +0x2c
    PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11) PV(12)
    virtual int Vf4c();                                            // +0x4c
    char           pad50[0x120 - 4];
    cSpatialObject mSpatial;                                       // +0x120
    char           pad124[0x590 - 0x124];
    cCivilization* mpCivilization;                                 // +0x590
    char           pad594[0x728 - 0x594];
    cSPTimer       mCommTimer;                                     // +0x728

    bool Fbdb200(int nounID);                                      // 0x00bdb200
    void Fbdb3b0(struct cVehicle* v, int n);                       // 0x00bdb3b0
    void Fbe1820(int nounID);                                      // 0x00be1820
    cCivilization* GetCivilization();                              // 0x00bd9bf0
};

struct cGameData {      // embedded at +0x508 of the vehicle
    PV(00) PV(01) PV(02) PV(03)
    virtual int GetNounID();                                       // +0x10
};

struct CityRef {
    cCity* mpCity;
};

struct cVehicle {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b)
    PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11) PV(12)
    virtual int Vf4c();                                            // +0x4c
    char           pad4[0x30];
    cSpatialObject mLoco;                                          // +0x34
    char           pad38[0x2a4 - 0x38];
    union {
        uint8_t    mPathFlags;                                     // +0x2a4
        uint32_t   mPathFlags32;
    };
    char           pad2a8[0x508 - 0x2a8];
    cGameData      mGameData;                                      // +0x508

    CityRef* Fca71d0();                                            // 0x00ca71d0
    void Fca7250(const char* msg);                                 // 0x00ca7250
    void Fcaa900();                                                // 0x00caa900
    void Fcac000(cCity* city, int a, int b);                       // 0x00cac000
    void Fcacbe0();                                                // 0x00cacbe0
    void Fca80e0(int n);                                           // 0x00ca80e0
};

void __cdecl AttemptRepark(cVehicle* v);                            // 0x00dc9430

// The object returned by cCity::Cast(0x403df5f): a community whose spatial
// interface sits at +0x34 (rather than the cCity +0x120 layout).
struct cCommunitySpatial {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual Vector3* GetPoint(float f, int n);                     // +0x2c
    PV(0c) PV(0d)
    virtual void SetPosition(const Vector3& pos);                  // +0x38
    PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
    virtual bool IsPlayerControlled();                             // +0x58
};

struct cCommunity {
    PV(00) PV(01) PV(02)
    virtual cCommunity* Cast(uint32_t typeID);                     // +0x0c
    PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b)
    PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11) PV(12)
    virtual int Vf4c();                                            // +0x4c
    char pad4[0x30];
    cCommunitySpatial mSpatial;                                    // +0x34
    cCivNoun* GetNoun();                                           // 0x00bfdf80
};

struct cPathArcBuilder {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09)
    PV(0a) PV(0b) PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11)
    virtual void SetCiv(int civ);                                  // +0x48
    char pad4[0x30];
    cCommunitySpatial mSpatial;                                    // +0x34
    void Start(cCivNoun* civ, cCommunity* city, const Vector3* pos, float speed, int flag);  // 0x00cbe640
};

struct cCivNounMgr {
    cCivNoun* Fb25f40(int nounID);                                 // 0x00b25f40
};
struct cGameNounManager {
    cCivNoun* Fb25f40(int nounID);                                 // 0x00b25f40
    cPathArcBuilder* Fbfe7a0();                                    // 0x00bfe7a0
};
struct cRelationshipManager {
    float Fd00d60(cCivilization* civ, cCivNoun* noun, int n);      // 0x00d00d60
    float RecordEvent(int a, int b, int id, float value);          // 0x00d06240
};
struct cScoreTable {
    float Fceee30(cCity* city, cCivNoun* noun);                    // 0x00ceee30
};
struct cStrategy {
    void Fcf9040(cCity* city, uint32_t a, uint32_t b, const Vector3& pos, const Vector4* v, int c, int d);   // 0x00cf9040
};
struct cStarRecord {
    char pad[0x184];
    int  mCommContext;                                             // +0x184
    int  GetCommContext();                                         // 0x00ce6950
    int  GetCommContext(uint32_t id, uint32_t group, int mode);    // 0x00ce6950
};
struct cPlanet {
    char         pad[0x13c];
    cStarRecord* mpStarRecord;                                     // +0x13c
};
struct cCommManager {
    void ShowCommEvent(cCity* a, cCity* b, int ctx, uint32_t id, uint32_t grp, int e);   // 0x00aeb760
    void ShowCommEvent(cCivNoun* noun, int a, int ctx);                                  // 0x00aeb760
};
struct cSomething {
    void Fae37c0(int n, Vector3 pos);                              // 0x00ae37c0
};
struct cAudioSystem {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b)
    PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17)
    virtual void PlaySoundAt(uint32_t id, const Vector3& pos, const Vector3& vel);   // +0x60
};

namespace EA { namespace Random {
class RandomLinearCongruential { public:
    double RandomDoubleUniform();                                  // 0x009360d0
};
}}
extern EA::Random::RandomLinearCongruential sMathRandom;           // 0x01601760
extern cScoreTable g_ScoreTable;                                   // 0x0169c254

extern cGameNounManager*  __cdecl NounManager();                   // 0x00b3d300
extern cRelationshipManager* __cdecl RelationshipManager();        // 0x00b3d2c0
extern cAudioSystem*      __cdecl AudioSystem();                   // 0x00b3d240
extern cCommManager*      __cdecl CommManager();                   // 0x00b3d4a0
extern cStrategy*         __cdecl CivModeStrategy();               // 0x00cf74c0
extern cSomething*        __cdecl Fb26930();                       // 0x00b26930
extern cPlanet*           __cdecl GetActivePlanet();               // 0x01021260
extern void*              __cdecl GetCurrentGameMode();            // 0x00b5b800
extern void __cdecl PlayEffectAt(uint32_t id, Vector3 pos);        // 0x00dc4560
extern bool __cdecl StandardVehicleMoveTick(cVehicle* v);          // 0x00dc95b0

struct TradeMem {
    int     mState;        // 0 heading to city, 1 at city
    float   mTime;
    bool    mFlag8;
    char    pad9[3];
    int     mFieldC;       // selects the mineral / relationship branch at state 1
};

static __forceinline bool Fail(cVehicle* self, const char* msg)
{
    self->Fca7250(msg);
    self->Fcaa900();
    return false;
}

static __forceinline bool AlreadyExists(cVehicle* self, cCity* city, const char* msg)
{
    self->Fca7250(msg);
    self->Fcac000(city, 5, 0);
    return false;
}

namespace SP { namespace VehicleTree {

// @ 0x00dca100
bool EstablishTradeRouteOrder_Tick(cVehicle* self, int, int, int, int, TradeMem* mem, int, float dt)
{
    if (self->mPathFlags & 8)
        return Fail(self, "(31) TR: path failure");
    {
        CityRef* ref = self->Fca71d0();
        cCity* c = ref->mpCity;
        if (c) {
            cCity* city = c->Cast(0xee9b2232);
            int selfCiv;
            if (city && !city->IsDestroyed() && ((selfCiv = self->Vf4c()), selfCiv != city->Vf4c())) {
                if (mem->mState == 0) {
                    if (self->mLoco.IsNearGoal()) {
                        mem->mTime = 0.0f;
                        mem->mState = 1;
                        return true;
                    }
                    if (!mem->mFlag8 && self->mLoco.Fc42210(150.0f)) {
                        mem->mFlag8 = true;
                        city->Fbdb3b0(self, 1);
                    }
                    return StandardVehicleMoveTick(self);
                }
                if (mem->mState != 1) {
                    return Fail(self, "(36) TR: unknown exit");
                }

                bool bSame = city->Vf4c() == self->Vf4c();
                bool bA = city->mSpatial.IsPlayerControlled() && !bSame;
                bool bB = !city->mSpatial.IsPlayerControlled() && !bSame;
                bool bC = false;
                int iState = -1;
                cGameData* gd = &self->mGameData;
                cCivNoun* civNoun = NounManager()->Fb25f40(gd->GetNounID());

                if (0.0f < mem->mTime) {
                    if (bA && civNoun->Fbef7e0()) {
                        iState = civNoun->mState434;
                        if (iState == 1 || iState == 2) {
                            civNoun->mState434 = 0xffffffff;
                            civNoun->mField438 = 0;
                            bC = (iState == 1);
                        }
                    }
                } else {
                    PlayEffectAt(0x6b36f685, self->mLoco.GetPosition());
                    if (city->Fbdb200(gd->GetNounID()) == 1) {
                        return AlreadyExists(self, city, "(34) TR: already exists");
                    }
                    if (bA && !civNoun->Fbef7e0())
                        civNoun->Fbf0330(city);
                }

                mem->mTime = mem->mTime + dt;
                if (((bB || bSame) && mem->mTime > 3.0f) || iState == 1 || iState == 2) {
                    mem->mTime = 0.0f;
                    self->Fca80e0(0x13);
                    civNoun->mTimer128.Restart();
                    if (city->Fbdb200(gd->GetNounID()) == 1) {
                        return AlreadyExists(self, city, "(35) TR: already exists");
                    }
                    cSpatialObject* loco = &self->mLoco;
                    if (loco->IsPlayerControlled())
                        Fb26930()->Fae37c0(2, city->mSpatial.GetPosition());

                    cCivNoun* civNoun2 = NounManager()->Fb25f40(gd->GetNounID());
                    RelationshipManager()->Fd00d60(city->GetCivilization(), civNoun2, 1);
                    float score = g_ScoreTable.Fceee30(city, civNoun2);

                    if ((bA && bC) || (bB && (double)score > sMathRandom.RandomDoubleUniform()) || bSame) {
                        PlayEffectAt(0xd5475761, loco->GetPosition());
                        city->Fbe1820(gd->GetNounID());
                        AudioSystem()->PlaySoundAt(0x4288913, loco->GetPosition(), loco->GetVelocity());
                        self->Fcac000(city, 5, 0);
                        if (!bSame) {
                            if (loco->IsPlayerControlled()) {
                                cCivilization* civ = city->GetCivilization();
                                Vector4 v;
                                v.x = civ->mPos.x; v.y = civ->mPos.y; v.z = civ->mPos.z; v.w = 1.0f;
                                CivModeStrategy()->Fcf9040(city, 0xb327dc63, 0xaa9a8ed7, loco->GetPosition(), &v, 0, 0);
                                CommManager()->ShowCommEvent(city, city, GetActivePlanet()->mpStarRecord->GetCommContext(),
                                                             0xdbf385bf, 0x9cecad2c, 0);
                                return true;
                            }
                            if (city->mSpatial.IsPlayerControlled()) {
                                cCivNounPos* n = (cCivNounPos*)NounManager()->Fb25f40(gd->GetNounID());
                                Vector4 v;
                                v.x = n->mPos.x; v.y = n->mPos.y; v.z = n->mPos.z; v.w = 1.0f;
                                CivModeStrategy()->Fcf9040(city, 0xe1f6430a, 0xaa9a8ed7, loco->GetPosition(), &v, 0, 0);
                            }
                        }
                        return true;
                    }

                    PlayEffectAt(0x5bc0bd48, loco->GetPosition());
                    if (loco->IsPlayerControlled()) {
                        cSPTimer* timer = &city->mCommTimer;
                        uint64_t elapsed = timer->GetElapsedTime();
                        if (elapsed > 40000) {
                            cCivilization* civ = city->GetCivilization();
                            Vector4 v;
                            v.x = civ->mPos.x; v.y = civ->mPos.y; v.z = civ->mPos.z; v.w = 1.0f;
                            CivModeStrategy()->Fcf9040(city, 0x8b24acc6, 0xaa9a8ed7, loco->GetPosition(), &v, 0, 0);
                            CommManager()->ShowCommEvent(city, city, GetActivePlanet()->mpStarRecord->GetCommContext(),
                                                         0xdbf385bf, 0x26546f31, 0);
                            timer->Restart();
                        }
                    }
                    self->Fcaa900();
                    if (bA)
                        civNoun->Fbef8c0();
                    return true;
                }
                return true;

            }
        }
    }
    return Fail(self, "(32) TR: bad city");
}

// @ 0x00dca7b0
bool OfferToBuyCityOrder_Tick(cVehicle* self, int, int, int, int, TradeMem* mem, int, float)
{
    bool bGameMode = (GetCurrentGameMode() == (void*)0x1654c04);

    if (self->mPathFlags & 8)
        return Fail(self, "(36) BC: path failure");

    cGameData* gd = &self->mGameData;
    cCivNoun* civNoun = NounManager()->Fb25f40(gd->GetNounID());
    (void)gd->GetNounID();

    CityRef* ref = self->Fca71d0();
    cCity* city = ref->mpCity;
    if (city) {
        cCommunity* comm = (cCommunity*)city->Cast(0x403df5f);
        if (comm) {
            int selfVf4c = self->Vf4c();
            if (comm->Vf4c() != selfVf4c && comm->Vf4c() != -1) {
                (void)comm->mSpatial.IsPlayerControlled();
                if (bGameMode)
                    (void)self->mLoco.IsPlayerControlled();

                switch (mem->mState) {
                case 0:
                    if (self->mLoco.IsNearGoal()) {
                        mem->mTime = 0.0f;
                        mem->mState = 1;
                        return true;
                    }
                    if (!StandardVehicleMoveTick(self))
                        return Fail(self, "(37) BC: move failure");
                    return true;

                case 1:
                    if (mem->mFieldC == 0) {
                        float cost = civNoun->Fbf0640();
                        if (cost > civNoun->GetMoney())
                            return Fail(self, "(39a) BC: not enough money");
                        comm->GetNoun()->FcivicRadiusAccum(cost, 0);
                        civNoun->SpendMoney(cost);

                        cStarRecord* star = GetActivePlanet()->mpStarRecord;
                        int ctx = star->GetCommContext(0xdbf385bf, 0x4ce5b975, 0);
                        CommManager()->ShowCommEvent(comm->GetNoun(), 0, ctx);

                        cPathArcBuilder* builder = NounManager()->Fbfe7a0();
                        builder->SetCiv(civNoun->Vf4c());
                        builder->mSpatial.SetPosition(self->mLoco.GetPosition());
                        Vector3* p = comm->mSpatial.GetPoint(20.0f, 1);
                        builder->Start(civNoun, comm, p, 20.0f, 1);
                        return Fail(self, "(40a) BC: normal completion");
                    } else {
                        float cost = civNoun->Fbf06d0();
                        if (cost > civNoun->GetMoney())
                            return Fail(self, "(39b) BC: not enough money");
                        civNoun->SpendMoney(cost);
                        (void)RelationshipManager()->RecordEvent(comm->Vf4c(), civNoun->Vf4c(), 0x526e4fb, 1.0f);

                        cPathArcBuilder* builder = NounManager()->Fbfe7a0();
                        builder->SetCiv(civNoun->Vf4c());
                        builder->mSpatial.SetPosition(self->mLoco.GetPosition());
                        Vector3* p = comm->mSpatial.GetPoint(20.0f, 1);
                        builder->Start(civNoun, comm, p, 20.0f, 1);
                        return Fail(self, "(40b) BC: normal completion");
                    }

                default:
                    return Fail(self, "(41) BC: unknown exit");
                }
            }
        }
    }
    return Fail(self, "(38) BC: bad mineral");
}

// @ 0x00dcaad0
bool MoveToPointOrder_Tick(cVehicle* self)
{
    if (self->mPathFlags32 & 2)
        AttemptRepark(self);
    else if (self->mPathFlags32 & 4)
        self->Fcacbe0();

    if (self->mLoco.IsNearGoal()) {
        self->Fca7250("(43) MTP: normal completion");
        self->Fcaa900();
        return false;
    }
    return true;
}

}}
