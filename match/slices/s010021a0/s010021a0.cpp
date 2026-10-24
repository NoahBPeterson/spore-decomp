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

struct Rec1021230 { char pad[0x44]; char f44; Vector3* FUN_00c8b360(); };   // 0x00c8b360

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

struct Viewer;
struct IQ { virtual void q0(); virtual void q1(); virtual void q2(); virtual void* Query(uint32_t id); };   // +0xc
struct IL2 {
    virtual void l0(); virtual void l1(); virtual void l2(); virtual void l3(); virtual void l4(); virtual void l5();
    virtual void l6(); virtual Viewer* GetViewer(); virtual void l8(); virtual void l9(); virtual void l10(); virtual void l11();
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

// ===========================================================================
// gold7-assigned helpers (s010021a0): posse / space-game / UI-space code.
// ===========================================================================

// ---- supporting declarations ----------------------------------------------
extern "C" void FUN_00c8bc10(uint32_t p);                                          // 0x00c8bc10
extern "C" void EA_IO_WriteUint32(void* dst, const void* src, int n, int flag);    // 0x0093aa70

struct IOConnect {                                                                 // reached from a serializable's +0x20
    virtual void a0(); virtual void a1(); virtual void a2();
    virtual void a3(); virtual void a4(); virtual void a5();
    virtual void* GetWriter();                                                     // vtable +0x18
};
struct SerContainer {                                                              // the object handed to Write/Read
    virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3();
    virtual void c4(); virtual void c5(); virtual void c6();
    virtual void Finish();                                                         // vtable +0x1c
    virtual IOConnect* GetConnect();                                               // vtable +0x20
};
struct PRec5 {                                                                     // 0x14-byte record with a vtable
    virtual void p0(); virtual void p1();
    virtual void Slot8(int v);                                                     // vtable +0x08
    virtual void p3();
    virtual void Slot10(SerContainer* c);                                          // vtable +0x10
    uint32_t pad14[4];                                                             // +0x04..+0x14
};
struct PRecList { PRec5* begin; PRec5* end; };

struct UISpace {                                                                   // SP::cSPUISpace
    virtual void Ifc0();                                                           // vtable +0x00
    virtual void Release4();                                                       // vtable +0x04
    UISpace* Construct();                                                          // 0x01070ba0 (constructor)
    void FUN_01071570();                                                           // 0x01071570
    void Init();                                                                   // 0x01073700
};
struct SimGame {                                                                   // owner of the UI space at +0x14
    char pad00[0x14];
    UISpace* mUISpace14;                                                           // +0x14
    char pad18[0x54 - 0x18];
    void* mField54;                                                                // +0x54
    char pad58[0x70 - 0x58];
    void* mField70;                                                                // +0x70
    char pad74[0xb4 - 0x74];
    void* mFieldb4; void* mFieldb8; void* mFieldbc; void* mFieldc0;                // +0xb4..+0xc0
};
struct SimTicker {                                                                 // SP::SimTicker
    virtual void k0(); virtual void k1(); virtual void k2(); virtual void k3(); virtual void k4();
    virtual void k5(); virtual void k6(); virtual void k7(); virtual void k8(); virtual void k9();
    virtual void k10(); virtual void k11(); virtual void k12(); virtual void k13(); virtual void k14();
    virtual void k15(); virtual void k16(); virtual void k17(); virtual void k18(); virtual void k19();
    virtual void k20();
    virtual void Slot54(void* v);                                                  // vtable +0x54
};
struct MgdObj {                                                                    // object returned by FUN_0067ddc0
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3(); virtual void m4();
    virtual void m5(); virtual void m6(); virtual void m7(); virtual void m8();
    virtual void Slot24();                                                         // vtable +0x24
    virtual void Slot28(void* v);                                                  // vtable +0x28
};
struct ResMan {                                                                    // EA::ResourceMan
    virtual void r0(); virtual void r1(); virtual void r2(); virtual void r3(); virtual void r4(); virtual void r5();
    virtual void r6(); virtual void r7(); virtual void r8(); virtual void r9(); virtual void r10(); virtual void r11();
    virtual void r12(); virtual void r13(); virtual void r14(); virtual void r15(); virtual void r16(); virtual void r17();
    virtual void r18(); virtual void r19(); virtual void r20(); virtual void r21(); virtual void r22(); virtual void r23();
    virtual void r24(); virtual void r25(); virtual void r26(); virtual void r27();
    virtual void Slot70(void* a, void* b);                                         // vtable +0x70
};
struct RefMgr {                                                                    // manager at 0x0167ea54
    virtual void f0(); virtual void f1(); virtual void f2(); virtual void f3(); virtual void f4(); virtual void f5();
    virtual void f6(); virtual void f7(); virtual void f8(); virtual void f9(); virtual void f10(); virtual void f11();
    virtual void Slot30(void* id);                                                 // vtable +0x30
};
struct CardPanel { void SetCardsVisibility(bool v); };                             // 0x00e14c10

extern "C" SimTicker* FUN_00b3d330();                                             // SP::SimTicker
extern "C" MgdObj*    FUN_0067ddc0();                                             // 0x0067ddc0
extern "C" ResMan*    FUN_0067dcd0();                                             // EA::ResourceMan::GetManager
extern "C" CardPanel* FUN_00b3d400();                                             // 0x00b3d400
extern "C" void FUN_00ff9390();                                                   // 0x00ff9390
extern "C" int FUN_01021080();                                                    // cSPLivingUniverse::GetUniverseContext
extern "C" void* operator_new(uint32_t size, const char* file, uint32_t line, uint32_t a, void* alloc, uint32_t tag);   // 0x00f473a0
extern RefMgr* g_0167ea54;                                                        // 0x0167ea54

struct SimSpace {                                                                  // ecx receiver of the serializer wrappers
    void OnSolarRollover(uint32_t p);
    bool Write(void* param_2);
    bool Read(void* param_2);
    char GonzagoWrite(void* io);                                                   // 0x00b5b610 cGonzagoSimulator::Write
    char GonzagoRead(void* io);                                                    // 0x00b5b650 cGonzagoSimulator::Read
};
struct Serializer {                                                                // cVarListSerializer
    Serializer(void* obj, uint32_t a, uint32_t b);                                 // 0x00692f90
    bool Serialize(void* io);                                                      // 0x00692900
    bool Read(void* io);                                                           // 0x00693e10
    uint32_t m[0x285];
};
extern "C" void EA_IO_ReadInt32(void* dst, void* src, int n, int flag);           // 0x0093a780

// ---------------------------------------------------------------------------
// 0x01002bf0  solar-rollover notification (thin forwarder).
// ---------------------------------------------------------------------------
// @ 0x01002bf0
void SimSpace::OnSolarRollover(uint32_t param_1)
{
    FUN_00c8bc10(param_1);
}

// ---------------------------------------------------------------------------
// 0x01002ea0  copy-forward 0x14-byte records, clearing each through vtable +0x08.
// ---------------------------------------------------------------------------
// @ 0x01002ea0
PRec5* FUN_01002ea0(PRec5* first, PRec5* last, PRec5* out)
{
    if (first != last) {
        do {
            first->Slot8(0);
            ++first;
            ++out;
        } while (first != last);
    }
    return out;
}

// ---------------------------------------------------------------------------
// 0x01002e30  write a record count, then serialize each 0x14-byte record.
// ---------------------------------------------------------------------------
// @ 0x01002e30
void FUN_01002e30(SerContainer* c, PRecList* list)
{
    int count = (int)(list->end - list->begin);
    IOConnect* conn = c->GetConnect();
    void* writer = conn->GetWriter();
    EA_IO_WriteUint32(writer, &count, 1, 0);
    PRec5* p = list->begin;
    PRec5* end = list->end;
    for (; p != end; ++p)
        p->Slot10(c);
    c->Finish();
}

// ---------------------------------------------------------------------------
// 0x01002ee0  post two manager events.
// ---------------------------------------------------------------------------
// @ 0x01002ee0
void FUN_01002ee0()
{
    struct Local { void* vftable; uint32_t tag; };
    ResMan* m = FUN_0067dcd0();
    Local a; a.vftable = (void*)0x13eb428; a.tag = 0x1c135da;
    m->Slot70(0, &a);
    Local b; b.vftable = (void*)0x13eb428; b.tag = 0xe6bce5;
    m->Slot70(0, &b);
}

// ---------------------------------------------------------------------------
// 0x01003070  shut down the UI space and notify the manager.
// ---------------------------------------------------------------------------
// @ 0x01003070
void __fastcall FUN_01003070(SimGame* self)
{
    UISpace* u = self->mUISpace14;
    if (u != 0) {
        u->FUN_01071570();
        UISpace* u2 = self->mUISpace14;
        if (u2 != 0) {
            self->mUISpace14 = 0;
            u2->Release4();
        }
    }
    MgdObj* m = FUN_0067ddc0();
    if (m != 0) {
        m->Slot28(0);
        m->Slot24();
    }
}

// ---------------------------------------------------------------------------
// 0x010030c0  lazily create the UI space and show the mission cards.
// ---------------------------------------------------------------------------
// @ 0x010030c0
void __fastcall FUN_010030c0(SimGame* self)
{
    if (self->mUISpace14 == 0) {
        UISpace* nw = (UISpace*)operator_new(0x6ac, "Simulator", 0, 0, 0, 0);
        UISpace* u = (nw != 0) ? nw->Construct() : 0;
        UISpace* old = self->mUISpace14;
        if (u != old) {
            if (u != 0)
                u->Ifc0();
            self->mUISpace14 = u;
            if (old != 0)
                old->Release4();
        }
        self->mUISpace14->Init();
        if (self->mField54 != 0)
            FUN_00ff9390();
    }
    MgdObj* m = FUN_0067ddc0();
    if (m != 0 && FUN_01021080() == 0) {
        m->Slot28((void*)1);
        m->Slot24();
    }
}

// ---------------------------------------------------------------------------
// 0x01003160  tick the six tracked objects, drop the UI space and pick the map.
// ---------------------------------------------------------------------------
// @ 0x01003160
void __fastcall FUN_01003160(SimGame* self)
{
    SimTicker* t = FUN_00b3d330();
    t->Slot54(self);
    t->Slot54(self->mField70);
    t->Slot54(self->mFieldb8);
    t->Slot54(self->mFieldc0);
    t->Slot54(self->mFieldb4);
    t->Slot54(self->mFieldbc);
    UISpace* u = self->mUISpace14;
    if (u != 0) {
        u->FUN_01071570();
        UISpace* u2 = self->mUISpace14;
        if (u2 != 0) {
            self->mUISpace14 = 0;
            u2->Release4();
        }
    }
    if (FUN_00b3d400() != 0)
        FUN_00b3d400()->SetCardsVisibility(false);
    g_0167ea54->Slot30((void*)FNV1_String8("Planet_Space", 0x811c9dc5, 1));
}

// ===========================================================================
// 0x01002c30 / 0x01002cc0  cSPSimulatorSpaceGame serialization wrappers.
// ===========================================================================
// @ 0x01002c30
bool SimSpace::Write(void* param_2)
{
    SerContainer* ctx = (SerContainer*)param_2;
    IOConnect* pl = ctx->GetConnect();
    uint32_t tag = 0xb03517bc;
    void* writer = pl->GetWriter();
    EA_IO_WriteUint32(writer, &tag, 1, 0);
    char ok = GonzagoWrite(param_2);
    Serializer ser((char*)this - 8, 0x15b6618, 0x1a80d26);
    if (ok != 0) {
        if (ser.Serialize(param_2) != 0)
            return true;
    }
    return false;
}

// @ 0x01002cc0
bool SimSpace::Read(void* param_2)
{
    SerContainer* ctx = (SerContainer*)param_2;
    IOConnect* pl = ctx->GetConnect();
    void* reader = pl->GetWriter();
    char tag[4];
    EA_IO_ReadInt32(reader, tag, 1, 0);
    char ok = GonzagoRead(param_2);
    Serializer ser((char*)this - 8, 0x15b6618, 0x1a80d26);
    if (ok != 0) {
        if (ser.Read(param_2) != 0)
            return true;
    }
    return false;
}

// ===========================================================================
// supporting types for 0x01002f30 / 0x010027b0
// ===========================================================================
extern float DAT_013fec70;                          // 1460.0f
extern float DAT_01477fc0;                          // 300.0f
extern float DAT_013ef54c;                          // 1.1f
extern float DAT_015b6254;                          // camera-distance scale

struct TerrainSphereFull { char pad[0x124c]; int mMaxMembers; };   // +0x124c

struct InvSub {                                     // sub-object embedded at inventory+0x508
    virtual void i0(); virtual void i1(); virtual void i2(); virtual void i3(); virtual void i4();
    virtual void i5(); virtual void i6(); virtual void i7(); virtual void i8(); virtual void i9();
    virtual void i10(); virtual void i11(); virtual void i12(); virtual void i13(); virtual void i14();
    virtual void i15(); virtual void i16(); virtual void i17(); virtual void i18(); virtual void i19();
    virtual void i20(); virtual void i21();
    virtual float Slot58();                         // vtable +0x58
};
struct InvView {                                    // SP::cSPSimulatorPlayerInventory (view)
    char pad0[0x508];
    InvSub sub508;                                  // +0x508
    char pad1[0x7f8 - 0x50c];
    float f7f8;                                     // +0x7f8
    float FUN_00c389f0(float v);                    // 0x00c389f0
};
struct UFOSimGame {                                 // cSPSimulatorSpaceGame
    InvView* GetPlayerInventory();                  // 0x00a1ad60
};
extern "C" UFOSimGame* FUN_00ffbe50();              // SP::GetUFOSimulator
extern "C" void FUN_00f924e0(float v);              // 0x00f924e0

struct SubC4 {                                      // object at GetUFOThing(...)+0xc4
    virtual void s0(); virtual void Release4();     // +0x04
    virtual void s2(); virtual void Slot0c(int v);  // +0x0c
};
struct B3d470b { char pad[0xc4]; SubC4* fC4; };     // view of FUN_00b3d470() result
struct TriggerMgr {                                 // SP::cTriggerMgr
    void PostTrigger(const char* name, int a, int b, int c, int d, int e);   // 0x00ae0930
};
extern "C" TriggerMgr* FUN_00b3d4d0();              // SP::GetTriggerMgr
extern "C" void FUN_00e39ab0(uint32_t a, int b, void* c, void* d, int e, int f, void* g, void* h);   // 0x00e39ab0

// ---------------------------------------------------------------------------
// 0x01002f30  "center of galaxy" trigger handler.
// ---------------------------------------------------------------------------
// @ 0x01002f30
void FUN_01002f30(void)
{
    TerrainSphere* sp = FUN_00b3d300()->GetCurrentTerrainSphere();
    if (!sp->FUN_00c772c0(0x681c28e)) {
        TerrainSphere* sp2 = FUN_00b3d300()->GetCurrentTerrainSphere();
        sp2->FUN_00c77bf0(0x681c28e);

        InvView* inv = FUN_00ffbe50()->GetPlayerInventory();
        if (inv != 0) {
            FUN_00f924e0(inv->sub508.Slot58());
            inv->FUN_00c389f0(inv->f7f8);
        }

        uint32_t loc[12] = {0};
        FUN_00e39ab0(0x57baffd3, 0, &loc[9], &loc[6], 0, 0, &loc[3], &loc[0]);

        B3d470b* b = (B3d470b*)FUN_00b3d470();
        if (b->fC4 != 0) {
            b->fC4->Slot0c(1);
            B3d470b* b2 = (B3d470b*)FUN_00b3d470();
            SubC4* p = b2->fC4;
            if (p != 0) {
                b2->fC4 = 0;
                p->Release4();
            }
        }
        FUN_00b3d4d0()->PostTrigger("SPG_CenterOfGalaxy", 1, 0, 0, 0, 0);
    }
}

// ===========================================================================
// 0x010027b0  AddPosseMember -- add an ally UFO to the player's posse.
// ===========================================================================
struct ListBuf {                                    // EASTL intrusive list root/node (player+0x70)
    ListBuf* mpNext;                                // +0x00
    ListBuf* mpPrev;                                // +0x04
    int      mValue;                                // +0x08
};
struct EmpireView {                                 // SP::cEmpire (view)
    char pad0[0x58];
    int  mArchetype;                                // +0x58
    char pad1[0x84 - 0x5c];
    int  mId;                                       // +0x84
    int  GetWeaponryLevel();                        // 0x00c317a0
    int  GetUFOKey();                               // 0x00c326b0
    void* GetPollinator(uint32_t prop, int key);    // 0x0067cb30
};
struct Pollinator { void UpdateProperty(uint32_t prop, int key); };   // 0x0060d860
struct EventLogT { void PostFeedbackEvent(int a, int b, int c, int d, int e, int f); };   // 0x00dd8640
extern "C" EventLogT* FUN_00b3d3e0();               // SP::EventLog

struct GUFOInner {                                  // sub-object at ufo+0x34
    virtual void i0(); virtual void i1(); virtual void i2(); virtual void i3(); virtual void i4();
    virtual void i5(); virtual void i6(); virtual void i7(); virtual void i8(); virtual void i9();
    virtual void i10();
    virtual void* Slot2c(float a, float b);         // vtable +0x2c
};
struct GameDataUFO {                                // SP::cSPGameDataUFO
    virtual void u0(); virtual void u1(); virtual void u2(); virtual void u3(); virtual void u4();
    virtual void u5(); virtual void u6(); virtual void u7(); virtual void u8(); virtual void u9();
    virtual void u10(); virtual void u11(); virtual void u12(); virtual void u13(); virtual void u14();
    virtual void u15(); virtual void u16(); virtual void u17(); virtual void u18();
    virtual int GetEmpireId();                      // vtable +0x4c
    char pad2[0x34 - 0x04];
    GUFOInner inner34;                              // +0x34
    void SetDestination(Vector3* p);                // 0x00c3bfe0
    void PopToDestination();                        // 0x00c37e60
    void FUN_00c3aa40(Vector3* dir, void* orient);  // 0x00c3aa40
};
struct PlanetModelT {                               // SP::cPlanetModel
    void MakeRandomWorldPosition(Vector3* out, void* a);   // 0x00b81780
    void* BuildSurfaceOrientation(void* out, Vector3* p);  // 0x00b7f190
};
extern "C" PlanetModelT* FUN_00b3d350();            // SP::PlanetModel
struct PlanetObj {                                  // SP::cSPLivingUniverse active planet
    virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4();
    virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9();
    virtual void p10();
    virtual Vector3* GetPos();                      // vtable +0x2c
};
extern "C" PlanetObj* FUN_01021260();               // SP::cSPLivingUniverse::GetActivePlanet
struct Viewer {                                     // SP::cViewer
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    void GetCameraLocationInfo(int a, Vector3* out, int b, int c);   // 0x007c3d30
};
struct AT {                                         // EA::Audio::SystemAT
    virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3();
    virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7();
    virtual void* Slot20();                         // vtable +0x20
};
extern "C" AT* GetSystemAT();                       // EA::Audio::GetSystemAT
struct UIFinder { void FUN_0106b500(); };           // 0x0106b500
extern "C" UIFinder* FUN_010666a0(void* ufo);       // 0x010666a0
extern "C" GameDataUFO* AddHighLODAlliedUFO(EmpireView* emp, int a, int count);   // 0x0102b1d0
extern "C" void PositionPosseMembers();             // 0x0102be20
extern "C" void KillSetiEffects(uint32_t sound, void* at);   // 0x00435ed0

struct PlayerUFO {                                  // SP::cSPSimulatorPlayerUFO
    char pad[0x70];
    ListBuf mPosse;                                 // +0x70
    void  FUN_01001700(int id, int b);              // 0x01001700
    void* AddPosseMember(int param_2, char param_3);   // 0x010027b0
};

// @ 0x010027b0
void* PlayerUFO::AddPosseMember(int param_2, char param_3)
{
    TerrainSphereFull* ts = (TerrainSphereFull*)FUN_00b3d300()->GetCurrentTerrainSphere();
    int maxMembers = ts->mMaxMembers;
    if (maxMembers == 0)
        return 0;

    int playerEmpireId = FUN_01021090();

    int count = 0;
    for (ListBuf* n = mPosse.mpNext; n != &mPosse; n = n->mpNext)
        ++count;

    bool doAdd = true;
    EmpireView* chosen = 0;
    if (count > 0 && maxMembers <= count) {
        doAdd = false;
        for (ListBuf* n = mPosse.mpNext; n != &mPosse; n = n->mpNext) {
            EmpireView* emp = (EmpireView*)FUN_00b3d2a0()->GetEmpireByID(n->mValue);
            if (emp != 0 && emp->mId != playerEmpireId) {
                if (chosen != 0) {
                    int empLvl = emp->GetWeaponryLevel();
                    int chosenLvl = chosen->GetWeaponryLevel();
                    if (chosenLvl <= empLvl)
                        continue;
                }
                chosen = emp;
            }
        }
        if (chosen != 0) {
            doAdd = true;
            FUN_01001700(chosen->mId, 0);
            if (param_3 != 0)
                FUN_00b3d3e0()->PostFeedbackEvent(0x36d582f0, 0x131a9f54, 0, 0, 1, 0);
        }
    }

    GameDataUFO* ufo = 0;
    if (doAdd) {
        ListBuf* node = (ListBuf*)operator_new(0xc, "Simulator", 0, 0, (void*)0x13ebb38, 0xd1);
        node->mValue = param_2;
        node->mpNext = mPosse.mpNext;
        node->mpPrev = mPosse.mpPrev;
        mPosse.mpPrev->mpNext = node;
        mPosse.mpPrev = node;

        EmpireView* emp2 = (EmpireView*)FUN_00b3d2a0()->GetEmpireByID(param_2);
        int cnt2 = 0;
        for (ListBuf* n = mPosse.mpNext; n != &mPosse; n = n->mpNext)
            ++cnt2;
        ufo = AddHighLODAlliedUFO(emp2, 0, cnt2);
        PositionPosseMembers();
        if (param_3 != 0 && param_2 != playerEmpireId)
            FUN_00b3d3e0()->PostFeedbackEvent(0xa0c7000a, 0x131a9f54, 0, 0, 1, 0);

        if (FUN_01021090() != ufo->GetEmpireId()) {
            int key = emp2->GetUFOKey();
            Pollinator* pol = (Pollinator*)emp2->GetPollinator(0x27ef0ff0, key);
            pol->UpdateProperty(0x27ef0ff0, key);
        }

        int ctx = FUN_01021080();
        if (ctx == 0) {
            PlanetModelT* model = FUN_00b3d350();
            void* r = ufo->inner34.Slot2c(DAT_01477fc0, DAT_013fec70);
            Vector3 p0;
            model->MakeRandomWorldPosition(&p0, r);
            Vector3 scr;
            scr.x = p0.x * DAT_013ef54c;
            scr.y = p0.y * DAT_013ef54c;
            scr.z = p0.z * DAT_013ef54c;
            uint32_t orient[4];
            void* o = model->BuildSurfaceOrientation(orient, &p0);
            ufo->FUN_00c3aa40(&scr, o);
        } else if (ctx == 1) {
            Viewer* viewer = FUN_0067dd10()->GetL2()->GetViewer();
            Vector3 cam;
            viewer->GetCameraLocationInfo(0, &cam, 0, 0);
            PlanetObj* act = FUN_01021260();
            Vector3 scr;
            scr.x = cam.x * DAT_015b6254;
            scr.y = cam.y * DAT_015b6254;
            scr.z = cam.z * DAT_015b6254;
            Vector3* base = act->GetPos();
            Vector3 dst;
            dst.x = base->x + scr.x;
            dst.y = base->y + scr.y;
            dst.z = base->z + scr.z;
            ufo->SetDestination(&dst);
            ufo->PopToDestination();
        } else if (ctx == 2) {
            Rec1021230* r2 = FUN_01021230();
            ufo->SetDestination(r2->FUN_00c8b360());
            ufo->PopToDestination();
        }

        if (emp2 != 0) {
            uint32_t sound = 0;
            switch (emp2->mArchetype) {
            case 0: sound = 0x99422df0; break;
            case 1: sound = 0xd3feb879; break;
            case 2: sound = 0x350cfd88; break;
            case 3: sound = 0x51d62aab; break;
            case 4: sound = 0xf628f0e1; break;
            case 5: sound = 0x8b050578; break;
            case 6: sound = 0xdb4ad9f1; break;
            case 7: sound = 0xb07352e1; break;
            case 8: sound = 0x2b67bd78; break;
            default:
                if ((void*)FUN_01021300() == (void*)emp2)
                    sound = 0xb261f252;
                break;
            }
            AT* at = GetSystemAT();
            KillSetiEffects(sound, at != 0 ? at->Slot20() : 0);
        }
        FUN_010666a0(ufo)->FUN_0106b500();
    }
    return ufo;
}
