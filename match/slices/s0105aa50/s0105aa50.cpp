// s0105aa50 : tool StartTool (drop cargo): places the selected inventory item into the world
typedef unsigned int uint32_t;

#define P(n) virtual void pad##n();
#define P4(a) P(a##0) P(a##1) P(a##2) P(a##3)
#define P8(a) P4(a##x) P4(a##y)
#define PA(a, n) P(a##n)

struct Vec3 { float x, y, z; };

struct ActionTarget {
    uint32_t b[12];
    ActionTarget* Init(const Vec3* pos, const Vec3* dir);  // 0x00ad79d0
    void Destroy();                                        // 0x00ad7ad0
};

// COM-like handle (Release is slot 2)
struct Unk {
    virtual void p0();
    virtual void p1();
    virtual void Release();
};

// cast results: cargo-info interfaces; slot 6 yields the species id
struct Cargo {
    P4(c0) P4(c1)
};
struct CargoA {
    P(a0) P(a1) P(a2) P(a3) P(a4) P(a5)
    virtual int GetN();
};

struct Item {
    P(i0) P(i1) P(i2) P(i3) P(i4) P(i5)
    virtual int GetN();                // +0x18
    char pad4[0x10 - 4];
    int f10;
    int type;
    char pad18[0x20 - 0x18];
    int f20;
};

struct Inv {
    P4(a) P4(b) P4(c) P4(d) P4(e) P4(f)
    P(g0)
    virtual int Find(int type, int n);                        // +0x64 (slot 25)
    P(h0) P(h1) P(h2) P(h3) P(h4)
    virtual bool Take(int handle, void** out, int count);     // +0x7c (slot 31)
    Item* Current();                                          // 0x00ff3f10
    void Refresh();                                           // 0x00ff3e80
};

struct YSub {
    P4(a) P4(b) P4(c) P4(d) P4(e) P(f0) P(f1)
    virtual float Value();                                    // +0x58 (slot 22)
    void SetValue(float v);                                   // 0x00f924e0
};

struct Profile;

struct Y {
    P(a0) P(a1) P(a2) P(a3) P(a4) P(a5) P(a6) P(a7) P(a8) P(a9) P(aa) P(ab) P(ac) P(ad) P(ae) P(af) P(ag) P(ah)
    virtual void Apply(int x);                                // +0x48 (slot 18)
    P8(b) P8(c) P8(d) P8(e) P4(f) P(g0) P(g1) P(g2)
    virtual void Place(int a, int b, int c, const Vec3* p);   // +0xe8 (slot 58)
    char pad4[0x5a8 - 4];
    YSub sub;                                                 // +0x5a8
    char pad5[0xb4c - 0x5a8 - 4];
    char* extra;                                              // +0xb4c
    void ApplyProfile(Profile* p);                            // 0x00c222f0
};

struct Slot {
    void* v;
    void* ptrValue() { return v; }
    void Assign(void* v);                                     // 0x00b5f950 (AutoRefCount operator=)
};

struct Abducted {
    P8(a) P8(b)
    virtual void Attach(void* p);                             // +0x40 (slot 16)
    void SetFlag(int v);                                      // 0x01030dd0
};

struct Beh {
    P8(a)
    virtual void* Find(int id, int a, void* target, int b);   // +0x20 (slot 8)
    P(b0) P(b1) P(b2) P(b3) P(b4)
    virtual void Register(void* p);                           // +0x38 (slot 14)
};

struct Beam {
    char pad[0x11c];
    void GetEndPoints(Vec3* a, Vec3* b);                      // 0x00cb8ba0
};

struct Tool {
    char pad[0x124];
    Beam* beam;
    char pad2[0x12c - 0x128];
    Slot held;
};

struct M1 { void Start(uint32_t id, ActionTarget* t, int z); };           // 0x00ae09b0
struct M2 {
    void* UpdateVignettes(const void* data);                              // 0x00ad11f0
    Y* Make(Profile* p, Vec3* pos);                                       // 0x00ad0510
};
struct Plant;
struct M3 {
    Plant* MakePlant(Vec3 pos, int n100, Profile* prof, int n, int z);    // 0x00b2b430
    void Finish(Plant* p, int one);                                       // 0x00b2c980
};

