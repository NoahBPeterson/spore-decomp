// Slice s00ccdd70 (cl2 #178): SP::cTribeDisplayStrategy::Activate (0x00ccdd70, 2071 bytes).
//
// Retail layout of cTribeDisplayStrategy (differs from the 2008 PDB), recovered from the asm:
//   +0x38 EA::Messaging::IHandler subobject (secondary base)
//   +0x4c global tribe UI (cSPGlobalUI-TribeUI, 0x68 bytes)       +0x50 mode strategy (refcount via vt0/vt1)
//   +0x58 message server, +0x5c handler, +0x60 id table, +0x64 count(10), +0x68 0
//   +0x70 civ minimap (secondary base at +4), +0x74 layout (vt1/vt2), +0x78 posse set (intrusive +4)
//   +0xb0 ornament (intrusive +4), +0xb8 model instance sets [2] (stride 0x60)
//   +0x2b8 swatch, +0x2bc window (both refcount via vt0/vt1), +0x4f0/+0x4f4 UI helpers
#include "types.h"

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

inline void* operator new(unsigned int, void* p) { return p; }

extern "C" void* op_new(u32 size, const char* name, int a, int b, int c, int d);   // 0xf473a0

struct Vec3 { float x, y, z; };

// ---- generic virtual dispatch ---------------------------------------------
template <class R> inline R V0(void* o, int off) { return ((R (__thiscall *)(void*))(*(void***)o)[off / 4])(o); }
template <class R, class A> inline R V1(void* o, int off, A a) { return ((R (__thiscall *)(void*, A))(*(void***)o)[off / 4])(o, a); }
template <class R, class A, class B> inline R V2(void* o, int off, A a, B b) { return ((R (__thiscall *)(void*, A, B))(*(void***)o)[off / 4])(o, a, b); }
template <class R, class A, class B, class C> inline R V3(void* o, int off, A a, B b, C c) { return ((R (__thiscall *)(void*, A, B, C))(*(void***)o)[off / 4])(o, a, b, c); }

// ---- refcount styles --------------------------------------------------------
struct RefA { virtual void AddRef(); virtual void Release(); };                    // slots 0/1
struct RefB { virtual void Dtor(int); virtual void AddRef(); virtual void Release(); };   // slots 1/2
struct RCObj { virtual void Del(int); int ref; };                                   // intrusive +4

template <class T> inline void SetA(T*& slot, T* nv)
{
    T* old = slot;
    if (nv != old) {
        if (nv) nv->AddRef();
        slot = nv;
        if (old) old->Release();
    }
}
template <class T> inline void SetC(T*& slot, T* nv)
{
    T* old = slot;
    if (nv != old) {
        if (nv) ++nv->ref;
        slot = nv;
        if (old && --old->ref == 0) {
            old->ref = 1;
            old->Del(1);
        }
    }
}

