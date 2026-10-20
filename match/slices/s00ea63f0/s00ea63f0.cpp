// slice s00ea63f0 -- EA::Audio creature-ability primitive handlers (the objects registered by
// AudioSetup::Setup in slice s00ea8160). Every handler derives from EA::Audio::PrimitiveBase and is
// registered under its own message id with the engine's PrimBase message server.
//
// Recurring engine helpers (addresses are the original VAs):
//   0x00a16ed0  PrimBase::SetValue(this, float value, int id)      -> this->mValue@0x20 = value
//   0x00a16e70  PrimBase::Shutdown(this)                           -> bool  (tail call)
//   0x00a16f00  PrimBase::HandleMessage(this, int id, void* arg)   -> bool  (slot +0x38)
//   0x00a16f60  PrimitiveBase::Init(this)                          -> bool
//   0x0067dcc0  SP::MessageServer()                                -> IMsgServer* (slots +0x20 Post, +0x2c Send)
//
// Value handlers take (float value, u32 id) on the stack with ecx = this, i.e. __thiscall; they are
// written here as __fastcall(self, edx, value, id) which produces the identical layout.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"
#include <math.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

// ---- engine entry points ---------------------------------------------------------------------------------
void* __cdecl App();                                  // 0x0067dd10  SP::App()
void* __cdecl SpaceGameGet();                         // 0x01002bd0  SP::SpaceGameGet()
void* __cdecl cSPSimulatorSpaceGame_GetPlayerInventory(void* sim);   // 0x00a1ad60
void* __cdecl SP_MessageServer();                     // 0x0067dcc0
void* __cdecl GetUFOSimulator();                      // 0x00ffbe50
void* __cdecl NounManager();                          // 0x00b3d300  SP::NounManager()
void* __cdecl GameTimeManager();                      // 0x00b3d380  SP::GameTimeManager()
void* __cdecl cTribeModeStrategy_Instance();          // 0x00cd40b0
void* __cdecl cCivModeStrategy_Get();                 // 0x00cf74c0
void* __cdecl AudioSystem();                          // 0x0067cb00
void* __cdecl AppSimContext();                        // 0x01021260
void* __cdecl SimGetSpaceGame();                      // 0x01002bd0 (same as SpaceGameGet)
void* __cdecl SpaceGameRelated1();                    // 0x00b3d350
void   __cdecl operator_delete(void* p);              // 0x00f47380

// float constants (absolute addresses)
extern "C" float kF1;    // 0x01470f1c   (2.0f)
extern "C" float kF2;    // 0x013f4fd0   (2147483648.0f -- the i32->float sign fix-up)
extern "C" float kFa;    // 0x013eb95c   (3.0f)
extern "C" float kFb;    // 0x014853e0
extern "C" float kFc;    // 0x01486110
extern "C" float kFd;    // 0x01486374
extern "C" float kFe;    // 0x013ec480
extern "C" float kFf;    // 0x01487378   (1.0f)
extern "C" float kFg;    // 0x01485720   (1.0f, used by the NounManager check)
extern "C" float kFh;    // 0x013eeda0   (8.0f)

// ---------------------------------------------------------------------------------------------------------
// EA::Audio::PrimitiveBase -- the common base of every handler in this slice.
// vtable +0x20 = Post/SetValue(this, payload, id)   (0x00a16ed0 stores into +0x20)
// vtable +0x34 = CommitValue(this, float)           (pure virtual, overridden by each handler)
// vtable +0x38 = HandleMessage(this, int id, void* arg)
// ---------------------------------------------------------------------------------------------------------
struct PrimBase {
    void* mVtbl;      // +0x00
    void* mVtbl2;     // +0x04
    void* mVtbl3;     // +0x08
    u32   m0c;        // +0x0c
    u8    m10;        // +0x10
    u8    pad11[3];
    float m14;        // +0x14
    void* m18;        // +0x18
    void* m1c;        // +0x1c
    float mValue;     // +0x20

    bool Init();                         // 0x00a16f60
    bool Shutdown();                     // 0x00a16e70
    void SetValue(float value, int id);  // 0x00a16ed0
    bool HandleMessage(int id, void* arg);   // 0x00a16f00
    void Commit(float value);            // vtable +0x34
};

// SP::MessageServer() object: slots +0x20 (Post) and +0x2c (Send).
struct IMsgServer {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void Post(void* self, u32 id);              // +0x20
    virtual void v24(); virtual void v28();
    virtual void Send(void* self, u32 id, int flag);    // +0x2c
};

