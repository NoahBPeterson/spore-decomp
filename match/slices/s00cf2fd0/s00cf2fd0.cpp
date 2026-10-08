// Slice s00cf2fd0 - SP::cCityInputStrategy::HandleMenuItem (0x00cf31f0, 2556 bytes): handles a pie-menu
// item id in civ-stage city mode. Returns true after HideUTFMenu(1).
//   0x321..0x32f   : construct a building/unit slot (id-0x321 split into quotient/remainder by 5)
//   0x38b          : end object placement of the selected hall's owner
//   0x37e95b9..bd  : send the selected vehicles (purpose 0/1/2) at the cursor's targets
//   0x37eaf27/29/2a/2b : city-hall menu actions (finish placement / launch editor / spend money)
//   0x39a6152      : turret-style purchase (spend money)
//   0x46ee610, 0x51b4174 : show a comm event for the active planet
//   0x51b40a4      : gather vehicles around the selected object and send them
// Flags /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc), as the neighbouring cCityInputStrategy slices.
#include "types.h"

struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {}
};

// ---- virtual-call helpers (vtable slot by byte offset, thiscall) -------------------------------
template <class R> static inline R VC0(void* o, int off)
{ return ((R(__thiscall*)(void*))(*(void***)o)[off / 4])(o); }
template <class R, class A> static inline R VC1(void* o, int off, A a)
{ return ((R(__thiscall*)(void*, A))(*(void***)o)[off / 4])(o, a); }
template <class R, class A, class B> static inline R VC2(void* o, int off, A a, B b)
{ return ((R(__thiscall*)(void*, A, B))(*(void***)o)[off / 4])(o, a, b); }

#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define P1 virtual void CAT(pad_, __COUNTER__)();
#define P2 P1 P1
#define P4 P2 P2
#define P8 P4 P4
#define P16 P8 P8
#define P32 P16 P16

struct ResourceKey { uint32_t a, b, c; };
struct Vehicle;
struct Civ;

struct Obj {                       // cast-capable game object; Cast() is vtable slot 3
    virtual void s0(); virtual void s1(); virtual void s2();
    virtual void* Cast(uint32_t id);
    P32 P8 P2                      // slots 4..45
    virtual Vehicle* GetVehicle(uint32_t id);   // +0xb8
};

struct Civilization {
    char pad[0x98];
    float mMoney;                                    // +0x98
    ResourceKey* GetModelTypeKey(int x);             // 0x00bf9770 (this+0x6c, jmp 0x00bf9700)
    void SpendMoney(float amount);                   // 0x00bef710 (ret 4)
    void Func_BEFD80(float amount, bool b);          // 0x00befd80 (ret 8)
    void Func_BF03E0(void* pObj, float f);           // 0x00bf03e0 (ret 8)
};

struct PosIface {                                    // spatial interface: GetPosition() at +0x2c
    P8 P2 P1
    virtual const Vec3* GetPosition();
};
struct City {
    virtual void v0();
    char pad[0x120 - 4];
    PosIface mOwned;                                 // +0x120 (interface)
    Civilization* GetCivilization();                 // 0x00bd9bf0 (mov eax,[ecx+0x590])
    void Func_BDDDA0(int quot, int rem, ResourceKey key, int flag);   // 0x00bddda0 (ret 0x18)
    void Func_BE1820(int a);                         // 0x00be1820 (ret 4)
    void Func_BE33E0(void* pSelected);               // 0x00be33e0 (ret 4)
    bool Func_BD7FC0(int empireID);                  // 0x00bd7fc0 (ret 4)
    float Func_BE9250(int empireID);                 // 0x00be9250 (ret 4), float in st0
};
City* __cdecl EndObjectPlacement(void* pOwner);      // 0x00ac86d0