// ---- external game objects (masked callees) -----------------------------------
struct Layout : RefB {
    Layout* Ctor();                                                  // 0x810000 thiscall, returns this
    bool Init(const wchar_t* name, u32 id, int a, u32 b);            // 0x812160 ret 0x10
    void SetVisibility(int v);                                       // 0x810590 ret 4
};
struct PosseSet : RCObj {
    PosseSet() { ref = 0; z[0] = z[1] = z[2] = z[3] = z[4] = z[5] = 0; }
    int z[6];
    void Init();                                                     // 0xcca230
};
struct Window : RefA {
    char pad[0x80];
};
struct TribeUI {
    virtual void s0(); virtual void s1(); virtual void Setup(const void* p);   // slot 2 (0x8)
    int pad;
    void* buffer;                                                    // +8
    TribeUI* Ctor();                                                 // 0xe03ab0
    void* GetBuffer();                                               // 0x93b6c0
    Window* FindWindowByID(int id);                                  // 0xe012b0 ret 4
};
struct Ornament : RCObj {
    Ornament* Ctor(void* buf, const void* name);                     // 0xe28a10 ret 8
    void Post();                                                     // 0xe29c80
};
struct ModeStrategy : RefA {
    ModeStrategy* Ctor();                                            // 0xe31320
    void Setup();                                                    // 0xe31670
    void SetFlag(int v);                                             // 0xe31160 ret 4
    u8   GetFlag();                                                  // 0xe31170
};
struct CivMinimap : RefA {
    CivMinimap* Ctor(int w, int h, const Vec3* a, const Vec3* b, float f, int z);   // 0xe0fc90 ret 0x18
};
struct PropList { bool GetDescription(u32 id); };                    // 0x6a25a0 ret 4
struct Swatch : RefA {
    Swatch* Ctor();                                                  // 0x5f6bd0
    void Init(void* a, Window* w, int b, int c, int d, int e, int f);   // 0x5f4f80 ret 0x1c
    void F2240(int v);                                               // 0x5f2240 ret 4
    void F2250(int v);                                               // 0x5f2250 ret 4
    void F2d00(u32 id, int v);                                       // 0x5f2d00 ret 8
};
struct SwatchMgr { Swatch* CreateSwatch(Swatch* proto); };           // 0x5f0ca0 ret 4
SwatchMgr* SwatchManager();                                          // 0x401020
struct TribeData { void* Fn(int idx); };
struct Tribe { TribeData* GetThing(int); };                          // 0xc8e820 ret 4
struct Orn2 : RefA {
    virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual int NounType();                                          // slot 8 (0x20)
    char pad[0x84 - 4];
    u32 flags;                                                       // +0x84
    char pad2[0xa5 - 0x88];
    u8 f_a5;
    char pad3[3];
    u8 f_a9;
};
struct NounMgr {
    Orn2* Create(u32 noun, u32 kind, u32 z, const void* pos, const void* q);  // 0xb23650 ret 0x14
    Tribe* GetPlayerTribe();                                         // 0xbfc5f0
};
NounMgr* NounManager();                                              // 0xb3d300
struct TribeMode;
struct TMBase0 { virtual void a(); };
struct TMBase1 { virtual void b(); };
struct TribeMode : TMBase0, TMBase1 {
    char pad[0x258 - 8];
    Orn2* player[20];                                                // +0x258
    Orn2* npc[20];                                                   // +0x2a8
    bool Flag();                                                     // 0xcd54f0
};
TribeMode* TribeModeInstance();                                      // 0xcd40b0
struct Server { };
Server* GetServer();                                                 // 0x883860
void* GetHeap();                                                     // 0x9512c0
void* AllocAligned(u32 size, u32 align, const char* name, void* heap);   // 0x9512d0
struct Planet {
    u32* GetName();   // 0xc707e0
};
Planet* GetActivePlanet();                                           // 0x1021260
struct UIHelper {
    void Fn(int a, int b);   // 0xce9e20 ret 8
};

struct Xform {
    u16 a, b;
    float pos[3];
    float scale;
    float m[9];
};
struct XVec {
    Xform* b; Xform* e; Xform* c;
    void Resize(u32 n);                                              // 0x41e3b0 ret 4
};
struct ModelSet {
    u32 pad0;
    u32 id;                                                          // +4
    u32 pad8;
    XVec vec;                                                        // +0xc
    char pad[0x60 - 0x18];
    void AddToRenderer(void* p);                                     // 0x6f3df0 ret 4
};
void* GetRenderer();                                                 // 0x67de00

extern u32 g_msgIds[10];       // 0x1476be4
extern PropList* g_appProps;   // 0x15fd918
extern Vec3 g_xfPos;           // 0x169b0f0
extern float g_xfMat[9];       // 0x169b13c
extern char g_uiSetupArg[];   // 0x157ecc8
extern char g_ornName[];      // 0x1476b68

struct DispBase { virtual ~DispBase(); char pad[0x34]; };
struct IHandler { virtual void h0(); };

struct TribeDisplay : DispBase, IHandler {
    char p3c[0x4c - 0x3c];
    TribeUI* ui;           // +0x4c
    ModeStrategy* mode;    // +0x50
    char p54[4];
    Server* server;        // +0x58
    IHandler* handler;     // +0x5c
    u32* idTable;          // +0x60
    int idCount;           // +0x64
    int p68;               // +0x68
    char p6c[4];
    CivMinimap* minimap;   // +0x70
    Layout* layout;        // +0x74
    PosseSet* posse;       // +0x78
    char p7c[0xb0 - 0x7c];
    Ornament* ornament;    // +0xb0
    char pb4[4];
    ModelSet sets[2];      // +0xb8
    char pad2[0x2b8 - 0x178];
    Swatch* swatch;        // +0x2b8
    Window* swatchWin;     // +0x2bc
    char pad3[0x4f0 - 0x2c0];
    UIHelper* helperA;     // +0x4f0
    UIHelper* helperB;     // +0x4f4