// Direct engine calls (original addresses).
void   __fastcall PrimBase_SetValue(void* self, void* /*edx*/, float value, int id);    // 0x00a16ed0
char   __fastcall PrimBase_HandleMessage(void* self, void* /*edx*/, int id, void* arg); // 0x00a16f00
void*  __cdecl    SimGetPlayerInventory(void* sim);   // 0x00a1ad60
bool   __cdecl    SimQuery(void* inv);                // 0x01065fd0
bool   __cdecl    SimQueryUfoA(void* inv);            // 0x00c372c0
bool   __cdecl    SimQueryUfoB(void* inv);            // 0x00c37300
char   __fastcall CivHasThing(void* o, void* /*edx*/);    // 0x00e042b0
void*  __cdecl    CivStrategyChild(void* o);          // 0x00cf7500
struct SimCtx {
    float Perf();                           // 0x00c70a20  (__thiscall)
    int   Count();                          // 0x00c70fb0  (__thiscall)
};
void*  __cdecl    AudioComponent(void* sys);          // 0x0067cb00
void   __cdecl    SetNamedFloat(u32 tag, float v);    // 0x005ca880
float  __fastcall UFODataA(void* o, void* /*edx*/);   // 0x00f19170
struct UfoData {
    float  GetC();                          // 0x00f19160  (__thiscall)
    float  GetA();                          // 0x00f19170
    float* GetB();                          // 0x00f19180
};
float* __fastcall UFODataB(void* o, void* /*edx*/);   // 0x00f19180
void*  __cdecl    PlanetModel();                      // 0x00b3d350
void*  __cdecl    TerraformingManager();              // 0x00b3d430
void*  __cdecl    ActivePlanet();                     // 0x01021260

// ===========================================================================================================
// @ 0x00ea63f0  "one of the listed item keys is in the player's inventory"
// The inventory object exposes its key query at vtable slot +0x74; the app object exposes its state
// getter at +0x38.  Declaring them as real virtual methods reproduces the exact `mov edx,[ecx] /
// mov eax,[edx+N] / push arg / mov ecx,esi / call eax` sequence (a __fastcall cast instead inserts a
// spurious `xor edx,edx`).
extern "C" u8 kItemKey[];   // 0x016c6b24 .. 0x016c6ba0 (key bytes)
struct InvObj {
    virtual bool v00(); virtual bool v01(); virtual bool v02(); virtual bool v03();
    virtual bool v04(); virtual bool v05(); virtual bool v06(); virtual bool v07();
    virtual bool v08(); virtual bool v09(); virtual bool v10(); virtual bool v11();
    virtual bool v12(); virtual bool v13(); virtual bool v14(); virtual bool v15();
    virtual bool v16(); virtual bool v17(); virtual bool v18(); virtual bool v19();
    virtual bool v20(); virtual bool v21(); virtual bool v22(); virtual bool v23();
    virtual bool v24(); virtual bool v25(); virtual bool v26(); virtual bool v27();
    virtual bool v28();
    virtual bool Has(const void* key);      // +0x74 (slot 29)
};
struct AppStateObj {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c(); virtual void v0d();
    virtual u32 GetState();                 // +0x38 (slot 14)
};
// The space-game object hands out the player inventory through a plain (non-virtual) __thiscall getter.
struct SpaceGameObj {
    InvObj* GetPlayerInventory();           // 0x00a1ad60
};
// The inventory also answers the UFO-simulator queries through plain __thiscall methods.
struct InvQuery {
    char QueryUfoA();                       // 0x00c372c0
    char QueryUfoB();                       // 0x00c37300
};
// vtable view of a handler: slot +0x34 is the (pure virtual) value commit.
struct HandlerVtbl {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12();
    virtual void Commit(float value);       // +0x34 (slot 13)
};
// Every handler's Commit is the pure-virtual slot +0x34; the __fastcall cast this file used elsewhere
// inserts a spurious `xor edx,edx`, so dispatch through a real virtual method instead.
#define COMMIT(s, v) ((HandlerVtbl*)(s))->Commit(v)
// SP::App()'s vtable as used by this slice: +0x38 state getter, +0x58 object getter.
struct AppVtbl {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c(); virtual void v0d();
    virtual u32  GetState();                // +0x38 (slot 14)
    virtual void v0f(); virtual void v10(); virtual void v11(); virtual void v12();
    virtual void v13(); virtual void v14(); virtual void v15();
    virtual void* GetObj();                 // +0x58 (slot 22)
};
void __fastcall F_ea663f0(PrimBase* self, void* /*edx*/, float value, u32 id)
{
    self->SetValue(value, (int)id);

    AppStateObj* app = (AppStateObj*)App();
    if (app->GetState() != 0x1654c05)
        return;

    if (SpaceGameGet() == 0)
        return;

    void* sim = SpaceGameGet();
    InvObj* inv = ((SpaceGameObj*)sim)->GetPlayerInventory();
    if (inv == 0)
        return;

    if (inv->Has(&kItemKey[0x18])) goto hit;
    if (inv->Has(&kItemKey[0x24])) goto hit;
    if (inv->Has(&kItemKey[0x30])) goto hit;
    if (inv->Has(&kItemKey[0x3c])) goto hit;
    if (inv->Has(&kItemKey[0x48])) goto hit;
    if (inv->Has(&kItemKey[0x54])) goto hit;
    if (inv->Has(&kItemKey[0x60])) goto hit;
    if (inv->Has(&kItemKey[0x6c])) goto hit;
    if (inv->Has(&kItemKey[0x78])) goto hit;
    if (inv->Has(&kItemKey[0x0c])) { ((HandlerVtbl*)self)->Commit(kF1); return; }
    ((HandlerVtbl*)self)->Commit(inv->Has(&kItemKey[0x00]) ? 1.0f : 0.0f);
    return;
hit:
    ((HandlerVtbl*)self)->Commit(kFa);
}

