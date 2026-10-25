// Slice s00ffc230 -- space-game player-UFO simulator glue: teardown, travel
// destination, civ distance/discount, mission reachability, star picking.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"
#include <math.h>

// ---------------------------------------------------------------- globals
extern float          g_onef;        // 0x01485720  1.0f
extern float          g_epsf;        // 0x014950e4  1.5258789e-05f
extern float          g_smallf;      // 0x013f9428  1.0e-3f
extern float          g_vecA[3];     // 0x016dba18  reference point
extern float          g_vecPrev[3];  // 0x016dc0e8  last camera point
extern unsigned       g_vecInit;     // 0x016dc0f4  camera-point initialised flag
extern unsigned char  g_flag15b7434; // 0x015b7434  force star update
extern float          g_c15b6220;    // 0x015b6220
extern float          g_c15b6224;    // 0x015b6224
extern float          g_c15b6228;    // 0x015b6228
extern float          g_c15b622c;    // 0x015b622c
extern float          g_c15b6230;    // 0x015b6230
extern float          g_c15b6234;    // 0x015b6234
extern float          g_c15b6238;    // 0x015b6238
extern float          g_c15b623c;    // 0x015b623c
extern float          g_c15b6240;    // 0x015b6240
extern void*          g_player16dba14; // 0x016dba14  current player
extern int            g_id16dba9c;   // 0x016dba9c
extern int            g_id16dbaa8;   // 0x016dbaa8
extern int            g_id16dbab4;   // 0x016dbab4
extern int            g_id16dbac0;   // 0x016dbac0
extern int            g_id16dbacc;   // 0x016dbacc
extern int            g_id16dbad8;   // 0x016dbad8
extern int            g_id16dbae4;   // 0x016dbae4
extern int            g_id16dbaf0;   // 0x016dbaf0
extern int            g_id16dbafc;   // 0x016dbafc
extern int            g_id16dbb08;   // 0x016dbb08
extern int            g_id16dbb14;   // 0x016dbb14

struct Vec3 { float x, y, z; };

// ---------------------------------------------------------------- callees
void*  __cdecl App();                                // 0x0067dd10
void*  __cdecl FUN_01021300();                       // 0x01021300  GetPlayerEmpire
void*  __cdecl FUN_01021240();                       // 0x01021240  GetActivePlanet
void*  __cdecl FUN_01021260();                       // 0x01021260  GetActivePlanet
void*  __cdecl FUN_01021230();                       // 0x01021230
int    __cdecl FUN_01021080();                       // 0x01021080  GetUniverseContext
void*  __cdecl FUN_0102f810();                       // 0x0102f810  economy tuning
void*  __cdecl FUN_01002bd0();                       // 0x01002bd0  SpaceGameGet
void*  __cdecl FUN_00b3d2a0();                       // 0x00b3d2a0  travel tuning
void*  __cdecl FUN_00b3d300(unsigned);               // 0x00b3d300  NounManager
void*  __cdecl FUN_00b3d380();                       // 0x00b3d380  GameTimeManager
void*  __cdecl FUN_00b3d4d0();                       // 0x00b3d4d0  current context
void*  __cdecl FUN_00feb9f0();                       // 0x00feb9f0  GetMissionManager
void*  __cdecl FUN_00c37360();                       // 0x00c37360  universe scale
float  __cdecl FUN_00c376b0();                       // 0x00c376b0
float  __cdecl FUN_0104be30(void* ecx);              // 0x0104be30  handler value
float  __fastcall FUN_01017240(void* self);          // 0x01017240
float  __fastcall FUN_01017220(void* self);          // 0x01017220
bool   __fastcall FUN_01017f20(void* self);          // 0x01017f20
void   __fastcall FUN_0101b9e0(void* self);          // 0x0101b9e0
void*  __fastcall FUN_00a1ad60(void* self);          // 0x00a1ad60  player inventory
int    __fastcall FUN_00bb9ae0(void* self);          // 0x00bb9ae0
void*  __fastcall FUN_00b1fdb0(void* self);          // 0x00b1fdb0  GetAvatar
float  __fastcall FUN_0102fd40(void* self);          // 0x0102fd40  colony discount
float  __fastcall FUN_0102fd90(void* self);          // 0x0102fd90  alliance discount
float  __fastcall FUN_0102fcf0(void* self);          // 0x0102fcf0  travel rate
bool   __fastcall FUN_00c772c0(void* self);          // 0x00c772c0  in-terrain-sphere test
void*  __fastcall FUN_00f67d90(void* self);          // 0x00f67d90  terrain sphere
bool   __fastcall FUN_00feba90(void* self);          // 0x00feba90  IsRunning
void*  __fastcall FUN_00c30c60(void* self);          // 0x00c30c60  player's civ
void*  __fastcall FUN_00c5f3d0(void* self);          // 0x00c5f3d0
void*  __fastcall FUN_00b8de30(void* self);          // 0x00b8de30
int    __fastcall FUN_00c8b550(void* self);          // 0x00c8b550
bool   __fastcall FUN_00ac80f0(void* self);          // 0x00ac80f0
int    __fastcall FUN_00801920(void* self);          // 0x00801920

