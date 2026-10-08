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
};

struct TradeMgr {
    void m_10383a0(Obj* sys);                         // RemoveAllTradeRoutesFromSystem
    int m_1037e40(int sysId, int empId);              // GetPlayerProgressOnTradeRoute
};

struct StarMgr {
    Obj* m_ba9370(int id);                            // cStarManager::GetEmpireByID
    TradeMgr* m_ba6490();                             // trade route manager
    void m_bb59b0(Obj* p, Obj** outPlanet);           // GetOrActivatePlanet
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

template <class R> inline R vc0(void* o, int off) {
    typedef R(__thiscall * F)(void*);
    return ((F)(*(void***)o)[off / 4])(o);
}
template <class R, class A, class B, class C> inline R vc3(void* o, int off, A a, B b, C c) {
    typedef R(__thiscall * F)(void*, A, B, C);
    return ((F)(*(void***)o)[off / 4])(o, a, b, c);
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
