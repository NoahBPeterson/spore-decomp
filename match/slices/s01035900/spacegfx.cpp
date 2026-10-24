// Slice s01035900 targets (the committed s01035900.cpp holds the non-target
// 0x01035900 InitForGame):
//   010361c0  FUN_010361c0            universe-context switch
//   010362e0  FUN_010362e0            stop the effects, then activate graphics
//   010363a0  FUN_010363a0            render-window setup; tail-calls 010361c0
//   010364b0  FUN_010364b0            start the effects, drop the +0x90 object
//   01036590  FUN_01036590            attach a named effect object
//   01036610  FUN_01036610            SP::sCalcTiltAlpha
//   010367e0  FUN_010367e0            push a bool into every tree node's object
//
// Retail cSPSpaceGfx layout (subset used here) from the disassembly.
#include <stddef.h>
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

// objects created by the effects manager (AddRef +4, Release +8, act +0xc)
struct GfxObj { virtual void v00(); virtual void AddRef(); virtual void Release();
                virtual void Act(int state); };

// the "second" object family used by App()->[0x50](): Release +4, act +0xc
struct GfxObj2 { virtual void v00(); virtual void AddRef(); virtual void Release();
                 virtual void Act(int state); virtual void v10(); virtual void v14();
                 virtual void v18(); virtual void v1c(); virtual void v20();
                 virtual void Act9(int state);                          // +0x24
                 virtual void v28(); virtual void Get(int id, void* out);
                 virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
                 virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
                 virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
                 virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
                 virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
                 virtual void v80();
                 virtual void SetPair(void* a, void* b);                // +0x84
                 virtual void SetActive(int v); };                      // +0x88

// object whose slot-2 method takes an int (the +0x80 slot in the render manager)
struct GfxObjB { virtual void b00(); virtual void b04(); virtual void Do(int v); };

// object stored in the +0x90 slot and the +0xb0 lookup object
struct SlotObj  { virtual void s00(); virtual void Release(); };          // slot 1 = Release
struct LookupObj{ virtual void l00(); virtual void l04();
                  virtual bool Lookup(int name, int b, void** out); };    // slot 2
struct ActiveObj{ virtual void a00(); virtual void a04();
                  virtual void SetActive(int v); };                       // slot 2

// the render-window manager returned by FUN_0067dd50()
struct WinMgr {
    virtual void w00(); virtual void w04(); virtual void w08(); virtual void w0c();
    virtual void w10(); virtual void w14(); virtual void w18(); virtual void w1c();
    virtual void w20(); virtual void w24(); virtual void w28(); virtual void w2c();
    virtual void w30(); virtual void w34(); virtual void w38(); virtual void w3c();
    virtual void w40(); virtual void w44(); virtual void w48();
    virtual void Set(void* a, int b, int c);                     // +0x4c
    virtual void Do(int v);                                      // +0x50
};

struct cStar { int GetSolarSystem(); };
struct cSolarSystem { void ActivateGraphics(int on); };

// the property object returned by PropertyManager
struct Prop { virtual void p00(); virtual void Release(); virtual void p08(); virtual void p0c();
              virtual void p10(); virtual void p14(); virtual void p18(); virtual void p1c();
              virtual void p20();
              virtual bool GetProp(int id, void* out);                // +0x24
};

struct PropMgr2 { virtual void p00(); virtual void p04(); virtual void p08(); virtual void p0c();
                  virtual void p10(); virtual void p14(); virtual void p18(); virtual void p1c();
                  virtual void p20(); virtual void p24(); virtual void p28();
                  virtual bool Get(int a, int b, void** out);           // +0x2c
                  virtual void p30(); virtual void p34(); virtual void p38(); virtual void p3c();
                  virtual void p40(); virtual void p44(); virtual void p48(); virtual void* GetAppValue(); // +0x50
                  virtual void p54(); virtual void p58(); virtual void p5c();
                  virtual void Register(int a, int b, int c, int d);     // +0x4c
                  virtual void Set(int id); };                           // +0x50

