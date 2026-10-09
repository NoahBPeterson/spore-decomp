// Slice s0102df20: SP::DoSpaceCommAction (0x0102df20, 4528 bytes, cdecl).
//
// Dispatcher for the space "comm" screen actions. msg[0] is an FNV hash of the action name,
// arg is the other empire's id, mission the (optional) mission the action concerns. Every
// action ends in one of a few shared tails: an event log entry
//   EventLog()->AddEntry(arg, planet->empire->f184, 0xc8fbf7d7, <string id>, 0, 0)
// or the plain "refresh" call EventLog()->Refresh().
//
// Callees are masked relocations; declarations only need the right calling convention and
// argument sizes. Thiscall callees whose purpose is unknown are members of the opaque Obj
// named m_<va>. Arities were taken from `ret N` of each callee (the Ghidra decompile
// over-counts args that actually belong to a later thiscall).
// Flags: /O2 /MD /Gy /TP /arch:SSE.
#include "types.h"

typedef unsigned int uint;

struct Vec3 { float x, y, z; };
struct Quat { float x, y, z, w; };
struct Obj;
struct PtrVec { Obj** b; Obj** e; Obj** c; };

struct Obj {
    // event log / UI (b3d4a0, b3d4d0 return one of these)
    void m_aea210();
    void m_aeb720(int arg, int stringKey, int category, int text, int a, int b);
    void m_aeb3e0(int a, int b, int c, int d, int e, int f, int g, int h);
    void m_ae0930(const char* s, int a, int b, int c, int d, int e);
    void m_ae09b0(int id, void* data, int z);
    // empire / planet
    int m_ce6950();                       // empire id style getter ([this+0x184])
    Obj* m_b8de30();
    Vec3* m_5c65e0();                     // cCivData::GetCities
    Obj* m_c31730();                      // cEmpire::GetHomePlanet
    int m_c30c60();
    void m_c30bb0();
    void m_c31a00(int amount);
    int m_c313d0(Vec3 v);
    // managers
    Obj* m_ba9370(int id);                // cStarManager::GetEmpireByID
    Obj* m_ba6490();
    Obj* m_ba6dc0(Obj* p);
    float m_d06240(int a, int b, int key, float f);   // cRelationshipManager::RecordEvent
    int m_d00a70(int a, int b, int c);
    void m_d05830(int a, int b);
    void m_d038e0(Obj* a, Obj* b);        // StartPeace
    void m_d06920(Obj* a, Obj* b);        // StartAlliance
    Obj* m_ad49b0();
    Obj* m_f67d90();                      // cTerrainEditor::GetCurrentTerrainSphere
    void m_c77bf0(int key);
    void m_c7be30(Obj* e);
    // tuning
    int m_102fa30(int type);              // GetTradeCaptureOfferPrice
    int m_1030930(int type, Obj* emp);    // GetPeaceOfferPrice
    int m_1030390();                      // GetTradeRouteMaxNumber
    int m_1030650(int x);                 // CalcAttackRequestCost
    int m_10407d0(Obj* emp);
    // trade
    int m_1037f20();                      // GetNumberOfPlayerTradeRoutes
    void m_10393a0(Obj* sort, int arg, int key, uint pid);   // AddTradeRoute
    Obj* m_bfc5f0(int a, int b);
    void m_fe5430();
    // sim
    Obj* m_a1ad60();                      // GetPlayerInventory
    void m_ff45e0(void* key);
    void m_106ac90(int x);
    void m_10027b0(int a, int b);         // AddPosseMember
    void m_10019a0();
    void m_1046fc0();
    // missions
    void m_c46e20(int x);                 // GiveOnAcceptItems
    void m_c485b0();                      // Accept
    void m_c485c0();
    void m_c485d0();
    void m_c485e0();
    void m_c485f0();
    void m_c59eb0();                      // AcceptCurrentStep
    void m_c59f00();
    void m_c59f60();
    Obj* m_c59d90();                      // GetCurrSubMission
    void m_c52070();                      // ValidateProgressEvent
    int m_c57ef0(int arg, void* planet);  // cSPMissionMultiDelivery::OnDelivery
    Obj* m_b1fdb0();                      // GetAvatar
    Obj* m_bba790();
    int m_b8dab0();
    Obj* m_c8b770();                      // cStar::GetSolarSystem
    void m_676e90(uint id, int x);        // Achievements::Controller::AutoTest
};