    void MakeTribeIcons();   // 0xccd8a0
    // @ 0x00ccdd70
    void Activate();
};

void TribeDisplay::Activate()
{
    Server* srv = GetServer();
    IHandler* h = static_cast<IHandler*>(this);
    server = srv;
    handler = h;
    idTable = g_msgIds;
    idCount = 10;
    p68 = 0;
    if (srv && h) {
        u32 i = 0;
        do {
            V2<void, IHandler*, u32>(srv, 0x24, h, *(u32*)((char*)g_msgIds + i));
            i += 4;
        } while (i < 0x28);
    }

    // layout
    {
        void* mem = op_new(0x18, "Simulator/PosseItemTribeIcons", 0, 0, 0, 0);
        Layout* l = mem ? ((Layout*)mem)->Ctor() : 0;
        Layout* old = layout;
        if (l != old) {
            if (l) l->AddRef();
            layout = l;
            if (old) old->Release();
        }
        if (layout->Init(L"PosseItemTribeIcons", 0x40464100, 1, 0x5b598fa))
            layout->SetVisibility(0);
    }

    // posse set
    {
        PosseSet* p = new (op_new(0x20, "Simulator", 0, 0, 0, 0)) PosseSet();
        SetC<PosseSet>(posse, p);
        posse->Init();
    }

    // global UI
    {
        void* mem = op_new(0x68, "Simulator/cSPGlobalUI-TribeUI", 0, 0, 0, 0);
        ui = mem ? ((TribeUI*)mem)->Ctor() : 0;
        ui->Setup(g_uiSetupArg);
        void* buf = ui->GetBuffer();

        Ornament* o = 0;
        void* m2 = op_new(0x38, "Simulator", 0, 0, 0, 0);
        if (m2) o = ((Ornament*)m2)->Ctor(buf, g_ornName);
        SetC<Ornament>(ornament, o);
        if (ornament) ornament->Post();
    }

    // mode strategy
    {
        void* mem = op_new(0xa8, "Simulator", 0, 0, 0, 0);
        ModeStrategy* m = mem ? ((ModeStrategy*)mem)->Ctor() : 0;
        SetA<ModeStrategy>(mode, m);
        mode->Setup();
        mode->SetFlag(0);
    }

    Window* w = ui->FindWindowByID(0x53f02b0);
    if (w) V2<void, int, int>(w, 0x7c, 1, 0);

    Window* w2 = ui->FindWindowByID(-1);
    TribeMode* inst = TribeModeInstance();
    V1<void, TMBase1*>(w2, 0x104, static_cast<TMBase1*>(inst));

    Window* w3 = ui->FindWindowByID(0x190722e);
    float* rp = V0<float*>(w3, 0x38);
    float rect[4];
    rect[0] = rp[0]; rect[1] = rp[1]; rect[2] = rp[2]; rect[3] = rp[3];

    {
        void* mem = AllocAligned(0x9a8, 8, "UI/CivMinimap", GetHeap());
        CivMinimap* mm = 0;
        if (mem) {
            Vec3 up = { 0.0f, 1.0f, 0.0f };
            Vec3 fwd = { 0.0f, 0.0f, -1.0f };
            mm = ((CivMinimap*)mem)->Ctor((int)(rect[3] - rect[1]), (int)(rect[2] - rect[0]), &fwd, &up, 0.0f, 0);
        }
        SetA<CivMinimap>(minimap, mm);
    }
    {
        void* sub = minimap ? (void*)((char*)minimap + 4) : 0;
        V1<void, void*>(w3, 0xd8, sub);
    }

    if (g_appProps->GetDescription(0x4da5b79)) {
        NounMgr* nm = NounManager();
        Tribe* t = nm->GetPlayerTribe();
        TribeData* td = t->GetThing(0);

        Window* a = ui->FindWindowByID(0x4da6498);
        SetA<Window>(swatchWin, a);

        void* smem = op_new(0x17c, "UI", 0, 0, 0, 0);
        Swatch* sw = smem ? ((Swatch*)smem)->Ctor() : 0;
        Swatch* made = SwatchManager()->CreateSwatch(sw);
        SetA<Swatch>(swatch, made);

        swatch->Init((char*)td + 0x504, swatchWin, 1, 1, 2, 0, -1);
        V1<void, int>(swatch, 0x2c, 1);
        swatch->F2240(1);
        swatch->F2250(0);
        swatch->F2d00(0x2481de5, 1);
    } else {
        Window* a = ui->FindWindowByID(0x4da6498);
        Window* b = ui->FindWindowByID(0x4da6948);
        if (a) V2<void, int, int>(a, 0x7c, 1, 0);
        if (b) V2<void, int, int>(b, 0x7c, 1, 0);
    }

    Window* w4 = ui->FindWindowByID(0x6454b47);
    if (w4) {
        V1<void, TMBase1*>(w4, 0x104, static_cast<TMBase1*>(inst));
        V2<void, int, int>(w4, 0x7c, 1, inst->Flag());
        Window* w5 = ui->FindWindowByID(0x652a628);
        V2<void, int, int>(w5, 0x7c, 1, inst->Flag());
    }

    Orn2** pp = inst->player;
    for (int n = 20; n != 0; --n, ++pp) {
        Orn2* o = *pp;
        if (!o) {
            o = NounManager()->Create(0x3a2511e, 0x99f41d70, 0, 0, 0);
            if (!o || o->NounType() != 0x3a2511e) o = 0;
            SetA<Orn2>(*pp, o);
        }
        o->f_a5 = 1;
        o->f_a9 = 0;
        o->flags |= 0x80;
    }
    pp = inst->npc;
    for (int n = 20; n != 0; --n, ++pp) {
        Orn2* o = *pp;
        if (!o) {
            o = NounManager()->Create(0x3a2511e, 0x99f41d70, 0, 0, 0);
            if (!o || o->NounType() != 0x3a2511e) o = 0;
            SetA<Orn2>(*pp, o);
        }
        o->f_a5 = 1;
        o->f_a9 = 0;
        o->flags |= 0x80;
    }

    for (int k = 0; k < 2; ++k) {
        ModelSet& s = sets[k];
        s.id = 0xa201658f;
        if (s.vec.b == s.vec.e) s.vec.Resize(0x28);
        for (u32 i = 0; i < (u32)(s.vec.e - s.vec.b); ++i) {
            Xform* t = &s.vec.b[i];
            for (int j = 0; j < 9; ++j) t->m[j] = g_xfMat[j];
            t->scale = 1.0f;
            t->pos[0] = g_xfPos.x; t->pos[1] = g_xfPos.y; t->pos[2] = g_xfPos.z;
            t->a = 0;
            t->b = 0;
        }
    }

    for (int k = 0; k < 2; ++k) sets[k].AddToRenderer(GetRenderer());
    MakeTribeIcons();

    Window* w6 = ui->FindWindowByID(0x562a0f7);
    Window* w7 = V2<Window*, u32, int>(w6, 0xf0, 0x562a2da, 1);
    if (w7) {
        u32* name = GetActivePlanet()->GetName();
        V1<void, u32>(w7, 0x80, *name);
    }
    helperA->Fn(0, 0);
    helperB->Fn(1, 0);
}

