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
    char pad0[0x20];
    int mField24;                                 // +0x24
    char pad24[0xc];
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
struct CityInfo {
    int mField0;                                  // +0x00
    int pad04[7];                                 // +0x04
    int mContinent;                               // +0x20
    unsigned char pad24;                          // +0x24
    unsigned char pad25;                          // +0x25
    unsigned char mFlag26;                        // +0x26
    char pad27[0xa];                              // +0x27
    unsigned char mFlag31;                        // +0x31
    char pad32[0x2];                              // +0x32
    int mField34;                                 // +0x34
    int mField38;                                 // +0x38
    int mField3c;                                 // +0x3c
    int pad40[9];                                 // +0x40

    void FUN_00ae4230();                          // 0x00ae4230 (construct)
    void FUN_00ae42a0();                          // 0x00ae42a0 (destroy)
};

struct CityInfoVector {
    CityInfo* m_begin;                            // +0x00
    CityInfo* m_end;                              // +0x04
    CityInfo* m_capacity;                         // +0x08
    void FUN_00ae5d60(CityInfo* pos, CityInfo* value); // 0x00ae5d60
};

struct SimSingleton {
    char pad0[0x14];
    CityInfoVector m_cityInfos;                   // +0x14
    char pad20[0xc8 - 0x20];

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

// ---------------------------------------------------------------- fixed slot vector helper
struct FixedSlotVector
{
    void* m_begin;      // +0x00
    void* m_end;        // +0x04
    void* m_capacity;   // +0x08
    char  m_pad0c[0x8];
    void* m_field14;    // +0x14

