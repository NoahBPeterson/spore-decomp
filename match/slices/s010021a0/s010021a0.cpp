// s010021a0 -- "go to star" action: charges the player's empire for contacting `target`, plays the
// reticle goto-screen effect, rebuilds the star map filter, and raises awareness of nearby empires.
// (PDB candidate name from the card: SP::cSPMission::RefreshStarMapEffect -- not confirmed.)
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};

struct IVisualEffect {
    virtual void v0();
    virtual void Release();            // +4
    virtual void v2(int);              // +8
    virtual void v3(int);              // +0xc
    virtual void v4();
    virtual void v5();
    virtual void v6(void*);            // +0x18
};
struct EffectRef {
    IVisualEffect* p;
    IVisualEffect** AsPPTypeParam();   // 0x00a16f40
};
struct EffectsManagerT {
    virtual void e0(); virtual void e1(); virtual void e2(); virtual void e3(); virtual void e4();
    virtual void e5(); virtual void e6(); virtual void e7(); virtual void e8(); virtual void e9();
    virtual void e10();
    virtual bool GetEffect(uint32_t id, int arg, IVisualEffect** out);   // +0x2c
};

struct XformMsg {
    uint32_t d[14];
    XformMsg();   // 0x00434040
    void SetPos(Vector3* p);           // 0x00571d40
};

struct Star {
    char pad[0x28];
    int kind;
    bool FUN_00b8d970();               // 0x00b8d970
};
struct StarVec {
    Star** begin;
    Star** end;
    int size() const { return end - begin; }
};

struct Civ {
    Vector3* GetPos();                 // 0x005c65e0
    int GetAvatar();                   // 0x00b1fdb0
    int FUN_00bb9ae0();                // 0x00bb9ae0
    StarVec* FUN_00bba790();           // 0x00bba790
};

struct Empire {
    int FUN_00c30cb0();                // 0x00c30cb0
    void FUN_00c31a00(int);            // 0x00c31a00
};
struct StarEmpire {
    char pad[0x84];
    int f84;
    bool FUN_00c30910();               // 0x00c30910
};

struct IRel {
    virtual void r0(); virtual void r1(); virtual void r2(); virtual void r3(); virtual void r4(); virtual void r5();
    virtual void r6(); virtual void r7(); virtual void r8(); virtual void r9(); virtual void r10(); virtual void r11();
    virtual void r12(); virtual void r13(); virtual void r14(); virtual void r15(); virtual void r16(); virtual void r17();
    virtual void r18(); virtual void r19(); virtual void r20(); virtual void r21(); virtual void r22(); virtual void r23();
    virtual void r24(); virtual void r25(); virtual void r26(); virtual void r27(); virtual void r28(); virtual void r29();
    virtual void r30(); virtual void r31(); virtual void r32(); virtual void r33(); virtual void r34(); virtual void r35();
    virtual void r36(); virtual void r37(); virtual void r38(); virtual void r39(); virtual void r40(); virtual void r41();
    virtual void r42(); virtual void r43(); virtual void r44(); virtual void r45(); virtual void r46(); virtual void r47();
    virtual void Free();               // +0xc0
};
struct PlanetRef {
    IRel* p;
    IRel** AsPPTypeParam();            // 0x00ae9790
};

struct StarMgr {
    StarEmpire* GetEmpireByID(int id);          // 0x00ba9370
    void FUN_00bb57b0(Civ* c, int z);           // 0x00bb57b0
    void GetOrActivatePlanet(Star* s, IRel** out);   // 0x00bb59b0
    int FUN_00885c90();                         // 0x00885c90
};

struct RelMgr {
    float RecordEvent(int a, int b, uint32_t ev, float amount);   // 0x00d06240
};

struct SimUniverse {
    char pad0[0x150]; float grobCap;
    char pad1[0x174 - 0x154]; float empireCap;
    void AdjustAwareness(int id, int mode);     // 0x01014a80
    int FUN_010107b0(int id);                   // 0x010107b0
};
extern SimUniverse* gSimUniverse;               // 0x016dc798