// ===========================================================================================================
// @ 0x00ea6610  register the handler, then Init
bool __fastcall Ability_6610(PrimBase* self, void* /*edx*/)
{
    if (!self->Init())
        return false;
    IMsgServer* s = (IMsgServer*)SP_MessageServer();
    if (s == 0)
        return true;
    void* payload = self ? (char*)self + 4 : 0;
    s->Post(payload, 0x5cbe8ff);
    return true;
}

// ===========================================================================================================
// @ 0x00ea6660  unregister the handler, then Shutdown
bool __fastcall Ability_6660(PrimBase* self, void* /*edx*/)
{
    IMsgServer* s = (IMsgServer*)SP_MessageServer();
    if (s != 0)
    {
        void* payload = self ? (char*)self + 4 : 0;
        s->Send(payload, 0x5cbe8ff, 0xffffd8f1);
    }
    return self->Shutdown();
}

// ===========================================================================================================
// @ 0x00ea66a0  message handler: the message argument is a float at +0, forwarded to slot +0x34.
char __fastcall Ability_66a0(void* self, void* /*edx*/, u32 id, float* value)
{
    if (id == 0x5cbe8ff)
    {
        void* obj = (char*)self - 4;
        COMMIT(obj, *value);
    }
    return 1;
}

// ===========================================================================================================
// @ 0x00ea6760  "the camera is close to the planet's model"
struct Vec3 { float x, y, z; };
struct ViewerObj {
    void GetCameraLocationInfo(Vec3* out, int a, int b, int c);   // 0x007c3d30
};
struct ViewObj {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06();
    virtual ViewerObj* GetViewer();          // +0x1c (slot 7)
};
struct AppViewObj {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void* GetView();                 // +0x50 (slot 20)
};
struct ModelGeom {
    virtual void v00(); virtual void v01(); virtual void v02();
    virtual float* GetRadius();              // +0x0c (slot 3)
};
void __fastcall Ability_6760(PrimBase* self, void* /*edx*/, float value, u32 id)
{
    self->SetValue(value, (int)id);

    AppViewObj* app = (AppViewObj*)App();
    ViewObj* view = (ViewObj*)app->GetView();
    if (view == 0)
        return;
    ViewerObj* viewer = view->GetViewer();
    if (viewer == 0)
        return;

    Vec3 v;
    viewer->GetCameraLocationInfo(&v, 0, 0, 0);
    float d2 = v.x * v.x + v.z * v.z + v.y * v.y;

    void* pm = PlanetModel();
    void* q = *(void**)((char*)pm + 0x24);
    if (q == 0)
        return;
    float* r = ((ModelGeom*)q)->GetRadius();
    float limit = r[0x3c / 4] * r[0x38 / 4] + r[0x34 / 4];
    int hit = limit > sqrtf(d2);
    COMMIT(self, (float)hit);
}