float  __cdecl FUN_010434e0(void* a, void* b);       // 0x010434e0  distance
float  __cdecl FUN_010434c0(void* a, void* b);       // 0x010434c0  distance
float  __cdecl FUN_010434c0(void* a, float* b);      // 0x010434c0  distance to point
void   __cdecl FUN_0105c3d0(float* out, void* obj, float t);   // 0x0105c3d0
void   __cdecl FUN_0105c5d0(float* out, void* obj, float t);   // 0x0105c5d0
void   __cdecl FUN_0105f760(void* game, float a, float b);      // 0x0105f760
float  __cdecl FUN_00b0f060(float a, float b, float c);         // 0x00b0f060
int    __cdecl FUN_011e0810(float v);                           // 0x011e0810  float->int helper

// ---------------------------------------------------------------- interfaces
struct ICloseable {
    virtual void p00();                    // +0x00
    virtual void Release();                // +0x04
    virtual void p08();                    // +0x08
    virtual void SetVisible(bool on);      // +0x0c
    virtual bool IsVisible();              // +0x10
};

struct IItemIface {
    virtual void p00();                    // +0x00
    virtual void p04();                    // +0x04
    virtual void p08();                    // +0x08
    virtual void* Get(unsigned id);        // +0x0c
};

struct InventoryItem {
    char       pad00[0x0c];
    IItemIface iface;                      // +0x0c  embedded interface (vptr)
};

struct IObj {                              // object carrying a world position
    virtual void p00();                    // +0x00
    virtual void p04();
    virtual void p08();
    virtual void p0c();
    virtual void p10();
    virtual void p14();
    virtual void p18();
    virtual void p1c();
    virtual void p20();
    virtual void p24();
    virtual void p28();
    virtual float* GetPos();               // +0x2c
    virtual void p30();                    // +0x30
    virtual void p34();                    // +0x34
    virtual void SetPos(float* p);         // +0x38
};

struct INounB {
    virtual void p00();                    // +0x00
    virtual void p04();                    // +0x04
    virtual void p08();                    // +0x08
    virtual void* Find(unsigned id);       // +0x0c
};

struct IMgrA {
    virtual void p00();                    // +0x00
    virtual void p04();
    virtual void p08();
    virtual void p0c();
    virtual void p10();
    virtual void p14();
    virtual void p18();
    virtual void p1c();
    virtual void p20();
    virtual void p24();
    virtual void p28();
    virtual void p2c();
    virtual void p30();
    virtual void p34();
    virtual INounB* GetNounMgr();          // +0x38
};

struct IViewer {
    void GetCameraLocationInfo();          // 0x007c3d30
};

struct IApp {
    virtual void p00();                    // +0x00
    virtual void p04();
    virtual void p08();
    virtual void p0c();
    virtual void p10();
    virtual void p14();
    virtual void p18();
    virtual void p1c();
    virtual void p20();
    virtual void p24();
    virtual void p28();
    virtual void p2c();
    virtual void p30();
    virtual void p34();
    virtual void p38();
    virtual void p3c();
    virtual void p40();
    virtual void p44();
    virtual void p48();
    virtual void p4c();
    virtual IMgrA* GetMgrA();              // +0x50
    virtual void p54();                    // +0x54
    virtual IViewer* GetViewer(float* out, int, int, int); // +0x58
};