// ==== cursor strategy (cSPUITCCCursorStrategy, 0x00cce590 .. 0x00cceca0) =====

// ---- external objects (bodies masked: only the layout matters) --------------
int  __stdcall GetPauseGateCount(u32 gate);                          // 0x00b320d0 (ret 4)
void __cdecl EndBanMode(int on);                                     // 0x00dd1840 (ret 4)
void __cdecl ToggleBanningContent(int on);                           // 0x00dd17f0 (ret 4)
void __cdecl FUN_00e09a50(int on);                                   // 0x00e09a50 (ret 4)
void __cdecl FUN_00e099d0(int on);                                   // 0x00e099d0 (ret 4)
void __cdecl RemoveHandler(void* h, u32 a, u32 b, u32 c, u32 d);     // 0x00571db0 (ret 0x14)
void* __cdecl GetCurrentGameMode();                                  // 0x00b5b800

struct TerrainCursor                                                 // the hovered terrain cursor
{
    void SetMode(int mode);                                          // 0x00b2fba0 (ret 4)
};
TerrainCursor* __cdecl GetGameTerrainCursor();                       // 0x00b30d70

struct CameraCtl                                                     // SP::cTerrainCameraController
{
    char pad00[0x390];
    u8   mMode390;                                                   // +0x390
    void SetToggle(bool on);                                         // 0x00b0f950 (ret 4)
};
CameraCtl* __cdecl GetCameraCtl();                                   // 0x00b3d280