struct TerrainSphere {
    bool FUN_00c772c0(uint32_t id);             // 0x00c772c0
    void FUN_00c77bf0(uint32_t id);             // 0x00c77bf0
    void FUN_00c7ba90(Civ* c);                  // 0x00c7ba90
};
struct NounMgr {
    TerrainSphere* GetCurrentTerrainSphere();   // 0x00f67d90
};

struct GameTime { char pad[0x48]; uint8_t pauseBits; };

struct IObj3 { virtual void s0(); virtual void s1(); virtual void s2(); virtual void Do(int v); };
struct B3d470 {
    char pad[0x34];
    IObj3* f34;
    void FUN_01036940(Vector3 v);               // 0x01036940
};
struct B3d360 {
    void FUN_00b7dec0();                        // 0x00b7dec0
    void FUN_00b7daf0(IRel* p);                 // 0x00b7daf0
};

struct Rec1021230 { char pad[0x44]; char f44; };

struct Owner {
    char pad0[0x508];
    struct Sub508 {
        virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5();
        virtual void Apply(float v, int a, int b, void* c, int d);   // +0x18
    } sub508;
    char pad1[0x74c - 0x50c];
    char b74c;
    char pad2[0x7f4 - 0x74d];
    float f7f4;
    float FUN_00c389f0(float v);                // 0x00c389f0
    void FUN_00c3c360(Civ* c);                  // 0x00c3c360
};

struct Tuning {
    float GetTravelFuelCost();                  // 0x0102feb0
    float FUN_0102fe60();                       // 0x0102fe60
};

struct StarMap {
    void FilterHelperRebuildAll();   // 0x01048ce0
};

struct MsgServer {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3(); virtual void m4(); virtual void m5();
    virtual void Post(uint32_t id, int a, int b, int c);   // +0x18
};

struct Holder { char pad[0x68]; Civ** begin; Civ** end; };
struct Tribe { void FUN_00fe5430(int a, int b); };      // 0x00fe5430
struct SpaceGame {
    char pad[0x30];
    Holder* f30;
    Tribe* GetPlayerTribe();                    // 0x00bfc5f0
};

struct IQ { virtual void q0(); virtual void q1(); virtual void q2(); virtual void* Query(uint32_t id); };   // +0xc
struct IL2 {
    virtual void l0(); virtual void l1(); virtual void l2(); virtual void l3(); virtual void l4(); virtual void l5();
    virtual void l6(); virtual void l7(); virtual void l8(); virtual void l9(); virtual void l10(); virtual void l11();
    virtual void l12(); virtual void l13(); virtual void l14(); virtual void l15();
    virtual IQ* GetNode(uint32_t id);           // +0x40
};
struct IL1 {
    virtual void k0(); virtual void k1(); virtual void k2(); virtual void k3(); virtual void k4(); virtual void k5();
    virtual void k6(); virtual void k7(); virtual void k8(); virtual void k9(); virtual void k10(); virtual void k11();
    virtual void k12(); virtual void k13(); virtual void k14(); virtual void k15(); virtual void k16(); virtual void k17();
    virtual void k18(); virtual void k19();
    virtual IL2* GetChild();                    // +0x50
};
struct AppT { virtual void ap0(); };
struct AppObj {   // SP::App(): vtable slot 20 (+0x50)
    virtual void x0(); virtual void x1(); virtual void x2(); virtual void x3(); virtual void x4(); virtual void x5();
    virtual void x6(); virtual void x7(); virtual void x8(); virtual void x9(); virtual void x10(); virtual void x11();
    virtual void x12(); virtual void x13(); virtual void x14(); virtual void x15(); virtual void x16(); virtual void x17();
    virtual void x18(); virtual void x19();
    virtual IL2* GetL2();                       // +0x50
};

struct TestSys { char pad[0x70]; void* listNext; };
extern TestSys* g_015fd928;                     // 0x015fd928