struct IInventory {
    virtual void p00();                    // +0x00
    virtual void p04();
    virtual void p08();
    virtual void p0c();
    virtual void p10();
    virtual void p14();
    virtual void p18();
    virtual void p1c();
    virtual void p20();
    virtual void p24();
    virtual void p28();
    virtual void p2c();
    virtual void p30();
    virtual void p34();
    virtual void p38();
    virtual void p3c();
    virtual void p40();
    virtual void p44();
    virtual void p48();
    virtual void p4c();
    virtual void p50();
    virtual void p54();
    virtual void p58();
    virtual void p5c();
    virtual void p60();
    virtual void p64();
    virtual void* FindItem(void* id);      // +0x68
};

struct IMission {
    virtual void p00();                    // +0x00
    virtual void p04();                    // +0x04
    virtual void p08();                    // +0x08
    virtual void* Get(unsigned id);        // +0x0c
};

struct IMissionMgr {
    void* GetMissionByID(unsigned id);     // 0x00fee480
};

struct ICiv {
    void* GetCities();                     // 0x005c65e0  -> this + 0x3c
};

struct IEmpire {
    bool IsColony(void* nounMgr);          // 0x00c31470
    bool HasAvatar(void* avatar);          // 0x00c31bf0
};

// ---------------------------------------------------------------- game objects
struct Timer {
    void Reset();                          // 0x00bc3170
};

struct Sub508 {
    void f(int arg);                       // 0x00bfc470
};

struct SpaceGame {
    char          pad00[0x34];
    IObj          view;                    // +0x34  embedded view object (vptr)
    char          pad38[0x508 - 0x38];
    Sub508        sub508;                  // +0x508
    char          pad509[0x608 - 0x509];
    unsigned char b608;                    // +0x608
    char          pad609[0x624 - 0x609];
    unsigned char b624;                    // +0x624
    char          pad625[0x688 - 0x625];
    unsigned char b688;                    // +0x688
    unsigned char b689;                    // +0x689
    char          pad68a[0x6d0 - 0x68a];
    Timer         t6d0;                    // +0x6d0
    char          pad6d1[0x6f0 - 0x6d1];
    Timer         t6f0;                    // +0x6f0
    char          pad6f1[0x718 - 0x6f1];
    float         posX;                    // +0x718
    float         posY;                    // +0x71c
    float         posZ;                    // +0x720
    char          pad724[0x740 - 0x724];
    float         offX;                    // +0x740
    float         offY;                    // +0x744
    float         offZ;                    // +0x748
    unsigned char mode74c;                 // +0x74c
    char          pad74d[0x760 - 0x74d];
    void*         p760;                    // +0x760

    void  MoveTo(float* p);                // 0x00c381e0
    void  setup(int a, int b);             // 0x00c389c0
    float time();                          // 0x00c3ae70
    void  update();                        // 0x00c3b3f0
    bool  testA();                         // 0x00c37170
    bool  testB();                         // 0x00c372b0
    void  launch(float* p);                // 0x00c3be70
};

struct StarRecord {
    char           pad00[0x04];
    unsigned       flags;                  // +0x04
    char           pad08[0x0a - 0x08];
    unsigned short counter;                // +0x0a
    float          f0c;                    // +0x0c
    float          f10;                    // +0x10
    float          f14;                    // +0x14
    float          f18;                    // +0x18
    char           pad1c[0x64 - 0x1c];
    IItemIface*    p64;                    // +0x64
};

namespace SP {
struct cSPSimulatorPlayerUFO {
    char        pad00[0x1c];
    void*       mHandler;                  // +0x1c  auto-message handler
    char        pad20[0x40 - 0x20];
    SpaceGame*  mpGame;                    // +0x40
    char        pad44[0x58 - 0x44];
    StarRecord** mpStars;                  // +0x58  array of star-record pointers
    char        pad5c[0xa8 - 0x5c];
    ICloseable* pA8;                       // +0xa8
    ICloseable* pAC;                       // +0xac
    ICloseable* pB0;                       // +0xb0
    ICloseable* pB4;                       // +0xb4
    char        padb8[0xd8 - 0xb8];
    int         pD8;                       // +0xd8
    ICloseable* pDC;                       // +0xdc