struct AppRoot { virtual void a00(); virtual void a04(); virtual void a08(); virtual void a0c();
                 virtual void a10(); virtual void a14(); virtual void a18(); virtual void a1c();
                 virtual void a20(); virtual void a24(); virtual void a28(); virtual void a2c();
                 virtual void a30(); virtual void a34(); virtual void a38(); virtual void a3c();
                 virtual void a40(); virtual void a44(); virtual void a48(); virtual void a4c();
                 virtual void* GetWorld();                                   // +0x50
                 virtual uint32_t GetModeId(); };                            // +0x54  (unused)

struct WorldObj { virtual void w00(); virtual void w04(); virtual void w08(); virtual void w0c();
                  virtual void w10(); virtual void w14(); virtual void w18(); virtual void w1c();
                  virtual void w20(); virtual void w24(); virtual void w28(); virtual void w2c();
                  virtual void* GetSub(); };                                 // +0x38

// the "render manager" returned by FUN_00b3d470()
struct RenderMgr {
    uint8_t  pad00[0x60];
    GfxObj*  mpA60;                                              // +0x60
    GfxObj*  mpA64;                                              // +0x64
    GfxObj*  mpA68;                                              // +0x68
    uint32_t m6c;                                                // +0x6c  (loaded flag)
    GfxObj*  mpA70;                                              // +0x70
    uint32_t m74;                                                // +0x74 (not touched)
    GfxObj*  mpA78;                                              // +0x78
    GfxObj*  mpA7c;                                              // +0x7c
    GfxObj*  mpA80;                                              // +0x80
    GfxObj*  mpA84;                                              // +0x84
    GfxObj*  mpA88;                                              // +0x88
    uint8_t  pad8c[0x94 - 0x8c];
    GfxObj2* mpA94;                                              // +0x94
    GfxObj*  mpA98;                                              // +0x98
    GfxObj2* mpA9c;                                              // +0x9c
    GfxObj2* mpAa0;                                              // +0xa0
    GfxObj*  mpAa4;                                              // +0xa4
    uint8_t  pada8[0xac - 0xa8];
    GfxObj*  mpAac;                                              // +0xac
    GfxObj*  mpAb0;                                              // +0xb0
};

// cSPSpaceGfx subject object: +0x40 tree sentinel, +0x44 tree head, +0x58 bool,
// +0x90 effect slot.  (Only the fields touched here are named.)
struct GfxNode { uint8_t pad00[0x14]; void** mppObject; };

class cSPSpaceGfx {
public:
    uint8_t  pad00[0x40];
    uint8_t  mTree[0x18];                                        // +0x40 .. +0x58
    char     mbFlag58;                                           // +0x58
    uint8_t  pad59[0x90 - 0x59];
    void*    mpEffect90;                                         // +0x90
    GfxObj*  mpA94;                                              // +0x94
    GfxObj*  mpA98;                                              // +0x98
    GfxObj2* mpA9c;                                              // +0x9c
    GfxObj2* mpAa0;                                              // +0xa0  (unused here; render mgr has the real one)
    GfxObj*  mpAa4;                                              // +0xa4
    uint8_t  pada8[0xac - 0xa8];
    GfxObj*  mpAac;                                              // +0xac
    GfxObj*  mpAb0;                                              // +0xb0

    void FUN_010363a0();                                         // 0x010363a0
    void FUN_010364b0();                                         // 0x010364b0
    void FUN_01036590(void* arg);                                // 0x01036590
    void FUN_010367e0(char v);                                   // 0x010367e0
};

