// Slice s0102cd90: SP::TryPurchaseOffer (0x0102d1b0, 1569 bytes, cdecl).
//
// The player buys a system ("trade capture") from another empire for `price`. The offer is
// graded against the tuning deltas (good / bad / very bad), which picks a comm-screen text key and
// records a relationship event. A good or ok offer captures the system: the system's trade routes
// are removed, its planets get activated, the comm screen gets a "surrender" string, the player
// pays and a UI message is posted. A very bad offer only shows the text and the trade-route progress.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-.
#include "types.h"
#include <intrin.h>

typedef unsigned int uint;

struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct Quat {
    float x, y, z, w;
    Quat() {}
    Quat(const Quat& o) : x(o.x), y(o.y), z(o.z), w(o.w) {}
};
struct Obj;
struct PtrVec { Obj** b; Obj** e; Obj** c; };

struct Tuning {
    int m_102fa30(int type);          // GetTradeCaptureOfferPrice
    int m_102ffc0();                  // GetTradeCaptureGoodOfferDelta
    int m_102ff40();                  // GetTradeCaptureBadOfferDelta
    int m_102ff80();                  // GetTradeCaptureVeryBadOfferDelta
    float m_1030600();                // GetTradeCaptureRemainingBuildingRatio
    float m_10305b0();                // GetTradeCaptureRemainingCityRatio
    float m_1030560();                // GetTradeCaptureRemainingPlanetRatio
    int m_1030930(int type, Obj* empire);  // GetPeaceOfferPrice
    int m_1030aa0(Obj* empire);        // GetPeaceGoodOfferDelta
    int m_10309c0(Obj* empire);        // GetPeaceBadOfferDelta
    int m_1030a30(Obj* empire);        // GetPeaceVeryBadOfferDelta
};

struct TradeMgr {
    void m_10383a0(Obj* sys);                         // RemoveAllTradeRoutesFromSystem
    int m_1037e40(int sysId, int empId);              // GetPlayerProgressOnTradeRoute
};

struct StarMgr {
    Obj* m_ba9370(int id);                            // cStarManager::GetEmpireByID
    TradeMgr* m_ba6490();                             // trade route manager
    void m_bb59b0(Obj* p, Obj** outPlanet);           // GetOrActivatePlanet
    Obj* m_ba6dc0(Obj* planet);                       // banner / planet lookup
};

struct Obj {
    int m_bba990();
    Obj* m_bbaa60(int i);
    int m_b8dab0();
    int m_c70c00();                   // planet: sim active?
    void m_c71e70();                  // cPlanet::PlanetSimActivate
    int m_c70e00();
    Obj* m_c8b770();                  // cStar::GetSolarSystem
    Obj* m_a1ad60();                  // GetPlayerInventory
    Obj* m_bfc5f0();                  // GetPlayerTribe
    void m_fe5430(int a, int b);
    void m_c31a00(int amount);
    void m_ae9140(int id);
    void m_aea230(void* strVec);
    void m_aeb720(int arg, int empId, int category, int text, int a, int b);
    void m_ae09b0(int id, void* data, int z);
    int m_ce6950();
    float m_d06240(int a, int b, int key, float f);   // cRelationshipManager::RecordEvent
    void m_676e90(uint id, int x);    // Achievements::Controller::AutoTest
    int  m_d01e30(Obj* empire, Obj* player);           // cRelationshipManager::EndAlliance
    float m_d00a10(int empireId, int playerId, int zero);  // cRelationshipManager::ClampRelationship
    void m_d06920(Obj* empire, Obj* player);           // cRelationshipManager::StartAlliance
    void m_d05830(int empireId, int playerId);
    void m_d038e0(Obj* empire, Obj* player);           // cRelationshipManager::StartPeace
    void m_aea210();                                   // cCommManager::CloseCommEvent
    Obj* m_b8de30();                                   // cBioElemSort::SortBanners
    Obj* m_b1fdb0();                                   // cGameNounManager::GetAvatar
    int  m_c30c80();
    void m_60d860(uint id, int v);                     // cPollinator::UpdateProperty
    void m_c5b370(Obj* target);                        // cPlanetMission::SetTarget
    void m_c47180(int param);
    int  m_c5b530();                                   // cSPRaidEvent::GenerateBomberCount
    void m_c5b390(int n);
    void m_c485b0();                                   // cSPMission::Accept
    void m_c322f0(int v);
    char m_1075500();
    void m_1075ef0();
    Vec3* m_4df400();
};

