// Slice s00b35300 -- Gonzago editor world: setup/teardown, picking helpers, small container helpers.
// Built /O2 /MD /Gy /TP /arch:SSE (no /EHsc).
#include "types.h"
#include <math.h>
#include <new.h>
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;

// Placeholder virtuals used to put a real method at its vtable slot.
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

// Physics query filter passed to the world's ray/sphere casts.
struct Filter {
    u32 w0, w1, w2, w3;
    u32 e;
    u8  type;
    u8  z;
};

struct Prop {
    char pad[0x12];
    u16 type;
    float* GetFloat();                                   // 0x41ea70
};
struct PropBase { int GetModificationCount(); };         // 0x6237a0
struct PropList {
    VP4 VP4 VP
    virtual bool Get(u32 id, Prop** out);                // 0x24
    char pad[0x2c];
    PropBase* parent;                                    // 0x30
    int count;                                           // 0x34
    int GetIntProperty(u32 id);                          // 0x6a2660
};

struct Obj;
// Entity manager: slot 92 (0x170) destroys an entity.
struct ObjMgr {
    VP16 VP16 VP16 VP16 VP16 VP4 VP4 VP4
    virtual void Destroy(Obj* o, int flag);              // 0x170
};
struct Comp : RefObj {
    VP
    virtual RefObj* Query(u32 id);                       // 0xc
    VP4 VP VP VP
    virtual bool Fn2c();                                 // 0x2c
};
struct Key {
    u32 a, b, c;
    bool operator==(const Key& o) const { return a == o.a && b == o.b && c == o.c; }
};
struct CompA : RefObj {
    VP16 VP16 VP4
    virtual Key* GetKey();                               // 0x98
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
struct Res { bool Fn(); };                               // 0xb33e10
Res* __stdcall GetRes(u32 key);                          // 0xb3d240
struct RefPtr { RefObj* p; RefPtr& operator=(RefObj* o); };   // 0xb5f950
// Lookup of a component by id, tolerant of a missing component table.
static inline RefObj* QueryComp(Comp* c, u32 id) { return c ? c->Query(id) : 0; }
static inline RefObj* QueryCompP(Comp** pc, u32 id) { Comp* c = *pc; return c ? c->Query(id) : 0; }
struct Thing2 { bool Fn(Vec3* a, Vec3* b, Vec3* c); };   // 0xc0f2e0
// Thing handed to the picking helpers: slot 43 (0xac) handle, slot 46 (0xb8) component by id.
struct Thing {
    VP16 VP16 VP4 VP4 VP VP VP
    virtual Handle* GetHandle();                         // 0xac
    VP VP
    virtual Thing2* GetComp(u32 id);                     // 0xb8
};

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

// Entry of the sorted pick list: entity (ref-counted via Obj::rc) plus its sort key.
struct Elem {
    Obj* p;
    float f;
    Elem(const Elem& o) : p(o.p) { if (p) ++p->rc; f = o.f; }
};

// Intrusive list node: slot 0 is the scalar deleting destructor.
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

// Viewer/layer registry (global at 0x15fd8c0).
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
    virtual Effect* Get(u32 id);                         // 0x54
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
struct SceneB { PropList* Fn2(); };                      // FUN_00b3d320 result

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
struct NounInfo { char pad[0xc4]; Vec3 v; };
struct NounMgr { NounInfo* Get(); };                     // 0xb25f40
NounMgr*     __stdcall GetNounManager(u32 id);           // 0xb3d300
extern Vec3 g_defVec;                                    // 0x1569494
int          __cdecl GetUniverseContext();               // 0x1021080
void         __fastcall Helper_fc3f00(RefObj* o);        // 0xfc3f00 (thiscall)
extern PropList* g_Props;                                // 0x15fd918
extern RefObj*   g_Lighting;                             // 0x167ea54
extern Registered* g_Gonzago;                            // 0x167ea58
extern u32 g_a, g_b, g_c;                                // 0x167e9f8
extern float g_na, g_nb, g_nc;                           // 0x167ea5c

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
    bool FindNearest(Vec3* pos, float t, u32 p4, RefObj** out);   // 0xb35d30
    bool Pick(int a, int b, u32 d, RefPtr* r, Vec3* out, u8 e);   // 0xb35ec0
};

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
        *(u32*)&p->v.x = g_a;
        *(u32*)&p->v.y = g_b;
        *(u32*)&p->v.z = g_c;
        p->d = 1.0f;
        *(u32*)&p->w.x = g_a;
        *(u32*)&p->w.y = g_b;
        *(u32*)&p->w.z = g_c;
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

// @ 0x00b35b80
Vec3 __stdcall GetNounOffset(u32 id)
{
    NounInfo* n = GetNounManager(id)->Get();
    if (n)
        return n->v;
    return g_defVec;
}

// @ 0x00b35bf0
bool __stdcall PickSegment(Thing* obj, Vec3* a, Vec3* b, Vec3* out)
{
    if (obj) {
        Thing2* c = obj->GetComp(0xce9f6639);
        if (c)
            return c->Fn(a, b, out);
    }
    World* w = GetGonzagoModelWorld();
    if (w)
        w->AddRef();
    Handle* h = obj->GetHandle();
    if (w) {
        if (h) {
            Filter f;
            float t;
            f.w0 = 0; f.w1 = 0; f.w2 = 0; f.w3 = 0; f.e = 0; f.z = 0;
            f.type = 4;
            if (w->Cast2(a, b, h, &t, &f)) {
                Vec3 A(*a);
                Vec3 B(*b);
                out->x = A.x + (B.x - A.x) * t;
                out->y = A.y + (B.y - A.y) * t;
                out->z = A.z + (B.z - A.z) * t;
                w->Release();
                return true;
            }
        }
        w->Release();
    }
    return false;
}