struct PlantX { P8(a) P8(b) P8(c) P8(d) P8(e) P4(f) P(g0) P(g1) P(g2) P(g3) P(g4) virtual void Set(int n); };  // slot 45
struct PlantSub {
    P8(a) P8(b) P8(c) P8(d) P8(e) P(f0) P(f1) P(f2)
    virtual int Dummy43(int a);                                           // +0xac (slot 43)
    virtual PlantX* GetX();                                               // +0xb0 (slot 44)
};
struct Plant {
    char pad0[0x34];
    PlantSub sub;                                                         // +0x34
};

struct ArtSub {
    P8(a) P4(b) P(c0) P(c1)
    virtual void SetPos(Vec3* p);                                         // +0x38 (slot 14)
};
struct Artifact {
    char pad0[0x34];
    ArtSub sub;                                                           // +0x34
    char pad1[0x638 - 0x34 - 4];
    int f638;
    void Init1();                                                         // 0x00c69090
    void Set(int type, int n, int f10, int one);                          // 0x00c74d30
    int Dir(Vec3* out);                                                   // 0x00ad2620
};
struct GameDataVec;
struct Nm {
    Artifact* Get();                                                      // 0x0103a080
    GameDataVec* GetGameDataVector(int a, int b, int c, int d, void* e);  // 0x00b21340
};
struct Empire;
struct Planet {
    char pad[0x13c];
    int f13c;
    bool Fb7e3e0(Vec3* p);                                               // 0x00b7e3e0
    Empire* F00c71e30();                                                 // 0x00c71e30
};
struct Empire { char pad[0x84]; int f84; };

struct ProfSrc {
    Profile* GetProfile();                                                // 0x004df550
    Profile* GetPlantProfile();                                           // 0x004df440
};
struct Game {
    Inv* GetPlayerInventory();                // 0x00a1ad60
    void* f5180(int n);                       // 0x01005180
    void* GetAvatar();                        // 0x00b1fdb0
    void* F1003480();                         // 0x01003480
};

bool __stdcall Base(Tool* self, Vec3* a2, int a3);                        // 0x01059f20
Game* SpaceGameGet();                                                     // 0x01002bd0
M1* GetM1();                                                              // 0x00b3d4d0
M2* GetM2();                                                              // 0x00b3d480
M3* GetM3();                                                              // 0x00b3d3b0
Beh* BehaviorManager();                                                   // 0x00b3d260
Nm* NounManager();                                                        // 0x00b3d300
Planet* GetActivePlanet();                                                // 0x01021260
Y* FindY(void* v);                                                        // 0x00c0c380
Vec3* normalized_safe(Vec3* out, const Vec3* in);                         // 0x00449c20
Cargo* CastAnimal(void** p);                                              // 0x010536e0
Cargo* CastPlant(void** p);                                               // 0x01053700
Abducted* CastAbducted(void* i);                                          // 0x010536a0
void* CastPlantUnk(Plant* p);                                             // 0x007fe970
ProfSrc* __stdcall GetSetting9(int n);                                    // 0x00401090
void Spawn(int pf, int type, int dirv, int x, int one, Vec3 pos, int z);  // 0x00c731a0
extern int g_behId;                                                       // 0x016df2f4

static inline void* TargetOf(Beam* b) { return b ? (char*)b + 0x11c : 0; }