struct PlayerObj {
    uint32_t pad_000[0x84 / 4];
    int      empire_id;                                // +0x84
};

struct TerrainPlayer {
    uint32_t pad_000[0x10fc / 4];
    uint32_t t10fc, t1100, t1104, t1108, t110c;        // +0x10fc
    int  m_c76800(Obj* empire);                        // cPlayer::GetPeacePriceForPlayer
    void m_c7bc20(int empireId, int flag);             // cPlayer::SetWarFlag20
};

struct NounMgr {
    TerrainPlayer* m_f67d90();                         // cTerrainEditor::GetCurrentTerrainSphere
};

struct U32Vec {
    uint32_t* b; uint32_t* e; uint32_t* c;
    void push_back(uint32_t v);
    void m_4558a0(uint32_t* pos, const uint32_t* val); // eastl slow path (0x004558a0)
};

struct SpaceGame {
    uint32_t pad_000[6];
    Obj*     trading;                                  // +0x18
};

// Object built by cSPUISpaceTrading::Shutdown (0x9c bytes, cEditorLaunchData-like).
struct LaunchData {
    void*    vptr;                                     // +0x00
    uint32_t pad_004[2];
    uint32_t f00c;                                     // +0x0c
    uint32_t f010, f014, f018;                         // +0x10
    uint32_t pad_01c[2];
    uint32_t f024, f028, f02c, f030;                   // +0x24
    unsigned char f034, f035, f036, f037, f038, f039;  // +0x34
    unsigned char pad_03a[2];
    unsigned char f03c, f03d;                          // +0x3c
    unsigned char pad_03e[2];
    void*    str_b;                                    // +0x40
    void*    str_e;                                    // +0x44
    uint32_t str_c;                                    // +0x48
    unsigned char pad_04c[0x64 - 0x4c];
    unsigned char f064;                                // +0x64
    unsigned char pad_065[0x6d - 0x65];
    unsigned char f06d;                                // +0x6d
    unsigned char pad_06e[2];
    U32Vec   vec;                                      // +0x70
    unsigned char pad_07c[0x90 - 0x7c];
    uint32_t f090;                                     // +0x90
    Obj*     p094;                                     // +0x94
    void m_5a9080();                                   // cEditorLaunchData::cEditorLaunchData
};

struct MissionMgr {
    Obj* m_fec590(uint id, int param, Obj* empire, int zero);  // CreateMissionFromID
    char m_fee590(Obj* planet, int* out);                      // IsPlanetARaidTarget
};

struct RelTuning {
    float m_1040820(float rel);
};

struct RandomGlobal {
    double RandomDouble();
};

struct Planet { uint pad[79]; Obj* emp; };           // +0x13c
inline uint& nounField(Obj* n, int off) { return *(uint*)((char*)n + off); }

struct EvtData {
    char pad[0x1c];
    float f1c;
    float f20;
    EvtData(const Vec3* p, const Quat* q);   // 0x00ad79d0
    ~EvtData();                              // 0x00ad7ad0 cActionTarget::~cActionTarget
};

struct Z3 { int a, b, c, d; Z3() : a(0), b(0), c(0) {} };

Planet* GetActivePlanet();                 // 0x01021260
uint GetPlayerEmpireID();                  // 0x01021090
Obj* GetPlayerEmpire();                    // 0x01021300
int GetUniverseContext();                  // 0x01021080
Obj* Fn_01021230();
StarMgr* StarManager();                    // 0x00b3d2a0
Obj* RelationshipManager();                // 0x00b3d2c0
Obj* SpaceGameGet();                       // 0x01002bd0
Obj* GetUFOSimulator();                    // 0x00ffbe50
Obj* MessageServer();                      // 0x0067dcc0
Tuning* Fn_0102f810();                     // SP::GetSpaceEconomyTuning
Obj* Fn_00b3d4a0();                        // CommManager
Obj* Fn_00b3d4d0();                        // GetTriggerMgr
Obj* Fn_00675250();                        // Achievements::Controller::Get
void Fn_01044640();
void Fn_00c705c0(Obj* p, int v);
void Fn_00c8ce40(Obj* sort, float r3, int one1, float r2, int one2, float r1, int zero);
void Fn_00e39ab0(int key, Obj* emp, Z3* d, Z3* c, int v, int zero, Z3* b, Z3* a);
void* __cdecl operator_new6(uint, const char*, int, int, const char*, int);   // 0x00f473a0
void  __cdecl operator_delete__(void*);                                        // 0x00f47380
void  __cdecl StrCopy(void* dst, const void* src, uint n);                     // 0x011e0744 (memcpy)