// externals
extern RenderMgr* FUN_00b3d470();                                 // 0x00b3d470
extern AppRoot* SP_App();                                        // 0x67dd10
extern void* FUN_0067dd50();                                     // 0x67dd50 -> render-window mgr
extern PropMgr2* SP_PropertyManager();                           // 0x67de30
extern int   FUN_01021230();                                     // 0x01021230
extern int   cStar_GetSolarSystem(int star);                     // 0x00c8b770
extern void  cSolarSystem_ActivateGraphics(int ss, int on);      // 0x00c86c70
// render-manager API whose methods take `this` in ecx (the standalone thunks)
struct RenderMgrApi { int Setup(int a, int b); };                // 0x01034950
struct Planet { int GetPlanetType(); };                          // 0x00c70880
extern Planet* FUN_01021260();                                   // 0x01021260
extern int   FUN_01021280();                                     // 0x01021280 (GetUniverseContext)
extern int   FUN_00c707f0(int a);                                // 0x00c707f0
extern int   SP_GetCurrentGameMode();                            // 0x00b5b800
extern void* RBTreeIncrement(void* node);                        // 0x00921580
extern int   SP_GetUniverseContext();                            // 0x01021080
extern int   SP_GetActivePlanet();                               // 0x01021080 family
extern int   SimGetNameRow(int a);                               // 0x00c707f0
extern bool  RBTreeIncrement_advance(void* node, void** out);    // 0x921580
extern void* RBTreeIncrement(void* node);                        // 0x0921580
extern float PropertyGetFloat(void* prop);                       // 0x41ea70

extern float  s_fConst90;                                        // 0x13ec4d8
extern float  s_fDegToRad;                                       // 0x14998dc
extern void*  s_pTreeRoot;                                       // 0x15b7840
extern void*  s_pTreeRoot2;                                      // 0x15b7844
#define GAME_MODE_TAG 0x1654c05

void FUN_010362e0();                                             // fwd (0x010362e0)
void FUN_010361c0();                                             // fwd (0x010361c0)

// @ 0x010361c0
void FUN_010361c0()
{
    switch (FUN_01021280()) {
    case 0:
        ((RenderMgrApi*)FUN_00b3d470())->Setup(1, ((Planet*)FUN_01021260())->GetPlanetType());
        break;
    case 1:
        ((RenderMgrApi*)FUN_00b3d470())->Setup(2, -1);
        break;
    case 2: {
        RenderMgr* r = FUN_00b3d470();
        if (r->m6c != 0) {
            r->mpA60->Act(1);
            r->mpA64->Act(1);
            GfxObj* p68 = r->mpA68;
            if (p68 != 0)
                p68->Act(1);
            r->mpA70->Act(1);
            r->mpA78->Act(1);
            r->mpA7c->Act(1);
            ((GfxObjB*)r->mpA80)->Do(0);
            r->mpA84->Act(1);
            r->mpA88->Act(1);
            r->mpA98->Act(2);
        }
        GfxObj* o = FUN_00b3d470()->mpAac;
        o->Act(0);
        return;
    }
    default:
        return;
    }

    int star = FUN_01021230();
    if (star != 0) {
        int ss = ((cStar*)star)->GetSolarSystem();
        if (ss != 0)
            ((cSolarSystem*)ss)->ActivateGraphics(1);
    }
}

// @ 0x010362e0
void FUN_010362e0()
{
    RenderMgr* r = FUN_00b3d470();
    if (r->m6c != 0) {
        r->mpA60->Act(1);
        r->mpA64->Act(1);
        GfxObj* p68 = r->mpA68;
        if (p68 != 0)
            p68->Act(1);
        r->mpA70->Act(1);
        r->mpA78->Act(1);
        r->mpA7c->Act(1);
        ((GfxObjB*)r->mpA80)->Do(0);
        r->mpA84->Act(1);
        r->mpA88->Act(1);
        r->mpA98->Act(2);
    }
    int star = FUN_01021230();
    if (star != 0) {
        int ss = ((cStar*)star)->GetSolarSystem();
        if (ss != 0)
            ((cSolarSystem*)ss)->ActivateGraphics(0);
    }
}

// @ 0x010363a0
void cSPSpaceGfx::FUN_010363a0()
{
    ((WinMgr*)FUN_0067dd50())->Set((void*)0x15b7840, 5, 0);
    ((WinMgr*)FUN_0067dd50())->Set((void*)0x15b7840, 0xd, 0);
    ((WinMgr*)FUN_0067dd50())->Set((void*)0x15b7840, 4, 0);
    ((WinMgr*)FUN_0067dd50())->Set((void*)0x15b7840, 6, 0);

    mpA94->Act(0);
    mpA98->Act(0);
    mpA9c->Act(0);
    mpAa4->Act(0);
    mpAb0->Act(0);

    AppRoot* app = SP_App();
    GfxObj2* obj = (GfxObj2*)FUN_00b3d470()->mpAa0;
    obj->SetPair((void*)0x15b7844, app->GetWorld());

    FUN_00b3d470()->mpA9c->Act9(2);

    if (SP_GetCurrentGameMode() == GAME_MODE_TAG)
        return;
    FUN_010361c0();
}