bool __stdcall StartTool(Tool* self, Vec3* a2, int a3)
{
    if (!Base(self, a2, a3)) return true;
    ActionTarget at;
    Vec3 dummy;
    at.Init(a2, &dummy);
    GetM1()->Start(0x5dce504a, &at, 0);
    Inv* inv = SpaceGameGet()->GetPlayerInventory();
    if (!inv) goto done;
    {
        Item* item = inv->Current();
        if (!item) {
            at.Destroy();
            return false;
        }
        if (item->type == 3) goto done;
        int handle = inv->Find(item->type, item->GetN());
        int t = item->type;
        bool bPlant = t == 0, bAnimal = t == 1, bAbd = t == 6, b4 = t == 4, b5 = t == 5;
        Unk* held = 0;
        int count;
        if (bPlant || bAnimal || bAbd) {
            if (!b4) count = 1; else count = item->f10;
        } else if (b4) {
            count = item->f10;
        } else if (b5) {
            count = 1;
        } else {
            goto done;
        }
        inv->Take(handle, (void**)&held, count);
        if (self->beam) {
            Vec3 start, end, d, dir;
            self->beam->GetEndPoints(&start, &end);
            d.x = end.x - start.x;
            d.y = end.y - start.y;
            d.z = end.z - start.z;
            Vec3* n = normalized_safe(&dir, &d);
            Vec3 pos;
            pos.x = n->x + start.x;
            pos.y = n->y + start.y;
            pos.z = n->z + start.z;
            if (bAbd) {
                M2* m2 = GetM2();
                if (m2) {
                    Y* y = FindY(m2->UpdateVignettes((const void*)0x018eb4b7));
                    if (y) {
                        y->Place(0, 0, 1, a2);
                        y->Apply(item->f20);
                        Cargo* ac = CastAnimal((void**)&held);
                        if (ac) {
                            Profile* pr = GetSetting9(((CargoA*)ac)->GetN())->GetProfile();
                            if (pr) y->ApplyProfile(pr);
                        }
                        YSub* sub = &y->sub;
                        sub->SetValue(sub->Value());
                        self->held.Assign(y);
                        BehaviorManager()->Register((char*)y + 0x58);
                        void* tgt = TargetOf(self->beam);
                        Abducted* ab = CastAbducted(BehaviorManager()->Find(g_behId, 0, tgt, 0));
                        if (ab) {
                            ab->SetFlag(1);
                            ab->Attach((char*)y + 0x58);
                        }
                    }
                }
            } else if (bAnimal) {
                M2* m2 = GetM2();
                if (m2 && !self->held.ptrValue()) {
                    Cargo* ac = CastAnimal((void**)&held);
                    if (ac) {
                        Profile* pr = GetSetting9(((CargoA*)ac)->GetN())->GetProfile();
                        if (pr) {
                            Y* w = m2->Make(pr, &pos);
                            if (w) {
                                YSub* sub = &w->sub;
                                sub->SetValue(sub->Value());
                                self->held.Assign(w);
                                *(uint32_t*)(w->extra + 0x5fc) |= 0x800000;
                                void* tgt = TargetOf(self->beam);
                                Abducted* ab = CastAbducted(BehaviorManager()->Find(g_behId, 0, tgt, 0));
                                if (ab) {
                                    ab->SetFlag(1);
                                    ab->Attach((char*)w + 0x58);
                                }
                            }
                        }
                    }
                }
            } else if (bPlant) {
                Cargo* pc = CastPlant((void**)&held);
                if (pc) {
                    Profile* pr = GetSetting9(((CargoA*)pc)->GetN())->GetPlantProfile();
                    if (pr) {
                        Plant* pl = GetM3()->MakePlant(pos, 100, pr, ((CargoA*)pc)->GetN(), 0);
                        PlantX* x = pl->sub.GetX();
                        x->Set(pl->sub.Dummy43(1));
                        GetM3()->Finish(pl, 1);
                        self->held.Assign(CastPlantUnk(pl));
                        BehaviorManager()->Register((char*)pl + 0x5e8);
                        void* tgt = TargetOf(self->beam);
                        Abducted* ab = CastAbducted(BehaviorManager()->Find(g_behId, 0, tgt, 0));
                        if (ab) {
                            ab->SetFlag(1);
                            ab->Attach((char*)pl + 0x5e8);
                        }
                    }
                }
            } else if (b4 || b5) {
                Artifact* art = NounManager()->Get();
                if (art) {
                    art->Init1();
                    art->sub.SetPos(&pos);
                    art->Set(item->type, item->GetN(), item->f10, 1);
                    self->held.Assign(art);
                    BehaviorManager()->Register((char*)art + 0x5d0);
                    void* tgt = TargetOf(self->beam);
                    Abducted* ab = CastAbducted(BehaviorManager()->Find(g_behId, 0, tgt, 0));
                    if (ab) {
                        ab->SetFlag(1);
                        ab->Attach((char*)art + 0x5d0);
                    }
                    Planet* pl = GetActivePlanet();
                    Spawn(pl->f13c, item->type, art->Dir(&dir), art->f638, 1, pos, 0);
                }
            }
        }
        if (held) held->Release();
    }
done:
    at.Destroy();
    return true;
}