// ---- eastl set<uint> as a stack local -----------------------------------------------------------------
struct SetNode {
    SetNode* right;
    SetNode* left;
    SetNode* parent;
    uint32_t color;
    uint32_t value;
};
struct SetIter {
    SetNode* node;
    SetIter() {}
    SetIter(const SetIter& o) : node(o.node) {}
};
struct InsertRet {
    SetIter it;
    bool inserted;
    InsertRet() {}
};
struct Tag {};
struct UIntSet {
    uint32_t alloc;
    SetNode* aRight;
    SetNode* aLeft;
    SetNode* aParent;
    uint8_t aColor;
    uint32_t size;
    UIntSet() { aRight = (SetNode*)&aRight; aLeft = (SetNode*)&aRight; aParent = 0; aColor = 0; size = 0; }
    SetIter find(const uint32_t& key);                          // 0x00e5c780
    InsertRet DoInsertValue(const uint32_t& key, Tag t);        // 0x00a17a70
    void DoNukeSubtree(SetNode* n);                             // 0x009a9600
    SetNode* end() { return (SetNode*)&aRight; }
    SetNode* begin() { return aLeft; }
    ~UIntSet();
};
extern "C" void operator_delete__(void* p);   // 0x00f47380
inline UIntSet::~UIntSet()
{
    SetNode* n = aParent;
    while (n) {
        DoNukeSubtree(n->right);
        SetNode* l = n->left;
        operator_delete__(n);
        n = l;
    }
}

// ---- free functions ------------------------------------------------------------------------------------
extern "C" {
GameTime* FUN_00b3d380();
Civ* FUN_01021240();
Empire* FUN_01021300();
void FUN_01043500(uint32_t id, int z);
NounMgr* FUN_00b3d300();
int FUN_01021090();
StarMgr* FUN_00b3d2a0();
RelMgr* FUN_00b3d2c0();
bool FUN_00c8bb00(Civ* c);
Rec1021230* FUN_01021230();
B3d470* FUN_00b3d470();
void FUN_010219b0(Civ* c, int z);
uint32_t FNV1_String8(const char* s, uint32_t seed, int n);   // 0x00932e80
void FUN_01041c50(const char* s, uint32_t id, int z);
StarMap* FUN_01046fc0();
Tuning* FUN_0102f810();
B3d360* FUN_00b3d360();
float FUN_010434e0(Vector3* a, Vector3* b);
SetNode* RBTreeIncrement(SetNode* n);   // 0x00921580
EffectsManagerT* FUN_0067ddd0();
SpaceGame* FUN_01002bd0();
MsgServer* FUN_0067dcc0();
AppObj* FUN_0067dd10();
void FUN_01017000(void* p);
}

struct Cls {
    char pad0[0x40];
    Owner* owner;                  // +0x40
    EffectRef eff;                 // +0x44

    int FUN_00ffc4e0(Civ* a, Civ* b);       // 0x00ffc4e0
    bool FUN_00ffdbb0();                    // 0x00ffdbb0
    void FUN_01001360(Vector3* p);          // 0x01001360
    void Run(Civ* target);
};

