// s00b99ed0 -- creates a civ-mode city at a position: sets up the player's civilization / tribe, labels it
// from the species profile, places the city (be8680) and fills in the request record.
// cdecl(request*, Vector3* pos, Quat* rot), returns the new city.
// Flags: /O2 /MD /Gy /TP /arch:SSE
#include "types.h"

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct Quat {
    float x, y, z, w;
    Quat() {}
    Quat(const Quat& o) : x(o.x), y(o.y), z(o.z), w(o.w) {}
};

extern wchar_t g_emptyWStr;   // 0x01667bac
struct WStr {                 // eastl::basic_string<wchar_t>: begin, end, capacity, allocator
    wchar_t* b;
    wchar_t* e;
    wchar_t* cap;
    uint32_t alloc;
    WStr() { b = e = &g_emptyWStr; cap = &g_emptyWStr + 1; }
    ~WStr();
};
extern "C" void operator_delete__(void* p);   // 0x00f47380
inline WStr::~WStr()
{
    if ((cap - b) > 1 && b)
        operator_delete__(b);
}

struct RandomLCG {
    uint32_t seed;
    uint32_t RandomUint32Uniform(uint32_t n);   // 0x00a68fb0
    double RandomDoubleUniform();               // 0x009360d0
};
extern RandomLCG g_Random;                      // 0x01601760

extern int g_1688884, g_1688888;
extern float g_168887c, g_1688880;

// ---- managed object (intrusive ref count; its owner destroys it) -------------------------------------
struct Obj;
struct IOwner {
    virtual void o0();
    virtual void o1();
    virtual void o2();
    virtual void o3();
    virtual void o4();
    virtual void o5();
    virtual void o6();
    virtual void o7();
    virtual void o8();
    virtual void o9();
    virtual void o10();
    virtual void o11();
    virtual void o12();
    virtual void o13();
    virtual void o14();
    virtual void o15();
    virtual void o16();
    virtual void o17();
    virtual void o18();
    virtual void o19();
    virtual void o20();
    virtual void o21();
    virtual void o22();
    virtual void o23();
    virtual void o24();
    virtual void o25();
    virtual void o26();
    virtual void o27();
    virtual void o28();
    virtual void o29();
    virtual void o30();
    virtual void o31();
    virtual void o32();
    virtual void o33();
    virtual void o34();
    virtual void o35();
    virtual void o36();
    virtual void o37();
    virtual void o38();
    virtual void o39();
    virtual void o40();
    virtual void o41();
    virtual void o42();
    virtual void o43();
    virtual void o44();
    virtual void o45();
    virtual void o46();
    virtual void o47();
    virtual void o48();
    virtual void o49();
    virtual void o50();
    virtual void o51();
    virtual void o52();
    virtual void o53();
    virtual void o54();
    virtual void o55();
    virtual void o56();
    virtual void o57();
    virtual void o58();
    virtual void o59();
    virtual void o60();
    virtual void o61();
    virtual void o62();
    virtual void o63();
    virtual void o64();
    virtual void o65();
    virtual void o66();
    virtual void o67();
    virtual void o68();
    virtual void o69();
    virtual void o70();
    virtual void o71();
    virtual void o72();
    virtual void o73();
    virtual void o74();
    virtual void o75();
    virtual void o76();
    virtual void o77();
    virtual void o78();
    virtual void o79();
    virtual void o80();
    virtual void o81();
    virtual void o82();
    virtual void o83();
    virtual void o84();
    virtual void o85();
    virtual void o86();
    virtual void o87();
    virtual void o88();
    virtual void o89();
    virtual void o90();

    virtual void Cancel(Obj* o, int z);          // +0x16c
    virtual void Destroy(Obj* o, bool flag);     // +0x170
};
struct Obj {
    IOwner* owner;
    union { uint32_t f4; struct { uint32_t low : 31; uint32_t top : 1; } b4; };
    char pad[0x40 - 8];
    int refs;
};
inline void ReleaseObj(Obj* o)
{
    int n = o->refs;
    if (n > 1)
        o->refs = n - 1;
    else
        o->owner->Destroy(o, o->b4.top != 0);
}

struct City;
struct ModeObj {
    void FUN_00ce8de0(City* c);                  // 0x00ce8de0
};
struct CivMode {
    char pad0[0x29];
    char flag29;
    char pad1[0x104 - 0x2a];
    Obj* f104;
    ModeObj* FUN_00cf7500();                     // 0x00cf7500
};
extern "C" CivMode* FUN_00cf74c0();

struct TestSys { char pad[0x70]; void* listNext; };
extern TestSys* g_015fd928;                      // 0x015fd928

// ---- game objects -------------------------------------------------------------------------------------
struct Iface {                                   // embedded interface object (vptr at its start)
    virtual void v0(void* x);
    virtual void v1();
    virtual void v2(void* x);
    virtual void* v3();
    virtual void i4();
    virtual void i5();
    virtual void i6();
    virtual void i7();
    virtual void i8();
    virtual void i9();
    virtual void i10();

