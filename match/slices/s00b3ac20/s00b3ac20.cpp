// Slice s00b3ac20 -- editor/viewer one-time initializer (registers cheats + message listeners,
// creates the physics world and raster, wires model/effect resources, fills a key->value table).
// Built /O2 /MD /Gy /EHsc /TP.
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

// Intrusive ref-counted base: vtable slot 0 = AddRef, slot 1 = Release.
struct RefObj {
    virtual int AddRef();
    virtual int Release();
};

struct Bits64 {
    u32 w[2];
    Bits64() { w[0] = 0; w[1] = 0; }
    void set(u32 i)   { if (i < 0x40) w[i >> 5] |= 1u << (i & 0x1f); }
    void reset(u32 i) { if (i < 0x40) w[i >> 5] &= ~(1u << (i & 0x1f)); }
};

// World object (Gonzago model world): vtable +0x11c / +0x120 / +0x140 take mask pairs / a renderer.
struct World : RefObj {
    virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6();
    virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11();
    virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16();
    virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21();
    virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26();
    virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31();
    virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36();
    virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41();
    virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46();
    virtual void p47(); virtual void p48(); virtual void p49(); virtual void p50(); virtual void p51();
    virtual void p52(); virtual void p53(); virtual void p54(); virtual void p55(); virtual void p56();
    virtual void p57(); virtual void p58(); virtual void p59(); virtual void p60(); virtual void p61();
    virtual void p62(); virtual void p63(); virtual void p64(); virtual void p65(); virtual void p66();
    virtual void p67(); virtual void p68(); virtual void p69(); virtual void p70();
    virtual void SetMasks(Bits64* a, Bits64* b, int slot);      // 0x11c (71)
    virtual void ClearMasks(Bits64* a, Bits64* b, int slot);    // 0x120 (72)
    virtual void p73(); virtual void p74(); virtual void p75(); virtual void p76(); virtual void p77();
    virtual void p78(); virtual void p79();
    virtual void SetRenderer(RefObj* r, int slot, int enable);  // 0x140 (80)
};

// Resource/model manager: vtable +0x14 Get(id, 0, 0), +0x1c Find(id), +0x28 GetIndex(id, name).
struct ResManager {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3(); virtual void m4();
    virtual World* Get(u32 id, int a, int b);              // 0x14
    virtual void m6();
    virtual World* Find(u32 id);                           // 0x1c
    virtual void m8(); virtual void m9();
    virtual u32 GetIndex(u32 id, const char* name);        // 0x28
};

struct Effect : RefObj {
    virtual void SetQuality(int q);                        // 0xc
};

struct EffectsManager {
    virtual void e0(); virtual void e1(); virtual void e2(); virtual void e3(); virtual void e4();
    virtual void e5(); virtual void e6(); virtual void e7(); virtual void e8(); virtual void e9();
    virtual void e10(); virtual void e11(); virtual void e12(); virtual void e13(); virtual void e14();
    virtual void e15(); virtual void e16(); virtual void e17(); virtual void e18();
    virtual Effect* Get(u32 id, int flags);                // 0x4c
};

struct LightingMgr {
    virtual void l0(); virtual void l1(); virtual void l2(); virtual void l3(); virtual void l4();
    virtual void l5();
    virtual RefObj* Get(u32 id, int a, int b);             // 0x18
};
struct Lighting : RefObj {
    virtual void l2(); virtual void l3(); virtual void l4(); virtual void l5(); virtual void l6();
    virtual void l7(); virtual void l8(); virtual void l9(); virtual void l10();
    virtual void Apply(u32 id);                            // 0x30 (12)
};

struct cCommandBase {
    int cb[3];
    cCommandBase();
    virtual ~cCommandBase() {}
};
struct cViewManagerCommand : cCommandBase { virtual void Run() {} };
struct cSuperHighLODCheat  : cCommandBase { virtual void Run() {} };

struct CheatManager {
    virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4();
    virtual void c5();
    virtual void AddCheat(const char* name, cCommandBase* cmd, int flags);  // 0x18
};

struct IListener { virtual void l0(); };
struct MessageServer {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7();
    virtual void AddListener(IListener* l, u32 msg);       // 0x20
};

struct ViewerSetup { virtual void v0(); };    // FUN_0067dd50 result; vtable +0x1c called
struct ViewerSetup2 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6();
    virtual void Run();                                     // 0x1c
};