struct Planet { uint pad[79]; Obj* emp; };           // +0x13c
struct Emp { uint pad[33]; uint f84; };              // +0x84
struct Tuning90 : Obj { uint pad[36]; int f90; };          // +0x90
inline uint& nounField(Obj* n, int off) { return *(uint*)((char*)n + off); }
struct VecCopy {                              // eastl::vector<Obj*> copy (50d440 ctor / 4e1bf0 dtor)
    Obj** b; Obj** e; Obj** c;
    VecCopy(const PtrVec& src);   // 0x0050d440
    ~VecCopy();                   // 0x004e1bf0
};
struct SpaceGameObj { uint pad[5]; Obj* f14; };
struct Flag44 { char pad[0x44]; char flag; };

// Transform-like event payload built from a position + orientation (ad79d0 ctor / ad7ad0 dtor)
struct EvtData {
    char pad[0x1c];
    float f1c;
    float f20;
    EvtData(const Vec3* p, const Quat* q);   // 0x00ad79d0
    ~EvtData();                              // 0x00ad7ad0 cActionTarget::~cActionTarget
};

struct Z3 { int a, b, c; Z3() : a(0), b(0), c(0) {} };

// ---- cdecl callees ----
Planet* GetActivePlanet();                 // 0x01021260 SP::cSPLivingUniverse::GetActivePlanet
Obj* GetSystemAT();                        // 0x00a206f0 EA::Audio::GetSystemAT
uint GetPlayerEmpireID();                  // SP::cSPLivingUniverse::GetPlayerEmpireID
Obj* GetPlayerEmpire();                    // SP::cSPLivingUniverse::GetPlayerEmpire
int GetUniverseContext();                  // 0x01021080
Obj* Fn_01021240();
Obj* Fn_01021230();
Obj* StarManager();
Obj* RelationshipManager();
Obj* NounManager();
Obj* SpaceGameGet();
Obj* GetUFOSimulator();
Obj* MessageServer();                      // 0x0067dcc0
Obj* Fn_0102f810();                        // SP::GetSpaceEconomyTuning
Tuning90* GetSpaceRelationshipTuning();
Obj* Fn_00b3d4a0();
Obj* Fn_00b3d4d0();
Obj* Fn_00675250();                        // Achievements::Controller::Get
void Fn_01044640();
void Fn_0102caa0(int arg, Planet* p);
void Fn_0102c980(Obj* x);
void Fn_0102cd30();
void Fn_0102cd40();
void Fn_0102c9e0(int arg, Planet* p, int x);
void Fn_0102cc30(int arg, Planet* p);
void Fn_0102d7e0();
void Fn_0102d820();
void Fn_0102daa0(Obj* x);
void Fn_0102d0b0(int arg, Obj* x);
int Fn_0102b690(Obj* avatar, uint pid, int count);
void Fn_00c8c9d0(Obj* x);
void Fn_00c8d000(Obj* x, uint pid);
char Fn_00c8b920(int empId, uint pid);
Obj* Fn_00aed3f0(Obj* mission);
Obj* icast_Delivery(Obj* m);               // EA::COM::interface_cast<cSPMissionMultiDelivery*>
Obj* icast_Fetch(Obj* m);                  // interface_cast<cSPMissionFetch*>
Obj* icast_Flight101(Obj* m);              // interface_cast<cSPMissionFlight101*>
void GiveGift(int arg, int kind);          // 0x0102cae0
void TryBreakAlliance(int arg);            // 0x0102cd90
void TryCreateAlliance(int arg);           // 0x0102ce30
void TryPeaceOffer(int arg, int price);    // 0x0102cf10
void TryPurchaseOffer(int arg, Obj* sort, int price);   // 0x0102d1b0
int GetAttackRequestResponse(int arg);     // 0x0102d150
void Fn_00e39ab0(int key, Obj* emp, Z3* d, Z3* c, int v, int zero, Z3* b, Z3* a);