    virtual Vector3* v11();                      // +0x2c
    virtual void j12();
    virtual void j13();
    virtual void j14();
    virtual void j15();
    virtual void j16();
    virtual void j17();
    virtual void j18();
    virtual void j19();
    virtual void j20();
    virtual void j21();
    virtual void j22();
    virtual void j23();
    virtual void j24();
    virtual void j25();
    virtual void j26();
    virtual void j27();
    virtual void j28();
    virtual void j29();
    virtual void j30();
    virtual void j31();
    virtual void j32();
    virtual void j33();
    virtual void j34();
    virtual void j35();
    virtual void j36();

    virtual void v37(void* x);                   // +0x94
};
struct SpeciesProfile {
    char pad[0x504];
    char animKey;
    void GetUiName(WStr* out);                   // 0x004da330
};
struct Tribe {
    virtual void t0(); virtual void t1(); virtual void t2(); virtual void t3(); virtual void t4(); virtual void t5();
    virtual void t6(); virtual void t7(); virtual void t8(); virtual void t9(); virtual void t10(); virtual void t11();
    virtual void t12(); virtual void t13(); virtual void t14(); virtual void t15(); virtual void t16(); virtual void t17();
    virtual void t18();
    virtual int GetType();                       // +0x4c
    char pad[0x34 - 4];
    Iface f34;
    SpeciesProfile* GetSlot0(int i);             // 0x00c8e820
};
struct FbNode {
    FbNode* right;
    FbNode* left;
    FbNode* parent;
    uint32_t color;
    uint32_t key;
    void* value;                                  // +0x14
};
struct FbIter {
    FbNode* node;
    FbIter() {}
    FbIter(const FbIter& o) : node(o.node) {}
};
struct FbMap {
    FbIter find(const uint32_t& key);             // 0x00e5c780
};
struct Obj3c {
    uint32_t d[2];
    void FUN_00b6f380(WStr* s);                   // 0x00b6f380
};
struct Civ {
    virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4(); virtual void c5();
    virtual void c6(); virtual void c7(); virtual void c8(); virtual void c9(); virtual void c10(); virtual void c11();
    virtual void c12(); virtual void c13(); virtual void c14(); virtual void c15(); virtual void c16(); virtual void c17();
    virtual void ApplyRequest(struct Req* r);    // +0x48
    char pad0[0x34 - 0x4];
    Iface f34;
    char pad1[0x3c - 0x38];
    Obj3c f3c;
    FbMap f44;
    char pad2[0x8a - 0x48];
    char b8a;
    void FUN_00befc40(Tribe* t);                  // 0x00befc40
    void FUN_00bebdd0(void* k);                   // 0x00bebdd0
    void FUN_00bf4370(City* c);                   // 0x00bf4370
    void FUN_00bf4eb0();                          // 0x00bf4eb0
    void FUN_00bf4fc0();                          // 0x00bf4fc0
};
struct CityExtra {
    char pad0[0x108];
    char b108;
    char pad1[0x110 - 0x109];
    Vector3* f110;
    char pad2[0x254 - 0x114];
    int f254;
};
struct CityHall {
    char pad[0x34];
    Iface f34;
};
struct City {
    virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4(); virtual void c5();
    virtual void c6(); virtual void c7(); virtual void c8(); virtual void c9(); virtual void c10(); virtual void c11();
    virtual void c12(); virtual void c13(); virtual void c14(); virtual void c15(); virtual void c16(); virtual void c17();
    virtual void SetType(int t);                  // +0x48
    char pad0[0x34 - 4];
    Iface f34;
    char pad1[0x120 - 0x38];
    Iface f120;
    char pad2[0x324 - 0x124];
    CityExtra* f324;
    CityHall* GetCityHall();                      // 0x00bd9b40
    void FUN_00be73d0(int a, int b);              // 0x00be73d0
    void FUN_00be8680(Vector3* p, float f, int pick, int a, int b, int c, int d, int mode, Quat* q, int e);   // 0x00be8680
};
struct Req {
    int id;
    Vector3 pos;
    Quat rot;
    char pad0[0x25 - 0x20];
    char b25;
    char pad1[0x28 - 0x26];
    int f28;
    char pad2[0x34 - 0x2c];
    int mode;
    char pad3[0x48 - 0x38];
    Vector3 out;
    int FUN_00a1ad10();                           // 0x00a1ad10
    void FUN_00ae38f0(int z);                     // 0x00ae38f0
};
struct TerrainSphere {
    char pad0[0x1150];
    char at1150;
    char pad1[0x1178 - 0x1151];
    int v1178, v117c, v1180;
};
struct NounMgr {
    Civ* GetPlayerCivilization();                 // 0x00b25fb0
    Tribe* GetPlayerTribe();                      // 0x00bfc5f0
    void FUN_00b21410(void* n);                   // 0x00b21410
    int FUN_00b20790(Req* r);                     // 0x00b20790
    void FUN_00b23560(Civ* c);                    // 0x00b23560
    TerrainSphere* GetCurrentTerrainSphere();     // 0x00f67d90
    void RemoveNoun(int id);                      // 0x00b225d0
};
struct Settings {
    SpeciesProfile* GetAvatarProfile();           // 0x004df420
};
struct SimSingleton {
    SimSingleton();                               // 0x00ae5c30
    void FUN_00ae3230(int v);                     // 0x00ae3230
};
void* operator new(unsigned int sz, const char* name, int a, int b, int c, int d);   // 0x00f473a0
extern SimSingleton* g_SimSingleton;              // 0x0167a60c