struct RasterInfo { u32 handle; u32 pad[2]; u16 w; u16 h; };
struct cSPEditorPhysicsWorld {
    char pad[0x174];
    cSPEditorPhysicsWorld();
    void Init(int);
    RasterInfo* GetRasterInfo();
};
struct InitArea { void Init(int); };
struct V { u32 a, b; };
struct ValueMap {
    char pad[0x34];
    V& operator[](const u32& key);
};

void* __cdecl operator_new(unsigned, const char*, int, int, int, int);
inline void* operator new(unsigned n, const char* name, int a, int b, int c, int d) {
    return operator_new(n, name, a, b, c, d);
}
inline void operator delete(void*, const char*, int, int, int, int) {}

namespace SP {
    CheatManager*   __cdecl GetCheatManager();    // 0x67de20
    MessageServer*  __cdecl GetMessageServer();   // 0x67dcc0
    LightingMgr*    __cdecl GetLightingManager(); // 0x67dd90
    ResManager*     __cdecl GetModelManager();    // 0x67dd80
    EffectsManager* __cdecl GetEffectsManager();  // 0x67ddd0
    World*          __cdecl GetGonzagoModelWorld(); // 0xb3d520
    int __cdecl CreateRaster(int, int, int, int, u32);  // 0x761420
}
ViewerSetup2* __cdecl GetViewerSetup();           // 0x67dd50
extern RefObj* g_Lighting;                        // 0x167ea54

struct A0 { virtual void a0(); };
struct C0 : IListener { virtual void c0(); };

struct B {
    virtual void b0();
    char pad0[0x20];
    InitArea area;          // 0x24 ... (0x60 bytes)
    char pad1[0x5f];
    ValueMap m;             // 0x84
    u8  f_b8, f_b9, f_ba;
    char pad2[0x21];
    RefObj* p_dc;
    RefObj* p_e0;
    char pad3[4];
    cSPEditorPhysicsWorld* phys;   // 0xe8
    char pad4[4];
    int raster;                    // 0xf0

    void Setup();
};
struct Outer : A0, C0, B { void Prepare(); };


static inline void AssignRef(RefObj*& dst, RefObj* src) {
    RefObj* old = dst;
    if (src != old) {
        if (src) src->AddRef();
        dst = src;
        if (old) old->Release();
    }
}