struct Vehicle {                   // SP::cVehicle (fields used here)
    char pad[0xb20];
    int  mState;                   // +0xb20
    bool Func_C9FE40(void* o);                    // 0x00c9fe40 (ret 4)
    void Func_CAC000(void* o, int a, int b);      // 0x00cac000 (ret 0xc)
    bool Func_CA8340(void* x);                    // 0x00ca8340 (ret 4)
};
struct TerrainSphere {
    void Func_C77BF0(uint32_t id);  // 0x00c77bf0 (ret 4)
};
struct PlayerCiv;
struct NounMgr {
    TerrainSphere* GetCurrentTerrainSphere();  // 0x00f67d90
    int GetPlayerEmpireOrMinus1();             // 0x00b1f9d0
    Civilization* GetPlayerCivilization();     // 0x00b25fb0
};
struct CivModeStrategy {
    float Func_CF7A50();                       // 0x00cf7a50
};
struct CommManager {
    void ShowCommEvent(void* a, void* b, void* c, uint32_t d, uint32_t e, int f);   // 0x00aeb760 (ret 0x18)
};
struct StarRef {
    void* GetCommContext();                    // 0x00ce6950 (mov eax,[ecx+0x184])
};
struct Planet {
    char pad[0x13c];
    StarRef* mpStar;                           // +0x13c
    StarRef* GetStar() { return mpStar; }
};
struct SpatialIface34 {                              // interface at sel+0x34
    P8 P2 P1                                         // slots 0..10
    virtual const Vec3* GetPosition();               // +0x2c
    P16 P8 P2                                        // slots 12..37
    virtual void* Func98();                          // +0x98
};
struct CostIface120 {                                // interface at sel+0x120
    P8 P2 P1
    virtual void Func2C(int v);                      // +0x2c
};
struct Sel {                                         // object behind this+0x10c / this+0x110 (cSpatialGameData)
    P8 P4                                            // slots 0..11
    virtual Obj* GetOwner();                         // +0x30
    P8 P2                                            // slots 13..22
    virtual float GetCostA();                        // +0x5c
    virtual float GetCostB();                        // +0x60
    P8                                               // slots 25..32
    virtual City* GetPlaced();                       // +0x84
    char pad04[0x34 - 4];
    SpatialIface34 mIface34;                         // +0x34
    char pad38[0x120 - 0x38];
    CostIface120 mIface120;                          // +0x120
    void* Func_BCD630();                             // 0x00bcd630
};
struct Obj118 {                                // object behind this+0x118
    char pad[0x588];
    CostIface120 mIface588;
    City* Func_BCE5C0();                       // 0x00bce5c0 (mov eax,[ecx+0x688])
    float Func_BD0110();                       // 0x00bd0110 (float in st0)
};
struct Cursor {                                      // terrain cursor
    P16 P8
    virtual void GetObjects(struct ObjVec* pOut, uint32_t type);   // +0x60
};

NounMgr*       __cdecl NounManager();             // 0x00b3d300
CivModeStrategy* __cdecl GetCivModeStrategy();    // 0x00cf74c0
CommManager*   __cdecl GetCommManager();          // 0x00b3d4a0
Planet*        __cdecl GetActivePlanet();         // 0x01021260
uint32_t       __cdecl GetRecorderState();        // 0x00435e90
void           __cdecl KillSetiEffects(uint32_t hash, uint32_t state);   // 0x00435ed0
Cursor*        __cdecl GetGameTerrainCursor();    // 0x00b30d70
void*          __cdecl InterfaceCastBuilding(void* p);   // 0x00cf1090
struct Item34 { int Func_8E7F80(); };                  // 0x008e7f80 (mov eax,[ecx+0x34])
Item34*        __cdecl Func_AE6740(void* p);      // 0x00ae6740
int            __cdecl Func_C9E6D0(int a, int b); // 0x00c9e6d0
Vehicle*       __cdecl CastVehicle(void** it);    // 0x00bd8440
void           __cdecl HideUTFMenu(int flag);     // 0x00b7c810

struct Zero16 { int a, b, c, d; };
void __cdecl EditorLaunch(uint32_t id, void* pObj, uint32_t key, void* pSel, Zero16 z, int flag);   // 0x005a94d0

struct ObjVec {                    // eastl::vector<AutoRefCount<cSpatialObject>, sp_vector_allocator>
    Obj** mpBegin; Obj** mpEnd; Obj** mpCap;
    int mAllocFields[2];           // allocator state, not initialised by the inlined constructor
    ObjVec() : mpBegin(0), mpEnd(0), mpCap(0) {}
    void Destroy();                // 0x00ad92d0 (out-of-line ~vector)
};

struct VRef {                      // EA::AutoRefCount<cVehicle>
    Vehicle* p;
    VRef(Vehicle* v);              // 0x00572660
    ~VRef() { if (p) VC0<void>(p, 4); }
};
struct VehVec {                    // eastl::vector<AutoRefCount<cVehicle>, sp_vector_allocator>
    Vehicle** mpBegin; Vehicle** mpEnd; Vehicle** mpCap;
    void erase(Vehicle** first, Vehicle** last);          // 0x00e25bd0 (ret 8)
    bool empty() const { return mpBegin == mpEnd; }
    void push_back(VRef* v);                              // 0x00e1c7f0 (ret 4)
};