// ---------------------------------------------------------------------------
// tool-strategy handlers sharing cSPToolStrategy::OnHit
// ---------------------------------------------------------------------------

struct ItemBase {
    P8(a) P8(b) P8(c) P8(d) P8(e) P4(f) P(g0) P(g1)
    virtual void* FindPlugin(int key);                                // +0xb8 (slot 46)
};

struct Strategy {
    P(a0)
    virtual void Slot1();                                             // +0x04
    P(a2) P(a3) P(a4) P(a5)
    virtual void* GetKey();                                           // +0x18 action key (int[3])
    P8(b) P8(c) P(d0) P(d1)
    virtual bool Slot64(void* z);                                     // +0x64
    P8(e) P8(f) P4(g)
    char pad0[0x14 - 4];
    int f14;                                                          // +0x14
    char pad1[0x114 - 0x18];
    ItemBase* item;                                                   // +0x114 held item sub-object
    bool CanUse();                                                    // 0x0104cbc0
    void SetValue(int v);                                             // 0x0104cc00
    int GetCount();                                                   // 0x00a02d30
    float GetRate();                                                  // 0x00ce6940
};

// item requested by key 0xb033b403 (energy repair)
struct RepairObj {
    char pad0[0x714];
    int f714;                                                         // +0x714
    char pad1[0x7f4 - 0x718];
    float f7f4;                                                       // +0x7f4
    float f7f8;                                                       // +0x7f8
    float Repair(float amount);                                       // 0x00c389f0
};

// item requested by key 0x13f94d4 (combatant repair)
struct Combatant {
    P8(a) P8(b) P4(c) P(d0) P(d1)
    virtual float Slot58();                                           // +0x58
    char pad0[0x38 - 4];
    float f38;                                                        // +0x38
    void PartialRepair(float amount);                                 // 0x00bfd1a0
};

struct FVec8 {
    char pad[0xc];
    float* mData;                                                     // +0x0c element array
    void resize(uint32_t n);                                          // 0x007eb820
};

struct WalkAround { void GetOutOfUFO(); };                            // 0x01016070

struct WM {
    P(b0)
    virtual void* Slot1();                                            // +0x04
    P8(c) P8(d) P(e0)
    virtual void Slot4c(int a, void* b);                              // +0x4c (slot 19)
};

struct UFOSim {
    char pad[0x18];
    char f18;                                                         // +0x18
    void F00ffc0b0();                                                 // 0x00ffc0b0
};

struct MsgServer {
    P(a0) P(a1) P(a2) P(a3) P(a4)
    virtual int Slot14(int id, void* msg, int z);                     // +0x14
    virtual int Slot18(int key, int a, int b, int c);                 // +0x18
};

// 5-arg message: vftable/refcount then 10 data slots, id, rc-flags
struct MsgRC5 {
    void* mVftable;                                                   // +0x00
    int mRefCount;                                                    // +0x04
    uint32_t mData[10];                                               // +0x08
    int mId;                                                          // +0x30
    int mPad34;                                                       // +0x34
    int mRCFlags;                                                     // +0x38
    void Destruct();                                                  // 0x00421cf0
};

struct TargetC {
    P(a0) P(a1) P(a2)
    virtual void* SlotC(int key);                                     // +0x0c
};

struct PlanetRecord { char pad[0x2c]; uint32_t f2c; };

struct Ocean {
    P(a0) P(a1) P(a2) P(a3) P(a4) P(a5)
    virtual void Slot18(float f, int a, int b, Vec3* v, int z);       // +0x18
};

struct Profile {
    char pad0[0x504];
    void* f504;                                                       // +0x504 key passed to GetPollinator
};

struct Creature {
    char pad0[0x5a8];
    Ocean sub;                                                        // +0x5a8
    char pad1[0x5e0 - 0x5a8 - 4];
    float f5e0;                                                       // +0x5e0
    Profile* GetSpeciesProfile();                                     // 0x00c0bbd0
    int F00c0bc00(int z);                                             // 0x00c0bc00
    Vec3* GetVec3();                                                  // 0x00c0bc00
};

