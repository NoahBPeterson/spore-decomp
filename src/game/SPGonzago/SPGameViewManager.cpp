// src/game/SPGonzago/SPGameViewManager.cpp -- migrated from slice(s) s00b35300, s00b34610 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPGameViewManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ArgScript/cArguments.h"
#include "SP/cPlanetModel.h"
#include "SP/cViewer.h"
#include "SP/cPropertyList.h"
#include "SP/cDirectPropertyList.h"
#include "SP/cSPEditorPhysicsWorld.h"
#include <math.h>
#include <new.h>

// unnamed retail callees and globals (address in the comment)
extern "C" int    strcmp(const char*, const char*);
extern void*       g_obj54;       // 0x0167ea54
extern void*       g_obj58;       // 0x0167ea58
extern "C" void*  __cdecl SP_ModelManager(void);     // 0x0067dd80
extern "C" void*  __cdecl SP_LightingManager(void);  // 0x0067dd90
extern "C" void*  __cdecl SP_MessageServer(void);    // 0x0067dcc0
extern "C" void*  __cdecl SP_EffectsManager(void);   // 0x0067ddd0
extern "C" void*  __cdecl SP_GonzagoModelWorld(void); // 0x00b3d520
#pragma warning(disable : 4100)
#pragma intrinsic(strcmp)

// ---- items of slice s00b34610 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int  u32;
typedef unsigned char u8;
extern void*       g_obj54;       // 0x0167ea54
extern void*       g_obj58;       // 0x0167ea58
struct IMsg {                                   // SP::MessageServer
    virtual void d00(), d04(), d08(), d0C(), d10(), d14(), d18(), d1C(),
                 d20(), d24(), d28();
    virtual void v2C(void*, u32, u32);
};
struct IModelMgr {                              // SP::ModelManager
    virtual void d00(), d04(), d08(), d0C(), d10(), d14();
    virtual void  v18(u32);
    virtual void* v1C(u32);
};
struct IEffects {                               // SP::EffectsManager
    virtual void d00(), d04(), d08(), d0C(), d10(), d14(), d18(), d1C(),
                 d20(), d24(), d28(), d2C(), d30(), d34(), d38(), d3C(),
                 d40(), d44(), d48(), d4C();
    virtual void  v50(u32);
    virtual void* v54(u32);
};
struct ILight {                                 // SP::LightingManager
    virtual void d00(), d04(), d08(), d0C(), d10(), d14(), d18(), d1C();
    virtual void v20(u32);
};
struct IObjRef {                                // refcounted object: AddRef / Release
    virtual void v00();
    virtual void v04();
};
struct IObj18 {                                 // object with slot 0x18
    virtual void v00(), v04(), v08(), v0C(), v10(), v14(), v18();
};
struct IObj20 {                                 // object with slot 0x20 + refcount
    virtual void v00(), v04(), v08(), v0C(), v10(), v14(), v18(), v1C();
    virtual void v20();
};
struct IGonzWorld {                             // SP::GonzagoModelWorld
    virtual void v00(), v04(), v08(), v0C(), v10(), v14(), v18(), v1C(),
                 v20(), v24(), v28(), v2C(), v30(), v34(), v38(), v3C(),
                 v40(), v44(), v48(), v4C(), v50(), v54(), v58(), v5C(),
                 v60(), v64(), v68(), v6C(), v70(), v74(), v78(), v7C(),
                 v80(), v84(), v88(), v8C(), v90(), v94(), v98(), v9C(),
                 vA0(), vA4(), vA8(), vAC(), vB0(), vB4(), vB8(), vBC(),
                 vC0(), vC4(), vC8(), vCC(), vD0(), vD4(), vD8(), vDC(),
                 vE0(), vE4(), vE8(), vEC(), vF0(), vF4(), vF8(), vFC(),
                 v100(), v104(), v108(), v10C(), v110(), v114(), v118(), v11C(),
                 v120(), v124(), v128(), v12C(), v130(), v134();
    virtual char v138();
};
struct IModel140 {                              // loaded model object
    virtual void v00(), v04(), v08(), v0C(), v10(), v14(), v18(), v1C(),
                 v20(), v24(), v28(), v2C(), v30(), v34(), v38(), v3C(),
                 v40(), v44(), v48(), v4C(), v50(), v54(), v58(), v5C(),
                 v60(), v64(), v68(), v6C(), v70(), v74(), v78(), v7C(),
                 v80(), v84(), v88(), v8C(), v90(), v94(), v98(), v9C(),
                 vA0(), vA4(), vA8(), vAC(), vB0(), vB4(), vB8(), vBC(),
                 vC0(), vC4(), vC8(), vCC(), vD0(), vD4(), vD8(), vDC(),
                 vE0(), vE4(), vE8(), vEC(), vF0(), vF4(), vF8(), vFC(),
                 v100(), v104(), v108(), v10C(), v110(), v114(), v118(), v11C(),
                 v120(), v124(), v128(), v12C(), v130(), v134(), v138(), v13C();
    virtual void v140(int, int, int);
};
struct CAct {                                   // game mode teardown object
    u8       pad00[0x80];
    IObj20*  m80;                               // +0x80
    u8       pad84[0x58];
    IObj20*  mDC;                               // +0xDC
    IObj20*  mE0;                               // +0xE0
    u8       padE4[0x04];
    void*    mE8;                               // +0xE8
    u8       padEC[0x04];
    void*    mF0;                               // +0xF0
    u8       padF4[0x0C];
    IObj20*  m100;                              // +0x100
};
extern "C" void*  __cdecl SP_ModelManager(void);     // 0x0067dd80
extern "C" void*  __cdecl SP_LightingManager(void);  // 0x0067dd90
extern "C" void*  __cdecl SP_MessageServer(void);    // 0x0067dcc0
extern "C" void*  __cdecl SP_EffectsManager(void);   // 0x0067ddd0
extern "C" void*  __cdecl SP_GonzagoModelWorld(void); // 0x00b3d520
void    __cdecl FUN_00761110(void* p);                                  // 0x00761110
struct CObj3ba0 {
    void FUN_007c3ba0();                                                // 0x007c3ba0
};
// ---- items of slice s00b34610 end