extern "C" {
NounMgr* FUN_00b3d300();
City* FUN_00bd9d70(Vector3* p, int z);
int FUN_00bef920(int v);
int FUN_00b993c0(int v);
Settings* FUN_00401090();
}

// @ 0x00b99ed0
City* CreateCivCity(Req* req, Vector3* pos, Quat* rot)
{
    NounMgr* nm = FUN_00b3d300();
    City* city = 0;
    Civ* civ;
    int pick = g_1688888 + g_Random.RandomUint32Uniform(g_1688884 - g_1688888 + 1);
    double lo = g_1688880;
    double hi = g_168887c;
    double v = g_Random.RandomDoubleUniform() * (hi - lo) + lo;
    if (v >= hi)
        v = hi;
    else if (lo > v)
        v = lo;
    float f = (float)v;
    int mode = req->mode;
    if (FUN_00cf74c0()->flag29 == 1) {
        if (!g_015fd928 || g_015fd928->listNext == &g_015fd928->listNext) {
            Obj* o = FUN_00cf74c0()->f104;
            if (o) {
                o->refs++;
                ReleaseObj(o);
            }
            o->owner->Cancel(o, 0);
            Obj** slot = &FUN_00cf74c0()->f104;
            Obj* old = *slot;
            if (old) {
                *slot = 0;
                ReleaseObj(old);
            }
        }
        Tribe* tribe = nm->GetPlayerTribe();
        if (tribe) {
            Vector3 p(*pos);
            int type = tribe->GetType();
            city = FUN_00bd9d70(&p, 0);
            city->SetType(type);
            civ = nm->GetPlayerCivilization();
            civ->FUN_00befc40(tribe);
            WStr name;
            SpeciesProfile* sp = tribe->GetSlot0(0);
            sp->GetUiName(&name);
            civ->f3c.FUN_00b6f380(&name);
            uint32_t key = 0xd;
            civ->f34.v0(civ->f44.find(key).node->value);
            civ->FUN_00bebdd0(&sp->animKey);
            civ->f34.v2(tribe->f34.v3());
            city->FUN_00be73d0(FUN_00bef920(req->f28), 0);
            civ->FUN_00bf4370(city);
            nm->FUN_00b21410(tribe);
            nm->FUN_00b21410(civ);
            civ->ApplyRequest(req);
            if (nm->FUN_00b20790(req) <= 4)
                nm->FUN_00b23560(civ);
            city->FUN_00be8680(&p, f, pick, 0, 1, 0, 0, mode, rot, 1);
            FUN_00b3d300()->GetPlayerCivilization()->FUN_00bf4eb0();
            CityHall* hall = city->GetCityHall();
            Iface* hf = &hall->f34;
            hf->v37(&FUN_00b3d300()->GetCurrentTerrainSphere()->at1150);
            Vector3* tv = city->f120.v11();
            TerrainSphere* ts = FUN_00b3d300()->GetCurrentTerrainSphere();
            ts->v1178 = ((int*)tv)[0];
            ts->v117c = ((int*)tv)[1];
            ts->v1180 = ((int*)tv)[2];
            int r = req->FUN_00a1ad10();
            if (r) {
                FUN_00b3d300()->RemoveNoun(r);
                req->FUN_00ae38f0(0);
            }
        }
    } else {
        city = FUN_00bd9d70(pos, 0);
        civ = nm->GetPlayerCivilization();
        civ->b8a = req->b25;
        WStr name;
        SpeciesProfile* sp = FUN_00401090()->GetAvatarProfile();
        sp->GetUiName(&name);
        civ->f3c.FUN_00b6f380(&name);
        uint32_t key = 0xd;
        civ->f34.v0(civ->f44.find(key).node->value);
        civ->FUN_00bebdd0(&sp->animKey);
        city->FUN_00be73d0(FUN_00bef920(req->f28), 0);
        civ->FUN_00bf4370(city);
        city->FUN_00be8680(pos, f, pick, 0, 1, 0, 0, mode, rot, 1);
        FUN_00b3d300()->RemoveNoun(FUN_00b993c0(req->id));
        req->id = -1;
    }
    FUN_00b3d300()->GetPlayerCivilization()->FUN_00bf4fc0();
    city->f324->b108 = 1;
    req->out = city->f324->f110[city->f324->f254];
    req->pos = Vector3(*pos);
    req->rot = Quat(*rot);
    if (!g_SimSingleton) {
        void* mem = new ("Simulator/SimSingleton", 0, 0, 0, 0) SimSingleton();
        g_SimSingleton = (SimSingleton*)mem;
    }
    g_SimSingleton->FUN_00ae3230(1);
    uint32_t key2 = 0xb;
    city->f34.v0(civ->f44.find(key2).node->value);
    FUN_00cf74c0()->FUN_00cf7500()->FUN_00ce8de0(city);
    return city;
}