struct TF { char pad[0x20]; Vec3 f20; Vec3 f2c; };
struct TFA { void F00bbcb10(); };                                     // 0x00bbcb10
struct Pollinator { void Update(); };                                 // 0x0060d860
struct RelationshipMgr { float RecordEvent(int key, float amount); }; // 0x00d06240
struct Tok { char pad[0xc]; void* f0c; };
struct Msg { void Fff6380(); };                                       // 0x00ff6380
struct CreatureEdit { void AutoTest(); };                             // 0x00676e90

struct GDSub {
    P8(a) P(b0) P(b1) P(b2)
    virtual void* Slot2c();                                           // +0x2c (slot 11)
};
struct GDElem {
    P8(a) P4(b)
    virtual void* Slot2c();                                           // +0x2c of the element itself
    char pad[0x34 - 4];
    GDSub sub;                                                        // +0x34
    int ProfLeaveZone();                                              // 0x00bd9e30
};

struct ColonySub {
    P8(a) P(b0) P(b1) P(b2)
    virtual void* Position();                                         // +0x2c (slot 11)
    P(c0) P(c1)
    virtual void SetPosition(Vec3* p);                                // +0x38 (slot 14)
    P8(d) P4(e) P(f0)
    virtual float Radius();                                           // +0x70 (slot 28)
};
struct ColonyObj {
    virtual void Slot0();                                             // +0x00
    virtual void Slot1();                                             // +0x04
    P8(a) P8(b) P8(c) P8(d) P8(e) P4(f)
    virtual void* SlotB8(int key);                                    // +0xb8 (slot 46)
    char pad[0x34 - 4];
    ColonySub sub;                                                    // +0x34
};
struct Cursor {
    P8(a) P8(b) P8(c) P8(d) P8(e) P8(f) P(g0) P(g1) P(g2) P(g3) P(g4)
    virtual void* SlotD4();                                           // +0xd4 (slot 53)
};

struct GameDataVec { char pad[4]; void** mBegin; void** mEnd; };

bool __stdcall OnHit(void* self, void* a2, int a3, int zero);          // 0x010593e0 cSPToolStrategy::OnHit
bool __stdcall CanUseToolBase(void* self, Vec3* pos, int a3);          // 0x01053980 cSPToolStrategy::CanUseToolAtLocation
int __stdcall SetErrorEvent(void* self, int key, int flag);            // 0x010527f0 cSPToolStrategy::SetErrorEvent
void __stdcall CreatePanicBubbleForTool(void* self, Vec3 pos);         // 0x01059170
PlanetRecord* __stdcall GetActivePlanetRecord();                       // 0x010212a0
Empire* __stdcall GetPlayerEmpire();                                   // 0x01021300
int __stdcall GetPlayerEmpireID(int key);                              // 0x01021090
MsgServer* MessageServer();                                            // 0x0067dcc0
CreatureEdit* __stdcall AchievementsController(int a, int b);           // 0x00675250
UFOSim* GetUFOSimulator();                                             // 0x00ffbe50
Planet* PlanetModel();                                                 // 0x00b3d350
Cursor* GetGameTerrainCursor();                                        // 0x00b30d70
TF* TerraformingMgr();                                                 // 0x00b3d390
TFA* __stdcall TerraformingMgrArg(int v);                              // 0x00b3d430
RelationshipMgr* __stdcall RelationshipManager(int a, int b);          // 0x00b3d2c0
Pollinator* __stdcall GetPollinator(const void* key, void* src);       // 0x0067cb30
Vec3* __stdcall RandomDirection3(Vec3* out);                           // 0x00b7e560
WalkAround* F1015df0();                                                // 0x01015df0
WM* WindowManager();                                                   // 0x0067caa0

extern int g_keyZoo[3];                                                // 0x016e1e08
extern int g_keyEradicate[3];                                          // 0x016e1e14
extern int g_keyEpicize[3];                                            // 0x016e1e20
extern int g_keyCreatureEdit[3];                                       // 0x016e1d9c
extern Tok* g_spaceTokenTranslator;                                    // 0x016e0d08
extern float g_relEventAmount;                                         // 0x013ef568
extern float g_oneF;                                                   // 0x01485720