// @ 0x010021a0
void Cls::Run(Civ* target)
{
    if (!target)
        return;
    if (FUN_00b3d380()->pauseBits & 1)
        return;
    Civ* cur = FUN_01021240();
    if (cur == target)
        return;
    bool flag = (owner->b74c == 0);
    int cost = FUN_00ffc4e0(cur, target);
    Empire* emp = FUN_01021300();
    if (!emp)
        return;
    if (!g_015fd928 || g_015fd928->listNext == &g_015fd928->listNext) {
        if (cost > emp->FUN_00c30cb0()) {
            FUN_01043500(0x3e7e341, 0);
            return;
        }
    }
    FUN_01043500(0x3e7e349, 0);
    emp->FUN_00c31a00(-cost);
    TerrainSphere* sphere = FUN_00b3d300()->GetCurrentTerrainSphere();
    if (sphere->FUN_00c772c0(0x5f1f0bc))
        sphere->FUN_00c77bf0(0x5f1f0ca);
    int playerId = FUN_01021090();
    if (cur->FUN_00bb9ae0() == 5 && cur->GetAvatar() != playerId) {
        StarEmpire* se = FUN_00b3d2a0()->GetEmpireByID(cur->GetAvatar());
        if (se && !se->FUN_00c30910() && gSimUniverse->FUN_010107b0(se->f84) == 3)
            FUN_00b3d2c0()->RecordEvent(cur->GetAvatar(), playerId, 0x5b942d0, 1.0f);
    }
    sphere = FUN_00b3d300()->GetCurrentTerrainSphere();
    if (FUN_00c8bb00(cur))
        sphere->FUN_00c7ba90(cur);
    FUN_01021230()->f44 = 1;
    IObj3** pf34 = &FUN_00b3d470()->f34;
    (*pf34)->Do(0);
    FUN_010219b0(target, 0);
    IVisualEffect* e0 = eff.p;
    if (e0)
        e0->v3(1);
    uint32_t hash = FNV1_String8("UI_common_reticle_goto_screen", 0x811c9dc5, 1);
    EffectsManagerT* em = FUN_0067ddd0();
    if (em->GetEffect(hash, 0, eff.AsPPTypeParam())) {
        XformMsg msg;
        msg.SetPos(target->GetPos());
        eff.p->v6(&msg);
        eff.p->v2(0);
    }
    Vector3 pos(*target->GetPos());
    FUN_00b3d470()->FUN_01036940(pos);
    if (flag && FUN_00ffdbb0())
        FUN_01041c50("SPG_TravelNearCore", 0x5f776d6, 0);
    FUN_01001360(target->GetPos());
    FUN_01046fc0()->FilterHelperRebuildAll();
    Owner* o = owner;
    if (o->f7f4 > 0.0f) {
        o->FUN_00c389f0(-FUN_0102f810()->GetTravelFuelCost());
    } else {
        o->sub508.Apply(FUN_0102f810()->FUN_0102fe60(), -1, 5, (void*)0x16dba18, 0);
    }
    owner->FUN_00c3c360(target);
    FUN_00b3d2a0()->FUN_00bb57b0(target, 0);
    FUN_00b3d360()->FUN_00b7dec0();
    StarVec* stars = target->FUN_00bba790();
    for (int i = 0; i < stars->size(); i++) {
        Star* s = stars->begin[i];
        if (s->kind != 0 && s->kind != 1 && !s->FUN_00b8d970()) {
            PlanetRef ref;
            ref.p = 0;
            FUN_00b3d2a0()->GetOrActivatePlanet(s, ref.AsPPTypeParam());
            FUN_00b3d360()->FUN_00b7daf0(ref.p);
            if (ref.p)
                ref.p->Free();
        }
    }
    int myAvatar = target->GetAvatar();
    int pid = FUN_01021090();
    int stmp = FUN_00b3d2a0()->FUN_00885c90();
    SimUniverse* univ = gSimUniverse;
    float grobCap = univ->grobCap;
    float empireCap = univ->empireCap;
    UIntSet set;
    {
        Holder* h = FUN_01002bd0()->f30;
        for (Civ** it = h->begin; it != h->end; ++it) {
            Civ* c = *it;
            int av = c->GetAvatar();
            if (av != myAvatar && av != pid) {
                uint32_t key = av;
                if (set.find(key).node == set.end()) {
                    float d = FUN_010434e0(c->GetPos(), target->GetPos());
                    float cap = (av == stmp) ? grobCap : empireCap;
                    if (cap >= d)
                        set.DoInsertValue(key, Tag());
                }
            }
        }
    }
    for (SetNode* n = set.begin(); n != set.end(); n = RBTreeIncrement(n))
        univ->AdjustAwareness(n->value, 4);
    if (myAvatar != -1 && myAvatar != pid)
        univ->AdjustAwareness(myAvatar, 2);
    FUN_0067dcc0()->Post(0x55bd8f7, 0, 0, 0);
    FUN_0067dcc0()->Post(0x6174b67, 0, 0, 0);
    if (FUN_01002bd0()) {
        if (FUN_01002bd0()->GetPlayerTribe())
            FUN_01002bd0()->GetPlayerTribe()->FUN_00fe5430(0x16, 1);
    }
    IQ* q = FUN_0067dd10()->GetL2()->GetNode(0x1103192);
    if (q) {
        void* r = q->Query(0x303154cc);
        if (r)
            FUN_01017000(r);
    }
}