// @ 0x00b35d30
bool Owner::FindNearest(Vec3* pos, float r, u32 p4, RefObj** out)
{
    Filter f;
    f.w0 = 0; f.w1 = 0; f.w2 = 0; f.w3 = 0;
    f.e = p4;
    f.type = 3;
    f.z = 0;
    RefObj* old = *out;
    if (old) {
        *out = 0;
        old->Release();
    }
    World* w = GetGonzagoModelWorld();
    if (w)
        w->AddRef();
    if ((w && w->Cast(pos, r, &vbeg, &f)) || w1->Cast(pos, r, &vbeg, &f)) {
        Obj** end = vend;
        float best = 3.4028234e+38f;
        for (Obj** p = vbeg; p != end; ++p) {
            Obj* o = *p;
            if (o->comp) {
                float dx = o->x - pos->x;
                float dy = o->y - pos->y;
                float dz = o->z - pos->z;
                float d = sqrtf(dz * dz + dy * dy + dx * dx);
                if (d <= best) {
                    best = d;
                    RefObj* q = QueryComp(o->comp, 0x17f243b);
                    RefObj* prev = *out;
                    if (q != prev) {
                        if (q) q->AddRef();
                        *out = q;
                        if (prev) prev->Release();
                    }
                }
            }
        }
    }
    bool ok = *out != 0;
    if (w)
        w->Release();
    return ok;
}

// @ 0x00b35ec0
bool Owner::Pick(int a, int b, u32 d, RefPtr* r, Vec3* out, u8 e)
{
    Vec3 loc;
    Filter f;
    f.w0 = 0; f.w1 = 0; f.w2 = 0; f.w3 = 0;
    f.type = e;
    f.z = 0;
    f.e = d;
    Obj* o = GetGonzagoModelWorld()->Pick(a, b, 0, &loc, 0, &f, 0, 0);
    if (!o) {
        o = w1->Pick(a, b, 0, &loc, 0, &f, 0, 0);
        if (!o)
            return false;
    }
    if (o->comp) {
        RefObj* q = QueryComp(o->comp, 0x17f243b);
        if (q) {
            *r = q;
            *out = loc;
            return true;
        }
    }
    return false;
}

// @ 0x00b35fa0
float GetEditorFloat()
{
    float f = 0.0f;
    Prop* p;
    if (g_Props && g_Props->Get(0x26b7d69, &p) && p->type == 0xd)
        f = *p->GetFloat();
    PropList* t = GetSceneB()->Fn2();
    if (t && t->Get(0x26b7d69, &p) && p->type == 0xd)
        f = *p->GetFloat();
    return f;
}

// @ 0x00b36030
bool CanSelect(Obj* o)
{
    if (o->f8c > 0.0f)
        return false;
    CompA* a = (CompA*)QueryComp(o->comp, 0x1186577);
    Comp* b = (Comp*)QueryComp(o->comp, 0x17f243b);
    if (!a || !b)
        return false;
    return !b->Fn2c() && GetRes(a->GetKey()->b)->Fn();
}

// @ 0x00b360d0
Elem* FindByKey(Elem* first, Elem* last, Key key)
{
    while (first != last) {
        CompA* a = (CompA*)QueryCompP(&first->p->comp, 0x1186577);
        if (*a->GetKey() == key)
            break;
        ++first;
    }
    return first;
}

static inline u8 IsFlagBit(int v) { u8 b = (u8)((u32)v >> 31); b &= 1; return b; }

// @ 0x00b36130
void __stdcall ReleaseRange(Elem* first, Elem* last)
{
    for (; first < last; ++first) {
        Obj* o = first->p;
        if (o) {
            int rc = o->rc;
            if (rc > 1)
                o->rc = rc - 1;
            else
                o->mgr->Destroy(o, IsFlagBit(o->f4));
        }
    }
}

// @ 0x00b36180
float __fastcall SortKey(Obj* o);                        // 0xc887c0 (thiscall, float result)
void HeapAdjust(Obj** arr, int first, int len, int hole, u32 v1, u32 v2);
void SiftDown_b33ea0(Obj** arr, int first, int hole, u32 v1, u32 v2);   // 0xb33ea0
void HeapPercolate(Obj** arr, int first, int len, int hole, u32 v1, u32 v2)
{
    int child = hole * 2 + 2;
    while (child < len) {
        Obj* right = arr[child];
        Obj* left = arr[child - 1];
        float r = SortKey(right);
        if (SortKey(left) > r)
            --child;
        arr[hole] = arr[child];
        hole = child;
        child = child * 2 + 2;
    }
    if (child == len) {
        arr[hole] = arr[child - 1];
        hole = child - 1;
    }
    SiftDown_b33ea0(arr, first, hole, v1, v2);
}

struct Iter { Elem* p; Iter(Elem* q) : p(q) {} };

// @ 0x00b36200
Iter CopyRange(Elem* first, Elem* last, Elem* dest)
{
    Iter r(dest);
    Elem* d = dest;
    for (; first != last; ++first, ++d)
        new (d) Elem(*first);
    r.p = d;
    return r;
}

// @ 0x00b36250
void FillN(Elem* dest, unsigned n, const Elem* src)
{
    Elem* d = dest;
    for (; n > 0; --n, ++d)
        new (d) Elem(*src);
}

// @ 0x00b36280
void CopyTo(Elem* first, Elem* last, Elem* dest)
{
    Elem* d = dest;
    for (; first != last; ++first, ++d)
        new (d) Elem(*first);
}