// @ 0x0105b0f0
bool __stdcall EnergyRepairDoToolAction(Strategy* self, void* a2, int a3, void* a4)
{
    if (OnHit(self, a2, a3, 0)) {
        ItemBase* item = self->item;
        if (item) {
            RepairObj* obj = (RepairObj*)item->FindPlugin(0xb033b403);
            if (obj && !obj->f714) {
                float v = obj->f7f8;
                if (v > obj->f7f4) obj->Repair(v * self->GetRate() * 0.01f);
                return true;
            }
        }
    }
    return false;
}

// @ 0x0105b180
bool __stdcall FUN_0105b180(Strategy* self, void* a2, int a3, void* a4)
{
    if (OnHit(self, a2, a3, 0)) {
        Combatant* c = 0;
        ItemBase* item = self->item;
        if (item) c = (Combatant*)item->FindPlugin(0x13f94d4);
        float cap = c->f38;
        if (c->Slot58() > cap) {
            float r = c->Slot58() * self->GetRate() * 0.01f;
            c->PartialRepair(r);
            FVec8* v = (FVec8*)SpaceGameGet()->f5180(0xc);
            v->resize(8);
            v->mData[7] = r;
            return true;
        }
    }
    return false;
}

// @ 0x0105b240
bool __stdcall GetOutOfUFODoToolAction(Strategy* self, void* a2, int a3, void* a4)
{
    if (OnHit(self, a2, a3, 0)) {
        if (self->CanUse()) {
            self->SetValue(-1);
            if (self->GetCount() <= 0) {
                Inv* inv = SpaceGameGet()->GetPlayerInventory();
                int handle = inv->Find(self->f14, (int)self->GetKey());
                void* taken = self;
                self->Slot1();
                if (SpaceGameGet()->GetPlayerInventory()->Take(handle, &taken, -1)) {
                    SpaceGameGet()->GetPlayerInventory()->Refresh();
                }
                if (taken) ((Unk*)taken)->Release();
            }
        }
        SpaceGameGet()->F1003480();
        WalkAround* wa = F1015df0();
        wa->GetOutOfUFO();
        WindowManager()->Slot4c(0, WindowManager()->Slot1());
        return true;
    }
    return false;
}

// @ 0x0105b350
bool __stdcall DefaultProjectileWeaponDoToolAction(Strategy* self, Vec3* pos, int a3, TargetC* a4)
{
    if (!OnHit(self, pos, a3, 0)) return false;
    int* k1 = (int*)self->GetKey();
    if (k1[0] == g_keyZoo[0] && k1[1] == g_keyZoo[1] && k1[2] == g_keyZoo[2]) {
        PlanetRecord* rec = GetActivePlanetRecord();
        rec->f2c |= 0x800;
        void* av = SpaceGameGet()->GetAvatar();
        if (av) ((Msg*)av)->Fff6380();
        MessageServer()->Slot18(0x490d429, 0, 0, 0);
        g_spaceTokenTranslator->f0c = GetActivePlanetRecord();
        AchievementsController(0xcfc6c8ee, 1)->AutoTest();
        GetUFOSimulator()->f18 = 0;
    }
    int* k2 = (int*)self->GetKey();
    if (k2[0] == g_keyEradicate[0] && k2[1] == g_keyEradicate[1]
        && k2[2] == g_keyEradicate[2] && a3 == 0) {
        if (a4) {
            Creature* cr = (Creature*)a4->SlotC(0xd0036e08);
            if (cr) {
                void* prof = &cr->GetSpeciesProfile()->f504;
                GetPollinator((const void*)0xbe96cd0, prof)->Update();
                TerraformingMgrArg(cr->F00c0bc00(0))->F00bbcb10();
                float f = cr->f5e0;
                Vec3 dir;
                cr->sub.Slot18(f, -1, 0, RandomDirection3(&dir), 0);
                Empire* e = GetActivePlanet()->F00c71e30();
                if (e && e != GetPlayerEmpire()) {
                    RelationshipManager(e->f84, GetPlayerEmpireID(0x526e531))
                        ->RecordEvent(0x526e531, g_relEventAmount);
                }
            }
        }
    }
    int* k3 = (int*)self->GetKey();
    if (k3[0] == g_keyEpicize[0] && k3[1] == g_keyEpicize[1]
        && k3[2] == g_keyEpicize[2] && a3 == 0 && a4) {
        Creature* cr = (Creature*)a4->SlotC(0xd0036e08);
        if (cr) {
            Vec3 p = *cr->GetVec3();
            TerraformingMgr()->f20 = p;
            TerraformingMgr()->f2c = *pos;
        }
    }
    int* k4 = (int*)self->GetKey();
    if (k4[0] == g_keyCreatureEdit[0] && k4[1] == g_keyCreatureEdit[1]
        && k4[2] == g_keyCreatureEdit[2]) {
        GetUFOSimulator()->F00ffc0b0();
        GetUFOSimulator()->f18 = 0;
        if (a3 == 0 && a4) {
            Creature* cr = (Creature*)a4->SlotC(0xd0036e08);
            if (cr) {
                MsgRC5 msg;
                msg.mId = 0x3b092aa;
                msg.mVftable = (void*)0x13eb90c;
                msg.mRefCount = 0;
                msg.mVftable = (void*)0x13eb844;
                msg.mRCFlags = 0;
                msg.mData[0] = (uint32_t)cr;
                MessageServer()->Slot14(msg.mId, &msg, 0);
                msg.Destruct();
            }
        }
    }
    CreatePanicBubbleForTool(self, *pos);
    return true;
}