    void  SetPlanetDestination(float* dest, unsigned char a, unsigned char b,
                               unsigned char c, unsigned char d);
    void  CalcMaxTravelDistance();
    float ScaledTravelTime(void* param);
    bool  CanReach(ICiv* civ);
    void  Update(float param);
    void  GetStarRecordUnderMouse();
};
}

// ---------------------------------------------------------------- 0x00ffc230
// @ 0x00ffc230
void __fastcall FUN_00ffc230(SP::cSPSimulatorPlayerUFO* p)
{
    if (p->pDC != 0) {
        ICloseable* obj = p->pDC;
        p->pDC = 0;
        obj->Release();
    }
    if (p->pB0 != 0 && p->pB0->IsVisible())
        p->pB0->SetVisible(true);
    if (p->pB4 != 0 && p->pB4->IsVisible())
        p->pB4->SetVisible(true);
    p->mpGame->sub508.f(0);
    p->mpGame->t6d0.Reset();
    p->mpGame->setup(1, 0);
    p->mpGame->t6f0.Reset();
}

// ---------------------------------------------------------------- 0x00ffc350
// @ 0x00ffc350
void SP::cSPSimulatorPlayerUFO::SetPlanetDestination(float* dest, unsigned char a,
                                                     unsigned char b, unsigned char c,
                                                     unsigned char d)
{
    float dot = dest[0] * dest[0] + dest[1] * dest[1] + dest[2] * dest[2];
    if (dot >= g_epsf && mpGame->testA()) {
        IApp*  app  = (IApp*)App();
        IMgrA* mgr  = app->GetMgrA();
        INounB* noun = mgr->GetNounMgr();
        void*  found;
        if (noun == 0)
            found = 0;
        else
            found = noun->Find(0x303154cd);

        SpaceGame* g = mpGame;
        float x = g->posX, y = g->posY, z = g->posZ;
        if (found == 0 ||
            sqrt(x * x + y * y + z * z) <= FUN_01017240(found)) {
            mpGame->launch(dest);
            mpGame->b608 = a;
            mpGame->b624 = b;
            mpGame->b688 = c;
            mpGame->b689 = d;
            if (found != 0)
                FUN_0101b9e0(found);
        }
    }
}

// ---------------------------------------------------------------- 0x00ffc490
// @ 0x00ffc490
float __stdcall FUN_00ffc490(ICiv* a, ICiv* b)
{
    float f = FUN_010434e0(a->GetCities(), b->GetCities());
    return f > 1.0f ? f : 1.0f;
}

// ---------------------------------------------------------------- 0x00ffc4e0
// @ 0x00ffc4e0
void __stdcall FUN_00ffc4e0(ICiv* self, void* nounMgr)
{
    void*  empire = FUN_01021300();
    float  discount;
    if (empire != 0) {
        if (((IEmpire*)empire)->IsColony(nounMgr)) {
            discount = FUN_0102fd40(FUN_0102f810());
        } else if (FUN_00bb9ae0(nounMgr) == 5) {
            void* avatar = FUN_00b1fdb0(nounMgr);
            if (((IEmpire*)empire)->HasAvatar(avatar))
                discount = FUN_0102fd90(FUN_0102f810());
            else
                discount = g_onef;
        } else {
            discount = g_onef;
        }
    } else {
        discount = g_onef;
    }

    void* cities2 = ((ICiv*)nounMgr)->GetCities();
    void* cities1 = self->GetCities();
    float dist    = FUN_010434e0(cities1, cities2);
    float chosen  = dist > g_onef ? dist : g_onef;
    float product = FUN_0102fcf0(FUN_0102f810()) * discount * chosen;
    FUN_011e0810(product);
}