// ===========================================================================================================
// @ 0x00ea68d0  "any of my units has moved recently"
void __fastcall Ability_68d0(PrimBase* self, void* /*edx*/, float value, u32 id)
{
    self->SetValue(value, (int)id);
    COMMIT(self, 0.0f);

    void* p = AppSimContext();
    if (p != 0)
    {
        float a = ((SimCtx*)p)->Perf();
        bool r = (kFd < a) && (((SimCtx*)p)->Count() == 0);
        COMMIT(self, (float)r);
    }
}

// ===========================================================================================================
// @ 0x00ea69e0
void __fastcall Ability_69e0(PrimBase* self, void* /*edx*/, float value, u32 id)
{
    self->SetValue(value, (int)id);
    COMMIT(self, 0.0f);

    void* p = AppSimContext();
    if (p != 0)
    {
        float a = ((SimCtx*)p)->Perf();
        bool r = (a < kFe) && (((SimCtx*)p)->Count() == 0);
        COMMIT(self, (float)r);
    }
}

// ===========================================================================================================
// @ 0x00ea6ae0
bool __fastcall Ability_6ae0(PrimBase* self, void* /*edx*/)
{
    if (!self->Init())
        return false;
    void* payload = self ? (char*)self + 4 : 0;
    IMsgServer* s = (IMsgServer*)SP_MessageServer();
    s->Post(payload, 0x248975f);
    return true;
}

// ===========================================================================================================
// @ 0x00ea6b20
bool __fastcall Ability_6b20(PrimBase* self, void* /*edx*/)
{
    void* payload = self ? (char*)self + 4 : 0;
    IMsgServer* s = (IMsgServer*)SP_MessageServer();
    s->Send(payload, 0x248975f, 0xffffd8f1);
    return self->Shutdown();
}

// ===========================================================================================================
// @ 0x00ea6b60  message handler
char __fastcall Ability_6b60(void* self, void* /*edx*/, u32 id, float* value)
{
    if (id == 0x248975f)
    {
        void* obj = (char*)self - 4;
        COMMIT(obj, 0.0f);
        void* p = AppSimContext();
        if (p != 0)
            COMMIT(obj, (float)(((SimCtx*)p)->Count() > 0));
    }
    return 1;
}

// ===========================================================================================================
// @ 0x00ea6c40  planet terraforming stage -> committed value
struct PlanetKind {
    int GetKind();                           // 0x00c70e00
};
struct TerraObj {
    int F670(void* arg);                     // 0x00bbc670
};
void __fastcall Ability_6c40(PrimBase* self, void* /*edx*/, float value, u32 id)
{
    self->SetValue(value, (int)id);

    void* planet = ActivePlanet();
    if (planet == 0)
        return;

    switch (((PlanetKind*)planet)->GetKind())
    {
    case 1:
    {
        void* field = *(void**)((char*)planet + 0x13c);
        void* tm = TerraformingManager();
        if (tm == 0 || ((TerraObj*)tm)->F670(field) != 0)
        {
            if (*(u32*)((char*)field + 0xd0) != *(u32*)((char*)field + 0xd4))
                COMMIT(self, kF1);
            else
                COMMIT(self, 1.0f);
            return;
        }
        COMMIT(self, 0.0f);
        return;
    }
    case 3: COMMIT(self, kFa); return;
    case 4: COMMIT(self, kFb); return;
    case 5: COMMIT(self, kFc); return;
    default: COMMIT(self, 0.0f); return;
    }
}

// ===========================================================================================================
// @ 0x00ea6dd0  game-phase indicator
struct GameTime {
    char pad00[0x48];
    u32  m48;                                // +0x48
    void GetTimes(float* a, float* b, float* c, float* d);   // 0x00b31700
    float GetValue();                        // 0x00b31730
};
void __fastcall Ability_6dd0(PrimBase* self, void* /*edx*/, float value, u32 id)
{
    GameTime* g = (GameTime*)GameTimeManager();
    if (g == 0)
        return;
    if ((g->m48 & 1) != 0)
    {
        COMMIT(self, 0.0f);
        return;
    }
    float a, b, c, d;
    g->GetTimes(&a, &b, &c, &d);
    float r = g->GetValue();
    if (r == a)      COMMIT(self, 1.0f);
    else if (r == b) COMMIT(self, kF1);
    else if (r == c) COMMIT(self, kFb);
    else if (r == d) COMMIT(self, kFh);
}