extern char g_key_016de7e4[];
extern PtrVec g_AttackRequestPlanets;       // 0x16decac
extern int g_TargetPlanetIndex;             // 0x15b751c
extern const char k_Military_Planet[];      // 0x0149963c "SPG_SystemSurrender_Military_Planet"

template <class R> inline R vc0(void* o, int off) {
    typedef R(__thiscall * F)(void*);
    return ((F)(*(void***)o)[off / 4])(o);
}
template <class R, class A> inline R vc1(void* o, int off, A a) {
    typedef R(__thiscall * F)(void*, A);
    return ((F)(*(void***)o)[off / 4])(o, a);
}
template <class R, class A, class B> inline R vc2(void* o, int off, A a, B b) {
    typedef R(__thiscall * F)(void*, A, B);
    return ((F)(*(void***)o)[off / 4])(o, a, b);
}
template <class R, class A, class B, class C> inline R vc3(void* o, int off, A a, B b, C c) {
    typedef R(__thiscall * F)(void*, A, B, C);
    return ((F)(*(void***)o)[off / 4])(o, a, b, c);
}

static inline void LogTail(int arg, Planet* p, int text) {
    Fn_00b3d4a0()->m_aeb720(arg, p->emp->m_ce6950(), (int)0xc8fbf7d7, text, 0, 0);
}

