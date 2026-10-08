// Slice s00dcd720: SP::VehicleTree::ConvertCityOrder_Tick (0x00dcdac0).
// Behavior-tree tick of a culture vehicle converting a city: validate the order, then choose what the vehicle
// should attack next (a nearby unit of the city, a group member of the tribe, or the cultural target itself).
//   bool Tick(cVehicle* self, int, int, int, int, State* st)
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
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
    bool FUN_00c42210(float f);                                    // 0x00c42210
    PV(17) PV(18) PV(19) PV(1a) PV(1b) PV(1c) PV(1d) PV(1e) PV(1f)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(2a) PV(2b) PV(2c) PV(2d)
    virtual void* IsType(uint32_t typeID);                         // +0xb8
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

struct cEmpire {
    int FUN_00bf0d10(cEntity* e);                                  // 0x00bf0d10
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

struct VehicleList { cVehicle** mpBegin; cVehicle** mpEnd; };
struct cNounManager {
    cEmpire* GetEmpire(uint32_t politicalID);                      // 0x00b25f40
    VehicleList* GetVehicles();                                    // 0x00ae73b0
};
cNounManager* __cdecl NounManager();                               // 0x00b3d300

struct cVehicleBase {
    virtual void AddRef();
    virtual void Release();                                        // +0x04
    PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d) PV(0e) PV(0f)
    PV(10) PV(11) PV(12)
    virtual uint32_t GetPoliticalID();                             // +0x4c
    uint32_t dpad04[(0x34 - 4) / 4];
    cSpatialObject mLoco;                                          // +0x34
    uint32_t pad38[(0x508 - 0x38) / 4];
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
};
cEntity* __cdecl FUN_00dc4ca0(cSpatialObject* target);             // 0x00dc4ca0
bool __cdecl IsValidFireTarget(cGameData* mine, cGameData* theirs);   // 0x00dc4e20 (anonymous namespace)
cGameData* __cdecl FUN_00dc69a0(cVehicle* v, Civilization* civ, int a, int b, int c);   // 0x00dc69a0

struct State {
    uint32_t mPoliticalID;
    OrderRef mOrder;                                               // +4
};