// --- helpers for the diplomacy / attack-request slice ---
NounMgr*      NounManager();                   // 0x00b3d300
extern uint32_t g_15da7c4, g_15da7c8, g_15da7cc, g_15da7d0;   // 0x015da7c4
MissionMgr*   GetMissionManager();             // 0x00feb9f0
RelTuning*    Fn_010407c0();                   // 0x010407c0 GetSpaceRelationshipTuning
Obj*          Fn_0067cb30();                   // 0x0067cb30 manager getter
Obj*          Fn_00c30c80(Obj* o);             // 0x00c30c80
char          IsWorldLayoutFlagSet(int flag);  // 0x00685520
Obj*          Fn_00401090();                   // 0x00401090
Obj*          Fn_004df400();                   // 0x004df400 (returns a vec3-ish blob)
Obj*          Fn_00b3d320(Obj* o);             // 0x00b3d320
void          Fn_00b1dee0(Obj* o);             // 0x00b1dee0
void          Fn_00e5c780(void* self, int* key, void* out);  // 0x00e5c780 rbtree find
extern int    g_targetPlanetIndex;             // 0x015b751c
extern Obj**  g_attackRequestPlanets;          // 0x016decac (vector begin)
extern Obj**  g_attackRequestPlanetsEnd;       // 0x016decb0 (vector end)
inline RandomGlobal* randomGlobal() { return (RandomGlobal*)0x01601760; }

template <class R> inline R vc0(void* o, int off) {
    typedef R(__thiscall * F)(void*);
    return ((F)(*(void***)o)[off / 4])(o);
}
template <class R, class A, class B, class C> inline R vc3(void* o, int off, A a, B b, C c) {
    typedef R(__thiscall * F)(void*, A, B, C);
    return ((F)(*(void***)o)[off / 4])(o, a, b, c);
}
template <class R, class A, class B, class C, class D> inline R vc4(void* o, int off, A a, B b, C c, D d) {
    typedef R(__thiscall * F)(void*, A, B, C, D);
    return ((F)(*(void***)o)[off / 4])(o, a, b, c, d);
}
template <class R, class A> inline R vc1(void* o, int off, A a) {
    typedef R(__thiscall * F)(void*, A);
    return ((F)(*(void***)o)[off / 4])(o, a);
}