// ---------------------------------------------------------------- 0x00ffc5b0
// @ 0x00ffc5b0
int __fastcall FUN_00ffc5b0(SP::cSPSimulatorPlayerUFO* p)
{
    if (p->mpGame->testB()) {
        float* pos = p->mpGame->view.GetPos();
        float  d   = sqrt(pos[0] * pos[0] + pos[1] * pos[1] + pos[2] * pos[2]);
        return d > FUN_00c376b0() ? 1 : 0;
    }

    IApp*  app  = (IApp*)App();
    IMgrA* mgr  = app->GetMgrA();
    INounB* noun = mgr->GetNounMgr();
    if (noun != 0) {
        void* found = noun->Find(0x303154cd);
        if (found != 0) {
            void*     tm = FUN_00b3d380();
            SpaceGame* g = ((SP::cSPSimulatorPlayerUFO*)g_player16dba14)->mpGame;
            float x = g->posX, y = g->posY, z = g->posZ;
            if (((*(unsigned char*)((char*)tm + 0x48)) & 1) == 0) {
                float limit = FUN_01017220(found);
                float d     = sqrt(x * x + y * y + z * z);
                if (limit < d) {
                    if (FUN_01017f20(found))
                        return 1;
                }
            }
        }
    }
    return 0;
}

// ---------------------------------------------------------------- 0x00ffc6d0
// @ 0x00ffc6d0
void SP::cSPSimulatorPlayerUFO::CalcMaxTravelDistance()
{
    void* sg = FUN_01002bd0();
    if (sg != 0) {
        IInventory* inv = (IInventory*)FUN_00a1ad60(sg);
        if (inv != 0) {
            void* item = 0;
            if (item == 0) item = inv->FindItem(&g_id16dbb14);
            if (item == 0) item = inv->FindItem(&g_id16dbb08);
            if (item == 0) item = inv->FindItem(&g_id16dbafc);
            if (item == 0) item = inv->FindItem(&g_id16dbaf0);
            if (item == 0) item = inv->FindItem(&g_id16dbae4);
            if (item == 0) item = inv->FindItem(&g_id16dbad8);
            if (item == 0) item = inv->FindItem(&g_id16dbacc);
            if (item == 0) item = inv->FindItem(&g_id16dbac0);
            if (item == 0) item = inv->FindItem(&g_id16dbab4);
            if (item == 0) item = inv->FindItem(&g_id16dbaa8);
            if (item == 0) item = inv->FindItem(&g_id16dba9c);
            if (item != 0) {
                mHandler = ((InventoryItem*)item)->iface.Get(0x707459f0);
                return;
            }
        }
    }
    mHandler = 0;
}

// ---------------------------------------------------------------- 0x00ffc7f0
// @ 0x00ffc7f0
float SP::cSPSimulatorPlayerUFO::ScaledTravelTime(void* param)
{
    if (mHandler == 0) {
        CalcMaxTravelDistance();
        if (mHandler == 0)
            return 0.0f;
    }
    float t = FUN_0104be30(mHandler);

    void* nounMgr = FUN_00b3d300(0x61f1454);
    void* sphere  = FUN_00f67d90(nounMgr);
    if (!FUN_00c772c0(sphere)) {
        void* info = FUN_00b3d2a0();
        float d    = FUN_010434e0(param, &g_vecA);
        if (d < *(float*)((char*)info + 0x1d0)) {
            void* info2 = FUN_00b3d2a0();
            float a     = *(float*)((char*)info2 + 0x1c8);
            if (a < t) {
                float r = FUN_00b0f060(*(float*)((char*)info + 0x1cc),
                                       *(float*)((char*)info + 0x1d0), d);
                return r * (t - a) + a;
            }
        }
    }
    return t;
}