// ---- items of slice s00b35300 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_na;                                       // 0x167ea5c
extern float g_nb;                                       // 0x167ea60
extern float g_nc;                                       // 0x167ea64
typedef uint8_t  u8_s00b3_5300;
typedef uint16_t u16;
typedef uint32_t u32_s00b3_5300;
#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define VP virtual void CAT(_p, __COUNTER__)();
#define VP4 VP VP VP VP
#define VP16 VP4 VP4 VP4 VP4
struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct RefObj {
    virtual int AddRef();
    virtual int Release();
};
struct Filter {
    u32_s00b3_5300 w0, w1, w2, w3;
    u32_s00b3_5300 e;
    u8_s00b3_5300  type;
    u8_s00b3_5300  z;
};
struct Prop {
    char pad[0x12];
    u16 type;
    float* GetFloat();                                   // 0x41ea70
};
struct PropBase {
    int GetModificationCount();                          // 0x6237a0
};
struct PropList {
    VP4 VP4 VP
    virtual bool Get(u32_s00b3_5300 id, Prop** out);                // 0x24
    char pad[0x2c];
    PropBase* parent;                                    // 0x30
    int count;                                           // 0x34
    int GetIntProperty(u32_s00b3_5300 id);                          // 0x6a2660
};
struct Obj;
struct ObjMgr {
    VP16 VP16 VP16 VP16 VP16 VP4 VP4 VP4
    virtual void Destroy(Obj* o, int flag);              // 0x170
};
struct Comp : RefObj {
    VP
    virtual RefObj* Query(u32_s00b3_5300 id);                       // 0xc
    VP4 VP VP VP
    virtual bool Fn2c();                                 // 0x2c
};
struct Obj {
    ObjMgr* mgr;                                         // 0
    int f4;
    int f8;
    float x, y, z;                                       // 0xc
    char pad1[0x28];
    int rc;                                              // 0x40
    char pad2[0x20];
    Comp* comp;                                          // 0x64
    char pad3[0x24];
    float f8c;                                           // 0x8c
};
struct Handle { int a; Obj* b; };
struct RefPtr { RefObj* p; RefPtr& operator=(RefObj* o); };   // 0xb5f950
struct World : RefObj {
    VP4 VP VP VP
    virtual Obj* Pick(int a, int b, int c, Vec3* out, int d, Filter* f, int e, int g);   // 0x24
    VP4
    virtual bool Cast(Vec3* p, float t, void* list, Filter* f);                      // 0x38
    VP VP
    virtual bool Cast2(Vec3* a, Vec3* b, Handle* h, float* t, Filter* f);            // 0x44
    VP16 VP16 VP16 VP4 VP VP VP
    virtual void SetInt(int a, int b, int v);            // 0x124
    VP VP VP
    virtual void SetFlag(int v);                         // 0x134
    VP
    virtual RefObj* GetLayer();                          // 0x13c
    VP4 VP
    virtual void SetFloat(float v);                      // 0x154
};
struct LNode {
    LNode*  a;                                           // 4
    LNode** b;                                           // 8
    virtual ~LNode();
};
struct Listed : RefObj {
    VP4 VP4 VP4
    virtual void Detach();                               // 0x38
    char pad[0x10];
    LNode* node;                                         // 0x14
};
struct Viewer {
    VP16 VP VP VP
    virtual void Add(void* obj, int id, int pri);      // 0x4c
    virtual void Remove(int id);                         // 0x50
};
struct ModelMgr {                                        // SP::ModelManager
    VP4 VP4 VP
    virtual void SetWorld(World* w);                     // 0x24
};
struct Effect : RefObj {
    VP
    virtual void SetQuality(int q);                      // 0xc
    VP4 VP4 VP VP
    virtual void Fn38();
};
struct EffectParams {
    char pad[0xd8];
    Vec3 v;                                              // 0xd8
    float d;                                             // 0xe4
    Vec3 w;                                              // 0xe8
};
struct EffectsMgr {                                      // SP::EffectsManager
    VP16 VP4 VP
    virtual Effect* Get(u32_s00b3_5300 id);                         // 0x54
    virtual void Fn58(Effect* e);                        // 0x58
    VP16 VP
    virtual EffectParams* GetParams();                   // 0xa0
};
struct LightMgr {                                        // FUN_0067de00
    VP16 VP16 VP VP
    virtual void Fn88(RefObj* l);                        // 0x88
};
struct Planet {
    VP4 VP
    virtual RefObj* Fn14(int a);                         // 0x14
    VP16 VP4 VP4 VP4 VP
    virtual void SetViewer(Viewer* v);                   // 0x8c
    virtual void UnsetViewer(Viewer* v);                 // 0x90
};
struct PlanetModel { char pad[0x24]; Planet* planet; };
struct NameMgr {                                         // FUN_0067cb20
    VP4 VP4
    virtual RefObj* Get(const wchar_t* name);            // 0x20
};
struct Registered : RefObj {                             // result of NameMgr::Get
    VP4 VP
    virtual void Attach(World* w, int a, int b, int c, int d);   // 0x1c
};
struct cSPEditorPhysicsWorld {
    char pad[0x174];
    cSPEditorPhysicsWorld();                             // 0x7c3f70
    ~cSPEditorPhysicsWorld();                            // 0x7c4000
    void Init(int);                                      // 0x7c4dd0
    void SetMode(int a, int b);                          // 0x7c3ce0
    void Shutdown();                                     // 0x7c3ba0
};
struct SceneA { void Fn(); void Fn2(); };                            // FUN_00b3d470 result
struct SceneB {                                          // FUN_00b3d320 result
    PropList* Fn2();                                     // 0xb1de80
};
void* __cdecl operator_new(unsigned, const char*, int, int, int, int);
inline void* operator new(unsigned n, const char* name, int a, int b, int c, int d) {
    return operator_new(n, name, a, b, c, d);
}
inline void operator delete(void*, const char*, int, int, int, int) {}
World*       __cdecl GetGonzagoModelWorld();             // 0xb3d520
Viewer*      __cdecl GetViewer();                        // 0x67dd50
ModelMgr*    __cdecl GetModelManager();                  // 0x67dd80
EffectsMgr*  __cdecl GetEffectsManager();                // 0x67ddd0
LightMgr*    __cdecl GetLightMgr();                      // 0x67de00
NameMgr*     __cdecl GetNameMgr();                       // 0x67cb20
PlanetModel* __cdecl GetPlanetModel();                   // 0xb3d350
SceneA*      __cdecl GetSceneA();                        // 0xb3d470
SceneB*      __cdecl GetSceneB();                        // 0xb3d320
int          __cdecl GetUniverseContext();               // 0x1021080
void         __fastcall Helper_fc3f00(RefObj* o);        // 0xfc3f00 (thiscall)
extern PropList* g_Props;                                // 0x15fd918
extern RefObj*   g_Lighting;                             // 0x167ea54
extern Registered* g_Gonzago;                            // 0x167ea58
extern u32_s00b3_5300 g_a;                                          // 0x167e9f8
extern u32_s00b3_5300 g_b;                                          // 0x167e9fc
extern u32_s00b3_5300 g_c;                                          // 0x167ea00
static inline void AssignRef(RefObj*& dst, RefObj* src) {
    RefObj* old = dst;
    if (src != old) {
        if (src) src->AddRef();
        dst = src;
        if (old) old->Release();
    }
}
struct Owner {
    char pad0[0x2c];
    Obj** vbeg;                                          // 0x2c
    Obj** vend;                                          // 0x30
    char pad1[0x88 - 0x34];
    Listed* sel;                                         // 0x88
    char pad2[0xe4 - 0x8c];
    World* w1;                                           // 0xe4
    World* w2;                                           // 0xe8
    cSPEditorPhysicsWorld* phys;                         // 0xec
    char pad3[0x104 - 0xf0];
    int modCount;                                        // 0x104
    RefObj* fx;                                          // 0x108