// ===========================================================================================================
// @ 0x00ea6f20
void __fastcall Ability_6f20(PrimBase* self, void* /*edx*/, float value, u32 id)
{
    void* p = AppSimContext();
    if (p != 0)
    {
        void* q = *(void**)((char*)p + 0x13c);
        if (q != 0)
        {
            u32 r = ((*(u32*)((char*)q + 0xbc) != *(u32*)((char*)q + 0xc0)) << 1)
                  | (*(u32*)((char*)q + 0xd0) != *(u32*)((char*)q + 0xd4));
            COMMIT(self, (float)r);
        }
    }
}

// ===========================================================================================================
// @ 0x00ea7020  predicate: true when the noun's vtable slot +0x58 reports "nothing"
struct Noun58 {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15();
    virtual char IsNothing();               // +0x58 (slot 22)
};
bool __cdecl Ability_7020(void* obj)
{
    Noun58* p = (Noun58*)((char*)obj + 0x120);
    return p->IsNothing() == 0;
}
// ===========================================================================================================
struct Noun120 {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a();
    virtual float* GetPos();                 // +0x2c (slot 11)
};
void* __cdecl Ability_7040(void** range, float* ctx, char(__cdecl* pred)(void*))
{
    void** end = (void**)range[1];
    void* result = 0;
    float best = kFf;
    for (void** it = (void**)range[0]; it != end; ++it)
    {
        void* o = *it;
        if (pred(o))
        {
            Noun120* p = (Noun120*)((char*)o + 0x120);
            float* pos = p->GetPos();
            float dx = pos[0] - ctx[0];
            float dy = pos[1] - ctx[1];
            float dz = pos[2] - ctx[2];
            float d2 = dx * dx + dy * dy + dz * dz;
            if (best > d2)
            {
                result = o;
                best = d2;
            }
        }
    }
    return result;
}

// ===========================================================================================================
// cTribeModeStrategy() object: +0x1c8 holds an object with a float getter 0x00bc22b0.
struct TribeObj {
    float Value();                          // 0x00bc22b0  (returns float in st(0))
};
struct Tribe {
    char  pad00[0x1c8];
    TribeObj* m1c8;                         // +0x1c8
};
// @ 0x00ea7190
void __fastcall Ability_7190(PrimBase* self, void* /*edx*/, float value, u32 id)
{
    float r = kFf;
    void* app = App();
    if (((AppVtbl*)app)->GetState() == 0x1654c02)
    {
        if ((*(Tribe*)cTribeModeStrategy_Instance()).m1c8 != 0)
        {
            r = (*(Tribe*)cTribeModeStrategy_Instance()).m1c8->Value();
            COMMIT(self, r);
            return;
        }
    }
    COMMIT(self, r);
}

// ===========================================================================================================
// SP::NounManager() object: 0x00b25c30 is a plain __thiscall getter.
struct Xform {
    void Decompose(float* pos, float* c, float* b, float* a);   // 0x007c3d30
};
struct NounMgr {
    void* Query();                          // 0x00b25c30
    void* GetAv();                          // 0x00b1fdb0
};
// polymorphic sub-object living at +0xc0 of the noun-manager result.
struct AvSub {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual void* Get();                    // +0x2c
};
struct Av {
    char   pad00[0xc0];
    AvSub  m;                               // +0xc0
};
// audio system: vtable +0x2c returns the component mixer, whose +0x08 queries a channel.
struct AudioComp {
    virtual void v00(); virtual void v04();
    virtual int  Query(void* r);            // +0x08
};
struct AudioSys {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual AudioComp* Get();               // +0x2c
};
// @ 0x00ea72a0
void __fastcall Ability_72a0(PrimBase* self, void* /*edx*/, float value, u32 id)
{
    self->SetValue(value, (int)id);

    float r = 0.0f;
    void* app = App();
    u32 st = ((AppVtbl*)app)->GetState();
    if (st == 0x1654c04 || st == 0x1654c05)
    {
        void* n = NounManager();
        if (((NounMgr*)n)->Query() != 0)
            r = kFg;
    }
    COMMIT(self, r);
}