struct CardPanel                                                     // SP::cUIMissionCardPanel
{
    void SetCardsVisibility(int on);                                 // 0x00e14c10 (ret 4)
};
CardPanel* __cdecl GetCards();                                       // 0x00b3d400

struct CursorTable                                                   // SP::CursorTable
{
    u32 AddCursor(u32 id, const wchar_t* name, int a, int b, int c);  // 0x00802050 (ret 0x14)
};
CursorTable* __cdecl GetCursorTable();                               // 0x0067cab0

struct TcRefObj                                                      // refcounted helper (+0x5c, +0xc0)
{
    virtual void AddRef();                                           // +0x00
    virtual void Release();                                          // +0x04
    virtual void Slot8();                                            // +0x08
    virtual void Release3();                                         // +0x0c
    void Reset();                                                    // 0x00d12fc0
};

struct Stopwatch                                                     // EA::Stopwatch at +0xa8
{
    u32 mStart;                                                      // +0x00
    u32 mStop;                                                       // +0x04
    u32 mDelta;                                                      // +0x08
    u32 mPad;                                                        // +0x0c
    void Restart();                                                  // 0x00571e80
};

struct TcTerrain                                                     // the planet view at +0x40
{
    bool TerrainHasKey(u32 key);                                     // 0x00cd4460 (ret 4)
};

struct TcModeObject                                                  // result of view->vt[0x6c]
{
    u32 F00cc93b0(u32 v);                                            // 0x00cc93b0 (ret 4)
    char          pad00[0x50];
    ModeStrategy* mpMode;                                            // +0x50
    u8            mFlag54;                                           // +0x54
};

struct Citizen                                                       // SP::cSPCreatureCitizen
{
    void* GiveOrder(void* a, void* b, void* c);                      // 0x00c275b0 (ret 0xc)
};

struct PtrVec2 { void** mBegin; void** mEnd; };

u32 g_msgToken169b1c4;                                               // 0x0169b1c4

class cSPUITCCCursorStrategy
{
public:
    void RegisterCursors();                                          // 0x00cce610 (PDB candidate: ctor)
    void FUN_00cce5b0();                                             // 0x00cce5b0
    void FUN_00cce5e0();                                             // 0x00cce5e0
    void FUN_00cce940();                                             // 0x00cce940
    void FUN_00ccea10(void* obj, bool flag);                         // 0x00ccea10 (ret 8)
    u32  FUN_00cceae0(void* obj, u32 mode, void* arg3);              // 0x00cceae0 (ret 0xc)
    u32  FUN_00ccebd0(void* obj, int flag, void* arg3);              // 0x00ccebd0 (ret 0xc)
    void FUN_00ccec20(u32 flag);                                     // 0x00ccec20 (ret 4)
    u32  FUN_00cceca0(void* a, void* b);                             // 0x00cceca0 (ret 8)

    char       pad00[0x40];
    TcTerrain* mpTerrain;                                            // +0x40
    void*      mpHandler;                                            // +0x44
    u32        mH48;                                                 // +0x48
    u32        mH4c;                                                 // +0x4c
    u32        mH50;                                                 // +0x50
    u32        mH54;                                                 // +0x54
    u32        mPad58;                                               // +0x58
    TcRefObj*  mpRef5c;                                              // +0x5c
    char       pad60[0xa0 - 0x60];
    u32        mMode;                                                // +0xa0
    char       padA4[0xa8 - 0xa4];
    Stopwatch  mStop;                                                // +0xa8
    char       padB8[0xc0 - 0xb8];
    TcRefObj*  mpRefC0;                                              // +0xc0
};

// @ 0x00cce590
bool __cdecl FUN_00cce590()
{
    return GetPauseGateCount(0x64beb65) > 0;
}