    void InitStorage(void* arg);       // 0x004cd3c0
    FixedSlotVector* Init(void* arg);  // 0x00b9a5b0 (ret 4)
};

// @ 0x00b9a5b0
FixedSlotVector* FixedSlotVector::Init(void* arg)
{
    m_begin = (char*)this + 0x18;
    m_end = (char*)this + 0x18;
    void* capacity = (char*)m_begin + 0x14;
    m_capacity = capacity;
    m_field14 = 0;
    void* storageArg = arg;
    InitStorage(storageArg);
    return this;
}

// ---------------------------------------------------------------- planet / star managers
struct PlanetMgr {
    int  GetContinent(Vector3* pos);                              // 0x00b88590
    bool FindClosestWater(Vector3* pos, float radius, Vector3* out); // 0x00b8bb70
};
PlanetMgr* PlanetModel();                                          // 0x00b3d350

struct StarMgr {
    int FUN_00ba6630(int a);                                       // 0x00ba6630
};
StarMgr* StarManager();                                            // 0x00b3d2a0

// @ 0x00b9a8d0
void FUN_00b9a8d0(City* city, bool npc)
{
    if (!g_SimSingleton) {
        void* mem = new ("Simulator/SimSingleton", 0, 0, 0, 0) SimSingleton();
        g_SimSingleton = (SimSingleton*)mem;
    }

    CityInfoVector* infos = &g_SimSingleton->m_cityInfos;
    if (infos->m_end < infos->m_capacity) {
        CityInfo* slot = infos->m_end;
        infos->m_end = slot + 1;
        if (slot)
            slot->FUN_00ae4230();
    } else {
        CityInfo temp;
        temp.FUN_00ae4230();
        infos->FUN_00ae5d60(infos->m_end, &temp);
        temp.FUN_00ae42a0();
    }

    if (!g_SimSingleton) {
        void* mem = new ("Simulator/SimSingleton", 0, 0, 0, 0) SimSingleton();
        g_SimSingleton = (SimSingleton*)mem;
    }

    CityInfo* info = g_SimSingleton->m_cityInfos.m_end - 1;
    info->mContinent = PlanetModel()->GetContinent(city->f34.v11());
    info->mFlag26 = (unsigned char)npc;
    info->pad24 = 0;
    info->mField0 = city->mField24;

    Vector3 water;
    unsigned char found = (unsigned char)PlanetModel()->FindClosestWater(
        city->f34.v11(), 70.0f, &water);
    info->mFlag31 = found;
    info->mField34 = (int)g_Random.RandomUint32Uniform(3);
    info->mField3c = StarManager()->FUN_00ba6630(0);
}

// ---------------------------------------------------------------- noun / city-data selection
struct IntVec {
    int* m_begin;      // +0x00
    int* m_end;        // +0x04
    int* m_capacity;   // +0x08
};

struct CityData;

struct SList {
    char pad0[0x3c];
    CityData** m_city;                             // +0x3c
    void SetElementAlignment(uint32_t alignment);  // 0x00fcc200
};

struct CityData {
    void SetKey(Vector3* pos);                     // 0x00ff0430
    void SetWidth(void* value);                    // 0x009879d0
};

struct Entity {
    char pad0[0x34];
    Iface f34;                                     // +0x34
    char pad38[0x108 - 0x38];
    int mField108;                                 // +0x108
};

struct GameDataVec {
    char pad0[4];
    Entity** m_begin;                              // +0x04
    Entity** m_end;                                // +0x08
};

struct cGameNounManager {
    GameDataVec* GetGameDataVector(void* f1, void* f2, void* f3, void* f4, int type); // 0x00b21340
};
cGameNounManager* NounManager();                   // 0x00b3d300

struct SelArg {
    IntVec*  FUN_00c71000();                       // 0x00c71000
    SList*   FUN_00c71030(int index);              // 0x00c71030
};

uint32_t FUN_00b6e050();                           // 0x00b6e050
void*    FUN_00b93550(CityData* data, SelArg* arg); // 0x00b93550

// @ 0x00b9a4d0
void FUN_00b9a4d0(SelArg* arg)
{
    IntVec* entries = arg->FUN_00c71000();
    int index = 0;
    GameDataVec* gameData = NounManager()->GetGameDataVector(
        (void*)0x00cd7d10, (void*)0x00d3d420, (void*)0x00ace070,
        (void*)0x00b1e500, 0x36be27e);

    Entity** it = gameData->m_begin;
    Entity** end = gameData->m_end;
    while (it != end && index < (entries->m_end - entries->m_begin)) {
        Entity* entity = *it;
        if (entity->mField108 == (int)0xd18d25cdu) {
            uint32_t alignment = FUN_00b6e050();
            SList* slist = arg->FUN_00c71030(index);
            slist->SetElementAlignment(alignment);

            SList* slist2 = arg->FUN_00c71030(index);
            CityData* data = *slist2->m_city;
            data->SetKey(entity->f34.v11());
            void* value = FUN_00b93550(data, arg);
            if (value != 0) {
                data->SetWidth(value);
                ++index;
            }
        }
        ++it;
    }
}

// ---------------------------------------------------------------- cleanup helper
struct CleanupRef {
    int m_ref;                                    // +0x04
    virtual void Release(int flags) { (void)flags; }
};

struct IntVec8 {
    int* m_begin;                                 // +0x00
    int* m_end;                                   // +0x04
    int* m_capacity;                              // +0x08
    void FUN_00b98ea0(int value);                 // 0x00b98ea0
};

struct CleanupHolder {
    int m_pad0;                                   // +0x00
    unsigned char m_flag4;                        // +0x04
    char m_pad5[0x3];
    IntVec8 m_vec;                                // +0x08
    int m_field14[2];                             // +0x14
    CleanupRef* m_ref1c;                          // +0x1c
    CleanupRef* m_ref20;                          // +0x20
    int m_field24[2];                             // +0x24
    void* m_ptr2c;                                // +0x2c
    void* m_ptr30;                                // +0x30
    void* m_ptr34;                                // +0x34
    int m_field38[6];                             // +0x38
    void* m_ptr50;                                // +0x50
    void* m_ptr54;                                // +0x54