namespace SP { namespace VehicleTree {

// @ 0x00dcdac0
bool ConvertCityOrder_Tick(cVehicle* self, int, int, int, int, State* st)
{
    if (st->mOrder.mpObject->IsDone()) {
        self->FUN_00caa900();
        return false;
    }
    Info* info = self->FUN_00ca71d0();
    if (info->mKind == 3) {
        if (info->mpObject) {
            cCulturalTarget* tgt = (cCulturalTarget*)info->mpObject->Cast(0x3d5c477);
            if (tgt && !tgt->IsDestroyed()) {
                cCity* city = tgt->FUN_00bd84e0();
                if (city && !city->IsDestroyed()) {
                    if (city->GetCivilization()->GetPoliticalID() != st->mPoliticalID) {
                        self->FUN_00ca7250("(6.5) Convert city order complete");
                        self->FUN_00caa900();
                        return false;
                    }
                    int cntA = 0;
                    int cntB = 0;
                    VehicleList* list = NounManager()->GetVehicles();
                    int n = (int)(list->mpEnd - list->mpBegin);
                    for (int i = 0; i < n; ++i) {
                        cVehicle* v = list->mpBegin[i];
                        if (v != self) {
                            uint32_t mine = self->GetPoliticalID();
                            if (v->GetPoliticalID() == mine && v->mState == 1) {
                                Info* vi = v->FUN_00ca71d0();
                                if (vi->mKind == 3) {
                                    cCulturalTarget* vt = FUN_00bd8420(vi);
                                    if (vt && vt->FUN_00bd84e0() == city) {
                                        if (v->GetTarget() == &vt->mSpatial)
                                            ++cntA;
                                        if (FUN_00dc4ca0(v->GetTarget()) == 0)
                                            ++cntB;
                                    }
                                }
                            }
                        }
                    }
                    if (cntB > 0) {
                        cEntity* e = FUN_00dc4ca0(self->GetTarget());
                        if (e && e->mf290 <= 1 && !e->FUN_00bfc600())
                            return true;
                    }
                    if (cntA < 1 && city->FUN_00bd7e20())
                        goto phase2;

                    {
                        cBuilding* best = 0;
                        float bestDist = 3.402823466e+38F;
                        BuildingVector found;
                        city->FUN_00be5700(&found);
                        cBuilding** it = found.mpBegin;
                        cBuilding** end = found.mpEnd;
                        for (; it != end; ++it) {
                            cBuilding* o = *it;
                            if (IsValidFireTarget(self, o) && !o->FUN_00bd3550(self)) {
                                VehicleList* list2 = NounManager()->GetVehicles();
                                int n2 = (int)(list2->mpEnd - list2->mpBegin);
                                for (int j = 0; j < n2; ++j) {
                                    cVehicle* v = list2->mpBegin[j];
                                    uint32_t mine = self->GetPoliticalID();
                                    if (v->GetPoliticalID() == mine && v->mState == 1) {
                                        Info* vi = v->FUN_00ca71d0();
                                        if (vi->mKind == 3) {
                                            cCulturalTarget* vt = FUN_00bd8420(vi);
                                            if (vt && vt->FUN_00bd84e0() == city) {
                                                cSpatialObject* os = o->GetSpatial();
                                                const Vector3& vp = v->mLoco.GetPosition();
                                                const Vector3& op = os->GetPosition();
                                                float d = (op - vp).Length();
                                                if (d < o->GetRange() + 10.0f) {
                                                    cSpatialObject* os2 = o->GetSpatial();
                                                    const Vector3& mp = self->mLoco.GetPosition();
                                                    const Vector3& op2 = os2->GetPosition();
                                                    float d2 = (op2 - mp).Length();
                                                    if (d2 < bestDist) {
                                                        best = o;
                                                        bestDist = d2;
                                                    }
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        if (best) {
                            self->FUN_00dc4d00(best->GetSpatial());
                            self->SetAttackTarget(best);
                            return true;
                        }
                        if (self->FUN_00c9f3d0() == city) {
                            cGameData* g = FUN_00dc69a0(self, city->GetCivilization(), 1, 1, 1);
                            if (g) {
                                int cnt = 0;
                                bool ok = true;
                                if (self->mLoco.Vf58()) {
                                    VehicleList* list3 = NounManager()->GetVehicles();
                                    int n3 = (int)(list3->mpEnd - list3->mpBegin);
                                    for (int k = 0; k < n3; ++k) {
                                        cVehicle* v = list3->mpBegin[k];
                                        if (v != self) {
                                            uint32_t mine = self->GetPoliticalID();
                                            if (v->GetPoliticalID() == mine && v->mState == 1) {
                                                int kind = v->FUN_00ca71d0()->mKind;
                                                if (kind == 1 || kind == 3) {
                                                    cSpatialObject* gs = g->GetSpatial();
                                                    if (v->GetTarget() == gs)
                                                        ++cnt;
                                                }
                                            }
                                        }
                                    }
                                    if (cnt >= 2)
                                        ok = false;
                                }
                                if (ok) {
                                    self->FUN_00dc4d00(g->GetSpatial());
                                    self->SetAttackTarget(g);
                                    return true;
                                }
                            }
                        }
                    }
                phase2:
                    if (self->FUN_00c9f3d0() == city && !city->FUN_00bd7e20()) {
                        EntityVector* members = city->GetMembers();
                        for (unsigned i = 0; i < (unsigned)(members->mpEnd - members->mpBegin); ++i) {
                            cEntity* m = members->mpBegin[i];
                            if (IsValidFireTarget(self, m) && !m->FUN_00bd3280(self) && m->GetTypeID() == 0x1a56aba
                                && ((m->mf298 - m->mf29c) > 0 || m->mf290 > 0)) {
                                if (NounManager()->GetEmpire(self->GetPoliticalID())->FUN_00bf0d10(m) == 0) {
                                    self->FUN_00dc4d00(m->GetSpatial());
                                    self->SetAttackTarget(m);
                                    return true;
                                }
                            }
                        }
                    }
                    cSpatialObject* ts = self->GetTarget();
                    cEntity* te = ts ? (cEntity*)ts->IsType(0x1a55e4d) : 0;
                    if (!te || te->mf290 > 1 || te->FUN_00bfc600()) {
                        if (self->mLoco.FUN_00c42210(90.0f) && tgt->mf1d8 == 2 && tgt->mf1dc != self->GetOwnerID()) {
                            cCulturalTarget* nt = city->FUN_00bd8d70(self);
                            if (!nt) {
                                self->FUN_00ca7250("(7) No culture target when rescanning");
                                self->FUN_00caa900();
                                return false;
                            }
                            self->FUN_00c9fa30(nt);
                            cCulturalConvertCityOrder* ord = FUN_00dc4c80(FUN_00c9efc0()->GetGroupOrder(self->FUN_00ca71d0()));
                            if (ord && !ord->IsDone()) {
                                st->mPoliticalID = nt->mGameData.GetOwnerID();
                                st->mOrder.mpObject->FUN_00dc8c50(self);
                                ord->FUN_00dc8c00(self);
                                ord->FUN_00dcc350(self);
                                st->mOrder = ord;
                                self->FUN_00dc4d00(&nt->mSpatial);
                                self->SetAttackTarget(&nt->mGameData);
                                return true;
                            }
                        }
                        self->FUN_00dc4d00(&tgt->mSpatial);
                        self->SetAttackTarget(&tgt->mGameData);
                    }
                    return true;
                }
                self->FUN_00ca7250("(8) bad city");
            }
        }
        self->FUN_00ca7250("(9) bad culture target");
    }
    self->FUN_00ca7250("(10) orders mismatch");
    self->FUN_00caa900();
    return false;
}

}}