// ===========================================================================================================
// @ 0x00ea7690
// 0x00ea5510 is a plain __thiscall (this in ecx, float value then id on the stack); returning nothing.
struct LeafUpdate {
    void Forward(float value, int id);      // 0x00ea5510
};
void __fastcall Ability_7690(PrimBase* self, void* /*edx*/, float value, u32 id)
{
    ((LeafUpdate*)self)->Forward(value, (int)id);
    COMMIT(self, (float)*(u8*)((char*)self + 0x24));
}

// ===========================================================================================================
// @ 0x00ea7830
bool __fastcall Ability_7830(PrimBase* self, void* /*edx*/)
{
    if (!self->Init())
        return false;
    *(u32*)((char*)self + 0x38) = *(u32*)0x016c6adc;
    *(u32*)((char*)self + 0x3c) = *(u32*)0x016c6ae0;
    *(u32*)((char*)self + 0x40) = *(u32*)0x016c6ae4;
    return true;
}

// ===========================================================================================================
// @ 0x00ea7870
void __fastcall Ability_7870(PrimBase* self, void* /*edx*/, float value, u32 id)
{
    self->SetValue(value, (int)id);

    void* app = App();
    void* a = ((AppVtbl*)app)->GetObj();
    if (a != 0)
    {
        float pos[3], f0[3], f1[3], f2[3];
        ((Xform*)a)->Decompose(pos, f2, f1, f0);
        float dx = pos[0] - *(float*)((char*)self + 0x38);
        float dy = pos[1] - *(float*)((char*)self + 0x3c);
        float dz = pos[2] - *(float*)((char*)self + 0x40);
        COMMIT(self, sqrt(dx * dx + dy * dy + dz * dz));
        *(u32*)((char*)self + 0x38) = ((u32*)pos)[0];
        *(u32*)((char*)self + 0x3c) = ((u32*)pos)[1];
        *(u32*)((char*)self + 0x40) = ((u32*)pos)[2];
    }
}

// ===========================================================================================================
// @ 0x00ea79a0
void __fastcall Ability_79a0(PrimBase* self, void* /*edx*/, float value, u32 id)
{
    self->SetValue(value, (int)id);

    void* n = NounManager();
    if (n != 0)
    {
        void* av = ((NounMgr*)n)->GetAv();
        if (av != 0)
        {
            void* r = ((Av*)av)->m.Get();
            void* sys = AudioSystem();
            COMMIT(self, (float)(((AudioSys*)sys)->Get()->Query(r) == 3));
        }
    }
}

// ===========================================================================================================
// @ 0x00ea7ab0
bool __fastcall Ability_7ab0(PrimBase* self, void* /*edx*/)
{
    void* payload = self ? (char*)self + 4 : 0;
    IMsgServer* s = (IMsgServer*)SP_MessageServer();
    s->Post(payload, 0x553fe73);
    return self->Init();
}

// ===========================================================================================================
// @ 0x00ea7ae0
bool __fastcall Ability_7ae0(PrimBase* self, void* /*edx*/)
{
    void* payload = self ? (char*)self + 4 : 0;
    IMsgServer* s = (IMsgServer*)SP_MessageServer();
    s->Send(payload, 0x553fe73, 0xffffd8f1);
    return self->Shutdown();
}

// ===========================================================================================================
// @ 0x00ea7b20  message handler: the message argument is a float at +8.
char __fastcall Ability_7b20(void* self, void* /*edx*/, u32 id, float* value)
{
    if (id == 0x553fe73)
    {
        void* obj = (char*)self - 4;
        COMMIT(obj, value[2]);
        return 1;
    }
    return ((PrimBase*)self)->HandleMessage((int)id, value);
}

// ===========================================================================================================
// @ 0x00ea7be0
// 0x00cf7500 is a plain __thiscall getter returning this->m_ec; 0x00e042b0 is a plain __thiscall
// predicate.  Both are called with ecx only, so they are modelled as members to avoid a pushed dummy.
struct CivStrategy {
    void* GetChild();                       // 0x00cf7500  -> this->m_ec
};
struct CivChild {
    char HasThing();                        // 0x00e042b0
};
void __fastcall Ability_7be0(PrimBase* self, void* /*edx*/, float value, u32 id)
{
    self->SetValue(value, (int)id);

    unsigned char r = 0;
    CivStrategy* m = (CivStrategy*)cCivModeStrategy_Get();
    if (m != 0)
    {
        CivChild* a = (CivChild*)m->GetChild();
        if (a != 0 && *(void**)((char*)a + 0x64) != 0)
            r = ((CivChild*)*(void**)((char*)a + 0x64))->HasThing();
    }
    COMMIT(self, (float)r);
}