// @ 0x0105b6a0
bool __stdcall PlaceColonyCanUseToolAtLocation(Strategy* self, Vec3* pos, int a3)
{
    if (!CanUseToolBase(self, pos, a3)) return false;
    Planet* pm = PlanetModel();
    if (pm && pm->Fb7e3e0(pos)) {
        SetErrorEvent(self, 0xd7ff4c0b, a3);
        return false;
    }
    Cursor* cur = GetGameTerrainCursor();
    ColonyObj* probe = (ColonyObj*)cur->SlotD4();
    if (!probe) return false;
    ColonyObj* obj = (ColonyObj*)probe->SlotB8(0x2450023);
    if (!obj) return false;
    obj->Slot0();
    obj->sub.SetPosition(pos);
    Nm* nm = NounManager();
    GameDataVec* vec = NounManager()->GetGameDataVector(0xcd7d10, 0xd3d420, 0xacdff0, 0xb1e500, (void*)0x18c43e8);
    GDElem** it = (GDElem**)vec->mBegin;
    GDElem** end = (GDElem**)vec->mEnd;
    for (; it != end; ++it) {
        GDElem* e = *it;
        if (!e->Slot2c()) {
            int z = e->ProfLeaveZone();
            if (z && self->Slot64((void*)z)) {
                SetErrorEvent(self, 0x147e3c98, a3);
                obj->Slot1();
                return false;
            }
        }
    }
    GameDataVec* vec2 = nm->GetGameDataVector(0xcd7d10, 0xd3d420, 0xae5ea0, 0xb1e500, (void*)0x403df5c);
    float r = obj->sub.Radius();
    float radius = r * obj->sub.Radius() - g_oneF;
    bool found = false;
    GDElem** it2 = (GDElem**)vec2->mBegin;
    GDElem** end2 = (GDElem**)vec2->mEnd;
    for (; it2 != end2; ++it2) {
        Vec3* p = (Vec3*)(*it2)->sub.Slot2c();
        if ((pos->y - p->y) * (pos->y - p->y) + (pos->z - p->z) * (pos->z - p->z)
            + (pos->x - p->x) * (pos->x - p->x) <= 14400.0f) {
            SetErrorEvent(self, 0x1458fe70, a3);
            obj->Slot1();
            return false;
        }
        Vec3* q = (Vec3*)(*it2)->sub.Slot2c();
        if ((pos->z - q->z) * (pos->z - q->z) + (pos->y - q->y) * (pos->y - q->y)
            + (pos->x - q->x) * (pos->x - q->x) <= radius) {
            found = true;
        }
    }
    if (!found) SetErrorEvent(self, 0xc18c8011, a3);
    obj->Slot1();
    return found;
}