// @ 0x0102df20
void DoSpaceCommAction(int* msg, int arg, Obj* mission) {
    Planet* planet = GetActivePlanet();

    Obj* at = GetSystemAT();
    int v = at ? vc0<int>(at, 0x20) : 0;
    at = GetSystemAT();
    if (at) {
        vc1<void>(at, 0x38, 0x3475365);
        vc2<void>(at, 0x40, 0x3475381, (int)0x7cd49637);
        vc2<void>(at, 0x40, 0x3475385, v);
        vc0<void>(at, 0x58);
    }

    switch (msg[0]) {
    case (int)0x8a820a27:
        Fn_0102caa0(arg, planet);
        return;
    case (int)0x8a43c6d9:
        Fn_0102c980(planet->emp->m_b8de30());
        LogTail(arg, planet, (int)0x80e15bcf);
        return;
    case (int)0x86eb5442:
        Fn_0102cd30();
        return;
    case (int)0x9320dbba:
        TryPeaceOffer(arg, Fn_0102f810()->m_1030930(3, StarManager()->m_ba9370(arg)));
        return;
    case (int)0x9320dbbb:
        TryPeaceOffer(arg, Fn_0102f810()->m_1030930(4, StarManager()->m_ba9370(arg)));
        return;
    case (int)0x9320dbbc:
        TryPeaceOffer(arg, Fn_0102f810()->m_1030930(1, StarManager()->m_ba9370(arg)));
        return;
    case (int)0x9320dbbd:
        TryPeaceOffer(arg, Fn_0102f810()->m_1030930(2, StarManager()->m_ba9370(arg)));
        return;
    case (int)0x9320dbbf:
        TryPeaceOffer(arg, Fn_0102f810()->m_1030930(0, StarManager()->m_ba9370(arg)));
        return;
    case (int)0x9b18a2fa:
        if (mission) mission->m_c46e20(0);
        return;
    case (int)0xab909e37: {
        Fn_00c8c9d0(Fn_01021240());
        ((Flag44*)Fn_01021230())->flag = 0;
        Fn_00b3d4a0()->m_aea210();
        return;
    }
    case (int)0xa624e3fa: {
        if (!mission) return;
        Obj* m = Fn_00aed3f0(mission);
        if (!m) return;
        if (vc0<int>(m, 0x60) == 0) m->m_c485b0();
        else m->m_c59eb0();
        return;
    }
    case (int)0xacc50317:
        if (mission) mission->m_c485f0();
        return;
    case (int)0xaccf645c:
        SpaceGameGet()->m_a1ad60()->m_ff45e0(g_key_016de7e4);
        return;
    case (int)0xae44b32e:
    case 0x577614c6:
        RelationshipManager()->m_d06240(arg, GetPlayerEmpireID(), 0x5b6cf09, 1.0f);
        NounManager()->m_f67d90()->m_c77bf0(0x5f1f0ca);
        LogTail(arg, planet, 0x2ea8fb98);
        return;
    case (int)0xc0816f3b:
        if (mission) mission->m_c485d0();
        return;
    case (int)0xc9cb7680:
        GetUFOSimulator()->m_10019a0();
        return;
    case (int)0xca667561:
        GetUFOSimulator()->m_10027b0(arg, 1);
        LogTail(arg, planet, (int)0xe9146e3c);
        return;
    case (int)0xd13e4ca2:
        GiveGift(arg, 1);
        return;
    case (int)0xd95019bd:
        TryBreakAlliance(arg); // 0x0102cd90
        return;
    case (int)0xd91dba31: {
        if (!mission) return;
        Obj* m = Fn_00aed3f0(mission);
        if (!m) return;
        m->m_c59f60();
        int r = vc0<int>(mission, 0xa4);
        Fn_00b3d4a0()->m_aeb720(arg, planet->emp->m_ce6950(), r, (int)0x8b756f4b, (int)mission, 0);
        return;
    }
    case (int)0xdac9a912:
        GiveGift(arg, 0);
        return;
    case (int)0xeab9e2c9: {
        Obj* emp = StarManager()->m_ba9370(arg);
        Z3 a, b, c, d;
        Fn_00e39ab0(0x16f8fdb4, emp, &d, &c, (int)nounField(Fn_01021240(), 0x70), 0, &b, &a);
        int ctx = GetUniverseContext();
        if (ctx == 0) {
            Fn_01044640();
            vc3<void>(MessageServer(), 0x14, 0x678a3ef, 0, 0);
            Fn_00b3d4d0()->m_ae0930(k_Military_Planet, 1, 0, 0, 0, 0);
        } else if (ctx == 1) {
            Obj* sys = Fn_01021230()->m_c8b770();
            PtrVec* list = (PtrVec*)((char*)sys + 0x10);
            Obj* best = 0;
            Obj* inv = GetUFOSimulator()->m_a1ad60();
            Vec3* pp = vc0<Vec3*>((char*)inv + 0x34, 0x2c);
            Vec3 P = *pp;
            int n = list->e - list->b;
            for (int i = 0; i < n; i++) {
                Obj* it = list->b[i];
                if (Fn_00c8b920((int)nounField(it, 0x13c), GetPlayerEmpireID())) {
                    Vec3* q = vc0<Vec3*>(it, 0x2c);
                    float dx = P.x - q->x, dy = P.y - q->y, dz = P.z - q->z;
                    if (dz * dz + dy * dy + dx * dx < 3.40282346e+38f) best = it;
                }
            }
            if (best) {
                Vec3* q = vc0<Vec3*>(best, 0x2c);
                P = *q;
                Quat* o = vc0<Quat*>(best, 0x30);
                Quat Q = *o;
                EvtData ev(&P, &Q);
                ev.f20 = vc0<float>(best, 0x70);
                ev.f1c = vc0<float>(best, 0x74);
                Fn_00b3d4d0()->m_ae09b0(0x5f848353, &ev, 0);
                Fn_00b3d4d0()->m_ae0930("SPG_SystemSurrender_Military_Solar", 1, 0, 0, 0, 0);
            }
        }
        Obj* avatar = Fn_01021240()->m_b1fdb0();
        Fn_00c8d000(Fn_01021240(), GetPlayerEmpireID());
        int count = 0;
        PtrVec* lst = (PtrVec*)Fn_01021240()->m_bba790();
        int n = lst->e - lst->b;
        for (int i = 0; i < n; i++)
            if (lst->b[i]->m_b8dab0() == 5) count++;
        char ok = (char)Fn_0102b690(avatar, GetPlayerEmpireID(), count);
        Fn_00675250()->m_676e90(0xd3f14a26, 1);
        if (ok) return;
        Fn_00b3d4a0()->m_aea210();
        return;
    }
    case (int)0xe3b5dbdf: {
        if (!mission) return;
        Obj* d = icast_Delivery(mission);
        if (!d) return;
        int got = d->m_c57ef0(arg, planet);
        int r = vc0<int>(mission, 0xa4);
        Fn_00b3d4a0()->m_aeb720(arg, planet->emp->m_ce6950(), r, got, (int)mission, 0);
        return;
    }
    case (int)0xdaff3ce0: {
        Fn_0102daa0(Fn_01021240());
        VecCopy local(g_AttackRequestPlanets);
        LogTail(arg, planet, local.b == local.e ? 0x174890ac : (int)0xac4e8b42);
        return;
    }
    case (int)0xfaa8c815: {
        if (!mission) return;
        Obj* f = icast_Fetch(mission);
        if (!f) {
            Obj* fl = icast_Flight101(mission);
            if (!fl) return;
            f = icast_Fetch(fl->m_c59d90());
            if (!f) return;
        }
        f->m_c52070();
        return;
    }
    case 0x7d5647d: {
        if (!mission) return;
        Obj* m = Fn_00aed3f0(mission);
        if (!m) return;
        m->m_c59f00();
        return;
    }
    case 0xc5d2701:
        Fn_0102cc30(arg, planet);
        return;
    case 0x12293370:
        TryPurchaseOffer(arg, planet->emp->m_b8de30(), Fn_0102f810()->m_102fa30(4));
        return;
    case 0x12293371:
        TryPurchaseOffer(arg, planet->emp->m_b8de30(), Fn_0102f810()->m_102fa30(3));
        return;
    case 0x12293374:
        TryPurchaseOffer(arg, planet->emp->m_b8de30(), Fn_0102f810()->m_102fa30(0));
        return;
    case 0x12293376:
        TryPurchaseOffer(arg, planet->emp->m_b8de30(), Fn_0102f810()->m_102fa30(2));
        return;
    case 0x12293377:
        TryPurchaseOffer(arg, planet->emp->m_b8de30(), Fn_0102f810()->m_102fa30(1));
        return;
    case 0x12d9113a:
        GiveGift(arg, 2);
        return;
    case 0x135594f5: {
        Obj* sort = planet->emp->m_b8de30();
        int key = GetPlayerEmpire()->m_c313d0(*sort->m_5c65e0());
        int status = (int)0x917bee91;
        Obj* tm = StarManager()->m_ba6490();
        int max = Fn_0102f810()->m_1030390();
        if (max > 0 && tm->m_1037f20() >= max) status = (int)0xdc68eaa0;
        int rel = RelationshipManager()->m_d00a70(arg, GetPlayerEmpireID(), 1);
        if (rel < 3) {
            status = 0x4584b3cd;
        } else if (status == (int)0x917bee91) {
            StarManager()->m_ba6490()->m_10393a0(sort, arg, key, GetPlayerEmpireID());
            SpaceGameGet()->m_bfc5f0(0x19, 1)->m_fe5430();
        }
        LogTail(arg, planet, status);
        return;
    }
    case 0x1a771205: {
        RelationshipManager()->m_d06240(arg, GetPlayerEmpireID(), 0x594afff, 1.0f);
        Obj* e = StarManager()->m_ba9370(arg);
        e->m_c30bb0();
        Fn_00b3d4a0()->m_aea210();
        ((SpaceGameObj*)SpaceGameGet())->f14->m_106ac90(e->m_c30c60());
        return;
    }
    case 0x1febc3ea:
        if (mission) mission->m_c485c0();
        return;
    case 0x2027bc64:
        Fn_0102d7e0();
        LogTail(arg, planet, 0x2ea8fb98);
        return;
    case 0x2125a82a:
        RelationshipManager()->m_d06240(arg, GetPlayerEmpireID(), 0x5f62736, 1.0f);
        Fn_00b3d4a0()->m_aea210();
        return;
    case 0x2e42264b:
        NounManager()->m_f67d90()->m_c7be30(StarManager()->m_ba9370(arg));
        Fn_00b3d4a0()->m_aea210();
        return;
    case 0x307071c8:
        g_TargetPlanetIndex = 0;
        LogTail(arg, planet, GetAttackRequestResponse(arg));
        return;
    case 0x307071cb:
        g_TargetPlanetIndex = 1;
        LogTail(arg, planet, GetAttackRequestResponse(arg));
        return;
    case 0x307071ca:
        g_TargetPlanetIndex = 2;
        LogTail(arg, planet, GetAttackRequestResponse(arg));
        return;
    case 0x307071cd:
        g_TargetPlanetIndex = 3;
        LogTail(arg, planet, GetAttackRequestResponse(arg));
        return;
    case 0x31484f2c:
        TryCreateAlliance(arg);
        return;
    case 0x39a2e1bc:
        Fn_00b3d4a0()->m_aea210();
        return;
    case 0x3de7cb69: {
        uint pid = GetPlayerEmpireID();
        RelationshipManager()->m_d05830(arg, pid);
        Obj* e = StarManager()->m_ba9370(arg);
        RelationshipManager()->m_d038e0(e, GetPlayerEmpire());
        RelationshipManager()->m_d06240(arg, pid, 0x57e4fe3, 1.0f);
        PtrVec* lst = (PtrVec*)NounManager()->m_ad49b0();
        int n = lst->e - lst->b;
        for (int i = 0; i < n; i++) {
            Obj* nn = lst->b[i];
            if (nn && (nounField(nn, 0x714) == 8 || nounField(nn, 0x714) == 6)) {
                vc0<void>((char*)nn + 0x508, 0x38);
                Obj* h = (Obj*)nounField(nn, 0x68c);
                if (h) {
                    nounField(nn, 0x68c) = 0;
                    vc0<void>(h, 4);
                }
            }
        }
        Fn_00b3d4a0()->m_aea210();
        return;
    }
    case 0x4c113574: {
        int idx = (int)g_AttackRequestPlanets.b[g_TargetPlanetIndex];
        Obj* t = StarManager()->m_ba6dc0((Obj*)idx);
        Fn_0102d0b0(arg, t);
        GetPlayerEmpire()->m_c31a00(-Fn_0102f810()->m_1030650((int)t));
        Fn_0102d7e0();
        Fn_00b3d4a0()->m_aea210();
        return;
    }
    case 0x4c182387: {
        Fn_00b3d4a0()->m_aea210();
        Obj* e = StarManager()->m_ba9370(arg);
        Fn_00b3d4a0()->m_aeb3e0(((Emp*)e)->f84, e->m_c30c60(), e->m_c31730()->m_ce6950(),
                                (int)0x95bbbbfc, 0x7fc02fbc, 2, 0, 0);
        return;
    }
    case 0x52b8a79f:
        GetPlayerEmpire()->m_c31a00(GetSpaceRelationshipTuning()->f90);
        RelationshipManager()->m_d06240(arg, GetPlayerEmpireID(), 0x594b017, 1.0f);
        Fn_00b3d4a0()->m_aea210();
        return;
    case 0x5c2efcb0: {
        Obj* e = StarManager()->m_ba9370(arg);
        GetPlayerEmpire()->m_c31a00(-GetSpaceRelationshipTuning()->m_10407d0(e));
        e->m_c30bb0();
        Fn_00b3d4a0()->m_aea210();
        return;
    }
    case 0x5d79f0cb: {
        if (!mission) return;
        mission->m_c485b0();
        uint pid = GetPlayerEmpireID();
        if (arg != (int)pid) RelationshipManager()->m_d06240(arg, pid, 0x5b6ce81, 1.0f);
        return;
    }
    case 0x6c70b992: {
        Obj* e = StarManager()->m_ba9370(arg);
        RelationshipManager()->m_d06920(e, GetPlayerEmpire());
        Fn_00b3d4a0()->m_aea210();
        return;
    }
    case 0x75ad98bb:
        Fn_0102cd40();
        return;
    case 0x7b1f7d82:
        Fn_0102c9e0(arg, planet, msg[1]);
        return;
    case 0x7d8aa8be:
        if (mission) mission->m_c485e0();
        return;
    case 0x7e9ccaab:
        Fn_0102d820();
        return;
    }
}
// --- equivalence checker address annotations
    void GetActivePlanet(...); // 0x01021260
    void GetSystemAT(...); // 0x00a206f0
    void GiveGift(...); // 0x0102cae0
    void TryBreakAlliance(...); // 0x0102cd90
    void TryPeaceOffer(...); // 0x0102cf10

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