// ---------------------------------------------------------------- 0x00ffc8d0
// @ 0x00ffc8d0
bool SP::cSPSimulatorPlayerUFO::CanReach(ICiv* civ)
{
    if (FUN_00feba90(FUN_00feb9f0())) {
        void*  planet  = FUN_01021240();
        void*  pcities = ((ICiv*)planet)->GetCities();
        void*  ccities = civ->GetCities();
        float  f1      = ScaledTravelTime(pcities);
        float  f2      = ScaledTravelTime(ccities);
        float  mx      = f1 > f2 ? f1 : f2;
        float  sq      = mx * mx;
        float  d1      = FUN_010434c0(ccities, pcities);
        SpaceGame* g   = mpGame;
        if (g->mode74c == 0) {
            float d2 = FUN_010434c0(civ->GetCities(), &g->posX);
            if (sq < d1)
                return false;
            if (sq < d2)
                return false;
            return true;
        }
        if (sq < d1)
            return false;
        return true;
    }

    void*  mission = ((IMissionMgr*)FUN_00feb9f0())->GetMissionByID(0x7bdbb97d);
    void*  x;
    if (mission == 0)
        x = 0;
    else
        x = ((IMission*)mission)->Get(0x422227e);

    void* empire = FUN_00c30c60(FUN_01021300());
    if (civ == empire)
        return true;
    if (x != 0) {
        void* a = FUN_00c5f3d0(x);
        void* b = FUN_00b8de30(a);
        if (civ == b)
            return true;
    }
    return false;
}

// ---------------------------------------------------------------- 0x00ffca20
// @ 0x00ffca20
void __fastcall FUN_00ffca20(SP::cSPSimulatorPlayerUFO* p)
{
    if (p->pA8 != 0 && p->pA8->IsVisible()) {
        p->pA8->SetVisible(true);
        if (p->pA8 != 0) {
            ICloseable* obj = p->pA8;
            p->pA8 = 0;
            obj->Release();
        }
    }
    if (p->pAC != 0 && p->pAC->IsVisible()) {
        p->pAC->SetVisible(true);
        if (p->pAC != 0) {
            ICloseable* obj = p->pAC;
            p->pAC = 0;
            obj->Release();
        }
    }
}

// ---------------------------------------------------------------- 0x00ffcab0
// @ 0x00ffcab0
void SP::cSPSimulatorPlayerUFO::Update(float param)
{
    mpGame->update();
    int ctx = FUN_01021080();

    if (ctx == 0) {
        mpGame->MoveTo(g_vecA);
        return;
    }

    if (ctx == 1) {
        void* planet = FUN_01021260();
        if (planet == 0)
            return;
        float t = mpGame->time();
        Vec3  p;
        FUN_0105c3d0(&p.x, planet, t);
        SpaceGame* g = mpGame;
        if (g->mode74c == 0) {
            void* target = g->p760;
            if (target == 0 || planet == target) {
                float* pp = ((IObj*)planet)->GetPos();
                float  dx = pp[0] - g->posX;
                float  dy = pp[1] - g->posY;
                float  dz = pp[2] - g->posZ;
                float  scale = sqrt(dx * dx + dy * dy + dz * dz) /
                               *(float*)((char*)FUN_00c37360() + 0x114);
                float k;
                if (scale <= g_epsf) {
                    k = g_onef;
                } else {
                    float r = (float)(int)param / scale;
                    k = r >= g_onef ? g_onef : r;
                }
                Vec3 out;
                out.x = (p.x - g->offX) * k + g->offX;
                out.y = (p.y - g->offY) * k + g->offY;
                out.z = (p.z - g->offZ) * k + g->offZ;
                g->MoveTo(&out.x);
                return;
            }
            Vec3 q;
            FUN_0105c3d0(&q.x, target, t);
            float* tp = ((IObj*)target)->GetPos();
            float* pp = ((IObj*)planet)->GetPos();
            float dx0 = pp[0] - tp[0];
            float dy0 = pp[1] - tp[1];
            float dz0 = pp[2] - tp[2];
            g = mpGame;
            float* p2 = ((IObj*)planet)->GetPos();
            float ex = p2[0] - g->posX;
            float ey = p2[1] - g->posY;
            float ez = p2[2] - g->posZ;
            float frac = g_onef - sqrt(ex * ex + ey * ey + ez * ez) /
                                     sqrt(dx0 * dx0 + dy0 * dy0 + dz0 * dz0);
            if (frac <= 0.0f)
                frac = 0.0f;
            if (frac >= g_onef)
                frac = g_onef;
            Vec3 out;
            out.x = q.x + (p.x - q.x) * frac;
            out.y = q.y + (p.y - q.y) * frac;
            out.z = q.z + (p.z - q.z) * frac;
            g->MoveTo(&out.x);
        } else {
            g->MoveTo(&p.x);
            void* info = FUN_00b3d4d0();
            if (*(int*)((char*)info + 0x2c) != 1 && *(int*)((char*)info + 0x2c) != 2) {
                float k = t < g_c15b6220 ? t : g_c15b6220;
                FUN_0105f760(mpGame, k, param);
                SpaceGame* gg = mpGame;
                Vec3 out;
                out.x = gg->posX + gg->offX;
                out.y = gg->posY + gg->offY;
                out.z = gg->posZ + gg->offZ;
                gg->view.SetPos(&out.x);
            }
        }
        return;
    }

    if (ctx == 2) {
        void* x = FUN_01021230();
        if (x == 0)
            return;
        if (FUN_00c8b550(x) == 2)
            return;
        float t = mpGame->time();
        Vec3  p;
        FUN_0105c5d0(&p.x, *(void**)((char*)x + 0x48), t);
        SpaceGame* g = mpGame;
        if (g->mode74c == 0) {
            float r = (float)(int)param * g_c15b6224;
            float k = r >= g_onef ? g_onef : r;
            Vec3 out;
            out.x = (p.x - g->offX) * k + g->offX;
            out.y = (p.y - g->offY) * k + g->offY;
            out.z = (p.z - g->offZ) * k + g->offZ;
            g->MoveTo(&out.x);
            return;
        }
        g->MoveTo(&p.x);
        void* info = FUN_00b3d4d0();
        if (!FUN_00ac80f0(info)) {
            float k = t < g_c15b6228 ? t : g_c15b6228;
            FUN_0105f760(mpGame, k, param);
            SpaceGame* gg = mpGame;
            Vec3 out;
            out.x = gg->posX + gg->offX;
            out.y = gg->posY + gg->offY;
            out.z = gg->posZ + gg->offZ;
            gg->view.SetPos(&out.x);
        }
    }
}