// @ 0x00cce5b0
void cSPUITCCCursorStrategy::FUN_00cce5b0()
{
    if (mMode == 1) {
        mMode = 0;
        EndBanMode(1);
    } else {
        mMode = 1;
        ToggleBanningContent(1);
    }
}

// @ 0x00cce5e0
void cSPUITCCCursorStrategy::FUN_00cce5e0()
{
    if (mMode == 2) {
        mMode = 0;
        FUN_00e09a50(0);
    } else {
        mMode = 2;
        FUN_00e099d0(0);
    }
}

// @ 0x00cce610
void cSPUITCCCursorStrategy::RegisterCursors()
{
    CursorTable* t = GetCursorTable();
    t->AddCursor(0x3febe37, L"cursor-trg-tool-pickup-fish", 1, 0, 0);
    t->AddCursor(0x3febe38, L"cursor-trg-tool-pickup-gather", 1, 0, 0);
    t->AddCursor(0x63fe8d4, L"cursor_pickup-maracas", 1, 0, 0);
    t->AddCursor(0x63fe8d5, L"cursor_pickup-horn", 1, 0, 0);
    t->AddCursor(0x63fe8d6, L"cursor_pickup-didgeridoo", 1, 0, 0);
    t->AddCursor(0x63fe8d7, L"cursor_pickup-axe", 1, 0, 0);
    t->AddCursor(0x63fe8d8, L"cursor_pickup-spears", 1, 0, 0);
    t->AddCursor(0x63fe8d9, L"cursor_pickup-torch", 1, 0, 0);
    t->AddCursor(0x3febe3b, L"cursor_pickup-heal", 1, 0, 0);
    t->AddCursor(0x3febe3d, L"cursor-dance", 1, 0, 0);
    t->AddCursor(0x3febe33, L"cursor-heal", 1, 0, 0);
    t->AddCursor(0x3febe50, L"cursor-eat-carcass", 1, 0, 0);
    t->AddCursor(0x3febe51, L"cursor-eat-fruit", 1, 0, 0);
    t->AddCursor(0x3febe52, L"cursor-eat-omni", 1, 0, 0);
    t->AddCursor(0x3febe3f, L"cursor-fish", 1, 0, 0);
    t->AddCursor(0x3febe40, L"cursor-gather", 1, 0, 0);
    t->AddCursor(0x3febe42, L"cursor-steal", 1, 0, 0);
    t->AddCursor(0x3febe43, L"cursor_atk", 1, 0, 0);
    t->AddCursor(0x525ff0f, L"cursor_repair", 1, 0, 0);
    t->AddCursor(0x5498863, L"cursor-mate", 1, 0, 0);
    t->AddCursor(0x8b875bdc, L"cursor-crg-give-grn", 1, 0, 0);
    t->AddCursor(0xf59ce677, L"cursor-crg-give-grn-no", 1, 0, 0);
    t->AddCursor(0x57801b0, L"cur-planner", 1, 0, 0);
    t->AddCursor(0x3570021, L"cursor_atk", 1, 0, 0);
    t->AddCursor(0x3a204b0, L"cursor-no-opt", 1, 0, 0);
    t->AddCursor(0x3febe36, L"cursor-trg-tool-pickup-gather", 1, 0, 0);
    t->AddCursor(0x3febe41, L"cursor-more", 1, 0, 0);
    t->AddCursor(0x525ff7d, L"cursor_social", 1, 0, 0);
    t->AddCursor(0xe382f00e, L"cursor-trg-domesticate", 1, 0, 0);
    t->AddCursor(0x600cd69, L"cursor-camera-translate", 1, 0, 0);
}

// @ 0x00cce940
void cSPUITCCCursorStrategy::FUN_00cce940()
{
    if (mpRef5c) {
        mpRef5c->Reset();
        if (mpRef5c) {
            TcRefObj* old = mpRef5c;
            mpRef5c = 0;
            old->Release3();
        }
    }
    if (mpHandler) {
        void* h = mpHandler;
        mpHandler = 0;
        RemoveHandler(h, mH48, mH4c, mH50, mH54);
    }
    g_msgToken169b1c4 = 0;
    V3<void>(GetServer(), 0x14, 0x706bf688, 0, 0);
}