    void Setup();                                        // 0xb35300
    void Teardown();                                     // 0xb35860
    void OnRemove(Listed* e);                            // 0xb35af0
    bool FindNearest(Vec3* pos, float t, u32_s00b3_5300 p4, RefObj** out);   // 0xb35d30
    bool Pick(int a, int b, u32_s00b3_5300 d, RefPtr* r, Vec3* out, u8_s00b3_5300 e);   // 0xb35ec0
};
// ---- items of slice s00b35300 end

// @ 0x00b34ff0
void __fastcall FUN_00b34ff0(CAct* ecx_this, void* edx)
{
    if (ecx_this->m80 != 0) {
        IObj20* p = ecx_this->m80;
        ecx_this->m80 = 0;
        p->v04();
    }
    if (SP_GonzagoModelWorld() != 0) {
        if (((IGonzWorld*)SP_GonzagoModelWorld())->v138() != 0) {
            ((IObj18*)((char*)ecx_this - 8))->v18();
        }
    }
    void* msg = SP_MessageServer();
    if (msg != 0) {
        void* p = (char*)ecx_this - 8;
        void* arg = p ? (void*)((char*)ecx_this - 4) : 0;
        ((IMsg*)msg)->v2C(arg, 0x30c11c7, 0xffffd8f1);
        arg = p ? (void*)((char*)ecx_this - 4) : 0;
        ((IMsg*)msg)->v2C(arg, 0x3047cb34, 0xffffd8f1);
        arg = p ? (void*)((char*)ecx_this - 4) : 0;
        ((IMsg*)msg)->v2C(arg, 0x1a0219e, 0xffffd8f1);
        arg = p ? (void*)((char*)ecx_this - 4) : 0;
        ((IMsg*)msg)->v2C(arg, 0x4b719d4, 0xffffd8f1);
        arg = p ? (void*)((char*)ecx_this - 4) : 0;
        ((IMsg*)msg)->v2C(arg, 0x712924f2, 0xffffd8f1);
        arg = p ? (void*)((char*)ecx_this - 4) : 0;
        ((IMsg*)msg)->v2C(arg, 0x712924f3, 0xffffd8f1);
    }
    if (SP_GonzagoModelWorld() != 0) {
        ((IModelMgr*)SP_ModelManager())->v18(0xeb9968);
    }
    if (ecx_this->mDC != 0) {
        ((IModelMgr*)SP_ModelManager())->v18(0x317ccba);
    }
    if (ecx_this->mE0 != 0) {
        ((IModelMgr*)SP_ModelManager())->v18(0x5de6030);
    }
    void* eff = ((IEffects*)SP_EffectsManager())->v54(0xeb9968);
    if (eff != 0) {
        ((IObjRef*)eff)->v00();
        ((IEffects*)SP_EffectsManager())->v50(0xeb9968);
    }    if (ecx_this->mE8 != 0) {
        ((CObj3ba0*)ecx_this->mE8)->FUN_007c3ba0();
        ecx_this->mE8 = 0;
    }
    if (ecx_this->mF0 != 0) {
        FUN_00761110(ecx_this->mF0);
        ecx_this->mF0 = 0;
    }
    if (((IEffects*)SP_EffectsManager())->v54(0x23541242) != 0) {
        ((IEffects*)SP_EffectsManager())->v50(0x23541242);
    }
    if (((IEffects*)SP_EffectsManager())->v54(0x3701a5c) != 0) {
        ((IEffects*)SP_EffectsManager())->v50(0x3701a5c);
    }
    if (g_obj54 != 0) {
        IModel140* model = (IModel140*)((IModelMgr*)SP_ModelManager())->v1C(0x3fbae24);
        if (model != 0) {
            model->v00();
            model->v140(0, 0, 1);
            model->v140(0, 1, 1);
        }
        if (g_obj54 != 0) {
            IObjRef* o = (IObjRef*)g_obj54;
            g_obj54 = 0;
            o->v04();
        }
        ((ILight*)SP_LightingManager())->v20(0x4a4dea0);
        if (model != 0) {
            model->v04();
        }
    }
    if (g_obj58 != 0) {
        ((IObj20*)g_obj58)->v20();
        if (g_obj58 != 0) {
            IObj20* o = (IObj20*)g_obj58;
            g_obj58 = 0;
            o->v04();
        }
    }
    if (ecx_this->m100 != 0) {
        ecx_this->m100->v20();
        if (ecx_this->m100 != 0) {
            IObj20* o = ecx_this->m100;
            ecx_this->m100 = 0;
            o->v04();
        }
    }
    if (eff != 0) {
        ((IObjRef*)eff)->v04();
    }
}