// ===========================================================================================================
// @ 0x00ea7cd0
// 0x01065fd0 is a plain __thiscall predicate (this in ecx, no stack args).
struct SimQ {
    char Query();                           // 0x01065fd0
};
void __fastcall Ability_7cd0(PrimBase* self, void* /*edx*/, float value, u32 id)
{
    self->SetValue(value, (int)id);

    unsigned char r = 0;
    void* g = SpaceGameGet();
    if (g != 0 && *(void**)((char*)g + 0x14) != 0)
        r = ((SimQ*)*(void**)((char*)g + 0x14))->Query();
    COMMIT(self, (float)r);
}

// ===========================================================================================================
// @ 0x00ea7db0
void __fastcall Ability_7db0(PrimBase* self, void* /*edx*/, float value, u32 id)
{
    self->SetValue(value, (int)id);

    unsigned char r = 0;
    void* sim = GetUFOSimulator();
    if (sim != 0)
    {
        InvObj* inv = ((SpaceGameObj*)sim)->GetPlayerInventory();
        if (inv != 0)
            r = ((InvQuery*)inv)->QueryUfoA();
    }
    COMMIT(self, (float)r);
}

// ===========================================================================================================
// @ 0x00ea7e90
void __fastcall Ability_7e90(PrimBase* self, void* /*edx*/, float value, u32 id)
{
    self->SetValue(value, (int)id);

    unsigned char r = 0;
    void* sim = GetUFOSimulator();
    if (sim != 0)
    {
        InvObj* inv = ((SpaceGameObj*)sim)->GetPlayerInventory();
        if (inv != 0)
            r = ((InvQuery*)inv)->QueryUfoB();
    }
    COMMIT(self, (float)r);
}

// ===========================================================================================================
// @ 0x00ea7f70
void __fastcall Ability_7f70(PrimBase* self, void* /*edx*/, float value, u32 id)
{
    self->SetValue(value, (int)id);

    void* g = *(void**)0x016c7aa4;
    float out = kFf;
    if (g != 0)
    {
        void* o = *(void**)((char*)g + 0x78);
        if (o != 0)
        {
            out = ((UfoData*)o)->GetA();
            float* v = ((UfoData*)o)->GetB();
            SetNamedFloat(0x41543a2d, v[0]);
            SetNamedFloat(0x41543a2c, v[1]);
            SetNamedFloat(0x41543a2f, v[2]);
        }
    }
    COMMIT(self, out);
}

// ===========================================================================================================
// @ 0x00ea80a0
void __fastcall Ability_80a0(PrimBase* self, void* /*edx*/, float value, u32 id)
{
    self->SetValue(value, (int)id);

    float out = 0.0f;
    void* g = *(void**)0x016c7aa4;
    if (g != 0)
    {
        void* o = *(void**)((char*)g + 0x78);
        if (o != 0)
            out = ((UfoData*)o)->GetC();
    }
    COMMIT(self, out);
}

// ===========================================================================================================
// @ 0x00ea8100  GmeEditorResBase / IMsgHandler / GmeRefCount deleting destructor
struct GmeRefCounted {
    void* mVt0;      // +0x00
    void* mVt1;      // +0x04
    void* mVt2;      // +0x08
    u32   pad0c;     // +0x0c
    u32   pad10;     // +0x10
    u32   pad14;     // +0x14
    void* m18;       // +0x18
    void* m1c;       // +0x1c
    u32   m20;       // +0x20
    u32   m24;       // +0x24  vector begin
    u32   m28;       // +0x28
    u32   m2c;       // +0x2c  vector end (sized-delete threshold = begin + 1)
};

// The interface the destructor walks at +0x18; slot +4 is its Release().
struct DtorIface {
    virtual void v00();                 // +0x00
    virtual void Release();             // +0x04
};

void* __fastcall GmeEditorResBase_dtor(GmeRefCounted* self, void* /*edx*/, unsigned char flags)
{
    if ((int)(self->m2c - self->m24) > 1 && self->m24 != 0)
        operator_delete((void*)self->m24);

    DtorIface* p = (DtorIface*)self->m18;
    if (p != 0)
        p->Release();

    self->mVt2 = (void*)0x13ef094;
    self->mVt1 = (void*)0x13eb394;
    self->mVt0 = (void*)0x13eb938;

    if (flags & 1)
        operator_delete(self);
    return self;
}