// eastl::vector<char> holding a string literal (+ NUL), posted to the comm screen.
struct StrVec {
    char* b; char* e; char* c;
};
static __forceinline void PostCommString(const char* s, uint n) {
    StrVec v;
    v.b = 0; v.e = 0; v.c = 0;
    char* p = (char*)operator_new6(n + 1, "Simulator", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    v.c = p + n + 1;
    v.b = p;
    StrCopy(p, s, n);
    v.e = p + n;
    *v.e = 0;
    Fn_00b3d4a0()->m_aea230(&v);
    if ((v.c - v.b) > 1 && v.b) operator_delete__(v.b);
}

// UI message (vtable 0x013eb844, base 0x013eb90c). Destruct releases flagged slot pointers.
extern void* vtbl_UIMessageBase[];   // 0x013eb90c
extern void* vtbl_UIMessage[];       // 0x013eb844
struct IRel { virtual void v0(); virtual void Release(); };
struct UIMessage {
    void** vptr; volatile long rc; int d0; uint pad[11]; uint id; uint pad34; uint flags;
    UIMessage(uint id_, int data) {
        id = id_;
        vptr = vtbl_UIMessageBase;
        _InterlockedExchange(&rc, 0);
        vptr = vtbl_UIMessage;
        flags = 0;
        d0 = data;
    }
    ~UIMessage() {
        vptr = vtbl_UIMessage;
        uint bit = 1;
        for (int i = 0; i < 32; i++) {
            if ((flags & bit) && ((IRel**)((char*)this + 8))[i * 2]) ((IRel**)((char*)this + 8))[i * 2]->Release();
            bit = _rotl(bit, 1);
        }
    }
};
struct MsgServer {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void Post(unsigned type, UIMessage* m, int flag);   // +0x14
};

// @ 0x0102d1b0
void TryPurchaseOffer(int arg, Obj* sort, int price) {
    int basePrice = sort->m_bba990();
    uint key = 0x92a95b57;
    bool exact = false;
    if (price == Fn_0102f810()->m_102fa30(4)) {
        key = 0x57c98667;
        exact = true;
    }
    int delta = price - basePrice;
    bool capture = true;
    if (delta > Fn_0102f810()->m_102ffc0()) {
        RelationshipManager()->m_d06240(arg, GetPlayerEmpireID(), 0x55901b3, 1.0f);
        key = 0xe8a568ec;
    } else if (delta > Fn_0102f810()->m_102ff40()) {
        key = 0x57c98667;
    } else if (!exact) {
        if (delta > Fn_0102f810()->m_102ff80()) {
            key = 0x81034ee0;
        } else {
            RelationshipManager()->m_d06240(arg, GetPlayerEmpireID(), 0x5590199, 1.0f);
            key = 0x92a95b57;
        }
        capture = false;
        StarManager()->m_ba6490()->m_1037e40(nounField(sort, 0x70), arg);
    }
    if (capture) {
        Obj* emp = StarManager()->m_ba9370(arg);
        Z3 a, b, c, d;
        Fn_00e39ab0(0xfdd30461, emp, &d, &c, (int)nounField(sort, 0x70), 0, &b, &a);
        Fn_00c8ce40(sort, Fn_0102f810()->m_1030560(), 1, Fn_0102f810()->m_10305b0(), 1,
                    Fn_0102f810()->m_1030600(), 0);
        StarManager()->m_ba6490()->m_10383a0(sort);
        int count = *(unsigned char*)((char*)sort + 0xac);
        for (int i = 0; i < count; i++) {
            Obj* p = sort->m_bbaa60(i);
            if (p->m_b8dab0() == 5) {
                Obj* planet;
                StarManager()->m_bb59b0(p, &planet);
                if (!planet->m_c70c00()) planet->m_c71e70();
                Fn_00c705c0(p, 0x7fffffff);
            }
        }
        Fn_00b3d4a0()->m_ae9140((int)nounField(sort, 0x70));
        int ctx = GetUniverseContext();
        switch (ctx) {
        case 0:
            Fn_01044640();
            vc3<void>(MessageServer(), 0x14, 0x678a3ef, 0, 0);
            PostCommString("SPG_SystemSurrender_Diplomatic_Planet", 0x25);
            break;
        case 1: {
            Obj* sys = Fn_01021230()->m_c8b770();
            PtrVec* list = (PtrVec*)((char*)sys + 0x10);
            Obj* best = 0;
            Obj* inv = GetUFOSimulator()->m_a1ad60();
            Vec3* pp = vc0<Vec3*>((char*)inv + 0x34, 0x2c);
            Vec3 P = *pp;
            int n = list->e - list->b;
            for (int i = 0; i < n; i++) {
                Obj* it = list->b[i];
                if (it->m_c70e00() == 5) {
                    Vec3* q = vc0<Vec3*>(list->b[i], 0x2c);
                    float dx = P.x - q->x, dy = P.y - q->y, dz = P.z - q->z;
                    if (dx * dx + dz * dz + dy * dy < 3.40282346e+38f) best = list->b[i];
                }
            }
            if (best) {
                Vec3* q = vc0<Vec3*>(best, 0x2c);
                Vec3 pos = *q;
                Quat* o = vc0<Quat*>(best, 0x30);
                Quat Q = *o;
                EvtData ev(&pos, &Q);
                ev.f20 = vc0<float>(best, 0x70);
                ev.f1c = vc0<float>(best, 0x74);
                Fn_00b3d4d0()->m_ae09b0(0x5f848353, &ev, 0);
                PostCommString("SPG_SystemSurrender_Diplomatic_Solar", 0x24);
            }
            break;
        }
        }
        Fn_00675250()->m_676e90(0xd3f14a26, 1);
        SpaceGameGet()->m_bfc5f0()->m_fe5430(0x1a, 1);
        GetPlayerEmpire()->m_c31a00(-price);
        UIMessage m(0xf46092d2, (int)nounField(sort, 0x70));
        ((MsgServer*)MessageServer())->Post(0xf46092d2, &m, 0);
    }
    Planet* pl = GetActivePlanet();
    Fn_00b3d4a0()->m_aeb720(arg, pl->emp->m_ce6950(), (int)0xc8fbf7d7, (int)key, 0, 0);
}

// @ 0x0102cd90
void TryBreakAlliance(int empireId) {
    Obj* empire = StarManager()->m_ba9370(empireId);
    Obj* player = GetPlayerEmpire();
    RelationshipManager()->m_d01e30(empire, player);
    int pid = ((PlayerObj*)player)->empire_id;
    RelationshipManager()->m_d06240(empireId, pid, 0x526e521, 1.0f);
    vc4<void>(MessageServer(), 0x18, 0x43f2585, 0, 0, 0);
    Planet* pl = GetActivePlanet();
    Obj* emp = pl->emp;
    Fn_00b3d4a0()->m_aeb720(empireId, emp->m_ce6950(), (int)0xc8fbf7d7,
                            (int)0x20534e67, 0, 0);
}

// @ 0x0102ce30
void TryCreateAlliance(int empireId) {
    Obj* empire = StarManager()->m_ba9370(empireId);
    SpaceGameGet();
    Obj* player = GetPlayerEmpire();
    float rel = RelationshipManager()->m_d00a10(empireId, ((PlayerObj*)player)->empire_id, 0);
    float threshold = Fn_010407c0()->m_1040820(rel);
    double r = randomGlobal()->RandomDouble();
    uint key;
    Planet* pl;
    if (threshold < (float)r) {
        key = 0xb1519e40;
        pl = GetActivePlanet();
    } else {
        RelationshipManager()->m_d06920(empire, player);
        int v = empire->m_c30c80() + 0x504;
        uint id = 0x5ba499af;
        Fn_0067cb30()->m_60d860(id, v);
        key = 0x12510968;
        pl = GetActivePlanet();
    }
    Fn_00b3d4a0()->m_aeb720(empireId, pl->emp->m_ce6950(), (int)0xc8fbf7d7,
                            (int)key, 0, 0);
}

// @ 0x0102cf10
void TryPeaceOffer(int empireId, int price) {
    Obj* empire = StarManager()->m_ba9370(empireId);
    int basePrice = NounManager()->m_f67d90()->m_c76800(empire);
    int commKey = 0x1273c3f6;
    uint eventKey = 0x5661a77;
    bool good = (price == Fn_0102f810()->m_1030930(4, empire));
    if (good)
        commKey = 0x6c5f070e;
    int delta = price - basePrice;
    if (delta > Fn_0102f810()->m_1030aa0(empire)) {
        commKey = 0x38c512e1;
        good = true;
    } else if (delta > Fn_0102f810()->m_10309c0(empire)) {
        commKey = 0x6c5f070e;
        good = true;
    } else if (!good) {
        int v = Fn_0102f810()->m_1030a30(empire);
        commKey = ((delta <= v) - 1 & 0xa612289f) + 0x1273c3f6;
    }
    Obj* player = GetPlayerEmpire();
    Fn_00675250()->m_676e90(0x77893b39, 1);
    player->m_c31a00(-price);
    if (good) {
        RelationshipManager()->m_d05830(empireId, ((PlayerObj*)player)->empire_id);
        NounManager()->m_f67d90()->m_c7bc20(empireId, 0);
        empire->m_c322f0(1);
        RelationshipManager()->m_d038e0(empire, player);
        if (commKey == 0x38c512e1)
            eventKey = 0x5661a7c;
    }
    RelationshipManager()->m_d06240(empireId, ((PlayerObj*)player)->empire_id, eventKey, 1.0f);
    Planet* pl = GetActivePlanet();
    Fn_00b3d4a0()->m_aeb720(empireId, pl->emp->m_ce6950(), (int)0xc8fbf7d7,
                            (int)commKey, 0, 0);
}

// @ 0x0102d0b0
void AttackPlanet(int param1, int param2) {
    if (!param2)
        return;
    Obj* empire = StarManager()->m_ba9370(param1);
    Obj* avatar = ((Obj*)param2)->m_b8de30()->m_b1fdb0();
    Obj* empire2 = StarManager()->m_ba9370((int)avatar);
    Obj* mission = GetMissionManager()->m_fec590(0xbbae6b99, param2, empire2, 0);
    if (!mission)
        return;
    Obj* raid = vc1<Obj*>(mission, 0xc, 0x3960c0a);
    if (!raid)
        return;
    raid->m_c5b370(empire);
    raid->m_c47180(param2);
    int n = raid->m_c5b530();
    raid->m_c5b390(n);
    raid->m_c485b0();
}

// @ 0x0102d150
int GetAttackRequestResponse(int param) {
    int fail = 0xec3ae04;
    Obj* planet = g_attackRequestPlanets[g_targetPlanetIndex];
    Obj* banners = StarManager()->m_ba6dc0(planet);
    int local;
    if (GetMissionManager()->m_fee590(banners, &local))
        return (local - param) != 0 ? 0xa6cc89f3 : 0x6f3064cc;
    return fail;
}

// @ 0x0102d7e0
void ClearAttackRequest(void) {
    Obj** begin = g_attackRequestPlanets;
    Obj** end = g_attackRequestPlanetsEnd;
    StrCopy(begin, end, 0);
    Obj** q = end - (g_attackRequestPlanetsEnd - begin);
    g_attackRequestPlanetsEnd = q;
    g_targetPlanetIndex = -1;
}

// eastl::vector<unsigned int, sp_vector_allocator>::push_back, inlined at the call site.
void U32Vec::push_back(uint32_t v) {
    uint32_t* p = e;
    if (p < c) {
        e = p + 1;
        if (p) *p = v;
    } else {
        m_4558a0(p, &v);
    }
}

// @ 0x0102d820
void Shutdown(void) {
    SpaceGame* sg = (SpaceGame*)SpaceGameGet();
    if (sg->trading->m_1075500())
        ((SpaceGame*)SpaceGameGet())->trading->m_1075ef0();
    Fn_00b3d4a0()->m_aea210();
    if (!IsWorldLayoutFlagSet(2))
        return;

    LaunchData* obj = (LaunchData*)operator_new6(0x9c, "App", 0, 0, 0, 0);
    if (obj) {
        obj->m_5a9080();
        if (obj) vc0<void>(obj, 4);
    }
    Obj* a = Fn_00401090();
    Vec3* p = a->m_4df400();
    obj->f010 = *(uint32_t*)&p->x;
    obj->f014 = *(uint32_t*)&p->y;
    obj->f018 = *(uint32_t*)&p->z;
    obj->f00c = 0xa56567f7;
    if (obj->p094) {
        obj->p094 = 0;
        vc0<void>(obj->p094, 4);
    }
    obj->f024 = g_15da7c4;
    obj->f028 = g_15da7c8;
    obj->f02c = g_15da7cc;
    obj->f030 = g_15da7d0;
    obj->f035 = 1;
    obj->f034 = 0;
    obj->f036 = 0;
    obj->f038 = 0;
    obj->f037 = 0;
    obj->f039 = 0;
    obj->f03c = 1;
    obj->f06d = 1;

    TerrainPlayer* tp = NounManager()->m_f67d90();
    if (tp) {
        obj->vec.push_back(tp->t10fc);
        obj->vec.push_back(tp->t1100);
        obj->vec.push_back(tp->t1104);
        obj->vec.push_back(tp->t1108);
        obj->vec.push_back(tp->t110c);
    }
    obj->f090 = 0x66787bc;

    Obj* player = GetPlayerEmpire();
    PlayerObj* pj = (PlayerObj*)player;
    int key = 0x11;
    // (rbtree lookup of the player's feedback string, then basic_string<wchar_t>::assign)
    Fn_00e5c780((char*)pj + 0x14, &key, (void*)((char*)obj + 0x40));

    obj->f03d = 1;
    obj->f064 = 1;
    Fn_00b1dee0(Fn_00b3d320((Obj*)obj));
    vc0<void>(obj, 8);
}