// @ 0x00b35300
void Owner::Setup()
{
    World* w = GetGonzagoModelWorld();
    if (w) {
        w->AddRef();
        int pv = g_Props->GetIntProperty(0x1d1176d);
        w->SetInt(0, 0, pv);
        GetViewer()->Add(w->GetLayer(), 12, 4);
        GetViewer()->Add(w->GetLayer(), 13, 0);
        GetViewer()->Add(w->GetLayer(), 20, 2);
        GetViewer()->Add(this, 0x1a, 7);
        w->SetFlag(1);
        GetModelManager()->SetWorld(w);
        PropList* t = GetSceneB()->Fn2();
        PropList* gp = g_Props;
        int a = gp->parent ? gp->parent->GetModificationCount() : 0;
        int total = gp->count + a;
        modCount = total;
        if (t) {
            int b = t->parent ? t->parent->GetModificationCount() : 0;
            modCount = t->count + total + b;
        }
        float f = 0.0f;
        if (!GetUniverseContext()) {
            Prop* p;
            if (g_Props && g_Props->Get(0x26b7d69, &p) && p->type == 0xd)
                f = *p->GetFloat();
            if (t && t->Get(0x26b7d69, &p) && p->type == 0xd)
                f = *p->GetFloat();
        }
        w->SetFloat(f);
    }
    if (w1) {
        int pv = g_Props->GetIntProperty(0x1d1176d);
        w1->SetInt(0, 0, pv);
        GetViewer()->Add(w1->GetLayer(), 13, 0);
        w1->SetFlag(1);
    }
    if (w2) {
        GetViewer()->Add(this, 0xf, 0);
        w2->SetFlag(1);
    }
    Effect* e1 = GetEffectsManager()->Get(0xeb9968);
    if (e1) {
        e1->AddRef();
        e1->SetQuality(0);
        GetEffectsManager()->Fn58(e1);
        EffectParams* p = GetEffectsManager()->GetParams();
        *(u32_s00b3_5300*)&p->v.x = g_a;
        *(u32_s00b3_5300*)&p->v.y = g_b;
        *(u32_s00b3_5300*)&p->v.z = g_c;
        p->d = 1.0f;
        *(u32_s00b3_5300*)&p->w.x = g_a;
        *(u32_s00b3_5300*)&p->w.y = g_b;
        *(u32_s00b3_5300*)&p->w.z = g_c;
    }
    Effect* e2 = GetEffectsManager()->Get(0x23541242);
    if (e2) {
        e2->AddRef();
        e2->SetQuality(0);
    }
    PlanetModel* pm = GetPlanetModel();
    if (pm) {
        Planet* pl = pm->planet;
        if (pl) {
            pl->SetViewer(GetViewer());
            Helper_fc3f00(pl->Fn14(1));
        }
    }
    GetLightMgr()->Fn88(g_Lighting);
    if (!g_Gonzago) {
        AssignRef((RefObj*&)g_Gonzago, GetNameMgr()->Get(L"Gonzago"));
        World* w2_ = GetGonzagoModelWorld();
        if (w2_) {
            w2_->AddRef();
            g_Gonzago->Attach(w2_, 1, 1, 1, 0);
            w2_->Release();
        }
        if (!g_Gonzago) goto skip;
    }
    GetViewer()->Add(g_Gonzago, 0xe, 1);
    GetViewer()->Add(g_Gonzago, 0x15, 2);
skip:
    if (!fx) {
        AssignRef(fx, GetNameMgr()->Get(L"CreatureFX"));
        if (w2)
            ((Registered*)fx)->Attach(w2, 1, 1, 1, 0);
    }
    if (!phys) {
        phys = new ("Simulator", 0, 0, 0, 0) cSPEditorPhysicsWorld();
        phys->Init(0);
        phys->SetMode(0xf, 0);
    }
    GetSceneA()->Fn();
    // (scene object released below)
    if (e2) e2->Release();
    if (e1) e1->Release();
    if (w) w->Release();
}

