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
    virtual void Take(int handle, void** out, int count);     // +0x7c (slot 31)
    Item* Current();                                          // 0x00ff3f10
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
struct Nm { Artifact* Get(); };                                           // 0x0103a080
struct Planet { char pad[0x13c]; int f13c; };

struct ProfSrc {
    Profile* GetProfile();                                                // 0x004df550
    Profile* GetPlantProfile();                                           // 0x004df440
};
struct Game { Inv* GetPlayerInventory(); };                               // 0x00a1ad60

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