// @ 0x00cce9b0
u32 __stdcall FUN_00cce9b0(void** vec, void* a, void* b, void* c)
{
    void** it = (void**)vec[0];
    void** end = (void**)vec[1];
    if (it == end)
        return 1;
    do {
        void* o = *it;
        Citizen* cit = o ? (Citizen*)V1<void*>(o, 0xb8, (void*)0x4f176642) : 0;
        cit->GiveOrder(a, b, c);
        ++it;
    } while (it != end);
    return 0;
}

// @ 0x00ccea10
void cSPUITCCCursorStrategy::FUN_00ccea10(void* obj, bool flag)
{
    if ((GetCameraCtl() != 0 && GetCameraCtl()->mMode390 != 0) || flag) {
        mStop.mStart = 0;
        mStop.mStop = 0;
        mStop.mDelta = 0;
        mStop.mPad = 0;
        if (mpRefC0) {
            TcRefObj* old = mpRefC0;
            mpRefC0 = 0;
            old->Release();
        }
    } else {
        mStop.Restart();
        if (obj != 0) {
            TcRefObj* old = mpRefC0;
            if (obj != old) {
                ((TcRefObj*)obj)->AddRef();
                mpRefC0 = (TcRefObj*)obj;
                if (old)
                    old->Release();
            }
            if (V0<void*>(obj, 0x20) == (void*)0x18c88e4 && ((u32*)obj)[0x8a] == 0x356eb8a) {
                old = mpRefC0;
                if (old) {
                    mpRefC0 = 0;
                    old->Release();
                }
            }
        }
    }
}

// @ 0x00cceae0
u32 cSPUITCCCursorStrategy::FUN_00cceae0(void* obj, u32 mode, void* arg3)
{
    bool flag = false;
    switch (mode) {
    case 0:
        flag = true;
        break;
    case 1:
        GetGameTerrainCursor()->SetMode(2);
        break;
    case 2:
        GetGameTerrainCursor()->SetMode(0);
        break;
    case 3:
        GetGameTerrainCursor()->SetMode(1);
        break;
    }
    if (!mpTerrain->TerrainHasKey(0x56d1871)) {
        if (mpTerrain->TerrainHasKey(0x64be5ff)) {
            void* tribe = NounManager()->GetPlayerTribe();
            if (tribe) {
                PtrVec2* v = (PtrVec2*)V0<void*>(tribe, 0x94);
                u32 n = (u32)(v->mEnd - v->mBegin);
                for (u32 i = 0; i < n; ++i)
                    V1<void>(v->mBegin[i], 0x54, 0);
            }
        }
    }
    TerrainCursor* cur = GetGameTerrainCursor();
    void* v = obj ? V1<void*>(obj, 0xc, (void*)0x1186577) : 0;
    V2<void>(cur, 0xa0, flag, v);
    return 0;
}

// @ 0x00ccebd0
u32 cSPUITCCCursorStrategy::FUN_00ccebd0(void* obj, int flag, void* arg3)
{
    if (flag == 0)
        GetGameTerrainCursor()->SetMode(0);
    TerrainCursor* cur = GetGameTerrainCursor();
    void* v = obj ? V1<void*>(obj, 0xc, (void*)0x1186577) : 0;
    V2<void>(cur, 0x9c, 0, v);
    return 0;
}

// @ 0x00ccec20
void cSPUITCCCursorStrategy::FUN_00ccec20(u32 flag)
{
    if (GetCurrentGameMode() != (void*)0x1654c02)
        return;
    TcModeObject* mode = (TcModeObject*)V0<void*>(mpTerrain, 0x6c);
    mode->F00cc93b0(flag);
    if (GetCards())
        GetCards()->SetCardsVisibility((int)flag);
    if (mode->mpMode) {
        if (flag != 0) {
            if (mode->mFlag54)
                mode->mpMode->SetFlag(1);
        } else {
            mode->mFlag54 = mode->mpMode->GetFlag();
            mode->mpMode->SetFlag(0);
        }
    }
}

// @ 0x00cceca0
u32 cSPUITCCCursorStrategy::FUN_00cceca0(void* a, void* b)
{
    CameraCtl* cam = GetCameraCtl();
    if (cam == 0)
        return 0;
    if ((mStop.mStart | mStop.mStop) != 0) {
        cam->SetToggle(true);
        return 0;
    }
    cam->SetToggle(false);
    return 0;
}