    void FUN_00b9a630();                          // 0x00b9a630
};

// @ 0x00b9a630
void CleanupHolder::FUN_00b9a630()
{
    if (m_vec.m_end != m_vec.m_begin) {
        m_vec.m_end = m_vec.m_begin;
        m_vec.FUN_00b98ea0(0);
    } else {
        m_vec.m_end = m_vec.m_begin;
    }

    if (m_ref1c != 0) {
        CleanupRef* ref = m_ref1c;
        m_ref1c = 0;
        if (--ref->m_ref == 0) {
            ref->m_ref = 1;
            ref->Release(1);
        }
    }
    if (m_ref20 != 0) {
        CleanupRef* ref = m_ref20;
        m_ref20 = 0;
        if (--ref->m_ref == 0) {
            ref->m_ref = 1;
            ref->Release(1);
        }
    }

    m_ptr2c = 0;
    m_ptr30 = 0;
    operator_delete__(m_ptr34);
    m_ptr34 = 0;
    operator_delete__(m_ptr54);
    m_ptr54 = 0;
    m_ptr50 = 0;
    m_flag4 = 0;
}

// ---------------------------------------------------------------- species archetype lookup
extern int g_168890c;
extern int g_1688910;
extern unsigned char g_1688920;

struct SpeciesArch {
    char pad0[0x14];
    int m_field14;                                // +0x14
};

__declspec(noinline) int* FUN_00401090(int a, int b);                  // 0x00401090
__declspec(noinline) SpeciesArch* FUN_004e0050(int* key);              // 0x004e0050
__declspec(noinline) int* FUN_00401090(int* out, int* arch, int a, int b, int c);
__declspec(noinline) int FUN_004dfff0(int* out, int* arch, int a, int b, int c); // 0x004dfff0
__declspec(noinline) int FUN_00b96220(int* out, int a, int b, int* key, unsigned char c); // 0x00b96220
__declspec(noinline) void FUN_00b98230(int* out, int* key);            // 0x00b98230
__declspec(noinline) void FUN_004cd3c0(int value);                     // 0x004cd3c0

struct cObjectTemplateDB2
{
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
    virtual void v38(); virtual void v39(); virtual void v3a(); virtual void v3b();
    virtual void v3c(); virtual void v3d(); virtual void v3e(); virtual void v3f();
    virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
    virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
    virtual void v48(); virtual void v49(); virtual void v4a(); virtual void v4b();
    virtual void v4c(); virtual void v4d(); virtual void v4e(); virtual void v4f();
    virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53();
    virtual void v54(); virtual void v55(); virtual void v56(); virtual void v57();
    virtual void Notify(void* value, int count);  // +0x58
};
cObjectTemplateDB2* ObjectTemplateDB2();          // 0x0067cb40

// @ 0x00b9a750
int FUN_00b9a750(int arg1, int arg2, int arg3, int arg4, unsigned char* outFlag)
{
    int chosen = 0;
    unsigned char flag = 0;

    int* key = FUN_00401090(arg2, arg3);
    SpeciesArch* arch = FUN_004e0050(key);
    int archField = arch->m_field14;

    if (arg1 != 0) {
        int node[4];
        int lookupKey = arg1;
        if (FUN_00b96220(node, g_168890c, g_1688910, &lookupKey, g_1688920) &&
            node[0] != 0) {
            chosen = *(int*)((char*)node[0] + 8);
            flag = *(unsigned char*)((char*)node[0] + 0xc);
            if (chosen != 0)
                goto done;
        }
    }

    {
        int storage = 0;
        int* vec = 0;
        int key2[2];
        key2[0] = 0;
        key2[1] = 0;
        FUN_004cd3c0(1);
        int* archKey = FUN_00401090(arg2, arg3);
        SpeciesArch* arch2 = FUN_004e0050(archKey);
        if (arch2 != 0) {
            int* begin = (int*)&storage;
            int* end = begin;
            if (FUN_00401090(begin, (int*)arch2, 1, arg4, 0) &&
                FUN_004dfff0(begin, (int*)arch2, 1, arg4, 0) > 0) {
                chosen = *begin;
            } else {
                if (FUN_00401090(begin, (int*)arch2, 1, arg4, 1) &&
                    FUN_004dfff0(begin, (int*)arch2, 1, arg4, 1) > 0) {
                    flag = 1;
                    chosen = *begin;
                }
            }
            if (chosen != 0) {
                key2[0] = arg1;
                key2[1] = archField;
                int out[2];
                out[0] = chosen;
                out[1] = flag;
                FUN_00b98230(out, key2);
            }
        }
        (void)vec;
    }

done:
    if (outFlag != 0)
        *outFlag = flag;
    if (chosen != 0)
        ObjectTemplateDB2()->Notify((void*)(chosen + 0x504), 1);
    return chosen;
}

// Local models for the opaque helpers above, so the object links in the
// differential harness without pulling in unrelated engine objects.
int* FUN_00401090(int a, int b)
{
    static int key[2];
    key[0] = a;
    key[1] = b;
    return key;
}

SpeciesArch* FUN_004e0050(int* key)
{
    static SpeciesArch arch;
    arch.m_field14 = key ? key[0] : 0;
    return &arch;
}

int* FUN_00401090(int* out, int* arch, int a, int b, int c)
{
    (void)arch; (void)a; (void)b; (void)c;
    return out;
}

int FUN_004dfff0(int* out, int* arch, int a, int b, int c)
{
    (void)out; (void)arch; (void)a; (void)b; (void)c;
    return 0;
}

int FUN_00b96220(int* out, int a, int b, int* key, unsigned char c)
{
    (void)a; (void)b; (void)key; (void)c;
    out[0] = 0;
    return 0;
}

void FUN_00b98230(int* out, int* key)
{
    (void)out; (void)key;
}

void FUN_004cd3c0(int value)
{
    (void)value;
}

void IntVec8::FUN_00b98ea0(int value)
{
    (void)value;
}