// @ 0x010364b0
void cSPSpaceGfx::FUN_010364b0()
{
    if (SP_GetCurrentGameMode() != GAME_MODE_TAG)
        FUN_010362e0();

    ((WinMgr*)FUN_0067dd50())->Do(5);
    ((WinMgr*)FUN_0067dd50())->Do(0xd);
    ((WinMgr*)FUN_0067dd50())->Do(4);
    ((WinMgr*)FUN_0067dd50())->Do(6);

    mpA94->Act(2);
    mpA98->Act(2);
    mpA9c->Act(2);
    mpAa4->Act(2);
    mpAac->Act(2);
    mpAb0->Act(2);

    if (mpEffect90 != 0) {
        ((GfxObj*)mpEffect90)->Act(1);
        SlotObj* p = (SlotObj*)mpEffect90;
        if (p != 0) {
            mpEffect90 = 0;
            p->Release();
            return;
        }
    }
}

// @ 0x01036590
void cSPSpaceGfx::FUN_01036590(void* arg)
{
    if (arg == 0)
        return;
    int name = FUN_00c707f0(1);
    if (name == 0)
        return;

    RenderMgr* r = FUN_00b3d470();
    LookupObj* obj = (LookupObj*)r->mpAb0;
    SlotObj* old = (SlotObj*)mpEffect90;
    if (old != 0) {
        mpEffect90 = 0;
        old->Release();
    }
    if (!obj->Lookup(name, 0, &mpEffect90))
        return;
    ((ActiveObj*)mpEffect90)->SetActive(0);
}

// @ 0x01036610
float FUN_01036610()
{
    AppRoot* app = SP_App();
    void* w = app->GetWorld();
    void* sub = ((void*(*)()) ((void**)*(void**)w)[0x38 / 4])();
    if (sub == 0)
        return 1.0f;
    int obj = ((int(*)(void*, int))((void**)*(void**)sub)[0xc / 4])(sub, 0x303154cc);
    if (obj == 0)
        return 1.0f;

    Prop* prop = 0;
    PropMgr2* pm = SP_PropertyManager();
    if (prop != 0) {
        prop = 0;
        prop->Release();
    }
    pm->Get(0x521d0174, 0x2ae0c7e, (void**)&prop);
    if (prop == 0)
        return 1.0f;

    float a = 0.0f, b = 0.0f, c = 1.0f;
    void* out;
    if (prop->GetProp(0x195a040, &out) && out != 0)
        a = PropertyGetFloat(out);

    if (prop->GetProp(0x195a041, &out) && out != 0)
        b = PropertyGetFloat(out);

    a = (s_fConst90 - a) * s_fDegToRad;
    b = (s_fConst90 - b) * s_fDegToRad;

    if (prop->GetProp(0x195a042, &out) && out != 0)
        c = PropertyGetFloat(out);

    float t = (*(float*)(obj + 0x70) - a) * c;
    t = t / (b - a);
    float zero = 0.0f;
    if (t < zero)
        t = zero;
    if (c < t)
        t = c;

    if (prop != 0)
        prop->Release();

    return t;
}

// @ 0x010367e0
void cSPSpaceGfx::FUN_010367e0(char v)
{
    if (v == mbFlag58)
        return;
    GfxNode* node = *(GfxNode**)&mTree[4];                       // +0x44
    GfxNode* sentinel = (GfxNode*)&mTree[0];                     // +0x40
    mbFlag58 = v;
    while (node != sentinel) {
        void** pp = node->mppObject;
        void* o = *pp;
        ((void(*)(void*, int))((void**)*(void**)o)[0x16c / 4])(pp, v);
        node = (GfxNode*)RBTreeIncrement(node);
    }
}