struct CityInputStrategy {
    char   pad[0xe8];
    VehVec mSelected;                                     // +0xe8
    char   pade[0x10c - 0xf4];
    Sel*   mp10c;                                         // +0x10c
    Sel*   mp110;                                         // +0x110
    char   pad114[0x118 - 0x114];
    Obj118* mp118;                                        // +0x118
    Sel*   mp11c;                                         // +0x11c
    void Func_CF30B0(void* target, Vec3 pos, int flag);   // 0x00cf30b0 (ret 0x14)
    bool HandleMenuItem(int id);
};

// @ 0x00cf31f0
bool CityInputStrategy::HandleMenuItem(int id)
{
    if (id >= 0x321 && id <= 0x32f) {
        int quot = (id - 0x321) / 5;
        int rem = (id - 0x321) % 5;
        Obj* hall = mp110->GetOwner();
        City* city = hall ? (City*)hall->Cast(0xee9b2232) : 0;
        Civilization* civ = city->GetCivilization();
        ResourceKey* key = civ->GetModelTypeKey(Func_C9E6D0(quot, rem));
        city->Func_BDDDA0(quot, rem, *key, 0);
    }

    switch (id) {
    case 0x38b:
        if (mp10c)
            EndObjectPlacement(mp10c->GetOwner())->Func_BE1820(0);
        break;

    case 0x37e95b9: {
        ObjVec objects;
        GetGameTerrainCursor()->GetObjects(&objects, 0x137e8e0);
        if (objects.mpBegin != objects.mpEnd && mp10c
            && InterfaceCastBuilding(mp10c)) {
            Item34* pX = Func_AE6740(mp10c);
            if (pX && pX->Func_8E7F80() != 2) {
                Obj** it = objects.mpBegin;
                Obj** itEnd = objects.mpEnd;
                for (; it != itEnd; ++it) {
                    Vehicle* veh = CastVehicle((void**)it);
                    if (veh && veh->mState == 0 && veh->Func_CA8340(mp10c->GetPlaced())) {
                        VRef r(veh);
                        mSelected.push_back(&r);
                    }
                }
                if (mSelected.mpBegin != mSelected.mpEnd) {
                    Func_CF30B0(mp10c->GetPlaced(), *mp10c->GetPlaced()->mOwned.GetPosition(), 2);
                    NounManager()->GetCurrentTerrainSphere()->Func_C77BF0(0x52da1f6);
                    KillSetiEffects(0x940e34ee, 0x37fd5b2);
                }
            }
        }
        objects.Destroy();
        break;
    }

    case 0x37e95bb:
        if (mp10c->GetPlaced()->Func_BD7FC0(NounManager()->GetPlayerEmpireOrMinus1())) {
            NounManager()->GetPlayerCivilization()->Func_BF03E0(
                mp10c->GetPlaced(),
                mp10c->GetPlaced()->Func_BE9250(NounManager()->GetPlayerEmpireOrMinus1()));
            NounManager()->GetCurrentTerrainSphere()->Func_C77BF0(0x52da1f7);
        }
        break;

    case 0x37e95ba: {
        ObjVec objects;
        GetGameTerrainCursor()->GetObjects(&objects, 0x137e8e0);
        if (objects.mpBegin != objects.mpEnd && mp10c) {
            mSelected.erase(mSelected.mpBegin, mSelected.mpEnd);
            Obj** it = objects.mpBegin;
            Obj** itEnd = objects.mpEnd;
            for (; it != itEnd; ++it) {
                Vehicle* veh = CastVehicle((void**)it);
                if (veh->mState == 1 && veh->Func_CA8340(mp10c->GetPlaced())) {
                    VRef r(veh);
                    mSelected.push_back(&r);
                }
            }
            if (!mSelected.empty()) {
                Func_CF30B0(mp10c->GetPlaced(), *mp10c->GetPlaced()->mOwned.GetPosition(), 3);
                KillSetiEffects(0x9ab713eb, 0x37fd5b2);
            }
        }
        objects.Destroy();
        break;
    }

    case 0x37e95bc: {
        ObjVec objects;
        GetGameTerrainCursor()->GetObjects(&objects, 0x137e8e0);
        if (objects.mpBegin != objects.mpEnd && mp10c) {
            mSelected.erase(mSelected.mpBegin, mSelected.mpEnd);
            Obj** it = objects.mpBegin;
            Obj** itEnd = objects.mpEnd;
            for (; it != itEnd; ++it) {
                Vehicle* veh = CastVehicle((void**)it);
                if (veh->mState == 2 && veh->Func_CA8340(mp10c->GetPlaced())) {
                    VRef r(veh);
                    mSelected.push_back(&r);
                }
            }
            if (!mSelected.empty()) {
                Func_CF30B0(mp10c->GetPlaced(), *mp10c->GetPlaced()->mOwned.GetPosition(), 9);
                NounManager()->GetCurrentTerrainSphere()->Func_C77BF0(0x52da1f4);
                KillSetiEffects(0xca345816, 0x37fd5b2);
            }
        }
        objects.Destroy();
        break;
    }

    case 0x37e95bd: {
        ObjVec objects;
        GetGameTerrainCursor()->GetObjects(&objects, 0x137e8e0);
        if (objects.mpBegin != objects.mpEnd && mp10c) {
            Obj** it = objects.mpBegin;
            Obj** itEnd = objects.mpEnd;
            for (; it != itEnd; ++it) {
                Vehicle* veh = CastVehicle((void**)it);
                if (veh->mState == 2 && veh->Func_CA8340(mp10c->GetPlaced()))
                    veh->Func_CAC000(mp10c->GetPlaced(), 5, 1);
            }
        }
        objects.Destroy();
        break;
    }

    case 0x37eaf27: {
        Obj* hall = VC0<Obj*>(mp10c, 0x30);
        City* city = hall ? (City*)hall->Cast(0xee9b2232) : 0;
        Sel* sel = mp10c;
        city->GetCivilization()->Func_BEFD80(GetCivModeStrategy()->Func_CF7A50() * sel->GetCostA(), false);
        Obj* hall2 = VC0<Obj*>(mp10c, 0x30);
        City* city2 = hall2 ? (City*)hall2->Cast(0xee9b2232) : 0;
        city2->Func_BE33E0(mp10c);
        mp10c = 0;
        break;
    }

    case 0x37eaf2b:
        EndObjectPlacement(mp10c->GetOwner())->Func_BE33E0(mp10c);
        mp10c = 0;
        break;

    case 0x37eaf2a: {
        City* city = EndObjectPlacement(mp10c->GetOwner());
        Civilization* civ = city->GetCivilization();
        float cost = mp10c->GetCostB();
        if (civ->mMoney >= cost) {
            Sel* sel = mp10c;
            sel->mIface120.Func2C(0);
            civ->SpendMoney(cost);
        } else {
            KillSetiEffects(0x594303b7, GetRecorderState());
        }
        break;
    }

    case 0x37eaf29: {
        Sel* sel = mp10c;
        Zero16 z = { 0, 0, 0, 0 };
        EditorLaunch(0xd817cd63, sel->mIface34.Func98(), 0x2def34f, sel, z, 0);
        break;
    }

    case 0x39a6152:
        if (mp118) {
            Civilization* civ = mp118->Func_BCE5C0()->GetCivilization();
            if (civ) {
                float cost = mp118->Func_BD0110();
                if (civ->mMoney >= cost) {
                    mp118->mIface588.Func2C(0);
                    civ->SpendMoney(cost);
                }
            }
        }
        break;

    case 0x51b4174: {
        CommManager* pComm = GetCommManager();
        Planet* pPlanet = GetActivePlanet();
        pComm->ShowCommEvent(mp10c->Func_BCD630(), mp10c->GetPlaced(),
                             pPlanet->GetStar()->GetCommContext(), 0xdbf385bf, 0xee4f8f7f, 0);
        break;
    }

    case 0x51b40a4: {
        ObjVec objects;
        GetGameTerrainCursor()->GetObjects(&objects, 0x137e8e0);
        if (objects.mpBegin != objects.mpEnd && mp11c) {
            mSelected.erase(mSelected.mpBegin, mSelected.mpEnd);
            Obj** it = objects.mpBegin;
            Obj** itEnd = objects.mpEnd;
            for (; it != itEnd; ++it) {
                Obj* p = *it;
                Vehicle* veh = p ? p->GetVehicle(0x137e8e0) : 0;
                if (veh->mState == 2 && veh->Func_C9FE40(mp11c)) {
                    VRef r(veh);
                    mSelected.push_back(&r);
                }
            }
            if (!mSelected.empty()) {
                Func_CF30B0(mp11c, *mp11c->mIface34.GetPosition(), 0xb);
                KillSetiEffects(0xd15f2608, 0x37fd5b2);
            }
        }
        objects.Destroy();
        break;
    }

    case 0x46ee610: {
        CommManager* pComm = GetCommManager();
        Planet* pPlanet = GetActivePlanet();
        pComm->ShowCommEvent(mp10c->Func_BCD630(), mp10c->GetPlaced(),
                             pPlanet->GetStar()->GetCommContext(), 0xdbf385bf, 0x942bfb93, 0);
        break;
    }
    }

    HideUTFMenu(1);
    return true;
}