// ---------------------------------------------------------------- 0x00ffd000
// @ 0x00ffd000
void SP::cSPSimulatorPlayerUFO::GetStarRecordUnderMouse()
{
    if ((g_vecInit & 1) == 0) {
        g_vecInit |= 1;
        g_vecPrev[0] = g_vecA[0];
        g_vecPrev[1] = g_vecA[1];
        g_vecPrev[2] = g_vecA[2];
    }

    IApp* app = (IApp*)App();
    float cam[3];
    IViewer* viewer = app->GetViewer(cam, 0, 0, 0);
    viewer->GetCameraLocationInfo();

    float dx = g_vecPrev[0] - cam[0];
    float dy = g_vecPrev[1] - cam[1];
    float dz = g_vecPrev[2] - cam[2];
    if (0.001f <= dx * dx + dy * dy + dz * dz || g_flag15b7434 != 0) {
        g_vecPrev[0] = cam[0];
        g_vecPrev[1] = cam[1];
        g_vecPrev[2] = cam[2];
        int off = 0;
        do {
            StarRecord* sr = mpStars[off / 4];
            if (((sr->flags >> 15) & 1) == 0)
                return;
            float ex = cam[0] - sr->f0c;
            float ey = cam[1] - sr->f10;
            float ez = cam[2] - sr->f14;
            float dist = sqrt(ex * ex + ey * ey + ez * ez);
            float val;
            void* found = 0;
            if (sr->p64 != 0)
                found = sr->p64->Get(0x3e4353b);
            if (sr->p64 == 0 || found == 0 || FUN_00801920(found) != 1) {
                float hi = g_c15b6238 * dist;
                float mid = g_c15b623c * dist;
                float lo = g_c15b6240;
                if (mid > lo)
                    lo = mid;
                val = hi < lo ? hi : lo;
            } else {
                float hi = g_c15b622c * dist;
                float mid = g_c15b6230 * dist;
                float lo = g_c15b6234;
                if (mid > lo)
                    lo = mid;
                val = hi < lo ? hi : lo;
            }
            sr->counter = sr->counter + 1;
            off += 4;
            sr->f18 = val;
        } while (off < 4000);
    }
}