// @ 0x00b35860
void Owner::Teardown()
{
    GetSceneA()->Fn2();
    World* w = GetGonzagoModelWorld();
    if (w) {
        w->AddRef();
        GetViewer()->Remove(0xc);
        GetViewer()->Remove(0xd);
        GetViewer()->Remove(0x14);
        GetViewer()->Remove(0x1a);
        w->SetFlag(0);
        GetModelManager()->SetWorld(0);
    }
    if (g_Gonzago)
        GetViewer()->Remove(0xe);
    if (w1)
        w1->SetFlag(0);
    if (w2) {
        GetViewer()->Remove(0xf);
        w2->SetFlag(0);
    }
    Effect* e1 = GetEffectsManager()->Get(0xeb9968);
    if (e1) {
        e1->AddRef();
        e1->Fn38();
        e1->SetQuality(2);
        GetEffectsManager()->Fn58(0);
        EffectParams* p = GetEffectsManager()->GetParams();
        Vec3 n;
        n.x = -g_na;
        n.y = -g_nb;
        n.z = -g_nc;
        p->v = n;
        p->d = 0.0f;
    }
    Effect* e2 = GetEffectsManager()->Get(0x23541242);
    if (e2) {
        e2->AddRef();
        e2->SetQuality(2);
    }
    GetLightMgr()->Fn88(0);
    PlanetModel* pm = GetPlanetModel();
    if (pm) {
        Planet* pl = pm->planet;
        if (pl) {
            pl->UnsetViewer(GetViewer());
            Helper_fc3f00(pl->Fn14(0));
        }
    }
    if (phys) {
        phys->Shutdown();
        cSPEditorPhysicsWorld* ph = phys;
        if (ph) {
            ph->~cSPEditorPhysicsWorld();
            operator delete(ph);
        }
        phys = 0;
    }
    if (e2) e2->Release();
    if (e1) e1->Release();
    if (w) w->Release();
}

// @ 0x00b35af0
void Owner::OnRemove(Listed* e)
{
    if (e == sel) {
        Listed* old = sel;
        if (old) {
            sel = 0;
            old->Release();
        }
    }
    e->Detach();
    LNode* n = e->node;
    if (n) {
        e->node = 0;
        LNode** pv = n->b;
        LNode* nx = n->a;
        *pv = nx;
        nx->a = (LNode*)pv;
        n->a = 0;
        n->b = 0;
        delete n;
    }
}