// @ 0x00b3ac20
void B::Setup()
{
    if (f_b8)
        return;
    f_ba = 1;
    f_b9 = 1;
    area.Init(0x80);
    new ("App/cViewManagerCommand", 0, 0, 0, 0) cViewManagerCommand();
    SP::GetCheatManager();
    cSuperHighLODCheat* cheat = new ("App/cSuperHighLODCheat", 0, 0, 0, 0) cSuperHighLODCheat();
    SP::GetCheatManager()->AddCheat("highresTextureLevel", cheat, 0);
    MessageServer* ms = SP::GetMessageServer();
    Outer* o = (Outer*)((char*)this - 8);
    ms->AddListener((C0*)o, 0x30c11c7);
    ms->AddListener((C0*)o, 0x3047cb34);
    ms->AddListener((C0*)o, 0x1a0219e);
    ms->AddListener((C0*)o, 0x4b719d4);
    ms->AddListener((C0*)o, 0x712924f2);
    ms->AddListener((C0*)o, 0x712924f3);
    f_b8 = 1;
    AssignRef(g_Lighting, SP::GetLightingManager()->Get(0x4a4dea0, 0, 0));
    ((Lighting*)g_Lighting)->Apply(0x5f848353);

    phys = new ("Simulator", 0, 0, 0, 0) cSPEditorPhysicsWorld();
    phys->Init(0);
    GetViewerSetup()->Run();
    RasterInfo* ri = phys->GetRasterInfo();
    raster = SP::CreateRaster((u16)ri->h, (u16)ri->w, 1, 2, ri->handle);

    ResManager* mm = SP::GetModelManager();
    World* w = SP::GetGonzagoModelWorld();
    if (w) {
        w->AddRef();
    } else {
        w = mm->Get(0xeb9968, 0, 0);
        if (w) w->AddRef();
        u32 mask   = mm->GetIndex(0x31e5f0f, "Mask");
        u32 post   = mm->GetIndex(0x420b420, "PostEffects");
        u32 back   = mm->GetIndex(0x64ac354, "BackgroundEffects");
        u32 noshad = mm->GetIndex(0x6669387, "NoShadowCast");
        u32 over   = mm->GetIndex(0x7aa969b, "overdraw");
        Bits64 a, b;
        a.set(mask); a.set(post); a.set(back);
        w->SetMasks(&b, &a, 0);
        a = Bits64(); b = Bits64();
        b.set(mask);
        w->SetMasks(&b, &a, 1);
        a = Bits64(); b = Bits64();
        b.set(post);
        w->SetMasks(&b, &a, 2);
        a = Bits64(); b = Bits64();
        b.set(over);
        w->SetMasks(&b, &a, 7);
        w->ClearMasks(&b, &a, 0);
        a.reset(post);
        a.set(noshad);
        w->SetMasks(&b, &a, 3);
        a = Bits64(); b = Bits64();
        b.set(back);
        w->SetMasks(&b, &a, 4);
    }
    RefObj* r;
    r = mm->Find(0x317ccba) ? mm->Find(0x317ccba) : mm->Get(0x317ccba, 0, 0);
    AssignRef(p_dc, r);
    r = mm->Find(0x5de6030) ? mm->Find(0x5de6030) : mm->Get(0x5de6030, 0, 0);
    AssignRef(p_e0, r);

    Effect* e1 = SP::GetEffectsManager()->Get(0xeb9968, 0);
    if (e1) e1->AddRef();
    e1->SetQuality(2);
    Effect* e2 = SP::GetEffectsManager()->Get(0x23541242, 0);
    if (e2) e2->AddRef();
    e2->SetQuality(2);
    SP::GetEffectsManager()->Get(0x3701a5c, 0);
    w->SetRenderer(g_Lighting, 0, 1);
    w->SetRenderer(g_Lighting, 1, 1);
    w->SetRenderer(g_Lighting, 4, 1);
    RefObj* mv = SP::GetModelManager()->Find(0x3fbae24);
    if (mv) {
        mv->AddRef();
        ((World*)mv)->SetRenderer(g_Lighting, 0, 1);
        ((World*)mv)->SetRenderer(g_Lighting, 1, 1);
    }
    ((Outer*)((char*)this - 8))->Prepare();
    { V& v = m[0x0147e293u]; v.a = 0x3596af86u; v.b = 0; }
    { V& v = m[0x014fc194u]; v.a = 0x98ff936au; v.b = 0; }
    { V& v = m[0x01511148u]; v.a = 0xc07ea120u; v.b = 0; }
    { V& v = m[0x015b6c56u]; v.a = 0x5faed94cu; v.b = 0; }
    { V& v = m[0x1b559d6u]; v.a = 0xeab8865cu; v.b = 0; }
    { V& v = m[0x1b559d7u]; v.a = 0x927be8cau; v.b = 0; }
    { V& v = m[0x4c9bc66u]; v.a = 0x6a934f8eu; v.b = 0; }
    { V& v = m[0x1b55d9au]; v.a = 0xef8f883fu; v.b = 0; }
    { V& v = m[0x1b55d9bu]; v.a = 0x882f73b0u; v.b = 0; }
    { V& v = m[0x33ce1f4u]; v.a = 0xa58cc82du; v.b = 0; }
    { V& v = m[0x33ce359u]; v.a = 0xf0556401u; v.b = 0; }
    { V& v = m[0x4fd21bbcu]; v.a = 0x4fd21bbcu; v.b = 0; }
    { V& v = m[0xd3520187u]; v.a = 0xd3520187u; v.b = 0; }
    { V& v = m[0x534a52c0u]; v.a = 0x534a52c0u; v.b = 0; }
    { V& v = m[0xe4141994u]; v.a = 0xe4141994u; v.b = 0; }
    { V& v = m[0xed8c1210u]; v.a = 0xed8c1210u; v.b = 0; }
    { V& v = m[0xf7129557u]; v.a = 0xf7129557u; v.b = 0; }
    { V& v = m[0x1c0ffcfu]; v.a = 0xc07ea120u; v.b = 0; }
    { V& v = m[0x1d1109fu]; v.a = 0x384e54a4u; v.b = 0; }
    { V& v = m[0x1d110a0u]; v.a = 0x384e54a4u; v.b = 0; }
    { V& v = m[0x70f4ed3fu]; v.a = 0x4c216c78u; v.b = 0; }
    { V& v = m[0x70f4ed48u]; v.a = 0xdd480fccu; v.b = 0; }
    { V& v = m[0x22941e7u]; v.a = 0x696fc076u; v.b = 0; }
    { V& v = m[0x110f08c3u]; v.a = 0x3a616feeu; v.b = 0; }
    { V& v = m[0x2818ee0u]; v.a = 0x2090a5c4u; v.b = 0; }
    { V& v = m[0x2c4a8c2u]; v.a = 0x13505630u; v.b = 0; }
    { V& v = m[0x2c4a8cfu]; v.a = 0x2af2f191u; v.b = 0; }
    { V& v = m[0x2df3696u]; v.a = 0x6f1a1f1cu; v.b = 0; }
    { V& v = m[0x2e5d3a1u]; v.a = 0xb6f9b664u; v.b = 0; }
    { V& v = m[0x2df3697u]; v.a = 0xb6f9b679u; v.b = 0; }
    { V& v = m[0x2e5d3a6u]; v.a = 0x841a4016u; v.b = 0; }
    { V& v = m[0x30e8e52u]; v.a = 0x557b9e43u; v.b = 0; }
    { V& v = m[0x3f970d5u]; v.a = 0x6857b824u; v.b = 0; }
    { V& v = m[0x3704925u]; v.a = 0xf42bc0cau; v.b = 0; }
    { V& v = m[0x498da10u]; v.a = 0xf3043512u; v.b = 0; }
    { V& v = m[0x498ef27u]; v.a = 0x13714350u; v.b = 0; }
    { V& v = m[0x498ef28u]; v.a = 0x13714350u; v.b = 0; }
    { V& v = m[0x498ef29u]; v.a = 0x13714350u; v.b = 0; }
    { V& v = m[0x498ef2au]; v.a = 0xaa8e5065u; v.b = 0; }
    { V& v = m[0x498ef2bu]; v.a = 0x35d90ae0u; v.b = 0; }
    { V& v = m[0x3967564u]; v.a = 0x94f98b88u; v.b = 0; }
    { V& v = m[0x4288912u]; v.a = 0xd409170au; v.b = 0; }
    { V& v = m[0x4288913u]; v.a = 0x2e779a5bu; v.b = 0; }
    { V& v = m[0x4288915u]; v.a = 0x8c556f0fu; v.b = 0; }
    { V& v = m[0x4288916u]; v.a = 0x75f3c47au; v.b = 0; }
    { V& v = m[0x42a3491u]; v.a = 0x26a290fbu; v.b = 0; }
    { V& v = m[0x4aef54cu]; v.a = 0x61247e8au; v.b = 0; }
    { V& v = m[0x5f2281eu]; v.a = 0x8742f960u; v.b = 0; }
    { V& v = m[0x5f22835u]; v.a = 0x3600a13cu; v.b = 0; }
    { V& v = m[0x9d10712au]; v.a = 0x9d10712au; v.b = 0; }
    { V& v = m[0x631456d0u]; v.a = 0x631456d0u; v.b = 0; }
    { V& v = m[0x5dfc872u]; v.a = 0x147e73aau; v.b = 0; }
    { V& v = m[0x5dfc876u]; v.a = 0x8e205c26u; v.b = 0; }
    { V& v = m[0x5dfc877u]; v.a = 0x9eea0c4du; v.b = 0; }
    { V& v = m[0x674a629u]; v.a = 0x94e81dau; v.b = 0; }
    { V& v = m[0x5f4d3ceu]; v.a = 0x6cc01c53u; v.b = 0; }
    { V& v = m[0x5f4e0a8u]; v.a = 0xea04f48cu; v.b = 0; }
    { V& v = m[0x5f4e0b2u]; v.a = 0xb8888214u; v.b = 0; }
    { V& v = m[0x6257fd5u]; v.a = 0x18d072fbu; v.b = 0; }
    { V& v = m[0x6257fd6u]; v.a = 0x284f0d6du; v.b = 0; }
    { V& v = m[0x64bf470u]; v.a = 0x8b47348u; v.b = 0; }
    { V& v = m[0x64d02d1u]; v.a = 0x5b83cc01u; v.b = 0; }
    { V& v = m[0x64d03a2u]; v.a = 0x3a2ebdf1u; v.b = 0; }
    { V& v = m[0x65baa81u]; v.a = 0x653a14b2u; v.b = 0; }
    { V& v = m[0x71d8ae1u]; v.a = 0x86eac279u; v.b = 0; }
    { V& v = m[0x71d8ae2u]; v.a = 0xc3e33771u; v.b = 0; }
    { V& v = m[0x7b11813u]; v.a = 0x8b00b61bu; v.b = 0; }
    { V& v = m[0x303426c3u]; v.a = 0x64b8ee25u; v.b = 0; }
    { V& v = m[0x903426cdu]; v.a = 0xa4f9b7e1u; v.b = 0; }
    { V& v = m[0xf03426e2u]; v.a = 0xd2f96c5du; v.b = 0; }
    { V& v = m[0xf03426ebu]; v.a = 0x59627979u; v.b = 0; }
    { V& v = m[0x90342700u]; v.a = 0x236675a1u; v.b = 0; }
    { V& v = m[0x3034270eu]; v.a = 0xda408635u; v.b = 0; }
    { V& v = m[0x90342759u]; v.a = 0x84bf60c5u; v.b = 0; }
    { V& v = m[0xf0342787u]; v.a = 0x41fbaff5u; v.b = 0; }
    { V& v = m[0x70342790u]; v.a = 0x8a3f628fu; v.b = 0; }
    { V& v = m[0xb034279cu]; v.a = 0x5c53082fu; v.b = 0; }
    { V& v = m[0xb03427a8u]; v.a = 0x5bbb080eu; v.b = 0; }
    { V& v = m[0x903427bfu]; v.a = 0x3830077fu; v.b = 0; }
    { V& v = m[0x703427c9u]; v.a = 0x4717946au; v.b = 0; }
    { V& v = m[0xd03427ceu]; v.a = 0x7a23d986u; v.b = 0; }
    { V& v = m[0x903427dau]; v.a = 0xffd97cdau; v.b = 0; }
    { V& v = m[0x303d8d78u]; v.a = 0xc3a516aau; v.b = 0; }
    { V& v = m[0xd03d8d89u]; v.a = 0xff9d0821u; v.b = 0; }
    { V& v = m[0x703d8d99u]; v.a = 0x8618c23au; v.b = 0; }
    { V& v = m[0x1046f5efu]; v.a = 0x70071e35u; v.b = 0; }
    { V& v = m[0x37ac469u]; v.a = 0xdd64cccau; v.b = 0; }
    { V& v = m[0x37ac46au]; v.a = 0x1f7d424bu; v.b = 0; }
    { V& v = m[0xf046f5fdu]; v.a = 0xfafe30f5u; v.b = 0; }
    { V& v = m[0xf046f60au]; v.a = 0x81e1fb19u; v.b = 0; }
    { V& v = m[0x1046f612u]; v.a = 0x118baa1u; v.b = 0; }
    { V& v = m[0x7046f646u]; v.a = 0x17d5bd7bu; v.b = 0; }
    { V& v = m[0x7046f656u]; v.a = 0x20f1d4edu; v.b = 0; }
    { V& v = m[0xb062b167u]; v.a = 0x245cb231u; v.b = 0; }
    { V& v = m[0xf062b161u]; v.a = 0x68e34bdu; v.b = 0; }
    { V& v = m[0xd062b171u]; v.a = 0x1939bc61u; v.b = 0; }
    { V& v = m[0x3062b66bu]; v.a = 0xc273c016u; v.b = 0; }
    { V& v = m[0x5062b673u]; v.a = 0xa2d7c12du; v.b = 0; }
    { V& v = m[0x2e63e90u]; v.a = 0x60bad155u; v.b = 0; }
    { V& v = m[0x2e63e91u]; v.a = 0x63e4b4f4u; v.b = 0; }
    { V& v = m[0x2e63e92u]; v.a = 0x3d2f6e8eu; v.b = 0; }
    { V& v = m[0x2e63e93u]; v.a = 0x275cdfceu; v.b = 0; }
    { V& v = m[0x2e65455u]; v.a = 0x62065c42u; v.b = 0; }
    { V& v = m[0x11c8ccdfu]; v.a = 0x57ad4e74u; v.b = 0; }
    if (mv) mv->Release();
    e2->Release();
    e1->Release();
    w->Release();
}
